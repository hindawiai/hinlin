<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2020, NXP Semiconductors
 */
#समावेश "sja1105.h"
#समावेश "sja1105_vl.h"

काष्ठा sja1105_rule *sja1105_rule_find(काष्ठा sja1105_निजी *priv,
				       अचिन्हित दीर्घ cookie)
अणु
	काष्ठा sja1105_rule *rule;

	list_क्रम_each_entry(rule, &priv->flow_block.rules, list)
		अगर (rule->cookie == cookie)
			वापस rule;

	वापस शून्य;
पूर्ण

अटल पूर्णांक sja1105_find_मुक्त_l2_policer(काष्ठा sja1105_निजी *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SJA1105_NUM_L2_POLICERS; i++)
		अगर (!priv->flow_block.l2_policer_used[i])
			वापस i;

	वापस -1;
पूर्ण

अटल पूर्णांक sja1105_setup_bcast_policer(काष्ठा sja1105_निजी *priv,
				       काष्ठा netlink_ext_ack *extack,
				       अचिन्हित दीर्घ cookie, पूर्णांक port,
				       u64 rate_bytes_per_sec,
				       u32 burst)
अणु
	काष्ठा sja1105_rule *rule = sja1105_rule_find(priv, cookie);
	काष्ठा sja1105_l2_policing_entry *policing;
	bool new_rule = false;
	अचिन्हित दीर्घ p;
	पूर्णांक rc;

	अगर (!rule) अणु
		rule = kzalloc(माप(*rule), GFP_KERNEL);
		अगर (!rule)
			वापस -ENOMEM;

		rule->cookie = cookie;
		rule->type = SJA1105_RULE_BCAST_POLICER;
		rule->bcast_pol.sharindx = sja1105_find_मुक्त_l2_policer(priv);
		rule->key.type = SJA1105_KEY_BCAST;
		new_rule = true;
	पूर्ण

	अगर (rule->bcast_pol.sharindx == -1) अणु
		NL_SET_ERR_MSG_MOD(extack, "No more L2 policers free");
		rc = -ENOSPC;
		जाओ out;
	पूर्ण

	policing = priv->अटल_config.tables[BLK_IDX_L2_POLICING].entries;

	अगर (policing[(SJA1105_NUM_PORTS * SJA1105_NUM_TC) + port].sharindx != port) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Port already has a broadcast policer");
		rc = -EEXIST;
		जाओ out;
	पूर्ण

	rule->port_mask |= BIT(port);

	/* Make the broadcast policers of all ports attached to this block
	 * poपूर्णांक to the newly allocated policer
	 */
	क्रम_each_set_bit(p, &rule->port_mask, SJA1105_NUM_PORTS) अणु
		पूर्णांक bcast = (SJA1105_NUM_PORTS * SJA1105_NUM_TC) + p;

		policing[bcast].sharindx = rule->bcast_pol.sharindx;
	पूर्ण

	policing[rule->bcast_pol.sharindx].rate = भाग_u64(rate_bytes_per_sec *
							  512, 1000000);
	policing[rule->bcast_pol.sharindx].smax = burst;

	/* TODO: support per-flow MTU */
	policing[rule->bcast_pol.sharindx].maxlen = VLAN_ETH_FRAME_LEN +
						    ETH_FCS_LEN;

	rc = sja1105_अटल_config_reload(priv, SJA1105_BEST_EFFORT_POLICING);

out:
	अगर (rc == 0 && new_rule) अणु
		priv->flow_block.l2_policer_used[rule->bcast_pol.sharindx] = true;
		list_add(&rule->list, &priv->flow_block.rules);
	पूर्ण अन्यथा अगर (new_rule) अणु
		kमुक्त(rule);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_setup_tc_policer(काष्ठा sja1105_निजी *priv,
				    काष्ठा netlink_ext_ack *extack,
				    अचिन्हित दीर्घ cookie, पूर्णांक port, पूर्णांक tc,
				    u64 rate_bytes_per_sec,
				    u32 burst)
अणु
	काष्ठा sja1105_rule *rule = sja1105_rule_find(priv, cookie);
	काष्ठा sja1105_l2_policing_entry *policing;
	bool new_rule = false;
	अचिन्हित दीर्घ p;
	पूर्णांक rc;

	अगर (!rule) अणु
		rule = kzalloc(माप(*rule), GFP_KERNEL);
		अगर (!rule)
			वापस -ENOMEM;

		rule->cookie = cookie;
		rule->type = SJA1105_RULE_TC_POLICER;
		rule->tc_pol.sharindx = sja1105_find_मुक्त_l2_policer(priv);
		rule->key.type = SJA1105_KEY_TC;
		rule->key.tc.pcp = tc;
		new_rule = true;
	पूर्ण

	अगर (rule->tc_pol.sharindx == -1) अणु
		NL_SET_ERR_MSG_MOD(extack, "No more L2 policers free");
		rc = -ENOSPC;
		जाओ out;
	पूर्ण

	policing = priv->अटल_config.tables[BLK_IDX_L2_POLICING].entries;

	अगर (policing[(port * SJA1105_NUM_TC) + tc].sharindx != port) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Port-TC pair already has an L2 policer");
		rc = -EEXIST;
		जाओ out;
	पूर्ण

	rule->port_mask |= BIT(port);

	/* Make the policers क्रम traffic class @tc of all ports attached to
	 * this block poपूर्णांक to the newly allocated policer
	 */
	क्रम_each_set_bit(p, &rule->port_mask, SJA1105_NUM_PORTS) अणु
		पूर्णांक index = (p * SJA1105_NUM_TC) + tc;

		policing[index].sharindx = rule->tc_pol.sharindx;
	पूर्ण

	policing[rule->tc_pol.sharindx].rate = भाग_u64(rate_bytes_per_sec *
						       512, 1000000);
	policing[rule->tc_pol.sharindx].smax = burst;

	/* TODO: support per-flow MTU */
	policing[rule->tc_pol.sharindx].maxlen = VLAN_ETH_FRAME_LEN +
						 ETH_FCS_LEN;

	rc = sja1105_अटल_config_reload(priv, SJA1105_BEST_EFFORT_POLICING);

out:
	अगर (rc == 0 && new_rule) अणु
		priv->flow_block.l2_policer_used[rule->tc_pol.sharindx] = true;
		list_add(&rule->list, &priv->flow_block.rules);
	पूर्ण अन्यथा अगर (new_rule) अणु
		kमुक्त(rule);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_flower_policer(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				  काष्ठा netlink_ext_ack *extack,
				  अचिन्हित दीर्घ cookie,
				  काष्ठा sja1105_key *key,
				  u64 rate_bytes_per_sec,
				  u32 burst)
अणु
	चयन (key->type) अणु
	हाल SJA1105_KEY_BCAST:
		वापस sja1105_setup_bcast_policer(priv, extack, cookie, port,
						   rate_bytes_per_sec, burst);
	हाल SJA1105_KEY_TC:
		वापस sja1105_setup_tc_policer(priv, extack, cookie, port,
						key->tc.pcp, rate_bytes_per_sec,
						burst);
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "Unknown keys for policing");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक sja1105_flower_parse_key(काष्ठा sja1105_निजी *priv,
				    काष्ठा netlink_ext_ack *extack,
				    काष्ठा flow_cls_offload *cls,
				    काष्ठा sja1105_key *key)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	bool is_bcast_dmac = false;
	u64 dmac = U64_MAX;
	u16 vid = U16_MAX;
	u16 pcp = U16_MAX;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Unsupported keys used");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		अगर (match.key->n_proto) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Matching on protocol not supported");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		u8 bcast[] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xffपूर्ण;
		u8 null[] = अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);

		अगर (!ether_addr_equal_masked(match.key->src, null,
					     match.mask->src)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Matching on source MAC not supported");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (!ether_addr_equal(match.mask->dst, bcast)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Masked matching on MAC not supported");
			वापस -EOPNOTSUPP;
		पूर्ण

		dmac = ether_addr_to_u64(match.key->dst);
		is_bcast_dmac = ether_addr_equal(match.key->dst, bcast);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);

		अगर (match.mask->vlan_id &&
		    match.mask->vlan_id != VLAN_VID_MASK) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Masked matching on VID is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (match.mask->vlan_priority &&
		    match.mask->vlan_priority != 0x7) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Masked matching on PCP is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (match.mask->vlan_id)
			vid = match.key->vlan_id;
		अगर (match.mask->vlan_priority)
			pcp = match.key->vlan_priority;
	पूर्ण

	अगर (is_bcast_dmac && vid == U16_MAX && pcp == U16_MAX) अणु
		key->type = SJA1105_KEY_BCAST;
		वापस 0;
	पूर्ण
	अगर (dmac == U64_MAX && vid == U16_MAX && pcp != U16_MAX) अणु
		key->type = SJA1105_KEY_TC;
		key->tc.pcp = pcp;
		वापस 0;
	पूर्ण
	अगर (dmac != U64_MAX && vid != U16_MAX && pcp != U16_MAX) अणु
		key->type = SJA1105_KEY_VLAN_AWARE_VL;
		key->vl.dmac = dmac;
		key->vl.vid = vid;
		key->vl.pcp = pcp;
		वापस 0;
	पूर्ण
	अगर (dmac != U64_MAX) अणु
		key->type = SJA1105_KEY_VLAN_UNAWARE_VL;
		key->vl.dmac = dmac;
		वापस 0;
	पूर्ण

	NL_SET_ERR_MSG_MOD(extack, "Not matching on any known key");
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक sja1105_cls_flower_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा flow_cls_offload *cls, bool ingress)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls);
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा sja1105_निजी *priv = ds->priv;
	स्थिर काष्ठा flow_action_entry *act;
	अचिन्हित दीर्घ cookie = cls->cookie;
	bool routing_rule = false;
	काष्ठा sja1105_key key;
	bool gate_rule = false;
	bool vl_rule = false;
	पूर्णांक rc, i;

	rc = sja1105_flower_parse_key(priv, extack, cls, &key);
	अगर (rc)
		वापस rc;

	flow_action_क्रम_each(i, act, &rule->action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_POLICE:
			अगर (act->police.rate_pkt_ps) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "QoS offload not support packets per second");
				rc = -EOPNOTSUPP;
				जाओ out;
			पूर्ण

			rc = sja1105_flower_policer(priv, port, extack, cookie,
						    &key,
						    act->police.rate_bytes_ps,
						    act->police.burst);
			अगर (rc)
				जाओ out;
			अवरोध;
		हाल FLOW_ACTION_TRAP: अणु
			पूर्णांक cpu = dsa_upstream_port(ds, port);

			routing_rule = true;
			vl_rule = true;

			rc = sja1105_vl_redirect(priv, port, extack, cookie,
						 &key, BIT(cpu), true);
			अगर (rc)
				जाओ out;
			अवरोध;
		पूर्ण
		हाल FLOW_ACTION_REसूचीECT: अणु
			काष्ठा dsa_port *to_dp;

			to_dp = dsa_port_from_netdev(act->dev);
			अगर (IS_ERR(to_dp)) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Destination not a switch port");
				वापस -EOPNOTSUPP;
			पूर्ण

			routing_rule = true;
			vl_rule = true;

			rc = sja1105_vl_redirect(priv, port, extack, cookie,
						 &key, BIT(to_dp->index), true);
			अगर (rc)
				जाओ out;
			अवरोध;
		पूर्ण
		हाल FLOW_ACTION_DROP:
			vl_rule = true;

			rc = sja1105_vl_redirect(priv, port, extack, cookie,
						 &key, 0, false);
			अगर (rc)
				जाओ out;
			अवरोध;
		हाल FLOW_ACTION_GATE:
			gate_rule = true;
			vl_rule = true;

			rc = sja1105_vl_gate(priv, port, extack, cookie,
					     &key, act->gate.index,
					     act->gate.prio,
					     act->gate.baseसमय,
					     act->gate.cycleसमय,
					     act->gate.cycleसमयext,
					     act->gate.num_entries,
					     act->gate.entries);
			अगर (rc)
				जाओ out;
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack,
					   "Action not supported");
			rc = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (vl_rule && !rc) अणु
		/* Delay scheduling configuration until DESTPORTS has been
		 * populated by all other actions.
		 */
		अगर (gate_rule) अणु
			अगर (!routing_rule) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Can only offload gate action together with redirect or trap");
				वापस -EOPNOTSUPP;
			पूर्ण
			rc = sja1105_init_scheduling(priv);
			अगर (rc)
				जाओ out;
		पूर्ण

		rc = sja1105_अटल_config_reload(priv, SJA1105_VIRTUAL_LINKS);
	पूर्ण

out:
	वापस rc;
पूर्ण

पूर्णांक sja1105_cls_flower_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा flow_cls_offload *cls, bool ingress)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_rule *rule = sja1105_rule_find(priv, cls->cookie);
	काष्ठा sja1105_l2_policing_entry *policing;
	पूर्णांक old_sharindx;

	अगर (!rule)
		वापस 0;

	अगर (rule->type == SJA1105_RULE_VL)
		वापस sja1105_vl_delete(priv, port, rule, cls->common.extack);

	policing = priv->अटल_config.tables[BLK_IDX_L2_POLICING].entries;

	अगर (rule->type == SJA1105_RULE_BCAST_POLICER) अणु
		पूर्णांक bcast = (SJA1105_NUM_PORTS * SJA1105_NUM_TC) + port;

		old_sharindx = policing[bcast].sharindx;
		policing[bcast].sharindx = port;
	पूर्ण अन्यथा अगर (rule->type == SJA1105_RULE_TC_POLICER) अणु
		पूर्णांक index = (port * SJA1105_NUM_TC) + rule->key.tc.pcp;

		old_sharindx = policing[index].sharindx;
		policing[index].sharindx = port;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	rule->port_mask &= ~BIT(port);
	अगर (!rule->port_mask) अणु
		priv->flow_block.l2_policer_used[old_sharindx] = false;
		list_del(&rule->list);
		kमुक्त(rule);
	पूर्ण

	वापस sja1105_अटल_config_reload(priv, SJA1105_BEST_EFFORT_POLICING);
पूर्ण

पूर्णांक sja1105_cls_flower_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     काष्ठा flow_cls_offload *cls, bool ingress)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_rule *rule = sja1105_rule_find(priv, cls->cookie);
	पूर्णांक rc;

	अगर (!rule)
		वापस 0;

	अगर (rule->type != SJA1105_RULE_VL)
		वापस 0;

	rc = sja1105_vl_stats(priv, port, rule, &cls->stats,
			      cls->common.extack);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

व्योम sja1105_flower_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	पूर्णांक port;

	INIT_LIST_HEAD(&priv->flow_block.rules);

	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++)
		priv->flow_block.l2_policer_used[port] = true;
पूर्ण

व्योम sja1105_flower_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा sja1105_निजी *priv = ds->priv;
	काष्ठा sja1105_rule *rule;
	काष्ठा list_head *pos, *n;

	list_क्रम_each_safe(pos, n, &priv->flow_block.rules) अणु
		rule = list_entry(pos, काष्ठा sja1105_rule, list);
		list_del(&rule->list);
		kमुक्त(rule);
	पूर्ण
पूर्ण
