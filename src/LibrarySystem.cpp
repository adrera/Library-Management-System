/*
This is the implementation file for the library system
this manages the main library actions and keeps the records together
*/

#include "LibrarySystem.h"
#include "Maintenance.h"
#include "SystemErrors.h"
#include <sstream>
#include <fstream>

// Librarysystem implementation

LibrarySystem :: LibrarySystem(FeeRuleBase* rule)
: feeRule(rule),
nextAccountID(1),
nextLoanID(5001),
nextBookCode(1001),
booksAddedCount(0),
booksDeletedCount(0),
totalFeesCollected(0.0) {}

LibrarySystem::~LibrarySystem() {
for (AccountBase* acc : accounts) {
delete acc;
}
accounts.clear();
}

// account stuff
int LibrarySystem :: createStudentAccount(const std::string& fullName) {
StudentAccount* acc = new StudentAccount(nextAccountID, fullName);
accounts.push_back(acc);
return nextAccountID++;
}

int LibrarySystem :: createFacultyAccount(const std::string& fullName) {
FacultyAccount* acc = new FacultyAccount(nextAccountID, fullName);
accounts.push_back(acc);
return nextAccountID++;
}

bool LibrarySystem :: updateAccount(int accountID, const std::string& newName) {
AccountBase* acc = findAccount(accountID);
if (!acc)
throw MessageError("Account not found.");

acc->setFullName(newName);
return true;
}

bool LibrarySystem :: deleteAccount(int accountID) {
for (auto it = accounts.begin(); it != accounts.end(); ++it) {
if ((*it)->getAccountID() == accountID) {
if ((*it)->getBorrowedCount() > 0)
throw MessageError("Cannot delete account with borrowed books.");

delete *it;
accounts.erase(it);
return true;
}
}
throw MessageError("Account not found.");
}

AccountBase* LibrarySystem :: findAccount(int accountID) const {
for (AccountBase* acc : accounts) {
if (acc->getAccountID() == accountID)
return acc;
}
return nullptr;
}

std::vector<AccountBase*> LibrarySystem :: searchAccountsByName(const std::string& name) const {
std::vector<AccountBase*> result;
for (AccountBase* acc : accounts) {
if (acc->getFullName().find(name) != std::string::npos)
result.push_back(acc);
}
return result;
}

// book stuff
int LibrarySystem :: addBook(const std::string& title, const std::string& authorName) {
bookRecords.emplace_back(nextBookCode, title, authorName);
booksAddedCount++;
return nextBookCode++;
}

bool LibrarySystem :: updateBook(int bookCode, const std::string& newTitle, const std::string& newAuthorName) {
BookRecord* book = findBook(bookCode);
if (!book)
throw MessageError("Book not found.");

book->setTitle(newTitle);
book->setAuthorName(newAuthorName);
return true;
}

bool LibrarySystem :: deleteBook(int bookCode) {
for (auto it = bookRecords.begin(); it != bookRecords.end(); ++it) {
if (it->getBookCode() == bookCode) {
if (it->getLoanerStatus())
throw MessageError("Cannot delete a book that is checked out.");

bookRecords.erase(it);
booksDeletedCount++;
return true;
}
}
throw MessageError("Book not found.");
}

BookRecord* LibrarySystem :: findBook(int bookCode) {
for (auto& book : bookRecords) {
if (book.getBookCode() == bookCode)
return &book;
}
return nullptr;
}

const BookRecord* LibrarySystem :: findBook(int bookCode) const {
for (const auto& book : bookRecords) {
if (book.getBookCode() == bookCode)
return &book;
}
return nullptr;
}

std::vector<BookRecord*> LibrarySystem :: searchBooksByTitle(const std::string& title) {
std::vector<BookRecord*> result;
for (auto& book : bookRecords) {
if (book.getTitle().find(title) != std::string::npos)
result.push_back(&book);
}
return result;
}

std::vector<BookRecord*> LibrarySystem :: searchBooksByAuthor(const std::string& authorName) {
std::vector<BookRecord*> result;
for (auto& book : bookRecords) {
if (book.getAuthorName().find(authorName) != std::string::npos)
result.push_back(&book);
}
return result;
}

// loan stuff
int LibrarySystem :: checkoutBook(int accountID, int bookCode,
std::time_t checkoutDate, std::time_t dueDate)
{
AccountBase* acc = findAccount(accountID);
if (!acc)
throw MessageError("Account not found.");

BookRecord* book = findBook(bookCode);
if (!book)
throw MessageError("Book not found.");

if (book->getLoanerStatus())
throw MessageError("Book is already loaned out.");

if (acc->getBorrowedCount() >= acc->getBorrowLimit())
throw MessageError("Borrow limit reached.");

loanRecords.emplace_back(nextLoanID, accountID, bookCode, checkoutDate, dueDate);

book->setLoanerStatus(true);
acc->incrementBorrowed();

return nextLoanID++;
}

LoanRecord* LibrarySystem :: findLoan(int loanID) {
for (auto& loan : loanRecords) {
if (loan.getLoanId() == loanID)
return &loan;
}
return nullptr;
}

std::vector<LoanRecord*> LibrarySystem :: getLoansForAccount(int accountID) {
std::vector<LoanRecord*> result;
for (auto& loan : loanRecords) {
if (loan.getLoanerAccountId() == accountID)
result.push_back(&loan);
}
return result;
}

bool LibrarySystem :: returnBook(int loanID, std::time_t returnDate) {
LoanRecord* loan = findLoan(loanID);
if (!loan)
throw MessageError("Loan not found.");

if (loan->isReturned())
throw MessageError("Book already returned.");

BookRecord* book = findBook(loan->getBookCode());
if (!book)
throw MessageError("Book record missing.");

AccountBase* acc = findAccount(loan->getLoanerAccountId());
if (!acc)
throw MessageError("Account record missing.");

loan->markReturned(returnDate);
book->setLoanerStatus(false);
acc->decrementBorrowed();

return true;
}

// fees
double LibrarySystem :: calculateOverdueFee(int loanID) const {
for (const auto& loan : loanRecords) {
if (loan.getLoanId() == loanID)
return feeRule->calculateFee(loan.daysOverdue());
}
throw MessageError("Loan not found.");
}

double LibrarySystem :: collectOverdueFee(int loanID) {
double fee = calculateOverdueFee(loanID);
totalFeesCollected += fee;
return fee;
}

// file loading
bool LibrarySystem :: loadAccountsFromFile(const std::string& fileName) {
std::ifstream file(fileName);
if (!file)
throw MessageError("Could not open accounts file.");

std::string type;
std::string name;

while (file >> type) {
file.ignore();
std::getline(file, name);

if (type == "Student") {
createStudentAccount(name);
}
else if (type == "Faculty") {
createFacultyAccount(name);
}
}

return true;
}

bool LibrarySystem :: loadBooksFromFile(const std::string& fileName) {
std::ifstream file(fileName);
if (!file)
throw MessageError("Could not open books file.");

std::string title;
std::string author;

while (std::getline(file, title, '|') && std::getline(file, author)) {
addBook(title, author);
}

return true;
}

bool LibrarySystem :: loadLoansFromFile(const std::string& fileName) {
std::ifstream file(fileName);
if (!file)
throw MessageError("Could not open loans file.");

int accountID;
int bookCode;
std::string checkoutStr;
std::string dueStr;

while (file >> accountID >> bookCode >> checkoutStr >> dueStr) {
std::time_t checkout = parseDate(checkoutStr);
std::time_t due = parseDate(dueStr);

checkoutBook(accountID, bookCode, checkout, due);
}

return true;
}

// report helpers
int LibrarySystem :: getTotalBookCount() const {
return static_cast<int>(bookRecords.size());
}

int LibrarySystem :: getCheckedOutBookCount() const {
int count = 0;
for (const auto& book : bookRecords) {
if (book.getLoanerStatus())
count++;
}
return count;
}

int LibrarySystem :: getBooksAddedCount() const {
return booksAddedCount;
}

int LibrarySystem :: getBooksDeletedCount() const {
return booksDeletedCount;
}

double LibrarySystem :: getTotalFeesCollected() const {
return totalFeesCollected;
}

// summaries
std::string LibrarySystem::generateAccountSummary(int accountID) const {
AccountBase* acc = findAccount(accountID);
if (!acc)
throw MessageError("Account not found.");

return acc->toSummaryString();
}

std::string LibrarySystem::generateBookSummary(int bookCode) const {
const BookRecord* book = findBook(bookCode);
if (!book)
throw MessageError("Book not found.");

return book->toSummaryString();
}

std::string LibrarySystem::generateLoanSummary(int loanID) const {
for (const auto& loan : loanRecords) {
if (loan.getLoanId() == loanID)
return loan.toSummaryString();
}
throw MessageError("Loan not found.");
}

std::string LibrarySystem::generateLibraryReport() const {
std::ostringstream out;
out << "Library Report\n";
out << "Total accounts: " << accounts.size() << "\n";
out << "Total books: " << getTotalBookCount() << "\n";
out << "Books checked out: " << getCheckedOutBookCount() << "\n";
out << "Books added: " << booksAddedCount << "\n";
out << "Books deleted: " << booksDeletedCount << "\n";
out << "Total loans: " << loanRecords.size() << "\n";
out << "Fees collected: $" << totalFeesCollected << "\n";

int lateCount = 0;
for (const auto& loan : loanRecords) {
if (loan.daysOverdue() > 0)
lateCount++;
}

out << "Late returns: " << lateCount << "\n";
return out.str();
}

std::string LibrarySystem::listAllAccounts() const {
std::ostringstream out;
for (const auto& acc : accounts) {
out << acc->toSummaryString() << "\n";
}
return out.str();
}

std::string LibrarySystem::listAllBooks() const {
std::ostringstream out;
for (const auto& book : bookRecords) {
out << book.toSummaryString() << "\n";
}
return out.str();
}

std::string LibrarySystem::listAllLoans() const {
std::ostringstream out;
for (const auto& loan : loanRecords) {
out << loan.toSummaryString() << "\n";
}
return out.str();
}

// LibrarySystem.cpp