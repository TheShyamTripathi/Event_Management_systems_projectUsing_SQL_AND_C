// login.c

#include "login.h"
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include <mysqld_error.h>


// Function to encrypt a single character with a shift
char encryptChar(char ch, int shift) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return (ch - base + shift + 26) % 26 + base;
    }
    if (isdigit(ch)) {
        return (ch - '0' + shift + 10) % 10 + '0';
    }
    return ch;
}

// Function to encrypt the entire password string
void encrypt(const char* password, int shift, char* encrypted) {
    int len = strlen(password);
    int i;
    for ( i = 0; i < len; i++) {
        encrypted[i] = encryptChar(password[i], shift);
    }
    encrypted[len] = '\0';
}

// Function to decrypt a single character with a shift
char decryptChar(char ch, int shift) {
    if (isalpha(ch)) {
        char base = isupper(ch) ? 'A' : 'a';
        return (ch - base - shift + 26) % 26 + base;
    }
    if (isdigit(ch)) {
        return (ch - '0' - shift + 10) % 10 + '0';
    }
    return ch;
}

// Function to decrypt the entire encrypted password string
void decrypt(const char* encrypted, int shift, char* decrypted) {
    int len = strlen(encrypted);
    int i;
    for ( i = 0; i < len; i++) {
        decrypted[i] = decryptChar(encrypted[i], shift);
    }
    decrypted[len] = '\0';
}

// Function to retrieve the encrypted password from the database
void getDBPassword(MYSQL* conn, const char* id, char* encryptedPW) {
    char query[256];
    sprintf(query, "SELECT PW FROM password WHERE Id = '%s'", id);
    if (mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
    } else {
        MYSQL_RES* res = mysql_store_result(conn);
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) {
                strcpy(encryptedPW, row[0]);
            }
        }
    }
}

