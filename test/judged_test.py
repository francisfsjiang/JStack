#!/usr/bin/python3
import socket
from ctypes import *

f=open("test.c",'rb')
c=f.read()
f.close()
s=socket.socket()
s.connect(("127.0.0.1",23333))
s.send(bytes(c_uint(0)) +
        bytes(c_uint(0)) +
        bytes(c_uint(1001)) +
        bytes(c_uint(1002)) +
        c)
print(bytes(c_uint(1000)))
data=s.recv(100)
print(data)
s.close()
