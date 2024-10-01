#include <stdio.h>
#include "functions1.h"  // Include the header file for function declarations
#include <mysql.h>
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
void deleteAttendance(MYSQL *conn) {
    char *query;
    int AttendanceID;
    bool a = true;

    // Allocate memory for the query
    query = malloc(256 * sizeof(char));
    if (query == NULL) {
        fprintf(stderr, "Memory allocation for query failed\n");
        return;
    }

    char confirm;
    while (a) {
        printf("Enter the AttendanceID (e.g. 1): ");
        scanf("%d", &AttendanceID);  // Corrected variable name from userid to AttendanceID

        // Formulate the SELECT query
        sprintf(query, "SELECT * FROM Attendance WHERE AttendanceID = %d", AttendanceID);

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
            printf("User Attendance found:\n");
            printf("AttendanceID: %s\n", row[0]);  // AttendanceID is the first column            
            printf("UserID: %s\n", row[1]);         // UserID is the second column
            printf("EventID: %s\n", row[2]);        // EventID is the third column (fixed index)

            printf("Confirm deletion (Y/N): ");
        } else {
            printf("No user attendance found with AttendanceID %d. Please try again.\n", AttendanceID);
            mysql_free_result(result);
            continue; // Go back to the start of the loop
        }

        // Clear the input buffer before reading a character
        while ((getchar()) != '\n'); // Clear any remaining newline characters
        scanf("%c", &confirm);
        
        if (confirm == 'Y' || confirm == 'y') {
            sprintf(query, "DELETE FROM Attendance WHERE AttendanceID = %d", AttendanceID);
            // Execute the DELETE query
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            } else {
                printf("Attendance record deleted successfully!\n");
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

// function to delete the registrations
void deleteRegistrations(MYSQL *conn) {
    char *query;
    int RegistrationID; // Changed from AttendanceID to RegistrationID
    bool a = true;

    // Allocate memory for the query
    query = malloc(256 * sizeof(char));
    if (query == NULL) {
        fprintf(stderr, "Memory allocation for query failed\n");
        return;
    }

    char confirm;
    while (a) {
        printf("Enter the RegistrationID (e.g. 10000): ");
        scanf("%d", &RegistrationID); // Corrected variable name to RegistrationID

        // Formulate the SELECT query
        sprintf(query, "SELECT * FROM Registrations WHERE RegistrationID = %d", RegistrationID);

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
            printf("Event Registration found:\n");
            printf("RegistrationID: %s\n", row[0]);  // RegistrationID is the first column            
            printf("UserID: %s\n", row[1]);            // UserID is the second column
            printf("EventID: %s\n", row[2]);           // EventID is the third column

            printf("Confirm deletion (Y/N): ");
        } else {
            printf("No Event Registrations found with RegistrationID %d. Please try again.\n", RegistrationID);
            mysql_free_result(result);
            continue; // Go back to the start of the loop
        }

        // Clear the input buffer before reading a character
        while ((getchar()) != '\n'); // Clear any remaining newline characters
        scanf("%c", &confirm);
        
        if (confirm == 'Y' || confirm == 'y') {
            sprintf(query, "DELETE FROM Registrations WHERE RegistrationID = %d", RegistrationID);
            // Execute the DELETE query
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            } else {
                printf("Registration of event deleted successfully!\n");
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

void searchUser(MYSQL *conn) {
    char *query;
    char choice;
    int userid;
    char *email = malloc(101 * sizeof(char));

    // Allocate memory for the query
    query = malloc(256 * sizeof(char));
    if (query == NULL || email == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    printf("Press 1 to display all users, 2 to search by UserID or Email, 0 to exit: ");
    scanf(" %c", &choice); // Space before %c to ignore any newline character left in input buffer

    if (choice == '1') {
        // Select all users
        sprintf(query, "SELECT * FROM Users");

        // Execute the query
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

        // Display users in table format
        printf("+--------+----------------------+--------------------------------+------------------+\n");
        printf("| UserID | Name                 | Email                          | Role             |\n");
        printf("+--------+----------------------+--------------------------------+------------------+\n");

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result)) != NULL) {
            printf("| %-6s | %-20s | %-20s | %-26s |\n", row[0], row[1], row[2], row[3]);
        }

        printf("+--------+----------------------+--------------------------------+------------------+\n");

        mysql_free_result(result); // Free the result set
    } else if (choice == '2') {
        // Search by UserID or Email
        printf("Search by (U)serID or (E)mail? Enter U or E: ");
        scanf(" %c", &choice); // Space before %c to ignore any newline character left in input buffer

        if (choice == 'U' || choice == 'u') {
            // Search by UserID
            printf("Enter the UserID: ");
            scanf("%d", &userid);

            // Formulate the query
            sprintf(query, "SELECT * FROM Users WHERE UserID = %d", userid);

            // Execute the query
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
                printf("UserID: %s\n", row[0]);  // UserID
                printf("Name: %s\n", row[1]);     // Name
                printf("Email: %s\n", row[2]);    // Email
                printf("Role: %s\n", row[3]);     // Role (Organizer/Participant)
            } else {
                printf("No user found with UserID %d.\n", userid);
            }

            mysql_free_result(result); // Free the result set
        } else if (choice == 'E' || choice == 'e') {
            // Search by Email
            printf("Enter the Email: ");
            getchar(); // To consume the newline character left by previous input
            fgets(email, 101, stdin);
            email[strcspn(email, "\n")] = 0; // Remove newline character

            // Formulate the query
            sprintf(query, "SELECT * FROM Users WHERE Email = '%s'", email);

            // Execute the query
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
                free(query);
                free(email);
                return;
            }

            MYSQL_RES *result = mysql_store_result(conn);
            if (result == NULL) {
                fprintf(stderr, "Failed to retrieve result: %s\n", mysql_error(conn));
                free(query);
                free(email);
                return;
            }

            // Check if any rows were returned
            if (mysql_num_rows(result) > 0) {
                MYSQL_ROW row = mysql_fetch_row(result);
                printf("User found:\n");
                printf("UserID: %s\n", row[0]);  // UserID
                printf("Name: %s\n", row[1]);     // Name
                printf("Email: %s\n", row[2]);    // Email
                printf("Role: %s\n", row[3]);     // Role (Organizer/Participant)
            } else {
                printf("No user found with Email '%s'.\n", email);
            }

            mysql_free_result(result); // Free the result set
        } else {
            printf("Invalid choice! Please enter U or E.\n");
        }
    } else if (choice == '0') {
        // Exit
        printf("Exiting...\n");
    } else {
        printf("Invalid option! Please enter 1, 2, or 0.\n");
    }

    // Free allocated memory
    free(query);
    free(email);
}

void findEvent(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    int choice;
    printf("Press 1 to display all events, 2 to search by EventID, 0 to exit: ");
    scanf("%d", &choice);

    char query[256];

    if (choice == 1) {
        // Query to select all events
        sprintf(query, "SELECT * FROM Events");

        // Execute the query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query Failed: %s\n", mysql_error(conn));
            return;
        }

        // Store the result of the query
        res = mysql_store_result(conn);
        if (res == NULL) {
            fprintf(stderr, "No result: %s\n", mysql_error(conn));
            return;
        }

        // Display the events in table format
        printf("+---------+--------------------+------------+--------+-------------------+\n");
        printf("| EventID | Title              | Date       | Time   | Location           |\n");
        printf("+---------+--------------------+------------+--------+-------------------+\n");

        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("| %-7s | %-18s | %-10s | %-6s | %-17s |\n", row[0], row[1], row[2], row[3], row[4]);
        }

        printf("+---------+--------------------+------------+--------+-------------------+\n");

        // Free the result set
        mysql_free_result(res);

    } else if (choice == 2) {
        // Search for a specific event by EventID
        int eventID;
        printf("Enter the EventID to search: ");
        scanf("%d", &eventID);

        // Formulate the query
        sprintf(query, "SELECT * FROM Events WHERE EventID = %d", eventID);

        // Execute the query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query Failed: %s\n", mysql_error(conn));
            return;
        }

        // Store the result of the query
        res = mysql_store_result(conn);
        if (res == NULL) {
            fprintf(stderr, "No result: %s\n", mysql_error(conn));
            return;
        }

        // Fetch and display the row
        row = mysql_fetch_row(res);
        if (row) {
            printf("Event found:\n");
            printf("EventID: %s\n", row[0]);
            printf("Title: %s\n", row[1]);
            printf("Date: %s\n", row[2]);
            printf("Time: %s\n", row[3]);
            printf("Location: %s\n", row[4]);
        } else {
            printf("Event with EventID %d not found.\n", eventID);
        }

        // Free the result set
        mysql_free_result(res);

    } else if (choice == 0) {
        // Exit
        printf("Exiting...\n");
    } else {
        printf("Invalid option! Please enter 1, 2, or 0.\n");
    }
}



// function to search event register
void findRegisterEvent(MYSQL *conn) {
    MYSQL_ROW row;
    MYSQL_RES *res;

    int choice;
    printf("Press 1 to display all registered events, 2 to search by RegistrationID, 0 to exit: ");
    scanf("%d", &choice);

    char *query;

    // Allocate memory for the query
    query = malloc(256 * sizeof(char));
    if (query == NULL) {
        fprintf(stderr, "Memory allocation for query failed\n");
        return;
    }

    if (choice == 1) {
        // Query to select all registrations
        sprintf(query, "SELECT * FROM Registrations");

        // Execute the query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query Failed: %s\n", mysql_error(conn));
            free(query);  // Free the allocated memory before returning
            return;
        }

        // Store the result of the query
        res = mysql_store_result(conn);
        if (res == NULL) {
            fprintf(stderr, "No result: %s\n", mysql_error(conn));
            free(query);  // Free the allocated memory before returning
            return;
        }

        // Display the registrations in table format
        printf("+-----------------+--------------------+-----------+\n");
        printf("| RegistrationID   | UserID             | EventID   |\n");
        printf("+-----------------+--------------------+-----------+\n");

        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("| %-15s | %-18s | %-9s |\n", row[0], row[1], row[2]);
        }

        printf("+-----------------+--------------------+-----------+\n");

        // Free the result set
        mysql_free_result(res);

    } else if (choice == 2) {
        // Search for a specific registration by RegistrationID
        int registrationID;
        printf("Enter the RegistrationID to search: ");
        scanf("%d", &registrationID);

        // Formulate the query
        sprintf(query, "SELECT * FROM Registrations WHERE RegistrationID = %d", registrationID);

        // Execute the query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query Failed: %s\n", mysql_error(conn));
            free(query);  // Free the allocated memory before returning
            return;
        }

        // Store the result of the query
        res = mysql_store_result(conn);
        if (res == NULL) {
            fprintf(stderr, "No result: %s\n", mysql_error(conn));
            free(query);  // Free the allocated memory before returning
            return;
        }

        // Fetch and display the row
        row = mysql_fetch_row(res);
        if (row) {
            printf("Registered Event found:\n");
            printf("RegistrationID: %s\n", row[0]);
            printf("UserID: %s\n", row[1]);
            printf("EventID: %s\n", row[2]);
        } else {
            printf("Registered Event with RegistrationID %d not found.\n", registrationID);
        }

        // Free the result set
        mysql_free_result(res);

    } else if (choice == 0) {
        printf("Exiting...\n");
    } else {
        printf("Invalid option! Please enter 1, 2, or 0.\n");
    }

    // Free allocated memory
    free(query);
}

// function to search user attendance
void findAttendance(MYSQL *conn) {
    MYSQL_ROW row;
    MYSQL_RES *res;

    int choice;
    printf("Press 1 to display all attendance, 2 to search by AttendanceID, 0 to exit: ");
    scanf("%d", &choice);

    char *query;

    // Allocate memory for the query
    query = malloc(256 * sizeof(char));
    if (query == NULL) {
        fprintf(stderr, "Memory allocation for query failed\n");
        return;
    }

    if (choice == 1) {
        // Query to select all attendance records
        sprintf(query, "SELECT * FROM Attendance");

        // Execute the query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query Failed: %s\n", mysql_error(conn));
            free(query);  // Free the allocated memory before returning
            return;
        }

        // Store the result of the query
        res = mysql_store_result(conn);
        if (res == NULL) {
            fprintf(stderr, "No result: %s\n", mysql_error(conn));
            free(query);  // Free the allocated memory before returning
            return;
        }

        // Display the attendance in table format
        printf("+-----------------+--------------------+-----------+\n");
        printf("| AttendanceID    | UserID             | EventID   |\n");
        printf("+-----------------+--------------------+-----------+\n");

        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("| %-15s | %-18s | %-9s |\n", row[0], row[1], row[2]);
        }

        printf("+-----------------+--------------------+-----------+\n");

        // Free the result set
        mysql_free_result(res);

    } else if (choice == 2) {
        // Search for a specific attendance record by AttendanceID
        int attendanceID;
        printf("Enter the AttendanceID to search: ");
        scanf("%d", &attendanceID);

        // Formulate the query
        sprintf(query, "SELECT * FROM Attendance WHERE AttendanceID = %d", attendanceID);

        // Execute the query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query Failed: %s\n", mysql_error(conn));
            free(query);  // Free the allocated memory before returning
            return;
        }

        // Store the result of the query
        res = mysql_store_result(conn);
        if (res == NULL) {
            fprintf(stderr, "No result: %s\n", mysql_error(conn));
            free(query);  // Free the allocated memory before returning
            return;
        }

        // Fetch and display the row
        row = mysql_fetch_row(res);
        if (row) {
            printf("Attendance Record found:\n");
            printf("AttendanceID: %s\n", row[0]);
            printf("UserID: %s\n", row[1]);
            printf("EventID: %s\n", row[2]);
        } else {
            printf("Attendance record with AttendanceID %d not found.\n", attendanceID);
        }

        // Free the result set
        mysql_free_result(res);

    } else if (choice == 0) {
        printf("Exiting...\n");
    } else {
        printf("Invalid option! Please enter 1, 2, or 0.\n");
    }

    // Free allocated memory
    free(query);
}

// Function to check if a user exists by User ID
int userExists(MYSQL *conn, int user_id) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM Users WHERE UserID = %d", user_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return 0; // Assuming user does not exist if the query fails
    }

	MYSQL_RES *res	= mysql_store_result(conn);
    if (res) {
        MYSQL_ROW row = mysql_fetch_row(res);
        int count = atoi(row[0]);
        mysql_free_result(res);
        return count > 0; // Return true if user exists
    }

    return 0; // User does not exist
}

// Function to update user details
void updateUser(MYSQL *conn) {
    char *query = malloc(512 * sizeof(char));
    int user_id;
    char *new_name = (char *)malloc(100 * sizeof(char)); // Dynamic allocation for Name
    char *new_email = (char *)malloc(100 * sizeof(char)); // Dynamic allocation for Email
    char *new_role = (char *)malloc(20 * sizeof(char)); // Dynamic allocation for Role
    int choice;

    // Ask the user for User ID
    printf("Enter the User ID to update: ");
    scanf("%d", &user_id);

    // Check if the user exists
    if (!userExists(conn, user_id)) {
        printf("User with ID %d does not exist.\n", user_id);
        free(new_name);
        free(new_email);
        free(new_role);
        return;
    }

    // Retrieve and display current user details
    snprintf(query, 512, "SELECT Name, Email, Role FROM Users WHERE UserID = %d", user_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        free(new_name);
        free(new_email);
        free(new_role);
        free(query);
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Error fetching result: %s\n", mysql_error(conn));
        free(new_name);
        free(new_email);
        free(new_role);
        free(query);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row) {
        printf("\nCurrent User Details:\n");
        printf("Name: %s\n", row[1]);
        printf("Email: %s\n", row[2]);
        printf("Role: %s\n", row[3]);
    }
    mysql_free_result(result);

    // Ask for confirmation to proceed
    printf("Are you sure you want to update User ID %d? (1 for Yes, 0 for No): ", user_id);
    int confirm;
    scanf("%d", &confirm);
    if (!confirm) {
        printf("Update cancelled.\n");
        free(new_name);
        free(new_email);
        free(new_role);
        free(query);
        return;
    }

    do {
        // Display menu options
        printf("\nWhat would you like to update?\n");
        printf("1. Update Name\n");
        printf("2. Update Email\n");
        printf("3. Update Role\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Exit condition
        if (choice == 4) {
            printf("Exiting...\n");
            break;
        }

        // Update based on user's choice
        switch (choice) {
            case 1:
                // Update Name
                printf("Enter new Name: ");
                getchar(); // To consume newline left by scanf
                fgets(new_name, 100, stdin);
                new_name[strcspn(new_name, "\n")] = 0;  // Remove newline

                // Prepare SQL query to update Name
                snprintf(query, 512, "UPDATE Users SET Name = '%s' WHERE UserID = %d", new_name, user_id);
                break;

            case 2:
                // Update Email
                printf("Enter new Email: ");
                getchar(); // To consume newline
                fgets(new_email, 100, stdin);
                new_email[strcspn(new_email, "\n")] = 0;  // Remove newline

                // Prepare SQL query to update Email
                snprintf(query, 512, "UPDATE Users SET Email = '%s' WHERE UserID = %d", new_email, user_id);
                break;

            case 3:
                // Update Role
                printf("Enter new Role (Organizer/Participant): ");
                getchar(); // To consume newline
                fgets(new_role, 20, stdin);
                new_role[strcspn(new_role, "\n")] = 0;  // Remove newline

                // Prepare SQL query to update Role
                snprintf(query, 512, "UPDATE Users SET Role = '%s' WHERE UserID = %d", new_role, user_id);
                break;

            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
                continue;
        }

        // Execute the SQL query if a valid update choice was made
        if (choice >= 1 && choice <= 3) {
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            } else {
                printf("User updated successfully!\n");
            }
        }

    } while (1); // Continue the loop until the user chooses to exit

    // Free allocated memory
    free(new_name);
    free(new_email);
    free(new_role);
    free(query);
}

//function to check if the event exists
int checkEventExists(MYSQL *conn, int event_id) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM Events WHERE EventID = %d", event_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int count = atoi(row[0]);
    mysql_free_result(res);
    return count > 0;
}
//function to update event
void updateEvent(MYSQL *conn) {
    char *query = malloc(512 * sizeof(char));
    int event_id;
    char *new_title = malloc(100 * sizeof(char));
    char *new_date = malloc(11 * sizeof(char));  // format: YYYY-MM-DD
    char *new_time = malloc(9 * sizeof(char));   // format: HH:MM:SS
    char *new_location = malloc(100 * sizeof(char));
    int choice;

    do {
        printf("\nWhat would you like to do?\n");
        printf("1. Update Title\n");
        printf("2. Update Date\n");
        printf("3. Update Time\n");
        printf("4. Update Location\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting...\n");
            break;
        }

        printf("Enter the Event ID to update: ");
        scanf("%d", &event_id);

        if (!checkEventExists(conn, event_id)) {
            printf("Event ID %d does not exist.\n", event_id);
            continue;
        }

        // Retrieve and display the current event details
        snprintf(query, 512, "SELECT Title, Date, Time, Location FROM Events WHERE EventID = %d", event_id);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            continue;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "Error fetching result: %s\n", mysql_error(conn));
            continue;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        if (row) {
            printf("\nCurrent Event Details:\n");
            printf("Title: %s\n", row[1]);
            printf("Date: %s\n", row[2]);
            printf("Time: %s\n", row[3]);
            printf("Location: %s\n", row[4]);
        }
        mysql_free_result(result);

        // Ask for confirmation to proceed
        printf("Are you sure you want to update Event ID %d? (1 for Yes, 0 for No): ", event_id);
        int confirm;
        scanf("%d", &confirm);
        if (!confirm) {
            printf("Update cancelled.\n");
            continue;
        }

        // Update the event based on user's choice
        switch (choice) {
            case 1:
                printf("Enter new Title: ");
                getchar(); // To consume newline left by scanf
                fgets(new_title, 100, stdin);
                new_title[strcspn(new_title, "\n")] = 0;

                snprintf(query, 512, "UPDATE Events SET Title = '%s' WHERE EventID = %d", new_title, event_id);
                break;

            case 2:
                printf("Enter new Date (YYYY-MM-DD): ");
                scanf("%10s", new_date);

                snprintf(query, 512, "UPDATE Events SET Date = '%s' WHERE EventID = %d", new_date, event_id);
                break;

            case 3:
                printf("Enter new Time (HH:MM:SS): ");
                scanf("%8s", new_time);

                snprintf(query, 512, "UPDATE Events SET Time = '%s' WHERE EventID = %d", new_time, event_id);
                break;

            case 4:
                printf("Enter new Location: ");
                getchar(); // To consume newline
                fgets(new_location, 100, stdin);
                new_location[strcspn(new_location, "\n")] = 0;

                snprintf(query, 512, "UPDATE Events SET Location = '%s' WHERE EventID = %d", new_location, event_id);
                break;

            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
                continue;
        }

        // Execute the update query
        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        } else {
            printf("Event updated successfully!\n");
        }

    } while (1);

    free(new_title);
    free(new_date);
    free(new_time);
    free(new_location);
    free(query);
}

//function to check attendanceid exits 
int checkAttendanceExists(MYSQL *conn, int attendance_id) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM Attendance WHERE AttendanceID = %d", attendance_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int count = atoi(row[0]);
    mysql_free_result(res);
    return count > 0;
}
//function to update attendance
// Function to update attendance details
void updateAttendance(MYSQL *conn) {
    char *query = malloc(512 * sizeof(char));
    int attendance_id;
    int new_user_id;
    int new_event_id;
    int choice;

    // Ask the user for Attendance ID
    printf("Enter the Attendance ID to update: ");
    scanf("%d", &attendance_id);

    // Check if the attendance record exists
    if (!checkAttendanceExists(conn, attendance_id)) {
        printf("Attendance ID %d does not exist.\n", attendance_id);
        free(query);
        return;
    }

    // Retrieve and display current attendance details
    snprintf(query, 512, "SELECT UserID, EventID FROM Attendance WHERE AttendanceID = %d", attendance_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        free(query);
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Error fetching result: %s\n", mysql_error(conn));
        free(query);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row) {
        printf("\nCurrent Attendance Details:\n");
        printf("UserID: %s\n", row[1]);
        printf("EventID: %s\n", row[2]);
    }
    mysql_free_result(result);

    // Ask for confirmation to proceed
    printf("Are you sure you want to update Attendance ID %d? (1 for Yes, 0 for No): ", attendance_id);
    int confirm;
    scanf("%d", &confirm);
    if (!confirm) {
        printf("Update cancelled.\n");
        free(query);
        return;
    }

    do {
        // Display menu options
        printf("\nWhat would you like to do?\n");
        printf("1. Update UserID\n");
        printf("2. Update EventID\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Exit condition
        if (choice == 3) {
            printf("Exiting...\n");
            break;
        }

        // Update based on user's choice
        switch (choice) {
            case 1:
                printf("Enter new UserID: ");
                scanf("%d", &new_user_id);
                snprintf(query, 512, "UPDATE Attendance SET UserID = %d WHERE AttendanceID = %d", new_user_id, attendance_id);
                break;

            case 2:
                printf("Enter new EventID: ");
                scanf("%d", &new_event_id);
                snprintf(query, 512, "UPDATE Attendance SET EventID = %d WHERE AttendanceID = %d", new_event_id, attendance_id);
                break;

            default:
                printf("Invalid choice! Please enter a number between 1 and 3.\n");
                continue;
        }

        // Execute the SQL query if a valid update choice was made
        if (choice == 1 || choice == 2) {
            if (mysql_query(conn, query)) {
                fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            } else {
                printf("Attendance updated successfully!\n");
            }
        }

    } while (1);

    // Free allocated memory
    free(query);
}

//function to check if registration id exists
int checkRegistrationExists(MYSQL *conn, int registration_id) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM Registrations WHERE RegistrationID = %d", registration_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    int count = atoi(row[0]);
    mysql_free_result(res);
    return count > 0;
}
// Function to update Registration table
void updateRegistration(MYSQL *conn) {
    char *query = malloc(256 * sizeof(char));
    int registration_id;
    int new_user_id;
    int new_event_id;
    int choice;

    // Ask the user for Registration ID
    printf("Enter the Registration ID to update: ");
    scanf("%d", &registration_id);

    // Check if the registration record exists
    if (!checkRegistrationExists(conn, registration_id)) {
        printf("Registration ID %d does not exist.\n", registration_id);
        free(query);
        return;
    }

    // Retrieve and display current registration details
    snprintf(query, 256, "SELECT UserID, EventID FROM Registrations WHERE RegistrationID = %d", registration_id);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        free(query);
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Error fetching result: %s\n", mysql_error(conn));
        free(query);
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row) {
        printf("\nCurrent Registration Details:\n");
        printf("UserID: %s\n", row[1]);
        printf("EventID: %s\n", row[2]);
    } else {
        printf("No details found for Registration ID %d.\n", registration_id);
    }
    mysql_free_result(result);

    // Ask for confirmation to proceed
    printf("Are you sure you want to update Registration ID %d? (1 for Yes, 0 for No): ", registration_id);
    int confirm;
    scanf("%d", &confirm);
    if (!confirm) {
        printf("Update cancelled.\n");
        free(query);
        return;
    }

    // Display menu for updates
    printf("What would you like to update?\n");
    printf("1. Update UserID\n");
    printf("2. Update EventID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new UserID: ");
            scanf("%d", &new_user_id);
            snprintf(query, 256, "UPDATE Registrations SET UserID = %d WHERE RegistrationID = %d", new_user_id, registration_id);
            break;

        case 2:
            printf("Enter new EventID: ");
            scanf("%d", &new_event_id);
            snprintf(query, 256, "UPDATE Registrations SET EventID = %d WHERE RegistrationID = %d", new_event_id, registration_id);
            break;

        default:
            printf("Invalid choice!\n");
            free(query);
            return;
    }

    // Execute the SQL query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
    } else {
        printf("Registration updated successfully!\n");
    }

    // Free allocated memory
    free(query);
}



void joinShow(MYSQL *conn) {
    // Allocate memory for the query
    char *query;
    query = (char *)malloc(512 * sizeof(char));

    // Define the SQL query
    snprintf(query, 512,
        "SELECT u.UserID, u.Name, u.Email, u.Role, "
        "e.EventID, e.Title, e.Date, e.Time, e.Location, "
        "r.RegistrationID, "
        "a.AttendanceID "
        "FROM Users u "
        "JOIN Registrations r ON u.UserID = r.UserID "
        "JOIN Events e ON r.EventID = e.EventID "
        "JOIN Attendance a ON u.UserID = a.UserID AND e.EventID = a.EventID "
        "ORDER BY e.Date ASC LIMIT 5;");

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(query);
        return;
    }

    // Store the result
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Failed to retrieve result: %s\n", mysql_error(conn));
        free(query);
        return;
    }

    // Display the joined data in table format
    printf("+--------+----------------------+--------------------------------+------------------+---------+-------------------+------------+--------+------------+-----------------+------------+--------------+\n");
    printf("| UserID | Name                 | Email                          | Role             | EventID | Title             | Date       | Time   | Location   | RegistrationID   | Attendance | AttendanceID |\n");
    printf("+--------+----------------------+--------------------------------+------------------+---------+-------------------+------------+--------+------------+-----------------+------------+--------------+\n");

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result)) != NULL) {
        printf("| %-6s | %-20s | %-30s | %-16s | %-7s | %-17s | %-10s | %-6s | %-10s | %-15s | %-10s | %-12s |\n", 
            row[0], row[1], row[2], row[3], row[4], row[5], row[6], row[7], row[8], row[9], row[10], row[11]);
    }

    printf("+--------+----------------------+--------------------------------+------------------+---------+-------------------+------------+--------+------------+-----------------+------------+--------------+\n");

    // Free the result and query
    mysql_free_result(result);
    free(query);
}


