<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित NPC_H
#घोषणा NPC_H

क्रमागत NPC_LID_E अणु
	NPC_LID_LA = 0,
	NPC_LID_LB,
	NPC_LID_LC,
	NPC_LID_LD,
	NPC_LID_LE,
	NPC_LID_LF,
	NPC_LID_LG,
	NPC_LID_LH,
पूर्ण;

#घोषणा NPC_LT_NA 0

क्रमागत npc_kpu_la_ltype अणु
	NPC_LT_LA_8023 = 1,
	NPC_LT_LA_ETHER,
	NPC_LT_LA_IH_NIX_ETHER,
	NPC_LT_LA_IH_8_ETHER,
	NPC_LT_LA_IH_4_ETHER,
	NPC_LT_LA_IH_2_ETHER,
	NPC_LT_LA_HIGIG2_ETHER,
	NPC_LT_LA_IH_NIX_HIGIG2_ETHER,
	NPC_LT_LA_CUSTOM0 = 0xE,
	NPC_LT_LA_CUSTOM1 = 0xF,
पूर्ण;

क्रमागत npc_kpu_lb_ltype अणु
	NPC_LT_LB_ETAG = 1,
	NPC_LT_LB_CTAG,
	NPC_LT_LB_STAG_QINQ,
	NPC_LT_LB_BTAG,
	NPC_LT_LB_ITAG,
	NPC_LT_LB_DSA,
	NPC_LT_LB_DSA_VLAN,
	NPC_LT_LB_EDSA,
	NPC_LT_LB_EDSA_VLAN,
	NPC_LT_LB_EXDSA,
	NPC_LT_LB_EXDSA_VLAN,
	NPC_LT_LB_FDSA,
	NPC_LT_LB_CUSTOM0 = 0xE,
	NPC_LT_LB_CUSTOM1 = 0xF,
पूर्ण;

क्रमागत npc_kpu_lc_ltype अणु
	NPC_LT_LC_IP = 1,
	NPC_LT_LC_IP_OPT,
	NPC_LT_LC_IP6,
	NPC_LT_LC_IP6_EXT,
	NPC_LT_LC_ARP,
	NPC_LT_LC_RARP,
	NPC_LT_LC_MPLS,
	NPC_LT_LC_NSH,
	NPC_LT_LC_PTP,
	NPC_LT_LC_FCOE,
	NPC_LT_LC_CUSTOM0 = 0xE,
	NPC_LT_LC_CUSTOM1 = 0xF,
पूर्ण;

/* Don't modअगरy Ltypes upto SCTP, otherwise it will
 * effect flow tag calculation and thus RSS.
 */
क्रमागत npc_kpu_ld_ltype अणु
	NPC_LT_LD_TCP = 1,
	NPC_LT_LD_UDP,
	NPC_LT_LD_ICMP,
	NPC_LT_LD_SCTP,
	NPC_LT_LD_ICMP6,
	NPC_LT_LD_CUSTOM0,
	NPC_LT_LD_CUSTOM1,
	NPC_LT_LD_IGMP = 8,
	NPC_LT_LD_AH,
	NPC_LT_LD_GRE,
	NPC_LT_LD_NVGRE,
	NPC_LT_LD_NSH,
	NPC_LT_LD_TU_MPLS_IN_NSH,
	NPC_LT_LD_TU_MPLS_IN_IP,
पूर्ण;

क्रमागत npc_kpu_le_ltype अणु
	NPC_LT_LE_VXLAN = 1,
	NPC_LT_LE_GENEVE,
	NPC_LT_LE_ESP,
	NPC_LT_LE_GTPU = 4,
	NPC_LT_LE_VXLANGPE,
	NPC_LT_LE_GTPC,
	NPC_LT_LE_NSH,
	NPC_LT_LE_TU_MPLS_IN_GRE,
	NPC_LT_LE_TU_NSH_IN_GRE,
	NPC_LT_LE_TU_MPLS_IN_UDP,
	NPC_LT_LE_CUSTOM0 = 0xE,
	NPC_LT_LE_CUSTOM1 = 0xF,
पूर्ण;

क्रमागत npc_kpu_lf_ltype अणु
	NPC_LT_LF_TU_ETHER = 1,
	NPC_LT_LF_TU_PPP,
	NPC_LT_LF_TU_MPLS_IN_VXLANGPE,
	NPC_LT_LF_TU_NSH_IN_VXLANGPE,
	NPC_LT_LF_TU_MPLS_IN_NSH,
	NPC_LT_LF_TU_3RD_NSH,
	NPC_LT_LF_CUSTOM0 = 0xE,
	NPC_LT_LF_CUSTOM1 = 0xF,
पूर्ण;

क्रमागत npc_kpu_lg_ltype अणु
	NPC_LT_LG_TU_IP = 1,
	NPC_LT_LG_TU_IP6,
	NPC_LT_LG_TU_ARP,
	NPC_LT_LG_TU_ETHER_IN_NSH,
	NPC_LT_LG_CUSTOM0 = 0xE,
	NPC_LT_LG_CUSTOM1 = 0xF,
पूर्ण;

/* Don't modअगरy Ltypes upto SCTP, otherwise it will
 * effect flow tag calculation and thus RSS.
 */
क्रमागत npc_kpu_lh_ltype अणु
	NPC_LT_LH_TU_TCP = 1,
	NPC_LT_LH_TU_UDP,
	NPC_LT_LH_TU_ICMP,
	NPC_LT_LH_TU_SCTP,
	NPC_LT_LH_TU_ICMP6,
	NPC_LT_LH_TU_IGMP = 8,
	NPC_LT_LH_TU_ESP,
	NPC_LT_LH_TU_AH,
	NPC_LT_LH_CUSTOM0 = 0xE,
	NPC_LT_LH_CUSTOM1 = 0xF,
पूर्ण;

/* NPC port kind defines how the incoming or outgoing packets
 * are processed. NPC accepts packets from up to 64 pkinds.
 * Software assigns pkind क्रम each incoming port such as CGX
 * Ethernet पूर्णांकerfaces, LBK पूर्णांकerfaces, etc.
 */
क्रमागत npc_pkind_type अणु
	NPC_TX_DEF_PKIND = 63ULL,	/* NIX-TX PKIND */
पूर्ण;

/* list of known and supported fields in packet header and
 * fields present in key काष्ठाure.
 */
क्रमागत key_fields अणु
	NPC_DMAC,
	NPC_SMAC,
	NPC_ETYPE,
	NPC_OUTER_VID,
	NPC_TOS,
	NPC_SIP_IPV4,
	NPC_DIP_IPV4,
	NPC_SIP_IPV6,
	NPC_DIP_IPV6,
	NPC_IPPROTO_TCP,
	NPC_IPPROTO_UDP,
	NPC_IPPROTO_SCTP,
	NPC_IPPROTO_AH,
	NPC_IPPROTO_ESP,
	NPC_IPPROTO_ICMP,
	NPC_IPPROTO_ICMP6,
	NPC_SPORT_TCP,
	NPC_DPORT_TCP,
	NPC_SPORT_UDP,
	NPC_DPORT_UDP,
	NPC_SPORT_SCTP,
	NPC_DPORT_SCTP,
	NPC_HEADER_FIELDS_MAX,
	NPC_CHAN = NPC_HEADER_FIELDS_MAX, /* Valid when Rx */
	NPC_PF_FUNC, /* Valid when Tx */
	NPC_ERRLEV,
	NPC_ERRCODE,
	NPC_LXMB,
	NPC_LA,
	NPC_LB,
	NPC_LC,
	NPC_LD,
	NPC_LE,
	NPC_LF,
	NPC_LG,
	NPC_LH,
	/* Ethertype क्रम untagged frame */
	NPC_ETYPE_ETHER,
	/* Ethertype क्रम single tagged frame */
	NPC_ETYPE_TAG1,
	/* Ethertype क्रम द्विगुन tagged frame */
	NPC_ETYPE_TAG2,
	/* outer vlan tci क्रम single tagged frame */
	NPC_VLAN_TAG1,
	/* outer vlan tci क्रम द्विगुन tagged frame */
	NPC_VLAN_TAG2,
	/* other header fields programmed to extract but not of our पूर्णांकerest */
	NPC_UNKNOWN,
	NPC_KEY_FIELDS_MAX,
पूर्ण;

काष्ठा npc_kpu_profile_cam अणु
	u8 state;
	u8 state_mask;
	u16 dp0;
	u16 dp0_mask;
	u16 dp1;
	u16 dp1_mask;
	u16 dp2;
	u16 dp2_mask;
पूर्ण;

काष्ठा npc_kpu_profile_action अणु
	u8 errlev;
	u8 errcode;
	u8 dp0_offset;
	u8 dp1_offset;
	u8 dp2_offset;
	u8 bypass_count;
	u8 parse_करोne;
	u8 next_state;
	u8 ptr_advance;
	u8 cap_ena;
	u8 lid;
	u8 ltype;
	u8 flags;
	u8 offset;
	u8 mask;
	u8 right;
	u8 shअगरt;
पूर्ण;

काष्ठा npc_kpu_profile अणु
	पूर्णांक cam_entries;
	पूर्णांक action_entries;
	स्थिर काष्ठा npc_kpu_profile_cam *cam;
	स्थिर काष्ठा npc_kpu_profile_action *action;
पूर्ण;

/* NPC KPU रेजिस्टर क्रमmats */
काष्ठा npc_kpu_cam अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u64 rsvd_63_56     : 8;
	u64 state          : 8;
	u64 dp2_data       : 16;
	u64 dp1_data       : 16;
	u64 dp0_data       : 16;
#अन्यथा
	u64 dp0_data       : 16;
	u64 dp1_data       : 16;
	u64 dp2_data       : 16;
	u64 state          : 8;
	u64 rsvd_63_56     : 8;
#पूर्ण_अगर
पूर्ण;

काष्ठा npc_kpu_action0 अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u64 rsvd_63_57     : 7;
	u64 byp_count      : 3;
	u64 capture_ena    : 1;
	u64 parse_करोne     : 1;
	u64 next_state     : 8;
	u64 rsvd_43        : 1;
	u64 capture_lid    : 3;
	u64 capture_ltype  : 4;
	u64 capture_flags  : 8;
	u64 ptr_advance    : 8;
	u64 var_len_offset : 8;
	u64 var_len_mask   : 8;
	u64 var_len_right  : 1;
	u64 var_len_shअगरt  : 3;
#अन्यथा
	u64 var_len_shअगरt  : 3;
	u64 var_len_right  : 1;
	u64 var_len_mask   : 8;
	u64 var_len_offset : 8;
	u64 ptr_advance    : 8;
	u64 capture_flags  : 8;
	u64 capture_ltype  : 4;
	u64 capture_lid    : 3;
	u64 rsvd_43        : 1;
	u64 next_state     : 8;
	u64 parse_करोne     : 1;
	u64 capture_ena    : 1;
	u64 byp_count      : 3;
	u64 rsvd_63_57     : 7;
#पूर्ण_अगर
पूर्ण;

काष्ठा npc_kpu_action1 अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u64 rsvd_63_36     : 28;
	u64 errlev         : 4;
	u64 errcode        : 8;
	u64 dp2_offset     : 8;
	u64 dp1_offset     : 8;
	u64 dp0_offset     : 8;
#अन्यथा
	u64 dp0_offset     : 8;
	u64 dp1_offset     : 8;
	u64 dp2_offset     : 8;
	u64 errcode        : 8;
	u64 errlev         : 4;
	u64 rsvd_63_36     : 28;
#पूर्ण_अगर
पूर्ण;

काष्ठा npc_kpu_pkind_cpi_def अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u64 ena            : 1;
	u64 rsvd_62_59     : 4;
	u64 lid            : 3;
	u64 ltype_match    : 4;
	u64 ltype_mask     : 4;
	u64 flags_match    : 8;
	u64 flags_mask     : 8;
	u64 add_offset     : 8;
	u64 add_mask       : 8;
	u64 rsvd_15        : 1;
	u64 add_shअगरt      : 3;
	u64 rsvd_11_10     : 2;
	u64 cpi_base       : 10;
#अन्यथा
	u64 cpi_base       : 10;
	u64 rsvd_11_10     : 2;
	u64 add_shअगरt      : 3;
	u64 rsvd_15        : 1;
	u64 add_mask       : 8;
	u64 add_offset     : 8;
	u64 flags_mask     : 8;
	u64 flags_match    : 8;
	u64 ltype_mask     : 4;
	u64 ltype_match    : 4;
	u64 lid            : 3;
	u64 rsvd_62_59     : 4;
	u64 ena            : 1;
#पूर्ण_अगर
पूर्ण;

काष्ठा nix_rx_action अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u64	rsvd_63_61	:3;
	u64	flow_key_alg	:5;
	u64	match_id	:16;
	u64	index		:20;
	u64	pf_func		:16;
	u64	op		:4;
#अन्यथा
	u64	op		:4;
	u64	pf_func		:16;
	u64	index		:20;
	u64	match_id	:16;
	u64	flow_key_alg	:5;
	u64	rsvd_63_61	:3;
#पूर्ण_अगर
पूर्ण;

/* NPC_AF_INTFX_KEX_CFG field masks */
#घोषणा NPC_PARSE_NIBBLE		GENMASK_ULL(30, 0)

/* NPC_PARSE_KEX_S nibble definitions क्रम each field */
#घोषणा NPC_PARSE_NIBBLE_CHAN		GENMASK_ULL(2, 0)
#घोषणा NPC_PARSE_NIBBLE_ERRLEV		BIT_ULL(3)
#घोषणा NPC_PARSE_NIBBLE_ERRCODE	GENMASK_ULL(5, 4)
#घोषणा NPC_PARSE_NIBBLE_L2L3_BCAST	BIT_ULL(6)
#घोषणा NPC_PARSE_NIBBLE_LA_FLAGS	GENMASK_ULL(8, 7)
#घोषणा NPC_PARSE_NIBBLE_LA_LTYPE	BIT_ULL(9)
#घोषणा NPC_PARSE_NIBBLE_LB_FLAGS	GENMASK_ULL(11, 10)
#घोषणा NPC_PARSE_NIBBLE_LB_LTYPE	BIT_ULL(12)
#घोषणा NPC_PARSE_NIBBLE_LC_FLAGS	GENMASK_ULL(14, 13)
#घोषणा NPC_PARSE_NIBBLE_LC_LTYPE	BIT_ULL(15)
#घोषणा NPC_PARSE_NIBBLE_LD_FLAGS	GENMASK_ULL(17, 16)
#घोषणा NPC_PARSE_NIBBLE_LD_LTYPE	BIT_ULL(18)
#घोषणा NPC_PARSE_NIBBLE_LE_FLAGS	GENMASK_ULL(20, 19)
#घोषणा NPC_PARSE_NIBBLE_LE_LTYPE	BIT_ULL(21)
#घोषणा NPC_PARSE_NIBBLE_LF_FLAGS	GENMASK_ULL(23, 22)
#घोषणा NPC_PARSE_NIBBLE_LF_LTYPE	BIT_ULL(24)
#घोषणा NPC_PARSE_NIBBLE_LG_FLAGS	GENMASK_ULL(26, 25)
#घोषणा NPC_PARSE_NIBBLE_LG_LTYPE	BIT_ULL(27)
#घोषणा NPC_PARSE_NIBBLE_LH_FLAGS	GENMASK_ULL(29, 28)
#घोषणा NPC_PARSE_NIBBLE_LH_LTYPE	BIT_ULL(30)

काष्ठा nix_tx_action अणु
#अगर defined(__BIG_ENDIAN_BITFIELD)
	u64	rsvd_63_48	:16;
	u64	match_id	:16;
	u64	index		:20;
	u64	rsvd_11_8	:8;
	u64	op		:4;
#अन्यथा
	u64	op		:4;
	u64	rsvd_11_8	:8;
	u64	index		:20;
	u64	match_id	:16;
	u64	rsvd_63_48	:16;
#पूर्ण_अगर
पूर्ण;

/* NIX Receive Vtag Action Structure */
#घोषणा RX_VTAG0_VALID_BIT		BIT_ULL(15)
#घोषणा RX_VTAG0_TYPE_MASK		GENMASK_ULL(14, 12)
#घोषणा RX_VTAG0_LID_MASK		GENMASK_ULL(10, 8)
#घोषणा RX_VTAG0_RELPTR_MASK		GENMASK_ULL(7, 0)
#घोषणा RX_VTAG1_VALID_BIT		BIT_ULL(47)
#घोषणा RX_VTAG1_TYPE_MASK		GENMASK_ULL(46, 44)
#घोषणा RX_VTAG1_LID_MASK		GENMASK_ULL(42, 40)
#घोषणा RX_VTAG1_RELPTR_MASK		GENMASK_ULL(39, 32)

/* NIX Transmit Vtag Action Structure */
#घोषणा TX_VTAG0_DEF_MASK		GENMASK_ULL(25, 16)
#घोषणा TX_VTAG0_OP_MASK		GENMASK_ULL(13, 12)
#घोषणा TX_VTAG0_LID_MASK		GENMASK_ULL(10, 8)
#घोषणा TX_VTAG0_RELPTR_MASK		GENMASK_ULL(7, 0)
#घोषणा TX_VTAG1_DEF_MASK		GENMASK_ULL(57, 48)
#घोषणा TX_VTAG1_OP_MASK		GENMASK_ULL(45, 44)
#घोषणा TX_VTAG1_LID_MASK		GENMASK_ULL(42, 40)
#घोषणा TX_VTAG1_RELPTR_MASK		GENMASK_ULL(39, 32)

/* NPC MCAM reserved entry index per nixlf */
#घोषणा NIXLF_UCAST_ENTRY	0
#घोषणा NIXLF_BCAST_ENTRY	1
#घोषणा NIXLF_PROMISC_ENTRY	2

काष्ठा npc_mcam_kex अणु
	/* MKEX Profle Header */
	u64 mkex_sign; /* "mcam-kex-profile" (8 bytes/ASCII अक्षरacters) */
	u8 name[MKEX_NAME_LEN];   /* MKEX Profile name */
	u64 cpu_model;   /* Format as profiled by CPU hardware */
	u64 kpu_version; /* KPU firmware/profile version */
	u64 reserved; /* Reserved क्रम extension */

	/* MKEX Profle Data */
	u64 keyx_cfg[NPC_MAX_INTF]; /* NPC_AF_INTF(0..1)_KEX_CFG */
	/* NPC_AF_KEX_LDATA(0..1)_FLAGS_CFG */
	u64 kex_ld_flags[NPC_MAX_LD];
	/* NPC_AF_INTF(0..1)_LID(0..7)_LT(0..15)_LD(0..1)_CFG */
	u64 पूर्णांकf_lid_lt_ld[NPC_MAX_INTF][NPC_MAX_LID][NPC_MAX_LT][NPC_MAX_LD];
	/* NPC_AF_INTF(0..1)_LDATA(0..1)_FLAGS(0..15)_CFG */
	u64 पूर्णांकf_ld_flags[NPC_MAX_INTF][NPC_MAX_LD][NPC_MAX_LFL];
पूर्ण __packed;

काष्ठा npc_lt_def अणु
	u8	ltype_mask;
	u8	ltype_match;
	u8	lid;
पूर्ण;

काष्ठा npc_lt_def_ipsec अणु
	u8	ltype_mask;
	u8	ltype_match;
	u8	lid;
	u8	spi_offset;
	u8	spi_nz;
पूर्ण;

काष्ठा npc_lt_def_cfg अणु
	काष्ठा npc_lt_def	rx_ol2;
	काष्ठा npc_lt_def	rx_oip4;
	काष्ठा npc_lt_def	rx_iip4;
	काष्ठा npc_lt_def	rx_oip6;
	काष्ठा npc_lt_def	rx_iip6;
	काष्ठा npc_lt_def	rx_otcp;
	काष्ठा npc_lt_def	rx_itcp;
	काष्ठा npc_lt_def	rx_oudp;
	काष्ठा npc_lt_def	rx_iudp;
	काष्ठा npc_lt_def	rx_osctp;
	काष्ठा npc_lt_def	rx_isctp;
	काष्ठा npc_lt_def_ipsec	rx_ipsec[2];
	काष्ठा npc_lt_def	pck_ol2;
	काष्ठा npc_lt_def	pck_oip4;
	काष्ठा npc_lt_def	pck_oip6;
	काष्ठा npc_lt_def	pck_iip4;
पूर्ण;

काष्ठा rvu_npc_mcam_rule अणु
	काष्ठा flow_msg packet;
	काष्ठा flow_msg mask;
	u8 पूर्णांकf;
	जोड़ अणु
		काष्ठा nix_tx_action tx_action;
		काष्ठा nix_rx_action rx_action;
	पूर्ण;
	u64 vtag_action;
	काष्ठा list_head list;
	u64 features;
	u16 owner;
	u16 entry;
	u16 cntr;
	bool has_cntr;
	u8 शेष_rule;
	bool enable;
	bool vfvlan_cfg;
पूर्ण;

#पूर्ण_अगर /* NPC_H */
