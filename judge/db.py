# encoding: utf-8

from configparser import ConfigParser

from judge.db_adapter.mongo_adapter import MongodbAdapter


class JudgeDBConnection:
    """
    :param
    """
    def __init__(self, judge_config: ConfigParser):
        self.db_adapter = MongodbAdapter(
            host=judge_config['db']['host'],
            port=int(judge_config['db']['port']),
            db=judge_config['db']['db_name']
        )

    def has_new_run(self):
        print(self.db_adapter.has_new_run())