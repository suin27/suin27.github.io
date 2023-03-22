#ifndef __LIB_H__
#define __LIB_H__

typedef struct _BOOK {
	int sn; //책 고유 번호
	char name[100]; //책 이름
	char writer[100]; //책 저자
	char public[100]; //책 출판사
	int loan; //대여 유무
	char cate[100]; //책 카테고리
	int search_num; //검색 횟수
	int movie_search;//영화 유무파악.
}BOOK;//한 책에 관한 정보



typedef struct _MOVIE {
	char name[100];
	char site[100];
	char producer[100];
	int price;
}MOVIE; //한 영화에 대한 정보

typedef struct _BUYBOOK {
	int price; // 책 가격
	char site[100]; //책 구매 사이트
	char name[100];//책 이름

}BUYBOOK;// 도서 구매 정보

typedef struct _USER {
	char username[20];	//대여자 이름
	char date[30]; // 대여 날짜
	char return_date[30]; // 반납 예정 날짜(대여날짜+3d	)
	char bookname[100]; //책 이름
	int user_number; //대여자 전화 번호
	int delay;//연체 유무 파악.
}USER;//대여자 정보

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


