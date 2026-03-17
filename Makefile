CFLAGS := -O2

.PHONY: clean all

all: random-ff embed-ff extract-ff

random-ff: random-ff.c util.c
	$(CC) $(CFLAGS) -o $@ $^

embed-ff: embed-ff.c util.c
	$(CC) $(CFLAGS) -o $@ $^

extract-ff: extract-ff.c util.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	git clean -fx
