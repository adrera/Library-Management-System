/*
This is the header file for the Library Information
holds all the main classes for accounts, books, and loans
*/

#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <string>
#include <ctime>

// base class for all accounts
class AccountBase {
protected:
std::string fullName;
int accountID;
int borrowedCount;

public:
AccountBase(int id, const std::string& name)
: accountID(id), fullName(name), borrowedCount(0) {}
virtual ~AccountBase() = default;

int getAccountID() const {
return accountID;
}

std::string getFullName() const {
return fullName;
}

int getBorrowedCount() const {
return borrowedCount;
}

// lets us update name later if needed
void setFullName(const std::string& name) {
fullName = name;
}

// tracking books
void incrementBorrowed() {
borrowedCount++;
}

void decrementBorrowed() {
if (borrowedCount > 0) borrowedCount--;
}

virtual std::string getRoleLabel() const = 0;
virtual int getBorrowLimit() const = 0;

// quick summary string
virtual std::string toSummaryString() const;
};

// student account
class StudentAccount : public AccountBase {
public:
StudentAccount(int id, const std::string& name);

std::string getRoleLabel() const override;
int getBorrowLimit() const override;
};

// faculty account
class FacultyAccount : public AccountBase {
public:
FacultyAccount(int id, const std::string& name);

std::string getRoleLabel() const override;
int getBorrowLimit() const override;
};

// book info class
class BookRecord {
private:
std::string title;
std::string authorName;
int bookCode;
bool loanerStatus;

public:
BookRecord(int code, const std::string& title, const std::string& author);

int getBookCode() const;
const std::string& getTitle() const;
const std::string& getAuthorName() const;

// for updating book info later
void setTitle(const std::string& newTitle);
void setAuthorName(const std::string& newAuthorName);

bool getLoanerStatus() const;
void setLoanerStatus(bool value);

std::string toSummaryString() const;
};

// loan record
class LoanRecord {
private:
int loanID;
int loanerAccountID;
int bookCode;

std::time_t checkoutDate;
std::time_t returnDate;
std::time_t dueDate;
bool returnedFlag;

public:
LoanRecord(int id, int accountId, int bookCode, std::time_t checkout, std::time_t due);

int getLoanId() const;
int getLoanerAccountId() const;
int getBookCode() const;
std::time_t getCheckoutDate() const;
std::time_t getDueDate() const;
bool isReturned() const;
std::time_t getReturnDate() const;

void markReturned(std::time_t returnedAt);

bool isOverdue() const;
int daysOverdue() const;

std::string toSummaryString() const;
};

#endif // LIBRARYINFO_H