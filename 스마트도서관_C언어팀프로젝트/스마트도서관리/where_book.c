#include "crt.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"lib.h"
#include"where_book.h"
#include "loan_and_return.h"
int get_time2(char* tinfo)//�ð��Լ�1
{
	time_t timer;
	struct tm* t;
	//timer : 1970�� 1�� 1�� 0�� 0�ʺ���~ ������� ��
	timer = time(NULL);
	t = localtime(&timer);
	char buf[20] = { 0, };//�迭�ȿ� �������.//5���� �ø����� ��Ʈ�������ϰ�
	//��,��,���� ����ȭ ���Ѽ� �������Ѿߵ�.
	//sprintf(buf, "%d��%d��%d��-%d��%d��%d��",

	sprintf(buf, "%d��%d��%d��",

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
		printf("������ ������ �� �����ϴ�.");
		return;
	}
	//printf(" ���������� ���ٸ� \n	��µ� �����ϴ�\n");
	printf("��ü ������ ����մϴ�\n");
	LIB lb = { 0, };
	printf("=================================\n");
	int cot = 1;
	char curtime_3day_add[40] = { 0, };//���簡 �Ǿ���.
	int d = get_time2(curtime_3day_add) - 3;
	int c = 0;
	while (fread(&lb, sizeof(lb), 1, fpr) == 1) {
		if (lb.book.loan == 1) {
			printf("%s���� ������ å %s�� ��ü�����Դϴ�.\n", lb.user.username, lb.book.name);
			if (lb.user.delay - d >= 0) {
				printf("�ݳ����� %d�� ���ҽ��ϴ�.\n", lb.user.delay - d);
			}
			else {
				printf("��ü���� %d��°�Դϴ�.\n", (-1) * (lb.user.delay - d));
			}
			lb.user.delay = lb.user.delay - d;
			c++;
		}
	}
	if (c == 0) {
	printf("��ü ������ �����ϴ�.");
	}
	fclose(fpr);

}