#define BOOST_TEST_MAIN                 // 必须定义主测试套件，必须位于头文件之前
#include <boost/test/unit_test.hpp>
#include <boost/assign.hpp>
#include <iostream>
#include <vector>

struct global_fixture
{
  global_fixture() { std::cout << "global setup\n"; }
  ~global_fixture() { std::cout << "global teardown\n"; }
};
BOOST_TEST_GLOBAL_FIXTURE(global_fixture);      // 全局测试夹具

struct assign_fixture
{
  assign_fixture() { std::cout << "suit setup\n"; }
  ~assign_fixture() { std::cout << "suit teardown\n"; }

  std::vector<int> v;
  int param = 10;
};
BOOST_FIXTURE_TEST_SUITE(s_assign, assign_fixture)  // 测试套件的夹具

BOOST_AUTO_TEST_CASE(t_assign1)
{
  std::cout << "t_assign1 begin" << std::endl;
  using namespace boost::assign;
  v += 1, 2, 3, 4;
  BOOST_CHECK_EQUAL(v.size(), 4);
  BOOST_CHECK_EQUAL(v[2], 3);
  std::cout << "t_assign1 end" << std::endl;
}

BOOST_AUTO_TEST_CASE(t_assign2)
{
  std::cout << "t_assign2 begin" << std::endl;
  boost::assign::push_back(v)(10)(20)(30);
  BOOST_CHECK_EQUAL(v.size(), 3);
  BOOST_CHECK_EQUAL(v[2], 300);	// 预设错误
  std::cout << "t_assign2 end" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
