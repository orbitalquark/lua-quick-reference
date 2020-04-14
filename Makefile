CC = gcc
CFLAGS = -g -std=c99 -I /usr/include/lua5.3
LDFLAGS = -llua5.3

exes = ex23 ex24 ex25 ex26 ex27 ex28 ex29 ex30 ex31 ex32 ex33 ex34
all: $(exes)

ex23: ex23.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex24: ex24.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex25: ex25.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex26: ex26.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex27: ex27.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex28: ex28.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex29: ex29.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex30: ex30.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex31: ex31.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex32: ex32.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex33: ex33.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
ex34: ex34.c; $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

ex33 ex34: LDFLAGS+=-lm -ldl

clean:
	rm -f $(exes)

run: $(exes)
	for exe in $(exes); do ./$$exe; done
