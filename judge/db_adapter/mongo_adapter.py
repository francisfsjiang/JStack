# encoding: utf-8

import pymongo


class MongoAdapter:
    """
    Mongodb adapter
    """
    def __init__(self, host: str, port: int, db: str):
        self.coon = pymongo.MongoClient(
            host,
            port
        )
        self.db = self.coon[db]
