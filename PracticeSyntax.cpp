#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <deque>
#include <vector>
#include <stdexcept>


using std::cout;
using std::cin;
using std::string;

struct point2D{ //Base struct
    float y;
    float x;

    point2D(){
        this->y = 0;
        this->x = 0;
    }

    point2D(float y, float x){
        this->y = y;
        this->x = x;
    }

    void virtual printValues(){
        cout << "X: " << this->x << "Y: " << this->y << std::endl;
    }
};

struct point3D : point2D{ //Inheritance Struct
    float z;

    point3D()
        :point2D() {
            this->z = 0;
    }

    point3D(float y, float x, float z)
        :point2D(y, x) {
            this->z = z;
    }

    void printValues() override {
        cout << "X: " << this->x << "Y: " << this->y << "Z: " << this->z << std::endl;
    }
};

class BaseCar{ //Base class
    public:
        BaseCar(int licensePlate, int carId){
            this->licensePlate = licensePlate;
            this->carId = carId;
        }

        void virtual honk() = 0; //Pure virtual

        void virtual drive(){ //Virtual
            cout << "Car is driving! " << std::endl;
        }

        int accelerationPerSecond(){
            return 5;
        }

        int getCarId(){
            return carId;
        }

        virtual ~BaseCar() = default;
    protected:
        int licensePlate;

    private:
        int carId;
};

class ElectricCar : public BaseCar{ //Inheritance 
    public:
        ElectricCar(int licensePlate, int carId) //Parent constructor
            :BaseCar(licensePlate, carId){
                battery = 0;
        }

        ElectricCar(int licensePlate, int carId, int battery) //Parent and own constructor
            :BaseCar(licensePlate, carId){
                this->battery = battery;
        }
        void honk() override { //Override pure virtual
            cout << "Beep Boop" << std::endl;
        }

        void drive() override { //Override function
            cout << "Electric Car is driving! " << std::endl;
        }

        void chargeCar(){
            battery = 100;
        }

        int getLicensePlate() const { //Const -> cannot change any class values, yes locals
            return licensePlate;
        }

        bool operator+ (const ElectricCar & rhs){ //Overloaded operators: +, -, ==, >, <, =
            return true;
        }

        friend std::ostream& operator<<(std::ostream& os, const ElectricCar money) { //Output stream overload
            os << "Electric Car";
            return os;
        }

        ~ElectricCar() override = default;
    protected:

    private:
        int battery;
};

enum class Weather{
    sunny, rainy, cloudy, cold, snowy
};

void sampleLoops();

void sampleEnum();

void sampleConst();

void sampleCast();

void sampleString();

void sampleArray();

void sampleVectorStack();

void sampleMap();

void sampleSet();

void sampleDeque();

void sampleStack();

void sampleSmartPointers();

int main (){
    sampleLoops();
    
    sampleEnum();

    sampleConst();

    sampleCast();

    sampleString();

    sampleArray();

    sampleVectorStack();

    sampleMap();

    sampleSet();

    sampleDeque();

    sampleStack();

    sampleSmartPointers();
    
    return 0;
}

void sampleLoops(){ 
    int* arr = new int[10];
    std::vector<int> v;
    //For
    for (int i = 0; i < 10; i++){
        cout << i; 
        arr[i] = i;
        v.push_back(i);
    }
    cout << std::endl;

    //Auto
    for (auto & val : v){ //Reference
        cout << val * 10;
    }
    cout << std::endl;

    for (auto val : v){ //Makes copy for value
        cout << val * 10;
    }
    cout << std::endl;

    //While
    int i = 0;
    while (i != v.size()){
        i++;
    }

    //Do While
    std::string input;
    do{
        cout << "input 'q': " << std::endl;
    }
    while(input != "q");
}

void sampleEnum(){
    //EnumToString
    Weather weather = Weather::rainy;
    switch(weather){
        case Weather::sunny:
            cout << "Sunny" << std::endl;
            break;
        case Weather::rainy:
            cout << "Rainy" << std::endl;
            break;
        case Weather::cloudy:
            cout << "Cloudy" << std::endl;
            break;
        case Weather::cold:
            cout << "Cold" << std::endl;
            break;
        case Weather::snowy:
            cout << "Snowy" << std::endl;
            break;
    }

    //Get the int from enum
    cout << "Value of enum " << static_cast<int>(weather) << std::endl;
}

void sampleConst(const int& y){ //Const parameter so can't be chaged
    int a = 5, b = 6;

    const int x = 10; //Cant change value
    const int* p = &a; //Pointer to const int
    int* const q = &a; //Const pointer to int
    const int* const r = &a; //Const pointer to const int
}

void sampleCast(){
    float x = 2.2;

    //Static cast conversion
    int y = static_cast<int>(x); 

    //Dynamic cast conversion. If cast fails returns nullptr
    BaseCar* carPtr1 = new ElectricCar(5, 10); 
    ElectricCar* electricCarPtr1 = dynamic_cast<ElectricCar*>(carPtr1);

    // BaseCar* carPtr2 = new BaseCar(5, 10); 
    // ElectricCar* electricCarPtr2 = dynamic_cast<ElectricCar*>(carPtr2); //Nullptr

    //const cast removes the const qualifier from the ptr
    const int* yptr = &y;
    int* ptry = const_cast<int*>(yptr);

    //reinterpret cast does bit reinterpretation
    int n = 50;
    char* charPtr = reinterpret_cast<char*>(&n); //First byte of int as a char
}

void sampleString(){
    string val1 = "Hello ", val2 = "World", val3 = "1", val4;

    //Concatenation
    val4 = val1 + val2 + "!!!";
    cout << "String concat " << val4 << std::endl;

    //String to int
    int x = std::stoi(val3);
    cout << "Str to int " << x << std::endl;

    //Int to string
    string val5 = std::to_string(x);
    cout << "int to str " << val5 << std::endl;

    //Find string index
    int val6 = val4.find("World"); //Find string from start, idx
    int val6 = val4.rfind("World"); //Find string from end, idx
    if (val6 == string::npos){
        cout << "Substring not found" << std::endl;
    }

    //Find substring
    string sub = val4.substr(6,11);

    //Find first or last char of given chars
    string s = "hello world";
    cout << s.find_first_of("aeiou") << std::endl; // 1 ('e')
    cout << s.find_last_of("aeiou") << std::endl;  // 7 ('o')    
}

void sampleArray(){
    int arr1[] = {1,2,3,4,5,6,7,8,9};
    int* arr2 = new int[10];

    for(int i = 0; i < 10; i++){
        arr2[i] = i;
    }

    for (auto & val : arr1){ //Auto only valid for reg arrays not from 'new' as those are pointers
        cout << val << std::endl;
    }

    int* ptr = arr2;
    for (;ptr < arr2+10; ptr++){
        cout << *ptr << std::endl;
    }
    delete[] arr2;
}

void sampleVectorStack(){
    //Vector usage
    std::vector<std::vector<int>> grid;
    std::vector<int> row1;
    std::vector<int> row2;
    std::vector<int> row3;
    std::vector<int> extra;

    for (int i = 0; i < 10; i++){
        row1.push_back(i);
        row2.push_back(i+10);
        row3.push_back(i+100);
        extra.push_back(i);
    }
    grid.push_back(row1);
    grid.push_back(row2);
    grid.push_back(row3);

    //Get size of vector
    int gridSize = 0, rowSize = 0;
    gridSize = grid.size();
    rowSize = row1.size();
    cout << "Grid size: " << gridSize << " Row size: " << rowSize << std::endl;
    cout << "Grid at (0,0): " << grid[0][0] << std::endl;

    //Auto loop
    for (auto val : row1){
        cout << val << std::endl;
    }

    //Insert & Erase
    extra.insert(extra.begin()+1, 99); //Insert value 99 at index 1
    extra.erase(extra.begin() + 2); //Remove value at index 2

    //Stack usage
    std::vector<int> stack;
    stack.push_back(0);
    stack.push_back(1);
    stack.push_back(2);
    stack.push_back(3);
    stack.push_back(4);
    stack.push_back(5);

    //Get value and pop off stack
    int top = stack.back();
    stack.pop_back();
}

void sampleMap(){
    std::map<string, int> m;
    std::unordered_map<string, int> um;

    //Insert elements
    m["Apple"] = 5;
    m.insert({"orange", 8});

    //Access 
    m.at("apple");

    //Iteration
    for (auto& [key, val] : m){
        cout << key << " -> " << val << std::endl;
    }

    //Find
    if (m.find("banana") == m.end()){
        cout << "No banana found" << std::endl;
    }

    //Erase
    m.erase("orange");

    //Size
    m.size();
}

void sampleSet(){
    std::set<int> s;
    s.insert(5);
    s.insert(6);
    s.insert(7);
    s.insert(8);
    s.insert(9);

    //Loop through set
    for (auto & val : s){
        cout << " " << val << " ";
    }
    cout << std::endl;

    //Check existance
    if (s.count(7)){
        cout << "7 is in the set" << std::endl;
    }

    //Remove value
    s.erase(8);
     
    //Get size
    int sz = s.size();
}

void sampleDeque(){
    //Declaration
    std::deque<int> dq;

    //Insert
    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);
    dq.push_back(4);
    dq.push_back(5);
    dq.push_back(6);

    //Loop through dq values
    for (auto & val : dq){
        cout << val << " ";
    }
    cout << std::endl;

    //Get value at front or end
    int front = dq.front();
    int back = dq.back();

    //Removing values from front and end
    dq.pop_back();
    dq.pop_front();

    //Loop through elements
    for (auto val : dq){
        cout << val << " ";
    }
    cout << std::endl;

    //Get the size
    int sz = dq.size();
}   

void sampleStack(){
    std::stack<int> stack;

    //Insert
    stack.push(10);
    stack.push(15);

    //Get value at top of stack
    cout << stack.top() << std::endl;

    //Pop value from stack
    stack.pop(); 
}

void sampleSmartPointers(){
    //unique_ptr -> Desctructor called when owner ptr is out of scope
    std::unique_ptr<ElectricCar> u1 = std::make_unique<ElectricCar>(5, 10);
    int plate = u1->getLicensePlate();

    std::unique_ptr<ElectricCar> u2;
    //u2 = u1; //This gives an error as it cannot transfer ownership due to uniqueness
    u2 = std::move(u1); //Transfer ownership using move

    if (!u1){
        cout << "unique ptr 1 is now empty" << std::endl;
    }

    //shared_ptr -> Descturctor called when all owner ptrs are out of scope
    std::shared_ptr<ElectricCar> s1 = std::make_shared<ElectricCar>(10, 15);
    
    std::shared_ptr<ElectricCar> s2 = s1;

    //Num of pointers that share reference to same address
    cout << "Ref count = " << s1.use_count() << std::endl;

    //Completely depricated in c++11, 2011 & removed in c++ 17, 2017
    //auto_ptr -> Destructor is called when owner is out of scope
    // std::auto_ptr<ElectricCar> a1(new ElectricCar(20,25));
    
    // std::auto_ptr<ElectricCar> a2 = a1; //Ownership was transfered silently

    // //Check ownership
    // if (!a1.get()){
    //     cout << "a1 lost ownership" << std::endl;
    // }

    // plate = a2->getLicensePlate;
}