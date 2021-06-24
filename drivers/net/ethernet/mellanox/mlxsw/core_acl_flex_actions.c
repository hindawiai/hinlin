<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/rhashtable.h>
#समावेश <linux/list.h>
#समावेश <linux/idr.h>
#समावेश <linux/refcount.h>
#समावेश <net/flow_offload.h>

#समावेश "item.h"
#समावेश "trap.h"
#समावेश "core_acl_flex_actions.h"

क्रमागत mlxsw_afa_set_type अणु
	MLXSW_AFA_SET_TYPE_NEXT,
	MLXSW_AFA_SET_TYPE_GOTO,
पूर्ण;

/* afa_set_type
 * Type of the record at the end of the action set.
 */
MLXSW_ITEM32(afa, set, type, 0xA0, 28, 4);

/* afa_set_next_action_set_ptr
 * A poपूर्णांकer to the next action set in the KVD Centralized database.
 */
MLXSW_ITEM32(afa, set, next_action_set_ptr, 0xA4, 0, 24);

/* afa_set_जाओ_g
 * group - When set, the binding is of an ACL group. When cleared,
 * the binding is of an ACL.
 * Must be set to 1 क्रम Spectrum.
 */
MLXSW_ITEM32(afa, set, जाओ_g, 0xA4, 29, 1);

क्रमागत mlxsw_afa_set_जाओ_binding_cmd अणु
	/* जारी go the next binding poपूर्णांक */
	MLXSW_AFA_SET_GOTO_BINDING_CMD_NONE,
	/* jump to the next binding poपूर्णांक no वापस */
	MLXSW_AFA_SET_GOTO_BINDING_CMD_JUMP,
	/* terminate the acl binding */
	MLXSW_AFA_SET_GOTO_BINDING_CMD_TERM = 4,
पूर्ण;

/* afa_set_जाओ_binding_cmd */
MLXSW_ITEM32(afa, set, जाओ_binding_cmd, 0xA4, 24, 3);

/* afa_set_जाओ_next_binding
 * ACL/ACL group identअगरier. If the g bit is set, this field should hold
 * the acl_group_id, अन्यथा it should hold the acl_id.
 */
MLXSW_ITEM32(afa, set, जाओ_next_binding, 0xA4, 0, 16);

/* afa_all_action_type
 * Action Type.
 */
MLXSW_ITEM32(afa, all, action_type, 0x00, 24, 6);

काष्ठा mlxsw_afa अणु
	अचिन्हित पूर्णांक max_acts_per_set;
	स्थिर काष्ठा mlxsw_afa_ops *ops;
	व्योम *ops_priv;
	काष्ठा rhashtable set_ht;
	काष्ठा rhashtable fwd_entry_ht;
	काष्ठा rhashtable cookie_ht;
	काष्ठा rhashtable policer_ht;
	काष्ठा idr cookie_idr;
	काष्ठा list_head policer_list;
पूर्ण;

#घोषणा MLXSW_AFA_SET_LEN 0xA8

काष्ठा mlxsw_afa_set_ht_key अणु
	अक्षर enc_actions[MLXSW_AFA_SET_LEN]; /* Encoded set */
	bool is_first;
पूर्ण;

/* Set काष्ठाure holds one action set record. It contains up to three
 * actions (depends on size of particular actions). The set is either
 * put directly to a rule, or it is stored in KVD linear area.
 * To prevent duplicate entries in KVD linear area, a hashtable is
 * used to track sets that were previously inserted and may be shared.
 */

काष्ठा mlxsw_afa_set अणु
	काष्ठा rhash_head ht_node;
	काष्ठा mlxsw_afa_set_ht_key ht_key;
	u32 kvdl_index;
	u8 shared:1, /* Inserted in hashtable (करोesn't mean that
		      * kvdl_index is valid).
		      */
	   has_trap:1,
	   has_police:1;
	अचिन्हित पूर्णांक ref_count;
	काष्ठा mlxsw_afa_set *next; /* Poपूर्णांकer to the next set. */
	काष्ठा mlxsw_afa_set *prev; /* Poपूर्णांकer to the previous set,
				     * note that set may have multiple
				     * sets from multiple blocks
				     * poपूर्णांकing at it. This is only
				     * usable until commit.
				     */
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_afa_set_ht_params = अणु
	.key_len = माप(काष्ठा mlxsw_afa_set_ht_key),
	.key_offset = दुरत्व(काष्ठा mlxsw_afa_set, ht_key),
	.head_offset = दुरत्व(काष्ठा mlxsw_afa_set, ht_node),
	.स्वतःmatic_shrinking = true,
पूर्ण;

काष्ठा mlxsw_afa_fwd_entry_ht_key अणु
	u8 local_port;
पूर्ण;

काष्ठा mlxsw_afa_fwd_entry अणु
	काष्ठा rhash_head ht_node;
	काष्ठा mlxsw_afa_fwd_entry_ht_key ht_key;
	u32 kvdl_index;
	अचिन्हित पूर्णांक ref_count;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_afa_fwd_entry_ht_params = अणु
	.key_len = माप(काष्ठा mlxsw_afa_fwd_entry_ht_key),
	.key_offset = दुरत्व(काष्ठा mlxsw_afa_fwd_entry, ht_key),
	.head_offset = दुरत्व(काष्ठा mlxsw_afa_fwd_entry, ht_node),
	.स्वतःmatic_shrinking = true,
पूर्ण;

काष्ठा mlxsw_afa_cookie अणु
	काष्ठा rhash_head ht_node;
	refcount_t ref_count;
	काष्ठा rcu_head rcu;
	u32 cookie_index;
	काष्ठा flow_action_cookie fa_cookie;
पूर्ण;

अटल u32 mlxsw_afa_cookie_hash(स्थिर काष्ठा flow_action_cookie *fa_cookie,
				 u32 seed)
अणु
	वापस jhash2((u32 *) fa_cookie->cookie,
		      fa_cookie->cookie_len / माप(u32), seed);
पूर्ण

अटल u32 mlxsw_afa_cookie_key_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा flow_action_cookie *fa_cookie = data;

	वापस mlxsw_afa_cookie_hash(fa_cookie, seed);
पूर्ण

अटल u32 mlxsw_afa_cookie_obj_hashfn(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा mlxsw_afa_cookie *cookie = data;

	वापस mlxsw_afa_cookie_hash(&cookie->fa_cookie, seed);
पूर्ण

अटल पूर्णांक mlxsw_afa_cookie_obj_cmpfn(काष्ठा rhashtable_compare_arg *arg,
				      स्थिर व्योम *obj)
अणु
	स्थिर काष्ठा flow_action_cookie *fa_cookie = arg->key;
	स्थिर काष्ठा mlxsw_afa_cookie *cookie = obj;

	अगर (cookie->fa_cookie.cookie_len == fa_cookie->cookie_len)
		वापस स_भेद(cookie->fa_cookie.cookie, fa_cookie->cookie,
			      fa_cookie->cookie_len);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params mlxsw_afa_cookie_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा mlxsw_afa_cookie, ht_node),
	.hashfn	= mlxsw_afa_cookie_key_hashfn,
	.obj_hashfn = mlxsw_afa_cookie_obj_hashfn,
	.obj_cmpfn = mlxsw_afa_cookie_obj_cmpfn,
	.स्वतःmatic_shrinking = true,
पूर्ण;

काष्ठा mlxsw_afa_policer अणु
	काष्ठा rhash_head ht_node;
	काष्ठा list_head list; /* Member of policer_list */
	refcount_t ref_count;
	u32 fa_index;
	u16 policer_index;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_afa_policer_ht_params = अणु
	.key_len = माप(u32),
	.key_offset = दुरत्व(काष्ठा mlxsw_afa_policer, fa_index),
	.head_offset = दुरत्व(काष्ठा mlxsw_afa_policer, ht_node),
	.स्वतःmatic_shrinking = true,
पूर्ण;

काष्ठा mlxsw_afa *mlxsw_afa_create(अचिन्हित पूर्णांक max_acts_per_set,
				   स्थिर काष्ठा mlxsw_afa_ops *ops,
				   व्योम *ops_priv)
अणु
	काष्ठा mlxsw_afa *mlxsw_afa;
	पूर्णांक err;

	mlxsw_afa = kzalloc(माप(*mlxsw_afa), GFP_KERNEL);
	अगर (!mlxsw_afa)
		वापस ERR_PTR(-ENOMEM);
	err = rhashtable_init(&mlxsw_afa->set_ht, &mlxsw_afa_set_ht_params);
	अगर (err)
		जाओ err_set_rhashtable_init;
	err = rhashtable_init(&mlxsw_afa->fwd_entry_ht,
			      &mlxsw_afa_fwd_entry_ht_params);
	अगर (err)
		जाओ err_fwd_entry_rhashtable_init;
	err = rhashtable_init(&mlxsw_afa->cookie_ht,
			      &mlxsw_afa_cookie_ht_params);
	अगर (err)
		जाओ err_cookie_rhashtable_init;
	err = rhashtable_init(&mlxsw_afa->policer_ht,
			      &mlxsw_afa_policer_ht_params);
	अगर (err)
		जाओ err_policer_rhashtable_init;
	idr_init(&mlxsw_afa->cookie_idr);
	INIT_LIST_HEAD(&mlxsw_afa->policer_list);
	mlxsw_afa->max_acts_per_set = max_acts_per_set;
	mlxsw_afa->ops = ops;
	mlxsw_afa->ops_priv = ops_priv;
	वापस mlxsw_afa;

err_policer_rhashtable_init:
	rhashtable_destroy(&mlxsw_afa->cookie_ht);
err_cookie_rhashtable_init:
	rhashtable_destroy(&mlxsw_afa->fwd_entry_ht);
err_fwd_entry_rhashtable_init:
	rhashtable_destroy(&mlxsw_afa->set_ht);
err_set_rhashtable_init:
	kमुक्त(mlxsw_afa);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_create);

व्योम mlxsw_afa_destroy(काष्ठा mlxsw_afa *mlxsw_afa)
अणु
	WARN_ON(!list_empty(&mlxsw_afa->policer_list));
	WARN_ON(!idr_is_empty(&mlxsw_afa->cookie_idr));
	idr_destroy(&mlxsw_afa->cookie_idr);
	rhashtable_destroy(&mlxsw_afa->policer_ht);
	rhashtable_destroy(&mlxsw_afa->cookie_ht);
	rhashtable_destroy(&mlxsw_afa->fwd_entry_ht);
	rhashtable_destroy(&mlxsw_afa->set_ht);
	kमुक्त(mlxsw_afa);
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_destroy);

अटल व्योम mlxsw_afa_set_जाओ_set(काष्ठा mlxsw_afa_set *set,
				   क्रमागत mlxsw_afa_set_जाओ_binding_cmd cmd,
				   u16 group_id)
अणु
	अक्षर *actions = set->ht_key.enc_actions;

	mlxsw_afa_set_type_set(actions, MLXSW_AFA_SET_TYPE_GOTO);
	mlxsw_afa_set_जाओ_g_set(actions, true);
	mlxsw_afa_set_जाओ_binding_cmd_set(actions, cmd);
	mlxsw_afa_set_जाओ_next_binding_set(actions, group_id);
पूर्ण

अटल व्योम mlxsw_afa_set_next_set(काष्ठा mlxsw_afa_set *set,
				   u32 next_set_kvdl_index)
अणु
	अक्षर *actions = set->ht_key.enc_actions;

	mlxsw_afa_set_type_set(actions, MLXSW_AFA_SET_TYPE_NEXT);
	mlxsw_afa_set_next_action_set_ptr_set(actions, next_set_kvdl_index);
पूर्ण

अटल काष्ठा mlxsw_afa_set *mlxsw_afa_set_create(bool is_first)
अणु
	काष्ठा mlxsw_afa_set *set;

	set = kzalloc(माप(*set), GFP_KERNEL);
	अगर (!set)
		वापस शून्य;
	/* Need to initialize the set to pass by शेष */
	mlxsw_afa_set_जाओ_set(set, MLXSW_AFA_SET_GOTO_BINDING_CMD_TERM, 0);
	set->ht_key.is_first = is_first;
	set->ref_count = 1;
	वापस set;
पूर्ण

अटल व्योम mlxsw_afa_set_destroy(काष्ठा mlxsw_afa_set *set)
अणु
	kमुक्त(set);
पूर्ण

अटल पूर्णांक mlxsw_afa_set_share(काष्ठा mlxsw_afa *mlxsw_afa,
			       काष्ठा mlxsw_afa_set *set)
अणु
	पूर्णांक err;

	err = rhashtable_insert_fast(&mlxsw_afa->set_ht, &set->ht_node,
				     mlxsw_afa_set_ht_params);
	अगर (err)
		वापस err;
	err = mlxsw_afa->ops->kvdl_set_add(mlxsw_afa->ops_priv,
					   &set->kvdl_index,
					   set->ht_key.enc_actions,
					   set->ht_key.is_first);
	अगर (err)
		जाओ err_kvdl_set_add;
	set->shared = true;
	set->prev = शून्य;
	वापस 0;

err_kvdl_set_add:
	rhashtable_हटाओ_fast(&mlxsw_afa->set_ht, &set->ht_node,
			       mlxsw_afa_set_ht_params);
	वापस err;
पूर्ण

अटल व्योम mlxsw_afa_set_unshare(काष्ठा mlxsw_afa *mlxsw_afa,
				  काष्ठा mlxsw_afa_set *set)
अणु
	mlxsw_afa->ops->kvdl_set_del(mlxsw_afa->ops_priv,
				     set->kvdl_index,
				     set->ht_key.is_first);
	rhashtable_हटाओ_fast(&mlxsw_afa->set_ht, &set->ht_node,
			       mlxsw_afa_set_ht_params);
	set->shared = false;
पूर्ण

अटल व्योम mlxsw_afa_set_put(काष्ठा mlxsw_afa *mlxsw_afa,
			      काष्ठा mlxsw_afa_set *set)
अणु
	अगर (--set->ref_count)
		वापस;
	अगर (set->shared)
		mlxsw_afa_set_unshare(mlxsw_afa, set);
	mlxsw_afa_set_destroy(set);
पूर्ण

अटल काष्ठा mlxsw_afa_set *mlxsw_afa_set_get(काष्ठा mlxsw_afa *mlxsw_afa,
					       काष्ठा mlxsw_afa_set *orig_set)
अणु
	काष्ठा mlxsw_afa_set *set;
	पूर्णांक err;

	/* There is a hashtable of sets मुख्यtained. If a set with the exact
	 * same encoding exists, we reuse it. Otherwise, the current set
	 * is shared by making it available to others using the hash table.
	 */
	set = rhashtable_lookup_fast(&mlxsw_afa->set_ht, &orig_set->ht_key,
				     mlxsw_afa_set_ht_params);
	अगर (set) अणु
		set->ref_count++;
		mlxsw_afa_set_put(mlxsw_afa, orig_set);
	पूर्ण अन्यथा अणु
		set = orig_set;
		err = mlxsw_afa_set_share(mlxsw_afa, set);
		अगर (err)
			वापस ERR_PTR(err);
	पूर्ण
	वापस set;
पूर्ण

/* Block काष्ठाure holds a list of action sets. One action block
 * represents one chain of actions executed upon match of a rule.
 */

काष्ठा mlxsw_afa_block अणु
	काष्ठा mlxsw_afa *afa;
	bool finished;
	काष्ठा mlxsw_afa_set *first_set;
	काष्ठा mlxsw_afa_set *cur_set;
	अचिन्हित पूर्णांक cur_act_index; /* In current set. */
	काष्ठा list_head resource_list; /* List of resources held by actions
					 * in this block.
					 */
पूर्ण;

काष्ठा mlxsw_afa_resource अणु
	काष्ठा list_head list;
	व्योम (*deकाष्ठाor)(काष्ठा mlxsw_afa_block *block,
			   काष्ठा mlxsw_afa_resource *resource);
पूर्ण;

अटल व्योम mlxsw_afa_resource_add(काष्ठा mlxsw_afa_block *block,
				   काष्ठा mlxsw_afa_resource *resource)
अणु
	list_add(&resource->list, &block->resource_list);
पूर्ण

अटल व्योम mlxsw_afa_resource_del(काष्ठा mlxsw_afa_resource *resource)
अणु
	list_del(&resource->list);
पूर्ण

अटल व्योम mlxsw_afa_resources_destroy(काष्ठा mlxsw_afa_block *block)
अणु
	काष्ठा mlxsw_afa_resource *resource, *पंचांगp;

	list_क्रम_each_entry_safe(resource, पंचांगp, &block->resource_list, list) अणु
		resource->deकाष्ठाor(block, resource);
	पूर्ण
पूर्ण

काष्ठा mlxsw_afa_block *mlxsw_afa_block_create(काष्ठा mlxsw_afa *mlxsw_afa)
अणु
	काष्ठा mlxsw_afa_block *block;

	block = kzalloc(माप(*block), GFP_KERNEL);
	अगर (!block)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&block->resource_list);
	block->afa = mlxsw_afa;

	/* At least one action set is always present, so just create it here */
	block->first_set = mlxsw_afa_set_create(true);
	अगर (!block->first_set)
		जाओ err_first_set_create;

	/* In हाल user inकाष्ठाs to have dummy first set, we leave it
	 * empty here and create another, real, set right away.
	 */
	अगर (mlxsw_afa->ops->dummy_first_set) अणु
		block->cur_set = mlxsw_afa_set_create(false);
		अगर (!block->cur_set)
			जाओ err_second_set_create;
		block->cur_set->prev = block->first_set;
		block->first_set->next = block->cur_set;
	पूर्ण अन्यथा अणु
		block->cur_set = block->first_set;
	पूर्ण

	वापस block;

err_second_set_create:
	mlxsw_afa_set_destroy(block->first_set);
err_first_set_create:
	kमुक्त(block);
	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_create);

व्योम mlxsw_afa_block_destroy(काष्ठा mlxsw_afa_block *block)
अणु
	काष्ठा mlxsw_afa_set *set = block->first_set;
	काष्ठा mlxsw_afa_set *next_set;

	करो अणु
		next_set = set->next;
		mlxsw_afa_set_put(block->afa, set);
		set = next_set;
	पूर्ण जबतक (set);
	mlxsw_afa_resources_destroy(block);
	kमुक्त(block);
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_destroy);

पूर्णांक mlxsw_afa_block_commit(काष्ठा mlxsw_afa_block *block)
अणु
	काष्ठा mlxsw_afa_set *set = block->cur_set;
	काष्ठा mlxsw_afa_set *prev_set;

	block->cur_set = शून्य;
	block->finished = true;

	/* Go over all linked sets starting from last
	 * and try to find existing set in the hash table.
	 * In हाल it is not there, assign a KVD linear index
	 * and insert it.
	 */
	करो अणु
		prev_set = set->prev;
		set = mlxsw_afa_set_get(block->afa, set);
		अगर (IS_ERR(set))
			/* No rollback is needed since the chain is
			 * in consistent state and mlxsw_afa_block_destroy
			 * will take care of putting it away.
			 */
			वापस PTR_ERR(set);
		अगर (prev_set) अणु
			prev_set->next = set;
			mlxsw_afa_set_next_set(prev_set, set->kvdl_index);
			set = prev_set;
		पूर्ण
	पूर्ण जबतक (prev_set);

	block->first_set = set;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_commit);

अक्षर *mlxsw_afa_block_first_set(काष्ठा mlxsw_afa_block *block)
अणु
	वापस block->first_set->ht_key.enc_actions;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_first_set);

अक्षर *mlxsw_afa_block_cur_set(काष्ठा mlxsw_afa_block *block)
अणु
	वापस block->cur_set->ht_key.enc_actions;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_cur_set);

u32 mlxsw_afa_block_first_kvdl_index(काष्ठा mlxsw_afa_block *block)
अणु
	/* First set is never in KVD linear. So the first set
	 * with valid KVD linear index is always the second one.
	 */
	अगर (WARN_ON(!block->first_set->next))
		वापस 0;
	वापस block->first_set->next->kvdl_index;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_first_kvdl_index);

पूर्णांक mlxsw_afa_block_activity_get(काष्ठा mlxsw_afa_block *block, bool *activity)
अणु
	u32 kvdl_index = mlxsw_afa_block_first_kvdl_index(block);

	वापस block->afa->ops->kvdl_set_activity_get(block->afa->ops_priv,
						      kvdl_index, activity);
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_activity_get);

पूर्णांक mlxsw_afa_block_जारी(काष्ठा mlxsw_afa_block *block)
अणु
	अगर (block->finished)
		वापस -EINVAL;
	mlxsw_afa_set_जाओ_set(block->cur_set,
			       MLXSW_AFA_SET_GOTO_BINDING_CMD_NONE, 0);
	block->finished = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_जारी);

पूर्णांक mlxsw_afa_block_jump(काष्ठा mlxsw_afa_block *block, u16 group_id)
अणु
	अगर (block->finished)
		वापस -EINVAL;
	mlxsw_afa_set_जाओ_set(block->cur_set,
			       MLXSW_AFA_SET_GOTO_BINDING_CMD_JUMP, group_id);
	block->finished = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_jump);

पूर्णांक mlxsw_afa_block_terminate(काष्ठा mlxsw_afa_block *block)
अणु
	अगर (block->finished)
		वापस -EINVAL;
	mlxsw_afa_set_जाओ_set(block->cur_set,
			       MLXSW_AFA_SET_GOTO_BINDING_CMD_TERM, 0);
	block->finished = true;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_terminate);

अटल काष्ठा mlxsw_afa_fwd_entry *
mlxsw_afa_fwd_entry_create(काष्ठा mlxsw_afa *mlxsw_afa, u8 local_port)
अणु
	काष्ठा mlxsw_afa_fwd_entry *fwd_entry;
	पूर्णांक err;

	fwd_entry = kzalloc(माप(*fwd_entry), GFP_KERNEL);
	अगर (!fwd_entry)
		वापस ERR_PTR(-ENOMEM);
	fwd_entry->ht_key.local_port = local_port;
	fwd_entry->ref_count = 1;

	err = rhashtable_insert_fast(&mlxsw_afa->fwd_entry_ht,
				     &fwd_entry->ht_node,
				     mlxsw_afa_fwd_entry_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	err = mlxsw_afa->ops->kvdl_fwd_entry_add(mlxsw_afa->ops_priv,
						 &fwd_entry->kvdl_index,
						 local_port);
	अगर (err)
		जाओ err_kvdl_fwd_entry_add;
	वापस fwd_entry;

err_kvdl_fwd_entry_add:
	rhashtable_हटाओ_fast(&mlxsw_afa->fwd_entry_ht, &fwd_entry->ht_node,
			       mlxsw_afa_fwd_entry_ht_params);
err_rhashtable_insert:
	kमुक्त(fwd_entry);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_afa_fwd_entry_destroy(काष्ठा mlxsw_afa *mlxsw_afa,
					काष्ठा mlxsw_afa_fwd_entry *fwd_entry)
अणु
	mlxsw_afa->ops->kvdl_fwd_entry_del(mlxsw_afa->ops_priv,
					   fwd_entry->kvdl_index);
	rhashtable_हटाओ_fast(&mlxsw_afa->fwd_entry_ht, &fwd_entry->ht_node,
			       mlxsw_afa_fwd_entry_ht_params);
	kमुक्त(fwd_entry);
पूर्ण

अटल काष्ठा mlxsw_afa_fwd_entry *
mlxsw_afa_fwd_entry_get(काष्ठा mlxsw_afa *mlxsw_afa, u8 local_port)
अणु
	काष्ठा mlxsw_afa_fwd_entry_ht_key ht_key = अणु0पूर्ण;
	काष्ठा mlxsw_afa_fwd_entry *fwd_entry;

	ht_key.local_port = local_port;
	fwd_entry = rhashtable_lookup_fast(&mlxsw_afa->fwd_entry_ht, &ht_key,
					   mlxsw_afa_fwd_entry_ht_params);
	अगर (fwd_entry) अणु
		fwd_entry->ref_count++;
		वापस fwd_entry;
	पूर्ण
	वापस mlxsw_afa_fwd_entry_create(mlxsw_afa, local_port);
पूर्ण

अटल व्योम mlxsw_afa_fwd_entry_put(काष्ठा mlxsw_afa *mlxsw_afa,
				    काष्ठा mlxsw_afa_fwd_entry *fwd_entry)
अणु
	अगर (--fwd_entry->ref_count)
		वापस;
	mlxsw_afa_fwd_entry_destroy(mlxsw_afa, fwd_entry);
पूर्ण

काष्ठा mlxsw_afa_fwd_entry_ref अणु
	काष्ठा mlxsw_afa_resource resource;
	काष्ठा mlxsw_afa_fwd_entry *fwd_entry;
पूर्ण;

अटल व्योम
mlxsw_afa_fwd_entry_ref_destroy(काष्ठा mlxsw_afa_block *block,
				काष्ठा mlxsw_afa_fwd_entry_ref *fwd_entry_ref)
अणु
	mlxsw_afa_resource_del(&fwd_entry_ref->resource);
	mlxsw_afa_fwd_entry_put(block->afa, fwd_entry_ref->fwd_entry);
	kमुक्त(fwd_entry_ref);
पूर्ण

अटल व्योम
mlxsw_afa_fwd_entry_ref_deकाष्ठाor(काष्ठा mlxsw_afa_block *block,
				   काष्ठा mlxsw_afa_resource *resource)
अणु
	काष्ठा mlxsw_afa_fwd_entry_ref *fwd_entry_ref;

	fwd_entry_ref = container_of(resource, काष्ठा mlxsw_afa_fwd_entry_ref,
				     resource);
	mlxsw_afa_fwd_entry_ref_destroy(block, fwd_entry_ref);
पूर्ण

अटल काष्ठा mlxsw_afa_fwd_entry_ref *
mlxsw_afa_fwd_entry_ref_create(काष्ठा mlxsw_afa_block *block, u8 local_port)
अणु
	काष्ठा mlxsw_afa_fwd_entry_ref *fwd_entry_ref;
	काष्ठा mlxsw_afa_fwd_entry *fwd_entry;
	पूर्णांक err;

	fwd_entry_ref = kzalloc(माप(*fwd_entry_ref), GFP_KERNEL);
	अगर (!fwd_entry_ref)
		वापस ERR_PTR(-ENOMEM);
	fwd_entry = mlxsw_afa_fwd_entry_get(block->afa, local_port);
	अगर (IS_ERR(fwd_entry)) अणु
		err = PTR_ERR(fwd_entry);
		जाओ err_fwd_entry_get;
	पूर्ण
	fwd_entry_ref->fwd_entry = fwd_entry;
	fwd_entry_ref->resource.deकाष्ठाor = mlxsw_afa_fwd_entry_ref_deकाष्ठाor;
	mlxsw_afa_resource_add(block, &fwd_entry_ref->resource);
	वापस fwd_entry_ref;

err_fwd_entry_get:
	kमुक्त(fwd_entry_ref);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा mlxsw_afa_counter अणु
	काष्ठा mlxsw_afa_resource resource;
	u32 counter_index;
पूर्ण;

अटल व्योम
mlxsw_afa_counter_destroy(काष्ठा mlxsw_afa_block *block,
			  काष्ठा mlxsw_afa_counter *counter)
अणु
	mlxsw_afa_resource_del(&counter->resource);
	block->afa->ops->counter_index_put(block->afa->ops_priv,
					   counter->counter_index);
	kमुक्त(counter);
पूर्ण

अटल व्योम
mlxsw_afa_counter_deकाष्ठाor(काष्ठा mlxsw_afa_block *block,
			     काष्ठा mlxsw_afa_resource *resource)
अणु
	काष्ठा mlxsw_afa_counter *counter;

	counter = container_of(resource, काष्ठा mlxsw_afa_counter, resource);
	mlxsw_afa_counter_destroy(block, counter);
पूर्ण

अटल काष्ठा mlxsw_afa_counter *
mlxsw_afa_counter_create(काष्ठा mlxsw_afa_block *block)
अणु
	काष्ठा mlxsw_afa_counter *counter;
	पूर्णांक err;

	counter = kzalloc(माप(*counter), GFP_KERNEL);
	अगर (!counter)
		वापस ERR_PTR(-ENOMEM);

	err = block->afa->ops->counter_index_get(block->afa->ops_priv,
						 &counter->counter_index);
	अगर (err)
		जाओ err_counter_index_get;
	counter->resource.deकाष्ठाor = mlxsw_afa_counter_deकाष्ठाor;
	mlxsw_afa_resource_add(block, &counter->resource);
	वापस counter;

err_counter_index_get:
	kमुक्त(counter);
	वापस ERR_PTR(err);
पूर्ण

/* 20 bits is a maximum that hardware can handle in trap with userdef action
 * and carry aदीर्घ with the trapped packet.
 */
#घोषणा MLXSW_AFA_COOKIE_INDEX_BITS 20
#घोषणा MLXSW_AFA_COOKIE_INDEX_MAX ((1 << MLXSW_AFA_COOKIE_INDEX_BITS) - 1)

अटल काष्ठा mlxsw_afa_cookie *
mlxsw_afa_cookie_create(काष्ठा mlxsw_afa *mlxsw_afa,
			स्थिर काष्ठा flow_action_cookie *fa_cookie)
अणु
	काष्ठा mlxsw_afa_cookie *cookie;
	u32 cookie_index;
	पूर्णांक err;

	cookie = kzalloc(माप(*cookie) + fa_cookie->cookie_len, GFP_KERNEL);
	अगर (!cookie)
		वापस ERR_PTR(-ENOMEM);
	refcount_set(&cookie->ref_count, 1);
	स_नकल(&cookie->fa_cookie, fa_cookie,
	       माप(*fa_cookie) + fa_cookie->cookie_len);

	err = rhashtable_insert_fast(&mlxsw_afa->cookie_ht, &cookie->ht_node,
				     mlxsw_afa_cookie_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	/* Start cookie indexes with 1. Leave the 0 index unused. Packets
	 * that come from the HW which are not dropped by drop-with-cookie
	 * action are going to pass cookie_index 0 to lookup.
	 */
	cookie_index = 1;
	err = idr_alloc_u32(&mlxsw_afa->cookie_idr, cookie, &cookie_index,
			    MLXSW_AFA_COOKIE_INDEX_MAX, GFP_KERNEL);
	अगर (err)
		जाओ err_idr_alloc;
	cookie->cookie_index = cookie_index;
	वापस cookie;

err_idr_alloc:
	rhashtable_हटाओ_fast(&mlxsw_afa->cookie_ht, &cookie->ht_node,
			       mlxsw_afa_cookie_ht_params);
err_rhashtable_insert:
	kमुक्त(cookie);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_afa_cookie_destroy(काष्ठा mlxsw_afa *mlxsw_afa,
				     काष्ठा mlxsw_afa_cookie *cookie)
अणु
	idr_हटाओ(&mlxsw_afa->cookie_idr, cookie->cookie_index);
	rhashtable_हटाओ_fast(&mlxsw_afa->cookie_ht, &cookie->ht_node,
			       mlxsw_afa_cookie_ht_params);
	kमुक्त_rcu(cookie, rcu);
पूर्ण

अटल काष्ठा mlxsw_afa_cookie *
mlxsw_afa_cookie_get(काष्ठा mlxsw_afa *mlxsw_afa,
		     स्थिर काष्ठा flow_action_cookie *fa_cookie)
अणु
	काष्ठा mlxsw_afa_cookie *cookie;

	cookie = rhashtable_lookup_fast(&mlxsw_afa->cookie_ht, fa_cookie,
					mlxsw_afa_cookie_ht_params);
	अगर (cookie) अणु
		refcount_inc(&cookie->ref_count);
		वापस cookie;
	पूर्ण
	वापस mlxsw_afa_cookie_create(mlxsw_afa, fa_cookie);
पूर्ण

अटल व्योम mlxsw_afa_cookie_put(काष्ठा mlxsw_afa *mlxsw_afa,
				 काष्ठा mlxsw_afa_cookie *cookie)
अणु
	अगर (!refcount_dec_and_test(&cookie->ref_count))
		वापस;
	mlxsw_afa_cookie_destroy(mlxsw_afa, cookie);
पूर्ण

/* RCU पढ़ो lock must be held */
स्थिर काष्ठा flow_action_cookie *
mlxsw_afa_cookie_lookup(काष्ठा mlxsw_afa *mlxsw_afa, u32 cookie_index)
अणु
	काष्ठा mlxsw_afa_cookie *cookie;

	/* 0 index means no cookie */
	अगर (!cookie_index)
		वापस शून्य;
	cookie = idr_find(&mlxsw_afa->cookie_idr, cookie_index);
	अगर (!cookie)
		वापस शून्य;
	वापस &cookie->fa_cookie;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_cookie_lookup);

काष्ठा mlxsw_afa_cookie_ref अणु
	काष्ठा mlxsw_afa_resource resource;
	काष्ठा mlxsw_afa_cookie *cookie;
पूर्ण;

अटल व्योम
mlxsw_afa_cookie_ref_destroy(काष्ठा mlxsw_afa_block *block,
			     काष्ठा mlxsw_afa_cookie_ref *cookie_ref)
अणु
	mlxsw_afa_resource_del(&cookie_ref->resource);
	mlxsw_afa_cookie_put(block->afa, cookie_ref->cookie);
	kमुक्त(cookie_ref);
पूर्ण

अटल व्योम
mlxsw_afa_cookie_ref_deकाष्ठाor(काष्ठा mlxsw_afa_block *block,
				काष्ठा mlxsw_afa_resource *resource)
अणु
	काष्ठा mlxsw_afa_cookie_ref *cookie_ref;

	cookie_ref = container_of(resource, काष्ठा mlxsw_afa_cookie_ref,
				  resource);
	mlxsw_afa_cookie_ref_destroy(block, cookie_ref);
पूर्ण

अटल काष्ठा mlxsw_afa_cookie_ref *
mlxsw_afa_cookie_ref_create(काष्ठा mlxsw_afa_block *block,
			    स्थिर काष्ठा flow_action_cookie *fa_cookie)
अणु
	काष्ठा mlxsw_afa_cookie_ref *cookie_ref;
	काष्ठा mlxsw_afa_cookie *cookie;
	पूर्णांक err;

	cookie_ref = kzalloc(माप(*cookie_ref), GFP_KERNEL);
	अगर (!cookie_ref)
		वापस ERR_PTR(-ENOMEM);
	cookie = mlxsw_afa_cookie_get(block->afa, fa_cookie);
	अगर (IS_ERR(cookie)) अणु
		err = PTR_ERR(cookie);
		जाओ err_cookie_get;
	पूर्ण
	cookie_ref->cookie = cookie;
	cookie_ref->resource.deकाष्ठाor = mlxsw_afa_cookie_ref_deकाष्ठाor;
	mlxsw_afa_resource_add(block, &cookie_ref->resource);
	वापस cookie_ref;

err_cookie_get:
	kमुक्त(cookie_ref);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा mlxsw_afa_policer *
mlxsw_afa_policer_create(काष्ठा mlxsw_afa *mlxsw_afa, u32 fa_index,
			 u64 rate_bytes_ps, u32 burst,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_policer *policer;
	पूर्णांक err;

	policer = kzalloc(माप(*policer), GFP_KERNEL);
	अगर (!policer)
		वापस ERR_PTR(-ENOMEM);

	err = mlxsw_afa->ops->policer_add(mlxsw_afa->ops_priv, rate_bytes_ps,
					  burst, &policer->policer_index,
					  extack);
	अगर (err)
		जाओ err_policer_add;

	refcount_set(&policer->ref_count, 1);
	policer->fa_index = fa_index;

	err = rhashtable_insert_fast(&mlxsw_afa->policer_ht, &policer->ht_node,
				     mlxsw_afa_policer_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	list_add_tail(&policer->list, &mlxsw_afa->policer_list);

	वापस policer;

err_rhashtable_insert:
	mlxsw_afa->ops->policer_del(mlxsw_afa->ops_priv,
				    policer->policer_index);
err_policer_add:
	kमुक्त(policer);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_afa_policer_destroy(काष्ठा mlxsw_afa *mlxsw_afa,
				      काष्ठा mlxsw_afa_policer *policer)
अणु
	list_del(&policer->list);
	rhashtable_हटाओ_fast(&mlxsw_afa->policer_ht, &policer->ht_node,
			       mlxsw_afa_policer_ht_params);
	mlxsw_afa->ops->policer_del(mlxsw_afa->ops_priv,
				    policer->policer_index);
	kमुक्त(policer);
पूर्ण

अटल काष्ठा mlxsw_afa_policer *
mlxsw_afa_policer_get(काष्ठा mlxsw_afa *mlxsw_afa, u32 fa_index,
		      u64 rate_bytes_ps, u32 burst,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_policer *policer;

	policer = rhashtable_lookup_fast(&mlxsw_afa->policer_ht, &fa_index,
					 mlxsw_afa_policer_ht_params);
	अगर (policer) अणु
		refcount_inc(&policer->ref_count);
		वापस policer;
	पूर्ण

	वापस mlxsw_afa_policer_create(mlxsw_afa, fa_index, rate_bytes_ps,
					burst, extack);
पूर्ण

अटल व्योम mlxsw_afa_policer_put(काष्ठा mlxsw_afa *mlxsw_afa,
				  काष्ठा mlxsw_afa_policer *policer)
अणु
	अगर (!refcount_dec_and_test(&policer->ref_count))
		वापस;
	mlxsw_afa_policer_destroy(mlxsw_afa, policer);
पूर्ण

काष्ठा mlxsw_afa_policer_ref अणु
	काष्ठा mlxsw_afa_resource resource;
	काष्ठा mlxsw_afa_policer *policer;
पूर्ण;

अटल व्योम
mlxsw_afa_policer_ref_destroy(काष्ठा mlxsw_afa_block *block,
			      काष्ठा mlxsw_afa_policer_ref *policer_ref)
अणु
	mlxsw_afa_resource_del(&policer_ref->resource);
	mlxsw_afa_policer_put(block->afa, policer_ref->policer);
	kमुक्त(policer_ref);
पूर्ण

अटल व्योम
mlxsw_afa_policer_ref_deकाष्ठाor(काष्ठा mlxsw_afa_block *block,
				 काष्ठा mlxsw_afa_resource *resource)
अणु
	काष्ठा mlxsw_afa_policer_ref *policer_ref;

	policer_ref = container_of(resource, काष्ठा mlxsw_afa_policer_ref,
				   resource);
	mlxsw_afa_policer_ref_destroy(block, policer_ref);
पूर्ण

अटल काष्ठा mlxsw_afa_policer_ref *
mlxsw_afa_policer_ref_create(काष्ठा mlxsw_afa_block *block, u32 fa_index,
			     u64 rate_bytes_ps, u32 burst,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_policer_ref *policer_ref;
	काष्ठा mlxsw_afa_policer *policer;
	पूर्णांक err;

	policer_ref = kzalloc(माप(*policer_ref), GFP_KERNEL);
	अगर (!policer_ref)
		वापस ERR_PTR(-ENOMEM);

	policer = mlxsw_afa_policer_get(block->afa, fa_index, rate_bytes_ps,
					burst, extack);
	अगर (IS_ERR(policer)) अणु
		err = PTR_ERR(policer);
		जाओ err_policer_get;
	पूर्ण

	policer_ref->policer = policer;
	policer_ref->resource.deकाष्ठाor = mlxsw_afa_policer_ref_deकाष्ठाor;
	mlxsw_afa_resource_add(block, &policer_ref->resource);

	वापस policer_ref;

err_policer_get:
	kमुक्त(policer_ref);
	वापस ERR_PTR(err);
पूर्ण

#घोषणा MLXSW_AFA_ONE_ACTION_LEN 32
#घोषणा MLXSW_AFA_PAYLOAD_OFFSET 4

क्रमागत mlxsw_afa_action_type अणु
	MLXSW_AFA_ACTION_TYPE_TRAP,
	MLXSW_AFA_ACTION_TYPE_POLICE,
	MLXSW_AFA_ACTION_TYPE_OTHER,
पूर्ण;

अटल bool
mlxsw_afa_block_need_split(स्थिर काष्ठा mlxsw_afa_block *block,
			   क्रमागत mlxsw_afa_action_type type)
अणु
	काष्ठा mlxsw_afa_set *cur_set = block->cur_set;

	/* Due to a hardware limitation, police action cannot be in the same
	 * action set with MLXSW_AFA_TRAP_CODE or MLXSW_AFA_TRAPWU_CODE
	 * actions. Work around this limitation by creating a new action set
	 * and place the new action there.
	 */
	वापस (cur_set->has_trap && type == MLXSW_AFA_ACTION_TYPE_POLICE) ||
	       (cur_set->has_police && type == MLXSW_AFA_ACTION_TYPE_TRAP);
पूर्ण

अटल अक्षर *mlxsw_afa_block_append_action_ext(काष्ठा mlxsw_afa_block *block,
					       u8 action_code, u8 action_size,
					       क्रमागत mlxsw_afa_action_type type)
अणु
	अक्षर *oneact;
	अक्षर *actions;

	अगर (block->finished)
		वापस ERR_PTR(-EINVAL);
	अगर (block->cur_act_index + action_size > block->afa->max_acts_per_set ||
	    mlxsw_afa_block_need_split(block, type)) अणु
		काष्ठा mlxsw_afa_set *set;

		/* The appended action won't fit पूर्णांकo the current action set,
		 * so create a new set.
		 */
		set = mlxsw_afa_set_create(false);
		अगर (!set)
			वापस ERR_PTR(-ENOBUFS);
		set->prev = block->cur_set;
		block->cur_act_index = 0;
		block->cur_set->next = set;
		block->cur_set = set;
	पूर्ण

	चयन (type) अणु
	हाल MLXSW_AFA_ACTION_TYPE_TRAP:
		block->cur_set->has_trap = true;
		अवरोध;
	हाल MLXSW_AFA_ACTION_TYPE_POLICE:
		block->cur_set->has_police = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	actions = block->cur_set->ht_key.enc_actions;
	oneact = actions + block->cur_act_index * MLXSW_AFA_ONE_ACTION_LEN;
	block->cur_act_index += action_size;
	mlxsw_afa_all_action_type_set(oneact, action_code);
	वापस oneact + MLXSW_AFA_PAYLOAD_OFFSET;
पूर्ण

अटल अक्षर *mlxsw_afa_block_append_action(काष्ठा mlxsw_afa_block *block,
					   u8 action_code, u8 action_size)
अणु
	वापस mlxsw_afa_block_append_action_ext(block, action_code,
						 action_size,
						 MLXSW_AFA_ACTION_TYPE_OTHER);
पूर्ण

/* VLAN Action
 * -----------
 * VLAN action is used क्रम manipulating VLANs. It can be used to implement QinQ,
 * VLAN translation, change of PCP bits of the VLAN tag, push, pop as swap VLANs
 * and more.
 */

#घोषणा MLXSW_AFA_VLAN_CODE 0x02
#घोषणा MLXSW_AFA_VLAN_SIZE 1

क्रमागत mlxsw_afa_vlan_vlan_tag_cmd अणु
	MLXSW_AFA_VLAN_VLAN_TAG_CMD_NOP,
	MLXSW_AFA_VLAN_VLAN_TAG_CMD_PUSH_TAG,
	MLXSW_AFA_VLAN_VLAN_TAG_CMD_POP_TAG,
पूर्ण;

क्रमागत mlxsw_afa_vlan_cmd अणु
	MLXSW_AFA_VLAN_CMD_NOP,
	MLXSW_AFA_VLAN_CMD_SET_OUTER,
	MLXSW_AFA_VLAN_CMD_SET_INNER,
	MLXSW_AFA_VLAN_CMD_COPY_OUTER_TO_INNER,
	MLXSW_AFA_VLAN_CMD_COPY_INNER_TO_OUTER,
	MLXSW_AFA_VLAN_CMD_SWAP,
पूर्ण;

/* afa_vlan_vlan_tag_cmd
 * Tag command: push, pop, nop VLAN header.
 */
MLXSW_ITEM32(afa, vlan, vlan_tag_cmd, 0x00, 29, 3);

/* afa_vlan_vid_cmd */
MLXSW_ITEM32(afa, vlan, vid_cmd, 0x04, 29, 3);

/* afa_vlan_vid */
MLXSW_ITEM32(afa, vlan, vid, 0x04, 0, 12);

/* afa_vlan_ethertype_cmd */
MLXSW_ITEM32(afa, vlan, ethertype_cmd, 0x08, 29, 3);

/* afa_vlan_ethertype
 * Index to EtherTypes in Switch VLAN EtherType Register (SVER).
 */
MLXSW_ITEM32(afa, vlan, ethertype, 0x08, 24, 3);

/* afa_vlan_pcp_cmd */
MLXSW_ITEM32(afa, vlan, pcp_cmd, 0x08, 13, 3);

/* afa_vlan_pcp */
MLXSW_ITEM32(afa, vlan, pcp, 0x08, 8, 3);

अटल अंतरभूत व्योम
mlxsw_afa_vlan_pack(अक्षर *payload,
		    क्रमागत mlxsw_afa_vlan_vlan_tag_cmd vlan_tag_cmd,
		    क्रमागत mlxsw_afa_vlan_cmd vid_cmd, u16 vid,
		    क्रमागत mlxsw_afa_vlan_cmd pcp_cmd, u8 pcp,
		    क्रमागत mlxsw_afa_vlan_cmd ethertype_cmd, u8 ethertype)
अणु
	mlxsw_afa_vlan_vlan_tag_cmd_set(payload, vlan_tag_cmd);
	mlxsw_afa_vlan_vid_cmd_set(payload, vid_cmd);
	mlxsw_afa_vlan_vid_set(payload, vid);
	mlxsw_afa_vlan_pcp_cmd_set(payload, pcp_cmd);
	mlxsw_afa_vlan_pcp_set(payload, pcp);
	mlxsw_afa_vlan_ethertype_cmd_set(payload, ethertype_cmd);
	mlxsw_afa_vlan_ethertype_set(payload, ethertype);
पूर्ण

पूर्णांक mlxsw_afa_block_append_vlan_modअगरy(काष्ठा mlxsw_afa_block *block,
				       u16 vid, u8 pcp, u8 et,
				       काष्ठा netlink_ext_ack *extack)
अणु
	अक्षर *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_VLAN_CODE,
						  MLXSW_AFA_VLAN_SIZE);

	अगर (IS_ERR(act)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append vlan_modify action");
		वापस PTR_ERR(act);
	पूर्ण
	mlxsw_afa_vlan_pack(act, MLXSW_AFA_VLAN_VLAN_TAG_CMD_NOP,
			    MLXSW_AFA_VLAN_CMD_SET_OUTER, vid,
			    MLXSW_AFA_VLAN_CMD_SET_OUTER, pcp,
			    MLXSW_AFA_VLAN_CMD_SET_OUTER, et);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_vlan_modअगरy);

/* Trap Action / Trap With Userdef Action
 * --------------------------------------
 * The Trap action enables trapping / mirroring packets to the CPU
 * as well as discarding packets.
 * The ACL Trap / Discard separates the क्रमward/discard control from CPU
 * trap control. In addition, the Trap / Discard action enables activating
 * SPAN (port mirroring).
 *
 * The Trap with userdef action action has the same functionality as
 * the Trap action with addition of user defined value that can be set
 * and used by higher layer applications.
 */

#घोषणा MLXSW_AFA_TRAP_CODE 0x03
#घोषणा MLXSW_AFA_TRAP_SIZE 1

#घोषणा MLXSW_AFA_TRAPWU_CODE 0x04
#घोषणा MLXSW_AFA_TRAPWU_SIZE 2

क्रमागत mlxsw_afa_trap_trap_action अणु
	MLXSW_AFA_TRAP_TRAP_ACTION_NOP = 0,
	MLXSW_AFA_TRAP_TRAP_ACTION_TRAP = 2,
पूर्ण;

/* afa_trap_trap_action
 * Trap Action.
 */
MLXSW_ITEM32(afa, trap, trap_action, 0x00, 24, 4);

क्रमागत mlxsw_afa_trap_क्रमward_action अणु
	MLXSW_AFA_TRAP_FORWARD_ACTION_FORWARD = 1,
	MLXSW_AFA_TRAP_FORWARD_ACTION_DISCARD = 3,
पूर्ण;

/* afa_trap_क्रमward_action
 * Forward Action.
 */
MLXSW_ITEM32(afa, trap, क्रमward_action, 0x00, 0, 4);

/* afa_trap_trap_id
 * Trap ID to configure.
 */
MLXSW_ITEM32(afa, trap, trap_id, 0x04, 0, 9);

/* afa_trap_mirror_agent
 * Mirror agent.
 */
MLXSW_ITEM32(afa, trap, mirror_agent, 0x08, 29, 3);

/* afa_trap_mirror_enable
 * Mirror enable.
 */
MLXSW_ITEM32(afa, trap, mirror_enable, 0x08, 24, 1);

/* user_def_val
 * Value क्रम the SW usage. Can be used to pass inक्रमmation of which
 * rule has caused a trap. This may be overwritten by later traps.
 * This field करोes a set on the packet's user_def_val only अगर this
 * is the first trap_id or अगर the trap_id has replaced the previous
 * packet's trap_id.
 */
MLXSW_ITEM32(afa, trap, user_def_val, 0x0C, 0, 20);

अटल अंतरभूत व्योम
mlxsw_afa_trap_pack(अक्षर *payload,
		    क्रमागत mlxsw_afa_trap_trap_action trap_action,
		    क्रमागत mlxsw_afa_trap_क्रमward_action क्रमward_action,
		    u16 trap_id)
अणु
	mlxsw_afa_trap_trap_action_set(payload, trap_action);
	mlxsw_afa_trap_क्रमward_action_set(payload, क्रमward_action);
	mlxsw_afa_trap_trap_id_set(payload, trap_id);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_afa_trapwu_pack(अक्षर *payload,
		      क्रमागत mlxsw_afa_trap_trap_action trap_action,
		      क्रमागत mlxsw_afa_trap_क्रमward_action क्रमward_action,
		      u16 trap_id, u32 user_def_val)
अणु
	mlxsw_afa_trap_pack(payload, trap_action, क्रमward_action, trap_id);
	mlxsw_afa_trap_user_def_val_set(payload, user_def_val);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_afa_trap_mirror_pack(अक्षर *payload, bool mirror_enable,
			   u8 mirror_agent)
अणु
	mlxsw_afa_trap_mirror_enable_set(payload, mirror_enable);
	mlxsw_afa_trap_mirror_agent_set(payload, mirror_agent);
पूर्ण

अटल अक्षर *mlxsw_afa_block_append_action_trap(काष्ठा mlxsw_afa_block *block,
						u8 action_code, u8 action_size)
अणु
	वापस mlxsw_afa_block_append_action_ext(block, action_code,
						 action_size,
						 MLXSW_AFA_ACTION_TYPE_TRAP);
पूर्ण

अटल पूर्णांक mlxsw_afa_block_append_drop_plain(काष्ठा mlxsw_afa_block *block,
					     bool ingress)
अणु
	अक्षर *act = mlxsw_afa_block_append_action_trap(block,
						       MLXSW_AFA_TRAP_CODE,
						       MLXSW_AFA_TRAP_SIZE);

	अगर (IS_ERR(act))
		वापस PTR_ERR(act);
	mlxsw_afa_trap_pack(act, MLXSW_AFA_TRAP_TRAP_ACTION_TRAP,
			    MLXSW_AFA_TRAP_FORWARD_ACTION_DISCARD,
			    ingress ? MLXSW_TRAP_ID_DISCARD_INGRESS_ACL :
				      MLXSW_TRAP_ID_DISCARD_EGRESS_ACL);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_afa_block_append_drop_with_cookie(काष्ठा mlxsw_afa_block *block,
					bool ingress,
					स्थिर काष्ठा flow_action_cookie *fa_cookie,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_cookie_ref *cookie_ref;
	u32 cookie_index;
	अक्षर *act;
	पूर्णांक err;

	cookie_ref = mlxsw_afa_cookie_ref_create(block, fa_cookie);
	अगर (IS_ERR(cookie_ref)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot create cookie for drop action");
		वापस PTR_ERR(cookie_ref);
	पूर्ण
	cookie_index = cookie_ref->cookie->cookie_index;

	act = mlxsw_afa_block_append_action_trap(block, MLXSW_AFA_TRAPWU_CODE,
						 MLXSW_AFA_TRAPWU_SIZE);
	अगर (IS_ERR(act)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append drop with cookie action");
		err = PTR_ERR(act);
		जाओ err_append_action;
	पूर्ण
	mlxsw_afa_trapwu_pack(act, MLXSW_AFA_TRAP_TRAP_ACTION_TRAP,
			      MLXSW_AFA_TRAP_FORWARD_ACTION_DISCARD,
			      ingress ? MLXSW_TRAP_ID_DISCARD_INGRESS_ACL :
					MLXSW_TRAP_ID_DISCARD_EGRESS_ACL,
			      cookie_index);
	वापस 0;

err_append_action:
	mlxsw_afa_cookie_ref_destroy(block, cookie_ref);
	वापस err;
पूर्ण

पूर्णांक mlxsw_afa_block_append_drop(काष्ठा mlxsw_afa_block *block, bool ingress,
				स्थिर काष्ठा flow_action_cookie *fa_cookie,
				काष्ठा netlink_ext_ack *extack)
अणु
	वापस fa_cookie ?
	       mlxsw_afa_block_append_drop_with_cookie(block, ingress,
						       fa_cookie, extack) :
	       mlxsw_afa_block_append_drop_plain(block, ingress);
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_drop);

पूर्णांक mlxsw_afa_block_append_trap(काष्ठा mlxsw_afa_block *block, u16 trap_id)
अणु
	अक्षर *act = mlxsw_afa_block_append_action_trap(block,
						       MLXSW_AFA_TRAP_CODE,
						       MLXSW_AFA_TRAP_SIZE);

	अगर (IS_ERR(act))
		वापस PTR_ERR(act);
	mlxsw_afa_trap_pack(act, MLXSW_AFA_TRAP_TRAP_ACTION_TRAP,
			    MLXSW_AFA_TRAP_FORWARD_ACTION_DISCARD, trap_id);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_trap);

पूर्णांक mlxsw_afa_block_append_trap_and_क्रमward(काष्ठा mlxsw_afa_block *block,
					    u16 trap_id)
अणु
	अक्षर *act = mlxsw_afa_block_append_action_trap(block,
						       MLXSW_AFA_TRAP_CODE,
						       MLXSW_AFA_TRAP_SIZE);

	अगर (IS_ERR(act))
		वापस PTR_ERR(act);
	mlxsw_afa_trap_pack(act, MLXSW_AFA_TRAP_TRAP_ACTION_TRAP,
			    MLXSW_AFA_TRAP_FORWARD_ACTION_FORWARD, trap_id);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_trap_and_क्रमward);

काष्ठा mlxsw_afa_mirror अणु
	काष्ठा mlxsw_afa_resource resource;
	पूर्णांक span_id;
	u8 local_in_port;
	bool ingress;
पूर्ण;

अटल व्योम
mlxsw_afa_mirror_destroy(काष्ठा mlxsw_afa_block *block,
			 काष्ठा mlxsw_afa_mirror *mirror)
अणु
	mlxsw_afa_resource_del(&mirror->resource);
	block->afa->ops->mirror_del(block->afa->ops_priv,
				    mirror->local_in_port,
				    mirror->span_id,
				    mirror->ingress);
	kमुक्त(mirror);
पूर्ण

अटल व्योम
mlxsw_afa_mirror_deकाष्ठाor(काष्ठा mlxsw_afa_block *block,
			    काष्ठा mlxsw_afa_resource *resource)
अणु
	काष्ठा mlxsw_afa_mirror *mirror;

	mirror = container_of(resource, काष्ठा mlxsw_afa_mirror, resource);
	mlxsw_afa_mirror_destroy(block, mirror);
पूर्ण

अटल काष्ठा mlxsw_afa_mirror *
mlxsw_afa_mirror_create(काष्ठा mlxsw_afa_block *block, u8 local_in_port,
			स्थिर काष्ठा net_device *out_dev, bool ingress)
अणु
	काष्ठा mlxsw_afa_mirror *mirror;
	पूर्णांक err;

	mirror = kzalloc(माप(*mirror), GFP_KERNEL);
	अगर (!mirror)
		वापस ERR_PTR(-ENOMEM);

	err = block->afa->ops->mirror_add(block->afa->ops_priv,
					  local_in_port, out_dev,
					  ingress, &mirror->span_id);
	अगर (err)
		जाओ err_mirror_add;

	mirror->ingress = ingress;
	mirror->local_in_port = local_in_port;
	mirror->resource.deकाष्ठाor = mlxsw_afa_mirror_deकाष्ठाor;
	mlxsw_afa_resource_add(block, &mirror->resource);
	वापस mirror;

err_mirror_add:
	kमुक्त(mirror);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक
mlxsw_afa_block_append_allocated_mirror(काष्ठा mlxsw_afa_block *block,
					u8 mirror_agent)
अणु
	अक्षर *act = mlxsw_afa_block_append_action_trap(block,
						       MLXSW_AFA_TRAP_CODE,
						       MLXSW_AFA_TRAP_SIZE);

	अगर (IS_ERR(act))
		वापस PTR_ERR(act);
	mlxsw_afa_trap_pack(act, MLXSW_AFA_TRAP_TRAP_ACTION_NOP,
			    MLXSW_AFA_TRAP_FORWARD_ACTION_FORWARD, 0);
	mlxsw_afa_trap_mirror_pack(act, true, mirror_agent);
	वापस 0;
पूर्ण

पूर्णांक
mlxsw_afa_block_append_mirror(काष्ठा mlxsw_afa_block *block, u8 local_in_port,
			      स्थिर काष्ठा net_device *out_dev, bool ingress,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_mirror *mirror;
	पूर्णांक err;

	mirror = mlxsw_afa_mirror_create(block, local_in_port, out_dev,
					 ingress);
	अगर (IS_ERR(mirror)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot create mirror action");
		वापस PTR_ERR(mirror);
	पूर्ण
	err = mlxsw_afa_block_append_allocated_mirror(block, mirror->span_id);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append mirror action");
		जाओ err_append_allocated_mirror;
	पूर्ण

	वापस 0;

err_append_allocated_mirror:
	mlxsw_afa_mirror_destroy(block, mirror);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_mirror);

/* QoS Action
 * ----------
 * The QOS_ACTION is used क्रम manipulating the QoS attributes of a packet. It
 * can be used to change the DCSP, ECN, Color and Switch Priority of the packet.
 * Note that PCP field can be changed using the VLAN action.
 */

#घोषणा MLXSW_AFA_QOS_CODE 0x06
#घोषणा MLXSW_AFA_QOS_SIZE 1

क्रमागत mlxsw_afa_qos_ecn_cmd अणु
	/* Do nothing */
	MLXSW_AFA_QOS_ECN_CMD_NOP,
	/* Set ECN to afa_qos_ecn */
	MLXSW_AFA_QOS_ECN_CMD_SET,
पूर्ण;

/* afa_qos_ecn_cmd
 */
MLXSW_ITEM32(afa, qos, ecn_cmd, 0x04, 29, 3);

/* afa_qos_ecn
 * ECN value.
 */
MLXSW_ITEM32(afa, qos, ecn, 0x04, 24, 2);

क्रमागत mlxsw_afa_qos_dscp_cmd अणु
	/* Do nothing */
	MLXSW_AFA_QOS_DSCP_CMD_NOP,
	/* Set DSCP 3 LSB bits according to dscp[2:0] */
	MLXSW_AFA_QOS_DSCP_CMD_SET_3LSB,
	/* Set DSCP 3 MSB bits according to dscp[5:3] */
	MLXSW_AFA_QOS_DSCP_CMD_SET_3MSB,
	/* Set DSCP 6 bits according to dscp[5:0] */
	MLXSW_AFA_QOS_DSCP_CMD_SET_ALL,
पूर्ण;

/* afa_qos_dscp_cmd
 * DSCP command.
 */
MLXSW_ITEM32(afa, qos, dscp_cmd, 0x04, 14, 2);

/* afa_qos_dscp
 * DSCP value.
 */
MLXSW_ITEM32(afa, qos, dscp, 0x04, 0, 6);

क्रमागत mlxsw_afa_qos_चयन_prio_cmd अणु
	/* Do nothing */
	MLXSW_AFA_QOS_SWITCH_PRIO_CMD_NOP,
	/* Set Switch Priority to afa_qos_चयन_prio */
	MLXSW_AFA_QOS_SWITCH_PRIO_CMD_SET,
पूर्ण;

/* afa_qos_चयन_prio_cmd
 */
MLXSW_ITEM32(afa, qos, चयन_prio_cmd, 0x08, 14, 2);

/* afa_qos_चयन_prio
 * Switch Priority.
 */
MLXSW_ITEM32(afa, qos, चयन_prio, 0x08, 0, 4);

क्रमागत mlxsw_afa_qos_dscp_rw अणु
	MLXSW_AFA_QOS_DSCP_RW_PRESERVE,
	MLXSW_AFA_QOS_DSCP_RW_SET,
	MLXSW_AFA_QOS_DSCP_RW_CLEAR,
पूर्ण;

/* afa_qos_dscp_rw
 * DSCP Re-ग_लिखो Enable. Controlling the reग_लिखो_enable क्रम DSCP.
 */
MLXSW_ITEM32(afa, qos, dscp_rw, 0x0C, 30, 2);

अटल अंतरभूत व्योम
mlxsw_afa_qos_ecn_pack(अक्षर *payload,
		       क्रमागत mlxsw_afa_qos_ecn_cmd ecn_cmd, u8 ecn)
अणु
	mlxsw_afa_qos_ecn_cmd_set(payload, ecn_cmd);
	mlxsw_afa_qos_ecn_set(payload, ecn);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_afa_qos_dscp_pack(अक्षर *payload,
			क्रमागत mlxsw_afa_qos_dscp_cmd dscp_cmd, u8 dscp)
अणु
	mlxsw_afa_qos_dscp_cmd_set(payload, dscp_cmd);
	mlxsw_afa_qos_dscp_set(payload, dscp);
पूर्ण

अटल अंतरभूत व्योम
mlxsw_afa_qos_चयन_prio_pack(अक्षर *payload,
			       क्रमागत mlxsw_afa_qos_चयन_prio_cmd prio_cmd,
			       u8 prio)
अणु
	mlxsw_afa_qos_चयन_prio_cmd_set(payload, prio_cmd);
	mlxsw_afa_qos_चयन_prio_set(payload, prio);
पूर्ण

अटल पूर्णांक __mlxsw_afa_block_append_qos_dsfield(काष्ठा mlxsw_afa_block *block,
						bool set_dscp, u8 dscp,
						bool set_ecn, u8 ecn,
						काष्ठा netlink_ext_ack *extack)
अणु
	अक्षर *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_QOS_CODE,
						  MLXSW_AFA_QOS_SIZE);

	अगर (IS_ERR(act)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append QOS action");
		वापस PTR_ERR(act);
	पूर्ण

	अगर (set_ecn)
		mlxsw_afa_qos_ecn_pack(act, MLXSW_AFA_QOS_ECN_CMD_SET, ecn);
	अगर (set_dscp) अणु
		mlxsw_afa_qos_dscp_pack(act, MLXSW_AFA_QOS_DSCP_CMD_SET_ALL,
					dscp);
		mlxsw_afa_qos_dscp_rw_set(act, MLXSW_AFA_QOS_DSCP_RW_CLEAR);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlxsw_afa_block_append_qos_dsfield(काष्ठा mlxsw_afa_block *block,
				       u8 dsfield,
				       काष्ठा netlink_ext_ack *extack)
अणु
	वापस __mlxsw_afa_block_append_qos_dsfield(block,
						    true, dsfield >> 2,
						    true, dsfield & 0x03,
						    extack);
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_qos_dsfield);

पूर्णांक mlxsw_afa_block_append_qos_dscp(काष्ठा mlxsw_afa_block *block,
				    u8 dscp, काष्ठा netlink_ext_ack *extack)
अणु
	वापस __mlxsw_afa_block_append_qos_dsfield(block,
						    true, dscp,
						    false, 0,
						    extack);
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_qos_dscp);

पूर्णांक mlxsw_afa_block_append_qos_ecn(काष्ठा mlxsw_afa_block *block,
				   u8 ecn, काष्ठा netlink_ext_ack *extack)
अणु
	वापस __mlxsw_afa_block_append_qos_dsfield(block,
						    false, 0,
						    true, ecn,
						    extack);
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_qos_ecn);

पूर्णांक mlxsw_afa_block_append_qos_चयन_prio(काष्ठा mlxsw_afa_block *block,
					   u8 prio,
					   काष्ठा netlink_ext_ack *extack)
अणु
	अक्षर *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_QOS_CODE,
						  MLXSW_AFA_QOS_SIZE);

	अगर (IS_ERR(act)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append QOS action");
		वापस PTR_ERR(act);
	पूर्ण
	mlxsw_afa_qos_चयन_prio_pack(act, MLXSW_AFA_QOS_SWITCH_PRIO_CMD_SET,
				       prio);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_qos_चयन_prio);

/* Forwarding Action
 * -----------------
 * Forwarding Action can be used to implement Policy Based Switching (PBS)
 * as well as OpenFlow related "Output" action.
 */

#घोषणा MLXSW_AFA_FORWARD_CODE 0x07
#घोषणा MLXSW_AFA_FORWARD_SIZE 1

क्रमागत mlxsw_afa_क्रमward_type अणु
	/* PBS, Policy Based Switching */
	MLXSW_AFA_FORWARD_TYPE_PBS,
	/* Output, OpenFlow output type */
	MLXSW_AFA_FORWARD_TYPE_OUTPUT,
पूर्ण;

/* afa_क्रमward_type */
MLXSW_ITEM32(afa, क्रमward, type, 0x00, 24, 2);

/* afa_क्रमward_pbs_ptr
 * A poपूर्णांकer to the PBS entry configured by PPBS रेजिस्टर.
 * Reserved when in_port is set.
 */
MLXSW_ITEM32(afa, क्रमward, pbs_ptr, 0x08, 0, 24);

/* afa_क्रमward_in_port
 * Packet is क्रमwarded back to the ingress port.
 */
MLXSW_ITEM32(afa, क्रमward, in_port, 0x0C, 0, 1);

अटल अंतरभूत व्योम
mlxsw_afa_क्रमward_pack(अक्षर *payload, क्रमागत mlxsw_afa_क्रमward_type type,
		       u32 pbs_ptr, bool in_port)
अणु
	mlxsw_afa_क्रमward_type_set(payload, type);
	mlxsw_afa_क्रमward_pbs_ptr_set(payload, pbs_ptr);
	mlxsw_afa_क्रमward_in_port_set(payload, in_port);
पूर्ण

पूर्णांक mlxsw_afa_block_append_fwd(काष्ठा mlxsw_afa_block *block,
			       u8 local_port, bool in_port,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_fwd_entry_ref *fwd_entry_ref;
	u32 kvdl_index;
	अक्षर *act;
	पूर्णांक err;

	अगर (in_port) अणु
		NL_SET_ERR_MSG_MOD(extack, "Forwarding to ingress port is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	fwd_entry_ref = mlxsw_afa_fwd_entry_ref_create(block, local_port);
	अगर (IS_ERR(fwd_entry_ref)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot create forward action");
		वापस PTR_ERR(fwd_entry_ref);
	पूर्ण
	kvdl_index = fwd_entry_ref->fwd_entry->kvdl_index;

	act = mlxsw_afa_block_append_action(block, MLXSW_AFA_FORWARD_CODE,
					    MLXSW_AFA_FORWARD_SIZE);
	अगर (IS_ERR(act)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append forward action");
		err = PTR_ERR(act);
		जाओ err_append_action;
	पूर्ण
	mlxsw_afa_क्रमward_pack(act, MLXSW_AFA_FORWARD_TYPE_PBS,
			       kvdl_index, in_port);
	वापस 0;

err_append_action:
	mlxsw_afa_fwd_entry_ref_destroy(block, fwd_entry_ref);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_fwd);

/* Policing and Counting Action
 * ----------------------------
 * Policing and Counting action is used क्रम binding policer and counter
 * to ACL rules.
 */

#घोषणा MLXSW_AFA_POLCNT_CODE 0x08
#घोषणा MLXSW_AFA_POLCNT_SIZE 1

क्रमागत अणु
	MLXSW_AFA_POLCNT_COUNTER,
	MLXSW_AFA_POLCNT_POLICER,
पूर्ण;

/* afa_polcnt_c_p
 * Counter or policer.
 * Indicates whether the action binds a policer or a counter to the flow.
 * 0: Counter
 * 1: Policer
 */
MLXSW_ITEM32(afa, polcnt, c_p, 0x00, 31, 1);

क्रमागत mlxsw_afa_polcnt_counter_set_type अणु
	/* No count */
	MLXSW_AFA_POLCNT_COUNTER_SET_TYPE_NO_COUNT = 0x00,
	/* Count packets and bytes */
	MLXSW_AFA_POLCNT_COUNTER_SET_TYPE_PACKETS_BYTES = 0x03,
	/* Count only packets */
	MLXSW_AFA_POLCNT_COUNTER_SET_TYPE_PACKETS = 0x05,
पूर्ण;

/* afa_polcnt_counter_set_type
 * Counter set type क्रम flow counters.
 */
MLXSW_ITEM32(afa, polcnt, counter_set_type, 0x04, 24, 8);

/* afa_polcnt_counter_index
 * Counter index क्रम flow counters.
 */
MLXSW_ITEM32(afa, polcnt, counter_index, 0x04, 0, 24);

/* afa_polcnt_pid
 * Policer ID.
 * Reserved when c_p = 0
 */
MLXSW_ITEM32(afa, polcnt, pid, 0x08, 0, 14);

अटल अंतरभूत व्योम
mlxsw_afa_polcnt_pack(अक्षर *payload,
		      क्रमागत mlxsw_afa_polcnt_counter_set_type set_type,
		      u32 counter_index)
अणु
	mlxsw_afa_polcnt_c_p_set(payload, MLXSW_AFA_POLCNT_COUNTER);
	mlxsw_afa_polcnt_counter_set_type_set(payload, set_type);
	mlxsw_afa_polcnt_counter_index_set(payload, counter_index);
पूर्ण

अटल व्योम mlxsw_afa_polcnt_policer_pack(अक्षर *payload, u16 policer_index)
अणु
	mlxsw_afa_polcnt_c_p_set(payload, MLXSW_AFA_POLCNT_POLICER);
	mlxsw_afa_polcnt_pid_set(payload, policer_index);
पूर्ण

पूर्णांक mlxsw_afa_block_append_allocated_counter(काष्ठा mlxsw_afa_block *block,
					     u32 counter_index)
अणु
	अक्षर *act = mlxsw_afa_block_append_action(block, MLXSW_AFA_POLCNT_CODE,
						  MLXSW_AFA_POLCNT_SIZE);
	अगर (IS_ERR(act))
		वापस PTR_ERR(act);
	mlxsw_afa_polcnt_pack(act, MLXSW_AFA_POLCNT_COUNTER_SET_TYPE_PACKETS_BYTES,
			      counter_index);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_allocated_counter);

पूर्णांक mlxsw_afa_block_append_counter(काष्ठा mlxsw_afa_block *block,
				   u32 *p_counter_index,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_counter *counter;
	u32 counter_index;
	पूर्णांक err;

	counter = mlxsw_afa_counter_create(block);
	अगर (IS_ERR(counter)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot create count action");
		वापस PTR_ERR(counter);
	पूर्ण
	counter_index = counter->counter_index;

	err = mlxsw_afa_block_append_allocated_counter(block, counter_index);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append count action");
		जाओ err_append_allocated_counter;
	पूर्ण
	अगर (p_counter_index)
		*p_counter_index = counter_index;
	वापस 0;

err_append_allocated_counter:
	mlxsw_afa_counter_destroy(block, counter);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_counter);

पूर्णांक mlxsw_afa_block_append_police(काष्ठा mlxsw_afa_block *block,
				  u32 fa_index, u64 rate_bytes_ps, u32 burst,
				  u16 *p_policer_index,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_policer_ref *policer_ref;
	अक्षर *act;
	पूर्णांक err;

	policer_ref = mlxsw_afa_policer_ref_create(block, fa_index,
						   rate_bytes_ps,
						   burst, extack);
	अगर (IS_ERR(policer_ref))
		वापस PTR_ERR(policer_ref);
	*p_policer_index = policer_ref->policer->policer_index;

	act = mlxsw_afa_block_append_action_ext(block, MLXSW_AFA_POLCNT_CODE,
						MLXSW_AFA_POLCNT_SIZE,
						MLXSW_AFA_ACTION_TYPE_POLICE);
	अगर (IS_ERR(act)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append police action");
		err = PTR_ERR(act);
		जाओ err_append_action;
	पूर्ण
	mlxsw_afa_polcnt_policer_pack(act, *p_policer_index);

	वापस 0;

err_append_action:
	mlxsw_afa_policer_ref_destroy(block, policer_ref);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_police);

/* Virtual Router and Forwarding Doमुख्य Action
 * -------------------------------------------
 * Virtual Switch action is used क्रम manipulate the Virtual Router (VR),
 * MPLS label space and the Forwarding Identअगरier (FID).
 */

#घोषणा MLXSW_AFA_VIRFWD_CODE 0x0E
#घोषणा MLXSW_AFA_VIRFWD_SIZE 1

क्रमागत mlxsw_afa_virfwd_fid_cmd अणु
	/* Do nothing */
	MLXSW_AFA_VIRFWD_FID_CMD_NOOP,
	/* Set the Forwarding Identअगरier (FID) to fid */
	MLXSW_AFA_VIRFWD_FID_CMD_SET,
पूर्ण;

/* afa_virfwd_fid_cmd */
MLXSW_ITEM32(afa, virfwd, fid_cmd, 0x08, 29, 3);

/* afa_virfwd_fid
 * The FID value.
 */
MLXSW_ITEM32(afa, virfwd, fid, 0x08, 0, 16);

अटल अंतरभूत व्योम mlxsw_afa_virfwd_pack(अक्षर *payload,
					 क्रमागत mlxsw_afa_virfwd_fid_cmd fid_cmd,
					 u16 fid)
अणु
	mlxsw_afa_virfwd_fid_cmd_set(payload, fid_cmd);
	mlxsw_afa_virfwd_fid_set(payload, fid);
पूर्ण

पूर्णांक mlxsw_afa_block_append_fid_set(काष्ठा mlxsw_afa_block *block, u16 fid,
				   काष्ठा netlink_ext_ack *extack)
अणु
	अक्षर *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_VIRFWD_CODE,
						  MLXSW_AFA_VIRFWD_SIZE);
	अगर (IS_ERR(act)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append fid_set action");
		वापस PTR_ERR(act);
	पूर्ण
	mlxsw_afa_virfwd_pack(act, MLXSW_AFA_VIRFWD_FID_CMD_SET, fid);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_fid_set);

/* MC Routing Action
 * -----------------
 * The Multicast router action. Can be used by RMFT_V2 - Router Multicast
 * Forwarding Table Version 2 Register.
 */

#घोषणा MLXSW_AFA_MCROUTER_CODE 0x10
#घोषणा MLXSW_AFA_MCROUTER_SIZE 2

क्रमागत mlxsw_afa_mcrouter_rpf_action अणु
	MLXSW_AFA_MCROUTER_RPF_ACTION_NOP,
	MLXSW_AFA_MCROUTER_RPF_ACTION_TRAP,
	MLXSW_AFA_MCROUTER_RPF_ACTION_DISCARD_ERROR,
पूर्ण;

/* afa_mcrouter_rpf_action */
MLXSW_ITEM32(afa, mcrouter, rpf_action, 0x00, 28, 3);

/* afa_mcrouter_expected_irअगर */
MLXSW_ITEM32(afa, mcrouter, expected_irअगर, 0x00, 0, 16);

/* afa_mcrouter_min_mtu */
MLXSW_ITEM32(afa, mcrouter, min_mtu, 0x08, 0, 16);

क्रमागत mlxsw_afa_mrouter_vrmid अणु
	MLXSW_AFA_MCROUTER_VRMID_INVALID,
	MLXSW_AFA_MCROUTER_VRMID_VALID
पूर्ण;

/* afa_mcrouter_vrmid
 * Valid RMID: rigr_rmid_index is used as RMID
 */
MLXSW_ITEM32(afa, mcrouter, vrmid, 0x0C, 31, 1);

/* afa_mcrouter_rigr_rmid_index
 * When the vrmid field is set to invalid, the field is used as poपूर्णांकer to
 * Router Interface Group (RIGR) Table in the KVD linear.
 * When the vrmid is set to valid, the field is used as RMID index, ranged
 * from 0 to max_mid - 1. The index is to the Port Group Table.
 */
MLXSW_ITEM32(afa, mcrouter, rigr_rmid_index, 0x0C, 0, 24);

अटल अंतरभूत व्योम
mlxsw_afa_mcrouter_pack(अक्षर *payload,
			क्रमागत mlxsw_afa_mcrouter_rpf_action rpf_action,
			u16 expected_irअगर, u16 min_mtu,
			क्रमागत mlxsw_afa_mrouter_vrmid vrmid, u32 rigr_rmid_index)

अणु
	mlxsw_afa_mcrouter_rpf_action_set(payload, rpf_action);
	mlxsw_afa_mcrouter_expected_irअगर_set(payload, expected_irअगर);
	mlxsw_afa_mcrouter_min_mtu_set(payload, min_mtu);
	mlxsw_afa_mcrouter_vrmid_set(payload, vrmid);
	mlxsw_afa_mcrouter_rigr_rmid_index_set(payload, rigr_rmid_index);
पूर्ण

पूर्णांक mlxsw_afa_block_append_mcrouter(काष्ठा mlxsw_afa_block *block,
				    u16 expected_irअगर, u16 min_mtu,
				    bool rmid_valid, u32 kvdl_index)
अणु
	अक्षर *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_MCROUTER_CODE,
						  MLXSW_AFA_MCROUTER_SIZE);
	अगर (IS_ERR(act))
		वापस PTR_ERR(act);
	mlxsw_afa_mcrouter_pack(act, MLXSW_AFA_MCROUTER_RPF_ACTION_TRAP,
				expected_irअगर, min_mtu, rmid_valid, kvdl_index);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_mcrouter);

/* L4 Port Action
 * --------------
 * The L4_PORT_ACTION is used क्रम modअगरying the sport and dport fields of the packet, e.g. क्रम NAT.
 * If (the L4 is TCP) or अगर (the L4 is UDP and checksum field!=0) then the L4 checksum is updated.
 */

#घोषणा MLXSW_AFA_L4PORT_CODE 0x12
#घोषणा MLXSW_AFA_L4PORT_SIZE 1

क्रमागत mlxsw_afa_l4port_s_d अणु
	/* configure src_l4_port */
	MLXSW_AFA_L4PORT_S_D_SRC,
	/* configure dst_l4_port */
	MLXSW_AFA_L4PORT_S_D_DST,
पूर्ण;

/* afa_l4port_s_d
 * Source or destination.
 */
MLXSW_ITEM32(afa, l4port, s_d, 0x00, 31, 1);

/* afa_l4port_l4_port
 * Number of port to change to.
 */
MLXSW_ITEM32(afa, l4port, l4_port, 0x08, 0, 16);

अटल व्योम mlxsw_afa_l4port_pack(अक्षर *payload, क्रमागत mlxsw_afa_l4port_s_d s_d, u16 l4_port)
अणु
	mlxsw_afa_l4port_s_d_set(payload, s_d);
	mlxsw_afa_l4port_l4_port_set(payload, l4_port);
पूर्ण

पूर्णांक mlxsw_afa_block_append_l4port(काष्ठा mlxsw_afa_block *block, bool is_dport, u16 l4_port,
				  काष्ठा netlink_ext_ack *extack)
अणु
	क्रमागत mlxsw_afa_l4port_s_d s_d = is_dport ? MLXSW_AFA_L4PORT_S_D_DST :
						   MLXSW_AFA_L4PORT_S_D_SRC;
	अक्षर *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_L4PORT_CODE,
						  MLXSW_AFA_L4PORT_SIZE);

	अगर (IS_ERR(act)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append L4_PORT action");
		वापस PTR_ERR(act);
	पूर्ण

	mlxsw_afa_l4port_pack(act, s_d, l4_port);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_l4port);

/* Mirror Sampler Action
 * ---------------------
 * The SAMPLER_ACTION is used to mirror packets with a probability (sampling).
 */

#घोषणा MLXSW_AFA_SAMPLER_CODE 0x13
#घोषणा MLXSW_AFA_SAMPLER_SIZE 1

/* afa_sampler_mirror_agent
 * Mirror (SPAN) agent.
 */
MLXSW_ITEM32(afa, sampler, mirror_agent, 0x04, 0, 3);

#घोषणा MLXSW_AFA_SAMPLER_RATE_MAX (BIT(24) - 1)

/* afa_sampler_mirror_probability_rate
 * Mirroring probability.
 * Valid values are 1 to 2^24 - 1
 */
MLXSW_ITEM32(afa, sampler, mirror_probability_rate, 0x08, 0, 24);

अटल व्योम mlxsw_afa_sampler_pack(अक्षर *payload, u8 mirror_agent, u32 rate)
अणु
	mlxsw_afa_sampler_mirror_agent_set(payload, mirror_agent);
	mlxsw_afa_sampler_mirror_probability_rate_set(payload, rate);
पूर्ण

काष्ठा mlxsw_afa_sampler अणु
	काष्ठा mlxsw_afa_resource resource;
	पूर्णांक span_id;
	u8 local_port;
	bool ingress;
पूर्ण;

अटल व्योम mlxsw_afa_sampler_destroy(काष्ठा mlxsw_afa_block *block,
				      काष्ठा mlxsw_afa_sampler *sampler)
अणु
	mlxsw_afa_resource_del(&sampler->resource);
	block->afa->ops->sampler_del(block->afa->ops_priv, sampler->local_port,
				     sampler->span_id, sampler->ingress);
	kमुक्त(sampler);
पूर्ण

अटल व्योम mlxsw_afa_sampler_deकाष्ठाor(काष्ठा mlxsw_afa_block *block,
					 काष्ठा mlxsw_afa_resource *resource)
अणु
	काष्ठा mlxsw_afa_sampler *sampler;

	sampler = container_of(resource, काष्ठा mlxsw_afa_sampler, resource);
	mlxsw_afa_sampler_destroy(block, sampler);
पूर्ण

अटल काष्ठा mlxsw_afa_sampler *
mlxsw_afa_sampler_create(काष्ठा mlxsw_afa_block *block, u8 local_port,
			 काष्ठा psample_group *psample_group, u32 rate,
			 u32 trunc_size, bool truncate, bool ingress,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_sampler *sampler;
	पूर्णांक err;

	sampler = kzalloc(माप(*sampler), GFP_KERNEL);
	अगर (!sampler)
		वापस ERR_PTR(-ENOMEM);

	err = block->afa->ops->sampler_add(block->afa->ops_priv, local_port,
					   psample_group, rate, trunc_size,
					   truncate, ingress, &sampler->span_id,
					   extack);
	अगर (err)
		जाओ err_sampler_add;

	sampler->ingress = ingress;
	sampler->local_port = local_port;
	sampler->resource.deकाष्ठाor = mlxsw_afa_sampler_deकाष्ठाor;
	mlxsw_afa_resource_add(block, &sampler->resource);
	वापस sampler;

err_sampler_add:
	kमुक्त(sampler);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक
mlxsw_afa_block_append_allocated_sampler(काष्ठा mlxsw_afa_block *block,
					 u8 mirror_agent, u32 rate)
अणु
	अक्षर *act = mlxsw_afa_block_append_action(block, MLXSW_AFA_SAMPLER_CODE,
						  MLXSW_AFA_SAMPLER_SIZE);

	अगर (IS_ERR(act))
		वापस PTR_ERR(act);
	mlxsw_afa_sampler_pack(act, mirror_agent, rate);
	वापस 0;
पूर्ण

पूर्णांक mlxsw_afa_block_append_sampler(काष्ठा mlxsw_afa_block *block, u8 local_port,
				   काष्ठा psample_group *psample_group,
				   u32 rate, u32 trunc_size, bool truncate,
				   bool ingress,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_afa_sampler *sampler;
	पूर्णांक err;

	अगर (rate > MLXSW_AFA_SAMPLER_RATE_MAX) अणु
		NL_SET_ERR_MSG_MOD(extack, "Sampling rate is too high");
		वापस -EINVAL;
	पूर्ण

	sampler = mlxsw_afa_sampler_create(block, local_port, psample_group,
					   rate, trunc_size, truncate, ingress,
					   extack);
	अगर (IS_ERR(sampler))
		वापस PTR_ERR(sampler);

	err = mlxsw_afa_block_append_allocated_sampler(block, sampler->span_id,
						       rate);
	अगर (err) अणु
		NL_SET_ERR_MSG_MOD(extack, "Cannot append sampler action");
		जाओ err_append_allocated_sampler;
	पूर्ण

	वापस 0;

err_append_allocated_sampler:
	mlxsw_afa_sampler_destroy(block, sampler);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlxsw_afa_block_append_sampler);
