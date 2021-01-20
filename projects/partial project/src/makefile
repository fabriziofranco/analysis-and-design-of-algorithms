all: main

main: main.cpp
	g++ -std=c++2a main.cpp
	./a.out

debug: main.cpp
	g++ -std=c++2a -g main.cpp
	./a.out

clean:
	rm -f a.out main