# Library Management System

The folder contains the source code for the library management system in C++ using Object Oriented Programming. The 'Header' folder contains the header files 
for the code.

'libraryManagementSystem.cpp' is the main file containing the main code.

'bookList.csv' is the file containing information about the books in the below given format:
(Book Author, Book Name, Book ISBN, Book Publisher, Issued To, Issued Date, Due Date)


'userList.csv' is the file containing information about the books in the below given format:
(User Name, User Id, User Pass, User Role, User Fine Amount, User Issued Book Count, *Book ISBN, *Issue Date, *Due Date)
<br>
\* signfies that the book information will be available only for the number of book count.

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

-----------------------------------------------------------------------------------------------------------
    Sample user are:

    1. Name- Librarian
        Id - librarian
        Pass- 123
        Role- librarian

    2. Name- Student1
        Id - student1
        Pass- 123
        Role- student

    3. Name- Student2
        Id - student2
        Pass- 123
        Role- student

    4. Name- Professor1
        Id - professor1
        Pass- 123
        Role- professor
-----------------------------------------------------------------------------------------------------------
    Sample Books are:

    1. Name- Junior Level Books
        Author - Amit Garg
        ISBN- 978-93-5019-561-1
        Publication- Reader's Zone

    2. Name- Publish News Letter
        Author - Amit Garg
        ISBN- 978-43
        Publication- MCA Department

    3. Name- Client Server Computing
        Author - Lalit Kumar
        ISBN- 978-93-8067-432-1
        Publication- Sun India Publications

    4. Name- Data Structure Using C
        Author - Sharad Kumar Verma
        ISBN- 978-93-5163-389-1
        Publication- Thakur Publications
    
    5. Name- Client Server Computing
        Author - Sharad Kumar Verma
        ISBN- 978-93-8067-432-2
        Publication- Sun India Publications
