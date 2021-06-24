<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Physcial Function ethernet driver
 *
 * Copyright (C) 2021 Marvell.
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/bitfield.h>
#समावेश <net/flow_dissector.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_mirred.h>
#समावेश <net/tc_act/tc_vlan.h>
#समावेश <net/ipv6.h>

#समावेश "otx2_common.h"

/* Egress rate limiting definitions */
#घोषणा MAX_BURST_EXPONENT		0x0FULL
#घोषणा MAX_BURST_MANTISSA		0xFFULL
#घोषणा MAX_BURST_SIZE			130816ULL
#घोषणा MAX_RATE_DIVIDER_EXPONENT	12ULL
#घोषणा MAX_RATE_EXPONENT		0x0FULL
#घोषणा MAX_RATE_MANTISSA		0xFFULL

/* Bitfields in NIX_TLX_PIR रेजिस्टर */
#घोषणा TLX_RATE_MANTISSA		GENMASK_ULL(8, 1)
#घोषणा TLX_RATE_EXPONENT		GENMASK_ULL(12, 9)
#घोषणा TLX_RATE_DIVIDER_EXPONENT	GENMASK_ULL(16, 13)
#घोषणा TLX_BURST_MANTISSA		GENMASK_ULL(36, 29)
#घोषणा TLX_BURST_EXPONENT		GENMASK_ULL(40, 37)

काष्ठा otx2_tc_flow_stats अणु
	u64 bytes;
	u64 pkts;
	u64 used;
पूर्ण;

काष्ठा otx2_tc_flow अणु
	काष्ठा rhash_head		node;
	अचिन्हित दीर्घ			cookie;
	u16				entry;
	अचिन्हित पूर्णांक			bitpos;
	काष्ठा rcu_head			rcu;
	काष्ठा otx2_tc_flow_stats	stats;
	spinlock_t			lock; /* lock क्रम stats */
पूर्ण;

अटल व्योम otx2_get_egress_burst_cfg(u32 burst, u32 *burst_exp,
				      u32 *burst_mantissa)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/* Burst is calculated as
	 * ((256 + BURST_MANTISSA) << (1 + BURST_EXPONENT)) / 256
	 * Max supported burst size is 130,816 bytes.
	 */
	burst = min_t(u32, burst, MAX_BURST_SIZE);
	अगर (burst) अणु
		*burst_exp = ilog2(burst) ? ilog2(burst) - 1 : 0;
		पंचांगp = burst - roundकरोwn_घात_of_two(burst);
		अगर (burst < MAX_BURST_MANTISSA)
			*burst_mantissa = पंचांगp * 2;
		अन्यथा
			*burst_mantissa = पंचांगp / (1ULL << (*burst_exp - 7));
	पूर्ण अन्यथा अणु
		*burst_exp = MAX_BURST_EXPONENT;
		*burst_mantissa = MAX_BURST_MANTISSA;
	पूर्ण
पूर्ण

अटल व्योम otx2_get_egress_rate_cfg(u32 maxrate, u32 *exp,
				     u32 *mantissa, u32 *भाग_exp)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/* Rate calculation by hardware
	 *
	 * PIR_ADD = ((256 + mantissa) << exp) / 256
	 * rate = (2 * PIR_ADD) / ( 1 << भाग_exp)
	 * The resultant rate is in Mbps.
	 */

	/* 2Mbps to 100Gbps can be expressed with भाग_exp = 0.
	 * Setting this to '0' will ease the calculation of
	 * exponent and mantissa.
	 */
	*भाग_exp = 0;

	अगर (maxrate) अणु
		*exp = ilog2(maxrate) ? ilog2(maxrate) - 1 : 0;
		पंचांगp = maxrate - roundकरोwn_घात_of_two(maxrate);
		अगर (maxrate < MAX_RATE_MANTISSA)
			*mantissa = पंचांगp * 2;
		अन्यथा
			*mantissa = पंचांगp / (1ULL << (*exp - 7));
	पूर्ण अन्यथा अणु
		/* Instead of disabling rate limiting, set all values to max */
		*exp = MAX_RATE_EXPONENT;
		*mantissa = MAX_RATE_MANTISSA;
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_set_matchall_egress_rate(काष्ठा otx2_nic *nic, u32 burst, u32 maxrate)
अणु
	काष्ठा otx2_hw *hw = &nic->hw;
	काष्ठा nix_txschq_config *req;
	u32 burst_exp, burst_mantissa;
	u32 exp, mantissa, भाग_exp;
	पूर्णांक txschq, err;

	/* All SQs share the same TL4, so pick the first scheduler */
	txschq = hw->txschq_list[NIX_TXSCH_LVL_TL4][0];

	/* Get exponent and mantissa values from the desired rate */
	otx2_get_egress_burst_cfg(burst, &burst_exp, &burst_mantissa);
	otx2_get_egress_rate_cfg(maxrate, &exp, &mantissa, &भाग_exp);

	mutex_lock(&nic->mbox.lock);
	req = otx2_mbox_alloc_msg_nix_txschq_cfg(&nic->mbox);
	अगर (!req) अणु
		mutex_unlock(&nic->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->lvl = NIX_TXSCH_LVL_TL4;
	req->num_regs = 1;
	req->reg[0] = NIX_AF_TL4X_PIR(txschq);
	req->regval[0] = FIELD_PREP(TLX_BURST_EXPONENT, burst_exp) |
			 FIELD_PREP(TLX_BURST_MANTISSA, burst_mantissa) |
			 FIELD_PREP(TLX_RATE_DIVIDER_EXPONENT, भाग_exp) |
			 FIELD_PREP(TLX_RATE_EXPONENT, exp) |
			 FIELD_PREP(TLX_RATE_MANTISSA, mantissa) | BIT_ULL(0);

	err = otx2_sync_mbox_msg(&nic->mbox);
	mutex_unlock(&nic->mbox.lock);
	वापस err;
पूर्ण

अटल पूर्णांक otx2_tc_validate_flow(काष्ठा otx2_nic *nic,
				 काष्ठा flow_action *actions,
				 काष्ठा netlink_ext_ack *extack)
अणु
	अगर (nic->flags & OTX2_FLAG_INTF_DOWN) अणु
		NL_SET_ERR_MSG_MOD(extack, "Interface not initialized");
		वापस -EINVAL;
	पूर्ण

	अगर (!flow_action_has_entries(actions)) अणु
		NL_SET_ERR_MSG_MOD(extack, "MATCHALL offload called with no action");
		वापस -EINVAL;
	पूर्ण

	अगर (!flow_offload_has_one_action(actions)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Egress MATCHALL offload supports only 1 policing action");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक otx2_tc_egress_matchall_install(काष्ठा otx2_nic *nic,
					   काष्ठा tc_cls_matchall_offload *cls)
अणु
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा flow_action *actions = &cls->rule->action;
	काष्ठा flow_action_entry *entry;
	u32 rate;
	पूर्णांक err;

	err = otx2_tc_validate_flow(nic, actions, extack);
	अगर (err)
		वापस err;

	अगर (nic->flags & OTX2_FLAG_TC_MATCHALL_EGRESS_ENABLED) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Only one Egress MATCHALL ratelimiter can be offloaded");
		वापस -ENOMEM;
	पूर्ण

	entry = &cls->rule->action.entries[0];
	चयन (entry->id) अणु
	हाल FLOW_ACTION_POLICE:
		अगर (entry->police.rate_pkt_ps) अणु
			NL_SET_ERR_MSG_MOD(extack, "QoS offload not support packets per second");
			वापस -EOPNOTSUPP;
		पूर्ण
		/* Convert bytes per second to Mbps */
		rate = entry->police.rate_bytes_ps * 8;
		rate = max_t(u32, rate / 1000000, 1);
		err = otx2_set_matchall_egress_rate(nic, entry->police.burst, rate);
		अगर (err)
			वापस err;
		nic->flags |= OTX2_FLAG_TC_MATCHALL_EGRESS_ENABLED;
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(extack,
				   "Only police action is supported with Egress MATCHALL offload");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_tc_egress_matchall_delete(काष्ठा otx2_nic *nic,
					  काष्ठा tc_cls_matchall_offload *cls)
अणु
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	पूर्णांक err;

	अगर (nic->flags & OTX2_FLAG_INTF_DOWN) अणु
		NL_SET_ERR_MSG_MOD(extack, "Interface not initialized");
		वापस -EINVAL;
	पूर्ण

	err = otx2_set_matchall_egress_rate(nic, 0, 0);
	nic->flags &= ~OTX2_FLAG_TC_MATCHALL_EGRESS_ENABLED;
	वापस err;
पूर्ण

अटल पूर्णांक otx2_tc_parse_actions(काष्ठा otx2_nic *nic,
				 काष्ठा flow_action *flow_action,
				 काष्ठा npc_install_flow_req *req)
अणु
	काष्ठा flow_action_entry *act;
	काष्ठा net_device *target;
	काष्ठा otx2_nic *priv;
	पूर्णांक i;

	अगर (!flow_action_has_entries(flow_action)) अणु
		netdev_info(nic->netdev, "no tc actions specified");
		वापस -EINVAL;
	पूर्ण

	flow_action_क्रम_each(i, act, flow_action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_DROP:
			req->op = NIX_RX_ACTIONOP_DROP;
			वापस 0;
		हाल FLOW_ACTION_ACCEPT:
			req->op = NIX_RX_ACTION_DEFAULT;
			वापस 0;
		हाल FLOW_ACTION_REसूचीECT_INGRESS:
			target = act->dev;
			priv = netdev_priv(target);
			/* npc_install_flow_req करोesn't support passing a target pcअगरunc */
			अगर (rvu_get_pf(nic->pcअगरunc) != rvu_get_pf(priv->pcअगरunc)) अणु
				netdev_info(nic->netdev,
					    "can't redirect to other pf/vf\n");
				वापस -EOPNOTSUPP;
			पूर्ण
			req->vf = priv->pcअगरunc & RVU_PFVF_FUNC_MASK;
			req->op = NIX_RX_ACTION_DEFAULT;
			वापस 0;
		हाल FLOW_ACTION_VLAN_POP:
			req->vtag0_valid = true;
			/* use RX_VTAG_TYPE7 which is initialized to strip vlan tag */
			req->vtag0_type = NIX_AF_LFX_RX_VTAG_TYPE7;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_tc_prepare_flow(काष्ठा otx2_nic *nic,
				काष्ठा flow_cls_offload *f,
				काष्ठा npc_install_flow_req *req)
अणु
	काष्ठा flow_msg *flow_spec = &req->packet;
	काष्ठा flow_msg *flow_mask = &req->mask;
	काष्ठा flow_dissector *dissector;
	काष्ठा flow_rule *rule;
	u8 ip_proto = 0;

	rule = flow_cls_offload_flow_rule(f);
	dissector = rule->match.dissector;

	अगर ((dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_IP))))  अणु
		netdev_info(nic->netdev, "unsupported flow used key 0x%x",
			    dissector->used_keys);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);

		/* All EtherTypes can be matched, no hw limitation */
		flow_spec->etype = match.key->n_proto;
		flow_mask->etype = match.mask->n_proto;
		req->features |= BIT_ULL(NPC_ETYPE);

		अगर (match.mask->ip_proto &&
		    (match.key->ip_proto != IPPROTO_TCP &&
		     match.key->ip_proto != IPPROTO_UDP &&
		     match.key->ip_proto != IPPROTO_SCTP &&
		     match.key->ip_proto != IPPROTO_ICMP &&
		     match.key->ip_proto != IPPROTO_ICMPV6)) अणु
			netdev_info(nic->netdev,
				    "ip_proto=0x%x not supported\n",
				    match.key->ip_proto);
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (match.mask->ip_proto)
			ip_proto = match.key->ip_proto;

		अगर (ip_proto == IPPROTO_UDP)
			req->features |= BIT_ULL(NPC_IPPROTO_UDP);
		अन्यथा अगर (ip_proto == IPPROTO_TCP)
			req->features |= BIT_ULL(NPC_IPPROTO_TCP);
		अन्यथा अगर (ip_proto == IPPROTO_SCTP)
			req->features |= BIT_ULL(NPC_IPPROTO_SCTP);
		अन्यथा अगर (ip_proto == IPPROTO_ICMP)
			req->features |= BIT_ULL(NPC_IPPROTO_ICMP);
		अन्यथा अगर (ip_proto == IPPROTO_ICMPV6)
			req->features |= BIT_ULL(NPC_IPPROTO_ICMP6);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		अगर (!is_zero_ether_addr(match.mask->src)) अणु
			netdev_err(nic->netdev, "src mac match not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (!is_zero_ether_addr(match.mask->dst)) अणु
			ether_addr_copy(flow_spec->dmac, (u8 *)&match.key->dst);
			ether_addr_copy(flow_mask->dmac,
					(u8 *)&match.mask->dst);
			req->features |= BIT_ULL(NPC_DMAC);
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IP)) अणु
		काष्ठा flow_match_ip match;

		flow_rule_match_ip(rule, &match);
		अगर ((ntohs(flow_spec->etype) != ETH_P_IP) &&
		    match.mask->tos) अणु
			netdev_err(nic->netdev, "tos not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (match.mask->ttl) अणु
			netdev_err(nic->netdev, "ttl not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		flow_spec->tos = match.key->tos;
		flow_mask->tos = match.mask->tos;
		req->features |= BIT_ULL(NPC_TOS);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;
		u16 vlan_tci, vlan_tci_mask;

		flow_rule_match_vlan(rule, &match);

		अगर (ntohs(match.key->vlan_tpid) != ETH_P_8021Q) अणु
			netdev_err(nic->netdev, "vlan tpid 0x%x not supported\n",
				   ntohs(match.key->vlan_tpid));
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (match.mask->vlan_id ||
		    match.mask->vlan_dei ||
		    match.mask->vlan_priority) अणु
			vlan_tci = match.key->vlan_id |
				   match.key->vlan_dei << 12 |
				   match.key->vlan_priority << 13;

			vlan_tci_mask = match.mask->vlan_id |
					match.key->vlan_dei << 12 |
					match.key->vlan_priority << 13;

			flow_spec->vlan_tci = htons(vlan_tci);
			flow_mask->vlan_tci = htons(vlan_tci_mask);
			req->features |= BIT_ULL(NPC_OUTER_VID);
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);

		flow_spec->ip4dst = match.key->dst;
		flow_mask->ip4dst = match.mask->dst;
		req->features |= BIT_ULL(NPC_DIP_IPV4);

		flow_spec->ip4src = match.key->src;
		flow_mask->ip4src = match.mask->src;
		req->features |= BIT_ULL(NPC_SIP_IPV4);
	पूर्ण अन्यथा अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS)) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);

		अगर (ipv6_addr_loopback(&match.key->dst) ||
		    ipv6_addr_loopback(&match.key->src)) अणु
			netdev_err(nic->netdev,
				   "Flow matching on IPv6 loopback addr is not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (!ipv6_addr_any(&match.mask->dst)) अणु
			स_नकल(&flow_spec->ip6dst,
			       (काष्ठा in6_addr *)&match.key->dst,
			       माप(flow_spec->ip6dst));
			स_नकल(&flow_mask->ip6dst,
			       (काष्ठा in6_addr *)&match.mask->dst,
			       माप(flow_spec->ip6dst));
			req->features |= BIT_ULL(NPC_DIP_IPV6);
		पूर्ण

		अगर (!ipv6_addr_any(&match.mask->src)) अणु
			स_नकल(&flow_spec->ip6src,
			       (काष्ठा in6_addr *)&match.key->src,
			       माप(flow_spec->ip6src));
			स_नकल(&flow_mask->ip6src,
			       (काष्ठा in6_addr *)&match.mask->src,
			       माप(flow_spec->ip6src));
			req->features |= BIT_ULL(NPC_SIP_IPV6);
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);

		flow_spec->dport = match.key->dst;
		flow_mask->dport = match.mask->dst;
		अगर (ip_proto == IPPROTO_UDP)
			req->features |= BIT_ULL(NPC_DPORT_UDP);
		अन्यथा अगर (ip_proto == IPPROTO_TCP)
			req->features |= BIT_ULL(NPC_DPORT_TCP);
		अन्यथा अगर (ip_proto == IPPROTO_SCTP)
			req->features |= BIT_ULL(NPC_DPORT_SCTP);

		flow_spec->sport = match.key->src;
		flow_mask->sport = match.mask->src;
		अगर (ip_proto == IPPROTO_UDP)
			req->features |= BIT_ULL(NPC_SPORT_UDP);
		अन्यथा अगर (ip_proto == IPPROTO_TCP)
			req->features |= BIT_ULL(NPC_SPORT_TCP);
		अन्यथा अगर (ip_proto == IPPROTO_SCTP)
			req->features |= BIT_ULL(NPC_SPORT_SCTP);
	पूर्ण

	वापस otx2_tc_parse_actions(nic, &rule->action, req);
पूर्ण

अटल पूर्णांक otx2_del_mcam_flow_entry(काष्ठा otx2_nic *nic, u16 entry)
अणु
	काष्ठा npc_delete_flow_req *req;
	पूर्णांक err;

	mutex_lock(&nic->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_delete_flow(&nic->mbox);
	अगर (!req) अणु
		mutex_unlock(&nic->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->entry = entry;

	/* Send message to AF */
	err = otx2_sync_mbox_msg(&nic->mbox);
	अगर (err) अणु
		netdev_err(nic->netdev, "Failed to delete MCAM flow entry %d\n",
			   entry);
		mutex_unlock(&nic->mbox.lock);
		वापस -EFAULT;
	पूर्ण
	mutex_unlock(&nic->mbox.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_tc_del_flow(काष्ठा otx2_nic *nic,
			    काष्ठा flow_cls_offload *tc_flow_cmd)
अणु
	काष्ठा otx2_tc_info *tc_info = &nic->tc_info;
	काष्ठा otx2_tc_flow *flow_node;

	flow_node = rhashtable_lookup_fast(&tc_info->flow_table,
					   &tc_flow_cmd->cookie,
					   tc_info->flow_ht_params);
	अगर (!flow_node) अणु
		netdev_err(nic->netdev, "tc flow not found for cookie 0x%lx\n",
			   tc_flow_cmd->cookie);
		वापस -EINVAL;
	पूर्ण

	otx2_del_mcam_flow_entry(nic, flow_node->entry);

	WARN_ON(rhashtable_हटाओ_fast(&nic->tc_info.flow_table,
				       &flow_node->node,
				       nic->tc_info.flow_ht_params));
	kमुक्त_rcu(flow_node, rcu);

	clear_bit(flow_node->bitpos, tc_info->tc_entries_biपंचांगap);
	tc_info->num_entries--;

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_tc_add_flow(काष्ठा otx2_nic *nic,
			    काष्ठा flow_cls_offload *tc_flow_cmd)
अणु
	काष्ठा otx2_tc_info *tc_info = &nic->tc_info;
	काष्ठा otx2_tc_flow *new_node, *old_node;
	काष्ठा npc_install_flow_req *req;
	पूर्णांक rc;

	अगर (!(nic->flags & OTX2_FLAG_TC_FLOWER_SUPPORT))
		वापस -ENOMEM;

	/* allocate memory क्रम the new flow and it's node */
	new_node = kzalloc(माप(*new_node), GFP_KERNEL);
	अगर (!new_node)
		वापस -ENOMEM;
	spin_lock_init(&new_node->lock);
	new_node->cookie = tc_flow_cmd->cookie;

	mutex_lock(&nic->mbox.lock);
	req = otx2_mbox_alloc_msg_npc_install_flow(&nic->mbox);
	अगर (!req) अणु
		mutex_unlock(&nic->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	rc = otx2_tc_prepare_flow(nic, tc_flow_cmd, req);
	अगर (rc) अणु
		otx2_mbox_reset(&nic->mbox.mbox, 0);
		mutex_unlock(&nic->mbox.lock);
		वापस rc;
	पूर्ण

	/* If a flow exists with the same cookie, delete it */
	old_node = rhashtable_lookup_fast(&tc_info->flow_table,
					  &tc_flow_cmd->cookie,
					  tc_info->flow_ht_params);
	अगर (old_node)
		otx2_tc_del_flow(nic, tc_flow_cmd);

	अगर (biपंचांगap_full(tc_info->tc_entries_biपंचांगap, nic->flow_cfg->tc_max_flows)) अणु
		netdev_err(nic->netdev, "Not enough MCAM space to add the flow\n");
		otx2_mbox_reset(&nic->mbox.mbox, 0);
		mutex_unlock(&nic->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	new_node->bitpos = find_first_zero_bit(tc_info->tc_entries_biपंचांगap,
					       nic->flow_cfg->tc_max_flows);
	req->channel = nic->hw.rx_chan_base;
	req->entry = nic->flow_cfg->entry[nic->flow_cfg->tc_flower_offset +
					  nic->flow_cfg->tc_max_flows - new_node->bitpos];
	req->पूर्णांकf = NIX_INTF_RX;
	req->set_cntr = 1;
	new_node->entry = req->entry;

	/* Send message to AF */
	rc = otx2_sync_mbox_msg(&nic->mbox);
	अगर (rc) अणु
		netdev_err(nic->netdev, "Failed to install MCAM flow entry\n");
		mutex_unlock(&nic->mbox.lock);
		जाओ out;
	पूर्ण
	mutex_unlock(&nic->mbox.lock);

	/* add new flow to flow-table */
	rc = rhashtable_insert_fast(&nic->tc_info.flow_table, &new_node->node,
				    nic->tc_info.flow_ht_params);
	अगर (rc) अणु
		otx2_del_mcam_flow_entry(nic, req->entry);
		kमुक्त_rcu(new_node, rcu);
		जाओ out;
	पूर्ण

	set_bit(new_node->bitpos, tc_info->tc_entries_biपंचांगap);
	tc_info->num_entries++;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक otx2_tc_get_flow_stats(काष्ठा otx2_nic *nic,
				  काष्ठा flow_cls_offload *tc_flow_cmd)
अणु
	काष्ठा otx2_tc_info *tc_info = &nic->tc_info;
	काष्ठा npc_mcam_get_stats_req *req;
	काष्ठा npc_mcam_get_stats_rsp *rsp;
	काष्ठा otx2_tc_flow_stats *stats;
	काष्ठा otx2_tc_flow *flow_node;
	पूर्णांक err;

	flow_node = rhashtable_lookup_fast(&tc_info->flow_table,
					   &tc_flow_cmd->cookie,
					   tc_info->flow_ht_params);
	अगर (!flow_node) अणु
		netdev_info(nic->netdev, "tc flow not found for cookie %lx",
			    tc_flow_cmd->cookie);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&nic->mbox.lock);

	req = otx2_mbox_alloc_msg_npc_mcam_entry_stats(&nic->mbox);
	अगर (!req) अणु
		mutex_unlock(&nic->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->entry = flow_node->entry;

	err = otx2_sync_mbox_msg(&nic->mbox);
	अगर (err) अणु
		netdev_err(nic->netdev, "Failed to get stats for MCAM flow entry %d\n",
			   req->entry);
		mutex_unlock(&nic->mbox.lock);
		वापस -EFAULT;
	पूर्ण

	rsp = (काष्ठा npc_mcam_get_stats_rsp *)otx2_mbox_get_rsp
		(&nic->mbox.mbox, 0, &req->hdr);
	अगर (IS_ERR(rsp)) अणु
		mutex_unlock(&nic->mbox.lock);
		वापस PTR_ERR(rsp);
	पूर्ण

	mutex_unlock(&nic->mbox.lock);

	अगर (!rsp->stat_ena)
		वापस -EINVAL;

	stats = &flow_node->stats;

	spin_lock(&flow_node->lock);
	flow_stats_update(&tc_flow_cmd->stats, 0x0, rsp->stat - stats->pkts, 0x0, 0x0,
			  FLOW_ACTION_HW_STATS_IMMEDIATE);
	stats->pkts = rsp->stat;
	spin_unlock(&flow_node->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_setup_tc_cls_flower(काष्ठा otx2_nic *nic,
				    काष्ठा flow_cls_offload *cls_flower)
अणु
	चयन (cls_flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस otx2_tc_add_flow(nic, cls_flower);
	हाल FLOW_CLS_DESTROY:
		वापस otx2_tc_del_flow(nic, cls_flower);
	हाल FLOW_CLS_STATS:
		वापस otx2_tc_get_flow_stats(nic, cls_flower);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक otx2_setup_tc_block_ingress_cb(क्रमागत tc_setup_type type,
					  व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा otx2_nic *nic = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(nic->netdev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस otx2_setup_tc_cls_flower(nic, type_data);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक otx2_setup_tc_egress_matchall(काष्ठा otx2_nic *nic,
					 काष्ठा tc_cls_matchall_offload *cls_matchall)
अणु
	चयन (cls_matchall->command) अणु
	हाल TC_CLSMATCHALL_REPLACE:
		वापस otx2_tc_egress_matchall_install(nic, cls_matchall);
	हाल TC_CLSMATCHALL_DESTROY:
		वापस otx2_tc_egress_matchall_delete(nic, cls_matchall);
	हाल TC_CLSMATCHALL_STATS:
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक otx2_setup_tc_block_egress_cb(क्रमागत tc_setup_type type,
					 व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा otx2_nic *nic = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(nic->netdev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSMATCHALL:
		वापस otx2_setup_tc_egress_matchall(nic, type_data);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल LIST_HEAD(otx2_block_cb_list);

अटल पूर्णांक otx2_setup_tc_block(काष्ठा net_device *netdev,
			       काष्ठा flow_block_offload *f)
अणु
	काष्ठा otx2_nic *nic = netdev_priv(netdev);
	flow_setup_cb_t *cb;
	bool ingress;

	अगर (f->block_shared)
		वापस -EOPNOTSUPP;

	अगर (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS) अणु
		cb = otx2_setup_tc_block_ingress_cb;
		ingress = true;
	पूर्ण अन्यथा अगर (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS) अणु
		cb = otx2_setup_tc_block_egress_cb;
		ingress = false;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस flow_block_cb_setup_simple(f, &otx2_block_cb_list, cb,
					  nic, nic, ingress);
पूर्ण

पूर्णांक otx2_setup_tc(काष्ठा net_device *netdev, क्रमागत tc_setup_type type,
		  व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस otx2_setup_tc_block(netdev, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rhashtable_params tc_flow_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा otx2_tc_flow, node),
	.key_offset = दुरत्व(काष्ठा otx2_tc_flow, cookie),
	.key_len = माप(((काष्ठा otx2_tc_flow *)0)->cookie),
	.स्वतःmatic_shrinking = true,
पूर्ण;

पूर्णांक otx2_init_tc(काष्ठा otx2_nic *nic)
अणु
	काष्ठा otx2_tc_info *tc = &nic->tc_info;

	tc->flow_ht_params = tc_flow_ht_params;
	वापस rhashtable_init(&tc->flow_table, &tc->flow_ht_params);
पूर्ण

व्योम otx2_shutकरोwn_tc(काष्ठा otx2_nic *nic)
अणु
	काष्ठा otx2_tc_info *tc = &nic->tc_info;

	rhashtable_destroy(&tc->flow_table);
पूर्ण
