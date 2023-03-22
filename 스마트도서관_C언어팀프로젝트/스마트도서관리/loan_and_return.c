#include "crt.h"
#include<stdio.h>
#include<Windows.h>
#include "lib.h"
#include "loan_and_return.h"
#include <time.h>
void user_loan_input();
//10월 21일
//대여 날짜, 반납 날짜 구현함.
//대여이후 화면 대여자만 출력으로 수정
//도서 이름이 같은 경우가 있어서 책 대여의 키워드를 도서 고유 번호로 변경함.

//10월 25일 대여:반납,대여 갱신으로 분류함. 날짜를 현시간 기준으로 3일 덮어씀.
//void update_curtime_3day_add() 함수 추가.

void get_time(char* tinfo)//시간함수1
{
	time_t timer;
	struct tm* t; //timer : 1970년 1월 1일 0시 0초부터~ 현재까지 초
	timer = time(NULL);
	t = localtime(&timer);
	char buf[30] = { 0, };//배열안에 담겨있음.//5일을 늘릴려면 인트정보로하고
	//년,월,일을 세분화 시켜서 증가시켜야됨.//sprintf(buf, "%d년%d월%d일-%d시%d분%d초",
	sprintf(buf, "%d년%d월%d일",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday);
	//	t->tm_hour,
	//	t->tm_min,
	//	t->tm_sec);
	strcpy(tinfo, buf);//복사
}

int  get_time_3day_add(char* tinfo)//시간함수2(+3일추가)
{
	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);
	char buf[30] = { 0, };
	sprintf(buf, "%d년%d월%d일",
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday + 3);	
	strcpy(tinfo, buf);//복사
	int d = 0;
	d = (t->tm_year + 1900) * 10000 + (t->tm_mon + 1) * 100 + t->tm_mday + 3;
	return d;
}

void view_book_loan()//대여 초기 화면
{
	FILE* fpr = fopen("book.txt", "rt");
	if (fpr == NULL) {
		printf("파일을 읽을 수 없습니다.\n");
		return;
	}
	LIB lb = { 0, };
	printf("============================\n");
	printf("book.txt에서 읽은 정보\n");

	int count = 1;
	while (fread(&lb, sizeof(lb), 1, fpr) == 1)
	{
		printf("■■■■■ 도서 정보 ■■■■■\n");
		printf("도서 이름: %s\n", lb.book.name);
		printf("도서 저자: %s\n", lb.book.writer);
		printf("출판사: %s\n", lb.book.public);
		printf("카테고리: %s\n", lb.book.cate);
		printf("영화 유무: %c\n", lb.book.movie_search);
		printf("도서 검색 횟수: %d\n", lb.book.search_num);
		printf("도서 고유 번호: %d\n", lb.book.sn);//고유번호 검색아래둠.
		//printf("대여 여부: %d\n", lb.book.loan);
		if (lb.book.loan == 0||lb.book.loan==2)//도서 대여 정의: 0대여 가능,1불가능
		{
			printf("대여 여부 : 가능\n");
		}
		else
		{
			printf("대여 여부 : 불가능\n");
		}

		if (lb.book.movie_search == 1)
		{
			printf("\n------ 영화 정보 ------\n");
			printf("영화 이름 : %s\n", lb.movie.name);
			printf("영화 시청 사이트 : %s\n", lb.movie.site);
			printf("영화 감독명 : %s\n", lb.movie.name);
			printf("영화 가격 : %d\n", lb.movie.price);
		}
		else
		{
			printf("영화가 없는 도서입니다.\n");
		}
		printf("\n------ 도서 구매 정보 ------\n");
		printf("도서 이름: %s\n", lb.buybook.name);
		printf("구매 사이트 이름: %s\n", lb.buybook.site);
		printf("도서 가격: %d\n", lb.buybook.price);
		printf("\n");
	}
	fclose(fpr);
	book_loan_act();
}

void book_loan_act()//대여가 발생한다.(책이름에서->시리얼 넘버로 변경함.10월21일
{
	FILE* fp = fopen("book.txt", "rt");//<<가져오는것
	if (fp == NULL) {
		printf("파일을 읽을 수 없습니다.\n");
		return;
	}
	LIB lb = { 0, };
	int input_book_number = 0;//책 이름 입력받을 임시 변수(char에서 int로 변경)
	//int input_book_name->int input_book_number로변경10_25일

	printf("대여를 원하는 도서의 고유 번호을 입력하세요.\n");
	printf("0. 메인 메뉴로 돌아가기\n");
	scanf("%d", &input_book_number);
	
	if (input_book_number == 0) {
		printf("메인 메뉴로 돌아가기\n");
		return;
	}
	//lb.book.loan 비교할 대상
	//만약 input_book_name과 loan_book_name이 같다면// lb.book.loan을
	//1로 입력한다.
	LIB dest[100] = { 0, };
	int idx = 0;
	int found = 0;
	//char rent_name[20] = { 0, };//함수로 대여 이후 화면으로 값넘기기
	while (fread(&lb, sizeof(lb), 1, fp) == 1) {
		memcpy(&dest[idx], &lb, sizeof(lb));
		if (input_book_number == lb.book.sn && dest[idx].book.loan == 1) {
			printf("이미 대여된 도서는 대여불가합니다.\n");
			//printf("대여 가능한 도서를 선택하세요.\n");
			Sleep(500);
			found = 4;
			break;
		}
		if (input_book_number == lb.book.sn) {
			dest[idx].book.loan = 1;
			printf("대여자의 이름을 입력하세요.\n");
			scanf("%s", dest[idx].user.username);
			//strcpy(rent_name, dest[idx].user.username);//입력받은 값을 rent_name로 복사

			//대여 날짜
			char curtime[30] = { 0, };//복사가 되어짐.
			get_time(curtime);
			strcpy(dest[idx].user.date, curtime);//다시 구조체에 복사.


			char curtime_3day_add[40] = { 0, };//복사가 되어짐.
			int d = get_time_3day_add(curtime_3day_add);
			dest[idx].user.delay = d;
			strcpy(dest[idx].user.return_date, curtime_3day_add);//다시 구조체에 복사.

			printf("신청날짜 : %s\n", dest[idx].user.date);
			printf("반납 예정 날짜 : %s(대여기간+3일)\n", dest[idx].user.return_date);//+대여기간 추가

			printf("대여자 전화 번호(숫자만 입력하세요)\n");
			scanf("%d", &dest[idx].user.user_number);
			found = 1;
		}
		
		idx++;
	}
	fclose(fp);

	if (found == 0) {
		printf("대여할 정보를 찾을 수 없습니다.\n");
		Sleep(500);
		return;
	}
	else if (found == 1) {
		FILE* fps = fopen("book.txt", "wb");//, 바이너리:b
		if (fps == NULL) {
			printf("파일을 생성할 수 없습니다.\n");
			return;
		}
		for (int i = 0; i < 256; i++) {
			if (strcmp(dest[i].book.name, "") != 0) {//공백이 아니다 //데이터가 들어있다.
				fwrite(&dest[i], sizeof(LIB), 1, fps);
			}
			else break;
		}
		fclose(fps);
		memset(dest, 0, sizeof(LIB) * 100);
		Sleep(500);
		view_book_loan_after(input_book_number);
	}
	return;
}


void view_book_loan_after(int number)//대여 후기 화면(문제:대여한 모든 사람이 보인다)
{
	system("cls");
	FILE* fp;
	LIB lb = { 0, };

	fp = fopen("book.txt", "rt");//정보 추가-새로 추가가 아니라 정보를 읽어와서 수정 및 삭제처리하는것
	//기록//넘버 정해서 받기-리드로 정보를 따와서 수정하기.
	while (fread(&lb, sizeof(lb), 1, fp) == 1) {
		//if (lb.book.loan == 1) {loan이 1이면 보여준다.( strcmp( str1, str2 ) == 0 )//문자열비교 셈플	
		//if (strcmp(lb.user.username, name) == 0 && lb.book.loan == 1) { //대여자 이름일치, loan이 1이면 show
		if (lb.book.sn == number) { //대여자 이름일치, loan이 1이면 show
			printf("\n------ 도서 대여 정보 ------\n");
			printf("도서 고유 번호 : %d\n", lb.book.sn);
			printf("도서 이름 : %s\n", lb.book.name);
			printf("도서 저자 : %s\n", lb.book.writer);
			printf("출판사 : %s\n", lb.book.public);

			printf("\n------ 도서 대여자 정보 ------\n");

			printf("대여자 이름 : %s\n", lb.user.username);
			printf("대여 날짜 : %s\n", lb.user.date);
			printf("반납 예정 날짜 : %s(대여기간+3일)\n", lb.user.return_date);//+대여기간 추가
			printf("대여자 전화 번호 : 0%d\n", lb.user.user_number);

			printf("연체 유무 : %d\n", lb.user.delay);
			printf("\n");
			printf("%s대여 하셨습니다.\n", lb.user.username);
			
		}
	}
	fclose(fp);
	//view_book_loan();대여 매인뷰
	return;
}

void return_view_book_loan()//이름 검색>>자료와 비교>같다면>출력>반납처리
{
	printf("\n------ 도서 반납 처리 ------\n");
	FILE* fp = fopen("book.txt", "rt");
	if (fp == NULL) {
		printf("파일을 읽을 수 없습니다.\n");
		return;
	}
	LIB lb = { 0, };
	char book_loan_word[20] = { 0, };//검색입력 단어지정
	//char check_loan_name[20];//대여를 반납으로 처리 1->0으로 변경
	printf("대여자의 이름을 입력하세요. : ");
	scanf("%s", book_loan_word);//검색 단어 입력

	printf("=================================\n");
	printf("검색 결과\n");
	printf("=================================\n");

	int count = 1;
	while (fread(&lb, sizeof(lb), 1, fp) == 1)//검색 결과 출력하기
	{
		if (strcmp(book_loan_word, lb.user.username) == 0)//검색된 이름 : 대여자 이름 비교
		{
			printf("검색결과 : %s님은 대여가 있습니다.\n", lb.user.username);

			printf("■■■■■ 도서 정보 ■■■■■\n");
			printf("도서 이름 : %s\n", lb.book.name);
			printf("도서 저자 : %s\n", lb.book.writer);
			printf("출판사 : %s\n", lb.book.public);
			printf("도서 고유 번호 : %d\n", lb.book.sn);//고유 번호로 반납함.

			printf("\n------ 도서 대여 정보 ------\n");
			printf("대여자 이름 : %s\n", lb.user.username);
			printf("대여 날짜 : %s\n", lb.user.date);
			printf("반납 예정 날짜 : %s\n", lb.user.return_date);
			printf("대여자 전화 번호 : 0%d\n", lb.user.user_number);
			char curtime_3day_add[40] = { 0, };//복사가 되어짐.
			int d2 = get_time_3day_add(curtime_3day_add)-3;
			int c = d2 - lb.user.delay;
			if (d2 - lb.user.delay <= 0) {
				printf("반납까지 %d일 남았습니다.", (-1) * (d2 - lb.user.delay));
			}
			else printf("%d일 연체되었습니다.", d2 - lb.user.delay);
			
			printf("\n");
			count = 0;
		}
	}
	if (count == 1) {
		printf("대여자의 대여 정보가 없습니다\n");
		return;
	}
	//==================== 반납하기 숫자1을 숫자 0으로 바꾸기
	//10_25일 도서 반납하기 분기(1.반납,2.대여 갱신(지금시간+3일)
	int check_loan_sn = 0;//대여를 반납으로 처리 1->0으로 변경
	printf("=================================\n");
	printf("1.도서 반납\n");
	printf("2.도서 대여 갱신\n");
	//반납을 선택하면  &check_loan_sn으로 넘어가고 (변수:loan_ct1)
	//대여 갱신을 선택하면 변경후 4번 메뉴화면으로 넘어간다.(변수:loan_ct2)
	int loan_num1=0;
	scanf("%d", &loan_num1);
	if (loan_num1 ==1) {
		printf("반납을 원하시면 도서 고유 번호를 입력하세요.\n");
		scanf("%d", &check_loan_sn);//다시 이름을 입력받아서 처리
		LIB dest[100] = { 0, };
		int idx = 0;
		int found = 0;
		rewind(fp); // 파일 포인터 위치를 처음으로 이동
		while (fread(&lb, sizeof(lb), 1, fp) == 1) {
			memcpy(&dest[idx], &lb, sizeof(lb));
			if (check_loan_sn == lb.book.sn) {//a,b가 같은가
				if (strcmp(lb.user.username, book_loan_word) == 0) {
					dest[idx].book.loan = 0;  //1->0으로 변경하기			
					found = 1;
				}
			}
			idx++;
		}
		fclose(fp);
		////-----------------------------------------------
		if (found == 0) {
			printf("해당 정보를 찾을 수 없습니다.\n");
			return;
		}
		else if (found == 1) {
			FILE* fps = fopen("book.txt", "wt");//fps 's'는 파일저장
			if (fps == NULL) {
				printf("파일을 생성할 수 없습니다.\n");
				return;
			}
			for (int i = 0; i < 100; i++) {
				if (strcmp(dest[i].book.name, "") != 0) {//공백이 아니다 //데이터가 들어있다.//책이름이 있을때만 출력
					if (strcmp(dest[i].user.username, "") == 0) {//대여자가 없을때
						fwrite(&dest[i], sizeof(LIB), 1, fps);//그냥 출력
					}
					else if (strcmp(dest[i].user.username, "") != 0) {//대여자가 있을때
						if (dest[i].book.loan == 0) {//대여자는 있는데 반납이 된책. - 대여자 정보를 없애줘야할때
							strcpy(dest[i].user.username, "");//대여자 이름을 공백 즉 지워준다.
							strcpy(dest[i].user.date, "");
							//
							strcpy(dest[i].user.return_date, "");
							strcpy(dest[i].user.bookname, "");
							//strcpy(dest[i].user.user_number, "");
							//strcpy(dest[i].user.delay, "");
							///대여자 공백 지우기
							fwrite(&dest[i], sizeof(LIB), 1, fps);//이정보를 출력
						}
						else//대여자가 있고 대여상태일때
							fwrite(&dest[i], sizeof(LIB), 1, fps);//그대로 출력
					}
				}
			}
			fclose(fps);
			memset(dest, 0, sizeof(LIB) * 100);
			printf("%d 정보가 수정 중입니다.\n", lb.book.loan);
			Sleep(500);
			//view_book_loan_after();
		}
		return;

	}
	else if (loan_num1 ==2) {
		update_curtime_3day_add();
		return;
	}

	
}

void update_curtime_3day_add()//(((대여 갱신)))) 10월25일 작성함.
{
	FILE* fp = fopen("book.txt", "rt");//<<가져오는것
	if (fp == NULL) {
		printf("파일을 읽을 수 없습니다.\n");
		return;
	}
	LIB lb = { 0, };
	int input_book_updata = 0;//입력값이랑 도서번호 비교

	printf("대여 갱신을 원하는 도서의 고유 번호을 입력하세요.\n");
	scanf("%d", &input_book_updata);
	
	LIB dest[100] = { 0, };
	int idx = 0;
	int found_3day = 0;
	while (fread(&lb, sizeof(lb), 1, fp) == 1) {
		memcpy(&dest[idx], &lb, sizeof(lb));
		//if (input_book_updata == lb.book.sn && )) {
		if(input_book_updata == lb.book.sn && dest[idx].book.loan == 1){
		//대여 날짜
			char curtime[30] = { 0, };//복사가 되어짐.
			get_time(curtime);
			strcpy(dest[idx].user.date, curtime);//다시 구조체에 복사.

			char curtime_3day_add[40] = { 0, };//복사가 되어짐.
			int d = get_time_3day_add(curtime_3day_add);
			dest[idx].user.delay = d;
			strcpy(dest[idx].user.return_date, curtime_3day_add);//다시 구조체에 복사.

			printf("신청날짜 : %s\n", dest[idx].user.date);
			printf("반납 예정 날짜 : %s(대여기간+3일)\n", dest[idx].user.return_date);//+대여기간 추가
			found_3day = 1;
		}
		idx++;
	}
	fclose(fp);
	if (found_3day == 0) {
		printf("해당 정보를 찾을 수 없습니다.\n");		
		return;
	}
	else if (found_3day == 1) {
		FILE* fps = fopen("book.txt", "wb");//, 바이너리:b
		if (fps == NULL) {
			printf("파일을 생성할 수 없습니다.\n");
			return;
		}
		for (int i = 0; i < 256; i++) {
			if (strcmp(dest[i].book.name, "") != 0) {//공백이 아니다 //데이터가 들어있다.
				fwrite(&dest[i], sizeof(LIB), 1, fps);
			}
			else break;
		}
		fclose(fps);
		memset(dest, 0, sizeof(LIB) * 100);
		printf("대여 갱신 중입니다.\n");
		Sleep(1000);
		void return_view_book_loan();
	}
	return;
}