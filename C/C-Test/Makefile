MODULE = test_main

CC=gcc
CXX=g++
#CC = arm-linux-gnueabihf-gcc
#CXX = arm-linux-gnueabihf-g++

RM=rm -f
CFLAGS = -g -Wall
CPPFLAGS=-g -Wall
LDFLAGS= 


SRCS = main.c

OBJS=$(subst .c,.o,$(SRCS))


LIBS = 
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
	
clean:
	$(RM) $(OBJS)
	$(RM) $(MODULE)
	$(RM) -rf bin
	rm *.gz


.PHONY: clean
