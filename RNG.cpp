#include <random>
#include <iostream>
#include <fstream>

/* refer to https://stackoverflow.com/questions/28115724/getting-big-random-numbers-in-c-c */

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    //std::uint64_t lowbound = 65536, upbound = 4294967295;
    std::uint64_t lowbound = 0, upbound = 65535;
    std::uniform_int_distribution<unsigned long long> dis(lowbound, upbound);

    std::fstream f;
    f.open("RNG.txt", std::ios::out | std::ios::trunc);
    for (size_t i = 0; i < 100000; ++i)
        f << dis(gen) << ' ' << dis(gen) << std::endl;

    f.close();
    return 0;
}
