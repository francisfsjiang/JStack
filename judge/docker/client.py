# encoding: utf-8

import requests


class DockerClient(requests.Session):
    """

    """
    def __init__(self, url='unix:///var/run/docker.sock'):
        super().__init__()