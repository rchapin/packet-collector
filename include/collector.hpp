#include <iostream>
#include <libconfig.h++>
#include <string>

#include "boost_logger.hpp"

namespace packet_collector {

	class collector {

	private:
		/**
		 * Pointer to a boost severity logger
		 */
		severity_lgr_t* logger;

		char *configPath;
		
		libconfig::Config cfg;
		/**
	         * Maximum number of bytes of memory that the program can consume
		 */
		unsigned long long int _memMaxSize;

		 /**
		 * Memory usage threshold, at which, we will start throwing out
		 * warnings.
		 */ 
		unsigned long long int _memWarnSize;

	        /**
	         * Current number of bytes of memory consumed by the program
		 */
		unsigned long long int memCurrSize;


	public:

		/**
		 * Configuration file version that this version of the software
		 * supports.  If there is a mis-match between the value that is
		 * specified in the .cpp file and that in the config file the
		 * program will not run.
		 */
		const static std::string configVersion;

		/**
		 * Constructor.
		 * @param[in]	configPath	The path to the configuration file.
		 */
		collector(char *configPath, severity_lgr_t* logger);

		~collector();

		// --------------------------------------------------------------------
		// Accessor/Mutators:
		//

		unsigned long long int getMemMaxSize() const;

		void setMemMaxSize(unsigned long long int memMaxSize);

		unsigned long long int getMemWarnSize() const;

		void setMemWarnSize(unsigned long long int memWarnSize); 

		// --------------------------------------------------------------------
		// Member Functions:
		//

		/**
		 * Initializes the instance.  Can be invoked multiple times.
		 * Subsequent calls to init() trigger invocations to shutdown, and
		 * destruction of all child instances.
		 */
		void init();

		bool loadConfigs();

		void shutdown();

	};
}
