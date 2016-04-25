//cputil.h
#ifndef CPUTIL_H
#define CPUTIL_H

#include<cstdio>
#include<cstring>
#include<cstdlib>

class CpConnection{
	static const int MAX_PATH_LEN=300;
	char info_path[MAX_PATH_LEN];
	static const int MAX_INFO_LINE_LEN=300;
	char info_line[MAX_INFO_LINE_LEN];
	FILE* info_file;
public:
	CpConnection(unsigned long phys_addr);
	~CpConnection();

	int connect();
	void getCP();
	bool getCP(unsigned int version);
	char* getPath();
};

#endif
