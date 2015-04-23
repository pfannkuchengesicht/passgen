CXX=gcc
CXX_FLAGS=-c -O3 -Wall -Wextra
CXX_LFLAGS=-lm
SOURCES=passgen.c list.c stack.c argParser.c
OBJECTS=$(SOURCES:.c=.o)

EXEC=passgen

all: $(SOURCES) $(EXEC)

clean:
	rm -f $(OBJECTS)
	rm -f $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(CXX_LFLAGS)

%.o: %.c
	$(CXX) $(CXX_FLAGS) -o $@ $<
