#include "crt.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "lib.h"
#include "book_search.h"
#include "book_util.h"


void book_search()
{
	int enter = 0;
	char user_find[100] = { 0, };

	BOOK JB = { 0, };

	printf("검색할 방법을 선택하세요.\n");
	printf("1. 도서 제목\n");
	printf("2. 저자\n");
	printf("3. 출판사\n");

	printf("선택 : ");
	scanf("%d", &enter);

	if (enter == 1) {
		rewind(stdin);
		printf("검색할 도서 제목을 입력하세요.\n");
		scanf("%[^\n]s", user_find);
		book_search_list(user_find, 1);
		search_count(user_find);

		if (strlen(user_find) == 0) {
			printf("다시 입력하세요.");
		}
	}
	else if (enter == 2) {
		rewind(stdin);
		printf("검색할 저자를 입력하세요.\n");
		scanf("%[^\n]s", user_find);
		book_search_list(user_find, 2);

		if (strlen(user_find) == 0) {
			printf("다시 입력하세요.");
		}
	}
	else if (enter == 3) {
		rewind(stdin);
		printf("검색할 출판사를 입력하세요.\n");
		scanf("%[^\n]s", user_find);
		book_search_list(user_find, 3);

		if (strlen(user_find) == 0) {
			printf("다시 입력하세요.");
		}
	}
}

void book_search_list(char* enter, int num) {

	FILE* fpr = fopen("book.txt", "r");
	if (fpr == NULL) {
		printf("파일을 읽을 수 없습니다.\n");
		return;
	}

	LIB src = { 0, };
	static LIB dest[256] = { 0, };

	int find = 1;

	if (num == 1) {
		while (fread(&src, sizeof(LIB), 1, fpr) == 1) {
			if (strcmp(src.book.name, enter) == 0) {
				src.book.search_num++;
				lib_lb_show(src);
				find = 0;
				
			}
		}
		if (find == 1) {
			printf("내용을 찾을 수 없습니다.\n");
		}
	}
	else if (num == 2) {
		while (fread(&src, sizeof(LIB), 1, fpr) == 1) {
			if (strcmp(src.book.writer, enter) == 0) {
				src.book.search_num++;
				lib_lb_show(src);
				find = 0;
			}
		}
		if (find == 1) {
			printf("내용을 찾을 수 없습니다.\n");
		}
	}
	else if (num == 3) {
		while (fread(&src, sizeof(LIB), 1, fpr) == 1) {
			if (strcmp(src.book.public, enter) == 0) {
				src.book.search_num++;
				lib_lb_show(src);
				find = 0;
			}
		}
		if (find == 1) {
			printf("내용을 찾을 수 없습니다.\n");
		}
	}
	fclose(fpr);
}
