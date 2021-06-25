<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2014 Patrick McHardy <kaber@trash.net>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>
#समावेश <linux/jhash.h>
#समावेश <linux/netlink.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>

/* We target a hash table size of 4, element hपूर्णांक is 75% of final size */
#घोषणा NFT_RHASH_ELEMENT_HINT 3

काष्ठा nft_rhash अणु
	काष्ठा rhashtable		ht;
	काष्ठा delayed_work		gc_work;
पूर्ण;

काष्ठा nft_rhash_elem अणु
	काष्ठा rhash_head		node;
	काष्ठा nft_set_ext		ext;
पूर्ण;

काष्ठा nft_rhash_cmp_arg अणु
	स्थिर काष्ठा nft_set		*set;
	स्थिर u32			*key;
	u8				genmask;
पूर्ण;

अटल अंतरभूत u32 nft_rhash_key(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा nft_rhash_cmp_arg *arg = data;

	वापस jhash(arg->key, len, seed);
पूर्ण

अटल अंतरभूत u32 nft_rhash_obj(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा nft_rhash_elem *he = data;

	वापस jhash(nft_set_ext_key(&he->ext), len, seed);
पूर्ण

अटल अंतरभूत पूर्णांक nft_rhash_cmp(काष्ठा rhashtable_compare_arg *arg,
				स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा nft_rhash_cmp_arg *x = arg->key;
	स्थिर काष्ठा nft_rhash_elem *he = ptr;

	अगर (स_भेद(nft_set_ext_key(&he->ext), x->key, x->set->klen))
		वापस 1;
	अगर (nft_set_elem_expired(&he->ext))
		वापस 1;
	अगर (!nft_set_elem_active(&he->ext, x->genmask))
		वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params nft_rhash_params = अणु
	.head_offset		= दुरत्व(काष्ठा nft_rhash_elem, node),
	.hashfn			= nft_rhash_key,
	.obj_hashfn		= nft_rhash_obj,
	.obj_cmpfn		= nft_rhash_cmp,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

अटल bool nft_rhash_lookup(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			     स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);
	स्थिर काष्ठा nft_rhash_elem *he;
	काष्ठा nft_rhash_cmp_arg arg = अणु
		.genmask = nft_genmask_cur(net),
		.set	 = set,
		.key	 = key,
	पूर्ण;

	he = rhashtable_lookup(&priv->ht, &arg, nft_rhash_params);
	अगर (he != शून्य)
		*ext = &he->ext;

	वापस !!he;
पूर्ण

अटल व्योम *nft_rhash_get(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			   स्थिर काष्ठा nft_set_elem *elem, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);
	काष्ठा nft_rhash_elem *he;
	काष्ठा nft_rhash_cmp_arg arg = अणु
		.genmask = nft_genmask_cur(net),
		.set	 = set,
		.key	 = elem->key.val.data,
	पूर्ण;

	he = rhashtable_lookup(&priv->ht, &arg, nft_rhash_params);
	अगर (he != शून्य)
		वापस he;

	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल bool nft_rhash_update(काष्ठा nft_set *set, स्थिर u32 *key,
			     व्योम *(*new)(काष्ठा nft_set *,
					  स्थिर काष्ठा nft_expr *,
					  काष्ठा nft_regs *regs),
			     स्थिर काष्ठा nft_expr *expr,
			     काष्ठा nft_regs *regs,
			     स्थिर काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);
	काष्ठा nft_rhash_elem *he, *prev;
	काष्ठा nft_rhash_cmp_arg arg = अणु
		.genmask = NFT_GENMASK_ANY,
		.set	 = set,
		.key	 = key,
	पूर्ण;

	he = rhashtable_lookup(&priv->ht, &arg, nft_rhash_params);
	अगर (he != शून्य)
		जाओ out;

	he = new(set, expr, regs);
	अगर (he == शून्य)
		जाओ err1;

	prev = rhashtable_lookup_get_insert_key(&priv->ht, &arg, &he->node,
						nft_rhash_params);
	अगर (IS_ERR(prev))
		जाओ err2;

	/* Another cpu may race to insert the element with the same key */
	अगर (prev) अणु
		nft_set_elem_destroy(set, he, true);
		he = prev;
	पूर्ण

out:
	*ext = &he->ext;
	वापस true;

err2:
	nft_set_elem_destroy(set, he, true);
err1:
	वापस false;
पूर्ण

अटल पूर्णांक nft_rhash_insert(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			    स्थिर काष्ठा nft_set_elem *elem,
			    काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);
	काष्ठा nft_rhash_elem *he = elem->priv;
	काष्ठा nft_rhash_cmp_arg arg = अणु
		.genmask = nft_genmask_next(net),
		.set	 = set,
		.key	 = elem->key.val.data,
	पूर्ण;
	काष्ठा nft_rhash_elem *prev;

	prev = rhashtable_lookup_get_insert_key(&priv->ht, &arg, &he->node,
						nft_rhash_params);
	अगर (IS_ERR(prev))
		वापस PTR_ERR(prev);
	अगर (prev) अणु
		*ext = &prev->ext;
		वापस -EEXIST;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nft_rhash_activate(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			       स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_rhash_elem *he = elem->priv;

	nft_set_elem_change_active(net, set, &he->ext);
	nft_set_elem_clear_busy(&he->ext);
पूर्ण

अटल bool nft_rhash_flush(स्थिर काष्ठा net *net,
			    स्थिर काष्ठा nft_set *set, व्योम *priv)
अणु
	काष्ठा nft_rhash_elem *he = priv;

	अगर (!nft_set_elem_mark_busy(&he->ext) ||
	    !nft_is_active(net, &he->ext)) अणु
		nft_set_elem_change_active(net, set, &he->ext);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम *nft_rhash_deactivate(स्थिर काष्ठा net *net,
				  स्थिर काष्ठा nft_set *set,
				  स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);
	काष्ठा nft_rhash_elem *he;
	काष्ठा nft_rhash_cmp_arg arg = अणु
		.genmask = nft_genmask_next(net),
		.set	 = set,
		.key	 = elem->key.val.data,
	पूर्ण;

	rcu_पढ़ो_lock();
	he = rhashtable_lookup(&priv->ht, &arg, nft_rhash_params);
	अगर (he != शून्य &&
	    !nft_rhash_flush(net, set, he))
		he = शून्य;

	rcu_पढ़ो_unlock();

	वापस he;
पूर्ण

अटल व्योम nft_rhash_हटाओ(स्थिर काष्ठा net *net,
			     स्थिर काष्ठा nft_set *set,
			     स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);
	काष्ठा nft_rhash_elem *he = elem->priv;

	rhashtable_हटाओ_fast(&priv->ht, &he->node, nft_rhash_params);
पूर्ण

अटल bool nft_rhash_delete(स्थिर काष्ठा nft_set *set,
			     स्थिर u32 *key)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);
	काष्ठा nft_rhash_cmp_arg arg = अणु
		.genmask = NFT_GENMASK_ANY,
		.set = set,
		.key = key,
	पूर्ण;
	काष्ठा nft_rhash_elem *he;

	he = rhashtable_lookup(&priv->ht, &arg, nft_rhash_params);
	अगर (he == शून्य)
		वापस false;

	वापस rhashtable_हटाओ_fast(&priv->ht, &he->node, nft_rhash_params) == 0;
पूर्ण

अटल व्योम nft_rhash_walk(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			   काष्ठा nft_set_iter *iter)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);
	काष्ठा nft_rhash_elem *he;
	काष्ठा rhashtable_iter hti;
	काष्ठा nft_set_elem elem;

	rhashtable_walk_enter(&priv->ht, &hti);
	rhashtable_walk_start(&hti);

	जबतक ((he = rhashtable_walk_next(&hti))) अणु
		अगर (IS_ERR(he)) अणु
			अगर (PTR_ERR(he) != -EAGAIN) अणु
				iter->err = PTR_ERR(he);
				अवरोध;
			पूर्ण

			जारी;
		पूर्ण

		अगर (iter->count < iter->skip)
			जाओ cont;
		अगर (nft_set_elem_expired(&he->ext))
			जाओ cont;
		अगर (!nft_set_elem_active(&he->ext, iter->genmask))
			जाओ cont;

		elem.priv = he;

		iter->err = iter->fn(ctx, set, iter, &elem);
		अगर (iter->err < 0)
			अवरोध;

cont:
		iter->count++;
	पूर्ण
	rhashtable_walk_stop(&hti);
	rhashtable_walk_निकास(&hti);
पूर्ण

अटल bool nft_rhash_expr_needs_gc_run(स्थिर काष्ठा nft_set *set,
					काष्ठा nft_set_ext *ext)
अणु
	काष्ठा nft_set_elem_expr *elem_expr = nft_set_ext_expr(ext);
	काष्ठा nft_expr *expr;
	u32 size;

	nft_setelem_expr_क्रमeach(expr, elem_expr, size) अणु
		अगर (expr->ops->gc &&
		    expr->ops->gc(पढ़ो_pnet(&set->net), expr))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम nft_rhash_gc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nft_set *set;
	काष्ठा nft_rhash_elem *he;
	काष्ठा nft_rhash *priv;
	काष्ठा nft_set_gc_batch *gcb = शून्य;
	काष्ठा rhashtable_iter hti;

	priv = container_of(work, काष्ठा nft_rhash, gc_work.work);
	set  = nft_set_container_of(priv);

	rhashtable_walk_enter(&priv->ht, &hti);
	rhashtable_walk_start(&hti);

	जबतक ((he = rhashtable_walk_next(&hti))) अणु
		अगर (IS_ERR(he)) अणु
			अगर (PTR_ERR(he) != -EAGAIN)
				अवरोध;
			जारी;
		पूर्ण

		अगर (nft_set_ext_exists(&he->ext, NFT_SET_EXT_EXPRESSIONS) &&
		    nft_rhash_expr_needs_gc_run(set, &he->ext))
			जाओ needs_gc_run;

		अगर (!nft_set_elem_expired(&he->ext))
			जारी;
needs_gc_run:
		अगर (nft_set_elem_mark_busy(&he->ext))
			जारी;

		gcb = nft_set_gc_batch_check(set, gcb, GFP_ATOMIC);
		अगर (gcb == शून्य)
			अवरोध;
		rhashtable_हटाओ_fast(&priv->ht, &he->node, nft_rhash_params);
		atomic_dec(&set->nelems);
		nft_set_gc_batch_add(gcb, he);
	पूर्ण
	rhashtable_walk_stop(&hti);
	rhashtable_walk_निकास(&hti);

	he = nft_set_catchall_gc(set);
	अगर (he) अणु
		gcb = nft_set_gc_batch_check(set, gcb, GFP_ATOMIC);
		अगर (gcb)
			nft_set_gc_batch_add(gcb, he);
	पूर्ण
	nft_set_gc_batch_complete(gcb);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &priv->gc_work,
			   nft_set_gc_पूर्णांकerval(set));
पूर्ण

अटल u64 nft_rhash_privsize(स्थिर काष्ठा nlattr * स्थिर nla[],
			      स्थिर काष्ठा nft_set_desc *desc)
अणु
	वापस माप(काष्ठा nft_rhash);
पूर्ण

अटल व्योम nft_rhash_gc_init(स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &priv->gc_work,
			   nft_set_gc_पूर्णांकerval(set));
पूर्ण

अटल पूर्णांक nft_rhash_init(स्थिर काष्ठा nft_set *set,
			  स्थिर काष्ठा nft_set_desc *desc,
			  स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);
	काष्ठा rhashtable_params params = nft_rhash_params;
	पूर्णांक err;

	params.nelem_hपूर्णांक = desc->size ?: NFT_RHASH_ELEMENT_HINT;
	params.key_len	  = set->klen;

	err = rhashtable_init(&priv->ht, &params);
	अगर (err < 0)
		वापस err;

	INIT_DEFERRABLE_WORK(&priv->gc_work, nft_rhash_gc);
	अगर (set->flags & NFT_SET_TIMEOUT)
		nft_rhash_gc_init(set);

	वापस 0;
पूर्ण

अटल व्योम nft_rhash_elem_destroy(व्योम *ptr, व्योम *arg)
अणु
	nft_set_elem_destroy(arg, ptr, true);
पूर्ण

अटल व्योम nft_rhash_destroy(स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_rhash *priv = nft_set_priv(set);

	cancel_delayed_work_sync(&priv->gc_work);
	rcu_barrier();
	rhashtable_मुक्त_and_destroy(&priv->ht, nft_rhash_elem_destroy,
				    (व्योम *)set);
पूर्ण

/* Number of buckets is stored in u32, so cap our result to 1U<<31 */
#घोषणा NFT_MAX_BUCKETS (1U << 31)

अटल u32 nft_hash_buckets(u32 size)
अणु
	u64 val = भाग_u64((u64)size * 4, 3);

	अगर (val >= NFT_MAX_BUCKETS)
		वापस NFT_MAX_BUCKETS;

	वापस roundup_घात_of_two(val);
पूर्ण

अटल bool nft_rhash_estimate(स्थिर काष्ठा nft_set_desc *desc, u32 features,
			       काष्ठा nft_set_estimate *est)
अणु
	est->size   = ~0;
	est->lookup = NFT_SET_CLASS_O_1;
	est->space  = NFT_SET_CLASS_O_N;

	वापस true;
पूर्ण

काष्ठा nft_hash अणु
	u32				seed;
	u32				buckets;
	काष्ठा hlist_head		table[];
पूर्ण;

काष्ठा nft_hash_elem अणु
	काष्ठा hlist_node		node;
	काष्ठा nft_set_ext		ext;
पूर्ण;

अटल bool nft_hash_lookup(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			    स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_hash *priv = nft_set_priv(set);
	u8 genmask = nft_genmask_cur(net);
	स्थिर काष्ठा nft_hash_elem *he;
	u32 hash;

	hash = jhash(key, set->klen, priv->seed);
	hash = reciprocal_scale(hash, priv->buckets);
	hlist_क्रम_each_entry_rcu(he, &priv->table[hash], node) अणु
		अगर (!स_भेद(nft_set_ext_key(&he->ext), key, set->klen) &&
		    nft_set_elem_active(&he->ext, genmask)) अणु
			*ext = &he->ext;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम *nft_hash_get(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			  स्थिर काष्ठा nft_set_elem *elem, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा nft_hash *priv = nft_set_priv(set);
	u8 genmask = nft_genmask_cur(net);
	काष्ठा nft_hash_elem *he;
	u32 hash;

	hash = jhash(elem->key.val.data, set->klen, priv->seed);
	hash = reciprocal_scale(hash, priv->buckets);
	hlist_क्रम_each_entry_rcu(he, &priv->table[hash], node) अणु
		अगर (!स_भेद(nft_set_ext_key(&he->ext), elem->key.val.data, set->klen) &&
		    nft_set_elem_active(&he->ext, genmask))
			वापस he;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

अटल bool nft_hash_lookup_fast(स्थिर काष्ठा net *net,
				 स्थिर काष्ठा nft_set *set,
				 स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_hash *priv = nft_set_priv(set);
	u8 genmask = nft_genmask_cur(net);
	स्थिर काष्ठा nft_hash_elem *he;
	u32 hash, k1, k2;

	k1 = *key;
	hash = jhash_1word(k1, priv->seed);
	hash = reciprocal_scale(hash, priv->buckets);
	hlist_क्रम_each_entry_rcu(he, &priv->table[hash], node) अणु
		k2 = *(u32 *)nft_set_ext_key(&he->ext)->data;
		अगर (k1 == k2 &&
		    nft_set_elem_active(&he->ext, genmask)) अणु
			*ext = &he->ext;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल u32 nft_jhash(स्थिर काष्ठा nft_set *set, स्थिर काष्ठा nft_hash *priv,
		     स्थिर काष्ठा nft_set_ext *ext)
अणु
	स्थिर काष्ठा nft_data *key = nft_set_ext_key(ext);
	u32 hash, k1;

	अगर (set->klen == 4) अणु
		k1 = *(u32 *)key;
		hash = jhash_1word(k1, priv->seed);
	पूर्ण अन्यथा अणु
		hash = jhash(key, set->klen, priv->seed);
	पूर्ण
	hash = reciprocal_scale(hash, priv->buckets);

	वापस hash;
पूर्ण

अटल पूर्णांक nft_hash_insert(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			   स्थिर काष्ठा nft_set_elem *elem,
			   काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_hash_elem *this = elem->priv, *he;
	काष्ठा nft_hash *priv = nft_set_priv(set);
	u8 genmask = nft_genmask_next(net);
	u32 hash;

	hash = nft_jhash(set, priv, &this->ext);
	hlist_क्रम_each_entry(he, &priv->table[hash], node) अणु
		अगर (!स_भेद(nft_set_ext_key(&this->ext),
			    nft_set_ext_key(&he->ext), set->klen) &&
		    nft_set_elem_active(&he->ext, genmask)) अणु
			*ext = &he->ext;
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	hlist_add_head_rcu(&this->node, &priv->table[hash]);
	वापस 0;
पूर्ण

अटल व्योम nft_hash_activate(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			      स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_hash_elem *he = elem->priv;

	nft_set_elem_change_active(net, set, &he->ext);
पूर्ण

अटल bool nft_hash_flush(स्थिर काष्ठा net *net,
			   स्थिर काष्ठा nft_set *set, व्योम *priv)
अणु
	काष्ठा nft_hash_elem *he = priv;

	nft_set_elem_change_active(net, set, &he->ext);
	वापस true;
पूर्ण

अटल व्योम *nft_hash_deactivate(स्थिर काष्ठा net *net,
				 स्थिर काष्ठा nft_set *set,
				 स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_hash *priv = nft_set_priv(set);
	काष्ठा nft_hash_elem *this = elem->priv, *he;
	u8 genmask = nft_genmask_next(net);
	u32 hash;

	hash = nft_jhash(set, priv, &this->ext);
	hlist_क्रम_each_entry(he, &priv->table[hash], node) अणु
		अगर (!स_भेद(nft_set_ext_key(&he->ext), &elem->key.val,
			    set->klen) &&
		    nft_set_elem_active(&he->ext, genmask)) अणु
			nft_set_elem_change_active(net, set, &he->ext);
			वापस he;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम nft_hash_हटाओ(स्थिर काष्ठा net *net,
			    स्थिर काष्ठा nft_set *set,
			    स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_hash_elem *he = elem->priv;

	hlist_del_rcu(&he->node);
पूर्ण

अटल व्योम nft_hash_walk(स्थिर काष्ठा nft_ctx *ctx, काष्ठा nft_set *set,
			  काष्ठा nft_set_iter *iter)
अणु
	काष्ठा nft_hash *priv = nft_set_priv(set);
	काष्ठा nft_hash_elem *he;
	काष्ठा nft_set_elem elem;
	पूर्णांक i;

	क्रम (i = 0; i < priv->buckets; i++) अणु
		hlist_क्रम_each_entry_rcu(he, &priv->table[i], node) अणु
			अगर (iter->count < iter->skip)
				जाओ cont;
			अगर (!nft_set_elem_active(&he->ext, iter->genmask))
				जाओ cont;

			elem.priv = he;

			iter->err = iter->fn(ctx, set, iter, &elem);
			अगर (iter->err < 0)
				वापस;
cont:
			iter->count++;
		पूर्ण
	पूर्ण
पूर्ण

अटल u64 nft_hash_privsize(स्थिर काष्ठा nlattr * स्थिर nla[],
			     स्थिर काष्ठा nft_set_desc *desc)
अणु
	वापस माप(काष्ठा nft_hash) +
	       (u64)nft_hash_buckets(desc->size) * माप(काष्ठा hlist_head);
पूर्ण

अटल पूर्णांक nft_hash_init(स्थिर काष्ठा nft_set *set,
			 स्थिर काष्ठा nft_set_desc *desc,
			 स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_hash *priv = nft_set_priv(set);

	priv->buckets = nft_hash_buckets(desc->size);
	get_अक्रमom_bytes(&priv->seed, माप(priv->seed));

	वापस 0;
पूर्ण

अटल व्योम nft_hash_destroy(स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_hash *priv = nft_set_priv(set);
	काष्ठा nft_hash_elem *he;
	काष्ठा hlist_node *next;
	पूर्णांक i;

	क्रम (i = 0; i < priv->buckets; i++) अणु
		hlist_क्रम_each_entry_safe(he, next, &priv->table[i], node) अणु
			hlist_del_rcu(&he->node);
			nft_set_elem_destroy(set, he, true);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool nft_hash_estimate(स्थिर काष्ठा nft_set_desc *desc, u32 features,
			      काष्ठा nft_set_estimate *est)
अणु
	अगर (!desc->size)
		वापस false;

	अगर (desc->klen == 4)
		वापस false;

	est->size   = माप(काष्ठा nft_hash) +
		      (u64)nft_hash_buckets(desc->size) * माप(काष्ठा hlist_head) +
		      (u64)desc->size * माप(काष्ठा nft_hash_elem);
	est->lookup = NFT_SET_CLASS_O_1;
	est->space  = NFT_SET_CLASS_O_N;

	वापस true;
पूर्ण

अटल bool nft_hash_fast_estimate(स्थिर काष्ठा nft_set_desc *desc, u32 features,
				   काष्ठा nft_set_estimate *est)
अणु
	अगर (!desc->size)
		वापस false;

	अगर (desc->klen != 4)
		वापस false;

	est->size   = माप(काष्ठा nft_hash) +
		      (u64)nft_hash_buckets(desc->size) * माप(काष्ठा hlist_head) +
		      (u64)desc->size * माप(काष्ठा nft_hash_elem);
	est->lookup = NFT_SET_CLASS_O_1;
	est->space  = NFT_SET_CLASS_O_N;

	वापस true;
पूर्ण

स्थिर काष्ठा nft_set_type nft_set_rhash_type = अणु
	.features	= NFT_SET_MAP | NFT_SET_OBJECT |
			  NFT_SET_TIMEOUT | NFT_SET_EVAL,
	.ops		= अणु
		.privsize       = nft_rhash_privsize,
		.elemsize	= दुरत्व(काष्ठा nft_rhash_elem, ext),
		.estimate	= nft_rhash_estimate,
		.init		= nft_rhash_init,
		.gc_init	= nft_rhash_gc_init,
		.destroy	= nft_rhash_destroy,
		.insert		= nft_rhash_insert,
		.activate	= nft_rhash_activate,
		.deactivate	= nft_rhash_deactivate,
		.flush		= nft_rhash_flush,
		.हटाओ		= nft_rhash_हटाओ,
		.lookup		= nft_rhash_lookup,
		.update		= nft_rhash_update,
		.delete		= nft_rhash_delete,
		.walk		= nft_rhash_walk,
		.get		= nft_rhash_get,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा nft_set_type nft_set_hash_type = अणु
	.features	= NFT_SET_MAP | NFT_SET_OBJECT,
	.ops		= अणु
		.privsize       = nft_hash_privsize,
		.elemsize	= दुरत्व(काष्ठा nft_hash_elem, ext),
		.estimate	= nft_hash_estimate,
		.init		= nft_hash_init,
		.destroy	= nft_hash_destroy,
		.insert		= nft_hash_insert,
		.activate	= nft_hash_activate,
		.deactivate	= nft_hash_deactivate,
		.flush		= nft_hash_flush,
		.हटाओ		= nft_hash_हटाओ,
		.lookup		= nft_hash_lookup,
		.walk		= nft_hash_walk,
		.get		= nft_hash_get,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा nft_set_type nft_set_hash_fast_type = अणु
	.features	= NFT_SET_MAP | NFT_SET_OBJECT,
	.ops		= अणु
		.privsize       = nft_hash_privsize,
		.elemsize	= दुरत्व(काष्ठा nft_hash_elem, ext),
		.estimate	= nft_hash_fast_estimate,
		.init		= nft_hash_init,
		.destroy	= nft_hash_destroy,
		.insert		= nft_hash_insert,
		.activate	= nft_hash_activate,
		.deactivate	= nft_hash_deactivate,
		.flush		= nft_hash_flush,
		.हटाओ		= nft_hash_हटाओ,
		.lookup		= nft_hash_lookup_fast,
		.walk		= nft_hash_walk,
		.get		= nft_hash_get,
	पूर्ण,
पूर्ण;
