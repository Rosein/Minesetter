CXX = g++
TARGET = minesweeper
TARGET_TEST = run_tests

$(TARGET) : src/main.cpp obj/Game.o
	$(CXX) src/main.cpp obj/Game.o -o build/$(TARGET) -lgtest -lpthread

obj/Game.o : src/Game.cpp inc/Game.hpp
	$(CXX) src/Game.cpp -c -o obj/Game.o

$(TARGET_TEST) : uts/sut.cpp obj/GameTest.o obj/Game.o
	$(CXX) uts/sut.cpp obj/GameTest.o obj/Game.o -o build/$(TARGET_TEST) -lgtest -lpthread

obj/GameTest.o : uts/GameTest.cpp inc/Game.hpp
	$(CXX) uts/GameTest.cpp -c -o obj/GameTest.o

obj/Game.o : src/Game.cpp inc/Game.hpp
	$(CXX) src/Game.cpp -c -o obj/Game.o
clean:
	rm obj/*  build/*

run:
	./build/minesweeper
run_tests:

	./build/run_tests