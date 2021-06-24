<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#समावेश <linux/bitfield.h>
#समावेश <net/pkt_cls.h>

#समावेश "cmsg.h"
#समावेश "main.h"

अटल व्योम
nfp_flower_compile_meta_tci(काष्ठा nfp_flower_meta_tci *ext,
			    काष्ठा nfp_flower_meta_tci *msk,
			    काष्ठा flow_rule *rule, u8 key_type, bool qinq_sup)
अणु
	u16 पंचांगp_tci;

	स_रखो(ext, 0, माप(काष्ठा nfp_flower_meta_tci));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_meta_tci));

	/* Populate the metadata frame. */
	ext->nfp_flow_key_layer = key_type;
	ext->mask_id = ~0;

	msk->nfp_flow_key_layer = key_type;
	msk->mask_id = ~0;

	अगर (!qinq_sup && flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		/* Populate the tci field. */
		पंचांगp_tci = NFP_FLOWER_MASK_VLAN_PRESENT;
		पंचांगp_tci |= FIELD_PREP(NFP_FLOWER_MASK_VLAN_PRIO,
				      match.key->vlan_priority) |
			   FIELD_PREP(NFP_FLOWER_MASK_VLAN_VID,
				      match.key->vlan_id);
		ext->tci = cpu_to_be16(पंचांगp_tci);

		पंचांगp_tci = NFP_FLOWER_MASK_VLAN_PRESENT;
		पंचांगp_tci |= FIELD_PREP(NFP_FLOWER_MASK_VLAN_PRIO,
				      match.mask->vlan_priority) |
			   FIELD_PREP(NFP_FLOWER_MASK_VLAN_VID,
				      match.mask->vlan_id);
		msk->tci = cpu_to_be16(पंचांगp_tci);
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_compile_ext_meta(काष्ठा nfp_flower_ext_meta *frame, u32 key_ext)
अणु
	frame->nfp_flow_key_layer2 = cpu_to_be32(key_ext);
पूर्ण

अटल पूर्णांक
nfp_flower_compile_port(काष्ठा nfp_flower_in_port *frame, u32 cmsg_port,
			bool mask_version, क्रमागत nfp_flower_tun_type tun_type,
			काष्ठा netlink_ext_ack *extack)
अणु
	अगर (mask_version) अणु
		frame->in_port = cpu_to_be32(~0);
		वापस 0;
	पूर्ण

	अगर (tun_type) अणु
		frame->in_port = cpu_to_be32(NFP_FL_PORT_TYPE_TUN | tun_type);
	पूर्ण अन्यथा अणु
		अगर (!cmsg_port) अणु
			NL_SET_ERR_MSG_MOD(extack, "unsupported offload: invalid ingress interface for match offload");
			वापस -EOPNOTSUPP;
		पूर्ण
		frame->in_port = cpu_to_be32(cmsg_port);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_flower_compile_mac(काष्ठा nfp_flower_mac_mpls *ext,
		       काष्ठा nfp_flower_mac_mpls *msk, काष्ठा flow_rule *rule,
		       काष्ठा netlink_ext_ack *extack)
अणु
	स_रखो(ext, 0, माप(काष्ठा nfp_flower_mac_mpls));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_mac_mpls));

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		/* Populate mac frame. */
		ether_addr_copy(ext->mac_dst, &match.key->dst[0]);
		ether_addr_copy(ext->mac_src, &match.key->src[0]);
		ether_addr_copy(msk->mac_dst, &match.mask->dst[0]);
		ether_addr_copy(msk->mac_src, &match.mask->src[0]);
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_MPLS)) अणु
		काष्ठा flow_match_mpls match;
		u32 t_mpls;

		flow_rule_match_mpls(rule, &match);

		/* Only support matching the first LSE */
		अगर (match.mask->used_lses != 1) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "unsupported offload: invalid LSE depth for MPLS match offload");
			वापस -EOPNOTSUPP;
		पूर्ण

		t_mpls = FIELD_PREP(NFP_FLOWER_MASK_MPLS_LB,
				    match.key->ls[0].mpls_label) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_TC,
				    match.key->ls[0].mpls_tc) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_BOS,
				    match.key->ls[0].mpls_bos) |
			 NFP_FLOWER_MASK_MPLS_Q;
		ext->mpls_lse = cpu_to_be32(t_mpls);
		t_mpls = FIELD_PREP(NFP_FLOWER_MASK_MPLS_LB,
				    match.mask->ls[0].mpls_label) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_TC,
				    match.mask->ls[0].mpls_tc) |
			 FIELD_PREP(NFP_FLOWER_MASK_MPLS_BOS,
				    match.mask->ls[0].mpls_bos) |
			 NFP_FLOWER_MASK_MPLS_Q;
		msk->mpls_lse = cpu_to_be32(t_mpls);
	पूर्ण अन्यथा अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		/* Check क्रम mpls ether type and set NFP_FLOWER_MASK_MPLS_Q
		 * bit, which indicates an mpls ether type but without any
		 * mpls fields.
		 */
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		अगर (match.key->n_proto == cpu_to_be16(ETH_P_MPLS_UC) ||
		    match.key->n_proto == cpu_to_be16(ETH_P_MPLS_MC)) अणु
			ext->mpls_lse = cpu_to_be32(NFP_FLOWER_MASK_MPLS_Q);
			msk->mpls_lse = cpu_to_be32(NFP_FLOWER_MASK_MPLS_Q);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nfp_flower_compile_tport(काष्ठा nfp_flower_tp_ports *ext,
			 काष्ठा nfp_flower_tp_ports *msk,
			 काष्ठा flow_rule *rule)
अणु
	स_रखो(ext, 0, माप(काष्ठा nfp_flower_tp_ports));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_tp_ports));

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		ext->port_src = match.key->src;
		ext->port_dst = match.key->dst;
		msk->port_src = match.mask->src;
		msk->port_dst = match.mask->dst;
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_compile_ip_ext(काष्ठा nfp_flower_ip_ext *ext,
			  काष्ठा nfp_flower_ip_ext *msk, काष्ठा flow_rule *rule)
अणु
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		ext->proto = match.key->ip_proto;
		msk->proto = match.mask->ip_proto;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IP)) अणु
		काष्ठा flow_match_ip match;

		flow_rule_match_ip(rule, &match);
		ext->tos = match.key->tos;
		ext->ttl = match.key->ttl;
		msk->tos = match.mask->tos;
		msk->ttl = match.mask->ttl;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_TCP)) अणु
		u16 tcp_flags, tcp_flags_mask;
		काष्ठा flow_match_tcp match;

		flow_rule_match_tcp(rule, &match);
		tcp_flags = be16_to_cpu(match.key->flags);
		tcp_flags_mask = be16_to_cpu(match.mask->flags);

		अगर (tcp_flags & TCPHDR_FIN)
			ext->flags |= NFP_FL_TCP_FLAG_FIN;
		अगर (tcp_flags_mask & TCPHDR_FIN)
			msk->flags |= NFP_FL_TCP_FLAG_FIN;

		अगर (tcp_flags & TCPHDR_SYN)
			ext->flags |= NFP_FL_TCP_FLAG_SYN;
		अगर (tcp_flags_mask & TCPHDR_SYN)
			msk->flags |= NFP_FL_TCP_FLAG_SYN;

		अगर (tcp_flags & TCPHDR_RST)
			ext->flags |= NFP_FL_TCP_FLAG_RST;
		अगर (tcp_flags_mask & TCPHDR_RST)
			msk->flags |= NFP_FL_TCP_FLAG_RST;

		अगर (tcp_flags & TCPHDR_PSH)
			ext->flags |= NFP_FL_TCP_FLAG_PSH;
		अगर (tcp_flags_mask & TCPHDR_PSH)
			msk->flags |= NFP_FL_TCP_FLAG_PSH;

		अगर (tcp_flags & TCPHDR_URG)
			ext->flags |= NFP_FL_TCP_FLAG_URG;
		अगर (tcp_flags_mask & TCPHDR_URG)
			msk->flags |= NFP_FL_TCP_FLAG_URG;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(rule, &match);
		अगर (match.key->flags & FLOW_DIS_IS_FRAGMENT)
			ext->flags |= NFP_FL_IP_FRAGMENTED;
		अगर (match.mask->flags & FLOW_DIS_IS_FRAGMENT)
			msk->flags |= NFP_FL_IP_FRAGMENTED;
		अगर (match.key->flags & FLOW_DIS_FIRST_FRAG)
			ext->flags |= NFP_FL_IP_FRAG_FIRST;
		अगर (match.mask->flags & FLOW_DIS_FIRST_FRAG)
			msk->flags |= NFP_FL_IP_FRAG_FIRST;
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_fill_vlan(काष्ठा flow_dissector_key_vlan *key,
		     काष्ठा nfp_flower_vlan *frame,
		     bool outer_vlan)
अणु
	u16 tci;

	tci = NFP_FLOWER_MASK_VLAN_PRESENT;
	tci |= FIELD_PREP(NFP_FLOWER_MASK_VLAN_PRIO,
			  key->vlan_priority) |
	       FIELD_PREP(NFP_FLOWER_MASK_VLAN_VID,
			  key->vlan_id);

	अगर (outer_vlan) अणु
		frame->outer_tci = cpu_to_be16(tci);
		frame->outer_tpid = key->vlan_tpid;
	पूर्ण अन्यथा अणु
		frame->inner_tci = cpu_to_be16(tci);
		frame->inner_tpid = key->vlan_tpid;
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_compile_vlan(काष्ठा nfp_flower_vlan *ext,
			काष्ठा nfp_flower_vlan *msk,
			काष्ठा flow_rule *rule)
अणु
	काष्ठा flow_match_vlan match;

	स_रखो(ext, 0, माप(काष्ठा nfp_flower_vlan));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_vlan));

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		flow_rule_match_vlan(rule, &match);
		nfp_flower_fill_vlan(match.key, ext, true);
		nfp_flower_fill_vlan(match.mask, msk, true);
	पूर्ण
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CVLAN)) अणु
		flow_rule_match_cvlan(rule, &match);
		nfp_flower_fill_vlan(match.key, ext, false);
		nfp_flower_fill_vlan(match.mask, msk, false);
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_compile_ipv4(काष्ठा nfp_flower_ipv4 *ext,
			काष्ठा nfp_flower_ipv4 *msk, काष्ठा flow_rule *rule)
अणु
	काष्ठा flow_match_ipv4_addrs match;

	स_रखो(ext, 0, माप(काष्ठा nfp_flower_ipv4));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_ipv4));

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) अणु
		flow_rule_match_ipv4_addrs(rule, &match);
		ext->ipv4_src = match.key->src;
		ext->ipv4_dst = match.key->dst;
		msk->ipv4_src = match.mask->src;
		msk->ipv4_dst = match.mask->dst;
	पूर्ण

	nfp_flower_compile_ip_ext(&ext->ip_ext, &msk->ip_ext, rule);
पूर्ण

अटल व्योम
nfp_flower_compile_ipv6(काष्ठा nfp_flower_ipv6 *ext,
			काष्ठा nfp_flower_ipv6 *msk, काष्ठा flow_rule *rule)
अणु
	स_रखो(ext, 0, माप(काष्ठा nfp_flower_ipv6));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_ipv6));

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS)) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);
		ext->ipv6_src = match.key->src;
		ext->ipv6_dst = match.key->dst;
		msk->ipv6_src = match.mask->src;
		msk->ipv6_dst = match.mask->dst;
	पूर्ण

	nfp_flower_compile_ip_ext(&ext->ip_ext, &msk->ip_ext, rule);
पूर्ण

अटल पूर्णांक
nfp_flower_compile_geneve_opt(व्योम *ext, व्योम *msk, काष्ठा flow_rule *rule)
अणु
	काष्ठा flow_match_enc_opts match;

	flow_rule_match_enc_opts(rule, &match);
	स_नकल(ext, match.key->data, match.key->len);
	स_नकल(msk, match.mask->data, match.mask->len);

	वापस 0;
पूर्ण

अटल व्योम
nfp_flower_compile_tun_ipv4_addrs(काष्ठा nfp_flower_tun_ipv4 *ext,
				  काष्ठा nfp_flower_tun_ipv4 *msk,
				  काष्ठा flow_rule *rule)
अणु
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS)) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_enc_ipv4_addrs(rule, &match);
		ext->src = match.key->src;
		ext->dst = match.key->dst;
		msk->src = match.mask->src;
		msk->dst = match.mask->dst;
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_compile_tun_ipv6_addrs(काष्ठा nfp_flower_tun_ipv6 *ext,
				  काष्ठा nfp_flower_tun_ipv6 *msk,
				  काष्ठा flow_rule *rule)
अणु
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS)) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_enc_ipv6_addrs(rule, &match);
		ext->src = match.key->src;
		ext->dst = match.key->dst;
		msk->src = match.mask->src;
		msk->dst = match.mask->dst;
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_compile_tun_ip_ext(काष्ठा nfp_flower_tun_ip_ext *ext,
			      काष्ठा nfp_flower_tun_ip_ext *msk,
			      काष्ठा flow_rule *rule)
अणु
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_IP)) अणु
		काष्ठा flow_match_ip match;

		flow_rule_match_enc_ip(rule, &match);
		ext->tos = match.key->tos;
		ext->ttl = match.key->ttl;
		msk->tos = match.mask->tos;
		msk->ttl = match.mask->ttl;
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_compile_tun_udp_key(__be32 *key, __be32 *key_msk,
			       काष्ठा flow_rule *rule)
अणु
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) अणु
		काष्ठा flow_match_enc_keyid match;
		u32 vni;

		flow_rule_match_enc_keyid(rule, &match);
		vni = be32_to_cpu(match.key->keyid) << NFP_FL_TUN_VNI_OFFSET;
		*key = cpu_to_be32(vni);
		vni = be32_to_cpu(match.mask->keyid) << NFP_FL_TUN_VNI_OFFSET;
		*key_msk = cpu_to_be32(vni);
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_compile_tun_gre_key(__be32 *key, __be32 *key_msk, __be16 *flags,
			       __be16 *flags_msk, काष्ठा flow_rule *rule)
अणु
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) अणु
		काष्ठा flow_match_enc_keyid match;

		flow_rule_match_enc_keyid(rule, &match);
		*key = match.key->keyid;
		*key_msk = match.mask->keyid;

		*flags = cpu_to_be16(NFP_FL_GRE_FLAG_KEY);
		*flags_msk = cpu_to_be16(NFP_FL_GRE_FLAG_KEY);
	पूर्ण
पूर्ण

अटल व्योम
nfp_flower_compile_ipv4_gre_tun(काष्ठा nfp_flower_ipv4_gre_tun *ext,
				काष्ठा nfp_flower_ipv4_gre_tun *msk,
				काष्ठा flow_rule *rule)
अणु
	स_रखो(ext, 0, माप(काष्ठा nfp_flower_ipv4_gre_tun));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_ipv4_gre_tun));

	/* NVGRE is the only supported GRE tunnel type */
	ext->ethertype = cpu_to_be16(ETH_P_TEB);
	msk->ethertype = cpu_to_be16(~0);

	nfp_flower_compile_tun_ipv4_addrs(&ext->ipv4, &msk->ipv4, rule);
	nfp_flower_compile_tun_ip_ext(&ext->ip_ext, &msk->ip_ext, rule);
	nfp_flower_compile_tun_gre_key(&ext->tun_key, &msk->tun_key,
				       &ext->tun_flags, &msk->tun_flags, rule);
पूर्ण

अटल व्योम
nfp_flower_compile_ipv4_udp_tun(काष्ठा nfp_flower_ipv4_udp_tun *ext,
				काष्ठा nfp_flower_ipv4_udp_tun *msk,
				काष्ठा flow_rule *rule)
अणु
	स_रखो(ext, 0, माप(काष्ठा nfp_flower_ipv4_udp_tun));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_ipv4_udp_tun));

	nfp_flower_compile_tun_ipv4_addrs(&ext->ipv4, &msk->ipv4, rule);
	nfp_flower_compile_tun_ip_ext(&ext->ip_ext, &msk->ip_ext, rule);
	nfp_flower_compile_tun_udp_key(&ext->tun_id, &msk->tun_id, rule);
पूर्ण

अटल व्योम
nfp_flower_compile_ipv6_udp_tun(काष्ठा nfp_flower_ipv6_udp_tun *ext,
				काष्ठा nfp_flower_ipv6_udp_tun *msk,
				काष्ठा flow_rule *rule)
अणु
	स_रखो(ext, 0, माप(काष्ठा nfp_flower_ipv6_udp_tun));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_ipv6_udp_tun));

	nfp_flower_compile_tun_ipv6_addrs(&ext->ipv6, &msk->ipv6, rule);
	nfp_flower_compile_tun_ip_ext(&ext->ip_ext, &msk->ip_ext, rule);
	nfp_flower_compile_tun_udp_key(&ext->tun_id, &msk->tun_id, rule);
पूर्ण

अटल व्योम
nfp_flower_compile_ipv6_gre_tun(काष्ठा nfp_flower_ipv6_gre_tun *ext,
				काष्ठा nfp_flower_ipv6_gre_tun *msk,
				काष्ठा flow_rule *rule)
अणु
	स_रखो(ext, 0, माप(काष्ठा nfp_flower_ipv6_gre_tun));
	स_रखो(msk, 0, माप(काष्ठा nfp_flower_ipv6_gre_tun));

	/* NVGRE is the only supported GRE tunnel type */
	ext->ethertype = cpu_to_be16(ETH_P_TEB);
	msk->ethertype = cpu_to_be16(~0);

	nfp_flower_compile_tun_ipv6_addrs(&ext->ipv6, &msk->ipv6, rule);
	nfp_flower_compile_tun_ip_ext(&ext->ip_ext, &msk->ip_ext, rule);
	nfp_flower_compile_tun_gre_key(&ext->tun_key, &msk->tun_key,
				       &ext->tun_flags, &msk->tun_flags, rule);
पूर्ण

पूर्णांक nfp_flower_compile_flow_match(काष्ठा nfp_app *app,
				  काष्ठा flow_cls_offload *flow,
				  काष्ठा nfp_fl_key_ls *key_ls,
				  काष्ठा net_device *netdev,
				  काष्ठा nfp_fl_payload *nfp_flow,
				  क्रमागत nfp_flower_tun_type tun_type,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(flow);
	काष्ठा nfp_flower_priv *priv = app->priv;
	bool qinq_sup;
	u32 port_id;
	पूर्णांक ext_len;
	पूर्णांक err;
	u8 *ext;
	u8 *msk;

	port_id = nfp_flower_get_port_id_from_netdev(app, netdev);

	स_रखो(nfp_flow->unmasked_data, 0, key_ls->key_size);
	स_रखो(nfp_flow->mask_data, 0, key_ls->key_size);

	ext = nfp_flow->unmasked_data;
	msk = nfp_flow->mask_data;

	qinq_sup = !!(priv->flower_ext_feats & NFP_FL_FEATS_VLAN_QINQ);

	nfp_flower_compile_meta_tci((काष्ठा nfp_flower_meta_tci *)ext,
				    (काष्ठा nfp_flower_meta_tci *)msk,
				    rule, key_ls->key_layer, qinq_sup);
	ext += माप(काष्ठा nfp_flower_meta_tci);
	msk += माप(काष्ठा nfp_flower_meta_tci);

	/* Populate Extended Metadata अगर Required. */
	अगर (NFP_FLOWER_LAYER_EXT_META & key_ls->key_layer) अणु
		nfp_flower_compile_ext_meta((काष्ठा nfp_flower_ext_meta *)ext,
					    key_ls->key_layer_two);
		nfp_flower_compile_ext_meta((काष्ठा nfp_flower_ext_meta *)msk,
					    key_ls->key_layer_two);
		ext += माप(काष्ठा nfp_flower_ext_meta);
		msk += माप(काष्ठा nfp_flower_ext_meta);
	पूर्ण

	/* Populate Exact Port data. */
	err = nfp_flower_compile_port((काष्ठा nfp_flower_in_port *)ext,
				      port_id, false, tun_type, extack);
	अगर (err)
		वापस err;

	/* Populate Mask Port Data. */
	err = nfp_flower_compile_port((काष्ठा nfp_flower_in_port *)msk,
				      port_id, true, tun_type, extack);
	अगर (err)
		वापस err;

	ext += माप(काष्ठा nfp_flower_in_port);
	msk += माप(काष्ठा nfp_flower_in_port);

	अगर (NFP_FLOWER_LAYER_MAC & key_ls->key_layer) अणु
		err = nfp_flower_compile_mac((काष्ठा nfp_flower_mac_mpls *)ext,
					     (काष्ठा nfp_flower_mac_mpls *)msk,
					     rule, extack);
		अगर (err)
			वापस err;

		ext += माप(काष्ठा nfp_flower_mac_mpls);
		msk += माप(काष्ठा nfp_flower_mac_mpls);
	पूर्ण

	अगर (NFP_FLOWER_LAYER_TP & key_ls->key_layer) अणु
		nfp_flower_compile_tport((काष्ठा nfp_flower_tp_ports *)ext,
					 (काष्ठा nfp_flower_tp_ports *)msk,
					 rule);
		ext += माप(काष्ठा nfp_flower_tp_ports);
		msk += माप(काष्ठा nfp_flower_tp_ports);
	पूर्ण

	अगर (NFP_FLOWER_LAYER_IPV4 & key_ls->key_layer) अणु
		nfp_flower_compile_ipv4((काष्ठा nfp_flower_ipv4 *)ext,
					(काष्ठा nfp_flower_ipv4 *)msk,
					rule);
		ext += माप(काष्ठा nfp_flower_ipv4);
		msk += माप(काष्ठा nfp_flower_ipv4);
	पूर्ण

	अगर (NFP_FLOWER_LAYER_IPV6 & key_ls->key_layer) अणु
		nfp_flower_compile_ipv6((काष्ठा nfp_flower_ipv6 *)ext,
					(काष्ठा nfp_flower_ipv6 *)msk,
					rule);
		ext += माप(काष्ठा nfp_flower_ipv6);
		msk += माप(काष्ठा nfp_flower_ipv6);
	पूर्ण

	अगर (key_ls->key_layer_two & NFP_FLOWER_LAYER2_GRE) अणु
		अगर (key_ls->key_layer_two & NFP_FLOWER_LAYER2_TUN_IPV6) अणु
			काष्ठा nfp_flower_ipv6_gre_tun *gre_match;
			काष्ठा nfp_ipv6_addr_entry *entry;
			काष्ठा in6_addr *dst;

			nfp_flower_compile_ipv6_gre_tun((व्योम *)ext,
							(व्योम *)msk, rule);
			gre_match = (काष्ठा nfp_flower_ipv6_gre_tun *)ext;
			dst = &gre_match->ipv6.dst;
			ext += माप(काष्ठा nfp_flower_ipv6_gre_tun);
			msk += माप(काष्ठा nfp_flower_ipv6_gre_tun);

			entry = nfp_tunnel_add_ipv6_off(app, dst);
			अगर (!entry)
				वापस -EOPNOTSUPP;

			nfp_flow->nfp_tun_ipv6 = entry;
		पूर्ण अन्यथा अणु
			__be32 dst;

			nfp_flower_compile_ipv4_gre_tun((व्योम *)ext,
							(व्योम *)msk, rule);
			dst = ((काष्ठा nfp_flower_ipv4_gre_tun *)ext)->ipv4.dst;
			ext += माप(काष्ठा nfp_flower_ipv4_gre_tun);
			msk += माप(काष्ठा nfp_flower_ipv4_gre_tun);

			/* Store the tunnel destination in the rule data.
			 * This must be present and be an exact match.
			 */
			nfp_flow->nfp_tun_ipv4_addr = dst;
			nfp_tunnel_add_ipv4_off(app, dst);
		पूर्ण
	पूर्ण

	अगर (NFP_FLOWER_LAYER2_QINQ & key_ls->key_layer_two) अणु
		nfp_flower_compile_vlan((काष्ठा nfp_flower_vlan *)ext,
					(काष्ठा nfp_flower_vlan *)msk,
					rule);
		ext += माप(काष्ठा nfp_flower_vlan);
		msk += माप(काष्ठा nfp_flower_vlan);
	पूर्ण

	अगर (key_ls->key_layer & NFP_FLOWER_LAYER_VXLAN ||
	    key_ls->key_layer_two & NFP_FLOWER_LAYER2_GENEVE) अणु
		अगर (key_ls->key_layer_two & NFP_FLOWER_LAYER2_TUN_IPV6) अणु
			काष्ठा nfp_flower_ipv6_udp_tun *udp_match;
			काष्ठा nfp_ipv6_addr_entry *entry;
			काष्ठा in6_addr *dst;

			nfp_flower_compile_ipv6_udp_tun((व्योम *)ext,
							(व्योम *)msk, rule);
			udp_match = (काष्ठा nfp_flower_ipv6_udp_tun *)ext;
			dst = &udp_match->ipv6.dst;
			ext += माप(काष्ठा nfp_flower_ipv6_udp_tun);
			msk += माप(काष्ठा nfp_flower_ipv6_udp_tun);

			entry = nfp_tunnel_add_ipv6_off(app, dst);
			अगर (!entry)
				वापस -EOPNOTSUPP;

			nfp_flow->nfp_tun_ipv6 = entry;
		पूर्ण अन्यथा अणु
			__be32 dst;

			nfp_flower_compile_ipv4_udp_tun((व्योम *)ext,
							(व्योम *)msk, rule);
			dst = ((काष्ठा nfp_flower_ipv4_udp_tun *)ext)->ipv4.dst;
			ext += माप(काष्ठा nfp_flower_ipv4_udp_tun);
			msk += माप(काष्ठा nfp_flower_ipv4_udp_tun);

			/* Store the tunnel destination in the rule data.
			 * This must be present and be an exact match.
			 */
			nfp_flow->nfp_tun_ipv4_addr = dst;
			nfp_tunnel_add_ipv4_off(app, dst);
		पूर्ण

		अगर (key_ls->key_layer_two & NFP_FLOWER_LAYER2_GENEVE_OP) अणु
			err = nfp_flower_compile_geneve_opt(ext, msk, rule);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	/* Check that the flow key करोes not exceed the maximum limit.
	 * All काष्ठाures in the key is multiples of 4 bytes, so use u32.
	 */
	ext_len = (u32 *)ext - (u32 *)nfp_flow->unmasked_data;
	अगर (ext_len > NFP_FLOWER_KEY_MAX_LW) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "unsupported offload: flow key too long");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण
