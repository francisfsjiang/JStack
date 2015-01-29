#! /usr/bin/python3

f=open("syscall_table.txt","w")
for i in range(50):
    print("        ",end='',file=f)
    for j in range(5):
        print("0,",end='',file=f)
    print("    ",end='',file=f)
    for j in range(5):
        print("0,",end='',file=f)
    print("//",i*10,file=f)

f.close()
