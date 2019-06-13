#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>
using namespace std;

struct student {
    string firstname, lastname;
    int age, number;
    float grade;
};
struct user {
    string login, password;
};
vector<student> readFromFile(string fileName);
bool compareByFirstName(student a, student b);
bool compareByLastName(student a, student b);
bool compareBySid(student a, student b);
bool compareByAge(student a, student b);
bool compareByGpa(student a, student b);
void displayStudents(vector<student> students);
void writeToFile(string fileName, vector<student> students, string sortingMethod);
bool isComment(string line);
void readLine(ifstream& fin, string& str);
void addStudent(vector<student> &students);
void updateStudent(vector<student> &students);
void deleteStudent(vector<student> &students);
vector<user> loadUsers();
string floatToString(float num);
int generateSid();
bool authenticate();
void removeNewLine(string &input);
bool ifSidUsed(vector<student> students, string input);
bool validateInt(string input);
bool contains_non_alpha(string str);

int main() {
    bool authenticated = authenticate();
    if(!authenticated) {
        cout << "Sorry the limit of 3 attempts has been reached" << endl;
        cout << "Try again later" << endl;
        return 0;
    }
    while(true) {
        string fileName;
        cout << "Welcome to the student info organizer!" << endl;
        cout << "Enter the file name" << endl;
        cin >> fileName;
        vector<student> students = readFromFile(fileName);
        int choice = 0, oMethod = 0;
        cout << "You have following options: " << endl;
        cout << "1. Organize the file: " << endl;
        cout << "2. Add students to the file: " << endl;
        cout << "3. View the students in the file: " << endl;
        cout << "4. Update student information: " << endl;
        cout << "5. Delete student: " << endl;
        cout << "0. Exit \n";
        cin >> choice;
        while (!cin || choice > 5 || choice < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Sorry, the value must be a positive number in range 0 - 5!" << endl;
            cout << "You have following options or press 0 if you want to exit: " << endl;
            cout << "1. Organize the file: " << endl;
            cout << "2. Add students to the file: " << endl;
            cout << "3. View the students in the file: " << endl;
            cout << "4. Update student information: " << endl;
            cout << "5. Delete student: " << endl;
            cout << "0. Exit \n";
            cin >> choice;
        }
        switch(choice) {
            case 0 :
                cout << "Goodbye" << endl;
                return 0;
            case 1 : {
                cout << "Enter the organisation method: " << endl;
                cout << "Options of available organisation methods:" << endl;
                cout << "1. Organize the file based on alphabetical order by first name \n";
                cout << "2. Organise the file based on alphabetical order by last name \n";
                cout << "3. Organise the file based on SID\n";
                cout << "4. Organise the file based on GPA\n";
                cout << "5. Organise the file based on age\n";
                cout << "0. Exit \n";
                cin >> oMethod;
                while (!cin) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Sorry, the value must be numeric!" << endl;
                    cout << "Enter the organisation method: " << endl;
                    cin >> oMethod;
                }
                while(oMethod > 5 || oMethod < 0) {
                    cout << "Please choose a number between 1 and 5!" << endl;
                    cout << "Enter the organisation method: " << endl;
                    cout << "Options of available organisation methods:" << endl;
                    cout << "1. Organize the file based on alphabetical order by first name \n";
                    cout << "2. Organise the file based on alphabetical order by last name \n";
                    cout << "3. Organise the file based on SID\n";
                    cout << "4. Organise the file based on GPA\n";
                    cout << "5. Organise the file based on age\n";
                    cout << "0. Exit \n";
                    cin >> oMethod;
                }
                string sortingMethod;
                switch (oMethod) {
                    case 0:
                        cout << "Quitting..." << endl;
                        return 0;
                    case 1:
                        sortingMethod = "first name in alphabetical order";
                        sort(students.begin(),students.end(), compareByFirstName);
                        break;
                    case 2:
                        sortingMethod = "last name in alphabetical order";
                        sort(students.begin(),students.end(), compareByLastName);
                        break;
                    case 3:
                        sortingMethod = "SID number in ascending order";
                        sort(students.begin(),students.end(), compareBySid);
                        break;
                    case 4:
                        sortingMethod = "student gpa in descending order";
                        sort(students.begin(),students.end(), compareByGpa);
                        break;
                    case 5:
                        sortingMethod = "students' age in ascending order";
                        sort(students.begin(),students.end(), compareByAge);
                        break;
                }
                writeToFile("output.txt", students, sortingMethod);
                cout << "Success! ";
                cout << "Your data has been organized and stored in the output.txt file" << endl;
                break;
            }

            case 2:
                addStudent(students);
                writeToFile(fileName, students, "");
                break;
            case 3:
                displayStudents(students);
                break;
            case 4:
                updateStudent(students);
                writeToFile(fileName, students, "");
                break;
            case 5:
                deleteStudent(students);
                writeToFile(fileName, students, "");
                break;

        }
    }
}
bool isComment(string line) {
    return line.rfind("#",0) == 0;
}
void readLine(ifstream& fin, string& str) {
    string line;
    getline(fin, line);
    while(isComment(line)) {
        getline(fin,line);
    }
    str = line;
}
vector<student> readFromFile(string fileName) {
    ifstream fin(fileName.c_str());
    while (fin.fail()) {
        cout << "Program Error: Unable to open the file" << endl;
        cout << "Enter the file name" << endl;
        cin >> fileName;
        fin.open(fileName.c_str());
    }
    vector<student> students;
    while(!fin.eof()) {
        student record;
        readLine(fin, record.firstname);
        readLine(fin, record.lastname);
        string number;
        readLine(fin, number);
        record.number = stoi(number);
        string age;
        readLine(fin, age);
        record.age = stoi(age);
        string grade;
        readLine(fin, grade);
        record.grade = stof(grade);
        students.push_back(record);
    }
    fin.close();
    return students;
}
bool compareByFirstName(student a, student b) {
    return a.firstname.compare(b.firstname) < 0;
}
bool compareByLastName(student a, student b) {
    return a.lastname.compare(b.lastname) < 0;
}
bool compareBySid(student a, student b) {
    return a.number < b.number;
}
bool compareByGpa(student a, student b) {
    return a.grade > b.grade;
}
bool compareByAge(student a, student b) {
    return a.age < b.age;
}
void displayStudents(vector<student> students) {
    for(int i = 0; i < students.size();i++) {
        cout << "First name: " << students[i].firstname << endl;
        cout << "Last name: " << students[i].lastname << endl;
        cout << "SID: " << students[i].number << endl;
        cout << "GPA: " << students[i].grade << endl;
        cout << "AGE: " << students[i].age << endl;
    }
}
void writeToFile(string fileName, vector<student> students, string sortingMethod) {
    ofstream fout;
    fout.open(fileName,ios_base::out);
    if(sortingMethod.length()) {
        fout << "# You data was sorted by " + sortingMethod + '\n';
    }
    for(int i = 0; i < students.size(); i++) {
        fout << students[i].firstname + "\n";
        fout << students[i].lastname + "\n";
        fout << to_string(students[i].number) + "\n";
        string age = to_string(students[i].age);
        fout << age + "\n";
        fout << floatToString(students[i].grade) + ( i == students.size() - 1 ? "" : "\n");
    }
    fout.close();
}
void addStudent(vector<student> &students) {
    char response = 'y';

    do {
        student record;
        string number, gpa, age, firstName, lastName, buffer;
        cout << "Enter first name: " << endl;
        getline(cin, buffer);
        getline(cin, firstName);
        while(contains_non_alpha(firstName)) {
            cout << "Error, value should be alphabetic" << endl;
            cout << "Enter first name: " << endl;
            getline(cin, firstName);
        }
        record.firstname = firstName;
        cout << "Enter last name: " << endl;
        getline(cin, lastName);
        while(contains_non_alpha(lastName)) {
            cout << "Error, value should be alphabetic" << endl;
            cout << "Enter last name: " << endl;
            getline(cin, lastName);
        }
        record.lastname = lastName;
        cout << "Enter SID: " << endl;
        cin >> number;
        while(!validateInt(number) || number.length() < 9) {
            cout << "Value must be numeric and 9 digits long!" << endl;
            cout << "Enter SID: " << endl;
            cin >> number;
        }
        while(ifSidUsed(students, number)) {
            cout << "Error, SID is already taken" << endl;
            cout << "Enter SID: " << endl;
            cin >> number;
        }
        record.number = stoi(number);
        //record.number =  generateSid();
        cout << "Enter GPA: " << endl;
        cin >> gpa;
        while(!validateInt(gpa) || strncmp(gpa.c_str(), "4.0", 3) == 1) {
            cout << "Value must be numeric!" << endl;
            cout << "Enter GPA: " << endl;
            cin >> gpa;
        }
        record.grade = stof(gpa);
        cout << "Enter age: " << endl;
        cin >> age;
        while(!validateInt(age)) {
            cout << "Value must be numeric!" << endl;
            cout << "Enter age: " << endl;
            cin >> age;
        }
        record.age = stoi(age);
        students.push_back(record);
        cout << "The student was successfully added!" << endl;
        cout << "Would you like to add another student? y/n" << endl;
        cin >> response;
    }
    while(response != 'n');
}
void updateStudent(vector<student> &students) {
    int sid;
    string firstName, lastName, gpa, age;
    cout << "Let's find the student!" << endl;
    cout << "Enter SID" << endl;
    cin >> sid;
    while (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Sorry, the value must be numeric!" << endl;
        cout << "Enter SID" << endl;
        cin >> sid;
    }
    for (int i = 0; i < students.size(); i++) {
        if (students[i].number == sid) {
            student& record = students[i];
            string buffer;
            getline(cin, buffer);
            cout << "Student found!" << endl;
            cout << "Enter first name(" + students[i].firstname + "): ";
            getline(cin,firstName);
            if(firstName.length()) {
                while(contains_non_alpha(firstName)) {
                    cout << "Error, value should be alphabetic" << endl;
                    cout << "Enter first name: " << endl;
                    getline(cin, firstName);
                }
                record.firstname = firstName;
            }
            cout << "Enter last name(" + students[i].lastname  + "): ";
            getline(cin,lastName);
            if(lastName.length()) {
                while(contains_non_alpha(lastName)) {
                    cout << "Error, value should be alphabetic" << endl;
                    cout << "Enter last name: " << endl;
                    getline(cin, lastName);
                }
                record.lastname = lastName;
            }
            cout << "Enter GPA(" + floatToString(students[i].grade)  + "): ";
            getline(cin, gpa);
            if(gpa.length()) {
                while(!validateInt(gpa) || strncmp(gpa.c_str(), "4.0", 3) == 1) {
                    cout << "Value must be numeric!" << endl;
                    cout << "Enter GPA: " << endl;
                    cin >> gpa;
                }
                record.grade = stof(gpa);
            }
            cout << "Enter age(" + to_string(students[i].age)  + "): ";
            getline(cin,age);
            if(age.length()) {
                while(!validateInt(age)) {
                    cout << "Value must be numeric!" << endl;
                    cout << "Enter age: " << endl;
                    cin >> age;
                }
                record.age = stoi(age);
            }
            break;
        }
    }
}
void deleteStudent(vector<student> &students) {
    int sid;
    string firstName, lastName, gpa, age;
    cout << "Let's find the student!" << endl;
    cout << "Enter SID" << endl;
    cin >> sid;
    bool deleted = false;
    while (!cin || sid <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Sorry, the value must be a positive number greater than 0!" << endl;
        cout << "Enter SID" << endl;
        cin >> sid;
    }
    for (int i = 0; i < students.size(); i++) {
        if (students[i].number == sid) {
            cout << students[i].firstname << endl;
            cout << students[i].lastname << endl;
            cout << students[i].number << endl;
            cout << students[i].grade << endl;
            cout << students[i].age << endl;
            cout << "Student was deleted!" << endl;
            students.erase(students.begin() + i);
            deleted = true;
        }
    }
    if(!deleted) {
        cout << "Student not found" << endl;
    }
}

string floatToString(float num) {
    string str = to_string(num);
    return str.erase ( str.find_last_not_of('0') + 2, std::string::npos);
}
int generateSid() {
    ostringstream os;
    srand(time(0));
    for (int i = 0; i < 9; ++i)
    {
        int digit = rand() % 9 + 1;
        os << digit;
    }
    return stoi(os.str());
}

vector<user> loadUsers() {
    ifstream fin;
    fin.open("users.txt");
    vector<user> users;
    while(!fin.eof()) {
        user record;
        getline(fin, record.login);
        removeNewLine(record.login);
        getline(fin, record.password);
        removeNewLine(record.password);
        users.push_back(record);
    }
    fin.close();
    return users;

}
bool authenticate() {
    string login, password;
    vector<user> users = loadUsers();
    for(int i = 0; i < 3; i++) {
        cout << "Enter Login: " << endl;
        getline(cin, login);
        cout << "Enter Password: " << endl;
        getline(cin,password);
        for(int i = 0; i < users.size(); i++) {
            if(strncmp(users[i].login.c_str(), login.c_str(), login.length()) == 0 && strncmp(users[i].password.c_str(), password.c_str(), password.length()) == 0) {
                return true;
            }
        }
        cout << "Sorry, user is not found" << endl;
        cout << "Please try again" << endl;
    }
    return false;

}
void removeNewLine(string &input) {
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
}
bool ifSidUsed(vector<student> students, string input) {
    for(int i = 0; i < students.size(); i++) {
        if(students[i].number == stoi(input)) {
            return true;
        }
    }
    return false;
}
bool validateInt(string input) {
    try {
        int num = stoi(input);
        return num > 0;
    } catch(invalid_argument e) {
        return false;
    }
}
bool contains_non_alpha(string str){
    return !std::regex_match(str, std::regex("^[A-Za-z]+$"));
}