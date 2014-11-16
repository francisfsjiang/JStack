# encoding: utf-8

import mysql.connector


class MysqlAdapter:
    """
    Mysql database adapter
    """
    def __init__(self, host: str, port: int, database: str, user: str, password: str):
        self.conn = mysql.connector.connect(
            host=host,
            port=port,
            database=database,
            user=user,
            password=password
        )