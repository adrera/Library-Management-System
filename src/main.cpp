// This is the main file for the library system
// This system will test the library system by
// creating accounts
// adding books
// checking out and returning books
// calculating fees
// generating reports
// It will also demonstrate error handling through the MessageError class when invalid operations are attempted.


#include <iostream>
#include <ctime>
#include "LibrarySystem.h"
#include "FeeRules.h"
#include "SystemErrors.h"
#include "Maintenance.h"

int main() {
try {
OverdueFeeRule feeRule(1.0);
LibrarySystem library(&feeRule);

// loading starting data from files
library.loadAccountsFromFile("accounts.txt");
library.loadBooksFromFile("books.txt");
library.loadLoansFromFile("loans.txt");

std::cout << "Accounts Loaded:\n";
std::cout << library.listAllAccounts() << "\n";

std::cout << "Books Loaded:\n";
std::cout << library.listAllBooks() << "\n";

std::cout << "Loans Loaded:\n";
std::cout << library.listAllLoans() << "\n";

// returning two books late to test fee stuff
std::time_t returnedLate1 = parseDate("05/12/2026");
std::time_t returnedLate2 = parseDate("05/10/2026");

library.returnBook(5001, returnedLate1);
library.returnBook(5002, returnedLate2);

double fee1 = library.collectOverdueFee(5001);
double fee2 = library.collectOverdueFee(5002);

std::cout << "Fee for loan 5001: $" << fee1 << "\n";
std::cout << "Fee for loan 5002: $" << fee2 << "\n\n";

// testing update and delete features
library.updateAccount(3, "Mohamed Ali Updated");
library.updateBook(1003, "Bridgerton Updated", "Julia Quinn");

// delete works because this book was returned first
library.deleteBook(1002);

std::cout << "After Updates:\n";
std::cout << library.listAllAccounts() << "\n";
std::cout << library.listAllBooks() << "\n";

std::cout << "Final Report:\n";
std::cout << library.generateLibraryReport() << "\n";
}
catch (const MessageError& e) {
std::cout << "Error: " << e.getMessage() << "\n";
}

return 0;

}

