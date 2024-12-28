#include <stdio.h>
#include <string.h>

// Struct to store investment options
typedef struct {
    char option[100];
    char description[300];
} InvestmentOption;

// Array to store investment options
InvestmentOption shortTermLowRisk[] = {
    {"Fixed Deposits", "Guaranteed returns, no risk."},
    {"Savings Account", "Easy access to funds."}
};
InvestmentOption shortTermModerateRisk[] = {
    {"Debt Mutual Funds", "Lower risk than equities with better returns than FDs."},
    {"Recurring Deposits", "Steady growth with moderate returns."}
};
InvestmentOption shortTermHighRisk[] = {
    {"Stock Trading", "High risk but potential for quick gains."},
    {"Gold ETFs", "Hedge against inflation with moderate growth potential."}
};
InvestmentOption longTermLowRisk[] = {
    {"Government Bonds", "Safe with steady returns."},
    {"Public Provident Fund (PPF)", "Tax-saving long-term plan."}
};
InvestmentOption longTermModerateRisk[] = {
    {"Balanced Mutual Funds", "Diversified investments with moderate risk."},
    {"National Pension Scheme (NPS)", "Ideal for retirement planning."}
};
InvestmentOption longTermHighRisk[] = {
    {"Equity Mutual Funds", "High returns with long-term growth."},
    {"Direct Stock Investment", "High risk, but significant growth potential over time."}
};

// Function to convert salary to INR
double convertToINR(double salary, char currency[]) {
    if (strcmp(currency, "USD") == 0) {
        return salary * 82.5; // Example: 1 USD = 82.5 INR
    } else if (strcmp(currency, "EUR") == 0) {
        return salary * 90.0; // Example: 1 EUR = 90 INR
    } else if (strcmp(currency, "JPY") == 0) {
        return salary * 0.55; // Example: 1 JPY = 0.55 INR
    } else if (strcmp(currency, "INR") == 0) {
        return salary;
    } else {
        printf("Invalid currency input. Assuming salary is in INR.\n");
        return salary;
    }
}

// Function to calculate tax based on income slabs
double calculateTax(double annualIncome) {
    double tax = 0.0;

    if (annualIncome > 1500000) {
        tax += (annualIncome - 1500000) * 0.30;
        annualIncome = 1500000;
    }
    if (annualIncome > 1200000) {
        tax += (annualIncome - 1200000) * 0.20;
        annualIncome = 1200000;
    }
    if (annualIncome > 1000000) {
        tax += (annualIncome - 1000000) * 0.15;
        annualIncome = 1000000;
    }
    if (annualIncome > 700000) {
        tax += (annualIncome - 700000) * 0.10;
    }

    return tax;
}

// Function to display investment options based on user selection
void displayInvestmentOptions(InvestmentOption options[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d. %s: %s\n", i + 1, options[i].option, options[i].description);
    }
}

// Function to ask for valid input (ensures the input is within a range)
int getValidInput(int min, int max, const char *prompt) {
    int choice;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &choice) != 1 || choice < min || choice > max) {
            // Clear the buffer if the input is invalid
            while(getchar() != '\n'); 
            printf("Invalid input. Please enter a valid choice between %d and %d.\n", min, max);
        } else {
            break;
        }
    }
    return choice;
}

// Function to suggest investment schemes based on investable amount from savings
void suggestInvestmentSchemes(double investableFromSavings) {
    int goal, riskAppetite;

    // Get valid input for investment goal
    printf("\n--- Investment Personalization ---\n");
    goal = getValidInput(1, 2, "Select your investment goal:\n1. Short-term (1-3 years)\n2. Long-term (5+ years)\nEnter your choice (1 or 2): ");

    // Get valid input for risk appetite
    printf("\nSelect your risk appetite:\n");
    riskAppetite = getValidInput(1, 3, "1. Low Risk\n2. Moderate Risk\n3. High Risk\nEnter your choice (1, 2, or 3): ");

    printf("\n--- Personalized Investment Options ---\n");

    if (goal == 1) { // Short-term goals
        if (riskAppetite == 1) {
            displayInvestmentOptions(shortTermLowRisk, 2);
        } else if (riskAppetite == 2) {
            displayInvestmentOptions(shortTermModerateRisk, 2);
        } else if (riskAppetite == 3) {
            displayInvestmentOptions(shortTermHighRisk, 2);
        }
    } else if (goal == 2) { // Long-term goals
        if (riskAppetite == 1) {
            displayInvestmentOptions(longTermLowRisk, 2);
        } else if (riskAppetite == 2) {
            displayInvestmentOptions(longTermModerateRisk, 2);
        } else if (riskAppetite == 3) {
            displayInvestmentOptions(longTermHighRisk, 2);
        }
    } else {
        printf("Invalid goal selected. Showing generic suggestions:\n");
        printf("1. Savings Account\n2. Gold\n3. Fixed Deposits\n");
    }

    // Suggest how to allocate the investable amount from savings
    printf("\n--- Suggested Allocation ---\n");
    printf("Consider allocating your investable amount across 2-3 options for diversification.\n");
    printf("Example: 50%% in Fixed Deposits, 30%% in Gold, and 20%% in Share market.\n");

    if (investableFromSavings < 1000) {
        printf("Consider saving more before investing to access better options.\n");
    } else {
        printf("Investable Amount from Savings: %.2lf\n", investableFromSavings);
        printf("Suggested Split:\n");
        printf("  - %.2lf in Fixed Deposits\n", investableFromSavings * 0.5);
        printf("  - %.2lf in Gold\n", investableFromSavings * 0.3);
        printf("  - %.2lf in Share Market\n", investableFromSavings * 0.2);
    }
}

int main() {
    double salary, salaryINR, taxes, investableAmount, savings, investableFromSavings;
    char currency[10];

    // Input salary and currency
    printf("Enter your monthly salary amount: ");
    scanf("%lf", &salary);

    // Get valid currency input
    while (1) {
        printf("Enter the currency (INR/USD/EUR/JPY): ");
        scanf("%s", currency);
        if (strcmp(currency, "INR") == 0 || strcmp(currency, "USD") == 0 || strcmp(currency, "EUR") == 0 || strcmp(currency, "JPY") == 0) {
            break;
        } else {
            printf("Invalid currency input. Please enter a valid currency (INR, USD, EUR, JPY).\n");
        }
    }

    // Convert salary to INR
    salaryINR = convertToINR(salary, currency);

    // Calculate annual income
    double annualIncome = salaryINR * 12;
    printf("\n--- Income Details ---\n");
    printf("Monthly Salary in INR: %.2lf\n", salaryINR);
    printf("Annual Income in INR: %.2lf\n", annualIncome);

    // Calculate taxes
    taxes = calculateTax(annualIncome);

    // Calculate investable amount after tax
    investableAmount = annualIncome - taxes;

    // Calculate savings (20% of investable amount after tax)
    savings = investableAmount * 0.20;

    // Calculate investable amount from savings (7% of savings)
    investableFromSavings = savings * 0.07;

    // Display results
    printf("\n--- Salary Breakdown ---\n");
    printf("Taxes: %.2lf\n", taxes);
    printf("Amount after reducing taxes: %.2lf\n", investableAmount);
    printf("Savings : %.2lf\n", savings);
    printf("Amount to invest from savings : %.2lf\n", investableFromSavings);

    // Suggest investment schemes based on investable amount from savings
    if (investableFromSavings > 0) {
        suggestInvestmentSchemes(investableFromSavings);
    } else {
        printf("\nNo amount left to invest from savings. Please revise your savings plan.\n");
    }

    return 0;
}
