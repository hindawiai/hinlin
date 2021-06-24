<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>

#समावेश "spectrum_mr_tcam.h"
#समावेश "reg.h"
#समावेश "spectrum.h"
#समावेश "core_acl_flex_actions.h"
#समावेश "spectrum_mr.h"

काष्ठा mlxsw_sp_mr_tcam अणु
	व्योम *priv;
पूर्ण;

/* This काष्ठा maps to one RIGR2 रेजिस्टर entry */
काष्ठा mlxsw_sp_mr_erअगर_sublist अणु
	काष्ठा list_head list;
	u32 rigr2_kvdl_index;
	पूर्णांक num_erअगरs;
	u16 erअगर_indices[MLXSW_REG_RIGR2_MAX_ERIFS];
	bool synced;
पूर्ण;

काष्ठा mlxsw_sp_mr_tcam_erअगर_list अणु
	काष्ठा list_head erअगर_sublists;
	u32 kvdl_index;
पूर्ण;

अटल bool
mlxsw_sp_mr_erअगर_sublist_full(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_mr_erअगर_sublist *erअगर_sublist)
अणु
	पूर्णांक erअगर_list_entries = MLXSW_CORE_RES_GET(mlxsw_sp->core,
						   MC_ERIF_LIST_ENTRIES);

	वापस erअगर_sublist->num_erअगरs == erअगर_list_entries;
पूर्ण

अटल व्योम
mlxsw_sp_mr_erअगर_list_init(काष्ठा mlxsw_sp_mr_tcam_erअगर_list *erअगर_list)
अणु
	INIT_LIST_HEAD(&erअगर_list->erअगर_sublists);
पूर्ण

अटल काष्ठा mlxsw_sp_mr_erअगर_sublist *
mlxsw_sp_mr_erअगर_sublist_create(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_mr_tcam_erअगर_list *erअगर_list)
अणु
	काष्ठा mlxsw_sp_mr_erअगर_sublist *erअगर_sublist;
	पूर्णांक err;

	erअगर_sublist = kzalloc(माप(*erअगर_sublist), GFP_KERNEL);
	अगर (!erअगर_sublist)
		वापस ERR_PTR(-ENOMEM);
	err = mlxsw_sp_kvdl_alloc(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_MCRIGR,
				  1, &erअगर_sublist->rigr2_kvdl_index);
	अगर (err) अणु
		kमुक्त(erअगर_sublist);
		वापस ERR_PTR(err);
	पूर्ण

	list_add_tail(&erअगर_sublist->list, &erअगर_list->erअगर_sublists);
	वापस erअगर_sublist;
पूर्ण

अटल व्योम
mlxsw_sp_mr_erअगर_sublist_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_mr_erअगर_sublist *erअगर_sublist)
अणु
	list_del(&erअगर_sublist->list);
	mlxsw_sp_kvdl_मुक्त(mlxsw_sp, MLXSW_SP_KVDL_ENTRY_TYPE_MCRIGR,
			   1, erअगर_sublist->rigr2_kvdl_index);
	kमुक्त(erअगर_sublist);
पूर्ण

अटल पूर्णांक
mlxsw_sp_mr_erअगर_list_add(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_mr_tcam_erअगर_list *erअगर_list,
			  u16 erअगर_index)
अणु
	काष्ठा mlxsw_sp_mr_erअगर_sublist *sublist;

	/* If either there is no erअगर_entry or the last one is full, allocate a
	 * new one.
	 */
	अगर (list_empty(&erअगर_list->erअगर_sublists)) अणु
		sublist = mlxsw_sp_mr_erअगर_sublist_create(mlxsw_sp, erअगर_list);
		अगर (IS_ERR(sublist))
			वापस PTR_ERR(sublist);
		erअगर_list->kvdl_index = sublist->rigr2_kvdl_index;
	पूर्ण अन्यथा अणु
		sublist = list_last_entry(&erअगर_list->erअगर_sublists,
					  काष्ठा mlxsw_sp_mr_erअगर_sublist,
					  list);
		sublist->synced = false;
		अगर (mlxsw_sp_mr_erअगर_sublist_full(mlxsw_sp, sublist)) अणु
			sublist = mlxsw_sp_mr_erअगर_sublist_create(mlxsw_sp,
								  erअगर_list);
			अगर (IS_ERR(sublist))
				वापस PTR_ERR(sublist);
		पूर्ण
	पूर्ण

	/* Add the eRIF to the last entry's last index */
	sublist->erअगर_indices[sublist->num_erअगरs++] = erअगर_index;
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_mr_erअगर_list_flush(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_mr_tcam_erअगर_list *erअगर_list)
अणु
	काष्ठा mlxsw_sp_mr_erअगर_sublist *erअगर_sublist, *पंचांगp;

	list_क्रम_each_entry_safe(erअगर_sublist, पंचांगp, &erअगर_list->erअगर_sublists,
				 list)
		mlxsw_sp_mr_erअगर_sublist_destroy(mlxsw_sp, erअगर_sublist);
पूर्ण

अटल पूर्णांक
mlxsw_sp_mr_erअगर_list_commit(काष्ठा mlxsw_sp *mlxsw_sp,
			     काष्ठा mlxsw_sp_mr_tcam_erअगर_list *erअगर_list)
अणु
	काष्ठा mlxsw_sp_mr_erअगर_sublist *curr_sublist;
	अक्षर rigr2_pl[MLXSW_REG_RIGR2_LEN];
	पूर्णांक err;
	पूर्णांक i;

	list_क्रम_each_entry(curr_sublist, &erअगर_list->erअगर_sublists, list) अणु
		अगर (curr_sublist->synced)
			जारी;

		/* If the sublist is not the last one, pack the next index */
		अगर (list_is_last(&curr_sublist->list,
				 &erअगर_list->erअगर_sublists)) अणु
			mlxsw_reg_rigr2_pack(rigr2_pl,
					     curr_sublist->rigr2_kvdl_index,
					     false, 0);
		पूर्ण अन्यथा अणु
			काष्ठा mlxsw_sp_mr_erअगर_sublist *next_sublist;

			next_sublist = list_next_entry(curr_sublist, list);
			mlxsw_reg_rigr2_pack(rigr2_pl,
					     curr_sublist->rigr2_kvdl_index,
					     true,
					     next_sublist->rigr2_kvdl_index);
		पूर्ण

		/* Pack all the erअगरs */
		क्रम (i = 0; i < curr_sublist->num_erअगरs; i++) अणु
			u16 erअगर_index = curr_sublist->erअगर_indices[i];

			mlxsw_reg_rigr2_erअगर_entry_pack(rigr2_pl, i, true,
							erअगर_index);
		पूर्ण

		/* Write the entry */
		err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(rigr2),
				      rigr2_pl);
		अगर (err)
			/* No need of a rollback here because this
			 * hardware entry should not be poपूर्णांकed yet.
			 */
			वापस err;
		curr_sublist->synced = true;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_mr_erअगर_list_move(काष्ठा mlxsw_sp_mr_tcam_erअगर_list *to,
				       काष्ठा mlxsw_sp_mr_tcam_erअगर_list *from)
अणु
	list_splice(&from->erअगर_sublists, &to->erअगर_sublists);
	to->kvdl_index = from->kvdl_index;
पूर्ण

काष्ठा mlxsw_sp_mr_tcam_route अणु
	काष्ठा mlxsw_sp_mr_tcam_erअगर_list erअगर_list;
	काष्ठा mlxsw_afa_block *afa_block;
	u32 counter_index;
	क्रमागत mlxsw_sp_mr_route_action action;
	काष्ठा mlxsw_sp_mr_route_key key;
	u16 irअगर_index;
	u16 min_mtu;
	व्योम *priv;
पूर्ण;

अटल काष्ठा mlxsw_afa_block *
mlxsw_sp_mr_tcam_afa_block_create(काष्ठा mlxsw_sp *mlxsw_sp,
				  क्रमागत mlxsw_sp_mr_route_action route_action,
				  u16 irअगर_index, u32 counter_index,
				  u16 min_mtu,
				  काष्ठा mlxsw_sp_mr_tcam_erअगर_list *erअगर_list)
अणु
	काष्ठा mlxsw_afa_block *afa_block;
	पूर्णांक err;

	afa_block = mlxsw_afa_block_create(mlxsw_sp->afa);
	अगर (IS_ERR(afa_block))
		वापस afa_block;

	err = mlxsw_afa_block_append_allocated_counter(afa_block,
						       counter_index);
	अगर (err)
		जाओ err;

	चयन (route_action) अणु
	हाल MLXSW_SP_MR_ROUTE_ACTION_TRAP:
		err = mlxsw_afa_block_append_trap(afa_block,
						  MLXSW_TRAP_ID_ACL1);
		अगर (err)
			जाओ err;
		अवरोध;
	हाल MLXSW_SP_MR_ROUTE_ACTION_TRAP_AND_FORWARD:
	हाल MLXSW_SP_MR_ROUTE_ACTION_FORWARD:
		/* If we are about to append a multicast router action, commit
		 * the erअगर_list.
		 */
		err = mlxsw_sp_mr_erअगर_list_commit(mlxsw_sp, erअगर_list);
		अगर (err)
			जाओ err;

		err = mlxsw_afa_block_append_mcrouter(afa_block, irअगर_index,
						      min_mtu, false,
						      erअगर_list->kvdl_index);
		अगर (err)
			जाओ err;

		अगर (route_action == MLXSW_SP_MR_ROUTE_ACTION_TRAP_AND_FORWARD) अणु
			err = mlxsw_afa_block_append_trap_and_क्रमward(afa_block,
								      MLXSW_TRAP_ID_ACL2);
			अगर (err)
				जाओ err;
		पूर्ण
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ err;
	पूर्ण

	err = mlxsw_afa_block_commit(afa_block);
	अगर (err)
		जाओ err;
	वापस afa_block;
err:
	mlxsw_afa_block_destroy(afa_block);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_mr_tcam_afa_block_destroy(काष्ठा mlxsw_afa_block *afa_block)
अणु
	mlxsw_afa_block_destroy(afa_block);
पूर्ण

अटल पूर्णांक
mlxsw_sp_mr_tcam_erअगर_populate(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_mr_tcam_erअगर_list *erअगर_list,
			       काष्ठा mlxsw_sp_mr_route_info *route_info)
अणु
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < route_info->erअगर_num; i++) अणु
		u16 erअगर_index = route_info->erअगर_indices[i];

		err = mlxsw_sp_mr_erअगर_list_add(mlxsw_sp, erअगर_list,
						erअगर_index);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_mr_tcam_route_create(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv,
			      व्योम *route_priv,
			      काष्ठा mlxsw_sp_mr_route_params *route_params)
अणु
	स्थिर काष्ठा mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	काष्ठा mlxsw_sp_mr_tcam_route *route = route_priv;
	काष्ठा mlxsw_sp_mr_tcam *mr_tcam = priv;
	पूर्णांक err;

	route->key = route_params->key;
	route->irअगर_index = route_params->value.irअगर_index;
	route->min_mtu = route_params->value.min_mtu;
	route->action = route_params->value.route_action;

	/* Create the egress RIFs list */
	mlxsw_sp_mr_erअगर_list_init(&route->erअगर_list);
	err = mlxsw_sp_mr_tcam_erअगर_populate(mlxsw_sp, &route->erअगर_list,
					     &route_params->value);
	अगर (err)
		जाओ err_erअगर_populate;

	/* Create the flow counter */
	err = mlxsw_sp_flow_counter_alloc(mlxsw_sp, &route->counter_index);
	अगर (err)
		जाओ err_counter_alloc;

	/* Create the flexible action block */
	route->afa_block = mlxsw_sp_mr_tcam_afa_block_create(mlxsw_sp,
							     route->action,
							     route->irअगर_index,
							     route->counter_index,
							     route->min_mtu,
							     &route->erअगर_list);
	अगर (IS_ERR(route->afa_block)) अणु
		err = PTR_ERR(route->afa_block);
		जाओ err_afa_block_create;
	पूर्ण

	route->priv = kzalloc(ops->route_priv_size, GFP_KERNEL);
	अगर (!route->priv) अणु
		err = -ENOMEM;
		जाओ err_route_priv_alloc;
	पूर्ण

	/* Write the route to the TCAM */
	err = ops->route_create(mlxsw_sp, mr_tcam->priv, route->priv,
				&route->key, route->afa_block,
				route_params->prio);
	अगर (err)
		जाओ err_route_create;
	वापस 0;

err_route_create:
	kमुक्त(route->priv);
err_route_priv_alloc:
	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
err_afa_block_create:
	mlxsw_sp_flow_counter_मुक्त(mlxsw_sp, route->counter_index);
err_erअगर_populate:
err_counter_alloc:
	mlxsw_sp_mr_erअगर_list_flush(mlxsw_sp, &route->erअगर_list);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_mr_tcam_route_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
					   व्योम *priv, व्योम *route_priv)
अणु
	स्थिर काष्ठा mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	काष्ठा mlxsw_sp_mr_tcam_route *route = route_priv;
	काष्ठा mlxsw_sp_mr_tcam *mr_tcam = priv;

	ops->route_destroy(mlxsw_sp, mr_tcam->priv, route->priv, &route->key);
	kमुक्त(route->priv);
	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
	mlxsw_sp_flow_counter_मुक्त(mlxsw_sp, route->counter_index);
	mlxsw_sp_mr_erअगर_list_flush(mlxsw_sp, &route->erअगर_list);
पूर्ण

अटल पूर्णांक mlxsw_sp_mr_tcam_route_stats(काष्ठा mlxsw_sp *mlxsw_sp,
					व्योम *route_priv, u64 *packets,
					u64 *bytes)
अणु
	काष्ठा mlxsw_sp_mr_tcam_route *route = route_priv;

	वापस mlxsw_sp_flow_counter_get(mlxsw_sp, route->counter_index,
					 packets, bytes);
पूर्ण

अटल पूर्णांक
mlxsw_sp_mr_tcam_route_action_update(काष्ठा mlxsw_sp *mlxsw_sp,
				     व्योम *route_priv,
				     क्रमागत mlxsw_sp_mr_route_action route_action)
अणु
	स्थिर काष्ठा mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	काष्ठा mlxsw_sp_mr_tcam_route *route = route_priv;
	काष्ठा mlxsw_afa_block *afa_block;
	पूर्णांक err;

	/* Create a new flexible action block */
	afa_block = mlxsw_sp_mr_tcam_afa_block_create(mlxsw_sp, route_action,
						      route->irअगर_index,
						      route->counter_index,
						      route->min_mtu,
						      &route->erअगर_list);
	अगर (IS_ERR(afa_block))
		वापस PTR_ERR(afa_block);

	/* Update the TCAM route entry */
	err = ops->route_update(mlxsw_sp, route->priv, &route->key, afa_block);
	अगर (err)
		जाओ err;

	/* Delete the old one */
	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
	route->afa_block = afa_block;
	route->action = route_action;
	वापस 0;
err:
	mlxsw_sp_mr_tcam_afa_block_destroy(afa_block);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_mr_tcam_route_min_mtu_update(काष्ठा mlxsw_sp *mlxsw_sp,
						 व्योम *route_priv, u16 min_mtu)
अणु
	स्थिर काष्ठा mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	काष्ठा mlxsw_sp_mr_tcam_route *route = route_priv;
	काष्ठा mlxsw_afa_block *afa_block;
	पूर्णांक err;

	/* Create a new flexible action block */
	afa_block = mlxsw_sp_mr_tcam_afa_block_create(mlxsw_sp,
						      route->action,
						      route->irअगर_index,
						      route->counter_index,
						      min_mtu,
						      &route->erअगर_list);
	अगर (IS_ERR(afa_block))
		वापस PTR_ERR(afa_block);

	/* Update the TCAM route entry */
	err = ops->route_update(mlxsw_sp, route->priv, &route->key, afa_block);
	अगर (err)
		जाओ err;

	/* Delete the old one */
	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
	route->afa_block = afa_block;
	route->min_mtu = min_mtu;
	वापस 0;
err:
	mlxsw_sp_mr_tcam_afa_block_destroy(afa_block);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_mr_tcam_route_irअगर_update(काष्ठा mlxsw_sp *mlxsw_sp,
					      व्योम *route_priv, u16 irअगर_index)
अणु
	काष्ठा mlxsw_sp_mr_tcam_route *route = route_priv;

	अगर (route->action != MLXSW_SP_MR_ROUTE_ACTION_TRAP)
		वापस -EINVAL;
	route->irअगर_index = irअगर_index;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_mr_tcam_route_erअगर_add(काष्ठा mlxsw_sp *mlxsw_sp,
					   व्योम *route_priv, u16 erअगर_index)
अणु
	काष्ठा mlxsw_sp_mr_tcam_route *route = route_priv;
	पूर्णांक err;

	err = mlxsw_sp_mr_erअगर_list_add(mlxsw_sp, &route->erअगर_list,
					erअगर_index);
	अगर (err)
		वापस err;

	/* Commit the action only अगर the route action is not TRAP */
	अगर (route->action != MLXSW_SP_MR_ROUTE_ACTION_TRAP)
		वापस mlxsw_sp_mr_erअगर_list_commit(mlxsw_sp,
						    &route->erअगर_list);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_mr_tcam_route_erअगर_del(काष्ठा mlxsw_sp *mlxsw_sp,
					   व्योम *route_priv, u16 erअगर_index)
अणु
	स्थिर काष्ठा mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	काष्ठा mlxsw_sp_mr_tcam_route *route = route_priv;
	काष्ठा mlxsw_sp_mr_erअगर_sublist *erअगर_sublist;
	काष्ठा mlxsw_sp_mr_tcam_erअगर_list erअगर_list;
	काष्ठा mlxsw_afa_block *afa_block;
	पूर्णांक err;
	पूर्णांक i;

	/* Create a copy of the original erअगर_list without the deleted entry */
	mlxsw_sp_mr_erअगर_list_init(&erअगर_list);
	list_क्रम_each_entry(erअगर_sublist, &route->erअगर_list.erअगर_sublists, list) अणु
		क्रम (i = 0; i < erअगर_sublist->num_erअगरs; i++) अणु
			u16 curr_erअगर = erअगर_sublist->erअगर_indices[i];

			अगर (curr_erअगर == erअगर_index)
				जारी;
			err = mlxsw_sp_mr_erअगर_list_add(mlxsw_sp, &erअगर_list,
							curr_erअगर);
			अगर (err)
				जाओ err_erअगर_list_add;
		पूर्ण
	पूर्ण

	/* Create the flexible action block poपूर्णांकing to the new erअगर_list */
	afa_block = mlxsw_sp_mr_tcam_afa_block_create(mlxsw_sp, route->action,
						      route->irअगर_index,
						      route->counter_index,
						      route->min_mtu,
						      &erअगर_list);
	अगर (IS_ERR(afa_block)) अणु
		err = PTR_ERR(afa_block);
		जाओ err_afa_block_create;
	पूर्ण

	/* Update the TCAM route entry */
	err = ops->route_update(mlxsw_sp, route->priv, &route->key, afa_block);
	अगर (err)
		जाओ err_route_ग_लिखो;

	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
	mlxsw_sp_mr_erअगर_list_flush(mlxsw_sp, &route->erअगर_list);
	route->afa_block = afa_block;
	mlxsw_sp_mr_erअगर_list_move(&route->erअगर_list, &erअगर_list);
	वापस 0;

err_route_ग_लिखो:
	mlxsw_sp_mr_tcam_afa_block_destroy(afa_block);
err_afa_block_create:
err_erअगर_list_add:
	mlxsw_sp_mr_erअगर_list_flush(mlxsw_sp, &erअगर_list);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_mr_tcam_route_update(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *route_priv,
			      काष्ठा mlxsw_sp_mr_route_info *route_info)
अणु
	स्थिर काष्ठा mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	काष्ठा mlxsw_sp_mr_tcam_route *route = route_priv;
	काष्ठा mlxsw_sp_mr_tcam_erअगर_list erअगर_list;
	काष्ठा mlxsw_afa_block *afa_block;
	पूर्णांक err;

	/* Create a new erअगर_list */
	mlxsw_sp_mr_erअगर_list_init(&erअगर_list);
	err = mlxsw_sp_mr_tcam_erअगर_populate(mlxsw_sp, &erअगर_list, route_info);
	अगर (err)
		जाओ err_erअगर_populate;

	/* Create the flexible action block poपूर्णांकing to the new erअगर_list */
	afa_block = mlxsw_sp_mr_tcam_afa_block_create(mlxsw_sp,
						      route_info->route_action,
						      route_info->irअगर_index,
						      route->counter_index,
						      route_info->min_mtu,
						      &erअगर_list);
	अगर (IS_ERR(afa_block)) अणु
		err = PTR_ERR(afa_block);
		जाओ err_afa_block_create;
	पूर्ण

	/* Update the TCAM route entry */
	err = ops->route_update(mlxsw_sp, route->priv, &route->key, afa_block);
	अगर (err)
		जाओ err_route_ग_लिखो;

	mlxsw_sp_mr_tcam_afa_block_destroy(route->afa_block);
	mlxsw_sp_mr_erअगर_list_flush(mlxsw_sp, &route->erअगर_list);
	route->afa_block = afa_block;
	mlxsw_sp_mr_erअगर_list_move(&route->erअगर_list, &erअगर_list);
	route->action = route_info->route_action;
	route->irअगर_index = route_info->irअगर_index;
	route->min_mtu = route_info->min_mtu;
	वापस 0;

err_route_ग_लिखो:
	mlxsw_sp_mr_tcam_afa_block_destroy(afa_block);
err_afa_block_create:
err_erअगर_populate:
	mlxsw_sp_mr_erअगर_list_flush(mlxsw_sp, &erअगर_list);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_mr_tcam_init(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
	स्थिर काष्ठा mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	काष्ठा mlxsw_sp_mr_tcam *mr_tcam = priv;
	पूर्णांक err;

	अगर (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MC_ERIF_LIST_ENTRIES))
		वापस -EIO;

	mr_tcam->priv = kzalloc(ops->priv_size, GFP_KERNEL);
	अगर (!mr_tcam->priv)
		वापस -ENOMEM;

	err = ops->init(mlxsw_sp, mr_tcam->priv);
	अगर (err)
		जाओ err_init;
	वापस 0;

err_init:
	kमुक्त(mr_tcam->priv);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_mr_tcam_fini(काष्ठा mlxsw_sp *mlxsw_sp, व्योम *priv)
अणु
	स्थिर काष्ठा mlxsw_sp_mr_tcam_ops *ops = mlxsw_sp->mr_tcam_ops;
	काष्ठा mlxsw_sp_mr_tcam *mr_tcam = priv;

	ops->fini(mr_tcam->priv);
	kमुक्त(mr_tcam->priv);
पूर्ण

स्थिर काष्ठा mlxsw_sp_mr_ops mlxsw_sp_mr_tcam_ops = अणु
	.priv_size = माप(काष्ठा mlxsw_sp_mr_tcam),
	.route_priv_size = माप(काष्ठा mlxsw_sp_mr_tcam_route),
	.init = mlxsw_sp_mr_tcam_init,
	.route_create = mlxsw_sp_mr_tcam_route_create,
	.route_update = mlxsw_sp_mr_tcam_route_update,
	.route_stats = mlxsw_sp_mr_tcam_route_stats,
	.route_action_update = mlxsw_sp_mr_tcam_route_action_update,
	.route_min_mtu_update = mlxsw_sp_mr_tcam_route_min_mtu_update,
	.route_irअगर_update = mlxsw_sp_mr_tcam_route_irअगर_update,
	.route_erअगर_add = mlxsw_sp_mr_tcam_route_erअगर_add,
	.route_erअगर_del = mlxsw_sp_mr_tcam_route_erअगर_del,
	.route_destroy = mlxsw_sp_mr_tcam_route_destroy,
	.fini = mlxsw_sp_mr_tcam_fini,
पूर्ण;
