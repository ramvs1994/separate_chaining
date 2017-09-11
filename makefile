CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c hash_func.c insert_packet.c lookup_packet.c delete.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mainexe

all: $(SOURCES) $(EXECUTABLE)
	    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
