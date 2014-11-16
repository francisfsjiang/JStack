# encoding: utf-8

from configparser import ConfigParser

import pymongo


class JudgeDBCoon:
    """
    :param
    """
    def __init__(self, judge_config: ConfigParser):
        self.coon = pymongo.MongoClient(
            judge_config['db']['host'],
            int(judge_config['db']['port'])
        )
        self.db = self.coon.run_queue

    def has_new_run(self):
        self.coon