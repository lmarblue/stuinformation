#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char  tno[32] = "\0";
	char  tname[32] = "\0";
	char  tsex[32] = "\0";
  char tage[32]="\0";
	char location[32]="\0";
	char tel[32]="\0";
  char acno[32]="\0";
  char scm[32]="\0";
   	//char fl[8] = "\0";
  //char president[10]="\0";
	int status = 0;

	status = cgiFormString("tno",  tno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get tno error!\n");
		return 1;
	}

	status = cgiFormString("tname",  tname, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get tname error!\n");
		return 1;
	}

	status = cgiFormString("tsex",  tsex, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get tsex  error!\n");
		return 1;
	}

	status = cgiFormString("tage",  tage, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get tage  error!\n");
		return 1;
	}

 		status = cgiFormString("tel",  tel, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get tel error!\n");
		return 1;
	}

	status = cgiFormString("location",  location, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get location error!\n");
		return 1;
	}

	status = cgiFormString("acno",  acno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get acno  error!\n");
		return 1;
	}

	status = cgiFormString("scm",  scm, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scm  error!\n");
		return 1;
	}
	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	mysql_options(db,MYSQL_SET_CHARSET_NAME,"utf8");
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



	strcpy(sql, "create table teacher(tno varchar(32)  primary key,tname varchar(32) not null,tage varchar(32) check(tage between 1 and 120),tsex varchar(32) check(tsex in ('男' ,'女')),location varchar(32),tel varchar(32),acno varchar(32),scm varchar(32),fl varchar(8),foreign key (acno) references academy(acno),foreign key (scm) references School(scm))character set = utf8;");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}



	sprintf(sql, "insert into teacher values('%s', '%s', '%s','%s','%s','%s', '%s','%s','1')", tno,tname,tage,tsex,location,tel,acno,scm );
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add teacher ok!\n");
	mysql_close(db);
	return 0;
}
