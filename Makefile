# //elidana@gmail.com
MAIN_EXEC = main
TEST_EXEC = test


CXX = g++
CXXFLAGS = -std=c++11 -g
FLTK_FLAGS = `fltk-config --cxxflags --ldflags --use-images`

SRC_COMMON = Game.cpp Player.cpp Role.cpp Governor.cpp Spy.cpp Baron.cpp General.cpp Judge.cpp Merchant.cpp

SRC_MAIN = main.cpp GUI.cpp
OBJ_MAIN = $(SRC_MAIN:.cpp=.o) $(SRC_COMMON:.cpp=.o)

SRC_TEST = Test.cpp
OBJ_TEST = $(SRC_TEST:.cpp=.o) $(SRC_COMMON:.cpp=.o)

all: $(MAIN_EXEC)
Main: $(MAIN_EXEC)
	./$(MAIN_EXEC)
$(MAIN_EXEC): $(OBJ_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(FLTK_FLAGS)
	

$(TEST_EXEC): $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^

Test: $(TEST_EXEC)
	./$(TEST_EXEC)

valgrind: $(MAIN_EXEC)
	valgrind --leak-check=full ./$(MAIN_EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< $(FLTK_FLAGS)

clean:
	rm -f *.o $(MAIN_EXEC) $(TEST_EXEC)
