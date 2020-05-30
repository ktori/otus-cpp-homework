import sys


def issue_command(name, properties: dict, message):
    escaped_message = message.replace('%', '%25').replace('\r', '%0D').replace('\n', '%0A')
    print(f'::{name}{escaped_message}')
    sys.stdout.flush()


def issue(name, message=''):
    issue_command(name, {}, message)


class LogGroup:
    def __init__(self, name):
        self.name = name

    def __enter__(self):
        issue('group', self.name)

    def __exit__(self, exc_type, exc_val, exc_tb):
        issue('endgroup')
