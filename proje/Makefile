
all: proje

OBJ = proje.o fields.o jrb.o jval.o

proje: proje.o fields.o jrb.o jval.o
	$(CC) $(OBJ) -o $@
#	gcc proje.o fields.o jrb.o jval.o

proje.o: proje.c
	$(CC) -c $<
#	gcc -c proje.c

fields.o: fields.c fields.h
	$(CC) -c $<

jrb.o: jrb.c jrb.h
	$(CC) -c $<

jval.o: jval.c jval.h
	$(CC) -c $<

clean:
	rm *.o proje

cleanall:
	rm -rf *.o *txt proje .kilit giris encripted decripted

run: proje clean
	./proje -e giris encripted
	./proje -d encripted decripted