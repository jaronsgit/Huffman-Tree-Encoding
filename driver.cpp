#include <iostream>
#include <fstream>
#include <unordered_map>
#include "HuffmanTree.h"
#include "HuffmanNode.h"

#define PRINT(x) std::cout << x;

using namespace CHNJAR003;

int main(int argc, char *argv[])
{

    if (argc == 3)
    {

        std::string inputFileName = argv[1];
        std::string outputFileName = argv[2];

        PRINT(inputFileName + "\n");
        PRINT(outputFileName + "\n");

        HuffmanTree hufftree = HuffmanTree();

        hufftree.compressData(inputFileName, outputFileName);
        hufftree.compressToBitStream(inputFileName, outputFileName);
        hufftree.decompressFromBitStream(outputFileName, outputFileName);
    }
    else
    {
        std::cerr << "Incorrect number of command line parameters provided.";
    }

    return 0;
}