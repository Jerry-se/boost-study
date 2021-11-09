#include <string>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

bool init_log_environment(std::string _cfg)
{
  namespace logging = boost::log;
  using namespace logging::trivial;

  // if (!boost::filesystem::exists("./log/"))
  // {
  //   boost::filesystem::create_directory("./log/");
  // }
  logging::add_common_attributes();

  logging::register_simple_formatter_factory<severity_level, char>("Severity");
  logging::register_simple_filter_factory<severity_level, char>("Severity");

  std::ifstream file(_cfg);
  try
  {
    logging::init_from_stream(file);
    std::cout << "init config success" << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cout << "init_logger is fail, read log config file fail. curse: " << e.what() << std::endl;
    exit(-2);
  }
  return true;
}

int main(int argc, char* argv[]) {
  init_log_environment("sinks.cfg");
  using namespace logging::trivial;
  src::severity_channel_logger<severity_level, std::string> scl(keywords::channel = "test4");
  // 按照日志级别写入日志
  BOOST_LOG_SEV(scl, trace) << __FUNCTION__ << ":" << __LINE__ << "|" << "A trace severity message";
  BOOST_LOG_SEV(scl, debug) << __FUNCTION__ << ":" << __LINE__ << "|" << "A debug severity message";
  BOOST_LOG_SEV(scl, info) << __FUNCTION__ << ":" << __LINE__ << "|" << "An informational severity message";
  BOOST_LOG_SEV(scl, warning) << __FUNCTION__ << ":" << __LINE__ << "|" << "A warning severity message";
  BOOST_LOG_SEV(scl, error) << __FUNCTION__ << ":" << __LINE__ << "|" << "An error severity message";
  BOOST_LOG_SEV(scl, fatal) << __FUNCTION__ << ":" << __LINE__ << "|" << "A fatal severity message";
  return 0;
}
