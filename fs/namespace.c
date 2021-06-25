<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/namespace.c
 *
 * (C) Copyright Al Viro 2000, 2001
 *
 * Based on code from fs/super.c, copyright Linus Torvalds and others.
 * Heavily rewritten.
 */

#समावेश <linux/syscalls.h>
#समावेश <linux/export.h>
#समावेश <linux/capability.h>
#समावेश <linux/mnt_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/namei.h>
#समावेश <linux/security.h>
#समावेश <linux/cred.h>
#समावेश <linux/idr.h>
#समावेश <linux/init.h>		/* init_rootfs */
#समावेश <linux/fs_काष्ठा.h>	/* get_fs_root et.al. */
#समावेश <linux/fsnotअगरy.h>	/* fsnotअगरy_vfsmount_delete */
#समावेश <linux/file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/magic.h>
#समावेश <linux/memblock.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/task_work.h>
#समावेश <linux/sched/task.h>
#समावेश <uapi/linux/mount.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/shmem_fs.h>

#समावेश "pnode.h"
#समावेश "internal.h"

/* Maximum number of mounts in a mount namespace */
अचिन्हित पूर्णांक sysctl_mount_max __पढ़ो_mostly = 100000;

अटल अचिन्हित पूर्णांक m_hash_mask __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक m_hash_shअगरt __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक mp_hash_mask __पढ़ो_mostly;
अटल अचिन्हित पूर्णांक mp_hash_shअगरt __पढ़ो_mostly;

अटल __initdata अचिन्हित दीर्घ mhash_entries;
अटल पूर्णांक __init set_mhash_entries(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;
	mhash_entries = simple_म_से_अदीर्घ(str, &str, 0);
	वापस 1;
पूर्ण
__setup("mhash_entries=", set_mhash_entries);

अटल __initdata अचिन्हित दीर्घ mphash_entries;
अटल पूर्णांक __init set_mphash_entries(अक्षर *str)
अणु
	अगर (!str)
		वापस 0;
	mphash_entries = simple_म_से_अदीर्घ(str, &str, 0);
	वापस 1;
पूर्ण
__setup("mphash_entries=", set_mphash_entries);

अटल u64 event;
अटल DEFINE_IDA(mnt_id_ida);
अटल DEFINE_IDA(mnt_group_ida);

अटल काष्ठा hlist_head *mount_hashtable __पढ़ो_mostly;
अटल काष्ठा hlist_head *mountpoपूर्णांक_hashtable __पढ़ो_mostly;
अटल काष्ठा kmem_cache *mnt_cache __पढ़ो_mostly;
अटल DECLARE_RWSEM(namespace_sem);
अटल HLIST_HEAD(unmounted);	/* रक्षित by namespace_sem */
अटल LIST_HEAD(ex_mountpoपूर्णांकs); /* रक्षित by namespace_sem */

काष्ठा mount_kattr अणु
	अचिन्हित पूर्णांक attr_set;
	अचिन्हित पूर्णांक attr_clr;
	अचिन्हित पूर्णांक propagation;
	अचिन्हित पूर्णांक lookup_flags;
	bool recurse;
	काष्ठा user_namespace *mnt_userns;
पूर्ण;

/* /sys/fs */
काष्ठा kobject *fs_kobj;
EXPORT_SYMBOL_GPL(fs_kobj);

/*
 * vfsmount lock may be taken क्रम पढ़ो to prevent changes to the
 * vfsmount hash, ie. during mountpoपूर्णांक lookups or walking back
 * up the tree.
 *
 * It should be taken क्रम ग_लिखो in all हालs where the vfsmount
 * tree or hash is modअगरied or when a vfsmount काष्ठाure is modअगरied.
 */
__cacheline_aligned_in_smp DEFINE_SEQLOCK(mount_lock);

अटल अंतरभूत व्योम lock_mount_hash(व्योम)
अणु
	ग_लिखो_seqlock(&mount_lock);
पूर्ण

अटल अंतरभूत व्योम unlock_mount_hash(व्योम)
अणु
	ग_लिखो_sequnlock(&mount_lock);
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *m_hash(काष्ठा vfsmount *mnt, काष्ठा dentry *dentry)
अणु
	अचिन्हित दीर्घ पंचांगp = ((अचिन्हित दीर्घ)mnt / L1_CACHE_BYTES);
	पंचांगp += ((अचिन्हित दीर्घ)dentry / L1_CACHE_BYTES);
	पंचांगp = पंचांगp + (पंचांगp >> m_hash_shअगरt);
	वापस &mount_hashtable[पंचांगp & m_hash_mask];
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *mp_hash(काष्ठा dentry *dentry)
अणु
	अचिन्हित दीर्घ पंचांगp = ((अचिन्हित दीर्घ)dentry / L1_CACHE_BYTES);
	पंचांगp = पंचांगp + (पंचांगp >> mp_hash_shअगरt);
	वापस &mountpoपूर्णांक_hashtable[पंचांगp & mp_hash_mask];
पूर्ण

अटल पूर्णांक mnt_alloc_id(काष्ठा mount *mnt)
अणु
	पूर्णांक res = ida_alloc(&mnt_id_ida, GFP_KERNEL);

	अगर (res < 0)
		वापस res;
	mnt->mnt_id = res;
	वापस 0;
पूर्ण

अटल व्योम mnt_मुक्त_id(काष्ठा mount *mnt)
अणु
	ida_मुक्त(&mnt_id_ida, mnt->mnt_id);
पूर्ण

/*
 * Allocate a new peer group ID
 */
अटल पूर्णांक mnt_alloc_group_id(काष्ठा mount *mnt)
अणु
	पूर्णांक res = ida_alloc_min(&mnt_group_ida, 1, GFP_KERNEL);

	अगर (res < 0)
		वापस res;
	mnt->mnt_group_id = res;
	वापस 0;
पूर्ण

/*
 * Release a peer group ID
 */
व्योम mnt_release_group_id(काष्ठा mount *mnt)
अणु
	ida_मुक्त(&mnt_group_ida, mnt->mnt_group_id);
	mnt->mnt_group_id = 0;
पूर्ण

/*
 * vfsmount lock must be held क्रम पढ़ो
 */
अटल अंतरभूत व्योम mnt_add_count(काष्ठा mount *mnt, पूर्णांक n)
अणु
#अगर_घोषित CONFIG_SMP
	this_cpu_add(mnt->mnt_pcp->mnt_count, n);
#अन्यथा
	preempt_disable();
	mnt->mnt_count += n;
	preempt_enable();
#पूर्ण_अगर
पूर्ण

/*
 * vfsmount lock must be held क्रम ग_लिखो
 */
पूर्णांक mnt_get_count(काष्ठा mount *mnt)
अणु
#अगर_घोषित CONFIG_SMP
	पूर्णांक count = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		count += per_cpu_ptr(mnt->mnt_pcp, cpu)->mnt_count;
	पूर्ण

	वापस count;
#अन्यथा
	वापस mnt->mnt_count;
#पूर्ण_अगर
पूर्ण

अटल काष्ठा mount *alloc_vfsmnt(स्थिर अक्षर *name)
अणु
	काष्ठा mount *mnt = kmem_cache_zalloc(mnt_cache, GFP_KERNEL);
	अगर (mnt) अणु
		पूर्णांक err;

		err = mnt_alloc_id(mnt);
		अगर (err)
			जाओ out_मुक्त_cache;

		अगर (name) अणु
			mnt->mnt_devname = kstrdup_स्थिर(name, GFP_KERNEL);
			अगर (!mnt->mnt_devname)
				जाओ out_मुक्त_id;
		पूर्ण

#अगर_घोषित CONFIG_SMP
		mnt->mnt_pcp = alloc_percpu(काष्ठा mnt_pcp);
		अगर (!mnt->mnt_pcp)
			जाओ out_मुक्त_devname;

		this_cpu_add(mnt->mnt_pcp->mnt_count, 1);
#अन्यथा
		mnt->mnt_count = 1;
		mnt->mnt_ग_लिखोrs = 0;
#पूर्ण_अगर

		INIT_HLIST_NODE(&mnt->mnt_hash);
		INIT_LIST_HEAD(&mnt->mnt_child);
		INIT_LIST_HEAD(&mnt->mnt_mounts);
		INIT_LIST_HEAD(&mnt->mnt_list);
		INIT_LIST_HEAD(&mnt->mnt_expire);
		INIT_LIST_HEAD(&mnt->mnt_share);
		INIT_LIST_HEAD(&mnt->mnt_slave_list);
		INIT_LIST_HEAD(&mnt->mnt_slave);
		INIT_HLIST_NODE(&mnt->mnt_mp_list);
		INIT_LIST_HEAD(&mnt->mnt_umounting);
		INIT_HLIST_HEAD(&mnt->mnt_stuck_children);
		mnt->mnt.mnt_userns = &init_user_ns;
	पूर्ण
	वापस mnt;

#अगर_घोषित CONFIG_SMP
out_मुक्त_devname:
	kमुक्त_स्थिर(mnt->mnt_devname);
#पूर्ण_अगर
out_मुक्त_id:
	mnt_मुक्त_id(mnt);
out_मुक्त_cache:
	kmem_cache_मुक्त(mnt_cache, mnt);
	वापस शून्य;
पूर्ण

/*
 * Most r/o checks on a fs are क्रम operations that take
 * discrete amounts of समय, like a ग_लिखो() or unlink().
 * We must keep track of when those operations start
 * (क्रम permission checks) and when they end, so that
 * we can determine when ग_लिखोs are able to occur to
 * a fileप्रणाली.
 */
/*
 * __mnt_is_पढ़ोonly: check whether a mount is पढ़ो-only
 * @mnt: the mount to check क्रम its ग_लिखो status
 *
 * This shouldn't be used directly ouside of the VFS.
 * It करोes not guarantee that the fileप्रणाली will stay
 * r/w, just that it is right *now*.  This can not and
 * should not be used in place of IS_RDONLY(inode).
 * mnt_want/drop_ग_लिखो() will _keep_ the fileप्रणाली
 * r/w.
 */
bool __mnt_is_पढ़ोonly(काष्ठा vfsmount *mnt)
अणु
	वापस (mnt->mnt_flags & MNT_READONLY) || sb_rकरोnly(mnt->mnt_sb);
पूर्ण
EXPORT_SYMBOL_GPL(__mnt_is_पढ़ोonly);

अटल अंतरभूत व्योम mnt_inc_ग_लिखोrs(काष्ठा mount *mnt)
अणु
#अगर_घोषित CONFIG_SMP
	this_cpu_inc(mnt->mnt_pcp->mnt_ग_लिखोrs);
#अन्यथा
	mnt->mnt_ग_लिखोrs++;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम mnt_dec_ग_लिखोrs(काष्ठा mount *mnt)
अणु
#अगर_घोषित CONFIG_SMP
	this_cpu_dec(mnt->mnt_pcp->mnt_ग_लिखोrs);
#अन्यथा
	mnt->mnt_ग_लिखोrs--;
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित पूर्णांक mnt_get_ग_लिखोrs(काष्ठा mount *mnt)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		count += per_cpu_ptr(mnt->mnt_pcp, cpu)->mnt_ग_लिखोrs;
	पूर्ण

	वापस count;
#अन्यथा
	वापस mnt->mnt_ग_लिखोrs;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक mnt_is_पढ़ोonly(काष्ठा vfsmount *mnt)
अणु
	अगर (mnt->mnt_sb->s_पढ़ोonly_remount)
		वापस 1;
	/* Order wrt setting s_flags/s_पढ़ोonly_remount in करो_remount() */
	smp_rmb();
	वापस __mnt_is_पढ़ोonly(mnt);
पूर्ण

/*
 * Most r/o & frozen checks on a fs are क्रम operations that take discrete
 * amounts of समय, like a ग_लिखो() or unlink().  We must keep track of when
 * those operations start (क्रम permission checks) and when they end, so that we
 * can determine when ग_लिखोs are able to occur to a fileप्रणाली.
 */
/**
 * __mnt_want_ग_लिखो - get ग_लिखो access to a mount without मुक्तze protection
 * @m: the mount on which to take a ग_लिखो
 *
 * This tells the low-level fileप्रणाली that a ग_लिखो is about to be perक्रमmed to
 * it, and makes sure that ग_लिखोs are allowed (mnt it पढ़ो-ग_लिखो) beक्रमe
 * वापसing success. This operation करोes not protect against fileप्रणाली being
 * frozen. When the ग_लिखो operation is finished, __mnt_drop_ग_लिखो() must be
 * called. This is effectively a refcount.
 */
पूर्णांक __mnt_want_ग_लिखो(काष्ठा vfsmount *m)
अणु
	काष्ठा mount *mnt = real_mount(m);
	पूर्णांक ret = 0;

	preempt_disable();
	mnt_inc_ग_लिखोrs(mnt);
	/*
	 * The store to mnt_inc_ग_लिखोrs must be visible beक्रमe we pass
	 * MNT_WRITE_HOLD loop below, so that the slowpath can see our
	 * incremented count after it has set MNT_WRITE_HOLD.
	 */
	smp_mb();
	जबतक (READ_ONCE(mnt->mnt.mnt_flags) & MNT_WRITE_HOLD)
		cpu_relax();
	/*
	 * After the slowpath clears MNT_WRITE_HOLD, mnt_is_पढ़ोonly will
	 * be set to match its requirements. So we must not load that until
	 * MNT_WRITE_HOLD is cleared.
	 */
	smp_rmb();
	अगर (mnt_is_पढ़ोonly(m)) अणु
		mnt_dec_ग_लिखोrs(mnt);
		ret = -EROFS;
	पूर्ण
	preempt_enable();

	वापस ret;
पूर्ण

/**
 * mnt_want_ग_लिखो - get ग_लिखो access to a mount
 * @m: the mount on which to take a ग_लिखो
 *
 * This tells the low-level fileप्रणाली that a ग_लिखो is about to be perक्रमmed to
 * it, and makes sure that ग_लिखोs are allowed (mount is पढ़ो-ग_लिखो, fileप्रणाली
 * is not frozen) beक्रमe वापसing success.  When the ग_लिखो operation is
 * finished, mnt_drop_ग_लिखो() must be called.  This is effectively a refcount.
 */
पूर्णांक mnt_want_ग_लिखो(काष्ठा vfsmount *m)
अणु
	पूर्णांक ret;

	sb_start_ग_लिखो(m->mnt_sb);
	ret = __mnt_want_ग_लिखो(m);
	अगर (ret)
		sb_end_ग_लिखो(m->mnt_sb);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mnt_want_ग_लिखो);

/**
 * __mnt_want_ग_लिखो_file - get ग_लिखो access to a file's mount
 * @file: the file who's mount on which to take a ग_लिखो
 *
 * This is like __mnt_want_ग_लिखो, but अगर the file is alपढ़ोy खोलो क्रम writing it
 * skips incrementing mnt_ग_लिखोrs (since the खोलो file alपढ़ोy has a reference)
 * and instead only करोes the check क्रम emergency r/o remounts.  This must be
 * paired with __mnt_drop_ग_लिखो_file.
 */
पूर्णांक __mnt_want_ग_लिखो_file(काष्ठा file *file)
अणु
	अगर (file->f_mode & FMODE_WRITER) अणु
		/*
		 * Superblock may have become पढ़ोonly जबतक there are still
		 * writable fd's, e.g. due to a fs error with errors=remount-ro
		 */
		अगर (__mnt_is_पढ़ोonly(file->f_path.mnt))
			वापस -EROFS;
		वापस 0;
	पूर्ण
	वापस __mnt_want_ग_लिखो(file->f_path.mnt);
पूर्ण

/**
 * mnt_want_ग_लिखो_file - get ग_लिखो access to a file's mount
 * @file: the file who's mount on which to take a ग_लिखो
 *
 * This is like mnt_want_ग_लिखो, but अगर the file is alपढ़ोy खोलो क्रम writing it
 * skips incrementing mnt_ग_लिखोrs (since the खोलो file alपढ़ोy has a reference)
 * and instead only करोes the मुक्तze protection and the check क्रम emergency r/o
 * remounts.  This must be paired with mnt_drop_ग_लिखो_file.
 */
पूर्णांक mnt_want_ग_लिखो_file(काष्ठा file *file)
अणु
	पूर्णांक ret;

	sb_start_ग_लिखो(file_inode(file)->i_sb);
	ret = __mnt_want_ग_लिखो_file(file);
	अगर (ret)
		sb_end_ग_लिखो(file_inode(file)->i_sb);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mnt_want_ग_लिखो_file);

/**
 * __mnt_drop_ग_लिखो - give up ग_लिखो access to a mount
 * @mnt: the mount on which to give up ग_लिखो access
 *
 * Tells the low-level fileप्रणाली that we are करोne
 * perक्रमming ग_लिखोs to it.  Must be matched with
 * __mnt_want_ग_लिखो() call above.
 */
व्योम __mnt_drop_ग_लिखो(काष्ठा vfsmount *mnt)
अणु
	preempt_disable();
	mnt_dec_ग_लिखोrs(real_mount(mnt));
	preempt_enable();
पूर्ण

/**
 * mnt_drop_ग_लिखो - give up ग_लिखो access to a mount
 * @mnt: the mount on which to give up ग_लिखो access
 *
 * Tells the low-level fileप्रणाली that we are करोne perक्रमming ग_लिखोs to it and
 * also allows fileप्रणाली to be frozen again.  Must be matched with
 * mnt_want_ग_लिखो() call above.
 */
व्योम mnt_drop_ग_लिखो(काष्ठा vfsmount *mnt)
अणु
	__mnt_drop_ग_लिखो(mnt);
	sb_end_ग_लिखो(mnt->mnt_sb);
पूर्ण
EXPORT_SYMBOL_GPL(mnt_drop_ग_लिखो);

व्योम __mnt_drop_ग_लिखो_file(काष्ठा file *file)
अणु
	अगर (!(file->f_mode & FMODE_WRITER))
		__mnt_drop_ग_लिखो(file->f_path.mnt);
पूर्ण

व्योम mnt_drop_ग_लिखो_file(काष्ठा file *file)
अणु
	__mnt_drop_ग_लिखो_file(file);
	sb_end_ग_लिखो(file_inode(file)->i_sb);
पूर्ण
EXPORT_SYMBOL(mnt_drop_ग_लिखो_file);

अटल अंतरभूत पूर्णांक mnt_hold_ग_लिखोrs(काष्ठा mount *mnt)
अणु
	mnt->mnt.mnt_flags |= MNT_WRITE_HOLD;
	/*
	 * After storing MNT_WRITE_HOLD, we'll पढ़ो the counters. This store
	 * should be visible beक्रमe we करो.
	 */
	smp_mb();

	/*
	 * With ग_लिखोrs on hold, अगर this value is zero, then there are
	 * definitely no active ग_लिखोrs (although held ग_लिखोrs may subsequently
	 * increment the count, they'll have to रुको, and decrement it after
	 * seeing MNT_READONLY).
	 *
	 * It is OK to have counter incremented on one CPU and decremented on
	 * another: the sum will add up correctly. The danger would be when we
	 * sum up each counter, अगर we पढ़ो a counter beक्रमe it is incremented,
	 * but then पढ़ो another CPU's count which it has been subsequently
	 * decremented from -- we would see more decrements than we should.
	 * MNT_WRITE_HOLD protects against this scenario, because
	 * mnt_want_ग_लिखो first increments count, then smp_mb, then spins on
	 * MNT_WRITE_HOLD, so it can't be decremented by another CPU जबतक
	 * we're counting up here.
	 */
	अगर (mnt_get_ग_लिखोrs(mnt) > 0)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम mnt_unhold_ग_लिखोrs(काष्ठा mount *mnt)
अणु
	/*
	 * MNT_READONLY must become visible beक्रमe ~MNT_WRITE_HOLD, so ग_लिखोrs
	 * that become unheld will see MNT_READONLY.
	 */
	smp_wmb();
	mnt->mnt.mnt_flags &= ~MNT_WRITE_HOLD;
पूर्ण

अटल पूर्णांक mnt_make_पढ़ोonly(काष्ठा mount *mnt)
अणु
	पूर्णांक ret;

	ret = mnt_hold_ग_लिखोrs(mnt);
	अगर (!ret)
		mnt->mnt.mnt_flags |= MNT_READONLY;
	mnt_unhold_ग_लिखोrs(mnt);
	वापस ret;
पूर्ण

पूर्णांक sb_prepare_remount_पढ़ोonly(काष्ठा super_block *sb)
अणु
	काष्ठा mount *mnt;
	पूर्णांक err = 0;

	/* Racy optimization.  Recheck the counter under MNT_WRITE_HOLD */
	अगर (atomic_दीर्घ_पढ़ो(&sb->s_हटाओ_count))
		वापस -EBUSY;

	lock_mount_hash();
	list_क्रम_each_entry(mnt, &sb->s_mounts, mnt_instance) अणु
		अगर (!(mnt->mnt.mnt_flags & MNT_READONLY)) अणु
			mnt->mnt.mnt_flags |= MNT_WRITE_HOLD;
			smp_mb();
			अगर (mnt_get_ग_लिखोrs(mnt) > 0) अणु
				err = -EBUSY;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!err && atomic_दीर्घ_पढ़ो(&sb->s_हटाओ_count))
		err = -EBUSY;

	अगर (!err) अणु
		sb->s_पढ़ोonly_remount = 1;
		smp_wmb();
	पूर्ण
	list_क्रम_each_entry(mnt, &sb->s_mounts, mnt_instance) अणु
		अगर (mnt->mnt.mnt_flags & MNT_WRITE_HOLD)
			mnt->mnt.mnt_flags &= ~MNT_WRITE_HOLD;
	पूर्ण
	unlock_mount_hash();

	वापस err;
पूर्ण

अटल व्योम मुक्त_vfsmnt(काष्ठा mount *mnt)
अणु
	काष्ठा user_namespace *mnt_userns;

	mnt_userns = mnt_user_ns(&mnt->mnt);
	अगर (mnt_userns != &init_user_ns)
		put_user_ns(mnt_userns);
	kमुक्त_स्थिर(mnt->mnt_devname);
#अगर_घोषित CONFIG_SMP
	मुक्त_percpu(mnt->mnt_pcp);
#पूर्ण_अगर
	kmem_cache_मुक्त(mnt_cache, mnt);
पूर्ण

अटल व्योम delayed_मुक्त_vfsmnt(काष्ठा rcu_head *head)
अणु
	मुक्त_vfsmnt(container_of(head, काष्ठा mount, mnt_rcu));
पूर्ण

/* call under rcu_पढ़ो_lock */
पूर्णांक __legitimize_mnt(काष्ठा vfsmount *bastard, अचिन्हित seq)
अणु
	काष्ठा mount *mnt;
	अगर (पढ़ो_seqretry(&mount_lock, seq))
		वापस 1;
	अगर (bastard == शून्य)
		वापस 0;
	mnt = real_mount(bastard);
	mnt_add_count(mnt, 1);
	smp_mb();			// see mntput_no_expire()
	अगर (likely(!पढ़ो_seqretry(&mount_lock, seq)))
		वापस 0;
	अगर (bastard->mnt_flags & MNT_SYNC_UMOUNT) अणु
		mnt_add_count(mnt, -1);
		वापस 1;
	पूर्ण
	lock_mount_hash();
	अगर (unlikely(bastard->mnt_flags & MNT_DOOMED)) अणु
		mnt_add_count(mnt, -1);
		unlock_mount_hash();
		वापस 1;
	पूर्ण
	unlock_mount_hash();
	/* caller will mntput() */
	वापस -1;
पूर्ण

/* call under rcu_पढ़ो_lock */
bool legitimize_mnt(काष्ठा vfsmount *bastard, अचिन्हित seq)
अणु
	पूर्णांक res = __legitimize_mnt(bastard, seq);
	अगर (likely(!res))
		वापस true;
	अगर (unlikely(res < 0)) अणु
		rcu_पढ़ो_unlock();
		mntput(bastard);
		rcu_पढ़ो_lock();
	पूर्ण
	वापस false;
पूर्ण

/*
 * find the first mount at @dentry on vfsmount @mnt.
 * call under rcu_पढ़ो_lock()
 */
काष्ठा mount *__lookup_mnt(काष्ठा vfsmount *mnt, काष्ठा dentry *dentry)
अणु
	काष्ठा hlist_head *head = m_hash(mnt, dentry);
	काष्ठा mount *p;

	hlist_क्रम_each_entry_rcu(p, head, mnt_hash)
		अगर (&p->mnt_parent->mnt == mnt && p->mnt_mountpoपूर्णांक == dentry)
			वापस p;
	वापस शून्य;
पूर्ण

/*
 * lookup_mnt - Return the first child mount mounted at path
 *
 * "First" means first mounted chronologically.  If you create the
 * following mounts:
 *
 * mount /dev/sda1 /mnt
 * mount /dev/sda2 /mnt
 * mount /dev/sda3 /mnt
 *
 * Then lookup_mnt() on the base /mnt dentry in the root mount will
 * वापस successively the root dentry and vfsmount of /dev/sda1, then
 * /dev/sda2, then /dev/sda3, then शून्य.
 *
 * lookup_mnt takes a reference to the found vfsmount.
 */
काष्ठा vfsmount *lookup_mnt(स्थिर काष्ठा path *path)
अणु
	काष्ठा mount *child_mnt;
	काष्ठा vfsmount *m;
	अचिन्हित seq;

	rcu_पढ़ो_lock();
	करो अणु
		seq = पढ़ो_seqbegin(&mount_lock);
		child_mnt = __lookup_mnt(path->mnt, path->dentry);
		m = child_mnt ? &child_mnt->mnt : शून्य;
	पूर्ण जबतक (!legitimize_mnt(m, seq));
	rcu_पढ़ो_unlock();
	वापस m;
पूर्ण

अटल अंतरभूत व्योम lock_ns_list(काष्ठा mnt_namespace *ns)
अणु
	spin_lock(&ns->ns_lock);
पूर्ण

अटल अंतरभूत व्योम unlock_ns_list(काष्ठा mnt_namespace *ns)
अणु
	spin_unlock(&ns->ns_lock);
पूर्ण

अटल अंतरभूत bool mnt_is_cursor(काष्ठा mount *mnt)
अणु
	वापस mnt->mnt.mnt_flags & MNT_CURSOR;
पूर्ण

/*
 * __is_local_mountpoपूर्णांक - Test to see अगर dentry is a mountpoपूर्णांक in the
 *                         current mount namespace.
 *
 * The common हाल is dentries are not mountpoपूर्णांकs at all and that
 * test is handled अंतरभूत.  For the slow हाल when we are actually
 * dealing with a mountpoपूर्णांक of some kind, walk through all of the
 * mounts in the current mount namespace and test to see अगर the dentry
 * is a mountpoपूर्णांक.
 *
 * The mount_hashtable is not usable in the context because we
 * need to identअगरy all mounts that may be in the current mount
 * namespace not just a mount that happens to have some specअगरied
 * parent mount.
 */
bool __is_local_mountpoपूर्णांक(काष्ठा dentry *dentry)
अणु
	काष्ठा mnt_namespace *ns = current->nsproxy->mnt_ns;
	काष्ठा mount *mnt;
	bool is_covered = false;

	करोwn_पढ़ो(&namespace_sem);
	lock_ns_list(ns);
	list_क्रम_each_entry(mnt, &ns->list, mnt_list) अणु
		अगर (mnt_is_cursor(mnt))
			जारी;
		is_covered = (mnt->mnt_mountpoपूर्णांक == dentry);
		अगर (is_covered)
			अवरोध;
	पूर्ण
	unlock_ns_list(ns);
	up_पढ़ो(&namespace_sem);

	वापस is_covered;
पूर्ण

अटल काष्ठा mountpoपूर्णांक *lookup_mountpoपूर्णांक(काष्ठा dentry *dentry)
अणु
	काष्ठा hlist_head *chain = mp_hash(dentry);
	काष्ठा mountpoपूर्णांक *mp;

	hlist_क्रम_each_entry(mp, chain, m_hash) अणु
		अगर (mp->m_dentry == dentry) अणु
			mp->m_count++;
			वापस mp;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mountpoपूर्णांक *get_mountpoपूर्णांक(काष्ठा dentry *dentry)
अणु
	काष्ठा mountpoपूर्णांक *mp, *new = शून्य;
	पूर्णांक ret;

	अगर (d_mountpoपूर्णांक(dentry)) अणु
		/* might be worth a WARN_ON() */
		अगर (d_unlinked(dentry))
			वापस ERR_PTR(-ENOENT);
mountpoपूर्णांक:
		पढ़ो_seqlock_excl(&mount_lock);
		mp = lookup_mountpoपूर्णांक(dentry);
		पढ़ो_sequnlock_excl(&mount_lock);
		अगर (mp)
			जाओ करोne;
	पूर्ण

	अगर (!new)
		new = kदो_स्मृति(माप(काष्ठा mountpoपूर्णांक), GFP_KERNEL);
	अगर (!new)
		वापस ERR_PTR(-ENOMEM);


	/* Exactly one processes may set d_mounted */
	ret = d_set_mounted(dentry);

	/* Someone अन्यथा set d_mounted? */
	अगर (ret == -EBUSY)
		जाओ mountpoपूर्णांक;

	/* The dentry is not available as a mountpoपूर्णांक? */
	mp = ERR_PTR(ret);
	अगर (ret)
		जाओ करोne;

	/* Add the new mountpoपूर्णांक to the hash table */
	पढ़ो_seqlock_excl(&mount_lock);
	new->m_dentry = dget(dentry);
	new->m_count = 1;
	hlist_add_head(&new->m_hash, mp_hash(dentry));
	INIT_HLIST_HEAD(&new->m_list);
	पढ़ो_sequnlock_excl(&mount_lock);

	mp = new;
	new = शून्य;
करोne:
	kमुक्त(new);
	वापस mp;
पूर्ण

/*
 * vfsmount lock must be held.  Additionally, the caller is responsible
 * क्रम serializing calls क्रम given disposal list.
 */
अटल व्योम __put_mountpoपूर्णांक(काष्ठा mountpoपूर्णांक *mp, काष्ठा list_head *list)
अणु
	अगर (!--mp->m_count) अणु
		काष्ठा dentry *dentry = mp->m_dentry;
		BUG_ON(!hlist_empty(&mp->m_list));
		spin_lock(&dentry->d_lock);
		dentry->d_flags &= ~DCACHE_MOUNTED;
		spin_unlock(&dentry->d_lock);
		dput_to_list(dentry, list);
		hlist_del(&mp->m_hash);
		kमुक्त(mp);
	पूर्ण
पूर्ण

/* called with namespace_lock and vfsmount lock */
अटल व्योम put_mountpoपूर्णांक(काष्ठा mountpoपूर्णांक *mp)
अणु
	__put_mountpoपूर्णांक(mp, &ex_mountpoपूर्णांकs);
पूर्ण

अटल अंतरभूत पूर्णांक check_mnt(काष्ठा mount *mnt)
अणु
	वापस mnt->mnt_ns == current->nsproxy->mnt_ns;
पूर्ण

/*
 * vfsmount lock must be held क्रम ग_लिखो
 */
अटल व्योम touch_mnt_namespace(काष्ठा mnt_namespace *ns)
अणु
	अगर (ns) अणु
		ns->event = ++event;
		wake_up_पूर्णांकerruptible(&ns->poll);
	पूर्ण
पूर्ण

/*
 * vfsmount lock must be held क्रम ग_लिखो
 */
अटल व्योम __touch_mnt_namespace(काष्ठा mnt_namespace *ns)
अणु
	अगर (ns && ns->event != event) अणु
		ns->event = event;
		wake_up_पूर्णांकerruptible(&ns->poll);
	पूर्ण
पूर्ण

/*
 * vfsmount lock must be held क्रम ग_लिखो
 */
अटल काष्ठा mountpoपूर्णांक *unhash_mnt(काष्ठा mount *mnt)
अणु
	काष्ठा mountpoपूर्णांक *mp;
	mnt->mnt_parent = mnt;
	mnt->mnt_mountpoपूर्णांक = mnt->mnt.mnt_root;
	list_del_init(&mnt->mnt_child);
	hlist_del_init_rcu(&mnt->mnt_hash);
	hlist_del_init(&mnt->mnt_mp_list);
	mp = mnt->mnt_mp;
	mnt->mnt_mp = शून्य;
	वापस mp;
पूर्ण

/*
 * vfsmount lock must be held क्रम ग_लिखो
 */
अटल व्योम umount_mnt(काष्ठा mount *mnt)
अणु
	put_mountpoपूर्णांक(unhash_mnt(mnt));
पूर्ण

/*
 * vfsmount lock must be held क्रम ग_लिखो
 */
व्योम mnt_set_mountpoपूर्णांक(काष्ठा mount *mnt,
			काष्ठा mountpoपूर्णांक *mp,
			काष्ठा mount *child_mnt)
अणु
	mp->m_count++;
	mnt_add_count(mnt, 1);	/* essentially, that's mntget */
	child_mnt->mnt_mountpoपूर्णांक = mp->m_dentry;
	child_mnt->mnt_parent = mnt;
	child_mnt->mnt_mp = mp;
	hlist_add_head(&child_mnt->mnt_mp_list, &mp->m_list);
पूर्ण

अटल व्योम __attach_mnt(काष्ठा mount *mnt, काष्ठा mount *parent)
अणु
	hlist_add_head_rcu(&mnt->mnt_hash,
			   m_hash(&parent->mnt, mnt->mnt_mountpoपूर्णांक));
	list_add_tail(&mnt->mnt_child, &parent->mnt_mounts);
पूर्ण

/*
 * vfsmount lock must be held क्रम ग_लिखो
 */
अटल व्योम attach_mnt(काष्ठा mount *mnt,
			काष्ठा mount *parent,
			काष्ठा mountpoपूर्णांक *mp)
अणु
	mnt_set_mountpoपूर्णांक(parent, mp, mnt);
	__attach_mnt(mnt, parent);
पूर्ण

व्योम mnt_change_mountpoपूर्णांक(काष्ठा mount *parent, काष्ठा mountpoपूर्णांक *mp, काष्ठा mount *mnt)
अणु
	काष्ठा mountpoपूर्णांक *old_mp = mnt->mnt_mp;
	काष्ठा mount *old_parent = mnt->mnt_parent;

	list_del_init(&mnt->mnt_child);
	hlist_del_init(&mnt->mnt_mp_list);
	hlist_del_init_rcu(&mnt->mnt_hash);

	attach_mnt(mnt, parent, mp);

	put_mountpoपूर्णांक(old_mp);
	mnt_add_count(old_parent, -1);
पूर्ण

/*
 * vfsmount lock must be held क्रम ग_लिखो
 */
अटल व्योम commit_tree(काष्ठा mount *mnt)
अणु
	काष्ठा mount *parent = mnt->mnt_parent;
	काष्ठा mount *m;
	LIST_HEAD(head);
	काष्ठा mnt_namespace *n = parent->mnt_ns;

	BUG_ON(parent == mnt);

	list_add_tail(&head, &mnt->mnt_list);
	list_क्रम_each_entry(m, &head, mnt_list)
		m->mnt_ns = n;

	list_splice(&head, n->list.prev);

	n->mounts += n->pending_mounts;
	n->pending_mounts = 0;

	__attach_mnt(mnt, parent);
	touch_mnt_namespace(n);
पूर्ण

अटल काष्ठा mount *next_mnt(काष्ठा mount *p, काष्ठा mount *root)
अणु
	काष्ठा list_head *next = p->mnt_mounts.next;
	अगर (next == &p->mnt_mounts) अणु
		जबतक (1) अणु
			अगर (p == root)
				वापस शून्य;
			next = p->mnt_child.next;
			अगर (next != &p->mnt_parent->mnt_mounts)
				अवरोध;
			p = p->mnt_parent;
		पूर्ण
	पूर्ण
	वापस list_entry(next, काष्ठा mount, mnt_child);
पूर्ण

अटल काष्ठा mount *skip_mnt_tree(काष्ठा mount *p)
अणु
	काष्ठा list_head *prev = p->mnt_mounts.prev;
	जबतक (prev != &p->mnt_mounts) अणु
		p = list_entry(prev, काष्ठा mount, mnt_child);
		prev = p->mnt_mounts.prev;
	पूर्ण
	वापस p;
पूर्ण

/**
 * vfs_create_mount - Create a mount क्रम a configured superblock
 * @fc: The configuration context with the superblock attached
 *
 * Create a mount to an alपढ़ोy configured superblock.  If necessary, the
 * caller should invoke vfs_get_tree() beक्रमe calling this.
 *
 * Note that this करोes not attach the mount to anything.
 */
काष्ठा vfsmount *vfs_create_mount(काष्ठा fs_context *fc)
अणु
	काष्ठा mount *mnt;

	अगर (!fc->root)
		वापस ERR_PTR(-EINVAL);

	mnt = alloc_vfsmnt(fc->source ?: "none");
	अगर (!mnt)
		वापस ERR_PTR(-ENOMEM);

	अगर (fc->sb_flags & SB_KERNMOUNT)
		mnt->mnt.mnt_flags = MNT_INTERNAL;

	atomic_inc(&fc->root->d_sb->s_active);
	mnt->mnt.mnt_sb		= fc->root->d_sb;
	mnt->mnt.mnt_root	= dget(fc->root);
	mnt->mnt_mountpoपूर्णांक	= mnt->mnt.mnt_root;
	mnt->mnt_parent		= mnt;

	lock_mount_hash();
	list_add_tail(&mnt->mnt_instance, &mnt->mnt.mnt_sb->s_mounts);
	unlock_mount_hash();
	वापस &mnt->mnt;
पूर्ण
EXPORT_SYMBOL(vfs_create_mount);

काष्ठा vfsmount *fc_mount(काष्ठा fs_context *fc)
अणु
	पूर्णांक err = vfs_get_tree(fc);
	अगर (!err) अणु
		up_ग_लिखो(&fc->root->d_sb->s_umount);
		वापस vfs_create_mount(fc);
	पूर्ण
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(fc_mount);

काष्ठा vfsmount *vfs_kern_mount(काष्ठा file_प्रणाली_type *type,
				पूर्णांक flags, स्थिर अक्षर *name,
				व्योम *data)
अणु
	काष्ठा fs_context *fc;
	काष्ठा vfsmount *mnt;
	पूर्णांक ret = 0;

	अगर (!type)
		वापस ERR_PTR(-EINVAL);

	fc = fs_context_क्रम_mount(type, flags);
	अगर (IS_ERR(fc))
		वापस ERR_CAST(fc);

	अगर (name)
		ret = vfs_parse_fs_string(fc, "source",
					  name, म_माप(name));
	अगर (!ret)
		ret = parse_monolithic_mount_data(fc, data);
	अगर (!ret)
		mnt = fc_mount(fc);
	अन्यथा
		mnt = ERR_PTR(ret);

	put_fs_context(fc);
	वापस mnt;
पूर्ण
EXPORT_SYMBOL_GPL(vfs_kern_mount);

काष्ठा vfsmount *
vfs_submount(स्थिर काष्ठा dentry *mountpoपूर्णांक, काष्ठा file_प्रणाली_type *type,
	     स्थिर अक्षर *name, व्योम *data)
अणु
	/* Until it is worked out how to pass the user namespace
	 * through from the parent mount to the submount करोn't support
	 * unprivileged mounts with submounts.
	 */
	अगर (mountpoपूर्णांक->d_sb->s_user_ns != &init_user_ns)
		वापस ERR_PTR(-EPERM);

	वापस vfs_kern_mount(type, SB_SUBMOUNT, name, data);
पूर्ण
EXPORT_SYMBOL_GPL(vfs_submount);

अटल काष्ठा mount *clone_mnt(काष्ठा mount *old, काष्ठा dentry *root,
					पूर्णांक flag)
अणु
	काष्ठा super_block *sb = old->mnt.mnt_sb;
	काष्ठा mount *mnt;
	पूर्णांक err;

	mnt = alloc_vfsmnt(old->mnt_devname);
	अगर (!mnt)
		वापस ERR_PTR(-ENOMEM);

	अगर (flag & (CL_SLAVE | CL_PRIVATE | CL_SHARED_TO_SLAVE))
		mnt->mnt_group_id = 0; /* not a peer of original */
	अन्यथा
		mnt->mnt_group_id = old->mnt_group_id;

	अगर ((flag & CL_MAKE_SHARED) && !mnt->mnt_group_id) अणु
		err = mnt_alloc_group_id(mnt);
		अगर (err)
			जाओ out_मुक्त;
	पूर्ण

	mnt->mnt.mnt_flags = old->mnt.mnt_flags;
	mnt->mnt.mnt_flags &= ~(MNT_WRITE_HOLD|MNT_MARKED|MNT_INTERNAL);

	atomic_inc(&sb->s_active);
	mnt->mnt.mnt_userns = mnt_user_ns(&old->mnt);
	अगर (mnt->mnt.mnt_userns != &init_user_ns)
		mnt->mnt.mnt_userns = get_user_ns(mnt->mnt.mnt_userns);
	mnt->mnt.mnt_sb = sb;
	mnt->mnt.mnt_root = dget(root);
	mnt->mnt_mountpoपूर्णांक = mnt->mnt.mnt_root;
	mnt->mnt_parent = mnt;
	lock_mount_hash();
	list_add_tail(&mnt->mnt_instance, &sb->s_mounts);
	unlock_mount_hash();

	अगर ((flag & CL_SLAVE) ||
	    ((flag & CL_SHARED_TO_SLAVE) && IS_MNT_SHARED(old))) अणु
		list_add(&mnt->mnt_slave, &old->mnt_slave_list);
		mnt->mnt_master = old;
		CLEAR_MNT_SHARED(mnt);
	पूर्ण अन्यथा अगर (!(flag & CL_PRIVATE)) अणु
		अगर ((flag & CL_MAKE_SHARED) || IS_MNT_SHARED(old))
			list_add(&mnt->mnt_share, &old->mnt_share);
		अगर (IS_MNT_SLAVE(old))
			list_add(&mnt->mnt_slave, &old->mnt_slave);
		mnt->mnt_master = old->mnt_master;
	पूर्ण अन्यथा अणु
		CLEAR_MNT_SHARED(mnt);
	पूर्ण
	अगर (flag & CL_MAKE_SHARED)
		set_mnt_shared(mnt);

	/* stick the duplicate mount on the same expiry list
	 * as the original अगर that was on one */
	अगर (flag & CL_EXPIRE) अणु
		अगर (!list_empty(&old->mnt_expire))
			list_add(&mnt->mnt_expire, &old->mnt_expire);
	पूर्ण

	वापस mnt;

 out_मुक्त:
	mnt_मुक्त_id(mnt);
	मुक्त_vfsmnt(mnt);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम cleanup_mnt(काष्ठा mount *mnt)
अणु
	काष्ठा hlist_node *p;
	काष्ठा mount *m;
	/*
	 * The warning here probably indicates that somebody messed
	 * up a mnt_want/drop_ग_लिखो() pair.  If this happens, the
	 * fileप्रणाली was probably unable to make r/w->r/o transitions.
	 * The locking used to deal with mnt_count decrement provides barriers,
	 * so mnt_get_ग_लिखोrs() below is safe.
	 */
	WARN_ON(mnt_get_ग_लिखोrs(mnt));
	अगर (unlikely(mnt->mnt_pins.first))
		mnt_pin_समाप्त(mnt);
	hlist_क्रम_each_entry_safe(m, p, &mnt->mnt_stuck_children, mnt_umount) अणु
		hlist_del(&m->mnt_umount);
		mntput(&m->mnt);
	पूर्ण
	fsnotअगरy_vfsmount_delete(&mnt->mnt);
	dput(mnt->mnt.mnt_root);
	deactivate_super(mnt->mnt.mnt_sb);
	mnt_मुक्त_id(mnt);
	call_rcu(&mnt->mnt_rcu, delayed_मुक्त_vfsmnt);
पूर्ण

अटल व्योम __cleanup_mnt(काष्ठा rcu_head *head)
अणु
	cleanup_mnt(container_of(head, काष्ठा mount, mnt_rcu));
पूर्ण

अटल LLIST_HEAD(delayed_mntput_list);
अटल व्योम delayed_mntput(काष्ठा work_काष्ठा *unused)
अणु
	काष्ठा llist_node *node = llist_del_all(&delayed_mntput_list);
	काष्ठा mount *m, *t;

	llist_क्रम_each_entry_safe(m, t, node, mnt_llist)
		cleanup_mnt(m);
पूर्ण
अटल DECLARE_DELAYED_WORK(delayed_mntput_work, delayed_mntput);

अटल व्योम mntput_no_expire(काष्ठा mount *mnt)
अणु
	LIST_HEAD(list);
	पूर्णांक count;

	rcu_पढ़ो_lock();
	अगर (likely(READ_ONCE(mnt->mnt_ns))) अणु
		/*
		 * Since we करोn't करो lock_mount_hash() here,
		 * ->mnt_ns can change under us.  However, अगर it's
		 * non-शून्य, then there's a reference that won't
		 * be dropped until after an RCU delay करोne after
		 * turning ->mnt_ns शून्य.  So अगर we observe it
		 * non-शून्य under rcu_पढ़ो_lock(), the reference
		 * we are dropping is not the final one.
		 */
		mnt_add_count(mnt, -1);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	lock_mount_hash();
	/*
	 * make sure that अगर __legitimize_mnt() has not seen us grab
	 * mount_lock, we'll see their refcount increment here.
	 */
	smp_mb();
	mnt_add_count(mnt, -1);
	count = mnt_get_count(mnt);
	अगर (count != 0) अणु
		WARN_ON(count < 0);
		rcu_पढ़ो_unlock();
		unlock_mount_hash();
		वापस;
	पूर्ण
	अगर (unlikely(mnt->mnt.mnt_flags & MNT_DOOMED)) अणु
		rcu_पढ़ो_unlock();
		unlock_mount_hash();
		वापस;
	पूर्ण
	mnt->mnt.mnt_flags |= MNT_DOOMED;
	rcu_पढ़ो_unlock();

	list_del(&mnt->mnt_instance);

	अगर (unlikely(!list_empty(&mnt->mnt_mounts))) अणु
		काष्ठा mount *p, *पंचांगp;
		list_क्रम_each_entry_safe(p, पंचांगp, &mnt->mnt_mounts,  mnt_child) अणु
			__put_mountpoपूर्णांक(unhash_mnt(p), &list);
			hlist_add_head(&p->mnt_umount, &mnt->mnt_stuck_children);
		पूर्ण
	पूर्ण
	unlock_mount_hash();
	shrink_dentry_list(&list);

	अगर (likely(!(mnt->mnt.mnt_flags & MNT_INTERNAL))) अणु
		काष्ठा task_काष्ठा *task = current;
		अगर (likely(!(task->flags & PF_KTHREAD))) अणु
			init_task_work(&mnt->mnt_rcu, __cleanup_mnt);
			अगर (!task_work_add(task, &mnt->mnt_rcu, TWA_RESUME))
				वापस;
		पूर्ण
		अगर (llist_add(&mnt->mnt_llist, &delayed_mntput_list))
			schedule_delayed_work(&delayed_mntput_work, 1);
		वापस;
	पूर्ण
	cleanup_mnt(mnt);
पूर्ण

व्योम mntput(काष्ठा vfsmount *mnt)
अणु
	अगर (mnt) अणु
		काष्ठा mount *m = real_mount(mnt);
		/* aव्योम cacheline pingpong, hope gcc करोesn't get "smart" */
		अगर (unlikely(m->mnt_expiry_mark))
			m->mnt_expiry_mark = 0;
		mntput_no_expire(m);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mntput);

काष्ठा vfsmount *mntget(काष्ठा vfsmount *mnt)
अणु
	अगर (mnt)
		mnt_add_count(real_mount(mnt), 1);
	वापस mnt;
पूर्ण
EXPORT_SYMBOL(mntget);

/**
 * path_is_mountpoपूर्णांक() - Check अगर path is a mount in the current namespace.
 * @path: path to check
 *
 *  d_mountpoपूर्णांक() can only be used reliably to establish अगर a dentry is
 *  not mounted in any namespace and that common हाल is handled अंतरभूत.
 *  d_mountpoपूर्णांक() isn't aware of the possibility there may be multiple
 *  mounts using a given dentry in a dअगरferent namespace. This function
 *  checks अगर the passed in path is a mountpoपूर्णांक rather than the dentry
 *  alone.
 */
bool path_is_mountpoपूर्णांक(स्थिर काष्ठा path *path)
अणु
	अचिन्हित seq;
	bool res;

	अगर (!d_mountpoपूर्णांक(path->dentry))
		वापस false;

	rcu_पढ़ो_lock();
	करो अणु
		seq = पढ़ो_seqbegin(&mount_lock);
		res = __path_is_mountpoपूर्णांक(path);
	पूर्ण जबतक (पढ़ो_seqretry(&mount_lock, seq));
	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण
EXPORT_SYMBOL(path_is_mountpoपूर्णांक);

काष्ठा vfsmount *mnt_clone_पूर्णांकernal(स्थिर काष्ठा path *path)
अणु
	काष्ठा mount *p;
	p = clone_mnt(real_mount(path->mnt), path->dentry, CL_PRIVATE);
	अगर (IS_ERR(p))
		वापस ERR_CAST(p);
	p->mnt.mnt_flags |= MNT_INTERNAL;
	वापस &p->mnt;
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल काष्ठा mount *mnt_list_next(काष्ठा mnt_namespace *ns,
				   काष्ठा list_head *p)
अणु
	काष्ठा mount *mnt, *ret = शून्य;

	lock_ns_list(ns);
	list_क्रम_each_जारी(p, &ns->list) अणु
		mnt = list_entry(p, typeof(*mnt), mnt_list);
		अगर (!mnt_is_cursor(mnt)) अणु
			ret = mnt;
			अवरोध;
		पूर्ण
	पूर्ण
	unlock_ns_list(ns);

	वापस ret;
पूर्ण

/* iterator; we want it to have access to namespace_sem, thus here... */
अटल व्योम *m_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा proc_mounts *p = m->निजी;
	काष्ठा list_head *prev;

	करोwn_पढ़ो(&namespace_sem);
	अगर (!*pos) अणु
		prev = &p->ns->list;
	पूर्ण अन्यथा अणु
		prev = &p->cursor.mnt_list;

		/* Read after we'd reached the end? */
		अगर (list_empty(prev))
			वापस शून्य;
	पूर्ण

	वापस mnt_list_next(p->ns, prev);
पूर्ण

अटल व्योम *m_next(काष्ठा seq_file *m, व्योम *v, loff_t *pos)
अणु
	काष्ठा proc_mounts *p = m->निजी;
	काष्ठा mount *mnt = v;

	++*pos;
	वापस mnt_list_next(p->ns, &mnt->mnt_list);
पूर्ण

अटल व्योम m_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा proc_mounts *p = m->निजी;
	काष्ठा mount *mnt = v;

	lock_ns_list(p->ns);
	अगर (mnt)
		list_move_tail(&p->cursor.mnt_list, &mnt->mnt_list);
	अन्यथा
		list_del_init(&p->cursor.mnt_list);
	unlock_ns_list(p->ns);
	up_पढ़ो(&namespace_sem);
पूर्ण

अटल पूर्णांक m_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा proc_mounts *p = m->निजी;
	काष्ठा mount *r = v;
	वापस p->show(m, &r->mnt);
पूर्ण

स्थिर काष्ठा seq_operations mounts_op = अणु
	.start	= m_start,
	.next	= m_next,
	.stop	= m_stop,
	.show	= m_show,
पूर्ण;

व्योम mnt_cursor_del(काष्ठा mnt_namespace *ns, काष्ठा mount *cursor)
अणु
	करोwn_पढ़ो(&namespace_sem);
	lock_ns_list(ns);
	list_del(&cursor->mnt_list);
	unlock_ns_list(ns);
	up_पढ़ो(&namespace_sem);
पूर्ण
#पूर्ण_अगर  /* CONFIG_PROC_FS */

/**
 * may_umount_tree - check अगर a mount tree is busy
 * @m: root of mount tree
 *
 * This is called to check अगर a tree of mounts has any
 * खोलो files, pwds, chroots or sub mounts that are
 * busy.
 */
पूर्णांक may_umount_tree(काष्ठा vfsmount *m)
अणु
	काष्ठा mount *mnt = real_mount(m);
	पूर्णांक actual_refs = 0;
	पूर्णांक minimum_refs = 0;
	काष्ठा mount *p;
	BUG_ON(!m);

	/* ग_लिखो lock needed क्रम mnt_get_count */
	lock_mount_hash();
	क्रम (p = mnt; p; p = next_mnt(p, mnt)) अणु
		actual_refs += mnt_get_count(p);
		minimum_refs += 2;
	पूर्ण
	unlock_mount_hash();

	अगर (actual_refs > minimum_refs)
		वापस 0;

	वापस 1;
पूर्ण

EXPORT_SYMBOL(may_umount_tree);

/**
 * may_umount - check अगर a mount poपूर्णांक is busy
 * @mnt: root of mount
 *
 * This is called to check अगर a mount poपूर्णांक has any
 * खोलो files, pwds, chroots or sub mounts. If the
 * mount has sub mounts this will वापस busy
 * regardless of whether the sub mounts are busy.
 *
 * Doesn't take quota and stuff पूर्णांकo account. IOW, in some हालs it will
 * give false negatives. The मुख्य reason why it's here is that we need
 * a non-deकाष्ठाive way to look क्रम easily umountable fileप्रणालीs.
 */
पूर्णांक may_umount(काष्ठा vfsmount *mnt)
अणु
	पूर्णांक ret = 1;
	करोwn_पढ़ो(&namespace_sem);
	lock_mount_hash();
	अगर (propagate_mount_busy(real_mount(mnt), 2))
		ret = 0;
	unlock_mount_hash();
	up_पढ़ो(&namespace_sem);
	वापस ret;
पूर्ण

EXPORT_SYMBOL(may_umount);

अटल व्योम namespace_unlock(व्योम)
अणु
	काष्ठा hlist_head head;
	काष्ठा hlist_node *p;
	काष्ठा mount *m;
	LIST_HEAD(list);

	hlist_move_list(&unmounted, &head);
	list_splice_init(&ex_mountpoपूर्णांकs, &list);

	up_ग_लिखो(&namespace_sem);

	shrink_dentry_list(&list);

	अगर (likely(hlist_empty(&head)))
		वापस;

	synchronize_rcu_expedited();

	hlist_क्रम_each_entry_safe(m, p, &head, mnt_umount) अणु
		hlist_del(&m->mnt_umount);
		mntput(&m->mnt);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम namespace_lock(व्योम)
अणु
	करोwn_ग_लिखो(&namespace_sem);
पूर्ण

क्रमागत umount_tree_flags अणु
	UMOUNT_SYNC = 1,
	UMOUNT_PROPAGATE = 2,
	UMOUNT_CONNECTED = 4,
पूर्ण;

अटल bool disconnect_mount(काष्ठा mount *mnt, क्रमागत umount_tree_flags how)
अणु
	/* Leaving mounts connected is only valid क्रम lazy umounts */
	अगर (how & UMOUNT_SYNC)
		वापस true;

	/* A mount without a parent has nothing to be connected to */
	अगर (!mnt_has_parent(mnt))
		वापस true;

	/* Because the reference counting rules change when mounts are
	 * unmounted and connected, umounted mounts may not be
	 * connected to mounted mounts.
	 */
	अगर (!(mnt->mnt_parent->mnt.mnt_flags & MNT_UMOUNT))
		वापस true;

	/* Has it been requested that the mount reमुख्य connected? */
	अगर (how & UMOUNT_CONNECTED)
		वापस false;

	/* Is the mount locked such that it needs to reमुख्य connected? */
	अगर (IS_MNT_LOCKED(mnt))
		वापस false;

	/* By शेष disconnect the mount */
	वापस true;
पूर्ण

/*
 * mount_lock must be held
 * namespace_sem must be held क्रम ग_लिखो
 */
अटल व्योम umount_tree(काष्ठा mount *mnt, क्रमागत umount_tree_flags how)
अणु
	LIST_HEAD(पंचांगp_list);
	काष्ठा mount *p;

	अगर (how & UMOUNT_PROPAGATE)
		propagate_mount_unlock(mnt);

	/* Gather the mounts to umount */
	क्रम (p = mnt; p; p = next_mnt(p, mnt)) अणु
		p->mnt.mnt_flags |= MNT_UMOUNT;
		list_move(&p->mnt_list, &पंचांगp_list);
	पूर्ण

	/* Hide the mounts from mnt_mounts */
	list_क्रम_each_entry(p, &पंचांगp_list, mnt_list) अणु
		list_del_init(&p->mnt_child);
	पूर्ण

	/* Add propogated mounts to the पंचांगp_list */
	अगर (how & UMOUNT_PROPAGATE)
		propagate_umount(&पंचांगp_list);

	जबतक (!list_empty(&पंचांगp_list)) अणु
		काष्ठा mnt_namespace *ns;
		bool disconnect;
		p = list_first_entry(&पंचांगp_list, काष्ठा mount, mnt_list);
		list_del_init(&p->mnt_expire);
		list_del_init(&p->mnt_list);
		ns = p->mnt_ns;
		अगर (ns) अणु
			ns->mounts--;
			__touch_mnt_namespace(ns);
		पूर्ण
		p->mnt_ns = शून्य;
		अगर (how & UMOUNT_SYNC)
			p->mnt.mnt_flags |= MNT_SYNC_UMOUNT;

		disconnect = disconnect_mount(p, how);
		अगर (mnt_has_parent(p)) अणु
			mnt_add_count(p->mnt_parent, -1);
			अगर (!disconnect) अणु
				/* Don't क्रमget about p */
				list_add_tail(&p->mnt_child, &p->mnt_parent->mnt_mounts);
			पूर्ण अन्यथा अणु
				umount_mnt(p);
			पूर्ण
		पूर्ण
		change_mnt_propagation(p, MS_PRIVATE);
		अगर (disconnect)
			hlist_add_head(&p->mnt_umount, &unmounted);
	पूर्ण
पूर्ण

अटल व्योम shrink_submounts(काष्ठा mount *mnt);

अटल पूर्णांक करो_umount_root(काष्ठा super_block *sb)
अणु
	पूर्णांक ret = 0;

	करोwn_ग_लिखो(&sb->s_umount);
	अगर (!sb_rकरोnly(sb)) अणु
		काष्ठा fs_context *fc;

		fc = fs_context_क्रम_reconfigure(sb->s_root, SB_RDONLY,
						SB_RDONLY);
		अगर (IS_ERR(fc)) अणु
			ret = PTR_ERR(fc);
		पूर्ण अन्यथा अणु
			ret = parse_monolithic_mount_data(fc, शून्य);
			अगर (!ret)
				ret = reconfigure_super(fc);
			put_fs_context(fc);
		पूर्ण
	पूर्ण
	up_ग_लिखो(&sb->s_umount);
	वापस ret;
पूर्ण

अटल पूर्णांक करो_umount(काष्ठा mount *mnt, पूर्णांक flags)
अणु
	काष्ठा super_block *sb = mnt->mnt.mnt_sb;
	पूर्णांक retval;

	retval = security_sb_umount(&mnt->mnt, flags);
	अगर (retval)
		वापस retval;

	/*
	 * Allow userspace to request a mountpoपूर्णांक be expired rather than
	 * unmounting unconditionally. Unmount only happens अगर:
	 *  (1) the mark is alपढ़ोy set (the mark is cleared by mntput())
	 *  (2) the usage count == 1 [parent vfsmount] + 1 [sys_umount]
	 */
	अगर (flags & MNT_EXPIRE) अणु
		अगर (&mnt->mnt == current->fs->root.mnt ||
		    flags & (MNT_FORCE | MNT_DETACH))
			वापस -EINVAL;

		/*
		 * probably करोn't strictly need the lock here अगर we examined
		 * all race हालs, but it's a slowpath.
		 */
		lock_mount_hash();
		अगर (mnt_get_count(mnt) != 2) अणु
			unlock_mount_hash();
			वापस -EBUSY;
		पूर्ण
		unlock_mount_hash();

		अगर (!xchg(&mnt->mnt_expiry_mark, 1))
			वापस -EAGAIN;
	पूर्ण

	/*
	 * If we may have to पात operations to get out of this
	 * mount, and they will themselves hold resources we must
	 * allow the fs to करो things. In the Unix tradition of
	 * 'Gee thats tricky lets do it in userspace' the umount_begin
	 * might fail to complete on the first run through as other tasks
	 * must वापस, and the like. Thats क्रम the mount program to worry
	 * about क्रम the moment.
	 */

	अगर (flags & MNT_FORCE && sb->s_op->umount_begin) अणु
		sb->s_op->umount_begin(sb);
	पूर्ण

	/*
	 * No sense to grab the lock क्रम this test, but test itself looks
	 * somewhat bogus. Suggestions क्रम better replacement?
	 * Ho-hum... In principle, we might treat that as umount + चयन
	 * to rootfs. GC would eventually take care of the old vfsmount.
	 * Actually it makes sense, especially अगर rootfs would contain a
	 * /reboot - अटल binary that would बंद all descriptors and
	 * call reboot(9). Then init(8) could umount root and exec /reboot.
	 */
	अगर (&mnt->mnt == current->fs->root.mnt && !(flags & MNT_DETACH)) अणु
		/*
		 * Special हाल क्रम "unmounting" root ...
		 * we just try to remount it पढ़ोonly.
		 */
		अगर (!ns_capable(sb->s_user_ns, CAP_SYS_ADMIN))
			वापस -EPERM;
		वापस करो_umount_root(sb);
	पूर्ण

	namespace_lock();
	lock_mount_hash();

	/* Recheck MNT_LOCKED with the locks held */
	retval = -EINVAL;
	अगर (mnt->mnt.mnt_flags & MNT_LOCKED)
		जाओ out;

	event++;
	अगर (flags & MNT_DETACH) अणु
		अगर (!list_empty(&mnt->mnt_list))
			umount_tree(mnt, UMOUNT_PROPAGATE);
		retval = 0;
	पूर्ण अन्यथा अणु
		shrink_submounts(mnt);
		retval = -EBUSY;
		अगर (!propagate_mount_busy(mnt, 2)) अणु
			अगर (!list_empty(&mnt->mnt_list))
				umount_tree(mnt, UMOUNT_PROPAGATE|UMOUNT_SYNC);
			retval = 0;
		पूर्ण
	पूर्ण
out:
	unlock_mount_hash();
	namespace_unlock();
	वापस retval;
पूर्ण

/*
 * __detach_mounts - lazily unmount all mounts on the specअगरied dentry
 *
 * During unlink, सूची_हटाओ, and d_drop it is possible to loose the path
 * to an existing mountpoपूर्णांक, and wind up leaking the mount.
 * detach_mounts allows lazily unmounting those mounts instead of
 * leaking them.
 *
 * The caller may hold dentry->d_inode->i_mutex.
 */
व्योम __detach_mounts(काष्ठा dentry *dentry)
अणु
	काष्ठा mountpoपूर्णांक *mp;
	काष्ठा mount *mnt;

	namespace_lock();
	lock_mount_hash();
	mp = lookup_mountpoपूर्णांक(dentry);
	अगर (!mp)
		जाओ out_unlock;

	event++;
	जबतक (!hlist_empty(&mp->m_list)) अणु
		mnt = hlist_entry(mp->m_list.first, काष्ठा mount, mnt_mp_list);
		अगर (mnt->mnt.mnt_flags & MNT_UMOUNT) अणु
			umount_mnt(mnt);
			hlist_add_head(&mnt->mnt_umount, &unmounted);
		पूर्ण
		अन्यथा umount_tree(mnt, UMOUNT_CONNECTED);
	पूर्ण
	put_mountpoपूर्णांक(mp);
out_unlock:
	unlock_mount_hash();
	namespace_unlock();
पूर्ण

/*
 * Is the caller allowed to modअगरy his namespace?
 */
अटल अंतरभूत bool may_mount(व्योम)
अणु
	वापस ns_capable(current->nsproxy->mnt_ns->user_ns, CAP_SYS_ADMIN);
पूर्ण

#अगर_घोषित	CONFIG_MANDATORY_खाता_LOCKING
अटल अंतरभूत bool may_mandlock(व्योम)
अणु
	वापस capable(CAP_SYS_ADMIN);
पूर्ण
#अन्यथा
अटल अंतरभूत bool may_mandlock(व्योम)
अणु
	pr_warn("VFS: \"mand\" mount option not supported");
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक can_umount(स्थिर काष्ठा path *path, पूर्णांक flags)
अणु
	काष्ठा mount *mnt = real_mount(path->mnt);

	अगर (!may_mount())
		वापस -EPERM;
	अगर (path->dentry != path->mnt->mnt_root)
		वापस -EINVAL;
	अगर (!check_mnt(mnt))
		वापस -EINVAL;
	अगर (mnt->mnt.mnt_flags & MNT_LOCKED) /* Check optimistically */
		वापस -EINVAL;
	अगर (flags & MNT_FORCE && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;
	वापस 0;
पूर्ण

// caller is responsible क्रम flags being sane
पूर्णांक path_umount(काष्ठा path *path, पूर्णांक flags)
अणु
	काष्ठा mount *mnt = real_mount(path->mnt);
	पूर्णांक ret;

	ret = can_umount(path, flags);
	अगर (!ret)
		ret = करो_umount(mnt, flags);

	/* we mustn't call path_put() as that would clear mnt_expiry_mark */
	dput(path->dentry);
	mntput_no_expire(mnt);
	वापस ret;
पूर्ण

अटल पूर्णांक ksys_umount(अक्षर __user *name, पूर्णांक flags)
अणु
	पूर्णांक lookup_flags = LOOKUP_MOUNTPOINT;
	काष्ठा path path;
	पूर्णांक ret;

	// basic validity checks करोne first
	अगर (flags & ~(MNT_FORCE | MNT_DETACH | MNT_EXPIRE | UMOUNT_NOFOLLOW))
		वापस -EINVAL;

	अगर (!(flags & UMOUNT_NOFOLLOW))
		lookup_flags |= LOOKUP_FOLLOW;
	ret = user_path_at(AT_FDCWD, name, lookup_flags, &path);
	अगर (ret)
		वापस ret;
	वापस path_umount(&path, flags);
पूर्ण

SYSCALL_DEFINE2(umount, अक्षर __user *, name, पूर्णांक, flags)
अणु
	वापस ksys_umount(name, flags);
पूर्ण

#अगर_घोषित __ARCH_WANT_SYS_OLDUMOUNT

/*
 *	The 2.0 compatible umount. No flags.
 */
SYSCALL_DEFINE1(oldumount, अक्षर __user *, name)
अणु
	वापस ksys_umount(name, 0);
पूर्ण

#पूर्ण_अगर

अटल bool is_mnt_ns_file(काष्ठा dentry *dentry)
अणु
	/* Is this a proxy क्रम a mount namespace? */
	वापस dentry->d_op == &ns_dentry_operations &&
	       dentry->d_fsdata == &mntns_operations;
पूर्ण

अटल काष्ठा mnt_namespace *to_mnt_ns(काष्ठा ns_common *ns)
अणु
	वापस container_of(ns, काष्ठा mnt_namespace, ns);
पूर्ण

काष्ठा ns_common *from_mnt_ns(काष्ठा mnt_namespace *mnt)
अणु
	वापस &mnt->ns;
पूर्ण

अटल bool mnt_ns_loop(काष्ठा dentry *dentry)
अणु
	/* Could bind mounting the mount namespace inode cause a
	 * mount namespace loop?
	 */
	काष्ठा mnt_namespace *mnt_ns;
	अगर (!is_mnt_ns_file(dentry))
		वापस false;

	mnt_ns = to_mnt_ns(get_proc_ns(dentry->d_inode));
	वापस current->nsproxy->mnt_ns->seq >= mnt_ns->seq;
पूर्ण

काष्ठा mount *copy_tree(काष्ठा mount *mnt, काष्ठा dentry *dentry,
					पूर्णांक flag)
अणु
	काष्ठा mount *res, *p, *q, *r, *parent;

	अगर (!(flag & CL_COPY_UNBINDABLE) && IS_MNT_UNBINDABLE(mnt))
		वापस ERR_PTR(-EINVAL);

	अगर (!(flag & CL_COPY_MNT_NS_खाता) && is_mnt_ns_file(dentry))
		वापस ERR_PTR(-EINVAL);

	res = q = clone_mnt(mnt, dentry, flag);
	अगर (IS_ERR(q))
		वापस q;

	q->mnt_mountpoपूर्णांक = mnt->mnt_mountpoपूर्णांक;

	p = mnt;
	list_क्रम_each_entry(r, &mnt->mnt_mounts, mnt_child) अणु
		काष्ठा mount *s;
		अगर (!is_subdir(r->mnt_mountpoपूर्णांक, dentry))
			जारी;

		क्रम (s = r; s; s = next_mnt(s, r)) अणु
			अगर (!(flag & CL_COPY_UNBINDABLE) &&
			    IS_MNT_UNBINDABLE(s)) अणु
				अगर (s->mnt.mnt_flags & MNT_LOCKED) अणु
					/* Both unbindable and locked. */
					q = ERR_PTR(-EPERM);
					जाओ out;
				पूर्ण अन्यथा अणु
					s = skip_mnt_tree(s);
					जारी;
				पूर्ण
			पूर्ण
			अगर (!(flag & CL_COPY_MNT_NS_खाता) &&
			    is_mnt_ns_file(s->mnt.mnt_root)) अणु
				s = skip_mnt_tree(s);
				जारी;
			पूर्ण
			जबतक (p != s->mnt_parent) अणु
				p = p->mnt_parent;
				q = q->mnt_parent;
			पूर्ण
			p = s;
			parent = q;
			q = clone_mnt(p, p->mnt.mnt_root, flag);
			अगर (IS_ERR(q))
				जाओ out;
			lock_mount_hash();
			list_add_tail(&q->mnt_list, &res->mnt_list);
			attach_mnt(q, parent, p->mnt_mp);
			unlock_mount_hash();
		पूर्ण
	पूर्ण
	वापस res;
out:
	अगर (res) अणु
		lock_mount_hash();
		umount_tree(res, UMOUNT_SYNC);
		unlock_mount_hash();
	पूर्ण
	वापस q;
पूर्ण

/* Caller should check वापसed poपूर्णांकer क्रम errors */

काष्ठा vfsmount *collect_mounts(स्थिर काष्ठा path *path)
अणु
	काष्ठा mount *tree;
	namespace_lock();
	अगर (!check_mnt(real_mount(path->mnt)))
		tree = ERR_PTR(-EINVAL);
	अन्यथा
		tree = copy_tree(real_mount(path->mnt), path->dentry,
				 CL_COPY_ALL | CL_PRIVATE);
	namespace_unlock();
	अगर (IS_ERR(tree))
		वापस ERR_CAST(tree);
	वापस &tree->mnt;
पूर्ण

अटल व्योम मुक्त_mnt_ns(काष्ठा mnt_namespace *);
अटल काष्ठा mnt_namespace *alloc_mnt_ns(काष्ठा user_namespace *, bool);

व्योम dissolve_on_fput(काष्ठा vfsmount *mnt)
अणु
	काष्ठा mnt_namespace *ns;
	namespace_lock();
	lock_mount_hash();
	ns = real_mount(mnt)->mnt_ns;
	अगर (ns) अणु
		अगर (is_anon_ns(ns))
			umount_tree(real_mount(mnt), UMOUNT_CONNECTED);
		अन्यथा
			ns = शून्य;
	पूर्ण
	unlock_mount_hash();
	namespace_unlock();
	अगर (ns)
		मुक्त_mnt_ns(ns);
पूर्ण

व्योम drop_collected_mounts(काष्ठा vfsmount *mnt)
अणु
	namespace_lock();
	lock_mount_hash();
	umount_tree(real_mount(mnt), 0);
	unlock_mount_hash();
	namespace_unlock();
पूर्ण

/**
 * clone_निजी_mount - create a निजी clone of a path
 * @path: path to clone
 *
 * This creates a new vfsmount, which will be the clone of @path.  The new mount
 * will not be attached anywhere in the namespace and will be निजी (i.e.
 * changes to the originating mount won't be propagated पूर्णांकo this).
 *
 * Release with mntput().
 */
काष्ठा vfsmount *clone_निजी_mount(स्थिर काष्ठा path *path)
अणु
	काष्ठा mount *old_mnt = real_mount(path->mnt);
	काष्ठा mount *new_mnt;

	अगर (IS_MNT_UNBINDABLE(old_mnt))
		वापस ERR_PTR(-EINVAL);

	new_mnt = clone_mnt(old_mnt, path->dentry, CL_PRIVATE);
	अगर (IS_ERR(new_mnt))
		वापस ERR_CAST(new_mnt);

	/* Longterm mount to be हटाओd by kern_unmount*() */
	new_mnt->mnt_ns = MNT_NS_INTERNAL;

	वापस &new_mnt->mnt;
पूर्ण
EXPORT_SYMBOL_GPL(clone_निजी_mount);

पूर्णांक iterate_mounts(पूर्णांक (*f)(काष्ठा vfsmount *, व्योम *), व्योम *arg,
		   काष्ठा vfsmount *root)
अणु
	काष्ठा mount *mnt;
	पूर्णांक res = f(root, arg);
	अगर (res)
		वापस res;
	list_क्रम_each_entry(mnt, &real_mount(root)->mnt_list, mnt_list) अणु
		res = f(&mnt->mnt, arg);
		अगर (res)
			वापस res;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम lock_mnt_tree(काष्ठा mount *mnt)
अणु
	काष्ठा mount *p;

	क्रम (p = mnt; p; p = next_mnt(p, mnt)) अणु
		पूर्णांक flags = p->mnt.mnt_flags;
		/* Don't allow unprivileged users to change mount flags */
		flags |= MNT_LOCK_ATIME;

		अगर (flags & MNT_READONLY)
			flags |= MNT_LOCK_READONLY;

		अगर (flags & MNT_NODEV)
			flags |= MNT_LOCK_NODEV;

		अगर (flags & MNT_NOSUID)
			flags |= MNT_LOCK_NOSUID;

		अगर (flags & MNT_NOEXEC)
			flags |= MNT_LOCK_NOEXEC;
		/* Don't allow unprivileged users to reveal what is under a mount */
		अगर (list_empty(&p->mnt_expire))
			flags |= MNT_LOCKED;
		p->mnt.mnt_flags = flags;
	पूर्ण
पूर्ण

अटल व्योम cleanup_group_ids(काष्ठा mount *mnt, काष्ठा mount *end)
अणु
	काष्ठा mount *p;

	क्रम (p = mnt; p != end; p = next_mnt(p, mnt)) अणु
		अगर (p->mnt_group_id && !IS_MNT_SHARED(p))
			mnt_release_group_id(p);
	पूर्ण
पूर्ण

अटल पूर्णांक invent_group_ids(काष्ठा mount *mnt, bool recurse)
अणु
	काष्ठा mount *p;

	क्रम (p = mnt; p; p = recurse ? next_mnt(p, mnt) : शून्य) अणु
		अगर (!p->mnt_group_id && !IS_MNT_SHARED(p)) अणु
			पूर्णांक err = mnt_alloc_group_id(p);
			अगर (err) अणु
				cleanup_group_ids(mnt, p);
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक count_mounts(काष्ठा mnt_namespace *ns, काष्ठा mount *mnt)
अणु
	अचिन्हित पूर्णांक max = READ_ONCE(sysctl_mount_max);
	अचिन्हित पूर्णांक mounts = 0, old, pending, sum;
	काष्ठा mount *p;

	क्रम (p = mnt; p; p = next_mnt(p, mnt))
		mounts++;

	old = ns->mounts;
	pending = ns->pending_mounts;
	sum = old + pending;
	अगर ((old > sum) ||
	    (pending > sum) ||
	    (max < sum) ||
	    (mounts > (max - sum)))
		वापस -ENOSPC;

	ns->pending_mounts = pending + mounts;
	वापस 0;
पूर्ण

/*
 *  @source_mnt : mount tree to be attached
 *  @nd         : place the mount tree @source_mnt is attached
 *  @parent_nd  : अगर non-null, detach the source_mnt from its parent and
 *  		   store the parent mount and mountpoपूर्णांक dentry.
 *  		   (करोne when source_mnt is moved)
 *
 *  NOTE: in the table below explains the semantics when a source mount
 *  of a given type is attached to a destination mount of a given type.
 * ---------------------------------------------------------------------------
 * |         BIND MOUNT OPERATION                                            |
 * |**************************************************************************
 * | source-->| shared        |       निजी  |       slave    | unbindable |
 * | dest     |               |                |                |            |
 * |   |      |               |                |                |            |
 * |   v      |               |                |                |            |
 * |**************************************************************************
 * |  shared  | shared (++)   |     shared (+) |     shared(+++)|  invalid   |
 * |          |               |                |                |            |
 * |non-shared| shared (+)    |      निजी   |      slave (*) |  invalid   |
 * ***************************************************************************
 * A bind operation clones the source mount and mounts the clone on the
 * destination mount.
 *
 * (++)  the cloned mount is propagated to all the mounts in the propagation
 * 	 tree of the destination mount and the cloned mount is added to
 * 	 the peer group of the source mount.
 * (+)   the cloned mount is created under the destination mount and is marked
 *       as shared. The cloned mount is added to the peer group of the source
 *       mount.
 * (+++) the mount is propagated to all the mounts in the propagation tree
 *       of the destination mount and the cloned mount is made slave
 *       of the same master as that of the source mount. The cloned mount
 *       is marked as 'shared and slave'.
 * (*)   the cloned mount is made a slave of the same master as that of the
 * 	 source mount.
 *
 * ---------------------------------------------------------------------------
 * |         		MOVE MOUNT OPERATION                                 |
 * |**************************************************************************
 * | source-->| shared        |       निजी  |       slave    | unbindable |
 * | dest     |               |                |                |            |
 * |   |      |               |                |                |            |
 * |   v      |               |                |                |            |
 * |**************************************************************************
 * |  shared  | shared (+)    |     shared (+) |    shared(+++) |  invalid   |
 * |          |               |                |                |            |
 * |non-shared| shared (+*)   |      निजी   |    slave (*)   | unbindable |
 * ***************************************************************************
 *
 * (+)  the mount is moved to the destination. And is then propagated to
 * 	all the mounts in the propagation tree of the destination mount.
 * (+*)  the mount is moved to the destination.
 * (+++)  the mount is moved to the destination and is then propagated to
 * 	all the mounts beदीर्घing to the destination mount's propagation tree.
 * 	the mount is marked as 'shared and slave'.
 * (*)	the mount जारीs to be a slave at the new location.
 *
 * अगर the source mount is a tree, the operations explained above is
 * applied to each mount in the tree.
 * Must be called without spinlocks held, since this function can sleep
 * in allocations.
 */
अटल पूर्णांक attach_recursive_mnt(काष्ठा mount *source_mnt,
			काष्ठा mount *dest_mnt,
			काष्ठा mountpoपूर्णांक *dest_mp,
			bool moving)
अणु
	काष्ठा user_namespace *user_ns = current->nsproxy->mnt_ns->user_ns;
	HLIST_HEAD(tree_list);
	काष्ठा mnt_namespace *ns = dest_mnt->mnt_ns;
	काष्ठा mountpoपूर्णांक *smp;
	काष्ठा mount *child, *p;
	काष्ठा hlist_node *n;
	पूर्णांक err;

	/* Pपुनः_स्मृतिate a mountpoपूर्णांक in हाल the new mounts need
	 * to be tucked under other mounts.
	 */
	smp = get_mountpoपूर्णांक(source_mnt->mnt.mnt_root);
	अगर (IS_ERR(smp))
		वापस PTR_ERR(smp);

	/* Is there space to add these mounts to the mount namespace? */
	अगर (!moving) अणु
		err = count_mounts(ns, source_mnt);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (IS_MNT_SHARED(dest_mnt)) अणु
		err = invent_group_ids(source_mnt, true);
		अगर (err)
			जाओ out;
		err = propagate_mnt(dest_mnt, dest_mp, source_mnt, &tree_list);
		lock_mount_hash();
		अगर (err)
			जाओ out_cleanup_ids;
		क्रम (p = source_mnt; p; p = next_mnt(p, source_mnt))
			set_mnt_shared(p);
	पूर्ण अन्यथा अणु
		lock_mount_hash();
	पूर्ण
	अगर (moving) अणु
		unhash_mnt(source_mnt);
		attach_mnt(source_mnt, dest_mnt, dest_mp);
		touch_mnt_namespace(source_mnt->mnt_ns);
	पूर्ण अन्यथा अणु
		अगर (source_mnt->mnt_ns) अणु
			/* move from anon - the caller will destroy */
			list_del_init(&source_mnt->mnt_ns->list);
		पूर्ण
		mnt_set_mountpoपूर्णांक(dest_mnt, dest_mp, source_mnt);
		commit_tree(source_mnt);
	पूर्ण

	hlist_क्रम_each_entry_safe(child, n, &tree_list, mnt_hash) अणु
		काष्ठा mount *q;
		hlist_del_init(&child->mnt_hash);
		q = __lookup_mnt(&child->mnt_parent->mnt,
				 child->mnt_mountpoपूर्णांक);
		अगर (q)
			mnt_change_mountpoपूर्णांक(child, smp, q);
		/* Notice when we are propagating across user namespaces */
		अगर (child->mnt_parent->mnt_ns->user_ns != user_ns)
			lock_mnt_tree(child);
		child->mnt.mnt_flags &= ~MNT_LOCKED;
		commit_tree(child);
	पूर्ण
	put_mountpoपूर्णांक(smp);
	unlock_mount_hash();

	वापस 0;

 out_cleanup_ids:
	जबतक (!hlist_empty(&tree_list)) अणु
		child = hlist_entry(tree_list.first, काष्ठा mount, mnt_hash);
		child->mnt_parent->mnt_ns->pending_mounts = 0;
		umount_tree(child, UMOUNT_SYNC);
	पूर्ण
	unlock_mount_hash();
	cleanup_group_ids(source_mnt, शून्य);
 out:
	ns->pending_mounts = 0;

	पढ़ो_seqlock_excl(&mount_lock);
	put_mountpoपूर्णांक(smp);
	पढ़ो_sequnlock_excl(&mount_lock);

	वापस err;
पूर्ण

अटल काष्ठा mountpoपूर्णांक *lock_mount(काष्ठा path *path)
अणु
	काष्ठा vfsmount *mnt;
	काष्ठा dentry *dentry = path->dentry;
retry:
	inode_lock(dentry->d_inode);
	अगर (unlikely(cant_mount(dentry))) अणु
		inode_unlock(dentry->d_inode);
		वापस ERR_PTR(-ENOENT);
	पूर्ण
	namespace_lock();
	mnt = lookup_mnt(path);
	अगर (likely(!mnt)) अणु
		काष्ठा mountpoपूर्णांक *mp = get_mountpoपूर्णांक(dentry);
		अगर (IS_ERR(mp)) अणु
			namespace_unlock();
			inode_unlock(dentry->d_inode);
			वापस mp;
		पूर्ण
		वापस mp;
	पूर्ण
	namespace_unlock();
	inode_unlock(path->dentry->d_inode);
	path_put(path);
	path->mnt = mnt;
	dentry = path->dentry = dget(mnt->mnt_root);
	जाओ retry;
पूर्ण

अटल व्योम unlock_mount(काष्ठा mountpoपूर्णांक *where)
अणु
	काष्ठा dentry *dentry = where->m_dentry;

	पढ़ो_seqlock_excl(&mount_lock);
	put_mountpoपूर्णांक(where);
	पढ़ो_sequnlock_excl(&mount_lock);

	namespace_unlock();
	inode_unlock(dentry->d_inode);
पूर्ण

अटल पूर्णांक graft_tree(काष्ठा mount *mnt, काष्ठा mount *p, काष्ठा mountpoपूर्णांक *mp)
अणु
	अगर (mnt->mnt.mnt_sb->s_flags & SB_NOUSER)
		वापस -EINVAL;

	अगर (d_is_dir(mp->m_dentry) !=
	      d_is_dir(mnt->mnt.mnt_root))
		वापस -ENOTसूची;

	वापस attach_recursive_mnt(mnt, p, mp, false);
पूर्ण

/*
 * Sanity check the flags to change_mnt_propagation.
 */

अटल पूर्णांक flags_to_propagation_type(पूर्णांक ms_flags)
अणु
	पूर्णांक type = ms_flags & ~(MS_REC | MS_SILENT);

	/* Fail अगर any non-propagation flags are set */
	अगर (type & ~(MS_SHARED | MS_PRIVATE | MS_SLAVE | MS_UNBINDABLE))
		वापस 0;
	/* Only one propagation flag should be set */
	अगर (!is_घातer_of_2(type))
		वापस 0;
	वापस type;
पूर्ण

/*
 * recursively change the type of the mountpoपूर्णांक.
 */
अटल पूर्णांक करो_change_type(काष्ठा path *path, पूर्णांक ms_flags)
अणु
	काष्ठा mount *m;
	काष्ठा mount *mnt = real_mount(path->mnt);
	पूर्णांक recurse = ms_flags & MS_REC;
	पूर्णांक type;
	पूर्णांक err = 0;

	अगर (path->dentry != path->mnt->mnt_root)
		वापस -EINVAL;

	type = flags_to_propagation_type(ms_flags);
	अगर (!type)
		वापस -EINVAL;

	namespace_lock();
	अगर (type == MS_SHARED) अणु
		err = invent_group_ids(mnt, recurse);
		अगर (err)
			जाओ out_unlock;
	पूर्ण

	lock_mount_hash();
	क्रम (m = mnt; m; m = (recurse ? next_mnt(m, mnt) : शून्य))
		change_mnt_propagation(m, type);
	unlock_mount_hash();

 out_unlock:
	namespace_unlock();
	वापस err;
पूर्ण

अटल bool has_locked_children(काष्ठा mount *mnt, काष्ठा dentry *dentry)
अणु
	काष्ठा mount *child;
	list_क्रम_each_entry(child, &mnt->mnt_mounts, mnt_child) अणु
		अगर (!is_subdir(child->mnt_mountpoपूर्णांक, dentry))
			जारी;

		अगर (child->mnt.mnt_flags & MNT_LOCKED)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा mount *__करो_loopback(काष्ठा path *old_path, पूर्णांक recurse)
अणु
	काष्ठा mount *mnt = ERR_PTR(-EINVAL), *old = real_mount(old_path->mnt);

	अगर (IS_MNT_UNBINDABLE(old))
		वापस mnt;

	अगर (!check_mnt(old) && old_path->dentry->d_op != &ns_dentry_operations)
		वापस mnt;

	अगर (!recurse && has_locked_children(old, old_path->dentry))
		वापस mnt;

	अगर (recurse)
		mnt = copy_tree(old, old_path->dentry, CL_COPY_MNT_NS_खाता);
	अन्यथा
		mnt = clone_mnt(old, old_path->dentry, 0);

	अगर (!IS_ERR(mnt))
		mnt->mnt.mnt_flags &= ~MNT_LOCKED;

	वापस mnt;
पूर्ण

/*
 * करो loopback mount.
 */
अटल पूर्णांक करो_loopback(काष्ठा path *path, स्थिर अक्षर *old_name,
				पूर्णांक recurse)
अणु
	काष्ठा path old_path;
	काष्ठा mount *mnt = शून्य, *parent;
	काष्ठा mountpoपूर्णांक *mp;
	पूर्णांक err;
	अगर (!old_name || !*old_name)
		वापस -EINVAL;
	err = kern_path(old_name, LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT, &old_path);
	अगर (err)
		वापस err;

	err = -EINVAL;
	अगर (mnt_ns_loop(old_path.dentry))
		जाओ out;

	mp = lock_mount(path);
	अगर (IS_ERR(mp)) अणु
		err = PTR_ERR(mp);
		जाओ out;
	पूर्ण

	parent = real_mount(path->mnt);
	अगर (!check_mnt(parent))
		जाओ out2;

	mnt = __करो_loopback(&old_path, recurse);
	अगर (IS_ERR(mnt)) अणु
		err = PTR_ERR(mnt);
		जाओ out2;
	पूर्ण

	err = graft_tree(mnt, parent, mp);
	अगर (err) अणु
		lock_mount_hash();
		umount_tree(mnt, UMOUNT_SYNC);
		unlock_mount_hash();
	पूर्ण
out2:
	unlock_mount(mp);
out:
	path_put(&old_path);
	वापस err;
पूर्ण

अटल काष्ठा file *खोलो_detached_copy(काष्ठा path *path, bool recursive)
अणु
	काष्ठा user_namespace *user_ns = current->nsproxy->mnt_ns->user_ns;
	काष्ठा mnt_namespace *ns = alloc_mnt_ns(user_ns, true);
	काष्ठा mount *mnt, *p;
	काष्ठा file *file;

	अगर (IS_ERR(ns))
		वापस ERR_CAST(ns);

	namespace_lock();
	mnt = __करो_loopback(path, recursive);
	अगर (IS_ERR(mnt)) अणु
		namespace_unlock();
		मुक्त_mnt_ns(ns);
		वापस ERR_CAST(mnt);
	पूर्ण

	lock_mount_hash();
	क्रम (p = mnt; p; p = next_mnt(p, mnt)) अणु
		p->mnt_ns = ns;
		ns->mounts++;
	पूर्ण
	ns->root = mnt;
	list_add_tail(&ns->list, &mnt->mnt_list);
	mntget(&mnt->mnt);
	unlock_mount_hash();
	namespace_unlock();

	mntput(path->mnt);
	path->mnt = &mnt->mnt;
	file = dentry_खोलो(path, O_PATH, current_cred());
	अगर (IS_ERR(file))
		dissolve_on_fput(path->mnt);
	अन्यथा
		file->f_mode |= FMODE_NEED_UNMOUNT;
	वापस file;
पूर्ण

SYSCALL_DEFINE3(खोलो_tree, पूर्णांक, dfd, स्थिर अक्षर __user *, filename, अचिन्हित, flags)
अणु
	काष्ठा file *file;
	काष्ठा path path;
	पूर्णांक lookup_flags = LOOKUP_AUTOMOUNT | LOOKUP_FOLLOW;
	bool detached = flags & OPEN_TREE_CLONE;
	पूर्णांक error;
	पूर्णांक fd;

	BUILD_BUG_ON(OPEN_TREE_CLOEXEC != O_CLOEXEC);

	अगर (flags & ~(AT_EMPTY_PATH | AT_NO_AUTOMOUNT | AT_RECURSIVE |
		      AT_SYMLINK_NOFOLLOW | OPEN_TREE_CLONE |
		      OPEN_TREE_CLOEXEC))
		वापस -EINVAL;

	अगर ((flags & (AT_RECURSIVE | OPEN_TREE_CLONE)) == AT_RECURSIVE)
		वापस -EINVAL;

	अगर (flags & AT_NO_AUTOMOUNT)
		lookup_flags &= ~LOOKUP_AUTOMOUNT;
	अगर (flags & AT_SYMLINK_NOFOLLOW)
		lookup_flags &= ~LOOKUP_FOLLOW;
	अगर (flags & AT_EMPTY_PATH)
		lookup_flags |= LOOKUP_EMPTY;

	अगर (detached && !may_mount())
		वापस -EPERM;

	fd = get_unused_fd_flags(flags & O_CLOEXEC);
	अगर (fd < 0)
		वापस fd;

	error = user_path_at(dfd, filename, lookup_flags, &path);
	अगर (unlikely(error)) अणु
		file = ERR_PTR(error);
	पूर्ण अन्यथा अणु
		अगर (detached)
			file = खोलो_detached_copy(&path, flags & AT_RECURSIVE);
		अन्यथा
			file = dentry_खोलो(&path, O_PATH, current_cred());
		path_put(&path);
	पूर्ण
	अगर (IS_ERR(file)) अणु
		put_unused_fd(fd);
		वापस PTR_ERR(file);
	पूर्ण
	fd_install(fd, file);
	वापस fd;
पूर्ण

/*
 * Don't allow locked mount flags to be cleared.
 *
 * No locks need to be held here जबतक testing the various MNT_LOCK
 * flags because those flags can never be cleared once they are set.
 */
अटल bool can_change_locked_flags(काष्ठा mount *mnt, अचिन्हित पूर्णांक mnt_flags)
अणु
	अचिन्हित पूर्णांक fl = mnt->mnt.mnt_flags;

	अगर ((fl & MNT_LOCK_READONLY) &&
	    !(mnt_flags & MNT_READONLY))
		वापस false;

	अगर ((fl & MNT_LOCK_NODEV) &&
	    !(mnt_flags & MNT_NODEV))
		वापस false;

	अगर ((fl & MNT_LOCK_NOSUID) &&
	    !(mnt_flags & MNT_NOSUID))
		वापस false;

	अगर ((fl & MNT_LOCK_NOEXEC) &&
	    !(mnt_flags & MNT_NOEXEC))
		वापस false;

	अगर ((fl & MNT_LOCK_ATIME) &&
	    ((fl & MNT_ATIME_MASK) != (mnt_flags & MNT_ATIME_MASK)))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक change_mount_ro_state(काष्ठा mount *mnt, अचिन्हित पूर्णांक mnt_flags)
अणु
	bool पढ़ोonly_request = (mnt_flags & MNT_READONLY);

	अगर (पढ़ोonly_request == __mnt_is_पढ़ोonly(&mnt->mnt))
		वापस 0;

	अगर (पढ़ोonly_request)
		वापस mnt_make_पढ़ोonly(mnt);

	mnt->mnt.mnt_flags &= ~MNT_READONLY;
	वापस 0;
पूर्ण

अटल व्योम set_mount_attributes(काष्ठा mount *mnt, अचिन्हित पूर्णांक mnt_flags)
अणु
	mnt_flags |= mnt->mnt.mnt_flags & ~MNT_USER_SETTABLE_MASK;
	mnt->mnt.mnt_flags = mnt_flags;
	touch_mnt_namespace(mnt->mnt_ns);
पूर्ण

अटल व्योम mnt_warn_बारtamp_expiry(काष्ठा path *mountpoपूर्णांक, काष्ठा vfsmount *mnt)
अणु
	काष्ठा super_block *sb = mnt->mnt_sb;

	अगर (!__mnt_is_पढ़ोonly(mnt) &&
	   (kसमय_get_real_seconds() + TIME_UPTIME_SEC_MAX > sb->s_समय_max)) अणु
		अक्षर *buf = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
		अक्षर *mntpath = buf ? d_path(mountpoपूर्णांक, buf, PAGE_SIZE) : ERR_PTR(-ENOMEM);
		काष्ठा पंचांग पंचांग;

		समय64_to_पंचांग(sb->s_समय_max, 0, &पंचांग);

		pr_warn("%s filesystem being %s at %s supports timestamps until %04ld (0x%llx)\n",
			sb->s_type->name,
			is_mounted(mnt) ? "remounted" : "mounted",
			mntpath,
			पंचांग.पंचांग_year+1900, (अचिन्हित दीर्घ दीर्घ)sb->s_समय_max);

		मुक्त_page((अचिन्हित दीर्घ)buf);
	पूर्ण
पूर्ण

/*
 * Handle reconfiguration of the mountpoपूर्णांक only without alteration of the
 * superblock it refers to.  This is triggered by specअगरying MS_REMOUNT|MS_BIND
 * to mount(2).
 */
अटल पूर्णांक करो_reconfigure_mnt(काष्ठा path *path, अचिन्हित पूर्णांक mnt_flags)
अणु
	काष्ठा super_block *sb = path->mnt->mnt_sb;
	काष्ठा mount *mnt = real_mount(path->mnt);
	पूर्णांक ret;

	अगर (!check_mnt(mnt))
		वापस -EINVAL;

	अगर (path->dentry != mnt->mnt.mnt_root)
		वापस -EINVAL;

	अगर (!can_change_locked_flags(mnt, mnt_flags))
		वापस -EPERM;

	/*
	 * We're only checking whether the superblock is पढ़ो-only not
	 * changing it, so only take करोwn_पढ़ो(&sb->s_umount).
	 */
	करोwn_पढ़ो(&sb->s_umount);
	lock_mount_hash();
	ret = change_mount_ro_state(mnt, mnt_flags);
	अगर (ret == 0)
		set_mount_attributes(mnt, mnt_flags);
	unlock_mount_hash();
	up_पढ़ो(&sb->s_umount);

	mnt_warn_बारtamp_expiry(path, &mnt->mnt);

	वापस ret;
पूर्ण

/*
 * change fileप्रणाली flags. dir should be a physical root of fileप्रणाली.
 * If you've mounted a non-root directory somewhere and want to करो remount
 * on it - tough luck.
 */
अटल पूर्णांक करो_remount(काष्ठा path *path, पूर्णांक ms_flags, पूर्णांक sb_flags,
		      पूर्णांक mnt_flags, व्योम *data)
अणु
	पूर्णांक err;
	काष्ठा super_block *sb = path->mnt->mnt_sb;
	काष्ठा mount *mnt = real_mount(path->mnt);
	काष्ठा fs_context *fc;

	अगर (!check_mnt(mnt))
		वापस -EINVAL;

	अगर (path->dentry != path->mnt->mnt_root)
		वापस -EINVAL;

	अगर (!can_change_locked_flags(mnt, mnt_flags))
		वापस -EPERM;

	fc = fs_context_क्रम_reconfigure(path->dentry, sb_flags, MS_RMT_MASK);
	अगर (IS_ERR(fc))
		वापस PTR_ERR(fc);

	fc->oldapi = true;
	err = parse_monolithic_mount_data(fc, data);
	अगर (!err) अणु
		करोwn_ग_लिखो(&sb->s_umount);
		err = -EPERM;
		अगर (ns_capable(sb->s_user_ns, CAP_SYS_ADMIN)) अणु
			err = reconfigure_super(fc);
			अगर (!err) अणु
				lock_mount_hash();
				set_mount_attributes(mnt, mnt_flags);
				unlock_mount_hash();
			पूर्ण
		पूर्ण
		up_ग_लिखो(&sb->s_umount);
	पूर्ण

	mnt_warn_बारtamp_expiry(path, &mnt->mnt);

	put_fs_context(fc);
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक tree_contains_unbindable(काष्ठा mount *mnt)
अणु
	काष्ठा mount *p;
	क्रम (p = mnt; p; p = next_mnt(p, mnt)) अणु
		अगर (IS_MNT_UNBINDABLE(p))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Check that there aren't references to earlier/same mount namespaces in the
 * specअगरied subtree.  Such references can act as pins क्रम mount namespaces
 * that aren't checked by the mount-cycle checking code, thereby allowing
 * cycles to be made.
 */
अटल bool check_क्रम_nsfs_mounts(काष्ठा mount *subtree)
अणु
	काष्ठा mount *p;
	bool ret = false;

	lock_mount_hash();
	क्रम (p = subtree; p; p = next_mnt(p, subtree))
		अगर (mnt_ns_loop(p->mnt.mnt_root))
			जाओ out;

	ret = true;
out:
	unlock_mount_hash();
	वापस ret;
पूर्ण

अटल पूर्णांक करो_move_mount(काष्ठा path *old_path, काष्ठा path *new_path)
अणु
	काष्ठा mnt_namespace *ns;
	काष्ठा mount *p;
	काष्ठा mount *old;
	काष्ठा mount *parent;
	काष्ठा mountpoपूर्णांक *mp, *old_mp;
	पूर्णांक err;
	bool attached;

	mp = lock_mount(new_path);
	अगर (IS_ERR(mp))
		वापस PTR_ERR(mp);

	old = real_mount(old_path->mnt);
	p = real_mount(new_path->mnt);
	parent = old->mnt_parent;
	attached = mnt_has_parent(old);
	old_mp = old->mnt_mp;
	ns = old->mnt_ns;

	err = -EINVAL;
	/* The mountpoपूर्णांक must be in our namespace. */
	अगर (!check_mnt(p))
		जाओ out;

	/* The thing moved must be mounted... */
	अगर (!is_mounted(&old->mnt))
		जाओ out;

	/* ... and either ours or the root of anon namespace */
	अगर (!(attached ? check_mnt(old) : is_anon_ns(ns)))
		जाओ out;

	अगर (old->mnt.mnt_flags & MNT_LOCKED)
		जाओ out;

	अगर (old_path->dentry != old_path->mnt->mnt_root)
		जाओ out;

	अगर (d_is_dir(new_path->dentry) !=
	    d_is_dir(old_path->dentry))
		जाओ out;
	/*
	 * Don't move a mount residing in a shared parent.
	 */
	अगर (attached && IS_MNT_SHARED(parent))
		जाओ out;
	/*
	 * Don't move a mount tree containing unbindable mounts to a destination
	 * mount which is shared.
	 */
	अगर (IS_MNT_SHARED(p) && tree_contains_unbindable(old))
		जाओ out;
	err = -ELOOP;
	अगर (!check_क्रम_nsfs_mounts(old))
		जाओ out;
	क्रम (; mnt_has_parent(p); p = p->mnt_parent)
		अगर (p == old)
			जाओ out;

	err = attach_recursive_mnt(old, real_mount(new_path->mnt), mp,
				   attached);
	अगर (err)
		जाओ out;

	/* अगर the mount is moved, it should no दीर्घer be expire
	 * स्वतःmatically */
	list_del_init(&old->mnt_expire);
	अगर (attached)
		put_mountpoपूर्णांक(old_mp);
out:
	unlock_mount(mp);
	अगर (!err) अणु
		अगर (attached)
			mntput_no_expire(parent);
		अन्यथा
			मुक्त_mnt_ns(ns);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक करो_move_mount_old(काष्ठा path *path, स्थिर अक्षर *old_name)
अणु
	काष्ठा path old_path;
	पूर्णांक err;

	अगर (!old_name || !*old_name)
		वापस -EINVAL;

	err = kern_path(old_name, LOOKUP_FOLLOW, &old_path);
	अगर (err)
		वापस err;

	err = करो_move_mount(&old_path, path);
	path_put(&old_path);
	वापस err;
पूर्ण

/*
 * add a mount पूर्णांकo a namespace's mount tree
 */
अटल पूर्णांक करो_add_mount(काष्ठा mount *newmnt, काष्ठा mountpoपूर्णांक *mp,
			काष्ठा path *path, पूर्णांक mnt_flags)
अणु
	काष्ठा mount *parent = real_mount(path->mnt);

	mnt_flags &= ~MNT_INTERNAL_FLAGS;

	अगर (unlikely(!check_mnt(parent))) अणु
		/* that's acceptable only क्रम स्वतःmounts करोne in निजी ns */
		अगर (!(mnt_flags & MNT_SHRINKABLE))
			वापस -EINVAL;
		/* ... and क्रम those we'd better have mountpoपूर्णांक still alive */
		अगर (!parent->mnt_ns)
			वापस -EINVAL;
	पूर्ण

	/* Refuse the same fileप्रणाली on the same mount poपूर्णांक */
	अगर (path->mnt->mnt_sb == newmnt->mnt.mnt_sb &&
	    path->mnt->mnt_root == path->dentry)
		वापस -EBUSY;

	अगर (d_is_symlink(newmnt->mnt.mnt_root))
		वापस -EINVAL;

	newmnt->mnt.mnt_flags = mnt_flags;
	वापस graft_tree(newmnt, parent, mp);
पूर्ण

अटल bool mount_too_revealing(स्थिर काष्ठा super_block *sb, पूर्णांक *new_mnt_flags);

/*
 * Create a new mount using a superblock configuration and request it
 * be added to the namespace tree.
 */
अटल पूर्णांक करो_new_mount_fc(काष्ठा fs_context *fc, काष्ठा path *mountpoपूर्णांक,
			   अचिन्हित पूर्णांक mnt_flags)
अणु
	काष्ठा vfsmount *mnt;
	काष्ठा mountpoपूर्णांक *mp;
	काष्ठा super_block *sb = fc->root->d_sb;
	पूर्णांक error;

	error = security_sb_kern_mount(sb);
	अगर (!error && mount_too_revealing(sb, &mnt_flags))
		error = -EPERM;

	अगर (unlikely(error)) अणु
		fc_drop_locked(fc);
		वापस error;
	पूर्ण

	up_ग_लिखो(&sb->s_umount);

	mnt = vfs_create_mount(fc);
	अगर (IS_ERR(mnt))
		वापस PTR_ERR(mnt);

	mnt_warn_बारtamp_expiry(mountpoपूर्णांक, mnt);

	mp = lock_mount(mountpoपूर्णांक);
	अगर (IS_ERR(mp)) अणु
		mntput(mnt);
		वापस PTR_ERR(mp);
	पूर्ण
	error = करो_add_mount(real_mount(mnt), mp, mountpoपूर्णांक, mnt_flags);
	unlock_mount(mp);
	अगर (error < 0)
		mntput(mnt);
	वापस error;
पूर्ण

/*
 * create a new mount क्रम userspace and request it to be added पूर्णांकo the
 * namespace's tree
 */
अटल पूर्णांक करो_new_mount(काष्ठा path *path, स्थिर अक्षर *fstype, पूर्णांक sb_flags,
			पूर्णांक mnt_flags, स्थिर अक्षर *name, व्योम *data)
अणु
	काष्ठा file_प्रणाली_type *type;
	काष्ठा fs_context *fc;
	स्थिर अक्षर *subtype = शून्य;
	पूर्णांक err = 0;

	अगर (!fstype)
		वापस -EINVAL;

	type = get_fs_type(fstype);
	अगर (!type)
		वापस -ENODEV;

	अगर (type->fs_flags & FS_HAS_SUBTYPE) अणु
		subtype = म_अक्षर(fstype, '.');
		अगर (subtype) अणु
			subtype++;
			अगर (!*subtype) अणु
				put_fileप्रणाली(type);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	fc = fs_context_क्रम_mount(type, sb_flags);
	put_fileप्रणाली(type);
	अगर (IS_ERR(fc))
		वापस PTR_ERR(fc);

	अगर (subtype)
		err = vfs_parse_fs_string(fc, "subtype",
					  subtype, म_माप(subtype));
	अगर (!err && name)
		err = vfs_parse_fs_string(fc, "source", name, म_माप(name));
	अगर (!err)
		err = parse_monolithic_mount_data(fc, data);
	अगर (!err && !mount_capable(fc))
		err = -EPERM;
	अगर (!err)
		err = vfs_get_tree(fc);
	अगर (!err)
		err = करो_new_mount_fc(fc, path, mnt_flags);

	put_fs_context(fc);
	वापस err;
पूर्ण

पूर्णांक finish_स्वतःmount(काष्ठा vfsmount *m, काष्ठा path *path)
अणु
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा mountpoपूर्णांक *mp;
	काष्ठा mount *mnt;
	पूर्णांक err;

	अगर (!m)
		वापस 0;
	अगर (IS_ERR(m))
		वापस PTR_ERR(m);

	mnt = real_mount(m);
	/* The new mount record should have at least 2 refs to prevent it being
	 * expired beक्रमe we get a chance to add it
	 */
	BUG_ON(mnt_get_count(mnt) < 2);

	अगर (m->mnt_sb == path->mnt->mnt_sb &&
	    m->mnt_root == dentry) अणु
		err = -ELOOP;
		जाओ discard;
	पूर्ण

	/*
	 * we करोn't want to use lock_mount() - in this हाल finding something
	 * that overmounts our mountpoपूर्णांक to be means "quitely drop what we've
	 * got", not "try to mount it on top".
	 */
	inode_lock(dentry->d_inode);
	namespace_lock();
	अगर (unlikely(cant_mount(dentry))) अणु
		err = -ENOENT;
		जाओ discard_locked;
	पूर्ण
	rcu_पढ़ो_lock();
	अगर (unlikely(__lookup_mnt(path->mnt, dentry))) अणु
		rcu_पढ़ो_unlock();
		err = 0;
		जाओ discard_locked;
	पूर्ण
	rcu_पढ़ो_unlock();
	mp = get_mountpoपूर्णांक(dentry);
	अगर (IS_ERR(mp)) अणु
		err = PTR_ERR(mp);
		जाओ discard_locked;
	पूर्ण

	err = करो_add_mount(mnt, mp, path, path->mnt->mnt_flags | MNT_SHRINKABLE);
	unlock_mount(mp);
	अगर (unlikely(err))
		जाओ discard;
	mntput(m);
	वापस 0;

discard_locked:
	namespace_unlock();
	inode_unlock(dentry->d_inode);
discard:
	/* हटाओ m from any expiration list it may be on */
	अगर (!list_empty(&mnt->mnt_expire)) अणु
		namespace_lock();
		list_del_init(&mnt->mnt_expire);
		namespace_unlock();
	पूर्ण
	mntput(m);
	mntput(m);
	वापस err;
पूर्ण

/**
 * mnt_set_expiry - Put a mount on an expiration list
 * @mnt: The mount to list.
 * @expiry_list: The list to add the mount to.
 */
व्योम mnt_set_expiry(काष्ठा vfsmount *mnt, काष्ठा list_head *expiry_list)
अणु
	namespace_lock();

	list_add_tail(&real_mount(mnt)->mnt_expire, expiry_list);

	namespace_unlock();
पूर्ण
EXPORT_SYMBOL(mnt_set_expiry);

/*
 * process a list of expirable mountpoपूर्णांकs with the पूर्णांकent of discarding any
 * mountpoपूर्णांकs that aren't in use and haven't been touched since last we came
 * here
 */
व्योम mark_mounts_क्रम_expiry(काष्ठा list_head *mounts)
अणु
	काष्ठा mount *mnt, *next;
	LIST_HEAD(graveyard);

	अगर (list_empty(mounts))
		वापस;

	namespace_lock();
	lock_mount_hash();

	/* extract from the expiration list every vfsmount that matches the
	 * following criteria:
	 * - only referenced by its parent vfsmount
	 * - still marked क्रम expiry (marked on the last call here; marks are
	 *   cleared by mntput())
	 */
	list_क्रम_each_entry_safe(mnt, next, mounts, mnt_expire) अणु
		अगर (!xchg(&mnt->mnt_expiry_mark, 1) ||
			propagate_mount_busy(mnt, 1))
			जारी;
		list_move(&mnt->mnt_expire, &graveyard);
	पूर्ण
	जबतक (!list_empty(&graveyard)) अणु
		mnt = list_first_entry(&graveyard, काष्ठा mount, mnt_expire);
		touch_mnt_namespace(mnt->mnt_ns);
		umount_tree(mnt, UMOUNT_PROPAGATE|UMOUNT_SYNC);
	पूर्ण
	unlock_mount_hash();
	namespace_unlock();
पूर्ण

EXPORT_SYMBOL_GPL(mark_mounts_क्रम_expiry);

/*
 * Ripoff of 'select_parent()'
 *
 * search the list of submounts क्रम a given mountpoपूर्णांक, and move any
 * shrinkable submounts to the 'graveyard' list.
 */
अटल पूर्णांक select_submounts(काष्ठा mount *parent, काष्ठा list_head *graveyard)
अणु
	काष्ठा mount *this_parent = parent;
	काष्ठा list_head *next;
	पूर्णांक found = 0;

repeat:
	next = this_parent->mnt_mounts.next;
resume:
	जबतक (next != &this_parent->mnt_mounts) अणु
		काष्ठा list_head *पंचांगp = next;
		काष्ठा mount *mnt = list_entry(पंचांगp, काष्ठा mount, mnt_child);

		next = पंचांगp->next;
		अगर (!(mnt->mnt.mnt_flags & MNT_SHRINKABLE))
			जारी;
		/*
		 * Descend a level अगर the d_mounts list is non-empty.
		 */
		अगर (!list_empty(&mnt->mnt_mounts)) अणु
			this_parent = mnt;
			जाओ repeat;
		पूर्ण

		अगर (!propagate_mount_busy(mnt, 1)) अणु
			list_move_tail(&mnt->mnt_expire, graveyard);
			found++;
		पूर्ण
	पूर्ण
	/*
	 * All करोne at this level ... ascend and resume the search
	 */
	अगर (this_parent != parent) अणु
		next = this_parent->mnt_child.next;
		this_parent = this_parent->mnt_parent;
		जाओ resume;
	पूर्ण
	वापस found;
पूर्ण

/*
 * process a list of expirable mountpoपूर्णांकs with the पूर्णांकent of discarding any
 * submounts of a specअगरic parent mountpoपूर्णांक
 *
 * mount_lock must be held क्रम ग_लिखो
 */
अटल व्योम shrink_submounts(काष्ठा mount *mnt)
अणु
	LIST_HEAD(graveyard);
	काष्ठा mount *m;

	/* extract submounts of 'mountpoint' from the expiration list */
	जबतक (select_submounts(mnt, &graveyard)) अणु
		जबतक (!list_empty(&graveyard)) अणु
			m = list_first_entry(&graveyard, काष्ठा mount,
						mnt_expire);
			touch_mnt_namespace(m->mnt_ns);
			umount_tree(m, UMOUNT_PROPAGATE|UMOUNT_SYNC);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम *copy_mount_options(स्थिर व्योम __user * data)
अणु
	अक्षर *copy;
	अचिन्हित left, offset;

	अगर (!data)
		वापस शून्य;

	copy = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!copy)
		वापस ERR_PTR(-ENOMEM);

	left = copy_from_user(copy, data, PAGE_SIZE);

	/*
	 * Not all architectures have an exact copy_from_user(). Resort to
	 * byte at a समय.
	 */
	offset = PAGE_SIZE - left;
	जबतक (left) अणु
		अक्षर c;
		अगर (get_user(c, (स्थिर अक्षर __user *)data + offset))
			अवरोध;
		copy[offset] = c;
		left--;
		offset++;
	पूर्ण

	अगर (left == PAGE_SIZE) अणु
		kमुक्त(copy);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	वापस copy;
पूर्ण

अटल अक्षर *copy_mount_string(स्थिर व्योम __user *data)
अणु
	वापस data ? strndup_user(data, PATH_MAX) : शून्य;
पूर्ण

/*
 * Flags is a 32-bit value that allows up to 31 non-fs dependent flags to
 * be given to the mount() call (ie: पढ़ो-only, no-dev, no-suid etc).
 *
 * data is a (व्योम *) that can poपूर्णांक to any काष्ठाure up to
 * PAGE_SIZE-1 bytes, which can contain arbitrary fs-dependent
 * inक्रमmation (or be शून्य).
 *
 * Pre-0.97 versions of mount() didn't have a flags word.
 * When the flags word was पूर्णांकroduced its top half was required
 * to have the magic value 0xC0ED, and this reमुख्यed so until 2.4.0-test9.
 * Thereक्रमe, अगर this magic number is present, it carries no inक्रमmation
 * and must be discarded.
 */
पूर्णांक path_mount(स्थिर अक्षर *dev_name, काष्ठा path *path,
		स्थिर अक्षर *type_page, अचिन्हित दीर्घ flags, व्योम *data_page)
अणु
	अचिन्हित पूर्णांक mnt_flags = 0, sb_flags;
	पूर्णांक ret;

	/* Discard magic */
	अगर ((flags & MS_MGC_MSK) == MS_MGC_VAL)
		flags &= ~MS_MGC_MSK;

	/* Basic sanity checks */
	अगर (data_page)
		((अक्षर *)data_page)[PAGE_SIZE - 1] = 0;

	अगर (flags & MS_NOUSER)
		वापस -EINVAL;

	ret = security_sb_mount(dev_name, path, type_page, flags, data_page);
	अगर (ret)
		वापस ret;
	अगर (!may_mount())
		वापस -EPERM;
	अगर ((flags & SB_MANDLOCK) && !may_mandlock())
		वापस -EPERM;

	/* Default to relaसमय unless overriden */
	अगर (!(flags & MS_NOATIME))
		mnt_flags |= MNT_RELATIME;

	/* Separate the per-mountpoपूर्णांक flags */
	अगर (flags & MS_NOSUID)
		mnt_flags |= MNT_NOSUID;
	अगर (flags & MS_NODEV)
		mnt_flags |= MNT_NODEV;
	अगर (flags & MS_NOEXEC)
		mnt_flags |= MNT_NOEXEC;
	अगर (flags & MS_NOATIME)
		mnt_flags |= MNT_NOATIME;
	अगर (flags & MS_NOसूचीATIME)
		mnt_flags |= MNT_NOसूचीATIME;
	अगर (flags & MS_STRICTATIME)
		mnt_flags &= ~(MNT_RELATIME | MNT_NOATIME);
	अगर (flags & MS_RDONLY)
		mnt_flags |= MNT_READONLY;
	अगर (flags & MS_NOSYMFOLLOW)
		mnt_flags |= MNT_NOSYMFOLLOW;

	/* The शेष aसमय क्रम remount is preservation */
	अगर ((flags & MS_REMOUNT) &&
	    ((flags & (MS_NOATIME | MS_NOसूचीATIME | MS_RELATIME |
		       MS_STRICTATIME)) == 0)) अणु
		mnt_flags &= ~MNT_ATIME_MASK;
		mnt_flags |= path->mnt->mnt_flags & MNT_ATIME_MASK;
	पूर्ण

	sb_flags = flags & (SB_RDONLY |
			    SB_SYNCHRONOUS |
			    SB_MANDLOCK |
			    SB_सूचीSYNC |
			    SB_SILENT |
			    SB_POSIXACL |
			    SB_LAZYTIME |
			    SB_I_VERSION);

	अगर ((flags & (MS_REMOUNT | MS_BIND)) == (MS_REMOUNT | MS_BIND))
		वापस करो_reconfigure_mnt(path, mnt_flags);
	अगर (flags & MS_REMOUNT)
		वापस करो_remount(path, flags, sb_flags, mnt_flags, data_page);
	अगर (flags & MS_BIND)
		वापस करो_loopback(path, dev_name, flags & MS_REC);
	अगर (flags & (MS_SHARED | MS_PRIVATE | MS_SLAVE | MS_UNBINDABLE))
		वापस करो_change_type(path, flags);
	अगर (flags & MS_MOVE)
		वापस करो_move_mount_old(path, dev_name);

	वापस करो_new_mount(path, type_page, sb_flags, mnt_flags, dev_name,
			    data_page);
पूर्ण

दीर्घ करो_mount(स्थिर अक्षर *dev_name, स्थिर अक्षर __user *dir_name,
		स्थिर अक्षर *type_page, अचिन्हित दीर्घ flags, व्योम *data_page)
अणु
	काष्ठा path path;
	पूर्णांक ret;

	ret = user_path_at(AT_FDCWD, dir_name, LOOKUP_FOLLOW, &path);
	अगर (ret)
		वापस ret;
	ret = path_mount(dev_name, &path, type_page, flags, data_page);
	path_put(&path);
	वापस ret;
पूर्ण

अटल काष्ठा ucounts *inc_mnt_namespaces(काष्ठा user_namespace *ns)
अणु
	वापस inc_ucount(ns, current_euid(), UCOUNT_MNT_NAMESPACES);
पूर्ण

अटल व्योम dec_mnt_namespaces(काष्ठा ucounts *ucounts)
अणु
	dec_ucount(ucounts, UCOUNT_MNT_NAMESPACES);
पूर्ण

अटल व्योम मुक्त_mnt_ns(काष्ठा mnt_namespace *ns)
अणु
	अगर (!is_anon_ns(ns))
		ns_मुक्त_inum(&ns->ns);
	dec_mnt_namespaces(ns->ucounts);
	put_user_ns(ns->user_ns);
	kमुक्त(ns);
पूर्ण

/*
 * Assign a sequence number so we can detect when we attempt to bind
 * mount a reference to an older mount namespace पूर्णांकo the current
 * mount namespace, preventing reference counting loops.  A 64bit
 * number incrementing at 10Ghz will take 12,427 years to wrap which
 * is effectively never, so we can ignore the possibility.
 */
अटल atomic64_t mnt_ns_seq = ATOMIC64_INIT(1);

अटल काष्ठा mnt_namespace *alloc_mnt_ns(काष्ठा user_namespace *user_ns, bool anon)
अणु
	काष्ठा mnt_namespace *new_ns;
	काष्ठा ucounts *ucounts;
	पूर्णांक ret;

	ucounts = inc_mnt_namespaces(user_ns);
	अगर (!ucounts)
		वापस ERR_PTR(-ENOSPC);

	new_ns = kzalloc(माप(काष्ठा mnt_namespace), GFP_KERNEL);
	अगर (!new_ns) अणु
		dec_mnt_namespaces(ucounts);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	अगर (!anon) अणु
		ret = ns_alloc_inum(&new_ns->ns);
		अगर (ret) अणु
			kमुक्त(new_ns);
			dec_mnt_namespaces(ucounts);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण
	new_ns->ns.ops = &mntns_operations;
	अगर (!anon)
		new_ns->seq = atomic64_add_वापस(1, &mnt_ns_seq);
	refcount_set(&new_ns->ns.count, 1);
	INIT_LIST_HEAD(&new_ns->list);
	init_रुकोqueue_head(&new_ns->poll);
	spin_lock_init(&new_ns->ns_lock);
	new_ns->user_ns = get_user_ns(user_ns);
	new_ns->ucounts = ucounts;
	वापस new_ns;
पूर्ण

__latent_entropy
काष्ठा mnt_namespace *copy_mnt_ns(अचिन्हित दीर्घ flags, काष्ठा mnt_namespace *ns,
		काष्ठा user_namespace *user_ns, काष्ठा fs_काष्ठा *new_fs)
अणु
	काष्ठा mnt_namespace *new_ns;
	काष्ठा vfsmount *rooपंचांगnt = शून्य, *pwdmnt = शून्य;
	काष्ठा mount *p, *q;
	काष्ठा mount *old;
	काष्ठा mount *new;
	पूर्णांक copy_flags;

	BUG_ON(!ns);

	अगर (likely(!(flags & CLONE_NEWNS))) अणु
		get_mnt_ns(ns);
		वापस ns;
	पूर्ण

	old = ns->root;

	new_ns = alloc_mnt_ns(user_ns, false);
	अगर (IS_ERR(new_ns))
		वापस new_ns;

	namespace_lock();
	/* First pass: copy the tree topology */
	copy_flags = CL_COPY_UNBINDABLE | CL_EXPIRE;
	अगर (user_ns != ns->user_ns)
		copy_flags |= CL_SHARED_TO_SLAVE;
	new = copy_tree(old, old->mnt.mnt_root, copy_flags);
	अगर (IS_ERR(new)) अणु
		namespace_unlock();
		मुक्त_mnt_ns(new_ns);
		वापस ERR_CAST(new);
	पूर्ण
	अगर (user_ns != ns->user_ns) अणु
		lock_mount_hash();
		lock_mnt_tree(new);
		unlock_mount_hash();
	पूर्ण
	new_ns->root = new;
	list_add_tail(&new_ns->list, &new->mnt_list);

	/*
	 * Second pass: चयन the tsk->fs->* elements and mark new vfsmounts
	 * as beदीर्घing to new namespace.  We have alपढ़ोy acquired a निजी
	 * fs_काष्ठा, so tsk->fs->lock is not needed.
	 */
	p = old;
	q = new;
	जबतक (p) अणु
		q->mnt_ns = new_ns;
		new_ns->mounts++;
		अगर (new_fs) अणु
			अगर (&p->mnt == new_fs->root.mnt) अणु
				new_fs->root.mnt = mntget(&q->mnt);
				rooपंचांगnt = &p->mnt;
			पूर्ण
			अगर (&p->mnt == new_fs->pwd.mnt) अणु
				new_fs->pwd.mnt = mntget(&q->mnt);
				pwdmnt = &p->mnt;
			पूर्ण
		पूर्ण
		p = next_mnt(p, old);
		q = next_mnt(q, new);
		अगर (!q)
			अवरोध;
		जबतक (p->mnt.mnt_root != q->mnt.mnt_root)
			p = next_mnt(p, old);
	पूर्ण
	namespace_unlock();

	अगर (rooपंचांगnt)
		mntput(rooपंचांगnt);
	अगर (pwdmnt)
		mntput(pwdmnt);

	वापस new_ns;
पूर्ण

काष्ठा dentry *mount_subtree(काष्ठा vfsmount *m, स्थिर अक्षर *name)
अणु
	काष्ठा mount *mnt = real_mount(m);
	काष्ठा mnt_namespace *ns;
	काष्ठा super_block *s;
	काष्ठा path path;
	पूर्णांक err;

	ns = alloc_mnt_ns(&init_user_ns, true);
	अगर (IS_ERR(ns)) अणु
		mntput(m);
		वापस ERR_CAST(ns);
	पूर्ण
	mnt->mnt_ns = ns;
	ns->root = mnt;
	ns->mounts++;
	list_add(&mnt->mnt_list, &ns->list);

	err = vfs_path_lookup(m->mnt_root, m,
			name, LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT, &path);

	put_mnt_ns(ns);

	अगर (err)
		वापस ERR_PTR(err);

	/* trade a vfsmount reference क्रम active sb one */
	s = path.mnt->mnt_sb;
	atomic_inc(&s->s_active);
	mntput(path.mnt);
	/* lock the sucker */
	करोwn_ग_लिखो(&s->s_umount);
	/* ... and वापस the root of (sub)tree on it */
	वापस path.dentry;
पूर्ण
EXPORT_SYMBOL(mount_subtree);

SYSCALL_DEFINE5(mount, अक्षर __user *, dev_name, अक्षर __user *, dir_name,
		अक्षर __user *, type, अचिन्हित दीर्घ, flags, व्योम __user *, data)
अणु
	पूर्णांक ret;
	अक्षर *kernel_type;
	अक्षर *kernel_dev;
	व्योम *options;

	kernel_type = copy_mount_string(type);
	ret = PTR_ERR(kernel_type);
	अगर (IS_ERR(kernel_type))
		जाओ out_type;

	kernel_dev = copy_mount_string(dev_name);
	ret = PTR_ERR(kernel_dev);
	अगर (IS_ERR(kernel_dev))
		जाओ out_dev;

	options = copy_mount_options(data);
	ret = PTR_ERR(options);
	अगर (IS_ERR(options))
		जाओ out_data;

	ret = करो_mount(kernel_dev, dir_name, kernel_type, flags, options);

	kमुक्त(options);
out_data:
	kमुक्त(kernel_dev);
out_dev:
	kमुक्त(kernel_type);
out_type:
	वापस ret;
पूर्ण

#घोषणा FSMOUNT_VALID_FLAGS \
	(MOUNT_ATTR_RDONLY | MOUNT_ATTR_NOSUID | MOUNT_ATTR_NODEV | \
	 MOUNT_ATTR_NOEXEC | MOUNT_ATTR__ATIME | MOUNT_ATTR_NOसूचीATIME)

#घोषणा MOUNT_SETATTR_VALID_FLAGS (FSMOUNT_VALID_FLAGS | MOUNT_ATTR_IDMAP)

#घोषणा MOUNT_SETATTR_PROPAGATION_FLAGS \
	(MS_UNBINDABLE | MS_PRIVATE | MS_SLAVE | MS_SHARED)

अटल अचिन्हित पूर्णांक attr_flags_to_mnt_flags(u64 attr_flags)
अणु
	अचिन्हित पूर्णांक mnt_flags = 0;

	अगर (attr_flags & MOUNT_ATTR_RDONLY)
		mnt_flags |= MNT_READONLY;
	अगर (attr_flags & MOUNT_ATTR_NOSUID)
		mnt_flags |= MNT_NOSUID;
	अगर (attr_flags & MOUNT_ATTR_NODEV)
		mnt_flags |= MNT_NODEV;
	अगर (attr_flags & MOUNT_ATTR_NOEXEC)
		mnt_flags |= MNT_NOEXEC;
	अगर (attr_flags & MOUNT_ATTR_NOसूचीATIME)
		mnt_flags |= MNT_NOसूचीATIME;

	वापस mnt_flags;
पूर्ण

/*
 * Create a kernel mount representation क्रम a new, prepared superblock
 * (specअगरied by fs_fd) and attach to an खोलो_tree-like file descriptor.
 */
SYSCALL_DEFINE3(fsmount, पूर्णांक, fs_fd, अचिन्हित पूर्णांक, flags,
		अचिन्हित पूर्णांक, attr_flags)
अणु
	काष्ठा mnt_namespace *ns;
	काष्ठा fs_context *fc;
	काष्ठा file *file;
	काष्ठा path newmount;
	काष्ठा mount *mnt;
	काष्ठा fd f;
	अचिन्हित पूर्णांक mnt_flags = 0;
	दीर्घ ret;

	अगर (!may_mount())
		वापस -EPERM;

	अगर ((flags & ~(FSMOUNT_CLOEXEC)) != 0)
		वापस -EINVAL;

	अगर (attr_flags & ~FSMOUNT_VALID_FLAGS)
		वापस -EINVAL;

	mnt_flags = attr_flags_to_mnt_flags(attr_flags);

	चयन (attr_flags & MOUNT_ATTR__ATIME) अणु
	हाल MOUNT_ATTR_STRICTATIME:
		अवरोध;
	हाल MOUNT_ATTR_NOATIME:
		mnt_flags |= MNT_NOATIME;
		अवरोध;
	हाल MOUNT_ATTR_RELATIME:
		mnt_flags |= MNT_RELATIME;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	f = fdget(fs_fd);
	अगर (!f.file)
		वापस -EBADF;

	ret = -EINVAL;
	अगर (f.file->f_op != &fscontext_fops)
		जाओ err_fsfd;

	fc = f.file->निजी_data;

	ret = mutex_lock_पूर्णांकerruptible(&fc->uapi_mutex);
	अगर (ret < 0)
		जाओ err_fsfd;

	/* There must be a valid superblock or we can't mount it */
	ret = -EINVAL;
	अगर (!fc->root)
		जाओ err_unlock;

	ret = -EPERM;
	अगर (mount_too_revealing(fc->root->d_sb, &mnt_flags)) अणु
		pr_warn("VFS: Mount too revealing\n");
		जाओ err_unlock;
	पूर्ण

	ret = -EBUSY;
	अगर (fc->phase != FS_CONTEXT_AWAITING_MOUNT)
		जाओ err_unlock;

	ret = -EPERM;
	अगर ((fc->sb_flags & SB_MANDLOCK) && !may_mandlock())
		जाओ err_unlock;

	newmount.mnt = vfs_create_mount(fc);
	अगर (IS_ERR(newmount.mnt)) अणु
		ret = PTR_ERR(newmount.mnt);
		जाओ err_unlock;
	पूर्ण
	newmount.dentry = dget(fc->root);
	newmount.mnt->mnt_flags = mnt_flags;

	/* We've करोne the mount bit - now move the file context पूर्णांकo more or
	 * less the same state as अगर we'd done an fspick().  We don't want to
	 * करो any memory allocation or anything like that at this poपूर्णांक as we
	 * करोn't want to have to handle any errors incurred.
	 */
	vfs_clean_context(fc);

	ns = alloc_mnt_ns(current->nsproxy->mnt_ns->user_ns, true);
	अगर (IS_ERR(ns)) अणु
		ret = PTR_ERR(ns);
		जाओ err_path;
	पूर्ण
	mnt = real_mount(newmount.mnt);
	mnt->mnt_ns = ns;
	ns->root = mnt;
	ns->mounts = 1;
	list_add(&mnt->mnt_list, &ns->list);
	mntget(newmount.mnt);

	/* Attach to an apparent O_PATH fd with a note that we need to unmount
	 * it, not just simply put it.
	 */
	file = dentry_खोलो(&newmount, O_PATH, fc->cred);
	अगर (IS_ERR(file)) अणु
		dissolve_on_fput(newmount.mnt);
		ret = PTR_ERR(file);
		जाओ err_path;
	पूर्ण
	file->f_mode |= FMODE_NEED_UNMOUNT;

	ret = get_unused_fd_flags((flags & FSMOUNT_CLOEXEC) ? O_CLOEXEC : 0);
	अगर (ret >= 0)
		fd_install(ret, file);
	अन्यथा
		fput(file);

err_path:
	path_put(&newmount);
err_unlock:
	mutex_unlock(&fc->uapi_mutex);
err_fsfd:
	fdput(f);
	वापस ret;
पूर्ण

/*
 * Move a mount from one place to another.  In combination with
 * fsखोलो()/fsmount() this is used to install a new mount and in combination
 * with खोलो_tree(OPEN_TREE_CLONE [| AT_RECURSIVE]) it can be used to copy
 * a mount subtree.
 *
 * Note the flags value is a combination of MOVE_MOUNT_* flags.
 */
SYSCALL_DEFINE5(move_mount,
		पूर्णांक, from_dfd, स्थिर अक्षर __user *, from_pathname,
		पूर्णांक, to_dfd, स्थिर अक्षर __user *, to_pathname,
		अचिन्हित पूर्णांक, flags)
अणु
	काष्ठा path from_path, to_path;
	अचिन्हित पूर्णांक lflags;
	पूर्णांक ret = 0;

	अगर (!may_mount())
		वापस -EPERM;

	अगर (flags & ~MOVE_MOUNT__MASK)
		वापस -EINVAL;

	/* If someone gives a pathname, they aren't permitted to move
	 * from an fd that requires unmount as we can't get at the flag
	 * to clear it afterwards.
	 */
	lflags = 0;
	अगर (flags & MOVE_MOUNT_F_SYMLINKS)	lflags |= LOOKUP_FOLLOW;
	अगर (flags & MOVE_MOUNT_F_AUTOMOUNTS)	lflags |= LOOKUP_AUTOMOUNT;
	अगर (flags & MOVE_MOUNT_F_EMPTY_PATH)	lflags |= LOOKUP_EMPTY;

	ret = user_path_at(from_dfd, from_pathname, lflags, &from_path);
	अगर (ret < 0)
		वापस ret;

	lflags = 0;
	अगर (flags & MOVE_MOUNT_T_SYMLINKS)	lflags |= LOOKUP_FOLLOW;
	अगर (flags & MOVE_MOUNT_T_AUTOMOUNTS)	lflags |= LOOKUP_AUTOMOUNT;
	अगर (flags & MOVE_MOUNT_T_EMPTY_PATH)	lflags |= LOOKUP_EMPTY;

	ret = user_path_at(to_dfd, to_pathname, lflags, &to_path);
	अगर (ret < 0)
		जाओ out_from;

	ret = security_move_mount(&from_path, &to_path);
	अगर (ret < 0)
		जाओ out_to;

	ret = करो_move_mount(&from_path, &to_path);

out_to:
	path_put(&to_path);
out_from:
	path_put(&from_path);
	वापस ret;
पूर्ण

/*
 * Return true अगर path is reachable from root
 *
 * namespace_sem or mount_lock is held
 */
bool is_path_reachable(काष्ठा mount *mnt, काष्ठा dentry *dentry,
			 स्थिर काष्ठा path *root)
अणु
	जबतक (&mnt->mnt != root->mnt && mnt_has_parent(mnt)) अणु
		dentry = mnt->mnt_mountpoपूर्णांक;
		mnt = mnt->mnt_parent;
	पूर्ण
	वापस &mnt->mnt == root->mnt && is_subdir(dentry, root->dentry);
पूर्ण

bool path_is_under(स्थिर काष्ठा path *path1, स्थिर काष्ठा path *path2)
अणु
	bool res;
	पढ़ो_seqlock_excl(&mount_lock);
	res = is_path_reachable(real_mount(path1->mnt), path1->dentry, path2);
	पढ़ो_sequnlock_excl(&mount_lock);
	वापस res;
पूर्ण
EXPORT_SYMBOL(path_is_under);

/*
 * pivot_root Semantics:
 * Moves the root file प्रणाली of the current process to the directory put_old,
 * makes new_root as the new root file प्रणाली of the current process, and sets
 * root/cwd of all processes which had them on the current root to new_root.
 *
 * Restrictions:
 * The new_root and put_old must be directories, and  must not be on the
 * same file  प्रणाली as the current process root. The put_old  must  be
 * underneath new_root,  i.e. adding a non-zero number of /.. to the string
 * poपूर्णांकed to by put_old must yield the same directory as new_root. No other
 * file प्रणाली may be mounted on put_old. After all, new_root is a mountpoपूर्णांक.
 *
 * Also, the current root cannot be on the 'rootfs' (initial ramfs) fileप्रणाली.
 * See Documentation/fileप्रणालीs/ramfs-rootfs-initramfs.rst क्रम alternatives
 * in this situation.
 *
 * Notes:
 *  - we करोn't move root/cwd अगर they are not at the root (reason: अगर something
 *    cared enough to change them, it's probably wrong to क्रमce them अन्यथाwhere)
 *  - it's okay to pick a root that isn't the root of a file प्रणाली, e.g.
 *    /nfs/my_root where /nfs is the mount poपूर्णांक. It must be a mountpoपूर्णांक,
 *    though, so you may need to say mount --bind /nfs/my_root /nfs/my_root
 *    first.
 */
SYSCALL_DEFINE2(pivot_root, स्थिर अक्षर __user *, new_root,
		स्थिर अक्षर __user *, put_old)
अणु
	काष्ठा path new, old, root;
	काष्ठा mount *new_mnt, *root_mnt, *old_mnt, *root_parent, *ex_parent;
	काष्ठा mountpoपूर्णांक *old_mp, *root_mp;
	पूर्णांक error;

	अगर (!may_mount())
		वापस -EPERM;

	error = user_path_at(AT_FDCWD, new_root,
			     LOOKUP_FOLLOW | LOOKUP_सूचीECTORY, &new);
	अगर (error)
		जाओ out0;

	error = user_path_at(AT_FDCWD, put_old,
			     LOOKUP_FOLLOW | LOOKUP_सूचीECTORY, &old);
	अगर (error)
		जाओ out1;

	error = security_sb_pivotroot(&old, &new);
	अगर (error)
		जाओ out2;

	get_fs_root(current->fs, &root);
	old_mp = lock_mount(&old);
	error = PTR_ERR(old_mp);
	अगर (IS_ERR(old_mp))
		जाओ out3;

	error = -EINVAL;
	new_mnt = real_mount(new.mnt);
	root_mnt = real_mount(root.mnt);
	old_mnt = real_mount(old.mnt);
	ex_parent = new_mnt->mnt_parent;
	root_parent = root_mnt->mnt_parent;
	अगर (IS_MNT_SHARED(old_mnt) ||
		IS_MNT_SHARED(ex_parent) ||
		IS_MNT_SHARED(root_parent))
		जाओ out4;
	अगर (!check_mnt(root_mnt) || !check_mnt(new_mnt))
		जाओ out4;
	अगर (new_mnt->mnt.mnt_flags & MNT_LOCKED)
		जाओ out4;
	error = -ENOENT;
	अगर (d_unlinked(new.dentry))
		जाओ out4;
	error = -EBUSY;
	अगर (new_mnt == root_mnt || old_mnt == root_mnt)
		जाओ out4; /* loop, on the same file प्रणाली  */
	error = -EINVAL;
	अगर (root.mnt->mnt_root != root.dentry)
		जाओ out4; /* not a mountpoपूर्णांक */
	अगर (!mnt_has_parent(root_mnt))
		जाओ out4; /* not attached */
	अगर (new.mnt->mnt_root != new.dentry)
		जाओ out4; /* not a mountpoपूर्णांक */
	अगर (!mnt_has_parent(new_mnt))
		जाओ out4; /* not attached */
	/* make sure we can reach put_old from new_root */
	अगर (!is_path_reachable(old_mnt, old.dentry, &new))
		जाओ out4;
	/* make certain new is below the root */
	अगर (!is_path_reachable(new_mnt, new.dentry, &root))
		जाओ out4;
	lock_mount_hash();
	umount_mnt(new_mnt);
	root_mp = unhash_mnt(root_mnt);  /* we'll need its mountpoपूर्णांक */
	अगर (root_mnt->mnt.mnt_flags & MNT_LOCKED) अणु
		new_mnt->mnt.mnt_flags |= MNT_LOCKED;
		root_mnt->mnt.mnt_flags &= ~MNT_LOCKED;
	पूर्ण
	/* mount old root on put_old */
	attach_mnt(root_mnt, old_mnt, old_mp);
	/* mount new_root on / */
	attach_mnt(new_mnt, root_parent, root_mp);
	mnt_add_count(root_parent, -1);
	touch_mnt_namespace(current->nsproxy->mnt_ns);
	/* A moved mount should not expire स्वतःmatically */
	list_del_init(&new_mnt->mnt_expire);
	put_mountpoपूर्णांक(root_mp);
	unlock_mount_hash();
	chroot_fs_refs(&root, &new);
	error = 0;
out4:
	unlock_mount(old_mp);
	अगर (!error)
		mntput_no_expire(ex_parent);
out3:
	path_put(&root);
out2:
	path_put(&old);
out1:
	path_put(&new);
out0:
	वापस error;
पूर्ण

अटल अचिन्हित पूर्णांक recalc_flags(काष्ठा mount_kattr *kattr, काष्ठा mount *mnt)
अणु
	अचिन्हित पूर्णांक flags = mnt->mnt.mnt_flags;

	/*  flags to clear */
	flags &= ~kattr->attr_clr;
	/* flags to उठाओ */
	flags |= kattr->attr_set;

	वापस flags;
पूर्ण

अटल पूर्णांक can_idmap_mount(स्थिर काष्ठा mount_kattr *kattr, काष्ठा mount *mnt)
अणु
	काष्ठा vfsmount *m = &mnt->mnt;

	अगर (!kattr->mnt_userns)
		वापस 0;

	/*
	 * Once a mount has been idmapped we करोn't allow it to change its
	 * mapping. It makes things simpler and callers can just create
	 * another bind-mount they can idmap अगर they want to.
	 */
	अगर (mnt_user_ns(m) != &init_user_ns)
		वापस -EPERM;

	/* The underlying fileप्रणाली करोesn't support idmapped mounts yet. */
	अगर (!(m->mnt_sb->s_type->fs_flags & FS_ALLOW_IDMAP))
		वापस -EINVAL;

	/* Don't yet support fileप्रणाली mountable in user namespaces. */
	अगर (m->mnt_sb->s_user_ns != &init_user_ns)
		वापस -EINVAL;

	/* We're not controlling the superblock. */
	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	/* Mount has alपढ़ोy been visible in the fileप्रणाली hierarchy. */
	अगर (!is_anon_ns(mnt->mnt_ns))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा mount *mount_setattr_prepare(काष्ठा mount_kattr *kattr,
					   काष्ठा mount *mnt, पूर्णांक *err)
अणु
	काष्ठा mount *m = mnt, *last = शून्य;

	अगर (!is_mounted(&m->mnt)) अणु
		*err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!(mnt_has_parent(m) ? check_mnt(m) : is_anon_ns(m->mnt_ns))) अणु
		*err = -EINVAL;
		जाओ out;
	पूर्ण

	करो अणु
		अचिन्हित पूर्णांक flags;

		flags = recalc_flags(kattr, m);
		अगर (!can_change_locked_flags(m, flags)) अणु
			*err = -EPERM;
			जाओ out;
		पूर्ण

		*err = can_idmap_mount(kattr, m);
		अगर (*err)
			जाओ out;

		last = m;

		अगर ((kattr->attr_set & MNT_READONLY) &&
		    !(m->mnt.mnt_flags & MNT_READONLY)) अणु
			*err = mnt_hold_ग_लिखोrs(m);
			अगर (*err)
				जाओ out;
		पूर्ण
	पूर्ण जबतक (kattr->recurse && (m = next_mnt(m, mnt)));

out:
	वापस last;
पूर्ण

अटल व्योम करो_idmap_mount(स्थिर काष्ठा mount_kattr *kattr, काष्ठा mount *mnt)
अणु
	काष्ठा user_namespace *mnt_userns;

	अगर (!kattr->mnt_userns)
		वापस;

	mnt_userns = get_user_ns(kattr->mnt_userns);
	/* Pairs with smp_load_acquire() in mnt_user_ns(). */
	smp_store_release(&mnt->mnt.mnt_userns, mnt_userns);
पूर्ण

अटल व्योम mount_setattr_commit(काष्ठा mount_kattr *kattr,
				 काष्ठा mount *mnt, काष्ठा mount *last,
				 पूर्णांक err)
अणु
	काष्ठा mount *m = mnt;

	करो अणु
		अगर (!err) अणु
			अचिन्हित पूर्णांक flags;

			करो_idmap_mount(kattr, m);
			flags = recalc_flags(kattr, m);
			WRITE_ONCE(m->mnt.mnt_flags, flags);
		पूर्ण

		/*
		 * We either set MNT_READONLY above so make it visible
		 * beक्रमe ~MNT_WRITE_HOLD or we failed to recursively
		 * apply mount options.
		 */
		अगर ((kattr->attr_set & MNT_READONLY) &&
		    (m->mnt.mnt_flags & MNT_WRITE_HOLD))
			mnt_unhold_ग_लिखोrs(m);

		अगर (!err && kattr->propagation)
			change_mnt_propagation(m, kattr->propagation);

		/*
		 * On failure, only cleanup until we found the first mount
		 * we failed to handle.
		 */
		अगर (err && m == last)
			अवरोध;
	पूर्ण जबतक (kattr->recurse && (m = next_mnt(m, mnt)));

	अगर (!err)
		touch_mnt_namespace(mnt->mnt_ns);
पूर्ण

अटल पूर्णांक करो_mount_setattr(काष्ठा path *path, काष्ठा mount_kattr *kattr)
अणु
	काष्ठा mount *mnt = real_mount(path->mnt), *last = शून्य;
	पूर्णांक err = 0;

	अगर (path->dentry != mnt->mnt.mnt_root)
		वापस -EINVAL;

	अगर (kattr->propagation) अणु
		/*
		 * Only take namespace_lock() अगर we're actually changing
		 * propagation.
		 */
		namespace_lock();
		अगर (kattr->propagation == MS_SHARED) अणु
			err = invent_group_ids(mnt, kattr->recurse);
			अगर (err) अणु
				namespace_unlock();
				वापस err;
			पूर्ण
		पूर्ण
	पूर्ण

	lock_mount_hash();

	/*
	 * Get the mount tree in a shape where we can change mount
	 * properties without failure.
	 */
	last = mount_setattr_prepare(kattr, mnt, &err);
	अगर (last) /* Commit all changes or revert to the old state. */
		mount_setattr_commit(kattr, mnt, last, err);

	unlock_mount_hash();

	अगर (kattr->propagation) अणु
		namespace_unlock();
		अगर (err)
			cleanup_group_ids(mnt, शून्य);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक build_mount_idmapped(स्थिर काष्ठा mount_attr *attr, माप_प्रकार usize,
				काष्ठा mount_kattr *kattr, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err = 0;
	काष्ठा ns_common *ns;
	काष्ठा user_namespace *mnt_userns;
	काष्ठा file *file;

	अगर (!((attr->attr_set | attr->attr_clr) & MOUNT_ATTR_IDMAP))
		वापस 0;

	/*
	 * We currently करो not support clearing an idmapped mount. If this ever
	 * is a use-हाल we can revisit this but क्रम now let's keep it simple
	 * and not allow it.
	 */
	अगर (attr->attr_clr & MOUNT_ATTR_IDMAP)
		वापस -EINVAL;

	अगर (attr->userns_fd > पूर्णांक_उच्च)
		वापस -EINVAL;

	file = fget(attr->userns_fd);
	अगर (!file)
		वापस -EBADF;

	अगर (!proc_ns_file(file)) अणु
		err = -EINVAL;
		जाओ out_fput;
	पूर्ण

	ns = get_proc_ns(file_inode(file));
	अगर (ns->ops->type != CLONE_NEWUSER) अणु
		err = -EINVAL;
		जाओ out_fput;
	पूर्ण

	/*
	 * The init_user_ns is used to indicate that a vfsmount is not idmapped.
	 * This is simpler than just having to treat शून्य as unmapped. Users
	 * wanting to idmap a mount to init_user_ns can just use a namespace
	 * with an identity mapping.
	 */
	mnt_userns = container_of(ns, काष्ठा user_namespace, ns);
	अगर (mnt_userns == &init_user_ns) अणु
		err = -EPERM;
		जाओ out_fput;
	पूर्ण
	kattr->mnt_userns = get_user_ns(mnt_userns);

out_fput:
	fput(file);
	वापस err;
पूर्ण

अटल पूर्णांक build_mount_kattr(स्थिर काष्ठा mount_attr *attr, माप_प्रकार usize,
			     काष्ठा mount_kattr *kattr, अचिन्हित पूर्णांक flags)
अणु
	अचिन्हित पूर्णांक lookup_flags = LOOKUP_AUTOMOUNT | LOOKUP_FOLLOW;

	अगर (flags & AT_NO_AUTOMOUNT)
		lookup_flags &= ~LOOKUP_AUTOMOUNT;
	अगर (flags & AT_SYMLINK_NOFOLLOW)
		lookup_flags &= ~LOOKUP_FOLLOW;
	अगर (flags & AT_EMPTY_PATH)
		lookup_flags |= LOOKUP_EMPTY;

	*kattr = (काष्ठा mount_kattr) अणु
		.lookup_flags	= lookup_flags,
		.recurse	= !!(flags & AT_RECURSIVE),
	पूर्ण;

	अगर (attr->propagation & ~MOUNT_SETATTR_PROPAGATION_FLAGS)
		वापस -EINVAL;
	अगर (hweight32(attr->propagation & MOUNT_SETATTR_PROPAGATION_FLAGS) > 1)
		वापस -EINVAL;
	kattr->propagation = attr->propagation;

	अगर ((attr->attr_set | attr->attr_clr) & ~MOUNT_SETATTR_VALID_FLAGS)
		वापस -EINVAL;

	kattr->attr_set = attr_flags_to_mnt_flags(attr->attr_set);
	kattr->attr_clr = attr_flags_to_mnt_flags(attr->attr_clr);

	/*
	 * Since the MOUNT_ATTR_<aसमय> values are an क्रमागत, not a biपंचांगap,
	 * users wanting to transition to a dअगरferent aसमय setting cannot
	 * simply specअगरy the aसमय setting in @attr_set, but must also
	 * specअगरy MOUNT_ATTR__ATIME in the @attr_clr field.
	 * So ensure that MOUNT_ATTR__ATIME can't be partially set in
	 * @attr_clr and that @attr_set can't have any aसमय bits set अगर
	 * MOUNT_ATTR__ATIME isn't set in @attr_clr.
	 */
	अगर (attr->attr_clr & MOUNT_ATTR__ATIME) अणु
		अगर ((attr->attr_clr & MOUNT_ATTR__ATIME) != MOUNT_ATTR__ATIME)
			वापस -EINVAL;

		/*
		 * Clear all previous समय settings as they are mutually
		 * exclusive.
		 */
		kattr->attr_clr |= MNT_RELATIME | MNT_NOATIME;
		चयन (attr->attr_set & MOUNT_ATTR__ATIME) अणु
		हाल MOUNT_ATTR_RELATIME:
			kattr->attr_set |= MNT_RELATIME;
			अवरोध;
		हाल MOUNT_ATTR_NOATIME:
			kattr->attr_set |= MNT_NOATIME;
			अवरोध;
		हाल MOUNT_ATTR_STRICTATIME:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (attr->attr_set & MOUNT_ATTR__ATIME)
			वापस -EINVAL;
	पूर्ण

	वापस build_mount_idmapped(attr, usize, kattr, flags);
पूर्ण

अटल व्योम finish_mount_kattr(काष्ठा mount_kattr *kattr)
अणु
	put_user_ns(kattr->mnt_userns);
	kattr->mnt_userns = शून्य;
पूर्ण

SYSCALL_DEFINE5(mount_setattr, पूर्णांक, dfd, स्थिर अक्षर __user *, path,
		अचिन्हित पूर्णांक, flags, काष्ठा mount_attr __user *, uattr,
		माप_प्रकार, usize)
अणु
	पूर्णांक err;
	काष्ठा path target;
	काष्ठा mount_attr attr;
	काष्ठा mount_kattr kattr;

	BUILD_BUG_ON(माप(काष्ठा mount_attr) != MOUNT_ATTR_SIZE_VER0);

	अगर (flags & ~(AT_EMPTY_PATH |
		      AT_RECURSIVE |
		      AT_SYMLINK_NOFOLLOW |
		      AT_NO_AUTOMOUNT))
		वापस -EINVAL;

	अगर (unlikely(usize > PAGE_SIZE))
		वापस -E2BIG;
	अगर (unlikely(usize < MOUNT_ATTR_SIZE_VER0))
		वापस -EINVAL;

	अगर (!may_mount())
		वापस -EPERM;

	err = copy_काष्ठा_from_user(&attr, माप(attr), uattr, usize);
	अगर (err)
		वापस err;

	/* Don't bother walking through the mounts अगर this is a nop. */
	अगर (attr.attr_set == 0 &&
	    attr.attr_clr == 0 &&
	    attr.propagation == 0)
		वापस 0;

	err = build_mount_kattr(&attr, usize, &kattr, flags);
	अगर (err)
		वापस err;

	err = user_path_at(dfd, path, kattr.lookup_flags, &target);
	अगर (err)
		वापस err;

	err = करो_mount_setattr(&target, &kattr);
	finish_mount_kattr(&kattr);
	path_put(&target);
	वापस err;
पूर्ण

अटल व्योम __init init_mount_tree(व्योम)
अणु
	काष्ठा vfsmount *mnt;
	काष्ठा mount *m;
	काष्ठा mnt_namespace *ns;
	काष्ठा path root;

	mnt = vfs_kern_mount(&rootfs_fs_type, 0, "rootfs", शून्य);
	अगर (IS_ERR(mnt))
		panic("Can't create rootfs");

	ns = alloc_mnt_ns(&init_user_ns, false);
	अगर (IS_ERR(ns))
		panic("Can't allocate initial namespace");
	m = real_mount(mnt);
	m->mnt_ns = ns;
	ns->root = m;
	ns->mounts = 1;
	list_add(&m->mnt_list, &ns->list);
	init_task.nsproxy->mnt_ns = ns;
	get_mnt_ns(ns);

	root.mnt = mnt;
	root.dentry = mnt->mnt_root;
	mnt->mnt_flags |= MNT_LOCKED;

	set_fs_pwd(current->fs, &root);
	set_fs_root(current->fs, &root);
पूर्ण

व्योम __init mnt_init(व्योम)
अणु
	पूर्णांक err;

	mnt_cache = kmem_cache_create("mnt_cache", माप(काष्ठा mount),
			0, SLAB_HWCACHE_ALIGN | SLAB_PANIC, शून्य);

	mount_hashtable = alloc_large_प्रणाली_hash("Mount-cache",
				माप(काष्ठा hlist_head),
				mhash_entries, 19,
				HASH_ZERO,
				&m_hash_shअगरt, &m_hash_mask, 0, 0);
	mountpoपूर्णांक_hashtable = alloc_large_प्रणाली_hash("Mountpoint-cache",
				माप(काष्ठा hlist_head),
				mphash_entries, 19,
				HASH_ZERO,
				&mp_hash_shअगरt, &mp_hash_mask, 0, 0);

	अगर (!mount_hashtable || !mountpoपूर्णांक_hashtable)
		panic("Failed to allocate mount hash table\n");

	kernfs_init();

	err = sysfs_init();
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: sysfs_init error: %d\n",
			__func__, err);
	fs_kobj = kobject_create_and_add("fs", शून्य);
	अगर (!fs_kobj)
		prपूर्णांकk(KERN_WARNING "%s: kobj create error\n", __func__);
	shmem_init();
	init_rootfs();
	init_mount_tree();
पूर्ण

व्योम put_mnt_ns(काष्ठा mnt_namespace *ns)
अणु
	अगर (!refcount_dec_and_test(&ns->ns.count))
		वापस;
	drop_collected_mounts(&ns->root->mnt);
	मुक्त_mnt_ns(ns);
पूर्ण

काष्ठा vfsmount *kern_mount(काष्ठा file_प्रणाली_type *type)
अणु
	काष्ठा vfsmount *mnt;
	mnt = vfs_kern_mount(type, SB_KERNMOUNT, type->name, शून्य);
	अगर (!IS_ERR(mnt)) अणु
		/*
		 * it is a दीर्घterm mount, करोn't release mnt until
		 * we unmount beक्रमe file sys is unरेजिस्टरed
		*/
		real_mount(mnt)->mnt_ns = MNT_NS_INTERNAL;
	पूर्ण
	वापस mnt;
पूर्ण
EXPORT_SYMBOL_GPL(kern_mount);

व्योम kern_unmount(काष्ठा vfsmount *mnt)
अणु
	/* release दीर्घ term mount so mount poपूर्णांक can be released */
	अगर (!IS_ERR_OR_शून्य(mnt)) अणु
		real_mount(mnt)->mnt_ns = शून्य;
		synchronize_rcu();	/* yecchhh... */
		mntput(mnt);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(kern_unmount);

व्योम kern_unmount_array(काष्ठा vfsmount *mnt[], अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		अगर (mnt[i])
			real_mount(mnt[i])->mnt_ns = शून्य;
	synchronize_rcu_expedited();
	क्रम (i = 0; i < num; i++)
		mntput(mnt[i]);
पूर्ण
EXPORT_SYMBOL(kern_unmount_array);

bool our_mnt(काष्ठा vfsmount *mnt)
अणु
	वापस check_mnt(real_mount(mnt));
पूर्ण

bool current_chrooted(व्योम)
अणु
	/* Does the current process have a non-standard root */
	काष्ठा path ns_root;
	काष्ठा path fs_root;
	bool chrooted;

	/* Find the namespace root */
	ns_root.mnt = &current->nsproxy->mnt_ns->root->mnt;
	ns_root.dentry = ns_root.mnt->mnt_root;
	path_get(&ns_root);
	जबतक (d_mountpoपूर्णांक(ns_root.dentry) && follow_करोwn_one(&ns_root))
		;

	get_fs_root(current->fs, &fs_root);

	chrooted = !path_equal(&fs_root, &ns_root);

	path_put(&fs_root);
	path_put(&ns_root);

	वापस chrooted;
पूर्ण

अटल bool mnt_alपढ़ोy_visible(काष्ठा mnt_namespace *ns,
				स्थिर काष्ठा super_block *sb,
				पूर्णांक *new_mnt_flags)
अणु
	पूर्णांक new_flags = *new_mnt_flags;
	काष्ठा mount *mnt;
	bool visible = false;

	करोwn_पढ़ो(&namespace_sem);
	lock_ns_list(ns);
	list_क्रम_each_entry(mnt, &ns->list, mnt_list) अणु
		काष्ठा mount *child;
		पूर्णांक mnt_flags;

		अगर (mnt_is_cursor(mnt))
			जारी;

		अगर (mnt->mnt.mnt_sb->s_type != sb->s_type)
			जारी;

		/* This mount is not fully visible अगर it's root directory
		 * is not the root directory of the fileप्रणाली.
		 */
		अगर (mnt->mnt.mnt_root != mnt->mnt.mnt_sb->s_root)
			जारी;

		/* A local view of the mount flags */
		mnt_flags = mnt->mnt.mnt_flags;

		/* Don't miss पढ़ोonly hidden in the superblock flags */
		अगर (sb_rकरोnly(mnt->mnt.mnt_sb))
			mnt_flags |= MNT_LOCK_READONLY;

		/* Verअगरy the mount flags are equal to or more permissive
		 * than the proposed new mount.
		 */
		अगर ((mnt_flags & MNT_LOCK_READONLY) &&
		    !(new_flags & MNT_READONLY))
			जारी;
		अगर ((mnt_flags & MNT_LOCK_ATIME) &&
		    ((mnt_flags & MNT_ATIME_MASK) != (new_flags & MNT_ATIME_MASK)))
			जारी;

		/* This mount is not fully visible अगर there are any
		 * locked child mounts that cover anything except क्रम
		 * empty directories.
		 */
		list_क्रम_each_entry(child, &mnt->mnt_mounts, mnt_child) अणु
			काष्ठा inode *inode = child->mnt_mountpoपूर्णांक->d_inode;
			/* Only worry about locked mounts */
			अगर (!(child->mnt.mnt_flags & MNT_LOCKED))
				जारी;
			/* Is the directory permanetly empty? */
			अगर (!is_empty_dir_inode(inode))
				जाओ next;
		पूर्ण
		/* Preserve the locked attributes */
		*new_mnt_flags |= mnt_flags & (MNT_LOCK_READONLY | \
					       MNT_LOCK_ATIME);
		visible = true;
		जाओ found;
	next:	;
	पूर्ण
found:
	unlock_ns_list(ns);
	up_पढ़ो(&namespace_sem);
	वापस visible;
पूर्ण

अटल bool mount_too_revealing(स्थिर काष्ठा super_block *sb, पूर्णांक *new_mnt_flags)
अणु
	स्थिर अचिन्हित दीर्घ required_अगरlags = SB_I_NOEXEC | SB_I_NODEV;
	काष्ठा mnt_namespace *ns = current->nsproxy->mnt_ns;
	अचिन्हित दीर्घ s_अगरlags;

	अगर (ns->user_ns == &init_user_ns)
		वापस false;

	/* Can this fileप्रणाली be too revealing? */
	s_अगरlags = sb->s_अगरlags;
	अगर (!(s_अगरlags & SB_I_USERNS_VISIBLE))
		वापस false;

	अगर ((s_अगरlags & required_अगरlags) != required_अगरlags) अणु
		WARN_ONCE(1, "Expected s_iflags to contain 0x%lx\n",
			  required_अगरlags);
		वापस true;
	पूर्ण

	वापस !mnt_alपढ़ोy_visible(ns, sb, new_mnt_flags);
पूर्ण

bool mnt_may_suid(काष्ठा vfsmount *mnt)
अणु
	/*
	 * Foreign mounts (accessed via fस_बदलो or through /proc
	 * symlinks) are always treated as अगर they are nosuid.  This
	 * prevents namespaces from trusting potentially unsafe
	 * suid/sgid bits, file caps, or security labels that originate
	 * in other namespaces.
	 */
	वापस !(mnt->mnt_flags & MNT_NOSUID) && check_mnt(real_mount(mnt)) &&
	       current_in_userns(mnt->mnt_sb->s_user_ns);
पूर्ण

अटल काष्ठा ns_common *mntns_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा ns_common *ns = शून्य;
	काष्ठा nsproxy *nsproxy;

	task_lock(task);
	nsproxy = task->nsproxy;
	अगर (nsproxy) अणु
		ns = &nsproxy->mnt_ns->ns;
		get_mnt_ns(to_mnt_ns(ns));
	पूर्ण
	task_unlock(task);

	वापस ns;
पूर्ण

अटल व्योम mntns_put(काष्ठा ns_common *ns)
अणु
	put_mnt_ns(to_mnt_ns(ns));
पूर्ण

अटल पूर्णांक mntns_install(काष्ठा nsset *nsset, काष्ठा ns_common *ns)
अणु
	काष्ठा nsproxy *nsproxy = nsset->nsproxy;
	काष्ठा fs_काष्ठा *fs = nsset->fs;
	काष्ठा mnt_namespace *mnt_ns = to_mnt_ns(ns), *old_mnt_ns;
	काष्ठा user_namespace *user_ns = nsset->cred->user_ns;
	काष्ठा path root;
	पूर्णांक err;

	अगर (!ns_capable(mnt_ns->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(user_ns, CAP_SYS_CHROOT) ||
	    !ns_capable(user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (is_anon_ns(mnt_ns))
		वापस -EINVAL;

	अगर (fs->users != 1)
		वापस -EINVAL;

	get_mnt_ns(mnt_ns);
	old_mnt_ns = nsproxy->mnt_ns;
	nsproxy->mnt_ns = mnt_ns;

	/* Find the root */
	err = vfs_path_lookup(mnt_ns->root->mnt.mnt_root, &mnt_ns->root->mnt,
				"/", LOOKUP_DOWN, &root);
	अगर (err) अणु
		/* revert to old namespace */
		nsproxy->mnt_ns = old_mnt_ns;
		put_mnt_ns(mnt_ns);
		वापस err;
	पूर्ण

	put_mnt_ns(old_mnt_ns);

	/* Update the pwd and root */
	set_fs_pwd(fs, &root);
	set_fs_root(fs, &root);

	path_put(&root);
	वापस 0;
पूर्ण

अटल काष्ठा user_namespace *mntns_owner(काष्ठा ns_common *ns)
अणु
	वापस to_mnt_ns(ns)->user_ns;
पूर्ण

स्थिर काष्ठा proc_ns_operations mntns_operations = अणु
	.name		= "mnt",
	.type		= CLONE_NEWNS,
	.get		= mntns_get,
	.put		= mntns_put,
	.install	= mntns_install,
	.owner		= mntns_owner,
पूर्ण;
