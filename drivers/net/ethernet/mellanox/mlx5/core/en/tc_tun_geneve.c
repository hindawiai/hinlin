<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2018 Mellanox Technologies. */

#समावेश <net/geneve.h>
#समावेश "lib/geneve.h"
#समावेश "en/tc_tun.h"

#घोषणा MLX5E_GENEVE_VER 0

अटल bool mlx5e_tc_tun_can_offload_geneve(काष्ठा mlx5e_priv *priv)
अणु
	वापस !!(MLX5_CAP_GEN(priv->mdev, flex_parser_protocols) & MLX5_FLEX_PROTO_GENEVE);
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_calc_hlen_geneve(काष्ठा mlx5e_encap_entry *e)
अणु
	वापस माप(काष्ठा udphdr) +
	       माप(काष्ठा genevehdr) +
	       e->tun_info->options_len;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_check_udp_dport_geneve(काष्ठा mlx5e_priv *priv,
					       काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा flow_match_ports enc_ports;

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_PORTS))
		वापस -EOPNOTSUPP;

	flow_rule_match_enc_ports(rule, &enc_ports);

	/* Currently we support only शेष GENEVE
	 * port, so udp dst port must match.
	 */
	अगर (be16_to_cpu(enc_ports.key->dst) != GENEVE_UDP_PORT) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matched UDP dst port is not registered as a GENEVE port");
		netdev_warn(priv->netdev,
			    "UDP port %d is not registered as a GENEVE port\n",
			    be16_to_cpu(enc_ports.key->dst));
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_parse_udp_ports_geneve(काष्ठा mlx5e_priv *priv,
					       काष्ठा mlx5_flow_spec *spec,
					       काष्ठा flow_cls_offload *f,
					       व्योम *headers_c,
					       व्योम *headers_v)
अणु
	पूर्णांक err;

	err = mlx5e_tc_tun_parse_udp_ports(priv, spec, f, headers_c, headers_v);
	अगर (err)
		वापस err;

	वापस mlx5e_tc_tun_check_udp_dport_geneve(priv, f);
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_init_encap_attr_geneve(काष्ठा net_device *tunnel_dev,
					       काष्ठा mlx5e_priv *priv,
					       काष्ठा mlx5e_encap_entry *e,
					       काष्ठा netlink_ext_ack *extack)
अणु
	e->tunnel = &geneve_tunnel;

	/* Reक्रमmat type क्रम GENEVE encap is similar to VXLAN:
	 * in both हालs the HW adds in the same place a
	 * defined encapsulation header that the SW provides.
	 */
	e->reक्रमmat_type = MLX5_REFORMAT_TYPE_L2_TO_VXLAN;
	वापस 0;
पूर्ण

अटल व्योम mlx5e_tunnel_id_to_vni(__be64 tun_id, __u8 *vni)
अणु
#अगर_घोषित __BIG_ENDIAN
	vni[0] = (__क्रमce __u8)(tun_id >> 16);
	vni[1] = (__क्रमce __u8)(tun_id >> 8);
	vni[2] = (__क्रमce __u8)tun_id;
#अन्यथा
	vni[0] = (__क्रमce __u8)((__क्रमce u64)tun_id >> 40);
	vni[1] = (__क्रमce __u8)((__क्रमce u64)tun_id >> 48);
	vni[2] = (__क्रमce __u8)((__क्रमce u64)tun_id >> 56);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक mlx5e_gen_ip_tunnel_header_geneve(अक्षर buf[],
					     __u8 *ip_proto,
					     काष्ठा mlx5e_encap_entry *e)
अणु
	स्थिर काष्ठा ip_tunnel_info *tun_info = e->tun_info;
	काष्ठा udphdr *udp = (काष्ठा udphdr *)(buf);
	काष्ठा genevehdr *geneveh;

	geneveh = (काष्ठा genevehdr *)((अक्षर *)udp + माप(काष्ठा udphdr));

	*ip_proto = IPPROTO_UDP;

	udp->dest = tun_info->key.tp_dst;

	स_रखो(geneveh, 0, माप(*geneveh));
	geneveh->ver = MLX5E_GENEVE_VER;
	geneveh->opt_len = tun_info->options_len / 4;
	geneveh->oam = !!(tun_info->key.tun_flags & TUNNEL_OAM);
	geneveh->critical = !!(tun_info->key.tun_flags & TUNNEL_CRIT_OPT);
	mlx5e_tunnel_id_to_vni(tun_info->key.tun_id, geneveh->vni);
	geneveh->proto_type = htons(ETH_P_TEB);

	अगर (tun_info->key.tun_flags & TUNNEL_GENEVE_OPT) अणु
		अगर (!geneveh->opt_len)
			वापस -EOPNOTSUPP;
		ip_tunnel_info_opts_get(geneveh->options, tun_info);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_parse_geneve_vni(काष्ठा mlx5e_priv *priv,
					 काष्ठा mlx5_flow_spec *spec,
					 काष्ठा flow_cls_offload *f)
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

	अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev, ft_field_support.outer_geneve_vni)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Matching on GENEVE VNI is not supported");
		netdev_warn(priv->netdev, "Matching on GENEVE VNI is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	MLX5_SET(fte_match_set_misc, misc_c, geneve_vni, be32_to_cpu(enc_keyid.mask->keyid));
	MLX5_SET(fte_match_set_misc, misc_v, geneve_vni, be32_to_cpu(enc_keyid.key->keyid));

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_parse_geneve_options(काष्ठा mlx5e_priv *priv,
					     काष्ठा mlx5_flow_spec *spec,
					     काष्ठा flow_cls_offload *f)
अणु
	u8 max_tlv_option_data_len = MLX5_CAP_GEN(priv->mdev, max_geneve_tlv_option_data_len);
	u8 max_tlv_options = MLX5_CAP_GEN(priv->mdev, max_geneve_tlv_options);
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	व्योम *misc_c, *misc_v, *misc_3_c, *misc_3_v;
	काष्ठा geneve_opt *option_key, *option_mask;
	__be32 opt_data_key = 0, opt_data_mask = 0;
	काष्ठा flow_match_enc_opts enc_opts;
	पूर्णांक res = 0;

	misc_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
	misc_v = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);
	misc_3_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters_3);
	misc_3_v = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters_3);

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_OPTS))
		वापस 0;

	flow_rule_match_enc_opts(rule, &enc_opts);

	अगर (स_प्रथम_inv(&enc_opts.mask->data, 0, माप(enc_opts.mask->data)) &&
	    !MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev,
					ft_field_support.geneve_tlv_option_0_data)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matching on GENEVE options is not supported");
		netdev_warn(priv->netdev,
			    "Matching on GENEVE options is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* make sure that we're talking about GENEVE options */

	अगर (enc_opts.key->dst_opt_type != TUNNEL_GENEVE_OPT) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matching on GENEVE options: option type is not GENEVE");
		netdev_warn(priv->netdev,
			    "Matching on GENEVE options: option type is not GENEVE\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (enc_opts.mask->len &&
	    !MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev,
					ft_field_support.outer_geneve_opt_len)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Matching on GENEVE options len is not supported");
		netdev_warn(priv->netdev,
			    "Matching on GENEVE options len is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* max_geneve_tlv_option_data_len comes in multiples of 4 bytes, and it
	 * करोesn't include the TLV option header. 'geneve_opt_len' is a total
	 * len of all the options, including the headers, also multiples of 4
	 * bytes. Len that comes from the dissector is in bytes.
	 */

	अगर ((enc_opts.key->len / 4) > ((max_tlv_option_data_len + 1) * max_tlv_options)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matching on GENEVE options: unsupported options len");
		netdev_warn(priv->netdev,
			    "Matching on GENEVE options: unsupported options len (len=%d)\n",
			    enc_opts.key->len);
		वापस -EOPNOTSUPP;
	पूर्ण

	MLX5_SET(fte_match_set_misc, misc_c, geneve_opt_len, enc_opts.mask->len / 4);
	MLX5_SET(fte_match_set_misc, misc_v, geneve_opt_len, enc_opts.key->len / 4);

	/* we support matching on one option only, so just get it */
	option_key = (काष्ठा geneve_opt *)&enc_opts.key->data[0];
	option_mask = (काष्ठा geneve_opt *)&enc_opts.mask->data[0];

	अगर (option_mask->opt_class == 0 && option_mask->type == 0 &&
	    !स_प्रथम_inv(option_mask->opt_data, 0, option_mask->length * 4))
		वापस 0;

	अगर (option_key->length > max_tlv_option_data_len) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matching on GENEVE options: unsupported option len");
		netdev_warn(priv->netdev,
			    "Matching on GENEVE options: unsupported option len (key=%d, mask=%d)\n",
			    option_key->length, option_mask->length);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* data can't be all 0 - fail to offload such rule */
	अगर (!स_प्रथम_inv(option_key->opt_data, 0, option_key->length * 4)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matching on GENEVE options: can't match on 0 data field");
		netdev_warn(priv->netdev,
			    "Matching on GENEVE options: can't match on 0 data field\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* add new GENEVE TLV options object */
	res = mlx5_geneve_tlv_option_add(priv->mdev->geneve, option_key);
	अगर (res) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Matching on GENEVE options: failed creating TLV opt object");
		netdev_warn(priv->netdev,
			    "Matching on GENEVE options: failed creating TLV opt object (class:type:len = 0x%x:0x%x:%d)\n",
			    be16_to_cpu(option_key->opt_class),
			    option_key->type, option_key->length);
		वापस res;
	पूर्ण

	/* In general, after creating the object, need to query it
	 * in order to check which option data to set in misc3.
	 * But we support only geneve_tlv_option_0_data, so no
	 * poपूर्णांक querying at this stage.
	 */

	स_नकल(&opt_data_key, option_key->opt_data, option_key->length * 4);
	स_नकल(&opt_data_mask, option_mask->opt_data, option_mask->length * 4);
	MLX5_SET(fte_match_set_misc3, misc_3_v,
		 geneve_tlv_option_0_data, be32_to_cpu(opt_data_key));
	MLX5_SET(fte_match_set_misc3, misc_3_c,
		 geneve_tlv_option_0_data, be32_to_cpu(opt_data_mask));

	spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS_3;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_parse_geneve_params(काष्ठा mlx5e_priv *priv,
					    काष्ठा mlx5_flow_spec *spec,
					    काष्ठा flow_cls_offload *f)
अणु
	व्योम *misc_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
	व्योम *misc_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,  misc_parameters);
	काष्ठा netlink_ext_ack *extack = f->common.extack;

	/* match on OAM - packets with OAM bit on should NOT be offloaded */

	अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev, ft_field_support.outer_geneve_oam)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Matching on GENEVE OAM is not supported");
		netdev_warn(priv->netdev, "Matching on GENEVE OAM is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	MLX5_SET_TO_ONES(fte_match_set_misc, misc_c, geneve_oam);
	MLX5_SET(fte_match_set_misc, misc_v, geneve_oam, 0);

	/* Match on GENEVE protocol. We support only Transparent Eth Bridge. */

	अगर (MLX5_CAP_ESW_FLOWTABLE_FDB(priv->mdev,
				       ft_field_support.outer_geneve_protocol_type)) अणु
		MLX5_SET_TO_ONES(fte_match_set_misc, misc_c, geneve_protocol_type);
		MLX5_SET(fte_match_set_misc, misc_v, geneve_protocol_type, ETH_P_TEB);
	पूर्ण

	spec->match_criteria_enable |= MLX5_MATCH_MISC_PARAMETERS;

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_parse_geneve(काष्ठा mlx5e_priv *priv,
				     काष्ठा mlx5_flow_spec *spec,
				     काष्ठा flow_cls_offload *f,
				     व्योम *headers_c,
				     व्योम *headers_v)
अणु
	पूर्णांक err;

	err = mlx5e_tc_tun_parse_geneve_params(priv, spec, f);
	अगर (err)
		वापस err;

	err = mlx5e_tc_tun_parse_geneve_vni(priv, spec, f);
	अगर (err)
		वापस err;

	वापस mlx5e_tc_tun_parse_geneve_options(priv, spec, f);
पूर्ण

अटल bool mlx5e_tc_tun_encap_info_equal_geneve(काष्ठा mlx5e_encap_key *a,
						 काष्ठा mlx5e_encap_key *b)
अणु
	काष्ठा ip_tunnel_info *a_info;
	काष्ठा ip_tunnel_info *b_info;
	bool a_has_opts, b_has_opts;

	अगर (!mlx5e_tc_tun_encap_info_equal_generic(a, b))
		वापस false;

	a_has_opts = !!(a->ip_tun_key->tun_flags & TUNNEL_GENEVE_OPT);
	b_has_opts = !!(b->ip_tun_key->tun_flags & TUNNEL_GENEVE_OPT);

	/* keys are equal when both करोn't have any options attached */
	अगर (!a_has_opts && !b_has_opts)
		वापस true;

	अगर (a_has_opts != b_has_opts)
		वापस false;

	/* geneve options stored in memory next to ip_tunnel_info काष्ठा */
	a_info = container_of(a->ip_tun_key, काष्ठा ip_tunnel_info, key);
	b_info = container_of(b->ip_tun_key, काष्ठा ip_tunnel_info, key);

	वापस a_info->options_len == b_info->options_len &&
		स_भेद(a_info + 1, b_info + 1, a_info->options_len) == 0;
पूर्ण

काष्ठा mlx5e_tc_tunnel geneve_tunnel = अणु
	.tunnel_type          = MLX5E_TC_TUNNEL_TYPE_GENEVE,
	.match_level          = MLX5_MATCH_L4,
	.can_offload          = mlx5e_tc_tun_can_offload_geneve,
	.calc_hlen            = mlx5e_tc_tun_calc_hlen_geneve,
	.init_encap_attr      = mlx5e_tc_tun_init_encap_attr_geneve,
	.generate_ip_tun_hdr  = mlx5e_gen_ip_tunnel_header_geneve,
	.parse_udp_ports      = mlx5e_tc_tun_parse_udp_ports_geneve,
	.parse_tunnel         = mlx5e_tc_tun_parse_geneve,
	.encap_info_equal     = mlx5e_tc_tun_encap_info_equal_geneve,
पूर्ण;
