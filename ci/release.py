from os.path import basename

import requests

from ci import repository, sha, log_info
from ci.github import base_url, headers


class Release:
    def __init__(self, projects):
        self.projects = projects
        self.id = None
        self.created_json = None
        self.upload_url = None

    def name(self):
        return f'{sha[0:8]}: {", ".join([p.name for p in self.projects])}'

    def build_and_upload(self):
        packages = [(project, project.create_package()) for project in self.projects]
        self.create_remote()
        for (project, package) in packages:
            self.upload_asset(package, basename(package), f'Package for {project.name}')

    def create_remote(self):
        r = requests.post(f'{base_url()}/repos/{repository}/releases', json={
            'tag_name': 'refs/heads/master',
            'target_commitish': sha,
            'name': self.name(),
            'body': f'Automatic CI build of projects'
        }, headers=headers)
        self.created_json = r.json()
        self.id = self.created_json['id']
        self.upload_url = self.created_json['upload_url'].replace('{?name,label}', '')

    def upload_asset(self, file, name, label):
        with open(file, 'rb') as f:
            log_info('Uploading file', file)
            r = requests.post(self.upload_url, data=f.read(), params={
                'name': name,
                'label': label
            }, headers={**headers(), 'Content-Type': 'application/vnd.debian.binary-package'})
            log_info('Uploaded release asset', r.json()['id'])
