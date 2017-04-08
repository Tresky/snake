# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -pedantic -Wall

# Relative directories
ODIR = obj

# Libraries to link to
LIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
INCS = -I/usr/local/include


#### OBJECT FILES ####
_ENG_OBJ = snake_game.o video.o snake.o
ENG_OBJ = $(patsubst %, $(ODIR)/%, $(_ENG_OBJ))

#### DEPENDENCY HEADER FILES ####
_ENG_DEP = snake_game.hpp video.hpp snake.hpp
ENG_DEP = $(patsubst %, ./src/game/%, $(_ENG_DEP))

#### RULES ####
# Links object files and libraries into executable
snake: $(ENG_OBJ) obj/main.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) $(INCS)

# Compiles engine from /src/game/*
$(ODIR)/%.o: ./src/game/%.cpp $(ENG_DEP)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

# Compiles the main.cpp file and places the object
# file in the obj/ directory.
$(ODIR)/main.o: ./src/main.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

#### CLEANUP ####
# Ensures that the clean 'rule' isn't mistaken for
# a file name. If a file called 'clean' were made and
# this line wasn't present, the 'clean' file would not
# compile because it has no prerequisites and would be
# considered up-to-date all the time.
#
# NOTE: Rules only activate if the dependant files
# (right side of colon) have changed since the last time
# the make was run.
.PHONY: clean

# Ran independantly.
# Deletes all object files and the executable.
clean:
	rm -f $(ODIR)/*.o #*~ core ./src/*~
	rm -f snake
