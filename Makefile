CC       = cc
CFLAGS   = -pipe -std=c99 -O2 -g -Wall -Wextra
LDFLAGS  = -lwiringPi

all: beatbutton

beatbutton: beatbutton.o
	$(CC) $(LDFLAGS) -o $@ $^

beatbutton.o: beatbutton.c config.h
	$(CC) $(CFLAGS) -c -o $@ $<

install: all
	cp -f beatbutton /usr/local/bin/beatbutton
	cp -f beatbutton.sh /etc/init.d/beatbutton
	update-rc.d beatbutton defaults

uninstall:
	-invoke-rc.d beatbutton stop
	-update-rc.d beatbutton remove
	rm -f /etc/init.d/beatbutton
	rm -f /usr/local/bin/beatbutton

clean:
	rm -f beatbutton
	rm -f *.o
