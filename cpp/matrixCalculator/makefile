EXE = matrixCalculator

INC_DIR = include
SRC_DIR = src
OBJ_DIR = objects

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


# CXX is the compiler to be used ensure that it is the same compiler that the BOOST
# library being used was compiled with else it leads to, segmentation fault: 11, when
# running the unitTests executable. If gcc then g++ version > version 4.8.
# If clang then clang++ 
# 
# The "-I" flag adds a search path for the compiler to search for files from.
# "$(CURDIR)" is a predefined variable that evaluates to the file path of the makefile.
CXX = g++
CXXFLAGS = -I$(CURDIR) -Wall -std=c++11


all: $(EXE)

# Link object files together to form the executable.
$(EXE) : $(OBJ_DIR) $(OBJ)
	$(CXX) $(OBJ) -o $@
	
# Unit testing target.
# unitTests: $(OBJ_DIR) test/testMatrixCalculator.o
#  	$(CXX) test/testMatrixCalculator.o -L/usr/local/Cellar/boost/1.61.0_1/lib -lboost_unit_test_framework-mt -o $@

# Check that the objects directory exists and if not create the directory.	
$(OBJ_DIR): 
	if [ ! -d "$(OBJ_DIR)" ]; then mkdir $(OBJ_DIR); fi

#compile the source code files into object files.
$(OBJ_DIR)/main.o : $(SRC_DIR)/main.cpp $(INC_DIR)/D_Base_Matrix.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
# test/testMatrixCalculator.o : test/testmatrixCalculator.cpp $(INC_DIR)/D_Base_Matrix.h
#	$(CXX) $(CXXFLAGS) -I/usr/local/Cellar/boost/1.61.0_1/include -c $< -o $@


.PHONY : clean
clean : 
	$(RM) $(OBJ)
	$(RM) $(EXE)
#	rm test/testMatrixCalculator.o
#	rm unitTests
	rmdir $(OBJ_DIR)
