CC = g++
CPPFLAGS = -g -Wall -std=c++17
DEPS =  Message.h driver.h Contact.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CPPFLAGS)

app: driver.o  Message.o Contact.o
	$(CC) -o app driver.o  Message.o Contact.o

.PHONY: clean

clean:
	$(info -- cleaning up --)
	rm -f app
	rm -f *.o


