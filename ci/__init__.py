import json
import os
import sys

root = os.environ['GITHUB_WORKSPACE']
projects_root = os.path.join(root, 'homework')
event_payload = json.load(open(os.environ['GITHUB_EVENT_PATH'], 'r'))
username = os.environ['GITHUB_ACTOR']
repository = os.environ['GITHUB_REPOSITORY']
access_token = os.environ['GITHUB_TOKEN']
sha = os.environ['GITHUB_SHA']


ANSI_RESET = u'\u001b[0m'
ANSI_BRIGHT_CYAN = u'\u001b[36;1m'


def log_info(*args):
    print(f'{ANSI_BRIGHT_CYAN}CI:', ' '.join(args), ANSI_RESET)
    sys.stdout.flush()
