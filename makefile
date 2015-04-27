CXX=gcc
CXX_FLAGS=-c -O3 -Wall -Wextra
CXX_LFLAGS=-lm
MANPAGES=passgen.1
GMANPAGES=$(MANPAGES:.1=.1.gz)
SOURCES=passgen.c list.c stack.c argParser.c
OBJECTS=$(SOURCES:.c=.o)

EXEC=passgen

all: $(SOURCES) $(EXEC) $(GMANPAGES)

install: all
	@echo "installing..."
	cp $(EXEC) /usr/bin/
	cp $(GMANPAGES) /usr/share/man/man1/

uninstall:
	rm -f $(patsubst %,/usr/share/man/man1/%,$(GMANPAGES))
	rm -f $(patsubst %,/usr/bin/%,$(EXEC))

%.1.gz: %.1
	gzip -k $<

clean:
	rm -f $(OBJECTS)
	rm -f $(EXEC)
	rm -f $(GMANPAGES)

$(EXEC): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(CXX_LFLAGS)

%.o: %.c
	$(CXX) $(CXX_FLAGS) -o $@ $<
