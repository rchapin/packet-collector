#include <string>

#include <boost/log/core.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>

typedef boost::log::trivial::severity_level severity_lvl_t;
typedef boost::log::sources::severity_logger<severity_lvl_t> severity_lgr_t;

#define	INFO boost::log::trivial::info
#define	WARN boost::log::trivial::warning
#define	ERROR boost::log::trivial::error
#define	FATAL boost::log::trivial::fatal

class boost_logger {

	private:
		std::string logFilePath;
		boost::shared_ptr<boost::log::core> core;
		severity_lgr_t logger;

	public:
		void init(std::string logFilePath);
		severity_lgr_t* getLogger();

}; 

