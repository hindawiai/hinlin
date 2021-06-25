<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/genभाग.स>
#समावेश <linux/gfp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/objagg.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>

#समावेश "core.h"
#समावेश "reg.h"
#समावेश "spectrum.h"
#समावेश "spectrum_acl_tcam.h"

/* gen_pool_alloc() वापसs 0 when allocation fails, so use an offset */
#घोषणा MLXSW_SP_ACL_ERP_GENALLOC_OFFSET 0x100
#घोषणा MLXSW_SP_ACL_ERP_MAX_PER_REGION 16

काष्ठा mlxsw_sp_acl_erp_core अणु
	अचिन्हित पूर्णांक erpt_entries_size[MLXSW_SP_ACL_ATCAM_REGION_TYPE_MAX + 1];
	काष्ठा gen_pool *erp_tables;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा mlxsw_sp_acl_bf *bf;
	अचिन्हित पूर्णांक num_erp_banks;
पूर्ण;

काष्ठा mlxsw_sp_acl_erp_key अणु
	अक्षर mask[MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN];
#घोषणा __MASK_LEN 0x38
#घोषणा __MASK_IDX(i) (__MASK_LEN - (i) - 1)
	bool ctcam;
पूर्ण;

काष्ठा mlxsw_sp_acl_erp अणु
	काष्ठा mlxsw_sp_acl_erp_key key;
	u8 id;
	u8 index;
	DECLARE_BITMAP(mask_biपंचांगap, MLXSW_SP_ACL_TCAM_MASK_LEN);
	काष्ठा list_head list;
	काष्ठा mlxsw_sp_acl_erp_table *erp_table;
पूर्ण;

काष्ठा mlxsw_sp_acl_erp_master_mask अणु
	DECLARE_BITMAP(biपंचांगap, MLXSW_SP_ACL_TCAM_MASK_LEN);
	अचिन्हित पूर्णांक count[MLXSW_SP_ACL_TCAM_MASK_LEN];
पूर्ण;

काष्ठा mlxsw_sp_acl_erp_table अणु
	काष्ठा mlxsw_sp_acl_erp_master_mask master_mask;
	DECLARE_BITMAP(erp_id_biपंचांगap, MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	DECLARE_BITMAP(erp_index_biपंचांगap, MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	काष्ठा list_head atcam_erps_list;
	काष्ठा mlxsw_sp_acl_erp_core *erp_core;
	काष्ठा mlxsw_sp_acl_atcam_region *aregion;
	स्थिर काष्ठा mlxsw_sp_acl_erp_table_ops *ops;
	अचिन्हित दीर्घ base_index;
	अचिन्हित पूर्णांक num_atcam_erps;
	अचिन्हित पूर्णांक num_max_atcam_erps;
	अचिन्हित पूर्णांक num_ctcam_erps;
	अचिन्हित पूर्णांक num_deltas;
	काष्ठा objagg *objagg;
	काष्ठा mutex objagg_lock; /* guards objagg manipulation */
पूर्ण;

काष्ठा mlxsw_sp_acl_erp_table_ops अणु
	काष्ठा mlxsw_sp_acl_erp *
		(*erp_create)(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			      काष्ठा mlxsw_sp_acl_erp_key *key);
	व्योम (*erp_destroy)(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			    काष्ठा mlxsw_sp_acl_erp *erp);
पूर्ण;

अटल काष्ठा mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_mask_create(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			     काष्ठा mlxsw_sp_acl_erp_key *key);
अटल व्योम
mlxsw_sp_acl_erp_mask_destroy(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			      काष्ठा mlxsw_sp_acl_erp *erp);
अटल काष्ठा mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_second_mask_create(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				    काष्ठा mlxsw_sp_acl_erp_key *key);
अटल व्योम
mlxsw_sp_acl_erp_second_mask_destroy(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				     काष्ठा mlxsw_sp_acl_erp *erp);
अटल काष्ठा mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_first_mask_create(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				   काष्ठा mlxsw_sp_acl_erp_key *key);
अटल व्योम
mlxsw_sp_acl_erp_first_mask_destroy(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				    काष्ठा mlxsw_sp_acl_erp *erp);
अटल व्योम
mlxsw_sp_acl_erp_no_mask_destroy(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				 काष्ठा mlxsw_sp_acl_erp *erp);

अटल स्थिर काष्ठा mlxsw_sp_acl_erp_table_ops erp_multiple_masks_ops = अणु
	.erp_create = mlxsw_sp_acl_erp_mask_create,
	.erp_destroy = mlxsw_sp_acl_erp_mask_destroy,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_acl_erp_table_ops erp_two_masks_ops = अणु
	.erp_create = mlxsw_sp_acl_erp_mask_create,
	.erp_destroy = mlxsw_sp_acl_erp_second_mask_destroy,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_acl_erp_table_ops erp_single_mask_ops = अणु
	.erp_create = mlxsw_sp_acl_erp_second_mask_create,
	.erp_destroy = mlxsw_sp_acl_erp_first_mask_destroy,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_acl_erp_table_ops erp_no_mask_ops = अणु
	.erp_create = mlxsw_sp_acl_erp_first_mask_create,
	.erp_destroy = mlxsw_sp_acl_erp_no_mask_destroy,
पूर्ण;

अटल bool
mlxsw_sp_acl_erp_table_is_used(स्थिर काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	वापस erp_table->ops != &erp_single_mask_ops &&
	       erp_table->ops != &erp_no_mask_ops;
पूर्ण

अटल अचिन्हित पूर्णांक
mlxsw_sp_acl_erp_bank_get(स्थिर काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	वापस erp->index % erp->erp_table->erp_core->num_erp_banks;
पूर्ण

अटल अचिन्हित पूर्णांक
mlxsw_sp_acl_erp_table_entry_size(स्थिर काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region *aregion = erp_table->aregion;
	काष्ठा mlxsw_sp_acl_erp_core *erp_core = erp_table->erp_core;

	वापस erp_core->erpt_entries_size[aregion->type];
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_erp_id_get(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				   u8 *p_id)
अणु
	u8 id;

	id = find_first_zero_bit(erp_table->erp_id_biपंचांगap,
				 MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	अगर (id < MLXSW_SP_ACL_ERP_MAX_PER_REGION) अणु
		__set_bit(id, erp_table->erp_id_biपंचांगap);
		*p_id = id;
		वापस 0;
	पूर्ण

	वापस -ENOBUFS;
पूर्ण

अटल व्योम mlxsw_sp_acl_erp_id_put(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				    u8 id)
अणु
	__clear_bit(id, erp_table->erp_id_biपंचांगap);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_master_mask_bit_set(अचिन्हित दीर्घ bit,
				     काष्ठा mlxsw_sp_acl_erp_master_mask *mask)
अणु
	अगर (mask->count[bit]++ == 0)
		__set_bit(bit, mask->biपंचांगap);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_master_mask_bit_clear(अचिन्हित दीर्घ bit,
				       काष्ठा mlxsw_sp_acl_erp_master_mask *mask)
अणु
	अगर (--mask->count[bit] == 0)
		__clear_bit(bit, mask->biपंचांगap);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_master_mask_update(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region = erp_table->aregion->region;
	काष्ठा mlxsw_sp *mlxsw_sp = region->mlxsw_sp;
	अक्षर percr_pl[MLXSW_REG_PERCR_LEN];
	अक्षर *master_mask;

	mlxsw_reg_percr_pack(percr_pl, region->id);
	master_mask = mlxsw_reg_percr_master_mask_data(percr_pl);
	biपंचांगap_to_arr32((u32 *) master_mask, erp_table->master_mask.biपंचांगap,
			MLXSW_SP_ACL_TCAM_MASK_LEN);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(percr), percr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_master_mask_set(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				 काष्ठा mlxsw_sp_acl_erp_key *key)
अणु
	DECLARE_BITMAP(mask_biपंचांगap, MLXSW_SP_ACL_TCAM_MASK_LEN);
	अचिन्हित दीर्घ bit;
	पूर्णांक err;

	biपंचांगap_from_arr32(mask_biपंचांगap, (u32 *) key->mask,
			  MLXSW_SP_ACL_TCAM_MASK_LEN);
	क्रम_each_set_bit(bit, mask_biपंचांगap, MLXSW_SP_ACL_TCAM_MASK_LEN)
		mlxsw_sp_acl_erp_master_mask_bit_set(bit,
						     &erp_table->master_mask);

	err = mlxsw_sp_acl_erp_master_mask_update(erp_table);
	अगर (err)
		जाओ err_master_mask_update;

	वापस 0;

err_master_mask_update:
	क्रम_each_set_bit(bit, mask_biपंचांगap, MLXSW_SP_ACL_TCAM_MASK_LEN)
		mlxsw_sp_acl_erp_master_mask_bit_clear(bit,
						       &erp_table->master_mask);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_master_mask_clear(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				   काष्ठा mlxsw_sp_acl_erp_key *key)
अणु
	DECLARE_BITMAP(mask_biपंचांगap, MLXSW_SP_ACL_TCAM_MASK_LEN);
	अचिन्हित दीर्घ bit;
	पूर्णांक err;

	biपंचांगap_from_arr32(mask_biपंचांगap, (u32 *) key->mask,
			  MLXSW_SP_ACL_TCAM_MASK_LEN);
	क्रम_each_set_bit(bit, mask_biपंचांगap, MLXSW_SP_ACL_TCAM_MASK_LEN)
		mlxsw_sp_acl_erp_master_mask_bit_clear(bit,
						       &erp_table->master_mask);

	err = mlxsw_sp_acl_erp_master_mask_update(erp_table);
	अगर (err)
		जाओ err_master_mask_update;

	वापस 0;

err_master_mask_update:
	क्रम_each_set_bit(bit, mask_biपंचांगap, MLXSW_SP_ACL_TCAM_MASK_LEN)
		mlxsw_sp_acl_erp_master_mask_bit_set(bit,
						     &erp_table->master_mask);
	वापस err;
पूर्ण

अटल काष्ठा mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_generic_create(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				काष्ठा mlxsw_sp_acl_erp_key *key)
अणु
	काष्ठा mlxsw_sp_acl_erp *erp;
	पूर्णांक err;

	erp = kzalloc(माप(*erp), GFP_KERNEL);
	अगर (!erp)
		वापस ERR_PTR(-ENOMEM);

	err = mlxsw_sp_acl_erp_id_get(erp_table, &erp->id);
	अगर (err)
		जाओ err_erp_id_get;

	स_नकल(&erp->key, key, माप(*key));
	list_add(&erp->list, &erp_table->atcam_erps_list);
	erp_table->num_atcam_erps++;
	erp->erp_table = erp_table;

	err = mlxsw_sp_acl_erp_master_mask_set(erp_table, &erp->key);
	अगर (err)
		जाओ err_master_mask_set;

	वापस erp;

err_master_mask_set:
	erp_table->num_atcam_erps--;
	list_del(&erp->list);
	mlxsw_sp_acl_erp_id_put(erp_table, erp->id);
err_erp_id_get:
	kमुक्त(erp);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_generic_destroy(काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = erp->erp_table;

	mlxsw_sp_acl_erp_master_mask_clear(erp_table, &erp->key);
	erp_table->num_atcam_erps--;
	list_del(&erp->list);
	mlxsw_sp_acl_erp_id_put(erp_table, erp->id);
	kमुक्त(erp);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_table_alloc(काष्ठा mlxsw_sp_acl_erp_core *erp_core,
			     अचिन्हित पूर्णांक num_erps,
			     क्रमागत mlxsw_sp_acl_atcam_region_type region_type,
			     अचिन्हित दीर्घ *p_index)
अणु
	अचिन्हित पूर्णांक num_rows, entry_size;

	/* We only allow allocations of entire rows */
	अगर (num_erps % erp_core->num_erp_banks != 0)
		वापस -EINVAL;

	entry_size = erp_core->erpt_entries_size[region_type];
	num_rows = num_erps / erp_core->num_erp_banks;

	*p_index = gen_pool_alloc(erp_core->erp_tables, num_rows * entry_size);
	अगर (*p_index == 0)
		वापस -ENOBUFS;
	*p_index -= MLXSW_SP_ACL_ERP_GENALLOC_OFFSET;

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_table_मुक्त(काष्ठा mlxsw_sp_acl_erp_core *erp_core,
			    अचिन्हित पूर्णांक num_erps,
			    क्रमागत mlxsw_sp_acl_atcam_region_type region_type,
			    अचिन्हित दीर्घ index)
अणु
	अचिन्हित दीर्घ base_index;
	अचिन्हित पूर्णांक entry_size;
	माप_प्रकार size;

	entry_size = erp_core->erpt_entries_size[region_type];
	base_index = index + MLXSW_SP_ACL_ERP_GENALLOC_OFFSET;
	size = num_erps / erp_core->num_erp_banks * entry_size;
	gen_pool_मुक्त(erp_core->erp_tables, base_index, size);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_table_master_rp(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	अगर (!list_is_singular(&erp_table->atcam_erps_list))
		वापस शून्य;

	वापस list_first_entry(&erp_table->atcam_erps_list,
				काष्ठा mlxsw_sp_acl_erp, list);
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_erp_index_get(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				      u8 *p_index)
अणु
	u8 index;

	index = find_first_zero_bit(erp_table->erp_index_biपंचांगap,
				    erp_table->num_max_atcam_erps);
	अगर (index < erp_table->num_max_atcam_erps) अणु
		__set_bit(index, erp_table->erp_index_biपंचांगap);
		*p_index = index;
		वापस 0;
	पूर्ण

	वापस -ENOBUFS;
पूर्ण

अटल व्योम mlxsw_sp_acl_erp_index_put(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				       u8 index)
अणु
	__clear_bit(index, erp_table->erp_index_biपंचांगap);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_table_locate(स्थिर काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			      स्थिर काष्ठा mlxsw_sp_acl_erp *erp,
			      u8 *p_erpt_bank, u8 *p_erpt_index)
अणु
	अचिन्हित पूर्णांक entry_size = mlxsw_sp_acl_erp_table_entry_size(erp_table);
	काष्ठा mlxsw_sp_acl_erp_core *erp_core = erp_table->erp_core;
	अचिन्हित पूर्णांक row;

	*p_erpt_bank = erp->index % erp_core->num_erp_banks;
	row = erp->index / erp_core->num_erp_banks;
	*p_erpt_index = erp_table->base_index + row * entry_size;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_table_erp_add(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			       काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = erp_table->erp_core->mlxsw_sp;
	क्रमागत mlxsw_reg_perpt_key_size key_size;
	अक्षर perpt_pl[MLXSW_REG_PERPT_LEN];
	u8 erpt_bank, erpt_index;

	mlxsw_sp_acl_erp_table_locate(erp_table, erp, &erpt_bank, &erpt_index);
	key_size = (क्रमागत mlxsw_reg_perpt_key_size) erp_table->aregion->type;
	mlxsw_reg_perpt_pack(perpt_pl, erpt_bank, erpt_index, key_size, erp->id,
			     0, erp_table->base_index, erp->index,
			     erp->key.mask);
	mlxsw_reg_perpt_erp_vector_pack(perpt_pl, erp_table->erp_index_biपंचांगap,
					MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	mlxsw_reg_perpt_erp_vector_set(perpt_pl, erp->index, true);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(perpt), perpt_pl);
पूर्ण

अटल व्योम mlxsw_sp_acl_erp_table_erp_del(काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	अक्षर empty_mask[MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN] = अणु 0 पूर्ण;
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = erp->erp_table;
	काष्ठा mlxsw_sp *mlxsw_sp = erp_table->erp_core->mlxsw_sp;
	क्रमागत mlxsw_reg_perpt_key_size key_size;
	अक्षर perpt_pl[MLXSW_REG_PERPT_LEN];
	u8 erpt_bank, erpt_index;

	mlxsw_sp_acl_erp_table_locate(erp_table, erp, &erpt_bank, &erpt_index);
	key_size = (क्रमागत mlxsw_reg_perpt_key_size) erp_table->aregion->type;
	mlxsw_reg_perpt_pack(perpt_pl, erpt_bank, erpt_index, key_size, erp->id,
			     0, erp_table->base_index, erp->index, empty_mask);
	mlxsw_reg_perpt_erp_vector_pack(perpt_pl, erp_table->erp_index_biपंचांगap,
					MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	mlxsw_reg_perpt_erp_vector_set(perpt_pl, erp->index, false);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(perpt), perpt_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_table_enable(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			      bool ctcam_le)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region = erp_table->aregion->region;
	काष्ठा mlxsw_sp *mlxsw_sp = erp_table->erp_core->mlxsw_sp;
	अक्षर pererp_pl[MLXSW_REG_PERERP_LEN];

	mlxsw_reg_pererp_pack(pererp_pl, region->id, ctcam_le, true, 0,
			      erp_table->base_index, 0);
	mlxsw_reg_pererp_erp_vector_pack(pererp_pl, erp_table->erp_index_biपंचांगap,
					 MLXSW_SP_ACL_ERP_MAX_PER_REGION);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pererp), pererp_pl);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_table_disable(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region = erp_table->aregion->region;
	काष्ठा mlxsw_sp *mlxsw_sp = erp_table->erp_core->mlxsw_sp;
	अक्षर pererp_pl[MLXSW_REG_PERERP_LEN];
	काष्ठा mlxsw_sp_acl_erp *master_rp;

	master_rp = mlxsw_sp_acl_erp_table_master_rp(erp_table);
	/* It is possible we करो not have a master RP when we disable the
	 * table when there are no rules in the A-TCAM and the last C-TCAM
	 * rule is deleted
	 */
	mlxsw_reg_pererp_pack(pererp_pl, region->id, false, false, 0, 0,
			      master_rp ? master_rp->id : 0);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pererp), pererp_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_table_relocate(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	काष्ठा mlxsw_sp_acl_erp *erp;
	पूर्णांक err;

	list_क्रम_each_entry(erp, &erp_table->atcam_erps_list, list) अणु
		err = mlxsw_sp_acl_erp_table_erp_add(erp_table, erp);
		अगर (err)
			जाओ err_table_erp_add;
	पूर्ण

	वापस 0;

err_table_erp_add:
	list_क्रम_each_entry_जारी_reverse(erp, &erp_table->atcam_erps_list,
					     list)
		mlxsw_sp_acl_erp_table_erp_del(erp);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_table_expand(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	अचिन्हित पूर्णांक num_erps, old_num_erps = erp_table->num_max_atcam_erps;
	काष्ठा mlxsw_sp_acl_erp_core *erp_core = erp_table->erp_core;
	अचिन्हित दीर्घ old_base_index = erp_table->base_index;
	bool ctcam_le = erp_table->num_ctcam_erps > 0;
	पूर्णांक err;

	अगर (erp_table->num_atcam_erps < erp_table->num_max_atcam_erps)
		वापस 0;

	अगर (erp_table->num_max_atcam_erps == MLXSW_SP_ACL_ERP_MAX_PER_REGION)
		वापस -ENOBUFS;

	num_erps = old_num_erps + erp_core->num_erp_banks;
	err = mlxsw_sp_acl_erp_table_alloc(erp_core, num_erps,
					   erp_table->aregion->type,
					   &erp_table->base_index);
	अगर (err)
		वापस err;
	erp_table->num_max_atcam_erps = num_erps;

	err = mlxsw_sp_acl_erp_table_relocate(erp_table);
	अगर (err)
		जाओ err_table_relocate;

	err = mlxsw_sp_acl_erp_table_enable(erp_table, ctcam_le);
	अगर (err)
		जाओ err_table_enable;

	mlxsw_sp_acl_erp_table_मुक्त(erp_core, old_num_erps,
				    erp_table->aregion->type, old_base_index);

	वापस 0;

err_table_enable:
err_table_relocate:
	erp_table->num_max_atcam_erps = old_num_erps;
	mlxsw_sp_acl_erp_table_मुक्त(erp_core, num_erps,
				    erp_table->aregion->type,
				    erp_table->base_index);
	erp_table->base_index = old_base_index;
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_acl_erp_table_bf_add(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			   काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region *aregion = erp_table->aregion;
	अचिन्हित पूर्णांक erp_bank = mlxsw_sp_acl_erp_bank_get(erp);
	काष्ठा mlxsw_sp_acl_atcam_entry *aentry;
	पूर्णांक err;

	list_क्रम_each_entry(aentry, &aregion->entries_list, list) अणु
		err = mlxsw_sp_acl_bf_entry_add(aregion->region->mlxsw_sp,
						erp_table->erp_core->bf,
						aregion, erp_bank, aentry);
		अगर (err)
			जाओ bf_entry_add_err;
	पूर्ण

	वापस 0;

bf_entry_add_err:
	list_क्रम_each_entry_जारी_reverse(aentry, &aregion->entries_list,
					     list)
		mlxsw_sp_acl_bf_entry_del(aregion->region->mlxsw_sp,
					  erp_table->erp_core->bf,
					  aregion, erp_bank, aentry);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_acl_erp_table_bf_del(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			   काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region *aregion = erp_table->aregion;
	अचिन्हित पूर्णांक erp_bank = mlxsw_sp_acl_erp_bank_get(erp);
	काष्ठा mlxsw_sp_acl_atcam_entry *aentry;

	list_क्रम_each_entry_reverse(aentry, &aregion->entries_list, list)
		mlxsw_sp_acl_bf_entry_del(aregion->region->mlxsw_sp,
					  erp_table->erp_core->bf,
					  aregion, erp_bank, aentry);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_region_table_trans(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	काष्ठा mlxsw_sp_acl_erp_core *erp_core = erp_table->erp_core;
	काष्ठा mlxsw_sp_acl_erp *master_rp;
	पूर्णांक err;

	/* Initially, allocate a single eRP row. Expand later as needed */
	err = mlxsw_sp_acl_erp_table_alloc(erp_core, erp_core->num_erp_banks,
					   erp_table->aregion->type,
					   &erp_table->base_index);
	अगर (err)
		वापस err;
	erp_table->num_max_atcam_erps = erp_core->num_erp_banks;

	/* Transition the sole RP currently configured (the master RP)
	 * to the eRP table
	 */
	master_rp = mlxsw_sp_acl_erp_table_master_rp(erp_table);
	अगर (!master_rp) अणु
		err = -EINVAL;
		जाओ err_table_master_rp;
	पूर्ण

	/* Make sure the master RP is using a valid index, as
	 * only a single eRP row is currently allocated.
	 */
	master_rp->index = 0;
	__set_bit(master_rp->index, erp_table->erp_index_biपंचांगap);

	err = mlxsw_sp_acl_erp_table_erp_add(erp_table, master_rp);
	अगर (err)
		जाओ err_table_master_rp_add;

	/* Update Bloom filter beक्रमe enabling eRP table, as rules
	 * on the master RP were not set to Bloom filter up to this
	 * poपूर्णांक.
	 */
	err = mlxsw_acl_erp_table_bf_add(erp_table, master_rp);
	अगर (err)
		जाओ err_table_bf_add;

	err = mlxsw_sp_acl_erp_table_enable(erp_table, false);
	अगर (err)
		जाओ err_table_enable;

	वापस 0;

err_table_enable:
	mlxsw_acl_erp_table_bf_del(erp_table, master_rp);
err_table_bf_add:
	mlxsw_sp_acl_erp_table_erp_del(master_rp);
err_table_master_rp_add:
	__clear_bit(master_rp->index, erp_table->erp_index_biपंचांगap);
err_table_master_rp:
	mlxsw_sp_acl_erp_table_मुक्त(erp_core, erp_table->num_max_atcam_erps,
				    erp_table->aregion->type,
				    erp_table->base_index);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_region_master_mask_trans(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	काष्ठा mlxsw_sp_acl_erp_core *erp_core = erp_table->erp_core;
	काष्ठा mlxsw_sp_acl_erp *master_rp;

	mlxsw_sp_acl_erp_table_disable(erp_table);
	master_rp = mlxsw_sp_acl_erp_table_master_rp(erp_table);
	अगर (!master_rp)
		वापस;
	mlxsw_acl_erp_table_bf_del(erp_table, master_rp);
	mlxsw_sp_acl_erp_table_erp_del(master_rp);
	__clear_bit(master_rp->index, erp_table->erp_index_biपंचांगap);
	mlxsw_sp_acl_erp_table_मुक्त(erp_core, erp_table->num_max_atcam_erps,
				    erp_table->aregion->type,
				    erp_table->base_index);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_region_erp_add(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region = erp_table->aregion->region;
	काष्ठा mlxsw_sp *mlxsw_sp = erp_table->erp_core->mlxsw_sp;
	bool ctcam_le = erp_table->num_ctcam_erps > 0;
	अक्षर pererp_pl[MLXSW_REG_PERERP_LEN];

	mlxsw_reg_pererp_pack(pererp_pl, region->id, ctcam_le, true, 0,
			      erp_table->base_index, 0);
	mlxsw_reg_pererp_erp_vector_pack(pererp_pl, erp_table->erp_index_biपंचांगap,
					 MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	mlxsw_reg_pererp_erpt_vector_set(pererp_pl, erp->index, true);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pererp), pererp_pl);
पूर्ण

अटल व्योम mlxsw_sp_acl_erp_region_erp_del(काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = erp->erp_table;
	काष्ठा mlxsw_sp_acl_tcam_region *region = erp_table->aregion->region;
	काष्ठा mlxsw_sp *mlxsw_sp = erp_table->erp_core->mlxsw_sp;
	bool ctcam_le = erp_table->num_ctcam_erps > 0;
	अक्षर pererp_pl[MLXSW_REG_PERERP_LEN];

	mlxsw_reg_pererp_pack(pererp_pl, region->id, ctcam_le, true, 0,
			      erp_table->base_index, 0);
	mlxsw_reg_pererp_erp_vector_pack(pererp_pl, erp_table->erp_index_biपंचांगap,
					 MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	mlxsw_reg_pererp_erpt_vector_set(pererp_pl, erp->index, false);

	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pererp), pererp_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_region_ctcam_enable(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	/* No need to re-enable lookup in the C-TCAM */
	अगर (erp_table->num_ctcam_erps > 1)
		वापस 0;

	वापस mlxsw_sp_acl_erp_table_enable(erp_table, true);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_region_ctcam_disable(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	/* Only disable C-TCAM lookup when last C-TCAM eRP is deleted */
	अगर (erp_table->num_ctcam_erps > 1)
		वापस;

	mlxsw_sp_acl_erp_table_enable(erp_table, false);
पूर्ण

अटल पूर्णांक
__mlxsw_sp_acl_erp_table_other_inc(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				   अचिन्हित पूर्णांक *inc_num)
अणु
	पूर्णांक err;

	/* If there are C-TCAM eRP or deltas in use we need to transition
	 * the region to use eRP table, अगर it is not alपढ़ोy करोne
	 */
	अगर (!mlxsw_sp_acl_erp_table_is_used(erp_table)) अणु
		err = mlxsw_sp_acl_erp_region_table_trans(erp_table);
		अगर (err)
			वापस err;
	पूर्ण

	/* When C-TCAM or deltas are used, the eRP table must be used */
	अगर (erp_table->ops != &erp_multiple_masks_ops)
		erp_table->ops = &erp_multiple_masks_ops;

	(*inc_num)++;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_erp_ctcam_inc(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	वापस __mlxsw_sp_acl_erp_table_other_inc(erp_table,
						  &erp_table->num_ctcam_erps);
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_erp_delta_inc(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	वापस __mlxsw_sp_acl_erp_table_other_inc(erp_table,
						  &erp_table->num_deltas);
पूर्ण

अटल व्योम
__mlxsw_sp_acl_erp_table_other_dec(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				   अचिन्हित पूर्णांक *dec_num)
अणु
	(*dec_num)--;

	/* If there are no C-TCAM eRP or deltas in use, the state we
	 * transition to depends on the number of A-TCAM eRPs currently
	 * in use.
	 */
	अगर (erp_table->num_ctcam_erps > 0 || erp_table->num_deltas > 0)
		वापस;

	चयन (erp_table->num_atcam_erps) अणु
	हाल 2:
		/* Keep using the eRP table, but correctly set the
		 * operations poपूर्णांकer so that when an A-TCAM eRP is
		 * deleted we will transition to use the master mask
		 */
		erp_table->ops = &erp_two_masks_ops;
		अवरोध;
	हाल 1:
		/* We only kept the eRP table because we had C-TCAM
		 * eRPs in use. Now that the last C-TCAM eRP is gone we
		 * can stop using the table and transition to use the
		 * master mask
		 */
		mlxsw_sp_acl_erp_region_master_mask_trans(erp_table);
		erp_table->ops = &erp_single_mask_ops;
		अवरोध;
	हाल 0:
		/* There are no more eRPs of any kind used by the region
		 * so मुक्त its eRP table and transition to initial state
		 */
		mlxsw_sp_acl_erp_table_disable(erp_table);
		mlxsw_sp_acl_erp_table_मुक्त(erp_table->erp_core,
					    erp_table->num_max_atcam_erps,
					    erp_table->aregion->type,
					    erp_table->base_index);
		erp_table->ops = &erp_no_mask_ops;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_acl_erp_ctcam_dec(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	__mlxsw_sp_acl_erp_table_other_dec(erp_table,
					   &erp_table->num_ctcam_erps);
पूर्ण

अटल व्योम mlxsw_sp_acl_erp_delta_dec(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	__mlxsw_sp_acl_erp_table_other_dec(erp_table,
					   &erp_table->num_deltas);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_ctcam_mask_create(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				   काष्ठा mlxsw_sp_acl_erp_key *key)
अणु
	काष्ठा mlxsw_sp_acl_erp *erp;
	पूर्णांक err;

	erp = kzalloc(माप(*erp), GFP_KERNEL);
	अगर (!erp)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(&erp->key, key, माप(*key));
	biपंचांगap_from_arr32(erp->mask_biपंचांगap, (u32 *) key->mask,
			  MLXSW_SP_ACL_TCAM_MASK_LEN);

	err = mlxsw_sp_acl_erp_ctcam_inc(erp_table);
	अगर (err)
		जाओ err_erp_ctcam_inc;

	erp->erp_table = erp_table;

	err = mlxsw_sp_acl_erp_master_mask_set(erp_table, &erp->key);
	अगर (err)
		जाओ err_master_mask_set;

	err = mlxsw_sp_acl_erp_region_ctcam_enable(erp_table);
	अगर (err)
		जाओ err_erp_region_ctcam_enable;

	वापस erp;

err_erp_region_ctcam_enable:
	mlxsw_sp_acl_erp_master_mask_clear(erp_table, &erp->key);
err_master_mask_set:
	mlxsw_sp_acl_erp_ctcam_dec(erp_table);
err_erp_ctcam_inc:
	kमुक्त(erp);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_ctcam_mask_destroy(काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = erp->erp_table;

	mlxsw_sp_acl_erp_region_ctcam_disable(erp_table);
	mlxsw_sp_acl_erp_master_mask_clear(erp_table, &erp->key);
	mlxsw_sp_acl_erp_ctcam_dec(erp_table);
	kमुक्त(erp);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_mask_create(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			     काष्ठा mlxsw_sp_acl_erp_key *key)
अणु
	काष्ठा mlxsw_sp_acl_erp *erp;
	पूर्णांक err;

	अगर (key->ctcam)
		वापस mlxsw_sp_acl_erp_ctcam_mask_create(erp_table, key);

	/* Expand the eRP table क्रम the new eRP, अगर needed */
	err = mlxsw_sp_acl_erp_table_expand(erp_table);
	अगर (err)
		वापस ERR_PTR(err);

	erp = mlxsw_sp_acl_erp_generic_create(erp_table, key);
	अगर (IS_ERR(erp))
		वापस erp;

	err = mlxsw_sp_acl_erp_index_get(erp_table, &erp->index);
	अगर (err)
		जाओ err_erp_index_get;

	err = mlxsw_sp_acl_erp_table_erp_add(erp_table, erp);
	अगर (err)
		जाओ err_table_erp_add;

	err = mlxsw_sp_acl_erp_region_erp_add(erp_table, erp);
	अगर (err)
		जाओ err_region_erp_add;

	erp_table->ops = &erp_multiple_masks_ops;

	वापस erp;

err_region_erp_add:
	mlxsw_sp_acl_erp_table_erp_del(erp);
err_table_erp_add:
	mlxsw_sp_acl_erp_index_put(erp_table, erp->index);
err_erp_index_get:
	mlxsw_sp_acl_erp_generic_destroy(erp);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_mask_destroy(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
			      काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	अगर (erp->key.ctcam)
		वापस mlxsw_sp_acl_erp_ctcam_mask_destroy(erp);

	mlxsw_sp_acl_erp_region_erp_del(erp);
	mlxsw_sp_acl_erp_table_erp_del(erp);
	mlxsw_sp_acl_erp_index_put(erp_table, erp->index);
	mlxsw_sp_acl_erp_generic_destroy(erp);

	अगर (erp_table->num_atcam_erps == 2 && erp_table->num_ctcam_erps == 0 &&
	    erp_table->num_deltas == 0)
		erp_table->ops = &erp_two_masks_ops;
पूर्ण

अटल काष्ठा mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_second_mask_create(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				    काष्ठा mlxsw_sp_acl_erp_key *key)
अणु
	काष्ठा mlxsw_sp_acl_erp *erp;
	पूर्णांक err;

	अगर (key->ctcam)
		वापस mlxsw_sp_acl_erp_ctcam_mask_create(erp_table, key);

	/* Transition to use eRP table instead of master mask */
	err = mlxsw_sp_acl_erp_region_table_trans(erp_table);
	अगर (err)
		वापस ERR_PTR(err);

	erp = mlxsw_sp_acl_erp_generic_create(erp_table, key);
	अगर (IS_ERR(erp)) अणु
		err = PTR_ERR(erp);
		जाओ err_erp_create;
	पूर्ण

	err = mlxsw_sp_acl_erp_index_get(erp_table, &erp->index);
	अगर (err)
		जाओ err_erp_index_get;

	err = mlxsw_sp_acl_erp_table_erp_add(erp_table, erp);
	अगर (err)
		जाओ err_table_erp_add;

	err = mlxsw_sp_acl_erp_region_erp_add(erp_table, erp);
	अगर (err)
		जाओ err_region_erp_add;

	erp_table->ops = &erp_two_masks_ops;

	वापस erp;

err_region_erp_add:
	mlxsw_sp_acl_erp_table_erp_del(erp);
err_table_erp_add:
	mlxsw_sp_acl_erp_index_put(erp_table, erp->index);
err_erp_index_get:
	mlxsw_sp_acl_erp_generic_destroy(erp);
err_erp_create:
	mlxsw_sp_acl_erp_region_master_mask_trans(erp_table);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_second_mask_destroy(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				     काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	अगर (erp->key.ctcam)
		वापस mlxsw_sp_acl_erp_ctcam_mask_destroy(erp);

	mlxsw_sp_acl_erp_region_erp_del(erp);
	mlxsw_sp_acl_erp_table_erp_del(erp);
	mlxsw_sp_acl_erp_index_put(erp_table, erp->index);
	mlxsw_sp_acl_erp_generic_destroy(erp);
	/* Transition to use master mask instead of eRP table */
	mlxsw_sp_acl_erp_region_master_mask_trans(erp_table);

	erp_table->ops = &erp_single_mask_ops;
पूर्ण

अटल काष्ठा mlxsw_sp_acl_erp *
mlxsw_sp_acl_erp_first_mask_create(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				   काष्ठा mlxsw_sp_acl_erp_key *key)
अणु
	काष्ठा mlxsw_sp_acl_erp *erp;

	अगर (key->ctcam)
		वापस ERR_PTR(-EINVAL);

	erp = mlxsw_sp_acl_erp_generic_create(erp_table, key);
	अगर (IS_ERR(erp))
		वापस erp;

	erp_table->ops = &erp_single_mask_ops;

	वापस erp;
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_first_mask_destroy(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				    काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	mlxsw_sp_acl_erp_generic_destroy(erp);
	erp_table->ops = &erp_no_mask_ops;
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_no_mask_destroy(काष्ठा mlxsw_sp_acl_erp_table *erp_table,
				 काष्ठा mlxsw_sp_acl_erp *erp)
अणु
	WARN_ON(1);
पूर्ण

काष्ठा mlxsw_sp_acl_erp_mask *
mlxsw_sp_acl_erp_mask_get(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			  स्थिर अक्षर *mask, bool ctcam)
अणु
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;
	काष्ठा mlxsw_sp_acl_erp_key key;
	काष्ठा objagg_obj *objagg_obj;

	स_नकल(key.mask, mask, MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN);
	key.ctcam = ctcam;
	mutex_lock(&erp_table->objagg_lock);
	objagg_obj = objagg_obj_get(erp_table->objagg, &key);
	mutex_unlock(&erp_table->objagg_lock);
	अगर (IS_ERR(objagg_obj))
		वापस ERR_CAST(objagg_obj);
	वापस (काष्ठा mlxsw_sp_acl_erp_mask *) objagg_obj;
पूर्ण

व्योम mlxsw_sp_acl_erp_mask_put(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			       काष्ठा mlxsw_sp_acl_erp_mask *erp_mask)
अणु
	काष्ठा objagg_obj *objagg_obj = (काष्ठा objagg_obj *) erp_mask;
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;

	mutex_lock(&erp_table->objagg_lock);
	objagg_obj_put(erp_table->objagg, objagg_obj);
	mutex_unlock(&erp_table->objagg_lock);
पूर्ण

पूर्णांक mlxsw_sp_acl_erp_bf_insert(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			       काष्ठा mlxsw_sp_acl_erp_mask *erp_mask,
			       काष्ठा mlxsw_sp_acl_atcam_entry *aentry)
अणु
	काष्ठा objagg_obj *objagg_obj = (काष्ठा objagg_obj *) erp_mask;
	स्थिर काष्ठा mlxsw_sp_acl_erp *erp = objagg_obj_root_priv(objagg_obj);
	अचिन्हित पूर्णांक erp_bank;

	अगर (!mlxsw_sp_acl_erp_table_is_used(erp->erp_table))
		वापस 0;

	erp_bank = mlxsw_sp_acl_erp_bank_get(erp);
	वापस mlxsw_sp_acl_bf_entry_add(mlxsw_sp,
					erp->erp_table->erp_core->bf,
					aregion, erp_bank, aentry);
पूर्ण

व्योम mlxsw_sp_acl_erp_bf_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				काष्ठा mlxsw_sp_acl_erp_mask *erp_mask,
				काष्ठा mlxsw_sp_acl_atcam_entry *aentry)
अणु
	काष्ठा objagg_obj *objagg_obj = (काष्ठा objagg_obj *) erp_mask;
	स्थिर काष्ठा mlxsw_sp_acl_erp *erp = objagg_obj_root_priv(objagg_obj);
	अचिन्हित पूर्णांक erp_bank;

	अगर (!mlxsw_sp_acl_erp_table_is_used(erp->erp_table))
		वापस;

	erp_bank = mlxsw_sp_acl_erp_bank_get(erp);
	mlxsw_sp_acl_bf_entry_del(mlxsw_sp,
				  erp->erp_table->erp_core->bf,
				  aregion, erp_bank, aentry);
पूर्ण

bool
mlxsw_sp_acl_erp_mask_is_ctcam(स्थिर काष्ठा mlxsw_sp_acl_erp_mask *erp_mask)
अणु
	काष्ठा objagg_obj *objagg_obj = (काष्ठा objagg_obj *) erp_mask;
	स्थिर काष्ठा mlxsw_sp_acl_erp_key *key = objagg_obj_raw(objagg_obj);

	वापस key->ctcam;
पूर्ण

u8 mlxsw_sp_acl_erp_mask_erp_id(स्थिर काष्ठा mlxsw_sp_acl_erp_mask *erp_mask)
अणु
	काष्ठा objagg_obj *objagg_obj = (काष्ठा objagg_obj *) erp_mask;
	स्थिर काष्ठा mlxsw_sp_acl_erp *erp = objagg_obj_root_priv(objagg_obj);

	वापस erp->id;
पूर्ण

काष्ठा mlxsw_sp_acl_erp_delta अणु
	काष्ठा mlxsw_sp_acl_erp_key key;
	u16 start;
	u8 mask;
पूर्ण;

u16 mlxsw_sp_acl_erp_delta_start(स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta)
अणु
	वापस delta->start;
पूर्ण

u8 mlxsw_sp_acl_erp_delta_mask(स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta)
अणु
	वापस delta->mask;
पूर्ण

u8 mlxsw_sp_acl_erp_delta_value(स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta,
				स्थिर अक्षर *enc_key)
अणु
	u16 start = delta->start;
	u8 mask = delta->mask;
	u16 पंचांगp;

	अगर (!mask)
		वापस 0;

	पंचांगp = (अचिन्हित अक्षर) enc_key[__MASK_IDX(start / 8)];
	अगर (start / 8 + 1 < __MASK_LEN)
		पंचांगp |= (अचिन्हित अक्षर) enc_key[__MASK_IDX(start / 8 + 1)] << 8;
	पंचांगp >>= start % 8;
	पंचांगp &= mask;
	वापस पंचांगp;
पूर्ण

व्योम mlxsw_sp_acl_erp_delta_clear(स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta,
				  स्थिर अक्षर *enc_key)
अणु
	u16 start = delta->start;
	u8 mask = delta->mask;
	अचिन्हित अक्षर *byte;
	u16 पंचांगp;

	पंचांगp = mask;
	पंचांगp <<= start % 8;
	पंचांगp = ~पंचांगp;

	byte = (अचिन्हित अक्षर *) &enc_key[__MASK_IDX(start / 8)];
	*byte &= पंचांगp & 0xff;
	अगर (start / 8 + 1 < __MASK_LEN) अणु
		byte = (अचिन्हित अक्षर *) &enc_key[__MASK_IDX(start / 8 + 1)];
		*byte &= (पंचांगp >> 8) & 0xff;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_acl_erp_delta
mlxsw_sp_acl_erp_delta_शेष = अणुपूर्ण;

स्थिर काष्ठा mlxsw_sp_acl_erp_delta *
mlxsw_sp_acl_erp_delta(स्थिर काष्ठा mlxsw_sp_acl_erp_mask *erp_mask)
अणु
	काष्ठा objagg_obj *objagg_obj = (काष्ठा objagg_obj *) erp_mask;
	स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta;

	delta = objagg_obj_delta_priv(objagg_obj);
	अगर (!delta)
		delta = &mlxsw_sp_acl_erp_delta_शेष;
	वापस delta;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_delta_fill(स्थिर काष्ठा mlxsw_sp_acl_erp_key *parent_key,
			    स्थिर काष्ठा mlxsw_sp_acl_erp_key *key,
			    u16 *delta_start, u8 *delta_mask)
अणु
	पूर्णांक offset = 0;
	पूर्णांक si = -1;
	u16 pmask;
	u16 mask;
	पूर्णांक i;

	/* The dअगरference between 2 masks can be up to 8 consecutive bits. */
	क्रम (i = 0; i < __MASK_LEN; i++) अणु
		अगर (parent_key->mask[__MASK_IDX(i)] == key->mask[__MASK_IDX(i)])
			जारी;
		अगर (si == -1)
			si = i;
		अन्यथा अगर (si != i - 1)
			वापस -EINVAL;
	पूर्ण
	अगर (si == -1) अणु
		/* The masks are the same, this can happen in हाल eRPs with
		 * the same mask were created in both A-TCAM and C-TCAM.
		 * The only possible condition under which this can happen
		 * is identical rule insertion. Delta is not possible here.
		 */
		वापस -EINVAL;
	पूर्ण
	pmask = (अचिन्हित अक्षर) parent_key->mask[__MASK_IDX(si)];
	mask = (अचिन्हित अक्षर) key->mask[__MASK_IDX(si)];
	अगर (si + 1 < __MASK_LEN) अणु
		pmask |= (अचिन्हित अक्षर) parent_key->mask[__MASK_IDX(si + 1)] << 8;
		mask |= (अचिन्हित अक्षर) key->mask[__MASK_IDX(si + 1)] << 8;
	पूर्ण

	अगर ((pmask ^ mask) & pmask)
		वापस -EINVAL;
	mask &= ~pmask;
	जबतक (!(mask & (1 << offset)))
		offset++;
	जबतक (!(mask & 1))
		mask >>= 1;
	अगर (mask & 0xff00)
		वापस -EINVAL;

	*delta_start = si * 8 + offset;
	*delta_mask = mask;

	वापस 0;
पूर्ण

अटल bool mlxsw_sp_acl_erp_delta_check(व्योम *priv, स्थिर व्योम *parent_obj,
					 स्थिर व्योम *obj)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_erp_key *parent_key = parent_obj;
	स्थिर काष्ठा mlxsw_sp_acl_erp_key *key = obj;
	u16 delta_start;
	u8 delta_mask;
	पूर्णांक err;

	err = mlxsw_sp_acl_erp_delta_fill(parent_key, key,
					  &delta_start, &delta_mask);
	वापस err ? false : true;
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_erp_hपूर्णांकs_obj_cmp(स्थिर व्योम *obj1, स्थिर व्योम *obj2)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_erp_key *key1 = obj1;
	स्थिर काष्ठा mlxsw_sp_acl_erp_key *key2 = obj2;

	/* For hपूर्णांकs purposes, two objects are considered equal
	 * in हाल the masks are the same. Does not matter what
	 * the "ctcam" value is.
	 */
	वापस स_भेद(key1->mask, key2->mask, माप(key1->mask));
पूर्ण

अटल व्योम *mlxsw_sp_acl_erp_delta_create(व्योम *priv, व्योम *parent_obj,
					   व्योम *obj)
अणु
	काष्ठा mlxsw_sp_acl_erp_key *parent_key = parent_obj;
	काष्ठा mlxsw_sp_acl_atcam_region *aregion = priv;
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;
	काष्ठा mlxsw_sp_acl_erp_key *key = obj;
	काष्ठा mlxsw_sp_acl_erp_delta *delta;
	u16 delta_start;
	u8 delta_mask;
	पूर्णांक err;

	अगर (parent_key->ctcam || key->ctcam)
		वापस ERR_PTR(-EINVAL);
	err = mlxsw_sp_acl_erp_delta_fill(parent_key, key,
					  &delta_start, &delta_mask);
	अगर (err)
		वापस ERR_PTR(-EINVAL);

	delta = kzalloc(माप(*delta), GFP_KERNEL);
	अगर (!delta)
		वापस ERR_PTR(-ENOMEM);
	delta->start = delta_start;
	delta->mask = delta_mask;

	err = mlxsw_sp_acl_erp_delta_inc(erp_table);
	अगर (err)
		जाओ err_erp_delta_inc;

	स_नकल(&delta->key, key, माप(*key));
	err = mlxsw_sp_acl_erp_master_mask_set(erp_table, &delta->key);
	अगर (err)
		जाओ err_master_mask_set;

	वापस delta;

err_master_mask_set:
	mlxsw_sp_acl_erp_delta_dec(erp_table);
err_erp_delta_inc:
	kमुक्त(delta);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_acl_erp_delta_destroy(व्योम *priv, व्योम *delta_priv)
अणु
	काष्ठा mlxsw_sp_acl_erp_delta *delta = delta_priv;
	काष्ठा mlxsw_sp_acl_atcam_region *aregion = priv;
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;

	mlxsw_sp_acl_erp_master_mask_clear(erp_table, &delta->key);
	mlxsw_sp_acl_erp_delta_dec(erp_table);
	kमुक्त(delta);
पूर्ण

अटल व्योम *mlxsw_sp_acl_erp_root_create(व्योम *priv, व्योम *obj,
					  अचिन्हित पूर्णांक root_id)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region *aregion = priv;
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;
	काष्ठा mlxsw_sp_acl_erp_key *key = obj;

	अगर (!key->ctcam &&
	    root_id != OBJAGG_OBJ_ROOT_ID_INVALID &&
	    root_id >= MLXSW_SP_ACL_ERP_MAX_PER_REGION)
		वापस ERR_PTR(-ENOBUFS);
	वापस erp_table->ops->erp_create(erp_table, key);
पूर्ण

अटल व्योम mlxsw_sp_acl_erp_root_destroy(व्योम *priv, व्योम *root_priv)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region *aregion = priv;
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;

	erp_table->ops->erp_destroy(erp_table, root_priv);
पूर्ण

अटल स्थिर काष्ठा objagg_ops mlxsw_sp_acl_erp_objagg_ops = अणु
	.obj_size = माप(काष्ठा mlxsw_sp_acl_erp_key),
	.delta_check = mlxsw_sp_acl_erp_delta_check,
	.hपूर्णांकs_obj_cmp = mlxsw_sp_acl_erp_hपूर्णांकs_obj_cmp,
	.delta_create = mlxsw_sp_acl_erp_delta_create,
	.delta_destroy = mlxsw_sp_acl_erp_delta_destroy,
	.root_create = mlxsw_sp_acl_erp_root_create,
	.root_destroy = mlxsw_sp_acl_erp_root_destroy,
पूर्ण;

अटल काष्ठा mlxsw_sp_acl_erp_table *
mlxsw_sp_acl_erp_table_create(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			      काष्ठा objagg_hपूर्णांकs *hपूर्णांकs)
अणु
	काष्ठा mlxsw_sp_acl_erp_table *erp_table;
	पूर्णांक err;

	erp_table = kzalloc(माप(*erp_table), GFP_KERNEL);
	अगर (!erp_table)
		वापस ERR_PTR(-ENOMEM);

	erp_table->objagg = objagg_create(&mlxsw_sp_acl_erp_objagg_ops,
					  hपूर्णांकs, aregion);
	अगर (IS_ERR(erp_table->objagg)) अणु
		err = PTR_ERR(erp_table->objagg);
		जाओ err_objagg_create;
	पूर्ण

	erp_table->erp_core = aregion->atcam->erp_core;
	erp_table->ops = &erp_no_mask_ops;
	INIT_LIST_HEAD(&erp_table->atcam_erps_list);
	erp_table->aregion = aregion;
	mutex_init(&erp_table->objagg_lock);

	वापस erp_table;

err_objagg_create:
	kमुक्त(erp_table);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_acl_erp_table_destroy(काष्ठा mlxsw_sp_acl_erp_table *erp_table)
अणु
	WARN_ON(!list_empty(&erp_table->atcam_erps_list));
	mutex_destroy(&erp_table->objagg_lock);
	objagg_destroy(erp_table->objagg);
	kमुक्त(erp_table);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_master_mask_init(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = aregion->region->mlxsw_sp;
	अक्षर percr_pl[MLXSW_REG_PERCR_LEN];

	mlxsw_reg_percr_pack(percr_pl, aregion->region->id);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(percr), percr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_region_param_init(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = aregion->region->mlxsw_sp;
	अक्षर pererp_pl[MLXSW_REG_PERERP_LEN];

	mlxsw_reg_pererp_pack(pererp_pl, aregion->region->id, false, false, 0,
			      0, 0);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pererp), pererp_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_hपूर्णांकs_check(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			     काष्ठा objagg_hपूर्णांकs *hपूर्णांकs, bool *p_rehash_needed)
अणु
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;
	स्थिर काष्ठा objagg_stats *ostats;
	स्थिर काष्ठा objagg_stats *hstats;
	पूर्णांक err;

	*p_rehash_needed = false;

	mutex_lock(&erp_table->objagg_lock);
	ostats = objagg_stats_get(erp_table->objagg);
	mutex_unlock(&erp_table->objagg_lock);
	अगर (IS_ERR(ostats)) अणु
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to get ERP stats\n");
		वापस PTR_ERR(ostats);
	पूर्ण

	hstats = objagg_hपूर्णांकs_stats_get(hपूर्णांकs);
	अगर (IS_ERR(hstats)) अणु
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to get ERP hints stats\n");
		err = PTR_ERR(hstats);
		जाओ err_hपूर्णांकs_stats_get;
	पूर्ण

	/* Very basic criterion क्रम now. */
	अगर (hstats->root_count < ostats->root_count)
		*p_rehash_needed = true;

	err = 0;

	objagg_stats_put(hstats);
err_hपूर्णांकs_stats_get:
	objagg_stats_put(ostats);
	वापस err;
पूर्ण

व्योम *
mlxsw_sp_acl_erp_rehash_hपूर्णांकs_get(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	काष्ठा mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;
	काष्ठा mlxsw_sp *mlxsw_sp = aregion->region->mlxsw_sp;
	काष्ठा objagg_hपूर्णांकs *hपूर्णांकs;
	bool rehash_needed;
	पूर्णांक err;

	mutex_lock(&erp_table->objagg_lock);
	hपूर्णांकs = objagg_hपूर्णांकs_get(erp_table->objagg,
				 OBJAGG_OPT_ALGO_SIMPLE_GREEDY);
	mutex_unlock(&erp_table->objagg_lock);
	अगर (IS_ERR(hपूर्णांकs)) अणु
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to create ERP hints\n");
		वापस ERR_CAST(hपूर्णांकs);
	पूर्ण
	err = mlxsw_sp_acl_erp_hपूर्णांकs_check(mlxsw_sp, aregion, hपूर्णांकs,
					   &rehash_needed);
	अगर (err)
		जाओ errout;

	अगर (!rehash_needed) अणु
		err = -EAGAIN;
		जाओ errout;
	पूर्ण
	वापस hपूर्णांकs;

errout:
	objagg_hपूर्णांकs_put(hपूर्णांकs);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlxsw_sp_acl_erp_rehash_hपूर्णांकs_put(व्योम *hपूर्णांकs_priv)
अणु
	काष्ठा objagg_hपूर्णांकs *hपूर्णांकs = hपूर्णांकs_priv;

	objagg_hपूर्णांकs_put(hपूर्णांकs);
पूर्ण

पूर्णांक mlxsw_sp_acl_erp_region_init(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				 व्योम *hपूर्णांकs_priv)
अणु
	काष्ठा mlxsw_sp_acl_erp_table *erp_table;
	काष्ठा objagg_hपूर्णांकs *hपूर्णांकs = hपूर्णांकs_priv;
	पूर्णांक err;

	erp_table = mlxsw_sp_acl_erp_table_create(aregion, hपूर्णांकs);
	अगर (IS_ERR(erp_table))
		वापस PTR_ERR(erp_table);
	aregion->erp_table = erp_table;

	/* Initialize the region's master mask to all zeroes */
	err = mlxsw_sp_acl_erp_master_mask_init(aregion);
	अगर (err)
		जाओ err_erp_master_mask_init;

	/* Initialize the region to not use the eRP table */
	err = mlxsw_sp_acl_erp_region_param_init(aregion);
	अगर (err)
		जाओ err_erp_region_param_init;

	वापस 0;

err_erp_region_param_init:
err_erp_master_mask_init:
	mlxsw_sp_acl_erp_table_destroy(erp_table);
	वापस err;
पूर्ण

व्योम mlxsw_sp_acl_erp_region_fini(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	mlxsw_sp_acl_erp_table_destroy(aregion->erp_table);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_erp_tables_sizes_query(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_acl_erp_core *erp_core)
अणु
	अचिन्हित पूर्णांक size;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_ERPT_ENTRIES_2KB) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_ERPT_ENTRIES_4KB) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_ERPT_ENTRIES_8KB) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_ERPT_ENTRIES_12KB))
		वापस -EIO;

	size = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_ERPT_ENTRIES_2KB);
	erp_core->erpt_entries_size[MLXSW_SP_ACL_ATCAM_REGION_TYPE_2KB] = size;

	size = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_ERPT_ENTRIES_4KB);
	erp_core->erpt_entries_size[MLXSW_SP_ACL_ATCAM_REGION_TYPE_4KB] = size;

	size = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_ERPT_ENTRIES_8KB);
	erp_core->erpt_entries_size[MLXSW_SP_ACL_ATCAM_REGION_TYPE_8KB] = size;

	size = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_ERPT_ENTRIES_12KB);
	erp_core->erpt_entries_size[MLXSW_SP_ACL_ATCAM_REGION_TYPE_12KB] = size;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_erp_tables_init(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_acl_erp_core *erp_core)
अणु
	अचिन्हित पूर्णांक erpt_bank_size;
	पूर्णांक err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_MAX_ERPT_BANK_SIZE) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_MAX_ERPT_BANKS))
		वापस -EIO;
	erpt_bank_size = MLXSW_CORE_RES_GET(mlxsw_sp->core,
					    ACL_MAX_ERPT_BANK_SIZE);
	erp_core->num_erp_banks = MLXSW_CORE_RES_GET(mlxsw_sp->core,
						     ACL_MAX_ERPT_BANKS);

	erp_core->erp_tables = gen_pool_create(0, -1);
	अगर (!erp_core->erp_tables)
		वापस -ENOMEM;
	gen_pool_set_algo(erp_core->erp_tables, gen_pool_best_fit, शून्य);

	err = gen_pool_add(erp_core->erp_tables,
			   MLXSW_SP_ACL_ERP_GENALLOC_OFFSET, erpt_bank_size,
			   -1);
	अगर (err)
		जाओ err_gen_pool_add;

	erp_core->bf = mlxsw_sp_acl_bf_init(mlxsw_sp, erp_core->num_erp_banks);
	अगर (IS_ERR(erp_core->bf)) अणु
		err = PTR_ERR(erp_core->bf);
		जाओ err_bf_init;
	पूर्ण

	/* Dअगरferent regions require masks of dअगरferent sizes */
	err = mlxsw_sp_acl_erp_tables_sizes_query(mlxsw_sp, erp_core);
	अगर (err)
		जाओ err_erp_tables_sizes_query;

	वापस 0;

err_erp_tables_sizes_query:
	mlxsw_sp_acl_bf_fini(erp_core->bf);
err_bf_init:
err_gen_pool_add:
	gen_pool_destroy(erp_core->erp_tables);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_acl_erp_tables_fini(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_acl_erp_core *erp_core)
अणु
	mlxsw_sp_acl_bf_fini(erp_core->bf);
	gen_pool_destroy(erp_core->erp_tables);
पूर्ण

पूर्णांक mlxsw_sp_acl_erps_init(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_acl_atcam *atcam)
अणु
	काष्ठा mlxsw_sp_acl_erp_core *erp_core;
	पूर्णांक err;

	erp_core = kzalloc(माप(*erp_core), GFP_KERNEL);
	अगर (!erp_core)
		वापस -ENOMEM;
	erp_core->mlxsw_sp = mlxsw_sp;
	atcam->erp_core = erp_core;

	err = mlxsw_sp_acl_erp_tables_init(mlxsw_sp, erp_core);
	अगर (err)
		जाओ err_erp_tables_init;

	वापस 0;

err_erp_tables_init:
	kमुक्त(erp_core);
	वापस err;
पूर्ण

व्योम mlxsw_sp_acl_erps_fini(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_acl_atcam *atcam)
अणु
	mlxsw_sp_acl_erp_tables_fini(mlxsw_sp, atcam->erp_core);
	kमुक्त(atcam->erp_core);
पूर्ण
