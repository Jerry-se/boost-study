#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
namespace sinks = boost::log::sinks;

using namespace std;

void createModuleOneSink() {
  boost::shared_ptr<logging::core> core = logging::core::get();

  boost::shared_ptr<sinks::text_file_backend> backend =
    boost::make_shared<sinks::text_file_backend>(
      keywords::file_name = "logs/ModuleOne_%Y-%m-%d_%H-%M-%S_%N.log",
      keywords::rotation_size = 5 * 1024 * 1024,
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(
        12, 0, 0)
      );

  typedef sinks::synchronous_sink<sinks::text_file_backend> sink_t;
  boost::shared_ptr<sink_t> sink(new sink_t(backend));
  sink->set_formatter(
    expr::stream
    << expr::format_date_time<boost::posix_time::ptime>(
    "TimeStamp", "%Y-%m-%d %H:%M:%S")
    << ": <"
    << logging::trivial::severity
    << "> "
    << expr::attr<string>("Channel")
    << ":"
    << expr::smessage);

  sink->set_filter(expr::attr<string>("Channel") == "module one" &&
    logging::trivial::severity >= logging::trivial::warning);
  core->add_sink(sink);
}


void createModuleTwoSink() {
  boost::shared_ptr<logging::core> core = logging::core::get();

  boost::shared_ptr<sinks::text_file_backend> backend =
    boost::make_shared<sinks::text_file_backend>(
      keywords::file_name = "logs/ModuleTwo_%Y-%m-%d_%H-%M-%S_%N.log",
      keywords::rotation_size = 5 * 1024 * 1024,
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(
        12, 0, 0)
      );

  typedef sinks::synchronous_sink<sinks::text_file_backend> sink_t;
  boost::shared_ptr<sink_t> sink(new sink_t(backend));
    sink->set_formatter(
    expr::stream
    << expr::format_date_time<boost::posix_time::ptime>(
    "TimeStamp", "%Y-%m-%d %H:%M:%S")
    << ": <"
    << logging::trivial::severity
    << "> "
    << expr::attr<string>("Channel")
    << ":"
    << expr::smessage);

  sink->set_filter(expr::attr<string>("Channel") == "module two");
  core->add_sink(sink);
}


int main(int, char*[]) {
  createModuleOneSink();
  createModuleTwoSink();

  logging::add_common_attributes();

  using namespace logging::trivial;

  logging::core::get()->set_filter
    (
      logging::trivial::severity >= logging::trivial::info
    );

  src::severity_channel_logger<severity_level, // the type of the severity level
  std::string> moduleOneLogger(keywords::channel = "module one");
  src::severity_channel_logger<severity_level, // the type of the severity level
  std::string> moduleTwoLogger(keywords::channel = "module two");

  BOOST_LOG_SEV(moduleOneLogger, trace)<< "A trace severity message";
  BOOST_LOG_SEV(moduleOneLogger, debug)<< "A debug severity message";
  BOOST_LOG_SEV(moduleOneLogger, info)<< "An informational severity message";
  BOOST_LOG_SEV(moduleOneLogger, warning)<< "A warning severity message";
  BOOST_LOG_SEV(moduleOneLogger, error)<< "An error severity message";
  BOOST_LOG_SEV(moduleOneLogger, fatal)<< "A fatal severity message";

  BOOST_LOG_SEV(moduleTwoLogger, info)<< "An informational severity message";
  BOOST_LOG_SEV(moduleTwoLogger, fatal)<< "An informational severity message";
  BOOST_LOG_SEV(moduleOneLogger, trace)<< "A trace severity message";

  return 0;
}
