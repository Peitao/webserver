all:
	cd net; ${MAKE}
	cd src; ${MAKE}
	cd net-demo; ${MAKE}
	cd vertical_search; ${MAKE}

clean:
	cd net; ${MAKE} clean
	cd src; ${MAKE} clean
	cd net-demo; ${MAKE} clean
	cd vertical_search; ${MAKE} clean
	
