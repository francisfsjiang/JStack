import sys
while 1:
    line = sys.stdin.readline()
    if not line:
        break;
    a= line.split()
    print(int(a[0])+int(a[1]))
