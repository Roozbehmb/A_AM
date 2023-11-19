#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <set>
namespace fs = std::filesystem;

using namespace std;

void searchInFile(const std::string& filePath, const std::string& searchPhrase) {
    
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        int lineCount = 0;
        while (getline(file, line)) {
            lineCount++;
            if (line.find(searchPhrase) != std::string::npos) {
                std::cout << "Match found in file: " << filePath << " (Line " << lineCount << ")\n";
            }
        }
        file.close();
    }
}
