#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <stdbool.h>
#include <windows.h>
#include "login.h"
#include "functions1.h"

// Function to connect to the database
MYSQL* connectDatabase() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("mysql_init() failed\n");
        return NULL;
    }
    
    // Replace with your own MySQL credentials
    if (mysql_real_connect(conn, "localhost", "root", "Shyamsql@123", "projectd", 0, NULL, 0) == NULL) {
        printf("Connection failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

int main() {
    MYSQL *conn = connectDatabase();
    if (conn == NULL) {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    } else {
        printf("Logged In Database!\n");
    }

    int shift = 7;
    int exitFlag = 0;
    bool userAuthenticated = false;  // Flag to track if user is successfully signed in

    while (!exitFlag && !userAuthenticated) {
        system("cls");
        printf("1. Signup.\n");
        printf("2. SignIn.\n");
        printf("0. Exit.\n");
        printf("Enter Your Choice: ");
        int val;
        scanf("%d", &val);

        if (val == 1) {
            system("cls");
            char id[50], pw[50], encryptedPW[50];
            printf("Enter ID for Signup: ");
            scanf("%s", id);
            printf("Enter A Strong Password: ");
            scanf("%s", pw);

            // Encrypt the password
            encrypt(pw, shift, encryptedPW);

            // Insert the encrypted password into the database
            char signupQuery[256];
            sprintf(signupQuery, "INSERT INTO password (Id, PW) VALUES ('%s', '%s')", id, encryptedPW);
            if (mysql_query(conn, signupQuery)) {
                printf("Error: %s\n", mysql_error(conn));
            } else {
                printf("Signup Successfully\n");
            }
            Sleep(3000);

        } else if (val == 2) {
            system("cls");
            char id[50], pw[50], encryptedDBPassword[50], decryptedPW[50];
            printf("Enter ID: ");
            scanf("%s", id);
            printf("Enter Your Password: ");
            scanf("%s", pw);

            // Retrieve the encrypted password from the database
            getDBPassword(conn, id, encryptedDBPassword);

            if (strlen(encryptedDBPassword) > 0) {
                // Decrypt the password from the database
                decrypt(encryptedDBPassword, shift, decryptedPW);

                // Check if the entered password matches the decrypted password
                if (strcmp(decryptedPW, pw) == 0) {
                    printf("Login Successful! Welcome!\n");
                    userAuthenticated = true;  // User successfully signed in
                } else {
                    printf("Incorrect Password. Try Again!\n");
                }
            } else {
                printf("User ID not found. Try Again!\n");
            }
            Sleep(5000);

        } else if (val == 0) {
            exitFlag = 1;
            printf("Bye!\n");

        } else {
            printf("Invalid Input\n");
        }
    }

    // If user is authenticated, start further process
    if (userAuthenticated) {
        printf("\nStarting further process...\n");
		joinShow(conn);
	
    }

    // Close the database connection
    mysql_close(conn);
    return 0;
}

