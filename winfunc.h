#include <iostream>
#include <windows.h>
using namespace std;

namespace console_setting{
    
    void SetTitle(wstring title);                       // đặt tiêu đề   
    void gotoxy(SHORT posX, SHORT posY);                // đi đến tọa độ xy
    void setcolor(int backgound_color, int text_color); // chỉnh màu nền và kí tự 
    void SetVietnamese();                               // tiếng việt 
    void SetMaximize();                                 // Mở rộng
    void SetFullscreen();
    void SetWindowSize(SHORT width, SHORT height);      // đặt tỷ lệ cửa sổ
    void SetScreenBufferSize(SHORT width, SHORT height);// đặt tỷ lệ khung hình hiển thị
    void DisableCtrButton(bool Close, bool Min, bool Max, bool Restore);// vô hiệu hóa các phím menu (0,0,0,1)
    void DisableResizeWindow();             // vô hiệu hóa thay đổi kích thước màn hình
    void DisableSelection();                // vô hiệu hóa bôi đen
    void ShowScrollbar(BOOL Show);          // ẩn hiện thanh cuộn
    void ShowCur(bool CursorVisibility);    // ẩn hiện con trỏ


}
void console_setting::SetTitle(wstring title) {
    LPCWSTR L_title = title.c_str();
    SetConsoleTitle(L_title);
}
void console_setting::gotoxy(SHORT posX, SHORT posY){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}
void console_setting::setcolor(int backgound_color, int text_color){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void console_setting::SetVietnamese(){
    SetConsoleOutputCP(65001);
}
void console_setting::SetMaximize(){
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}
void console_setting::SetFullscreen(){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD flags=CONSOLE_FULLSCREEN_MODE;
    COORD NewSize;
    SetConsoleDisplayMode(hStdout,flags,&NewSize);
}
void console_setting::SetWindowSize(SHORT width, SHORT height){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
void console_setting::SetScreenBufferSize(SHORT width, SHORT height){
    
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}
void console_setting::DisableCtrButton(bool Close, bool Min, bool Max, bool Restore){
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);
    
    if (Close == 1) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    if (Min == 1) DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    if (Max == 1) DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    if (Restore == 1) DeleteMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
}
void console_setting::DisableResizeWindow(){
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}
void console_setting::DisableSelection(){
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}
void console_setting::ShowScrollbar(BOOL Show){
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}
void console_setting::ShowCur(bool CursorVisibility){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    
    SetConsoleCursorInfo(handle, &ConCurInf);
}
/* color
[	0 = Black	]
[	1 = Blue	]
[	2 = Green	]
[	3 = Aqua	]
[	4 = Red	    ]
[	5 = Purple	]
[	6 = Yellow	]
[	7 = White	]
[	8 = Gray	]
[	9 = Light Blue	    ]
[	10 = Light Green	]
[	11 = Light Aqua	    ]
[	12 = Light Red	    ]
[	13 = Light Purple	]
[	14 = Light Yellow	]
[	15 = Bright White	]
*/