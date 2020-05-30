import os
import shutil
import subprocess
import sys
import tempfile
from distutils.dir_util import copy_tree

from . import event_payload, projects_root, log_info, username, access_token, repository
from .actions import LogGroup
from .project import Project
from .release import Release


def get_changed_files():
    before = event_payload['before']
    after = event_payload['after']

    return subprocess.check_output(['git', '--no-pager', 'diff', '--name-only', before, after]).decode(sys.getdefaultencoding()).splitlines()


def get_project_names():
    return [f.name for f in os.scandir(projects_root) if f.is_dir()]


changed_files = get_changed_files()
projects = [Project(name) for name in get_project_names()]
changed_projects = [p for p in projects if p.should_update(changed_files)]


def build_projects():
    for project in changed_projects:
        log_info(project.name, 'has changed')
        project.run_cmake()
        project.run_make()
        project.run_tests()


def generate_and_upload_docs():
    old_cwd = os.getcwd()
    tmp = tempfile.TemporaryDirectory()
    os.chdir(tmp.name)

    log_info('Entered temporary directory', os.getcwd(), 'cloning repository now')

    clone_url = f'https://{username}:{access_token}@github.com/{repository}.git'
    subprocess.check_call(['git', 'clone', '--single-branch', '--branch', 'gh-pages', clone_url, '.'])
    subprocess.check_call(['git', 'config', 'user.name', username])
    subprocess.check_call(['git', 'config', 'user.email', f'{username}@users.noreply.github.com'])

    for project in changed_projects:
        project_docs_out = os.path.join(tmp.name, project.cmake_project_name)
        project_docs_in = project.generate_docs()
        shutil.rmtree(project_docs_out, ignore_errors=True)
        copy_tree(project_docs_in, project_docs_out)

    if subprocess.check_output(['git', 'status', '-s']).decode(sys.getdefaultencoding()):
        with LogGroup('Uploading'):
            log_info('Creating a commit')
            subprocess.check_call(['git', 'add', '.'])
            subprocess.check_call(['git', 'status'])
            subprocess.check_call(['git', 'commit', '-a', '-m', f'Generated docs for {sha[0:8]}'])
            log_info('Pushing')
            subprocess.check_call(['git', 'push', clone_url, 'gh-pages'])
    else:
        log_info('There are no changes to documentation')

    os.chdir(old_cwd)


def generate_packages():
    return [project.create_package() for project in changed_projects]


if not changed_projects:
    log_info('No changes in projects')
    exit(0)

with LogGroup('Building projects'):
    build_projects()

with LogGroup('Generating and uploading documentation'):
    generate_and_upload_docs()

with LogGroup('Generating packages'):
    generate_packages()

with LogGroup('Creating and uploading a release'):
    release = Release(changed_projects)
    release.build_and_upload()
