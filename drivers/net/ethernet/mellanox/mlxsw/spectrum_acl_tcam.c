<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bitops.h>
#समावेश <linux/list.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mutex.h>
#समावेश <trace/events/mlxsw.h>

#समावेश "reg.h"
#समावेश "core.h"
#समावेश "resources.h"
#समावेश "spectrum.h"
#समावेश "spectrum_acl_tcam.h"
#समावेश "core_acl_flex_keys.h"

माप_प्रकार mlxsw_sp_acl_tcam_priv_size(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	वापस ops->priv_size;
पूर्ण

#घोषणा MLXSW_SP_ACL_TCAM_VREGION_REHASH_INTRVL_DFLT 5000 /* ms */
#घोषणा MLXSW_SP_ACL_TCAM_VREGION_REHASH_INTRVL_MIN 3000 /* ms */
#घोषणा MLXSW_SP_ACL_TCAM_VREGION_REHASH_CREDITS 100 /* number of entries */

पूर्णांक mlxsw_sp_acl_tcam_init(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_acl_tcam *tcam)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	u64 max_tcam_regions;
	u64 max_regions;
	u64 max_groups;
	माप_प्रकार alloc_size;
	पूर्णांक err;

	mutex_init(&tcam->lock);
	tcam->vregion_rehash_पूर्णांकrvl =
			MLXSW_SP_ACL_TCAM_VREGION_REHASH_INTRVL_DFLT;
	INIT_LIST_HEAD(&tcam->vregion_list);

	max_tcam_regions = MLXSW_CORE_RES_GET(mlxsw_sp->core,
					      ACL_MAX_TCAM_REGIONS);
	max_regions = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_MAX_REGIONS);

	/* Use 1:1 mapping between ACL region and TCAM region */
	अगर (max_tcam_regions < max_regions)
		max_regions = max_tcam_regions;

	alloc_size = माप(tcam->used_regions[0]) * BITS_TO_LONGS(max_regions);
	tcam->used_regions = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!tcam->used_regions)
		वापस -ENOMEM;
	tcam->max_regions = max_regions;

	max_groups = MLXSW_CORE_RES_GET(mlxsw_sp->core, ACL_MAX_GROUPS);
	alloc_size = माप(tcam->used_groups[0]) * BITS_TO_LONGS(max_groups);
	tcam->used_groups = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!tcam->used_groups) अणु
		err = -ENOMEM;
		जाओ err_alloc_used_groups;
	पूर्ण
	tcam->max_groups = max_groups;
	tcam->max_group_size = MLXSW_CORE_RES_GET(mlxsw_sp->core,
						 ACL_MAX_GROUP_SIZE);

	err = ops->init(mlxsw_sp, tcam->priv, tcam);
	अगर (err)
		जाओ err_tcam_init;

	वापस 0;

err_tcam_init:
	kमुक्त(tcam->used_groups);
err_alloc_used_groups:
	kमुक्त(tcam->used_regions);
	वापस err;
पूर्ण

व्योम mlxsw_sp_acl_tcam_fini(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_acl_tcam *tcam)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	mutex_destroy(&tcam->lock);
	ops->fini(mlxsw_sp, tcam->priv);
	kमुक्त(tcam->used_groups);
	kमुक्त(tcam->used_regions);
पूर्ण

पूर्णांक mlxsw_sp_acl_tcam_priority_get(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_acl_rule_info *rulei,
				   u32 *priority, bool fillup_priority)
अणु
	u64 max_priority;

	अगर (!fillup_priority) अणु
		*priority = 0;
		वापस 0;
	पूर्ण

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, KVD_SIZE))
		वापस -EIO;

	/* Priority range is 1..cap_kvd_size-1. */
	max_priority = MLXSW_CORE_RES_GET(mlxsw_sp->core, KVD_SIZE) - 1;
	अगर (rulei->priority >= max_priority)
		वापस -EINVAL;

	/* Unlike in TC, in HW, higher number means higher priority. */
	*priority = max_priority - rulei->priority;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_tcam_region_id_get(काष्ठा mlxsw_sp_acl_tcam *tcam,
					   u16 *p_id)
अणु
	u16 id;

	id = find_first_zero_bit(tcam->used_regions, tcam->max_regions);
	अगर (id < tcam->max_regions) अणु
		__set_bit(id, tcam->used_regions);
		*p_id = id;
		वापस 0;
	पूर्ण
	वापस -ENOBUFS;
पूर्ण

अटल व्योम mlxsw_sp_acl_tcam_region_id_put(काष्ठा mlxsw_sp_acl_tcam *tcam,
					    u16 id)
अणु
	__clear_bit(id, tcam->used_regions);
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_tcam_group_id_get(काष्ठा mlxsw_sp_acl_tcam *tcam,
					  u16 *p_id)
अणु
	u16 id;

	id = find_first_zero_bit(tcam->used_groups, tcam->max_groups);
	अगर (id < tcam->max_groups) अणु
		__set_bit(id, tcam->used_groups);
		*p_id = id;
		वापस 0;
	पूर्ण
	वापस -ENOBUFS;
पूर्ण

अटल व्योम mlxsw_sp_acl_tcam_group_id_put(काष्ठा mlxsw_sp_acl_tcam *tcam,
					   u16 id)
अणु
	__clear_bit(id, tcam->used_groups);
पूर्ण

काष्ठा mlxsw_sp_acl_tcam_pattern अणु
	स्थिर क्रमागत mlxsw_afk_element *elements;
	अचिन्हित पूर्णांक elements_count;
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_group अणु
	काष्ठा mlxsw_sp_acl_tcam *tcam;
	u16 id;
	काष्ठा mutex lock; /* guards region list updates */
	काष्ठा list_head region_list;
	अचिन्हित पूर्णांक region_count;
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_vgroup अणु
	काष्ठा mlxsw_sp_acl_tcam_group group;
	काष्ठा list_head vregion_list;
	काष्ठा rhashtable vchunk_ht;
	स्थिर काष्ठा mlxsw_sp_acl_tcam_pattern *patterns;
	अचिन्हित पूर्णांक patterns_count;
	bool पंचांगplt_elusage_set;
	काष्ठा mlxsw_afk_element_usage पंचांगplt_elusage;
	bool vregion_rehash_enabled;
	अचिन्हित पूर्णांक *p_min_prio;
	अचिन्हित पूर्णांक *p_max_prio;
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_rehash_ctx अणु
	व्योम *hपूर्णांकs_priv;
	bool this_is_rollback;
	काष्ठा mlxsw_sp_acl_tcam_vchunk *current_vchunk; /* vchunk being
							  * currently migrated.
							  */
	काष्ठा mlxsw_sp_acl_tcam_ventry *start_ventry; /* ventry to start
							* migration from in
							* a vchunk being
							* currently migrated.
							*/
	काष्ठा mlxsw_sp_acl_tcam_ventry *stop_ventry; /* ventry to stop
						       * migration at
						       * a vchunk being
						       * currently migrated.
						       */
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_vregion अणु
	काष्ठा mutex lock; /* Protects consistency of region, region2 poपूर्णांकers
			    * and vchunk_list.
			    */
	काष्ठा mlxsw_sp_acl_tcam_region *region;
	काष्ठा mlxsw_sp_acl_tcam_region *region2; /* Used during migration */
	काष्ठा list_head list; /* Member of a TCAM group */
	काष्ठा list_head tlist; /* Member of a TCAM */
	काष्ठा list_head vchunk_list; /* List of vchunks under this vregion */
	काष्ठा mlxsw_afk_key_info *key_info;
	काष्ठा mlxsw_sp_acl_tcam *tcam;
	काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup;
	काष्ठा अणु
		काष्ठा delayed_work dw;
		काष्ठा mlxsw_sp_acl_tcam_rehash_ctx ctx;
	पूर्ण rehash;
	काष्ठा mlxsw_sp *mlxsw_sp;
	अचिन्हित पूर्णांक ref_count;
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_vchunk;

काष्ठा mlxsw_sp_acl_tcam_chunk अणु
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk;
	काष्ठा mlxsw_sp_acl_tcam_region *region;
	अचिन्हित दीर्घ priv[];
	/* priv has to be always the last item */
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_vchunk अणु
	काष्ठा mlxsw_sp_acl_tcam_chunk *chunk;
	काष्ठा mlxsw_sp_acl_tcam_chunk *chunk2; /* Used during migration */
	काष्ठा list_head list; /* Member of a TCAM vregion */
	काष्ठा rhash_head ht_node; /* Member of a chunk HT */
	काष्ठा list_head ventry_list;
	अचिन्हित पूर्णांक priority; /* Priority within the vregion and group */
	काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup;
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion;
	अचिन्हित पूर्णांक ref_count;
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_entry अणु
	काष्ठा mlxsw_sp_acl_tcam_ventry *ventry;
	काष्ठा mlxsw_sp_acl_tcam_chunk *chunk;
	अचिन्हित दीर्घ priv[];
	/* priv has to be always the last item */
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_ventry अणु
	काष्ठा mlxsw_sp_acl_tcam_entry *entry;
	काष्ठा list_head list; /* Member of a TCAM vchunk */
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk;
	काष्ठा mlxsw_sp_acl_rule_info *rulei;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_acl_tcam_vchunk_ht_params = अणु
	.key_len = माप(अचिन्हित पूर्णांक),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_acl_tcam_vchunk, priority),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_acl_tcam_vchunk, ht_node),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल पूर्णांक mlxsw_sp_acl_tcam_group_update(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_acl_tcam_group *group)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region;
	अक्षर pagt_pl[MLXSW_REG_PAGT_LEN];
	पूर्णांक acl_index = 0;

	mlxsw_reg_pagt_pack(pagt_pl, group->id);
	list_क्रम_each_entry(region, &group->region_list, list) अणु
		bool multi = false;

		/* Check अगर the next entry in the list has the same vregion. */
		अगर (region->list.next != &group->region_list &&
		    list_next_entry(region, list)->vregion == region->vregion)
			multi = true;
		mlxsw_reg_pagt_acl_id_pack(pagt_pl, acl_index++,
					   region->id, multi);
	पूर्ण
	mlxsw_reg_pagt_size_set(pagt_pl, acl_index);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pagt), pagt_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_group_add(काष्ठा mlxsw_sp_acl_tcam *tcam,
			    काष्ठा mlxsw_sp_acl_tcam_group *group)
अणु
	पूर्णांक err;

	group->tcam = tcam;
	INIT_LIST_HEAD(&group->region_list);

	err = mlxsw_sp_acl_tcam_group_id_get(tcam, &group->id);
	अगर (err)
		वापस err;

	mutex_init(&group->lock);

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_acl_tcam_group_del(काष्ठा mlxsw_sp_acl_tcam_group *group)
अणु
	काष्ठा mlxsw_sp_acl_tcam *tcam = group->tcam;

	mutex_destroy(&group->lock);
	mlxsw_sp_acl_tcam_group_id_put(tcam, group->id);
	WARN_ON(!list_empty(&group->region_list));
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_vgroup_add(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_acl_tcam *tcam,
			     काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup,
			     स्थिर काष्ठा mlxsw_sp_acl_tcam_pattern *patterns,
			     अचिन्हित पूर्णांक patterns_count,
			     काष्ठा mlxsw_afk_element_usage *पंचांगplt_elusage,
			     bool vregion_rehash_enabled,
			     अचिन्हित पूर्णांक *p_min_prio,
			     अचिन्हित पूर्णांक *p_max_prio)
अणु
	पूर्णांक err;

	vgroup->patterns = patterns;
	vgroup->patterns_count = patterns_count;
	vgroup->vregion_rehash_enabled = vregion_rehash_enabled;
	vgroup->p_min_prio = p_min_prio;
	vgroup->p_max_prio = p_max_prio;

	अगर (पंचांगplt_elusage) अणु
		vgroup->पंचांगplt_elusage_set = true;
		स_नकल(&vgroup->पंचांगplt_elusage, पंचांगplt_elusage,
		       माप(vgroup->पंचांगplt_elusage));
	पूर्ण
	INIT_LIST_HEAD(&vgroup->vregion_list);

	err = mlxsw_sp_acl_tcam_group_add(tcam, &vgroup->group);
	अगर (err)
		वापस err;

	err = rhashtable_init(&vgroup->vchunk_ht,
			      &mlxsw_sp_acl_tcam_vchunk_ht_params);
	अगर (err)
		जाओ err_rhashtable_init;

	वापस 0;

err_rhashtable_init:
	mlxsw_sp_acl_tcam_group_del(&vgroup->group);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vgroup_del(काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup)
अणु
	rhashtable_destroy(&vgroup->vchunk_ht);
	mlxsw_sp_acl_tcam_group_del(&vgroup->group);
	WARN_ON(!list_empty(&vgroup->vregion_list));
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_group_bind(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_acl_tcam_group *group,
			     काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     bool ingress)
अणु
	अक्षर ppbt_pl[MLXSW_REG_PPBT_LEN];

	mlxsw_reg_ppbt_pack(ppbt_pl, ingress ? MLXSW_REG_PXBT_E_IACL :
					       MLXSW_REG_PXBT_E_EACL,
			    MLXSW_REG_PXBT_OP_BIND, mlxsw_sp_port->local_port,
			    group->id);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ppbt), ppbt_pl);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_group_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_tcam_group *group,
			       काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       bool ingress)
अणु
	अक्षर ppbt_pl[MLXSW_REG_PPBT_LEN];

	mlxsw_reg_ppbt_pack(ppbt_pl, ingress ? MLXSW_REG_PXBT_E_IACL :
					       MLXSW_REG_PXBT_E_EACL,
			    MLXSW_REG_PXBT_OP_UNBIND, mlxsw_sp_port->local_port,
			    group->id);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ppbt), ppbt_pl);
पूर्ण

अटल u16
mlxsw_sp_acl_tcam_group_id(काष्ठा mlxsw_sp_acl_tcam_group *group)
अणु
	वापस group->id;
पूर्ण

अटल अचिन्हित पूर्णांक
mlxsw_sp_acl_tcam_vregion_prio(काष्ठा mlxsw_sp_acl_tcam_vregion *vregion)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk;

	अगर (list_empty(&vregion->vchunk_list))
		वापस 0;
	/* As a priority of a vregion, वापस priority of the first vchunk */
	vchunk = list_first_entry(&vregion->vchunk_list,
				  typeof(*vchunk), list);
	वापस vchunk->priority;
पूर्ण

अटल अचिन्हित पूर्णांक
mlxsw_sp_acl_tcam_vregion_max_prio(काष्ठा mlxsw_sp_acl_tcam_vregion *vregion)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk;

	अगर (list_empty(&vregion->vchunk_list))
		वापस 0;
	vchunk = list_last_entry(&vregion->vchunk_list,
				 typeof(*vchunk), list);
	वापस vchunk->priority;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vgroup_prio_update(काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion;

	अगर (list_empty(&vgroup->vregion_list))
		वापस;
	vregion = list_first_entry(&vgroup->vregion_list,
				   typeof(*vregion), list);
	*vgroup->p_min_prio = mlxsw_sp_acl_tcam_vregion_prio(vregion);
	vregion = list_last_entry(&vgroup->vregion_list,
				  typeof(*vregion), list);
	*vgroup->p_max_prio = mlxsw_sp_acl_tcam_vregion_max_prio(vregion);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_group_region_attach(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_acl_tcam_group *group,
				      काष्ठा mlxsw_sp_acl_tcam_region *region,
				      अचिन्हित पूर्णांक priority,
				      काष्ठा mlxsw_sp_acl_tcam_region *next_region)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *region2;
	काष्ठा list_head *pos;
	पूर्णांक err;

	mutex_lock(&group->lock);
	अगर (group->region_count == group->tcam->max_group_size) अणु
		err = -ENOBUFS;
		जाओ err_region_count_check;
	पूर्ण

	अगर (next_region) अणु
		/* If the next region is defined, place the new one
		 * beक्रमe it. The next one is a sibling.
		 */
		pos = &next_region->list;
	पूर्ण अन्यथा अणु
		/* Position the region inside the list according to priority */
		list_क्रम_each(pos, &group->region_list) अणु
			region2 = list_entry(pos, typeof(*region2), list);
			अगर (mlxsw_sp_acl_tcam_vregion_prio(region2->vregion) >
			    priority)
				अवरोध;
		पूर्ण
	पूर्ण
	list_add_tail(&region->list, pos);
	region->group = group;

	err = mlxsw_sp_acl_tcam_group_update(mlxsw_sp, group);
	अगर (err)
		जाओ err_group_update;

	group->region_count++;
	mutex_unlock(&group->lock);
	वापस 0;

err_group_update:
	list_del(&region->list);
err_region_count_check:
	mutex_unlock(&group->lock);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_group_region_detach(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_acl_tcam_region *region)
अणु
	काष्ठा mlxsw_sp_acl_tcam_group *group = region->group;

	mutex_lock(&group->lock);
	list_del(&region->list);
	group->region_count--;
	mlxsw_sp_acl_tcam_group_update(mlxsw_sp, group);
	mutex_unlock(&group->lock);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_vgroup_vregion_attach(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup,
					काष्ठा mlxsw_sp_acl_tcam_vregion *vregion,
					अचिन्हित पूर्णांक priority)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion2;
	काष्ठा list_head *pos;
	पूर्णांक err;

	/* Position the vregion inside the list according to priority */
	list_क्रम_each(pos, &vgroup->vregion_list) अणु
		vregion2 = list_entry(pos, typeof(*vregion2), list);
		अगर (mlxsw_sp_acl_tcam_vregion_prio(vregion2) > priority)
			अवरोध;
	पूर्ण
	list_add_tail(&vregion->list, pos);

	err = mlxsw_sp_acl_tcam_group_region_attach(mlxsw_sp, &vgroup->group,
						    vregion->region,
						    priority, शून्य);
	अगर (err)
		जाओ err_region_attach;

	वापस 0;

err_region_attach:
	list_del(&vregion->list);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vgroup_vregion_detach(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_acl_tcam_vregion *vregion)
अणु
	list_del(&vregion->list);
	अगर (vregion->region2)
		mlxsw_sp_acl_tcam_group_region_detach(mlxsw_sp,
						      vregion->region2);
	mlxsw_sp_acl_tcam_group_region_detach(mlxsw_sp, vregion->region);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_tcam_vregion *
mlxsw_sp_acl_tcam_vgroup_vregion_find(काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup,
				      अचिन्हित पूर्णांक priority,
				      काष्ठा mlxsw_afk_element_usage *elusage,
				      bool *p_need_split)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion, *vregion2;
	काष्ठा list_head *pos;
	bool issubset;

	list_क्रम_each(pos, &vgroup->vregion_list) अणु
		vregion = list_entry(pos, typeof(*vregion), list);

		/* First, check अगर the requested priority करोes not rather beदीर्घ
		 * under some of the next vregions.
		 */
		अगर (pos->next != &vgroup->vregion_list) अणु /* not last */
			vregion2 = list_entry(pos->next, typeof(*vregion2),
					      list);
			अगर (priority >=
			    mlxsw_sp_acl_tcam_vregion_prio(vregion2))
				जारी;
		पूर्ण

		issubset = mlxsw_afk_key_info_subset(vregion->key_info,
						     elusage);

		/* If requested element usage would not fit and the priority
		 * is lower than the currently inspected vregion we cannot
		 * use this region, so वापस शून्य to indicate new vregion has
		 * to be created.
		 */
		अगर (!issubset &&
		    priority < mlxsw_sp_acl_tcam_vregion_prio(vregion))
			वापस शून्य;

		/* If requested element usage would not fit and the priority
		 * is higher than the currently inspected vregion we cannot
		 * use this vregion. There is still some hope that the next
		 * vregion would be the fit. So let it be processed and
		 * eventually अवरोध at the check right above this.
		 */
		अगर (!issubset &&
		    priority > mlxsw_sp_acl_tcam_vregion_max_prio(vregion))
			जारी;

		/* Indicate अगर the vregion needs to be split in order to add
		 * the requested priority. Split is needed when requested
		 * element usage won't fit पूर्णांकo the found vregion.
		 */
		*p_need_split = !issubset;
		वापस vregion;
	पूर्ण
	वापस शून्य; /* New vregion has to be created. */
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vgroup_use_patterns(काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup,
				      काष्ठा mlxsw_afk_element_usage *elusage,
				      काष्ठा mlxsw_afk_element_usage *out)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_pattern *pattern;
	पूर्णांक i;

	/* In हाल the ढाँचा is set, we करोn't have to look up the pattern
	 * and just use the ढाँचा.
	 */
	अगर (vgroup->पंचांगplt_elusage_set) अणु
		स_नकल(out, &vgroup->पंचांगplt_elusage, माप(*out));
		WARN_ON(!mlxsw_afk_element_usage_subset(elusage, out));
		वापस;
	पूर्ण

	क्रम (i = 0; i < vgroup->patterns_count; i++) अणु
		pattern = &vgroup->patterns[i];
		mlxsw_afk_element_usage_fill(out, pattern->elements,
					     pattern->elements_count);
		अगर (mlxsw_afk_element_usage_subset(elusage, out))
			वापस;
	पूर्ण
	स_नकल(out, elusage, माप(*out));
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_region_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_tcam_region *region)
अणु
	काष्ठा mlxsw_afk_key_info *key_info = region->key_info;
	अक्षर ptar_pl[MLXSW_REG_PTAR_LEN];
	अचिन्हित पूर्णांक encodings_count;
	पूर्णांक i;
	पूर्णांक err;

	mlxsw_reg_ptar_pack(ptar_pl, MLXSW_REG_PTAR_OP_ALLOC,
			    region->key_type,
			    MLXSW_SP_ACL_TCAM_REGION_BASE_COUNT,
			    region->id, region->tcam_region_info);
	encodings_count = mlxsw_afk_key_info_blocks_count_get(key_info);
	क्रम (i = 0; i < encodings_count; i++) अणु
		u16 encoding;

		encoding = mlxsw_afk_key_info_block_encoding_get(key_info, i);
		mlxsw_reg_ptar_key_id_pack(ptar_pl, i, encoding);
	पूर्ण
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptar), ptar_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_ptar_unpack(ptar_pl, region->tcam_region_info);
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_region_मुक्त(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_acl_tcam_region *region)
अणु
	अक्षर ptar_pl[MLXSW_REG_PTAR_LEN];

	mlxsw_reg_ptar_pack(ptar_pl, MLXSW_REG_PTAR_OP_FREE,
			    region->key_type, 0, region->id,
			    region->tcam_region_info);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(ptar), ptar_pl);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_region_enable(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_tcam_region *region)
अणु
	अक्षर pacl_pl[MLXSW_REG_PACL_LEN];

	mlxsw_reg_pacl_pack(pacl_pl, region->id, true,
			    region->tcam_region_info);
	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pacl), pacl_pl);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_region_disable(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_tcam_region *region)
अणु
	अक्षर pacl_pl[MLXSW_REG_PACL_LEN];

	mlxsw_reg_pacl_pack(pacl_pl, region->id, false,
			    region->tcam_region_info);
	mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(pacl), pacl_pl);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_tcam_region *
mlxsw_sp_acl_tcam_region_create(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_tcam *tcam,
				काष्ठा mlxsw_sp_acl_tcam_vregion *vregion,
				व्योम *hपूर्णांकs_priv)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	काष्ठा mlxsw_sp_acl_tcam_region *region;
	पूर्णांक err;

	region = kzalloc(माप(*region) + ops->region_priv_size, GFP_KERNEL);
	अगर (!region)
		वापस ERR_PTR(-ENOMEM);
	region->mlxsw_sp = mlxsw_sp;
	region->vregion = vregion;
	region->key_info = vregion->key_info;

	err = mlxsw_sp_acl_tcam_region_id_get(tcam, &region->id);
	अगर (err)
		जाओ err_region_id_get;

	err = ops->region_associate(mlxsw_sp, region);
	अगर (err)
		जाओ err_tcam_region_associate;

	region->key_type = ops->key_type;
	err = mlxsw_sp_acl_tcam_region_alloc(mlxsw_sp, region);
	अगर (err)
		जाओ err_tcam_region_alloc;

	err = mlxsw_sp_acl_tcam_region_enable(mlxsw_sp, region);
	अगर (err)
		जाओ err_tcam_region_enable;

	err = ops->region_init(mlxsw_sp, region->priv, tcam->priv,
			       region, hपूर्णांकs_priv);
	अगर (err)
		जाओ err_tcam_region_init;

	वापस region;

err_tcam_region_init:
	mlxsw_sp_acl_tcam_region_disable(mlxsw_sp, region);
err_tcam_region_enable:
	mlxsw_sp_acl_tcam_region_मुक्त(mlxsw_sp, region);
err_tcam_region_alloc:
err_tcam_region_associate:
	mlxsw_sp_acl_tcam_region_id_put(tcam, region->id);
err_region_id_get:
	kमुक्त(region);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_region_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_tcam_region *region)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	ops->region_fini(mlxsw_sp, region->priv);
	mlxsw_sp_acl_tcam_region_disable(mlxsw_sp, region);
	mlxsw_sp_acl_tcam_region_मुक्त(mlxsw_sp, region);
	mlxsw_sp_acl_tcam_region_id_put(region->group->tcam,
					region->id);
	kमुक्त(region);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vregion_rehash_work_schedule(काष्ठा mlxsw_sp_acl_tcam_vregion *vregion)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = vregion->tcam->vregion_rehash_पूर्णांकrvl;

	अगर (!पूर्णांकerval)
		वापस;
	mlxsw_core_schedule_dw(&vregion->rehash.dw,
			       msecs_to_jअगरfies(पूर्णांकerval));
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vregion_rehash(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_tcam_vregion *vregion,
				 पूर्णांक *credits);

अटल व्योम mlxsw_sp_acl_tcam_vregion_rehash_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion =
		container_of(work, काष्ठा mlxsw_sp_acl_tcam_vregion,
			     rehash.dw.work);
	पूर्णांक credits = MLXSW_SP_ACL_TCAM_VREGION_REHASH_CREDITS;

	mlxsw_sp_acl_tcam_vregion_rehash(vregion->mlxsw_sp, vregion, &credits);
	अगर (credits < 0)
		/* Rehash gone out of credits so it was पूर्णांकerrupted.
		 * Schedule the work as soon as possible to जारी.
		 */
		mlxsw_core_schedule_dw(&vregion->rehash.dw, 0);
	अन्यथा
		mlxsw_sp_acl_tcam_vregion_rehash_work_schedule(vregion);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_rehash_ctx_vchunk_changed(काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion = vchunk->vregion;

	/* If a rule was added or deleted from vchunk which is currently
	 * under rehash migration, we have to reset the ventry poपूर्णांकers
	 * to make sure all rules are properly migrated.
	 */
	अगर (vregion->rehash.ctx.current_vchunk == vchunk) अणु
		vregion->rehash.ctx.start_ventry = शून्य;
		vregion->rehash.ctx.stop_ventry = शून्य;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_rehash_ctx_vregion_changed(काष्ठा mlxsw_sp_acl_tcam_vregion *vregion)
अणु
	/* If a chunk was added or deleted from vregion we have to reset
	 * the current chunk poपूर्णांकer to make sure all chunks
	 * are properly migrated.
	 */
	vregion->rehash.ctx.current_vchunk = शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_acl_tcam_vregion *
mlxsw_sp_acl_tcam_vregion_create(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup,
				 अचिन्हित पूर्णांक priority,
				 काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	काष्ठा mlxsw_afk *afk = mlxsw_sp_acl_afk(mlxsw_sp->acl);
	काष्ठा mlxsw_sp_acl_tcam *tcam = vgroup->group.tcam;
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion;
	पूर्णांक err;

	vregion = kzalloc(माप(*vregion), GFP_KERNEL);
	अगर (!vregion)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&vregion->vchunk_list);
	mutex_init(&vregion->lock);
	vregion->tcam = tcam;
	vregion->mlxsw_sp = mlxsw_sp;
	vregion->vgroup = vgroup;
	vregion->ref_count = 1;

	vregion->key_info = mlxsw_afk_key_info_get(afk, elusage);
	अगर (IS_ERR(vregion->key_info)) अणु
		err = PTR_ERR(vregion->key_info);
		जाओ err_key_info_get;
	पूर्ण

	vregion->region = mlxsw_sp_acl_tcam_region_create(mlxsw_sp, tcam,
							  vregion, शून्य);
	अगर (IS_ERR(vregion->region)) अणु
		err = PTR_ERR(vregion->region);
		जाओ err_region_create;
	पूर्ण

	err = mlxsw_sp_acl_tcam_vgroup_vregion_attach(mlxsw_sp, vgroup, vregion,
						      priority);
	अगर (err)
		जाओ err_vgroup_vregion_attach;

	अगर (vgroup->vregion_rehash_enabled && ops->region_rehash_hपूर्णांकs_get) अणु
		/* Create the delayed work क्रम vregion periodic rehash */
		INIT_DELAYED_WORK(&vregion->rehash.dw,
				  mlxsw_sp_acl_tcam_vregion_rehash_work);
		mlxsw_sp_acl_tcam_vregion_rehash_work_schedule(vregion);
		mutex_lock(&tcam->lock);
		list_add_tail(&vregion->tlist, &tcam->vregion_list);
		mutex_unlock(&tcam->lock);
	पूर्ण

	वापस vregion;

err_vgroup_vregion_attach:
	mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, vregion->region);
err_region_create:
	mlxsw_afk_key_info_put(vregion->key_info);
err_key_info_get:
	kमुक्त(vregion);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vregion_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_tcam_vregion *vregion)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup = vregion->vgroup;
	काष्ठा mlxsw_sp_acl_tcam *tcam = vregion->tcam;

	अगर (vgroup->vregion_rehash_enabled && ops->region_rehash_hपूर्णांकs_get) अणु
		mutex_lock(&tcam->lock);
		list_del(&vregion->tlist);
		mutex_unlock(&tcam->lock);
		cancel_delayed_work_sync(&vregion->rehash.dw);
	पूर्ण
	mlxsw_sp_acl_tcam_vgroup_vregion_detach(mlxsw_sp, vregion);
	अगर (vregion->region2)
		mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, vregion->region2);
	mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, vregion->region);
	mlxsw_afk_key_info_put(vregion->key_info);
	mutex_destroy(&vregion->lock);
	kमुक्त(vregion);
पूर्ण

u32 mlxsw_sp_acl_tcam_vregion_rehash_पूर्णांकrvl_get(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_acl_tcam *tcam)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	u32 vregion_rehash_पूर्णांकrvl;

	अगर (WARN_ON(!ops->region_rehash_hपूर्णांकs_get))
		वापस 0;
	vregion_rehash_पूर्णांकrvl = tcam->vregion_rehash_पूर्णांकrvl;
	वापस vregion_rehash_पूर्णांकrvl;
पूर्ण

पूर्णांक mlxsw_sp_acl_tcam_vregion_rehash_पूर्णांकrvl_set(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_acl_tcam *tcam,
						u32 val)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion;

	अगर (val < MLXSW_SP_ACL_TCAM_VREGION_REHASH_INTRVL_MIN && val)
		वापस -EINVAL;
	अगर (WARN_ON(!ops->region_rehash_hपूर्णांकs_get))
		वापस -EOPNOTSUPP;
	tcam->vregion_rehash_पूर्णांकrvl = val;
	mutex_lock(&tcam->lock);
	list_क्रम_each_entry(vregion, &tcam->vregion_list, tlist) अणु
		अगर (val)
			mlxsw_core_schedule_dw(&vregion->rehash.dw, 0);
		अन्यथा
			cancel_delayed_work_sync(&vregion->rehash.dw);
	पूर्ण
	mutex_unlock(&tcam->lock);
	वापस 0;
पूर्ण

अटल काष्ठा mlxsw_sp_acl_tcam_vregion *
mlxsw_sp_acl_tcam_vregion_get(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup,
			      अचिन्हित पूर्णांक priority,
			      काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	काष्ठा mlxsw_afk_element_usage vregion_elusage;
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion;
	bool need_split;

	vregion = mlxsw_sp_acl_tcam_vgroup_vregion_find(vgroup, priority,
							elusage, &need_split);
	अगर (vregion) अणु
		अगर (need_split) अणु
			/* According to priority, new vchunk should beदीर्घ to
			 * an existing vregion. However, this vchunk needs
			 * elements that vregion करोes not contain. We need
			 * to split the existing vregion पूर्णांकo two and create
			 * a new vregion क्रम the new vchunk in between.
			 * This is not supported now.
			 */
			वापस ERR_PTR(-EOPNOTSUPP);
		पूर्ण
		vregion->ref_count++;
		वापस vregion;
	पूर्ण

	mlxsw_sp_acl_tcam_vgroup_use_patterns(vgroup, elusage,
					      &vregion_elusage);

	वापस mlxsw_sp_acl_tcam_vregion_create(mlxsw_sp, vgroup, priority,
						&vregion_elusage);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vregion_put(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_acl_tcam_vregion *vregion)
अणु
	अगर (--vregion->ref_count)
		वापस;
	mlxsw_sp_acl_tcam_vregion_destroy(mlxsw_sp, vregion);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_tcam_chunk *
mlxsw_sp_acl_tcam_chunk_create(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk,
			       काष्ठा mlxsw_sp_acl_tcam_region *region)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	काष्ठा mlxsw_sp_acl_tcam_chunk *chunk;

	chunk = kzalloc(माप(*chunk) + ops->chunk_priv_size, GFP_KERNEL);
	अगर (!chunk)
		वापस ERR_PTR(-ENOMEM);
	chunk->vchunk = vchunk;
	chunk->region = region;

	ops->chunk_init(region->priv, chunk->priv, vchunk->priority);
	वापस chunk;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_chunk_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_tcam_chunk *chunk)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	ops->chunk_fini(chunk->priv);
	kमुक्त(chunk);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_tcam_vchunk *
mlxsw_sp_acl_tcam_vchunk_create(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup,
				अचिन्हित पूर्णांक priority,
				काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk, *vchunk2;
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion;
	काष्ठा list_head *pos;
	पूर्णांक err;

	अगर (priority == MLXSW_SP_ACL_TCAM_CATCHALL_PRIO)
		वापस ERR_PTR(-EINVAL);

	vchunk = kzalloc(माप(*vchunk), GFP_KERNEL);
	अगर (!vchunk)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&vchunk->ventry_list);
	vchunk->priority = priority;
	vchunk->vgroup = vgroup;
	vchunk->ref_count = 1;

	vregion = mlxsw_sp_acl_tcam_vregion_get(mlxsw_sp, vgroup,
						priority, elusage);
	अगर (IS_ERR(vregion)) अणु
		err = PTR_ERR(vregion);
		जाओ err_vregion_get;
	पूर्ण

	vchunk->vregion = vregion;

	err = rhashtable_insert_fast(&vgroup->vchunk_ht, &vchunk->ht_node,
				     mlxsw_sp_acl_tcam_vchunk_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	mutex_lock(&vregion->lock);
	vchunk->chunk = mlxsw_sp_acl_tcam_chunk_create(mlxsw_sp, vchunk,
						       vchunk->vregion->region);
	अगर (IS_ERR(vchunk->chunk)) अणु
		mutex_unlock(&vregion->lock);
		err = PTR_ERR(vchunk->chunk);
		जाओ err_chunk_create;
	पूर्ण

	mlxsw_sp_acl_tcam_rehash_ctx_vregion_changed(vregion);

	/* Position the vchunk inside the list according to priority */
	list_क्रम_each(pos, &vregion->vchunk_list) अणु
		vchunk2 = list_entry(pos, typeof(*vchunk2), list);
		अगर (vchunk2->priority > priority)
			अवरोध;
	पूर्ण
	list_add_tail(&vchunk->list, pos);
	mutex_unlock(&vregion->lock);
	mlxsw_sp_acl_tcam_vgroup_prio_update(vgroup);

	वापस vchunk;

err_chunk_create:
	rhashtable_हटाओ_fast(&vgroup->vchunk_ht, &vchunk->ht_node,
			       mlxsw_sp_acl_tcam_vchunk_ht_params);
err_rhashtable_insert:
	mlxsw_sp_acl_tcam_vregion_put(mlxsw_sp, vregion);
err_vregion_get:
	kमुक्त(vchunk);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vchunk_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion = vchunk->vregion;
	काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup = vchunk->vgroup;

	mutex_lock(&vregion->lock);
	mlxsw_sp_acl_tcam_rehash_ctx_vregion_changed(vregion);
	list_del(&vchunk->list);
	अगर (vchunk->chunk2)
		mlxsw_sp_acl_tcam_chunk_destroy(mlxsw_sp, vchunk->chunk2);
	mlxsw_sp_acl_tcam_chunk_destroy(mlxsw_sp, vchunk->chunk);
	mutex_unlock(&vregion->lock);
	rhashtable_हटाओ_fast(&vgroup->vchunk_ht, &vchunk->ht_node,
			       mlxsw_sp_acl_tcam_vchunk_ht_params);
	mlxsw_sp_acl_tcam_vregion_put(mlxsw_sp, vchunk->vregion);
	kमुक्त(vchunk);
	mlxsw_sp_acl_tcam_vgroup_prio_update(vgroup);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_tcam_vchunk *
mlxsw_sp_acl_tcam_vchunk_get(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup,
			     अचिन्हित पूर्णांक priority,
			     काष्ठा mlxsw_afk_element_usage *elusage)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk;

	vchunk = rhashtable_lookup_fast(&vgroup->vchunk_ht, &priority,
					mlxsw_sp_acl_tcam_vchunk_ht_params);
	अगर (vchunk) अणु
		अगर (WARN_ON(!mlxsw_afk_key_info_subset(vchunk->vregion->key_info,
						       elusage)))
			वापस ERR_PTR(-EINVAL);
		vchunk->ref_count++;
		वापस vchunk;
	पूर्ण
	वापस mlxsw_sp_acl_tcam_vchunk_create(mlxsw_sp, vgroup,
					       priority, elusage);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vchunk_put(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk)
अणु
	अगर (--vchunk->ref_count)
		वापस;
	mlxsw_sp_acl_tcam_vchunk_destroy(mlxsw_sp, vchunk);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_tcam_entry *
mlxsw_sp_acl_tcam_entry_create(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_tcam_ventry *ventry,
			       काष्ठा mlxsw_sp_acl_tcam_chunk *chunk)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	काष्ठा mlxsw_sp_acl_tcam_entry *entry;
	पूर्णांक err;

	entry = kzalloc(माप(*entry) + ops->entry_priv_size, GFP_KERNEL);
	अगर (!entry)
		वापस ERR_PTR(-ENOMEM);
	entry->ventry = ventry;
	entry->chunk = chunk;

	err = ops->entry_add(mlxsw_sp, chunk->region->priv, chunk->priv,
			     entry->priv, ventry->rulei);
	अगर (err)
		जाओ err_entry_add;

	वापस entry;

err_entry_add:
	kमुक्त(entry);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_acl_tcam_entry_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
					    काष्ठा mlxsw_sp_acl_tcam_entry *entry)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	ops->entry_del(mlxsw_sp, entry->chunk->region->priv,
		       entry->chunk->priv, entry->priv);
	kमुक्त(entry);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_entry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_acl_tcam_region *region,
				       काष्ठा mlxsw_sp_acl_tcam_entry *entry,
				       काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	वापस ops->entry_action_replace(mlxsw_sp, region->priv,
					 entry->priv, rulei);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_entry_activity_get(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_acl_tcam_entry *entry,
				     bool *activity)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	वापस ops->entry_activity_get(mlxsw_sp, entry->chunk->region->priv,
				       entry->priv, activity);
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_tcam_ventry_add(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_acl_tcam_vgroup *vgroup,
					काष्ठा mlxsw_sp_acl_tcam_ventry *ventry,
					काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion;
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk;
	पूर्णांक err;

	vchunk = mlxsw_sp_acl_tcam_vchunk_get(mlxsw_sp, vgroup, rulei->priority,
					      &rulei->values.elusage);
	अगर (IS_ERR(vchunk))
		वापस PTR_ERR(vchunk);

	ventry->vchunk = vchunk;
	ventry->rulei = rulei;
	vregion = vchunk->vregion;

	mutex_lock(&vregion->lock);
	ventry->entry = mlxsw_sp_acl_tcam_entry_create(mlxsw_sp, ventry,
						       vchunk->chunk);
	अगर (IS_ERR(ventry->entry)) अणु
		mutex_unlock(&vregion->lock);
		err = PTR_ERR(ventry->entry);
		जाओ err_entry_create;
	पूर्ण

	list_add_tail(&ventry->list, &vchunk->ventry_list);
	mlxsw_sp_acl_tcam_rehash_ctx_vchunk_changed(vchunk);
	mutex_unlock(&vregion->lock);

	वापस 0;

err_entry_create:
	mlxsw_sp_acl_tcam_vchunk_put(mlxsw_sp, vchunk);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_acl_tcam_ventry_del(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_acl_tcam_ventry *ventry)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk = ventry->vchunk;
	काष्ठा mlxsw_sp_acl_tcam_vregion *vregion = vchunk->vregion;

	mutex_lock(&vregion->lock);
	mlxsw_sp_acl_tcam_rehash_ctx_vchunk_changed(vchunk);
	list_del(&ventry->list);
	mlxsw_sp_acl_tcam_entry_destroy(mlxsw_sp, ventry->entry);
	mutex_unlock(&vregion->lock);
	mlxsw_sp_acl_tcam_vchunk_put(mlxsw_sp, vchunk);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_ventry_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_acl_tcam_ventry *ventry,
					काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk = ventry->vchunk;

	वापस mlxsw_sp_acl_tcam_entry_action_replace(mlxsw_sp,
						      vchunk->vregion->region,
						      ventry->entry, rulei);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_ventry_activity_get(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_acl_tcam_ventry *ventry,
				      bool *activity)
अणु
	वापस mlxsw_sp_acl_tcam_entry_activity_get(mlxsw_sp,
						    ventry->entry, activity);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_ventry_migrate(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_tcam_ventry *ventry,
				 काष्ठा mlxsw_sp_acl_tcam_chunk *chunk,
				 पूर्णांक *credits)
अणु
	काष्ठा mlxsw_sp_acl_tcam_entry *new_entry;

	/* First check अगर the entry is not alपढ़ोy where we want it to be. */
	अगर (ventry->entry->chunk == chunk)
		वापस 0;

	अगर (--(*credits) < 0)
		वापस 0;

	new_entry = mlxsw_sp_acl_tcam_entry_create(mlxsw_sp, ventry, chunk);
	अगर (IS_ERR(new_entry))
		वापस PTR_ERR(new_entry);
	mlxsw_sp_acl_tcam_entry_destroy(mlxsw_sp, ventry->entry);
	ventry->entry = new_entry;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_vchunk_migrate_start(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk,
				       काष्ठा mlxsw_sp_acl_tcam_region *region,
				       काष्ठा mlxsw_sp_acl_tcam_rehash_ctx *ctx)
अणु
	काष्ठा mlxsw_sp_acl_tcam_chunk *new_chunk;

	new_chunk = mlxsw_sp_acl_tcam_chunk_create(mlxsw_sp, vchunk, region);
	अगर (IS_ERR(new_chunk))
		वापस PTR_ERR(new_chunk);
	vchunk->chunk2 = vchunk->chunk;
	vchunk->chunk = new_chunk;
	ctx->current_vchunk = vchunk;
	ctx->start_ventry = शून्य;
	ctx->stop_ventry = शून्य;
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vchunk_migrate_end(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk,
				     काष्ठा mlxsw_sp_acl_tcam_rehash_ctx *ctx)
अणु
	mlxsw_sp_acl_tcam_chunk_destroy(mlxsw_sp, vchunk->chunk2);
	vchunk->chunk2 = शून्य;
	ctx->current_vchunk = शून्य;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_vchunk_migrate_one(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk,
				     काष्ठा mlxsw_sp_acl_tcam_region *region,
				     काष्ठा mlxsw_sp_acl_tcam_rehash_ctx *ctx,
				     पूर्णांक *credits)
अणु
	काष्ठा mlxsw_sp_acl_tcam_ventry *ventry;
	पूर्णांक err;

	अगर (vchunk->chunk->region != region) अणु
		err = mlxsw_sp_acl_tcam_vchunk_migrate_start(mlxsw_sp, vchunk,
							     region, ctx);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (!vchunk->chunk2) अणु
		/* The chunk is alपढ़ोy as it should be, nothing to करो. */
		वापस 0;
	पूर्ण

	/* If the migration got पूर्णांकerrupted, we have the ventry to start from
	 * stored in context.
	 */
	अगर (ctx->start_ventry)
		ventry = ctx->start_ventry;
	अन्यथा
		ventry = list_first_entry(&vchunk->ventry_list,
					  typeof(*ventry), list);

	list_क्रम_each_entry_from(ventry, &vchunk->ventry_list, list) अणु
		/* During rollback, once we reach the ventry that failed
		 * to migrate, we are करोne.
		 */
		अगर (ventry == ctx->stop_ventry)
			अवरोध;

		err = mlxsw_sp_acl_tcam_ventry_migrate(mlxsw_sp, ventry,
						       vchunk->chunk, credits);
		अगर (err) अणु
			अगर (ctx->this_is_rollback) अणु
				/* Save the ventry which we ended with and try
				 * to जारी later on.
				 */
				ctx->start_ventry = ventry;
				वापस err;
			पूर्ण
			/* Swap the chunk and chunk2 poपूर्णांकers so the follow-up
			 * rollback call will see the original chunk poपूर्णांकer
			 * in vchunk->chunk.
			 */
			swap(vchunk->chunk, vchunk->chunk2);
			/* The rollback has to be करोne from beginning of the
			 * chunk, that is why we have to null the start_ventry.
			 * However, we know where to stop the rollback,
			 * at the current ventry.
			 */
			ctx->start_ventry = शून्य;
			ctx->stop_ventry = ventry;
			वापस err;
		पूर्ण अन्यथा अगर (*credits < 0) अणु
			/* We are out of credits, the rest of the ventries
			 * will be migrated later. Save the ventry
			 * which we ended with.
			 */
			ctx->start_ventry = ventry;
			वापस 0;
		पूर्ण
	पूर्ण

	mlxsw_sp_acl_tcam_vchunk_migrate_end(mlxsw_sp, vchunk, ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_vchunk_migrate_all(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_acl_tcam_vregion *vregion,
				     काष्ठा mlxsw_sp_acl_tcam_rehash_ctx *ctx,
				     पूर्णांक *credits)
अणु
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk;
	पूर्णांक err;

	/* If the migration got पूर्णांकerrupted, we have the vchunk
	 * we are working on stored in context.
	 */
	अगर (ctx->current_vchunk)
		vchunk = ctx->current_vchunk;
	अन्यथा
		vchunk = list_first_entry(&vregion->vchunk_list,
					  typeof(*vchunk), list);

	list_क्रम_each_entry_from(vchunk, &vregion->vchunk_list, list) अणु
		err = mlxsw_sp_acl_tcam_vchunk_migrate_one(mlxsw_sp, vchunk,
							   vregion->region,
							   ctx, credits);
		अगर (err || *credits < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_vregion_migrate(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_tcam_vregion *vregion,
				  काष्ठा mlxsw_sp_acl_tcam_rehash_ctx *ctx,
				  पूर्णांक *credits)
अणु
	पूर्णांक err, err2;

	trace_mlxsw_sp_acl_tcam_vregion_migrate(mlxsw_sp, vregion);
	mutex_lock(&vregion->lock);
	err = mlxsw_sp_acl_tcam_vchunk_migrate_all(mlxsw_sp, vregion,
						   ctx, credits);
	अगर (err) अणु
		/* In हाल migration was not successful, we need to swap
		 * so the original region poपूर्णांकer is asचिन्हित again
		 * to vregion->region.
		 */
		swap(vregion->region, vregion->region2);
		ctx->current_vchunk = शून्य;
		ctx->this_is_rollback = true;
		err2 = mlxsw_sp_acl_tcam_vchunk_migrate_all(mlxsw_sp, vregion,
							    ctx, credits);
		अगर (err2) अणु
			trace_mlxsw_sp_acl_tcam_vregion_rehash_rollback_failed(mlxsw_sp,
									       vregion);
			dev_err(mlxsw_sp->bus_info->dev, "Failed to rollback during vregion migration fail\n");
			/* Let the rollback to be जारीd later on. */
		पूर्ण
	पूर्ण
	mutex_unlock(&vregion->lock);
	trace_mlxsw_sp_acl_tcam_vregion_migrate_end(mlxsw_sp, vregion);
	वापस err;
पूर्ण

अटल bool
mlxsw_sp_acl_tcam_vregion_rehash_in_progress(स्थिर काष्ठा mlxsw_sp_acl_tcam_rehash_ctx *ctx)
अणु
	वापस ctx->hपूर्णांकs_priv;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_vregion_rehash_start(काष्ठा mlxsw_sp *mlxsw_sp,
				       काष्ठा mlxsw_sp_acl_tcam_vregion *vregion,
				       काष्ठा mlxsw_sp_acl_tcam_rehash_ctx *ctx)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;
	अचिन्हित पूर्णांक priority = mlxsw_sp_acl_tcam_vregion_prio(vregion);
	काष्ठा mlxsw_sp_acl_tcam_region *new_region;
	व्योम *hपूर्णांकs_priv;
	पूर्णांक err;

	trace_mlxsw_sp_acl_tcam_vregion_rehash(mlxsw_sp, vregion);

	hपूर्णांकs_priv = ops->region_rehash_hपूर्णांकs_get(vregion->region->priv);
	अगर (IS_ERR(hपूर्णांकs_priv))
		वापस PTR_ERR(hपूर्णांकs_priv);

	new_region = mlxsw_sp_acl_tcam_region_create(mlxsw_sp, vregion->tcam,
						     vregion, hपूर्णांकs_priv);
	अगर (IS_ERR(new_region)) अणु
		err = PTR_ERR(new_region);
		जाओ err_region_create;
	पूर्ण

	/* vregion->region contains the poपूर्णांकer to the new region
	 * we are going to migrate to.
	 */
	vregion->region2 = vregion->region;
	vregion->region = new_region;
	err = mlxsw_sp_acl_tcam_group_region_attach(mlxsw_sp,
						    vregion->region2->group,
						    new_region, priority,
						    vregion->region2);
	अगर (err)
		जाओ err_group_region_attach;

	ctx->hपूर्णांकs_priv = hपूर्णांकs_priv;
	ctx->this_is_rollback = false;

	वापस 0;

err_group_region_attach:
	vregion->region = vregion->region2;
	vregion->region2 = शून्य;
	mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, new_region);
err_region_create:
	ops->region_rehash_hपूर्णांकs_put(hपूर्णांकs_priv);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vregion_rehash_end(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_acl_tcam_vregion *vregion,
				     काष्ठा mlxsw_sp_acl_tcam_rehash_ctx *ctx)
अणु
	काष्ठा mlxsw_sp_acl_tcam_region *unused_region = vregion->region2;
	स्थिर काष्ठा mlxsw_sp_acl_tcam_ops *ops = mlxsw_sp->acl_tcam_ops;

	vregion->region2 = शून्य;
	mlxsw_sp_acl_tcam_group_region_detach(mlxsw_sp, unused_region);
	mlxsw_sp_acl_tcam_region_destroy(mlxsw_sp, unused_region);
	ops->region_rehash_hपूर्णांकs_put(ctx->hपूर्णांकs_priv);
	ctx->hपूर्णांकs_priv = शून्य;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_vregion_rehash(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_tcam_vregion *vregion,
				 पूर्णांक *credits)
अणु
	काष्ठा mlxsw_sp_acl_tcam_rehash_ctx *ctx = &vregion->rehash.ctx;
	पूर्णांक err;

	/* Check अगर the previous rehash work was पूर्णांकerrupted
	 * which means we have to जारी it now.
	 * If not, start a new rehash.
	 */
	अगर (!mlxsw_sp_acl_tcam_vregion_rehash_in_progress(ctx)) अणु
		err = mlxsw_sp_acl_tcam_vregion_rehash_start(mlxsw_sp,
							     vregion, ctx);
		अगर (err) अणु
			अगर (err != -EAGAIN)
				dev_err(mlxsw_sp->bus_info->dev, "Failed get rehash hints\n");
			वापस;
		पूर्ण
	पूर्ण

	err = mlxsw_sp_acl_tcam_vregion_migrate(mlxsw_sp, vregion,
						ctx, credits);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to migrate vregion\n");
	पूर्ण

	अगर (*credits >= 0)
		mlxsw_sp_acl_tcam_vregion_rehash_end(mlxsw_sp, vregion, ctx);
पूर्ण

अटल स्थिर क्रमागत mlxsw_afk_element mlxsw_sp_acl_tcam_pattern_ipv4[] = अणु
	MLXSW_AFK_ELEMENT_SRC_SYS_PORT,
	MLXSW_AFK_ELEMENT_DMAC_32_47,
	MLXSW_AFK_ELEMENT_DMAC_0_31,
	MLXSW_AFK_ELEMENT_SMAC_32_47,
	MLXSW_AFK_ELEMENT_SMAC_0_31,
	MLXSW_AFK_ELEMENT_ETHERTYPE,
	MLXSW_AFK_ELEMENT_IP_PROTO,
	MLXSW_AFK_ELEMENT_SRC_IP_0_31,
	MLXSW_AFK_ELEMENT_DST_IP_0_31,
	MLXSW_AFK_ELEMENT_DST_L4_PORT,
	MLXSW_AFK_ELEMENT_SRC_L4_PORT,
	MLXSW_AFK_ELEMENT_VID,
	MLXSW_AFK_ELEMENT_PCP,
	MLXSW_AFK_ELEMENT_TCP_FLAGS,
	MLXSW_AFK_ELEMENT_IP_TTL_,
	MLXSW_AFK_ELEMENT_IP_ECN,
	MLXSW_AFK_ELEMENT_IP_DSCP,
पूर्ण;

अटल स्थिर क्रमागत mlxsw_afk_element mlxsw_sp_acl_tcam_pattern_ipv6[] = अणु
	MLXSW_AFK_ELEMENT_ETHERTYPE,
	MLXSW_AFK_ELEMENT_IP_PROTO,
	MLXSW_AFK_ELEMENT_SRC_IP_96_127,
	MLXSW_AFK_ELEMENT_SRC_IP_64_95,
	MLXSW_AFK_ELEMENT_SRC_IP_32_63,
	MLXSW_AFK_ELEMENT_SRC_IP_0_31,
	MLXSW_AFK_ELEMENT_DST_IP_96_127,
	MLXSW_AFK_ELEMENT_DST_IP_64_95,
	MLXSW_AFK_ELEMENT_DST_IP_32_63,
	MLXSW_AFK_ELEMENT_DST_IP_0_31,
	MLXSW_AFK_ELEMENT_DST_L4_PORT,
	MLXSW_AFK_ELEMENT_SRC_L4_PORT,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_acl_tcam_pattern mlxsw_sp_acl_tcam_patterns[] = अणु
	अणु
		.elements = mlxsw_sp_acl_tcam_pattern_ipv4,
		.elements_count = ARRAY_SIZE(mlxsw_sp_acl_tcam_pattern_ipv4),
	पूर्ण,
	अणु
		.elements = mlxsw_sp_acl_tcam_pattern_ipv6,
		.elements_count = ARRAY_SIZE(mlxsw_sp_acl_tcam_pattern_ipv6),
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_SP_ACL_TCAM_PATTERNS_COUNT \
	ARRAY_SIZE(mlxsw_sp_acl_tcam_patterns)

काष्ठा mlxsw_sp_acl_tcam_flower_ruleset अणु
	काष्ठा mlxsw_sp_acl_tcam_vgroup vgroup;
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_flower_rule अणु
	काष्ठा mlxsw_sp_acl_tcam_ventry ventry;
पूर्ण;

अटल पूर्णांक
mlxsw_sp_acl_tcam_flower_ruleset_add(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_acl_tcam *tcam,
				     व्योम *ruleset_priv,
				     काष्ठा mlxsw_afk_element_usage *पंचांगplt_elusage,
				     अचिन्हित पूर्णांक *p_min_prio,
				     अचिन्हित पूर्णांक *p_max_prio)
अणु
	काष्ठा mlxsw_sp_acl_tcam_flower_ruleset *ruleset = ruleset_priv;

	वापस mlxsw_sp_acl_tcam_vgroup_add(mlxsw_sp, tcam, &ruleset->vgroup,
					    mlxsw_sp_acl_tcam_patterns,
					    MLXSW_SP_ACL_TCAM_PATTERNS_COUNT,
					    पंचांगplt_elusage, true,
					    p_min_prio, p_max_prio);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_flower_ruleset_del(काष्ठा mlxsw_sp *mlxsw_sp,
				     व्योम *ruleset_priv)
अणु
	काष्ठा mlxsw_sp_acl_tcam_flower_ruleset *ruleset = ruleset_priv;

	mlxsw_sp_acl_tcam_vgroup_del(&ruleset->vgroup);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_flower_ruleset_bind(काष्ठा mlxsw_sp *mlxsw_sp,
				      व्योम *ruleset_priv,
				      काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				      bool ingress)
अणु
	काष्ठा mlxsw_sp_acl_tcam_flower_ruleset *ruleset = ruleset_priv;

	वापस mlxsw_sp_acl_tcam_group_bind(mlxsw_sp, &ruleset->vgroup.group,
					    mlxsw_sp_port, ingress);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_flower_ruleset_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
					व्योम *ruleset_priv,
					काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					bool ingress)
अणु
	काष्ठा mlxsw_sp_acl_tcam_flower_ruleset *ruleset = ruleset_priv;

	mlxsw_sp_acl_tcam_group_unbind(mlxsw_sp, &ruleset->vgroup.group,
				       mlxsw_sp_port, ingress);
पूर्ण

अटल u16
mlxsw_sp_acl_tcam_flower_ruleset_group_id(व्योम *ruleset_priv)
अणु
	काष्ठा mlxsw_sp_acl_tcam_flower_ruleset *ruleset = ruleset_priv;

	वापस mlxsw_sp_acl_tcam_group_id(&ruleset->vgroup.group);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_flower_rule_add(काष्ठा mlxsw_sp *mlxsw_sp,
				  व्योम *ruleset_priv, व्योम *rule_priv,
				  काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp_acl_tcam_flower_ruleset *ruleset = ruleset_priv;
	काष्ठा mlxsw_sp_acl_tcam_flower_rule *rule = rule_priv;

	वापस mlxsw_sp_acl_tcam_ventry_add(mlxsw_sp, &ruleset->vgroup,
					    &rule->ventry, rulei);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_flower_rule_del(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *rule_priv)
अणु
	काष्ठा mlxsw_sp_acl_tcam_flower_rule *rule = rule_priv;

	mlxsw_sp_acl_tcam_ventry_del(mlxsw_sp, &rule->ventry);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_flower_rule_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					     व्योम *rule_priv,
					     काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_flower_rule_activity_get(काष्ठा mlxsw_sp *mlxsw_sp,
					   व्योम *rule_priv, bool *activity)
अणु
	काष्ठा mlxsw_sp_acl_tcam_flower_rule *rule = rule_priv;

	वापस mlxsw_sp_acl_tcam_ventry_activity_get(mlxsw_sp, &rule->ventry,
						     activity);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_acl_profile_ops mlxsw_sp_acl_tcam_flower_ops = अणु
	.ruleset_priv_size	= माप(काष्ठा mlxsw_sp_acl_tcam_flower_ruleset),
	.ruleset_add		= mlxsw_sp_acl_tcam_flower_ruleset_add,
	.ruleset_del		= mlxsw_sp_acl_tcam_flower_ruleset_del,
	.ruleset_bind		= mlxsw_sp_acl_tcam_flower_ruleset_bind,
	.ruleset_unbind		= mlxsw_sp_acl_tcam_flower_ruleset_unbind,
	.ruleset_group_id	= mlxsw_sp_acl_tcam_flower_ruleset_group_id,
	.rule_priv_size		= माप(काष्ठा mlxsw_sp_acl_tcam_flower_rule),
	.rule_add		= mlxsw_sp_acl_tcam_flower_rule_add,
	.rule_del		= mlxsw_sp_acl_tcam_flower_rule_del,
	.rule_action_replace	= mlxsw_sp_acl_tcam_flower_rule_action_replace,
	.rule_activity_get	= mlxsw_sp_acl_tcam_flower_rule_activity_get,
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_mr_ruleset अणु
	काष्ठा mlxsw_sp_acl_tcam_vchunk *vchunk;
	काष्ठा mlxsw_sp_acl_tcam_vgroup vgroup;
पूर्ण;

काष्ठा mlxsw_sp_acl_tcam_mr_rule अणु
	काष्ठा mlxsw_sp_acl_tcam_ventry ventry;
पूर्ण;

अटल पूर्णांक
mlxsw_sp_acl_tcam_mr_ruleset_add(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_tcam *tcam,
				 व्योम *ruleset_priv,
				 काष्ठा mlxsw_afk_element_usage *पंचांगplt_elusage,
				 अचिन्हित पूर्णांक *p_min_prio,
				 अचिन्हित पूर्णांक *p_max_prio)
अणु
	काष्ठा mlxsw_sp_acl_tcam_mr_ruleset *ruleset = ruleset_priv;
	पूर्णांक err;

	err = mlxsw_sp_acl_tcam_vgroup_add(mlxsw_sp, tcam, &ruleset->vgroup,
					   mlxsw_sp_acl_tcam_patterns,
					   MLXSW_SP_ACL_TCAM_PATTERNS_COUNT,
					   पंचांगplt_elusage, false,
					   p_min_prio, p_max_prio);
	अगर (err)
		वापस err;

	/* For most of the TCAM clients it would make sense to take a tcam chunk
	 * only when the first rule is written. This is not the हाल क्रम
	 * multicast router as it is required to bind the multicast router to a
	 * specअगरic ACL Group ID which must exist in HW beक्रमe multicast router
	 * is initialized.
	 */
	ruleset->vchunk = mlxsw_sp_acl_tcam_vchunk_get(mlxsw_sp,
						       &ruleset->vgroup, 1,
						       पंचांगplt_elusage);
	अगर (IS_ERR(ruleset->vchunk)) अणु
		err = PTR_ERR(ruleset->vchunk);
		जाओ err_chunk_get;
	पूर्ण

	वापस 0;

err_chunk_get:
	mlxsw_sp_acl_tcam_vgroup_del(&ruleset->vgroup);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_mr_ruleset_del(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *ruleset_priv)
अणु
	काष्ठा mlxsw_sp_acl_tcam_mr_ruleset *ruleset = ruleset_priv;

	mlxsw_sp_acl_tcam_vchunk_put(mlxsw_sp, ruleset->vchunk);
	mlxsw_sp_acl_tcam_vgroup_del(&ruleset->vgroup);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_mr_ruleset_bind(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *ruleset_priv,
				  काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  bool ingress)
अणु
	/* Binding is करोne when initializing multicast router */
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_mr_ruleset_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
				    व्योम *ruleset_priv,
				    काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    bool ingress)
अणु
पूर्ण

अटल u16
mlxsw_sp_acl_tcam_mr_ruleset_group_id(व्योम *ruleset_priv)
अणु
	काष्ठा mlxsw_sp_acl_tcam_mr_ruleset *ruleset = ruleset_priv;

	वापस mlxsw_sp_acl_tcam_group_id(&ruleset->vgroup.group);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_mr_rule_add(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *ruleset_priv,
			      व्योम *rule_priv,
			      काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp_acl_tcam_mr_ruleset *ruleset = ruleset_priv;
	काष्ठा mlxsw_sp_acl_tcam_mr_rule *rule = rule_priv;

	वापस mlxsw_sp_acl_tcam_ventry_add(mlxsw_sp, &ruleset->vgroup,
					   &rule->ventry, rulei);
पूर्ण

अटल व्योम
mlxsw_sp_acl_tcam_mr_rule_del(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *rule_priv)
अणु
	काष्ठा mlxsw_sp_acl_tcam_mr_rule *rule = rule_priv;

	mlxsw_sp_acl_tcam_ventry_del(mlxsw_sp, &rule->ventry);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_mr_rule_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
					 व्योम *rule_priv,
					 काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	काष्ठा mlxsw_sp_acl_tcam_mr_rule *rule = rule_priv;

	वापस mlxsw_sp_acl_tcam_ventry_action_replace(mlxsw_sp, &rule->ventry,
						       rulei);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_tcam_mr_rule_activity_get(काष्ठा mlxsw_sp *mlxsw_sp,
				       व्योम *rule_priv, bool *activity)
अणु
	काष्ठा mlxsw_sp_acl_tcam_mr_rule *rule = rule_priv;

	वापस mlxsw_sp_acl_tcam_ventry_activity_get(mlxsw_sp, &rule->ventry,
						     activity);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_acl_profile_ops mlxsw_sp_acl_tcam_mr_ops = अणु
	.ruleset_priv_size	= माप(काष्ठा mlxsw_sp_acl_tcam_mr_ruleset),
	.ruleset_add		= mlxsw_sp_acl_tcam_mr_ruleset_add,
	.ruleset_del		= mlxsw_sp_acl_tcam_mr_ruleset_del,
	.ruleset_bind		= mlxsw_sp_acl_tcam_mr_ruleset_bind,
	.ruleset_unbind		= mlxsw_sp_acl_tcam_mr_ruleset_unbind,
	.ruleset_group_id	= mlxsw_sp_acl_tcam_mr_ruleset_group_id,
	.rule_priv_size		= माप(काष्ठा mlxsw_sp_acl_tcam_mr_rule),
	.rule_add		= mlxsw_sp_acl_tcam_mr_rule_add,
	.rule_del		= mlxsw_sp_acl_tcam_mr_rule_del,
	.rule_action_replace	= mlxsw_sp_acl_tcam_mr_rule_action_replace,
	.rule_activity_get	= mlxsw_sp_acl_tcam_mr_rule_activity_get,
पूर्ण;

अटल स्थिर काष्ठा mlxsw_sp_acl_profile_ops *
mlxsw_sp_acl_tcam_profile_ops_arr[] = अणु
	[MLXSW_SP_ACL_PROखाता_FLOWER] = &mlxsw_sp_acl_tcam_flower_ops,
	[MLXSW_SP_ACL_PROखाता_MR] = &mlxsw_sp_acl_tcam_mr_ops,
पूर्ण;

स्थिर काष्ठा mlxsw_sp_acl_profile_ops *
mlxsw_sp_acl_tcam_profile_ops(काष्ठा mlxsw_sp *mlxsw_sp,
			      क्रमागत mlxsw_sp_acl_profile profile)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops;

	अगर (WARN_ON(profile >= ARRAY_SIZE(mlxsw_sp_acl_tcam_profile_ops_arr)))
		वापस शून्य;
	ops = mlxsw_sp_acl_tcam_profile_ops_arr[profile];
	अगर (WARN_ON(!ops))
		वापस शून्य;
	वापस ops;
पूर्ण
