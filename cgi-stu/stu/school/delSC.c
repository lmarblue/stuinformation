
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char scm[16]= "\0";
	char flag[8]="\0";
	int status=0;


	status = cgiFormString("scm",  scm, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get scm error!\n");
		return 1;
	}

	status = cgiFormString("flag", flag, 8);
	//fprintf(cgiOut, "flag = [%s] status=[%d]\n", flag, status);
	//fprintf(cgiOut, "<hr>scm=%s ,flag=%s \n", scm,flag);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get flag error!\n");
		return 1;
	}


	// fprintf(cgiOut, "scm=%s ,flag=%s \n", scm,flag);
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

   //fprintf(cgiOut, "scm=%s ,flag=%s \n", scm,flag);

	 if(flag[0]== '1'){
	 	sprintf(sql, "delete from School where scm = '%s' ", scm);
	 	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	 	{
	 		fprintf(cgiOut,"mysql_real_query fail11:%s\n", mysql_error(db));
	 		mysql_close(db);
	 		return -1;
	 	}
	 }else{
	 	sprintf(sql, "update School set fl = '0' where scm='%s' ",scm);
	 	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	 	{
	 		fprintf(cgiOut,"mysql_real_query fail22:%s\n", mysql_error(db));
	 		mysql_close(db);
	 		return -1;
	 	}
	 }


	 fprintf(cgiOut, "delete School ok!\n");
	 mysql_close(db);

	return 0;
}
