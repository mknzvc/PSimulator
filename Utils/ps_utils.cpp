#include "ps_utils.h"

namespace utils
{
    void setBit(unsigned int& number, char position)
    {
        number |= 1U << position;
    }

    void unsetBit(unsigned int &number, char position)
    {
        number &= ~(1 << position);
    }

    void isloateRightmostBit(unsigned number, unsigned &out)
    {
        out = number & (-number);
    }

    char getOnesCount(unsigned number)
    {
        char count = 0;
        while(number)
        {
            count += number&1;
            number >>= 1;
        }
        return count;
    }

    unsigned getNthBit(unsigned number, char position)
    {
        return (number & (1U << position)) != 0;
    }

    unsigned bitwiseXOR(unsigned left, unsigned right)
    {
        return left ^ right;
    }

    unsigned bitwiseXNOR(unsigned left, unsigned right)
    {
        return ~(left^right);
    }

    unsigned getMaskedBits(unsigned number, unsigned mask)
    {

    }

}
