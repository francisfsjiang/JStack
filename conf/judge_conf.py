# encoding: utf-8

judge_conf = None

judge_conf.DB = {
    'host': '192.168.1.107',
    'port': 27017,
    'db_name': 'js_judge',
    'user': 'root',
    'password': 'test'
}

judge_conf.LOG = {
    'log_file': 'log/judge.log',
    'format': '%(asctime)s - %(name)s - %(levelname)s - %(message)s'
}

judge_conf.RUN = {
    'pid_file': 'run/judged.pid'
}
