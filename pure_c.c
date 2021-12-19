#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        conn = mysql_init(NULL);
        printf("MySQL client version : %d \n",mysql_get_client_version());
        if(!mysql_real_connect(conn,"127.0.0.1","root","密码","grade_db",0,NULL,0)){
                puts("Error connecting");
                printf("%s\n",mysql_error(conn));
         }
          else{
                puts("Success connecting");
            }
        /* send SQL query */
        if (mysql_query(conn, "SELECT stu_id,stu_num, stu_name,(SELECT score FROM grade WHERE stu_id = stu.stu_id AND subject_id = 0 ) AS ch,(SELECT score FROM grade WHERE stu_id = stu.stu_id AND subject_id = 1 ) AS math,(SELECT score FROM grade WHERE stu_id = stu.stu_id AND subject_id = 2 ) AS eng FROM stu;")) {
fprintf(stderr, "%s\n", mysql_error(conn));
            exit(0);
        }
        res = mysql_use_result(conn);
        printf("The Result is\n");
        while ((row = mysql_fetch_row(res)) != NULL){
        	printf("(%s) 学号: %10s 姓名： %12s \t||\t 语文: %5s\t数学: %5s\t英语:%5s \n", row[0],row[1],row[2],row[3],row[4],row[5]);
        }

        /* close connection */
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
}