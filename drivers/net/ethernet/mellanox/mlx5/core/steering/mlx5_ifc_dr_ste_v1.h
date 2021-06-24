<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2020 NVIDIA CORPORATION. All rights reserved. */

#अगर_अघोषित MLX5_IFC_DR_STE_V1_H
#घोषणा MLX5_IFC_DR_STE_V1_H

क्रमागत mlx5_अगरc_ste_v1_modअगरy_hdr_offset अणु
	MLX5_MODIFY_HEADER_V1_QW_OFFSET = 0x20,
पूर्ण;

काष्ठा mlx5_अगरc_ste_single_action_flow_tag_v1_bits अणु
	u8         action_id[0x8];
	u8         flow_tag[0x18];
पूर्ण;

काष्ठा mlx5_अगरc_ste_single_action_modअगरy_list_v1_bits अणु
	u8         action_id[0x8];
	u8         num_of_modअगरy_actions[0x8];
	u8         modअगरy_actions_ptr[0x10];
पूर्ण;

काष्ठा mlx5_अगरc_ste_single_action_हटाओ_header_v1_bits अणु
	u8         action_id[0x8];
	u8         reserved_at_8[0x2];
	u8         start_anchor[0x6];
	u8         reserved_at_10[0x2];
	u8         end_anchor[0x6];
	u8         reserved_at_18[0x4];
	u8         decap[0x1];
	u8         vni_to_cqe[0x1];
	u8         qos_profile[0x2];
पूर्ण;

काष्ठा mlx5_अगरc_ste_single_action_हटाओ_header_size_v1_bits अणु
	u8         action_id[0x8];
	u8         reserved_at_8[0x2];
	u8         start_anchor[0x6];
	u8         outer_l4_हटाओ[0x1];
	u8         reserved_at_11[0x1];
	u8         start_offset[0x7];
	u8         reserved_at_18[0x1];
	u8         हटाओ_size[0x6];
पूर्ण;

काष्ठा mlx5_अगरc_ste_द्विगुन_action_copy_v1_bits अणु
	u8         action_id[0x8];
	u8         destination_dw_offset[0x8];
	u8         reserved_at_10[0x2];
	u8         destination_left_shअगरter[0x6];
	u8         reserved_at_17[0x2];
	u8         destination_length[0x6];

	u8         reserved_at_20[0x8];
	u8         source_dw_offset[0x8];
	u8         reserved_at_30[0x2];
	u8         source_right_shअगरter[0x6];
	u8         reserved_at_38[0x8];
पूर्ण;

काष्ठा mlx5_अगरc_ste_द्विगुन_action_set_v1_bits अणु
	u8         action_id[0x8];
	u8         destination_dw_offset[0x8];
	u8         reserved_at_10[0x2];
	u8         destination_left_shअगरter[0x6];
	u8         reserved_at_18[0x2];
	u8         destination_length[0x6];

	u8         अंतरभूत_data[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_द्विगुन_action_add_v1_bits अणु
	u8         action_id[0x8];
	u8         destination_dw_offset[0x8];
	u8         reserved_at_10[0x2];
	u8         destination_left_shअगरter[0x6];
	u8         reserved_at_18[0x2];
	u8         destination_length[0x6];

	u8         add_value[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_द्विगुन_action_insert_with_अंतरभूत_v1_bits अणु
	u8         action_id[0x8];
	u8         reserved_at_8[0x2];
	u8         start_anchor[0x6];
	u8         start_offset[0x7];
	u8         reserved_at_17[0x9];

	u8         अंतरभूत_data[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_द्विगुन_action_insert_with_ptr_v1_bits अणु
	u8         action_id[0x8];
	u8         reserved_at_8[0x2];
	u8         start_anchor[0x6];
	u8         start_offset[0x7];
	u8         size[0x6];
	u8         attributes[0x3];

	u8         poपूर्णांकer[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_द्विगुन_action_modअगरy_action_list_v1_bits अणु
	u8         action_id[0x8];
	u8         modअगरy_actions_pattern_poपूर्णांकer[0x18];

	u8         number_of_modअगरy_actions[0x8];
	u8         modअगरy_actions_argument_poपूर्णांकer[0x18];
पूर्ण;

काष्ठा mlx5_अगरc_ste_match_bwc_v1_bits अणु
	u8         entry_क्रमmat[0x8];
	u8         counter_id[0x18];

	u8         miss_address_63_48[0x10];
	u8         match_definer_ctx_idx[0x8];
	u8         miss_address_39_32[0x8];

	u8         miss_address_31_6[0x1a];
	u8         reserved_at_5a[0x1];
	u8         match_polarity[0x1];
	u8         reparse[0x1];
	u8         reserved_at_5d[0x3];

	u8         next_table_base_63_48[0x10];
	u8         hash_definer_ctx_idx[0x8];
	u8         next_table_base_39_32_size[0x8];

	u8         next_table_base_31_5_size[0x1b];
	u8         hash_type[0x2];
	u8         hash_after_actions[0x1];
	u8         reserved_at_9e[0x2];

	u8         byte_mask[0x10];
	u8         next_entry_क्रमmat[0x1];
	u8         mask_mode[0x1];
	u8         gvmi[0xe];

	u8         action[0x40];
पूर्ण;

काष्ठा mlx5_अगरc_ste_mask_and_match_v1_bits अणु
	u8         entry_क्रमmat[0x8];
	u8         counter_id[0x18];

	u8         miss_address_63_48[0x10];
	u8         match_definer_ctx_idx[0x8];
	u8         miss_address_39_32[0x8];

	u8         miss_address_31_6[0x1a];
	u8         reserved_at_5a[0x1];
	u8         match_polarity[0x1];
	u8         reparse[0x1];
	u8         reserved_at_5d[0x3];

	u8         next_table_base_63_48[0x10];
	u8         hash_definer_ctx_idx[0x8];
	u8         next_table_base_39_32_size[0x8];

	u8         next_table_base_31_5_size[0x1b];
	u8         hash_type[0x2];
	u8         hash_after_actions[0x1];
	u8         reserved_at_9e[0x2];

	u8         action[0x60];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l2_src_v1_bits अणु
	u8         reserved_at_0[0x1];
	u8         sx_snअगरfer[0x1];
	u8         functional_loopback[0x1];
	u8         ip_fragmented[0x1];
	u8         qp_type[0x2];
	u8         encapsulation_type[0x2];
	u8         port[0x2];
	u8         l3_type[0x2];
	u8         l4_type[0x2];
	u8         first_vlan_qualअगरier[0x2];
	u8         first_priority[0x3];
	u8         first_cfi[0x1];
	u8         first_vlan_id[0xc];

	u8         smac_47_16[0x20];

	u8         smac_15_0[0x10];
	u8         l3_ethertype[0x10];

	u8         reserved_at_60[0x6];
	u8         tcp_syn[0x1];
	u8         reserved_at_67[0x3];
	u8         क्रमce_loopback[0x1];
	u8         l2_ok[0x1];
	u8         l3_ok[0x1];
	u8         l4_ok[0x1];
	u8         second_vlan_qualअगरier[0x2];

	u8         second_priority[0x3];
	u8         second_cfi[0x1];
	u8         second_vlan_id[0xc];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l2_dst_v1_bits अणु
	u8         reserved_at_0[0x1];
	u8         sx_snअगरfer[0x1];
	u8         functional_lb[0x1];
	u8         ip_fragmented[0x1];
	u8         qp_type[0x2];
	u8         encapsulation_type[0x2];
	u8         port[0x2];
	u8         l3_type[0x2];
	u8         l4_type[0x2];
	u8         first_vlan_qualअगरier[0x2];
	u8         first_priority[0x3];
	u8         first_cfi[0x1];
	u8         first_vlan_id[0xc];

	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         l3_ethertype[0x10];

	u8         reserved_at_60[0x6];
	u8         tcp_syn[0x1];
	u8         reserved_at_67[0x3];
	u8         क्रमce_lb[0x1];
	u8         l2_ok[0x1];
	u8         l3_ok[0x1];
	u8         l4_ok[0x1];
	u8         second_vlan_qualअगरier[0x2];
	u8         second_priority[0x3];
	u8         second_cfi[0x1];
	u8         second_vlan_id[0xc];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l2_src_dst_v1_bits अणु
	u8         dmac_47_16[0x20];

	u8         smac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         reserved_at_50[0x2];
	u8         functional_lb[0x1];
	u8         reserved_at_53[0x5];
	u8         port[0x2];
	u8         l3_type[0x2];
	u8         reserved_at_5c[0x2];
	u8         first_vlan_qualअगरier[0x2];

	u8         first_priority[0x3];
	u8         first_cfi[0x1];
	u8         first_vlan_id[0xc];
	u8         smac_15_0[0x10];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l3_ipv4_5_tuple_v1_bits अणु
	u8         source_address[0x20];

	u8         destination_address[0x20];

	u8         source_port[0x10];
	u8         destination_port[0x10];

	u8         reserved_at_60[0x4];
	u8         l4_ok[0x1];
	u8         l3_ok[0x1];
	u8         fragmented[0x1];
	u8         tcp_ns[0x1];
	u8         tcp_cwr[0x1];
	u8         tcp_ece[0x1];
	u8         tcp_urg[0x1];
	u8         tcp_ack[0x1];
	u8         tcp_psh[0x1];
	u8         tcp_rst[0x1];
	u8         tcp_syn[0x1];
	u8         tcp_fin[0x1];
	u8         dscp[0x6];
	u8         ecn[0x2];
	u8         protocol[0x8];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l2_tnl_v1_bits अणु
	u8         l2_tunneling_network_id[0x20];

	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         l3_ethertype[0x10];

	u8         reserved_at_60[0x3];
	u8         ip_fragmented[0x1];
	u8         reserved_at_64[0x2];
	u8         encp_type[0x2];
	u8         reserved_at_68[0x2];
	u8         l3_type[0x2];
	u8         l4_type[0x2];
	u8         first_vlan_qualअगरier[0x2];
	u8         first_priority[0x3];
	u8         first_cfi[0x1];
	u8         first_vlan_id[0xc];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l3_ipv4_misc_v1_bits अणु
	u8         identअगरication[0x10];
	u8         flags[0x3];
	u8         fragment_offset[0xd];

	u8         total_length[0x10];
	u8         checksum[0x10];

	u8         version[0x4];
	u8         ihl[0x4];
	u8         समय_प्रकारo_live[0x8];
	u8         reserved_at_50[0x10];

	u8         reserved_at_60[0x1c];
	u8         voq_पूर्णांकernal_prio[0x4];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l4_v1_bits अणु
	u8         ipv6_version[0x4];
	u8         reserved_at_4[0x4];
	u8         dscp[0x6];
	u8         ecn[0x2];
	u8         ipv6_hop_limit[0x8];
	u8         protocol[0x8];

	u8         src_port[0x10];
	u8         dst_port[0x10];

	u8         first_fragment[0x1];
	u8         reserved_at_41[0xb];
	u8         flow_label[0x14];

	u8         tcp_data_offset[0x4];
	u8         l4_ok[0x1];
	u8         l3_ok[0x1];
	u8         fragmented[0x1];
	u8         tcp_ns[0x1];
	u8         tcp_cwr[0x1];
	u8         tcp_ece[0x1];
	u8         tcp_urg[0x1];
	u8         tcp_ack[0x1];
	u8         tcp_psh[0x1];
	u8         tcp_rst[0x1];
	u8         tcp_syn[0x1];
	u8         tcp_fin[0x1];
	u8         ipv6_paylen[0x10];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l4_misc_v1_bits अणु
	u8         winकरोw_size[0x10];
	u8         urgent_poपूर्णांकer[0x10];

	u8         ack_num[0x20];

	u8         seq_num[0x20];

	u8         length[0x10];
	u8         checksum[0x10];
पूर्ण;

काष्ठा mlx5_अगरc_ste_mpls_v1_bits अणु
	u8         reserved_at_0[0x15];
	u8         mpls_ok[0x1];
	u8         mpls4_s_bit[0x1];
	u8         mpls4_qualअगरier[0x1];
	u8         mpls3_s_bit[0x1];
	u8         mpls3_qualअगरier[0x1];
	u8         mpls2_s_bit[0x1];
	u8         mpls2_qualअगरier[0x1];
	u8         mpls1_s_bit[0x1];
	u8         mpls1_qualअगरier[0x1];
	u8         mpls0_s_bit[0x1];
	u8         mpls0_qualअगरier[0x1];

	u8         mpls0_label[0x14];
	u8         mpls0_exp[0x3];
	u8         mpls0_s_bos[0x1];
	u8         mpls0_ttl[0x8];

	u8         mpls1_label[0x20];

	u8         mpls2_label[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_gre_v1_bits अणु
	u8         gre_c_present[0x1];
	u8         reserved_at_1[0x1];
	u8         gre_k_present[0x1];
	u8         gre_s_present[0x1];
	u8         strict_src_route[0x1];
	u8         recur[0x3];
	u8         flags[0x5];
	u8         version[0x3];
	u8         gre_protocol[0x10];

	u8         reserved_at_20[0x20];

	u8         gre_key_h[0x18];
	u8         gre_key_l[0x8];

	u8         reserved_at_60[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_src_gvmi_qp_v1_bits अणु
	u8         loopback_synd[0x8];
	u8         reserved_at_8[0x7];
	u8         functional_lb[0x1];
	u8         source_gvmi[0x10];

	u8         क्रमce_lb[0x1];
	u8         reserved_at_21[0x1];
	u8         source_is_requestor[0x1];
	u8         reserved_at_23[0x5];
	u8         source_qp[0x18];

	u8         reserved_at_40[0x20];

	u8         reserved_at_60[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_icmp_v1_bits अणु
	u8         icmp_payload_data[0x20];

	u8         icmp_header_data[0x20];

	u8         icmp_type[0x8];
	u8         icmp_code[0x8];
	u8         reserved_at_50[0x10];

	u8         reserved_at_60[0x20];
पूर्ण;

#पूर्ण_अगर /* MLX5_IFC_DR_STE_V1_H */
