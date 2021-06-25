<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/mutex.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/ipv6.h>

#समावेश "spectrum_mr.h"
#समावेश "spectrum_router.h"

काष्ठा mlxsw_sp_mr अणु
	स्थिर काष्ठा mlxsw_sp_mr_ops *mr_ops;
	व्योम *catchall_route_priv;
	काष्ठा delayed_work stats_update_dw;
	काष्ठा list_head table_list;
	काष्ठा mutex table_list_lock; /* Protects table_list */
#घोषणा MLXSW_SP_MR_ROUTES_COUNTER_UPDATE_INTERVAL 5000 /* ms */
	अचिन्हित दीर्घ priv[];
	/* priv has to be always the last item */
पूर्ण;

काष्ठा mlxsw_sp_mr_vअगर;
काष्ठा mlxsw_sp_mr_vअगर_ops अणु
	bool (*is_regular)(स्थिर काष्ठा mlxsw_sp_mr_vअगर *vअगर);
पूर्ण;

काष्ठा mlxsw_sp_mr_vअगर अणु
	काष्ठा net_device *dev;
	स्थिर काष्ठा mlxsw_sp_rअगर *rअगर;
	अचिन्हित दीर्घ vअगर_flags;

	/* A list of route_vअगर_entry काष्ठाs that poपूर्णांक to routes that the VIF
	 * instance is used as one of the egress VIFs
	 */
	काष्ठा list_head route_evअगर_list;

	/* A list of route_vअगर_entry काष्ठाs that poपूर्णांक to routes that the VIF
	 * instance is used as an ingress VIF
	 */
	काष्ठा list_head route_ivअगर_list;

	/* Protocol specअगरic operations क्रम a VIF */
	स्थिर काष्ठा mlxsw_sp_mr_vअगर_ops *ops;
पूर्ण;

काष्ठा mlxsw_sp_mr_route_vअगर_entry अणु
	काष्ठा list_head vअगर_node;
	काष्ठा list_head route_node;
	काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर;
	काष्ठा mlxsw_sp_mr_route *mr_route;
पूर्ण;

काष्ठा mlxsw_sp_mr_table;
काष्ठा mlxsw_sp_mr_table_ops अणु
	bool (*is_route_valid)(स्थिर काष्ठा mlxsw_sp_mr_table *mr_table,
			       स्थिर काष्ठा mr_mfc *mfc);
	व्योम (*key_create)(काष्ठा mlxsw_sp_mr_table *mr_table,
			   काष्ठा mlxsw_sp_mr_route_key *key,
			   काष्ठा mr_mfc *mfc);
	bool (*is_route_starg)(स्थिर काष्ठा mlxsw_sp_mr_table *mr_table,
			       स्थिर काष्ठा mlxsw_sp_mr_route *mr_route);
पूर्ण;

काष्ठा mlxsw_sp_mr_table अणु
	काष्ठा list_head node;
	क्रमागत mlxsw_sp_l3proto proto;
	काष्ठा mlxsw_sp *mlxsw_sp;
	u32 vr_id;
	काष्ठा mlxsw_sp_mr_vअगर vअगरs[MAXVIFS];
	काष्ठा list_head route_list;
	काष्ठा mutex route_list_lock; /* Protects route_list */
	काष्ठा rhashtable route_ht;
	स्थिर काष्ठा mlxsw_sp_mr_table_ops *ops;
	अक्षर catchall_route_priv[];
	/* catchall_route_priv has to be always the last item */
पूर्ण;

काष्ठा mlxsw_sp_mr_route अणु
	काष्ठा list_head node;
	काष्ठा rhash_head ht_node;
	काष्ठा mlxsw_sp_mr_route_key key;
	क्रमागत mlxsw_sp_mr_route_action route_action;
	u16 min_mtu;
	काष्ठा mr_mfc *mfc;
	व्योम *route_priv;
	स्थिर काष्ठा mlxsw_sp_mr_table *mr_table;
	/* A list of route_vअगर_entry काष्ठाs that poपूर्णांक to the egress VIFs */
	काष्ठा list_head evअगर_list;
	/* A route_vअगर_entry काष्ठा that poपूर्णांक to the ingress VIF */
	काष्ठा mlxsw_sp_mr_route_vअगर_entry ivअगर;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_mr_route_ht_params = अणु
	.key_len = माप(काष्ठा mlxsw_sp_mr_route_key),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_mr_route, key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_mr_route, ht_node),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल bool mlxsw_sp_mr_vअगर_valid(स्थिर काष्ठा mlxsw_sp_mr_vअगर *vअगर)
अणु
	वापस vअगर->ops->is_regular(vअगर) && vअगर->dev && vअगर->rअगर;
पूर्ण

अटल bool mlxsw_sp_mr_vअगर_exists(स्थिर काष्ठा mlxsw_sp_mr_vअगर *vअगर)
अणु
	वापस vअगर->dev;
पूर्ण

अटल bool
mlxsw_sp_mr_route_ivअगर_in_evअगरs(स्थिर काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	vअगरi_t ivअगर = mr_route->mfc->mfc_parent;

	वापस mr_route->mfc->mfc_un.res.ttls[ivअगर] != 255;
पूर्ण

अटल पूर्णांक
mlxsw_sp_mr_route_valid_evअगरs_num(स्थिर काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve;
	पूर्णांक valid_evअगरs;

	valid_evअगरs = 0;
	list_क्रम_each_entry(rve, &mr_route->evअगर_list, route_node)
		अगर (mlxsw_sp_mr_vअगर_valid(rve->mr_vअगर))
			valid_evअगरs++;
	वापस valid_evअगरs;
पूर्ण

अटल क्रमागत mlxsw_sp_mr_route_action
mlxsw_sp_mr_route_action(स्थिर काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve;

	/* If the ingress port is not regular and resolved, trap the route */
	अगर (!mlxsw_sp_mr_vअगर_valid(mr_route->ivअगर.mr_vअगर))
		वापस MLXSW_SP_MR_ROUTE_ACTION_TRAP;

	/* The kernel करोes not match a (*,G) route that the ingress पूर्णांकerface is
	 * not one of the egress पूर्णांकerfaces, so trap these kind of routes.
	 */
	अगर (mr_route->mr_table->ops->is_route_starg(mr_route->mr_table,
						    mr_route) &&
	    !mlxsw_sp_mr_route_ivअगर_in_evअगरs(mr_route))
		वापस MLXSW_SP_MR_ROUTE_ACTION_TRAP;

	/* If the route has no valid eVIFs, trap it. */
	अगर (!mlxsw_sp_mr_route_valid_evअगरs_num(mr_route))
		वापस MLXSW_SP_MR_ROUTE_ACTION_TRAP;

	/* If one of the eVIFs has no RIF, trap-and-क्रमward the route as there
	 * is some more routing to करो in software too.
	 */
	list_क्रम_each_entry(rve, &mr_route->evअगर_list, route_node)
		अगर (mlxsw_sp_mr_vअगर_exists(rve->mr_vअगर) && !rve->mr_vअगर->rअगर)
			वापस MLXSW_SP_MR_ROUTE_ACTION_TRAP_AND_FORWARD;

	वापस MLXSW_SP_MR_ROUTE_ACTION_FORWARD;
पूर्ण

अटल क्रमागत mlxsw_sp_mr_route_prio
mlxsw_sp_mr_route_prio(स्थिर काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	वापस mr_route->mr_table->ops->is_route_starg(mr_route->mr_table,
						       mr_route) ?
		MLXSW_SP_MR_ROUTE_PRIO_STARG : MLXSW_SP_MR_ROUTE_PRIO_SG;
पूर्ण

अटल पूर्णांक mlxsw_sp_mr_route_evअगर_link(काष्ठा mlxsw_sp_mr_route *mr_route,
				       काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर)
अणु
	काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve;

	rve = kzalloc(माप(*rve), GFP_KERNEL);
	अगर (!rve)
		वापस -ENOMEM;
	rve->mr_route = mr_route;
	rve->mr_vअगर = mr_vअगर;
	list_add_tail(&rve->route_node, &mr_route->evअगर_list);
	list_add_tail(&rve->vअगर_node, &mr_vअगर->route_evअगर_list);
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_mr_route_evअगर_unlink(काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve)
अणु
	list_del(&rve->route_node);
	list_del(&rve->vअगर_node);
	kमुक्त(rve);
पूर्ण

अटल व्योम mlxsw_sp_mr_route_ivअगर_link(काष्ठा mlxsw_sp_mr_route *mr_route,
					काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर)
अणु
	mr_route->ivअगर.mr_route = mr_route;
	mr_route->ivअगर.mr_vअगर = mr_vअगर;
	list_add_tail(&mr_route->ivअगर.vअगर_node, &mr_vअगर->route_ivअगर_list);
पूर्ण

अटल व्योम mlxsw_sp_mr_route_ivअगर_unlink(काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	list_del(&mr_route->ivअगर.vअगर_node);
पूर्ण

अटल पूर्णांक
mlxsw_sp_mr_route_info_create(काष्ठा mlxsw_sp_mr_table *mr_table,
			      काष्ठा mlxsw_sp_mr_route *mr_route,
			      काष्ठा mlxsw_sp_mr_route_info *route_info)
अणु
	काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve;
	u16 *erअगर_indices;
	u16 irअगर_index;
	u16 erअगर = 0;

	erअगर_indices = kदो_स्मृति_array(MAXVIFS, माप(*erअगर_indices),
				     GFP_KERNEL);
	अगर (!erअगर_indices)
		वापस -ENOMEM;

	list_क्रम_each_entry(rve, &mr_route->evअगर_list, route_node) अणु
		अगर (mlxsw_sp_mr_vअगर_valid(rve->mr_vअगर)) अणु
			u16 rअगरi = mlxsw_sp_rअगर_index(rve->mr_vअगर->rअगर);

			erअगर_indices[erअगर++] = rअगरi;
		पूर्ण
	पूर्ण

	अगर (mlxsw_sp_mr_vअगर_valid(mr_route->ivअगर.mr_vअगर))
		irअगर_index = mlxsw_sp_rअगर_index(mr_route->ivअगर.mr_vअगर->rअगर);
	अन्यथा
		irअगर_index = 0;

	route_info->irअगर_index = irअगर_index;
	route_info->erअगर_indices = erअगर_indices;
	route_info->min_mtu = mr_route->min_mtu;
	route_info->route_action = mr_route->route_action;
	route_info->erअगर_num = erअगर;
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_mr_route_info_destroy(काष्ठा mlxsw_sp_mr_route_info *route_info)
अणु
	kमुक्त(route_info->erअगर_indices);
पूर्ण

अटल पूर्णांक mlxsw_sp_mr_route_ग_लिखो(काष्ठा mlxsw_sp_mr_table *mr_table,
				   काष्ठा mlxsw_sp_mr_route *mr_route,
				   bool replace)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	काष्ठा mlxsw_sp_mr_route_info route_info;
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;
	पूर्णांक err;

	err = mlxsw_sp_mr_route_info_create(mr_table, mr_route, &route_info);
	अगर (err)
		वापस err;

	अगर (!replace) अणु
		काष्ठा mlxsw_sp_mr_route_params route_params;

		mr_route->route_priv = kzalloc(mr->mr_ops->route_priv_size,
					       GFP_KERNEL);
		अगर (!mr_route->route_priv) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		route_params.key = mr_route->key;
		route_params.value = route_info;
		route_params.prio = mlxsw_sp_mr_route_prio(mr_route);
		err = mr->mr_ops->route_create(mlxsw_sp, mr->priv,
					       mr_route->route_priv,
					       &route_params);
		अगर (err)
			kमुक्त(mr_route->route_priv);
	पूर्ण अन्यथा अणु
		err = mr->mr_ops->route_update(mlxsw_sp, mr_route->route_priv,
					       &route_info);
	पूर्ण
out:
	mlxsw_sp_mr_route_info_destroy(&route_info);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_mr_route_erase(काष्ठा mlxsw_sp_mr_table *mr_table,
				    काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;

	mr->mr_ops->route_destroy(mlxsw_sp, mr->priv, mr_route->route_priv);
	kमुक्त(mr_route->route_priv);
पूर्ण

अटल काष्ठा mlxsw_sp_mr_route *
mlxsw_sp_mr_route_create(काष्ठा mlxsw_sp_mr_table *mr_table,
			 काष्ठा mr_mfc *mfc)
अणु
	काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve, *पंचांगp;
	काष्ठा mlxsw_sp_mr_route *mr_route;
	पूर्णांक err = 0;
	पूर्णांक i;

	/* Allocate and init a new route and fill it with parameters */
	mr_route = kzalloc(माप(*mr_route), GFP_KERNEL);
	अगर (!mr_route)
		वापस ERR_PTR(-ENOMEM);
	INIT_LIST_HEAD(&mr_route->evअगर_list);

	/* Find min_mtu and link iVIF and eVIFs */
	mr_route->min_mtu = ETH_MAX_MTU;
	mr_cache_hold(mfc);
	mr_route->mfc = mfc;
	mr_table->ops->key_create(mr_table, &mr_route->key, mr_route->mfc);

	mr_route->mr_table = mr_table;
	क्रम (i = 0; i < MAXVIFS; i++) अणु
		अगर (mfc->mfc_un.res.ttls[i] != 255) अणु
			err = mlxsw_sp_mr_route_evअगर_link(mr_route,
							  &mr_table->vअगरs[i]);
			अगर (err)
				जाओ err;
			अगर (mr_table->vअगरs[i].dev &&
			    mr_table->vअगरs[i].dev->mtu < mr_route->min_mtu)
				mr_route->min_mtu = mr_table->vअगरs[i].dev->mtu;
		पूर्ण
	पूर्ण
	mlxsw_sp_mr_route_ivअगर_link(mr_route,
				    &mr_table->vअगरs[mfc->mfc_parent]);

	mr_route->route_action = mlxsw_sp_mr_route_action(mr_route);
	वापस mr_route;
err:
	mr_cache_put(mfc);
	list_क्रम_each_entry_safe(rve, पंचांगp, &mr_route->evअगर_list, route_node)
		mlxsw_sp_mr_route_evअगर_unlink(rve);
	kमुक्त(mr_route);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_mr_route_destroy(काष्ठा mlxsw_sp_mr_table *mr_table,
				      काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve, *पंचांगp;

	mlxsw_sp_mr_route_ivअगर_unlink(mr_route);
	mr_cache_put(mr_route->mfc);
	list_क्रम_each_entry_safe(rve, पंचांगp, &mr_route->evअगर_list, route_node)
		mlxsw_sp_mr_route_evअगर_unlink(rve);
	kमुक्त(mr_route);
पूर्ण

अटल व्योम mlxsw_sp_mr_mfc_offload_set(काष्ठा mlxsw_sp_mr_route *mr_route,
					bool offload)
अणु
	अगर (offload)
		mr_route->mfc->mfc_flags |= MFC_OFFLOAD;
	अन्यथा
		mr_route->mfc->mfc_flags &= ~MFC_OFFLOAD;
पूर्ण

अटल व्योम mlxsw_sp_mr_mfc_offload_update(काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	bool offload;

	offload = mr_route->route_action != MLXSW_SP_MR_ROUTE_ACTION_TRAP;
	mlxsw_sp_mr_mfc_offload_set(mr_route, offload);
पूर्ण

अटल व्योम __mlxsw_sp_mr_route_del(काष्ठा mlxsw_sp_mr_table *mr_table,
				    काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	WARN_ON_ONCE(!mutex_is_locked(&mr_table->route_list_lock));

	mlxsw_sp_mr_mfc_offload_set(mr_route, false);
	rhashtable_हटाओ_fast(&mr_table->route_ht, &mr_route->ht_node,
			       mlxsw_sp_mr_route_ht_params);
	list_del(&mr_route->node);
	mlxsw_sp_mr_route_erase(mr_table, mr_route);
	mlxsw_sp_mr_route_destroy(mr_table, mr_route);
पूर्ण

पूर्णांक mlxsw_sp_mr_route_add(काष्ठा mlxsw_sp_mr_table *mr_table,
			  काष्ठा mr_mfc *mfc, bool replace)
अणु
	काष्ठा mlxsw_sp_mr_route *mr_orig_route = शून्य;
	काष्ठा mlxsw_sp_mr_route *mr_route;
	पूर्णांक err;

	अगर (!mr_table->ops->is_route_valid(mr_table, mfc))
		वापस -EINVAL;

	/* Create a new route */
	mr_route = mlxsw_sp_mr_route_create(mr_table, mfc);
	अगर (IS_ERR(mr_route))
		वापस PTR_ERR(mr_route);

	/* Find any route with a matching key */
	mr_orig_route = rhashtable_lookup_fast(&mr_table->route_ht,
					       &mr_route->key,
					       mlxsw_sp_mr_route_ht_params);
	अगर (replace) अणु
		/* On replace हाल, make the route poपूर्णांक to the new route_priv.
		 */
		अगर (WARN_ON(!mr_orig_route)) अणु
			err = -ENOENT;
			जाओ err_no_orig_route;
		पूर्ण
		mr_route->route_priv = mr_orig_route->route_priv;
	पूर्ण अन्यथा अगर (mr_orig_route) अणु
		/* On non replace हाल, अगर another route with the same key was
		 * found, पात, as duplicate routes are used क्रम proxy routes.
		 */
		dev_warn(mr_table->mlxsw_sp->bus_info->dev,
			 "Offloading proxy routes is not supported.\n");
		err = -EINVAL;
		जाओ err_duplicate_route;
	पूर्ण

	/* Write the route to the hardware */
	err = mlxsw_sp_mr_route_ग_लिखो(mr_table, mr_route, replace);
	अगर (err)
		जाओ err_mr_route_ग_लिखो;

	/* Put it in the table data-काष्ठाures */
	mutex_lock(&mr_table->route_list_lock);
	list_add_tail(&mr_route->node, &mr_table->route_list);
	mutex_unlock(&mr_table->route_list_lock);
	err = rhashtable_insert_fast(&mr_table->route_ht,
				     &mr_route->ht_node,
				     mlxsw_sp_mr_route_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	/* Destroy the original route */
	अगर (replace) अणु
		rhashtable_हटाओ_fast(&mr_table->route_ht,
				       &mr_orig_route->ht_node,
				       mlxsw_sp_mr_route_ht_params);
		list_del(&mr_orig_route->node);
		mlxsw_sp_mr_route_destroy(mr_table, mr_orig_route);
	पूर्ण

	mlxsw_sp_mr_mfc_offload_update(mr_route);
	वापस 0;

err_rhashtable_insert:
	mutex_lock(&mr_table->route_list_lock);
	list_del(&mr_route->node);
	mutex_unlock(&mr_table->route_list_lock);
	mlxsw_sp_mr_route_erase(mr_table, mr_route);
err_mr_route_ग_लिखो:
err_no_orig_route:
err_duplicate_route:
	mlxsw_sp_mr_route_destroy(mr_table, mr_route);
	वापस err;
पूर्ण

व्योम mlxsw_sp_mr_route_del(काष्ठा mlxsw_sp_mr_table *mr_table,
			   काष्ठा mr_mfc *mfc)
अणु
	काष्ठा mlxsw_sp_mr_route *mr_route;
	काष्ठा mlxsw_sp_mr_route_key key;

	mr_table->ops->key_create(mr_table, &key, mfc);
	mr_route = rhashtable_lookup_fast(&mr_table->route_ht, &key,
					  mlxsw_sp_mr_route_ht_params);
	अगर (mr_route) अणु
		mutex_lock(&mr_table->route_list_lock);
		__mlxsw_sp_mr_route_del(mr_table, mr_route);
		mutex_unlock(&mr_table->route_list_lock);
	पूर्ण
पूर्ण

/* Should be called after the VIF काष्ठा is updated */
अटल पूर्णांक
mlxsw_sp_mr_route_ivअगर_resolve(काष्ठा mlxsw_sp_mr_table *mr_table,
			       काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	क्रमागत mlxsw_sp_mr_route_action route_action;
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;
	u16 irअगर_index;
	पूर्णांक err;

	route_action = mlxsw_sp_mr_route_action(rve->mr_route);
	अगर (route_action == MLXSW_SP_MR_ROUTE_ACTION_TRAP)
		वापस 0;

	/* rve->mr_vअगर->rअगर is guaranteed to be valid at this stage */
	irअगर_index = mlxsw_sp_rअगर_index(rve->mr_vअगर->rअगर);
	err = mr->mr_ops->route_irअगर_update(mlxsw_sp, rve->mr_route->route_priv,
					    irअगर_index);
	अगर (err)
		वापस err;

	err = mr->mr_ops->route_action_update(mlxsw_sp,
					      rve->mr_route->route_priv,
					      route_action);
	अगर (err)
		/* No need to rollback here because the iRIF change only takes
		 * place after the action has been updated.
		 */
		वापस err;

	rve->mr_route->route_action = route_action;
	mlxsw_sp_mr_mfc_offload_update(rve->mr_route);
	वापस 0;
पूर्ण

अटल व्योम
mlxsw_sp_mr_route_ivअगर_unresolve(काष्ठा mlxsw_sp_mr_table *mr_table,
				 काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;

	mr->mr_ops->route_action_update(mlxsw_sp, rve->mr_route->route_priv,
					MLXSW_SP_MR_ROUTE_ACTION_TRAP);
	rve->mr_route->route_action = MLXSW_SP_MR_ROUTE_ACTION_TRAP;
	mlxsw_sp_mr_mfc_offload_update(rve->mr_route);
पूर्ण

/* Should be called after the RIF काष्ठा is updated */
अटल पूर्णांक
mlxsw_sp_mr_route_evअगर_resolve(काष्ठा mlxsw_sp_mr_table *mr_table,
			       काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	क्रमागत mlxsw_sp_mr_route_action route_action;
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;
	u16 erअगर_index = 0;
	पूर्णांक err;

	/* Add the eRIF */
	अगर (mlxsw_sp_mr_vअगर_valid(rve->mr_vअगर)) अणु
		erअगर_index = mlxsw_sp_rअगर_index(rve->mr_vअगर->rअगर);
		err = mr->mr_ops->route_erअगर_add(mlxsw_sp,
						 rve->mr_route->route_priv,
						 erअगर_index);
		अगर (err)
			वापस err;
	पूर्ण

	/* Update the route action, as the new eVIF can be a tunnel or a pimreg
	 * device which will require updating the action.
	 */
	route_action = mlxsw_sp_mr_route_action(rve->mr_route);
	अगर (route_action != rve->mr_route->route_action) अणु
		err = mr->mr_ops->route_action_update(mlxsw_sp,
						      rve->mr_route->route_priv,
						      route_action);
		अगर (err)
			जाओ err_route_action_update;
	पूर्ण

	/* Update the minimum MTU */
	अगर (rve->mr_vअगर->dev->mtu < rve->mr_route->min_mtu) अणु
		rve->mr_route->min_mtu = rve->mr_vअगर->dev->mtu;
		err = mr->mr_ops->route_min_mtu_update(mlxsw_sp,
						       rve->mr_route->route_priv,
						       rve->mr_route->min_mtu);
		अगर (err)
			जाओ err_route_min_mtu_update;
	पूर्ण

	rve->mr_route->route_action = route_action;
	mlxsw_sp_mr_mfc_offload_update(rve->mr_route);
	वापस 0;

err_route_min_mtu_update:
	अगर (route_action != rve->mr_route->route_action)
		mr->mr_ops->route_action_update(mlxsw_sp,
						rve->mr_route->route_priv,
						rve->mr_route->route_action);
err_route_action_update:
	अगर (mlxsw_sp_mr_vअगर_valid(rve->mr_vअगर))
		mr->mr_ops->route_erअगर_del(mlxsw_sp, rve->mr_route->route_priv,
					   erअगर_index);
	वापस err;
पूर्ण

/* Should be called beक्रमe the RIF काष्ठा is updated */
अटल व्योम
mlxsw_sp_mr_route_evअगर_unresolve(काष्ठा mlxsw_sp_mr_table *mr_table,
				 काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	क्रमागत mlxsw_sp_mr_route_action route_action;
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;
	u16 rअगरi;

	/* If the unresolved RIF was not valid, no need to delete it */
	अगर (!mlxsw_sp_mr_vअगर_valid(rve->mr_vअगर))
		वापस;

	/* Update the route action: अगर there is only one valid eVIF in the
	 * route, set the action to trap as the VIF deletion will lead to zero
	 * valid eVIFs. On any other हाल, use the mlxsw_sp_mr_route_action to
	 * determine the route action.
	 */
	अगर (mlxsw_sp_mr_route_valid_evअगरs_num(rve->mr_route) == 1)
		route_action = MLXSW_SP_MR_ROUTE_ACTION_TRAP;
	अन्यथा
		route_action = mlxsw_sp_mr_route_action(rve->mr_route);
	अगर (route_action != rve->mr_route->route_action)
		mr->mr_ops->route_action_update(mlxsw_sp,
						rve->mr_route->route_priv,
						route_action);

	/* Delete the erअगर from the route */
	rअगरi = mlxsw_sp_rअगर_index(rve->mr_vअगर->rअगर);
	mr->mr_ops->route_erअगर_del(mlxsw_sp, rve->mr_route->route_priv, rअगरi);
	rve->mr_route->route_action = route_action;
	mlxsw_sp_mr_mfc_offload_update(rve->mr_route);
पूर्ण

अटल पूर्णांक mlxsw_sp_mr_vअगर_resolve(काष्ठा mlxsw_sp_mr_table *mr_table,
				   काष्ठा net_device *dev,
				   काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर,
				   अचिन्हित दीर्घ vअगर_flags,
				   स्थिर काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_mr_route_vअगर_entry *irve, *erve;
	पूर्णांक err;

	/* Update the VIF */
	mr_vअगर->dev = dev;
	mr_vअगर->rअगर = rअगर;
	mr_vअगर->vअगर_flags = vअगर_flags;

	/* Update all routes where this VIF is used as an unresolved iRIF */
	list_क्रम_each_entry(irve, &mr_vअगर->route_ivअगर_list, vअगर_node) अणु
		err = mlxsw_sp_mr_route_ivअगर_resolve(mr_table, irve);
		अगर (err)
			जाओ err_irअगर_unresolve;
	पूर्ण

	/* Update all routes where this VIF is used as an unresolved eRIF */
	list_क्रम_each_entry(erve, &mr_vअगर->route_evअगर_list, vअगर_node) अणु
		err = mlxsw_sp_mr_route_evअगर_resolve(mr_table, erve);
		अगर (err)
			जाओ err_erअगर_unresolve;
	पूर्ण
	वापस 0;

err_erअगर_unresolve:
	list_क्रम_each_entry_जारी_reverse(erve, &mr_vअगर->route_evअगर_list,
					     vअगर_node)
		mlxsw_sp_mr_route_evअगर_unresolve(mr_table, erve);
err_irअगर_unresolve:
	list_क्रम_each_entry_जारी_reverse(irve, &mr_vअगर->route_ivअगर_list,
					     vअगर_node)
		mlxsw_sp_mr_route_ivअगर_unresolve(mr_table, irve);
	mr_vअगर->rअगर = शून्य;
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_mr_vअगर_unresolve(काष्ठा mlxsw_sp_mr_table *mr_table,
				      काष्ठा net_device *dev,
				      काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर)
अणु
	काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve;

	/* Update all routes where this VIF is used as an unresolved eRIF */
	list_क्रम_each_entry(rve, &mr_vअगर->route_evअगर_list, vअगर_node)
		mlxsw_sp_mr_route_evअगर_unresolve(mr_table, rve);

	/* Update all routes where this VIF is used as an unresolved iRIF */
	list_क्रम_each_entry(rve, &mr_vअगर->route_ivअगर_list, vअगर_node)
		mlxsw_sp_mr_route_ivअगर_unresolve(mr_table, rve);

	/* Update the VIF */
	mr_vअगर->dev = dev;
	mr_vअगर->rअगर = शून्य;
पूर्ण

पूर्णांक mlxsw_sp_mr_vअगर_add(काष्ठा mlxsw_sp_mr_table *mr_table,
			काष्ठा net_device *dev, vअगरi_t vअगर_index,
			अचिन्हित दीर्घ vअगर_flags, स्थिर काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर = &mr_table->vअगरs[vअगर_index];

	अगर (WARN_ON(vअगर_index >= MAXVIFS))
		वापस -EINVAL;
	अगर (mr_vअगर->dev)
		वापस -EEXIST;
	वापस mlxsw_sp_mr_vअगर_resolve(mr_table, dev, mr_vअगर, vअगर_flags, rअगर);
पूर्ण

व्योम mlxsw_sp_mr_vअगर_del(काष्ठा mlxsw_sp_mr_table *mr_table, vअगरi_t vअगर_index)
अणु
	काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर = &mr_table->vअगरs[vअगर_index];

	अगर (WARN_ON(vअगर_index >= MAXVIFS))
		वापस;
	अगर (WARN_ON(!mr_vअगर->dev))
		वापस;
	mlxsw_sp_mr_vअगर_unresolve(mr_table, शून्य, mr_vअगर);
पूर्ण

अटल काष्ठा mlxsw_sp_mr_vअगर *
mlxsw_sp_mr_dev_vअगर_lookup(काष्ठा mlxsw_sp_mr_table *mr_table,
			   स्थिर काष्ठा net_device *dev)
अणु
	vअगरi_t vअगर_index;

	क्रम (vअगर_index = 0; vअगर_index < MAXVIFS; vअगर_index++)
		अगर (mr_table->vअगरs[vअगर_index].dev == dev)
			वापस &mr_table->vअगरs[vअगर_index];
	वापस शून्य;
पूर्ण

पूर्णांक mlxsw_sp_mr_rअगर_add(काष्ठा mlxsw_sp_mr_table *mr_table,
			स्थिर काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	स्थिर काष्ठा net_device *rअगर_dev = mlxsw_sp_rअगर_dev(rअगर);
	काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर;

	अगर (!rअगर_dev)
		वापस 0;

	mr_vअगर = mlxsw_sp_mr_dev_vअगर_lookup(mr_table, rअगर_dev);
	अगर (!mr_vअगर)
		वापस 0;
	वापस mlxsw_sp_mr_vअगर_resolve(mr_table, mr_vअगर->dev, mr_vअगर,
				       mr_vअगर->vअगर_flags, rअगर);
पूर्ण

व्योम mlxsw_sp_mr_rअगर_del(काष्ठा mlxsw_sp_mr_table *mr_table,
			 स्थिर काष्ठा mlxsw_sp_rअगर *rअगर)
अणु
	स्थिर काष्ठा net_device *rअगर_dev = mlxsw_sp_rअगर_dev(rअगर);
	काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर;

	अगर (!rअगर_dev)
		वापस;

	mr_vअगर = mlxsw_sp_mr_dev_vअगर_lookup(mr_table, rअगर_dev);
	अगर (!mr_vअगर)
		वापस;
	mlxsw_sp_mr_vअगर_unresolve(mr_table, mr_vअगर->dev, mr_vअगर);
पूर्ण

व्योम mlxsw_sp_mr_rअगर_mtu_update(काष्ठा mlxsw_sp_mr_table *mr_table,
				स्थिर काष्ठा mlxsw_sp_rअगर *rअगर, पूर्णांक mtu)
अणु
	स्थिर काष्ठा net_device *rअगर_dev = mlxsw_sp_rअगर_dev(rअगर);
	काष्ठा mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	काष्ठा mlxsw_sp_mr_route_vअगर_entry *rve;
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;
	काष्ठा mlxsw_sp_mr_vअगर *mr_vअगर;

	अगर (!rअगर_dev)
		वापस;

	/* Search क्रम a VIF that use that RIF */
	mr_vअगर = mlxsw_sp_mr_dev_vअगर_lookup(mr_table, rअगर_dev);
	अगर (!mr_vअगर)
		वापस;

	/* Update all the routes that uses that VIF as eVIF */
	list_क्रम_each_entry(rve, &mr_vअगर->route_evअगर_list, vअगर_node) अणु
		अगर (mtu < rve->mr_route->min_mtu) अणु
			rve->mr_route->min_mtu = mtu;
			mr->mr_ops->route_min_mtu_update(mlxsw_sp,
							 rve->mr_route->route_priv,
							 mtu);
		पूर्ण
	पूर्ण
पूर्ण

/* Protocol specअगरic functions */
अटल bool
mlxsw_sp_mr_route4_validate(स्थिर काष्ठा mlxsw_sp_mr_table *mr_table,
			    स्थिर काष्ठा mr_mfc *c)
अणु
	काष्ठा mfc_cache *mfc = (काष्ठा mfc_cache *) c;

	/* If the route is a (*,*) route, पात, as these kind of routes are
	 * used क्रम proxy routes.
	 */
	अगर (mfc->mfc_origin == htonl(INADDR_ANY) &&
	    mfc->mfc_mcastgrp == htonl(INADDR_ANY)) अणु
		dev_warn(mr_table->mlxsw_sp->bus_info->dev,
			 "Offloading proxy routes is not supported.\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम mlxsw_sp_mr_route4_key(काष्ठा mlxsw_sp_mr_table *mr_table,
				   काष्ठा mlxsw_sp_mr_route_key *key,
				   काष्ठा mr_mfc *c)
अणु
	स्थिर काष्ठा mfc_cache *mfc = (काष्ठा mfc_cache *) c;
	bool starg;

	starg = (mfc->mfc_origin == htonl(INADDR_ANY));

	स_रखो(key, 0, माप(*key));
	key->vrid = mr_table->vr_id;
	key->proto = MLXSW_SP_L3_PROTO_IPV4;
	key->group.addr4 = mfc->mfc_mcastgrp;
	key->group_mask.addr4 = htonl(0xffffffff);
	key->source.addr4 = mfc->mfc_origin;
	key->source_mask.addr4 = htonl(starg ? 0 : 0xffffffff);
पूर्ण

अटल bool mlxsw_sp_mr_route4_starg(स्थिर काष्ठा mlxsw_sp_mr_table *mr_table,
				     स्थिर काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	वापस mr_route->key.source_mask.addr4 == htonl(INADDR_ANY);
पूर्ण

अटल bool mlxsw_sp_mr_vअगर4_is_regular(स्थिर काष्ठा mlxsw_sp_mr_vअगर *vअगर)
अणु
	वापस !(vअगर->vअगर_flags & (VIFF_TUNNEL | VIFF_REGISTER));
पूर्ण

अटल bool
mlxsw_sp_mr_route6_validate(स्थिर काष्ठा mlxsw_sp_mr_table *mr_table,
			    स्थिर काष्ठा mr_mfc *c)
अणु
	काष्ठा mfc6_cache *mfc = (काष्ठा mfc6_cache *) c;

	/* If the route is a (*,*) route, पात, as these kind of routes are
	 * used क्रम proxy routes.
	 */
	अगर (ipv6_addr_any(&mfc->mf6c_origin) &&
	    ipv6_addr_any(&mfc->mf6c_mcastgrp)) अणु
		dev_warn(mr_table->mlxsw_sp->bus_info->dev,
			 "Offloading proxy routes is not supported.\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम mlxsw_sp_mr_route6_key(काष्ठा mlxsw_sp_mr_table *mr_table,
				   काष्ठा mlxsw_sp_mr_route_key *key,
				   काष्ठा mr_mfc *c)
अणु
	स्थिर काष्ठा mfc6_cache *mfc = (काष्ठा mfc6_cache *) c;

	स_रखो(key, 0, माप(*key));
	key->vrid = mr_table->vr_id;
	key->proto = MLXSW_SP_L3_PROTO_IPV6;
	key->group.addr6 = mfc->mf6c_mcastgrp;
	स_रखो(&key->group_mask.addr6, 0xff, माप(key->group_mask.addr6));
	key->source.addr6 = mfc->mf6c_origin;
	अगर (!ipv6_addr_any(&mfc->mf6c_origin))
		स_रखो(&key->source_mask.addr6, 0xff,
		       माप(key->source_mask.addr6));
पूर्ण

अटल bool mlxsw_sp_mr_route6_starg(स्थिर काष्ठा mlxsw_sp_mr_table *mr_table,
				     स्थिर काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	वापस ipv6_addr_any(&mr_route->key.source_mask.addr6);
पूर्ण

अटल bool mlxsw_sp_mr_vअगर6_is_regular(स्थिर काष्ठा mlxsw_sp_mr_vअगर *vअगर)
अणु
	वापस !(vअगर->vअगर_flags & MIFF_REGISTER);
पूर्ण

अटल काष्ठा
mlxsw_sp_mr_vअगर_ops mlxsw_sp_mr_vअगर_ops_arr[] = अणु
	अणु
		.is_regular = mlxsw_sp_mr_vअगर4_is_regular,
	पूर्ण,
	अणु
		.is_regular = mlxsw_sp_mr_vअगर6_is_regular,
	पूर्ण,
पूर्ण;

अटल काष्ठा
mlxsw_sp_mr_table_ops mlxsw_sp_mr_table_ops_arr[] = अणु
	अणु
		.is_route_valid = mlxsw_sp_mr_route4_validate,
		.key_create = mlxsw_sp_mr_route4_key,
		.is_route_starg = mlxsw_sp_mr_route4_starg,
	पूर्ण,
	अणु
		.is_route_valid = mlxsw_sp_mr_route6_validate,
		.key_create = mlxsw_sp_mr_route6_key,
		.is_route_starg = mlxsw_sp_mr_route6_starg,
	पूर्ण,

पूर्ण;

काष्ठा mlxsw_sp_mr_table *mlxsw_sp_mr_table_create(काष्ठा mlxsw_sp *mlxsw_sp,
						   u32 vr_id,
						   क्रमागत mlxsw_sp_l3proto proto)
अणु
	काष्ठा mlxsw_sp_mr_route_params catchall_route_params = अणु
		.prio = MLXSW_SP_MR_ROUTE_PRIO_CATCHALL,
		.key = अणु
			.vrid = vr_id,
			.proto = proto,
		पूर्ण,
		.value = अणु
			.route_action = MLXSW_SP_MR_ROUTE_ACTION_TRAP,
		पूर्ण
	पूर्ण;
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;
	काष्ठा mlxsw_sp_mr_table *mr_table;
	पूर्णांक err;
	पूर्णांक i;

	mr_table = kzalloc(माप(*mr_table) + mr->mr_ops->route_priv_size,
			   GFP_KERNEL);
	अगर (!mr_table)
		वापस ERR_PTR(-ENOMEM);

	mr_table->vr_id = vr_id;
	mr_table->mlxsw_sp = mlxsw_sp;
	mr_table->proto = proto;
	mr_table->ops = &mlxsw_sp_mr_table_ops_arr[proto];
	INIT_LIST_HEAD(&mr_table->route_list);
	mutex_init(&mr_table->route_list_lock);

	err = rhashtable_init(&mr_table->route_ht,
			      &mlxsw_sp_mr_route_ht_params);
	अगर (err)
		जाओ err_route_rhashtable_init;

	क्रम (i = 0; i < MAXVIFS; i++) अणु
		INIT_LIST_HEAD(&mr_table->vअगरs[i].route_evअगर_list);
		INIT_LIST_HEAD(&mr_table->vअगरs[i].route_ivअगर_list);
		mr_table->vअगरs[i].ops = &mlxsw_sp_mr_vअगर_ops_arr[proto];
	पूर्ण

	err = mr->mr_ops->route_create(mlxsw_sp, mr->priv,
				       mr_table->catchall_route_priv,
				       &catchall_route_params);
	अगर (err)
		जाओ err_ops_route_create;
	mutex_lock(&mr->table_list_lock);
	list_add_tail(&mr_table->node, &mr->table_list);
	mutex_unlock(&mr->table_list_lock);
	वापस mr_table;

err_ops_route_create:
	rhashtable_destroy(&mr_table->route_ht);
err_route_rhashtable_init:
	mutex_destroy(&mr_table->route_list_lock);
	kमुक्त(mr_table);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlxsw_sp_mr_table_destroy(काष्ठा mlxsw_sp_mr_table *mr_table)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mr_table->mlxsw_sp;
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;

	WARN_ON(!mlxsw_sp_mr_table_empty(mr_table));
	mutex_lock(&mr->table_list_lock);
	list_del(&mr_table->node);
	mutex_unlock(&mr->table_list_lock);
	mr->mr_ops->route_destroy(mlxsw_sp, mr->priv,
				  &mr_table->catchall_route_priv);
	rhashtable_destroy(&mr_table->route_ht);
	mutex_destroy(&mr_table->route_list_lock);
	kमुक्त(mr_table);
पूर्ण

व्योम mlxsw_sp_mr_table_flush(काष्ठा mlxsw_sp_mr_table *mr_table)
अणु
	काष्ठा mlxsw_sp_mr_route *mr_route, *पंचांगp;
	पूर्णांक i;

	mutex_lock(&mr_table->route_list_lock);
	list_क्रम_each_entry_safe(mr_route, पंचांगp, &mr_table->route_list, node)
		__mlxsw_sp_mr_route_del(mr_table, mr_route);
	mutex_unlock(&mr_table->route_list_lock);

	क्रम (i = 0; i < MAXVIFS; i++) अणु
		mr_table->vअगरs[i].dev = शून्य;
		mr_table->vअगरs[i].rअगर = शून्य;
	पूर्ण
पूर्ण

bool mlxsw_sp_mr_table_empty(स्थिर काष्ठा mlxsw_sp_mr_table *mr_table)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAXVIFS; i++)
		अगर (mr_table->vअगरs[i].dev)
			वापस false;
	वापस list_empty(&mr_table->route_list);
पूर्ण

अटल व्योम mlxsw_sp_mr_route_stats_update(काष्ठा mlxsw_sp *mlxsw_sp,
					   काष्ठा mlxsw_sp_mr_route *mr_route)
अणु
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;
	u64 packets, bytes;

	अगर (mr_route->route_action == MLXSW_SP_MR_ROUTE_ACTION_TRAP)
		वापस;

	mr->mr_ops->route_stats(mlxsw_sp, mr_route->route_priv, &packets,
				&bytes);

	अगर (mr_route->mfc->mfc_un.res.pkt != packets)
		mr_route->mfc->mfc_un.res.lastuse = jअगरfies;
	mr_route->mfc->mfc_un.res.pkt = packets;
	mr_route->mfc->mfc_un.res.bytes = bytes;
पूर्ण

अटल व्योम mlxsw_sp_mr_stats_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_mr *mr = container_of(work, काष्ठा mlxsw_sp_mr,
					      stats_update_dw.work);
	काष्ठा mlxsw_sp_mr_table *mr_table;
	काष्ठा mlxsw_sp_mr_route *mr_route;
	अचिन्हित दीर्घ पूर्णांकerval;

	mutex_lock(&mr->table_list_lock);
	list_क्रम_each_entry(mr_table, &mr->table_list, node) अणु
		mutex_lock(&mr_table->route_list_lock);
		list_क्रम_each_entry(mr_route, &mr_table->route_list, node)
			mlxsw_sp_mr_route_stats_update(mr_table->mlxsw_sp,
						       mr_route);
		mutex_unlock(&mr_table->route_list_lock);
	पूर्ण
	mutex_unlock(&mr->table_list_lock);

	पूर्णांकerval = msecs_to_jअगरfies(MLXSW_SP_MR_ROUTES_COUNTER_UPDATE_INTERVAL);
	mlxsw_core_schedule_dw(&mr->stats_update_dw, पूर्णांकerval);
पूर्ण

पूर्णांक mlxsw_sp_mr_init(काष्ठा mlxsw_sp *mlxsw_sp,
		     स्थिर काष्ठा mlxsw_sp_mr_ops *mr_ops)
अणु
	काष्ठा mlxsw_sp_mr *mr;
	अचिन्हित दीर्घ पूर्णांकerval;
	पूर्णांक err;

	mr = kzalloc(माप(*mr) + mr_ops->priv_size, GFP_KERNEL);
	अगर (!mr)
		वापस -ENOMEM;
	mr->mr_ops = mr_ops;
	mlxsw_sp->mr = mr;
	INIT_LIST_HEAD(&mr->table_list);
	mutex_init(&mr->table_list_lock);

	err = mr_ops->init(mlxsw_sp, mr->priv);
	अगर (err)
		जाओ err;

	/* Create the delayed work क्रम counter updates */
	INIT_DELAYED_WORK(&mr->stats_update_dw, mlxsw_sp_mr_stats_update);
	पूर्णांकerval = msecs_to_jअगरfies(MLXSW_SP_MR_ROUTES_COUNTER_UPDATE_INTERVAL);
	mlxsw_core_schedule_dw(&mr->stats_update_dw, पूर्णांकerval);
	वापस 0;
err:
	mutex_destroy(&mr->table_list_lock);
	kमुक्त(mr);
	वापस err;
पूर्ण

व्योम mlxsw_sp_mr_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_mr *mr = mlxsw_sp->mr;

	cancel_delayed_work_sync(&mr->stats_update_dw);
	mr->mr_ops->fini(mlxsw_sp, mr->priv);
	mutex_destroy(&mr->table_list_lock);
	kमुक्त(mr);
पूर्ण
