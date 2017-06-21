CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= addac.cgi selac.cgi modac.cgi  delac.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
	cp *.cgi /usr/lib/cgi-bin/sx/
