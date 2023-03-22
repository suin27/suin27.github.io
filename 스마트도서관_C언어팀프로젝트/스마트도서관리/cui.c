#include"crt.h"
#include<stdio.h>
#include<windows.h>//표준 c는 아니다.-윈도우에서만 사용할 수 있다.
#include "cui.h"

void gotoxy(int x, int y) {
	COORD pos = { x,y };//여기서 coord는 구조체이다
	//win32 api - 윈도우 운영체제에서 제공하는 함수
	//->>운영체제들은 앵간해서 c로 이루어져 있다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//윈도우에서만 사용할수 있는 시스템 함수이다.
}//화면에 좌표 찍는 함수

void new_title() {
	int x = 2;
	int y = 0;
	gotoxy(x, y + 1); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");//지정된 좌표로 가서 다음 문구를 실행하라.
	gotoxy(x, y + 2); printf("■");
	for (int i = 2; i < 37; i++) {
		gotoxy(x, y + i); printf("■");
	}
	gotoxy(x, y + 8); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	//제목 그림 v1.0
	
	gotoxy(x + 6, y + 2); printf(" ●      ●●●   ●●●      ●●       ●●    ●    ●");
	gotoxy(x + 4, y + 3); printf(" ●  ●      ●     ●    ●  ●    ●   ●    ●  ●  ●");
	gotoxy(x + 4, y + 4); printf(" ●  ●      ●     ●●●   ●      ● ●      ● ●●");
	gotoxy(x + 2, y + 5); printf(" ●  ●  ●    ●     ●●●   ●      ● ●      ● ●●");
	gotoxy(x + 2, y + 6); printf(" ●      ●    ●     ●    ●  ●    ●   ●    ●  ●  ●  ");
	gotoxy(x + 2, y + 7); printf(" ●      ●  ●●●   ●●●      ●●       ●●    ●    ●");
	
	for (int i = 2; i < 37; i++) {
		gotoxy(x + 64, y + i); printf("■");
	}
	gotoxy(x, y + 36); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");


	x = 3;
	gotoxy(x, y + 12); printf(" ※※※ 메뉴 도움말 ※※※");
	gotoxy(x, y + 16); printf("▶ 도서 검색	: 등록된 도서 중 검색한 도서 정보를 출력합니다.");
	gotoxy(x, y + 18); printf("▶ 도서 대여	: 등록된 도서 중 원하는 도서를 대여처리 합니다.");
	gotoxy(x, y + 20); printf("▶ 도서 반납	: 대여 처리한 도서를 반납처리 합니다.");
	gotoxy(x, y + 22); printf("▶ 도서 추천	: 검색수가 많은 도서를 출력합니다.");
	gotoxy(x, y + 24); printf("▶ 도서 구매 정보	: 도서의 구매 정보를 출력합니다.");
	gotoxy(x, y + 26); printf("▶ 도서 관리	: 관리자 번호를 입력해야만 사용할 수 있습니다.");
	gotoxy(x, y + 28); printf("▶ 메인메뉴 이동은 아무키나 누르세요! ◀");
}

void set_cursor_type(CURSOR_TYPE type) {//이 또한 표준 c 는 아니다.
	CONSOLE_CURSOR_INFO curinfo;//이 구조체의 
	memset(&curinfo, 0, sizeof(curinfo));//메모리를 초기화
	switch (type) {
	case NOCURSOR:
		curinfo.dwSize = 1;
		curinfo.bVisible = FALSE;
		break;
	case SOLID_CURSOR:
		curinfo.dwSize = 100;
		curinfo.bVisible = TRUE;
		break;
	case NORMAL_CURSOR:
		curinfo.dwSize = 20;
		curinfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

void fontcolor(FONT_COLOR color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}