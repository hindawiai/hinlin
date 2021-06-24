<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/* Copyright (c) 2019, Mellanox Technologies */

#अगर_अघोषित _MLX5DR_H_
#घोषणा _MLX5DR_H_

काष्ठा mlx5dr_करोमुख्य;
काष्ठा mlx5dr_table;
काष्ठा mlx5dr_matcher;
काष्ठा mlx5dr_rule;
काष्ठा mlx5dr_action;

क्रमागत mlx5dr_करोमुख्य_type अणु
	MLX5DR_DOMAIN_TYPE_NIC_RX,
	MLX5DR_DOMAIN_TYPE_NIC_TX,
	MLX5DR_DOMAIN_TYPE_FDB,
पूर्ण;

क्रमागत mlx5dr_करोमुख्य_sync_flags अणु
	MLX5DR_DOMAIN_SYNC_FLAGS_SW = 1 << 0,
	MLX5DR_DOMAIN_SYNC_FLAGS_HW = 1 << 1,
पूर्ण;

क्रमागत mlx5dr_action_reक्रमmat_type अणु
	DR_ACTION_REFORMAT_TYP_TNL_L2_TO_L2,
	DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L2,
	DR_ACTION_REFORMAT_TYP_TNL_L3_TO_L2,
	DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L3,
पूर्ण;

काष्ठा mlx5dr_match_parameters अणु
	माप_प्रकार match_sz;
	u64 *match_buf; /* Device spec क्रमmat */
पूर्ण;

काष्ठा mlx5dr_action_dest अणु
	काष्ठा mlx5dr_action *dest;
	काष्ठा mlx5dr_action *reक्रमmat;
पूर्ण;

काष्ठा mlx5dr_करोमुख्य *
mlx5dr_करोमुख्य_create(काष्ठा mlx5_core_dev *mdev, क्रमागत mlx5dr_करोमुख्य_type type);

पूर्णांक mlx5dr_करोमुख्य_destroy(काष्ठा mlx5dr_करोमुख्य *करोमुख्य);

पूर्णांक mlx5dr_करोमुख्य_sync(काष्ठा mlx5dr_करोमुख्य *करोमुख्य, u32 flags);

व्योम mlx5dr_करोमुख्य_set_peer(काष्ठा mlx5dr_करोमुख्य *dmn,
			    काष्ठा mlx5dr_करोमुख्य *peer_dmn);

काष्ठा mlx5dr_table *
mlx5dr_table_create(काष्ठा mlx5dr_करोमुख्य *करोमुख्य, u32 level, u32 flags);

पूर्णांक mlx5dr_table_destroy(काष्ठा mlx5dr_table *table);

u32 mlx5dr_table_get_id(काष्ठा mlx5dr_table *table);

काष्ठा mlx5dr_matcher *
mlx5dr_matcher_create(काष्ठा mlx5dr_table *table,
		      u32 priority,
		      u8 match_criteria_enable,
		      काष्ठा mlx5dr_match_parameters *mask);

पूर्णांक mlx5dr_matcher_destroy(काष्ठा mlx5dr_matcher *matcher);

काष्ठा mlx5dr_rule *
mlx5dr_rule_create(काष्ठा mlx5dr_matcher *matcher,
		   काष्ठा mlx5dr_match_parameters *value,
		   माप_प्रकार num_actions,
		   काष्ठा mlx5dr_action *actions[],
		   u32 flow_source);

पूर्णांक mlx5dr_rule_destroy(काष्ठा mlx5dr_rule *rule);

पूर्णांक mlx5dr_table_set_miss_action(काष्ठा mlx5dr_table *tbl,
				 काष्ठा mlx5dr_action *action);

काष्ठा mlx5dr_action *
mlx5dr_action_create_dest_table_num(काष्ठा mlx5dr_करोमुख्य *dmn, u32 table_num);

काष्ठा mlx5dr_action *
mlx5dr_action_create_dest_table(काष्ठा mlx5dr_table *table);

काष्ठा mlx5dr_action *
mlx5dr_action_create_dest_flow_fw_table(काष्ठा mlx5dr_करोमुख्य *करोमुख्य,
					काष्ठा mlx5_flow_table *ft);

काष्ठा mlx5dr_action *
mlx5dr_action_create_dest_vport(काष्ठा mlx5dr_करोमुख्य *करोमुख्य,
				u32 vport, u8 vhca_id_valid,
				u16 vhca_id);

काष्ठा mlx5dr_action *
mlx5dr_action_create_mult_dest_tbl(काष्ठा mlx5dr_करोमुख्य *dmn,
				   काष्ठा mlx5dr_action_dest *dests,
				   u32 num_of_dests);

काष्ठा mlx5dr_action *mlx5dr_action_create_drop(व्योम);

काष्ठा mlx5dr_action *mlx5dr_action_create_tag(u32 tag_value);

काष्ठा mlx5dr_action *
mlx5dr_action_create_flow_counter(u32 counter_id);

काष्ठा mlx5dr_action *
mlx5dr_action_create_packet_reक्रमmat(काष्ठा mlx5dr_करोमुख्य *dmn,
				     क्रमागत mlx5dr_action_reक्रमmat_type reक्रमmat_type,
				     माप_प्रकार data_sz,
				     व्योम *data);

काष्ठा mlx5dr_action *
mlx5dr_action_create_modअगरy_header(काष्ठा mlx5dr_करोमुख्य *करोमुख्य,
				   u32 flags,
				   माप_प्रकार actions_sz,
				   __be64 actions[]);

काष्ठा mlx5dr_action *mlx5dr_action_create_pop_vlan(व्योम);

काष्ठा mlx5dr_action *
mlx5dr_action_create_push_vlan(काष्ठा mlx5dr_करोमुख्य *करोमुख्य, __be32 vlan_hdr);

पूर्णांक mlx5dr_action_destroy(काष्ठा mlx5dr_action *action);

अटल अंतरभूत bool
mlx5dr_is_supported(काष्ठा mlx5_core_dev *dev)
अणु
	वापस MLX5_CAP_GEN(dev, roce) &&
	       (MLX5_CAP_ESW_FLOWTABLE_FDB(dev, sw_owner) ||
		(MLX5_CAP_ESW_FLOWTABLE_FDB(dev, sw_owner_v2) &&
		 (MLX5_CAP_GEN(dev, steering_क्रमmat_version) <=
		  MLX5_STEERING_FORMAT_CONNECTX_6DX)));
पूर्ण

/* buddy functions & काष्ठाure */

काष्ठा mlx5dr_icm_mr;

काष्ठा mlx5dr_icm_buddy_mem अणु
	अचिन्हित दीर्घ		**biपंचांगap;
	अचिन्हित पूर्णांक		*num_मुक्त;
	u32			max_order;
	काष्ठा list_head	list_node;
	काष्ठा mlx5dr_icm_mr	*icm_mr;
	काष्ठा mlx5dr_icm_pool	*pool;

	/* This is the list of used chunks. HW may be accessing this memory */
	काष्ठा list_head	used_list;
	u64			used_memory;

	/* Hardware may be accessing this memory but at some future,
	 * undetermined समय, it might cease to करो so.
	 * sync_ste command sets them मुक्त.
	 */
	काष्ठा list_head	hot_list;
पूर्ण;

पूर्णांक mlx5dr_buddy_init(काष्ठा mlx5dr_icm_buddy_mem *buddy,
		      अचिन्हित पूर्णांक max_order);
व्योम mlx5dr_buddy_cleanup(काष्ठा mlx5dr_icm_buddy_mem *buddy);
पूर्णांक mlx5dr_buddy_alloc_mem(काष्ठा mlx5dr_icm_buddy_mem *buddy,
			   अचिन्हित पूर्णांक order,
			   अचिन्हित पूर्णांक *segment);
व्योम mlx5dr_buddy_मुक्त_mem(काष्ठा mlx5dr_icm_buddy_mem *buddy,
			   अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक order);

#पूर्ण_अगर /* _MLX5DR_H_ */
