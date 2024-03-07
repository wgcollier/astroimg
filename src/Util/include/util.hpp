#ifndef __UTIL_MODULE_H__
#define __UTIL_MODULE_H__

#include <iostream>
#include <vector>
namespace util
{
void appendword2vector(const uint16_t, std::vector<uint8_t>&);
uint16_t word_frombytes(uint8_t, uint8_t, bool);
}

#endif /* __UTIL_MODULE_H__ */
