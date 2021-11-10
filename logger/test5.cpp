#include <stdexcept>
#include <string>
#include <iostream>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_multifile_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/support/date_time.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

// Global logger declaration
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::severity_logger_mt<logging::trivial::severity_level>)

#define TASK_LOG(taskid, message, severity) \
  do { \
    BOOST_LOG_SCOPED_LOGGER_TAG(my_logger::get(), "TaskID", taskid); \
    BOOST_LOG_SEV(my_logger::get(), severity) << message; \
  } while(0)
#define TASK_LOG_TRACE(taskid, message)    TASK_LOG(taskid, message, logging::trivial::trace)
#define TASK_LOG_DEBUG(taskid, message)    TASK_LOG(taskid, message, logging::trivial::debug)
#define TASK_LOG_INFO(taskid, message)     TASK_LOG(taskid, message, logging::trivial::info)
#define TASK_LOG_WARNING(taskid, message)  TASK_LOG(taskid, message, logging::trivial::warning)
#define TASK_LOG_ERROR(taskid, message)    TASK_LOG(taskid, message, logging::trivial::error)
#define TASK_LOG_FATAL(taskid, message)    TASK_LOG(taskid, message, logging::trivial::fatal)

void init_logging() {
  auto sink = logging::add_file_log
    (
      //attribute
      keywords::file_name = "logs/matrix_core_%Y%m%d%H%M%S_%N.log",
      keywords::target = "logs",
      keywords::max_files = 10,
      keywords::rotation_size = 100 * 1024 * 1024,
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
      keywords::format = (
        expr::stream
          << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%m-%d %H:%M:%S.%f")
          << "|" << expr::attr< attrs::current_thread_id::value_type>("ThreadID")
          << "|" << std::setw(7) << std::setfill(' ') << std::left << logging::trivial::severity
          << "|" << expr::smessage)
    );
  logging::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
  sink->locked_backend()->auto_flush(true);

  // logging::core::get()->set_exception_handler(
  //   logging::make_exception_handler<std::runtime_error, std::logic_error>(log_exception_handler())
  // );

  logging::add_common_attributes();
}

void add_multifile_logging() {
  try {
    boost::shared_ptr< logging::core > core = logging::core::get();

    boost::shared_ptr< sinks::text_multifile_backend > backend =
      boost::make_shared< sinks::text_multifile_backend >();

    // Set up the file naming pattern
    backend->set_file_name_composer
    (
      sinks::file::as_file_name_composer(expr::stream << "logs/" << expr::attr< std::string >("TaskID") << ".log")
    );

    // Wrap it into the frontend and register in the core.
    // The backend requires synchronization in the frontend.
    typedef sinks::synchronous_sink< sinks::text_multifile_backend > sink_t;
    boost::shared_ptr< sink_t > sink(new sink_t(backend));

    // Set the formatter
    sink->set_formatter
    (
      expr::stream
        << "["
        << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
        << "] [TaskID: " << expr::attr< std::string >("TaskID")
        << "] [" << std::setw(7) << std::setfill(' ') << std::left << logging::trivial::severity
        << "] "
        << expr::smessage
    );
    sink->set_filter(expr::has_attr("TaskID"));
    // sink->locked_backend()->auto_flush(true);
    core->add_sink(sink);
  }
  catch (...) {
    std::cout << "log error" << std::endl;
  }
}

void thread_func() {
  for (int i = 0; i < 10; ++i) {
    if (i % 2 == 0) {
      TASK_LOG_INFO("aaa", "thread func " << i);
    }
    else {
      TASK_LOG_INFO("bbb", "thread func " << i);
    }
  }
}

int main(int argc, char* argv[]) {
  init_logging();
  add_multifile_logging();
  BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
  BOOST_LOG_TRIVIAL(info) << "An informational severity message";
  BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
  BOOST_LOG_TRIVIAL(error) << "An error severity message";
  BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";
  {
    BOOST_LOG_SCOPED_LOGGER_TAG(my_logger::get(), "TaskID", "aaa");
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::trace) << "A trace severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::debug) << "A debug severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::info) << "An informational severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::warning) << "A warning severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::error) << "An error severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::fatal) << "A fatal severity message";
  }
  {
    BOOST_LOG_SCOPED_LOGGER_TAG(my_logger::get(), "TaskID", "bbb");
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::trace) << "A trace severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::debug) << "A debug severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::info) << "An informational severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::warning) << "A warning severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::error) << "An error severity message";
    BOOST_LOG_SEV(my_logger::get(), logging::trivial::fatal) << "A fatal severity message";
  }
  boost::thread t1(thread_func);
  t1.join();
  // TASK_LOG_TRACE("bbb", "A trace severity message");
  // TASK_LOG_DEBUG("bbb", "A debug severity message");
  // TASK_LOG_INFO("bbb", "An informational severity message");
  // TASK_LOG_WARNING("bbb", "A warning severity message");
  // TASK_LOG_ERROR("bbb", "An error severity message");
  // TASK_LOG_FATAL("bbb", "A fatal severity message");
  return 0;
}
