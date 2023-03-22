#include "crt.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"lib.h"
#include"where_book.h"
#include "loan_and_return.h"
int get_time2(char* tinfo)//시간함수1
{
	time_t timer;
	struct tm* t;
	//timer : 1970년 1월 1일 0시 0초부터~ 현재까지 초
	timer = time(NULL);
	t = localtime(&timer);
	char buf[20] = { 0, };//배열안에 담겨있음.//5일을 늘릴려면 인트정보로하고
	//년,월,일을 세분화 시켜서 증가시켜야됨.
	//sprintf(buf, "%d년%d월%d일-%d시%d분%d초",

	sprintf(buf, "%d년%d월%d일",

		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday);
	//	t->tm_hour,
	//	t->tm_min,
	//	t->tm_sec);
	int d = 0;
	d = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday + 3;
	return d;
}
void w_book() {
	FILE* fpr = NULL;
	fpr = fopen("book.txt", "r");
	if (fpr == NULL) {
		printf("파일을 생성할 수 없습니다.");
		return;
	}
	//printf(" 도서정보가 없다면 \n	출력도 없습니다\n");
	printf("연체 정보를 출력합니다\n");
	LIB lb = { 0, };
	printf("=================================\n");
	int cot = 1;
	char curtime_3day_add[40] = { 0, };//복사가 되어짐.
	int d = get_time2(curtime_3day_add) - 3;
	int c = 0;
	while (fread(&lb, sizeof(lb), 1, fpr) == 1) {
		if (lb.book.loan == 1) {
			printf("%s님이 빌리신 책 %s의 연체정보입니다.\n", lb.user.username, lb.book.name);
			if (lb.user.delay - d >= 0) {
				printf("반납까지 %d일 남았습니다.\n", lb.user.delay - d);
			}
			else {
				printf("연체된지 %d일째입니다.\n", (-1) * (lb.user.delay - d));
			}
			lb.user.delay = lb.user.delay - d;
			c++;
		}
	}
	if (c == 0) {
	printf("연체 정보가 없습니다.");
	}
	fclose(fpr);

}