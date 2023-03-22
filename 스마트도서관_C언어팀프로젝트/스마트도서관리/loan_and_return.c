#include "crt.h"
#include<stdio.h>
#include<Windows.h>
#include "lib.h"
#include "loan_and_return.h"
#include <time.h>
void user_loan_input();
//10�� 21��
//�뿩 ��¥, �ݳ� ��¥ ������.
//�뿩���� ȭ�� �뿩�ڸ� ������� ����
//���� �̸��� ���� ��찡 �־ å �뿩�� Ű���带 ���� ���� ��ȣ�� ������.

//10�� 25�� �뿩:�ݳ�,�뿩 �������� �з���. ��¥�� ���ð� �������� 3�� ���.
//void update_curtime_3day_add() �Լ� �߰�.

void get_time(char* tinfo)//�ð��Լ�1
{
	time_t timer;
	struct tm* t; //timer : 1970�� 1�� 1�� 0�� 0�ʺ���~ ������� ��
	timer = time(NULL);
	t = localtime(&timer);
	char buf[30] = { 0, };//�迭�ȿ� �������.//5���� �ø����� ��Ʈ�������ϰ�
	//��,��,���� ����ȭ ���Ѽ� �������Ѿߵ�.//sprintf(buf, "%d��%d��%d��-%d��%d��%d��",
	sprintf(buf, "%d��%d��%d��",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday);
	//	t->tm_hour,
	//	t->tm_min,
	//	t->tm_sec);
	strcpy(tinfo, buf);//����
}

int  get_time_3day_add(char* tinfo)//�ð��Լ�2(+3���߰�)
{
	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);
	char buf[30] = { 0, };
	sprintf(buf, "%d��%d��%d��",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday + 3);	
	strcpy(tinfo, buf);//����
	int d = 0;
	d = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday + 3;
	return d;
}

void view_book_loan()//�뿩 �ʱ� ȭ��
{
	FILE* fpr = fopen("book.txt", "rt");
	if (fpr == NULL) {
		printf("������ ���� �� �����ϴ�.\n");
		return;
	}
	LIB lb = { 0, };
	printf("============================\n");
	printf("book.txt���� ���� ����\n");

	int count = 1;
	while (fread(&lb, sizeof(lb), 1, fpr) == 1)
	{
		printf("������ ���� ���� ������\n");
		printf("���� �̸�: %s\n", lb.book.name);
		printf("���� ����: %s\n", lb.book.writer);
		printf("���ǻ�: %s\n", lb.book.public);
		printf("ī�װ�: %s\n", lb.book.cate);
		printf("��ȭ ����: %c\n", lb.book.movie_search);
		printf("���� �˻� Ƚ��: %d\n", lb.book.search_num);
		printf("���� ���� ��ȣ: %d\n", lb.book.sn);//������ȣ �˻��Ʒ���.
		//printf("�뿩 ����: %d\n", lb.book.loan);
		if (lb.book.loan == 0||lb.book.loan==2)//���� �뿩 ����: 0�뿩 ����,1�Ұ���
		{
			printf("�뿩 ���� : ����\n");
		}
		else
		{
			printf("�뿩 ���� : �Ұ���\n");
		}

		if (lb.book.movie_search == 1)
		{
			printf("\n------ ��ȭ ���� ------\n");
			printf("��ȭ �̸� : %s\n", lb.movie.name);
			printf("��ȭ ��û ����Ʈ : %s\n", lb.movie.site);
			printf("��ȭ ������ : %s\n", lb.movie.name);
			printf("��ȭ ���� : %d\n", lb.movie.price);
		}
		else
		{
			printf("��ȭ�� ���� �����Դϴ�.\n");
		}
		printf("\n------ ���� ���� ���� ------\n");
		printf("���� �̸�: %s\n", lb.buybook.name);
		printf("���� ����Ʈ �̸�: %s\n", lb.buybook.site);
		printf("���� ����: %d\n", lb.buybook.price);
		printf("\n");
	}
	fclose(fpr);
	book_loan_act();
}

void book_loan_act()//�뿩�� �߻��Ѵ�.(å�̸�����->�ø��� �ѹ��� ������.10��21��
{
	FILE* fp = fopen("book.txt", "rt");//<<�������°�
	if (fp == NULL) {
		printf("������ ���� �� �����ϴ�.\n");
		return;
	}
	LIB lb = { 0, };
	int input_book_number = 0;//å �̸� �Է¹��� �ӽ� ����(char���� int�� ����)
	//int input_book_name->int input_book_number�κ���10_25��

	printf("�뿩�� ���ϴ� ������ ���� ��ȣ�� �Է��ϼ���.\n");
	printf("0. ���� �޴��� ���ư���\n");
	scanf("%d", &input_book_number);
	
	if (input_book_number == 0) {
		printf("���� �޴��� ���ư���\n");
		return;
	}
	//lb.book.loan ���� ���
	//���� input_book_name�� loan_book_name�� ���ٸ�// lb.book.loan��
	//1�� �Է��Ѵ�.
	LIB dest[100] = { 0, };
	int idx = 0;
	int found = 0;
	//char rent_name[20] = { 0, };//�Լ��� �뿩 ���� ȭ������ ���ѱ��
	while (fread(&lb, sizeof(lb), 1, fp) == 1) {
		memcpy(&dest[idx], &lb, sizeof(lb));
		if (input_book_number == lb.book.sn && dest[idx].book.loan == 1) {
			printf("�̹� �뿩�� ������ �뿩�Ұ��մϴ�.\n");
			//printf("�뿩 ������ ������ �����ϼ���.\n");
			Sleep(500);
			found = 4;
			break;
		}
		if (input_book_number == lb.book.sn) {
			dest[idx].book.loan = 1;
			printf("�뿩���� �̸��� �Է��ϼ���.\n");
			scanf("%s", dest[idx].user.username);
			//strcpy(rent_name, dest[idx].user.username);//�Է¹��� ���� rent_name�� ����

			//�뿩 ��¥
			char curtime[30] = { 0, };//���簡 �Ǿ���.
			get_time(curtime);
			strcpy(dest[idx].user.date, curtime);//�ٽ� ����ü�� ����.


			char curtime_3day_add[40] = { 0, };//���簡 �Ǿ���.
			int d = get_time_3day_add(curtime_3day_add);
			dest[idx].user.delay = d;
			strcpy(dest[idx].user.return_date, curtime_3day_add);//�ٽ� ����ü�� ����.

			printf("��û��¥ : %s\n", dest[idx].user.date);
			printf("�ݳ� ���� ��¥ : %s(�뿩�Ⱓ+3��)\n", dest[idx].user.return_date);//+�뿩�Ⱓ �߰�

			printf("�뿩�� ��ȭ ��ȣ(���ڸ� �Է��ϼ���)\n");
			scanf("%d", &dest[idx].user.user_number);
			found = 1;
		}
		
		idx++;
	}
	fclose(fp);

	if (found == 0) {
		printf("�뿩�� ������ ã�� �� �����ϴ�.\n");
		Sleep(500);
		return;
	}
	else if (found == 1) {
		FILE* fps = fopen("book.txt", "wb");//, ���̳ʸ�:b
		if (fps == NULL) {
			printf("������ ������ �� �����ϴ�.\n");
			return;
		}
		for (int i = 0; i < 256; i++) {
			if (strcmp(dest[i].book.name, "") != 0) {//������ �ƴϴ� //�����Ͱ� ����ִ�.
				fwrite(&dest[i], sizeof(LIB), 1, fps);
			}
			else break;
		}
		fclose(fps);
		memset(dest, 0, sizeof(LIB) * 100);
		Sleep(500);
		view_book_loan_after(input_book_number);
	}
	return;
}


void view_book_loan_after(int number)//�뿩 �ı� ȭ��(����:�뿩�� ��� ����� ���δ�)
{
	system("cls");
	FILE* fp;
	LIB lb = { 0, };

	fp = fopen("book.txt", "rt");//���� �߰�-���� �߰��� �ƴ϶� ������ �о�ͼ� ���� �� ����ó���ϴ°�
	//���//�ѹ� ���ؼ� �ޱ�-����� ������ ���ͼ� �����ϱ�.
	while (fread(&lb, sizeof(lb), 1, fp) == 1) {
		//if (lb.book.loan == 1) {loan�� 1�̸� �����ش�.( strcmp( str1, str2 ) == 0 )//���ڿ��� ����	
		//if (strcmp(lb.user.username, name) == 0 && lb.book.loan == 1) { //�뿩�� �̸���ġ, loan�� 1�̸� show
		if (lb.book.sn == number) { //�뿩�� �̸���ġ, loan�� 1�̸� show
			printf("\n------ ���� �뿩 ���� ------\n");
			printf("���� ���� ��ȣ : %d\n", lb.book.sn);
			printf("���� �̸� : %s\n", lb.book.name);
			printf("���� ���� : %s\n", lb.book.writer);
			printf("���ǻ� : %s\n", lb.book.public);

			printf("\n------ ���� �뿩�� ���� ------\n");

			printf("�뿩�� �̸� : %s\n", lb.user.username);
			printf("�뿩 ��¥ : %s\n", lb.user.date);
			printf("�ݳ� ���� ��¥ : %s(�뿩�Ⱓ+3��)\n", lb.user.return_date);//+�뿩�Ⱓ �߰�
			printf("�뿩�� ��ȭ ��ȣ : 0%d\n", lb.user.user_number);

			printf("��ü ���� : %d\n", lb.user.delay);
			printf("\n");
			printf("%s�뿩 �ϼ̽��ϴ�.\n", lb.user.username);
			
		}
	}
	fclose(fp);
	//view_book_loan();�뿩 ���κ�
	return;
}

void return_view_book_loan()//�̸� �˻�>>�ڷ�� ��>���ٸ�>���>�ݳ�ó��
{
	printf("\n------ ���� �ݳ� ó�� ------\n");
	FILE* fp = fopen("book.txt", "rt");
	if (fp == NULL) {
		printf("������ ���� �� �����ϴ�.\n");
		return;
	}
	LIB lb = { 0, };
	char book_loan_word[20] = { 0, };//�˻��Է� �ܾ�����
	//char check_loan_name[20];//�뿩�� �ݳ����� ó�� 1->0���� ����
	printf("�뿩���� �̸��� �Է��ϼ���. : ");
	scanf("%s", book_loan_word);//�˻� �ܾ� �Է�

	printf("=================================\n");
	printf("�˻� ���\n");
	printf("=================================\n");

	int count = 1;
	while (fread(&lb, sizeof(lb), 1, fp) == 1)//�˻� ��� ����ϱ�
	{
		if (strcmp(book_loan_word, lb.user.username) == 0)//�˻��� �̸� : �뿩�� �̸� ��
		{
			printf("�˻���� : %s���� �뿩�� �ֽ��ϴ�.\n", lb.user.username);

			printf("������ ���� ���� ������\n");
			printf("���� �̸� : %s\n", lb.book.name);
			printf("���� ���� : %s\n", lb.book.writer);
			printf("���ǻ� : %s\n", lb.book.public);
			printf("���� ���� ��ȣ : %d\n", lb.book.sn);//���� ��ȣ�� �ݳ���.

			printf("\n------ ���� �뿩 ���� ------\n");
			printf("�뿩�� �̸� : %s\n", lb.user.username);
			printf("�뿩 ��¥ : %s\n", lb.user.date);
			printf("�ݳ� ���� ��¥ : %s\n", lb.user.return_date);
			printf("�뿩�� ��ȭ ��ȣ : 0%d\n", lb.user.user_number);
			char curtime_3day_add[40] = { 0, };//���簡 �Ǿ���.
			int d2 = get_time_3day_add(curtime_3day_add)-3;
			int c = d2 - lb.user.delay;
			if (d2 - lb.user.delay <= 0) {
				printf("�ݳ����� %d�� ���ҽ��ϴ�.", (-1) * (d2 - lb.user.delay));
			}
			else printf("%d�� ��ü�Ǿ����ϴ�.", d2 - lb.user.delay);
			
			printf("\n");
			count = 0;
		}
	}
	if (count == 1) {
		printf("�뿩���� �뿩 ������ �����ϴ�\n");
		return;
	}
	//==================== �ݳ��ϱ� ����1�� ���� 0���� �ٲٱ�
	//10_25�� ���� �ݳ��ϱ� �б�(1.�ݳ�,2.�뿩 ����(���ݽð�+3��)
	int check_loan_sn = 0;//�뿩�� �ݳ����� ó�� 1->0���� ����
	printf("=================================\n");
	printf("1.���� �ݳ�\n");
	printf("2.���� �뿩 ����\n");
	//�ݳ��� �����ϸ�  &check_loan_sn���� �Ѿ�� (����:loan_ct1)
	//�뿩 ������ �����ϸ� ������ 4�� �޴�ȭ������ �Ѿ��.(����:loan_ct2)
	int loan_num1=0;
	scanf("%d", &loan_num1);
	if (loan_num1 ==1) {
		printf("�ݳ��� ���Ͻø� ���� ���� ��ȣ�� �Է��ϼ���.\n");
		scanf("%d", &check_loan_sn);//�ٽ� �̸��� �Է¹޾Ƽ� ó��
		LIB dest[100] = { 0, };
		int idx = 0;
		int found = 0;
		rewind(fp); // ���� ������ ��ġ�� ó������ �̵�
		while (fread(&lb, sizeof(lb), 1, fp) == 1) {
			memcpy(&dest[idx], &lb, sizeof(lb));
			if (check_loan_sn == lb.book.sn) {//a,b�� ������
				if (strcmp(lb.user.username, book_loan_word) == 0) {
					dest[idx].book.loan = 0;  //1->0���� �����ϱ�			
					found = 1;
				}
			}
			idx++;
		}
		fclose(fp);
		////-----------------------------------------------
		if (found == 0) {
			printf("�ش� ������ ã�� �� �����ϴ�.\n");
			return;
		}
		else if (found == 1) {
			FILE* fps = fopen("book.txt", "wt");//fps 's'�� ��������
			if (fps == NULL) {
				printf("������ ������ �� �����ϴ�.\n");
				return;
			}
			for (int i = 0; i < 100; i++) {
				if (strcmp(dest[i].book.name, "") != 0) {//������ �ƴϴ� //�����Ͱ� ����ִ�.//å�̸��� �������� ���
					if (strcmp(dest[i].user.username, "") == 0) {//�뿩�ڰ� ������
						fwrite(&dest[i], sizeof(LIB), 1, fps);//�׳� ���
					}
					else if (strcmp(dest[i].user.username, "") != 0) {//�뿩�ڰ� ������
						if (dest[i].book.loan == 0) {//�뿩�ڴ� �ִµ� �ݳ��� ��å. - �뿩�� ������ ��������Ҷ�
							strcpy(dest[i].user.username, "");//�뿩�� �̸��� ���� �� �����ش�.
							strcpy(dest[i].user.date, "");
							//
							strcpy(dest[i].user.return_date, "");
							strcpy(dest[i].user.bookname, "");
							//strcpy(dest[i].user.user_number, "");
							//strcpy(dest[i].user.delay, "");
							///�뿩�� ���� �����
							fwrite(&dest[i], sizeof(LIB), 1, fps);//�������� ���
						}
						else//�뿩�ڰ� �ְ� �뿩�����϶�
							fwrite(&dest[i], sizeof(LIB), 1, fps);//�״�� ���
					}
				}
			}
			fclose(fps);
			memset(dest, 0, sizeof(LIB) * 100);
			printf("%d ������ ���� ���Դϴ�.\n", lb.book.loan);
			Sleep(500);
			//view_book_loan_after();
		}
		return;

	}
	else if (loan_num1 ==2) {
		update_curtime_3day_add();
		return;
	}

	
}

void update_curtime_3day_add()//(((�뿩 ����)))) 10��25�� �ۼ���.
{
	FILE* fp = fopen("book.txt", "rt");//<<�������°�
	if (fp == NULL) {
		printf("������ ���� �� �����ϴ�.\n");
		return;
	}
	LIB lb = { 0, };
	int input_book_updata = 0;//�Է°��̶� ������ȣ ��

	printf("�뿩 ������ ���ϴ� ������ ���� ��ȣ�� �Է��ϼ���.\n");
	scanf("%d", &input_book_updata);
	
	LIB dest[100] = { 0, };
	int idx = 0;
	int found_3day = 0;
	while (fread(&lb, sizeof(lb), 1, fp) == 1) {
		memcpy(&dest[idx], &lb, sizeof(lb));
		//if (input_book_updata == lb.book.sn && )) {
		if(input_book_updata == lb.book.sn && dest[idx].book.loan == 1){
		//�뿩 ��¥
			char curtime[30] = { 0, };//���簡 �Ǿ���.
			get_time(curtime);
			strcpy(dest[idx].user.date, curtime);//�ٽ� ����ü�� ����.

			char curtime_3day_add[40] = { 0, };//���簡 �Ǿ���.
			int d = get_time_3day_add(curtime_3day_add);
			dest[idx].user.delay = d;
			strcpy(dest[idx].user.return_date, curtime_3day_add);//�ٽ� ����ü�� ����.

			printf("��û��¥ : %s\n", dest[idx].user.date);
			printf("�ݳ� ���� ��¥ : %s(�뿩�Ⱓ+3��)\n", dest[idx].user.return_date);//+�뿩�Ⱓ �߰�
			found_3day = 1;
		}
		idx++;
	}
	fclose(fp);
	if (found_3day == 0) {
		printf("�ش� ������ ã�� �� �����ϴ�.\n");		
		return;
	}
	else if (found_3day == 1) {
		FILE* fps = fopen("book.txt", "wb");//, ���̳ʸ�:b
		if (fps == NULL) {
			printf("������ ������ �� �����ϴ�.\n");
			return;
		}
		for (int i = 0; i < 256; i++) {
			if (strcmp(dest[i].book.name, "") != 0) {//������ �ƴϴ� //�����Ͱ� ����ִ�.
				fwrite(&dest[i], sizeof(LIB), 1, fps);
			}
			else break;
		}
		fclose(fps);
		memset(dest, 0, sizeof(LIB) * 100);
		printf("�뿩 ���� ���Դϴ�.\n");
		Sleep(1000);
		void return_view_book_loan();
	}
	return;
}