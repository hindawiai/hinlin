<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2018 Mellanox Technologies. */

#समावेश <net/gre.h>
#समावेश "en/tc_tun.h"

अटल bool mlx5e_tc_tun_can_offload_gretap(काष्ठा mlx5e_priv *priv)
अणु
	वापस !!MLX5_CAP_ESW(priv->mdev, nvgre_encap_decap);
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_calc_hlen_gretap(काष्ठा mlx5e_encap_entry *e)
अणु
	वापस gre_calc_hlen(e->tun_info->key.tun_flags);
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_init_encap_attr_gretap(काष्ठा net_device *tunnel_dev,
					       काष्ठा mlx5e_priv *priv,
					       काष्ठा mlx5e_encap_entry *e,
					       काष्ठा netlink_ext_ack *extack)
अणु
	e->tunnel = &gre_tunnel;
	e->reक्रमmat_type = MLX5_REFORMAT_TYPE_L2_TO_NVGRE;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_gen_ip_tunnel_header_gretap(अक्षर buf[],
					     __u8 *ip_proto,
					     काष्ठा mlx5e_encap_entry *e)
अणु
	स्थिर काष्ठा ip_tunnel_key *tun_key  = &e->tun_info->key;
	काष्ठा gre_base_hdr *greh = (काष्ठा gre_base_hdr *)(buf);
	__be32 tun_id = tunnel_id_to_key32(tun_key->tun_id);
	पूर्णांक hdr_len;

	*ip_proto = IPPROTO_GRE;

	/* the HW करोes not calculate GRE csum or sequences */
	अगर (tun_key->tun_flags & (TUNNEL_CSUM | TUNNEL_SEQ))
		वापस -EOPNOTSUPP;

	greh->protocol = htons(ETH_P_TEB);

	/* GRE key */
	hdr_len	= mlx5e_tc_tun_calc_hlen_gretap(e);
	greh->flags = gre_tnl_flags_to_gre_flags(tun_key->tun_flags);
	अगर (tun_key->tun_flags & TUNNEL_KEY) अणु
		__be32 *ptr = (__be32 *)(((u8 *)greh) + hdr_len - 4);
		*ptr = tun_id;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_parse_gretap(काष्ठा mlx5e_priv *priv,
				     काष्ठा mlx5_flow_spec *spec,
				     काष्ठा flow_cls_offload *f,
				     व्योम *headers_c,
				     व्योम *headers_v)
अणु
	व्योम *misc_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
	व्योम *misc_v = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);

	MLX5_SET_TO_ONES(fte_match_set_lyr_2_4, headers_c, ip_protocol);
	MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_protocol, IPPROTO_GRE);

	/* gre protocol */
	MLX5_SET_TO_ONES(fte_match_set_misc, misc_c, gre_protocol);
	MLX5_SET(fte_match_set_misc, misc_v, gre_protocol, ETH_P_TEB);

	/* gre key */
	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) अणु
		काष्ठा flow_match_enc_keyid enc_keyid;

		flow_rule_match_enc_keyid(rule, &enc_keyid);
		MLX5_SET(fte_match_set_misc, misc_c,
			 gre_key.key, be32_to_cpu(enc_keyid.mask->keyid));
		MLX5_SET(fte_match_set_misc, misc_v,
			 gre_key.key, be32_to_cpu(enc_keyid.key->keyid));
	पूर्ण

	spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS;

	वापस 0;
पूर्ण

काष्ठा mlx5e_tc_tunnel gre_tunnel = अणु
	.tunnel_type          = MLX5E_TC_TUNNEL_TYPE_GRETAP,
	.match_level          = MLX5_MATCH_L3,
	.can_offload          = mlx5e_tc_tun_can_offload_gretap,
	.calc_hlen            = mlx5e_tc_tun_calc_hlen_gretap,
	.init_encap_attr      = mlx5e_tc_tun_init_encap_attr_gretap,
	.generate_ip_tun_hdr  = mlx5e_gen_ip_tunnel_header_gretap,
	.parse_udp_ports      = शून्य,
	.parse_tunnel         = mlx5e_tc_tun_parse_gretap,
	.encap_info_equal     = mlx5e_tc_tun_encap_info_equal_generic,
पूर्ण;
