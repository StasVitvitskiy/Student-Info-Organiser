#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct student {
    string firstname, lastname;
    int age, number;
    float grade;
};

vector<student> readFromFile(string fileName);
bool compareByFirstName(student a, student b);
bool compareByLastName(student a, student b);
bool compareBySid(student a, student b);
bool compareByAge(student a, student b);
bool compareByGpa(student a, student b);
void displayStudents(vector<student> students);
void writeToFile(vector<student> students, string sortingMethod);
bool isComment(string line);
void readLine(ifstream& fin, string& str);


int main() {
    while(true) {
        string fileName;
        int oMethod = 0;
        cout << "Enter the file name" << endl;
        cin >> fileName;
        vector<student> students = readFromFile(fileName);

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
        string sortingMethod;
        switch (oMethod) {
            case 0:
                cout << "Quitting..." << endl;
                return 0;
                break;
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
        writeToFile(students, sortingMethod);
        cout << "Success! ";
        cout << "Your data has been organized and stored in the output.txt file" << endl;
        cout << "Do you want to organise another file? y/n" << endl;
        char response;
        cin >> response;
        if(response == 'n') {
            cout << "Goodbye";
            return 0;
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
void writeToFile(vector<student> students, string sortingMethod) {
    ofstream fout;
    fout.open("output.txt",ios_base::out);
    fout << "# You data was sorted by " + sortingMethod + '\n';
    for(int i = 0; i < students.size(); i++) {
        fout << students[i].firstname + "\n";
        fout << students[i].lastname + "\n";
        fout << to_string(students[i].number) + "\n";
        string grade = to_string(students[i].grade);
        fout << grade.erase ( grade.find_last_not_of('0') + 1, std::string::npos ) + "\n";
        fout << to_string(students[i].age) + "\n";
    }
    fout.close();
}