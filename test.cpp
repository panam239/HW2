#define BOOST_TEST_MODULE unit_test

#include <boost/test/unit_test.hpp>

#include "filters.h"
#include "lib.h"

BOOST_AUTO_TEST_SUITE(unit_test)

BOOST_AUTO_TEST_CASE(test_valid_version) {
    BOOST_CHECK(version() > 0);

}

BOOST_AUTO_TEST_CASE(test_initialization) {
    BOOST_CHECK_THROW(createAddress(""), Address::InvaidInitString);

    BOOST_CHECK_THROW(createAddress("11"), Address::InvaidInitString);
    BOOST_CHECK_THROW(createAddress(".."), Address::InvaidInitString);
    BOOST_CHECK_THROW(createAddress(".11"), Address::InvaidInitString);
    BOOST_CHECK_THROW(createAddress("11.22"), Address::InvaidInitString);
    BOOST_CHECK_THROW(createAddress("11.11.11.11.11"), Address::InvaidInitString);
    BOOST_CHECK_THROW(createAddress("11.11.11.300"), Address::InvaidInitString);
    BOOST_CHECK_NO_THROW(createAddress("11.11.11.11"));

    BOOST_CHECK_THROW(createAddress(":"), Address::InvaidInitString);
    BOOST_CHECK_THROW(createAddress("1:2:3:4:5"), Address::InvaidInitString);
    BOOST_CHECK_THROW(createAddress("1:2:3:4:5:6:7:8:9"), Address::InvaidInitString);
    BOOST_CHECK_THROW(createAddress("a:b:c:d:e:f:g:h"), Address::InvaidInitString);
    BOOST_CHECK_THROW(createAddress("a:b:c:d:e:f:ff:fffff"), Address::InvaidInitString);
    BOOST_CHECK_NO_THROW(createAddress("::"));
    BOOST_CHECK_NO_THROW(createAddress("1::"));
    BOOST_CHECK_NO_THROW(createAddress("::1"));
    BOOST_CHECK_NO_THROW(createAddress("1::1"));
    BOOST_CHECK_NO_THROW(createAddress("1::1:1"));
    BOOST_CHECK_NO_THROW(createAddress("ffff:eeee:dddd:cccc:bbbb:aaaa:9999:8888"));
}

BOOST_AUTO_TEST_CASE(test_text_format) {
    BOOST_CHECK_EQUAL(stringToInt("1111", 1), -1);
    BOOST_CHECK_EQUAL(stringToInt("11", 2), 3);
    BOOST_CHECK_EQUAL(stringToInt("1f", 16), 31);
    BOOST_CHECK_EQUAL(stringToInt("1f", 15), -1);
    BOOST_CHECK_EQUAL(stringToInt("1f", 17), -1);

    BOOST_CHECK_EQUAL(intToHexString(1), "1");
    BOOST_CHECK_EQUAL(intToHexString(0), "0");
    BOOST_CHECK_EQUAL(intToHexString(15), "f");
    BOOST_CHECK_EQUAL(intToHexString(16), "10");
    BOOST_CHECK_EQUAL(intToHexString(321425), "4e791");
}

BOOST_AUTO_TEST_CASE(test_compare) {
    Address* a = createAddress("1.2.3.4");
    Address* b = createAddress("1:2:3:4::");
    BOOST_CHECK(Address::cmp(b,a));
    delete a;
    delete b;

    a = createAddress("1.2.3.5");
    b = createAddress("1:2:3:4::");
    BOOST_CHECK(Address::cmp(a,b));
    delete a;
    delete b;

    a = createAddress("1.2.3.4");
    b = createAddress("1:2:3:5::");
    BOOST_CHECK(Address::cmp(b,a));
    delete a;
    delete b;
}


}
