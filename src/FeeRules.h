/*
This is the header file for the fee rules it will hold definitions for the classes 
-FeeRuleBase
-OverdueFeeRule
Each class will hold its dedicated information to create objects for fees later in system
*/

#ifndef FEERULES_H
#define FEERULES_H

#include <string>  
#include <ctime> // for time_t Return/Checkout dates etc.

// Abstract base/parent class for the different fee rules
class FeeRuleBase {
public:
    //Constructor/Destructor
    FeeRuleBase() {}
    virtual ~FeeRuleBase() = default;

    // Pure virtual function to be implemented by derived classes.
    virtual double calculateFee(int daysOverdue) const = 0; // Calculate fee based on days overdue(to be overridden)

    //Pure virtual function to get rule name(to be overridden)
    virtual std::string getRuleName() const = 0;
};

//Derived class for overdue fee rules(parent: FeeRuleBase)
class OverdueFeeRule : public FeeRuleBase {
private:
    double lateDailyRate; // Fee charged per day overdue

public:
    OverdueFeeRule(double rate);

    // override functions (dynamic polymorphism)
    double calculateFee(int daysOverdue) const override;
    std::string getRuleName() const override;

    //Getter
    double getLateDailyRate() const;
};

#endif // FEERULES_H
