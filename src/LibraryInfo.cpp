/*
This is the implementation file for the library information
it holds the main data stuff for accounts, books, and loans
*/

#include "LibraryInfo.h"
#include <sstream>
#include <iomanip>

// account summary
std::string AccountBase::toSummaryString() const {
std::ostringstream out;
out << "Account ID= " << accountID
<< ", Name= " << fullName
<< ", Role= " << getRoleLabel()
<< ", Limit= " << getBorrowLimit()
<< ", Borrowed= " << borrowedCount;
return out.str();
}

// student functions
StudentAccount::StudentAccount(int id, const std::string& name)
: AccountBase(id, name) {}

std::string StudentAccount::getRoleLabel() const {
return "Student";
}

int StudentAccount::getBorrowLimit() const {
return 5;
}

// faculty functions
FacultyAccount::FacultyAccount(int id, const std::string& name)
: AccountBase(id, name) {}

std::string FacultyAccount::getRoleLabel() const {
return "Faculty";
}

int FacultyAccount::getBorrowLimit() const {
return 10;
}

// book functions
BookRecord::BookRecord(int code, const std::string& title, const std::string& author)
: bookCode(code), title(title), authorName(author), loanerStatus(false) {}

int BookRecord::getBookCode() const {
return bookCode;
}

const std::string& BookRecord::getTitle() const {
return title;
}

const std::string& BookRecord::getAuthorName() const {
return authorName;
}

void BookRecord::setTitle(const std::string& newTitle) {
title = newTitle;
}

void BookRecord::setAuthorName(const std::string& newAuthorName) {
authorName = newAuthorName;
}

bool BookRecord::getLoanerStatus() const {
return loanerStatus;
}

void BookRecord::setLoanerStatus(bool value) {
loanerStatus = value;
}

std::string BookRecord::toSummaryString() const {
std::ostringstream out;
out << "Book Code= " << bookCode
<< ", Title= " << title
<< ", Author= " << authorName
<< ", Loaned Out= " << (loanerStatus ? "Yes" : "No");
return out.str();
}

// loan functions
LoanRecord::LoanRecord(int id, int accountId, int bookCode,
std::time_t checkout, std::time_t due)
: loanID(id),
loanerAccountID(accountId),
bookCode(bookCode),
checkoutDate(checkout),
returnDate(0),
dueDate(due),
returnedFlag(false) {}

int LoanRecord :: getLoanId() const {
return loanID;
}

int LoanRecord :: getLoanerAccountId() const {
return loanerAccountID;
}

int LoanRecord :: getBookCode() const {
return bookCode;
}

std::time_t LoanRecord :: getCheckoutDate() const {
return checkoutDate;
}

std::time_t LoanRecord :: getDueDate() const {
return dueDate;
}

bool LoanRecord :: isReturned() const {
return returnedFlag;
}

std::time_t LoanRecord :: getReturnDate() const {
return returnDate;
}

void LoanRecord :: markReturned(std::time_t returnedAt) {
returnDate = returnedAt;
returnedFlag = true;
}

bool LoanRecord :: isOverdue() const {
if(!returnedFlag) {
return false;
}
return returnDate > dueDate;
}

int LoanRecord::daysOverdue() const {
if (!returnedFlag)
return 0;

double diff = std::difftime(returnDate, dueDate);
int days = static_cast<int>(diff / 86400);

return (days > 0 ? days : 0);
}

std::string LoanRecord::toSummaryString() const {
std::ostringstream out;
out << "Loan ID= " << loanID
<< ", Account ID= " << loanerAccountID
<< ", Book Code= " << bookCode
<< ", Checkout= " << checkoutDate
<< ", Due= " << dueDate
<< ", Returned= " << (returnedFlag ? "Yes" : "No");

if (returnedFlag) {
out << ", Return Date= " << returnDate
<< ", Days Late= " << daysOverdue();
}

return out.str();
}