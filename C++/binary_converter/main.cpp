#include <iostream>
#include <bitset>

auto printBinary(const int n) -> void {

    int numberOfBits = 8;
    size_t size = sizeof(int);

    unsigned int bitmask = (1 << (numberOfBits    * size -1));
    for(int i = 0; i < size * numberOfBits; ++i) {
        if((n & bitmask) != 0) {
            std::cout << '1';
        }
        else {
            std::cout << '0';
        }
    
        bitmask = (bitmask >> 1);
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cout << "Enter any number : ";
    std::cin >> n;
    printBinary(n);
}