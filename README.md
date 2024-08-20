# Event Management System

## Project Overview
The **Event Management System** is a simple application built as a class project. The system allows users to create and manage events, register participants, and track attendance. The project is implemented using C programming for the back-end logic and MySQL for the database.

## Features
- **User Management**: Add and manage users with different roles (Organizers and Participants).
- **Event Creation**: Organizers can create and manage events, including event title, date, time, and location.
- **Event Registration**: Participants can register for events.
- **Attendance Tracking**: Track participant attendance for events.

## Database Schema
The system uses a MySQL database with the following tables:

1. **Users**
   - `UserID` (Primary Key)
   - `Name`
   - `Email`
   - `Role` (Organizer/Participant)

2. **Events**
   - `EventID` (Primary Key)
   - `Title`
   - `Date`
   - `Time`
   - `Location`

3. **Registrations**
   - `RegistrationID` (Primary Key)
   - `UserID` (Foreign Key)
   - `EventID` (Foreign Key)

4. **Attendance**
   - `AttendanceID` (Primary Key)
   - `UserID` (Foreign Key)
   - `EventID` (Foreign Key)

## Getting Started

### Prerequisites
- **C Compiler**: Ensure you have a C compiler (like GCC) installed.
- **MySQL Server**: Install and configure MySQL server.
- **MySQL Connector/C**: Required to connect C programs with MySQL databases.

## Setup and Installation

### MySQL Server Setup
1. **Install MySQL Server**:
   ```sh
   sudo apt-get install mysql-server
2. **Secure MySQL Installation**:
   ```sh
   sudo mysql_secure_installation
3. **Create DATABASE**:
   ```sh
   CREATE DATABASE student_management;

## MySQL Connector/C Setup
4. **Install MySQL Connector/C**:
   ```sh
   sudo apt-get install libmysqlclient-dev

### Project Setup
5. **Clone the Repository**:
   ```sh
   git clone <https://github.com/TheShyamTripathi/event_Management_systems_projectUsing_SQL_AND_C/>
6. **Navigate to Project Directory**:
   ```sh
   cd event-management-system
7. **Compile the program**:
   ```sh
   gcc -o event-management main.c -lymsqlclient
8. **Run the Program**:
   ```sh
   ./event_management

## Sample Commands

Below are some example commands used in the system:

### Add User:
```perl
add_user("John Doe", "john@example.com", "Organizer");
```
### Create Event:
```bash
   create_event("Tech Conference", "2024-09-15", "10:00 AM", "Auditorium");
```
### Register for Event:
```bash
   register_for_event(2, 5); // UserID = 2, EventID = 5
```
### Mark Attendence:
```bash
   mark_attendance(2, 5); // UserID = 2, EventID = 5
```

## Usage
### Add Users:
- Organizers and participants can be added to the system.

### Create Events:
- Organizers can create events by providing details like title, date, time, and location.

### Register for Events:
- Participants can browse available events and register for them.

### Track Attendance:
- The system allows attendance marking for participants who attend events.

  


## Contribution
We welcome contributions to enhance the functionality of this project. Feel free to fork the repository, make changes, and submit a pull request.

## Authors
- [Shyam Tripathi](https://github.com/TheShyamTripathi)
- [Harrsh Singh Tiwari](https://github.com/Harsh14055/)
- [Richa Kumari Jaishwal](https://github.com/Richajaishwal0)
- [Binay Kushwaha](https://github.com/GOLD3PHOENIXsurili)

## Future Enhancements

Some potential future improvements for the system:

- Implement a graphical user interface (GUI).
- Add notifications for event reminders.
- Implement feedback and reporting features.


## Acknowledgements
We would like to thank our professors and mentors for their guidance and support throughout this project.


## Collaboration
We welcome collaboration from anyone interested in contributing to this project. If you have any ideas, suggestions, or would like to contribute code, please feel free to fork the repository and submit a pull request.

---

Thank you for your interest in our project!

[Project Repository](https://github.com/TheShyamTripathi/Student_Management_systems_projectUsing_SQL_AND_C/)

