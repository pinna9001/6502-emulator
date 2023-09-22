.PHONY: 6502
6502:
	cd ./6502/src && make

main: 6502
	gcc -o main main.c -I6502/include -L 6502/src -l 6502

tests:
	cd ./6502/tests && bash run_tests.sh
	rm -f ./6502/tests/*.o
	rm -f ./6502/tests/*.exe

.PHONY: clean
clean:
	rm -rf *.exe
	rm -rf *.o
	rm -rf *.a
	rm -rf 6502/src/*.exe
	rm -rf 6502/src/*.o
	rm -rf 6502/src/*.a