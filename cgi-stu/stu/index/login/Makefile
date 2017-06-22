CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS=selsss.cgi seltea.cgi 

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
	cp *.cgi /usr/lib/cgi-bin/sx/
