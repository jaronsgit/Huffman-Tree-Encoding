#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "HuffmanTree.h"
#include "HuffmanNode.h"

using namespace CHNJAR003;

//frequency counting
//tree construction
//code table construction (tree traversal)
//encoding
//etc.
//bit packing and unpacking test cases as well

TEST_CASE("COMPRESSION ALGORITHM TESTING")
{
    HuffmanTree hufftree = HuffmanTree();

    typedef std::unordered_map<char, int> freq_map_t;
    typedef std::unordered_map<char, std::string> code_map_t;
    typedef std::priority_queue<HuffmanNode> node_queue_t;

    freq_map_t tempFreqMap;
    code_map_t tempCodeMap;
    node_queue_t tempNodeQueue;

    SECTION("buildFrequencyTable() Tests")
    {
        hufftree.buildFrequencyTable("testingFiles/testinput");
        tempFreqMap = hufftree.getFrequencyTable();

        SECTION("Frequency table size is correct.")
        {
            REQUIRE(tempFreqMap.size() == 8);
        }

        SECTION("Characters are present in table with correct frequencies.")
        {
            REQUIRE(tempFreqMap['g'] == 3);
            REQUIRE(tempFreqMap['o'] == 3);
            REQUIRE(tempFreqMap[' '] == 2);
            REQUIRE(tempFreqMap['e'] == 1);
            REQUIRE(tempFreqMap['s'] == 1);
            REQUIRE(tempFreqMap['h'] == 1);
            REQUIRE(tempFreqMap['p'] == 1);
            REQUIRE(tempFreqMap['r'] == 1);
        }
    }

    SECTION("fillPriorityQueue() Tests")
    {
        hufftree.fillPriorityQueue(tempFreqMap);
        tempNodeQueue = hufftree.getNodeQueue();

        SECTION("Priority queue size is correct - matches frequency map size.")
        {
            REQUIRE(tempNodeQueue.size() == tempFreqMap.size());
        }
    }

    SECTION("buildHuffmanTree() Tests")
    {
        hufftree.buildFrequencyTable("testingFiles/testinput");
        tempFreqMap = hufftree.getFrequencyTable();
        hufftree.buildHuffmanTree(tempFreqMap);

        //std::cout << "tempFreqMap size: " << tempFreqMap.size();

        int rootFreq = hufftree.getRootNode()->getFrequency();

        int totChars = 0;

        for (const auto &element : tempFreqMap)
        {
            totChars += element.second; //Accumulate total number of characters in the file
        }

        REQUIRE(rootFreq == totChars);
    }

    SECTION("buildCodeTable() Tests")
    {
        hufftree.buildFrequencyTable("testingFiles/testinput");
        tempFreqMap = hufftree.getFrequencyTable();
        hufftree.buildHuffmanTree(tempFreqMap);

        hufftree.buildCodeTable(hufftree.getRootNode(), ""); //Build the code table from the tree

        tempCodeMap = hufftree.getCodeTable();

        REQUIRE(tempCodeMap['g'].length() == 2);
        REQUIRE(tempCodeMap['o'].length() == 2);
        REQUIRE(tempCodeMap['p'].length() == 4);
        REQUIRE(tempCodeMap['r'].length() == 4);
        REQUIRE(tempCodeMap['s'].length() == 4);
    }
}