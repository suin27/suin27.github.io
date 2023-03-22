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
		printf("파일을 읽을 수 없습니다.\n");
		return;
	}
	fread(&cnf_t, sizeof(cnf_t), 1, fpdelete);
	if (cnf_t.book.sn == 0)	// 파일은 있으나 안에 데이터가 없을때 탈출하기 위한 함수	
	{
		printf("데이터를 찾을 수 없습니다.\n");
		fclose(fpdelete);
		return;
	}
	//fclose(fpdelete);
	//fpdelete = fopen("book.txt", "rt");

	rewind(fpdelete);

	printf("1. 검색 삭제\n2. 전체 삭제\n");
	int dt_select = 0;
	scanf(" %d", &dt_select);
	switch (dt_select)
	{
	case 1:
	{
		LIB dt_t = { 0 };
		int i = 0;
		int found = 0;	// 삭제할 도서 유무를 판단하기 위한 스위치 변수
		printf("삭제할 도서의 이름을 입력하세요 : \n");
		getchar();
		gets_s(deletename, sizeof(deletename));
		while (fread(&dt_t, sizeof(dt_t), 1, fpdelete) == 1)
		{
			if (strcmp(deletename, dt_t.book.name) == 0)
			{
				printf("==================================\n");
				printf("도서 제목 : %s\n", dt_t.book.name);			// 책이름
				printf("도서 번호 : %d\n", dt_t.book.sn);			// 고유번호
				printf("저자 : %s\n", dt_t.book.writer);				// 저자
				printf("출판사 : %s\n", dt_t.book.public);			// 출판사											
				printf("==================================\n");
				found = 1;											// 스위치변수
			}
		}
		//fclose(fpdelete);										// 삭제하기로한 이름을 검색한 구조체를 출력
		rewind(fpdelete);
		i = 0;
		if (!found)
		{
			printf("삭제할 도서 정보를 찾을 수 없습니다.\n");
			return;
		}
		found = 0;

		int delete_book_sn;		// 동명의 책들을 구분하기 위해 고유번호로 다시 입력받아 삭제
		printf("삭제할 도서 번호를 입력하세요.\n");
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
				printf("검색하신 도서 정보를 삭제했습니다.\n");
			}
		}
		if (!found)
		{
			printf("삭제할 도서 정보를 찾을 수 없습니다.\n");
			return;
		}

		fclose(fpdelete);

		fpdelete = fopen("book.txt", "wt");
		if (fpdelete == NULL)
		{
			printf("파일을 생성할 수 없습니다.\n");
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
			printf("파일을 생성할 수 없습니다.\n");
			return;
		}

		printf("모든 도서 목록을 삭제했습니다.\n");

		fclose(fpdelete);
		break;
	}
	default:
		rewind(stdin);
		printf("잘못된 선택지 입니다. 다시 입력하세요.\n");
	}
}

void edit_file()
{
	LIB cnf_t = { 0 };
	LIB ed_sn_check = { 0 };
	LIB edcheck = { 0 };
	int edit_book_sn;		// 동명의 책들을 구분하기 위해 고유번호로 다시 입력

	char edit_search_book[100] = { 0 };
	int found = 0;

	FILE* fpedit = NULL;
	fpedit = fopen("book.txt", "rt");
	if (fpedit == NULL)
	{
		printf("파일을 읽을 수 없습니다.\n");
		return;
	}
	fread(&cnf_t, sizeof(cnf_t), 1, fpedit);
	if (cnf_t.book.name == 0)	// 파일은 있으나 안에 데이터가 없을때 탈출하기 위한 함수	
	{
		printf("데이터를 찾을 수 없습니다.\n");
		fclose(fpedit);
		return;
	}

	rewind(fpedit);
	//fclose(fpedit);
	//fpedit = fopen("book.txt", "rt");
	printf("수정하고자 하는 도서 제목을 입력하세요.\n"); // 애초에 책 이름이 틀렸을때 해결할 방법 필요.

	getchar();
	gets_s(edit_search_book, sizeof(edit_search_book));
	system("cls");

	while (fread(&edcheck, sizeof(LIB), 1, fpedit) == 1)
	{
		if (strcmp(edit_search_book, edcheck.book.name) == 0)		// 동명의 책을 모두 출력하기 위한 문구
		{
			printf("====================================\n");
			printf("도서 제목 : %s\n", edcheck.book.name);			// 책이름
			printf("도서 번호 : %d\n", edcheck.book.sn);				// 고유번호
			printf("저자 : %s\n", edcheck.book.writer);				// 저자
			printf("출판사 : %s\n", edcheck.book.public);			// 출판사	
			printf("====================================\n");
			found = 1;												// 스위치변수 // 동명의 책이 검색되었을 때 스위치변수 변화
		}
	}

	if (found == 1)	// 스위치 변수가 변했을 때 sn를 비교하기 위한 if문
	{
		found = 0;
		printf("수정할 도서 번호를 입력하세요.\n");
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

	if (!found)	// 검색한 이름의 책을 찾지 못했거나, 검색한 이름의 책이 있어도 그책의 sn이 입력한 sn와 다를 경우 출력될 문구
	{
		printf("수정할 도서 정보를 찾을 수 없습니다.\n");
		return;
	}
	fclose(fpedit);

	edit_menu(edit_search_book, edit_book_sn);
}

void edit_menu(char edit_search_book[100], int edit_book_sn)
{
	system("cls");
	printf("수정하고자 하는 도서의 정보를 선택하세요.\n");
	printf("1. 모든 정보 수정\n");
	printf("2. 도서 정보 수정\n");
	printf("3. 대여자 정보 수정(대여 유무 수정)\n");
	printf("4. 구매 정보 수정\n");
	printf("5. 영화 정보 수정(영화 유무 수정)\n");
	printf("0. 돌아가기\n");
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
		memcpy(&dest[idx], &ed, sizeof(LIB));		// 읽어온 ed전부를 dest[idx]에 저장
		if (strcmp(edit_search_book, ed.book.name) == 0 && edit_book_sn == ed.book.sn)
		{
			switch (edit_menu_all)
			{
			case 1:
				printf("모든 정보 수정을 선택하셨습니다.\n");
				// 책 정보
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 도서 제목을 입력하세요.\n");
				getchar();
				gets_s(dest[idx].book.name, sizeof(dest[idx].book.name));
				system("cls");
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 도서 번호를 입력하세요.\n");		// 이미 있는 고유번호로 수정하면 안되게 해야함.
				
				scanf("%d", &edit_book_sn);
				int sn1 = dest[idx].book.sn;
				sn1 = sn_overlap_no(sn1);
				dest[idx].book.sn = sn1;
				system("cls");
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 저자를 입력하세요.\n");
				scanf("%s", dest[idx].book.writer);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 출판사를 입력하세요.\n");
				scanf("%s", dest[idx].book.public);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 카테고리를 입력하세요.\n");
				scanf("%s", dest[idx].book.cate);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 검색 횟수를 입력하세요.\n");
				scanf("%d", &dest[idx].book.search_num);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 대여 유무를 입력하세요.\n");
				printf("1. YES\n2. NO\n");
				scanf("%d", &dest[idx].book.loan);
				system("cls");
				if (dest[idx].book.loan == 1)	// 대여자 정보가 바뀌었을때만 대여자 구조체 정보 수정?
				{
					// 대여자 정보
					//printf("대여 정보의 도서 제목을 변경합니다.\n");
					strcpy(dest[idx].user.bookname, dest[idx].book.name);
					edit_printf_all(dest[idx]);
					printf("새로 바꿀 대여자의 이름을 입력하세요.\n");
					scanf("%s", dest[idx].user.username);
					system("cls");
					edit_printf_all(dest[idx]);
					printf("새로 바꿀 대여자의 전화 번호를 입력하세요.\n");
					scanf("%d", &dest[idx].user.user_number);
					system("cls");
				}
				else if (dest[idx].book.loan == 2)
				{
					printf("수정 중인 도서가 대여 중인 상태가 아닙니다. 해당 도서의 대여 정보를 초기화 합니다.\n");
					memset(&dest[idx].user, 0, sizeof(USER));
				}
				else
				{
					rewind(stdin);
					printf("잘못 입력하셨습니다.\n");
					break;
				}
				// 구매 정보
				//printf("구매 정보의 도서 제목을 변경합니다.\n");
				strcpy(dest[idx].buybook.name, dest[idx].book.name);
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 책의 구매 사이트를 입력하세요.\n");
				scanf("%s", dest[idx].buybook.site);
				system("cls");
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 책의 구매 가격을 입력하세요.\n");
				scanf("%d", &dest[idx].buybook.price);
				system("cls");
				// 영화 정보
				edit_printf_all(dest[idx]);
				printf("새로 바꿀 영화 유무를 입력하세요.\n");
				printf("1. YES\n2. NO\n");
				scanf("%d", &dest[idx].book.movie_search);
				system("cls");
				if (dest[idx].book.movie_search == 1)
				{
					// 영화 정보
					edit_printf_all(dest[idx]);
					printf("새로 바꿀 영화 제목을 입력하세요.\n");
					getchar();
					gets_s(dest[idx].movie.name, sizeof(dest[idx].movie.name));
					system("cls");
					edit_printf_all(dest[idx]);
					printf("새로 바꿀 영화 감독 이름을 입력하세요.\n");
					scanf("%s", dest[idx].movie.producer);
					system("cls");
					edit_printf_all(dest[idx]);
					printf("새로 바꿀 영화 시청 사이트를 입력하세요.\n");
					scanf("%s", dest[idx].movie.site);
					system("cls");
					edit_printf_all(dest[idx]);
					printf("새로 바꿀 영화 가격을 입력하세요.\n");
					scanf("%d", &dest[idx].movie.price);
					system("cls");
				}
				else if (dest[idx].book.movie_search == 2)
				{
					printf("수정 중인 도서의 영화가 없습니다. 해당 도서의 영화 정보를 초기화 합니다.\n");
					memset(&dest[idx].movie, 0, sizeof(MOVIE));	// 영화가 없는 도서일경우 영화정보수정을 묻지않고 0으로 초기화
				}
				else
				{
					rewind(stdin);
					printf("잘못 입력하셨습니다.\n");
					break;
				}
				break;
			case 2:												// 도서 정보 수정 스위치문
			{
				printf("도서 정보 수정을 선택하셨습니다.\n");
				edit_printf_book(dest[idx]);
				printf("세부 메뉴를 선택하세요.\n");
				printf("1. 도서 제목 수정\n");
				printf("2. 도서 번호 수정\n");
				printf("3. 저자 수정\n");
				printf("4. 출판사 수정\n");
				printf("5. 카테고리 수정\n");
				printf("6. 검색 횟수 수정\n");
				printf("7. 도서 정보 모두 수정\n");
				printf("0. 돌아가기\n");
				int edit_menu_book = -1;
				scanf("%d", &edit_menu_book);
				system("cls");
				switch (edit_menu_book)
				{
				case 1:
					printf("1. 도서 제목 수정\n");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 책의 이름을 입력하세요.\n");
					getchar();
					gets_s(dest[idx].book.name, sizeof(dest[idx].book.name));
					strcpy(dest[idx].buybook.name, dest[idx].book.name);		// 새로 입력한 책 이름을 구매 정보에 복사
					system("cls");
					break;
				case 2:
					printf("2. 도서 번호 수정\n");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 고유 번호를 입력하세요.\n");
					scanf("%d", &dest[idx].book.sn);
					int sn1 = dest[idx].book.sn;
					sn1 = sn_overlap_no(sn1);
					dest[idx].book.sn = sn1;
					system("cls");
					break;
				case 3:
					printf("3. 저자 수정\n");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 저자를 입력하세요.\n");
					scanf("%s", dest[idx].book.writer);
					system("cls");
					break;
				case 4:
					printf("4. 출판사 수정\n");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 출판사를 입력하세요.\n");
					scanf("%s", dest[idx].book.public);
					system("cls");
					break;
				case 5:
					printf("5. 카테고리 수정\n");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 카테고리를 입력하세요.\n");
					scanf("%s", dest[idx].book.cate);
					system("cls");
					break;
				case 6:
					printf("6. 검색 횟수 수정\n");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 검색 횟수를 입력하세요.\n");
					scanf("%d", &dest[idx].book.search_num);
					system("cls");
					break;
				case 7:
					printf("7. 도서 정보 모두 수정\n");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 도서 제목을 입력하세요.\n");
					getchar();
					gets_s(dest[idx].book.name, sizeof(dest[idx].book.name));
					strcpy(dest[idx].buybook.name, dest[idx].book.name);
					system("cls");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 도서 번호를 입력하세요.\n");
					scanf("%d", &dest[idx].book.sn);
					sn1 = dest[idx].book.sn;
					sn1 = sn_overlap_no(sn1);
					dest[idx].book.sn = sn1;
					system("cls");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 저자를 입력하세요.\n");
					scanf("%s", dest[idx].book.writer);
					system("cls");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 출판사를 입력하세요.\n");
					scanf("%s", dest[idx].book.public);
					system("cls");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 카테고리를 입력하세요.\n");
					scanf("%s", dest[idx].book.cate);
					system("cls");
					edit_printf_book(dest[idx]);
					printf("새로 바꿀 검색 횟수를 입력하세요.\n");
					scanf("%d", &dest[idx].book.search_num);
					system("cls");
					break;
				case 0:
					printf("0. 돌아가기\n");
					edit_menu(edit_search_book, edit_book_sn);

				default:
					
					printf("잘못 입력하셨습니다.");
					rewind(stdin);
				}
				break;
			}
			case 3:												// 대여자 정보 수정 스위치문
			{
				printf("대여자 정보 수정을 선택하셨습니다.\n");
				edit_printf_loan(dest[idx]);
				printf("수정할 도서의 현재 대여 유무 상태를 입력하세요.\n");
				printf("1. YES\n2. NO\n");
				scanf("%d", &dest[idx].book.loan);
				system("cls");
				if (dest[idx].book.loan == 1)
				{
					printf("세부 메뉴를 선택하세요.\n");
					edit_printf_loan(dest[idx]);
					printf("1. 대여자 이름 수정\n");
					printf("2. 대여자 전화번호 수정\n");
					printf("3. 대여자 정보 모두 수정\n");
					printf("0. 돌아가기\n");
					int edit_menu_user = -1;
					scanf("%d", &edit_menu_user);
					system("cls");
					switch (edit_menu_user)
					{
					case 1:
						printf("1. 대여자 이름 수정\n");
						edit_printf_loan(dest[idx]);
						printf("새로 바꿀 대여자의 이름을 입력하세요.\n");
						getchar();
						gets_s(dest[idx].user.username, sizeof(dest[idx].user.username));
						system("cls");
						break;
					case 2:
						printf("2. 대여자 전화번호 수정\n");
						edit_printf_loan(dest[idx]);
						printf("새로 바꿀 대여자의 전화 번호를 입력하세요.\n");
						scanf("%d", &dest[idx].user.user_number);
						system("cls");
						break;
					case 3:
						printf("3. 대여자 정보 모두 수정\n");
						edit_printf_loan(dest[idx]);
						printf("새로 바꿀 대여자의 이름을 입력하세요.\n");
						getchar();
						gets_s(dest[idx].user.username, sizeof(dest[idx].user.username));
						system("cls");
						edit_printf_loan(dest[idx]);
						printf("새로 바꿀 대여자의 전화 번호를 입력하세요.\n");
						scanf("%d", &dest[idx].user.user_number);
						system("cls");
						break;
					case 0:
						printf("0. 돌아가기\n");
						edit_menu(edit_search_book, edit_book_sn);
					default:
						rewind(stdin);
						printf("잘못 입력하셨습니다.\n");
					}
				}
				else if (dest[idx].book.loan == 2)
				{
					printf("수정 중인 도서가 대여 중인 상태가 아닙니다. 해당 도서의 대여 정보를 초기화 합니다.\n");
					memset(&dest[idx].user, 0, sizeof(USER));
				}
				else
				{
					rewind(stdin);
					printf("잘못 입력하셨습니다.\n");
					break;
				}
				break;
			}
			case 4:												// 구매 정보 수정 스위치문
			{
				printf("구매 정보 수정을 선택하셨습니다.\n");
				edit_printf_buybook(dest[idx]);
				printf("세부 메뉴를 선택하세요.\n");
				printf("1. 사이트 수정\n");
				printf("2. 가격 수정\n");
				printf("3. 구매 정보 모두 수정\n");
				printf("0. 돌아가기\n");
				int edit_menu_buybook = -1;
				scanf("%d", &edit_menu_buybook);
				system("cls");
				switch (edit_menu_buybook)
				{
				case 1:
					printf("1. 사이트 수정\n");
					edit_printf_buybook(dest[idx]);
					printf("새로 바꿀 책의 구매 사이트를 입력하세요.\n");
					scanf("%s", dest[idx].buybook.site);
					system("cls");
					break;
				case 2:
					printf("2. 가격 수정\n");
					edit_printf_buybook(dest[idx]);
					printf("새로 바꿀 책의 구매 가격을 입력하세요.\n");
					scanf("%d", &dest[idx].buybook.price);
					system("cls");
					break;
				case 3:
					printf("3. 구매 정보 모두 수정\n");
					edit_printf_buybook(dest[idx]);
					printf("새로 바꿀 책의 구매 사이트를 입력하세요.\n");
					scanf("%s", dest[idx].buybook.site);
					system("cls");
					edit_printf_buybook(dest[idx]);
					printf("새로 바꿀 책의 구매 가격을 입력하세요.\n");
					scanf("%d", &dest[idx].buybook.price);
					system("cls");
					break;
				case 0:
					printf("0. 돌아가기\n");
					edit_menu(edit_search_book, edit_book_sn);
				default:
					rewind(stdin);
					printf("잘못 입력하셨습니다.");
				}
				break;
			}
			case 5:												// 영화 정보 수정 스위치문
			{
				printf("영화 정보 수정을 선택하셨습니다.\n");
				edit_printf_movie(dest[idx]);
				printf("수정할 도서의 현재 영화 유무 상태를 입력하세요.\n");
				printf("1. YES\n2. NO\n");
				scanf("%d", &dest[idx].book.movie_search);
				system("cls");
				if (dest[idx].book.movie_search == 1)
				{
					printf("세부 메뉴를 선택하세요.\n");
					edit_printf_movie(dest[idx]);
					printf("1. 영화 제목 수정\n");
					printf("2. 감독 수정\n");
					printf("3. 영화 시청 사이트 수정\n");
					printf("4. 가격 수정\n");
					printf("5. 영화 정보 모두 수정\n");
					printf("0. 돌아가기\n");
					int edit_menu_movie = -1;
					scanf("%d", &edit_menu_movie);
					system("cls");
					switch (edit_menu_movie)
					{
					case 1:
						printf("1. 영화 제목 수정\n");
						edit_printf_movie(dest[idx]);
						printf("새로 바꿀 영화 이름을 입력하세요.\n");
						getchar();
						gets_s(dest[idx].movie.name, sizeof(dest[idx].movie.name));
						system("cls");
						break;
					case 2:
						printf("3. 감독 수정\n");
						edit_printf_movie(dest[idx]);
						printf("새로 바꿀 영화 감독 이름을 입력하세요.\n");
						scanf("%s", dest[idx].movie.producer);
						system("cls");
						break;
					case 3:
						printf("2. 영화 시청 사이트 수정\n");
						edit_printf_movie(dest[idx]);
						printf("새로 바꿀 영화 시청 사이트를 입력하세요.\n");
						scanf("%s", dest[idx].movie.site);
						system("cls");
						break;
					case 4:
						printf("4. 가격 수정\n");
						edit_printf_movie(dest[idx]);
						printf("새로 바꿀 영화 가격을 입력하세요.\n");
						scanf("%d", &dest[idx].movie.price);
						system("cls");
						break;
					case 5:
						printf("5. 영화 정보 모두 수정\n");
						edit_printf_movie(dest[idx]);
						printf("새로 바꿀 영화 이름을 입력하세요.\n");
						getchar();
						gets_s(dest[idx].movie.name, sizeof(dest[idx].movie.name));
						system("cls");
						edit_printf_movie(dest[idx]);
						printf("새로 바꿀 영화 감독 이름을 입력하세요.\n");
						scanf("%s", dest[idx].movie.producer);
						system("cls");
						edit_printf_movie(dest[idx]);
						printf("새로 바꿀 영화 시청 사이트를 입력하세요.\n");
						scanf("%s", dest[idx].movie.site);
						system("cls");
						edit_printf_movie(dest[idx]);
						printf("새로 바꿀 영화 가격을 입력하세요.\n");
						scanf("%d", &dest[idx].movie.price);
						system("cls");
						break;
					case 0:
						printf("0. 돌아가기\n");
						edit_menu(edit_search_book, edit_book_sn);
					default:
						
						printf("잘못 입력하셨습니다.");
						rewind(stdin);
					}
				}
				else if (dest[idx].book.movie_search == 2)
				{
					printf("수정 중인 도서의 영화가 없습니다. 해당 도서의 영화 정보를 초기화 합니다.\n");
					memset(&dest[idx].movie, 0, sizeof(MOVIE));	// 영화가 없는 도서일경우 영화정보수정을 묻지않고 0으로 초기화
				}
				else
				{
					rewind(stdin);
					printf("잘못 입력하셨습니다.\n");
					break;
				}
				break;
			}
			case 0:
				printf("0. 돌아가기\n");
				break;
			default:
				rewind(stdin);
				printf("잘못 입력하셨습니다.\n");	
			}
		}
		idx++;
	}
	fclose(fpedit);

	fpedit = fopen("book.txt", "wt");
	if (fpedit == NULL)
	{
		printf("파일을 생성할 수 없습니다.\n");
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
	printf("도서 제목 : %s\n",lib.book.name);
	printf("도서 번호 : %d\n", lib.book.sn);
	printf("저자 : %s\n", lib.book.writer);
	printf("출판사 : %s\n", lib.book.public);
	printf("카테고리 : %s\n", lib.book.cate);
	printf("검색 횟수 : %d\n", lib.book.search_num);
	printf("==================================\n");
}

void edit_printf_loan(LIB lib)
{
	printf("==================================\n");
	if (lib.book.loan == 1)
	{
		printf("이 도서는 대여 중인 상태입니다.\n");
		printf("대여자 이름 : %s\n", lib.user.username);
		if (lib.user.user_number == 0)
		{
			printf("대여자 전화번호 : \n");
		}
		else
		{
			printf("대여자 전화번호 : 0%d\n", lib.user.user_number);
		}
	}
	else
	{
		printf("이 도서는 대여 가능한 상태입니다.\n");
	}
	printf("==================================\n");
}

void edit_printf_buybook(LIB lib)
{
	printf("==================================\n");
	printf("도서 구매 사이트 : %s\n", lib.buybook.site);
	printf("도서 구매 가격 : %d\n", lib.buybook.price);
	printf("==================================\n");
}

void edit_printf_movie(LIB lib)
{
	printf("==================================\n");
	if (lib.book.movie_search == 1)
	{
		printf("이 도서는 영화 정보가 있습니다.\n");
		printf("영화 제목 : %s\n", lib.movie.name);
		printf("영화 감독 이름 : %s\n", lib.movie.producer);
		printf("영화 시청 사이트 : %s\n", lib.movie.site);		// 감독, 사이트 순서 변경
		printf("영화 가격 : %d\n", lib.movie.price);
	}
	else
	{
		printf("이 도서는 영화 정보가 없습니다.\n");
	}
	printf("==================================\n");
}