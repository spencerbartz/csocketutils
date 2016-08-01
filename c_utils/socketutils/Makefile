all:
	gcc -c socketutils.c -I./include
	ar -r libsocketutils.a socketutils.o

test:
	gcc socketutils_test.c -o socketutils_test -lsocketutils -L. -I. -lloggerutils -L./lib -I./include
	./socketutils_test httpclient &>test_output.txt
	rm -f socketutils_test
	rm -f *.o
	diff correct_test_output.txt test_output.txt	

package:
	mkdir include
	mkdir lib
	cp libsocketutils.a lib/
	cp socketutils.h include/
	tar -czf socketutils.tar.gz lib/ include/
	rm -rf include
	rm -rf lib

clean:
	rm -f *.o
	rm -f socketutils_test
	rm -f test_output.txt

cleanlib:
	rm -f libsocketutils.a

