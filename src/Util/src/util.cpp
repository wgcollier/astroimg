# include "util.hpp"

void util::appendword2vector(const uint16_t word, std::vector<uint8_t>& vecdata)
{
	uint8_t byt;

	byt = static_cast<uint8_t>(word>>8);
	vecdata.push_back(byt);

	byt = static_cast<uint8_t>(word);
	vecdata.push_back(byt);
}

uint16_t util::word_frombytes(uint8_t byte0, uint8_t byte1, bool byteswap)
{
	uint16_t val;
        if (byteswap)
	    val = static_cast<uint16_t>(byte1)<<8 | static_cast<uint16_t>(byte0);
	else
	    val = static_cast<uint16_t>(byte0)<<8 | static_cast<uint16_t>(byte1);
	return val;
}
