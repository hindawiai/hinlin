<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Patrick McHardy <kaber@trash.net>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>

काष्ठा nft_rbtree अणु
	काष्ठा rb_root		root;
	rwlock_t		lock;
	seqcount_rwlock_t	count;
	काष्ठा delayed_work	gc_work;
पूर्ण;

काष्ठा nft_rbtree_elem अणु
	काष्ठा rb_node		node;
	काष्ठा nft_set_ext	ext;
पूर्ण;

अटल bool nft_rbtree_पूर्णांकerval_end(स्थिर काष्ठा nft_rbtree_elem *rbe)
अणु
	वापस nft_set_ext_exists(&rbe->ext, NFT_SET_EXT_FLAGS) &&
	       (*nft_set_ext_flags(&rbe->ext) & NFT_SET_ELEM_INTERVAL_END);
पूर्ण

अटल bool nft_rbtree_पूर्णांकerval_start(स्थिर काष्ठा nft_rbtree_elem *rbe)
अणु
	वापस !nft_rbtree_पूर्णांकerval_end(rbe);
पूर्ण

अटल bool nft_rbtree_equal(स्थिर काष्ठा nft_set *set, स्थिर व्योम *this,
			     स्थिर काष्ठा nft_rbtree_elem *पूर्णांकerval)
अणु
	वापस स_भेद(this, nft_set_ext_key(&पूर्णांकerval->ext), set->klen) == 0;
पूर्ण

अटल bool __nft_rbtree_lookup(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
				स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext,
				अचिन्हित पूर्णांक seq)
अणु
	काष्ठा nft_rbtree *priv = nft_set_priv(set);
	स्थिर काष्ठा nft_rbtree_elem *rbe, *पूर्णांकerval = शून्य;
	u8 genmask = nft_genmask_cur(net);
	स्थिर काष्ठा rb_node *parent;
	स्थिर व्योम *this;
	पूर्णांक d;

	parent = rcu_dereference_raw(priv->root.rb_node);
	जबतक (parent != शून्य) अणु
		अगर (पढ़ो_seqcount_retry(&priv->count, seq))
			वापस false;

		rbe = rb_entry(parent, काष्ठा nft_rbtree_elem, node);

		this = nft_set_ext_key(&rbe->ext);
		d = स_भेद(this, key, set->klen);
		अगर (d < 0) अणु
			parent = rcu_dereference_raw(parent->rb_left);
			अगर (पूर्णांकerval &&
			    nft_rbtree_equal(set, this, पूर्णांकerval) &&
			    nft_rbtree_पूर्णांकerval_end(rbe) &&
			    nft_rbtree_पूर्णांकerval_start(पूर्णांकerval))
				जारी;
			पूर्णांकerval = rbe;
		पूर्ण अन्यथा अगर (d > 0)
			parent = rcu_dereference_raw(parent->rb_right);
		अन्यथा अणु
			अगर (!nft_set_elem_active(&rbe->ext, genmask)) अणु
				parent = rcu_dereference_raw(parent->rb_left);
				जारी;
			पूर्ण

			अगर (nft_set_elem_expired(&rbe->ext))
				वापस false;

			अगर (nft_rbtree_पूर्णांकerval_end(rbe)) अणु
				अगर (nft_set_is_anonymous(set))
					वापस false;
				parent = rcu_dereference_raw(parent->rb_left);
				पूर्णांकerval = शून्य;
				जारी;
			पूर्ण

			*ext = &rbe->ext;
			वापस true;
		पूर्ण
	पूर्ण

	अगर (set->flags & NFT_SET_INTERVAL && पूर्णांकerval != शून्य &&
	    nft_set_elem_active(&पूर्णांकerval->ext, genmask) &&
	    !nft_set_elem_expired(&पूर्णांकerval->ext) &&
	    nft_rbtree_पूर्णांकerval_start(पूर्णांकerval)) अणु
		*ext = &पूर्णांकerval->ext;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool nft_rbtree_lookup(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			      स्थिर u32 *key, स्थिर काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_rbtree *priv = nft_set_priv(set);
	अचिन्हित पूर्णांक seq = पढ़ो_seqcount_begin(&priv->count);
	bool ret;

	ret = __nft_rbtree_lookup(net, set, key, ext, seq);
	अगर (ret || !पढ़ो_seqcount_retry(&priv->count, seq))
		वापस ret;

	पढ़ो_lock_bh(&priv->lock);
	seq = पढ़ो_seqcount_begin(&priv->count);
	ret = __nft_rbtree_lookup(net, set, key, ext, seq);
	पढ़ो_unlock_bh(&priv->lock);

	वापस ret;
पूर्ण

अटल bool __nft_rbtree_get(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			     स्थिर u32 *key, काष्ठा nft_rbtree_elem **elem,
			     अचिन्हित पूर्णांक seq, अचिन्हित पूर्णांक flags, u8 genmask)
अणु
	काष्ठा nft_rbtree_elem *rbe, *पूर्णांकerval = शून्य;
	काष्ठा nft_rbtree *priv = nft_set_priv(set);
	स्थिर काष्ठा rb_node *parent;
	स्थिर व्योम *this;
	पूर्णांक d;

	parent = rcu_dereference_raw(priv->root.rb_node);
	जबतक (parent != शून्य) अणु
		अगर (पढ़ो_seqcount_retry(&priv->count, seq))
			वापस false;

		rbe = rb_entry(parent, काष्ठा nft_rbtree_elem, node);

		this = nft_set_ext_key(&rbe->ext);
		d = स_भेद(this, key, set->klen);
		अगर (d < 0) अणु
			parent = rcu_dereference_raw(parent->rb_left);
			अगर (!(flags & NFT_SET_ELEM_INTERVAL_END))
				पूर्णांकerval = rbe;
		पूर्ण अन्यथा अगर (d > 0) अणु
			parent = rcu_dereference_raw(parent->rb_right);
			अगर (flags & NFT_SET_ELEM_INTERVAL_END)
				पूर्णांकerval = rbe;
		पूर्ण अन्यथा अणु
			अगर (!nft_set_elem_active(&rbe->ext, genmask)) अणु
				parent = rcu_dereference_raw(parent->rb_left);
				जारी;
			पूर्ण

			अगर (nft_set_elem_expired(&rbe->ext))
				वापस false;

			अगर (!nft_set_ext_exists(&rbe->ext, NFT_SET_EXT_FLAGS) ||
			    (*nft_set_ext_flags(&rbe->ext) & NFT_SET_ELEM_INTERVAL_END) ==
			    (flags & NFT_SET_ELEM_INTERVAL_END)) अणु
				*elem = rbe;
				वापस true;
			पूर्ण

			अगर (nft_rbtree_पूर्णांकerval_end(rbe))
				पूर्णांकerval = शून्य;

			parent = rcu_dereference_raw(parent->rb_left);
		पूर्ण
	पूर्ण

	अगर (set->flags & NFT_SET_INTERVAL && पूर्णांकerval != शून्य &&
	    nft_set_elem_active(&पूर्णांकerval->ext, genmask) &&
	    !nft_set_elem_expired(&पूर्णांकerval->ext) &&
	    ((!nft_rbtree_पूर्णांकerval_end(पूर्णांकerval) &&
	      !(flags & NFT_SET_ELEM_INTERVAL_END)) ||
	     (nft_rbtree_पूर्णांकerval_end(पूर्णांकerval) &&
	      (flags & NFT_SET_ELEM_INTERVAL_END)))) अणु
		*elem = पूर्णांकerval;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम *nft_rbtree_get(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			    स्थिर काष्ठा nft_set_elem *elem, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा nft_rbtree *priv = nft_set_priv(set);
	अचिन्हित पूर्णांक seq = पढ़ो_seqcount_begin(&priv->count);
	काष्ठा nft_rbtree_elem *rbe = ERR_PTR(-ENOENT);
	स्थिर u32 *key = (स्थिर u32 *)&elem->key.val;
	u8 genmask = nft_genmask_cur(net);
	bool ret;

	ret = __nft_rbtree_get(net, set, key, &rbe, seq, flags, genmask);
	अगर (ret || !पढ़ो_seqcount_retry(&priv->count, seq))
		वापस rbe;

	पढ़ो_lock_bh(&priv->lock);
	seq = पढ़ो_seqcount_begin(&priv->count);
	ret = __nft_rbtree_get(net, set, key, &rbe, seq, flags, genmask);
	अगर (!ret)
		rbe = ERR_PTR(-ENOENT);
	पढ़ो_unlock_bh(&priv->lock);

	वापस rbe;
पूर्ण

अटल पूर्णांक __nft_rbtree_insert(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			       काष्ठा nft_rbtree_elem *new,
			       काष्ठा nft_set_ext **ext)
अणु
	bool overlap = false, dup_end_left = false, dup_end_right = false;
	काष्ठा nft_rbtree *priv = nft_set_priv(set);
	u8 genmask = nft_genmask_next(net);
	काष्ठा nft_rbtree_elem *rbe;
	काष्ठा rb_node *parent, **p;
	पूर्णांक d;

	/* Detect overlaps as we descend the tree. Set the flag in these हालs:
	 *
	 * a1. _ _ __>|  ?_ _ __|  (insert end beक्रमe existing end)
	 * a2. _ _ ___|  ?_ _ _>|  (insert end after existing end)
	 * a3. _ _ ___? >|_ _ __|  (insert start beक्रमe existing end)
	 *
	 * and clear it later on, as we eventually reach the poपूर्णांकs indicated by
	 * '?' above, in the cases described below. We'll always meet these
	 * later, locally, due to tree ordering, and overlaps क्रम the पूर्णांकervals
	 * that are the बंदst together are always evaluated last.
	 *
	 * b1. _ _ __>|  !_ _ __|  (insert end beक्रमe existing start)
	 * b2. _ _ ___|  !_ _ _>|  (insert end after existing start)
	 * b3. _ _ ___! >|_ _ __|  (insert start after existing end, as a leaf)
	 *            '--' no nodes falling in this range
	 * b4.          >|_ _   !  (insert start beक्रमe existing start)
	 *
	 * Case a3. resolves to b3.:
	 * - अगर the inserted start element is the lefपंचांगost, because the '0'
	 *   element in the tree serves as end element
	 * - otherwise, अगर an existing end is found immediately to the left. If
	 *   there are existing nodes in between, we need to further descend the
	 *   tree beक्रमe we can conclude the new start isn't causing an overlap
	 *
	 * or to b4., which, preceded by a3., means we alपढ़ोy traversed one or
	 * more existing पूर्णांकervals entirely, from the right.
	 *
	 * For a new, righपंचांगost pair of elements, we'll hit हालs b3. and b2.,
	 * in that order.
	 *
	 * The flag is also cleared in two special हालs:
	 *
	 * b5. |__ _ _!|<_ _ _   (insert start right beक्रमe existing end)
	 * b6. |__ _ >|!__ _ _   (insert end right after existing start)
	 *
	 * which always happen as last step and imply that no further
	 * overlapping is possible.
	 *
	 * Another special हाल comes from the fact that start elements matching
	 * an alपढ़ोy existing start element are allowed: insertion is not
	 * perक्रमmed but we वापस -EEXIST in that हाल, and the error will be
	 * cleared by the caller अगर NLM_F_EXCL is not present in the request.
	 * This way, request क्रम insertion of an exact overlap isn't reported as
	 * error to userspace अगर not desired.
	 *
	 * However, अगर the existing start matches a pre-existing start, but the
	 * end element करोesn't match the corresponding pre-existing end element,
	 * we need to report a partial overlap. This is a local condition that
	 * can be noticed without need क्रम a tracking flag, by checking क्रम a
	 * local duplicated end क्रम a corresponding start, from left and right,
	 * separately.
	 */

	parent = शून्य;
	p = &priv->root.rb_node;
	जबतक (*p != शून्य) अणु
		parent = *p;
		rbe = rb_entry(parent, काष्ठा nft_rbtree_elem, node);
		d = स_भेद(nft_set_ext_key(&rbe->ext),
			   nft_set_ext_key(&new->ext),
			   set->klen);
		अगर (d < 0) अणु
			p = &parent->rb_left;

			अगर (nft_rbtree_पूर्णांकerval_start(new)) अणु
				अगर (nft_rbtree_पूर्णांकerval_end(rbe) &&
				    nft_set_elem_active(&rbe->ext, genmask) &&
				    !nft_set_elem_expired(&rbe->ext) && !*p)
					overlap = false;
			पूर्ण अन्यथा अणु
				अगर (dup_end_left && !*p)
					वापस -ENOTEMPTY;

				overlap = nft_rbtree_पूर्णांकerval_end(rbe) &&
					  nft_set_elem_active(&rbe->ext,
							      genmask) &&
					  !nft_set_elem_expired(&rbe->ext);

				अगर (overlap) अणु
					dup_end_right = true;
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (d > 0) अणु
			p = &parent->rb_right;

			अगर (nft_rbtree_पूर्णांकerval_end(new)) अणु
				अगर (dup_end_right && !*p)
					वापस -ENOTEMPTY;

				overlap = nft_rbtree_पूर्णांकerval_end(rbe) &&
					  nft_set_elem_active(&rbe->ext,
							      genmask) &&
					  !nft_set_elem_expired(&rbe->ext);

				अगर (overlap) अणु
					dup_end_left = true;
					जारी;
				पूर्ण
			पूर्ण अन्यथा अगर (nft_set_elem_active(&rbe->ext, genmask) &&
				   !nft_set_elem_expired(&rbe->ext)) अणु
				overlap = nft_rbtree_पूर्णांकerval_end(rbe);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (nft_rbtree_पूर्णांकerval_end(rbe) &&
			    nft_rbtree_पूर्णांकerval_start(new)) अणु
				p = &parent->rb_left;

				अगर (nft_set_elem_active(&rbe->ext, genmask) &&
				    !nft_set_elem_expired(&rbe->ext))
					overlap = false;
			पूर्ण अन्यथा अगर (nft_rbtree_पूर्णांकerval_start(rbe) &&
				   nft_rbtree_पूर्णांकerval_end(new)) अणु
				p = &parent->rb_right;

				अगर (nft_set_elem_active(&rbe->ext, genmask) &&
				    !nft_set_elem_expired(&rbe->ext))
					overlap = false;
			पूर्ण अन्यथा अगर (nft_set_elem_active(&rbe->ext, genmask) &&
				   !nft_set_elem_expired(&rbe->ext)) अणु
				*ext = &rbe->ext;
				वापस -EEXIST;
			पूर्ण अन्यथा अणु
				p = &parent->rb_left;
			पूर्ण
		पूर्ण

		dup_end_left = dup_end_right = false;
	पूर्ण

	अगर (overlap)
		वापस -ENOTEMPTY;

	rb_link_node_rcu(&new->node, parent, p);
	rb_insert_color(&new->node, &priv->root);
	वापस 0;
पूर्ण

अटल पूर्णांक nft_rbtree_insert(स्थिर काष्ठा net *net, स्थिर काष्ठा nft_set *set,
			     स्थिर काष्ठा nft_set_elem *elem,
			     काष्ठा nft_set_ext **ext)
अणु
	काष्ठा nft_rbtree *priv = nft_set_priv(set);
	काष्ठा nft_rbtree_elem *rbe = elem->priv;
	पूर्णांक err;

	ग_लिखो_lock_bh(&priv->lock);
	ग_लिखो_seqcount_begin(&priv->count);
	err = __nft_rbtree_insert(net, set, rbe, ext);
	ग_लिखो_seqcount_end(&priv->count);
	ग_लिखो_unlock_bh(&priv->lock);

	वापस err;
पूर्ण

अटल व्योम nft_rbtree_हटाओ(स्थिर काष्ठा net *net,
			      स्थिर काष्ठा nft_set *set,
			      स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_rbtree *priv = nft_set_priv(set);
	काष्ठा nft_rbtree_elem *rbe = elem->priv;

	ग_लिखो_lock_bh(&priv->lock);
	ग_लिखो_seqcount_begin(&priv->count);
	rb_erase(&rbe->node, &priv->root);
	ग_लिखो_seqcount_end(&priv->count);
	ग_लिखो_unlock_bh(&priv->lock);
पूर्ण

अटल व्योम nft_rbtree_activate(स्थिर काष्ठा net *net,
				स्थिर काष्ठा nft_set *set,
				स्थिर काष्ठा nft_set_elem *elem)
अणु
	काष्ठा nft_rbtree_elem *rbe = elem->priv;

	nft_set_elem_change_active(net, set, &rbe->ext);
	nft_set_elem_clear_busy(&rbe->ext);
पूर्ण

अटल bool nft_rbtree_flush(स्थिर काष्ठा net *net,
			     स्थिर काष्ठा nft_set *set, व्योम *priv)
अणु
	काष्ठा nft_rbtree_elem *rbe = priv;

	अगर (!nft_set_elem_mark_busy(&rbe->ext) ||
	    !nft_is_active(net, &rbe->ext)) अणु
		nft_set_elem_change_active(net, set, &rbe->ext);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम *nft_rbtree_deactivate(स्थिर काष्ठा net *net,
				   स्थिर काष्ठा nft_set *set,
				   स्थिर काष्ठा nft_set_elem *elem)
अणु
	स्थिर काष्ठा nft_rbtree *priv = nft_set_priv(set);
	स्थिर काष्ठा rb_node *parent = priv->root.rb_node;
	काष्ठा nft_rbtree_elem *rbe, *this = elem->priv;
	u8 genmask = nft_genmask_next(net);
	पूर्णांक d;

	जबतक (parent != शून्य) अणु
		rbe = rb_entry(parent, काष्ठा nft_rbtree_elem, node);

		d = स_भेद(nft_set_ext_key(&rbe->ext), &elem->key.val,
					   set->klen);
		अगर (d < 0)
			parent = parent->rb_left;
		अन्यथा अगर (d > 0)
			parent = parent->rb_right;
		अन्यथा अणु
			अगर (nft_rbtree_पूर्णांकerval_end(rbe) &&
			    nft_rbtree_पूर्णांकerval_start(this)) अणु
				parent = parent->rb_left;
				जारी;
			पूर्ण अन्यथा अगर (nft_rbtree_पूर्णांकerval_start(rbe) &&
				   nft_rbtree_पूर्णांकerval_end(this)) अणु
				parent = parent->rb_right;
				जारी;
			पूर्ण अन्यथा अगर (!nft_set_elem_active(&rbe->ext, genmask)) अणु
				parent = parent->rb_left;
				जारी;
			पूर्ण
			nft_rbtree_flush(net, set, rbe);
			वापस rbe;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम nft_rbtree_walk(स्थिर काष्ठा nft_ctx *ctx,
			    काष्ठा nft_set *set,
			    काष्ठा nft_set_iter *iter)
अणु
	काष्ठा nft_rbtree *priv = nft_set_priv(set);
	काष्ठा nft_rbtree_elem *rbe;
	काष्ठा nft_set_elem elem;
	काष्ठा rb_node *node;

	पढ़ो_lock_bh(&priv->lock);
	क्रम (node = rb_first(&priv->root); node != शून्य; node = rb_next(node)) अणु
		rbe = rb_entry(node, काष्ठा nft_rbtree_elem, node);

		अगर (iter->count < iter->skip)
			जाओ cont;
		अगर (nft_set_elem_expired(&rbe->ext))
			जाओ cont;
		अगर (!nft_set_elem_active(&rbe->ext, iter->genmask))
			जाओ cont;

		elem.priv = rbe;

		iter->err = iter->fn(ctx, set, iter, &elem);
		अगर (iter->err < 0) अणु
			पढ़ो_unlock_bh(&priv->lock);
			वापस;
		पूर्ण
cont:
		iter->count++;
	पूर्ण
	पढ़ो_unlock_bh(&priv->lock);
पूर्ण

अटल व्योम nft_rbtree_gc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nft_rbtree_elem *rbe, *rbe_end = शून्य, *rbe_prev = शून्य;
	काष्ठा nft_set_gc_batch *gcb = शून्य;
	काष्ठा nft_rbtree *priv;
	काष्ठा rb_node *node;
	काष्ठा nft_set *set;

	priv = container_of(work, काष्ठा nft_rbtree, gc_work.work);
	set  = nft_set_container_of(priv);

	ग_लिखो_lock_bh(&priv->lock);
	ग_लिखो_seqcount_begin(&priv->count);
	क्रम (node = rb_first(&priv->root); node != शून्य; node = rb_next(node)) अणु
		rbe = rb_entry(node, काष्ठा nft_rbtree_elem, node);

		अगर (nft_rbtree_पूर्णांकerval_end(rbe)) अणु
			rbe_end = rbe;
			जारी;
		पूर्ण
		अगर (!nft_set_elem_expired(&rbe->ext))
			जारी;
		अगर (nft_set_elem_mark_busy(&rbe->ext))
			जारी;

		अगर (rbe_prev) अणु
			rb_erase(&rbe_prev->node, &priv->root);
			rbe_prev = शून्य;
		पूर्ण
		gcb = nft_set_gc_batch_check(set, gcb, GFP_ATOMIC);
		अगर (!gcb)
			अवरोध;

		atomic_dec(&set->nelems);
		nft_set_gc_batch_add(gcb, rbe);
		rbe_prev = rbe;

		अगर (rbe_end) अणु
			atomic_dec(&set->nelems);
			nft_set_gc_batch_add(gcb, rbe_end);
			rb_erase(&rbe_end->node, &priv->root);
			rbe_end = शून्य;
		पूर्ण
		node = rb_next(node);
		अगर (!node)
			अवरोध;
	पूर्ण
	अगर (rbe_prev)
		rb_erase(&rbe_prev->node, &priv->root);
	ग_लिखो_seqcount_end(&priv->count);
	ग_लिखो_unlock_bh(&priv->lock);

	rbe = nft_set_catchall_gc(set);
	अगर (rbe) अणु
		gcb = nft_set_gc_batch_check(set, gcb, GFP_ATOMIC);
		अगर (gcb)
			nft_set_gc_batch_add(gcb, rbe);
	पूर्ण
	nft_set_gc_batch_complete(gcb);

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &priv->gc_work,
			   nft_set_gc_पूर्णांकerval(set));
पूर्ण

अटल u64 nft_rbtree_privsize(स्थिर काष्ठा nlattr * स्थिर nla[],
			       स्थिर काष्ठा nft_set_desc *desc)
अणु
	वापस माप(काष्ठा nft_rbtree);
पूर्ण

अटल पूर्णांक nft_rbtree_init(स्थिर काष्ठा nft_set *set,
			   स्थिर काष्ठा nft_set_desc *desc,
			   स्थिर काष्ठा nlattr * स्थिर nla[])
अणु
	काष्ठा nft_rbtree *priv = nft_set_priv(set);

	rwlock_init(&priv->lock);
	seqcount_rwlock_init(&priv->count, &priv->lock);
	priv->root = RB_ROOT;

	INIT_DEFERRABLE_WORK(&priv->gc_work, nft_rbtree_gc);
	अगर (set->flags & NFT_SET_TIMEOUT)
		queue_delayed_work(प्रणाली_घातer_efficient_wq, &priv->gc_work,
				   nft_set_gc_पूर्णांकerval(set));

	वापस 0;
पूर्ण

अटल व्योम nft_rbtree_destroy(स्थिर काष्ठा nft_set *set)
अणु
	काष्ठा nft_rbtree *priv = nft_set_priv(set);
	काष्ठा nft_rbtree_elem *rbe;
	काष्ठा rb_node *node;

	cancel_delayed_work_sync(&priv->gc_work);
	rcu_barrier();
	जबतक ((node = priv->root.rb_node) != शून्य) अणु
		rb_erase(node, &priv->root);
		rbe = rb_entry(node, काष्ठा nft_rbtree_elem, node);
		nft_set_elem_destroy(set, rbe, true);
	पूर्ण
पूर्ण

अटल bool nft_rbtree_estimate(स्थिर काष्ठा nft_set_desc *desc, u32 features,
				काष्ठा nft_set_estimate *est)
अणु
	अगर (desc->field_count > 1)
		वापस false;

	अगर (desc->size)
		est->size = माप(काष्ठा nft_rbtree) +
			    desc->size * माप(काष्ठा nft_rbtree_elem);
	अन्यथा
		est->size = ~0;

	est->lookup = NFT_SET_CLASS_O_LOG_N;
	est->space  = NFT_SET_CLASS_O_N;

	वापस true;
पूर्ण

स्थिर काष्ठा nft_set_type nft_set_rbtree_type = अणु
	.features	= NFT_SET_INTERVAL | NFT_SET_MAP | NFT_SET_OBJECT | NFT_SET_TIMEOUT,
	.ops		= अणु
		.privsize	= nft_rbtree_privsize,
		.elemsize	= दुरत्व(काष्ठा nft_rbtree_elem, ext),
		.estimate	= nft_rbtree_estimate,
		.init		= nft_rbtree_init,
		.destroy	= nft_rbtree_destroy,
		.insert		= nft_rbtree_insert,
		.हटाओ		= nft_rbtree_हटाओ,
		.deactivate	= nft_rbtree_deactivate,
		.flush		= nft_rbtree_flush,
		.activate	= nft_rbtree_activate,
		.lookup		= nft_rbtree_lookup,
		.walk		= nft_rbtree_walk,
		.get		= nft_rbtree_get,
	पूर्ण,
पूर्ण;
