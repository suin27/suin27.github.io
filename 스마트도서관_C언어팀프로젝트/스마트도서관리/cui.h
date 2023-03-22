#ifndef __CUI_H__//헤더파일 중복 방지 때문에 사용
#define __CUI_H__
//extern은 생략해도 상관은 없다 어차피 컴파일러가 자동으로 붙여주기 때문

typedef enum {//enum-숫자(상수)정보를 대신하는 역할
	NOCURSOR,//차례대로 명시하지 않을시 0 만약 1로 명시할시
	SOLID_CURSOR,//1					2
	NORMAL_CURSOR//2가 된다.				3이 된다. - 더 큰수도 마찬가지.즉 아래로 내려갈수로 +1이 됨/
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
