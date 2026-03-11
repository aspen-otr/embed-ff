CFLAGS := -O2

.PHONY: clean

random-ff-img: random-ff-img.c
	$(CC) $(CFLAGS) -o $@ $<

ff-write-to-bits: ff-write-to-bits.c
	$(CC) $(CFLAGS) -o $@ $<

ff-low-bytes: ff-low-bytes.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	$(RM) ff-get-low-bytes random-ff-img ff-write-to-bits
	$(RM) *.ff
	$(RM) *.bin
	$(RM) *.png
