#include "crt.h"
#include<stdio.h>
#include "menu.h"
int main_menu() {
	printf("=================================\n");
	printf(" 도서 관리 App v1.2\n");
	printf("=================================\n");
	printf(" 1. 도서 정보\n");
	printf(" 2. 도서 검색\n");
	printf(" 3. 도서 대여\n");
	printf(" 4. 도서 반납\n");
	printf(" 5. 도서 추천\n");
	printf(" 6. 도서 구매\n");
	printf(" 7. 도서 관리\n");
	printf(" 0. 종료\n");
	printf("=================================\n");
	printf(" 메뉴를 선택하세요 : ");
	int menu = -1;
	scanf("%d", &menu);
	return menu;
}