<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2017 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/flow_dissector.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_skbedit.h>
#समावेश <net/tc_act/tc_mirred.h>
#समावेश <net/tc_act/tc_vlan.h>
#समावेश <net/tc_act/tc_pedit.h>
#समावेश <net/tc_act/tc_tunnel_key.h>
#समावेश <net/vxlan.h>

#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"
#समावेश "bnxt_sriov.h"
#समावेश "bnxt_tc.h"
#समावेश "bnxt_vfr.h"

#घोषणा BNXT_FID_INVALID			0xffff
#घोषणा VLAN_TCI(vid, prio)	((vid) | ((prio) << VLAN_PRIO_SHIFT))

#घोषणा is_vlan_pcp_wildcarded(vlan_tci_mask)	\
	((ntohs(vlan_tci_mask) & VLAN_PRIO_MASK) == 0x0000)
#घोषणा is_vlan_pcp_exacपंचांगatch(vlan_tci_mask)	\
	((ntohs(vlan_tci_mask) & VLAN_PRIO_MASK) == VLAN_PRIO_MASK)
#घोषणा is_vlan_pcp_zero(vlan_tci)	\
	((ntohs(vlan_tci) & VLAN_PRIO_MASK) == 0x0000)
#घोषणा is_vid_exacपंचांगatch(vlan_tci_mask)	\
	((ntohs(vlan_tci_mask) & VLAN_VID_MASK) == VLAN_VID_MASK)

अटल bool is_wildcard(व्योम *mask, पूर्णांक len);
अटल bool is_exacपंचांगatch(व्योम *mask, पूर्णांक len);
/* Return the dst fid of the func क्रम flow क्रमwarding
 * For PFs: src_fid is the fid of the PF
 * For VF-reps: src_fid the fid of the VF
 */
अटल u16 bnxt_flow_get_dst_fid(काष्ठा bnxt *pf_bp, काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp;

	/* check अगर dev beदीर्घs to the same चयन */
	अगर (!netdev_port_same_parent_id(pf_bp->dev, dev)) अणु
		netdev_info(pf_bp->dev, "dev(ifindex=%d) not on same switch\n",
			    dev->अगरindex);
		वापस BNXT_FID_INVALID;
	पूर्ण

	/* Is dev a VF-rep? */
	अगर (bnxt_dev_is_vf_rep(dev))
		वापस bnxt_vf_rep_get_fid(dev);

	bp = netdev_priv(dev);
	वापस bp->pf.fw_fid;
पूर्ण

अटल पूर्णांक bnxt_tc_parse_redir(काष्ठा bnxt *bp,
			       काष्ठा bnxt_tc_actions *actions,
			       स्थिर काष्ठा flow_action_entry *act)
अणु
	काष्ठा net_device *dev = act->dev;

	अगर (!dev) अणु
		netdev_info(bp->dev, "no dev in mirred action\n");
		वापस -EINVAL;
	पूर्ण

	actions->flags |= BNXT_TC_ACTION_FLAG_FWD;
	actions->dst_dev = dev;
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_tc_parse_vlan(काष्ठा bnxt *bp,
			      काष्ठा bnxt_tc_actions *actions,
			      स्थिर काष्ठा flow_action_entry *act)
अणु
	चयन (act->id) अणु
	हाल FLOW_ACTION_VLAN_POP:
		actions->flags |= BNXT_TC_ACTION_FLAG_POP_VLAN;
		अवरोध;
	हाल FLOW_ACTION_VLAN_PUSH:
		actions->flags |= BNXT_TC_ACTION_FLAG_PUSH_VLAN;
		actions->push_vlan_tci = htons(act->vlan.vid);
		actions->push_vlan_tpid = act->vlan.proto;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_tc_parse_tunnel_set(काष्ठा bnxt *bp,
				    काष्ठा bnxt_tc_actions *actions,
				    स्थिर काष्ठा flow_action_entry *act)
अणु
	स्थिर काष्ठा ip_tunnel_info *tun_info = act->tunnel;
	स्थिर काष्ठा ip_tunnel_key *tun_key = &tun_info->key;

	अगर (ip_tunnel_info_af(tun_info) != AF_INET) अणु
		netdev_info(bp->dev, "only IPv4 tunnel-encap is supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	actions->tun_encap_key = *tun_key;
	actions->flags |= BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP;
	वापस 0;
पूर्ण

/* Key & Mask from the stack comes unaligned in multiple iterations of 4 bytes
 * each(u32).
 * This routine consolidates such multiple unaligned values पूर्णांकo one
 * field each क्रम Key & Mask (क्रम src and dst macs separately)
 * For example,
 *			Mask/Key	Offset	Iteration
 *			==========	======	=========
 *	dst mac		0xffffffff	0	1
 *	dst mac		0x0000ffff	4	2
 *
 *	src mac		0xffff0000	4	1
 *	src mac		0xffffffff	8	2
 *
 * The above combination coming from the stack will be consolidated as
 *			Mask/Key
 *			==============
 *	src mac:	0xffffffffffff
 *	dst mac:	0xffffffffffff
 */
अटल व्योम bnxt_set_l2_key_mask(u32 part_key, u32 part_mask,
				 u8 *actual_key, u8 *actual_mask)
अणु
	u32 key = get_unaligned((u32 *)actual_key);
	u32 mask = get_unaligned((u32 *)actual_mask);

	part_key &= part_mask;
	part_key |= key & ~part_mask;

	put_unaligned(mask | part_mask, (u32 *)actual_mask);
	put_unaligned(part_key, (u32 *)actual_key);
पूर्ण

अटल पूर्णांक
bnxt_fill_l2_reग_लिखो_fields(काष्ठा bnxt_tc_actions *actions,
			    u16 *eth_addr, u16 *eth_addr_mask)
अणु
	u16 *p;
	पूर्णांक j;

	अगर (unlikely(bnxt_eth_addr_key_mask_invalid(eth_addr, eth_addr_mask)))
		वापस -EINVAL;

	अगर (!is_wildcard(&eth_addr_mask[0], ETH_ALEN)) अणु
		अगर (!is_exacपंचांगatch(&eth_addr_mask[0], ETH_ALEN))
			वापस -EINVAL;
		/* FW expects dmac to be in u16 array क्रमmat */
		p = eth_addr;
		क्रम (j = 0; j < 3; j++)
			actions->l2_reग_लिखो_dmac[j] = cpu_to_be16(*(p + j));
	पूर्ण

	अगर (!is_wildcard(&eth_addr_mask[ETH_ALEN / 2], ETH_ALEN)) अणु
		अगर (!is_exacपंचांगatch(&eth_addr_mask[ETH_ALEN / 2], ETH_ALEN))
			वापस -EINVAL;
		/* FW expects smac to be in u16 array क्रमmat */
		p = &eth_addr[ETH_ALEN / 2];
		क्रम (j = 0; j < 3; j++)
			actions->l2_reग_लिखो_smac[j] = cpu_to_be16(*(p + j));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bnxt_tc_parse_pedit(काष्ठा bnxt *bp, काष्ठा bnxt_tc_actions *actions,
		    काष्ठा flow_action_entry *act, पूर्णांक act_idx, u8 *eth_addr,
		    u8 *eth_addr_mask)
अणु
	माप_प्रकार offset_of_ip6_daddr = दुरत्व(काष्ठा ipv6hdr, daddr);
	माप_प्रकार offset_of_ip6_saddr = दुरत्व(काष्ठा ipv6hdr, saddr);
	u32 mask, val, offset, idx;
	u8 htype;

	offset = act->mangle.offset;
	htype = act->mangle.htype;
	mask = ~act->mangle.mask;
	val = act->mangle.val;

	चयन (htype) अणु
	हाल FLOW_ACT_MANGLE_HDR_TYPE_ETH:
		अगर (offset > PEDIT_OFFSET_SMAC_LAST_4_BYTES) अणु
			netdev_err(bp->dev,
				   "%s: eth_hdr: Invalid pedit field\n",
				   __func__);
			वापस -EINVAL;
		पूर्ण
		actions->flags |= BNXT_TC_ACTION_FLAG_L2_REWRITE;

		bnxt_set_l2_key_mask(val, mask, &eth_addr[offset],
				     &eth_addr_mask[offset]);
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_IP4:
		actions->flags |= BNXT_TC_ACTION_FLAG_NAT_XLATE;
		actions->nat.l3_is_ipv4 = true;
		अगर (offset ==  दुरत्व(काष्ठा iphdr, saddr)) अणु
			actions->nat.src_xlate = true;
			actions->nat.l3.ipv4.saddr.s_addr = htonl(val);
		पूर्ण अन्यथा अगर (offset ==  दुरत्व(काष्ठा iphdr, daddr)) अणु
			actions->nat.src_xlate = false;
			actions->nat.l3.ipv4.daddr.s_addr = htonl(val);
		पूर्ण अन्यथा अणु
			netdev_err(bp->dev,
				   "%s: IPv4_hdr: Invalid pedit field\n",
				   __func__);
			वापस -EINVAL;
		पूर्ण

		netdev_dbg(bp->dev, "nat.src_xlate = %d src IP: %pI4 dst ip : %pI4\n",
			   actions->nat.src_xlate, &actions->nat.l3.ipv4.saddr,
			   &actions->nat.l3.ipv4.daddr);
		अवरोध;

	हाल FLOW_ACT_MANGLE_HDR_TYPE_IP6:
		actions->flags |= BNXT_TC_ACTION_FLAG_NAT_XLATE;
		actions->nat.l3_is_ipv4 = false;
		अगर (offset >= दुरत्व(काष्ठा ipv6hdr, saddr) &&
		    offset < offset_of_ip6_daddr) अणु
			/* 16 byte IPv6 address comes in 4 iterations of
			 * 4byte chunks each
			 */
			actions->nat.src_xlate = true;
			idx = (offset - offset_of_ip6_saddr) / 4;
			/* First 4bytes will be copied to idx 0 and so on */
			actions->nat.l3.ipv6.saddr.s6_addr32[idx] = htonl(val);
		पूर्ण अन्यथा अगर (offset >= offset_of_ip6_daddr &&
			   offset < offset_of_ip6_daddr + 16) अणु
			actions->nat.src_xlate = false;
			idx = (offset - offset_of_ip6_daddr) / 4;
			actions->nat.l3.ipv6.saddr.s6_addr32[idx] = htonl(val);
		पूर्ण अन्यथा अणु
			netdev_err(bp->dev,
				   "%s: IPv6_hdr: Invalid pedit field\n",
				   __func__);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल FLOW_ACT_MANGLE_HDR_TYPE_TCP:
	हाल FLOW_ACT_MANGLE_HDR_TYPE_UDP:
		/* HW करोes not support L4 reग_लिखो alone without L3
		 * reग_लिखो
		 */
		अगर (!(actions->flags & BNXT_TC_ACTION_FLAG_NAT_XLATE)) अणु
			netdev_err(bp->dev,
				   "Need to specify L3 rewrite as well\n");
			वापस -EINVAL;
		पूर्ण
		अगर (actions->nat.src_xlate)
			actions->nat.l4.ports.sport = htons(val);
		अन्यथा
			actions->nat.l4.ports.dport = htons(val);
		netdev_dbg(bp->dev, "actions->nat.sport = %d dport = %d\n",
			   actions->nat.l4.ports.sport,
			   actions->nat.l4.ports.dport);
		अवरोध;
	शेष:
		netdev_err(bp->dev, "%s: Unsupported pedit hdr type\n",
			   __func__);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_tc_parse_actions(काष्ठा bnxt *bp,
				 काष्ठा bnxt_tc_actions *actions,
				 काष्ठा flow_action *flow_action,
				 काष्ठा netlink_ext_ack *extack)
अणु
	/* Used to store the L2 reग_लिखो mask क्रम dmac (6 bytes) followed by
	 * smac (6 bytes) अगर reग_लिखो of both is specअगरied, otherwise either
	 * dmac or smac
	 */
	u16 eth_addr_mask[ETH_ALEN] = अणु 0 पूर्ण;
	/* Used to store the L2 reग_लिखो key क्रम dmac (6 bytes) followed by
	 * smac (6 bytes) अगर reग_लिखो of both is specअगरied, otherwise either
	 * dmac or smac
	 */
	u16 eth_addr[ETH_ALEN] = अणु 0 पूर्ण;
	काष्ठा flow_action_entry *act;
	पूर्णांक i, rc;

	अगर (!flow_action_has_entries(flow_action)) अणु
		netdev_info(bp->dev, "no actions\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!flow_action_basic_hw_stats_check(flow_action, extack))
		वापस -EOPNOTSUPP;

	flow_action_क्रम_each(i, act, flow_action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_DROP:
			actions->flags |= BNXT_TC_ACTION_FLAG_DROP;
			वापस 0; /* करोn't bother with other actions */
		हाल FLOW_ACTION_REसूचीECT:
			rc = bnxt_tc_parse_redir(bp, actions, act);
			अगर (rc)
				वापस rc;
			अवरोध;
		हाल FLOW_ACTION_VLAN_POP:
		हाल FLOW_ACTION_VLAN_PUSH:
		हाल FLOW_ACTION_VLAN_MANGLE:
			rc = bnxt_tc_parse_vlan(bp, actions, act);
			अगर (rc)
				वापस rc;
			अवरोध;
		हाल FLOW_ACTION_TUNNEL_ENCAP:
			rc = bnxt_tc_parse_tunnel_set(bp, actions, act);
			अगर (rc)
				वापस rc;
			अवरोध;
		हाल FLOW_ACTION_TUNNEL_DECAP:
			actions->flags |= BNXT_TC_ACTION_FLAG_TUNNEL_DECAP;
			अवरोध;
		/* Packet edit: L2 reग_लिखो, NAT, NAPT */
		हाल FLOW_ACTION_MANGLE:
			rc = bnxt_tc_parse_pedit(bp, actions, act, i,
						 (u8 *)eth_addr,
						 (u8 *)eth_addr_mask);
			अगर (rc)
				वापस rc;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (actions->flags & BNXT_TC_ACTION_FLAG_L2_REWRITE) अणु
		rc = bnxt_fill_l2_reग_लिखो_fields(actions, eth_addr,
						 eth_addr_mask);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (actions->flags & BNXT_TC_ACTION_FLAG_FWD) अणु
		अगर (actions->flags & BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP) अणु
			/* dst_fid is PF's fid */
			actions->dst_fid = bp->pf.fw_fid;
		पूर्ण अन्यथा अणु
			/* find the FID from dst_dev */
			actions->dst_fid =
				bnxt_flow_get_dst_fid(bp, actions->dst_dev);
			अगर (actions->dst_fid == BNXT_FID_INVALID)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_tc_parse_flow(काष्ठा bnxt *bp,
			      काष्ठा flow_cls_offload *tc_flow_cmd,
			      काष्ठा bnxt_tc_flow *flow)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(tc_flow_cmd);
	काष्ठा flow_dissector *dissector = rule->match.dissector;

	/* KEY_CONTROL and KEY_BASIC are needed क्रम क्रमming a meaningful key */
	अगर ((dissector->used_keys & BIT(FLOW_DISSECTOR_KEY_CONTROL)) == 0 ||
	    (dissector->used_keys & BIT(FLOW_DISSECTOR_KEY_BASIC)) == 0) अणु
		netdev_info(bp->dev, "cannot form TC key: used_keys = 0x%x\n",
			    dissector->used_keys);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		flow->l2_key.ether_type = match.key->n_proto;
		flow->l2_mask.ether_type = match.mask->n_proto;

		अगर (match.key->n_proto == htons(ETH_P_IP) ||
		    match.key->n_proto == htons(ETH_P_IPV6)) अणु
			flow->l4_key.ip_proto = match.key->ip_proto;
			flow->l4_mask.ip_proto = match.mask->ip_proto;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_ETH_ADDRS;
		ether_addr_copy(flow->l2_key.dmac, match.key->dst);
		ether_addr_copy(flow->l2_mask.dmac, match.mask->dst);
		ether_addr_copy(flow->l2_key.smac, match.key->src);
		ether_addr_copy(flow->l2_mask.smac, match.mask->src);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		flow->l2_key.inner_vlan_tci =
			cpu_to_be16(VLAN_TCI(match.key->vlan_id,
					     match.key->vlan_priority));
		flow->l2_mask.inner_vlan_tci =
			cpu_to_be16((VLAN_TCI(match.mask->vlan_id,
					      match.mask->vlan_priority)));
		flow->l2_key.inner_vlan_tpid = htons(ETH_P_8021Q);
		flow->l2_mask.inner_vlan_tpid = htons(0xffff);
		flow->l2_key.num_vlans = 1;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_IPV4_ADDRS;
		flow->l3_key.ipv4.daddr.s_addr = match.key->dst;
		flow->l3_mask.ipv4.daddr.s_addr = match.mask->dst;
		flow->l3_key.ipv4.saddr.s_addr = match.key->src;
		flow->l3_mask.ipv4.saddr.s_addr = match.mask->src;
	पूर्ण अन्यथा अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS)) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_IPV6_ADDRS;
		flow->l3_key.ipv6.daddr = match.key->dst;
		flow->l3_mask.ipv6.daddr = match.mask->dst;
		flow->l3_key.ipv6.saddr = match.key->src;
		flow->l3_mask.ipv6.saddr = match.mask->src;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_PORTS;
		flow->l4_key.ports.dport = match.key->dst;
		flow->l4_mask.ports.dport = match.mask->dst;
		flow->l4_key.ports.sport = match.key->src;
		flow->l4_mask.ports.sport = match.mask->src;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ICMP)) अणु
		काष्ठा flow_match_icmp match;

		flow_rule_match_icmp(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_ICMP;
		flow->l4_key.icmp.type = match.key->type;
		flow->l4_key.icmp.code = match.key->code;
		flow->l4_mask.icmp.type = match.mask->type;
		flow->l4_mask.icmp.code = match.mask->code;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS)) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_enc_ipv4_addrs(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_IPV4_ADDRS;
		flow->tun_key.u.ipv4.dst = match.key->dst;
		flow->tun_mask.u.ipv4.dst = match.mask->dst;
		flow->tun_key.u.ipv4.src = match.key->src;
		flow->tun_mask.u.ipv4.src = match.mask->src;
	पूर्ण अन्यथा अगर (flow_rule_match_key(rule,
				      FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) अणु
		काष्ठा flow_match_enc_keyid match;

		flow_rule_match_enc_keyid(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_ID;
		flow->tun_key.tun_id = key32_to_tunnel_id(match.key->keyid);
		flow->tun_mask.tun_id = key32_to_tunnel_id(match.mask->keyid);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_enc_ports(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_PORTS;
		flow->tun_key.tp_dst = match.key->dst;
		flow->tun_mask.tp_dst = match.mask->dst;
		flow->tun_key.tp_src = match.key->src;
		flow->tun_mask.tp_src = match.mask->src;
	पूर्ण

	वापस bnxt_tc_parse_actions(bp, &flow->actions, &rule->action,
				     tc_flow_cmd->common.extack);
पूर्ण

अटल पूर्णांक bnxt_hwrm_cfa_flow_मुक्त(काष्ठा bnxt *bp,
				   काष्ठा bnxt_tc_flow_node *flow_node)
अणु
	काष्ठा hwrm_cfa_flow_मुक्त_input req = अणु 0 पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_FLOW_FREE, -1, -1);
	अगर (bp->fw_cap & BNXT_FW_CAP_OVS_64BIT_HANDLE)
		req.ext_flow_handle = flow_node->ext_flow_handle;
	अन्यथा
		req.flow_handle = flow_node->flow_handle;

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		netdev_info(bp->dev, "%s: Error rc=%d\n", __func__, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक ipv6_mask_len(काष्ठा in6_addr *mask)
अणु
	पूर्णांक mask_len = 0, i;

	क्रम (i = 0; i < 4; i++)
		mask_len += inet_mask_len(mask->s6_addr32[i]);

	वापस mask_len;
पूर्ण

अटल bool is_wildcard(व्योम *mask, पूर्णांक len)
अणु
	स्थिर u8 *p = mask;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (p[i] != 0)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool is_exacपंचांगatch(व्योम *mask, पूर्णांक len)
अणु
	स्थिर u8 *p = mask;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		अगर (p[i] != 0xff)
			वापस false;

	वापस true;
पूर्ण

अटल bool is_vlan_tci_allowed(__be16  vlan_tci_mask,
				__be16  vlan_tci)
अणु
	/* VLAN priority must be either exactly zero or fully wildcarded and
	 * VLAN id must be exact match.
	 */
	अगर (is_vid_exacपंचांगatch(vlan_tci_mask) &&
	    ((is_vlan_pcp_exacपंचांगatch(vlan_tci_mask) &&
	      is_vlan_pcp_zero(vlan_tci)) ||
	     is_vlan_pcp_wildcarded(vlan_tci_mask)))
		वापस true;

	वापस false;
पूर्ण

अटल bool bits_set(व्योम *key, पूर्णांक len)
अणु
	स्थिर u8 *p = key;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		अगर (p[i] != 0)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक bnxt_hwrm_cfa_flow_alloc(काष्ठा bnxt *bp, काष्ठा bnxt_tc_flow *flow,
				    __le16 ref_flow_handle,
				    __le32 tunnel_handle,
				    काष्ठा bnxt_tc_flow_node *flow_node)
अणु
	काष्ठा bnxt_tc_actions *actions = &flow->actions;
	काष्ठा bnxt_tc_l3_key *l3_mask = &flow->l3_mask;
	काष्ठा bnxt_tc_l3_key *l3_key = &flow->l3_key;
	काष्ठा hwrm_cfa_flow_alloc_input req = अणु 0 पूर्ण;
	काष्ठा hwrm_cfa_flow_alloc_output *resp;
	u16 flow_flags = 0, action_flags = 0;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_FLOW_ALLOC, -1, -1);

	req.src_fid = cpu_to_le16(flow->src_fid);
	req.ref_flow_handle = ref_flow_handle;

	अगर (actions->flags & BNXT_TC_ACTION_FLAG_L2_REWRITE) अणु
		स_नकल(req.l2_reग_लिखो_dmac, actions->l2_reग_लिखो_dmac,
		       ETH_ALEN);
		स_नकल(req.l2_reग_लिखो_smac, actions->l2_reग_लिखो_smac,
		       ETH_ALEN);
		action_flags |=
			CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_L2_HEADER_REWRITE;
	पूर्ण

	अगर (actions->flags & BNXT_TC_ACTION_FLAG_NAT_XLATE) अणु
		अगर (actions->nat.l3_is_ipv4) अणु
			action_flags |=
				CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_NAT_IPV4_ADDRESS;

			अगर (actions->nat.src_xlate) अणु
				action_flags |=
					CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_NAT_SRC;
				/* L3 source reग_लिखो */
				req.nat_ip_address[0] =
					actions->nat.l3.ipv4.saddr.s_addr;
				/* L4 source port */
				अगर (actions->nat.l4.ports.sport)
					req.nat_port =
						actions->nat.l4.ports.sport;
			पूर्ण अन्यथा अणु
				action_flags |=
					CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_NAT_DEST;
				/* L3 destination reग_लिखो */
				req.nat_ip_address[0] =
					actions->nat.l3.ipv4.daddr.s_addr;
				/* L4 destination port */
				अगर (actions->nat.l4.ports.dport)
					req.nat_port =
						actions->nat.l4.ports.dport;
			पूर्ण
			netdev_dbg(bp->dev,
				   "req.nat_ip_address: %pI4 src_xlate: %d req.nat_port: %x\n",
				   req.nat_ip_address, actions->nat.src_xlate,
				   req.nat_port);
		पूर्ण अन्यथा अणु
			अगर (actions->nat.src_xlate) अणु
				action_flags |=
					CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_NAT_SRC;
				/* L3 source reग_लिखो */
				स_नकल(req.nat_ip_address,
				       actions->nat.l3.ipv6.saddr.s6_addr32,
				       माप(req.nat_ip_address));
				/* L4 source port */
				अगर (actions->nat.l4.ports.sport)
					req.nat_port =
						actions->nat.l4.ports.sport;
			पूर्ण अन्यथा अणु
				action_flags |=
					CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_NAT_DEST;
				/* L3 destination reग_लिखो */
				स_नकल(req.nat_ip_address,
				       actions->nat.l3.ipv6.daddr.s6_addr32,
				       माप(req.nat_ip_address));
				/* L4 destination port */
				अगर (actions->nat.l4.ports.dport)
					req.nat_port =
						actions->nat.l4.ports.dport;
			पूर्ण
			netdev_dbg(bp->dev,
				   "req.nat_ip_address: %pI6 src_xlate: %d req.nat_port: %x\n",
				   req.nat_ip_address, actions->nat.src_xlate,
				   req.nat_port);
		पूर्ण
	पूर्ण

	अगर (actions->flags & BNXT_TC_ACTION_FLAG_TUNNEL_DECAP ||
	    actions->flags & BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP) अणु
		req.tunnel_handle = tunnel_handle;
		flow_flags |= CFA_FLOW_ALLOC_REQ_FLAGS_TUNNEL;
		action_flags |= CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_TUNNEL;
	पूर्ण

	req.ethertype = flow->l2_key.ether_type;
	req.ip_proto = flow->l4_key.ip_proto;

	अगर (flow->flags & BNXT_TC_FLOW_FLAGS_ETH_ADDRS) अणु
		स_नकल(req.dmac, flow->l2_key.dmac, ETH_ALEN);
		स_नकल(req.smac, flow->l2_key.smac, ETH_ALEN);
	पूर्ण

	अगर (flow->l2_key.num_vlans > 0) अणु
		flow_flags |= CFA_FLOW_ALLOC_REQ_FLAGS_NUM_VLAN_ONE;
		/* FW expects the inner_vlan_tci value to be set
		 * in outer_vlan_tci when num_vlans is 1 (which is
		 * always the हाल in TC.)
		 */
		req.outer_vlan_tci = flow->l2_key.inner_vlan_tci;
	पूर्ण

	/* If all IP and L4 fields are wildcarded then this is an L2 flow */
	अगर (is_wildcard(l3_mask, माप(*l3_mask)) &&
	    is_wildcard(&flow->l4_mask, माप(flow->l4_mask))) अणु
		flow_flags |= CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_L2;
	पूर्ण अन्यथा अणु
		flow_flags |= flow->l2_key.ether_type == htons(ETH_P_IP) ?
				CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_IPV4 :
				CFA_FLOW_ALLOC_REQ_FLAGS_FLOWTYPE_IPV6;

		अगर (flow->flags & BNXT_TC_FLOW_FLAGS_IPV4_ADDRS) अणु
			req.ip_dst[0] = l3_key->ipv4.daddr.s_addr;
			req.ip_dst_mask_len =
				inet_mask_len(l3_mask->ipv4.daddr.s_addr);
			req.ip_src[0] = l3_key->ipv4.saddr.s_addr;
			req.ip_src_mask_len =
				inet_mask_len(l3_mask->ipv4.saddr.s_addr);
		पूर्ण अन्यथा अगर (flow->flags & BNXT_TC_FLOW_FLAGS_IPV6_ADDRS) अणु
			स_नकल(req.ip_dst, l3_key->ipv6.daddr.s6_addr32,
			       माप(req.ip_dst));
			req.ip_dst_mask_len =
					ipv6_mask_len(&l3_mask->ipv6.daddr);
			स_नकल(req.ip_src, l3_key->ipv6.saddr.s6_addr32,
			       माप(req.ip_src));
			req.ip_src_mask_len =
					ipv6_mask_len(&l3_mask->ipv6.saddr);
		पूर्ण
	पूर्ण

	अगर (flow->flags & BNXT_TC_FLOW_FLAGS_PORTS) अणु
		req.l4_src_port = flow->l4_key.ports.sport;
		req.l4_src_port_mask = flow->l4_mask.ports.sport;
		req.l4_dst_port = flow->l4_key.ports.dport;
		req.l4_dst_port_mask = flow->l4_mask.ports.dport;
	पूर्ण अन्यथा अगर (flow->flags & BNXT_TC_FLOW_FLAGS_ICMP) अणु
		/* l4 ports serve as type/code when ip_proto is ICMP */
		req.l4_src_port = htons(flow->l4_key.icmp.type);
		req.l4_src_port_mask = htons(flow->l4_mask.icmp.type);
		req.l4_dst_port = htons(flow->l4_key.icmp.code);
		req.l4_dst_port_mask = htons(flow->l4_mask.icmp.code);
	पूर्ण
	req.flags = cpu_to_le16(flow_flags);

	अगर (actions->flags & BNXT_TC_ACTION_FLAG_DROP) अणु
		action_flags |= CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_DROP;
	पूर्ण अन्यथा अणु
		अगर (actions->flags & BNXT_TC_ACTION_FLAG_FWD) अणु
			action_flags |= CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_FWD;
			req.dst_fid = cpu_to_le16(actions->dst_fid);
		पूर्ण
		अगर (actions->flags & BNXT_TC_ACTION_FLAG_PUSH_VLAN) अणु
			action_flags |=
			    CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_L2_HEADER_REWRITE;
			req.l2_reग_लिखो_vlan_tpid = actions->push_vlan_tpid;
			req.l2_reग_लिखो_vlan_tci = actions->push_vlan_tci;
			स_नकल(&req.l2_reग_लिखो_dmac, &req.dmac, ETH_ALEN);
			स_नकल(&req.l2_reग_लिखो_smac, &req.smac, ETH_ALEN);
		पूर्ण
		अगर (actions->flags & BNXT_TC_ACTION_FLAG_POP_VLAN) अणु
			action_flags |=
			    CFA_FLOW_ALLOC_REQ_ACTION_FLAGS_L2_HEADER_REWRITE;
			/* Reग_लिखो config with tpid = 0 implies vlan pop */
			req.l2_reग_लिखो_vlan_tpid = 0;
			स_नकल(&req.l2_reग_लिखो_dmac, &req.dmac, ETH_ALEN);
			स_नकल(&req.l2_reग_लिखो_smac, &req.smac, ETH_ALEN);
		पूर्ण
	पूर्ण
	req.action_flags = cpu_to_le16(action_flags);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		resp = bnxt_get_hwrm_resp_addr(bp, &req);
		/* CFA_FLOW_ALLOC response पूर्णांकerpretation:
		 *		    fw with	     fw with
		 *		    16-bit	     64-bit
		 *		    flow handle      flow handle
		 *		    ===========	     ===========
		 * flow_handle      flow handle      flow context id
		 * ext_flow_handle  INVALID	     flow handle
		 * flow_id	    INVALID	     flow counter id
		 */
		flow_node->flow_handle = resp->flow_handle;
		अगर (bp->fw_cap & BNXT_FW_CAP_OVS_64BIT_HANDLE) अणु
			flow_node->ext_flow_handle = resp->ext_flow_handle;
			flow_node->flow_id = resp->flow_id;
		पूर्ण
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक hwrm_cfa_decap_filter_alloc(काष्ठा bnxt *bp,
				       काष्ठा bnxt_tc_flow *flow,
				       काष्ठा bnxt_tc_l2_key *l2_info,
				       __le32 ref_decap_handle,
				       __le32 *decap_filter_handle)
अणु
	काष्ठा hwrm_cfa_decap_filter_alloc_input req = अणु 0 पूर्ण;
	काष्ठा hwrm_cfa_decap_filter_alloc_output *resp;
	काष्ठा ip_tunnel_key *tun_key = &flow->tun_key;
	u32 enables = 0;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_DECAP_FILTER_ALLOC, -1, -1);

	req.flags = cpu_to_le32(CFA_DECAP_FILTER_ALLOC_REQ_FLAGS_OVS_TUNNEL);
	enables |= CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_TUNNEL_TYPE |
		   CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_IP_PROTOCOL;
	req.tunnel_type = CFA_DECAP_FILTER_ALLOC_REQ_TUNNEL_TYPE_VXLAN;
	req.ip_protocol = CFA_DECAP_FILTER_ALLOC_REQ_IP_PROTOCOL_UDP;

	अगर (flow->flags & BNXT_TC_FLOW_FLAGS_TUNL_ID) अणु
		enables |= CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_TUNNEL_ID;
		/* tunnel_id is wrongly defined in hsi defn. as __le32 */
		req.tunnel_id = tunnel_id_to_key32(tun_key->tun_id);
	पूर्ण

	अगर (flow->flags & BNXT_TC_FLOW_FLAGS_TUNL_ETH_ADDRS) अणु
		enables |= CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_DST_MACADDR;
		ether_addr_copy(req.dst_macaddr, l2_info->dmac);
	पूर्ण
	अगर (l2_info->num_vlans) अणु
		enables |= CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_T_IVLAN_VID;
		req.t_ivlan_vid = l2_info->inner_vlan_tci;
	पूर्ण

	enables |= CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_ETHERTYPE;
	req.ethertype = htons(ETH_P_IP);

	अगर (flow->flags & BNXT_TC_FLOW_FLAGS_TUNL_IPV4_ADDRS) अणु
		enables |= CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_SRC_IPADDR |
			   CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_DST_IPADDR |
			   CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_IPADDR_TYPE;
		req.ip_addr_type = CFA_DECAP_FILTER_ALLOC_REQ_IP_ADDR_TYPE_IPV4;
		req.dst_ipaddr[0] = tun_key->u.ipv4.dst;
		req.src_ipaddr[0] = tun_key->u.ipv4.src;
	पूर्ण

	अगर (flow->flags & BNXT_TC_FLOW_FLAGS_TUNL_PORTS) अणु
		enables |= CFA_DECAP_FILTER_ALLOC_REQ_ENABLES_DST_PORT;
		req.dst_port = tun_key->tp_dst;
	पूर्ण

	/* Eventhough the decap_handle वापसed by hwrm_cfa_decap_filter_alloc
	 * is defined as __le32, l2_ctxt_ref_id is defined in HSI as __le16.
	 */
	req.l2_ctxt_ref_id = (__क्रमce __le16)ref_decap_handle;
	req.enables = cpu_to_le32(enables);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		resp = bnxt_get_hwrm_resp_addr(bp, &req);
		*decap_filter_handle = resp->decap_filter_id;
	पूर्ण अन्यथा अणु
		netdev_info(bp->dev, "%s: Error rc=%d\n", __func__, rc);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक hwrm_cfa_decap_filter_मुक्त(काष्ठा bnxt *bp,
				      __le32 decap_filter_handle)
अणु
	काष्ठा hwrm_cfa_decap_filter_मुक्त_input req = अणु 0 पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_DECAP_FILTER_FREE, -1, -1);
	req.decap_filter_id = decap_filter_handle;

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		netdev_info(bp->dev, "%s: Error rc=%d\n", __func__, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक hwrm_cfa_encap_record_alloc(काष्ठा bnxt *bp,
				       काष्ठा ip_tunnel_key *encap_key,
				       काष्ठा bnxt_tc_l2_key *l2_info,
				       __le32 *encap_record_handle)
अणु
	काष्ठा hwrm_cfa_encap_record_alloc_input req = अणु 0 पूर्ण;
	काष्ठा hwrm_cfa_encap_record_alloc_output *resp;
	काष्ठा hwrm_cfa_encap_data_vxlan *encap =
			(काष्ठा hwrm_cfa_encap_data_vxlan *)&req.encap_data;
	काष्ठा hwrm_vxlan_ipv4_hdr *encap_ipv4 =
				(काष्ठा hwrm_vxlan_ipv4_hdr *)encap->l3;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_ENCAP_RECORD_ALLOC, -1, -1);

	req.encap_type = CFA_ENCAP_RECORD_ALLOC_REQ_ENCAP_TYPE_VXLAN;

	ether_addr_copy(encap->dst_mac_addr, l2_info->dmac);
	ether_addr_copy(encap->src_mac_addr, l2_info->smac);
	अगर (l2_info->num_vlans) अणु
		encap->num_vlan_tags = l2_info->num_vlans;
		encap->ovlan_tci = l2_info->inner_vlan_tci;
		encap->ovlan_tpid = l2_info->inner_vlan_tpid;
	पूर्ण

	encap_ipv4->ver_hlen = 4 << VXLAN_IPV4_HDR_VER_HLEN_VERSION_SFT;
	encap_ipv4->ver_hlen |= 5 << VXLAN_IPV4_HDR_VER_HLEN_HEADER_LENGTH_SFT;
	encap_ipv4->ttl = encap_key->ttl;

	encap_ipv4->dest_ip_addr = encap_key->u.ipv4.dst;
	encap_ipv4->src_ip_addr = encap_key->u.ipv4.src;
	encap_ipv4->protocol = IPPROTO_UDP;

	encap->dst_port = encap_key->tp_dst;
	encap->vni = tunnel_id_to_key32(encap_key->tun_id);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		resp = bnxt_get_hwrm_resp_addr(bp, &req);
		*encap_record_handle = resp->encap_record_id;
	पूर्ण अन्यथा अणु
		netdev_info(bp->dev, "%s: Error rc=%d\n", __func__, rc);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक hwrm_cfa_encap_record_मुक्त(काष्ठा bnxt *bp,
				      __le32 encap_record_handle)
अणु
	काष्ठा hwrm_cfa_encap_record_मुक्त_input req = अणु 0 पूर्ण;
	पूर्णांक rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_ENCAP_RECORD_FREE, -1, -1);
	req.encap_record_id = encap_record_handle;

	rc = hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (rc)
		netdev_info(bp->dev, "%s: Error rc=%d\n", __func__, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_tc_put_l2_node(काष्ठा bnxt *bp,
			       काष्ठा bnxt_tc_flow_node *flow_node)
अणु
	काष्ठा bnxt_tc_l2_node *l2_node = flow_node->l2_node;
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	पूर्णांक rc;

	/* हटाओ flow_node from the L2 shared flow list */
	list_del(&flow_node->l2_list_node);
	अगर (--l2_node->refcount == 0) अणु
		rc =  rhashtable_हटाओ_fast(&tc_info->l2_table, &l2_node->node,
					     tc_info->l2_ht_params);
		अगर (rc)
			netdev_err(bp->dev,
				   "Error: %s: rhashtable_remove_fast: %d\n",
				   __func__, rc);
		kमुक्त_rcu(l2_node, rcu);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा bnxt_tc_l2_node *
bnxt_tc_get_l2_node(काष्ठा bnxt *bp, काष्ठा rhashtable *l2_table,
		    काष्ठा rhashtable_params ht_params,
		    काष्ठा bnxt_tc_l2_key *l2_key)
अणु
	काष्ठा bnxt_tc_l2_node *l2_node;
	पूर्णांक rc;

	l2_node = rhashtable_lookup_fast(l2_table, l2_key, ht_params);
	अगर (!l2_node) अणु
		l2_node = kzalloc(माप(*l2_node), GFP_KERNEL);
		अगर (!l2_node) अणु
			rc = -ENOMEM;
			वापस शून्य;
		पूर्ण

		l2_node->key = *l2_key;
		rc = rhashtable_insert_fast(l2_table, &l2_node->node,
					    ht_params);
		अगर (rc) अणु
			kमुक्त_rcu(l2_node, rcu);
			netdev_err(bp->dev,
				   "Error: %s: rhashtable_insert_fast: %d\n",
				   __func__, rc);
			वापस शून्य;
		पूर्ण
		INIT_LIST_HEAD(&l2_node->common_l2_flows);
	पूर्ण
	वापस l2_node;
पूर्ण

/* Get the ref_flow_handle क्रम a flow by checking अगर there are any other
 * flows that share the same L2 key as this flow.
 */
अटल पूर्णांक
bnxt_tc_get_ref_flow_handle(काष्ठा bnxt *bp, काष्ठा bnxt_tc_flow *flow,
			    काष्ठा bnxt_tc_flow_node *flow_node,
			    __le16 *ref_flow_handle)
अणु
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	काष्ठा bnxt_tc_flow_node *ref_flow_node;
	काष्ठा bnxt_tc_l2_node *l2_node;

	l2_node = bnxt_tc_get_l2_node(bp, &tc_info->l2_table,
				      tc_info->l2_ht_params,
				      &flow->l2_key);
	अगर (!l2_node)
		वापस -1;

	/* If any other flow is using this l2_node, use it's flow_handle
	 * as the ref_flow_handle
	 */
	अगर (l2_node->refcount > 0) अणु
		ref_flow_node = list_first_entry(&l2_node->common_l2_flows,
						 काष्ठा bnxt_tc_flow_node,
						 l2_list_node);
		*ref_flow_handle = ref_flow_node->flow_handle;
	पूर्ण अन्यथा अणु
		*ref_flow_handle = cpu_to_le16(0xffff);
	पूर्ण

	/* Insert the l2_node पूर्णांकo the flow_node so that subsequent flows
	 * with a matching l2 key can use the flow_handle of this flow
	 * as their ref_flow_handle
	 */
	flow_node->l2_node = l2_node;
	list_add(&flow_node->l2_list_node, &l2_node->common_l2_flows);
	l2_node->refcount++;
	वापस 0;
पूर्ण

/* After the flow parsing is करोne, this routine is used क्रम checking
 * अगर there are any aspects of the flow that prevent it from being
 * offloaded.
 */
अटल bool bnxt_tc_can_offload(काष्ठा bnxt *bp, काष्ठा bnxt_tc_flow *flow)
अणु
	/* If L4 ports are specअगरied then ip_proto must be TCP or UDP */
	अगर ((flow->flags & BNXT_TC_FLOW_FLAGS_PORTS) &&
	    (flow->l4_key.ip_proto != IPPROTO_TCP &&
	     flow->l4_key.ip_proto != IPPROTO_UDP)) अणु
		netdev_info(bp->dev, "Cannot offload non-TCP/UDP (%d) ports\n",
			    flow->l4_key.ip_proto);
		वापस false;
	पूर्ण

	/* Currently source/dest MAC cannot be partial wildcard  */
	अगर (bits_set(&flow->l2_key.smac, माप(flow->l2_key.smac)) &&
	    !is_exacपंचांगatch(flow->l2_mask.smac, माप(flow->l2_mask.smac))) अणु
		netdev_info(bp->dev, "Wildcard match unsupported for Source MAC\n");
		वापस false;
	पूर्ण
	अगर (bits_set(&flow->l2_key.dmac, माप(flow->l2_key.dmac)) &&
	    !is_exacपंचांगatch(&flow->l2_mask.dmac, माप(flow->l2_mask.dmac))) अणु
		netdev_info(bp->dev, "Wildcard match unsupported for Dest MAC\n");
		वापस false;
	पूर्ण

	/* Currently VLAN fields cannot be partial wildcard */
	अगर (bits_set(&flow->l2_key.inner_vlan_tci,
		     माप(flow->l2_key.inner_vlan_tci)) &&
	    !is_vlan_tci_allowed(flow->l2_mask.inner_vlan_tci,
				 flow->l2_key.inner_vlan_tci)) अणु
		netdev_info(bp->dev, "Unsupported VLAN TCI\n");
		वापस false;
	पूर्ण
	अगर (bits_set(&flow->l2_key.inner_vlan_tpid,
		     माप(flow->l2_key.inner_vlan_tpid)) &&
	    !is_exacपंचांगatch(&flow->l2_mask.inner_vlan_tpid,
			   माप(flow->l2_mask.inner_vlan_tpid))) अणु
		netdev_info(bp->dev, "Wildcard match unsupported for VLAN TPID\n");
		वापस false;
	पूर्ण

	/* Currently Ethertype must be set */
	अगर (!is_exacपंचांगatch(&flow->l2_mask.ether_type,
			   माप(flow->l2_mask.ether_type))) अणु
		netdev_info(bp->dev, "Wildcard match unsupported for Ethertype\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Returns the final refcount of the node on success
 * or a -ve error code on failure
 */
अटल पूर्णांक bnxt_tc_put_tunnel_node(काष्ठा bnxt *bp,
				   काष्ठा rhashtable *tunnel_table,
				   काष्ठा rhashtable_params *ht_params,
				   काष्ठा bnxt_tc_tunnel_node *tunnel_node)
अणु
	पूर्णांक rc;

	अगर (--tunnel_node->refcount == 0) अणु
		rc =  rhashtable_हटाओ_fast(tunnel_table, &tunnel_node->node,
					     *ht_params);
		अगर (rc) अणु
			netdev_err(bp->dev, "rhashtable_remove_fast rc=%d\n", rc);
			rc = -1;
		पूर्ण
		kमुक्त_rcu(tunnel_node, rcu);
		वापस rc;
	पूर्ण अन्यथा अणु
		वापस tunnel_node->refcount;
	पूर्ण
पूर्ण

/* Get (or add) either encap or decap tunnel node from/to the supplied
 * hash table.
 */
अटल काष्ठा bnxt_tc_tunnel_node *
bnxt_tc_get_tunnel_node(काष्ठा bnxt *bp, काष्ठा rhashtable *tunnel_table,
			काष्ठा rhashtable_params *ht_params,
			काष्ठा ip_tunnel_key *tun_key)
अणु
	काष्ठा bnxt_tc_tunnel_node *tunnel_node;
	पूर्णांक rc;

	tunnel_node = rhashtable_lookup_fast(tunnel_table, tun_key, *ht_params);
	अगर (!tunnel_node) अणु
		tunnel_node = kzalloc(माप(*tunnel_node), GFP_KERNEL);
		अगर (!tunnel_node) अणु
			rc = -ENOMEM;
			जाओ err;
		पूर्ण

		tunnel_node->key = *tun_key;
		tunnel_node->tunnel_handle = INVALID_TUNNEL_HANDLE;
		rc = rhashtable_insert_fast(tunnel_table, &tunnel_node->node,
					    *ht_params);
		अगर (rc) अणु
			kमुक्त_rcu(tunnel_node, rcu);
			जाओ err;
		पूर्ण
	पूर्ण
	tunnel_node->refcount++;
	वापस tunnel_node;
err:
	netdev_info(bp->dev, "error rc=%d\n", rc);
	वापस शून्य;
पूर्ण

अटल पूर्णांक bnxt_tc_get_ref_decap_handle(काष्ठा bnxt *bp,
					काष्ठा bnxt_tc_flow *flow,
					काष्ठा bnxt_tc_l2_key *l2_key,
					काष्ठा bnxt_tc_flow_node *flow_node,
					__le32 *ref_decap_handle)
अणु
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	काष्ठा bnxt_tc_flow_node *ref_flow_node;
	काष्ठा bnxt_tc_l2_node *decap_l2_node;

	decap_l2_node = bnxt_tc_get_l2_node(bp, &tc_info->decap_l2_table,
					    tc_info->decap_l2_ht_params,
					    l2_key);
	अगर (!decap_l2_node)
		वापस -1;

	/* If any other flow is using this decap_l2_node, use it's decap_handle
	 * as the ref_decap_handle
	 */
	अगर (decap_l2_node->refcount > 0) अणु
		ref_flow_node =
			list_first_entry(&decap_l2_node->common_l2_flows,
					 काष्ठा bnxt_tc_flow_node,
					 decap_l2_list_node);
		*ref_decap_handle = ref_flow_node->decap_node->tunnel_handle;
	पूर्ण अन्यथा अणु
		*ref_decap_handle = INVALID_TUNNEL_HANDLE;
	पूर्ण

	/* Insert the l2_node पूर्णांकo the flow_node so that subsequent flows
	 * with a matching decap l2 key can use the decap_filter_handle of
	 * this flow as their ref_decap_handle
	 */
	flow_node->decap_l2_node = decap_l2_node;
	list_add(&flow_node->decap_l2_list_node,
		 &decap_l2_node->common_l2_flows);
	decap_l2_node->refcount++;
	वापस 0;
पूर्ण

अटल व्योम bnxt_tc_put_decap_l2_node(काष्ठा bnxt *bp,
				      काष्ठा bnxt_tc_flow_node *flow_node)
अणु
	काष्ठा bnxt_tc_l2_node *decap_l2_node = flow_node->decap_l2_node;
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	पूर्णांक rc;

	/* हटाओ flow_node from the decap L2 sharing flow list */
	list_del(&flow_node->decap_l2_list_node);
	अगर (--decap_l2_node->refcount == 0) अणु
		rc =  rhashtable_हटाओ_fast(&tc_info->decap_l2_table,
					     &decap_l2_node->node,
					     tc_info->decap_l2_ht_params);
		अगर (rc)
			netdev_err(bp->dev, "rhashtable_remove_fast rc=%d\n", rc);
		kमुक्त_rcu(decap_l2_node, rcu);
	पूर्ण
पूर्ण

अटल व्योम bnxt_tc_put_decap_handle(काष्ठा bnxt *bp,
				     काष्ठा bnxt_tc_flow_node *flow_node)
अणु
	__le32 decap_handle = flow_node->decap_node->tunnel_handle;
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	पूर्णांक rc;

	अगर (flow_node->decap_l2_node)
		bnxt_tc_put_decap_l2_node(bp, flow_node);

	rc = bnxt_tc_put_tunnel_node(bp, &tc_info->decap_table,
				     &tc_info->decap_ht_params,
				     flow_node->decap_node);
	अगर (!rc && decap_handle != INVALID_TUNNEL_HANDLE)
		hwrm_cfa_decap_filter_मुक्त(bp, decap_handle);
पूर्ण

अटल पूर्णांक bnxt_tc_resolve_tunnel_hdrs(काष्ठा bnxt *bp,
				       काष्ठा ip_tunnel_key *tun_key,
				       काष्ठा bnxt_tc_l2_key *l2_info)
अणु
#अगर_घोषित CONFIG_INET
	काष्ठा net_device *real_dst_dev = bp->dev;
	काष्ठा flowi4 flow = अणु अणु0पूर्ण पूर्ण;
	काष्ठा net_device *dst_dev;
	काष्ठा neighbour *nbr;
	काष्ठा rtable *rt;
	पूर्णांक rc;

	flow.flowi4_proto = IPPROTO_UDP;
	flow.fl4_dport = tun_key->tp_dst;
	flow.daddr = tun_key->u.ipv4.dst;

	rt = ip_route_output_key(dev_net(real_dst_dev), &flow);
	अगर (IS_ERR(rt)) अणु
		netdev_info(bp->dev, "no route to %pI4b\n", &flow.daddr);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* The route must either poपूर्णांक to the real_dst_dev or a dst_dev that
	 * uses the real_dst_dev.
	 */
	dst_dev = rt->dst.dev;
	अगर (is_vlan_dev(dst_dev)) अणु
#अगर IS_ENABLED(CONFIG_VLAN_8021Q)
		काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dst_dev);

		अगर (vlan->real_dev != real_dst_dev) अणु
			netdev_info(bp->dev,
				    "dst_dev(%s) doesn't use PF-if(%s)\n",
				    netdev_name(dst_dev),
				    netdev_name(real_dst_dev));
			rc = -EOPNOTSUPP;
			जाओ put_rt;
		पूर्ण
		l2_info->inner_vlan_tci = htons(vlan->vlan_id);
		l2_info->inner_vlan_tpid = vlan->vlan_proto;
		l2_info->num_vlans = 1;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (dst_dev != real_dst_dev) अणु
		netdev_info(bp->dev,
			    "dst_dev(%s) for %pI4b is not PF-if(%s)\n",
			    netdev_name(dst_dev), &flow.daddr,
			    netdev_name(real_dst_dev));
		rc = -EOPNOTSUPP;
		जाओ put_rt;
	पूर्ण

	nbr = dst_neigh_lookup(&rt->dst, &flow.daddr);
	अगर (!nbr) अणु
		netdev_info(bp->dev, "can't lookup neighbor for %pI4b\n",
			    &flow.daddr);
		rc = -EOPNOTSUPP;
		जाओ put_rt;
	पूर्ण

	tun_key->u.ipv4.src = flow.saddr;
	tun_key->ttl = ip4_dst_hoplimit(&rt->dst);
	neigh_ha_snapshot(l2_info->dmac, nbr, dst_dev);
	ether_addr_copy(l2_info->smac, dst_dev->dev_addr);
	neigh_release(nbr);
	ip_rt_put(rt);

	वापस 0;
put_rt:
	ip_rt_put(rt);
	वापस rc;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक bnxt_tc_get_decap_handle(काष्ठा bnxt *bp, काष्ठा bnxt_tc_flow *flow,
				    काष्ठा bnxt_tc_flow_node *flow_node,
				    __le32 *decap_filter_handle)
अणु
	काष्ठा ip_tunnel_key *decap_key = &flow->tun_key;
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	काष्ठा bnxt_tc_l2_key l2_info = अणु अणु0पूर्ण पूर्ण;
	काष्ठा bnxt_tc_tunnel_node *decap_node;
	काष्ठा ip_tunnel_key tun_key = अणु 0 पूर्ण;
	काष्ठा bnxt_tc_l2_key *decap_l2_info;
	__le32 ref_decap_handle;
	पूर्णांक rc;

	/* Check अगर there's another flow using the same tunnel decap.
	 * If not, add this tunnel to the table and resolve the other
	 * tunnel header fileds. Ignore src_port in the tunnel_key,
	 * since it is not required क्रम decap filters.
	 */
	decap_key->tp_src = 0;
	decap_node = bnxt_tc_get_tunnel_node(bp, &tc_info->decap_table,
					     &tc_info->decap_ht_params,
					     decap_key);
	अगर (!decap_node)
		वापस -ENOMEM;

	flow_node->decap_node = decap_node;

	अगर (decap_node->tunnel_handle != INVALID_TUNNEL_HANDLE)
		जाओ करोne;

	/* Resolve the L2 fields क्रम tunnel decap
	 * Resolve the route क्रम remote vtep (saddr) of the decap key
	 * Find it's next-hop mac addrs
	 */
	tun_key.u.ipv4.dst = flow->tun_key.u.ipv4.src;
	tun_key.tp_dst = flow->tun_key.tp_dst;
	rc = bnxt_tc_resolve_tunnel_hdrs(bp, &tun_key, &l2_info);
	अगर (rc)
		जाओ put_decap;

	decap_l2_info = &decap_node->l2_info;
	/* decap smac is wildcarded */
	ether_addr_copy(decap_l2_info->dmac, l2_info.smac);
	अगर (l2_info.num_vlans) अणु
		decap_l2_info->num_vlans = l2_info.num_vlans;
		decap_l2_info->inner_vlan_tpid = l2_info.inner_vlan_tpid;
		decap_l2_info->inner_vlan_tci = l2_info.inner_vlan_tci;
	पूर्ण
	flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_ETH_ADDRS;

	/* For getting a decap_filter_handle we first need to check अगर
	 * there are any other decap flows that share the same tunnel L2
	 * key and अगर so, pass that flow's decap_filter_handle as the
	 * ref_decap_handle क्रम this flow.
	 */
	rc = bnxt_tc_get_ref_decap_handle(bp, flow, decap_l2_info, flow_node,
					  &ref_decap_handle);
	अगर (rc)
		जाओ put_decap;

	/* Issue the hwrm cmd to allocate a decap filter handle */
	rc = hwrm_cfa_decap_filter_alloc(bp, flow, decap_l2_info,
					 ref_decap_handle,
					 &decap_node->tunnel_handle);
	अगर (rc)
		जाओ put_decap_l2;

करोne:
	*decap_filter_handle = decap_node->tunnel_handle;
	वापस 0;

put_decap_l2:
	bnxt_tc_put_decap_l2_node(bp, flow_node);
put_decap:
	bnxt_tc_put_tunnel_node(bp, &tc_info->decap_table,
				&tc_info->decap_ht_params,
				flow_node->decap_node);
	वापस rc;
पूर्ण

अटल व्योम bnxt_tc_put_encap_handle(काष्ठा bnxt *bp,
				     काष्ठा bnxt_tc_tunnel_node *encap_node)
अणु
	__le32 encap_handle = encap_node->tunnel_handle;
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	पूर्णांक rc;

	rc = bnxt_tc_put_tunnel_node(bp, &tc_info->encap_table,
				     &tc_info->encap_ht_params, encap_node);
	अगर (!rc && encap_handle != INVALID_TUNNEL_HANDLE)
		hwrm_cfa_encap_record_मुक्त(bp, encap_handle);
पूर्ण

/* Lookup the tunnel encap table and check अगर there's an encap_handle
 * alloc'd alपढ़ोy.
 * If not, query L2 info via a route lookup and issue an encap_record_alloc
 * cmd to FW.
 */
अटल पूर्णांक bnxt_tc_get_encap_handle(काष्ठा bnxt *bp, काष्ठा bnxt_tc_flow *flow,
				    काष्ठा bnxt_tc_flow_node *flow_node,
				    __le32 *encap_handle)
अणु
	काष्ठा ip_tunnel_key *encap_key = &flow->actions.tun_encap_key;
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	काष्ठा bnxt_tc_tunnel_node *encap_node;
	पूर्णांक rc;

	/* Check अगर there's another flow using the same tunnel encap.
	 * If not, add this tunnel to the table and resolve the other
	 * tunnel header fileds
	 */
	encap_node = bnxt_tc_get_tunnel_node(bp, &tc_info->encap_table,
					     &tc_info->encap_ht_params,
					     encap_key);
	अगर (!encap_node)
		वापस -ENOMEM;

	flow_node->encap_node = encap_node;

	अगर (encap_node->tunnel_handle != INVALID_TUNNEL_HANDLE)
		जाओ करोne;

	rc = bnxt_tc_resolve_tunnel_hdrs(bp, encap_key, &encap_node->l2_info);
	अगर (rc)
		जाओ put_encap;

	/* Allocate a new tunnel encap record */
	rc = hwrm_cfa_encap_record_alloc(bp, encap_key, &encap_node->l2_info,
					 &encap_node->tunnel_handle);
	अगर (rc)
		जाओ put_encap;

करोne:
	*encap_handle = encap_node->tunnel_handle;
	वापस 0;

put_encap:
	bnxt_tc_put_tunnel_node(bp, &tc_info->encap_table,
				&tc_info->encap_ht_params, encap_node);
	वापस rc;
पूर्ण

अटल व्योम bnxt_tc_put_tunnel_handle(काष्ठा bnxt *bp,
				      काष्ठा bnxt_tc_flow *flow,
				      काष्ठा bnxt_tc_flow_node *flow_node)
अणु
	अगर (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_DECAP)
		bnxt_tc_put_decap_handle(bp, flow_node);
	अन्यथा अगर (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP)
		bnxt_tc_put_encap_handle(bp, flow_node->encap_node);
पूर्ण

अटल पूर्णांक bnxt_tc_get_tunnel_handle(काष्ठा bnxt *bp,
				     काष्ठा bnxt_tc_flow *flow,
				     काष्ठा bnxt_tc_flow_node *flow_node,
				     __le32 *tunnel_handle)
अणु
	अगर (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_DECAP)
		वापस bnxt_tc_get_decap_handle(bp, flow, flow_node,
						tunnel_handle);
	अन्यथा अगर (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_ENCAP)
		वापस bnxt_tc_get_encap_handle(bp, flow, flow_node,
						tunnel_handle);
	अन्यथा
		वापस 0;
पूर्ण
अटल पूर्णांक __bnxt_tc_del_flow(काष्ठा bnxt *bp,
			      काष्ठा bnxt_tc_flow_node *flow_node)
अणु
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	पूर्णांक rc;

	/* send HWRM cmd to मुक्त the flow-id */
	bnxt_hwrm_cfa_flow_मुक्त(bp, flow_node);

	mutex_lock(&tc_info->lock);

	/* release references to any tunnel encap/decap nodes */
	bnxt_tc_put_tunnel_handle(bp, &flow_node->flow, flow_node);

	/* release reference to l2 node */
	bnxt_tc_put_l2_node(bp, flow_node);

	mutex_unlock(&tc_info->lock);

	rc = rhashtable_हटाओ_fast(&tc_info->flow_table, &flow_node->node,
				    tc_info->flow_ht_params);
	अगर (rc)
		netdev_err(bp->dev, "Error: %s: rhashtable_remove_fast rc=%d\n",
			   __func__, rc);

	kमुक्त_rcu(flow_node, rcu);
	वापस 0;
पूर्ण

अटल व्योम bnxt_tc_set_flow_dir(काष्ठा bnxt *bp, काष्ठा bnxt_tc_flow *flow,
				 u16 src_fid)
अणु
	flow->l2_key.dir = (bp->pf.fw_fid == src_fid) ? BNXT_सूची_RX : BNXT_सूची_TX;
पूर्ण

अटल व्योम bnxt_tc_set_src_fid(काष्ठा bnxt *bp, काष्ठा bnxt_tc_flow *flow,
				u16 src_fid)
अणु
	अगर (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_DECAP)
		flow->src_fid = bp->pf.fw_fid;
	अन्यथा
		flow->src_fid = src_fid;
पूर्ण

/* Add a new flow or replace an existing flow.
 * Notes on locking:
 * There are essentially two critical sections here.
 * 1. जबतक adding a new flow
 *    a) lookup l2-key
 *    b) issue HWRM cmd and get flow_handle
 *    c) link l2-key with flow
 * 2. जबतक deleting a flow
 *    a) unlinking l2-key from flow
 * A lock is needed to protect these two critical sections.
 *
 * The hash-tables are alपढ़ोy रक्षित by the rhashtable API.
 */
अटल पूर्णांक bnxt_tc_add_flow(काष्ठा bnxt *bp, u16 src_fid,
			    काष्ठा flow_cls_offload *tc_flow_cmd)
अणु
	काष्ठा bnxt_tc_flow_node *new_node, *old_node;
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	काष्ठा bnxt_tc_flow *flow;
	__le32 tunnel_handle = 0;
	__le16 ref_flow_handle;
	पूर्णांक rc;

	/* allocate memory क्रम the new flow and it's node */
	new_node = kzalloc(माप(*new_node), GFP_KERNEL);
	अगर (!new_node) अणु
		rc = -ENOMEM;
		जाओ करोne;
	पूर्ण
	new_node->cookie = tc_flow_cmd->cookie;
	flow = &new_node->flow;

	rc = bnxt_tc_parse_flow(bp, tc_flow_cmd, flow);
	अगर (rc)
		जाओ मुक्त_node;

	bnxt_tc_set_src_fid(bp, flow, src_fid);
	bnxt_tc_set_flow_dir(bp, flow, flow->src_fid);

	अगर (!bnxt_tc_can_offload(bp, flow)) अणु
		rc = -EOPNOTSUPP;
		kमुक्त_rcu(new_node, rcu);
		वापस rc;
	पूर्ण

	/* If a flow exists with the same cookie, delete it */
	old_node = rhashtable_lookup_fast(&tc_info->flow_table,
					  &tc_flow_cmd->cookie,
					  tc_info->flow_ht_params);
	अगर (old_node)
		__bnxt_tc_del_flow(bp, old_node);

	/* Check अगर the L2 part of the flow has been offloaded alपढ़ोy.
	 * If so, bump up it's refcnt and get it's reference handle.
	 */
	mutex_lock(&tc_info->lock);
	rc = bnxt_tc_get_ref_flow_handle(bp, flow, new_node, &ref_flow_handle);
	अगर (rc)
		जाओ unlock;

	/* If the flow involves tunnel encap/decap, get tunnel_handle */
	rc = bnxt_tc_get_tunnel_handle(bp, flow, new_node, &tunnel_handle);
	अगर (rc)
		जाओ put_l2;

	/* send HWRM cmd to alloc the flow */
	rc = bnxt_hwrm_cfa_flow_alloc(bp, flow, ref_flow_handle,
				      tunnel_handle, new_node);
	अगर (rc)
		जाओ put_tunnel;

	flow->lastused = jअगरfies;
	spin_lock_init(&flow->stats_lock);
	/* add new flow to flow-table */
	rc = rhashtable_insert_fast(&tc_info->flow_table, &new_node->node,
				    tc_info->flow_ht_params);
	अगर (rc)
		जाओ hwrm_flow_मुक्त;

	mutex_unlock(&tc_info->lock);
	वापस 0;

hwrm_flow_मुक्त:
	bnxt_hwrm_cfa_flow_मुक्त(bp, new_node);
put_tunnel:
	bnxt_tc_put_tunnel_handle(bp, flow, new_node);
put_l2:
	bnxt_tc_put_l2_node(bp, new_node);
unlock:
	mutex_unlock(&tc_info->lock);
मुक्त_node:
	kमुक्त_rcu(new_node, rcu);
करोne:
	netdev_err(bp->dev, "Error: %s: cookie=0x%lx error=%d\n",
		   __func__, tc_flow_cmd->cookie, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_tc_del_flow(काष्ठा bnxt *bp,
			    काष्ठा flow_cls_offload *tc_flow_cmd)
अणु
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	काष्ठा bnxt_tc_flow_node *flow_node;

	flow_node = rhashtable_lookup_fast(&tc_info->flow_table,
					   &tc_flow_cmd->cookie,
					   tc_info->flow_ht_params);
	अगर (!flow_node)
		वापस -EINVAL;

	वापस __bnxt_tc_del_flow(bp, flow_node);
पूर्ण

अटल पूर्णांक bnxt_tc_get_flow_stats(काष्ठा bnxt *bp,
				  काष्ठा flow_cls_offload *tc_flow_cmd)
अणु
	काष्ठा bnxt_tc_flow_stats stats, *curr_stats, *prev_stats;
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	काष्ठा bnxt_tc_flow_node *flow_node;
	काष्ठा bnxt_tc_flow *flow;
	अचिन्हित दीर्घ lastused;

	flow_node = rhashtable_lookup_fast(&tc_info->flow_table,
					   &tc_flow_cmd->cookie,
					   tc_info->flow_ht_params);
	अगर (!flow_node)
		वापस -1;

	flow = &flow_node->flow;
	curr_stats = &flow->stats;
	prev_stats = &flow->prev_stats;

	spin_lock(&flow->stats_lock);
	stats.packets = curr_stats->packets - prev_stats->packets;
	stats.bytes = curr_stats->bytes - prev_stats->bytes;
	*prev_stats = *curr_stats;
	lastused = flow->lastused;
	spin_unlock(&flow->stats_lock);

	flow_stats_update(&tc_flow_cmd->stats, stats.bytes, stats.packets, 0,
			  lastused, FLOW_ACTION_HW_STATS_DELAYED);
	वापस 0;
पूर्ण

अटल व्योम bnxt_fill_cfa_stats_req(काष्ठा bnxt *bp,
				    काष्ठा bnxt_tc_flow_node *flow_node,
				    __le16 *flow_handle, __le32 *flow_id)
अणु
	u16 handle;

	अगर (bp->fw_cap & BNXT_FW_CAP_OVS_64BIT_HANDLE) अणु
		*flow_id = flow_node->flow_id;

		/* If flow_id is used to fetch flow stats then:
		 * 1. lower 12 bits of flow_handle must be set to all 1s.
		 * 2. 15th bit of flow_handle must specअगरy the flow
		 *    direction (TX/RX).
		 */
		अगर (flow_node->flow.l2_key.dir == BNXT_सूची_RX)
			handle = CFA_FLOW_INFO_REQ_FLOW_HANDLE_सूची_RX |
				 CFA_FLOW_INFO_REQ_FLOW_HANDLE_MAX_MASK;
		अन्यथा
			handle = CFA_FLOW_INFO_REQ_FLOW_HANDLE_MAX_MASK;

		*flow_handle = cpu_to_le16(handle);
	पूर्ण अन्यथा अणु
		*flow_handle = flow_node->flow_handle;
	पूर्ण
पूर्ण

अटल पूर्णांक
bnxt_hwrm_cfa_flow_stats_get(काष्ठा bnxt *bp, पूर्णांक num_flows,
			     काष्ठा bnxt_tc_stats_batch stats_batch[])
अणु
	काष्ठा hwrm_cfa_flow_stats_input req = अणु 0 पूर्ण;
	काष्ठा hwrm_cfa_flow_stats_output *resp;
	__le16 *req_flow_handles = &req.flow_handle_0;
	__le32 *req_flow_ids = &req.flow_id_0;
	पूर्णांक rc, i;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_FLOW_STATS, -1, -1);
	req.num_flows = cpu_to_le16(num_flows);
	क्रम (i = 0; i < num_flows; i++) अणु
		काष्ठा bnxt_tc_flow_node *flow_node = stats_batch[i].flow_node;

		bnxt_fill_cfa_stats_req(bp, flow_node,
					&req_flow_handles[i], &req_flow_ids[i]);
	पूर्ण

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, माप(req), HWRM_CMD_TIMEOUT);
	अगर (!rc) अणु
		__le64 *resp_packets;
		__le64 *resp_bytes;

		resp = bnxt_get_hwrm_resp_addr(bp, &req);
		resp_packets = &resp->packet_0;
		resp_bytes = &resp->byte_0;

		क्रम (i = 0; i < num_flows; i++) अणु
			stats_batch[i].hw_stats.packets =
						le64_to_cpu(resp_packets[i]);
			stats_batch[i].hw_stats.bytes =
						le64_to_cpu(resp_bytes[i]);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_info(bp->dev, "error rc=%d\n", rc);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);

	वापस rc;
पूर्ण

/* Add val to accum जबतक handling a possible wraparound
 * of val. Eventhough val is of type u64, its actual width
 * is denoted by mask and will wrap-around beyond that width.
 */
अटल व्योम accumulate_val(u64 *accum, u64 val, u64 mask)
अणु
#घोषणा low_bits(x, mask)		((x) & (mask))
#घोषणा high_bits(x, mask)		((x) & ~(mask))
	bool wrapped = val < low_bits(*accum, mask);

	*accum = high_bits(*accum, mask) + val;
	अगर (wrapped)
		*accum += (mask + 1);
पूर्ण

/* The HW counters' width is much less than 64bits.
 * Handle possible wrap-around जबतक updating the stat counters
 */
अटल व्योम bnxt_flow_stats_accum(काष्ठा bnxt_tc_info *tc_info,
				  काष्ठा bnxt_tc_flow_stats *acc_stats,
				  काष्ठा bnxt_tc_flow_stats *hw_stats)
अणु
	accumulate_val(&acc_stats->bytes, hw_stats->bytes, tc_info->bytes_mask);
	accumulate_val(&acc_stats->packets, hw_stats->packets,
		       tc_info->packets_mask);
पूर्ण

अटल पूर्णांक
bnxt_tc_flow_stats_batch_update(काष्ठा bnxt *bp, पूर्णांक num_flows,
				काष्ठा bnxt_tc_stats_batch stats_batch[])
अणु
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	पूर्णांक rc, i;

	rc = bnxt_hwrm_cfa_flow_stats_get(bp, num_flows, stats_batch);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < num_flows; i++) अणु
		काष्ठा bnxt_tc_flow_node *flow_node = stats_batch[i].flow_node;
		काष्ठा bnxt_tc_flow *flow = &flow_node->flow;

		spin_lock(&flow->stats_lock);
		bnxt_flow_stats_accum(tc_info, &flow->stats,
				      &stats_batch[i].hw_stats);
		अगर (flow->stats.packets != flow->prev_stats.packets)
			flow->lastused = jअगरfies;
		spin_unlock(&flow->stats_lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
bnxt_tc_flow_stats_batch_prep(काष्ठा bnxt *bp,
			      काष्ठा bnxt_tc_stats_batch stats_batch[],
			      पूर्णांक *num_flows)
अणु
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	काष्ठा rhashtable_iter *iter = &tc_info->iter;
	व्योम *flow_node;
	पूर्णांक rc, i;

	rhashtable_walk_start(iter);

	rc = 0;
	क्रम (i = 0; i < BNXT_FLOW_STATS_BATCH_MAX; i++) अणु
		flow_node = rhashtable_walk_next(iter);
		अगर (IS_ERR(flow_node)) अणु
			i = 0;
			अगर (PTR_ERR(flow_node) == -EAGAIN) अणु
				जारी;
			पूर्ण अन्यथा अणु
				rc = PTR_ERR(flow_node);
				जाओ करोne;
			पूर्ण
		पूर्ण

		/* No more flows */
		अगर (!flow_node)
			जाओ करोne;

		stats_batch[i].flow_node = flow_node;
	पूर्ण
करोne:
	rhashtable_walk_stop(iter);
	*num_flows = i;
	वापस rc;
पूर्ण

व्योम bnxt_tc_flow_stats_work(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;
	पूर्णांक num_flows, rc;

	num_flows = atomic_पढ़ो(&tc_info->flow_table.nelems);
	अगर (!num_flows)
		वापस;

	rhashtable_walk_enter(&tc_info->flow_table, &tc_info->iter);

	क्रम (;;) अणु
		rc = bnxt_tc_flow_stats_batch_prep(bp, tc_info->stats_batch,
						   &num_flows);
		अगर (rc) अणु
			अगर (rc == -EAGAIN)
				जारी;
			अवरोध;
		पूर्ण

		अगर (!num_flows)
			अवरोध;

		bnxt_tc_flow_stats_batch_update(bp, num_flows,
						tc_info->stats_batch);
	पूर्ण

	rhashtable_walk_निकास(&tc_info->iter);
पूर्ण

पूर्णांक bnxt_tc_setup_flower(काष्ठा bnxt *bp, u16 src_fid,
			 काष्ठा flow_cls_offload *cls_flower)
अणु
	चयन (cls_flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस bnxt_tc_add_flow(bp, src_fid, cls_flower);
	हाल FLOW_CLS_DESTROY:
		वापस bnxt_tc_del_flow(bp, cls_flower);
	हाल FLOW_CLS_STATS:
		वापस bnxt_tc_get_flow_stats(bp, cls_flower);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_tc_setup_indr_block_cb(क्रमागत tc_setup_type type,
				       व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा bnxt_flower_indr_block_cb_priv *priv = cb_priv;
	काष्ठा flow_cls_offload *flower = type_data;
	काष्ठा bnxt *bp = priv->bp;

	अगर (flower->common.chain_index)
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस bnxt_tc_setup_flower(bp, bp->pf.fw_fid, flower);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल काष्ठा bnxt_flower_indr_block_cb_priv *
bnxt_tc_indr_block_cb_lookup(काष्ठा bnxt *bp, काष्ठा net_device *netdev)
अणु
	काष्ठा bnxt_flower_indr_block_cb_priv *cb_priv;

	/* All callback list access should be रक्षित by RTNL. */
	ASSERT_RTNL();

	list_क्रम_each_entry(cb_priv, &bp->tc_indr_block_list, list)
		अगर (cb_priv->tunnel_netdev == netdev)
			वापस cb_priv;

	वापस शून्य;
पूर्ण

अटल व्योम bnxt_tc_setup_indr_rel(व्योम *cb_priv)
अणु
	काष्ठा bnxt_flower_indr_block_cb_priv *priv = cb_priv;

	list_del(&priv->list);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक bnxt_tc_setup_indr_block(काष्ठा net_device *netdev, काष्ठा Qdisc *sch, काष्ठा bnxt *bp,
				    काष्ठा flow_block_offload *f, व्योम *data,
				    व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb))
अणु
	काष्ठा bnxt_flower_indr_block_cb_priv *cb_priv;
	काष्ठा flow_block_cb *block_cb;

	अगर (f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		वापस -EOPNOTSUPP;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		cb_priv = kदो_स्मृति(माप(*cb_priv), GFP_KERNEL);
		अगर (!cb_priv)
			वापस -ENOMEM;

		cb_priv->tunnel_netdev = netdev;
		cb_priv->bp = bp;
		list_add(&cb_priv->list, &bp->tc_indr_block_list);

		block_cb = flow_indr_block_cb_alloc(bnxt_tc_setup_indr_block_cb,
						    cb_priv, cb_priv,
						    bnxt_tc_setup_indr_rel, f,
						    netdev, sch, data, bp, cleanup);
		अगर (IS_ERR(block_cb)) अणु
			list_del(&cb_priv->list);
			kमुक्त(cb_priv);
			वापस PTR_ERR(block_cb);
		पूर्ण

		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &bnxt_block_cb_list);
		अवरोध;
	हाल FLOW_BLOCK_UNBIND:
		cb_priv = bnxt_tc_indr_block_cb_lookup(bp, netdev);
		अगर (!cb_priv)
			वापस -ENOENT;

		block_cb = flow_block_cb_lookup(f->block,
						bnxt_tc_setup_indr_block_cb,
						cb_priv);
		अगर (!block_cb)
			वापस -ENOENT;

		flow_indr_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool bnxt_is_netdev_indr_offload(काष्ठा net_device *netdev)
अणु
	वापस netअगर_is_vxlan(netdev);
पूर्ण

अटल पूर्णांक bnxt_tc_setup_indr_cb(काष्ठा net_device *netdev, काष्ठा Qdisc *sch, व्योम *cb_priv,
				 क्रमागत tc_setup_type type, व्योम *type_data,
				 व्योम *data,
				 व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb))
अणु
	अगर (!bnxt_is_netdev_indr_offload(netdev))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस bnxt_tc_setup_indr_block(netdev, sch, cb_priv, type_data, data, cleanup);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params bnxt_tc_flow_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा bnxt_tc_flow_node, node),
	.key_offset = दुरत्व(काष्ठा bnxt_tc_flow_node, cookie),
	.key_len = माप(((काष्ठा bnxt_tc_flow_node *)0)->cookie),
	.स्वतःmatic_shrinking = true
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params bnxt_tc_l2_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा bnxt_tc_l2_node, node),
	.key_offset = दुरत्व(काष्ठा bnxt_tc_l2_node, key),
	.key_len = BNXT_TC_L2_KEY_LEN,
	.स्वतःmatic_shrinking = true
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params bnxt_tc_decap_l2_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा bnxt_tc_l2_node, node),
	.key_offset = दुरत्व(काष्ठा bnxt_tc_l2_node, key),
	.key_len = BNXT_TC_L2_KEY_LEN,
	.स्वतःmatic_shrinking = true
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params bnxt_tc_tunnel_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा bnxt_tc_tunnel_node, node),
	.key_offset = दुरत्व(काष्ठा bnxt_tc_tunnel_node, key),
	.key_len = माप(काष्ठा ip_tunnel_key),
	.स्वतःmatic_shrinking = true
पूर्ण;

/* convert counter width in bits to a mask */
#घोषणा mask(width)		((u64)~0 >> (64 - (width)))

पूर्णांक bnxt_init_tc(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_tc_info *tc_info;
	पूर्णांक rc;

	अगर (bp->hwrm_spec_code < 0x10803)
		वापस 0;

	tc_info = kzalloc(माप(*tc_info), GFP_KERNEL);
	अगर (!tc_info)
		वापस -ENOMEM;
	mutex_init(&tc_info->lock);

	/* Counter widths are programmed by FW */
	tc_info->bytes_mask = mask(36);
	tc_info->packets_mask = mask(28);

	tc_info->flow_ht_params = bnxt_tc_flow_ht_params;
	rc = rhashtable_init(&tc_info->flow_table, &tc_info->flow_ht_params);
	अगर (rc)
		जाओ मुक्त_tc_info;

	tc_info->l2_ht_params = bnxt_tc_l2_ht_params;
	rc = rhashtable_init(&tc_info->l2_table, &tc_info->l2_ht_params);
	अगर (rc)
		जाओ destroy_flow_table;

	tc_info->decap_l2_ht_params = bnxt_tc_decap_l2_ht_params;
	rc = rhashtable_init(&tc_info->decap_l2_table,
			     &tc_info->decap_l2_ht_params);
	अगर (rc)
		जाओ destroy_l2_table;

	tc_info->decap_ht_params = bnxt_tc_tunnel_ht_params;
	rc = rhashtable_init(&tc_info->decap_table,
			     &tc_info->decap_ht_params);
	अगर (rc)
		जाओ destroy_decap_l2_table;

	tc_info->encap_ht_params = bnxt_tc_tunnel_ht_params;
	rc = rhashtable_init(&tc_info->encap_table,
			     &tc_info->encap_ht_params);
	अगर (rc)
		जाओ destroy_decap_table;

	tc_info->enabled = true;
	bp->dev->hw_features |= NETIF_F_HW_TC;
	bp->dev->features |= NETIF_F_HW_TC;
	bp->tc_info = tc_info;

	/* init indirect block notअगरications */
	INIT_LIST_HEAD(&bp->tc_indr_block_list);

	rc = flow_indr_dev_रेजिस्टर(bnxt_tc_setup_indr_cb, bp);
	अगर (!rc)
		वापस 0;

	rhashtable_destroy(&tc_info->encap_table);

destroy_decap_table:
	rhashtable_destroy(&tc_info->decap_table);
destroy_decap_l2_table:
	rhashtable_destroy(&tc_info->decap_l2_table);
destroy_l2_table:
	rhashtable_destroy(&tc_info->l2_table);
destroy_flow_table:
	rhashtable_destroy(&tc_info->flow_table);
मुक्त_tc_info:
	kमुक्त(tc_info);
	वापस rc;
पूर्ण

व्योम bnxt_shutकरोwn_tc(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_tc_info *tc_info = bp->tc_info;

	अगर (!bnxt_tc_flower_enabled(bp))
		वापस;

	flow_indr_dev_unरेजिस्टर(bnxt_tc_setup_indr_cb, bp,
				 bnxt_tc_setup_indr_rel);
	rhashtable_destroy(&tc_info->flow_table);
	rhashtable_destroy(&tc_info->l2_table);
	rhashtable_destroy(&tc_info->decap_l2_table);
	rhashtable_destroy(&tc_info->decap_table);
	rhashtable_destroy(&tc_info->encap_table);
	kमुक्त(tc_info);
	bp->tc_info = शून्य;
पूर्ण
