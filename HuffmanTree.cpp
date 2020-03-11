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
    ifs.open((inputFileName + ".txt").c_str());

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

void HuffmanTree::fillPriorityQueue(std::unordered_map<char, int> ft)
{
    for (std::pair<char, int> element : ft)
    {
        char keyChar = element.first;
        int valueFreq = element.second;

        //PRINT("key=" + std::string(1, keyChar) + " value=" + std::to_string(valueFreq) + "\n");

        /*
        HuffmanNode tempNode;
        std::shared_ptr<HuffmanNode> tempPtr = std::make_shared<HuffmanNode>(tempNode);
        tempPtr->setCharacter(keyChar);
        tempPtr->setFrequency(valueFreq);

        nodeQueue.push(*tempPtr);
        */

        HuffmanNode tempNode = HuffmanNode();
        tempNode.setCharacter(keyChar);
        tempNode.setFrequency(valueFreq);
        nodeQueue.push(tempNode);

        //PRINT("tempNode char=" + std::string(1, tempPtr->getCharacter()) + "\n");
    }
}

void HuffmanTree::buildHuffmanTree(std::unordered_map<char, int> ft)
{
    fillPriorityQueue(ft);

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

    PRINT("root frequency=" + std::to_string(root->getFrequency()) + "\n");

    buildCodeTable(root.get(), ""); //Build the code table from the tree
}

void HuffmanTree::buildCodeTable(HuffmanNode *node, std::string binaryCode)
{

    if (node->getLeftChild())
    { //has left child
        buildCodeTable(node->getLeftChild(), binaryCode += "0");
    }

    if (node->getRightChild())
    { //has right child
        buildCodeTable(node->getRightChild(), binaryCode += "1");
    }

    if (!node->getLeftChild() && !node->getRightChild())
    { //if it is a leaf node
        codeTable[node->getCharacter()] = binaryCode;
        PRINT("code for " + std::string(1, node->getCharacter()) + "=" + binaryCode + "\n");
    }
}

void HuffmanTree::compressData(std::string inputFileName, std::string outputFileName)
{
    buildFrequencyTable(inputFileName); //build the frequency table (map) of all the characters in the text file
    buildHuffmanTree(frequencyTable);

    //Now compress the ASCII text file and write it out

    int numCharsInFile = 0;
    int numBitsInFile = 0;

    std::ofstream outputFile;
    outputFile.open((outputFileName + ".txt").c_str());

    std::ifstream inputFile;
    inputFile.open((inputFileName + ".txt").c_str());

    if (inputFile.is_open())
    {
        char tempChar;
        while (inputFile.get(tempChar))
        {
            numCharsInFile++;                            //increment the number of characters read from the file
            std::string bitString = codeTable[tempChar]; //convert the character to its corresponding string binary code
            numBitsInFile += bitString.length();         //record the number of individual "bits"
            outputFile << bitString;                     //write the bitstring to the output textfile

            //PRINT(bitString + "\n");
        }
        inputFile.close();
        outputFile.close();
    }

    outputFile.open((outputFileName + ".hdr").c_str());

    if (outputFile.is_open())
    {
        //PRINT("About to write out the code table.\n");

        for (std::pair<char, std::string> element : codeTable)
        {
            char keyChar = element.first;
            std::string valueBitString = element.second;
            //PRINT(std::string(1, keyChar) + ":" + valueBitString + "\n");
            outputFile << keyChar << ":" << valueBitString << std::endl;
        }

        outputFile.close();
        int actualFileSize = (numBitsInFile / 8) + (numBitsInFile % 8 ? 1 : 0);
        PRINT("Actual file size supposed to be: " + std::to_string(actualFileSize) + " bytes\n");
    }
    else
    {
        PRINT("Could not open file.");
    }
}

std::unordered_map<char, int> HuffmanTree::getFrequencyTable() const
{
    return frequencyTable;
}
std::unordered_map<char, std::string> HuffmanTree::getCodeTable() const
{
    return codeTable;
}
std::priority_queue<HuffmanNode> HuffmanTree::getNodeQueue() const
{
    return nodeQueue;
}