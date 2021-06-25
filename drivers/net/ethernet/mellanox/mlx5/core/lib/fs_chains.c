<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
// Copyright (c) 2020 Mellanox Technologies.

#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/mlx5_अगरc.h>
#समावेश <linux/mlx5/fs.h>

#समावेश "lib/fs_chains.h"
#समावेश "en/mapping.h"
#समावेश "fs_core.h"
#समावेश "en_tc.h"

#घोषणा chains_lock(chains) ((chains)->lock)
#घोषणा chains_ht(chains) ((chains)->chains_ht)
#घोषणा prios_ht(chains) ((chains)->prios_ht)
#घोषणा ft_pool_left(chains) ((chains)->ft_left)
#घोषणा tc_शेष_ft(chains) ((chains)->tc_शेष_ft)
#घोषणा tc_end_ft(chains) ((chains)->tc_end_ft)
#घोषणा ns_to_chains_fs_prio(ns) ((ns) == MLX5_FLOW_NAMESPACE_FDB ? \
				  FDB_TC_OFFLOAD : MLX5E_TC_PRIO)

/* Firmware currently has 4 pool of 4 sizes that it supports (FT_POOLS),
 * and a भव memory region of 16M (MLX5_FT_SIZE), this region is duplicated
 * क्रम each flow table pool. We can allocate up to 16M of each pool,
 * and we keep track of how much we used via get_next_avail_sz_from_pool.
 * Firmware करोesn't report any of this क्रम now.
 * ESW_POOL is expected to be sorted from large to small and match firmware
 * pools.
 */
#घोषणा FT_SIZE (16 * 1024 * 1024)
अटल स्थिर अचिन्हित पूर्णांक FT_POOLS[] = अणु 4 * 1024 * 1024,
					  1 * 1024 * 1024,
					  64 * 1024,
					  128 पूर्ण;
#घोषणा FT_TBL_SZ (64 * 1024)

काष्ठा mlx5_fs_chains अणु
	काष्ठा mlx5_core_dev *dev;

	काष्ठा rhashtable chains_ht;
	काष्ठा rhashtable prios_ht;
	/* Protects above chains_ht and prios_ht */
	काष्ठा mutex lock;

	काष्ठा mlx5_flow_table *tc_शेष_ft;
	काष्ठा mlx5_flow_table *tc_end_ft;
	काष्ठा mapping_ctx *chains_mapping;

	क्रमागत mlx5_flow_namespace_type ns;
	u32 group_num;
	u32 flags;

	पूर्णांक ft_left[ARRAY_SIZE(FT_POOLS)];
पूर्ण;

काष्ठा fs_chain अणु
	काष्ठा rhash_head node;

	u32 chain;

	पूर्णांक ref;
	पूर्णांक id;

	काष्ठा mlx5_fs_chains *chains;
	काष्ठा list_head prios_list;
	काष्ठा mlx5_flow_handle *restore_rule;
	काष्ठा mlx5_modअगरy_hdr *miss_modअगरy_hdr;
पूर्ण;

काष्ठा prio_key अणु
	u32 chain;
	u32 prio;
	u32 level;
पूर्ण;

काष्ठा prio अणु
	काष्ठा rhash_head node;
	काष्ठा list_head list;

	काष्ठा prio_key key;

	पूर्णांक ref;

	काष्ठा fs_chain *chain;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_table *next_ft;
	काष्ठा mlx5_flow_group *miss_group;
	काष्ठा mlx5_flow_handle *miss_rule;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params chain_params = अणु
	.head_offset = दुरत्व(काष्ठा fs_chain, node),
	.key_offset = दुरत्व(काष्ठा fs_chain, chain),
	.key_len = माप_field(काष्ठा fs_chain, chain),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params prio_params = अणु
	.head_offset = दुरत्व(काष्ठा prio, node),
	.key_offset = दुरत्व(काष्ठा prio, key),
	.key_len = माप_field(काष्ठा prio, key),
	.स्वतःmatic_shrinking = true,
पूर्ण;

bool mlx5_chains_prios_supported(काष्ठा mlx5_fs_chains *chains)
अणु
	वापस chains->flags & MLX5_CHAINS_AND_PRIOS_SUPPORTED;
पूर्ण

bool mlx5_chains_ignore_flow_level_supported(काष्ठा mlx5_fs_chains *chains)
अणु
	वापस chains->flags & MLX5_CHAINS_IGNORE_FLOW_LEVEL_SUPPORTED;
पूर्ण

bool mlx5_chains_backwards_supported(काष्ठा mlx5_fs_chains *chains)
अणु
	वापस mlx5_chains_prios_supported(chains) &&
	       mlx5_chains_ignore_flow_level_supported(chains);
पूर्ण

u32 mlx5_chains_get_chain_range(काष्ठा mlx5_fs_chains *chains)
अणु
	अगर (!mlx5_chains_prios_supported(chains))
		वापस 1;

	अगर (mlx5_chains_ignore_flow_level_supported(chains))
		वापस अच_पूर्णांक_उच्च - 1;

	/* We should get here only क्रम eचयन हाल */
	वापस FDB_TC_MAX_CHAIN;
पूर्ण

u32 mlx5_chains_get_nf_ft_chain(काष्ठा mlx5_fs_chains *chains)
अणु
	वापस mlx5_chains_get_chain_range(chains) + 1;
पूर्ण

u32 mlx5_chains_get_prio_range(काष्ठा mlx5_fs_chains *chains)
अणु
	अगर (mlx5_chains_ignore_flow_level_supported(chains))
		वापस अच_पूर्णांक_उच्च;

	/* We should get here only क्रम eचयन हाल */
	वापस FDB_TC_MAX_PRIO;
पूर्ण

अटल अचिन्हित पूर्णांक mlx5_chains_get_level_range(काष्ठा mlx5_fs_chains *chains)
अणु
	अगर (mlx5_chains_ignore_flow_level_supported(chains))
		वापस अच_पूर्णांक_उच्च;

	/* Same value क्रम FDB and NIC RX tables */
	वापस FDB_TC_LEVELS_PER_PRIO;
पूर्ण

व्योम
mlx5_chains_set_end_ft(काष्ठा mlx5_fs_chains *chains,
		       काष्ठा mlx5_flow_table *ft)
अणु
	tc_end_ft(chains) = ft;
पूर्ण

#घोषणा POOL_NEXT_SIZE 0
अटल पूर्णांक
mlx5_chains_get_avail_sz_from_pool(काष्ठा mlx5_fs_chains *chains,
				   पूर्णांक desired_size)
अणु
	पूर्णांक i, found_i = -1;

	क्रम (i = ARRAY_SIZE(FT_POOLS) - 1; i >= 0; i--) अणु
		अगर (ft_pool_left(chains)[i] && FT_POOLS[i] > desired_size) अणु
			found_i = i;
			अगर (desired_size != POOL_NEXT_SIZE)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (found_i != -1) अणु
		--ft_pool_left(chains)[found_i];
		वापस FT_POOLS[found_i];
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mlx5_chains_put_sz_to_pool(काष्ठा mlx5_fs_chains *chains, पूर्णांक sz)
अणु
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(FT_POOLS) - 1; i >= 0; i--) अणु
		अगर (sz == FT_POOLS[i]) अणु
			++ft_pool_left(chains)[i];
			वापस;
		पूर्ण
	पूर्ण

	WARN_ONCE(1, "Couldn't find size %d in flow table size pool", sz);
पूर्ण

अटल व्योम
mlx5_chains_init_sz_pool(काष्ठा mlx5_fs_chains *chains, u32 ft_max)
अणु
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(FT_POOLS) - 1; i >= 0; i--)
		ft_pool_left(chains)[i] =
			FT_POOLS[i] <= ft_max ? FT_SIZE / FT_POOLS[i] : 0;
पूर्ण

अटल काष्ठा mlx5_flow_table *
mlx5_chains_create_table(काष्ठा mlx5_fs_chains *chains,
			 u32 chain, u32 prio, u32 level)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_namespace *ns;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक sz;

	अगर (chains->flags & MLX5_CHAINS_FT_TUNNEL_SUPPORTED)
		ft_attr.flags |= (MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT |
				  MLX5_FLOW_TABLE_TUNNEL_EN_DECAP);

	sz = (chain == mlx5_chains_get_nf_ft_chain(chains)) ?
	     mlx5_chains_get_avail_sz_from_pool(chains, FT_TBL_SZ) :
	     mlx5_chains_get_avail_sz_from_pool(chains, POOL_NEXT_SIZE);
	अगर (!sz)
		वापस ERR_PTR(-ENOSPC);
	ft_attr.max_fte = sz;

	/* We use tc_शेष_ft(chains) as the table's next_ft till
	 * ignore_flow_level is allowed on FT creation and not just क्रम FTEs.
	 * Instead caller should add an explicit miss rule अगर needed.
	 */
	ft_attr.next_ft = tc_शेष_ft(chains);

	/* The root table(chain 0, prio 1, level 0) is required to be
	 * connected to the previous fs_core managed prio.
	 * We always create it, as a managed table, in order to align with
	 * fs_core logic.
	 */
	अगर (!mlx5_chains_ignore_flow_level_supported(chains) ||
	    (chain == 0 && prio == 1 && level == 0)) अणु
		ft_attr.level = level;
		ft_attr.prio = prio - 1;
		ns = (chains->ns == MLX5_FLOW_NAMESPACE_FDB) ?
			mlx5_get_fdb_sub_ns(chains->dev, chain) :
			mlx5_get_flow_namespace(chains->dev, chains->ns);
	पूर्ण अन्यथा अणु
		ft_attr.flags |= MLX5_FLOW_TABLE_UNMANAGED;
		ft_attr.prio = ns_to_chains_fs_prio(chains->ns);
		/* Firmware करोesn't allow us to create another level 0 table,
		 * so we create all unmanaged tables as level 1.
		 *
		 * To connect them, we use explicit miss rules with
		 * ignore_flow_level. Caller is responsible to create
		 * these rules (अगर needed).
		 */
		ft_attr.level = 1;
		ns = mlx5_get_flow_namespace(chains->dev, chains->ns);
	पूर्ण

	ft_attr.स्वतःgroup.num_reserved_entries = 2;
	ft_attr.स्वतःgroup.max_num_groups = chains->group_num;
	ft = mlx5_create_स्वतः_grouped_flow_table(ns, &ft_attr);
	अगर (IS_ERR(ft)) अणु
		mlx5_core_warn(chains->dev, "Failed to create chains table err %d (chain: %d, prio: %d, level: %d, size: %d)\n",
			       (पूर्णांक)PTR_ERR(ft), chain, prio, level, sz);
		mlx5_chains_put_sz_to_pool(chains, sz);
		वापस ft;
	पूर्ण

	वापस ft;
पूर्ण

अटल व्योम
mlx5_chains_destroy_table(काष्ठा mlx5_fs_chains *chains,
			  काष्ठा mlx5_flow_table *ft)
अणु
	mlx5_chains_put_sz_to_pool(chains, ft->max_fte);
	mlx5_destroy_flow_table(ft);
पूर्ण

अटल पूर्णांक
create_chain_restore(काष्ठा fs_chain *chain)
अणु
	काष्ठा mlx5_eचयन *esw = chain->chains->dev->priv.eचयन;
	अक्षर modact[MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः)];
	काष्ठा mlx5_fs_chains *chains = chain->chains;
	क्रमागत mlx5e_tc_attr_to_reg chain_to_reg;
	काष्ठा mlx5_modअगरy_hdr *mod_hdr;
	u32 index;
	पूर्णांक err;

	अगर (chain->chain == mlx5_chains_get_nf_ft_chain(chains) ||
	    !mlx5_chains_prios_supported(chains))
		वापस 0;

	err = mlx5_chains_get_chain_mapping(chains, chain->chain, &index);
	अगर (err)
		वापस err;
	अगर (index == MLX5_FS_DEFAULT_FLOW_TAG) अणु
		/* we got the special शेष flow tag id, so we won't know
		 * अगर we actually marked the packet with the restore rule
		 * we create.
		 *
		 * This हाल isn't possible with MLX5_FS_DEFAULT_FLOW_TAG = 0.
		 */
		err = mlx5_chains_get_chain_mapping(chains, chain->chain, &index);
		mapping_हटाओ(chains->chains_mapping, MLX5_FS_DEFAULT_FLOW_TAG);
		अगर (err)
			वापस err;
	पूर्ण

	chain->id = index;

	अगर (chains->ns == MLX5_FLOW_NAMESPACE_FDB) अणु
		chain_to_reg = CHAIN_TO_REG;
		chain->restore_rule = esw_add_restore_rule(esw, chain->id);
		अगर (IS_ERR(chain->restore_rule)) अणु
			err = PTR_ERR(chain->restore_rule);
			जाओ err_rule;
		पूर्ण
	पूर्ण अन्यथा अगर (chains->ns == MLX5_FLOW_NAMESPACE_KERNEL) अणु
		/* For NIC RX we करोn't need a restore rule
		 * since we ग_लिखो the metadata to reg_b
		 * that is passed to SW directly.
		 */
		chain_to_reg = NIC_CHAIN_TO_REG;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		जाओ err_rule;
	पूर्ण

	MLX5_SET(set_action_in, modact, action_type, MLX5_ACTION_TYPE_SET);
	MLX5_SET(set_action_in, modact, field,
		 mlx5e_tc_attr_to_reg_mappings[chain_to_reg].mfield);
	MLX5_SET(set_action_in, modact, offset,
		 mlx5e_tc_attr_to_reg_mappings[chain_to_reg].moffset * 8);
	MLX5_SET(set_action_in, modact, length,
		 mlx5e_tc_attr_to_reg_mappings[chain_to_reg].mlen * 8);
	MLX5_SET(set_action_in, modact, data, chain->id);
	mod_hdr = mlx5_modअगरy_header_alloc(chains->dev, chains->ns,
					   1, modact);
	अगर (IS_ERR(mod_hdr)) अणु
		err = PTR_ERR(mod_hdr);
		जाओ err_mod_hdr;
	पूर्ण
	chain->miss_modअगरy_hdr = mod_hdr;

	वापस 0;

err_mod_hdr:
	अगर (!IS_ERR_OR_शून्य(chain->restore_rule))
		mlx5_del_flow_rules(chain->restore_rule);
err_rule:
	/* Datapath can't find this mapping, so we can safely हटाओ it */
	mapping_हटाओ(chains->chains_mapping, chain->id);
	वापस err;
पूर्ण

अटल व्योम destroy_chain_restore(काष्ठा fs_chain *chain)
अणु
	काष्ठा mlx5_fs_chains *chains = chain->chains;

	अगर (!chain->miss_modअगरy_hdr)
		वापस;

	अगर (chain->restore_rule)
		mlx5_del_flow_rules(chain->restore_rule);

	mlx5_modअगरy_header_dealloc(chains->dev, chain->miss_modअगरy_hdr);
	mapping_हटाओ(chains->chains_mapping, chain->id);
पूर्ण

अटल काष्ठा fs_chain *
mlx5_chains_create_chain(काष्ठा mlx5_fs_chains *chains, u32 chain)
अणु
	काष्ठा fs_chain *chain_s = शून्य;
	पूर्णांक err;

	chain_s = kvzalloc(माप(*chain_s), GFP_KERNEL);
	अगर (!chain_s)
		वापस ERR_PTR(-ENOMEM);

	chain_s->chains = chains;
	chain_s->chain = chain;
	INIT_LIST_HEAD(&chain_s->prios_list);

	err = create_chain_restore(chain_s);
	अगर (err)
		जाओ err_restore;

	err = rhashtable_insert_fast(&chains_ht(chains), &chain_s->node,
				     chain_params);
	अगर (err)
		जाओ err_insert;

	वापस chain_s;

err_insert:
	destroy_chain_restore(chain_s);
err_restore:
	kvमुक्त(chain_s);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlx5_chains_destroy_chain(काष्ठा fs_chain *chain)
अणु
	काष्ठा mlx5_fs_chains *chains = chain->chains;

	rhashtable_हटाओ_fast(&chains_ht(chains), &chain->node,
			       chain_params);

	destroy_chain_restore(chain);
	kvमुक्त(chain);
पूर्ण

अटल काष्ठा fs_chain *
mlx5_chains_get_chain(काष्ठा mlx5_fs_chains *chains, u32 chain)
अणु
	काष्ठा fs_chain *chain_s;

	chain_s = rhashtable_lookup_fast(&chains_ht(chains), &chain,
					 chain_params);
	अगर (!chain_s) अणु
		chain_s = mlx5_chains_create_chain(chains, chain);
		अगर (IS_ERR(chain_s))
			वापस chain_s;
	पूर्ण

	chain_s->ref++;

	वापस chain_s;
पूर्ण

अटल काष्ठा mlx5_flow_handle *
mlx5_chains_add_miss_rule(काष्ठा fs_chain *chain,
			  काष्ठा mlx5_flow_table *ft,
			  काष्ठा mlx5_flow_table *next_ft)
अणु
	काष्ठा mlx5_fs_chains *chains = chain->chains;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_act act = अणुपूर्ण;

	act.flags  = FLOW_ACT_NO_APPEND;
	अगर (mlx5_chains_ignore_flow_level_supported(chain->chains))
		act.flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;

	act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	dest.type  = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = next_ft;

	अगर (next_ft == tc_end_ft(chains) &&
	    chain->chain != mlx5_chains_get_nf_ft_chain(chains) &&
	    mlx5_chains_prios_supported(chains)) अणु
		act.modअगरy_hdr = chain->miss_modअगरy_hdr;
		act.action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
	पूर्ण

	वापस mlx5_add_flow_rules(ft, शून्य, &act, &dest, 1);
पूर्ण

अटल पूर्णांक
mlx5_chains_update_prio_prevs(काष्ठा prio *prio,
			      काष्ठा mlx5_flow_table *next_ft)
अणु
	काष्ठा mlx5_flow_handle *miss_rules[FDB_TC_LEVELS_PER_PRIO + 1] = अणुपूर्ण;
	काष्ठा fs_chain *chain = prio->chain;
	काष्ठा prio *pos;
	पूर्णांक n = 0, err;

	अगर (prio->key.level)
		वापस 0;

	/* Iterate in reverse order until reaching the level 0 rule of
	 * the previous priority, adding all the miss rules first, so we can
	 * revert them अगर any of them fails.
	 */
	pos = prio;
	list_क्रम_each_entry_जारी_reverse(pos,
					     &chain->prios_list,
					     list) अणु
		miss_rules[n] = mlx5_chains_add_miss_rule(chain,
							  pos->ft,
							  next_ft);
		अगर (IS_ERR(miss_rules[n])) अणु
			err = PTR_ERR(miss_rules[n]);
			जाओ err_prev_rule;
		पूर्ण

		n++;
		अगर (!pos->key.level)
			अवरोध;
	पूर्ण

	/* Success, delete old miss rules, and update the poपूर्णांकers. */
	n = 0;
	pos = prio;
	list_क्रम_each_entry_जारी_reverse(pos,
					     &chain->prios_list,
					     list) अणु
		mlx5_del_flow_rules(pos->miss_rule);

		pos->miss_rule = miss_rules[n];
		pos->next_ft = next_ft;

		n++;
		अगर (!pos->key.level)
			अवरोध;
	पूर्ण

	वापस 0;

err_prev_rule:
	जबतक (--n >= 0)
		mlx5_del_flow_rules(miss_rules[n]);

	वापस err;
पूर्ण

अटल व्योम
mlx5_chains_put_chain(काष्ठा fs_chain *chain)
अणु
	अगर (--chain->ref == 0)
		mlx5_chains_destroy_chain(chain);
पूर्ण

अटल काष्ठा prio *
mlx5_chains_create_prio(काष्ठा mlx5_fs_chains *chains,
			u32 chain, u32 prio, u32 level)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_handle *miss_rule;
	काष्ठा mlx5_flow_group *miss_group;
	काष्ठा mlx5_flow_table *next_ft;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा fs_chain *chain_s;
	काष्ठा list_head *pos;
	काष्ठा prio *prio_s;
	u32 *flow_group_in;
	पूर्णांक err;

	chain_s = mlx5_chains_get_chain(chains, chain);
	अगर (IS_ERR(chain_s))
		वापस ERR_CAST(chain_s);

	prio_s = kvzalloc(माप(*prio_s), GFP_KERNEL);
	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!prio_s || !flow_group_in) अणु
		err = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	/* Chain's prio list is sorted by prio and level.
	 * And all levels of some prio poपूर्णांक to the next prio's level 0.
	 * Example list (prio, level):
	 * (3,0)->(3,1)->(5,0)->(5,1)->(6,1)->(7,0)
	 * In hardware, we will we have the following poपूर्णांकers:
	 * (3,0) -> (5,0) -> (7,0) -> Slow path
	 * (3,1) -> (5,0)
	 * (5,1) -> (7,0)
	 * (6,1) -> (7,0)
	 */

	/* Default miss क्रम each chain: */
	next_ft = (chain == mlx5_chains_get_nf_ft_chain(chains)) ?
		  tc_शेष_ft(chains) :
		  tc_end_ft(chains);
	list_क्रम_each(pos, &chain_s->prios_list) अणु
		काष्ठा prio *p = list_entry(pos, काष्ठा prio, list);

		/* निकास on first pos that is larger */
		अगर (prio < p->key.prio || (prio == p->key.prio &&
					   level < p->key.level)) अणु
			/* Get next level 0 table */
			next_ft = p->key.level == 0 ? p->ft : p->next_ft;
			अवरोध;
		पूर्ण
	पूर्ण

	ft = mlx5_chains_create_table(chains, chain, prio, level);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		जाओ err_create;
	पूर्ण

	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index,
		 ft->max_fte - 2);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index,
		 ft->max_fte - 1);
	miss_group = mlx5_create_flow_group(ft, flow_group_in);
	अगर (IS_ERR(miss_group)) अणु
		err = PTR_ERR(miss_group);
		जाओ err_group;
	पूर्ण

	/* Add miss rule to next_ft */
	miss_rule = mlx5_chains_add_miss_rule(chain_s, ft, next_ft);
	अगर (IS_ERR(miss_rule)) अणु
		err = PTR_ERR(miss_rule);
		जाओ err_miss_rule;
	पूर्ण

	prio_s->miss_group = miss_group;
	prio_s->miss_rule = miss_rule;
	prio_s->next_ft = next_ft;
	prio_s->chain = chain_s;
	prio_s->key.chain = chain;
	prio_s->key.prio = prio;
	prio_s->key.level = level;
	prio_s->ft = ft;

	err = rhashtable_insert_fast(&prios_ht(chains), &prio_s->node,
				     prio_params);
	अगर (err)
		जाओ err_insert;

	list_add(&prio_s->list, pos->prev);

	/* Table is पढ़ोy, connect it */
	err = mlx5_chains_update_prio_prevs(prio_s, ft);
	अगर (err)
		जाओ err_update;

	kvमुक्त(flow_group_in);
	वापस prio_s;

err_update:
	list_del(&prio_s->list);
	rhashtable_हटाओ_fast(&prios_ht(chains), &prio_s->node,
			       prio_params);
err_insert:
	mlx5_del_flow_rules(miss_rule);
err_miss_rule:
	mlx5_destroy_flow_group(miss_group);
err_group:
	mlx5_chains_destroy_table(chains, ft);
err_create:
err_alloc:
	kvमुक्त(prio_s);
	kvमुक्त(flow_group_in);
	mlx5_chains_put_chain(chain_s);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlx5_chains_destroy_prio(काष्ठा mlx5_fs_chains *chains,
			 काष्ठा prio *prio)
अणु
	काष्ठा fs_chain *chain = prio->chain;

	WARN_ON(mlx5_chains_update_prio_prevs(prio,
					      prio->next_ft));

	list_del(&prio->list);
	rhashtable_हटाओ_fast(&prios_ht(chains), &prio->node,
			       prio_params);
	mlx5_del_flow_rules(prio->miss_rule);
	mlx5_destroy_flow_group(prio->miss_group);
	mlx5_chains_destroy_table(chains, prio->ft);
	mlx5_chains_put_chain(chain);
	kvमुक्त(prio);
पूर्ण

काष्ठा mlx5_flow_table *
mlx5_chains_get_table(काष्ठा mlx5_fs_chains *chains, u32 chain, u32 prio,
		      u32 level)
अणु
	काष्ठा mlx5_flow_table *prev_fts;
	काष्ठा prio *prio_s;
	काष्ठा prio_key key;
	पूर्णांक l = 0;

	अगर ((chain > mlx5_chains_get_chain_range(chains) &&
	     chain != mlx5_chains_get_nf_ft_chain(chains)) ||
	    prio > mlx5_chains_get_prio_range(chains) ||
	    level > mlx5_chains_get_level_range(chains))
		वापस ERR_PTR(-EOPNOTSUPP);

	/* create earlier levels क्रम correct fs_core lookup when
	 * connecting tables.
	 */
	क्रम (l = 0; l < level; l++) अणु
		prev_fts = mlx5_chains_get_table(chains, chain, prio, l);
		अगर (IS_ERR(prev_fts)) अणु
			prio_s = ERR_CAST(prev_fts);
			जाओ err_get_prevs;
		पूर्ण
	पूर्ण

	key.chain = chain;
	key.prio = prio;
	key.level = level;

	mutex_lock(&chains_lock(chains));
	prio_s = rhashtable_lookup_fast(&prios_ht(chains), &key,
					prio_params);
	अगर (!prio_s) अणु
		prio_s = mlx5_chains_create_prio(chains, chain,
						 prio, level);
		अगर (IS_ERR(prio_s))
			जाओ err_create_prio;
	पूर्ण

	++prio_s->ref;
	mutex_unlock(&chains_lock(chains));

	वापस prio_s->ft;

err_create_prio:
	mutex_unlock(&chains_lock(chains));
err_get_prevs:
	जबतक (--l >= 0)
		mlx5_chains_put_table(chains, chain, prio, l);
	वापस ERR_CAST(prio_s);
पूर्ण

व्योम
mlx5_chains_put_table(काष्ठा mlx5_fs_chains *chains, u32 chain, u32 prio,
		      u32 level)
अणु
	काष्ठा prio *prio_s;
	काष्ठा prio_key key;

	key.chain = chain;
	key.prio = prio;
	key.level = level;

	mutex_lock(&chains_lock(chains));
	prio_s = rhashtable_lookup_fast(&prios_ht(chains), &key,
					prio_params);
	अगर (!prio_s)
		जाओ err_get_prio;

	अगर (--prio_s->ref == 0)
		mlx5_chains_destroy_prio(chains, prio_s);
	mutex_unlock(&chains_lock(chains));

	जबतक (level-- > 0)
		mlx5_chains_put_table(chains, chain, prio, level);

	वापस;

err_get_prio:
	mutex_unlock(&chains_lock(chains));
	WARN_ONCE(1,
		  "Couldn't find table: (chain: %d prio: %d level: %d)",
		  chain, prio, level);
पूर्ण

काष्ठा mlx5_flow_table *
mlx5_chains_get_tc_end_ft(काष्ठा mlx5_fs_chains *chains)
अणु
	वापस tc_end_ft(chains);
पूर्ण

काष्ठा mlx5_flow_table *
mlx5_chains_create_global_table(काष्ठा mlx5_fs_chains *chains)
अणु
	u32 chain, prio, level;
	पूर्णांक err;

	अगर (!mlx5_chains_ignore_flow_level_supported(chains)) अणु
		err = -EOPNOTSUPP;

		mlx5_core_warn(chains->dev,
			       "Couldn't create global flow table, ignore_flow_level not supported.");
		जाओ err_ignore;
	पूर्ण

	chain = mlx5_chains_get_chain_range(chains),
	prio = mlx5_chains_get_prio_range(chains);
	level = mlx5_chains_get_level_range(chains);

	वापस mlx5_chains_create_table(chains, chain, prio, level);

err_ignore:
	वापस ERR_PTR(err);
पूर्ण

व्योम
mlx5_chains_destroy_global_table(काष्ठा mlx5_fs_chains *chains,
				 काष्ठा mlx5_flow_table *ft)
अणु
	mlx5_chains_destroy_table(chains, ft);
पूर्ण

अटल काष्ठा mlx5_fs_chains *
mlx5_chains_init(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_chains_attr *attr)
अणु
	काष्ठा mlx5_fs_chains *chains_priv;
	u32 max_flow_counter;
	पूर्णांक err;

	chains_priv = kzalloc(माप(*chains_priv), GFP_KERNEL);
	अगर (!chains_priv)
		वापस ERR_PTR(-ENOMEM);

	max_flow_counter = (MLX5_CAP_GEN(dev, max_flow_counter_31_16) << 16) |
			    MLX5_CAP_GEN(dev, max_flow_counter_15_0);

	mlx5_core_dbg(dev,
		      "Init flow table chains, max counters(%d), groups(%d), max flow table size(%d)\n",
		      max_flow_counter, attr->max_grp_num, attr->max_ft_sz);

	chains_priv->dev = dev;
	chains_priv->flags = attr->flags;
	chains_priv->ns = attr->ns;
	chains_priv->group_num = attr->max_grp_num;
	chains_priv->chains_mapping = attr->mapping;
	tc_शेष_ft(chains_priv) = tc_end_ft(chains_priv) = attr->शेष_ft;

	mlx5_core_info(dev, "Supported tc offload range - chains: %u, prios: %u\n",
		       mlx5_chains_get_chain_range(chains_priv),
		       mlx5_chains_get_prio_range(chains_priv));

	mlx5_chains_init_sz_pool(chains_priv, attr->max_ft_sz);

	err = rhashtable_init(&chains_ht(chains_priv), &chain_params);
	अगर (err)
		जाओ init_chains_ht_err;

	err = rhashtable_init(&prios_ht(chains_priv), &prio_params);
	अगर (err)
		जाओ init_prios_ht_err;

	mutex_init(&chains_lock(chains_priv));

	वापस chains_priv;

init_prios_ht_err:
	rhashtable_destroy(&chains_ht(chains_priv));
init_chains_ht_err:
	kमुक्त(chains_priv);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlx5_chains_cleanup(काष्ठा mlx5_fs_chains *chains)
अणु
	mutex_destroy(&chains_lock(chains));
	rhashtable_destroy(&prios_ht(chains));
	rhashtable_destroy(&chains_ht(chains));

	kमुक्त(chains);
पूर्ण

काष्ठा mlx5_fs_chains *
mlx5_chains_create(काष्ठा mlx5_core_dev *dev, काष्ठा mlx5_chains_attr *attr)
अणु
	काष्ठा mlx5_fs_chains *chains;

	chains = mlx5_chains_init(dev, attr);

	वापस chains;
पूर्ण

व्योम
mlx5_chains_destroy(काष्ठा mlx5_fs_chains *chains)
अणु
	mlx5_chains_cleanup(chains);
पूर्ण

पूर्णांक
mlx5_chains_get_chain_mapping(काष्ठा mlx5_fs_chains *chains, u32 chain,
			      u32 *chain_mapping)
अणु
	काष्ठा mapping_ctx *ctx = chains->chains_mapping;
	काष्ठा mlx5_mapped_obj mapped_obj = अणुपूर्ण;

	mapped_obj.type = MLX5_MAPPED_OBJ_CHAIN;
	mapped_obj.chain = chain;
	वापस mapping_add(ctx, &mapped_obj, chain_mapping);
पूर्ण

पूर्णांक
mlx5_chains_put_chain_mapping(काष्ठा mlx5_fs_chains *chains, u32 chain_mapping)
अणु
	काष्ठा mapping_ctx *ctx = chains->chains_mapping;

	वापस mapping_हटाओ(ctx, chain_mapping);
पूर्ण
