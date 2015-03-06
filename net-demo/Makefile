OBJS = main.o
CFLAGS += -I ../deps/libevent-2.0.21-stable/include/ -O2 --std=c++0x -I ../net/
LIB += -levent -L../deps/libevent-2.0.21-stable/lib/ -lrt -pthread -lthenet -L../net/

all: $(OBJS)
	g++ -o ../net-demo.exe $(OBJS) ${LIB} ${CFLAGS}
main.o: main.cpp
	g++ -c ${CFLAGS} main.cpp

clean:
	rm -f *.o ../net-demo.exe

