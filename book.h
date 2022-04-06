#include <iostream>
#include <bits/stdc++.h>
#include "dateFunctions.h"
using namespace std;

class Book
{
private:
    string title;
    string author;
    string publisher;
    string isbn;
    string issued_to;
    string duedate;
    string issue_date;

public:
    Book(string title, string author, string publisher, string isbn, string issued_to, string issue_date, string duedate)
    {
        this->title = title;
        this->author = author;
        this->publisher = publisher;
        this->isbn = isbn;
        this->issued_to = issued_to;
        this->duedate = duedate;
        this->issue_date = issue_date;
    }

    void print()
    {
        cout << "-----------------------------" << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "-----------------------------\n"
             << endl;
    }

    void show_duedate()
    {
        cout << "-----------------------------" << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Issued to: " << issued_to << endl;
        cout << "Issue date: " << issue_date << endl;
        cout << "Due date: " << duedate << endl;
        cout << "-----------------------------\n"
             << endl;
    }

    int show_Availability()
    {
        cout << "-----------------------------" << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Publisher: " << publisher << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Issued to: " << issued_to << endl;
        cout << "Issue date: " << issue_date << endl;
        cout << "Due date: " << duedate << endl;
        if (issued_to == "none")
        {
            cout << "Availability: Yes" << endl;
        }
        else
        {
            cout << "Availability: No" << endl;
        }
        cout << "-----------------------------"
             << endl;

        if (issued_to == "none")
        {
            return 1;
        }
        return 0;
    }

    void addIssuedBook(string id, string isbn, string role)
    {

        string filename("sampleBookList.csv");
        fstream file;

        string readFile = "bookList.csv";
        fstream readFilePath(readFile, ios::in);

        file.open(filename, std::ios_base::app | std::ios_base::in);

        if (readFilePath.is_open())
        {
            string line, word;
            vector<string> row;
            while (getline(readFilePath, line))
            {
                row.clear();

                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                string isbn_row;
                isbn_row = row[2];

                if (isbn_row != isbn)
                    file << line << endl;
                else
                {
                    time_t now = time(0);
                    tm *ltm = localtime(&now);

                    string issuedate = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
                    string duedate;
                    if (role == "student")
                    {
                        Date date(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                        duedate = date.addDays(30);
                    }
                    else
                    {
                        Date date(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                        duedate = date.addDays(60);
                    }
                    file << row[0] << "," << row[1] << "," << isbn << ","
                         << row[3] << "," << id << "," << issuedate << "," << duedate << endl;
                }
            }
        }

        remove(readFile.c_str());
        rename("sampleBookList.csv", readFile.c_str());

        string userFilename("sampleUserList.csv");
        fstream userFile;

        string userReadFile = "userList.csv";
        fstream userReadFilePath(userReadFile, ios::in);

        userFile.open(userFilename, std::ios_base::app | std::ios_base::in);

        if (userReadFilePath.is_open())
        {
            string line, word;
            vector<string> row;
            while (getline(userReadFilePath, line))
            {
                row.clear();
                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                string id_row;
                id_row = row[1];

                if (id_row != id)
                    userFile << line << endl;
                else
                {
                    row[5] = to_string(stoi(row[5]) + 1);
                    for (int i = 0; i < row.size() - 1; i++)
                    {
                        userFile << row[i] << ",";
                    }
                    userFile << row[row.size() - 1];

                    time_t now = time(0);
                    tm *ltm = localtime(&now);

                    string issuedate = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
                    string duedate;
                    if (role == "student")
                    {
                        Date date(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                        duedate = date.addDays(30);
                    }
                    else
                    {
                        Date date(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
                        duedate = date.addDays(60);
                    }
                    string s = "," + isbn + "," + issuedate + "," + duedate;

                    userFile << s << endl;
                }
            }
        }

        remove(userReadFile.c_str());
        rename("sampleUserList.csv", userReadFile.c_str());
    }

    void book_request(int issuedBooks, string id, string role, string isbn)
    {
        if (role == "student")
        {
            if (issuedBooks < 5)
            {
                cout << endl;
                cout << "Issued to: " << id << endl;
                cout << "Please return the book within due date to avoid any fine amount!" << endl;
                addIssuedBook(id, isbn, role);
            }
            else
            {
                cout << "You have already issued 5 books! Book issue limit reached" << endl;
            }
        }
        else
        {
            cout << endl;
            cout << "Issued to: " << id << endl;
            cout << "Please return the book within due date to avoid any fine amount!" << endl;
            addIssuedBook(id, isbn, role);
        }
    }

    void book_return(string id, string role, string isbn)
    {
        string filename("sampleBookList.csv");
        fstream file;

        string readFile = "bookList.csv";
        fstream readFilePath(readFile, ios::in);

        file.open(filename, std::ios_base::app | std::ios_base::in);

        if (readFilePath.is_open())
        {
            string line, word;
            vector<string> row;
            while (getline(readFilePath, line))
            {
                row.clear();

                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                string isbn_row;
                isbn_row = row[2];

                if (isbn_row != isbn)
                    file << line << endl;
                else
                {
                    file << row[0] << "," << row[1] << "," << isbn << ","
                         << row[3] << ","
                         << "none"
                         << ","
                         << "none"
                         << ","
                         << "none" << endl;
                }
            }
        }

        remove(readFile.c_str());
        rename("sampleBookList.csv", readFile.c_str());

        string userFilename("sampleUserList.csv");
        fstream userFile;

        string userReadFile = "userList.csv";
        fstream userReadFilePath(userReadFile, ios::in);

        userFile.open(userFilename, std::ios_base::app | std::ios_base::in);

        if (userReadFilePath.is_open())
        {
            string line, word;
            vector<string> row;
            while (getline(userReadFilePath, line))
            {
                row.clear();
                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                string id_row;
                id_row = row[1];

                if (id_row != id)
                    userFile << line << endl;
                else
                {
                    row[5] = to_string(stoi(row[5]) - 1);
                    for (int i = 0; i < row.size(); i++)
                    {
                        if (row[i] == isbn)
                        {
                            row.erase(row.begin() + i);
                            row.erase(row.begin() + i);
                            row.erase(row.begin() + i);
                            break;
                        }
                    }

                    for (int i = 0; i < row.size() - 1; i++)
                    {
                        userFile << row[i] << ",";
                    }
                    userFile << row[row.size() - 1] << endl;
                }
            }
        }

        remove(userReadFile.c_str());
        rename("sampleUserList.csv", userReadFile.c_str());
    }
};
