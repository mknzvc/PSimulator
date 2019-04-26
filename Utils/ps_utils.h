#ifndef PS_UTILS_H
#define PS_UTILS_H

namespace utils
{

void setBit(unsigned int& number, char position);

void unsetBit(unsigned int& number, char position);

void isloateRightmostBit(unsigned number, unsigned& out);

char getOnesCount(unsigned number);

unsigned getNthBit(unsigned number, char position);

unsigned bitwiseXOR(unsigned left, unsigned right);

unsigned bitwiseXNOR(unsigned left, unsigned right);

}

namespace types
{

enum class FeedbackType
{
    XOR = 0,
    XNOR = 1
};

}

#endif // PS_UTILS_H
