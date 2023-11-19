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
    file.read(reinterpret_cast<char*>(&dosHeader), sizeof(EP_IMAGE_DOS_HEADER));

    if (dosHeader.e_magic == EP_IMAGE_DOS_SIGNATURE) {
        std::cout << "DOS Header:" << std::endl;
        std::cout << "e_lfanew (Offset to PE signature): " << dosHeader.e_lfanew << std::endl;
    } else {
        std::cerr << "Invalid DOS signature." << std::endl;
    }
}


void parseNtHeader(std::ifstream& file) {
    file.seekg(0, std::ios::beg);
    EP_IMAGE_DOS_HEADER dosHeader;
    file.read(reinterpret_cast<char*>(&dosHeader), sizeof(EP_IMAGE_DOS_HEADER));

    if (dosHeader.e_magic == EP_IMAGE_DOS_SIGNATURE) {
        file.seekg(dosHeader.e_lfanew, std::ios::beg);
        EP_IMAGE_NT_HEADERS ntHeader;
        file.read(reinterpret_cast<char*>(&ntHeader), sizeof(EP_IMAGE_NT_HEADERS));

        if (ntHeader.Signature == EP_IMAGE_NT_SIGNATURE) {
            std::cout << "\nNT Header:" << std::endl;
            std::cout << "Signature: " << std::hex << ntHeader.Signature << std::dec << std::endl;
        } else {
            std::cerr << "Invalid NT signature." << std::endl;
        }
    } else {
        std::cerr << "Invalid DOS signature." << std::endl;
    }
}


void parseFileHeader(std::ifstream& file) {
    file.seekg(0, std::ios::beg);
    EP_IMAGE_DOS_HEADER dosHeader;
    file.read(reinterpret_cast<char*>(&dosHeader), sizeof(EP_IMAGE_DOS_HEADER));

    if (dosHeader.e_magic == EP_IMAGE_DOS_SIGNATURE) {
        file.seekg(dosHeader.e_lfanew + sizeof(uint32_t), std::ios::beg); // Move to IMAGE_NT_HEADERS
        EP_IMAGE_FILE_HEADER fileHeader;
        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(EP_IMAGE_FILE_HEADER));

        std::cout << "\nFile Header:" << std::endl;
        std::cout << "Machine: " << std::hex << fileHeader.Machine << std::dec << std::endl;
        std::cout << "NumberOfSections: " << fileHeader.NumberOfSections << std::endl;
        std::cout << "TimeDateStamp: " << fileHeader.TimeDateStamp << std::endl;
        std::cout << "SizeOfOptionalHeader: " << fileHeader.SizeOfOptionalHeader << std::endl;
        std::cout << "Characteristics: " << std::hex << fileHeader.Characteristics << std::dec << std::endl;
    } else {
        std::cerr << "Invalid DOS signature." << std::endl;
    }
}


void parseOptionalHeader(std::ifstream& file) {
    file.seekg(0, std::ios::beg);
    EP_IMAGE_DOS_HEADER dosHeader;
    file.read(reinterpret_cast<char*>(&dosHeader), sizeof(EP_IMAGE_DOS_HEADER));

    if (dosHeader.e_magic == EP_IMAGE_DOS_SIGNATURE) {
        file.seekg(dosHeader.e_lfanew + sizeof(uint32_t), std::ios::beg); // Move to IMAGE_NT_HEADERS
        EP_IMAGE_FILE_HEADER fileHeader;
        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(EP_IMAGE_FILE_HEADER));

        file.seekg(dosHeader.e_lfanew + sizeof(uint32_t) + sizeof(EP_IMAGE_FILE_HEADER), std::ios::beg); // Move to Optional Header
        EP_IMAGE_OPTIONAL_HEADER optionalHeader;
        file.read(reinterpret_cast<char*>(&optionalHeader), sizeof(EP_IMAGE_OPTIONAL_HEADER));

        std::cout << "\nOptional Header:" << std::endl;
        std::cout << "Magic: " << std::hex << optionalHeader.Magic << std::dec << std::endl;
        // Other optional header fields can be added here as needed
    } else {
        std::cerr << "Invalid DOS signature." << std::endl;
    }
}

void parseSectionHeaders(std::ifstream& file) {
    file.seekg(0, std::ios::beg);
    EP_IMAGE_DOS_HEADER dosHeader;
    file.read(reinterpret_cast<char*>(&dosHeader), sizeof(EP_IMAGE_DOS_HEADER));

    if (dosHeader.e_magic == EP_IMAGE_DOS_SIGNATURE) {
        file.seekg(dosHeader.e_lfanew + sizeof(uint32_t), std::ios::beg); // Move to IMAGE_NT_HEADERS
        EP_IMAGE_FILE_HEADER fileHeader;
        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(EP_IMAGE_FILE_HEADER));

        file.seekg(dosHeader.e_lfanew + sizeof(uint32_t) + sizeof(EP_IMAGE_FILE_HEADER), std::ios::beg); // Move to Optional Header
        EP_IMAGE_OPTIONAL_HEADER optionalHeader;
        file.read(reinterpret_cast<char*>(&optionalHeader), sizeof(EP_IMAGE_OPTIONAL_HEADER));

        file.seekg(dosHeader.e_lfanew + sizeof(uint32_t) + sizeof(EP_IMAGE_FILE_HEADER) + fileHeader.SizeOfOptionalHeader, std::ios::beg); // Move to Section Headers
        std::vector<EP_IMAGE_SECTION_HEADER> sectionHeaders(fileHeader.NumberOfSections);
        file.read(reinterpret_cast<char*>(sectionHeaders.data()), sizeof(EP_IMAGE_SECTION_HEADER) * fileHeader.NumberOfSections);

        std::cout << "\nSection Headers:" << std::endl;
        for (const auto& sectionHeader : sectionHeaders) {
            std::cout << "Name: " << sectionHeader.Name << std::endl;
            std::cout << "VirtualSize: " << sectionHeader.VirtualSize << std::endl;
            std::cout << "VirtualAddress: " << sectionHeader.VirtualAddress << std::endl;
            std::cout << "SizeOfRawData: " << sectionHeader.SizeOfRawData << std::endl;
            std::cout << "PointerToRawData: " << sectionHeader.PointerToRawData << std::endl;
            std::cout << "Characteristics: " << std::hex << sectionHeader.Characteristics << std::dec << std::endl;
            std::cout << std::endl;
        }
    } else {
        std::cerr << "Invalid DOS signature." << std::endl;
    }
}

int parsePEHeaders(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    
    parseDosHeader(file);
    parseNtHeader(file);
    parseFileHeader(file);
    parseOptionalHeader(file);
    parseSectionHeaders(file);


    return 0;
}



#endif // EP_PARSE_FILE_H
