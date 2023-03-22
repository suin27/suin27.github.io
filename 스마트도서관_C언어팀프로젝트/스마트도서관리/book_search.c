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

	printf("�˻��� ����� �����ϼ���.\n");
	printf("1. ���� ����\n");
	printf("2. ����\n");
	printf("3. ���ǻ�\n");

	printf("���� : ");
	scanf("%d", &enter);

	if (enter == 1) {
		rewind(stdin);
		printf("�˻��� ���� ������ �Է��ϼ���.\n");
		scanf("%[^\n]s", user_find);
		book_search_list(user_find, 1);
		search_count(user_find);

		if (strlen(user_find) == 0) {
			printf("�ٽ� �Է��ϼ���.");
		}
	}
	else if (enter == 2) {
		rewind(stdin);
		printf("�˻��� ���ڸ� �Է��ϼ���.\n");
		scanf("%[^\n]s", user_find);
		book_search_list(user_find, 2);

		if (strlen(user_find) == 0) {
			printf("�ٽ� �Է��ϼ���.");
		}
	}
	else if (enter == 3) {
		rewind(stdin);
		printf("�˻��� ���ǻ縦 �Է��ϼ���.\n");
		scanf("%[^\n]s", user_find);
		book_search_list(user_find, 3);

		if (strlen(user_find) == 0) {
			printf("�ٽ� �Է��ϼ���.");
		}
	}
}

void book_search_list(char* enter, int num) {

	FILE* fpr = fopen("book.txt", "r");
	if (fpr == NULL) {
		printf("������ ���� �� �����ϴ�.\n");
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
			printf("������ ã�� �� �����ϴ�.\n");
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
			printf("������ ã�� �� �����ϴ�.\n");
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
			printf("������ ã�� �� �����ϴ�.\n");
		}
	}
	fclose(fpr);
}
