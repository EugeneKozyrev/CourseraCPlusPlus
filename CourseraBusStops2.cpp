#include <iostream>
#include <map>
#include <vector>
#include <algorithm>


int main(int argc, char const *argv[]){
    int a;
    std::cin >> a;
    std::map<std::vector<std::string>, int> bus_route_revers;
    std::vector<std::string> temp_vector;
    int counter = 0;

    for(int i = 0; i < a; ++i){
        int b;
        std::cin >> b;
        std::string stop;
        int check = 1;
        for(int j = 1; j <= b; ++j){
            std::cin >> stop;
            temp_vector.push_back(stop);
        }
        counter++;
        for(auto& item : bus_route_revers){
            if(temp_vector == item.first){
                std::cout << "Already exists for " << item.second << std::endl;
                check = 0;
                counter--;
                temp_vector.clear();
            }
        }
        if(check){
            bus_route_revers[temp_vector] = counter;
            std::cout << "New bus " << counter << std::endl;
            temp_vector.clear();
        }

    }
    return 0;
}