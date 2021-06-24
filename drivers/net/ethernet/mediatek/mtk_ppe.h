<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Felix Fietkau <nbd@nbd.name> */

#अगर_अघोषित __MTK_PPE_H
#घोषणा __MTK_PPE_H

#समावेश <linux/kernel.h>
#समावेश <linux/bitfield.h>

#घोषणा MTK_ETH_PPE_BASE		0xc00

#घोषणा MTK_PPE_ENTRIES_SHIFT		3
#घोषणा MTK_PPE_ENTRIES			(1024 << MTK_PPE_ENTRIES_SHIFT)
#घोषणा MTK_PPE_HASH_MASK		(MTK_PPE_ENTRIES - 1)
#घोषणा MTK_PPE_WAIT_TIMEOUT_US		1000000

#घोषणा MTK_FOE_IB1_UNBIND_TIMESTAMP	GENMASK(7, 0)
#घोषणा MTK_FOE_IB1_UNBIND_PACKETS	GENMASK(23, 8)
#घोषणा MTK_FOE_IB1_UNBIND_PREBIND	BIT(24)

#घोषणा MTK_FOE_IB1_BIND_TIMESTAMP	GENMASK(14, 0)
#घोषणा MTK_FOE_IB1_BIND_KEEPALIVE	BIT(15)
#घोषणा MTK_FOE_IB1_BIND_VLAN_LAYER	GENMASK(18, 16)
#घोषणा MTK_FOE_IB1_BIND_PPPOE		BIT(19)
#घोषणा MTK_FOE_IB1_BIND_VLAN_TAG	BIT(20)
#घोषणा MTK_FOE_IB1_BIND_PKT_SAMPLE	BIT(21)
#घोषणा MTK_FOE_IB1_BIND_CACHE		BIT(22)
#घोषणा MTK_FOE_IB1_BIND_TUNNEL_DECAP	BIT(23)
#घोषणा MTK_FOE_IB1_BIND_TTL		BIT(24)

#घोषणा MTK_FOE_IB1_PACKET_TYPE		GENMASK(27, 25)
#घोषणा MTK_FOE_IB1_STATE		GENMASK(29, 28)
#घोषणा MTK_FOE_IB1_UDP			BIT(30)
#घोषणा MTK_FOE_IB1_STATIC		BIT(31)

क्रमागत अणु
	MTK_PPE_PKT_TYPE_IPV4_HNAPT = 0,
	MTK_PPE_PKT_TYPE_IPV4_ROUTE = 1,
	MTK_PPE_PKT_TYPE_BRIDGE = 2,
	MTK_PPE_PKT_TYPE_IPV4_DSLITE = 3,
	MTK_PPE_PKT_TYPE_IPV6_ROUTE_3T = 4,
	MTK_PPE_PKT_TYPE_IPV6_ROUTE_5T = 5,
	MTK_PPE_PKT_TYPE_IPV6_6RD = 7,
पूर्ण;

#घोषणा MTK_FOE_IB2_QID			GENMASK(3, 0)
#घोषणा MTK_FOE_IB2_PSE_QOS		BIT(4)
#घोषणा MTK_FOE_IB2_DEST_PORT		GENMASK(7, 5)
#घोषणा MTK_FOE_IB2_MULTICAST		BIT(8)

#घोषणा MTK_FOE_IB2_WHNAT_QID2		GENMASK(13, 12)
#घोषणा MTK_FOE_IB2_WHNAT_DEVIDX	BIT(16)
#घोषणा MTK_FOE_IB2_WHNAT_NAT		BIT(17)

#घोषणा MTK_FOE_IB2_PORT_MG		GENMASK(17, 12)

#घोषणा MTK_FOE_IB2_PORT_AG		GENMASK(23, 18)

#घोषणा MTK_FOE_IB2_DSCP		GENMASK(31, 24)

#घोषणा MTK_FOE_VLAN2_WHNAT_BSS		GEMMASK(5, 0)
#घोषणा MTK_FOE_VLAN2_WHNAT_WCID	GENMASK(13, 6)
#घोषणा MTK_FOE_VLAN2_WHNAT_RING	GENMASK(15, 14)

क्रमागत अणु
	MTK_FOE_STATE_INVALID,
	MTK_FOE_STATE_UNBIND,
	MTK_FOE_STATE_BIND,
	MTK_FOE_STATE_FIN
पूर्ण;

काष्ठा mtk_foe_mac_info अणु
	u16 vlan1;
	u16 etype;

	u32 dest_mac_hi;

	u16 vlan2;
	u16 dest_mac_lo;

	u32 src_mac_hi;

	u16 pppoe_id;
	u16 src_mac_lo;
पूर्ण;

काष्ठा mtk_foe_bridge अणु
	u32 dest_mac_hi;

	u16 src_mac_lo;
	u16 dest_mac_lo;

	u32 src_mac_hi;

	u32 ib2;

	u32 _rsv[5];

	u32 udf_tsid;
	काष्ठा mtk_foe_mac_info l2;
पूर्ण;

काष्ठा mtk_ipv4_tuple अणु
	u32 src_ip;
	u32 dest_ip;
	जोड़ अणु
		काष्ठा अणु
			u16 dest_port;
			u16 src_port;
		पूर्ण;
		काष्ठा अणु
			u8 protocol;
			u8 _pad[3]; /* fill with 0xa5a5a5 */
		पूर्ण;
		u32 ports;
	पूर्ण;
पूर्ण;

काष्ठा mtk_foe_ipv4 अणु
	काष्ठा mtk_ipv4_tuple orig;

	u32 ib2;

	काष्ठा mtk_ipv4_tuple new;

	u16 बारtamp;
	u16 _rsv0[3];

	u32 udf_tsid;

	काष्ठा mtk_foe_mac_info l2;
पूर्ण;

काष्ठा mtk_foe_ipv4_dslite अणु
	काष्ठा mtk_ipv4_tuple ip4;

	u32 tunnel_src_ip[4];
	u32 tunnel_dest_ip[4];

	u8 flow_label[3];
	u8 priority;

	u32 udf_tsid;

	u32 ib2;

	काष्ठा mtk_foe_mac_info l2;
पूर्ण;

काष्ठा mtk_foe_ipv6 अणु
	u32 src_ip[4];
	u32 dest_ip[4];

	जोड़ अणु
		काष्ठा अणु
			u8 protocol;
			u8 _pad[3]; /* fill with 0xa5a5a5 */
		पूर्ण; /* 3-tuple */
		काष्ठा अणु
			u16 dest_port;
			u16 src_port;
		पूर्ण; /* 5-tuple */
		u32 ports;
	पूर्ण;

	u32 _rsv[3];

	u32 udf;

	u32 ib2;
	काष्ठा mtk_foe_mac_info l2;
पूर्ण;

काष्ठा mtk_foe_ipv6_6rd अणु
	u32 src_ip[4];
	u32 dest_ip[4];
	u16 dest_port;
	u16 src_port;

	u32 tunnel_src_ip;
	u32 tunnel_dest_ip;

	u16 hdr_csum;
	u8 dscp;
	u8 ttl;

	u8 flag;
	u8 pad;
	u8 per_flow_6rd_id;
	u8 pad2;

	u32 ib2;
	काष्ठा mtk_foe_mac_info l2;
पूर्ण;

काष्ठा mtk_foe_entry अणु
	u32 ib1;

	जोड़ अणु
		काष्ठा mtk_foe_bridge bridge;
		काष्ठा mtk_foe_ipv4 ipv4;
		काष्ठा mtk_foe_ipv4_dslite dslite;
		काष्ठा mtk_foe_ipv6 ipv6;
		काष्ठा mtk_foe_ipv6_6rd ipv6_6rd;
		u32 data[19];
	पूर्ण;
पूर्ण;

क्रमागत अणु
	MTK_PPE_CPU_REASON_TTL_EXCEEDED			= 0x02,
	MTK_PPE_CPU_REASON_OPTION_HEADER		= 0x03,
	MTK_PPE_CPU_REASON_NO_FLOW			= 0x07,
	MTK_PPE_CPU_REASON_IPV4_FRAG			= 0x08,
	MTK_PPE_CPU_REASON_IPV4_DSLITE_FRAG		= 0x09,
	MTK_PPE_CPU_REASON_IPV4_DSLITE_NO_TCP_UDP	= 0x0a,
	MTK_PPE_CPU_REASON_IPV6_6RD_NO_TCP_UDP		= 0x0b,
	MTK_PPE_CPU_REASON_TCP_FIN_SYN_RST		= 0x0c,
	MTK_PPE_CPU_REASON_UN_HIT			= 0x0d,
	MTK_PPE_CPU_REASON_HIT_UNBIND			= 0x0e,
	MTK_PPE_CPU_REASON_HIT_UNBIND_RATE_REACHED	= 0x0f,
	MTK_PPE_CPU_REASON_HIT_BIND_TCP_FIN		= 0x10,
	MTK_PPE_CPU_REASON_HIT_TTL_1			= 0x11,
	MTK_PPE_CPU_REASON_HIT_BIND_VLAN_VIOLATION	= 0x12,
	MTK_PPE_CPU_REASON_KEEPALIVE_UC_OLD_HDR		= 0x13,
	MTK_PPE_CPU_REASON_KEEPALIVE_MC_NEW_HDR		= 0x14,
	MTK_PPE_CPU_REASON_KEEPALIVE_DUP_OLD_HDR	= 0x15,
	MTK_PPE_CPU_REASON_HIT_BIND_FORCE_CPU		= 0x16,
	MTK_PPE_CPU_REASON_TUNNEL_OPTION_HEADER		= 0x17,
	MTK_PPE_CPU_REASON_MULTICAST_TO_CPU		= 0x18,
	MTK_PPE_CPU_REASON_MULTICAST_TO_GMAC1_CPU	= 0x19,
	MTK_PPE_CPU_REASON_HIT_PRE_BIND			= 0x1a,
	MTK_PPE_CPU_REASON_PACKET_SAMPLING		= 0x1b,
	MTK_PPE_CPU_REASON_EXCEED_MTU			= 0x1c,
	MTK_PPE_CPU_REASON_PPE_BYPASS			= 0x1e,
	MTK_PPE_CPU_REASON_INVALID			= 0x1f,
पूर्ण;

काष्ठा mtk_ppe अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	पूर्णांक version;

	काष्ठा mtk_foe_entry *foe_table;
	dma_addr_t foe_phys;

	व्योम *acct_table;
पूर्ण;

पूर्णांक mtk_ppe_init(काष्ठा mtk_ppe *ppe, काष्ठा device *dev, व्योम __iomem *base,
		 पूर्णांक version);
पूर्णांक mtk_ppe_start(काष्ठा mtk_ppe *ppe);
पूर्णांक mtk_ppe_stop(काष्ठा mtk_ppe *ppe);

अटल अंतरभूत व्योम
mtk_foe_entry_clear(काष्ठा mtk_ppe *ppe, u16 hash)
अणु
	ppe->foe_table[hash].ib1 = 0;
	dma_wmb();
पूर्ण

अटल अंतरभूत पूर्णांक
mtk_foe_entry_बारtamp(काष्ठा mtk_ppe *ppe, u16 hash)
अणु
	u32 ib1 = READ_ONCE(ppe->foe_table[hash].ib1);

	अगर (FIELD_GET(MTK_FOE_IB1_STATE, ib1) != MTK_FOE_STATE_BIND)
		वापस -1;

	वापस FIELD_GET(MTK_FOE_IB1_BIND_TIMESTAMP, ib1);
पूर्ण

पूर्णांक mtk_foe_entry_prepare(काष्ठा mtk_foe_entry *entry, पूर्णांक type, पूर्णांक l4proto,
			  u8 pse_port, u8 *src_mac, u8 *dest_mac);
पूर्णांक mtk_foe_entry_set_pse_port(काष्ठा mtk_foe_entry *entry, u8 port);
पूर्णांक mtk_foe_entry_set_ipv4_tuple(काष्ठा mtk_foe_entry *entry, bool orig,
				 __be32 src_addr, __be16 src_port,
				 __be32 dest_addr, __be16 dest_port);
पूर्णांक mtk_foe_entry_set_ipv6_tuple(काष्ठा mtk_foe_entry *entry,
				 __be32 *src_addr, __be16 src_port,
				 __be32 *dest_addr, __be16 dest_port);
पूर्णांक mtk_foe_entry_set_dsa(काष्ठा mtk_foe_entry *entry, पूर्णांक port);
पूर्णांक mtk_foe_entry_set_vlan(काष्ठा mtk_foe_entry *entry, पूर्णांक vid);
पूर्णांक mtk_foe_entry_set_pppoe(काष्ठा mtk_foe_entry *entry, पूर्णांक sid);
पूर्णांक mtk_foe_entry_commit(काष्ठा mtk_ppe *ppe, काष्ठा mtk_foe_entry *entry,
			 u16 बारtamp);
पूर्णांक mtk_ppe_debugfs_init(काष्ठा mtk_ppe *ppe);

#पूर्ण_अगर
