from ci import access_token


def base_url():
    return 'https://api.github.com'


def headers():
    return {
        'Accept': 'application/vnd.github.v3+json',
        'Authorization': f'token {access_token}',
        'User-Agent': 'ktori'
    }

