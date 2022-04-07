# Library Management System

The folder contains the source code for the library management system in C++ using Object Oriented Programming. The 'Header' folder contains the header files 
for the code.

'libraryManagementSystem.cpp' is the main file containing the main code.

'bookList.csv' is the file containing information about the books in the below given format:
(Book Author, Book Name, Book ISBN, Book Publisher, Issued To, Issued Date, Due Date)


'userList.csv' is the file containing information about the books in the below given format:
(User Name, User Id, User Pass, User Role, User Fine Amount, User Issued Book Count, *Book ISBN, *Issue Date, *Due Date)
* signfies that the book information will be available only for the number of book count.

Since the file is in csv format which is comma(,) separated, having comma in user input will break down the code working. So please avoid writing comma in user input.

Header files are: 
- book.h (containing class Book and its functions)
- user.h (containing class User and its child classes Student, Professor and Librarian)
- student.h (containing funtions related to Student Portal)
- professor.h (containing funtions related to Professor Portal)
- librarian.h (containing funtions related to Librarian Portal)
- dateFunctions.h (containing Date class and functions related to Date handling)
- userDatabase.h (containing userDatabase class and functions related to userDatabase handling)
- bookDatabase.h (containing bookDatabase class and functions related to bookDatabase handling)

On the code run, the initiateLibrarian() funtion in the main file checks for the existence of the librarian and if doesn't exist then creates 
a librarian account with the default username, id and password.

To run the code:
- Open terminal.
- Change directory to the folder '200554_LibManagementSystem'
- Run 'g++ -o libraryManagementSystem libraryManagementSystem.cpp & ./libraryManagementSystem'
- The program will run now.

