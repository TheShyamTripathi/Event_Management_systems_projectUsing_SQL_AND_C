#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <stdbool.h>
#include <windows.h>
#include "functions1.h"
#include "login.h"


//Events

//EventID (Primary Key)
//Title
//Date
//Time
//Location

//Registrations

//RegistrationID (Primary Key)
//UserID (Foreign Key)
//EventID (Foreign Key)


//Attendance
//
//AttendanceID (Primary Key)
//UserID (Foreign Key)
//EventID (Foreign Key)


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

//Users

//UserID (Primary Key)
//Name
//Email
//Role (Organizer/Participant)


int main() {
    MYSQL *conn = connectDatabase();
    if (conn == NULL) {
        return 1;
    }
    
	return 0;
}
