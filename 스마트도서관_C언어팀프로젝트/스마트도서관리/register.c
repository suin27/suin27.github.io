#include "crt.h"
#include<stdio.h>
#include<Windows.h>
#include "lib.h"
#include"register.h"
int cert_w() {
	FILE* fcw = NULL;
	fcw = fopen("register.txt", "a");
	if (fcw == NULL) {
		printf("������ ������ �� �����ϴ�.");
		return;
	}
	REGI re = { 0, };
	printf("�ű� �����ڸ� ����մϴ�. �̸��� �Է��ϼ��� : ");
	scanf("%s", re.name);
	printf("����Ͻ� ID�� �Է��ϼ��� : ");
	getchar();
	gets_s(re.id, sizeof(char) * 20);
	rewind(stdin);
	int q = 0;
	while (1) {
		char pw[20]={0,};
		printf("����Ͻ� ��й�ȣ�� �Է��ϼ��� : ");
		gets_s(re.pas, sizeof(char) * 20);
		rewind(stdin);
		printf("��й�ȣ�� �ѹ� �� �Է��ϼ��� : ");
		gets_s(pw, sizeof(char) * 20);
		rewind(stdin);
		if (strcmp(pw, re.pas) == 0) {
			printf("������ ����� �Ϸ�Ǿ����ϴ�.\n");
			system("pause");
			q = 2;
			break;
		}
		else {
			printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �����ϼ���.\n"); 
		}
	}
	printf("=================================\n");
	fwrite(&re, sizeof(re), 1, fcw);
	fclose(fcw);
	return q;
}

int cert_r() {
	int q = 0;
	for (int i = 0; i < 3; i++) {
		FILE* fcr = NULL;
		fcr = fopen("register.txt", "r");
		if (fcr == NULL) {
			printf("������ ������ �����ϴ�. �����ڸ� �����մϴ�.\n");
			int q=cert_w();
			return q;
		}
		if (i >= 1) {
		
		}
		if (i == 0) {
			getchar();
		}
		REGI re2 = { 0, };
		//printf(" ���������� ���ٸ� \n	��µ� �����ϴ�\n");
		//printf(" ���� ������ ����մϴ�\n");
		
		printf("���̵� : ");
		gets_s(re2.id, sizeof(char) * 20);
		rewind(stdin);
		
		printf("PW : ");
		gets_s(re2.pas, sizeof(char) * 20);
		rewind(stdin);
		REGI re = { 0, };
		printf("=================================\n");
		
		int cot = 1;
		int t = 0;
		int p = 0;
		while (fread(&re, sizeof(re), 1, fcr) == 1) {
			if (strcmp(re.id, re2.id) == 0) {
				t++;
				if (strcmp(re.pas, re2.pas) != 0) {
					printf("���̵� Ȥ�� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է��ϼ���2.\n");
				}
				else if (strcmp(re.pas, re2.pas) == 0) {
					printf("�α�����...");
					Sleep(750);
					q = 1;
				}
			}
			
		}
		if (t == 0) {
			printf("���̵� Ȥ�� ��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �Է��ϼ���.\n");
		}
		fclose(fcr);
		if (q == 1) {
			break;
		}
	}
	return q;
}