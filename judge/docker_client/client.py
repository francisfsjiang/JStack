# encoding: utf-8

import requests
import requests.adapters


class Client(requests.Session):
    """

    """
    def __init__(self, url='unix:///var/run/docker.sock', max_container_num=10):
        super().__init__()
        self.url = url
        if url.startswith('unix://'):
            self.conn_type = 'unix_sock'
            self.host = url.strip('unix:/')
        elif url.startswith('http://'):
            self.conn_type = 'http'
            self.host = url.strip('http://')

        # self.mount('http://', requests.adapters.HTTPAdapter)

    def containers(self, all=True):
        url = self.url + '/containers/json'
        print(url)
        return self.get(url, params={'all': all})
