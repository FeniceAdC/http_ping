# Project: multiple http_ping

CFLAGS=-Wall -O2 -Werror

all: master
	
master:  master.o main.o http_ping.o
	cc $(CFLAGS) http_ping.o master.o main.o -o master
	
main.o: main.c master.h http_ping.h
	cc $(CFLAGS) -c main.c
	
master.o:   master.c master.h 
	cc $(CFLAGS) -c master.c

http_ping.o:   http_ping.c http_ping.h  master.h 
	cc $(CFLAGS) -c http_ping.c