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
}