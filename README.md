# C++ Assignment 3: Huffman Tree Encoding

The project includes HuffmanNode.h, HuffmanNode.cpp, HuffmanTree.h, HuffmanTree.cpp, driver.cpp, catch.hpp, unitTests.cpp as well as a Makefile.

HuffmanNode.h is the header file for the node class of the Huffman Tree.
HuffmanNode.cpp is the source file for the node clas of the Huffman Tree.
HuffmanTree.h is the header file for the tree class and all the related methods of the Huffman Compression Algorithm.
HuffmanTree.cpp is the source file for the tree class and all the related methods of the Huffman Compression Algorithm.
driver.cpp is the program that parses command line input and calls the necessary commands.
unitTests.cpp contains all the unit tests for the assignment.

## How to use the program

In order to use the program/run the executable, the text files to be compressed by the program must just be placed within the assignment directory "Assignment3_CHNJAR003" itself.

The compressed files - the compressed txt files, binary files as well as header files - will then be output into the directory "/outputFiles" within the main assignment directory.

### The structure of the command line execution is as follows:

```bash
huffencode <inputFile> <outputFile>
```

Note that the inputFile and outputFile arguments must be just the names of the .txt files without the .txt extension.

Also note that the program will output the four separate files when it is invoked:

1. <outputFile>.txt -> containing the compressed bitstream in ASCII characters
2. <outputFile>.hdr -> containing the code table of the characters and their corresponding binary representations
3. <outputFile>.bin -> the actual compressed binary file using a packed bit stream to store the data.
4. <outputFile>\_decompressed.txt -> the now decompressed file that was created using the compressed binary file and the code table .hdr header file.

All the above file will be placed into the /outputFiles directory as previously mentioned.

#### For example:

```bash
huffencode testinput testoutput
```

Navigate to the folder in Terminal and utilise the provided Makefile to compile the program source code using:

```bash
make
```

Use the following command to compile the program source code as well as the unit testing source file:

```bash
make all
```

The following command can be used to run the executable with the command line arguments:

```bash
make run
```

Use the following command to run the unit tests for the assignment:

```bash
make run-tests
```

Use the following command to remove the binary files from the project folder:

```bash
make clean
```

## Authors

**CHNJAR003**
