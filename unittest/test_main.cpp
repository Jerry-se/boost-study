// entry of the test
#define BOOST_TEST_MODULE "Custom command line arguments of boost unittest"
#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
#include <iostream>

using namespace boost::unit_test;

/*
// 关于程序的入口，boost test里是有已经定义了的main函数的，在 boost_1_54_0\boost\test\impl\unit_test_main.ipp中
int BOOST_TEST_CALL_DECL
main( int argc, char* argv[] )
{
    // prototype for user's unit test init function
#ifdef BOOST_TEST_ALTERNATIVE_INIT_API
    extern bool init_unit_test();

    boost::unit_test::init_unit_test_func init_func = &init_unit_test;
#else
    extern ::boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[] );

    boost::unit_test::init_unit_test_func init_func = &init_unit_test_suite;
#endif

    return ::boost::unit_test::unit_test_main( init_func, argc, argv );
}
*/

// https://www.boost.org/doc/libs/1_70_0/libs/test/doc/html/boost_test/runtime_config/custom_command_line_arguments.html
BOOST_AUTO_TEST_CASE(test_accessing_command_line)
{
  for (int i = 0; i < framework::master_test_suite().argc; i++) {
    std::cout << "framework::master_test_suite().argv[" << i << "]=" << framework::master_test_suite().argv[i] << std::endl;
  }
  BOOST_TEST_REQUIRE( framework::master_test_suite().argc == 3 );
  BOOST_TEST( framework::master_test_suite().argv[1] == "--specific-param" );
  BOOST_TEST( framework::master_test_suite().argv[2] == "'additional value with quotes'" );
  BOOST_TEST_MESSAGE( "'argv[0]' contains " << framework::master_test_suite().argv[0] );
}

// void free_test_function(int i) {
//   BOOST_CHECK(i < 4);
// }

// // 自定义init_unit_test_suite函数的时候不能定义宏BOOST_TEST_MODULE
// ::boost::unit_test::test_suite* init_unit_test_suite(int argc, char* argv[])
// {
//   std::cout << "hello" << std::endl;
//   for (int i = 0; i < argc; i++) {
//     std::cout << argv[i] << std::endl;
//   }
//   int params[] = {1, 2, 3, 4, 5};
//   boost::unit_test::framework::master_test_suite().add(BOOST_PARAM_TEST_CASE(&free_test_function, params, params + 5));
//   return 0;
// }
