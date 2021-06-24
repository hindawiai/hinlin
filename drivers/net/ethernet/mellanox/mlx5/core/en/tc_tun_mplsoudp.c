<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2018 Mellanox Technologies. */

#समावेश <net/bareudp.h>
#समावेश <net/mpls.h>
#समावेश "en/tc_tun.h"

अटल bool can_offload(काष्ठा mlx5e_priv *priv)
अणु
	वापस MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev, reक्रमmat_l3_tunnel_to_l2);
पूर्ण

अटल पूर्णांक calc_hlen(काष्ठा mlx5e_encap_entry *e)
अणु
	वापस माप(काष्ठा udphdr) + MPLS_HLEN;
पूर्ण

अटल पूर्णांक init_encap_attr(काष्ठा net_device *tunnel_dev,
			   काष्ठा mlx5e_priv *priv,
			   काष्ठा mlx5e_encap_entry *e,
			   काष्ठा netlink_ext_ack *extack)
अणु
	e->tunnel = &mplsoudp_tunnel;
	e->reक्रमmat_type = MLX5_REFORMAT_TYPE_L2_TO_L3_TUNNEL;
	वापस 0;
पूर्ण

अटल पूर्णांक generate_ip_tun_hdr(अक्षर buf[],
			       __u8 *ip_proto,
			       काष्ठा mlx5e_encap_entry *r)
अणु
	स्थिर काष्ठा ip_tunnel_key *tun_key = &r->tun_info->key;
	काष्ठा udphdr *udp = (काष्ठा udphdr *)(buf);
	काष्ठा mpls_shim_hdr *mpls;
	u32 tun_id;

	tun_id = be32_to_cpu(tunnel_id_to_key32(tun_key->tun_id));
	mpls = (काष्ठा mpls_shim_hdr *)(udp + 1);
	*ip_proto = IPPROTO_UDP;

	udp->dest = tun_key->tp_dst;
	*mpls = mpls_entry_encode(tun_id, tun_key->ttl, tun_key->tos, true);

	वापस 0;
पूर्ण

अटल पूर्णांक parse_udp_ports(काष्ठा mlx5e_priv *priv,
			   काष्ठा mlx5_flow_spec *spec,
			   काष्ठा flow_cls_offload *f,
			   व्योम *headers_c,
			   व्योम *headers_v)
अणु
	वापस mlx5e_tc_tun_parse_udp_ports(priv, spec, f, headers_c, headers_v);
पूर्ण

अटल पूर्णांक parse_tunnel(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5_flow_spec *spec,
			काष्ठा flow_cls_offload *f,
			व्योम *headers_c,
			व्योम *headers_v)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_match_enc_keyid enc_keyid;
	काष्ठा flow_match_mpls match;
	व्योम *misc2_c;
	व्योम *misc2_v;

	misc2_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
			       misc_parameters_2);
	misc2_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
			       misc_parameters_2);

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_MPLS))
		वापस 0;

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID))
		वापस 0;

	flow_rule_match_enc_keyid(rule, &enc_keyid);

	अगर (!enc_keyid.mask->keyid)
		वापस 0;

	अगर (!MLX5_CAP_ETH(priv->mdev, tunnel_stateless_mpls_over_udp) &&
	    !(MLX5_CAP_GEN(priv->mdev, flex_parser_protocols) & MLX5_FLEX_PROTO_CW_MPLS_UDP))
		वापस -EOPNOTSUPP;

	flow_rule_match_mpls(rule, &match);

	/* Only support matching the first LSE */
	अगर (match.mask->used_lses != 1)
		वापस -EOPNOTSUPP;

	MLX5_SET(fte_match_set_misc2, misc2_c,
		 outer_first_mpls_over_udp.mpls_label,
		 match.mask->ls[0].mpls_label);
	MLX5_SET(fte_match_set_misc2, misc2_v,
		 outer_first_mpls_over_udp.mpls_label,
		 match.key->ls[0].mpls_label);

	MLX5_SET(fte_match_set_misc2, misc2_c,
		 outer_first_mpls_over_udp.mpls_exp,
		 match.mask->ls[0].mpls_tc);
	MLX5_SET(fte_match_set_misc2, misc2_v,
		 outer_first_mpls_over_udp.mpls_exp, match.key->ls[0].mpls_tc);

	MLX5_SET(fte_match_set_misc2, misc2_c,
		 outer_first_mpls_over_udp.mpls_s_bos,
		 match.mask->ls[0].mpls_bos);
	MLX5_SET(fte_match_set_misc2, misc2_v,
		 outer_first_mpls_over_udp.mpls_s_bos,
		 match.key->ls[0].mpls_bos);

	MLX5_SET(fte_match_set_misc2, misc2_c,
		 outer_first_mpls_over_udp.mpls_ttl,
		 match.mask->ls[0].mpls_ttl);
	MLX5_SET(fte_match_set_misc2, misc2_v,
		 outer_first_mpls_over_udp.mpls_ttl,
		 match.key->ls[0].mpls_ttl);
	spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS_2;

	वापस 0;
पूर्ण

काष्ठा mlx5e_tc_tunnel mplsoudp_tunnel = अणु
	.tunnel_type          = MLX5E_TC_TUNNEL_TYPE_MPLSOUDP,
	.match_level          = MLX5_MATCH_L4,
	.can_offload          = can_offload,
	.calc_hlen            = calc_hlen,
	.init_encap_attr      = init_encap_attr,
	.generate_ip_tun_hdr  = generate_ip_tun_hdr,
	.parse_udp_ports      = parse_udp_ports,
	.parse_tunnel         = parse_tunnel,
	.encap_info_equal     = mlx5e_tc_tun_encap_info_equal_generic,
पूर्ण;
