#include <windows.h>

#pragma comment(lib, "user32.lib")



int main() {
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
    system("start explorer");
    while(true) {
        _sleep(50);
        SetCursorPos(rand()%1000, rand()%1000);
    }
}