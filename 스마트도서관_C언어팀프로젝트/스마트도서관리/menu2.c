#include "crt.h"
#include<stdio.h>
#include "menu.h"
int main_menu2() {
	printf("=================================\n");
	printf(" ���� ���� App v1.0\n");
	printf("=================================\n");
	printf(" 1. ���� ����\n");
	printf(" 2. ���� �˻�\n");
	printf(" 3. ���� �뿩\n");
	printf(" 4. ���� �ݳ�\n");
	printf(" 5. ���� ��õ\n");
	printf(" 6. ���� ����\n");
	printf(" 7. ���� �߰�\n");
	printf(" 8. ���� ����\n");
	printf(" 9. ���� ����\n");
	printf(" 10. ��ü�� ����\n");
	printf(" 0. ����\n");
	printf("=================================\n");
	printf(" �޴��� �����ϼ��� : ");
	int menu2 = -1;
	scanf("%d", &menu2);
	return menu2;
}