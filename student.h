#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void studentPortal(Student student)
{
    cout << "-------Student Portal-------\n"
         << endl;
    student.getStudentName();
    cout << endl;
    cout << "1. See all books" << endl;
    cout << "2. Search for a book." << endl;
    cout << "3. List the issued books" << endl;
    cout << "4. Availability status of book" << endl;
    cout << "5. Issue a book" << endl;
    cout << "6. Return a book" << endl;
    cout << "7. Calculate fine" << endl;
    cout << "0. Logout" << endl;
    cout << "---------------------------------------" << endl;

    int response;
    cout << ">> Enter your choice: ";
    cin >> response;
    cout << endl;

    vector<vector<string>> list_of_books;
    BookDatabase books(list_of_books);
    books.setListOfBooks();

    switch (response)
    {
    case 1:
        books.display();
        studentPortal(student);
        break;
    case 2:
        books.search();
        studentPortal(student);
        break;
    case 3:
        student.listIssuedBooks();
        studentPortal(student);
        break;
    case 4:
        books.availabilityStatus();
        studentPortal(student);
        break;
    case 5:
        books.issue(student.getNumberOfIssuedBooksStudent(), student.getStudentId(), "student");
        books.setListOfBooks();
        studentPortal(student);
        break;
    case 6:
        books.returnBook(student.getNumberOfIssuedBooksStudent(), student.getStudentId(), "student");
        books.setListOfBooks();
        studentPortal(student);
        break;
    case 7:
        student.calculate_fine();
        student.updateStudentFine();
        studentPortal(student);
        break;
    
    case 0:
        cout << "\n>> Logged out!!\n"
             << endl;
        break;
    default:
        cout << "\n>> Invalid Choice\n"
             << endl;
        studentPortal(student);
        break;
    }
}

vector<vector<string>> studentIssuedBooks(string searchKey)
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

void loginAsStudent()
{
    cout << "-------Student Login-------" << endl;
    string username, password;
    cout << ">> Enter username: ";
    cin >> username;
    cout << ">> Enter password: ";
    cin >> password;

    string fname = "userList.csv";

    vector<string> row;
    string line, word;

    fstream file(fname, ios::in);
    if (file.is_open())
    {
        int loggedIn = 0;
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            if (row[1] == username && row[3] == "student")
            {
                if (row[2] == password)
                {
                    cout << "\n>> Login Successful\n"
                         << endl;
                    loggedIn = 1;

                    vector<vector<string>> books = studentIssuedBooks(username);
                    string name = row[0];
                    int fine = stoi(row[4]);

                    Student student(name, username, password, fine, books);
                    studentPortal(student);
                }
                else
                {
                    cout << "\n>> Login Failed! Wrong password!\n"
                         << endl;
                    loggedIn = 2;
                    loginAsStudent();
                }
            }
        }

        if (loggedIn == 0)
        {
            cout << "\n>> Login Failed! User not found!\n"
                 << endl;
        }
    }
    else
        cout << "\n>> Could not open the file\n"
             << endl;
}