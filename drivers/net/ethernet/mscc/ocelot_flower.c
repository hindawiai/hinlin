<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Microsemi Ocelot Switch driver
 * Copyright (c) 2019 Microsemi Corporation
 */

#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <soc/mscc/ocelot_vcap.h>
#समावेश "ocelot_vcap.h"

/* Arbitrarily chosen स्थिरants क्रम encoding the VCAP block and lookup number
 * पूर्णांकo the chain number. This is UAPI.
 */
#घोषणा VCAP_BLOCK			10000
#घोषणा VCAP_LOOKUP			1000
#घोषणा VCAP_IS1_NUM_LOOKUPS		3
#घोषणा VCAP_IS2_NUM_LOOKUPS		2
#घोषणा VCAP_IS2_NUM_PAG		256
#घोषणा VCAP_IS1_CHAIN(lookup)		\
	(1 * VCAP_BLOCK + (lookup) * VCAP_LOOKUP)
#घोषणा VCAP_IS2_CHAIN(lookup, pag)	\
	(2 * VCAP_BLOCK + (lookup) * VCAP_LOOKUP + (pag))

अटल पूर्णांक ocelot_chain_to_block(पूर्णांक chain, bool ingress)
अणु
	पूर्णांक lookup, pag;

	अगर (!ingress) अणु
		अगर (chain == 0)
			वापस VCAP_ES0;
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Backwards compatibility with older, single-chain tc-flower
	 * offload support in Ocelot
	 */
	अगर (chain == 0)
		वापस VCAP_IS2;

	क्रम (lookup = 0; lookup < VCAP_IS1_NUM_LOOKUPS; lookup++)
		अगर (chain == VCAP_IS1_CHAIN(lookup))
			वापस VCAP_IS1;

	क्रम (lookup = 0; lookup < VCAP_IS2_NUM_LOOKUPS; lookup++)
		क्रम (pag = 0; pag < VCAP_IS2_NUM_PAG; pag++)
			अगर (chain == VCAP_IS2_CHAIN(lookup, pag))
				वापस VCAP_IS2;

	वापस -EOPNOTSUPP;
पूर्ण

/* Caller must ensure this is a valid IS1 or IS2 chain first,
 * by calling ocelot_chain_to_block.
 */
अटल पूर्णांक ocelot_chain_to_lookup(पूर्णांक chain)
अणु
	वापस (chain / VCAP_LOOKUP) % 10;
पूर्ण

/* Caller must ensure this is a valid IS2 chain first,
 * by calling ocelot_chain_to_block.
 */
अटल पूर्णांक ocelot_chain_to_pag(पूर्णांक chain)
अणु
	पूर्णांक lookup = ocelot_chain_to_lookup(chain);

	/* calculate PAG value as chain index relative to the first PAG */
	वापस chain - VCAP_IS2_CHAIN(lookup, 0);
पूर्ण

अटल bool ocelot_is_जाओ_target_valid(पूर्णांक जाओ_target, पूर्णांक chain,
					bool ingress)
अणु
	पूर्णांक pag;

	/* Can't offload GOTO in VCAP ES0 */
	अगर (!ingress)
		वापस (जाओ_target < 0);

	/* Non-optional GOTOs */
	अगर (chain == 0)
		/* VCAP IS1 can be skipped, either partially or completely */
		वापस (जाओ_target == VCAP_IS1_CHAIN(0) ||
			जाओ_target == VCAP_IS1_CHAIN(1) ||
			जाओ_target == VCAP_IS1_CHAIN(2) ||
			जाओ_target == VCAP_IS2_CHAIN(0, 0) ||
			जाओ_target == VCAP_IS2_CHAIN(1, 0));

	अगर (chain == VCAP_IS1_CHAIN(0))
		वापस (जाओ_target == VCAP_IS1_CHAIN(1));

	अगर (chain == VCAP_IS1_CHAIN(1))
		वापस (जाओ_target == VCAP_IS1_CHAIN(2));

	/* Lookup 2 of VCAP IS1 can really support non-optional GOTOs,
	 * using a Policy Association Group (PAG) value, which is an 8-bit
	 * value encoding a VCAP IS2 target chain.
	 */
	अगर (chain == VCAP_IS1_CHAIN(2)) अणु
		क्रम (pag = 0; pag < VCAP_IS2_NUM_PAG; pag++)
			अगर (जाओ_target == VCAP_IS2_CHAIN(0, pag))
				वापस true;

		वापस false;
	पूर्ण

	/* Non-optional GOTO from VCAP IS2 lookup 0 to lookup 1.
	 * We cannot change the PAG at this poपूर्णांक.
	 */
	क्रम (pag = 0; pag < VCAP_IS2_NUM_PAG; pag++)
		अगर (chain == VCAP_IS2_CHAIN(0, pag))
			वापस (जाओ_target == VCAP_IS2_CHAIN(1, pag));

	/* VCAP IS2 lookup 1 cannot jump anywhere */
	वापस false;
पूर्ण

अटल काष्ठा ocelot_vcap_filter *
ocelot_find_vcap_filter_that_poपूर्णांकs_at(काष्ठा ocelot *ocelot, पूर्णांक chain)
अणु
	काष्ठा ocelot_vcap_filter *filter;
	काष्ठा ocelot_vcap_block *block;
	पूर्णांक block_id;

	block_id = ocelot_chain_to_block(chain, true);
	अगर (block_id < 0)
		वापस शून्य;

	अगर (block_id == VCAP_IS2) अणु
		block = &ocelot->block[VCAP_IS1];

		list_क्रम_each_entry(filter, &block->rules, list)
			अगर (filter->type == OCELOT_VCAP_FILTER_PAG &&
			    filter->जाओ_target == chain)
				वापस filter;
	पूर्ण

	list_क्रम_each_entry(filter, &ocelot->dummy_rules, list)
		अगर (filter->जाओ_target == chain)
			वापस filter;

	वापस शून्य;
पूर्ण

अटल पूर्णांक ocelot_flower_parse_action(काष्ठा ocelot *ocelot, पूर्णांक port,
				      bool ingress, काष्ठा flow_cls_offload *f,
				      काष्ठा ocelot_vcap_filter *filter)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	bool allow_missing_जाओ_target = false;
	स्थिर काष्ठा flow_action_entry *a;
	क्रमागत ocelot_tag_tpid_sel tpid;
	पूर्णांक i, chain, egress_port;
	u64 rate;

	अगर (!flow_action_basic_hw_stats_check(&f->rule->action,
					      f->common.extack))
		वापस -EOPNOTSUPP;

	chain = f->common.chain_index;
	filter->block_id = ocelot_chain_to_block(chain, ingress);
	अगर (filter->block_id < 0) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot offload to this chain");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (filter->block_id == VCAP_IS1 || filter->block_id == VCAP_IS2)
		filter->lookup = ocelot_chain_to_lookup(chain);
	अगर (filter->block_id == VCAP_IS2)
		filter->pag = ocelot_chain_to_pag(chain);

	filter->जाओ_target = -1;
	filter->type = OCELOT_VCAP_FILTER_DUMMY;

	flow_action_क्रम_each(i, a, &f->rule->action) अणु
		चयन (a->id) अणु
		हाल FLOW_ACTION_DROP:
			अगर (filter->block_id != VCAP_IS2) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Drop action can only be offloaded to VCAP IS2");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (filter->जाओ_target != -1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Last action must be GOTO");
				वापस -EOPNOTSUPP;
			पूर्ण
			filter->action.mask_mode = OCELOT_MASK_MODE_PERMIT_DENY;
			filter->action.port_mask = 0;
			filter->action.police_ena = true;
			filter->action.pol_ix = OCELOT_POLICER_DISCARD;
			filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
			अवरोध;
		हाल FLOW_ACTION_TRAP:
			अगर (filter->block_id != VCAP_IS2) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Trap action can only be offloaded to VCAP IS2");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (filter->जाओ_target != -1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Last action must be GOTO");
				वापस -EOPNOTSUPP;
			पूर्ण
			filter->action.mask_mode = OCELOT_MASK_MODE_PERMIT_DENY;
			filter->action.port_mask = 0;
			filter->action.cpu_copy_ena = true;
			filter->action.cpu_qu_num = 0;
			filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
			अवरोध;
		हाल FLOW_ACTION_POLICE:
			अगर (filter->block_id != VCAP_IS2 ||
			    filter->lookup != 0) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Police action can only be offloaded to VCAP IS2 lookup 0");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (filter->जाओ_target != -1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Last action must be GOTO");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (a->police.rate_pkt_ps) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "QoS offload not support packets per second");
				वापस -EOPNOTSUPP;
			पूर्ण
			filter->action.police_ena = true;
			rate = a->police.rate_bytes_ps;
			filter->action.pol.rate = भाग_u64(rate, 1000) * 8;
			filter->action.pol.burst = a->police.burst;
			filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
			अवरोध;
		हाल FLOW_ACTION_REसूचीECT:
			अगर (filter->block_id != VCAP_IS2) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Redirect action can only be offloaded to VCAP IS2");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (filter->जाओ_target != -1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Last action must be GOTO");
				वापस -EOPNOTSUPP;
			पूर्ण
			egress_port = ocelot->ops->netdev_to_port(a->dev);
			अगर (egress_port < 0) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Destination not an ocelot port");
				वापस -EOPNOTSUPP;
			पूर्ण
			filter->action.mask_mode = OCELOT_MASK_MODE_REसूचीECT;
			filter->action.port_mask = BIT(egress_port);
			filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
			अवरोध;
		हाल FLOW_ACTION_VLAN_POP:
			अगर (filter->block_id != VCAP_IS1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "VLAN pop action can only be offloaded to VCAP IS1");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (filter->जाओ_target != -1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Last action must be GOTO");
				वापस -EOPNOTSUPP;
			पूर्ण
			filter->action.vlan_pop_cnt_ena = true;
			filter->action.vlan_pop_cnt++;
			अगर (filter->action.vlan_pop_cnt > 2) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Cannot pop more than 2 VLAN headers");
				वापस -EOPNOTSUPP;
			पूर्ण
			filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
			अवरोध;
		हाल FLOW_ACTION_VLAN_MANGLE:
			अगर (filter->block_id != VCAP_IS1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "VLAN modify action can only be offloaded to VCAP IS1");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (filter->जाओ_target != -1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Last action must be GOTO");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (!ocelot_port->vlan_aware) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Can only modify VLAN under VLAN aware bridge");
				वापस -EOPNOTSUPP;
			पूर्ण
			filter->action.vid_replace_ena = true;
			filter->action.pcp_dei_ena = true;
			filter->action.vid = a->vlan.vid;
			filter->action.pcp = a->vlan.prio;
			filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
			अवरोध;
		हाल FLOW_ACTION_PRIORITY:
			अगर (filter->block_id != VCAP_IS1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Priority action can only be offloaded to VCAP IS1");
				वापस -EOPNOTSUPP;
			पूर्ण
			अगर (filter->जाओ_target != -1) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Last action must be GOTO");
				वापस -EOPNOTSUPP;
			पूर्ण
			filter->action.qos_ena = true;
			filter->action.qos_val = a->priority;
			filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
			अवरोध;
		हाल FLOW_ACTION_GOTO:
			filter->जाओ_target = a->chain_index;

			अगर (filter->block_id == VCAP_IS1 && filter->lookup == 2) अणु
				पूर्णांक pag = ocelot_chain_to_pag(filter->जाओ_target);

				filter->action.pag_override_mask = 0xff;
				filter->action.pag_val = pag;
				filter->type = OCELOT_VCAP_FILTER_PAG;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_VLAN_PUSH:
			अगर (filter->block_id != VCAP_ES0) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "VLAN push action can only be offloaded to VCAP ES0");
				वापस -EOPNOTSUPP;
			पूर्ण
			चयन (ntohs(a->vlan.proto)) अणु
			हाल ETH_P_8021Q:
				tpid = OCELOT_TAG_TPID_SEL_8021Q;
				अवरोध;
			हाल ETH_P_8021AD:
				tpid = OCELOT_TAG_TPID_SEL_8021AD;
				अवरोध;
			शेष:
				NL_SET_ERR_MSG_MOD(extack,
						   "Cannot push custom TPID");
				वापस -EOPNOTSUPP;
			पूर्ण
			filter->action.tag_a_tpid_sel = tpid;
			filter->action.push_outer_tag = OCELOT_ES0_TAG;
			filter->action.tag_a_vid_sel = 1;
			filter->action.vid_a_val = a->vlan.vid;
			filter->action.pcp_a_val = a->vlan.prio;
			filter->type = OCELOT_VCAP_FILTER_OFFLOAD;
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Cannot offload action");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (filter->जाओ_target == -1) अणु
		अगर ((filter->block_id == VCAP_IS2 && filter->lookup == 1) ||
		    chain == 0) अणु
			allow_missing_जाओ_target = true;
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG_MOD(extack, "Missing GOTO action");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (!ocelot_is_जाओ_target_valid(filter->जाओ_target, chain, ingress) &&
	    !allow_missing_जाओ_target) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot offload this GOTO target");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_flower_parse_indev(काष्ठा ocelot *ocelot, पूर्णांक port,
				     काष्ठा flow_cls_offload *f,
				     काष्ठा ocelot_vcap_filter *filter)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	स्थिर काष्ठा vcap_props *vcap = &ocelot->vcap[VCAP_ES0];
	पूर्णांक key_length = vcap->keys[VCAP_ES0_IGR_PORT].length;
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा net_device *dev, *indev;
	काष्ठा flow_match_meta match;
	पूर्णांक ingress_port;

	flow_rule_match_meta(rule, &match);

	अगर (!match.mask->ingress_अगरindex)
		वापस 0;

	अगर (match.mask->ingress_अगरindex != 0xFFFFFFFF) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported ingress ifindex mask");
		वापस -EOPNOTSUPP;
	पूर्ण

	dev = ocelot->ops->port_to_netdev(ocelot, port);
	अगर (!dev)
		वापस -EINVAL;

	indev = __dev_get_by_index(dev_net(dev), match.key->ingress_अगरindex);
	अगर (!indev) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can't find the ingress port to match on");
		वापस -ENOENT;
	पूर्ण

	ingress_port = ocelot->ops->netdev_to_port(indev);
	अगर (ingress_port < 0) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Can only offload an ocelot ingress port");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (ingress_port == port) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Ingress port is equal to the egress port");
		वापस -EINVAL;
	पूर्ण

	filter->ingress_port.value = ingress_port;
	filter->ingress_port.mask = GENMASK(key_length - 1, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
ocelot_flower_parse_key(काष्ठा ocelot *ocelot, पूर्णांक port, bool ingress,
			काष्ठा flow_cls_offload *f,
			काष्ठा ocelot_vcap_filter *filter)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	u16 proto = ntohs(f->common.protocol);
	bool match_protocol = true;
	पूर्णांक ret;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_META) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS))) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	/* For VCAP ES0 (egress reग_लिखोr) we can match on the ingress port */
	अगर (!ingress) अणु
		ret = ocelot_flower_parse_indev(ocelot, port, f, filter);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(rule, &match);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		अगर (filter->block_id == VCAP_ES0) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "VCAP ES0 cannot match on MAC address");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (filter->block_id == VCAP_IS1 &&
		    !is_zero_ether_addr(match.mask->dst)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Key type S1_NORMAL cannot match on destination MAC");
			वापस -EOPNOTSUPP;
		पूर्ण

		/* The hw support mac matches only क्रम MAC_ETYPE key,
		 * thereक्रमe अगर other matches(port, tcp flags, etc) are added
		 * then just bail out
		 */
		अगर ((dissector->used_keys &
		    (BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
		     BIT(FLOW_DISSECTOR_KEY_BASIC) |
		     BIT(FLOW_DISSECTOR_KEY_CONTROL))) !=
		    (BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
		     BIT(FLOW_DISSECTOR_KEY_BASIC) |
		     BIT(FLOW_DISSECTOR_KEY_CONTROL)))
			वापस -EOPNOTSUPP;

		flow_rule_match_eth_addrs(rule, &match);
		filter->key_type = OCELOT_VCAP_KEY_ETYPE;
		ether_addr_copy(filter->key.etype.dmac.value,
				match.key->dst);
		ether_addr_copy(filter->key.etype.smac.value,
				match.key->src);
		ether_addr_copy(filter->key.etype.dmac.mask,
				match.mask->dst);
		ether_addr_copy(filter->key.etype.smac.mask,
				match.mask->src);
		जाओ finished_key_parsing;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		अगर (ntohs(match.key->n_proto) == ETH_P_IP) अणु
			अगर (filter->block_id == VCAP_ES0) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "VCAP ES0 cannot match on IP protocol");
				वापस -EOPNOTSUPP;
			पूर्ण

			filter->key_type = OCELOT_VCAP_KEY_IPV4;
			filter->key.ipv4.proto.value[0] =
				match.key->ip_proto;
			filter->key.ipv4.proto.mask[0] =
				match.mask->ip_proto;
			match_protocol = false;
		पूर्ण
		अगर (ntohs(match.key->n_proto) == ETH_P_IPV6) अणु
			अगर (filter->block_id == VCAP_ES0) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "VCAP ES0 cannot match on IP protocol");
				वापस -EOPNOTSUPP;
			पूर्ण

			filter->key_type = OCELOT_VCAP_KEY_IPV6;
			filter->key.ipv6.proto.value[0] =
				match.key->ip_proto;
			filter->key.ipv6.proto.mask[0] =
				match.mask->ip_proto;
			match_protocol = false;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS) &&
	    proto == ETH_P_IP) अणु
		काष्ठा flow_match_ipv4_addrs match;
		u8 *पंचांगp;

		अगर (filter->block_id == VCAP_ES0) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "VCAP ES0 cannot match on IP address");
			वापस -EOPNOTSUPP;
		पूर्ण

		flow_rule_match_ipv4_addrs(rule, &match);

		अगर (filter->block_id == VCAP_IS1 && *(u32 *)&match.mask->dst) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Key type S1_NORMAL cannot match on destination IP");
			वापस -EOPNOTSUPP;
		पूर्ण

		पंचांगp = &filter->key.ipv4.sip.value.addr[0];
		स_नकल(पंचांगp, &match.key->src, 4);

		पंचांगp = &filter->key.ipv4.sip.mask.addr[0];
		स_नकल(पंचांगp, &match.mask->src, 4);

		पंचांगp = &filter->key.ipv4.dip.value.addr[0];
		स_नकल(पंचांगp, &match.key->dst, 4);

		पंचांगp = &filter->key.ipv4.dip.mask.addr[0];
		स_नकल(पंचांगp, &match.mask->dst, 4);
		match_protocol = false;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS) &&
	    proto == ETH_P_IPV6) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		अगर (filter->block_id == VCAP_ES0) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "VCAP ES0 cannot match on L4 ports");
			वापस -EOPNOTSUPP;
		पूर्ण

		flow_rule_match_ports(rule, &match);
		filter->key.ipv4.sport.value = ntohs(match.key->src);
		filter->key.ipv4.sport.mask = ntohs(match.mask->src);
		filter->key.ipv4.dport.value = ntohs(match.key->dst);
		filter->key.ipv4.dport.mask = ntohs(match.mask->dst);
		match_protocol = false;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		filter->key_type = OCELOT_VCAP_KEY_ANY;
		filter->vlan.vid.value = match.key->vlan_id;
		filter->vlan.vid.mask = match.mask->vlan_id;
		filter->vlan.pcp.value[0] = match.key->vlan_priority;
		filter->vlan.pcp.mask[0] = match.mask->vlan_priority;
		match_protocol = false;
	पूर्ण

finished_key_parsing:
	अगर (match_protocol && proto != ETH_P_ALL) अणु
		अगर (filter->block_id == VCAP_ES0) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "VCAP ES0 cannot match on L2 proto");
			वापस -EOPNOTSUPP;
		पूर्ण

		/* TODO: support SNAP, LLC etc */
		अगर (proto < ETH_P_802_3_MIN)
			वापस -EOPNOTSUPP;
		filter->key_type = OCELOT_VCAP_KEY_ETYPE;
		*(__be16 *)filter->key.etype.etype.value = htons(proto);
		*(__be16 *)filter->key.etype.etype.mask = htons(0xffff);
	पूर्ण
	/* अन्यथा, a filter of type OCELOT_VCAP_KEY_ANY is implicitly added */

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_flower_parse(काष्ठा ocelot *ocelot, पूर्णांक port, bool ingress,
			       काष्ठा flow_cls_offload *f,
			       काष्ठा ocelot_vcap_filter *filter)
अणु
	पूर्णांक ret;

	filter->prio = f->common.prio;
	filter->id.cookie = f->cookie;
	filter->id.tc_offload = true;

	ret = ocelot_flower_parse_action(ocelot, port, ingress, f, filter);
	अगर (ret)
		वापस ret;

	वापस ocelot_flower_parse_key(ocelot, port, ingress, f, filter);
पूर्ण

अटल काष्ठा ocelot_vcap_filter
*ocelot_vcap_filter_create(काष्ठा ocelot *ocelot, पूर्णांक port, bool ingress,
			   काष्ठा flow_cls_offload *f)
अणु
	काष्ठा ocelot_vcap_filter *filter;

	filter = kzalloc(माप(*filter), GFP_KERNEL);
	अगर (!filter)
		वापस शून्य;

	अगर (ingress) अणु
		filter->ingress_port_mask = BIT(port);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा vcap_props *vcap = &ocelot->vcap[VCAP_ES0];
		पूर्णांक key_length = vcap->keys[VCAP_ES0_EGR_PORT].length;

		filter->egress_port.value = port;
		filter->egress_port.mask = GENMASK(key_length - 1, 0);
	पूर्ण

	वापस filter;
पूर्ण

अटल पूर्णांक ocelot_vcap_dummy_filter_add(काष्ठा ocelot *ocelot,
					काष्ठा ocelot_vcap_filter *filter)
अणु
	list_add(&filter->list, &ocelot->dummy_rules);

	वापस 0;
पूर्ण

अटल पूर्णांक ocelot_vcap_dummy_filter_del(काष्ठा ocelot *ocelot,
					काष्ठा ocelot_vcap_filter *filter)
अणु
	list_del(&filter->list);
	kमुक्त(filter);

	वापस 0;
पूर्ण

पूर्णांक ocelot_cls_flower_replace(काष्ठा ocelot *ocelot, पूर्णांक port,
			      काष्ठा flow_cls_offload *f, bool ingress)
अणु
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा ocelot_vcap_filter *filter;
	पूर्णांक chain = f->common.chain_index;
	पूर्णांक ret;

	अगर (chain && !ocelot_find_vcap_filter_that_poपूर्णांकs_at(ocelot, chain)) अणु
		NL_SET_ERR_MSG_MOD(extack, "No default GOTO action points to this chain");
		वापस -EOPNOTSUPP;
	पूर्ण

	filter = ocelot_vcap_filter_create(ocelot, port, ingress, f);
	अगर (!filter)
		वापस -ENOMEM;

	ret = ocelot_flower_parse(ocelot, port, ingress, f, filter);
	अगर (ret) अणु
		kमुक्त(filter);
		वापस ret;
	पूर्ण

	/* The non-optional GOTOs क्रम the TCAM skeleton करोn't need
	 * to be actually offloaded.
	 */
	अगर (filter->type == OCELOT_VCAP_FILTER_DUMMY)
		वापस ocelot_vcap_dummy_filter_add(ocelot, filter);

	वापस ocelot_vcap_filter_add(ocelot, filter, f->common.extack);
पूर्ण
EXPORT_SYMBOL_GPL(ocelot_cls_flower_replace);

पूर्णांक ocelot_cls_flower_destroy(काष्ठा ocelot *ocelot, पूर्णांक port,
			      काष्ठा flow_cls_offload *f, bool ingress)
अणु
	काष्ठा ocelot_vcap_filter *filter;
	काष्ठा ocelot_vcap_block *block;
	पूर्णांक block_id;

	block_id = ocelot_chain_to_block(f->common.chain_index, ingress);
	अगर (block_id < 0)
		वापस 0;

	block = &ocelot->block[block_id];

	filter = ocelot_vcap_block_find_filter_by_id(block, f->cookie, true);
	अगर (!filter)
		वापस 0;

	अगर (filter->type == OCELOT_VCAP_FILTER_DUMMY)
		वापस ocelot_vcap_dummy_filter_del(ocelot, filter);

	वापस ocelot_vcap_filter_del(ocelot, filter);
पूर्ण
EXPORT_SYMBOL_GPL(ocelot_cls_flower_destroy);

पूर्णांक ocelot_cls_flower_stats(काष्ठा ocelot *ocelot, पूर्णांक port,
			    काष्ठा flow_cls_offload *f, bool ingress)
अणु
	काष्ठा ocelot_vcap_filter *filter;
	काष्ठा ocelot_vcap_block *block;
	पूर्णांक block_id, ret;

	block_id = ocelot_chain_to_block(f->common.chain_index, ingress);
	अगर (block_id < 0)
		वापस 0;

	block = &ocelot->block[block_id];

	filter = ocelot_vcap_block_find_filter_by_id(block, f->cookie, true);
	अगर (!filter || filter->type == OCELOT_VCAP_FILTER_DUMMY)
		वापस 0;

	ret = ocelot_vcap_filter_stats_update(ocelot, filter);
	अगर (ret)
		वापस ret;

	flow_stats_update(&f->stats, 0x0, filter->stats.pkts, 0, 0x0,
			  FLOW_ACTION_HW_STATS_IMMEDIATE);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ocelot_cls_flower_stats);
