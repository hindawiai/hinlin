<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/kernfs/dir.c - kernfs directory implementation
 *
 * Copyright (c) 2001-3 Patrick Mochel
 * Copyright (c) 2007 SUSE Linux Products GmbH
 * Copyright (c) 2007, 2013 Tejun Heo <tj@kernel.org>
 */

#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश <linux/hash.h>

#समावेश "kernfs-internal.h"

DEFINE_MUTEX(kernfs_mutex);
अटल DEFINE_SPINLOCK(kernfs_नाम_lock);	/* kn->parent and ->name */
अटल अक्षर kernfs_pr_cont_buf[PATH_MAX];	/* रक्षित by नाम_lock */
अटल DEFINE_SPINLOCK(kernfs_idr_lock);	/* root->ino_idr */

#घोषणा rb_to_kn(X) rb_entry((X), काष्ठा kernfs_node, rb)

अटल bool kernfs_active(काष्ठा kernfs_node *kn)
अणु
	lockdep_निश्चित_held(&kernfs_mutex);
	वापस atomic_पढ़ो(&kn->active) >= 0;
पूर्ण

अटल bool kernfs_lockdep(काष्ठा kernfs_node *kn)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	वापस kn->flags & KERNFS_LOCKDEP;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक kernfs_name_locked(काष्ठा kernfs_node *kn, अक्षर *buf, माप_प्रकार buflen)
अणु
	अगर (!kn)
		वापस strlcpy(buf, "(null)", buflen);

	वापस strlcpy(buf, kn->parent ? kn->name : "/", buflen);
पूर्ण

/* kernfs_node_depth - compute depth from @from to @to */
अटल माप_प्रकार kernfs_depth(काष्ठा kernfs_node *from, काष्ठा kernfs_node *to)
अणु
	माप_प्रकार depth = 0;

	जबतक (to->parent && to != from) अणु
		depth++;
		to = to->parent;
	पूर्ण
	वापस depth;
पूर्ण

अटल काष्ठा kernfs_node *kernfs_common_ancestor(काष्ठा kernfs_node *a,
						  काष्ठा kernfs_node *b)
अणु
	माप_प्रकार da, db;
	काष्ठा kernfs_root *ra = kernfs_root(a), *rb = kernfs_root(b);

	अगर (ra != rb)
		वापस शून्य;

	da = kernfs_depth(ra->kn, a);
	db = kernfs_depth(rb->kn, b);

	जबतक (da > db) अणु
		a = a->parent;
		da--;
	पूर्ण
	जबतक (db > da) अणु
		b = b->parent;
		db--;
	पूर्ण

	/* worst हाल b and a will be the same at root */
	जबतक (b != a) अणु
		b = b->parent;
		a = a->parent;
	पूर्ण

	वापस a;
पूर्ण

/**
 * kernfs_path_from_node_locked - find a pseuकरो-असलolute path to @kn_to,
 * where kn_from is treated as root of the path.
 * @kn_from: kernfs node which should be treated as root क्रम the path
 * @kn_to: kernfs node to which path is needed
 * @buf: buffer to copy the path पूर्णांकo
 * @buflen: size of @buf
 *
 * We need to handle couple of scenarios here:
 * [1] when @kn_from is an ancestor of @kn_to at some level
 * kn_from: /n1/n2/n3
 * kn_to:   /n1/n2/n3/n4/n5
 * result:  /n4/n5
 *
 * [2] when @kn_from is on a dअगरferent hierarchy and we need to find common
 * ancestor between @kn_from and @kn_to.
 * kn_from: /n1/n2/n3/n4
 * kn_to:   /n1/n2/n5
 * result:  /../../n5
 * OR
 * kn_from: /n1/n2/n3/n4/n5   [depth=5]
 * kn_to:   /n1/n2/n3         [depth=3]
 * result:  /../..
 *
 * [3] when @kn_to is शून्य result will be "(null)"
 *
 * Returns the length of the full path.  If the full length is equal to or
 * greater than @buflen, @buf contains the truncated path with the trailing
 * '\0'.  On error, -त्रुटि_सं is वापसed.
 */
अटल पूर्णांक kernfs_path_from_node_locked(काष्ठा kernfs_node *kn_to,
					काष्ठा kernfs_node *kn_from,
					अक्षर *buf, माप_प्रकार buflen)
अणु
	काष्ठा kernfs_node *kn, *common;
	स्थिर अक्षर parent_str[] = "/..";
	माप_प्रकार depth_from, depth_to, len = 0;
	पूर्णांक i, j;

	अगर (!kn_to)
		वापस strlcpy(buf, "(null)", buflen);

	अगर (!kn_from)
		kn_from = kernfs_root(kn_to)->kn;

	अगर (kn_from == kn_to)
		वापस strlcpy(buf, "/", buflen);

	अगर (!buf)
		वापस -EINVAL;

	common = kernfs_common_ancestor(kn_from, kn_to);
	अगर (WARN_ON(!common))
		वापस -EINVAL;

	depth_to = kernfs_depth(common, kn_to);
	depth_from = kernfs_depth(common, kn_from);

	buf[0] = '\0';

	क्रम (i = 0; i < depth_from; i++)
		len += strlcpy(buf + len, parent_str,
			       len < buflen ? buflen - len : 0);

	/* Calculate how many bytes we need क्रम the rest */
	क्रम (i = depth_to - 1; i >= 0; i--) अणु
		क्रम (kn = kn_to, j = 0; j < i; j++)
			kn = kn->parent;
		len += strlcpy(buf + len, "/",
			       len < buflen ? buflen - len : 0);
		len += strlcpy(buf + len, kn->name,
			       len < buflen ? buflen - len : 0);
	पूर्ण

	वापस len;
पूर्ण

/**
 * kernfs_name - obtain the name of a given node
 * @kn: kernfs_node of पूर्णांकerest
 * @buf: buffer to copy @kn's name पूर्णांकo
 * @buflen: size of @buf
 *
 * Copies the name of @kn पूर्णांकo @buf of @buflen bytes.  The behavior is
 * similar to strlcpy().  It वापसs the length of @kn's name and अगर @buf
 * isn't long enough, it's filled upto @buflen-1 and nul terminated.
 *
 * Fills buffer with "(null)" अगर @kn is शून्य.
 *
 * This function can be called from any context.
 */
पूर्णांक kernfs_name(काष्ठा kernfs_node *kn, अक्षर *buf, माप_प्रकार buflen)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&kernfs_नाम_lock, flags);
	ret = kernfs_name_locked(kn, buf, buflen);
	spin_unlock_irqrestore(&kernfs_नाम_lock, flags);
	वापस ret;
पूर्ण

/**
 * kernfs_path_from_node - build path of node @to relative to @from.
 * @from: parent kernfs_node relative to which we need to build the path
 * @to: kernfs_node of पूर्णांकerest
 * @buf: buffer to copy @to's path पूर्णांकo
 * @buflen: size of @buf
 *
 * Builds @to's path relative to @from in @buf. @from and @to must
 * be on the same kernfs-root. If @from is not parent of @to, then a relative
 * path (which includes '..'s) as needed to reach from @from to @to is
 * वापसed.
 *
 * Returns the length of the full path.  If the full length is equal to or
 * greater than @buflen, @buf contains the truncated path with the trailing
 * '\0'.  On error, -त्रुटि_सं is वापसed.
 */
पूर्णांक kernfs_path_from_node(काष्ठा kernfs_node *to, काष्ठा kernfs_node *from,
			  अक्षर *buf, माप_प्रकार buflen)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&kernfs_नाम_lock, flags);
	ret = kernfs_path_from_node_locked(to, from, buf, buflen);
	spin_unlock_irqrestore(&kernfs_नाम_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kernfs_path_from_node);

/**
 * pr_cont_kernfs_name - pr_cont name of a kernfs_node
 * @kn: kernfs_node of पूर्णांकerest
 *
 * This function can be called from any context.
 */
व्योम pr_cont_kernfs_name(काष्ठा kernfs_node *kn)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kernfs_नाम_lock, flags);

	kernfs_name_locked(kn, kernfs_pr_cont_buf, माप(kernfs_pr_cont_buf));
	pr_cont("%s", kernfs_pr_cont_buf);

	spin_unlock_irqrestore(&kernfs_नाम_lock, flags);
पूर्ण

/**
 * pr_cont_kernfs_path - pr_cont path of a kernfs_node
 * @kn: kernfs_node of पूर्णांकerest
 *
 * This function can be called from any context.
 */
व्योम pr_cont_kernfs_path(काष्ठा kernfs_node *kn)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक sz;

	spin_lock_irqsave(&kernfs_नाम_lock, flags);

	sz = kernfs_path_from_node_locked(kn, शून्य, kernfs_pr_cont_buf,
					  माप(kernfs_pr_cont_buf));
	अगर (sz < 0) अणु
		pr_cont("(error)");
		जाओ out;
	पूर्ण

	अगर (sz >= माप(kernfs_pr_cont_buf)) अणु
		pr_cont("(name too long)");
		जाओ out;
	पूर्ण

	pr_cont("%s", kernfs_pr_cont_buf);

out:
	spin_unlock_irqrestore(&kernfs_नाम_lock, flags);
पूर्ण

/**
 * kernfs_get_parent - determine the parent node and pin it
 * @kn: kernfs_node of पूर्णांकerest
 *
 * Determines @kn's parent, pins and वापसs it.  This function can be
 * called from any context.
 */
काष्ठा kernfs_node *kernfs_get_parent(काष्ठा kernfs_node *kn)
अणु
	काष्ठा kernfs_node *parent;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&kernfs_नाम_lock, flags);
	parent = kn->parent;
	kernfs_get(parent);
	spin_unlock_irqrestore(&kernfs_नाम_lock, flags);

	वापस parent;
पूर्ण

/**
 *	kernfs_name_hash
 *	@name: Null terminated string to hash
 *	@ns:   Namespace tag to hash
 *
 *	Returns 31 bit hash of ns + name (so it fits in an off_t )
 */
अटल अचिन्हित पूर्णांक kernfs_name_hash(स्थिर अक्षर *name, स्थिर व्योम *ns)
अणु
	अचिन्हित दीर्घ hash = init_name_hash(ns);
	अचिन्हित पूर्णांक len = म_माप(name);
	जबतक (len--)
		hash = partial_name_hash(*name++, hash);
	hash = end_name_hash(hash);
	hash &= 0x7fffffffU;
	/* Reserve hash numbers 0, 1 and पूर्णांक_उच्च क्रम magic directory entries */
	अगर (hash < 2)
		hash += 2;
	अगर (hash >= पूर्णांक_उच्च)
		hash = पूर्णांक_उच्च - 1;
	वापस hash;
पूर्ण

अटल पूर्णांक kernfs_name_compare(अचिन्हित पूर्णांक hash, स्थिर अक्षर *name,
			       स्थिर व्योम *ns, स्थिर काष्ठा kernfs_node *kn)
अणु
	अगर (hash < kn->hash)
		वापस -1;
	अगर (hash > kn->hash)
		वापस 1;
	अगर (ns < kn->ns)
		वापस -1;
	अगर (ns > kn->ns)
		वापस 1;
	वापस म_भेद(name, kn->name);
पूर्ण

अटल पूर्णांक kernfs_sd_compare(स्थिर काष्ठा kernfs_node *left,
			     स्थिर काष्ठा kernfs_node *right)
अणु
	वापस kernfs_name_compare(left->hash, left->name, left->ns, right);
पूर्ण

/**
 *	kernfs_link_sibling - link kernfs_node पूर्णांकo sibling rbtree
 *	@kn: kernfs_node of पूर्णांकerest
 *
 *	Link @kn पूर्णांकo its sibling rbtree which starts from
 *	@kn->parent->dir.children.
 *
 *	Locking:
 *	mutex_lock(kernfs_mutex)
 *
 *	RETURNS:
 *	0 on susccess -EEXIST on failure.
 */
अटल पूर्णांक kernfs_link_sibling(काष्ठा kernfs_node *kn)
अणु
	काष्ठा rb_node **node = &kn->parent->dir.children.rb_node;
	काष्ठा rb_node *parent = शून्य;

	जबतक (*node) अणु
		काष्ठा kernfs_node *pos;
		पूर्णांक result;

		pos = rb_to_kn(*node);
		parent = *node;
		result = kernfs_sd_compare(kn, pos);
		अगर (result < 0)
			node = &pos->rb.rb_left;
		अन्यथा अगर (result > 0)
			node = &pos->rb.rb_right;
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	/* add new node and rebalance the tree */
	rb_link_node(&kn->rb, parent, node);
	rb_insert_color(&kn->rb, &kn->parent->dir.children);

	/* successfully added, account subdir number */
	अगर (kernfs_type(kn) == KERNFS_सूची)
		kn->parent->dir.subdirs++;

	वापस 0;
पूर्ण

/**
 *	kernfs_unlink_sibling - unlink kernfs_node from sibling rbtree
 *	@kn: kernfs_node of पूर्णांकerest
 *
 *	Try to unlink @kn from its sibling rbtree which starts from
 *	kn->parent->dir.children.  Returns %true अगर @kn was actually
 *	हटाओd, %false अगर @kn wasn't on the rbtree.
 *
 *	Locking:
 *	mutex_lock(kernfs_mutex)
 */
अटल bool kernfs_unlink_sibling(काष्ठा kernfs_node *kn)
अणु
	अगर (RB_EMPTY_NODE(&kn->rb))
		वापस false;

	अगर (kernfs_type(kn) == KERNFS_सूची)
		kn->parent->dir.subdirs--;

	rb_erase(&kn->rb, &kn->parent->dir.children);
	RB_CLEAR_NODE(&kn->rb);
	वापस true;
पूर्ण

/**
 *	kernfs_get_active - get an active reference to kernfs_node
 *	@kn: kernfs_node to get an active reference to
 *
 *	Get an active reference of @kn.  This function is noop अगर @kn
 *	is शून्य.
 *
 *	RETURNS:
 *	Poपूर्णांकer to @kn on success, शून्य on failure.
 */
काष्ठा kernfs_node *kernfs_get_active(काष्ठा kernfs_node *kn)
अणु
	अगर (unlikely(!kn))
		वापस शून्य;

	अगर (!atomic_inc_unless_negative(&kn->active))
		वापस शून्य;

	अगर (kernfs_lockdep(kn))
		rwsem_acquire_पढ़ो(&kn->dep_map, 0, 1, _RET_IP_);
	वापस kn;
पूर्ण

/**
 *	kernfs_put_active - put an active reference to kernfs_node
 *	@kn: kernfs_node to put an active reference to
 *
 *	Put an active reference to @kn.  This function is noop अगर @kn
 *	is शून्य.
 */
व्योम kernfs_put_active(काष्ठा kernfs_node *kn)
अणु
	पूर्णांक v;

	अगर (unlikely(!kn))
		वापस;

	अगर (kernfs_lockdep(kn))
		rwsem_release(&kn->dep_map, _RET_IP_);
	v = atomic_dec_वापस(&kn->active);
	अगर (likely(v != KN_DEACTIVATED_BIAS))
		वापस;

	wake_up_all(&kernfs_root(kn)->deactivate_रुकोq);
पूर्ण

/**
 * kernfs_drain - drain kernfs_node
 * @kn: kernfs_node to drain
 *
 * Drain existing usages and nuke all existing mmaps of @kn.  Mutiple
 * हटाओrs may invoke this function concurrently on @kn and all will
 * वापस after draining is complete.
 */
अटल व्योम kernfs_drain(काष्ठा kernfs_node *kn)
	__releases(&kernfs_mutex) __acquires(&kernfs_mutex)
अणु
	काष्ठा kernfs_root *root = kernfs_root(kn);

	lockdep_निश्चित_held(&kernfs_mutex);
	WARN_ON_ONCE(kernfs_active(kn));

	mutex_unlock(&kernfs_mutex);

	अगर (kernfs_lockdep(kn)) अणु
		rwsem_acquire(&kn->dep_map, 0, 0, _RET_IP_);
		अगर (atomic_पढ़ो(&kn->active) != KN_DEACTIVATED_BIAS)
			lock_contended(&kn->dep_map, _RET_IP_);
	पूर्ण

	/* but everyone should रुको क्रम draining */
	रुको_event(root->deactivate_रुकोq,
		   atomic_पढ़ो(&kn->active) == KN_DEACTIVATED_BIAS);

	अगर (kernfs_lockdep(kn)) अणु
		lock_acquired(&kn->dep_map, _RET_IP_);
		rwsem_release(&kn->dep_map, _RET_IP_);
	पूर्ण

	kernfs_drain_खोलो_files(kn);

	mutex_lock(&kernfs_mutex);
पूर्ण

/**
 * kernfs_get - get a reference count on a kernfs_node
 * @kn: the target kernfs_node
 */
व्योम kernfs_get(काष्ठा kernfs_node *kn)
अणु
	अगर (kn) अणु
		WARN_ON(!atomic_पढ़ो(&kn->count));
		atomic_inc(&kn->count);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kernfs_get);

/**
 * kernfs_put - put a reference count on a kernfs_node
 * @kn: the target kernfs_node
 *
 * Put a reference count of @kn and destroy it अगर it reached zero.
 */
व्योम kernfs_put(काष्ठा kernfs_node *kn)
अणु
	काष्ठा kernfs_node *parent;
	काष्ठा kernfs_root *root;

	अगर (!kn || !atomic_dec_and_test(&kn->count))
		वापस;
	root = kernfs_root(kn);
 repeat:
	/*
	 * Moving/renaming is always करोne जबतक holding reference.
	 * kn->parent won't change beneath us.
	 */
	parent = kn->parent;

	WARN_ONCE(atomic_पढ़ो(&kn->active) != KN_DEACTIVATED_BIAS,
		  "kernfs_put: %s/%s: released with incorrect active_ref %d\n",
		  parent ? parent->name : "", kn->name, atomic_पढ़ो(&kn->active));

	अगर (kernfs_type(kn) == KERNFS_LINK)
		kernfs_put(kn->symlink.target_kn);

	kमुक्त_स्थिर(kn->name);

	अगर (kn->iattr) अणु
		simple_xattrs_मुक्त(&kn->iattr->xattrs);
		kmem_cache_मुक्त(kernfs_iattrs_cache, kn->iattr);
	पूर्ण
	spin_lock(&kernfs_idr_lock);
	idr_हटाओ(&root->ino_idr, (u32)kernfs_ino(kn));
	spin_unlock(&kernfs_idr_lock);
	kmem_cache_मुक्त(kernfs_node_cache, kn);

	kn = parent;
	अगर (kn) अणु
		अगर (atomic_dec_and_test(&kn->count))
			जाओ repeat;
	पूर्ण अन्यथा अणु
		/* just released the root kn, मुक्त @root too */
		idr_destroy(&root->ino_idr);
		kमुक्त(root);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(kernfs_put);

अटल पूर्णांक kernfs_करोp_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा kernfs_node *kn;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	/* Always perक्रमm fresh lookup क्रम negatives */
	अगर (d_really_is_negative(dentry))
		जाओ out_bad_unlocked;

	kn = kernfs_dentry_node(dentry);
	mutex_lock(&kernfs_mutex);

	/* The kernfs node has been deactivated */
	अगर (!kernfs_active(kn))
		जाओ out_bad;

	/* The kernfs node has been moved? */
	अगर (kernfs_dentry_node(dentry->d_parent) != kn->parent)
		जाओ out_bad;

	/* The kernfs node has been नामd */
	अगर (म_भेद(dentry->d_name.name, kn->name) != 0)
		जाओ out_bad;

	/* The kernfs node has been moved to a dअगरferent namespace */
	अगर (kn->parent && kernfs_ns_enabled(kn->parent) &&
	    kernfs_info(dentry->d_sb)->ns != kn->ns)
		जाओ out_bad;

	mutex_unlock(&kernfs_mutex);
	वापस 1;
out_bad:
	mutex_unlock(&kernfs_mutex);
out_bad_unlocked:
	वापस 0;
पूर्ण

स्थिर काष्ठा dentry_operations kernfs_करोps = अणु
	.d_revalidate	= kernfs_करोp_revalidate,
पूर्ण;

/**
 * kernfs_node_from_dentry - determine kernfs_node associated with a dentry
 * @dentry: the dentry in question
 *
 * Return the kernfs_node associated with @dentry.  If @dentry is not a
 * kernfs one, %शून्य is वापसed.
 *
 * While the वापसed kernfs_node will stay accessible as दीर्घ as @dentry
 * is accessible, the वापसed node can be in any state and the caller is
 * fully responsible क्रम determining what's accessible.
 */
काष्ठा kernfs_node *kernfs_node_from_dentry(काष्ठा dentry *dentry)
अणु
	अगर (dentry->d_sb->s_op == &kernfs_sops)
		वापस kernfs_dentry_node(dentry);
	वापस शून्य;
पूर्ण

अटल काष्ठा kernfs_node *__kernfs_new_node(काष्ठा kernfs_root *root,
					     काष्ठा kernfs_node *parent,
					     स्थिर अक्षर *name, umode_t mode,
					     kuid_t uid, kgid_t gid,
					     अचिन्हित flags)
अणु
	काष्ठा kernfs_node *kn;
	u32 id_highbits;
	पूर्णांक ret;

	name = kstrdup_स्थिर(name, GFP_KERNEL);
	अगर (!name)
		वापस शून्य;

	kn = kmem_cache_zalloc(kernfs_node_cache, GFP_KERNEL);
	अगर (!kn)
		जाओ err_out1;

	idr_preload(GFP_KERNEL);
	spin_lock(&kernfs_idr_lock);
	ret = idr_alloc_cyclic(&root->ino_idr, kn, 1, 0, GFP_ATOMIC);
	अगर (ret >= 0 && ret < root->last_id_lowbits)
		root->id_highbits++;
	id_highbits = root->id_highbits;
	root->last_id_lowbits = ret;
	spin_unlock(&kernfs_idr_lock);
	idr_preload_end();
	अगर (ret < 0)
		जाओ err_out2;

	kn->id = (u64)id_highbits << 32 | ret;

	atomic_set(&kn->count, 1);
	atomic_set(&kn->active, KN_DEACTIVATED_BIAS);
	RB_CLEAR_NODE(&kn->rb);

	kn->name = name;
	kn->mode = mode;
	kn->flags = flags;

	अगर (!uid_eq(uid, GLOBAL_ROOT_UID) || !gid_eq(gid, GLOBAL_ROOT_GID)) अणु
		काष्ठा iattr iattr = अणु
			.ia_valid = ATTR_UID | ATTR_GID,
			.ia_uid = uid,
			.ia_gid = gid,
		पूर्ण;

		ret = __kernfs_setattr(kn, &iattr);
		अगर (ret < 0)
			जाओ err_out3;
	पूर्ण

	अगर (parent) अणु
		ret = security_kernfs_init_security(parent, kn);
		अगर (ret)
			जाओ err_out3;
	पूर्ण

	वापस kn;

 err_out3:
	idr_हटाओ(&root->ino_idr, (u32)kernfs_ino(kn));
 err_out2:
	kmem_cache_मुक्त(kernfs_node_cache, kn);
 err_out1:
	kमुक्त_स्थिर(name);
	वापस शून्य;
पूर्ण

काष्ठा kernfs_node *kernfs_new_node(काष्ठा kernfs_node *parent,
				    स्थिर अक्षर *name, umode_t mode,
				    kuid_t uid, kgid_t gid,
				    अचिन्हित flags)
अणु
	काष्ठा kernfs_node *kn;

	kn = __kernfs_new_node(kernfs_root(parent), parent,
			       name, mode, uid, gid, flags);
	अगर (kn) अणु
		kernfs_get(parent);
		kn->parent = parent;
	पूर्ण
	वापस kn;
पूर्ण

/*
 * kernfs_find_and_get_node_by_id - get kernfs_node from node id
 * @root: the kernfs root
 * @id: the target node id
 *
 * @id's lower 32bits encode ino and upper gen.  If the gen portion is
 * zero, all generations are matched.
 *
 * RETURNS:
 * शून्य on failure. Return a kernfs node with reference counter incremented
 */
काष्ठा kernfs_node *kernfs_find_and_get_node_by_id(काष्ठा kernfs_root *root,
						   u64 id)
अणु
	काष्ठा kernfs_node *kn;
	ino_t ino = kernfs_id_ino(id);
	u32 gen = kernfs_id_gen(id);

	spin_lock(&kernfs_idr_lock);

	kn = idr_find(&root->ino_idr, (u32)ino);
	अगर (!kn)
		जाओ err_unlock;

	अगर (माप(ino_t) >= माप(u64)) अणु
		/* we looked up with the low 32bits, compare the whole */
		अगर (kernfs_ino(kn) != ino)
			जाओ err_unlock;
	पूर्ण अन्यथा अणु
		/* 0 matches all generations */
		अगर (unlikely(gen && kernfs_gen(kn) != gen))
			जाओ err_unlock;
	पूर्ण

	/*
	 * ACTIVATED is रक्षित with kernfs_mutex but it was clear when
	 * @kn was added to idr and we just wanna see it set.  No need to
	 * grab kernfs_mutex.
	 */
	अगर (unlikely(!(kn->flags & KERNFS_ACTIVATED) ||
		     !atomic_inc_not_zero(&kn->count)))
		जाओ err_unlock;

	spin_unlock(&kernfs_idr_lock);
	वापस kn;
err_unlock:
	spin_unlock(&kernfs_idr_lock);
	वापस शून्य;
पूर्ण

/**
 *	kernfs_add_one - add kernfs_node to parent without warning
 *	@kn: kernfs_node to be added
 *
 *	The caller must alपढ़ोy have initialized @kn->parent.  This
 *	function increments nlink of the parent's inode अगर @kn is a
 *	directory and link पूर्णांकo the children list of the parent.
 *
 *	RETURNS:
 *	0 on success, -EEXIST अगर entry with the given name alपढ़ोy
 *	exists.
 */
पूर्णांक kernfs_add_one(काष्ठा kernfs_node *kn)
अणु
	काष्ठा kernfs_node *parent = kn->parent;
	काष्ठा kernfs_iattrs *ps_iattr;
	bool has_ns;
	पूर्णांक ret;

	mutex_lock(&kernfs_mutex);

	ret = -EINVAL;
	has_ns = kernfs_ns_enabled(parent);
	अगर (WARN(has_ns != (bool)kn->ns, KERN_WARNING "kernfs: ns %s in '%s' for '%s'\n",
		 has_ns ? "required" : "invalid", parent->name, kn->name))
		जाओ out_unlock;

	अगर (kernfs_type(parent) != KERNFS_सूची)
		जाओ out_unlock;

	ret = -ENOENT;
	अगर (parent->flags & KERNFS_EMPTY_सूची)
		जाओ out_unlock;

	अगर ((parent->flags & KERNFS_ACTIVATED) && !kernfs_active(parent))
		जाओ out_unlock;

	kn->hash = kernfs_name_hash(kn->name, kn->ns);

	ret = kernfs_link_sibling(kn);
	अगर (ret)
		जाओ out_unlock;

	/* Update बारtamps on the parent */
	ps_iattr = parent->iattr;
	अगर (ps_iattr) अणु
		kसमय_get_real_ts64(&ps_iattr->ia_स_समय);
		ps_iattr->ia_mसमय = ps_iattr->ia_स_समय;
	पूर्ण

	mutex_unlock(&kernfs_mutex);

	/*
	 * Activate the new node unless CREATE_DEACTIVATED is requested.
	 * If not activated here, the kernfs user is responsible क्रम
	 * activating the node with kernfs_activate().  A node which hasn't
	 * been activated is not visible to userland and its removal won't
	 * trigger deactivation.
	 */
	अगर (!(kernfs_root(kn)->flags & KERNFS_ROOT_CREATE_DEACTIVATED))
		kernfs_activate(kn);
	वापस 0;

out_unlock:
	mutex_unlock(&kernfs_mutex);
	वापस ret;
पूर्ण

/**
 * kernfs_find_ns - find kernfs_node with the given name
 * @parent: kernfs_node to search under
 * @name: name to look क्रम
 * @ns: the namespace tag to use
 *
 * Look क्रम kernfs_node with name @name under @parent.  Returns poपूर्णांकer to
 * the found kernfs_node on success, %शून्य on failure.
 */
अटल काष्ठा kernfs_node *kernfs_find_ns(काष्ठा kernfs_node *parent,
					  स्थिर अचिन्हित अक्षर *name,
					  स्थिर व्योम *ns)
अणु
	काष्ठा rb_node *node = parent->dir.children.rb_node;
	bool has_ns = kernfs_ns_enabled(parent);
	अचिन्हित पूर्णांक hash;

	lockdep_निश्चित_held(&kernfs_mutex);

	अगर (has_ns != (bool)ns) अणु
		WARN(1, KERN_WARNING "kernfs: ns %s in '%s' for '%s'\n",
		     has_ns ? "required" : "invalid", parent->name, name);
		वापस शून्य;
	पूर्ण

	hash = kernfs_name_hash(name, ns);
	जबतक (node) अणु
		काष्ठा kernfs_node *kn;
		पूर्णांक result;

		kn = rb_to_kn(node);
		result = kernfs_name_compare(hash, name, ns, kn);
		अगर (result < 0)
			node = node->rb_left;
		अन्यथा अगर (result > 0)
			node = node->rb_right;
		अन्यथा
			वापस kn;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा kernfs_node *kernfs_walk_ns(काष्ठा kernfs_node *parent,
					  स्थिर अचिन्हित अक्षर *path,
					  स्थिर व्योम *ns)
अणु
	माप_प्रकार len;
	अक्षर *p, *name;

	lockdep_निश्चित_held(&kernfs_mutex);

	/* grab kernfs_नाम_lock to piggy back on kernfs_pr_cont_buf */
	spin_lock_irq(&kernfs_नाम_lock);

	len = strlcpy(kernfs_pr_cont_buf, path, माप(kernfs_pr_cont_buf));

	अगर (len >= माप(kernfs_pr_cont_buf)) अणु
		spin_unlock_irq(&kernfs_नाम_lock);
		वापस शून्य;
	पूर्ण

	p = kernfs_pr_cont_buf;

	जबतक ((name = strsep(&p, "/")) && parent) अणु
		अगर (*name == '\0')
			जारी;
		parent = kernfs_find_ns(parent, name, ns);
	पूर्ण

	spin_unlock_irq(&kernfs_नाम_lock);

	वापस parent;
पूर्ण

/**
 * kernfs_find_and_get_ns - find and get kernfs_node with the given name
 * @parent: kernfs_node to search under
 * @name: name to look क्रम
 * @ns: the namespace tag to use
 *
 * Look क्रम kernfs_node with name @name under @parent and get a reference
 * अगर found.  This function may sleep and वापसs poपूर्णांकer to the found
 * kernfs_node on success, %शून्य on failure.
 */
काष्ठा kernfs_node *kernfs_find_and_get_ns(काष्ठा kernfs_node *parent,
					   स्थिर अक्षर *name, स्थिर व्योम *ns)
अणु
	काष्ठा kernfs_node *kn;

	mutex_lock(&kernfs_mutex);
	kn = kernfs_find_ns(parent, name, ns);
	kernfs_get(kn);
	mutex_unlock(&kernfs_mutex);

	वापस kn;
पूर्ण
EXPORT_SYMBOL_GPL(kernfs_find_and_get_ns);

/**
 * kernfs_walk_and_get_ns - find and get kernfs_node with the given path
 * @parent: kernfs_node to search under
 * @path: path to look क्रम
 * @ns: the namespace tag to use
 *
 * Look क्रम kernfs_node with path @path under @parent and get a reference
 * अगर found.  This function may sleep and वापसs poपूर्णांकer to the found
 * kernfs_node on success, %शून्य on failure.
 */
काष्ठा kernfs_node *kernfs_walk_and_get_ns(काष्ठा kernfs_node *parent,
					   स्थिर अक्षर *path, स्थिर व्योम *ns)
अणु
	काष्ठा kernfs_node *kn;

	mutex_lock(&kernfs_mutex);
	kn = kernfs_walk_ns(parent, path, ns);
	kernfs_get(kn);
	mutex_unlock(&kernfs_mutex);

	वापस kn;
पूर्ण

/**
 * kernfs_create_root - create a new kernfs hierarchy
 * @scops: optional syscall operations क्रम the hierarchy
 * @flags: KERNFS_ROOT_* flags
 * @priv: opaque data associated with the new directory
 *
 * Returns the root of the new hierarchy on success, ERR_PTR() value on
 * failure.
 */
काष्ठा kernfs_root *kernfs_create_root(काष्ठा kernfs_syscall_ops *scops,
				       अचिन्हित पूर्णांक flags, व्योम *priv)
अणु
	काष्ठा kernfs_root *root;
	काष्ठा kernfs_node *kn;

	root = kzalloc(माप(*root), GFP_KERNEL);
	अगर (!root)
		वापस ERR_PTR(-ENOMEM);

	idr_init(&root->ino_idr);
	INIT_LIST_HEAD(&root->supers);

	/*
	 * On 64bit ino setups, id is ino.  On 32bit, low 32bits are ino.
	 * High bits generation.  The starting value क्रम both ino and
	 * genenration is 1.  Initialize upper 32bit allocation
	 * accordingly.
	 */
	अगर (माप(ino_t) >= माप(u64))
		root->id_highbits = 0;
	अन्यथा
		root->id_highbits = 1;

	kn = __kernfs_new_node(root, शून्य, "", S_IFसूची | S_IRUGO | S_IXUGO,
			       GLOBAL_ROOT_UID, GLOBAL_ROOT_GID,
			       KERNFS_सूची);
	अगर (!kn) अणु
		idr_destroy(&root->ino_idr);
		kमुक्त(root);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	kn->priv = priv;
	kn->dir.root = root;

	root->syscall_ops = scops;
	root->flags = flags;
	root->kn = kn;
	init_रुकोqueue_head(&root->deactivate_रुकोq);

	अगर (!(root->flags & KERNFS_ROOT_CREATE_DEACTIVATED))
		kernfs_activate(kn);

	वापस root;
पूर्ण

/**
 * kernfs_destroy_root - destroy a kernfs hierarchy
 * @root: root of the hierarchy to destroy
 *
 * Destroy the hierarchy anchored at @root by removing all existing
 * directories and destroying @root.
 */
व्योम kernfs_destroy_root(काष्ठा kernfs_root *root)
अणु
	kernfs_हटाओ(root->kn);	/* will also मुक्त @root */
पूर्ण

/**
 * kernfs_create_dir_ns - create a directory
 * @parent: parent in which to create a new directory
 * @name: name of the new directory
 * @mode: mode of the new directory
 * @uid: uid of the new directory
 * @gid: gid of the new directory
 * @priv: opaque data associated with the new directory
 * @ns: optional namespace tag of the directory
 *
 * Returns the created node on success, ERR_PTR() value on failure.
 */
काष्ठा kernfs_node *kernfs_create_dir_ns(काष्ठा kernfs_node *parent,
					 स्थिर अक्षर *name, umode_t mode,
					 kuid_t uid, kgid_t gid,
					 व्योम *priv, स्थिर व्योम *ns)
अणु
	काष्ठा kernfs_node *kn;
	पूर्णांक rc;

	/* allocate */
	kn = kernfs_new_node(parent, name, mode | S_IFसूची,
			     uid, gid, KERNFS_सूची);
	अगर (!kn)
		वापस ERR_PTR(-ENOMEM);

	kn->dir.root = parent->dir.root;
	kn->ns = ns;
	kn->priv = priv;

	/* link in */
	rc = kernfs_add_one(kn);
	अगर (!rc)
		वापस kn;

	kernfs_put(kn);
	वापस ERR_PTR(rc);
पूर्ण

/**
 * kernfs_create_empty_dir - create an always empty directory
 * @parent: parent in which to create a new directory
 * @name: name of the new directory
 *
 * Returns the created node on success, ERR_PTR() value on failure.
 */
काष्ठा kernfs_node *kernfs_create_empty_dir(काष्ठा kernfs_node *parent,
					    स्थिर अक्षर *name)
अणु
	काष्ठा kernfs_node *kn;
	पूर्णांक rc;

	/* allocate */
	kn = kernfs_new_node(parent, name, S_IRUGO|S_IXUGO|S_IFसूची,
			     GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, KERNFS_सूची);
	अगर (!kn)
		वापस ERR_PTR(-ENOMEM);

	kn->flags |= KERNFS_EMPTY_सूची;
	kn->dir.root = parent->dir.root;
	kn->ns = शून्य;
	kn->priv = शून्य;

	/* link in */
	rc = kernfs_add_one(kn);
	अगर (!rc)
		वापस kn;

	kernfs_put(kn);
	वापस ERR_PTR(rc);
पूर्ण

अटल काष्ठा dentry *kernfs_iop_lookup(काष्ठा inode *dir,
					काष्ठा dentry *dentry,
					अचिन्हित पूर्णांक flags)
अणु
	काष्ठा dentry *ret;
	काष्ठा kernfs_node *parent = dir->i_निजी;
	काष्ठा kernfs_node *kn;
	काष्ठा inode *inode;
	स्थिर व्योम *ns = शून्य;

	mutex_lock(&kernfs_mutex);

	अगर (kernfs_ns_enabled(parent))
		ns = kernfs_info(dir->i_sb)->ns;

	kn = kernfs_find_ns(parent, dentry->d_name.name, ns);

	/* no such entry */
	अगर (!kn || !kernfs_active(kn)) अणु
		ret = शून्य;
		जाओ out_unlock;
	पूर्ण

	/* attach dentry and inode */
	inode = kernfs_get_inode(dir->i_sb, kn);
	अगर (!inode) अणु
		ret = ERR_PTR(-ENOMEM);
		जाओ out_unlock;
	पूर्ण

	/* instantiate and hash dentry */
	ret = d_splice_alias(inode, dentry);
 out_unlock:
	mutex_unlock(&kernfs_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक kernfs_iop_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *dir, काष्ठा dentry *dentry,
			    umode_t mode)
अणु
	काष्ठा kernfs_node *parent = dir->i_निजी;
	काष्ठा kernfs_syscall_ops *scops = kernfs_root(parent)->syscall_ops;
	पूर्णांक ret;

	अगर (!scops || !scops->सूची_गढ़ो)
		वापस -EPERM;

	अगर (!kernfs_get_active(parent))
		वापस -ENODEV;

	ret = scops->सूची_गढ़ो(parent, dentry->d_name.name, mode);

	kernfs_put_active(parent);
	वापस ret;
पूर्ण

अटल पूर्णांक kernfs_iop_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा kernfs_node *kn  = kernfs_dentry_node(dentry);
	काष्ठा kernfs_syscall_ops *scops = kernfs_root(kn)->syscall_ops;
	पूर्णांक ret;

	अगर (!scops || !scops->सूची_हटाओ)
		वापस -EPERM;

	अगर (!kernfs_get_active(kn))
		वापस -ENODEV;

	ret = scops->सूची_हटाओ(kn);

	kernfs_put_active(kn);
	वापस ret;
पूर्ण

अटल पूर्णांक kernfs_iop_नाम(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			     काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा kernfs_node *kn = kernfs_dentry_node(old_dentry);
	काष्ठा kernfs_node *new_parent = new_dir->i_निजी;
	काष्ठा kernfs_syscall_ops *scops = kernfs_root(kn)->syscall_ops;
	पूर्णांक ret;

	अगर (flags)
		वापस -EINVAL;

	अगर (!scops || !scops->नाम)
		वापस -EPERM;

	अगर (!kernfs_get_active(kn))
		वापस -ENODEV;

	अगर (!kernfs_get_active(new_parent)) अणु
		kernfs_put_active(kn);
		वापस -ENODEV;
	पूर्ण

	ret = scops->नाम(kn, new_parent, new_dentry->d_name.name);

	kernfs_put_active(new_parent);
	kernfs_put_active(kn);
	वापस ret;
पूर्ण

स्थिर काष्ठा inode_operations kernfs_dir_iops = अणु
	.lookup		= kernfs_iop_lookup,
	.permission	= kernfs_iop_permission,
	.setattr	= kernfs_iop_setattr,
	.getattr	= kernfs_iop_getattr,
	.listxattr	= kernfs_iop_listxattr,

	.सूची_गढ़ो		= kernfs_iop_सूची_गढ़ो,
	.सूची_हटाओ		= kernfs_iop_सूची_हटाओ,
	.नाम		= kernfs_iop_नाम,
पूर्ण;

अटल काष्ठा kernfs_node *kernfs_lefपंचांगost_descendant(काष्ठा kernfs_node *pos)
अणु
	काष्ठा kernfs_node *last;

	जबतक (true) अणु
		काष्ठा rb_node *rbn;

		last = pos;

		अगर (kernfs_type(pos) != KERNFS_सूची)
			अवरोध;

		rbn = rb_first(&pos->dir.children);
		अगर (!rbn)
			अवरोध;

		pos = rb_to_kn(rbn);
	पूर्ण

	वापस last;
पूर्ण

/**
 * kernfs_next_descendant_post - find the next descendant क्रम post-order walk
 * @pos: the current position (%शून्य to initiate traversal)
 * @root: kernfs_node whose descendants to walk
 *
 * Find the next descendant to visit क्रम post-order traversal of @root's
 * descendants.  @root is included in the iteration and the last node to be
 * visited.
 */
अटल काष्ठा kernfs_node *kernfs_next_descendant_post(काष्ठा kernfs_node *pos,
						       काष्ठा kernfs_node *root)
अणु
	काष्ठा rb_node *rbn;

	lockdep_निश्चित_held(&kernfs_mutex);

	/* अगर first iteration, visit lefपंचांगost descendant which may be root */
	अगर (!pos)
		वापस kernfs_lefपंचांगost_descendant(root);

	/* अगर we visited @root, we're करोne */
	अगर (pos == root)
		वापस शून्य;

	/* अगर there's an unvisited sibling, visit its lefपंचांगost descendant */
	rbn = rb_next(&pos->rb);
	अगर (rbn)
		वापस kernfs_lefपंचांगost_descendant(rb_to_kn(rbn));

	/* no sibling left, visit parent */
	वापस pos->parent;
पूर्ण

/**
 * kernfs_activate - activate a node which started deactivated
 * @kn: kernfs_node whose subtree is to be activated
 *
 * If the root has KERNFS_ROOT_CREATE_DEACTIVATED set, a newly created node
 * needs to be explicitly activated.  A node which hasn't been activated
 * isn't visible to userland and deactivation is skipped during its
 * removal.  This is useful to स्थिरruct atomic init sequences where
 * creation of multiple nodes should either succeed or fail atomically.
 *
 * The caller is responsible क्रम ensuring that this function is not called
 * after kernfs_हटाओ*() is invoked on @kn.
 */
व्योम kernfs_activate(काष्ठा kernfs_node *kn)
अणु
	काष्ठा kernfs_node *pos;

	mutex_lock(&kernfs_mutex);

	pos = शून्य;
	जबतक ((pos = kernfs_next_descendant_post(pos, kn))) अणु
		अगर (pos->flags & KERNFS_ACTIVATED)
			जारी;

		WARN_ON_ONCE(pos->parent && RB_EMPTY_NODE(&pos->rb));
		WARN_ON_ONCE(atomic_पढ़ो(&pos->active) != KN_DEACTIVATED_BIAS);

		atomic_sub(KN_DEACTIVATED_BIAS, &pos->active);
		pos->flags |= KERNFS_ACTIVATED;
	पूर्ण

	mutex_unlock(&kernfs_mutex);
पूर्ण

अटल व्योम __kernfs_हटाओ(काष्ठा kernfs_node *kn)
अणु
	काष्ठा kernfs_node *pos;

	lockdep_निश्चित_held(&kernfs_mutex);

	/*
	 * Short-circuit अगर non-root @kn has alपढ़ोy finished removal.
	 * This is क्रम kernfs_हटाओ_self() which plays with active ref
	 * after removal.
	 */
	अगर (!kn || (kn->parent && RB_EMPTY_NODE(&kn->rb)))
		वापस;

	pr_debug("kernfs %s: removing\n", kn->name);

	/* prevent any new usage under @kn by deactivating all nodes */
	pos = शून्य;
	जबतक ((pos = kernfs_next_descendant_post(pos, kn)))
		अगर (kernfs_active(pos))
			atomic_add(KN_DEACTIVATED_BIAS, &pos->active);

	/* deactivate and unlink the subtree node-by-node */
	करो अणु
		pos = kernfs_lefपंचांगost_descendant(kn);

		/*
		 * kernfs_drain() drops kernfs_mutex temporarily and @pos's
		 * base ref could have been put by someone अन्यथा by the समय
		 * the function वापसs.  Make sure it करोesn't go away
		 * underneath us.
		 */
		kernfs_get(pos);

		/*
		 * Drain अगरf @kn was activated.  This aव्योमs draining and
		 * its lockdep annotations क्रम nodes which have never been
		 * activated and allows embedding kernfs_हटाओ() in create
		 * error paths without worrying about draining.
		 */
		अगर (kn->flags & KERNFS_ACTIVATED)
			kernfs_drain(pos);
		अन्यथा
			WARN_ON_ONCE(atomic_पढ़ो(&kn->active) != KN_DEACTIVATED_BIAS);

		/*
		 * kernfs_unlink_sibling() succeeds once per node.  Use it
		 * to decide who's responsible क्रम cleanups.
		 */
		अगर (!pos->parent || kernfs_unlink_sibling(pos)) अणु
			काष्ठा kernfs_iattrs *ps_iattr =
				pos->parent ? pos->parent->iattr : शून्य;

			/* update बारtamps on the parent */
			अगर (ps_iattr) अणु
				kसमय_get_real_ts64(&ps_iattr->ia_स_समय);
				ps_iattr->ia_mसमय = ps_iattr->ia_स_समय;
			पूर्ण

			kernfs_put(pos);
		पूर्ण

		kernfs_put(pos);
	पूर्ण जबतक (pos != kn);
पूर्ण

/**
 * kernfs_हटाओ - हटाओ a kernfs_node recursively
 * @kn: the kernfs_node to हटाओ
 *
 * Remove @kn aदीर्घ with all its subdirectories and files.
 */
व्योम kernfs_हटाओ(काष्ठा kernfs_node *kn)
अणु
	mutex_lock(&kernfs_mutex);
	__kernfs_हटाओ(kn);
	mutex_unlock(&kernfs_mutex);
पूर्ण

/**
 * kernfs_अवरोध_active_protection - अवरोध out of active protection
 * @kn: the self kernfs_node
 *
 * The caller must be running off of a kernfs operation which is invoked
 * with an active reference - e.g. one of kernfs_ops.  Each invocation of
 * this function must also be matched with an invocation of
 * kernfs_unअवरोध_active_protection().
 *
 * This function releases the active reference of @kn the caller is
 * holding.  Once this function is called, @kn may be हटाओd at any poपूर्णांक
 * and the caller is solely responsible क्रम ensuring that the objects it
 * dereferences are accessible.
 */
व्योम kernfs_अवरोध_active_protection(काष्ठा kernfs_node *kn)
अणु
	/*
	 * Take out ourself out of the active ref dependency chain.  If
	 * we're called without an active ref, lockdep will complain.
	 */
	kernfs_put_active(kn);
पूर्ण

/**
 * kernfs_unअवरोध_active_protection - unकरो kernfs_अवरोध_active_protection()
 * @kn: the self kernfs_node
 *
 * If kernfs_अवरोध_active_protection() was called, this function must be
 * invoked beक्रमe finishing the kernfs operation.  Note that जबतक this
 * function restores the active reference, it करोesn't and can't actually
 * restore the active protection - @kn may alपढ़ोy or be in the process of
 * being हटाओd.  Once kernfs_अवरोध_active_protection() is invoked, that
 * protection is irreversibly gone क्रम the kernfs operation instance.
 *
 * While this function may be called at any poपूर्णांक after
 * kernfs_अवरोध_active_protection() is invoked, its most useful location
 * would be right beक्रमe the enclosing kernfs operation वापसs.
 */
व्योम kernfs_unअवरोध_active_protection(काष्ठा kernfs_node *kn)
अणु
	/*
	 * @kn->active could be in any state; however, the increment we करो
	 * here will be unकरोne as soon as the enclosing kernfs operation
	 * finishes and this temporary bump can't अवरोध anything.  If @kn
	 * is alive, nothing changes.  If @kn is being deactivated, the
	 * soon-to-follow put will either finish deactivation or restore
	 * deactivated state.  If @kn is alपढ़ोy हटाओd, the temporary
	 * bump is guaranteed to be gone beक्रमe @kn is released.
	 */
	atomic_inc(&kn->active);
	अगर (kernfs_lockdep(kn))
		rwsem_acquire(&kn->dep_map, 0, 1, _RET_IP_);
पूर्ण

/**
 * kernfs_हटाओ_self - हटाओ a kernfs_node from its own method
 * @kn: the self kernfs_node to हटाओ
 *
 * The caller must be running off of a kernfs operation which is invoked
 * with an active reference - e.g. one of kernfs_ops.  This can be used to
 * implement a file operation which deletes itself.
 *
 * For example, the "delete" file क्रम a sysfs device directory can be
 * implemented by invoking kernfs_हटाओ_self() on the "delete" file
 * itself.  This function अवरोधs the circular dependency of trying to
 * deactivate self जबतक holding an active ref itself.  It isn't necessary
 * to modअगरy the usual removal path to use kernfs_हटाओ_self().  The
 * "delete" implementation can simply invoke kernfs_हटाओ_self() on self
 * beक्रमe proceeding with the usual removal path.  kernfs will ignore later
 * kernfs_हटाओ() on self.
 *
 * kernfs_हटाओ_self() can be called multiple बार concurrently on the
 * same kernfs_node.  Only the first one actually perक्रमms removal and
 * वापसs %true.  All others will रुको until the kernfs operation which
 * won self-removal finishes and वापस %false.  Note that the losers रुको
 * क्रम the completion of not only the winning kernfs_हटाओ_self() but also
 * the whole kernfs_ops which won the arbitration.  This can be used to
 * guarantee, क्रम example, all concurrent ग_लिखोs to a "delete" file to
 * finish only after the whole operation is complete.
 */
bool kernfs_हटाओ_self(काष्ठा kernfs_node *kn)
अणु
	bool ret;

	mutex_lock(&kernfs_mutex);
	kernfs_अवरोध_active_protection(kn);

	/*
	 * SUICIDAL is used to arbitrate among competing invocations.  Only
	 * the first one will actually perक्रमm removal.  When the removal
	 * is complete, SUICIDED is set and the active ref is restored
	 * जबतक holding kernfs_mutex.  The ones which lost arbitration
	 * रुकोs क्रम SUICDED && drained which can happen only after the
	 * enclosing kernfs operation which executed the winning instance
	 * of kernfs_हटाओ_self() finished.
	 */
	अगर (!(kn->flags & KERNFS_SUICIDAL)) अणु
		kn->flags |= KERNFS_SUICIDAL;
		__kernfs_हटाओ(kn);
		kn->flags |= KERNFS_SUICIDED;
		ret = true;
	पूर्ण अन्यथा अणु
		रुको_queue_head_t *रुकोq = &kernfs_root(kn)->deactivate_रुकोq;
		DEFINE_WAIT(रुको);

		जबतक (true) अणु
			prepare_to_रुको(रुकोq, &रुको, TASK_UNINTERRUPTIBLE);

			अगर ((kn->flags & KERNFS_SUICIDED) &&
			    atomic_पढ़ो(&kn->active) == KN_DEACTIVATED_BIAS)
				अवरोध;

			mutex_unlock(&kernfs_mutex);
			schedule();
			mutex_lock(&kernfs_mutex);
		पूर्ण
		finish_रुको(रुकोq, &रुको);
		WARN_ON_ONCE(!RB_EMPTY_NODE(&kn->rb));
		ret = false;
	पूर्ण

	/*
	 * This must be करोne जबतक holding kernfs_mutex; otherwise, रुकोing
	 * क्रम SUICIDED && deactivated could finish prematurely.
	 */
	kernfs_unअवरोध_active_protection(kn);

	mutex_unlock(&kernfs_mutex);
	वापस ret;
पूर्ण

/**
 * kernfs_हटाओ_by_name_ns - find a kernfs_node by name and हटाओ it
 * @parent: parent of the target
 * @name: name of the kernfs_node to हटाओ
 * @ns: namespace tag of the kernfs_node to हटाओ
 *
 * Look क्रम the kernfs_node with @name and @ns under @parent and हटाओ it.
 * Returns 0 on success, -ENOENT अगर such entry करोesn't exist.
 */
पूर्णांक kernfs_हटाओ_by_name_ns(काष्ठा kernfs_node *parent, स्थिर अक्षर *name,
			     स्थिर व्योम *ns)
अणु
	काष्ठा kernfs_node *kn;

	अगर (!parent) अणु
		WARN(1, KERN_WARNING "kernfs: can not remove '%s', no directory\n",
			name);
		वापस -ENOENT;
	पूर्ण

	mutex_lock(&kernfs_mutex);

	kn = kernfs_find_ns(parent, name, ns);
	अगर (kn)
		__kernfs_हटाओ(kn);

	mutex_unlock(&kernfs_mutex);

	अगर (kn)
		वापस 0;
	अन्यथा
		वापस -ENOENT;
पूर्ण

/**
 * kernfs_नाम_ns - move and नाम a kernfs_node
 * @kn: target node
 * @new_parent: new parent to put @sd under
 * @new_name: new name
 * @new_ns: new namespace tag
 */
पूर्णांक kernfs_नाम_ns(काष्ठा kernfs_node *kn, काष्ठा kernfs_node *new_parent,
		     स्थिर अक्षर *new_name, स्थिर व्योम *new_ns)
अणु
	काष्ठा kernfs_node *old_parent;
	स्थिर अक्षर *old_name = शून्य;
	पूर्णांक error;

	/* can't move or नाम root */
	अगर (!kn->parent)
		वापस -EINVAL;

	mutex_lock(&kernfs_mutex);

	error = -ENOENT;
	अगर (!kernfs_active(kn) || !kernfs_active(new_parent) ||
	    (new_parent->flags & KERNFS_EMPTY_सूची))
		जाओ out;

	error = 0;
	अगर ((kn->parent == new_parent) && (kn->ns == new_ns) &&
	    (म_भेद(kn->name, new_name) == 0))
		जाओ out;	/* nothing to नाम */

	error = -EEXIST;
	अगर (kernfs_find_ns(new_parent, new_name, new_ns))
		जाओ out;

	/* नाम kernfs_node */
	अगर (म_भेद(kn->name, new_name) != 0) अणु
		error = -ENOMEM;
		new_name = kstrdup_स्थिर(new_name, GFP_KERNEL);
		अगर (!new_name)
			जाओ out;
	पूर्ण अन्यथा अणु
		new_name = शून्य;
	पूर्ण

	/*
	 * Move to the appropriate place in the appropriate directories rbtree.
	 */
	kernfs_unlink_sibling(kn);
	kernfs_get(new_parent);

	/* नाम_lock protects ->parent and ->name accessors */
	spin_lock_irq(&kernfs_नाम_lock);

	old_parent = kn->parent;
	kn->parent = new_parent;

	kn->ns = new_ns;
	अगर (new_name) अणु
		old_name = kn->name;
		kn->name = new_name;
	पूर्ण

	spin_unlock_irq(&kernfs_नाम_lock);

	kn->hash = kernfs_name_hash(kn->name, kn->ns);
	kernfs_link_sibling(kn);

	kernfs_put(old_parent);
	kमुक्त_स्थिर(old_name);

	error = 0;
 out:
	mutex_unlock(&kernfs_mutex);
	वापस error;
पूर्ण

/* Relationship between mode and the DT_xxx types */
अटल अंतरभूत अचिन्हित अक्षर dt_type(काष्ठा kernfs_node *kn)
अणु
	वापस (kn->mode >> 12) & 15;
पूर्ण

अटल पूर्णांक kernfs_dir_fop_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	kernfs_put(filp->निजी_data);
	वापस 0;
पूर्ण

अटल काष्ठा kernfs_node *kernfs_dir_pos(स्थिर व्योम *ns,
	काष्ठा kernfs_node *parent, loff_t hash, काष्ठा kernfs_node *pos)
अणु
	अगर (pos) अणु
		पूर्णांक valid = kernfs_active(pos) &&
			pos->parent == parent && hash == pos->hash;
		kernfs_put(pos);
		अगर (!valid)
			pos = शून्य;
	पूर्ण
	अगर (!pos && (hash > 1) && (hash < पूर्णांक_उच्च)) अणु
		काष्ठा rb_node *node = parent->dir.children.rb_node;
		जबतक (node) अणु
			pos = rb_to_kn(node);

			अगर (hash < pos->hash)
				node = node->rb_left;
			अन्यथा अगर (hash > pos->hash)
				node = node->rb_right;
			अन्यथा
				अवरोध;
		पूर्ण
	पूर्ण
	/* Skip over entries which are dying/dead or in the wrong namespace */
	जबतक (pos && (!kernfs_active(pos) || pos->ns != ns)) अणु
		काष्ठा rb_node *node = rb_next(&pos->rb);
		अगर (!node)
			pos = शून्य;
		अन्यथा
			pos = rb_to_kn(node);
	पूर्ण
	वापस pos;
पूर्ण

अटल काष्ठा kernfs_node *kernfs_dir_next_pos(स्थिर व्योम *ns,
	काष्ठा kernfs_node *parent, ino_t ino, काष्ठा kernfs_node *pos)
अणु
	pos = kernfs_dir_pos(ns, parent, ino, pos);
	अगर (pos) अणु
		करो अणु
			काष्ठा rb_node *node = rb_next(&pos->rb);
			अगर (!node)
				pos = शून्य;
			अन्यथा
				pos = rb_to_kn(node);
		पूर्ण जबतक (pos && (!kernfs_active(pos) || pos->ns != ns));
	पूर्ण
	वापस pos;
पूर्ण

अटल पूर्णांक kernfs_fop_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा kernfs_node *parent = kernfs_dentry_node(dentry);
	काष्ठा kernfs_node *pos = file->निजी_data;
	स्थिर व्योम *ns = शून्य;

	अगर (!dir_emit_करोts(file, ctx))
		वापस 0;
	mutex_lock(&kernfs_mutex);

	अगर (kernfs_ns_enabled(parent))
		ns = kernfs_info(dentry->d_sb)->ns;

	क्रम (pos = kernfs_dir_pos(ns, parent, ctx->pos, pos);
	     pos;
	     pos = kernfs_dir_next_pos(ns, parent, ctx->pos, pos)) अणु
		स्थिर अक्षर *name = pos->name;
		अचिन्हित पूर्णांक type = dt_type(pos);
		पूर्णांक len = म_माप(name);
		ino_t ino = kernfs_ino(pos);

		ctx->pos = pos->hash;
		file->निजी_data = pos;
		kernfs_get(pos);

		mutex_unlock(&kernfs_mutex);
		अगर (!dir_emit(ctx, name, len, ino, type))
			वापस 0;
		mutex_lock(&kernfs_mutex);
	पूर्ण
	mutex_unlock(&kernfs_mutex);
	file->निजी_data = शून्य;
	ctx->pos = पूर्णांक_उच्च;
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations kernfs_dir_fops = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= kernfs_fop_सूची_पढ़ो,
	.release	= kernfs_dir_fop_release,
	.llseek		= generic_file_llseek,
पूर्ण;
