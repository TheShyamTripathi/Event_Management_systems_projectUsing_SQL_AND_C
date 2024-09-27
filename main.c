#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <windows.h>

// Function to connect to the database
MYSQL* connectDatabase() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("mysql_init() failed\n");
        return NULL;
    }

    // Replace "localhost", "user", "password", "traffic_db" with your own credentials
    if (mysql_real_connect(conn, "localhost", "root", "Shyamsql@123", "projectd", 0, NULL, 0) == NULL) {
        printf("Connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

int main() {
	return 0;
}
