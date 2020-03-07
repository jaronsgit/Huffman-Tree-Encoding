#include "HuffmanNode.h"

using namespace CHNJAR003;

HuffmanNode::HuffmanNode()
{
    frequency = 0;
    character = 0;
    leftChild = nullptr;
    rightChild = nullptr;
}

HuffmanNode::~HuffmanNode()
{
    frequency = -1;
    leftChild = nullptr;
    rightChild = nullptr;
}
