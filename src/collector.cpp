#include <libconfig.h++>
#include <iostream>

#include "../include/collector.hpp"

// ============================================================================
// Packetcollector Class implemention:
//

namespace packet_collector {

  // TODO:  Clean this up and use proper namespace declarations
  using std::cout;
  using std::endl;
  using std::cerr;
  using std::string;
  using libconfig::Config;
  using libconfig::FileIOException;
  using libconfig::ParseException;
  using libconfig::SettingNotFoundException;
  using libconfig::Setting;


  // --------------------------------------------------------------------
  // Constructor/Destructors:
  //
  collector::collector(char *configPath, severity_lgr_t* logger) {
    this->logger = logger;
    BOOST_LOG_SEV(*logger, INFO) << CLASS_NAME
      << "From collector constructor, configPath = " << configPath;

    this->configPath = configPath;
  }

  collector::~collector() {
    BOOST_LOG_SEV(*logger, INFO) << CLASS_NAME << "From collector destructor";
    this->shutdown();
  }
  
  // --------------------------------------------------------------------
  // Accessor/Mutators:
  //

  unsigned long long int collector::getMemMaxSize() const { return _memMaxSize; }

   void collector::setMemMaxSize(unsigned long long int memMaxSize) { _memMaxSize = memMaxSize; }

  unsigned long long int collector::getMemWarnSize() const { return _memWarnSize; }

   void collector::setMemWarnSize(unsigned long long int memWarnSize) { _memWarnSize = memWarnSize; }

  // --------------------------------------------------------------------
  // Member Functions:
  //

  void collector::init() {
    BOOST_LOG_SEV(*logger, INFO) << CLASS_NAME << "From collector.init()";

    // Shutdown running PacketWriters and Pcaps

        bool cfgLoaded = loadConfigs();
    if (cfgLoaded) {
      BOOST_LOG_SEV(*logger, INFO) << CLASS_NAME << "Successfully loaded configs, continuing...";
    } else {
      BOOST_LOG_SEV(*logger, FATAL) << CLASS_NAME << "Config not loaded, exiting....";
    }
    
  }

  bool collector::loadConfigs() {
    BOOST_LOG_SEV(*logger, INFO) << CLASS_NAME << "From loadConfigs()";

    try {
      cfg.readFile(this->configPath);

    } catch (const FileIOException &fioex) {
      BOOST_LOG_SEV(*logger, ERROR) << CLASS_NAME << "I/O error while reading cfg file " << this->configPath;
      return false;
    } catch (const ParseException &pex) {
      BOOST_LOG_SEV(*logger, ERROR) << CLASS_NAME << "Parse error in cfg file at " << pex.getFile()
        << ":" << pex.getLine() <<  " - " << pex.getError();
      return false;
    }

    const Setting& rootSetting = cfg.getRoot();

    try {
      string configVersion;
      if (cfg.lookupValue("configVersion", configVersion)) {
        // Check that the version of the configuration matches
        // that of the software.
        if (configVersion != collector::configVersion) {
          BOOST_LOG_SEV(*logger, ERROR) << CLASS_NAME << "\t! configVersions do not match.\n\t"
            << this->configPath << " = " << configVersion
            << " whereas the current version required is "
            << collector::configVersion;
          return false;
        }

      } else {

        BOOST_LOG_SEV(*logger, ERROR) << CLASS_NAME << "\t! Unable to read 'configVersion' cfg. "
          << "Check that is is specified property and matches the collector version";
        return false;
      }

      // If we have not yet returned, we have verified that
      // this config file is compatible with this version of
      // the software.

      unsigned long long int maxSize;
      if (cfg.lookupValue("memory.maxSize", maxSize)) {
        BOOST_LOG_SEV(*logger, INFO) << CLASS_NAME << "memory.maxSize = " << maxSize;
        this->setMemMaxSize(maxSize);
      } else {
        BOOST_LOG_SEV(*logger, ERROR) << "\t! Unable to read 'memory.maxSize'. "
          << "Check that it is specified as a proper long long int";
      }

      unsigned long long int warnSize;
      if (cfg.lookupValue("memory.warnSize", warnSize)) {
        BOOST_LOG_SEV(*logger, INFO) << CLASS_NAME << "memory.warnSize = " << warnSize;
        this->setMemWarnSize(warnSize);
      } else {
        BOOST_LOG_SEV(*logger, ERROR) << CLASS_NAME << "\t! Unable to read 'memory.warnSize'. "
          << "Check that it is specified as a proper long long int";
      }

    } catch (SettingNotFoundException &snfex) {
      BOOST_LOG_SEV(*logger, ERROR) << CLASS_NAME << "Setting not found " << snfex.what();
    }

    return true;
  }

  void collector::shutdown() {
    BOOST_LOG_SEV(*logger, INFO) << CLASS_NAME << "From shutdown()" << endl;
  }
}

const std::string packet_collector::collector::configVersion = "0.1";

