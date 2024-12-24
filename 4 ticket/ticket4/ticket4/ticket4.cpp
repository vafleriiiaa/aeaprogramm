#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;  // Пространство имен std для упрощения работы с вводом-выводом.

int main() {
    TCHAR currentDir[MAX_PATH]; // Массив для хранения пути к текущему каталогу.

    // Получаем текущий каталог.
    DWORD result = GetCurrentDirectory(MAX_PATH, currentDir);
    if (result == 0) { // Если ошибка, выводим код ошибки и завершаем программу.
        cerr << "Error: Failed to get current directory. Error code: " << GetLastError() << endl;
        return 1;
    }
    else if (result > MAX_PATH) { // Проверяем, не превышает ли путь максимально допустимую длину.
        cerr << "Error: Current directory path is too long." << endl;
        return 1;
    }

    // Выводим текущий каталог.
    cout << "Current Directory: " << currentDir << endl;

    // Печать содержимого каталога.
    WIN32_FIND_DATA findFileData; // Структура для хранения информации о файлах.
    HANDLE hFind = FindFirstFile((wstring(currentDir) + L"\\*").c_str(), &findFileData); // Открываем поиск файлов.

    if (hFind == INVALID_HANDLE_VALUE) { // Проверяем успешность открытия.
        cerr << "Error: Failed to read directory contents. Error code: " << GetLastError() << endl;
        return 1;
    }

    cout << "Directory Contents:" << endl;
    do {
        // Проверяем, является ли объект директорией.
        wcout << ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? L"[DIR] " : L"      ")
            << findFileData.cFileName << endl;
    } while (FindNextFile(hFind, &findFileData)); // Идем к следующему файлу.

    FindClose(hFind); // Закрываем дескриптор поиска.
    return 0; // Успешное завершение программы.
}

