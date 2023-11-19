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