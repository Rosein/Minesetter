GPP = g++
TARGET = run_tests

$(TARGET) : uts/sut.cpp obj/GameTest.o obj/Game.o
	$(GPP) uts/sut.cpp obj/GameTest.o obj/Game.o -o build/$(TARGET) -lgtest

obj/GameTest.o : uts/GameTest.cpp inc/Game.hpp
	$(GPP) uts/GameTest.cpp -c -o obj/GameTest.o

obj/Game.o : src/Game.cpp inc/Game.hpp
	$(GPP) src/Game.cpp -c -o obj/Game.o
clean:
	rm obj/*  build/*
run:

	./build/run_tests