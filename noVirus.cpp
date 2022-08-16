#include <windows.h>
#include <cstdio>
#include <string>

#define MOVE_X_INCR 50
#define MOVE_Y_INCR 20
#define MAX_WINDOWS 10
#define MODULO_THING 150

HWND WINAPI GetConsoleWindowNT() {
  typedef HWND WINAPI(*GetConsoleWindowT)();
  GetConsoleWindowT GetConsoleWindow;
  HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
  GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib, TEXT("GetConsoleWindow"));

  if (GetConsoleWindow == nullptr) {
	return nullptr;
  }
  return GetConsoleWindow();
}

struct POS {
  int x;
  int y;
};

int main(int argc, char **argv) {
  HWND hWnd = GetConsoleWindowNT();

  HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
  MONITORINFO info;
  info.cbSize = sizeof(MONITORINFO);
  GetMonitorInfo(monitor, &info);

  POS screen;
  screen.x = info.rcMonitor.right - info.rcMonitor.left;
  screen.y = info.rcMonitor.bottom - info.rcMonitor.top;

  short windowCount = 0;

  for (int x = 0; x < screen.x; x += MOVE_X_INCR) {
	for (int y = 0; y < screen.y; y += MOVE_Y_INCR)
	  MoveWindow(hWnd, x, y, 300, 200, TRUE);
	for (int y = screen.y; y > 0; y -= MOVE_Y_INCR)
	  MoveWindow(hWnd, x, y, 300, 200, TRUE);

	if (x % MODULO_THING == 0 && windowCount <= MAX_WINDOWS && argv[1] == nullptr) {
	  char szExeFileName[MAX_PATH];
	  GetModuleFileName(NULL, szExeFileName, MAX_PATH);
	  system((std::string("start ") + szExeFileName + " x").c_str());
	  windowCount++;
	}
  }
}