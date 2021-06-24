<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (C) 2020 Felix Fietkau <nbd@nbd.name> */

#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "mtk_ppe.h"
#समावेश "mtk_ppe_regs.h"

अटल व्योम ppe_w32(काष्ठा mtk_ppe *ppe, u32 reg, u32 val)
अणु
	ग_लिखोl(val, ppe->base + reg);
पूर्ण

अटल u32 ppe_r32(काष्ठा mtk_ppe *ppe, u32 reg)
अणु
	वापस पढ़ोl(ppe->base + reg);
पूर्ण

अटल u32 ppe_m32(काष्ठा mtk_ppe *ppe, u32 reg, u32 mask, u32 set)
अणु
	u32 val;

	val = ppe_r32(ppe, reg);
	val &= ~mask;
	val |= set;
	ppe_w32(ppe, reg, val);

	वापस val;
पूर्ण

अटल u32 ppe_set(काष्ठा mtk_ppe *ppe, u32 reg, u32 val)
अणु
	वापस ppe_m32(ppe, reg, 0, val);
पूर्ण

अटल u32 ppe_clear(काष्ठा mtk_ppe *ppe, u32 reg, u32 val)
अणु
	वापस ppe_m32(ppe, reg, val, 0);
पूर्ण

अटल पूर्णांक mtk_ppe_रुको_busy(काष्ठा mtk_ppe *ppe)
अणु
	पूर्णांक ret;
	u32 val;

	ret = पढ़ोl_poll_समयout(ppe->base + MTK_PPE_GLO_CFG, val,
				 !(val & MTK_PPE_GLO_CFG_BUSY),
				 20, MTK_PPE_WAIT_TIMEOUT_US);

	अगर (ret)
		dev_err(ppe->dev, "PPE table busy");

	वापस ret;
पूर्ण

अटल व्योम mtk_ppe_cache_clear(काष्ठा mtk_ppe *ppe)
अणु
	ppe_set(ppe, MTK_PPE_CACHE_CTL, MTK_PPE_CACHE_CTL_CLEAR);
	ppe_clear(ppe, MTK_PPE_CACHE_CTL, MTK_PPE_CACHE_CTL_CLEAR);
पूर्ण

अटल व्योम mtk_ppe_cache_enable(काष्ठा mtk_ppe *ppe, bool enable)
अणु
	mtk_ppe_cache_clear(ppe);

	ppe_m32(ppe, MTK_PPE_CACHE_CTL, MTK_PPE_CACHE_CTL_EN,
		enable * MTK_PPE_CACHE_CTL_EN);
पूर्ण

अटल u32 mtk_ppe_hash_entry(काष्ठा mtk_foe_entry *e)
अणु
	u32 hv1, hv2, hv3;
	u32 hash;

	चयन (FIELD_GET(MTK_FOE_IB1_PACKET_TYPE, e->ib1)) अणु
		हाल MTK_PPE_PKT_TYPE_BRIDGE:
			hv1 = e->bridge.src_mac_lo;
			hv1 ^= ((e->bridge.src_mac_hi & 0xffff) << 16);
			hv2 = e->bridge.src_mac_hi >> 16;
			hv2 ^= e->bridge.dest_mac_lo;
			hv3 = e->bridge.dest_mac_hi;
			अवरोध;
		हाल MTK_PPE_PKT_TYPE_IPV4_ROUTE:
		हाल MTK_PPE_PKT_TYPE_IPV4_HNAPT:
			hv1 = e->ipv4.orig.ports;
			hv2 = e->ipv4.orig.dest_ip;
			hv3 = e->ipv4.orig.src_ip;
			अवरोध;
		हाल MTK_PPE_PKT_TYPE_IPV6_ROUTE_3T:
		हाल MTK_PPE_PKT_TYPE_IPV6_ROUTE_5T:
			hv1 = e->ipv6.src_ip[3] ^ e->ipv6.dest_ip[3];
			hv1 ^= e->ipv6.ports;

			hv2 = e->ipv6.src_ip[2] ^ e->ipv6.dest_ip[2];
			hv2 ^= e->ipv6.dest_ip[0];

			hv3 = e->ipv6.src_ip[1] ^ e->ipv6.dest_ip[1];
			hv3 ^= e->ipv6.src_ip[0];
			अवरोध;
		हाल MTK_PPE_PKT_TYPE_IPV4_DSLITE:
		हाल MTK_PPE_PKT_TYPE_IPV6_6RD:
		शेष:
			WARN_ON_ONCE(1);
			वापस MTK_PPE_HASH_MASK;
	पूर्ण

	hash = (hv1 & hv2) | ((~hv1) & hv3);
	hash = (hash >> 24) | ((hash & 0xffffff) << 8);
	hash ^= hv1 ^ hv2 ^ hv3;
	hash ^= hash >> 16;
	hash <<= 1;
	hash &= MTK_PPE_ENTRIES - 1;

	वापस hash;
पूर्ण

अटल अंतरभूत काष्ठा mtk_foe_mac_info *
mtk_foe_entry_l2(काष्ठा mtk_foe_entry *entry)
अणु
	पूर्णांक type = FIELD_GET(MTK_FOE_IB1_PACKET_TYPE, entry->ib1);

	अगर (type >= MTK_PPE_PKT_TYPE_IPV4_DSLITE)
		वापस &entry->ipv6.l2;

	वापस &entry->ipv4.l2;
पूर्ण

अटल अंतरभूत u32 *
mtk_foe_entry_ib2(काष्ठा mtk_foe_entry *entry)
अणु
	पूर्णांक type = FIELD_GET(MTK_FOE_IB1_PACKET_TYPE, entry->ib1);

	अगर (type >= MTK_PPE_PKT_TYPE_IPV4_DSLITE)
		वापस &entry->ipv6.ib2;

	वापस &entry->ipv4.ib2;
पूर्ण

पूर्णांक mtk_foe_entry_prepare(काष्ठा mtk_foe_entry *entry, पूर्णांक type, पूर्णांक l4proto,
			  u8 pse_port, u8 *src_mac, u8 *dest_mac)
अणु
	काष्ठा mtk_foe_mac_info *l2;
	u32 ports_pad, val;

	स_रखो(entry, 0, माप(*entry));

	val = FIELD_PREP(MTK_FOE_IB1_STATE, MTK_FOE_STATE_BIND) |
	      FIELD_PREP(MTK_FOE_IB1_PACKET_TYPE, type) |
	      FIELD_PREP(MTK_FOE_IB1_UDP, l4proto == IPPROTO_UDP) |
	      MTK_FOE_IB1_BIND_TTL |
	      MTK_FOE_IB1_BIND_CACHE;
	entry->ib1 = val;

	val = FIELD_PREP(MTK_FOE_IB2_PORT_MG, 0x3f) |
	      FIELD_PREP(MTK_FOE_IB2_PORT_AG, 0x1f) |
	      FIELD_PREP(MTK_FOE_IB2_DEST_PORT, pse_port);

	अगर (is_multicast_ether_addr(dest_mac))
		val |= MTK_FOE_IB2_MULTICAST;

	ports_pad = 0xa5a5a500 | (l4proto & 0xff);
	अगर (type == MTK_PPE_PKT_TYPE_IPV4_ROUTE)
		entry->ipv4.orig.ports = ports_pad;
	अगर (type == MTK_PPE_PKT_TYPE_IPV6_ROUTE_3T)
		entry->ipv6.ports = ports_pad;

	अगर (type >= MTK_PPE_PKT_TYPE_IPV4_DSLITE) अणु
		entry->ipv6.ib2 = val;
		l2 = &entry->ipv6.l2;
	पूर्ण अन्यथा अणु
		entry->ipv4.ib2 = val;
		l2 = &entry->ipv4.l2;
	पूर्ण

	l2->dest_mac_hi = get_unaligned_be32(dest_mac);
	l2->dest_mac_lo = get_unaligned_be16(dest_mac + 4);
	l2->src_mac_hi = get_unaligned_be32(src_mac);
	l2->src_mac_lo = get_unaligned_be16(src_mac + 4);

	अगर (type >= MTK_PPE_PKT_TYPE_IPV6_ROUTE_3T)
		l2->etype = ETH_P_IPV6;
	अन्यथा
		l2->etype = ETH_P_IP;

	वापस 0;
पूर्ण

पूर्णांक mtk_foe_entry_set_pse_port(काष्ठा mtk_foe_entry *entry, u8 port)
अणु
	u32 *ib2 = mtk_foe_entry_ib2(entry);
	u32 val;

	val = *ib2;
	val &= ~MTK_FOE_IB2_DEST_PORT;
	val |= FIELD_PREP(MTK_FOE_IB2_DEST_PORT, port);
	*ib2 = val;

	वापस 0;
पूर्ण

पूर्णांक mtk_foe_entry_set_ipv4_tuple(काष्ठा mtk_foe_entry *entry, bool egress,
				 __be32 src_addr, __be16 src_port,
				 __be32 dest_addr, __be16 dest_port)
अणु
	पूर्णांक type = FIELD_GET(MTK_FOE_IB1_PACKET_TYPE, entry->ib1);
	काष्ठा mtk_ipv4_tuple *t;

	चयन (type) अणु
	हाल MTK_PPE_PKT_TYPE_IPV4_HNAPT:
		अगर (egress) अणु
			t = &entry->ipv4.new;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल MTK_PPE_PKT_TYPE_IPV4_DSLITE:
	हाल MTK_PPE_PKT_TYPE_IPV4_ROUTE:
		t = &entry->ipv4.orig;
		अवरोध;
	हाल MTK_PPE_PKT_TYPE_IPV6_6RD:
		entry->ipv6_6rd.tunnel_src_ip = be32_to_cpu(src_addr);
		entry->ipv6_6rd.tunnel_dest_ip = be32_to_cpu(dest_addr);
		वापस 0;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	t->src_ip = be32_to_cpu(src_addr);
	t->dest_ip = be32_to_cpu(dest_addr);

	अगर (type == MTK_PPE_PKT_TYPE_IPV4_ROUTE)
		वापस 0;

	t->src_port = be16_to_cpu(src_port);
	t->dest_port = be16_to_cpu(dest_port);

	वापस 0;
पूर्ण

पूर्णांक mtk_foe_entry_set_ipv6_tuple(काष्ठा mtk_foe_entry *entry,
				 __be32 *src_addr, __be16 src_port,
				 __be32 *dest_addr, __be16 dest_port)
अणु
	पूर्णांक type = FIELD_GET(MTK_FOE_IB1_PACKET_TYPE, entry->ib1);
	u32 *src, *dest;
	पूर्णांक i;

	चयन (type) अणु
	हाल MTK_PPE_PKT_TYPE_IPV4_DSLITE:
		src = entry->dslite.tunnel_src_ip;
		dest = entry->dslite.tunnel_dest_ip;
		अवरोध;
	हाल MTK_PPE_PKT_TYPE_IPV6_ROUTE_5T:
	हाल MTK_PPE_PKT_TYPE_IPV6_6RD:
		entry->ipv6.src_port = be16_to_cpu(src_port);
		entry->ipv6.dest_port = be16_to_cpu(dest_port);
		fallthrough;
	हाल MTK_PPE_PKT_TYPE_IPV6_ROUTE_3T:
		src = entry->ipv6.src_ip;
		dest = entry->ipv6.dest_ip;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 4; i++)
		src[i] = be32_to_cpu(src_addr[i]);
	क्रम (i = 0; i < 4; i++)
		dest[i] = be32_to_cpu(dest_addr[i]);

	वापस 0;
पूर्ण

पूर्णांक mtk_foe_entry_set_dsa(काष्ठा mtk_foe_entry *entry, पूर्णांक port)
अणु
	काष्ठा mtk_foe_mac_info *l2 = mtk_foe_entry_l2(entry);

	l2->etype = BIT(port);

	अगर (!(entry->ib1 & MTK_FOE_IB1_BIND_VLAN_LAYER))
		entry->ib1 |= FIELD_PREP(MTK_FOE_IB1_BIND_VLAN_LAYER, 1);
	अन्यथा
		l2->etype |= BIT(8);

	entry->ib1 &= ~MTK_FOE_IB1_BIND_VLAN_TAG;

	वापस 0;
पूर्ण

पूर्णांक mtk_foe_entry_set_vlan(काष्ठा mtk_foe_entry *entry, पूर्णांक vid)
अणु
	काष्ठा mtk_foe_mac_info *l2 = mtk_foe_entry_l2(entry);

	चयन (FIELD_GET(MTK_FOE_IB1_BIND_VLAN_LAYER, entry->ib1)) अणु
	हाल 0:
		entry->ib1 |= MTK_FOE_IB1_BIND_VLAN_TAG |
			      FIELD_PREP(MTK_FOE_IB1_BIND_VLAN_LAYER, 1);
		l2->vlan1 = vid;
		वापस 0;
	हाल 1:
		अगर (!(entry->ib1 & MTK_FOE_IB1_BIND_VLAN_TAG)) अणु
			l2->vlan1 = vid;
			l2->etype |= BIT(8);
		पूर्ण अन्यथा अणु
			l2->vlan2 = vid;
			entry->ib1 += FIELD_PREP(MTK_FOE_IB1_BIND_VLAN_LAYER, 1);
		पूर्ण
		वापस 0;
	शेष:
		वापस -ENOSPC;
	पूर्ण
पूर्ण

पूर्णांक mtk_foe_entry_set_pppoe(काष्ठा mtk_foe_entry *entry, पूर्णांक sid)
अणु
	काष्ठा mtk_foe_mac_info *l2 = mtk_foe_entry_l2(entry);

	अगर (!(entry->ib1 & MTK_FOE_IB1_BIND_VLAN_LAYER) ||
	    (entry->ib1 & MTK_FOE_IB1_BIND_VLAN_TAG))
		l2->etype = ETH_P_PPP_SES;

	entry->ib1 |= MTK_FOE_IB1_BIND_PPPOE;
	l2->pppoe_id = sid;

	वापस 0;
पूर्ण

अटल अंतरभूत bool mtk_foe_entry_usable(काष्ठा mtk_foe_entry *entry)
अणु
	वापस !(entry->ib1 & MTK_FOE_IB1_STATIC) &&
	       FIELD_GET(MTK_FOE_IB1_STATE, entry->ib1) != MTK_FOE_STATE_BIND;
पूर्ण

पूर्णांक mtk_foe_entry_commit(काष्ठा mtk_ppe *ppe, काष्ठा mtk_foe_entry *entry,
			 u16 बारtamp)
अणु
	काष्ठा mtk_foe_entry *hwe;
	u32 hash;

	बारtamp &= MTK_FOE_IB1_BIND_TIMESTAMP;
	entry->ib1 &= ~MTK_FOE_IB1_BIND_TIMESTAMP;
	entry->ib1 |= FIELD_PREP(MTK_FOE_IB1_BIND_TIMESTAMP, बारtamp);

	hash = mtk_ppe_hash_entry(entry);
	hwe = &ppe->foe_table[hash];
	अगर (!mtk_foe_entry_usable(hwe)) अणु
		hwe++;
		hash++;

		अगर (!mtk_foe_entry_usable(hwe))
			वापस -ENOSPC;
	पूर्ण

	स_नकल(&hwe->data, &entry->data, माप(hwe->data));
	wmb();
	hwe->ib1 = entry->ib1;

	dma_wmb();

	mtk_ppe_cache_clear(ppe);

	वापस hash;
पूर्ण

पूर्णांक mtk_ppe_init(काष्ठा mtk_ppe *ppe, काष्ठा device *dev, व्योम __iomem *base,
		 पूर्णांक version)
अणु
	काष्ठा mtk_foe_entry *foe;

	/* need to allocate a separate device, since it PPE DMA access is
	 * not coherent.
	 */
	ppe->base = base;
	ppe->dev = dev;
	ppe->version = version;

	foe = dmam_alloc_coherent(ppe->dev, MTK_PPE_ENTRIES * माप(*foe),
				  &ppe->foe_phys, GFP_KERNEL);
	अगर (!foe)
		वापस -ENOMEM;

	ppe->foe_table = foe;

	mtk_ppe_debugfs_init(ppe);

	वापस 0;
पूर्ण

अटल व्योम mtk_ppe_init_foe_table(काष्ठा mtk_ppe *ppe)
अणु
	अटल स्थिर u8 skip[] = अणु 12, 25, 38, 51, 76, 89, 102 पूर्ण;
	पूर्णांक i, k;

	स_रखो(ppe->foe_table, 0, MTK_PPE_ENTRIES * माप(ppe->foe_table));

	अगर (!IS_ENABLED(CONFIG_SOC_MT7621))
		वापस;

	/* skip all entries that cross the 1024 byte boundary */
	क्रम (i = 0; i < MTK_PPE_ENTRIES; i += 128)
		क्रम (k = 0; k < ARRAY_SIZE(skip); k++)
			ppe->foe_table[i + skip[k]].ib1 |= MTK_FOE_IB1_STATIC;
पूर्ण

पूर्णांक mtk_ppe_start(काष्ठा mtk_ppe *ppe)
अणु
	u32 val;

	mtk_ppe_init_foe_table(ppe);
	ppe_w32(ppe, MTK_PPE_TB_BASE, ppe->foe_phys);

	val = MTK_PPE_TB_CFG_ENTRY_80B |
	      MTK_PPE_TB_CFG_AGE_NON_L4 |
	      MTK_PPE_TB_CFG_AGE_UNBIND |
	      MTK_PPE_TB_CFG_AGE_TCP |
	      MTK_PPE_TB_CFG_AGE_UDP |
	      MTK_PPE_TB_CFG_AGE_TCP_FIN |
	      FIELD_PREP(MTK_PPE_TB_CFG_SEARCH_MISS,
			 MTK_PPE_SEARCH_MISS_ACTION_FORWARD_BUILD) |
	      FIELD_PREP(MTK_PPE_TB_CFG_KEEPALIVE,
			 MTK_PPE_KEEPALIVE_DISABLE) |
	      FIELD_PREP(MTK_PPE_TB_CFG_HASH_MODE, 1) |
	      FIELD_PREP(MTK_PPE_TB_CFG_SCAN_MODE,
			 MTK_PPE_SCAN_MODE_KEEPALIVE_AGE) |
	      FIELD_PREP(MTK_PPE_TB_CFG_ENTRY_NUM,
			 MTK_PPE_ENTRIES_SHIFT);
	ppe_w32(ppe, MTK_PPE_TB_CFG, val);

	ppe_w32(ppe, MTK_PPE_IP_PROTO_CHK,
		MTK_PPE_IP_PROTO_CHK_IPV4 | MTK_PPE_IP_PROTO_CHK_IPV6);

	mtk_ppe_cache_enable(ppe, true);

	val = MTK_PPE_FLOW_CFG_IP4_TCP_FRAG |
	      MTK_PPE_FLOW_CFG_IP4_UDP_FRAG |
	      MTK_PPE_FLOW_CFG_IP6_3T_ROUTE |
	      MTK_PPE_FLOW_CFG_IP6_5T_ROUTE |
	      MTK_PPE_FLOW_CFG_IP6_6RD |
	      MTK_PPE_FLOW_CFG_IP4_NAT |
	      MTK_PPE_FLOW_CFG_IP4_NAPT |
	      MTK_PPE_FLOW_CFG_IP4_DSLITE |
	      MTK_PPE_FLOW_CFG_L2_BRIDGE |
	      MTK_PPE_FLOW_CFG_IP4_NAT_FRAG;
	ppe_w32(ppe, MTK_PPE_FLOW_CFG, val);

	val = FIELD_PREP(MTK_PPE_UNBIND_AGE_MIN_PACKETS, 1000) |
	      FIELD_PREP(MTK_PPE_UNBIND_AGE_DELTA, 3);
	ppe_w32(ppe, MTK_PPE_UNBIND_AGE, val);

	val = FIELD_PREP(MTK_PPE_BIND_AGE0_DELTA_UDP, 12) |
	      FIELD_PREP(MTK_PPE_BIND_AGE0_DELTA_NON_L4, 1);
	ppe_w32(ppe, MTK_PPE_BIND_AGE0, val);

	val = FIELD_PREP(MTK_PPE_BIND_AGE1_DELTA_TCP_FIN, 1) |
	      FIELD_PREP(MTK_PPE_BIND_AGE1_DELTA_TCP, 7);
	ppe_w32(ppe, MTK_PPE_BIND_AGE1, val);

	val = MTK_PPE_BIND_LIMIT0_QUARTER | MTK_PPE_BIND_LIMIT0_HALF;
	ppe_w32(ppe, MTK_PPE_BIND_LIMIT0, val);

	val = MTK_PPE_BIND_LIMIT1_FULL |
	      FIELD_PREP(MTK_PPE_BIND_LIMIT1_NON_L4, 1);
	ppe_w32(ppe, MTK_PPE_BIND_LIMIT1, val);

	val = FIELD_PREP(MTK_PPE_BIND_RATE_BIND, 30) |
	      FIELD_PREP(MTK_PPE_BIND_RATE_PREBIND, 1);
	ppe_w32(ppe, MTK_PPE_BIND_RATE, val);

	/* enable PPE */
	val = MTK_PPE_GLO_CFG_EN |
	      MTK_PPE_GLO_CFG_IP4_L4_CS_DROP |
	      MTK_PPE_GLO_CFG_IP4_CS_DROP |
	      MTK_PPE_GLO_CFG_FLOW_DROP_UPDATE;
	ppe_w32(ppe, MTK_PPE_GLO_CFG, val);

	ppe_w32(ppe, MTK_PPE_DEFAULT_CPU_PORT, 0);

	वापस 0;
पूर्ण

पूर्णांक mtk_ppe_stop(काष्ठा mtk_ppe *ppe)
अणु
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < MTK_PPE_ENTRIES; i++)
		ppe->foe_table[i].ib1 = FIELD_PREP(MTK_FOE_IB1_STATE,
						   MTK_FOE_STATE_INVALID);

	mtk_ppe_cache_enable(ppe, false);

	/* disable offload engine */
	ppe_clear(ppe, MTK_PPE_GLO_CFG, MTK_PPE_GLO_CFG_EN);
	ppe_w32(ppe, MTK_PPE_FLOW_CFG, 0);

	/* disable aging */
	val = MTK_PPE_TB_CFG_AGE_NON_L4 |
	      MTK_PPE_TB_CFG_AGE_UNBIND |
	      MTK_PPE_TB_CFG_AGE_TCP |
	      MTK_PPE_TB_CFG_AGE_UDP |
	      MTK_PPE_TB_CFG_AGE_TCP_FIN;
	ppe_clear(ppe, MTK_PPE_TB_CFG, val);

	वापस mtk_ppe_रुको_busy(ppe);
पूर्ण
