<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश <linux/types.h>
#समावेश <linux/crc32.h>
#समावेश "dr_ste.h"

काष्ठा dr_hw_ste_क्रमmat अणु
	u8 ctrl[DR_STE_SIZE_CTRL];
	u8 tag[DR_STE_SIZE_TAG];
	u8 mask[DR_STE_SIZE_MASK];
पूर्ण;

अटल u32 dr_ste_crc32_calc(स्थिर व्योम *input_data, माप_प्रकार length)
अणु
	u32 crc = crc32(0, input_data, length);

	वापस (__क्रमce u32)htonl(crc);
पूर्ण

bool mlx5dr_ste_supp_ttl_cs_recalc(काष्ठा mlx5dr_cmd_caps *caps)
अणु
	वापस caps->sw_क्रमmat_ver > MLX5_STEERING_FORMAT_CONNECTX_5;
पूर्ण

u32 mlx5dr_ste_calc_hash_index(u8 *hw_ste_p, काष्ठा mlx5dr_ste_htbl *htbl)
अणु
	काष्ठा dr_hw_ste_क्रमmat *hw_ste = (काष्ठा dr_hw_ste_क्रमmat *)hw_ste_p;
	u8 masked[DR_STE_SIZE_TAG] = अणुपूर्ण;
	u32 crc32, index;
	u16 bit;
	पूर्णांक i;

	/* Don't calculate CRC अगर the result is predicted */
	अगर (htbl->chunk->num_of_entries == 1 || htbl->byte_mask == 0)
		वापस 0;

	/* Mask tag using byte mask, bit per byte */
	bit = 1 << (DR_STE_SIZE_TAG - 1);
	क्रम (i = 0; i < DR_STE_SIZE_TAG; i++) अणु
		अगर (htbl->byte_mask & bit)
			masked[i] = hw_ste->tag[i];

		bit = bit >> 1;
	पूर्ण

	crc32 = dr_ste_crc32_calc(masked, DR_STE_SIZE_TAG);
	index = crc32 & (htbl->chunk->num_of_entries - 1);

	वापस index;
पूर्ण

u16 mlx5dr_ste_conv_bit_to_byte_mask(u8 *bit_mask)
अणु
	u16 byte_mask = 0;
	पूर्णांक i;

	क्रम (i = 0; i < DR_STE_SIZE_MASK; i++) अणु
		byte_mask = byte_mask << 1;
		अगर (bit_mask[i] == 0xff)
			byte_mask |= 1;
	पूर्ण
	वापस byte_mask;
पूर्ण

अटल u8 *dr_ste_get_tag(u8 *hw_ste_p)
अणु
	काष्ठा dr_hw_ste_क्रमmat *hw_ste = (काष्ठा dr_hw_ste_क्रमmat *)hw_ste_p;

	वापस hw_ste->tag;
पूर्ण

व्योम mlx5dr_ste_set_bit_mask(u8 *hw_ste_p, u8 *bit_mask)
अणु
	काष्ठा dr_hw_ste_क्रमmat *hw_ste = (काष्ठा dr_hw_ste_क्रमmat *)hw_ste_p;

	स_नकल(hw_ste->mask, bit_mask, DR_STE_SIZE_MASK);
पूर्ण

अटल व्योम dr_ste_set_always_hit(काष्ठा dr_hw_ste_क्रमmat *hw_ste)
अणु
	स_रखो(&hw_ste->tag, 0, माप(hw_ste->tag));
	स_रखो(&hw_ste->mask, 0, माप(hw_ste->mask));
पूर्ण

अटल व्योम dr_ste_set_always_miss(काष्ठा dr_hw_ste_क्रमmat *hw_ste)
अणु
	hw_ste->tag[0] = 0xdc;
	hw_ste->mask[0] = 0;
पूर्ण

व्योम mlx5dr_ste_set_miss_addr(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			      u8 *hw_ste_p, u64 miss_addr)
अणु
	ste_ctx->set_miss_addr(hw_ste_p, miss_addr);
पूर्ण

अटल व्योम dr_ste_always_miss_addr(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				    काष्ठा mlx5dr_ste *ste, u64 miss_addr)
अणु
	u8 *hw_ste_p = ste->hw_ste;

	ste_ctx->set_next_lu_type(hw_ste_p, MLX5DR_STE_LU_TYPE_DONT_CARE);
	ste_ctx->set_miss_addr(hw_ste_p, miss_addr);
	dr_ste_set_always_miss((काष्ठा dr_hw_ste_क्रमmat *)ste->hw_ste);
पूर्ण

व्योम mlx5dr_ste_set_hit_addr(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			     u8 *hw_ste, u64 icm_addr, u32 ht_size)
अणु
	ste_ctx->set_hit_addr(hw_ste, icm_addr, ht_size);
पूर्ण

u64 mlx5dr_ste_get_icm_addr(काष्ठा mlx5dr_ste *ste)
अणु
	u32 index = ste - ste->htbl->ste_arr;

	वापस ste->htbl->chunk->icm_addr + DR_STE_SIZE * index;
पूर्ण

u64 mlx5dr_ste_get_mr_addr(काष्ठा mlx5dr_ste *ste)
अणु
	u32 index = ste - ste->htbl->ste_arr;

	वापस ste->htbl->chunk->mr_addr + DR_STE_SIZE * index;
पूर्ण

काष्ठा list_head *mlx5dr_ste_get_miss_list(काष्ठा mlx5dr_ste *ste)
अणु
	u32 index = ste - ste->htbl->ste_arr;

	वापस &ste->htbl->miss_list[index];
पूर्ण

अटल व्योम dr_ste_always_hit_htbl(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				   काष्ठा mlx5dr_ste *ste,
				   काष्ठा mlx5dr_ste_htbl *next_htbl)
अणु
	काष्ठा mlx5dr_icm_chunk *chunk = next_htbl->chunk;
	u8 *hw_ste = ste->hw_ste;

	ste_ctx->set_byte_mask(hw_ste, next_htbl->byte_mask);
	ste_ctx->set_next_lu_type(hw_ste, next_htbl->lu_type);
	ste_ctx->set_hit_addr(hw_ste, chunk->icm_addr, chunk->num_of_entries);

	dr_ste_set_always_hit((काष्ठा dr_hw_ste_क्रमmat *)ste->hw_ste);
पूर्ण

bool mlx5dr_ste_is_last_in_rule(काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				u8 ste_location)
अणु
	वापस ste_location == nic_matcher->num_of_builders;
पूर्ण

/* Replace relevant fields, except of:
 * htbl - keep the origin htbl
 * miss_list + list - alपढ़ोy took the src from the list.
 * icm_addr/mr_addr - depends on the hosting table.
 *
 * Beक्रमe:
 * | a | -> | b | -> | c | ->
 *
 * After:
 * | a | -> | c | ->
 * While the data that was in b copied to a.
 */
अटल व्योम dr_ste_replace(काष्ठा mlx5dr_ste *dst, काष्ठा mlx5dr_ste *src)
अणु
	स_नकल(dst->hw_ste, src->hw_ste, DR_STE_SIZE_REDUCED);
	dst->next_htbl = src->next_htbl;
	अगर (dst->next_htbl)
		dst->next_htbl->poपूर्णांकing_ste = dst;

	dst->refcount = src->refcount;

	INIT_LIST_HEAD(&dst->rule_list);
	list_splice_tail_init(&src->rule_list, &dst->rule_list);
पूर्ण

/* Free ste which is the head and the only one in miss_list */
अटल व्योम
dr_ste_हटाओ_head_ste(काष्ठा mlx5dr_ste_ctx *ste_ctx,
		       काष्ठा mlx5dr_ste *ste,
		       काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
		       काष्ठा mlx5dr_ste_send_info *ste_info_head,
		       काष्ठा list_head *send_ste_list,
		       काष्ठा mlx5dr_ste_htbl *stats_tbl)
अणु
	u8 पंचांगp_data_ste[DR_STE_SIZE] = अणुपूर्ण;
	काष्ठा mlx5dr_ste पंचांगp_ste = अणुपूर्ण;
	u64 miss_addr;

	पंचांगp_ste.hw_ste = पंचांगp_data_ste;

	/* Use temp ste because dr_ste_always_miss_addr
	 * touches bit_mask area which करोesn't exist at ste->hw_ste.
	 */
	स_नकल(पंचांगp_ste.hw_ste, ste->hw_ste, DR_STE_SIZE_REDUCED);
	miss_addr = nic_matcher->e_anchor->chunk->icm_addr;
	dr_ste_always_miss_addr(ste_ctx, &पंचांगp_ste, miss_addr);
	स_नकल(ste->hw_ste, पंचांगp_ste.hw_ste, DR_STE_SIZE_REDUCED);

	list_del_init(&ste->miss_list_node);

	/* Write full STE size in order to have "always_miss" */
	mlx5dr_send_fill_and_append_ste_send_info(ste, DR_STE_SIZE,
						  0, पंचांगp_data_ste,
						  ste_info_head,
						  send_ste_list,
						  true /* Copy data */);

	stats_tbl->ctrl.num_of_valid_entries--;
पूर्ण

/* Free ste which is the head but NOT the only one in miss_list:
 * |_ste_| --> |_next_ste_| -->|__| -->|__| -->/0
 */
अटल व्योम
dr_ste_replace_head_ste(काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
			काष्ठा mlx5dr_ste *ste,
			काष्ठा mlx5dr_ste *next_ste,
			काष्ठा mlx5dr_ste_send_info *ste_info_head,
			काष्ठा list_head *send_ste_list,
			काष्ठा mlx5dr_ste_htbl *stats_tbl)

अणु
	काष्ठा mlx5dr_ste_htbl *next_miss_htbl;
	u8 hw_ste[DR_STE_SIZE] = अणुपूर्ण;
	पूर्णांक sb_idx;

	next_miss_htbl = next_ste->htbl;

	/* Remove from the miss_list the next_ste beक्रमe copy */
	list_del_init(&next_ste->miss_list_node);

	/* All rule-members that use next_ste should know about that */
	mlx5dr_rule_update_rule_member(next_ste, ste);

	/* Move data from next पूर्णांकo ste */
	dr_ste_replace(ste, next_ste);

	/* Copy all 64 hw_ste bytes */
	स_नकल(hw_ste, ste->hw_ste, DR_STE_SIZE_REDUCED);
	sb_idx = ste->ste_chain_location - 1;
	mlx5dr_ste_set_bit_mask(hw_ste,
				nic_matcher->ste_builder[sb_idx].bit_mask);

	/* Del the htbl that contains the next_ste.
	 * The origin htbl stay with the same number of entries.
	 */
	mlx5dr_htbl_put(next_miss_htbl);

	mlx5dr_send_fill_and_append_ste_send_info(ste, DR_STE_SIZE,
						  0, hw_ste,
						  ste_info_head,
						  send_ste_list,
						  true /* Copy data */);

	stats_tbl->ctrl.num_of_collisions--;
	stats_tbl->ctrl.num_of_valid_entries--;
पूर्ण

/* Free ste that is located in the middle of the miss list:
 * |__| -->|_prev_ste_|->|_ste_|-->|_next_ste_|
 */
अटल व्योम dr_ste_हटाओ_middle_ste(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				     काष्ठा mlx5dr_ste *ste,
				     काष्ठा mlx5dr_ste_send_info *ste_info,
				     काष्ठा list_head *send_ste_list,
				     काष्ठा mlx5dr_ste_htbl *stats_tbl)
अणु
	काष्ठा mlx5dr_ste *prev_ste;
	u64 miss_addr;

	prev_ste = list_prev_entry(ste, miss_list_node);
	अगर (WARN_ON(!prev_ste))
		वापस;

	miss_addr = ste_ctx->get_miss_addr(ste->hw_ste);
	ste_ctx->set_miss_addr(prev_ste->hw_ste, miss_addr);

	mlx5dr_send_fill_and_append_ste_send_info(prev_ste, DR_STE_SIZE_CTRL, 0,
						  prev_ste->hw_ste, ste_info,
						  send_ste_list, true /* Copy data*/);

	list_del_init(&ste->miss_list_node);

	stats_tbl->ctrl.num_of_valid_entries--;
	stats_tbl->ctrl.num_of_collisions--;
पूर्ण

व्योम mlx5dr_ste_मुक्त(काष्ठा mlx5dr_ste *ste,
		     काष्ठा mlx5dr_matcher *matcher,
		     काष्ठा mlx5dr_matcher_rx_tx *nic_matcher)
अणु
	काष्ठा mlx5dr_ste_send_info *cur_ste_info, *पंचांगp_ste_info;
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_ste_ctx *ste_ctx = dmn->ste_ctx;
	काष्ठा mlx5dr_ste_send_info ste_info_head;
	काष्ठा mlx5dr_ste *next_ste, *first_ste;
	bool put_on_origin_table = true;
	काष्ठा mlx5dr_ste_htbl *stats_tbl;
	LIST_HEAD(send_ste_list);

	first_ste = list_first_entry(mlx5dr_ste_get_miss_list(ste),
				     काष्ठा mlx5dr_ste, miss_list_node);
	stats_tbl = first_ste->htbl;

	/* Two options:
	 * 1. ste is head:
	 *	a. head ste is the only ste in the miss list
	 *	b. head ste is not the only ste in the miss-list
	 * 2. ste is not head
	 */
	अगर (first_ste == ste) अणु /* Ste is the head */
		काष्ठा mlx5dr_ste *last_ste;

		last_ste = list_last_entry(mlx5dr_ste_get_miss_list(ste),
					   काष्ठा mlx5dr_ste, miss_list_node);
		अगर (last_ste == first_ste)
			next_ste = शून्य;
		अन्यथा
			next_ste = list_next_entry(ste, miss_list_node);

		अगर (!next_ste) अणु
			/* One and only entry in the list */
			dr_ste_हटाओ_head_ste(ste_ctx, ste,
					       nic_matcher,
					       &ste_info_head,
					       &send_ste_list,
					       stats_tbl);
		पूर्ण अन्यथा अणु
			/* First but not only entry in the list */
			dr_ste_replace_head_ste(nic_matcher, ste,
						next_ste, &ste_info_head,
						&send_ste_list, stats_tbl);
			put_on_origin_table = false;
		पूर्ण
	पूर्ण अन्यथा अणु /* Ste in the middle of the list */
		dr_ste_हटाओ_middle_ste(ste_ctx, ste,
					 &ste_info_head, &send_ste_list,
					 stats_tbl);
	पूर्ण

	/* Update HW */
	list_क्रम_each_entry_safe(cur_ste_info, पंचांगp_ste_info,
				 &send_ste_list, send_list) अणु
		list_del(&cur_ste_info->send_list);
		mlx5dr_send_postsend_ste(dmn, cur_ste_info->ste,
					 cur_ste_info->data, cur_ste_info->size,
					 cur_ste_info->offset);
	पूर्ण

	अगर (put_on_origin_table)
		mlx5dr_htbl_put(ste->htbl);
पूर्ण

bool mlx5dr_ste_equal_tag(व्योम *src, व्योम *dst)
अणु
	काष्ठा dr_hw_ste_क्रमmat *s_hw_ste = (काष्ठा dr_hw_ste_क्रमmat *)src;
	काष्ठा dr_hw_ste_क्रमmat *d_hw_ste = (काष्ठा dr_hw_ste_क्रमmat *)dst;

	वापस !स_भेद(s_hw_ste->tag, d_hw_ste->tag, DR_STE_SIZE_TAG);
पूर्ण

व्योम mlx5dr_ste_set_hit_addr_by_next_htbl(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					  u8 *hw_ste,
					  काष्ठा mlx5dr_ste_htbl *next_htbl)
अणु
	काष्ठा mlx5dr_icm_chunk *chunk = next_htbl->chunk;

	ste_ctx->set_hit_addr(hw_ste, chunk->icm_addr, chunk->num_of_entries);
पूर्ण

व्योम mlx5dr_ste_prepare_क्रम_postsend(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				     u8 *hw_ste_p, u32 ste_size)
अणु
	अगर (ste_ctx->prepare_क्रम_postsend)
		ste_ctx->prepare_क्रम_postsend(hw_ste_p, ste_size);
पूर्ण

/* Init one ste as a pattern क्रम ste data array */
व्योम mlx5dr_ste_set_क्रमmatted_ste(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				  u16 gvmi,
				  काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn,
				  काष्ठा mlx5dr_ste_htbl *htbl,
				  u8 *क्रमmatted_ste,
				  काष्ठा mlx5dr_htbl_connect_info *connect_info)
अणु
	काष्ठा mlx5dr_ste ste = अणुपूर्ण;

	ste_ctx->ste_init(क्रमmatted_ste, htbl->lu_type, nic_dmn->ste_type, gvmi);
	ste.hw_ste = क्रमmatted_ste;

	अगर (connect_info->type == CONNECT_HIT)
		dr_ste_always_hit_htbl(ste_ctx, &ste, connect_info->hit_next_htbl);
	अन्यथा
		dr_ste_always_miss_addr(ste_ctx, &ste, connect_info->miss_icm_addr);
पूर्ण

पूर्णांक mlx5dr_ste_htbl_init_and_postsend(काष्ठा mlx5dr_करोमुख्य *dmn,
				      काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn,
				      काष्ठा mlx5dr_ste_htbl *htbl,
				      काष्ठा mlx5dr_htbl_connect_info *connect_info,
				      bool update_hw_ste)
अणु
	u8 क्रमmatted_ste[DR_STE_SIZE] = अणुपूर्ण;

	mlx5dr_ste_set_क्रमmatted_ste(dmn->ste_ctx,
				     dmn->info.caps.gvmi,
				     nic_dmn,
				     htbl,
				     क्रमmatted_ste,
				     connect_info);

	वापस mlx5dr_send_postsend_क्रमmatted_htbl(dmn, htbl, क्रमmatted_ste, update_hw_ste);
पूर्ण

पूर्णांक mlx5dr_ste_create_next_htbl(काष्ठा mlx5dr_matcher *matcher,
				काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
				काष्ठा mlx5dr_ste *ste,
				u8 *cur_hw_ste,
				क्रमागत mlx5dr_icm_chunk_size log_table_size)
अणु
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn = nic_matcher->nic_tbl->nic_dmn;
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_ste_ctx *ste_ctx = dmn->ste_ctx;
	काष्ठा mlx5dr_htbl_connect_info info;
	काष्ठा mlx5dr_ste_htbl *next_htbl;

	अगर (!mlx5dr_ste_is_last_in_rule(nic_matcher, ste->ste_chain_location)) अणु
		u16 next_lu_type;
		u16 byte_mask;

		next_lu_type = ste_ctx->get_next_lu_type(cur_hw_ste);
		byte_mask = ste_ctx->get_byte_mask(cur_hw_ste);

		next_htbl = mlx5dr_ste_htbl_alloc(dmn->ste_icm_pool,
						  log_table_size,
						  next_lu_type,
						  byte_mask);
		अगर (!next_htbl) अणु
			mlx5dr_dbg(dmn, "Failed allocating table\n");
			वापस -ENOMEM;
		पूर्ण

		/* Write new table to HW */
		info.type = CONNECT_MISS;
		info.miss_icm_addr = nic_matcher->e_anchor->chunk->icm_addr;
		अगर (mlx5dr_ste_htbl_init_and_postsend(dmn, nic_dmn, next_htbl,
						      &info, false)) अणु
			mlx5dr_info(dmn, "Failed writing table to HW\n");
			जाओ मुक्त_table;
		पूर्ण

		mlx5dr_ste_set_hit_addr_by_next_htbl(ste_ctx,
						     cur_hw_ste, next_htbl);
		ste->next_htbl = next_htbl;
		next_htbl->poपूर्णांकing_ste = ste;
	पूर्ण

	वापस 0;

मुक्त_table:
	mlx5dr_ste_htbl_मुक्त(next_htbl);
	वापस -ENOENT;
पूर्ण

अटल व्योम dr_ste_set_ctrl(काष्ठा mlx5dr_ste_htbl *htbl)
अणु
	काष्ठा mlx5dr_ste_htbl_ctrl *ctrl = &htbl->ctrl;
	पूर्णांक num_of_entries;

	htbl->ctrl.may_grow = true;

	अगर (htbl->chunk_size == DR_CHUNK_SIZE_MAX - 1 || !htbl->byte_mask)
		htbl->ctrl.may_grow = false;

	/* Threshold is 50%, one is added to table of size 1 */
	num_of_entries = mlx5dr_icm_pool_chunk_माप_प्रकारo_entries(htbl->chunk_size);
	ctrl->increase_threshold = (num_of_entries + 1) / 2;
पूर्ण

काष्ठा mlx5dr_ste_htbl *mlx5dr_ste_htbl_alloc(काष्ठा mlx5dr_icm_pool *pool,
					      क्रमागत mlx5dr_icm_chunk_size chunk_size,
					      u16 lu_type, u16 byte_mask)
अणु
	काष्ठा mlx5dr_icm_chunk *chunk;
	काष्ठा mlx5dr_ste_htbl *htbl;
	पूर्णांक i;

	htbl = kzalloc(माप(*htbl), GFP_KERNEL);
	अगर (!htbl)
		वापस शून्य;

	chunk = mlx5dr_icm_alloc_chunk(pool, chunk_size);
	अगर (!chunk)
		जाओ out_मुक्त_htbl;

	htbl->chunk = chunk;
	htbl->lu_type = lu_type;
	htbl->byte_mask = byte_mask;
	htbl->ste_arr = chunk->ste_arr;
	htbl->hw_ste_arr = chunk->hw_ste_arr;
	htbl->miss_list = chunk->miss_list;
	htbl->refcount = 0;

	क्रम (i = 0; i < chunk->num_of_entries; i++) अणु
		काष्ठा mlx5dr_ste *ste = &htbl->ste_arr[i];

		ste->hw_ste = htbl->hw_ste_arr + i * DR_STE_SIZE_REDUCED;
		ste->htbl = htbl;
		ste->refcount = 0;
		INIT_LIST_HEAD(&ste->miss_list_node);
		INIT_LIST_HEAD(&htbl->miss_list[i]);
		INIT_LIST_HEAD(&ste->rule_list);
	पूर्ण

	htbl->chunk_size = chunk_size;
	dr_ste_set_ctrl(htbl);
	वापस htbl;

out_मुक्त_htbl:
	kमुक्त(htbl);
	वापस शून्य;
पूर्ण

पूर्णांक mlx5dr_ste_htbl_मुक्त(काष्ठा mlx5dr_ste_htbl *htbl)
अणु
	अगर (htbl->refcount)
		वापस -EBUSY;

	mlx5dr_icm_मुक्त_chunk(htbl->chunk);
	kमुक्त(htbl);
	वापस 0;
पूर्ण

व्योम mlx5dr_ste_set_actions_tx(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       काष्ठा mlx5dr_करोमुख्य *dmn,
			       u8 *action_type_set,
			       u8 *hw_ste_arr,
			       काष्ठा mlx5dr_ste_actions_attr *attr,
			       u32 *added_stes)
अणु
	ste_ctx->set_actions_tx(dmn, action_type_set, hw_ste_arr,
				attr, added_stes);
पूर्ण

व्योम mlx5dr_ste_set_actions_rx(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       काष्ठा mlx5dr_करोमुख्य *dmn,
			       u8 *action_type_set,
			       u8 *hw_ste_arr,
			       काष्ठा mlx5dr_ste_actions_attr *attr,
			       u32 *added_stes)
अणु
	ste_ctx->set_actions_rx(dmn, action_type_set, hw_ste_arr,
				attr, added_stes);
पूर्ण

स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field *
mlx5dr_ste_conv_modअगरy_hdr_sw_field(काष्ठा mlx5dr_ste_ctx *ste_ctx, u16 sw_field)
अणु
	स्थिर काष्ठा mlx5dr_ste_action_modअगरy_field *hw_field;

	अगर (sw_field >= ste_ctx->modअगरy_field_arr_sz)
		वापस शून्य;

	hw_field = &ste_ctx->modअगरy_field_arr[sw_field];
	अगर (!hw_field->end && !hw_field->start)
		वापस शून्य;

	वापस hw_field;
पूर्ण

व्योम mlx5dr_ste_set_action_set(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       __be64 *hw_action,
			       u8 hw_field,
			       u8 shअगरter,
			       u8 length,
			       u32 data)
अणु
	ste_ctx->set_action_set((u8 *)hw_action,
				hw_field, shअगरter, length, data);
पूर्ण

व्योम mlx5dr_ste_set_action_add(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       __be64 *hw_action,
			       u8 hw_field,
			       u8 shअगरter,
			       u8 length,
			       u32 data)
अणु
	ste_ctx->set_action_add((u8 *)hw_action,
				hw_field, shअगरter, length, data);
पूर्ण

व्योम mlx5dr_ste_set_action_copy(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				__be64 *hw_action,
				u8 dst_hw_field,
				u8 dst_shअगरter,
				u8 dst_len,
				u8 src_hw_field,
				u8 src_shअगरter)
अणु
	ste_ctx->set_action_copy((u8 *)hw_action,
				 dst_hw_field, dst_shअगरter, dst_len,
				 src_hw_field, src_shअगरter);
पूर्ण

पूर्णांक mlx5dr_ste_set_action_decap_l3_list(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					व्योम *data, u32 data_sz,
					u8 *hw_action, u32 hw_action_sz,
					u16 *used_hw_action_num)
अणु
	/* Only Ethernet frame is supported, with VLAN (18) or without (14) */
	अगर (data_sz != HDR_LEN_L2 && data_sz != HDR_LEN_L2_W_VLAN)
		वापस -EINVAL;

	वापस ste_ctx->set_action_decap_l3_list(data, data_sz,
						 hw_action, hw_action_sz,
						 used_hw_action_num);
पूर्ण

पूर्णांक mlx5dr_ste_build_pre_check(काष्ठा mlx5dr_करोमुख्य *dmn,
			       u8 match_criteria,
			       काष्ठा mlx5dr_match_param *mask,
			       काष्ठा mlx5dr_match_param *value)
अणु
	अगर (!value && (match_criteria & DR_MATCHER_CRITERIA_MISC)) अणु
		अगर (mask->misc.source_port && mask->misc.source_port != 0xffff) अणु
			mlx5dr_err(dmn,
				   "Partial mask source_port is not supported\n");
			वापस -EINVAL;
		पूर्ण
		अगर (mask->misc.source_eचयन_owner_vhca_id &&
		    mask->misc.source_eचयन_owner_vhca_id != 0xffff) अणु
			mlx5dr_err(dmn,
				   "Partial mask source_eswitch_owner_vhca_id is not supported\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5dr_ste_build_ste_arr(काष्ठा mlx5dr_matcher *matcher,
			     काष्ठा mlx5dr_matcher_rx_tx *nic_matcher,
			     काष्ठा mlx5dr_match_param *value,
			     u8 *ste_arr)
अणु
	काष्ठा mlx5dr_करोमुख्य_rx_tx *nic_dmn = nic_matcher->nic_tbl->nic_dmn;
	काष्ठा mlx5dr_करोमुख्य *dmn = matcher->tbl->dmn;
	काष्ठा mlx5dr_ste_ctx *ste_ctx = dmn->ste_ctx;
	काष्ठा mlx5dr_ste_build *sb;
	पूर्णांक ret, i;

	ret = mlx5dr_ste_build_pre_check(dmn, matcher->match_criteria,
					 &matcher->mask, value);
	अगर (ret)
		वापस ret;

	sb = nic_matcher->ste_builder;
	क्रम (i = 0; i < nic_matcher->num_of_builders; i++) अणु
		ste_ctx->ste_init(ste_arr,
				  sb->lu_type,
				  nic_dmn->ste_type,
				  dmn->info.caps.gvmi);

		mlx5dr_ste_set_bit_mask(ste_arr, sb->bit_mask);

		ret = sb->ste_build_tag_func(value, sb, dr_ste_get_tag(ste_arr));
		अगर (ret)
			वापस ret;

		/* Connect the STEs */
		अगर (i < (nic_matcher->num_of_builders - 1)) अणु
			/* Need the next builder क्रम these fields,
			 * not relevant क्रम the last ste in the chain.
			 */
			sb++;
			ste_ctx->set_next_lu_type(ste_arr, sb->lu_type);
			ste_ctx->set_byte_mask(ste_arr, sb->byte_mask);
		पूर्ण
		ste_arr += DR_STE_SIZE;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dr_ste_copy_mask_misc(अक्षर *mask, काष्ठा mlx5dr_match_misc *spec)
अणु
	spec->gre_c_present = MLX5_GET(fte_match_set_misc, mask, gre_c_present);
	spec->gre_k_present = MLX5_GET(fte_match_set_misc, mask, gre_k_present);
	spec->gre_s_present = MLX5_GET(fte_match_set_misc, mask, gre_s_present);
	spec->source_vhca_port = MLX5_GET(fte_match_set_misc, mask, source_vhca_port);
	spec->source_sqn = MLX5_GET(fte_match_set_misc, mask, source_sqn);

	spec->source_port = MLX5_GET(fte_match_set_misc, mask, source_port);
	spec->source_eचयन_owner_vhca_id = MLX5_GET(fte_match_set_misc, mask,
						      source_eचयन_owner_vhca_id);

	spec->outer_second_prio = MLX5_GET(fte_match_set_misc, mask, outer_second_prio);
	spec->outer_second_cfi = MLX5_GET(fte_match_set_misc, mask, outer_second_cfi);
	spec->outer_second_vid = MLX5_GET(fte_match_set_misc, mask, outer_second_vid);
	spec->inner_second_prio = MLX5_GET(fte_match_set_misc, mask, inner_second_prio);
	spec->inner_second_cfi = MLX5_GET(fte_match_set_misc, mask, inner_second_cfi);
	spec->inner_second_vid = MLX5_GET(fte_match_set_misc, mask, inner_second_vid);

	spec->outer_second_cvlan_tag =
		MLX5_GET(fte_match_set_misc, mask, outer_second_cvlan_tag);
	spec->inner_second_cvlan_tag =
		MLX5_GET(fte_match_set_misc, mask, inner_second_cvlan_tag);
	spec->outer_second_svlan_tag =
		MLX5_GET(fte_match_set_misc, mask, outer_second_svlan_tag);
	spec->inner_second_svlan_tag =
		MLX5_GET(fte_match_set_misc, mask, inner_second_svlan_tag);

	spec->gre_protocol = MLX5_GET(fte_match_set_misc, mask, gre_protocol);

	spec->gre_key_h = MLX5_GET(fte_match_set_misc, mask, gre_key.nvgre.hi);
	spec->gre_key_l = MLX5_GET(fte_match_set_misc, mask, gre_key.nvgre.lo);

	spec->vxlan_vni = MLX5_GET(fte_match_set_misc, mask, vxlan_vni);

	spec->geneve_vni = MLX5_GET(fte_match_set_misc, mask, geneve_vni);
	spec->geneve_oam = MLX5_GET(fte_match_set_misc, mask, geneve_oam);

	spec->outer_ipv6_flow_label =
		MLX5_GET(fte_match_set_misc, mask, outer_ipv6_flow_label);

	spec->inner_ipv6_flow_label =
		MLX5_GET(fte_match_set_misc, mask, inner_ipv6_flow_label);

	spec->geneve_opt_len = MLX5_GET(fte_match_set_misc, mask, geneve_opt_len);
	spec->geneve_protocol_type =
		MLX5_GET(fte_match_set_misc, mask, geneve_protocol_type);

	spec->bth_dst_qp = MLX5_GET(fte_match_set_misc, mask, bth_dst_qp);
पूर्ण

अटल व्योम dr_ste_copy_mask_spec(अक्षर *mask, काष्ठा mlx5dr_match_spec *spec)
अणु
	__be32 raw_ip[4];

	spec->smac_47_16 = MLX5_GET(fte_match_set_lyr_2_4, mask, smac_47_16);

	spec->smac_15_0 = MLX5_GET(fte_match_set_lyr_2_4, mask, smac_15_0);
	spec->ethertype = MLX5_GET(fte_match_set_lyr_2_4, mask, ethertype);

	spec->dmac_47_16 = MLX5_GET(fte_match_set_lyr_2_4, mask, dmac_47_16);

	spec->dmac_15_0 = MLX5_GET(fte_match_set_lyr_2_4, mask, dmac_15_0);
	spec->first_prio = MLX5_GET(fte_match_set_lyr_2_4, mask, first_prio);
	spec->first_cfi = MLX5_GET(fte_match_set_lyr_2_4, mask, first_cfi);
	spec->first_vid = MLX5_GET(fte_match_set_lyr_2_4, mask, first_vid);

	spec->ip_protocol = MLX5_GET(fte_match_set_lyr_2_4, mask, ip_protocol);
	spec->ip_dscp = MLX5_GET(fte_match_set_lyr_2_4, mask, ip_dscp);
	spec->ip_ecn = MLX5_GET(fte_match_set_lyr_2_4, mask, ip_ecn);
	spec->cvlan_tag = MLX5_GET(fte_match_set_lyr_2_4, mask, cvlan_tag);
	spec->svlan_tag = MLX5_GET(fte_match_set_lyr_2_4, mask, svlan_tag);
	spec->frag = MLX5_GET(fte_match_set_lyr_2_4, mask, frag);
	spec->ip_version = MLX5_GET(fte_match_set_lyr_2_4, mask, ip_version);
	spec->tcp_flags = MLX5_GET(fte_match_set_lyr_2_4, mask, tcp_flags);
	spec->tcp_sport = MLX5_GET(fte_match_set_lyr_2_4, mask, tcp_sport);
	spec->tcp_dport = MLX5_GET(fte_match_set_lyr_2_4, mask, tcp_dport);

	spec->ttl_hoplimit = MLX5_GET(fte_match_set_lyr_2_4, mask, ttl_hoplimit);

	spec->udp_sport = MLX5_GET(fte_match_set_lyr_2_4, mask, udp_sport);
	spec->udp_dport = MLX5_GET(fte_match_set_lyr_2_4, mask, udp_dport);

	स_नकल(raw_ip, MLX5_ADDR_OF(fte_match_set_lyr_2_4, mask,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
				    माप(raw_ip));

	spec->src_ip_127_96 = be32_to_cpu(raw_ip[0]);
	spec->src_ip_95_64 = be32_to_cpu(raw_ip[1]);
	spec->src_ip_63_32 = be32_to_cpu(raw_ip[2]);
	spec->src_ip_31_0 = be32_to_cpu(raw_ip[3]);

	स_नकल(raw_ip, MLX5_ADDR_OF(fte_match_set_lyr_2_4, mask,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
				    माप(raw_ip));

	spec->dst_ip_127_96 = be32_to_cpu(raw_ip[0]);
	spec->dst_ip_95_64 = be32_to_cpu(raw_ip[1]);
	spec->dst_ip_63_32 = be32_to_cpu(raw_ip[2]);
	spec->dst_ip_31_0 = be32_to_cpu(raw_ip[3]);
पूर्ण

अटल व्योम dr_ste_copy_mask_misc2(अक्षर *mask, काष्ठा mlx5dr_match_misc2 *spec)
अणु
	spec->outer_first_mpls_label =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls.mpls_label);
	spec->outer_first_mpls_exp =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls.mpls_exp);
	spec->outer_first_mpls_s_bos =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls.mpls_s_bos);
	spec->outer_first_mpls_ttl =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls.mpls_ttl);
	spec->inner_first_mpls_label =
		MLX5_GET(fte_match_set_misc2, mask, inner_first_mpls.mpls_label);
	spec->inner_first_mpls_exp =
		MLX5_GET(fte_match_set_misc2, mask, inner_first_mpls.mpls_exp);
	spec->inner_first_mpls_s_bos =
		MLX5_GET(fte_match_set_misc2, mask, inner_first_mpls.mpls_s_bos);
	spec->inner_first_mpls_ttl =
		MLX5_GET(fte_match_set_misc2, mask, inner_first_mpls.mpls_ttl);
	spec->outer_first_mpls_over_gre_label =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_gre.mpls_label);
	spec->outer_first_mpls_over_gre_exp =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_gre.mpls_exp);
	spec->outer_first_mpls_over_gre_s_bos =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_gre.mpls_s_bos);
	spec->outer_first_mpls_over_gre_ttl =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_gre.mpls_ttl);
	spec->outer_first_mpls_over_udp_label =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_udp.mpls_label);
	spec->outer_first_mpls_over_udp_exp =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_udp.mpls_exp);
	spec->outer_first_mpls_over_udp_s_bos =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_udp.mpls_s_bos);
	spec->outer_first_mpls_over_udp_ttl =
		MLX5_GET(fte_match_set_misc2, mask, outer_first_mpls_over_udp.mpls_ttl);
	spec->metadata_reg_c_7 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_7);
	spec->metadata_reg_c_6 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_6);
	spec->metadata_reg_c_5 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_5);
	spec->metadata_reg_c_4 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_4);
	spec->metadata_reg_c_3 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_3);
	spec->metadata_reg_c_2 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_2);
	spec->metadata_reg_c_1 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_1);
	spec->metadata_reg_c_0 = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_c_0);
	spec->metadata_reg_a = MLX5_GET(fte_match_set_misc2, mask, metadata_reg_a);
पूर्ण

अटल व्योम dr_ste_copy_mask_misc3(अक्षर *mask, काष्ठा mlx5dr_match_misc3 *spec)
अणु
	spec->inner_tcp_seq_num = MLX5_GET(fte_match_set_misc3, mask, inner_tcp_seq_num);
	spec->outer_tcp_seq_num = MLX5_GET(fte_match_set_misc3, mask, outer_tcp_seq_num);
	spec->inner_tcp_ack_num = MLX5_GET(fte_match_set_misc3, mask, inner_tcp_ack_num);
	spec->outer_tcp_ack_num = MLX5_GET(fte_match_set_misc3, mask, outer_tcp_ack_num);
	spec->outer_vxlan_gpe_vni =
		MLX5_GET(fte_match_set_misc3, mask, outer_vxlan_gpe_vni);
	spec->outer_vxlan_gpe_next_protocol =
		MLX5_GET(fte_match_set_misc3, mask, outer_vxlan_gpe_next_protocol);
	spec->outer_vxlan_gpe_flags =
		MLX5_GET(fte_match_set_misc3, mask, outer_vxlan_gpe_flags);
	spec->icmpv4_header_data = MLX5_GET(fte_match_set_misc3, mask, icmp_header_data);
	spec->icmpv6_header_data =
		MLX5_GET(fte_match_set_misc3, mask, icmpv6_header_data);
	spec->icmpv4_type = MLX5_GET(fte_match_set_misc3, mask, icmp_type);
	spec->icmpv4_code = MLX5_GET(fte_match_set_misc3, mask, icmp_code);
	spec->icmpv6_type = MLX5_GET(fte_match_set_misc3, mask, icmpv6_type);
	spec->icmpv6_code = MLX5_GET(fte_match_set_misc3, mask, icmpv6_code);
	spec->geneve_tlv_option_0_data =
		MLX5_GET(fte_match_set_misc3, mask, geneve_tlv_option_0_data);
	spec->gtpu_msg_flags = MLX5_GET(fte_match_set_misc3, mask, gtpu_msg_flags);
	spec->gtpu_msg_type = MLX5_GET(fte_match_set_misc3, mask, gtpu_msg_type);
	spec->gtpu_teid = MLX5_GET(fte_match_set_misc3, mask, gtpu_teid);
	spec->gtpu_dw_0 = MLX5_GET(fte_match_set_misc3, mask, gtpu_dw_0);
	spec->gtpu_dw_2 = MLX5_GET(fte_match_set_misc3, mask, gtpu_dw_2);
	spec->gtpu_first_ext_dw_0 =
		MLX5_GET(fte_match_set_misc3, mask, gtpu_first_ext_dw_0);
पूर्ण

अटल व्योम dr_ste_copy_mask_misc4(अक्षर *mask, काष्ठा mlx5dr_match_misc4 *spec)
अणु
	spec->prog_sample_field_id_0 =
		MLX5_GET(fte_match_set_misc4, mask, prog_sample_field_id_0);
	spec->prog_sample_field_value_0 =
		MLX5_GET(fte_match_set_misc4, mask, prog_sample_field_value_0);
	spec->prog_sample_field_id_1 =
		MLX5_GET(fte_match_set_misc4, mask, prog_sample_field_id_1);
	spec->prog_sample_field_value_1 =
		MLX5_GET(fte_match_set_misc4, mask, prog_sample_field_value_1);
	spec->prog_sample_field_id_2 =
		MLX5_GET(fte_match_set_misc4, mask, prog_sample_field_id_2);
	spec->prog_sample_field_value_2 =
		MLX5_GET(fte_match_set_misc4, mask, prog_sample_field_value_2);
	spec->prog_sample_field_id_3 =
		MLX5_GET(fte_match_set_misc4, mask, prog_sample_field_id_3);
	spec->prog_sample_field_value_3 =
		MLX5_GET(fte_match_set_misc4, mask, prog_sample_field_value_3);
पूर्ण

व्योम mlx5dr_ste_copy_param(u8 match_criteria,
			   काष्ठा mlx5dr_match_param *set_param,
			   काष्ठा mlx5dr_match_parameters *mask)
अणु
	u8 tail_param[MLX5_ST_SZ_BYTES(fte_match_set_lyr_2_4)] = अणुपूर्ण;
	u8 *data = (u8 *)mask->match_buf;
	माप_प्रकार param_location;
	व्योम *buff;

	अगर (match_criteria & DR_MATCHER_CRITERIA_OUTER) अणु
		अगर (mask->match_sz < माप(काष्ठा mlx5dr_match_spec)) अणु
			स_नकल(tail_param, data, mask->match_sz);
			buff = tail_param;
		पूर्ण अन्यथा अणु
			buff = mask->match_buf;
		पूर्ण
		dr_ste_copy_mask_spec(buff, &set_param->outer);
	पूर्ण
	param_location = माप(काष्ठा mlx5dr_match_spec);

	अगर (match_criteria & DR_MATCHER_CRITERIA_MISC) अणु
		अगर (mask->match_sz < param_location +
		    माप(काष्ठा mlx5dr_match_misc)) अणु
			स_नकल(tail_param, data + param_location,
			       mask->match_sz - param_location);
			buff = tail_param;
		पूर्ण अन्यथा अणु
			buff = data + param_location;
		पूर्ण
		dr_ste_copy_mask_misc(buff, &set_param->misc);
	पूर्ण
	param_location += माप(काष्ठा mlx5dr_match_misc);

	अगर (match_criteria & DR_MATCHER_CRITERIA_INNER) अणु
		अगर (mask->match_sz < param_location +
		    माप(काष्ठा mlx5dr_match_spec)) अणु
			स_नकल(tail_param, data + param_location,
			       mask->match_sz - param_location);
			buff = tail_param;
		पूर्ण अन्यथा अणु
			buff = data + param_location;
		पूर्ण
		dr_ste_copy_mask_spec(buff, &set_param->inner);
	पूर्ण
	param_location += माप(काष्ठा mlx5dr_match_spec);

	अगर (match_criteria & DR_MATCHER_CRITERIA_MISC2) अणु
		अगर (mask->match_sz < param_location +
		    माप(काष्ठा mlx5dr_match_misc2)) अणु
			स_नकल(tail_param, data + param_location,
			       mask->match_sz - param_location);
			buff = tail_param;
		पूर्ण अन्यथा अणु
			buff = data + param_location;
		पूर्ण
		dr_ste_copy_mask_misc2(buff, &set_param->misc2);
	पूर्ण

	param_location += माप(काष्ठा mlx5dr_match_misc2);

	अगर (match_criteria & DR_MATCHER_CRITERIA_MISC3) अणु
		अगर (mask->match_sz < param_location +
		    माप(काष्ठा mlx5dr_match_misc3)) अणु
			स_नकल(tail_param, data + param_location,
			       mask->match_sz - param_location);
			buff = tail_param;
		पूर्ण अन्यथा अणु
			buff = data + param_location;
		पूर्ण
		dr_ste_copy_mask_misc3(buff, &set_param->misc3);
	पूर्ण

	param_location += माप(काष्ठा mlx5dr_match_misc3);

	अगर (match_criteria & DR_MATCHER_CRITERIA_MISC4) अणु
		अगर (mask->match_sz < param_location +
		    माप(काष्ठा mlx5dr_match_misc4)) अणु
			स_नकल(tail_param, data + param_location,
			       mask->match_sz - param_location);
			buff = tail_param;
		पूर्ण अन्यथा अणु
			buff = data + param_location;
		पूर्ण
		dr_ste_copy_mask_misc4(buff, &set_param->misc4);
	पूर्ण
पूर्ण

व्योम mlx5dr_ste_build_eth_l2_src_dst(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				     काष्ठा mlx5dr_ste_build *sb,
				     काष्ठा mlx5dr_match_param *mask,
				     bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_l2_src_dst_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_eth_l3_ipv6_dst(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				      काष्ठा mlx5dr_ste_build *sb,
				      काष्ठा mlx5dr_match_param *mask,
				      bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_l3_ipv6_dst_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_eth_l3_ipv6_src(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				      काष्ठा mlx5dr_ste_build *sb,
				      काष्ठा mlx5dr_match_param *mask,
				      bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_l3_ipv6_src_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_eth_l3_ipv4_5_tuple(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					  काष्ठा mlx5dr_ste_build *sb,
					  काष्ठा mlx5dr_match_param *mask,
					  bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_l3_ipv4_5_tuple_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_eth_l2_src(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_l2_src_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_eth_l2_dst(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_l2_dst_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_eth_l2_tnl(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask, bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_l2_tnl_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_eth_l3_ipv4_misc(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				       काष्ठा mlx5dr_ste_build *sb,
				       काष्ठा mlx5dr_match_param *mask,
				       bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_l3_ipv4_misc_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_eth_ipv6_l3_l4(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				     काष्ठा mlx5dr_ste_build *sb,
				     काष्ठा mlx5dr_match_param *mask,
				     bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_ipv6_l3_l4_init(sb, mask);
पूर्ण

अटल पूर्णांक dr_ste_build_empty_always_hit_tag(काष्ठा mlx5dr_match_param *value,
					     काष्ठा mlx5dr_ste_build *sb,
					     u8 *tag)
अणु
	वापस 0;
पूर्ण

व्योम mlx5dr_ste_build_empty_always_hit(काष्ठा mlx5dr_ste_build *sb, bool rx)
अणु
	sb->rx = rx;
	sb->lu_type = MLX5DR_STE_LU_TYPE_DONT_CARE;
	sb->byte_mask = 0;
	sb->ste_build_tag_func = &dr_ste_build_empty_always_hit_tag;
पूर्ण

व्योम mlx5dr_ste_build_mpls(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			   काष्ठा mlx5dr_ste_build *sb,
			   काष्ठा mlx5dr_match_param *mask,
			   bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_mpls_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_tnl_gre(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			      काष्ठा mlx5dr_ste_build *sb,
			      काष्ठा mlx5dr_match_param *mask,
			      bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_tnl_gre_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_tnl_mpls_over_gre(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					काष्ठा mlx5dr_ste_build *sb,
					काष्ठा mlx5dr_match_param *mask,
					काष्ठा mlx5dr_cmd_caps *caps,
					bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	sb->caps = caps;
	वापस ste_ctx->build_tnl_mpls_over_gre_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_tnl_mpls_over_udp(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					काष्ठा mlx5dr_ste_build *sb,
					काष्ठा mlx5dr_match_param *mask,
					काष्ठा mlx5dr_cmd_caps *caps,
					bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	sb->caps = caps;
	वापस ste_ctx->build_tnl_mpls_over_udp_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_icmp(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			   काष्ठा mlx5dr_ste_build *sb,
			   काष्ठा mlx5dr_match_param *mask,
			   काष्ठा mlx5dr_cmd_caps *caps,
			   bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	sb->caps = caps;
	ste_ctx->build_icmp_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_general_purpose(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				      काष्ठा mlx5dr_ste_build *sb,
				      काष्ठा mlx5dr_match_param *mask,
				      bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_general_purpose_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_eth_l4_misc(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				  काष्ठा mlx5dr_ste_build *sb,
				  काष्ठा mlx5dr_match_param *mask,
				  bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_eth_l4_misc_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_tnl_vxlan_gpe(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				    काष्ठा mlx5dr_ste_build *sb,
				    काष्ठा mlx5dr_match_param *mask,
				    bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_tnl_vxlan_gpe_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_tnl_geneve(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_tnl_geneve_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_tnl_geneve_tlv_opt(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					 काष्ठा mlx5dr_ste_build *sb,
					 काष्ठा mlx5dr_match_param *mask,
					 काष्ठा mlx5dr_cmd_caps *caps,
					 bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->caps = caps;
	sb->inner = inner;
	ste_ctx->build_tnl_geneve_tlv_opt_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_tnl_gtpu(काष्ठा mlx5dr_ste_ctx *ste_ctx,
			       काष्ठा mlx5dr_ste_build *sb,
			       काष्ठा mlx5dr_match_param *mask,
			       bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_tnl_gtpu_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_tnl_gtpu_flex_parser_0(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					     काष्ठा mlx5dr_ste_build *sb,
					     काष्ठा mlx5dr_match_param *mask,
					     काष्ठा mlx5dr_cmd_caps *caps,
					     bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->caps = caps;
	sb->inner = inner;
	ste_ctx->build_tnl_gtpu_flex_parser_0_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_tnl_gtpu_flex_parser_1(काष्ठा mlx5dr_ste_ctx *ste_ctx,
					     काष्ठा mlx5dr_ste_build *sb,
					     काष्ठा mlx5dr_match_param *mask,
					     काष्ठा mlx5dr_cmd_caps *caps,
					     bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->caps = caps;
	sb->inner = inner;
	ste_ctx->build_tnl_gtpu_flex_parser_1_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_रेजिस्टर_0(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_रेजिस्टर_0_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_रेजिस्टर_1(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				 काष्ठा mlx5dr_ste_build *sb,
				 काष्ठा mlx5dr_match_param *mask,
				 bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_रेजिस्टर_1_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_src_gvmi_qpn(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				   काष्ठा mlx5dr_ste_build *sb,
				   काष्ठा mlx5dr_match_param *mask,
				   काष्ठा mlx5dr_करोमुख्य *dmn,
				   bool inner, bool rx)
अणु
	/* Set vhca_id_valid beक्रमe we reset source_eचयन_owner_vhca_id */
	sb->vhca_id_valid = mask->misc.source_eचयन_owner_vhca_id;

	sb->rx = rx;
	sb->dmn = dmn;
	sb->inner = inner;
	ste_ctx->build_src_gvmi_qpn_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_flex_parser_0(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				    काष्ठा mlx5dr_ste_build *sb,
				    काष्ठा mlx5dr_match_param *mask,
				    bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_flex_parser_0_init(sb, mask);
पूर्ण

व्योम mlx5dr_ste_build_flex_parser_1(काष्ठा mlx5dr_ste_ctx *ste_ctx,
				    काष्ठा mlx5dr_ste_build *sb,
				    काष्ठा mlx5dr_match_param *mask,
				    bool inner, bool rx)
अणु
	sb->rx = rx;
	sb->inner = inner;
	ste_ctx->build_flex_parser_1_init(sb, mask);
पूर्ण

अटल काष्ठा mlx5dr_ste_ctx *mlx5dr_ste_ctx_arr[] = अणु
	[MLX5_STEERING_FORMAT_CONNECTX_5] = &ste_ctx_v0,
	[MLX5_STEERING_FORMAT_CONNECTX_6DX] = &ste_ctx_v1,
पूर्ण;

काष्ठा mlx5dr_ste_ctx *mlx5dr_ste_get_ctx(u8 version)
अणु
	अगर (version > MLX5_STEERING_FORMAT_CONNECTX_6DX)
		वापस शून्य;

	वापस mlx5dr_ste_ctx_arr[version];
पूर्ण
