#include "crt.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include "lib.h"
#include "book_util.h"
#include "book_delete.h"
void delete_file()
{
	char deletename[100] = { 0 };
	LIB dt[50] = { 0 };
	LIB cnf_t = { 0 };

	FILE* fpdelete = fopen("book.txt", "rt");
	if (fpdelete == NULL)
	{
		printf("������ ���� �� �����ϴ�.\n");
		return;
	}
	fread(&cnf_t, sizeof(cnf_t), 1, fpdelete);
	if (cnf_t.book.sn == 0)	// ������ ������ �ȿ� �����Ͱ� ������ Ż���ϱ� ���� �Լ�	
	{
		printf("�����͸� ã�� �� �����ϴ�.\n");
		fclose(fpdelete);
		return;
	}
	//fclose(fpdelete);
	//fpdelete = fopen("book.txt", "rt");

	rewind(fpdelete);

	printf("1. �˻� ����\n2. ��ü ����\n");
	int dt_select = 0;
	scanf(" %d", &dt_select);
	switch (dt_select)
	{
	case 1:
	{
		LIB dt_t = { 0 };
		int i = 0;
		int found = 0;	// ������ ���� ������ �Ǵ��ϱ� ���� ����ġ ����
		printf("������ ������ �̸��� �Է��ϼ��� : \n");
		getchar();
		gets_s(deletename, sizeof(deletename));
		while (fread(&dt_t, sizeof(dt_t), 1, fpdelete) == 1)
		{
			if (strcmp(deletename, dt_t.book.name) == 0)
			{
				printf("==================================\n");
				printf("���� ���� : %s\n", dt_t.book.name);			// å�̸�
				printf("���� ��ȣ : %d\n", dt_t.book.sn);			// ������ȣ
				printf("���� : %s\n", dt_t.book.writer);				// ����
				printf("���ǻ� : %s\n", dt_t.book.public);			// ���ǻ�											
				printf("==================================\n");
				found = 1;											// ����ġ����
			}
		}
		//fclose(fpdelete);										// �����ϱ���� �̸��� �˻��� ����ü�� ���
		rewind(fpdelete);
		i = 0;
		if (!found)
		{
			printf("������ ���� ������ ã�� �� �����ϴ�.\n");
			return;
		}
		found = 0;

		int delete_book_sn;		// ������ å���� �����ϱ� ���� ������ȣ�� �ٽ� �Է¹޾� ����
		printf("������ ���� ��ȣ�� �Է��ϼ���.\n");
		scanf("%d", &delete_book_sn);

		//fpdelete = fopen("book.txt", "rt");
		while (fread(&dt_t, sizeof(dt_t), 1, fpdelete) == 1)
		{
			if (delete_book_sn != dt_t.book.sn)
			{
				memcpy(&dt[i++], &dt_t, sizeof(LIB));
			}
			else
			{
				found = 1;
				printf("�˻��Ͻ� ���� ������ �����߽��ϴ�.\n");
			}
		}
		if (!found)
		{
			printf("������ ���� ������ ã�� �� �����ϴ�.\n");
			return;
		}

		fclose(fpdelete);

		fpdelete = fopen("book.txt", "wt");
		if (fpdelete == NULL)
		{
			printf("������ ������ �� �����ϴ�.\n");
			return;
		}

		for (i = 0; i < 256; i++)
		{
			if (strcmp(dt[i].book.name, "") != 0)
			{
				fwrite(&dt[i], sizeof(dt[i]), 1, fpdelete);
			}
			else
			{
				break;
			}
		}
		fclose(fpdelete);
		break;
	}

	case 2:
	{
		fclose(fpdelete);
		fpdelete = fopen("book.txt", "wt");
		if (fpdelete == NULL)
		{
			printf("������ ������ �� �����ϴ�.\n");
			return;
		}

		printf("��� ���� ����� �����߽��ϴ�.\n");

		fclose(fpdelete);
		break;
	}
	default:
		rewind(stdin);
		printf("�߸��� ������ �Դϴ�. �ٽ� �Է��ϼ���.\n");
	}
}

void edit_file()
{
	LIB cnf_t = { 0 };
	LIB ed_sn_check = { 0 };
	LIB edcheck = { 0 };
	int edit_book_sn;		// ������ å���� �����ϱ� ���� ������ȣ�� �ٽ� �Է�

	char edit_search_book[100] = { 0 };
	int found = 0;

	FILE* fpedit = NULL;
	fpedit = fopen("book.txt", "rt");
	if (fpedit == NULL)
	{
		printf("������ ���� �� �����ϴ�.\n");
		return;
	}
	fread(&cnf_t, sizeof(cnf_t), 1, fpedit);
	if (cnf_t.book.name == 0)	// ������ ������ �ȿ� �����Ͱ� ������ Ż���ϱ� ���� �Լ�	
	{
		printf("�����͸� ã�� �� �����ϴ�.\n");
		fclose(fpedit);
		return;
	}

	rewind(fpedit);
	//fclose(fpedit);
	//fpedit = fopen("book.txt", "rt");
	printf("�����ϰ��� �ϴ� ���� ������ �Է��ϼ���.\n"); // ���ʿ� å �̸��� Ʋ������ �ذ��� ��� �ʿ�.

	getchar();
	gets_s(edit_search_book, sizeof(edit_search_book));
	system("cls");

	while (fread(&edcheck, sizeof(LIB), 1, fpedit) == 1)
	{
		if (strcmp(edit_search_book, edcheck.book.name) == 0)		// ������ å�� ��� ����ϱ� ���� ����
		{
			printf("====================================\n");
			printf("���� ���� : %s\n", edcheck.book.name);			// å�̸�
			printf("���� ��ȣ : %d\n", edcheck.book.sn);				// ������ȣ
			printf("���� : %s\n", edcheck.book.writer);				// ����
			printf("���ǻ� : %s\n", edcheck.book.public);			// ���ǻ�	
			printf("====================================\n");
			found = 1;												// ����ġ���� // ������ å�� �˻��Ǿ��� �� ����ġ���� ��ȭ
		}
	}

	if (found == 1)	// ����ġ ������ ������ �� sn�� ���ϱ� ���� if��
	{
		found = 0;
		printf("������ ���� ��ȣ�� �Է��ϼ���.\n");
		scanf("%d", &edit_book_sn);
		rewind(fpedit);
		while (fread(&ed_sn_check, sizeof(LIB), 1, fpedit) == 1)
		{
			if ((strcmp(edit_search_book, ed_sn_check.book.name) == 0) && (edit_book_sn == ed_sn_check.book.sn))
			{
				found = 1;
			}
		}
	}

	if (!found)	// �˻��� �̸��� å�� ã�� ���߰ų�, �˻��� �̸��� å�� �־ ��å�� sn�� �Է��� sn�� �ٸ� ��� ��µ� ����
	{
		printf("������ ���� ������ ã�� �� �����ϴ�.\n");
		return;
	}
	fclose(fpedit);

	edit_menu(edit_search_book, edit_book_sn);
}

void edit_menu(char edit_search_book[100], int edit_book_sn)
{
	system("cls");
	printf("�����ϰ��� �ϴ� ������ ������ �����ϼ���.\n");
	printf("1. ��� ���� ����\n");
	printf("2. ���� ���� ����\n");
	printf("3. �뿩�� ���� ����(�뿩 ���� ����)\n");
	printf("4. ���� ���� ����\n");
	printf("5. ��ȭ ���� ����(��ȭ ���� ����)\n");
	printf("0. ���ư���\n");
	int edit_menu_all = -1;
	scanf("%d", &edit_menu_all);
	system("cls");

	FILE* fpedit = NULL;
	fpedit = fopen("book.txt", "rt");
	int idx = 0;
	LIB dest[50] = { 0 };
	LIB ed = { 0 };
	rewind(fpedit);

	while (fread(&ed, sizeof(LIB), 1, fpedit) == 1)
	{
		memcpy(&dest[idx], &ed, sizeof(LIB));		// �о�� ed���θ� dest[idx]�� ����
		if (strcmp(edit_search_book, ed.book.name) == 0 && edit_book_sn == ed.book.sn)
		{
			switch (edit_menu_all)
			{
			case 1:
				printf("��� ���� ������ �����ϼ̽��ϴ�.\n");
				// å ����
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� ���� ������ �Է��ϼ���.\n");
				getchar();
				gets_s(dest[idx].book.name, sizeof(dest[idx].book.name));
				system("cls");
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� ���� ��ȣ�� �Է��ϼ���.\n");		// �̹� �ִ� ������ȣ�� �����ϸ� �ȵǰ� �ؾ���.
				
				scanf("%d", &edit_book_sn);
				int sn1 = dest[idx].book.sn;
				sn1 = sn_overlap_no(sn1);
				dest[idx].book.sn = sn1;
				system("cls");
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� ���ڸ� �Է��ϼ���.\n");
				scanf("%s", dest[idx].book.writer);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� ���ǻ縦 �Է��ϼ���.\n");
				scanf("%s", dest[idx].book.public);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� ī�װ��� �Է��ϼ���.\n");
				scanf("%s", dest[idx].book.cate);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� �˻� Ƚ���� �Է��ϼ���.\n");
				scanf("%d", &dest[idx].book.search_num);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� �뿩 ������ �Է��ϼ���.\n");
				printf("1. YES\n2. NO\n");
				scanf("%d", &dest[idx].book.loan);
				system("cls");
				if (dest[idx].book.loan == 1)	// �뿩�� ������ �ٲ�������� �뿩�� ����ü ���� ����?
				{
					// �뿩�� ����
					//printf("�뿩 ������ ���� ������ �����մϴ�.\n");
					strcpy(dest[idx].user.bookname, dest[idx].book.name);
					edit_printf_all(dest[idx]);
					printf("���� �ٲ� �뿩���� �̸��� �Է��ϼ���.\n");
					scanf("%s", dest[idx].user.username);
					system("cls");
					edit_printf_all(dest[idx]);
					printf("���� �ٲ� �뿩���� ��ȭ ��ȣ�� �Է��ϼ���.\n");
					scanf("%d", &dest[idx].user.user_number);
					system("cls");
				}
				else if (dest[idx].book.loan == 2)
				{
					printf("���� ���� ������ �뿩 ���� ���°� �ƴմϴ�. �ش� ������ �뿩 ������ �ʱ�ȭ �մϴ�.\n");
					memset(&dest[idx].user, 0, sizeof(USER));
				}
				else
				{
					rewind(stdin);
					printf("�߸� �Է��ϼ̽��ϴ�.\n");
					break;
				}
				// ���� ����
				//printf("���� ������ ���� ������ �����մϴ�.\n");
				strcpy(dest[idx].buybook.name, dest[idx].book.name);
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� å�� ���� ����Ʈ�� �Է��ϼ���.\n");
				scanf("%s", dest[idx].buybook.site);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� å�� ���� ������ �Է��ϼ���.\n");
				scanf("%d", &dest[idx].buybook.price);
				system("cls");
				// ��ȭ ����
				edit_printf_all(dest[idx]);
				printf("���� �ٲ� ��ȭ ������ �Է��ϼ���.\n");
				printf("1. YES\n2. NO\n");
				scanf("%d", &dest[idx].book.movie_search);
				system("cls");
				if (dest[idx].book.movie_search == 1)
				{
					// ��ȭ ����
					edit_printf_all(dest[idx]);
					printf("���� �ٲ� ��ȭ ������ �Է��ϼ���.\n");
					getchar();
					gets_s(dest[idx].movie.name, sizeof(dest[idx].movie.name));
					system("cls");
					edit_printf_all(dest[idx]);
					printf("���� �ٲ� ��ȭ ���� �̸��� �Է��ϼ���.\n");
					scanf("%s", dest[idx].movie.producer);
					system("cls");
					edit_printf_all(dest[idx]);
					printf("���� �ٲ� ��ȭ ��û ����Ʈ�� �Է��ϼ���.\n");
					scanf("%s", dest[idx].movie.site);
					system("cls");
					edit_printf_all(dest[idx]);
					printf("���� �ٲ� ��ȭ ������ �Է��ϼ���.\n");
					scanf("%d", &dest[idx].movie.price);
					system("cls");
				}
				else if (dest[idx].book.movie_search == 2)
				{
					printf("���� ���� ������ ��ȭ�� �����ϴ�. �ش� ������ ��ȭ ������ �ʱ�ȭ �մϴ�.\n");
					memset(&dest[idx].movie, 0, sizeof(MOVIE));	// ��ȭ�� ���� �����ϰ�� ��ȭ���������� �����ʰ� 0���� �ʱ�ȭ
				}
				else
				{
					rewind(stdin);
					printf("�߸� �Է��ϼ̽��ϴ�.\n");
					break;
				}
				break;
			case 2:												// ���� ���� ���� ����ġ��
			{
				printf("���� ���� ������ �����ϼ̽��ϴ�.\n");
				edit_printf_book(dest[idx]);
				printf("���� �޴��� �����ϼ���.\n");
				printf("1. ���� ���� ����\n");
				printf("2. ���� ��ȣ ����\n");
				printf("3. ���� ����\n");
				printf("4. ���ǻ� ����\n");
				printf("5. ī�װ� ����\n");
				printf("6. �˻� Ƚ�� ����\n");
				printf("7. ���� ���� ��� ����\n");
				printf("0. ���ư���\n");
				int edit_menu_book = -1;
				scanf("%d", &edit_menu_book);
				system("cls");
				switch (edit_menu_book)
				{
				case 1:
					printf("1. ���� ���� ����\n");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� å�� �̸��� �Է��ϼ���.\n");
					getchar();
					gets_s(dest[idx].book.name, sizeof(dest[idx].book.name));
					strcpy(dest[idx].buybook.name, dest[idx].book.name);		// ���� �Է��� å �̸��� ���� ������ ����
					system("cls");
					break;
				case 2:
					printf("2. ���� ��ȣ ����\n");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� ���� ��ȣ�� �Է��ϼ���.\n");
					scanf("%d", &dest[idx].book.sn);
					int sn1 = dest[idx].book.sn;
					sn1 = sn_overlap_no(sn1);
					dest[idx].book.sn = sn1;
					system("cls");
					break;
				case 3:
					printf("3. ���� ����\n");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� ���ڸ� �Է��ϼ���.\n");
					scanf("%s", dest[idx].book.writer);
					system("cls");
					break;
				case 4:
					printf("4. ���ǻ� ����\n");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� ���ǻ縦 �Է��ϼ���.\n");
					scanf("%s", dest[idx].book.public);
					system("cls");
					break;
				case 5:
					printf("5. ī�װ� ����\n");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� ī�װ��� �Է��ϼ���.\n");
					scanf("%s", dest[idx].book.cate);
					system("cls");
					break;
				case 6:
					printf("6. �˻� Ƚ�� ����\n");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� �˻� Ƚ���� �Է��ϼ���.\n");
					scanf("%d", &dest[idx].book.search_num);
					system("cls");
					break;
				case 7:
					printf("7. ���� ���� ��� ����\n");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� ���� ������ �Է��ϼ���.\n");
					getchar();
					gets_s(dest[idx].book.name, sizeof(dest[idx].book.name));
					strcpy(dest[idx].buybook.name, dest[idx].book.name);
					system("cls");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� ���� ��ȣ�� �Է��ϼ���.\n");
					scanf("%d", &dest[idx].book.sn);
					sn1 = dest[idx].book.sn;
					sn1 = sn_overlap_no(sn1);
					dest[idx].book.sn = sn1;
					system("cls");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� ���ڸ� �Է��ϼ���.\n");
					scanf("%s", dest[idx].book.writer);
					system("cls");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� ���ǻ縦 �Է��ϼ���.\n");
					scanf("%s", dest[idx].book.public);
					system("cls");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� ī�װ��� �Է��ϼ���.\n");
					scanf("%s", dest[idx].book.cate);
					system("cls");
					edit_printf_book(dest[idx]);
					printf("���� �ٲ� �˻� Ƚ���� �Է��ϼ���.\n");
					scanf("%d", &dest[idx].book.search_num);
					system("cls");
					break;
				case 0:
					printf("0. ���ư���\n");
					edit_menu(edit_search_book, edit_book_sn);

				default:
					
					printf("�߸� �Է��ϼ̽��ϴ�.");
					rewind(stdin);
				}
				break;
			}
			case 3:												// �뿩�� ���� ���� ����ġ��
			{
				printf("�뿩�� ���� ������ �����ϼ̽��ϴ�.\n");
				edit_printf_loan(dest[idx]);
				printf("������ ������ ���� �뿩 ���� ���¸� �Է��ϼ���.\n");
				printf("1. YES\n2. NO\n");
				scanf("%d", &dest[idx].book.loan);
				system("cls");
				if (dest[idx].book.loan == 1)
				{
					printf("���� �޴��� �����ϼ���.\n");
					edit_printf_loan(dest[idx]);
					printf("1. �뿩�� �̸� ����\n");
					printf("2. �뿩�� ��ȭ��ȣ ����\n");
					printf("3. �뿩�� ���� ��� ����\n");
					printf("0. ���ư���\n");
					int edit_menu_user = -1;
					scanf("%d", &edit_menu_user);
					system("cls");
					switch (edit_menu_user)
					{
					case 1:
						printf("1. �뿩�� �̸� ����\n");
						edit_printf_loan(dest[idx]);
						printf("���� �ٲ� �뿩���� �̸��� �Է��ϼ���.\n");
						getchar();
						gets_s(dest[idx].user.username, sizeof(dest[idx].user.username));
						system("cls");
						break;
					case 2:
						printf("2. �뿩�� ��ȭ��ȣ ����\n");
						edit_printf_loan(dest[idx]);
						printf("���� �ٲ� �뿩���� ��ȭ ��ȣ�� �Է��ϼ���.\n");
						scanf("%d", &dest[idx].user.user_number);
						system("cls");
						break;
					case 3:
						printf("3. �뿩�� ���� ��� ����\n");
						edit_printf_loan(dest[idx]);
						printf("���� �ٲ� �뿩���� �̸��� �Է��ϼ���.\n");
						getchar();
						gets_s(dest[idx].user.username, sizeof(dest[idx].user.username));
						system("cls");
						edit_printf_loan(dest[idx]);
						printf("���� �ٲ� �뿩���� ��ȭ ��ȣ�� �Է��ϼ���.\n");
						scanf("%d", &dest[idx].user.user_number);
						system("cls");
						break;
					case 0:
						printf("0. ���ư���\n");
						edit_menu(edit_search_book, edit_book_sn);
					default:
						rewind(stdin);
						printf("�߸� �Է��ϼ̽��ϴ�.\n");
					}
				}
				else if (dest[idx].book.loan == 2)
				{
					printf("���� ���� ������ �뿩 ���� ���°� �ƴմϴ�. �ش� ������ �뿩 ������ �ʱ�ȭ �մϴ�.\n");
					memset(&dest[idx].user, 0, sizeof(USER));
				}
				else
				{
					rewind(stdin);
					printf("�߸� �Է��ϼ̽��ϴ�.\n");
					break;
				}
				break;
			}
			case 4:												// ���� ���� ���� ����ġ��
			{
				printf("���� ���� ������ �����ϼ̽��ϴ�.\n");
				edit_printf_buybook(dest[idx]);
				printf("���� �޴��� �����ϼ���.\n");
				printf("1. ����Ʈ ����\n");
				printf("2. ���� ����\n");
				printf("3. ���� ���� ��� ����\n");
				printf("0. ���ư���\n");
				int edit_menu_buybook = -1;
				scanf("%d", &edit_menu_buybook);
				system("cls");
				switch (edit_menu_buybook)
				{
				case 1:
					printf("1. ����Ʈ ����\n");
					edit_printf_buybook(dest[idx]);
					printf("���� �ٲ� å�� ���� ����Ʈ�� �Է��ϼ���.\n");
					scanf("%s", dest[idx].buybook.site);
					system("cls");
					break;
				case 2:
					printf("2. ���� ����\n");
					edit_printf_buybook(dest[idx]);
					printf("���� �ٲ� å�� ���� ������ �Է��ϼ���.\n");
					scanf("%d", &dest[idx].buybook.price);
					system("cls");
					break;
				case 3:
					printf("3. ���� ���� ��� ����\n");
					edit_printf_buybook(dest[idx]);
					printf("���� �ٲ� å�� ���� ����Ʈ�� �Է��ϼ���.\n");
					scanf("%s", dest[idx].buybook.site);
					system("cls");
					edit_printf_buybook(dest[idx]);
					printf("���� �ٲ� å�� ���� ������ �Է��ϼ���.\n");
					scanf("%d", &dest[idx].buybook.price);
					system("cls");
					break;
				case 0:
					printf("0. ���ư���\n");
					edit_menu(edit_search_book, edit_book_sn);
				default:
					rewind(stdin);
					printf("�߸� �Է��ϼ̽��ϴ�.");
				}
				break;
			}
			case 5:												// ��ȭ ���� ���� ����ġ��
			{
				printf("��ȭ ���� ������ �����ϼ̽��ϴ�.\n");
				edit_printf_movie(dest[idx]);
				printf("������ ������ ���� ��ȭ ���� ���¸� �Է��ϼ���.\n");
				printf("1. YES\n2. NO\n");
				scanf("%d", &dest[idx].book.movie_search);
				system("cls");
				if (dest[idx].book.movie_search == 1)
				{
					printf("���� �޴��� �����ϼ���.\n");
					edit_printf_movie(dest[idx]);
					printf("1. ��ȭ ���� ����\n");
					printf("2. ���� ����\n");
					printf("3. ��ȭ ��û ����Ʈ ����\n");
					printf("4. ���� ����\n");
					printf("5. ��ȭ ���� ��� ����\n");
					printf("0. ���ư���\n");
					int edit_menu_movie = -1;
					scanf("%d", &edit_menu_movie);
					system("cls");
					switch (edit_menu_movie)
					{
					case 1:
						printf("1. ��ȭ ���� ����\n");
						edit_printf_movie(dest[idx]);
						printf("���� �ٲ� ��ȭ �̸��� �Է��ϼ���.\n");
						getchar();
						gets_s(dest[idx].movie.name, sizeof(dest[idx].movie.name));
						system("cls");
						break;
					case 2:
						printf("3. ���� ����\n");
						edit_printf_movie(dest[idx]);
						printf("���� �ٲ� ��ȭ ���� �̸��� �Է��ϼ���.\n");
						scanf("%s", dest[idx].movie.producer);
						system("cls");
						break;
					case 3:
						printf("2. ��ȭ ��û ����Ʈ ����\n");
						edit_printf_movie(dest[idx]);
						printf("���� �ٲ� ��ȭ ��û ����Ʈ�� �Է��ϼ���.\n");
						scanf("%s", dest[idx].movie.site);
						system("cls");
						break;
					case 4:
						printf("4. ���� ����\n");
						edit_printf_movie(dest[idx]);
						printf("���� �ٲ� ��ȭ ������ �Է��ϼ���.\n");
						scanf("%d", &dest[idx].movie.price);
						system("cls");
						break;
					case 5:
						printf("5. ��ȭ ���� ��� ����\n");
						edit_printf_movie(dest[idx]);
						printf("���� �ٲ� ��ȭ �̸��� �Է��ϼ���.\n");
						getchar();
						gets_s(dest[idx].movie.name, sizeof(dest[idx].movie.name));
						system("cls");
						edit_printf_movie(dest[idx]);
						printf("���� �ٲ� ��ȭ ���� �̸��� �Է��ϼ���.\n");
						scanf("%s", dest[idx].movie.producer);
						system("cls");
						edit_printf_movie(dest[idx]);
						printf("���� �ٲ� ��ȭ ��û ����Ʈ�� �Է��ϼ���.\n");
						scanf("%s", dest[idx].movie.site);
						system("cls");
						edit_printf_movie(dest[idx]);
						printf("���� �ٲ� ��ȭ ������ �Է��ϼ���.\n");
						scanf("%d", &dest[idx].movie.price);
						system("cls");
						break;
					case 0:
						printf("0. ���ư���\n");
						edit_menu(edit_search_book, edit_book_sn);
					default:
						
						printf("�߸� �Է��ϼ̽��ϴ�.");
						rewind(stdin);
					}
				}
				else if (dest[idx].book.movie_search == 2)
				{
					printf("���� ���� ������ ��ȭ�� �����ϴ�. �ش� ������ ��ȭ ������ �ʱ�ȭ �մϴ�.\n");
					memset(&dest[idx].movie, 0, sizeof(MOVIE));	// ��ȭ�� ���� �����ϰ�� ��ȭ���������� �����ʰ� 0���� �ʱ�ȭ
				}
				else
				{
					rewind(stdin);
					printf("�߸� �Է��ϼ̽��ϴ�.\n");
					break;
				}
				break;
			}
			case 0:
				printf("0. ���ư���\n");
				break;
			default:
				rewind(stdin);
				printf("�߸� �Է��ϼ̽��ϴ�.\n");	
			}
		}
		idx++;
	}
	fclose(fpedit);

	fpedit = fopen("book.txt", "wt");
	if (fpedit == NULL)
	{
		printf("������ ������ �� �����ϴ�.\n");
		return;
	}
	for (int i = 0; i < 256; i++)
	{
		if (strcmp(dest[i].book.name, "") != 0)
		{
			fwrite(&dest[i], sizeof(LIB), 1, fpedit);
		}
		else
		{
			break;
		}
	}
	fclose(fpedit);
}

void edit_printf_all(LIB lib)
{
	edit_printf_book(lib);
	edit_printf_loan(lib);
	edit_printf_buybook(lib);
	edit_printf_movie(lib);
}

void edit_printf_book(LIB lib)
{
	printf("==================================\n");
	printf("���� ���� : %s\n",lib.book.name);
	printf("���� ��ȣ : %d\n", lib.book.sn);
	printf("���� : %s\n", lib.book.writer);
	printf("���ǻ� : %s\n", lib.book.public);
	printf("ī�װ� : %s\n", lib.book.cate);
	printf("�˻� Ƚ�� : %d\n", lib.book.search_num);
	printf("==================================\n");
}

void edit_printf_loan(LIB lib)
{
	printf("==================================\n");
	if (lib.book.loan == 1)
	{
		printf("�� ������ �뿩 ���� �����Դϴ�.\n");
		printf("�뿩�� �̸� : %s\n", lib.user.username);
		if (lib.user.user_number == 0)
		{
			printf("�뿩�� ��ȭ��ȣ : \n");
		}
		else
		{
			printf("�뿩�� ��ȭ��ȣ : 0%d\n", lib.user.user_number);
		}
	}
	else
	{
		printf("�� ������ �뿩 ������ �����Դϴ�.\n");
	}
	printf("==================================\n");
}

void edit_printf_buybook(LIB lib)
{
	printf("==================================\n");
	printf("���� ���� ����Ʈ : %s\n", lib.buybook.site);
	printf("���� ���� ���� : %d\n", lib.buybook.price);
	printf("==================================\n");
}

void edit_printf_movie(LIB lib)
{
	printf("==================================\n");
	if (lib.book.movie_search == 1)
	{
		printf("�� ������ ��ȭ ������ �ֽ��ϴ�.\n");
		printf("��ȭ ���� : %s\n", lib.movie.name);
		printf("��ȭ ���� �̸� : %s\n", lib.movie.producer);
		printf("��ȭ ��û ����Ʈ : %s\n", lib.movie.site);		// ����, ����Ʈ ���� ����
		printf("��ȭ ���� : %d\n", lib.movie.price);
	}
	else
	{
		printf("�� ������ ��ȭ ������ �����ϴ�.\n");
	}
	printf("==================================\n");
}