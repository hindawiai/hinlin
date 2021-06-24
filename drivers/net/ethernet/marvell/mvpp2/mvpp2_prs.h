<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header Parser definitions क्रम Marvell PPv2 Network Controller
 *
 * Copyright (C) 2014 Marvell
 *
 * Marcin Wojtas <mw@semihalf.com>
 */
#अगर_अघोषित _MVPP2_PRS_H_
#घोषणा _MVPP2_PRS_H_

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mvpp2.h"

/* Parser स्थिरants */
#घोषणा MVPP2_PRS_TCAM_SRAM_SIZE	256
#घोषणा MVPP2_PRS_TCAM_WORDS		6
#घोषणा MVPP2_PRS_SRAM_WORDS		4
#घोषणा MVPP2_PRS_FLOW_ID_SIZE		64
#घोषणा MVPP2_PRS_FLOW_ID_MASK		0x3f
#घोषणा MVPP2_PRS_TCAM_ENTRY_INVALID	1
#घोषणा MVPP2_PRS_TCAM_DSA_TAGGED_BIT	BIT(5)
#घोषणा MVPP2_PRS_IPV4_HEAD		0x40
#घोषणा MVPP2_PRS_IPV4_HEAD_MASK	0xf0
#घोषणा MVPP2_PRS_IPV4_MC		0xe0
#घोषणा MVPP2_PRS_IPV4_MC_MASK		0xf0
#घोषणा MVPP2_PRS_IPV4_BC_MASK		0xff
#घोषणा MVPP2_PRS_IPV4_IHL_MIN		0x5
#घोषणा MVPP2_PRS_IPV4_IHL_MAX		0xf
#घोषणा MVPP2_PRS_IPV4_IHL_MASK		0xf
#घोषणा MVPP2_PRS_IPV6_MC		0xff
#घोषणा MVPP2_PRS_IPV6_MC_MASK		0xff
#घोषणा MVPP2_PRS_IPV6_HOP_MASK		0xff
#घोषणा MVPP2_PRS_TCAM_PROTO_MASK	0xff
#घोषणा MVPP2_PRS_TCAM_PROTO_MASK_L	0x3f
#घोषणा MVPP2_PRS_DBL_VLANS_MAX		100
#घोषणा MVPP2_PRS_CAST_MASK		BIT(0)
#घोषणा MVPP2_PRS_MCAST_VAL		BIT(0)
#घोषणा MVPP2_PRS_UCAST_VAL		0x0

/* Tcam काष्ठाure:
 * - lookup ID - 4 bits
 * - port ID - 1 byte
 * - additional inक्रमmation - 1 byte
 * - header data - 8 bytes
 * The fields are represented by MVPP2_PRS_TCAM_DATA_REG(5)->(0).
 */
#घोषणा MVPP2_PRS_AI_BITS			8
#घोषणा MVPP2_PRS_AI_MASK			0xff
#घोषणा MVPP2_PRS_PORT_MASK			0xff
#घोषणा MVPP2_PRS_LU_MASK			0xf

/* TCAM entries in रेजिस्टरs are accessed using 16 data bits + 16 enable bits */
#घोषणा MVPP2_PRS_BYTE_TO_WORD(byte)	((byte) / 2)
#घोषणा MVPP2_PRS_BYTE_IN_WORD(byte)	((byte) % 2)

#घोषणा MVPP2_PRS_TCAM_EN(data)		((data) << 16)
#घोषणा MVPP2_PRS_TCAM_AI_WORD		4
#घोषणा MVPP2_PRS_TCAM_AI(ai)		(ai)
#घोषणा MVPP2_PRS_TCAM_AI_EN(ai)	MVPP2_PRS_TCAM_EN(MVPP2_PRS_TCAM_AI(ai))
#घोषणा MVPP2_PRS_TCAM_PORT_WORD	4
#घोषणा MVPP2_PRS_TCAM_PORT(p)		((p) << 8)
#घोषणा MVPP2_PRS_TCAM_PORT_EN(p)	MVPP2_PRS_TCAM_EN(MVPP2_PRS_TCAM_PORT(p))
#घोषणा MVPP2_PRS_TCAM_LU_WORD		5
#घोषणा MVPP2_PRS_TCAM_LU(lu)		(lu)
#घोषणा MVPP2_PRS_TCAM_LU_EN(lu)	MVPP2_PRS_TCAM_EN(MVPP2_PRS_TCAM_LU(lu))
#घोषणा MVPP2_PRS_TCAM_INV_WORD		5

#घोषणा MVPP2_PRS_VID_TCAM_BYTE         2

/* TCAM range क्रम unicast and multicast filtering. We have 25 entries per port,
 * with 4 dedicated to UC filtering and the rest to multicast filtering.
 * Additionnally we reserve one entry क्रम the broadcast address, and one क्रम
 * each port's own address.
 */
#घोषणा MVPP2_PRS_MAC_UC_MC_FILT_MAX	25
#घोषणा MVPP2_PRS_MAC_RANGE_SIZE	80

/* Number of entries per port dedicated to UC and MC filtering */
#घोषणा MVPP2_PRS_MAC_UC_FILT_MAX	4
#घोषणा MVPP2_PRS_MAC_MC_FILT_MAX	(MVPP2_PRS_MAC_UC_MC_FILT_MAX - \
					 MVPP2_PRS_MAC_UC_FILT_MAX)

/* There is a TCAM range reserved क्रम VLAN filtering entries, range size is 33
 * 10 VLAN ID filter entries per port
 * 1 शेष VLAN filter entry per port
 * It is assumed that there are 3 ports क्रम filter, not including loopback port
 */
#घोषणा MVPP2_PRS_VLAN_FILT_MAX		11
#घोषणा MVPP2_PRS_VLAN_FILT_RANGE_SIZE	33

#घोषणा MVPP2_PRS_VLAN_FILT_MAX_ENTRY   (MVPP2_PRS_VLAN_FILT_MAX - 2)
#घोषणा MVPP2_PRS_VLAN_FILT_DFLT_ENTRY  (MVPP2_PRS_VLAN_FILT_MAX - 1)

/* Tcam entries ID */
#घोषणा MVPP2_PE_DROP_ALL		0
#घोषणा MVPP2_PE_FIRST_FREE_TID		1

/* MAC filtering range */
#घोषणा MVPP2_PE_MAC_RANGE_END		(MVPP2_PE_VID_FILT_RANGE_START - 1)
#घोषणा MVPP2_PE_MAC_RANGE_START	(MVPP2_PE_MAC_RANGE_END - \
						MVPP2_PRS_MAC_RANGE_SIZE + 1)
/* VLAN filtering range */
#घोषणा MVPP2_PE_VID_FILT_RANGE_END     (MVPP2_PRS_TCAM_SRAM_SIZE - 32)
#घोषणा MVPP2_PE_VID_FILT_RANGE_START   (MVPP2_PE_VID_FILT_RANGE_END - \
					 MVPP2_PRS_VLAN_FILT_RANGE_SIZE + 1)
#घोषणा MVPP2_PE_LAST_FREE_TID          (MVPP2_PE_MAC_RANGE_START - 1)
#घोषणा MVPP2_PE_MH_SKIP_PRS		(MVPP2_PRS_TCAM_SRAM_SIZE - 31)
#घोषणा MVPP2_PE_IP6_EXT_PROTO_UN	(MVPP2_PRS_TCAM_SRAM_SIZE - 30)
#घोषणा MVPP2_PE_IP6_ADDR_UN		(MVPP2_PRS_TCAM_SRAM_SIZE - 29)
#घोषणा MVPP2_PE_IP4_ADDR_UN		(MVPP2_PRS_TCAM_SRAM_SIZE - 28)
#घोषणा MVPP2_PE_LAST_DEFAULT_FLOW	(MVPP2_PRS_TCAM_SRAM_SIZE - 27)
#घोषणा MVPP2_PE_FIRST_DEFAULT_FLOW	(MVPP2_PRS_TCAM_SRAM_SIZE - 22)
#घोषणा MVPP2_PE_EDSA_TAGGED		(MVPP2_PRS_TCAM_SRAM_SIZE - 21)
#घोषणा MVPP2_PE_EDSA_UNTAGGED		(MVPP2_PRS_TCAM_SRAM_SIZE - 20)
#घोषणा MVPP2_PE_DSA_TAGGED		(MVPP2_PRS_TCAM_SRAM_SIZE - 19)
#घोषणा MVPP2_PE_DSA_UNTAGGED		(MVPP2_PRS_TCAM_SRAM_SIZE - 18)
#घोषणा MVPP2_PE_ETYPE_EDSA_TAGGED	(MVPP2_PRS_TCAM_SRAM_SIZE - 17)
#घोषणा MVPP2_PE_ETYPE_EDSA_UNTAGGED	(MVPP2_PRS_TCAM_SRAM_SIZE - 16)
#घोषणा MVPP2_PE_ETYPE_DSA_TAGGED	(MVPP2_PRS_TCAM_SRAM_SIZE - 15)
#घोषणा MVPP2_PE_ETYPE_DSA_UNTAGGED	(MVPP2_PRS_TCAM_SRAM_SIZE - 14)
#घोषणा MVPP2_PE_MH_DEFAULT		(MVPP2_PRS_TCAM_SRAM_SIZE - 13)
#घोषणा MVPP2_PE_DSA_DEFAULT		(MVPP2_PRS_TCAM_SRAM_SIZE - 12)
#घोषणा MVPP2_PE_IP6_PROTO_UN		(MVPP2_PRS_TCAM_SRAM_SIZE - 11)
#घोषणा MVPP2_PE_IP4_PROTO_UN		(MVPP2_PRS_TCAM_SRAM_SIZE - 10)
#घोषणा MVPP2_PE_ETH_TYPE_UN		(MVPP2_PRS_TCAM_SRAM_SIZE - 9)
#घोषणा MVPP2_PE_VID_FLTR_DEFAULT	(MVPP2_PRS_TCAM_SRAM_SIZE - 8)
#घोषणा MVPP2_PE_VID_EDSA_FLTR_DEFAULT	(MVPP2_PRS_TCAM_SRAM_SIZE - 7)
#घोषणा MVPP2_PE_VLAN_DBL		(MVPP2_PRS_TCAM_SRAM_SIZE - 6)
#घोषणा MVPP2_PE_VLAN_NONE		(MVPP2_PRS_TCAM_SRAM_SIZE - 5)
#घोषणा MVPP2_PE_FC_DROP		(MVPP2_PRS_TCAM_SRAM_SIZE - 4)
#घोषणा MVPP2_PE_MAC_MC_PROMISCUOUS	(MVPP2_PRS_TCAM_SRAM_SIZE - 3)
#घोषणा MVPP2_PE_MAC_UC_PROMISCUOUS	(MVPP2_PRS_TCAM_SRAM_SIZE - 2)
#घोषणा MVPP2_PE_MAC_NON_PROMISCUOUS	(MVPP2_PRS_TCAM_SRAM_SIZE - 1)

#घोषणा MVPP2_PRS_VID_PORT_FIRST(port)	(MVPP2_PE_VID_FILT_RANGE_START + \
					 ((port) * MVPP2_PRS_VLAN_FILT_MAX))
#घोषणा MVPP2_PRS_VID_PORT_LAST(port)	(MVPP2_PRS_VID_PORT_FIRST(port) \
					 + MVPP2_PRS_VLAN_FILT_MAX_ENTRY)
/* Index of शेष vid filter क्रम given port */
#घोषणा MVPP2_PRS_VID_PORT_DFLT(port)	(MVPP2_PRS_VID_PORT_FIRST(port) \
					 + MVPP2_PRS_VLAN_FILT_DFLT_ENTRY)

/* Sram काष्ठाure
 * The fields are represented by MVPP2_PRS_TCAM_DATA_REG(3)->(0).
 */
#घोषणा MVPP2_PRS_SRAM_RI_OFFS			0
#घोषणा MVPP2_PRS_SRAM_RI_WORD			0
#घोषणा MVPP2_PRS_SRAM_RI_CTRL_OFFS		32
#घोषणा MVPP2_PRS_SRAM_RI_CTRL_WORD		1
#घोषणा MVPP2_PRS_SRAM_RI_CTRL_BITS		32
#घोषणा MVPP2_PRS_SRAM_SHIFT_OFFS		64
#घोषणा MVPP2_PRS_SRAM_SHIFT_SIGN_BIT		72
#घोषणा MVPP2_PRS_SRAM_SHIFT_MASK		0xff
#घोषणा MVPP2_PRS_SRAM_UDF_OFFS			73
#घोषणा MVPP2_PRS_SRAM_UDF_BITS			8
#घोषणा MVPP2_PRS_SRAM_UDF_MASK			0xff
#घोषणा MVPP2_PRS_SRAM_UDF_SIGN_BIT		81
#घोषणा MVPP2_PRS_SRAM_UDF_TYPE_OFFS		82
#घोषणा MVPP2_PRS_SRAM_UDF_TYPE_MASK		0x7
#घोषणा MVPP2_PRS_SRAM_UDF_TYPE_L3		1
#घोषणा MVPP2_PRS_SRAM_UDF_TYPE_L4		4
#घोषणा MVPP2_PRS_SRAM_OP_SEL_SHIFT_OFFS	85
#घोषणा MVPP2_PRS_SRAM_OP_SEL_SHIFT_MASK	0x3
#घोषणा MVPP2_PRS_SRAM_OP_SEL_SHIFT_ADD		1
#घोषणा MVPP2_PRS_SRAM_OP_SEL_SHIFT_IP4_ADD	2
#घोषणा MVPP2_PRS_SRAM_OP_SEL_SHIFT_IP6_ADD	3
#घोषणा MVPP2_PRS_SRAM_OP_SEL_UDF_OFFS		87
#घोषणा MVPP2_PRS_SRAM_OP_SEL_UDF_BITS		2
#घोषणा MVPP2_PRS_SRAM_OP_SEL_UDF_MASK		0x3
#घोषणा MVPP2_PRS_SRAM_OP_SEL_UDF_ADD		0
#घोषणा MVPP2_PRS_SRAM_OP_SEL_UDF_IP4_ADD	2
#घोषणा MVPP2_PRS_SRAM_OP_SEL_UDF_IP6_ADD	3
#घोषणा MVPP2_PRS_SRAM_OP_SEL_BASE_OFFS		89
#घोषणा MVPP2_PRS_SRAM_AI_OFFS			90
#घोषणा MVPP2_PRS_SRAM_AI_CTRL_OFFS		98
#घोषणा MVPP2_PRS_SRAM_AI_CTRL_BITS		8
#घोषणा MVPP2_PRS_SRAM_AI_MASK			0xff
#घोषणा MVPP2_PRS_SRAM_NEXT_LU_OFFS		106
#घोषणा MVPP2_PRS_SRAM_NEXT_LU_MASK		0xf
#घोषणा MVPP2_PRS_SRAM_LU_DONE_BIT		110
#घोषणा MVPP2_PRS_SRAM_LU_GEN_BIT		111

/* Sram result info bits assignment */
#घोषणा MVPP2_PRS_RI_MAC_ME_MASK		0x1
#घोषणा MVPP2_PRS_RI_DSA_MASK			0x2
#घोषणा MVPP2_PRS_RI_VLAN_MASK			(BIT(2) | BIT(3))
#घोषणा MVPP2_PRS_RI_VLAN_NONE			0x0
#घोषणा MVPP2_PRS_RI_VLAN_SINGLE		BIT(2)
#घोषणा MVPP2_PRS_RI_VLAN_DOUBLE		BIT(3)
#घोषणा MVPP2_PRS_RI_VLAN_TRIPLE		(BIT(2) | BIT(3))
#घोषणा MVPP2_PRS_RI_CPU_CODE_MASK		0x70
#घोषणा MVPP2_PRS_RI_CPU_CODE_RX_SPEC		BIT(4)
#घोषणा MVPP2_PRS_RI_L2_CAST_MASK		(BIT(9) | BIT(10))
#घोषणा MVPP2_PRS_RI_L2_UCAST			0x0
#घोषणा MVPP2_PRS_RI_L2_MCAST			BIT(9)
#घोषणा MVPP2_PRS_RI_L2_BCAST			BIT(10)
#घोषणा MVPP2_PRS_RI_PPPOE_MASK			0x800
#घोषणा MVPP2_PRS_RI_L3_PROTO_MASK		(BIT(12) | BIT(13) | BIT(14))
#घोषणा MVPP2_PRS_RI_L3_UN			0x0
#घोषणा MVPP2_PRS_RI_L3_IP4			BIT(12)
#घोषणा MVPP2_PRS_RI_L3_IP4_OPT			BIT(13)
#घोषणा MVPP2_PRS_RI_L3_IP4_OTHER		(BIT(12) | BIT(13))
#घोषणा MVPP2_PRS_RI_L3_IP6			BIT(14)
#घोषणा MVPP2_PRS_RI_L3_IP6_EXT			(BIT(12) | BIT(14))
#घोषणा MVPP2_PRS_RI_L3_ARP			(BIT(13) | BIT(14))
#घोषणा MVPP2_PRS_RI_L3_ADDR_MASK		(BIT(15) | BIT(16))
#घोषणा MVPP2_PRS_RI_L3_UCAST			0x0
#घोषणा MVPP2_PRS_RI_L3_MCAST			BIT(15)
#घोषणा MVPP2_PRS_RI_L3_BCAST			(BIT(15) | BIT(16))
#घोषणा MVPP2_PRS_RI_IP_FRAG_MASK		0x20000
#घोषणा MVPP2_PRS_RI_IP_FRAG_TRUE		BIT(17)
#घोषणा MVPP2_PRS_RI_UDF3_MASK			0x300000
#घोषणा MVPP2_PRS_RI_UDF3_RX_SPECIAL		BIT(21)
#घोषणा MVPP2_PRS_RI_L4_PROTO_MASK		0x1c00000
#घोषणा MVPP2_PRS_RI_L4_TCP			BIT(22)
#घोषणा MVPP2_PRS_RI_L4_UDP			BIT(23)
#घोषणा MVPP2_PRS_RI_L4_OTHER			(BIT(22) | BIT(23))
#घोषणा MVPP2_PRS_RI_UDF7_MASK			0x60000000
#घोषणा MVPP2_PRS_RI_UDF7_IP6_LITE		BIT(29)
#घोषणा MVPP2_PRS_RI_DROP_MASK			0x80000000

#घोषणा MVPP2_PRS_IP_MASK			(MVPP2_PRS_RI_L3_PROTO_MASK | \
						MVPP2_PRS_RI_IP_FRAG_MASK | \
						MVPP2_PRS_RI_L4_PROTO_MASK)

/* Sram additional info bits assignment */
#घोषणा MVPP2_PRS_IPV4_DIP_AI_BIT		BIT(0)
#घोषणा MVPP2_PRS_IPV6_NO_EXT_AI_BIT		BIT(0)
#घोषणा MVPP2_PRS_IPV6_EXT_AI_BIT		BIT(1)
#घोषणा MVPP2_PRS_IPV6_EXT_AH_AI_BIT		BIT(2)
#घोषणा MVPP2_PRS_IPV6_EXT_AH_LEN_AI_BIT	BIT(3)
#घोषणा MVPP2_PRS_IPV6_EXT_AH_L4_AI_BIT		BIT(4)
#घोषणा MVPP2_PRS_SINGLE_VLAN_AI		0
#घोषणा MVPP2_PRS_DBL_VLAN_AI_BIT		BIT(7)
#घोषणा MVPP2_PRS_EDSA_VID_AI_BIT		BIT(0)

/* DSA/EDSA type */
#घोषणा MVPP2_PRS_TAGGED		true
#घोषणा MVPP2_PRS_UNTAGGED		false
#घोषणा MVPP2_PRS_EDSA			true
#घोषणा MVPP2_PRS_DSA			false

/* MAC entries, shaकरोw udf */
क्रमागत mvpp2_prs_udf अणु
	MVPP2_PRS_UDF_MAC_DEF,
	MVPP2_PRS_UDF_MAC_RANGE,
	MVPP2_PRS_UDF_L2_DEF,
	MVPP2_PRS_UDF_L2_DEF_COPY,
	MVPP2_PRS_UDF_L2_USER,
पूर्ण;

/* Lookup ID */
क्रमागत mvpp2_prs_lookup अणु
	MVPP2_PRS_LU_MH,
	MVPP2_PRS_LU_MAC,
	MVPP2_PRS_LU_DSA,
	MVPP2_PRS_LU_VLAN,
	MVPP2_PRS_LU_VID,
	MVPP2_PRS_LU_L2,
	MVPP2_PRS_LU_PPPOE,
	MVPP2_PRS_LU_IP4,
	MVPP2_PRS_LU_IP6,
	MVPP2_PRS_LU_FLOWS,
	MVPP2_PRS_LU_LAST,
पूर्ण;

काष्ठा mvpp2_prs_entry अणु
	u32 index;
	u32 tcam[MVPP2_PRS_TCAM_WORDS];
	u32 sram[MVPP2_PRS_SRAM_WORDS];
पूर्ण;

काष्ठा mvpp2_prs_result_info अणु
	u32 ri;
	u32 ri_mask;
पूर्ण;

काष्ठा mvpp2_prs_shaकरोw अणु
	bool valid;
	bool finish;

	/* Lookup ID */
	पूर्णांक lu;

	/* User defined offset */
	पूर्णांक udf;

	/* Result info */
	u32 ri;
	u32 ri_mask;
पूर्ण;

पूर्णांक mvpp2_prs_शेष_init(काष्ठा platक्रमm_device *pdev, काष्ठा mvpp2 *priv);

पूर्णांक mvpp2_prs_init_from_hw(काष्ठा mvpp2 *priv, काष्ठा mvpp2_prs_entry *pe,
			   पूर्णांक tid);

अचिन्हित पूर्णांक mvpp2_prs_tcam_port_map_get(काष्ठा mvpp2_prs_entry *pe);

व्योम mvpp2_prs_tcam_data_byte_get(काष्ठा mvpp2_prs_entry *pe,
				  अचिन्हित पूर्णांक offs, अचिन्हित अक्षर *byte,
				  अचिन्हित अक्षर *enable);

पूर्णांक mvpp2_prs_mac_da_accept(काष्ठा mvpp2_port *port, स्थिर u8 *da, bool add);

पूर्णांक mvpp2_prs_tag_mode_set(काष्ठा mvpp2 *priv, पूर्णांक port, पूर्णांक type);

पूर्णांक mvpp2_prs_add_flow(काष्ठा mvpp2 *priv, पूर्णांक flow, u32 ri, u32 ri_mask);

पूर्णांक mvpp2_prs_def_flow(काष्ठा mvpp2_port *port);

व्योम mvpp2_prs_vid_enable_filtering(काष्ठा mvpp2_port *port);

व्योम mvpp2_prs_vid_disable_filtering(काष्ठा mvpp2_port *port);

पूर्णांक mvpp2_prs_vid_entry_add(काष्ठा mvpp2_port *port, u16 vid);

व्योम mvpp2_prs_vid_entry_हटाओ(काष्ठा mvpp2_port *port, u16 vid);

व्योम mvpp2_prs_vid_हटाओ_all(काष्ठा mvpp2_port *port);

व्योम mvpp2_prs_mac_promisc_set(काष्ठा mvpp2 *priv, पूर्णांक port,
			       क्रमागत mvpp2_prs_l2_cast l2_cast, bool add);

व्योम mvpp2_prs_mac_del_all(काष्ठा mvpp2_port *port);

पूर्णांक mvpp2_prs_update_mac_da(काष्ठा net_device *dev, स्थिर u8 *da);

पूर्णांक mvpp2_prs_hits(काष्ठा mvpp2 *priv, पूर्णांक index);

#पूर्ण_अगर
