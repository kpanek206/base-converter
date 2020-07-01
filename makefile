objects = main.o
flags = -g -Wall -pedantic -std=c++11
system_converter: $(objects)
	g++ $(flags) -o system_converter $(objects)
main.o: main.cpp conversion_int.cpp conversion_fr.cpp
	g++ $(flags) -c main.cpp main.h conversion_int.cpp conversion_fr.cpp
clean:
	rm -rf *.o system_converter
