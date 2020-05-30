import os
import json
import shutil
import subprocess
import sys
import tempfile
from distutils.dir_util import copy_tree
from subprocess import check_output
from typing import List

root = os.environ['GITHUB_WORKSPACE']
projects_root = os.path.join(root, 'homework')
event_payload = json.load(open(os.environ['GITHUB_EVENT_PATH'], 'r'))
username = os.environ['GITHUB_ACTOR']
repository = os.environ['GITHUB_REPOSITORY']
access_token = os.environ['GITHUB_TOKEN']


def get_changed_files():
    before = event_payload['before']
    after = event_payload['after']

    return check_output(['git', '--no-pager', 'diff', '--name-only', before, after]).decode(sys.getdefaultencoding()).splitlines()


def get_project_names():
    return [f.name for f in os.scandir(projects_root) if f.is_dir()]


class Project:
    def __init__(self, name):
        self.name = name
        self.cwd = os.path.join(projects_root, name)

    def should_update(self, changes: List[str]):
        for change in changes:
            if change == 'CMakeLists.txt':
                return True
            if change.startswith('.github'):
                return True
            if change.startswith(f'homework/project/{self.name}'):
                return True

        return False

    def run_cmake(self):
        subprocess.check_call(['cmake', '.'], cwd=self.cwd)

    def run_make(self):
        subprocess.check_call(['make'], cwd=self.cwd)

    def run_tests(self):
        pass

    def create_package(self) -> str:
        pass

    def generate_docs(self) -> str:
        docs_out = os.path.join(self.cwd, 'docs', self.name)
        os.makedirs(docs_out)
        subprocess.check_call(['doxygen', 'Doxyfile'], cwd=self.cwd)
        return docs_out


changed_files = get_changed_files()
projects = [Project(name) for name in get_project_names()]
changed_projects = [p for p in projects if p.should_update(changed_files)]


def build_projects():
    for project in changed_projects:
        project.run_cmake()
        project.run_make()
        project.run_tests()


def generate_and_upload_docs():
    old_cwd = os.getcwd()
    tmp = tempfile.TemporaryDirectory()
    os.chdir(tmp.name)

    clone_url = f'https://{username}:{access_token}@github.com/{repository}.git'
    subprocess.check_call(['git', 'clone', '--single-branch', '--branch', 'gh-pages', clone_url, '.'])
    subprocess.check_call(['git', 'config', 'user.name', username])
    subprocess.check_call(['git', 'config', 'user.email', f'{username}@users.noreply.github.com'])

    for project in changed_projects:
        project_docs_out = os.path.join(tmp.name, project.name)
        project_docs_in = project.generate_docs()
        shutil.rmtree(project_docs_out, ignore_errors=True)
        copy_tree(project_docs_in, project_docs_out)

    sha = os.environ['GITHUB_SHA']
    subprocess.check_call(['git', 'commit', '-a', '-m', f'Generated docs for {sha[0:8]}'])
    subprocess.check_call(['git', 'push', clone_url, 'gh-pages'])

    os.chdir(old_cwd)


build_projects()
generate_and_upload_docs()

# generate packages

# create and upload release
