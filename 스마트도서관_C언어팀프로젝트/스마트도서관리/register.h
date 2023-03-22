#ifndef __REGISTER_H__
#define __REGISTER_H__

typedef struct _REGI {
	char id[20];
	char pas[20];
	char name[10];
}REGI;//한 관리자에 대한 정보

extern int cert_w();
extern int cert_r();

#endif

