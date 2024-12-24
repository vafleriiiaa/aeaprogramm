
#include <conio.h>

int main(int argc, char* argv[]) {
    int i;

    _cputs("Process is created");
    _cputs("\nProcess name is: ");
    _cputs(argv[0]);

    for (i = 1; i < argc; ++i) {
        _cprintf("\nThe %d parameter = %s", i, argv[i]);
    }

    _cputs("\nPress any key to finish\n");
    _getch();

    return 0;
}