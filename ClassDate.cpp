#include<iostream>
#include<map>
#include<string>
#include<iomanip>
#include<sstream>
#include<set>
#include<exception>

class Date {
public:
    int GetYear() const { return year; }
    int GetMonth() const { return month; }
    int GetDay() const { return day; }

    Date(){}
    Date(int d, int m, int y){
        day = d;
        month = m;
        year = y;
    }

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs){
    std::string left, right;
    std::stringstream streamLeft, streamRight;
    streamLeft.fill('0');
    streamRight.fill('0');
    streamLeft << std::setw(4) << lhs.GetYear() << std::setw(2) << lhs.GetMonth() << std::setw(2) << lhs.GetDay();
    streamRight << std::setw(4) << rhs.GetYear() << std::setw(2) << rhs.GetMonth() << std::setw(2) << rhs.GetDay();
    std::getline(streamLeft, left);
    std::getline(streamRight, right);
    return left > right; // change sign to <
}

class Database {
public:
    void AddEvent(const Date& date, const std::string& event){
        DateBase[date].insert(event);
    }

    bool DeleteEvent(const Date& date, const std::string& event){
        if(DateBase.at(date).count(event) == 1) {
            DateBase[date].erase(event);
            return true;
        }
        return false;
    }

    int DeleteDate(const Date& date){
        int eventCount = DateBase.at(date).size();
        DateBase.erase(date);
        return eventCount;
    }

    void Find(const Date& date) const{
        for(const auto& elem : DateBase.at(date)){
            std::cout << elem << '\n';
        }
    }

    void Print() const{
        std::cout.fill('0');
        for(const auto& elem : DateBase){
            for(const auto& event : elem.second){
                std::cout << std::setw(4) << elem.first.GetDay() << '-' << std::setw(2) << elem.first.GetMonth() << '-' << std::setw(2) << elem.first.GetYear() << ' ' << event << '\n';
            }
        }
    }

private:
    std::map<Date, std::set<std::string>> DateBase;
};

int WriteToVariable(std::stringstream& in, int dataField){
    char symbol;
    while(std::isdigit(in.peek())){
        symbol = in.peek();
        dataField = dataField * 10 + (symbol - 48);
        in.ignore(1);
    }
    return dataField;
}

Date ReadFunction(std::string& inputString){
    char s1 = 0, s2 = 0;
    std::stringstream inputStringStream(inputString);
    const std::string errString = "Wrong date format: ";
    int inputYear = 0, inputMonth = 0, inputDay = 0;
    if(inputString.find('-') == std::string::npos) throw std::invalid_argument(errString + inputString);
    if(!std::isdigit(inputStringStream.peek()) && inputStringStream.peek() != ' ' && inputStringStream.peek() != '-') throw std::invalid_argument(errString + inputString);
    char minus = inputStringStream.peek();
    if(minus == '-') inputStringStream.ignore(1);
    inputYear = WriteToVariable(inputStringStream, inputYear);
    if(minus == '-') inputYear *= -1;
    if(inputStringStream.peek() != '-'){
        std::cout << inputStringStream.peek();
        throw std::invalid_argument(errString + inputString);
    }
    inputStringStream >> s1;
    if(!std::isdigit(inputStringStream.peek()) && inputStringStream.peek() != '+' && inputStringStream.peek() != '-') throw std::invalid_argument(errString + inputString);
    minus = inputStringStream.peek();
    if(minus == '-') inputStringStream.ignore(1);
    if(inputStringStream.peek() == '+') inputStringStream.ignore(1);
    inputMonth = WriteToVariable(inputStringStream, inputMonth);
    if(minus == '-') inputMonth *= -1;
    if(inputStringStream.peek() != '-') throw std::invalid_argument(errString + inputString);
    inputStringStream >> s2;
    if(!std::isdigit(inputStringStream.peek()) && inputStringStream.peek() != '+'  && inputStringStream.peek() != '-') throw std::invalid_argument(errString + inputString);
    minus = inputStringStream.peek();
    if(minus == '-') inputStringStream.ignore(1);
    if(inputStringStream.peek() == '+') inputStringStream.ignore(1);
    inputDay = WriteToVariable(inputStringStream, inputDay);
    if(minus == '-') inputDay *= -1;
    if(!inputStringStream.eof() && inputStringStream.peek() != ' ') throw std::invalid_argument(errString + inputString);

    //if(inputYear > 9999 || inputYear < 0) throw std::exception();
    if(inputMonth > 12 || inputMonth <= 0) throw std::invalid_argument("Month value is invalid: " + std::to_string(inputMonth));
    if(inputDay > 31 || inputDay <= 0) throw std::invalid_argument("Day value is invalid: " + std::to_string(inputDay));
    return {inputYear, inputMonth, inputDay};
}


int main() {
    Database db;

    std::string command;
    while (getline(std::cin, command)) {
        try {
            std::string com, name, date;
            std::stringstream in(command);
            Date d;
            in >> com;

            if(com == "Add"){
                try {
                    try {
                        in >> date >> name;
                        d = ReadFunction(date);
                        if(!name.empty()){
                            db.AddEvent(d, name);
                        }
                    } catch (std::exception& e){
                        std::cout << e.what() << '\n';
                        break;
                    }
                } catch (std::exception& e){}
            }

            else if(com == "Del"){
                try {
                    in >> date;
                    d = ReadFunction(date);
                } catch (std::exception& e){
                    std::cout << e.what() << '\n';
                    break;
                }
                if(!in.eof()){
                    try{
                        in >> name;
                        if(db.DeleteEvent(d, name)) std::cout << "Deleted successfully" << '\n';
                        else std::cout << "Event not found" << '\n';
                    } catch (std::exception& e) {
                        std::cout << "Event not found" << '\n';
                    }
                } else{
                    try {
                        int count = db.DeleteDate(d);
                        std::cout << "Deleted " << count << " events" << '\n';
                    } catch (std::exception& e){
                        std::cout << "Deleted 0 events" << '\n';
                    }
                }
            }

            else if(com == "Find"){
                try {
                    try {
                        in >> date;
                        d = ReadFunction(date);
                    } catch (std::exception& e){
                        std::cout << e.what() << '\n';
                        break;
                    }
                    db.Find(d);
                } catch (std::exception& e){}
            }

            else if (com == "Print")db.Print();

            else if(!command.empty()){
                try {
                    throw std::invalid_argument("Unknown command: " + com);
                } catch (std::exception& e){
                    std::cout << e.what() << '\n';
                    break;
                }
            }
        } catch (std::exception& e){}
    }

    return 0;
}