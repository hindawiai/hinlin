<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/skbuff.h>
#समावेश <net/devlink.h>
#समावेश <net/pkt_cls.h>

#समावेश "cmsg.h"
#समावेश "main.h"
#समावेश "../nfpcore/nfp_cpp.h"
#समावेश "../nfpcore/nfp_nsp.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_main.h"
#समावेश "../nfp_net.h"
#समावेश "../nfp_port.h"

#घोषणा NFP_FLOWER_SUPPORTED_TCPFLAGS \
	(TCPHDR_FIN | TCPHDR_SYN | TCPHDR_RST | \
	 TCPHDR_PSH | TCPHDR_URG)

#घोषणा NFP_FLOWER_SUPPORTED_CTLFLAGS \
	(FLOW_DIS_IS_FRAGMENT | \
	 FLOW_DIS_FIRST_FRAG)

#घोषणा NFP_FLOWER_WHITELIST_DISSECTOR \
	(BIT(FLOW_DISSECTOR_KEY_CONTROL) | \
	 BIT(FLOW_DISSECTOR_KEY_BASIC) | \
	 BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) | \
	 BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) | \
	 BIT(FLOW_DISSECTOR_KEY_TCP) | \
	 BIT(FLOW_DISSECTOR_KEY_PORTS) | \
	 BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) | \
	 BIT(FLOW_DISSECTOR_KEY_VLAN) | \
	 BIT(FLOW_DISSECTOR_KEY_CVLAN) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_KEYID) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_CONTROL) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_PORTS) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_OPTS) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_IP) | \
	 BIT(FLOW_DISSECTOR_KEY_MPLS) | \
	 BIT(FLOW_DISSECTOR_KEY_IP))

#घोषणा NFP_FLOWER_WHITELIST_TUN_DISSECTOR \
	(BIT(FLOW_DISSECTOR_KEY_ENC_CONTROL) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_KEYID) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_OPTS) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_PORTS) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_IP))

#घोषणा NFP_FLOWER_WHITELIST_TUN_DISSECTOR_R \
	(BIT(FLOW_DISSECTOR_KEY_ENC_CONTROL) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS))

#घोषणा NFP_FLOWER_WHITELIST_TUN_DISSECTOR_V6_R \
	(BIT(FLOW_DISSECTOR_KEY_ENC_CONTROL) | \
	 BIT(FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS))

#घोषणा NFP_FLOWER_MERGE_FIELDS \
	(NFP_FLOWER_LAYER_PORT | \
	 NFP_FLOWER_LAYER_MAC | \
	 NFP_FLOWER_LAYER_TP | \
	 NFP_FLOWER_LAYER_IPV4 | \
	 NFP_FLOWER_LAYER_IPV6)

#घोषणा NFP_FLOWER_PRE_TUN_RULE_FIELDS \
	(NFP_FLOWER_LAYER_EXT_META | \
	 NFP_FLOWER_LAYER_PORT | \
	 NFP_FLOWER_LAYER_MAC | \
	 NFP_FLOWER_LAYER_IPV4 | \
	 NFP_FLOWER_LAYER_IPV6)

काष्ठा nfp_flower_merge_check अणु
	जोड़ अणु
		काष्ठा अणु
			__be16 tci;
			काष्ठा nfp_flower_mac_mpls l2;
			काष्ठा nfp_flower_tp_ports l4;
			जोड़ अणु
				काष्ठा nfp_flower_ipv4 ipv4;
				काष्ठा nfp_flower_ipv6 ipv6;
			पूर्ण;
		पूर्ण;
		अचिन्हित दीर्घ vals[8];
	पूर्ण;
पूर्ण;

अटल पूर्णांक
nfp_flower_xmit_flow(काष्ठा nfp_app *app, काष्ठा nfp_fl_payload *nfp_flow,
		     u8 mtype)
अणु
	u32 meta_len, key_len, mask_len, act_len, tot_len;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *msg;

	meta_len =  माप(काष्ठा nfp_fl_rule_metadata);
	key_len = nfp_flow->meta.key_len;
	mask_len = nfp_flow->meta.mask_len;
	act_len = nfp_flow->meta.act_len;

	tot_len = meta_len + key_len + mask_len + act_len;

	/* Convert to दीर्घ words as firmware expects
	 * lengths in units of NFP_FL_LW_SIZ.
	 */
	nfp_flow->meta.key_len >>= NFP_FL_LW_SIZ;
	nfp_flow->meta.mask_len >>= NFP_FL_LW_SIZ;
	nfp_flow->meta.act_len >>= NFP_FL_LW_SIZ;

	skb = nfp_flower_cmsg_alloc(app, tot_len, mtype, GFP_KERNEL);
	अगर (!skb)
		वापस -ENOMEM;

	msg = nfp_flower_cmsg_get_data(skb);
	स_नकल(msg, &nfp_flow->meta, meta_len);
	स_नकल(&msg[meta_len], nfp_flow->unmasked_data, key_len);
	स_नकल(&msg[meta_len + key_len], nfp_flow->mask_data, mask_len);
	स_नकल(&msg[meta_len + key_len + mask_len],
	       nfp_flow->action_data, act_len);

	/* Convert back to bytes as software expects
	 * lengths in units of bytes.
	 */
	nfp_flow->meta.key_len <<= NFP_FL_LW_SIZ;
	nfp_flow->meta.mask_len <<= NFP_FL_LW_SIZ;
	nfp_flow->meta.act_len <<= NFP_FL_LW_SIZ;

	nfp_ctrl_tx(app->ctrl, skb);

	वापस 0;
पूर्ण

अटल bool nfp_flower_check_higher_than_mac(काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);

	वापस flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS) ||
	       flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS) ||
	       flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS) ||
	       flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ICMP);
पूर्ण

अटल bool nfp_flower_check_higher_than_l3(काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);

	वापस flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS) ||
	       flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ICMP);
पूर्ण

अटल पूर्णांक
nfp_flower_calc_opt_layer(काष्ठा flow_dissector_key_enc_opts *enc_opts,
			  u32 *key_layer_two, पूर्णांक *key_size, bool ipv6,
			  काष्ठा netlink_ext_ack *extack)
अणु
	अगर (enc_opts->len > NFP_FL_MAX_GENEVE_OPT_KEY ||
	    (ipv6 && enc_opts->len > NFP_FL_MAX_GENEVE_OPT_KEY_V6)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: geneve options exceed maximum length");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (enc_opts->len > 0) अणु
		*key_layer_two |= NFP_FLOWER_LAYER2_GENEVE_OP;
		*key_size += माप(काष्ठा nfp_flower_geneve_options);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_calc_udp_tun_layer(काष्ठा flow_dissector_key_ports *enc_ports,
			      काष्ठा flow_dissector_key_enc_opts *enc_op,
			      u32 *key_layer_two, u8 *key_layer, पूर्णांक *key_size,
			      काष्ठा nfp_flower_priv *priv,
			      क्रमागत nfp_flower_tun_type *tun_type, bool ipv6,
			      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	चयन (enc_ports->dst) अणु
	हाल htons(IANA_VXLAN_UDP_PORT):
		*tun_type = NFP_FL_TUNNEL_VXLAN;
		*key_layer |= NFP_FLOWER_LAYER_VXLAN;

		अगर (ipv6) अणु
			*key_layer |= NFP_FLOWER_LAYER_EXT_META;
			*key_size += माप(काष्ठा nfp_flower_ext_meta);
			*key_layer_two |= NFP_FLOWER_LAYER2_TUN_IPV6;
			*key_size += माप(काष्ठा nfp_flower_ipv6_udp_tun);
		पूर्ण अन्यथा अणु
			*key_size += माप(काष्ठा nfp_flower_ipv4_udp_tun);
		पूर्ण

		अगर (enc_op) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: encap options not supported on vxlan tunnels");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल htons(GENEVE_UDP_PORT):
		अगर (!(priv->flower_ext_feats & NFP_FL_FEATS_GENEVE)) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: loaded firmware does not support geneve offload");
			वापस -EOPNOTSUPP;
		पूर्ण
		*tun_type = NFP_FL_TUNNEL_GENEVE;
		*key_layer |= NFP_FLOWER_LAYER_EXT_META;
		*key_size += माप(काष्ठा nfp_flower_ext_meta);
		*key_layer_two |= NFP_FLOWER_LAYER2_GENEVE;

		अगर (ipv6) अणु
			*key_layer_two |= NFP_FLOWER_LAYER2_TUN_IPV6;
			*key_size += माप(काष्ठा nfp_flower_ipv6_udp_tun);
		पूर्ण अन्यथा अणु
			*key_size += माप(काष्ठा nfp_flower_ipv4_udp_tun);
		पूर्ण

		अगर (!enc_op)
			अवरोध;
		अगर (!(priv->flower_ext_feats & NFP_FL_FEATS_GENEVE_OPT)) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: loaded firmware does not support geneve option offload");
			वापस -EOPNOTSUPP;
		पूर्ण
		err = nfp_flower_calc_opt_layer(enc_op, key_layer_two, key_size,
						ipv6, extack);
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: tunnel type unknown");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_calculate_key_layers(काष्ठा nfp_app *app,
				काष्ठा net_device *netdev,
				काष्ठा nfp_fl_key_ls *ret_key_ls,
				काष्ठा flow_cls_offload *flow,
				क्रमागत nfp_flower_tun_type *tun_type,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(flow);
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	काष्ठा flow_match_basic basic = अणु शून्य, शून्यपूर्ण;
	काष्ठा nfp_flower_priv *priv = app->priv;
	u32 key_layer_two;
	u8 key_layer;
	पूर्णांक key_size;
	पूर्णांक err;

	अगर (dissector->used_keys & ~NFP_FLOWER_WHITELIST_DISSECTOR) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: match not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* If any tun dissector is used then the required set must be used. */
	अगर (dissector->used_keys & NFP_FLOWER_WHITELIST_TUN_DISSECTOR &&
	    (dissector->used_keys & NFP_FLOWER_WHITELIST_TUN_DISSECTOR_V6_R)
	    != NFP_FLOWER_WHITELIST_TUN_DISSECTOR_V6_R &&
	    (dissector->used_keys & NFP_FLOWER_WHITELIST_TUN_DISSECTOR_R)
	    != NFP_FLOWER_WHITELIST_TUN_DISSECTOR_R) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: tunnel match not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	key_layer_two = 0;
	key_layer = NFP_FLOWER_LAYER_PORT;
	key_size = माप(काष्ठा nfp_flower_meta_tci) +
		   माप(काष्ठा nfp_flower_in_port);

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS) ||
	    flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_MPLS)) अणु
		key_layer |= NFP_FLOWER_LAYER_MAC;
		key_size += माप(काष्ठा nfp_flower_mac_mpls);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan vlan;

		flow_rule_match_vlan(rule, &vlan);
		अगर (!(priv->flower_ext_feats & NFP_FL_FEATS_VLAN_PCP) &&
		    vlan.key->vlan_priority) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: loaded firmware does not support VLAN PCP offload");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (priv->flower_ext_feats & NFP_FL_FEATS_VLAN_QINQ &&
		    !(key_layer_two & NFP_FLOWER_LAYER2_QINQ)) अणु
			key_layer |= NFP_FLOWER_LAYER_EXT_META;
			key_size += माप(काष्ठा nfp_flower_ext_meta);
			key_size += माप(काष्ठा nfp_flower_vlan);
			key_layer_two |= NFP_FLOWER_LAYER2_QINQ;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CVLAN)) अणु
		काष्ठा flow_match_vlan cvlan;

		अगर (!(priv->flower_ext_feats & NFP_FL_FEATS_VLAN_QINQ)) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: loaded firmware does not support VLAN QinQ offload");
			वापस -EOPNOTSUPP;
		पूर्ण

		flow_rule_match_vlan(rule, &cvlan);
		अगर (!(key_layer_two & NFP_FLOWER_LAYER2_QINQ)) अणु
			key_layer |= NFP_FLOWER_LAYER_EXT_META;
			key_size += माप(काष्ठा nfp_flower_ext_meta);
			key_size += माप(काष्ठा nfp_flower_vlan);
			key_layer_two |= NFP_FLOWER_LAYER2_QINQ;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_CONTROL)) अणु
		काष्ठा flow_match_enc_opts enc_op = अणु शून्य, शून्य पूर्ण;
		काष्ठा flow_match_ipv4_addrs ipv4_addrs;
		काष्ठा flow_match_ipv6_addrs ipv6_addrs;
		काष्ठा flow_match_control enc_ctl;
		काष्ठा flow_match_ports enc_ports;
		bool ipv6_tun = false;

		flow_rule_match_enc_control(rule, &enc_ctl);

		अगर (enc_ctl.mask->addr_type != 0xffff) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: wildcarded protocols on tunnels are not supported");
			वापस -EOPNOTSUPP;
		पूर्ण

		ipv6_tun = enc_ctl.key->addr_type ==
				FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		अगर (ipv6_tun &&
		    !(priv->flower_ext_feats & NFP_FL_FEATS_IPV6_TUN)) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: firmware does not support IPv6 tunnels");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (!ipv6_tun &&
		    enc_ctl.key->addr_type != FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: tunnel address type not IPv4 or IPv6");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (ipv6_tun) अणु
			flow_rule_match_enc_ipv6_addrs(rule, &ipv6_addrs);
			अगर (स_प्रथम_inv(&ipv6_addrs.mask->dst, 0xff,
				       माप(ipv6_addrs.mask->dst))) अणु
				NL_SET_ERR_MSG_MOD(extack, "unsupported offload: only an exact match IPv6 destination address is supported");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण अन्यथा अणु
			flow_rule_match_enc_ipv4_addrs(rule, &ipv4_addrs);
			अगर (ipv4_addrs.mask->dst != cpu_to_be32(~0)) अणु
				NL_SET_ERR_MSG_MOD(extack, "unsupported offload: only an exact match IPv4 destination address is supported");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण

		अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_OPTS))
			flow_rule_match_enc_opts(rule, &enc_op);

		अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_PORTS)) अणु
			/* check अगर GRE, which has no enc_ports */
			अगर (!netअगर_is_gretap(netdev)) अणु
				NL_SET_ERR_MSG_MOD(extack, "unsupported offload: an exact match on L4 destination port is required for non-GRE tunnels");
				वापस -EOPNOTSUPP;
			पूर्ण

			*tun_type = NFP_FL_TUNNEL_GRE;
			key_layer |= NFP_FLOWER_LAYER_EXT_META;
			key_size += माप(काष्ठा nfp_flower_ext_meta);
			key_layer_two |= NFP_FLOWER_LAYER2_GRE;

			अगर (ipv6_tun) अणु
				key_layer_two |= NFP_FLOWER_LAYER2_TUN_IPV6;
				key_size +=
					माप(काष्ठा nfp_flower_ipv6_udp_tun);
			पूर्ण अन्यथा अणु
				key_size +=
					माप(काष्ठा nfp_flower_ipv4_udp_tun);
			पूर्ण

			अगर (enc_op.key) अणु
				NL_SET_ERR_MSG_MOD(extack, "unsupported offload: encap options not supported on GRE tunnels");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण अन्यथा अणु
			flow_rule_match_enc_ports(rule, &enc_ports);
			अगर (enc_ports.mask->dst != cpu_to_be16(~0)) अणु
				NL_SET_ERR_MSG_MOD(extack, "unsupported offload: only an exact match L4 destination port is supported");
				वापस -EOPNOTSUPP;
			पूर्ण

			err = nfp_flower_calc_udp_tun_layer(enc_ports.key,
							    enc_op.key,
							    &key_layer_two,
							    &key_layer,
							    &key_size, priv,
							    tun_type, ipv6_tun,
							    extack);
			अगर (err)
				वापस err;

			/* Ensure the ingress netdev matches the expected
			 * tun type.
			 */
			अगर (!nfp_fl_netdev_is_tunnel_type(netdev, *tun_type)) अणु
				NL_SET_ERR_MSG_MOD(extack, "unsupported offload: ingress netdev does not match the expected tunnel type");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC))
		flow_rule_match_basic(rule, &basic);

	अगर (basic.mask && basic.mask->n_proto) अणु
		/* Ethernet type is present in the key. */
		चयन (basic.key->n_proto) अणु
		हाल cpu_to_be16(ETH_P_IP):
			key_layer |= NFP_FLOWER_LAYER_IPV4;
			key_size += माप(काष्ठा nfp_flower_ipv4);
			अवरोध;

		हाल cpu_to_be16(ETH_P_IPV6):
			key_layer |= NFP_FLOWER_LAYER_IPV6;
			key_size += माप(काष्ठा nfp_flower_ipv6);
			अवरोध;

		/* Currently we करो not offload ARP
		 * because we rely on it to get to the host.
		 */
		हाल cpu_to_be16(ETH_P_ARP):
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: ARP not supported");
			वापस -EOPNOTSUPP;

		हाल cpu_to_be16(ETH_P_MPLS_UC):
		हाल cpu_to_be16(ETH_P_MPLS_MC):
			अगर (!(key_layer & NFP_FLOWER_LAYER_MAC)) अणु
				key_layer |= NFP_FLOWER_LAYER_MAC;
				key_size += माप(काष्ठा nfp_flower_mac_mpls);
			पूर्ण
			अवरोध;

		/* Will be included in layer 2. */
		हाल cpu_to_be16(ETH_P_8021Q):
			अवरोध;

		शेष:
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: match on given EtherType is not supported");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अगर (nfp_flower_check_higher_than_mac(flow)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: cannot match above L2 without specified EtherType");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (basic.mask && basic.mask->ip_proto) अणु
		चयन (basic.key->ip_proto) अणु
		हाल IPPROTO_TCP:
		हाल IPPROTO_UDP:
		हाल IPPROTO_SCTP:
		हाल IPPROTO_ICMP:
		हाल IPPROTO_ICMPV6:
			key_layer |= NFP_FLOWER_LAYER_TP;
			key_size += माप(काष्ठा nfp_flower_tp_ports);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!(key_layer & NFP_FLOWER_LAYER_TP) &&
	    nfp_flower_check_higher_than_l3(flow)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: cannot match on L4 information without specified IP protocol type");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_TCP)) अणु
		काष्ठा flow_match_tcp tcp;
		u32 tcp_flags;

		flow_rule_match_tcp(rule, &tcp);
		tcp_flags = be16_to_cpu(tcp.key->flags);

		अगर (tcp_flags & ~NFP_FLOWER_SUPPORTED_TCPFLAGS) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: no match support for selected TCP flags");
			वापस -EOPNOTSUPP;
		पूर्ण

		/* We only support PSH and URG flags when either
		 * FIN, SYN or RST is present as well.
		 */
		अगर ((tcp_flags & (TCPHDR_PSH | TCPHDR_URG)) &&
		    !(tcp_flags & (TCPHDR_FIN | TCPHDR_SYN | TCPHDR_RST))) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: PSH and URG is only supported when used with FIN, SYN or RST");
			वापस -EOPNOTSUPP;
		पूर्ण

		/* We need to store TCP flags in the either the IPv4 or IPv6 key
		 * space, thus we need to ensure we include a IPv4/IPv6 key
		 * layer अगर we have not करोne so alपढ़ोy.
		 */
		अगर (!basic.key) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: match on TCP flags requires a match on L3 protocol");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (!(key_layer & NFP_FLOWER_LAYER_IPV4) &&
		    !(key_layer & NFP_FLOWER_LAYER_IPV6)) अणु
			चयन (basic.key->n_proto) अणु
			हाल cpu_to_be16(ETH_P_IP):
				key_layer |= NFP_FLOWER_LAYER_IPV4;
				key_size += माप(काष्ठा nfp_flower_ipv4);
				अवरोध;

			हाल cpu_to_be16(ETH_P_IPV6):
					key_layer |= NFP_FLOWER_LAYER_IPV6;
				key_size += माप(काष्ठा nfp_flower_ipv6);
				अवरोध;

			शेष:
				NL_SET_ERR_MSG_MOD(extack, "unsupported offload: match on TCP flags requires a match on IPv4/IPv6");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control ctl;

		flow_rule_match_control(rule, &ctl);
		अगर (ctl.key->flags & ~NFP_FLOWER_SUPPORTED_CTLFLAGS) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: match on unknown control flag");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	ret_key_ls->key_layer = key_layer;
	ret_key_ls->key_layer_two = key_layer_two;
	ret_key_ls->key_size = key_size;

	वापस 0;
पूर्ण

अटल काष्ठा nfp_fl_payload *
nfp_flower_allocate_new(काष्ठा nfp_fl_key_ls *key_layer)
अणु
	काष्ठा nfp_fl_payload *flow_pay;

	flow_pay = kदो_स्मृति(माप(*flow_pay), GFP_KERNEL);
	अगर (!flow_pay)
		वापस शून्य;

	flow_pay->meta.key_len = key_layer->key_size;
	flow_pay->unmasked_data = kदो_स्मृति(key_layer->key_size, GFP_KERNEL);
	अगर (!flow_pay->unmasked_data)
		जाओ err_मुक्त_flow;

	flow_pay->meta.mask_len = key_layer->key_size;
	flow_pay->mask_data = kदो_स्मृति(key_layer->key_size, GFP_KERNEL);
	अगर (!flow_pay->mask_data)
		जाओ err_मुक्त_unmasked;

	flow_pay->action_data = kदो_स्मृति(NFP_FL_MAX_A_SIZ, GFP_KERNEL);
	अगर (!flow_pay->action_data)
		जाओ err_मुक्त_mask;

	flow_pay->nfp_tun_ipv4_addr = 0;
	flow_pay->nfp_tun_ipv6 = शून्य;
	flow_pay->meta.flags = 0;
	INIT_LIST_HEAD(&flow_pay->linked_flows);
	flow_pay->in_hw = false;
	flow_pay->pre_tun_rule.dev = शून्य;

	वापस flow_pay;

err_मुक्त_mask:
	kमुक्त(flow_pay->mask_data);
err_मुक्त_unmasked:
	kमुक्त(flow_pay->unmasked_data);
err_मुक्त_flow:
	kमुक्त(flow_pay);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
nfp_flower_update_merge_with_actions(काष्ठा nfp_fl_payload *flow,
				     काष्ठा nfp_flower_merge_check *merge,
				     u8 *last_act_id, पूर्णांक *act_out)
अणु
	काष्ठा nfp_fl_set_ipv6_tc_hl_fl *ipv6_tc_hl_fl;
	काष्ठा nfp_fl_set_ip4_ttl_tos *ipv4_ttl_tos;
	काष्ठा nfp_fl_set_ip4_addrs *ipv4_add;
	काष्ठा nfp_fl_set_ipv6_addr *ipv6_add;
	काष्ठा nfp_fl_push_vlan *push_vlan;
	काष्ठा nfp_fl_pre_tunnel *pre_tun;
	काष्ठा nfp_fl_set_tport *tport;
	काष्ठा nfp_fl_set_eth *eth;
	काष्ठा nfp_fl_act_head *a;
	अचिन्हित पूर्णांक act_off = 0;
	bool ipv6_tun = false;
	u8 act_id = 0;
	u8 *ports;
	पूर्णांक i;

	जबतक (act_off < flow->meta.act_len) अणु
		a = (काष्ठा nfp_fl_act_head *)&flow->action_data[act_off];
		act_id = a->jump_id;

		चयन (act_id) अणु
		हाल NFP_FL_ACTION_OPCODE_OUTPUT:
			अगर (act_out)
				(*act_out)++;
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_PUSH_VLAN:
			push_vlan = (काष्ठा nfp_fl_push_vlan *)a;
			अगर (push_vlan->vlan_tci)
				merge->tci = cpu_to_be16(0xffff);
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_POP_VLAN:
			merge->tci = cpu_to_be16(0);
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_SET_TUNNEL:
			/* New tunnel header means l2 to l4 can be matched. */
			eth_broadcast_addr(&merge->l2.mac_dst[0]);
			eth_broadcast_addr(&merge->l2.mac_src[0]);
			स_रखो(&merge->l4, 0xff,
			       माप(काष्ठा nfp_flower_tp_ports));
			अगर (ipv6_tun)
				स_रखो(&merge->ipv6, 0xff,
				       माप(काष्ठा nfp_flower_ipv6));
			अन्यथा
				स_रखो(&merge->ipv4, 0xff,
				       माप(काष्ठा nfp_flower_ipv4));
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_SET_ETHERNET:
			eth = (काष्ठा nfp_fl_set_eth *)a;
			क्रम (i = 0; i < ETH_ALEN; i++)
				merge->l2.mac_dst[i] |= eth->eth_addr_mask[i];
			क्रम (i = 0; i < ETH_ALEN; i++)
				merge->l2.mac_src[i] |=
					eth->eth_addr_mask[ETH_ALEN + i];
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_SET_IPV4_ADDRS:
			ipv4_add = (काष्ठा nfp_fl_set_ip4_addrs *)a;
			merge->ipv4.ipv4_src |= ipv4_add->ipv4_src_mask;
			merge->ipv4.ipv4_dst |= ipv4_add->ipv4_dst_mask;
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_SET_IPV4_TTL_TOS:
			ipv4_ttl_tos = (काष्ठा nfp_fl_set_ip4_ttl_tos *)a;
			merge->ipv4.ip_ext.ttl |= ipv4_ttl_tos->ipv4_ttl_mask;
			merge->ipv4.ip_ext.tos |= ipv4_ttl_tos->ipv4_tos_mask;
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_SET_IPV6_SRC:
			ipv6_add = (काष्ठा nfp_fl_set_ipv6_addr *)a;
			क्रम (i = 0; i < 4; i++)
				merge->ipv6.ipv6_src.in6_u.u6_addr32[i] |=
					ipv6_add->ipv6[i].mask;
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_SET_IPV6_DST:
			ipv6_add = (काष्ठा nfp_fl_set_ipv6_addr *)a;
			क्रम (i = 0; i < 4; i++)
				merge->ipv6.ipv6_dst.in6_u.u6_addr32[i] |=
					ipv6_add->ipv6[i].mask;
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_SET_IPV6_TC_HL_FL:
			ipv6_tc_hl_fl = (काष्ठा nfp_fl_set_ipv6_tc_hl_fl *)a;
			merge->ipv6.ip_ext.ttl |=
				ipv6_tc_hl_fl->ipv6_hop_limit_mask;
			merge->ipv6.ip_ext.tos |= ipv6_tc_hl_fl->ipv6_tc_mask;
			merge->ipv6.ipv6_flow_label_exthdr |=
				ipv6_tc_hl_fl->ipv6_label_mask;
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_SET_UDP:
		हाल NFP_FL_ACTION_OPCODE_SET_TCP:
			tport = (काष्ठा nfp_fl_set_tport *)a;
			ports = (u8 *)&merge->l4.port_src;
			क्रम (i = 0; i < 4; i++)
				ports[i] |= tport->tp_port_mask[i];
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_PRE_TUNNEL:
			pre_tun = (काष्ठा nfp_fl_pre_tunnel *)a;
			ipv6_tun = be16_to_cpu(pre_tun->flags) &
					NFP_FL_PRE_TUN_IPV6;
			अवरोध;
		हाल NFP_FL_ACTION_OPCODE_PRE_LAG:
		हाल NFP_FL_ACTION_OPCODE_PUSH_GENEVE:
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण

		act_off += a->len_lw << NFP_FL_LW_SIZ;
	पूर्ण

	अगर (last_act_id)
		*last_act_id = act_id;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_populate_merge_match(काष्ठा nfp_fl_payload *flow,
				काष्ठा nfp_flower_merge_check *merge,
				bool extra_fields)
अणु
	काष्ठा nfp_flower_meta_tci *meta_tci;
	u8 *mask = flow->mask_data;
	u8 key_layer, match_size;

	स_रखो(merge, 0, माप(काष्ठा nfp_flower_merge_check));

	meta_tci = (काष्ठा nfp_flower_meta_tci *)mask;
	key_layer = meta_tci->nfp_flow_key_layer;

	अगर (key_layer & ~NFP_FLOWER_MERGE_FIELDS && !extra_fields)
		वापस -EOPNOTSUPP;

	merge->tci = meta_tci->tci;
	mask += माप(काष्ठा nfp_flower_meta_tci);

	अगर (key_layer & NFP_FLOWER_LAYER_EXT_META)
		mask += माप(काष्ठा nfp_flower_ext_meta);

	mask += माप(काष्ठा nfp_flower_in_port);

	अगर (key_layer & NFP_FLOWER_LAYER_MAC) अणु
		match_size = माप(काष्ठा nfp_flower_mac_mpls);
		स_नकल(&merge->l2, mask, match_size);
		mask += match_size;
	पूर्ण

	अगर (key_layer & NFP_FLOWER_LAYER_TP) अणु
		match_size = माप(काष्ठा nfp_flower_tp_ports);
		स_नकल(&merge->l4, mask, match_size);
		mask += match_size;
	पूर्ण

	अगर (key_layer & NFP_FLOWER_LAYER_IPV4) अणु
		match_size = माप(काष्ठा nfp_flower_ipv4);
		स_नकल(&merge->ipv4, mask, match_size);
	पूर्ण

	अगर (key_layer & NFP_FLOWER_LAYER_IPV6) अणु
		match_size = माप(काष्ठा nfp_flower_ipv6);
		स_नकल(&merge->ipv6, mask, match_size);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_can_merge(काष्ठा nfp_fl_payload *sub_flow1,
		     काष्ठा nfp_fl_payload *sub_flow2)
अणु
	/* Two flows can be merged अगर sub_flow2 only matches on bits that are
	 * either matched by sub_flow1 or set by a sub_flow1 action. This
	 * ensures that every packet that hits sub_flow1 and recirculates is
	 * guaranteed to hit sub_flow2.
	 */
	काष्ठा nfp_flower_merge_check sub_flow1_merge, sub_flow2_merge;
	पूर्णांक err, act_out = 0;
	u8 last_act_id = 0;

	err = nfp_flower_populate_merge_match(sub_flow1, &sub_flow1_merge,
					      true);
	अगर (err)
		वापस err;

	err = nfp_flower_populate_merge_match(sub_flow2, &sub_flow2_merge,
					      false);
	अगर (err)
		वापस err;

	err = nfp_flower_update_merge_with_actions(sub_flow1, &sub_flow1_merge,
						   &last_act_id, &act_out);
	अगर (err)
		वापस err;

	/* Must only be 1 output action and it must be the last in sequence. */
	अगर (act_out != 1 || last_act_id != NFP_FL_ACTION_OPCODE_OUTPUT)
		वापस -EOPNOTSUPP;

	/* Reject merge अगर sub_flow2 matches on something that is not matched
	 * on or set in an action by sub_flow1.
	 */
	err = biपंचांगap_andnot(sub_flow2_merge.vals, sub_flow2_merge.vals,
			    sub_flow1_merge.vals,
			    माप(काष्ठा nfp_flower_merge_check) * 8);
	अगर (err)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक
nfp_flower_copy_pre_actions(अक्षर *act_dst, अक्षर *act_src, पूर्णांक len,
			    bool *tunnel_act)
अणु
	अचिन्हित पूर्णांक act_off = 0, act_len;
	काष्ठा nfp_fl_act_head *a;
	u8 act_id = 0;

	जबतक (act_off < len) अणु
		a = (काष्ठा nfp_fl_act_head *)&act_src[act_off];
		act_len = a->len_lw << NFP_FL_LW_SIZ;
		act_id = a->jump_id;

		चयन (act_id) अणु
		हाल NFP_FL_ACTION_OPCODE_PRE_TUNNEL:
			अगर (tunnel_act)
				*tunnel_act = true;
			fallthrough;
		हाल NFP_FL_ACTION_OPCODE_PRE_LAG:
			स_नकल(act_dst + act_off, act_src + act_off, act_len);
			अवरोध;
		शेष:
			वापस act_off;
		पूर्ण

		act_off += act_len;
	पूर्ण

	वापस act_off;
पूर्ण

अटल पूर्णांक
nfp_fl_verअगरy_post_tun_acts(अक्षर *acts, पूर्णांक len, काष्ठा nfp_fl_push_vlan **vlan)
अणु
	काष्ठा nfp_fl_act_head *a;
	अचिन्हित पूर्णांक act_off = 0;

	जबतक (act_off < len) अणु
		a = (काष्ठा nfp_fl_act_head *)&acts[act_off];

		अगर (a->jump_id == NFP_FL_ACTION_OPCODE_PUSH_VLAN && !act_off)
			*vlan = (काष्ठा nfp_fl_push_vlan *)a;
		अन्यथा अगर (a->jump_id != NFP_FL_ACTION_OPCODE_OUTPUT)
			वापस -EOPNOTSUPP;

		act_off += a->len_lw << NFP_FL_LW_SIZ;
	पूर्ण

	/* Ensure any VLAN push also has an egress action. */
	अगर (*vlan && act_off <= माप(काष्ठा nfp_fl_push_vlan))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_fl_push_vlan_after_tun(अक्षर *acts, पूर्णांक len, काष्ठा nfp_fl_push_vlan *vlan)
अणु
	काष्ठा nfp_fl_set_tun *tun;
	काष्ठा nfp_fl_act_head *a;
	अचिन्हित पूर्णांक act_off = 0;

	जबतक (act_off < len) अणु
		a = (काष्ठा nfp_fl_act_head *)&acts[act_off];

		अगर (a->jump_id == NFP_FL_ACTION_OPCODE_SET_TUNNEL) अणु
			tun = (काष्ठा nfp_fl_set_tun *)a;
			tun->outer_vlan_tpid = vlan->vlan_tpid;
			tun->outer_vlan_tci = vlan->vlan_tci;

			वापस 0;
		पूर्ण

		act_off += a->len_lw << NFP_FL_LW_SIZ;
	पूर्ण

	/* Return error अगर no tunnel action is found. */
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
nfp_flower_merge_action(काष्ठा nfp_fl_payload *sub_flow1,
			काष्ठा nfp_fl_payload *sub_flow2,
			काष्ठा nfp_fl_payload *merge_flow)
अणु
	अचिन्हित पूर्णांक sub1_act_len, sub2_act_len, pre_off1, pre_off2;
	काष्ठा nfp_fl_push_vlan *post_tun_push_vlan = शून्य;
	bool tunnel_act = false;
	अक्षर *merge_act;
	पूर्णांक err;

	/* The last action of sub_flow1 must be output - करो not merge this. */
	sub1_act_len = sub_flow1->meta.act_len - माप(काष्ठा nfp_fl_output);
	sub2_act_len = sub_flow2->meta.act_len;

	अगर (!sub2_act_len)
		वापस -EINVAL;

	अगर (sub1_act_len + sub2_act_len > NFP_FL_MAX_A_SIZ)
		वापस -EINVAL;

	/* A लघुcut can only be applied अगर there is a single action. */
	अगर (sub1_act_len)
		merge_flow->meta.लघुcut = cpu_to_be32(NFP_FL_SC_ACT_शून्य);
	अन्यथा
		merge_flow->meta.लघुcut = sub_flow2->meta.लघुcut;

	merge_flow->meta.act_len = sub1_act_len + sub2_act_len;
	merge_act = merge_flow->action_data;

	/* Copy any pre-actions to the start of merge flow action list. */
	pre_off1 = nfp_flower_copy_pre_actions(merge_act,
					       sub_flow1->action_data,
					       sub1_act_len, &tunnel_act);
	merge_act += pre_off1;
	sub1_act_len -= pre_off1;
	pre_off2 = nfp_flower_copy_pre_actions(merge_act,
					       sub_flow2->action_data,
					       sub2_act_len, शून्य);
	merge_act += pre_off2;
	sub2_act_len -= pre_off2;

	/* FW करोes a tunnel push when egressing, thereक्रमe, अगर sub_flow 1 pushes
	 * a tunnel, there are restrictions on what sub_flow 2 actions lead to a
	 * valid merge.
	 */
	अगर (tunnel_act) अणु
		अक्षर *post_tun_acts = &sub_flow2->action_data[pre_off2];

		err = nfp_fl_verअगरy_post_tun_acts(post_tun_acts, sub2_act_len,
						  &post_tun_push_vlan);
		अगर (err)
			वापस err;

		अगर (post_tun_push_vlan) अणु
			pre_off2 += माप(*post_tun_push_vlan);
			sub2_act_len -= माप(*post_tun_push_vlan);
		पूर्ण
	पूर्ण

	/* Copy reमुख्यing actions from sub_flows 1 and 2. */
	स_नकल(merge_act, sub_flow1->action_data + pre_off1, sub1_act_len);

	अगर (post_tun_push_vlan) अणु
		/* Update tunnel action in merge to include VLAN push. */
		err = nfp_fl_push_vlan_after_tun(merge_act, sub1_act_len,
						 post_tun_push_vlan);
		अगर (err)
			वापस err;

		merge_flow->meta.act_len -= माप(*post_tun_push_vlan);
	पूर्ण

	merge_act += sub1_act_len;
	स_नकल(merge_act, sub_flow2->action_data + pre_off2, sub2_act_len);

	वापस 0;
पूर्ण

/* Flow link code should only be accessed under RTNL. */
अटल व्योम nfp_flower_unlink_flow(काष्ठा nfp_fl_payload_link *link)
अणु
	list_del(&link->merge_flow.list);
	list_del(&link->sub_flow.list);
	kमुक्त(link);
पूर्ण

अटल व्योम nfp_flower_unlink_flows(काष्ठा nfp_fl_payload *merge_flow,
				    काष्ठा nfp_fl_payload *sub_flow)
अणु
	काष्ठा nfp_fl_payload_link *link;

	list_क्रम_each_entry(link, &merge_flow->linked_flows, merge_flow.list)
		अगर (link->sub_flow.flow == sub_flow) अणु
			nfp_flower_unlink_flow(link);
			वापस;
		पूर्ण
पूर्ण

अटल पूर्णांक nfp_flower_link_flows(काष्ठा nfp_fl_payload *merge_flow,
				 काष्ठा nfp_fl_payload *sub_flow)
अणु
	काष्ठा nfp_fl_payload_link *link;

	link = kदो_स्मृति(माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस -ENOMEM;

	link->merge_flow.flow = merge_flow;
	list_add_tail(&link->merge_flow.list, &merge_flow->linked_flows);
	link->sub_flow.flow = sub_flow;
	list_add_tail(&link->sub_flow.list, &sub_flow->linked_flows);

	वापस 0;
पूर्ण

/**
 * nfp_flower_merge_offloaded_flows() - Merge 2 existing flows to single flow.
 * @app:	Poपूर्णांकer to the APP handle
 * @sub_flow1:	Initial flow matched to produce merge hपूर्णांक
 * @sub_flow2:	Post recirculation flow matched in merge hपूर्णांक
 *
 * Combines 2 flows (अगर valid) to a single flow, removing the initial from hw
 * and offloading the new, merged flow.
 *
 * Return: negative value on error, 0 in success.
 */
पूर्णांक nfp_flower_merge_offloaded_flows(काष्ठा nfp_app *app,
				     काष्ठा nfp_fl_payload *sub_flow1,
				     काष्ठा nfp_fl_payload *sub_flow2)
अणु
	काष्ठा flow_cls_offload merge_tc_off;
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा netlink_ext_ack *extack = शून्य;
	काष्ठा nfp_fl_payload *merge_flow;
	काष्ठा nfp_fl_key_ls merge_key_ls;
	काष्ठा nfp_merge_info *merge_info;
	u64 parent_ctx = 0;
	पूर्णांक err;

	ASSERT_RTNL();

	extack = merge_tc_off.common.extack;
	अगर (sub_flow1 == sub_flow2 ||
	    nfp_flower_is_merge_flow(sub_flow1) ||
	    nfp_flower_is_merge_flow(sub_flow2))
		वापस -EINVAL;

	/* check अगर the two flows are alपढ़ोy merged */
	parent_ctx = (u64)(be32_to_cpu(sub_flow1->meta.host_ctx_id)) << 32;
	parent_ctx |= (u64)(be32_to_cpu(sub_flow2->meta.host_ctx_id));
	अगर (rhashtable_lookup_fast(&priv->merge_table,
				   &parent_ctx, merge_table_params)) अणु
		nfp_flower_cmsg_warn(app, "The two flows are already merged.\n");
		वापस 0;
	पूर्ण

	err = nfp_flower_can_merge(sub_flow1, sub_flow2);
	अगर (err)
		वापस err;

	merge_key_ls.key_size = sub_flow1->meta.key_len;

	merge_flow = nfp_flower_allocate_new(&merge_key_ls);
	अगर (!merge_flow)
		वापस -ENOMEM;

	merge_flow->tc_flower_cookie = (अचिन्हित दीर्घ)merge_flow;
	merge_flow->ingress_dev = sub_flow1->ingress_dev;

	स_नकल(merge_flow->unmasked_data, sub_flow1->unmasked_data,
	       sub_flow1->meta.key_len);
	स_नकल(merge_flow->mask_data, sub_flow1->mask_data,
	       sub_flow1->meta.mask_len);

	err = nfp_flower_merge_action(sub_flow1, sub_flow2, merge_flow);
	अगर (err)
		जाओ err_destroy_merge_flow;

	err = nfp_flower_link_flows(merge_flow, sub_flow1);
	अगर (err)
		जाओ err_destroy_merge_flow;

	err = nfp_flower_link_flows(merge_flow, sub_flow2);
	अगर (err)
		जाओ err_unlink_sub_flow1;

	merge_tc_off.cookie = merge_flow->tc_flower_cookie;
	err = nfp_compile_flow_metadata(app, &merge_tc_off, merge_flow,
					merge_flow->ingress_dev, extack);
	अगर (err)
		जाओ err_unlink_sub_flow2;

	err = rhashtable_insert_fast(&priv->flow_table, &merge_flow->fl_node,
				     nfp_flower_table_params);
	अगर (err)
		जाओ err_release_metadata;

	merge_info = kदो_स्मृति(माप(*merge_info), GFP_KERNEL);
	अगर (!merge_info) अणु
		err = -ENOMEM;
		जाओ err_हटाओ_rhash;
	पूर्ण
	merge_info->parent_ctx = parent_ctx;
	err = rhashtable_insert_fast(&priv->merge_table, &merge_info->ht_node,
				     merge_table_params);
	अगर (err)
		जाओ err_destroy_merge_info;

	err = nfp_flower_xmit_flow(app, merge_flow,
				   NFP_FLOWER_CMSG_TYPE_FLOW_MOD);
	अगर (err)
		जाओ err_हटाओ_merge_info;

	merge_flow->in_hw = true;
	sub_flow1->in_hw = false;

	वापस 0;

err_हटाओ_merge_info:
	WARN_ON_ONCE(rhashtable_हटाओ_fast(&priv->merge_table,
					    &merge_info->ht_node,
					    merge_table_params));
err_destroy_merge_info:
	kमुक्त(merge_info);
err_हटाओ_rhash:
	WARN_ON_ONCE(rhashtable_हटाओ_fast(&priv->flow_table,
					    &merge_flow->fl_node,
					    nfp_flower_table_params));
err_release_metadata:
	nfp_modअगरy_flow_metadata(app, merge_flow);
err_unlink_sub_flow2:
	nfp_flower_unlink_flows(merge_flow, sub_flow2);
err_unlink_sub_flow1:
	nfp_flower_unlink_flows(merge_flow, sub_flow1);
err_destroy_merge_flow:
	kमुक्त(merge_flow->action_data);
	kमुक्त(merge_flow->mask_data);
	kमुक्त(merge_flow->unmasked_data);
	kमुक्त(merge_flow);
	वापस err;
पूर्ण

/**
 * nfp_flower_validate_pre_tun_rule()
 * @app:	Poपूर्णांकer to the APP handle
 * @flow:	Poपूर्णांकer to NFP flow representation of rule
 * @key_ls:	Poपूर्णांकer to NFP key layers काष्ठाure
 * @extack:	Netlink extended ACK report
 *
 * Verअगरies the flow as a pre-tunnel rule.
 *
 * Return: negative value on error, 0 अगर verअगरied.
 */
अटल पूर्णांक
nfp_flower_validate_pre_tun_rule(काष्ठा nfp_app *app,
				 काष्ठा nfp_fl_payload *flow,
				 काष्ठा nfp_fl_key_ls *key_ls,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_flower_meta_tci *meta_tci;
	काष्ठा nfp_flower_mac_mpls *mac;
	u8 *ext = flow->unmasked_data;
	काष्ठा nfp_fl_act_head *act;
	u8 *mask = flow->mask_data;
	bool vlan = false;
	पूर्णांक act_offset;
	u8 key_layer;

	meta_tci = (काष्ठा nfp_flower_meta_tci *)flow->unmasked_data;
	key_layer = key_ls->key_layer;
	अगर (!(priv->flower_ext_feats & NFP_FL_FEATS_VLAN_QINQ)) अणु
		अगर (meta_tci->tci & cpu_to_be16(NFP_FLOWER_MASK_VLAN_PRESENT)) अणु
			u16 vlan_tci = be16_to_cpu(meta_tci->tci);

			vlan_tci &= ~NFP_FLOWER_MASK_VLAN_PRESENT;
			flow->pre_tun_rule.vlan_tci = cpu_to_be16(vlan_tci);
			vlan = true;
		पूर्ण अन्यथा अणु
			flow->pre_tun_rule.vlan_tci = cpu_to_be16(0xffff);
		पूर्ण
	पूर्ण

	अगर (key_layer & ~NFP_FLOWER_PRE_TUN_RULE_FIELDS) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: too many match fields");
		वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अगर (key_ls->key_layer_two & ~NFP_FLOWER_LAYER2_QINQ) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: non-vlan in extended match fields");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!(key_layer & NFP_FLOWER_LAYER_MAC)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: MAC fields match required");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!(key_layer & NFP_FLOWER_LAYER_IPV4) &&
	    !(key_layer & NFP_FLOWER_LAYER_IPV6)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: match on ipv4/ipv6 eth_type must be present");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Skip fields known to exist. */
	mask += माप(काष्ठा nfp_flower_meta_tci);
	ext += माप(काष्ठा nfp_flower_meta_tci);
	अगर (key_ls->key_layer_two) अणु
		mask += माप(काष्ठा nfp_flower_ext_meta);
		ext += माप(काष्ठा nfp_flower_ext_meta);
	पूर्ण
	mask += माप(काष्ठा nfp_flower_in_port);
	ext += माप(काष्ठा nfp_flower_in_port);

	/* Ensure destination MAC address matches pre_tun_dev. */
	mac = (काष्ठा nfp_flower_mac_mpls *)ext;
	अगर (स_भेद(&mac->mac_dst[0], flow->pre_tun_rule.dev->dev_addr, 6)) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: dest MAC must match output dev MAC");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Ensure destination MAC address is fully matched. */
	mac = (काष्ठा nfp_flower_mac_mpls *)mask;
	अगर (!is_broadcast_ether_addr(&mac->mac_dst[0])) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: dest MAC field must not be masked");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (mac->mpls_lse) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: MPLS not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	mask += माप(काष्ठा nfp_flower_mac_mpls);
	ext += माप(काष्ठा nfp_flower_mac_mpls);
	अगर (key_layer & NFP_FLOWER_LAYER_IPV4 ||
	    key_layer & NFP_FLOWER_LAYER_IPV6) अणु
		/* Flags and proto fields have same offset in IPv4 and IPv6. */
		पूर्णांक ip_flags = दुरत्व(काष्ठा nfp_flower_ipv4, ip_ext.flags);
		पूर्णांक ip_proto = दुरत्व(काष्ठा nfp_flower_ipv4, ip_ext.proto);
		पूर्णांक size;
		पूर्णांक i;

		size = key_layer & NFP_FLOWER_LAYER_IPV4 ?
			माप(काष्ठा nfp_flower_ipv4) :
			माप(काष्ठा nfp_flower_ipv6);


		/* Ensure proto and flags are the only IP layer fields. */
		क्रम (i = 0; i < size; i++)
			अगर (mask[i] && i != ip_flags && i != ip_proto) अणु
				NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: only flags and proto can be matched in ip header");
				वापस -EOPNOTSUPP;
			पूर्ण
		ext += size;
		mask += size;
	पूर्ण

	अगर ((priv->flower_ext_feats & NFP_FL_FEATS_VLAN_QINQ)) अणु
		अगर (key_ls->key_layer_two & NFP_FLOWER_LAYER2_QINQ) अणु
			काष्ठा nfp_flower_vlan *vlan_tags;
			u16 vlan_tci;

			vlan_tags = (काष्ठा nfp_flower_vlan *)ext;

			vlan_tci = be16_to_cpu(vlan_tags->outer_tci);

			vlan_tci &= ~NFP_FLOWER_MASK_VLAN_PRESENT;
			flow->pre_tun_rule.vlan_tci = cpu_to_be16(vlan_tci);
			vlan = true;
		पूर्ण अन्यथा अणु
			flow->pre_tun_rule.vlan_tci = cpu_to_be16(0xffff);
		पूर्ण
	पूर्ण

	/* Action must be a single egress or pop_vlan and egress. */
	act_offset = 0;
	act = (काष्ठा nfp_fl_act_head *)&flow->action_data[act_offset];
	अगर (vlan) अणु
		अगर (act->jump_id != NFP_FL_ACTION_OPCODE_POP_VLAN) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: match on VLAN must have VLAN pop as first action");
			वापस -EOPNOTSUPP;
		पूर्ण

		act_offset += act->len_lw << NFP_FL_LW_SIZ;
		act = (काष्ठा nfp_fl_act_head *)&flow->action_data[act_offset];
	पूर्ण

	अगर (act->jump_id != NFP_FL_ACTION_OPCODE_OUTPUT) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: non egress action detected where egress was expected");
		वापस -EOPNOTSUPP;
	पूर्ण

	act_offset += act->len_lw << NFP_FL_LW_SIZ;

	/* Ensure there are no more actions after egress. */
	अगर (act_offset != flow->meta.act_len) अणु
		NL_SET_ERR_MSG_MOD(extack, "unsupported pre-tunnel rule: egress is not the last action");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nfp_flower_add_offload() - Adds a new flow to hardware.
 * @app:	Poपूर्णांकer to the APP handle
 * @netdev:	netdev काष्ठाure.
 * @flow:	TC flower classअगरier offload काष्ठाure.
 *
 * Adds a new flow to the repeated hash काष्ठाure and action payload.
 *
 * Return: negative value on error, 0 अगर configured successfully.
 */
अटल पूर्णांक
nfp_flower_add_offload(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
		       काष्ठा flow_cls_offload *flow)
अणु
	क्रमागत nfp_flower_tun_type tun_type = NFP_FL_TUNNEL_NONE;
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा netlink_ext_ack *extack = शून्य;
	काष्ठा nfp_fl_payload *flow_pay;
	काष्ठा nfp_fl_key_ls *key_layer;
	काष्ठा nfp_port *port = शून्य;
	पूर्णांक err;

	extack = flow->common.extack;
	अगर (nfp_netdev_is_nfp_repr(netdev))
		port = nfp_port_from_netdev(netdev);

	key_layer = kदो_स्मृति(माप(*key_layer), GFP_KERNEL);
	अगर (!key_layer)
		वापस -ENOMEM;

	err = nfp_flower_calculate_key_layers(app, netdev, key_layer, flow,
					      &tun_type, extack);
	अगर (err)
		जाओ err_मुक्त_key_ls;

	flow_pay = nfp_flower_allocate_new(key_layer);
	अगर (!flow_pay) अणु
		err = -ENOMEM;
		जाओ err_मुक्त_key_ls;
	पूर्ण

	err = nfp_flower_compile_flow_match(app, flow, key_layer, netdev,
					    flow_pay, tun_type, extack);
	अगर (err)
		जाओ err_destroy_flow;

	err = nfp_flower_compile_action(app, flow, netdev, flow_pay, extack);
	अगर (err)
		जाओ err_destroy_flow;

	अगर (flow_pay->pre_tun_rule.dev) अणु
		err = nfp_flower_validate_pre_tun_rule(app, flow_pay, key_layer, extack);
		अगर (err)
			जाओ err_destroy_flow;
	पूर्ण

	err = nfp_compile_flow_metadata(app, flow, flow_pay, netdev, extack);
	अगर (err)
		जाओ err_destroy_flow;

	flow_pay->tc_flower_cookie = flow->cookie;
	err = rhashtable_insert_fast(&priv->flow_table, &flow_pay->fl_node,
				     nfp_flower_table_params);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot insert flow into tables for offloads");
		जाओ err_release_metadata;
	पूर्ण

	अगर (flow_pay->pre_tun_rule.dev)
		err = nfp_flower_xmit_pre_tun_flow(app, flow_pay);
	अन्यथा
		err = nfp_flower_xmit_flow(app, flow_pay,
					   NFP_FLOWER_CMSG_TYPE_FLOW_ADD);
	अगर (err)
		जाओ err_हटाओ_rhash;

	अगर (port)
		port->tc_offload_cnt++;

	flow_pay->in_hw = true;

	/* Deallocate flow payload when flower rule has been destroyed. */
	kमुक्त(key_layer);

	वापस 0;

err_हटाओ_rhash:
	WARN_ON_ONCE(rhashtable_हटाओ_fast(&priv->flow_table,
					    &flow_pay->fl_node,
					    nfp_flower_table_params));
err_release_metadata:
	nfp_modअगरy_flow_metadata(app, flow_pay);
err_destroy_flow:
	अगर (flow_pay->nfp_tun_ipv6)
		nfp_tunnel_put_ipv6_off(app, flow_pay->nfp_tun_ipv6);
	kमुक्त(flow_pay->action_data);
	kमुक्त(flow_pay->mask_data);
	kमुक्त(flow_pay->unmasked_data);
	kमुक्त(flow_pay);
err_मुक्त_key_ls:
	kमुक्त(key_layer);
	वापस err;
पूर्ण

अटल व्योम
nfp_flower_हटाओ_merge_flow(काष्ठा nfp_app *app,
			     काष्ठा nfp_fl_payload *del_sub_flow,
			     काष्ठा nfp_fl_payload *merge_flow)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_fl_payload_link *link, *temp;
	काष्ठा nfp_merge_info *merge_info;
	काष्ठा nfp_fl_payload *origin;
	u64 parent_ctx = 0;
	bool mod = false;
	पूर्णांक err;

	link = list_first_entry(&merge_flow->linked_flows,
				काष्ठा nfp_fl_payload_link, merge_flow.list);
	origin = link->sub_flow.flow;

	/* Re-add rule the merge had overwritten अगर it has not been deleted. */
	अगर (origin != del_sub_flow)
		mod = true;

	err = nfp_modअगरy_flow_metadata(app, merge_flow);
	अगर (err) अणु
		nfp_flower_cmsg_warn(app, "Metadata fail for merge flow delete.\n");
		जाओ err_मुक्त_links;
	पूर्ण

	अगर (!mod) अणु
		err = nfp_flower_xmit_flow(app, merge_flow,
					   NFP_FLOWER_CMSG_TYPE_FLOW_DEL);
		अगर (err) अणु
			nfp_flower_cmsg_warn(app, "Failed to delete merged flow.\n");
			जाओ err_मुक्त_links;
		पूर्ण
	पूर्ण अन्यथा अणु
		__nfp_modअगरy_flow_metadata(priv, origin);
		err = nfp_flower_xmit_flow(app, origin,
					   NFP_FLOWER_CMSG_TYPE_FLOW_MOD);
		अगर (err)
			nfp_flower_cmsg_warn(app, "Failed to revert merge flow.\n");
		origin->in_hw = true;
	पूर्ण

err_मुक्त_links:
	/* Clean any links connected with the merged flow. */
	list_क्रम_each_entry_safe(link, temp, &merge_flow->linked_flows,
				 merge_flow.list) अणु
		u32 ctx_id = be32_to_cpu(link->sub_flow.flow->meta.host_ctx_id);

		parent_ctx = (parent_ctx << 32) | (u64)(ctx_id);
		nfp_flower_unlink_flow(link);
	पूर्ण

	merge_info = rhashtable_lookup_fast(&priv->merge_table,
					    &parent_ctx,
					    merge_table_params);
	अगर (merge_info) अणु
		WARN_ON_ONCE(rhashtable_हटाओ_fast(&priv->merge_table,
						    &merge_info->ht_node,
						    merge_table_params));
		kमुक्त(merge_info);
	पूर्ण

	kमुक्त(merge_flow->action_data);
	kमुक्त(merge_flow->mask_data);
	kमुक्त(merge_flow->unmasked_data);
	WARN_ON_ONCE(rhashtable_हटाओ_fast(&priv->flow_table,
					    &merge_flow->fl_node,
					    nfp_flower_table_params));
	kमुक्त_rcu(merge_flow, rcu);
पूर्ण

अटल व्योम
nfp_flower_del_linked_merge_flows(काष्ठा nfp_app *app,
				  काष्ठा nfp_fl_payload *sub_flow)
अणु
	काष्ठा nfp_fl_payload_link *link, *temp;

	/* Remove any merge flow क्रमmed from the deleted sub_flow. */
	list_क्रम_each_entry_safe(link, temp, &sub_flow->linked_flows,
				 sub_flow.list)
		nfp_flower_हटाओ_merge_flow(app, sub_flow,
					     link->merge_flow.flow);
पूर्ण

/**
 * nfp_flower_del_offload() - Removes a flow from hardware.
 * @app:	Poपूर्णांकer to the APP handle
 * @netdev:	netdev काष्ठाure.
 * @flow:	TC flower classअगरier offload काष्ठाure
 *
 * Removes a flow from the repeated hashत काष्ठाure and clears the
 * action payload. Any flows merged from this are also deleted.
 *
 * Return: negative value on error, 0 अगर हटाओd successfully.
 */
अटल पूर्णांक
nfp_flower_del_offload(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
		       काष्ठा flow_cls_offload *flow)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा netlink_ext_ack *extack = शून्य;
	काष्ठा nfp_fl_payload *nfp_flow;
	काष्ठा nfp_port *port = शून्य;
	पूर्णांक err;

	extack = flow->common.extack;
	अगर (nfp_netdev_is_nfp_repr(netdev))
		port = nfp_port_from_netdev(netdev);

	nfp_flow = nfp_flower_search_fl_table(app, flow->cookie, netdev);
	अगर (!nfp_flow) अणु
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot remove flow that does not exist");
		वापस -ENOENT;
	पूर्ण

	err = nfp_modअगरy_flow_metadata(app, nfp_flow);
	अगर (err)
		जाओ err_मुक्त_merge_flow;

	अगर (nfp_flow->nfp_tun_ipv4_addr)
		nfp_tunnel_del_ipv4_off(app, nfp_flow->nfp_tun_ipv4_addr);

	अगर (nfp_flow->nfp_tun_ipv6)
		nfp_tunnel_put_ipv6_off(app, nfp_flow->nfp_tun_ipv6);

	अगर (!nfp_flow->in_hw) अणु
		err = 0;
		जाओ err_मुक्त_merge_flow;
	पूर्ण

	अगर (nfp_flow->pre_tun_rule.dev)
		err = nfp_flower_xmit_pre_tun_del_flow(app, nfp_flow);
	अन्यथा
		err = nfp_flower_xmit_flow(app, nfp_flow,
					   NFP_FLOWER_CMSG_TYPE_FLOW_DEL);
	/* Fall through on error. */

err_मुक्त_merge_flow:
	nfp_flower_del_linked_merge_flows(app, nfp_flow);
	अगर (port)
		port->tc_offload_cnt--;
	kमुक्त(nfp_flow->action_data);
	kमुक्त(nfp_flow->mask_data);
	kमुक्त(nfp_flow->unmasked_data);
	WARN_ON_ONCE(rhashtable_हटाओ_fast(&priv->flow_table,
					    &nfp_flow->fl_node,
					    nfp_flower_table_params));
	kमुक्त_rcu(nfp_flow, rcu);
	वापस err;
पूर्ण

अटल व्योम
__nfp_flower_update_merge_stats(काष्ठा nfp_app *app,
				काष्ठा nfp_fl_payload *merge_flow)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा nfp_fl_payload_link *link;
	काष्ठा nfp_fl_payload *sub_flow;
	u64 pkts, bytes, used;
	u32 ctx_id;

	ctx_id = be32_to_cpu(merge_flow->meta.host_ctx_id);
	pkts = priv->stats[ctx_id].pkts;
	/* Do not cycle subflows अगर no stats to distribute. */
	अगर (!pkts)
		वापस;
	bytes = priv->stats[ctx_id].bytes;
	used = priv->stats[ctx_id].used;

	/* Reset stats क्रम the merge flow. */
	priv->stats[ctx_id].pkts = 0;
	priv->stats[ctx_id].bytes = 0;

	/* The merge flow has received stats updates from firmware.
	 * Distribute these stats to all subflows that क्रमm the merge.
	 * The stats will collected from TC via the subflows.
	 */
	list_क्रम_each_entry(link, &merge_flow->linked_flows, merge_flow.list) अणु
		sub_flow = link->sub_flow.flow;
		ctx_id = be32_to_cpu(sub_flow->meta.host_ctx_id);
		priv->stats[ctx_id].pkts += pkts;
		priv->stats[ctx_id].bytes += bytes;
		priv->stats[ctx_id].used = max_t(u64, used,
						 priv->stats[ctx_id].used);
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_update_merge_stats(काष्ठा nfp_app *app,
			      काष्ठा nfp_fl_payload *sub_flow)
अणु
	काष्ठा nfp_fl_payload_link *link;

	/* Get merge flows that the subflow क्रमms to distribute their stats. */
	list_क्रम_each_entry(link, &sub_flow->linked_flows, sub_flow.list)
		__nfp_flower_update_merge_stats(app, link->merge_flow.flow);
पूर्ण

/**
 * nfp_flower_get_stats() - Populates flow stats obtained from hardware.
 * @app:	Poपूर्णांकer to the APP handle
 * @netdev:	Netdev काष्ठाure.
 * @flow:	TC flower classअगरier offload काष्ठाure
 *
 * Populates a flow statistics काष्ठाure whichत which corresponds to a
 * specअगरic flow.
 *
 * Return: negative value on error, 0 अगर stats populated successfully.
 */
अटल पूर्णांक
nfp_flower_get_stats(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
		     काष्ठा flow_cls_offload *flow)
अणु
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा netlink_ext_ack *extack = शून्य;
	काष्ठा nfp_fl_payload *nfp_flow;
	u32 ctx_id;

	extack = flow->common.extack;
	nfp_flow = nfp_flower_search_fl_table(app, flow->cookie, netdev);
	अगर (!nfp_flow) अणु
		NL_SET_ERR_MSG_MOD(extack, "invalid entry: cannot dump stats for flow that does not exist");
		वापस -EINVAL;
	पूर्ण

	ctx_id = be32_to_cpu(nfp_flow->meta.host_ctx_id);

	spin_lock_bh(&priv->stats_lock);
	/* If request is क्रम a sub_flow, update stats from merged flows. */
	अगर (!list_empty(&nfp_flow->linked_flows))
		nfp_flower_update_merge_stats(app, nfp_flow);

	flow_stats_update(&flow->stats, priv->stats[ctx_id].bytes,
			  priv->stats[ctx_id].pkts, 0, priv->stats[ctx_id].used,
			  FLOW_ACTION_HW_STATS_DELAYED);

	priv->stats[ctx_id].pkts = 0;
	priv->stats[ctx_id].bytes = 0;
	spin_unlock_bh(&priv->stats_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_repr_offload(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			काष्ठा flow_cls_offload *flower)
अणु
	अगर (!eth_proto_is_802_3(flower->common.protocol))
		वापस -EOPNOTSUPP;

	चयन (flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस nfp_flower_add_offload(app, netdev, flower);
	हाल FLOW_CLS_DESTROY:
		वापस nfp_flower_del_offload(app, netdev, flower);
	हाल FLOW_CLS_STATS:
		वापस nfp_flower_get_stats(app, netdev, flower);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक nfp_flower_setup_tc_block_cb(क्रमागत tc_setup_type type,
					व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा nfp_repr *repr = cb_priv;

	अगर (!tc_cls_can_offload_and_chain0(repr->netdev, type_data))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस nfp_flower_repr_offload(repr->app, repr->netdev,
					       type_data);
	हाल TC_SETUP_CLSMATCHALL:
		वापस nfp_flower_setup_qos_offload(repr->app, repr->netdev,
						    type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल LIST_HEAD(nfp_block_cb_list);

अटल पूर्णांक nfp_flower_setup_tc_block(काष्ठा net_device *netdev,
				     काष्ठा flow_block_offload *f)
अणु
	काष्ठा nfp_repr *repr = netdev_priv(netdev);
	काष्ठा nfp_flower_repr_priv *repr_priv;
	काष्ठा flow_block_cb *block_cb;

	अगर (f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		वापस -EOPNOTSUPP;

	repr_priv = repr->app_priv;
	repr_priv->block_shared = f->block_shared;
	f->driver_block_list = &nfp_block_cb_list;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		अगर (flow_block_cb_is_busy(nfp_flower_setup_tc_block_cb, repr,
					  &nfp_block_cb_list))
			वापस -EBUSY;

		block_cb = flow_block_cb_alloc(nfp_flower_setup_tc_block_cb,
					       repr, repr, शून्य);
		अगर (IS_ERR(block_cb))
			वापस PTR_ERR(block_cb);

		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &nfp_block_cb_list);
		वापस 0;
	हाल FLOW_BLOCK_UNBIND:
		block_cb = flow_block_cb_lookup(f->block,
						nfp_flower_setup_tc_block_cb,
						repr);
		अगर (!block_cb)
			वापस -ENOENT;

		flow_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक nfp_flower_setup_tc(काष्ठा nfp_app *app, काष्ठा net_device *netdev,
			क्रमागत tc_setup_type type, व्योम *type_data)
अणु
	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस nfp_flower_setup_tc_block(netdev, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

काष्ठा nfp_flower_indr_block_cb_priv अणु
	काष्ठा net_device *netdev;
	काष्ठा nfp_app *app;
	काष्ठा list_head list;
पूर्ण;

अटल काष्ठा nfp_flower_indr_block_cb_priv *
nfp_flower_indr_block_cb_priv_lookup(काष्ठा nfp_app *app,
				     काष्ठा net_device *netdev)
अणु
	काष्ठा nfp_flower_indr_block_cb_priv *cb_priv;
	काष्ठा nfp_flower_priv *priv = app->priv;

	/* All callback list access should be रक्षित by RTNL. */
	ASSERT_RTNL();

	list_क्रम_each_entry(cb_priv, &priv->indr_block_cb_priv, list)
		अगर (cb_priv->netdev == netdev)
			वापस cb_priv;

	वापस शून्य;
पूर्ण

अटल पूर्णांक nfp_flower_setup_indr_block_cb(क्रमागत tc_setup_type type,
					  व्योम *type_data, व्योम *cb_priv)
अणु
	काष्ठा nfp_flower_indr_block_cb_priv *priv = cb_priv;
	काष्ठा flow_cls_offload *flower = type_data;

	अगर (flower->common.chain_index)
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस nfp_flower_repr_offload(priv->app, priv->netdev,
					       type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

व्योम nfp_flower_setup_indr_tc_release(व्योम *cb_priv)
अणु
	काष्ठा nfp_flower_indr_block_cb_priv *priv = cb_priv;

	list_del(&priv->list);
	kमुक्त(priv);
पूर्ण

अटल पूर्णांक
nfp_flower_setup_indr_tc_block(काष्ठा net_device *netdev, काष्ठा Qdisc *sch, काष्ठा nfp_app *app,
			       काष्ठा flow_block_offload *f, व्योम *data,
			       व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb))
अणु
	काष्ठा nfp_flower_indr_block_cb_priv *cb_priv;
	काष्ठा nfp_flower_priv *priv = app->priv;
	काष्ठा flow_block_cb *block_cb;

	अगर ((f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS &&
	     !nfp_flower_पूर्णांकernal_port_can_offload(app, netdev)) ||
	    (f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS &&
	     nfp_flower_पूर्णांकernal_port_can_offload(app, netdev)))
		वापस -EOPNOTSUPP;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		cb_priv = nfp_flower_indr_block_cb_priv_lookup(app, netdev);
		अगर (cb_priv &&
		    flow_block_cb_is_busy(nfp_flower_setup_indr_block_cb,
					  cb_priv,
					  &nfp_block_cb_list))
			वापस -EBUSY;

		cb_priv = kदो_स्मृति(माप(*cb_priv), GFP_KERNEL);
		अगर (!cb_priv)
			वापस -ENOMEM;

		cb_priv->netdev = netdev;
		cb_priv->app = app;
		list_add(&cb_priv->list, &priv->indr_block_cb_priv);

		block_cb = flow_indr_block_cb_alloc(nfp_flower_setup_indr_block_cb,
						    cb_priv, cb_priv,
						    nfp_flower_setup_indr_tc_release,
						    f, netdev, sch, data, app, cleanup);
		अगर (IS_ERR(block_cb)) अणु
			list_del(&cb_priv->list);
			kमुक्त(cb_priv);
			वापस PTR_ERR(block_cb);
		पूर्ण

		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &nfp_block_cb_list);
		वापस 0;
	हाल FLOW_BLOCK_UNBIND:
		cb_priv = nfp_flower_indr_block_cb_priv_lookup(app, netdev);
		अगर (!cb_priv)
			वापस -ENOENT;

		block_cb = flow_block_cb_lookup(f->block,
						nfp_flower_setup_indr_block_cb,
						cb_priv);
		अगर (!block_cb)
			वापस -ENOENT;

		flow_indr_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
nfp_flower_indr_setup_tc_cb(काष्ठा net_device *netdev, काष्ठा Qdisc *sch, व्योम *cb_priv,
			    क्रमागत tc_setup_type type, व्योम *type_data,
			    व्योम *data,
			    व्योम (*cleanup)(काष्ठा flow_block_cb *block_cb))
अणु
	अगर (!nfp_fl_is_netdev_to_offload(netdev))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस nfp_flower_setup_indr_tc_block(netdev, sch, cb_priv,
						      type_data, data, cleanup);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण
