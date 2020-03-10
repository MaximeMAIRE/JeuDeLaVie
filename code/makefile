CSOURCE = $(wildcard src/*.c)
CHEADER = $(wildcard include/*.h)
COBJ = $(patsubst src/%.c, obj/%.o, $(CSOURCE))

vpath %.o obj
vpath %.h include
vpath %.c src


bin/main : $(COBJ)
	gcc -g -Wall -o $@ $^


obj/%.o : %.c $(CHEADER)
	gcc -g -Wall -o $@ -c $< -I include


clean:
	rm obj/*
	rm bin/main

doc:
	doxygen Doxyfile

dist:
	tar -zcvf MaximeMaire_GoL_3.tar.gz bin/ obj/ src/ include/ ./Doxyfile makefile