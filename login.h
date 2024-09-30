// login.h

#ifndef LOGIN_H
#define LOGIN_H

#include <mysql.h>
#include <ctype.h>

void encrypt(const char* password, int shift, char* encrypted);
void decrypt(const char* encrypted, int shift, char* decrypted);
void getDBPassword(MYSQL* conn, const char* id, char* encryptedPW);

#endif // LOGIN_H

