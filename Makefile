CC=g++
LIBS=-lm

huffencode: driver.o HuffmanTree.o HuffmanNode.o
	$(CC) driver.o HuffmanTree.o HuffmanNode.o -o huffencode -std=c++11 $(LIBS)

%.o : %.cpp   
	$(CC) -c $< -o $@ -std=c++11

unitTests: unitTests.o HuffmanTree.o HuffmanNode.o
	$(CC) unitTests.o HuffmanTree.o HuffmanNode.o -o unitTests -std=c++11 $(LIBS)

all:
	make
	make unitTests
   
# deletes all the object code files as well as the previously generated outputs
clean:
	@rm -f *.o
	@rm huffencode
	@rm unitTests
	
run:
	./huffencode testinput testoutput

run-tests:
	./unitTests