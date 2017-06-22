CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= addtc.cgi deltc.cgi  seltc.cgi  

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi
install:
	cp *.cgi /usr/lib/cgi-bin/sx/
