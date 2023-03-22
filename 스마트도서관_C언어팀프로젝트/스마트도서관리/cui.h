#ifndef __CUI_H__//������� �ߺ� ���� ������ ���
#define __CUI_H__
//extern�� �����ص� ����� ���� ������ �����Ϸ��� �ڵ����� �ٿ��ֱ� ����

typedef enum {//enum-����(���)������ ����ϴ� ����
	NOCURSOR,//���ʴ�� ������� ������ 0 ���� 1�� ����ҽ�
	SOLID_CURSOR,//1					2
	NORMAL_CURSOR//2�� �ȴ�.				3�� �ȴ�. - �� ū���� ��������.�� �Ʒ��� ���������� +1�� ��/
}CURSOR_TYPE;

typedef enum {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	LIGHT_GRAY,
}FONT_COLOR;

extern void gotoxy(int x, int y);
extern void new_title();
extern void set_cursor_type(CURSOR_TYPE type);
extern void fontcolor(FONT_COLOR color);
#endif
