all:
	gcc -o  Flood-It_alea *.c -lSDL

clean:
	rm -f *.o Flood-It_alea *.gch

.PHONY: all clean
