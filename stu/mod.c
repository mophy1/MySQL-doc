#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"



char * headname = "head.html";
char * footname = "footer.html";
int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char studentNo[10] = "\0";
	char studentName[30] = "\0";
	char sex[10] = "\0";
	char birthday[30] = "\0";
	char school_id[20] = "\0";
	int status = 0;
	int ret;
	//char sql[128] = "\0";
	char ch;
  FILE * fd;

//	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
  fclose(fd);
	MYSQL *db;
	char sql[128] = "\0";

	status = cgiFormString("studentNo",  studentNo, 10);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get studentNo error!\n");
		return 1;
	}



	status = cgiFormString("studentName",  studentName, 30);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get studentName error!\n");
		return 1;
	}

	status = cgiFormString("sex",  sex, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get sex error!\n");
		return 1;
	}

	status = cgiFormString("birthday",  birthday, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get birthday error!\n");
		return 1;
	}

	status = cgiFormString("school_id",  school_id, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get school_id error!\n");
		return 1;
	}


	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu_info",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

mysql_set_character_set(db, "utf8");
	sprintf(sql, "update information set studentName = '%s',sex= '%s',birthday='%s' where studentNo = '%s' ", studentName, sex, birthday,studentNo);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;

	}




	fprintf(cgiOut, "<p style='margin-left:20px;'>update student ok!</p>");
	fprintf(cgiOut, "<input type='button' name='button1' id='button1' value='返回' onclick='history.go(-1)'  class='btn btn-default'>");
	mysql_close(db);
	return 0;
}
