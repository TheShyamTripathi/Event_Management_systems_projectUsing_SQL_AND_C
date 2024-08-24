#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>

using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "your_password";
const char* DB = "my_cpp";

class University {
    private:
        int Id;
        string Name, Subject;
        float CGPA;
    public:
        University() : Id(0), Name(""), Subject(""), CGPA(0.0) {}

        void setId(int id) { Id = id; }
        void setName(string name) { Name = name; }
        void setSubject(string subject) { Subject = subject; }
        void setGrade(float cgpa) { CGPA = cgpa; }

        int getId() { return Id; }
        string getName() { return Name; }
        string getSubject() { return Subject; }
        float getGrade() { return CGPA; }
};

void insert(MYSQL* conn, University u) {
    int id;
    string name, subject;
    float cgpa;
    
    cout << "Enter Id: ";
    cin >> id;
    u.setId(id);
    
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    u.setName(name);
    
    cout << "Enter Subject: ";
    getline(cin, subject);
    u.setSubject(subject);
    
    cout << "Enter CGPA: ";
    cin >> cgpa;
    u.setGrade(cgpa);
    
    stringstream ss, as;
    ss << u.getId();
    as << u.getGrade();
    
    string ins = "INSERT INTO student (Id, Name, Subject, CGPA) VALUES('" + ss.str() + "','" + u.getName() + "','" + u.getSubject() + "','" + as.str() + "')";
    
    if (mysql_query(conn, ins.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Data Inserted Successfully." << endl;
    }
    
    Sleep(4000);
}

void showRecord(MYSQL* conn) {
    string show = "SELECT * FROM student";
    
    if (mysql_query(conn, show.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        MYSQL_RES* res = mysql_store_result(conn);
        if (res) {
            int num = mysql_num_fields(res);
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))) {
                for (int i = 0; i < num; i++) {
                    cout << " " << row[i];
                }
                cout << endl;
            }
            mysql_free_result(res);  // Free the result set
        }
    }
    Sleep(7000);
}

void search(MYSQL* conn) {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;
    
    stringstream ss;
    ss << id;
    string show = "SELECT * FROM student WHERE Id = '" + ss.str() + "'";
    
    if (mysql_query(conn, show.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        MYSQL_RES* res = mysql_store_result(conn);
        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row) {
                int num = mysql_num_fields(res);
                for (int i = 0; i < num; i++) {
                    cout << " " << row[i];
                }
            } else {
                cout << "No record found!" << endl;
            }
            mysql_free_result(res);  // Free the result set
        }
    }
    Sleep(5000);
}

void update(MYSQL* conn, University u) {
    int id;
    cout << "Enter Id: ";
    cin >> id;
    
    stringstream ss;
    ss << id;
    string subject;
    cout << "Enter New Subject: ";
    cin >> subject;
    u.setSubject(subject);
    
    string upd = "UPDATE student SET Subject = '" + u.getSubject() + "' WHERE Id = '" + ss.str() + "'";
    if (mysql_query(conn, upd.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Data Updated Successfully" << endl;
    }
    Sleep(3000);
}

void deleteS(MYSQL* conn) {
    int id;
    cout << "Enter student ID: ";
    cin >> id;
    
    stringstream ss;
    ss << id;
    
    string del = "DELETE FROM student WHERE Id = '" + ss.str() + "'";
    if (mysql_query(conn, del.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    } else {
        cout << "Data Deleted Successfully" << endl;
    }
    Sleep(3000);
}

int main(int argc, char** argv) {
    University u;
    MYSQL* conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl;
        return -1;
    } else {
        cout << "Logged in!" << endl;
    }
    Sleep(3000);
    
    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << "Welcome to University Management System" << endl;
        cout << "******************************************" << endl;
        cout << "1. Insert Student Data" << endl;
        cout << "2. Show Student Data" << endl;
        cout << "3. Search Student Data" << endl;
        cout << "4. Update Student Data" << endl;
        cout << "5. Delete Student Data" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> val;
        
        switch (val) {
            case 1:
                insert(conn, u);
                break;
            case 2:
                showRecord(conn);
                break;
            case 3:
                search(conn);
                break;
            case 4:
                update(conn, u);
                break;
            case 5:
                deleteS(conn);
                break;
            case 0:
                exit = true;
                cout << "Good Day!" << endl;
                Sleep(3000);
                break;
            default:
                cout << "Invalid Input" << endl;
                Sleep(2000);
        }
    }
    
    mysql_close(conn);  // Close MySQL connection before exiting
    return 0;
}

