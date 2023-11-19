#ifndef EP_PARSE_FILE_H
#define EP_PARSE_FILE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

const uint16_t EP_IMAGE_DOS_SIGNATURE = 0x5A4D; // "MZ"
const uint32_t EP_IMAGE_NT_SIGNATURE = 0x00004550; // "PE\0\0"

#endif // EP_PARSE_FILE_H
