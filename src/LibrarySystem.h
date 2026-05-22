/*
This is the header file for the library system
this class handles the main actions for the library
*/

#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <string>
#include <ctime>
#include <vector>
#include "LibraryInfo.h"
#include "FeeRules.h"

class LibrarySystem {
private:
std::vector<AccountBase*> accounts;
std::vector<BookRecord> bookRecords;
std::vector<LoanRecord> loanRecords;

FeeRuleBase* feeRule;

int nextAccountID;
int nextLoanID;
int nextBookCode;

int booksAddedCount;
int booksDeletedCount;
double totalFeesCollected;

public:
LibrarySystem(FeeRuleBase* rule);
~LibrarySystem();

// account stuff
int createStudentAccount(const std::string& fullName);
int createFacultyAccount(const std::string& fullName);
bool updateAccount(int accountID, const std::string& newName);
bool deleteAccount(int accountID);
AccountBase* findAccount(int accountID) const;
std::vector<AccountBase*> searchAccountsByName(const std::string& name) const;

// book stuff
int addBook(const std::string& title, const std::string& authorName);
bool updateBook(int bookCode, const std::string& newTitle, const std::string& newAuthorName);
bool deleteBook(int bookCode);
BookRecord* findBook(int bookCode);
const BookRecord* findBook(int bookCode) const;
std::vector<BookRecord*> searchBooksByTitle(const std::string& title);
std::vector<BookRecord*> searchBooksByAuthor(const std::string& authorName);

// loan stuff
int checkoutBook(int accountID, int bookCode, std::time_t checkoutDate, std::time_t dueDate);
bool returnBook(int loanID, std::time_t returnDate);
LoanRecord* findLoan(int loanID);
std::vector<LoanRecord*> getLoansForAccount(int accountID);

// fees
double calculateOverdueFee(int loanID) const;
double collectOverdueFee(int loanID);

// file loading
bool loadAccountsFromFile(const std::string& fileName);
bool loadBooksFromFile(const std::string& fileName);
bool loadLoansFromFile(const std::string& fileName);

// reports
int getTotalBookCount() const;
int getCheckedOutBookCount() const;
int getBooksAddedCount() const;
int getBooksDeletedCount() const;
double getTotalFeesCollected() const;

std::string generateAccountSummary(int accountID) const;
std::string generateBookSummary(int bookCode) const;
std::string generateLoanSummary(int loanID) const;
std::string generateLibraryReport() const;

std::string listAllAccounts() const;
std::string listAllBooks() const;
std::string listAllLoans() const;
};

#endif // LIBRARYSYSTEM_H