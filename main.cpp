#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <cctype> 

using std::cout;
using std::cin;
using std::endl;
using std::string;

enum class MenuOptions {
    transaction, view, analytics, save, load, exit, invalid
};

enum class Category {
    food, transportation, entertainment, utilities, other
};

template<typename T>
T findMax(const std::vector<T>& data);

template<typename T>
double calculateAverage(const std::vector<T>& data);

string printMenu();

int transactionManagement();

string stringToLower(string input);

MenuOptions stringToMenuOptions(string input);

struct CustomDate {
    int day;
    int month;
    int year;

    bool setYear(int day, int month, int year){
        if (day < 0 || day > 31 || month < 0 || month > 12 || year < 0 || year > 2026){
            return false;
        }
        this->day = day;
        this->month = month;
        this->year = year;
        return true;
    }

    bool operator==(const CustomDate& rhs) const {
        if (
            this->day == rhs.day && this-> month == rhs.month && this->year == rhs.year
        ){
            return true;
        }
        return false;
    }

    bool operator>(const CustomDate& rhs) const {
        if (this->year != rhs.year){
            return (this->year > rhs.year ) ? true : false;
        }
        else if (this->month != rhs.month) {
            return (this->month > rhs.month) ? true : false;
        }
        else if (this->day != rhs.day) {
            return (this->day > rhs.day) ? true : false;
        }
        return false;
    }

    bool operator<(const CustomDate& rhs) const {
        if (this->year != rhs.year){
            return (this->year < rhs.year ) ? true : false;
        }
        else if (this->month != rhs.month) {
            return (this->month < rhs.month) ? true : false;
        }
        else if (this->day != rhs.day) {
            return (this->day < rhs.day) ? true : false;
        }
        return false;
    }
};

struct CategoryStats {
    string name;
    double totalSpent;
    int transactionCount;
    double percentageBudget;
};

template<typename T>
class Statistics{
    private:
        std::vector<T> data;
    public: 
        void addData(const T& item) { data.push_back(item); }
        T getMax() const { return findMax(data);}
        double getAverage() const { return calculateAverage(data); }
        size_t getCount() const{ return data.size(); }
};

class MoneyAmount {
    public: 
        MoneyAmount(){
            this->money = 0.0;
        }
        MoneyAmount(double amount){
            this->money = amount;
        }
        
        string getFormattedAmount() const {
            return string("$") + std::to_string(money);
        }

        double getMoney() const {
            return money;
        }

        void setMoney(double money){
            this->money = money;
        }

        MoneyAmount operator+(const MoneyAmount& rhs) const {
            return MoneyAmount(this->money + rhs.getMoney());
        }

        MoneyAmount operator-(const MoneyAmount& rhs) const {
            return MoneyAmount(this->money - rhs.getMoney());
        }

        bool operator==(const MoneyAmount& rhs) const {
            return (this->money == rhs.getMoney()) ? true : false;
        }

        friend std::ostream& operator<<(std::ostream& os, const MoneyAmount& money) {
            os << money.getFormattedAmount();
            return os;
        }
        
    private:
        double money;

};

class Transaction{ //Base class
    public:
        Transaction(double value, string description, CustomDate date, Category category){
            this->amount = MoneyAmount(value);
            this->description = description;
            this->date = date;
            this->category = category;
        }

        virtual ~Transaction() = default;

        virtual double calculateImpact() const = 0; //Pure virtual

        virtual void displayTransaction() const { //Virtual
            cout << "Basic Info" << endl;
        }

        MoneyAmount getAmount() const {
            return amount;
        }

        Category getCategory() const {
            return category;
        }

        string getDescription() const {
            return description;
        }

        CustomDate getDate() const {
            return date;
        }

    protected: 
        MoneyAmount amount;
        string description;
        CustomDate date;
        Category category;

};

class IncomeTransaction : public Transaction{
    public:
        IncomeTransaction(double value, string description, CustomDate date, Category category) 
            : Transaction(value, description, date, category) {}

        double calculateImpact() const override {
            return amount.getMoney();
        }

        void displayTransaction() const override{
            cout << "Earned " << amount.getFormattedAmount() << " from Income" << endl;
        }

    private:

};

class ExpenseTransaction : public Transaction{
    public:
        ExpenseTransaction(double value, string description, CustomDate date, Category category) 
            : Transaction(value, description, date, category) {}

        double calculateImpact() const override {
            return -amount.getMoney();
        }

        void displayTransaction() const override{
            cout << "Spent " << amount.getFormattedAmount() << " from Expenses" << endl;
        }

    private:

};


class FinanceTracker{
    private:
        std::vector<std::unique_ptr<Transaction>> transactions;
        string filename;
        static int totalTransactions;

    public:
        void addTransaction(std::unique_ptr<Transaction> transaction){
            transactions.push_back(std::move(transaction));
            totalTransactions++;
        }
        
        void removeTransaction(int index){
            if (index >= 0 && index < static_cast<int>(transactions.size())) {
                transactions.erase(transactions.begin() + index);
            }
        }
        
        const std::vector<std::unique_ptr<Transaction>>& getAllTransactions() const{
            return transactions;
        }

        double calculateTotalBalance(){
            double balance = 0.0;
            for (const auto& transaction : transactions) {
                balance += transaction->calculateImpact();
            }
            return balance;
        }

        MoneyAmount getTotalIncome(){
            double total = 0.0;
            for (const auto& transaction : transactions) {
                double impact = transaction->calculateImpact();
                if (impact > 0) {
                    total += impact;
                }
            }
            return MoneyAmount(total);
        }

        MoneyAmount getTotalExpenses(){
            double total = 0.0;
            for (const auto& transaction : transactions) {
                double impact = transaction->calculateImpact();
                if (impact < 0) {
                    total += std::abs(impact);
                }
            }
            return MoneyAmount(total);
        }

        void displayAllTransactions(){
            if (transactions.empty()) {
                cout << "No transactions to display." << endl;
                return;
            }
            
            cout << "\n=== All Transactions ===" << endl;
            for (size_t i = 0; i < transactions.size(); i++) {
                cout << i + 1 << ". ";
                transactions[i]->displayTransaction();
            }
        }

        void displayAnalytics(){
            cout << "\n=== Financial Analytics ===" << endl;
            cout << "Total Balance: $" << calculateTotalBalance() << endl;
            cout << "Total Income: " << getTotalIncome() << endl;
            cout << "Total Expenses: " << getTotalExpenses() << endl;
            cout << "Total Transactions Created: " << totalTransactions << endl;
        }

        static int getTotalTransactionsCreated() {
            return totalTransactions;
        }

        size_t getTransactionCount() const {
            return transactions.size();
        }
};


int FinanceTracker::totalTransactions = 0;

int main(){
    cout << "Welcome to your financial tracker" << endl;
    string selection;
    bool running = true;
    FinanceTracker tracker;

    do{
        selection = printMenu();
        MenuOptions menuChoice = stringToMenuOptions(selection);
        switch(menuChoice){
            case MenuOptions::transaction: {
                cout << "Enter transaction type (income/expense): ";
                string type;
                cin >> type;
                
                cout << "Enter amount: $";
                double amount;
                cin >> amount;
                
                cout << "Enter description: ";
                string description;
                cin.ignore(); // Clear the newline
                getline(cin, description);
                
                cout << "Enter day: ";
                int day;
                cin >> day;
                cout << "Enter month: ";
                int month;
                cin >> month;
                cout << "Enter year: ";
                int year;
                cin >> year;
                
                CustomDate date;
                if (!date.setYear(day, month, year)) {
                    cout << "Invalid date entered!" << endl;
                    break;
                }
                
                cout << "Enter category (food, transportation, entertainment, utilities, other): ";
                string categoryStr;
                cin >> categoryStr;
                
                Category category = Category::other; // default
                if (categoryStr == "food") category = Category::food;
                else if (categoryStr == "transportation") category = Category::transportation;
                else if (categoryStr == "entertainment") category = Category::entertainment;
                else if (categoryStr == "utilities") category = Category::utilities;
                
                if (type == "income") {
                    tracker.addTransaction(std::make_unique<IncomeTransaction>(amount, description, date, category));
                } else {
                    tracker.addTransaction(std::make_unique<ExpenseTransaction>(amount, description, date, category));
                }
                
                cout << "Transaction added successfully!" << endl;
                break;
            }
            case MenuOptions::view:
                tracker.displayAllTransactions();
                break;
            case MenuOptions::analytics:
                tracker.displayAnalytics();
                break;
            case MenuOptions::save:
                cout << "Save functionality not implemented yet." << endl;
                break;
            case MenuOptions::load:
                cout << "Load functionality not implemented yet." << endl;
                break;
            case MenuOptions::exit:
                cout << "Exiting the program." << endl;
                running = false;
                break;
            case MenuOptions::invalid:
                cout << "Invalid input, please type one of the options" << endl;
                break;
        }

    } while(running);

    return 0;
}

string printMenu(){
    string selection;
    cout << "Select an option from our menu: " << endl;
    cout << "Transaction, View, Analytics, Save, Load, Exit" << endl;
    cout << "Selection: ";
    cin >> selection;
    return selection;
}

string stringToLower(string input){
    for (char& c : input) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return input;
}

MenuOptions stringToMenuOptions(string input){
    static const std::unordered_map<string, MenuOptions> table {
        {"transaction", MenuOptions::transaction},
        {"view", MenuOptions::view},
        {"analytics", MenuOptions::analytics},
        {"save", MenuOptions::save},
        {"load", MenuOptions::load}, 
        {"exit", MenuOptions::exit},     
    };
    input = stringToLower(input);
    auto it = table.find(input); //Look in table
    if (it != table.end())
        return it->second;
    return MenuOptions::invalid;
}

template<typename T>
T findMax(const std::vector<T>& data){
    if (data.size() == 0){
        throw std::runtime_error("Vector is empty, Cannot find max");
    }
    T max = data[0];
    for (auto d : data){
        if (d > max){
            max = d;
        }
    }
    return max;
}

template<typename T>
double calculateAverage(const std::vector<T>& data){
    double total = 0;
    for (size_t i = 0; i < data.size(); i++){
        total += data[i];
    }
    return (double)total / (double)data.size();
}