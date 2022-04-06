#include <iostream>
#include <bits/stdc++.h>
#include "librarian.h"
#include "student.h"
#include "professor.h"

using namespace std;

void initiateLibrarian()
{
    string filename("userList.csv");
    fstream file;

    string readFile = "userList.csv";
    fstream readFilePath(readFile, ios::in);

    string name,id,pass,role;
    name="Librarian";
    id="librarian";
    pass="123";
    role="librarian";

    file.open(filename, std::ios_base::app | std::ios_base::in);

    int found = 0;
    if (readFilePath.is_open())
    {
        string line, word;
        vector<vector<string>> content;
        vector<string> row;
        while (getline(readFilePath, line))
        {
            row.clear();

            stringstream str(line);
            while (getline(str, word, ','))
                row.push_back(word);

            if(row.size()>=4){
                string role_row;
                role_row = row[3];

                if (role_row == role)
                    found++;
            }
        }
    }

    if(found==0){
        file << name << "," << id << "," << pass << "," << role << "," << 0 << "," << 0 << endl;
    }
}

void chooseOption()
{
    cout << "-------Library Management System-------" << endl;
    cout << "1. Login as Student" << endl;
    cout << "2. Login as Professor" << endl;
    cout << "3. Login as Librarian" << endl;
    cout << "0. Exit" << endl;
    cout << "---------------------------------------" << endl;

    int response;
    cout << ">> Enter your choice: ";
    cin >> response;
    cout << endl;
    switch (response)
    {
    case 1:
        loginAsStudent();
        break;
    case 2:
        loginAsProfessor();
        break;
    case 3:
        loginAsLibrarian();
        break;
    case 0:
        cout << "\n>> Exit\n"
             << endl;
        exit(0);
        break;
    default:
        cout << "\n>> Invalid Choice\n"
             << endl;
        break;
    }
}
int main()
{
    initiateLibrarian();

    while (true)
    {
        chooseOption();
    }

    return 0;
}