#include <iostream>
#include <cmath> // Changed from math.h for C++ standards (contains pow, log10, etc.)
#include <stdexcept>
#include <sstream>
#include <string>
#include <iomanip> // For toString() formatting

#include "LoanCalculator.h"

using namespace std;

// Constructor: Initializes the double members correctly
LoanCalculator::LoanCalculator() :
  amountSet_(false),
  initialPayment_(0.0),
  interestSet_(false),
  paymentSet_(false),
  periodTotalSet_(false),
  periodElapsedSet_(false),
  openingFee_(0.0),
  openingPercent_(0.0)
{
  // Initialize double members to 0.0 for safety
  amount_ = 0.0;
  interest_ = 0.0;
  interestPeriodic_ = 0.0;
  payment_ = 0.0;
  periodTotal_ = 0;
  periodElapsed_ = 0;
}

//
// The actual calculation methods
//

/**
 * Loan balance after n payments have been made:
 * B_n = A*(1+i)^n - (P/i)*((1+i)^n - 1)
 *
 * NOTE: Return type changed from float to double.
 */
double LoanCalculator::calculateLoanBalance()
{
  if(!amountSet_ || !interestSet_ || !periodElapsedSet_ || !paymentSet_)
  {
    throw invalid_argument("Must set loan amount, interest, and elapsed period for this calculation" );
  }

  // Uses double member variables and double math (implicit from the pow function with double arguments)
  return (amount_*pow((1.0+interestPeriodic_), periodElapsed_)) -
           (payment_/interestPeriodic_)*(pow((1.0+interestPeriodic_), periodElapsed_)-1.0);
}

/**
 * Payment amount on a loan:
 * P = i*A / (1 - (1+i)^-N)
 *
 * NOTE: Return type changed from float to double.
 */
double LoanCalculator::calculatePayment()
{
  if(!amountSet_ || !interestSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set loan amount, interest, and total period for this calculation" );
  }

  // Changed internal variable to double
  double totalAmount = amount_ - initialPayment_;
  totalAmount = totalAmount + openingFee_ + (totalAmount * (openingPercent_/100.0));

  // Uses double member variables and double math (implicit from the pow function with double arguments)
  return (interestPeriodic_*totalAmount) /
           (1.0 - pow((1.0+interestPeriodic_), (-1.0*periodTotal_)));
}

/**
 * Number of payments on a loan:
 * N = -log(1-i*A/P) / log(1+i)
 * (You can use any logarithm base, as long as both logs use the same base.)
 *
 * NOTE: Return type changed from float to double.
 */
double LoanCalculator::calculateNumberPayments()
{
  if(!amountSet_ || !interestSet_ || !paymentSet_)
  {
    throw invalid_argument("Must set loan amount, interest, and payment for this calculation" );
  }

  // Uses double math functions (log10) and double member variables
  return (-1.0*log10(1.0-(interestPeriodic_*amount_/payment_))) /
           log10(1.0 + interestPeriodic_);
}

/**
 * Original loan amount:
 * A = (P/i)*(1 - (1+i)^-N)
 *
 * NOTE: Return type changed from float to double.
 */
double LoanCalculator::calculateLoanAmount()
{
  if(!paymentSet_ || !interestSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set payment, interest, and total period for this calculation" );
  }

  // Uses double math functions and double member variables
  return (payment_/interestPeriodic_) *
           (1.0 - pow((1.0+interestPeriodic_), (-1.0*periodTotal_)));
}

/**
 * Interest Rate:
 * i = (((1 + P/A)^(1/q) - 1 )^q - 1)  NOTICE: This is an approximate not an exact solution
 * where q = log(1+1/N) / log(2)
 *
 * NOTE: Return type changed from float to double.
 */
double LoanCalculator::calculateInterestRate()
{
  if(!amountSet_ || !paymentSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set amount, payment, and total period for this calculation" );
  }

  // Changed internal variables to double
  double q = log10(1.0 + 1.0/periodTotal_) / log10(2.0);
  double monthlyInterest = pow((pow((1.0 + payment_/amount_), 1.0/q) -1.0), q) -1.0;

  // Now returns a double
  return monthlyInterest*12.0*100.0;
}

/**
 * NOTE: Return type changed from float to double.
 */
double LoanCalculator::calculateEffectiveInterestRate()
{
  if(!amountSet_ || !periodTotalSet_)
  {
    throw invalid_argument("Must set amount and total period for this calculation" );
  }

  // Changed internal variables to double
  double payment = calculatePayment();
  double totalAmount = amount_ - initialPayment_;

  double q = log10(1.0 + 1.0/periodTotal_) / log10(2.0);
  double monthlyInterest = pow((pow((1.0 + payment/totalAmount), 1.0/q) -1.0), q) -1.0;

  // Now returns a double
  return monthlyInterest*12.0*100.0;
}

std::string LoanCalculator::toString()
{
  stringstream ss;
  ss << fixed << setprecision(2); // Added formatting for currency

  //ss << "LoanCalculator set values:\n";

  if(amountSet_)
  {
    ss << "Initial Amount:       " << amount_ << "\n";
  }

  if(initialPayment_ != 0.0)
  {
    ss << "Initial Payment:      " << initialPayment_ << "\n";
    ss << "Actual Loan Amount:   " << (amount_ - initialPayment_) << "\n";
  }

  if(interestSet_)
  {
    ss << "Yearly Interest:      " << interest_ << "%\n";
    //ss << "Yearly Interest:      " << interest_
    //   << "\nMonthly Interest:    " << interestPeriodic_ << "\n";
  }

  if(paymentSet_)
  {
    ss << "Monthly payment:      " << payment_ << "\n";
  }

  if(periodTotalSet_)
  {
    ss << "Loan Period:          " << periodTotal_ << " months\n";
  }

  if(periodElapsedSet_)
  {
    ss << "Elapsed Period:       " << periodElapsed_ << " months\n";
  }

  if(openingFee_ != 0.0)
  {
      ss << "Opening Fee:        " << openingFee_ << "\n";
  }

  if(openingPercent_ != 0.0)
  {
    ss << "Opening Fee %:        " << openingPercent_ << "% = "
         << (openingPercent_/100.0)*(amount_ - initialPayment_) << "\n";
  }

  return ss.str();
}