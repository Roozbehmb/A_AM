#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include "listNames.h"
#include "parser.h"
#include "EPparseFile.h"
#include "copyingFile.h"
#include "searchInFile.h"
#include "bst-File.h"


int menu();
void Get_ExportImport();

int main(){

    menu();

    return 0;
}

int menu(){
        int choice ;
        std::string filePath = "C:\\Users\\Roozbeh\\Desktop\\rx.exe"; ///test

    do {
        // نمایش منو
        std::cout << "Menu:\n";
        std::cout << "1. Binary Search Tree or BTS  \n";
        std::cout << "2. Search a file or phrase \n";
        std::cout << "3. A copy of the executable file after running the program \n";
        std::cout << "4. parsePEHeaders \n";
        std::cout << "5. get list name linke node  \n";
        std::cout << "6. get list name export and import EP  \n";
        std::cout << "7. Exit\n";

        std::cout << "Enter your choice: ";

        // دریافت انتخاب کاربر
        std::cin >> choice;

        // اجرای اقدامات متناسب با انتخاب
        switch (choice) {
            case 1:
                bst_Name();
                // اجرای اقدامات مربوط به bst_Name 
                break;
            case 2:
                search();
                // اجرای اقدامات مربوط به search 
                break;
            case 3:
                dataFile();
                // اجرای اقدامات مربوط به dataFile 
                break;
            case 4:
                parsePEHeaders(filePath);
                // اجرای اقدامات مربوط به parsePEHeaders 
                break;
            case 5:
                GetLinkedList();
                // اجرای اقدامات مربوط به GetLinkedList 
                break;
            case 6:
                Get_ExportImport();
                // اجرای اقدامات مربوط به GetExportImport 
                break;
            default:
                std::cout << "Please try again!!!.\n";
                // اگر انتخاب معتبر نباشد، پیام خطا نمایش داده شود
        }

    } while (choice != 7); // تا زمانی که کاربر Exit نکند، حلقه ادامه یابد

return 0;
}

void Get_ExportImport(){


    LinkedList nameList;

    // while (true) {
    //     cout << "Please enter a name or number to create the file (or type '.' to finish): ";
    //     string name;
    //     cin >> name;

    //     if (name == ".") {
    //         break;
    //     }

    //     nameList.insert(name);
    // }

    std::string filePath = "C:\\Windows\\System32\\mspaint.exe";

    ParseImportExport(filePath);

}