#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <windows.h>



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

//
//Users
//
//UserID (Primary Key)
//Name
//Email
//Role (Organizer/Participant)

// function to insert the Users

void insertUsers(MYSQL *conn) {
    char *query;
    char *email = malloc(101 * sizeof(char));
    char *name = malloc(101 * sizeof(char));
    char *role = malloc(21 * sizeof(char)); // Role Enum("Organizer", "Participant")

    if (email == NULL || name == NULL || role == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Take input from user
    printf("Enter Name: ");
    fgets(name, 101, stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character

    printf("Enter Email: ");
    fgets(email, 101, stdin);
    email[strcspn(email, "\n")] = 0; // Remove newline character

    printf("Enter Role (Organizer/Participant): ");
    fgets(role, 21, stdin);
    role[strcspn(role, "\n")] = 0; // Remove newline character

    // Allocate memory for the query
    query = malloc((256 + strlen(name) + strlen(email) + strlen(role)) * sizeof(char));
    if (query == NULL) {
        fprintf(stderr, "Memory allocation for query failed\n");
        free(email);
        free(name);
        free(role);
        return;
    }

    // Formulate the query
    sprintf(query, "INSERT INTO Users (Name, Email, Role) VALUES ('%s', '%s', '%s')", name, email, role);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
    } else {
        printf("User inserted successfully!\n");
    }

    // Free allocated memory
    free(query);
    free(email);
    free(name);
    free(role);
}
// Function to insert Events
// Function to insert Registrations of Event
// Functon to insert Attendance


int main() {
    MYSQL *conn = connectDatabase();
    if (conn == NULL) {
        return 1;
    }
    
	return 0;
}
