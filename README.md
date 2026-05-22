### Ayatt Drera
### Library System


##  User Manual — Library Management System

###  Overview
The Library Management System is a fully object‑oriented C++ program designed to simulate the core operations of a small library. It automatically manages accounts, books, loans, overdue fees, and summary reporting. The system demonstrates inheritance, polymorphism, abstraction, and multi‑file program design.

This manual explains how the system works, how to interact with it, and what each component does.



##  System Components

### **1. Accounts**
The system supports two types of accounts:

- **StudentAccount**
- **FacultyAccount**

Both inherit from the abstract base class **AccountBase**, which provides:
- Account ID  
- Full name  
- Borrowed book count  
- Borrowing limits (polymorphic)  
- Summary string generation  

Faculty accounts typically have higher borrowing limits than student accounts.



### **2. Book Records**
Each book in the system is represented by a **BookRecord**, which stores:
- Title  
- Author name  
- Unique book code  
- Loan status (available or checked out)  

Books can be searched by title or author.



### **3. Loan Records**
A **LoanRecord** tracks:
- Loan ID  
- Account ID of the borrower  
- Book code  
- Checkout date  
- Due date  
- Return date  
- Overdue status  

Loan records allow the system to determine:
- Whether a book is returned  
- Whether it is overdue  
- How many days overdue it is  



### **4. Fee Rules**
The system uses a polymorphic fee rule structure:

- **FeeRuleBase** (abstract)
- **OverdueFeeRule** (implements daily overdue fees)

This allows future expansion (e.g., flat fees, tiered fees, faculty‑only rules).



### **5. Error Handling**
The system uses a lightweight error class:

- **MessageError**

This class stores an error message and can be thrown or returned when invalid operations occur



### **6. LibrarySystem Controller**
This is the central class that manages everything:

- Creates accounts  
- Adds books  
- Checks out books  
- Returns books  
- Calculates overdue fees  
- Generates summaries  
- Searches for books  
- Tracks all loan records  

It is the “brain” of the entire program.



##  How the Program Runs

When executed, the program performs the following steps automatically:

1. **Creates a fee rule** (e.g., daily overdue rate).  
2. **Initializes the LibrarySystem** with that rule.  
3. **Creates student and faculty accounts.**  
4. **Adds books** to the library.  
5. **Checks out books** to accounts.  
6. **Returns books** (some may be overdue).  
7. **Calculates overdue fees** using the fee rule.  
8. **Prints summaries** for:
   - Accounts  
   - Books  
   - Loans  

No user input is required — the system demonstrates its full functionality automatically.

## Initial Data Files

The program uses 3 text files to load starting data into the system.

### accounts.txt

Format:

`txt
Student Full Name
Faculty Full Name


## UMLs

### Account/ Account info
classDiagram
    class AccountBase {
        - string fullName
        - int accountID
        - int borrowedCount
        + getAccountID()
        + getFullName()
        + setFullName()
        + getBorrowedCount()
        + incrementBorrowed()
        + decrementBorrowed()
        + getRoleLabel()
        + getBorrowLimit()
    }

    class StudentAccount
    class FacultyAccount

    AccountBase <|-- StudentAccount
    AccountBase <|-- FacultyAccount

### BookRecord
classDiagram
    class BookRecord {
        - string title
        - string authorName
        - int bookCode
        - bool loanerStatus
        + getBookCode()
        + getTitle()
        + setTitle()
        + setAuthorName()
        + getLoanerStatus()
        + setLoanerStatus()
    }

### LoanRecord
classDiagram
    class LoanRecord {
        - int loanID
        - int loanerAccountID
        - int bookCode
        - time_t checkoutDate
        - time_t returnDate
        - time_t dueDate
        - bool returnedFlag
        + getLoanId()
        + markReturned()
        + isOverdue()
        + daysOverdue()
    }

### FeeRules
classDiagram
    class FeeRuleBase {
        + calculateFee()
    }

    class OverdueFeeRule {
        - double lateDailyRate
        + calculateFee()
    }

    FeeRuleBase <|-- OverdueFeeRule


### LibrarySystem
classDiagram
    class LibrarySystem {
        - vector accounts
        - vector bookRecords
        - vector loanRecords
        - feeRule
        + createStudentAccount()
        + createFacultyAccount()
        + updateAccount()
        + deleteAccount()
        + addBook()
        + updateBook()
        + deleteBook()
        + checkoutBook()
        + returnBook()
        + calculateOverdueFee()
        + loadAccountsFromFile()
        + loadBooksFromFile()
        + loadLoansFromFile()
        + generateLibraryReport()
    }


### If Encounter Errors While Running

In terminal collect all files and make sure all .cpp files are running together
paste
cl /EHsc main.cpp LibrarySystem.cpp LibraryInfo.cpp FeeRules.cpp Maintenance.cpp /Fe:main.exe

run using .\main.exe to test



##  How to Compile

g++ -std=c++17 -Wall -Wextra -o library main.cpp LibrarySystem.cpp LibraryInfo.cpp FeeRules.cpp Maintenance.cpp

OR Windows:

cl /EHsc main.cpp LibrarySystem.cpp LibraryInfo.cpp FeeRules.cpp Maintenance.cpp /Fe:main.exe







