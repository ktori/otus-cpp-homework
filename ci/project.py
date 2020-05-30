import os
import subprocess
from typing import List

from ci import projects_root, log_info
from ci.actions import LogGroup


class Project:
    def __init__(self, name):
        self.name = name
        self.cwd = os.path.join(projects_root, name)
        self.cmake_project_name = None

    def should_update(self, changes: List[str]):
        for change in changes:
            if change == 'CMakeLists.txt':
                return True
            if change.startswith('.github'):
                return True
            if change.startswith('ci'):
                return True
            if change.startswith(f'homework/{self.name}'):
                return True

        return False

    def run_cmake(self):
        with LogGroup(f'Configuring project {self.name}'):
            subprocess.check_call(['cmake', '.'], cwd=self.cwd)
            with open(os.path.join(self.cwd, 'CMakeCache.txt'), 'r') as cache:
                for line in cache:
                    if 'CMAKE_PROJECT_NAME:STATIC' in line:
                        self.cmake_project_name = line[len('CMAKE_PROJECT_NAME:STATIC='):].replace('\n', '')
                        log_info('Project name for', self.name, 'is', self.cmake_project_name)
                        break
                if self.cmake_project_name is None:
                    log_info('Unable to determine project name for', self.name)

    def run_make(self):
        with LogGroup(f'Building project {self.name}'):
            subprocess.check_call(['make'], cwd=self.cwd)

    def run_tests(self):
        if os.path.exists(os.path.join(self.cwd, 'test')):
            subprocess.check_call(['make', 'test'], cwd=self.cwd)
        else:
            log_info('No tests for', self.name)

    def create_package(self) -> str:
        with LogGroup(f'Building package for {self.name}'):
            subprocess.check_call(['make', 'package'], cwd=self.cwd)
            for file in os.listdir(self.cwd):
                if file.endswith('.deb'):
                    return os.path.join(self.cwd, file)
            raise RuntimeError('Could not locate deb package')

    def generate_docs(self) -> str:
        with LogGroup(f'Generating documentation {self.name}'):
            docs_out = os.path.join(self.cwd, 'docs', self.cmake_project_name)
            log_info('Generating documentation', self.name)
            log_info('Documentation output', docs_out)
            os.makedirs(docs_out)
            subprocess.check_call(['doxygen', 'Doxyfile'], cwd=self.cwd)
            return docs_out
