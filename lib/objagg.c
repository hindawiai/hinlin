<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/idr.h>
#समावेश <linux/list.h>
#समावेश <linux/sort.h>
#समावेश <linux/objagg.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/objagg.h>

काष्ठा objagg_hपूर्णांकs अणु
	काष्ठा rhashtable node_ht;
	काष्ठा rhashtable_params ht_params;
	काष्ठा list_head node_list;
	अचिन्हित पूर्णांक node_count;
	अचिन्हित पूर्णांक root_count;
	अचिन्हित पूर्णांक refcount;
	स्थिर काष्ठा objagg_ops *ops;
पूर्ण;

काष्ठा objagg_hपूर्णांकs_node अणु
	काष्ठा rhash_head ht_node; /* member of objagg_hपूर्णांकs->node_ht */
	काष्ठा list_head list; /* member of objagg_hपूर्णांकs->node_list */
	काष्ठा objagg_hपूर्णांकs_node *parent;
	अचिन्हित पूर्णांक root_id;
	काष्ठा objagg_obj_stats_info stats_info;
	अचिन्हित दीर्घ obj[];
पूर्ण;

अटल काष्ठा objagg_hपूर्णांकs_node *
objagg_hपूर्णांकs_lookup(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs, व्योम *obj)
अणु
	अगर (!objagg_hपूर्णांकs)
		वापस शून्य;
	वापस rhashtable_lookup_fast(&objagg_hपूर्णांकs->node_ht, obj,
				      objagg_hपूर्णांकs->ht_params);
पूर्ण

काष्ठा objagg अणु
	स्थिर काष्ठा objagg_ops *ops;
	व्योम *priv;
	काष्ठा rhashtable obj_ht;
	काष्ठा rhashtable_params ht_params;
	काष्ठा list_head obj_list;
	अचिन्हित पूर्णांक obj_count;
	काष्ठा ida root_ida;
	काष्ठा objagg_hपूर्णांकs *hपूर्णांकs;
पूर्ण;

काष्ठा objagg_obj अणु
	काष्ठा rhash_head ht_node; /* member of objagg->obj_ht */
	काष्ठा list_head list; /* member of objagg->obj_list */
	काष्ठा objagg_obj *parent; /* अगर the object is nested, this
				    * holds poपूर्णांकer to parent, otherwise शून्य
				    */
	जोड़ अणु
		व्योम *delta_priv; /* user delta निजी */
		व्योम *root_priv; /* user root निजी */
	पूर्ण;
	अचिन्हित पूर्णांक root_id;
	अचिन्हित पूर्णांक refcount; /* counts number of users of this object
				* including nested objects
				*/
	काष्ठा objagg_obj_stats stats;
	अचिन्हित दीर्घ obj[];
पूर्ण;

अटल अचिन्हित पूर्णांक objagg_obj_ref_inc(काष्ठा objagg_obj *objagg_obj)
अणु
	वापस ++objagg_obj->refcount;
पूर्ण

अटल अचिन्हित पूर्णांक objagg_obj_ref_dec(काष्ठा objagg_obj *objagg_obj)
अणु
	वापस --objagg_obj->refcount;
पूर्ण

अटल व्योम objagg_obj_stats_inc(काष्ठा objagg_obj *objagg_obj)
अणु
	objagg_obj->stats.user_count++;
	objagg_obj->stats.delta_user_count++;
	अगर (objagg_obj->parent)
		objagg_obj->parent->stats.delta_user_count++;
पूर्ण

अटल व्योम objagg_obj_stats_dec(काष्ठा objagg_obj *objagg_obj)
अणु
	objagg_obj->stats.user_count--;
	objagg_obj->stats.delta_user_count--;
	अगर (objagg_obj->parent)
		objagg_obj->parent->stats.delta_user_count--;
पूर्ण

अटल bool objagg_obj_is_root(स्थिर काष्ठा objagg_obj *objagg_obj)
अणु
	/* Nesting is not supported, so we can use ->parent
	 * to figure out अगर the object is root.
	 */
	वापस !objagg_obj->parent;
पूर्ण

/**
 * objagg_obj_root_priv - obtains root निजी क्रम an object
 * @objagg_obj:	objagg object instance
 *
 * Note: all locking must be provided by the caller.
 *
 * Either the object is root itself when the निजी is वापसed
 * directly, or the parent is root and its निजी is वापसed
 * instead.
 *
 * Returns a user निजी root poपूर्णांकer.
 */
स्थिर व्योम *objagg_obj_root_priv(स्थिर काष्ठा objagg_obj *objagg_obj)
अणु
	अगर (objagg_obj_is_root(objagg_obj))
		वापस objagg_obj->root_priv;
	WARN_ON(!objagg_obj_is_root(objagg_obj->parent));
	वापस objagg_obj->parent->root_priv;
पूर्ण
EXPORT_SYMBOL(objagg_obj_root_priv);

/**
 * objagg_obj_delta_priv - obtains delta निजी क्रम an object
 * @objagg_obj:	objagg object instance
 *
 * Note: all locking must be provided by the caller.
 *
 * Returns user निजी delta poपूर्णांकer or शून्य in हाल the passed
 * object is root.
 */
स्थिर व्योम *objagg_obj_delta_priv(स्थिर काष्ठा objagg_obj *objagg_obj)
अणु
	अगर (objagg_obj_is_root(objagg_obj))
		वापस शून्य;
	वापस objagg_obj->delta_priv;
पूर्ण
EXPORT_SYMBOL(objagg_obj_delta_priv);

/**
 * objagg_obj_raw - obtains object user निजी poपूर्णांकer
 * @objagg_obj:	objagg object instance
 *
 * Note: all locking must be provided by the caller.
 *
 * Returns user निजी poपूर्णांकer as was passed to objagg_obj_get() by "obj" arg.
 */
स्थिर व्योम *objagg_obj_raw(स्थिर काष्ठा objagg_obj *objagg_obj)
अणु
	वापस objagg_obj->obj;
पूर्ण
EXPORT_SYMBOL(objagg_obj_raw);

अटल काष्ठा objagg_obj *objagg_obj_lookup(काष्ठा objagg *objagg, व्योम *obj)
अणु
	वापस rhashtable_lookup_fast(&objagg->obj_ht, obj, objagg->ht_params);
पूर्ण

अटल पूर्णांक objagg_obj_parent_assign(काष्ठा objagg *objagg,
				    काष्ठा objagg_obj *objagg_obj,
				    काष्ठा objagg_obj *parent,
				    bool take_parent_ref)
अणु
	व्योम *delta_priv;

	delta_priv = objagg->ops->delta_create(objagg->priv, parent->obj,
					       objagg_obj->obj);
	अगर (IS_ERR(delta_priv))
		वापस PTR_ERR(delta_priv);

	/* User वापसed a delta निजी, that means that
	 * our object can be aggregated पूर्णांकo the parent.
	 */
	objagg_obj->parent = parent;
	objagg_obj->delta_priv = delta_priv;
	अगर (take_parent_ref)
		objagg_obj_ref_inc(objagg_obj->parent);
	trace_objagg_obj_parent_assign(objagg, objagg_obj,
				       parent,
				       parent->refcount);
	वापस 0;
पूर्ण

अटल पूर्णांक objagg_obj_parent_lookup_assign(काष्ठा objagg *objagg,
					   काष्ठा objagg_obj *objagg_obj)
अणु
	काष्ठा objagg_obj *objagg_obj_cur;
	पूर्णांक err;

	list_क्रम_each_entry(objagg_obj_cur, &objagg->obj_list, list) अणु
		/* Nesting is not supported. In हाल the object
		 * is not root, it cannot be asचिन्हित as parent.
		 */
		अगर (!objagg_obj_is_root(objagg_obj_cur))
			जारी;
		err = objagg_obj_parent_assign(objagg, objagg_obj,
					       objagg_obj_cur, true);
		अगर (!err)
			वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल व्योम __objagg_obj_put(काष्ठा objagg *objagg,
			     काष्ठा objagg_obj *objagg_obj);

अटल व्योम objagg_obj_parent_unassign(काष्ठा objagg *objagg,
				       काष्ठा objagg_obj *objagg_obj)
अणु
	trace_objagg_obj_parent_unassign(objagg, objagg_obj,
					 objagg_obj->parent,
					 objagg_obj->parent->refcount);
	objagg->ops->delta_destroy(objagg->priv, objagg_obj->delta_priv);
	__objagg_obj_put(objagg, objagg_obj->parent);
पूर्ण

अटल पूर्णांक objagg_obj_root_id_alloc(काष्ठा objagg *objagg,
				    काष्ठा objagg_obj *objagg_obj,
				    काष्ठा objagg_hपूर्णांकs_node *hnode)
अणु
	अचिन्हित पूर्णांक min, max;
	पूर्णांक root_id;

	/* In हाल there are no hपूर्णांकs available, the root id is invalid. */
	अगर (!objagg->hपूर्णांकs) अणु
		objagg_obj->root_id = OBJAGG_OBJ_ROOT_ID_INVALID;
		वापस 0;
	पूर्ण

	अगर (hnode) अणु
		min = hnode->root_id;
		max = hnode->root_id;
	पूर्ण अन्यथा अणु
		/* For objects with no hपूर्णांक, start after the last
		 * hपूर्णांकed root_id.
		 */
		min = objagg->hपूर्णांकs->root_count;
		max = ~0;
	पूर्ण

	root_id = ida_alloc_range(&objagg->root_ida, min, max, GFP_KERNEL);

	अगर (root_id < 0)
		वापस root_id;
	objagg_obj->root_id = root_id;
	वापस 0;
पूर्ण

अटल व्योम objagg_obj_root_id_मुक्त(काष्ठा objagg *objagg,
				    काष्ठा objagg_obj *objagg_obj)
अणु
	अगर (!objagg->hपूर्णांकs)
		वापस;
	ida_मुक्त(&objagg->root_ida, objagg_obj->root_id);
पूर्ण

अटल पूर्णांक objagg_obj_root_create(काष्ठा objagg *objagg,
				  काष्ठा objagg_obj *objagg_obj,
				  काष्ठा objagg_hपूर्णांकs_node *hnode)
अणु
	पूर्णांक err;

	err = objagg_obj_root_id_alloc(objagg, objagg_obj, hnode);
	अगर (err)
		वापस err;
	objagg_obj->root_priv = objagg->ops->root_create(objagg->priv,
							 objagg_obj->obj,
							 objagg_obj->root_id);
	अगर (IS_ERR(objagg_obj->root_priv)) अणु
		err = PTR_ERR(objagg_obj->root_priv);
		जाओ err_root_create;
	पूर्ण
	trace_objagg_obj_root_create(objagg, objagg_obj);
	वापस 0;

err_root_create:
	objagg_obj_root_id_मुक्त(objagg, objagg_obj);
	वापस err;
पूर्ण

अटल व्योम objagg_obj_root_destroy(काष्ठा objagg *objagg,
				    काष्ठा objagg_obj *objagg_obj)
अणु
	trace_objagg_obj_root_destroy(objagg, objagg_obj);
	objagg->ops->root_destroy(objagg->priv, objagg_obj->root_priv);
	objagg_obj_root_id_मुक्त(objagg, objagg_obj);
पूर्ण

अटल काष्ठा objagg_obj *__objagg_obj_get(काष्ठा objagg *objagg, व्योम *obj);

अटल पूर्णांक objagg_obj_init_with_hपूर्णांकs(काष्ठा objagg *objagg,
				      काष्ठा objagg_obj *objagg_obj,
				      bool *hपूर्णांक_found)
अणु
	काष्ठा objagg_hपूर्णांकs_node *hnode;
	काष्ठा objagg_obj *parent;
	पूर्णांक err;

	hnode = objagg_hपूर्णांकs_lookup(objagg->hपूर्णांकs, objagg_obj->obj);
	अगर (!hnode) अणु
		*hपूर्णांक_found = false;
		वापस 0;
	पूर्ण
	*hपूर्णांक_found = true;

	अगर (!hnode->parent)
		वापस objagg_obj_root_create(objagg, objagg_obj, hnode);

	parent = __objagg_obj_get(objagg, hnode->parent->obj);
	अगर (IS_ERR(parent))
		वापस PTR_ERR(parent);

	err = objagg_obj_parent_assign(objagg, objagg_obj, parent, false);
	अगर (err) अणु
		*hपूर्णांक_found = false;
		err = 0;
		जाओ err_parent_assign;
	पूर्ण

	वापस 0;

err_parent_assign:
	objagg_obj_put(objagg, parent);
	वापस err;
पूर्ण

अटल पूर्णांक objagg_obj_init(काष्ठा objagg *objagg,
			   काष्ठा objagg_obj *objagg_obj)
अणु
	bool hपूर्णांक_found;
	पूर्णांक err;

	/* First, try to use hपूर्णांकs अगर they are available and
	 * अगर they provide result.
	 */
	err = objagg_obj_init_with_hपूर्णांकs(objagg, objagg_obj, &hपूर्णांक_found);
	अगर (err)
		वापस err;

	अगर (hपूर्णांक_found)
		वापस 0;

	/* Try to find अगर the object can be aggregated under an existing one. */
	err = objagg_obj_parent_lookup_assign(objagg, objagg_obj);
	अगर (!err)
		वापस 0;
	/* If aggregation is not possible, make the object a root. */
	वापस objagg_obj_root_create(objagg, objagg_obj, शून्य);
पूर्ण

अटल व्योम objagg_obj_fini(काष्ठा objagg *objagg,
			    काष्ठा objagg_obj *objagg_obj)
अणु
	अगर (!objagg_obj_is_root(objagg_obj))
		objagg_obj_parent_unassign(objagg, objagg_obj);
	अन्यथा
		objagg_obj_root_destroy(objagg, objagg_obj);
पूर्ण

अटल काष्ठा objagg_obj *objagg_obj_create(काष्ठा objagg *objagg, व्योम *obj)
अणु
	काष्ठा objagg_obj *objagg_obj;
	पूर्णांक err;

	objagg_obj = kzalloc(माप(*objagg_obj) + objagg->ops->obj_size,
			     GFP_KERNEL);
	अगर (!objagg_obj)
		वापस ERR_PTR(-ENOMEM);
	objagg_obj_ref_inc(objagg_obj);
	स_नकल(objagg_obj->obj, obj, objagg->ops->obj_size);

	err = objagg_obj_init(objagg, objagg_obj);
	अगर (err)
		जाओ err_obj_init;

	err = rhashtable_insert_fast(&objagg->obj_ht, &objagg_obj->ht_node,
				     objagg->ht_params);
	अगर (err)
		जाओ err_ht_insert;
	list_add(&objagg_obj->list, &objagg->obj_list);
	objagg->obj_count++;
	trace_objagg_obj_create(objagg, objagg_obj);

	वापस objagg_obj;

err_ht_insert:
	objagg_obj_fini(objagg, objagg_obj);
err_obj_init:
	kमुक्त(objagg_obj);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा objagg_obj *__objagg_obj_get(काष्ठा objagg *objagg, व्योम *obj)
अणु
	काष्ठा objagg_obj *objagg_obj;

	/* First, try to find the object exactly as user passed it,
	 * perhaps it is alपढ़ोy in use.
	 */
	objagg_obj = objagg_obj_lookup(objagg, obj);
	अगर (objagg_obj) अणु
		objagg_obj_ref_inc(objagg_obj);
		वापस objagg_obj;
	पूर्ण

	वापस objagg_obj_create(objagg, obj);
पूर्ण

/**
 * objagg_obj_get - माला_लो an object within objagg instance
 * @objagg:	objagg instance
 * @obj:	user-specअगरic निजी object poपूर्णांकer
 *
 * Note: all locking must be provided by the caller.
 *
 * Size of the "obj" memory is specअगरied in "objagg->ops".
 *
 * There are 3 मुख्य options this function wraps:
 * 1) The object according to "obj" alपढ़ोy exist. In that हाल
 *    the reference counter is incrementes and the object is वापसed.
 * 2) The object करोes not exist, but it can be aggregated within
 *    another object. In that हाल, user ops->delta_create() is called
 *    to obtain delta data and a new object is created with वापसed
 *    user-delta निजी poपूर्णांकer.
 * 3) The object करोes not exist and cannot be aggregated पूर्णांकo
 *    any of the existing objects. In that हाल, user ops->root_create()
 *    is called to create the root and a new object is created with
 *    वापसed user-root निजी poपूर्णांकer.
 *
 * Returns a poपूर्णांकer to objagg object instance in हाल of success,
 * otherwise it वापसs poपूर्णांकer error using ERR_PTR macro.
 */
काष्ठा objagg_obj *objagg_obj_get(काष्ठा objagg *objagg, व्योम *obj)
अणु
	काष्ठा objagg_obj *objagg_obj;

	objagg_obj = __objagg_obj_get(objagg, obj);
	अगर (IS_ERR(objagg_obj))
		वापस objagg_obj;
	objagg_obj_stats_inc(objagg_obj);
	trace_objagg_obj_get(objagg, objagg_obj, objagg_obj->refcount);
	वापस objagg_obj;
पूर्ण
EXPORT_SYMBOL(objagg_obj_get);

अटल व्योम objagg_obj_destroy(काष्ठा objagg *objagg,
			       काष्ठा objagg_obj *objagg_obj)
अणु
	trace_objagg_obj_destroy(objagg, objagg_obj);
	--objagg->obj_count;
	list_del(&objagg_obj->list);
	rhashtable_हटाओ_fast(&objagg->obj_ht, &objagg_obj->ht_node,
			       objagg->ht_params);
	objagg_obj_fini(objagg, objagg_obj);
	kमुक्त(objagg_obj);
पूर्ण

अटल व्योम __objagg_obj_put(काष्ठा objagg *objagg,
			     काष्ठा objagg_obj *objagg_obj)
अणु
	अगर (!objagg_obj_ref_dec(objagg_obj))
		objagg_obj_destroy(objagg, objagg_obj);
पूर्ण

/**
 * objagg_obj_put - माला_दो an object within objagg instance
 * @objagg:	objagg instance
 * @objagg_obj:	objagg object instance
 *
 * Note: all locking must be provided by the caller.
 *
 * Symmetric to objagg_obj_get().
 */
व्योम objagg_obj_put(काष्ठा objagg *objagg, काष्ठा objagg_obj *objagg_obj)
अणु
	trace_objagg_obj_put(objagg, objagg_obj, objagg_obj->refcount);
	objagg_obj_stats_dec(objagg_obj);
	__objagg_obj_put(objagg, objagg_obj);
पूर्ण
EXPORT_SYMBOL(objagg_obj_put);

/**
 * objagg_create - creates a new objagg instance
 * @ops:		user-specअगरic callbacks
 * @objagg_hपूर्णांकs:	hपूर्णांकs, can be शून्य
 * @priv:		poपूर्णांकer to a निजी data passed to the ops
 *
 * Note: all locking must be provided by the caller.
 *
 * The purpose of the library is to provide an infraकाष्ठाure to
 * aggregate user-specअगरied objects. Library करोes not care about the type
 * of the object. User fills-up ops which take care of the specअगरic
 * user object manipulation.
 *
 * As a very stupid example, consider पूर्णांकeger numbers. For example
 * number 8 as a root object. That can aggregate number 9 with delta 1,
 * number 10 with delta 2, etc. This example is implemented as
 * a part of a testing module in test_objagg.c file.
 *
 * Each objagg instance contains multiple trees. Each tree node is
 * represented by "an object". In the current implementation there can be
 * only roots and leafs nodes. Leaf nodes are called deltas.
 * But in general, this can be easily extended क्रम पूर्णांकermediate nodes.
 * In that extension, a delta would be associated with all non-root
 * nodes.
 *
 * Returns a poपूर्णांकer to newly created objagg instance in हाल of success,
 * otherwise it वापसs poपूर्णांकer error using ERR_PTR macro.
 */
काष्ठा objagg *objagg_create(स्थिर काष्ठा objagg_ops *ops,
			     काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs, व्योम *priv)
अणु
	काष्ठा objagg *objagg;
	पूर्णांक err;

	अगर (WARN_ON(!ops || !ops->root_create || !ops->root_destroy ||
		    !ops->delta_check || !ops->delta_create ||
		    !ops->delta_destroy))
		वापस ERR_PTR(-EINVAL);

	objagg = kzalloc(माप(*objagg), GFP_KERNEL);
	अगर (!objagg)
		वापस ERR_PTR(-ENOMEM);
	objagg->ops = ops;
	अगर (objagg_hपूर्णांकs) अणु
		objagg->hपूर्णांकs = objagg_hपूर्णांकs;
		objagg_hपूर्णांकs->refcount++;
	पूर्ण
	objagg->priv = priv;
	INIT_LIST_HEAD(&objagg->obj_list);

	objagg->ht_params.key_len = ops->obj_size;
	objagg->ht_params.key_offset = दुरत्व(काष्ठा objagg_obj, obj);
	objagg->ht_params.head_offset = दुरत्व(काष्ठा objagg_obj, ht_node);

	err = rhashtable_init(&objagg->obj_ht, &objagg->ht_params);
	अगर (err)
		जाओ err_rhashtable_init;

	ida_init(&objagg->root_ida);

	trace_objagg_create(objagg);
	वापस objagg;

err_rhashtable_init:
	kमुक्त(objagg);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(objagg_create);

/**
 * objagg_destroy - destroys a new objagg instance
 * @objagg:	objagg instance
 *
 * Note: all locking must be provided by the caller.
 */
व्योम objagg_destroy(काष्ठा objagg *objagg)
अणु
	trace_objagg_destroy(objagg);
	ida_destroy(&objagg->root_ida);
	WARN_ON(!list_empty(&objagg->obj_list));
	rhashtable_destroy(&objagg->obj_ht);
	अगर (objagg->hपूर्णांकs)
		objagg_hपूर्णांकs_put(objagg->hपूर्णांकs);
	kमुक्त(objagg);
पूर्ण
EXPORT_SYMBOL(objagg_destroy);

अटल पूर्णांक objagg_stats_info_sort_cmp_func(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा objagg_obj_stats_info *stats_info1 = a;
	स्थिर काष्ठा objagg_obj_stats_info *stats_info2 = b;

	अगर (stats_info1->is_root != stats_info2->is_root)
		वापस stats_info2->is_root - stats_info1->is_root;
	अगर (stats_info1->stats.delta_user_count !=
	    stats_info2->stats.delta_user_count)
		वापस stats_info2->stats.delta_user_count -
		       stats_info1->stats.delta_user_count;
	वापस stats_info2->stats.user_count - stats_info1->stats.user_count;
पूर्ण

/**
 * objagg_stats_get - obtains stats of the objagg instance
 * @objagg:	objagg instance
 *
 * Note: all locking must be provided by the caller.
 *
 * The वापसed काष्ठाure contains statistics of all object
 * currently in use, ordered by following rules:
 * 1) Root objects are always on lower indexes than the rest.
 * 2) Objects with higher delta user count are always on lower
 *    indexes.
 * 3) In हाल more objects have the same delta user count,
 *    the objects are ordered by user count.
 *
 * Returns a poपूर्णांकer to stats instance in हाल of success,
 * otherwise it वापसs poपूर्णांकer error using ERR_PTR macro.
 */
स्थिर काष्ठा objagg_stats *objagg_stats_get(काष्ठा objagg *objagg)
अणु
	काष्ठा objagg_stats *objagg_stats;
	काष्ठा objagg_obj *objagg_obj;
	पूर्णांक i;

	objagg_stats = kzalloc(काष्ठा_size(objagg_stats, stats_info,
					   objagg->obj_count), GFP_KERNEL);
	अगर (!objagg_stats)
		वापस ERR_PTR(-ENOMEM);

	i = 0;
	list_क्रम_each_entry(objagg_obj, &objagg->obj_list, list) अणु
		स_नकल(&objagg_stats->stats_info[i].stats, &objagg_obj->stats,
		       माप(objagg_stats->stats_info[0].stats));
		objagg_stats->stats_info[i].objagg_obj = objagg_obj;
		objagg_stats->stats_info[i].is_root =
					objagg_obj_is_root(objagg_obj);
		अगर (objagg_stats->stats_info[i].is_root)
			objagg_stats->root_count++;
		i++;
	पूर्ण
	objagg_stats->stats_info_count = i;

	sort(objagg_stats->stats_info, objagg_stats->stats_info_count,
	     माप(काष्ठा objagg_obj_stats_info),
	     objagg_stats_info_sort_cmp_func, शून्य);

	वापस objagg_stats;
पूर्ण
EXPORT_SYMBOL(objagg_stats_get);

/**
 * objagg_stats_put - माला_दो stats of the objagg instance
 * @objagg_stats:	objagg instance stats
 *
 * Note: all locking must be provided by the caller.
 */
व्योम objagg_stats_put(स्थिर काष्ठा objagg_stats *objagg_stats)
अणु
	kमुक्त(objagg_stats);
पूर्ण
EXPORT_SYMBOL(objagg_stats_put);

अटल काष्ठा objagg_hपूर्णांकs_node *
objagg_hपूर्णांकs_node_create(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs,
			 काष्ठा objagg_obj *objagg_obj, माप_प्रकार obj_size,
			 काष्ठा objagg_hपूर्णांकs_node *parent_hnode)
अणु
	अचिन्हित पूर्णांक user_count = objagg_obj->stats.user_count;
	काष्ठा objagg_hपूर्णांकs_node *hnode;
	पूर्णांक err;

	hnode = kzalloc(माप(*hnode) + obj_size, GFP_KERNEL);
	अगर (!hnode)
		वापस ERR_PTR(-ENOMEM);
	स_नकल(hnode->obj, &objagg_obj->obj, obj_size);
	hnode->stats_info.stats.user_count = user_count;
	hnode->stats_info.stats.delta_user_count = user_count;
	अगर (parent_hnode) अणु
		parent_hnode->stats_info.stats.delta_user_count += user_count;
	पूर्ण अन्यथा अणु
		hnode->root_id = objagg_hपूर्णांकs->root_count++;
		hnode->stats_info.is_root = true;
	पूर्ण
	hnode->stats_info.objagg_obj = objagg_obj;

	err = rhashtable_insert_fast(&objagg_hपूर्णांकs->node_ht, &hnode->ht_node,
				     objagg_hपूर्णांकs->ht_params);
	अगर (err)
		जाओ err_ht_insert;

	list_add(&hnode->list, &objagg_hपूर्णांकs->node_list);
	hnode->parent = parent_hnode;
	objagg_hपूर्णांकs->node_count++;

	वापस hnode;

err_ht_insert:
	kमुक्त(hnode);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम objagg_hपूर्णांकs_flush(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs)
अणु
	काष्ठा objagg_hपूर्णांकs_node *hnode, *पंचांगp;

	list_क्रम_each_entry_safe(hnode, पंचांगp, &objagg_hपूर्णांकs->node_list, list) अणु
		list_del(&hnode->list);
		rhashtable_हटाओ_fast(&objagg_hपूर्णांकs->node_ht, &hnode->ht_node,
				       objagg_hपूर्णांकs->ht_params);
		kमुक्त(hnode);
	पूर्ण
पूर्ण

काष्ठा objagg_पंचांगp_node अणु
	काष्ठा objagg_obj *objagg_obj;
	bool crossed_out;
पूर्ण;

काष्ठा objagg_पंचांगp_graph अणु
	काष्ठा objagg_पंचांगp_node *nodes;
	अचिन्हित दीर्घ nodes_count;
	अचिन्हित दीर्घ *edges;
पूर्ण;

अटल पूर्णांक objagg_पंचांगp_graph_edge_index(काष्ठा objagg_पंचांगp_graph *graph,
				       पूर्णांक parent_index, पूर्णांक index)
अणु
	वापस index * graph->nodes_count + parent_index;
पूर्ण

अटल व्योम objagg_पंचांगp_graph_edge_set(काष्ठा objagg_पंचांगp_graph *graph,
				      पूर्णांक parent_index, पूर्णांक index)
अणु
	पूर्णांक edge_index = objagg_पंचांगp_graph_edge_index(graph, index,
						     parent_index);

	__set_bit(edge_index, graph->edges);
पूर्ण

अटल bool objagg_पंचांगp_graph_is_edge(काष्ठा objagg_पंचांगp_graph *graph,
				     पूर्णांक parent_index, पूर्णांक index)
अणु
	पूर्णांक edge_index = objagg_पंचांगp_graph_edge_index(graph, index,
						     parent_index);

	वापस test_bit(edge_index, graph->edges);
पूर्ण

अटल अचिन्हित पूर्णांक objagg_पंचांगp_graph_node_weight(काष्ठा objagg_पंचांगp_graph *graph,
						 अचिन्हित पूर्णांक index)
अणु
	काष्ठा objagg_पंचांगp_node *node = &graph->nodes[index];
	अचिन्हित पूर्णांक weight = node->objagg_obj->stats.user_count;
	पूर्णांक j;

	/* Node weight is sum of node users and all other nodes users
	 * that this node can represent with delta.
	 */

	क्रम (j = 0; j < graph->nodes_count; j++) अणु
		अगर (!objagg_पंचांगp_graph_is_edge(graph, index, j))
			जारी;
		node = &graph->nodes[j];
		अगर (node->crossed_out)
			जारी;
		weight += node->objagg_obj->stats.user_count;
	पूर्ण
	वापस weight;
पूर्ण

अटल पूर्णांक objagg_पंचांगp_graph_node_max_weight(काष्ठा objagg_पंचांगp_graph *graph)
अणु
	काष्ठा objagg_पंचांगp_node *node;
	अचिन्हित पूर्णांक max_weight = 0;
	अचिन्हित पूर्णांक weight;
	पूर्णांक max_index = -1;
	पूर्णांक i;

	क्रम (i = 0; i < graph->nodes_count; i++) अणु
		node = &graph->nodes[i];
		अगर (node->crossed_out)
			जारी;
		weight = objagg_पंचांगp_graph_node_weight(graph, i);
		अगर (weight >= max_weight) अणु
			max_weight = weight;
			max_index = i;
		पूर्ण
	पूर्ण
	वापस max_index;
पूर्ण

अटल काष्ठा objagg_पंचांगp_graph *objagg_पंचांगp_graph_create(काष्ठा objagg *objagg)
अणु
	अचिन्हित पूर्णांक nodes_count = objagg->obj_count;
	काष्ठा objagg_पंचांगp_graph *graph;
	काष्ठा objagg_पंचांगp_node *node;
	काष्ठा objagg_पंचांगp_node *pnode;
	काष्ठा objagg_obj *objagg_obj;
	माप_प्रकार alloc_size;
	पूर्णांक i, j;

	graph = kzalloc(माप(*graph), GFP_KERNEL);
	अगर (!graph)
		वापस शून्य;

	graph->nodes = kसुस्मृति(nodes_count, माप(*graph->nodes), GFP_KERNEL);
	अगर (!graph->nodes)
		जाओ err_nodes_alloc;
	graph->nodes_count = nodes_count;

	alloc_size = BITS_TO_LONGS(nodes_count * nodes_count) *
		     माप(अचिन्हित दीर्घ);
	graph->edges = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!graph->edges)
		जाओ err_edges_alloc;

	i = 0;
	list_क्रम_each_entry(objagg_obj, &objagg->obj_list, list) अणु
		node = &graph->nodes[i++];
		node->objagg_obj = objagg_obj;
	पूर्ण

	/* Assemble a temporary graph. Insert edge X->Y in हाल Y can be
	 * in delta of X.
	 */
	क्रम (i = 0; i < nodes_count; i++) अणु
		क्रम (j = 0; j < nodes_count; j++) अणु
			अगर (i == j)
				जारी;
			pnode = &graph->nodes[i];
			node = &graph->nodes[j];
			अगर (objagg->ops->delta_check(objagg->priv,
						     pnode->objagg_obj->obj,
						     node->objagg_obj->obj)) अणु
				objagg_पंचांगp_graph_edge_set(graph, i, j);

			पूर्ण
		पूर्ण
	पूर्ण
	वापस graph;

err_edges_alloc:
	kमुक्त(graph->nodes);
err_nodes_alloc:
	kमुक्त(graph);
	वापस शून्य;
पूर्ण

अटल व्योम objagg_पंचांगp_graph_destroy(काष्ठा objagg_पंचांगp_graph *graph)
अणु
	kमुक्त(graph->edges);
	kमुक्त(graph->nodes);
	kमुक्त(graph);
पूर्ण

अटल पूर्णांक
objagg_opt_simple_greedy_fillup_hपूर्णांकs(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs,
				      काष्ठा objagg *objagg)
अणु
	काष्ठा objagg_hपूर्णांकs_node *hnode, *parent_hnode;
	काष्ठा objagg_पंचांगp_graph *graph;
	काष्ठा objagg_पंचांगp_node *node;
	पूर्णांक index;
	पूर्णांक j;
	पूर्णांक err;

	graph = objagg_पंचांगp_graph_create(objagg);
	अगर (!graph)
		वापस -ENOMEM;

	/* Find the nodes from the ones that can accommodate most users
	 * and cross them out of the graph. Save them to the hपूर्णांक list.
	 */
	जबतक ((index = objagg_पंचांगp_graph_node_max_weight(graph)) != -1) अणु
		node = &graph->nodes[index];
		node->crossed_out = true;
		hnode = objagg_hपूर्णांकs_node_create(objagg_hपूर्णांकs,
						 node->objagg_obj,
						 objagg->ops->obj_size,
						 शून्य);
		अगर (IS_ERR(hnode)) अणु
			err = PTR_ERR(hnode);
			जाओ out;
		पूर्ण
		parent_hnode = hnode;
		क्रम (j = 0; j < graph->nodes_count; j++) अणु
			अगर (!objagg_पंचांगp_graph_is_edge(graph, index, j))
				जारी;
			node = &graph->nodes[j];
			अगर (node->crossed_out)
				जारी;
			node->crossed_out = true;
			hnode = objagg_hपूर्णांकs_node_create(objagg_hपूर्णांकs,
							 node->objagg_obj,
							 objagg->ops->obj_size,
							 parent_hnode);
			अगर (IS_ERR(hnode)) अणु
				err = PTR_ERR(hnode);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	err = 0;
out:
	objagg_पंचांगp_graph_destroy(graph);
	वापस err;
पूर्ण

काष्ठा objagg_opt_algo अणु
	पूर्णांक (*fillup_hपूर्णांकs)(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs,
			    काष्ठा objagg *objagg);
पूर्ण;

अटल स्थिर काष्ठा objagg_opt_algo objagg_opt_simple_greedy = अणु
	.fillup_hपूर्णांकs = objagg_opt_simple_greedy_fillup_hपूर्णांकs,
पूर्ण;


अटल स्थिर काष्ठा objagg_opt_algo *objagg_opt_algos[] = अणु
	[OBJAGG_OPT_ALGO_SIMPLE_GREEDY] = &objagg_opt_simple_greedy,
पूर्ण;

अटल पूर्णांक objagg_hपूर्णांकs_obj_cmp(काष्ठा rhashtable_compare_arg *arg,
				स्थिर व्योम *obj)
अणु
	काष्ठा rhashtable *ht = arg->ht;
	काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs =
			container_of(ht, काष्ठा objagg_hपूर्णांकs, node_ht);
	स्थिर काष्ठा objagg_ops *ops = objagg_hपूर्णांकs->ops;
	स्थिर अक्षर *ptr = obj;

	ptr += ht->p.key_offset;
	वापस ops->hपूर्णांकs_obj_cmp ? ops->hपूर्णांकs_obj_cmp(ptr, arg->key) :
				    स_भेद(ptr, arg->key, ht->p.key_len);
पूर्ण

/**
 * objagg_hपूर्णांकs_get - obtains hपूर्णांकs instance
 * @objagg:		objagg instance
 * @opt_algo_type:	type of hपूर्णांकs finding algorithm
 *
 * Note: all locking must be provided by the caller.
 *
 * According to the algo type, the existing objects of objagg instance
 * are going to be went-through to assemble an optimal tree. We call this
 * tree hपूर्णांकs. These hपूर्णांकs can be later on used क्रम creation of
 * a new objagg instance. There, the future object creations are going
 * to be consulted with these hपूर्णांकs in order to find out, where exactly
 * the new object should be put as a root or delta.
 *
 * Returns a poपूर्णांकer to hपूर्णांकs instance in हाल of success,
 * otherwise it वापसs poपूर्णांकer error using ERR_PTR macro.
 */
काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs_get(काष्ठा objagg *objagg,
				      क्रमागत objagg_opt_algo_type opt_algo_type)
अणु
	स्थिर काष्ठा objagg_opt_algo *algo = objagg_opt_algos[opt_algo_type];
	काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs;
	पूर्णांक err;

	objagg_hपूर्णांकs = kzalloc(माप(*objagg_hपूर्णांकs), GFP_KERNEL);
	अगर (!objagg_hपूर्णांकs)
		वापस ERR_PTR(-ENOMEM);

	objagg_hपूर्णांकs->ops = objagg->ops;
	objagg_hपूर्णांकs->refcount = 1;

	INIT_LIST_HEAD(&objagg_hपूर्णांकs->node_list);

	objagg_hपूर्णांकs->ht_params.key_len = objagg->ops->obj_size;
	objagg_hपूर्णांकs->ht_params.key_offset =
				दुरत्व(काष्ठा objagg_hपूर्णांकs_node, obj);
	objagg_hपूर्णांकs->ht_params.head_offset =
				दुरत्व(काष्ठा objagg_hपूर्णांकs_node, ht_node);
	objagg_hपूर्णांकs->ht_params.obj_cmpfn = objagg_hपूर्णांकs_obj_cmp;

	err = rhashtable_init(&objagg_hपूर्णांकs->node_ht, &objagg_hपूर्णांकs->ht_params);
	अगर (err)
		जाओ err_rhashtable_init;

	err = algo->fillup_hपूर्णांकs(objagg_hपूर्णांकs, objagg);
	अगर (err)
		जाओ err_fillup_hपूर्णांकs;

	अगर (WARN_ON(objagg_hपूर्णांकs->node_count != objagg->obj_count)) अणु
		err = -EINVAL;
		जाओ err_node_count_check;
	पूर्ण

	वापस objagg_hपूर्णांकs;

err_node_count_check:
err_fillup_hपूर्णांकs:
	objagg_hपूर्णांकs_flush(objagg_hपूर्णांकs);
	rhashtable_destroy(&objagg_hपूर्णांकs->node_ht);
err_rhashtable_init:
	kमुक्त(objagg_hपूर्णांकs);
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(objagg_hपूर्णांकs_get);

/**
 * objagg_hपूर्णांकs_put - माला_दो hपूर्णांकs instance
 * @objagg_hपूर्णांकs:	objagg hपूर्णांकs instance
 *
 * Note: all locking must be provided by the caller.
 */
व्योम objagg_hपूर्णांकs_put(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs)
अणु
	अगर (--objagg_hपूर्णांकs->refcount)
		वापस;
	objagg_hपूर्णांकs_flush(objagg_hपूर्णांकs);
	rhashtable_destroy(&objagg_hपूर्णांकs->node_ht);
	kमुक्त(objagg_hपूर्णांकs);
पूर्ण
EXPORT_SYMBOL(objagg_hपूर्णांकs_put);

/**
 * objagg_hपूर्णांकs_stats_get - obtains stats of the hपूर्णांकs instance
 * @objagg_hपूर्णांकs:	hपूर्णांकs instance
 *
 * Note: all locking must be provided by the caller.
 *
 * The वापसed काष्ठाure contains statistics of all objects
 * currently in use, ordered by following rules:
 * 1) Root objects are always on lower indexes than the rest.
 * 2) Objects with higher delta user count are always on lower
 *    indexes.
 * 3) In हाल multiple objects have the same delta user count,
 *    the objects are ordered by user count.
 *
 * Returns a poपूर्णांकer to stats instance in हाल of success,
 * otherwise it वापसs poपूर्णांकer error using ERR_PTR macro.
 */
स्थिर काष्ठा objagg_stats *
objagg_hपूर्णांकs_stats_get(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs)
अणु
	काष्ठा objagg_stats *objagg_stats;
	काष्ठा objagg_hपूर्णांकs_node *hnode;
	पूर्णांक i;

	objagg_stats = kzalloc(काष्ठा_size(objagg_stats, stats_info,
					   objagg_hपूर्णांकs->node_count),
			       GFP_KERNEL);
	अगर (!objagg_stats)
		वापस ERR_PTR(-ENOMEM);

	i = 0;
	list_क्रम_each_entry(hnode, &objagg_hपूर्णांकs->node_list, list) अणु
		स_नकल(&objagg_stats->stats_info[i], &hnode->stats_info,
		       माप(objagg_stats->stats_info[0]));
		अगर (objagg_stats->stats_info[i].is_root)
			objagg_stats->root_count++;
		i++;
	पूर्ण
	objagg_stats->stats_info_count = i;

	sort(objagg_stats->stats_info, objagg_stats->stats_info_count,
	     माप(काष्ठा objagg_obj_stats_info),
	     objagg_stats_info_sort_cmp_func, शून्य);

	वापस objagg_stats;
पूर्ण
EXPORT_SYMBOL(objagg_hपूर्णांकs_stats_get);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Jiri Pirko <jiri@mellanox.com>");
MODULE_DESCRIPTION("Object aggregation manager");
