<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश "reg.h"
#समावेश "core.h"
#समावेश "spectrum.h"
#समावेश "spectrum_acl_tcam.h"

काष्ठा mlxsw_sp1_acl_tcam_region अणु
	काष्ठा mlxsw_sp_acl_ctcam_region cregion;
	काष्ठा mlxsw_sp_acl_tcam_region *region;
	काष्ठा अणु
		काष्ठा mlxsw_sp_acl_ctcam_chunk cchunk;
		काष्ठा mlxsw_sp_acl_ctcam_entry centry;
		काष्ठा mlxsw_sp_acl_rule_info *rulei;
	पूर्ण catchall;
पूर्ण;

काष्ठा mlxsw_sp1_acl_tcam_chunk अणु
	काष्ठा mlxsw_sp_acl_ctcam_chunk cchunk;
पूर्ण;

काष्ठा mlxsw_sp1_acl_tcam_entry अणु
	काष्ठा mlxsw_sp_acl_ctcam_entry centry;
पूर्ण;

अटल पूर्णांक
mlxsw_sp1_acl_ctcam_region_entry_insert(काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
					काष्ठा mlxsw_sp_acl_ctcam_entry *centry,
					स्थिर अक्षर *mask)
अणु
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp1_acl_ctcam_region_entry_हटाओ(काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
					काष्ठा mlxsw_sp_acl_ctcam_entry *centry)
अणु
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_acl_ctcam_region_ops
mlxsw_sp1_acl_ctcam_region_ops = अणु
	.entry_insert = mlxsw_sp1_acl_ctcam_region_entry_insert,
	.entry_हटाओ = mlxsw_sp1_acl_ctcam_region_entry_हटाओ,
पूर्ण;

अटल पूर्णांक mlxsw_sp1_acl_tcam_init(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
				   काष्ठा mlxsw_sp_acl_tcam *tcam)
अणु
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp1_acl_tcam_fini(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
पूर्ण

अटल पूर्णांक
mlxsw_sp1_acl_ctcam_region_catchall_add(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp1_acl_tcam_region *region)
अणु
	काष्ठा mlxsw_sp_acl_rule_info *rulei;
	पूर्णांक err;

	mlxsw_sp_acl_ctcam_chunk_init(&region->cregion,
				      &region->catchall.cchunk,
				      MLXSW_SP_ACL_TCAM_CATCHALL_PRIO);
	rulei = mlxsw_sp_acl_rulei_create(mlxsw_sp->acl, शून्य);
	अगर (IS_ERR(rulei)) अणु
		err = PTR_ERR(rulei);
		जाओ err_rulei_create;
	पूर्ण
	err = mlxsw_sp_acl_rulei_act_जारी(rulei);
	अगर (WARN_ON(err))
		जाओ err_rulei_act_जारी;
	err = mlxsw_sp_acl_rulei_commit(rulei);
	अगर (err)
		जाओ err_rulei_commit;
	err = mlxsw_sp_acl_ctcam_entry_add(mlxsw_sp, &region->cregion,
					   &region->catchall.cchunk,
					   &region->catchall.centry,
					   rulei, false);
	अगर (err)
		जाओ err_entry_add;
	region->catchall.rulei = rulei;
	वापस 0;

err_entry_add:
err_rulei_commit:
err_rulei_act_जारी:
	mlxsw_sp_acl_rulei_destroy(rulei);
err_rulei_create:
	mlxsw_sp_acl_ctcam_chunk_fini(&region->catchall.cchunk);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp1_acl_ctcam_region_catchall_del(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp1_acl_tcam_region *region)
अणु
	काष्ठा mlxsw_sp_acl_rule_info *rulei = region->catchall.rulei;

	mlxsw_sp_acl_ctcam_entry_del(mlxsw_sp, &region->cregion,
				     &region->catchall.cchunk,
				     &region->catchall.centry);
	mlxsw_sp_acl_rulei_destroy(rulei);
	mlxsw_sp_acl_ctcam_chunk_fini(&region->catchall.cchunk);
पूर्ण

अटल पूर्णांक
mlxsw_sp1_acl_tcam_region_init(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *region_priv,
			       व्योम *tcam_priv,
			       काष्ठा mlxsw_sp_acl_tcam_region *_region,
			       व्योम *hपूर्णांकs_priv)
अणु
	काष्ठा mlxsw_sp1_acl_tcam_region *region = region_priv;
	पूर्णांक err;

	err = mlxsw_sp_acl_ctcam_region_init(mlxsw_sp, &region->cregion,
					     _region,
					     &mlxsw_sp1_acl_ctcam_region_ops);
	अगर (err)
		वापस err;
	err = mlxsw_sp1_acl_ctcam_region_catchall_add(mlxsw_sp, region);
	अगर (err)
		जाओ err_catchall_add;
	region->region = _region;
	वापस 0;

err_catchall_add:
	mlxsw_sp_acl_ctcam_region_fini(&region->cregion);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp1_acl_tcam_region_fini(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *region_priv)
अणु
	काष्ठा mlxsw_sp1_acl_tcam_region *region = region_priv;

	mlxsw_sp1_acl_ctcam_region_catchall_del(mlxsw_sp, region);
	mlxsw_sp_acl_ctcam_region_fini(&region->cregion);
पूर्ण

अटल पूर्णांक
mlxsw_sp1_acl_tcam_region_associate(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_acl_tcam_region *region)
अणु
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp1_acl_tcam_chunk_init(व्योम *region_priv, व्योम *chunk_priv,
					  अचिन्हित पूर्णांक priority)
अणु
	काष्ठा mlxsw_sp1_acl_tcam_region *region = region_priv;
	काष्ठा mlxsw_sp1_acl_tcam_chunk *chunk = chunk_priv;

	mlxsw_sp_acl_ctcam_chunk_init(&region->cregion, &chunk->cchunk,
				      priority);
पूर्ण

अटल व्योम mlxsw_sp1_acl_tcam_chunk_fini(व्योम *chunk_priv)
अणु
	काष्ठा mlxsw_sp1_acl_tcam_chunk *chunk = chunk_priv;

	mlxsw_sp_acl_ctcam_chunk_fini(&chunk->cchunk);
पूर्ण

अटल पूर्णांक mlxsw_sp1_acl_tcam_entry_add(काष्ठा mlxsw_sp *mlxsw_sp,
					व्योम *region_priv, व्योम *chunk_priv,
					व्योम *entry_priv,
					काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp1_acl_tcam_region *region = region_priv;
	काष्ठा mlxsw_sp1_acl_tcam_chunk *chunk = chunk_priv;
	काष्ठा mlxsw_sp1_acl_tcam_entry *entry = entry_priv;

	वापस mlxsw_sp_acl_ctcam_entry_add(mlxsw_sp, &region->cregion,
					    &chunk->cchunk, &entry->centry,
					    rulei, false);
पूर्ण

अटल व्योम mlxsw_sp1_acl_tcam_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
					 व्योम *region_priv, व्योम *chunk_priv,
					 व्योम *entry_priv)
अणु
	काष्ठा mlxsw_sp1_acl_tcam_region *region = region_priv;
	काष्ठा mlxsw_sp1_acl_tcam_chunk *chunk = chunk_priv;
	काष्ठा mlxsw_sp1_acl_tcam_entry *entry = entry_priv;

	mlxsw_sp_acl_ctcam_entry_del(mlxsw_sp, &region->cregion,
				     &chunk->cchunk, &entry->centry);
पूर्ण

अटल पूर्णांक
mlxsw_sp1_acl_tcam_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					व्योम *region_priv, व्योम *entry_priv,
					काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_acl_tcam_region_entry_activity_get(काष्ठा mlxsw_sp *mlxsw_sp,
					     काष्ठा mlxsw_sp_acl_tcam_region *_region,
					     अचिन्हित पूर्णांक offset,
					     bool *activity)
अणु
	अक्षर ptce2_pl[MLXSW_REG_PTCE2_LEN];
	पूर्णांक err;

	mlxsw_reg_ptce2_pack(ptce2_pl, true, MLXSW_REG_PTCE2_OP_QUERY_CLEAR_ON_READ,
			     _region->tcam_region_info, offset, 0);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ptce2), ptce2_pl);
	अगर (err)
		वापस err;
	*activity = mlxsw_reg_ptce2_a_get(ptce2_pl);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp1_acl_tcam_entry_activity_get(काष्ठा mlxsw_sp *mlxsw_sp,
				      व्योम *region_priv, व्योम *entry_priv,
				      bool *activity)
अणु
	काष्ठा mlxsw_sp1_acl_tcam_region *region = region_priv;
	काष्ठा mlxsw_sp1_acl_tcam_entry *entry = entry_priv;
	अचिन्हित पूर्णांक offset;

	offset = mlxsw_sp_acl_ctcam_entry_offset(&entry->centry);
	वापस mlxsw_sp1_acl_tcam_region_entry_activity_get(mlxsw_sp,
							    region->region,
							    offset, activity);
पूर्ण

स्थिर काष्ठा mlxsw_sp_acl_tcam_ops mlxsw_sp1_acl_tcam_ops = अणु
	.key_type		= MLXSW_REG_PTAR_KEY_TYPE_FLEX,
	.priv_size		= 0,
	.init			= mlxsw_sp1_acl_tcam_init,
	.fini			= mlxsw_sp1_acl_tcam_fini,
	.region_priv_size	= माप(काष्ठा mlxsw_sp1_acl_tcam_region),
	.region_init		= mlxsw_sp1_acl_tcam_region_init,
	.region_fini		= mlxsw_sp1_acl_tcam_region_fini,
	.region_associate	= mlxsw_sp1_acl_tcam_region_associate,
	.chunk_priv_size	= माप(काष्ठा mlxsw_sp1_acl_tcam_chunk),
	.chunk_init		= mlxsw_sp1_acl_tcam_chunk_init,
	.chunk_fini		= mlxsw_sp1_acl_tcam_chunk_fini,
	.entry_priv_size	= माप(काष्ठा mlxsw_sp1_acl_tcam_entry),
	.entry_add		= mlxsw_sp1_acl_tcam_entry_add,
	.entry_del		= mlxsw_sp1_acl_tcam_entry_del,
	.entry_action_replace	= mlxsw_sp1_acl_tcam_entry_action_replace,
	.entry_activity_get	= mlxsw_sp1_acl_tcam_entry_activity_get,
पूर्ण;
