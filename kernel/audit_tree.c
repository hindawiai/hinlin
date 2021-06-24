<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "audit.h"
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/refcount.h>
#समावेश <linux/slab.h>

काष्ठा audit_tree;
काष्ठा audit_chunk;

काष्ठा audit_tree अणु
	refcount_t count;
	पूर्णांक goner;
	काष्ठा audit_chunk *root;
	काष्ठा list_head chunks;
	काष्ठा list_head rules;
	काष्ठा list_head list;
	काष्ठा list_head same_root;
	काष्ठा rcu_head head;
	अक्षर pathname[];
पूर्ण;

काष्ठा audit_chunk अणु
	काष्ठा list_head hash;
	अचिन्हित दीर्घ key;
	काष्ठा fsnotअगरy_mark *mark;
	काष्ठा list_head trees;		/* with root here */
	पूर्णांक count;
	atomic_दीर्घ_t refs;
	काष्ठा rcu_head head;
	काष्ठा node अणु
		काष्ठा list_head list;
		काष्ठा audit_tree *owner;
		अचिन्हित index;		/* index; upper bit indicates 'will prune' */
	पूर्ण owners[];
पूर्ण;

काष्ठा audit_tree_mark अणु
	काष्ठा fsnotअगरy_mark mark;
	काष्ठा audit_chunk *chunk;
पूर्ण;

अटल LIST_HEAD(tree_list);
अटल LIST_HEAD(prune_list);
अटल काष्ठा task_काष्ठा *prune_thपढ़ो;

/*
 * One काष्ठा chunk is attached to each inode of पूर्णांकerest through
 * audit_tree_mark (fsnotअगरy mark). We replace काष्ठा chunk on tagging /
 * untagging, the mark is stable as दीर्घ as there is chunk attached. The
 * association between mark and chunk is रक्षित by hash_lock and
 * audit_tree_group->mark_mutex. Thus as दीर्घ as we hold
 * audit_tree_group->mark_mutex and check that the mark is alive by
 * FSNOTIFY_MARK_FLAG_ATTACHED flag check, we are sure the mark poपूर्णांकs to
 * the current chunk.
 *
 * Rules have poपूर्णांकer to काष्ठा audit_tree.
 * Rules have काष्ठा list_head rlist क्रमming a list of rules over
 * the same tree.
 * References to काष्ठा chunk are collected at audit_inodeअणु,_childपूर्ण()
 * समय and used in AUDIT_TREE rule matching.
 * These references are dropped at the same समय we are calling
 * audit_मुक्त_names(), etc.
 *
 * Cyclic lists galore:
 * tree.chunks anchors chunk.owners[].list			hash_lock
 * tree.rules anchors rule.rlist				audit_filter_mutex
 * chunk.trees anchors tree.same_root				hash_lock
 * chunk.hash is a hash with middle bits of watch.inode as
 * a hash function.						RCU, hash_lock
 *
 * tree is refcounted; one reference क्रम "some rules on rules_list refer to
 * it", one क्रम each chunk with poपूर्णांकer to it.
 *
 * chunk is refcounted by embedded .refs. Mark associated with the chunk holds
 * one chunk reference. This reference is dropped either when a mark is going
 * to be मुक्तd (corresponding inode goes away) or when chunk attached to the
 * mark माला_लो replaced. This reference must be dropped using
 * audit_mark_put_chunk() to make sure the reference is dropped only after RCU
 * grace period as it protects RCU पढ़ोers of the hash table.
 *
 * node.index allows to get from node.list to containing chunk.
 * MSB of that sucker is stolen to mark taggings that we might have to
 * revert - several operations have very unpleasant cleanup logics and
 * that makes a dअगरference.  Some.
 */

अटल काष्ठा fsnotअगरy_group *audit_tree_group;
अटल काष्ठा kmem_cache *audit_tree_mark_cachep __पढ़ो_mostly;

अटल काष्ठा audit_tree *alloc_tree(स्थिर अक्षर *s)
अणु
	काष्ठा audit_tree *tree;

	tree = kदो_स्मृति(माप(काष्ठा audit_tree) + म_माप(s) + 1, GFP_KERNEL);
	अगर (tree) अणु
		refcount_set(&tree->count, 1);
		tree->goner = 0;
		INIT_LIST_HEAD(&tree->chunks);
		INIT_LIST_HEAD(&tree->rules);
		INIT_LIST_HEAD(&tree->list);
		INIT_LIST_HEAD(&tree->same_root);
		tree->root = शून्य;
		म_नकल(tree->pathname, s);
	पूर्ण
	वापस tree;
पूर्ण

अटल अंतरभूत व्योम get_tree(काष्ठा audit_tree *tree)
अणु
	refcount_inc(&tree->count);
पूर्ण

अटल अंतरभूत व्योम put_tree(काष्ठा audit_tree *tree)
अणु
	अगर (refcount_dec_and_test(&tree->count))
		kमुक्त_rcu(tree, head);
पूर्ण

/* to aव्योम bringing the entire thing in audit.h */
स्थिर अक्षर *audit_tree_path(काष्ठा audit_tree *tree)
अणु
	वापस tree->pathname;
पूर्ण

अटल व्योम मुक्त_chunk(काष्ठा audit_chunk *chunk)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < chunk->count; i++) अणु
		अगर (chunk->owners[i].owner)
			put_tree(chunk->owners[i].owner);
	पूर्ण
	kमुक्त(chunk);
पूर्ण

व्योम audit_put_chunk(काष्ठा audit_chunk *chunk)
अणु
	अगर (atomic_दीर्घ_dec_and_test(&chunk->refs))
		मुक्त_chunk(chunk);
पूर्ण

अटल व्योम __put_chunk(काष्ठा rcu_head *rcu)
अणु
	काष्ठा audit_chunk *chunk = container_of(rcu, काष्ठा audit_chunk, head);
	audit_put_chunk(chunk);
पूर्ण

/*
 * Drop reference to the chunk that was held by the mark. This is the reference
 * that माला_लो dropped after we've हटाओd the chunk from the hash table and we
 * use it to make sure chunk cannot be मुक्तd beक्रमe RCU grace period expires.
 */
अटल व्योम audit_mark_put_chunk(काष्ठा audit_chunk *chunk)
अणु
	call_rcu(&chunk->head, __put_chunk);
पूर्ण

अटल अंतरभूत काष्ठा audit_tree_mark *audit_mark(काष्ठा fsnotअगरy_mark *mark)
अणु
	वापस container_of(mark, काष्ठा audit_tree_mark, mark);
पूर्ण

अटल काष्ठा audit_chunk *mark_chunk(काष्ठा fsnotअगरy_mark *mark)
अणु
	वापस audit_mark(mark)->chunk;
पूर्ण

अटल व्योम audit_tree_destroy_watch(काष्ठा fsnotअगरy_mark *mark)
अणु
	kmem_cache_मुक्त(audit_tree_mark_cachep, audit_mark(mark));
पूर्ण

अटल काष्ठा fsnotअगरy_mark *alloc_mark(व्योम)
अणु
	काष्ठा audit_tree_mark *amark;

	amark = kmem_cache_zalloc(audit_tree_mark_cachep, GFP_KERNEL);
	अगर (!amark)
		वापस शून्य;
	fsnotअगरy_init_mark(&amark->mark, audit_tree_group);
	amark->mark.mask = FS_IN_IGNORED;
	वापस &amark->mark;
पूर्ण

अटल काष्ठा audit_chunk *alloc_chunk(पूर्णांक count)
अणु
	काष्ठा audit_chunk *chunk;
	पूर्णांक i;

	chunk = kzalloc(काष्ठा_size(chunk, owners, count), GFP_KERNEL);
	अगर (!chunk)
		वापस शून्य;

	INIT_LIST_HEAD(&chunk->hash);
	INIT_LIST_HEAD(&chunk->trees);
	chunk->count = count;
	atomic_दीर्घ_set(&chunk->refs, 1);
	क्रम (i = 0; i < count; i++) अणु
		INIT_LIST_HEAD(&chunk->owners[i].list);
		chunk->owners[i].index = i;
	पूर्ण
	वापस chunk;
पूर्ण

क्रमागत अणुHASH_SIZE = 128पूर्ण;
अटल काष्ठा list_head chunk_hash_heads[HASH_SIZE];
अटल __cacheline_aligned_in_smp DEFINE_SPINLOCK(hash_lock);

/* Function to वापस search key in our hash from inode. */
अटल अचिन्हित दीर्घ inode_to_key(स्थिर काष्ठा inode *inode)
अणु
	/* Use address poपूर्णांकed to by connector->obj as the key */
	वापस (अचिन्हित दीर्घ)&inode->i_fsnotअगरy_marks;
पूर्ण

अटल अंतरभूत काष्ठा list_head *chunk_hash(अचिन्हित दीर्घ key)
अणु
	अचिन्हित दीर्घ n = key / L1_CACHE_BYTES;
	वापस chunk_hash_heads + n % HASH_SIZE;
पूर्ण

/* hash_lock & mark->group->mark_mutex is held by caller */
अटल व्योम insert_hash(काष्ठा audit_chunk *chunk)
अणु
	काष्ठा list_head *list;

	/*
	 * Make sure chunk is fully initialized beक्रमe making it visible in the
	 * hash. Pairs with a data dependency barrier in READ_ONCE() in
	 * audit_tree_lookup().
	 */
	smp_wmb();
	WARN_ON_ONCE(!chunk->key);
	list = chunk_hash(chunk->key);
	list_add_rcu(&chunk->hash, list);
पूर्ण

/* called under rcu_पढ़ो_lock */
काष्ठा audit_chunk *audit_tree_lookup(स्थिर काष्ठा inode *inode)
अणु
	अचिन्हित दीर्घ key = inode_to_key(inode);
	काष्ठा list_head *list = chunk_hash(key);
	काष्ठा audit_chunk *p;

	list_क्रम_each_entry_rcu(p, list, hash) अणु
		/*
		 * We use a data dependency barrier in READ_ONCE() to make sure
		 * the chunk we see is fully initialized.
		 */
		अगर (READ_ONCE(p->key) == key) अणु
			atomic_दीर्घ_inc(&p->refs);
			वापस p;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

bool audit_tree_match(काष्ठा audit_chunk *chunk, काष्ठा audit_tree *tree)
अणु
	पूर्णांक n;
	क्रम (n = 0; n < chunk->count; n++)
		अगर (chunk->owners[n].owner == tree)
			वापस true;
	वापस false;
पूर्ण

/* tagging and untagging inodes with trees */

अटल काष्ठा audit_chunk *find_chunk(काष्ठा node *p)
अणु
	पूर्णांक index = p->index & ~(1U<<31);
	p -= index;
	वापस container_of(p, काष्ठा audit_chunk, owners[0]);
पूर्ण

अटल व्योम replace_mark_chunk(काष्ठा fsnotअगरy_mark *mark,
			       काष्ठा audit_chunk *chunk)
अणु
	काष्ठा audit_chunk *old;

	निश्चित_spin_locked(&hash_lock);
	old = mark_chunk(mark);
	audit_mark(mark)->chunk = chunk;
	अगर (chunk)
		chunk->mark = mark;
	अगर (old)
		old->mark = शून्य;
पूर्ण

अटल व्योम replace_chunk(काष्ठा audit_chunk *new, काष्ठा audit_chunk *old)
अणु
	काष्ठा audit_tree *owner;
	पूर्णांक i, j;

	new->key = old->key;
	list_splice_init(&old->trees, &new->trees);
	list_क्रम_each_entry(owner, &new->trees, same_root)
		owner->root = new;
	क्रम (i = j = 0; j < old->count; i++, j++) अणु
		अगर (!old->owners[j].owner) अणु
			i--;
			जारी;
		पूर्ण
		owner = old->owners[j].owner;
		new->owners[i].owner = owner;
		new->owners[i].index = old->owners[j].index - j + i;
		अगर (!owner) /* result of earlier fallback */
			जारी;
		get_tree(owner);
		list_replace_init(&old->owners[j].list, &new->owners[i].list);
	पूर्ण
	replace_mark_chunk(old->mark, new);
	/*
	 * Make sure chunk is fully initialized beक्रमe making it visible in the
	 * hash. Pairs with a data dependency barrier in READ_ONCE() in
	 * audit_tree_lookup().
	 */
	smp_wmb();
	list_replace_rcu(&old->hash, &new->hash);
पूर्ण

अटल व्योम हटाओ_chunk_node(काष्ठा audit_chunk *chunk, काष्ठा node *p)
अणु
	काष्ठा audit_tree *owner = p->owner;

	अगर (owner->root == chunk) अणु
		list_del_init(&owner->same_root);
		owner->root = शून्य;
	पूर्ण
	list_del_init(&p->list);
	p->owner = शून्य;
	put_tree(owner);
पूर्ण

अटल पूर्णांक chunk_count_trees(काष्ठा audit_chunk *chunk)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;

	क्रम (i = 0; i < chunk->count; i++)
		अगर (chunk->owners[i].owner)
			ret++;
	वापस ret;
पूर्ण

अटल व्योम untag_chunk(काष्ठा audit_chunk *chunk, काष्ठा fsnotअगरy_mark *mark)
अणु
	काष्ठा audit_chunk *new;
	पूर्णांक size;

	mutex_lock(&audit_tree_group->mark_mutex);
	/*
	 * mark_mutex stabilizes chunk attached to the mark so we can check
	 * whether it didn't change while we've dropped hash_lock.
	 */
	अगर (!(mark->flags & FSNOTIFY_MARK_FLAG_ATTACHED) ||
	    mark_chunk(mark) != chunk)
		जाओ out_mutex;

	size = chunk_count_trees(chunk);
	अगर (!size) अणु
		spin_lock(&hash_lock);
		list_del_init(&chunk->trees);
		list_del_rcu(&chunk->hash);
		replace_mark_chunk(mark, शून्य);
		spin_unlock(&hash_lock);
		fsnotअगरy_detach_mark(mark);
		mutex_unlock(&audit_tree_group->mark_mutex);
		audit_mark_put_chunk(chunk);
		fsnotअगरy_मुक्त_mark(mark);
		वापस;
	पूर्ण

	new = alloc_chunk(size);
	अगर (!new)
		जाओ out_mutex;

	spin_lock(&hash_lock);
	/*
	 * This has to go last when updating chunk as once replace_chunk() is
	 * called, new RCU पढ़ोers can see the new chunk.
	 */
	replace_chunk(new, chunk);
	spin_unlock(&hash_lock);
	mutex_unlock(&audit_tree_group->mark_mutex);
	audit_mark_put_chunk(chunk);
	वापस;

out_mutex:
	mutex_unlock(&audit_tree_group->mark_mutex);
पूर्ण

/* Call with group->mark_mutex held, releases it */
अटल पूर्णांक create_chunk(काष्ठा inode *inode, काष्ठा audit_tree *tree)
अणु
	काष्ठा fsnotअगरy_mark *mark;
	काष्ठा audit_chunk *chunk = alloc_chunk(1);

	अगर (!chunk) अणु
		mutex_unlock(&audit_tree_group->mark_mutex);
		वापस -ENOMEM;
	पूर्ण

	mark = alloc_mark();
	अगर (!mark) अणु
		mutex_unlock(&audit_tree_group->mark_mutex);
		kमुक्त(chunk);
		वापस -ENOMEM;
	पूर्ण

	अगर (fsnotअगरy_add_inode_mark_locked(mark, inode, 0)) अणु
		mutex_unlock(&audit_tree_group->mark_mutex);
		fsnotअगरy_put_mark(mark);
		kमुक्त(chunk);
		वापस -ENOSPC;
	पूर्ण

	spin_lock(&hash_lock);
	अगर (tree->goner) अणु
		spin_unlock(&hash_lock);
		fsnotअगरy_detach_mark(mark);
		mutex_unlock(&audit_tree_group->mark_mutex);
		fsnotअगरy_मुक्त_mark(mark);
		fsnotअगरy_put_mark(mark);
		kमुक्त(chunk);
		वापस 0;
	पूर्ण
	replace_mark_chunk(mark, chunk);
	chunk->owners[0].index = (1U << 31);
	chunk->owners[0].owner = tree;
	get_tree(tree);
	list_add(&chunk->owners[0].list, &tree->chunks);
	अगर (!tree->root) अणु
		tree->root = chunk;
		list_add(&tree->same_root, &chunk->trees);
	पूर्ण
	chunk->key = inode_to_key(inode);
	/*
	 * Inserting पूर्णांकo the hash table has to go last as once we करो that RCU
	 * पढ़ोers can see the chunk.
	 */
	insert_hash(chunk);
	spin_unlock(&hash_lock);
	mutex_unlock(&audit_tree_group->mark_mutex);
	/*
	 * Drop our initial reference. When mark we poपूर्णांक to is getting मुक्तd,
	 * we get notअगरication through ->मुक्तing_mark callback and cleanup
	 * chunk poपूर्णांकing to this mark.
	 */
	fsnotअगरy_put_mark(mark);
	वापस 0;
पूर्ण

/* the first tagged inode becomes root of tree */
अटल पूर्णांक tag_chunk(काष्ठा inode *inode, काष्ठा audit_tree *tree)
अणु
	काष्ठा fsnotअगरy_mark *mark;
	काष्ठा audit_chunk *chunk, *old;
	काष्ठा node *p;
	पूर्णांक n;

	mutex_lock(&audit_tree_group->mark_mutex);
	mark = fsnotअगरy_find_mark(&inode->i_fsnotअगरy_marks, audit_tree_group);
	अगर (!mark)
		वापस create_chunk(inode, tree);

	/*
	 * Found mark is guaranteed to be attached and mark_mutex protects mark
	 * from getting detached and thus it makes sure there is chunk attached
	 * to the mark.
	 */
	/* are we alपढ़ोy there? */
	spin_lock(&hash_lock);
	old = mark_chunk(mark);
	क्रम (n = 0; n < old->count; n++) अणु
		अगर (old->owners[n].owner == tree) अणु
			spin_unlock(&hash_lock);
			mutex_unlock(&audit_tree_group->mark_mutex);
			fsnotअगरy_put_mark(mark);
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock(&hash_lock);

	chunk = alloc_chunk(old->count + 1);
	अगर (!chunk) अणु
		mutex_unlock(&audit_tree_group->mark_mutex);
		fsnotअगरy_put_mark(mark);
		वापस -ENOMEM;
	पूर्ण

	spin_lock(&hash_lock);
	अगर (tree->goner) अणु
		spin_unlock(&hash_lock);
		mutex_unlock(&audit_tree_group->mark_mutex);
		fsnotअगरy_put_mark(mark);
		kमुक्त(chunk);
		वापस 0;
	पूर्ण
	p = &chunk->owners[chunk->count - 1];
	p->index = (chunk->count - 1) | (1U<<31);
	p->owner = tree;
	get_tree(tree);
	list_add(&p->list, &tree->chunks);
	अगर (!tree->root) अणु
		tree->root = chunk;
		list_add(&tree->same_root, &chunk->trees);
	पूर्ण
	/*
	 * This has to go last when updating chunk as once replace_chunk() is
	 * called, new RCU पढ़ोers can see the new chunk.
	 */
	replace_chunk(chunk, old);
	spin_unlock(&hash_lock);
	mutex_unlock(&audit_tree_group->mark_mutex);
	fsnotअगरy_put_mark(mark); /* pair to fsnotअगरy_find_mark */
	audit_mark_put_chunk(old);

	वापस 0;
पूर्ण

अटल व्योम audit_tree_log_हटाओ_rule(काष्ठा audit_context *context,
				       काष्ठा audit_krule *rule)
अणु
	काष्ठा audit_buffer *ab;

	अगर (!audit_enabled)
		वापस;
	ab = audit_log_start(context, GFP_KERNEL, AUDIT_CONFIG_CHANGE);
	अगर (unlikely(!ab))
		वापस;
	audit_log_क्रमmat(ab, "op=remove_rule dir=");
	audit_log_untrustedstring(ab, rule->tree->pathname);
	audit_log_key(ab, rule->filterkey);
	audit_log_क्रमmat(ab, " list=%d res=1", rule->listnr);
	audit_log_end(ab);
पूर्ण

अटल व्योम समाप्त_rules(काष्ठा audit_context *context, काष्ठा audit_tree *tree)
अणु
	काष्ठा audit_krule *rule, *next;
	काष्ठा audit_entry *entry;

	list_क्रम_each_entry_safe(rule, next, &tree->rules, rlist) अणु
		entry = container_of(rule, काष्ठा audit_entry, rule);

		list_del_init(&rule->rlist);
		अगर (rule->tree) अणु
			/* not a half-baked one */
			audit_tree_log_हटाओ_rule(context, rule);
			अगर (entry->rule.exe)
				audit_हटाओ_mark(entry->rule.exe);
			rule->tree = शून्य;
			list_del_rcu(&entry->list);
			list_del(&entry->rule.list);
			call_rcu(&entry->rcu, audit_मुक्त_rule_rcu);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Remove tree from chunks. If 'tagged' is set, हटाओ tree only from tagged
 * chunks. The function expects tagged chunks are all at the beginning of the
 * chunks list.
 */
अटल व्योम prune_tree_chunks(काष्ठा audit_tree *victim, bool tagged)
अणु
	spin_lock(&hash_lock);
	जबतक (!list_empty(&victim->chunks)) अणु
		काष्ठा node *p;
		काष्ठा audit_chunk *chunk;
		काष्ठा fsnotअगरy_mark *mark;

		p = list_first_entry(&victim->chunks, काष्ठा node, list);
		/* have we run out of marked? */
		अगर (tagged && !(p->index & (1U<<31)))
			अवरोध;
		chunk = find_chunk(p);
		mark = chunk->mark;
		हटाओ_chunk_node(chunk, p);
		/* Racing with audit_tree_मुक्तing_mark()? */
		अगर (!mark)
			जारी;
		fsnotअगरy_get_mark(mark);
		spin_unlock(&hash_lock);

		untag_chunk(chunk, mark);
		fsnotअगरy_put_mark(mark);

		spin_lock(&hash_lock);
	पूर्ण
	spin_unlock(&hash_lock);
	put_tree(victim);
पूर्ण

/*
 * finish समाप्तing काष्ठा audit_tree
 */
अटल व्योम prune_one(काष्ठा audit_tree *victim)
अणु
	prune_tree_chunks(victim, false);
पूर्ण

/* trim the uncommitted chunks from tree */

अटल व्योम trim_marked(काष्ठा audit_tree *tree)
अणु
	काष्ठा list_head *p, *q;
	spin_lock(&hash_lock);
	अगर (tree->goner) अणु
		spin_unlock(&hash_lock);
		वापस;
	पूर्ण
	/* reorder */
	क्रम (p = tree->chunks.next; p != &tree->chunks; p = q) अणु
		काष्ठा node *node = list_entry(p, काष्ठा node, list);
		q = p->next;
		अगर (node->index & (1U<<31)) अणु
			list_del_init(p);
			list_add(p, &tree->chunks);
		पूर्ण
	पूर्ण
	spin_unlock(&hash_lock);

	prune_tree_chunks(tree, true);

	spin_lock(&hash_lock);
	अगर (!tree->root && !tree->goner) अणु
		tree->goner = 1;
		spin_unlock(&hash_lock);
		mutex_lock(&audit_filter_mutex);
		समाप्त_rules(audit_context(), tree);
		list_del_init(&tree->list);
		mutex_unlock(&audit_filter_mutex);
		prune_one(tree);
	पूर्ण अन्यथा अणु
		spin_unlock(&hash_lock);
	पूर्ण
पूर्ण

अटल व्योम audit_schedule_prune(व्योम);

/* called with audit_filter_mutex */
पूर्णांक audit_हटाओ_tree_rule(काष्ठा audit_krule *rule)
अणु
	काष्ठा audit_tree *tree;
	tree = rule->tree;
	अगर (tree) अणु
		spin_lock(&hash_lock);
		list_del_init(&rule->rlist);
		अगर (list_empty(&tree->rules) && !tree->goner) अणु
			tree->root = शून्य;
			list_del_init(&tree->same_root);
			tree->goner = 1;
			list_move(&tree->list, &prune_list);
			rule->tree = शून्य;
			spin_unlock(&hash_lock);
			audit_schedule_prune();
			वापस 1;
		पूर्ण
		rule->tree = शून्य;
		spin_unlock(&hash_lock);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक compare_root(काष्ठा vfsmount *mnt, व्योम *arg)
अणु
	वापस inode_to_key(d_backing_inode(mnt->mnt_root)) ==
	       (अचिन्हित दीर्घ)arg;
पूर्ण

व्योम audit_trim_trees(व्योम)
अणु
	काष्ठा list_head cursor;

	mutex_lock(&audit_filter_mutex);
	list_add(&cursor, &tree_list);
	जबतक (cursor.next != &tree_list) अणु
		काष्ठा audit_tree *tree;
		काष्ठा path path;
		काष्ठा vfsmount *root_mnt;
		काष्ठा node *node;
		पूर्णांक err;

		tree = container_of(cursor.next, काष्ठा audit_tree, list);
		get_tree(tree);
		list_del(&cursor);
		list_add(&cursor, &tree->list);
		mutex_unlock(&audit_filter_mutex);

		err = kern_path(tree->pathname, 0, &path);
		अगर (err)
			जाओ skip_it;

		root_mnt = collect_mounts(&path);
		path_put(&path);
		अगर (IS_ERR(root_mnt))
			जाओ skip_it;

		spin_lock(&hash_lock);
		list_क्रम_each_entry(node, &tree->chunks, list) अणु
			काष्ठा audit_chunk *chunk = find_chunk(node);
			/* this could be शून्य अगर the watch is dying अन्यथा where... */
			node->index |= 1U<<31;
			अगर (iterate_mounts(compare_root,
					   (व्योम *)(chunk->key),
					   root_mnt))
				node->index &= ~(1U<<31);
		पूर्ण
		spin_unlock(&hash_lock);
		trim_marked(tree);
		drop_collected_mounts(root_mnt);
skip_it:
		put_tree(tree);
		mutex_lock(&audit_filter_mutex);
	पूर्ण
	list_del(&cursor);
	mutex_unlock(&audit_filter_mutex);
पूर्ण

पूर्णांक audit_make_tree(काष्ठा audit_krule *rule, अक्षर *pathname, u32 op)
अणु

	अगर (pathname[0] != '/' ||
	    rule->listnr != AUDIT_FILTER_EXIT ||
	    op != Audit_equal ||
	    rule->inode_f || rule->watch || rule->tree)
		वापस -EINVAL;
	rule->tree = alloc_tree(pathname);
	अगर (!rule->tree)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम audit_put_tree(काष्ठा audit_tree *tree)
अणु
	put_tree(tree);
पूर्ण

अटल पूर्णांक tag_mount(काष्ठा vfsmount *mnt, व्योम *arg)
अणु
	वापस tag_chunk(d_backing_inode(mnt->mnt_root), arg);
पूर्ण

/*
 * That माला_लो run when evict_chunk() ends up needing to समाप्त audit_tree.
 * Runs from a separate thपढ़ो.
 */
अटल पूर्णांक prune_tree_thपढ़ो(व्योम *unused)
अणु
	क्रम (;;) अणु
		अगर (list_empty(&prune_list)) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			schedule();
		पूर्ण

		audit_ctl_lock();
		mutex_lock(&audit_filter_mutex);

		जबतक (!list_empty(&prune_list)) अणु
			काष्ठा audit_tree *victim;

			victim = list_entry(prune_list.next,
					काष्ठा audit_tree, list);
			list_del_init(&victim->list);

			mutex_unlock(&audit_filter_mutex);

			prune_one(victim);

			mutex_lock(&audit_filter_mutex);
		पूर्ण

		mutex_unlock(&audit_filter_mutex);
		audit_ctl_unlock();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक audit_launch_prune(व्योम)
अणु
	अगर (prune_thपढ़ो)
		वापस 0;
	prune_thपढ़ो = kthपढ़ो_run(prune_tree_thपढ़ो, शून्य,
				"audit_prune_tree");
	अगर (IS_ERR(prune_thपढ़ो)) अणु
		pr_err("cannot start thread audit_prune_tree");
		prune_thपढ़ो = शून्य;
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/* called with audit_filter_mutex */
पूर्णांक audit_add_tree_rule(काष्ठा audit_krule *rule)
अणु
	काष्ठा audit_tree *seed = rule->tree, *tree;
	काष्ठा path path;
	काष्ठा vfsmount *mnt;
	पूर्णांक err;

	rule->tree = शून्य;
	list_क्रम_each_entry(tree, &tree_list, list) अणु
		अगर (!म_भेद(seed->pathname, tree->pathname)) अणु
			put_tree(seed);
			rule->tree = tree;
			list_add(&rule->rlist, &tree->rules);
			वापस 0;
		पूर्ण
	पूर्ण
	tree = seed;
	list_add(&tree->list, &tree_list);
	list_add(&rule->rlist, &tree->rules);
	/* करो not set rule->tree yet */
	mutex_unlock(&audit_filter_mutex);

	अगर (unlikely(!prune_thपढ़ो)) अणु
		err = audit_launch_prune();
		अगर (err)
			जाओ Err;
	पूर्ण

	err = kern_path(tree->pathname, 0, &path);
	अगर (err)
		जाओ Err;
	mnt = collect_mounts(&path);
	path_put(&path);
	अगर (IS_ERR(mnt)) अणु
		err = PTR_ERR(mnt);
		जाओ Err;
	पूर्ण

	get_tree(tree);
	err = iterate_mounts(tag_mount, tree, mnt);
	drop_collected_mounts(mnt);

	अगर (!err) अणु
		काष्ठा node *node;
		spin_lock(&hash_lock);
		list_क्रम_each_entry(node, &tree->chunks, list)
			node->index &= ~(1U<<31);
		spin_unlock(&hash_lock);
	पूर्ण अन्यथा अणु
		trim_marked(tree);
		जाओ Err;
	पूर्ण

	mutex_lock(&audit_filter_mutex);
	अगर (list_empty(&rule->rlist)) अणु
		put_tree(tree);
		वापस -ENOENT;
	पूर्ण
	rule->tree = tree;
	put_tree(tree);

	वापस 0;
Err:
	mutex_lock(&audit_filter_mutex);
	list_del_init(&tree->list);
	list_del_init(&tree->rules);
	put_tree(tree);
	वापस err;
पूर्ण

पूर्णांक audit_tag_tree(अक्षर *old, अक्षर *new)
अणु
	काष्ठा list_head cursor, barrier;
	पूर्णांक failed = 0;
	काष्ठा path path1, path2;
	काष्ठा vfsmount *tagged;
	पूर्णांक err;

	err = kern_path(new, 0, &path2);
	अगर (err)
		वापस err;
	tagged = collect_mounts(&path2);
	path_put(&path2);
	अगर (IS_ERR(tagged))
		वापस PTR_ERR(tagged);

	err = kern_path(old, 0, &path1);
	अगर (err) अणु
		drop_collected_mounts(tagged);
		वापस err;
	पूर्ण

	mutex_lock(&audit_filter_mutex);
	list_add(&barrier, &tree_list);
	list_add(&cursor, &barrier);

	जबतक (cursor.next != &tree_list) अणु
		काष्ठा audit_tree *tree;
		पूर्णांक good_one = 0;

		tree = container_of(cursor.next, काष्ठा audit_tree, list);
		get_tree(tree);
		list_del(&cursor);
		list_add(&cursor, &tree->list);
		mutex_unlock(&audit_filter_mutex);

		err = kern_path(tree->pathname, 0, &path2);
		अगर (!err) अणु
			good_one = path_is_under(&path1, &path2);
			path_put(&path2);
		पूर्ण

		अगर (!good_one) अणु
			put_tree(tree);
			mutex_lock(&audit_filter_mutex);
			जारी;
		पूर्ण

		failed = iterate_mounts(tag_mount, tree, tagged);
		अगर (failed) अणु
			put_tree(tree);
			mutex_lock(&audit_filter_mutex);
			अवरोध;
		पूर्ण

		mutex_lock(&audit_filter_mutex);
		spin_lock(&hash_lock);
		अगर (!tree->goner) अणु
			list_del(&tree->list);
			list_add(&tree->list, &tree_list);
		पूर्ण
		spin_unlock(&hash_lock);
		put_tree(tree);
	पूर्ण

	जबतक (barrier.prev != &tree_list) अणु
		काष्ठा audit_tree *tree;

		tree = container_of(barrier.prev, काष्ठा audit_tree, list);
		get_tree(tree);
		list_del(&tree->list);
		list_add(&tree->list, &barrier);
		mutex_unlock(&audit_filter_mutex);

		अगर (!failed) अणु
			काष्ठा node *node;
			spin_lock(&hash_lock);
			list_क्रम_each_entry(node, &tree->chunks, list)
				node->index &= ~(1U<<31);
			spin_unlock(&hash_lock);
		पूर्ण अन्यथा अणु
			trim_marked(tree);
		पूर्ण

		put_tree(tree);
		mutex_lock(&audit_filter_mutex);
	पूर्ण
	list_del(&barrier);
	list_del(&cursor);
	mutex_unlock(&audit_filter_mutex);
	path_put(&path1);
	drop_collected_mounts(tagged);
	वापस failed;
पूर्ण


अटल व्योम audit_schedule_prune(व्योम)
अणु
	wake_up_process(prune_thपढ़ो);
पूर्ण

/*
 * ... and that one is करोne अगर evict_chunk() decides to delay until the end
 * of syscall.  Runs synchronously.
 */
व्योम audit_समाप्त_trees(काष्ठा audit_context *context)
अणु
	काष्ठा list_head *list = &context->समाप्तed_trees;

	audit_ctl_lock();
	mutex_lock(&audit_filter_mutex);

	जबतक (!list_empty(list)) अणु
		काष्ठा audit_tree *victim;

		victim = list_entry(list->next, काष्ठा audit_tree, list);
		समाप्त_rules(context, victim);
		list_del_init(&victim->list);

		mutex_unlock(&audit_filter_mutex);

		prune_one(victim);

		mutex_lock(&audit_filter_mutex);
	पूर्ण

	mutex_unlock(&audit_filter_mutex);
	audit_ctl_unlock();
पूर्ण

/*
 *  Here comes the stuff asynchronous to auditctl operations
 */

अटल व्योम evict_chunk(काष्ठा audit_chunk *chunk)
अणु
	काष्ठा audit_tree *owner;
	काष्ठा list_head *postponed = audit_समाप्तed_trees();
	पूर्णांक need_prune = 0;
	पूर्णांक n;

	mutex_lock(&audit_filter_mutex);
	spin_lock(&hash_lock);
	जबतक (!list_empty(&chunk->trees)) अणु
		owner = list_entry(chunk->trees.next,
				   काष्ठा audit_tree, same_root);
		owner->goner = 1;
		owner->root = शून्य;
		list_del_init(&owner->same_root);
		spin_unlock(&hash_lock);
		अगर (!postponed) अणु
			समाप्त_rules(audit_context(), owner);
			list_move(&owner->list, &prune_list);
			need_prune = 1;
		पूर्ण अन्यथा अणु
			list_move(&owner->list, postponed);
		पूर्ण
		spin_lock(&hash_lock);
	पूर्ण
	list_del_rcu(&chunk->hash);
	क्रम (n = 0; n < chunk->count; n++)
		list_del_init(&chunk->owners[n].list);
	spin_unlock(&hash_lock);
	mutex_unlock(&audit_filter_mutex);
	अगर (need_prune)
		audit_schedule_prune();
पूर्ण

अटल पूर्णांक audit_tree_handle_event(काष्ठा fsnotअगरy_mark *mark, u32 mask,
				   काष्ठा inode *inode, काष्ठा inode *dir,
				   स्थिर काष्ठा qstr *file_name, u32 cookie)
अणु
	वापस 0;
पूर्ण

अटल व्योम audit_tree_मुक्तing_mark(काष्ठा fsnotअगरy_mark *mark,
				    काष्ठा fsnotअगरy_group *group)
अणु
	काष्ठा audit_chunk *chunk;

	mutex_lock(&mark->group->mark_mutex);
	spin_lock(&hash_lock);
	chunk = mark_chunk(mark);
	replace_mark_chunk(mark, शून्य);
	spin_unlock(&hash_lock);
	mutex_unlock(&mark->group->mark_mutex);
	अगर (chunk) अणु
		evict_chunk(chunk);
		audit_mark_put_chunk(chunk);
	पूर्ण

	/*
	 * We are guaranteed to have at least one reference to the mark from
	 * either the inode or the caller of fsnotअगरy_destroy_mark().
	 */
	BUG_ON(refcount_पढ़ो(&mark->refcnt) < 1);
पूर्ण

अटल स्थिर काष्ठा fsnotअगरy_ops audit_tree_ops = अणु
	.handle_inode_event = audit_tree_handle_event,
	.मुक्तing_mark = audit_tree_मुक्तing_mark,
	.मुक्त_mark = audit_tree_destroy_watch,
पूर्ण;

अटल पूर्णांक __init audit_tree_init(व्योम)
अणु
	पूर्णांक i;

	audit_tree_mark_cachep = KMEM_CACHE(audit_tree_mark, SLAB_PANIC);

	audit_tree_group = fsnotअगरy_alloc_group(&audit_tree_ops);
	अगर (IS_ERR(audit_tree_group))
		audit_panic("cannot initialize fsnotify group for rectree watches");

	क्रम (i = 0; i < HASH_SIZE; i++)
		INIT_LIST_HEAD(&chunk_hash_heads[i]);

	वापस 0;
पूर्ण
__initcall(audit_tree_init);
