
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char scm[16]= "\0";
	char flag[1]="\0";
	int status=0;


	status = cgiFormString("scm",  scm, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scm error!\n");
		return 1;
	}

	status = cgiFormString("flag", flag, 1);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get flag error!\n");
		return 1;
	}


	fprintf(cgiOut, "scm=%s ,flag=%s \n", scm,flag);
	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	if(strcmp(flag,1) == 0){
		sprintf(sql, "delete from School where scm = '%s'", scm);
		if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}else{
		strcpy(scm,"001");
		sprintf(sql, "update School set scm='%s' ",scm);
		if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}


	fprintf(cgiOut, "delete stu ok!\n");
	mysql_close(db);

	return 0;
}
