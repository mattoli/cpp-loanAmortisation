// loanAmortisation.cpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <math.h>

// calculate payment per period
// i = total simple interest | p = payments per annum
// r = interest rate per period | n = total number of periods
double calcPayment(const double& i, const int& p, const double& r, const int& n) {
    double pmt;
    pmt = i / (p * (1 - pow(1 + r, -n)));
    return pmt;
}

// main function
int main()
{
	// init base variables
	double loanAmount, interestRate, loanBalance, totalInterest, totalPrincipal;
	int loanTerm, pmtPerAnnum = 12;

	// get user input
	std::cout << "Loan Amount: ";
	std::cin >> loanAmount;

	std::cout << "Interest Rate (%): ";
	std::cin >> interestRate;
    interestRate /= 100;        // interest rate to actual value (i.e. 6% to 0.06)

	std::cout << "Loan Term (Years): ";
	std::cin >> loanTerm;

	// calc payments
	loanBalance = loanAmount;                                   // set starting loan balance as loan amount
	double simpleInterest = loanBalance * interestRate;         // calculate simple interest for 1st year
	double interestPerPeriod = interestRate / pmtPerAnnum;      // rate per period (month) from annual interest rate
	int totalPeriods = pmtPerAnnum * loanTerm;                  // calc total periods (months)
    double monthlyPayment = calcPayment(simpleInterest, pmtPerAnnum, interestPerPeriod, totalPeriods);      // calculate monthly P&I repayment
	std::cout << "Monthly Payment: " << monthlyPayment << "\n";

	// init table helpers
	const int int_width = 10;
	const int dbl_width = 15;
	const int num_flds = 6;
	const std::string sep = " |";
	const int total_width = int_width + dbl_width * 5 + sep.size() * num_flds;
	const std::string line = sep + std::string(total_width - 1, '-') + '|';
	
	// init table headings
	std::cout << line << "\n";
	std::cout << sep << std::setw(int_width) << " Month" << sep 
			  << std::setw(dbl_width) << " OpenBal" << sep 
			  << std::setw(dbl_width) << " Interest" << sep 
			  << std::setw(dbl_width) << " Principal" << sep 
			  << std::setw(dbl_width) << " TotPayment" << sep 
			  << std::setw(dbl_width) << " CloseBal" << sep << "\n";
	std::cout << line << "\n";

    // iter through periods, calculate & print out
	for (int i = 0; i < totalPeriods; i++) {
		double periodInterest = interestPerPeriod * loanBalance;
		double periodPrincipal = monthlyPayment - periodInterest;
		double closeBalance = loanBalance - periodPrincipal;
        totalInterest += periodInterest;
        totalPrincipal += periodPrincipal;

		std::cout << std::fixed << std::setprecision(2) << sep 
				  << std::setw(int_width) << (i + 1) << sep
				  << std::setw(dbl_width) << loanBalance << sep
				  << std::setw(dbl_width) << periodInterest << sep
				  << std::setw(dbl_width) << periodPrincipal << sep
				  << std::setw(dbl_width) << monthlyPayment << sep
				  << std::setw(dbl_width) << closeBalance << sep << "\n";

		// update loan balance
		loanBalance -= periodPrincipal;

	}
    std::cout << line << "\n";

    std::cout << "Total Payments: " << (monthlyPayment * totalPeriods) << "\n";
    std::cout << "Total Interest: " << totalInterest << "\n";
    std::cout << "Total Principal: " << totalPrincipal << "\n";

	return 0;
}
