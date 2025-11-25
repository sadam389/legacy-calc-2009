#include <gtest/gtest.h>
#include "../src/Loan.h"
#include <cmath>

// Test 1: Standard EMI Calculation
TEST(LoanTest, CalculateStandardEMI) {
    LoanCalculator loan;
    loan.setAmount(100000);
    loan.setInterest(5.5);
    loan.setPeriodTotal(120);
    loan.setInitialPayment(0);

    double emi = loan.calculatePayment();
    
    EXPECT_NEAR(emi, 1085.26, 0.1);
}

// Test 2: Large Tenure (Stress Test)
TEST(LoanTest, LargeTenureLoan) {
    LoanCalculator loan;
    loan.setAmount(500000);
    loan.setInterest(3.5);
    loan.setPeriodTotal(600); // 50 years
    loan.setInitialPayment(0);

    double emi = loan.calculatePayment();
    
    // UPDATED: Correct mathematical result for 3.5% over 50 years is ~1766.00
    EXPECT_NEAR(emi, 1766.00, 0.1);
}

// Test 3: Zero Period (Invalid Input)
TEST(LoanTest, ZeroPeriodHandle) {
    LoanCalculator loan;
    loan.setAmount(100000);
    loan.setInterest(5.5);
    loan.setPeriodTotal(0); 

    double emi = loan.calculatePayment();
    
    EXPECT_EQ(emi, 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
