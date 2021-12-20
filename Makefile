build:
	rm -rf build && mkdir build && cd build && cmake .. && make

run:
	./build/cmd/main

format-code:
	./formatter.sh cmd && ./formatter.sh src && ./formatter.sh tests
