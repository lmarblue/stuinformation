#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"


int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
/*	fprintf(cgiOut, "<head><meta charset=\"utf-8\"/><title>查询结果</title>\
			<style>table {width:400px; margin: 50px auto; border: 1px solid gray; border-collapse: collapse; border-spacing: none; text-align:center;}\
			tr,td,th{border: 1px solid gray;}\
			</style>\
			</head>");*/

	fprintf(cgiOut, "<head><meta charset=\"utf-8\"><title>查询结果</title>\
		    <link rel=\"stylesheet\" href=\"/stu/public/css/bootstrap.min.css\">\
		</head>");


    //char  cno[32]="\0";
    char sno[32] = "\0";
    char password[32]="\0";

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

	int ret;
	MYSQL *db;
	char sql[128] = "\0";

	sprintf(sql, "select sno,password from suser where sno='%s' and password='%s' ",sno,password);
	//fprintf(cgiOut, "%s\n",sql );
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


	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	MYSQL_RES *res;
	res = mysql_store_result(db);
	if (res == NULL)
	{
		fprintf(cgiOut,"mysql_store_result fail:%s\n", mysql_error(db));
		return -1;
	}


	MYSQL_ROW  row;

	if((row = mysql_fetch_row(res)) != NULL){
		fprintf(cgiOut,"<a href=\"/sinfo.html\">点击进入学生页面</a>");
	}else{
		fprintf(cgiOut,"<a href=\"/login_stu.html\">学号或密码错误点击重输</a>");
	}



	mysql_close(db);

	return 0;
}
