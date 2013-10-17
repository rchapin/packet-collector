/**
 * Configurations for pcap instances
 */
struct pcap_configs {

	/**
	 * Should this instance automatically start sniffing packets on
	 * invocations to pcap.writerReady
	 */
	bool startOnWriterReady;
};
