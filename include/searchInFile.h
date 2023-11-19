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

void searchInDirectory(const std::string& directoryPath, const std::string& searchPhrase,vector<string> &list_new ,int select ) {
    int i=0;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        
        if (entry.is_directory()) {
            searchInDirectory(entry.path().string(), searchPhrase,list_new , select); /// تبدیل به رشته
        } else if (entry.is_regular_file()) {
            
            if(select == 1){
                if(entry.path().filename().string().find(searchPhrase) != std::string::npos){
                    string  list= entry.path().filename().string();
                    list_new.push_back(list);
                }
            }else{
                    searchInFile(entry.path().string(), searchPhrase); // تبدیل به رشته
            }

            }
        
        }
    }

    void display(vector<string> list){
    int arrSize = list.size();
    for(int i = 0; i < arrSize; i++) {
    cout << " Match found text in the file = \t" << list[i] << endl;
}
    }

void sortedByName(){
string path_name = "./amnparadaz";

  set<fs::path> sorted_by_name;

  for (auto &entry : fs::directory_iterator(path_name))
    sorted_by_name.insert(entry.path());

  for (auto &filename : sorted_by_name){
    cout << filename.string() << endl;
  }
}

int search(){
    vector<string> List;
    int select = 0;
    std::string searchPhrase;

    cout << "1)Search by file name  "<<endl;
    cout << "2)Search for text in the file "<<endl;
    cin >> select;
    
    if(select > 0 and select <= 2){
        if(select==2){std::cout << "Enter a text to search in a file : ";}
        else{std::cout << "Enter the search phrase : ";}
    cin >> searchPhrase;
  //  std::getline(std::cin, searchPhrase);
    std::string startingDirectory = "."; 

    searchInDirectory(startingDirectory, searchPhrase, List , select );

    display(List);

    }


    return 0;
}
