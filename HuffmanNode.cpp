#include "HuffmanNode.h"

namespace CHNJAR003
{

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

HuffmanNode::HuffmanNode(const HuffmanNode &rhs) : frequency(rhs.frequency),
                                                   character(rhs.character), rightChild(rhs.rightChild), leftChild(rhs.leftChild)
{
}

HuffmanNode::HuffmanNode(HuffmanNode &&rhs) : frequency(rhs.frequency), character(rhs.character), rightChild(rhs.rightChild), leftChild(rhs.leftChild)
{
    rhs.rightChild = nullptr;
    rhs.leftChild = nullptr;
    rhs.frequency = -1;
}

HuffmanNode &HuffmanNode::operator=(const HuffmanNode &rhs)
{
    if (this != &rhs)
    {
        frequency = rhs.frequency;
        character = rhs.character;
        rightChild = rhs.rightChild;
        leftChild = rhs.leftChild;
    }
    return *this; //return a reference to the current object
}

HuffmanNode &HuffmanNode::operator=(HuffmanNode &&rhs)
{
    if (this != &rhs)
    {
        character = std::move(rhs.character);
        frequency = rhs.frequency;
        rhs.frequency = -1;
        leftChild = rhs.leftChild;
        rightChild = rhs.rightChild;

        rhs.leftChild = nullptr;
        rhs.rightChild = nullptr;
    }

    return *this; //return a reference to the current object
}

void HuffmanNode::setCharacter(char c)
{
    character = c;
}

void HuffmanNode::setFrequency(int f)
{
    frequency = f;
}

void HuffmanNode::setLeftChild(HuffmanNode left)
{
    leftChild = std::shared_ptr<HuffmanNode>(new HuffmanNode(left));
}
void HuffmanNode::setRightChild(HuffmanNode right)
{
    rightChild = std::shared_ptr<HuffmanNode>(new HuffmanNode(right));
}

char HuffmanNode::getCharacter(void) const
{
    return character;
}

int HuffmanNode::getFrequency(void) const
{
    return frequency;
}
HuffmanNode *HuffmanNode::getLeftChild() const
{
    return leftChild.get();
}

HuffmanNode *HuffmanNode::getRightChild() const
{
    return rightChild.get();
}

bool operator<(const HuffmanNode &a, const HuffmanNode &b)
{

    return a.getFrequency() > b.getFrequency();
}

} // namespace CHNJAR003