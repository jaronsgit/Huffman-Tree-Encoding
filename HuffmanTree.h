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
    std::unordered_map<char, int> frequencyTable; //Map of the characters and their associated frequencies

    void buildFrequencyTable(std::string inputFileName);

public:
    HuffmanTree();
    ~HuffmanTree();

    void buildHuffmanTree(std::unordered_map<char, int> ft); //Build the HuffmanTree representation from map of frequencies
    void compressData(std::string inputFileName, std::string outputFileName);
};

} // namespace CHNJAR003

#endif
