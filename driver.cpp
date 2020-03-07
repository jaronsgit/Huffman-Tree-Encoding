#include <iostream>
#include <fstream>
#include <unordered_map>
#include "HuffmanTree.h"
#include "HuffmanNode.h"

#define PRINT(x) std::cout << x;

using namespace CHNJAR003;

int main(int argc, char *argv[])
{

    if (argc == 2)
    {

        std::string inputFileName = argv[0];
        std::string outputFileName = argv[1];
    }
    else
    {
        std::cerr << "Incorrect number of command line parameters provided.";
    }

    return 0;
}