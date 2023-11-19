#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <cctype>  
// #include "listNames.h"  

using namespace std;


void parseExportTable(std::ifstream& file, const IMAGE_EXPORT_DIRECTORY& exportDirectory) {
    std::cout << "\nExport Table:" << std::endl;
    file.seekg(exportDirectory.AddressOfNames, std::ios::beg);
    std::vector<uint32_t> nameOffsets(exportDirectory.NumberOfNames);
    file.read(reinterpret_cast<char*>(nameOffsets.data()), sizeof(uint32_t) * exportDirectory.NumberOfNames);

    for (uint32_t i = 0; i < exportDirectory.NumberOfNames; ++i) {
        if (nameOffsets[i] < static_cast<uint32_t>(file.tellg())) {
            // Skip invalid offset
            continue;
        }

        file.seekg(nameOffsets[i], std::ios::beg);
        std::string functionName;
        std::getline(file, functionName, '\0');

        bool isValid = true;
        for (char c : functionName) {
            if (!::isprint(static_cast<unsigned char>(c))) {
                isValid = false;
                break;
            }
        }

        if (functionName.empty() || !isValid) {
            std::cout << "Exported Function Offset[" << i << "]: " << nameOffsets[i] << std::endl;
            std::cout << "Exported Function: <Invalid or Empty>" << std::endl;
        } else {
            std::cout << "Exported Function Offset[" << i << "]: " << nameOffsets[i] << std::endl;
            std::cout << "Exported Function: " << functionName << " (size: " << functionName.size() << ")" << std::endl;
        }
    }
}

void parseImportTable(std::ifstream& file, const IMAGE_IMPORT_DESCRIPTOR& importDescriptor) {
    std::cout << "\nImport Table:" << std::endl;

    file.seekg(importDescriptor.Name, std::ios::beg);
    std::string importedLibraryName;
    std::getline(file, importedLibraryName, '\0');
    std::cout << "Imported Library: " << importedLibraryName << std::endl;

    file.seekg(importDescriptor.OriginalFirstThunk, std::ios::beg);
    std::vector<uint32_t> thunkData;
    while (true) {
        uint32_t thunk;
        file.read(reinterpret_cast<char*>(&thunk), sizeof(uint32_t));
        if (thunk == 0) {
            break;
        }
        thunkData.push_back(thunk);
    }

    for (uint32_t thunk : thunkData) {
        if (thunk & 0x80000000) {
            // Ordinal
            std::cout << "Imported Function (Ordinal): " << (thunk & 0xFFFF) << std::endl;
        } else {
            // By Name
            file.seekg(thunk + 2, std::ios::beg); // Skip hint
            std::string importedFunctionName;
            std::getline(file, importedFunctionName, '\0');
            std::cout << "Imported Function (ByName): " << importedFunctionName << std::endl;
        }
    }
}

void ParseImportExport(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    IMAGE_DOS_HEADER dosHeader;
    file.read(reinterpret_cast<char*>(&dosHeader), sizeof(IMAGE_DOS_HEADER));

    if (dosHeader.e_magic != 0x5A4D) {
        std::cerr << "Not a valid PE file." << std::endl;
        return;
    }

    IMAGE_NT_HEADERS ntHeaders;
    file.seekg(dosHeader.e_lfanew, std::ios::beg);
    file.read(reinterpret_cast<char*>(&ntHeaders), sizeof(IMAGE_NT_HEADERS));

    // Parse Export Table
    IMAGE_EXPORT_DIRECTORY exportDirectory;
    file.seekg(
        ntHeaders.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress,
        std::ios::beg
    );
    file.read(reinterpret_cast<char*>(&exportDirectory), sizeof(IMAGE_EXPORT_DIRECTORY));
    parseExportTable(file, exportDirectory);

    // Parse Import Table
    IMAGE_IMPORT_DESCRIPTOR importDescriptor;
    file.seekg(
        ntHeaders.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress,
        std::ios::beg
    );
    while (true) {
        file.read(reinterpret_cast<char*>(&importDescriptor), sizeof(IMAGE_IMPORT_DESCRIPTOR));
        if (importDescriptor.Name == 0) {
            break;
        }
        parseImportTable(file, importDescriptor);
    }

    file.close();
}