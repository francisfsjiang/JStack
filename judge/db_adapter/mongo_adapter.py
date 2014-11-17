# encoding: utf-8

import pymongo
import json

import judge.errors as errors
from judge.db_adapter.adapter import Adapter


class MongodbAdapter(Adapter):
    """
    Mongodb connection adapter
    """
    def __init__(self, host='localhost', port=27017, database='', user='', password=''):
        super().__init__()
        try:
            self.conn = pymongo.MongoClient(
                host,
                port
            )
        except Exception as e:
            print(e)
        self.db = self.conn[database]

    def has_new_run(self):
        return self.db.run_queue.find_one()
