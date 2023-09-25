INCLUDE_PATH = ../include

OBJS = memory.o cpu.o

6502: $(OBJS)
	ar rcs lib6502.a $(OBJS)

%.o: %.c
	gcc -c -o $@ $< -I$(INCLUDE_PATH)