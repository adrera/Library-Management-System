/*
This is the implementation file for the fee rules it will hold implemented fuunctions for defined classe
this is fee rule functions with calculations
*/

#include "FeeRules.h"
#include <sstream>

// OverdueFeeRule class implementation
OverdueFeeRule :: OverdueFeeRule(double rate)
    : lateDailyRate(rate) {}

    //Calculating fee based on days overdue and the daily rate
    double OverdueFeeRule :: calculateFee(int daysOverdue) const {
        if (daysOverdue > 0) {
            return daysOverdue * lateDailyRate;
        }
        return 0.0; //0 if no days overdue
    }

    //Getting the name of the rule/ returning message
    std::string OverdueFeeRule :: getRuleName() const {
        std::ostringstream out;
        out << "Overdue Day Rate:$ "
            << lateDailyRate;
            return out.str();
    }

    //Getting  the late daily rate
    double OverdueFeeRule :: getLateDailyRate() const {
        return lateDailyRate;
    }

    //FeeRules.cpp