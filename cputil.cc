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
	
}
//get all checkpoint info
void CpConnection::getCP(){
	if(!this->info_file){
		printf("Cannot access cp_info file.\n");
		return;
	}
	fputs("cp a", this->info_file);
	fflush(this->info_file);

	/* format info */
	while(fgets(this->info_line, MAX_INFO_LINE_LEN, this->info_file)) {
		if(!strncmp(this->info_line, "------",6)){
			break;
		}	
		printf("%s", this->info_line);
	}
	while(fgets(this->info_line, MAX_INFO_LINE_LEN, this->info_file)) {
		if(strlen(this->info_line)!=1) {
			printf("%s", this->info_line);
		}
	}
}
//get the checkpoint info with the version number
bool CpConnection::getCP(unsigned int version){
	unsigned int cur_ver;
        bool found = false;
	if(!this->info_file){
		printf("Cannot access cp_info file.\n");
		return false;
	}
	fputs("cp a", this->info_file);
	fflush(this->info_file);

	while(fgets(this->info_line, MAX_INFO_LINE_LEN, this->info_file)) {
		if(found) {
			if(!strncmp(this->info_line, "version", 7))
				break;
			printf("%s", this->info_line);
		}
		else {
			if(!strncmp(this->info_line, "version",7)){
				sscanf(this->info_line, "version: %u", &cur_ver);
				if(cur_ver == version)
					found = true;
			}
		}	
	}
	return found;
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
	cpConn->getCP(2);
	delete cpConn;
	return 0;
}
