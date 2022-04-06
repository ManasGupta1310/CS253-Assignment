#include <iostream>
#include <bits/stdc++.h>
#include "book.h"
#include "userDatabase.h"

using namespace std;

class BookDatabase
{
private:
    vector<vector<string>> list_of_books;

public:
    BookDatabase(vector<vector<string>> list_of_books)
    {
        this->list_of_books = list_of_books;
    }

    void setListOfBooks()
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

                content.push_back(row);
            }
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;

        this->list_of_books = content;
    }

    void display()
    {
        if (list_of_books.size() == 0)
        {
            cout << "No books to show!!\n"
                 << endl;
        }
        else
        {
            for (int i = 0; i < list_of_books.size(); i++)
            {
                Book book(list_of_books[i][1], list_of_books[i][0], list_of_books[i][2], list_of_books[i][3], list_of_books[i][4], list_of_books[i][5], list_of_books[i][6]);
                book.print();
            }
        }
    }

    void search()
    {
        string fname = "bookList.csv";

        int response;
        cout << "---------------------------------------" << endl;
        cout << "Search by: " << endl;
        cout << "1. Title" << endl;
        cout << "2. Author" << endl;
        cout << "3. ISBN" << endl;
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
            cin.ignore();
            cout << ">> Enter the title of the book you want to search: ";
            getline(cin, searchKey);
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

                    string title;
                    title = row[1];
                    transform(title.begin(), title.end(), title.begin(), ::tolower);
                    transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                    int index_str;
                    if (title == searchKey || (index_str = title.find(searchKey) != string::npos))
                    {
                        found++;
                        Book book(row[1], row[0], row[2], row[3], row[4], row[5], row[6]);
                        book.print();
                    }
                }

                if (found == 0)
                    cout << "\n>> No such book found!" << endl;
            }
            else
                cout << "\n>> Could not open the file\n"
                     << endl;
            break;
        case 2:
            cin.ignore();
            cout << ">> Enter the author of the book you want to search: ";
            getline(cin, searchKey);
            if (file.is_open())
            {
                int found = 0;
                while (getline(file, line))
                {
                    row.clear();

                    stringstream str(line);
                    while (getline(str, word, ','))
                        row.push_back(word);

                    string author;
                    author = row[0];
                    transform(author.begin(), author.end(), author.begin(), ::tolower);
                    transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                    int index_str;
                    if (author == searchKey || (index_str = author.find(searchKey) != string::npos))
                    {
                        found++;
                        Book book(row[1], row[0], row[2], row[3], row[4], row[5], row[6]);
                        book.print();
                    }
                }

                if (found == 0)
                    cout << "\n>> No such book found!" << endl;
                cout << endl;
            }
            else
                cout << "\n>> Could not open the file\n"
                     << endl;
            break;
        case 3:
            cin.ignore();
            cout << ">> Enter the ISBN of the book you want to search: ";
            getline(cin, searchKey);
            if (file.is_open())
            {
                int found = 0;
                while (getline(file, line))
                {
                    row.clear();

                    stringstream str(line);
                    while (getline(str, word, ','))
                        row.push_back(word);

                    string isbn;
                    isbn = row[2];
                    transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
                    transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                    int index_str;
                    if (isbn == searchKey)
                    {
                        found++;
                        Book book(row[1], row[0], row[2], row[3], row[4], row[5], row[6]);
                        book.print();
                    }
                }

                if (found == 0)
                    cout << "\n>> No such book found!" << endl;
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
        string filename("bookList.csv");
        fstream file;

        string title, author, isbn, publication;
        cout << "---------------------------------------" << endl;
        cin.ignore();
        cout << ">> Enter the author of the book you want to add: " << endl;
        getline(cin, author);
        cout << ">> Enter the title of the book you want to add: " << endl;
        getline(cin, title);
        cout << ">> Enter the ISBN of the book you want to add: " << endl;
        getline(cin, isbn);
        cout << ">> Enter the publication of the book you want to add: " << endl;
        getline(cin, publication);
        cout << "---------------------------------------" << endl;

        if (author == "" || title == "" || isbn == "" || publication == "")
        {
            cout<<">> Can't have empty fields!\n"<<endl;
            return;
        }
        file.open(filename, std::ios_base::app | std::ios_base::in);
        if (file.is_open())
            file << author << "," << title << "," << isbn << "," << publication << ",none,none,none" << endl;
        cout << ">> Added  book successfully!\n"
             << endl;
    }

    void deleteBook()
    {
        string filename("sampleBookList.csv");
        fstream file;

        string readFile = "bookList.csv";
        fstream readFilePath(readFile, ios::in);

        string isbn;
        cout << "---------------------------------------" << endl;
        cin.ignore();
        cout << ">> Enter the ISBN of the book you want to delete: " << endl;
        getline(cin, isbn);
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

                string isbn_row;
                isbn_row = row[2];

                if (isbn_row != isbn)
                    file << line << endl;
                else
                    found++;
            }
        }

        remove(readFile.c_str());
        rename("sampleBookList.csv", readFile.c_str());
        if (found != 0)
            cout << ">> Deleted  book successfully!\n"
                 << endl;
        else
            cout << ">> No such book found!\n"
                 << endl;
    }

    void update()
    {
        string filename("sampleBookList.csv");
        fstream file;

        string readFile = "bookList.csv";
        fstream readFilePath(readFile, ios::in);

        string isbn;
        string new_title, new_author, new_isbn, new_publication, new_issuedTo, new_duedate, new_issuedate;
        cout << "---------------------------------------" << endl;
        cin.ignore();
        cout << ">> Enter the ISBN of the book you want to update: " << endl;
        getline(cin, isbn);
        cout << ">> Enter the updated author of the book: (Hit enter to enter default value!)" << endl;
        getline(cin, new_author);
        cout << ">> Enter the updated title of the book: (Hit enter to enter default value!)" << endl;
        getline(cin, new_title);
        cout << ">> Enter the updated ISBN of the book: (Hit enter to enter default value!)" << endl;
        getline(cin, new_isbn);
        cout << ">> Enter the updated publication of the book: (Hit enter to enter default value!)" << endl;
        getline(cin, new_publication);
        cout << ">> Enter the updated issued person of the book: (Hit enter to enter default value!)" << endl;
        getline(cin, new_issuedTo);
        cout << ">> Enter the updated issue date of the book: (Hit enter to enter default value!)" << endl;
        getline(cin, new_issuedate);
        cout << ">> Enter the updated due date of the book: (Hit enter to enter default value!)" << endl;
        getline(cin, new_duedate);
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

                string isbn_row;
                isbn_row = row[2];

                if (isbn_row != isbn)
                    file << line << endl;
                else
                {
                    if (new_author == "")
                        new_author = row[0];
                    if (new_title == "")
                        new_title = row[1];
                    if (new_isbn == "")
                        new_isbn = row[2];
                    if (new_publication == "")
                        new_publication = row[3];
                    if (new_issuedTo == "")
                        new_issuedTo = row[4];
                    if (new_issuedate == "")
                        new_issuedate = row[5];
                    if (new_duedate == "")
                        new_duedate = row[6];
                    file << new_author << "," << new_title << "," << new_isbn << ","
                         << new_publication << "," << new_issuedTo << "," << new_issuedate << "," << new_duedate << endl;
                    found++;
                }
            }
        }

        remove(readFile.c_str());
        rename("sampleBookList.csv", readFile.c_str());
        if (found != 0)
            cout << ">> Updated  book successfully!\n"
                 << endl;
        else
            cout << ">> No such book found!\n"
                 << endl;
    }

    void issueCheck()
    {
        string fname = "bookList.csv";
        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);
        string searchKey;
        cin.ignore();
        cout << ">> Enter the ISBN of the book you want to check issue status: ";
        getline(cin, searchKey);
        if (file.is_open())
        {
            int found = 0;
            while (getline(file, line))
            {
                row.clear();

                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                string isbn;
                isbn = row[2];
                transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
                transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                int index_str;
                if (isbn == searchKey)
                {
                    found++;
                    Book book(row[1], row[0], row[2], row[3], row[4], row[5], row[6]);
                    book.show_duedate();
                }
            }

            if (found == 0)
                cout << "\n>> No such book found!" << endl;
            cout << endl;
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;
    }

    void userIssuedBooks()
    {
        vector<vector<string>> list_of_users;

        UserDatabase user(list_of_users);
        user.setListOfUsers();

        string fname = "bookList.csv";
        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);
        string searchKey;
        cin.ignore();
        cout << ">> Enter the ID of the user you want to check issued books: ";
        getline(cin, searchKey);
        cout << endl;

        if (user.userCheck(searchKey))
        {
            if (file.is_open())
            {
                int found = 0;

                cout << "Books issued to " << searchKey << ":" << endl;
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
                        found++;
                        Book book(row[1], row[0], row[2], row[3], row[4], row[5], row[6]);
                        book.show_duedate();
                    }
                }

                if (found == 0)
                    cout << "\n>> No issued books found!" << endl;
                cout << endl;
            }
            else
                cout << "\n>> Could not open the file\n"
                     << endl;
        }
    }

    void availabilityStatus()
    {
        string fname = "bookList.csv";

        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);
        string searchKey;

        cin.ignore();
        cout << ">> Enter the ISBN of the book you want to search: ";
        getline(cin, searchKey);
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

                string isbn;
                isbn = row[2];
                transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
                transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                int index_str;
                if (isbn == searchKey)
                {
                    found++;
                    Book book(row[1], row[0], row[2], row[3], row[4], row[5], row[6]);
                    int available = book.show_Availability();
                }
            }

            if (found == 0)
                cout << "\n>> No such book found!" << endl;
            cout << endl;
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;
    }

    void issue(int issuedBooks, string id, string role)
    {
        string fname = "bookList.csv";
        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);
        string searchKey;
        cin.ignore();
        cout << ">> Enter the ISBN of the book you want to issue: ";
        getline(cin, searchKey);
        if (file.is_open())
        {
            int found = 0;
            while (getline(file, line))
            {
                row.clear();

                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                string isbn;
                isbn = row[2];
                transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
                transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                int index_str;
                if (isbn == searchKey)
                {
                    found++;
                    Book book(row[1], row[0], row[2], row[3], row[4], row[5], row[6]);
                    int available = book.show_Availability();
                    if (available == 1)
                    {
                        int response;
                        cout << ">>Book is available for issuance!! Do you want to issue the book?\n"
                             << endl;
                        cout << "1. Yes" << endl;
                        cout << "2. No" << endl;
                        cout << endl;
                        cout << "Enter your choice: ";
                        cin >> response;
                        cout << endl;
                        switch (response)
                        {
                        case 1:
                            book.book_request(issuedBooks, id, role, isbn);
                            break;
                        case 2:
                            cout << ">> Book not issued" << endl;
                            break;

                        default:
                            cout << ">> Invalid input" << endl;
                            break;
                        }
                    }
                    else
                        cout << ">> Book is not available!\n"
                             << endl;
                }
            }

            if (found == 0)
                cout << "\n>> No such book found!" << endl;
            cout << endl;
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;
    }

    void returnBook(int issuedBooks, string id, string role)
    {
        string fname = "bookList.csv";
        vector<vector<string>> content;
        vector<string> row;
        string line, word;

        fstream file(fname, ios::in);
        string searchKey;
        cin.ignore();
        cout << ">> Enter the ISBN of the book you want to return: ";
        getline(cin, searchKey);
        if (file.is_open())
        {
            int found = 0;
            while (getline(file, line))
            {
                row.clear();

                stringstream str(line);
                while (getline(str, word, ','))
                    row.push_back(word);

                string isbn;
                isbn = row[2];
                transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
                transform(searchKey.begin(), searchKey.end(), searchKey.begin(), ::tolower);

                int index_str;
                if (isbn == searchKey)
                {
                    found++;
                    Book book(row[1], row[0], row[2], row[3], row[4], row[5], row[6]);
                    int available = book.show_Availability();

                    if (id == row[4])
                    {
                        int response;
                        cout << ">> Do you want to return the book?\n"
                             << endl;
                        cout << "1. Yes" << endl;
                        cout << "2. No" << endl;
                        cout << endl;
                        cout << "Enter your choice: ";
                        cin >> response;
                        cout << endl;
                        switch (response)
                        {
                        case 1:
                            book.book_return(id, role, isbn);
                            cout << " Book successfully returned!" << endl;
                            break;
                        case 2:
                            cout << ">> Book not returned!" << endl;
                            break;

                        default:
                            cout << ">> Invalid input" << endl;
                            break;
                        }
                    }
                    else
                    {
                        cout << "Book is not issued to you!" << endl;
                    }
                }
            }

            if (found == 0)
                cout << "\n>> No such book found!" << endl;
            cout << endl;
        }
        else
            cout << "\n>> Could not open the file\n"
                 << endl;
    }
};