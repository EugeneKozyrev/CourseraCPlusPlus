#include<iostream>
#include<string>
#include<vector>
#include<cmath>

void ComeIn(std::vector<bool>& v, int k){
    for (int i = 0; i < k; ++i){
        v.push_back(false);
    }
}

void ComeOut(std::vector<bool>& v, int k){
    k = abs(k);
    for (int i = 0; i < k; ++i){
        v.pop_back();
    }
}

void Worry(std::vector<bool>& v, int k){
    v[k] = true;
}

void Quiet(std::vector<bool>& v, int k){
    v[k] = false;
}

void WorryCount(std::vector<bool>& v){
    int count = 0;
    for(auto w : v){
        if (w) count++;
    }
    std::cout << count << '\n';
}

int main(int argc, char const *argv[]){
    int q;
    std::cin >> q;
    std::vector<bool> queue;
    for(int i = 0; i < q; ++i){
        std::string command;
        int count;
        std::cin >> command;
        if (command == "COME"){
            std::cin >> count;
            if(count < 0) ComeOut(queue, count);
            else ComeIn(queue, count);
        } else if (command == "QUIET") {
            std::cin >> count;
            Quiet(queue, count);
        } else if (command == "WORRY") {
            std::cin >> count;
            Worry(queue, count);
        } else if (command == "WORRY_COUNT") {
            WorryCount(queue);
        }
    }
	return 0;
}