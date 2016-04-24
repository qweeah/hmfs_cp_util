//cputil.cc
#include"cputil.h"

//Constructor
CpConnection::CpConnection(unsigned long phys_addr){
	sprintf(this->info_path, "/sys/kernel/debug/hmfs/%ld/info", phys_addr);
	this->info_file = NULL;
}

//Destructor
CpConnection::~CpConnection(){
	if(this->info_file) {
		printf("closing...\n");
		fclose(this->info_file);
	}	
}

//establish the connection
int CpConnection::connect(){
	this->info_file = fopen(info_path, "r+");
	if(!this->info_file) {
		printf("Cannot access cp_info file.\n");
		return 0;
	}
	/* test: send query & output*/
	fputs("cp a", this->info_file);
	fflush(this->info_file);
	while(fgets(this->info_line, MAX_INFO_LINE_LEN, this->info_file)) {
		if(strlen(this->info_line)!=1) {
			printf("%d:%s", strlen(this->info_line), this->info_line);
		}
	}	
}

char* CpConnection::getPath(){
	return this->info_path;
}
int main(){
	unsigned long phys_addr;
	printf("Please input physical address:\n");
	scanf("%ld", &phys_addr);
	CpConnection *cpConn = new CpConnection(phys_addr);
	puts(cpConn->getPath());
	cpConn->connect();
	delete cpConn;
	return 0;
}
