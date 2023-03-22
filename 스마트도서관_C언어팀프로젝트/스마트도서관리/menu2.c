#include "crt.h"
#include<stdio.h>
#include "menu.h"
int main_menu2() {
	printf("=================================\n");
	printf(" 도서 관리 App v1.0\n");
	printf("=================================\n");
	printf(" 1. 도서 정보\n");
	printf(" 2. 도서 검색\n");
	printf(" 3. 도서 대여\n");
	printf(" 4. 도서 반납\n");
	printf(" 5. 도서 추천\n");
	printf(" 6. 도서 구매\n");
	printf(" 7. 도서 추가\n");
	printf(" 8. 도서 삭제\n");
	printf(" 9. 도서 수정\n");
	printf(" 10. 연체자 정보\n");
	printf(" 0. 종료\n");
	printf("=================================\n");
	printf(" 메뉴를 선택하세요 : ");
	int menu2 = -1;
	scanf("%d", &menu2);
	return menu2;
}