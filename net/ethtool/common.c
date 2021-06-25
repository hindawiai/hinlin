<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/ethtool_netlink.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/phy.h>
#समावेश <linux/rtnetlink.h>

#समावेश "common.h"

स्थिर अक्षर netdev_features_strings[NETDEV_FEATURE_COUNT][ETH_GSTRING_LEN] = अणु
	[NETIF_F_SG_BIT] =               "tx-scatter-gather",
	[NETIF_F_IP_CSUM_BIT] =          "tx-checksum-ipv4",
	[NETIF_F_HW_CSUM_BIT] =          "tx-checksum-ip-generic",
	[NETIF_F_IPV6_CSUM_BIT] =        "tx-checksum-ipv6",
	[NETIF_F_HIGHDMA_BIT] =          "highdma",
	[NETIF_F_FRAGLIST_BIT] =         "tx-scatter-gather-fraglist",
	[NETIF_F_HW_VLAN_CTAG_TX_BIT] =  "tx-vlan-hw-insert",

	[NETIF_F_HW_VLAN_CTAG_RX_BIT] =  "rx-vlan-hw-parse",
	[NETIF_F_HW_VLAN_CTAG_FILTER_BIT] = "rx-vlan-filter",
	[NETIF_F_HW_VLAN_STAG_TX_BIT] =  "tx-vlan-stag-hw-insert",
	[NETIF_F_HW_VLAN_STAG_RX_BIT] =  "rx-vlan-stag-hw-parse",
	[NETIF_F_HW_VLAN_STAG_FILTER_BIT] = "rx-vlan-stag-filter",
	[NETIF_F_VLAN_CHALLENGED_BIT] =  "vlan-challenged",
	[NETIF_F_GSO_BIT] =              "tx-generic-segmentation",
	[NETIF_F_LLTX_BIT] =             "tx-lockless",
	[NETIF_F_NETNS_LOCAL_BIT] =      "netns-local",
	[NETIF_F_GRO_BIT] =              "rx-gro",
	[NETIF_F_GRO_HW_BIT] =           "rx-gro-hw",
	[NETIF_F_LRO_BIT] =              "rx-lro",

	[NETIF_F_TSO_BIT] =              "tx-tcp-segmentation",
	[NETIF_F_GSO_ROBUST_BIT] =       "tx-gso-robust",
	[NETIF_F_TSO_ECN_BIT] =          "tx-tcp-ecn-segmentation",
	[NETIF_F_TSO_MANGLEID_BIT] =	 "tx-tcp-mangleid-segmentation",
	[NETIF_F_TSO6_BIT] =             "tx-tcp6-segmentation",
	[NETIF_F_FSO_BIT] =              "tx-fcoe-segmentation",
	[NETIF_F_GSO_GRE_BIT] =		 "tx-gre-segmentation",
	[NETIF_F_GSO_GRE_CSUM_BIT] =	 "tx-gre-csum-segmentation",
	[NETIF_F_GSO_IPXIP4_BIT] =	 "tx-ipxip4-segmentation",
	[NETIF_F_GSO_IPXIP6_BIT] =	 "tx-ipxip6-segmentation",
	[NETIF_F_GSO_UDP_TUNNEL_BIT] =	 "tx-udp_tnl-segmentation",
	[NETIF_F_GSO_UDP_TUNNEL_CSUM_BIT] = "tx-udp_tnl-csum-segmentation",
	[NETIF_F_GSO_PARTIAL_BIT] =	 "tx-gso-partial",
	[NETIF_F_GSO_TUNNEL_REMCSUM_BIT] = "tx-tunnel-remcsum-segmentation",
	[NETIF_F_GSO_SCTP_BIT] =	 "tx-sctp-segmentation",
	[NETIF_F_GSO_ESP_BIT] =		 "tx-esp-segmentation",
	[NETIF_F_GSO_UDP_L4_BIT] =	 "tx-udp-segmentation",
	[NETIF_F_GSO_FRAGLIST_BIT] =	 "tx-gso-list",

	[NETIF_F_FCOE_CRC_BIT] =         "tx-checksum-fcoe-crc",
	[NETIF_F_SCTP_CRC_BIT] =        "tx-checksum-sctp",
	[NETIF_F_FCOE_MTU_BIT] =         "fcoe-mtu",
	[NETIF_F_NTUPLE_BIT] =           "rx-ntuple-filter",
	[NETIF_F_RXHASH_BIT] =           "rx-hashing",
	[NETIF_F_RXCSUM_BIT] =           "rx-checksum",
	[NETIF_F_NOCACHE_COPY_BIT] =     "tx-nocache-copy",
	[NETIF_F_LOOPBACK_BIT] =         "loopback",
	[NETIF_F_RXFCS_BIT] =            "rx-fcs",
	[NETIF_F_RXALL_BIT] =            "rx-all",
	[NETIF_F_HW_L2FW_DOFFLOAD_BIT] = "l2-fwd-offload",
	[NETIF_F_HW_TC_BIT] =		 "hw-tc-offload",
	[NETIF_F_HW_ESP_BIT] =		 "esp-hw-offload",
	[NETIF_F_HW_ESP_TX_CSUM_BIT] =	 "esp-tx-csum-hw-offload",
	[NETIF_F_RX_UDP_TUNNEL_PORT_BIT] =	 "rx-udp_tunnel-port-offload",
	[NETIF_F_HW_TLS_RECORD_BIT] =	"tls-hw-record",
	[NETIF_F_HW_TLS_TX_BIT] =	 "tls-hw-tx-offload",
	[NETIF_F_HW_TLS_RX_BIT] =	 "tls-hw-rx-offload",
	[NETIF_F_GRO_FRAGLIST_BIT] =	 "rx-gro-list",
	[NETIF_F_HW_MACSEC_BIT] =	 "macsec-hw-offload",
	[NETIF_F_GRO_UDP_FWD_BIT] =	 "rx-udp-gro-forwarding",
	[NETIF_F_HW_HSR_TAG_INS_BIT] =	 "hsr-tag-ins-offload",
	[NETIF_F_HW_HSR_TAG_RM_BIT] =	 "hsr-tag-rm-offload",
	[NETIF_F_HW_HSR_FWD_BIT] =	 "hsr-fwd-offload",
	[NETIF_F_HW_HSR_DUP_BIT] =	 "hsr-dup-offload",
पूर्ण;

स्थिर अक्षर
rss_hash_func_strings[ETH_RSS_HASH_FUNCS_COUNT][ETH_GSTRING_LEN] = अणु
	[ETH_RSS_HASH_TOP_BIT] =	"toeplitz",
	[ETH_RSS_HASH_XOR_BIT] =	"xor",
	[ETH_RSS_HASH_CRC32_BIT] =	"crc32",
पूर्ण;

स्थिर अक्षर
tunable_strings[__ETHTOOL_TUNABLE_COUNT][ETH_GSTRING_LEN] = अणु
	[ETHTOOL_ID_UNSPEC]     = "Unspec",
	[ETHTOOL_RX_COPYBREAK]	= "rx-copybreak",
	[ETHTOOL_TX_COPYBREAK]	= "tx-copybreak",
	[ETHTOOL_PFC_PREVENTION_TOUT] = "pfc-prevention-tout",
पूर्ण;

स्थिर अक्षर
phy_tunable_strings[__ETHTOOL_PHY_TUNABLE_COUNT][ETH_GSTRING_LEN] = अणु
	[ETHTOOL_ID_UNSPEC]     = "Unspec",
	[ETHTOOL_PHY_DOWNSHIFT]	= "phy-downshift",
	[ETHTOOL_PHY_FAST_LINK_DOWN] = "phy-fast-link-down",
	[ETHTOOL_PHY_EDPD]	= "phy-energy-detect-power-down",
पूर्ण;

#घोषणा __LINK_MODE_NAME(speed, type, duplex) \
	#speed "base" #type "/" #duplex
#घोषणा __DEFINE_LINK_MODE_NAME(speed, type, duplex) \
	[ETHTOOL_LINK_MODE(speed, type, duplex)] = \
	__LINK_MODE_NAME(speed, type, duplex)
#घोषणा __DEFINE_SPECIAL_MODE_NAME(_mode, _name) \
	[ETHTOOL_LINK_MODE_ ## _mode ## _BIT] = _name

स्थिर अक्षर link_mode_names[][ETH_GSTRING_LEN] = अणु
	__DEFINE_LINK_MODE_NAME(10, T, Half),
	__DEFINE_LINK_MODE_NAME(10, T, Full),
	__DEFINE_LINK_MODE_NAME(100, T, Half),
	__DEFINE_LINK_MODE_NAME(100, T, Full),
	__DEFINE_LINK_MODE_NAME(1000, T, Half),
	__DEFINE_LINK_MODE_NAME(1000, T, Full),
	__DEFINE_SPECIAL_MODE_NAME(Autoneg, "Autoneg"),
	__DEFINE_SPECIAL_MODE_NAME(TP, "TP"),
	__DEFINE_SPECIAL_MODE_NAME(AUI, "AUI"),
	__DEFINE_SPECIAL_MODE_NAME(MII, "MII"),
	__DEFINE_SPECIAL_MODE_NAME(FIBRE, "FIBRE"),
	__DEFINE_SPECIAL_MODE_NAME(BNC, "BNC"),
	__DEFINE_LINK_MODE_NAME(10000, T, Full),
	__DEFINE_SPECIAL_MODE_NAME(Pause, "Pause"),
	__DEFINE_SPECIAL_MODE_NAME(Asym_Pause, "Asym_Pause"),
	__DEFINE_LINK_MODE_NAME(2500, X, Full),
	__DEFINE_SPECIAL_MODE_NAME(Backplane, "Backplane"),
	__DEFINE_LINK_MODE_NAME(1000, KX, Full),
	__DEFINE_LINK_MODE_NAME(10000, KX4, Full),
	__DEFINE_LINK_MODE_NAME(10000, KR, Full),
	__DEFINE_SPECIAL_MODE_NAME(10000baseR_FEC, "10000baseR_FEC"),
	__DEFINE_LINK_MODE_NAME(20000, MLD2, Full),
	__DEFINE_LINK_MODE_NAME(20000, KR2, Full),
	__DEFINE_LINK_MODE_NAME(40000, KR4, Full),
	__DEFINE_LINK_MODE_NAME(40000, CR4, Full),
	__DEFINE_LINK_MODE_NAME(40000, SR4, Full),
	__DEFINE_LINK_MODE_NAME(40000, LR4, Full),
	__DEFINE_LINK_MODE_NAME(56000, KR4, Full),
	__DEFINE_LINK_MODE_NAME(56000, CR4, Full),
	__DEFINE_LINK_MODE_NAME(56000, SR4, Full),
	__DEFINE_LINK_MODE_NAME(56000, LR4, Full),
	__DEFINE_LINK_MODE_NAME(25000, CR, Full),
	__DEFINE_LINK_MODE_NAME(25000, KR, Full),
	__DEFINE_LINK_MODE_NAME(25000, SR, Full),
	__DEFINE_LINK_MODE_NAME(50000, CR2, Full),
	__DEFINE_LINK_MODE_NAME(50000, KR2, Full),
	__DEFINE_LINK_MODE_NAME(100000, KR4, Full),
	__DEFINE_LINK_MODE_NAME(100000, SR4, Full),
	__DEFINE_LINK_MODE_NAME(100000, CR4, Full),
	__DEFINE_LINK_MODE_NAME(100000, LR4_ER4, Full),
	__DEFINE_LINK_MODE_NAME(50000, SR2, Full),
	__DEFINE_LINK_MODE_NAME(1000, X, Full),
	__DEFINE_LINK_MODE_NAME(10000, CR, Full),
	__DEFINE_LINK_MODE_NAME(10000, SR, Full),
	__DEFINE_LINK_MODE_NAME(10000, LR, Full),
	__DEFINE_LINK_MODE_NAME(10000, LRM, Full),
	__DEFINE_LINK_MODE_NAME(10000, ER, Full),
	__DEFINE_LINK_MODE_NAME(2500, T, Full),
	__DEFINE_LINK_MODE_NAME(5000, T, Full),
	__DEFINE_SPECIAL_MODE_NAME(FEC_NONE, "None"),
	__DEFINE_SPECIAL_MODE_NAME(FEC_RS, "RS"),
	__DEFINE_SPECIAL_MODE_NAME(FEC_BASER, "BASER"),
	__DEFINE_LINK_MODE_NAME(50000, KR, Full),
	__DEFINE_LINK_MODE_NAME(50000, SR, Full),
	__DEFINE_LINK_MODE_NAME(50000, CR, Full),
	__DEFINE_LINK_MODE_NAME(50000, LR_ER_FR, Full),
	__DEFINE_LINK_MODE_NAME(50000, DR, Full),
	__DEFINE_LINK_MODE_NAME(100000, KR2, Full),
	__DEFINE_LINK_MODE_NAME(100000, SR2, Full),
	__DEFINE_LINK_MODE_NAME(100000, CR2, Full),
	__DEFINE_LINK_MODE_NAME(100000, LR2_ER2_FR2, Full),
	__DEFINE_LINK_MODE_NAME(100000, DR2, Full),
	__DEFINE_LINK_MODE_NAME(200000, KR4, Full),
	__DEFINE_LINK_MODE_NAME(200000, SR4, Full),
	__DEFINE_LINK_MODE_NAME(200000, LR4_ER4_FR4, Full),
	__DEFINE_LINK_MODE_NAME(200000, DR4, Full),
	__DEFINE_LINK_MODE_NAME(200000, CR4, Full),
	__DEFINE_LINK_MODE_NAME(100, T1, Full),
	__DEFINE_LINK_MODE_NAME(1000, T1, Full),
	__DEFINE_LINK_MODE_NAME(400000, KR8, Full),
	__DEFINE_LINK_MODE_NAME(400000, SR8, Full),
	__DEFINE_LINK_MODE_NAME(400000, LR8_ER8_FR8, Full),
	__DEFINE_LINK_MODE_NAME(400000, DR8, Full),
	__DEFINE_LINK_MODE_NAME(400000, CR8, Full),
	__DEFINE_SPECIAL_MODE_NAME(FEC_LLRS, "LLRS"),
	__DEFINE_LINK_MODE_NAME(100000, KR, Full),
	__DEFINE_LINK_MODE_NAME(100000, SR, Full),
	__DEFINE_LINK_MODE_NAME(100000, LR_ER_FR, Full),
	__DEFINE_LINK_MODE_NAME(100000, DR, Full),
	__DEFINE_LINK_MODE_NAME(100000, CR, Full),
	__DEFINE_LINK_MODE_NAME(200000, KR2, Full),
	__DEFINE_LINK_MODE_NAME(200000, SR2, Full),
	__DEFINE_LINK_MODE_NAME(200000, LR2_ER2_FR2, Full),
	__DEFINE_LINK_MODE_NAME(200000, DR2, Full),
	__DEFINE_LINK_MODE_NAME(200000, CR2, Full),
	__DEFINE_LINK_MODE_NAME(400000, KR4, Full),
	__DEFINE_LINK_MODE_NAME(400000, SR4, Full),
	__DEFINE_LINK_MODE_NAME(400000, LR4_ER4_FR4, Full),
	__DEFINE_LINK_MODE_NAME(400000, DR4, Full),
	__DEFINE_LINK_MODE_NAME(400000, CR4, Full),
	__DEFINE_LINK_MODE_NAME(100, FX, Half),
	__DEFINE_LINK_MODE_NAME(100, FX, Full),
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(link_mode_names) == __ETHTOOL_LINK_MODE_MASK_NBITS);

#घोषणा __LINK_MODE_LANES_CR		1
#घोषणा __LINK_MODE_LANES_CR2		2
#घोषणा __LINK_MODE_LANES_CR4		4
#घोषणा __LINK_MODE_LANES_CR8		8
#घोषणा __LINK_MODE_LANES_DR		1
#घोषणा __LINK_MODE_LANES_DR2		2
#घोषणा __LINK_MODE_LANES_DR4		4
#घोषणा __LINK_MODE_LANES_DR8		8
#घोषणा __LINK_MODE_LANES_KR		1
#घोषणा __LINK_MODE_LANES_KR2		2
#घोषणा __LINK_MODE_LANES_KR4		4
#घोषणा __LINK_MODE_LANES_KR8		8
#घोषणा __LINK_MODE_LANES_SR		1
#घोषणा __LINK_MODE_LANES_SR2		2
#घोषणा __LINK_MODE_LANES_SR4		4
#घोषणा __LINK_MODE_LANES_SR8		8
#घोषणा __LINK_MODE_LANES_ER		1
#घोषणा __LINK_MODE_LANES_KX		1
#घोषणा __LINK_MODE_LANES_KX4		4
#घोषणा __LINK_MODE_LANES_LR		1
#घोषणा __LINK_MODE_LANES_LR4		4
#घोषणा __LINK_MODE_LANES_LR4_ER4	4
#घोषणा __LINK_MODE_LANES_LR_ER_FR	1
#घोषणा __LINK_MODE_LANES_LR2_ER2_FR2	2
#घोषणा __LINK_MODE_LANES_LR4_ER4_FR4	4
#घोषणा __LINK_MODE_LANES_LR8_ER8_FR8	8
#घोषणा __LINK_MODE_LANES_LRM		1
#घोषणा __LINK_MODE_LANES_MLD2		2
#घोषणा __LINK_MODE_LANES_T		1
#घोषणा __LINK_MODE_LANES_T1		1
#घोषणा __LINK_MODE_LANES_X		1
#घोषणा __LINK_MODE_LANES_FX		1

#घोषणा __DEFINE_LINK_MODE_PARAMS(_speed, _type, _duplex)	\
	[ETHTOOL_LINK_MODE(_speed, _type, _duplex)] = अणु		\
		.speed  = SPEED_ ## _speed, \
		.lanes  = __LINK_MODE_LANES_ ## _type, \
		.duplex	= __DUPLEX_ ## _duplex \
	पूर्ण
#घोषणा __DUPLEX_Half DUPLEX_HALF
#घोषणा __DUPLEX_Full DUPLEX_FULL
#घोषणा __DEFINE_SPECIAL_MODE_PARAMS(_mode) \
	[ETHTOOL_LINK_MODE_ ## _mode ## _BIT] = अणु \
		.speed	= SPEED_UNKNOWN, \
		.lanes	= 0, \
		.duplex	= DUPLEX_UNKNOWN, \
	पूर्ण

स्थिर काष्ठा link_mode_info link_mode_params[] = अणु
	__DEFINE_LINK_MODE_PARAMS(10, T, Half),
	__DEFINE_LINK_MODE_PARAMS(10, T, Full),
	__DEFINE_LINK_MODE_PARAMS(100, T, Half),
	__DEFINE_LINK_MODE_PARAMS(100, T, Full),
	__DEFINE_LINK_MODE_PARAMS(1000, T, Half),
	__DEFINE_LINK_MODE_PARAMS(1000, T, Full),
	__DEFINE_SPECIAL_MODE_PARAMS(Autoneg),
	__DEFINE_SPECIAL_MODE_PARAMS(TP),
	__DEFINE_SPECIAL_MODE_PARAMS(AUI),
	__DEFINE_SPECIAL_MODE_PARAMS(MII),
	__DEFINE_SPECIAL_MODE_PARAMS(FIBRE),
	__DEFINE_SPECIAL_MODE_PARAMS(BNC),
	__DEFINE_LINK_MODE_PARAMS(10000, T, Full),
	__DEFINE_SPECIAL_MODE_PARAMS(Pause),
	__DEFINE_SPECIAL_MODE_PARAMS(Asym_Pause),
	__DEFINE_LINK_MODE_PARAMS(2500, X, Full),
	__DEFINE_SPECIAL_MODE_PARAMS(Backplane),
	__DEFINE_LINK_MODE_PARAMS(1000, KX, Full),
	__DEFINE_LINK_MODE_PARAMS(10000, KX4, Full),
	__DEFINE_LINK_MODE_PARAMS(10000, KR, Full),
	[ETHTOOL_LINK_MODE_10000baseR_FEC_BIT] = अणु
		.speed	= SPEED_10000,
		.lanes	= 1,
		.duplex = DUPLEX_FULL,
	पूर्ण,
	__DEFINE_LINK_MODE_PARAMS(20000, MLD2, Full),
	__DEFINE_LINK_MODE_PARAMS(20000, KR2, Full),
	__DEFINE_LINK_MODE_PARAMS(40000, KR4, Full),
	__DEFINE_LINK_MODE_PARAMS(40000, CR4, Full),
	__DEFINE_LINK_MODE_PARAMS(40000, SR4, Full),
	__DEFINE_LINK_MODE_PARAMS(40000, LR4, Full),
	__DEFINE_LINK_MODE_PARAMS(56000, KR4, Full),
	__DEFINE_LINK_MODE_PARAMS(56000, CR4, Full),
	__DEFINE_LINK_MODE_PARAMS(56000, SR4, Full),
	__DEFINE_LINK_MODE_PARAMS(56000, LR4, Full),
	__DEFINE_LINK_MODE_PARAMS(25000, CR, Full),
	__DEFINE_LINK_MODE_PARAMS(25000, KR, Full),
	__DEFINE_LINK_MODE_PARAMS(25000, SR, Full),
	__DEFINE_LINK_MODE_PARAMS(50000, CR2, Full),
	__DEFINE_LINK_MODE_PARAMS(50000, KR2, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, KR4, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, SR4, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, CR4, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, LR4_ER4, Full),
	__DEFINE_LINK_MODE_PARAMS(50000, SR2, Full),
	__DEFINE_LINK_MODE_PARAMS(1000, X, Full),
	__DEFINE_LINK_MODE_PARAMS(10000, CR, Full),
	__DEFINE_LINK_MODE_PARAMS(10000, SR, Full),
	__DEFINE_LINK_MODE_PARAMS(10000, LR, Full),
	__DEFINE_LINK_MODE_PARAMS(10000, LRM, Full),
	__DEFINE_LINK_MODE_PARAMS(10000, ER, Full),
	__DEFINE_LINK_MODE_PARAMS(2500, T, Full),
	__DEFINE_LINK_MODE_PARAMS(5000, T, Full),
	__DEFINE_SPECIAL_MODE_PARAMS(FEC_NONE),
	__DEFINE_SPECIAL_MODE_PARAMS(FEC_RS),
	__DEFINE_SPECIAL_MODE_PARAMS(FEC_BASER),
	__DEFINE_LINK_MODE_PARAMS(50000, KR, Full),
	__DEFINE_LINK_MODE_PARAMS(50000, SR, Full),
	__DEFINE_LINK_MODE_PARAMS(50000, CR, Full),
	__DEFINE_LINK_MODE_PARAMS(50000, LR_ER_FR, Full),
	__DEFINE_LINK_MODE_PARAMS(50000, DR, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, KR2, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, SR2, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, CR2, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, LR2_ER2_FR2, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, DR2, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, KR4, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, SR4, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, LR4_ER4_FR4, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, DR4, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, CR4, Full),
	__DEFINE_LINK_MODE_PARAMS(100, T1, Full),
	__DEFINE_LINK_MODE_PARAMS(1000, T1, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, KR8, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, SR8, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, LR8_ER8_FR8, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, DR8, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, CR8, Full),
	__DEFINE_SPECIAL_MODE_PARAMS(FEC_LLRS),
	__DEFINE_LINK_MODE_PARAMS(100000, KR, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, SR, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, LR_ER_FR, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, DR, Full),
	__DEFINE_LINK_MODE_PARAMS(100000, CR, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, KR2, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, SR2, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, LR2_ER2_FR2, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, DR2, Full),
	__DEFINE_LINK_MODE_PARAMS(200000, CR2, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, KR4, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, SR4, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, LR4_ER4_FR4, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, DR4, Full),
	__DEFINE_LINK_MODE_PARAMS(400000, CR4, Full),
	__DEFINE_LINK_MODE_PARAMS(100, FX, Half),
	__DEFINE_LINK_MODE_PARAMS(100, FX, Full),
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(link_mode_params) == __ETHTOOL_LINK_MODE_MASK_NBITS);

स्थिर अक्षर netअगर_msg_class_names[][ETH_GSTRING_LEN] = अणु
	[NETIF_MSG_DRV_BIT]		= "drv",
	[NETIF_MSG_PROBE_BIT]		= "probe",
	[NETIF_MSG_LINK_BIT]		= "link",
	[NETIF_MSG_TIMER_BIT]		= "timer",
	[NETIF_MSG_IFDOWN_BIT]		= "ifdown",
	[NETIF_MSG_IFUP_BIT]		= "ifup",
	[NETIF_MSG_RX_ERR_BIT]		= "rx_err",
	[NETIF_MSG_TX_ERR_BIT]		= "tx_err",
	[NETIF_MSG_TX_QUEUED_BIT]	= "tx_queued",
	[NETIF_MSG_INTR_BIT]		= "intr",
	[NETIF_MSG_TX_DONE_BIT]		= "tx_done",
	[NETIF_MSG_RX_STATUS_BIT]	= "rx_status",
	[NETIF_MSG_PKTDATA_BIT]		= "pktdata",
	[NETIF_MSG_HW_BIT]		= "hw",
	[NETIF_MSG_WOL_BIT]		= "wol",
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(netअगर_msg_class_names) == NETIF_MSG_CLASS_COUNT);

स्थिर अक्षर wol_mode_names[][ETH_GSTRING_LEN] = अणु
	[स्थिर_ilog2(WAKE_PHY)]		= "phy",
	[स्थिर_ilog2(WAKE_UCAST)]	= "ucast",
	[स्थिर_ilog2(WAKE_MCAST)]	= "mcast",
	[स्थिर_ilog2(WAKE_BCAST)]	= "bcast",
	[स्थिर_ilog2(WAKE_ARP)]		= "arp",
	[स्थिर_ilog2(WAKE_MAGIC)]	= "magic",
	[स्थिर_ilog2(WAKE_MAGICSECURE)]	= "magicsecure",
	[स्थिर_ilog2(WAKE_FILTER)]	= "filter",
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(wol_mode_names) == WOL_MODE_COUNT);

स्थिर अक्षर sof_बारtamping_names[][ETH_GSTRING_LEN] = अणु
	[स्थिर_ilog2(SOF_TIMESTAMPING_TX_HARDWARE)]  = "hardware-transmit",
	[स्थिर_ilog2(SOF_TIMESTAMPING_TX_SOFTWARE)]  = "software-transmit",
	[स्थिर_ilog2(SOF_TIMESTAMPING_RX_HARDWARE)]  = "hardware-receive",
	[स्थिर_ilog2(SOF_TIMESTAMPING_RX_SOFTWARE)]  = "software-receive",
	[स्थिर_ilog2(SOF_TIMESTAMPING_SOFTWARE)]     = "software-system-clock",
	[स्थिर_ilog2(SOF_TIMESTAMPING_SYS_HARDWARE)] = "hardware-legacy-clock",
	[स्थिर_ilog2(SOF_TIMESTAMPING_RAW_HARDWARE)] = "hardware-raw-clock",
	[स्थिर_ilog2(SOF_TIMESTAMPING_OPT_ID)]       = "option-id",
	[स्थिर_ilog2(SOF_TIMESTAMPING_TX_SCHED)]     = "sched-transmit",
	[स्थिर_ilog2(SOF_TIMESTAMPING_TX_ACK)]       = "ack-transmit",
	[स्थिर_ilog2(SOF_TIMESTAMPING_OPT_CMSG)]     = "option-cmsg",
	[स्थिर_ilog2(SOF_TIMESTAMPING_OPT_TSONLY)]   = "option-tsonly",
	[स्थिर_ilog2(SOF_TIMESTAMPING_OPT_STATS)]    = "option-stats",
	[स्थिर_ilog2(SOF_TIMESTAMPING_OPT_PKTINFO)]  = "option-pktinfo",
	[स्थिर_ilog2(SOF_TIMESTAMPING_OPT_TX_SWHW)]  = "option-tx-swhw",
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(sof_बारtamping_names) == __SOF_TIMESTAMPING_CNT);

स्थिर अक्षर ts_tx_type_names[][ETH_GSTRING_LEN] = अणु
	[HWTSTAMP_TX_OFF]		= "off",
	[HWTSTAMP_TX_ON]		= "on",
	[HWTSTAMP_TX_ONESTEP_SYNC]	= "onestep-sync",
	[HWTSTAMP_TX_ONESTEP_P2P]	= "onestep-p2p",
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(ts_tx_type_names) == __HWTSTAMP_TX_CNT);

स्थिर अक्षर ts_rx_filter_names[][ETH_GSTRING_LEN] = अणु
	[HWTSTAMP_FILTER_NONE]			= "none",
	[HWTSTAMP_FILTER_ALL]			= "all",
	[HWTSTAMP_FILTER_SOME]			= "some",
	[HWTSTAMP_FILTER_PTP_V1_L4_EVENT]	= "ptpv1-l4-event",
	[HWTSTAMP_FILTER_PTP_V1_L4_SYNC]	= "ptpv1-l4-sync",
	[HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ]	= "ptpv1-l4-delay-req",
	[HWTSTAMP_FILTER_PTP_V2_L4_EVENT]	= "ptpv2-l4-event",
	[HWTSTAMP_FILTER_PTP_V2_L4_SYNC]	= "ptpv2-l4-sync",
	[HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ]	= "ptpv2-l4-delay-req",
	[HWTSTAMP_FILTER_PTP_V2_L2_EVENT]	= "ptpv2-l2-event",
	[HWTSTAMP_FILTER_PTP_V2_L2_SYNC]	= "ptpv2-l2-sync",
	[HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ]	= "ptpv2-l2-delay-req",
	[HWTSTAMP_FILTER_PTP_V2_EVENT]		= "ptpv2-event",
	[HWTSTAMP_FILTER_PTP_V2_SYNC]		= "ptpv2-sync",
	[HWTSTAMP_FILTER_PTP_V2_DELAY_REQ]	= "ptpv2-delay-req",
	[HWTSTAMP_FILTER_NTP_ALL]		= "ntp-all",
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(ts_rx_filter_names) == __HWTSTAMP_FILTER_CNT);

स्थिर अक्षर udp_tunnel_type_names[][ETH_GSTRING_LEN] = अणु
	[ETHTOOL_UDP_TUNNEL_TYPE_VXLAN]		= "vxlan",
	[ETHTOOL_UDP_TUNNEL_TYPE_GENEVE]	= "geneve",
	[ETHTOOL_UDP_TUNNEL_TYPE_VXLAN_GPE]	= "vxlan-gpe",
पूर्ण;
अटल_निश्चित(ARRAY_SIZE(udp_tunnel_type_names) ==
	      __ETHTOOL_UDP_TUNNEL_TYPE_CNT);

/* वापस false अगर legacy contained non-0 deprecated fields
 * maxtxpkt/maxrxpkt. rest of ksettings always updated
 */
bool
convert_legacy_settings_to_link_ksettings(
	काष्ठा ethtool_link_ksettings *link_ksettings,
	स्थिर काष्ठा ethtool_cmd *legacy_settings)
अणु
	bool retval = true;

	स_रखो(link_ksettings, 0, माप(*link_ksettings));

	/* This is used to tell users that driver is still using these
	 * deprecated legacy fields, and they should not use
	 * %ETHTOOL_GLINKSETTINGS/%ETHTOOL_SLINKSETTINGS
	 */
	अगर (legacy_settings->maxtxpkt ||
	    legacy_settings->maxrxpkt)
		retval = false;

	ethtool_convert_legacy_u32_to_link_mode(
		link_ksettings->link_modes.supported,
		legacy_settings->supported);
	ethtool_convert_legacy_u32_to_link_mode(
		link_ksettings->link_modes.advertising,
		legacy_settings->advertising);
	ethtool_convert_legacy_u32_to_link_mode(
		link_ksettings->link_modes.lp_advertising,
		legacy_settings->lp_advertising);
	link_ksettings->base.speed
		= ethtool_cmd_speed(legacy_settings);
	link_ksettings->base.duplex
		= legacy_settings->duplex;
	link_ksettings->base.port
		= legacy_settings->port;
	link_ksettings->base.phy_address
		= legacy_settings->phy_address;
	link_ksettings->base.स्वतःneg
		= legacy_settings->स्वतःneg;
	link_ksettings->base.mdio_support
		= legacy_settings->mdio_support;
	link_ksettings->base.eth_tp_mdix
		= legacy_settings->eth_tp_mdix;
	link_ksettings->base.eth_tp_mdix_ctrl
		= legacy_settings->eth_tp_mdix_ctrl;
	वापस retval;
पूर्ण

पूर्णांक __ethtool_get_link(काष्ठा net_device *dev)
अणु
	अगर (!dev->ethtool_ops->get_link)
		वापस -EOPNOTSUPP;

	वापस netअगर_running(dev) && dev->ethtool_ops->get_link(dev);
पूर्ण

पूर्णांक ethtool_get_max_rxfh_channel(काष्ठा net_device *dev, u32 *max)
अणु
	u32 dev_size, current_max = 0;
	u32 *indir;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_rxfh_indir_size ||
	    !dev->ethtool_ops->get_rxfh)
		वापस -EOPNOTSUPP;
	dev_size = dev->ethtool_ops->get_rxfh_indir_size(dev);
	अगर (dev_size == 0)
		वापस -EOPNOTSUPP;

	indir = kसुस्मृति(dev_size, माप(indir[0]), GFP_USER);
	अगर (!indir)
		वापस -ENOMEM;

	ret = dev->ethtool_ops->get_rxfh(dev, indir, शून्य, शून्य);
	अगर (ret)
		जाओ out;

	जबतक (dev_size--)
		current_max = max(current_max, indir[dev_size]);

	*max = current_max;

out:
	kमुक्त(indir);
	वापस ret;
पूर्ण

पूर्णांक ethtool_check_ops(स्थिर काष्ठा ethtool_ops *ops)
अणु
	अगर (WARN_ON(ops->set_coalesce && !ops->supported_coalesce_params))
		वापस -EINVAL;
	/* NOTE: sufficiently insane drivers may swap ethtool_ops at runसमय,
	 * the fact that ops are checked at registration समय करोes not
	 * mean the ops attached to a netdev later on are sane.
	 */
	वापस 0;
पूर्ण

पूर्णांक __ethtool_get_ts_info(काष्ठा net_device *dev, काष्ठा ethtool_ts_info *info)
अणु
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	काष्ठा phy_device *phydev = dev->phydev;

	स_रखो(info, 0, माप(*info));
	info->cmd = ETHTOOL_GET_TS_INFO;

	अगर (phy_has_tsinfo(phydev))
		वापस phy_ts_info(phydev, info);
	अगर (ops->get_ts_info)
		वापस ops->get_ts_info(dev, info);

	info->so_बारtamping = SOF_TIMESTAMPING_RX_SOFTWARE |
				SOF_TIMESTAMPING_SOFTWARE;
	info->phc_index = -1;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_phy_ops *ethtool_phy_ops;

व्योम ethtool_set_ethtool_phy_ops(स्थिर काष्ठा ethtool_phy_ops *ops)
अणु
	rtnl_lock();
	ethtool_phy_ops = ops;
	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(ethtool_set_ethtool_phy_ops);

व्योम
ethtool_params_from_link_mode(काष्ठा ethtool_link_ksettings *link_ksettings,
			      क्रमागत ethtool_link_mode_bit_indices link_mode)
अणु
	स्थिर काष्ठा link_mode_info *link_info;

	अगर (WARN_ON_ONCE(link_mode >= __ETHTOOL_LINK_MODE_MASK_NBITS))
		वापस;

	link_info = &link_mode_params[link_mode];
	link_ksettings->base.speed = link_info->speed;
	link_ksettings->lanes = link_info->lanes;
	link_ksettings->base.duplex = link_info->duplex;
पूर्ण
EXPORT_SYMBOL_GPL(ethtool_params_from_link_mode);
