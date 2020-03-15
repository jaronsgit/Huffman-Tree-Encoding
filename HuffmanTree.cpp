#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <queue>
#include <bitset>
#include <string>
#include <cstring>
#include <sstream>
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

//performs shallow copy construction using rhs HuffmanTree
HuffmanTree::HuffmanTree(const HuffmanTree &rhs) : root(rhs.root)
{
}
//move copy constructor
HuffmanTree::HuffmanTree(HuffmanTree &&rhs) : root(std::move(rhs.root))
{
    rhs.root = nullptr;
}
//copy assignment operator
HuffmanTree &HuffmanTree::operator=(const HuffmanTree &rhs)
{
    if (this != &rhs)
    {
        root = rhs.root;
    }
    return *this;
}
//move assignment operator
HuffmanTree &HuffmanTree::operator=(HuffmanTree &&rhs)
{
    if (this != &rhs)
    {
        root = std::move(rhs.root);
        rhs.root = nullptr;
    }
    return *this;
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

    /*std::cout << "FT:" << std::endl;
    for (auto const &element : frequencyTable)
    {
        std::cout << (int)element.first << ":" << element.second << std::endl;
    }*/
}

void HuffmanTree::fillPriorityQueue(std::unordered_map<char, int> ft)
{

    for (std::pair<char, int> element : ft)
    {
        char keyChar = element.first;
        int valueFreq = element.second;

        //PRINT("key=" + std::string(1, keyChar) + " value=" + std::to_string(valueFreq) + "\n");

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

        HuffmanNode newTempNode = HuffmanNode();

        int sumFrequency = 0;

        HuffmanNode temp = nodeQueue.top(); //temporarily store the top element
        sumFrequency += temp.getFrequency();
        newTempNode.setLeftChild(temp);
        nodeQueue.pop();

        temp = nodeQueue.top(); //temporarily store the top element
        sumFrequency += temp.getFrequency();
        newTempNode.setRightChild(temp);
        nodeQueue.pop();

        newTempNode.setFrequency(sumFrequency);

        nodeQueue.push(newTempNode);
    }

    root = std::make_shared<HuffmanNode>(nodeQueue.top());
    nodeQueue.pop();

    //PRINT("root frequency=" + std::to_string(root->getFrequency()) + "\n");
}

void HuffmanTree::buildCodeTable(HuffmanNode *node, std::string binaryCode)
{

    if ((node->getLeftChild() == nullptr) && (node->getRightChild() == nullptr))
    { //Is at a leaf node
        codeTable[node->getCharacter()] = binaryCode;

        return;
    }
    else
    {
        std::string leftCode = binaryCode + "0";
        std::string rightCode = binaryCode + "1";
        buildCodeTable(node->getLeftChild(), leftCode);
        buildCodeTable(node->getRightChild(), rightCode);
    }
}

void HuffmanTree::compressData(std::string inputFileName, std::string outputFileName)
{
    PRINT("Running compressData()\n");
    buildFrequencyTable(inputFileName); //build the frequency table (map) of all the characters in the text file
    buildHuffmanTree(frequencyTable);
    buildCodeTable(root.get(), ""); //Build the code table from the tree

    //Now compress the ASCII text file and write it out

    std::string encodedString = encodeData(inputFileName);

    std::ofstream outputFile;
    outputFile.open((outputFileName + ".txt").c_str());

    if (outputFile.is_open())
    {
        outputFile << encodedString;
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
            outputFile << (int)keyChar << ":" << valueBitString << std::endl;
        }

        outputFile.close();
        //int actualFileSize = (numBitsInFile / 8) + (numBitsInFile % 8 ? 1 : 0);
        //PRINT("Actual file size supposed to be: " + std::to_string(actualFileSize) + " bytes\n");
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

HuffmanNode *HuffmanTree::getRootNode() const
{
    return root.get();
}

std::string HuffmanTree::encodeData(std::string inputFileName)
{
    PRINT("Running encodeData()\n");
    int numCharsInFile = 0;
    int numBitsInFile = 0;

    std::string encodedString = "";

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
            encodedString += bitString;                  //add the bitstring for the character to the full string
            //PRINT(bitString + "\n");
        }
        inputFile.close();
    }

    //int actualFileSize = (numBitsInFile / 8) + (numBitsInFile % 8 ? 1 : 0);
    //PRINT("Actual file size supposed to be: " + std::to_string(actualFileSize) + " bytes\n");

    return encodedString;
}

void HuffmanTree::compressToBitStream(std::string inputFileName, std::string outputFileName)
{
    PRINT("Running compressToBitStream()\n");
    buildFrequencyTable(inputFileName); //build the frequency table (map) of all the characters in the text file
    buildHuffmanTree(frequencyTable);
    buildCodeTable(root.get(), ""); //Build the code table from the tree
    std::string encodedString = encodeData(inputFileName);

    int processedBitsCount = 0;

    std::ofstream binaryFile;
    binaryFile.open((outputFileName + ".bin").c_str(), std::ios::binary | std::ios::out);

    if (binaryFile.is_open())
    {

        int numBits = encodedString.length();
        char endlChar = '\n';
        binaryFile.write(reinterpret_cast<const char *>(&numBits), sizeof(numBits));
        binaryFile.write(&endlChar, 1);

        while (processedBitsCount < encodedString.length())
        {
            std::string subBits = encodedString.substr(processedBitsCount, 8);
            processedBitsCount += 8;
            //std::bitset<8> tempBitset(subBits);
            std::bitset<8> tempBitset;

            for (int i = 0; i < subBits.length(); i++)
            {
                if (subBits[i] == '1')
                {
                    tempBitset[7 - i] = 1;
                }
            }

            char tempChar = tempBitset.to_ulong();
            //PRINT("writing to binary file: " + tempBitset.to_string() + "\n");
            binaryFile.write((char *)&tempChar, 1);
        }
        binaryFile.close();
    }
    else
    {
        PRINT("Could not open the binary file to write compressed file.\n");
    }

    std::ofstream outputFile;
    outputFile.open((outputFileName + ".hdr").c_str());

    if (outputFile.is_open())
    {
        //PRINT("About to write out the code table.\n");

        for (std::pair<char, std::string> element : codeTable)
        {
            char keyChar = element.first;
            std::string valueBitString = element.second;
            //PRINT(std::string(1, keyChar) + ":" + valueBitString + "\n");
            outputFile << (int)keyChar << ":" << valueBitString << std::endl;
        }

        outputFile.close();
        //int actualFileSize = (numBitsInFile / 8) + (numBitsInFile % 8 ? 1 : 0);
        //PRINT("Actual file size supposed to be: " + std::to_string(actualFileSize) + " bytes\n");
    }
    else
    {
        PRINT("Could not open file.");
    }

    //char test = std::stoi("101", nullptr, 2);
}

void HuffmanTree::decompressFromBitStream(std::string binFileName, std::string codeTableFile)
{
    std::unordered_map<std::string, char> decode_code_table;
    std::ifstream inputCodeFile;
    inputCodeFile.open((codeTableFile + ".hdr").c_str());

    if (inputCodeFile.is_open())
    {

        std::string line;
        std::string token;
        std::vector<std::string> tokens;

        getline(inputCodeFile, line);
        while (!inputCodeFile.eof())
        {
            std::istringstream iss(line);
            while (getline(iss, token, ':'))
            {
                tokens.push_back(token);
            }
            getline(inputCodeFile, line);
        }
        //PRINT("About to print decompress map:\n")
        //insert the codes from the header file into the code table/map
        for (int i = 0; i < tokens.size(); i += 2)
        {

            decode_code_table[tokens[i + 1]] = (char)std::stoi(tokens[i]);
        }

        /*for (const auto &element : decode_code_table)
        {
            PRINT(element.first + ":" + std::string(1, element.second) + "\n");
        }*/

        inputCodeFile.close();
    }
    else
    {
        PRINT("Could not open the code table header file in order to read compressed file.\n");
    }

    std::ifstream inputBinaryFile;

    inputBinaryFile.open((binFileName + ".bin").c_str(), std::ios::in | std::ios::binary);

    if (inputBinaryFile.is_open())
    {

        int totNumBits;
        char tempChar;
        inputBinaryFile.read(reinterpret_cast<char *>(&totNumBits), sizeof(int)); // read in the total number of bits
        inputBinaryFile.read(&tempChar, 1);

        int totNumBytes = totNumBits / 8 + (totNumBits % 8 ? 1 : 0);
        //std::bitset<8> *bitsetByteArray = new std::bitset<8>[totNumBytes];

        std::string encodedString = "";
        std::string tempBit = "";
        std::bitset<8> tempBitsetByte;

        int bitcount = 0;
        for (int byteIndex = 0; byteIndex < totNumBytes; byteIndex++)
        {
            inputBinaryFile.read((char *)&tempBitsetByte, 1);
            //PRINT("reading from binary file: " + tempBitsetByte.to_string() + "\n");
            for (int i = 7; i > -1; i--)
            {
                tempBit = (tempBitsetByte[i] == 1 ? '1' : '0');
                if (bitcount < totNumBits)
                {
                    encodedString += tempBit;
                    bitcount++;
                }
            }
        }

        //PRINT("Encoded string: " + encodedString + "\n");

        std::string decodedString = decodeData(decode_code_table, encodedString);
        //PRINT("Decoded string: " + decodedString + "\n");
        inputBinaryFile.close();

        std::ofstream decompressedFile;
        decompressedFile.open((binFileName + "_decompressed.txt").c_str());

        //write it out to file
        if (decompressedFile.is_open())
        {
            decompressedFile << decodedString;
            decompressedFile.close();
        }
    }
    else
    {
        PRINT("Could not open the binary file to read compressed file.\n");
    }
}

std::string HuffmanTree::decodeData(std::unordered_map<std::string, char> decode_code_table, std::string encodedString)
{
    std::string tempCode = "";
    std::string decodedString = "";

    for (int i = 0; i < encodedString.length(); i++)
    {
        tempCode += encodedString[i];

        if (decode_code_table.count(tempCode) > 0)
        {
            decodedString += decode_code_table[tempCode];
            tempCode = "";
        }
    }
    return decodedString;
}