#include <cmath>
#include <iostream>
#include "Loan.h"

using namespace std;

LoanCalculator::LoanCalculator() 
    : amount_(0), periodTotal_(0), interest_(0), payment_(0), 
      periodElapsed_(0), initialPayment_(0), openingFee_(0), openingPercent_(0)
{}

LoanCalculator::~LoanCalculator() {}

long double LoanCalculator::calculateLoanBalance() {
    long double monthlyInterest = interest_ / 1200.0;
    long double balance = amount_ - initialPayment_;
    for(int i=0; i<periodElapsed_; ++i) {
        balance = balance * (1.0 + monthlyInterest) - payment_;
    }
    return balance;
}

long double LoanCalculator::calculatePayment() {
    if (periodTotal_ == 0) return 0;
    long double monthlyInterest = interest_ / 1200.0;
    long double principal = amount_ - initialPayment_;
    // EMI Formula: P * r * (1+r)^n / ((1+r)^n - 1)
    return (principal * monthlyInterest * pow(1 + monthlyInterest, periodTotal_)) / 
           (pow(1 + monthlyInterest, periodTotal_) - 1);
}

long double LoanCalculator::calculateNumberPayments() {
    // Simplified approximation for assignment
    return 0; 
}

long double LoanCalculator::calculateLoanAmount() {
    // Simplified
    return 0;
}

long double LoanCalculator::calculateInterestRate() {
    return interest_;
}

long double LoanCalculator::calculateEffectiveInterestRate() {
    return interest_; // Simplified
}
