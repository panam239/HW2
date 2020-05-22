#include <boost/algorithm/string.hpp>

#include "address.h"

const std::array<char, 16> hex{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

bool Address::cmp(const Address* addr1, const Address* addr2) {
    for(uint8_t i = 0; i < std::min(addr1->values.size(), addr2->values.size()); i++) {
        if(addr1->values.at(i) != addr2->values.at(i)) {
            return addr1->values.at(i) >= addr2->values.at(i);
        }
    }
    return addr1->values.size() >= addr2->values.size();
}

std::string strFromLine(const std::string& str) {
    auto space = str.find_first_of('\t');
    return str.substr(0, space);
}

std::string intToHexString(int val)
{
    if(val == 0) return "0";
    std::string res = "";
    while(true) {
        res = hex.at(val % 16) + res;
        val >>= 4;
        if(val == 0) break;
    }
    return res;
}

Address *createAddress(const std::string &str)
{
    if(str.find('.') != std::string::npos){
        return new Ipv4(str);
    }
    else if(str.find(':') != std::string::npos){
        return new Ipv6(str);
    } else {
        throw Address::InvaidInitString(str);
    }
}

int stringToInt(const std::string &val, uint8_t base)
{
    if(base > 16 || base < 2) {
        return -1;
    }
    int res = 0;
    int multiplier = 1;
    for(int8_t i = val.length() - 1; i >= 0; i--) {
        int tmpVal = 0;
        bool found = false;
        for(uint8_t j = 0; j < base; j++) {
            if(hex.at(j) == val.at(i)) {
                tmpVal = j;
                found =  true;
                break;
            }
        }
        if(!found) return -1;
        res += tmpVal * multiplier;
        multiplier *= base;
    }
    return res;
}


Address::Address(const std::string &)
{

}

bool Address::isFiltered(const std::vector<int>& mask) const
{
        if(mask.size() > values.size()) return false;
        for(uint8_t i = 0; i < mask.size(); i++) {
            if(mask.at(i) != values.at(i)) return false;
        }
        return true;
}

bool Address::isContains(const int value) const
{
    for(unsigned int i = 0; i < values.size(); i++) {
        if(value == values.at(i)) return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, Address* addr)
{
    out << addr->toString();
    return out;
}

Ipv4::Ipv4(const std::string& str) : Address(str) {
    values.reserve(4);
    std::vector<std::string> strList;
    boost::split(strList, str, boost::is_any_of("."));
    if(strList.size() != 4) {
        throw InvaidInitString(str);
    }
    for(auto a : strList) {
        int octet = stringToInt(a, 10);
        if(octet > 255 || octet < 0) {
            throw InvaidInitString(str);
        }
        values.push_back(octet);
    }
}

std::string Ipv4::toString() const
{
    auto str = std::to_string(values.at(0));
    for(uint8_t i = 1; i < values.size(); i++) {
        str += "." + std::to_string(values.at(i));
    }
    return str;
}

Ipv6::Ipv6(const std::string &str) : Address(str)
{
    std::vector<std::string> strList;
    values.resize(8);
    for(auto &a:values) {
        a = 0;
    }
    boost::split(strList, str, boost::is_any_of(":"));
    if(strList.size() > 8 || strList.size() < 3) {
        throw InvaidInitString(str);
    }
    bool hasSpace = false;
    for(uint8_t  i = 0; i < strList.size(); i++) {
        if(strList.at(i) == "") {
            hasSpace = true;
            break;
        }
        int value = stringToInt(strList.at(i), 16);
        if(value > 1 << 16 || value < 0) {
            throw InvaidInitString(str);
        }
        values.at(i) = value;
    }
    if(hasSpace) {
        for(uint8_t i = strList.size() - 1; true; i--) {
            if(strList.at(i) == "") {
                break;
            }
            values.at(i + 8 - strList.size()) = stringToInt(strList.at(i), 16);
        }
    } else if(strList.size() != 8) {
        throw InvaidInitString(str);
    }
}

std::string Ipv6::toString() const
{
    auto str = intToHexString(values.at(0));
    for(uint8_t i = 1; i < values.size(); i++) {
        str += ":" + intToHexString(values.at(i));
    }
    return str;
}
