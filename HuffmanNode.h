#ifndef HUFFMANNODE_H
#define HUFFMANNODE_H
#include <memory>
namespace CHNJAR003
{

class HuffmanNode
{
private:
    char character;
    int frequency;
    std::shared_ptr<HuffmanNode> leftChild;
    std::shared_ptr<HuffmanNode> rightChild;

public:
    HuffmanNode(void);                              //default constructor
    ~HuffmanNode();                                 //destructor
    HuffmanNode(const HuffmanNode &rhs);            //copy constructor
    HuffmanNode(HuffmanNode &&rhs);                 //move consructor
    HuffmanNode &operator=(const HuffmanNode &rhs); //assignent operator
    HuffmanNode &operator=(HuffmanNode &&rhs);      //move assignment operator

    void setCharacter(char c);             //setter for character
    void setFrequency(int f);              //setter for frequency
    void setLeftChild(HuffmanNode left);   //setter for left child node
    void setRightChild(HuffmanNode right); //setter for right child node

    char getCharacter(void);      //getter for character
    int getFrequency(void);       //getter for frequency
    HuffmanNode *getLeftChild();  //getter for left child node
    HuffmanNode *getRightChild(); //getter for right child node
};

} // namespace CHNJAR003

#endif