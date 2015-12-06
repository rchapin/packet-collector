#include "pcap_configs.hpp"

/**
 * Packet capture class utilizing libpcap
 */
class pcap {

private:
  int x, y;

  pcap_configs conf;

public:
  void setValues(int a, int b);

};
