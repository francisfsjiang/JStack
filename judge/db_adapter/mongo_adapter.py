# encoding: utf-8

import pymongo
import json


class MongodbAdapter:
    """
    Mongodb connection adapter
    """
    def __init__(self, host: str, port: int, db: str):
        self.conn = pymongo.MongoClient(
            host,
            port
        )
        self.db = self.conn[db]

    def has_new_run(self):
        return self.db.run_queue.find_one()
