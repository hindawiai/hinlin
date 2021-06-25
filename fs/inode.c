<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 1997 Linus Torvalds
 * (C) 1999 Andrea Arcangeli <andrea@suse.de> (dynamic inode allocation)
 */
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/hash.h>
#समावेश <linux/swap.h>
#समावेश <linux/security.h>
#समावेश <linux/cdev.h>
#समावेश <linux/memblock.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/mount.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/buffer_head.h> /* क्रम inode_has_buffers */
#समावेश <linux/ratelimit.h>
#समावेश <linux/list_lru.h>
#समावेश <linux/iversion.h>
#समावेश <trace/events/ग_लिखोback.h>
#समावेश "internal.h"

/*
 * Inode locking rules:
 *
 * inode->i_lock protects:
 *   inode->i_state, inode->i_hash, __iget()
 * Inode LRU list locks protect:
 *   inode->i_sb->s_inode_lru, inode->i_lru
 * inode->i_sb->s_inode_list_lock protects:
 *   inode->i_sb->s_inodes, inode->i_sb_list
 * bdi->wb.list_lock protects:
 *   bdi->wb.b_अणुdirty,io,more_io,dirty_समयपूर्ण, inode->i_io_list
 * inode_hash_lock protects:
 *   inode_hashtable, inode->i_hash
 *
 * Lock ordering:
 *
 * inode->i_sb->s_inode_list_lock
 *   inode->i_lock
 *     Inode LRU list locks
 *
 * bdi->wb.list_lock
 *   inode->i_lock
 *
 * inode_hash_lock
 *   inode->i_sb->s_inode_list_lock
 *   inode->i_lock
 *
 * iunique_lock
 *   inode_hash_lock
 */

अटल अचिन्हित पूर्णांक i_hash_mask __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक i_hash_shअगरt __पढ़ो_mostly;
अटल काष्ठा hlist_head *inode_hashtable __पढ़ो_mostly;
अटल __cacheline_aligned_in_smp DEFINE_SPINLOCK(inode_hash_lock);

/*
 * Empty aops. Can be used क्रम the हालs where the user करोes not
 * define any of the address_space operations.
 */
स्थिर काष्ठा address_space_operations empty_aops = अणु
पूर्ण;
EXPORT_SYMBOL(empty_aops);

/*
 * Statistics gathering..
 */
काष्ठा inodes_stat_t inodes_stat;

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, nr_inodes);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, nr_unused);

अटल काष्ठा kmem_cache *inode_cachep __पढ़ो_mostly;

अटल दीर्घ get_nr_inodes(व्योम)
अणु
	पूर्णांक i;
	दीर्घ sum = 0;
	क्रम_each_possible_cpu(i)
		sum += per_cpu(nr_inodes, i);
	वापस sum < 0 ? 0 : sum;
पूर्ण

अटल अंतरभूत दीर्घ get_nr_inodes_unused(व्योम)
अणु
	पूर्णांक i;
	दीर्घ sum = 0;
	क्रम_each_possible_cpu(i)
		sum += per_cpu(nr_unused, i);
	वापस sum < 0 ? 0 : sum;
पूर्ण

दीर्घ get_nr_dirty_inodes(व्योम)
अणु
	/* not actually dirty inodes, but a wild approximation */
	दीर्घ nr_dirty = get_nr_inodes() - get_nr_inodes_unused();
	वापस nr_dirty > 0 ? nr_dirty : 0;
पूर्ण

/*
 * Handle nr_inode sysctl
 */
#अगर_घोषित CONFIG_SYSCTL
पूर्णांक proc_nr_inodes(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	inodes_stat.nr_inodes = get_nr_inodes();
	inodes_stat.nr_unused = get_nr_inodes_unused();
	वापस proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक no_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस -ENXIO;
पूर्ण

/**
 * inode_init_always - perक्रमm inode काष्ठाure initialisation
 * @sb: superblock inode beदीर्घs to
 * @inode: inode to initialise
 *
 * These are initializations that need to be करोne on every inode
 * allocation as the fields are not initialised by slab allocation.
 */
पूर्णांक inode_init_always(काष्ठा super_block *sb, काष्ठा inode *inode)
अणु
	अटल स्थिर काष्ठा inode_operations empty_iops;
	अटल स्थिर काष्ठा file_operations no_खोलो_fops = अणु.खोलो = no_खोलोपूर्ण;
	काष्ठा address_space *स्थिर mapping = &inode->i_data;

	inode->i_sb = sb;
	inode->i_blkbits = sb->s_blocksize_bits;
	inode->i_flags = 0;
	atomic64_set(&inode->i_sequence, 0);
	atomic_set(&inode->i_count, 1);
	inode->i_op = &empty_iops;
	inode->i_fop = &no_खोलो_fops;
	inode->i_ino = 0;
	inode->__i_nlink = 1;
	inode->i_opflags = 0;
	अगर (sb->s_xattr)
		inode->i_opflags |= IOP_XATTR;
	i_uid_ग_लिखो(inode, 0);
	i_gid_ग_लिखो(inode, 0);
	atomic_set(&inode->i_ग_लिखोcount, 0);
	inode->i_size = 0;
	inode->i_ग_लिखो_hपूर्णांक = WRITE_LIFE_NOT_SET;
	inode->i_blocks = 0;
	inode->i_bytes = 0;
	inode->i_generation = 0;
	inode->i_pipe = शून्य;
	inode->i_cdev = शून्य;
	inode->i_link = शून्य;
	inode->i_dir_seq = 0;
	inode->i_rdev = 0;
	inode->dirtied_when = 0;

#अगर_घोषित CONFIG_CGROUP_WRITEBACK
	inode->i_wb_frn_winner = 0;
	inode->i_wb_frn_avg_समय = 0;
	inode->i_wb_frn_history = 0;
#पूर्ण_अगर

	अगर (security_inode_alloc(inode))
		जाओ out;
	spin_lock_init(&inode->i_lock);
	lockdep_set_class(&inode->i_lock, &sb->s_type->i_lock_key);

	init_rwsem(&inode->i_rwsem);
	lockdep_set_class(&inode->i_rwsem, &sb->s_type->i_mutex_key);

	atomic_set(&inode->i_dio_count, 0);

	mapping->a_ops = &empty_aops;
	mapping->host = inode;
	mapping->flags = 0;
	अगर (sb->s_type->fs_flags & FS_THP_SUPPORT)
		__set_bit(AS_THP_SUPPORT, &mapping->flags);
	mapping->wb_err = 0;
	atomic_set(&mapping->i_mmap_writable, 0);
#अगर_घोषित CONFIG_READ_ONLY_THP_FOR_FS
	atomic_set(&mapping->nr_thps, 0);
#पूर्ण_अगर
	mapping_set_gfp_mask(mapping, GFP_HIGHUSER_MOVABLE);
	mapping->निजी_data = शून्य;
	mapping->ग_लिखोback_index = 0;
	inode->i_निजी = शून्य;
	inode->i_mapping = mapping;
	INIT_HLIST_HEAD(&inode->i_dentry);	/* buggered by rcu मुक्तing */
#अगर_घोषित CONFIG_FS_POSIX_ACL
	inode->i_acl = inode->i_शेष_acl = ACL_NOT_CACHED;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FSNOTIFY
	inode->i_fsnotअगरy_mask = 0;
#पूर्ण_अगर
	inode->i_flctx = शून्य;
	this_cpu_inc(nr_inodes);

	वापस 0;
out:
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(inode_init_always);

व्योम मुक्त_inode_nonrcu(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(inode_cachep, inode);
पूर्ण
EXPORT_SYMBOL(मुक्त_inode_nonrcu);

अटल व्योम i_callback(काष्ठा rcu_head *head)
अणु
	काष्ठा inode *inode = container_of(head, काष्ठा inode, i_rcu);
	अगर (inode->मुक्त_inode)
		inode->मुक्त_inode(inode);
	अन्यथा
		मुक्त_inode_nonrcu(inode);
पूर्ण

अटल काष्ठा inode *alloc_inode(काष्ठा super_block *sb)
अणु
	स्थिर काष्ठा super_operations *ops = sb->s_op;
	काष्ठा inode *inode;

	अगर (ops->alloc_inode)
		inode = ops->alloc_inode(sb);
	अन्यथा
		inode = kmem_cache_alloc(inode_cachep, GFP_KERNEL);

	अगर (!inode)
		वापस शून्य;

	अगर (unlikely(inode_init_always(sb, inode))) अणु
		अगर (ops->destroy_inode) अणु
			ops->destroy_inode(inode);
			अगर (!ops->मुक्त_inode)
				वापस शून्य;
		पूर्ण
		inode->मुक्त_inode = ops->मुक्त_inode;
		i_callback(&inode->i_rcu);
		वापस शून्य;
	पूर्ण

	वापस inode;
पूर्ण

व्योम __destroy_inode(काष्ठा inode *inode)
अणु
	BUG_ON(inode_has_buffers(inode));
	inode_detach_wb(inode);
	security_inode_मुक्त(inode);
	fsnotअगरy_inode_delete(inode);
	locks_मुक्त_lock_context(inode);
	अगर (!inode->i_nlink) अणु
		WARN_ON(atomic_दीर्घ_पढ़ो(&inode->i_sb->s_हटाओ_count) == 0);
		atomic_दीर्घ_dec(&inode->i_sb->s_हटाओ_count);
	पूर्ण

#अगर_घोषित CONFIG_FS_POSIX_ACL
	अगर (inode->i_acl && !is_uncached_acl(inode->i_acl))
		posix_acl_release(inode->i_acl);
	अगर (inode->i_शेष_acl && !is_uncached_acl(inode->i_शेष_acl))
		posix_acl_release(inode->i_शेष_acl);
#पूर्ण_अगर
	this_cpu_dec(nr_inodes);
पूर्ण
EXPORT_SYMBOL(__destroy_inode);

अटल व्योम destroy_inode(काष्ठा inode *inode)
अणु
	स्थिर काष्ठा super_operations *ops = inode->i_sb->s_op;

	BUG_ON(!list_empty(&inode->i_lru));
	__destroy_inode(inode);
	अगर (ops->destroy_inode) अणु
		ops->destroy_inode(inode);
		अगर (!ops->मुक्त_inode)
			वापस;
	पूर्ण
	inode->मुक्त_inode = ops->मुक्त_inode;
	call_rcu(&inode->i_rcu, i_callback);
पूर्ण

/**
 * drop_nlink - directly drop an inode's link count
 * @inode: inode
 *
 * This is a low-level fileप्रणाली helper to replace any
 * direct fileप्रणाली manipulation of i_nlink.  In हालs
 * where we are attempting to track ग_लिखोs to the
 * fileप्रणाली, a decrement to zero means an imminent
 * ग_लिखो when the file is truncated and actually unlinked
 * on the fileप्रणाली.
 */
व्योम drop_nlink(काष्ठा inode *inode)
अणु
	WARN_ON(inode->i_nlink == 0);
	inode->__i_nlink--;
	अगर (!inode->i_nlink)
		atomic_दीर्घ_inc(&inode->i_sb->s_हटाओ_count);
पूर्ण
EXPORT_SYMBOL(drop_nlink);

/**
 * clear_nlink - directly zero an inode's link count
 * @inode: inode
 *
 * This is a low-level fileप्रणाली helper to replace any
 * direct fileप्रणाली manipulation of i_nlink.  See
 * drop_nlink() क्रम why we care about i_nlink hitting zero.
 */
व्योम clear_nlink(काष्ठा inode *inode)
अणु
	अगर (inode->i_nlink) अणु
		inode->__i_nlink = 0;
		atomic_दीर्घ_inc(&inode->i_sb->s_हटाओ_count);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(clear_nlink);

/**
 * set_nlink - directly set an inode's link count
 * @inode: inode
 * @nlink: new nlink (should be non-zero)
 *
 * This is a low-level fileप्रणाली helper to replace any
 * direct fileप्रणाली manipulation of i_nlink.
 */
व्योम set_nlink(काष्ठा inode *inode, अचिन्हित पूर्णांक nlink)
अणु
	अगर (!nlink) अणु
		clear_nlink(inode);
	पूर्ण अन्यथा अणु
		/* Yes, some fileप्रणालीs करो change nlink from zero to one */
		अगर (inode->i_nlink == 0)
			atomic_दीर्घ_dec(&inode->i_sb->s_हटाओ_count);

		inode->__i_nlink = nlink;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(set_nlink);

/**
 * inc_nlink - directly increment an inode's link count
 * @inode: inode
 *
 * This is a low-level fileप्रणाली helper to replace any
 * direct fileप्रणाली manipulation of i_nlink.  Currently,
 * it is only here क्रम parity with dec_nlink().
 */
व्योम inc_nlink(काष्ठा inode *inode)
अणु
	अगर (unlikely(inode->i_nlink == 0)) अणु
		WARN_ON(!(inode->i_state & I_LINKABLE));
		atomic_दीर्घ_dec(&inode->i_sb->s_हटाओ_count);
	पूर्ण

	inode->__i_nlink++;
पूर्ण
EXPORT_SYMBOL(inc_nlink);

अटल व्योम __address_space_init_once(काष्ठा address_space *mapping)
अणु
	xa_init_flags(&mapping->i_pages, XA_FLAGS_LOCK_IRQ | XA_FLAGS_ACCOUNT);
	init_rwsem(&mapping->i_mmap_rwsem);
	INIT_LIST_HEAD(&mapping->निजी_list);
	spin_lock_init(&mapping->निजी_lock);
	mapping->i_mmap = RB_ROOT_CACHED;
पूर्ण

व्योम address_space_init_once(काष्ठा address_space *mapping)
अणु
	स_रखो(mapping, 0, माप(*mapping));
	__address_space_init_once(mapping);
पूर्ण
EXPORT_SYMBOL(address_space_init_once);

/*
 * These are initializations that only need to be करोne
 * once, because the fields are idempotent across use
 * of the inode, so let the slab aware of that.
 */
व्योम inode_init_once(काष्ठा inode *inode)
अणु
	स_रखो(inode, 0, माप(*inode));
	INIT_HLIST_NODE(&inode->i_hash);
	INIT_LIST_HEAD(&inode->i_devices);
	INIT_LIST_HEAD(&inode->i_io_list);
	INIT_LIST_HEAD(&inode->i_wb_list);
	INIT_LIST_HEAD(&inode->i_lru);
	__address_space_init_once(&inode->i_data);
	i_size_ordered_init(inode);
पूर्ण
EXPORT_SYMBOL(inode_init_once);

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा inode *inode = (काष्ठा inode *) foo;

	inode_init_once(inode);
पूर्ण

/*
 * inode->i_lock must be held
 */
व्योम __iget(काष्ठा inode *inode)
अणु
	atomic_inc(&inode->i_count);
पूर्ण

/*
 * get additional reference to inode; caller must alपढ़ोy hold one.
 */
व्योम ihold(काष्ठा inode *inode)
अणु
	WARN_ON(atomic_inc_वापस(&inode->i_count) < 2);
पूर्ण
EXPORT_SYMBOL(ihold);

अटल व्योम inode_lru_list_add(काष्ठा inode *inode)
अणु
	अगर (list_lru_add(&inode->i_sb->s_inode_lru, &inode->i_lru))
		this_cpu_inc(nr_unused);
	अन्यथा
		inode->i_state |= I_REFERENCED;
पूर्ण

/*
 * Add inode to LRU अगर needed (inode is unused and clean).
 *
 * Needs inode->i_lock held.
 */
व्योम inode_add_lru(काष्ठा inode *inode)
अणु
	अगर (!(inode->i_state & (I_सूचीTY_ALL | I_SYNC |
				I_FREEING | I_WILL_FREE)) &&
	    !atomic_पढ़ो(&inode->i_count) && inode->i_sb->s_flags & SB_ACTIVE)
		inode_lru_list_add(inode);
पूर्ण


अटल व्योम inode_lru_list_del(काष्ठा inode *inode)
अणु

	अगर (list_lru_del(&inode->i_sb->s_inode_lru, &inode->i_lru))
		this_cpu_dec(nr_unused);
पूर्ण

/**
 * inode_sb_list_add - add inode to the superblock list of inodes
 * @inode: inode to add
 */
व्योम inode_sb_list_add(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_sb->s_inode_list_lock);
	list_add(&inode->i_sb_list, &inode->i_sb->s_inodes);
	spin_unlock(&inode->i_sb->s_inode_list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(inode_sb_list_add);

अटल अंतरभूत व्योम inode_sb_list_del(काष्ठा inode *inode)
अणु
	अगर (!list_empty(&inode->i_sb_list)) अणु
		spin_lock(&inode->i_sb->s_inode_list_lock);
		list_del_init(&inode->i_sb_list);
		spin_unlock(&inode->i_sb->s_inode_list_lock);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ hash(काष्ठा super_block *sb, अचिन्हित दीर्घ hashval)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = (hashval * (अचिन्हित दीर्घ)sb) ^ (GOLDEN_RATIO_PRIME + hashval) /
			L1_CACHE_BYTES;
	पंचांगp = पंचांगp ^ ((पंचांगp ^ GOLDEN_RATIO_PRIME) >> i_hash_shअगरt);
	वापस पंचांगp & i_hash_mask;
पूर्ण

/**
 *	__insert_inode_hash - hash an inode
 *	@inode: unhashed inode
 *	@hashval: अचिन्हित दीर्घ value used to locate this object in the
 *		inode_hashtable.
 *
 *	Add an inode to the inode hash क्रम this superblock.
 */
व्योम __insert_inode_hash(काष्ठा inode *inode, अचिन्हित दीर्घ hashval)
अणु
	काष्ठा hlist_head *b = inode_hashtable + hash(inode->i_sb, hashval);

	spin_lock(&inode_hash_lock);
	spin_lock(&inode->i_lock);
	hlist_add_head_rcu(&inode->i_hash, b);
	spin_unlock(&inode->i_lock);
	spin_unlock(&inode_hash_lock);
पूर्ण
EXPORT_SYMBOL(__insert_inode_hash);

/**
 *	__हटाओ_inode_hash - हटाओ an inode from the hash
 *	@inode: inode to unhash
 *
 *	Remove an inode from the superblock.
 */
व्योम __हटाओ_inode_hash(काष्ठा inode *inode)
अणु
	spin_lock(&inode_hash_lock);
	spin_lock(&inode->i_lock);
	hlist_del_init_rcu(&inode->i_hash);
	spin_unlock(&inode->i_lock);
	spin_unlock(&inode_hash_lock);
पूर्ण
EXPORT_SYMBOL(__हटाओ_inode_hash);

व्योम clear_inode(काष्ठा inode *inode)
अणु
	/*
	 * We have to cycle the i_pages lock here because reclaim can be in the
	 * process of removing the last page (in __delete_from_page_cache())
	 * and we must not मुक्त the mapping under it.
	 */
	xa_lock_irq(&inode->i_data.i_pages);
	BUG_ON(inode->i_data.nrpages);
	/*
	 * Almost always, mapping_empty(&inode->i_data) here; but there are
	 * two known and दीर्घ-standing ways in which nodes may get left behind
	 * (when deep radix-tree node allocation failed partway; or when THP
	 * collapse_file() failed). Until those two known हालs are cleaned up,
	 * or a cleanup function is called here, करो not BUG_ON(!mapping_empty),
	 * nor even WARN_ON(!mapping_empty).
	 */
	xa_unlock_irq(&inode->i_data.i_pages);
	BUG_ON(!list_empty(&inode->i_data.निजी_list));
	BUG_ON(!(inode->i_state & I_FREEING));
	BUG_ON(inode->i_state & I_CLEAR);
	BUG_ON(!list_empty(&inode->i_wb_list));
	/* करोn't need i_lock here, no concurrent mods to i_state */
	inode->i_state = I_FREEING | I_CLEAR;
पूर्ण
EXPORT_SYMBOL(clear_inode);

/*
 * Free the inode passed in, removing it from the lists it is still connected
 * to. We हटाओ any pages still attached to the inode and रुको क्रम any IO that
 * is still in progress beक्रमe finally destroying the inode.
 *
 * An inode must alपढ़ोy be marked I_FREEING so that we aव्योम the inode being
 * moved back onto lists अगर we race with other code that manipulates the lists
 * (e.g. ग_लिखोback_single_inode). The caller is responsible क्रम setting this.
 *
 * An inode must alपढ़ोy be हटाओd from the LRU list beक्रमe being evicted from
 * the cache. This should occur atomically with setting the I_FREEING state
 * flag, so no inodes here should ever be on the LRU when being evicted.
 */
अटल व्योम evict(काष्ठा inode *inode)
अणु
	स्थिर काष्ठा super_operations *op = inode->i_sb->s_op;

	BUG_ON(!(inode->i_state & I_FREEING));
	BUG_ON(!list_empty(&inode->i_lru));

	अगर (!list_empty(&inode->i_io_list))
		inode_io_list_del(inode);

	inode_sb_list_del(inode);

	/*
	 * Wait क्रम flusher thपढ़ो to be करोne with the inode so that fileप्रणाली
	 * करोes not start destroying it जबतक ग_लिखोback is still running. Since
	 * the inode has I_FREEING set, flusher thपढ़ो won't start new work on
	 * the inode.  We just have to रुको क्रम running ग_लिखोback to finish.
	 */
	inode_रुको_क्रम_ग_लिखोback(inode);

	अगर (op->evict_inode) अणु
		op->evict_inode(inode);
	पूर्ण अन्यथा अणु
		truncate_inode_pages_final(&inode->i_data);
		clear_inode(inode);
	पूर्ण
	अगर (S_ISCHR(inode->i_mode) && inode->i_cdev)
		cd_क्रमget(inode);

	हटाओ_inode_hash(inode);

	spin_lock(&inode->i_lock);
	wake_up_bit(&inode->i_state, __I_NEW);
	BUG_ON(inode->i_state != (I_FREEING | I_CLEAR));
	spin_unlock(&inode->i_lock);

	destroy_inode(inode);
पूर्ण

/*
 * dispose_list - dispose of the contents of a local list
 * @head: the head of the list to मुक्त
 *
 * Dispose-list माला_लो a local list with local inodes in it, so it करोesn't
 * need to worry about list corruption and SMP locks.
 */
अटल व्योम dispose_list(काष्ठा list_head *head)
अणु
	जबतक (!list_empty(head)) अणु
		काष्ठा inode *inode;

		inode = list_first_entry(head, काष्ठा inode, i_lru);
		list_del_init(&inode->i_lru);

		evict(inode);
		cond_resched();
	पूर्ण
पूर्ण

/**
 * evict_inodes	- evict all evictable inodes क्रम a superblock
 * @sb:		superblock to operate on
 *
 * Make sure that no inodes with zero refcount are retained.  This is
 * called by superblock shutकरोwn after having SB_ACTIVE flag हटाओd,
 * so any inode reaching zero refcount during or after that call will
 * be immediately evicted.
 */
व्योम evict_inodes(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode, *next;
	LIST_HEAD(dispose);

again:
	spin_lock(&sb->s_inode_list_lock);
	list_क्रम_each_entry_safe(inode, next, &sb->s_inodes, i_sb_list) अणु
		अगर (atomic_पढ़ो(&inode->i_count))
			जारी;

		spin_lock(&inode->i_lock);
		अगर (inode->i_state & (I_NEW | I_FREEING | I_WILL_FREE)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण

		inode->i_state |= I_FREEING;
		inode_lru_list_del(inode);
		spin_unlock(&inode->i_lock);
		list_add(&inode->i_lru, &dispose);

		/*
		 * We can have a ton of inodes to evict at unmount समय given
		 * enough memory, check to see अगर we need to go to sleep क्रम a
		 * bit so we करोn't livelock.
		 */
		अगर (need_resched()) अणु
			spin_unlock(&sb->s_inode_list_lock);
			cond_resched();
			dispose_list(&dispose);
			जाओ again;
		पूर्ण
	पूर्ण
	spin_unlock(&sb->s_inode_list_lock);

	dispose_list(&dispose);
पूर्ण
EXPORT_SYMBOL_GPL(evict_inodes);

/**
 * invalidate_inodes	- attempt to मुक्त all inodes on a superblock
 * @sb:		superblock to operate on
 * @समाप्त_dirty: flag to guide handling of dirty inodes
 *
 * Attempts to मुक्त all inodes क्रम a given superblock.  If there were any
 * busy inodes वापस a non-zero value, अन्यथा zero.
 * If @समाप्त_dirty is set, discard dirty inodes too, otherwise treat
 * them as busy.
 */
पूर्णांक invalidate_inodes(काष्ठा super_block *sb, bool समाप्त_dirty)
अणु
	पूर्णांक busy = 0;
	काष्ठा inode *inode, *next;
	LIST_HEAD(dispose);

again:
	spin_lock(&sb->s_inode_list_lock);
	list_क्रम_each_entry_safe(inode, next, &sb->s_inodes, i_sb_list) अणु
		spin_lock(&inode->i_lock);
		अगर (inode->i_state & (I_NEW | I_FREEING | I_WILL_FREE)) अणु
			spin_unlock(&inode->i_lock);
			जारी;
		पूर्ण
		अगर (inode->i_state & I_सूचीTY_ALL && !समाप्त_dirty) अणु
			spin_unlock(&inode->i_lock);
			busy = 1;
			जारी;
		पूर्ण
		अगर (atomic_पढ़ो(&inode->i_count)) अणु
			spin_unlock(&inode->i_lock);
			busy = 1;
			जारी;
		पूर्ण

		inode->i_state |= I_FREEING;
		inode_lru_list_del(inode);
		spin_unlock(&inode->i_lock);
		list_add(&inode->i_lru, &dispose);
		अगर (need_resched()) अणु
			spin_unlock(&sb->s_inode_list_lock);
			cond_resched();
			dispose_list(&dispose);
			जाओ again;
		पूर्ण
	पूर्ण
	spin_unlock(&sb->s_inode_list_lock);

	dispose_list(&dispose);

	वापस busy;
पूर्ण

/*
 * Isolate the inode from the LRU in preparation क्रम मुक्तing it.
 *
 * Any inodes which are pinned purely because of attached pagecache have their
 * pagecache हटाओd.  If the inode has metadata buffers attached to
 * mapping->निजी_list then try to हटाओ them.
 *
 * If the inode has the I_REFERENCED flag set, then it means that it has been
 * used recently - the flag is set in iput_final(). When we encounter such an
 * inode, clear the flag and move it to the back of the LRU so it माला_लो another
 * pass through the LRU beक्रमe it माला_लो reclaimed. This is necessary because of
 * the fact we are करोing lazy LRU updates to minimise lock contention so the
 * LRU करोes not have strict ordering. Hence we करोn't want to reclaim inodes
 * with this flag set because they are the inodes that are out of order.
 */
अटल क्रमागत lru_status inode_lru_isolate(काष्ठा list_head *item,
		काष्ठा list_lru_one *lru, spinlock_t *lru_lock, व्योम *arg)
अणु
	काष्ठा list_head *मुक्तable = arg;
	काष्ठा inode	*inode = container_of(item, काष्ठा inode, i_lru);

	/*
	 * we are inverting the lru lock/inode->i_lock here, so use a trylock.
	 * If we fail to get the lock, just skip it.
	 */
	अगर (!spin_trylock(&inode->i_lock))
		वापस LRU_SKIP;

	/*
	 * Referenced or dirty inodes are still in use. Give them another pass
	 * through the LRU as we canot reclaim them now.
	 */
	अगर (atomic_पढ़ो(&inode->i_count) ||
	    (inode->i_state & ~I_REFERENCED)) अणु
		list_lru_isolate(lru, &inode->i_lru);
		spin_unlock(&inode->i_lock);
		this_cpu_dec(nr_unused);
		वापस LRU_REMOVED;
	पूर्ण

	/* recently referenced inodes get one more pass */
	अगर (inode->i_state & I_REFERENCED) अणु
		inode->i_state &= ~I_REFERENCED;
		spin_unlock(&inode->i_lock);
		वापस LRU_ROTATE;
	पूर्ण

	अगर (inode_has_buffers(inode) || inode->i_data.nrpages) अणु
		__iget(inode);
		spin_unlock(&inode->i_lock);
		spin_unlock(lru_lock);
		अगर (हटाओ_inode_buffers(inode)) अणु
			अचिन्हित दीर्घ reap;
			reap = invalidate_mapping_pages(&inode->i_data, 0, -1);
			अगर (current_is_kswapd())
				__count_vm_events(KSWAPD_INODESTEAL, reap);
			अन्यथा
				__count_vm_events(PGINODESTEAL, reap);
			अगर (current->reclaim_state)
				current->reclaim_state->reclaimed_slab += reap;
		पूर्ण
		iput(inode);
		spin_lock(lru_lock);
		वापस LRU_RETRY;
	पूर्ण

	WARN_ON(inode->i_state & I_NEW);
	inode->i_state |= I_FREEING;
	list_lru_isolate_move(lru, &inode->i_lru, मुक्तable);
	spin_unlock(&inode->i_lock);

	this_cpu_dec(nr_unused);
	वापस LRU_REMOVED;
पूर्ण

/*
 * Walk the superblock inode LRU क्रम मुक्तable inodes and attempt to मुक्त them.
 * This is called from the superblock shrinker function with a number of inodes
 * to trim from the LRU. Inodes to be मुक्तd are moved to a temporary list and
 * then are मुक्तd outside inode_lock by dispose_list().
 */
दीर्घ prune_icache_sb(काष्ठा super_block *sb, काष्ठा shrink_control *sc)
अणु
	LIST_HEAD(मुक्तable);
	दीर्घ मुक्तd;

	मुक्तd = list_lru_shrink_walk(&sb->s_inode_lru, sc,
				     inode_lru_isolate, &मुक्तable);
	dispose_list(&मुक्तable);
	वापस मुक्तd;
पूर्ण

अटल व्योम __रुको_on_मुक्तing_inode(काष्ठा inode *inode);
/*
 * Called with the inode lock held.
 */
अटल काष्ठा inode *find_inode(काष्ठा super_block *sb,
				काष्ठा hlist_head *head,
				पूर्णांक (*test)(काष्ठा inode *, व्योम *),
				व्योम *data)
अणु
	काष्ठा inode *inode = शून्य;

repeat:
	hlist_क्रम_each_entry(inode, head, i_hash) अणु
		अगर (inode->i_sb != sb)
			जारी;
		अगर (!test(inode, data))
			जारी;
		spin_lock(&inode->i_lock);
		अगर (inode->i_state & (I_FREEING|I_WILL_FREE)) अणु
			__रुको_on_मुक्तing_inode(inode);
			जाओ repeat;
		पूर्ण
		अगर (unlikely(inode->i_state & I_CREATING)) अणु
			spin_unlock(&inode->i_lock);
			वापस ERR_PTR(-ESTALE);
		पूर्ण
		__iget(inode);
		spin_unlock(&inode->i_lock);
		वापस inode;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * find_inode_fast is the fast path version of find_inode, see the comment at
 * iget_locked क्रम details.
 */
अटल काष्ठा inode *find_inode_fast(काष्ठा super_block *sb,
				काष्ठा hlist_head *head, अचिन्हित दीर्घ ino)
अणु
	काष्ठा inode *inode = शून्य;

repeat:
	hlist_क्रम_each_entry(inode, head, i_hash) अणु
		अगर (inode->i_ino != ino)
			जारी;
		अगर (inode->i_sb != sb)
			जारी;
		spin_lock(&inode->i_lock);
		अगर (inode->i_state & (I_FREEING|I_WILL_FREE)) अणु
			__रुको_on_मुक्तing_inode(inode);
			जाओ repeat;
		पूर्ण
		अगर (unlikely(inode->i_state & I_CREATING)) अणु
			spin_unlock(&inode->i_lock);
			वापस ERR_PTR(-ESTALE);
		पूर्ण
		__iget(inode);
		spin_unlock(&inode->i_lock);
		वापस inode;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Each cpu owns a range of LAST_INO_BATCH numbers.
 * 'shared_last_ino' is dirtied only once out of LAST_INO_BATCH allocations,
 * to renew the exhausted range.
 *
 * This करोes not signअगरicantly increase overflow rate because every CPU can
 * consume at most LAST_INO_BATCH-1 unused inode numbers. So there is
 * NR_CPUS*(LAST_INO_BATCH-1) wastage. At 4096 and 1024, this is ~0.1% of the
 * 2^32 range, and is a worst-हाल. Even a 50% wastage would only increase
 * overflow rate by 2x, which करोes not seem too signअगरicant.
 *
 * On a 32bit, non LFS stat() call, glibc will generate an EOVERFLOW
 * error अगर st_ino won't fit in target काष्ठा field. Use 32bit counter
 * here to attempt to aव्योम that.
 */
#घोषणा LAST_INO_BATCH 1024
अटल DEFINE_PER_CPU(अचिन्हित पूर्णांक, last_ino);

अचिन्हित पूर्णांक get_next_ino(व्योम)
अणु
	अचिन्हित पूर्णांक *p = &get_cpu_var(last_ino);
	अचिन्हित पूर्णांक res = *p;

#अगर_घोषित CONFIG_SMP
	अगर (unlikely((res & (LAST_INO_BATCH-1)) == 0)) अणु
		अटल atomic_t shared_last_ino;
		पूर्णांक next = atomic_add_वापस(LAST_INO_BATCH, &shared_last_ino);

		res = next - LAST_INO_BATCH;
	पूर्ण
#पूर्ण_अगर

	res++;
	/* get_next_ino should not provide a 0 inode number */
	अगर (unlikely(!res))
		res++;
	*p = res;
	put_cpu_var(last_ino);
	वापस res;
पूर्ण
EXPORT_SYMBOL(get_next_ino);

/**
 *	new_inode_pseuकरो 	- obtain an inode
 *	@sb: superblock
 *
 *	Allocates a new inode क्रम given superblock.
 *	Inode wont be chained in superblock s_inodes list
 *	This means :
 *	- fs can't be unmount
 *	- quotas, fsnotअगरy, ग_लिखोback can't work
 */
काष्ठा inode *new_inode_pseuकरो(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode = alloc_inode(sb);

	अगर (inode) अणु
		spin_lock(&inode->i_lock);
		inode->i_state = 0;
		spin_unlock(&inode->i_lock);
		INIT_LIST_HEAD(&inode->i_sb_list);
	पूर्ण
	वापस inode;
पूर्ण

/**
 *	new_inode 	- obtain an inode
 *	@sb: superblock
 *
 *	Allocates a new inode क्रम given superblock. The शेष gfp_mask
 *	क्रम allocations related to inode->i_mapping is GFP_HIGHUSER_MOVABLE.
 *	If HIGHMEM pages are unsuitable or it is known that pages allocated
 *	क्रम the page cache are not reclaimable or migratable,
 *	mapping_set_gfp_mask() must be called with suitable flags on the
 *	newly created inode's mapping
 *
 */
काष्ठा inode *new_inode(काष्ठा super_block *sb)
अणु
	काष्ठा inode *inode;

	spin_lock_prefetch(&sb->s_inode_list_lock);

	inode = new_inode_pseuकरो(sb);
	अगर (inode)
		inode_sb_list_add(inode);
	वापस inode;
पूर्ण
EXPORT_SYMBOL(new_inode);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
व्योम lockdep_annotate_inode_mutex_key(काष्ठा inode *inode)
अणु
	अगर (S_ISसूची(inode->i_mode)) अणु
		काष्ठा file_प्रणाली_type *type = inode->i_sb->s_type;

		/* Set new key only अगर fileप्रणाली hasn't alपढ़ोy changed it */
		अगर (lockdep_match_class(&inode->i_rwsem, &type->i_mutex_key)) अणु
			/*
			 * ensure nobody is actually holding i_mutex
			 */
			// mutex_destroy(&inode->i_mutex);
			init_rwsem(&inode->i_rwsem);
			lockdep_set_class(&inode->i_rwsem,
					  &type->i_mutex_dir_key);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(lockdep_annotate_inode_mutex_key);
#पूर्ण_अगर

/**
 * unlock_new_inode - clear the I_NEW state and wake up any रुकोers
 * @inode:	new inode to unlock
 *
 * Called when the inode is fully initialised to clear the new state of the
 * inode and wake up anyone रुकोing क्रम the inode to finish initialisation.
 */
व्योम unlock_new_inode(काष्ठा inode *inode)
अणु
	lockdep_annotate_inode_mutex_key(inode);
	spin_lock(&inode->i_lock);
	WARN_ON(!(inode->i_state & I_NEW));
	inode->i_state &= ~I_NEW & ~I_CREATING;
	smp_mb();
	wake_up_bit(&inode->i_state, __I_NEW);
	spin_unlock(&inode->i_lock);
पूर्ण
EXPORT_SYMBOL(unlock_new_inode);

व्योम discard_new_inode(काष्ठा inode *inode)
अणु
	lockdep_annotate_inode_mutex_key(inode);
	spin_lock(&inode->i_lock);
	WARN_ON(!(inode->i_state & I_NEW));
	inode->i_state &= ~I_NEW;
	smp_mb();
	wake_up_bit(&inode->i_state, __I_NEW);
	spin_unlock(&inode->i_lock);
	iput(inode);
पूर्ण
EXPORT_SYMBOL(discard_new_inode);

/**
 * lock_two_nondirectories - take two i_mutexes on non-directory objects
 *
 * Lock any non-शून्य argument that is not a directory.
 * Zero, one or two objects may be locked by this function.
 *
 * @inode1: first inode to lock
 * @inode2: second inode to lock
 */
व्योम lock_two_nondirectories(काष्ठा inode *inode1, काष्ठा inode *inode2)
अणु
	अगर (inode1 > inode2)
		swap(inode1, inode2);

	अगर (inode1 && !S_ISसूची(inode1->i_mode))
		inode_lock(inode1);
	अगर (inode2 && !S_ISसूची(inode2->i_mode) && inode2 != inode1)
		inode_lock_nested(inode2, I_MUTEX_NONसूची2);
पूर्ण
EXPORT_SYMBOL(lock_two_nondirectories);

/**
 * unlock_two_nondirectories - release locks from lock_two_nondirectories()
 * @inode1: first inode to unlock
 * @inode2: second inode to unlock
 */
व्योम unlock_two_nondirectories(काष्ठा inode *inode1, काष्ठा inode *inode2)
अणु
	अगर (inode1 && !S_ISसूची(inode1->i_mode))
		inode_unlock(inode1);
	अगर (inode2 && !S_ISसूची(inode2->i_mode) && inode2 != inode1)
		inode_unlock(inode2);
पूर्ण
EXPORT_SYMBOL(unlock_two_nondirectories);

/**
 * inode_insert5 - obtain an inode from a mounted file प्रणाली
 * @inode:	pre-allocated inode to use क्रम insert to cache
 * @hashval:	hash value (usually inode number) to get
 * @test:	callback used क्रम comparisons between inodes
 * @set:	callback used to initialize a new काष्ठा inode
 * @data:	opaque data poपूर्णांकer to pass to @test and @set
 *
 * Search क्रम the inode specअगरied by @hashval and @data in the inode cache,
 * and अगर present it is वापस it with an increased reference count. This is
 * a variant of iget5_locked() क्रम callers that करोn't want to fail on memory
 * allocation of inode.
 *
 * If the inode is not in cache, insert the pre-allocated inode to cache and
 * वापस it locked, hashed, and with the I_NEW flag set. The file प्रणाली माला_लो
 * to fill it in beक्रमe unlocking it via unlock_new_inode().
 *
 * Note both @test and @set are called with the inode_hash_lock held, so can't
 * sleep.
 */
काष्ठा inode *inode_insert5(काष्ठा inode *inode, अचिन्हित दीर्घ hashval,
			    पूर्णांक (*test)(काष्ठा inode *, व्योम *),
			    पूर्णांक (*set)(काष्ठा inode *, व्योम *), व्योम *data)
अणु
	काष्ठा hlist_head *head = inode_hashtable + hash(inode->i_sb, hashval);
	काष्ठा inode *old;
	bool creating = inode->i_state & I_CREATING;

again:
	spin_lock(&inode_hash_lock);
	old = find_inode(inode->i_sb, head, test, data);
	अगर (unlikely(old)) अणु
		/*
		 * Uhhuh, somebody अन्यथा created the same inode under us.
		 * Use the old inode instead of the pपुनः_स्मृतिated one.
		 */
		spin_unlock(&inode_hash_lock);
		अगर (IS_ERR(old))
			वापस शून्य;
		रुको_on_inode(old);
		अगर (unlikely(inode_unhashed(old))) अणु
			iput(old);
			जाओ again;
		पूर्ण
		वापस old;
	पूर्ण

	अगर (set && unlikely(set(inode, data))) अणु
		inode = शून्य;
		जाओ unlock;
	पूर्ण

	/*
	 * Return the locked inode with I_NEW set, the
	 * caller is responsible क्रम filling in the contents
	 */
	spin_lock(&inode->i_lock);
	inode->i_state |= I_NEW;
	hlist_add_head_rcu(&inode->i_hash, head);
	spin_unlock(&inode->i_lock);
	अगर (!creating)
		inode_sb_list_add(inode);
unlock:
	spin_unlock(&inode_hash_lock);

	वापस inode;
पूर्ण
EXPORT_SYMBOL(inode_insert5);

/**
 * iget5_locked - obtain an inode from a mounted file प्रणाली
 * @sb:		super block of file प्रणाली
 * @hashval:	hash value (usually inode number) to get
 * @test:	callback used क्रम comparisons between inodes
 * @set:	callback used to initialize a new काष्ठा inode
 * @data:	opaque data poपूर्णांकer to pass to @test and @set
 *
 * Search क्रम the inode specअगरied by @hashval and @data in the inode cache,
 * and अगर present it is वापस it with an increased reference count. This is
 * a generalized version of iget_locked() क्रम file प्रणालीs where the inode
 * number is not sufficient क्रम unique identअगरication of an inode.
 *
 * If the inode is not in cache, allocate a new inode and वापस it locked,
 * hashed, and with the I_NEW flag set. The file प्रणाली माला_लो to fill it in
 * beक्रमe unlocking it via unlock_new_inode().
 *
 * Note both @test and @set are called with the inode_hash_lock held, so can't
 * sleep.
 */
काष्ठा inode *iget5_locked(काष्ठा super_block *sb, अचिन्हित दीर्घ hashval,
		पूर्णांक (*test)(काष्ठा inode *, व्योम *),
		पूर्णांक (*set)(काष्ठा inode *, व्योम *), व्योम *data)
अणु
	काष्ठा inode *inode = ilookup5(sb, hashval, test, data);

	अगर (!inode) अणु
		काष्ठा inode *new = alloc_inode(sb);

		अगर (new) अणु
			new->i_state = 0;
			inode = inode_insert5(new, hashval, test, set, data);
			अगर (unlikely(inode != new))
				destroy_inode(new);
		पूर्ण
	पूर्ण
	वापस inode;
पूर्ण
EXPORT_SYMBOL(iget5_locked);

/**
 * iget_locked - obtain an inode from a mounted file प्रणाली
 * @sb:		super block of file प्रणाली
 * @ino:	inode number to get
 *
 * Search क्रम the inode specअगरied by @ino in the inode cache and अगर present
 * वापस it with an increased reference count. This is क्रम file प्रणालीs
 * where the inode number is sufficient क्रम unique identअगरication of an inode.
 *
 * If the inode is not in cache, allocate a new inode and वापस it locked,
 * hashed, and with the I_NEW flag set.  The file प्रणाली माला_लो to fill it in
 * beक्रमe unlocking it via unlock_new_inode().
 */
काष्ठा inode *iget_locked(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा hlist_head *head = inode_hashtable + hash(sb, ino);
	काष्ठा inode *inode;
again:
	spin_lock(&inode_hash_lock);
	inode = find_inode_fast(sb, head, ino);
	spin_unlock(&inode_hash_lock);
	अगर (inode) अणु
		अगर (IS_ERR(inode))
			वापस शून्य;
		रुको_on_inode(inode);
		अगर (unlikely(inode_unhashed(inode))) अणु
			iput(inode);
			जाओ again;
		पूर्ण
		वापस inode;
	पूर्ण

	inode = alloc_inode(sb);
	अगर (inode) अणु
		काष्ठा inode *old;

		spin_lock(&inode_hash_lock);
		/* We released the lock, so.. */
		old = find_inode_fast(sb, head, ino);
		अगर (!old) अणु
			inode->i_ino = ino;
			spin_lock(&inode->i_lock);
			inode->i_state = I_NEW;
			hlist_add_head_rcu(&inode->i_hash, head);
			spin_unlock(&inode->i_lock);
			inode_sb_list_add(inode);
			spin_unlock(&inode_hash_lock);

			/* Return the locked inode with I_NEW set, the
			 * caller is responsible क्रम filling in the contents
			 */
			वापस inode;
		पूर्ण

		/*
		 * Uhhuh, somebody अन्यथा created the same inode under
		 * us. Use the old inode instead of the one we just
		 * allocated.
		 */
		spin_unlock(&inode_hash_lock);
		destroy_inode(inode);
		अगर (IS_ERR(old))
			वापस शून्य;
		inode = old;
		रुको_on_inode(inode);
		अगर (unlikely(inode_unhashed(inode))) अणु
			iput(inode);
			जाओ again;
		पूर्ण
	पूर्ण
	वापस inode;
पूर्ण
EXPORT_SYMBOL(iget_locked);

/*
 * search the inode cache क्रम a matching inode number.
 * If we find one, then the inode number we are trying to
 * allocate is not unique and so we should not use it.
 *
 * Returns 1 अगर the inode number is unique, 0 अगर it is not.
 */
अटल पूर्णांक test_inode_iunique(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा hlist_head *b = inode_hashtable + hash(sb, ino);
	काष्ठा inode *inode;

	hlist_क्रम_each_entry_rcu(inode, b, i_hash) अणु
		अगर (inode->i_ino == ino && inode->i_sb == sb)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/**
 *	iunique - get a unique inode number
 *	@sb: superblock
 *	@max_reserved: highest reserved inode number
 *
 *	Obtain an inode number that is unique on the प्रणाली क्रम a given
 *	superblock. This is used by file प्रणालीs that have no natural
 *	permanent inode numbering प्रणाली. An inode number is वापसed that
 *	is higher than the reserved limit but unique.
 *
 *	BUGS:
 *	With a large number of inodes live on the file प्रणाली this function
 *	currently becomes quite slow.
 */
ino_t iunique(काष्ठा super_block *sb, ino_t max_reserved)
अणु
	/*
	 * On a 32bit, non LFS stat() call, glibc will generate an EOVERFLOW
	 * error अगर st_ino won't fit in target काष्ठा field. Use 32bit counter
	 * here to attempt to aव्योम that.
	 */
	अटल DEFINE_SPINLOCK(iunique_lock);
	अटल अचिन्हित पूर्णांक counter;
	ino_t res;

	rcu_पढ़ो_lock();
	spin_lock(&iunique_lock);
	करो अणु
		अगर (counter <= max_reserved)
			counter = max_reserved + 1;
		res = counter++;
	पूर्ण जबतक (!test_inode_iunique(sb, res));
	spin_unlock(&iunique_lock);
	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण
EXPORT_SYMBOL(iunique);

काष्ठा inode *igrab(काष्ठा inode *inode)
अणु
	spin_lock(&inode->i_lock);
	अगर (!(inode->i_state & (I_FREEING|I_WILL_FREE))) अणु
		__iget(inode);
		spin_unlock(&inode->i_lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&inode->i_lock);
		/*
		 * Handle the हाल where s_op->clear_inode is not been
		 * called yet, and somebody is calling igrab
		 * जबतक the inode is getting मुक्तd.
		 */
		inode = शून्य;
	पूर्ण
	वापस inode;
पूर्ण
EXPORT_SYMBOL(igrab);

/**
 * ilookup5_noरुको - search क्रम an inode in the inode cache
 * @sb:		super block of file प्रणाली to search
 * @hashval:	hash value (usually inode number) to search क्रम
 * @test:	callback used क्रम comparisons between inodes
 * @data:	opaque data poपूर्णांकer to pass to @test
 *
 * Search क्रम the inode specअगरied by @hashval and @data in the inode cache.
 * If the inode is in the cache, the inode is वापसed with an incremented
 * reference count.
 *
 * Note: I_NEW is not रुकोed upon so you have to be very careful what you करो
 * with the वापसed inode.  You probably should be using ilookup5() instead.
 *
 * Note2: @test is called with the inode_hash_lock held, so can't sleep.
 */
काष्ठा inode *ilookup5_noरुको(काष्ठा super_block *sb, अचिन्हित दीर्घ hashval,
		पूर्णांक (*test)(काष्ठा inode *, व्योम *), व्योम *data)
अणु
	काष्ठा hlist_head *head = inode_hashtable + hash(sb, hashval);
	काष्ठा inode *inode;

	spin_lock(&inode_hash_lock);
	inode = find_inode(sb, head, test, data);
	spin_unlock(&inode_hash_lock);

	वापस IS_ERR(inode) ? शून्य : inode;
पूर्ण
EXPORT_SYMBOL(ilookup5_noरुको);

/**
 * ilookup5 - search क्रम an inode in the inode cache
 * @sb:		super block of file प्रणाली to search
 * @hashval:	hash value (usually inode number) to search क्रम
 * @test:	callback used क्रम comparisons between inodes
 * @data:	opaque data poपूर्णांकer to pass to @test
 *
 * Search क्रम the inode specअगरied by @hashval and @data in the inode cache,
 * and अगर the inode is in the cache, वापस the inode with an incremented
 * reference count.  Waits on I_NEW beक्रमe वापसing the inode.
 * वापसed with an incremented reference count.
 *
 * This is a generalized version of ilookup() क्रम file प्रणालीs where the
 * inode number is not sufficient क्रम unique identअगरication of an inode.
 *
 * Note: @test is called with the inode_hash_lock held, so can't sleep.
 */
काष्ठा inode *ilookup5(काष्ठा super_block *sb, अचिन्हित दीर्घ hashval,
		पूर्णांक (*test)(काष्ठा inode *, व्योम *), व्योम *data)
अणु
	काष्ठा inode *inode;
again:
	inode = ilookup5_noरुको(sb, hashval, test, data);
	अगर (inode) अणु
		रुको_on_inode(inode);
		अगर (unlikely(inode_unhashed(inode))) अणु
			iput(inode);
			जाओ again;
		पूर्ण
	पूर्ण
	वापस inode;
पूर्ण
EXPORT_SYMBOL(ilookup5);

/**
 * ilookup - search क्रम an inode in the inode cache
 * @sb:		super block of file प्रणाली to search
 * @ino:	inode number to search क्रम
 *
 * Search क्रम the inode @ino in the inode cache, and अगर the inode is in the
 * cache, the inode is वापसed with an incremented reference count.
 */
काष्ठा inode *ilookup(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा hlist_head *head = inode_hashtable + hash(sb, ino);
	काष्ठा inode *inode;
again:
	spin_lock(&inode_hash_lock);
	inode = find_inode_fast(sb, head, ino);
	spin_unlock(&inode_hash_lock);

	अगर (inode) अणु
		अगर (IS_ERR(inode))
			वापस शून्य;
		रुको_on_inode(inode);
		अगर (unlikely(inode_unhashed(inode))) अणु
			iput(inode);
			जाओ again;
		पूर्ण
	पूर्ण
	वापस inode;
पूर्ण
EXPORT_SYMBOL(ilookup);

/**
 * find_inode_noरुको - find an inode in the inode cache
 * @sb:		super block of file प्रणाली to search
 * @hashval:	hash value (usually inode number) to search क्रम
 * @match:	callback used क्रम comparisons between inodes
 * @data:	opaque data poपूर्णांकer to pass to @match
 *
 * Search क्रम the inode specअगरied by @hashval and @data in the inode
 * cache, where the helper function @match will वापस 0 अगर the inode
 * करोes not match, 1 अगर the inode करोes match, and -1 अगर the search
 * should be stopped.  The @match function must be responsible क्रम
 * taking the i_lock spin_lock and checking i_state क्रम an inode being
 * मुक्तd or being initialized, and incrementing the reference count
 * beक्रमe वापसing 1.  It also must not sleep, since it is called with
 * the inode_hash_lock spinlock held.
 *
 * This is a even more generalized version of ilookup5() when the
 * function must never block --- find_inode() can block in
 * __रुको_on_मुक्तing_inode() --- or when the caller can not increment
 * the reference count because the resulting iput() might cause an
 * inode eviction.  The tradeoff is that the @match funtion must be
 * very carefully implemented.
 */
काष्ठा inode *find_inode_noरुको(काष्ठा super_block *sb,
				अचिन्हित दीर्घ hashval,
				पूर्णांक (*match)(काष्ठा inode *, अचिन्हित दीर्घ,
					     व्योम *),
				व्योम *data)
अणु
	काष्ठा hlist_head *head = inode_hashtable + hash(sb, hashval);
	काष्ठा inode *inode, *ret_inode = शून्य;
	पूर्णांक mval;

	spin_lock(&inode_hash_lock);
	hlist_क्रम_each_entry(inode, head, i_hash) अणु
		अगर (inode->i_sb != sb)
			जारी;
		mval = match(inode, hashval, data);
		अगर (mval == 0)
			जारी;
		अगर (mval == 1)
			ret_inode = inode;
		जाओ out;
	पूर्ण
out:
	spin_unlock(&inode_hash_lock);
	वापस ret_inode;
पूर्ण
EXPORT_SYMBOL(find_inode_noरुको);

/**
 * find_inode_rcu - find an inode in the inode cache
 * @sb:		Super block of file प्रणाली to search
 * @hashval:	Key to hash
 * @test:	Function to test match on an inode
 * @data:	Data क्रम test function
 *
 * Search क्रम the inode specअगरied by @hashval and @data in the inode cache,
 * where the helper function @test will वापस 0 अगर the inode करोes not match
 * and 1 अगर it करोes.  The @test function must be responsible क्रम taking the
 * i_lock spin_lock and checking i_state क्रम an inode being मुक्तd or being
 * initialized.
 *
 * If successful, this will वापस the inode क्रम which the @test function
 * वापसed 1 and शून्य otherwise.
 *
 * The @test function is not permitted to take a ref on any inode presented.
 * It is also not permitted to sleep.
 *
 * The caller must hold the RCU पढ़ो lock.
 */
काष्ठा inode *find_inode_rcu(काष्ठा super_block *sb, अचिन्हित दीर्घ hashval,
			     पूर्णांक (*test)(काष्ठा inode *, व्योम *), व्योम *data)
अणु
	काष्ठा hlist_head *head = inode_hashtable + hash(sb, hashval);
	काष्ठा inode *inode;

	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_held(),
			 "suspicious find_inode_rcu() usage");

	hlist_क्रम_each_entry_rcu(inode, head, i_hash) अणु
		अगर (inode->i_sb == sb &&
		    !(READ_ONCE(inode->i_state) & (I_FREEING | I_WILL_FREE)) &&
		    test(inode, data))
			वापस inode;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(find_inode_rcu);

/**
 * find_inode_by_ino_rcu - Find an inode in the inode cache
 * @sb:		Super block of file प्रणाली to search
 * @ino:	The inode number to match
 *
 * Search क्रम the inode specअगरied by @hashval and @data in the inode cache,
 * where the helper function @test will वापस 0 अगर the inode करोes not match
 * and 1 अगर it करोes.  The @test function must be responsible क्रम taking the
 * i_lock spin_lock and checking i_state क्रम an inode being मुक्तd or being
 * initialized.
 *
 * If successful, this will वापस the inode क्रम which the @test function
 * वापसed 1 and शून्य otherwise.
 *
 * The @test function is not permitted to take a ref on any inode presented.
 * It is also not permitted to sleep.
 *
 * The caller must hold the RCU पढ़ो lock.
 */
काष्ठा inode *find_inode_by_ino_rcu(काष्ठा super_block *sb,
				    अचिन्हित दीर्घ ino)
अणु
	काष्ठा hlist_head *head = inode_hashtable + hash(sb, ino);
	काष्ठा inode *inode;

	RCU_LOCKDEP_WARN(!rcu_पढ़ो_lock_held(),
			 "suspicious find_inode_by_ino_rcu() usage");

	hlist_क्रम_each_entry_rcu(inode, head, i_hash) अणु
		अगर (inode->i_ino == ino &&
		    inode->i_sb == sb &&
		    !(READ_ONCE(inode->i_state) & (I_FREEING | I_WILL_FREE)))
		    वापस inode;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(find_inode_by_ino_rcu);

पूर्णांक insert_inode_locked(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	ino_t ino = inode->i_ino;
	काष्ठा hlist_head *head = inode_hashtable + hash(sb, ino);

	जबतक (1) अणु
		काष्ठा inode *old = शून्य;
		spin_lock(&inode_hash_lock);
		hlist_क्रम_each_entry(old, head, i_hash) अणु
			अगर (old->i_ino != ino)
				जारी;
			अगर (old->i_sb != sb)
				जारी;
			spin_lock(&old->i_lock);
			अगर (old->i_state & (I_FREEING|I_WILL_FREE)) अणु
				spin_unlock(&old->i_lock);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (likely(!old)) अणु
			spin_lock(&inode->i_lock);
			inode->i_state |= I_NEW | I_CREATING;
			hlist_add_head_rcu(&inode->i_hash, head);
			spin_unlock(&inode->i_lock);
			spin_unlock(&inode_hash_lock);
			वापस 0;
		पूर्ण
		अगर (unlikely(old->i_state & I_CREATING)) अणु
			spin_unlock(&old->i_lock);
			spin_unlock(&inode_hash_lock);
			वापस -EBUSY;
		पूर्ण
		__iget(old);
		spin_unlock(&old->i_lock);
		spin_unlock(&inode_hash_lock);
		रुको_on_inode(old);
		अगर (unlikely(!inode_unhashed(old))) अणु
			iput(old);
			वापस -EBUSY;
		पूर्ण
		iput(old);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(insert_inode_locked);

पूर्णांक insert_inode_locked4(काष्ठा inode *inode, अचिन्हित दीर्घ hashval,
		पूर्णांक (*test)(काष्ठा inode *, व्योम *), व्योम *data)
अणु
	काष्ठा inode *old;

	inode->i_state |= I_CREATING;
	old = inode_insert5(inode, hashval, test, शून्य, data);

	अगर (old != inode) अणु
		iput(old);
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(insert_inode_locked4);


पूर्णांक generic_delete_inode(काष्ठा inode *inode)
अणु
	वापस 1;
पूर्ण
EXPORT_SYMBOL(generic_delete_inode);

/*
 * Called when we're dropping the last reference
 * to an inode.
 *
 * Call the FS "drop_inode()" function, शेषing to
 * the legacy UNIX fileप्रणाली behaviour.  If it tells
 * us to evict inode, करो so.  Otherwise, retain inode
 * in cache अगर fs is alive, sync and evict अगर fs is
 * shutting करोwn.
 */
अटल व्योम iput_final(काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	स्थिर काष्ठा super_operations *op = inode->i_sb->s_op;
	अचिन्हित दीर्घ state;
	पूर्णांक drop;

	WARN_ON(inode->i_state & I_NEW);

	अगर (op->drop_inode)
		drop = op->drop_inode(inode);
	अन्यथा
		drop = generic_drop_inode(inode);

	अगर (!drop &&
	    !(inode->i_state & I_DONTCACHE) &&
	    (sb->s_flags & SB_ACTIVE)) अणु
		inode_add_lru(inode);
		spin_unlock(&inode->i_lock);
		वापस;
	पूर्ण

	state = inode->i_state;
	अगर (!drop) अणु
		WRITE_ONCE(inode->i_state, state | I_WILL_FREE);
		spin_unlock(&inode->i_lock);

		ग_लिखो_inode_now(inode, 1);

		spin_lock(&inode->i_lock);
		state = inode->i_state;
		WARN_ON(state & I_NEW);
		state &= ~I_WILL_FREE;
	पूर्ण

	WRITE_ONCE(inode->i_state, state | I_FREEING);
	अगर (!list_empty(&inode->i_lru))
		inode_lru_list_del(inode);
	spin_unlock(&inode->i_lock);

	evict(inode);
पूर्ण

/**
 *	iput	- put an inode
 *	@inode: inode to put
 *
 *	Puts an inode, dropping its usage count. If the inode use count hits
 *	zero, the inode is then मुक्तd and may also be destroyed.
 *
 *	Consequently, iput() can sleep.
 */
व्योम iput(काष्ठा inode *inode)
अणु
	अगर (!inode)
		वापस;
	BUG_ON(inode->i_state & I_CLEAR);
retry:
	अगर (atomic_dec_and_lock(&inode->i_count, &inode->i_lock)) अणु
		अगर (inode->i_nlink && (inode->i_state & I_सूचीTY_TIME)) अणु
			atomic_inc(&inode->i_count);
			spin_unlock(&inode->i_lock);
			trace_ग_लिखोback_lazyसमय_iput(inode);
			mark_inode_dirty_sync(inode);
			जाओ retry;
		पूर्ण
		iput_final(inode);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(iput);

#अगर_घोषित CONFIG_BLOCK
/**
 *	bmap	- find a block number in a file
 *	@inode:  inode owning the block number being requested
 *	@block: poपूर्णांकer containing the block to find
 *
 *	Replaces the value in ``*block`` with the block number on the device holding
 *	corresponding to the requested block number in the file.
 *	That is, asked क्रम block 4 of inode 1 the function will replace the
 *	4 in ``*block``, with disk block relative to the disk start that holds that
 *	block of the file.
 *
 *	Returns -EINVAL in हाल of error, 0 otherwise. If mapping falls पूर्णांकo a
 *	hole, वापसs 0 and ``*block`` is also set to 0.
 */
पूर्णांक bmap(काष्ठा inode *inode, sector_t *block)
अणु
	अगर (!inode->i_mapping->a_ops->bmap)
		वापस -EINVAL;

	*block = inode->i_mapping->a_ops->bmap(inode->i_mapping, *block);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(bmap);
#पूर्ण_अगर

/*
 * With relative aसमय, only update aसमय अगर the previous aसमय is
 * earlier than either the स_समय or mसमय or अगर at least a day has
 * passed since the last aसमय update.
 */
अटल पूर्णांक relaसमय_need_update(काष्ठा vfsmount *mnt, काष्ठा inode *inode,
			     काष्ठा बारpec64 now)
अणु

	अगर (!(mnt->mnt_flags & MNT_RELATIME))
		वापस 1;
	/*
	 * Is mसमय younger than aसमय? If yes, update aसमय:
	 */
	अगर (बारpec64_compare(&inode->i_mसमय, &inode->i_aसमय) >= 0)
		वापस 1;
	/*
	 * Is स_समय younger than aसमय? If yes, update aसमय:
	 */
	अगर (बारpec64_compare(&inode->i_स_समय, &inode->i_aसमय) >= 0)
		वापस 1;

	/*
	 * Is the previous aसमय value older than a day? If yes,
	 * update aसमय:
	 */
	अगर ((दीर्घ)(now.tv_sec - inode->i_aसमय.tv_sec) >= 24*60*60)
		वापस 1;
	/*
	 * Good, we can skip the aसमय update:
	 */
	वापस 0;
पूर्ण

पूर्णांक generic_update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *समय, पूर्णांक flags)
अणु
	पूर्णांक dirty_flags = 0;

	अगर (flags & (S_ATIME | S_CTIME | S_MTIME)) अणु
		अगर (flags & S_ATIME)
			inode->i_aसमय = *समय;
		अगर (flags & S_CTIME)
			inode->i_स_समय = *समय;
		अगर (flags & S_MTIME)
			inode->i_mसमय = *समय;

		अगर (inode->i_sb->s_flags & SB_LAZYTIME)
			dirty_flags |= I_सूचीTY_TIME;
		अन्यथा
			dirty_flags |= I_सूचीTY_SYNC;
	पूर्ण

	अगर ((flags & S_VERSION) && inode_maybe_inc_iversion(inode, false))
		dirty_flags |= I_सूचीTY_SYNC;

	__mark_inode_dirty(inode, dirty_flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(generic_update_समय);

/*
 * This करोes the actual work of updating an inodes समय or version.  Must have
 * had called mnt_want_ग_लिखो() beक्रमe calling this.
 */
अटल पूर्णांक update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *समय, पूर्णांक flags)
अणु
	अगर (inode->i_op->update_समय)
		वापस inode->i_op->update_समय(inode, समय, flags);
	वापस generic_update_समय(inode, समय, flags);
पूर्ण

/**
 *	aसमय_needs_update	-	update the access समय
 *	@path: the &काष्ठा path to update
 *	@inode: inode to update
 *
 *	Update the accessed समय on an inode and mark it क्रम ग_लिखोback.
 *	This function स्वतःmatically handles पढ़ो only file प्रणालीs and media,
 *	as well as the "noatime" flag and inode specअगरic "noatime" markers.
 */
bool aसमय_needs_update(स्थिर काष्ठा path *path, काष्ठा inode *inode)
अणु
	काष्ठा vfsmount *mnt = path->mnt;
	काष्ठा बारpec64 now;

	अगर (inode->i_flags & S_NOATIME)
		वापस false;

	/* Aसमय updates will likely cause i_uid and i_gid to be written
	 * back improprely अगर their true value is unknown to the vfs.
	 */
	अगर (HAS_UNMAPPED_ID(mnt_user_ns(mnt), inode))
		वापस false;

	अगर (IS_NOATIME(inode))
		वापस false;
	अगर ((inode->i_sb->s_flags & SB_NOसूचीATIME) && S_ISसूची(inode->i_mode))
		वापस false;

	अगर (mnt->mnt_flags & MNT_NOATIME)
		वापस false;
	अगर ((mnt->mnt_flags & MNT_NOसूचीATIME) && S_ISसूची(inode->i_mode))
		वापस false;

	now = current_समय(inode);

	अगर (!relaसमय_need_update(mnt, inode, now))
		वापस false;

	अगर (बारpec64_equal(&inode->i_aसमय, &now))
		वापस false;

	वापस true;
पूर्ण

व्योम touch_aसमय(स्थिर काष्ठा path *path)
अणु
	काष्ठा vfsmount *mnt = path->mnt;
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा बारpec64 now;

	अगर (!aसमय_needs_update(path, inode))
		वापस;

	अगर (!sb_start_ग_लिखो_trylock(inode->i_sb))
		वापस;

	अगर (__mnt_want_ग_लिखो(mnt) != 0)
		जाओ skip_update;
	/*
	 * File प्रणालीs can error out when updating inodes अगर they need to
	 * allocate new space to modअगरy an inode (such is the हाल क्रम
	 * Btrfs), but since we touch aसमय जबतक walking करोwn the path we
	 * really करोn't care अगर we failed to update the aसमय of the file,
	 * so just ignore the वापस value.
	 * We may also fail on fileप्रणालीs that have the ability to make parts
	 * of the fs पढ़ो only, e.g. subvolumes in Btrfs.
	 */
	now = current_समय(inode);
	update_समय(inode, &now, S_ATIME);
	__mnt_drop_ग_लिखो(mnt);
skip_update:
	sb_end_ग_लिखो(inode->i_sb);
पूर्ण
EXPORT_SYMBOL(touch_aसमय);

/*
 * The logic we want is
 *
 *	अगर suid or (sgid and xgrp)
 *		हटाओ privs
 */
पूर्णांक should_हटाओ_suid(काष्ठा dentry *dentry)
अणु
	umode_t mode = d_inode(dentry)->i_mode;
	पूर्णांक समाप्त = 0;

	/* suid always must be समाप्तed */
	अगर (unlikely(mode & S_ISUID))
		समाप्त = ATTR_KILL_SUID;

	/*
	 * sgid without any exec bits is just a mandatory locking mark; leave
	 * it alone.  If some exec bits are set, it's a real sgid; समाप्त it.
	 */
	अगर (unlikely((mode & S_ISGID) && (mode & S_IXGRP)))
		समाप्त |= ATTR_KILL_SGID;

	अगर (unlikely(समाप्त && !capable(CAP_FSETID) && S_ISREG(mode)))
		वापस समाप्त;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(should_हटाओ_suid);

/*
 * Return mask of changes क्रम notअगरy_change() that need to be करोne as a
 * response to ग_लिखो or truncate. Return 0 अगर nothing has to be changed.
 * Negative value on error (change should be denied).
 */
पूर्णांक dentry_needs_हटाओ_privs(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक mask = 0;
	पूर्णांक ret;

	अगर (IS_NOSEC(inode))
		वापस 0;

	mask = should_हटाओ_suid(dentry);
	ret = security_inode_need_समाप्तpriv(dentry);
	अगर (ret < 0)
		वापस ret;
	अगर (ret)
		mask |= ATTR_KILL_PRIV;
	वापस mask;
पूर्ण

अटल पूर्णांक __हटाओ_privs(काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *dentry, पूर्णांक समाप्त)
अणु
	काष्ठा iattr newattrs;

	newattrs.ia_valid = ATTR_FORCE | समाप्त;
	/*
	 * Note we call this on ग_लिखो, so notअगरy_change will not
	 * encounter any conflicting delegations:
	 */
	वापस notअगरy_change(mnt_userns, dentry, &newattrs, शून्य);
पूर्ण

/*
 * Remove special file priviledges (suid, capabilities) when file is written
 * to or truncated.
 */
पूर्णांक file_हटाओ_privs(काष्ठा file *file)
अणु
	काष्ठा dentry *dentry = file_dentry(file);
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक समाप्त;
	पूर्णांक error = 0;

	/*
	 * Fast path क्रम nothing security related.
	 * As well क्रम non-regular files, e.g. blkdev inodes.
	 * For example, blkdev_ग_लिखो_iter() might get here
	 * trying to हटाओ privs which it is not allowed to.
	 */
	अगर (IS_NOSEC(inode) || !S_ISREG(inode->i_mode))
		वापस 0;

	समाप्त = dentry_needs_हटाओ_privs(dentry);
	अगर (समाप्त < 0)
		वापस समाप्त;
	अगर (समाप्त)
		error = __हटाओ_privs(file_mnt_user_ns(file), dentry, समाप्त);
	अगर (!error)
		inode_has_no_xattr(inode);

	वापस error;
पूर्ण
EXPORT_SYMBOL(file_हटाओ_privs);

/**
 *	file_update_समय	-	update mसमय and स_समय समय
 *	@file: file accessed
 *
 *	Update the mसमय and स_समय members of an inode and mark the inode
 *	क्रम ग_लिखोback.  Note that this function is meant exclusively क्रम
 *	usage in the file ग_लिखो path of fileप्रणालीs, and fileप्रणालीs may
 *	choose to explicitly ignore update via this function with the
 *	S_NOCMTIME inode flag, e.g. क्रम network fileप्रणाली where these
 *	बारtamps are handled by the server.  This can वापस an error क्रम
 *	file प्रणालीs who need to allocate space in order to update an inode.
 */

पूर्णांक file_update_समय(काष्ठा file *file)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा बारpec64 now;
	पूर्णांक sync_it = 0;
	पूर्णांक ret;

	/* First try to exhaust all avenues to not sync */
	अगर (IS_NOCMTIME(inode))
		वापस 0;

	now = current_समय(inode);
	अगर (!बारpec64_equal(&inode->i_mसमय, &now))
		sync_it = S_MTIME;

	अगर (!बारpec64_equal(&inode->i_स_समय, &now))
		sync_it |= S_CTIME;

	अगर (IS_I_VERSION(inode) && inode_iversion_need_inc(inode))
		sync_it |= S_VERSION;

	अगर (!sync_it)
		वापस 0;

	/* Finally allowed to ग_लिखो? Takes lock. */
	अगर (__mnt_want_ग_लिखो_file(file))
		वापस 0;

	ret = update_समय(inode, &now, sync_it);
	__mnt_drop_ग_लिखो_file(file);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(file_update_समय);

/* Caller must hold the file's inode lock */
पूर्णांक file_modअगरied(काष्ठा file *file)
अणु
	पूर्णांक err;

	/*
	 * Clear the security bits अगर the process is not being run by root.
	 * This keeps people from modअगरying setuid and setgid binaries.
	 */
	err = file_हटाओ_privs(file);
	अगर (err)
		वापस err;

	अगर (unlikely(file->f_mode & FMODE_NOCMTIME))
		वापस 0;

	वापस file_update_समय(file);
पूर्ण
EXPORT_SYMBOL(file_modअगरied);

पूर्णांक inode_needs_sync(काष्ठा inode *inode)
अणु
	अगर (IS_SYNC(inode))
		वापस 1;
	अगर (S_ISसूची(inode->i_mode) && IS_सूचीSYNC(inode))
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(inode_needs_sync);

/*
 * If we try to find an inode in the inode hash जबतक it is being
 * deleted, we have to रुको until the fileप्रणाली completes its
 * deletion beक्रमe reporting that it isn't found.  This function रुकोs
 * until the deletion _might_ have completed.  Callers are responsible
 * to recheck inode state.
 *
 * It करोesn't matter अगर I_NEW is not set initially, a call to
 * wake_up_bit(&inode->i_state, __I_NEW) after removing from the hash list
 * will DTRT.
 */
अटल व्योम __रुको_on_मुक्तing_inode(काष्ठा inode *inode)
अणु
	रुको_queue_head_t *wq;
	DEFINE_WAIT_BIT(रुको, &inode->i_state, __I_NEW);
	wq = bit_रुकोqueue(&inode->i_state, __I_NEW);
	prepare_to_रुको(wq, &रुको.wq_entry, TASK_UNINTERRUPTIBLE);
	spin_unlock(&inode->i_lock);
	spin_unlock(&inode_hash_lock);
	schedule();
	finish_रुको(wq, &रुको.wq_entry);
	spin_lock(&inode_hash_lock);
पूर्ण

अटल __initdata अचिन्हित दीर्घ ihash_entries;
अटल पूर्णांक __init set_ihash_entries(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;
	ihash_entries = simple_म_से_अदीर्घ(str, &str, 0);
	वापस 1;
पूर्ण
__setup("ihash_entries=", set_ihash_entries);

/*
 * Initialize the रुकोqueues and inode hash table.
 */
व्योम __init inode_init_early(व्योम)
अणु
	/* If hashes are distributed across NUMA nodes, defer
	 * hash allocation until vदो_स्मृति space is available.
	 */
	अगर (hashdist)
		वापस;

	inode_hashtable =
		alloc_large_प्रणाली_hash("Inode-cache",
					माप(काष्ठा hlist_head),
					ihash_entries,
					14,
					HASH_EARLY | HASH_ZERO,
					&i_hash_shअगरt,
					&i_hash_mask,
					0,
					0);
पूर्ण

व्योम __init inode_init(व्योम)
अणु
	/* inode slab cache */
	inode_cachep = kmem_cache_create("inode_cache",
					 माप(काष्ठा inode),
					 0,
					 (SLAB_RECLAIM_ACCOUNT|SLAB_PANIC|
					 SLAB_MEM_SPREAD|SLAB_ACCOUNT),
					 init_once);

	/* Hash may have been set up in inode_init_early */
	अगर (!hashdist)
		वापस;

	inode_hashtable =
		alloc_large_प्रणाली_hash("Inode-cache",
					माप(काष्ठा hlist_head),
					ihash_entries,
					14,
					HASH_ZERO,
					&i_hash_shअगरt,
					&i_hash_mask,
					0,
					0);
पूर्ण

व्योम init_special_inode(काष्ठा inode *inode, umode_t mode, dev_t rdev)
अणु
	inode->i_mode = mode;
	अगर (S_ISCHR(mode)) अणु
		inode->i_fop = &def_chr_fops;
		inode->i_rdev = rdev;
	पूर्ण अन्यथा अगर (S_ISBLK(mode)) अणु
		inode->i_fop = &def_blk_fops;
		inode->i_rdev = rdev;
	पूर्ण अन्यथा अगर (S_ISFIFO(mode))
		inode->i_fop = &pipefअगरo_fops;
	अन्यथा अगर (S_ISSOCK(mode))
		;	/* leave it no_खोलो_fops */
	अन्यथा
		prपूर्णांकk(KERN_DEBUG "init_special_inode: bogus i_mode (%o) for"
				  " inode %s:%lu\n", mode, inode->i_sb->s_id,
				  inode->i_ino);
पूर्ण
EXPORT_SYMBOL(init_special_inode);

/**
 * inode_init_owner - Init uid,gid,mode क्रम new inode according to posix standards
 * @mnt_userns:	User namespace of the mount the inode was created from
 * @inode: New inode
 * @dir: Directory inode
 * @mode: mode of the new inode
 *
 * If the inode has been created through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions
 * and initializing i_uid and i_gid. On non-idmapped mounts or अगर permission
 * checking is to be perक्रमmed on the raw inode simply passs init_user_ns.
 */
व्योम inode_init_owner(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		      स्थिर काष्ठा inode *dir, umode_t mode)
अणु
	inode_fsuid_set(inode, mnt_userns);
	अगर (dir && dir->i_mode & S_ISGID) अणु
		inode->i_gid = dir->i_gid;

		/* Directories are special, and always inherit S_ISGID */
		अगर (S_ISसूची(mode))
			mode |= S_ISGID;
		अन्यथा अगर ((mode & (S_ISGID | S_IXGRP)) == (S_ISGID | S_IXGRP) &&
			 !in_group_p(i_gid_पूर्णांकo_mnt(mnt_userns, dir)) &&
			 !capable_wrt_inode_uidgid(mnt_userns, dir, CAP_FSETID))
			mode &= ~S_ISGID;
	पूर्ण अन्यथा
		inode_fsgid_set(inode, mnt_userns);
	inode->i_mode = mode;
पूर्ण
EXPORT_SYMBOL(inode_init_owner);

/**
 * inode_owner_or_capable - check current task permissions to inode
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @inode: inode being checked
 *
 * Return true अगर current either has CAP_FOWNER in a namespace with the
 * inode owner uid mapped, or owns the file.
 *
 * If the inode has been found through an idmapped mount the user namespace of
 * the vfsmount must be passed through @mnt_userns. This function will then take
 * care to map the inode according to @mnt_userns beक्रमe checking permissions.
 * On non-idmapped mounts or अगर permission checking is to be perक्रमmed on the
 * raw inode simply passs init_user_ns.
 */
bool inode_owner_or_capable(काष्ठा user_namespace *mnt_userns,
			    स्थिर काष्ठा inode *inode)
अणु
	kuid_t i_uid;
	काष्ठा user_namespace *ns;

	i_uid = i_uid_पूर्णांकo_mnt(mnt_userns, inode);
	अगर (uid_eq(current_fsuid(), i_uid))
		वापस true;

	ns = current_user_ns();
	अगर (kuid_has_mapping(ns, i_uid) && ns_capable(ns, CAP_FOWNER))
		वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL(inode_owner_or_capable);

/*
 * Direct i/o helper functions
 */
अटल व्योम __inode_dio_रुको(काष्ठा inode *inode)
अणु
	रुको_queue_head_t *wq = bit_रुकोqueue(&inode->i_state, __I_DIO_WAKEUP);
	DEFINE_WAIT_BIT(q, &inode->i_state, __I_DIO_WAKEUP);

	करो अणु
		prepare_to_रुको(wq, &q.wq_entry, TASK_UNINTERRUPTIBLE);
		अगर (atomic_पढ़ो(&inode->i_dio_count))
			schedule();
	पूर्ण जबतक (atomic_पढ़ो(&inode->i_dio_count));
	finish_रुको(wq, &q.wq_entry);
पूर्ण

/**
 * inode_dio_रुको - रुको क्रम outstanding DIO requests to finish
 * @inode: inode to रुको क्रम
 *
 * Waits क्रम all pending direct I/O requests to finish so that we can
 * proceed with a truncate or equivalent operation.
 *
 * Must be called under a lock that serializes taking new references
 * to i_dio_count, usually by inode->i_mutex.
 */
व्योम inode_dio_रुको(काष्ठा inode *inode)
अणु
	अगर (atomic_पढ़ो(&inode->i_dio_count))
		__inode_dio_रुको(inode);
पूर्ण
EXPORT_SYMBOL(inode_dio_रुको);

/*
 * inode_set_flags - atomically set some inode flags
 *
 * Note: the caller should be holding i_mutex, or अन्यथा be sure that
 * they have exclusive access to the inode काष्ठाure (i.e., जबतक the
 * inode is being instantiated).  The reason क्रम the cmpxchg() loop
 * --- which wouldn't be necessary अगर all code paths which modअगरy
 * i_flags actually followed this rule, is that there is at least one
 * code path which करोesn't today so we use cmpxchg() out of an abundance
 * of caution.
 *
 * In the दीर्घ run, i_mutex is overसमाप्त, and we should probably look
 * at using the i_lock spinlock to protect i_flags, and then make sure
 * it is so करोcumented in include/linux/fs.h and that all code follows
 * the locking convention!!
 */
व्योम inode_set_flags(काष्ठा inode *inode, अचिन्हित पूर्णांक flags,
		     अचिन्हित पूर्णांक mask)
अणु
	WARN_ON_ONCE(flags & ~mask);
	set_mask_bits(&inode->i_flags, mask, flags);
पूर्ण
EXPORT_SYMBOL(inode_set_flags);

व्योम inode_nohighmem(काष्ठा inode *inode)
अणु
	mapping_set_gfp_mask(inode->i_mapping, GFP_USER);
पूर्ण
EXPORT_SYMBOL(inode_nohighmem);

/**
 * बारtamp_truncate - Truncate बारpec to a granularity
 * @t: Timespec
 * @inode: inode being updated
 *
 * Truncate a बारpec to the granularity supported by the fs
 * containing the inode. Always rounds करोwn. gran must
 * not be 0 nor greater than a second (NSEC_PER_SEC, or 10^9 ns).
 */
काष्ठा बारpec64 बारtamp_truncate(काष्ठा बारpec64 t, काष्ठा inode *inode)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित पूर्णांक gran = sb->s_समय_gran;

	t.tv_sec = clamp(t.tv_sec, sb->s_समय_min, sb->s_समय_max);
	अगर (unlikely(t.tv_sec == sb->s_समय_max || t.tv_sec == sb->s_समय_min))
		t.tv_nsec = 0;

	/* Aव्योम भागision in the common हालs 1 ns and 1 s. */
	अगर (gran == 1)
		; /* nothing */
	अन्यथा अगर (gran == NSEC_PER_SEC)
		t.tv_nsec = 0;
	अन्यथा अगर (gran > 1 && gran < NSEC_PER_SEC)
		t.tv_nsec -= t.tv_nsec % gran;
	अन्यथा
		WARN(1, "invalid file time granularity: %u", gran);
	वापस t;
पूर्ण
EXPORT_SYMBOL(बारtamp_truncate);

/**
 * current_समय - Return FS समय
 * @inode: inode.
 *
 * Return the current समय truncated to the समय granularity supported by
 * the fs.
 *
 * Note that inode and inode->sb cannot be शून्य.
 * Otherwise, the function warns and वापसs समय without truncation.
 */
काष्ठा बारpec64 current_समय(काष्ठा inode *inode)
अणु
	काष्ठा बारpec64 now;

	kसमय_get_coarse_real_ts64(&now);

	अगर (unlikely(!inode->i_sb)) अणु
		WARN(1, "current_time() called with uninitialized super_block in the inode");
		वापस now;
	पूर्ण

	वापस बारtamp_truncate(now, inode);
पूर्ण
EXPORT_SYMBOL(current_समय);
