#include "crt.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "book_util.h"
#include "lib.h"
#include "menu.h"
#include "register.h"
#include "book_search.h"
#include "loan_and_return.h"
#include "book_delete.h"
#include "where_book.h"
void start_menu() {
	system("cls");
	while (1) {
		switch (main_menu()) {
		case MA_LOOK :
			printf("1. 도서 정보\n");
			book_read();
			break;
		case MA_SERACH:
			printf("2. 도서 검색\n");//전병조
			book_search();
			break;
		case MA_LOAN:
			printf("3. 도서 대여\n");//김종욱
			view_book_loan();
			break;
		case MA_RETURN:
			printf("4. 도서 반납\n");//김종욱
			return_view_book_loan();
			break;
		case MA_CHU:
			printf("5. 도서 추천\n");//김성혜
			book_suggestion();
			break;
		case MA_BUY:
			printf("6. 도서 구매\n");//박수인
			book_lib_buy();
			break;
		case MA_REGISTER:
			printf("7. 도서 관리\n");//메뉴2를 불러옴. //메뉴와 다르게 메뉴2는 추가와 삭제 연체자 목록이 추가됨.
			re_menu();
			break;
		case MA_EXIT://7번 종료(EXIT)이나 메뉴 헤더 하나로 쓰면서 임시로 DEL을 종료로 사용_메뉴 1에서만
			printf("0. 앱을 종료합니다.\n");
			exit(0);
		default:
			printf(" 메뉴를 벗어난 수를 입력했습니다.\n");
			printf(" 다시 입력하세요.\n");
			rewind(stdin);
		}
		system("pause");//시스템 함수
		system("cls");
	}
}
void re_menu() {
	
	int comp = 0;
	comp = cert_r();
	system("cls");
	if (comp == 2) {
		start_menu();
	}
	else if (comp == 1) {
		while (1) {
			switch (main_menu2()) {
			case MA_LOOK :
				printf("1. 도서 정보\n");
				book_read();
			case MA_SERACH:
				printf("2. 도서 검색\n");
				book_search();
				break;
			case MA_LOAN:
				printf("3. 도서 대여\n");
				view_book_loan();
				break;
			case MA_RETURN:
				printf("4. 도서 반납\n");
				return_view_book_loan();
				break;
			case MA_CHU:
				printf("5. 도서 추천\n");
				book_suggestion();
				break;
			case MA_BUY:
				printf("6. 도서 구매\n");
				book_lib_buy();
				break;
			case MA_ADD://메뉴 헤더를 하나로 사용하기에 여기서는 관리모드가 아닌 관리 - 도서 추가 이다.
				printf("7. 도서 추가\n");//다같이.
				book_lib_input();
				break;
			case MA_DEL:
				printf("8. 도서 삭제\n");//전병주
				delete_file();
				break;
			case MA_REFAIR:
				printf("9. 정보 수정\n");//전병주
				edit_file();
				break;
			case MA_READ:
				printf("10. 연체자 정보\n");
				w_book();
				break;
			case MA_MORE :
				printf("11. 관리자 추가\n");
				cert_w();
				break;
			case MA_EXIT:
				printf("관리자 메뉴를 종료하고 일반 사용자 메뉴를 불러옵니다.\n");
				return;
			default:
				printf("메뉴를 벗어난 수를 입력했습니다.\n");
				printf("다시 입력하세요.\n");
				rewind(stdin);
			}
			system("pause");//시스템 함수
			system("cls");
		}
	}
	else {
		printf("관리자 로그인에 실패했습니다.\n");
	}
}
void book_write(LIB lb) {
	FILE* fp = NULL;
	fp = fopen("book.txt", "a");
	if (fp == NULL) {
		printf("파일을 생성할 수 없습니다.\n");
		return;
	}
	fwrite(&lb, sizeof(lb), 1, fp);
	fclose(fp);
}
void book_read() {
	printf("전체 도서 정보 출력은 1번\n");
	printf("대여 가능 도서 출력은 2번\n");
	printf("대여중(대여불가) 도서 출력은 3번\n");
	int n1;
	scanf("%d", &n1);
	if (n1 == 1) {
		FILE* fpr = NULL;
		fpr = fopen("book.txt", "r");
		if (fpr == NULL) {
			printf("파일을 읽을 수 없습니다.\n");
			return;
		}
		printf("데이터를 찾을 수 없으면 출력이 없습니다.\n");
		system("cls");
		LIB lb = { 0, };
		printf("=================================\n");
		int cot = 1;
		while (fread(&lb, sizeof(lb), 1, fpr) == 1) {
			printf("%d번째 도서\n", cot);
			lib_lb_show(lb);
			cot++;
		}
		fclose(fpr);
	}
	else if (n1 == 2) {
		FILE* fpr = NULL;
		fpr = fopen("book.txt", "r");
		if (fpr == NULL) {
			printf("파일을 읽을 수 없습니다.\n");
			return;
		}
		printf("데이터를 찾을 수 없습니다.\n");
		LIB lb = { 0, };
		printf("=================================\n");
		int cot = 1;
		while (fread(&lb, sizeof(lb), 1, fpr) == 1) {
			if (lb.book.loan == 0||lb.book.loan==2) {
				printf("%d번째 도서\n", cot);
				lib_lb_show(lb);
				cot++;
			}
		}
		fclose(fpr);
	}
	else if (n1 == 3) {
		FILE* fpr = NULL;
		fpr = fopen("book.txt", "r");
		if (fpr == NULL) {
			printf("파일을 읽을 수 없습니다.\n");
			return;
		}
		printf("데이터를 찾을 수 없으면 출력이 없습니다.\n");
		LIB lb = { 0, };
		printf("=================================\n");
		int cot = 1;
		while (fread(&lb, sizeof(lb), 1, fpr) == 1) {
			if (lb.book.loan == 1) {
				printf("%d번째 도서\n", cot);
				lib_lb_show(lb);
				cot++;
			}
		}
		fclose(fpr);
	}
}
void book_lib_buy() {
	FILE* fbr = NULL;
	fbr = fopen("book.txt", "r");
	if (fbr == NULL) {
		printf("파일을 읽을 수 없습니다.\n");
		return;
	}
	LIB lbb = { 0, };
	//printf(" 도서정보가 없다면 \n	출력도 없습니다\n");
	//printf(" 도서 정보를 출력합니다\n");
	printf(" 구매하고 싶은 도서 제목을 검색하세요 : ");
	getchar();
	gets_s(lbb.buybook.name, sizeof(char) * 100);
	LIB lb = { 0, };
	printf("=================================\n");
	int cot = 1;
	while (fread(&lb, sizeof(lb), 1, fbr) == 1) {
		if(strcmp(lbb.buybook.name, lb.book.name) == 0) {
			printf("%s 도서는 %s 사이트에서 %d 원의 가격으로 구매하실 수 있습니다.\n", lb.book.name, lb.buybook.site, lb.buybook.price);
		}
	}
	fclose(fbr);
}
void book_suggestion()
{
	system("cls");
	while (1)
	{
		switch (sug_menu())
		{
		case 1:
		{
			LIB sugg1 = { 0, };
			LIB sugg2 = { 0, };
			LIB sugg3 = { 0, };
			LIB array[5] = { 0, };
			FILE* fp = NULL;
			fp = fopen("book.txt", "r");
			if (fp == NULL)
			{
				printf("파일이 없습니다.\n");//작동 확인 후 지울 예정
				return;
			}
			while (fread(&sugg1, sizeof(LIB), 1, fp) == 1)
			{
				if (sugg1.book.search_num > array[4].book.search_num)
				{
					sugg2.book.search_num = sugg1.book.search_num;
					strcpy(sugg2.book.name, sugg1.book.name);
					sugg1.book.search_num = array[4].book.search_num;
					strcpy(sugg1.book.name, array[4].book.name);
					array[4].book.search_num = sugg2.book.search_num;
					strcpy(array[4].book.name, sugg2.book.name);
					for (int i = 4; i > 0; i--)
					{
						for (int j = 3; j >= 0; j--)
						{
							if (array[i].book.search_num > array[j].book.search_num)
							{
								sugg3.book.search_num = array[i].book.search_num;
								strcpy(sugg3.book.name, array[i].book.name);
								array[i].book.search_num = array[j].book.search_num;
								strcpy(array[i].book.name, array[j].book.name);
								array[j].book.search_num = sugg3.book.search_num;
								strcpy(array[j].book.name, sugg3.book.name);
							}
						}
					}
				}
			}
			fclose(fp);
			for (int i = 4; i >= 0; i--)
			{
				if (strcmp(array[i].book.name, "") != 0)
				{
					printf("추천하는 책은 %s입니다.\n", array[i].book.name);
				}
			}
			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			char cate_e[100];
			LIB sugg1 = { 0, };
			LIB sugg2 = { 0, };
			LIB sugg3 = { 0, };
			LIB array[5] = { 0, };
			printf("카테고리를 입력해주세요.\n");
			getchar();
			gets_s(cate_e, sizeof(char) * 100);
			FILE* fp = NULL;
			fp = fopen("book.txt", "r");
			if (fp == NULL)
			{
				printf("파일이 없습니다.\n");//작동 확인 후 지울 예정
				return;
			}
			while (fread(&sugg1, sizeof(LIB), 1, fp) == 1)
			{
				if (strcmp(sugg1.book.cate, cate_e) == 0)
				{
					if (sugg1.book.search_num > array[4].book.search_num)
					{
						sugg2.book.search_num = sugg1.book.search_num;
						strcpy(sugg2.book.name, sugg1.book.name);
						sugg1.book.search_num = array[4].book.search_num;
						strcpy(sugg1.book.name, array[4].book.name);
						array[4].book.search_num = sugg2.book.search_num;
						strcpy(array[4].book.name, sugg2.book.name);
						for (int i = 4; i > 0; i--)
						{
							for (int j = 3; j >= 0; j--)
							{
								if (array[i].book.search_num > array[j].book.search_num)
								{
									sugg3.book.search_num = array[i].book.search_num;
									strcpy(sugg3.book.name, array[i].book.name);
									array[i].book.search_num = array[j].book.search_num;
									strcpy(array[i].book.name, array[j].book.name);
									array[j].book.search_num = sugg3.book.search_num;
									strcpy(array[j].book.name, sugg3.book.name);
								}
							}
						}
					}
				}
			}
			fclose(fp);
			for (int i = 4; i >= 0; i--)
			{
				if (strcmp(array[i].book.name, "") != 0)
				{
					printf("추천하는 책은 %s입니다.\n", array[i].book.name);
				}
			}
			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			char writer[100];
			LIB sugg1 = { 0, };
			LIB sugg2 = { 0, };
			LIB sugg3 = { 0, };
			LIB array[5] = { 0, };
			printf("저자를 입력해주세요.\n");
			getchar();
			gets_s(writer, sizeof(char) * 100);
			FILE* fp = NULL;
			fp = fopen("book.txt", "r");
			if (fp == NULL)
			{
				printf("파일이 없습니다.\n");//작동 확인 후 지울 예정
				return;
			}
			while (fread(&sugg1, sizeof(LIB), 1, fp) == 1)
			{
				if (strcmp(sugg1.book.writer, writer) == 0)
				{
					if (sugg1.book.search_num > array[4].book.search_num)
					{
						sugg2.book.search_num = sugg1.book.search_num;
						strcpy(sugg2.book.name, sugg1.book.name);
						sugg1.book.search_num = array[4].book.search_num;
						strcpy(sugg1.book.name, array[4].book.name);
						array[4].book.search_num = sugg2.book.search_num;
						strcpy(array[4].book.name, sugg2.book.name);
						for (int i = 4; i > 0; i--)
						{
							for (int j = 3; j >= 0; j--)
							{
								if (array[i].book.search_num > array[j].book.search_num)
								{
									sugg3.book.search_num = array[i].book.search_num;
									strcpy(sugg3.book.name, array[i].book.name);
									array[i].book.search_num = array[j].book.search_num;
									strcpy(array[i].book.name, array[j].book.name);
									array[j].book.search_num = sugg3.book.search_num;
									strcpy(array[j].book.name, sugg3.book.name);
								}
							}
						}
					}
				}
			}
			fclose(fp);
			for (int i = 4; i >= 0; i--)
			{
				if (strcmp(array[i].book.name, "") != 0)
				{
					printf("추천하는 책은 %s입니다.\n", array[i].book.name);
				}
			}
			system("pause");
			system("cls");
			break;
		}
		case 0:
		{
			printf("0. 돌아가기\n");
			system("cls");
			return;
		}
		default:
		{
			printf("잘못 입력하셨습니다. 다시 입력해주십시오. \n");
			rewind(stdin);
		}
		system("pause");
		system("cls");
		}
	}
}
int sug_menu() {
	printf("=============================\n");
	printf("도서 추천\n");
	printf("=============================\n");
	printf("1. 인기 도서 추천\n");
	printf("2. 카테고리 추천\n");
	printf("3. 저자 추천\n");
	printf("0. 메인메뉴로 돌아기기\n");
	printf("=============================\n");
	printf("메뉴를 선택하세요 : ");
	int menu = -1;
	scanf("%d", &menu);
	return menu;
}
void search_count(char* name)
{
	FILE* fp = fopen("book.txt", "r");
	if (fp == NULL)
	{
		printf("파일이 없습니다\n");//작동 확인 후 지울 예정
		return;
	}
	LIB sp1 = { 0, };
	LIB sp2[70] = { 0, };
	int i = 0;
	int found = 0;
	while (fread(&sp1, sizeof(LIB), 1, fp) == 1)
	{
		memcpy(&sp2[i], &sp1, sizeof(LIB));
		if (strcmp(name, sp1.book.name) == 0)
		{
			int n = sp2[i].book.search_num;
			sp2[i].book.search_num = sp2[i].book.search_num + 1;
			printf("%d 정보를 %d로 수정 중입니다...\n", n, sp2[i].book.search_num);//작동 확인 후 지울 예정
			found = 1;
		}
		i++;
	}
	fclose(fp);
	if (found == 0)
	{
		printf("잘못 입력하셨습니다. 다시 입력해주십시오. \n");
		rewind(stdin);
	}
	else
	{
		FILE* fps = fopen("book.txt", "w");
		if (fps == NULL)
		{
			printf("파일이 없습니다\n");//작동 확인 후 지울 예정
			return;
		}
		for (int i = 0; i < 70; i++)
		{
			if (strcmp(sp2[i].book.name, "") != 0)
			{
				fwrite(&sp2[i], sizeof(LIB), 1, fps);
			}
			else break;
		}
		fclose(fps);
		memset(sp2, 0, sizeof(LIB) * 70);
	}
}