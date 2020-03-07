#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <queue>
#include <unordered_map>
using namespace CHNJAR003;

#define PRINT(x) std::cout << x;

HuffmanTree::HuffmanTree()
{
    root = nullptr;
}

HuffmanTree::~HuffmanTree()
{
    root = nullptr;
}

void HuffmanTree::buildFrequencyTable(std::string inputFileName)
{
    std::ifstream ifs;
    ifs.open(inputFileName);

    if (ifs.is_open())
    {
        char tempChar;
        while (ifs.get(tempChar))
        {
            frequencyTable[tempChar] += 1; //increment the frequency of the character in the map
        }

        ifs.close();
    }
}

void HuffmanTree::compressData(std::string inputFileName, std::string outputFileName)
{
    buildFrequencyTable(inputFileName); //build the frequency table (map) of all the characters in the text file

    for (std::pair<char, int> element : frequencyTable)
    {
        char key = element.first;
        int value = element.second;

        PRINT("key=" + std::string(1, key) + " value=" + std::to_string(value) + "\n");
    }
}