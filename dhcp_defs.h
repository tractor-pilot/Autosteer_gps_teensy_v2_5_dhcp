typedef struct DHCP_MSG {
    byte		op;
    byte		htype;
    byte		hlen;
    byte		hops;
    uint32_t	xid;
    uint16_t	secs;
#define DHCP_FLAG_BROADCAST (0x8000)
    uint16_t	flags;
    byte		ciaddr[4];  // Client IP
    byte		yiaddr[4];  // Your IP
    byte		siaddr[4];  // Server IP
    byte		giaddr[4];  // Gateway IP
    byte		chaddr[16]; // Client hardware address (zero padded)
    byte		sname[64];
    byte		file[128];
#define DHCP_MAGIC (0x63825363)
        byte    	magic[4];
    byte		OPT[]; 
};

#define DHCP_MESSAGE_SIZE	576    

#define	DHCP_SERVER_PORT	67	
#define DHCP_CLIENT_PORT	68

#define DHCP_BOOTREQUEST	1
#define DHCP_BOOTREPLY		2

/* DHCP message type */
#define	DHCP_DISCOVER		1
#define DHCP_OFFER		  2
#define	DHCP_REQUEST		3
#define	DHCP_DECLINE		4
#define	DHCP_ACK		    5
#define DHCP_NAK		    6
#define	DHCP_RELEASE		7
#define DHCP_INFORM		  8

enum {
    dhcpPadOption =	0,
    dhcpSubnetMask =	1,
    dhcpTimerOffset	=	2,
    dhcpRoutersOnSubnet	=	3,
    dhcpTimeServer =	4,
    dhcpNameServer =5,
    dhcpDns	=	6,
    dhcpLogServer	=	7,
    dhcpCookieServer =	8,
    dhcpLprServer	=	9,
    dhcpImpressServer		=	10,
    dhcpResourceLocationServer	=	11,
    dhcpHostName	=	12,
    dhcpBootFileSize		=	13,
    dhcpMeritDumpFile		=	14,
    dhcpDomainName			=	15,
    dhcpSwapServer			=	16,
    dhcpRootPath			=	17,
    dhcpExtentionsPath		=	18,
    dhcpIPforwarding		=	19,
    dhcpNonLocalSourceRouting	=	20,
    dhcpPolicyFilter		=	21,
    dhcpMaxDgramReasmSize		=	22,
    dhcpDefaultIPTTL		=	23,
    dhcpPathMTUagingTimeout		=	24,
    dhcpPathMTUplateauTable		=	25,
    dhcpIfMTU		=	26,
    dhcpAllSubnetsLocal	=	27,
    dhcpBroadcastAddr	=	28,
    dhcpPerformMaskDiscovery	=	29,
    dhcpMaskSupplier		=	30,
    dhcpPerformRouterDiscovery	=	31,
    dhcpRouterSolicitationAddr	=	32,
    dhcpStaticRoute	=	33,
    dhcpTrailerEncapsulation	=	34,
    dhcpArpCacheTimeout		=	35,
    dhcpEthernetEncapsulation	=	36,
    dhcpTcpDefaultTTL		=	37,
    dhcpTcpKeepaliveInterval	=	38,
    dhcpTcpKeepaliveGarbage		=	39,
    dhcpNisDomainName	=	40,
    dhcpNisServers	=	41,
    dhcpNtpServers	=	42,
    dhcpVendorSpecificInfo		=	43,
    dhcpNetBIOSnameServer		=	44,
    dhcpNetBIOSdgramDistServer	=	45,
    dhcpNetBIOSnodeType	=	46,
    dhcpNetBIOSscope	=	47,
    dhcpXFontServer	=	48,
    dhcpXDisplayManager	=	49,
    dhcpRequestedIPaddr	=	50,
    dhcpIPaddrLeaseTime	=	51,
    dhcpOptionOverload	=	52,
    dhcpMessageType		=	53,
    dhcpServerIdentifier	=	54,
    dhcpParamRequest =	55,
    dhcpMsg	=	56,
    dhcpMaxMsgSize	=	57,
    dhcpT1value	=	58,
    dhcpT2value	=	59,
    dhcpClassIdentifier	=	60,
    dhcpClientIdentifier =	61,
    dhcpEndOption	=	255
};
