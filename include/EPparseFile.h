#ifndef EP_PARSE_FILE_H
#define EP_PARSE_FILE_H


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

const uint16_t EP_IMAGE_DOS_SIGNATURE = 0x5A4D; // "MZ"
const uint32_t EP_IMAGE_NT_SIGNATURE = 0x00004550; // "PE\0\0"

#pragma pack(push, 1)

struct EP_IMAGE_DOS_HEADER {
    uint16_t e_magic;      // Magic number
    uint16_t e_cblp;
    uint16_t e_cp;
    uint16_t e_crlc;
    uint16_t e_cparhdr;
    uint16_t e_minalloc;
    uint16_t e_maxalloc;
    uint16_t e_ss;
    uint16_t e_sp;
    uint16_t e_csum;
    uint16_t e_ip;
    uint16_t e_cs;
    uint16_t e_lfarlc;
    uint16_t e_ovno;
    uint16_t e_res[4];
    uint16_t e_oemid;
    uint16_t e_oeminfo;
    uint16_t e_res2[10];
    uint32_t e_lfanew;     // Offset to the PE signature
};

struct EP_IMAGE_NT_HEADERS {
    uint32_t Signature;
};

struct EP_IMAGE_FILE_HEADER {
    uint16_t Machine;
    uint16_t NumberOfSections;
    uint32_t TimeDateStamp;
    uint32_t PointerToSymbolTable;
    uint32_t NumberOfSymbols;
    uint16_t SizeOfOptionalHeader;
    uint16_t Characteristics;
};

struct EP_IMAGE_OPTIONAL_HEADER {
    uint16_t Magic;
    // Other optional header fields can be added as needed
};

struct EP_IMAGE_SECTION_HEADER {
    char     Name[8];
    uint32_t VirtualSize;
    uint32_t VirtualAddress;
    uint32_t SizeOfRawData;
    uint32_t PointerToRawData;
    uint32_t PointerToRelocations;
    uint32_t PointerToLinenumbers;
    uint16_t NumberOfRelocations;
    uint16_t NumberOfLinenumbers;
    uint32_t Characteristics;
};

#pragma pack(pop)

void parseDosHeader(std::ifstream& file) {
    EP_IMAGE_DOS_HEADER dosHeader;
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(&dosHeader), sizeof(IMAGE_DOS_HEADER));

    if (dosHeader.e_magic == EP_IMAGE_DOS_SIGNATURE) {
        std::cout << "DOS Header:" << std::endl;
        std::cout << "e_lfanew (Offset to PE signature): " << dosHeader.e_lfanew << std::endl;
    } else {
        std::cerr << "Invalid DOS signature." << std::endl;
    }
}

#endif // EP_PARSE_FILE_H
