INCLUDE_PATH = ../include
LIB_PATH = ../src

6502:
	cd ../src && make

run_%_test: %_test
	./$<

%_test: %_test.o 6502
	gcc -o  $@ $< -L$(LIB_PATH) -l6502

%_test.o: %_test.c
	gcc -c -o $@ $< -I$(INCLUDE_PATH)