CC      = /usr/bin/gcc  
CFLAGS  = -Wall -shared -fPIC 
OBJ     = giac_history.so
LIBDIR  = /usr/local/lib


all:    giac_history.so

giac_history.so:    giac_history.c
	$(CC) $(CFLAGS) -o $@ $<
	strip $(OBJ)

.PHONY: clean
clean:
	rm -f $(OBJ)

.PHONY: install
install:
	install -m 0755 $(OBJ) $(LIBDIR)
    
