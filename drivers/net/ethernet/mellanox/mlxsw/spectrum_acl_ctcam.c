<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/parman.h>

#समावेश "reg.h"
#समावेश "core.h"
#समावेश "spectrum.h"
#समावेश "spectrum_acl_tcam.h"

अटल पूर्णांक
mlxsw_sp_acl_ctcam_region_resize(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_tcam_region *region,
				 u16 new_size)
अणु
	अक्षर ptar_pl[MLXSW_REG_PTAR_LEN];

	mlxsw_reg_ptar_pack(ptar_pl, MLXSW_REG_PTAR_OP_RESIZE,
			    region->key_type, new_size, region->id,
			    region->tcam_region_info);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptar), ptar_pl);
पूर्ण

अटल व्योम
mlxsw_sp_acl_ctcam_region_move(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_tcam_region *region,
			       u16 src_offset, u16 dst_offset, u16 size)
अणु
	अक्षर prcr_pl[MLXSW_REG_PRCR_LEN];

	mlxsw_reg_prcr_pack(prcr_pl, MLXSW_REG_PRCR_OP_MOVE,
			    region->tcam_region_info, src_offset,
			    region->tcam_region_info, dst_offset, size);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(prcr), prcr_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_ctcam_region_entry_insert(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
				       काष्ठा mlxsw_sp_acl_ctcam_entry *centry,
				       काष्ठा mlxsw_sp_acl_rule_info *rulei,
				       bool fillup_priority)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region = cregion->region;
	काष्ठा mlxsw_afk *afk = mlxsw_sp_acl_afk(mlxsw_sp->acl);
	अक्षर ptce2_pl[MLXSW_REG_PTCE2_LEN];
	अक्षर *act_set;
	u32 priority;
	अक्षर *mask;
	अक्षर *key;
	पूर्णांक err;

	err = mlxsw_sp_acl_tcam_priority_get(mlxsw_sp, rulei, &priority,
					     fillup_priority);
	अगर (err)
		वापस err;

	mlxsw_reg_ptce2_pack(ptce2_pl, true, MLXSW_REG_PTCE2_OP_WRITE_WRITE,
			     region->tcam_region_info,
			     centry->parman_item.index, priority);
	key = mlxsw_reg_ptce2_flex_key_blocks_data(ptce2_pl);
	mask = mlxsw_reg_ptce2_mask_data(ptce2_pl);
	mlxsw_afk_encode(afk, region->key_info, &rulei->values, key, mask);

	err = cregion->ops->entry_insert(cregion, centry, mask);
	अगर (err)
		वापस err;

	/* Only the first action set beदीर्घs here, the rest is in KVD */
	act_set = mlxsw_afa_block_first_set(rulei->act_block);
	mlxsw_reg_ptce2_flex_action_set_स_नकल_to(ptce2_pl, act_set);

	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptce2), ptce2_pl);
	अगर (err)
		जाओ err_ptce2_ग_लिखो;

	वापस 0;

err_ptce2_ग_लिखो:
	cregion->ops->entry_हटाओ(cregion, centry);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_ctcam_region_entry_हटाओ(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
				       काष्ठा mlxsw_sp_acl_ctcam_entry *centry)
अणु
	अक्षर ptce2_pl[MLXSW_REG_PTCE2_LEN];

	mlxsw_reg_ptce2_pack(ptce2_pl, false, MLXSW_REG_PTCE2_OP_WRITE_WRITE,
			     cregion->region->tcam_region_info,
			     centry->parman_item.index, 0);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptce2), ptce2_pl);
	cregion->ops->entry_हटाओ(cregion, centry);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_ctcam_region_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					       काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
					       काष्ठा mlxsw_sp_acl_ctcam_entry *centry,
					       काष्ठा mlxsw_afa_block *afa_block,
					       अचिन्हित पूर्णांक priority)
अणु
	अक्षर ptce2_pl[MLXSW_REG_PTCE2_LEN];
	अक्षर *act_set;

	mlxsw_reg_ptce2_pack(ptce2_pl, true, MLXSW_REG_PTCE2_OP_WRITE_UPDATE,
			     cregion->region->tcam_region_info,
			     centry->parman_item.index, priority);

	act_set = mlxsw_afa_block_first_set(afa_block);
	mlxsw_reg_ptce2_flex_action_set_स_नकल_to(ptce2_pl, act_set);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptce2), ptce2_pl);
पूर्ण


अटल पूर्णांक mlxsw_sp_acl_ctcam_region_parman_resize(व्योम *priv,
						   अचिन्हित दीर्घ new_count)
अणु
	काष्ठा mlxsw_sp_acl_ctcam_region *cregion = priv;
	काष्ठा mlxsw_sp_acl_tcam_region *region = cregion->region;
	काष्ठा mlxsw_sp *mlxsw_sp = region->mlxsw_sp;
	u64 max_tcam_rules;

	max_tcam_rules = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_MAX_TCAM_RULES);
	अगर (new_count > max_tcam_rules)
		वापस -EINVAL;
	वापस mlxsw_sp_acl_ctcam_region_resize(mlxsw_sp, region, new_count);
पूर्ण

अटल व्योम mlxsw_sp_acl_ctcam_region_parman_move(व्योम *priv,
						  अचिन्हित दीर्घ from_index,
						  अचिन्हित दीर्घ to_index,
						  अचिन्हित दीर्घ count)
अणु
	काष्ठा mlxsw_sp_acl_ctcam_region *cregion = priv;
	काष्ठा mlxsw_sp_acl_tcam_region *region = cregion->region;
	काष्ठा mlxsw_sp *mlxsw_sp = region->mlxsw_sp;

	mlxsw_sp_acl_ctcam_region_move(mlxsw_sp, region,
				       from_index, to_index, count);
पूर्ण

अटल स्थिर काष्ठा parman_ops mlxsw_sp_acl_ctcam_region_parman_ops = अणु
	.base_count	= MLXSW_SP_ACL_TCAM_REGION_BASE_COUNT,
	.resize_step	= MLXSW_SP_ACL_TCAM_REGION_RESIZE_STEP,
	.resize		= mlxsw_sp_acl_ctcam_region_parman_resize,
	.move		= mlxsw_sp_acl_ctcam_region_parman_move,
	.algo		= PARMAN_ALGO_TYPE_LSORT,
पूर्ण;

पूर्णांक
mlxsw_sp_acl_ctcam_region_init(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
			       काष्ठा mlxsw_sp_acl_tcam_region *region,
			       स्थिर काष्ठा mlxsw_sp_acl_ctcam_region_ops *ops)
अणु
	cregion->region = region;
	cregion->ops = ops;
	cregion->parman = parman_create(&mlxsw_sp_acl_ctcam_region_parman_ops,
					cregion);
	अगर (!cregion->parman)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम mlxsw_sp_acl_ctcam_region_fini(काष्ठा mlxsw_sp_acl_ctcam_region *cregion)
अणु
	parman_destroy(cregion->parman);
पूर्ण

व्योम mlxsw_sp_acl_ctcam_chunk_init(काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
				   काष्ठा mlxsw_sp_acl_ctcam_chunk *cchunk,
				   अचिन्हित पूर्णांक priority)
अणु
	parman_prio_init(cregion->parman, &cchunk->parman_prio, priority);
पूर्ण

व्योम mlxsw_sp_acl_ctcam_chunk_fini(काष्ठा mlxsw_sp_acl_ctcam_chunk *cchunk)
अणु
	parman_prio_fini(&cchunk->parman_prio);
पूर्ण

पूर्णांक mlxsw_sp_acl_ctcam_entry_add(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
				 काष्ठा mlxsw_sp_acl_ctcam_chunk *cchunk,
				 काष्ठा mlxsw_sp_acl_ctcam_entry *centry,
				 काष्ठा mlxsw_sp_acl_rule_info *rulei,
				 bool fillup_priority)
अणु
	पूर्णांक err;

	err = parman_item_add(cregion->parman, &cchunk->parman_prio,
			      &centry->parman_item);
	अगर (err)
		वापस err;

	err = mlxsw_sp_acl_ctcam_region_entry_insert(mlxsw_sp, cregion, centry,
						     rulei, fillup_priority);
	अगर (err)
		जाओ err_rule_insert;
	वापस 0;

err_rule_insert:
	parman_item_हटाओ(cregion->parman, &cchunk->parman_prio,
			   &centry->parman_item);
	वापस err;
पूर्ण

व्योम mlxsw_sp_acl_ctcam_entry_del(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
				  काष्ठा mlxsw_sp_acl_ctcam_chunk *cchunk,
				  काष्ठा mlxsw_sp_acl_ctcam_entry *centry)
अणु
	mlxsw_sp_acl_ctcam_region_entry_हटाओ(mlxsw_sp, cregion, centry);
	parman_item_हटाओ(cregion->parman, &cchunk->parman_prio,
			   &centry->parman_item);
पूर्ण

पूर्णांक mlxsw_sp_acl_ctcam_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					    काष्ठा mlxsw_sp_acl_ctcam_region *cregion,
					    काष्ठा mlxsw_sp_acl_ctcam_entry *centry,
					    काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	वापस mlxsw_sp_acl_ctcam_region_entry_action_replace(mlxsw_sp, cregion,
							      centry,
							      rulei->act_block,
							      rulei->priority);
पूर्ण
