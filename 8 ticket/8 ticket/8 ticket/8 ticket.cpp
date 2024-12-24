#include <windows.h> 
#include <iostream> 

using namespace std;

int main()
{
    // Путь к исполняемому файлу 
    char lpszAppName[] = "C:\\Program Files (x86)\\Yandex\\YandexBrowser\\24.12.1.714\\service_update.exe";

    // Параметры запуска процесса 
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Инициализация структуры STARTUPINFO 
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    // Создаем новый консольный процесс 
    if (!CreateProcess(
        lpszAppName,       // Имя исполняемого файла 
        NULL,              // Командная строка (NULL означает использовать имя файла) 
        NULL,              // Атрибуты безопасности процесса 
        NULL,              // Атрибуты безопасности потока 
        FALSE,             // Наследование дескрипторов 
        CREATE_NEW_CONSOLE, // Флаг создания новой консоли 
        NULL,              // Переменные окружения (используем текущие) 
        NULL,              // Текущий каталог (используем текущий) 
        &si,               // Указатель на STARTUPINFO 
        &pi))              // Указатель на PROCESS_INFORMATION 
    {
        cerr << "Failed to create process. Error code: " << GetLastError() << endl;
        return 1;
    }

    cout << "The new process is created with PID: " << pi.dwProcessId << endl;

    // Время ожидания завершения процесса (например, 10 секунд) 
    DWORD dwWaitTime = 10000; // 10 секунд 

    // Ожидаем завершения процесса в течение заданного времени 
    DWORD dwWaitResult = WaitForSingleObject(pi.hProcess, dwWaitTime);

    switch (dwWaitResult)
    {
    case WAIT_OBJECT_0:
        // Процесс завершился 
        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        cout << "The process has finished with exit code: " << exitCode << endl;
        break;

    case WAIT_TIMEOUT:
        // Процесс не завершился в течение заданного времени 
        cout << "The process is still running. Terminating it..." << endl;
        TerminateProcess(pi.hProcess, 1); // Завершаем процесс с кодом 1 
        cout << "The process has been terminated." << endl;
        break;

    default:
        // Произошла ошибка 
        cerr << "Error while waiting for process. Error code: " << GetLastError() << endl;
        break;
    }

    // Закрываем дескрипторы процесса и потока 
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    cout << "Press any key to exit." << endl;
    cin.get();
    return 0;
}