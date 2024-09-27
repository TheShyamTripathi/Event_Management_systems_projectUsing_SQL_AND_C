#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <stdbool.h>
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
void addUsers(MYSQL *conn) {
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
void createEvent(MYSQL *conn) {
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
void registerForEvent(MYSQL *conn) {
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
//Attendance
//
//AttendanceID (Primary Key)
//UserID (Foreign Key)
//EventID (Foreign Key)
void markAttendance(MYSQL *conn) {
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
    sprintf(query, "INSERT INTO Attendance (UserID, EventID) VALUES (%d, %d)", userid, eventid);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
    } else {
        printf("Attendance inserted successfully!\n");
    }

    // Free allocated memory
    free(query);
}

// function to delete user
void removeUser(MYSQL *conn) {
    char *query;
    int userid;
    bool a = true;

    // Allocate memory for the query
    query = malloc(256 * sizeof(char));
    if (query == NULL) {
        fprintf(stderr, "Memory allocation for query failed\n");
        return;
    }

    char confirm;
    while (a) {
        printf("Enter the UserID (e.g. 1001): ");
        scanf("%d", &userid);

        // Formulate the SELECT query
        sprintf(query, "SELECT * FROM USERS WHERE UserID = %d", userid);

        // Execute the SELECT query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            free(query);
            return;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "Failed to retrieve result: %s\n", mysql_error(conn));
            free(query);
            return;
        }

        // Check if any rows were returned
        if (mysql_num_rows(result) > 0) {
            MYSQL_ROW row = mysql_fetch_row(result);
            printf("User found:\n");
            printf("UserID: %s\n", row[0]);  //  UserID is the first column
            printf("Name: %s\n", row[1]);     // Name is the second column
            printf("Email: %s\n", row[2]);    // Email is the third column
            printf("Role: %s\n", row[3]);     // Role is the fourth column
            printf("Confirm deletion (Y/N): ");
        } else {
            printf("No user found with UserID %d. Please try again.\n", userid);
            mysql_free_result(result);
            continue; // Go back to the start of the loop
        }

        // Clear the input buffer before reading a character
        while ((getchar()) != '\n'); // Clear any remaining newline characters
        scanf("%c", &confirm);
        
        if (confirm == 'Y' || confirm == 'y') {
            sprintf(query, "DELETE FROM USERS WHERE UserID = %d", userid);
            // Execute the DELETE query
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            } else {
                printf("User deleted successfully!\n");
                a = false; // Exit the loop
            }
        } else {
            printf("Retry!\n");
        }

        mysql_free_result(result); // Free the result set
    }

    // Free allocated memory
    free(query);
}
// function to delete event
void deleteEvent(MYSQL *conn) {
    char *query;
    int eventid;
    bool a = true;

    // Allocate memory for the query
    query = malloc(256 * sizeof(char));
    if (query == NULL) {
        fprintf(stderr, "Memory allocation for query failed\n");
        return;
    }

    char confirm;
    while (a) {
        printf("Enter the EventID (e.g. 101): ");
        scanf("%d", &eventid);

        // Formulate the SELECT query
        sprintf(query, "SELECT * FROM Events WHERE EventID = %d", eventid);

        // Execute the SELECT query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            free(query);
            return;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "Failed to retrieve result: %s\n", mysql_error(conn));
            free(query);
            return;
        }

        // Check if any rows were returned
        if (mysql_num_rows(result) > 0) {
            MYSQL_ROW row = mysql_fetch_row(result);
            printf("Event found:\n");
            printf("EventID: %s\n", row[0]);  //  EventID is the first column
            printf("Title: %s\n", row[1]);     // Title is the second column
            printf("Date: %s\n", row[2]);    // Date is the third column
            printf("Time: %s\n", row[3]);     // Time is the fourth column
            printf("Location: %s\n", row[4]);     // Location is the fifth column
            printf("Confirm deletion (Y/N): ");
        } else {
            printf("No Event found with EventID %d. Please try again.\n", eventid);
            mysql_free_result(result);
            continue; // Go back to the start of the loop
        }

        // Clear the input buffer before reading a character
        while ((getchar()) != '\n'); // Clear any remaining newline characters
        scanf("%c", &confirm);
        
        if (confirm == 'Y' || confirm == 'y') {
            sprintf(query, "DELETE FROM Events WHERE EventID = %d", eventid);
            // Execute the DELETE query
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            } else {
                printf("User deleted successfully!\n");
                a = false; // Exit the loop
            }
        } else {
            printf("Retry!\n");
        }

        mysql_free_result(result); // Free the result set
    }

    // Free allocated memory
    free(query);
}
// function to delete the attendance 
// function to delete the registrations


// function to search user
// function  to search event
// function to search event register
// function to search user attendance

// function to update the user
// function to udate the event
// function to update the attendance
// function to update the registrations

int main() {
    MYSQL *conn = connectDatabase();
    if (conn == NULL) {
        return 1;
    }
    
	return 0;
}
