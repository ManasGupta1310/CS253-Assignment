#include <iostream>
#include <bits/stdc++.h>
#include "bookDatabase.h"

using namespace std;

void librarianPortal(Librarian librarian);

void librarianUserPortal(Librarian librarian)
{
    cout << "-------Librarian Portal-------\n"
         << endl;
    librarian.getLibrarianName();
    cout << endl;
    cout << "1. See all users" << endl;
    cout << "2. Search for a user." << endl;
    cout << "3. Add a user" << endl;
    cout << "4. Delete a user" << endl;
    cout << "5. Update a user" << endl;
    cout << "6. Clear fine of user" << endl;

    cout << "0. Exit" << endl;
    cout << "---------------------------------------" << endl;

    int response;
    cout << ">> Enter your choice: ";
    cin >> response;
    cout << endl;

    vector<vector<string>> list_of_users;
    UserDatabase user(list_of_users);
    user.setListOfUsers();

    switch (response)
    {
    case 1:
        user.display();
        librarianUserPortal(librarian);
        break;
    case 2:
        user.search();
        librarianUserPortal(librarian);
        break;
    case 3:
        user.add();
        user.setListOfUsers();
        librarianUserPortal(librarian);
        break;
    case 4:
        user.deleteUser();
        user.setListOfUsers();
        librarianUserPortal(librarian);
        break;
    case 5:
        user.update();
        user.setListOfUsers();
        librarianUserPortal(librarian);
        break;
    case 6: 
        user.clear_fine();
        user.setListOfUsers();
        librarianUserPortal(librarian);
        break;
    case 0:
        break;
    default:
        cout << "\n>> Invalid Choice\n"
             << endl;
        librarianUserPortal(librarian);
        break;
    }
}

void librarianBookPortal(Librarian librarian)
{
    cout << "-------Librarian Portal-------\n"
         << endl;
    librarian.getLibrarianName();
    cout << endl;
    cout << "1. See all books" << endl;
    cout << "2. Check books issued by user" << endl;
    cout << "3. Add a book." << endl;
    cout << "4. Search for a book." << endl;
    cout << "5. Delete a book" << endl;
    cout << "6. Update a book" << endl;
    cout << "7. Check issuance of book" << endl;

    cout << "0. Exit" << endl;
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
        librarianBookPortal(librarian);
        break;
    case 2:
        books.userIssuedBooks();
        librarianBookPortal(librarian);
        break;
    case 3:
        books.add();
        books.setListOfBooks();
        librarianBookPortal(librarian);
        break;
    case 4:
        books.search();
        librarianBookPortal(librarian);
        break;
    case 5:
        books.deleteBook();
        books.setListOfBooks();
        librarianBookPortal(librarian);
        break;
    case 6:
        books.update();
        books.setListOfBooks();
        librarianBookPortal(librarian);
        break;
    case 7:
        books.issueCheck();
        librarianBookPortal(librarian);
        break;

    case 0:
        break;
    default:
        cout << "\n>> Invalid Choice\n"
             << endl;
        librarianBookPortal(librarian);
        break;
    }
}

void librarianPortal(Librarian librarian)
{
    cout << "-------Librarian Portal-------\n"
         << endl;
    librarian.getLibrarianName();
    cout << endl;
    cout << "1. User portal" << endl;
    cout << "2. Book portal" << endl;

    cout << "0. Logout" << endl;
    cout << "---------------------------------------" << endl;

    int response;
    cout << ">> Enter your choice: ";
    cin >> response;
    cout << endl;

    switch (response)
    {
    case 1:
        librarianUserPortal(librarian);
        librarianPortal(librarian);
        break;
    case 2:
        librarianBookPortal(librarian);
        librarianPortal(librarian);
        break;
    case 0:
        cout << "\n>> Logged out!!\n"
             << endl;
        break;
    default:
        cout << "\n>> Invalid Choice\n"
             << endl;
        librarianPortal(librarian);
        break;
    }
}

void loginAsLibrarian()
{
    cout << "-------Librarian Login-------" << endl;
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
            if (row[1] == username && row[3] == "librarian")
            {
                if (row[2] == password)
                {
                    cout << "\n>> Login Successful\n"
                         << endl;
                    loggedIn = 1;
                    string name = row[0];

                    Librarian librarian(name, username, password);
                    librarianPortal(librarian);
                }
                else
                {
                    cout << "\n>> Login Failed! Wrong password!\n"
                         << endl;
                    loggedIn = 2;
                    loginAsLibrarian();
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