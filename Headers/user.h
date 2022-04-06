#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class User
{
private:
    string name;
    string id;
    string password;

public:
    User(string name, string id, string password)
    {
        this->name = name;
        this->id = id;
        this->password = password;
    }

    void getName()
    {
        cout << "Name: " << name << endl;
    }

    string getId()
    {
        return id;
    }

    vector<vector<string>> userIssuedBooks(string searchKey)
    {
        string fname = "bookList.csv";
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

                string id;
                id = row[4];
                transform(id.begin(), id.end(), id.begin(), ::tolower);
                transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                int index_str;
                if (id == searchKey)
                {
                    vector<string> book;
                    book.push_back(row[0]);
                    book.push_back(row[1]);
                    book.push_back(row[2]);
                    book.push_back(row[3]);
                    book.push_back(row[5]);
                    book.push_back(row[6]);
                    content.push_back(book);
                }
            }
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;

        return content;
    }
};

const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

int countLeapYears(vector<int> v)
{
    int years = v[2];

    if (v[1] <= 2)
        years--;

    return years / 4 - years / 100 + years / 400;
}

class Student : User
{
private:
    int fine_amount;
    vector<vector<string>> list_of_books;

public:
    Student(string name, string id, string password, int fine_amount, vector<vector<string>> list_of_books) : User(name, id, password)
    {
        this->fine_amount = fine_amount;
        this->list_of_books = list_of_books;
    }

    void setIssuedBooks(){
        this->list_of_books = userIssuedBooks(getId());
    }

    void calculate_fine()
    {
        int amount = 0;
        string fname = "userList.csv";

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
                if (row[1] == getId())
                    break;
            }

            vector<int> current_date;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            current_date.push_back(ltm->tm_mday);
            current_date.push_back(1 + ltm->tm_mon);
            current_date.push_back(1900 + ltm->tm_year);

            vector<int> due_date;

            int days = 0;
            int n = stoi(row[5]);
            string part;
            int i = 1;
            while (i <= n)
            {
                due_date.clear();
                stringstream str(row[5 + i * 3]);
                while (getline(str, part, '/'))
                    due_date.push_back(stoi(part));

                i++;

                long int n1 = current_date[2] * 365 + current_date[0];

                for (int i = 0; i < current_date[1] - 1; i++)
                    n1 += monthDays[i];

                n1 += countLeapYears(current_date);

                long int n2 = due_date[2] * 365 + due_date[0];
                for (int i = 0; i < due_date[1] - 1; i++)
                    n2 += monthDays[i];
                n2 += countLeapYears(due_date);

                if (n1 > n2)
                    days += n1 - n2;
                else
                    days += 0;
            }

            amount = 2 * days;
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;
        cout << ">> Fine amount: Rs." << amount << endl;
        cout << endl;
        this->fine_amount = amount;
    }

    void updateStudentFine()
    {
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

                if (id_row != getId())
                    userFile << line << endl;
                else
                {
                    row[4] = to_string(fine_amount);
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

    void clear_fine_amount()
    {
        this->fine_amount = 0;
    }

    void getStudentName()
    {
        getName();
    }

    void getFineAmount()
    {
        cout << ">> Fine amount: Rs." << fine_amount << endl;
    }

    string getStudentId()
    {
        return getId();
    }

    void listIssuedBooks()
    {
        if (list_of_books.size() > 0)
        {
            cout << ">> Issued Books: " << endl;
            for (int i = 0; i < list_of_books.size(); i++)
            {
                cout << "---------------------------------------" << endl;
                cout << "Author: " << list_of_books[i][0] << endl;
                cout << "Title: " << list_of_books[i][1] << endl;
                cout << "ISBN: " << list_of_books[i][2] << endl;
                cout << "Publication: " << list_of_books[i][3] << endl;
                cout << "Issue Date: " << list_of_books[i][4] << endl;
                cout << "Return Date: " << list_of_books[i][5] << endl;
                cout << "---------------------------------------" << endl;
            }
        }
        else
        {
            cout << "---------------------------------------" << endl;
            cout << ">> No books issued" << endl;
            cout << "---------------------------------------" << endl;
        }
    }

    int getNumberOfIssuedBooksStudent()
    {
        return list_of_books.size();
    }
};

class Professor : User
{
private:
    int fine_amount;
    vector<vector<string>> list_of_books;

public:
    Professor(string name, string id, string password, int fine_amount, vector<vector<string>> list_of_books) : User(name, id, password)
    {
        this->fine_amount = fine_amount;
        this->list_of_books = list_of_books;
    }

    void setIssuedBooks(){
        this->list_of_books = userIssuedBooks(getId());
    }
    
    void calculate_fine()
    {
        int amount = 0;
        string fname = "userList.csv";

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
                if (row[1] == getId())
                    break;
            }

            vector<int> current_date;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            current_date.push_back(ltm->tm_mday);
            current_date.push_back(1 + ltm->tm_mon);
            current_date.push_back(1900 + ltm->tm_year);

            vector<int> due_date;

            int days = 0;
            int n = stoi(row[5]);
            string part;
            int i = 1;
            while (i <= n)
            {
                due_date.clear();
                stringstream str(row[5 + i * 3]);
                while (getline(str, part, '/'))
                    due_date.push_back(stoi(part));

                i++;

                long int n1 = current_date[2] * 365 + current_date[0];

                for (int i = 0; i < current_date[1] - 1; i++)
                    n1 += monthDays[i];

                n1 += countLeapYears(current_date);

                long int n2 = due_date[2] * 365 + due_date[0];
                for (int i = 0; i < due_date[1] - 1; i++)
                    n2 += monthDays[i];
                n2 += countLeapYears(due_date);

                if (n1 > n2)
                    days += n1 - n2;
                else
                    days += 0;
            }

            amount = 5 * days;
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;
        cout << ">> Fine amount: Rs." << amount << endl;
        cout << endl;
        this->fine_amount = amount;
    }

    void updateProfessorFine()
    {
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

                if (id_row != getId())
                    userFile << line << endl;
                else
                {
                    row[4] = to_string(fine_amount);
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

    void clear_fine_amount()
    {
        this->fine_amount = 0;
    }

    void getProfessorName()
    {
        getName();
    }

    void getFineAmount()
    {
        cout << ">> Fine amount: Rs." << fine_amount << endl;
    }

    string getProfessorId()
    {
        return getId();
    }

    void listIssuedBooks()
    {
        if (list_of_books.size() > 0)
        {
            cout << ">> Issued Books: " << endl;
            for (int i = 0; i < list_of_books.size(); i++)
            {
                cout << "---------------------------------------" << endl;
                cout << "Author: " << list_of_books[i][0] << endl;
                cout << "Title: " << list_of_books[i][1] << endl;
                cout << "ISBN: " << list_of_books[i][2] << endl;
                cout << "Publication: " << list_of_books[i][3] << endl;
                cout << "Issue Date: " << list_of_books[i][4] << endl;
                cout << "Return Date: " << list_of_books[i][5] << endl;
                cout << "---------------------------------------" << endl;
            }
        }
        else
        {
            cout << "---------------------------------------" << endl;
            cout << ">> No books issued" << endl;
            cout << "---------------------------------------" << endl;
        }
    }

    int getNumberOfIssuedBooksProfessor()
    {
        return list_of_books.size();
    }
};

class Librarian : User
{
public:
    Librarian(string name, string id, string password) : User(name, id, password)
    {
    }

    void getLibrarianName()
    {
        getName();
    }

    string getLibrarianId()
    {
        return getId();
    }
};