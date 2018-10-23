MODULE = netlink_main

#CC=gcc
#CXX=g++
CC = arm-linux-gnueabihf-gcc
CXX = arm-linux-gnueabihf-g++

RM=rm -f
CFLAGS = -g -Wall
CPPFLAGS=-g -Wall
LDFLAGS= 


SRCS = netlink_main.c

OBJS=$(subst .c,.o,$(SRCS))


LIBS = -lnl-3 -lnl-genl-3
#LIBS = -lvnc
INCPATH+=-I. -I/home/yuali/projects/yuanli/study/C/NetLinkTest/lib/include/libnl3 -L/home/yuali/projects/yuanli/study/C/NetLinkTest/lib/lib

all: $(MODULE)

# %.o:%.cc
# 	$(CXX) $(INCPATH) $(CPPFLAGS) -c -o $@ $<

# %.o:%.c
# 	$(CC) $(INCPATH) $(CPPFLAGS) -c -o $@ $<

$(MODULE): $(SRCS)
	$(CC) $(CFLAGS)  $^ -o $(MODULE) $(INCPATH) $(LIBS)
	mkdir -p bin
	cp $(MODULE) ./bin
	tar -zcvf netlink_main.tar.gz  ./bin
	scp netlink_main root@172.24.176.221:/data/netlink/


clean:
	$(RM) $(OBJS)
	$(RM) $(MODULE)
	$(RM) -rf bin
	rm *.gz


.PHONY: clean
