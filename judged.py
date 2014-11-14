#!/usr/bin/env python3
# encoding: utf-8

import os
import sys
import time
import fcntl


PID_FILE = '/var/run/judged.pid'
LOG_FILE = '/var/log/judged.log'


def start_daemon():
    pid = os.fork()
    if pid > 0:
        sys.exit(0)

    os.chdir("/")
    os.setsid()
    os.umask(0)

    pid = os.fork()
    if pid > 0:
        sys.exit(0)

    print("Daemon on %d start successfully." % os.getpid())
    sys.stdout.flush()
    sys.stderr.flush()
    si = open(os.devnull, 'r')
    so = open(os.devnull, 'a+')
    # se = open(os.devnull, 'a+')
    os.dup2(si.fileno(), sys.stdin.fileno())
    os.dup2(so.fileno(), sys.stdout.fileno())
    # os.dup2(se.fileno(), sys.stderr.fileno())

    log_file = open(LOG_FILE, 'w+')
    while True:
        time.sleep(10)
        f = open('/Users/never/test.txt', 'a')
        #f.wirte(str(os.getpid()))
        f.write('hello\n' + str(os.getpid()))


def print_help():
    print("usage: judged start|status|stop")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print_help()
        exit(0)
    elif sys.argv[1] == 'start':
        start_daemon()
    elif sys.argv[1] == 'status':
        pass
    elif sys.argv[1] == 'stop':
        pid = open('judged.pid', 'r')
        os.kill(int(pid.read()))
    else:
        print_help()
    exit(0)
