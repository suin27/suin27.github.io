#ifndef __MENU_H__
#define __MENU_H__

typedef enum {//main menu(1~7) - ��� �̸� ����//�������� ���Ͽ�.
	//->case 1 ���ٴ� mainput�� �� ������. //���⼭�� �ϵ��ڵ� ������. 
	MA_EXIT = 0,
	MA_LOOK=1,
	MA_SERACH = 2,
	MA_LOAN,
	MA_RETURN,
	MA_CHU,
	MA_BUY,
	MA_REGISTER = 7, MA_ADD = 7,
	MA_DEL = 8,
	MA_REFAIR,
	MA_READ, //��ü�������
	MA_MORE
}MAIN_MENU;

extern int main_menu();
extern int main_menu2();

#endif
