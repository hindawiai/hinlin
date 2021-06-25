<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>

#समावेश "spectrum.h"
#समावेश "spectrum_acl_tcam.h"
#समावेश "core_acl_flex_actions.h"

काष्ठा mlxsw_sp2_acl_tcam अणु
	काष्ठा mlxsw_sp_acl_atcam atcam;
	u32 kvdl_index;
	अचिन्हित पूर्णांक kvdl_count;
पूर्ण;

काष्ठा mlxsw_sp2_acl_tcam_region अणु
	काष्ठा mlxsw_sp_acl_atcam_region aregion;
	काष्ठा mlxsw_sp_acl_tcam_region *region;
पूर्ण;

काष्ठा mlxsw_sp2_acl_tcam_chunk अणु
	काष्ठा mlxsw_sp_acl_atcam_chunk achunk;
पूर्ण;

काष्ठा mlxsw_sp2_acl_tcam_entry अणु
	काष्ठा mlxsw_sp_acl_atcam_entry aentry;
	काष्ठा mlxsw_afa_block *act_block;
पूर्ण;

अटल पूर्णांक
mlxsw_sp2_acl_ctcam_region_entry_insert(काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
					काष्ठा mlxsw_sp_acl_ctcam_entry *centry,
					स्थिर अक्षर *mask)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region *aregion;
	काष्ठा mlxsw_sp_acl_atcam_entry *aentry;
	काष्ठा mlxsw_sp_acl_erp_mask *erp_mask;

	aregion = mlxsw_sp_acl_tcam_cregion_aregion(cregion);
	aentry = mlxsw_sp_acl_tcam_centry_aentry(centry);

	erp_mask = mlxsw_sp_acl_erp_mask_get(aregion, mask, true);
	अगर (IS_ERR(erp_mask))
		वापस PTR_ERR(erp_mask);
	aentry->erp_mask = erp_mask;

	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp2_acl_ctcam_region_entry_हटाओ(काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
					काष्ठा mlxsw_sp_acl_ctcam_entry *centry)
अणु
	काष्ठा mlxsw_sp_acl_atcam_region *aregion;
	काष्ठा mlxsw_sp_acl_atcam_entry *aentry;

	aregion = mlxsw_sp_acl_tcam_cregion_aregion(cregion);
	aentry = mlxsw_sp_acl_tcam_centry_aentry(centry);

	mlxsw_sp_acl_erp_mask_put(aregion, aentry->erp_mask);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_acl_ctcam_region_ops
mlxsw_sp2_acl_ctcam_region_ops = अणु
	.entry_insert = mlxsw_sp2_acl_ctcam_region_entry_insert,
	.entry_हटाओ = mlxsw_sp2_acl_ctcam_region_entry_हटाओ,
पूर्ण;

अटल पूर्णांक mlxsw_sp2_acl_tcam_init(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
				   काष्ठा mlxsw_sp_acl_tcam *_tcam)
अणु
	काष्ठा mlxsw_sp2_acl_tcam *tcam = priv;
	काष्ठा mlxsw_afa_block *afa_block;
	अक्षर pefa_pl[MLXSW_REG_PEFA_LEN];
	अक्षर pgcr_pl[MLXSW_REG_PGCR_LEN];
	अक्षर *enc_actions;
	पूर्णांक i;
	पूर्णांक err;

	tcam->kvdl_count = _tcam->max_regions;
	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
				  tcam->kvdl_count, &tcam->kvdl_index);
	अगर (err)
		वापस err;

	/* Create flex action block, set शेष action (जारी)
	 * but करोn't commit. We need just the current set encoding
	 * to be written using PEFA रेजिस्टर to all indexes क्रम all regions.
	 */
	afa_block = mlxsw_afa_block_create(mlxsw_sp->afa);
	अगर (IS_ERR(afa_block)) अणु
		err = PTR_ERR(afa_block);
		जाओ err_afa_block;
	पूर्ण
	err = mlxsw_afa_block_जारी(afa_block);
	अगर (WARN_ON(err))
		जाओ err_afa_block_जारी;
	enc_actions = mlxsw_afa_block_cur_set(afa_block);

	क्रम (i = 0; i < tcam->kvdl_count; i++) अणु
		mlxsw_reg_pefa_pack(pefa_pl, tcam->kvdl_index + i,
				    true, enc_actions);
		err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pefa), pefa_pl);
		अगर (err)
			जाओ err_pefa_ग_लिखो;
	पूर्ण
	mlxsw_reg_pgcr_pack(pgcr_pl, tcam->kvdl_index);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pgcr), pgcr_pl);
	अगर (err)
		जाओ err_pgcr_ग_लिखो;

	err = mlxsw_sp_acl_atcam_init(mlxsw_sp, &tcam->atcam);
	अगर (err)
		जाओ err_atcam_init;

	mlxsw_afa_block_destroy(afa_block);
	वापस 0;

err_atcam_init:
err_pgcr_ग_लिखो:
err_pefa_ग_लिखो:
err_afa_block_जारी:
	mlxsw_afa_block_destroy(afa_block);
err_afa_block:
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
			   tcam->kvdl_count, tcam->kvdl_index);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp2_acl_tcam_fini(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
	काष्ठा mlxsw_sp2_acl_tcam *tcam = priv;

	mlxsw_sp_acl_atcam_fini(mlxsw_sp, &tcam->atcam);
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_ACTSET,
			   tcam->kvdl_count, tcam->kvdl_index);
पूर्ण

अटल पूर्णांक
mlxsw_sp2_acl_tcam_region_init(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *region_priv,
			       व्योम *tcam_priv,
			       काष्ठा mlxsw_sp_acl_tcam_region *_region,
			       व्योम *hपूर्णांकs_priv)
अणु
	काष्ठा mlxsw_sp2_acl_tcam_region *region = region_priv;
	काष्ठा mlxsw_sp2_acl_tcam *tcam = tcam_priv;

	region->region = _region;

	वापस mlxsw_sp_acl_atcam_region_init(mlxsw_sp, &tcam->atcam,
					      &region->aregion,
					      _region, hपूर्णांकs_priv,
					      &mlxsw_sp2_acl_ctcam_region_ops);
पूर्ण

अटल व्योम
mlxsw_sp2_acl_tcam_region_fini(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *region_priv)
अणु
	काष्ठा mlxsw_sp2_acl_tcam_region *region = region_priv;

	mlxsw_sp_acl_atcam_region_fini(&region->aregion);
पूर्ण

अटल पूर्णांक
mlxsw_sp2_acl_tcam_region_associate(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_acl_tcam_region *region)
अणु
	वापस mlxsw_sp_acl_atcam_region_associate(mlxsw_sp, region->id);
पूर्ण

अटल व्योम *mlxsw_sp2_acl_tcam_region_rehash_hपूर्णांकs_get(व्योम *region_priv)
अणु
	काष्ठा mlxsw_sp2_acl_tcam_region *region = region_priv;

	वापस mlxsw_sp_acl_atcam_rehash_hपूर्णांकs_get(&region->aregion);
पूर्ण

अटल व्योम mlxsw_sp2_acl_tcam_region_rehash_hपूर्णांकs_put(व्योम *hपूर्णांकs_priv)
अणु
	mlxsw_sp_acl_atcam_rehash_hपूर्णांकs_put(hपूर्णांकs_priv);
पूर्ण

अटल व्योम mlxsw_sp2_acl_tcam_chunk_init(व्योम *region_priv, व्योम *chunk_priv,
					  अचिन्हित पूर्णांक priority)
अणु
	काष्ठा mlxsw_sp2_acl_tcam_region *region = region_priv;
	काष्ठा mlxsw_sp2_acl_tcam_chunk *chunk = chunk_priv;

	mlxsw_sp_acl_atcam_chunk_init(&region->aregion, &chunk->achunk,
				      priority);
पूर्ण

अटल व्योम mlxsw_sp2_acl_tcam_chunk_fini(व्योम *chunk_priv)
अणु
	काष्ठा mlxsw_sp2_acl_tcam_chunk *chunk = chunk_priv;

	mlxsw_sp_acl_atcam_chunk_fini(&chunk->achunk);
पूर्ण

अटल पूर्णांक mlxsw_sp2_acl_tcam_entry_add(काष्ठा mlxsw_sp *mlxsw_sp,
					व्योम *region_priv, व्योम *chunk_priv,
					व्योम *entry_priv,
					काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp2_acl_tcam_region *region = region_priv;
	काष्ठा mlxsw_sp2_acl_tcam_chunk *chunk = chunk_priv;
	काष्ठा mlxsw_sp2_acl_tcam_entry *entry = entry_priv;

	entry->act_block = rulei->act_block;
	वापस mlxsw_sp_acl_atcam_entry_add(mlxsw_sp, &region->aregion,
					    &chunk->achunk, &entry->aentry,
					    rulei);
पूर्ण

अटल व्योम mlxsw_sp2_acl_tcam_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
					 व्योम *region_priv, व्योम *chunk_priv,
					 व्योम *entry_priv)
अणु
	काष्ठा mlxsw_sp2_acl_tcam_region *region = region_priv;
	काष्ठा mlxsw_sp2_acl_tcam_chunk *chunk = chunk_priv;
	काष्ठा mlxsw_sp2_acl_tcam_entry *entry = entry_priv;

	mlxsw_sp_acl_atcam_entry_del(mlxsw_sp, &region->aregion, &chunk->achunk,
				     &entry->aentry);
पूर्ण

अटल पूर्णांक
mlxsw_sp2_acl_tcam_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					व्योम *region_priv, व्योम *entry_priv,
					काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp2_acl_tcam_region *region = region_priv;
	काष्ठा mlxsw_sp2_acl_tcam_entry *entry = entry_priv;

	entry->act_block = rulei->act_block;
	वापस mlxsw_sp_acl_atcam_entry_action_replace(mlxsw_sp,
						       &region->aregion,
						       &entry->aentry, rulei);
पूर्ण

अटल पूर्णांक
mlxsw_sp2_acl_tcam_entry_activity_get(काष्ठा mlxsw_sp *mlxsw_sp,
				      व्योम *region_priv, व्योम *entry_priv,
				      bool *activity)
अणु
	काष्ठा mlxsw_sp2_acl_tcam_entry *entry = entry_priv;

	वापस mlxsw_afa_block_activity_get(entry->act_block, activity);
पूर्ण

स्थिर काष्ठा mlxsw_sp_acl_tcam_ops mlxsw_sp2_acl_tcam_ops = अणु
	.key_type		= MLXSW_REG_PTAR_KEY_TYPE_FLEX2,
	.priv_size		= माप(काष्ठा mlxsw_sp2_acl_tcam),
	.init			= mlxsw_sp2_acl_tcam_init,
	.fini			= mlxsw_sp2_acl_tcam_fini,
	.region_priv_size	= माप(काष्ठा mlxsw_sp2_acl_tcam_region),
	.region_init		= mlxsw_sp2_acl_tcam_region_init,
	.region_fini		= mlxsw_sp2_acl_tcam_region_fini,
	.region_associate	= mlxsw_sp2_acl_tcam_region_associate,
	.region_rehash_hपूर्णांकs_get = mlxsw_sp2_acl_tcam_region_rehash_hपूर्णांकs_get,
	.region_rehash_hपूर्णांकs_put = mlxsw_sp2_acl_tcam_region_rehash_hपूर्णांकs_put,
	.chunk_priv_size	= माप(काष्ठा mlxsw_sp2_acl_tcam_chunk),
	.chunk_init		= mlxsw_sp2_acl_tcam_chunk_init,
	.chunk_fini		= mlxsw_sp2_acl_tcam_chunk_fini,
	.entry_priv_size	= माप(काष्ठा mlxsw_sp2_acl_tcam_entry),
	.entry_add		= mlxsw_sp2_acl_tcam_entry_add,
	.entry_del		= mlxsw_sp2_acl_tcam_entry_del,
	.entry_action_replace	= mlxsw_sp2_acl_tcam_entry_action_replace,
	.entry_activity_get	= mlxsw_sp2_acl_tcam_entry_activity_get,
पूर्ण;
