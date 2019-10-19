// loanAmortisation.cpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <math.h>

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
    interestRate = interestRate / 100;

	std::cout << "Loan Term (Years): ";
	std::cin >> loanTerm;

	// calc payments
	loanBalance = loanAmount;
	double simpleInterest = loanBalance * interestRate;
	double interestPerPeriod = interestRate / pmtPerAnnum;
	int totalPeriods = pmtPerAnnum * loanTerm;
	double monthlyPayment = simpleInterest / (pmtPerAnnum * (1 - pow(1 + interestPerPeriod, -totalPeriods)));
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
        totalInterest = totalInterest + periodInterest;
        totalPrincipal = totalPrincipal + periodPrincipal;

		std::cout << std::fixed << std::setprecision(2) << sep 
				  << std::setw(int_width) << (i + 1) << sep
				  << std::setw(dbl_width) << loanBalance << sep
				  << std::setw(dbl_width) << periodInterest << sep
				  << std::setw(dbl_width) << periodPrincipal << sep
				  << std::setw(dbl_width) << monthlyPayment << sep
				  << std::setw(dbl_width) << closeBalance << sep << "\n";

		// update loan balance
		loanBalance = loanBalance - periodPrincipal;

	}
    std::cout << line << "\n";
    
    std::cout << "Total Payments: " << (monthlyPayment * totalPeriods) << "\n";
    std::cout << "Total Interest: " << totalInterest << "\n";
    std::cout << "Total Principal: " << totalPrincipal << "\n";

	return 0;
}
