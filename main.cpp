#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

enum Category {
    Food, Transportation, Entertainment, Utilities, Other
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
    }

    bool operator<(const CustomDate& rhs) const {
        
    }
};
class Transaction{ //Base class
    public:
        double virtual calculateImpact() = 0; //Pure virtual

        void virtual displayTransaction() { //Virtual
            cout << "Basic Info" << endl;
        }

    private: 
        double amount;
        string description;
        string date;
        Category category;


}

int printMenu();

int transactionManagement();


int main(){
    cout << "Welcome to your financial tracker" << endl;
    int selection = 0;
    do{
        selection = printMenu();
        switch(selection){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
        }

    } while(selection != 5);

    return 0;
}

int printMenu(){
    int selection = 0;
    while (selection <= 0 || selection > 5) {
        cout << "Select an option from out menu: " << endl;
        cout << "1.) Add Transaction, 2.) View All 2.) View by Category 3.) Analytics 4.) Save/Load 5.) Exit" << endl;
        cout << "Selection: ";
        cin >> selection;
    }
    return selection;
}


