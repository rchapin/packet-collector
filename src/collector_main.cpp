#include <libconfig.h++>
#include <iostream>
#include <string>
// #include <boost/log/core.hpp>
// #include <boost/log/trivial.hpp>
// #include <boost/log/expressions.hpp>

#include "../include/collector.hpp"

/**
 * Initialize the logging implementation instance
 */
boost_logger initLogger(char* configPath) {

	libconfig::Config cfg;
	try {
		cfg.readFile(configPath);
	} catch (const libconfig::FileIOException &fioex) {
		std::cerr << "I/O error while reading cfg file " << configPath << std::endl;
		// return false;
	} catch (const libconfig::ParseException &pex) {
		std::cerr	<< "Parse error in cfg file at " << pex.getFile() << ":" << pex.getLine()
			<<  " - " << pex.getError() << std::endl;
		// return false;
	}

	std::string logPath;
	if (cfg.lookupValue("logging.file", logPath)) {
		// logging::add_file_log(logPath);


	} else {
		std::cerr << "No log file specified!" << std::endl;
	}

	// Instantiate our boost_logger instance
	boost_logger logger;
	logger.init(logPath);

//	severity_lgr_t* logger = boost_lgr.getLogger();
//	BOOST_LOG_SEV(*logger, INFO) << "From collector_main";
// 	BOOST_LOG_SEV(*logger, WARN) << "Warning!";
	return (logger);							   
}

int main(int argc, char* argv[]) {

     	// Check that we received the minimum number of arguments
	// Should be [path-to-config-file [optional: LOGLEVEL]]
	if ( argc != 2 ) {
		printf("Missing proper number of arguments\n");
		//
		// TODO:	print a usage message
		//
		return -1;
	}

	// Path to config file
	char* configPath = argv[1];
	printf("Using config file = %s\n", configPath);

	boost_logger logger = initLogger(configPath);
	severity_lgr_t* severity_logger = logger.getLogger();

 	packet_collector::collector *collector = new packet_collector::collector(configPath, severity_logger);
 	collector->init();

	delete collector;

	return 0;
}

