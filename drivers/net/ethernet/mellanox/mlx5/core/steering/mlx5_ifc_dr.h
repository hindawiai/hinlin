<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019, Mellanox Technologies */

#अगर_अघोषित MLX5_IFC_DR_H
#घोषणा MLX5_IFC_DR_H

क्रमागत अणु
	MLX5DR_STE_LU_TYPE_DONT_CARE			= 0x0f,
पूर्ण;

क्रमागत mlx5dr_ste_entry_type अणु
	MLX5DR_STE_TYPE_TX		= 1,
	MLX5DR_STE_TYPE_RX		= 2,
	MLX5DR_STE_TYPE_MODIFY_PKT	= 6,
पूर्ण;

काष्ठा mlx5_अगरc_ste_general_bits अणु
	u8         entry_type[0x4];
	u8         reserved_at_4[0x4];
	u8         entry_sub_type[0x8];
	u8         byte_mask[0x10];

	u8         next_table_base_63_48[0x10];
	u8         next_lu_type[0x8];
	u8         next_table_base_39_32_size[0x8];

	u8         next_table_base_31_5_size[0x1b];
	u8         linear_hash_enable[0x1];
	u8         reserved_at_5c[0x2];
	u8         next_table_rank[0x2];

	u8         reserved_at_60[0xa0];
	u8         tag_value[0x60];
	u8         bit_mask[0x60];
पूर्ण;

काष्ठा mlx5_अगरc_ste_sx_transmit_bits अणु
	u8         entry_type[0x4];
	u8         reserved_at_4[0x4];
	u8         entry_sub_type[0x8];
	u8         byte_mask[0x10];

	u8         next_table_base_63_48[0x10];
	u8         next_lu_type[0x8];
	u8         next_table_base_39_32_size[0x8];

	u8         next_table_base_31_5_size[0x1b];
	u8         linear_hash_enable[0x1];
	u8         reserved_at_5c[0x2];
	u8         next_table_rank[0x2];

	u8         sx_wire[0x1];
	u8         sx_func_lb[0x1];
	u8         sx_snअगरfer[0x1];
	u8         sx_wire_enable[0x1];
	u8         sx_func_lb_enable[0x1];
	u8         sx_snअगरfer_enable[0x1];
	u8         action_type[0x3];
	u8         reserved_at_69[0x1];
	u8         action_description[0x6];
	u8         gvmi[0x10];

	u8         encap_poपूर्णांकer_vlan_data[0x20];

	u8         loopback_synकरोme_en[0x8];
	u8         loopback_synकरोme[0x8];
	u8         counter_trigger[0x10];

	u8         miss_address_63_48[0x10];
	u8         counter_trigger_23_16[0x8];
	u8         miss_address_39_32[0x8];

	u8         miss_address_31_6[0x1a];
	u8         learning_poपूर्णांक[0x1];
	u8         go_back[0x1];
	u8         match_polarity[0x1];
	u8         mask_mode[0x1];
	u8         miss_rank[0x2];
पूर्ण;

काष्ठा mlx5_अगरc_ste_rx_steering_mult_bits अणु
	u8         entry_type[0x4];
	u8         reserved_at_4[0x4];
	u8         entry_sub_type[0x8];
	u8         byte_mask[0x10];

	u8         next_table_base_63_48[0x10];
	u8         next_lu_type[0x8];
	u8         next_table_base_39_32_size[0x8];

	u8         next_table_base_31_5_size[0x1b];
	u8         linear_hash_enable[0x1];
	u8         reserved_at_[0x2];
	u8         next_table_rank[0x2];

	u8         member_count[0x10];
	u8         gvmi[0x10];

	u8         qp_list_poपूर्णांकer[0x20];

	u8         reserved_at_a0[0x1];
	u8         tunneling_action[0x3];
	u8         action_description[0x4];
	u8         reserved_at_a8[0x8];
	u8         counter_trigger_15_0[0x10];

	u8         miss_address_63_48[0x10];
	u8         counter_trigger_23_16[0x08];
	u8         miss_address_39_32[0x8];

	u8         miss_address_31_6[0x1a];
	u8         learning_poपूर्णांक[0x1];
	u8         fail_on_error[0x1];
	u8         match_polarity[0x1];
	u8         mask_mode[0x1];
	u8         miss_rank[0x2];
पूर्ण;

काष्ठा mlx5_अगरc_ste_modअगरy_packet_bits अणु
	u8         entry_type[0x4];
	u8         reserved_at_4[0x4];
	u8         entry_sub_type[0x8];
	u8         byte_mask[0x10];

	u8         next_table_base_63_48[0x10];
	u8         next_lu_type[0x8];
	u8         next_table_base_39_32_size[0x8];

	u8         next_table_base_31_5_size[0x1b];
	u8         linear_hash_enable[0x1];
	u8         reserved_at_[0x2];
	u8         next_table_rank[0x2];

	u8         number_of_re_ग_लिखो_actions[0x10];
	u8         gvmi[0x10];

	u8         header_re_ग_लिखो_actions_poपूर्णांकer[0x20];

	u8         reserved_at_a0[0x1];
	u8         tunneling_action[0x3];
	u8         action_description[0x4];
	u8         reserved_at_a8[0x8];
	u8         counter_trigger_15_0[0x10];

	u8         miss_address_63_48[0x10];
	u8         counter_trigger_23_16[0x08];
	u8         miss_address_39_32[0x8];

	u8         miss_address_31_6[0x1a];
	u8         learning_poपूर्णांक[0x1];
	u8         fail_on_error[0x1];
	u8         match_polarity[0x1];
	u8         mask_mode[0x1];
	u8         miss_rank[0x2];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l2_src_bits अणु
	u8         smac_47_16[0x20];

	u8         smac_15_0[0x10];
	u8         l3_ethertype[0x10];

	u8         qp_type[0x2];
	u8         ethertype_filter[0x1];
	u8         reserved_at_43[0x1];
	u8         sx_snअगरfer[0x1];
	u8         क्रमce_lb[0x1];
	u8         functional_lb[0x1];
	u8         port[0x1];
	u8         reserved_at_48[0x4];
	u8         first_priority[0x3];
	u8         first_cfi[0x1];
	u8         first_vlan_qualअगरier[0x2];
	u8         reserved_at_52[0x2];
	u8         first_vlan_id[0xc];

	u8         ip_fragmented[0x1];
	u8         tcp_syn[0x1];
	u8         encp_type[0x2];
	u8         l3_type[0x2];
	u8         l4_type[0x2];
	u8         reserved_at_68[0x4];
	u8         second_priority[0x3];
	u8         second_cfi[0x1];
	u8         second_vlan_qualअगरier[0x2];
	u8         reserved_at_72[0x2];
	u8         second_vlan_id[0xc];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l2_dst_bits अणु
	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         l3_ethertype[0x10];

	u8         qp_type[0x2];
	u8         ethertype_filter[0x1];
	u8         reserved_at_43[0x1];
	u8         sx_snअगरfer[0x1];
	u8         क्रमce_lb[0x1];
	u8         functional_lb[0x1];
	u8         port[0x1];
	u8         reserved_at_48[0x4];
	u8         first_priority[0x3];
	u8         first_cfi[0x1];
	u8         first_vlan_qualअगरier[0x2];
	u8         reserved_at_52[0x2];
	u8         first_vlan_id[0xc];

	u8         ip_fragmented[0x1];
	u8         tcp_syn[0x1];
	u8         encp_type[0x2];
	u8         l3_type[0x2];
	u8         l4_type[0x2];
	u8         reserved_at_68[0x4];
	u8         second_priority[0x3];
	u8         second_cfi[0x1];
	u8         second_vlan_qualअगरier[0x2];
	u8         reserved_at_72[0x2];
	u8         second_vlan_id[0xc];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l2_src_dst_bits अणु
	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         smac_47_32[0x10];

	u8         smac_31_0[0x20];

	u8         sx_snअगरfer[0x1];
	u8         क्रमce_lb[0x1];
	u8         functional_lb[0x1];
	u8         port[0x1];
	u8         l3_type[0x2];
	u8         reserved_at_66[0x6];
	u8         first_priority[0x3];
	u8         first_cfi[0x1];
	u8         first_vlan_qualअगरier[0x2];
	u8         reserved_at_72[0x2];
	u8         first_vlan_id[0xc];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l3_ipv4_5_tuple_bits अणु
	u8         destination_address[0x20];

	u8         source_address[0x20];

	u8         source_port[0x10];
	u8         destination_port[0x10];

	u8         fragmented[0x1];
	u8         first_fragment[0x1];
	u8         reserved_at_62[0x2];
	u8         reserved_at_64[0x1];
	u8         ecn[0x2];
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
	u8         reserved_at_76[0x2];
	u8         protocol[0x8];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l3_ipv6_dst_bits अणु
	u8         dst_ip_127_96[0x20];

	u8         dst_ip_95_64[0x20];

	u8         dst_ip_63_32[0x20];

	u8         dst_ip_31_0[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l2_tnl_bits अणु
	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         l3_ethertype[0x10];

	u8         l2_tunneling_network_id[0x20];

	u8         ip_fragmented[0x1];
	u8         tcp_syn[0x1];
	u8         encp_type[0x2];
	u8         l3_type[0x2];
	u8         l4_type[0x2];
	u8         first_priority[0x3];
	u8         first_cfi[0x1];
	u8         reserved_at_6c[0x3];
	u8         gre_key_flag[0x1];
	u8         first_vlan_qualअगरier[0x2];
	u8         reserved_at_72[0x2];
	u8         first_vlan_id[0xc];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l3_ipv6_src_bits अणु
	u8         src_ip_127_96[0x20];

	u8         src_ip_95_64[0x20];

	u8         src_ip_63_32[0x20];

	u8         src_ip_31_0[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l3_ipv4_misc_bits अणु
	u8         version[0x4];
	u8         ihl[0x4];
	u8         reserved_at_8[0x8];
	u8         total_length[0x10];

	u8         identअगरication[0x10];
	u8         flags[0x3];
	u8         fragment_offset[0xd];

	u8         समय_प्रकारo_live[0x8];
	u8         reserved_at_48[0x8];
	u8         checksum[0x10];

	u8         reserved_at_60[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l4_bits अणु
	u8         fragmented[0x1];
	u8         first_fragment[0x1];
	u8         reserved_at_2[0x6];
	u8         protocol[0x8];
	u8         dst_port[0x10];

	u8         ipv6_version[0x4];
	u8         reserved_at_24[0x1];
	u8         ecn[0x2];
	u8         tcp_ns[0x1];
	u8         tcp_cwr[0x1];
	u8         tcp_ece[0x1];
	u8         tcp_urg[0x1];
	u8         tcp_ack[0x1];
	u8         tcp_psh[0x1];
	u8         tcp_rst[0x1];
	u8         tcp_syn[0x1];
	u8         tcp_fin[0x1];
	u8         src_port[0x10];

	u8         ipv6_payload_length[0x10];
	u8         ipv6_hop_limit[0x8];
	u8         dscp[0x6];
	u8         reserved_at_5e[0x2];

	u8         tcp_data_offset[0x4];
	u8         reserved_at_64[0x8];
	u8         flow_label[0x14];
पूर्ण;

काष्ठा mlx5_अगरc_ste_eth_l4_misc_bits अणु
	u8         checksum[0x10];
	u8         length[0x10];

	u8         seq_num[0x20];

	u8         ack_num[0x20];

	u8         urgent_poपूर्णांकer[0x10];
	u8         winकरोw_size[0x10];
पूर्ण;

काष्ठा mlx5_अगरc_ste_mpls_bits अणु
	u8         mpls0_label[0x14];
	u8         mpls0_exp[0x3];
	u8         mpls0_s_bos[0x1];
	u8         mpls0_ttl[0x8];

	u8         mpls1_label[0x20];

	u8         mpls2_label[0x20];

	u8         reserved_at_60[0x16];
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
पूर्ण;

काष्ठा mlx5_अगरc_ste_रेजिस्टर_0_bits अणु
	u8         रेजिस्टर_0_h[0x20];

	u8         रेजिस्टर_0_l[0x20];

	u8         रेजिस्टर_1_h[0x20];

	u8         रेजिस्टर_1_l[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_रेजिस्टर_1_bits अणु
	u8         रेजिस्टर_2_h[0x20];

	u8         रेजिस्टर_2_l[0x20];

	u8         रेजिस्टर_3_h[0x20];

	u8         रेजिस्टर_3_l[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_gre_bits अणु
	u8         gre_c_present[0x1];
	u8         reserved_at_30[0x1];
	u8         gre_k_present[0x1];
	u8         gre_s_present[0x1];
	u8         strict_src_route[0x1];
	u8         recur[0x3];
	u8         flags[0x5];
	u8         version[0x3];
	u8         gre_protocol[0x10];

	u8         checksum[0x10];
	u8         offset[0x10];

	u8         gre_key_h[0x18];
	u8         gre_key_l[0x8];

	u8         seq_num[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_flex_parser_0_bits अणु
	u8         flex_parser_3[0x20];

	u8         flex_parser_2[0x20];

	u8         flex_parser_1[0x20];

	u8         flex_parser_0[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_flex_parser_1_bits अणु
	u8         flex_parser_7[0x20];

	u8         flex_parser_6[0x20];

	u8         flex_parser_5[0x20];

	u8         flex_parser_4[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_flex_parser_tnl_bits अणु
	u8         flex_parser_tunneling_header_63_32[0x20];

	u8         flex_parser_tunneling_header_31_0[0x20];

	u8         reserved_at_40[0x40];
पूर्ण;

काष्ठा mlx5_अगरc_ste_flex_parser_tnl_vxlan_gpe_bits अणु
	u8         outer_vxlan_gpe_flags[0x8];
	u8         reserved_at_8[0x10];
	u8         outer_vxlan_gpe_next_protocol[0x8];

	u8         outer_vxlan_gpe_vni[0x18];
	u8         reserved_at_38[0x8];

	u8         reserved_at_40[0x40];
पूर्ण;

काष्ठा mlx5_अगरc_ste_flex_parser_tnl_geneve_bits अणु
	u8         reserved_at_0[0x2];
	u8         geneve_opt_len[0x6];
	u8         geneve_oam[0x1];
	u8         reserved_at_9[0x7];
	u8         geneve_protocol_type[0x10];

	u8         geneve_vni[0x18];
	u8         reserved_at_38[0x8];

	u8         reserved_at_40[0x40];
पूर्ण;

काष्ठा mlx5_अगरc_ste_flex_parser_tnl_gtpu_bits अणु
	u8	   reserved_at_0[0x5];
	u8	   gtpu_msg_flags[0x3];
	u8	   gtpu_msg_type[0x8];
	u8	   reserved_at_10[0x10];

	u8	   gtpu_teid[0x20];

	u8	   reserved_at_40[0x40];
पूर्ण;

काष्ठा mlx5_अगरc_ste_general_purpose_bits अणु
	u8         general_purpose_lookup_field[0x20];

	u8         reserved_at_20[0x20];

	u8         reserved_at_40[0x20];

	u8         reserved_at_60[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_ste_src_gvmi_qp_bits अणु
	u8         loopback_syndrome[0x8];
	u8         reserved_at_8[0x8];
	u8         source_gvmi[0x10];

	u8         reserved_at_20[0x5];
	u8         क्रमce_lb[0x1];
	u8         functional_lb[0x1];
	u8         source_is_requestor[0x1];
	u8         source_qp[0x18];

	u8         reserved_at_40[0x20];

	u8         reserved_at_60[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_l2_hdr_bits अणु
	u8         dmac_47_16[0x20];

	u8         dmac_15_0[0x10];
	u8         smac_47_32[0x10];

	u8         smac_31_0[0x20];

	u8         ethertype[0x10];
	u8         vlan_type[0x10];

	u8         vlan[0x10];
	u8         reserved_at_90[0x10];
पूर्ण;

/* Both HW set and HW add share the same HW क्रमmat with dअगरferent opcodes */
काष्ठा mlx5_अगरc_dr_action_hw_set_bits अणु
	u8         opcode[0x8];
	u8         destination_field_code[0x8];
	u8         reserved_at_10[0x2];
	u8         destination_left_shअगरter[0x6];
	u8         reserved_at_18[0x3];
	u8         destination_length[0x5];

	u8         अंतरभूत_data[0x20];
पूर्ण;

काष्ठा mlx5_अगरc_dr_action_hw_copy_bits अणु
	u8         opcode[0x8];
	u8         destination_field_code[0x8];
	u8         reserved_at_10[0x2];
	u8         destination_left_shअगरter[0x6];
	u8         reserved_at_18[0x2];
	u8         destination_length[0x6];

	u8         reserved_at_20[0x8];
	u8         source_field_code[0x8];
	u8         reserved_at_30[0x2];
	u8         source_left_shअगरter[0x6];
	u8         reserved_at_38[0x8];
पूर्ण;

#पूर्ण_अगर /* MLX5_IFC_DR_H */
