# encoding: utf-8

import configparser
import logging
import os
import signal
import sys
import time

# import pymongo

from judge.db import JudgeDBConnection


def init_logger(judge_config):
    """
    Init and return the logger
    :param judge_config:
    :return: judge_logger
    """
    judged_logger = logging.getLogger('Judged')
    log_file_path = os.path.join(os.getcwd(), judge_config['log']['log_file'])
    #check dir
    (_path, _) = os.path.split(log_file_path)
    if not os.path.exists(_path):
        os.mkdir(_path)

    log_handler = logging.FileHandler(log_file_path, delay=True)
    log_format = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    log_handler.setFormatter(log_format)
    log_handler.setLevel(level=logging.DEBUG)
    judged_logger.setLevel(level=logging.DEBUG)
    judged_logger.addHandler(log_handler)
    return judged_logger


def start_daemon(judge_config: configparser.ConfigParser, judge_logger: logging.Logger):
    """
    Start a daemon process which is running the .
    :param judge_config:
    :param judge_logger:
    :return: None
    """

    pid_file_path = os.path.join(os.getcwd(), judge_config['run']['pid_file'])
    # pid = os.fork()
    # if pid > 0:
    #     sys.exit(0)
    #
    # os.chdir('/')
    # os.setsid()
    # os.umask(0)
    #
    # pid = os.fork()
    # if pid > 0:
    #     sys.exit(0)

    if os.path.exists(pid_file_path):
        print('Judged daemon has being running.')
        judge_logger.error('Judged daemon has being running.')
        exit(0)

    try:
        (_path, _) = os.path.split(pid_file_path)
        if not os.path.exists(_path):
            os.mkdir(_path)
        pid_file = open(pid_file_path, mode='w+')
        print('Judge daemon(pid=%d) start successfully.' % os.getpid())
        judge_logger.info('Judge daemon(pid=%d) start successfully.' % os.getpid())
        pid_file.write('%d' % os.getpid())
        pid_file.close()
    except Exception as e:
        print(e)

    #redirect stdio
    sys.stdout.flush()
    sys.stderr.flush()
    si = open(os.devnull, 'r')
    # so = open(os.devnull, 'a+')
    # se = open(os.devnull, 'a+')
    os.dup2(si.fileno(), sys.stdin.fileno())
    # os.dup2(so.fileno(), sys.stdout.fileno())
    # os.dup2(se.fileno(), sys.stderr.fileno())

    # signal.signal(signal.SIGKILL, exit_clean)

    main_loop(judge_config, judge_logger)

    try:
        os.remove(pid_file_path)
    except Exception as e:
        judge_logger.error(e)
    exit(0)


def main_loop(judge_config: configparser.ConfigParser, judge_logger: logging.Logger):
    """
    A loop to check if there is
    :param logger:
    :return:
    """
    try:
        db_coon = JudgeDBConnection(judge_config)

        while True:
            time.sleep(3)
            db_coon.has_new_run()
            judge_logger.debug('Judge daemon runs for 3s.')
    except Exception as e:
        judge_logger.error(e)
        return
