#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void professorPortal(Professor professor)
{
    cout << "-------Professor Portal-------\n"
         << endl;
    professor.getProfessorName();
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
        professorPortal(professor);
        break;
    case 2:
        books.search();
        professorPortal(professor);
        break;
    case 3:
        professor.listIssuedBooks();
        professorPortal(professor);
        break;
    case 4:
        books.availabilityStatus();
        professorPortal(professor);
        break;
    case 5:
        books.issue(professor.getNumberOfIssuedBooksProfessor(), professor.getProfessorId(), "professor");
        books.setListOfBooks();
        professorPortal(professor);
        break;
    case 6:
        books.returnBook(professor.getNumberOfIssuedBooksProfessor(), professor.getProfessorId(), "professor");
        books.setListOfBooks();
        professorPortal(professor);
        break;
    case 7:
        professor.calculate_fine();
        professor.updateProfessorFine();
        professorPortal(professor);
        break;
    case 0:
        cout << "\n>> Logged out!\n"
             << endl;
        break;
    default:
        cout << "\n>> Invalid Choice\n"
             << endl;
        professorPortal(professor);
        break;
    }
}

void loginAsProfessor()
{
    cout << "-------Professor Login-------" << endl;
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
            if (row[1] == username && row[3] == "professor")
            {
                if (row[2] == password)
                {
                    cout << "\n>> Login Successful\n"
                         << endl;
                    loggedIn = 1;

                    string name = row[0];
                    User user(name, username, password);
                    vector<vector<string>> books = user.userIssuedBooks(username);
                    int fine = stoi(row[4]);

                    Professor professor(name, username, password, fine, books);
                    professorPortal(professor);
                }
                else
                {
                    cout << "\n>> Login Failed! Wrong password!\n"
                         << endl;
                    loggedIn = 2;
                    loginAsProfessor();
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
