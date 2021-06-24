<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश "dr_types.h"

#घोषणा DR_ICM_MODIFY_HDR_ALIGN_BASE 64
#घोषणा DR_ICM_SYNC_THRESHOLD_POOL (64 * 1024 * 1024)

काष्ठा mlx5dr_icm_pool अणु
	क्रमागत mlx5dr_icm_type icm_type;
	क्रमागत mlx5dr_icm_chunk_size max_log_chunk_sz;
	काष्ठा mlx5dr_करोमुख्य *dmn;
	/* memory management */
	काष्ठा mutex mutex; /* protect the ICM pool and ICM buddy */
	काष्ठा list_head buddy_mem_list;
	u64 hot_memory_size;
पूर्ण;

काष्ठा mlx5dr_icm_dm अणु
	u32 obj_id;
	क्रमागत mlx5_sw_icm_type type;
	phys_addr_t addr;
	माप_प्रकार length;
पूर्ण;

काष्ठा mlx5dr_icm_mr अणु
	काष्ठा mlx5_core_mkey mkey;
	काष्ठा mlx5dr_icm_dm dm;
	काष्ठा mlx5dr_करोमुख्य *dmn;
	माप_प्रकार length;
	u64 icm_start_addr;
पूर्ण;

अटल पूर्णांक dr_icm_create_dm_mkey(काष्ठा mlx5_core_dev *mdev,
				 u32 pd, u64 length, u64 start_addr, पूर्णांक mode,
				 काष्ठा mlx5_core_mkey *mkey)
अणु
	u32 inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	u32 in[MLX5_ST_SZ_DW(create_mkey_in)] = अणुपूर्ण;
	व्योम *mkc;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);

	MLX5_SET(mkc, mkc, access_mode_1_0, mode);
	MLX5_SET(mkc, mkc, access_mode_4_2, (mode >> 2) & 0x7);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, lr, 1);
	अगर (mode == MLX5_MKC_ACCESS_MODE_SW_ICM) अणु
		MLX5_SET(mkc, mkc, rw, 1);
		MLX5_SET(mkc, mkc, rr, 1);
	पूर्ण

	MLX5_SET64(mkc, mkc, len, length);
	MLX5_SET(mkc, mkc, pd, pd);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);
	MLX5_SET64(mkc, mkc, start_addr, start_addr);

	वापस mlx5_core_create_mkey(mdev, mkey, in, inlen);
पूर्ण

अटल काष्ठा mlx5dr_icm_mr *
dr_icm_pool_mr_create(काष्ठा mlx5dr_icm_pool *pool)
अणु
	काष्ठा mlx5_core_dev *mdev = pool->dmn->mdev;
	क्रमागत mlx5_sw_icm_type dm_type;
	काष्ठा mlx5dr_icm_mr *icm_mr;
	माप_प्रकार log_align_base;
	पूर्णांक err;

	icm_mr = kvzalloc(माप(*icm_mr), GFP_KERNEL);
	अगर (!icm_mr)
		वापस शून्य;

	icm_mr->dmn = pool->dmn;

	icm_mr->dm.length = mlx5dr_icm_pool_chunk_माप_प्रकारo_byte(pool->max_log_chunk_sz,
							       pool->icm_type);

	अगर (pool->icm_type == DR_ICM_TYPE_STE) अणु
		dm_type = MLX5_SW_ICM_TYPE_STEERING;
		log_align_base = ilog2(icm_mr->dm.length);
	पूर्ण अन्यथा अणु
		dm_type = MLX5_SW_ICM_TYPE_HEADER_MODIFY;
		/* Align base is 64B */
		log_align_base = ilog2(DR_ICM_MODIFY_HDR_ALIGN_BASE);
	पूर्ण
	icm_mr->dm.type = dm_type;

	err = mlx5_dm_sw_icm_alloc(mdev, icm_mr->dm.type, icm_mr->dm.length,
				   log_align_base, 0, &icm_mr->dm.addr,
				   &icm_mr->dm.obj_id);
	अगर (err) अणु
		mlx5dr_err(pool->dmn, "Failed to allocate SW ICM memory, err (%d)\n", err);
		जाओ मुक्त_icm_mr;
	पूर्ण

	/* Register device memory */
	err = dr_icm_create_dm_mkey(mdev, pool->dmn->pdn,
				    icm_mr->dm.length,
				    icm_mr->dm.addr,
				    MLX5_MKC_ACCESS_MODE_SW_ICM,
				    &icm_mr->mkey);
	अगर (err) अणु
		mlx5dr_err(pool->dmn, "Failed to create SW ICM MKEY, err (%d)\n", err);
		जाओ मुक्त_dm;
	पूर्ण

	icm_mr->icm_start_addr = icm_mr->dm.addr;

	अगर (icm_mr->icm_start_addr & (BIT(log_align_base) - 1)) अणु
		mlx5dr_err(pool->dmn, "Failed to get Aligned ICM mem (asked: %zu)\n",
			   log_align_base);
		जाओ मुक्त_mkey;
	पूर्ण

	वापस icm_mr;

मुक्त_mkey:
	mlx5_core_destroy_mkey(mdev, &icm_mr->mkey);
मुक्त_dm:
	mlx5_dm_sw_icm_dealloc(mdev, icm_mr->dm.type, icm_mr->dm.length, 0,
			       icm_mr->dm.addr, icm_mr->dm.obj_id);
मुक्त_icm_mr:
	kvमुक्त(icm_mr);
	वापस शून्य;
पूर्ण

अटल व्योम dr_icm_pool_mr_destroy(काष्ठा mlx5dr_icm_mr *icm_mr)
अणु
	काष्ठा mlx5_core_dev *mdev = icm_mr->dmn->mdev;
	काष्ठा mlx5dr_icm_dm *dm = &icm_mr->dm;

	mlx5_core_destroy_mkey(mdev, &icm_mr->mkey);
	mlx5_dm_sw_icm_dealloc(mdev, dm->type, dm->length, 0,
			       dm->addr, dm->obj_id);
	kvमुक्त(icm_mr);
पूर्ण

अटल पूर्णांक dr_icm_chunk_ste_init(काष्ठा mlx5dr_icm_chunk *chunk)
अणु
	chunk->ste_arr = kvzalloc(chunk->num_of_entries *
				  माप(chunk->ste_arr[0]), GFP_KERNEL);
	अगर (!chunk->ste_arr)
		वापस -ENOMEM;

	chunk->hw_ste_arr = kvzalloc(chunk->num_of_entries *
				     DR_STE_SIZE_REDUCED, GFP_KERNEL);
	अगर (!chunk->hw_ste_arr)
		जाओ out_मुक्त_ste_arr;

	chunk->miss_list = kvदो_स्मृति(chunk->num_of_entries *
				    माप(chunk->miss_list[0]), GFP_KERNEL);
	अगर (!chunk->miss_list)
		जाओ out_मुक्त_hw_ste_arr;

	वापस 0;

out_मुक्त_hw_ste_arr:
	kvमुक्त(chunk->hw_ste_arr);
out_मुक्त_ste_arr:
	kvमुक्त(chunk->ste_arr);
	वापस -ENOMEM;
पूर्ण

अटल व्योम dr_icm_chunk_ste_cleanup(काष्ठा mlx5dr_icm_chunk *chunk)
अणु
	kvमुक्त(chunk->miss_list);
	kvमुक्त(chunk->hw_ste_arr);
	kvमुक्त(chunk->ste_arr);
पूर्ण

अटल क्रमागत mlx5dr_icm_type
get_chunk_icm_type(काष्ठा mlx5dr_icm_chunk *chunk)
अणु
	वापस chunk->buddy_mem->pool->icm_type;
पूर्ण

अटल व्योम dr_icm_chunk_destroy(काष्ठा mlx5dr_icm_chunk *chunk,
				 काष्ठा mlx5dr_icm_buddy_mem *buddy)
अणु
	क्रमागत mlx5dr_icm_type icm_type = get_chunk_icm_type(chunk);

	buddy->used_memory -= chunk->byte_size;
	list_del(&chunk->chunk_list);

	अगर (icm_type == DR_ICM_TYPE_STE)
		dr_icm_chunk_ste_cleanup(chunk);

	kvमुक्त(chunk);
पूर्ण

अटल पूर्णांक dr_icm_buddy_create(काष्ठा mlx5dr_icm_pool *pool)
अणु
	काष्ठा mlx5dr_icm_buddy_mem *buddy;
	काष्ठा mlx5dr_icm_mr *icm_mr;

	icm_mr = dr_icm_pool_mr_create(pool);
	अगर (!icm_mr)
		वापस -ENOMEM;

	buddy = kvzalloc(माप(*buddy), GFP_KERNEL);
	अगर (!buddy)
		जाओ मुक्त_mr;

	अगर (mlx5dr_buddy_init(buddy, pool->max_log_chunk_sz))
		जाओ err_मुक्त_buddy;

	buddy->icm_mr = icm_mr;
	buddy->pool = pool;

	/* add it to the -start- of the list in order to search in it first */
	list_add(&buddy->list_node, &pool->buddy_mem_list);

	वापस 0;

err_मुक्त_buddy:
	kvमुक्त(buddy);
मुक्त_mr:
	dr_icm_pool_mr_destroy(icm_mr);
	वापस -ENOMEM;
पूर्ण

अटल व्योम dr_icm_buddy_destroy(काष्ठा mlx5dr_icm_buddy_mem *buddy)
अणु
	काष्ठा mlx5dr_icm_chunk *chunk, *next;

	list_क्रम_each_entry_safe(chunk, next, &buddy->hot_list, chunk_list)
		dr_icm_chunk_destroy(chunk, buddy);

	list_क्रम_each_entry_safe(chunk, next, &buddy->used_list, chunk_list)
		dr_icm_chunk_destroy(chunk, buddy);

	dr_icm_pool_mr_destroy(buddy->icm_mr);

	mlx5dr_buddy_cleanup(buddy);

	kvमुक्त(buddy);
पूर्ण

अटल काष्ठा mlx5dr_icm_chunk *
dr_icm_chunk_create(काष्ठा mlx5dr_icm_pool *pool,
		    क्रमागत mlx5dr_icm_chunk_size chunk_size,
		    काष्ठा mlx5dr_icm_buddy_mem *buddy_mem_pool,
		    अचिन्हित पूर्णांक seg)
अणु
	काष्ठा mlx5dr_icm_chunk *chunk;
	पूर्णांक offset;

	chunk = kvzalloc(माप(*chunk), GFP_KERNEL);
	अगर (!chunk)
		वापस शून्य;

	offset = mlx5dr_icm_pool_dm_type_to_entry_size(pool->icm_type) * seg;

	chunk->rkey = buddy_mem_pool->icm_mr->mkey.key;
	chunk->mr_addr = offset;
	chunk->icm_addr =
		(uपूर्णांकptr_t)buddy_mem_pool->icm_mr->icm_start_addr + offset;
	chunk->num_of_entries =
		mlx5dr_icm_pool_chunk_माप_प्रकारo_entries(chunk_size);
	chunk->byte_size =
		mlx5dr_icm_pool_chunk_माप_प्रकारo_byte(chunk_size, pool->icm_type);
	chunk->seg = seg;

	अगर (pool->icm_type == DR_ICM_TYPE_STE && dr_icm_chunk_ste_init(chunk)) अणु
		mlx5dr_err(pool->dmn,
			   "Failed to init ste arrays (order: %d)\n",
			   chunk_size);
		जाओ out_मुक्त_chunk;
	पूर्ण

	buddy_mem_pool->used_memory += chunk->byte_size;
	chunk->buddy_mem = buddy_mem_pool;
	INIT_LIST_HEAD(&chunk->chunk_list);

	/* chunk now is part of the used_list */
	list_add_tail(&chunk->chunk_list, &buddy_mem_pool->used_list);

	वापस chunk;

out_मुक्त_chunk:
	kvमुक्त(chunk);
	वापस शून्य;
पूर्ण

अटल bool dr_icm_pool_is_sync_required(काष्ठा mlx5dr_icm_pool *pool)
अणु
	अगर (pool->hot_memory_size > DR_ICM_SYNC_THRESHOLD_POOL)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक dr_icm_pool_sync_all_buddy_pools(काष्ठा mlx5dr_icm_pool *pool)
अणु
	काष्ठा mlx5dr_icm_buddy_mem *buddy, *पंचांगp_buddy;
	पूर्णांक err;

	err = mlx5dr_cmd_sync_steering(pool->dmn->mdev);
	अगर (err) अणु
		mlx5dr_err(pool->dmn, "Failed to sync to HW (err: %d)\n", err);
		वापस err;
	पूर्ण

	list_क्रम_each_entry_safe(buddy, पंचांगp_buddy, &pool->buddy_mem_list, list_node) अणु
		काष्ठा mlx5dr_icm_chunk *chunk, *पंचांगp_chunk;

		list_क्रम_each_entry_safe(chunk, पंचांगp_chunk, &buddy->hot_list, chunk_list) अणु
			mlx5dr_buddy_मुक्त_mem(buddy, chunk->seg,
					      ilog2(chunk->num_of_entries));
			pool->hot_memory_size -= chunk->byte_size;
			dr_icm_chunk_destroy(chunk, buddy);
		पूर्ण

		अगर (!buddy->used_memory && pool->icm_type == DR_ICM_TYPE_STE)
			dr_icm_buddy_destroy(buddy);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dr_icm_handle_buddies_get_mem(काष्ठा mlx5dr_icm_pool *pool,
					 क्रमागत mlx5dr_icm_chunk_size chunk_size,
					 काष्ठा mlx5dr_icm_buddy_mem **buddy,
					 अचिन्हित पूर्णांक *seg)
अणु
	काष्ठा mlx5dr_icm_buddy_mem *buddy_mem_pool;
	bool new_mem = false;
	पूर्णांक err;

alloc_buddy_mem:
	/* find the next मुक्त place from the buddy list */
	list_क्रम_each_entry(buddy_mem_pool, &pool->buddy_mem_list, list_node) अणु
		err = mlx5dr_buddy_alloc_mem(buddy_mem_pool,
					     chunk_size, seg);
		अगर (!err)
			जाओ found;

		अगर (WARN_ON(new_mem)) अणु
			/* We have new memory pool, first in the list */
			mlx5dr_err(pool->dmn,
				   "No memory for order: %d\n",
				   chunk_size);
			जाओ out;
		पूर्ण
	पूर्ण

	/* no more available allocators in that pool, create new */
	err = dr_icm_buddy_create(pool);
	अगर (err) अणु
		mlx5dr_err(pool->dmn,
			   "Failed creating buddy for order %d\n",
			   chunk_size);
		जाओ out;
	पूर्ण

	/* mark we have new memory, first in list */
	new_mem = true;
	जाओ alloc_buddy_mem;

found:
	*buddy = buddy_mem_pool;
out:
	वापस err;
पूर्ण

/* Allocate an ICM chunk, each chunk holds a piece of ICM memory and
 * also memory used क्रम HW STE management क्रम optimizations.
 */
काष्ठा mlx5dr_icm_chunk *
mlx5dr_icm_alloc_chunk(काष्ठा mlx5dr_icm_pool *pool,
		       क्रमागत mlx5dr_icm_chunk_size chunk_size)
अणु
	काष्ठा mlx5dr_icm_chunk *chunk = शून्य;
	काष्ठा mlx5dr_icm_buddy_mem *buddy;
	अचिन्हित पूर्णांक seg;
	पूर्णांक ret;

	अगर (chunk_size > pool->max_log_chunk_sz)
		वापस शून्य;

	mutex_lock(&pool->mutex);
	/* find mem, get back the relevant buddy pool and seg in that mem */
	ret = dr_icm_handle_buddies_get_mem(pool, chunk_size, &buddy, &seg);
	अगर (ret)
		जाओ out;

	chunk = dr_icm_chunk_create(pool, chunk_size, buddy, seg);
	अगर (!chunk)
		जाओ out_err;

	जाओ out;

out_err:
	mlx5dr_buddy_मुक्त_mem(buddy, seg, chunk_size);
out:
	mutex_unlock(&pool->mutex);
	वापस chunk;
पूर्ण

व्योम mlx5dr_icm_मुक्त_chunk(काष्ठा mlx5dr_icm_chunk *chunk)
अणु
	काष्ठा mlx5dr_icm_buddy_mem *buddy = chunk->buddy_mem;
	काष्ठा mlx5dr_icm_pool *pool = buddy->pool;

	/* move the memory to the रुकोing list AKA "hot" */
	mutex_lock(&pool->mutex);
	list_move_tail(&chunk->chunk_list, &buddy->hot_list);
	pool->hot_memory_size += chunk->byte_size;

	/* Check अगर we have chunks that are रुकोing क्रम sync-ste */
	अगर (dr_icm_pool_is_sync_required(pool))
		dr_icm_pool_sync_all_buddy_pools(pool);

	mutex_unlock(&pool->mutex);
पूर्ण

काष्ठा mlx5dr_icm_pool *mlx5dr_icm_pool_create(काष्ठा mlx5dr_करोमुख्य *dmn,
					       क्रमागत mlx5dr_icm_type icm_type)
अणु
	क्रमागत mlx5dr_icm_chunk_size max_log_chunk_sz;
	काष्ठा mlx5dr_icm_pool *pool;

	अगर (icm_type == DR_ICM_TYPE_STE)
		max_log_chunk_sz = dmn->info.max_log_sw_icm_sz;
	अन्यथा
		max_log_chunk_sz = dmn->info.max_log_action_icm_sz;

	pool = kvzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस शून्य;

	pool->dmn = dmn;
	pool->icm_type = icm_type;
	pool->max_log_chunk_sz = max_log_chunk_sz;

	INIT_LIST_HEAD(&pool->buddy_mem_list);

	mutex_init(&pool->mutex);

	वापस pool;
पूर्ण

व्योम mlx5dr_icm_pool_destroy(काष्ठा mlx5dr_icm_pool *pool)
अणु
	काष्ठा mlx5dr_icm_buddy_mem *buddy, *पंचांगp_buddy;

	list_क्रम_each_entry_safe(buddy, पंचांगp_buddy, &pool->buddy_mem_list, list_node)
		dr_icm_buddy_destroy(buddy);

	mutex_destroy(&pool->mutex);
	kvमुक्त(pool);
पूर्ण
