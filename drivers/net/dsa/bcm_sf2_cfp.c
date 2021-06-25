<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom Starfighter 2 DSA चयन CFP support
 *
 * Copyright (C) 2016, Broadcom
 */

#समावेश <linux/list.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/in.h>
#समावेश <linux/netdevice.h>
#समावेश <net/dsa.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <net/flow_offload.h>
#समावेश <net/चयनdev.h>
#समावेश <uapi/linux/अगर_bridge.h>

#समावेश "bcm_sf2.h"
#समावेश "bcm_sf2_regs.h"

काष्ठा cfp_rule अणु
	पूर्णांक port;
	काष्ठा ethtool_rx_flow_spec fs;
	काष्ठा list_head next;
पूर्ण;

काष्ठा cfp_udf_slice_layout अणु
	u8 slices[UDFS_PER_SLICE];
	u32 mask_value;
	u32 base_offset;
पूर्ण;

काष्ठा cfp_udf_layout अणु
	काष्ठा cfp_udf_slice_layout udfs[UDF_NUM_SLICES];
पूर्ण;

अटल स्थिर u8 zero_slice[UDFS_PER_SLICE] = अणु पूर्ण;

/* UDF slices layout क्रम a TCPv4/UDPv4 specअगरication */
अटल स्थिर काष्ठा cfp_udf_layout udf_tcpip4_layout = अणु
	.udfs = अणु
		[1] = अणु
			.slices = अणु
				/* End of L2, byte offset 12, src IP[0:15] */
				CFG_UDF_EOL2 | 6,
				/* End of L2, byte offset 14, src IP[16:31] */
				CFG_UDF_EOL2 | 7,
				/* End of L2, byte offset 16, dst IP[0:15] */
				CFG_UDF_EOL2 | 8,
				/* End of L2, byte offset 18, dst IP[16:31] */
				CFG_UDF_EOL2 | 9,
				/* End of L3, byte offset 0, src port */
				CFG_UDF_EOL3 | 0,
				/* End of L3, byte offset 2, dst port */
				CFG_UDF_EOL3 | 1,
				0, 0, 0
			पूर्ण,
			.mask_value = L3_FRAMING_MASK | IPPROTO_MASK | IP_FRAG,
			.base_offset = CORE_UDF_0_A_0_8_PORT_0 + UDF_SLICE_OFFSET,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* UDF slices layout क्रम a TCPv6/UDPv6 specअगरication */
अटल स्थिर काष्ठा cfp_udf_layout udf_tcpip6_layout = अणु
	.udfs = अणु
		[0] = अणु
			.slices = अणु
				/* End of L2, byte offset 8, src IP[0:15] */
				CFG_UDF_EOL2 | 4,
				/* End of L2, byte offset 10, src IP[16:31] */
				CFG_UDF_EOL2 | 5,
				/* End of L2, byte offset 12, src IP[32:47] */
				CFG_UDF_EOL2 | 6,
				/* End of L2, byte offset 14, src IP[48:63] */
				CFG_UDF_EOL2 | 7,
				/* End of L2, byte offset 16, src IP[64:79] */
				CFG_UDF_EOL2 | 8,
				/* End of L2, byte offset 18, src IP[80:95] */
				CFG_UDF_EOL2 | 9,
				/* End of L2, byte offset 20, src IP[96:111] */
				CFG_UDF_EOL2 | 10,
				/* End of L2, byte offset 22, src IP[112:127] */
				CFG_UDF_EOL2 | 11,
				/* End of L3, byte offset 0, src port */
				CFG_UDF_EOL3 | 0,
			पूर्ण,
			.mask_value = L3_FRAMING_MASK | IPPROTO_MASK | IP_FRAG,
			.base_offset = CORE_UDF_0_B_0_8_PORT_0,
		पूर्ण,
		[3] = अणु
			.slices = अणु
				/* End of L2, byte offset 24, dst IP[0:15] */
				CFG_UDF_EOL2 | 12,
				/* End of L2, byte offset 26, dst IP[16:31] */
				CFG_UDF_EOL2 | 13,
				/* End of L2, byte offset 28, dst IP[32:47] */
				CFG_UDF_EOL2 | 14,
				/* End of L2, byte offset 30, dst IP[48:63] */
				CFG_UDF_EOL2 | 15,
				/* End of L2, byte offset 32, dst IP[64:79] */
				CFG_UDF_EOL2 | 16,
				/* End of L2, byte offset 34, dst IP[80:95] */
				CFG_UDF_EOL2 | 17,
				/* End of L2, byte offset 36, dst IP[96:111] */
				CFG_UDF_EOL2 | 18,
				/* End of L2, byte offset 38, dst IP[112:127] */
				CFG_UDF_EOL2 | 19,
				/* End of L3, byte offset 2, dst port */
				CFG_UDF_EOL3 | 1,
			पूर्ण,
			.mask_value = L3_FRAMING_MASK | IPPROTO_MASK | IP_FRAG,
			.base_offset = CORE_UDF_0_D_0_11_PORT_0,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक bcm_sf2_get_num_udf_slices(स्थिर u8 *layout)
अणु
	अचिन्हित पूर्णांक i, count = 0;

	क्रम (i = 0; i < UDFS_PER_SLICE; i++) अणु
		अगर (layout[i] != 0)
			count++;
	पूर्ण

	वापस count;
पूर्ण

अटल अंतरभूत u32 udf_upper_bits(पूर्णांक num_udf)
अणु
	वापस GENMASK(num_udf - 1, 0) >> (UDFS_PER_SLICE - 1);
पूर्ण

अटल अंतरभूत u32 udf_lower_bits(पूर्णांक num_udf)
अणु
	वापस (u8)GENMASK(num_udf - 1, 0);
पूर्ण

अटल अचिन्हित पूर्णांक bcm_sf2_get_slice_number(स्थिर काष्ठा cfp_udf_layout *l,
					     अचिन्हित पूर्णांक start)
अणु
	स्थिर काष्ठा cfp_udf_slice_layout *slice_layout;
	अचिन्हित पूर्णांक slice_idx;

	क्रम (slice_idx = start; slice_idx < UDF_NUM_SLICES; slice_idx++) अणु
		slice_layout = &l->udfs[slice_idx];
		अगर (स_भेद(slice_layout->slices, zero_slice,
			   माप(zero_slice)))
			अवरोध;
	पूर्ण

	वापस slice_idx;
पूर्ण

अटल व्योम bcm_sf2_cfp_udf_set(काष्ठा bcm_sf2_priv *priv,
				स्थिर काष्ठा cfp_udf_layout *layout,
				अचिन्हित पूर्णांक slice_num)
अणु
	u32 offset = layout->udfs[slice_num].base_offset;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < UDFS_PER_SLICE; i++)
		core_ग_लिखोl(priv, layout->udfs[slice_num].slices[i],
			    offset + i * 4);
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_op(काष्ठा bcm_sf2_priv *priv, अचिन्हित पूर्णांक op)
अणु
	अचिन्हित पूर्णांक समयout = 1000;
	u32 reg;

	reg = core_पढ़ोl(priv, CORE_CFP_ACC);
	reg &= ~(OP_SEL_MASK | RAM_SEL_MASK);
	reg |= OP_STR_DONE | op;
	core_ग_लिखोl(priv, reg, CORE_CFP_ACC);

	करो अणु
		reg = core_पढ़ोl(priv, CORE_CFP_ACC);
		अगर (!(reg & OP_STR_DONE))
			अवरोध;

		cpu_relax();
	पूर्ण जबतक (समयout--);

	अगर (!समयout)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bcm_sf2_cfp_rule_addr_set(काष्ठा bcm_sf2_priv *priv,
					     अचिन्हित पूर्णांक addr)
अणु
	u32 reg;

	WARN_ON(addr >= priv->num_cfp_rules);

	reg = core_पढ़ोl(priv, CORE_CFP_ACC);
	reg &= ~(XCESS_ADDR_MASK << XCESS_ADDR_SHIFT);
	reg |= addr << XCESS_ADDR_SHIFT;
	core_ग_लिखोl(priv, reg, CORE_CFP_ACC);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bcm_sf2_cfp_rule_size(काष्ठा bcm_sf2_priv *priv)
अणु
	/* Entry #0 is reserved */
	वापस priv->num_cfp_rules - 1;
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_act_pol_set(काष्ठा bcm_sf2_priv *priv,
				   अचिन्हित पूर्णांक rule_index,
				   पूर्णांक src_port,
				   अचिन्हित पूर्णांक port_num,
				   अचिन्हित पूर्णांक queue_num,
				   bool fwd_map_change)
अणु
	पूर्णांक ret;
	u32 reg;

	/* Replace ARL derived destination with DST_MAP derived, define
	 * which port and queue this should be क्रमwarded to.
	 */
	अगर (fwd_map_change)
		reg = CHANGE_FWRD_MAP_IB_REP_ARL |
		      BIT(port_num + DST_MAP_IB_SHIFT) |
		      CHANGE_TC | queue_num << NEW_TC_SHIFT;
	अन्यथा
		reg = 0;

	/* Enable looping back to the original port */
	अगर (src_port == port_num)
		reg |= LOOP_BK_EN;

	core_ग_लिखोl(priv, reg, CORE_ACT_POL_DATA0);

	/* Set classअगरication ID that needs to be put in Broadcom tag */
	core_ग_लिखोl(priv, rule_index << CHAIN_ID_SHIFT, CORE_ACT_POL_DATA1);

	core_ग_लिखोl(priv, 0, CORE_ACT_POL_DATA2);

	/* Configure policer RAM now */
	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | ACT_POL_RAM);
	अगर (ret) अणु
		pr_err("Policer entry at %d failed\n", rule_index);
		वापस ret;
	पूर्ण

	/* Disable the policer */
	core_ग_लिखोl(priv, POLICER_MODE_DISABLE, CORE_RATE_METER0);

	/* Now the rate meter */
	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | RATE_METER_RAM);
	अगर (ret) अणु
		pr_err("Meter entry at %d failed\n", rule_index);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bcm_sf2_cfp_slice_ipv4(काष्ठा bcm_sf2_priv *priv,
				   काष्ठा flow_dissector_key_ipv4_addrs *addrs,
				   काष्ठा flow_dissector_key_ports *ports,
				   स्थिर __be16 vlan_tci,
				   अचिन्हित पूर्णांक slice_num, u8 num_udf,
				   bool mask)
अणु
	u32 reg, offset;

	/* UDF_Valid[7:0]	[31:24]
	 * S-Tag		[23:8]
	 * C-Tag		[7:0]
	 */
	reg = udf_lower_bits(num_udf) << 24 | be16_to_cpu(vlan_tci) >> 8;
	अगर (mask)
		core_ग_लिखोl(priv, reg, CORE_CFP_MASK_PORT(5));
	अन्यथा
		core_ग_लिखोl(priv, reg, CORE_CFP_DATA_PORT(5));

	/* C-Tag		[31:24]
	 * UDF_n_A8		[23:8]
	 * UDF_n_A7		[7:0]
	 */
	reg = (u32)(be16_to_cpu(vlan_tci) & 0xff) << 24;
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(4);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(4);
	core_ग_लिखोl(priv, reg, offset);

	/* UDF_n_A7		[31:24]
	 * UDF_n_A6		[23:8]
	 * UDF_n_A5		[7:0]
	 */
	reg = be16_to_cpu(ports->dst) >> 8;
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(3);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(3);
	core_ग_लिखोl(priv, reg, offset);

	/* UDF_n_A5		[31:24]
	 * UDF_n_A4		[23:8]
	 * UDF_n_A3		[7:0]
	 */
	reg = (be16_to_cpu(ports->dst) & 0xff) << 24 |
	      (u32)be16_to_cpu(ports->src) << 8 |
	      (be32_to_cpu(addrs->dst) & 0x0000ff00) >> 8;
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(2);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(2);
	core_ग_लिखोl(priv, reg, offset);

	/* UDF_n_A3		[31:24]
	 * UDF_n_A2		[23:8]
	 * UDF_n_A1		[7:0]
	 */
	reg = (u32)(be32_to_cpu(addrs->dst) & 0xff) << 24 |
	      (u32)(be32_to_cpu(addrs->dst) >> 16) << 8 |
	      (be32_to_cpu(addrs->src) & 0x0000ff00) >> 8;
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(1);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(1);
	core_ग_लिखोl(priv, reg, offset);

	/* UDF_n_A1		[31:24]
	 * UDF_n_A0		[23:8]
	 * Reserved		[7:4]
	 * Slice ID		[3:2]
	 * Slice valid		[1:0]
	 */
	reg = (u32)(be32_to_cpu(addrs->src) & 0xff) << 24 |
	      (u32)(be32_to_cpu(addrs->src) >> 16) << 8 |
	      SLICE_NUM(slice_num) | SLICE_VALID;
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(0);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(0);
	core_ग_लिखोl(priv, reg, offset);
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_ipv4_rule_set(काष्ठा bcm_sf2_priv *priv, पूर्णांक port,
				     अचिन्हित पूर्णांक port_num,
				     अचिन्हित पूर्णांक queue_num,
				     काष्ठा ethtool_rx_flow_spec *fs)
अणु
	__be16 vlan_tci = 0, vlan_m_tci = htons(0xffff);
	काष्ठा ethtool_rx_flow_spec_input input = अणुपूर्ण;
	स्थिर काष्ठा cfp_udf_layout *layout;
	अचिन्हित पूर्णांक slice_num, rule_index;
	काष्ठा ethtool_rx_flow_rule *flow;
	काष्ठा flow_match_ipv4_addrs ipv4;
	काष्ठा flow_match_ports ports;
	काष्ठा flow_match_ip ip;
	u8 ip_proto, ip_frag;
	u8 num_udf;
	u32 reg;
	पूर्णांक ret;

	चयन (fs->flow_type & ~FLOW_EXT) अणु
	हाल TCP_V4_FLOW:
		ip_proto = IPPROTO_TCP;
		अवरोध;
	हाल UDP_V4_FLOW:
		ip_proto = IPPROTO_UDP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ip_frag = !!(be32_to_cpu(fs->h_ext.data[0]) & 1);

	/* Extract VLAN TCI */
	अगर (fs->flow_type & FLOW_EXT) अणु
		vlan_tci = fs->h_ext.vlan_tci;
		vlan_m_tci = fs->m_ext.vlan_tci;
	पूर्ण

	/* Locate the first rule available */
	अगर (fs->location == RX_CLS_LOC_ANY)
		rule_index = find_first_zero_bit(priv->cfp.used,
						 priv->num_cfp_rules);
	अन्यथा
		rule_index = fs->location;

	अगर (rule_index > bcm_sf2_cfp_rule_size(priv))
		वापस -ENOSPC;

	input.fs = fs;
	flow = ethtool_rx_flow_rule_create(&input);
	अगर (IS_ERR(flow))
		वापस PTR_ERR(flow);

	flow_rule_match_ipv4_addrs(flow->rule, &ipv4);
	flow_rule_match_ports(flow->rule, &ports);
	flow_rule_match_ip(flow->rule, &ip);

	layout = &udf_tcpip4_layout;
	/* We only use one UDF slice क्रम now */
	slice_num = bcm_sf2_get_slice_number(layout, 0);
	अगर (slice_num == UDF_NUM_SLICES) अणु
		ret = -EINVAL;
		जाओ out_err_flow_rule;
	पूर्ण

	num_udf = bcm_sf2_get_num_udf_slices(layout->udfs[slice_num].slices);

	/* Apply the UDF layout क्रम this filter */
	bcm_sf2_cfp_udf_set(priv, layout, slice_num);

	/* Apply to all packets received through this port */
	core_ग_लिखोl(priv, BIT(port), CORE_CFP_DATA_PORT(7));

	/* Source port map match */
	core_ग_लिखोl(priv, 0xff, CORE_CFP_MASK_PORT(7));

	/* S-Tag status		[31:30]
	 * C-Tag status		[29:28]
	 * L2 framing		[27:26]
	 * L3 framing		[25:24]
	 * IP ToS		[23:16]
	 * IP proto		[15:08]
	 * IP Fragm		[7]
	 * Non 1st frag		[6]
	 * IP Authen		[5]
	 * TTL range		[4:3]
	 * PPPoE session	[2]
	 * Reserved		[1]
	 * UDF_Valid[8]		[0]
	 */
	core_ग_लिखोl(priv, ip.key->tos << IPTOS_SHIFT |
		    ip_proto << IPPROTO_SHIFT | ip_frag << IP_FRAG_SHIFT |
		    udf_upper_bits(num_udf),
		    CORE_CFP_DATA_PORT(6));

	/* Mask with the specअगरic layout क्रम IPv4 packets */
	core_ग_लिखोl(priv, layout->udfs[slice_num].mask_value |
		    udf_upper_bits(num_udf), CORE_CFP_MASK_PORT(6));

	/* Program the match and the mask */
	bcm_sf2_cfp_slice_ipv4(priv, ipv4.key, ports.key, vlan_tci,
			       slice_num, num_udf, false);
	bcm_sf2_cfp_slice_ipv4(priv, ipv4.mask, ports.mask, vlan_m_tci,
			       SLICE_NUM_MASK, num_udf, true);

	/* Insert पूर्णांकo TCAM now */
	bcm_sf2_cfp_rule_addr_set(priv, rule_index);

	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | TCAM_SEL);
	अगर (ret) अणु
		pr_err("TCAM entry at addr %d failed\n", rule_index);
		जाओ out_err_flow_rule;
	पूर्ण

	/* Insert पूर्णांकo Action and policer RAMs now */
	ret = bcm_sf2_cfp_act_pol_set(priv, rule_index, port, port_num,
				      queue_num, true);
	अगर (ret)
		जाओ out_err_flow_rule;

	/* Turn on CFP क्रम this rule now */
	reg = core_पढ़ोl(priv, CORE_CFP_CTL_REG);
	reg |= BIT(port);
	core_ग_लिखोl(priv, reg, CORE_CFP_CTL_REG);

	/* Flag the rule as being used and वापस it */
	set_bit(rule_index, priv->cfp.used);
	set_bit(rule_index, priv->cfp.unique);
	fs->location = rule_index;

	वापस 0;

out_err_flow_rule:
	ethtool_rx_flow_rule_destroy(flow);
	वापस ret;
पूर्ण

अटल व्योम bcm_sf2_cfp_slice_ipv6(काष्ठा bcm_sf2_priv *priv,
				   स्थिर __be32 *ip6_addr, स्थिर __be16 port,
				   स्थिर __be16 vlan_tci,
				   अचिन्हित पूर्णांक slice_num, u32 udf_bits,
				   bool mask)
अणु
	u32 reg, पंचांगp, val, offset;

	/* UDF_Valid[7:0]	[31:24]
	 * S-Tag		[23:8]
	 * C-Tag		[7:0]
	 */
	reg = udf_bits << 24 | be16_to_cpu(vlan_tci) >> 8;
	अगर (mask)
		core_ग_लिखोl(priv, reg, CORE_CFP_MASK_PORT(5));
	अन्यथा
		core_ग_लिखोl(priv, reg, CORE_CFP_DATA_PORT(5));

	/* C-Tag		[31:24]
	 * UDF_n_B8		[23:8]	(port)
	 * UDF_n_B7 (upper)	[7:0]	(addr[15:8])
	 */
	reg = be32_to_cpu(ip6_addr[3]);
	val = (u32)be16_to_cpu(port) << 8 | ((reg >> 8) & 0xff);
	val |= (u32)(be16_to_cpu(vlan_tci) & 0xff) << 24;
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(4);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(4);
	core_ग_लिखोl(priv, val, offset);

	/* UDF_n_B7 (lower)	[31:24]	(addr[7:0])
	 * UDF_n_B6		[23:8] (addr[31:16])
	 * UDF_n_B5 (upper)	[7:0] (addr[47:40])
	 */
	पंचांगp = be32_to_cpu(ip6_addr[2]);
	val = (u32)(reg & 0xff) << 24 | (u32)(reg >> 16) << 8 |
	      ((पंचांगp >> 8) & 0xff);
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(3);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(3);
	core_ग_लिखोl(priv, val, offset);

	/* UDF_n_B5 (lower)	[31:24] (addr[39:32])
	 * UDF_n_B4		[23:8] (addr[63:48])
	 * UDF_n_B3 (upper)	[7:0] (addr[79:72])
	 */
	reg = be32_to_cpu(ip6_addr[1]);
	val = (u32)(पंचांगp & 0xff) << 24 | (u32)(पंचांगp >> 16) << 8 |
	      ((reg >> 8) & 0xff);
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(2);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(2);
	core_ग_लिखोl(priv, val, offset);

	/* UDF_n_B3 (lower)	[31:24] (addr[71:64])
	 * UDF_n_B2		[23:8] (addr[95:80])
	 * UDF_n_B1 (upper)	[7:0] (addr[111:104])
	 */
	पंचांगp = be32_to_cpu(ip6_addr[0]);
	val = (u32)(reg & 0xff) << 24 | (u32)(reg >> 16) << 8 |
	      ((पंचांगp >> 8) & 0xff);
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(1);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(1);
	core_ग_लिखोl(priv, val, offset);

	/* UDF_n_B1 (lower)	[31:24] (addr[103:96])
	 * UDF_n_B0		[23:8] (addr[127:112])
	 * Reserved		[7:4]
	 * Slice ID		[3:2]
	 * Slice valid		[1:0]
	 */
	reg = (u32)(पंचांगp & 0xff) << 24 | (u32)(पंचांगp >> 16) << 8 |
	       SLICE_NUM(slice_num) | SLICE_VALID;
	अगर (mask)
		offset = CORE_CFP_MASK_PORT(0);
	अन्यथा
		offset = CORE_CFP_DATA_PORT(0);
	core_ग_लिखोl(priv, reg, offset);
पूर्ण

अटल काष्ठा cfp_rule *bcm_sf2_cfp_rule_find(काष्ठा bcm_sf2_priv *priv,
					      पूर्णांक port, u32 location)
अणु
	काष्ठा cfp_rule *rule = शून्य;

	list_क्रम_each_entry(rule, &priv->cfp.rules_list, next) अणु
		अगर (rule->port == port && rule->fs.location == location)
			अवरोध;
	पूर्ण

	वापस rule;
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_rule_cmp(काष्ठा bcm_sf2_priv *priv, पूर्णांक port,
				काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा cfp_rule *rule = शून्य;
	माप_प्रकार fs_size = 0;
	पूर्णांक ret = 1;

	अगर (list_empty(&priv->cfp.rules_list))
		वापस ret;

	list_क्रम_each_entry(rule, &priv->cfp.rules_list, next) अणु
		ret = 1;
		अगर (rule->port != port)
			जारी;

		अगर (rule->fs.flow_type != fs->flow_type ||
		    rule->fs.ring_cookie != fs->ring_cookie ||
		    rule->fs.h_ext.data[0] != fs->h_ext.data[0])
			जारी;

		चयन (fs->flow_type & ~FLOW_EXT) अणु
		हाल TCP_V6_FLOW:
		हाल UDP_V6_FLOW:
			fs_size = माप(काष्ठा ethtool_tcpip6_spec);
			अवरोध;
		हाल TCP_V4_FLOW:
		हाल UDP_V4_FLOW:
			fs_size = माप(काष्ठा ethtool_tcpip4_spec);
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		ret = स_भेद(&rule->fs.h_u, &fs->h_u, fs_size);
		ret |= स_भेद(&rule->fs.m_u, &fs->m_u, fs_size);
		/* Compare VLAN TCI values as well */
		अगर (rule->fs.flow_type & FLOW_EXT) अणु
			ret |= rule->fs.h_ext.vlan_tci != fs->h_ext.vlan_tci;
			ret |= rule->fs.m_ext.vlan_tci != fs->m_ext.vlan_tci;
		पूर्ण
		अगर (ret == 0)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_ipv6_rule_set(काष्ठा bcm_sf2_priv *priv, पूर्णांक port,
				     अचिन्हित पूर्णांक port_num,
				     अचिन्हित पूर्णांक queue_num,
				     काष्ठा ethtool_rx_flow_spec *fs)
अणु
	__be16 vlan_tci = 0, vlan_m_tci = htons(0xffff);
	काष्ठा ethtool_rx_flow_spec_input input = अणुपूर्ण;
	अचिन्हित पूर्णांक slice_num, rule_index[2];
	स्थिर काष्ठा cfp_udf_layout *layout;
	काष्ठा ethtool_rx_flow_rule *flow;
	काष्ठा flow_match_ipv6_addrs ipv6;
	काष्ठा flow_match_ports ports;
	u8 ip_proto, ip_frag;
	पूर्णांक ret = 0;
	u8 num_udf;
	u32 reg;

	चयन (fs->flow_type & ~FLOW_EXT) अणु
	हाल TCP_V6_FLOW:
		ip_proto = IPPROTO_TCP;
		अवरोध;
	हाल UDP_V6_FLOW:
		ip_proto = IPPROTO_UDP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ip_frag = !!(be32_to_cpu(fs->h_ext.data[0]) & 1);

	/* Extract VLAN TCI */
	अगर (fs->flow_type & FLOW_EXT) अणु
		vlan_tci = fs->h_ext.vlan_tci;
		vlan_m_tci = fs->m_ext.vlan_tci;
	पूर्ण

	layout = &udf_tcpip6_layout;
	slice_num = bcm_sf2_get_slice_number(layout, 0);
	अगर (slice_num == UDF_NUM_SLICES)
		वापस -EINVAL;

	num_udf = bcm_sf2_get_num_udf_slices(layout->udfs[slice_num].slices);

	/* Negotiate two indexes, one क्रम the second half which we are chained
	 * from, which is what we will वापस to user-space, and a second one
	 * which is used to store its first half. That first half करोes not
	 * allow any choice of placement, so it just needs to find the next
	 * available bit. We वापस the second half as fs->location because
	 * that helps with the rule lookup later on since the second half is
	 * chained from its first half, we can easily identअगरy IPv6 CFP rules
	 * by looking whether they carry a CHAIN_ID.
	 *
	 * We also want the second half to have a lower rule_index than its
	 * first half because the HW search is by incrementing addresses.
	 */
	अगर (fs->location == RX_CLS_LOC_ANY)
		rule_index[1] = find_first_zero_bit(priv->cfp.used,
						    priv->num_cfp_rules);
	अन्यथा
		rule_index[1] = fs->location;
	अगर (rule_index[1] > bcm_sf2_cfp_rule_size(priv))
		वापस -ENOSPC;

	/* Flag it as used (cleared on error path) such that we can immediately
	 * obtain a second one to chain from.
	 */
	set_bit(rule_index[1], priv->cfp.used);

	rule_index[0] = find_first_zero_bit(priv->cfp.used,
					    priv->num_cfp_rules);
	अगर (rule_index[0] > bcm_sf2_cfp_rule_size(priv)) अणु
		ret = -ENOSPC;
		जाओ out_err;
	पूर्ण

	input.fs = fs;
	flow = ethtool_rx_flow_rule_create(&input);
	अगर (IS_ERR(flow)) अणु
		ret = PTR_ERR(flow);
		जाओ out_err;
	पूर्ण
	flow_rule_match_ipv6_addrs(flow->rule, &ipv6);
	flow_rule_match_ports(flow->rule, &ports);

	/* Apply the UDF layout क्रम this filter */
	bcm_sf2_cfp_udf_set(priv, layout, slice_num);

	/* Apply to all packets received through this port */
	core_ग_लिखोl(priv, BIT(port), CORE_CFP_DATA_PORT(7));

	/* Source port map match */
	core_ग_लिखोl(priv, 0xff, CORE_CFP_MASK_PORT(7));

	/* S-Tag status		[31:30]
	 * C-Tag status		[29:28]
	 * L2 framing		[27:26]
	 * L3 framing		[25:24]
	 * IP ToS		[23:16]
	 * IP proto		[15:08]
	 * IP Fragm		[7]
	 * Non 1st frag		[6]
	 * IP Authen		[5]
	 * TTL range		[4:3]
	 * PPPoE session	[2]
	 * Reserved		[1]
	 * UDF_Valid[8]		[0]
	 */
	reg = 1 << L3_FRAMING_SHIFT | ip_proto << IPPROTO_SHIFT |
		ip_frag << IP_FRAG_SHIFT | udf_upper_bits(num_udf);
	core_ग_लिखोl(priv, reg, CORE_CFP_DATA_PORT(6));

	/* Mask with the specअगरic layout क्रम IPv6 packets including
	 * UDF_Valid[8]
	 */
	reg = layout->udfs[slice_num].mask_value | udf_upper_bits(num_udf);
	core_ग_लिखोl(priv, reg, CORE_CFP_MASK_PORT(6));

	/* Slice the IPv6 source address and port */
	bcm_sf2_cfp_slice_ipv6(priv, ipv6.key->src.in6_u.u6_addr32,
			       ports.key->src, vlan_tci, slice_num,
			       udf_lower_bits(num_udf), false);
	bcm_sf2_cfp_slice_ipv6(priv, ipv6.mask->src.in6_u.u6_addr32,
			       ports.mask->src, vlan_m_tci, SLICE_NUM_MASK,
			       udf_lower_bits(num_udf), true);

	/* Insert पूर्णांकo TCAM now because we need to insert a second rule */
	bcm_sf2_cfp_rule_addr_set(priv, rule_index[0]);

	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | TCAM_SEL);
	अगर (ret) अणु
		pr_err("TCAM entry at addr %d failed\n", rule_index[0]);
		जाओ out_err_flow_rule;
	पूर्ण

	/* Insert पूर्णांकo Action and policer RAMs now */
	ret = bcm_sf2_cfp_act_pol_set(priv, rule_index[0], port, port_num,
				      queue_num, false);
	अगर (ret)
		जाओ out_err_flow_rule;

	/* Now deal with the second slice to chain this rule */
	slice_num = bcm_sf2_get_slice_number(layout, slice_num + 1);
	अगर (slice_num == UDF_NUM_SLICES) अणु
		ret = -EINVAL;
		जाओ out_err_flow_rule;
	पूर्ण

	num_udf = bcm_sf2_get_num_udf_slices(layout->udfs[slice_num].slices);

	/* Apply the UDF layout क्रम this filter */
	bcm_sf2_cfp_udf_set(priv, layout, slice_num);

	/* Chained rule, source port match is coming from the rule we are
	 * chained from.
	 */
	core_ग_लिखोl(priv, 0, CORE_CFP_DATA_PORT(7));
	core_ग_लिखोl(priv, 0, CORE_CFP_MASK_PORT(7));

	/*
	 * CHAIN ID		[31:24] chain to previous slice
	 * Reserved		[23:20]
	 * UDF_Valid[11:8]	[19:16]
	 * UDF_Valid[7:0]	[15:8]
	 * UDF_n_D11		[7:0]
	 */
	reg = rule_index[0] << 24 | udf_upper_bits(num_udf) << 16 |
		udf_lower_bits(num_udf) << 8;
	core_ग_लिखोl(priv, reg, CORE_CFP_DATA_PORT(6));

	/* Mask all except chain ID, UDF Valid[8] and UDF Valid[7:0] */
	reg = XCESS_ADDR_MASK << 24 | udf_upper_bits(num_udf) << 16 |
		udf_lower_bits(num_udf) << 8;
	core_ग_लिखोl(priv, reg, CORE_CFP_MASK_PORT(6));

	bcm_sf2_cfp_slice_ipv6(priv, ipv6.key->dst.in6_u.u6_addr32,
			       ports.key->dst, 0, slice_num,
			       0, false);
	bcm_sf2_cfp_slice_ipv6(priv, ipv6.mask->dst.in6_u.u6_addr32,
			       ports.key->dst, 0, SLICE_NUM_MASK,
			       0, true);

	/* Insert पूर्णांकo TCAM now */
	bcm_sf2_cfp_rule_addr_set(priv, rule_index[1]);

	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | TCAM_SEL);
	अगर (ret) अणु
		pr_err("TCAM entry at addr %d failed\n", rule_index[1]);
		जाओ out_err_flow_rule;
	पूर्ण

	/* Insert पूर्णांकo Action and policer RAMs now, set chain ID to
	 * the one we are chained to
	 */
	ret = bcm_sf2_cfp_act_pol_set(priv, rule_index[1], port, port_num,
				      queue_num, true);
	अगर (ret)
		जाओ out_err_flow_rule;

	/* Turn on CFP क्रम this rule now */
	reg = core_पढ़ोl(priv, CORE_CFP_CTL_REG);
	reg |= BIT(port);
	core_ग_लिखोl(priv, reg, CORE_CFP_CTL_REG);

	/* Flag the second half rule as being used now, वापस it as the
	 * location, and flag it as unique जबतक dumping rules
	 */
	set_bit(rule_index[0], priv->cfp.used);
	set_bit(rule_index[1], priv->cfp.unique);
	fs->location = rule_index[1];

	वापस ret;

out_err_flow_rule:
	ethtool_rx_flow_rule_destroy(flow);
out_err:
	clear_bit(rule_index[1], priv->cfp.used);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_rule_insert(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	s8 cpu_port = dsa_to_port(ds, port)->cpu_dp->index;
	__u64 ring_cookie = fs->ring_cookie;
	काष्ठा चयनdev_obj_port_vlan vlan;
	अचिन्हित पूर्णांक queue_num, port_num;
	u16 vid;
	पूर्णांक ret;

	/* This rule is a Wake-on-LAN filter and we must specअगरically
	 * target the CPU port in order क्रम it to be working.
	 */
	अगर (ring_cookie == RX_CLS_FLOW_WAKE)
		ring_cookie = cpu_port * SF2_NUM_EGRESS_QUEUES;

	/* We करो not support discarding packets, check that the
	 * destination port is enabled and that we are within the
	 * number of ports supported by the चयन
	 */
	port_num = ring_cookie / SF2_NUM_EGRESS_QUEUES;

	अगर (ring_cookie == RX_CLS_FLOW_DISC ||
	    !(dsa_is_user_port(ds, port_num) ||
	      dsa_is_cpu_port(ds, port_num)) ||
	    port_num >= priv->hw_params.num_ports)
		वापस -EINVAL;

	/* If the rule is matching a particular VLAN, make sure that we honor
	 * the matching and have it tagged or untagged on the destination port,
	 * we करो this on egress with a VLAN entry. The egress tagging attribute
	 * is expected to be provided in h_ext.data[1] bit 0. A 1 means untagged,
	 * a 0 means tagged.
	 */
	अगर (fs->flow_type & FLOW_EXT) अणु
		/* We cannot support matching multiple VLAN IDs yet */
		अगर ((be16_to_cpu(fs->m_ext.vlan_tci) & VLAN_VID_MASK) !=
		    VLAN_VID_MASK)
			वापस -EINVAL;

		vid = be16_to_cpu(fs->h_ext.vlan_tci) & VLAN_VID_MASK;
		vlan.vid = vid;
		अगर (be32_to_cpu(fs->h_ext.data[1]) & 1)
			vlan.flags = BRIDGE_VLAN_INFO_UNTAGGED;
		अन्यथा
			vlan.flags = 0;

		ret = ds->ops->port_vlan_add(ds, port_num, &vlan, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * We have a small oddity where Port 6 just करोes not have a
	 * valid bit here (so we substract by one).
	 */
	queue_num = ring_cookie % SF2_NUM_EGRESS_QUEUES;
	अगर (port_num >= 7)
		port_num -= 1;

	चयन (fs->flow_type & ~FLOW_EXT) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		ret = bcm_sf2_cfp_ipv4_rule_set(priv, port, port_num,
						queue_num, fs);
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		ret = bcm_sf2_cfp_ipv6_rule_set(priv, port, port_num,
						queue_num, fs);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_rule_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	काष्ठा cfp_rule *rule = शून्य;
	पूर्णांक ret = -EINVAL;

	/* Check क्रम unsupported extensions */
	अगर (fs->flow_type & FLOW_MAC_EXT)
		वापस -EINVAL;

	अगर (fs->location != RX_CLS_LOC_ANY &&
	    fs->location > bcm_sf2_cfp_rule_size(priv))
		वापस -EINVAL;

	अगर ((fs->flow_type & FLOW_EXT) &&
	    !(ds->ops->port_vlan_add || ds->ops->port_vlan_del))
		वापस -EOPNOTSUPP;

	अगर (fs->location != RX_CLS_LOC_ANY &&
	    test_bit(fs->location, priv->cfp.used))
		वापस -EBUSY;

	ret = bcm_sf2_cfp_rule_cmp(priv, port, fs);
	अगर (ret == 0)
		वापस -EEXIST;

	rule = kzalloc(माप(*rule), GFP_KERNEL);
	अगर (!rule)
		वापस -ENOMEM;

	ret = bcm_sf2_cfp_rule_insert(ds, port, fs);
	अगर (ret) अणु
		kमुक्त(rule);
		वापस ret;
	पूर्ण

	rule->port = port;
	स_नकल(&rule->fs, fs, माप(*fs));
	list_add_tail(&rule->next, &priv->cfp.rules_list);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_rule_del_one(काष्ठा bcm_sf2_priv *priv, पूर्णांक port,
				    u32 loc, u32 *next_loc)
अणु
	पूर्णांक ret;
	u32 reg;

	/* Indicate which rule we want to पढ़ो */
	bcm_sf2_cfp_rule_addr_set(priv, loc);

	ret =  bcm_sf2_cfp_op(priv, OP_SEL_READ | TCAM_SEL);
	अगर (ret)
		वापस ret;

	/* Check अगर this is possibly an IPv6 rule that would
	 * indicate we need to delete its companion rule
	 * as well
	 */
	reg = core_पढ़ोl(priv, CORE_CFP_DATA_PORT(6));
	अगर (next_loc)
		*next_loc = (reg >> 24) & CHAIN_ID_MASK;

	/* Clear its valid bits */
	reg = core_पढ़ोl(priv, CORE_CFP_DATA_PORT(0));
	reg &= ~SLICE_VALID;
	core_ग_लिखोl(priv, reg, CORE_CFP_DATA_PORT(0));

	/* Write back this entry पूर्णांकo the TCAM now */
	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | TCAM_SEL);
	अगर (ret)
		वापस ret;

	clear_bit(loc, priv->cfp.used);
	clear_bit(loc, priv->cfp.unique);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_rule_हटाओ(काष्ठा bcm_sf2_priv *priv, पूर्णांक port,
				   u32 loc)
अणु
	u32 next_loc = 0;
	पूर्णांक ret;

	ret = bcm_sf2_cfp_rule_del_one(priv, port, loc, &next_loc);
	अगर (ret)
		वापस ret;

	/* If this was an IPv6 rule, delete is companion rule too */
	अगर (next_loc)
		ret = bcm_sf2_cfp_rule_del_one(priv, port, next_loc, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_rule_del(काष्ठा bcm_sf2_priv *priv, पूर्णांक port, u32 loc)
अणु
	काष्ठा cfp_rule *rule;
	पूर्णांक ret;

	अगर (loc > bcm_sf2_cfp_rule_size(priv))
		वापस -EINVAL;

	/* Refuse deleting unused rules, and those that are not unique since
	 * that could leave IPv6 rules with one of the chained rule in the
	 * table.
	 */
	अगर (!test_bit(loc, priv->cfp.unique) || loc == 0)
		वापस -EINVAL;

	rule = bcm_sf2_cfp_rule_find(priv, port, loc);
	अगर (!rule)
		वापस -EINVAL;

	ret = bcm_sf2_cfp_rule_हटाओ(priv, port, loc);

	list_del(&rule->next);
	kमुक्त(rule);

	वापस ret;
पूर्ण

अटल व्योम bcm_sf2_invert_masks(काष्ठा ethtool_rx_flow_spec *flow)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < माप(flow->m_u); i++)
		flow->m_u.hdata[i] ^= 0xff;

	flow->m_ext.vlan_etype ^= cpu_to_be16(~0);
	flow->m_ext.vlan_tci ^= cpu_to_be16(~0);
	flow->m_ext.data[0] ^= cpu_to_be32(~0);
	flow->m_ext.data[1] ^= cpu_to_be32(~0);
पूर्ण

अटल पूर्णांक bcm_sf2_cfp_rule_get(काष्ठा bcm_sf2_priv *priv, पूर्णांक port,
				काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा cfp_rule *rule;

	rule = bcm_sf2_cfp_rule_find(priv, port, nfc->fs.location);
	अगर (!rule)
		वापस -EINVAL;

	स_नकल(&nfc->fs, &rule->fs, माप(rule->fs));

	bcm_sf2_invert_masks(&nfc->fs);

	/* Put the TCAM size here */
	nfc->data = bcm_sf2_cfp_rule_size(priv);

	वापस 0;
पूर्ण

/* We implement the search करोing a TCAM search operation */
अटल पूर्णांक bcm_sf2_cfp_rule_get_all(काष्ठा bcm_sf2_priv *priv,
				    पूर्णांक port, काष्ठा ethtool_rxnfc *nfc,
				    u32 *rule_locs)
अणु
	अचिन्हित पूर्णांक index = 1, rules_cnt = 0;

	क्रम_each_set_bit_from(index, priv->cfp.unique, priv->num_cfp_rules) अणु
		rule_locs[rules_cnt] = index;
		rules_cnt++;
	पूर्ण

	/* Put the TCAM size here */
	nfc->data = bcm_sf2_cfp_rule_size(priv);
	nfc->rule_cnt = rules_cnt;

	वापस 0;
पूर्ण

पूर्णांक bcm_sf2_get_rxnfc(काष्ठा dsa_चयन *ds, पूर्णांक port,
		      काष्ठा ethtool_rxnfc *nfc, u32 *rule_locs)
अणु
	काष्ठा net_device *p = dsa_to_port(ds, port)->cpu_dp->master;
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	पूर्णांक ret = 0;

	mutex_lock(&priv->cfp.lock);

	चयन (nfc->cmd) अणु
	हाल ETHTOOL_GRXCLSRLCNT:
		/* Subtract the शेष, unusable rule */
		nfc->rule_cnt = biपंचांगap_weight(priv->cfp.unique,
					      priv->num_cfp_rules) - 1;
		/* We support specअगरying rule locations */
		nfc->data |= RX_CLS_LOC_SPECIAL;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = bcm_sf2_cfp_rule_get(priv, port, nfc);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		ret = bcm_sf2_cfp_rule_get_all(priv, port, nfc, rule_locs);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&priv->cfp.lock);

	अगर (ret)
		वापस ret;

	/* Pass up the commands to the attached master network device */
	अगर (p->ethtool_ops->get_rxnfc) अणु
		ret = p->ethtool_ops->get_rxnfc(p, nfc, rule_locs);
		अगर (ret == -EOPNOTSUPP)
			ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक bcm_sf2_set_rxnfc(काष्ठा dsa_चयन *ds, पूर्णांक port,
		      काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा net_device *p = dsa_to_port(ds, port)->cpu_dp->master;
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	पूर्णांक ret = 0;

	mutex_lock(&priv->cfp.lock);

	चयन (nfc->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		ret = bcm_sf2_cfp_rule_set(ds, port, &nfc->fs);
		अवरोध;

	हाल ETHTOOL_SRXCLSRLDEL:
		ret = bcm_sf2_cfp_rule_del(priv, port, nfc->fs.location);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mutex_unlock(&priv->cfp.lock);

	अगर (ret)
		वापस ret;

	/* Pass up the commands to the attached master network device.
	 * This can fail, so rollback the operation अगर we need to.
	 */
	अगर (p->ethtool_ops->set_rxnfc) अणु
		ret = p->ethtool_ops->set_rxnfc(p, nfc);
		अगर (ret && ret != -EOPNOTSUPP) अणु
			mutex_lock(&priv->cfp.lock);
			bcm_sf2_cfp_rule_del(priv, port, nfc->fs.location);
			mutex_unlock(&priv->cfp.lock);
		पूर्ण अन्यथा अणु
			ret = 0;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक bcm_sf2_cfp_rst(काष्ठा bcm_sf2_priv *priv)
अणु
	अचिन्हित पूर्णांक समयout = 1000;
	u32 reg;

	reg = core_पढ़ोl(priv, CORE_CFP_ACC);
	reg |= TCAM_RESET;
	core_ग_लिखोl(priv, reg, CORE_CFP_ACC);

	करो अणु
		reg = core_पढ़ोl(priv, CORE_CFP_ACC);
		अगर (!(reg & TCAM_RESET))
			अवरोध;

		cpu_relax();
	पूर्ण जबतक (समयout--);

	अगर (!समयout)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

व्योम bcm_sf2_cfp_निकास(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	काष्ठा cfp_rule *rule, *n;

	अगर (list_empty(&priv->cfp.rules_list))
		वापस;

	list_क्रम_each_entry_safe_reverse(rule, n, &priv->cfp.rules_list, next)
		bcm_sf2_cfp_rule_del(priv, rule->port, rule->fs.location);
पूर्ण

पूर्णांक bcm_sf2_cfp_resume(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	काष्ठा cfp_rule *rule;
	पूर्णांक ret = 0;
	u32 reg;

	अगर (list_empty(&priv->cfp.rules_list))
		वापस ret;

	reg = core_पढ़ोl(priv, CORE_CFP_CTL_REG);
	reg &= ~CFP_EN_MAP_MASK;
	core_ग_लिखोl(priv, reg, CORE_CFP_CTL_REG);

	ret = bcm_sf2_cfp_rst(priv);
	अगर (ret)
		वापस ret;

	list_क्रम_each_entry(rule, &priv->cfp.rules_list, next) अणु
		ret = bcm_sf2_cfp_rule_हटाओ(priv, rule->port,
					      rule->fs.location);
		अगर (ret) अणु
			dev_err(ds->dev, "failed to remove rule\n");
			वापस ret;
		पूर्ण

		ret = bcm_sf2_cfp_rule_insert(ds, rule->port, &rule->fs);
		अगर (ret) अणु
			dev_err(ds->dev, "failed to restore rule\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा bcm_sf2_cfp_stat अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक ram_loc;
	स्थिर अक्षर *name;
पूर्ण bcm_sf2_cfp_stats[] = अणु
	अणु
		.offset = CORE_STAT_GREEN_CNTR,
		.ram_loc = GREEN_STAT_RAM,
		.name = "Green"
	पूर्ण,
	अणु
		.offset = CORE_STAT_YELLOW_CNTR,
		.ram_loc = YELLOW_STAT_RAM,
		.name = "Yellow"
	पूर्ण,
	अणु
		.offset = CORE_STAT_RED_CNTR,
		.ram_loc = RED_STAT_RAM,
		.name = "Red"
	पूर्ण,
पूर्ण;

व्योम bcm_sf2_cfp_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     u32 stringset, uपूर्णांक8_t *data)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	अचिन्हित पूर्णांक s = ARRAY_SIZE(bcm_sf2_cfp_stats);
	अक्षर buf[ETH_GSTRING_LEN];
	अचिन्हित पूर्णांक i, j, iter;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (i = 1; i < priv->num_cfp_rules; i++) अणु
		क्रम (j = 0; j < s; j++) अणु
			snम_लिखो(buf, माप(buf),
				 "CFP%03d_%sCntr",
				 i, bcm_sf2_cfp_stats[j].name);
			iter = (i - 1) * s + j;
			strlcpy(data + iter * ETH_GSTRING_LEN,
				buf, ETH_GSTRING_LEN);
		पूर्ण
	पूर्ण
पूर्ण

व्योम bcm_sf2_cfp_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   uपूर्णांक64_t *data)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	अचिन्हित पूर्णांक s = ARRAY_SIZE(bcm_sf2_cfp_stats);
	स्थिर काष्ठा bcm_sf2_cfp_stat *stat;
	अचिन्हित पूर्णांक i, j, iter;
	काष्ठा cfp_rule *rule;
	पूर्णांक ret;

	mutex_lock(&priv->cfp.lock);
	क्रम (i = 1; i < priv->num_cfp_rules; i++) अणु
		rule = bcm_sf2_cfp_rule_find(priv, port, i);
		अगर (!rule)
			जारी;

		क्रम (j = 0; j < s; j++) अणु
			stat = &bcm_sf2_cfp_stats[j];

			bcm_sf2_cfp_rule_addr_set(priv, i);
			ret = bcm_sf2_cfp_op(priv, stat->ram_loc | OP_SEL_READ);
			अगर (ret)
				जारी;

			iter = (i - 1) * s + j;
			data[iter] = core_पढ़ोl(priv, stat->offset);
		पूर्ण

	पूर्ण
	mutex_unlock(&priv->cfp.lock);
पूर्ण

पूर्णांक bcm_sf2_cfp_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	काष्ठा bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);

	अगर (sset != ETH_SS_STATS)
		वापस 0;

	/* 3 counters per CFP rules */
	वापस (priv->num_cfp_rules - 1) * ARRAY_SIZE(bcm_sf2_cfp_stats);
पूर्ण
