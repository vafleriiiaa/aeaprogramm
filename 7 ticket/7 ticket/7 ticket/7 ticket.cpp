#include <windows.h>
#include <iostream>

using namespace std;

int main() {
    // Путь к исполняемому файлу
    LPCSTR exePath = "C:\\exam\\7 ticket\\7 ticket\\x64\\Debug";

        // Аргументы для запуска (включая имя файла)
        char cmdLine[] = "\"C:\\exam\\7 ticket\\7 ticket\\x64\\Debug\" param1 param2";
        // Структуры для процесса и потока
        STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    // Создание нового процесса
    if (CreateProcess(
        NULL,           // Имя исполняемого файла (NULL, если используем cmdLine)
        cmdLine,        // Полная командная строка (имя файла + параметры)
        NULL,           // Атрибуты защиты процесса
        NULL,           // Атрибуты защиты потока
        FALSE,          // Наследование дескрипторов
        CREATE_NEW_CONSOLE, // Создание нового окна консоли
        NULL,           // Переменные окружения
        NULL,           // Рабочая директория
        &si,            // Указатель на STARTUPINFO
        &pi             // Указатель на PROCESS_INFORMATION
    )) {
        cout << "Cozdan.\n";

        // Ожидание завершения процесса
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Закрытие дескрипторов
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        cout << "Zavershen.\n";
    }
    else {
        cout << "Ne ydaloc: " << GetLastError() << endl;
    }

    return 0;
}