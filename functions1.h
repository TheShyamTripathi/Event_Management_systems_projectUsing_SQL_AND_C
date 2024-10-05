#ifndef FUNCTIONS1_H   // Header guard start
#define FUNCTIONS1_H   // Define the header guard

#include <mysql.h>
#include <ctype.h>

// 
void clear_stdin();
void encrypt(const char* password, int shift, char* encrypted);
void decrypt(const char* encrypted, int shift, char* decrypted);
void getDBPassword(MYSQL* conn, const char* id, char* encryptedPW);
// Function to insert the Users
void addUsers(MYSQL *conn);

// Function to insert Events
void createEvent(MYSQL *conn);

// Function to insert Registrations of Event
void registerForEvent(MYSQL *conn);

// Function to insert Attendance
void markAttendance(MYSQL *conn);

// Function to delete user
void removeUser(MYSQL *conn);

// Function to delete event
void deleteEvent(MYSQL *conn);

// Function to delete the attendance 
void deleteAttendance(MYSQL *conn);

// Function to delete the registrations
void deleteRegistrations(MYSQL *conn);

// Function to search for a user
void searchUser(MYSQL *conn);

// Function to find an event
void findEvent(MYSQL *conn);

// Function to search for event registration
void findRegisterEvent(MYSQL *conn);

// Function to search user attendance
void findAttendance(MYSQL *conn);

// Function to check if a user exists by User ID
int userExists(MYSQL *conn, int user_id);

// Function to update user details
void updateUser(MYSQL *conn);

// Function to check if the event exists
int checkEventExists(MYSQL *conn, int event_id);

// Function to update event
void updateEvent(MYSQL *conn);

// Function to check if attendance ID exists 
int checkAttendanceExists(MYSQL *conn, int attendance_id);

// Function to update attendance details
void updateAttendance(MYSQL *conn);

// Function to check if registration ID exists
int checkRegistrationExists(MYSQL *conn, int registration_id);

// Function to update Registration table
void updateRegistration(MYSQL *conn);

// Function to join the table 
void joinShow(MYSQL *conn);

#endif  // Header guard end

