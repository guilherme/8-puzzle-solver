TARGET = main

SRC = Table.cpp main.cpp
OBJ = $(patsubst %.cpp,%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	g++ -g -Wall $(OBJ) -o $(TARGET)

%.o: %.cpp
	g++ -g -Wall -c $< -o $@

