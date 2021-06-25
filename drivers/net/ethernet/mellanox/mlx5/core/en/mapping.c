<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2018 Mellanox Technologies */

#समावेश <linux/jhash.h>
#समावेश <linux/slab.h>
#समावेश <linux/xarray.h>
#समावेश <linux/hashtable.h>

#समावेश "mapping.h"

#घोषणा MAPPING_GRACE_PERIOD 2000

काष्ठा mapping_ctx अणु
	काष्ठा xarray xarray;
	DECLARE_HASHTABLE(ht, 8);
	काष्ठा mutex lock; /* Guards hashtable and xarray */
	अचिन्हित दीर्घ max_id;
	माप_प्रकार data_size;
	bool delayed_removal;
	काष्ठा delayed_work dwork;
	काष्ठा list_head pending_list;
	spinlock_t pending_list_lock; /* Guards pending list */
पूर्ण;

काष्ठा mapping_item अणु
	काष्ठा rcu_head rcu;
	काष्ठा list_head list;
	अचिन्हित दीर्घ समयout;
	काष्ठा hlist_node node;
	पूर्णांक cnt;
	u32 id;
	अक्षर data[];
पूर्ण;

पूर्णांक mapping_add(काष्ठा mapping_ctx *ctx, व्योम *data, u32 *id)
अणु
	काष्ठा mapping_item *mi;
	पूर्णांक err = -ENOMEM;
	u32 hash_key;

	mutex_lock(&ctx->lock);

	hash_key = jhash(data, ctx->data_size, 0);
	hash_क्रम_each_possible(ctx->ht, mi, node, hash_key) अणु
		अगर (!स_भेद(data, mi->data, ctx->data_size))
			जाओ attach;
	पूर्ण

	mi = kzalloc(माप(*mi) + ctx->data_size, GFP_KERNEL);
	अगर (!mi)
		जाओ err_alloc;

	स_नकल(mi->data, data, ctx->data_size);
	hash_add(ctx->ht, &mi->node, hash_key);

	err = xa_alloc(&ctx->xarray, &mi->id, mi, XA_LIMIT(1, ctx->max_id),
		       GFP_KERNEL);
	अगर (err)
		जाओ err_assign;
attach:
	++mi->cnt;
	*id = mi->id;

	mutex_unlock(&ctx->lock);

	वापस 0;

err_assign:
	hash_del(&mi->node);
	kमुक्त(mi);
err_alloc:
	mutex_unlock(&ctx->lock);

	वापस err;
पूर्ण

अटल व्योम mapping_हटाओ_and_मुक्त(काष्ठा mapping_ctx *ctx,
				    काष्ठा mapping_item *mi)
अणु
	xa_erase(&ctx->xarray, mi->id);
	kमुक्त_rcu(mi, rcu);
पूर्ण

अटल व्योम mapping_मुक्त_item(काष्ठा mapping_ctx *ctx,
			      काष्ठा mapping_item *mi)
अणु
	अगर (!ctx->delayed_removal) अणु
		mapping_हटाओ_and_मुक्त(ctx, mi);
		वापस;
	पूर्ण

	mi->समयout = jअगरfies + msecs_to_jअगरfies(MAPPING_GRACE_PERIOD);

	spin_lock(&ctx->pending_list_lock);
	list_add_tail(&mi->list, &ctx->pending_list);
	spin_unlock(&ctx->pending_list_lock);

	schedule_delayed_work(&ctx->dwork, MAPPING_GRACE_PERIOD);
पूर्ण

पूर्णांक mapping_हटाओ(काष्ठा mapping_ctx *ctx, u32 id)
अणु
	अचिन्हित दीर्घ index = id;
	काष्ठा mapping_item *mi;
	पूर्णांक err = -ENOENT;

	mutex_lock(&ctx->lock);
	mi = xa_load(&ctx->xarray, index);
	अगर (!mi)
		जाओ out;
	err = 0;

	अगर (--mi->cnt > 0)
		जाओ out;

	hash_del(&mi->node);
	mapping_मुक्त_item(ctx, mi);
out:
	mutex_unlock(&ctx->lock);

	वापस err;
पूर्ण

पूर्णांक mapping_find(काष्ठा mapping_ctx *ctx, u32 id, व्योम *data)
अणु
	अचिन्हित दीर्घ index = id;
	काष्ठा mapping_item *mi;
	पूर्णांक err = -ENOENT;

	rcu_पढ़ो_lock();
	mi = xa_load(&ctx->xarray, index);
	अगर (!mi)
		जाओ err_find;

	स_नकल(data, mi->data, ctx->data_size);
	err = 0;

err_find:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल व्योम
mapping_हटाओ_and_मुक्त_list(काष्ठा mapping_ctx *ctx, काष्ठा list_head *list)
अणु
	काष्ठा mapping_item *mi;

	list_क्रम_each_entry(mi, list, list)
		mapping_हटाओ_and_मुक्त(ctx, mi);
पूर्ण

अटल व्योम mapping_work_handler(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ min_समयout = 0, now = jअगरfies;
	काष्ठा mapping_item *mi, *next;
	LIST_HEAD(pending_items);
	काष्ठा mapping_ctx *ctx;

	ctx = container_of(work, काष्ठा mapping_ctx, dwork.work);

	spin_lock(&ctx->pending_list_lock);
	list_क्रम_each_entry_safe(mi, next, &ctx->pending_list, list) अणु
		अगर (समय_after(now, mi->समयout))
			list_move(&mi->list, &pending_items);
		अन्यथा अगर (!min_समयout ||
			 समय_beक्रमe(mi->समयout, min_समयout))
			min_समयout = mi->समयout;
	पूर्ण
	spin_unlock(&ctx->pending_list_lock);

	mapping_हटाओ_and_मुक्त_list(ctx, &pending_items);

	अगर (min_समयout)
		schedule_delayed_work(&ctx->dwork, असल(min_समयout - now));
पूर्ण

अटल व्योम mapping_flush_work(काष्ठा mapping_ctx *ctx)
अणु
	अगर (!ctx->delayed_removal)
		वापस;

	cancel_delayed_work_sync(&ctx->dwork);
	mapping_हटाओ_and_मुक्त_list(ctx, &ctx->pending_list);
पूर्ण

काष्ठा mapping_ctx *
mapping_create(माप_प्रकार data_size, u32 max_id, bool delayed_removal)
अणु
	काष्ठा mapping_ctx *ctx;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ctx->max_id = max_id ? max_id : अच_पूर्णांक_उच्च;
	ctx->data_size = data_size;

	अगर (delayed_removal) अणु
		INIT_DELAYED_WORK(&ctx->dwork, mapping_work_handler);
		INIT_LIST_HEAD(&ctx->pending_list);
		spin_lock_init(&ctx->pending_list_lock);
		ctx->delayed_removal = true;
	पूर्ण

	mutex_init(&ctx->lock);
	xa_init_flags(&ctx->xarray, XA_FLAGS_ALLOC1);

	वापस ctx;
पूर्ण

व्योम mapping_destroy(काष्ठा mapping_ctx *ctx)
अणु
	mapping_flush_work(ctx);
	xa_destroy(&ctx->xarray);
	mutex_destroy(&ctx->lock);

	kमुक्त(ctx);
पूर्ण
