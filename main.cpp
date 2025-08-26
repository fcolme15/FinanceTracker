#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

enum class Category {
    food, transportation, entertainment, utilities, other, exit, invalid
};

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
    private:
        double money;

};

class Transaction{ //Base class
    public:
        Transaction(double value){
            amount = MoneyAmount(value);
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
        string date;
        Category category;


};

class IncomeTransaction : public Transaction{
    public:
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
            return amount.getMoney();
        }

        void displayTransaction() override{
            cout << "Spent " << amount.getFormattedAmount() << " from Expenses" << endl;
        }

    private:

};

string printMenu();

int transactionManagement();

string stringToLower();

Category stringToCategory();




int main(){
    cout << "Welcome to your financial tracker" << endl;
    string selection;
    bool running = true;

    do{
        selection = printMenu();
        Category category = stringToCategory(selection);
        switch(category){
            case Category::food:
                break;
            case Category::transportation:
                break;
            case Category::entertainment:
                break;
            case Category::utilities:
                break;
            case Category::other:
                break;
            case Category::exit:
                cout << "Exiting the program." << endl;
                break;
            case Category::invalid:
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

Category stringToCategory(string input){
    static const std::unordered_map<string, Category> table {
        {"food",  Category::food},
        {"transportation",  Category::transportation},
        {"entertainment",  Category::entertainment},
        {"utilities",  Category::utilities},
        {"other",  Category::other}, 
        {"exit",  Category::exit},
        {"invalid",  Category::invalid},       
    };
    input = stringToLower(input);
    auto it = table.find(input); //Look in table
    if (it != table.end())
        return it->second;
    return Category::invalid;
}

