#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

void PrintRightBusOrder(std::vector<std::string>& bus_order, std::vector<std::string>& bus_in_scope){
    for(auto elem : bus_order){
        for(auto item : bus_in_scope){
            if(elem == item) std::cout << item << ' ';
        }
    }
}

void BUSES_FOR_STOP(const std::map<std::string, std::vector<std::string>>& bus_route, std::string& stop, std::vector<std::string>& bus_order){
    int check = 0;
    std::vector<std::string> bus_in_scope;
    for(auto item : bus_route){
        for(auto elem : item.second){
            if(elem == stop){
                bus_in_scope.push_back(item.first);
                check++;
            }
        }
    }
    PrintRightBusOrder(bus_order, bus_in_scope);
    if(check == 0) std::cout << "No stop";
    std::cout << std::endl;
}

void NEW_BUS(std::map<std::string, std::vector<std::string>>& bus_route, std::string& bus, std::vector<std::string>& stops, std::vector<std::string>& bus_order){
    bus_route[bus] = stops;
    bus_order.push_back(bus);
}

void STOPS_FOR_BUS(std::map<std::string, std::vector<std::string>>& bus_route, std::string& bus, std::vector<std::string>& bus_order){
    std::vector<std::string> bus_in_scope;
    if(bus_route.count(bus)){
        for(auto elem : bus_route[bus]){
            std::cout << "Stop " << elem << ": ";
            int check = 0;
            bus_in_scope.clear();
            for(auto item : bus_route){
                if(item.first != bus){
                    for(auto i : item.second){
                        if(i == elem){
                            bus_in_scope.push_back(item.first);
                            check++;
                        }
                    }
                }
            }
            PrintRightBusOrder(bus_order, bus_in_scope);
            if(check == 0) std::cout << "no interchange";
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "No bus" << std::endl;
    }
}

void ALL_BUSES(std::map<std::string, std::vector<std::string>>& bus_route){
    if(bus_route.empty()){
        std::cout << "No buses" << std::endl;
    } else {
        for( auto& item : bus_route){
            std::cout << "Bus " << item.first << ": ";
            for(auto& elem : item.second){
                std::cout << elem << ' ';
            }
            std::cout << std::endl;
        }
    }
}

int main(int argc, char const *argv[]){
    int a;
    std::cin >> a;
    std::string command;
    std::map<std::string, std::vector<std::string>> bus_route;
    std::vector<std::string> bus_order;
    for(int i = 0; i < a; ++i){
        std::cin >> command;
        if(command == "BUSES_FOR_STOP"){
            std::string stop ;
            std::cin >> stop ;
            BUSES_FOR_STOP(bus_route, stop, bus_order);
        } else if (command == "STOPS_FOR_BUS"){
            std::string bus;
            std::cin >> bus;
            STOPS_FOR_BUS(bus_route, bus, bus_order);
        } else if(command == "NEW_BUS"){
            std::string bus;
            int stop_count;
            std::string stop;
            std::cin >> bus >> stop_count;
            std::vector<std::string> bus_stop;
            for(int i = 0; i < stop_count; ++i){
                std::cin >> stop;
                bus_stop.push_back(stop);
            }
            NEW_BUS(bus_route, bus, bus_stop, bus_order);
        } else if(command == "ALL_BUSES"){
            ALL_BUSES(bus_route);
        }
    }
    return 0;
}