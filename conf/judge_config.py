# encoding: utf-8


DB = {
    'sys_name': 'mongodb',
    'host': '192.168.1.107',
    'port': 27017,
    'db_name': 'js_judge',
    'user': 'root',
    'password': 'test'
}

LOG = {
    'log_file': 'log/judge.log',
    'format': '%(asctime)s - %(name)s - %(levelname)s - %(message)s'
}

RUN = {
    'pid_file': 'run/judged.pid'
}

DOCKER = {
    'hosts': [
        '192.168.1.107:5555'
    ],
    'max_container_num': [
        5
    ],
}