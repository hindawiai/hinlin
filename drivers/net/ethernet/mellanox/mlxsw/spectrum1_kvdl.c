<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>

#समावेश "spectrum.h"

#घोषणा MLXSW_SP1_KVDL_SINGLE_BASE 0
#घोषणा MLXSW_SP1_KVDL_SINGLE_SIZE 16384
#घोषणा MLXSW_SP1_KVDL_SINGLE_END \
	(MLXSW_SP1_KVDL_SINGLE_SIZE + MLXSW_SP1_KVDL_SINGLE_BASE - 1)

#घोषणा MLXSW_SP1_KVDL_CHUNKS_BASE \
	(MLXSW_SP1_KVDL_SINGLE_BASE + MLXSW_SP1_KVDL_SINGLE_SIZE)
#घोषणा MLXSW_SP1_KVDL_CHUNKS_SIZE 49152
#घोषणा MLXSW_SP1_KVDL_CHUNKS_END \
	(MLXSW_SP1_KVDL_CHUNKS_SIZE + MLXSW_SP1_KVDL_CHUNKS_BASE - 1)

#घोषणा MLXSW_SP1_KVDL_LARGE_CHUNKS_BASE \
	(MLXSW_SP1_KVDL_CHUNKS_BASE + MLXSW_SP1_KVDL_CHUNKS_SIZE)
#घोषणा MLXSW_SP1_KVDL_LARGE_CHUNKS_SIZE \
	(MLXSW_SP_KVD_LINEAR_SIZE - MLXSW_SP1_KVDL_LARGE_CHUNKS_BASE)
#घोषणा MLXSW_SP1_KVDL_LARGE_CHUNKS_END \
	(MLXSW_SP1_KVDL_LARGE_CHUNKS_SIZE + MLXSW_SP1_KVDL_LARGE_CHUNKS_BASE - 1)

#घोषणा MLXSW_SP1_KVDL_SINGLE_ALLOC_SIZE 1
#घोषणा MLXSW_SP1_KVDL_CHUNKS_ALLOC_SIZE 32
#घोषणा MLXSW_SP1_KVDL_LARGE_CHUNKS_ALLOC_SIZE 512

काष्ठा mlxsw_sp1_kvdl_part_info अणु
	अचिन्हित पूर्णांक part_index;
	अचिन्हित पूर्णांक start_index;
	अचिन्हित पूर्णांक end_index;
	अचिन्हित पूर्णांक alloc_size;
	क्रमागत mlxsw_sp_resource_id resource_id;
पूर्ण;

क्रमागत mlxsw_sp1_kvdl_part_id अणु
	MLXSW_SP1_KVDL_PART_ID_SINGLE,
	MLXSW_SP1_KVDL_PART_ID_CHUNKS,
	MLXSW_SP1_KVDL_PART_ID_LARGE_CHUNKS,
पूर्ण;

#घोषणा MLXSW_SP1_KVDL_PART_INFO(id)				\
[MLXSW_SP1_KVDL_PART_ID_##id] = अणु				\
	.start_index = MLXSW_SP1_KVDL_##id##_BASE,		\
	.end_index = MLXSW_SP1_KVDL_##id##_END,			\
	.alloc_size = MLXSW_SP1_KVDL_##id##_ALLOC_SIZE,		\
	.resource_id = MLXSW_SP_RESOURCE_KVD_LINEAR_##id,	\
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp1_kvdl_part_info mlxsw_sp1_kvdl_parts_info[] = अणु
	MLXSW_SP1_KVDL_PART_INFO(SINGLE),
	MLXSW_SP1_KVDL_PART_INFO(CHUNKS),
	MLXSW_SP1_KVDL_PART_INFO(LARGE_CHUNKS),
पूर्ण;

#घोषणा MLXSW_SP1_KVDL_PARTS_INFO_LEN ARRAY_SIZE(mlxsw_sp1_kvdl_parts_info)

काष्ठा mlxsw_sp1_kvdl_part अणु
	काष्ठा mlxsw_sp1_kvdl_part_info info;
	अचिन्हित दीर्घ usage[];	/* Entries */
पूर्ण;

काष्ठा mlxsw_sp1_kvdl अणु
	काष्ठा mlxsw_sp1_kvdl_part *parts[MLXSW_SP1_KVDL_PARTS_INFO_LEN];
पूर्ण;

अटल काष्ठा mlxsw_sp1_kvdl_part *
mlxsw_sp1_kvdl_alloc_size_part(काष्ठा mlxsw_sp1_kvdl *kvdl,
			       अचिन्हित पूर्णांक alloc_size)
अणु
	काष्ठा mlxsw_sp1_kvdl_part *part, *min_part = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP1_KVDL_PARTS_INFO_LEN; i++) अणु
		part = kvdl->parts[i];
		अगर (alloc_size <= part->info.alloc_size &&
		    (!min_part ||
		     part->info.alloc_size <= min_part->info.alloc_size))
			min_part = part;
	पूर्ण

	वापस min_part ?: ERR_PTR(-ENOBUFS);
पूर्ण

अटल काष्ठा mlxsw_sp1_kvdl_part *
mlxsw_sp1_kvdl_index_part(काष्ठा mlxsw_sp1_kvdl *kvdl, u32 kvdl_index)
अणु
	काष्ठा mlxsw_sp1_kvdl_part *part;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP1_KVDL_PARTS_INFO_LEN; i++) अणु
		part = kvdl->parts[i];
		अगर (kvdl_index >= part->info.start_index &&
		    kvdl_index <= part->info.end_index)
			वापस part;
	पूर्ण

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल u32
mlxsw_sp1_kvdl_to_kvdl_index(स्थिर काष्ठा mlxsw_sp1_kvdl_part_info *info,
			     अचिन्हित पूर्णांक entry_index)
अणु
	वापस info->start_index + entry_index * info->alloc_size;
पूर्ण

अटल अचिन्हित पूर्णांक
mlxsw_sp1_kvdl_to_entry_index(स्थिर काष्ठा mlxsw_sp1_kvdl_part_info *info,
			      u32 kvdl_index)
अणु
	वापस (kvdl_index - info->start_index) / info->alloc_size;
पूर्ण

अटल पूर्णांक mlxsw_sp1_kvdl_part_alloc(काष्ठा mlxsw_sp1_kvdl_part *part,
				     u32 *p_kvdl_index)
अणु
	स्थिर काष्ठा mlxsw_sp1_kvdl_part_info *info = &part->info;
	अचिन्हित पूर्णांक entry_index, nr_entries;

	nr_entries = (info->end_index - info->start_index + 1) /
		     info->alloc_size;
	entry_index = find_first_zero_bit(part->usage, nr_entries);
	अगर (entry_index == nr_entries)
		वापस -ENOBUFS;
	__set_bit(entry_index, part->usage);

	*p_kvdl_index = mlxsw_sp1_kvdl_to_kvdl_index(info, entry_index);

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp1_kvdl_part_मुक्त(काष्ठा mlxsw_sp1_kvdl_part *part,
				     u32 kvdl_index)
अणु
	स्थिर काष्ठा mlxsw_sp1_kvdl_part_info *info = &part->info;
	अचिन्हित पूर्णांक entry_index;

	entry_index = mlxsw_sp1_kvdl_to_entry_index(info, kvdl_index);
	__clear_bit(entry_index, part->usage);
पूर्ण

अटल पूर्णांक mlxsw_sp1_kvdl_alloc(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
				क्रमागत mlxsw_sp_kvdl_entry_type type,
				अचिन्हित पूर्णांक entry_count,
				u32 *p_entry_index)
अणु
	काष्ठा mlxsw_sp1_kvdl *kvdl = priv;
	काष्ठा mlxsw_sp1_kvdl_part *part;

	/* Find partition with smallest allocation size satisfying the
	 * requested size.
	 */
	part = mlxsw_sp1_kvdl_alloc_size_part(kvdl, entry_count);
	अगर (IS_ERR(part))
		वापस PTR_ERR(part);

	वापस mlxsw_sp1_kvdl_part_alloc(part, p_entry_index);
पूर्ण

अटल व्योम mlxsw_sp1_kvdl_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
				क्रमागत mlxsw_sp_kvdl_entry_type type,
				अचिन्हित पूर्णांक entry_count, पूर्णांक entry_index)
अणु
	काष्ठा mlxsw_sp1_kvdl *kvdl = priv;
	काष्ठा mlxsw_sp1_kvdl_part *part;

	part = mlxsw_sp1_kvdl_index_part(kvdl, entry_index);
	अगर (IS_ERR(part))
		वापस;
	mlxsw_sp1_kvdl_part_मुक्त(part, entry_index);
पूर्ण

अटल पूर्णांक mlxsw_sp1_kvdl_alloc_size_query(काष्ठा mlxsw_sp *mlxsw_sp,
					   व्योम *priv,
					   क्रमागत mlxsw_sp_kvdl_entry_type type,
					   अचिन्हित पूर्णांक entry_count,
					   अचिन्हित पूर्णांक *p_alloc_size)
अणु
	काष्ठा mlxsw_sp1_kvdl *kvdl = priv;
	काष्ठा mlxsw_sp1_kvdl_part *part;

	part = mlxsw_sp1_kvdl_alloc_size_part(kvdl, entry_count);
	अगर (IS_ERR(part))
		वापस PTR_ERR(part);

	*p_alloc_size = part->info.alloc_size;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp1_kvdl_part_update(काष्ठा mlxsw_sp1_kvdl_part *part,
				       काष्ठा mlxsw_sp1_kvdl_part *part_prev,
				       अचिन्हित पूर्णांक size)
अणु
	अगर (!part_prev) अणु
		part->info.end_index = size - 1;
	पूर्ण अन्यथा अणु
		part->info.start_index = part_prev->info.end_index + 1;
		part->info.end_index = part->info.start_index + size - 1;
	पूर्ण
पूर्ण

अटल काष्ठा mlxsw_sp1_kvdl_part *
mlxsw_sp1_kvdl_part_init(काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा mlxsw_sp1_kvdl_part_info *info,
			 काष्ठा mlxsw_sp1_kvdl_part *part_prev)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	काष्ठा mlxsw_sp1_kvdl_part *part;
	bool need_update = true;
	अचिन्हित पूर्णांक nr_entries;
	माप_प्रकार usage_size;
	u64 resource_size;
	पूर्णांक err;

	err = devlink_resource_size_get(devlink, info->resource_id,
					&resource_size);
	अगर (err) अणु
		need_update = false;
		resource_size = info->end_index - info->start_index + 1;
	पूर्ण

	nr_entries = भाग_u64(resource_size, info->alloc_size);
	usage_size = BITS_TO_LONGS(nr_entries) * माप(अचिन्हित दीर्घ);
	part = kzalloc(माप(*part) + usage_size, GFP_KERNEL);
	अगर (!part)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(&part->info, info, माप(part->info));

	अगर (need_update)
		mlxsw_sp1_kvdl_part_update(part, part_prev, resource_size);
	वापस part;
पूर्ण

अटल व्योम mlxsw_sp1_kvdl_part_fini(काष्ठा mlxsw_sp1_kvdl_part *part)
अणु
	kमुक्त(part);
पूर्ण

अटल पूर्णांक mlxsw_sp1_kvdl_parts_init(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp1_kvdl *kvdl)
अणु
	स्थिर काष्ठा mlxsw_sp1_kvdl_part_info *info;
	काष्ठा mlxsw_sp1_kvdl_part *part_prev = शून्य;
	पूर्णांक err, i;

	क्रम (i = 0; i < MLXSW_SP1_KVDL_PARTS_INFO_LEN; i++) अणु
		info = &mlxsw_sp1_kvdl_parts_info[i];
		kvdl->parts[i] = mlxsw_sp1_kvdl_part_init(mlxsw_sp, info,
							  part_prev);
		अगर (IS_ERR(kvdl->parts[i])) अणु
			err = PTR_ERR(kvdl->parts[i]);
			जाओ err_kvdl_part_init;
		पूर्ण
		part_prev = kvdl->parts[i];
	पूर्ण
	वापस 0;

err_kvdl_part_init:
	क्रम (i--; i >= 0; i--)
		mlxsw_sp1_kvdl_part_fini(kvdl->parts[i]);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp1_kvdl_parts_fini(काष्ठा mlxsw_sp1_kvdl *kvdl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP1_KVDL_PARTS_INFO_LEN; i++)
		mlxsw_sp1_kvdl_part_fini(kvdl->parts[i]);
पूर्ण

अटल u64 mlxsw_sp1_kvdl_part_occ(काष्ठा mlxsw_sp1_kvdl_part *part)
अणु
	स्थिर काष्ठा mlxsw_sp1_kvdl_part_info *info = &part->info;
	अचिन्हित पूर्णांक nr_entries;
	पूर्णांक bit = -1;
	u64 occ = 0;

	nr_entries = (info->end_index -
		      info->start_index + 1) /
		      info->alloc_size;
	जबतक ((bit = find_next_bit(part->usage, nr_entries, bit + 1))
		< nr_entries)
		occ += info->alloc_size;
	वापस occ;
पूर्ण

अटल u64 mlxsw_sp1_kvdl_occ_get(व्योम *priv)
अणु
	स्थिर काष्ठा mlxsw_sp1_kvdl *kvdl = priv;
	u64 occ = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP1_KVDL_PARTS_INFO_LEN; i++)
		occ += mlxsw_sp1_kvdl_part_occ(kvdl->parts[i]);

	वापस occ;
पूर्ण

अटल u64 mlxsw_sp1_kvdl_single_occ_get(व्योम *priv)
अणु
	स्थिर काष्ठा mlxsw_sp1_kvdl *kvdl = priv;
	काष्ठा mlxsw_sp1_kvdl_part *part;

	part = kvdl->parts[MLXSW_SP1_KVDL_PART_ID_SINGLE];
	वापस mlxsw_sp1_kvdl_part_occ(part);
पूर्ण

अटल u64 mlxsw_sp1_kvdl_chunks_occ_get(व्योम *priv)
अणु
	स्थिर काष्ठा mlxsw_sp1_kvdl *kvdl = priv;
	काष्ठा mlxsw_sp1_kvdl_part *part;

	part = kvdl->parts[MLXSW_SP1_KVDL_PART_ID_CHUNKS];
	वापस mlxsw_sp1_kvdl_part_occ(part);
पूर्ण

अटल u64 mlxsw_sp1_kvdl_large_chunks_occ_get(व्योम *priv)
अणु
	स्थिर काष्ठा mlxsw_sp1_kvdl *kvdl = priv;
	काष्ठा mlxsw_sp1_kvdl_part *part;

	part = kvdl->parts[MLXSW_SP1_KVDL_PART_ID_LARGE_CHUNKS];
	वापस mlxsw_sp1_kvdl_part_occ(part);
पूर्ण

अटल पूर्णांक mlxsw_sp1_kvdl_init(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	काष्ठा mlxsw_sp1_kvdl *kvdl = priv;
	पूर्णांक err;

	err = mlxsw_sp1_kvdl_parts_init(mlxsw_sp, kvdl);
	अगर (err)
		वापस err;
	devlink_resource_occ_get_रेजिस्टर(devlink,
					  MLXSW_SP_RESOURCE_KVD_LINEAR,
					  mlxsw_sp1_kvdl_occ_get,
					  kvdl);
	devlink_resource_occ_get_रेजिस्टर(devlink,
					  MLXSW_SP_RESOURCE_KVD_LINEAR_SINGLE,
					  mlxsw_sp1_kvdl_single_occ_get,
					  kvdl);
	devlink_resource_occ_get_रेजिस्टर(devlink,
					  MLXSW_SP_RESOURCE_KVD_LINEAR_CHUNKS,
					  mlxsw_sp1_kvdl_chunks_occ_get,
					  kvdl);
	devlink_resource_occ_get_रेजिस्टर(devlink,
					  MLXSW_SP_RESOURCE_KVD_LINEAR_LARGE_CHUNKS,
					  mlxsw_sp1_kvdl_large_chunks_occ_get,
					  kvdl);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp1_kvdl_fini(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_sp->core);
	काष्ठा mlxsw_sp1_kvdl *kvdl = priv;

	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    MLXSW_SP_RESOURCE_KVD_LINEAR_LARGE_CHUNKS);
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    MLXSW_SP_RESOURCE_KVD_LINEAR_CHUNKS);
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    MLXSW_SP_RESOURCE_KVD_LINEAR_SINGLE);
	devlink_resource_occ_get_unरेजिस्टर(devlink,
					    MLXSW_SP_RESOURCE_KVD_LINEAR);
	mlxsw_sp1_kvdl_parts_fini(kvdl);
पूर्ण

स्थिर काष्ठा mlxsw_sp_kvdl_ops mlxsw_sp1_kvdl_ops = अणु
	.priv_size = माप(काष्ठा mlxsw_sp1_kvdl),
	.init = mlxsw_sp1_kvdl_init,
	.fini = mlxsw_sp1_kvdl_fini,
	.alloc = mlxsw_sp1_kvdl_alloc,
	.मुक्त = mlxsw_sp1_kvdl_मुक्त,
	.alloc_size_query = mlxsw_sp1_kvdl_alloc_size_query,
पूर्ण;

पूर्णांक mlxsw_sp1_kvdl_resources_रेजिस्टर(काष्ठा mlxsw_core *mlxsw_core)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(mlxsw_core);
	अटल काष्ठा devlink_resource_size_params size_params;
	u32 kvdl_max_size;
	पूर्णांक err;

	kvdl_max_size = MLXSW_CORE_RES_GET(mlxsw_core, KVD_SIZE) -
			MLXSW_CORE_RES_GET(mlxsw_core, KVD_SINGLE_MIN_SIZE) -
			MLXSW_CORE_RES_GET(mlxsw_core, KVD_DOUBLE_MIN_SIZE);

	devlink_resource_size_params_init(&size_params, 0, kvdl_max_size,
					  MLXSW_SP1_KVDL_SINGLE_ALLOC_SIZE,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
	err = devlink_resource_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_NAME_KVD_LINEAR_SINGLES,
					MLXSW_SP1_KVDL_SINGLE_SIZE,
					MLXSW_SP_RESOURCE_KVD_LINEAR_SINGLE,
					MLXSW_SP_RESOURCE_KVD_LINEAR,
					&size_params);
	अगर (err)
		वापस err;

	devlink_resource_size_params_init(&size_params, 0, kvdl_max_size,
					  MLXSW_SP1_KVDL_CHUNKS_ALLOC_SIZE,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
	err = devlink_resource_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_NAME_KVD_LINEAR_CHUNKS,
					MLXSW_SP1_KVDL_CHUNKS_SIZE,
					MLXSW_SP_RESOURCE_KVD_LINEAR_CHUNKS,
					MLXSW_SP_RESOURCE_KVD_LINEAR,
					&size_params);
	अगर (err)
		वापस err;

	devlink_resource_size_params_init(&size_params, 0, kvdl_max_size,
					  MLXSW_SP1_KVDL_LARGE_CHUNKS_ALLOC_SIZE,
					  DEVLINK_RESOURCE_UNIT_ENTRY);
	err = devlink_resource_रेजिस्टर(devlink, MLXSW_SP_RESOURCE_NAME_KVD_LINEAR_LARGE_CHUNKS,
					MLXSW_SP1_KVDL_LARGE_CHUNKS_SIZE,
					MLXSW_SP_RESOURCE_KVD_LINEAR_LARGE_CHUNKS,
					MLXSW_SP_RESOURCE_KVD_LINEAR,
					&size_params);
	वापस err;
पूर्ण
