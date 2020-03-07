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
        char keyChar = element.first;
        int valueFreq = element.second;

        //PRINT("key=" + std::string(1, keyChar) + " value=" + std::to_string(valueFreq) + "\n");

        //HuffmanNode *temp = new HuffmanNode();
        HuffmanNode tempNode;
        std::shared_ptr<HuffmanNode> tempPtr = std::make_shared<HuffmanNode>(tempNode);
        tempPtr->setCharacter(keyChar);
        tempPtr->setFrequency(valueFreq);

        nodeQueue.push(*tempPtr);

        PRINT("tempNode char=" + std::string(1, tempPtr->getCharacter()) + "\n");
    }

    // PRINT("\n\n");

    while (nodeQueue.size() > 1)
    {

        //HuffmanNode temp = nodeQueue.top();
        //nodeQueue.pop();
        //PRINT("character=" + std::string(1, temp.getCharacter()) + " frequency=" + std::to_string(temp.getFrequency()) + "\n")

        //HuffmanNode *newTemp = new HuffmanNode();
        HuffmanNode newTempNode;
        std::shared_ptr<HuffmanNode> newTempPtr = std::make_shared<HuffmanNode>(newTempNode);

        int sumFrequency = 0;

        HuffmanNode temp = nodeQueue.top(); //temporarily store the top element
        sumFrequency += temp.getFrequency();
        newTempPtr->setLeftChild(temp);
        nodeQueue.pop();

        temp = nodeQueue.top(); //temporarily store the top element
        sumFrequency += temp.getFrequency();
        newTempPtr->setRightChild(temp);
        nodeQueue.pop();

        newTempPtr->setFrequency(sumFrequency);

        nodeQueue.push(*newTempPtr);
        PRINT("newTempNode frequency=" + std::to_string(newTempPtr->getFrequency()) + "\n");
    }

    root = std::make_shared<HuffmanNode>(nodeQueue.top());
    nodeQueue.pop();
}