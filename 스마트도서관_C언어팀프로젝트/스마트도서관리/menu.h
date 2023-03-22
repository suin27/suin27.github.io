#ifndef __MENU_H__
#define __MENU_H__

typedef enum {//main menu(1~7) - 상수 이름 정의//직관성을 위하여.
	//->case 1 보다는 mainput이 더 직관적. //여기서는 하드코딩 방지용. 
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
	MA_READ, //연체도서목록
	MA_MORE
}MAIN_MENU;

extern int main_menu();
extern int main_menu2();

#endif
