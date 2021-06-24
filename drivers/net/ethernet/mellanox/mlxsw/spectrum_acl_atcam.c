<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/refcount.h>
#समावेश <linux/rhashtable.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/mlxsw.h>

#समावेश "reg.h"
#समावेश "core.h"
#समावेश "spectrum.h"
#समावेश "spectrum_acl_tcam.h"
#समावेश "core_acl_flex_keys.h"

#घोषणा MLXSW_SP_ACL_ATCAM_LKEY_ID_BLOCK_CLEAR_START	0
#घोषणा MLXSW_SP_ACL_ATCAM_LKEY_ID_BLOCK_CLEAR_END	5

काष्ठा mlxsw_sp_acl_atcam_lkey_id_ht_key अणु
	अक्षर enc_key[MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN]; /* MSB blocks */
	u8 erp_id;
पूर्ण;

काष्ठा mlxsw_sp_acl_atcam_lkey_id अणु
	काष्ठा rhash_head ht_node;
	काष्ठा mlxsw_sp_acl_atcam_lkey_id_ht_key ht_key;
	refcount_t refcnt;
	u32 id;
पूर्ण;

काष्ठा mlxsw_sp_acl_atcam_region_ops अणु
	पूर्णांक (*init)(काष्ठा mlxsw_sp_acl_atcam_region *aregion);
	व्योम (*fini)(काष्ठा mlxsw_sp_acl_atcam_region *aregion);
	काष्ठा mlxsw_sp_acl_atcam_lkey_id *
		(*lkey_id_get)(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			       अक्षर *enc_key, u8 erp_id);
	व्योम (*lkey_id_put)(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			    काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id);
पूर्ण;

काष्ठा mlxsw_sp_acl_atcam_region_generic अणु
	काष्ठा mlxsw_sp_acl_atcam_lkey_id dummy_lkey_id;
पूर्ण;

काष्ठा mlxsw_sp_acl_atcam_region_12kb अणु
	काष्ठा rhashtable lkey_ht;
	अचिन्हित पूर्णांक max_lkey_id;
	अचिन्हित दीर्घ *used_lkey_id;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_acl_atcam_lkey_id_ht_params = अणु
	.key_len = माप(काष्ठा mlxsw_sp_acl_atcam_lkey_id_ht_key),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_acl_atcam_lkey_id, ht_key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_acl_atcam_lkey_id, ht_node),
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_acl_atcam_entries_ht_params = अणु
	.key_len = माप(काष्ठा mlxsw_sp_acl_atcam_entry_ht_key),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_acl_atcam_entry, ht_key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_acl_atcam_entry, ht_node),
पूर्ण;

अटल bool
mlxsw_sp_acl_atcam_is_centry(स्थिर काष्ठा mlxsw_sp_acl_atcam_entry *aentry)
अणु
	वापस mlxsw_sp_acl_erp_mask_is_ctcam(aentry->erp_mask);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_atcam_region_generic_init(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region_generic *region_generic;

	region_generic = kzalloc(माप(*region_generic), GFP_KERNEL);
	अगर (!region_generic)
		वापस -ENOMEM;

	refcount_set(&region_generic->dummy_lkey_id.refcnt, 1);
	aregion->priv = region_generic;

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_acl_atcam_region_generic_fini(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	kमुक्त(aregion->priv);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_atcam_lkey_id *
mlxsw_sp_acl_atcam_generic_lkey_id_get(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				       अक्षर *enc_key, u8 erp_id)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region_generic *region_generic;

	region_generic = aregion->priv;
	वापस &region_generic->dummy_lkey_id;
पूर्ण

अटल व्योम
mlxsw_sp_acl_atcam_generic_lkey_id_put(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				       काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id)
अणु
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_acl_atcam_region_ops
mlxsw_sp_acl_atcam_region_generic_ops = अणु
	.init		= mlxsw_sp_acl_atcam_region_generic_init,
	.fini		= mlxsw_sp_acl_atcam_region_generic_fini,
	.lkey_id_get	= mlxsw_sp_acl_atcam_generic_lkey_id_get,
	.lkey_id_put	= mlxsw_sp_acl_atcam_generic_lkey_id_put,
पूर्ण;

अटल पूर्णांक
mlxsw_sp_acl_atcam_region_12kb_init(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = aregion->region->mlxsw_sp;
	काष्ठा mlxsw_sp_acl_atcam_region_12kb *region_12kb;
	माप_प्रकार alloc_size;
	u64 max_lkey_id;
	पूर्णांक err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, ACL_MAX_LARGE_KEY_ID))
		वापस -EIO;

	max_lkey_id = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_MAX_LARGE_KEY_ID);
	region_12kb = kzalloc(माप(*region_12kb), GFP_KERNEL);
	अगर (!region_12kb)
		वापस -ENOMEM;

	alloc_size = BITS_TO_LONGS(max_lkey_id) * माप(अचिन्हित दीर्घ);
	region_12kb->used_lkey_id = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!region_12kb->used_lkey_id) अणु
		err = -ENOMEM;
		जाओ err_used_lkey_id_alloc;
	पूर्ण

	err = rhashtable_init(&region_12kb->lkey_ht,
			      &mlxsw_sp_acl_atcam_lkey_id_ht_params);
	अगर (err)
		जाओ err_rhashtable_init;

	region_12kb->max_lkey_id = max_lkey_id;
	aregion->priv = region_12kb;

	वापस 0;

err_rhashtable_init:
	kमुक्त(region_12kb->used_lkey_id);
err_used_lkey_id_alloc:
	kमुक्त(region_12kb);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_atcam_region_12kb_fini(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region_12kb *region_12kb = aregion->priv;

	rhashtable_destroy(&region_12kb->lkey_ht);
	kमुक्त(region_12kb->used_lkey_id);
	kमुक्त(region_12kb);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_atcam_lkey_id *
mlxsw_sp_acl_atcam_lkey_id_create(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				  काष्ठा mlxsw_sp_acl_atcam_lkey_id_ht_key *ht_key)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region_12kb *region_12kb = aregion->priv;
	काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id;
	u32 id;
	पूर्णांक err;

	id = find_first_zero_bit(region_12kb->used_lkey_id,
				 region_12kb->max_lkey_id);
	अगर (id < region_12kb->max_lkey_id)
		__set_bit(id, region_12kb->used_lkey_id);
	अन्यथा
		वापस ERR_PTR(-ENOBUFS);

	lkey_id = kzalloc(माप(*lkey_id), GFP_KERNEL);
	अगर (!lkey_id) अणु
		err = -ENOMEM;
		जाओ err_lkey_id_alloc;
	पूर्ण

	lkey_id->id = id;
	स_नकल(&lkey_id->ht_key, ht_key, माप(*ht_key));
	refcount_set(&lkey_id->refcnt, 1);

	err = rhashtable_insert_fast(&region_12kb->lkey_ht,
				     &lkey_id->ht_node,
				     mlxsw_sp_acl_atcam_lkey_id_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	वापस lkey_id;

err_rhashtable_insert:
	kमुक्त(lkey_id);
err_lkey_id_alloc:
	__clear_bit(id, region_12kb->used_lkey_id);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_acl_atcam_lkey_id_destroy(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				   काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region_12kb *region_12kb = aregion->priv;
	u32 id = lkey_id->id;

	rhashtable_हटाओ_fast(&region_12kb->lkey_ht, &lkey_id->ht_node,
			       mlxsw_sp_acl_atcam_lkey_id_ht_params);
	kमुक्त(lkey_id);
	__clear_bit(id, region_12kb->used_lkey_id);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_atcam_lkey_id *
mlxsw_sp_acl_atcam_12kb_lkey_id_get(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				    अक्षर *enc_key, u8 erp_id)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region_12kb *region_12kb = aregion->priv;
	काष्ठा mlxsw_sp_acl_tcam_region *region = aregion->region;
	काष्ठा mlxsw_sp_acl_atcam_lkey_id_ht_key ht_key = अणुअणु 0 पूर्ण पूर्ण;
	काष्ठा mlxsw_sp *mlxsw_sp = region->mlxsw_sp;
	काष्ठा mlxsw_afk *afk = mlxsw_sp_acl_afk(mlxsw_sp->acl);
	काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id;

	स_नकल(ht_key.enc_key, enc_key, माप(ht_key.enc_key));
	mlxsw_afk_clear(afk, ht_key.enc_key,
			MLXSW_SP_ACL_ATCAM_LKEY_ID_BLOCK_CLEAR_START,
			MLXSW_SP_ACL_ATCAM_LKEY_ID_BLOCK_CLEAR_END);
	ht_key.erp_id = erp_id;
	lkey_id = rhashtable_lookup_fast(&region_12kb->lkey_ht, &ht_key,
					 mlxsw_sp_acl_atcam_lkey_id_ht_params);
	अगर (lkey_id) अणु
		refcount_inc(&lkey_id->refcnt);
		वापस lkey_id;
	पूर्ण

	वापस mlxsw_sp_acl_atcam_lkey_id_create(aregion, &ht_key);
पूर्ण

अटल व्योम
mlxsw_sp_acl_atcam_12kb_lkey_id_put(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				    काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id)
अणु
	अगर (refcount_dec_and_test(&lkey_id->refcnt))
		mlxsw_sp_acl_atcam_lkey_id_destroy(aregion, lkey_id);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_acl_atcam_region_ops
mlxsw_sp_acl_atcam_region_12kb_ops = अणु
	.init		= mlxsw_sp_acl_atcam_region_12kb_init,
	.fini		= mlxsw_sp_acl_atcam_region_12kb_fini,
	.lkey_id_get	= mlxsw_sp_acl_atcam_12kb_lkey_id_get,
	.lkey_id_put	= mlxsw_sp_acl_atcam_12kb_lkey_id_put,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_acl_atcam_region_ops *
mlxsw_sp_acl_atcam_region_ops_arr[] = अणु
	[MLXSW_SP_ACL_ATCAM_REGION_TYPE_2KB]	=
		&mlxsw_sp_acl_atcam_region_generic_ops,
	[MLXSW_SP_ACL_ATCAM_REGION_TYPE_4KB]	=
		&mlxsw_sp_acl_atcam_region_generic_ops,
	[MLXSW_SP_ACL_ATCAM_REGION_TYPE_8KB]	=
		&mlxsw_sp_acl_atcam_region_generic_ops,
	[MLXSW_SP_ACL_ATCAM_REGION_TYPE_12KB]	=
		&mlxsw_sp_acl_atcam_region_12kb_ops,
पूर्ण;

पूर्णांक mlxsw_sp_acl_atcam_region_associate(काष्ठा mlxsw_sp *mlxsw_sp,
					u16 region_id)
अणु
	अक्षर perar_pl[MLXSW_REG_PERAR_LEN];
	/* For now, just assume that every region has 12 key blocks */
	u16 hw_region = region_id * 3;
	u64 max_regions;

	max_regions = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_MAX_REGIONS);
	अगर (hw_region >= max_regions)
		वापस -ENOBUFS;

	mlxsw_reg_perar_pack(perar_pl, region_id, hw_region);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(perar), perar_pl);
पूर्ण

अटल व्योम
mlxsw_sp_acl_atcam_region_type_init(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region = aregion->region;
	क्रमागत mlxsw_sp_acl_atcam_region_type region_type;
	अचिन्हित पूर्णांक blocks_count;

	/* We alपढ़ोy know the blocks count can not exceed the maximum
	 * blocks count.
	 */
	blocks_count = mlxsw_afk_key_info_blocks_count_get(region->key_info);
	अगर (blocks_count <= 2)
		region_type = MLXSW_SP_ACL_ATCAM_REGION_TYPE_2KB;
	अन्यथा अगर (blocks_count <= 4)
		region_type = MLXSW_SP_ACL_ATCAM_REGION_TYPE_4KB;
	अन्यथा अगर (blocks_count <= 8)
		region_type = MLXSW_SP_ACL_ATCAM_REGION_TYPE_8KB;
	अन्यथा
		region_type = MLXSW_SP_ACL_ATCAM_REGION_TYPE_12KB;

	aregion->type = region_type;
	aregion->ops = mlxsw_sp_acl_atcam_region_ops_arr[region_type];
पूर्ण

पूर्णांक
mlxsw_sp_acl_atcam_region_init(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_atcam *atcam,
			       काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			       काष्ठा mlxsw_sp_acl_tcam_region *region,
			       व्योम *hपूर्णांकs_priv,
			       स्थिर काष्ठा mlxsw_sp_acl_ctcam_region_ops *ops)
अणु
	पूर्णांक err;

	aregion->region = region;
	aregion->atcam = atcam;
	mlxsw_sp_acl_atcam_region_type_init(aregion);
	INIT_LIST_HEAD(&aregion->entries_list);

	err = rhashtable_init(&aregion->entries_ht,
			      &mlxsw_sp_acl_atcam_entries_ht_params);
	अगर (err)
		वापस err;
	err = aregion->ops->init(aregion);
	अगर (err)
		जाओ err_ops_init;
	err = mlxsw_sp_acl_erp_region_init(aregion, hपूर्णांकs_priv);
	अगर (err)
		जाओ err_erp_region_init;
	err = mlxsw_sp_acl_ctcam_region_init(mlxsw_sp, &aregion->cregion,
					     region, ops);
	अगर (err)
		जाओ err_ctcam_region_init;

	वापस 0;

err_ctcam_region_init:
	mlxsw_sp_acl_erp_region_fini(aregion);
err_erp_region_init:
	aregion->ops->fini(aregion);
err_ops_init:
	rhashtable_destroy(&aregion->entries_ht);
	वापस err;
पूर्ण

व्योम mlxsw_sp_acl_atcam_region_fini(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	mlxsw_sp_acl_ctcam_region_fini(&aregion->cregion);
	mlxsw_sp_acl_erp_region_fini(aregion);
	aregion->ops->fini(aregion);
	rhashtable_destroy(&aregion->entries_ht);
	WARN_ON(!list_empty(&aregion->entries_list));
पूर्ण

व्योम mlxsw_sp_acl_atcam_chunk_init(काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				   काष्ठा mlxsw_sp_acl_atcam_chunk *achunk,
				   अचिन्हित पूर्णांक priority)
अणु
	mlxsw_sp_acl_ctcam_chunk_init(&aregion->cregion, &achunk->cchunk,
				      priority);
पूर्ण

व्योम mlxsw_sp_acl_atcam_chunk_fini(काष्ठा mlxsw_sp_acl_atcam_chunk *achunk)
अणु
	mlxsw_sp_acl_ctcam_chunk_fini(&achunk->cchunk);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_atcam_region_entry_insert(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				       काष्ठा mlxsw_sp_acl_atcam_entry *aentry,
				       काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region = aregion->region;
	u8 erp_id = mlxsw_sp_acl_erp_mask_erp_id(aentry->erp_mask);
	काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id;
	अक्षर ptce3_pl[MLXSW_REG_PTCE3_LEN];
	u32 kvdl_index, priority;
	पूर्णांक err;

	err = mlxsw_sp_acl_tcam_priority_get(mlxsw_sp, rulei, &priority, true);
	अगर (err)
		वापस err;

	lkey_id = aregion->ops->lkey_id_get(aregion, aentry->enc_key, erp_id);
	अगर (IS_ERR(lkey_id))
		वापस PTR_ERR(lkey_id);
	aentry->lkey_id = lkey_id;

	kvdl_index = mlxsw_afa_block_first_kvdl_index(rulei->act_block);
	mlxsw_reg_ptce3_pack(ptce3_pl, true, MLXSW_REG_PTCE3_OP_WRITE_WRITE,
			     priority, region->tcam_region_info,
			     aentry->enc_key, erp_id,
			     aentry->delta_info.start,
			     aentry->delta_info.mask,
			     aentry->delta_info.value,
			     refcount_पढ़ो(&lkey_id->refcnt) != 1, lkey_id->id,
			     kvdl_index);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptce3), ptce3_pl);
	अगर (err)
		जाओ err_ptce3_ग_लिखो;

	वापस 0;

err_ptce3_ग_लिखो:
	aregion->ops->lkey_id_put(aregion, lkey_id);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_atcam_region_entry_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				       काष्ठा mlxsw_sp_acl_atcam_entry *aentry)
अणु
	काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id = aentry->lkey_id;
	काष्ठा mlxsw_sp_acl_tcam_region *region = aregion->region;
	u8 erp_id = mlxsw_sp_acl_erp_mask_erp_id(aentry->erp_mask);
	अक्षर ptce3_pl[MLXSW_REG_PTCE3_LEN];

	mlxsw_reg_ptce3_pack(ptce3_pl, false, MLXSW_REG_PTCE3_OP_WRITE_WRITE, 0,
			     region->tcam_region_info,
			     aentry->enc_key, erp_id,
			     aentry->delta_info.start,
			     aentry->delta_info.mask,
			     aentry->delta_info.value,
			     refcount_पढ़ो(&lkey_id->refcnt) != 1,
			     lkey_id->id, 0);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptce3), ptce3_pl);
	aregion->ops->lkey_id_put(aregion, lkey_id);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_atcam_region_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					       काष्ठा mlxsw_sp_acl_atcam_region *aregion,
					       काष्ठा mlxsw_sp_acl_atcam_entry *aentry,
					       काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp_acl_atcam_lkey_id *lkey_id = aentry->lkey_id;
	u8 erp_id = mlxsw_sp_acl_erp_mask_erp_id(aentry->erp_mask);
	काष्ठा mlxsw_sp_acl_tcam_region *region = aregion->region;
	अक्षर ptce3_pl[MLXSW_REG_PTCE3_LEN];
	u32 kvdl_index, priority;
	पूर्णांक err;

	err = mlxsw_sp_acl_tcam_priority_get(mlxsw_sp, rulei, &priority, true);
	अगर (err)
		वापस err;
	kvdl_index = mlxsw_afa_block_first_kvdl_index(rulei->act_block);
	mlxsw_reg_ptce3_pack(ptce3_pl, true, MLXSW_REG_PTCE3_OP_WRITE_UPDATE,
			     priority, region->tcam_region_info,
			     aentry->enc_key, erp_id,
			     aentry->delta_info.start,
			     aentry->delta_info.mask,
			     aentry->delta_info.value,
			     refcount_पढ़ो(&lkey_id->refcnt) != 1, lkey_id->id,
			     kvdl_index);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptce3), ptce3_pl);
पूर्ण

अटल पूर्णांक
__mlxsw_sp_acl_atcam_entry_add(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			       काष्ठा mlxsw_sp_acl_atcam_entry *aentry,
			       काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region = aregion->region;
	अक्षर mask[MLXSW_REG_PTCEX_FLEX_KEY_BLOCKS_LEN] = अणु 0 पूर्ण;
	काष्ठा mlxsw_afk *afk = mlxsw_sp_acl_afk(mlxsw_sp->acl);
	स्थिर काष्ठा mlxsw_sp_acl_erp_delta *delta;
	काष्ठा mlxsw_sp_acl_erp_mask *erp_mask;
	पूर्णांक err;

	mlxsw_afk_encode(afk, region->key_info, &rulei->values,
			 aentry->ht_key.full_enc_key, mask);

	erp_mask = mlxsw_sp_acl_erp_mask_get(aregion, mask, false);
	अगर (IS_ERR(erp_mask))
		वापस PTR_ERR(erp_mask);
	aentry->erp_mask = erp_mask;
	aentry->ht_key.erp_id = mlxsw_sp_acl_erp_mask_erp_id(erp_mask);
	स_नकल(aentry->enc_key, aentry->ht_key.full_enc_key,
	       माप(aentry->enc_key));

	/* Compute all needed delta inक्रमmation and clear the delta bits
	 * from the encrypted key.
	 */
	delta = mlxsw_sp_acl_erp_delta(aentry->erp_mask);
	aentry->delta_info.start = mlxsw_sp_acl_erp_delta_start(delta);
	aentry->delta_info.mask = mlxsw_sp_acl_erp_delta_mask(delta);
	aentry->delta_info.value =
		mlxsw_sp_acl_erp_delta_value(delta,
					     aentry->ht_key.full_enc_key);
	mlxsw_sp_acl_erp_delta_clear(delta, aentry->enc_key);

	/* Add rule to the list of A-TCAM rules, assuming this
	 * rule is पूर्णांकended to A-TCAM. In हाल this rule करोes
	 * not fit पूर्णांकo A-TCAM it will be हटाओd from the list.
	 */
	list_add(&aentry->list, &aregion->entries_list);

	/* We can't insert identical rules पूर्णांकo the A-TCAM, so fail and
	 * let the rule spill पूर्णांकo C-TCAM
	 */
	err = rhashtable_lookup_insert_fast(&aregion->entries_ht,
					    &aentry->ht_node,
					    mlxsw_sp_acl_atcam_entries_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	/* Bloom filter must be updated here, beक्रमe inserting the rule पूर्णांकo
	 * the A-TCAM.
	 */
	err = mlxsw_sp_acl_erp_bf_insert(mlxsw_sp, aregion, erp_mask, aentry);
	अगर (err)
		जाओ err_bf_insert;

	err = mlxsw_sp_acl_atcam_region_entry_insert(mlxsw_sp, aregion, aentry,
						     rulei);
	अगर (err)
		जाओ err_rule_insert;

	वापस 0;

err_rule_insert:
	mlxsw_sp_acl_erp_bf_हटाओ(mlxsw_sp, aregion, erp_mask, aentry);
err_bf_insert:
	rhashtable_हटाओ_fast(&aregion->entries_ht, &aentry->ht_node,
			       mlxsw_sp_acl_atcam_entries_ht_params);
err_rhashtable_insert:
	list_del(&aentry->list);
	mlxsw_sp_acl_erp_mask_put(aregion, erp_mask);
	वापस err;
पूर्ण

अटल व्योम
__mlxsw_sp_acl_atcam_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_atcam_region *aregion,
			       काष्ठा mlxsw_sp_acl_atcam_entry *aentry)
अणु
	mlxsw_sp_acl_atcam_region_entry_हटाओ(mlxsw_sp, aregion, aentry);
	mlxsw_sp_acl_erp_bf_हटाओ(mlxsw_sp, aregion, aentry->erp_mask, aentry);
	rhashtable_हटाओ_fast(&aregion->entries_ht, &aentry->ht_node,
			       mlxsw_sp_acl_atcam_entries_ht_params);
	list_del(&aentry->list);
	mlxsw_sp_acl_erp_mask_put(aregion, aentry->erp_mask);
पूर्ण

अटल पूर्णांक
__mlxsw_sp_acl_atcam_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_acl_atcam_region *aregion,
					  काष्ठा mlxsw_sp_acl_atcam_entry *aentry,
					  काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	वापस mlxsw_sp_acl_atcam_region_entry_action_replace(mlxsw_sp, aregion,
							      aentry, rulei);
पूर्ण

पूर्णांक mlxsw_sp_acl_atcam_entry_add(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				 काष्ठा mlxsw_sp_acl_atcam_chunk *achunk,
				 काष्ठा mlxsw_sp_acl_atcam_entry *aentry,
				 काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	पूर्णांक err;

	err = __mlxsw_sp_acl_atcam_entry_add(mlxsw_sp, aregion, aentry, rulei);
	अगर (!err)
		वापस 0;

	/* It is possible we failed to add the rule to the A-TCAM due to
	 * exceeded number of masks. Try to spill पूर्णांकo C-TCAM.
	 */
	trace_mlxsw_sp_acl_atcam_entry_add_ctcam_spill(mlxsw_sp, aregion);
	err = mlxsw_sp_acl_ctcam_entry_add(mlxsw_sp, &aregion->cregion,
					   &achunk->cchunk, &aentry->centry,
					   rulei, true);
	अगर (!err)
		वापस 0;

	वापस err;
पूर्ण

व्योम mlxsw_sp_acl_atcam_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_atcam_region *aregion,
				  काष्ठा mlxsw_sp_acl_atcam_chunk *achunk,
				  काष्ठा mlxsw_sp_acl_atcam_entry *aentry)
अणु
	अगर (mlxsw_sp_acl_atcam_is_centry(aentry))
		mlxsw_sp_acl_ctcam_entry_del(mlxsw_sp, &aregion->cregion,
					     &achunk->cchunk, &aentry->centry);
	अन्यथा
		__mlxsw_sp_acl_atcam_entry_del(mlxsw_sp, aregion, aentry);
पूर्ण

पूर्णांक
mlxsw_sp_acl_atcam_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_acl_atcam_region *aregion,
					काष्ठा mlxsw_sp_acl_atcam_entry *aentry,
					काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	पूर्णांक err;

	अगर (mlxsw_sp_acl_atcam_is_centry(aentry))
		err = mlxsw_sp_acl_ctcam_entry_action_replace(mlxsw_sp,
							      &aregion->cregion,
							      &aentry->centry,
							      rulei);
	अन्यथा
		err = __mlxsw_sp_acl_atcam_entry_action_replace(mlxsw_sp,
								aregion, aentry,
								rulei);

	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_acl_atcam_init(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_acl_atcam *atcam)
अणु
	वापस mlxsw_sp_acl_erps_init(mlxsw_sp, atcam);
पूर्ण

व्योम mlxsw_sp_acl_atcam_fini(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_acl_atcam *atcam)
अणु
	mlxsw_sp_acl_erps_fini(mlxsw_sp, atcam);
पूर्ण

व्योम *
mlxsw_sp_acl_atcam_rehash_hपूर्णांकs_get(काष्ठा mlxsw_sp_acl_atcam_region *aregion)
अणु
	वापस mlxsw_sp_acl_erp_rehash_hपूर्णांकs_get(aregion);
पूर्ण

व्योम mlxsw_sp_acl_atcam_rehash_hपूर्णांकs_put(व्योम *hपूर्णांकs_priv)
अणु
	mlxsw_sp_acl_erp_rehash_hपूर्णांकs_put(hपूर्णांकs_priv);
पूर्ण
