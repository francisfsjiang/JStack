#!/usr/bin/env python3
# encoding: utf-8

import os
import sys
import time
import signal
import configparser
import logging
import judge.core


JudgedConfig = None
JudgedLogger = None


def start_daemon(pid_file_path):
    pid = os.fork()
    if pid > 0:
        sys.exit(0)

    os.chdir('/')
    os.setsid()
    os.umask(0)

    pid = os.fork()
    if pid > 0:
        sys.exit(0)

    if os.path.exists(pid_file_path):
        print('Judged daemon is running.')
        JudgedLogger.error('Judged daemon is running.')
        exit(0)

    try:
        (_path, _) = os.path.split(pid_file_path)
        if not os.path.exists(_path):
            os.mkdir(_path)
        pid_file = open(pid_file_path, mode='w+')
        print('Judge daemon(pid=%d) start successfully.' % os.getpid())
        JudgedLogger.info('Judge daemon(pid=%d) start successfully.' % os.getpid())
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

    judge.core.main_loop(JudgedLogger)


def init_logger():
    global JudgedLogger
    JudgedLogger = logging.getLogger('Judged')
    log_file_path = os.path.join(os.getcwd(), JudgedConfig['log']['log_file'])
    #check dir
    (_path, _) = os.path.split(log_file_path)
    if not os.path.exists(_path):
        os.mkdir(_path)

    log_handler = logging.FileHandler(log_file_path, delay=True)
    log_format = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    log_handler.setFormatter(log_format)
    log_handler.setLevel(level=logging.DEBUG)
    JudgedLogger.setLevel(level=logging.DEBUG)
    JudgedLogger.addHandler(log_handler)


def print_help():
    print('usage: judged start|status|stop')

if __name__ == '__main__':

    JudgedConfig = configparser.ConfigParser()
    JudgedConfig.read('conf/judged.conf')

    pid_file_path = os.path.join(os.getcwd(), JudgedConfig['run']['pid_file'])
    init_logger()

    if len(sys.argv) < 2:
        print_help()
        exit(0)
    elif sys.argv[1] == 'start':
        start_daemon(pid_file_path)
    elif sys.argv[1] == 'status':
        pass
    elif sys.argv[1] == 'stop':
        try:
            pid_file = open(pid_file_path, 'r')
            pid = int(pid_file.read())
            os.kill(pid, signal.SIGKILL)
            print('Judge daemon(pid=%d) has bing killed' % pid)
            JudgedLogger.info('Judge daemon(pid=%d) has bing killed' % pid)
            pid_file.close()
            os.remove(pid_file_path)
        except FileNotFoundError as e:
            print('Process is not running')
    else:
        print_help()
    exit(0)
