# 🏦 Bank ATM System (C++)

## 📌 Overview

This project is a **Bank ATM Simulation System** built using C++. It allows users to register, log in, and perform banking operations such as balance checking, withdrawals, transfers, and password management.

The system demonstrates the use of **Data Structures and Object-Oriented Programming (OOP)** concepts in a real-world banking scenario.

---

## 🚀 Features

### 👤 User Features

* User Registration (Sign Up)
* Secure Login Authentication
* Check Savings & Current Account Balance
* Withdraw Money
* Transfer Funds:

  * Between own accounts
  * To other customers
* Change Password
* Logout System

### 🛠️ Admin Features

* View registered customers
* View unused customer IDs
* Monitor system data

---

## 🧱 Tech Stack

* **Language:** C++
* **Concepts Used:**

  * Object-Oriented Programming (OOP)
  * STL (Stack, Queue, Vector)
  * Dynamic Memory Allocation
  * File-less Data Handling

---

## 📂 Project Structure

```
├── main.cpp          # Main program file
├── README.md         # Project documentation
```

---

## ⚙️ How It Works

### 1. Registration

* Users are assigned a **default customer ID**
* A **secure random password** is generated
* Initial balances:

  * Savings: ₹10,000
  * Current: ₹25,000

### 2. Login

* Users authenticate using ID and password
* System validates credentials from database

### 3. Banking Operations

* Withdraw money with minimum balance rules
* Transfer funds internally or to other users
* Service charges applied if minimum balance violated

---

## 💰 Business Rules

| Account Type | Minimum Balance | Service Charge |
| ------------ | --------------- | -------------- |
| Savings      | ₹1000           | ₹50            |
| Current      | ₹5000           | ₹250           |

---

## ▶️ How to Run

### Step 1: Compile

```bash
g++ main.cpp -o bank
```

### Step 2: Run

```bash
./bank
```

---

## 🧪 Sample Flow

```
1. Sign Up
2. Login
3. Admin Login
4. Exit
```

After login:

```
1. Check Balance
2. Withdraw
3. Transfer
4. Change Password
5. Logout
```

---

## 📊 Data Structures Used

* **Stack**

  * Stores predefined customer IDs
* **Queue**

  * Manages customer access (FIFO)
* **Vector**

  * Stores customer database dynamically

---

## 🔐 Security Features

* Password-based authentication
* Random password generation
* Admin authentication system

---

## ⚠️ Limitations

* No database (data is not persistent)
* No encryption for passwords
* CLI-based UI only

---

## 🌱 Future Improvements

* Add file/database storage (SQLite/Firebase)
* GUI using Qt or web frontend
* Encryption for passwords
* Transaction history
* AI-based fraud detection (future scope 🚀)

---

## 👨‍💻 Author

**Viswajit R**
AI & Data Science Student

---

## 📜 License

This project is for educational purposes only.
