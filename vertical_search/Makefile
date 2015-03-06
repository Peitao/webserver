OBJS = main.o query_process.o searcher.o
CFLAGS += -I ../deps/libevent-2.0.21-stable/include/ -O2 --std=c++0x -I ../net/
LIB += -levent -L../deps/libevent-2.0.21-stable/lib/ -lrt -pthread -lthenet -L../net/

all: $(OBJS)
	g++ -o ../vc.exe $(OBJS) ${LIB} ${CFLAGS}
main.o: main.cpp
	g++ -c ${CFLAGS} main.cpp

query_process.o : query_process.cc
	g++ -c ${CFLAGS} query_process.cc
searcher.o : searcher.cc
	g++ -c ${CFLAGS} searcher.cc

clean:
	rm -f *.o ../vc.exe

