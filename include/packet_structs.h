// Ethernet headers are always 14 bytes	
#define	ETH_HDR_LEN	14

#define ETH_ADDR_LEN	6

//
// IPv4 Internet address
//
struct in_addr_ipv4 {
	union {
		struct {
			u_char oct1;	// First octect, and so forth
			u_char oct2;
			u_char oct3;
			u_char oct4;
		} four_chars;

		struct {
			u_short s_h;	// High short
			u_short s_low;	// Low short
		} two_shorts;

		u_long one_long;	// Entire 4 bytes as a long

	};
};

//
// TODO:	Need to flesh out the implementation of this data structure
//		Right now it's just a placeholder to contain the 32 bits in
//		the header.
// TCP header Sequence number 
struct tcp_seq {
	long seq_num;
};

//
// TODO:	Need to flesh out the implementation of this data structure
//		Right now it's just a placeholder to contain the 32 bits in
//		the header.
// TCP header acknowledgement number
struct tcp_ack {
	long ack_num;
};

//
// Ethernet Header
//
struct eth_header {
	u_char	desthost[ETH_ADDR_LEN];		// Destination host
	u_char	sourcehost[ETH_ADDR_LEN];	// Source host
	u_short	type;				// IP, ARP, RARP, etc . . . 
};

//
// IP Header
//
struct ip_header {
	// version << 4 | header length >> 2 (? >> 4)
	// version = 4 bits
	// header length = # of 32-bit words in the header
	u_char	vers_hdr_len;
	
	// Type of service
	u_char	type_of_service;	

	// Differentiated Services Code Point << 6 | Explicit Congestion Notification >> 2
	// ECN, is only supported when both endpoints support it and are willing
	// to use it, and only effective when supported by underlying network.
	u_char	ip_dscp_ecn;
	bool	ecn_support;

	u_short	len;	// Total length
	u_short	offset;	// Fragement offset field
	
#define IP_RF 	0x8000;	// Reserved fragment flag
#define IP_DF	0x4000;	// Don't fragment flag
#define IP_MF	0x2000;	// More fragments flag

	u_char	ttl;	 // Time to live
	u_char	protocol;

	struct in_addr_ipv4 source, dest;	// Source and destination addresses

};

#define	IP_HDR_LENGTH(ip)	(((ip)->vers_hdr_len) & 0x0f)
#define	IP_VERSION(ip)		(((ip)->vers_hdr_len) >> 4)

//
// TCP Header
//
struct tcp_header {
	u_short	source_port;	// Source port
	u_short	dest_port;	// Destination port
	tcp_seq	sequence_num;	// Sequence number
	tcp_ack	ack_num;	// Acknowledgement number
	u_short	offset_rsvd;	// Data offset, reserved

# define TH_OFF(th)	(((th)->offset_rsvd & 0xf0) >> 4)

	u_char	flags;

#define TH_FIN	0x01
#define TH_SYN	0x02
#define TH_RST	0x04
#define TH_PUSH	0x08
#define TH_ACK	0x10
#define TH_URG	0x20
#define TH_ECE	0x40
#define TH_CWR	0x80
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)

	u_short	window;		// Window
	u_short	checksum;	// Checksum
	u_short	urg_pntr;	// Urgent pointer

};
