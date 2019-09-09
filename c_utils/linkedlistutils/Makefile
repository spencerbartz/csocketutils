all:
	gcc -c linkedlist.c 
	ar -r liblinkedlist.a linkedlist.o

test:
	gcc loggerutils_test.c -o loggerutils_test -lloggerutils -L. -I.
	./loggerutils_test &>test_output.txt
	rm -f loggerutils_test
	rm -f *.o
	diff correct_test_output.txt test_output.txt
	

package:
	mkdir include
	mkdir lib
	cp libloggerutils.a lib/
	cp loggerutils.h include/
	tar -czf loggerutils.tar.gz lib/ include/
	rm -rf include
	rm -rf lib

clean:
	rm -f *.o
	rm -f loggerutils_test
	rm -f test_output.txt

cleanlib:
	rm -f libloggerutils.a

