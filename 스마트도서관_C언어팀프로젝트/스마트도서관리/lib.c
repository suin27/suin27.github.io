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
	printf("���� ������ �Է��մϴ�\n");
	printf("###################################\n");
	printf("���� �̸��� �Է��Ͻʽÿ�\n");
	getchar();
	gets_s(lb.book.name, sizeof(char) * 100);
	printf("���� ��ȣ�� �Է��Ͻʽÿ�\n");
	scanf("%d", &lb.book.sn);
	int sn1 = lb.book.sn;
	sn1 = sn_overlap_no(sn1);
	lb.book.sn = sn1;
	printf("���� ���ڸ� �Է��Ͻʽÿ�\n");
	scanf("%s", lb.book.writer);
	printf("���ǻ縦 �Է��Ͻʽÿ�\n");
	scanf("%s", lb.book.public);
	printf("ī�װ��� �Է��Ͻʽÿ�\n");
	scanf("%s", lb.book.cate);
	printf("��ȭ ������ �Է��Ͻʽÿ�.(Y/N)\n");
	scanf(" %d", &lb.book.movie_search);
	
	if (lb.book.movie_search == 1)
	{
		printf("\n------ ��ȭ ���� ------\n");
		printf("��ȭ �̸��� �Է��Ͻʽÿ�\n");
		getchar();
		gets_s(lb.movie.name, sizeof(char) * 100);
		printf("��ȭ ��û ����Ʈ�� �Է��Ͻʽÿ�\n");
		scanf("%s", lb.movie.site);
		printf("��ȭ �������� �Է��Ͻʽÿ�\n");
		scanf("%s", lb.movie.producer);
		printf("��ȭ ������ �Է��Ͻʽÿ�\n");
		scanf("%d", &lb.movie.price);
	}
	else
	{
		printf("��ȭ�� ���� �����Դϴ�.");
	}

	printf("\n------ ���� ���� ���� ------\n");
	printf("���� �̸� : ");
	printf(" %s\n", lb.book.name);
	printf("���� ����Ʈ �̸��� �Է��Ͻʽÿ�\n");
	scanf("%s", lb.buybook.site);
	printf("���� ������ �Է��Ͻʽÿ�.\n");
	scanf("%d", &lb.buybook.price);
	
	book_write(lb);

}
int sn_overlap_no(int sn)
{
	FILE* fp = NULL;
	fp = fopen("book.txt", "r");
	if (fp == NULL) {
		printf("������ ������ �� �����ϴ�.");
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
		printf("�ߺ��� ������ȣ �Է����� sn�� �ڵ����� %d���� �Էµ˴ϴ�.\n", sn);
	}
	
	fclose(fp);
	return sn;
}
void lib_lb_show(LIB lb) {
	printf("\n");
	printf("###################################\n");
	printf("%8s %s\n", "���� ����",lb.book.name);
	printf("###################################\n");
	printf("���� ��ȣ : %d\n", lb.book.sn);
	printf("���� ���� : %s\n", lb.book.writer);
	printf("���� ���ǻ� : %s\n", lb.book.public);
	printf("���� ī�װ� : %s\n", lb.book.cate);
	if (lb.book.loan == 1) {
		printf("�� ������ �̹� �뿩���� ���� �Դϴ�\n");
	}
	else if (lb.book.loan == 2||lb.book.loan==0) {
		printf("�� ������ �뿩�� �����մϴ�\n");
	}
	printf("\n");
	if (lb.movie.price != 0) {
		printf("------ ���� ��ȭ ���� ------\n");
		printf("��ȭ �̸� : %s\n", lb.movie.name);
		printf("��ȭ ���� : %s\n", lb.movie.producer);
		printf("��ȭ ��û ����Ʈ : %s\n", lb.movie.site);
		printf("��ȭ ���� : %d\n", lb.movie.price);
		printf("\n");
	}
	
}
