#include <iostream>
#include <map>

void DUMP (const std::map<std::string, std::string>& m){
    if(m.empty())
        std::cout << "There are no countries in the world" << std::endl;
    else{
        for(const auto& item: m){
            std::cout << item.first <<  "/"  << item.second << " ";
        }
    }
    std::cout << std::endl;
}

void ABOUT(std::map<std::string, std::string>& m, std::string& str){
    if(m.count(str)){
        std::cout << "Country " << str << " has capital " << m[str] << std::endl;
    } else {
        std::cout << "Country " << str << " doesn't exist" << std::endl;
    }
}

void RENAME(std::map<std::string, std::string>& m, std::string& old_country_name, std::string& new_country_name){
    if(m.count(new_country_name)){
        std::cout << "Incorrect rename, skip" << std::endl;
    }
    else if(!m.count(old_country_name)){
        std::cout << "Incorrect rename, skip" << std::endl;
    }
    else if((m.count(old_country_name)) && (new_country_name == m[old_country_name])){
        std::cout << "Incorrect rename, skip" << std::endl;
    } else {
        std::cout << "Country " << old_country_name <<  " with capital " << m[old_country_name] << " has been renamed to " << new_country_name << std::endl;
        m[new_country_name] = m[old_country_name];
        m.erase(old_country_name);
    }
}

void CHANGE_CAPITAL(std::map<std::string, std::string>& m, std::string& country, std::string& new_capital){
    if(!m.count(country)){
        std::cout << "Introduce new country " << country << " with capital " << new_capital << std::endl;
        m.emplace(country, new_capital);
    } else if(m[country] == new_capital){
        std::cout << "Country " << country << " hasn't changed its capital" << std::endl;
    } else if(m.count(country) && (m[country] != new_capital)){
        std::cout << "Country " << country << " has changed its capital from " << m[country] << " to " << new_capital << std::endl;
        m[country] = new_capital;
    }
}

int main(int argc, char const *argv[]){
    int a;
    std::cin >> a;
    std::string command;
    std::map<std::string, std::string> datebook;
    for(int i = 0; i < a; ++i){
        std::cin >> command;
        if(command == "CHANGE_CAPITAL"){
            std::string country, new_capital;
            std::cin >> country >> new_capital;
            CHANGE_CAPITAL(datebook, country, new_capital);
        } else if (command == "RENAME"){
            std::string old_country_name, new_country_name;
            std::cin >> old_country_name >> new_country_name;
            RENAME(datebook, old_country_name, new_country_name);
        } else if(command == "ABOUT"){
            std::string country;
            std::cin >> country;
            ABOUT(datebook, country);
        } else if(command == "DUMP"){
            DUMP(datebook);
        }
    }
    return 0;
}
