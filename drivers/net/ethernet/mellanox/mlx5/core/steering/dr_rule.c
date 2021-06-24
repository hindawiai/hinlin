<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "dr_types.h"

#घोषणा DR_RULE_MAX_STE_CHAIN (DR_RULE_MAX_STES + DR_ACTION_MAX_STES)

काष्ठा mlx5dr_rule_action_member अणु
	काष्ठा mlx5dr_action *action;
	काष्ठा list_head list;
पूर्ण;

अटल पूर्णांक dr_rule_append_to_miss_list(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				       काष्ठा mlx5dr_ste *new_last_ste,
				       काष्ठा list_head *miss_list,
				       काष्ठा list_head *send_list)
अणु
	काष्ठा mlx5dr_ste_send_info *ste_info_last;
	काष्ठा mlx5dr_ste *last_ste;

	/* The new entry will be inserted after the last */
	last_ste = list_last_entry(miss_list, काष्ठा mlx5dr_ste, miss_list_node);
	WARN_ON(!last_ste);

	ste_info_last = kzalloc(माप(*ste_info_last), GFP_KERNEL);
	अगर (!ste_info_last)
		वापस -ENOMEM;

	mlx5dr_ste_set_miss_addr(ste_ctx, last_ste->hw_ste,
				 mlx5dr_ste_get_icm_addr(new_last_ste));
	list_add_tail(&new_last_ste->miss_list_node, miss_list);

	mlx5dr_send_fill_and_append_ste_send_info(last_ste, DR_STE_SIZE_CTRL,
						  0, last_ste->hw_ste,
						  ste_info_last, send_list, true);

	वापस 0;
पूर्ण

अटल काष्ठा mlx5dr_ste *
dr_rule_create_collision_htbl(काष्ठा mlx5dr_matcher *matcher,
			      काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
			      u8 *hw_ste)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_ste_ctx *ste_ctx = dmn->ste_ctx;
	काष्ठा mlx5dr_ste_htbl *new_htbl;
	काष्ठा mlx5dr_ste *ste;

	/* Create new table क्रम miss entry */
	new_htbl = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
					 DR_CHUNK_SIZE_1,
					 MLX5DR_STE_LU_TYPE_DONT_CARE,
					 0);
	अगर (!new_htbl) अणु
		mlx5dr_dbg(dmn, "Failed allocating collision table\n");
		वापस शून्य;
	पूर्ण

	/* One and only entry, never grows */
	ste = new_htbl->ste_arr;
	mlx5dr_ste_set_miss_addr(ste_ctx, hw_ste,
				 nic_matcher->e_anchor->chunk->icm_addr);
	mlx5dr_htbl_get(new_htbl);

	वापस ste;
पूर्ण

अटल काष्ठा mlx5dr_ste *
dr_rule_create_collision_entry(काष्ठा mlx5dr_matcher *matcher,
			       काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
			       u8 *hw_ste,
			       काष्ठा mlx5dr_ste *orig_ste)
अणु
	काष्ठा mlx5dr_ste *ste;

	ste = dr_rule_create_collision_htbl(matcher, nic_matcher, hw_ste);
	अगर (!ste) अणु
		mlx5dr_dbg(matcher->tbl->dmn, "Failed creating collision entry\n");
		वापस शून्य;
	पूर्ण

	ste->ste_chain_location = orig_ste->ste_chain_location;

	/* In collision entry, all members share the same miss_list_head */
	ste->htbl->miss_list = mlx5dr_ste_get_miss_list(orig_ste);

	/* Next table */
	अगर (mlx5dr_ste_create_next_htbl(matcher, nic_matcher, ste, hw_ste,
					DR_CHUNK_SIZE_1)) अणु
		mlx5dr_dbg(matcher->tbl->dmn, "Failed allocating table\n");
		जाओ मुक्त_tbl;
	पूर्ण

	वापस ste;

मुक्त_tbl:
	mlx5dr_ste_मुक्त(ste, matcher, nic_matcher);
	वापस शून्य;
पूर्ण

अटल पूर्णांक
dr_rule_handle_one_ste_in_update_list(काष्ठा mlx5dr_ste_send_info *ste_info,
				      काष्ठा mlx5dr_करोमुख्य *dmn)
अणु
	पूर्णांक ret;

	list_del(&ste_info->send_list);

	/* Copy data to ste, only reduced size or control, the last 16B (mask)
	 * is alपढ़ोy written to the hw.
	 */
	अगर (ste_info->size == DR_STE_SIZE_CTRL)
		स_नकल(ste_info->ste->hw_ste, ste_info->data, DR_STE_SIZE_CTRL);
	अन्यथा
		स_नकल(ste_info->ste->hw_ste, ste_info->data, DR_STE_SIZE_REDUCED);

	ret = mlx5dr_send_postsend_ste(dmn, ste_info->ste, ste_info->data,
				       ste_info->size, ste_info->offset);
	अगर (ret)
		जाओ out;

out:
	kमुक्त(ste_info);
	वापस ret;
पूर्ण

अटल पूर्णांक dr_rule_send_update_list(काष्ठा list_head *send_ste_list,
				    काष्ठा mlx5dr_करोमुख्य *dmn,
				    bool is_reverse)
अणु
	काष्ठा mlx5dr_ste_send_info *ste_info, *पंचांगp_ste_info;
	पूर्णांक ret;

	अगर (is_reverse) अणु
		list_क्रम_each_entry_safe_reverse(ste_info, पंचांगp_ste_info,
						 send_ste_list, send_list) अणु
			ret = dr_rule_handle_one_ste_in_update_list(ste_info,
								    dmn);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_safe(ste_info, पंचांगp_ste_info,
					 send_ste_list, send_list) अणु
			ret = dr_rule_handle_one_ste_in_update_list(ste_info,
								    dmn);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mlx5dr_ste *
dr_rule_find_ste_in_miss_list(काष्ठा list_head *miss_list, u8 *hw_ste)
अणु
	काष्ठा mlx5dr_ste *ste;

	अगर (list_empty(miss_list))
		वापस शून्य;

	/* Check अगर hw_ste is present in the list */
	list_क्रम_each_entry(ste, miss_list, miss_list_node) अणु
		अगर (mlx5dr_ste_equal_tag(ste->hw_ste, hw_ste))
			वापस ste;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mlx5dr_ste *
dr_rule_rehash_handle_collision(काष्ठा mlx5dr_matcher *matcher,
				काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				काष्ठा list_head *update_list,
				काष्ठा mlx5dr_ste *col_ste,
				u8 *hw_ste)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_ste *new_ste;
	पूर्णांक ret;

	new_ste = dr_rule_create_collision_htbl(matcher, nic_matcher, hw_ste);
	अगर (!new_ste)
		वापस शून्य;

	/* In collision entry, all members share the same miss_list_head */
	new_ste->htbl->miss_list = mlx5dr_ste_get_miss_list(col_ste);

	/* Update the previous from the list */
	ret = dr_rule_append_to_miss_list(dmn->ste_ctx, new_ste,
					  mlx5dr_ste_get_miss_list(col_ste),
					  update_list);
	अगर (ret) अणु
		mlx5dr_dbg(dmn, "Failed update dup entry\n");
		जाओ err_निकास;
	पूर्ण

	वापस new_ste;

err_निकास:
	mlx5dr_ste_मुक्त(new_ste, matcher, nic_matcher);
	वापस शून्य;
पूर्ण

अटल व्योम dr_rule_rehash_copy_ste_ctrl(काष्ठा mlx5dr_matcher *matcher,
					 काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
					 काष्ठा mlx5dr_ste *cur_ste,
					 काष्ठा mlx5dr_ste *new_ste)
अणु
	new_ste->next_htbl = cur_ste->next_htbl;
	new_ste->ste_chain_location = cur_ste->ste_chain_location;

	अगर (!mlx5dr_ste_is_last_in_rule(nic_matcher, new_ste->ste_chain_location))
		new_ste->next_htbl->poपूर्णांकing_ste = new_ste;

	/* We need to copy the refcount since this ste
	 * may have been traversed several बार
	 */
	new_ste->refcount = cur_ste->refcount;

	/* Link old STEs rule_mem list to the new ste */
	mlx5dr_rule_update_rule_member(cur_ste, new_ste);
	INIT_LIST_HEAD(&new_ste->rule_list);
	list_splice_tail_init(&cur_ste->rule_list, &new_ste->rule_list);
पूर्ण

अटल काष्ठा mlx5dr_ste *
dr_rule_rehash_copy_ste(काष्ठा mlx5dr_matcher *matcher,
			काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
			काष्ठा mlx5dr_ste *cur_ste,
			काष्ठा mlx5dr_ste_htbl *new_htbl,
			काष्ठा list_head *update_list)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_ste_send_info *ste_info;
	bool use_update_list = false;
	u8 hw_ste[DR_STE_SIZE] = अणुपूर्ण;
	काष्ठा mlx5dr_ste *new_ste;
	पूर्णांक new_idx;
	u8 sb_idx;

	/* Copy STE mask from the matcher */
	sb_idx = cur_ste->ste_chain_location - 1;
	mlx5dr_ste_set_bit_mask(hw_ste, nic_matcher->ste_builder[sb_idx].bit_mask);

	/* Copy STE control and tag */
	स_नकल(hw_ste, cur_ste->hw_ste, DR_STE_SIZE_REDUCED);
	mlx5dr_ste_set_miss_addr(dmn->ste_ctx, hw_ste,
				 nic_matcher->e_anchor->chunk->icm_addr);

	new_idx = mlx5dr_ste_calc_hash_index(hw_ste, new_htbl);
	new_ste = &new_htbl->ste_arr[new_idx];

	अगर (mlx5dr_ste_is_not_used(new_ste)) अणु
		mlx5dr_htbl_get(new_htbl);
		list_add_tail(&new_ste->miss_list_node,
			      mlx5dr_ste_get_miss_list(new_ste));
	पूर्ण अन्यथा अणु
		new_ste = dr_rule_rehash_handle_collision(matcher,
							  nic_matcher,
							  update_list,
							  new_ste,
							  hw_ste);
		अगर (!new_ste) अणु
			mlx5dr_dbg(dmn, "Failed adding collision entry, index: %d\n",
				   new_idx);
			वापस शून्य;
		पूर्ण
		new_htbl->ctrl.num_of_collisions++;
		use_update_list = true;
	पूर्ण

	स_नकल(new_ste->hw_ste, hw_ste, DR_STE_SIZE_REDUCED);

	new_htbl->ctrl.num_of_valid_entries++;

	अगर (use_update_list) अणु
		ste_info = kzalloc(माप(*ste_info), GFP_KERNEL);
		अगर (!ste_info)
			जाओ err_निकास;

		mlx5dr_send_fill_and_append_ste_send_info(new_ste, DR_STE_SIZE, 0,
							  hw_ste, ste_info,
							  update_list, true);
	पूर्ण

	dr_rule_rehash_copy_ste_ctrl(matcher, nic_matcher, cur_ste, new_ste);

	वापस new_ste;

err_निकास:
	mlx5dr_ste_मुक्त(new_ste, matcher, nic_matcher);
	वापस शून्य;
पूर्ण

अटल पूर्णांक dr_rule_rehash_copy_miss_list(काष्ठा mlx5dr_matcher *matcher,
					 काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
					 काष्ठा list_head *cur_miss_list,
					 काष्ठा mlx5dr_ste_htbl *new_htbl,
					 काष्ठा list_head *update_list)
अणु
	काष्ठा mlx5dr_ste *पंचांगp_ste, *cur_ste, *new_ste;

	अगर (list_empty(cur_miss_list))
		वापस 0;

	list_क्रम_each_entry_safe(cur_ste, पंचांगp_ste, cur_miss_list, miss_list_node) अणु
		new_ste = dr_rule_rehash_copy_ste(matcher,
						  nic_matcher,
						  cur_ste,
						  new_htbl,
						  update_list);
		अगर (!new_ste)
			जाओ err_insert;

		list_del(&cur_ste->miss_list_node);
		mlx5dr_htbl_put(cur_ste->htbl);
	पूर्ण
	वापस 0;

err_insert:
	mlx5dr_err(matcher->tbl->dmn, "Fatal error during resize\n");
	WARN_ON(true);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dr_rule_rehash_copy_htbl(काष्ठा mlx5dr_matcher *matcher,
				    काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				    काष्ठा mlx5dr_ste_htbl *cur_htbl,
				    काष्ठा mlx5dr_ste_htbl *new_htbl,
				    काष्ठा list_head *update_list)
अणु
	काष्ठा mlx5dr_ste *cur_ste;
	पूर्णांक cur_entries;
	पूर्णांक err = 0;
	पूर्णांक i;

	cur_entries = mlx5dr_icm_pool_chunk_माप_प्रकारo_entries(cur_htbl->chunk_size);

	अगर (cur_entries < 1) अणु
		mlx5dr_dbg(matcher->tbl->dmn, "Invalid number of entries\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < cur_entries; i++) अणु
		cur_ste = &cur_htbl->ste_arr[i];
		अगर (mlx5dr_ste_is_not_used(cur_ste)) /* Empty, nothing to copy */
			जारी;

		err = dr_rule_rehash_copy_miss_list(matcher,
						    nic_matcher,
						    mlx5dr_ste_get_miss_list(cur_ste),
						    new_htbl,
						    update_list);
		अगर (err)
			जाओ clean_copy;
	पूर्ण

clean_copy:
	वापस err;
पूर्ण

अटल काष्ठा mlx5dr_ste_htbl *
dr_rule_rehash_htbl(काष्ठा mlx5dr_rule *rule,
		    काष्ठा mlx5dr_rule_rx_tx *nic_rule,
		    काष्ठा mlx5dr_ste_htbl *cur_htbl,
		    u8 ste_location,
		    काष्ठा list_head *update_list,
		    क्रमागत mlx5dr_icm_chunk_size new_size)
अणु
	काष्ठा mlx5dr_ste_send_info *del_ste_info, *पंचांगp_ste_info;
	काष्ठा mlx5dr_matcher *matcher = rule->matcher;
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_matcher_rx_tx *nic_matcher;
	काष्ठा mlx5dr_ste_send_info *ste_info;
	काष्ठा mlx5dr_htbl_connect_info info;
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn;
	u8 क्रमmatted_ste[DR_STE_SIZE] = अणुपूर्ण;
	LIST_HEAD(rehash_table_send_list);
	काष्ठा mlx5dr_ste *ste_to_update;
	काष्ठा mlx5dr_ste_htbl *new_htbl;
	पूर्णांक err;

	nic_matcher = nic_rule->nic_matcher;
	nic_dmn = nic_matcher->nic_tbl->nic_dmn;

	ste_info = kzalloc(माप(*ste_info), GFP_KERNEL);
	अगर (!ste_info)
		वापस शून्य;

	new_htbl = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
					 new_size,
					 cur_htbl->lu_type,
					 cur_htbl->byte_mask);
	अगर (!new_htbl) अणु
		mlx5dr_err(dmn, "Failed to allocate new hash table\n");
		जाओ मुक्त_ste_info;
	पूर्ण

	/* Write new table to HW */
	info.type = CONNECT_MISS;
	info.miss_icm_addr = nic_matcher->e_anchor->chunk->icm_addr;
	mlx5dr_ste_set_क्रमmatted_ste(dmn->ste_ctx,
				     dmn->info.caps.gvmi,
				     nic_dmn,
				     new_htbl,
				     क्रमmatted_ste,
				     &info);

	new_htbl->poपूर्णांकing_ste = cur_htbl->poपूर्णांकing_ste;
	new_htbl->poपूर्णांकing_ste->next_htbl = new_htbl;
	err = dr_rule_rehash_copy_htbl(matcher,
				       nic_matcher,
				       cur_htbl,
				       new_htbl,
				       &rehash_table_send_list);
	अगर (err)
		जाओ मुक्त_new_htbl;

	अगर (mlx5dr_send_postsend_htbl(dmn, new_htbl, क्रमmatted_ste,
				      nic_matcher->ste_builder[ste_location - 1].bit_mask)) अणु
		mlx5dr_err(dmn, "Failed writing table to HW\n");
		जाओ मुक्त_new_htbl;
	पूर्ण

	/* Writing to the hw is करोne in regular order of rehash_table_send_list,
	 * in order to have the origin data written beक्रमe the miss address of
	 * collision entries, अगर exists.
	 */
	अगर (dr_rule_send_update_list(&rehash_table_send_list, dmn, false)) अणु
		mlx5dr_err(dmn, "Failed updating table to HW\n");
		जाओ मुक्त_ste_list;
	पूर्ण

	/* Connect previous hash table to current */
	अगर (ste_location == 1) अणु
		/* The previous table is an anchor, anchors size is always one STE */
		काष्ठा mlx5dr_ste_htbl *prev_htbl = cur_htbl->poपूर्णांकing_ste->htbl;

		/* On matcher s_anchor we keep an extra refcount */
		mlx5dr_htbl_get(new_htbl);
		mlx5dr_htbl_put(cur_htbl);

		nic_matcher->s_htbl = new_htbl;

		/* It is safe to operate dr_ste_set_hit_addr on the hw_ste here
		 * (48B len) which works only on first 32B
		 */
		mlx5dr_ste_set_hit_addr(dmn->ste_ctx,
					prev_htbl->ste_arr[0].hw_ste,
					new_htbl->chunk->icm_addr,
					new_htbl->chunk->num_of_entries);

		ste_to_update = &prev_htbl->ste_arr[0];
	पूर्ण अन्यथा अणु
		mlx5dr_ste_set_hit_addr_by_next_htbl(dmn->ste_ctx,
						     cur_htbl->poपूर्णांकing_ste->hw_ste,
						     new_htbl);
		ste_to_update = cur_htbl->poपूर्णांकing_ste;
	पूर्ण

	mlx5dr_send_fill_and_append_ste_send_info(ste_to_update, DR_STE_SIZE_CTRL,
						  0, ste_to_update->hw_ste, ste_info,
						  update_list, false);

	वापस new_htbl;

मुक्त_ste_list:
	/* Clean all ste_info's from the new table */
	list_क्रम_each_entry_safe(del_ste_info, पंचांगp_ste_info,
				 &rehash_table_send_list, send_list) अणु
		list_del(&del_ste_info->send_list);
		kमुक्त(del_ste_info);
	पूर्ण

मुक्त_new_htbl:
	mlx5dr_ste_htbl_मुक्त(new_htbl);
मुक्त_ste_info:
	kमुक्त(ste_info);
	mlx5dr_info(dmn, "Failed creating rehash table\n");
	वापस शून्य;
पूर्ण

अटल काष्ठा mlx5dr_ste_htbl *dr_rule_rehash(काष्ठा mlx5dr_rule *rule,
					      काष्ठा mlx5dr_rule_rx_tx *nic_rule,
					      काष्ठा mlx5dr_ste_htbl *cur_htbl,
					      u8 ste_location,
					      काष्ठा list_head *update_list)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = rule->matcher->tbl->dmn;
	क्रमागत mlx5dr_icm_chunk_size new_size;

	new_size = mlx5dr_icm_next_higher_chunk(cur_htbl->chunk_size);
	new_size = min_t(u32, new_size, dmn->info.max_log_sw_icm_sz);

	अगर (new_size == cur_htbl->chunk_size)
		वापस शून्य; /* Skip rehash, we alपढ़ोy at the max size */

	वापस dr_rule_rehash_htbl(rule, nic_rule, cur_htbl, ste_location,
				   update_list, new_size);
पूर्ण

अटल काष्ठा mlx5dr_ste *
dr_rule_handle_collision(काष्ठा mlx5dr_matcher *matcher,
			 काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
			 काष्ठा mlx5dr_ste *ste,
			 u8 *hw_ste,
			 काष्ठा list_head *miss_list,
			 काष्ठा list_head *send_list)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_ste_ctx *ste_ctx = dmn->ste_ctx;
	काष्ठा mlx5dr_ste_send_info *ste_info;
	काष्ठा mlx5dr_ste *new_ste;

	ste_info = kzalloc(माप(*ste_info), GFP_KERNEL);
	अगर (!ste_info)
		वापस शून्य;

	new_ste = dr_rule_create_collision_entry(matcher, nic_matcher, hw_ste, ste);
	अगर (!new_ste)
		जाओ मुक्त_send_info;

	अगर (dr_rule_append_to_miss_list(ste_ctx, new_ste,
					miss_list, send_list)) अणु
		mlx5dr_dbg(dmn, "Failed to update prev miss_list\n");
		जाओ err_निकास;
	पूर्ण

	mlx5dr_send_fill_and_append_ste_send_info(new_ste, DR_STE_SIZE, 0, hw_ste,
						  ste_info, send_list, false);

	ste->htbl->ctrl.num_of_collisions++;
	ste->htbl->ctrl.num_of_valid_entries++;

	वापस new_ste;

err_निकास:
	mlx5dr_ste_मुक्त(new_ste, matcher, nic_matcher);
मुक्त_send_info:
	kमुक्त(ste_info);
	वापस शून्य;
पूर्ण

अटल व्योम dr_rule_हटाओ_action_members(काष्ठा mlx5dr_rule *rule)
अणु
	काष्ठा mlx5dr_rule_action_member *action_mem;
	काष्ठा mlx5dr_rule_action_member *पंचांगp;

	list_क्रम_each_entry_safe(action_mem, पंचांगp, &rule->rule_actions_list, list) अणु
		list_del(&action_mem->list);
		refcount_dec(&action_mem->action->refcount);
		kvमुक्त(action_mem);
	पूर्ण
पूर्ण

अटल पूर्णांक dr_rule_add_action_members(काष्ठा mlx5dr_rule *rule,
				      माप_प्रकार num_actions,
				      काष्ठा mlx5dr_action *actions[])
अणु
	काष्ठा mlx5dr_rule_action_member *action_mem;
	पूर्णांक i;

	क्रम (i = 0; i < num_actions; i++) अणु
		action_mem = kvzalloc(माप(*action_mem), GFP_KERNEL);
		अगर (!action_mem)
			जाओ मुक्त_action_members;

		action_mem->action = actions[i];
		INIT_LIST_HEAD(&action_mem->list);
		list_add_tail(&action_mem->list, &rule->rule_actions_list);
		refcount_inc(&action_mem->action->refcount);
	पूर्ण

	वापस 0;

मुक्त_action_members:
	dr_rule_हटाओ_action_members(rule);
	वापस -ENOMEM;
पूर्ण

/* While the poपूर्णांकer of ste is no दीर्घer valid, like जबतक moving ste to be
 * the first in the miss_list, and to be in the origin table,
 * all rule-members that are attached to this ste should update their ste member
 * to the new poपूर्णांकer
 */
व्योम mlx5dr_rule_update_rule_member(काष्ठा mlx5dr_ste *ste,
				    काष्ठा mlx5dr_ste *new_ste)
अणु
	काष्ठा mlx5dr_rule_member *rule_mem;

	list_क्रम_each_entry(rule_mem, &ste->rule_list, use_ste_list)
		rule_mem->ste = new_ste;
पूर्ण

अटल व्योम dr_rule_clean_rule_members(काष्ठा mlx5dr_rule *rule,
				       काष्ठा mlx5dr_rule_rx_tx *nic_rule)
अणु
	काष्ठा mlx5dr_rule_member *rule_mem;
	काष्ठा mlx5dr_rule_member *पंचांगp_mem;

	अगर (list_empty(&nic_rule->rule_members_list))
		वापस;
	list_क्रम_each_entry_safe(rule_mem, पंचांगp_mem, &nic_rule->rule_members_list, list) अणु
		list_del(&rule_mem->list);
		list_del(&rule_mem->use_ste_list);
		mlx5dr_ste_put(rule_mem->ste, rule->matcher, nic_rule->nic_matcher);
		kvमुक्त(rule_mem);
	पूर्ण
पूर्ण

अटल u16 dr_get_bits_per_mask(u16 byte_mask)
अणु
	u16 bits = 0;

	जबतक (byte_mask) अणु
		byte_mask = byte_mask & (byte_mask - 1);
		bits++;
	पूर्ण

	वापस bits;
पूर्ण

अटल bool dr_rule_need_enlarge_hash(काष्ठा mlx5dr_ste_htbl *htbl,
				      काष्ठा mlx5dr_करोमुख्य *dmn,
				      काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn)
अणु
	काष्ठा mlx5dr_ste_htbl_ctrl *ctrl = &htbl->ctrl;

	अगर (dmn->info.max_log_sw_icm_sz <= htbl->chunk_size)
		वापस false;

	अगर (!ctrl->may_grow)
		वापस false;

	अगर (dr_get_bits_per_mask(htbl->byte_mask) * BITS_PER_BYTE <= htbl->chunk_size)
		वापस false;

	अगर (ctrl->num_of_collisions >= ctrl->increase_threshold &&
	    (ctrl->num_of_valid_entries - ctrl->num_of_collisions) >= ctrl->increase_threshold)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक dr_rule_add_member(काष्ठा mlx5dr_rule_rx_tx *nic_rule,
			      काष्ठा mlx5dr_ste *ste)
अणु
	काष्ठा mlx5dr_rule_member *rule_mem;

	rule_mem = kvzalloc(माप(*rule_mem), GFP_KERNEL);
	अगर (!rule_mem)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&rule_mem->list);
	INIT_LIST_HEAD(&rule_mem->use_ste_list);

	rule_mem->ste = ste;
	list_add_tail(&rule_mem->list, &nic_rule->rule_members_list);

	list_add_tail(&rule_mem->use_ste_list, &ste->rule_list);

	वापस 0;
पूर्ण

अटल पूर्णांक dr_rule_handle_action_stes(काष्ठा mlx5dr_rule *rule,
				      काष्ठा mlx5dr_rule_rx_tx *nic_rule,
				      काष्ठा list_head *send_ste_list,
				      काष्ठा mlx5dr_ste *last_ste,
				      u8 *hw_ste_arr,
				      u32 new_hw_ste_arr_sz)
अणु
	काष्ठा mlx5dr_matcher_rx_tx *nic_matcher = nic_rule->nic_matcher;
	काष्ठा mlx5dr_ste_send_info *ste_info_arr[DR_ACTION_MAX_STES];
	u8 num_of_builders = nic_matcher->num_of_builders;
	काष्ठा mlx5dr_matcher *matcher = rule->matcher;
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	u8 *curr_hw_ste, *prev_hw_ste;
	काष्ठा mlx5dr_ste *action_ste;
	पूर्णांक i, k, ret;

	/* Two हालs:
	 * 1. num_of_builders is equal to new_hw_ste_arr_sz, the action in the ste
	 * 2. num_of_builders is less then new_hw_ste_arr_sz, new ste was added
	 *    to support the action.
	 */
	अगर (num_of_builders == new_hw_ste_arr_sz)
		वापस 0;

	क्रम (i = num_of_builders, k = 0; i < new_hw_ste_arr_sz; i++, k++) अणु
		curr_hw_ste = hw_ste_arr + i * DR_STE_SIZE;
		prev_hw_ste = (i == 0) ? curr_hw_ste : hw_ste_arr + ((i - 1) * DR_STE_SIZE);
		action_ste = dr_rule_create_collision_htbl(matcher,
							   nic_matcher,
							   curr_hw_ste);
		अगर (!action_ste)
			वापस -ENOMEM;

		mlx5dr_ste_get(action_ste);

		/* While मुक्त ste we go over the miss list, so add this ste to the list */
		list_add_tail(&action_ste->miss_list_node,
			      mlx5dr_ste_get_miss_list(action_ste));

		ste_info_arr[k] = kzalloc(माप(*ste_info_arr[k]),
					  GFP_KERNEL);
		अगर (!ste_info_arr[k])
			जाओ err_निकास;

		/* Poपूर्णांक current ste to the new action */
		mlx5dr_ste_set_hit_addr_by_next_htbl(dmn->ste_ctx,
						     prev_hw_ste,
						     action_ste->htbl);
		ret = dr_rule_add_member(nic_rule, action_ste);
		अगर (ret) अणु
			mlx5dr_dbg(dmn, "Failed adding rule member\n");
			जाओ मुक्त_ste_info;
		पूर्ण
		mlx5dr_send_fill_and_append_ste_send_info(action_ste, DR_STE_SIZE, 0,
							  curr_hw_ste,
							  ste_info_arr[k],
							  send_ste_list, false);
	पूर्ण

	वापस 0;

मुक्त_ste_info:
	kमुक्त(ste_info_arr[k]);
err_निकास:
	mlx5dr_ste_put(action_ste, matcher, nic_matcher);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक dr_rule_handle_empty_entry(काष्ठा mlx5dr_matcher *matcher,
				      काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				      काष्ठा mlx5dr_ste_htbl *cur_htbl,
				      काष्ठा mlx5dr_ste *ste,
				      u8 ste_location,
				      u8 *hw_ste,
				      काष्ठा list_head *miss_list,
				      काष्ठा list_head *send_list)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_ste_send_info *ste_info;

	/* Take ref on table, only on first समय this ste is used */
	mlx5dr_htbl_get(cur_htbl);

	/* new entry -> new branch */
	list_add_tail(&ste->miss_list_node, miss_list);

	mlx5dr_ste_set_miss_addr(dmn->ste_ctx, hw_ste,
				 nic_matcher->e_anchor->chunk->icm_addr);

	ste->ste_chain_location = ste_location;

	ste_info = kzalloc(माप(*ste_info), GFP_KERNEL);
	अगर (!ste_info)
		जाओ clean_ste_setting;

	अगर (mlx5dr_ste_create_next_htbl(matcher,
					nic_matcher,
					ste,
					hw_ste,
					DR_CHUNK_SIZE_1)) अणु
		mlx5dr_dbg(dmn, "Failed allocating table\n");
		जाओ clean_ste_info;
	पूर्ण

	cur_htbl->ctrl.num_of_valid_entries++;

	mlx5dr_send_fill_and_append_ste_send_info(ste, DR_STE_SIZE, 0, hw_ste,
						  ste_info, send_list, false);

	वापस 0;

clean_ste_info:
	kमुक्त(ste_info);
clean_ste_setting:
	list_del_init(&ste->miss_list_node);
	mlx5dr_htbl_put(cur_htbl);

	वापस -ENOMEM;
पूर्ण

अटल काष्ठा mlx5dr_ste *
dr_rule_handle_ste_branch(काष्ठा mlx5dr_rule *rule,
			  काष्ठा mlx5dr_rule_rx_tx *nic_rule,
			  काष्ठा list_head *send_ste_list,
			  काष्ठा mlx5dr_ste_htbl *cur_htbl,
			  u8 *hw_ste,
			  u8 ste_location,
			  काष्ठा mlx5dr_ste_htbl **put_htbl)
अणु
	काष्ठा mlx5dr_matcher *matcher = rule->matcher;
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_matcher_rx_tx *nic_matcher;
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn;
	काष्ठा mlx5dr_ste_htbl *new_htbl;
	काष्ठा mlx5dr_ste *matched_ste;
	काष्ठा list_head *miss_list;
	bool skip_rehash = false;
	काष्ठा mlx5dr_ste *ste;
	पूर्णांक index;

	nic_matcher = nic_rule->nic_matcher;
	nic_dmn = nic_matcher->nic_tbl->nic_dmn;

again:
	index = mlx5dr_ste_calc_hash_index(hw_ste, cur_htbl);
	miss_list = &cur_htbl->chunk->miss_list[index];
	ste = &cur_htbl->ste_arr[index];

	अगर (mlx5dr_ste_is_not_used(ste)) अणु
		अगर (dr_rule_handle_empty_entry(matcher, nic_matcher, cur_htbl,
					       ste, ste_location,
					       hw_ste, miss_list,
					       send_ste_list))
			वापस शून्य;
	पूर्ण अन्यथा अणु
		/* Hash table index in use, check अगर this ste is in the miss list */
		matched_ste = dr_rule_find_ste_in_miss_list(miss_list, hw_ste);
		अगर (matched_ste) अणु
			/* If it is last STE in the chain, and has the same tag
			 * it means that all the previous stes are the same,
			 * अगर so, this rule is duplicated.
			 */
			अगर (!mlx5dr_ste_is_last_in_rule(nic_matcher, ste_location))
				वापस matched_ste;

			mlx5dr_dbg(dmn, "Duplicate rule inserted\n");
		पूर्ण

		अगर (!skip_rehash && dr_rule_need_enlarge_hash(cur_htbl, dmn, nic_dmn)) अणु
			/* Hash table index in use, try to resize of the hash */
			skip_rehash = true;

			/* Hold the table till we update.
			 * Release in dr_rule_create_rule()
			 */
			*put_htbl = cur_htbl;
			mlx5dr_htbl_get(cur_htbl);

			new_htbl = dr_rule_rehash(rule, nic_rule, cur_htbl,
						  ste_location, send_ste_list);
			अगर (!new_htbl) अणु
				mlx5dr_htbl_put(cur_htbl);
				mlx5dr_err(dmn, "Failed creating rehash table, htbl-log_size: %d\n",
					   cur_htbl->chunk_size);
			पूर्ण अन्यथा अणु
				cur_htbl = new_htbl;
			पूर्ण
			जाओ again;
		पूर्ण अन्यथा अणु
			/* Hash table index in use, add another collision (miss) */
			ste = dr_rule_handle_collision(matcher,
						       nic_matcher,
						       ste,
						       hw_ste,
						       miss_list,
						       send_ste_list);
			अगर (!ste) अणु
				mlx5dr_dbg(dmn, "failed adding collision entry, index: %d\n",
					   index);
				वापस शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ste;
पूर्ण

अटल bool dr_rule_cmp_value_to_mask(u8 *mask, u8 *value,
				      u32 s_idx, u32 e_idx)
अणु
	u32 i;

	क्रम (i = s_idx; i < e_idx; i++) अणु
		अगर (value[i] & ~mask[i]) अणु
			pr_info("Rule parameters contains a value not specified by mask\n");
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल bool dr_rule_verअगरy(काष्ठा mlx5dr_matcher *matcher,
			   काष्ठा mlx5dr_match_parameters *value,
			   काष्ठा mlx5dr_match_param *param)
अणु
	u8 match_criteria = matcher->match_criteria;
	माप_प्रकार value_size = value->match_sz;
	u8 *mask_p = (u8 *)&matcher->mask;
	u8 *param_p = (u8 *)param;
	u32 s_idx, e_idx;

	अगर (!value_size ||
	    (value_size > DR_SZ_MATCH_PARAM || (value_size % माप(u32)))) अणु
		mlx5dr_err(matcher->tbl->dmn, "Rule parameters length is incorrect\n");
		वापस false;
	पूर्ण

	mlx5dr_ste_copy_param(matcher->match_criteria, param, value);

	अगर (match_criteria & DR_MATCHER_CRITERIA_OUTER) अणु
		s_idx = दुरत्व(काष्ठा mlx5dr_match_param, outer);
		e_idx = min(s_idx + माप(param->outer), value_size);

		अगर (!dr_rule_cmp_value_to_mask(mask_p, param_p, s_idx, e_idx)) अणु
			mlx5dr_err(matcher->tbl->dmn, "Rule outer parameters contains a value not specified by mask\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (match_criteria & DR_MATCHER_CRITERIA_MISC) अणु
		s_idx = दुरत्व(काष्ठा mlx5dr_match_param, misc);
		e_idx = min(s_idx + माप(param->misc), value_size);

		अगर (!dr_rule_cmp_value_to_mask(mask_p, param_p, s_idx, e_idx)) अणु
			mlx5dr_err(matcher->tbl->dmn, "Rule misc parameters contains a value not specified by mask\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (match_criteria & DR_MATCHER_CRITERIA_INNER) अणु
		s_idx = दुरत्व(काष्ठा mlx5dr_match_param, inner);
		e_idx = min(s_idx + माप(param->inner), value_size);

		अगर (!dr_rule_cmp_value_to_mask(mask_p, param_p, s_idx, e_idx)) अणु
			mlx5dr_err(matcher->tbl->dmn, "Rule inner parameters contains a value not specified by mask\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (match_criteria & DR_MATCHER_CRITERIA_MISC2) अणु
		s_idx = दुरत्व(काष्ठा mlx5dr_match_param, misc2);
		e_idx = min(s_idx + माप(param->misc2), value_size);

		अगर (!dr_rule_cmp_value_to_mask(mask_p, param_p, s_idx, e_idx)) अणु
			mlx5dr_err(matcher->tbl->dmn, "Rule misc2 parameters contains a value not specified by mask\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (match_criteria & DR_MATCHER_CRITERIA_MISC3) अणु
		s_idx = दुरत्व(काष्ठा mlx5dr_match_param, misc3);
		e_idx = min(s_idx + माप(param->misc3), value_size);

		अगर (!dr_rule_cmp_value_to_mask(mask_p, param_p, s_idx, e_idx)) अणु
			mlx5dr_err(matcher->tbl->dmn, "Rule misc3 parameters contains a value not specified by mask\n");
			वापस false;
		पूर्ण
	पूर्ण

	अगर (match_criteria & DR_MATCHER_CRITERIA_MISC4) अणु
		s_idx = दुरत्व(काष्ठा mlx5dr_match_param, misc4);
		e_idx = min(s_idx + माप(param->misc4), value_size);

		अगर (!dr_rule_cmp_value_to_mask(mask_p, param_p, s_idx, e_idx)) अणु
			mlx5dr_err(matcher->tbl->dmn,
				   "Rule misc4 parameters contains a value not specified by mask\n");
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक dr_rule_destroy_rule_nic(काष्ठा mlx5dr_rule *rule,
				    काष्ठा mlx5dr_rule_rx_tx *nic_rule)
अणु
	mlx5dr_करोमुख्य_nic_lock(nic_rule->nic_matcher->nic_tbl->nic_dmn);
	dr_rule_clean_rule_members(rule, nic_rule);
	mlx5dr_करोमुख्य_nic_unlock(nic_rule->nic_matcher->nic_tbl->nic_dmn);

	वापस 0;
पूर्ण

अटल पूर्णांक dr_rule_destroy_rule_fdb(काष्ठा mlx5dr_rule *rule)
अणु
	dr_rule_destroy_rule_nic(rule, &rule->rx);
	dr_rule_destroy_rule_nic(rule, &rule->tx);
	वापस 0;
पूर्ण

अटल पूर्णांक dr_rule_destroy_rule(काष्ठा mlx5dr_rule *rule)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = rule->matcher->tbl->dmn;

	चयन (dmn->type) अणु
	हाल MLX5DR_DOMAIN_TYPE_NIC_RX:
		dr_rule_destroy_rule_nic(rule, &rule->rx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_NIC_TX:
		dr_rule_destroy_rule_nic(rule, &rule->tx);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_FDB:
		dr_rule_destroy_rule_fdb(rule);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dr_rule_हटाओ_action_members(rule);
	kमुक्त(rule);
	वापस 0;
पूर्ण

अटल क्रमागत mlx5dr_ipv dr_rule_get_ipv(काष्ठा mlx5dr_match_spec *spec)
अणु
	अगर (spec->ip_version == 6 || spec->ethertype == ETH_P_IPV6)
		वापस DR_RULE_IPV6;

	वापस DR_RULE_IPV4;
पूर्ण

अटल bool dr_rule_skip(क्रमागत mlx5dr_करोमुख्य_type करोमुख्य,
			 क्रमागत mlx5dr_ste_entry_type ste_type,
			 काष्ठा mlx5dr_match_param *mask,
			 काष्ठा mlx5dr_match_param *value,
			 u32 flow_source)
अणु
	bool rx = ste_type == MLX5DR_STE_TYPE_RX;

	अगर (करोमुख्य != MLX5DR_DOMAIN_TYPE_FDB)
		वापस false;

	अगर (mask->misc.source_port) अणु
		अगर (rx && value->misc.source_port != WIRE_PORT)
			वापस true;

		अगर (!rx && value->misc.source_port == WIRE_PORT)
			वापस true;
	पूर्ण

	अगर (rx && flow_source == MLX5_FLOW_CONTEXT_FLOW_SOURCE_LOCAL_VPORT)
		वापस true;

	अगर (!rx && flow_source == MLX5_FLOW_CONTEXT_FLOW_SOURCE_UPLINK)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक
dr_rule_create_rule_nic(काष्ठा mlx5dr_rule *rule,
			काष्ठा mlx5dr_rule_rx_tx *nic_rule,
			काष्ठा mlx5dr_match_param *param,
			माप_प्रकार num_actions,
			काष्ठा mlx5dr_action *actions[])
अणु
	काष्ठा mlx5dr_ste_send_info *ste_info, *पंचांगp_ste_info;
	काष्ठा mlx5dr_matcher *matcher = rule->matcher;
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_matcher_rx_tx *nic_matcher;
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn;
	काष्ठा mlx5dr_ste_htbl *htbl = शून्य;
	काष्ठा mlx5dr_ste_htbl *cur_htbl;
	काष्ठा mlx5dr_ste *ste = शून्य;
	LIST_HEAD(send_ste_list);
	u8 *hw_ste_arr = शून्य;
	u32 new_hw_ste_arr_sz;
	पूर्णांक ret, i;

	nic_matcher = nic_rule->nic_matcher;
	nic_dmn = nic_matcher->nic_tbl->nic_dmn;

	INIT_LIST_HEAD(&nic_rule->rule_members_list);

	अगर (dr_rule_skip(dmn->type, nic_dmn->ste_type, &matcher->mask, param,
			 rule->flow_source))
		वापस 0;

	hw_ste_arr = kzalloc(DR_RULE_MAX_STE_CHAIN * DR_STE_SIZE, GFP_KERNEL);
	अगर (!hw_ste_arr)
		वापस -ENOMEM;

	mlx5dr_करोमुख्य_nic_lock(nic_dmn);

	ret = mlx5dr_matcher_select_builders(matcher,
					     nic_matcher,
					     dr_rule_get_ipv(&param->outer),
					     dr_rule_get_ipv(&param->inner));
	अगर (ret)
		जाओ मुक्त_hw_ste;

	/* Set the tag values inside the ste array */
	ret = mlx5dr_ste_build_ste_arr(matcher, nic_matcher, param, hw_ste_arr);
	अगर (ret)
		जाओ मुक्त_hw_ste;

	/* Set the actions values/addresses inside the ste array */
	ret = mlx5dr_actions_build_ste_arr(matcher, nic_matcher, actions,
					   num_actions, hw_ste_arr,
					   &new_hw_ste_arr_sz);
	अगर (ret)
		जाओ मुक्त_hw_ste;

	cur_htbl = nic_matcher->s_htbl;

	/* Go over the array of STEs, and build dr_ste accordingly.
	 * The loop is over only the builders which are equal or less to the
	 * number of stes, in हाल we have actions that lives in other stes.
	 */
	क्रम (i = 0; i < nic_matcher->num_of_builders; i++) अणु
		/* Calculate CRC and keep new ste entry */
		u8 *cur_hw_ste_ent = hw_ste_arr + (i * DR_STE_SIZE);

		ste = dr_rule_handle_ste_branch(rule,
						nic_rule,
						&send_ste_list,
						cur_htbl,
						cur_hw_ste_ent,
						i + 1,
						&htbl);
		अगर (!ste) अणु
			mlx5dr_err(dmn, "Failed creating next branch\n");
			ret = -ENOENT;
			जाओ मुक्त_rule;
		पूर्ण

		cur_htbl = ste->next_htbl;

		/* Keep all STEs in the rule काष्ठा */
		ret = dr_rule_add_member(nic_rule, ste);
		अगर (ret) अणु
			mlx5dr_dbg(dmn, "Failed adding rule member index %d\n", i);
			जाओ मुक्त_ste;
		पूर्ण

		mlx5dr_ste_get(ste);
	पूर्ण

	/* Connect actions */
	ret = dr_rule_handle_action_stes(rule, nic_rule, &send_ste_list,
					 ste, hw_ste_arr, new_hw_ste_arr_sz);
	अगर (ret) अणु
		mlx5dr_dbg(dmn, "Failed apply actions\n");
		जाओ मुक्त_rule;
	पूर्ण
	ret = dr_rule_send_update_list(&send_ste_list, dmn, true);
	अगर (ret) अणु
		mlx5dr_err(dmn, "Failed sending ste!\n");
		जाओ मुक्त_rule;
	पूर्ण

	अगर (htbl)
		mlx5dr_htbl_put(htbl);

	mlx5dr_करोमुख्य_nic_unlock(nic_dmn);

	kमुक्त(hw_ste_arr);

	वापस 0;

मुक्त_ste:
	mlx5dr_ste_put(ste, matcher, nic_matcher);
मुक्त_rule:
	dr_rule_clean_rule_members(rule, nic_rule);
	/* Clean all ste_info's */
	list_क्रम_each_entry_safe(ste_info, पंचांगp_ste_info, &send_ste_list, send_list) अणु
		list_del(&ste_info->send_list);
		kमुक्त(ste_info);
	पूर्ण
मुक्त_hw_ste:
	mlx5dr_करोमुख्य_nic_unlock(nic_dmn);
	kमुक्त(hw_ste_arr);
	वापस ret;
पूर्ण

अटल पूर्णांक
dr_rule_create_rule_fdb(काष्ठा mlx5dr_rule *rule,
			काष्ठा mlx5dr_match_param *param,
			माप_प्रकार num_actions,
			काष्ठा mlx5dr_action *actions[])
अणु
	काष्ठा mlx5dr_match_param copy_param = अणुपूर्ण;
	पूर्णांक ret;

	/* Copy match_param since they will be consumed during the first
	 * nic_rule insertion.
	 */
	स_नकल(&copy_param, param, माप(काष्ठा mlx5dr_match_param));

	ret = dr_rule_create_rule_nic(rule, &rule->rx, param,
				      num_actions, actions);
	अगर (ret)
		वापस ret;

	ret = dr_rule_create_rule_nic(rule, &rule->tx, &copy_param,
				      num_actions, actions);
	अगर (ret)
		जाओ destroy_rule_nic_rx;

	वापस 0;

destroy_rule_nic_rx:
	dr_rule_destroy_rule_nic(rule, &rule->rx);
	वापस ret;
पूर्ण

अटल काष्ठा mlx5dr_rule *
dr_rule_create_rule(काष्ठा mlx5dr_matcher *matcher,
		    काष्ठा mlx5dr_match_parameters *value,
		    माप_प्रकार num_actions,
		    काष्ठा mlx5dr_action *actions[],
		    u32 flow_source)
अणु
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_match_param param = अणुपूर्ण;
	काष्ठा mlx5dr_rule *rule;
	पूर्णांक ret;

	अगर (!dr_rule_verअगरy(matcher, value, &param))
		वापस शून्य;

	rule = kzalloc(माप(*rule), GFP_KERNEL);
	अगर (!rule)
		वापस शून्य;

	rule->matcher = matcher;
	rule->flow_source = flow_source;
	INIT_LIST_HEAD(&rule->rule_actions_list);

	ret = dr_rule_add_action_members(rule, num_actions, actions);
	अगर (ret)
		जाओ मुक्त_rule;

	चयन (dmn->type) अणु
	हाल MLX5DR_DOMAIN_TYPE_NIC_RX:
		rule->rx.nic_matcher = &matcher->rx;
		ret = dr_rule_create_rule_nic(rule, &rule->rx, &param,
					      num_actions, actions);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_NIC_TX:
		rule->tx.nic_matcher = &matcher->tx;
		ret = dr_rule_create_rule_nic(rule, &rule->tx, &param,
					      num_actions, actions);
		अवरोध;
	हाल MLX5DR_DOMAIN_TYPE_FDB:
		rule->rx.nic_matcher = &matcher->rx;
		rule->tx.nic_matcher = &matcher->tx;
		ret = dr_rule_create_rule_fdb(rule, &param,
					      num_actions, actions);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (ret)
		जाओ हटाओ_action_members;

	वापस rule;

हटाओ_action_members:
	dr_rule_हटाओ_action_members(rule);
मुक्त_rule:
	kमुक्त(rule);
	mlx5dr_err(dmn, "Failed creating rule\n");
	वापस शून्य;
पूर्ण

काष्ठा mlx5dr_rule *mlx5dr_rule_create(काष्ठा mlx5dr_matcher *matcher,
				       काष्ठा mlx5dr_match_parameters *value,
				       माप_प्रकार num_actions,
				       काष्ठा mlx5dr_action *actions[],
				       u32 flow_source)
अणु
	काष्ठा mlx5dr_rule *rule;

	refcount_inc(&matcher->refcount);

	rule = dr_rule_create_rule(matcher, value, num_actions, actions, flow_source);
	अगर (!rule)
		refcount_dec(&matcher->refcount);

	वापस rule;
पूर्ण

पूर्णांक mlx5dr_rule_destroy(काष्ठा mlx5dr_rule *rule)
अणु
	काष्ठा mlx5dr_matcher *matcher = rule->matcher;
	पूर्णांक ret;

	ret = dr_rule_destroy_rule(rule);
	अगर (!ret)
		refcount_dec(&matcher->refcount);

	वापस ret;
पूर्ण
