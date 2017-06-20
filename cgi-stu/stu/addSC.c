#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char  scm[16] = "\0";
	char scname[30] = "\0";
	char location[20] = "\0";
  char president[10]="\0";
	char bdate="null";
	int status = 0;

	status = cgiFormString("scm",  scm, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scm error!\n");
		return 1;
	}

	status = cgiFormString("scname",  scname, 30);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scname error!\n");
		return 1;
	}

	status = cgiFormString("location",  location, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get location  error!\n");
		return 1;
	}


	status = cgiFormString("president",  president, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get president error!\n");
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



	strcpy(sql, "create table School(scm smallint  primary key,scname varchar(30) not null,location varchar(20),president varchar(10))");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return ;
		}
	}



	sprintf(sql, "insert into School values('%s', '%s','%s','%s')", scm, scname,location,president );
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add School ok!\n");
	mysql_close(db);
	return 0;
}
