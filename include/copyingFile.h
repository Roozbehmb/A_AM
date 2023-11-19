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
    wchar_t appDataPath[MAX_PATH];
    HRESULT result = SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appDataPath);
    if (SUCCEEDED(result)) {
          std::wcout << L"file:" << appDataPath << std::endl;
        std::wstring destinationPath = std::wstring(appDataPath) + L"\\YourApp.exe";
                if (CopyFileW(exePath, destinationPath.c_str(), FALSE) != 0) {
            std::wcout << L"The program was successfully copied to the AppData path." << std::endl;
            return 0;

        } else {
            std::wcout << L"Error copying the program to the AppData path. Error code: " << GetLastError() << std::endl;
            return 0;

        }
    } else {
        std::wcout << L"Error getting the AppData path. Error code: " << result << std::endl;
        return 0;

    }
}