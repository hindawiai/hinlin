<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/bitfield.h>
#समावेश <linux/mpls.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_csum.h>
#समावेश <net/tc_act/tc_gact.h>
#समावेश <net/tc_act/tc_mirred.h>
#समावेश <net/tc_act/tc_mpls.h>
#समावेश <net/tc_act/tc_pedit.h>
#समावेश <net/tc_act/tc_vlan.h>
#समावेश <net/tc_act/tc_tunnel_key.h>

#समावेश "cmsg.h"
#समावेश "main.h"
#समावेश "../nfp_net_repr.h"

/* The kernel versions of TUNNEL_* are not ABI and thereक्रमe vulnerable
 * to change. Such changes will अवरोध our FW ABI.
 */
#घोषणा NFP_FL_TUNNEL_CSUM			cpu_to_be16(0x01)
#घोषणा NFP_FL_TUNNEL_KEY			cpu_to_be16(0x04)
#घोषणा NFP_FL_TUNNEL_GENEVE_OPT		cpu_to_be16(0x0800)
#घोषणा NFP_FL_SUPPORTED_TUNNEL_INFO_FLAGS	(IP_TUNNEL_INFO_TX | \
						 IP_TUNNEL_INFO_IPV6)
#घोषणा NFP_FL_SUPPORTED_UDP_TUN_FLAGS		(NFP_FL_TUNNEL_CSUM | \
						 NFP_FL_TUNNEL_KEY | \
						 NFP_FL_TUNNEL_GENEVE_OPT)

अटल पूर्णांक
nfp_fl_push_mpls(काष्ठा nfp_fl_push_mpls *push_mpls,
		 स्थिर काष्ठा flow_action_entry *act,
		 काष्ठा netlink_ext_ack *extack)
अणु
	माप_प्रकार act_size = माप(काष्ठा nfp_fl_push_mpls);
	u32 mpls_lse = 0;

	push_mpls->head.jump_id = NFP_FL_ACTION_OPCODE_PUSH_MPLS;
	push_mpls->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	/* BOS is optional in the TC action but required क्रम offload. */
	अगर (act->mpls_push.bos != ACT_MPLS_BOS_NOT_SET) अणु
		mpls_lse |= act->mpls_push.bos << MPLS_LS_S_SHIFT;
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: BOS field must explicitly be set for MPLS push");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Leave MPLS TC as a शेष value of 0 अगर not explicitly set. */
	अगर (act->mpls_push.tc != ACT_MPLS_TC_NOT_SET)
		mpls_lse |= act->mpls_push.tc << MPLS_LS_TC_SHIFT;

	/* Proto, label and TTL are enक्रमced and verअगरied क्रम MPLS push. */
	mpls_lse |= act->mpls_push.label << MPLS_LS_LABEL_SHIFT;
	mpls_lse |= act->mpls_push.ttl << MPLS_LS_TTL_SHIFT;
	push_mpls->ethtype = act->mpls_push.proto;
	push_mpls->lse = cpu_to_be32(mpls_lse);

	वापस 0;
पूर्ण

अटल व्योम
nfp_fl_pop_mpls(काष्ठा nfp_fl_pop_mpls *pop_mpls,
		स्थिर काष्ठा flow_action_entry *act)
अणु
	माप_प्रकार act_size = माप(काष्ठा nfp_fl_pop_mpls);

	pop_mpls->head.jump_id = NFP_FL_ACTION_OPCODE_POP_MPLS;
	pop_mpls->head.len_lw = act_size >> NFP_FL_LW_SIZ;
	pop_mpls->ethtype = act->mpls_pop.proto;
पूर्ण

अटल व्योम
nfp_fl_set_mpls(काष्ठा nfp_fl_set_mpls *set_mpls,
		स्थिर काष्ठा flow_action_entry *act)
अणु
	माप_प्रकार act_size = माप(काष्ठा nfp_fl_set_mpls);
	u32 mpls_lse = 0, mpls_mask = 0;

	set_mpls->head.jump_id = NFP_FL_ACTION_OPCODE_SET_MPLS;
	set_mpls->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	अगर (act->mpls_mangle.label != ACT_MPLS_LABEL_NOT_SET) अणु
		mpls_lse |= act->mpls_mangle.label << MPLS_LS_LABEL_SHIFT;
		mpls_mask |= MPLS_LS_LABEL_MASK;
	पूर्ण
	अगर (act->mpls_mangle.tc != ACT_MPLS_TC_NOT_SET) अणु
		mpls_lse |= act->mpls_mangle.tc << MPLS_LS_TC_SHIFT;
		mpls_mask |= MPLS_LS_TC_MASK;
	पूर्ण
	अगर (act->mpls_mangle.bos != ACT_MPLS_BOS_NOT_SET) अणु
		mpls_lse |= act->mpls_mangle.bos << MPLS_LS_S_SHIFT;
		mpls_mask |= MPLS_LS_S_MASK;
	पूर्ण
	अगर (act->mpls_mangle.ttl) अणु
		mpls_lse |= act->mpls_mangle.ttl << MPLS_LS_TTL_SHIFT;
		mpls_mask |= MPLS_LS_TTL_MASK;
	पूर्ण

	set_mpls->lse = cpu_to_be32(mpls_lse);
	set_mpls->lse_mask = cpu_to_be32(mpls_mask);
पूर्ण

अटल व्योम nfp_fl_pop_vlan(काष्ठा nfp_fl_pop_vlan *pop_vlan)
अणु
	माप_प्रकार act_size = माप(काष्ठा nfp_fl_pop_vlan);

	pop_vlan->head.jump_id = NFP_FL_ACTION_OPCODE_POP_VLAN;
	pop_vlan->head.len_lw = act_size >> NFP_FL_LW_SIZ;
	pop_vlan->reserved = 0;
पूर्ण

अटल व्योम
nfp_fl_push_vlan(काष्ठा nfp_fl_push_vlan *push_vlan,
		 स्थिर काष्ठा flow_action_entry *act)
अणु
	माप_प्रकार act_size = माप(काष्ठा nfp_fl_push_vlan);
	u16 पंचांगp_push_vlan_tci;

	push_vlan->head.jump_id = NFP_FL_ACTION_OPCODE_PUSH_VLAN;
	push_vlan->head.len_lw = act_size >> NFP_FL_LW_SIZ;
	push_vlan->reserved = 0;
	push_vlan->vlan_tpid = act->vlan.proto;

	पंचांगp_push_vlan_tci =
		FIELD_PREP(NFP_FL_PUSH_VLAN_PRIO, act->vlan.prio) |
		FIELD_PREP(NFP_FL_PUSH_VLAN_VID, act->vlan.vid);
	push_vlan->vlan_tci = cpu_to_be16(पंचांगp_push_vlan_tci);
पूर्ण

अटल पूर्णांक
nfp_fl_pre_lag(काष्ठा nfp_app *app, स्थिर काष्ठा flow_action_entry *act,
	       काष्ठा nfp_fl_payload *nfp_flow, पूर्णांक act_len,
	       काष्ठा netlink_ext_ack *extack)
अणु
	माप_प्रकार act_size = माप(काष्ठा nfp_fl_pre_lag);
	काष्ठा nfp_fl_pre_lag *pre_lag;
	काष्ठा net_device *out_dev;
	पूर्णांक err;

	out_dev = act->dev;
	अगर (!out_dev || !netअगर_is_lag_master(out_dev))
		वापस 0;

	अगर (act_len + act_size > NFP_FL_MAX_A_SIZ) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at LAG action");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Pre_lag action must be first on action list.
	 * If other actions alपढ़ोy exist they need pushed क्रमward.
	 */
	अगर (act_len)
		स_हटाओ(nfp_flow->action_data + act_size,
			nfp_flow->action_data, act_len);

	pre_lag = (काष्ठा nfp_fl_pre_lag *)nfp_flow->action_data;
	err = nfp_flower_lag_populate_pre_action(app, out_dev, pre_lag, extack);
	अगर (err)
		वापस err;

	pre_lag->head.jump_id = NFP_FL_ACTION_OPCODE_PRE_LAG;
	pre_lag->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	nfp_flow->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_शून्य);

	वापस act_size;
पूर्ण

अटल पूर्णांक
nfp_fl_output(काष्ठा nfp_app *app, काष्ठा nfp_fl_output *output,
	      स्थिर काष्ठा flow_action_entry *act,
	      काष्ठा nfp_fl_payload *nfp_flow,
	      bool last, काष्ठा net_device *in_dev,
	      क्रमागत nfp_flower_tun_type tun_type, पूर्णांक *tun_out_cnt,
	      bool pkt_host, काष्ठा netlink_ext_ack *extack)
अणु
	माप_प्रकार act_size = माप(काष्ठा nfp_fl_output);
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा net_device *out_dev;
	u16 पंचांगp_flags;

	output->head.jump_id = NFP_FL_ACTION_OPCODE_OUTPUT;
	output->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	out_dev = act->dev;
	अगर (!out_dev) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid egress interface for mirred action");
		वापस -EOPNOTSUPP;
	पूर्ण

	पंचांगp_flags = last ? NFP_FL_OUT_FLAGS_LAST : 0;

	अगर (tun_type) अणु
		/* Verअगरy the egress netdev matches the tunnel type. */
		अगर (!nfp_fl_netdev_is_tunnel_type(out_dev, tun_type)) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: egress interface does not match the required tunnel type");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (*tun_out_cnt) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: cannot offload more than one tunnel mirred output per filter");
			वापस -EOPNOTSUPP;
		पूर्ण
		(*tun_out_cnt)++;

		output->flags = cpu_to_be16(पंचांगp_flags |
					    NFP_FL_OUT_FLAGS_USE_TUN);
		output->port = cpu_to_be32(NFP_FL_PORT_TYPE_TUN | tun_type);
	पूर्ण अन्यथा अगर (netअगर_is_lag_master(out_dev) &&
		   priv->flower_en_feats & NFP_FL_ENABLE_LAG) अणु
		पूर्णांक gid;

		output->flags = cpu_to_be16(पंचांगp_flags);
		gid = nfp_flower_lag_get_output_id(app, out_dev);
		अगर (gid < 0) अणु
			NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot find group id for LAG action");
			वापस gid;
		पूर्ण
		output->port = cpu_to_be32(NFP_FL_LAG_OUT | gid);
	पूर्ण अन्यथा अगर (nfp_flower_पूर्णांकernal_port_can_offload(app, out_dev)) अणु
		अगर (!(priv->flower_ext_feats & NFP_FL_FEATS_PRE_TUN_RULES)) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: pre-tunnel rules not supported in loaded firmware");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (nfp_flow->pre_tun_rule.dev || !pkt_host) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: pre-tunnel rules require single egress dev and ptype HOST action");
			वापस -EOPNOTSUPP;
		पूर्ण

		nfp_flow->pre_tun_rule.dev = out_dev;

		वापस 0;
	पूर्ण अन्यथा अणु
		/* Set action output parameters. */
		output->flags = cpu_to_be16(पंचांगp_flags);

		अगर (nfp_netdev_is_nfp_repr(in_dev)) अणु
			/* Confirm ingress and egress are on same device. */
			अगर (!netdev_port_same_parent_id(in_dev, out_dev)) अणु
				NL_SET_ERR_MSG_MOD(extack, "unsupported offload: ingress and egress interfaces are on different devices");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण

		अगर (!nfp_netdev_is_nfp_repr(out_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: egress interface is not an nfp port");
			वापस -EOPNOTSUPP;
		पूर्ण

		output->port = cpu_to_be32(nfp_repr_get_port_id(out_dev));
		अगर (!output->port) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid port id for egress interface");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	nfp_flow->meta.लघुcut = output->port;

	वापस 0;
पूर्ण

अटल bool
nfp_flower_tun_is_gre(काष्ठा flow_cls_offload *flow, पूर्णांक start_idx)
अणु
	काष्ठा flow_action_entry *act = flow->rule->action.entries;
	पूर्णांक num_act = flow->rule->action.num_entries;
	पूर्णांक act_idx;

	/* Preparse action list क्रम next mirred or redirect action */
	क्रम (act_idx = start_idx + 1; act_idx < num_act; act_idx++)
		अगर (act[act_idx].id == FLOW_ACTION_REसूचीECT ||
		    act[act_idx].id == FLOW_ACTION_MIRRED)
			वापस netअगर_is_gretap(act[act_idx].dev);

	वापस false;
पूर्ण

अटल क्रमागत nfp_flower_tun_type
nfp_fl_get_tun_from_act(काष्ठा nfp_app *app,
			काष्ठा flow_cls_offload *flow,
			स्थिर काष्ठा flow_action_entry *act, पूर्णांक act_idx)
अणु
	स्थिर काष्ठा ip_tunnel_info *tun = act->tunnel;
	काष्ठा nfp_flower_priv *priv = app->priv;

	/* Determine the tunnel type based on the egress netdev
	 * in the mirred action क्रम tunnels without l4.
	 */
	अगर (nfp_flower_tun_is_gre(flow, act_idx))
		वापस NFP_FL_TUNNEL_GRE;

	चयन (tun->key.tp_dst) अणु
	हाल htons(IANA_VXLAN_UDP_PORT):
		वापस NFP_FL_TUNNEL_VXLAN;
	हाल htons(GENEVE_UDP_PORT):
		अगर (priv->flower_ext_feats & NFP_FL_FEATS_GENEVE)
			वापस NFP_FL_TUNNEL_GENEVE;
		fallthrough;
	शेष:
		वापस NFP_FL_TUNNEL_NONE;
	पूर्ण
पूर्ण

अटल काष्ठा nfp_fl_pre_tunnel *nfp_fl_pre_tunnel(अक्षर *act_data, पूर्णांक act_len)
अणु
	माप_प्रकार act_size = माप(काष्ठा nfp_fl_pre_tunnel);
	काष्ठा nfp_fl_pre_tunnel *pre_tun_act;

	/* Pre_tunnel action must be first on action list.
	 * If other actions alपढ़ोy exist they need to be pushed क्रमward.
	 */
	अगर (act_len)
		स_हटाओ(act_data + act_size, act_data, act_len);

	pre_tun_act = (काष्ठा nfp_fl_pre_tunnel *)act_data;

	स_रखो(pre_tun_act, 0, act_size);

	pre_tun_act->head.jump_id = NFP_FL_ACTION_OPCODE_PRE_TUNNEL;
	pre_tun_act->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	वापस pre_tun_act;
पूर्ण

अटल पूर्णांक
nfp_fl_push_geneve_options(काष्ठा nfp_fl_payload *nfp_fl, पूर्णांक *list_len,
			   स्थिर काष्ठा flow_action_entry *act,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel_info *ip_tun = (काष्ठा ip_tunnel_info *)act->tunnel;
	पूर्णांक opt_len, opt_cnt, act_start, tot_push_len;
	u8 *src = ip_tunnel_info_opts(ip_tun);

	/* We need to populate the options in reverse order क्रम HW.
	 * Thereक्रमe we go through the options, calculating the
	 * number of options and the total size, then we populate
	 * them in reverse order in the action list.
	 */
	opt_cnt = 0;
	tot_push_len = 0;
	opt_len = ip_tun->options_len;
	जबतक (opt_len > 0) अणु
		काष्ठा geneve_opt *opt = (काष्ठा geneve_opt *)src;

		opt_cnt++;
		अगर (opt_cnt > NFP_FL_MAX_GENEVE_OPT_CNT) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed number of geneve options exceeded");
			वापस -EOPNOTSUPP;
		पूर्ण

		tot_push_len += माप(काष्ठा nfp_fl_push_geneve) +
			       opt->length * 4;
		अगर (tot_push_len > NFP_FL_MAX_GENEVE_OPT_ACT) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at push geneve options");
			वापस -EOPNOTSUPP;
		पूर्ण

		opt_len -= माप(काष्ठा geneve_opt) + opt->length * 4;
		src += माप(काष्ठा geneve_opt) + opt->length * 4;
	पूर्ण

	अगर (*list_len + tot_push_len > NFP_FL_MAX_A_SIZ) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at push geneve options");
		वापस -EOPNOTSUPP;
	पूर्ण

	act_start = *list_len;
	*list_len += tot_push_len;
	src = ip_tunnel_info_opts(ip_tun);
	जबतक (opt_cnt) अणु
		काष्ठा geneve_opt *opt = (काष्ठा geneve_opt *)src;
		काष्ठा nfp_fl_push_geneve *push;
		माप_प्रकार act_size, len;

		opt_cnt--;
		act_size = माप(काष्ठा nfp_fl_push_geneve) + opt->length * 4;
		tot_push_len -= act_size;
		len = act_start + tot_push_len;

		push = (काष्ठा nfp_fl_push_geneve *)&nfp_fl->action_data[len];
		push->head.jump_id = NFP_FL_ACTION_OPCODE_PUSH_GENEVE;
		push->head.len_lw = act_size >> NFP_FL_LW_SIZ;
		push->reserved = 0;
		push->class = opt->opt_class;
		push->type = opt->type;
		push->length = opt->length;
		स_नकल(&push->opt_data, opt->opt_data, opt->length * 4);

		src += माप(काष्ठा geneve_opt) + opt->length * 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_fl_set_tun(काष्ठा nfp_app *app, काष्ठा nfp_fl_set_tun *set_tun,
	       स्थिर काष्ठा flow_action_entry *act,
	       काष्ठा nfp_fl_pre_tunnel *pre_tun,
	       क्रमागत nfp_flower_tun_type tun_type,
	       काष्ठा net_device *netdev, काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा ip_tunnel_info *ip_tun = act->tunnel;
	bool ipv6 = ip_tunnel_info_af(ip_tun) == AF_INET6;
	माप_प्रकार act_size = माप(काष्ठा nfp_fl_set_tun);
	काष्ठा nfp_flower_priv *priv = app->priv;
	u32 पंचांगp_set_ip_tun_type_index = 0;
	/* Currently support one pre-tunnel so index is always 0. */
	पूर्णांक pretun_idx = 0;

	अगर (!IS_ENABLED(CONFIG_IPV6) && ipv6)
		वापस -EOPNOTSUPP;

	अगर (ipv6 && !(priv->flower_ext_feats & NFP_FL_FEATS_IPV6_TUN))
		वापस -EOPNOTSUPP;

	BUILD_BUG_ON(NFP_FL_TUNNEL_CSUM != TUNNEL_CSUM ||
		     NFP_FL_TUNNEL_KEY	!= TUNNEL_KEY ||
		     NFP_FL_TUNNEL_GENEVE_OPT != TUNNEL_GENEVE_OPT);
	अगर (ip_tun->options_len &&
	    (tun_type != NFP_FL_TUNNEL_GENEVE ||
	    !(priv->flower_ext_feats & NFP_FL_FEATS_GENEVE_OPT))) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: loaded firmware does not support geneve options offload");
		वापस -EOPNOTSUPP;
	पूर्ण

	set_tun->head.jump_id = NFP_FL_ACTION_OPCODE_SET_TUNNEL;
	set_tun->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	/* Set tunnel type and pre-tunnel index. */
	पंचांगp_set_ip_tun_type_index |=
		FIELD_PREP(NFP_FL_TUNNEL_TYPE, tun_type) |
		FIELD_PREP(NFP_FL_PRE_TUN_INDEX, pretun_idx);

	set_tun->tun_type_index = cpu_to_be32(पंचांगp_set_ip_tun_type_index);
	set_tun->tun_id = ip_tun->key.tun_id;

	अगर (ip_tun->key.ttl) अणु
		set_tun->ttl = ip_tun->key.ttl;
#अगर_घोषित CONFIG_IPV6
	पूर्ण अन्यथा अगर (ipv6) अणु
		काष्ठा net *net = dev_net(netdev);
		काष्ठा flowi6 flow = अणुपूर्ण;
		काष्ठा dst_entry *dst;

		flow.daddr = ip_tun->key.u.ipv6.dst;
		flow.flowi4_proto = IPPROTO_UDP;
		dst = ipv6_stub->ipv6_dst_lookup_flow(net, शून्य, &flow, शून्य);
		अगर (!IS_ERR(dst)) अणु
			set_tun->ttl = ip6_dst_hoplimit(dst);
			dst_release(dst);
		पूर्ण अन्यथा अणु
			set_tun->ttl = net->ipv6.devconf_all->hop_limit;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		काष्ठा net *net = dev_net(netdev);
		काष्ठा flowi4 flow = अणुपूर्ण;
		काष्ठा rtable *rt;
		पूर्णांक err;

		/* Do a route lookup to determine ttl - अगर fails then use
		 * शेष. Note that CONFIG_INET is a requirement of
		 * CONFIG_NET_SWITCHDEV so must be defined here.
		 */
		flow.daddr = ip_tun->key.u.ipv4.dst;
		flow.flowi4_proto = IPPROTO_UDP;
		rt = ip_route_output_key(net, &flow);
		err = PTR_ERR_OR_ZERO(rt);
		अगर (!err) अणु
			set_tun->ttl = ip4_dst_hoplimit(&rt->dst);
			ip_rt_put(rt);
		पूर्ण अन्यथा अणु
			set_tun->ttl = net->ipv4.sysctl_ip_शेष_ttl;
		पूर्ण
	पूर्ण

	set_tun->tos = ip_tun->key.tos;

	अगर (!(ip_tun->key.tun_flags & NFP_FL_TUNNEL_KEY) ||
	    ip_tun->key.tun_flags & ~NFP_FL_SUPPORTED_UDP_TUN_FLAGS) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: loaded firmware does not support tunnel flag offload");
		वापस -EOPNOTSUPP;
	पूर्ण
	set_tun->tun_flags = ip_tun->key.tun_flags;

	अगर (tun_type == NFP_FL_TUNNEL_GENEVE) अणु
		set_tun->tun_proto = htons(ETH_P_TEB);
		set_tun->tun_len = ip_tun->options_len / 4;
	पूर्ण

	/* Complete pre_tunnel action. */
	अगर (ipv6) अणु
		pre_tun->flags |= cpu_to_be16(NFP_FL_PRE_TUN_IPV6);
		pre_tun->ipv6_dst = ip_tun->key.u.ipv6.dst;
	पूर्ण अन्यथा अणु
		pre_tun->ipv4_dst = ip_tun->key.u.ipv4.dst;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nfp_fl_set_helper32(u32 value, u32 mask, u8 *p_exact, u8 *p_mask)
अणु
	u32 oldvalue = get_unaligned((u32 *)p_exact);
	u32 oldmask = get_unaligned((u32 *)p_mask);

	value &= mask;
	value |= oldvalue & ~mask;

	put_unaligned(oldmask | mask, (u32 *)p_mask);
	put_unaligned(value, (u32 *)p_exact);
पूर्ण

अटल पूर्णांक
nfp_fl_set_eth(स्थिर काष्ठा flow_action_entry *act, u32 off,
	       काष्ठा nfp_fl_set_eth *set_eth, काष्ठा netlink_ext_ack *extack)
अणु
	u32 exact, mask;

	अगर (off + 4 > ETH_ALEN * 2) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit ethernet action");
		वापस -EOPNOTSUPP;
	पूर्ण

	mask = ~act->mangle.mask;
	exact = act->mangle.val;

	अगर (exact & ~mask) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit ethernet action");
		वापस -EOPNOTSUPP;
	पूर्ण

	nfp_fl_set_helper32(exact, mask, &set_eth->eth_addr_val[off],
			    &set_eth->eth_addr_mask[off]);

	set_eth->reserved = cpu_to_be16(0);
	set_eth->head.jump_id = NFP_FL_ACTION_OPCODE_SET_ETHERNET;
	set_eth->head.len_lw = माप(*set_eth) >> NFP_FL_LW_SIZ;

	वापस 0;
पूर्ण

काष्ठा ipv4_ttl_word अणु
	__u8	ttl;
	__u8	protocol;
	__sum16	check;
पूर्ण;

अटल पूर्णांक
nfp_fl_set_ip4(स्थिर काष्ठा flow_action_entry *act, u32 off,
	       काष्ठा nfp_fl_set_ip4_addrs *set_ip_addr,
	       काष्ठा nfp_fl_set_ip4_ttl_tos *set_ip_ttl_tos,
	       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ipv4_ttl_word *ttl_word_mask;
	काष्ठा ipv4_ttl_word *ttl_word;
	काष्ठा iphdr *tos_word_mask;
	काष्ठा iphdr *tos_word;
	__be32 exact, mask;

	/* We are expecting tcf_pedit to वापस a big endian value */
	mask = (__क्रमce __be32)~act->mangle.mask;
	exact = (__क्रमce __be32)act->mangle.val;

	अगर (exact & ~mask) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit IPv4 action");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (off) अणु
	हाल दुरत्व(काष्ठा iphdr, daddr):
		set_ip_addr->ipv4_dst_mask |= mask;
		set_ip_addr->ipv4_dst &= ~mask;
		set_ip_addr->ipv4_dst |= exact & mask;
		set_ip_addr->head.jump_id = NFP_FL_ACTION_OPCODE_SET_IPV4_ADDRS;
		set_ip_addr->head.len_lw = माप(*set_ip_addr) >>
					   NFP_FL_LW_SIZ;
		अवरोध;
	हाल दुरत्व(काष्ठा iphdr, saddr):
		set_ip_addr->ipv4_src_mask |= mask;
		set_ip_addr->ipv4_src &= ~mask;
		set_ip_addr->ipv4_src |= exact & mask;
		set_ip_addr->head.jump_id = NFP_FL_ACTION_OPCODE_SET_IPV4_ADDRS;
		set_ip_addr->head.len_lw = माप(*set_ip_addr) >>
					   NFP_FL_LW_SIZ;
		अवरोध;
	हाल दुरत्व(काष्ठा iphdr, ttl):
		ttl_word_mask = (काष्ठा ipv4_ttl_word *)&mask;
		ttl_word = (काष्ठा ipv4_ttl_word *)&exact;

		अगर (ttl_word_mask->protocol || ttl_word_mask->check) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit IPv4 ttl action");
			वापस -EOPNOTSUPP;
		पूर्ण

		set_ip_ttl_tos->ipv4_ttl_mask |= ttl_word_mask->ttl;
		set_ip_ttl_tos->ipv4_ttl &= ~ttl_word_mask->ttl;
		set_ip_ttl_tos->ipv4_ttl |= ttl_word->ttl & ttl_word_mask->ttl;
		set_ip_ttl_tos->head.jump_id =
			NFP_FL_ACTION_OPCODE_SET_IPV4_TTL_TOS;
		set_ip_ttl_tos->head.len_lw = माप(*set_ip_ttl_tos) >>
					      NFP_FL_LW_SIZ;
		अवरोध;
	हाल round_करोwn(दुरत्व(काष्ठा iphdr, tos), 4):
		tos_word_mask = (काष्ठा iphdr *)&mask;
		tos_word = (काष्ठा iphdr *)&exact;

		अगर (tos_word_mask->version || tos_word_mask->ihl ||
		    tos_word_mask->tot_len) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit IPv4 tos action");
			वापस -EOPNOTSUPP;
		पूर्ण

		set_ip_ttl_tos->ipv4_tos_mask |= tos_word_mask->tos;
		set_ip_ttl_tos->ipv4_tos &= ~tos_word_mask->tos;
		set_ip_ttl_tos->ipv4_tos |= tos_word->tos & tos_word_mask->tos;
		set_ip_ttl_tos->head.jump_id =
			NFP_FL_ACTION_OPCODE_SET_IPV4_TTL_TOS;
		set_ip_ttl_tos->head.len_lw = माप(*set_ip_ttl_tos) >>
					      NFP_FL_LW_SIZ;
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: pedit on unsupported section of IPv4 header");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nfp_fl_set_ip6_helper(पूर्णांक opcode_tag, u8 word, __be32 exact, __be32 mask,
		      काष्ठा nfp_fl_set_ipv6_addr *ip6)
अणु
	ip6->ipv6[word].mask |= mask;
	ip6->ipv6[word].exact &= ~mask;
	ip6->ipv6[word].exact |= exact & mask;

	ip6->reserved = cpu_to_be16(0);
	ip6->head.jump_id = opcode_tag;
	ip6->head.len_lw = माप(*ip6) >> NFP_FL_LW_SIZ;
पूर्ण

काष्ठा ipv6_hop_limit_word अणु
	__be16 payload_len;
	u8 nexthdr;
	u8 hop_limit;
पूर्ण;

अटल पूर्णांक
nfp_fl_set_ip6_hop_limit_flow_label(u32 off, __be32 exact, __be32 mask,
				    काष्ठा nfp_fl_set_ipv6_tc_hl_fl *ip_hl_fl,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ipv6_hop_limit_word *fl_hl_mask;
	काष्ठा ipv6_hop_limit_word *fl_hl;

	चयन (off) अणु
	हाल दुरत्व(काष्ठा ipv6hdr, payload_len):
		fl_hl_mask = (काष्ठा ipv6_hop_limit_word *)&mask;
		fl_hl = (काष्ठा ipv6_hop_limit_word *)&exact;

		अगर (fl_hl_mask->nexthdr || fl_hl_mask->payload_len) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit IPv6 hop limit action");
			वापस -EOPNOTSUPP;
		पूर्ण

		ip_hl_fl->ipv6_hop_limit_mask |= fl_hl_mask->hop_limit;
		ip_hl_fl->ipv6_hop_limit &= ~fl_hl_mask->hop_limit;
		ip_hl_fl->ipv6_hop_limit |= fl_hl->hop_limit &
					    fl_hl_mask->hop_limit;
		अवरोध;
	हाल round_करोwn(दुरत्व(काष्ठा ipv6hdr, flow_lbl), 4):
		अगर (mask & ~IPV6_FLOW_LABEL_MASK ||
		    exact & ~IPV6_FLOW_LABEL_MASK) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit IPv6 flow label action");
			वापस -EOPNOTSUPP;
		पूर्ण

		ip_hl_fl->ipv6_label_mask |= mask;
		ip_hl_fl->ipv6_label &= ~mask;
		ip_hl_fl->ipv6_label |= exact & mask;
		अवरोध;
	पूर्ण

	ip_hl_fl->head.jump_id = NFP_FL_ACTION_OPCODE_SET_IPV6_TC_HL_FL;
	ip_hl_fl->head.len_lw = माप(*ip_hl_fl) >> NFP_FL_LW_SIZ;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_fl_set_ip6(स्थिर काष्ठा flow_action_entry *act, u32 off,
	       काष्ठा nfp_fl_set_ipv6_addr *ip_dst,
	       काष्ठा nfp_fl_set_ipv6_addr *ip_src,
	       काष्ठा nfp_fl_set_ipv6_tc_hl_fl *ip_hl_fl,
	       काष्ठा netlink_ext_ack *extack)
अणु
	__be32 exact, mask;
	पूर्णांक err = 0;
	u8 word;

	/* We are expecting tcf_pedit to वापस a big endian value */
	mask = (__क्रमce __be32)~act->mangle.mask;
	exact = (__क्रमce __be32)act->mangle.val;

	अगर (exact & ~mask) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit IPv6 action");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (off < दुरत्व(काष्ठा ipv6hdr, saddr)) अणु
		err = nfp_fl_set_ip6_hop_limit_flow_label(off, exact, mask,
							  ip_hl_fl, extack);
	पूर्ण अन्यथा अगर (off < दुरत्व(काष्ठा ipv6hdr, daddr)) अणु
		word = (off - दुरत्व(काष्ठा ipv6hdr, saddr)) / माप(exact);
		nfp_fl_set_ip6_helper(NFP_FL_ACTION_OPCODE_SET_IPV6_SRC, word,
				      exact, mask, ip_src);
	पूर्ण अन्यथा अगर (off < दुरत्व(काष्ठा ipv6hdr, daddr) +
		       माप(काष्ठा in6_addr)) अणु
		word = (off - दुरत्व(काष्ठा ipv6hdr, daddr)) / माप(exact);
		nfp_fl_set_ip6_helper(NFP_FL_ACTION_OPCODE_SET_IPV6_DST, word,
				      exact, mask, ip_dst);
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: pedit on unsupported section of IPv6 header");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
nfp_fl_set_tport(स्थिर काष्ठा flow_action_entry *act, u32 off,
		 काष्ठा nfp_fl_set_tport *set_tport, पूर्णांक opcode,
		 काष्ठा netlink_ext_ack *extack)
अणु
	u32 exact, mask;

	अगर (off) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: pedit on unsupported section of L4 header");
		वापस -EOPNOTSUPP;
	पूर्ण

	mask = ~act->mangle.mask;
	exact = act->mangle.val;

	अगर (exact & ~mask) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid pedit L4 action");
		वापस -EOPNOTSUPP;
	पूर्ण

	nfp_fl_set_helper32(exact, mask, set_tport->tp_port_val,
			    set_tport->tp_port_mask);

	set_tport->reserved = cpu_to_be16(0);
	set_tport->head.jump_id = opcode;
	set_tport->head.len_lw = माप(*set_tport) >> NFP_FL_LW_SIZ;

	वापस 0;
पूर्ण

अटल u32 nfp_fl_csum_l4_to_flag(u8 ip_proto)
अणु
	चयन (ip_proto) अणु
	हाल 0:
		/* Filter करोesn't क्रमce proto match,
		 * both TCP and UDP will be updated अगर encountered
		 */
		वापस TCA_CSUM_UPDATE_FLAG_TCP | TCA_CSUM_UPDATE_FLAG_UDP;
	हाल IPPROTO_TCP:
		वापस TCA_CSUM_UPDATE_FLAG_TCP;
	हाल IPPROTO_UDP:
		वापस TCA_CSUM_UPDATE_FLAG_UDP;
	शेष:
		/* All other protocols will be ignored by FW */
		वापस 0;
	पूर्ण
पूर्ण

काष्ठा nfp_flower_pedit_acts अणु
	काष्ठा nfp_fl_set_ipv6_addr set_ip6_dst, set_ip6_src;
	काष्ठा nfp_fl_set_ipv6_tc_hl_fl set_ip6_tc_hl_fl;
	काष्ठा nfp_fl_set_ip4_ttl_tos set_ip_ttl_tos;
	काष्ठा nfp_fl_set_ip4_addrs set_ip_addr;
	काष्ठा nfp_fl_set_tport set_tport;
	काष्ठा nfp_fl_set_eth set_eth;
पूर्ण;

अटल पूर्णांक
nfp_fl_commit_mangle(काष्ठा flow_cls_offload *flow, अक्षर *nfp_action,
		     पूर्णांक *a_len, काष्ठा nfp_flower_pedit_acts *set_act,
		     u32 *csum_updated)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(flow);
	माप_प्रकार act_size = 0;
	u8 ip_proto = 0;

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		ip_proto = match.key->ip_proto;
	पूर्ण

	अगर (set_act->set_eth.head.len_lw) अणु
		act_size = माप(set_act->set_eth);
		स_नकल(nfp_action, &set_act->set_eth, act_size);
		*a_len += act_size;
	पूर्ण

	अगर (set_act->set_ip_ttl_tos.head.len_lw) अणु
		nfp_action += act_size;
		act_size = माप(set_act->set_ip_ttl_tos);
		स_नकल(nfp_action, &set_act->set_ip_ttl_tos, act_size);
		*a_len += act_size;

		/* Hardware will स्वतःmatically fix IPv4 and TCP/UDP checksum. */
		*csum_updated |= TCA_CSUM_UPDATE_FLAG_IPV4HDR |
				nfp_fl_csum_l4_to_flag(ip_proto);
	पूर्ण

	अगर (set_act->set_ip_addr.head.len_lw) अणु
		nfp_action += act_size;
		act_size = माप(set_act->set_ip_addr);
		स_नकल(nfp_action, &set_act->set_ip_addr, act_size);
		*a_len += act_size;

		/* Hardware will स्वतःmatically fix IPv4 and TCP/UDP checksum. */
		*csum_updated |= TCA_CSUM_UPDATE_FLAG_IPV4HDR |
				nfp_fl_csum_l4_to_flag(ip_proto);
	पूर्ण

	अगर (set_act->set_ip6_tc_hl_fl.head.len_lw) अणु
		nfp_action += act_size;
		act_size = माप(set_act->set_ip6_tc_hl_fl);
		स_नकल(nfp_action, &set_act->set_ip6_tc_hl_fl, act_size);
		*a_len += act_size;

		/* Hardware will स्वतःmatically fix TCP/UDP checksum. */
		*csum_updated |= nfp_fl_csum_l4_to_flag(ip_proto);
	पूर्ण

	अगर (set_act->set_ip6_dst.head.len_lw &&
	    set_act->set_ip6_src.head.len_lw) अणु
		/* TC compiles set src and dst IPv6 address as a single action,
		 * the hardware requires this to be 2 separate actions.
		 */
		nfp_action += act_size;
		act_size = माप(set_act->set_ip6_src);
		स_नकल(nfp_action, &set_act->set_ip6_src, act_size);
		*a_len += act_size;

		act_size = माप(set_act->set_ip6_dst);
		स_नकल(&nfp_action[माप(set_act->set_ip6_src)],
		       &set_act->set_ip6_dst, act_size);
		*a_len += act_size;

		/* Hardware will स्वतःmatically fix TCP/UDP checksum. */
		*csum_updated |= nfp_fl_csum_l4_to_flag(ip_proto);
	पूर्ण अन्यथा अगर (set_act->set_ip6_dst.head.len_lw) अणु
		nfp_action += act_size;
		act_size = माप(set_act->set_ip6_dst);
		स_नकल(nfp_action, &set_act->set_ip6_dst, act_size);
		*a_len += act_size;

		/* Hardware will स्वतःmatically fix TCP/UDP checksum. */
		*csum_updated |= nfp_fl_csum_l4_to_flag(ip_proto);
	पूर्ण अन्यथा अगर (set_act->set_ip6_src.head.len_lw) अणु
		nfp_action += act_size;
		act_size = माप(set_act->set_ip6_src);
		स_नकल(nfp_action, &set_act->set_ip6_src, act_size);
		*a_len += act_size;

		/* Hardware will स्वतःmatically fix TCP/UDP checksum. */
		*csum_updated |= nfp_fl_csum_l4_to_flag(ip_proto);
	पूर्ण
	अगर (set_act->set_tport.head.len_lw) अणु
		nfp_action += act_size;
		act_size = माप(set_act->set_tport);
		स_नकल(nfp_action, &set_act->set_tport, act_size);
		*a_len += act_size;

		/* Hardware will स्वतःmatically fix TCP/UDP checksum. */
		*csum_updated |= nfp_fl_csum_l4_to_flag(ip_proto);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_fl_pedit(स्थिर काष्ठा flow_action_entry *act,
	     काष्ठा flow_cls_offload *flow, अक्षर *nfp_action, पूर्णांक *a_len,
	     u32 *csum_updated, काष्ठा nfp_flower_pedit_acts *set_act,
	     काष्ठा netlink_ext_ack *extack)
अणु
	क्रमागत flow_action_mangle_base htype;
	u32 offset;

	htype = act->mangle.htype;
	offset = act->mangle.offset;

	चयन (htype) अणु
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_ETH:
		वापस nfp_fl_set_eth(act, offset, &set_act->set_eth, extack);
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_IP4:
		वापस nfp_fl_set_ip4(act, offset, &set_act->set_ip_addr,
				      &set_act->set_ip_ttl_tos, extack);
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_IP6:
		वापस nfp_fl_set_ip6(act, offset, &set_act->set_ip6_dst,
				      &set_act->set_ip6_src,
				      &set_act->set_ip6_tc_hl_fl, extack);
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_TCP:
		वापस nfp_fl_set_tport(act, offset, &set_act->set_tport,
					NFP_FL_ACTION_OPCODE_SET_TCP, extack);
	हाल TCA_PEDIT_KEY_EX_HDR_TYPE_UDP:
		वापस nfp_fl_set_tport(act, offset, &set_act->set_tport,
					NFP_FL_ACTION_OPCODE_SET_UDP, extack);
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: pedit on unsupported header");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक
nfp_flower_output_action(काष्ठा nfp_app *app,
			 स्थिर काष्ठा flow_action_entry *act,
			 काष्ठा nfp_fl_payload *nfp_fl, पूर्णांक *a_len,
			 काष्ठा net_device *netdev, bool last,
			 क्रमागत nfp_flower_tun_type *tun_type, पूर्णांक *tun_out_cnt,
			 पूर्णांक *out_cnt, u32 *csum_updated, bool pkt_host,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_fl_output *output;
	पूर्णांक err, prelag_size;

	/* If csum_updated has not been reset by now, it means HW will
	 * incorrectly update csums when they are not requested.
	 */
	अगर (*csum_updated) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: set actions without updating checksums are not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (*a_len + माप(काष्ठा nfp_fl_output) > NFP_FL_MAX_A_SIZ) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: mirred output increases action list size beyond the allowed maximum");
		वापस -EOPNOTSUPP;
	पूर्ण

	output = (काष्ठा nfp_fl_output *)&nfp_fl->action_data[*a_len];
	err = nfp_fl_output(app, output, act, nfp_fl, last, netdev, *tun_type,
			    tun_out_cnt, pkt_host, extack);
	अगर (err)
		वापस err;

	*a_len += माप(काष्ठा nfp_fl_output);

	अगर (priv->flower_en_feats & NFP_FL_ENABLE_LAG) अणु
		/* nfp_fl_pre_lag वापसs -err or size of prelag action added.
		 * This will be 0 अगर it is not egressing to a lag dev.
		 */
		prelag_size = nfp_fl_pre_lag(app, act, nfp_fl, *a_len, extack);
		अगर (prelag_size < 0) अणु
			वापस prelag_size;
		पूर्ण अन्यथा अगर (prelag_size > 0 && (!last || *out_cnt)) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: LAG action has to be last action in action list");
			वापस -EOPNOTSUPP;
		पूर्ण

		*a_len += prelag_size;
	पूर्ण
	(*out_cnt)++;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_loop_action(काष्ठा nfp_app *app, स्थिर काष्ठा flow_action_entry *act,
		       काष्ठा flow_cls_offload *flow,
		       काष्ठा nfp_fl_payload *nfp_fl, पूर्णांक *a_len,
		       काष्ठा net_device *netdev,
		       क्रमागत nfp_flower_tun_type *tun_type, पूर्णांक *tun_out_cnt,
		       पूर्णांक *out_cnt, u32 *csum_updated,
		       काष्ठा nfp_flower_pedit_acts *set_act, bool *pkt_host,
		       काष्ठा netlink_ext_ack *extack, पूर्णांक act_idx)
अणु
	काष्ठा nfp_fl_pre_tunnel *pre_tun;
	काष्ठा nfp_fl_set_tun *set_tun;
	काष्ठा nfp_fl_push_vlan *psh_v;
	काष्ठा nfp_fl_push_mpls *psh_m;
	काष्ठा nfp_fl_pop_vlan *pop_v;
	काष्ठा nfp_fl_pop_mpls *pop_m;
	काष्ठा nfp_fl_set_mpls *set_m;
	पूर्णांक err;

	चयन (act->id) अणु
	हाल FLOW_ACTION_DROP:
		nfp_fl->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_DROP);
		अवरोध;
	हाल FLOW_ACTION_REसूचीECT_INGRESS:
	हाल FLOW_ACTION_REसूचीECT:
		err = nfp_flower_output_action(app, act, nfp_fl, a_len, netdev,
					       true, tun_type, tun_out_cnt,
					       out_cnt, csum_updated, *pkt_host,
					       extack);
		अगर (err)
			वापस err;
		अवरोध;
	हाल FLOW_ACTION_MIRRED_INGRESS:
	हाल FLOW_ACTION_MIRRED:
		err = nfp_flower_output_action(app, act, nfp_fl, a_len, netdev,
					       false, tun_type, tun_out_cnt,
					       out_cnt, csum_updated, *pkt_host,
					       extack);
		अगर (err)
			वापस err;
		अवरोध;
	हाल FLOW_ACTION_VLAN_POP:
		अगर (*a_len +
		    माप(काष्ठा nfp_fl_pop_vlan) > NFP_FL_MAX_A_SIZ) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at pop vlan");
			वापस -EOPNOTSUPP;
		पूर्ण

		pop_v = (काष्ठा nfp_fl_pop_vlan *)&nfp_fl->action_data[*a_len];
		nfp_fl->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_POPV);

		nfp_fl_pop_vlan(pop_v);
		*a_len += माप(काष्ठा nfp_fl_pop_vlan);
		अवरोध;
	हाल FLOW_ACTION_VLAN_PUSH:
		अगर (*a_len +
		    माप(काष्ठा nfp_fl_push_vlan) > NFP_FL_MAX_A_SIZ) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at push vlan");
			वापस -EOPNOTSUPP;
		पूर्ण

		psh_v = (काष्ठा nfp_fl_push_vlan *)&nfp_fl->action_data[*a_len];
		nfp_fl->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_शून्य);

		nfp_fl_push_vlan(psh_v, act);
		*a_len += माप(काष्ठा nfp_fl_push_vlan);
		अवरोध;
	हाल FLOW_ACTION_TUNNEL_ENCAP: अणु
		स्थिर काष्ठा ip_tunnel_info *ip_tun = act->tunnel;

		*tun_type = nfp_fl_get_tun_from_act(app, flow, act, act_idx);
		अगर (*tun_type == NFP_FL_TUNNEL_NONE) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: unsupported tunnel type in action list");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (ip_tun->mode & ~NFP_FL_SUPPORTED_TUNNEL_INFO_FLAGS) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: unsupported tunnel flags in action list");
			वापस -EOPNOTSUPP;
		पूर्ण

		/* Pre-tunnel action is required क्रम tunnel encap.
		 * This checks क्रम next hop entries on NFP.
		 * If none, the packet falls back beक्रमe applying other actions.
		 */
		अगर (*a_len + माप(काष्ठा nfp_fl_pre_tunnel) +
		    माप(काष्ठा nfp_fl_set_tun) > NFP_FL_MAX_A_SIZ) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at tunnel encap");
			वापस -EOPNOTSUPP;
		पूर्ण

		pre_tun = nfp_fl_pre_tunnel(nfp_fl->action_data, *a_len);
		nfp_fl->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_शून्य);
		*a_len += माप(काष्ठा nfp_fl_pre_tunnel);

		err = nfp_fl_push_geneve_options(nfp_fl, a_len, act, extack);
		अगर (err)
			वापस err;

		set_tun = (व्योम *)&nfp_fl->action_data[*a_len];
		err = nfp_fl_set_tun(app, set_tun, act, pre_tun, *tun_type,
				     netdev, extack);
		अगर (err)
			वापस err;
		*a_len += माप(काष्ठा nfp_fl_set_tun);
		पूर्ण
		अवरोध;
	हाल FLOW_ACTION_TUNNEL_DECAP:
		/* Tunnel decap is handled by शेष so accept action. */
		वापस 0;
	हाल FLOW_ACTION_MANGLE:
		अगर (nfp_fl_pedit(act, flow, &nfp_fl->action_data[*a_len],
				 a_len, csum_updated, set_act, extack))
			वापस -EOPNOTSUPP;
		अवरोध;
	हाल FLOW_ACTION_CSUM:
		/* csum action requests recalc of something we have not fixed */
		अगर (act->csum_flags & ~*csum_updated) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: unsupported csum update action in action list");
			वापस -EOPNOTSUPP;
		पूर्ण
		/* If we will correctly fix the csum we can हटाओ it from the
		 * csum update list. Which will later be used to check support.
		 */
		*csum_updated &= ~act->csum_flags;
		अवरोध;
	हाल FLOW_ACTION_MPLS_PUSH:
		अगर (*a_len +
		    माप(काष्ठा nfp_fl_push_mpls) > NFP_FL_MAX_A_SIZ) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at push MPLS");
			वापस -EOPNOTSUPP;
		पूर्ण

		psh_m = (काष्ठा nfp_fl_push_mpls *)&nfp_fl->action_data[*a_len];
		nfp_fl->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_शून्य);

		err = nfp_fl_push_mpls(psh_m, act, extack);
		अगर (err)
			वापस err;
		*a_len += माप(काष्ठा nfp_fl_push_mpls);
		अवरोध;
	हाल FLOW_ACTION_MPLS_POP:
		अगर (*a_len +
		    माप(काष्ठा nfp_fl_pop_mpls) > NFP_FL_MAX_A_SIZ) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at pop MPLS");
			वापस -EOPNOTSUPP;
		पूर्ण

		pop_m = (काष्ठा nfp_fl_pop_mpls *)&nfp_fl->action_data[*a_len];
		nfp_fl->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_शून्य);

		nfp_fl_pop_mpls(pop_m, act);
		*a_len += माप(काष्ठा nfp_fl_pop_mpls);
		अवरोध;
	हाल FLOW_ACTION_MPLS_MANGLE:
		अगर (*a_len +
		    माप(काष्ठा nfp_fl_set_mpls) > NFP_FL_MAX_A_SIZ) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: maximum allowed action list size exceeded at set MPLS");
			वापस -EOPNOTSUPP;
		पूर्ण

		set_m = (काष्ठा nfp_fl_set_mpls *)&nfp_fl->action_data[*a_len];
		nfp_fl->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_शून्य);

		nfp_fl_set_mpls(set_m, act);
		*a_len += माप(काष्ठा nfp_fl_set_mpls);
		अवरोध;
	हाल FLOW_ACTION_PTYPE:
		/* TC ptype skbedit sets PACKET_HOST क्रम ingress redirect. */
		अगर (act->ptype != PACKET_HOST)
			वापस -EOPNOTSUPP;

		*pkt_host = true;
		अवरोध;
	शेष:
		/* Currently we करो not handle any other actions. */
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: unsupported action in action list");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool nfp_fl_check_mangle_start(काष्ठा flow_action *flow_act,
				      पूर्णांक current_act_idx)
अणु
	काष्ठा flow_action_entry current_act;
	काष्ठा flow_action_entry prev_act;

	current_act = flow_act->entries[current_act_idx];
	अगर (current_act.id != FLOW_ACTION_MANGLE)
		वापस false;

	अगर (current_act_idx == 0)
		वापस true;

	prev_act = flow_act->entries[current_act_idx - 1];

	वापस prev_act.id != FLOW_ACTION_MANGLE;
पूर्ण

अटल bool nfp_fl_check_mangle_end(काष्ठा flow_action *flow_act,
				    पूर्णांक current_act_idx)
अणु
	काष्ठा flow_action_entry current_act;
	काष्ठा flow_action_entry next_act;

	current_act = flow_act->entries[current_act_idx];
	अगर (current_act.id != FLOW_ACTION_MANGLE)
		वापस false;

	अगर (current_act_idx == flow_act->num_entries)
		वापस true;

	next_act = flow_act->entries[current_act_idx + 1];

	वापस next_act.id != FLOW_ACTION_MANGLE;
पूर्ण

पूर्णांक nfp_flower_compile_action(काष्ठा nfp_app *app,
			      काष्ठा flow_cls_offload *flow,
			      काष्ठा net_device *netdev,
			      काष्ठा nfp_fl_payload *nfp_flow,
			      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक act_len, act_cnt, err, tun_out_cnt, out_cnt, i;
	काष्ठा nfp_flower_pedit_acts set_act;
	क्रमागत nfp_flower_tun_type tun_type;
	काष्ठा flow_action_entry *act;
	bool pkt_host = false;
	u32 csum_updated = 0;

	अगर (!flow_action_hw_stats_check(&flow->rule->action, extack,
					FLOW_ACTION_HW_STATS_DELAYED_BIT))
		वापस -EOPNOTSUPP;

	स_रखो(nfp_flow->action_data, 0, NFP_FL_MAX_A_SIZ);
	nfp_flow->meta.act_len = 0;
	tun_type = NFP_FL_TUNNEL_NONE;
	act_len = 0;
	act_cnt = 0;
	tun_out_cnt = 0;
	out_cnt = 0;

	flow_action_क्रम_each(i, act, &flow->rule->action) अणु
		अगर (nfp_fl_check_mangle_start(&flow->rule->action, i))
			स_रखो(&set_act, 0, माप(set_act));
		err = nfp_flower_loop_action(app, act, flow, nfp_flow, &act_len,
					     netdev, &tun_type, &tun_out_cnt,
					     &out_cnt, &csum_updated,
					     &set_act, &pkt_host, extack, i);
		अगर (err)
			वापस err;
		act_cnt++;
		अगर (nfp_fl_check_mangle_end(&flow->rule->action, i))
			nfp_fl_commit_mangle(flow,
					     &nfp_flow->action_data[act_len],
					     &act_len, &set_act, &csum_updated);
	पूर्ण

	/* We optimise when the action list is small, this can unक्रमtunately
	 * not happen once we have more than one action in the action list.
	 */
	अगर (act_cnt > 1)
		nfp_flow->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_शून्य);

	nfp_flow->meta.act_len = act_len;

	वापस 0;
पूर्ण
