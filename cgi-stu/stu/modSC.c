#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char scm[16] = "\0";
	char  scname[30]= "\0";
	char location[20] = "\0";
  char president[10]="\0";
  int status = 0;

	status = cgiFormString("scname",  scname, 30);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scname error!\n");
		return 1;
	}

	status = cgiFormString("location",  location, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get location error!\n");
		return 1;
	}

	status = cgiFormString("scm",  scm, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scm error!\n");
		return 1;
	}

	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

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
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "st",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}


	sprintf(sql, "update School set scname='%s', location='%s' ,president='%s' where scm ='%s' ", scname, location, president,scm);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "update School ok!\n");
	mysql_close(db);
	return 0;
}
