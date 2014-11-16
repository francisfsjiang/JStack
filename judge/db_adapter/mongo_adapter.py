# encoding: utf-8

import pymongo
import json


class MongoAdapter:
    """
    Mongodb connection adapter
    """
    def __init__(self, host: str, port: int, db: str):
        self.coon = pymongo.MongoClient(
            host,
            port
        )
        self.db = self.coon[db]

    def has_new_run(self):
        return self.db.run_queue.find_one()
