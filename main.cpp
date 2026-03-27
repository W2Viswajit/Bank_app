#include <iostream>
#include <stdexcept>

// Custom Dynamic Array Implementation
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int currentSize;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < currentSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray(int initialCapacity = 10) : capacity(initialCapacity), currentSize(0) {
        data = new T[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (currentSize == capacity) {
            resize(capacity * 2);
        }
        data[currentSize++] = value;
    }

    void remove_at(int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        for (int i = index; i < currentSize - 1; ++i) {
            data[i] = data[i + 1];
        }
        --currentSize;
    }

    T& at(int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    int size() const {
        return currentSize;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }
};

#endif

// Custom Stack Implementation
#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H

#include <stdexcept>

template <typename T>
class Stack {
private:
    T* data;
    int capacity;
    int topIndex;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i <= topIndex; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    Stack(int initialCapacity = 10) : capacity(initialCapacity), topIndex(-1) {
        data = new T[capacity];
    }

    ~Stack() {
        delete[] data;
    }

    void push(const T& value) {
        if (topIndex + 1 == capacity) {
            resize(capacity * 2);
        }
        data[++topIndex] = value;
    }

    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow");
        }
        --topIndex;
    }

    T& top() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    int size() const {
        return topIndex + 1;
    }
};

#endif

 // Custom Queue Implementation
#ifndef CUSTOM_QUEUE_H
#define CUSTOM_QUEUE_H

#include <stdexcept>

template <typename T>
class Queue {
private:
    T* data;
    int capacity;
    int frontIndex;
    int rearIndex;
    int currentSize;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < currentSize; ++i) {
            newData[i] = data[(frontIndex + i) % capacity];
        }
        delete[] data;
        data = newData;
        frontIndex = 0;
        rearIndex = currentSize - 1;
        capacity = newCapacity;
    }

public:
    Queue(int initialCapacity = 10) : capacity(initialCapacity), frontIndex(0), rearIndex(-1), currentSize(0) {
        data = new T[capacity];
    }

    ~Queue() {
        delete[] data;
    }

    void enqueue(const T& value) {
        if (currentSize == capacity) {
            resize(capacity * 2);
        }
        rearIndex = (rearIndex + 1) % capacity;
        data[rearIndex] = value;
        ++currentSize;
    }

    void dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue underflow");
        }
        frontIndex = (frontIndex + 1) % capacity;
        --currentSize;
    }

    T& front() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
        return data[frontIndex];
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    int size() const {
        return currentSize;
    }
};

#endif


using namespace std;

struct Customer {
    string id;
    string name;
    string email;
    string address;
    string phone;
    string password;
    double savingsBalance;
    double currentBalance;
};

Stack<string> predefinedIds;
Stack<string> predefinedPasswords;
Stack<string> usedIds;         
Stack<string> usedPasswords;  
Queue<Customer> accessQueue;
DynamicArray<Customer> customerDB;

void initializeDefaults() {
    predefinedIds.push("user1");
    predefinedPasswords.push("pass1");
    predefinedIds.push("user2");
    predefinedPasswords.push("pass2");
    predefinedIds.push("user3");
    predefinedPasswords.push("pass3");
    predefinedIds.push("user4");
    predefinedPasswords.push("pass4");
    predefinedIds.push("user5");
    predefinedPasswords.push("pass5");

}

bool authenticateUser(const string& id, const string& password) {
    for (int i = 0; i < customerDB.size(); ++i) {
        if (customerDB.at(i).id == id && customerDB.at(i).password == password) {
            return true;
        }
    }
    return false;
}

void registerUser() {
    if (predefinedIds.isEmpty() || predefinedPasswords.isEmpty()) {
        cout << "No more default IDs available for registration.\n";
        return;
    }

    Customer newCustomer;
    newCustomer.id = predefinedIds.top();
    predefinedIds.pop();
    usedIds.push(newCustomer.id);
    newCustomer.password = predefinedPasswords.top();
    predefinedPasswords.pop();
    usedPasswords.push(newCustomer.password);               

    cin.ignore();
    cout << "Enter Name: ";
    getline(cin,newCustomer.name);
    cout << "Enter Email: ";
    getline(cin,newCustomer.email);
    cout << "Enter Address: ";
    getline(cin,newCustomer.address);
    cout << "Enter Phone: ";
    getline(cin,newCustomer.phone);

    newCustomer.savingsBalance = 10000.0;
    newCustomer.currentBalance = 25000.0;

    customerDB.push_back(newCustomer);
    cout << "\nRegistration Successful! Your ID: " << newCustomer.id << ", Password: " << newCustomer.password << "\n";
}
void adminLogin() {
    cout << "Remaining IDs in Stack:\n";
    Stack<string> tempIds = predefinedIds;
    while (!tempIds.isEmpty()) {
        cout << tempIds.top() << "\n";
        tempIds.pop();
    }

    cout << "\nIDs in Use:\n";
    Stack<string> tempUsedIds = usedIds;
    while (!tempUsedIds.isEmpty()) {
        cout << tempUsedIds.top() << "\n";
        tempUsedIds.pop();
    }

    cout << "\nRemaining Passwords in Stack:\n";
    Stack<string> tempPasswords = predefinedPasswords;
    while (!tempPasswords.isEmpty()) {
        cout << tempPasswords.top() << "\n";
        tempPasswords.pop();
    }

    cout << "\nPasswords in use:\n";
    Stack<string> tempUsedPasswords = usedPasswords; 
    while (!tempUsedPasswords.isEmpty()) {
        cout << tempUsedPasswords.top() << "\n";
        tempUsedPasswords.pop();
    }

    cout << "\nRegistered Customers in customerDB:\n";
    for (int i = 0; i < customerDB.size(); ++i) {
        cout << "Customer " << i + 1 << ": ID = " 
             << customerDB.at(i).id 
             << ", Name = " 
             << customerDB.at(i).name 
             << ", Password = " 
             << customerDB.at(i).password 
             << ", Email = " 
             << customerDB.at(i).email 
             << ", Address = " 
             << customerDB.at(i).address 
             << ", Phone = " 
             << customerDB.at(i).phone 
             << "\n";
    }

    cout << "\nCurrent Access Queue:\n";
    Queue<Customer> tempQueue = accessQueue;
    while (!tempQueue.isEmpty()) {
        Customer frontCustomer = tempQueue.front();
        cout << "Customer ID: " << frontCustomer.id 
             << ", Name: " << frontCustomer.name << "\n";
        tempQueue.dequeue();
    }
}

void displayMenu() {
    cout << "1. Check Balance\n";
    cout << "2. Withdraw\n";
    cout << "3. Transfer\n";
    cout << "4. Change Password\n";
    cout << "5. Logout\n";
    cout << "Choose: \n";
}

int getValidChoice(int min, int max) {
    int choice;
    while (true) {
        cout << "Enter your choice (" << min << "-" << max << "): ";
        if (cin >> choice && choice >= min && choice <= max) {
            return choice;
        }
        cout << "Invalid input! Please enter a valid option.\n";
        cin.clear();
        cin.ignore(1000, '\n');  
    }
}

double getValidAmount() {
    double amount;
    while (true) {
        cout << "Enter Amount: ";
        cin >> amount;

        if (cin.fail() || amount < 0) {
            cout << "Invalid amount! Amount cannot be negative. Please enter a positive number.\n";
            cin.clear();            
            cin.ignore(1000, '\n'); 
        } else {
            return amount;          
        }
    }
}

void changePassword(const string& id, const string& newPassword) {
    for (int i = 0; i < customerDB.size(); ++i) {
        if (customerDB.at(i).id == id) {
            customerDB.at(i).password = newPassword;
            cout << "Password updated successfully for " << id << ".\n";
            return;
        }
    }
    cout << "User ID not found.\n";
}

void handleSession(Customer& customer) {
    while (true) {
        displayMenu();
        int choice = getValidChoice(1, 5);
        switch (choice) {
            case 1:{
                cout << "\nSavings Balance: Rs." << customer.savingsBalance << "\n";
                cout << "Current Balance: Rs." << customer.currentBalance << "\n";
                break;
            }   

            case 2: {
                cout << "Withdrawal Menu\n";
                cout << "1. Withdraw from Savings\n2. Withdraw from Current\nChoose: ";
                int accChoice;
                cin >> accChoice;
                double amount = getValidAmount();
                if (accChoice == 1) {
                    if (customer.savingsBalance - amount < 50.0) {
                        cout << "Insufficient balance for this withdrawal. Minimum Rs.50 must remain in the account.\n";
                    } 
                    else if (customer.savingsBalance - amount < 1000.0) {
                        // Deduct amount and apply service charge if balance drops below Rs.1000
                        customer.savingsBalance -= (amount + 50.0);
                        cout << "Service charge of Rs.50 applied.\n";
                    } 
                    else {
                        // Normal withdrawal without service charge
                        customer.savingsBalance -= amount;
                    }
                    cout << "\nSavings Balance: Rs." << customer.savingsBalance << "\n";
                    cout << "Current Balance: Rs." << customer.currentBalance << "\n";
                } 
                
                else if (accChoice == 2) {
                    if (customer.currentBalance - amount < 250.0) {
                        cout << "Insufficient balance for this withdrawal. Minimum Rs.250 must remain in the account.\n";
                    } 
                    else if (customer.currentBalance - amount < 5000.0) {
                        customer.currentBalance -= (amount + 250.0);
                        cout << "Service charge of Rs.250 applied.\n";
                    } 
                    else {
                        customer.currentBalance -= amount;
                    }
                    cout << "\nSavings Balance: Rs." << customer.savingsBalance << "\n";
                    cout << "Current Balance: Rs." << customer.currentBalance << "\n";
                 
                }
                
                else {
                    cout << "Invalid account choice.\n";
                }
                break;
            }

            case 3: {
                cout << "Transfer Menu\n";
                cout << "1. Transfer between accounts\n2. Transfer to another customer\nChoose: ";
                int transferChoice;
                cin >> transferChoice;
                
                if (transferChoice == 1) {
                    double amount;
                    cout << "1. Savings to Current\n2. Current to Savings\nChoose: ";
                    int accChoice;
                    cin >> accChoice;
                    amount = getValidAmount();
                    switch(accChoice){
                        case 1:{
                            if((customer.savingsBalance - amount) <= 50){ 
                                cout << "Insufficient balance for this withdrawal. Minimum Rs.50 must remain in the account.\n";
                            } 

                            else if((customer.savingsBalance - amount) > 0 && (customer.savingsBalance - amount) < 1000.0) {
                                customer.savingsBalance -= (amount + 50.0);
                                customer.currentBalance += amount;
                                cout << "Service charge of Rs.50 applied.\n";
                                
                            }
                            else {
                            customer.savingsBalance -= amount;
                            customer.currentBalance += amount;
                            }
                            cout << "\nSavings Balance: Rs." << customer.savingsBalance << "\n";
                            cout << "Current Balance: Rs." << customer.currentBalance << "\n";
                            break;
                        }
                        case 2:{
                            if((customer.currentBalance - amount) <= 250){ 
                                cout << "Insufficient balance for this withdrawal. Minimum Rs.250 must remain in the account.\n";
                            } 

                            else if((customer.currentBalance - amount) > 0 && (customer.currentBalance - amount) < 5000.0) {
                                customer.currentBalance -= (amount + 250.0);
                                customer.savingsBalance += amount;
                                cout << "Service charge of Rs.250 applied.\n";
                                
                            }
                            else {
                            customer.currentBalance -= amount;
                            customer.savingsBalance += amount;
                            }
                            cout << "\nSavings Balance: Rs." << customer.savingsBalance << "\n";
                            cout << "Current Balance: Rs." << customer.currentBalance << "\n";
                            break;
                        }
                        default: {
                            cout << "Invalid account choice.\n";
                            break;
                        }
                    }
                }

                else if (transferChoice == 2) {
                    string recipientId;
                    cout << "Enter Recipient ID: ";
                    cin >> recipientId;
                    double amount = getValidAmount();
                    bool check = false;
                    for (int i = 0; i < customerDB.size(); ++i) {
                        if (customerDB.at(i).id == recipientId) {
                            check = true;
                            if (customer.savingsBalance - amount <= 50) {
                                cout << "Insufficient balance for this transaction.\n";
                            } 
                            else if  ((customer.savingsBalance - amount) > 0 && (customer.savingsBalance - amount) < 1000.0) {
                                customer.savingsBalance -= (amount + 50.0);
                                customerDB.at(i).savingsBalance += amount;
                                cout << "Service charge of Rs.50 applied.\n";
                            }
                            else {
                                customer.savingsBalance -= amount;
                                customerDB.at(i).savingsBalance += amount;
                            }
                            cout << "\nSavings Balance: Rs." << customer.savingsBalance << "\n";
                            cout << "Current Balance: Rs." << customer.currentBalance << "\n";
                            break;
                        }                        
                    }
                    if(!check){
                            cout<<"Account does not exist.\n";
                    }
                    break;  
                } 
                           
                else {
                    cout << "Invalid transfer choice.\n";
                }
                break;
            }

            case 4:{
                string newPassword;
                cout << "Enter New Password: ";
                cin >> newPassword;
                changePassword(customer.id, newPassword);
                break;
            }

            case 5:{
                cout << "Logging out...\n";
                return;
            }

            default:
                cout << "Invalid choice.\n";
        }
    }
}

void login() {
    string id, password;
    cout << "Enter ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> password;

    if (authenticateUser(id, password)) {
        for (int i = 0; i < customerDB.size(); ++i) {
            if (customerDB.at(i).id == id) {
                accessQueue.enqueue(customerDB.at(i));
                Customer& currentCustomer = accessQueue.front();
                cout << "Login Successful!\n\n";
                handleSession(currentCustomer);
                accessQueue.dequeue();
                break;
            }
        }
    } else {
        cout << "Invalid ID or Password.\n";
    }
}

int main() {
    initializeDefaults();
    string adminpassword;

    while (true) {
        cout << "\nBank Application\n";
        cout << "1. Sign-up\n2. Login\n3. Admin Login\n4. Exit\nChoose: ";
        int choice = getValidChoice(1, 4);
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                cout << "Enter Admin Password: ";
                cin >> adminpassword;
                if(adminpassword == "admin")
                    adminLogin();
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}