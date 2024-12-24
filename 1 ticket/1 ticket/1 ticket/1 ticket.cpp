#include <windows.h>
#include <iostream>
#include <stdio.h>
#define BUF_SIZE 256
using namespace std;

int main(int argc, LPTSTR argv[]) {
    HANDLE hStdOut; // дескриптор файла для вывода на консоль
    DWORD nOut; // количество записанных байт
    CHAR Buffer[BUF_SIZE];
    LPCWSTR fileNames[] = { L"test11.txt", L"test22.txt", L"test33.txt" }; // массив имен файлов

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 1; i < argc; i++) {
        HANDLE hIn = CreateFile(argv[i], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hIn == INVALID_HANDLE_VALUE) {
            printf("unable to open input file. Error: %x\n", GetLastError());
            return 1;
        }

        while (ReadFile(hIn, Buffer, BUF_SIZE, &nOut, NULL) && (nOut != 0)) {
            WriteFile(hStdOut, Buffer, nOut, &nOut, NULL); // вывод содержимого файла на стандартное устройство вывода
            printf("\n");
        }
        CloseHandle(hIn);
    }
    return 0;
}

