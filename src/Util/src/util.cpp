# include "util.hpp"

void appendword2vector(const uint16_t word, std::vector<uint8_t>& vecdata)
{
	uint8_t byt;

	byt = word>>8;
	vecdata.push_back(byt);

	byt = word;
	vecdata.push_back(byt);
}

uint16_t word_frombytes(uint8_t byte0, uint8_t byte1, bool byteswap)
{
	int val;
        if (byteswap)
	    val = static_cast<int>(byte0)<<8 | static_cast<int>(byte1);
	else
	    val = static_cast<int>(byte1)<<8 | static_cast<int>(byte0);
	return val;
}
