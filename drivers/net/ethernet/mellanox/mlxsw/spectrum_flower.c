<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/log2.h>
#समावेश <net/net_namespace.h>
#समावेश <net/flow_dissector.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_mirred.h>
#समावेश <net/tc_act/tc_vlan.h>

#समावेश "spectrum.h"
#समावेश "core_acl_flex_keys.h"

अटल पूर्णांक mlxsw_sp_flower_parse_actions(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_flow_block *block,
					 काष्ठा mlxsw_sp_acl_rule_info *rulei,
					 काष्ठा flow_action *flow_action,
					 काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा flow_action_entry *act;
	पूर्णांक mirror_act_count = 0;
	पूर्णांक police_act_count = 0;
	पूर्णांक sample_act_count = 0;
	पूर्णांक err, i;

	अगर (!flow_action_has_entries(flow_action))
		वापस 0;
	अगर (!flow_action_mixed_hw_stats_check(flow_action, extack))
		वापस -EOPNOTSUPP;

	act = flow_action_first_entry_get(flow_action);
	अगर (act->hw_stats & FLOW_ACTION_HW_STATS_DISABLED) अणु
		/* Nothing to करो */
	पूर्ण अन्यथा अगर (act->hw_stats & FLOW_ACTION_HW_STATS_IMMEDIATE) अणु
		/* Count action is inserted first */
		err = mlxsw_sp_acl_rulei_act_count(mlxsw_sp, rulei, extack);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported action HW stats type");
		वापस -EOPNOTSUPP;
	पूर्ण

	flow_action_क्रम_each(i, act, flow_action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_ACCEPT:
			err = mlxsw_sp_acl_rulei_act_terminate(rulei);
			अगर (err) अणु
				NL_SET_ERR_MSG_MOD(extack, "Cannot append terminate action");
				वापस err;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_DROP: अणु
			bool ingress;

			अगर (mlxsw_sp_flow_block_is_mixed_bound(block)) अणु
				NL_SET_ERR_MSG_MOD(extack, "Drop action is not supported when block is bound to ingress and egress");
				वापस -EOPNOTSUPP;
			पूर्ण
			ingress = mlxsw_sp_flow_block_is_ingress_bound(block);
			err = mlxsw_sp_acl_rulei_act_drop(rulei, ingress,
							  act->cookie, extack);
			अगर (err) अणु
				NL_SET_ERR_MSG_MOD(extack, "Cannot append drop action");
				वापस err;
			पूर्ण

			/* Forbid block with this rulei to be bound
			 * to ingress/egress in future. Ingress rule is
			 * a blocker क्रम egress and vice versa.
			 */
			अगर (ingress)
				rulei->egress_bind_blocker = 1;
			अन्यथा
				rulei->ingress_bind_blocker = 1;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_TRAP:
			err = mlxsw_sp_acl_rulei_act_trap(rulei);
			अगर (err) अणु
				NL_SET_ERR_MSG_MOD(extack, "Cannot append trap action");
				वापस err;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_GOTO: अणु
			u32 chain_index = act->chain_index;
			काष्ठा mlxsw_sp_acl_ruleset *ruleset;
			u16 group_id;

			ruleset = mlxsw_sp_acl_ruleset_lookup(mlxsw_sp, block,
							      chain_index,
							      MLXSW_SP_ACL_PROखाता_FLOWER);
			अगर (IS_ERR(ruleset))
				वापस PTR_ERR(ruleset);

			group_id = mlxsw_sp_acl_ruleset_group_id(ruleset);
			err = mlxsw_sp_acl_rulei_act_jump(rulei, group_id);
			अगर (err) अणु
				NL_SET_ERR_MSG_MOD(extack, "Cannot append jump action");
				वापस err;
			पूर्ण
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_REसूचीECT: अणु
			काष्ठा net_device *out_dev;
			काष्ठा mlxsw_sp_fid *fid;
			u16 fid_index;

			अगर (mlxsw_sp_flow_block_is_egress_bound(block)) अणु
				NL_SET_ERR_MSG_MOD(extack, "Redirect action is not supported on egress");
				वापस -EOPNOTSUPP;
			पूर्ण

			/* Forbid block with this rulei to be bound
			 * to egress in future.
			 */
			rulei->egress_bind_blocker = 1;

			fid = mlxsw_sp_acl_dummy_fid(mlxsw_sp);
			fid_index = mlxsw_sp_fid_index(fid);
			err = mlxsw_sp_acl_rulei_act_fid_set(mlxsw_sp, rulei,
							     fid_index, extack);
			अगर (err)
				वापस err;

			out_dev = act->dev;
			err = mlxsw_sp_acl_rulei_act_fwd(mlxsw_sp, rulei,
							 out_dev, extack);
			अगर (err)
				वापस err;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_MIRRED: अणु
			काष्ठा net_device *out_dev = act->dev;

			अगर (mirror_act_count++) अणु
				NL_SET_ERR_MSG_MOD(extack, "Multiple mirror actions per rule are not supported");
				वापस -EOPNOTSUPP;
			पूर्ण

			err = mlxsw_sp_acl_rulei_act_mirror(mlxsw_sp, rulei,
							    block, out_dev,
							    extack);
			अगर (err)
				वापस err;
			पूर्ण
			अवरोध;
		हाल FLOW_ACTION_VLAN_MANGLE: अणु
			u16 proto = be16_to_cpu(act->vlan.proto);
			u8 prio = act->vlan.prio;
			u16 vid = act->vlan.vid;

			err = mlxsw_sp_acl_rulei_act_vlan(mlxsw_sp, rulei,
							  act->id, vid,
							  proto, prio, extack);
			अगर (err)
				वापस err;
			अवरोध;
			पूर्ण
		हाल FLOW_ACTION_PRIORITY:
			err = mlxsw_sp_acl_rulei_act_priority(mlxsw_sp, rulei,
							      act->priority,
							      extack);
			अगर (err)
				वापस err;
			अवरोध;
		हाल FLOW_ACTION_MANGLE: अणु
			क्रमागत flow_action_mangle_base htype = act->mangle.htype;
			__be32 be_mask = (__क्रमce __be32) act->mangle.mask;
			__be32 be_val = (__क्रमce __be32) act->mangle.val;
			u32 offset = act->mangle.offset;
			u32 mask = be32_to_cpu(be_mask);
			u32 val = be32_to_cpu(be_val);

			err = mlxsw_sp_acl_rulei_act_mangle(mlxsw_sp, rulei,
							    htype, offset,
							    mask, val, extack);
			अगर (err)
				वापस err;
			अवरोध;
			पूर्ण
		हाल FLOW_ACTION_POLICE: अणु
			u32 burst;

			अगर (police_act_count++) अणु
				NL_SET_ERR_MSG_MOD(extack, "Multiple police actions per rule are not supported");
				वापस -EOPNOTSUPP;
			पूर्ण

			अगर (act->police.rate_pkt_ps) अणु
				NL_SET_ERR_MSG_MOD(extack, "QoS offload not support packets per second");
				वापस -EOPNOTSUPP;
			पूर्ण

			/* The kernel might adjust the requested burst size so
			 * that it is not exactly a घातer of two. Re-adjust it
			 * here since the hardware only supports burst sizes
			 * that are a घातer of two.
			 */
			burst = roundup_घात_of_two(act->police.burst);
			err = mlxsw_sp_acl_rulei_act_police(mlxsw_sp, rulei,
							    act->police.index,
							    act->police.rate_bytes_ps,
							    burst, extack);
			अगर (err)
				वापस err;
			अवरोध;
			पूर्ण
		हाल FLOW_ACTION_SAMPLE: अणु
			अगर (sample_act_count++) अणु
				NL_SET_ERR_MSG_MOD(extack, "Multiple sample actions per rule are not supported");
				वापस -EOPNOTSUPP;
			पूर्ण

			err = mlxsw_sp_acl_rulei_act_sample(mlxsw_sp, rulei,
							    block,
							    act->sample.psample_group,
							    act->sample.rate,
							    act->sample.trunc_size,
							    act->sample.truncate,
							    extack);
			अगर (err)
				वापस err;
			अवरोध;
			पूर्ण
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported action");
			dev_err(mlxsw_sp->bus_info->dev, "Unsupported action\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_flower_parse_meta(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				      काष्ठा flow_cls_offload *f,
				      काष्ठा mlxsw_sp_flow_block *block)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	काष्ठा net_device *ingress_dev;
	काष्ठा flow_match_meta match;

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_META))
		वापस 0;

	flow_rule_match_meta(rule, &match);
	अगर (match.mask->ingress_अगरindex != 0xFFFFFFFF) अणु
		NL_SET_ERR_MSG_MOD(f->common.extack, "Unsupported ingress ifindex mask");
		वापस -EINVAL;
	पूर्ण

	ingress_dev = __dev_get_by_index(block->net,
					 match.key->ingress_अगरindex);
	अगर (!ingress_dev) अणु
		NL_SET_ERR_MSG_MOD(f->common.extack, "Can't find specified ingress port to match on");
		वापस -EINVAL;
	पूर्ण

	अगर (!mlxsw_sp_port_dev_check(ingress_dev)) अणु
		NL_SET_ERR_MSG_MOD(f->common.extack, "Can't match on non-mlxsw ingress port");
		वापस -EINVAL;
	पूर्ण

	mlxsw_sp_port = netdev_priv(ingress_dev);
	अगर (mlxsw_sp_port->mlxsw_sp != block->mlxsw_sp) अणु
		NL_SET_ERR_MSG_MOD(f->common.extack, "Can't match on a port from different device");
		वापस -EINVAL;
	पूर्ण

	mlxsw_sp_acl_rulei_keymask_u32(rulei,
				       MLXSW_AFK_ELEMENT_SRC_SYS_PORT,
				       mlxsw_sp_port->local_port,
				       0xFFFFFFFF);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_flower_parse_ipv4(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				       काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_match_ipv4_addrs match;

	flow_rule_match_ipv4_addrs(f->rule, &match);

	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_0_31,
				       (अक्षर *) &match.key->src,
				       (अक्षर *) &match.mask->src, 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_0_31,
				       (अक्षर *) &match.key->dst,
				       (अक्षर *) &match.mask->dst, 4);
पूर्ण

अटल व्योम mlxsw_sp_flower_parse_ipv6(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				       काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_match_ipv6_addrs match;

	flow_rule_match_ipv6_addrs(f->rule, &match);

	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_96_127,
				       &match.key->src.s6_addr[0x0],
				       &match.mask->src.s6_addr[0x0], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_64_95,
				       &match.key->src.s6_addr[0x4],
				       &match.mask->src.s6_addr[0x4], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_32_63,
				       &match.key->src.s6_addr[0x8],
				       &match.mask->src.s6_addr[0x8], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_SRC_IP_0_31,
				       &match.key->src.s6_addr[0xC],
				       &match.mask->src.s6_addr[0xC], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_96_127,
				       &match.key->dst.s6_addr[0x0],
				       &match.mask->dst.s6_addr[0x0], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_64_95,
				       &match.key->dst.s6_addr[0x4],
				       &match.mask->dst.s6_addr[0x4], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_32_63,
				       &match.key->dst.s6_addr[0x8],
				       &match.mask->dst.s6_addr[0x8], 4);
	mlxsw_sp_acl_rulei_keymask_buf(rulei, MLXSW_AFK_ELEMENT_DST_IP_0_31,
				       &match.key->dst.s6_addr[0xC],
				       &match.mask->dst.s6_addr[0xC], 4);
पूर्ण

अटल पूर्णांक mlxsw_sp_flower_parse_ports(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_acl_rule_info *rulei,
				       काष्ठा flow_cls_offload *f,
				       u8 ip_proto)
अणु
	स्थिर काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_match_ports match;

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS))
		वापस 0;

	अगर (ip_proto != IPPROTO_TCP && ip_proto != IPPROTO_UDP) अणु
		NL_SET_ERR_MSG_MOD(f->common.extack, "Only UDP and TCP keys are supported");
		dev_err(mlxsw_sp->bus_info->dev, "Only UDP and TCP keys are supported\n");
		वापस -EINVAL;
	पूर्ण

	flow_rule_match_ports(rule, &match);
	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_DST_L4_PORT,
				       ntohs(match.key->dst),
				       ntohs(match.mask->dst));
	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_SRC_L4_PORT,
				       ntohs(match.key->src),
				       ntohs(match.mask->src));
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_flower_parse_tcp(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_acl_rule_info *rulei,
				     काष्ठा flow_cls_offload *f,
				     u8 ip_proto)
अणु
	स्थिर काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_match_tcp match;

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_TCP))
		वापस 0;

	अगर (ip_proto != IPPROTO_TCP) अणु
		NL_SET_ERR_MSG_MOD(f->common.extack, "TCP keys supported only for TCP");
		dev_err(mlxsw_sp->bus_info->dev, "TCP keys supported only for TCP\n");
		वापस -EINVAL;
	पूर्ण

	flow_rule_match_tcp(rule, &match);

	अगर (match.mask->flags & htons(0x0E00)) अणु
		NL_SET_ERR_MSG_MOD(f->common.extack, "TCP flags match not supported on reserved bits");
		dev_err(mlxsw_sp->bus_info->dev, "TCP flags match not supported on reserved bits\n");
		वापस -EINVAL;
	पूर्ण

	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_TCP_FLAGS,
				       ntohs(match.key->flags),
				       ntohs(match.mask->flags));
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_flower_parse_ip(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_acl_rule_info *rulei,
				    काष्ठा flow_cls_offload *f,
				    u16 n_proto)
अणु
	स्थिर काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_match_ip match;

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IP))
		वापस 0;

	अगर (n_proto != ETH_P_IP && n_proto != ETH_P_IPV6) अणु
		NL_SET_ERR_MSG_MOD(f->common.extack, "IP keys supported only for IPv4/6");
		dev_err(mlxsw_sp->bus_info->dev, "IP keys supported only for IPv4/6\n");
		वापस -EINVAL;
	पूर्ण

	flow_rule_match_ip(rule, &match);

	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_IP_TTL_,
				       match.key->ttl, match.mask->ttl);

	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_IP_ECN,
				       match.key->tos & 0x3,
				       match.mask->tos & 0x3);

	mlxsw_sp_acl_rulei_keymask_u32(rulei, MLXSW_AFK_ELEMENT_IP_DSCP,
				       match.key->tos >> 2,
				       match.mask->tos >> 2);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_flower_parse(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_flow_block *block,
				 काष्ठा mlxsw_sp_acl_rule_info *rulei,
				 काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	u16 n_proto_mask = 0;
	u16 n_proto_key = 0;
	u16 addr_type = 0;
	u8 ip_proto = 0;
	पूर्णांक err;

	अगर (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_META) |
	      BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_TCP) |
	      BIT(FLOW_DISSECTOR_KEY_IP) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN))) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Unsupported key\n");
		NL_SET_ERR_MSG_MOD(f->common.extack, "Unsupported key");
		वापस -EOPNOTSUPP;
	पूर्ण

	mlxsw_sp_acl_rulei_priority(rulei, f->common.prio);

	err = mlxsw_sp_flower_parse_meta(rulei, f, block);
	अगर (err)
		वापस err;

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(rule, &match);
		addr_type = match.key->addr_type;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		n_proto_key = ntohs(match.key->n_proto);
		n_proto_mask = ntohs(match.mask->n_proto);

		अगर (n_proto_key == ETH_P_ALL) अणु
			n_proto_key = 0;
			n_proto_mask = 0;
		पूर्ण
		mlxsw_sp_acl_rulei_keymask_u32(rulei,
					       MLXSW_AFK_ELEMENT_ETHERTYPE,
					       n_proto_key, n_proto_mask);

		ip_proto = match.key->ip_proto;
		mlxsw_sp_acl_rulei_keymask_u32(rulei,
					       MLXSW_AFK_ELEMENT_IP_PROTO,
					       match.key->ip_proto,
					       match.mask->ip_proto);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		mlxsw_sp_acl_rulei_keymask_buf(rulei,
					       MLXSW_AFK_ELEMENT_DMAC_32_47,
					       match.key->dst,
					       match.mask->dst, 2);
		mlxsw_sp_acl_rulei_keymask_buf(rulei,
					       MLXSW_AFK_ELEMENT_DMAC_0_31,
					       match.key->dst + 2,
					       match.mask->dst + 2, 4);
		mlxsw_sp_acl_rulei_keymask_buf(rulei,
					       MLXSW_AFK_ELEMENT_SMAC_32_47,
					       match.key->src,
					       match.mask->src, 2);
		mlxsw_sp_acl_rulei_keymask_buf(rulei,
					       MLXSW_AFK_ELEMENT_SMAC_0_31,
					       match.key->src + 2,
					       match.mask->src + 2, 4);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		अगर (mlxsw_sp_flow_block_is_egress_bound(block)) अणु
			NL_SET_ERR_MSG_MOD(f->common.extack, "vlan_id key is not supported on egress");
			वापस -EOPNOTSUPP;
		पूर्ण

		/* Forbid block with this rulei to be bound
		 * to egress in future.
		 */
		rulei->egress_bind_blocker = 1;

		अगर (match.mask->vlan_id != 0)
			mlxsw_sp_acl_rulei_keymask_u32(rulei,
						       MLXSW_AFK_ELEMENT_VID,
						       match.key->vlan_id,
						       match.mask->vlan_id);
		अगर (match.mask->vlan_priority != 0)
			mlxsw_sp_acl_rulei_keymask_u32(rulei,
						       MLXSW_AFK_ELEMENT_PCP,
						       match.key->vlan_priority,
						       match.mask->vlan_priority);
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS)
		mlxsw_sp_flower_parse_ipv4(rulei, f);

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS)
		mlxsw_sp_flower_parse_ipv6(rulei, f);

	err = mlxsw_sp_flower_parse_ports(mlxsw_sp, rulei, f, ip_proto);
	अगर (err)
		वापस err;
	err = mlxsw_sp_flower_parse_tcp(mlxsw_sp, rulei, f, ip_proto);
	अगर (err)
		वापस err;

	err = mlxsw_sp_flower_parse_ip(mlxsw_sp, rulei, f, n_proto_key & n_proto_mask);
	अगर (err)
		वापस err;

	वापस mlxsw_sp_flower_parse_actions(mlxsw_sp, block, rulei,
					     &f->rule->action,
					     f->common.extack);
पूर्ण

अटल पूर्णांक mlxsw_sp_flower_mall_prio_check(काष्ठा mlxsw_sp_flow_block *block,
					   काष्ठा flow_cls_offload *f)
अणु
	bool ingress = mlxsw_sp_flow_block_is_ingress_bound(block);
	अचिन्हित पूर्णांक mall_min_prio;
	अचिन्हित पूर्णांक mall_max_prio;
	पूर्णांक err;

	err = mlxsw_sp_mall_prio_get(block, f->common.chain_index,
				     &mall_min_prio, &mall_max_prio);
	अगर (err) अणु
		अगर (err == -ENOENT)
			/* No matchall filters installed on this chain. */
			वापस 0;
		NL_SET_ERR_MSG(f->common.extack, "Failed to get matchall priorities");
		वापस err;
	पूर्ण
	अगर (ingress && f->common.prio <= mall_min_prio) अणु
		NL_SET_ERR_MSG(f->common.extack, "Failed to add in front of existing matchall rules");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (!ingress && f->common.prio >= mall_max_prio) अणु
		NL_SET_ERR_MSG(f->common.extack, "Failed to add behind of existing matchall rules");
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_flower_replace(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_flow_block *block,
			    काष्ठा flow_cls_offload *f)
अणु
	काष्ठा mlxsw_sp_acl_rule_info *rulei;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;
	काष्ठा mlxsw_sp_acl_rule *rule;
	पूर्णांक err;

	err = mlxsw_sp_flower_mall_prio_check(block, f);
	अगर (err)
		वापस err;

	ruleset = mlxsw_sp_acl_ruleset_get(mlxsw_sp, block,
					   f->common.chain_index,
					   MLXSW_SP_ACL_PROखाता_FLOWER, शून्य);
	अगर (IS_ERR(ruleset))
		वापस PTR_ERR(ruleset);

	rule = mlxsw_sp_acl_rule_create(mlxsw_sp, ruleset, f->cookie, शून्य,
					f->common.extack);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		जाओ err_rule_create;
	पूर्ण

	rulei = mlxsw_sp_acl_rule_rulei(rule);
	err = mlxsw_sp_flower_parse(mlxsw_sp, block, rulei, f);
	अगर (err)
		जाओ err_flower_parse;

	err = mlxsw_sp_acl_rulei_commit(rulei);
	अगर (err)
		जाओ err_rulei_commit;

	err = mlxsw_sp_acl_rule_add(mlxsw_sp, rule);
	अगर (err)
		जाओ err_rule_add;

	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
	वापस 0;

err_rule_add:
err_rulei_commit:
err_flower_parse:
	mlxsw_sp_acl_rule_destroy(mlxsw_sp, rule);
err_rule_create:
	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
	वापस err;
पूर्ण

व्योम mlxsw_sp_flower_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_flow_block *block,
			     काष्ठा flow_cls_offload *f)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;
	काष्ठा mlxsw_sp_acl_rule *rule;

	ruleset = mlxsw_sp_acl_ruleset_get(mlxsw_sp, block,
					   f->common.chain_index,
					   MLXSW_SP_ACL_PROखाता_FLOWER, शून्य);
	अगर (IS_ERR(ruleset))
		वापस;

	rule = mlxsw_sp_acl_rule_lookup(mlxsw_sp, ruleset, f->cookie);
	अगर (rule) अणु
		mlxsw_sp_acl_rule_del(mlxsw_sp, rule);
		mlxsw_sp_acl_rule_destroy(mlxsw_sp, rule);
	पूर्ण

	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
पूर्ण

पूर्णांक mlxsw_sp_flower_stats(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_flow_block *block,
			  काष्ठा flow_cls_offload *f)
अणु
	क्रमागत flow_action_hw_stats used_hw_stats = FLOW_ACTION_HW_STATS_DISABLED;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;
	काष्ठा mlxsw_sp_acl_rule *rule;
	u64 packets;
	u64 lastuse;
	u64 bytes;
	u64 drops;
	पूर्णांक err;

	ruleset = mlxsw_sp_acl_ruleset_get(mlxsw_sp, block,
					   f->common.chain_index,
					   MLXSW_SP_ACL_PROखाता_FLOWER, शून्य);
	अगर (WARN_ON(IS_ERR(ruleset)))
		वापस -EINVAL;

	rule = mlxsw_sp_acl_rule_lookup(mlxsw_sp, ruleset, f->cookie);
	अगर (!rule)
		वापस -EINVAL;

	err = mlxsw_sp_acl_rule_get_stats(mlxsw_sp, rule, &packets, &bytes,
					  &drops, &lastuse, &used_hw_stats);
	अगर (err)
		जाओ err_rule_get_stats;

	flow_stats_update(&f->stats, bytes, packets, drops, lastuse,
			  used_hw_stats);

	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
	वापस 0;

err_rule_get_stats:
	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_flower_पंचांगplt_create(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_flow_block *block,
				 काष्ठा flow_cls_offload *f)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;
	काष्ठा mlxsw_sp_acl_rule_info rulei;
	पूर्णांक err;

	स_रखो(&rulei, 0, माप(rulei));
	err = mlxsw_sp_flower_parse(mlxsw_sp, block, &rulei, f);
	अगर (err)
		वापस err;
	ruleset = mlxsw_sp_acl_ruleset_get(mlxsw_sp, block,
					   f->common.chain_index,
					   MLXSW_SP_ACL_PROखाता_FLOWER,
					   &rulei.values.elusage);

	/* keep the reference to the ruleset */
	वापस PTR_ERR_OR_ZERO(ruleset);
पूर्ण

व्योम mlxsw_sp_flower_पंचांगplt_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_flow_block *block,
				   काष्ठा flow_cls_offload *f)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;

	ruleset = mlxsw_sp_acl_ruleset_get(mlxsw_sp, block,
					   f->common.chain_index,
					   MLXSW_SP_ACL_PROखाता_FLOWER, शून्य);
	अगर (IS_ERR(ruleset))
		वापस;
	/* put the reference to the ruleset kept in create */
	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
	mlxsw_sp_acl_ruleset_put(mlxsw_sp, ruleset);
पूर्ण

पूर्णांक mlxsw_sp_flower_prio_get(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_flow_block *block,
			     u32 chain_index, अचिन्हित पूर्णांक *p_min_prio,
			     अचिन्हित पूर्णांक *p_max_prio)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;

	ruleset = mlxsw_sp_acl_ruleset_lookup(mlxsw_sp, block,
					      chain_index,
					      MLXSW_SP_ACL_PROखाता_FLOWER);
	अगर (IS_ERR(ruleset))
		/* In हाल there are no flower rules, the caller
		 * receives -ENOENT to indicate there is no need
		 * to check the priorities.
		 */
		वापस PTR_ERR(ruleset);
	mlxsw_sp_acl_ruleset_prio_get(ruleset, p_min_prio, p_max_prio);
	वापस 0;
पूर्ण
