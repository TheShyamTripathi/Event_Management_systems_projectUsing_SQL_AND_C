// login.h

#ifndef LOGIN_H
#define LOGIN_H

#include <mysql.h>
#include <ctype.h>

// Constants for MySQL connection
extern const char* HOST;
extern const char* USER;
extern const char* PW;
extern const char* DB;

// Struct to handle user login
typedef struct {
    char userId[50];  // Stores the user ID
    char userPW[50];  // Stores the user password
} Login;

// Function declarations
void setId(Login* login, const char* id);
void setPW(Login* login, const char* pw);
const char* getId(const Login* login);
const char* getPW(const Login* login);
void encrypt(const char* password, int shift, char* encrypted);
void decrypt(const char* encrypted, int shift, char* decrypted);
void getDBPassword(MYSQL* conn, const char* id, char* encryptedPW);

#endif // LOGIN_H

