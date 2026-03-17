CFLAGS := -O2

.PHONY: clean all

all: random-ff embed-ff extract-ff

random-ff: random-ff.o util.o
	$(CC) $(CFLAGS) -o $@ $^

embed-ff: embed-ff.o util.o
	$(CC) $(CFLAGS) -o $@ $^

extract-ff: extract-ff.o util.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	git clean -fx
