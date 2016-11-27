all: test

SRCS = block_file.cpp IO.cpp MergeSort.cpp processing.cpp b+tree.cpp  Medrank.cpp  RandomOfGaussianDistribution.cpp L2NN.cpp OverallRatio.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

CC = g++ -std=c++11
OPTI = -Wall -o0
DEBUG = -g
INC = -I./
OBJ = -o
REMOVE = -rm -rf

CXX_FLAGS = $(CC) $(OPTI)

test: $(OBJS)
	$(CXX_FLAGS) -o medrank $(OBJS)

definition.o: definition.h

block_file.o: block_file.h

RandomOfGaussianDistribution.o: RandomOfGaussianDistribution.h

Medrank.o: Medrank.h

MergeSort.o: MergeSort.h

L2NN.o: L2NN.h

processing.o: processing.h

b+tree.o: b+tree.h

IO.o: IO.h

OverallRatio.o: OverallRatio.h

clean:
	$(REMOVE) *.o *.gch *.dat medrank
