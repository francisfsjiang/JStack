# encoding: utf-8

from judge.db_adapter.mongo_adapter import MongodbAdapter


class JudgeDBConnection:
    """
    :param
    """
    def __init__(self, judge_config):
        self.db_adapter = MongodbAdapter(
            host=judge_config.DB['host'],
            port=int(judge_config.DB['port']),
            database=judge_config.DB['db_name']
        )

    def has_new_run(self):
        print(self.db_adapter.has_new_run())