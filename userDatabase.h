#include <iostream>
#include <bits/stdc++.h>
#include "user.h"

using namespace std;

class UserDatabase
{
private:
    vector<vector<string>> list_of_users;

public:
    UserDatabase(vector<vector<string>> list_of_users)
    {
        this->list_of_users = list_of_users;
    }

    void setListOfUsers()
    {
        string fname = "userList.csv";

        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);
        if (file.is_open())
        {
            while (getline(file, line))
            {
                row.clear();

                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                content.push_back(row);
            }
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;

        this->list_of_users = content;
    }

    void display()
    {
        if (list_of_users.size() == 0)
        {
            cout << "No users to show!!\n"
                 << endl;
        }
        else
        {
            for (int i = 0; i < list_of_users.size(); i++)
            {
                cout << "---------------------------------------" << endl;
                cout << "Name: " << list_of_users[i][0] << endl;
                cout << "ID: " << list_of_users[i][1] << endl;
                cout << "Role: " << list_of_users[i][3] << endl;
                cout << "Books Issued: " << list_of_users[i][5] << endl;
                cout << "---------------------------------------\n"
                     << endl;
            }
        }
    }

    void search()
    {
        string fname = "userList.csv";

        int response;
        cout << "---------------------------------------" << endl;
        cout << "Search by: " << endl;
        cout << "1. Name" << endl;
        cout << "2. Id" << endl;
        cout << "0. Back to portal!" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> response;
        cout << "---------------------------------------" << endl;

        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);
        string searchKey;

        switch (response)
        {
        case 1:
            cout << ">> Enter the name of the user you want to search: ";
            cin >> searchKey;
            cout << endl;
            if (file.is_open())
            {
                int found = 0;
                while (getline(file, line))
                {
                    row.clear();

                    stringstream str(line);
                    while (getline(str, word, ','))
                        row.push_back(word);

                    string name;
                    name = row[0];
                    transform(name.begin(), name.end(), name.begin(), ::tolower);
                    transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                    int index_str;
                    if (name == searchKey || (index_str = name.find(searchKey) != string::npos))
                    {
                        found++;
                        cout << "---------------------------------------" << endl;
                        cout << "Name: " << row[0] << endl;
                        cout << "ID: " << row[1] << endl;
                        cout << "Role: " << row[3] << endl;
                        cout << "Books Issued: " << row[5] << endl;
                        cout << "---------------------------------------\n"
                             << endl;
                    }
                }

                if (found == 0)
                    cout << ">> No such user found!" << endl;
            }
            else
                cout << "\n>> Could not open the file\n"
                     << endl;
            break;
        case 2:
            cout << ">> Enter the ID of the user you want to search: ";
            cin >> searchKey;
            if (file.is_open())
            {
                int found = 0;
                while (getline(file, line))
                {
                    row.clear();

                    stringstream str(line);
                    while (getline(str, word, ','))
                        row.push_back(word);

                    string id;
                    id = row[1];
                    transform(id.begin(), id.end(), id.begin(), ::tolower);
                    transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                    int index_str;
                    if (id == searchKey || (index_str = id.find(searchKey) != string::npos))
                    {
                        found++;
                        cout << "---------------------------------------" << endl;
                        cout << "Name: " << row[0] << endl;
                        cout << "ID: " << row[1] << endl;
                        cout << "Role: " << row[3] << endl;
                        cout << "Books Issued: " << row[5] << endl;
                        cout << "---------------------------------------\n"
                             << endl;
                    }
                }

                if (found == 0)
                    cout << ">> No such user found!" << endl;
                cout << endl;
            }
            else
                cout << "\n>> Could not open the file\n"
                     << endl;
            break;
        case 0:
            break;

        default:
            cout << "\n>> Invalid Choice\n"
                 << endl;
            break;
        }
    }

    void add()
    {
        string filename("userList.csv");
        fstream file;

        string name, id, pass, role;
        cout << "---------------------------------------" << endl;
        cin.ignore();
        cout << ">> Enter the name of the user you want to add: " << endl;
        getline(cin, name);
        cout << ">> Enter the ID of the user you want to add: " << endl;
        getline(cin, id);
        cout << ">> Enter the password of the user you want to add: " << endl;
        getline(cin, pass);
        cout << ">> Enter the role of the user you want to add: " << endl;
        getline(cin, role);
        cout << "---------------------------------------" << endl;

        if (name == "" || id == "" || pass == "" || role == "")
        {
            cout << ">> Can't have empty fields!\n"
                 << endl;
            return;
        }

        if (role == "librarian")
        {
            cout << "Not allowed to enter user with librarian role!\n"
                 << endl;
            return;
        }

        file.open(filename, std::ios_base::app | std::ios_base::in);
        if (file.is_open())
            file << name << "," << id << "," << pass << "," << role << "," << 0 << "," << 0 << endl;
        cout << ">> Added user successfully!\n"
             << endl;
    }

    void deleteUser()
    {
        string filename("sampleUserList.csv");
        fstream file;

        string readFile = "userList.csv";
        fstream readFilePath(readFile, ios::in);

        string id;
        cout << "---------------------------------------" << endl;
        cin.ignore();
        cout << ">> Enter the ID of the user you want to delete: " << endl;
        getline(cin, id);
        cout << "---------------------------------------" << endl;

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

                string id_row;
                id_row = row[1];

                if (id_row != id)
                    file << line << endl;
                else
                    found++;
            }
        }

        remove(readFile.c_str());
        rename("sampleUserList.csv", readFile.c_str());
        if (found != 0)
            cout << ">> Deleted user successfully!\n"
                 << endl;
        else
            cout << ">> No such user found!\n"
                 << endl;
    }

    void update()
    {
        string filename("sampleUserList.csv");
        fstream file;

        string readFile = "userList.csv";
        fstream readFilePath(readFile, ios::in);

        string id;
        string new_name, new_id, new_pass, new_role;
        cout << "---------------------------------------" << endl;
        cin.ignore();
        cout << ">> Enter the id of the user you want to update:" << endl;
        getline(cin, id);
        cout << ">> Enter the updated name of the user: (Hit enter to enter default value!)" << endl;
        getline(cin, new_name);
        cout << ">> Enter the updated ID of the user: (Hit enter to enter default value!)" << endl;
        getline(cin, new_id);
        cout << ">> Enter the updated password of the user: (Hit enter to enter default value!)" << endl;
        getline(cin, new_pass);
        cout << ">> Enter the updated role of the user: (Hit enter to enter default value!)" << endl;
        getline(cin, new_role);
        cout << "---------------------------------------" << endl;

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

                string s = "";
                for (int i = 4; i < row.size(); i++)
                {
                    s += ",";
                    s += row[i];
                }

                string id_row;
                id_row = row[1];

                if (id_row != id)
                    file << line << endl;
                else
                {
                    if (new_name == "")
                    {
                        new_name = row[0];
                    }
                    if (new_id == "")
                    {
                        new_id = row[1];
                    }
                    if (new_pass == "")
                    {
                        new_pass = row[2];
                    }
                    if (new_role == "")
                    {
                        new_role = row[3];
                    }
                    file << new_name << "," << new_id << "," << new_pass << "," << new_role << s << endl;
                    found++;
                }
            }
        }

        remove(readFile.c_str());
        rename("sampleUserList.csv", readFile.c_str());
        if (found != 0)
            cout << ">> Updated user successfully!\n"
                 << endl;
        else
            cout << ">> No such user found!\n"
                 << endl;
    }

    bool userCheck(string searchKey)
    {
        string fname = "userList.csv";
        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);

        if (file.is_open())
        {
            int found = 0;
            while (getline(file, line))
            {
                row.clear();

                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                string id;
                id = row[1];
                transform(id.begin(), id.end(), id.begin(), ::tolower);
                transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                if (id == searchKey)
                {
                    found++;
                    return true;
                }
            }

            if (found == 0)
                cout << ">> No such user found!" << endl;
            cout << endl;
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;

        return false;
    }

    void clear_fine()
    {
        string fname = "userList.csv";

        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);
        string searchKey;
        cout << ">> Enter the ID of the user you want to clear fine of: ";
        cin >> searchKey;
        if (file.is_open())
        {
            int found = 0;
            while (getline(file, line))
            {
                row.clear();

                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                string id;
                id = row[1];
                transform(id.begin(), id.end(), id.begin(), ::tolower);
                transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                int index_str;
                if (id == searchKey || (index_str = id.find(searchKey) != string::npos))
                {
                    found++;
                    cout << "---------------------------------------" << endl;
                    cout << "Name: " << row[0] << endl;
                    cout << "ID: " << row[1] << endl;
                    cout << "Role: " << row[3] << endl;
                    cout << "Fine: " << row[4] << endl;
                    cout << "Book issued: " << row[5] << endl;
                    cout << "---------------------------------------\n"
                         << endl;

                    if (row[3] == "student")
                    {
                        User user(row[0], row[1], row[2]);
                        vector<vector<string>> books = user.userIssuedBooks(row[1]);
                        int fine = stoi(row[4]);

                        Student student(row[0], row[1], row[2], stoi(row[4]), books);
                        student.clear_fine_amount();
                        student.updateStudentFine();
                    }
                    else if (row[3] == "professor")
                    {
                        User user(row[0], row[1], row[2]);
                        vector<vector<string>> books = user.userIssuedBooks(row[1]);
                        int fine = stoi(row[4]);

                        Professor professor(row[0], row[1], row[2], stoi(row[4]), books);
                        professor.clear_fine_amount();
                        professor.updateProfessorFine();
                    }

                    cout << "Fine cleared!\n"
                         << endl;
                }
            }

            if (found == 0)
                cout << ">> No such user found!" << endl;
            cout << endl;
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;
    }
};