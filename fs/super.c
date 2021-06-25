<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/super.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  super.c contains code to handle: - mount काष्ठाures
 *                                   - super-block tables
 *                                   - fileप्रणाली drivers list
 *                                   - mount प्रणाली call
 *                                   - umount प्रणाली call
 *                                   - ustat प्रणाली call
 *
 * GK 2/5/95  -  Changed to support mounting the root fs via NFS
 *
 *  Added kerneld support: Jacques Gelinas and Bjorn Ekwall
 *  Added change_root: Werner Almesberger & Hans Lermen, Feb '96
 *  Added options to /proc/mounts:
 *    Torbjथघrn Lindh (torbjorn.lindh@gopta.se), April 14, 1996.
 *  Added devfs support: Riअक्षरd Gooch <rgooch@atnf.csiro.au>, 13-JAN-1998
 *  Heavily rewritten क्रम 'one fs - one tree' dcache architecture. AV, Mar 2000
 */

#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/mount.h>
#समावेश <linux/security.h>
#समावेश <linux/ग_लिखोback.h>		/* क्रम the emergency remount stuff */
#समावेश <linux/idr.h>
#समावेश <linux/mutex.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/rculist_bl.h>
#समावेश <linux/cleancache.h>
#समावेश <linux/fscrypt.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/fs_context.h>
#समावेश <uapi/linux/mount.h>
#समावेश "internal.h"

अटल पूर्णांक thaw_super_locked(काष्ठा super_block *sb);

अटल LIST_HEAD(super_blocks);
अटल DEFINE_SPINLOCK(sb_lock);

अटल अक्षर *sb_ग_लिखोrs_name[SB_FREEZE_LEVELS] = अणु
	"sb_writers",
	"sb_pagefaults",
	"sb_internal",
पूर्ण;

/*
 * One thing we have to be careful of with a per-sb shrinker is that we करोn't
 * drop the last active reference to the superblock from within the shrinker.
 * If that happens we could trigger unरेजिस्टरing the shrinker from within the
 * shrinker path and that leads to deadlock on the shrinker_rwsem. Hence we
 * take a passive reference to the superblock to aव्योम this from occurring.
 */
अटल अचिन्हित दीर्घ super_cache_scan(काष्ठा shrinker *shrink,
				      काष्ठा shrink_control *sc)
अणु
	काष्ठा super_block *sb;
	दीर्घ	fs_objects = 0;
	दीर्घ	total_objects;
	दीर्घ	मुक्तd = 0;
	दीर्घ	dentries;
	दीर्घ	inodes;

	sb = container_of(shrink, काष्ठा super_block, s_shrink);

	/*
	 * Deadlock aव्योमance.  We may hold various FS locks, and we करोn't want
	 * to recurse पूर्णांकo the FS that called us in clear_inode() and मित्रs..
	 */
	अगर (!(sc->gfp_mask & __GFP_FS))
		वापस SHRINK_STOP;

	अगर (!trylock_super(sb))
		वापस SHRINK_STOP;

	अगर (sb->s_op->nr_cached_objects)
		fs_objects = sb->s_op->nr_cached_objects(sb, sc);

	inodes = list_lru_shrink_count(&sb->s_inode_lru, sc);
	dentries = list_lru_shrink_count(&sb->s_dentry_lru, sc);
	total_objects = dentries + inodes + fs_objects + 1;
	अगर (!total_objects)
		total_objects = 1;

	/* proportion the scan between the caches */
	dentries = mult_frac(sc->nr_to_scan, dentries, total_objects);
	inodes = mult_frac(sc->nr_to_scan, inodes, total_objects);
	fs_objects = mult_frac(sc->nr_to_scan, fs_objects, total_objects);

	/*
	 * prune the dcache first as the icache is pinned by it, then
	 * prune the icache, followed by the fileप्रणाली specअगरic caches
	 *
	 * Ensure that we always scan at least one object - memcg kmem
	 * accounting uses this to fully empty the caches.
	 */
	sc->nr_to_scan = dentries + 1;
	मुक्तd = prune_dcache_sb(sb, sc);
	sc->nr_to_scan = inodes + 1;
	मुक्तd += prune_icache_sb(sb, sc);

	अगर (fs_objects) अणु
		sc->nr_to_scan = fs_objects + 1;
		मुक्तd += sb->s_op->मुक्त_cached_objects(sb, sc);
	पूर्ण

	up_पढ़ो(&sb->s_umount);
	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ super_cache_count(काष्ठा shrinker *shrink,
				       काष्ठा shrink_control *sc)
अणु
	काष्ठा super_block *sb;
	दीर्घ	total_objects = 0;

	sb = container_of(shrink, काष्ठा super_block, s_shrink);

	/*
	 * We करोn't call trylock_super() here as it is a scalability bottleneck,
	 * so we're exposed to partial setup state. The shrinker rwsem करोes not
	 * protect fileप्रणाली operations backing list_lru_shrink_count() or
	 * s_op->nr_cached_objects(). Counts can change between
	 * super_cache_count and super_cache_scan, so we really करोn't need locks
	 * here.
	 *
	 * However, अगर we are currently mounting the superblock, the underlying
	 * fileप्रणाली might be in a state of partial स्थिरruction and hence it
	 * is dangerous to access it.  trylock_super() uses a SB_BORN check to
	 * aव्योम this situation, so करो the same here. The memory barrier is
	 * matched with the one in mount_fs() as we करोn't hold locks here.
	 */
	अगर (!(sb->s_flags & SB_BORN))
		वापस 0;
	smp_rmb();

	अगर (sb->s_op && sb->s_op->nr_cached_objects)
		total_objects = sb->s_op->nr_cached_objects(sb, sc);

	total_objects += list_lru_shrink_count(&sb->s_dentry_lru, sc);
	total_objects += list_lru_shrink_count(&sb->s_inode_lru, sc);

	अगर (!total_objects)
		वापस SHRINK_EMPTY;

	total_objects = vfs_pressure_ratio(total_objects);
	वापस total_objects;
पूर्ण

अटल व्योम destroy_super_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा super_block *s = container_of(work, काष्ठा super_block,
							destroy_work);
	पूर्णांक i;

	क्रम (i = 0; i < SB_FREEZE_LEVELS; i++)
		percpu_मुक्त_rwsem(&s->s_ग_लिखोrs.rw_sem[i]);
	kमुक्त(s);
पूर्ण

अटल व्योम destroy_super_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा super_block *s = container_of(head, काष्ठा super_block, rcu);
	INIT_WORK(&s->destroy_work, destroy_super_work);
	schedule_work(&s->destroy_work);
पूर्ण

/* Free a superblock that has never been seen by anyone */
अटल व्योम destroy_unused_super(काष्ठा super_block *s)
अणु
	अगर (!s)
		वापस;
	up_ग_लिखो(&s->s_umount);
	list_lru_destroy(&s->s_dentry_lru);
	list_lru_destroy(&s->s_inode_lru);
	security_sb_मुक्त(s);
	put_user_ns(s->s_user_ns);
	kमुक्त(s->s_subtype);
	मुक्त_pपुनः_स्मृतिed_shrinker(&s->s_shrink);
	/* no delays needed */
	destroy_super_work(&s->destroy_work);
पूर्ण

/**
 *	alloc_super	-	create new superblock
 *	@type:	fileप्रणाली type superblock should beदीर्घ to
 *	@flags: the mount flags
 *	@user_ns: User namespace क्रम the super_block
 *
 *	Allocates and initializes a new &काष्ठा super_block.  alloc_super()
 *	वापसs a poपूर्णांकer new superblock or %शून्य अगर allocation had failed.
 */
अटल काष्ठा super_block *alloc_super(काष्ठा file_प्रणाली_type *type, पूर्णांक flags,
				       काष्ठा user_namespace *user_ns)
अणु
	काष्ठा super_block *s = kzalloc(माप(काष्ठा super_block),  GFP_USER);
	अटल स्थिर काष्ठा super_operations शेष_op;
	पूर्णांक i;

	अगर (!s)
		वापस शून्य;

	INIT_LIST_HEAD(&s->s_mounts);
	s->s_user_ns = get_user_ns(user_ns);
	init_rwsem(&s->s_umount);
	lockdep_set_class(&s->s_umount, &type->s_umount_key);
	/*
	 * sget() can have s_umount recursion.
	 *
	 * When it cannot find a suitable sb, it allocates a new
	 * one (this one), and tries again to find a suitable old
	 * one.
	 *
	 * In हाल that succeeds, it will acquire the s_umount
	 * lock of the old one. Since these are clearly distrinct
	 * locks, and this object isn't exposed yet, there's no
	 * risk of deadlocks.
	 *
	 * Annotate this by putting this lock in a dअगरferent
	 * subclass.
	 */
	करोwn_ग_लिखो_nested(&s->s_umount, SINGLE_DEPTH_NESTING);

	अगर (security_sb_alloc(s))
		जाओ fail;

	क्रम (i = 0; i < SB_FREEZE_LEVELS; i++) अणु
		अगर (__percpu_init_rwsem(&s->s_ग_लिखोrs.rw_sem[i],
					sb_ग_लिखोrs_name[i],
					&type->s_ग_लिखोrs_key[i]))
			जाओ fail;
	पूर्ण
	init_रुकोqueue_head(&s->s_ग_लिखोrs.रुको_unfrozen);
	s->s_bdi = &noop_backing_dev_info;
	s->s_flags = flags;
	अगर (s->s_user_ns != &init_user_ns)
		s->s_अगरlags |= SB_I_NODEV;
	INIT_HLIST_NODE(&s->s_instances);
	INIT_HLIST_BL_HEAD(&s->s_roots);
	mutex_init(&s->s_sync_lock);
	INIT_LIST_HEAD(&s->s_inodes);
	spin_lock_init(&s->s_inode_list_lock);
	INIT_LIST_HEAD(&s->s_inodes_wb);
	spin_lock_init(&s->s_inode_wblist_lock);

	s->s_count = 1;
	atomic_set(&s->s_active, 1);
	mutex_init(&s->s_vfs_नाम_mutex);
	lockdep_set_class(&s->s_vfs_नाम_mutex, &type->s_vfs_नाम_key);
	init_rwsem(&s->s_dquot.dqio_sem);
	s->s_maxbytes = MAX_NON_LFS;
	s->s_op = &शेष_op;
	s->s_समय_gran = 1000000000;
	s->s_समय_min = TIME64_MIN;
	s->s_समय_max = TIME64_MAX;
	s->cleancache_poolid = CLEANCACHE_NO_POOL;

	s->s_shrink.seeks = DEFAULT_SEEKS;
	s->s_shrink.scan_objects = super_cache_scan;
	s->s_shrink.count_objects = super_cache_count;
	s->s_shrink.batch = 1024;
	s->s_shrink.flags = SHRINKER_NUMA_AWARE | SHRINKER_MEMCG_AWARE;
	अगर (pपुनः_स्मृति_shrinker(&s->s_shrink))
		जाओ fail;
	अगर (list_lru_init_memcg(&s->s_dentry_lru, &s->s_shrink))
		जाओ fail;
	अगर (list_lru_init_memcg(&s->s_inode_lru, &s->s_shrink))
		जाओ fail;
	वापस s;

fail:
	destroy_unused_super(s);
	वापस शून्य;
पूर्ण

/* Superblock refcounting  */

/*
 * Drop a superblock's refcount.  The caller must hold sb_lock.
 */
अटल व्योम __put_super(काष्ठा super_block *s)
अणु
	अगर (!--s->s_count) अणु
		list_del_init(&s->s_list);
		WARN_ON(s->s_dentry_lru.node);
		WARN_ON(s->s_inode_lru.node);
		WARN_ON(!list_empty(&s->s_mounts));
		security_sb_मुक्त(s);
		fscrypt_sb_मुक्त(s);
		put_user_ns(s->s_user_ns);
		kमुक्त(s->s_subtype);
		call_rcu(&s->rcu, destroy_super_rcu);
	पूर्ण
पूर्ण

/**
 *	put_super	-	drop a temporary reference to superblock
 *	@sb: superblock in question
 *
 *	Drops a temporary reference, मुक्तs superblock अगर there's no
 *	references left.
 */
व्योम put_super(काष्ठा super_block *sb)
अणु
	spin_lock(&sb_lock);
	__put_super(sb);
	spin_unlock(&sb_lock);
पूर्ण


/**
 *	deactivate_locked_super	-	drop an active reference to superblock
 *	@s: superblock to deactivate
 *
 *	Drops an active reference to superblock, converting it पूर्णांकo a temporary
 *	one अगर there is no other active references left.  In that हाल we
 *	tell fs driver to shut it करोwn and drop the temporary reference we
 *	had just acquired.
 *
 *	Caller holds exclusive lock on superblock; that lock is released.
 */
व्योम deactivate_locked_super(काष्ठा super_block *s)
अणु
	काष्ठा file_प्रणाली_type *fs = s->s_type;
	अगर (atomic_dec_and_test(&s->s_active)) अणु
		cleancache_invalidate_fs(s);
		unरेजिस्टर_shrinker(&s->s_shrink);
		fs->समाप्त_sb(s);

		/*
		 * Since list_lru_destroy() may sleep, we cannot call it from
		 * put_super(), where we hold the sb_lock. Thereक्रमe we destroy
		 * the lru lists right now.
		 */
		list_lru_destroy(&s->s_dentry_lru);
		list_lru_destroy(&s->s_inode_lru);

		put_fileप्रणाली(fs);
		put_super(s);
	पूर्ण अन्यथा अणु
		up_ग_लिखो(&s->s_umount);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(deactivate_locked_super);

/**
 *	deactivate_super	-	drop an active reference to superblock
 *	@s: superblock to deactivate
 *
 *	Variant of deactivate_locked_super(), except that superblock is *not*
 *	locked by caller.  If we are going to drop the final active reference,
 *	lock will be acquired prior to that.
 */
व्योम deactivate_super(काष्ठा super_block *s)
अणु
	अगर (!atomic_add_unless(&s->s_active, -1, 1)) अणु
		करोwn_ग_लिखो(&s->s_umount);
		deactivate_locked_super(s);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(deactivate_super);

/**
 *	grab_super - acquire an active reference
 *	@s: reference we are trying to make active
 *
 *	Tries to acquire an active reference.  grab_super() is used when we
 * 	had just found a superblock in super_blocks or fs_type->fs_supers
 *	and want to turn it पूर्णांकo a full-blown active reference.  grab_super()
 *	is called with sb_lock held and drops it.  Returns 1 in हाल of
 *	success, 0 अगर we had failed (superblock contents was alपढ़ोy dead or
 *	dying when grab_super() had been called).  Note that this is only
 *	called क्रम superblocks not in runकरोwn mode (== ones still on ->fs_supers
 *	of their type), so increment of ->s_count is OK here.
 */
अटल पूर्णांक grab_super(काष्ठा super_block *s) __releases(sb_lock)
अणु
	s->s_count++;
	spin_unlock(&sb_lock);
	करोwn_ग_लिखो(&s->s_umount);
	अगर ((s->s_flags & SB_BORN) && atomic_inc_not_zero(&s->s_active)) अणु
		put_super(s);
		वापस 1;
	पूर्ण
	up_ग_लिखो(&s->s_umount);
	put_super(s);
	वापस 0;
पूर्ण

/*
 *	trylock_super - try to grab ->s_umount shared
 *	@sb: reference we are trying to grab
 *
 *	Try to prevent fs shutकरोwn.  This is used in places where we
 *	cannot take an active reference but we need to ensure that the
 *	fileप्रणाली is not shut करोwn जबतक we are working on it. It वापसs
 *	false अगर we cannot acquire s_umount or अगर we lose the race and
 *	fileप्रणाली alपढ़ोy got पूर्णांकo shutकरोwn, and वापसs true with the s_umount
 *	lock held in पढ़ो mode in हाल of success. On successful वापस,
 *	the caller must drop the s_umount lock when करोne.
 *
 *	Note that unlike get_super() et.al. this one करोes *not* bump ->s_count.
 *	The reason why it's safe is that we are OK with करोing trylock instead
 *	of करोwn_पढ़ो().  There's a couple of places that are OK with that, but
 *	it's very much not a general-purpose पूर्णांकerface.
 */
bool trylock_super(काष्ठा super_block *sb)
अणु
	अगर (करोwn_पढ़ो_trylock(&sb->s_umount)) अणु
		अगर (!hlist_unhashed(&sb->s_instances) &&
		    sb->s_root && (sb->s_flags & SB_BORN))
			वापस true;
		up_पढ़ो(&sb->s_umount);
	पूर्ण

	वापस false;
पूर्ण

/**
 *	generic_shutकरोwn_super	-	common helper क्रम ->समाप्त_sb()
 *	@sb: superblock to समाप्त
 *
 *	generic_shutकरोwn_super() करोes all fs-independent work on superblock
 *	shutकरोwn.  Typical ->समाप्त_sb() should pick all fs-specअगरic objects
 *	that need deकाष्ठाion out of superblock, call generic_shutकरोwn_super()
 *	and release aक्रमementioned objects.  Note: dentries and inodes _are_
 *	taken care of and करो not need specअगरic handling.
 *
 *	Upon calling this function, the fileप्रणाली may no दीर्घer alter or
 *	rearrange the set of dentries beदीर्घing to this super_block, nor may it
 *	change the attachments of dentries to inodes.
 */
व्योम generic_shutकरोwn_super(काष्ठा super_block *sb)
अणु
	स्थिर काष्ठा super_operations *sop = sb->s_op;

	अगर (sb->s_root) अणु
		shrink_dcache_क्रम_umount(sb);
		sync_fileप्रणाली(sb);
		sb->s_flags &= ~SB_ACTIVE;

		cgroup_ग_लिखोback_umount();

		/* evict all inodes with zero refcount */
		evict_inodes(sb);
		/* only nonzero refcount inodes can have marks */
		fsnotअगरy_sb_delete(sb);
		security_sb_delete(sb);

		अगर (sb->s_dio_करोne_wq) अणु
			destroy_workqueue(sb->s_dio_करोne_wq);
			sb->s_dio_करोne_wq = शून्य;
		पूर्ण

		अगर (sop->put_super)
			sop->put_super(sb);

		अगर (!list_empty(&sb->s_inodes)) अणु
			prपूर्णांकk("VFS: Busy inodes after unmount of %s. "
			   "Self-destruct in 5 seconds.  Have a nice day...\n",
			   sb->s_id);
		पूर्ण
	पूर्ण
	spin_lock(&sb_lock);
	/* should be initialized क्रम __put_super_and_need_restart() */
	hlist_del_init(&sb->s_instances);
	spin_unlock(&sb_lock);
	up_ग_लिखो(&sb->s_umount);
	अगर (sb->s_bdi != &noop_backing_dev_info) अणु
		bdi_put(sb->s_bdi);
		sb->s_bdi = &noop_backing_dev_info;
	पूर्ण
पूर्ण

EXPORT_SYMBOL(generic_shutकरोwn_super);

bool mount_capable(काष्ठा fs_context *fc)
अणु
	अगर (!(fc->fs_type->fs_flags & FS_USERNS_MOUNT))
		वापस capable(CAP_SYS_ADMIN);
	अन्यथा
		वापस ns_capable(fc->user_ns, CAP_SYS_ADMIN);
पूर्ण

/**
 * sget_fc - Find or create a superblock
 * @fc:	Fileप्रणाली context.
 * @test: Comparison callback
 * @set: Setup callback
 *
 * Find or create a superblock using the parameters stored in the fileप्रणाली
 * context and the two callback functions.
 *
 * If an extant superblock is matched, then that will be वापसed with an
 * elevated reference count that the caller must transfer or discard.
 *
 * If no match is made, a new superblock will be allocated and basic
 * initialisation will be perक्रमmed (s_type, s_fs_info and s_id will be set and
 * the set() callback will be invoked), the superblock will be published and it
 * will be वापसed in a partially स्थिरructed state with SB_BORN and SB_ACTIVE
 * as yet unset.
 */
काष्ठा super_block *sget_fc(काष्ठा fs_context *fc,
			    पूर्णांक (*test)(काष्ठा super_block *, काष्ठा fs_context *),
			    पूर्णांक (*set)(काष्ठा super_block *, काष्ठा fs_context *))
अणु
	काष्ठा super_block *s = शून्य;
	काष्ठा super_block *old;
	काष्ठा user_namespace *user_ns = fc->global ? &init_user_ns : fc->user_ns;
	पूर्णांक err;

retry:
	spin_lock(&sb_lock);
	अगर (test) अणु
		hlist_क्रम_each_entry(old, &fc->fs_type->fs_supers, s_instances) अणु
			अगर (test(old, fc))
				जाओ share_extant_sb;
		पूर्ण
	पूर्ण
	अगर (!s) अणु
		spin_unlock(&sb_lock);
		s = alloc_super(fc->fs_type, fc->sb_flags, user_ns);
		अगर (!s)
			वापस ERR_PTR(-ENOMEM);
		जाओ retry;
	पूर्ण

	s->s_fs_info = fc->s_fs_info;
	err = set(s, fc);
	अगर (err) अणु
		s->s_fs_info = शून्य;
		spin_unlock(&sb_lock);
		destroy_unused_super(s);
		वापस ERR_PTR(err);
	पूर्ण
	fc->s_fs_info = शून्य;
	s->s_type = fc->fs_type;
	s->s_अगरlags |= fc->s_अगरlags;
	strlcpy(s->s_id, s->s_type->name, माप(s->s_id));
	list_add_tail(&s->s_list, &super_blocks);
	hlist_add_head(&s->s_instances, &s->s_type->fs_supers);
	spin_unlock(&sb_lock);
	get_fileप्रणाली(s->s_type);
	रेजिस्टर_shrinker_prepared(&s->s_shrink);
	वापस s;

share_extant_sb:
	अगर (user_ns != old->s_user_ns) अणु
		spin_unlock(&sb_lock);
		destroy_unused_super(s);
		वापस ERR_PTR(-EBUSY);
	पूर्ण
	अगर (!grab_super(old))
		जाओ retry;
	destroy_unused_super(s);
	वापस old;
पूर्ण
EXPORT_SYMBOL(sget_fc);

/**
 *	sget	-	find or create a superblock
 *	@type:	  fileप्रणाली type superblock should beदीर्घ to
 *	@test:	  comparison callback
 *	@set:	  setup callback
 *	@flags:	  mount flags
 *	@data:	  argument to each of them
 */
काष्ठा super_block *sget(काष्ठा file_प्रणाली_type *type,
			पूर्णांक (*test)(काष्ठा super_block *,व्योम *),
			पूर्णांक (*set)(काष्ठा super_block *,व्योम *),
			पूर्णांक flags,
			व्योम *data)
अणु
	काष्ठा user_namespace *user_ns = current_user_ns();
	काष्ठा super_block *s = शून्य;
	काष्ठा super_block *old;
	पूर्णांक err;

	/* We करोn't yet pass the user namespace of the parent
	 * mount through to here so always use &init_user_ns
	 * until that changes.
	 */
	अगर (flags & SB_SUBMOUNT)
		user_ns = &init_user_ns;

retry:
	spin_lock(&sb_lock);
	अगर (test) अणु
		hlist_क्रम_each_entry(old, &type->fs_supers, s_instances) अणु
			अगर (!test(old, data))
				जारी;
			अगर (user_ns != old->s_user_ns) अणु
				spin_unlock(&sb_lock);
				destroy_unused_super(s);
				वापस ERR_PTR(-EBUSY);
			पूर्ण
			अगर (!grab_super(old))
				जाओ retry;
			destroy_unused_super(s);
			वापस old;
		पूर्ण
	पूर्ण
	अगर (!s) अणु
		spin_unlock(&sb_lock);
		s = alloc_super(type, (flags & ~SB_SUBMOUNT), user_ns);
		अगर (!s)
			वापस ERR_PTR(-ENOMEM);
		जाओ retry;
	पूर्ण

	err = set(s, data);
	अगर (err) अणु
		spin_unlock(&sb_lock);
		destroy_unused_super(s);
		वापस ERR_PTR(err);
	पूर्ण
	s->s_type = type;
	strlcpy(s->s_id, type->name, माप(s->s_id));
	list_add_tail(&s->s_list, &super_blocks);
	hlist_add_head(&s->s_instances, &type->fs_supers);
	spin_unlock(&sb_lock);
	get_fileप्रणाली(type);
	रेजिस्टर_shrinker_prepared(&s->s_shrink);
	वापस s;
पूर्ण
EXPORT_SYMBOL(sget);

व्योम drop_super(काष्ठा super_block *sb)
अणु
	up_पढ़ो(&sb->s_umount);
	put_super(sb);
पूर्ण

EXPORT_SYMBOL(drop_super);

व्योम drop_super_exclusive(काष्ठा super_block *sb)
अणु
	up_ग_लिखो(&sb->s_umount);
	put_super(sb);
पूर्ण
EXPORT_SYMBOL(drop_super_exclusive);

अटल व्योम __iterate_supers(व्योम (*f)(काष्ठा super_block *))
अणु
	काष्ठा super_block *sb, *p = शून्य;

	spin_lock(&sb_lock);
	list_क्रम_each_entry(sb, &super_blocks, s_list) अणु
		अगर (hlist_unhashed(&sb->s_instances))
			जारी;
		sb->s_count++;
		spin_unlock(&sb_lock);

		f(sb);

		spin_lock(&sb_lock);
		अगर (p)
			__put_super(p);
		p = sb;
	पूर्ण
	अगर (p)
		__put_super(p);
	spin_unlock(&sb_lock);
पूर्ण
/**
 *	iterate_supers - call function क्रम all active superblocks
 *	@f: function to call
 *	@arg: argument to pass to it
 *
 *	Scans the superblock list and calls given function, passing it
 *	locked superblock and given argument.
 */
व्योम iterate_supers(व्योम (*f)(काष्ठा super_block *, व्योम *), व्योम *arg)
अणु
	काष्ठा super_block *sb, *p = शून्य;

	spin_lock(&sb_lock);
	list_क्रम_each_entry(sb, &super_blocks, s_list) अणु
		अगर (hlist_unhashed(&sb->s_instances))
			जारी;
		sb->s_count++;
		spin_unlock(&sb_lock);

		करोwn_पढ़ो(&sb->s_umount);
		अगर (sb->s_root && (sb->s_flags & SB_BORN))
			f(sb, arg);
		up_पढ़ो(&sb->s_umount);

		spin_lock(&sb_lock);
		अगर (p)
			__put_super(p);
		p = sb;
	पूर्ण
	अगर (p)
		__put_super(p);
	spin_unlock(&sb_lock);
पूर्ण

/**
 *	iterate_supers_type - call function क्रम superblocks of given type
 *	@type: fs type
 *	@f: function to call
 *	@arg: argument to pass to it
 *
 *	Scans the superblock list and calls given function, passing it
 *	locked superblock and given argument.
 */
व्योम iterate_supers_type(काष्ठा file_प्रणाली_type *type,
	व्योम (*f)(काष्ठा super_block *, व्योम *), व्योम *arg)
अणु
	काष्ठा super_block *sb, *p = शून्य;

	spin_lock(&sb_lock);
	hlist_क्रम_each_entry(sb, &type->fs_supers, s_instances) अणु
		sb->s_count++;
		spin_unlock(&sb_lock);

		करोwn_पढ़ो(&sb->s_umount);
		अगर (sb->s_root && (sb->s_flags & SB_BORN))
			f(sb, arg);
		up_पढ़ो(&sb->s_umount);

		spin_lock(&sb_lock);
		अगर (p)
			__put_super(p);
		p = sb;
	पूर्ण
	अगर (p)
		__put_super(p);
	spin_unlock(&sb_lock);
पूर्ण

EXPORT_SYMBOL(iterate_supers_type);

/**
 * get_super - get the superblock of a device
 * @bdev: device to get the superblock क्रम
 *
 * Scans the superblock list and finds the superblock of the file प्रणाली
 * mounted on the device given. %शून्य is वापसed अगर no match is found.
 */
काष्ठा super_block *get_super(काष्ठा block_device *bdev)
अणु
	काष्ठा super_block *sb;

	अगर (!bdev)
		वापस शून्य;

	spin_lock(&sb_lock);
rescan:
	list_क्रम_each_entry(sb, &super_blocks, s_list) अणु
		अगर (hlist_unhashed(&sb->s_instances))
			जारी;
		अगर (sb->s_bdev == bdev) अणु
			sb->s_count++;
			spin_unlock(&sb_lock);
			करोwn_पढ़ो(&sb->s_umount);
			/* still alive? */
			अगर (sb->s_root && (sb->s_flags & SB_BORN))
				वापस sb;
			up_पढ़ो(&sb->s_umount);
			/* nope, got unmounted */
			spin_lock(&sb_lock);
			__put_super(sb);
			जाओ rescan;
		पूर्ण
	पूर्ण
	spin_unlock(&sb_lock);
	वापस शून्य;
पूर्ण

/**
 * get_active_super - get an active reference to the superblock of a device
 * @bdev: device to get the superblock क्रम
 *
 * Scans the superblock list and finds the superblock of the file प्रणाली
 * mounted on the device given.  Returns the superblock with an active
 * reference or %शून्य अगर none was found.
 */
काष्ठा super_block *get_active_super(काष्ठा block_device *bdev)
अणु
	काष्ठा super_block *sb;

	अगर (!bdev)
		वापस शून्य;

restart:
	spin_lock(&sb_lock);
	list_क्रम_each_entry(sb, &super_blocks, s_list) अणु
		अगर (hlist_unhashed(&sb->s_instances))
			जारी;
		अगर (sb->s_bdev == bdev) अणु
			अगर (!grab_super(sb))
				जाओ restart;
			up_ग_लिखो(&sb->s_umount);
			वापस sb;
		पूर्ण
	पूर्ण
	spin_unlock(&sb_lock);
	वापस शून्य;
पूर्ण

काष्ठा super_block *user_get_super(dev_t dev, bool excl)
अणु
	काष्ठा super_block *sb;

	spin_lock(&sb_lock);
rescan:
	list_क्रम_each_entry(sb, &super_blocks, s_list) अणु
		अगर (hlist_unhashed(&sb->s_instances))
			जारी;
		अगर (sb->s_dev ==  dev) अणु
			sb->s_count++;
			spin_unlock(&sb_lock);
			अगर (excl)
				करोwn_ग_लिखो(&sb->s_umount);
			अन्यथा
				करोwn_पढ़ो(&sb->s_umount);
			/* still alive? */
			अगर (sb->s_root && (sb->s_flags & SB_BORN))
				वापस sb;
			अगर (excl)
				up_ग_लिखो(&sb->s_umount);
			अन्यथा
				up_पढ़ो(&sb->s_umount);
			/* nope, got unmounted */
			spin_lock(&sb_lock);
			__put_super(sb);
			जाओ rescan;
		पूर्ण
	पूर्ण
	spin_unlock(&sb_lock);
	वापस शून्य;
पूर्ण

/**
 * reconfigure_super - asks fileप्रणाली to change superblock parameters
 * @fc: The superblock and configuration
 *
 * Alters the configuration parameters of a live superblock.
 */
पूर्णांक reconfigure_super(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *sb = fc->root->d_sb;
	पूर्णांक retval;
	bool remount_ro = false;
	bool क्रमce = fc->sb_flags & SB_FORCE;

	अगर (fc->sb_flags_mask & ~MS_RMT_MASK)
		वापस -EINVAL;
	अगर (sb->s_ग_लिखोrs.frozen != SB_UNFROZEN)
		वापस -EBUSY;

	retval = security_sb_remount(sb, fc->security);
	अगर (retval)
		वापस retval;

	अगर (fc->sb_flags_mask & SB_RDONLY) अणु
#अगर_घोषित CONFIG_BLOCK
		अगर (!(fc->sb_flags & SB_RDONLY) && sb->s_bdev &&
		    bdev_पढ़ो_only(sb->s_bdev))
			वापस -EACCES;
#पूर्ण_अगर

		remount_ro = (fc->sb_flags & SB_RDONLY) && !sb_rकरोnly(sb);
	पूर्ण

	अगर (remount_ro) अणु
		अगर (!hlist_empty(&sb->s_pins)) अणु
			up_ग_लिखो(&sb->s_umount);
			group_pin_समाप्त(&sb->s_pins);
			करोwn_ग_लिखो(&sb->s_umount);
			अगर (!sb->s_root)
				वापस 0;
			अगर (sb->s_ग_लिखोrs.frozen != SB_UNFROZEN)
				वापस -EBUSY;
			remount_ro = !sb_rकरोnly(sb);
		पूर्ण
	पूर्ण
	shrink_dcache_sb(sb);

	/* If we are reconfiguring to RDONLY and current sb is पढ़ो/ग_लिखो,
	 * make sure there are no files खोलो क्रम writing.
	 */
	अगर (remount_ro) अणु
		अगर (क्रमce) अणु
			sb->s_पढ़ोonly_remount = 1;
			smp_wmb();
		पूर्ण अन्यथा अणु
			retval = sb_prepare_remount_पढ़ोonly(sb);
			अगर (retval)
				वापस retval;
		पूर्ण
	पूर्ण

	अगर (fc->ops->reconfigure) अणु
		retval = fc->ops->reconfigure(fc);
		अगर (retval) अणु
			अगर (!क्रमce)
				जाओ cancel_पढ़ोonly;
			/* If क्रमced remount, go ahead despite any errors */
			WARN(1, "forced remount of a %s fs returned %i\n",
			     sb->s_type->name, retval);
		पूर्ण
	पूर्ण

	WRITE_ONCE(sb->s_flags, ((sb->s_flags & ~fc->sb_flags_mask) |
				 (fc->sb_flags & fc->sb_flags_mask)));
	/* Needs to be ordered wrt mnt_is_पढ़ोonly() */
	smp_wmb();
	sb->s_पढ़ोonly_remount = 0;

	/*
	 * Some fileप्रणालीs modअगरy their metadata via some other path than the
	 * bdev buffer cache (eg. use a निजी mapping, or directories in
	 * pagecache, etc). Also file data modअगरications go via their own
	 * mappings. So If we try to mount पढ़ोonly then copy the fileप्रणाली
	 * from bdev, we could get stale data, so invalidate it to give a best
	 * efक्रमt at coherency.
	 */
	अगर (remount_ro && sb->s_bdev)
		invalidate_bdev(sb->s_bdev);
	वापस 0;

cancel_पढ़ोonly:
	sb->s_पढ़ोonly_remount = 0;
	वापस retval;
पूर्ण

अटल व्योम करो_emergency_remount_callback(काष्ठा super_block *sb)
अणु
	करोwn_ग_लिखो(&sb->s_umount);
	अगर (sb->s_root && sb->s_bdev && (sb->s_flags & SB_BORN) &&
	    !sb_rकरोnly(sb)) अणु
		काष्ठा fs_context *fc;

		fc = fs_context_क्रम_reconfigure(sb->s_root,
					SB_RDONLY | SB_FORCE, SB_RDONLY);
		अगर (!IS_ERR(fc)) अणु
			अगर (parse_monolithic_mount_data(fc, शून्य) == 0)
				(व्योम)reconfigure_super(fc);
			put_fs_context(fc);
		पूर्ण
	पूर्ण
	up_ग_लिखो(&sb->s_umount);
पूर्ण

अटल व्योम करो_emergency_remount(काष्ठा work_काष्ठा *work)
अणु
	__iterate_supers(करो_emergency_remount_callback);
	kमुक्त(work);
	prपूर्णांकk("Emergency Remount complete\n");
पूर्ण

व्योम emergency_remount(व्योम)
अणु
	काष्ठा work_काष्ठा *work;

	work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
	अगर (work) अणु
		INIT_WORK(work, करो_emergency_remount);
		schedule_work(work);
	पूर्ण
पूर्ण

अटल व्योम करो_thaw_all_callback(काष्ठा super_block *sb)
अणु
	करोwn_ग_लिखो(&sb->s_umount);
	अगर (sb->s_root && sb->s_flags & SB_BORN) अणु
		emergency_thaw_bdev(sb);
		thaw_super_locked(sb);
	पूर्ण अन्यथा अणु
		up_ग_लिखो(&sb->s_umount);
	पूर्ण
पूर्ण

अटल व्योम करो_thaw_all(काष्ठा work_काष्ठा *work)
अणु
	__iterate_supers(करो_thaw_all_callback);
	kमुक्त(work);
	prपूर्णांकk(KERN_WARNING "Emergency Thaw complete\n");
पूर्ण

/**
 * emergency_thaw_all -- क्रमcibly thaw every frozen fileप्रणाली
 *
 * Used क्रम emergency unमुक्तze of all fileप्रणालीs via SysRq
 */
व्योम emergency_thaw_all(व्योम)
अणु
	काष्ठा work_काष्ठा *work;

	work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
	अगर (work) अणु
		INIT_WORK(work, करो_thaw_all);
		schedule_work(work);
	पूर्ण
पूर्ण

अटल DEFINE_IDA(unnamed_dev_ida);

/**
 * get_anon_bdev - Allocate a block device क्रम fileप्रणालीs which करोn't have one.
 * @p: Poपूर्णांकer to a dev_t.
 *
 * Fileप्रणालीs which करोn't use real block devices can call this function
 * to allocate a भव block device.
 *
 * Context: Any context.  Frequently called जबतक holding sb_lock.
 * Return: 0 on success, -EMखाता अगर there are no anonymous bdevs left
 * or -ENOMEM अगर memory allocation failed.
 */
पूर्णांक get_anon_bdev(dev_t *p)
अणु
	पूर्णांक dev;

	/*
	 * Many userspace utilities consider an FSID of 0 invalid.
	 * Always वापस at least 1 from get_anon_bdev.
	 */
	dev = ida_alloc_range(&unnamed_dev_ida, 1, (1 << MINORBITS) - 1,
			GFP_ATOMIC);
	अगर (dev == -ENOSPC)
		dev = -EMखाता;
	अगर (dev < 0)
		वापस dev;

	*p = MKDEV(0, dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_anon_bdev);

व्योम मुक्त_anon_bdev(dev_t dev)
अणु
	ida_मुक्त(&unnamed_dev_ida, MINOR(dev));
पूर्ण
EXPORT_SYMBOL(मुक्त_anon_bdev);

पूर्णांक set_anon_super(काष्ठा super_block *s, व्योम *data)
अणु
	वापस get_anon_bdev(&s->s_dev);
पूर्ण
EXPORT_SYMBOL(set_anon_super);

व्योम समाप्त_anon_super(काष्ठा super_block *sb)
अणु
	dev_t dev = sb->s_dev;
	generic_shutकरोwn_super(sb);
	मुक्त_anon_bdev(dev);
पूर्ण
EXPORT_SYMBOL(समाप्त_anon_super);

व्योम समाप्त_litter_super(काष्ठा super_block *sb)
अणु
	अगर (sb->s_root)
		d_genocide(sb->s_root);
	समाप्त_anon_super(sb);
पूर्ण
EXPORT_SYMBOL(समाप्त_litter_super);

पूर्णांक set_anon_super_fc(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	वापस set_anon_super(sb, शून्य);
पूर्ण
EXPORT_SYMBOL(set_anon_super_fc);

अटल पूर्णांक test_keyed_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	वापस sb->s_fs_info == fc->s_fs_info;
पूर्ण

अटल पूर्णांक test_single_super(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	वापस 1;
पूर्ण

/**
 * vfs_get_super - Get a superblock with a search key set in s_fs_info.
 * @fc: The fileप्रणाली context holding the parameters
 * @keying: How to distinguish superblocks
 * @fill_super: Helper to initialise a new superblock
 *
 * Search क्रम a superblock and create a new one अगर not found.  The search
 * criterion is controlled by @keying.  If the search fails, a new superblock
 * is created and @fill_super() is called to initialise it.
 *
 * @keying can take one of a number of values:
 *
 * (1) vfs_get_single_super - Only one superblock of this type may exist on the
 *     प्रणाली.  This is typically used क्रम special प्रणाली fileप्रणालीs.
 *
 * (2) vfs_get_keyed_super - Multiple superblocks may exist, but they must have
 *     distinct keys (where the key is in s_fs_info).  Searching क्रम the same
 *     key again will turn up the superblock क्रम that key.
 *
 * (3) vfs_get_independent_super - Multiple superblocks may exist and are
 *     unkeyed.  Each call will get a new superblock.
 *
 * A permissions check is made by sget_fc() unless we're getting a superblock
 * क्रम a kernel-पूर्णांकernal mount or a submount.
 */
पूर्णांक vfs_get_super(काष्ठा fs_context *fc,
		  क्रमागत vfs_get_super_keying keying,
		  पूर्णांक (*fill_super)(काष्ठा super_block *sb,
				    काष्ठा fs_context *fc))
अणु
	पूर्णांक (*test)(काष्ठा super_block *, काष्ठा fs_context *);
	काष्ठा super_block *sb;
	पूर्णांक err;

	चयन (keying) अणु
	हाल vfs_get_single_super:
	हाल vfs_get_single_reconf_super:
		test = test_single_super;
		अवरोध;
	हाल vfs_get_keyed_super:
		test = test_keyed_super;
		अवरोध;
	हाल vfs_get_independent_super:
		test = शून्य;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	sb = sget_fc(fc, test, set_anon_super_fc);
	अगर (IS_ERR(sb))
		वापस PTR_ERR(sb);

	अगर (!sb->s_root) अणु
		err = fill_super(sb, fc);
		अगर (err)
			जाओ error;

		sb->s_flags |= SB_ACTIVE;
		fc->root = dget(sb->s_root);
	पूर्ण अन्यथा अणु
		fc->root = dget(sb->s_root);
		अगर (keying == vfs_get_single_reconf_super) अणु
			err = reconfigure_super(fc);
			अगर (err < 0) अणु
				dput(fc->root);
				fc->root = शून्य;
				जाओ error;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

error:
	deactivate_locked_super(sb);
	वापस err;
पूर्ण
EXPORT_SYMBOL(vfs_get_super);

पूर्णांक get_tree_nodev(काष्ठा fs_context *fc,
		  पूर्णांक (*fill_super)(काष्ठा super_block *sb,
				    काष्ठा fs_context *fc))
अणु
	वापस vfs_get_super(fc, vfs_get_independent_super, fill_super);
पूर्ण
EXPORT_SYMBOL(get_tree_nodev);

पूर्णांक get_tree_single(काष्ठा fs_context *fc,
		  पूर्णांक (*fill_super)(काष्ठा super_block *sb,
				    काष्ठा fs_context *fc))
अणु
	वापस vfs_get_super(fc, vfs_get_single_super, fill_super);
पूर्ण
EXPORT_SYMBOL(get_tree_single);

पूर्णांक get_tree_single_reconf(काष्ठा fs_context *fc,
		  पूर्णांक (*fill_super)(काष्ठा super_block *sb,
				    काष्ठा fs_context *fc))
अणु
	वापस vfs_get_super(fc, vfs_get_single_reconf_super, fill_super);
पूर्ण
EXPORT_SYMBOL(get_tree_single_reconf);

पूर्णांक get_tree_keyed(काष्ठा fs_context *fc,
		  पूर्णांक (*fill_super)(काष्ठा super_block *sb,
				    काष्ठा fs_context *fc),
		व्योम *key)
अणु
	fc->s_fs_info = key;
	वापस vfs_get_super(fc, vfs_get_keyed_super, fill_super);
पूर्ण
EXPORT_SYMBOL(get_tree_keyed);

#अगर_घोषित CONFIG_BLOCK

अटल पूर्णांक set_bdev_super(काष्ठा super_block *s, व्योम *data)
अणु
	s->s_bdev = data;
	s->s_dev = s->s_bdev->bd_dev;
	s->s_bdi = bdi_get(s->s_bdev->bd_bdi);

	अगर (blk_queue_stable_ग_लिखोs(s->s_bdev->bd_disk->queue))
		s->s_अगरlags |= SB_I_STABLE_WRITES;
	वापस 0;
पूर्ण

अटल पूर्णांक set_bdev_super_fc(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	वापस set_bdev_super(s, fc->sget_key);
पूर्ण

अटल पूर्णांक test_bdev_super_fc(काष्ठा super_block *s, काष्ठा fs_context *fc)
अणु
	वापस s->s_bdev == fc->sget_key;
पूर्ण

/**
 * get_tree_bdev - Get a superblock based on a single block device
 * @fc: The fileप्रणाली context holding the parameters
 * @fill_super: Helper to initialise a new superblock
 */
पूर्णांक get_tree_bdev(काष्ठा fs_context *fc,
		पूर्णांक (*fill_super)(काष्ठा super_block *,
				  काष्ठा fs_context *))
अणु
	काष्ठा block_device *bdev;
	काष्ठा super_block *s;
	भ_शेषe_t mode = FMODE_READ | FMODE_EXCL;
	पूर्णांक error = 0;

	अगर (!(fc->sb_flags & SB_RDONLY))
		mode |= FMODE_WRITE;

	अगर (!fc->source)
		वापस invalf(fc, "No source specified");

	bdev = blkdev_get_by_path(fc->source, mode, fc->fs_type);
	अगर (IS_ERR(bdev)) अणु
		errorf(fc, "%s: Can't open blockdev", fc->source);
		वापस PTR_ERR(bdev);
	पूर्ण

	/* Once the superblock is inserted पूर्णांकo the list by sget_fc(), s_umount
	 * will protect the lockfs code from trying to start a snapshot जबतक
	 * we are mounting
	 */
	mutex_lock(&bdev->bd_fsमुक्तze_mutex);
	अगर (bdev->bd_fsमुक्तze_count > 0) अणु
		mutex_unlock(&bdev->bd_fsमुक्तze_mutex);
		warnf(fc, "%pg: Can't mount, blockdev is frozen", bdev);
		blkdev_put(bdev, mode);
		वापस -EBUSY;
	पूर्ण

	fc->sb_flags |= SB_NOSEC;
	fc->sget_key = bdev;
	s = sget_fc(fc, test_bdev_super_fc, set_bdev_super_fc);
	mutex_unlock(&bdev->bd_fsमुक्तze_mutex);
	अगर (IS_ERR(s)) अणु
		blkdev_put(bdev, mode);
		वापस PTR_ERR(s);
	पूर्ण

	अगर (s->s_root) अणु
		/* Don't summarily change the RO/RW state. */
		अगर ((fc->sb_flags ^ s->s_flags) & SB_RDONLY) अणु
			warnf(fc, "%pg: Can't mount, would change RO state", bdev);
			deactivate_locked_super(s);
			blkdev_put(bdev, mode);
			वापस -EBUSY;
		पूर्ण

		/*
		 * s_umount nests inside bd_mutex during
		 * __invalidate_device().  blkdev_put() acquires
		 * bd_mutex and can't be called under s_umount.  Drop
		 * s_umount temporarily.  This is safe as we're
		 * holding an active reference.
		 */
		up_ग_लिखो(&s->s_umount);
		blkdev_put(bdev, mode);
		करोwn_ग_लिखो(&s->s_umount);
	पूर्ण अन्यथा अणु
		s->s_mode = mode;
		snम_लिखो(s->s_id, माप(s->s_id), "%pg", bdev);
		sb_set_blocksize(s, block_size(bdev));
		error = fill_super(s, fc);
		अगर (error) अणु
			deactivate_locked_super(s);
			वापस error;
		पूर्ण

		s->s_flags |= SB_ACTIVE;
		bdev->bd_super = s;
	पूर्ण

	BUG_ON(fc->root);
	fc->root = dget(s->s_root);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(get_tree_bdev);

अटल पूर्णांक test_bdev_super(काष्ठा super_block *s, व्योम *data)
अणु
	वापस (व्योम *)s->s_bdev == data;
पूर्ण

काष्ठा dentry *mount_bdev(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, स्थिर अक्षर *dev_name, व्योम *data,
	पूर्णांक (*fill_super)(काष्ठा super_block *, व्योम *, पूर्णांक))
अणु
	काष्ठा block_device *bdev;
	काष्ठा super_block *s;
	भ_शेषe_t mode = FMODE_READ | FMODE_EXCL;
	पूर्णांक error = 0;

	अगर (!(flags & SB_RDONLY))
		mode |= FMODE_WRITE;

	bdev = blkdev_get_by_path(dev_name, mode, fs_type);
	अगर (IS_ERR(bdev))
		वापस ERR_CAST(bdev);

	/*
	 * once the super is inserted पूर्णांकo the list by sget, s_umount
	 * will protect the lockfs code from trying to start a snapshot
	 * जबतक we are mounting
	 */
	mutex_lock(&bdev->bd_fsमुक्तze_mutex);
	अगर (bdev->bd_fsमुक्तze_count > 0) अणु
		mutex_unlock(&bdev->bd_fsमुक्तze_mutex);
		error = -EBUSY;
		जाओ error_bdev;
	पूर्ण
	s = sget(fs_type, test_bdev_super, set_bdev_super, flags | SB_NOSEC,
		 bdev);
	mutex_unlock(&bdev->bd_fsमुक्तze_mutex);
	अगर (IS_ERR(s))
		जाओ error_s;

	अगर (s->s_root) अणु
		अगर ((flags ^ s->s_flags) & SB_RDONLY) अणु
			deactivate_locked_super(s);
			error = -EBUSY;
			जाओ error_bdev;
		पूर्ण

		/*
		 * s_umount nests inside bd_mutex during
		 * __invalidate_device().  blkdev_put() acquires
		 * bd_mutex and can't be called under s_umount.  Drop
		 * s_umount temporarily.  This is safe as we're
		 * holding an active reference.
		 */
		up_ग_लिखो(&s->s_umount);
		blkdev_put(bdev, mode);
		करोwn_ग_लिखो(&s->s_umount);
	पूर्ण अन्यथा अणु
		s->s_mode = mode;
		snम_लिखो(s->s_id, माप(s->s_id), "%pg", bdev);
		sb_set_blocksize(s, block_size(bdev));
		error = fill_super(s, data, flags & SB_SILENT ? 1 : 0);
		अगर (error) अणु
			deactivate_locked_super(s);
			जाओ error;
		पूर्ण

		s->s_flags |= SB_ACTIVE;
		bdev->bd_super = s;
	पूर्ण

	वापस dget(s->s_root);

error_s:
	error = PTR_ERR(s);
error_bdev:
	blkdev_put(bdev, mode);
error:
	वापस ERR_PTR(error);
पूर्ण
EXPORT_SYMBOL(mount_bdev);

व्योम समाप्त_block_super(काष्ठा super_block *sb)
अणु
	काष्ठा block_device *bdev = sb->s_bdev;
	भ_शेषe_t mode = sb->s_mode;

	bdev->bd_super = शून्य;
	generic_shutकरोwn_super(sb);
	sync_blockdev(bdev);
	WARN_ON_ONCE(!(mode & FMODE_EXCL));
	blkdev_put(bdev, mode | FMODE_EXCL);
पूर्ण

EXPORT_SYMBOL(समाप्त_block_super);
#पूर्ण_अगर

काष्ठा dentry *mount_nodev(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, व्योम *data,
	पूर्णांक (*fill_super)(काष्ठा super_block *, व्योम *, पूर्णांक))
अणु
	पूर्णांक error;
	काष्ठा super_block *s = sget(fs_type, शून्य, set_anon_super, flags, शून्य);

	अगर (IS_ERR(s))
		वापस ERR_CAST(s);

	error = fill_super(s, data, flags & SB_SILENT ? 1 : 0);
	अगर (error) अणु
		deactivate_locked_super(s);
		वापस ERR_PTR(error);
	पूर्ण
	s->s_flags |= SB_ACTIVE;
	वापस dget(s->s_root);
पूर्ण
EXPORT_SYMBOL(mount_nodev);

अटल पूर्णांक reconfigure_single(काष्ठा super_block *s,
			      पूर्णांक flags, व्योम *data)
अणु
	काष्ठा fs_context *fc;
	पूर्णांक ret;

	/* The caller really need to be passing fc करोwn पूर्णांकo mount_single(),
	 * then a chunk of this can be हटाओd.  [Bollocks -- AV]
	 * Better yet, reconfiguration shouldn't happen, but rather the second
	 * mount should be rejected अगर the parameters are not compatible.
	 */
	fc = fs_context_क्रम_reconfigure(s->s_root, flags, MS_RMT_MASK);
	अगर (IS_ERR(fc))
		वापस PTR_ERR(fc);

	ret = parse_monolithic_mount_data(fc, data);
	अगर (ret < 0)
		जाओ out;

	ret = reconfigure_super(fc);
out:
	put_fs_context(fc);
	वापस ret;
पूर्ण

अटल पूर्णांक compare_single(काष्ठा super_block *s, व्योम *p)
अणु
	वापस 1;
पूर्ण

काष्ठा dentry *mount_single(काष्ठा file_प्रणाली_type *fs_type,
	पूर्णांक flags, व्योम *data,
	पूर्णांक (*fill_super)(काष्ठा super_block *, व्योम *, पूर्णांक))
अणु
	काष्ठा super_block *s;
	पूर्णांक error;

	s = sget(fs_type, compare_single, set_anon_super, flags, शून्य);
	अगर (IS_ERR(s))
		वापस ERR_CAST(s);
	अगर (!s->s_root) अणु
		error = fill_super(s, data, flags & SB_SILENT ? 1 : 0);
		अगर (!error)
			s->s_flags |= SB_ACTIVE;
	पूर्ण अन्यथा अणु
		error = reconfigure_single(s, flags, data);
	पूर्ण
	अगर (unlikely(error)) अणु
		deactivate_locked_super(s);
		वापस ERR_PTR(error);
	पूर्ण
	वापस dget(s->s_root);
पूर्ण
EXPORT_SYMBOL(mount_single);

/**
 * vfs_get_tree - Get the mountable root
 * @fc: The superblock configuration context.
 *
 * The fileप्रणाली is invoked to get or create a superblock which can then later
 * be used क्रम mounting.  The fileप्रणाली places a poपूर्णांकer to the root to be
 * used क्रम mounting in @fc->root.
 */
पूर्णांक vfs_get_tree(काष्ठा fs_context *fc)
अणु
	काष्ठा super_block *sb;
	पूर्णांक error;

	अगर (fc->root)
		वापस -EBUSY;

	/* Get the mountable root in fc->root, with a ref on the root and a ref
	 * on the superblock.
	 */
	error = fc->ops->get_tree(fc);
	अगर (error < 0)
		वापस error;

	अगर (!fc->root) अणु
		pr_err("Filesystem %s get_tree() didn't set fc->root\n",
		       fc->fs_type->name);
		/* We करोn't know what the locking state of the superblock is -
		 * अगर there is a superblock.
		 */
		BUG();
	पूर्ण

	sb = fc->root->d_sb;
	WARN_ON(!sb->s_bdi);

	/*
	 * Write barrier is क्रम super_cache_count(). We place it beक्रमe setting
	 * SB_BORN as the data dependency between the two functions is the
	 * superblock काष्ठाure contents that we just set up, not the SB_BORN
	 * flag.
	 */
	smp_wmb();
	sb->s_flags |= SB_BORN;

	error = security_sb_set_mnt_opts(sb, fc->security, 0, शून्य);
	अगर (unlikely(error)) अणु
		fc_drop_locked(fc);
		वापस error;
	पूर्ण

	/*
	 * fileप्रणालीs should never set s_maxbytes larger than MAX_LFS_खाताSIZE
	 * but s_maxbytes was an अचिन्हित दीर्घ दीर्घ क्रम many releases. Throw
	 * this warning क्रम a little जबतक to try and catch fileप्रणालीs that
	 * violate this rule.
	 */
	WARN((sb->s_maxbytes < 0), "%s set sb->s_maxbytes to "
		"negative value (%lld)\n", fc->fs_type->name, sb->s_maxbytes);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(vfs_get_tree);

/*
 * Setup निजी BDI क्रम given superblock. It माला_लो स्वतःmatically cleaned up
 * in generic_shutकरोwn_super().
 */
पूर्णांक super_setup_bdi_name(काष्ठा super_block *sb, अक्षर *fmt, ...)
अणु
	काष्ठा backing_dev_info *bdi;
	पूर्णांक err;
	बहु_सूची args;

	bdi = bdi_alloc(NUMA_NO_NODE);
	अगर (!bdi)
		वापस -ENOMEM;

	बहु_शुरू(args, fmt);
	err = bdi_रेजिस्टर_va(bdi, fmt, args);
	बहु_पूर्ण(args);
	अगर (err) अणु
		bdi_put(bdi);
		वापस err;
	पूर्ण
	WARN_ON(sb->s_bdi != &noop_backing_dev_info);
	sb->s_bdi = bdi;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(super_setup_bdi_name);

/*
 * Setup निजी BDI क्रम given superblock. I माला_लो स्वतःmatically cleaned up
 * in generic_shutकरोwn_super().
 */
पूर्णांक super_setup_bdi(काष्ठा super_block *sb)
अणु
	अटल atomic_दीर्घ_t bdi_seq = ATOMIC_LONG_INIT(0);

	वापस super_setup_bdi_name(sb, "%.28s-%ld", sb->s_type->name,
				    atomic_दीर्घ_inc_वापस(&bdi_seq));
पूर्ण
EXPORT_SYMBOL(super_setup_bdi);

/**
 * sb_रुको_ग_लिखो - रुको until all ग_लिखोrs to given file प्रणाली finish
 * @sb: the super क्रम which we रुको
 * @level: type of ग_लिखोrs we रुको क्रम (normal vs page fault)
 *
 * This function रुकोs until there are no ग_लिखोrs of given type to given file
 * प्रणाली.
 */
अटल व्योम sb_रुको_ग_लिखो(काष्ठा super_block *sb, पूर्णांक level)
अणु
	percpu_करोwn_ग_लिखो(sb->s_ग_लिखोrs.rw_sem + level-1);
पूर्ण

/*
 * We are going to वापस to userspace and क्रमget about these locks, the
 * ownership goes to the caller of thaw_super() which करोes unlock().
 */
अटल व्योम lockdep_sb_मुक्तze_release(काष्ठा super_block *sb)
अणु
	पूर्णांक level;

	क्रम (level = SB_FREEZE_LEVELS - 1; level >= 0; level--)
		percpu_rwsem_release(sb->s_ग_लिखोrs.rw_sem + level, 0, _THIS_IP_);
पूर्ण

/*
 * Tell lockdep we are holding these locks beक्रमe we call ->unमुक्तze_fs(sb).
 */
अटल व्योम lockdep_sb_मुक्तze_acquire(काष्ठा super_block *sb)
अणु
	पूर्णांक level;

	क्रम (level = 0; level < SB_FREEZE_LEVELS; ++level)
		percpu_rwsem_acquire(sb->s_ग_लिखोrs.rw_sem + level, 0, _THIS_IP_);
पूर्ण

अटल व्योम sb_मुक्तze_unlock(काष्ठा super_block *sb)
अणु
	पूर्णांक level;

	क्रम (level = SB_FREEZE_LEVELS - 1; level >= 0; level--)
		percpu_up_ग_लिखो(sb->s_ग_लिखोrs.rw_sem + level);
पूर्ण

/**
 * मुक्तze_super - lock the fileप्रणाली and क्रमce it पूर्णांकo a consistent state
 * @sb: the super to lock
 *
 * Syncs the super to make sure the fileप्रणाली is consistent and calls the fs's
 * मुक्तze_fs.  Subsequent calls to this without first thawing the fs will वापस
 * -EBUSY.
 *
 * During this function, sb->s_ग_लिखोrs.frozen goes through these values:
 *
 * SB_UNFROZEN: File प्रणाली is normal, all ग_लिखोs progress as usual.
 *
 * SB_FREEZE_WRITE: The file प्रणाली is in the process of being frozen.  New
 * ग_लिखोs should be blocked, though page faults are still allowed. We रुको क्रम
 * all ग_लिखोs to complete and then proceed to the next stage.
 *
 * SB_FREEZE_PAGEFAULT: Freezing जारीs. Now also page faults are blocked
 * but पूर्णांकernal fs thपढ़ोs can still modअगरy the fileप्रणाली (although they
 * should not dirty new pages or inodes), ग_लिखोback can run etc. After रुकोing
 * क्रम all running page faults we sync the fileप्रणाली which will clean all
 * dirty pages and inodes (no new dirty pages or inodes can be created when
 * sync is running).
 *
 * SB_FREEZE_FS: The file प्रणाली is frozen. Now all पूर्णांकernal sources of fs
 * modअगरication are blocked (e.g. XFS pपुनः_स्मृतिation truncation on inode
 * reclaim). This is usually implemented by blocking new transactions क्रम
 * fileप्रणालीs that have them and need this additional guard. After all
 * पूर्णांकernal ग_लिखोrs are finished we call ->मुक्तze_fs() to finish fileप्रणाली
 * मुक्तzing. Then we transition to SB_FREEZE_COMPLETE state. This state is
 * mostly auxiliary क्रम fileप्रणालीs to verअगरy they करो not modअगरy frozen fs.
 *
 * sb->s_ग_लिखोrs.frozen is रक्षित by sb->s_umount.
 */
पूर्णांक मुक्तze_super(काष्ठा super_block *sb)
अणु
	पूर्णांक ret;

	atomic_inc(&sb->s_active);
	करोwn_ग_लिखो(&sb->s_umount);
	अगर (sb->s_ग_लिखोrs.frozen != SB_UNFROZEN) अणु
		deactivate_locked_super(sb);
		वापस -EBUSY;
	पूर्ण

	अगर (!(sb->s_flags & SB_BORN)) अणु
		up_ग_लिखो(&sb->s_umount);
		वापस 0;	/* sic - it's "nothing to do" */
	पूर्ण

	अगर (sb_rकरोnly(sb)) अणु
		/* Nothing to करो really... */
		sb->s_ग_लिखोrs.frozen = SB_FREEZE_COMPLETE;
		up_ग_लिखो(&sb->s_umount);
		वापस 0;
	पूर्ण

	sb->s_ग_लिखोrs.frozen = SB_FREEZE_WRITE;
	/* Release s_umount to preserve sb_start_ग_लिखो -> s_umount ordering */
	up_ग_लिखो(&sb->s_umount);
	sb_रुको_ग_लिखो(sb, SB_FREEZE_WRITE);
	करोwn_ग_लिखो(&sb->s_umount);

	/* Now we go and block page faults... */
	sb->s_ग_लिखोrs.frozen = SB_FREEZE_PAGEFAULT;
	sb_रुको_ग_लिखो(sb, SB_FREEZE_PAGEFAULT);

	/* All ग_लिखोrs are करोne so after syncing there won't be dirty data */
	sync_fileप्रणाली(sb);

	/* Now रुको क्रम पूर्णांकernal fileप्रणाली counter */
	sb->s_ग_लिखोrs.frozen = SB_FREEZE_FS;
	sb_रुको_ग_लिखो(sb, SB_FREEZE_FS);

	अगर (sb->s_op->मुक्तze_fs) अणु
		ret = sb->s_op->मुक्तze_fs(sb);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR
				"VFS:Filesystem freeze failed\n");
			sb->s_ग_लिखोrs.frozen = SB_UNFROZEN;
			sb_मुक्तze_unlock(sb);
			wake_up(&sb->s_ग_लिखोrs.रुको_unfrozen);
			deactivate_locked_super(sb);
			वापस ret;
		पूर्ण
	पूर्ण
	/*
	 * For debugging purposes so that fs can warn अगर it sees ग_लिखो activity
	 * when frozen is set to SB_FREEZE_COMPLETE, and क्रम thaw_super().
	 */
	sb->s_ग_लिखोrs.frozen = SB_FREEZE_COMPLETE;
	lockdep_sb_मुक्तze_release(sb);
	up_ग_लिखो(&sb->s_umount);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(मुक्तze_super);

अटल पूर्णांक thaw_super_locked(काष्ठा super_block *sb)
अणु
	पूर्णांक error;

	अगर (sb->s_ग_लिखोrs.frozen != SB_FREEZE_COMPLETE) अणु
		up_ग_लिखो(&sb->s_umount);
		वापस -EINVAL;
	पूर्ण

	अगर (sb_rकरोnly(sb)) अणु
		sb->s_ग_लिखोrs.frozen = SB_UNFROZEN;
		जाओ out;
	पूर्ण

	lockdep_sb_मुक्तze_acquire(sb);

	अगर (sb->s_op->unमुक्तze_fs) अणु
		error = sb->s_op->unमुक्तze_fs(sb);
		अगर (error) अणु
			prपूर्णांकk(KERN_ERR
				"VFS:Filesystem thaw failed\n");
			lockdep_sb_मुक्तze_release(sb);
			up_ग_लिखो(&sb->s_umount);
			वापस error;
		पूर्ण
	पूर्ण

	sb->s_ग_लिखोrs.frozen = SB_UNFROZEN;
	sb_मुक्तze_unlock(sb);
out:
	wake_up(&sb->s_ग_लिखोrs.रुको_unfrozen);
	deactivate_locked_super(sb);
	वापस 0;
पूर्ण

/**
 * thaw_super -- unlock fileप्रणाली
 * @sb: the super to thaw
 *
 * Unlocks the fileप्रणाली and marks it ग_लिखोable again after मुक्तze_super().
 */
पूर्णांक thaw_super(काष्ठा super_block *sb)
अणु
	करोwn_ग_लिखो(&sb->s_umount);
	वापस thaw_super_locked(sb);
पूर्ण
EXPORT_SYMBOL(thaw_super);
