#include "crt.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include "lib.h"
#include "book_util.h"
void book_lib_input() {
	LIB lb= { 0, };
	printf("###################################\n");
	printf("도서 정보를 입력합니다\n");
	printf("###################################\n");
	printf("도서 이름을 입력하십시오\n");
	getchar();
	gets_s(lb.book.name, sizeof(char) * 100);
	printf("도서 번호를 입력하십시오\n");
	scanf("%d", &lb.book.sn);
	int sn1 = lb.book.sn;
	sn1 = sn_overlap_no(sn1);
	lb.book.sn = sn1;
	printf("도서 저자를 입력하십시오\n");
	scanf("%s", lb.book.writer);
	printf("출판사를 입력하십시오\n");
	scanf("%s", lb.book.public);
	printf("카테고리를 입력하십시오\n");
	scanf("%s", lb.book.cate);
	printf("영화 유무를 입력하십시오.(Y/N)\n");
	scanf(" %d", &lb.book.movie_search);
	
	if (lb.book.movie_search == 1)
	{
		printf("\n------ 영화 정보 ------\n");
		printf("영화 이름을 입력하십시오\n");
		getchar();
		gets_s(lb.movie.name, sizeof(char) * 100);
		printf("영화 시청 사이트를 입력하십시오\n");
		scanf("%s", lb.movie.site);
		printf("영화 감독명을 입력하십시오\n");
		scanf("%s", lb.movie.producer);
		printf("영화 가격을 입력하십시오\n");
		scanf("%d", &lb.movie.price);
	}
	else
	{
		printf("영화가 없는 도서입니다.");
	}

	printf("\n------ 도서 구매 정보 ------\n");
	printf("도서 이름 : ");
	printf(" %s\n", lb.book.name);
	printf("구매 사이트 이름을 입력하십시오\n");
	scanf("%s", lb.buybook.site);
	printf("도서 가격을 입력하십시오.\n");
	scanf("%d", &lb.buybook.price);
	
	book_write(lb);

}
int sn_overlap_no(int sn)
{
	FILE* fp = NULL;
	fp = fopen("book.txt", "r");
	if (fp == NULL) {
		printf("파일을 생성할 수 없습니다.");
		return 0;
	}
	LIB snsn = { 0, };
	int count = 0;
	char ok={0};
	while (fread(&snsn, sizeof(LIB), 1, fp) == 1)
	{
		if (sn == snsn.book.sn)
		{
			sn = sn + 1;
			count++;
		}
	}
	if (count != 0) {
		printf("중복된 고유번호 입력으로 sn은 자동으로 %d으로 입력됩니다.\n", sn);
	}
	
	fclose(fp);
	return sn;
}
void lib_lb_show(LIB lb) {
	printf("\n");
	printf("###################################\n");
	printf("%8s %s\n", "도서 제목",lb.book.name);
	printf("###################################\n");
	printf("도서 번호 : %d\n", lb.book.sn);
	printf("도서 저자 : %s\n", lb.book.writer);
	printf("도서 출판사 : %s\n", lb.book.public);
	printf("도서 카테고리 : %s\n", lb.book.cate);
	if (lb.book.loan == 1) {
		printf("이 도서는 이미 대여중인 도서 입니다\n");
	}
	else if (lb.book.loan == 2||lb.book.loan==0) {
		printf("이 도서는 대여가 가능합니다\n");
	}
	printf("\n");
	if (lb.movie.price != 0) {
		printf("------ 도서 영화 정보 ------\n");
		printf("영화 이름 : %s\n", lb.movie.name);
		printf("영화 감독 : %s\n", lb.movie.producer);
		printf("영화 시청 사이트 : %s\n", lb.movie.site);
		printf("영화 가격 : %d\n", lb.movie.price);
		printf("\n");
	}
	
}
