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

//Users

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

//Events

//EventID (Primary Key)
//Title
//Date
//Time
//Location
// Function to insert Events
void insertEvents(MYSQL *conn) {
    char *query;
    char *Title = malloc(200 * sizeof(char));
    char *date = malloc(20 * sizeof(char));
    char *time = malloc(20 * sizeof(char)); 
    char *Location = malloc(200 * sizeof(char));

    // Check for memory allocation failures
    if (Title == NULL || date == NULL || time == NULL || Location == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Take input from user
    printf("Enter Title: ");
    fgets(Title, 200, stdin);
    Title[strcspn(Title, "\n")] = 0; // Remove newline character

    printf("Enter Date (YYYY-MM-DD): ");
    fgets(date, 20, stdin);
    date[strcspn(date, "\n")] = 0; // Remove newline character

    printf("Enter Time (HH:MM): ");
    fgets(time, 20, stdin);
    time[strcspn(time, "\n")] = 0; // Remove newline character

    printf("Enter Location: ");
    fgets(Location, 200, stdin);
    Location[strcspn(Location, "\n")] = 0; // Remove newline character

    // Allocate memory for the query
    query = malloc((256 + strlen(Title) + strlen(date) + strlen(time) + strlen(Location)) * sizeof(char));
    if (query == NULL) {
        fprintf(stderr, "Memory allocation for query failed\n");
        free(Title);
        free(date);
        free(time);
        free(Location);
        return;
    }

    // Formulate the query
    sprintf(query, "INSERT INTO Events (Title, Date, Time, Location) VALUES ('%s', '%s', '%s', '%s')", 
            Title, date, time, Location);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
    } else {
        printf("Event inserted successfully!\n");
    }
    
    // Free allocated memory
    free(query);
    free(Title);
    free(date);
    free(time);
    free(Location);
}
// Function to insert Registrations of Event
//Registrations

//RegistrationID (Primary Key)
//UserID (Foreign Key)
//EventID (Foreign Key)
void insertRegistrations(MYSQL *conn) {
    char *query;
    int eventid, userid;

    // Allocate memory for the query
    query = malloc(256 * sizeof(char));
    if (query == NULL) {
        fprintf(stderr, "Memory allocation for query failed\n");
        return;
    }
    
    // Prompt user for input
    printf("Note: EventId must be three digits (100 and above)\nUserId must be from 1000 and above\n");
    
    printf("Enter the UserID: ");
    scanf("%d", &userid); // Use scanf to read integers directly
    
    printf("Enter the EventID: ");
    scanf("%d", &eventid); // Use scanf to read integers directly

    // Formulate the query
    sprintf(query, "INSERT INTO Registrations (UserID, EventID) VALUES (%d, %d)", userid, eventid);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
    } else {
        printf("Registration inserted successfully!\n");
    }

    // Free allocated memory
    free(query);
}

// Functon to insert Attendance


int main() {
    MYSQL *conn = connectDatabase();
    if (conn == NULL) {
        return 1;
    }
    
	return 0;
}
