#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "HuffmanTree.h"
#include "HuffmanNode.h"
#include <memory>

using namespace CHNJAR003;

TEST_CASE("HuffmanNode Testing")
{
    std::cout << "HuffmanNode Tests" << std::endl;
    std::cout << "-----------------" << std::endl;

    SECTION("Default Constructor")
    {
        std::cout << "Default Constructor Tests:\n";
        HuffmanNode node;
        REQUIRE(node.getFrequency() == 0);
        REQUIRE(node.getCharacter() == 0);
        REQUIRE(node.getLeftChild() == nullptr);
        REQUIRE(node.getRightChild() == nullptr);
    }
    SECTION("Destructor") {}
    SECTION("setCharacter()")
    {
        std::cout << "setCharacter() Tests:\n";
        HuffmanNode temp;
        temp.setCharacter('a');
        REQUIRE(temp.getCharacter() == 'a');
    }
    SECTION("setFrequency()")
    {
        std::cout << "setFrequency() Tests:\n";
        HuffmanNode temp;
        temp.setFrequency(23);
        REQUIRE(temp.getFrequency() == 23);
    }
    SECTION("Copy Constructor")
    {
        std::cout << "Default Constructor Tests:\n";
        HuffmanNode node1;
        node1.setCharacter('a');
        node1.setFrequency(23);
        REQUIRE(node1.getCharacter() == 'a');
        REQUIRE(node1.getFrequency() == 23);
        HuffmanNode node2 = node1;
        REQUIRE(node2.getCharacter() == 'a');
        REQUIRE(node2.getFrequency() == 23);
    }
    SECTION("Move Constructor")
    {
        std::cout << "Move Constructor Tests:\n";
        HuffmanNode node1;
        node1.setCharacter('a');
        node1.setFrequency(23);
        HuffmanNode temp;
        node1.setRightChild(temp);
        REQUIRE(node1.getCharacter() == 'a');
        REQUIRE(node1.getFrequency() == 23);
        REQUIRE(node1.getRightChild() != nullptr);

        HuffmanNode node2 = std::move(node1);
        REQUIRE(node1.getCharacter() == 0);
        REQUIRE(node1.getFrequency() == -1);
        REQUIRE(node1.getLeftChild() == nullptr);
        REQUIRE(node1.getRightChild() == nullptr);
        REQUIRE(node2.getCharacter() == 'a');
        REQUIRE(node2.getFrequency() == 23);
        REQUIRE(node2.getLeftChild() == nullptr);
        REQUIRE(node2.getRightChild() != nullptr);
    }
    SECTION("Assignment Operator")
    {
        std::cout << "Assignment Operator Tests:\n";
        HuffmanNode node1;
        node1.setCharacter('a');
        node1.setFrequency(23);
        HuffmanNode temp;
        node1.setRightChild(temp);

        REQUIRE(node1.getCharacter() == 'a');
        REQUIRE(node1.getFrequency() == 23);
        REQUIRE(node1.getRightChild() != nullptr);

        HuffmanNode node2;
        node2 = node1;

        REQUIRE(node2.getCharacter() == 'a');
        REQUIRE(node2.getFrequency() == 23);
        REQUIRE(node2.getRightChild() != nullptr);

        REQUIRE(node1.getCharacter() == 'a');
        REQUIRE(node1.getFrequency() == 23);
        REQUIRE(node1.getRightChild() != nullptr);
    }
    SECTION("Move Assignment Operator")
    {
        std::cout << "Move Assignment Tests:\n";

        HuffmanNode node1;
        node1.setCharacter('a');
        node1.setFrequency(23);
        HuffmanNode temp;
        node1.setRightChild(temp);
        REQUIRE(node1.getCharacter() == 'a');
        REQUIRE(node1.getFrequency() == 23);
        REQUIRE(node1.getRightChild() != nullptr);

        HuffmanNode node2;
        node2 = std::move(node1);
        REQUIRE(node1.getCharacter() == 0);
        REQUIRE(node1.getFrequency() == -1);
        REQUIRE(node1.getLeftChild() == nullptr);
        REQUIRE(node1.getRightChild() == nullptr);
        REQUIRE(node2.getCharacter() == 'a');
        REQUIRE(node2.getFrequency() == 23);
        REQUIRE(node2.getLeftChild() == nullptr);
        REQUIRE(node2.getRightChild() != nullptr);
    }

    SECTION("setLeftChild()")
    {
        std::cout << "setLeftChild() Tests:\n";
        HuffmanNode node1;

        HuffmanNode temp;
        node1.setLeftChild(temp);
        REQUIRE(node1.getLeftChild() != nullptr);
    }
    SECTION("setRightChild")
    {
        std::cout << "setRightChild() Tests:\n";
        HuffmanNode node1;

        HuffmanNode temp;
        node1.setRightChild(temp);
        REQUIRE(node1.getRightChild() != nullptr);
    }
    SECTION("getCharacter()")
    {
        std::cout << "getCharacter() Tests:\n";
        HuffmanNode node1;
        node1.setCharacter('a');
        REQUIRE(node1.getCharacter() == 'a');
    }
    SECTION("getFrequency()")
    {
        std::cout << "getFrequency() Tests:\n";
        HuffmanNode node1;
        node1.setFrequency(10);
        REQUIRE(node1.getFrequency() == 10);
    }
    SECTION("getLeftChild()")
    {
        std::cout << "getLeftChild() Tests:\n";
        HuffmanNode node1;
        node1.setCharacter('a');
        node1.setFrequency(23);
        HuffmanNode temp;
        temp.setCharacter('b');
        node1.setLeftChild(temp);

        REQUIRE(node1.getLeftChild()->getCharacter() == 'b');
    }
    SECTION("getRightChild()")
    {
        std::cout << "getRightChild() Tests:\n";
        HuffmanNode node1;
        node1.setCharacter('a');
        node1.setFrequency(23);
        HuffmanNode temp;
        temp.setCharacter('b');
        node1.setRightChild(temp);
        REQUIRE(node1.getRightChild()->getCharacter() == 'b');
    }
}

TEST_CASE("HuffmanTree Testing")
{
    HuffmanTree hufftree = HuffmanTree();

    typedef std::unordered_map<char, int> freq_map_t;
    typedef std::unordered_map<char, std::string> code_map_t;
    typedef std::priority_queue<HuffmanNode> node_queue_t;

    freq_map_t tempFreqMap;
    code_map_t tempCodeMap;
    node_queue_t tempNodeQueue;

    SECTION("HuffmanTree Testing")
    {
        std::cout << "HuffmanTree Tests" << std::endl;
        std::cout << "-----------------" << std::endl;

        SECTION("Default Constructor")
        {
            //std::cout << "Default Constructor Tests:\n";
            HuffmanTree tree;
            REQUIRE(tree.getRootNode() == nullptr);
        }
        SECTION("Copy Constructor")
        {

            hufftree.buildFrequencyTable("testingFiles/testinput");
            tempFreqMap = hufftree.getFrequencyTable();
            hufftree.buildHuffmanTree(tempFreqMap);
            HuffmanTree treeCopy = hufftree;
            REQUIRE(hufftree.getRootNode()->getFrequency() == treeCopy.getRootNode()->getFrequency());
        }
        SECTION("Move Constructor")
        {
            hufftree.buildFrequencyTable("testingFiles/testinput");
            tempFreqMap = hufftree.getFrequencyTable();
            hufftree.buildHuffmanTree(tempFreqMap);
            HuffmanTree treeCopy = std::move(hufftree);
            REQUIRE(((treeCopy.getRootNode() != nullptr) && (hufftree.getRootNode() == nullptr)));
        }
        SECTION("Copy Assignment Operator")
        {

            HuffmanTree tree;

            hufftree.buildFrequencyTable("testingFiles/testinput");
            tempFreqMap = hufftree.getFrequencyTable();
            hufftree.buildHuffmanTree(tempFreqMap);
            HuffmanTree treeCopy;
            treeCopy = hufftree;
            REQUIRE(hufftree.getRootNode()->getFrequency() == treeCopy.getRootNode()->getFrequency());
        }
        SECTION("Move Assignment Operator")
        {

            hufftree.buildFrequencyTable("testingFiles/testinput");
            tempFreqMap = hufftree.getFrequencyTable();
            hufftree.buildHuffmanTree(tempFreqMap);
            HuffmanTree treeCopy;
            treeCopy = std::move(hufftree);
            REQUIRE(((treeCopy.getRootNode() != nullptr) && (hufftree.getRootNode() == nullptr)));
        }
    }

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

    SECTION("encodeData() Tests")
    {
        hufftree.buildFrequencyTable("testingFiles/testinput");
        tempFreqMap = hufftree.getFrequencyTable();
        hufftree.buildHuffmanTree(tempFreqMap);
        hufftree.buildCodeTable(hufftree.getRootNode(), ""); //Build the code table from the tree
        tempCodeMap = hufftree.getCodeTable();

        std::string encodedString = hufftree.encodeData("testingFiles/testinput");

        int totBits = 0;
        for (auto const &element : tempFreqMap)
        {
            totBits += tempCodeMap[element.first].length() * element.second;
        }

        //std::cout << encodedString << std::endl;
        REQUIRE(encodedString.length() == totBits); //Ensure that the expected number of bits is present in the encoded string
    }

    SECTION("compressData() Tests")
    {
        hufftree.compressData("testingFiles/lorem_ipsum", "lorem_output");
        std::string encodedString = hufftree.encodeData("testingFiles/lorem_ipsum");
        std::ifstream ifs("testingFiles/lorem_output.txt");
        std::string readFromFileLine = "";
        if (ifs.is_open())
        {
            getline(ifs, readFromFileLine);
            //std::cout << "From the file: " << tempLine << std::endl;
        }
        else
        {
            std::cout << "Unable to open testing output text file." << std::endl;
        }
        ifs.close();
        ifs.open("outputFiles/lorem_output.hdr");
        int numPairs = 0;
        if (ifs.is_open())
        {
            std::string tempLine;
            while (!ifs.eof())
            {
                numPairs++;
                getline(ifs, tempLine);
                //std::cout << tempLine << std::endl;
            }
        }
        else
        {
            std::cout << "Unable to open testing output text file." << std::endl;
        }
        tempCodeMap = hufftree.getCodeTable();
        /*std::cout << "About to print out code table:" << std::endl;
        for (auto const &element : tempCodeMap)
        {
            std::cout << (int)element.first << ":" << element.second << std::endl;
        }*/

        REQUIRE(readFromFileLine.length() == encodedString.length()); //Ensure encoded string is written to file correctly
        REQUIRE((numPairs - 1) == tempCodeMap.size());                //Ensure code table is written to header file correctly - accounts for last endl character
    }
    SECTION("compressToBitStream() and decompressFromBitStream() Tests")
    {
        hufftree.compressToBitStream("testingFiles/lorem_ipsum", "lorem_output_bitstream");
        hufftree.decompressFromBitStream("outputFiles/lorem_output_bitstream", "outputFiles/lorem_output_bitstream");

        std::ifstream ifs1("testingFiles/lorem_ipsum.txt");
        std::ifstream ifs2("outputFiles/lorem_output_bitstream_decompressed.txt");
        std::string line1 = "";
        std::string line2 = "";
        if (ifs1.is_open() && ifs2.is_open())
        {
            getline(ifs1, line1);
            getline(ifs2, line2);
            REQUIRE(line1.compare(line2) == 0); //The original file must match the decompressed file
        }
        else
        {
            std::cout << "Unable to open input text file or decompressed text file." << std::endl;
        }
        ifs1.close();
        ifs2.close();
    }
}