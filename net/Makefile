OBJS = threadpool.o webserver.o util.o
CFLAGS += -I ../deps/libevent-2.0.21-stable/include/ -O2 --std=c++0x -I ../net/
LIB += -levent -L../deps/libevent-2.0.21-stable/lib/ -lrt -pthread

all: libthenet.a

libthenet.a: ${OBJS}
	 ar -crv -o libthenet.a ${OBJS}
webserver.o:webserver.cpp *.h
	g++ -c webserver.cpp ${CFLAGS}
threadpool.o:threadpool.cpp *.h
	g++ -c threadpool.cpp ${CFLAGS}
util.o:util.cpp *.h
	g++ -c util.cpp ${CFLAGS}
clean:
	rm -f *.o libthenet.a

