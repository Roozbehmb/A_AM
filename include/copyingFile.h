#include <iostream>
#include <string>
#include <windows.h>
#include <Shlobj.h>

int dataFile(){
    int number = 0;
    std::cout << "plese enter a number :"<<std::endl;
    std::cin >> number;
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);

}