<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "dr_types.h"

अटल bool dr_mask_is_smac_set(काष्ठा mlx5dr_match_spec *spec)
अणु
	वापस (spec->smac_47_16 || spec->smac_15_0);
पूर्ण

अटल bool dr_mask_is_dmac_set(काष्ठा mlx5dr_match_spec *spec)
अणु
	वापस (spec->dmac_47_16 || spec->dmac_15_0);
पूर्ण

अटल bool dr_mask_is_src_addr_set(काष्ठा mlx5dr_match_spec *spec)
अणु
	वापस (spec->src_ip_127_96 || spec->src_ip_95_64 ||
		spec->src_ip_63_32 || spec->src_ip_31_0);
पूर्ण

अटल bool dr_mask_is_dst_addr_set(काष्ठा mlx5dr_match_spec *spec)
अणु
	वापस (spec->dst_ip_127_96 || spec->dst_ip_95_64 ||
		spec->dst_ip_63_32 || spec->dst_ip_31_0);
पूर्ण

अटल bool dr_mask_is_l3_base_set(काष्ठा mlx5dr_match_spec *spec)
अणु
	वापस (spec->ip_protocol || spec->frag || spec->tcp_flags ||
		spec->ip_ecn || spec->ip_dscp);
पूर्ण

अटल bool dr_mask_is_tcp_udp_base_set(काष्ठा mlx5dr_match_spec *spec)
अणु
	वापस (spec->tcp_sport || spec->tcp_dport ||
		spec->udp_sport || spec->udp_dport);
पूर्ण

अटल bool dr_mask_is_ipv4_set(काष्ठा mlx5dr_match_spec *spec)
अणु
	वापस (spec->dst_ip_31_0 || spec->src_ip_31_0);
पूर्ण

अटल bool dr_mask_is_ipv4_5_tuple_set(काष्ठा mlx5dr_match_spec *spec)
अणु
	वापस (dr_mask_is_l3_base_set(spec) ||
		dr_mask_is_tcp_udp_base_set(spec) ||
		dr_mask_is_ipv4_set(spec));
पूर्ण

अटल bool dr_mask_is_eth_l2_tnl_set(काष्ठा mlx5dr_match_misc *misc)
अणु
	वापस misc->vxlan_vni;
पूर्ण

अटल bool dr_mask_is_ttl_set(काष्ठा mlx5dr_match_spec *spec)
अणु
	वापस spec->ttl_hoplimit;
पूर्ण

#घोषणा DR_MASK_IS_L2_DST(_spec, _misc, _inner_outer) (_spec.first_vid || \
	(_spec).first_cfi || (_spec).first_prio || (_spec).cvlan_tag || \
	(_spec).svlan_tag || (_spec).dmac_47_16 || (_spec).dmac_15_0 || \
	(_spec).ethertype || (_spec).ip_version || \
	(_misc)._inner_outer##_second_vid || \
	(_misc)._inner_outer##_second_cfi || \
	(_misc)._inner_outer##_second_prio || \
	(_misc)._inner_outer##_second_cvlan_tag || \
	(_misc)._inner_outer##_second_svlan_tag)

#घोषणा DR_MASK_IS_ETH_L4_SET(_spec, _misc, _inner_outer) ( \
	dr_mask_is_l3_base_set(&(_spec)) || \
	dr_mask_is_tcp_udp_base_set(&(_spec)) || \
	dr_mask_is_ttl_set(&(_spec)) || \
	(_misc)._inner_outer##_ipv6_flow_label)

#घोषणा DR_MASK_IS_ETH_L4_MISC_SET(_misc3, _inner_outer) ( \
	(_misc3)._inner_outer##_tcp_seq_num || \
	(_misc3)._inner_outer##_tcp_ack_num)

#घोषणा DR_MASK_IS_FIRST_MPLS_SET(_misc2, _inner_outer) ( \
	(_misc2)._inner_outer##_first_mpls_label || \
	(_misc2)._inner_outer##_first_mpls_exp || \
	(_misc2)._inner_outer##_first_mpls_s_bos || \
	(_misc2)._inner_outer##_first_mpls_ttl)

अटल bool dr_mask_is_tnl_gre_set(काष्ठा mlx5dr_match_misc *misc)
अणु
	वापस (misc->gre_key_h || misc->gre_key_l ||
		misc->gre_protocol || misc->gre_c_present ||
		misc->gre_k_present || misc->gre_s_present);
पूर्ण

#घोषणा DR_MASK_IS_OUTER_MPLS_OVER_GRE_SET(_misc) (\
	(_misc)->outer_first_mpls_over_gre_label || \
	(_misc)->outer_first_mpls_over_gre_exp || \
	(_misc)->outer_first_mpls_over_gre_s_bos || \
	(_misc)->outer_first_mpls_over_gre_ttl)

#घोषणा DR_MASK_IS_OUTER_MPLS_OVER_UDP_SET(_misc) (\
	(_misc)->outer_first_mpls_over_udp_label || \
	(_misc)->outer_first_mpls_over_udp_exp || \
	(_misc)->outer_first_mpls_over_udp_s_bos || \
	(_misc)->outer_first_mpls_over_udp_ttl)

अटल bool
dr_mask_is_vxlan_gpe_set(काष्ठा mlx5dr_match_misc3 *misc3)
अणु
	वापस (misc3->outer_vxlan_gpe_vni ||
		misc3->outer_vxlan_gpe_next_protocol ||
		misc3->outer_vxlan_gpe_flags);
पूर्ण

अटल bool
dr_matcher_supp_vxlan_gpe(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस (caps->sw_क्रमmat_ver == MLX5_STEERING_FORMAT_CONNECTX_6DX) ||
	       (caps->flex_protocols & MLX5_FLEX_PARSER_VXLAN_GPE_ENABLED);
पूर्ण

अटल bool
dr_mask_is_tnl_vxlan_gpe(काष्ठा mlx5dr_match_param *mask,
			 काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस dr_mask_is_vxlan_gpe_set(&mask->misc3) &&
	       dr_matcher_supp_vxlan_gpe(&dmn->info.caps);
पूर्ण

अटल bool dr_mask_is_tnl_geneve_set(काष्ठा mlx5dr_match_misc *misc)
अणु
	वापस misc->geneve_vni ||
	       misc->geneve_oam ||
	       misc->geneve_protocol_type ||
	       misc->geneve_opt_len;
पूर्ण

अटल bool dr_mask_is_tnl_geneve_tlv_opt(काष्ठा mlx5dr_match_misc3 *misc3)
अणु
	वापस misc3->geneve_tlv_option_0_data;
पूर्ण

अटल bool
dr_matcher_supp_tnl_geneve(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस (caps->sw_क्रमmat_ver == MLX5_STEERING_FORMAT_CONNECTX_6DX) ||
	       (caps->flex_protocols & MLX5_FLEX_PARSER_GENEVE_ENABLED);
पूर्ण

अटल bool
dr_mask_is_tnl_geneve(काष्ठा mlx5dr_match_param *mask,
		      काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस dr_mask_is_tnl_geneve_set(&mask->misc) &&
	       dr_matcher_supp_tnl_geneve(&dmn->info.caps);
पूर्ण

अटल bool dr_mask_is_tnl_gtpu_set(काष्ठा mlx5dr_match_misc3 *misc3)
अणु
	वापस misc3->gtpu_msg_flags || misc3->gtpu_msg_type || misc3->gtpu_teid;
पूर्ण

अटल bool dr_matcher_supp_tnl_gtpu(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस caps->flex_protocols & MLX5_FLEX_PARSER_GTPU_ENABLED;
पूर्ण

अटल bool dr_mask_is_tnl_gtpu(काष्ठा mlx5dr_match_param *mask,
				काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस dr_mask_is_tnl_gtpu_set(&mask->misc3) &&
	       dr_matcher_supp_tnl_gtpu(&dmn->info.caps);
पूर्ण

अटल पूर्णांक dr_matcher_supp_tnl_gtpu_dw_0(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस caps->flex_protocols & MLX5_FLEX_PARSER_GTPU_DW_0_ENABLED;
पूर्ण

अटल bool dr_mask_is_tnl_gtpu_dw_0(काष्ठा mlx5dr_match_param *mask,
				     काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस mask->misc3.gtpu_dw_0 &&
	       dr_matcher_supp_tnl_gtpu_dw_0(&dmn->info.caps);
पूर्ण

अटल पूर्णांक dr_matcher_supp_tnl_gtpu_teid(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस caps->flex_protocols & MLX5_FLEX_PARSER_GTPU_TEID_ENABLED;
पूर्ण

अटल bool dr_mask_is_tnl_gtpu_teid(काष्ठा mlx5dr_match_param *mask,
				     काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस mask->misc3.gtpu_teid &&
	       dr_matcher_supp_tnl_gtpu_teid(&dmn->info.caps);
पूर्ण

अटल पूर्णांक dr_matcher_supp_tnl_gtpu_dw_2(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस caps->flex_protocols & MLX5_FLEX_PARSER_GTPU_DW_2_ENABLED;
पूर्ण

अटल bool dr_mask_is_tnl_gtpu_dw_2(काष्ठा mlx5dr_match_param *mask,
				     काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस mask->misc3.gtpu_dw_2 &&
	       dr_matcher_supp_tnl_gtpu_dw_2(&dmn->info.caps);
पूर्ण

अटल पूर्णांक dr_matcher_supp_tnl_gtpu_first_ext(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस caps->flex_protocols & MLX5_FLEX_PARSER_GTPU_FIRST_EXT_DW_0_ENABLED;
पूर्ण

अटल bool dr_mask_is_tnl_gtpu_first_ext(काष्ठा mlx5dr_match_param *mask,
					  काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस mask->misc3.gtpu_first_ext_dw_0 &&
	       dr_matcher_supp_tnl_gtpu_first_ext(&dmn->info.caps);
पूर्ण

अटल bool dr_mask_is_tnl_gtpu_flex_parser_0(काष्ठा mlx5dr_match_param *mask,
					      काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	काष्ठा mlx5dr_cmd_caps *caps = &dmn->info.caps;

	वापस (dr_is_flex_parser_0_id(caps->flex_parser_id_gtpu_dw_0) &&
		dr_mask_is_tnl_gtpu_dw_0(mask, dmn)) ||
	       (dr_is_flex_parser_0_id(caps->flex_parser_id_gtpu_teid) &&
		dr_mask_is_tnl_gtpu_teid(mask, dmn)) ||
	       (dr_is_flex_parser_0_id(caps->flex_parser_id_gtpu_dw_2) &&
		dr_mask_is_tnl_gtpu_dw_2(mask, dmn)) ||
	       (dr_is_flex_parser_0_id(caps->flex_parser_id_gtpu_first_ext_dw_0) &&
		dr_mask_is_tnl_gtpu_first_ext(mask, dmn));
पूर्ण

अटल bool dr_mask_is_tnl_gtpu_flex_parser_1(काष्ठा mlx5dr_match_param *mask,
					      काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	काष्ठा mlx5dr_cmd_caps *caps = &dmn->info.caps;

	वापस (dr_is_flex_parser_1_id(caps->flex_parser_id_gtpu_dw_0) &&
		dr_mask_is_tnl_gtpu_dw_0(mask, dmn)) ||
	       (dr_is_flex_parser_1_id(caps->flex_parser_id_gtpu_teid) &&
		dr_mask_is_tnl_gtpu_teid(mask, dmn)) ||
	       (dr_is_flex_parser_1_id(caps->flex_parser_id_gtpu_dw_2) &&
		dr_mask_is_tnl_gtpu_dw_2(mask, dmn)) ||
	       (dr_is_flex_parser_1_id(caps->flex_parser_id_gtpu_first_ext_dw_0) &&
		dr_mask_is_tnl_gtpu_first_ext(mask, dmn));
पूर्ण

अटल bool dr_mask_is_tnl_gtpu_any(काष्ठा mlx5dr_match_param *mask,
				    काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस dr_mask_is_tnl_gtpu_flex_parser_0(mask, dmn) ||
	       dr_mask_is_tnl_gtpu_flex_parser_1(mask, dmn) ||
	       dr_mask_is_tnl_gtpu(mask, dmn);
पूर्ण

अटल पूर्णांक dr_matcher_supp_icmp_v4(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस (caps->sw_क्रमmat_ver == MLX5_STEERING_FORMAT_CONNECTX_6DX) ||
	       (caps->flex_protocols & MLX5_FLEX_PARSER_ICMP_V4_ENABLED);
पूर्ण

अटल पूर्णांक dr_matcher_supp_icmp_v6(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस (caps->sw_क्रमmat_ver == MLX5_STEERING_FORMAT_CONNECTX_6DX) ||
	       (caps->flex_protocols & MLX5_FLEX_PARSER_ICMP_V6_ENABLED);
पूर्ण

अटल bool dr_mask_is_icmpv6_set(काष्ठा mlx5dr_match_misc3 *misc3)
अणु
	वापस (misc3->icmpv6_type || misc3->icmpv6_code ||
		misc3->icmpv6_header_data);
पूर्ण

अटल bool dr_mask_is_icmp(काष्ठा mlx5dr_match_param *mask,
			    काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	अगर (DR_MASK_IS_ICMPV4_SET(&mask->misc3))
		वापस dr_matcher_supp_icmp_v4(&dmn->info.caps);
	अन्यथा अगर (dr_mask_is_icmpv6_set(&mask->misc3))
		वापस dr_matcher_supp_icmp_v6(&dmn->info.caps);

	वापस false;
पूर्ण

अटल bool dr_mask_is_wqe_metadata_set(काष्ठा mlx5dr_match_misc2 *misc2)
अणु
	वापस misc2->metadata_reg_a;
पूर्ण

अटल bool dr_mask_is_reg_c_0_3_set(काष्ठा mlx5dr_match_misc2 *misc2)
अणु
	वापस (misc2->metadata_reg_c_0 || misc2->metadata_reg_c_1 ||
		misc2->metadata_reg_c_2 || misc2->metadata_reg_c_3);
पूर्ण

अटल bool dr_mask_is_reg_c_4_7_set(काष्ठा mlx5dr_match_misc2 *misc2)
अणु
	वापस (misc2->metadata_reg_c_4 || misc2->metadata_reg_c_5 ||
		misc2->metadata_reg_c_6 || misc2->metadata_reg_c_7);
पूर्ण

अटल bool dr_mask_is_gvmi_or_qpn_set(काष्ठा mlx5dr_match_misc *misc)
अणु
	वापस (misc->source_sqn || misc->source_port);
पूर्ण

अटल bool dr_mask_is_flex_parser_id_0_3_set(u32 flex_parser_id,
					      u32 flex_parser_value)
अणु
	अगर (flex_parser_id)
		वापस flex_parser_id <= DR_STE_MAX_FLEX_0_ID;

	/* Using flex_parser 0 means that id is zero, thus value must be set. */
	वापस flex_parser_value;
पूर्ण

अटल bool dr_mask_is_flex_parser_0_3_set(काष्ठा mlx5dr_match_misc4 *misc4)
अणु
	वापस (dr_mask_is_flex_parser_id_0_3_set(misc4->prog_sample_field_id_0,
						  misc4->prog_sample_field_value_0) ||
		dr_mask_is_flex_parser_id_0_3_set(misc4->prog_sample_field_id_1,
						  misc4->prog_sample_field_value_1) ||
		dr_mask_is_flex_parser_id_0_3_set(misc4->prog_sample_field_id_2,
						  misc4->prog_sample_field_value_2) ||
		dr_mask_is_flex_parser_id_0_3_set(misc4->prog_sample_field_id_3,
						  misc4->prog_sample_field_value_3));
पूर्ण

अटल bool dr_mask_is_flex_parser_id_4_7_set(u32 flex_parser_id)
अणु
	वापस flex_parser_id > DR_STE_MAX_FLEX_0_ID &&
	       flex_parser_id <= DR_STE_MAX_FLEX_1_ID;
पूर्ण

अटल bool dr_mask_is_flex_parser_4_7_set(काष्ठा mlx5dr_match_misc4 *misc4)
अणु
	वापस (dr_mask_is_flex_parser_id_4_7_set(misc4->prog_sample_field_id_0) ||
		dr_mask_is_flex_parser_id_4_7_set(misc4->prog_sample_field_id_1) ||
		dr_mask_is_flex_parser_id_4_7_set(misc4->prog_sample_field_id_2) ||
		dr_mask_is_flex_parser_id_4_7_set(misc4->prog_sample_field_id_3));
पूर्ण

अटल पूर्णांक dr_matcher_supp_tnl_mpls_over_gre(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस caps->flex_protocols & MLX5_FLEX_PARSER_MPLS_OVER_GRE_ENABLED;
पूर्ण

अटल bool dr_mask_is_tnl_mpls_over_gre(काष्ठा mlx5dr_match_param *mask,
					 काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस DR_MASK_IS_OUTER_MPLS_OVER_GRE_SET(&mask->misc2) &&
	       dr_matcher_supp_tnl_mpls_over_gre(&dmn->info.caps);
पूर्ण

अटल पूर्णांक dr_matcher_supp_tnl_mpls_over_udp(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस caps->flex_protocols & mlx5_FLEX_PARSER_MPLS_OVER_UDP_ENABLED;
पूर्ण

अटल bool dr_mask_is_tnl_mpls_over_udp(काष्ठा mlx5dr_match_param *mask,
					 काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	वापस DR_MASK_IS_OUTER_MPLS_OVER_UDP_SET(&mask->misc2) &&
	       dr_matcher_supp_tnl_mpls_over_udp(&dmn->info.caps);
पूर्ण
पूर्णांक mlx5dr_matcher_select_builders(काष्ठा mlx5dr_matcher *matcher,
				   काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				   क्रमागत mlx5dr_ipv outer_ipv,
				   क्रमागत mlx5dr_ipv inner_ipv)
अणु
	nic_matcher->ste_builder =
		nic_matcher->ste_builder_arr[outer_ipv][inner_ipv];
	nic_matcher->num_of_builders =
		nic_matcher->num_of_builders_arr[outer_ipv][inner_ipv];

	अगर (!nic_matcher->num_of_builders) अणु
		mlx5dr_dbg(matcher->tbl->dmn,
			   "Rule not supported on this matcher due to IP related fields\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dr_matcher_set_ste_builders(काष्ठा mlx5dr_matcher *matcher,
				       काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				       क्रमागत mlx5dr_ipv outer_ipv,
				       क्रमागत mlx5dr_ipv inner_ipv)
अणु
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn = nic_matcher->nic_tbl->nic_dmn;
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_ste_ctx *ste_ctx = dmn->ste_ctx;
	काष्ठा mlx5dr_match_param mask = अणुपूर्ण;
	काष्ठा mlx5dr_ste_build *sb;
	bool inner, rx;
	पूर्णांक idx = 0;
	पूर्णांक ret, i;

	sb = nic_matcher->ste_builder_arr[outer_ipv][inner_ipv];
	rx = nic_dmn->ste_type == MLX5DR_STE_TYPE_RX;

	/* Create a temporary mask to track and clear used mask fields */
	अगर (matcher->match_criteria & DR_MATCHER_CRITERIA_OUTER)
		mask.outer = matcher->mask.outer;

	अगर (matcher->match_criteria & DR_MATCHER_CRITERIA_MISC)
		mask.misc = matcher->mask.misc;

	अगर (matcher->match_criteria & DR_MATCHER_CRITERIA_INNER)
		mask.inner = matcher->mask.inner;

	अगर (matcher->match_criteria & DR_MATCHER_CRITERIA_MISC2)
		mask.misc2 = matcher->mask.misc2;

	अगर (matcher->match_criteria & DR_MATCHER_CRITERIA_MISC3)
		mask.misc3 = matcher->mask.misc3;

	अगर (matcher->match_criteria & DR_MATCHER_CRITERIA_MISC4)
		mask.misc4 = matcher->mask.misc4;

	ret = mlx5dr_ste_build_pre_check(dmn, matcher->match_criteria,
					 &matcher->mask, शून्य);
	अगर (ret)
		वापस ret;

	/* Outer */
	अगर (matcher->match_criteria & (DR_MATCHER_CRITERIA_OUTER |
				       DR_MATCHER_CRITERIA_MISC |
				       DR_MATCHER_CRITERIA_MISC2 |
				       DR_MATCHER_CRITERIA_MISC3)) अणु
		inner = false;

		अगर (dr_mask_is_wqe_metadata_set(&mask.misc2))
			mlx5dr_ste_build_general_purpose(ste_ctx, &sb[idx++],
							 &mask, inner, rx);

		अगर (dr_mask_is_reg_c_0_3_set(&mask.misc2))
			mlx5dr_ste_build_रेजिस्टर_0(ste_ctx, &sb[idx++],
						    &mask, inner, rx);

		अगर (dr_mask_is_reg_c_4_7_set(&mask.misc2))
			mlx5dr_ste_build_रेजिस्टर_1(ste_ctx, &sb[idx++],
						    &mask, inner, rx);

		अगर (dr_mask_is_gvmi_or_qpn_set(&mask.misc) &&
		    (dmn->type == MLX5DR_DOMAIN_TYPE_FDB ||
		     dmn->type == MLX5DR_DOMAIN_TYPE_NIC_RX)) अणु
			mlx5dr_ste_build_src_gvmi_qpn(ste_ctx, &sb[idx++],
						      &mask, dmn, inner, rx);
		पूर्ण

		अगर (dr_mask_is_smac_set(&mask.outer) &&
		    dr_mask_is_dmac_set(&mask.outer)) अणु
			mlx5dr_ste_build_eth_l2_src_dst(ste_ctx, &sb[idx++],
							&mask, inner, rx);
		पूर्ण

		अगर (dr_mask_is_smac_set(&mask.outer))
			mlx5dr_ste_build_eth_l2_src(ste_ctx, &sb[idx++],
						    &mask, inner, rx);

		अगर (DR_MASK_IS_L2_DST(mask.outer, mask.misc, outer))
			mlx5dr_ste_build_eth_l2_dst(ste_ctx, &sb[idx++],
						    &mask, inner, rx);

		अगर (outer_ipv == DR_RULE_IPV6) अणु
			अगर (dr_mask_is_dst_addr_set(&mask.outer))
				mlx5dr_ste_build_eth_l3_ipv6_dst(ste_ctx, &sb[idx++],
								 &mask, inner, rx);

			अगर (dr_mask_is_src_addr_set(&mask.outer))
				mlx5dr_ste_build_eth_l3_ipv6_src(ste_ctx, &sb[idx++],
								 &mask, inner, rx);

			अगर (DR_MASK_IS_ETH_L4_SET(mask.outer, mask.misc, outer))
				mlx5dr_ste_build_eth_ipv6_l3_l4(ste_ctx, &sb[idx++],
								&mask, inner, rx);
		पूर्ण अन्यथा अणु
			अगर (dr_mask_is_ipv4_5_tuple_set(&mask.outer))
				mlx5dr_ste_build_eth_l3_ipv4_5_tuple(ste_ctx, &sb[idx++],
								     &mask, inner, rx);

			अगर (dr_mask_is_ttl_set(&mask.outer))
				mlx5dr_ste_build_eth_l3_ipv4_misc(ste_ctx, &sb[idx++],
								  &mask, inner, rx);
		पूर्ण

		अगर (dr_mask_is_tnl_vxlan_gpe(&mask, dmn))
			mlx5dr_ste_build_tnl_vxlan_gpe(ste_ctx, &sb[idx++],
						       &mask, inner, rx);
		अन्यथा अगर (dr_mask_is_tnl_geneve(&mask, dmn)) अणु
			mlx5dr_ste_build_tnl_geneve(ste_ctx, &sb[idx++],
						    &mask, inner, rx);
			अगर (dr_mask_is_tnl_geneve_tlv_opt(&mask.misc3))
				mlx5dr_ste_build_tnl_geneve_tlv_opt(ste_ctx, &sb[idx++],
								    &mask, &dmn->info.caps,
								    inner, rx);
		पूर्ण अन्यथा अगर (dr_mask_is_tnl_gtpu_any(&mask, dmn)) अणु
			अगर (dr_mask_is_tnl_gtpu_flex_parser_0(&mask, dmn))
				mlx5dr_ste_build_tnl_gtpu_flex_parser_0(ste_ctx, &sb[idx++],
									&mask, &dmn->info.caps,
									inner, rx);

			अगर (dr_mask_is_tnl_gtpu_flex_parser_1(&mask, dmn))
				mlx5dr_ste_build_tnl_gtpu_flex_parser_1(ste_ctx, &sb[idx++],
									&mask, &dmn->info.caps,
									inner, rx);

			अगर (dr_mask_is_tnl_gtpu(&mask, dmn))
				mlx5dr_ste_build_tnl_gtpu(ste_ctx, &sb[idx++],
							  &mask, inner, rx);
		पूर्ण

		अगर (DR_MASK_IS_ETH_L4_MISC_SET(mask.misc3, outer))
			mlx5dr_ste_build_eth_l4_misc(ste_ctx, &sb[idx++],
						     &mask, inner, rx);

		अगर (DR_MASK_IS_FIRST_MPLS_SET(mask.misc2, outer))
			mlx5dr_ste_build_mpls(ste_ctx, &sb[idx++],
					      &mask, inner, rx);

		अगर (dr_mask_is_tnl_mpls_over_gre(&mask, dmn))
			mlx5dr_ste_build_tnl_mpls_over_gre(ste_ctx, &sb[idx++],
							   &mask, &dmn->info.caps,
							   inner, rx);
		अन्यथा अगर (dr_mask_is_tnl_mpls_over_udp(&mask, dmn))
			mlx5dr_ste_build_tnl_mpls_over_udp(ste_ctx, &sb[idx++],
							   &mask, &dmn->info.caps,
							   inner, rx);

		अगर (dr_mask_is_icmp(&mask, dmn))
			mlx5dr_ste_build_icmp(ste_ctx, &sb[idx++],
					      &mask, &dmn->info.caps,
					      inner, rx);

		अगर (dr_mask_is_tnl_gre_set(&mask.misc))
			mlx5dr_ste_build_tnl_gre(ste_ctx, &sb[idx++],
						 &mask, inner, rx);
	पूर्ण

	/* Inner */
	अगर (matcher->match_criteria & (DR_MATCHER_CRITERIA_INNER |
				       DR_MATCHER_CRITERIA_MISC |
				       DR_MATCHER_CRITERIA_MISC2 |
				       DR_MATCHER_CRITERIA_MISC3)) अणु
		inner = true;

		अगर (dr_mask_is_eth_l2_tnl_set(&mask.misc))
			mlx5dr_ste_build_eth_l2_tnl(ste_ctx, &sb[idx++],
						    &mask, inner, rx);

		अगर (dr_mask_is_smac_set(&mask.inner) &&
		    dr_mask_is_dmac_set(&mask.inner)) अणु
			mlx5dr_ste_build_eth_l2_src_dst(ste_ctx, &sb[idx++],
							&mask, inner, rx);
		पूर्ण

		अगर (dr_mask_is_smac_set(&mask.inner))
			mlx5dr_ste_build_eth_l2_src(ste_ctx, &sb[idx++],
						    &mask, inner, rx);

		अगर (DR_MASK_IS_L2_DST(mask.inner, mask.misc, inner))
			mlx5dr_ste_build_eth_l2_dst(ste_ctx, &sb[idx++],
						    &mask, inner, rx);

		अगर (inner_ipv == DR_RULE_IPV6) अणु
			अगर (dr_mask_is_dst_addr_set(&mask.inner))
				mlx5dr_ste_build_eth_l3_ipv6_dst(ste_ctx, &sb[idx++],
								 &mask, inner, rx);

			अगर (dr_mask_is_src_addr_set(&mask.inner))
				mlx5dr_ste_build_eth_l3_ipv6_src(ste_ctx, &sb[idx++],
								 &mask, inner, rx);

			अगर (DR_MASK_IS_ETH_L4_SET(mask.inner, mask.misc, inner))
				mlx5dr_ste_build_eth_ipv6_l3_l4(ste_ctx, &sb[idx++],
								&mask, inner, rx);
		पूर्ण अन्यथा अणु
			अगर (dr_mask_is_ipv4_5_tuple_set(&mask.inner))
				mlx5dr_ste_build_eth_l3_ipv4_5_tuple(ste_ctx, &sb[idx++],
								     &mask, inner, rx);

			अगर (dr_mask_is_ttl_set(&mask.inner))
				mlx5dr_ste_build_eth_l3_ipv4_misc(ste_ctx, &sb[idx++],
								  &mask, inner, rx);
		पूर्ण

		अगर (DR_MASK_IS_ETH_L4_MISC_SET(mask.misc3, inner))
			mlx5dr_ste_build_eth_l4_misc(ste_ctx, &sb[idx++],
						     &mask, inner, rx);

		अगर (DR_MASK_IS_FIRST_MPLS_SET(mask.misc2, inner))
			mlx5dr_ste_build_mpls(ste_ctx, &sb[idx++],
					      &mask, inner, rx);

		अगर (dr_mask_is_tnl_mpls_over_gre(&mask, dmn))
			mlx5dr_ste_build_tnl_mpls_over_gre(ste_ctx, &sb[idx++],
							   &mask, &dmn->info.caps,
							   inner, rx);
		अन्यथा अगर (dr_mask_is_tnl_mpls_over_udp(&mask, dmn))
			mlx5dr_ste_build_tnl_mpls_over_udp(ste_ctx, &sb[idx++],
							   &mask, &dmn->info.caps,
							   inner, rx);
	पूर्ण

	अगर (matcher->match_criteria & DR_MATCHER_CRITERIA_MISC4) अणु
		अगर (dr_mask_is_flex_parser_0_3_set(&mask.misc4))
			mlx5dr_ste_build_flex_parser_0(ste_ctx, &sb[idx++],
						       &mask, false, rx);

		अगर (dr_mask_is_flex_parser_4_7_set(&mask.misc4))
			mlx5dr_ste_build_flex_parser_1(ste_ctx, &sb[idx++],
						       &mask, false, rx);
	पूर्ण

	/* Empty matcher, takes all */
	अगर (matcher->match_criteria == DR_MATCHER_CRITERIA_EMPTY)
		mlx5dr_ste_build_empty_always_hit(&sb[idx++], rx);

	अगर (idx == 0) अणु
		mlx5dr_err(dmn, "Cannot generate any valid rules from mask\n");
		वापस -EINVAL;
	पूर्ण

	/* Check that all mask fields were consumed */
	क्रम (i = 0; i < माप(काष्ठा mlx5dr_match_param); i++) अणु
		अगर (((u8 *)&mask)[i] != 0) अणु
			mlx5dr_dbg(dmn, "Mask contains unsupported parameters\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	nic_matcher->ste_builder = sb;
	nic_matcher->num_of_builders_arr[outer_ipv][inner_ipv] = idx;

	वापस 0;
पूर्ण

अटल पूर्णांक dr_matcher_connect(काष्ठा mlx5dr_करोमुख्य *dmn,
			      काष्ठा mlx5dr_matcher_rx_tx *curr_nic_matcher,
			      काष्ठा mlx5dr_matcher_rx_tx *next_nic_matcher,
			      काष्ठा mlx5dr_matcher_rx_tx *prev_nic_matcher)
अणु
	काष्ठा mlx5dr_table_rx_tx *nic_tbl = curr_nic_matcher->nic_tbl;
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn = nic_tbl->nic_dmn;
	काष्ठा mlx5dr_htbl_connect_info info;
	काष्ठा mlx5dr_ste_htbl *prev_htbl;
	पूर्णांक ret;

	/* Connect end anchor hash table to next_htbl or to the शेष address */
	अगर (next_nic_matcher) अणु
		info.type = CONNECT_HIT;
		info.hit_next_htbl = next_nic_matcher->s_htbl;
	पूर्ण अन्यथा अणु
		info.type = CONNECT_MISS;
		info.miss_icm_addr = nic_tbl->शेष_icm_addr;
	पूर्ण
	ret = mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn,
						curr_nic_matcher->e_anchor,
						&info, info.type == CONNECT_HIT);
	अगर (ret)
		वापस ret;

	/* Connect start hash table to end anchor */
	info.type = CONNECT_MISS;
	info.miss_icm_addr = curr_nic_matcher->e_anchor->chunk->icm_addr;
	ret = mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn,
						curr_nic_matcher->s_htbl,
						&info, false);
	अगर (ret)
		वापस ret;

	/* Connect previous hash table to matcher start hash table */
	अगर (prev_nic_matcher)
		prev_htbl = prev_nic_matcher->e_anchor;
	अन्यथा
		prev_htbl = nic_tbl->s_anchor;

	info.type = CONNECT_HIT;
	info.hit_next_htbl = curr_nic_matcher->s_htbl;
	ret = mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn, prev_htbl,
						&info, true);
	अगर (ret)
		वापस ret;

	/* Update the poपूर्णांकing ste and next hash table */
	curr_nic_matcher->s_htbl->poपूर्णांकing_ste = prev_htbl->ste_arr;
	prev_htbl->ste_arr[0].next_htbl = curr_nic_matcher->s_htbl;

	अगर (next_nic_matcher) अणु
		next_nic_matcher->s_htbl->poपूर्णांकing_ste = curr_nic_matcher->e_anchor->ste_arr;
		curr_nic_matcher->e_anchor->ste_arr[0].next_htbl = next_nic_matcher->s_htbl;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dr_matcher_add_to_tbl(काष्ठा mlx5dr_matcher *matcher)
अणु
	काष्ठा mlx5dr_matcher *next_matcher, *prev_matcher, *पंचांगp_matcher;
	काष्ठा mlx5dr_table *tbl = matcher->tbl;
	काष्ठा mlx5dr_करोमुख्य *dmn = tbl->dmn;
	bool first = true;
	पूर्णांक ret;

	next_matcher = शून्य;
	list_क्रम_each_entry(पंचांगp_matcher, &tbl->matcher_list, matcher_list) अणु
		अगर (पंचांगp_matcher->prio >= matcher->prio) अणु
			next_matcher = पंचांगp_matcher;
			अवरोध;
		पूर्ण
		first = false;
	पूर्ण

	prev_matcher = शून्य;
	अगर (next_matcher && !first)
		prev_matcher = list_prev_entry(next_matcher, matcher_list);
	अन्यथा अगर (!first)
		prev_matcher = list_last_entry(&tbl->matcher_list,
					       काष्ठा mlx5dr_matcher,
					       matcher_list);

	अगर (dmn->type == MLX5DR_DOMAIN_TYPE_FDB ||
	    dmn->type == MLX5DR_DOMAIN_TYPE_NIC_RX) अणु
		ret = dr_matcher_connect(dmn, &matcher->rx,
					 next_matcher ? &next_matcher->rx : शून्य,
					 prev_matcher ?	&prev_matcher->rx : शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dmn->type == MLX5DR_DOMAIN_TYPE_FDB ||
	    dmn->type == MLX5DR_DOMAIN_TYPE_NIC_TX) अणु
		ret = dr_matcher_connect(dmn, &matcher->tx,
					 next_matcher ? &next_matcher->tx : शून्य,
					 prev_matcher ?	&prev_matcher->tx : शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (prev_matcher)
		list_add(&matcher->matcher_list, &prev_matcher->matcher_list);
	अन्यथा अगर (next_matcher)
		list_add_tail(&matcher->matcher_list,
			      &next_matcher->matcher_list);
	अन्यथा
		list_add(&matcher->matcher_list, &tbl->matcher_list);

	वापस 0;
पूर्ण

अटल व्योम dr_matcher_uninit_nic(काष्ठा mlx5dr_matcher_rx_tx *nic_matcher)
अणु
	mlx5dr_htbl_put(nic_matcher->s_htbl);
	mlx5dr_htbl_put(nic_matcher->e_anchor);
पूर्ण

अटल व्योम dr_matcher_uninit_fdb(काष्ठा mlx5dr_matcher *matcher)
अणु
	dr_matcher_uninit_nic(&matcher->rx);
	dr_matcher_uninit_nic(&matcher->tx);
पूर्ण

अटल व्योम dr_matcher_uninit(काष्ठा mlx5dr_matcher *matcher)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;

	चयन (dmn->type) अणु
	हाल MLX5DR_DOMAIN_TYPE_NIC_RX:
		dr_matcher_uninit_nic(&matcher->rx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_NIC_TX:
		dr_matcher_uninit_nic(&matcher->tx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_FDB:
		dr_matcher_uninit_fdb(matcher);
		अवरोध;
	शेष:
		WARN_ON(true);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक dr_matcher_set_all_ste_builders(काष्ठा mlx5dr_matcher *matcher,
					   काष्ठा mlx5dr_matcher_rx_tx *nic_matcher)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;

	dr_matcher_set_ste_builders(matcher, nic_matcher, DR_RULE_IPV4, DR_RULE_IPV4);
	dr_matcher_set_ste_builders(matcher, nic_matcher, DR_RULE_IPV4, DR_RULE_IPV6);
	dr_matcher_set_ste_builders(matcher, nic_matcher, DR_RULE_IPV6, DR_RULE_IPV4);
	dr_matcher_set_ste_builders(matcher, nic_matcher, DR_RULE_IPV6, DR_RULE_IPV6);

	अगर (!nic_matcher->ste_builder) अणु
		mlx5dr_err(dmn, "Cannot generate IPv4 or IPv6 rules with given mask\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dr_matcher_init_nic(काष्ठा mlx5dr_matcher *matcher,
			       काष्ठा mlx5dr_matcher_rx_tx *nic_matcher)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	पूर्णांक ret;

	ret = dr_matcher_set_all_ste_builders(matcher, nic_matcher);
	अगर (ret)
		वापस ret;

	nic_matcher->e_anchor = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
						      DR_CHUNK_SIZE_1,
						      MLX5DR_STE_LU_TYPE_DONT_CARE,
						      0);
	अगर (!nic_matcher->e_anchor)
		वापस -ENOMEM;

	nic_matcher->s_htbl = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
						    DR_CHUNK_SIZE_1,
						    nic_matcher->ste_builder[0].lu_type,
						    nic_matcher->ste_builder[0].byte_mask);
	अगर (!nic_matcher->s_htbl) अणु
		ret = -ENOMEM;
		जाओ मुक्त_e_htbl;
	पूर्ण

	/* make sure the tables exist जबतक empty */
	mlx5dr_htbl_get(nic_matcher->s_htbl);
	mlx5dr_htbl_get(nic_matcher->e_anchor);

	वापस 0;

मुक्त_e_htbl:
	mlx5dr_ste_htbl_मुक्त(nic_matcher->e_anchor);
	वापस ret;
पूर्ण

अटल पूर्णांक dr_matcher_init_fdb(काष्ठा mlx5dr_matcher *matcher)
अणु
	पूर्णांक ret;

	ret = dr_matcher_init_nic(matcher, &matcher->rx);
	अगर (ret)
		वापस ret;

	ret = dr_matcher_init_nic(matcher, &matcher->tx);
	अगर (ret)
		जाओ uninit_nic_rx;

	वापस 0;

uninit_nic_rx:
	dr_matcher_uninit_nic(&matcher->rx);
	वापस ret;
पूर्ण

अटल पूर्णांक dr_matcher_init(काष्ठा mlx5dr_matcher *matcher,
			   काष्ठा mlx5dr_match_parameters *mask)
अणु
	काष्ठा mlx5dr_table *tbl = matcher->tbl;
	काष्ठा mlx5dr_करोमुख्य *dmn = tbl->dmn;
	पूर्णांक ret;

	अगर (matcher->match_criteria >= DR_MATCHER_CRITERIA_MAX) अणु
		mlx5dr_err(dmn, "Invalid match criteria attribute\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mask) अणु
		अगर (mask->match_sz > DR_SZ_MATCH_PARAM) अणु
			mlx5dr_err(dmn, "Invalid match size attribute\n");
			वापस -EINVAL;
		पूर्ण
		mlx5dr_ste_copy_param(matcher->match_criteria,
				      &matcher->mask, mask);
	पूर्ण

	चयन (dmn->type) अणु
	हाल MLX5DR_DOMAIN_TYPE_NIC_RX:
		matcher->rx.nic_tbl = &tbl->rx;
		ret = dr_matcher_init_nic(matcher, &matcher->rx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_NIC_TX:
		matcher->tx.nic_tbl = &tbl->tx;
		ret = dr_matcher_init_nic(matcher, &matcher->tx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_FDB:
		matcher->rx.nic_tbl = &tbl->rx;
		matcher->tx.nic_tbl = &tbl->tx;
		ret = dr_matcher_init_fdb(matcher);
		अवरोध;
	शेष:
		WARN_ON(true);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा mlx5dr_matcher *
mlx5dr_matcher_create(काष्ठा mlx5dr_table *tbl,
		      u32 priority,
		      u8 match_criteria_enable,
		      काष्ठा mlx5dr_match_parameters *mask)
अणु
	काष्ठा mlx5dr_matcher *matcher;
	पूर्णांक ret;

	refcount_inc(&tbl->refcount);

	matcher = kzalloc(माप(*matcher), GFP_KERNEL);
	अगर (!matcher)
		जाओ dec_ref;

	matcher->tbl = tbl;
	matcher->prio = priority;
	matcher->match_criteria = match_criteria_enable;
	refcount_set(&matcher->refcount, 1);
	INIT_LIST_HEAD(&matcher->matcher_list);

	mlx5dr_करोमुख्य_lock(tbl->dmn);

	ret = dr_matcher_init(matcher, mask);
	अगर (ret)
		जाओ मुक्त_matcher;

	ret = dr_matcher_add_to_tbl(matcher);
	अगर (ret)
		जाओ matcher_uninit;

	mlx5dr_करोमुख्य_unlock(tbl->dmn);

	वापस matcher;

matcher_uninit:
	dr_matcher_uninit(matcher);
मुक्त_matcher:
	mlx5dr_करोमुख्य_unlock(tbl->dmn);
	kमुक्त(matcher);
dec_ref:
	refcount_dec(&tbl->refcount);
	वापस शून्य;
पूर्ण

अटल पूर्णांक dr_matcher_disconnect(काष्ठा mlx5dr_करोमुख्य *dmn,
				 काष्ठा mlx5dr_table_rx_tx *nic_tbl,
				 काष्ठा mlx5dr_matcher_rx_tx *next_nic_matcher,
				 काष्ठा mlx5dr_matcher_rx_tx *prev_nic_matcher)
अणु
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn = nic_tbl->nic_dmn;
	काष्ठा mlx5dr_htbl_connect_info info;
	काष्ठा mlx5dr_ste_htbl *prev_anchor;

	अगर (prev_nic_matcher)
		prev_anchor = prev_nic_matcher->e_anchor;
	अन्यथा
		prev_anchor = nic_tbl->s_anchor;

	/* Connect previous anchor hash table to next matcher or to the शेष address */
	अगर (next_nic_matcher) अणु
		info.type = CONNECT_HIT;
		info.hit_next_htbl = next_nic_matcher->s_htbl;
		next_nic_matcher->s_htbl->poपूर्णांकing_ste = prev_anchor->ste_arr;
		prev_anchor->ste_arr[0].next_htbl = next_nic_matcher->s_htbl;
	पूर्ण अन्यथा अणु
		info.type = CONNECT_MISS;
		info.miss_icm_addr = nic_tbl->शेष_icm_addr;
		prev_anchor->ste_arr[0].next_htbl = शून्य;
	पूर्ण

	वापस mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn, prev_anchor,
						 &info, true);
पूर्ण

अटल पूर्णांक dr_matcher_हटाओ_from_tbl(काष्ठा mlx5dr_matcher *matcher)
अणु
	काष्ठा mlx5dr_matcher *prev_matcher, *next_matcher;
	काष्ठा mlx5dr_table *tbl = matcher->tbl;
	काष्ठा mlx5dr_करोमुख्य *dmn = tbl->dmn;
	पूर्णांक ret = 0;

	अगर (list_is_last(&matcher->matcher_list, &tbl->matcher_list))
		next_matcher = शून्य;
	अन्यथा
		next_matcher = list_next_entry(matcher, matcher_list);

	अगर (matcher->matcher_list.prev == &tbl->matcher_list)
		prev_matcher = शून्य;
	अन्यथा
		prev_matcher = list_prev_entry(matcher, matcher_list);

	अगर (dmn->type == MLX5DR_DOMAIN_TYPE_FDB ||
	    dmn->type == MLX5DR_DOMAIN_TYPE_NIC_RX) अणु
		ret = dr_matcher_disconnect(dmn, &tbl->rx,
					    next_matcher ? &next_matcher->rx : शून्य,
					    prev_matcher ? &prev_matcher->rx : शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dmn->type == MLX5DR_DOMAIN_TYPE_FDB ||
	    dmn->type == MLX5DR_DOMAIN_TYPE_NIC_TX) अणु
		ret = dr_matcher_disconnect(dmn, &tbl->tx,
					    next_matcher ? &next_matcher->tx : शून्य,
					    prev_matcher ? &prev_matcher->tx : शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	list_del(&matcher->matcher_list);

	वापस 0;
पूर्ण

पूर्णांक mlx5dr_matcher_destroy(काष्ठा mlx5dr_matcher *matcher)
अणु
	काष्ठा mlx5dr_table *tbl = matcher->tbl;

	अगर (refcount_पढ़ो(&matcher->refcount) > 1)
		वापस -EBUSY;

	mlx5dr_करोमुख्य_lock(tbl->dmn);

	dr_matcher_हटाओ_from_tbl(matcher);
	dr_matcher_uninit(matcher);
	refcount_dec(&matcher->tbl->refcount);

	mlx5dr_करोमुख्य_unlock(tbl->dmn);
	kमुक्त(matcher);

	वापस 0;
पूर्ण
