<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/**************************************************************************/
/*                                                                        */
/*  IBM System i and System p Virtual NIC Device Driver                   */
/*  Copyright (C) 2014 IBM Corp.                                          */
/*  Santiago Leon (santi_leon@yahoo.com)                                  */
/*  Thomas Falcon (tlfalcon@linux.vnet.ibm.com)                           */
/*  John Allen (jallen@linux.vnet.ibm.com)                                */
/*                                                                        */
/*                                                                        */
/* This module contains the implementation of a भव ethernet device   */
/* क्रम use with IBM i/pSeries LPAR Linux.  It utilizes the logical LAN    */
/* option of the RS/6000 Platक्रमm Architecture to पूर्णांकerface with भव */
/* ethernet NICs that are presented to the partition by the hypervisor.   */
/*                                                                        */
/**************************************************************************/

#घोषणा IBMVNIC_NAME		"ibmvnic"
#घोषणा IBMVNIC_DRIVER_VERSION	"1.0.1"
#घोषणा IBMVNIC_INVALID_MAP	-1
#घोषणा IBMVNIC_STATS_TIMEOUT	1
#घोषणा IBMVNIC_INIT_FAILED	2
#घोषणा IBMVNIC_OPEN_FAILED	3

/* basic काष्ठाures plus 100 2k buffers */
#घोषणा IBMVNIC_IO_ENTITLEMENT_DEFAULT	610305

/* Initial module_parameters */
#घोषणा IBMVNIC_RX_WEIGHT		16
/* when changing this, update IBMVNIC_IO_ENTITLEMENT_DEFAULT */
#घोषणा IBMVNIC_BUFFS_PER_POOL	100
#घोषणा IBMVNIC_MAX_QUEUES	16
#घोषणा IBMVNIC_MAX_QUEUE_SZ   4096
#घोषणा IBMVNIC_MAX_IND_DESCS  16
#घोषणा IBMVNIC_IND_ARR_SZ	(IBMVNIC_MAX_IND_DESCS * 32)

#घोषणा IBMVNIC_TSO_BUF_SZ	65536
#घोषणा IBMVNIC_TSO_BUFS	64
#घोषणा IBMVNIC_TSO_POOL_MASK	0x80000000

#घोषणा IBMVNIC_MAX_LTB_SIZE ((1 << (MAX_ORDER - 1)) * PAGE_SIZE)
#घोषणा IBMVNIC_BUFFER_HLEN 500

#घोषणा IBMVNIC_RESET_DELAY 100

अटल स्थिर अक्षर ibmvnic_priv_flags[][ETH_GSTRING_LEN] = अणु
#घोषणा IBMVNIC_USE_SERVER_MAXES 0x1
	"use-server-maxes"
पूर्ण;

काष्ठा ibmvnic_login_buffer अणु
	__be32 len;
	__be32 version;
#घोषणा INITIAL_VERSION_LB 1
	__be32 num_txcomp_subcrqs;
	__be32 off_txcomp_subcrqs;
	__be32 num_rxcomp_subcrqs;
	__be32 off_rxcomp_subcrqs;
	__be32 login_rsp_ioba;
	__be32 login_rsp_len;
	__be32 client_data_offset;
	__be32 client_data_len;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_login_rsp_buffer अणु
	__be32 len;
	__be32 version;
#घोषणा INITIAL_VERSION_LRB 1
	__be32 num_txsubm_subcrqs;
	__be32 off_txsubm_subcrqs;
	__be32 num_rxadd_subcrqs;
	__be32 off_rxadd_subcrqs;
	__be32 off_rxadd_buff_size;
	__be32 num_supp_tx_desc;
	__be32 off_supp_tx_desc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_query_ip_offload_buffer अणु
	__be32 len;
	__be32 version;
#घोषणा INITIAL_VERSION_IOB 1
	u8 ipv4_chksum;
	u8 ipv6_chksum;
	u8 tcp_ipv4_chksum;
	u8 tcp_ipv6_chksum;
	u8 udp_ipv4_chksum;
	u8 udp_ipv6_chksum;
	u8 large_tx_ipv4;
	u8 large_tx_ipv6;
	u8 large_rx_ipv4;
	u8 large_rx_ipv6;
	u8 reserved1[14];
	__be16 max_ipv4_header_size;
	__be16 max_ipv6_header_size;
	__be16 max_tcp_header_size;
	__be16 max_udp_header_size;
	__be32 max_large_tx_size;
	__be32 max_large_rx_size;
	u8 reserved2[16];
	u8 ipv6_extension_header;
#घोषणा IPV6_EH_NOT_SUPPORTED	0x00
#घोषणा IPV6_EH_SUPPORTED_LIM	0x01
#घोषणा IPV6_EH_SUPPORTED	0xFF
	u8 tcp_pseuकरोsum_req;
#घोषणा TCP_PS_NOT_REQUIRED	0x00
#घोषणा TCP_PS_REQUIRED		0x01
	u8 reserved3[30];
	__be16 num_ipv6_ext_headers;
	__be32 off_ipv6_ext_headers;
	u8 reserved4[154];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_control_ip_offload_buffer अणु
	__be32 len;
	__be32 version;
#घोषणा INITIAL_VERSION_IOB 1
	u8 ipv4_chksum;
	u8 ipv6_chksum;
	u8 tcp_ipv4_chksum;
	u8 tcp_ipv6_chksum;
	u8 udp_ipv4_chksum;
	u8 udp_ipv6_chksum;
	u8 large_tx_ipv4;
	u8 large_tx_ipv6;
	u8 bad_packet_rx;
	u8 large_rx_ipv4;
	u8 large_rx_ipv6;
	u8 reserved4[111];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_fw_component अणु
	u8 name[48];
	__be32 trace_buff_size;
	u8 correlator;
	u8 trace_level;
	u8 parent_correlator;
	u8 error_check_level;
	u8 trace_on;
	u8 reserved[7];
	u8 description[192];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_fw_trace_entry अणु
	__be32 trace_id;
	u8 num_valid_data;
	u8 reserved[3];
	__be64 pmc_रेजिस्टरs;
	__be64 समयbase;
	__be64 trace_data[5];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_statistics अणु
	__be32 version;
	__be32 promiscuous;
	__be64 rx_packets;
	__be64 rx_bytes;
	__be64 tx_packets;
	__be64 tx_bytes;
	__be64 ucast_tx_packets;
	__be64 ucast_rx_packets;
	__be64 mcast_tx_packets;
	__be64 mcast_rx_packets;
	__be64 bcast_tx_packets;
	__be64 bcast_rx_packets;
	__be64 align_errors;
	__be64 fcs_errors;
	__be64 single_collision_frames;
	__be64 multi_collision_frames;
	__be64 sqe_test_errors;
	__be64 deferred_tx;
	__be64 late_collisions;
	__be64 excess_collisions;
	__be64 पूर्णांकernal_mac_tx_errors;
	__be64 carrier_sense;
	__be64 too_दीर्घ_frames;
	__be64 पूर्णांकernal_mac_rx_errors;
	u8 reserved[72];
पूर्ण __packed __aligned(8);

#घोषणा NUM_TX_STATS 3
काष्ठा ibmvnic_tx_queue_stats अणु
	u64 packets;
	u64 bytes;
	u64 dropped_packets;
पूर्ण;

#घोषणा NUM_RX_STATS 3
काष्ठा ibmvnic_rx_queue_stats अणु
	u64 packets;
	u64 bytes;
	u64 पूर्णांकerrupts;
पूर्ण;

काष्ठा ibmvnic_acl_buffer अणु
	__be32 len;
	__be32 version;
#घोषणा INITIAL_VERSION_IOB 1
	u8 mac_acls_restrict;
	u8 vlan_acls_restrict;
	u8 reserved1[22];
	__be32 num_mac_addrs;
	__be32 offset_mac_addrs;
	__be32 num_vlan_ids;
	__be32 offset_vlan_ids;
	u8 reserved2[80];
पूर्ण __packed __aligned(8);

/* descriptors have been changed, how should this be defined?  1? 4? */

#घोषणा IBMVNIC_TX_DESC_VERSIONS 3

/* is this still needed? */
काष्ठा ibmvnic_tx_comp_desc अणु
	u8 first;
	u8 num_comps;
	__be16 rcs[5];
	__be32 correlators[5];
पूर्ण __packed __aligned(8);

/* some flags that included in v0 descriptor, which is gone
 * only used क्रम IBMVNIC_TCP_CHKSUM and IBMVNIC_UDP_CHKSUM
 * and only in some offload_flags variable that करोesn't seem
 * to be used anywhere, can probably be हटाओd?
 */

#घोषणा IBMVNIC_TCP_CHKSUM		0x20
#घोषणा IBMVNIC_UDP_CHKSUM		0x08

काष्ठा ibmvnic_tx_desc अणु
	u8 first;
	u8 type;

#घोषणा IBMVNIC_TX_DESC 0x10
	u8 n_crq_elem;
	u8 n_sge;
	u8 flags1;
#घोषणा IBMVNIC_TX_COMP_NEEDED		0x80
#घोषणा IBMVNIC_TX_CHKSUM_OFFLOAD	0x40
#घोषणा IBMVNIC_TX_LSO			0x20
#घोषणा IBMVNIC_TX_PROT_TCP		0x10
#घोषणा IBMVNIC_TX_PROT_UDP		0x08
#घोषणा IBMVNIC_TX_PROT_IPV4		0x04
#घोषणा IBMVNIC_TX_PROT_IPV6		0x02
#घोषणा IBMVNIC_TX_VLAN_PRESENT		0x01
	u8 flags2;
#घोषणा IBMVNIC_TX_VLAN_INSERT		0x80
	__be16 mss;
	u8 reserved[4];
	__be32 correlator;
	__be16 vlan_id;
	__be16 dma_reg;
	__be32 sge_len;
	__be64 ioba;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_hdr_desc अणु
	u8 first;
	u8 type;
#घोषणा IBMVNIC_HDR_DESC		0x11
	u8 len;
	u8 l2_len;
	__be16 l3_len;
	u8 l4_len;
	u8 flag;
	u8 data[24];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_hdr_ext_desc अणु
	u8 first;
	u8 type;
#घोषणा IBMVNIC_HDR_EXT_DESC		0x12
	u8 len;
	u8 data[29];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_sge_desc अणु
	u8 first;
	u8 type;
#घोषणा IBMVNIC_SGE_DESC		0x30
	__be16 sge1_dma_reg;
	__be32 sge1_len;
	__be64 sge1_ioba;
	__be16 reserved;
	__be16 sge2_dma_reg;
	__be32 sge2_len;
	__be64 sge2_ioba;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_rx_comp_desc अणु
	u8 first;
	u8 flags;
#घोषणा IBMVNIC_IP_CHKSUM_GOOD		0x80
#घोषणा IBMVNIC_TCP_UDP_CHKSUM_GOOD	0x40
#घोषणा IBMVNIC_END_FRAME			0x20
#घोषणा IBMVNIC_EXACT_MC			0x10
#घोषणा IBMVNIC_VLAN_STRIPPED			0x08
	__be16 off_frame_data;
	__be32 len;
	__be64 correlator;
	__be16 vlan_tci;
	__be16 rc;
	u8 reserved[12];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_generic_scrq अणु
	u8 first;
	u8 reserved[31];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_rx_buff_add_desc अणु
	u8 first;
	u8 reserved[7];
	__be64 correlator;
	__be32 ioba;
	u8 map_id;
	__be32 len:24;
	u8 reserved2[8];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_rc अणु
	u8 code; /* one of क्रमागत ibmvnic_rc_codes */
	u8 detailed_data[3];
पूर्ण __packed __aligned(4);

काष्ठा ibmvnic_generic_crq अणु
	u8 first;
	u8 cmd;
	u8 params[10];
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_version_exchange अणु
	u8 first;
	u8 cmd;
	__be16 version;
#घोषणा IBMVNIC_INITIAL_VERSION 1
	u8 reserved[8];
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_capability अणु
	u8 first;
	u8 cmd;
	__be16 capability; /* one of ibmvnic_capabilities */
	__be64 number;
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_login अणु
	u8 first;
	u8 cmd;
	u8 reserved[6];
	__be32 ioba;
	__be32 len;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_phys_parms अणु
	u8 first;
	u8 cmd;
	u8 flags1;
#घोषणा IBMVNIC_EXTERNAL_LOOPBACK	0x80
#घोषणा IBMVNIC_INTERNAL_LOOPBACK	0x40
#घोषणा IBMVNIC_PROMISC		0x20
#घोषणा IBMVNIC_PHYS_LINK_ACTIVE	0x10
#घोषणा IBMVNIC_AUTONEG_DUPLEX	0x08
#घोषणा IBMVNIC_FULL_DUPLEX	0x04
#घोषणा IBMVNIC_HALF_DUPLEX	0x02
#घोषणा IBMVNIC_CAN_CHG_PHYS_PARMS	0x01
	u8 flags2;
#घोषणा IBMVNIC_LOGICAL_LNK_ACTIVE 0x80
	__be32 speed;
#घोषणा IBMVNIC_AUTONEG		0x80000000
#घोषणा IBMVNIC_10MBPS		0x40000000
#घोषणा IBMVNIC_100MBPS		0x20000000
#घोषणा IBMVNIC_1GBPS		0x10000000
#घोषणा IBMVNIC_10GBPS		0x08000000
#घोषणा IBMVNIC_40GBPS		0x04000000
#घोषणा IBMVNIC_100GBPS		0x02000000
#घोषणा IBMVNIC_25GBPS		0x01000000
#घोषणा IBMVNIC_50GBPS		0x00800000
#घोषणा IBMVNIC_200GBPS		0x00400000
	__be32 mtu;
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_logical_link_state अणु
	u8 first;
	u8 cmd;
	u8 link_state;
#घोषणा IBMVNIC_LOGICAL_LNK_DN 0x00
#घोषणा IBMVNIC_LOGICAL_LNK_UP 0x01
#घोषणा IBMVNIC_LOGICAL_LNK_QUERY 0xff
	u8 reserved[9];
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_query_ip_offload अणु
	u8 first;
	u8 cmd;
	u8 reserved[2];
	__be32 len;
	__be32 ioba;
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_control_ip_offload अणु
	u8 first;
	u8 cmd;
	u8 reserved[2];
	__be32 ioba;
	__be32 len;
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_request_statistics अणु
	u8 first;
	u8 cmd;
	u8 flags;
#घोषणा IBMVNIC_PHYSICAL_PORT	0x80
	u8 reserved1;
	__be32 ioba;
	__be32 len;
	u8 reserved[4];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_error_indication अणु
	u8 first;
	u8 cmd;
	u8 flags;
#घोषणा IBMVNIC_FATAL_ERROR	0x80
	u8 reserved1;
	__be32 error_id;
	__be32 detail_error_sz;
	__be16 error_cause;
	u8 reserved2[2];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_link_state_indication अणु
	u8 first;
	u8 cmd;
	u8 reserved1[2];
	u8 phys_link_state;
	u8 logical_link_state;
	u8 reserved2[10];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_change_mac_addr अणु
	u8 first;
	u8 cmd;
	u8 mac_addr[6];
	u8 reserved[4];
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_multicast_ctrl अणु
	u8 first;
	u8 cmd;
	u8 mac_addr[6];
	u8 flags;
#घोषणा IBMVNIC_ENABLE_MC		0x80
#घोषणा IBMVNIC_DISABLE_MC		0x40
#घोषणा IBMVNIC_ENABLE_ALL		0x20
#घोषणा IBMVNIC_DISABLE_ALL	0x10
	u8 reserved1;
	__be16 reserved2; /* was num_enabled_mc_addr; */
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_get_vpd_size अणु
	u8 first;
	u8 cmd;
	u8 reserved[14];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_get_vpd_size_rsp अणु
	u8 first;
	u8 cmd;
	u8 reserved[2];
	__be64 len;
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_get_vpd अणु
	u8 first;
	u8 cmd;
	u8 reserved1[2];
	__be32 ioba;
	__be32 len;
	u8 reserved[4];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_get_vpd_rsp अणु
	u8 first;
	u8 cmd;
	u8 reserved[10];
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_acl_change_indication अणु
	u8 first;
	u8 cmd;
	__be16 change_type;
#घोषणा IBMVNIC_MAC_ACL 0
#घोषणा IBMVNIC_VLAN_ACL 1
	u8 reserved[12];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_acl_query अणु
	u8 first;
	u8 cmd;
	u8 reserved1[2];
	__be32 ioba;
	__be32 len;
	u8 reserved2[4];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_tune अणु
	u8 first;
	u8 cmd;
	u8 reserved1[2];
	__be32 ioba;
	__be32 len;
	u8 reserved2[4];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_request_map अणु
	u8 first;
	u8 cmd;
	u8 reserved1;
	u8 map_id;
	__be32 ioba;
	__be32 len;
	u8 reserved2[4];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_request_map_rsp अणु
	u8 first;
	u8 cmd;
	u8 reserved1;
	u8 map_id;
	u8 reserved2[8];
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_request_unmap अणु
	u8 first;
	u8 cmd;
	u8 reserved1;
	u8 map_id;
	u8 reserved2[12];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_request_unmap_rsp अणु
	u8 first;
	u8 cmd;
	u8 reserved1;
	u8 map_id;
	u8 reserved2[8];
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_query_map अणु
	u8 first;
	u8 cmd;
	u8 reserved[14];
पूर्ण __packed __aligned(8);

काष्ठा ibmvnic_query_map_rsp अणु
	u8 first;
	u8 cmd;
	u8 reserved;
	u8 page_size;
	__be32 tot_pages;
	__be32 मुक्त_pages;
	काष्ठा ibmvnic_rc rc;
पूर्ण __packed __aligned(8);

जोड़ ibmvnic_crq अणु
	काष्ठा ibmvnic_generic_crq generic;
	काष्ठा ibmvnic_version_exchange version_exchange;
	काष्ठा ibmvnic_version_exchange version_exchange_rsp;
	काष्ठा ibmvnic_capability query_capability;
	काष्ठा ibmvnic_capability query_capability_rsp;
	काष्ठा ibmvnic_capability request_capability;
	काष्ठा ibmvnic_capability request_capability_rsp;
	काष्ठा ibmvnic_login login;
	काष्ठा ibmvnic_generic_crq login_rsp;
	काष्ठा ibmvnic_phys_parms query_phys_parms;
	काष्ठा ibmvnic_phys_parms query_phys_parms_rsp;
	काष्ठा ibmvnic_phys_parms query_phys_capabilities;
	काष्ठा ibmvnic_phys_parms query_phys_capabilities_rsp;
	काष्ठा ibmvnic_phys_parms set_phys_parms;
	काष्ठा ibmvnic_phys_parms set_phys_parms_rsp;
	काष्ठा ibmvnic_logical_link_state logical_link_state;
	काष्ठा ibmvnic_logical_link_state logical_link_state_rsp;
	काष्ठा ibmvnic_query_ip_offload query_ip_offload;
	काष्ठा ibmvnic_query_ip_offload query_ip_offload_rsp;
	काष्ठा ibmvnic_control_ip_offload control_ip_offload;
	काष्ठा ibmvnic_control_ip_offload control_ip_offload_rsp;
	काष्ठा ibmvnic_request_statistics request_statistics;
	काष्ठा ibmvnic_generic_crq request_statistics_rsp;
	काष्ठा ibmvnic_error_indication error_indication;
	काष्ठा ibmvnic_link_state_indication link_state_indication;
	काष्ठा ibmvnic_change_mac_addr change_mac_addr;
	काष्ठा ibmvnic_change_mac_addr change_mac_addr_rsp;
	काष्ठा ibmvnic_multicast_ctrl multicast_ctrl;
	काष्ठा ibmvnic_multicast_ctrl multicast_ctrl_rsp;
	काष्ठा ibmvnic_get_vpd_size get_vpd_size;
	काष्ठा ibmvnic_get_vpd_size_rsp get_vpd_size_rsp;
	काष्ठा ibmvnic_get_vpd get_vpd;
	काष्ठा ibmvnic_get_vpd_rsp get_vpd_rsp;
	काष्ठा ibmvnic_acl_change_indication acl_change_indication;
	काष्ठा ibmvnic_acl_query acl_query;
	काष्ठा ibmvnic_generic_crq acl_query_rsp;
	काष्ठा ibmvnic_tune tune;
	काष्ठा ibmvnic_generic_crq tune_rsp;
	काष्ठा ibmvnic_request_map request_map;
	काष्ठा ibmvnic_request_map_rsp request_map_rsp;
	काष्ठा ibmvnic_request_unmap request_unmap;
	काष्ठा ibmvnic_request_unmap_rsp request_unmap_rsp;
	काष्ठा ibmvnic_query_map query_map;
	काष्ठा ibmvnic_query_map_rsp query_map_rsp;
पूर्ण;

क्रमागत ibmvnic_rc_codes अणु
	SUCCESS = 0,
	PARTIALSUCCESS = 1,
	PERMISSION = 2,
	NOMEMORY = 3,
	PARAMETER = 4,
	UNKNOWNCOMMAND = 5,
	ABORTED = 6,
	INVALIDSTATE = 7,
	INVALIDIOBA = 8,
	INVALIDLENGTH = 9,
	UNSUPPORTEDOPTION = 10,
पूर्ण;

क्रमागत ibmvnic_capabilities अणु
	MIN_TX_QUEUES = 1,
	MIN_RX_QUEUES = 2,
	MIN_RX_ADD_QUEUES = 3,
	MAX_TX_QUEUES = 4,
	MAX_RX_QUEUES = 5,
	MAX_RX_ADD_QUEUES = 6,
	REQ_TX_QUEUES = 7,
	REQ_RX_QUEUES = 8,
	REQ_RX_ADD_QUEUES = 9,
	MIN_TX_ENTRIES_PER_SUBCRQ = 10,
	MIN_RX_ADD_ENTRIES_PER_SUBCRQ = 11,
	MAX_TX_ENTRIES_PER_SUBCRQ = 12,
	MAX_RX_ADD_ENTRIES_PER_SUBCRQ = 13,
	REQ_TX_ENTRIES_PER_SUBCRQ = 14,
	REQ_RX_ADD_ENTRIES_PER_SUBCRQ = 15,
	TCP_IP_OFFLOAD = 16,
	PROMISC_REQUESTED = 17,
	PROMISC_SUPPORTED = 18,
	MIN_MTU = 19,
	MAX_MTU = 20,
	REQ_MTU = 21,
	MAX_MULTICAST_FILTERS = 22,
	VLAN_HEADER_INSERTION = 23,
	RX_VLAN_HEADER_INSERTION = 24,
	MAX_TX_SG_ENTRIES = 25,
	RX_SG_SUPPORTED = 26,
	RX_SG_REQUESTED = 27,
	OPT_TX_COMP_SUB_QUEUES = 28,
	OPT_RX_COMP_QUEUES = 29,
	OPT_RX_BUFADD_Q_PER_RX_COMP_Q = 30,
	OPT_TX_ENTRIES_PER_SUBCRQ = 31,
	OPT_RXBA_ENTRIES_PER_SUBCRQ = 32,
	TX_RX_DESC_REQ = 33,
पूर्ण;

क्रमागत ibmvnic_error_cause अणु
	ADAPTER_PROBLEM = 0,
	BUS_PROBLEM = 1,
	FW_PROBLEM = 2,
	DD_PROBLEM = 3,
	EEH_RECOVERY = 4,
	FW_UPDATED = 5,
	LOW_MEMORY = 6,
पूर्ण;

क्रमागत ibmvnic_commands अणु
	VERSION_EXCHANGE = 0x01,
	VERSION_EXCHANGE_RSP = 0x81,
	QUERY_CAPABILITY = 0x02,
	QUERY_CAPABILITY_RSP = 0x82,
	REQUEST_CAPABILITY = 0x03,
	REQUEST_CAPABILITY_RSP = 0x83,
	LOGIN = 0x04,
	LOGIN_RSP = 0x84,
	QUERY_PHYS_PARMS = 0x05,
	QUERY_PHYS_PARMS_RSP = 0x85,
	QUERY_PHYS_CAPABILITIES = 0x06,
	QUERY_PHYS_CAPABILITIES_RSP = 0x86,
	SET_PHYS_PARMS = 0x07,
	SET_PHYS_PARMS_RSP = 0x87,
	ERROR_INDICATION = 0x08,
	LOGICAL_LINK_STATE = 0x0C,
	LOGICAL_LINK_STATE_RSP = 0x8C,
	REQUEST_STATISTICS = 0x0D,
	REQUEST_STATISTICS_RSP = 0x8D,
	COLLECT_FW_TRACE = 0x11,
	COLLECT_FW_TRACE_RSP = 0x91,
	LINK_STATE_INDICATION = 0x12,
	CHANGE_MAC_ADDR = 0x13,
	CHANGE_MAC_ADDR_RSP = 0x93,
	MULTICAST_CTRL = 0x14,
	MULTICAST_CTRL_RSP = 0x94,
	GET_VPD_SIZE = 0x15,
	GET_VPD_SIZE_RSP = 0x95,
	GET_VPD = 0x16,
	GET_VPD_RSP = 0x96,
	TUNE = 0x17,
	TUNE_RSP = 0x97,
	QUERY_IP_OFFLOAD = 0x18,
	QUERY_IP_OFFLOAD_RSP = 0x98,
	CONTROL_IP_OFFLOAD = 0x19,
	CONTROL_IP_OFFLOAD_RSP = 0x99,
	ACL_CHANGE_INDICATION = 0x1A,
	ACL_QUERY = 0x1B,
	ACL_QUERY_RSP = 0x9B,
	QUERY_MAP = 0x1D,
	QUERY_MAP_RSP = 0x9D,
	REQUEST_MAP = 0x1E,
	REQUEST_MAP_RSP = 0x9E,
	REQUEST_UNMAP = 0x1F,
	REQUEST_UNMAP_RSP = 0x9F,
	VLAN_CTRL = 0x20,
	VLAN_CTRL_RSP = 0xA0,
पूर्ण;

क्रमागत ibmvnic_crq_type अणु
	IBMVNIC_CRQ_CMD			= 0x80,
	IBMVNIC_CRQ_CMD_RSP		= 0x80,
	IBMVNIC_CRQ_INIT_CMD		= 0xC0,
	IBMVNIC_CRQ_INIT_RSP		= 0xC0,
	IBMVNIC_CRQ_XPORT_EVENT		= 0xFF,
पूर्ण;

क्रमागत ibmvfc_crq_क्रमmat अणु
	IBMVNIC_CRQ_INIT                 = 0x01,
	IBMVNIC_CRQ_INIT_COMPLETE        = 0x02,
	IBMVNIC_PARTITION_MIGRATED       = 0x06,
	IBMVNIC_DEVICE_FAILOVER          = 0x08,
पूर्ण;

काष्ठा ibmvnic_crq_queue अणु
	जोड़ ibmvnic_crq *msgs;
	पूर्णांक size, cur;
	dma_addr_t msg_token;
	/* Used क्रम serialization of msgs, cur */
	spinlock_t lock;
	bool active;
	अक्षर name[32];
पूर्ण;

जोड़ sub_crq अणु
	काष्ठा ibmvnic_generic_scrq generic;
	काष्ठा ibmvnic_tx_comp_desc tx_comp;
	काष्ठा ibmvnic_tx_desc v1;
	काष्ठा ibmvnic_hdr_desc hdr;
	काष्ठा ibmvnic_hdr_ext_desc hdr_ext;
	काष्ठा ibmvnic_sge_desc sge;
	काष्ठा ibmvnic_rx_comp_desc rx_comp;
	काष्ठा ibmvnic_rx_buff_add_desc rx_add;
पूर्ण;

काष्ठा ibmvnic_ind_xmit_queue अणु
	जोड़ sub_crq *indir_arr;
	dma_addr_t indir_dma;
	पूर्णांक index;
पूर्ण;

काष्ठा ibmvnic_sub_crq_queue अणु
	जोड़ sub_crq *msgs;
	पूर्णांक size, cur;
	dma_addr_t msg_token;
	अचिन्हित दीर्घ crq_num;
	अचिन्हित दीर्घ hw_irq;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक pool_index;
	पूर्णांक scrq_num;
	/* Used क्रम serialization of msgs, cur */
	spinlock_t lock;
	काष्ठा sk_buff *rx_skb_top;
	काष्ठा ibmvnic_adapter *adapter;
	काष्ठा ibmvnic_ind_xmit_queue ind_buf;
	atomic_t used;
	अक्षर name[32];
	u64 handle;
पूर्ण ____cacheline_aligned;

काष्ठा ibmvnic_दीर्घ_term_buff अणु
	अचिन्हित अक्षर *buff;
	dma_addr_t addr;
	u64 size;
	u8 map_id;
पूर्ण;

काष्ठा ibmvnic_tx_buff अणु
	काष्ठा sk_buff *skb;
	पूर्णांक index;
	पूर्णांक pool_index;
	पूर्णांक num_entries;
पूर्ण;

काष्ठा ibmvnic_tx_pool अणु
	काष्ठा ibmvnic_tx_buff *tx_buff;
	पूर्णांक *मुक्त_map;
	पूर्णांक consumer_index;
	पूर्णांक producer_index;
	काष्ठा ibmvnic_दीर्घ_term_buff दीर्घ_term_buff;
	पूर्णांक num_buffers;
	पूर्णांक buf_size;
पूर्ण ____cacheline_aligned;

काष्ठा ibmvnic_rx_buff अणु
	काष्ठा sk_buff *skb;
	dma_addr_t dma;
	अचिन्हित अक्षर *data;
	पूर्णांक size;
	पूर्णांक pool_index;
पूर्ण;

काष्ठा ibmvnic_rx_pool अणु
	काष्ठा ibmvnic_rx_buff *rx_buff;
	पूर्णांक size;
	पूर्णांक index;
	पूर्णांक buff_size;
	atomic_t available;
	पूर्णांक *मुक्त_map;
	पूर्णांक next_मुक्त;
	पूर्णांक next_alloc;
	पूर्णांक active;
	काष्ठा ibmvnic_दीर्घ_term_buff दीर्घ_term_buff;
पूर्ण ____cacheline_aligned;

काष्ठा ibmvnic_vpd अणु
	अचिन्हित अक्षर *buff;
	dma_addr_t dma_addr;
	u64 len;
पूर्ण;

क्रमागत vnic_state अणुVNIC_PROBING = 1,
		 VNIC_PROBED,
		 VNIC_OPENING,
		 VNIC_OPEN,
		 VNIC_CLOSING,
		 VNIC_CLOSED,
		 VNIC_REMOVING,
		 VNIC_REMOVEDपूर्ण;

क्रमागत ibmvnic_reset_reason अणुVNIC_RESET_FAILOVER = 1,
			   VNIC_RESET_MOBILITY,
			   VNIC_RESET_FATAL,
			   VNIC_RESET_NON_FATAL,
			   VNIC_RESET_TIMEOUT,
			   VNIC_RESET_CHANGE_PARAMपूर्ण;

काष्ठा ibmvnic_rwi अणु
	क्रमागत ibmvnic_reset_reason reset_reason;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ibmvnic_tunables अणु
	u64 rx_queues;
	u64 tx_queues;
	u64 rx_entries;
	u64 tx_entries;
	u64 mtu;
पूर्ण;

काष्ठा ibmvnic_adapter अणु
	काष्ठा vio_dev *vdev;
	काष्ठा net_device *netdev;
	काष्ठा ibmvnic_crq_queue crq;
	u8 mac_addr[ETH_ALEN];
	काष्ठा ibmvnic_query_ip_offload_buffer ip_offload_buf;
	dma_addr_t ip_offload_tok;
	काष्ठा ibmvnic_control_ip_offload_buffer ip_offload_ctrl;
	dma_addr_t ip_offload_ctrl_tok;
	u32 msg_enable;
	u32 priv_flags;

	/* Vital Product Data (VPD) */
	काष्ठा ibmvnic_vpd *vpd;
	अक्षर fw_version[32];

	/* Statistics */
	काष्ठा ibmvnic_statistics stats;
	dma_addr_t stats_token;
	काष्ठा completion stats_करोne;
	पूर्णांक replenish_no_mem;
	पूर्णांक replenish_add_buff_success;
	पूर्णांक replenish_add_buff_failure;
	पूर्णांक replenish_task_cycles;
	पूर्णांक tx_send_failed;
	पूर्णांक tx_map_failed;

	काष्ठा ibmvnic_tx_queue_stats *tx_stats_buffers;
	काष्ठा ibmvnic_rx_queue_stats *rx_stats_buffers;

	पूर्णांक phys_link_state;
	पूर्णांक logical_link_state;

	u32 speed;
	u8 duplex;

	/* login data */
	काष्ठा ibmvnic_login_buffer *login_buf;
	dma_addr_t login_buf_token;
	पूर्णांक login_buf_sz;

	काष्ठा ibmvnic_login_rsp_buffer *login_rsp_buf;
	dma_addr_t login_rsp_buf_token;
	पूर्णांक login_rsp_buf_sz;

	atomic_t running_cap_crqs;
	bool रुको_capability;

	काष्ठा ibmvnic_sub_crq_queue **tx_scrq ____cacheline_aligned;
	काष्ठा ibmvnic_sub_crq_queue **rx_scrq ____cacheline_aligned;

	/* rx काष्ठाs */
	काष्ठा napi_काष्ठा *napi;
	काष्ठा ibmvnic_rx_pool *rx_pool;
	u64 promisc;

	काष्ठा ibmvnic_tx_pool *tx_pool;
	काष्ठा ibmvnic_tx_pool *tso_pool;
	काष्ठा completion init_करोne;
	पूर्णांक init_करोne_rc;

	काष्ठा completion fw_करोne;
	/* Used क्रम serialization of device commands */
	काष्ठा mutex fw_lock;
	पूर्णांक fw_करोne_rc;

	काष्ठा completion reset_करोne;
	पूर्णांक reset_करोne_rc;
	bool रुको_क्रम_reset;

	/* partner capabilities */
	u64 min_tx_queues;
	u64 min_rx_queues;
	u64 min_rx_add_queues;
	u64 max_tx_queues;
	u64 max_rx_queues;
	u64 max_rx_add_queues;
	u64 req_tx_queues;
	u64 req_rx_queues;
	u64 req_rx_add_queues;
	u64 min_tx_entries_per_subcrq;
	u64 min_rx_add_entries_per_subcrq;
	u64 max_tx_entries_per_subcrq;
	u64 max_rx_add_entries_per_subcrq;
	u64 req_tx_entries_per_subcrq;
	u64 req_rx_add_entries_per_subcrq;
	u64 tcp_ip_offload;
	u64 promisc_requested;
	u64 promisc_supported;
	u64 min_mtu;
	u64 max_mtu;
	u64 req_mtu;
	u64 max_multicast_filters;
	u64 vlan_header_insertion;
	u64 rx_vlan_header_insertion;
	u64 max_tx_sg_entries;
	u64 rx_sg_supported;
	u64 rx_sg_requested;
	u64 opt_tx_comp_sub_queues;
	u64 opt_rx_comp_queues;
	u64 opt_rx_bufadd_q_per_rx_comp_q;
	u64 opt_tx_entries_per_subcrq;
	u64 opt_rxba_entries_per_subcrq;
	__be64 tx_rx_desc_req;
	u8 map_id;
	u32 num_active_rx_scrqs;
	u32 num_active_rx_pools;
	u32 num_active_rx_napi;
	u32 num_active_tx_scrqs;
	u32 num_active_tx_pools;
	u32 cur_rx_buf_sz;

	काष्ठा tasklet_काष्ठा tasklet;
	क्रमागत vnic_state state;
	/* Used क्रम serialization of state field. When taking both state
	 * and rwi locks, take state lock first.
	 */
	spinlock_t state_lock;
	क्रमागत ibmvnic_reset_reason reset_reason;
	काष्ठा list_head rwi_list;
	/* Used क्रम serialization of rwi_list. When taking both state
	 * and rwi locks, take state lock first
	 */
	spinlock_t rwi_lock;
	काष्ठा work_काष्ठा ibmvnic_reset;
	काष्ठा delayed_work ibmvnic_delayed_reset;
	अचिन्हित दीर्घ resetting;
	bool napi_enabled, from_passive_init;
	bool login_pending;
	/* last device reset समय */
	अचिन्हित दीर्घ last_reset_समय;

	bool failover_pending;
	bool क्रमce_reset_recovery;

	काष्ठा ibmvnic_tunables desired;
	काष्ठा ibmvnic_tunables fallback;
पूर्ण;
