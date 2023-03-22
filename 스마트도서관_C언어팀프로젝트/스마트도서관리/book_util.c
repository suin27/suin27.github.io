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
			printf("1. ���� ����\n");
			book_read();
			break;
		case MA_SERACH:
			printf("2. ���� �˻�\n");//������
			book_search();
			break;
		case MA_LOAN:
			printf("3. ���� �뿩\n");//������
			view_book_loan();
			break;
		case MA_RETURN:
			printf("4. ���� �ݳ�\n");//������
			return_view_book_loan();
			break;
		case MA_CHU:
			printf("5. ���� ��õ\n");//�輺��
			book_suggestion();
			break;
		case MA_BUY:
			printf("6. ���� ����\n");//�ڼ���
			book_lib_buy();
			break;
		case MA_REGISTER:
			printf("7. ���� ����\n");//�޴�2�� �ҷ���. //�޴��� �ٸ��� �޴�2�� �߰��� ���� ��ü�� ����� �߰���.
			re_menu();
			break;
		case MA_EXIT://7�� ����(EXIT)�̳� �޴� ��� �ϳ��� ���鼭 �ӽ÷� DEL�� ����� ���_�޴� 1������
			printf("0. ���� �����մϴ�.\n");
			exit(0);
		default:
			printf(" �޴��� ��� ���� �Է��߽��ϴ�.\n");
			printf(" �ٽ� �Է��ϼ���.\n");
			rewind(stdin);
		}
		system("pause");//�ý��� �Լ�
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
				printf("1. ���� ����\n");
				book_read();
			case MA_SERACH:
				printf("2. ���� �˻�\n");
				book_search();
				break;
			case MA_LOAN:
				printf("3. ���� �뿩\n");
				view_book_loan();
				break;
			case MA_RETURN:
				printf("4. ���� �ݳ�\n");
				return_view_book_loan();
				break;
			case MA_CHU:
				printf("5. ���� ��õ\n");
				book_suggestion();
				break;
			case MA_BUY:
				printf("6. ���� ����\n");
				book_lib_buy();
				break;
			case MA_ADD://�޴� ����� �ϳ��� ����ϱ⿡ ���⼭�� ������尡 �ƴ� ���� - ���� �߰� �̴�.
				printf("7. ���� �߰�\n");//�ٰ���.
				book_lib_input();
				break;
			case MA_DEL:
				printf("8. ���� ����\n");//������
				delete_file();
				break;
			case MA_REFAIR:
				printf("9. ���� ����\n");//������
				edit_file();
				break;
			case MA_READ:
				printf("10. ��ü�� ����\n");
				w_book();
				break;
			case MA_MORE :
				printf("11. ������ �߰�\n");
				cert_w();
				break;
			case MA_EXIT:
				printf("������ �޴��� �����ϰ� �Ϲ� ����� �޴��� �ҷ��ɴϴ�.\n");
				return;
			default:
				printf("�޴��� ��� ���� �Է��߽��ϴ�.\n");
				printf("�ٽ� �Է��ϼ���.\n");
				rewind(stdin);
			}
			system("pause");//�ý��� �Լ�
			system("cls");
		}
	}
	else {
		printf("������ �α��ο� �����߽��ϴ�.\n");
	}
}
void book_write(LIB lb) {
	FILE* fp = NULL;
	fp = fopen("book.txt", "a");
	if (fp == NULL) {
		printf("������ ������ �� �����ϴ�.\n");
		return;
	}
	fwrite(&lb, sizeof(lb), 1, fp);
	fclose(fp);
}
void book_read() {
	printf("��ü ���� ���� ����� 1��\n");
	printf("�뿩 ���� ���� ����� 2��\n");
	printf("�뿩��(�뿩�Ұ�) ���� ����� 3��\n");
	int n1;
	scanf("%d", &n1);
	if (n1 == 1) {
		FILE* fpr = NULL;
		fpr = fopen("book.txt", "r");
		if (fpr == NULL) {
			printf("������ ���� �� �����ϴ�.\n");
			return;
		}
		printf("�����͸� ã�� �� ������ ����� �����ϴ�.\n");
		system("cls");
		LIB lb = { 0, };
		printf("=================================\n");
		int cot = 1;
		while (fread(&lb, sizeof(lb), 1, fpr) == 1) {
			printf("%d��° ����\n", cot);
			lib_lb_show(lb);
			cot++;
		}
		fclose(fpr);
	}
	else if (n1 == 2) {
		FILE* fpr = NULL;
		fpr = fopen("book.txt", "r");
		if (fpr == NULL) {
			printf("������ ���� �� �����ϴ�.\n");
			return;
		}
		printf("�����͸� ã�� �� �����ϴ�.\n");
		LIB lb = { 0, };
		printf("=================================\n");
		int cot = 1;
		while (fread(&lb, sizeof(lb), 1, fpr) == 1) {
			if (lb.book.loan == 0||lb.book.loan==2) {
				printf("%d��° ����\n", cot);
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
			printf("������ ���� �� �����ϴ�.\n");
			return;
		}
		printf("�����͸� ã�� �� ������ ����� �����ϴ�.\n");
		LIB lb = { 0, };
		printf("=================================\n");
		int cot = 1;
		while (fread(&lb, sizeof(lb), 1, fpr) == 1) {
			if (lb.book.loan == 1) {
				printf("%d��° ����\n", cot);
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
		printf("������ ���� �� �����ϴ�.\n");
		return;
	}
	LIB lbb = { 0, };
	//printf(" ���������� ���ٸ� \n	��µ� �����ϴ�\n");
	//printf(" ���� ������ ����մϴ�\n");
	printf(" �����ϰ� ���� ���� ������ �˻��ϼ��� : ");
	getchar();
	gets_s(lbb.buybook.name, sizeof(char) * 100);
	LIB lb = { 0, };
	printf("=================================\n");
	int cot = 1;
	while (fread(&lb, sizeof(lb), 1, fbr) == 1) {
		if(strcmp(lbb.buybook.name, lb.book.name) == 0) {
			printf("%s ������ %s ����Ʈ���� %d ���� �������� �����Ͻ� �� �ֽ��ϴ�.\n", lb.book.name, lb.buybook.site, lb.buybook.price);
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
				printf("������ �����ϴ�.\n");//�۵� Ȯ�� �� ���� ����
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
					printf("��õ�ϴ� å�� %s�Դϴ�.\n", array[i].book.name);
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
			printf("ī�װ��� �Է����ּ���.\n");
			getchar();
			gets_s(cate_e, sizeof(char) * 100);
			FILE* fp = NULL;
			fp = fopen("book.txt", "r");
			if (fp == NULL)
			{
				printf("������ �����ϴ�.\n");//�۵� Ȯ�� �� ���� ����
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
					printf("��õ�ϴ� å�� %s�Դϴ�.\n", array[i].book.name);
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
			printf("���ڸ� �Է����ּ���.\n");
			getchar();
			gets_s(writer, sizeof(char) * 100);
			FILE* fp = NULL;
			fp = fopen("book.txt", "r");
			if (fp == NULL)
			{
				printf("������ �����ϴ�.\n");//�۵� Ȯ�� �� ���� ����
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
					printf("��õ�ϴ� å�� %s�Դϴ�.\n", array[i].book.name);
				}
			}
			system("pause");
			system("cls");
			break;
		}
		case 0:
		{
			printf("0. ���ư���\n");
			system("cls");
			return;
		}
		default:
		{
			printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ֽʽÿ�. \n");
			rewind(stdin);
		}
		system("pause");
		system("cls");
		}
	}
}
int sug_menu() {
	printf("=============================\n");
	printf("���� ��õ\n");
	printf("=============================\n");
	printf("1. �α� ���� ��õ\n");
	printf("2. ī�װ� ��õ\n");
	printf("3. ���� ��õ\n");
	printf("0. ���θ޴��� ���Ʊ��\n");
	printf("=============================\n");
	printf("�޴��� �����ϼ��� : ");
	int menu = -1;
	scanf("%d", &menu);
	return menu;
}
void search_count(char* name)
{
	FILE* fp = fopen("book.txt", "r");
	if (fp == NULL)
	{
		printf("������ �����ϴ�\n");//�۵� Ȯ�� �� ���� ����
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
			printf("%d ������ %d�� ���� ���Դϴ�...\n", n, sp2[i].book.search_num);//�۵� Ȯ�� �� ���� ����
			found = 1;
		}
		i++;
	}
	fclose(fp);
	if (found == 0)
	{
		printf("�߸� �Է��ϼ̽��ϴ�. �ٽ� �Է����ֽʽÿ�. \n");
		rewind(stdin);
	}
	else
	{
		FILE* fps = fopen("book.txt", "w");
		if (fps == NULL)
		{
			printf("������ �����ϴ�\n");//�۵� Ȯ�� �� ���� ����
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