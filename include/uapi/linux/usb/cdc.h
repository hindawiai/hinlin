<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * USB Communications Device Class (CDC) definitions
 *
 * CDC says how to talk to lots of dअगरferent types of network adapters,
 * notably ethernet adapters and various modems.  It's used mostly with
 * firmware based USB peripherals.
 */

#अगर_अघोषित __UAPI_LINUX_USB_CDC_H
#घोषणा __UAPI_LINUX_USB_CDC_H

#समावेश <linux/types.h>

#घोषणा USB_CDC_SUBCLASS_ACM			0x02
#घोषणा USB_CDC_SUBCLASS_ETHERNET		0x06
#घोषणा USB_CDC_SUBCLASS_WHCM			0x08
#घोषणा USB_CDC_SUBCLASS_DMM			0x09
#घोषणा USB_CDC_SUBCLASS_MDLM			0x0a
#घोषणा USB_CDC_SUBCLASS_OBEX			0x0b
#घोषणा USB_CDC_SUBCLASS_EEM			0x0c
#घोषणा USB_CDC_SUBCLASS_NCM			0x0d
#घोषणा USB_CDC_SUBCLASS_MBIM			0x0e

#घोषणा USB_CDC_PROTO_NONE			0

#घोषणा USB_CDC_ACM_PROTO_AT_V25TER		1
#घोषणा USB_CDC_ACM_PROTO_AT_PCCA101		2
#घोषणा USB_CDC_ACM_PROTO_AT_PCCA101_WAKE	3
#घोषणा USB_CDC_ACM_PROTO_AT_GSM		4
#घोषणा USB_CDC_ACM_PROTO_AT_3G			5
#घोषणा USB_CDC_ACM_PROTO_AT_CDMA		6
#घोषणा USB_CDC_ACM_PROTO_VENDOR		0xff

#घोषणा USB_CDC_PROTO_EEM			7

#घोषणा USB_CDC_NCM_PROTO_NTB			1
#घोषणा USB_CDC_MBIM_PROTO_NTB			2

/*-------------------------------------------------------------------------*/

/*
 * Class-Specअगरic descriptors ... there are a couple करोzen of them
 */

#घोषणा USB_CDC_HEADER_TYPE		0x00	/* header_desc */
#घोषणा USB_CDC_CALL_MANAGEMENT_TYPE	0x01	/* call_mgmt_descriptor */
#घोषणा USB_CDC_ACM_TYPE		0x02	/* acm_descriptor */
#घोषणा USB_CDC_UNION_TYPE		0x06	/* जोड़_desc */
#घोषणा USB_CDC_COUNTRY_TYPE		0x07
#घोषणा USB_CDC_NETWORK_TERMINAL_TYPE	0x0a	/* network_terminal_desc */
#घोषणा USB_CDC_ETHERNET_TYPE		0x0f	/* ether_desc */
#घोषणा USB_CDC_WHCM_TYPE		0x11
#घोषणा USB_CDC_MDLM_TYPE		0x12	/* mdlm_desc */
#घोषणा USB_CDC_MDLM_DETAIL_TYPE	0x13	/* mdlm_detail_desc */
#घोषणा USB_CDC_DMM_TYPE		0x14
#घोषणा USB_CDC_OBEX_TYPE		0x15
#घोषणा USB_CDC_NCM_TYPE		0x1a
#घोषणा USB_CDC_MBIM_TYPE		0x1b
#घोषणा USB_CDC_MBIM_EXTENDED_TYPE	0x1c

/* "Header Functional Descriptor" from CDC spec  5.2.3.1 */
काष्ठा usb_cdc_header_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__le16	bcdCDC;
पूर्ण __attribute__ ((packed));

/* "Call Management Descriptor" from CDC spec  5.2.3.2 */
काष्ठा usb_cdc_call_mgmt_descriptor अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__u8	bmCapabilities;
#घोषणा USB_CDC_CALL_MGMT_CAP_CALL_MGMT		0x01
#घोषणा USB_CDC_CALL_MGMT_CAP_DATA_INTF		0x02

	__u8	bDataInterface;
पूर्ण __attribute__ ((packed));

/* "Abstract Control Management Descriptor" from CDC spec  5.2.3.3 */
काष्ठा usb_cdc_acm_descriptor अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__u8	bmCapabilities;
पूर्ण __attribute__ ((packed));

/* capabilities from 5.2.3.3 */

#घोषणा USB_CDC_COMM_FEATURE	0x01
#घोषणा USB_CDC_CAP_LINE	0x02
#घोषणा USB_CDC_CAP_BRK		0x04
#घोषणा USB_CDC_CAP_NOTIFY	0x08

/* "Union Functional Descriptor" from CDC spec 5.2.3.8 */
काष्ठा usb_cdc_जोड़_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__u8	bMasterInterface0;
	__u8	bSlaveInterface0;
	/* ... and there could be other slave पूर्णांकerfaces */
पूर्ण __attribute__ ((packed));

/* "Country Selection Functional Descriptor" from CDC spec 5.2.3.9 */
काष्ठा usb_cdc_country_functional_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__u8	iCountryCodeRelDate;
	__le16	wCountyCode0;
	/* ... and there can be a lot of country codes */
पूर्ण __attribute__ ((packed));

/* "Network Channel Terminal Functional Descriptor" from CDC spec 5.2.3.11 */
काष्ठा usb_cdc_network_terminal_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__u8	bEntityId;
	__u8	iName;
	__u8	bChannelIndex;
	__u8	bPhysicalInterface;
पूर्ण __attribute__ ((packed));

/* "Ethernet Networking Functional Descriptor" from CDC spec 5.2.3.16 */
काष्ठा usb_cdc_ether_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__u8	iMACAddress;
	__le32	bmEthernetStatistics;
	__le16	wMaxSegmentSize;
	__le16	wNumberMCFilters;
	__u8	bNumberPowerFilters;
पूर्ण __attribute__ ((packed));

/* "Telephone Control Model Functional Descriptor" from CDC WMC spec 6.3..3 */
काष्ठा usb_cdc_dmm_desc अणु
	__u8	bFunctionLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubtype;
	__u16	bcdVersion;
	__le16	wMaxCommand;
पूर्ण __attribute__ ((packed));

/* "MDLM Functional Descriptor" from CDC WMC spec 6.7.2.3 */
काष्ठा usb_cdc_mdlm_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__le16	bcdVersion;
	__u8	bGUID[16];
पूर्ण __attribute__ ((packed));

/* "MDLM Detail Functional Descriptor" from CDC WMC spec 6.7.2.4 */
काष्ठा usb_cdc_mdlm_detail_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	/* type is associated with mdlm_desc.bGUID */
	__u8	bGuidDescriptorType;
	__u8	bDetailData[0];
पूर्ण __attribute__ ((packed));

/* "OBEX Control Model Functional Descriptor" */
काष्ठा usb_cdc_obex_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__le16	bcdVersion;
पूर्ण __attribute__ ((packed));

/* "NCM Control Model Functional Descriptor" */
काष्ठा usb_cdc_ncm_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__le16	bcdNcmVersion;
	__u8	bmNetworkCapabilities;
पूर्ण __attribute__ ((packed));

/* "MBIM Control Model Functional Descriptor" */
काष्ठा usb_cdc_mbim_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__le16	bcdMBIMVersion;
	__le16  wMaxControlMessage;
	__u8    bNumberFilters;
	__u8    bMaxFilterSize;
	__le16  wMaxSegmentSize;
	__u8    bmNetworkCapabilities;
पूर्ण __attribute__ ((packed));

/* "MBIM Extended Functional Descriptor" from CDC MBIM spec 1.0 errata-1 */
काष्ठा usb_cdc_mbim_extended_desc अणु
	__u8	bLength;
	__u8	bDescriptorType;
	__u8	bDescriptorSubType;

	__le16	bcdMBIMExtendedVersion;
	__u8	bMaxOutstandingCommandMessages;
	__le16	wMTU;
पूर्ण __attribute__ ((packed));

/*-------------------------------------------------------------------------*/

/*
 * Class-Specअगरic Control Requests (6.2)
 *
 * section 3.6.2.1 table 4 has the ACM profile, क्रम modems.
 * section 3.8.2 table 10 has the ethernet profile.
 *
 * Microsoft's RNDIS stack क्रम Ethernet is a venकरोr-specअगरic CDC ACM variant,
 * heavily dependent on the encapsulated (proprietary) command mechanism.
 */

#घोषणा USB_CDC_SEND_ENCAPSULATED_COMMAND	0x00
#घोषणा USB_CDC_GET_ENCAPSULATED_RESPONSE	0x01
#घोषणा USB_CDC_REQ_SET_LINE_CODING		0x20
#घोषणा USB_CDC_REQ_GET_LINE_CODING		0x21
#घोषणा USB_CDC_REQ_SET_CONTROL_LINE_STATE	0x22
#घोषणा USB_CDC_REQ_SEND_BREAK			0x23
#घोषणा USB_CDC_SET_ETHERNET_MULTICAST_FILTERS	0x40
#घोषणा USB_CDC_SET_ETHERNET_PM_PATTERN_FILTER	0x41
#घोषणा USB_CDC_GET_ETHERNET_PM_PATTERN_FILTER	0x42
#घोषणा USB_CDC_SET_ETHERNET_PACKET_FILTER	0x43
#घोषणा USB_CDC_GET_ETHERNET_STATISTIC		0x44
#घोषणा USB_CDC_GET_NTB_PARAMETERS		0x80
#घोषणा USB_CDC_GET_NET_ADDRESS			0x81
#घोषणा USB_CDC_SET_NET_ADDRESS			0x82
#घोषणा USB_CDC_GET_NTB_FORMAT			0x83
#घोषणा USB_CDC_SET_NTB_FORMAT			0x84
#घोषणा USB_CDC_GET_NTB_INPUT_SIZE		0x85
#घोषणा USB_CDC_SET_NTB_INPUT_SIZE		0x86
#घोषणा USB_CDC_GET_MAX_DATAGRAM_SIZE		0x87
#घोषणा USB_CDC_SET_MAX_DATAGRAM_SIZE		0x88
#घोषणा USB_CDC_GET_CRC_MODE			0x89
#घोषणा USB_CDC_SET_CRC_MODE			0x8a

/* Line Coding Structure from CDC spec 6.2.13 */
काष्ठा usb_cdc_line_coding अणु
	__le32	dwDTERate;
	__u8	bCharFormat;
#घोषणा USB_CDC_1_STOP_BITS			0
#घोषणा USB_CDC_1_5_STOP_BITS			1
#घोषणा USB_CDC_2_STOP_BITS			2

	__u8	bParityType;
#घोषणा USB_CDC_NO_PARITY			0
#घोषणा USB_CDC_ODD_PARITY			1
#घोषणा USB_CDC_EVEN_PARITY			2
#घोषणा USB_CDC_MARK_PARITY			3
#घोषणा USB_CDC_SPACE_PARITY			4

	__u8	bDataBits;
पूर्ण __attribute__ ((packed));

/* table 62; bits in multicast filter */
#घोषणा	USB_CDC_PACKET_TYPE_PROMISCUOUS		(1 << 0)
#घोषणा	USB_CDC_PACKET_TYPE_ALL_MULTICAST	(1 << 1) /* no filter */
#घोषणा	USB_CDC_PACKET_TYPE_सूचीECTED		(1 << 2)
#घोषणा	USB_CDC_PACKET_TYPE_BROADCAST		(1 << 3)
#घोषणा	USB_CDC_PACKET_TYPE_MULTICAST		(1 << 4) /* filtered */


/*-------------------------------------------------------------------------*/

/*
 * Class-Specअगरic Notअगरications (6.3) sent by पूर्णांकerrupt transfers
 *
 * section 3.8.2 table 11 of the CDC spec lists Ethernet notअगरications
 * section 3.6.2.1 table 5 specअगरies ACM notअगरications, accepted by RNDIS
 * RNDIS also defines its own bit-incompatible notअगरications
 */

#घोषणा USB_CDC_NOTIFY_NETWORK_CONNECTION	0x00
#घोषणा USB_CDC_NOTIFY_RESPONSE_AVAILABLE	0x01
#घोषणा USB_CDC_NOTIFY_SERIAL_STATE		0x20
#घोषणा USB_CDC_NOTIFY_SPEED_CHANGE		0x2a

काष्ठा usb_cdc_notअगरication अणु
	__u8	bmRequestType;
	__u8	bNotअगरicationType;
	__le16	wValue;
	__le16	wIndex;
	__le16	wLength;
पूर्ण __attribute__ ((packed));

काष्ठा usb_cdc_speed_change अणु
	__le32	DLBitRRate;	/* contains the करोwnlink bit rate (IN pipe) */
	__le32	ULBitRate;	/* contains the uplink bit rate (OUT pipe) */
पूर्ण __attribute__ ((packed));

/*-------------------------------------------------------------------------*/

/*
 * Class Specअगरic काष्ठाures and स्थिरants
 *
 * CDC NCM NTB parameters काष्ठाure, CDC NCM subclass 6.2.1
 *
 */

काष्ठा usb_cdc_ncm_ntb_parameters अणु
	__le16	wLength;
	__le16	bmNtbFormatsSupported;
	__le32	dwNtbInMaxSize;
	__le16	wNdpInDivisor;
	__le16	wNdpInPayloadReमुख्यder;
	__le16	wNdpInAlignment;
	__le16	wPadding1;
	__le32	dwNtbOutMaxSize;
	__le16	wNdpOutDivisor;
	__le16	wNdpOutPayloadReमुख्यder;
	__le16	wNdpOutAlignment;
	__le16	wNtbOutMaxDatagrams;
पूर्ण __attribute__ ((packed));

/*
 * CDC NCM transfer headers, CDC NCM subclass 3.2
 */

#घोषणा USB_CDC_NCM_NTH16_SIGN		0x484D434E /* NCMH */
#घोषणा USB_CDC_NCM_NTH32_SIGN		0x686D636E /* ncmh */

काष्ठा usb_cdc_ncm_nth16 अणु
	__le32	dwSignature;
	__le16	wHeaderLength;
	__le16	wSequence;
	__le16	wBlockLength;
	__le16	wNdpIndex;
पूर्ण __attribute__ ((packed));

काष्ठा usb_cdc_ncm_nth32 अणु
	__le32	dwSignature;
	__le16	wHeaderLength;
	__le16	wSequence;
	__le32	dwBlockLength;
	__le32	dwNdpIndex;
पूर्ण __attribute__ ((packed));

/*
 * CDC NCM datagram poपूर्णांकers, CDC NCM subclass 3.3
 */

#घोषणा USB_CDC_NCM_NDP16_CRC_SIGN	0x314D434E /* NCM1 */
#घोषणा USB_CDC_NCM_NDP16_NOCRC_SIGN	0x304D434E /* NCM0 */
#घोषणा USB_CDC_NCM_NDP32_CRC_SIGN	0x316D636E /* ncm1 */
#घोषणा USB_CDC_NCM_NDP32_NOCRC_SIGN	0x306D636E /* ncm0 */

#घोषणा USB_CDC_MBIM_NDP16_IPS_SIGN     0x00535049 /* IPS<sessionID> : IPS0 क्रम now */
#घोषणा USB_CDC_MBIM_NDP32_IPS_SIGN     0x00737069 /* ips<sessionID> : ips0 क्रम now */
#घोषणा USB_CDC_MBIM_NDP16_DSS_SIGN     0x00535344 /* DSS<sessionID> */
#घोषणा USB_CDC_MBIM_NDP32_DSS_SIGN     0x00737364 /* dss<sessionID> */

/* 16-bit NCM Datagram Poपूर्णांकer Entry */
काष्ठा usb_cdc_ncm_dpe16 अणु
	__le16	wDatagramIndex;
	__le16	wDatagramLength;
पूर्ण __attribute__((__packed__));

/* 16-bit NCM Datagram Poपूर्णांकer Table */
काष्ठा usb_cdc_ncm_ndp16 अणु
	__le32	dwSignature;
	__le16	wLength;
	__le16	wNextNdpIndex;
	काष्ठा	usb_cdc_ncm_dpe16 dpe16[0];
पूर्ण __attribute__ ((packed));

/* 32-bit NCM Datagram Poपूर्णांकer Entry */
काष्ठा usb_cdc_ncm_dpe32 अणु
	__le32	dwDatagramIndex;
	__le32	dwDatagramLength;
पूर्ण __attribute__((__packed__));

/* 32-bit NCM Datagram Poपूर्णांकer Table */
काष्ठा usb_cdc_ncm_ndp32 अणु
	__le32	dwSignature;
	__le16	wLength;
	__le16	wReserved6;
	__le32	dwNextNdpIndex;
	__le32	dwReserved12;
	काष्ठा	usb_cdc_ncm_dpe32 dpe32[0];
पूर्ण __attribute__ ((packed));

/* CDC NCM subclass 3.2.1 and 3.2.2 */
#घोषणा USB_CDC_NCM_NDP16_INDEX_MIN			0x000C
#घोषणा USB_CDC_NCM_NDP32_INDEX_MIN			0x0010

/* CDC NCM subclass 3.3.3 Datagram Formatting */
#घोषणा USB_CDC_NCM_DATAGRAM_FORMAT_CRC			0x30
#घोषणा USB_CDC_NCM_DATAGRAM_FORMAT_NOCRC		0X31

/* CDC NCM subclass 4.2 NCM Communications Interface Protocol Code */
#घोषणा USB_CDC_NCM_PROTO_CODE_NO_ENCAP_COMMANDS	0x00
#घोषणा USB_CDC_NCM_PROTO_CODE_EXTERN_PROTO		0xFE

/* CDC NCM subclass 5.2.1 NCM Functional Descriptor, bmNetworkCapabilities */
#घोषणा USB_CDC_NCM_NCAP_ETH_FILTER			(1 << 0)
#घोषणा USB_CDC_NCM_NCAP_NET_ADDRESS			(1 << 1)
#घोषणा USB_CDC_NCM_NCAP_ENCAP_COMMAND			(1 << 2)
#घोषणा USB_CDC_NCM_NCAP_MAX_DATAGRAM_SIZE		(1 << 3)
#घोषणा USB_CDC_NCM_NCAP_CRC_MODE			(1 << 4)
#घोषणा	USB_CDC_NCM_NCAP_NTB_INPUT_SIZE			(1 << 5)

/* CDC NCM subclass Table 6-3: NTB Parameter Structure */
#घोषणा USB_CDC_NCM_NTB16_SUPPORTED			(1 << 0)
#घोषणा USB_CDC_NCM_NTB32_SUPPORTED			(1 << 1)

/* CDC NCM subclass Table 6-3: NTB Parameter Structure */
#घोषणा USB_CDC_NCM_NDP_ALIGN_MIN_SIZE			0x04
#घोषणा USB_CDC_NCM_NTB_MAX_LENGTH			0x1C

/* CDC NCM subclass 6.2.5 SetNtbFormat */
#घोषणा USB_CDC_NCM_NTB16_FORMAT			0x00
#घोषणा USB_CDC_NCM_NTB32_FORMAT			0x01

/* CDC NCM subclass 6.2.7 SetNtbInputSize */
#घोषणा USB_CDC_NCM_NTB_MIN_IN_SIZE			2048
#घोषणा USB_CDC_NCM_NTB_MIN_OUT_SIZE			2048

/* NTB Input Size Structure */
काष्ठा usb_cdc_ncm_ndp_input_size अणु
	__le32	dwNtbInMaxSize;
	__le16	wNtbInMaxDatagrams;
	__le16	wReserved;
पूर्ण __attribute__ ((packed));

/* CDC NCM subclass 6.2.11 SetCrcMode */
#घोषणा USB_CDC_NCM_CRC_NOT_APPENDED			0x00
#घोषणा USB_CDC_NCM_CRC_APPENDED			0x01

#पूर्ण_अगर /* __UAPI_LINUX_USB_CDC_H */
