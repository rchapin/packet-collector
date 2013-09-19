#include <iostream>
#include <stdio.h>
#include <pcap.h>

#include "../include/packet_structs.h"

int main(int argc, char *argv[])
{

   char *dev = argv[1];
   printf("Device: %s\n", dev);

   char errbuf[PCAP_ERRBUF_SIZE];

   pcap_t *pcap_handle;
   pcap_handle = pcap_open_live(dev, 2048, 1, 1000, errbuf);
   if (pcap_handle == 0) {
      printf("pcap_handle is null, exiting");
      return 1;
   } else {
		// printf("pcap_handle = %s\n", pcap_handle);
	}

	// Compiled filter expression
	struct bpf_program bpf;

	// Filter expression
	char filter_exp[] = "port 80";

	// Netmask of sniffing device
	bpf_u_int32 mask;

	// IP of our sniffing device
	bpf_u_int32 net;

	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		 fprintf(stderr, "Can't get netmask for device %s\n", dev);
		 net = 0;
		 mask = 0;
	 }
	printf("net = %d, mask = %d\n", net, mask);

	// Compile the filter
	int pcap_compile_retval = pcap_compile(pcap_handle, &bpf, filter_exp, 0, net);
	printf("pcap_compile_retval = %d\n", pcap_compile_retval);

	// Apply the filter
	int pcap_setfilter_retval = pcap_setfilter(pcap_handle, &bpf);
	printf("pcap_setfilter_retval = %d\n", pcap_setfilter_retval);

	// Grab a packet
	const u_char *packet;

	// The header that pcap gives us for the packet
	struct pcap_pkthdr header;
	packet = pcap_next(pcap_handle, &header);

	// Print the length of the packet
	printf("Packet's length is [%d]\n", header.len);

	// Close the session
	pcap_close(pcap_handle);

	return 0;
}
