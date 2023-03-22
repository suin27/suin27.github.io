#include "crt.h"
#include<stdio.h>
#include<Windows.h>
#include "lib.h"
#include"register.h"
int cert_w() {
	FILE* fcw = NULL;
	fcw = fopen("register.txt", "a");
	if (fcw == NULL) {
		printf("파일을 생성할 수 없습니다.");
		return;
	}
	REGI re = { 0, };
	printf("신규 관리자를 등록합니다. 이름을 입력하세요 : ");
	scanf("%s", re.name);
	printf("사용하실 ID를 입력하세요 : ");
	getchar();
	gets_s(re.id, sizeof(char) * 20);
	rewind(stdin);
	int q = 0;
	while (1) {
		char pw[20]={0,};
		printf("사용하실 비밀번호를 입력하세요 : ");
		gets_s(re.pas, sizeof(char) * 20);
		rewind(stdin);
		printf("비밀번호를 한번 더 입력하세요 : ");
		gets_s(pw, sizeof(char) * 20);
		rewind(stdin);
		if (strcmp(pw, re.pas) == 0) {
			printf("관리자 등록이 완료되었습니다.\n");
			system("pause");
			q = 2;
			break;
		}
		else {
			printf("비밀번호가 일치하지 않습니다. 다시 진행하세요.\n"); 
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
			printf("관리자 정보가 없습니다. 관리자를 생성합니다.\n");
			int q=cert_w();
			return q;
		}
		if (i >= 1) {
		
		}
		if (i == 0) {
			getchar();
		}
		REGI re2 = { 0, };
		//printf(" 도서정보가 없다면 \n	출력도 없습니다\n");
		//printf(" 도서 정보를 출력합니다\n");
		
		printf("아이디 : ");
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
					printf("아이디 혹은 비밀번호가 틀렸습니다. 다시 입력하세요2.\n");
				}
				else if (strcmp(re.pas, re2.pas) == 0) {
					printf("로그인중...");
					Sleep(750);
					q = 1;
				}
			}
			
		}
		if (t == 0) {
			printf("아이디 혹은 비밀번호가 틀렸습니다. 다시 입력하세요.\n");
		}
		fclose(fcr);
		if (q == 1) {
			break;
		}
	}
	return q;
}