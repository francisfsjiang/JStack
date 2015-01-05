# encoding: utf-8


class JSDBConnectionFailed(Exception):
    def __init__(self, msg):
        self.arg = msg

