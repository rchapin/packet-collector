#include <iostream>
#include <stdio.h>
#include <pcap.h>
#include <string>
#include <sstream>
#include <libconfig.h++>

#include "../include/packet_structs.h"

/**
 * Callback invoked when pcap_loop returns a packet.
 */
void received_packet(u_char *args, const struct pcap_pkthdr *hdr, const u_char *packet);

int main(int argc, char *argv[]) {
            
  // Check that we received the correct number of arguments
  // Should be [device name] [num packets to collect]
  if ( argc != 3 ) {
    printf("Missing proper number of arguments\n");
    //
    // TODO:  print a usage message
    //
    return -1;
  }

  // Name of device to listen for packets
  char *dev = argv[1];
  printf("Device: %s\n", dev);

  // Number of packets to read before exiting
  std::stringstream input_str_strm;
  input_str_strm << argv[2];
  u_int num_pkts_to_capture;
  input_str_strm >> num_pkts_to_capture;
  printf("Reading %d number of packets\n", num_pkts_to_capture);

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



  /*
  // Grab a single packet
  const u_char *packet;

  // The header that pcap gives us for the packet
  struct pcap_pkthdr header;
  packet = pcap_next(pcap_handle, &header);

  // Print the length of the packet
  printf("Packet's length is [%d]\n", header.len);
  */



   pcap_loop(pcap_handle, num_pkts_to_capture, received_packet, NULL);


  pcap_freecode(&bpf);

  // Close the session
  pcap_close(pcap_handle);

  return 0;
}


void received_packet(u_char *args, const struct pcap_pkthdr *hdr, const u_char *packet) {

  const struct eth_header *hdr_eth;
  const struct ip_header *hdr_ip;
  const struct tcp_header *hdr_tcp;
  const char *payload;  // Pointer to the firt of the payload bytes

  u_int size_ip_hdr;
  u_int size_tcp_hdr;

  hdr_eth = (struct eth_header*)(packet);
  hdr_ip = (struct ip_header*)(packet + ETH_HDR_LEN);
  size_ip_hdr = IP_HDR_LENGTH(hdr_ip)*4;

  // TODO:   Make this constant a #define var
  if ( size_ip_hdr < 20 ) {
    printf("Invalid IP header length of %u bytes\n", size_ip_hdr);
  } else {
    printf("size_ip_hdr = %u\n", size_ip_hdr);
  }

  hdr_tcp = (struct tcp_header*)(packet + ETH_HDR_LEN + size_ip_hdr);
  size_tcp_hdr = TH_OFF(hdr_tcp)*4;
  if ( size_tcp_hdr < 20 ) {
    printf("Invalid TCP header length of %u bytes\n", size_tcp_hdr);
  } else {
    printf("size_tcp_hdr = %u bytes\n", size_tcp_hdr);
  }
  
  // payload = (u_char *)(packet + ETH_HDR_LEN + size_ip_hdr + size_tcp_hdr);              

}


