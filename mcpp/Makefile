all: demo-fifo

CFLAGS = -Wall -std=c99

%.h: %.mc.h mcpp.m4 m5.m4
	m4 -I. -P mcpp.m4 "$<" >$@

%.c: %.mc.c mcpp.m4 m5.m4 %.mc.h

	m4 -I. -P mcpp.m4 "$<" >$@

float_fifo.c int_fifo.c: fifo.G.c fifo.G.h
float_fifo.h int_fifo.h: fifo.G.h

float_fifo.o: float_fifo.c float_fifo.h
int_fifo.o: int_fifo.c int_fifo.h
demo-fifo.o:  demo-fifo.c float_fifo.h int_fifo.h
demo-fifo:    demo-fifo.o float_fifo.o int_fifo.o

clean:
	rm -f demo-fifo fifo *.o float_fifo.[ch] *~ int_fifo.[ch]


