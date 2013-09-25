#include <iostream>
#include <libconfig.h++>

namespace PacketCollector {

	class Collector {

	private:
	       char *configPath;
	       libconfig::Config cfg;

	public:
		/**
		 * Constructor.
		 * @param[in]	configPath	The path to the configuration file.
		 */
		Collector(char *configPath);

		~Collector();

		// --------------------------------------------------------------------
		// Accessor/Mutators:
		//

		// --------------------------------------------------------------------
		// Member Functions:
		//

		/**
		 * Initializes the instance.  Can be invoked multiple times.
		 * Subsequent calls to init() trigger invocations to shutdown, and
		 * destruction to all child instances.
		 */
		void init();

		bool reloadConfigs();

	};
}
