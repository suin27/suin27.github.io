#include "crt.h"//crt secure no warnings�� �׻� �� ���� ��ġ�Ұ�.
#include<stdio.h>//stdio.h�� �ް��ؼ� 2��° ��ġ
#include<Windows.h>
#include<stdlib.h>
#include<conio.h>
#include "cui.h"
#include "menu.h"
#include "lib.h"
#include "book_util.h"
#include "register.h"

int main() {
	//�ܼ�â �ִ�ũ��.
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	fontcolor(GREEN);
	set_cursor_type(NOCURSOR);
	new_title();
	_getch();
	system("cls");
	fontcolor(LIGHT_GREEN);
	set_cursor_type(NORMAL_CURSOR);
	//������� Ÿ��Ʋ ȭ��
	start_menu();

	return 0;
}