
//#include <iostream>
//#include <string>
//#include <vector>
//#include <array>
#include <algorithm>

#include "filters.h"

int main()
{
    std::vector<Address*> ip_pool;

    for(std::string line; std::getline(std::cin, line);)
    {
        try {
            Address* v = createAddress(strFromLine(line));
            ip_pool.push_back(v);
        }
        catch(Address::InvaidInitString& err) {
            std::cout << err.what() << std::endl;
            continue;
        }
    }

    std::sort(ip_pool.begin(), ip_pool.end(), Address::cmp);
    std::cout << "filter" << std::endl;
    filter(ip_pool);
    std::cout << "filter 1" << std::endl;
    filter(ip_pool, 1);
    std::cout << "filter 46 70" << std::endl;
    filter(ip_pool, 46, 70);
    std::cout << "filter any 46" << std::endl;
    filter_any(ip_pool, 46);

    for(auto a:ip_pool) {
        delete a;
    }

    return 0;
}
