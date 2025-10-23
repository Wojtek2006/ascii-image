CXX = g++

SRC = src
INC = inc
BIN = bin
EXE = ascii

all: $(BIN)/$(EXE)

run: clean all
	./$(BIN)/$(EXE)

$(BIN)/$(EXE): $(SRC)/*.cpp
	$(CXX) -I$(INC) $^ -o $@

clean:
	rm $(BIN)/*