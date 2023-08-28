output: main.o constructor.o opcodes.o ROM-Loader.o
	g++ main.o constructor.o opcodes.o ROM-Loader.o -o output -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp CHIP-8.hpp
	g++ -c  main.cpp 
constructor.o : constructor.cpp CHIP-8.hpp
	g++ -c constructor.cpp
opcodes.o : opcodes.cpp CHIP-8.hpp
	g++ -c opcodes.cpp
ROM-Loader.o : ROM-Loader.cpp CHIP-8.hpp
	g++ -c ROM-Loader.cpp
clean:
	rm *.o
