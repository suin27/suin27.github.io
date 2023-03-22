#ifndef __LIB_H__
#define __LIB_H__

typedef struct _BOOK {
	int sn; //å ���� ��ȣ
	char name[100]; //å �̸�
	char writer[100]; //å ����
	char public[100]; //å ���ǻ�
	int loan; //�뿩 ����
	char cate[100]; //å ī�װ�
	int search_num; //�˻� Ƚ��
	int movie_search;//��ȭ �����ľ�.
}BOOK;//�� å�� ���� ����



typedef struct _MOVIE {
	char name[100];
	char site[100];
	char producer[100];
	int price;
}MOVIE; //�� ��ȭ�� ���� ����

typedef struct _BUYBOOK {
	int price; // å ����
	char site[100]; //å ���� ����Ʈ
	char name[100];//å �̸�

}BUYBOOK;// ���� ���� ����

typedef struct _USER {
	char username[20];	//�뿩�� �̸�
	char date[30]; // �뿩 ��¥
	char return_date[30]; // �ݳ� ���� ��¥(�뿩��¥+3d	)
	char bookname[100]; //å �̸�
	int user_number; //�뿩�� ��ȭ ��ȣ
	int delay;//��ü ���� �ľ�.
}USER;//�뿩�� ����

typedef struct _LIB {
	BOOK book;
	MOVIE movie;
	BUYBOOK buybook;
	USER user;
}LIB;
extern int sn_overlap_no(int sn);
extern void book_lib_input();
extern void lib_lb_show(LIB);
#endif


