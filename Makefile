CC=g++
LIBS=-lm

huffencode: driver.o HuffmanTree.o HuffmanNode.o
	$(CC) driver.o HuffmanTree.o HuffmanNode.o -o huffencode -std=c++11 $(LIBS)


%.o : %.cpp   
	$(CC) -c $< -o $@ -std=c++11
   

# deletes all the object code files as well as the previously generated outputs
clean:
	@rm -f *.o
	@rm huffencode
	
run:
	./huffencode testinput.txt testoutput.txt