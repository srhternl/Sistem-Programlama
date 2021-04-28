# Yorum satırı - Bu bir makefile.

all: proje

OBJ = proje.o fields.o

proje: proje.o fields.o
	$(CC) $(OBJ) -o $@
#	gcc proje.o fields.o

proje.o: proje.c
	$(CC) -c $<
#	gcc -c proje.c

fields.o: fields.c fields.h
	$(CC) -c $<

clean:
	rm *.o

vclean:
	rm -rf *.o
	rm proje