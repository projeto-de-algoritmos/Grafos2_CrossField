TARGET = CrossField
SOURCE = src
BIN = bin
INC = -I $(PWD)/headers/ #-I $(PWD)/lib/SFML-2.5.1/include/

SRC = $(wildcard $(SOURCE)/*.cpp)
OBJ = $(patsubst %,$(BIN)/%, $(notdir $(SRC:.cpp=.o)))

CC = g++
CFLAGS = $(INC) -W -Wall -std=c++14 
#SFMLFLAGS := -L lib/SFML-2.5.1/lib/ -lsfml-graphics -lsfml-window -lsfml-system
#export LD_LIBRARY_PATH=lib/SFML-2.5.1/lib/ && $(SFMLFLAGS)

$(BIN)/$(TARGET):	$(OBJ)
	$(CC) -o $@ $^ 

$(BIN)/%.o:	$(SOURCE)/%.cpp   check
	$(CC) -c $< -o $@ $(CFLAGS)

check:
	mkdir -p bin/

clean:
	rm -r bin/
	
run:	
	./$(BIN)/$(TARGET)