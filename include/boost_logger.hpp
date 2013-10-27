#include <string>

#include <boost/log/core.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/shared_ptr.hpp>

typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> sink_sync_txt_ostream_t;
typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_file_backend> sink_sync_txt_file_t;
typedef boost::log::trivial::severity_level severity_lvl_t;
typedef boost::log::sources::severity_logger<severity_lvl_t> severity_lgr_t;

#define	INFO boost::log::trivial::info
#define	WARN boost::log::trivial::warning
#define	ERROR boost::log::trivial::error
#define	FATAL boost::log::trivial::fatal

#ifdef CLASS_NAME
#undef CLASS_NAME
#endif
#define	CLASS_NAME "[boost_logger] "

class boost_logger {

	private:
		/**
		 * Path to the log file on the local file system.
		 */
		std::string logFilePath;

		boost::shared_ptr<boost::log::core> core;
		severity_lgr_t logger;
		sink_sync_txt_ostream_t* sink_sync_txt_ostream;
		sink_sync_txt_file_t* sink_sync_txt_file;

	public:

		boost_logger();
		
		/**
		 * Initialized the boost_logger instance instantiating the underlying
		 * boost::log logging implementation. 
		 */ 
		void init(std::string logFilePath);

		// --------------------------------------------------------------------
		// Accessor/Mutators:
		//
		/**
		 *
		 */
		severity_lgr_t* getLogger();

}; 

