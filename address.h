#pragma once

#include <string>
#include <vector>
//#include <iostream>

class Address {
public:
    Address(const std::string&);
    virtual ~Address(){}
    virtual std::string toString() const = 0;
    bool isFiltered(const std::vector<int>&) const;
    bool isContains(const int) const;
    friend std::ostream& operator<<(std::ostream& out, Address* addr);
    static bool cmp(const Address* addr1, const Address* addr2);

    class InvaidInitString: public std::logic_error {
    public:
        InvaidInitString(const std::string& input):
            std::logic_error("Address " + input + " is invalid") { }
    };

    std::vector<int> values;
};


Address* createAddress(const std::string& str);

std::string strFromLine(const std::string& str);
std::string intToHexString(int val);
int stringToInt(const std::string& val, uint8_t base);

class Ipv4 : public Address {
public:
    Ipv4(const std::string&);
    ~Ipv4() override{}
    std::string toString() const override;
};

class Ipv6 : public Address {
public:
    Ipv6(const std::string&);
    ~Ipv6() override{}
    std::string toString() const override;
};


