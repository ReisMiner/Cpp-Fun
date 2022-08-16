#include <windows.h>
#include <cstdio>

#define MOVE_INCR 1

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

int main() {
  HWND hWnd = GetConsoleWindowNT();

  HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
  MONITORINFO info;
  info.cbSize = sizeof(MONITORINFO);
  GetMonitorInfo(monitor, &info);

  POS screen;
  screen.x = info.rcMonitor.right - info.rcMonitor.left;
  screen.y = info.rcMonitor.bottom - info.rcMonitor.top;

  for (int x = 0; x < screen.x; x += MOVE_INCR) {
	for (int y = 0; y < screen.y; y += MOVE_INCR)
	  MoveWindow(hWnd, x, y, 300, 200, TRUE);
	for (int y = screen.y; y > 0; y -= MOVE_INCR)
	  MoveWindow(hWnd, x, y, 300, 200, TRUE);
  }
}