CSOURCE = $(wildcard src/*.c)
CHEADER = $(wildcard include/*.h)
COBJ = $(patsubst src/%.c, obj/%.o, $(CSOURCE))

vpath %.o obj
vpath %.h include
vpath %.c src


CPPFLAGS = -Iinclude
LDFLAGS = 
ifneq ($(MODE),Text)
	CPPFLAGS += -I/usr/include/cairo -DMODE_GRA
	LDFLAGS = -lcairo -lm -lX11
endif

bin/main : $(COBJ)
	gcc -g -Wall -o $@ $^ $(CPPFLAGS) $(LDFLAGS) 


obj/%.o : %.c $(CHEADER)
	gcc -g -Wall -o $@ -c $< $(CPPFLAGS) $(LDFLAGS) $(DFLAGS)


clean:
	rm obj/*
	rm bin/main

doc:
	doxygen Doxyfile

dist:
	tar -zcvf MaximeMaire_GoL_5.tar.gz bin/ obj/ src/ include/ ./Doxyfile makefile