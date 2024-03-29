#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <memory>
#include <queue>
#include <unordered_map>
#include "HuffmanNode.h"

namespace CHNJAR003
{

class HuffmanTree
{
private:
    std::shared_ptr<HuffmanNode> root;
    std::priority_queue<HuffmanNode> nodeQueue;
    std::unordered_map<char, int> frequencyTable;    //Map of the characters and their associated frequencies
    std::unordered_map<char, std::string> codeTable; //Map of the characters and their associated binary codes
public:
    HuffmanTree();                                  //default constructor
    ~HuffmanTree();                                 //destructor
    HuffmanTree(const HuffmanTree &rhs);            //copy constructor
    HuffmanTree(HuffmanTree &&rhs);                 //move constructor
    HuffmanTree &operator=(const HuffmanTree &rhs); //copy assignment operator
    HuffmanTree &operator=(HuffmanTree &&rhs);      //move assignment operator
    void buildFrequencyTable(std::string inputFileName);
    void fillPriorityQueue(std::unordered_map<char, int> ft);
    void buildHuffmanTree(std::unordered_map<char, int> ft);        //Build the HuffmanTree representation from map of frequencies
    void buildCodeTable(HuffmanNode *node, std::string binaryCode); //Recurse down tree and build table of characters and their binary codes
    std::string encodeData(std::string inputFileName);
    std::string decodeData(std::unordered_map<std::string, char> decode_code_table, std::string encodedString);
    void compressData(std::string inputFileName, std::string outputFileName);
    void compressToBitStream(std::string inputFileName, std::string outputFileName);
    void decompressFromBitStream(std::string binFileName, std::string codeTableFile);

    std::unordered_map<char, int> getFrequencyTable() const;
    std::unordered_map<char, std::string> getCodeTable() const;
    std::priority_queue<HuffmanNode> getNodeQueue() const;

    HuffmanNode *getRootNode() const;
};

} // namespace CHNJAR003

#endif
