#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

class Customer {
public:
    string customerID, password, name, email, address, phone;
    double savingsBalance, currentBalance;

    Customer(string id, string pass, string n, string e, string addr, string ph, double sb, double cb)
        : customerID(id), password(pass), name(n), email(e), address(addr), phone(ph), savingsBalance(sb), currentBalance(cb) {}
};

class BankSystem {
private:
    stack<pair<string, string>> predefinedDatabase;
    queue<Customer*> systemQueue;
    vector<Customer*> customers;

    const double MIN_SAVINGS_BALANCE = 1000.0;
    const double MIN_CURRENT_BALANCE = 5000.0;
    const double SAVINGS_SERVICE_CHARGE = 50.0;
    const double CURRENT_SERVICE_CHARGE = 250.0;

    string generatePassword() {
        string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()";
        string password;
        for (int i = 0; i < 8; ++i) {
            password += chars[rand() % chars.size()];
        }
        return password;
    }

    void applyServiceCharge(double& balance, double serviceCharge, const string& accountType) {
        if (balance >= serviceCharge) {
            balance -= serviceCharge;
            cout << "Rs. " << serviceCharge << " service charge applied to " << accountType << " account.\n";
        } else {
            cout << "Insufficient funds for service charge in " << accountType << " account.\n";
        }
    }

    void applyMinimumBalanceCharge(Customer* customer, const string& accountType) {
        if (accountType == "savings" && customer->savingsBalance < MIN_SAVINGS_BALANCE) {
            applyServiceCharge(customer->savingsBalance, SAVINGS_SERVICE_CHARGE, accountType);
        } else if (accountType == "current" && customer->currentBalance < MIN_CURRENT_BALANCE) {
            applyServiceCharge(customer->currentBalance, CURRENT_SERVICE_CHARGE, accountType);
        }
    }

public:
    BankSystem() {
        srand(static_cast<unsigned>(time(0)));
        predefinedDatabase.push({"user1", ""});
        predefinedDatabase.push({"user2", ""});
        predefinedDatabase.push({"user3", ""});
    }

    void signUp() {
        if (predefinedDatabase.empty()) {
            cout << "No default customer IDs available for registration.\n";
            return;
        }

        auto defaultCreds = predefinedDatabase.top();
        predefinedDatabase.pop();

        string name, email, address, phone;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter Address: ";
        cin >> address;
        cout << "Enter Phone Number: ";
        cin >> phone;

        string generatedPassword = generatePassword();
        Customer* newCustomer = new Customer(defaultCreds.first, generatedPassword, name, email, address, phone, 10000.0, 25000.0);
        customers.push_back(newCustomer);

        cout << "Registration successful! Your Customer ID is: " << defaultCreds.first << "\n";
        cout << "Your generated password is: " << generatedPassword << "\nPlease save it securely.\n";
    }

    Customer* login() {
        string customerID, password;
        cout << "Enter Customer ID: ";
        cin >> customerID;
        cout << "Enter Password: ";
        cin >> password;

        for (auto customer : customers) {
            if (customer->customerID == customerID && customer->password == password) {
                systemQueue.push(customer);
                cout << "Login successful!\n";
                return customer;
            }
        }

        cout << "Invalid Customer ID or Password.\n";
        return nullptr;
    }

    void adminLogin() {
        const string ADMIN_USERNAME = "admin", ADMIN_PASSWORD = "admin123";
        string adminUsername, adminPassword;

        cout << "Enter Admin Username: ";
        cin >> adminUsername;
        cout << "Enter Admin Password: ";
        cin >> adminPassword;

        if (adminUsername == ADMIN_USERNAME && adminPassword == ADMIN_PASSWORD) {
            cout << "\n--- Admin Panel ---\nRegistered Customers:\n";
            for (auto customer : customers) {
                cout << "Customer ID: " << customer->customerID << " | Name: " << customer->name << " | Email: " << customer->email << "\n";
            }

            cout << "\nUnused Customer IDs:\n";
            auto tempStack = predefinedDatabase;
            while (!tempStack.empty()) {
                auto creds = tempStack.top();
                tempStack.pop();
                cout << "Customer ID: " << creds.first << " | Password: " << (creds.second.empty() ? "Not Generated" : creds.second) << "\n";
            }
        } else {
            cout << "Invalid admin credentials. Access denied.\n";
        }
    }

    void checkBalance(Customer* customer) {
        cout << fixed << setprecision(2);
        cout << "Savings Account Balance: Rs. " << customer->savingsBalance << "\n";
        cout << "Current Account Balance: Rs. " << customer->currentBalance << "\n";
    }

    void withdraw(Customer* customer, const string& accountType, double amount) {
        double* balance = (accountType == "savings") ? &customer->savingsBalance : &customer->currentBalance;
        double serviceCharge = (accountType == "savings") ? SAVINGS_SERVICE_CHARGE : CURRENT_SERVICE_CHARGE;
        double maxDeductible = *balance - serviceCharge;

        if (amount > maxDeductible) amount = maxDeductible;
        if (amount < 0) amount = 0;

        *balance -= amount;
        cout << "Withdrawal successful. Amount withdrawn: Rs. " << amount << "\n";
        applyMinimumBalanceCharge(customer, accountType);
        checkBalance(customer);
    }

    void transfer(Customer* customer) {
        int choice;
        cout << "\n--- Transfer Options ---\n";
        cout << "1. Transfer between Savings and Current (Own Account)\n";
        cout << "2. Transfer to another Customer's Savings Account\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string fromAccount, toAccount;
                double amount;

                cout << "Enter From Account (savings/current): ";
                cin >> fromAccount;
                cout << "Enter To Account (savings/current): ";
                cin >> toAccount;
                cout << "Enter Amount to Transfer: ";
                cin >> amount;

                double* fromBalance = (fromAccount == "savings") ? &customer->savingsBalance : &customer->currentBalance;
                double* toBalance = (toAccount == "savings") ? &customer->savingsBalance : &customer->currentBalance;
                double serviceCharge = (fromAccount == "savings") ? SAVINGS_SERVICE_CHARGE : CURRENT_SERVICE_CHARGE;
                double maxDeductible = *fromBalance - serviceCharge;

                if (amount > maxDeductible) amount = maxDeductible;
                if (amount < 0) amount = 0;

                *fromBalance -= amount;
                *toBalance += amount;

                cout << "Transfer successful. Amount transferred: Rs. " << amount << "\n";
                applyMinimumBalanceCharge(customer, fromAccount);
                checkBalance(customer);
                break;
            }
            case 2: {
                string recipientID;
                double amount;

                cout << "Enter Recipient Customer ID: ";
                cin >> recipientID;
                cout << "Enter Amount to Transfer: ";
                cin >> amount;

                Customer* recipient = nullptr;
                for (auto cust : customers) {
                    if (cust->customerID == recipientID) {
                        recipient = cust;
                        break;
                    }
                }

                if (!recipient) {
                    cout << "Recipient not found.\n";
                    return;
                }

                if (customer->savingsBalance >= amount) {
                    customer->savingsBalance -= amount;
                    recipient->savingsBalance += amount;

                    cout << "Transfer successful. Amount transferred: Rs. " << amount << "\n";
                    checkBalance(customer);
                } else {
                    cout << "Insufficient savings balance for the transfer.\n";
                }
                break;
            }
            default:
                cout << "Invalid choice. Transfer cancelled.\n";
        }
    }
    
    void changePassword(Customer* customer) {
        string oldPassword, newPassword;
        cout << "Enter your current password: ";
        cin >> oldPassword;

        if (customer->password == oldPassword) {
            cout << "Enter new password: ";
            cin >> newPassword;
            customer->password = newPassword;
            cout << "Password changed successfully.\n";
        } else {
            cout << "Incorrect current password. Password change failed.\n";
        }
    }

    void logout(Customer* customer) {
        cout << "Logout successful. Goodbye, " << customer->name << "!\n";
        systemQueue.pop();
    }
};

int main() {
    BankSystem bank;
    Customer* loggedInCustomer = nullptr;
    int choice;

    do {
        cout << "\n--- Bank ATM System ---\n1. Sign Up\n2. Login\n3. Admin Login\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.signUp();
                break;
            case 2:
                loggedInCustomer = bank.login();
                while (loggedInCustomer) {
                    int action;
                    cout << "\n--- Customer Menu ---\n1. Check Balance\n2. Withdraw\n3. Transfer Between Accounts\n4. Change Password\n5. Logout\nEnter your action: ";
                    cin >> action;

                    if (action == 1) bank.checkBalance(loggedInCustomer);
                    else if (action == 2) {
                        string accountType;
                        double amount;
                        cout << "Enter Account Type (savings/current): ";
                        cin >> accountType;
                        cout << "Enter Amount to Withdraw: ";
                        cin >> amount;
                        bank.withdraw(loggedInCustomer, accountType, amount);
                    } else if (action == 3) {
                        bank.transfer(loggedInCustomer);
                    } else if (action == 4) {
                        bank.changePassword(loggedInCustomer);
                    } else if (action == 5) {
                        bank.logout(loggedInCustomer);
                        loggedInCustomer = nullptr;
                    } else {
                        cout << "Invalid action. Try again.\n";
                    }
                }
                break;
            case 3:
                bank.adminLogin();
                break;
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
    return 0;
}