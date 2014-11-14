#!/usr/bin/env python3
# encoding: utf-8

import os
import sys
import time
import fcntl
import signal
import configparser


JudgeConfig = None


def start_daemon(pid_file_path):
    # pid_file_path = os.path.join(os.getcwd(), JudgeConfig['run']['pid_file'])
    # LOG_FILE = os.path.join(os.getcwd(), LOG_FILE)

    pid = os.fork()
    if pid > 0:
        sys.exit(0)

    os.chdir('/')
    os.setsid()
    os.umask(0)

    pid = os.fork()
    if pid > 0:
        sys.exit(0)

    pid_file = open(pid_file_path, mode='w')
    fcntl.fcntl(pid_file, fcntl.F_GETLK)
    try:
        fcntl.flock(pid_file, fcntl.LOCK_EX)
        print('Daemon on %d start successfully.' % os.getpid())
    except IOError:
        print('Judged process has running')
        exit(0)
    pid_file.write('%d' % os.getpid())

    sys.stdout.flush()
    sys.stderr.flush()
    si = open(os.devnull, 'r')
    so = open(os.devnull, 'a+')
    # se = open(os.devnull, 'a+')
    os.dup2(si.fileno(), sys.stdin.fileno())
    os.dup2(so.fileno(), sys.stdout.fileno())
    # os.dup2(se.fileno(), sys.stderr.fileno())

    # log_file = open(LOG_FILE, 'w+')
    while True:
        time.sleep(10)
        f = open('/Users/never/test.txt', 'a')
        #f.wirte(str(os.getpid()))
        f.write('hello\n' + str(os.getpid()))


def print_help():
    print('usage: judged start|status|stop')

if __name__ == '__main__':

    JudgeConfig = configparser.ConfigParser()
    JudgeConfig.read('conf/judged.conf')

    pid_file_path = os.path.join(os.getcwd(), JudgeConfig['run']['pid_file'])

    if len(sys.argv) < 2:
        print_help()
        exit(0)
    elif sys.argv[1] == 'start':
        start_daemon(pid_file_path)
    elif sys.argv[1] == 'status':
        pass
    elif sys.argv[1] == 'stop':
        pid = int(open(pid_file_path, 'r').read())
        print(pid)
        os.kill(pid, signal.SIGKILL)
    else:
        print_help()
    exit(0)
