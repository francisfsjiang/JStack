# encoding: utf-8

import requests
import requests.adapters


class DockerNode(requests.Session):
    """

    """
    def __init__(self, url='unix:///var/run/docker.sock', max_container_num=10, docker_node_num=0):
        super().__init__()
        self.url = url
        if url.startswith('unix://'):
            self.conn_type = 'unix_sock'
            self.host = url.strip('unix:/')
        elif url.startswith('http://'):
            self.conn_type = 'http'
            self.host = url.strip('http://')
        self.container_list = []
        self.docker_node_num = docker_node_num
        self.headers.update({'Content-Type': 'application/json'})

        # self.mount('http://', requests.adapters.HTTPAdapter)

    def containers(self, all_item=True):
        url = self.url + '/containers/json'
        print(url)
        return self.get(url, params={'all': all_item})

    def create_container(self):
        url = self.url + '/containers/create'

        container_config = {
            "Hostname": "test",
            "Domainname": "test",
            "User": "",
            "Memory": 0xA00000,  #10MB=0xA00000B
            "MemorySwap": -1,  #memory+swap
            "CpuShares": 0,
            "Cpuset": "",
            "AttachStdin": True,
            "AttachStdout": True,
            "AttachStderr": True,
            "Tty": False,
            "OpenStdin": False,
            "StdinOnce": False,
            "Env": None,
            "Cmd": [
                "/bin/bash"
            ],
            "Entrypoint": "",
            "Image": "ubuntu:14.10",
            "Volumes": {
            },
            "WorkingDir": "",
            "NetworkDisabled": False,
            "ExposedPorts": {
            },
            "SecurityOpts": [""],
            "HostConfig": {
                "Binds": [],
                "Links": [],
                "LxcConf": {"lxc.utsname": "docker"},
                "PortBindings": {},
                "PublishAllPorts": False,
                "Privileged": False,
                "Dns": ["8.8.8.8"],
                "DnsSearch": [""],
                "VolumesFrom": [],
                "CapAdd": [],
                "CapDrop": [],
                "RestartPolicy": {"Name": "", "MaximumRetryCount": 0},
                "NetworkMode": "bridge",
                "Devices": []
            }
        }
        # return self.post(url, container_config, headers={'Content-Type: application/json'})
        return self.post(url, json=container_config)

    def stop_container(self, id):
        url = self.url + '/containers/%s/stop?t=1' % id
        return self.post(url)

    def start_container(self, id):
        url = self.url + '/containers/%s/start' % id
        start_config = {
            "Binds": ["/tmp:/tmp"],
            "Links": ["redis3:redis"],
            "LxcConf": {"lxc.utsname":"docker"},
            "PortBindings": {"22/tcp": [{"HostPort": "11022"}]},
            "PublishAllPorts": False,
            "Privileged": False,
            "Dns": ["8.8.8.8"],
            "DnsSearch": [""],
            "VolumesFrom": ["parent", "other:ro"],
            "CapAdd": [],
            "CapDrop": ["MKNOD"],
            "RestartPolicy": {"Name": "", "MaximumRetryCount": 0},
            "NetworkMode": "bridge",
            "Devices": []
        }
        return self.post(url, json=start_config)
