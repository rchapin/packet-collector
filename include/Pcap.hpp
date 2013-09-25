#include "PcapConfigs.hpp"

/**
 * Packet capture class utilizing libpcap
 */
class Pcap {

private:
	int x, y;

	PcapConfigs conf;

public:
	void setValues(int a, int b);

};
