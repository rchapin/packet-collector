#include <libconfig.h++>
#include <iostream>

#include "../include/Collector.hpp"

int main(int argc, char *argv[]) {

 	// Check that we received the correct number of arguments
	// Should be [path-to-config-file]
	if ( argc != 2 ) {
		printf("Missing proper number of arguments\n");
		//
		// TODO:	print a usage message
		//
		return -1;
	}

	// Path to config file

	char *configPath = argv[1];
	std::cout << "Using config file = " << configPath << std::endl;

	PacketCollector::Collector::Collector *collector = new PacketCollector::Collector(configPath);
	collector->init();

}

// ============================================================================
// PacketCollector Class implemention:
//

namespace PacketCollector {

	using std::cout;
	using std::endl;

	// --------------------------------------------------------------------
	// Constructor/Destructors:
	//
	Collector::Collector(char *configPath) {
		cout << "Collector constructor, configPath = " << configPath << endl;

		this->configPath = configPath;
	}

	// ~Collector::Collector() {}
	
	// --------------------------------------------------------------------
	// Accessor/Mutators:
	//


	// --------------------------------------------------------------------
	// Member Functions:
	//

	void Collector::init() {
		cout << "From init()" << endl;
	}

}


