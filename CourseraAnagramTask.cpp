#include <iostream>
#include <map>

void PrintMap (const std::map<char, int>& m){
    for(const auto& [key, val]: m){
        std::cout << key <<  " : "  << val << std::endl;
    }
}

bool IsAnagram(std::string first, std::string second){
    if(first.size() != second.size()) return false;
    std::map<char, int> m;
    for (const auto& i : first){
        ++m[i];
    }
    std::map<char, int> n;
    for (const auto& i : second){
        ++n[i];
    }
    return m == n;
}

int main(int argc, char const *argv[]){
    int t;
    std::string first, second;
    std::cin >> t;
    for(int i = 0; i < t; ++i){
        std::cin >> first >> second;
        if(IsAnagram(first, second))
            std::cout << "YES" << '\n';
        else
            std::cout << "NO" << '\n';
    }

    return 0;
}