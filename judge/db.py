# encoding: utf-8

from configparser import ConfigParser

from judge.db_adapter.mongo_adapter import MongoAdapter


class JudgeDBCoon:
    """
    :param
    """
    def __init__(self, judge_config: ConfigParser):
        self.db_adapter = MongoAdapter(
            host=judge_config['db']['host'],
            port=judge_config['db']['port'],
            db=judge_config['db']['db_name']
        )

    def has_new_run(self):
        self.coon