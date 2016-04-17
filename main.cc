//main.cc
#include "cputil.h"

#define MAX_TEXT_LEN 300

#define TEXT_MAIN "============ Main Menu ============\n"\
                  " 1. Checkpoints menu\n"\
                  " 2. List block usage\n"\
                  " 0. Exit\n"\
                  "===================================\n"

#define TEXT_CP "========== Checkpoint Menu ==========\n"\
                " 1. List all checkpoint info\n"\
                " 2. List one checkpoint info\n"\
                " 0. Back to main menu\n"\
                "=====================================\n"

//struct text_form {
//	void (*update)();
//	char text[MAX_TEXT_LEN];
//};
//struct text_form tForm;
CpConnection *cpConn;

void updateCPForm(){
	int x;
	unsigned int vNum;
	char c;
	while(scanf("%d", &x)) {
		switch(x){
			case 0: return;
			case 1: 
				cpConn->getCP();
				waitEnter();
				break;
			case 2:
				system("clear");
				printf("--- Input the version number ---\n");
				scanf("%u", &vNum);
				if(!cpConn->getCP(vNum)){
					printf("Checkpoint with version number '%d' not found!\n", vNum);
				}
				waitEnter();
			default:
				break;
		}
		system("clear");
		puts(TEXT_CP);
	}
	return;
}

void updateMainForm(){
	int x;
	while(scanf("%d", &x)) {
		switch(x){
			case 0: return;
			case 1: 
				system("clear");
				puts(TEXT_CP);	
				updateCPForm();
				break;
			case 2:
				system("clear");
				printf("Input the segment number:");
				scanf("%d", &x);
				cpConn->getSSA(x);
				waitEnter();
			default:
				break;
		}
		system("clear");
		puts(TEXT_MAIN);
	}
	return;
}

int main(){
	unsigned long phys_addr;
	printf("Please input physical address:\n");
	scanf("%ld", &phys_addr);
	//connect
	cpConn = new CpConnection(phys_addr);
//	cpConn->connect();

	system("clear");
	puts(TEXT_MAIN);
	updateMainForm();

	delete cpConn;
	return 0;
}
