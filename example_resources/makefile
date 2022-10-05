.PHONY: prepare
prepare:
	-mkdir out

%.vertex.o: %.vert
	xxd -a -i $^ > $^ex.c
	gcc -c $^ex.c -o $@
	mv $@ out

%.fragment.o: %.frag
	xxd -a -i $^ > $^ment.c
	gcc -c $^ment.c -o $@
	mv $@ out

clean-working-dir:
	-rm *.c

clean-build:
	rm -rf out