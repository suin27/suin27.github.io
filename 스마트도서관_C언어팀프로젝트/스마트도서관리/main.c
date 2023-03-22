#include "crt.h"//crt secure no warnings은 항상 젤 위에 위치할것.
#include<stdio.h>//stdio.h는 앵간해서 2번째 위치
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include "cui.h"
#include "menu.h"
#include "lib.h"
#include "book_util.h"
#include "register.h"

int main() {
	//콘솔창 최대크기.
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	fontcolor(GREEN);
	set_cursor_type(NOCURSOR);
	new_title();
	_getch();
	system("cls");
	fontcolor(LIGHT_GREEN);
	set_cursor_type(NORMAL_CURSOR);
	//여기까지 타이틀 화면
	start_menu();

	return 0;
}