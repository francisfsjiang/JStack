# encoding: utf-8

import mysql.connector
import mysql.connector.errors

import judge.errors as errors
from judge.db_adapter.adapter import Adapter


class MysqlAdapter(Adapter):
    """
    Mysql database adapter
    """
    def __init__(self, host: str, port: int, database: str, user: str, password: str):
        super().__init__()
        try:
            self.conn = mysql.connector.connect(
                host=host,
                port=port,
                database=database,
                user=user,
                password=password
            )
        except Exception as e:
            print(e)

