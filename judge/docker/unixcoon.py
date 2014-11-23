# encoding: utf-8


import six

if six.PY3:
    import http.client as httplib
else:
    import httplib
import requests.adapters
import socket

try:
    import requests.packages.urllib3.connectionpool as connectionpool
except ImportError:
    import urllib3.connectionpool as connectionpool

try:
    from requests.packages.urllib3._collections import RecentlyUsedContainer
except ImportError:
    from urllib3._collections import RecentlyUsedContainer


class UnixHTTPConnection(httplib.HTTPConnection, object):
    def __init__(self, base_url, unix_socket, timeout=60):
        httplib.HTTPConnection.__init__(self, 'localhost', timeout=timeout)
        self.base_url = base_url
        self.unix_socket = unix_socket
        self.timeout = timeout

    def connect(self):
        sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        sock.settimeout(self.timeout)
        sock.connect(self.base_url.replace("http+unix:/", ""))
        self.sock = sock

    def _extract_path(self, url):
        # remove the base_url entirely..
        return url.replace(self.base_url, "")

    def request(self, method, url, **kwargs):
        url = self._extract_path(self.unix_socket)
        super(UnixHTTPConnection, self).request(method, url, **kwargs)


class UnixHTTPConnectionPool(connectionpool.HTTPConnectionPool):
    def __init__(self, base_url, socket_path, timeout=60):
        connectionpool.HTTPConnectionPool.__init__(self, 'localhost',
                                                   timeout=timeout)
        self.base_url = base_url
        self.socket_path = socket_path
        self.timeout = timeout

    def _new_conn(self):
        return UnixHTTPConnection(self.base_url, self.socket_path,
                                  self.timeout)


class UnixAdapter(requests.adapters.HTTPAdapter):
    def __init__(self, base_url, timeout=60):
        self.base_url = base_url
        self.timeout = timeout
        self.pools = RecentlyUsedContainer(10,
                                           dispose_func=lambda p: p.close())
        super(UnixAdapter, self).__init__()

    def get_connection(self, socket_path, proxies=None):
        with self.pools.lock:
            pool = self.pools.get(socket_path)
            if pool:
                return pool

            pool = UnixHTTPConnectionPool(self.base_url,
                                          socket_path,
                                          self.timeout)
            self.pools[socket_path] = pool

        return pool

    def close(self):
        self.pools.clear()

