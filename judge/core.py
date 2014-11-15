# encoding: utf-8

import time


def main_loop(logger):
    while True:
        time.sleep(3)
        logger.debug('Judge daemon runs for 3s.')
