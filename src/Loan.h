/**
 * @file Loan.h
 * @brief Header file for the LoanCalculator class.
 *
 * This file contains the definition of the LoanCalculator class,
 * which performs various financial calculations such as EMI,
 * loan balance, and interest rates.
 */

#ifndef LOAN_H
#define LOAN_H

/**
 * @class LoanCalculator
 * @brief A class to handle loan and EMI calculations.
 *
 * The LoanCalculator class provides methods to calculate monthly payments,
 * total interest, and effective interest rates based on loan amount,
 * tenure, and interest rate.
 */
class LoanCalculator {
public:
    /**
     * @brief Constructor for LoanCalculator.
     * Initializes all member variables to zero.
     */
    LoanCalculator();

    /**
     * @brief Destructor for LoanCalculator.
     */
    ~LoanCalculator();

    /**
     * @brief Sets the loan amount.
     * @param amount The principal loan amount.
     */
    void setAmount(long double amount) { amount_ = amount; }

    /**
     * @brief Sets the total loan period.
     * @param period The total number of months.
     */
    void setPeriodTotal(int period) { periodTotal_ = period; }

    /**
     * @brief Sets the annual interest rate.
     * @param interest The yearly interest rate in percent.
     */
    void setInterest(long double interest) { interest_ = interest; }

    /**
     * @brief Sets the monthly payment amount.
     * @param payment The monthly EMI amount.
     */
    void setPayment(long double payment) { payment_ = payment; }

    /**
     * @brief Sets the elapsed period for balance calculation.
     * @param period The number of months passed.
     */
    void setPeriodElapsed(int period) { periodElapsed_ = period; }

    /**
     * @brief Sets the initial down payment.
     * @param payment The initial payment amount.
     */
    void setInitialPayment(long double payment) { initialPayment_ = payment; }

    /**
     * @brief Sets the opening fee.
     * @param fee The flat opening fee amount.
     */
    void setOpeningFee(long double fee) { openingFee_ = fee; }

    /**
     * @brief Sets the opening fee percentage.
     * @param percent The percentage of the loan amount charged as a fee.
     */
    void setOpeningPercent(long double percent) { openingPercent_ = percent; }

    // Getters
    long double getPeriodTotal() { return periodTotal_; }
    long double getOpeningFee() { return openingFee_; }
    long double getOpeningPercent() { return openingPercent_; }

    /**
     * @brief Calculates the remaining loan balance after a specific period.
     * @return The remaining balance as a long double.
     */
    long double calculateLoanBalance();

    /**
     * @brief Calculates the monthly EMI payment.
     * * Uses the standard EMI formula: P * r * (1+r)^n / ((1+r)^n - 1)
     * * @return The monthly payment amount.
     */
    long double calculatePayment();

    /**
     * @brief Calculates the number of payments required (Approximation).
     * @return The number of months.
     */
    long double calculateNumberPayments();

    /**
     * @brief Calculates the initial loan amount based on payment and rate.
     * @return The principal loan amount.
     */
    long double calculateLoanAmount();

    /**
     * @brief Returns the annual interest rate.
     * @return The interest rate percentage.
     */
    long double calculateInterestRate();

    /**
     * @brief Calculates the effective interest rate including fees.
     * @return The effective annual interest rate.
     */
    long double calculateEffectiveInterestRate();

private:
    long double amount_;        ///< Principal loan amount
    int periodTotal_;           ///< Total tenure in months
    long double interest_;      ///< Annual interest rate
    long double payment_;       ///< Monthly payment amount
    int periodElapsed_;         ///< Months elapsed for balance calc
    long double initialPayment_;///< Down payment
    long double openingFee_;    ///< Flat opening fee
    long double openingPercent_;///< Opening fee percentage
};

#endif