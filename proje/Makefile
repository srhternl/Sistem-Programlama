
all: kripto

OBJ = kripto.o fields.o jrb.o jval.o

kripto: kripto.o fields.o jrb.o jval.o
	$(CC) $(OBJ) -o $@
#	gcc kripto.o fields.o jrb.o jval.o

kripto.o: kripto.c
	$(CC) -c $<
#	gcc -c kripto.c

fields.o: ./libfdr/fields.c ./libfdr/fields.h
	$(CC) -c $<

jrb.o: ./libfdr/jrb.c ./libfdr/jrb.h
	$(CC) -c $<

jval.o: ./libfdr/jval.c ./libfdr/jval.h
	$(CC) -c $<

clean:
	rm *.o

cleanall:
	rm -rf *.o *txt kripto .kilit ornek_metin encripted decripted

run: kripto clean
	./kripto -e ornek_metin encripted
	./kripto -d encripted decripted