<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Copyright IBM Corp. 2007
 *    Author(s): Frank Pavlic <fpavlic@de.ibm.com>,
 *		 Thomas Spatzier <tspat@de.ibm.com>,
 *		 Frank Blaschka <frank.blaschka@de.ibm.com>
 */

#अगर_अघोषित __QETH_CORE_MPC_H__
#घोषणा __QETH_CORE_MPC_H__

#समावेश <यंत्र/qeth.h>
#समावेश <uapi/linux/अगर_ether.h>
#समावेश <uapi/linux/in6.h>

बाह्य स्थिर अचिन्हित अक्षर IPA_PDU_HEADER[];
#घोषणा IPA_PDU_HEADER_SIZE	0x40
#घोषणा QETH_IPA_PDU_LEN_TOTAL(buffer) (buffer + 0x0e)
#घोषणा QETH_IPA_PDU_LEN_PDU1(buffer) (buffer + 0x26)
#घोषणा QETH_IPA_PDU_LEN_PDU2(buffer) (buffer + 0x29)
#घोषणा QETH_IPA_PDU_LEN_PDU3(buffer) (buffer + 0x3a)

#घोषणा QETH_IPA_CMD_DEST_ADDR(buffer) (buffer + 0x2c)

#घोषणा QETH_SEQ_NO_LENGTH	4
#घोषणा QETH_MPC_TOKEN_LENGTH	4
#घोषणा QETH_MCL_LENGTH		4

#घोषणा QETH_TIMEOUT		(10 * HZ)
#घोषणा QETH_IPA_TIMEOUT	(45 * HZ)

/*****************************************************************************/
/* IP Assist related definitions                                             */
/*****************************************************************************/
#घोषणा IPA_CMD_INITIATOR_HOST  0x00
#घोषणा IPA_CMD_INITIATOR_OSA   0x01
#घोषणा IPA_CMD_INITIATOR_HOST_REPLY  0x80
#घोषणा IPA_CMD_INITIATOR_OSA_REPLY   0x81
#घोषणा IPA_CMD_PRIM_VERSION_NO 0x01

काष्ठा qeth_ipa_caps अणु
	u32 supported;
	u32 enabled;
पूर्ण;

अटल अंतरभूत bool qeth_ipa_caps_supported(काष्ठा qeth_ipa_caps *caps, u32 mask)
अणु
	वापस (caps->supported & mask) == mask;
पूर्ण

अटल अंतरभूत bool qeth_ipa_caps_enabled(काष्ठा qeth_ipa_caps *caps, u32 mask)
अणु
	वापस (caps->enabled & mask) == mask;
पूर्ण

#घोषणा qeth_adp_supported(c, f) \
	qeth_ipa_caps_supported(&c->options.adp, f)
#घोषणा qeth_is_supported(c, f) \
	qeth_ipa_caps_supported(&c->options.ipa4, f)
#घोषणा qeth_is_supported6(c, f) \
	qeth_ipa_caps_supported(&c->options.ipa6, f)
#घोषणा qeth_is_ipafunc_supported(c, prot, f) \
	 ((prot == QETH_PROT_IPV6) ? qeth_is_supported6(c, f) : \
				     qeth_is_supported(c, f))

क्रमागत qeth_card_types अणु
	QETH_CARD_TYPE_OSD     = 1,
	QETH_CARD_TYPE_IQD     = 5,
	QETH_CARD_TYPE_OSN     = 6,
	QETH_CARD_TYPE_OSM     = 3,
	QETH_CARD_TYPE_OSX     = 2,
पूर्ण;

#घोषणा IS_IQD(card)	((card)->info.type == QETH_CARD_TYPE_IQD)
#घोषणा IS_OSD(card)	((card)->info.type == QETH_CARD_TYPE_OSD)
#घोषणा IS_OSM(card)	((card)->info.type == QETH_CARD_TYPE_OSM)

#अगर_घोषित CONFIG_QETH_OSN
#घोषणा IS_OSN(card)	((card)->info.type == QETH_CARD_TYPE_OSN)
#अन्यथा
#घोषणा IS_OSN(card)	false
#पूर्ण_अगर

#अगर_घोषित CONFIG_QETH_OSX
#घोषणा IS_OSX(card)	((card)->info.type == QETH_CARD_TYPE_OSX)
#अन्यथा
#घोषणा IS_OSX(card)	false
#पूर्ण_अगर

#घोषणा IS_VM_NIC(card)	((card)->info.is_vm_nic)

#घोषणा QETH_MPC_DIFINFO_LEN_INDICATES_LINK_TYPE 0x18
/* only the first two bytes are looked at in qeth_get_cardname_लघु */
क्रमागत qeth_link_types अणु
	QETH_LINK_TYPE_FAST_ETH     = 0x01,
	QETH_LINK_TYPE_HSTR         = 0x02,
	QETH_LINK_TYPE_GBIT_ETH     = 0x03,
	QETH_LINK_TYPE_OSN          = 0x04,
	QETH_LINK_TYPE_10GBIT_ETH   = 0x10,
	QETH_LINK_TYPE_25GBIT_ETH   = 0x12,
	QETH_LINK_TYPE_LANE_ETH100  = 0x81,
	QETH_LINK_TYPE_LANE_TR      = 0x82,
	QETH_LINK_TYPE_LANE_ETH1000 = 0x83,
	QETH_LINK_TYPE_LANE         = 0x88,
पूर्ण;

क्रमागत qeth_routing_types अणु
	/* TODO: set to bit flag used in IPA Command */
	NO_ROUTER		= 0,
	PRIMARY_ROUTER		= 1,
	SECONDARY_ROUTER	= 2,
	MULTICAST_ROUTER	= 3,
	PRIMARY_CONNECTOR	= 4,
	SECONDARY_CONNECTOR	= 5,
पूर्ण;

/* IPA Commands */
क्रमागत qeth_ipa_cmds अणु
	IPA_CMD_STARTLAN		= 0x01,
	IPA_CMD_STOPLAN			= 0x02,
	IPA_CMD_SETVMAC			= 0x21,
	IPA_CMD_DELVMAC			= 0x22,
	IPA_CMD_SETGMAC			= 0x23,
	IPA_CMD_DELGMAC			= 0x24,
	IPA_CMD_SETVLAN			= 0x25,
	IPA_CMD_DELVLAN			= 0x26,
	IPA_CMD_VNICC			= 0x2a,
	IPA_CMD_SETBRIDGEPORT_OSA	= 0x2b,
	IPA_CMD_SETCCID			= 0x41,
	IPA_CMD_DELCCID			= 0x42,
	IPA_CMD_MODCCID			= 0x43,
	IPA_CMD_SETIP			= 0xb1,
	IPA_CMD_QIPASSIST		= 0xb2,
	IPA_CMD_SETASSPARMS		= 0xb3,
	IPA_CMD_SETIPM			= 0xb4,
	IPA_CMD_DELIPM			= 0xb5,
	IPA_CMD_SETRTG			= 0xb6,
	IPA_CMD_DELIP			= 0xb7,
	IPA_CMD_SETADAPTERPARMS		= 0xb8,
	IPA_CMD_SET_DIAG_ASS		= 0xb9,
	IPA_CMD_SETBRIDGEPORT_IQD	= 0xbe,
	IPA_CMD_CREATE_ADDR		= 0xc3,
	IPA_CMD_DESTROY_ADDR		= 0xc4,
	IPA_CMD_REGISTER_LOCAL_ADDR	= 0xd1,
	IPA_CMD_UNREGISTER_LOCAL_ADDR	= 0xd2,
	IPA_CMD_ADDRESS_CHANGE_NOTIF	= 0xd3,
	IPA_CMD_UNKNOWN			= 0x00
पूर्ण;

क्रमागत qeth_ip_ass_cmds अणु
	IPA_CMD_ASS_START	= 0x0001,
	IPA_CMD_ASS_STOP	= 0x0002,
	IPA_CMD_ASS_CONFIGURE	= 0x0003,
	IPA_CMD_ASS_ENABLE	= 0x0004,
पूर्ण;

क्रमागत qeth_arp_process_subcmds अणु
	IPA_CMD_ASS_ARP_SET_NO_ENTRIES	= 0x0003,
	IPA_CMD_ASS_ARP_QUERY_CACHE	= 0x0004,
	IPA_CMD_ASS_ARP_ADD_ENTRY	= 0x0005,
	IPA_CMD_ASS_ARP_REMOVE_ENTRY	= 0x0006,
	IPA_CMD_ASS_ARP_FLUSH_CACHE	= 0x0007,
	IPA_CMD_ASS_ARP_QUERY_INFO	= 0x0104,
	IPA_CMD_ASS_ARP_QUERY_STATS	= 0x0204,
पूर्ण;


/* Return Codes क्रम IPA Commands
 * according to OSA card Specs */

क्रमागत qeth_ipa_वापस_codes अणु
	IPA_RC_SUCCESS			= 0x0000,
	IPA_RC_NOTSUPP			= 0x0001,
	IPA_RC_IP_TABLE_FULL		= 0x0002,
	IPA_RC_UNKNOWN_ERROR		= 0x0003,
	IPA_RC_UNSUPPORTED_COMMAND	= 0x0004,
	IPA_RC_TRACE_ALREADY_ACTIVE	= 0x0005,
	IPA_RC_INVALID_FORMAT		= 0x0006,
	IPA_RC_DUP_IPV6_REMOTE		= 0x0008,
	IPA_RC_SBP_IQD_NOT_CONFIGURED	= 0x000C,
	IPA_RC_DUP_IPV6_HOME		= 0x0010,
	IPA_RC_UNREGISTERED_ADDR	= 0x0011,
	IPA_RC_NO_ID_AVAILABLE		= 0x0012,
	IPA_RC_ID_NOT_FOUND		= 0x0013,
	IPA_RC_SBP_IQD_ANO_DEV_PRIMARY	= 0x0014,
	IPA_RC_SBP_IQD_CURRENT_SECOND	= 0x0018,
	IPA_RC_SBP_IQD_LIMIT_SECOND	= 0x001C,
	IPA_RC_INVALID_IP_VERSION	= 0x0020,
	IPA_RC_SBP_IQD_CURRENT_PRIMARY	= 0x0024,
	IPA_RC_LAN_FRAME_MISMATCH	= 0x0040,
	IPA_RC_SBP_IQD_NO_QDIO_QUEUES	= 0x00EB,
	IPA_RC_L2_UNSUPPORTED_CMD	= 0x2003,
	IPA_RC_L2_DUP_MAC		= 0x2005,
	IPA_RC_L2_ADDR_TABLE_FULL	= 0x2006,
	IPA_RC_L2_DUP_LAYER3_MAC	= 0x200a,
	IPA_RC_L2_GMAC_NOT_FOUND	= 0x200b,
	IPA_RC_L2_MAC_NOT_AUTH_BY_HYP	= 0x200c,
	IPA_RC_L2_MAC_NOT_AUTH_BY_ADP	= 0x200d,
	IPA_RC_L2_MAC_NOT_FOUND		= 0x2010,
	IPA_RC_L2_INVALID_VLAN_ID	= 0x2015,
	IPA_RC_L2_DUP_VLAN_ID		= 0x2016,
	IPA_RC_L2_VLAN_ID_NOT_FOUND	= 0x2017,
	IPA_RC_L2_VLAN_ID_NOT_ALLOWED	= 0x2050,
	IPA_RC_VNICC_VNICBP		= 0x20B0,
	IPA_RC_SBP_OSA_NOT_CONFIGURED	= 0x2B0C,
	IPA_RC_SBP_OSA_OS_MISMATCH	= 0x2B10,
	IPA_RC_SBP_OSA_ANO_DEV_PRIMARY	= 0x2B14,
	IPA_RC_SBP_OSA_CURRENT_SECOND	= 0x2B18,
	IPA_RC_SBP_OSA_LIMIT_SECOND	= 0x2B1C,
	IPA_RC_SBP_OSA_NOT_AUTHD_BY_ZMAN = 0x2B20,
	IPA_RC_SBP_OSA_CURRENT_PRIMARY	= 0x2B24,
	IPA_RC_SBP_OSA_NO_QDIO_QUEUES	= 0x2BEB,
	IPA_RC_DATA_MISMATCH		= 0xe001,
	IPA_RC_INVALID_MTU_SIZE		= 0xe002,
	IPA_RC_INVALID_LANTYPE		= 0xe003,
	IPA_RC_INVALID_LANNUM		= 0xe004,
	IPA_RC_DUPLICATE_IP_ADDRESS	= 0xe005,
	IPA_RC_IP_ADDR_TABLE_FULL	= 0xe006,
	IPA_RC_LAN_PORT_STATE_ERROR	= 0xe007,
	IPA_RC_SETIP_NO_STARTLAN	= 0xe008,
	IPA_RC_SETIP_ALREADY_RECEIVED	= 0xe009,
	IPA_RC_IP_ADDR_ALREADY_USED	= 0xe00a,
	IPA_RC_MC_ADDR_NOT_FOUND	= 0xe00b,
	IPA_RC_SETIP_INVALID_VERSION	= 0xe00d,
	IPA_RC_UNSUPPORTED_SUBCMD	= 0xe00e,
	IPA_RC_ARP_ASSIST_NO_ENABLE	= 0xe00f,
	IPA_RC_PRIMARY_ALREADY_DEFINED	= 0xe010,
	IPA_RC_SECOND_ALREADY_DEFINED	= 0xe011,
	IPA_RC_INVALID_SETRTG_INDICATOR	= 0xe012,
	IPA_RC_MC_ADDR_ALREADY_DEFINED	= 0xe013,
	IPA_RC_LAN_OFFLINE		= 0xe080,
	IPA_RC_VEPA_TO_VEB_TRANSITION	= 0xe090,
	IPA_RC_INVALID_IP_VERSION2	= 0xf001,
	IPA_RC_FFFF			= 0xffff
पूर्ण;
/* क्रम VNIC Characteristics */
#घोषणा IPA_RC_VNICC_OOSEQ 0x0005

/* क्रम SET_DIAGNOSTIC_ASSIST */
#घोषणा IPA_RC_INVALID_SUBCMD		IPA_RC_IP_TABLE_FULL
#घोषणा IPA_RC_HARDWARE_AUTH_ERROR	IPA_RC_UNKNOWN_ERROR

/* क्रम SETBRIDGEPORT (द्विगुन occupancies) */
#घोषणा IPA_RC_SBP_IQD_OS_MISMATCH	 IPA_RC_DUP_IPV6_HOME
#घोषणा IPA_RC_SBP_IQD_NOT_AUTHD_BY_ZMAN IPA_RC_INVALID_IP_VERSION

/* IPA function flags; each flag marks availability of respective function */
क्रमागत qeth_ipa_funcs अणु
	IPA_ARP_PROCESSING      = 0x00000001L,
	IPA_INBOUND_CHECKSUM    = 0x00000002L,
	IPA_OUTBOUND_CHECKSUM   = 0x00000004L,
	/* RESERVED		= 0x00000008L,*/
	IPA_FILTERING           = 0x00000010L,
	IPA_IPV6                = 0x00000020L,
	IPA_MULTICASTING        = 0x00000040L,
	IPA_IP_REASSEMBLY       = 0x00000080L,
	IPA_QUERY_ARP_COUNTERS  = 0x00000100L,
	IPA_QUERY_ARP_ADDR_INFO = 0x00000200L,
	IPA_SETADAPTERPARMS     = 0x00000400L,
	IPA_VLAN_PRIO           = 0x00000800L,
	IPA_PASSTHRU            = 0x00001000L,
	IPA_FLUSH_ARP_SUPPORT   = 0x00002000L,
	IPA_FULL_VLAN           = 0x00004000L,
	IPA_INBOUND_PASSTHRU    = 0x00008000L,
	IPA_SOURCE_MAC          = 0x00010000L,
	IPA_OSA_MC_ROUTER       = 0x00020000L,
	IPA_QUERY_ARP_ASSIST	= 0x00040000L,
	IPA_INBOUND_TSO         = 0x00080000L,
	IPA_OUTBOUND_TSO        = 0x00100000L,
	IPA_INBOUND_CHECKSUM_V6 = 0x00400000L,
	IPA_OUTBOUND_CHECKSUM_V6 = 0x00800000L,
पूर्ण;

/* SETIP/DELIP IPA Command: ***************************************************/
क्रमागत qeth_ipa_setdelip_flags अणु
	QETH_IPA_SETDELIP_DEFAULT          = 0x00L, /* शेष */
	QETH_IPA_SETIP_VIPA_FLAG           = 0x01L, /* no grat. ARP */
	QETH_IPA_SETIP_TAKEOVER_FLAG       = 0x02L, /* nofail on grat. ARP */
	QETH_IPA_DELIP_ADDR_2_B_TAKEN_OVER = 0x20L,
	QETH_IPA_DELIP_VIPA_FLAG           = 0x40L,
	QETH_IPA_DELIP_ADDR_NEEDS_SETIP    = 0x80L,
पूर्ण;

/* SETADAPTER IPA Command: ****************************************************/
क्रमागत qeth_ipa_setadp_cmd अणु
	IPA_SETADP_QUERY_COMMANDS_SUPPORTED	= 0x00000001L,
	IPA_SETADP_ALTER_MAC_ADDRESS		= 0x00000002L,
	IPA_SETADP_ADD_DELETE_GROUP_ADDRESS	= 0x00000004L,
	IPA_SETADP_ADD_DELETE_FUNCTIONAL_ADDR	= 0x00000008L,
	IPA_SETADP_SET_ADDRESSING_MODE		= 0x00000010L,
	IPA_SETADP_SET_CONFIG_PARMS		= 0x00000020L,
	IPA_SETADP_SET_CONFIG_PARMS_EXTENDED	= 0x00000040L,
	IPA_SETADP_SET_BROADCAST_MODE		= 0x00000080L,
	IPA_SETADP_SEND_OSA_MESSAGE		= 0x00000100L,
	IPA_SETADP_SET_SNMP_CONTROL		= 0x00000200L,
	IPA_SETADP_QUERY_CARD_INFO		= 0x00000400L,
	IPA_SETADP_SET_PROMISC_MODE		= 0x00000800L,
	IPA_SETADP_SET_DIAG_ASSIST		= 0x00002000L,
	IPA_SETADP_SET_ACCESS_CONTROL		= 0x00010000L,
	IPA_SETADP_QUERY_OAT			= 0x00080000L,
	IPA_SETADP_QUERY_SWITCH_ATTRIBUTES	= 0x00100000L,
पूर्ण;
क्रमागत qeth_ipa_mac_ops अणु
	CHANGE_ADDR_READ_MAC		= 0,
	CHANGE_ADDR_REPLACE_MAC		= 1,
	CHANGE_ADDR_ADD_MAC		= 2,
	CHANGE_ADDR_DEL_MAC		= 4,
	CHANGE_ADDR_RESET_MAC		= 8,
पूर्ण;
क्रमागत qeth_ipa_addr_ops अणु
	CHANGE_ADDR_READ_ADDR		= 0,
	CHANGE_ADDR_ADD_ADDR		= 1,
	CHANGE_ADDR_DEL_ADDR		= 2,
	CHANGE_ADDR_FLUSH_ADDR_TABLE	= 4,
पूर्ण;
क्रमागत qeth_ipa_promisc_modes अणु
	SET_PROMISC_MODE_OFF		= 0,
	SET_PROMISC_MODE_ON		= 1,
पूर्ण;
क्रमागत qeth_ipa_isolation_modes अणु
	ISOLATION_MODE_NONE		= 0x00000000L,
	ISOLATION_MODE_FWD		= 0x00000001L,
	ISOLATION_MODE_DROP		= 0x00000002L,
पूर्ण;
क्रमागत qeth_ipa_set_access_mode_rc अणु
	SET_ACCESS_CTRL_RC_SUCCESS		= 0x0000,
	SET_ACCESS_CTRL_RC_NOT_SUPPORTED	= 0x0004,
	SET_ACCESS_CTRL_RC_ALREADY_NOT_ISOLATED	= 0x0008,
	SET_ACCESS_CTRL_RC_ALREADY_ISOLATED	= 0x0010,
	SET_ACCESS_CTRL_RC_NONE_SHARED_ADAPTER	= 0x0014,
	SET_ACCESS_CTRL_RC_ACTIVE_CHECKSUM_OFF	= 0x0018,
	SET_ACCESS_CTRL_RC_REFLREL_UNSUPPORTED	= 0x0022,
	SET_ACCESS_CTRL_RC_REFLREL_FAILED	= 0x0024,
	SET_ACCESS_CTRL_RC_REFLREL_DEACT_FAILED	= 0x0028,
पूर्ण;
क्रमागत qeth_card_info_card_type अणु
	CARD_INFO_TYPE_1G_COPPER_A	= 0x61,
	CARD_INFO_TYPE_1G_FIBRE_A	= 0x71,
	CARD_INFO_TYPE_10G_FIBRE_A	= 0x91,
	CARD_INFO_TYPE_1G_COPPER_B	= 0xb1,
	CARD_INFO_TYPE_1G_FIBRE_B	= 0xa1,
	CARD_INFO_TYPE_10G_FIBRE_B	= 0xc1,
पूर्ण;
क्रमागत qeth_card_info_port_mode अणु
	CARD_INFO_PORTM_HALFDUPLEX	= 0x0002,
	CARD_INFO_PORTM_FULLDUPLEX	= 0x0003,
पूर्ण;
क्रमागत qeth_card_info_port_speed अणु
	CARD_INFO_PORTS_10M		= 0x00000005,
	CARD_INFO_PORTS_100M		= 0x00000006,
	CARD_INFO_PORTS_1G		= 0x00000007,
	CARD_INFO_PORTS_10G		= 0x00000008,
	CARD_INFO_PORTS_25G		= 0x0000000A,
पूर्ण;

/* (SET)DELIP(M) IPA stuff ***************************************************/
काष्ठा qeth_ipacmd_setdelip4 अणु
	__be32 addr;
	__be32 mask;
	__u32  flags;
पूर्ण __attribute__ ((packed));

काष्ठा qeth_ipacmd_setdelip6 अणु
	काष्ठा in6_addr addr;
	काष्ठा in6_addr prefix;
	__u32  flags;
पूर्ण __attribute__ ((packed));

काष्ठा qeth_ipacmd_setdelipm अणु
	__u8 mac[6];
	__u8 padding[2];
	काष्ठा in6_addr ip;
पूर्ण __attribute__ ((packed));

काष्ठा qeth_ipacmd_layer2setdelmac अणु
	__u32 mac_length;
	__u8 mac[6];
पूर्ण __attribute__ ((packed));

काष्ठा qeth_ipacmd_layer2setdelvlan अणु
	__u16 vlan_id;
पूर्ण __attribute__ ((packed));

काष्ठा qeth_ipacmd_setassparms_hdr अणु
	__u16 length;
	__u16 command_code;
	__u16 वापस_code;
	__u8 number_of_replies;
	__u8 seq_no;
पूर्ण __attribute__((packed));

काष्ठा qeth_arp_query_data अणु
	__u16 request_bits;
	__u16 reply_bits;
	__u32 no_entries;
	अक्षर data; /* only क्रम replies */
पूर्ण __attribute__((packed));

/* used as parameter क्रम arp_query reply */
काष्ठा qeth_arp_query_info अणु
	__u32 udata_len;
	__u16 mask_bits;
	__u32 udata_offset;
	__u32 no_entries;
	अक्षर *udata;
पूर्ण;

/* IPA set assist segmentation bit definitions क्रम receive and
 * transmit checksum offloading.
 */
क्रमागत qeth_ipa_checksum_bits अणु
	QETH_IPA_CHECKSUM_IP_HDR	= 0x0002,
	QETH_IPA_CHECKSUM_UDP		= 0x0008,
	QETH_IPA_CHECKSUM_TCP		= 0x0010,
	QETH_IPA_CHECKSUM_LP2LP		= 0x0020
पूर्ण;

क्रमागत qeth_ipa_large_send_caps अणु
	QETH_IPA_LARGE_SEND_TCP		= 0x00000001,
पूर्ण;

काष्ठा qeth_tso_start_data अणु
	u32 mss;
	u32 supported;
पूर्ण;

/* SETASSPARMS IPA Command: */
काष्ठा qeth_ipacmd_setassparms अणु
	u32 assist_no;
	काष्ठा qeth_ipacmd_setassparms_hdr hdr;
	जोड़ अणु
		__u32 flags_32bit;
		काष्ठा qeth_ipa_caps caps;
		काष्ठा qeth_arp_cache_entry arp_entry;
		काष्ठा qeth_arp_query_data query_arp;
		काष्ठा qeth_tso_start_data tso;
	पूर्ण data;
पूर्ण __attribute__ ((packed));

#घोषणा SETASS_DATA_SIZखातापूर्ण(field) माप_field(काष्ठा qeth_ipacmd_setassparms,\
					       data.field)

/* SETRTG IPA Command:    ****************************************************/
काष्ठा qeth_set_routing अणु
	__u8 type;
पूर्ण;

/* SETADAPTERPARMS IPA Command:    *******************************************/
काष्ठा qeth_query_cmds_supp अणु
	__u32 no_lantypes_supp;
	__u8 lan_type;
	__u8 reserved1[3];
	__u32 supported_cmds;
	__u8 reserved2[8];
पूर्ण __attribute__ ((packed));

काष्ठा qeth_change_addr अणु
	u32 cmd;
	u32 addr_size;
	u32 no_macs;
	u8 addr[ETH_ALEN];
पूर्ण;

काष्ठा qeth_snmp_cmd अणु
	__u8  token[16];
	__u32 request;
	__u32 पूर्णांकerface;
	__u32 वापसcode;
	__u32 firmwarelevel;
	__u32 seqno;
	__u8  data;
पूर्ण __attribute__ ((packed));

काष्ठा qeth_snmp_ureq_hdr अणु
	__u32   data_len;
	__u32   req_len;
	__u32   reserved1;
	__u32   reserved2;
पूर्ण __attribute__ ((packed));

काष्ठा qeth_snmp_ureq अणु
	काष्ठा qeth_snmp_ureq_hdr hdr;
	काष्ठा qeth_snmp_cmd cmd;
पूर्ण __attribute__((packed));

/* SET_ACCESS_CONTROL: same क्रमmat क्रम request and reply */
काष्ठा qeth_set_access_ctrl अणु
	__u32 subcmd_code;
	__u8 reserved[8];
पूर्ण __attribute__((packed));

#घोषणा QETH_QOAT_PHYS_SPEED_UNKNOWN		0x00
#घोषणा QETH_QOAT_PHYS_SPEED_10M_HALF		0x01
#घोषणा QETH_QOAT_PHYS_SPEED_10M_FULL		0x02
#घोषणा QETH_QOAT_PHYS_SPEED_100M_HALF		0x03
#घोषणा QETH_QOAT_PHYS_SPEED_100M_FULL		0x04
#घोषणा QETH_QOAT_PHYS_SPEED_1000M_HALF		0x05
#घोषणा QETH_QOAT_PHYS_SPEED_1000M_FULL		0x06
// n/a						0x07
#घोषणा QETH_QOAT_PHYS_SPEED_10G_FULL		0x08
// n/a						0x09
#घोषणा QETH_QOAT_PHYS_SPEED_25G_FULL		0x0A

#घोषणा QETH_QOAT_PHYS_MEDIA_COPPER		0x01
#घोषणा QETH_QOAT_PHYS_MEDIA_FIBRE_SHORT	0x02
#घोषणा QETH_QOAT_PHYS_MEDIA_FIBRE_LONG		0x04

काष्ठा qeth_query_oat_physical_अगर अणु
	u8 res_head[33];
	u8 speed_duplex;
	u8 media_type;
	u8 res_tail[29];
पूर्ण;

#घोषणा QETH_QOAT_REPLY_TYPE_PHYS_IF		0x0004

काष्ठा qeth_query_oat_reply अणु
	u16 type;
	u16 length;
	u16 version;
	u8 res[10];
	काष्ठा qeth_query_oat_physical_अगर phys_अगर;
पूर्ण;

#घोषणा QETH_QOAT_SCOPE_INTERFACE		0x00000001

काष्ठा qeth_query_oat अणु
	u32 subcmd_code;
	u8 reserved[12];
	काष्ठा qeth_query_oat_reply reply[];
पूर्ण __packed;

काष्ठा qeth_qoat_priv अणु
	__u32 buffer_len;
	__u32 response_len;
	अक्षर *buffer;
पूर्ण;

काष्ठा qeth_query_card_info अणु
	__u8	card_type;
	__u8	reserved1;
	__u16	port_mode;
	__u32	port_speed;
	__u32	reserved2;
पूर्ण;

#घोषणा QETH_SWITCH_FORW_802_1		0x00000001
#घोषणा QETH_SWITCH_FORW_REFL_RELAY	0x00000002
#घोषणा QETH_SWITCH_CAP_RTE		0x00000004
#घोषणा QETH_SWITCH_CAP_ECP		0x00000008
#घोषणा QETH_SWITCH_CAP_VDP		0x00000010

काष्ठा qeth_query_चयन_attributes अणु
	__u8  version;
	__u8  reserved1;
	__u16 reserved2;
	__u32 capabilities;
	__u32 settings;
	__u8  reserved3[8];
पूर्ण;

#घोषणा QETH_SETADP_FLAGS_VIRTUAL_MAC	0x80	/* क्रम CHANGE_ADDR_READ_MAC */

काष्ठा qeth_ipacmd_setadpparms_hdr अणु
	u16 cmdlength;
	u16 reserved2;
	u32 command_code;
	u16 वापस_code;
	u8 used_total;
	u8 seq_no;
	u8 flags;
	u8 reserved3[3];
पूर्ण;

काष्ठा qeth_ipacmd_setadpparms अणु
	काष्ठा qeth_ipa_caps hw_cmds;
	काष्ठा qeth_ipacmd_setadpparms_hdr hdr;
	जोड़ अणु
		काष्ठा qeth_query_cmds_supp query_cmds_supp;
		काष्ठा qeth_change_addr change_addr;
		काष्ठा qeth_snmp_cmd snmp;
		काष्ठा qeth_set_access_ctrl set_access_ctrl;
		काष्ठा qeth_query_oat query_oat;
		काष्ठा qeth_query_card_info card_info;
		काष्ठा qeth_query_चयन_attributes query_चयन_attributes;
		__u32 mode;
	पूर्ण data;
पूर्ण __attribute__ ((packed));

#घोषणा SETADP_DATA_SIZखातापूर्ण(field) माप_field(काष्ठा qeth_ipacmd_setadpparms,\
					       data.field)

/* CREATE_ADDR IPA Command:    ***********************************************/
काष्ठा qeth_create_destroy_address अणु
	u8 mac_addr[ETH_ALEN];
	u16 uid;
पूर्ण;

/* SET DIAGNOSTIC ASSIST IPA Command:	 *************************************/

क्रमागत qeth_diags_cmds अणु
	QETH_DIAGS_CMD_QUERY	= 0x0001,
	QETH_DIAGS_CMD_TRAP	= 0x0002,
	QETH_DIAGS_CMD_TRACE	= 0x0004,
	QETH_DIAGS_CMD_NOLOG	= 0x0008,
	QETH_DIAGS_CMD_DUMP	= 0x0010,
पूर्ण;

क्रमागत qeth_diags_trace_types अणु
	QETH_DIAGS_TYPE_HIPERSOCKET	= 0x02,
पूर्ण;

क्रमागत qeth_diags_trace_cmds अणु
	QETH_DIAGS_CMD_TRACE_ENABLE	= 0x0001,
	QETH_DIAGS_CMD_TRACE_DISABLE	= 0x0002,
	QETH_DIAGS_CMD_TRACE_MODIFY	= 0x0004,
	QETH_DIAGS_CMD_TRACE_REPLACE	= 0x0008,
	QETH_DIAGS_CMD_TRACE_QUERY	= 0x0010,
पूर्ण;

क्रमागत qeth_diags_trap_action अणु
	QETH_DIAGS_TRAP_ARM	= 0x01,
	QETH_DIAGS_TRAP_DISARM	= 0x02,
	QETH_DIAGS_TRAP_CAPTURE = 0x04,
पूर्ण;

काष्ठा qeth_ipacmd_diagass अणु
	__u32  host_tod2;
	__u32:32;
	__u16  subcmd_len;
	__u16:16;
	__u32  subcmd;
	__u8   type;
	__u8   action;
	__u16  options;
	__u32  ext;
	__u8   cdata[64];
पूर्ण __attribute__ ((packed));

#घोषणा DIAG_HDR_LEN		दुरत्वend(काष्ठा qeth_ipacmd_diagass, ext)
#घोषणा DIAG_SUB_HDR_LEN	(दुरत्वend(काष्ठा qeth_ipacmd_diagass, ext) -\
				 दुरत्व(काष्ठा qeth_ipacmd_diagass, \
					  subcmd_len))

/* VNIC Characteristics IPA Command: *****************************************/
/* IPA commands/sub commands क्रम VNICC */
#घोषणा IPA_VNICC_QUERY_CHARS		0x00000000L
#घोषणा IPA_VNICC_QUERY_CMDS		0x00000001L
#घोषणा IPA_VNICC_ENABLE		0x00000002L
#घोषणा IPA_VNICC_DISABLE		0x00000004L
#घोषणा IPA_VNICC_SET_TIMEOUT		0x00000008L
#घोषणा IPA_VNICC_GET_TIMEOUT		0x00000010L

/* VNICC flags */
#घोषणा QETH_VNICC_FLOODING		0x80000000
#घोषणा QETH_VNICC_MCAST_FLOODING	0x40000000
#घोषणा QETH_VNICC_LEARNING		0x20000000
#घोषणा QETH_VNICC_TAKEOVER_SETVMAC	0x10000000
#घोषणा QETH_VNICC_TAKEOVER_LEARNING	0x08000000
#घोषणा QETH_VNICC_BRIDGE_INVISIBLE	0x04000000
#घोषणा QETH_VNICC_RX_BCAST		0x02000000

/* VNICC शेष values */
#घोषणा QETH_VNICC_ALL			0xff000000
#घोषणा QETH_VNICC_DEFAULT		QETH_VNICC_RX_BCAST
/* शेष VNICC समयout in seconds */
#घोषणा QETH_VNICC_DEFAULT_TIMEOUT	600

/* VNICC header */
काष्ठा qeth_ipacmd_vnicc_hdr अणु
	u16 data_length;
	u16 reserved;
	u32 sub_command;
पूर्ण;

/* query supported commands क्रम VNIC अक्षरacteristic */
काष्ठा qeth_vnicc_query_cmds अणु
	u32 vnic_अक्षर;
	u32 sup_cmds;
पूर्ण;

/* enable/disable VNIC अक्षरacteristic */
काष्ठा qeth_vnicc_set_अक्षर अणु
	u32 vnic_अक्षर;
पूर्ण;

/* get/set समयout क्रम VNIC अक्षरacteristic */
काष्ठा qeth_vnicc_माला_लोet_समयout अणु
	u32 vnic_अक्षर;
	u32 समयout;
पूर्ण;

/* complete VNICC IPA command message */
काष्ठा qeth_ipacmd_vnicc अणु
	काष्ठा qeth_ipa_caps vnicc_cmds;
	काष्ठा qeth_ipacmd_vnicc_hdr hdr;
	जोड़ अणु
		काष्ठा qeth_vnicc_query_cmds query_cmds;
		काष्ठा qeth_vnicc_set_अक्षर set_अक्षर;
		काष्ठा qeth_vnicc_माला_लोet_समयout माला_लोet_समयout;
	पूर्ण data;
पूर्ण;

#घोषणा VNICC_DATA_SIZखातापूर्ण(field)	माप_field(काष्ठा qeth_ipacmd_vnicc,\
						     data.field)

/* SETBRIDGEPORT IPA Command:	 *********************************************/
क्रमागत qeth_ipa_sbp_cmd अणु
	IPA_SBP_QUERY_COMMANDS_SUPPORTED	= 0x00000000L,
	IPA_SBP_RESET_BRIDGE_PORT_ROLE		= 0x00000001L,
	IPA_SBP_SET_PRIMARY_BRIDGE_PORT		= 0x00000002L,
	IPA_SBP_SET_SECONDARY_BRIDGE_PORT	= 0x00000004L,
	IPA_SBP_QUERY_BRIDGE_PORTS		= 0x00000008L,
	IPA_SBP_BRIDGE_PORT_STATE_CHANGE	= 0x00000010L,
पूर्ण;

काष्ठा net_अगर_token अणु
	__u16 devnum;
	__u8 cssid;
	__u8 iid;
	__u8 ssid;
	__u8 chpid;
	__u16 chid;
पूर्ण __packed;

काष्ठा mac_addr_lnid अणु
	__u8 mac[6];
	__u16 lnid;
पूर्ण __packed;

काष्ठा qeth_ipacmd_sbp_hdr अणु
	__u16 cmdlength;
	__u16 reserved1;
	__u32 command_code;
	__u16 वापस_code;
	__u8  used_total;
	__u8  seq_no;
	__u32 reserved2;
पूर्ण __packed;

काष्ठा qeth_sbp_query_cmds_supp अणु
	__u32 supported_cmds;
	__u32 reserved;
पूर्ण __packed;

काष्ठा qeth_sbp_set_primary अणु
	काष्ठा net_अगर_token token;
पूर्ण __packed;

काष्ठा qeth_sbp_port_entry अणु
		__u8 role;
		__u8 state;
		__u8 reserved1;
		__u8 reserved2;
		काष्ठा net_अगर_token token;
पूर्ण __packed;

/* For IPA_SBP_QUERY_BRIDGE_PORTS, IPA_SBP_BRIDGE_PORT_STATE_CHANGE */
काष्ठा qeth_sbp_port_data अणु
	__u8 primary_bp_supported;
	__u8 secondary_bp_supported;
	__u8 num_entries;
	__u8 entry_length;
	काष्ठा qeth_sbp_port_entry entry[];
पूर्ण __packed;

काष्ठा qeth_ipacmd_setbridgeport अणु
	काष्ठा qeth_ipa_caps sbp_cmds;
	काष्ठा qeth_ipacmd_sbp_hdr hdr;
	जोड़ अणु
		काष्ठा qeth_sbp_query_cmds_supp query_cmds_supp;
		काष्ठा qeth_sbp_set_primary set_primary;
		काष्ठा qeth_sbp_port_data port_data;
	पूर्ण data;
पूर्ण __packed;

#घोषणा SBP_DATA_SIZखातापूर्ण(field)	माप_field(काष्ठा qeth_ipacmd_setbridgeport,\
					     data.field)

/* ADDRESS_CHANGE_NOTIFICATION adapter-initiated "command" *******************/
/* Biपंचांगask क्रम entry->change_code. Both bits may be उठाओd.		     */
क्रमागत qeth_ipa_addr_change_code अणु
	IPA_ADDR_CHANGE_CODE_VLANID		= 0x01,
	IPA_ADDR_CHANGE_CODE_MACADDR		= 0x02,
	IPA_ADDR_CHANGE_CODE_REMOVAL		= 0x80,	/* अन्यथा addition */
पूर्ण;

काष्ठा qeth_ipacmd_addr_change_entry अणु
	काष्ठा net_अगर_token token;
	काष्ठा mac_addr_lnid addr_lnid;
	__u8 change_code;
	__u8 reserved1;
	__u16 reserved2;
पूर्ण __packed;

काष्ठा qeth_ipacmd_addr_change अणु
	__u8 lost_event_mask;
	__u8 reserved;
	__u16 num_entries;
	काष्ठा qeth_ipacmd_addr_change_entry entry[];
पूर्ण __packed;

/* [UN]REGISTER_LOCAL_ADDRESS notअगरications */
काष्ठा qeth_ipacmd_local_addr4 अणु
	__be32 addr;
	u32 flags;
पूर्ण;

काष्ठा qeth_ipacmd_local_addrs4 अणु
	u32 count;
	u32 addr_length;
	काष्ठा qeth_ipacmd_local_addr4 addrs[];
पूर्ण;

काष्ठा qeth_ipacmd_local_addr6 अणु
	काष्ठा in6_addr addr;
	u32 flags;
पूर्ण;

काष्ठा qeth_ipacmd_local_addrs6 अणु
	u32 count;
	u32 addr_length;
	काष्ठा qeth_ipacmd_local_addr6 addrs[];
पूर्ण;

/* Header क्रम each IPA command */
काष्ठा qeth_ipacmd_hdr अणु
	__u8   command;
	__u8   initiator;
	__u16  seqno;
	__u16  वापस_code;
	__u8   adapter_type;
	__u8   rel_adapter_no;
	__u8   prim_version_no;
	__u8   param_count;
	__u16  prot_version;
	काष्ठा qeth_ipa_caps assists;
पूर्ण __attribute__ ((packed));

/* The IPA command itself */
काष्ठा qeth_ipa_cmd अणु
	काष्ठा qeth_ipacmd_hdr hdr;
	जोड़ अणु
		काष्ठा qeth_ipacmd_setdelip4		setdelip4;
		काष्ठा qeth_ipacmd_setdelip6		setdelip6;
		काष्ठा qeth_ipacmd_setdelipm		setdelipm;
		काष्ठा qeth_ipacmd_setassparms		setassparms;
		काष्ठा qeth_ipacmd_layer2setdelmac	setdelmac;
		काष्ठा qeth_ipacmd_layer2setdelvlan	setdelvlan;
		काष्ठा qeth_create_destroy_address	create_destroy_addr;
		काष्ठा qeth_ipacmd_setadpparms		setadapterparms;
		काष्ठा qeth_set_routing			setrtg;
		काष्ठा qeth_ipacmd_diagass		diagass;
		काष्ठा qeth_ipacmd_setbridgeport	sbp;
		काष्ठा qeth_ipacmd_addr_change		addrchange;
		काष्ठा qeth_ipacmd_vnicc		vnicc;
		काष्ठा qeth_ipacmd_local_addrs4		local_addrs4;
		काष्ठा qeth_ipacmd_local_addrs6		local_addrs6;
	पूर्ण data;
पूर्ण __attribute__ ((packed));

#घोषणा IPA_DATA_SIZखातापूर्ण(field)	माप_field(काष्ठा qeth_ipa_cmd, data.field)

/*
 * special command क्रम ARP processing.
 * this is not included in setassparms command beक्रमe, because we get
 * problem with the size of काष्ठा qeth_ipacmd_setassparms otherwise
 */
क्रमागत qeth_ipa_arp_वापस_codes अणु
	QETH_IPA_ARP_RC_SUCCESS      = 0x0000,
	QETH_IPA_ARP_RC_FAILED       = 0x0001,
	QETH_IPA_ARP_RC_NOTSUPP      = 0x0002,
	QETH_IPA_ARP_RC_OUT_OF_RANGE = 0x0003,
	QETH_IPA_ARP_RC_Q_NOTSUPP    = 0x0004,
	QETH_IPA_ARP_RC_Q_NO_DATA    = 0x0008,
पूर्ण;

बाह्य स्थिर अक्षर *qeth_get_ipa_msg(क्रमागत qeth_ipa_वापस_codes rc);
बाह्य स्थिर अक्षर *qeth_get_ipa_cmd_name(क्रमागत qeth_ipa_cmds cmd);

/* Helper functions */
#घोषणा IS_IPA_REPLY(cmd) ((cmd->hdr.initiator == IPA_CMD_INITIATOR_HOST) || \
			   (cmd->hdr.initiator == IPA_CMD_INITIATOR_OSA_REPLY))

/*****************************************************************************/
/* END OF   IP Assist related definitions                                    */
/*****************************************************************************/

बाह्य स्थिर अचिन्हित अक्षर CM_ENABLE[];
#घोषणा CM_ENABLE_SIZE 0x63
#घोषणा QETH_CM_ENABLE_ISSUER_RM_TOKEN(buffer) (buffer + 0x2c)
#घोषणा QETH_CM_ENABLE_FILTER_TOKEN(buffer) (buffer + 0x53)
#घोषणा QETH_CM_ENABLE_USER_DATA(buffer) (buffer + 0x5b)

#घोषणा QETH_CM_ENABLE_RESP_FILTER_TOKEN(buffer) \
		(PDU_ENCAPSULATION(buffer) + 0x13)


बाह्य स्थिर अचिन्हित अक्षर CM_SETUP[];
#घोषणा CM_SETUP_SIZE 0x64
#घोषणा QETH_CM_SETUP_DEST_ADDR(buffer) (buffer + 0x2c)
#घोषणा QETH_CM_SETUP_CONNECTION_TOKEN(buffer) (buffer + 0x51)
#घोषणा QETH_CM_SETUP_FILTER_TOKEN(buffer) (buffer + 0x5a)

#घोषणा QETH_CM_SETUP_RESP_DEST_ADDR(buffer) \
		(PDU_ENCAPSULATION(buffer) + 0x1a)

बाह्य स्थिर अचिन्हित अक्षर ULP_ENABLE[];
#घोषणा ULP_ENABLE_SIZE 0x6b
#घोषणा QETH_ULP_ENABLE_LINKNUM(buffer) (buffer + 0x61)
#घोषणा QETH_ULP_ENABLE_DEST_ADDR(buffer) (buffer + 0x2c)
#घोषणा QETH_ULP_ENABLE_FILTER_TOKEN(buffer) (buffer + 0x53)
#घोषणा QETH_ULP_ENABLE_PORTNAME_AND_LL(buffer) (buffer + 0x62)
#घोषणा QETH_ULP_ENABLE_RESP_FILTER_TOKEN(buffer) \
		(PDU_ENCAPSULATION(buffer) + 0x13)
#घोषणा QETH_ULP_ENABLE_RESP_MAX_MTU(buffer) \
		(PDU_ENCAPSULATION(buffer) + 0x1f)
#घोषणा QETH_ULP_ENABLE_RESP_DIFINFO_LEN(buffer) \
		(PDU_ENCAPSULATION(buffer) + 0x17)
#घोषणा QETH_ULP_ENABLE_RESP_LINK_TYPE(buffer) \
		(PDU_ENCAPSULATION(buffer) + 0x2b)
/* Layer 2 definitions */
#घोषणा QETH_PROT_LAYER2 0x08
#घोषणा QETH_PROT_TCPIP  0x03
#घोषणा QETH_PROT_OSN2   0x0a
#घोषणा QETH_ULP_ENABLE_PROT_TYPE(buffer) (buffer + 0x50)
#घोषणा QETH_IPA_CMD_PROT_TYPE(buffer) (buffer + 0x19)

बाह्य स्थिर अचिन्हित अक्षर ULP_SETUP[];
#घोषणा ULP_SETUP_SIZE 0x6c
#घोषणा QETH_ULP_SETUP_DEST_ADDR(buffer) (buffer + 0x2c)
#घोषणा QETH_ULP_SETUP_CONNECTION_TOKEN(buffer) (buffer + 0x51)
#घोषणा QETH_ULP_SETUP_FILTER_TOKEN(buffer) (buffer + 0x5a)
#घोषणा QETH_ULP_SETUP_CUA(buffer) (buffer + 0x68)
#घोषणा QETH_ULP_SETUP_REAL_DEVADDR(buffer) (buffer + 0x6a)

#घोषणा QETH_ULP_SETUP_RESP_CONNECTION_TOKEN(buffer) \
		(PDU_ENCAPSULATION(buffer) + 0x1a)


बाह्य स्थिर अचिन्हित अक्षर DM_ACT[];
#घोषणा DM_ACT_SIZE 0x55
#घोषणा QETH_DM_ACT_DEST_ADDR(buffer) (buffer + 0x2c)
#घोषणा QETH_DM_ACT_CONNECTION_TOKEN(buffer) (buffer + 0x51)



#घोषणा QETH_TRANSPORT_HEADER_SEQ_NO(buffer) (buffer + 4)
#घोषणा QETH_PDU_HEADER_SEQ_NO(buffer) (buffer + 0x1c)
#घोषणा QETH_PDU_HEADER_ACK_SEQ_NO(buffer) (buffer + 0x20)

बाह्य स्थिर अचिन्हित अक्षर IDX_ACTIVATE_READ[];
बाह्य स्थिर अचिन्हित अक्षर IDX_ACTIVATE_WRITE[];
#घोषणा IDX_ACTIVATE_SIZE	0x22
#घोषणा QETH_IDX_ACT_PNO(buffer) (buffer+0x0b)
#घोषणा QETH_IDX_ACT_ISSUER_RM_TOKEN(buffer) (buffer + 0x0c)
#घोषणा QETH_IDX_ACT_INVAL_FRAME	0x40
#घोषणा QETH_IDX_NO_PORTNAME_REQUIRED(buffer) ((buffer)[0x0b] & 0x80)
#घोषणा QETH_IDX_ACT_FUNC_LEVEL(buffer) (buffer + 0x10)
#घोषणा QETH_IDX_ACT_DATASET_NAME(buffer) (buffer + 0x16)
#घोषणा QETH_IDX_ACT_QDIO_DEV_CUA(buffer) (buffer + 0x1e)
#घोषणा QETH_IDX_ACT_QDIO_DEV_REALADDR(buffer) (buffer + 0x20)
#घोषणा QETH_IS_IDX_ACT_POS_REPLY(buffer) (((buffer)[0x08] & 3) == 2)
#घोषणा QETH_IDX_REPLY_LEVEL(buffer) (buffer + 0x12)
#घोषणा QETH_IDX_ACT_CAUSE_CODE(buffer) (buffer)[0x09]
#घोषणा QETH_IDX_ACT_ERR_EXCL		0x19
#घोषणा QETH_IDX_ACT_ERR_AUTH		0x1E
#घोषणा QETH_IDX_ACT_ERR_AUTH_USER	0x20

#घोषणा QETH_IDX_TERMINATE		0xc0
#घोषणा QETH_IDX_TERMINATE_MASK		0xc0
#घोषणा QETH_IDX_TERM_BAD_TRANSPORT	0x41
#घोषणा QETH_IDX_TERM_BAD_TRANSPORT_VM	0xf6

#घोषणा PDU_ENCAPSULATION(buffer) \
	(buffer + *(buffer + (*(buffer + 0x0b)) + \
	 *(buffer + *(buffer + 0x0b) + 0x11) + 0x07))

#घोषणा IS_IPA(buffer) \
	((buffer) && \
	 (*(buffer + ((*(buffer + 0x0b)) + 4)) == 0xc1))

#पूर्ण_अगर
