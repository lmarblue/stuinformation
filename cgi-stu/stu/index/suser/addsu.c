#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

  char  sno[32]="\0";
  char  password[32]="\0";

	FILE * fd;
  char ch;
  fd=fopen("head.html", "r");
  if(fd==NULL){
  	fprintf(cgiOut, "Cannot open file,head.html \n");
  	return -1;
	}
   ch = fgetc(fd);
   while(ch != EOF){
   	fprintf(cgiOut, "%c", ch);
    ch = fgetc(fd);
	}
   close(fd);
   	//char fl[8] = "\0";
  //char president[10]="\0";
	int status = 0;

	status = cgiFormString("sno",  sno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sno error!\n");
		return 1;
	}

	status = cgiFormString("password",  password, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get password error!\n");
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



	strcpy(sql, "create table suser(sno varchar(32) primary key, password varchar(32) not null ,fl varchar(8),foreign key (sno) references student(sno))character set = utf8;");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}



	sprintf(sql, "insert into suser values('%s', '%s','1')", sno,password);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add suser ok!\n");
	mysql_close(db);
	return 0;
}
