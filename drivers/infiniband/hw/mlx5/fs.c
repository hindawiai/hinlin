<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
 */

#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/uverbs_types.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश <rdma/uverbs_std_types.h>
#समावेश <rdma/mlx5_user_ioctl_cmds.h>
#समावेश <rdma/mlx5_user_ioctl_verbs.h>
#समावेश <rdma/ib_uस्मृति.स>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/mlx5/fs_helpers.h>
#समावेश <linux/mlx5/accel.h>
#समावेश <linux/mlx5/eचयन.h>
#समावेश "mlx5_ib.h"
#समावेश "counters.h"
#समावेश "devx.h"
#समावेश "fs.h"

#घोषणा UVERBS_MODULE_NAME mlx5_ib
#समावेश <rdma/uverbs_named_ioctl.h>

क्रमागत अणु
	MATCH_CRITERIA_ENABLE_OUTER_BIT,
	MATCH_CRITERIA_ENABLE_MISC_BIT,
	MATCH_CRITERIA_ENABLE_INNER_BIT,
	MATCH_CRITERIA_ENABLE_MISC2_BIT
पूर्ण;

#घोषणा HEADER_IS_ZERO(match_criteria, headers)			           \
	!(स_प्रथम_inv(MLX5_ADDR_OF(fte_match_param, match_criteria, headers), \
		    0, MLX5_FLD_SZ_BYTES(fte_match_param, headers)))       \

अटल u8 get_match_criteria_enable(u32 *match_criteria)
अणु
	u8 match_criteria_enable;

	match_criteria_enable =
		(!HEADER_IS_ZERO(match_criteria, outer_headers)) <<
		MATCH_CRITERIA_ENABLE_OUTER_BIT;
	match_criteria_enable |=
		(!HEADER_IS_ZERO(match_criteria, misc_parameters)) <<
		MATCH_CRITERIA_ENABLE_MISC_BIT;
	match_criteria_enable |=
		(!HEADER_IS_ZERO(match_criteria, inner_headers)) <<
		MATCH_CRITERIA_ENABLE_INNER_BIT;
	match_criteria_enable |=
		(!HEADER_IS_ZERO(match_criteria, misc_parameters_2)) <<
		MATCH_CRITERIA_ENABLE_MISC2_BIT;

	वापस match_criteria_enable;
पूर्ण

अटल पूर्णांक set_proto(व्योम *outer_c, व्योम *outer_v, u8 mask, u8 val)
अणु
	u8 entry_mask;
	u8 entry_val;
	पूर्णांक err = 0;

	अगर (!mask)
		जाओ out;

	entry_mask = MLX5_GET(fte_match_set_lyr_2_4, outer_c,
			      ip_protocol);
	entry_val = MLX5_GET(fte_match_set_lyr_2_4, outer_v,
			     ip_protocol);
	अगर (!entry_mask) अणु
		MLX5_SET(fte_match_set_lyr_2_4, outer_c, ip_protocol, mask);
		MLX5_SET(fte_match_set_lyr_2_4, outer_v, ip_protocol, val);
		जाओ out;
	पूर्ण
	/* Don't override existing ip protocol */
	अगर (mask != entry_mask || val != entry_val)
		err = -EINVAL;
out:
	वापस err;
पूर्ण

अटल व्योम set_flow_label(व्योम *misc_c, व्योम *misc_v, u32 mask, u32 val,
			   bool inner)
अणु
	अगर (inner) अणु
		MLX5_SET(fte_match_set_misc,
			 misc_c, inner_ipv6_flow_label, mask);
		MLX5_SET(fte_match_set_misc,
			 misc_v, inner_ipv6_flow_label, val);
	पूर्ण अन्यथा अणु
		MLX5_SET(fte_match_set_misc,
			 misc_c, outer_ipv6_flow_label, mask);
		MLX5_SET(fte_match_set_misc,
			 misc_v, outer_ipv6_flow_label, val);
	पूर्ण
पूर्ण

अटल व्योम set_tos(व्योम *outer_c, व्योम *outer_v, u8 mask, u8 val)
अणु
	MLX5_SET(fte_match_set_lyr_2_4, outer_c, ip_ecn, mask);
	MLX5_SET(fte_match_set_lyr_2_4, outer_v, ip_ecn, val);
	MLX5_SET(fte_match_set_lyr_2_4, outer_c, ip_dscp, mask >> 2);
	MLX5_SET(fte_match_set_lyr_2_4, outer_v, ip_dscp, val >> 2);
पूर्ण

अटल पूर्णांक check_mpls_supp_fields(u32 field_support, स्थिर __be32 *set_mask)
अणु
	अगर (MLX5_GET(fte_match_mpls, set_mask, mpls_label) &&
	    !(field_support & MLX5_FIELD_SUPPORT_MPLS_LABEL))
		वापस -EOPNOTSUPP;

	अगर (MLX5_GET(fte_match_mpls, set_mask, mpls_exp) &&
	    !(field_support & MLX5_FIELD_SUPPORT_MPLS_EXP))
		वापस -EOPNOTSUPP;

	अगर (MLX5_GET(fte_match_mpls, set_mask, mpls_s_bos) &&
	    !(field_support & MLX5_FIELD_SUPPORT_MPLS_S_BOS))
		वापस -EOPNOTSUPP;

	अगर (MLX5_GET(fte_match_mpls, set_mask, mpls_ttl) &&
	    !(field_support & MLX5_FIELD_SUPPORT_MPLS_TTL))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

#घोषणा LAST_ETH_FIELD vlan_tag
#घोषणा LAST_IB_FIELD sl
#घोषणा LAST_IPV4_FIELD tos
#घोषणा LAST_IPV6_FIELD traffic_class
#घोषणा LAST_TCP_UDP_FIELD src_port
#घोषणा LAST_TUNNEL_FIELD tunnel_id
#घोषणा LAST_FLOW_TAG_FIELD tag_id
#घोषणा LAST_DROP_FIELD size
#घोषणा LAST_COUNTERS_FIELD counters

/* Field is the last supported field */
#घोषणा FIELDS_NOT_SUPPORTED(filter, field)                                    \
	स_प्रथम_inv((व्योम *)&filter.field + माप(filter.field), 0,            \
		   माप(filter) - दुरत्वend(typeof(filter), field))

पूर्णांक parse_flow_flow_action(काष्ठा mlx5_ib_flow_action *maction,
			   bool is_egress,
			   काष्ठा mlx5_flow_act *action)
अणु

	चयन (maction->ib_action.type) अणु
	हाल IB_FLOW_ACTION_ESP:
		अगर (action->action & (MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
				      MLX5_FLOW_CONTEXT_ACTION_DECRYPT))
			वापस -EINVAL;
		/* Currently only AES_GCM keymat is supported by the driver */
		action->esp_id = (uपूर्णांकptr_t)maction->esp_aes_gcm.ctx;
		action->action |= is_egress ?
			MLX5_FLOW_CONTEXT_ACTION_ENCRYPT :
			MLX5_FLOW_CONTEXT_ACTION_DECRYPT;
		वापस 0;
	हाल IB_FLOW_ACTION_UNSPECIFIED:
		अगर (maction->flow_action_raw.sub_type ==
		    MLX5_IB_FLOW_ACTION_MODIFY_HEADER) अणु
			अगर (action->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
				वापस -EINVAL;
			action->action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
			action->modअगरy_hdr =
				maction->flow_action_raw.modअगरy_hdr;
			वापस 0;
		पूर्ण
		अगर (maction->flow_action_raw.sub_type ==
		    MLX5_IB_FLOW_ACTION_DECAP) अणु
			अगर (action->action & MLX5_FLOW_CONTEXT_ACTION_DECAP)
				वापस -EINVAL;
			action->action |= MLX5_FLOW_CONTEXT_ACTION_DECAP;
			वापस 0;
		पूर्ण
		अगर (maction->flow_action_raw.sub_type ==
		    MLX5_IB_FLOW_ACTION_PACKET_REFORMAT) अणु
			अगर (action->action &
			    MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT)
				वापस -EINVAL;
			action->action |=
				MLX5_FLOW_CONTEXT_ACTION_PACKET_REFORMAT;
			action->pkt_reक्रमmat =
				maction->flow_action_raw.pkt_reक्रमmat;
			वापस 0;
		पूर्ण
		fallthrough;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक parse_flow_attr(काष्ठा mlx5_core_dev *mdev,
			   काष्ठा mlx5_flow_spec *spec,
			   स्थिर जोड़ ib_flow_spec *ib_spec,
			   स्थिर काष्ठा ib_flow_attr *flow_attr,
			   काष्ठा mlx5_flow_act *action, u32 prev_type)
अणु
	काष्ठा mlx5_flow_context *flow_context = &spec->flow_context;
	u32 *match_c = spec->match_criteria;
	u32 *match_v = spec->match_value;
	व्योम *misc_params_c = MLX5_ADDR_OF(fte_match_param, match_c,
					   misc_parameters);
	व्योम *misc_params_v = MLX5_ADDR_OF(fte_match_param, match_v,
					   misc_parameters);
	व्योम *misc_params2_c = MLX5_ADDR_OF(fte_match_param, match_c,
					    misc_parameters_2);
	व्योम *misc_params2_v = MLX5_ADDR_OF(fte_match_param, match_v,
					    misc_parameters_2);
	व्योम *headers_c;
	व्योम *headers_v;
	पूर्णांक match_ipv;
	पूर्णांक ret;

	अगर (ib_spec->type & IB_FLOW_SPEC_INNER) अणु
		headers_c = MLX5_ADDR_OF(fte_match_param, match_c,
					 inner_headers);
		headers_v = MLX5_ADDR_OF(fte_match_param, match_v,
					 inner_headers);
		match_ipv = MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
					ft_field_support.inner_ip_version);
	पूर्ण अन्यथा अणु
		headers_c = MLX5_ADDR_OF(fte_match_param, match_c,
					 outer_headers);
		headers_v = MLX5_ADDR_OF(fte_match_param, match_v,
					 outer_headers);
		match_ipv = MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
					ft_field_support.outer_ip_version);
	पूर्ण

	चयन (ib_spec->type & ~IB_FLOW_SPEC_INNER) अणु
	हाल IB_FLOW_SPEC_ETH:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->eth.mask, LAST_ETH_FIELD))
			वापस -EOPNOTSUPP;

		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
					     dmac_47_16),
				ib_spec->eth.mask.dst_mac);
		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
					     dmac_47_16),
				ib_spec->eth.val.dst_mac);

		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
					     smac_47_16),
				ib_spec->eth.mask.src_mac);
		ether_addr_copy(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
					     smac_47_16),
				ib_spec->eth.val.src_mac);

		अगर (ib_spec->eth.mask.vlan_tag) अणु
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 cvlan_tag, 1);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 cvlan_tag, 1);

			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 first_vid, ntohs(ib_spec->eth.mask.vlan_tag));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 first_vid, ntohs(ib_spec->eth.val.vlan_tag));

			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 first_cfi,
				 ntohs(ib_spec->eth.mask.vlan_tag) >> 12);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 first_cfi,
				 ntohs(ib_spec->eth.val.vlan_tag) >> 12);

			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 first_prio,
				 ntohs(ib_spec->eth.mask.vlan_tag) >> 13);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 first_prio,
				 ntohs(ib_spec->eth.val.vlan_tag) >> 13);
		पूर्ण
		MLX5_SET(fte_match_set_lyr_2_4, headers_c,
			 ethertype, ntohs(ib_spec->eth.mask.ether_type));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v,
			 ethertype, ntohs(ib_spec->eth.val.ether_type));
		अवरोध;
	हाल IB_FLOW_SPEC_IPV4:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->ipv4.mask, LAST_IPV4_FIELD))
			वापस -EOPNOTSUPP;

		अगर (match_ipv) अणु
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 ip_version, 0xf);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 ip_version, MLX5_FS_IPV4_VERSION);
		पूर्ण अन्यथा अणु
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 ethertype, 0xffff);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 ethertype, ETH_P_IP);
		पूर्ण

		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &ib_spec->ipv4.mask.src_ip,
		       माप(ib_spec->ipv4.mask.src_ip));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &ib_spec->ipv4.val.src_ip,
		       माप(ib_spec->ipv4.val.src_ip));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &ib_spec->ipv4.mask.dst_ip,
		       माप(ib_spec->ipv4.mask.dst_ip));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &ib_spec->ipv4.val.dst_ip,
		       माप(ib_spec->ipv4.val.dst_ip));

		set_tos(headers_c, headers_v,
			ib_spec->ipv4.mask.tos, ib_spec->ipv4.val.tos);

		अगर (set_proto(headers_c, headers_v,
			      ib_spec->ipv4.mask.proto,
			      ib_spec->ipv4.val.proto))
			वापस -EINVAL;
		अवरोध;
	हाल IB_FLOW_SPEC_IPV6:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->ipv6.mask, LAST_IPV6_FIELD))
			वापस -EOPNOTSUPP;

		अगर (match_ipv) अणु
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 ip_version, 0xf);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 ip_version, MLX5_FS_IPV6_VERSION);
		पूर्ण अन्यथा अणु
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 ethertype, 0xffff);
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 ethertype, ETH_P_IPV6);
		पूर्ण

		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &ib_spec->ipv6.mask.src_ip,
		       माप(ib_spec->ipv6.mask.src_ip));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &ib_spec->ipv6.val.src_ip,
		       माप(ib_spec->ipv6.val.src_ip));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &ib_spec->ipv6.mask.dst_ip,
		       माप(ib_spec->ipv6.mask.dst_ip));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &ib_spec->ipv6.val.dst_ip,
		       माप(ib_spec->ipv6.val.dst_ip));

		set_tos(headers_c, headers_v,
			ib_spec->ipv6.mask.traffic_class,
			ib_spec->ipv6.val.traffic_class);

		अगर (set_proto(headers_c, headers_v,
			      ib_spec->ipv6.mask.next_hdr,
			      ib_spec->ipv6.val.next_hdr))
			वापस -EINVAL;

		set_flow_label(misc_params_c, misc_params_v,
			       ntohl(ib_spec->ipv6.mask.flow_label),
			       ntohl(ib_spec->ipv6.val.flow_label),
			       ib_spec->type & IB_FLOW_SPEC_INNER);
		अवरोध;
	हाल IB_FLOW_SPEC_ESP:
		अगर (ib_spec->esp.mask.seq)
			वापस -EOPNOTSUPP;

		MLX5_SET(fte_match_set_misc, misc_params_c, outer_esp_spi,
			 ntohl(ib_spec->esp.mask.spi));
		MLX5_SET(fte_match_set_misc, misc_params_v, outer_esp_spi,
			 ntohl(ib_spec->esp.val.spi));
		अवरोध;
	हाल IB_FLOW_SPEC_TCP:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->tcp_udp.mask,
					 LAST_TCP_UDP_FIELD))
			वापस -EOPNOTSUPP;

		अगर (set_proto(headers_c, headers_v, 0xff, IPPROTO_TCP))
			वापस -EINVAL;

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, tcp_sport,
			 ntohs(ib_spec->tcp_udp.mask.src_port));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, tcp_sport,
			 ntohs(ib_spec->tcp_udp.val.src_port));

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, tcp_dport,
			 ntohs(ib_spec->tcp_udp.mask.dst_port));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, tcp_dport,
			 ntohs(ib_spec->tcp_udp.val.dst_port));
		अवरोध;
	हाल IB_FLOW_SPEC_UDP:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->tcp_udp.mask,
					 LAST_TCP_UDP_FIELD))
			वापस -EOPNOTSUPP;

		अगर (set_proto(headers_c, headers_v, 0xff, IPPROTO_UDP))
			वापस -EINVAL;

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, udp_sport,
			 ntohs(ib_spec->tcp_udp.mask.src_port));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, udp_sport,
			 ntohs(ib_spec->tcp_udp.val.src_port));

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, udp_dport,
			 ntohs(ib_spec->tcp_udp.mask.dst_port));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, udp_dport,
			 ntohs(ib_spec->tcp_udp.val.dst_port));
		अवरोध;
	हाल IB_FLOW_SPEC_GRE:
		अगर (ib_spec->gre.mask.c_ks_res0_ver)
			वापस -EOPNOTSUPP;

		अगर (set_proto(headers_c, headers_v, 0xff, IPPROTO_GRE))
			वापस -EINVAL;

		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ip_protocol,
			 0xff);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_protocol,
			 IPPROTO_GRE);

		MLX5_SET(fte_match_set_misc, misc_params_c, gre_protocol,
			 ntohs(ib_spec->gre.mask.protocol));
		MLX5_SET(fte_match_set_misc, misc_params_v, gre_protocol,
			 ntohs(ib_spec->gre.val.protocol));

		स_नकल(MLX5_ADDR_OF(fte_match_set_misc, misc_params_c,
				    gre_key.nvgre.hi),
		       &ib_spec->gre.mask.key,
		       माप(ib_spec->gre.mask.key));
		स_नकल(MLX5_ADDR_OF(fte_match_set_misc, misc_params_v,
				    gre_key.nvgre.hi),
		       &ib_spec->gre.val.key,
		       माप(ib_spec->gre.val.key));
		अवरोध;
	हाल IB_FLOW_SPEC_MPLS:
		चयन (prev_type) अणु
		हाल IB_FLOW_SPEC_UDP:
			अगर (check_mpls_supp_fields(MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
						   ft_field_support.outer_first_mpls_over_udp),
						   &ib_spec->mpls.mask.tag))
				वापस -EOPNOTSUPP;

			स_नकल(MLX5_ADDR_OF(fte_match_set_misc2, misc_params2_v,
					    outer_first_mpls_over_udp),
			       &ib_spec->mpls.val.tag,
			       माप(ib_spec->mpls.val.tag));
			स_नकल(MLX5_ADDR_OF(fte_match_set_misc2, misc_params2_c,
					    outer_first_mpls_over_udp),
			       &ib_spec->mpls.mask.tag,
			       माप(ib_spec->mpls.mask.tag));
			अवरोध;
		हाल IB_FLOW_SPEC_GRE:
			अगर (check_mpls_supp_fields(MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
						   ft_field_support.outer_first_mpls_over_gre),
						   &ib_spec->mpls.mask.tag))
				वापस -EOPNOTSUPP;

			स_नकल(MLX5_ADDR_OF(fte_match_set_misc2, misc_params2_v,
					    outer_first_mpls_over_gre),
			       &ib_spec->mpls.val.tag,
			       माप(ib_spec->mpls.val.tag));
			स_नकल(MLX5_ADDR_OF(fte_match_set_misc2, misc_params2_c,
					    outer_first_mpls_over_gre),
			       &ib_spec->mpls.mask.tag,
			       माप(ib_spec->mpls.mask.tag));
			अवरोध;
		शेष:
			अगर (ib_spec->type & IB_FLOW_SPEC_INNER) अणु
				अगर (check_mpls_supp_fields(MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
							   ft_field_support.inner_first_mpls),
							   &ib_spec->mpls.mask.tag))
					वापस -EOPNOTSUPP;

				स_नकल(MLX5_ADDR_OF(fte_match_set_misc2, misc_params2_v,
						    inner_first_mpls),
				       &ib_spec->mpls.val.tag,
				       माप(ib_spec->mpls.val.tag));
				स_नकल(MLX5_ADDR_OF(fte_match_set_misc2, misc_params2_c,
						    inner_first_mpls),
				       &ib_spec->mpls.mask.tag,
				       माप(ib_spec->mpls.mask.tag));
			पूर्ण अन्यथा अणु
				अगर (check_mpls_supp_fields(MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
							   ft_field_support.outer_first_mpls),
							   &ib_spec->mpls.mask.tag))
					वापस -EOPNOTSUPP;

				स_नकल(MLX5_ADDR_OF(fte_match_set_misc2, misc_params2_v,
						    outer_first_mpls),
				       &ib_spec->mpls.val.tag,
				       माप(ib_spec->mpls.val.tag));
				स_नकल(MLX5_ADDR_OF(fte_match_set_misc2, misc_params2_c,
						    outer_first_mpls),
				       &ib_spec->mpls.mask.tag,
				       माप(ib_spec->mpls.mask.tag));
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IB_FLOW_SPEC_VXLAN_TUNNEL:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->tunnel.mask,
					 LAST_TUNNEL_FIELD))
			वापस -EOPNOTSUPP;

		MLX5_SET(fte_match_set_misc, misc_params_c, vxlan_vni,
			 ntohl(ib_spec->tunnel.mask.tunnel_id));
		MLX5_SET(fte_match_set_misc, misc_params_v, vxlan_vni,
			 ntohl(ib_spec->tunnel.val.tunnel_id));
		अवरोध;
	हाल IB_FLOW_SPEC_ACTION_TAG:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->flow_tag,
					 LAST_FLOW_TAG_FIELD))
			वापस -EOPNOTSUPP;
		अगर (ib_spec->flow_tag.tag_id >= BIT(24))
			वापस -EINVAL;

		flow_context->flow_tag = ib_spec->flow_tag.tag_id;
		flow_context->flags |= FLOW_CONTEXT_HAS_TAG;
		अवरोध;
	हाल IB_FLOW_SPEC_ACTION_DROP:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->drop,
					 LAST_DROP_FIELD))
			वापस -EOPNOTSUPP;
		action->action |= MLX5_FLOW_CONTEXT_ACTION_DROP;
		अवरोध;
	हाल IB_FLOW_SPEC_ACTION_HANDLE:
		ret = parse_flow_flow_action(to_mflow_act(ib_spec->action.act),
			flow_attr->flags & IB_FLOW_ATTR_FLAGS_EGRESS, action);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल IB_FLOW_SPEC_ACTION_COUNT:
		अगर (FIELDS_NOT_SUPPORTED(ib_spec->flow_count,
					 LAST_COUNTERS_FIELD))
			वापस -EOPNOTSUPP;

		/* क्रम now support only one counters spec per flow */
		अगर (action->action & MLX5_FLOW_CONTEXT_ACTION_COUNT)
			वापस -EINVAL;

		action->counters = ib_spec->flow_count.counters;
		action->action |= MLX5_FLOW_CONTEXT_ACTION_COUNT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* If a flow could catch both multicast and unicast packets,
 * it won't fall पूर्णांकo the multicast flow steering table and this rule
 * could steal other multicast packets.
 */
अटल bool flow_is_multicast_only(स्थिर काष्ठा ib_flow_attr *ib_attr)
अणु
	जोड़ ib_flow_spec *flow_spec;

	अगर (ib_attr->type != IB_FLOW_ATTR_NORMAL ||
	    ib_attr->num_of_specs < 1)
		वापस false;

	flow_spec = (जोड़ ib_flow_spec *)(ib_attr + 1);
	अगर (flow_spec->type == IB_FLOW_SPEC_IPV4) अणु
		काष्ठा ib_flow_spec_ipv4 *ipv4_spec;

		ipv4_spec = (काष्ठा ib_flow_spec_ipv4 *)flow_spec;
		अगर (ipv4_is_multicast(ipv4_spec->val.dst_ip))
			वापस true;

		वापस false;
	पूर्ण

	अगर (flow_spec->type == IB_FLOW_SPEC_ETH) अणु
		काष्ठा ib_flow_spec_eth *eth_spec;

		eth_spec = (काष्ठा ib_flow_spec_eth *)flow_spec;
		वापस is_multicast_ether_addr(eth_spec->mask.dst_mac) &&
		       is_multicast_ether_addr(eth_spec->val.dst_mac);
	पूर्ण

	वापस false;
पूर्ण

क्रमागत valid_spec अणु
	VALID_SPEC_INVALID,
	VALID_SPEC_VALID,
	VALID_SPEC_NA,
पूर्ण;

अटल क्रमागत valid_spec
is_valid_esp_aes_gcm(काष्ठा mlx5_core_dev *mdev,
		     स्थिर काष्ठा mlx5_flow_spec *spec,
		     स्थिर काष्ठा mlx5_flow_act *flow_act,
		     bool egress)
अणु
	स्थिर u32 *match_c = spec->match_criteria;
	bool is_crypto =
		(flow_act->action & (MLX5_FLOW_CONTEXT_ACTION_ENCRYPT |
				     MLX5_FLOW_CONTEXT_ACTION_DECRYPT));
	bool is_ipsec = mlx5_fs_is_ipsec_flow(match_c);
	bool is_drop = flow_act->action & MLX5_FLOW_CONTEXT_ACTION_DROP;

	/*
	 * Currently only crypto is supported in egress, when regular egress
	 * rules would be supported, always वापस VALID_SPEC_NA.
	 */
	अगर (!is_crypto)
		वापस VALID_SPEC_NA;

	वापस is_crypto && is_ipsec &&
		(!egress || (!is_drop &&
			     !(spec->flow_context.flags & FLOW_CONTEXT_HAS_TAG))) ?
		VALID_SPEC_VALID : VALID_SPEC_INVALID;
पूर्ण

अटल bool is_valid_spec(काष्ठा mlx5_core_dev *mdev,
			  स्थिर काष्ठा mlx5_flow_spec *spec,
			  स्थिर काष्ठा mlx5_flow_act *flow_act,
			  bool egress)
अणु
	/* We curretly only support ipsec egress flow */
	वापस is_valid_esp_aes_gcm(mdev, spec, flow_act, egress) != VALID_SPEC_INVALID;
पूर्ण

अटल bool is_valid_ethertype(काष्ठा mlx5_core_dev *mdev,
			       स्थिर काष्ठा ib_flow_attr *flow_attr,
			       bool check_inner)
अणु
	जोड़ ib_flow_spec *ib_spec = (जोड़ ib_flow_spec *)(flow_attr + 1);
	पूर्णांक match_ipv = check_inner ?
			MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
					ft_field_support.inner_ip_version) :
			MLX5_CAP_FLOWTABLE_NIC_RX(mdev,
					ft_field_support.outer_ip_version);
	पूर्णांक inner_bit = check_inner ? IB_FLOW_SPEC_INNER : 0;
	bool ipv4_spec_valid, ipv6_spec_valid;
	अचिन्हित पूर्णांक ip_spec_type = 0;
	bool has_ethertype = false;
	अचिन्हित पूर्णांक spec_index;
	bool mask_valid = true;
	u16 eth_type = 0;
	bool type_valid;

	/* Validate that ethertype is correct */
	क्रम (spec_index = 0; spec_index < flow_attr->num_of_specs; spec_index++) अणु
		अगर ((ib_spec->type == (IB_FLOW_SPEC_ETH | inner_bit)) &&
		    ib_spec->eth.mask.ether_type) अणु
			mask_valid = (ib_spec->eth.mask.ether_type ==
				      htons(0xffff));
			has_ethertype = true;
			eth_type = ntohs(ib_spec->eth.val.ether_type);
		पूर्ण अन्यथा अगर ((ib_spec->type == (IB_FLOW_SPEC_IPV4 | inner_bit)) ||
			   (ib_spec->type == (IB_FLOW_SPEC_IPV6 | inner_bit))) अणु
			ip_spec_type = ib_spec->type;
		पूर्ण
		ib_spec = (व्योम *)ib_spec + ib_spec->size;
	पूर्ण

	type_valid = (!has_ethertype) || (!ip_spec_type);
	अगर (!type_valid && mask_valid) अणु
		ipv4_spec_valid = (eth_type == ETH_P_IP) &&
			(ip_spec_type == (IB_FLOW_SPEC_IPV4 | inner_bit));
		ipv6_spec_valid = (eth_type == ETH_P_IPV6) &&
			(ip_spec_type == (IB_FLOW_SPEC_IPV6 | inner_bit));

		type_valid = (ipv4_spec_valid) || (ipv6_spec_valid) ||
			     (((eth_type == ETH_P_MPLS_UC) ||
			       (eth_type == ETH_P_MPLS_MC)) && match_ipv);
	पूर्ण

	वापस type_valid;
पूर्ण

अटल bool is_valid_attr(काष्ठा mlx5_core_dev *mdev,
			  स्थिर काष्ठा ib_flow_attr *flow_attr)
अणु
	वापस is_valid_ethertype(mdev, flow_attr, false) &&
	       is_valid_ethertype(mdev, flow_attr, true);
पूर्ण

अटल व्योम put_flow_table(काष्ठा mlx5_ib_dev *dev,
			   काष्ठा mlx5_ib_flow_prio *prio, bool ft_added)
अणु
	prio->refcount -= !!ft_added;
	अगर (!prio->refcount) अणु
		mlx5_destroy_flow_table(prio->flow_table);
		prio->flow_table = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_ib_destroy_flow(काष्ठा ib_flow *flow_id)
अणु
	काष्ठा mlx5_ib_flow_handler *handler = container_of(flow_id,
							  काष्ठा mlx5_ib_flow_handler,
							  ibflow);
	काष्ठा mlx5_ib_flow_handler *iter, *पंचांगp;
	काष्ठा mlx5_ib_dev *dev = handler->dev;

	mutex_lock(&dev->flow_db->lock);

	list_क्रम_each_entry_safe(iter, पंचांगp, &handler->list, list) अणु
		mlx5_del_flow_rules(iter->rule);
		put_flow_table(dev, iter->prio, true);
		list_del(&iter->list);
		kमुक्त(iter);
	पूर्ण

	mlx5_del_flow_rules(handler->rule);
	put_flow_table(dev, handler->prio, true);
	mlx5_ib_counters_clear_description(handler->ibcounters);
	mutex_unlock(&dev->flow_db->lock);
	अगर (handler->flow_matcher)
		atomic_dec(&handler->flow_matcher->usecnt);
	kमुक्त(handler);

	वापस 0;
पूर्ण

अटल पूर्णांक ib_prio_to_core_prio(अचिन्हित पूर्णांक priority, bool करोnt_trap)
अणु
	priority *= 2;
	अगर (!करोnt_trap)
		priority++;
	वापस priority;
पूर्ण

क्रमागत flow_table_type अणु
	MLX5_IB_FT_RX,
	MLX5_IB_FT_TX
पूर्ण;

#घोषणा MLX5_FS_MAX_TYPES	 6
#घोषणा MLX5_FS_MAX_ENTRIES	 BIT(16)

अटल काष्ठा mlx5_ib_flow_prio *_get_prio(काष्ठा mlx5_flow_namespace *ns,
					   काष्ठा mlx5_ib_flow_prio *prio,
					   पूर्णांक priority,
					   पूर्णांक num_entries, पूर्णांक num_groups,
					   u32 flags)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_table *ft;

	ft_attr.prio = priority;
	ft_attr.max_fte = num_entries;
	ft_attr.flags = flags;
	ft_attr.स्वतःgroup.max_num_groups = num_groups;
	ft = mlx5_create_स्वतः_grouped_flow_table(ns, &ft_attr);
	अगर (IS_ERR(ft))
		वापस ERR_CAST(ft);

	prio->flow_table = ft;
	prio->refcount = 0;
	वापस prio;
पूर्ण

अटल काष्ठा mlx5_ib_flow_prio *get_flow_table(काष्ठा mlx5_ib_dev *dev,
						काष्ठा ib_flow_attr *flow_attr,
						क्रमागत flow_table_type ft_type)
अणु
	bool करोnt_trap = flow_attr->flags & IB_FLOW_ATTR_FLAGS_DONT_TRAP;
	काष्ठा mlx5_flow_namespace *ns = शून्य;
	क्रमागत mlx5_flow_namespace_type fn_type;
	काष्ठा mlx5_ib_flow_prio *prio;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक max_table_size;
	पूर्णांक num_entries;
	पूर्णांक num_groups;
	bool esw_encap;
	u32 flags = 0;
	पूर्णांक priority;

	max_table_size = BIT(MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev,
						       log_max_ft_size));
	esw_encap = mlx5_eचयन_get_encap_mode(dev->mdev) !=
		DEVLINK_ESWITCH_ENCAP_MODE_NONE;
	चयन (flow_attr->type) अणु
	हाल IB_FLOW_ATTR_NORMAL:
		अगर (flow_is_multicast_only(flow_attr) && !करोnt_trap)
			priority = MLX5_IB_FLOW_MCAST_PRIO;
		अन्यथा
			priority = ib_prio_to_core_prio(flow_attr->priority,
							करोnt_trap);
		अगर (ft_type == MLX5_IB_FT_RX) अणु
			fn_type = MLX5_FLOW_NAMESPACE_BYPASS;
			prio = &dev->flow_db->prios[priority];
			अगर (!dev->is_rep && !esw_encap &&
			    MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev, decap))
				flags |= MLX5_FLOW_TABLE_TUNNEL_EN_DECAP;
			अगर (!dev->is_rep && !esw_encap &&
			    MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev,
						      reक्रमmat_l3_tunnel_to_l2))
				flags |= MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT;
		पूर्ण अन्यथा अणु
			max_table_size = BIT(MLX5_CAP_FLOWTABLE_NIC_TX(
				dev->mdev, log_max_ft_size));
			fn_type = MLX5_FLOW_NAMESPACE_EGRESS;
			prio = &dev->flow_db->egress_prios[priority];
			अगर (!dev->is_rep && !esw_encap &&
			    MLX5_CAP_FLOWTABLE_NIC_TX(dev->mdev, reक्रमmat))
				flags |= MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT;
		पूर्ण
		ns = mlx5_get_flow_namespace(dev->mdev, fn_type);
		num_entries = MLX5_FS_MAX_ENTRIES;
		num_groups = MLX5_FS_MAX_TYPES;
		अवरोध;
	हाल IB_FLOW_ATTR_ALL_DEFAULT:
	हाल IB_FLOW_ATTR_MC_DEFAULT:
		ns = mlx5_get_flow_namespace(dev->mdev,
					     MLX5_FLOW_NAMESPACE_LEFTOVERS);
		build_leftovers_ft_param(&priority, &num_entries, &num_groups);
		prio = &dev->flow_db->prios[MLX5_IB_FLOW_LEFTOVERS_PRIO];
		अवरोध;
	हाल IB_FLOW_ATTR_SNIFFER:
		अगर (!MLX5_CAP_FLOWTABLE(dev->mdev,
					allow_snअगरfer_and_nic_rx_shared_tir))
			वापस ERR_PTR(-EOPNOTSUPP);

		ns = mlx5_get_flow_namespace(
			dev->mdev, ft_type == MLX5_IB_FT_RX ?
					   MLX5_FLOW_NAMESPACE_SNIFFER_RX :
					   MLX5_FLOW_NAMESPACE_SNIFFER_TX);

		prio = &dev->flow_db->snअगरfer[ft_type];
		priority = 0;
		num_entries = 1;
		num_groups = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (!ns)
		वापस ERR_PTR(-EOPNOTSUPP);

	max_table_size = min_t(पूर्णांक, num_entries, max_table_size);

	ft = prio->flow_table;
	अगर (!ft)
		वापस _get_prio(ns, prio, priority, max_table_size, num_groups,
				 flags);

	वापस prio;
पूर्ण

अटल व्योम set_underlay_qp(काष्ठा mlx5_ib_dev *dev,
			    काष्ठा mlx5_flow_spec *spec,
			    u32 underlay_qpn)
अणु
	व्योम *misc_params_c = MLX5_ADDR_OF(fte_match_param,
					   spec->match_criteria,
					   misc_parameters);
	व्योम *misc_params_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
					   misc_parameters);

	अगर (underlay_qpn &&
	    MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev,
				      ft_field_support.bth_dst_qp)) अणु
		MLX5_SET(fte_match_set_misc,
			 misc_params_v, bth_dst_qp, underlay_qpn);
		MLX5_SET(fte_match_set_misc,
			 misc_params_c, bth_dst_qp, 0xffffff);
	पूर्ण
पूर्ण

अटल व्योम mlx5_ib_set_rule_source_port(काष्ठा mlx5_ib_dev *dev,
					 काष्ठा mlx5_flow_spec *spec,
					 काष्ठा mlx5_eचयन_rep *rep)
अणु
	काष्ठा mlx5_eचयन *esw = dev->mdev->priv.eचयन;
	व्योम *misc;

	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    misc_parameters_2);

		MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_क्रम_match(rep->esw,
								   rep->vport));
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    misc_parameters_2);

		MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_0,
			 mlx5_eचयन_get_vport_metadata_mask());
	पूर्ण अन्यथा अणु
		misc = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				    misc_parameters);

		MLX5_SET(fte_match_set_misc, misc, source_port, rep->vport);

		misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				    misc_parameters);

		MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);
	पूर्ण
पूर्ण

अटल काष्ठा mlx5_ib_flow_handler *_create_flow_rule(काष्ठा mlx5_ib_dev *dev,
						      काष्ठा mlx5_ib_flow_prio *ft_prio,
						      स्थिर काष्ठा ib_flow_attr *flow_attr,
						      काष्ठा mlx5_flow_destination *dst,
						      u32 underlay_qpn,
						      काष्ठा mlx5_ib_create_flow *ucmd)
अणु
	काष्ठा mlx5_flow_table	*ft = ft_prio->flow_table;
	काष्ठा mlx5_ib_flow_handler *handler;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5_flow_destination dest_arr[2] = अणुपूर्ण;
	काष्ठा mlx5_flow_destination *rule_dst = dest_arr;
	स्थिर व्योम *ib_flow = (स्थिर व्योम *)flow_attr + माप(*flow_attr);
	अचिन्हित पूर्णांक spec_index;
	u32 prev_type = 0;
	पूर्णांक err = 0;
	पूर्णांक dest_num = 0;
	bool is_egress = flow_attr->flags & IB_FLOW_ATTR_FLAGS_EGRESS;

	अगर (!is_valid_attr(dev->mdev, flow_attr))
		वापस ERR_PTR(-EINVAL);

	अगर (dev->is_rep && is_egress)
		वापस ERR_PTR(-EINVAL);

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	handler = kzalloc(माप(*handler), GFP_KERNEL);
	अगर (!handler || !spec) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	INIT_LIST_HEAD(&handler->list);

	क्रम (spec_index = 0; spec_index < flow_attr->num_of_specs; spec_index++) अणु
		err = parse_flow_attr(dev->mdev, spec,
				      ib_flow, flow_attr, &flow_act,
				      prev_type);
		अगर (err < 0)
			जाओ मुक्त;

		prev_type = ((जोड़ ib_flow_spec *)ib_flow)->type;
		ib_flow += ((जोड़ ib_flow_spec *)ib_flow)->size;
	पूर्ण

	अगर (dst && !(flow_act.action & MLX5_FLOW_CONTEXT_ACTION_DROP)) अणु
		स_नकल(&dest_arr[0], dst, माप(*dst));
		dest_num++;
	पूर्ण

	अगर (!flow_is_multicast_only(flow_attr))
		set_underlay_qp(dev, spec, underlay_qpn);

	अगर (dev->is_rep && flow_attr->type != IB_FLOW_ATTR_SNIFFER) अणु
		काष्ठा mlx5_eचयन_rep *rep;

		rep = dev->port[flow_attr->port - 1].rep;
		अगर (!rep) अणु
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण

		mlx5_ib_set_rule_source_port(dev, spec, rep);
	पूर्ण

	spec->match_criteria_enable = get_match_criteria_enable(spec->match_criteria);

	अगर (is_egress &&
	    !is_valid_spec(dev->mdev, spec, &flow_act, is_egress)) अणु
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	अगर (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_COUNT) अणु
		काष्ठा mlx5_ib_mcounters *mcounters;

		err = mlx5_ib_flow_counters_set_data(flow_act.counters, ucmd);
		अगर (err)
			जाओ मुक्त;

		mcounters = to_mcounters(flow_act.counters);
		handler->ibcounters = flow_act.counters;
		dest_arr[dest_num].type =
			MLX5_FLOW_DESTINATION_TYPE_COUNTER;
		dest_arr[dest_num].counter_id =
			mlx5_fc_id(mcounters->hw_cntrs_hndl);
		dest_num++;
	पूर्ण

	अगर (flow_act.action & MLX5_FLOW_CONTEXT_ACTION_DROP) अणु
		अगर (!dest_num)
			rule_dst = शून्य;
	पूर्ण अन्यथा अणु
		अगर (flow_attr->flags & IB_FLOW_ATTR_FLAGS_DONT_TRAP)
			flow_act.action |=
				MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO;
		अगर (is_egress)
			flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_ALLOW;
		अन्यथा अगर (dest_num)
			flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	पूर्ण

	अगर ((spec->flow_context.flags & FLOW_CONTEXT_HAS_TAG)  &&
	    (flow_attr->type == IB_FLOW_ATTR_ALL_DEFAULT ||
	     flow_attr->type == IB_FLOW_ATTR_MC_DEFAULT)) अणु
		mlx5_ib_warn(dev, "Flow tag %u and attribute type %x isn't allowed in leftovers\n",
			     spec->flow_context.flow_tag, flow_attr->type);
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण
	handler->rule = mlx5_add_flow_rules(ft, spec,
					    &flow_act,
					    rule_dst, dest_num);

	अगर (IS_ERR(handler->rule)) अणु
		err = PTR_ERR(handler->rule);
		जाओ मुक्त;
	पूर्ण

	ft_prio->refcount++;
	handler->prio = ft_prio;
	handler->dev = dev;

	ft_prio->flow_table = ft;
मुक्त:
	अगर (err && handler) अणु
		mlx5_ib_counters_clear_description(handler->ibcounters);
		kमुक्त(handler);
	पूर्ण
	kvमुक्त(spec);
	वापस err ? ERR_PTR(err) : handler;
पूर्ण

अटल काष्ठा mlx5_ib_flow_handler *create_flow_rule(काष्ठा mlx5_ib_dev *dev,
						     काष्ठा mlx5_ib_flow_prio *ft_prio,
						     स्थिर काष्ठा ib_flow_attr *flow_attr,
						     काष्ठा mlx5_flow_destination *dst)
अणु
	वापस _create_flow_rule(dev, ft_prio, flow_attr, dst, 0, शून्य);
पूर्ण

क्रमागत अणु
	LEFTOVERS_MC,
	LEFTOVERS_UC,
पूर्ण;

अटल काष्ठा mlx5_ib_flow_handler *create_leftovers_rule(काष्ठा mlx5_ib_dev *dev,
							  काष्ठा mlx5_ib_flow_prio *ft_prio,
							  काष्ठा ib_flow_attr *flow_attr,
							  काष्ठा mlx5_flow_destination *dst)
अणु
	काष्ठा mlx5_ib_flow_handler *handler_ucast = शून्य;
	काष्ठा mlx5_ib_flow_handler *handler = शून्य;

	अटल काष्ठा अणु
		काष्ठा ib_flow_attr	flow_attr;
		काष्ठा ib_flow_spec_eth eth_flow;
	पूर्ण leftovers_specs[] = अणु
		[LEFTOVERS_MC] = अणु
			.flow_attr = अणु
				.num_of_specs = 1,
				.size = माप(leftovers_specs[0])
			पूर्ण,
			.eth_flow = अणु
				.type = IB_FLOW_SPEC_ETH,
				.size = माप(काष्ठा ib_flow_spec_eth),
				.mask = अणु.dst_mac = अणु0x1पूर्ण पूर्ण,
				.val =  अणु.dst_mac = अणु0x1पूर्ण पूर्ण
			पूर्ण
		पूर्ण,
		[LEFTOVERS_UC] = अणु
			.flow_attr = अणु
				.num_of_specs = 1,
				.size = माप(leftovers_specs[0])
			पूर्ण,
			.eth_flow = अणु
				.type = IB_FLOW_SPEC_ETH,
				.size = माप(काष्ठा ib_flow_spec_eth),
				.mask = अणु.dst_mac = अणु0x1पूर्ण पूर्ण,
				.val = अणु.dst_mac = अणुपूर्ण पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण;

	handler = create_flow_rule(dev, ft_prio,
				   &leftovers_specs[LEFTOVERS_MC].flow_attr,
				   dst);
	अगर (!IS_ERR(handler) &&
	    flow_attr->type == IB_FLOW_ATTR_ALL_DEFAULT) अणु
		handler_ucast = create_flow_rule(dev, ft_prio,
						 &leftovers_specs[LEFTOVERS_UC].flow_attr,
						 dst);
		अगर (IS_ERR(handler_ucast)) अणु
			mlx5_del_flow_rules(handler->rule);
			ft_prio->refcount--;
			kमुक्त(handler);
			handler = handler_ucast;
		पूर्ण अन्यथा अणु
			list_add(&handler_ucast->list, &handler->list);
		पूर्ण
	पूर्ण

	वापस handler;
पूर्ण

अटल काष्ठा mlx5_ib_flow_handler *create_snअगरfer_rule(काष्ठा mlx5_ib_dev *dev,
							काष्ठा mlx5_ib_flow_prio *ft_rx,
							काष्ठा mlx5_ib_flow_prio *ft_tx,
							काष्ठा mlx5_flow_destination *dst)
अणु
	काष्ठा mlx5_ib_flow_handler *handler_rx;
	काष्ठा mlx5_ib_flow_handler *handler_tx;
	पूर्णांक err;
	अटल स्थिर काष्ठा ib_flow_attr flow_attr  = अणु
		.num_of_specs = 0,
		.type = IB_FLOW_ATTR_SNIFFER,
		.size = माप(flow_attr)
	पूर्ण;

	handler_rx = create_flow_rule(dev, ft_rx, &flow_attr, dst);
	अगर (IS_ERR(handler_rx)) अणु
		err = PTR_ERR(handler_rx);
		जाओ err;
	पूर्ण

	handler_tx = create_flow_rule(dev, ft_tx, &flow_attr, dst);
	अगर (IS_ERR(handler_tx)) अणु
		err = PTR_ERR(handler_tx);
		जाओ err_tx;
	पूर्ण

	list_add(&handler_tx->list, &handler_rx->list);

	वापस handler_rx;

err_tx:
	mlx5_del_flow_rules(handler_rx->rule);
	ft_rx->refcount--;
	kमुक्त(handler_rx);
err:
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा ib_flow *mlx5_ib_create_flow(काष्ठा ib_qp *qp,
					   काष्ठा ib_flow_attr *flow_attr,
					   काष्ठा ib_udata *udata)
अणु
	काष्ठा mlx5_ib_dev *dev = to_mdev(qp->device);
	काष्ठा mlx5_ib_qp *mqp = to_mqp(qp);
	काष्ठा mlx5_ib_flow_handler *handler = शून्य;
	काष्ठा mlx5_flow_destination *dst = शून्य;
	काष्ठा mlx5_ib_flow_prio *ft_prio_tx = शून्य;
	काष्ठा mlx5_ib_flow_prio *ft_prio;
	bool is_egress = flow_attr->flags & IB_FLOW_ATTR_FLAGS_EGRESS;
	काष्ठा mlx5_ib_create_flow *ucmd = शून्य, ucmd_hdr;
	माप_प्रकार min_ucmd_sz, required_ucmd_sz;
	पूर्णांक err;
	पूर्णांक underlay_qpn;

	अगर (udata && udata->inlen) अणु
		min_ucmd_sz = दुरत्वend(काष्ठा mlx5_ib_create_flow, reserved);
		अगर (udata->inlen < min_ucmd_sz)
			वापस ERR_PTR(-EOPNOTSUPP);

		err = ib_copy_from_udata(&ucmd_hdr, udata, min_ucmd_sz);
		अगर (err)
			वापस ERR_PTR(err);

		/* currently supports only one counters data */
		अगर (ucmd_hdr.ncounters_data > 1)
			वापस ERR_PTR(-EINVAL);

		required_ucmd_sz = min_ucmd_sz +
			माप(काष्ठा mlx5_ib_flow_counters_data) *
			ucmd_hdr.ncounters_data;
		अगर (udata->inlen > required_ucmd_sz &&
		    !ib_is_udata_cleared(udata, required_ucmd_sz,
					 udata->inlen - required_ucmd_sz))
			वापस ERR_PTR(-EOPNOTSUPP);

		ucmd = kzalloc(required_ucmd_sz, GFP_KERNEL);
		अगर (!ucmd)
			वापस ERR_PTR(-ENOMEM);

		err = ib_copy_from_udata(ucmd, udata, required_ucmd_sz);
		अगर (err)
			जाओ मुक्त_ucmd;
	पूर्ण

	अगर (flow_attr->priority > MLX5_IB_FLOW_LAST_PRIO) अणु
		err = -ENOMEM;
		जाओ मुक्त_ucmd;
	पूर्ण

	अगर (flow_attr->flags &
	    ~(IB_FLOW_ATTR_FLAGS_DONT_TRAP | IB_FLOW_ATTR_FLAGS_EGRESS)) अणु
		err = -EINVAL;
		जाओ मुक्त_ucmd;
	पूर्ण

	अगर (is_egress &&
	    (flow_attr->type == IB_FLOW_ATTR_ALL_DEFAULT ||
	     flow_attr->type == IB_FLOW_ATTR_MC_DEFAULT)) अणु
		err = -EINVAL;
		जाओ मुक्त_ucmd;
	पूर्ण

	dst = kzalloc(माप(*dst), GFP_KERNEL);
	अगर (!dst) अणु
		err = -ENOMEM;
		जाओ मुक्त_ucmd;
	पूर्ण

	mutex_lock(&dev->flow_db->lock);

	ft_prio = get_flow_table(dev, flow_attr,
				 is_egress ? MLX5_IB_FT_TX : MLX5_IB_FT_RX);
	अगर (IS_ERR(ft_prio)) अणु
		err = PTR_ERR(ft_prio);
		जाओ unlock;
	पूर्ण
	अगर (flow_attr->type == IB_FLOW_ATTR_SNIFFER) अणु
		ft_prio_tx = get_flow_table(dev, flow_attr, MLX5_IB_FT_TX);
		अगर (IS_ERR(ft_prio_tx)) अणु
			err = PTR_ERR(ft_prio_tx);
			ft_prio_tx = शून्य;
			जाओ destroy_ft;
		पूर्ण
	पूर्ण

	अगर (is_egress) अणु
		dst->type = MLX5_FLOW_DESTINATION_TYPE_PORT;
	पूर्ण अन्यथा अणु
		dst->type = MLX5_FLOW_DESTINATION_TYPE_TIR;
		अगर (mqp->is_rss)
			dst->tir_num = mqp->rss_qp.tirn;
		अन्यथा
			dst->tir_num = mqp->raw_packet_qp.rq.tirn;
	पूर्ण

	चयन (flow_attr->type) अणु
	हाल IB_FLOW_ATTR_NORMAL:
		underlay_qpn = (mqp->flags & IB_QP_CREATE_SOURCE_QPN) ?
				       mqp->underlay_qpn :
				       0;
		handler = _create_flow_rule(dev, ft_prio, flow_attr, dst,
					    underlay_qpn, ucmd);
		अवरोध;
	हाल IB_FLOW_ATTR_ALL_DEFAULT:
	हाल IB_FLOW_ATTR_MC_DEFAULT:
		handler = create_leftovers_rule(dev, ft_prio, flow_attr, dst);
		अवरोध;
	हाल IB_FLOW_ATTR_SNIFFER:
		handler = create_snअगरfer_rule(dev, ft_prio, ft_prio_tx, dst);
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ destroy_ft;
	पूर्ण

	अगर (IS_ERR(handler)) अणु
		err = PTR_ERR(handler);
		handler = शून्य;
		जाओ destroy_ft;
	पूर्ण

	mutex_unlock(&dev->flow_db->lock);
	kमुक्त(dst);
	kमुक्त(ucmd);

	वापस &handler->ibflow;

destroy_ft:
	put_flow_table(dev, ft_prio, false);
	अगर (ft_prio_tx)
		put_flow_table(dev, ft_prio_tx, false);
unlock:
	mutex_unlock(&dev->flow_db->lock);
	kमुक्त(dst);
मुक्त_ucmd:
	kमुक्त(ucmd);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा mlx5_ib_flow_prio *
_get_flow_table(काष्ठा mlx5_ib_dev *dev,
		काष्ठा mlx5_ib_flow_matcher *fs_matcher,
		bool mcast)
अणु
	काष्ठा mlx5_flow_namespace *ns = शून्य;
	काष्ठा mlx5_ib_flow_prio *prio = शून्य;
	पूर्णांक max_table_size = 0;
	bool esw_encap;
	u32 flags = 0;
	पूर्णांक priority;

	अगर (mcast)
		priority = MLX5_IB_FLOW_MCAST_PRIO;
	अन्यथा
		priority = ib_prio_to_core_prio(fs_matcher->priority, false);

	esw_encap = mlx5_eचयन_get_encap_mode(dev->mdev) !=
		DEVLINK_ESWITCH_ENCAP_MODE_NONE;
	चयन (fs_matcher->ns_type) अणु
	हाल MLX5_FLOW_NAMESPACE_BYPASS:
		max_table_size = BIT(
			MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev, log_max_ft_size));
		अगर (MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev, decap) && !esw_encap)
			flags |= MLX5_FLOW_TABLE_TUNNEL_EN_DECAP;
		अगर (MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev,
					      reक्रमmat_l3_tunnel_to_l2) &&
		    !esw_encap)
			flags |= MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT;
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_EGRESS:
		max_table_size = BIT(
			MLX5_CAP_FLOWTABLE_NIC_TX(dev->mdev, log_max_ft_size));
		अगर (MLX5_CAP_FLOWTABLE_NIC_TX(dev->mdev, reक्रमmat) &&
		    !esw_encap)
			flags |= MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT;
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_FDB:
		max_table_size = BIT(
			MLX5_CAP_ESW_FLOWTABLE_FDB(dev->mdev, log_max_ft_size));
		अगर (MLX5_CAP_ESW_FLOWTABLE_FDB(dev->mdev, decap) && esw_encap)
			flags |= MLX5_FLOW_TABLE_TUNNEL_EN_DECAP;
		अगर (MLX5_CAP_ESW_FLOWTABLE_FDB(dev->mdev,
					       reक्रमmat_l3_tunnel_to_l2) &&
		    esw_encap)
			flags |= MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT;
		priority = FDB_BYPASS_PATH;
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_RDMA_RX:
		max_table_size = BIT(
			MLX5_CAP_FLOWTABLE_RDMA_RX(dev->mdev, log_max_ft_size));
		priority = fs_matcher->priority;
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_RDMA_TX:
		max_table_size = BIT(
			MLX5_CAP_FLOWTABLE_RDMA_TX(dev->mdev, log_max_ft_size));
		priority = fs_matcher->priority;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	max_table_size = min_t(पूर्णांक, max_table_size, MLX5_FS_MAX_ENTRIES);

	ns = mlx5_get_flow_namespace(dev->mdev, fs_matcher->ns_type);
	अगर (!ns)
		वापस ERR_PTR(-EOPNOTSUPP);

	चयन (fs_matcher->ns_type) अणु
	हाल MLX5_FLOW_NAMESPACE_BYPASS:
		prio = &dev->flow_db->prios[priority];
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_EGRESS:
		prio = &dev->flow_db->egress_prios[priority];
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_FDB:
		prio = &dev->flow_db->fdb;
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_RDMA_RX:
		prio = &dev->flow_db->rdma_rx[priority];
		अवरोध;
	हाल MLX5_FLOW_NAMESPACE_RDMA_TX:
		prio = &dev->flow_db->rdma_tx[priority];
		अवरोध;
	शेष: वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!prio)
		वापस ERR_PTR(-EINVAL);

	अगर (prio->flow_table)
		वापस prio;

	वापस _get_prio(ns, prio, priority, max_table_size,
			 MLX5_FS_MAX_TYPES, flags);
पूर्ण

अटल काष्ठा mlx5_ib_flow_handler *
_create_raw_flow_rule(काष्ठा mlx5_ib_dev *dev,
		      काष्ठा mlx5_ib_flow_prio *ft_prio,
		      काष्ठा mlx5_flow_destination *dst,
		      काष्ठा mlx5_ib_flow_matcher  *fs_matcher,
		      काष्ठा mlx5_flow_context *flow_context,
		      काष्ठा mlx5_flow_act *flow_act,
		      व्योम *cmd_in, पूर्णांक inlen,
		      पूर्णांक dst_num)
अणु
	काष्ठा mlx5_ib_flow_handler *handler;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5_flow_table *ft = ft_prio->flow_table;
	पूर्णांक err = 0;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	handler = kzalloc(माप(*handler), GFP_KERNEL);
	अगर (!handler || !spec) अणु
		err = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	INIT_LIST_HEAD(&handler->list);

	स_नकल(spec->match_value, cmd_in, inlen);
	स_नकल(spec->match_criteria, fs_matcher->matcher_mask.match_params,
	       fs_matcher->mask_len);
	spec->match_criteria_enable = fs_matcher->match_criteria_enable;
	spec->flow_context = *flow_context;

	handler->rule = mlx5_add_flow_rules(ft, spec,
					    flow_act, dst, dst_num);

	अगर (IS_ERR(handler->rule)) अणु
		err = PTR_ERR(handler->rule);
		जाओ मुक्त;
	पूर्ण

	ft_prio->refcount++;
	handler->prio = ft_prio;
	handler->dev = dev;
	ft_prio->flow_table = ft;

मुक्त:
	अगर (err)
		kमुक्त(handler);
	kvमुक्त(spec);
	वापस err ? ERR_PTR(err) : handler;
पूर्ण

अटल bool raw_fs_is_multicast(काष्ठा mlx5_ib_flow_matcher *fs_matcher,
				व्योम *match_v)
अणु
	व्योम *match_c;
	व्योम *match_v_set_lyr_2_4, *match_c_set_lyr_2_4;
	व्योम *dmac, *dmac_mask;
	व्योम *ipv4, *ipv4_mask;

	अगर (!(fs_matcher->match_criteria_enable &
	      (1 << MATCH_CRITERIA_ENABLE_OUTER_BIT)))
		वापस false;

	match_c = fs_matcher->matcher_mask.match_params;
	match_v_set_lyr_2_4 = MLX5_ADDR_OF(fte_match_param, match_v,
					   outer_headers);
	match_c_set_lyr_2_4 = MLX5_ADDR_OF(fte_match_param, match_c,
					   outer_headers);

	dmac = MLX5_ADDR_OF(fte_match_set_lyr_2_4, match_v_set_lyr_2_4,
			    dmac_47_16);
	dmac_mask = MLX5_ADDR_OF(fte_match_set_lyr_2_4, match_c_set_lyr_2_4,
				 dmac_47_16);

	अगर (is_multicast_ether_addr(dmac) &&
	    is_multicast_ether_addr(dmac_mask))
		वापस true;

	ipv4 = MLX5_ADDR_OF(fte_match_set_lyr_2_4, match_v_set_lyr_2_4,
			    dst_ipv4_dst_ipv6.ipv4_layout.ipv4);

	ipv4_mask = MLX5_ADDR_OF(fte_match_set_lyr_2_4, match_c_set_lyr_2_4,
				 dst_ipv4_dst_ipv6.ipv4_layout.ipv4);

	अगर (ipv4_is_multicast(*(__be32 *)(ipv4)) &&
	    ipv4_is_multicast(*(__be32 *)(ipv4_mask)))
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा mlx5_ib_flow_handler *raw_fs_rule_add(
	काष्ठा mlx5_ib_dev *dev, काष्ठा mlx5_ib_flow_matcher *fs_matcher,
	काष्ठा mlx5_flow_context *flow_context, काष्ठा mlx5_flow_act *flow_act,
	u32 counter_id, व्योम *cmd_in, पूर्णांक inlen, पूर्णांक dest_id, पूर्णांक dest_type)
अणु
	काष्ठा mlx5_flow_destination *dst;
	काष्ठा mlx5_ib_flow_prio *ft_prio;
	काष्ठा mlx5_ib_flow_handler *handler;
	पूर्णांक dst_num = 0;
	bool mcast;
	पूर्णांक err;

	अगर (fs_matcher->flow_type != MLX5_IB_FLOW_TYPE_NORMAL)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (fs_matcher->priority > MLX5_IB_FLOW_LAST_PRIO)
		वापस ERR_PTR(-ENOMEM);

	dst = kसुस्मृति(2, माप(*dst), GFP_KERNEL);
	अगर (!dst)
		वापस ERR_PTR(-ENOMEM);

	mcast = raw_fs_is_multicast(fs_matcher, cmd_in);
	mutex_lock(&dev->flow_db->lock);

	ft_prio = _get_flow_table(dev, fs_matcher, mcast);
	अगर (IS_ERR(ft_prio)) अणु
		err = PTR_ERR(ft_prio);
		जाओ unlock;
	पूर्ण

	चयन (dest_type) अणु
	हाल MLX5_FLOW_DESTINATION_TYPE_TIR:
		dst[dst_num].type = dest_type;
		dst[dst_num++].tir_num = dest_id;
		flow_act->action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
		अवरोध;
	हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE:
		dst[dst_num].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM;
		dst[dst_num++].ft_num = dest_id;
		flow_act->action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
		अवरोध;
	हाल MLX5_FLOW_DESTINATION_TYPE_PORT:
		dst[dst_num++].type = MLX5_FLOW_DESTINATION_TYPE_PORT;
		flow_act->action |= MLX5_FLOW_CONTEXT_ACTION_ALLOW;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (flow_act->action & MLX5_FLOW_CONTEXT_ACTION_COUNT) अणु
		dst[dst_num].type = MLX5_FLOW_DESTINATION_TYPE_COUNTER;
		dst[dst_num].counter_id = counter_id;
		dst_num++;
	पूर्ण

	handler = _create_raw_flow_rule(dev, ft_prio, dst_num ? dst : शून्य,
					fs_matcher, flow_context, flow_act,
					cmd_in, inlen, dst_num);

	अगर (IS_ERR(handler)) अणु
		err = PTR_ERR(handler);
		जाओ destroy_ft;
	पूर्ण

	mutex_unlock(&dev->flow_db->lock);
	atomic_inc(&fs_matcher->usecnt);
	handler->flow_matcher = fs_matcher;

	kमुक्त(dst);

	वापस handler;

destroy_ft:
	put_flow_table(dev, ft_prio, false);
unlock:
	mutex_unlock(&dev->flow_db->lock);
	kमुक्त(dst);

	वापस ERR_PTR(err);
पूर्ण

अटल u32 mlx5_ib_flow_action_flags_to_accel_xfrm_flags(u32 mlx5_flags)
अणु
	u32 flags = 0;

	अगर (mlx5_flags & MLX5_IB_UAPI_FLOW_ACTION_FLAGS_REQUIRE_METADATA)
		flags |= MLX5_ACCEL_XFRM_FLAG_REQUIRE_METADATA;

	वापस flags;
पूर्ण

#घोषणा MLX5_FLOW_ACTION_ESP_CREATE_LAST_SUPPORTED                             \
	MLX5_IB_UAPI_FLOW_ACTION_FLAGS_REQUIRE_METADATA
अटल काष्ठा ib_flow_action *
mlx5_ib_create_flow_action_esp(काष्ठा ib_device *device,
			       स्थिर काष्ठा ib_flow_action_attrs_esp *attr,
			       काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_dev *mdev = to_mdev(device);
	काष्ठा ib_uverbs_flow_action_esp_keymat_aes_gcm *aes_gcm;
	काष्ठा mlx5_accel_esp_xfrm_attrs accel_attrs = अणुपूर्ण;
	काष्ठा mlx5_ib_flow_action *action;
	u64 action_flags;
	u64 flags;
	पूर्णांक err = 0;

	err = uverbs_get_flags64(
		&action_flags, attrs, MLX5_IB_ATTR_CREATE_FLOW_ACTION_FLAGS,
		((MLX5_FLOW_ACTION_ESP_CREATE_LAST_SUPPORTED << 1) - 1));
	अगर (err)
		वापस ERR_PTR(err);

	flags = mlx5_ib_flow_action_flags_to_accel_xfrm_flags(action_flags);

	/* We current only support a subset of the standard features. Only a
	 * keymat of type AES_GCM, with icv_len == 16, iv_algo == SEQ and esn
	 * (with overlap). Full offload mode isn't supported.
	 */
	अगर (!attr->keymat || attr->replay || attr->encap ||
	    attr->spi || attr->seq || attr->tfc_pad ||
	    attr->hard_limit_pkts ||
	    (attr->flags & ~(IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED |
			     IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ENCRYPT)))
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (attr->keymat->protocol !=
	    IB_UVERBS_FLOW_ACTION_ESP_KEYMAT_AES_GCM)
		वापस ERR_PTR(-EOPNOTSUPP);

	aes_gcm = &attr->keymat->keymat.aes_gcm;

	अगर (aes_gcm->icv_len != 16 ||
	    aes_gcm->iv_algo != IB_UVERBS_FLOW_ACTION_IV_ALGO_SEQ)
		वापस ERR_PTR(-EOPNOTSUPP);

	action = kदो_स्मृति(माप(*action), GFP_KERNEL);
	अगर (!action)
		वापस ERR_PTR(-ENOMEM);

	action->esp_aes_gcm.ib_flags = attr->flags;
	स_नकल(&accel_attrs.keymat.aes_gcm.aes_key, &aes_gcm->aes_key,
	       माप(accel_attrs.keymat.aes_gcm.aes_key));
	accel_attrs.keymat.aes_gcm.key_len = aes_gcm->key_len * 8;
	स_नकल(&accel_attrs.keymat.aes_gcm.salt, &aes_gcm->salt,
	       माप(accel_attrs.keymat.aes_gcm.salt));
	स_नकल(&accel_attrs.keymat.aes_gcm.seq_iv, &aes_gcm->iv,
	       माप(accel_attrs.keymat.aes_gcm.seq_iv));
	accel_attrs.keymat.aes_gcm.icv_len = aes_gcm->icv_len * 8;
	accel_attrs.keymat.aes_gcm.iv_algo = MLX5_ACCEL_ESP_AES_GCM_IV_ALGO_SEQ;
	accel_attrs.keymat_type = MLX5_ACCEL_ESP_KEYMAT_AES_GCM;

	accel_attrs.esn = attr->esn;
	अगर (attr->flags & IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED)
		accel_attrs.flags |= MLX5_ACCEL_ESP_FLAGS_ESN_TRIGGERED;
	अगर (attr->flags & IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW)
		accel_attrs.flags |= MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP;

	अगर (attr->flags & IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ENCRYPT)
		accel_attrs.action |= MLX5_ACCEL_ESP_ACTION_ENCRYPT;

	action->esp_aes_gcm.ctx =
		mlx5_accel_esp_create_xfrm(mdev->mdev, &accel_attrs, flags);
	अगर (IS_ERR(action->esp_aes_gcm.ctx)) अणु
		err = PTR_ERR(action->esp_aes_gcm.ctx);
		जाओ err_parse;
	पूर्ण

	action->esp_aes_gcm.ib_flags = attr->flags;

	वापस &action->ib_action;

err_parse:
	kमुक्त(action);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक
mlx5_ib_modअगरy_flow_action_esp(काष्ठा ib_flow_action *action,
			       स्थिर काष्ठा ib_flow_action_attrs_esp *attr,
			       काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_flow_action *maction = to_mflow_act(action);
	काष्ठा mlx5_accel_esp_xfrm_attrs accel_attrs;
	पूर्णांक err = 0;

	अगर (attr->keymat || attr->replay || attr->encap ||
	    attr->spi || attr->seq || attr->tfc_pad ||
	    attr->hard_limit_pkts ||
	    (attr->flags & ~(IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED |
			     IB_FLOW_ACTION_ESP_FLAGS_MOD_ESP_ATTRS |
			     IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW)))
		वापस -EOPNOTSUPP;

	/* Only the ESN value or the MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP can
	 * be modअगरied.
	 */
	अगर (!(maction->esp_aes_gcm.ib_flags &
	      IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED) &&
	    attr->flags & (IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED |
			   IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW))
		वापस -EINVAL;

	स_नकल(&accel_attrs, &maction->esp_aes_gcm.ctx->attrs,
	       माप(accel_attrs));

	accel_attrs.esn = attr->esn;
	अगर (attr->flags & IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW)
		accel_attrs.flags |= MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP;
	अन्यथा
		accel_attrs.flags &= ~MLX5_ACCEL_ESP_FLAGS_ESN_STATE_OVERLAP;

	err = mlx5_accel_esp_modअगरy_xfrm(maction->esp_aes_gcm.ctx,
					 &accel_attrs);
	अगर (err)
		वापस err;

	maction->esp_aes_gcm.ib_flags &=
		~IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW;
	maction->esp_aes_gcm.ib_flags |=
		attr->flags & IB_UVERBS_FLOW_ACTION_ESP_FLAGS_ESN_NEW_WINDOW;

	वापस 0;
पूर्ण

अटल व्योम destroy_flow_action_raw(काष्ठा mlx5_ib_flow_action *maction)
अणु
	चयन (maction->flow_action_raw.sub_type) अणु
	हाल MLX5_IB_FLOW_ACTION_MODIFY_HEADER:
		mlx5_modअगरy_header_dealloc(maction->flow_action_raw.dev->mdev,
					   maction->flow_action_raw.modअगरy_hdr);
		अवरोध;
	हाल MLX5_IB_FLOW_ACTION_PACKET_REFORMAT:
		mlx5_packet_reक्रमmat_dealloc(maction->flow_action_raw.dev->mdev,
					     maction->flow_action_raw.pkt_reक्रमmat);
		अवरोध;
	हाल MLX5_IB_FLOW_ACTION_DECAP:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_ib_destroy_flow_action(काष्ठा ib_flow_action *action)
अणु
	काष्ठा mlx5_ib_flow_action *maction = to_mflow_act(action);

	चयन (action->type) अणु
	हाल IB_FLOW_ACTION_ESP:
		/*
		 * We only support aes_gcm by now, so we implicitly know this is
		 * the underline crypto.
		 */
		mlx5_accel_esp_destroy_xfrm(maction->esp_aes_gcm.ctx);
		अवरोध;
	हाल IB_FLOW_ACTION_UNSPECIFIED:
		destroy_flow_action_raw(maction);
		अवरोध;
	शेष:
		WARN_ON(true);
		अवरोध;
	पूर्ण

	kमुक्त(maction);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_ib_ft_type_to_namespace(क्रमागत mlx5_ib_uapi_flow_table_type table_type,
			     क्रमागत mlx5_flow_namespace_type *namespace)
अणु
	चयन (table_type) अणु
	हाल MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_RX:
		*namespace = MLX5_FLOW_NAMESPACE_BYPASS;
		अवरोध;
	हाल MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_TX:
		*namespace = MLX5_FLOW_NAMESPACE_EGRESS;
		अवरोध;
	हाल MLX5_IB_UAPI_FLOW_TABLE_TYPE_FDB:
		*namespace = MLX5_FLOW_NAMESPACE_FDB;
		अवरोध;
	हाल MLX5_IB_UAPI_FLOW_TABLE_TYPE_RDMA_RX:
		*namespace = MLX5_FLOW_NAMESPACE_RDMA_RX;
		अवरोध;
	हाल MLX5_IB_UAPI_FLOW_TABLE_TYPE_RDMA_TX:
		*namespace = MLX5_FLOW_NAMESPACE_RDMA_TX;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा uverbs_attr_spec mlx5_ib_flow_type[] = अणु
	[MLX5_IB_FLOW_TYPE_NORMAL] = अणु
		.type = UVERBS_ATTR_TYPE_PTR_IN,
		.u.ptr = अणु
			.len = माप(u16), /* data is priority */
			.min_len = माप(u16),
		पूर्ण
	पूर्ण,
	[MLX5_IB_FLOW_TYPE_SNIFFER] = अणु
		.type = UVERBS_ATTR_TYPE_PTR_IN,
		UVERBS_ATTR_NO_DATA(),
	पूर्ण,
	[MLX5_IB_FLOW_TYPE_ALL_DEFAULT] = अणु
		.type = UVERBS_ATTR_TYPE_PTR_IN,
		UVERBS_ATTR_NO_DATA(),
	पूर्ण,
	[MLX5_IB_FLOW_TYPE_MC_DEFAULT] = अणु
		.type = UVERBS_ATTR_TYPE_PTR_IN,
		UVERBS_ATTR_NO_DATA(),
	पूर्ण,
पूर्ण;

अटल bool is_flow_dest(व्योम *obj, पूर्णांक *dest_id, पूर्णांक *dest_type)
अणु
	काष्ठा devx_obj *devx_obj = obj;
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, devx_obj->dinbox, opcode);

	चयन (opcode) अणु
	हाल MLX5_CMD_OP_DESTROY_TIR:
		*dest_type = MLX5_FLOW_DESTINATION_TYPE_TIR;
		*dest_id = MLX5_GET(general_obj_in_cmd_hdr, devx_obj->dinbox,
				    obj_id);
		वापस true;

	हाल MLX5_CMD_OP_DESTROY_FLOW_TABLE:
		*dest_type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
		*dest_id = MLX5_GET(destroy_flow_table_in, devx_obj->dinbox,
				    table_id);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक get_dests(काष्ठा uverbs_attr_bundle *attrs,
		     काष्ठा mlx5_ib_flow_matcher *fs_matcher, पूर्णांक *dest_id,
		     पूर्णांक *dest_type, काष्ठा ib_qp **qp, u32 *flags)
अणु
	bool dest_devx, dest_qp;
	व्योम *devx_obj;
	पूर्णांक err;

	dest_devx = uverbs_attr_is_valid(attrs,
					 MLX5_IB_ATTR_CREATE_FLOW_DEST_DEVX);
	dest_qp = uverbs_attr_is_valid(attrs,
				       MLX5_IB_ATTR_CREATE_FLOW_DEST_QP);

	*flags = 0;
	err = uverbs_get_flags32(flags, attrs, MLX5_IB_ATTR_CREATE_FLOW_FLAGS,
				 MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DEFAULT_MISS |
					 MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DROP);
	अगर (err)
		वापस err;

	/* Both flags are not allowed */
	अगर (*flags & MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DEFAULT_MISS &&
	    *flags & MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DROP)
		वापस -EINVAL;

	अगर (fs_matcher->ns_type == MLX5_FLOW_NAMESPACE_BYPASS) अणु
		अगर (dest_devx && (dest_qp || *flags))
			वापस -EINVAL;
		अन्यथा अगर (dest_qp && *flags)
			वापस -EINVAL;
	पूर्ण

	/* Allow only DEVX object, drop as dest क्रम FDB */
	अगर (fs_matcher->ns_type == MLX5_FLOW_NAMESPACE_FDB && !(dest_devx ||
	     (*flags & MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DROP)))
		वापस -EINVAL;

	/* Allow only DEVX object or QP as dest when inserting to RDMA_RX */
	अगर ((fs_matcher->ns_type == MLX5_FLOW_NAMESPACE_RDMA_RX) &&
	    ((!dest_devx && !dest_qp) || (dest_devx && dest_qp)))
		वापस -EINVAL;

	*qp = शून्य;
	अगर (dest_devx) अणु
		devx_obj =
			uverbs_attr_get_obj(attrs,
					    MLX5_IB_ATTR_CREATE_FLOW_DEST_DEVX);

		/* Verअगरy that the given DEVX object is a flow
		 * steering destination.
		 */
		अगर (!is_flow_dest(devx_obj, dest_id, dest_type))
			वापस -EINVAL;
		/* Allow only flow table as dest when inserting to FDB or RDMA_RX */
		अगर ((fs_matcher->ns_type == MLX5_FLOW_NAMESPACE_FDB ||
		     fs_matcher->ns_type == MLX5_FLOW_NAMESPACE_RDMA_RX) &&
		    *dest_type != MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (dest_qp) अणु
		काष्ठा mlx5_ib_qp *mqp;

		*qp = uverbs_attr_get_obj(attrs,
					  MLX5_IB_ATTR_CREATE_FLOW_DEST_QP);
		अगर (IS_ERR(*qp))
			वापस PTR_ERR(*qp);

		अगर ((*qp)->qp_type != IB_QPT_RAW_PACKET)
			वापस -EINVAL;

		mqp = to_mqp(*qp);
		अगर (mqp->is_rss)
			*dest_id = mqp->rss_qp.tirn;
		अन्यथा
			*dest_id = mqp->raw_packet_qp.rq.tirn;
		*dest_type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	पूर्ण अन्यथा अगर ((fs_matcher->ns_type == MLX5_FLOW_NAMESPACE_EGRESS ||
		    fs_matcher->ns_type == MLX5_FLOW_NAMESPACE_RDMA_TX) &&
		   !(*flags & MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DROP)) अणु
		*dest_type = MLX5_FLOW_DESTINATION_TYPE_PORT;
	पूर्ण

	अगर (*dest_type == MLX5_FLOW_DESTINATION_TYPE_TIR &&
	    (fs_matcher->ns_type == MLX5_FLOW_NAMESPACE_EGRESS ||
	     fs_matcher->ns_type == MLX5_FLOW_NAMESPACE_RDMA_TX))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल bool is_flow_counter(व्योम *obj, u32 offset, u32 *counter_id)
अणु
	काष्ठा devx_obj *devx_obj = obj;
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, devx_obj->dinbox, opcode);

	अगर (opcode == MLX5_CMD_OP_DEALLOC_FLOW_COUNTER) अणु

		अगर (offset && offset >= devx_obj->flow_counter_bulk_size)
			वापस false;

		*counter_id = MLX5_GET(dealloc_flow_counter_in,
				       devx_obj->dinbox,
				       flow_counter_id);
		*counter_id += offset;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#घोषणा MLX5_IB_CREATE_FLOW_MAX_FLOW_ACTIONS 2
अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_CREATE_FLOW)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_flow_context flow_context = अणु.flow_tag =
		MLX5_FS_DEFAULT_FLOW_TAGपूर्ण;
	u32 *offset_attr, offset = 0, counter_id = 0;
	पूर्णांक dest_id, dest_type = -1, inlen, len, ret, i;
	काष्ठा mlx5_ib_flow_handler *flow_handler;
	काष्ठा mlx5_ib_flow_matcher *fs_matcher;
	काष्ठा ib_uobject **arr_flow_actions;
	काष्ठा ib_uflow_resources *uflow_res;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा ib_qp *qp = शून्य;
	व्योम *devx_obj, *cmd_in;
	काष्ठा ib_uobject *uobj;
	काष्ठा mlx5_ib_dev *dev;
	u32 flags;

	अगर (!capable(CAP_NET_RAW))
		वापस -EPERM;

	fs_matcher = uverbs_attr_get_obj(attrs,
					 MLX5_IB_ATTR_CREATE_FLOW_MATCHER);
	uobj =  uverbs_attr_get_uobject(attrs, MLX5_IB_ATTR_CREATE_FLOW_HANDLE);
	dev = mlx5_udata_to_mdev(&attrs->driver_udata);

	अगर (get_dests(attrs, fs_matcher, &dest_id, &dest_type, &qp, &flags))
		वापस -EINVAL;

	अगर (flags & MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DEFAULT_MISS)
		flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_NS;

	अगर (flags & MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DROP)
		flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_DROP;

	len = uverbs_attr_get_uobjs_arr(attrs,
		MLX5_IB_ATTR_CREATE_FLOW_ARR_COUNTERS_DEVX, &arr_flow_actions);
	अगर (len) अणु
		devx_obj = arr_flow_actions[0]->object;

		अगर (uverbs_attr_is_valid(attrs,
					 MLX5_IB_ATTR_CREATE_FLOW_ARR_COUNTERS_DEVX_OFFSET)) अणु

			पूर्णांक num_offsets = uverbs_attr_ptr_get_array_size(
				attrs,
				MLX5_IB_ATTR_CREATE_FLOW_ARR_COUNTERS_DEVX_OFFSET,
				माप(u32));

			अगर (num_offsets != 1)
				वापस -EINVAL;

			offset_attr = uverbs_attr_get_alloced_ptr(
				attrs,
				MLX5_IB_ATTR_CREATE_FLOW_ARR_COUNTERS_DEVX_OFFSET);
			offset = *offset_attr;
		पूर्ण

		अगर (!is_flow_counter(devx_obj, offset, &counter_id))
			वापस -EINVAL;

		flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_COUNT;
	पूर्ण

	cmd_in = uverbs_attr_get_alloced_ptr(
		attrs, MLX5_IB_ATTR_CREATE_FLOW_MATCH_VALUE);
	inlen = uverbs_attr_get_len(attrs,
				    MLX5_IB_ATTR_CREATE_FLOW_MATCH_VALUE);

	uflow_res = flow_resources_alloc(MLX5_IB_CREATE_FLOW_MAX_FLOW_ACTIONS);
	अगर (!uflow_res)
		वापस -ENOMEM;

	len = uverbs_attr_get_uobjs_arr(attrs,
		MLX5_IB_ATTR_CREATE_FLOW_ARR_FLOW_ACTIONS, &arr_flow_actions);
	क्रम (i = 0; i < len; i++) अणु
		काष्ठा mlx5_ib_flow_action *maction =
			to_mflow_act(arr_flow_actions[i]->object);

		ret = parse_flow_flow_action(maction, false, &flow_act);
		अगर (ret)
			जाओ err_out;
		flow_resources_add(uflow_res, IB_FLOW_SPEC_ACTION_HANDLE,
				   arr_flow_actions[i]->object);
	पूर्ण

	ret = uverbs_copy_from(&flow_context.flow_tag, attrs,
			       MLX5_IB_ATTR_CREATE_FLOW_TAG);
	अगर (!ret) अणु
		अगर (flow_context.flow_tag >= BIT(24)) अणु
			ret = -EINVAL;
			जाओ err_out;
		पूर्ण
		flow_context.flags |= FLOW_CONTEXT_HAS_TAG;
	पूर्ण

	flow_handler =
		raw_fs_rule_add(dev, fs_matcher, &flow_context, &flow_act,
				counter_id, cmd_in, inlen, dest_id, dest_type);
	अगर (IS_ERR(flow_handler)) अणु
		ret = PTR_ERR(flow_handler);
		जाओ err_out;
	पूर्ण

	ib_set_flow(uobj, &flow_handler->ibflow, qp, &dev->ib_dev, uflow_res);

	वापस 0;
err_out:
	ib_uverbs_flow_resources_मुक्त(uflow_res);
	वापस ret;
पूर्ण

अटल पूर्णांक flow_matcher_cleanup(काष्ठा ib_uobject *uobject,
				क्रमागत rdma_हटाओ_reason why,
				काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा mlx5_ib_flow_matcher *obj = uobject->object;

	अगर (atomic_पढ़ो(&obj->usecnt))
		वापस -EBUSY;

	kमुक्त(obj);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_matcher_ns(काष्ठा uverbs_attr_bundle *attrs,
			      काष्ठा mlx5_ib_flow_matcher *obj)
अणु
	क्रमागत mlx5_ib_uapi_flow_table_type ft_type =
		MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_RX;
	u32 flags;
	पूर्णांक err;

	/* New users should use MLX5_IB_ATTR_FLOW_MATCHER_FT_TYPE and older
	 * users should चयन to it. We leave this to not अवरोध userspace
	 */
	अगर (uverbs_attr_is_valid(attrs, MLX5_IB_ATTR_FLOW_MATCHER_FT_TYPE) &&
	    uverbs_attr_is_valid(attrs, MLX5_IB_ATTR_FLOW_MATCHER_FLOW_FLAGS))
		वापस -EINVAL;

	अगर (uverbs_attr_is_valid(attrs, MLX5_IB_ATTR_FLOW_MATCHER_FT_TYPE)) अणु
		err = uverbs_get_स्थिर(&ft_type, attrs,
				       MLX5_IB_ATTR_FLOW_MATCHER_FT_TYPE);
		अगर (err)
			वापस err;

		err = mlx5_ib_ft_type_to_namespace(ft_type, &obj->ns_type);
		अगर (err)
			वापस err;

		वापस 0;
	पूर्ण

	अगर (uverbs_attr_is_valid(attrs, MLX5_IB_ATTR_FLOW_MATCHER_FLOW_FLAGS)) अणु
		err = uverbs_get_flags32(&flags, attrs,
					 MLX5_IB_ATTR_FLOW_MATCHER_FLOW_FLAGS,
					 IB_FLOW_ATTR_FLAGS_EGRESS);
		अगर (err)
			वापस err;

		अगर (flags) अणु
			mlx5_ib_ft_type_to_namespace(
				MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_TX,
				&obj->ns_type);
			वापस 0;
		पूर्ण
	पूर्ण

	obj->ns_type = MLX5_FLOW_NAMESPACE_BYPASS;

	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_FLOW_MATCHER_CREATE)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, MLX5_IB_ATTR_FLOW_MATCHER_CREATE_HANDLE);
	काष्ठा mlx5_ib_dev *dev = mlx5_udata_to_mdev(&attrs->driver_udata);
	काष्ठा mlx5_ib_flow_matcher *obj;
	पूर्णांक err;

	obj = kzalloc(माप(काष्ठा mlx5_ib_flow_matcher), GFP_KERNEL);
	अगर (!obj)
		वापस -ENOMEM;

	obj->mask_len = uverbs_attr_get_len(
		attrs, MLX5_IB_ATTR_FLOW_MATCHER_MATCH_MASK);
	err = uverbs_copy_from(&obj->matcher_mask,
			       attrs,
			       MLX5_IB_ATTR_FLOW_MATCHER_MATCH_MASK);
	अगर (err)
		जाओ end;

	obj->flow_type = uverbs_attr_get_क्रमागत_id(
		attrs, MLX5_IB_ATTR_FLOW_MATCHER_FLOW_TYPE);

	अगर (obj->flow_type == MLX5_IB_FLOW_TYPE_NORMAL) अणु
		err = uverbs_copy_from(&obj->priority,
				       attrs,
				       MLX5_IB_ATTR_FLOW_MATCHER_FLOW_TYPE);
		अगर (err)
			जाओ end;
	पूर्ण

	err = uverbs_copy_from(&obj->match_criteria_enable,
			       attrs,
			       MLX5_IB_ATTR_FLOW_MATCHER_MATCH_CRITERIA);
	अगर (err)
		जाओ end;

	err = mlx5_ib_matcher_ns(attrs, obj);
	अगर (err)
		जाओ end;

	अगर (obj->ns_type == MLX5_FLOW_NAMESPACE_FDB &&
	    mlx5_eचयन_mode(dev->mdev) != MLX5_ESWITCH_OFFLOADS) अणु
		err = -EINVAL;
		जाओ end;
	पूर्ण

	uobj->object = obj;
	obj->mdev = dev->mdev;
	atomic_set(&obj->usecnt, 0);
	वापस 0;

end:
	kमुक्त(obj);
	वापस err;
पूर्ण

अटल काष्ठा ib_flow_action *
mlx5_ib_create_modअगरy_header(काष्ठा mlx5_ib_dev *dev,
			     क्रमागत mlx5_ib_uapi_flow_table_type ft_type,
			     u8 num_actions, व्योम *in)
अणु
	क्रमागत mlx5_flow_namespace_type namespace;
	काष्ठा mlx5_ib_flow_action *maction;
	पूर्णांक ret;

	ret = mlx5_ib_ft_type_to_namespace(ft_type, &namespace);
	अगर (ret)
		वापस ERR_PTR(-EINVAL);

	maction = kzalloc(माप(*maction), GFP_KERNEL);
	अगर (!maction)
		वापस ERR_PTR(-ENOMEM);

	maction->flow_action_raw.modअगरy_hdr =
		mlx5_modअगरy_header_alloc(dev->mdev, namespace, num_actions, in);

	अगर (IS_ERR(maction->flow_action_raw.modअगरy_hdr)) अणु
		ret = PTR_ERR(maction->flow_action_raw.modअगरy_hdr);
		kमुक्त(maction);
		वापस ERR_PTR(ret);
	पूर्ण
	maction->flow_action_raw.sub_type =
		MLX5_IB_FLOW_ACTION_MODIFY_HEADER;
	maction->flow_action_raw.dev = dev;

	वापस &maction->ib_action;
पूर्ण

अटल bool mlx5_ib_modअगरy_header_supported(काष्ठा mlx5_ib_dev *dev)
अणु
	वापस MLX5_CAP_FLOWTABLE_NIC_RX(dev->mdev,
					 max_modअगरy_header_actions) ||
	       MLX5_CAP_FLOWTABLE_NIC_TX(dev->mdev,
					 max_modअगरy_header_actions) ||
	       MLX5_CAP_FLOWTABLE_RDMA_TX(dev->mdev,
					 max_modअगरy_header_actions);
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_FLOW_ACTION_CREATE_MODIFY_HEADER)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(
		attrs, MLX5_IB_ATTR_CREATE_MODIFY_HEADER_HANDLE);
	काष्ठा mlx5_ib_dev *mdev = mlx5_udata_to_mdev(&attrs->driver_udata);
	क्रमागत mlx5_ib_uapi_flow_table_type ft_type;
	काष्ठा ib_flow_action *action;
	पूर्णांक num_actions;
	व्योम *in;
	पूर्णांक ret;

	अगर (!mlx5_ib_modअगरy_header_supported(mdev))
		वापस -EOPNOTSUPP;

	in = uverbs_attr_get_alloced_ptr(attrs,
		MLX5_IB_ATTR_CREATE_MODIFY_HEADER_ACTIONS_PRM);

	num_actions = uverbs_attr_ptr_get_array_size(
		attrs, MLX5_IB_ATTR_CREATE_MODIFY_HEADER_ACTIONS_PRM,
		MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः));
	अगर (num_actions < 0)
		वापस num_actions;

	ret = uverbs_get_स्थिर(&ft_type, attrs,
			       MLX5_IB_ATTR_CREATE_MODIFY_HEADER_FT_TYPE);
	अगर (ret)
		वापस ret;
	action = mlx5_ib_create_modअगरy_header(mdev, ft_type, num_actions, in);
	अगर (IS_ERR(action))
		वापस PTR_ERR(action);

	uverbs_flow_action_fill_action(action, uobj, &mdev->ib_dev,
				       IB_FLOW_ACTION_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल bool mlx5_ib_flow_action_packet_reक्रमmat_valid(काष्ठा mlx5_ib_dev *ibdev,
						      u8 packet_reक्रमmat_type,
						      u8 ft_type)
अणु
	चयन (packet_reक्रमmat_type) अणु
	हाल MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L2_TUNNEL:
		अगर (ft_type == MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_TX)
			वापस MLX5_CAP_FLOWTABLE(ibdev->mdev,
						  encap_general_header);
		अवरोध;
	हाल MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L3_TUNNEL:
		अगर (ft_type == MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_TX)
			वापस MLX5_CAP_FLOWTABLE_NIC_TX(ibdev->mdev,
				reक्रमmat_l2_to_l3_tunnel);
		अवरोध;
	हाल MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L3_TUNNEL_TO_L2:
		अगर (ft_type == MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_RX)
			वापस MLX5_CAP_FLOWTABLE_NIC_RX(ibdev->mdev,
				reक्रमmat_l3_tunnel_to_l2);
		अवरोध;
	हाल MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TUNNEL_TO_L2:
		अगर (ft_type == MLX5_IB_UAPI_FLOW_TABLE_TYPE_NIC_RX)
			वापस MLX5_CAP_FLOWTABLE_NIC_RX(ibdev->mdev, decap);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक mlx5_ib_dv_to_prm_packet_reक्रमamt_type(u8 dv_prt, u8 *prm_prt)
अणु
	चयन (dv_prt) अणु
	हाल MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L2_TUNNEL:
		*prm_prt = MLX5_REFORMAT_TYPE_L2_TO_L2_TUNNEL;
		अवरोध;
	हाल MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L3_TUNNEL_TO_L2:
		*prm_prt = MLX5_REFORMAT_TYPE_L3_TUNNEL_TO_L2;
		अवरोध;
	हाल MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TO_L3_TUNNEL:
		*prm_prt = MLX5_REFORMAT_TYPE_L2_TO_L3_TUNNEL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlx5_ib_flow_action_create_packet_reक्रमmat_ctx(
	काष्ठा mlx5_ib_dev *dev,
	काष्ठा mlx5_ib_flow_action *maction,
	u8 ft_type, u8 dv_prt,
	व्योम *in, माप_प्रकार len)
अणु
	क्रमागत mlx5_flow_namespace_type namespace;
	u8 prm_prt;
	पूर्णांक ret;

	ret = mlx5_ib_ft_type_to_namespace(ft_type, &namespace);
	अगर (ret)
		वापस ret;

	ret = mlx5_ib_dv_to_prm_packet_reक्रमamt_type(dv_prt, &prm_prt);
	अगर (ret)
		वापस ret;

	maction->flow_action_raw.pkt_reक्रमmat =
		mlx5_packet_reक्रमmat_alloc(dev->mdev, prm_prt, len,
					   in, namespace);
	अगर (IS_ERR(maction->flow_action_raw.pkt_reक्रमmat)) अणु
		ret = PTR_ERR(maction->flow_action_raw.pkt_reक्रमmat);
		वापस ret;
	पूर्ण

	maction->flow_action_raw.sub_type =
		MLX5_IB_FLOW_ACTION_PACKET_REFORMAT;
	maction->flow_action_raw.dev = dev;

	वापस 0;
पूर्ण

अटल पूर्णांक UVERBS_HANDLER(MLX5_IB_METHOD_FLOW_ACTION_CREATE_PACKET_REFORMAT)(
	काष्ठा uverbs_attr_bundle *attrs)
अणु
	काष्ठा ib_uobject *uobj = uverbs_attr_get_uobject(attrs,
		MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_HANDLE);
	काष्ठा mlx5_ib_dev *mdev = mlx5_udata_to_mdev(&attrs->driver_udata);
	क्रमागत mlx5_ib_uapi_flow_action_packet_reक्रमmat_type dv_prt;
	क्रमागत mlx5_ib_uapi_flow_table_type ft_type;
	काष्ठा mlx5_ib_flow_action *maction;
	पूर्णांक ret;

	ret = uverbs_get_स्थिर(&ft_type, attrs,
			       MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_FT_TYPE);
	अगर (ret)
		वापस ret;

	ret = uverbs_get_स्थिर(&dv_prt, attrs,
			       MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_TYPE);
	अगर (ret)
		वापस ret;

	अगर (!mlx5_ib_flow_action_packet_reक्रमmat_valid(mdev, dv_prt, ft_type))
		वापस -EOPNOTSUPP;

	maction = kzalloc(माप(*maction), GFP_KERNEL);
	अगर (!maction)
		वापस -ENOMEM;

	अगर (dv_prt ==
	    MLX5_IB_UAPI_FLOW_ACTION_PACKET_REFORMAT_TYPE_L2_TUNNEL_TO_L2) अणु
		maction->flow_action_raw.sub_type =
			MLX5_IB_FLOW_ACTION_DECAP;
		maction->flow_action_raw.dev = mdev;
	पूर्ण अन्यथा अणु
		व्योम *in;
		पूर्णांक len;

		in = uverbs_attr_get_alloced_ptr(attrs,
			MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_DATA_BUF);
		अगर (IS_ERR(in)) अणु
			ret = PTR_ERR(in);
			जाओ मुक्त_maction;
		पूर्ण

		len = uverbs_attr_get_len(attrs,
			MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_DATA_BUF);

		ret = mlx5_ib_flow_action_create_packet_reक्रमmat_ctx(mdev,
			maction, ft_type, dv_prt, in, len);
		अगर (ret)
			जाओ मुक्त_maction;
	पूर्ण

	uverbs_flow_action_fill_action(&maction->ib_action, uobj, &mdev->ib_dev,
				       IB_FLOW_ACTION_UNSPECIFIED);
	वापस 0;

मुक्त_maction:
	kमुक्त(maction);
	वापस ret;
पूर्ण

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_CREATE_FLOW,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_CREATE_FLOW_HANDLE,
			UVERBS_OBJECT_FLOW,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(
		MLX5_IB_ATTR_CREATE_FLOW_MATCH_VALUE,
		UVERBS_ATTR_SIZE(1, माप(काष्ठा mlx5_ib_match_params)),
		UA_MANDATORY,
		UA_ALLOC_AND_COPY),
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_CREATE_FLOW_MATCHER,
			MLX5_IB_OBJECT_FLOW_MATCHER,
			UVERBS_ACCESS_READ,
			UA_MANDATORY),
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_CREATE_FLOW_DEST_QP,
			UVERBS_OBJECT_QP,
			UVERBS_ACCESS_READ),
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_CREATE_FLOW_DEST_DEVX,
			MLX5_IB_OBJECT_DEVX_OBJ,
			UVERBS_ACCESS_READ),
	UVERBS_ATTR_IDRS_ARR(MLX5_IB_ATTR_CREATE_FLOW_ARR_FLOW_ACTIONS,
			     UVERBS_OBJECT_FLOW_ACTION,
			     UVERBS_ACCESS_READ, 1,
			     MLX5_IB_CREATE_FLOW_MAX_FLOW_ACTIONS,
			     UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_CREATE_FLOW_TAG,
			   UVERBS_ATTR_TYPE(u32),
			   UA_OPTIONAL),
	UVERBS_ATTR_IDRS_ARR(MLX5_IB_ATTR_CREATE_FLOW_ARR_COUNTERS_DEVX,
			     MLX5_IB_OBJECT_DEVX_OBJ,
			     UVERBS_ACCESS_READ, 1, 1,
			     UA_OPTIONAL),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_CREATE_FLOW_ARR_COUNTERS_DEVX_OFFSET,
			   UVERBS_ATTR_MIN_SIZE(माप(u32)),
			   UA_OPTIONAL,
			   UA_ALLOC_AND_COPY),
	UVERBS_ATTR_FLAGS_IN(MLX5_IB_ATTR_CREATE_FLOW_FLAGS,
			     क्रमागत mlx5_ib_create_flow_flags,
			     UA_OPTIONAL));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	MLX5_IB_METHOD_DESTROY_FLOW,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_CREATE_FLOW_HANDLE,
			UVERBS_OBJECT_FLOW,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

ADD_UVERBS_METHODS(mlx5_ib_fs,
		   UVERBS_OBJECT_FLOW,
		   &UVERBS_METHOD(MLX5_IB_METHOD_CREATE_FLOW),
		   &UVERBS_METHOD(MLX5_IB_METHOD_DESTROY_FLOW));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_FLOW_ACTION_CREATE_MODIFY_HEADER,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_CREATE_MODIFY_HEADER_HANDLE,
			UVERBS_OBJECT_FLOW_ACTION,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_CREATE_MODIFY_HEADER_ACTIONS_PRM,
			   UVERBS_ATTR_MIN_SIZE(MLX5_UN_SZ_BYTES(
				   set_add_copy_action_in_स्वतः)),
			   UA_MANDATORY,
			   UA_ALLOC_AND_COPY),
	UVERBS_ATTR_CONST_IN(MLX5_IB_ATTR_CREATE_MODIFY_HEADER_FT_TYPE,
			     क्रमागत mlx5_ib_uapi_flow_table_type,
			     UA_MANDATORY));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_FLOW_ACTION_CREATE_PACKET_REFORMAT,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_HANDLE,
			UVERBS_OBJECT_FLOW_ACTION,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_DATA_BUF,
			   UVERBS_ATTR_MIN_SIZE(1),
			   UA_ALLOC_AND_COPY,
			   UA_OPTIONAL),
	UVERBS_ATTR_CONST_IN(MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_TYPE,
			     क्रमागत mlx5_ib_uapi_flow_action_packet_reक्रमmat_type,
			     UA_MANDATORY),
	UVERBS_ATTR_CONST_IN(MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_FT_TYPE,
			     क्रमागत mlx5_ib_uapi_flow_table_type,
			     UA_MANDATORY));

ADD_UVERBS_METHODS(
	mlx5_ib_flow_actions,
	UVERBS_OBJECT_FLOW_ACTION,
	&UVERBS_METHOD(MLX5_IB_METHOD_FLOW_ACTION_CREATE_MODIFY_HEADER),
	&UVERBS_METHOD(MLX5_IB_METHOD_FLOW_ACTION_CREATE_PACKET_REFORMAT));

DECLARE_UVERBS_NAMED_METHOD(
	MLX5_IB_METHOD_FLOW_MATCHER_CREATE,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_FLOW_MATCHER_CREATE_HANDLE,
			MLX5_IB_OBJECT_FLOW_MATCHER,
			UVERBS_ACCESS_NEW,
			UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(
		MLX5_IB_ATTR_FLOW_MATCHER_MATCH_MASK,
		UVERBS_ATTR_SIZE(1, माप(काष्ठा mlx5_ib_match_params)),
		UA_MANDATORY),
	UVERBS_ATTR_ENUM_IN(MLX5_IB_ATTR_FLOW_MATCHER_FLOW_TYPE,
			    mlx5_ib_flow_type,
			    UA_MANDATORY),
	UVERBS_ATTR_PTR_IN(MLX5_IB_ATTR_FLOW_MATCHER_MATCH_CRITERIA,
			   UVERBS_ATTR_TYPE(u8),
			   UA_MANDATORY),
	UVERBS_ATTR_FLAGS_IN(MLX5_IB_ATTR_FLOW_MATCHER_FLOW_FLAGS,
			     क्रमागत ib_flow_flags,
			     UA_OPTIONAL),
	UVERBS_ATTR_CONST_IN(MLX5_IB_ATTR_FLOW_MATCHER_FT_TYPE,
			     क्रमागत mlx5_ib_uapi_flow_table_type,
			     UA_OPTIONAL));

DECLARE_UVERBS_NAMED_METHOD_DESTROY(
	MLX5_IB_METHOD_FLOW_MATCHER_DESTROY,
	UVERBS_ATTR_IDR(MLX5_IB_ATTR_FLOW_MATCHER_DESTROY_HANDLE,
			MLX5_IB_OBJECT_FLOW_MATCHER,
			UVERBS_ACCESS_DESTROY,
			UA_MANDATORY));

DECLARE_UVERBS_NAMED_OBJECT(MLX5_IB_OBJECT_FLOW_MATCHER,
			    UVERBS_TYPE_ALLOC_IDR(flow_matcher_cleanup),
			    &UVERBS_METHOD(MLX5_IB_METHOD_FLOW_MATCHER_CREATE),
			    &UVERBS_METHOD(MLX5_IB_METHOD_FLOW_MATCHER_DESTROY));

स्थिर काष्ठा uapi_definition mlx5_ib_flow_defs[] = अणु
	UAPI_DEF_CHAIN_OBJ_TREE_NAMED(
		MLX5_IB_OBJECT_FLOW_MATCHER),
	UAPI_DEF_CHAIN_OBJ_TREE(
		UVERBS_OBJECT_FLOW,
		&mlx5_ib_fs),
	UAPI_DEF_CHAIN_OBJ_TREE(UVERBS_OBJECT_FLOW_ACTION,
				&mlx5_ib_flow_actions),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops flow_ops = अणु
	.create_flow = mlx5_ib_create_flow,
	.destroy_flow = mlx5_ib_destroy_flow,
	.destroy_flow_action = mlx5_ib_destroy_flow_action,
पूर्ण;

अटल स्थिर काष्ठा ib_device_ops flow_ipsec_ops = अणु
	.create_flow_action_esp = mlx5_ib_create_flow_action_esp,
	.modअगरy_flow_action_esp = mlx5_ib_modअगरy_flow_action_esp,
पूर्ण;

पूर्णांक mlx5_ib_fs_init(काष्ठा mlx5_ib_dev *dev)
अणु
	dev->flow_db = kzalloc(माप(*dev->flow_db), GFP_KERNEL);

	अगर (!dev->flow_db)
		वापस -ENOMEM;

	mutex_init(&dev->flow_db->lock);

	ib_set_device_ops(&dev->ib_dev, &flow_ops);
	अगर (mlx5_accel_ipsec_device_caps(dev->mdev) &
	    MLX5_ACCEL_IPSEC_CAP_DEVICE)
		ib_set_device_ops(&dev->ib_dev, &flow_ipsec_ops);

	वापस 0;
पूर्ण
