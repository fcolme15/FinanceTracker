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

string stringToLower();

MenuOptions stringToMenuOptions();

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
        vector<T> data;
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
        
        string getFormattedAmount(){
            return string("$") + std::to_string(money);
        }

        double getMoney(){
            return money;
        }

        void setMoney(double money){
            this->money = money;
        }

        MoneyAmount operator+(MoneyAmount& rhs){
            return MoneyAmount(this->money + rhs.getMoney());
        }

        MoneyAmount operator-(MoneyAmount& rhs){
            return MoneyAmount(this->money - rhs.getMoney());
        }

        bool operator==(MoneyAmount& rhs){
            return (this->money == rhs.getMoney()) ? true : false;
        }

        friend std::ostream& operator<<(std::ostream& os, const MoneyAmount& money){
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

        double virtual calculateImpact() = 0; //Pure virtual

        void virtual displayTransaction() { //Virtual
            cout << "Basic Info" << endl;
        }

        MoneyAmount getAmount(){
            return amount;
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
        
        double calculateImpact() override {
            return amount.getMoney();
        }

        void displayTransaction() override{
            cout << "Earned " << amount.getFormattedAmount() << " from Income" << endl;
        }

    private:

};

class ExpenseTransaction : public Transaction{
    public:
        double calculateImpact() override {
            return -amount.getMoney();
        }

        void displayTransaction() override{
            cout << "Spent " << amount.getFormattedAmount() << " from Expenses" << endl;
        }

    private:

};



int main(){
    cout << "Welcome to your financial tracker" << endl;
    string selection;
    bool running = true;

    do{
        selection = printMenu();
        MenuOptions category = stringToMenuOptions(selection);
        switch(category){
            case MenuOptions::transaction:
                break;
            case MenuOptions::view:
                break;
            case MenuOptions::analytics:
                break;
            case MenuOptions::save:
                break;
            case MenuOptions::load:
                break;
            case MenuOptions::exit:
                cout << "Exiting the program." << endl;
                break;
            case MenuOptions::invalid:
                cout << "Invalid input, please type of one of the options" << endl;
                running = false;
                break;
        }

    } while(running);

    return 0;
}

string printMenu(){
    string selection;
    cout << "Select an option from out menu: " << endl;
    cout << "Transaction, View All Transactions, View by Category, Analytics, Save/Load, Exit" << endl;
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
        {"transaction",  MenuOptions::transaction},
        {"view",  MenuOptions::view},
        {"analytics",  MenuOptions::analytics},
        {"save",  MenuOptions::save},
        {"load",  MenuOptions::load}, 
        {"exit",  MenuOptions::exit},
        {"invalid",  MenuOptions::invalid},       
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
    for (int i = 0; i < data.size(); i++){
        total += data[i];
    }
    return (double)total / (double)data.size();
}