<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * fs/dcache.c
 *
 * Complete reimplementation
 * (C) 1997 Thomas Schoebel-Theuer,
 * with heavy changes by Linus Torvalds
 */

/*
 * Notes on the allocation strategy:
 *
 * The dcache is a master of the icache - whenever a dcache entry
 * exists, the inode will always exist. "iput()" is करोne either when
 * the dcache entry is deleted or garbage collected.
 */

#समावेश <linux/ratelimit.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/fscrypt.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/hash.h>
#समावेश <linux/cache.h>
#समावेश <linux/export.h>
#समावेश <linux/security.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/memblock.h>
#समावेश <linux/bit_spinlock.h>
#समावेश <linux/rculist_bl.h>
#समावेश <linux/list_lru.h>
#समावेश "internal.h"
#समावेश "mount.h"

/*
 * Usage:
 * dcache->d_inode->i_lock protects:
 *   - i_dentry, d_u.d_alias, d_inode of aliases
 * dcache_hash_bucket lock protects:
 *   - the dcache hash table
 * s_roots bl list spinlock protects:
 *   - the s_roots list (see __d_drop)
 * dentry->d_sb->s_dentry_lru_lock protects:
 *   - the dcache lru lists and counters
 * d_lock protects:
 *   - d_flags
 *   - d_name
 *   - d_lru
 *   - d_count
 *   - d_unhashed()
 *   - d_parent and d_subdirs
 *   - childrens' d_child and d_parent
 *   - d_u.d_alias, d_inode
 *
 * Ordering:
 * dentry->d_inode->i_lock
 *   dentry->d_lock
 *     dentry->d_sb->s_dentry_lru_lock
 *     dcache_hash_bucket lock
 *     s_roots lock
 *
 * If there is an ancestor relationship:
 * dentry->d_parent->...->d_parent->d_lock
 *   ...
 *     dentry->d_parent->d_lock
 *       dentry->d_lock
 *
 * If no ancestor relationship:
 * arbitrary, since it's serialized on नाम_lock
 */
पूर्णांक sysctl_vfs_cache_pressure __पढ़ो_mostly = 100;
EXPORT_SYMBOL_GPL(sysctl_vfs_cache_pressure);

__cacheline_aligned_in_smp DEFINE_SEQLOCK(नाम_lock);

EXPORT_SYMBOL(नाम_lock);

अटल काष्ठा kmem_cache *dentry_cache __पढ़ो_mostly;

स्थिर काष्ठा qstr empty_name = QSTR_INIT("", 0);
EXPORT_SYMBOL(empty_name);
स्थिर काष्ठा qstr slash_name = QSTR_INIT("/", 1);
EXPORT_SYMBOL(slash_name);
स्थिर काष्ठा qstr करोtकरोt_name = QSTR_INIT("..", 2);
EXPORT_SYMBOL(करोtकरोt_name);

/*
 * This is the single most critical data काष्ठाure when it comes
 * to the dcache: the hashtable क्रम lookups. Somebody should try
 * to make this good - I've just made it work.
 *
 * This hash-function tries to aव्योम losing too many bits of hash
 * inक्रमmation, yet aव्योम using a prime hash-size or similar.
 */

अटल अचिन्हित पूर्णांक d_hash_shअगरt __पढ़ो_mostly;

अटल काष्ठा hlist_bl_head *dentry_hashtable __पढ़ो_mostly;

अटल अंतरभूत काष्ठा hlist_bl_head *d_hash(अचिन्हित पूर्णांक hash)
अणु
	वापस dentry_hashtable + (hash >> d_hash_shअगरt);
पूर्ण

#घोषणा IN_LOOKUP_SHIFT 10
अटल काष्ठा hlist_bl_head in_lookup_hashtable[1 << IN_LOOKUP_SHIFT];

अटल अंतरभूत काष्ठा hlist_bl_head *in_lookup_hash(स्थिर काष्ठा dentry *parent,
					अचिन्हित पूर्णांक hash)
अणु
	hash += (अचिन्हित दीर्घ) parent / L1_CACHE_BYTES;
	वापस in_lookup_hashtable + hash_32(hash, IN_LOOKUP_SHIFT);
पूर्ण


/* Statistics gathering. */
काष्ठा dentry_stat_t dentry_stat = अणु
	.age_limit = 45,
पूर्ण;

अटल DEFINE_PER_CPU(दीर्घ, nr_dentry);
अटल DEFINE_PER_CPU(दीर्घ, nr_dentry_unused);
अटल DEFINE_PER_CPU(दीर्घ, nr_dentry_negative);

#अगर defined(CONFIG_SYSCTL) && defined(CONFIG_PROC_FS)

/*
 * Here we resort to our own counters instead of using generic per-cpu counters
 * क्रम consistency with what the vfs inode code करोes. We are expected to harvest
 * better code and perक्रमmance by having our own specialized counters.
 *
 * Please note that the loop is करोne over all possible CPUs, not over all online
 * CPUs. The reason क्रम this is that we करोn't want to play games with CPUs going
 * on and off. If one of them goes off, we will just keep their counters.
 *
 * glommer: See cffbc8a क्रम details, and अगर you ever पूर्णांकend to change this,
 * please update all vfs counters to match.
 */
अटल दीर्घ get_nr_dentry(व्योम)
अणु
	पूर्णांक i;
	दीर्घ sum = 0;
	क्रम_each_possible_cpu(i)
		sum += per_cpu(nr_dentry, i);
	वापस sum < 0 ? 0 : sum;
पूर्ण

अटल दीर्घ get_nr_dentry_unused(व्योम)
अणु
	पूर्णांक i;
	दीर्घ sum = 0;
	क्रम_each_possible_cpu(i)
		sum += per_cpu(nr_dentry_unused, i);
	वापस sum < 0 ? 0 : sum;
पूर्ण

अटल दीर्घ get_nr_dentry_negative(व्योम)
अणु
	पूर्णांक i;
	दीर्घ sum = 0;

	क्रम_each_possible_cpu(i)
		sum += per_cpu(nr_dentry_negative, i);
	वापस sum < 0 ? 0 : sum;
पूर्ण

पूर्णांक proc_nr_dentry(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		   माप_प्रकार *lenp, loff_t *ppos)
अणु
	dentry_stat.nr_dentry = get_nr_dentry();
	dentry_stat.nr_unused = get_nr_dentry_unused();
	dentry_stat.nr_negative = get_nr_dentry_negative();
	वापस proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
पूर्ण
#पूर्ण_अगर

/*
 * Compare 2 name strings, वापस 0 अगर they match, otherwise non-zero.
 * The strings are both count bytes दीर्घ, and count is non-zero.
 */
#अगर_घोषित CONFIG_DCACHE_WORD_ACCESS

#समावेश <यंत्र/word-at-a-समय.स>
/*
 * NOTE! 'cs' and 'scount' come from a dentry, so it has a
 * aligned allocation क्रम this particular component. We करोn't
 * strictly need the load_unaligned_zeropad() safety, but it
 * करोesn't hurt either.
 *
 * In contrast, 'ct' and 'tcount' can be from a pathname, and करो
 * need the careful unaligned handling.
 */
अटल अंतरभूत पूर्णांक dentry_string_cmp(स्थिर अचिन्हित अक्षर *cs, स्थिर अचिन्हित अक्षर *ct, अचिन्हित tcount)
अणु
	अचिन्हित दीर्घ a,b,mask;

	क्रम (;;) अणु
		a = पढ़ो_word_at_a_समय(cs);
		b = load_unaligned_zeropad(ct);
		अगर (tcount < माप(अचिन्हित दीर्घ))
			अवरोध;
		अगर (unlikely(a != b))
			वापस 1;
		cs += माप(अचिन्हित दीर्घ);
		ct += माप(अचिन्हित दीर्घ);
		tcount -= माप(अचिन्हित दीर्घ);
		अगर (!tcount)
			वापस 0;
	पूर्ण
	mask = bytemask_from_count(tcount);
	वापस unlikely(!!((a ^ b) & mask));
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक dentry_string_cmp(स्थिर अचिन्हित अक्षर *cs, स्थिर अचिन्हित अक्षर *ct, अचिन्हित tcount)
अणु
	करो अणु
		अगर (*cs != *ct)
			वापस 1;
		cs++;
		ct++;
		tcount--;
	पूर्ण जबतक (tcount);
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत पूर्णांक dentry_cmp(स्थिर काष्ठा dentry *dentry, स्थिर अचिन्हित अक्षर *ct, अचिन्हित tcount)
अणु
	/*
	 * Be careful about RCU walk racing with नाम:
	 * use 'READ_ONCE' to fetch the name poपूर्णांकer.
	 *
	 * NOTE! Even अगर a नाम will mean that the length
	 * was not loaded atomically, we करोn't care. The
	 * RCU walk will check the sequence count eventually,
	 * and catch it. And we won't overrun the buffer,
	 * because we're पढ़ोing the name poपूर्णांकer atomically,
	 * and a dentry name is guaranteed to be properly
	 * terminated with a NUL byte.
	 *
	 * End result: even अगर 'len' is wrong, we'll निकास
	 * early because the data cannot match (there can
	 * be no NUL in the ct/tcount data)
	 */
	स्थिर अचिन्हित अक्षर *cs = READ_ONCE(dentry->d_name.name);

	वापस dentry_string_cmp(cs, ct, tcount);
पूर्ण

काष्ठा बाह्यal_name अणु
	जोड़ अणु
		atomic_t count;
		काष्ठा rcu_head head;
	पूर्ण u;
	अचिन्हित अक्षर name[];
पूर्ण;

अटल अंतरभूत काष्ठा बाह्यal_name *बाह्यal_name(काष्ठा dentry *dentry)
अणु
	वापस container_of(dentry->d_name.name, काष्ठा बाह्यal_name, name[0]);
पूर्ण

अटल व्योम __d_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा dentry *dentry = container_of(head, काष्ठा dentry, d_u.d_rcu);

	kmem_cache_मुक्त(dentry_cache, dentry); 
पूर्ण

अटल व्योम __d_मुक्त_बाह्यal(काष्ठा rcu_head *head)
अणु
	काष्ठा dentry *dentry = container_of(head, काष्ठा dentry, d_u.d_rcu);
	kमुक्त(बाह्यal_name(dentry));
	kmem_cache_मुक्त(dentry_cache, dentry);
पूर्ण

अटल अंतरभूत पूर्णांक dname_बाह्यal(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_name.name != dentry->d_iname;
पूर्ण

व्योम take_dentry_name_snapshot(काष्ठा name_snapshot *name, काष्ठा dentry *dentry)
अणु
	spin_lock(&dentry->d_lock);
	name->name = dentry->d_name;
	अगर (unlikely(dname_बाह्यal(dentry))) अणु
		atomic_inc(&बाह्यal_name(dentry)->u.count);
	पूर्ण अन्यथा अणु
		स_नकल(name->अंतरभूत_name, dentry->d_iname,
		       dentry->d_name.len + 1);
		name->name.name = name->अंतरभूत_name;
	पूर्ण
	spin_unlock(&dentry->d_lock);
पूर्ण
EXPORT_SYMBOL(take_dentry_name_snapshot);

व्योम release_dentry_name_snapshot(काष्ठा name_snapshot *name)
अणु
	अगर (unlikely(name->name.name != name->अंतरभूत_name)) अणु
		काष्ठा बाह्यal_name *p;
		p = container_of(name->name.name, काष्ठा बाह्यal_name, name[0]);
		अगर (unlikely(atomic_dec_and_test(&p->u.count)))
			kमुक्त_rcu(p, u.head);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(release_dentry_name_snapshot);

अटल अंतरभूत व्योम __d_set_inode_and_type(काष्ठा dentry *dentry,
					  काष्ठा inode *inode,
					  अचिन्हित type_flags)
अणु
	अचिन्हित flags;

	dentry->d_inode = inode;
	flags = READ_ONCE(dentry->d_flags);
	flags &= ~(DCACHE_ENTRY_TYPE | DCACHE_FALLTHRU);
	flags |= type_flags;
	smp_store_release(&dentry->d_flags, flags);
पूर्ण

अटल अंतरभूत व्योम __d_clear_type_and_inode(काष्ठा dentry *dentry)
अणु
	अचिन्हित flags = READ_ONCE(dentry->d_flags);

	flags &= ~(DCACHE_ENTRY_TYPE | DCACHE_FALLTHRU);
	WRITE_ONCE(dentry->d_flags, flags);
	dentry->d_inode = शून्य;
	अगर (dentry->d_flags & DCACHE_LRU_LIST)
		this_cpu_inc(nr_dentry_negative);
पूर्ण

अटल व्योम dentry_मुक्त(काष्ठा dentry *dentry)
अणु
	WARN_ON(!hlist_unhashed(&dentry->d_u.d_alias));
	अगर (unlikely(dname_बाह्यal(dentry))) अणु
		काष्ठा बाह्यal_name *p = बाह्यal_name(dentry);
		अगर (likely(atomic_dec_and_test(&p->u.count))) अणु
			call_rcu(&dentry->d_u.d_rcu, __d_मुक्त_बाह्यal);
			वापस;
		पूर्ण
	पूर्ण
	/* अगर dentry was never visible to RCU, immediate मुक्त is OK */
	अगर (dentry->d_flags & DCACHE_NORCU)
		__d_मुक्त(&dentry->d_u.d_rcu);
	अन्यथा
		call_rcu(&dentry->d_u.d_rcu, __d_मुक्त);
पूर्ण

/*
 * Release the dentry's inode, using the fileप्रणाली
 * d_iput() operation अगर defined.
 */
अटल व्योम dentry_unlink_inode(काष्ठा dentry * dentry)
	__releases(dentry->d_lock)
	__releases(dentry->d_inode->i_lock)
अणु
	काष्ठा inode *inode = dentry->d_inode;

	raw_ग_लिखो_seqcount_begin(&dentry->d_seq);
	__d_clear_type_and_inode(dentry);
	hlist_del_init(&dentry->d_u.d_alias);
	raw_ग_लिखो_seqcount_end(&dentry->d_seq);
	spin_unlock(&dentry->d_lock);
	spin_unlock(&inode->i_lock);
	अगर (!inode->i_nlink)
		fsnotअगरy_inodeहटाओ(inode);
	अगर (dentry->d_op && dentry->d_op->d_iput)
		dentry->d_op->d_iput(dentry, inode);
	अन्यथा
		iput(inode);
पूर्ण

/*
 * The DCACHE_LRU_LIST bit is set whenever the 'd_lru' entry
 * is in use - which includes both the "real" per-superblock
 * LRU list _and_ the DCACHE_SHRINK_LIST use.
 *
 * The DCACHE_SHRINK_LIST bit is set whenever the dentry is
 * on the shrink list (ie not on the superblock LRU list).
 *
 * The per-cpu "nr_dentry_unused" counters are updated with
 * the DCACHE_LRU_LIST bit.
 *
 * The per-cpu "nr_dentry_negative" counters are only updated
 * when deleted from or added to the per-superblock LRU list, not
 * from/to the shrink list. That is to aव्योम an unneeded dec/inc
 * pair when moving from LRU to shrink list in select_collect().
 *
 * These helper functions make sure we always follow the
 * rules. d_lock must be held by the caller.
 */
#घोषणा D_FLAG_VERIFY(dentry,x) WARN_ON_ONCE(((dentry)->d_flags & (DCACHE_LRU_LIST | DCACHE_SHRINK_LIST)) != (x))
अटल व्योम d_lru_add(काष्ठा dentry *dentry)
अणु
	D_FLAG_VERIFY(dentry, 0);
	dentry->d_flags |= DCACHE_LRU_LIST;
	this_cpu_inc(nr_dentry_unused);
	अगर (d_is_negative(dentry))
		this_cpu_inc(nr_dentry_negative);
	WARN_ON_ONCE(!list_lru_add(&dentry->d_sb->s_dentry_lru, &dentry->d_lru));
पूर्ण

अटल व्योम d_lru_del(काष्ठा dentry *dentry)
अणु
	D_FLAG_VERIFY(dentry, DCACHE_LRU_LIST);
	dentry->d_flags &= ~DCACHE_LRU_LIST;
	this_cpu_dec(nr_dentry_unused);
	अगर (d_is_negative(dentry))
		this_cpu_dec(nr_dentry_negative);
	WARN_ON_ONCE(!list_lru_del(&dentry->d_sb->s_dentry_lru, &dentry->d_lru));
पूर्ण

अटल व्योम d_shrink_del(काष्ठा dentry *dentry)
अणु
	D_FLAG_VERIFY(dentry, DCACHE_SHRINK_LIST | DCACHE_LRU_LIST);
	list_del_init(&dentry->d_lru);
	dentry->d_flags &= ~(DCACHE_SHRINK_LIST | DCACHE_LRU_LIST);
	this_cpu_dec(nr_dentry_unused);
पूर्ण

अटल व्योम d_shrink_add(काष्ठा dentry *dentry, काष्ठा list_head *list)
अणु
	D_FLAG_VERIFY(dentry, 0);
	list_add(&dentry->d_lru, list);
	dentry->d_flags |= DCACHE_SHRINK_LIST | DCACHE_LRU_LIST;
	this_cpu_inc(nr_dentry_unused);
पूर्ण

/*
 * These can only be called under the global LRU lock, ie during the
 * callback क्रम मुक्तing the LRU list. "isolate" हटाओs it from the
 * LRU lists entirely, जबतक shrink_move moves it to the indicated
 * निजी list.
 */
अटल व्योम d_lru_isolate(काष्ठा list_lru_one *lru, काष्ठा dentry *dentry)
अणु
	D_FLAG_VERIFY(dentry, DCACHE_LRU_LIST);
	dentry->d_flags &= ~DCACHE_LRU_LIST;
	this_cpu_dec(nr_dentry_unused);
	अगर (d_is_negative(dentry))
		this_cpu_dec(nr_dentry_negative);
	list_lru_isolate(lru, &dentry->d_lru);
पूर्ण

अटल व्योम d_lru_shrink_move(काष्ठा list_lru_one *lru, काष्ठा dentry *dentry,
			      काष्ठा list_head *list)
अणु
	D_FLAG_VERIFY(dentry, DCACHE_LRU_LIST);
	dentry->d_flags |= DCACHE_SHRINK_LIST;
	अगर (d_is_negative(dentry))
		this_cpu_dec(nr_dentry_negative);
	list_lru_isolate_move(lru, &dentry->d_lru, list);
पूर्ण

अटल व्योम ___d_drop(काष्ठा dentry *dentry)
अणु
	काष्ठा hlist_bl_head *b;
	/*
	 * Hashed dentries are normally on the dentry hashtable,
	 * with the exception of those newly allocated by
	 * d_obtain_root, which are always IS_ROOT:
	 */
	अगर (unlikely(IS_ROOT(dentry)))
		b = &dentry->d_sb->s_roots;
	अन्यथा
		b = d_hash(dentry->d_name.hash);

	hlist_bl_lock(b);
	__hlist_bl_del(&dentry->d_hash);
	hlist_bl_unlock(b);
पूर्ण

व्योम __d_drop(काष्ठा dentry *dentry)
अणु
	अगर (!d_unhashed(dentry)) अणु
		___d_drop(dentry);
		dentry->d_hash.pprev = शून्य;
		ग_लिखो_seqcount_invalidate(&dentry->d_seq);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__d_drop);

/**
 * d_drop - drop a dentry
 * @dentry: dentry to drop
 *
 * d_drop() unhashes the entry from the parent dentry hashes, so that it won't
 * be found through a VFS lookup any more. Note that this is dअगरferent from
 * deleting the dentry - d_delete will try to mark the dentry negative अगर
 * possible, giving a successful _negative_ lookup, जबतक d_drop will
 * just make the cache lookup fail.
 *
 * d_drop() is used मुख्यly क्रम stuff that wants to invalidate a dentry क्रम some
 * reason (NFS समयouts or स्वतःfs deletes).
 *
 * __d_drop requires dentry->d_lock
 *
 * ___d_drop करोesn't mark dentry as "unhashed"
 * (dentry->d_hash.pprev will be LIST_POISON2, not शून्य).
 */
व्योम d_drop(काष्ठा dentry *dentry)
अणु
	spin_lock(&dentry->d_lock);
	__d_drop(dentry);
	spin_unlock(&dentry->d_lock);
पूर्ण
EXPORT_SYMBOL(d_drop);

अटल अंतरभूत व्योम dentry_unlist(काष्ठा dentry *dentry, काष्ठा dentry *parent)
अणु
	काष्ठा dentry *next;
	/*
	 * Inक्रमm d_walk() and shrink_dentry_list() that we are no दीर्घer
	 * attached to the dentry tree
	 */
	dentry->d_flags |= DCACHE_DENTRY_KILLED;
	अगर (unlikely(list_empty(&dentry->d_child)))
		वापस;
	__list_del_entry(&dentry->d_child);
	/*
	 * Cursors can move around the list of children.  While we'd been
	 * a normal list member, it didn't matter - ->d_child.next would've
	 * been updated.  However, from now on it won't be and क्रम the
	 * things like d_walk() it might end up with a nasty surprise.
	 * Normally d_walk() करोesn't care about cursors moving around -
	 * ->d_lock on parent prevents that and since a cursor has no children
	 * of its own, we get through it without ever unlocking the parent.
	 * There is one exception, though - अगर we ascend from a child that
	 * माला_लो समाप्तed as soon as we unlock it, the next sibling is found
	 * using the value left in its ->d_child.next.  And अगर _that_
	 * poपूर्णांकed to a cursor, and cursor got moved (e.g. by lseek())
	 * beक्रमe d_walk() regains parent->d_lock, we'll end up skipping
	 * everything the cursor had been moved past.
	 *
	 * Solution: make sure that the poपूर्णांकer left behind in ->d_child.next
	 * poपूर्णांकs to something that won't be moving around.  I.e. skip the
	 * cursors.
	 */
	जबतक (dentry->d_child.next != &parent->d_subdirs) अणु
		next = list_entry(dentry->d_child.next, काष्ठा dentry, d_child);
		अगर (likely(!(next->d_flags & DCACHE_DENTRY_CURSOR)))
			अवरोध;
		dentry->d_child.next = next->d_child.next;
	पूर्ण
पूर्ण

अटल व्योम __dentry_समाप्त(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent = शून्य;
	bool can_मुक्त = true;
	अगर (!IS_ROOT(dentry))
		parent = dentry->d_parent;

	/*
	 * The dentry is now unrecoverably dead to the world.
	 */
	lockref_mark_dead(&dentry->d_lockref);

	/*
	 * inक्रमm the fs via d_prune that this dentry is about to be
	 * unhashed and destroyed.
	 */
	अगर (dentry->d_flags & DCACHE_OP_PRUNE)
		dentry->d_op->d_prune(dentry);

	अगर (dentry->d_flags & DCACHE_LRU_LIST) अणु
		अगर (!(dentry->d_flags & DCACHE_SHRINK_LIST))
			d_lru_del(dentry);
	पूर्ण
	/* अगर it was on the hash then हटाओ it */
	__d_drop(dentry);
	dentry_unlist(dentry, parent);
	अगर (parent)
		spin_unlock(&parent->d_lock);
	अगर (dentry->d_inode)
		dentry_unlink_inode(dentry);
	अन्यथा
		spin_unlock(&dentry->d_lock);
	this_cpu_dec(nr_dentry);
	अगर (dentry->d_op && dentry->d_op->d_release)
		dentry->d_op->d_release(dentry);

	spin_lock(&dentry->d_lock);
	अगर (dentry->d_flags & DCACHE_SHRINK_LIST) अणु
		dentry->d_flags |= DCACHE_MAY_FREE;
		can_मुक्त = false;
	पूर्ण
	spin_unlock(&dentry->d_lock);
	अगर (likely(can_मुक्त))
		dentry_मुक्त(dentry);
	cond_resched();
पूर्ण

अटल काष्ठा dentry *__lock_parent(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent;
	rcu_पढ़ो_lock();
	spin_unlock(&dentry->d_lock);
again:
	parent = READ_ONCE(dentry->d_parent);
	spin_lock(&parent->d_lock);
	/*
	 * We can't blindly lock dentry until we are sure
	 * that we won't violate the locking order.
	 * Any changes of dentry->d_parent must have
	 * been करोne with parent->d_lock held, so
	 * spin_lock() above is enough of a barrier
	 * क्रम checking अगर it's still our child.
	 */
	अगर (unlikely(parent != dentry->d_parent)) अणु
		spin_unlock(&parent->d_lock);
		जाओ again;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (parent != dentry)
		spin_lock_nested(&dentry->d_lock, DENTRY_D_LOCK_NESTED);
	अन्यथा
		parent = शून्य;
	वापस parent;
पूर्ण

अटल अंतरभूत काष्ठा dentry *lock_parent(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent = dentry->d_parent;
	अगर (IS_ROOT(dentry))
		वापस शून्य;
	अगर (likely(spin_trylock(&parent->d_lock)))
		वापस parent;
	वापस __lock_parent(dentry);
पूर्ण

अटल अंतरभूत bool retain_dentry(काष्ठा dentry *dentry)
अणु
	WARN_ON(d_in_lookup(dentry));

	/* Unreachable? Get rid of it */
	अगर (unlikely(d_unhashed(dentry)))
		वापस false;

	अगर (unlikely(dentry->d_flags & DCACHE_DISCONNECTED))
		वापस false;

	अगर (unlikely(dentry->d_flags & DCACHE_OP_DELETE)) अणु
		अगर (dentry->d_op->d_delete(dentry))
			वापस false;
	पूर्ण

	अगर (unlikely(dentry->d_flags & DCACHE_DONTCACHE))
		वापस false;

	/* retain; LRU fodder */
	dentry->d_lockref.count--;
	अगर (unlikely(!(dentry->d_flags & DCACHE_LRU_LIST)))
		d_lru_add(dentry);
	अन्यथा अगर (unlikely(!(dentry->d_flags & DCACHE_REFERENCED)))
		dentry->d_flags |= DCACHE_REFERENCED;
	वापस true;
पूर्ण

व्योम d_mark_करोntcache(काष्ठा inode *inode)
अणु
	काष्ठा dentry *de;

	spin_lock(&inode->i_lock);
	hlist_क्रम_each_entry(de, &inode->i_dentry, d_u.d_alias) अणु
		spin_lock(&de->d_lock);
		de->d_flags |= DCACHE_DONTCACHE;
		spin_unlock(&de->d_lock);
	पूर्ण
	inode->i_state |= I_DONTCACHE;
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL(d_mark_करोntcache);

/*
 * Finish off a dentry we've decided to समाप्त.
 * dentry->d_lock must be held, वापसs with it unlocked.
 * Returns dentry requiring refcount drop, or शून्य अगर we're करोne.
 */
अटल काष्ठा dentry *dentry_समाप्त(काष्ठा dentry *dentry)
	__releases(dentry->d_lock)
अणु
	काष्ठा inode *inode = dentry->d_inode;
	काष्ठा dentry *parent = शून्य;

	अगर (inode && unlikely(!spin_trylock(&inode->i_lock)))
		जाओ slow_positive;

	अगर (!IS_ROOT(dentry)) अणु
		parent = dentry->d_parent;
		अगर (unlikely(!spin_trylock(&parent->d_lock))) अणु
			parent = __lock_parent(dentry);
			अगर (likely(inode || !dentry->d_inode))
				जाओ got_locks;
			/* negative that became positive */
			अगर (parent)
				spin_unlock(&parent->d_lock);
			inode = dentry->d_inode;
			जाओ slow_positive;
		पूर्ण
	पूर्ण
	__dentry_समाप्त(dentry);
	वापस parent;

slow_positive:
	spin_unlock(&dentry->d_lock);
	spin_lock(&inode->i_lock);
	spin_lock(&dentry->d_lock);
	parent = lock_parent(dentry);
got_locks:
	अगर (unlikely(dentry->d_lockref.count != 1)) अणु
		dentry->d_lockref.count--;
	पूर्ण अन्यथा अगर (likely(!retain_dentry(dentry))) अणु
		__dentry_समाप्त(dentry);
		वापस parent;
	पूर्ण
	/* we are keeping it, after all */
	अगर (inode)
		spin_unlock(&inode->i_lock);
	अगर (parent)
		spin_unlock(&parent->d_lock);
	spin_unlock(&dentry->d_lock);
	वापस शून्य;
पूर्ण

/*
 * Try to करो a lockless dput(), and वापस whether that was successful.
 *
 * If unsuccessful, we वापस false, having alपढ़ोy taken the dentry lock.
 *
 * The caller needs to hold the RCU पढ़ो lock, so that the dentry is
 * guaranteed to stay around even अगर the refcount goes करोwn to zero!
 */
अटल अंतरभूत bool fast_dput(काष्ठा dentry *dentry)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक d_flags;

	/*
	 * If we have a d_op->d_delete() operation, we sould not
	 * let the dentry count go to zero, so use "put_or_lock".
	 */
	अगर (unlikely(dentry->d_flags & DCACHE_OP_DELETE))
		वापस lockref_put_or_lock(&dentry->d_lockref);

	/*
	 * .. otherwise, we can try to just decrement the
	 * lockref optimistically.
	 */
	ret = lockref_put_वापस(&dentry->d_lockref);

	/*
	 * If the lockref_put_वापस() failed due to the lock being held
	 * by somebody अन्यथा, the fast path has failed. We will need to
	 * get the lock, and then check the count again.
	 */
	अगर (unlikely(ret < 0)) अणु
		spin_lock(&dentry->d_lock);
		अगर (dentry->d_lockref.count > 1) अणु
			dentry->d_lockref.count--;
			spin_unlock(&dentry->d_lock);
			वापस true;
		पूर्ण
		वापस false;
	पूर्ण

	/*
	 * If we weren't the last ref, we're करोne.
	 */
	अगर (ret)
		वापस true;

	/*
	 * Careful, careful. The reference count went करोwn
	 * to zero, but we करोn't hold the dentry lock, so
	 * somebody अन्यथा could get it again, and करो another
	 * dput(), and we need to not race with that.
	 *
	 * However, there is a very special and common हाल
	 * where we करोn't care, because there is nothing to
	 * करो: the dentry is still hashed, it करोes not have
	 * a 'delete' op, and it's referenced and alपढ़ोy on
	 * the LRU list.
	 *
	 * NOTE! Since we aren't locked, these values are
	 * not "stable". However, it is sufficient that at
	 * some poपूर्णांक after we dropped the reference the
	 * dentry was hashed and the flags had the proper
	 * value. Other dentry users may have re-gotten
	 * a reference to the dentry and change that, but
	 * our work is करोne - we can leave the dentry
	 * around with a zero refcount.
	 *
	 * Nevertheless, there are two हालs that we should समाप्त
	 * the dentry anyway.
	 * 1. मुक्त disconnected dentries as soon as their refcount
	 *    reached zero.
	 * 2. मुक्त dentries अगर they should not be cached.
	 */
	smp_rmb();
	d_flags = READ_ONCE(dentry->d_flags);
	d_flags &= DCACHE_REFERENCED | DCACHE_LRU_LIST |
			DCACHE_DISCONNECTED | DCACHE_DONTCACHE;

	/* Nothing to करो? Dropping the reference was all we needed? */
	अगर (d_flags == (DCACHE_REFERENCED | DCACHE_LRU_LIST) && !d_unhashed(dentry))
		वापस true;

	/*
	 * Not the fast normal हाल? Get the lock. We've alपढ़ोy decremented
	 * the refcount, but we'll need to re-check the situation after
	 * getting the lock.
	 */
	spin_lock(&dentry->d_lock);

	/*
	 * Did somebody अन्यथा grab a reference to it in the meanसमय, and
	 * we're no दीर्घer the last user after all? Alternatively, somebody
	 * अन्यथा could have समाप्तed it and marked it dead. Either way, we
	 * करोn't need to करो anything अन्यथा.
	 */
	अगर (dentry->d_lockref.count) अणु
		spin_unlock(&dentry->d_lock);
		वापस true;
	पूर्ण

	/*
	 * Re-get the reference we optimistically dropped. We hold the
	 * lock, and we just tested that it was zero, so we can just
	 * set it to 1.
	 */
	dentry->d_lockref.count = 1;
	वापस false;
पूर्ण


/* 
 * This is dput
 *
 * This is complicated by the fact that we करो not want to put
 * dentries that are no दीर्घer on any hash chain on the unused
 * list: we'd much rather just get rid of them immediately.
 *
 * However, that implies that we have to traverse the dentry
 * tree upwards to the parents which might _also_ now be
 * scheduled क्रम deletion (it may have been only रुकोing क्रम
 * its last child to go away).
 *
 * This tail recursion is करोne by hand as we करोn't want to depend
 * on the compiler to always get this right (gcc generally करोesn't).
 * Real recursion would eat up our stack space.
 */

/*
 * dput - release a dentry
 * @dentry: dentry to release 
 *
 * Release a dentry. This will drop the usage count and अगर appropriate
 * call the dentry unlink method as well as removing it from the queues and
 * releasing its resources. If the parent dentries were scheduled क्रम release
 * they too may now get deleted.
 */
व्योम dput(काष्ठा dentry *dentry)
अणु
	जबतक (dentry) अणु
		might_sleep();

		rcu_पढ़ो_lock();
		अगर (likely(fast_dput(dentry))) अणु
			rcu_पढ़ो_unlock();
			वापस;
		पूर्ण

		/* Slow हाल: now with the dentry lock held */
		rcu_पढ़ो_unlock();

		अगर (likely(retain_dentry(dentry))) अणु
			spin_unlock(&dentry->d_lock);
			वापस;
		पूर्ण

		dentry = dentry_समाप्त(dentry);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dput);

अटल व्योम __dput_to_list(काष्ठा dentry *dentry, काष्ठा list_head *list)
__must_hold(&dentry->d_lock)
अणु
	अगर (dentry->d_flags & DCACHE_SHRINK_LIST) अणु
		/* let the owner of the list it's on deal with it */
		--dentry->d_lockref.count;
	पूर्ण अन्यथा अणु
		अगर (dentry->d_flags & DCACHE_LRU_LIST)
			d_lru_del(dentry);
		अगर (!--dentry->d_lockref.count)
			d_shrink_add(dentry, list);
	पूर्ण
पूर्ण

व्योम dput_to_list(काष्ठा dentry *dentry, काष्ठा list_head *list)
अणु
	rcu_पढ़ो_lock();
	अगर (likely(fast_dput(dentry))) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (!retain_dentry(dentry))
		__dput_to_list(dentry, list);
	spin_unlock(&dentry->d_lock);
पूर्ण

/* This must be called with d_lock held */
अटल अंतरभूत व्योम __dget_dlock(काष्ठा dentry *dentry)
अणु
	dentry->d_lockref.count++;
पूर्ण

अटल अंतरभूत व्योम __dget(काष्ठा dentry *dentry)
अणु
	lockref_get(&dentry->d_lockref);
पूर्ण

काष्ठा dentry *dget_parent(काष्ठा dentry *dentry)
अणु
	पूर्णांक gotref;
	काष्ठा dentry *ret;
	अचिन्हित seq;

	/*
	 * Do optimistic parent lookup without any
	 * locking.
	 */
	rcu_पढ़ो_lock();
	seq = raw_seqcount_begin(&dentry->d_seq);
	ret = READ_ONCE(dentry->d_parent);
	gotref = lockref_get_not_zero(&ret->d_lockref);
	rcu_पढ़ो_unlock();
	अगर (likely(gotref)) अणु
		अगर (!पढ़ो_seqcount_retry(&dentry->d_seq, seq))
			वापस ret;
		dput(ret);
	पूर्ण

repeat:
	/*
	 * Don't need rcu_dereference because we re-check it was correct under
	 * the lock.
	 */
	rcu_पढ़ो_lock();
	ret = dentry->d_parent;
	spin_lock(&ret->d_lock);
	अगर (unlikely(ret != dentry->d_parent)) अणु
		spin_unlock(&ret->d_lock);
		rcu_पढ़ो_unlock();
		जाओ repeat;
	पूर्ण
	rcu_पढ़ो_unlock();
	BUG_ON(!ret->d_lockref.count);
	ret->d_lockref.count++;
	spin_unlock(&ret->d_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dget_parent);

अटल काष्ठा dentry * __d_find_any_alias(काष्ठा inode *inode)
अणु
	काष्ठा dentry *alias;

	अगर (hlist_empty(&inode->i_dentry))
		वापस शून्य;
	alias = hlist_entry(inode->i_dentry.first, काष्ठा dentry, d_u.d_alias);
	__dget(alias);
	वापस alias;
पूर्ण

/**
 * d_find_any_alias - find any alias क्रम a given inode
 * @inode: inode to find an alias क्रम
 *
 * If any aliases exist क्रम the given inode, take and वापस a
 * reference क्रम one of them.  If no aliases exist, वापस %शून्य.
 */
काष्ठा dentry *d_find_any_alias(काष्ठा inode *inode)
अणु
	काष्ठा dentry *de;

	spin_lock(&inode->i_lock);
	de = __d_find_any_alias(inode);
	spin_unlock(&inode->i_lock);
	वापस de;
पूर्ण
EXPORT_SYMBOL(d_find_any_alias);

अटल काष्ठा dentry *__d_find_alias(काष्ठा inode *inode)
अणु
	काष्ठा dentry *alias;

	अगर (S_ISसूची(inode->i_mode))
		वापस __d_find_any_alias(inode);

	hlist_क्रम_each_entry(alias, &inode->i_dentry, d_u.d_alias) अणु
		spin_lock(&alias->d_lock);
 		अगर (!d_unhashed(alias)) अणु
			__dget_dlock(alias);
			spin_unlock(&alias->d_lock);
			वापस alias;
		पूर्ण
		spin_unlock(&alias->d_lock);
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * d_find_alias - grab a hashed alias of inode
 * @inode: inode in question
 *
 * If inode has a hashed alias, or is a directory and has any alias,
 * acquire the reference to alias and वापस it. Otherwise वापस शून्य.
 * Notice that अगर inode is a directory there can be only one alias and
 * it can be unhashed only अगर it has no children, or अगर it is the root
 * of a fileप्रणाली, or अगर the directory was नामd and d_revalidate
 * was the first vfs operation to notice.
 *
 * If the inode has an IS_ROOT, DCACHE_DISCONNECTED alias, then prefer
 * any other hashed alias over that one.
 */
काष्ठा dentry *d_find_alias(काष्ठा inode *inode)
अणु
	काष्ठा dentry *de = शून्य;

	अगर (!hlist_empty(&inode->i_dentry)) अणु
		spin_lock(&inode->i_lock);
		de = __d_find_alias(inode);
		spin_unlock(&inode->i_lock);
	पूर्ण
	वापस de;
पूर्ण
EXPORT_SYMBOL(d_find_alias);

/*
 *  Caller MUST be holding rcu_पढ़ो_lock() and be guaranteed
 *  that inode won't get मुक्तd until rcu_पढ़ो_unlock().
 */
काष्ठा dentry *d_find_alias_rcu(काष्ठा inode *inode)
अणु
	काष्ठा hlist_head *l = &inode->i_dentry;
	काष्ठा dentry *de = शून्य;

	spin_lock(&inode->i_lock);
	// ->i_dentry and ->i_rcu are colocated, but the latter won't be
	// used without having I_FREEING set, which means no aliases left
	अगर (likely(!(inode->i_state & I_FREEING) && !hlist_empty(l))) अणु
		अगर (S_ISसूची(inode->i_mode)) अणु
			de = hlist_entry(l->first, काष्ठा dentry, d_u.d_alias);
		पूर्ण अन्यथा अणु
			hlist_क्रम_each_entry(de, l, d_u.d_alias)
				अगर (!d_unhashed(de))
					अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&inode->i_lock);
	वापस de;
पूर्ण

/*
 *	Try to समाप्त dentries associated with this inode.
 * WARNING: you must own a reference to inode.
 */
व्योम d_prune_aliases(काष्ठा inode *inode)
अणु
	काष्ठा dentry *dentry;
restart:
	spin_lock(&inode->i_lock);
	hlist_क्रम_each_entry(dentry, &inode->i_dentry, d_u.d_alias) अणु
		spin_lock(&dentry->d_lock);
		अगर (!dentry->d_lockref.count) अणु
			काष्ठा dentry *parent = lock_parent(dentry);
			अगर (likely(!dentry->d_lockref.count)) अणु
				__dentry_समाप्त(dentry);
				dput(parent);
				जाओ restart;
			पूर्ण
			अगर (parent)
				spin_unlock(&parent->d_lock);
		पूर्ण
		spin_unlock(&dentry->d_lock);
	पूर्ण
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL(d_prune_aliases);

/*
 * Lock a dentry from shrink list.
 * Called under rcu_पढ़ो_lock() and dentry->d_lock; the क्रमmer
 * guarantees that nothing we access will be मुक्तd under us.
 * Note that dentry is *not* रक्षित from concurrent dentry_समाप्त(),
 * d_delete(), etc.
 *
 * Return false अगर dentry has been disrupted or grabbed, leaving
 * the caller to kick it off-list.  Otherwise, वापस true and have
 * that dentry's inode and parent both locked.
 */
अटल bool shrink_lock_dentry(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry *parent;

	अगर (dentry->d_lockref.count)
		वापस false;

	inode = dentry->d_inode;
	अगर (inode && unlikely(!spin_trylock(&inode->i_lock))) अणु
		spin_unlock(&dentry->d_lock);
		spin_lock(&inode->i_lock);
		spin_lock(&dentry->d_lock);
		अगर (unlikely(dentry->d_lockref.count))
			जाओ out;
		/* changed inode means that somebody had grabbed it */
		अगर (unlikely(inode != dentry->d_inode))
			जाओ out;
	पूर्ण

	parent = dentry->d_parent;
	अगर (IS_ROOT(dentry) || likely(spin_trylock(&parent->d_lock)))
		वापस true;

	spin_unlock(&dentry->d_lock);
	spin_lock(&parent->d_lock);
	अगर (unlikely(parent != dentry->d_parent)) अणु
		spin_unlock(&parent->d_lock);
		spin_lock(&dentry->d_lock);
		जाओ out;
	पूर्ण
	spin_lock_nested(&dentry->d_lock, DENTRY_D_LOCK_NESTED);
	अगर (likely(!dentry->d_lockref.count))
		वापस true;
	spin_unlock(&parent->d_lock);
out:
	अगर (inode)
		spin_unlock(&inode->i_lock);
	वापस false;
पूर्ण

व्योम shrink_dentry_list(काष्ठा list_head *list)
अणु
	जबतक (!list_empty(list)) अणु
		काष्ठा dentry *dentry, *parent;

		dentry = list_entry(list->prev, काष्ठा dentry, d_lru);
		spin_lock(&dentry->d_lock);
		rcu_पढ़ो_lock();
		अगर (!shrink_lock_dentry(dentry)) अणु
			bool can_मुक्त = false;
			rcu_पढ़ो_unlock();
			d_shrink_del(dentry);
			अगर (dentry->d_lockref.count < 0)
				can_मुक्त = dentry->d_flags & DCACHE_MAY_FREE;
			spin_unlock(&dentry->d_lock);
			अगर (can_मुक्त)
				dentry_मुक्त(dentry);
			जारी;
		पूर्ण
		rcu_पढ़ो_unlock();
		d_shrink_del(dentry);
		parent = dentry->d_parent;
		अगर (parent != dentry)
			__dput_to_list(parent, list);
		__dentry_समाप्त(dentry);
	पूर्ण
पूर्ण

अटल क्रमागत lru_status dentry_lru_isolate(काष्ठा list_head *item,
		काष्ठा list_lru_one *lru, spinlock_t *lru_lock, व्योम *arg)
अणु
	काष्ठा list_head *मुक्तable = arg;
	काष्ठा dentry	*dentry = container_of(item, काष्ठा dentry, d_lru);


	/*
	 * we are inverting the lru lock/dentry->d_lock here,
	 * so use a trylock. If we fail to get the lock, just skip
	 * it
	 */
	अगर (!spin_trylock(&dentry->d_lock))
		वापस LRU_SKIP;

	/*
	 * Referenced dentries are still in use. If they have active
	 * counts, just हटाओ them from the LRU. Otherwise give them
	 * another pass through the LRU.
	 */
	अगर (dentry->d_lockref.count) अणु
		d_lru_isolate(lru, dentry);
		spin_unlock(&dentry->d_lock);
		वापस LRU_REMOVED;
	पूर्ण

	अगर (dentry->d_flags & DCACHE_REFERENCED) अणु
		dentry->d_flags &= ~DCACHE_REFERENCED;
		spin_unlock(&dentry->d_lock);

		/*
		 * The list move itself will be made by the common LRU code. At
		 * this poपूर्णांक, we've dropped the dentry->d_lock but keep the
		 * lru lock. This is safe to करो, since every list movement is
		 * रक्षित by the lru lock even अगर both locks are held.
		 *
		 * This is guaranteed by the fact that all LRU management
		 * functions are पूर्णांकermediated by the LRU API calls like
		 * list_lru_add and list_lru_del. List movement in this file
		 * only ever occur through this functions or through callbacks
		 * like this one, that are called from the LRU API.
		 *
		 * The only exceptions to this are functions like
		 * shrink_dentry_list, and code that first checks क्रम the
		 * DCACHE_SHRINK_LIST flag.  Those are guaranteed to be
		 * operating only with stack provided lists after they are
		 * properly isolated from the मुख्य list.  It is thus, always a
		 * local access.
		 */
		वापस LRU_ROTATE;
	पूर्ण

	d_lru_shrink_move(lru, dentry, मुक्तable);
	spin_unlock(&dentry->d_lock);

	वापस LRU_REMOVED;
पूर्ण

/**
 * prune_dcache_sb - shrink the dcache
 * @sb: superblock
 * @sc: shrink control, passed to list_lru_shrink_walk()
 *
 * Attempt to shrink the superblock dcache LRU by @sc->nr_to_scan entries. This
 * is करोne when we need more memory and called from the superblock shrinker
 * function.
 *
 * This function may fail to मुक्त any resources अगर all the dentries are in
 * use.
 */
दीर्घ prune_dcache_sb(काष्ठा super_block *sb, काष्ठा shrink_control *sc)
अणु
	LIST_HEAD(dispose);
	दीर्घ मुक्तd;

	मुक्तd = list_lru_shrink_walk(&sb->s_dentry_lru, sc,
				     dentry_lru_isolate, &dispose);
	shrink_dentry_list(&dispose);
	वापस मुक्तd;
पूर्ण

अटल क्रमागत lru_status dentry_lru_isolate_shrink(काष्ठा list_head *item,
		काष्ठा list_lru_one *lru, spinlock_t *lru_lock, व्योम *arg)
अणु
	काष्ठा list_head *मुक्तable = arg;
	काष्ठा dentry	*dentry = container_of(item, काष्ठा dentry, d_lru);

	/*
	 * we are inverting the lru lock/dentry->d_lock here,
	 * so use a trylock. If we fail to get the lock, just skip
	 * it
	 */
	अगर (!spin_trylock(&dentry->d_lock))
		वापस LRU_SKIP;

	d_lru_shrink_move(lru, dentry, मुक्तable);
	spin_unlock(&dentry->d_lock);

	वापस LRU_REMOVED;
पूर्ण


/**
 * shrink_dcache_sb - shrink dcache क्रम a superblock
 * @sb: superblock
 *
 * Shrink the dcache क्रम the specअगरied super block. This is used to मुक्त
 * the dcache beक्रमe unmounting a file प्रणाली.
 */
व्योम shrink_dcache_sb(काष्ठा super_block *sb)
अणु
	करो अणु
		LIST_HEAD(dispose);

		list_lru_walk(&sb->s_dentry_lru,
			dentry_lru_isolate_shrink, &dispose, 1024);
		shrink_dentry_list(&dispose);
	पूर्ण जबतक (list_lru_count(&sb->s_dentry_lru) > 0);
पूर्ण
EXPORT_SYMBOL(shrink_dcache_sb);

/**
 * क्रमागत d_walk_ret - action to talke during tree walk
 * @D_WALK_CONTINUE:	contrinue walk
 * @D_WALK_QUIT:	quit walk
 * @D_WALK_NORETRY:	quit when retry is needed
 * @D_WALK_SKIP:	skip this dentry and its children
 */
क्रमागत d_walk_ret अणु
	D_WALK_CONTINUE,
	D_WALK_QUIT,
	D_WALK_NORETRY,
	D_WALK_SKIP,
पूर्ण;

/**
 * d_walk - walk the dentry tree
 * @parent:	start of walk
 * @data:	data passed to @enter() and @finish()
 * @enter:	callback when first entering the dentry
 *
 * The @enter() callbacks are called with d_lock held.
 */
अटल व्योम d_walk(काष्ठा dentry *parent, व्योम *data,
		   क्रमागत d_walk_ret (*enter)(व्योम *, काष्ठा dentry *))
अणु
	काष्ठा dentry *this_parent;
	काष्ठा list_head *next;
	अचिन्हित seq = 0;
	क्रमागत d_walk_ret ret;
	bool retry = true;

again:
	पढ़ो_seqbegin_or_lock(&नाम_lock, &seq);
	this_parent = parent;
	spin_lock(&this_parent->d_lock);

	ret = enter(data, this_parent);
	चयन (ret) अणु
	हाल D_WALK_CONTINUE:
		अवरोध;
	हाल D_WALK_QUIT:
	हाल D_WALK_SKIP:
		जाओ out_unlock;
	हाल D_WALK_NORETRY:
		retry = false;
		अवरोध;
	पूर्ण
repeat:
	next = this_parent->d_subdirs.next;
resume:
	जबतक (next != &this_parent->d_subdirs) अणु
		काष्ठा list_head *पंचांगp = next;
		काष्ठा dentry *dentry = list_entry(पंचांगp, काष्ठा dentry, d_child);
		next = पंचांगp->next;

		अगर (unlikely(dentry->d_flags & DCACHE_DENTRY_CURSOR))
			जारी;

		spin_lock_nested(&dentry->d_lock, DENTRY_D_LOCK_NESTED);

		ret = enter(data, dentry);
		चयन (ret) अणु
		हाल D_WALK_CONTINUE:
			अवरोध;
		हाल D_WALK_QUIT:
			spin_unlock(&dentry->d_lock);
			जाओ out_unlock;
		हाल D_WALK_NORETRY:
			retry = false;
			अवरोध;
		हाल D_WALK_SKIP:
			spin_unlock(&dentry->d_lock);
			जारी;
		पूर्ण

		अगर (!list_empty(&dentry->d_subdirs)) अणु
			spin_unlock(&this_parent->d_lock);
			spin_release(&dentry->d_lock.dep_map, _RET_IP_);
			this_parent = dentry;
			spin_acquire(&this_parent->d_lock.dep_map, 0, 1, _RET_IP_);
			जाओ repeat;
		पूर्ण
		spin_unlock(&dentry->d_lock);
	पूर्ण
	/*
	 * All करोne at this level ... ascend and resume the search.
	 */
	rcu_पढ़ो_lock();
ascend:
	अगर (this_parent != parent) अणु
		काष्ठा dentry *child = this_parent;
		this_parent = child->d_parent;

		spin_unlock(&child->d_lock);
		spin_lock(&this_parent->d_lock);

		/* might go back up the wrong parent अगर we have had a नाम. */
		अगर (need_seqretry(&नाम_lock, seq))
			जाओ नाम_retry;
		/* go पूर्णांकo the first sibling still alive */
		करो अणु
			next = child->d_child.next;
			अगर (next == &this_parent->d_subdirs)
				जाओ ascend;
			child = list_entry(next, काष्ठा dentry, d_child);
		पूर्ण जबतक (unlikely(child->d_flags & DCACHE_DENTRY_KILLED));
		rcu_पढ़ो_unlock();
		जाओ resume;
	पूर्ण
	अगर (need_seqretry(&नाम_lock, seq))
		जाओ नाम_retry;
	rcu_पढ़ो_unlock();

out_unlock:
	spin_unlock(&this_parent->d_lock);
	करोne_seqretry(&नाम_lock, seq);
	वापस;

नाम_retry:
	spin_unlock(&this_parent->d_lock);
	rcu_पढ़ो_unlock();
	BUG_ON(seq & 1);
	अगर (!retry)
		वापस;
	seq = 1;
	जाओ again;
पूर्ण

काष्ठा check_mount अणु
	काष्ठा vfsmount *mnt;
	अचिन्हित पूर्णांक mounted;
पूर्ण;

अटल क्रमागत d_walk_ret path_check_mount(व्योम *data, काष्ठा dentry *dentry)
अणु
	काष्ठा check_mount *info = data;
	काष्ठा path path = अणु .mnt = info->mnt, .dentry = dentry पूर्ण;

	अगर (likely(!d_mountpoपूर्णांक(dentry)))
		वापस D_WALK_CONTINUE;
	अगर (__path_is_mountpoपूर्णांक(&path)) अणु
		info->mounted = 1;
		वापस D_WALK_QUIT;
	पूर्ण
	वापस D_WALK_CONTINUE;
पूर्ण

/**
 * path_has_submounts - check क्रम mounts over a dentry in the
 *                      current namespace.
 * @parent: path to check.
 *
 * Return true अगर the parent or its subdirectories contain
 * a mount poपूर्णांक in the current namespace.
 */
पूर्णांक path_has_submounts(स्थिर काष्ठा path *parent)
अणु
	काष्ठा check_mount data = अणु .mnt = parent->mnt, .mounted = 0 पूर्ण;

	पढ़ो_seqlock_excl(&mount_lock);
	d_walk(parent->dentry, &data, path_check_mount);
	पढ़ो_sequnlock_excl(&mount_lock);

	वापस data.mounted;
पूर्ण
EXPORT_SYMBOL(path_has_submounts);

/*
 * Called by mount code to set a mountpoपूर्णांक and check अगर the mountpoपूर्णांक is
 * reachable (e.g. NFS can unhash a directory dentry and then the complete
 * subtree can become unreachable).
 *
 * Only one of d_invalidate() and d_set_mounted() must succeed.  For
 * this reason take नाम_lock and d_lock on dentry and ancestors.
 */
पूर्णांक d_set_mounted(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *p;
	पूर्णांक ret = -ENOENT;
	ग_लिखो_seqlock(&नाम_lock);
	क्रम (p = dentry->d_parent; !IS_ROOT(p); p = p->d_parent) अणु
		/* Need exclusion wrt. d_invalidate() */
		spin_lock(&p->d_lock);
		अगर (unlikely(d_unhashed(p))) अणु
			spin_unlock(&p->d_lock);
			जाओ out;
		पूर्ण
		spin_unlock(&p->d_lock);
	पूर्ण
	spin_lock(&dentry->d_lock);
	अगर (!d_unlinked(dentry)) अणु
		ret = -EBUSY;
		अगर (!d_mountpoपूर्णांक(dentry)) अणु
			dentry->d_flags |= DCACHE_MOUNTED;
			ret = 0;
		पूर्ण
	पूर्ण
 	spin_unlock(&dentry->d_lock);
out:
	ग_लिखो_sequnlock(&नाम_lock);
	वापस ret;
पूर्ण

/*
 * Search the dentry child list of the specअगरied parent,
 * and move any unused dentries to the end of the unused
 * list क्रम prune_dcache(). We descend to the next level
 * whenever the d_subdirs list is non-empty and जारी
 * searching.
 *
 * It वापसs zero अगरf there are no unused children,
 * otherwise  it वापसs the number of children moved to
 * the end of the unused list. This may not be the total
 * number of unused children, because select_parent can
 * drop the lock and वापस early due to latency
 * स्थिरraपूर्णांकs.
 */

काष्ठा select_data अणु
	काष्ठा dentry *start;
	जोड़ अणु
		दीर्घ found;
		काष्ठा dentry *victim;
	पूर्ण;
	काष्ठा list_head dispose;
पूर्ण;

अटल क्रमागत d_walk_ret select_collect(व्योम *_data, काष्ठा dentry *dentry)
अणु
	काष्ठा select_data *data = _data;
	क्रमागत d_walk_ret ret = D_WALK_CONTINUE;

	अगर (data->start == dentry)
		जाओ out;

	अगर (dentry->d_flags & DCACHE_SHRINK_LIST) अणु
		data->found++;
	पूर्ण अन्यथा अणु
		अगर (dentry->d_flags & DCACHE_LRU_LIST)
			d_lru_del(dentry);
		अगर (!dentry->d_lockref.count) अणु
			d_shrink_add(dentry, &data->dispose);
			data->found++;
		पूर्ण
	पूर्ण
	/*
	 * We can वापस to the caller अगर we have found some (this
	 * ensures क्रमward progress). We'll be coming back to find
	 * the rest.
	 */
	अगर (!list_empty(&data->dispose))
		ret = need_resched() ? D_WALK_QUIT : D_WALK_NORETRY;
out:
	वापस ret;
पूर्ण

अटल क्रमागत d_walk_ret select_collect2(व्योम *_data, काष्ठा dentry *dentry)
अणु
	काष्ठा select_data *data = _data;
	क्रमागत d_walk_ret ret = D_WALK_CONTINUE;

	अगर (data->start == dentry)
		जाओ out;

	अगर (dentry->d_flags & DCACHE_SHRINK_LIST) अणु
		अगर (!dentry->d_lockref.count) अणु
			rcu_पढ़ो_lock();
			data->victim = dentry;
			वापस D_WALK_QUIT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dentry->d_flags & DCACHE_LRU_LIST)
			d_lru_del(dentry);
		अगर (!dentry->d_lockref.count)
			d_shrink_add(dentry, &data->dispose);
	पूर्ण
	/*
	 * We can वापस to the caller अगर we have found some (this
	 * ensures क्रमward progress). We'll be coming back to find
	 * the rest.
	 */
	अगर (!list_empty(&data->dispose))
		ret = need_resched() ? D_WALK_QUIT : D_WALK_NORETRY;
out:
	वापस ret;
पूर्ण

/**
 * shrink_dcache_parent - prune dcache
 * @parent: parent of entries to prune
 *
 * Prune the dcache to हटाओ unused children of the parent dentry.
 */
व्योम shrink_dcache_parent(काष्ठा dentry *parent)
अणु
	क्रम (;;) अणु
		काष्ठा select_data data = अणु.start = parentपूर्ण;

		INIT_LIST_HEAD(&data.dispose);
		d_walk(parent, &data, select_collect);

		अगर (!list_empty(&data.dispose)) अणु
			shrink_dentry_list(&data.dispose);
			जारी;
		पूर्ण

		cond_resched();
		अगर (!data.found)
			अवरोध;
		data.victim = शून्य;
		d_walk(parent, &data, select_collect2);
		अगर (data.victim) अणु
			काष्ठा dentry *parent;
			spin_lock(&data.victim->d_lock);
			अगर (!shrink_lock_dentry(data.victim)) अणु
				spin_unlock(&data.victim->d_lock);
				rcu_पढ़ो_unlock();
			पूर्ण अन्यथा अणु
				rcu_पढ़ो_unlock();
				parent = data.victim->d_parent;
				अगर (parent != data.victim)
					__dput_to_list(parent, &data.dispose);
				__dentry_समाप्त(data.victim);
			पूर्ण
		पूर्ण
		अगर (!list_empty(&data.dispose))
			shrink_dentry_list(&data.dispose);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(shrink_dcache_parent);

अटल क्रमागत d_walk_ret umount_check(व्योम *_data, काष्ठा dentry *dentry)
अणु
	/* it has busy descendents; complain about those instead */
	अगर (!list_empty(&dentry->d_subdirs))
		वापस D_WALK_CONTINUE;

	/* root with refcount 1 is fine */
	अगर (dentry == _data && dentry->d_lockref.count == 1)
		वापस D_WALK_CONTINUE;

	prपूर्णांकk(KERN_ERR "BUG: Dentry %p{i=%lx,n=%pd} "
			" still in use (%d) [unmount of %s %s]\n",
		       dentry,
		       dentry->d_inode ?
		       dentry->d_inode->i_ino : 0UL,
		       dentry,
		       dentry->d_lockref.count,
		       dentry->d_sb->s_type->name,
		       dentry->d_sb->s_id);
	WARN_ON(1);
	वापस D_WALK_CONTINUE;
पूर्ण

अटल व्योम करो_one_tree(काष्ठा dentry *dentry)
अणु
	shrink_dcache_parent(dentry);
	d_walk(dentry, dentry, umount_check);
	d_drop(dentry);
	dput(dentry);
पूर्ण

/*
 * destroy the dentries attached to a superblock on unmounting
 */
व्योम shrink_dcache_क्रम_umount(काष्ठा super_block *sb)
अणु
	काष्ठा dentry *dentry;

	WARN(करोwn_पढ़ो_trylock(&sb->s_umount), "s_umount should've been locked");

	dentry = sb->s_root;
	sb->s_root = शून्य;
	करो_one_tree(dentry);

	जबतक (!hlist_bl_empty(&sb->s_roots)) अणु
		dentry = dget(hlist_bl_entry(hlist_bl_first(&sb->s_roots), काष्ठा dentry, d_hash));
		करो_one_tree(dentry);
	पूर्ण
पूर्ण

अटल क्रमागत d_walk_ret find_submount(व्योम *_data, काष्ठा dentry *dentry)
अणु
	काष्ठा dentry **victim = _data;
	अगर (d_mountpoपूर्णांक(dentry)) अणु
		__dget_dlock(dentry);
		*victim = dentry;
		वापस D_WALK_QUIT;
	पूर्ण
	वापस D_WALK_CONTINUE;
पूर्ण

/**
 * d_invalidate - detach submounts, prune dcache, and drop
 * @dentry: dentry to invalidate (aka detach, prune and drop)
 */
व्योम d_invalidate(काष्ठा dentry *dentry)
अणु
	bool had_submounts = false;
	spin_lock(&dentry->d_lock);
	अगर (d_unhashed(dentry)) अणु
		spin_unlock(&dentry->d_lock);
		वापस;
	पूर्ण
	__d_drop(dentry);
	spin_unlock(&dentry->d_lock);

	/* Negative dentries can be dropped without further checks */
	अगर (!dentry->d_inode)
		वापस;

	shrink_dcache_parent(dentry);
	क्रम (;;) अणु
		काष्ठा dentry *victim = शून्य;
		d_walk(dentry, &victim, find_submount);
		अगर (!victim) अणु
			अगर (had_submounts)
				shrink_dcache_parent(dentry);
			वापस;
		पूर्ण
		had_submounts = true;
		detach_mounts(victim);
		dput(victim);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(d_invalidate);

/**
 * __d_alloc	-	allocate a dcache entry
 * @sb: fileप्रणाली it will beदीर्घ to
 * @name: qstr of the name
 *
 * Allocates a dentry. It वापसs %शून्य अगर there is insufficient memory
 * available. On a success the dentry is वापसed. The name passed in is
 * copied and the copy passed in may be reused after this call.
 */
 
अटल काष्ठा dentry *__d_alloc(काष्ठा super_block *sb, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा dentry *dentry;
	अक्षर *dname;
	पूर्णांक err;

	dentry = kmem_cache_alloc(dentry_cache, GFP_KERNEL);
	अगर (!dentry)
		वापस शून्य;

	/*
	 * We guarantee that the अंतरभूत name is always NUL-terminated.
	 * This way the स_नकल() करोne by the name चयनing in नाम
	 * will still always have a NUL at the end, even अगर we might
	 * be overwriting an पूर्णांकernal NUL अक्षरacter
	 */
	dentry->d_iname[DNAME_INLINE_LEN-1] = 0;
	अगर (unlikely(!name)) अणु
		name = &slash_name;
		dname = dentry->d_iname;
	पूर्ण अन्यथा अगर (name->len > DNAME_INLINE_LEN-1) अणु
		माप_प्रकार size = दुरत्व(काष्ठा बाह्यal_name, name[1]);
		काष्ठा बाह्यal_name *p = kदो_स्मृति(size + name->len,
						  GFP_KERNEL_ACCOUNT |
						  __GFP_RECLAIMABLE);
		अगर (!p) अणु
			kmem_cache_मुक्त(dentry_cache, dentry); 
			वापस शून्य;
		पूर्ण
		atomic_set(&p->u.count, 1);
		dname = p->name;
	पूर्ण अन्यथा  अणु
		dname = dentry->d_iname;
	पूर्ण	

	dentry->d_name.len = name->len;
	dentry->d_name.hash = name->hash;
	स_नकल(dname, name->name, name->len);
	dname[name->len] = 0;

	/* Make sure we always see the terminating NUL अक्षरacter */
	smp_store_release(&dentry->d_name.name, dname); /* ^^^ */

	dentry->d_lockref.count = 1;
	dentry->d_flags = 0;
	spin_lock_init(&dentry->d_lock);
	seqcount_spinlock_init(&dentry->d_seq, &dentry->d_lock);
	dentry->d_inode = शून्य;
	dentry->d_parent = dentry;
	dentry->d_sb = sb;
	dentry->d_op = शून्य;
	dentry->d_fsdata = शून्य;
	INIT_HLIST_BL_NODE(&dentry->d_hash);
	INIT_LIST_HEAD(&dentry->d_lru);
	INIT_LIST_HEAD(&dentry->d_subdirs);
	INIT_HLIST_NODE(&dentry->d_u.d_alias);
	INIT_LIST_HEAD(&dentry->d_child);
	d_set_d_op(dentry, dentry->d_sb->s_d_op);

	अगर (dentry->d_op && dentry->d_op->d_init) अणु
		err = dentry->d_op->d_init(dentry);
		अगर (err) अणु
			अगर (dname_बाह्यal(dentry))
				kमुक्त(बाह्यal_name(dentry));
			kmem_cache_मुक्त(dentry_cache, dentry);
			वापस शून्य;
		पूर्ण
	पूर्ण

	this_cpu_inc(nr_dentry);

	वापस dentry;
पूर्ण

/**
 * d_alloc	-	allocate a dcache entry
 * @parent: parent of entry to allocate
 * @name: qstr of the name
 *
 * Allocates a dentry. It वापसs %शून्य अगर there is insufficient memory
 * available. On a success the dentry is वापसed. The name passed in is
 * copied and the copy passed in may be reused after this call.
 */
काष्ठा dentry *d_alloc(काष्ठा dentry * parent, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा dentry *dentry = __d_alloc(parent->d_sb, name);
	अगर (!dentry)
		वापस शून्य;
	spin_lock(&parent->d_lock);
	/*
	 * करोn't need child lock because it is not subject
	 * to concurrency here
	 */
	__dget_dlock(parent);
	dentry->d_parent = parent;
	list_add(&dentry->d_child, &parent->d_subdirs);
	spin_unlock(&parent->d_lock);

	वापस dentry;
पूर्ण
EXPORT_SYMBOL(d_alloc);

काष्ठा dentry *d_alloc_anon(काष्ठा super_block *sb)
अणु
	वापस __d_alloc(sb, शून्य);
पूर्ण
EXPORT_SYMBOL(d_alloc_anon);

काष्ठा dentry *d_alloc_cursor(काष्ठा dentry * parent)
अणु
	काष्ठा dentry *dentry = d_alloc_anon(parent->d_sb);
	अगर (dentry) अणु
		dentry->d_flags |= DCACHE_DENTRY_CURSOR;
		dentry->d_parent = dget(parent);
	पूर्ण
	वापस dentry;
पूर्ण

/**
 * d_alloc_pseuकरो - allocate a dentry (क्रम lookup-less fileप्रणालीs)
 * @sb: the superblock
 * @name: qstr of the name
 *
 * For a fileप्रणाली that just pins its dentries in memory and never
 * perक्रमms lookups at all, वापस an unhashed IS_ROOT dentry.
 * This is used क्रम pipes, sockets et.al. - the stuff that should
 * never be anyone's children or parents.  Unlike all other
 * dentries, these will not have RCU delay between dropping the
 * last reference and मुक्तing them.
 *
 * The only user is alloc_file_pseuकरो() and that's what should
 * be considered a खुला पूर्णांकerface.  Don't use directly.
 */
काष्ठा dentry *d_alloc_pseuकरो(काष्ठा super_block *sb, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा dentry *dentry = __d_alloc(sb, name);
	अगर (likely(dentry))
		dentry->d_flags |= DCACHE_NORCU;
	वापस dentry;
पूर्ण

काष्ठा dentry *d_alloc_name(काष्ठा dentry *parent, स्थिर अक्षर *name)
अणु
	काष्ठा qstr q;

	q.name = name;
	q.hash_len = hashlen_string(parent, name);
	वापस d_alloc(parent, &q);
पूर्ण
EXPORT_SYMBOL(d_alloc_name);

व्योम d_set_d_op(काष्ठा dentry *dentry, स्थिर काष्ठा dentry_operations *op)
अणु
	WARN_ON_ONCE(dentry->d_op);
	WARN_ON_ONCE(dentry->d_flags & (DCACHE_OP_HASH	|
				DCACHE_OP_COMPARE	|
				DCACHE_OP_REVALIDATE	|
				DCACHE_OP_WEAK_REVALIDATE	|
				DCACHE_OP_DELETE	|
				DCACHE_OP_REAL));
	dentry->d_op = op;
	अगर (!op)
		वापस;
	अगर (op->d_hash)
		dentry->d_flags |= DCACHE_OP_HASH;
	अगर (op->d_compare)
		dentry->d_flags |= DCACHE_OP_COMPARE;
	अगर (op->d_revalidate)
		dentry->d_flags |= DCACHE_OP_REVALIDATE;
	अगर (op->d_weak_revalidate)
		dentry->d_flags |= DCACHE_OP_WEAK_REVALIDATE;
	अगर (op->d_delete)
		dentry->d_flags |= DCACHE_OP_DELETE;
	अगर (op->d_prune)
		dentry->d_flags |= DCACHE_OP_PRUNE;
	अगर (op->d_real)
		dentry->d_flags |= DCACHE_OP_REAL;

पूर्ण
EXPORT_SYMBOL(d_set_d_op);


/*
 * d_set_fallthru - Mark a dentry as falling through to a lower layer
 * @dentry - The dentry to mark
 *
 * Mark a dentry as falling through to the lower layer (as set with
 * d_pin_lower()).  This flag may be recorded on the medium.
 */
व्योम d_set_fallthru(काष्ठा dentry *dentry)
अणु
	spin_lock(&dentry->d_lock);
	dentry->d_flags |= DCACHE_FALLTHRU;
	spin_unlock(&dentry->d_lock);
पूर्ण
EXPORT_SYMBOL(d_set_fallthru);

अटल अचिन्हित d_flags_क्रम_inode(काष्ठा inode *inode)
अणु
	अचिन्हित add_flags = DCACHE_REGULAR_TYPE;

	अगर (!inode)
		वापस DCACHE_MISS_TYPE;

	अगर (S_ISसूची(inode->i_mode)) अणु
		add_flags = DCACHE_सूचीECTORY_TYPE;
		अगर (unlikely(!(inode->i_opflags & IOP_LOOKUP))) अणु
			अगर (unlikely(!inode->i_op->lookup))
				add_flags = DCACHE_AUTOसूची_TYPE;
			अन्यथा
				inode->i_opflags |= IOP_LOOKUP;
		पूर्ण
		जाओ type_determined;
	पूर्ण

	अगर (unlikely(!(inode->i_opflags & IOP_NOFOLLOW))) अणु
		अगर (unlikely(inode->i_op->get_link)) अणु
			add_flags = DCACHE_SYMLINK_TYPE;
			जाओ type_determined;
		पूर्ण
		inode->i_opflags |= IOP_NOFOLLOW;
	पूर्ण

	अगर (unlikely(!S_ISREG(inode->i_mode)))
		add_flags = DCACHE_SPECIAL_TYPE;

type_determined:
	अगर (unlikely(IS_AUTOMOUNT(inode)))
		add_flags |= DCACHE_NEED_AUTOMOUNT;
	वापस add_flags;
पूर्ण

अटल व्योम __d_instantiate(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	अचिन्हित add_flags = d_flags_क्रम_inode(inode);
	WARN_ON(d_in_lookup(dentry));

	spin_lock(&dentry->d_lock);
	/*
	 * Decrement negative dentry count अगर it was in the LRU list.
	 */
	अगर (dentry->d_flags & DCACHE_LRU_LIST)
		this_cpu_dec(nr_dentry_negative);
	hlist_add_head(&dentry->d_u.d_alias, &inode->i_dentry);
	raw_ग_लिखो_seqcount_begin(&dentry->d_seq);
	__d_set_inode_and_type(dentry, inode, add_flags);
	raw_ग_लिखो_seqcount_end(&dentry->d_seq);
	fsnotअगरy_update_flags(dentry);
	spin_unlock(&dentry->d_lock);
पूर्ण

/**
 * d_instantiate - fill in inode inक्रमmation क्रम a dentry
 * @entry: dentry to complete
 * @inode: inode to attach to this dentry
 *
 * Fill in inode inक्रमmation in the entry.
 *
 * This turns negative dentries पूर्णांकo productive full members
 * of society.
 *
 * NOTE! This assumes that the inode count has been incremented
 * (or otherwise set) by the caller to indicate that it is now
 * in use by the dcache.
 */
 
व्योम d_instantiate(काष्ठा dentry *entry, काष्ठा inode * inode)
अणु
	BUG_ON(!hlist_unhashed(&entry->d_u.d_alias));
	अगर (inode) अणु
		security_d_instantiate(entry, inode);
		spin_lock(&inode->i_lock);
		__d_instantiate(entry, inode);
		spin_unlock(&inode->i_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(d_instantiate);

/*
 * This should be equivalent to d_instantiate() + unlock_new_inode(),
 * with lockdep-related part of unlock_new_inode() करोne beक्रमe
 * anything अन्यथा.  Use that instead of खोलो-coding d_instantiate()/
 * unlock_new_inode() combinations.
 */
व्योम d_instantiate_new(काष्ठा dentry *entry, काष्ठा inode *inode)
अणु
	BUG_ON(!hlist_unhashed(&entry->d_u.d_alias));
	BUG_ON(!inode);
	lockdep_annotate_inode_mutex_key(inode);
	security_d_instantiate(entry, inode);
	spin_lock(&inode->i_lock);
	__d_instantiate(entry, inode);
	WARN_ON(!(inode->i_state & I_NEW));
	inode->i_state &= ~I_NEW & ~I_CREATING;
	smp_mb();
	wake_up_bit(&inode->i_state, __I_NEW);
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL(d_instantiate_new);

काष्ठा dentry *d_make_root(काष्ठा inode *root_inode)
अणु
	काष्ठा dentry *res = शून्य;

	अगर (root_inode) अणु
		res = d_alloc_anon(root_inode->i_sb);
		अगर (res)
			d_instantiate(res, root_inode);
		अन्यथा
			iput(root_inode);
	पूर्ण
	वापस res;
पूर्ण
EXPORT_SYMBOL(d_make_root);

अटल काष्ठा dentry *__d_instantiate_anon(काष्ठा dentry *dentry,
					   काष्ठा inode *inode,
					   bool disconnected)
अणु
	काष्ठा dentry *res;
	अचिन्हित add_flags;

	security_d_instantiate(dentry, inode);
	spin_lock(&inode->i_lock);
	res = __d_find_any_alias(inode);
	अगर (res) अणु
		spin_unlock(&inode->i_lock);
		dput(dentry);
		जाओ out_iput;
	पूर्ण

	/* attach a disconnected dentry */
	add_flags = d_flags_क्रम_inode(inode);

	अगर (disconnected)
		add_flags |= DCACHE_DISCONNECTED;

	spin_lock(&dentry->d_lock);
	__d_set_inode_and_type(dentry, inode, add_flags);
	hlist_add_head(&dentry->d_u.d_alias, &inode->i_dentry);
	अगर (!disconnected) अणु
		hlist_bl_lock(&dentry->d_sb->s_roots);
		hlist_bl_add_head(&dentry->d_hash, &dentry->d_sb->s_roots);
		hlist_bl_unlock(&dentry->d_sb->s_roots);
	पूर्ण
	spin_unlock(&dentry->d_lock);
	spin_unlock(&inode->i_lock);

	वापस dentry;

 out_iput:
	iput(inode);
	वापस res;
पूर्ण

काष्ठा dentry *d_instantiate_anon(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	वापस __d_instantiate_anon(dentry, inode, true);
पूर्ण
EXPORT_SYMBOL(d_instantiate_anon);

अटल काष्ठा dentry *__d_obtain_alias(काष्ठा inode *inode, bool disconnected)
अणु
	काष्ठा dentry *पंचांगp;
	काष्ठा dentry *res;

	अगर (!inode)
		वापस ERR_PTR(-ESTALE);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	res = d_find_any_alias(inode);
	अगर (res)
		जाओ out_iput;

	पंचांगp = d_alloc_anon(inode->i_sb);
	अगर (!पंचांगp) अणु
		res = ERR_PTR(-ENOMEM);
		जाओ out_iput;
	पूर्ण

	वापस __d_instantiate_anon(पंचांगp, inode, disconnected);

out_iput:
	iput(inode);
	वापस res;
पूर्ण

/**
 * d_obtain_alias - find or allocate a DISCONNECTED dentry क्रम a given inode
 * @inode: inode to allocate the dentry क्रम
 *
 * Obtain a dentry क्रम an inode resulting from NFS filehandle conversion or
 * similar खोलो by handle operations.  The वापसed dentry may be anonymous,
 * or may have a full name (अगर the inode was alपढ़ोy in the cache).
 *
 * When called on a directory inode, we must ensure that the inode only ever
 * has one dentry.  If a dentry is found, that is वापसed instead of
 * allocating a new one.
 *
 * On successful वापस, the reference to the inode has been transferred
 * to the dentry.  In हाल of an error the reference on the inode is released.
 * To make it easier to use in export operations a %शून्य or IS_ERR inode may
 * be passed in and the error will be propagated to the वापस value,
 * with a %शून्य @inode replaced by ERR_PTR(-ESTALE).
 */
काष्ठा dentry *d_obtain_alias(काष्ठा inode *inode)
अणु
	वापस __d_obtain_alias(inode, true);
पूर्ण
EXPORT_SYMBOL(d_obtain_alias);

/**
 * d_obtain_root - find or allocate a dentry क्रम a given inode
 * @inode: inode to allocate the dentry क्रम
 *
 * Obtain an IS_ROOT dentry क्रम the root of a fileप्रणाली.
 *
 * We must ensure that directory inodes only ever have one dentry.  If a
 * dentry is found, that is वापसed instead of allocating a new one.
 *
 * On successful वापस, the reference to the inode has been transferred
 * to the dentry.  In हाल of an error the reference on the inode is
 * released.  A %शून्य or IS_ERR inode may be passed in and will be the
 * error will be propagate to the वापस value, with a %शून्य @inode
 * replaced by ERR_PTR(-ESTALE).
 */
काष्ठा dentry *d_obtain_root(काष्ठा inode *inode)
अणु
	वापस __d_obtain_alias(inode, false);
पूर्ण
EXPORT_SYMBOL(d_obtain_root);

/**
 * d_add_ci - lookup or allocate new dentry with हाल-exact name
 * @inode:  the inode हाल-insensitive lookup has found
 * @dentry: the negative dentry that was passed to the parent's lookup func
 * @name:   the हाल-exact name to be associated with the वापसed dentry
 *
 * This is to aव्योम filling the dcache with हाल-insensitive names to the
 * same inode, only the actual correct हाल is stored in the dcache क्रम
 * हाल-insensitive fileप्रणालीs.
 *
 * For a हाल-insensitive lookup match and अगर the हाल-exact dentry
 * alपढ़ोy exists in the dcache, use it and वापस it.
 *
 * If no entry exists with the exact हाल name, allocate new dentry with
 * the exact हाल, and वापस the spliced entry.
 */
काष्ठा dentry *d_add_ci(काष्ठा dentry *dentry, काष्ठा inode *inode,
			काष्ठा qstr *name)
अणु
	काष्ठा dentry *found, *res;

	/*
	 * First check अगर a dentry matching the name alपढ़ोy exists,
	 * अगर not go ahead and create it now.
	 */
	found = d_hash_and_lookup(dentry->d_parent, name);
	अगर (found) अणु
		iput(inode);
		वापस found;
	पूर्ण
	अगर (d_in_lookup(dentry)) अणु
		found = d_alloc_parallel(dentry->d_parent, name,
					dentry->d_रुको);
		अगर (IS_ERR(found) || !d_in_lookup(found)) अणु
			iput(inode);
			वापस found;
		पूर्ण
	पूर्ण अन्यथा अणु
		found = d_alloc(dentry->d_parent, name);
		अगर (!found) अणु
			iput(inode);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण 
	पूर्ण
	res = d_splice_alias(inode, found);
	अगर (res) अणु
		dput(found);
		वापस res;
	पूर्ण
	वापस found;
पूर्ण
EXPORT_SYMBOL(d_add_ci);


अटल अंतरभूत bool d_same_name(स्थिर काष्ठा dentry *dentry,
				स्थिर काष्ठा dentry *parent,
				स्थिर काष्ठा qstr *name)
अणु
	अगर (likely(!(parent->d_flags & DCACHE_OP_COMPARE))) अणु
		अगर (dentry->d_name.len != name->len)
			वापस false;
		वापस dentry_cmp(dentry, name->name, name->len) == 0;
	पूर्ण
	वापस parent->d_op->d_compare(dentry,
				       dentry->d_name.len, dentry->d_name.name,
				       name) == 0;
पूर्ण

/**
 * __d_lookup_rcu - search क्रम a dentry (racy, store-मुक्त)
 * @parent: parent dentry
 * @name: qstr of name we wish to find
 * @seqp: वापसs d_seq value at the poपूर्णांक where the dentry was found
 * Returns: dentry, or शून्य
 *
 * __d_lookup_rcu is the dcache lookup function क्रम rcu-walk name
 * resolution (store-मुक्त path walking) design described in
 * Documentation/fileप्रणालीs/path-lookup.txt.
 *
 * This is not to be used outside core vfs.
 *
 * __d_lookup_rcu must only be used in rcu-walk mode, ie. with vfsmount lock
 * held, and rcu_पढ़ो_lock held. The वापसed dentry must not be stored पूर्णांकo
 * without taking d_lock and checking d_seq sequence count against @seq
 * वापसed here.
 *
 * A refcount may be taken on the found dentry with the d_rcu_to_refcount
 * function.
 *
 * Alternatively, __d_lookup_rcu may be called again to look up the child of
 * the वापसed dentry, so दीर्घ as its parent's seqlock is checked after the
 * child is looked up. Thus, an पूर्णांकerlocking stepping of sequence lock checks
 * is क्रमmed, giving पूर्णांकegrity करोwn the path walk.
 *
 * NOTE! The caller *has* to check the resulting dentry against the sequence
 * number we've वापसed beक्रमe using any of the resulting dentry state!
 */
काष्ठा dentry *__d_lookup_rcu(स्थिर काष्ठा dentry *parent,
				स्थिर काष्ठा qstr *name,
				अचिन्हित *seqp)
अणु
	u64 hashlen = name->hash_len;
	स्थिर अचिन्हित अक्षर *str = name->name;
	काष्ठा hlist_bl_head *b = d_hash(hashlen_hash(hashlen));
	काष्ठा hlist_bl_node *node;
	काष्ठा dentry *dentry;

	/*
	 * Note: There is signअगरicant duplication with __d_lookup_rcu which is
	 * required to prevent single thपढ़ोed perक्रमmance regressions
	 * especially on architectures where smp_rmb (in seqcounts) are costly.
	 * Keep the two functions in sync.
	 */

	/*
	 * The hash list is रक्षित using RCU.
	 *
	 * Carefully use d_seq when comparing a candidate dentry, to aव्योम
	 * races with d_move().
	 *
	 * It is possible that concurrent नामs can mess up our list
	 * walk here and result in missing our dentry, resulting in the
	 * false-negative result. d_lookup() protects against concurrent
	 * नामs using नाम_lock seqlock.
	 *
	 * See Documentation/fileप्रणालीs/path-lookup.txt क्रम more details.
	 */
	hlist_bl_क्रम_each_entry_rcu(dentry, node, b, d_hash) अणु
		अचिन्हित seq;

seqretry:
		/*
		 * The dentry sequence count protects us from concurrent
		 * नामs, and thus protects parent and name fields.
		 *
		 * The caller must perक्रमm a seqcount check in order
		 * to करो anything useful with the वापसed dentry.
		 *
		 * NOTE! We करो a "raw" seqcount_begin here. That means that
		 * we करोn't रुको क्रम the sequence count to stabilize अगर it
		 * is in the middle of a sequence change. If we करो the slow
		 * dentry compare, we will करो seqretries until it is stable,
		 * and अगर we end up with a successful lookup, we actually
		 * want to निकास RCU lookup anyway.
		 *
		 * Note that raw_seqcount_begin still *करोes* smp_rmb(), so
		 * we are still guaranteed NUL-termination of ->d_name.name.
		 */
		seq = raw_seqcount_begin(&dentry->d_seq);
		अगर (dentry->d_parent != parent)
			जारी;
		अगर (d_unhashed(dentry))
			जारी;

		अगर (unlikely(parent->d_flags & DCACHE_OP_COMPARE)) अणु
			पूर्णांक tlen;
			स्थिर अक्षर *tname;
			अगर (dentry->d_name.hash != hashlen_hash(hashlen))
				जारी;
			tlen = dentry->d_name.len;
			tname = dentry->d_name.name;
			/* we want a consistent (name,len) pair */
			अगर (पढ़ो_seqcount_retry(&dentry->d_seq, seq)) अणु
				cpu_relax();
				जाओ seqretry;
			पूर्ण
			अगर (parent->d_op->d_compare(dentry,
						    tlen, tname, name) != 0)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (dentry->d_name.hash_len != hashlen)
				जारी;
			अगर (dentry_cmp(dentry, str, hashlen_len(hashlen)) != 0)
				जारी;
		पूर्ण
		*seqp = seq;
		वापस dentry;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * d_lookup - search क्रम a dentry
 * @parent: parent dentry
 * @name: qstr of name we wish to find
 * Returns: dentry, or शून्य
 *
 * d_lookup searches the children of the parent dentry क्रम the name in
 * question. If the dentry is found its reference count is incremented and the
 * dentry is वापसed. The caller must use dput to मुक्त the entry when it has
 * finished using it. %शून्य is वापसed अगर the dentry करोes not exist.
 */
काष्ठा dentry *d_lookup(स्थिर काष्ठा dentry *parent, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा dentry *dentry;
	अचिन्हित seq;

	करो अणु
		seq = पढ़ो_seqbegin(&नाम_lock);
		dentry = __d_lookup(parent, name);
		अगर (dentry)
			अवरोध;
	पूर्ण जबतक (पढ़ो_seqretry(&नाम_lock, seq));
	वापस dentry;
पूर्ण
EXPORT_SYMBOL(d_lookup);

/**
 * __d_lookup - search क्रम a dentry (racy)
 * @parent: parent dentry
 * @name: qstr of name we wish to find
 * Returns: dentry, or शून्य
 *
 * __d_lookup is like d_lookup, however it may (rarely) वापस a
 * false-negative result due to unrelated नाम activity.
 *
 * __d_lookup is slightly faster by aव्योमing नाम_lock पढ़ो seqlock,
 * however it must be used carefully, eg. with a following d_lookup in
 * the हाल of failure.
 *
 * __d_lookup callers must be commented.
 */
काष्ठा dentry *__d_lookup(स्थिर काष्ठा dentry *parent, स्थिर काष्ठा qstr *name)
अणु
	अचिन्हित पूर्णांक hash = name->hash;
	काष्ठा hlist_bl_head *b = d_hash(hash);
	काष्ठा hlist_bl_node *node;
	काष्ठा dentry *found = शून्य;
	काष्ठा dentry *dentry;

	/*
	 * Note: There is signअगरicant duplication with __d_lookup_rcu which is
	 * required to prevent single thपढ़ोed perक्रमmance regressions
	 * especially on architectures where smp_rmb (in seqcounts) are costly.
	 * Keep the two functions in sync.
	 */

	/*
	 * The hash list is रक्षित using RCU.
	 *
	 * Take d_lock when comparing a candidate dentry, to aव्योम races
	 * with d_move().
	 *
	 * It is possible that concurrent नामs can mess up our list
	 * walk here and result in missing our dentry, resulting in the
	 * false-negative result. d_lookup() protects against concurrent
	 * नामs using नाम_lock seqlock.
	 *
	 * See Documentation/fileप्रणालीs/path-lookup.txt क्रम more details.
	 */
	rcu_पढ़ो_lock();
	
	hlist_bl_क्रम_each_entry_rcu(dentry, node, b, d_hash) अणु

		अगर (dentry->d_name.hash != hash)
			जारी;

		spin_lock(&dentry->d_lock);
		अगर (dentry->d_parent != parent)
			जाओ next;
		अगर (d_unhashed(dentry))
			जाओ next;

		अगर (!d_same_name(dentry, parent, name))
			जाओ next;

		dentry->d_lockref.count++;
		found = dentry;
		spin_unlock(&dentry->d_lock);
		अवरोध;
next:
		spin_unlock(&dentry->d_lock);
 	पूर्ण
 	rcu_पढ़ो_unlock();

 	वापस found;
पूर्ण

/**
 * d_hash_and_lookup - hash the qstr then search क्रम a dentry
 * @dir: Directory to search in
 * @name: qstr of name we wish to find
 *
 * On lookup failure शून्य is वापसed; on bad name - ERR_PTR(-error)
 */
काष्ठा dentry *d_hash_and_lookup(काष्ठा dentry *dir, काष्ठा qstr *name)
अणु
	/*
	 * Check क्रम a fs-specअगरic hash function. Note that we must
	 * calculate the standard hash first, as the d_op->d_hash()
	 * routine may choose to leave the hash value unchanged.
	 */
	name->hash = full_name_hash(dir, name->name, name->len);
	अगर (dir->d_flags & DCACHE_OP_HASH) अणु
		पूर्णांक err = dir->d_op->d_hash(dir, name);
		अगर (unlikely(err < 0))
			वापस ERR_PTR(err);
	पूर्ण
	वापस d_lookup(dir, name);
पूर्ण
EXPORT_SYMBOL(d_hash_and_lookup);

/*
 * When a file is deleted, we have two options:
 * - turn this dentry पूर्णांकo a negative dentry
 * - unhash this dentry and मुक्त it.
 *
 * Usually, we want to just turn this पूर्णांकo
 * a negative dentry, but अगर anybody अन्यथा is
 * currently using the dentry or the inode
 * we can't करो that and we fall back on removing
 * it from the hash queues and रुकोing क्रम
 * it to be deleted later when it has no users
 */
 
/**
 * d_delete - delete a dentry
 * @dentry: The dentry to delete
 *
 * Turn the dentry पूर्णांकo a negative dentry अगर possible, otherwise
 * हटाओ it from the hash queues so it can be deleted later
 */
 
व्योम d_delete(काष्ठा dentry * dentry)
अणु
	काष्ठा inode *inode = dentry->d_inode;

	spin_lock(&inode->i_lock);
	spin_lock(&dentry->d_lock);
	/*
	 * Are we the only user?
	 */
	अगर (dentry->d_lockref.count == 1) अणु
		dentry->d_flags &= ~DCACHE_CANT_MOUNT;
		dentry_unlink_inode(dentry);
	पूर्ण अन्यथा अणु
		__d_drop(dentry);
		spin_unlock(&dentry->d_lock);
		spin_unlock(&inode->i_lock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(d_delete);

अटल व्योम __d_rehash(काष्ठा dentry *entry)
अणु
	काष्ठा hlist_bl_head *b = d_hash(entry->d_name.hash);

	hlist_bl_lock(b);
	hlist_bl_add_head_rcu(&entry->d_hash, b);
	hlist_bl_unlock(b);
पूर्ण

/**
 * d_rehash	- add an entry back to the hash
 * @entry: dentry to add to the hash
 *
 * Adds a dentry to the hash according to its name.
 */
 
व्योम d_rehash(काष्ठा dentry * entry)
अणु
	spin_lock(&entry->d_lock);
	__d_rehash(entry);
	spin_unlock(&entry->d_lock);
पूर्ण
EXPORT_SYMBOL(d_rehash);

अटल अंतरभूत अचिन्हित start_dir_add(काष्ठा inode *dir)
अणु

	क्रम (;;) अणु
		अचिन्हित n = dir->i_dir_seq;
		अगर (!(n & 1) && cmpxchg(&dir->i_dir_seq, n, n + 1) == n)
			वापस n;
		cpu_relax();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम end_dir_add(काष्ठा inode *dir, अचिन्हित n)
अणु
	smp_store_release(&dir->i_dir_seq, n + 2);
पूर्ण

अटल व्योम d_रुको_lookup(काष्ठा dentry *dentry)
अणु
	अगर (d_in_lookup(dentry)) अणु
		DECLARE_WAITQUEUE(रुको, current);
		add_रुको_queue(dentry->d_रुको, &रुको);
		करो अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			spin_unlock(&dentry->d_lock);
			schedule();
			spin_lock(&dentry->d_lock);
		पूर्ण जबतक (d_in_lookup(dentry));
	पूर्ण
पूर्ण

काष्ठा dentry *d_alloc_parallel(काष्ठा dentry *parent,
				स्थिर काष्ठा qstr *name,
				रुको_queue_head_t *wq)
अणु
	अचिन्हित पूर्णांक hash = name->hash;
	काष्ठा hlist_bl_head *b = in_lookup_hash(parent, hash);
	काष्ठा hlist_bl_node *node;
	काष्ठा dentry *new = d_alloc(parent, name);
	काष्ठा dentry *dentry;
	अचिन्हित seq, r_seq, d_seq;

	अगर (unlikely(!new))
		वापस ERR_PTR(-ENOMEM);

retry:
	rcu_पढ़ो_lock();
	seq = smp_load_acquire(&parent->d_inode->i_dir_seq);
	r_seq = पढ़ो_seqbegin(&नाम_lock);
	dentry = __d_lookup_rcu(parent, name, &d_seq);
	अगर (unlikely(dentry)) अणु
		अगर (!lockref_get_not_dead(&dentry->d_lockref)) अणु
			rcu_पढ़ो_unlock();
			जाओ retry;
		पूर्ण
		अगर (पढ़ो_seqcount_retry(&dentry->d_seq, d_seq)) अणु
			rcu_पढ़ो_unlock();
			dput(dentry);
			जाओ retry;
		पूर्ण
		rcu_पढ़ो_unlock();
		dput(new);
		वापस dentry;
	पूर्ण
	अगर (unlikely(पढ़ो_seqretry(&नाम_lock, r_seq))) अणु
		rcu_पढ़ो_unlock();
		जाओ retry;
	पूर्ण

	अगर (unlikely(seq & 1)) अणु
		rcu_पढ़ो_unlock();
		जाओ retry;
	पूर्ण

	hlist_bl_lock(b);
	अगर (unlikely(READ_ONCE(parent->d_inode->i_dir_seq) != seq)) अणु
		hlist_bl_unlock(b);
		rcu_पढ़ो_unlock();
		जाओ retry;
	पूर्ण
	/*
	 * No changes क्रम the parent since the beginning of d_lookup().
	 * Since all removals from the chain happen with hlist_bl_lock(),
	 * any potential in-lookup matches are going to stay here until
	 * we unlock the chain.  All fields are stable in everything
	 * we encounter.
	 */
	hlist_bl_क्रम_each_entry(dentry, node, b, d_u.d_in_lookup_hash) अणु
		अगर (dentry->d_name.hash != hash)
			जारी;
		अगर (dentry->d_parent != parent)
			जारी;
		अगर (!d_same_name(dentry, parent, name))
			जारी;
		hlist_bl_unlock(b);
		/* now we can try to grab a reference */
		अगर (!lockref_get_not_dead(&dentry->d_lockref)) अणु
			rcu_पढ़ो_unlock();
			जाओ retry;
		पूर्ण

		rcu_पढ़ो_unlock();
		/*
		 * somebody is likely to be still करोing lookup क्रम it;
		 * रुको क्रम them to finish
		 */
		spin_lock(&dentry->d_lock);
		d_रुको_lookup(dentry);
		/*
		 * it's not in-lookup anymore; in principle we should repeat
		 * everything from dcache lookup, but it's likely to be what
		 * d_lookup() would've found anyway.  If it is, just वापस it;
		 * otherwise we really have to repeat the whole thing.
		 */
		अगर (unlikely(dentry->d_name.hash != hash))
			जाओ mismatch;
		अगर (unlikely(dentry->d_parent != parent))
			जाओ mismatch;
		अगर (unlikely(d_unhashed(dentry)))
			जाओ mismatch;
		अगर (unlikely(!d_same_name(dentry, parent, name)))
			जाओ mismatch;
		/* OK, it *is* a hashed match; वापस it */
		spin_unlock(&dentry->d_lock);
		dput(new);
		वापस dentry;
	पूर्ण
	rcu_पढ़ो_unlock();
	/* we can't take ->d_lock here; it's OK, though. */
	new->d_flags |= DCACHE_PAR_LOOKUP;
	new->d_रुको = wq;
	hlist_bl_add_head_rcu(&new->d_u.d_in_lookup_hash, b);
	hlist_bl_unlock(b);
	वापस new;
mismatch:
	spin_unlock(&dentry->d_lock);
	dput(dentry);
	जाओ retry;
पूर्ण
EXPORT_SYMBOL(d_alloc_parallel);

व्योम __d_lookup_करोne(काष्ठा dentry *dentry)
अणु
	काष्ठा hlist_bl_head *b = in_lookup_hash(dentry->d_parent,
						 dentry->d_name.hash);
	hlist_bl_lock(b);
	dentry->d_flags &= ~DCACHE_PAR_LOOKUP;
	__hlist_bl_del(&dentry->d_u.d_in_lookup_hash);
	wake_up_all(dentry->d_रुको);
	dentry->d_रुको = शून्य;
	hlist_bl_unlock(b);
	INIT_HLIST_NODE(&dentry->d_u.d_alias);
	INIT_LIST_HEAD(&dentry->d_lru);
पूर्ण
EXPORT_SYMBOL(__d_lookup_करोne);

/* inode->i_lock held अगर inode is non-शून्य */

अटल अंतरभूत व्योम __d_add(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = शून्य;
	अचिन्हित n;
	spin_lock(&dentry->d_lock);
	अगर (unlikely(d_in_lookup(dentry))) अणु
		dir = dentry->d_parent->d_inode;
		n = start_dir_add(dir);
		__d_lookup_करोne(dentry);
	पूर्ण
	अगर (inode) अणु
		अचिन्हित add_flags = d_flags_क्रम_inode(inode);
		hlist_add_head(&dentry->d_u.d_alias, &inode->i_dentry);
		raw_ग_लिखो_seqcount_begin(&dentry->d_seq);
		__d_set_inode_and_type(dentry, inode, add_flags);
		raw_ग_लिखो_seqcount_end(&dentry->d_seq);
		fsnotअगरy_update_flags(dentry);
	पूर्ण
	__d_rehash(dentry);
	अगर (dir)
		end_dir_add(dir, n);
	spin_unlock(&dentry->d_lock);
	अगर (inode)
		spin_unlock(&inode->i_lock);
पूर्ण

/**
 * d_add - add dentry to hash queues
 * @entry: dentry to add
 * @inode: The inode to attach to this dentry
 *
 * This adds the entry to the hash queues and initializes @inode.
 * The entry was actually filled in earlier during d_alloc().
 */

व्योम d_add(काष्ठा dentry *entry, काष्ठा inode *inode)
अणु
	अगर (inode) अणु
		security_d_instantiate(entry, inode);
		spin_lock(&inode->i_lock);
	पूर्ण
	__d_add(entry, inode);
पूर्ण
EXPORT_SYMBOL(d_add);

/**
 * d_exact_alias - find and hash an exact unhashed alias
 * @entry: dentry to add
 * @inode: The inode to go with this dentry
 *
 * If an unhashed dentry with the same name/parent and desired
 * inode alपढ़ोy exists, hash and वापस it.  Otherwise, वापस
 * शून्य.
 *
 * Parent directory should be locked.
 */
काष्ठा dentry *d_exact_alias(काष्ठा dentry *entry, काष्ठा inode *inode)
अणु
	काष्ठा dentry *alias;
	अचिन्हित पूर्णांक hash = entry->d_name.hash;

	spin_lock(&inode->i_lock);
	hlist_क्रम_each_entry(alias, &inode->i_dentry, d_u.d_alias) अणु
		/*
		 * Don't need alias->d_lock here, because aliases with
		 * d_parent == entry->d_parent are not subject to name or
		 * parent changes, because the parent inode i_mutex is held.
		 */
		अगर (alias->d_name.hash != hash)
			जारी;
		अगर (alias->d_parent != entry->d_parent)
			जारी;
		अगर (!d_same_name(alias, entry->d_parent, &entry->d_name))
			जारी;
		spin_lock(&alias->d_lock);
		अगर (!d_unhashed(alias)) अणु
			spin_unlock(&alias->d_lock);
			alias = शून्य;
		पूर्ण अन्यथा अणु
			__dget_dlock(alias);
			__d_rehash(alias);
			spin_unlock(&alias->d_lock);
		पूर्ण
		spin_unlock(&inode->i_lock);
		वापस alias;
	पूर्ण
	spin_unlock(&inode->i_lock);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(d_exact_alias);

अटल व्योम swap_names(काष्ठा dentry *dentry, काष्ठा dentry *target)
अणु
	अगर (unlikely(dname_बाह्यal(target))) अणु
		अगर (unlikely(dname_बाह्यal(dentry))) अणु
			/*
			 * Both बाह्यal: swap the poपूर्णांकers
			 */
			swap(target->d_name.name, dentry->d_name.name);
		पूर्ण अन्यथा अणु
			/*
			 * dentry:पूर्णांकernal, target:बाह्यal.  Steal target's
			 * storage and make target पूर्णांकernal.
			 */
			स_नकल(target->d_iname, dentry->d_name.name,
					dentry->d_name.len + 1);
			dentry->d_name.name = target->d_name.name;
			target->d_name.name = target->d_iname;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(dname_बाह्यal(dentry))) अणु
			/*
			 * dentry:बाह्यal, target:पूर्णांकernal.  Give dentry's
			 * storage to target and make dentry पूर्णांकernal
			 */
			स_नकल(dentry->d_iname, target->d_name.name,
					target->d_name.len + 1);
			target->d_name.name = dentry->d_name.name;
			dentry->d_name.name = dentry->d_iname;
		पूर्ण अन्यथा अणु
			/*
			 * Both are पूर्णांकernal.
			 */
			अचिन्हित पूर्णांक i;
			BUILD_BUG_ON(!IS_ALIGNED(DNAME_INLINE_LEN, माप(दीर्घ)));
			क्रम (i = 0; i < DNAME_INLINE_LEN / माप(दीर्घ); i++) अणु
				swap(((दीर्घ *) &dentry->d_iname)[i],
				     ((दीर्घ *) &target->d_iname)[i]);
			पूर्ण
		पूर्ण
	पूर्ण
	swap(dentry->d_name.hash_len, target->d_name.hash_len);
पूर्ण

अटल व्योम copy_name(काष्ठा dentry *dentry, काष्ठा dentry *target)
अणु
	काष्ठा बाह्यal_name *old_name = शून्य;
	अगर (unlikely(dname_बाह्यal(dentry)))
		old_name = बाह्यal_name(dentry);
	अगर (unlikely(dname_बाह्यal(target))) अणु
		atomic_inc(&बाह्यal_name(target)->u.count);
		dentry->d_name = target->d_name;
	पूर्ण अन्यथा अणु
		स_नकल(dentry->d_iname, target->d_name.name,
				target->d_name.len + 1);
		dentry->d_name.name = dentry->d_iname;
		dentry->d_name.hash_len = target->d_name.hash_len;
	पूर्ण
	अगर (old_name && likely(atomic_dec_and_test(&old_name->u.count)))
		kमुक्त_rcu(old_name, u.head);
पूर्ण

/*
 * __d_move - move a dentry
 * @dentry: entry to move
 * @target: new dentry
 * @exchange: exchange the two dentries
 *
 * Update the dcache to reflect the move of a file name. Negative
 * dcache entries should not be moved in this way. Caller must hold
 * नाम_lock, the i_mutex of the source and target directories,
 * and the sb->s_vfs_नाम_mutex अगर they dअगरfer. See lock_नाम().
 */
अटल व्योम __d_move(काष्ठा dentry *dentry, काष्ठा dentry *target,
		     bool exchange)
अणु
	काष्ठा dentry *old_parent, *p;
	काष्ठा inode *dir = शून्य;
	अचिन्हित n;

	WARN_ON(!dentry->d_inode);
	अगर (WARN_ON(dentry == target))
		वापस;

	BUG_ON(d_ancestor(target, dentry));
	old_parent = dentry->d_parent;
	p = d_ancestor(old_parent, target);
	अगर (IS_ROOT(dentry)) अणु
		BUG_ON(p);
		spin_lock(&target->d_parent->d_lock);
	पूर्ण अन्यथा अगर (!p) अणु
		/* target is not a descendent of dentry->d_parent */
		spin_lock(&target->d_parent->d_lock);
		spin_lock_nested(&old_parent->d_lock, DENTRY_D_LOCK_NESTED);
	पूर्ण अन्यथा अणु
		BUG_ON(p == dentry);
		spin_lock(&old_parent->d_lock);
		अगर (p != target)
			spin_lock_nested(&target->d_parent->d_lock,
					DENTRY_D_LOCK_NESTED);
	पूर्ण
	spin_lock_nested(&dentry->d_lock, 2);
	spin_lock_nested(&target->d_lock, 3);

	अगर (unlikely(d_in_lookup(target))) अणु
		dir = target->d_parent->d_inode;
		n = start_dir_add(dir);
		__d_lookup_करोne(target);
	पूर्ण

	ग_लिखो_seqcount_begin(&dentry->d_seq);
	ग_लिखो_seqcount_begin_nested(&target->d_seq, DENTRY_D_LOCK_NESTED);

	/* unhash both */
	अगर (!d_unhashed(dentry))
		___d_drop(dentry);
	अगर (!d_unhashed(target))
		___d_drop(target);

	/* ... and चयन them in the tree */
	dentry->d_parent = target->d_parent;
	अगर (!exchange) अणु
		copy_name(dentry, target);
		target->d_hash.pprev = शून्य;
		dentry->d_parent->d_lockref.count++;
		अगर (dentry != old_parent) /* wasn't IS_ROOT */
			WARN_ON(!--old_parent->d_lockref.count);
	पूर्ण अन्यथा अणु
		target->d_parent = old_parent;
		swap_names(dentry, target);
		list_move(&target->d_child, &target->d_parent->d_subdirs);
		__d_rehash(target);
		fsnotअगरy_update_flags(target);
	पूर्ण
	list_move(&dentry->d_child, &dentry->d_parent->d_subdirs);
	__d_rehash(dentry);
	fsnotअगरy_update_flags(dentry);
	fscrypt_handle_d_move(dentry);

	ग_लिखो_seqcount_end(&target->d_seq);
	ग_लिखो_seqcount_end(&dentry->d_seq);

	अगर (dir)
		end_dir_add(dir, n);

	अगर (dentry->d_parent != old_parent)
		spin_unlock(&dentry->d_parent->d_lock);
	अगर (dentry != old_parent)
		spin_unlock(&old_parent->d_lock);
	spin_unlock(&target->d_lock);
	spin_unlock(&dentry->d_lock);
पूर्ण

/*
 * d_move - move a dentry
 * @dentry: entry to move
 * @target: new dentry
 *
 * Update the dcache to reflect the move of a file name. Negative
 * dcache entries should not be moved in this way. See the locking
 * requirements क्रम __d_move.
 */
व्योम d_move(काष्ठा dentry *dentry, काष्ठा dentry *target)
अणु
	ग_लिखो_seqlock(&नाम_lock);
	__d_move(dentry, target, false);
	ग_लिखो_sequnlock(&नाम_lock);
पूर्ण
EXPORT_SYMBOL(d_move);

/*
 * d_exchange - exchange two dentries
 * @dentry1: first dentry
 * @dentry2: second dentry
 */
व्योम d_exchange(काष्ठा dentry *dentry1, काष्ठा dentry *dentry2)
अणु
	ग_लिखो_seqlock(&नाम_lock);

	WARN_ON(!dentry1->d_inode);
	WARN_ON(!dentry2->d_inode);
	WARN_ON(IS_ROOT(dentry1));
	WARN_ON(IS_ROOT(dentry2));

	__d_move(dentry1, dentry2, true);

	ग_लिखो_sequnlock(&नाम_lock);
पूर्ण

/**
 * d_ancestor - search क्रम an ancestor
 * @p1: ancestor dentry
 * @p2: child dentry
 *
 * Returns the ancestor dentry of p2 which is a child of p1, अगर p1 is
 * an ancestor of p2, अन्यथा शून्य.
 */
काष्ठा dentry *d_ancestor(काष्ठा dentry *p1, काष्ठा dentry *p2)
अणु
	काष्ठा dentry *p;

	क्रम (p = p2; !IS_ROOT(p); p = p->d_parent) अणु
		अगर (p->d_parent == p1)
			वापस p;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * This helper attempts to cope with remotely नामd directories
 *
 * It assumes that the caller is alपढ़ोy holding
 * dentry->d_parent->d_inode->i_mutex, and नाम_lock
 *
 * Note: If ever the locking in lock_नाम() changes, then please
 * remember to update this too...
 */
अटल पूर्णांक __d_unalias(काष्ठा inode *inode,
		काष्ठा dentry *dentry, काष्ठा dentry *alias)
अणु
	काष्ठा mutex *m1 = शून्य;
	काष्ठा rw_semaphore *m2 = शून्य;
	पूर्णांक ret = -ESTALE;

	/* If alias and dentry share a parent, then no extra locks required */
	अगर (alias->d_parent == dentry->d_parent)
		जाओ out_unalias;

	/* See lock_नाम() */
	अगर (!mutex_trylock(&dentry->d_sb->s_vfs_नाम_mutex))
		जाओ out_err;
	m1 = &dentry->d_sb->s_vfs_नाम_mutex;
	अगर (!inode_trylock_shared(alias->d_parent->d_inode))
		जाओ out_err;
	m2 = &alias->d_parent->d_inode->i_rwsem;
out_unalias:
	__d_move(alias, dentry, false);
	ret = 0;
out_err:
	अगर (m2)
		up_पढ़ो(m2);
	अगर (m1)
		mutex_unlock(m1);
	वापस ret;
पूर्ण

/**
 * d_splice_alias - splice a disconnected dentry पूर्णांकo the tree अगर one exists
 * @inode:  the inode which may have a disconnected dentry
 * @dentry: a negative dentry which we want to poपूर्णांक to the inode.
 *
 * If inode is a directory and has an IS_ROOT alias, then d_move that in
 * place of the given dentry and वापस it, अन्यथा simply d_add the inode
 * to the dentry and वापस शून्य.
 *
 * If a non-IS_ROOT directory is found, the fileप्रणाली is corrupt, and
 * we should error out: directories can't have multiple aliases.
 *
 * This is needed in the lookup routine of any fileप्रणाली that is exportable
 * (via knfsd) so that we can build dcache paths to directories effectively.
 *
 * If a dentry was found and moved, then it is वापसed.  Otherwise शून्य
 * is वापसed.  This matches the expected वापस value of ->lookup.
 *
 * Cluster fileप्रणालीs may call this function with a negative, hashed dentry.
 * In that हाल, we know that the inode will be a regular file, and also this
 * will only occur during atomic_खोलो. So we need to check क्रम the dentry
 * being alपढ़ोy hashed only in the final हाल.
 */
काष्ठा dentry *d_splice_alias(काष्ठा inode *inode, काष्ठा dentry *dentry)
अणु
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	BUG_ON(!d_unhashed(dentry));

	अगर (!inode)
		जाओ out;

	security_d_instantiate(dentry, inode);
	spin_lock(&inode->i_lock);
	अगर (S_ISसूची(inode->i_mode)) अणु
		काष्ठा dentry *new = __d_find_any_alias(inode);
		अगर (unlikely(new)) अणु
			/* The reference to new ensures it reमुख्यs an alias */
			spin_unlock(&inode->i_lock);
			ग_लिखो_seqlock(&नाम_lock);
			अगर (unlikely(d_ancestor(new, dentry))) अणु
				ग_लिखो_sequnlock(&नाम_lock);
				dput(new);
				new = ERR_PTR(-ELOOP);
				pr_warn_ratelimited(
					"VFS: Lookup of '%s' in %s %s"
					" would have caused loop\n",
					dentry->d_name.name,
					inode->i_sb->s_type->name,
					inode->i_sb->s_id);
			पूर्ण अन्यथा अगर (!IS_ROOT(new)) अणु
				काष्ठा dentry *old_parent = dget(new->d_parent);
				पूर्णांक err = __d_unalias(inode, dentry, new);
				ग_लिखो_sequnlock(&नाम_lock);
				अगर (err) अणु
					dput(new);
					new = ERR_PTR(err);
				पूर्ण
				dput(old_parent);
			पूर्ण अन्यथा अणु
				__d_move(new, dentry, false);
				ग_लिखो_sequnlock(&नाम_lock);
			पूर्ण
			iput(inode);
			वापस new;
		पूर्ण
	पूर्ण
out:
	__d_add(dentry, inode);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(d_splice_alias);

/*
 * Test whether new_dentry is a subdirectory of old_dentry.
 *
 * Trivially implemented using the dcache काष्ठाure
 */

/**
 * is_subdir - is new dentry a subdirectory of old_dentry
 * @new_dentry: new dentry
 * @old_dentry: old dentry
 *
 * Returns true अगर new_dentry is a subdirectory of the parent (at any depth).
 * Returns false otherwise.
 * Caller must ensure that "new_dentry" is pinned beक्रमe calling is_subdir()
 */
  
bool is_subdir(काष्ठा dentry *new_dentry, काष्ठा dentry *old_dentry)
अणु
	bool result;
	अचिन्हित seq;

	अगर (new_dentry == old_dentry)
		वापस true;

	करो अणु
		/* क्रम restarting inner loop in हाल of seq retry */
		seq = पढ़ो_seqbegin(&नाम_lock);
		/*
		 * Need rcu_पढ़ोlock to protect against the d_parent trashing
		 * due to d_move
		 */
		rcu_पढ़ो_lock();
		अगर (d_ancestor(old_dentry, new_dentry))
			result = true;
		अन्यथा
			result = false;
		rcu_पढ़ो_unlock();
	पूर्ण जबतक (पढ़ो_seqretry(&नाम_lock, seq));

	वापस result;
पूर्ण
EXPORT_SYMBOL(is_subdir);

अटल क्रमागत d_walk_ret d_genocide_समाप्त(व्योम *data, काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *root = data;
	अगर (dentry != root) अणु
		अगर (d_unhashed(dentry) || !dentry->d_inode)
			वापस D_WALK_SKIP;

		अगर (!(dentry->d_flags & DCACHE_GENOCIDE)) अणु
			dentry->d_flags |= DCACHE_GENOCIDE;
			dentry->d_lockref.count--;
		पूर्ण
	पूर्ण
	वापस D_WALK_CONTINUE;
पूर्ण

व्योम d_genocide(काष्ठा dentry *parent)
अणु
	d_walk(parent, parent, d_genocide_समाप्त);
पूर्ण

EXPORT_SYMBOL(d_genocide);

व्योम d_क्षणिक_ख(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	inode_dec_link_count(inode);
	BUG_ON(dentry->d_name.name != dentry->d_iname ||
		!hlist_unhashed(&dentry->d_u.d_alias) ||
		!d_unlinked(dentry));
	spin_lock(&dentry->d_parent->d_lock);
	spin_lock_nested(&dentry->d_lock, DENTRY_D_LOCK_NESTED);
	dentry->d_name.len = प्र_लिखो(dentry->d_iname, "#%llu",
				(अचिन्हित दीर्घ दीर्घ)inode->i_ino);
	spin_unlock(&dentry->d_lock);
	spin_unlock(&dentry->d_parent->d_lock);
	d_instantiate(dentry, inode);
पूर्ण
EXPORT_SYMBOL(d_क्षणिक_ख);

अटल __initdata अचिन्हित दीर्घ dhash_entries;
अटल पूर्णांक __init set_dhash_entries(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;
	dhash_entries = simple_म_से_अदीर्घ(str, &str, 0);
	वापस 1;
पूर्ण
__setup("dhash_entries=", set_dhash_entries);

अटल व्योम __init dcache_init_early(व्योम)
अणु
	/* If hashes are distributed across NUMA nodes, defer
	 * hash allocation until vदो_स्मृति space is available.
	 */
	अगर (hashdist)
		वापस;

	dentry_hashtable =
		alloc_large_प्रणाली_hash("Dentry cache",
					माप(काष्ठा hlist_bl_head),
					dhash_entries,
					13,
					HASH_EARLY | HASH_ZERO,
					&d_hash_shअगरt,
					शून्य,
					0,
					0);
	d_hash_shअगरt = 32 - d_hash_shअगरt;
पूर्ण

अटल व्योम __init dcache_init(व्योम)
अणु
	/*
	 * A स्थिरructor could be added क्रम stable state like the lists,
	 * but it is probably not worth it because of the cache nature
	 * of the dcache.
	 */
	dentry_cache = KMEM_CACHE_USERCOPY(dentry,
		SLAB_RECLAIM_ACCOUNT|SLAB_PANIC|SLAB_MEM_SPREAD|SLAB_ACCOUNT,
		d_iname);

	/* Hash may have been set up in dcache_init_early */
	अगर (!hashdist)
		वापस;

	dentry_hashtable =
		alloc_large_प्रणाली_hash("Dentry cache",
					माप(काष्ठा hlist_bl_head),
					dhash_entries,
					13,
					HASH_ZERO,
					&d_hash_shअगरt,
					शून्य,
					0,
					0);
	d_hash_shअगरt = 32 - d_hash_shअगरt;
पूर्ण

/* SLAB cache क्रम __getname() consumers */
काष्ठा kmem_cache *names_cachep __पढ़ो_mostly;
EXPORT_SYMBOL(names_cachep);

व्योम __init vfs_caches_init_early(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(in_lookup_hashtable); i++)
		INIT_HLIST_BL_HEAD(&in_lookup_hashtable[i]);

	dcache_init_early();
	inode_init_early();
पूर्ण

व्योम __init vfs_caches_init(व्योम)
अणु
	names_cachep = kmem_cache_create_usercopy("names_cache", PATH_MAX, 0,
			SLAB_HWCACHE_ALIGN|SLAB_PANIC, 0, PATH_MAX, शून्य);

	dcache_init();
	inode_init();
	files_init();
	files_maxfiles_init();
	mnt_init();
	bdev_cache_init();
	chrdev_init();
पूर्ण
