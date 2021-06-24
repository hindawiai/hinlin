<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2018 Mellanox Technologies. */

#समावेश <net/vxlan.h>
#समावेश "lib/vxlan.h"
#समावेश "en/tc_tun.h"

अटल bool mlx5e_tc_tun_can_offload_vxlan(काष्ठा mlx5e_priv *priv)
अणु
	वापस !!MLX5_CAP_ESW(priv->mdev, vxlan_encap_decap);
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_calc_hlen_vxlan(काष्ठा mlx5e_encap_entry *e)
अणु
	वापस VXLAN_HLEN;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_check_udp_dport_vxlan(काष्ठा mlx5e_priv *priv,
					      काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा flow_match_ports enc_ports;

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_PORTS))
		वापस -EOPNOTSUPP;

	flow_rule_match_enc_ports(rule, &enc_ports);

	/* check the UDP destination port validity */

	अगर (!mlx5_vxlan_lookup_port(priv->mdev->vxlan,
				    be16_to_cpu(enc_ports.key->dst))) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matched UDP dst port is not registered as a VXLAN port");
		netdev_warn(priv->netdev,
			    "UDP port %d is not registered as a VXLAN port\n",
			    be16_to_cpu(enc_ports.key->dst));
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_parse_udp_ports_vxlan(काष्ठा mlx5e_priv *priv,
					      काष्ठा mlx5_flow_spec *spec,
					      काष्ठा flow_cls_offload *f,
					      व्योम *headers_c,
					      व्योम *headers_v)
अणु
	पूर्णांक err = 0;

	err = mlx5e_tc_tun_parse_udp_ports(priv, spec, f, headers_c, headers_v);
	अगर (err)
		वापस err;

	वापस mlx5e_tc_tun_check_udp_dport_vxlan(priv, f);
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_init_encap_attr_vxlan(काष्ठा net_device *tunnel_dev,
					      काष्ठा mlx5e_priv *priv,
					      काष्ठा mlx5e_encap_entry *e,
					      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक dst_port = be16_to_cpu(e->tun_info->key.tp_dst);

	e->tunnel = &vxlan_tunnel;

	अगर (!mlx5_vxlan_lookup_port(priv->mdev->vxlan, dst_port)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "vxlan udp dport was not registered with the HW");
		netdev_warn(priv->netdev,
			    "%d isn't an offloaded vxlan udp dport\n",
			    dst_port);
		वापस -EOPNOTSUPP;
	पूर्ण

	e->reक्रमmat_type = MLX5_REFORMAT_TYPE_L2_TO_VXLAN;
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_gen_ip_tunnel_header_vxlan(अक्षर buf[],
					    __u8 *ip_proto,
					    काष्ठा mlx5e_encap_entry *e)
अणु
	स्थिर काष्ठा ip_tunnel_key *tun_key = &e->tun_info->key;
	__be32 tun_id = tunnel_id_to_key32(tun_key->tun_id);
	काष्ठा udphdr *udp = (काष्ठा udphdr *)(buf);
	काष्ठा vxlanhdr *vxh;

	vxh = (काष्ठा vxlanhdr *)((अक्षर *)udp + माप(काष्ठा udphdr));
	*ip_proto = IPPROTO_UDP;

	udp->dest = tun_key->tp_dst;
	vxh->vx_flags = VXLAN_HF_VNI;
	vxh->vx_vni = vxlan_vni_field(tun_id);

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_parse_vxlan(काष्ठा mlx5e_priv *priv,
				    काष्ठा mlx5_flow_spec *spec,
				    काष्ठा flow_cls_offload *f,
				    व्योम *headers_c,
				    व्योम *headers_v)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा flow_match_enc_keyid enc_keyid;
	व्योम *misc_c, *misc_v;

	misc_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
	misc_v = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID))
		वापस 0;

	flow_rule_match_enc_keyid(rule, &enc_keyid);

	अगर (!enc_keyid.mask->keyid)
		वापस 0;

	/* match on VNI is required */

	अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev,
					ft_field_support.outer_vxlan_vni)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matching on VXLAN VNI is not supported");
		netdev_warn(priv->netdev,
			    "Matching on VXLAN VNI is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	MLX5_SET(fte_match_set_misc, misc_c, vxlan_vni,
		 be32_to_cpu(enc_keyid.mask->keyid));
	MLX5_SET(fte_match_set_misc, misc_v, vxlan_vni,
		 be32_to_cpu(enc_keyid.key->keyid));

	spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS;

	वापस 0;
पूर्ण

काष्ठा mlx5e_tc_tunnel vxlan_tunnel = अणु
	.tunnel_type          = MLX5E_TC_TUNNEL_TYPE_VXLAN,
	.match_level          = MLX5_MATCH_L4,
	.can_offload          = mlx5e_tc_tun_can_offload_vxlan,
	.calc_hlen            = mlx5e_tc_tun_calc_hlen_vxlan,
	.init_encap_attr      = mlx5e_tc_tun_init_encap_attr_vxlan,
	.generate_ip_tun_hdr  = mlx5e_gen_ip_tunnel_header_vxlan,
	.parse_udp_ports      = mlx5e_tc_tun_parse_udp_ports_vxlan,
	.parse_tunnel         = mlx5e_tc_tun_parse_vxlan,
	.encap_info_equal     = mlx5e_tc_tun_encap_info_equal_generic,
पूर्ण;
