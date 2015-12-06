#include <fstream>
#include <iostream>
#include <string>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/empty_deleter.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>

#include "../include/boost_logger.hpp"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;

// Output format for our backend sinks:
// Need to add thread id to the log output
// Take a look at http://www.boost.org/doc/libs/1_54_0/libs/log/example/bounded_async_log/main.cpp
//    << expr::attr< boost::thread::id >("ThreadID")
#define LOG_OUTPUT_FORMAT \
  expr::stream \
    << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") \
    << ": (" << logging::trivial::severity \
    << ") " << expr::smessage


boost_logger::boost_logger() {}


void boost_logger::init(std::string logFilePath) {
  std::cout << "From  boost_logger.init(), "
    << "logFilePath = " << logFilePath << std::endl;

  this->logFilePath = logFilePath;

  //
  // Set up the stdout/console backend and frontend
  //
  // Get a shared pointer to the logging core
  this->core = boost::log::core::get();

  // Create a backend for stdout/console output
  boost::shared_ptr<sinks::text_ostream_backend> stdout_backend =
          boost::make_shared< sinks::text_ostream_backend >();

  stdout_backend->add_stream(
        boost::shared_ptr< std::ostream >(&std::clog, logging::empty_deleter()));

  // Enable auto-flushing after each log record is written
  stdout_backend->auto_flush(true);

  // Set up a synchronized frontend for the stdout_backend and register it with
  // the logging core.
  sink_sync_txt_ostream = new sink_sync_txt_ostream_t(stdout_backend);
  boost::shared_ptr<sink_sync_txt_ostream_t> stdout_sink(sink_sync_txt_ostream);

  stdout_sink->set_formatter(LOG_OUTPUT_FORMAT);
  this->core->add_sink(stdout_sink);

  //
  // Set up the file backend and frontend
  //
  // Create a backend for logging to a file
  boost::shared_ptr<sinks::text_file_backend> file_backend = 
    boost::make_shared<sinks::text_file_backend>(
      keywords::file_name = this->logFilePath,
      // Rotate at 5MB
      keywords::rotation_size = 5 * 1024 * 1024,
      // ... or every day at the beginning of the day
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
    );

  // Enable the auto-flushing after each log record is written
  file_backend->auto_flush(true);

  // Set up a synchronized frontend for the file_backend and register it with
  // the logging core.
  sink_sync_txt_file = new sink_sync_txt_file_t(file_backend);
  boost::shared_ptr<sink_sync_txt_file_t> file_sink(sink_sync_txt_file);
  
  // file_sink->set_formatter(&my_formatter);
  file_sink->set_formatter(LOG_OUTPUT_FORMAT);
  this->core->add_sink(file_sink);


  boost::log::add_common_attributes();

  // Set the log level for the core
  this->core->set_filter(
    logging::trivial::severity >= logging::trivial::info
  );

  BOOST_LOG_SEV(this->logger, INFO) << CLASS_NAME
    << "boost_logger initialized, writing to " << this->logFilePath;
}

severity_lgr_t* boost_logger::getLogger() {
  return (&this->logger);
}

