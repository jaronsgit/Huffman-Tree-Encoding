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

    void setCharacter(char c);                    //setter for character
    void setFrequency(int f);                     //setter for frequency
    void setLeftChild(const HuffmanNode &left);   //setter for left child node
    void setRightChild(const HuffmanNode &right); //setter for right child node

    char getCharacter(void) const;      //getter for character
    int getFrequency(void) const;       //getter for frequency
    HuffmanNode *getLeftChild() const;  //getter for left child node
    HuffmanNode *getRightChild() const; //getter for right child node

    friend bool operator<(const HuffmanNode &a, const HuffmanNode &b);
};

} // namespace CHNJAR003

#endif