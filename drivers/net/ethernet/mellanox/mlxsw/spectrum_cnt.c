<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/spinlock.h>

#समावेश "spectrum_cnt.h"

काष्ठा mlxsw_sp_counter_sub_pool अणु
	u64 size;
	अचिन्हित पूर्णांक base_index;
	क्रमागत mlxsw_res_id entry_size_res_id;
	स्थिर अक्षर *resource_name; /* devlink resource name */
	u64 resource_id; /* devlink resource id */
	अचिन्हित पूर्णांक entry_size;
	अचिन्हित पूर्णांक bank_count;
	atomic_t active_entries_count;
पूर्ण;

काष्ठा mlxsw_sp_counter_pool अणु
	u64 pool_size;
	अचिन्हित दीर्घ *usage; /* Usage biपंचांगap */
	spinlock_t counter_pool_lock; /* Protects counter pool allocations */
	atomic_t active_entries_count;
	अचिन्हित पूर्णांक sub_pools_count;
	काष्ठा mlxsw_sp_counter_sub_pool sub_pools[];
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_counter_sub_pool mlxsw_sp_counter_sub_pools[] = अणु
	[MLXSW_SP_COUNTER_SUB_POOL_FLOW] = अणु
		.entry_size_res_id = MLXSW_RES_ID_COUNTER_SIZE_PACKETS_BYTES,
		.resource_name = MLXSW_SP_RESOURCE_NAME_COUNTERS_FLOW,
		.resource_id = MLXSW_SP_RESOURCE_COUNTERS_FLOW,
		.bank_count = 6,
	पूर्ण,
	[MLXSW_SP_COUNTER_SUB_POOL_RIF] = अणु
		.entry_size_res_id = MLXSW_RES_ID_COUNTER_SIZE_ROUTER_BASIC,
		.resource_name = MLXSW_SP_RESOURCE_NAME_COUNTERS_RIF,
		.resource_id = MLXSW_SP_RESOURCE_COUNTERS_RIF,
		.bank_count = 2,
	पूर्ण
पूर्ण;

अटल u64 mlxsw_sp_counter_sub_pool_occ_get(व्योम *priv)
अणु
	स्थिर काष्ठा mlxsw_sp_counter_sub_pool *sub_pool = priv;

	वापस atomic_पढ़ो(&sub_pool->active_entries_count);
पूर्ण

अटल पूर्णांक mlxsw_sp_counter_sub_pools_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_counter_pool *pool = mlxsw_sp->counter_pool;
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	काष्ठा mlxsw_sp_counter_sub_pool *sub_pool;
	अचिन्हित पूर्णांक base_index = 0;
	क्रमागत mlxsw_res_id res_id;
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < pool->sub_pools_count; i++) अणु
		sub_pool = &pool->sub_pools[i];
		res_id = sub_pool->entry_size_res_id;

		अगर (!mlxsw_core_res_valid(mlxsw_sp->core, res_id))
			वापस -EIO;
		sub_pool->entry_size = mlxsw_core_res_get(mlxsw_sp->core,
							  res_id);
		err = devlink_resource_size_get(devlink,
						sub_pool->resource_id,
						&sub_pool->size);
		अगर (err)
			जाओ err_resource_size_get;

		devlink_resource_occ_get_रेजिस्टर(devlink,
						  sub_pool->resource_id,
						  mlxsw_sp_counter_sub_pool_occ_get,
						  sub_pool);

		sub_pool->base_index = base_index;
		base_index += sub_pool->size;
		atomic_set(&sub_pool->active_entries_count, 0);
	पूर्ण
	वापस 0;

err_resource_size_get:
	क्रम (i--; i >= 0; i--) अणु
		sub_pool = &pool->sub_pools[i];

		devlink_resource_occ_get_unरेजिस्टर(devlink,
						    sub_pool->resource_id);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_counter_sub_pools_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_counter_pool *pool = mlxsw_sp->counter_pool;
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	काष्ठा mlxsw_sp_counter_sub_pool *sub_pool;
	पूर्णांक i;

	क्रम (i = 0; i < pool->sub_pools_count; i++) अणु
		sub_pool = &pool->sub_pools[i];

		WARN_ON(atomic_पढ़ो(&sub_pool->active_entries_count));
		devlink_resource_occ_get_unरेजिस्टर(devlink,
						    sub_pool->resource_id);
	पूर्ण
पूर्ण

अटल u64 mlxsw_sp_counter_pool_occ_get(व्योम *priv)
अणु
	स्थिर काष्ठा mlxsw_sp_counter_pool *pool = priv;

	वापस atomic_पढ़ो(&pool->active_entries_count);
पूर्ण

पूर्णांक mlxsw_sp_counter_pool_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	अचिन्हित पूर्णांक sub_pools_count = ARRAY_SIZE(mlxsw_sp_counter_sub_pools);
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	काष्ठा mlxsw_sp_counter_pool *pool;
	अचिन्हित पूर्णांक map_size;
	पूर्णांक err;

	pool = kzalloc(काष्ठा_size(pool, sub_pools, sub_pools_count),
		       GFP_KERNEL);
	अगर (!pool)
		वापस -ENOMEM;
	mlxsw_sp->counter_pool = pool;
	pool->sub_pools_count = sub_pools_count;
	स_नकल(pool->sub_pools, mlxsw_sp_counter_sub_pools,
	       flex_array_size(pool, sub_pools, pool->sub_pools_count));
	spin_lock_init(&pool->counter_pool_lock);
	atomic_set(&pool->active_entries_count, 0);

	err = devlink_resource_size_get(devlink, MLXSW_SP_RESOURCE_COUNTERS,
					&pool->pool_size);
	अगर (err)
		जाओ err_pool_resource_size_get;
	devlink_resource_occ_get_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_COUNTERS,
					  mlxsw_sp_counter_pool_occ_get, pool);

	map_size = BITS_TO_LONGS(pool->pool_size) * माप(अचिन्हित दीर्घ);

	pool->usage = kzalloc(map_size, GFP_KERNEL);
	अगर (!pool->usage) अणु
		err = -ENOMEM;
		जाओ err_usage_alloc;
	पूर्ण

	err = mlxsw_sp_counter_sub_pools_init(mlxsw_sp);
	अगर (err)
		जाओ err_sub_pools_init;

	वापस 0;

err_sub_pools_init:
	kमुक्त(pool->usage);
err_usage_alloc:
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    MLXSW_SP_RESOURCE_COUNTERS);
err_pool_resource_size_get:
	kमुक्त(pool);
	वापस err;
पूर्ण

व्योम mlxsw_sp_counter_pool_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_counter_pool *pool = mlxsw_sp->counter_pool;
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);

	mlxsw_sp_counter_sub_pools_fini(mlxsw_sp);
	WARN_ON(find_first_bit(pool->usage, pool->pool_size) !=
			       pool->pool_size);
	WARN_ON(atomic_पढ़ो(&pool->active_entries_count));
	kमुक्त(pool->usage);
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    MLXSW_SP_RESOURCE_COUNTERS);
	kमुक्त(pool);
पूर्ण

पूर्णांक mlxsw_sp_counter_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
			   क्रमागत mlxsw_sp_counter_sub_pool_id sub_pool_id,
			   अचिन्हित पूर्णांक *p_counter_index)
अणु
	काष्ठा mlxsw_sp_counter_pool *pool = mlxsw_sp->counter_pool;
	काष्ठा mlxsw_sp_counter_sub_pool *sub_pool;
	अचिन्हित पूर्णांक entry_index;
	अचिन्हित पूर्णांक stop_index;
	पूर्णांक i, err;

	sub_pool = &pool->sub_pools[sub_pool_id];
	stop_index = sub_pool->base_index + sub_pool->size;
	entry_index = sub_pool->base_index;

	spin_lock(&pool->counter_pool_lock);
	entry_index = find_next_zero_bit(pool->usage, stop_index, entry_index);
	अगर (entry_index == stop_index) अणु
		err = -ENOBUFS;
		जाओ err_alloc;
	पूर्ण
	/* The sub-pools can contain non-पूर्णांकeger number of entries
	 * so we must check क्रम overflow
	 */
	अगर (entry_index + sub_pool->entry_size > stop_index) अणु
		err = -ENOBUFS;
		जाओ err_alloc;
	पूर्ण
	क्रम (i = 0; i < sub_pool->entry_size; i++)
		__set_bit(entry_index + i, pool->usage);
	spin_unlock(&pool->counter_pool_lock);

	*p_counter_index = entry_index;
	atomic_add(sub_pool->entry_size, &sub_pool->active_entries_count);
	atomic_add(sub_pool->entry_size, &pool->active_entries_count);
	वापस 0;

err_alloc:
	spin_unlock(&pool->counter_pool_lock);
	वापस err;
पूर्ण

व्योम mlxsw_sp_counter_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
			   क्रमागत mlxsw_sp_counter_sub_pool_id sub_pool_id,
			   अचिन्हित पूर्णांक counter_index)
अणु
	काष्ठा mlxsw_sp_counter_pool *pool = mlxsw_sp->counter_pool;
	काष्ठा mlxsw_sp_counter_sub_pool *sub_pool;
	पूर्णांक i;

	अगर (WARN_ON(counter_index >= pool->pool_size))
		वापस;
	sub_pool = &pool->sub_pools[sub_pool_id];
	spin_lock(&pool->counter_pool_lock);
	क्रम (i = 0; i < sub_pool->entry_size; i++)
		__clear_bit(counter_index + i, pool->usage);
	spin_unlock(&pool->counter_pool_lock);
	atomic_sub(sub_pool->entry_size, &sub_pool->active_entries_count);
	atomic_sub(sub_pool->entry_size, &pool->active_entries_count);
पूर्ण

पूर्णांक mlxsw_sp_counter_resources_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	अटल काष्ठा devlink_resource_size_params size_params;
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	स्थिर काष्ठा mlxsw_sp_counter_sub_pool *sub_pool;
	अचिन्हित पूर्णांक total_bank_config;
	u64 sub_pool_size;
	u64 base_index;
	u64 pool_size;
	u64 bank_size;
	पूर्णांक err;
	पूर्णांक i;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_core, COUNTER_POOL_SIZE) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_core, COUNTER_BANK_SIZE))
		वापस -EIO;

	pool_size = MLXSW_CORE_RES_GET(mlxsw_core, COUNTER_POOL_SIZE);
	bank_size = MLXSW_CORE_RES_GET(mlxsw_core, COUNTER_BANK_SIZE);

	devlink_resource_size_params_init(&size_params, pool_size,
					  pool_size, bank_size,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
	err = devlink_resource_रेजिस्टर(devlink,
					MLXSW_SP_RESOURCE_NAME_COUNTERS,
					pool_size,
					MLXSW_SP_RESOURCE_COUNTERS,
					DEVLINK_RESOURCE_ID_PARENT_TOP,
					&size_params);
	अगर (err)
		वापस err;

	/* Allocation is based on bank count which should be
	 * specअगरied क्रम each sub pool अटलally.
	 */
	total_bank_config = 0;
	base_index = 0;
	क्रम (i = 0; i < ARRAY_SIZE(mlxsw_sp_counter_sub_pools); i++) अणु
		sub_pool = &mlxsw_sp_counter_sub_pools[i];
		sub_pool_size = sub_pool->bank_count * bank_size;
		/* The last bank can't be fully used */
		अगर (base_index + sub_pool_size > pool_size)
			sub_pool_size = pool_size - base_index;
		base_index += sub_pool_size;

		devlink_resource_size_params_init(&size_params, sub_pool_size,
						  sub_pool_size, bank_size,
						  DEVLINK_RESOURCE_UNIT_ENTRY);
		err = devlink_resource_रेजिस्टर(devlink,
						sub_pool->resource_name,
						sub_pool_size,
						sub_pool->resource_id,
						MLXSW_SP_RESOURCE_COUNTERS,
						&size_params);
		अगर (err)
			वापस err;
		total_bank_config += sub_pool->bank_count;
	पूर्ण

	/* Check config is valid, no bank over subscription */
	अगर (WARN_ON(total_bank_config > भाग64_u64(pool_size, bank_size) + 1))
		वापस -EINVAL;

	वापस 0;
पूर्ण
