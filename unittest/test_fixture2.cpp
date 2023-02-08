#define BOOST_TEST_MODULE MyFixtureTest
#include <boost/test/included/unit_test.hpp>
#include <iostream>

/* 3) Global fixture */
struct MyConfig {
    MyConfig() : g_i( 0 )
    {
        instance() = this;
        std::cout << "global setup\n";
    }
    ~MyConfig()
    {
        std::cout << "g_i: " << g_i << std::endl;
        std::cout << "global teardown\n";
    }
    static MyConfig *&instance();
    int g_i;
};
BOOST_GLOBAL_FIXTURE(MyConfig);

MyConfig *&MyConfig::instance()
{
    static MyConfig *s_inst = 0;
    return s_inst;
}

/* 1) Per test case fixture */
struct F {
    F() : i( 0 ) { std::cout << "setup fixture\n"; }
    ~F()         { std::cout << "teardown fixture\n"; }
    int i;
};
BOOST_FIXTURE_TEST_CASE( test_case1, F )
{
    BOOST_CHECK( i == 1 );  // failed: i == 0
    ++i;
}
BOOST_FIXTURE_TEST_CASE( test_case2, F )
{
    BOOST_CHECK_EQUAL( i, 0 );  // pass: i == 0
    ++(MyConfig::instance()->g_i);
}
BOOST_AUTO_TEST_CASE( test_case3 )
{
    BOOST_CHECK( true );
    std::cout << "g_i: " << MyConfig::instance()->g_i << std::endl;
}

/* 2) Test suite level fixture */
BOOST_FIXTURE_TEST_SUITE( test_suite1, F )
BOOST_AUTO_TEST_CASE( test_case1 )
{
    BOOST_CHECK( i == 1 );  // failed: i == 0
    ++i;
}
BOOST_AUTO_TEST_CASE( test_case2 )
{
    BOOST_CHECK_EQUAL( i, 0 );  // pass: i == 0
    ++(MyConfig::instance()->g_i);
}
BOOST_AUTO_TEST_SUITE_END()
