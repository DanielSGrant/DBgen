# Names of all required programs,
EXECUTABLE_NAME = Database_Maker
SOURCE_NAME1 = Database_Maker
SOURCE_NAME2 = 
SOURCE_NAME3 =
SOURCE_NAME3 =

# Compiler information
CXX=g++
CXX_VERSION= -std=c++11
CXX_FLAGS= $(CXX_VERSION) -Wall -fmax-errors=8 -O3
FILE_PATH= ./

# Default goal, used for local compilation
.DEFAULT_GOAL := compileAll

# compilation targets
compile1:
	$(CXX) $(CXX_FLAGS) -c $(SOURCE_NAME1).cc 

compile2:
	$(CXX) $(CXX_FLAGS) -o $(FILE_PATH)$(EXECUTABLE_NAME) $(SOURCE_NAME1).o 

compile3:

clean:
	rm -f *.o *~ *% *# .#*
clean-all: clean
	rm -f $(EXECUTABLE_NAME)

compileAll: compile1 compile2 compile3 clean
