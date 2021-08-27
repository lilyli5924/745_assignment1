INCLUDE = /usr/local/include
LIB = /usr/local/lib
CC = g++
CFLAGS = -I$(INCLUDE) -L$(LIB) -c
LDFLAGS = -Wall -lm  -lc
SOURCES = create_graph.c spanning_tree.c main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = spanning_tree

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE) *~
