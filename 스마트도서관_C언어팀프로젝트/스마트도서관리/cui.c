#include"crt.h"
#include<stdio.h>
#include<windows.h>//ǥ�� c�� �ƴϴ�.-�����쿡���� ����� �� �ִ�.
#include "cui.h"

void gotoxy(int x, int y) {
	COORD pos = { x,y };//���⼭ coord�� ����ü�̴�
	//win32 api - ������ �ü������ �����ϴ� �Լ�
	//->>�ü������ �ް��ؼ� c�� �̷���� �ִ�.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);//�����쿡���� ����Ҽ� �ִ� �ý��� �Լ��̴�.
}//ȭ�鿡 ��ǥ ��� �Լ�

void new_title() {
	int x = 2;
	int y = 0;
	gotoxy(x, y + 1); printf("����������������������������������");//������ ��ǥ�� ���� ���� ������ �����϶�.
	gotoxy(x, y + 2); printf("��");
	for (int i = 2; i < 37; i++) {
		gotoxy(x, y + i); printf("��");
	}
	gotoxy(x, y + 8); printf("����������������������������������");
	//���� �׸� v1.0
	
	gotoxy(x + 6, y + 2); printf(" ��      �ܡܡ�   �ܡܡ�      �ܡ�       �ܡ�    ��    ��");
	gotoxy(x + 4, y + 3); printf(" ��  ��      ��     ��    ��  ��    ��   ��    ��  ��  ��");
	gotoxy(x + 4, y + 4); printf(" ��  ��      ��     �ܡܡ�   ��      �� ��      �� �ܡ�");
	gotoxy(x + 2, y + 5); printf(" ��  ��  ��    ��     �ܡܡ�   ��      �� ��      �� �ܡ�");
	gotoxy(x + 2, y + 6); printf(" ��      ��    ��     ��    ��  ��    ��   ��    ��  ��  ��  ");
	gotoxy(x + 2, y + 7); printf(" ��      ��  �ܡܡ�   �ܡܡ�      �ܡ�       �ܡ�    ��    ��");
	
	for (int i = 2; i < 37; i++) {
		gotoxy(x + 64, y + i); printf("��");
	}
	gotoxy(x, y + 36); printf("����������������������������������");


	x = 3;
	gotoxy(x, y + 12); printf(" �ءء� �޴� ���� �ءء�");
	gotoxy(x, y + 16); printf("�� ���� �˻�	: ��ϵ� ���� �� �˻��� ���� ������ ����մϴ�.");
	gotoxy(x, y + 18); printf("�� ���� �뿩	: ��ϵ� ���� �� ���ϴ� ������ �뿩ó�� �մϴ�.");
	gotoxy(x, y + 20); printf("�� ���� �ݳ�	: �뿩 ó���� ������ �ݳ�ó�� �մϴ�.");
	gotoxy(x, y + 22); printf("�� ���� ��õ	: �˻����� ���� ������ ����մϴ�.");
	gotoxy(x, y + 24); printf("�� ���� ���� ����	: ������ ���� ������ ����մϴ�.");
	gotoxy(x, y + 26); printf("�� ���� ����	: ������ ��ȣ�� �Է��ؾ߸� ����� �� �ֽ��ϴ�.");
	gotoxy(x, y + 28); printf("�� ���θ޴� �̵��� �ƹ�Ű�� ��������! ��");
}

void set_cursor_type(CURSOR_TYPE type) {//�� ���� ǥ�� c �� �ƴϴ�.
	CONSOLE_CURSOR_INFO curinfo;//�� ����ü�� 
	memset(&curinfo, 0, sizeof(curinfo));//�޸𸮸� �ʱ�ȭ
	switch (type) {
	case NOCURSOR:
		curinfo.dwSize = 1;
		curinfo.bVisible = FALSE;
		break;
	case SOLID_CURSOR:
		curinfo.dwSize = 100;
		curinfo.bVisible = TRUE;
		break;
	case NORMAL_CURSOR:
		curinfo.dwSize = 20;
		curinfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

void fontcolor(FONT_COLOR color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}