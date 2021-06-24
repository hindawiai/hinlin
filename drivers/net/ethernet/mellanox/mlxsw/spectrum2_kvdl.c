<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>

#समावेश "spectrum.h"
#समावेश "core.h"
#समावेश "reg.h"
#समावेश "resources.h"

काष्ठा mlxsw_sp2_kvdl_part_info अणु
	u8 res_type;
	/* For each defined partititon we need to know how many
	 * usage bits we need and how many indexes there are
	 * represented by a single bit. This could be got from FW
	 * querying appropriate resources. So have the resource
	 * ids क्रम क्रम this purpose in partition definition.
	 */
	क्रमागत mlxsw_res_id usage_bit_count_res_id;
	क्रमागत mlxsw_res_id index_range_res_id;
पूर्ण;

#घोषणा MLXSW_SP2_KVDL_PART_INFO(_entry_type, _res_type,			\
				 _usage_bit_count_res_id, _index_range_res_id)	\
[MLXSW_SP_KVDL_ENTRY_TYPE_##_entry_type] = अणु					\
	.res_type = _res_type,							\
	.usage_bit_count_res_id = MLXSW_RES_ID_##_usage_bit_count_res_id,	\
	.index_range_res_id = MLXSW_RES_ID_##_index_range_res_id,		\
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp2_kvdl_part_info mlxsw_sp2_kvdl_parts_info[] = अणु
	MLXSW_SP2_KVDL_PART_INFO(ADJ, 0x21, KVD_SIZE, MAX_KVD_LINEAR_RANGE),
	MLXSW_SP2_KVDL_PART_INFO(ACTSET, 0x23, MAX_KVD_ACTION_SETS,
				 MAX_KVD_ACTION_SETS),
	MLXSW_SP2_KVDL_PART_INFO(PBS, 0x24, KVD_SIZE, KVD_SIZE),
	MLXSW_SP2_KVDL_PART_INFO(MCRIGR, 0x26, KVD_SIZE, KVD_SIZE),
	MLXSW_SP2_KVDL_PART_INFO(TNUMT, 0x29, KVD_SIZE, KVD_SIZE),
पूर्ण;

#घोषणा MLXSW_SP2_KVDL_PARTS_INFO_LEN ARRAY_SIZE(mlxsw_sp2_kvdl_parts_info)

काष्ठा mlxsw_sp2_kvdl_part अणु
	स्थिर काष्ठा mlxsw_sp2_kvdl_part_info *info;
	अचिन्हित पूर्णांक usage_bit_count;
	अचिन्हित पूर्णांक indexes_per_usage_bit;
	अचिन्हित पूर्णांक last_allocated_bit;
	अचिन्हित दीर्घ usage[];	/* Usage bits */
पूर्ण;

काष्ठा mlxsw_sp2_kvdl अणु
	काष्ठा mlxsw_sp2_kvdl_part *parts[MLXSW_SP2_KVDL_PARTS_INFO_LEN];
पूर्ण;

अटल पूर्णांक mlxsw_sp2_kvdl_part_find_zero_bits(काष्ठा mlxsw_sp2_kvdl_part *part,
					      अचिन्हित पूर्णांक bit_count,
					      अचिन्हित पूर्णांक *p_bit)
अणु
	अचिन्हित पूर्णांक start_bit;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक i;
	bool wrap = false;

	start_bit = part->last_allocated_bit + 1;
	अगर (start_bit == part->usage_bit_count)
		start_bit = 0;
	bit = start_bit;
again:
	bit = find_next_zero_bit(part->usage, part->usage_bit_count, bit);
	अगर (!wrap && bit + bit_count >= part->usage_bit_count) अणु
		wrap = true;
		bit = 0;
		जाओ again;
	पूर्ण
	अगर (wrap && bit + bit_count >= start_bit)
		वापस -ENOBUFS;
	क्रम (i = 0; i < bit_count; i++) अणु
		अगर (test_bit(bit + i, part->usage)) अणु
			bit += bit_count;
			जाओ again;
		पूर्ण
	पूर्ण
	*p_bit = bit;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp2_kvdl_part_alloc(काष्ठा mlxsw_sp2_kvdl_part *part,
				     अचिन्हित पूर्णांक size,
				     u32 *p_kvdl_index)
अणु
	अचिन्हित पूर्णांक bit_count;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	bit_count = DIV_ROUND_UP(size, part->indexes_per_usage_bit);
	err = mlxsw_sp2_kvdl_part_find_zero_bits(part, bit_count, &bit);
	अगर (err)
		वापस err;
	क्रम (i = 0; i < bit_count; i++)
		__set_bit(bit + i, part->usage);
	*p_kvdl_index = bit * part->indexes_per_usage_bit;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp2_kvdl_rec_del(काष्ठा mlxsw_sp *mlxsw_sp, u8 res_type,
				  u16 size, u32 kvdl_index)
अणु
	अक्षर *iedr_pl;
	पूर्णांक err;

	iedr_pl = kदो_स्मृति(MLXSW_REG_IEDR_LEN, GFP_KERNEL);
	अगर (!iedr_pl)
		वापस -ENOMEM;

	mlxsw_reg_iedr_pack(iedr_pl);
	mlxsw_reg_iedr_rec_pack(iedr_pl, 0, res_type, size, kvdl_index);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(iedr), iedr_pl);
	kमुक्त(iedr_pl);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_kvdl_part_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp2_kvdl_part *part,
				     अचिन्हित पूर्णांक size, u32 kvdl_index)
अणु
	अचिन्हित पूर्णांक bit_count;
	अचिन्हित पूर्णांक bit;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/* We need to ask FW to delete previously used KVD linear index */
	err = mlxsw_sp2_kvdl_rec_del(mlxsw_sp, part->info->res_type,
				     size, kvdl_index);
	अगर (err)
		वापस;

	bit_count = DIV_ROUND_UP(size, part->indexes_per_usage_bit);
	bit = kvdl_index / part->indexes_per_usage_bit;
	क्रम (i = 0; i < bit_count; i++)
		__clear_bit(bit + i, part->usage);
पूर्ण

अटल पूर्णांक mlxsw_sp2_kvdl_alloc(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
				क्रमागत mlxsw_sp_kvdl_entry_type type,
				अचिन्हित पूर्णांक entry_count,
				u32 *p_entry_index)
अणु
	अचिन्हित पूर्णांक size = entry_count * mlxsw_sp_kvdl_entry_size(type);
	काष्ठा mlxsw_sp2_kvdl *kvdl = priv;
	काष्ठा mlxsw_sp2_kvdl_part *part = kvdl->parts[type];

	वापस mlxsw_sp2_kvdl_part_alloc(part, size, p_entry_index);
पूर्ण

अटल व्योम mlxsw_sp2_kvdl_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
				क्रमागत mlxsw_sp_kvdl_entry_type type,
				अचिन्हित पूर्णांक entry_count,
				पूर्णांक entry_index)
अणु
	अचिन्हित पूर्णांक size = entry_count * mlxsw_sp_kvdl_entry_size(type);
	काष्ठा mlxsw_sp2_kvdl *kvdl = priv;
	काष्ठा mlxsw_sp2_kvdl_part *part = kvdl->parts[type];

	वापस mlxsw_sp2_kvdl_part_मुक्त(mlxsw_sp, part, size, entry_index);
पूर्ण

अटल पूर्णांक mlxsw_sp2_kvdl_alloc_size_query(काष्ठा mlxsw_sp *mlxsw_sp,
					   व्योम *priv,
					   क्रमागत mlxsw_sp_kvdl_entry_type type,
					   अचिन्हित पूर्णांक entry_count,
					   अचिन्हित पूर्णांक *p_alloc_count)
अणु
	*p_alloc_count = entry_count;
	वापस 0;
पूर्ण

अटल काष्ठा mlxsw_sp2_kvdl_part *
mlxsw_sp2_kvdl_part_init(काष्ठा mlxsw_sp *mlxsw_sp,
			 स्थिर काष्ठा mlxsw_sp2_kvdl_part_info *info)
अणु
	अचिन्हित पूर्णांक indexes_per_usage_bit;
	काष्ठा mlxsw_sp2_kvdl_part *part;
	अचिन्हित पूर्णांक index_range;
	अचिन्हित पूर्णांक usage_bit_count;
	माप_प्रकार usage_size;

	अगर (!mlxsw_core_res_valid(mlxsw_sp->core,
				  info->usage_bit_count_res_id) ||
	    !mlxsw_core_res_valid(mlxsw_sp->core,
				  info->index_range_res_id))
		वापस ERR_PTR(-EIO);
	usage_bit_count = mlxsw_core_res_get(mlxsw_sp->core,
					     info->usage_bit_count_res_id);
	index_range = mlxsw_core_res_get(mlxsw_sp->core,
					 info->index_range_res_id);

	/* For some partitions, one usage bit represents a group of indexes.
	 * That's why we compute the number of indexes per usage bit here,
	 * according to queried resources.
	 */
	indexes_per_usage_bit = index_range / usage_bit_count;

	usage_size = BITS_TO_LONGS(usage_bit_count) * माप(अचिन्हित दीर्घ);
	part = kzalloc(माप(*part) + usage_size, GFP_KERNEL);
	अगर (!part)
		वापस ERR_PTR(-ENOMEM);
	part->info = info;
	part->usage_bit_count = usage_bit_count;
	part->indexes_per_usage_bit = indexes_per_usage_bit;
	part->last_allocated_bit = usage_bit_count - 1;
	वापस part;
पूर्ण

अटल व्योम mlxsw_sp2_kvdl_part_fini(काष्ठा mlxsw_sp2_kvdl_part *part)
अणु
	kमुक्त(part);
पूर्ण

अटल पूर्णांक mlxsw_sp2_kvdl_parts_init(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp2_kvdl *kvdl)
अणु
	स्थिर काष्ठा mlxsw_sp2_kvdl_part_info *info;
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < MLXSW_SP2_KVDL_PARTS_INFO_LEN; i++) अणु
		info = &mlxsw_sp2_kvdl_parts_info[i];
		kvdl->parts[i] = mlxsw_sp2_kvdl_part_init(mlxsw_sp, info);
		अगर (IS_ERR(kvdl->parts[i])) अणु
			err = PTR_ERR(kvdl->parts[i]);
			जाओ err_kvdl_part_init;
		पूर्ण
	पूर्ण
	वापस 0;

err_kvdl_part_init:
	क्रम (i--; i >= 0; i--)
		mlxsw_sp2_kvdl_part_fini(kvdl->parts[i]);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_kvdl_parts_fini(काष्ठा mlxsw_sp2_kvdl *kvdl)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_SP2_KVDL_PARTS_INFO_LEN; i++)
		mlxsw_sp2_kvdl_part_fini(kvdl->parts[i]);
पूर्ण

अटल पूर्णांक mlxsw_sp2_kvdl_init(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
	काष्ठा mlxsw_sp2_kvdl *kvdl = priv;

	वापस mlxsw_sp2_kvdl_parts_init(mlxsw_sp, kvdl);
पूर्ण

अटल व्योम mlxsw_sp2_kvdl_fini(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
	काष्ठा mlxsw_sp2_kvdl *kvdl = priv;

	mlxsw_sp2_kvdl_parts_fini(kvdl);
पूर्ण

स्थिर काष्ठा mlxsw_sp_kvdl_ops mlxsw_sp2_kvdl_ops = अणु
	.priv_size = माप(काष्ठा mlxsw_sp2_kvdl),
	.init = mlxsw_sp2_kvdl_init,
	.fini = mlxsw_sp2_kvdl_fini,
	.alloc = mlxsw_sp2_kvdl_alloc,
	.मुक्त = mlxsw_sp2_kvdl_मुक्त,
	.alloc_size_query = mlxsw_sp2_kvdl_alloc_size_query,
पूर्ण;
