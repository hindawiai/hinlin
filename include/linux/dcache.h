<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_DCACHE_H
#घोषणा __LINUX_DCACHE_H

#समावेश <linux/atomic.h>
#समावेश <linux/list.h>
#समावेश <linux/गणित.स>
#समावेश <linux/rculist.h>
#समावेश <linux/rculist_bl.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/cache.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/lockref.h>
#समावेश <linux/stringhash.h>
#समावेश <linux/रुको.h>

काष्ठा path;
काष्ठा vfsmount;

/*
 * linux/include/linux/dcache.h
 *
 * Dirent cache data काष्ठाures
 *
 * (C) Copyright 1997 Thomas Schoebel-Theuer,
 * with heavy changes by Linus Torvalds
 */

#घोषणा IS_ROOT(x) ((x) == (x)->d_parent)

/* The hash is always the low bits of hash_len */
#अगर_घोषित __LITTLE_ENDIAN
 #घोषणा HASH_LEN_DECLARE u32 hash; u32 len
 #घोषणा bytemask_from_count(cnt)	(~(~0ul << (cnt)*8))
#अन्यथा
 #घोषणा HASH_LEN_DECLARE u32 len; u32 hash
 #घोषणा bytemask_from_count(cnt)	(~(~0ul >> (cnt)*8))
#पूर्ण_अगर

/*
 * "quick string" -- eases parameter passing, but more importantly
 * saves "metadata" about the string (ie length and the hash).
 *
 * hash comes first so it snuggles against d_parent in the
 * dentry.
 */
काष्ठा qstr अणु
	जोड़ अणु
		काष्ठा अणु
			HASH_LEN_DECLARE;
		पूर्ण;
		u64 hash_len;
	पूर्ण;
	स्थिर अचिन्हित अक्षर *name;
पूर्ण;

#घोषणा QSTR_INIT(n,l) अणु अणु अणु .len = l पूर्ण पूर्ण, .name = n पूर्ण

बाह्य स्थिर काष्ठा qstr empty_name;
बाह्य स्थिर काष्ठा qstr slash_name;
बाह्य स्थिर काष्ठा qstr करोtकरोt_name;

काष्ठा dentry_stat_t अणु
	दीर्घ nr_dentry;
	दीर्घ nr_unused;
	दीर्घ age_limit;		/* age in seconds */
	दीर्घ want_pages;	/* pages requested by प्रणाली */
	दीर्घ nr_negative;	/* # of unused negative dentries */
	दीर्घ dummy;		/* Reserved क्रम future use */
पूर्ण;
बाह्य काष्ठा dentry_stat_t dentry_stat;

/*
 * Try to keep काष्ठा dentry aligned on 64 byte cachelines (this will
 * give reasonable cacheline footprपूर्णांक with larger lines without the
 * large memory footprपूर्णांक increase).
 */
#अगर_घोषित CONFIG_64BIT
# define DNAME_INLINE_LEN 32 /* 192 bytes */
#अन्यथा
# अगरdef CONFIG_SMP
#  define DNAME_INLINE_LEN 36 /* 128 bytes */
# अन्यथा
#  define DNAME_INLINE_LEN 40 /* 128 bytes */
# endअगर
#पूर्ण_अगर

#घोषणा d_lock	d_lockref.lock

काष्ठा dentry अणु
	/* RCU lookup touched fields */
	अचिन्हित पूर्णांक d_flags;		/* रक्षित by d_lock */
	seqcount_spinlock_t d_seq;	/* per dentry seqlock */
	काष्ठा hlist_bl_node d_hash;	/* lookup hash list */
	काष्ठा dentry *d_parent;	/* parent directory */
	काष्ठा qstr d_name;
	काष्ठा inode *d_inode;		/* Where the name beदीर्घs to - शून्य is
					 * negative */
	अचिन्हित अक्षर d_iname[DNAME_INLINE_LEN];	/* small names */

	/* Ref lookup also touches following */
	काष्ठा lockref d_lockref;	/* per-dentry lock and refcount */
	स्थिर काष्ठा dentry_operations *d_op;
	काष्ठा super_block *d_sb;	/* The root of the dentry tree */
	अचिन्हित दीर्घ d_समय;		/* used by d_revalidate */
	व्योम *d_fsdata;			/* fs-specअगरic data */

	जोड़ अणु
		काष्ठा list_head d_lru;		/* LRU list */
		रुको_queue_head_t *d_रुको;	/* in-lookup ones only */
	पूर्ण;
	काष्ठा list_head d_child;	/* child of parent list */
	काष्ठा list_head d_subdirs;	/* our children */
	/*
	 * d_alias and d_rcu can share memory
	 */
	जोड़ अणु
		काष्ठा hlist_node d_alias;	/* inode alias list */
		काष्ठा hlist_bl_node d_in_lookup_hash;	/* only क्रम in-lookup ones */
	 	काष्ठा rcu_head d_rcu;
	पूर्ण d_u;
पूर्ण __अक्रमomize_layout;

/*
 * dentry->d_lock spinlock nesting subclasses:
 *
 * 0: normal
 * 1: nested
 */
क्रमागत dentry_d_lock_class
अणु
	DENTRY_D_LOCK_NORMAL, /* implicitly used by plain spin_lock() APIs. */
	DENTRY_D_LOCK_NESTED
पूर्ण;

काष्ठा dentry_operations अणु
	पूर्णांक (*d_revalidate)(काष्ठा dentry *, अचिन्हित पूर्णांक);
	पूर्णांक (*d_weak_revalidate)(काष्ठा dentry *, अचिन्हित पूर्णांक);
	पूर्णांक (*d_hash)(स्थिर काष्ठा dentry *, काष्ठा qstr *);
	पूर्णांक (*d_compare)(स्थिर काष्ठा dentry *,
			अचिन्हित पूर्णांक, स्थिर अक्षर *, स्थिर काष्ठा qstr *);
	पूर्णांक (*d_delete)(स्थिर काष्ठा dentry *);
	पूर्णांक (*d_init)(काष्ठा dentry *);
	व्योम (*d_release)(काष्ठा dentry *);
	व्योम (*d_prune)(काष्ठा dentry *);
	व्योम (*d_iput)(काष्ठा dentry *, काष्ठा inode *);
	अक्षर *(*d_dname)(काष्ठा dentry *, अक्षर *, पूर्णांक);
	काष्ठा vfsmount *(*d_स्वतःmount)(काष्ठा path *);
	पूर्णांक (*d_manage)(स्थिर काष्ठा path *, bool);
	काष्ठा dentry *(*d_real)(काष्ठा dentry *, स्थिर काष्ठा inode *);
पूर्ण ____cacheline_aligned;

/*
 * Locking rules क्रम dentry_operations callbacks are to be found in
 * Documentation/fileप्रणालीs/locking.rst. Keep it updated!
 *
 * FUrther descriptions are found in Documentation/fileप्रणालीs/vfs.rst.
 * Keep it updated too!
 */

/* d_flags entries */
#घोषणा DCACHE_OP_HASH			0x00000001
#घोषणा DCACHE_OP_COMPARE		0x00000002
#घोषणा DCACHE_OP_REVALIDATE		0x00000004
#घोषणा DCACHE_OP_DELETE		0x00000008
#घोषणा DCACHE_OP_PRUNE			0x00000010

#घोषणा	DCACHE_DISCONNECTED		0x00000020
     /* This dentry is possibly not currently connected to the dcache tree, in
      * which हाल its parent will either be itself, or will have this flag as
      * well.  nfsd will not use a dentry with this bit set, but will first
      * endeavour to clear the bit either by discovering that it is connected,
      * or by perक्रमming lookup operations.   Any fileप्रणाली which supports
      * nfsd_operations MUST have a lookup function which, अगर it finds a
      * directory inode with a DCACHE_DISCONNECTED dentry, will d_move that
      * dentry पूर्णांकo place and वापस that dentry rather than the passed one,
      * typically using d_splice_alias. */

#घोषणा DCACHE_REFERENCED		0x00000040 /* Recently used, करोn't discard. */

#घोषणा DCACHE_DONTCACHE		0x00000080 /* Purge from memory on final dput() */

#घोषणा DCACHE_CANT_MOUNT		0x00000100
#घोषणा DCACHE_GENOCIDE			0x00000200
#घोषणा DCACHE_SHRINK_LIST		0x00000400

#घोषणा DCACHE_OP_WEAK_REVALIDATE	0x00000800

#घोषणा DCACHE_NFSFS_RENAMED		0x00001000
     /* this dentry has been "silly renamed" and has to be deleted on the last
      * dput() */
#घोषणा DCACHE_COOKIE			0x00002000 /* For use by dcookie subप्रणाली */
#घोषणा DCACHE_FSNOTIFY_PARENT_WATCHED	0x00004000
     /* Parent inode is watched by some fsnotअगरy listener */

#घोषणा DCACHE_DENTRY_KILLED		0x00008000

#घोषणा DCACHE_MOUNTED			0x00010000 /* is a mountpoपूर्णांक */
#घोषणा DCACHE_NEED_AUTOMOUNT		0x00020000 /* handle स्वतःmount on this dir */
#घोषणा DCACHE_MANAGE_TRANSIT		0x00040000 /* manage transit from this dirent */
#घोषणा DCACHE_MANAGED_DENTRY \
	(DCACHE_MOUNTED|DCACHE_NEED_AUTOMOUNT|DCACHE_MANAGE_TRANSIT)

#घोषणा DCACHE_LRU_LIST			0x00080000

#घोषणा DCACHE_ENTRY_TYPE		0x00700000
#घोषणा DCACHE_MISS_TYPE		0x00000000 /* Negative dentry (maybe fallthru to nowhere) */
#घोषणा DCACHE_WHITEOUT_TYPE		0x00100000 /* Whiteout dentry (stop pathwalk) */
#घोषणा DCACHE_सूचीECTORY_TYPE		0x00200000 /* Normal directory */
#घोषणा DCACHE_AUTOसूची_TYPE		0x00300000 /* Lookupless directory (presumed स्वतःmount) */
#घोषणा DCACHE_REGULAR_TYPE		0x00400000 /* Regular file type (or fallthru to such) */
#घोषणा DCACHE_SPECIAL_TYPE		0x00500000 /* Other file type (or fallthru to such) */
#घोषणा DCACHE_SYMLINK_TYPE		0x00600000 /* Symlink (or fallthru to such) */

#घोषणा DCACHE_MAY_FREE			0x00800000
#घोषणा DCACHE_FALLTHRU			0x01000000 /* Fall through to lower layer */
#घोषणा DCACHE_NOKEY_NAME		0x02000000 /* Encrypted name encoded without key */
#घोषणा DCACHE_OP_REAL			0x04000000

#घोषणा DCACHE_PAR_LOOKUP		0x10000000 /* being looked up (with parent locked shared) */
#घोषणा DCACHE_DENTRY_CURSOR		0x20000000
#घोषणा DCACHE_NORCU			0x40000000 /* No RCU delay क्रम मुक्तing */

बाह्य seqlock_t नाम_lock;

/*
 * These are the low-level FS पूर्णांकerfaces to the dcache..
 */
बाह्य व्योम d_instantiate(काष्ठा dentry *, काष्ठा inode *);
बाह्य व्योम d_instantiate_new(काष्ठा dentry *, काष्ठा inode *);
बाह्य काष्ठा dentry * d_instantiate_unique(काष्ठा dentry *, काष्ठा inode *);
बाह्य काष्ठा dentry * d_instantiate_anon(काष्ठा dentry *, काष्ठा inode *);
बाह्य व्योम __d_drop(काष्ठा dentry *dentry);
बाह्य व्योम d_drop(काष्ठा dentry *dentry);
बाह्य व्योम d_delete(काष्ठा dentry *);
बाह्य व्योम d_set_d_op(काष्ठा dentry *dentry, स्थिर काष्ठा dentry_operations *op);

/* allocate/de-allocate */
बाह्य काष्ठा dentry * d_alloc(काष्ठा dentry *, स्थिर काष्ठा qstr *);
बाह्य काष्ठा dentry * d_alloc_anon(काष्ठा super_block *);
बाह्य काष्ठा dentry * d_alloc_parallel(काष्ठा dentry *, स्थिर काष्ठा qstr *,
					रुको_queue_head_t *);
बाह्य काष्ठा dentry * d_splice_alias(काष्ठा inode *, काष्ठा dentry *);
बाह्य काष्ठा dentry * d_add_ci(काष्ठा dentry *, काष्ठा inode *, काष्ठा qstr *);
बाह्य काष्ठा dentry * d_exact_alias(काष्ठा dentry *, काष्ठा inode *);
बाह्य काष्ठा dentry *d_find_any_alias(काष्ठा inode *inode);
बाह्य काष्ठा dentry * d_obtain_alias(काष्ठा inode *);
बाह्य काष्ठा dentry * d_obtain_root(काष्ठा inode *);
बाह्य व्योम shrink_dcache_sb(काष्ठा super_block *);
बाह्य व्योम shrink_dcache_parent(काष्ठा dentry *);
बाह्य व्योम shrink_dcache_क्रम_umount(काष्ठा super_block *);
बाह्य व्योम d_invalidate(काष्ठा dentry *);

/* only used at mount-समय */
बाह्य काष्ठा dentry * d_make_root(काष्ठा inode *);

/* <clickety>-<click> the ramfs-type tree */
बाह्य व्योम d_genocide(काष्ठा dentry *);

बाह्य व्योम d_क्षणिक_ख(काष्ठा dentry *, काष्ठा inode *);

बाह्य काष्ठा dentry *d_find_alias(काष्ठा inode *);
बाह्य व्योम d_prune_aliases(काष्ठा inode *);

बाह्य काष्ठा dentry *d_find_alias_rcu(काष्ठा inode *);

/* test whether we have any submounts in a subdir tree */
बाह्य पूर्णांक path_has_submounts(स्थिर काष्ठा path *);

/*
 * This adds the entry to the hash queues.
 */
बाह्य व्योम d_rehash(काष्ठा dentry *);
 
बाह्य व्योम d_add(काष्ठा dentry *, काष्ठा inode *);

/* used क्रम नाम() and baskets */
बाह्य व्योम d_move(काष्ठा dentry *, काष्ठा dentry *);
बाह्य व्योम d_exchange(काष्ठा dentry *, काष्ठा dentry *);
बाह्य काष्ठा dentry *d_ancestor(काष्ठा dentry *, काष्ठा dentry *);

/* appendix may either be शून्य or be used क्रम transname suffixes */
बाह्य काष्ठा dentry *d_lookup(स्थिर काष्ठा dentry *, स्थिर काष्ठा qstr *);
बाह्य काष्ठा dentry *d_hash_and_lookup(काष्ठा dentry *, काष्ठा qstr *);
बाह्य काष्ठा dentry *__d_lookup(स्थिर काष्ठा dentry *, स्थिर काष्ठा qstr *);
बाह्य काष्ठा dentry *__d_lookup_rcu(स्थिर काष्ठा dentry *parent,
				स्थिर काष्ठा qstr *name, अचिन्हित *seq);

अटल अंतरभूत अचिन्हित d_count(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_lockref.count;
पूर्ण

/*
 * helper function क्रम dentry_operations.d_dname() members
 */
बाह्य __म_लिखो(4, 5)
अक्षर *dynamic_dname(काष्ठा dentry *, अक्षर *, पूर्णांक, स्थिर अक्षर *, ...);

बाह्य अक्षर *__d_path(स्थिर काष्ठा path *, स्थिर काष्ठा path *, अक्षर *, पूर्णांक);
बाह्य अक्षर *d_असलolute_path(स्थिर काष्ठा path *, अक्षर *, पूर्णांक);
बाह्य अक्षर *d_path(स्थिर काष्ठा path *, अक्षर *, पूर्णांक);
बाह्य अक्षर *dentry_path_raw(स्थिर काष्ठा dentry *, अक्षर *, पूर्णांक);
बाह्य अक्षर *dentry_path(स्थिर काष्ठा dentry *, अक्षर *, पूर्णांक);

/* Allocation counts.. */

/**
 *	dget, dget_dlock -	get a reference to a dentry
 *	@dentry: dentry to get a reference to
 *
 *	Given a dentry or %शून्य poपूर्णांकer increment the reference count
 *	अगर appropriate and वापस the dentry. A dentry will not be 
 *	destroyed when it has references.
 */
अटल अंतरभूत काष्ठा dentry *dget_dlock(काष्ठा dentry *dentry)
अणु
	अगर (dentry)
		dentry->d_lockref.count++;
	वापस dentry;
पूर्ण

अटल अंतरभूत काष्ठा dentry *dget(काष्ठा dentry *dentry)
अणु
	अगर (dentry)
		lockref_get(&dentry->d_lockref);
	वापस dentry;
पूर्ण

बाह्य काष्ठा dentry *dget_parent(काष्ठा dentry *dentry);

/**
 *	d_unhashed -	is dentry hashed
 *	@dentry: entry to check
 *
 *	Returns true अगर the dentry passed is not currently hashed.
 */
 
अटल अंतरभूत पूर्णांक d_unhashed(स्थिर काष्ठा dentry *dentry)
अणु
	वापस hlist_bl_unhashed(&dentry->d_hash);
पूर्ण

अटल अंतरभूत पूर्णांक d_unlinked(स्थिर काष्ठा dentry *dentry)
अणु
	वापस d_unhashed(dentry) && !IS_ROOT(dentry);
पूर्ण

अटल अंतरभूत पूर्णांक cant_mount(स्थिर काष्ठा dentry *dentry)
अणु
	वापस (dentry->d_flags & DCACHE_CANT_MOUNT);
पूर्ण

अटल अंतरभूत व्योम करोnt_mount(काष्ठा dentry *dentry)
अणु
	spin_lock(&dentry->d_lock);
	dentry->d_flags |= DCACHE_CANT_MOUNT;
	spin_unlock(&dentry->d_lock);
पूर्ण

बाह्य व्योम __d_lookup_करोne(काष्ठा dentry *);

अटल अंतरभूत पूर्णांक d_in_lookup(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_flags & DCACHE_PAR_LOOKUP;
पूर्ण

अटल अंतरभूत व्योम d_lookup_करोne(काष्ठा dentry *dentry)
अणु
	अगर (unlikely(d_in_lookup(dentry))) अणु
		spin_lock(&dentry->d_lock);
		__d_lookup_करोne(dentry);
		spin_unlock(&dentry->d_lock);
	पूर्ण
पूर्ण

बाह्य व्योम dput(काष्ठा dentry *);

अटल अंतरभूत bool d_managed(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_flags & DCACHE_MANAGED_DENTRY;
पूर्ण

अटल अंतरभूत bool d_mountpoपूर्णांक(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_flags & DCACHE_MOUNTED;
पूर्ण

/*
 * Directory cache entry type accessor functions.
 */
अटल अंतरभूत अचिन्हित __d_entry_type(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_flags & DCACHE_ENTRY_TYPE;
पूर्ण

अटल अंतरभूत bool d_is_miss(स्थिर काष्ठा dentry *dentry)
अणु
	वापस __d_entry_type(dentry) == DCACHE_MISS_TYPE;
पूर्ण

अटल अंतरभूत bool d_is_whiteout(स्थिर काष्ठा dentry *dentry)
अणु
	वापस __d_entry_type(dentry) == DCACHE_WHITEOUT_TYPE;
पूर्ण

अटल अंतरभूत bool d_can_lookup(स्थिर काष्ठा dentry *dentry)
अणु
	वापस __d_entry_type(dentry) == DCACHE_सूचीECTORY_TYPE;
पूर्ण

अटल अंतरभूत bool d_is_स्वतःdir(स्थिर काष्ठा dentry *dentry)
अणु
	वापस __d_entry_type(dentry) == DCACHE_AUTOसूची_TYPE;
पूर्ण

अटल अंतरभूत bool d_is_dir(स्थिर काष्ठा dentry *dentry)
अणु
	वापस d_can_lookup(dentry) || d_is_स्वतःdir(dentry);
पूर्ण

अटल अंतरभूत bool d_is_symlink(स्थिर काष्ठा dentry *dentry)
अणु
	वापस __d_entry_type(dentry) == DCACHE_SYMLINK_TYPE;
पूर्ण

अटल अंतरभूत bool d_is_reg(स्थिर काष्ठा dentry *dentry)
अणु
	वापस __d_entry_type(dentry) == DCACHE_REGULAR_TYPE;
पूर्ण

अटल अंतरभूत bool d_is_special(स्थिर काष्ठा dentry *dentry)
अणु
	वापस __d_entry_type(dentry) == DCACHE_SPECIAL_TYPE;
पूर्ण

अटल अंतरभूत bool d_is_file(स्थिर काष्ठा dentry *dentry)
अणु
	वापस d_is_reg(dentry) || d_is_special(dentry);
पूर्ण

अटल अंतरभूत bool d_is_negative(स्थिर काष्ठा dentry *dentry)
अणु
	// TODO: check d_is_whiteout(dentry) also.
	वापस d_is_miss(dentry);
पूर्ण

अटल अंतरभूत bool d_flags_negative(अचिन्हित flags)
अणु
	वापस (flags & DCACHE_ENTRY_TYPE) == DCACHE_MISS_TYPE;
पूर्ण

अटल अंतरभूत bool d_is_positive(स्थिर काष्ठा dentry *dentry)
अणु
	वापस !d_is_negative(dentry);
पूर्ण

/**
 * d_really_is_negative - Determine अगर a dentry is really negative (ignoring fallthroughs)
 * @dentry: The dentry in question
 *
 * Returns true अगर the dentry represents either an असलent name or a name that
 * करोesn't map to an inode (ie. ->d_inode is शून्य).  The dentry could represent
 * a true miss, a whiteout that isn't represented by a 0,0 अक्षरdev or a
 * fallthrough marker in an opaque directory.
 *
 * Note!  (1) This should be used *only* by a fileप्रणाली to examine its own
 * dentries.  It should not be used to look at some other fileप्रणाली's
 * dentries.  (2) It should also be used in combination with d_inode() to get
 * the inode.  (3) The dentry may have something attached to ->d_lower and the
 * type field of the flags may be set to something other than miss or whiteout.
 */
अटल अंतरभूत bool d_really_is_negative(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_inode == शून्य;
पूर्ण

/**
 * d_really_is_positive - Determine अगर a dentry is really positive (ignoring fallthroughs)
 * @dentry: The dentry in question
 *
 * Returns true अगर the dentry represents a name that maps to an inode
 * (ie. ->d_inode is not शून्य).  The dentry might still represent a whiteout अगर
 * that is represented on medium as a 0,0 अक्षरdev.
 *
 * Note!  (1) This should be used *only* by a fileप्रणाली to examine its own
 * dentries.  It should not be used to look at some other fileप्रणाली's
 * dentries.  (2) It should also be used in combination with d_inode() to get
 * the inode.
 */
अटल अंतरभूत bool d_really_is_positive(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_inode != शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक simple_positive(स्थिर काष्ठा dentry *dentry)
अणु
	वापस d_really_is_positive(dentry) && !d_unhashed(dentry);
पूर्ण

बाह्य व्योम d_set_fallthru(काष्ठा dentry *dentry);

अटल अंतरभूत bool d_is_fallthru(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_flags & DCACHE_FALLTHRU;
पूर्ण


बाह्य पूर्णांक sysctl_vfs_cache_pressure;

अटल अंतरभूत अचिन्हित दीर्घ vfs_pressure_ratio(अचिन्हित दीर्घ val)
अणु
	वापस mult_frac(val, sysctl_vfs_cache_pressure, 100);
पूर्ण

/**
 * d_inode - Get the actual inode of this dentry
 * @dentry: The dentry to query
 *
 * This is the helper normal fileप्रणालीs should use to get at their own inodes
 * in their own dentries and ignore the layering superimposed upon them.
 */
अटल अंतरभूत काष्ठा inode *d_inode(स्थिर काष्ठा dentry *dentry)
अणु
	वापस dentry->d_inode;
पूर्ण

/**
 * d_inode_rcu - Get the actual inode of this dentry with READ_ONCE()
 * @dentry: The dentry to query
 *
 * This is the helper normal fileप्रणालीs should use to get at their own inodes
 * in their own dentries and ignore the layering superimposed upon them.
 */
अटल अंतरभूत काष्ठा inode *d_inode_rcu(स्थिर काष्ठा dentry *dentry)
अणु
	वापस READ_ONCE(dentry->d_inode);
पूर्ण

/**
 * d_backing_inode - Get upper or lower inode we should be using
 * @upper: The upper layer
 *
 * This is the helper that should be used to get at the inode that will be used
 * अगर this dentry were to be खोलोed as a file.  The inode may be on the upper
 * dentry or it may be on a lower dentry pinned by the upper.
 *
 * Normal fileप्रणालीs should not use this to access their own inodes.
 */
अटल अंतरभूत काष्ठा inode *d_backing_inode(स्थिर काष्ठा dentry *upper)
अणु
	काष्ठा inode *inode = upper->d_inode;

	वापस inode;
पूर्ण

/**
 * d_backing_dentry - Get upper or lower dentry we should be using
 * @upper: The upper layer
 *
 * This is the helper that should be used to get the dentry of the inode that
 * will be used अगर this dentry were खोलोed as a file.  It may be the upper
 * dentry or it may be a lower dentry pinned by the upper.
 *
 * Normal fileप्रणालीs should not use this to access their own dentries.
 */
अटल अंतरभूत काष्ठा dentry *d_backing_dentry(काष्ठा dentry *upper)
अणु
	वापस upper;
पूर्ण

/**
 * d_real - Return the real dentry
 * @dentry: the dentry to query
 * @inode: inode to select the dentry from multiple layers (can be शून्य)
 *
 * If dentry is on a जोड़/overlay, then वापस the underlying, real dentry.
 * Otherwise वापस the dentry itself.
 *
 * See also: Documentation/fileप्रणालीs/vfs.rst
 */
अटल अंतरभूत काष्ठा dentry *d_real(काष्ठा dentry *dentry,
				    स्थिर काष्ठा inode *inode)
अणु
	अगर (unlikely(dentry->d_flags & DCACHE_OP_REAL))
		वापस dentry->d_op->d_real(dentry, inode);
	अन्यथा
		वापस dentry;
पूर्ण

/**
 * d_real_inode - Return the real inode
 * @dentry: The dentry to query
 *
 * If dentry is on a जोड़/overlay, then वापस the underlying, real inode.
 * Otherwise वापस d_inode().
 */
अटल अंतरभूत काष्ठा inode *d_real_inode(स्थिर काष्ठा dentry *dentry)
अणु
	/* This usage of d_real() results in स्थिर dentry */
	वापस d_backing_inode(d_real((काष्ठा dentry *) dentry, शून्य));
पूर्ण

काष्ठा name_snapshot अणु
	काष्ठा qstr name;
	अचिन्हित अक्षर अंतरभूत_name[DNAME_INLINE_LEN];
पूर्ण;
व्योम take_dentry_name_snapshot(काष्ठा name_snapshot *, काष्ठा dentry *);
व्योम release_dentry_name_snapshot(काष्ठा name_snapshot *);

#पूर्ण_अगर	/* __LINUX_DCACHE_H */
