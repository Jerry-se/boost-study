#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/text_multifile_backend.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;

// Global logger declaration
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)

void init_logging()
{
  boost::shared_ptr< logging::core > core = logging::core::get();

  boost::shared_ptr< sinks::text_multifile_backend > backend =
    boost::make_shared< sinks::text_multifile_backend >();

  // Set up the file naming pattern
  backend->set_file_name_composer
  (
    sinks::file::as_file_name_composer(expr::stream << "logs/" << expr::attr< std::string >("RequestID") << ".log")
  );

  // Wrap it into the frontend and register in the core.
  // The backend requires synchronization in the frontend.
  typedef sinks::synchronous_sink< sinks::text_multifile_backend > sink_t;
  boost::shared_ptr< sink_t > sink(new sink_t(backend));

  // Set the formatter
  sink->set_formatter
  (
    expr::stream
      << "[RequestID: " << expr::attr< std::string >("RequestID")
      << "] " << expr::smessage
  );

  core->add_sink(sink);
}

void logging_function() {
  src::logger lg;
  BOOST_LOG(lg) << "Hello, world!";
  for (unsigned int i = 0; i < 10; ++i) {
    BOOST_LOG(lg) << "Log record " << i;
  }
}

int main(int argc, char* argv[]) {
  init_logging();
  {
    BOOST_LOG_SCOPED_LOGGER_TAG(my_logger::get(), "RequestID", "111111111111111");
    for (unsigned int i = 0; i < 10; ++i) {
      BOOST_LOG(my_logger::get()) << "Log record " << i;
    }
  }
  {
    BOOST_LOG_SCOPED_LOGGER_TAG(my_logger::get(), "RequestID", "222222222222222");
    for (unsigned int i = 0; i < 10; ++i) {
      BOOST_LOG(my_logger::get()) << "Log record " << i;
    }
  }
  // {
  //   BOOST_LOG_SCOPED_THREAD_TAG("RequestID", "Request1");
  //   logging_function();
  // }
  // {
  //   BOOST_LOG_SCOPED_THREAD_TAG("RequestID", "Request2");
  //   logging_function();
  // }
  return 0;
}
