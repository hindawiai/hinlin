<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश <linux/iversion.h>

#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_defer.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_attr.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_inode_item.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_filestream.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_symlink.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_log.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_reflink.h"

kmem_zone_t *xfs_inode_zone;

/*
 * Used in xfs_itruncate_extents().  This is the maximum number of extents
 * मुक्तd from a file in a single transaction.
 */
#घोषणा	XFS_ITRUNC_MAX_EXTENTS	2

STATIC पूर्णांक xfs_iunlink(काष्ठा xfs_trans *, काष्ठा xfs_inode *);
STATIC पूर्णांक xfs_iunlink_हटाओ(काष्ठा xfs_trans *, काष्ठा xfs_inode *);

/*
 * helper function to extract extent size hपूर्णांक from inode
 */
xfs_extlen_t
xfs_get_extsz_hपूर्णांक(
	काष्ठा xfs_inode	*ip)
अणु
	/*
	 * No poपूर्णांक in aligning allocations अगर we need to COW to actually
	 * ग_लिखो to them.
	 */
	अगर (xfs_is_always_cow_inode(ip))
		वापस 0;
	अगर ((ip->i_dअगरlags & XFS_DIFLAG_EXTSIZE) && ip->i_extsize)
		वापस ip->i_extsize;
	अगर (XFS_IS_REALTIME_INODE(ip))
		वापस ip->i_mount->m_sb.sb_rextsize;
	वापस 0;
पूर्ण

/*
 * Helper function to extract CoW extent size hपूर्णांक from inode.
 * Between the extent size hपूर्णांक and the CoW extent size hपूर्णांक, we
 * वापस the greater of the two.  If the value is zero (स्वतःmatic),
 * use the शेष size.
 */
xfs_extlen_t
xfs_get_cowextsz_hपूर्णांक(
	काष्ठा xfs_inode	*ip)
अणु
	xfs_extlen_t		a, b;

	a = 0;
	अगर (ip->i_dअगरlags2 & XFS_DIFLAG2_COWEXTSIZE)
		a = ip->i_cowextsize;
	b = xfs_get_extsz_hपूर्णांक(ip);

	a = max(a, b);
	अगर (a == 0)
		वापस XFS_DEFAULT_COWEXTSZ_HINT;
	वापस a;
पूर्ण

/*
 * These two are wrapper routines around the xfs_ilock() routine used to
 * centralize some grungy code.  They are used in places that wish to lock the
 * inode solely क्रम पढ़ोing the extents.  The reason these places can't just
 * call xfs_ilock(ip, XFS_ILOCK_SHARED) is that the inode lock also guards to
 * bringing in of the extents from disk क्रम a file in b-tree क्रमmat.  If the
 * inode is in b-tree क्रमmat, then we need to lock the inode exclusively until
 * the extents are पढ़ो in.  Locking it exclusively all the समय would limit
 * our parallelism unnecessarily, though.  What we करो instead is check to see
 * अगर the extents have been पढ़ो in yet, and only lock the inode exclusively
 * अगर they have not.
 *
 * The functions वापस a value which should be given to the corresponding
 * xfs_iunlock() call.
 */
uपूर्णांक
xfs_ilock_data_map_shared(
	काष्ठा xfs_inode	*ip)
अणु
	uपूर्णांक			lock_mode = XFS_ILOCK_SHARED;

	अगर (xfs_need_iपढ़ो_extents(&ip->i_df))
		lock_mode = XFS_ILOCK_EXCL;
	xfs_ilock(ip, lock_mode);
	वापस lock_mode;
पूर्ण

uपूर्णांक
xfs_ilock_attr_map_shared(
	काष्ठा xfs_inode	*ip)
अणु
	uपूर्णांक			lock_mode = XFS_ILOCK_SHARED;

	अगर (ip->i_afp && xfs_need_iपढ़ो_extents(ip->i_afp))
		lock_mode = XFS_ILOCK_EXCL;
	xfs_ilock(ip, lock_mode);
	वापस lock_mode;
पूर्ण

/*
 * In addition to i_rwsem in the VFS inode, the xfs inode contains 2
 * multi-पढ़ोer locks: i_mmap_lock and the i_lock.  This routine allows
 * various combinations of the locks to be obtained.
 *
 * The 3 locks should always be ordered so that the IO lock is obtained first,
 * the mmap lock second and the ilock last in order to prevent deadlock.
 *
 * Basic locking order:
 *
 * i_rwsem -> i_mmap_lock -> page_lock -> i_ilock
 *
 * mmap_lock locking order:
 *
 * i_rwsem -> page lock -> mmap_lock
 * mmap_lock -> i_mmap_lock -> page_lock
 *
 * The dअगरference in mmap_lock locking order mean that we cannot hold the
 * i_mmap_lock over syscall based पढ़ो(2)/ग_लिखो(2) based IO. These IO paths can
 * fault in pages during copy in/out (क्रम buffered IO) or require the mmap_lock
 * in get_user_pages() to map the user pages पूर्णांकo the kernel address space क्रम
 * direct IO. Similarly the i_rwsem cannot be taken inside a page fault because
 * page faults alपढ़ोy hold the mmap_lock.
 *
 * Hence to serialise fully against both syscall and mmap based IO, we need to
 * take both the i_rwsem and the i_mmap_lock. These locks should *only* be both
 * taken in places where we need to invalidate the page cache in a race
 * मुक्त manner (e.g. truncate, hole punch and other extent manipulation
 * functions).
 */
व्योम
xfs_ilock(
	xfs_inode_t		*ip,
	uपूर्णांक			lock_flags)
अणु
	trace_xfs_ilock(ip, lock_flags, _RET_IP_);

	/*
	 * You can't set both SHARED and EXCL क्रम the same lock,
	 * and only XFS_IOLOCK_SHARED, XFS_IOLOCK_EXCL, XFS_ILOCK_SHARED,
	 * and XFS_ILOCK_EXCL are valid values to set in lock_flags.
	 */
	ASSERT((lock_flags & (XFS_IOLOCK_SHARED | XFS_IOLOCK_EXCL)) !=
	       (XFS_IOLOCK_SHARED | XFS_IOLOCK_EXCL));
	ASSERT((lock_flags & (XFS_MMAPLOCK_SHARED | XFS_MMAPLOCK_EXCL)) !=
	       (XFS_MMAPLOCK_SHARED | XFS_MMAPLOCK_EXCL));
	ASSERT((lock_flags & (XFS_ILOCK_SHARED | XFS_ILOCK_EXCL)) !=
	       (XFS_ILOCK_SHARED | XFS_ILOCK_EXCL));
	ASSERT((lock_flags & ~(XFS_LOCK_MASK | XFS_LOCK_SUBCLASS_MASK)) == 0);

	अगर (lock_flags & XFS_IOLOCK_EXCL) अणु
		करोwn_ग_लिखो_nested(&VFS_I(ip)->i_rwsem,
				  XFS_IOLOCK_DEP(lock_flags));
	पूर्ण अन्यथा अगर (lock_flags & XFS_IOLOCK_SHARED) अणु
		करोwn_पढ़ो_nested(&VFS_I(ip)->i_rwsem,
				 XFS_IOLOCK_DEP(lock_flags));
	पूर्ण

	अगर (lock_flags & XFS_MMAPLOCK_EXCL)
		mrupdate_nested(&ip->i_mmaplock, XFS_MMAPLOCK_DEP(lock_flags));
	अन्यथा अगर (lock_flags & XFS_MMAPLOCK_SHARED)
		mraccess_nested(&ip->i_mmaplock, XFS_MMAPLOCK_DEP(lock_flags));

	अगर (lock_flags & XFS_ILOCK_EXCL)
		mrupdate_nested(&ip->i_lock, XFS_ILOCK_DEP(lock_flags));
	अन्यथा अगर (lock_flags & XFS_ILOCK_SHARED)
		mraccess_nested(&ip->i_lock, XFS_ILOCK_DEP(lock_flags));
पूर्ण

/*
 * This is just like xfs_ilock(), except that the caller
 * is guaranteed not to sleep.  It वापसs 1 अगर it माला_लो
 * the requested locks and 0 otherwise.  If the IO lock is
 * obtained but the inode lock cannot be, then the IO lock
 * is dropped beक्रमe वापसing.
 *
 * ip -- the inode being locked
 * lock_flags -- this parameter indicates the inode's locks to be
 *       to be locked.  See the comment क्रम xfs_ilock() क्रम a list
 *	 of valid values.
 */
पूर्णांक
xfs_ilock_noरुको(
	xfs_inode_t		*ip,
	uपूर्णांक			lock_flags)
अणु
	trace_xfs_ilock_noरुको(ip, lock_flags, _RET_IP_);

	/*
	 * You can't set both SHARED and EXCL क्रम the same lock,
	 * and only XFS_IOLOCK_SHARED, XFS_IOLOCK_EXCL, XFS_ILOCK_SHARED,
	 * and XFS_ILOCK_EXCL are valid values to set in lock_flags.
	 */
	ASSERT((lock_flags & (XFS_IOLOCK_SHARED | XFS_IOLOCK_EXCL)) !=
	       (XFS_IOLOCK_SHARED | XFS_IOLOCK_EXCL));
	ASSERT((lock_flags & (XFS_MMAPLOCK_SHARED | XFS_MMAPLOCK_EXCL)) !=
	       (XFS_MMAPLOCK_SHARED | XFS_MMAPLOCK_EXCL));
	ASSERT((lock_flags & (XFS_ILOCK_SHARED | XFS_ILOCK_EXCL)) !=
	       (XFS_ILOCK_SHARED | XFS_ILOCK_EXCL));
	ASSERT((lock_flags & ~(XFS_LOCK_MASK | XFS_LOCK_SUBCLASS_MASK)) == 0);

	अगर (lock_flags & XFS_IOLOCK_EXCL) अणु
		अगर (!करोwn_ग_लिखो_trylock(&VFS_I(ip)->i_rwsem))
			जाओ out;
	पूर्ण अन्यथा अगर (lock_flags & XFS_IOLOCK_SHARED) अणु
		अगर (!करोwn_पढ़ो_trylock(&VFS_I(ip)->i_rwsem))
			जाओ out;
	पूर्ण

	अगर (lock_flags & XFS_MMAPLOCK_EXCL) अणु
		अगर (!mrtryupdate(&ip->i_mmaplock))
			जाओ out_unकरो_iolock;
	पूर्ण अन्यथा अगर (lock_flags & XFS_MMAPLOCK_SHARED) अणु
		अगर (!mrtryaccess(&ip->i_mmaplock))
			जाओ out_unकरो_iolock;
	पूर्ण

	अगर (lock_flags & XFS_ILOCK_EXCL) अणु
		अगर (!mrtryupdate(&ip->i_lock))
			जाओ out_unकरो_mmaplock;
	पूर्ण अन्यथा अगर (lock_flags & XFS_ILOCK_SHARED) अणु
		अगर (!mrtryaccess(&ip->i_lock))
			जाओ out_unकरो_mmaplock;
	पूर्ण
	वापस 1;

out_unकरो_mmaplock:
	अगर (lock_flags & XFS_MMAPLOCK_EXCL)
		mrunlock_excl(&ip->i_mmaplock);
	अन्यथा अगर (lock_flags & XFS_MMAPLOCK_SHARED)
		mrunlock_shared(&ip->i_mmaplock);
out_unकरो_iolock:
	अगर (lock_flags & XFS_IOLOCK_EXCL)
		up_ग_लिखो(&VFS_I(ip)->i_rwsem);
	अन्यथा अगर (lock_flags & XFS_IOLOCK_SHARED)
		up_पढ़ो(&VFS_I(ip)->i_rwsem);
out:
	वापस 0;
पूर्ण

/*
 * xfs_iunlock() is used to drop the inode locks acquired with
 * xfs_ilock() and xfs_ilock_noरुको().  The caller must pass
 * in the flags given to xfs_ilock() or xfs_ilock_noरुको() so
 * that we know which locks to drop.
 *
 * ip -- the inode being unlocked
 * lock_flags -- this parameter indicates the inode's locks to be
 *       to be unlocked.  See the comment क्रम xfs_ilock() क्रम a list
 *	 of valid values क्रम this parameter.
 *
 */
व्योम
xfs_iunlock(
	xfs_inode_t		*ip,
	uपूर्णांक			lock_flags)
अणु
	/*
	 * You can't set both SHARED and EXCL क्रम the same lock,
	 * and only XFS_IOLOCK_SHARED, XFS_IOLOCK_EXCL, XFS_ILOCK_SHARED,
	 * and XFS_ILOCK_EXCL are valid values to set in lock_flags.
	 */
	ASSERT((lock_flags & (XFS_IOLOCK_SHARED | XFS_IOLOCK_EXCL)) !=
	       (XFS_IOLOCK_SHARED | XFS_IOLOCK_EXCL));
	ASSERT((lock_flags & (XFS_MMAPLOCK_SHARED | XFS_MMAPLOCK_EXCL)) !=
	       (XFS_MMAPLOCK_SHARED | XFS_MMAPLOCK_EXCL));
	ASSERT((lock_flags & (XFS_ILOCK_SHARED | XFS_ILOCK_EXCL)) !=
	       (XFS_ILOCK_SHARED | XFS_ILOCK_EXCL));
	ASSERT((lock_flags & ~(XFS_LOCK_MASK | XFS_LOCK_SUBCLASS_MASK)) == 0);
	ASSERT(lock_flags != 0);

	अगर (lock_flags & XFS_IOLOCK_EXCL)
		up_ग_लिखो(&VFS_I(ip)->i_rwsem);
	अन्यथा अगर (lock_flags & XFS_IOLOCK_SHARED)
		up_पढ़ो(&VFS_I(ip)->i_rwsem);

	अगर (lock_flags & XFS_MMAPLOCK_EXCL)
		mrunlock_excl(&ip->i_mmaplock);
	अन्यथा अगर (lock_flags & XFS_MMAPLOCK_SHARED)
		mrunlock_shared(&ip->i_mmaplock);

	अगर (lock_flags & XFS_ILOCK_EXCL)
		mrunlock_excl(&ip->i_lock);
	अन्यथा अगर (lock_flags & XFS_ILOCK_SHARED)
		mrunlock_shared(&ip->i_lock);

	trace_xfs_iunlock(ip, lock_flags, _RET_IP_);
पूर्ण

/*
 * give up ग_लिखो locks.  the i/o lock cannot be held nested
 * अगर it is being demoted.
 */
व्योम
xfs_ilock_demote(
	xfs_inode_t		*ip,
	uपूर्णांक			lock_flags)
अणु
	ASSERT(lock_flags & (XFS_IOLOCK_EXCL|XFS_MMAPLOCK_EXCL|XFS_ILOCK_EXCL));
	ASSERT((lock_flags &
		~(XFS_IOLOCK_EXCL|XFS_MMAPLOCK_EXCL|XFS_ILOCK_EXCL)) == 0);

	अगर (lock_flags & XFS_ILOCK_EXCL)
		mrdemote(&ip->i_lock);
	अगर (lock_flags & XFS_MMAPLOCK_EXCL)
		mrdemote(&ip->i_mmaplock);
	अगर (lock_flags & XFS_IOLOCK_EXCL)
		करोwngrade_ग_लिखो(&VFS_I(ip)->i_rwsem);

	trace_xfs_ilock_demote(ip, lock_flags, _RET_IP_);
पूर्ण

#अगर defined(DEBUG) || defined(XFS_WARN)
पूर्णांक
xfs_isilocked(
	xfs_inode_t		*ip,
	uपूर्णांक			lock_flags)
अणु
	अगर (lock_flags & (XFS_ILOCK_EXCL|XFS_ILOCK_SHARED)) अणु
		अगर (!(lock_flags & XFS_ILOCK_SHARED))
			वापस !!ip->i_lock.mr_ग_लिखोr;
		वापस rwsem_is_locked(&ip->i_lock.mr_lock);
	पूर्ण

	अगर (lock_flags & (XFS_MMAPLOCK_EXCL|XFS_MMAPLOCK_SHARED)) अणु
		अगर (!(lock_flags & XFS_MMAPLOCK_SHARED))
			वापस !!ip->i_mmaplock.mr_ग_लिखोr;
		वापस rwsem_is_locked(&ip->i_mmaplock.mr_lock);
	पूर्ण

	अगर (lock_flags & (XFS_IOLOCK_EXCL|XFS_IOLOCK_SHARED)) अणु
		अगर (!(lock_flags & XFS_IOLOCK_SHARED))
			वापस !debug_locks ||
				lockdep_is_held_type(&VFS_I(ip)->i_rwsem, 0);
		वापस rwsem_is_locked(&VFS_I(ip)->i_rwsem);
	पूर्ण

	ASSERT(0);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * xfs_lockdep_subclass_ok() is only used in an ASSERT, so is only called when
 * DEBUG or XFS_WARN is set. And MAX_LOCKDEP_SUBCLASSES is then only defined
 * when CONFIG_LOCKDEP is set. Hence the complex define below to aव्योम build
 * errors and warnings.
 */
#अगर (defined(DEBUG) || defined(XFS_WARN)) && defined(CONFIG_LOCKDEP)
अटल bool
xfs_lockdep_subclass_ok(
	पूर्णांक subclass)
अणु
	वापस subclass < MAX_LOCKDEP_SUBCLASSES;
पूर्ण
#अन्यथा
#घोषणा xfs_lockdep_subclass_ok(subclass)	(true)
#पूर्ण_अगर

/*
 * Bump the subclass so xfs_lock_inodes() acquires each lock with a dअगरferent
 * value. This can be called क्रम any type of inode lock combination, including
 * parent locking. Care must be taken to ensure we करोn't overrun the subclass
 * storage fields in the class mask we build.
 */
अटल अंतरभूत पूर्णांक
xfs_lock_inumorder(पूर्णांक lock_mode, पूर्णांक subclass)
अणु
	पूर्णांक	class = 0;

	ASSERT(!(lock_mode & (XFS_ILOCK_PARENT | XFS_ILOCK_RTBITMAP |
			      XFS_ILOCK_RTSUM)));
	ASSERT(xfs_lockdep_subclass_ok(subclass));

	अगर (lock_mode & (XFS_IOLOCK_SHARED|XFS_IOLOCK_EXCL)) अणु
		ASSERT(subclass <= XFS_IOLOCK_MAX_SUBCLASS);
		class += subclass << XFS_IOLOCK_SHIFT;
	पूर्ण

	अगर (lock_mode & (XFS_MMAPLOCK_SHARED|XFS_MMAPLOCK_EXCL)) अणु
		ASSERT(subclass <= XFS_MMAPLOCK_MAX_SUBCLASS);
		class += subclass << XFS_MMAPLOCK_SHIFT;
	पूर्ण

	अगर (lock_mode & (XFS_ILOCK_SHARED|XFS_ILOCK_EXCL)) अणु
		ASSERT(subclass <= XFS_ILOCK_MAX_SUBCLASS);
		class += subclass << XFS_ILOCK_SHIFT;
	पूर्ण

	वापस (lock_mode & ~XFS_LOCK_SUBCLASS_MASK) | class;
पूर्ण

/*
 * The following routine will lock n inodes in exclusive mode.  We assume the
 * caller calls us with the inodes in i_ino order.
 *
 * We need to detect deadlock where an inode that we lock is in the AIL and we
 * start रुकोing क्रम another inode that is locked by a thपढ़ो in a दीर्घ running
 * transaction (such as truncate). This can result in deadlock since the दीर्घ
 * running trans might need to रुको क्रम the inode we just locked in order to
 * push the tail and मुक्त space in the log.
 *
 * xfs_lock_inodes() can only be used to lock one type of lock at a समय -
 * the iolock, the mmaplock or the ilock, but not more than one at a समय. If we
 * lock more than one at a समय, lockdep will report false positives saying we
 * have violated locking orders.
 */
अटल व्योम
xfs_lock_inodes(
	काष्ठा xfs_inode	**ips,
	पूर्णांक			inodes,
	uपूर्णांक			lock_mode)
अणु
	पूर्णांक			attempts = 0, i, j, try_lock;
	काष्ठा xfs_log_item	*lp;

	/*
	 * Currently supports between 2 and 5 inodes with exclusive locking.  We
	 * support an arbitrary depth of locking here, but असलolute limits on
	 * inodes depend on the type of locking and the limits placed by
	 * lockdep annotations in xfs_lock_inumorder.  These are all checked by
	 * the निश्चितs.
	 */
	ASSERT(ips && inodes >= 2 && inodes <= 5);
	ASSERT(lock_mode & (XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL |
			    XFS_ILOCK_EXCL));
	ASSERT(!(lock_mode & (XFS_IOLOCK_SHARED | XFS_MMAPLOCK_SHARED |
			      XFS_ILOCK_SHARED)));
	ASSERT(!(lock_mode & XFS_MMAPLOCK_EXCL) ||
		inodes <= XFS_MMAPLOCK_MAX_SUBCLASS + 1);
	ASSERT(!(lock_mode & XFS_ILOCK_EXCL) ||
		inodes <= XFS_ILOCK_MAX_SUBCLASS + 1);

	अगर (lock_mode & XFS_IOLOCK_EXCL) अणु
		ASSERT(!(lock_mode & (XFS_MMAPLOCK_EXCL | XFS_ILOCK_EXCL)));
	पूर्ण अन्यथा अगर (lock_mode & XFS_MMAPLOCK_EXCL)
		ASSERT(!(lock_mode & XFS_ILOCK_EXCL));

	try_lock = 0;
	i = 0;
again:
	क्रम (; i < inodes; i++) अणु
		ASSERT(ips[i]);

		अगर (i && (ips[i] == ips[i - 1]))	/* Alपढ़ोy locked */
			जारी;

		/*
		 * If try_lock is not set yet, make sure all locked inodes are
		 * not in the AIL.  If any are, set try_lock to be used later.
		 */
		अगर (!try_lock) अणु
			क्रम (j = (i - 1); j >= 0 && !try_lock; j--) अणु
				lp = &ips[j]->i_itemp->ili_item;
				अगर (lp && test_bit(XFS_LI_IN_AIL, &lp->li_flags))
					try_lock++;
			पूर्ण
		पूर्ण

		/*
		 * If any of the previous locks we have locked is in the AIL,
		 * we must TRY to get the second and subsequent locks. If
		 * we can't get any, we must release all we have
		 * and try again.
		 */
		अगर (!try_lock) अणु
			xfs_ilock(ips[i], xfs_lock_inumorder(lock_mode, i));
			जारी;
		पूर्ण

		/* try_lock means we have an inode locked that is in the AIL. */
		ASSERT(i != 0);
		अगर (xfs_ilock_noरुको(ips[i], xfs_lock_inumorder(lock_mode, i)))
			जारी;

		/*
		 * Unlock all previous guys and try again.  xfs_iunlock will try
		 * to push the tail अगर the inode is in the AIL.
		 */
		attempts++;
		क्रम (j = i - 1; j >= 0; j--) अणु
			/*
			 * Check to see अगर we've alपढ़ोy unlocked this one.  Not
			 * the first one going back, and the inode ptr is the
			 * same.
			 */
			अगर (j != (i - 1) && ips[j] == ips[j + 1])
				जारी;

			xfs_iunlock(ips[j], lock_mode);
		पूर्ण

		अगर ((attempts % 5) == 0) अणु
			delay(1); /* Don't just spin the CPU */
		पूर्ण
		i = 0;
		try_lock = 0;
		जाओ again;
	पूर्ण
पूर्ण

/*
 * xfs_lock_two_inodes() can only be used to lock one type of lock at a समय -
 * the mmaplock or the ilock, but not more than one type at a समय. If we lock
 * more than one at a समय, lockdep will report false positives saying we have
 * violated locking orders.  The iolock must be द्विगुन-locked separately since
 * we use i_rwsem क्रम that.  We now support taking one lock EXCL and the other
 * SHARED.
 */
व्योम
xfs_lock_two_inodes(
	काष्ठा xfs_inode	*ip0,
	uपूर्णांक			ip0_mode,
	काष्ठा xfs_inode	*ip1,
	uपूर्णांक			ip1_mode)
अणु
	काष्ठा xfs_inode	*temp;
	uपूर्णांक			mode_temp;
	पूर्णांक			attempts = 0;
	काष्ठा xfs_log_item	*lp;

	ASSERT(hweight32(ip0_mode) == 1);
	ASSERT(hweight32(ip1_mode) == 1);
	ASSERT(!(ip0_mode & (XFS_IOLOCK_SHARED|XFS_IOLOCK_EXCL)));
	ASSERT(!(ip1_mode & (XFS_IOLOCK_SHARED|XFS_IOLOCK_EXCL)));
	ASSERT(!(ip0_mode & (XFS_MMAPLOCK_SHARED|XFS_MMAPLOCK_EXCL)) ||
	       !(ip0_mode & (XFS_ILOCK_SHARED|XFS_ILOCK_EXCL)));
	ASSERT(!(ip1_mode & (XFS_MMAPLOCK_SHARED|XFS_MMAPLOCK_EXCL)) ||
	       !(ip1_mode & (XFS_ILOCK_SHARED|XFS_ILOCK_EXCL)));
	ASSERT(!(ip1_mode & (XFS_MMAPLOCK_SHARED|XFS_MMAPLOCK_EXCL)) ||
	       !(ip0_mode & (XFS_ILOCK_SHARED|XFS_ILOCK_EXCL)));
	ASSERT(!(ip0_mode & (XFS_MMAPLOCK_SHARED|XFS_MMAPLOCK_EXCL)) ||
	       !(ip1_mode & (XFS_ILOCK_SHARED|XFS_ILOCK_EXCL)));

	ASSERT(ip0->i_ino != ip1->i_ino);

	अगर (ip0->i_ino > ip1->i_ino) अणु
		temp = ip0;
		ip0 = ip1;
		ip1 = temp;
		mode_temp = ip0_mode;
		ip0_mode = ip1_mode;
		ip1_mode = mode_temp;
	पूर्ण

 again:
	xfs_ilock(ip0, xfs_lock_inumorder(ip0_mode, 0));

	/*
	 * If the first lock we have locked is in the AIL, we must TRY to get
	 * the second lock. If we can't get it, we must release the first one
	 * and try again.
	 */
	lp = &ip0->i_itemp->ili_item;
	अगर (lp && test_bit(XFS_LI_IN_AIL, &lp->li_flags)) अणु
		अगर (!xfs_ilock_noरुको(ip1, xfs_lock_inumorder(ip1_mode, 1))) अणु
			xfs_iunlock(ip0, ip0_mode);
			अगर ((++attempts % 5) == 0)
				delay(1); /* Don't just spin the CPU */
			जाओ again;
		पूर्ण
	पूर्ण अन्यथा अणु
		xfs_ilock(ip1, xfs_lock_inumorder(ip1_mode, 1));
	पूर्ण
पूर्ण

uपूर्णांक
xfs_ip2xflags(
	काष्ठा xfs_inode	*ip)
अणु
	uपूर्णांक			flags = 0;

	अगर (ip->i_dअगरlags & XFS_DIFLAG_ANY) अणु
		अगर (ip->i_dअगरlags & XFS_DIFLAG_REALTIME)
			flags |= FS_XFLAG_REALTIME;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_PREALLOC)
			flags |= FS_XFLAG_PREALLOC;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_IMMUTABLE)
			flags |= FS_XFLAG_IMMUTABLE;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_APPEND)
			flags |= FS_XFLAG_APPEND;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_SYNC)
			flags |= FS_XFLAG_SYNC;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_NOATIME)
			flags |= FS_XFLAG_NOATIME;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_NODUMP)
			flags |= FS_XFLAG_NODUMP;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_RTINHERIT)
			flags |= FS_XFLAG_RTINHERIT;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_PROJINHERIT)
			flags |= FS_XFLAG_PROJINHERIT;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_NOSYMLINKS)
			flags |= FS_XFLAG_NOSYMLINKS;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_EXTSIZE)
			flags |= FS_XFLAG_EXTSIZE;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_EXTSZINHERIT)
			flags |= FS_XFLAG_EXTSZINHERIT;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_NODEFRAG)
			flags |= FS_XFLAG_NODEFRAG;
		अगर (ip->i_dअगरlags & XFS_DIFLAG_खाताSTREAM)
			flags |= FS_XFLAG_खाताSTREAM;
	पूर्ण

	अगर (ip->i_dअगरlags2 & XFS_DIFLAG2_ANY) अणु
		अगर (ip->i_dअगरlags2 & XFS_DIFLAG2_DAX)
			flags |= FS_XFLAG_DAX;
		अगर (ip->i_dअगरlags2 & XFS_DIFLAG2_COWEXTSIZE)
			flags |= FS_XFLAG_COWEXTSIZE;
	पूर्ण

	अगर (XFS_IFORK_Q(ip))
		flags |= FS_XFLAG_HASATTR;
	वापस flags;
पूर्ण

/*
 * Lookups up an inode from "name". If ci_name is not शून्य, then a CI match
 * is allowed, otherwise it has to be an exact match. If a CI match is found,
 * ci_name->name will poपूर्णांक to a the actual name (caller must मुक्त) or
 * will be set to शून्य अगर an exact match is found.
 */
पूर्णांक
xfs_lookup(
	xfs_inode_t		*dp,
	काष्ठा xfs_name		*name,
	xfs_inode_t		**ipp,
	काष्ठा xfs_name		*ci_name)
अणु
	xfs_ino_t		inum;
	पूर्णांक			error;

	trace_xfs_lookup(dp, name);

	अगर (XFS_FORCED_SHUTDOWN(dp->i_mount))
		वापस -EIO;

	error = xfs_dir_lookup(शून्य, dp, name, &inum, ci_name);
	अगर (error)
		जाओ out_unlock;

	error = xfs_iget(dp->i_mount, शून्य, inum, 0, 0, ipp);
	अगर (error)
		जाओ out_मुक्त_name;

	वापस 0;

out_मुक्त_name:
	अगर (ci_name)
		kmem_मुक्त(ci_name->name);
out_unlock:
	*ipp = शून्य;
	वापस error;
पूर्ण

/* Propagate di_flags from a parent inode to a child inode. */
अटल व्योम
xfs_inode_inherit_flags(
	काष्ठा xfs_inode	*ip,
	स्थिर काष्ठा xfs_inode	*pip)
अणु
	अचिन्हित पूर्णांक		di_flags = 0;
	xfs_failaddr_t		failaddr;
	umode_t			mode = VFS_I(ip)->i_mode;

	अगर (S_ISसूची(mode)) अणु
		अगर (pip->i_dअगरlags & XFS_DIFLAG_RTINHERIT)
			di_flags |= XFS_DIFLAG_RTINHERIT;
		अगर (pip->i_dअगरlags & XFS_DIFLAG_EXTSZINHERIT) अणु
			di_flags |= XFS_DIFLAG_EXTSZINHERIT;
			ip->i_extsize = pip->i_extsize;
		पूर्ण
		अगर (pip->i_dअगरlags & XFS_DIFLAG_PROJINHERIT)
			di_flags |= XFS_DIFLAG_PROJINHERIT;
	पूर्ण अन्यथा अगर (S_ISREG(mode)) अणु
		अगर ((pip->i_dअगरlags & XFS_DIFLAG_RTINHERIT) &&
		    xfs_sb_version_hasrealसमय(&ip->i_mount->m_sb))
			di_flags |= XFS_DIFLAG_REALTIME;
		अगर (pip->i_dअगरlags & XFS_DIFLAG_EXTSZINHERIT) अणु
			di_flags |= XFS_DIFLAG_EXTSIZE;
			ip->i_extsize = pip->i_extsize;
		पूर्ण
	पूर्ण
	अगर ((pip->i_dअगरlags & XFS_DIFLAG_NOATIME) &&
	    xfs_inherit_noaसमय)
		di_flags |= XFS_DIFLAG_NOATIME;
	अगर ((pip->i_dअगरlags & XFS_DIFLAG_NODUMP) &&
	    xfs_inherit_nodump)
		di_flags |= XFS_DIFLAG_NODUMP;
	अगर ((pip->i_dअगरlags & XFS_DIFLAG_SYNC) &&
	    xfs_inherit_sync)
		di_flags |= XFS_DIFLAG_SYNC;
	अगर ((pip->i_dअगरlags & XFS_DIFLAG_NOSYMLINKS) &&
	    xfs_inherit_nosymlinks)
		di_flags |= XFS_DIFLAG_NOSYMLINKS;
	अगर ((pip->i_dअगरlags & XFS_DIFLAG_NODEFRAG) &&
	    xfs_inherit_nodefrag)
		di_flags |= XFS_DIFLAG_NODEFRAG;
	अगर (pip->i_dअगरlags & XFS_DIFLAG_खाताSTREAM)
		di_flags |= XFS_DIFLAG_खाताSTREAM;

	ip->i_dअगरlags |= di_flags;

	/*
	 * Inode verअगरiers on older kernels only check that the extent size
	 * hपूर्णांक is an पूर्णांकeger multiple of the rt extent size on realसमय files.
	 * They did not check the hपूर्णांक alignment on a directory with both
	 * rtinherit and extszinherit flags set.  If the misaligned hपूर्णांक is
	 * propagated from a directory पूर्णांकo a new realसमय file, new file
	 * allocations will fail due to math errors in the rt allocator and/or
	 * trip the verअगरiers.  Validate the hपूर्णांक settings in the new file so
	 * that we करोn't let broken hपूर्णांकs propagate.
	 */
	failaddr = xfs_inode_validate_extsize(ip->i_mount, ip->i_extsize,
			VFS_I(ip)->i_mode, ip->i_dअगरlags);
	अगर (failaddr) अणु
		ip->i_dअगरlags &= ~(XFS_DIFLAG_EXTSIZE |
				   XFS_DIFLAG_EXTSZINHERIT);
		ip->i_extsize = 0;
	पूर्ण
पूर्ण

/* Propagate di_flags2 from a parent inode to a child inode. */
अटल व्योम
xfs_inode_inherit_flags2(
	काष्ठा xfs_inode	*ip,
	स्थिर काष्ठा xfs_inode	*pip)
अणु
	xfs_failaddr_t		failaddr;

	अगर (pip->i_dअगरlags2 & XFS_DIFLAG2_COWEXTSIZE) अणु
		ip->i_dअगरlags2 |= XFS_DIFLAG2_COWEXTSIZE;
		ip->i_cowextsize = pip->i_cowextsize;
	पूर्ण
	अगर (pip->i_dअगरlags2 & XFS_DIFLAG2_DAX)
		ip->i_dअगरlags2 |= XFS_DIFLAG2_DAX;

	/* Don't let invalid cowextsize hपूर्णांकs propagate. */
	failaddr = xfs_inode_validate_cowextsize(ip->i_mount, ip->i_cowextsize,
			VFS_I(ip)->i_mode, ip->i_dअगरlags, ip->i_dअगरlags2);
	अगर (failaddr) अणु
		ip->i_dअगरlags2 &= ~XFS_DIFLAG2_COWEXTSIZE;
		ip->i_cowextsize = 0;
	पूर्ण
पूर्ण

/*
 * Initialise a newly allocated inode and वापस the in-core inode to the
 * caller locked exclusively.
 */
अटल पूर्णांक
xfs_init_new_inode(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*pip,
	xfs_ino_t		ino,
	umode_t			mode,
	xfs_nlink_t		nlink,
	dev_t			rdev,
	prid_t			prid,
	bool			init_xattrs,
	काष्ठा xfs_inode	**ipp)
अणु
	काष्ठा inode		*dir = pip ? VFS_I(pip) : शून्य;
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_inode	*ip;
	अचिन्हित पूर्णांक		flags;
	पूर्णांक			error;
	काष्ठा बारpec64	tv;
	काष्ठा inode		*inode;

	/*
	 * Protect against obviously corrupt allocation btree records. Later
	 * xfs_iget checks will catch re-allocation of other active in-memory
	 * and on-disk inodes. If we करोn't catch पुनः_स्मृतिating the parent inode
	 * here we will deadlock in xfs_iget() so we have to करो these checks
	 * first.
	 */
	अगर ((pip && ino == pip->i_ino) || !xfs_verअगरy_dir_ino(mp, ino)) अणु
		xfs_alert(mp, "Allocated a known in-use inode 0x%llx!", ino);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Get the in-core inode with the lock held exclusively to prevent
	 * others from looking at until we're करोne.
	 */
	error = xfs_iget(mp, tp, ino, XFS_IGET_CREATE, XFS_ILOCK_EXCL, &ip);
	अगर (error)
		वापस error;

	ASSERT(ip != शून्य);
	inode = VFS_I(ip);
	set_nlink(inode, nlink);
	inode->i_rdev = rdev;
	ip->i_projid = prid;

	अगर (dir && !(dir->i_mode & S_ISGID) &&
	    (mp->m_flags & XFS_MOUNT_GRPID)) अणु
		inode_fsuid_set(inode, mnt_userns);
		inode->i_gid = dir->i_gid;
		inode->i_mode = mode;
	पूर्ण अन्यथा अणु
		inode_init_owner(mnt_userns, inode, dir, mode);
	पूर्ण

	/*
	 * If the group ID of the new file करोes not match the effective group
	 * ID or one of the supplementary group IDs, the S_ISGID bit is cleared
	 * (and only अगर the irix_sgid_inherit compatibility variable is set).
	 */
	अगर (irix_sgid_inherit &&
	    (inode->i_mode & S_ISGID) &&
	    !in_group_p(i_gid_पूर्णांकo_mnt(mnt_userns, inode)))
		inode->i_mode &= ~S_ISGID;

	ip->i_disk_size = 0;
	ip->i_df.अगर_nextents = 0;
	ASSERT(ip->i_nblocks == 0);

	tv = current_समय(inode);
	inode->i_mसमय = tv;
	inode->i_aसमय = tv;
	inode->i_स_समय = tv;

	ip->i_extsize = 0;
	ip->i_dअगरlags = 0;

	अगर (xfs_sb_version_has_v3inode(&mp->m_sb)) अणु
		inode_set_iversion(inode, 1);
		ip->i_cowextsize = 0;
		ip->i_crसमय = tv;
	पूर्ण

	flags = XFS_ILOG_CORE;
	चयन (mode & S_IFMT) अणु
	हाल S_IFIFO:
	हाल S_IFCHR:
	हाल S_IFBLK:
	हाल S_IFSOCK:
		ip->i_df.अगर_क्रमmat = XFS_DINODE_FMT_DEV;
		flags |= XFS_ILOG_DEV;
		अवरोध;
	हाल S_IFREG:
	हाल S_IFसूची:
		अगर (pip && (pip->i_dअगरlags & XFS_DIFLAG_ANY))
			xfs_inode_inherit_flags(ip, pip);
		अगर (pip && (pip->i_dअगरlags2 & XFS_DIFLAG2_ANY))
			xfs_inode_inherit_flags2(ip, pip);
		/* FALLTHROUGH */
	हाल S_IFLNK:
		ip->i_df.अगर_क्रमmat = XFS_DINODE_FMT_EXTENTS;
		ip->i_df.अगर_bytes = 0;
		ip->i_df.अगर_u1.अगर_root = शून्य;
		अवरोध;
	शेष:
		ASSERT(0);
	पूर्ण

	/*
	 * If we need to create attributes immediately after allocating the
	 * inode, initialise an empty attribute विभाजन right now. We use the
	 * शेष विभाजन offset क्रम attributes here as we करोn't know exactly what
	 * size or how many attributes we might be adding. We can करो this
	 * safely here because we know the data विभाजन is completely empty and
	 * this saves us from needing to run a separate transaction to set the
	 * विभाजन offset in the immediate future.
	 */
	अगर (init_xattrs && xfs_sb_version_hasattr(&mp->m_sb)) अणु
		ip->i_विभाजनoff = xfs_शेष_attroffset(ip) >> 3;
		ip->i_afp = xfs_अगरork_alloc(XFS_DINODE_FMT_EXTENTS, 0);
	पूर्ण

	/*
	 * Log the new values stuffed पूर्णांकo the inode.
	 */
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);
	xfs_trans_log_inode(tp, ip, flags);

	/* now that we have an i_mode we can setup the inode काष्ठाure */
	xfs_setup_inode(ip);

	*ipp = ip;
	वापस 0;
पूर्ण

/*
 * Allocates a new inode from disk and वापस a poपूर्णांकer to the incore copy. This
 * routine will पूर्णांकernally commit the current transaction and allocate a new one
 * अगर we needed to allocate more on-disk मुक्त inodes to perक्रमm the requested
 * operation.
 *
 * If we are allocating quota inodes, we करो not have a parent inode to attach to
 * or associate with (i.e. dp == शून्य) because they are not linked पूर्णांकo the
 * directory काष्ठाure - they are attached directly to the superblock - and so
 * have no parent.
 */
पूर्णांक
xfs_dir_ialloc(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा xfs_trans	**tpp,
	काष्ठा xfs_inode	*dp,
	umode_t			mode,
	xfs_nlink_t		nlink,
	dev_t			rdev,
	prid_t			prid,
	bool			init_xattrs,
	काष्ठा xfs_inode	**ipp)
अणु
	काष्ठा xfs_buf		*agibp;
	xfs_ino_t		parent_ino = dp ? dp->i_ino : 0;
	xfs_ino_t		ino;
	पूर्णांक			error;

	ASSERT((*tpp)->t_flags & XFS_TRANS_PERM_LOG_RES);

	/*
	 * Call the space management code to pick the on-disk inode to be
	 * allocated.
	 */
	error = xfs_dialloc_select_ag(tpp, parent_ino, mode, &agibp);
	अगर (error)
		वापस error;

	अगर (!agibp)
		वापस -ENOSPC;

	/* Allocate an inode from the selected AG */
	error = xfs_dialloc_ag(*tpp, agibp, parent_ino, &ino);
	अगर (error)
		वापस error;
	ASSERT(ino != शून्यFSINO);

	वापस xfs_init_new_inode(mnt_userns, *tpp, dp, ino, mode, nlink, rdev,
				  prid, init_xattrs, ipp);
पूर्ण

/*
 * Decrement the link count on an inode & log the change.  If this causes the
 * link count to go to zero, move the inode to AGI unlinked list so that it can
 * be मुक्तd when the last active reference goes away via xfs_inactive().
 */
अटल पूर्णांक			/* error */
xfs_droplink(
	xfs_trans_t *tp,
	xfs_inode_t *ip)
अणु
	xfs_trans_ichgसमय(tp, ip, XFS_ICHGTIME_CHG);

	drop_nlink(VFS_I(ip));
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	अगर (VFS_I(ip)->i_nlink)
		वापस 0;

	वापस xfs_iunlink(tp, ip);
पूर्ण

/*
 * Increment the link count on an inode & log the change.
 */
अटल व्योम
xfs_bumplink(
	xfs_trans_t *tp,
	xfs_inode_t *ip)
अणु
	xfs_trans_ichgसमय(tp, ip, XFS_ICHGTIME_CHG);

	inc_nlink(VFS_I(ip));
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
पूर्ण

पूर्णांक
xfs_create(
	काष्ठा user_namespace	*mnt_userns,
	xfs_inode_t		*dp,
	काष्ठा xfs_name		*name,
	umode_t			mode,
	dev_t			rdev,
	bool			init_xattrs,
	xfs_inode_t		**ipp)
अणु
	पूर्णांक			is_dir = S_ISसूची(mode);
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_inode	*ip = शून्य;
	काष्ठा xfs_trans	*tp = शून्य;
	पूर्णांक			error;
	bool                    unlock_dp_on_error = false;
	prid_t			prid;
	काष्ठा xfs_dquot	*udqp = शून्य;
	काष्ठा xfs_dquot	*gdqp = शून्य;
	काष्ठा xfs_dquot	*pdqp = शून्य;
	काष्ठा xfs_trans_res	*tres;
	uपूर्णांक			resblks;

	trace_xfs_create(dp, name);

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	prid = xfs_get_initial_prid(dp);

	/*
	 * Make sure that we have allocated dquot(s) on disk.
	 */
	error = xfs_qm_vop_dqalloc(dp, mapped_fsuid(mnt_userns),
			mapped_fsgid(mnt_userns), prid,
			XFS_QMOPT_QUOTALL | XFS_QMOPT_INHERIT,
			&udqp, &gdqp, &pdqp);
	अगर (error)
		वापस error;

	अगर (is_dir) अणु
		resblks = XFS_MKसूची_SPACE_RES(mp, name->len);
		tres = &M_RES(mp)->tr_सूची_गढ़ो;
	पूर्ण अन्यथा अणु
		resblks = XFS_CREATE_SPACE_RES(mp, name->len);
		tres = &M_RES(mp)->tr_create;
	पूर्ण

	/*
	 * Initially assume that the file करोes not exist and
	 * reserve the resources क्रम that हाल.  If that is not
	 * the हाल we'll drop the one we have and get a more
	 * appropriate transaction later.
	 */
	error = xfs_trans_alloc_icreate(mp, tres, udqp, gdqp, pdqp, resblks,
			&tp);
	अगर (error == -ENOSPC) अणु
		/* flush outstanding delalloc blocks and retry */
		xfs_flush_inodes(mp);
		error = xfs_trans_alloc_icreate(mp, tres, udqp, gdqp, pdqp,
				resblks, &tp);
	पूर्ण
	अगर (error)
		जाओ out_release_dquots;

	xfs_ilock(dp, XFS_ILOCK_EXCL | XFS_ILOCK_PARENT);
	unlock_dp_on_error = true;

	error = xfs_iext_count_may_overflow(dp, XFS_DATA_FORK,
			XFS_IEXT_सूची_MANIP_CNT(mp));
	अगर (error)
		जाओ out_trans_cancel;

	/*
	 * A newly created regular or special file just has one directory
	 * entry poपूर्णांकing to them, but a directory also the "." entry
	 * poपूर्णांकing to itself.
	 */
	error = xfs_dir_ialloc(mnt_userns, &tp, dp, mode, is_dir ? 2 : 1, rdev,
			       prid, init_xattrs, &ip);
	अगर (error)
		जाओ out_trans_cancel;

	/*
	 * Now we join the directory inode to the transaction.  We करो not करो it
	 * earlier because xfs_dir_ialloc might commit the previous transaction
	 * (and release all the locks).  An error from here on will result in
	 * the transaction cancel unlocking dp so करोn't करो it explicitly in the
	 * error path.
	 */
	xfs_trans_ijoin(tp, dp, XFS_ILOCK_EXCL);
	unlock_dp_on_error = false;

	error = xfs_dir_createname(tp, dp, name, ip->i_ino,
					resblks - XFS_IALLOC_SPACE_RES(mp));
	अगर (error) अणु
		ASSERT(error != -ENOSPC);
		जाओ out_trans_cancel;
	पूर्ण
	xfs_trans_ichgसमय(tp, dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, dp, XFS_ILOG_CORE);

	अगर (is_dir) अणु
		error = xfs_dir_init(tp, ip, dp);
		अगर (error)
			जाओ out_trans_cancel;

		xfs_bumplink(tp, dp);
	पूर्ण

	/*
	 * If this is a synchronous mount, make sure that the
	 * create transaction goes to disk beक्रमe वापसing to
	 * the user.
	 */
	अगर (mp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_सूचीSYNC))
		xfs_trans_set_sync(tp);

	/*
	 * Attach the dquot(s) to the inodes and modअगरy them incore.
	 * These ids of the inode couldn't have changed since the new
	 * inode has been locked ever since it was created.
	 */
	xfs_qm_vop_create_dqattach(tp, ip, udqp, gdqp, pdqp);

	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out_release_inode;

	xfs_qm_dqrele(udqp);
	xfs_qm_dqrele(gdqp);
	xfs_qm_dqrele(pdqp);

	*ipp = ip;
	वापस 0;

 out_trans_cancel:
	xfs_trans_cancel(tp);
 out_release_inode:
	/*
	 * Wait until after the current transaction is पातed to finish the
	 * setup of the inode and release the inode.  This prevents recursive
	 * transactions and deadlocks from xfs_inactive.
	 */
	अगर (ip) अणु
		xfs_finish_inode_setup(ip);
		xfs_irele(ip);
	पूर्ण
 out_release_dquots:
	xfs_qm_dqrele(udqp);
	xfs_qm_dqrele(gdqp);
	xfs_qm_dqrele(pdqp);

	अगर (unlock_dp_on_error)
		xfs_iunlock(dp, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

पूर्णांक
xfs_create_क्षणिक_ख(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा xfs_inode	*dp,
	umode_t			mode,
	काष्ठा xfs_inode	**ipp)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_inode	*ip = शून्य;
	काष्ठा xfs_trans	*tp = शून्य;
	पूर्णांक			error;
	prid_t                  prid;
	काष्ठा xfs_dquot	*udqp = शून्य;
	काष्ठा xfs_dquot	*gdqp = शून्य;
	काष्ठा xfs_dquot	*pdqp = शून्य;
	काष्ठा xfs_trans_res	*tres;
	uपूर्णांक			resblks;

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	prid = xfs_get_initial_prid(dp);

	/*
	 * Make sure that we have allocated dquot(s) on disk.
	 */
	error = xfs_qm_vop_dqalloc(dp, mapped_fsuid(mnt_userns),
			mapped_fsgid(mnt_userns), prid,
			XFS_QMOPT_QUOTALL | XFS_QMOPT_INHERIT,
			&udqp, &gdqp, &pdqp);
	अगर (error)
		वापस error;

	resblks = XFS_IALLOC_SPACE_RES(mp);
	tres = &M_RES(mp)->tr_create_क्षणिक_ख;

	error = xfs_trans_alloc_icreate(mp, tres, udqp, gdqp, pdqp, resblks,
			&tp);
	अगर (error)
		जाओ out_release_dquots;

	error = xfs_dir_ialloc(mnt_userns, &tp, dp, mode, 0, 0, prid,
				false, &ip);
	अगर (error)
		जाओ out_trans_cancel;

	अगर (mp->m_flags & XFS_MOUNT_WSYNC)
		xfs_trans_set_sync(tp);

	/*
	 * Attach the dquot(s) to the inodes and modअगरy them incore.
	 * These ids of the inode couldn't have changed since the new
	 * inode has been locked ever since it was created.
	 */
	xfs_qm_vop_create_dqattach(tp, ip, udqp, gdqp, pdqp);

	error = xfs_iunlink(tp, ip);
	अगर (error)
		जाओ out_trans_cancel;

	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out_release_inode;

	xfs_qm_dqrele(udqp);
	xfs_qm_dqrele(gdqp);
	xfs_qm_dqrele(pdqp);

	*ipp = ip;
	वापस 0;

 out_trans_cancel:
	xfs_trans_cancel(tp);
 out_release_inode:
	/*
	 * Wait until after the current transaction is पातed to finish the
	 * setup of the inode and release the inode.  This prevents recursive
	 * transactions and deadlocks from xfs_inactive.
	 */
	अगर (ip) अणु
		xfs_finish_inode_setup(ip);
		xfs_irele(ip);
	पूर्ण
 out_release_dquots:
	xfs_qm_dqrele(udqp);
	xfs_qm_dqrele(gdqp);
	xfs_qm_dqrele(pdqp);

	वापस error;
पूर्ण

पूर्णांक
xfs_link(
	xfs_inode_t		*tdp,
	xfs_inode_t		*sip,
	काष्ठा xfs_name		*target_name)
अणु
	xfs_mount_t		*mp = tdp->i_mount;
	xfs_trans_t		*tp;
	पूर्णांक			error;
	पूर्णांक			resblks;

	trace_xfs_link(tdp, target_name);

	ASSERT(!S_ISसूची(VFS_I(sip)->i_mode));

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	error = xfs_qm_dqattach(sip);
	अगर (error)
		जाओ std_वापस;

	error = xfs_qm_dqattach(tdp);
	अगर (error)
		जाओ std_वापस;

	resblks = XFS_LINK_SPACE_RES(mp, target_name->len);
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_link, resblks, 0, 0, &tp);
	अगर (error == -ENOSPC) अणु
		resblks = 0;
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_link, 0, 0, 0, &tp);
	पूर्ण
	अगर (error)
		जाओ std_वापस;

	xfs_lock_two_inodes(sip, XFS_ILOCK_EXCL, tdp, XFS_ILOCK_EXCL);

	xfs_trans_ijoin(tp, sip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, tdp, XFS_ILOCK_EXCL);

	error = xfs_iext_count_may_overflow(tdp, XFS_DATA_FORK,
			XFS_IEXT_सूची_MANIP_CNT(mp));
	अगर (error)
		जाओ error_वापस;

	/*
	 * If we are using project inheritance, we only allow hard link
	 * creation in our tree when the project IDs are the same; अन्यथा
	 * the tree quota mechanism could be circumvented.
	 */
	अगर (unlikely((tdp->i_dअगरlags & XFS_DIFLAG_PROJINHERIT) &&
		     tdp->i_projid != sip->i_projid)) अणु
		error = -EXDEV;
		जाओ error_वापस;
	पूर्ण

	अगर (!resblks) अणु
		error = xfs_dir_canenter(tp, tdp, target_name);
		अगर (error)
			जाओ error_वापस;
	पूर्ण

	/*
	 * Handle initial link state of O_TMPखाता inode
	 */
	अगर (VFS_I(sip)->i_nlink == 0) अणु
		error = xfs_iunlink_हटाओ(tp, sip);
		अगर (error)
			जाओ error_वापस;
	पूर्ण

	error = xfs_dir_createname(tp, tdp, target_name, sip->i_ino,
				   resblks);
	अगर (error)
		जाओ error_वापस;
	xfs_trans_ichgसमय(tp, tdp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, tdp, XFS_ILOG_CORE);

	xfs_bumplink(tp, sip);

	/*
	 * If this is a synchronous mount, make sure that the
	 * link transaction goes to disk beक्रमe वापसing to
	 * the user.
	 */
	अगर (mp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_सूचीSYNC))
		xfs_trans_set_sync(tp);

	वापस xfs_trans_commit(tp);

 error_वापस:
	xfs_trans_cancel(tp);
 std_वापस:
	वापस error;
पूर्ण

/* Clear the reflink flag and the cowblocks tag अगर possible. */
अटल व्योम
xfs_itruncate_clear_reflink_flags(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_अगरork	*dविभाजन;
	काष्ठा xfs_अगरork	*cविभाजन;

	अगर (!xfs_is_reflink_inode(ip))
		वापस;
	dविभाजन = XFS_IFORK_PTR(ip, XFS_DATA_FORK);
	cविभाजन = XFS_IFORK_PTR(ip, XFS_COW_FORK);
	अगर (dविभाजन->अगर_bytes == 0 && cविभाजन->अगर_bytes == 0)
		ip->i_dअगरlags2 &= ~XFS_DIFLAG2_REFLINK;
	अगर (cविभाजन->अगर_bytes == 0)
		xfs_inode_clear_cowblocks_tag(ip);
पूर्ण

/*
 * Free up the underlying blocks past new_size.  The new size must be smaller
 * than the current size.  This routine can be used both क्रम the attribute and
 * data विभाजन, and करोes not modअगरy the inode size, which is left to the caller.
 *
 * The transaction passed to this routine must have made a permanent log
 * reservation of at least XFS_ITRUNCATE_LOG_RES.  This routine may commit the
 * given transaction and start new ones, so make sure everything involved in
 * the transaction is tidy beक्रमe calling here.  Some transaction will be
 * वापसed to the caller to be committed.  The incoming transaction must
 * alपढ़ोy include the inode, and both inode locks must be held exclusively.
 * The inode must also be "held" within the transaction.  On वापस the inode
 * will be "held" within the वापसed transaction.  This routine करोes NOT
 * require any disk space to be reserved क्रम it within the transaction.
 *
 * If we get an error, we must वापस with the inode locked and linked पूर्णांकo the
 * current transaction. This keeps things simple क्रम the higher level code,
 * because it always knows that the inode is locked and held in the transaction
 * that वापसs to it whether errors occur or not.  We करोn't mark the inode
 * dirty on error so that transactions can be easily पातed अगर possible.
 */
पूर्णांक
xfs_itruncate_extents_flags(
	काष्ठा xfs_trans	**tpp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			whichविभाजन,
	xfs_fमाप_प्रकार		new_size,
	पूर्णांक			flags)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp = *tpp;
	xfs_fileoff_t		first_unmap_block;
	xfs_filblks_t		unmap_len;
	पूर्णांक			error = 0;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(!atomic_पढ़ो(&VFS_I(ip)->i_count) ||
	       xfs_isilocked(ip, XFS_IOLOCK_EXCL));
	ASSERT(new_size <= XFS_ISIZE(ip));
	ASSERT(tp->t_flags & XFS_TRANS_PERM_LOG_RES);
	ASSERT(ip->i_itemp != शून्य);
	ASSERT(ip->i_itemp->ili_lock_flags == 0);
	ASSERT(!XFS_NOT_DQATTACHED(mp, ip));

	trace_xfs_itruncate_extents_start(ip, new_size);

	flags |= xfs_bmapi_aflag(whichविभाजन);

	/*
	 * Since it is possible क्रम space to become allocated beyond
	 * the end of the file (in a crash where the space is allocated
	 * but the inode size is not yet updated), simply हटाओ any
	 * blocks which show up between the new खातापूर्ण and the maximum
	 * possible file size.
	 *
	 * We have to मुक्त all the blocks to the bmbt maximum offset, even अगर
	 * the page cache can't scale that far.
	 */
	first_unmap_block = XFS_B_TO_FSB(mp, (xfs_ufमाप_प्रकार)new_size);
	अगर (!xfs_verअगरy_fileoff(mp, first_unmap_block)) अणु
		WARN_ON_ONCE(first_unmap_block > XFS_MAX_खाताOFF);
		वापस 0;
	पूर्ण

	unmap_len = XFS_MAX_खाताOFF - first_unmap_block + 1;
	जबतक (unmap_len > 0) अणु
		ASSERT(tp->t_firstblock == शून्यFSBLOCK);
		error = __xfs_bunmapi(tp, ip, first_unmap_block, &unmap_len,
				flags, XFS_ITRUNC_MAX_EXTENTS);
		अगर (error)
			जाओ out;

		/* मुक्त the just unmapped extents */
		error = xfs_defer_finish(&tp);
		अगर (error)
			जाओ out;
	पूर्ण

	अगर (whichविभाजन == XFS_DATA_FORK) अणु
		/* Remove all pending CoW reservations. */
		error = xfs_reflink_cancel_cow_blocks(ip, &tp,
				first_unmap_block, XFS_MAX_खाताOFF, true);
		अगर (error)
			जाओ out;

		xfs_itruncate_clear_reflink_flags(ip);
	पूर्ण

	/*
	 * Always re-log the inode so that our permanent transaction can keep
	 * on rolling it क्रमward in the log.
	 */
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	trace_xfs_itruncate_extents_end(ip, new_size);

out:
	*tpp = tp;
	वापस error;
पूर्ण

पूर्णांक
xfs_release(
	xfs_inode_t	*ip)
अणु
	xfs_mount_t	*mp = ip->i_mount;
	पूर्णांक		error = 0;

	अगर (!S_ISREG(VFS_I(ip)->i_mode) || (VFS_I(ip)->i_mode == 0))
		वापस 0;

	/* If this is a पढ़ो-only mount, करोn't करो this (would generate I/O) */
	अगर (mp->m_flags & XFS_MOUNT_RDONLY)
		वापस 0;

	अगर (!XFS_FORCED_SHUTDOWN(mp)) अणु
		पूर्णांक truncated;

		/*
		 * If we previously truncated this file and हटाओd old data
		 * in the process, we want to initiate "early" ग_लिखोout on
		 * the last बंद.  This is an attempt to combat the notorious
		 * शून्य files problem which is particularly noticeable from a
		 * truncate करोwn, buffered (re-)ग_लिखो (delalloc), followed by
		 * a crash.  What we are effectively करोing here is
		 * signअगरicantly reducing the समय winकरोw where we'd otherwise
		 * be exposed to that problem.
		 */
		truncated = xfs_अगरlags_test_and_clear(ip, XFS_ITRUNCATED);
		अगर (truncated) अणु
			xfs_अगरlags_clear(ip, XFS_IसूचीTY_RELEASE);
			अगर (ip->i_delayed_blks > 0) अणु
				error = filemap_flush(VFS_I(ip)->i_mapping);
				अगर (error)
					वापस error;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (VFS_I(ip)->i_nlink == 0)
		वापस 0;

	/*
	 * If we can't get the iolock just skip truncating the blocks past खातापूर्ण
	 * because we could deadlock with the mmap_lock otherwise. We'll get
	 * another chance to drop them once the last reference to the inode is
	 * dropped, so we'll never leak blocks permanently.
	 */
	अगर (!xfs_ilock_noरुको(ip, XFS_IOLOCK_EXCL))
		वापस 0;

	अगर (xfs_can_मुक्त_eofblocks(ip, false)) अणु
		/*
		 * Check अगर the inode is being खोलोed, written and बंदd
		 * frequently and we have delayed allocation blocks outstanding
		 * (e.g. streaming ग_लिखोs from the NFS server), truncating the
		 * blocks past खातापूर्ण will cause fragmentation to occur.
		 *
		 * In this हाल करोn't करो the truncation, but we have to be
		 * careful how we detect this हाल. Blocks beyond खातापूर्ण show up as
		 * i_delayed_blks even when the inode is clean, so we need to
		 * truncate them away first beक्रमe checking क्रम a dirty release.
		 * Hence on the first dirty बंद we will still हटाओ the
		 * speculative allocation, but after that we will leave it in
		 * place.
		 */
		अगर (xfs_अगरlags_test(ip, XFS_IसूचीTY_RELEASE))
			जाओ out_unlock;

		error = xfs_मुक्त_eofblocks(ip);
		अगर (error)
			जाओ out_unlock;

		/* delalloc blocks after truncation means it really is dirty */
		अगर (ip->i_delayed_blks)
			xfs_अगरlags_set(ip, XFS_IसूचीTY_RELEASE);
	पूर्ण

out_unlock:
	xfs_iunlock(ip, XFS_IOLOCK_EXCL);
	वापस error;
पूर्ण

/*
 * xfs_inactive_truncate
 *
 * Called to perक्रमm a truncate when an inode becomes unlinked.
 */
STATIC पूर्णांक
xfs_inactive_truncate(
	काष्ठा xfs_inode *ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate, 0, 0, 0, &tp);
	अगर (error) अणु
		ASSERT(XFS_FORCED_SHUTDOWN(mp));
		वापस error;
	पूर्ण
	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	/*
	 * Log the inode size first to prevent stale data exposure in the event
	 * of a प्रणाली crash beक्रमe the truncate completes. See the related
	 * comment in xfs_vn_setattr_size() क्रम details.
	 */
	ip->i_disk_size = 0;
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	error = xfs_itruncate_extents(&tp, ip, XFS_DATA_FORK, 0);
	अगर (error)
		जाओ error_trans_cancel;

	ASSERT(ip->i_df.अगर_nextents == 0);

	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ error_unlock;

	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस 0;

error_trans_cancel:
	xfs_trans_cancel(tp);
error_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * xfs_inactive_अगरree()
 *
 * Perक्रमm the inode मुक्त when an inode is unlinked.
 */
STATIC पूर्णांक
xfs_inactive_अगरree(
	काष्ठा xfs_inode *ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	/*
	 * We try to use a per-AG reservation क्रम any block needed by the finobt
	 * tree, but as the finobt feature predates the per-AG reservation
	 * support a degraded file प्रणाली might not have enough space क्रम the
	 * reservation at mount समय.  In that हाल try to dip पूर्णांकo the reserved
	 * pool and pray.
	 *
	 * Send a warning अगर the reservation करोes happen to fail, as the inode
	 * now reमुख्यs allocated and sits on the unlinked list until the fs is
	 * repaired.
	 */
	अगर (unlikely(mp->m_finobt_nores)) अणु
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_अगरree,
				XFS_IFREE_SPACE_RES(mp), 0, XFS_TRANS_RESERVE,
				&tp);
	पूर्ण अन्यथा अणु
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_अगरree, 0, 0, 0, &tp);
	पूर्ण
	अगर (error) अणु
		अगर (error == -ENOSPC) अणु
			xfs_warn_ratelimited(mp,
			"Failed to remove inode(s) from unlinked list. "
			"Please free space, unmount and run xfs_repair.");
		पूर्ण अन्यथा अणु
			ASSERT(XFS_FORCED_SHUTDOWN(mp));
		पूर्ण
		वापस error;
	पूर्ण

	/*
	 * We करो not hold the inode locked across the entire rolling transaction
	 * here. We only need to hold it क्रम the first transaction that
	 * xfs_अगरree() builds, which may mark the inode XFS_ISTALE अगर the
	 * underlying cluster buffer is मुक्तd. Relogging an XFS_ISTALE inode
	 * here अवरोधs the relationship between cluster buffer invalidation and
	 * stale inode invalidation on cluster buffer item journal commit
	 * completion, and can result in leaving dirty stale inodes hanging
	 * around in memory.
	 *
	 * We have no need क्रम serialising this inode operation against other
	 * operations - we मुक्तd the inode and hence पुनः_स्मृतिation is required
	 * and that will serialise on पुनः_स्मृतिating the space the deferops need
	 * to मुक्त. Hence we can unlock the inode on the first commit of
	 * the transaction rather than roll it right through the deferops. This
	 * aव्योमs relogging the XFS_ISTALE inode.
	 *
	 * We check that xfs_अगरree() hasn't grown an पूर्णांकernal transaction roll
	 * by निश्चितing that the inode is still locked when it वापसs.
	 */
	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);

	error = xfs_अगरree(tp, ip);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	अगर (error) अणु
		/*
		 * If we fail to मुक्त the inode, shut करोwn.  The cancel
		 * might करो that, we need to make sure.  Otherwise the
		 * inode might be lost क्रम a दीर्घ समय or क्रमever.
		 */
		अगर (!XFS_FORCED_SHUTDOWN(mp)) अणु
			xfs_notice(mp, "%s: xfs_ifree returned error %d",
				__func__, error);
			xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_META_IO_ERROR);
		पूर्ण
		xfs_trans_cancel(tp);
		वापस error;
	पूर्ण

	/*
	 * Credit the quota account(s). The inode is gone.
	 */
	xfs_trans_mod_dquot_byino(tp, ip, XFS_TRANS_DQ_ICOUNT, -1);

	/*
	 * Just ignore errors at this poपूर्णांक.  There is nothing we can करो except
	 * to try to keep going. Make sure it's not a silent error.
	 */
	error = xfs_trans_commit(tp);
	अगर (error)
		xfs_notice(mp, "%s: xfs_trans_commit returned error %d",
			__func__, error);

	वापस 0;
पूर्ण

/*
 * xfs_inactive
 *
 * This is called when the vnode reference count क्रम the vnode
 * goes to zero.  If the file has been unlinked, then it must
 * now be truncated.  Also, we clear all of the पढ़ो-ahead state
 * kept क्रम the inode here since the file is now बंदd.
 */
व्योम
xfs_inactive(
	xfs_inode_t	*ip)
अणु
	काष्ठा xfs_mount	*mp;
	पूर्णांक			error;
	पूर्णांक			truncate = 0;

	/*
	 * If the inode is alपढ़ोy मुक्त, then there can be nothing
	 * to clean up here.
	 */
	अगर (VFS_I(ip)->i_mode == 0) अणु
		ASSERT(ip->i_df.अगर_broot_bytes == 0);
		वापस;
	पूर्ण

	mp = ip->i_mount;
	ASSERT(!xfs_अगरlags_test(ip, XFS_IRECOVERY));

	/* If this is a पढ़ो-only mount, करोn't करो this (would generate I/O) */
	अगर (mp->m_flags & XFS_MOUNT_RDONLY)
		वापस;

	/* Metadata inodes require explicit resource cleanup. */
	अगर (xfs_is_metadata_inode(ip))
		वापस;

	/* Try to clean out the cow blocks अगर there are any. */
	अगर (xfs_inode_has_cow_data(ip))
		xfs_reflink_cancel_cow_range(ip, 0, शून्यखाताOFF, true);

	अगर (VFS_I(ip)->i_nlink != 0) अणु
		/*
		 * क्रमce is true because we are evicting an inode from the
		 * cache. Post-eof blocks must be मुक्तd, lest we end up with
		 * broken मुक्त space accounting.
		 *
		 * Note: करोn't bother with iolock here since lockdep complains
		 * about acquiring it in reclaim context. We have the only
		 * reference to the inode at this poपूर्णांक anyways.
		 */
		अगर (xfs_can_मुक्त_eofblocks(ip, true))
			xfs_मुक्त_eofblocks(ip);

		वापस;
	पूर्ण

	अगर (S_ISREG(VFS_I(ip)->i_mode) &&
	    (ip->i_disk_size != 0 || XFS_ISIZE(ip) != 0 ||
	     ip->i_df.अगर_nextents > 0 || ip->i_delayed_blks > 0))
		truncate = 1;

	error = xfs_qm_dqattach(ip);
	अगर (error)
		वापस;

	अगर (S_ISLNK(VFS_I(ip)->i_mode))
		error = xfs_inactive_symlink(ip);
	अन्यथा अगर (truncate)
		error = xfs_inactive_truncate(ip);
	अगर (error)
		वापस;

	/*
	 * If there are attributes associated with the file then blow them away
	 * now.  The code calls a routine that recursively deस्थिरructs the
	 * attribute विभाजन. If also blows away the in-core attribute विभाजन.
	 */
	अगर (XFS_IFORK_Q(ip)) अणु
		error = xfs_attr_inactive(ip);
		अगर (error)
			वापस;
	पूर्ण

	ASSERT(!ip->i_afp);
	ASSERT(ip->i_विभाजनoff == 0);

	/*
	 * Free the inode.
	 */
	error = xfs_inactive_अगरree(ip);
	अगर (error)
		वापस;

	/*
	 * Release the dquots held by inode, अगर any.
	 */
	xfs_qm_dqdetach(ip);
पूर्ण

/*
 * In-Core Unlinked List Lookups
 * =============================
 *
 * Every inode is supposed to be reachable from some other piece of metadata
 * with the exception of the root directory.  Inodes with a connection to a
 * file descriptor but not linked from anywhere in the on-disk directory tree
 * are collectively known as unlinked inodes, though the fileप्रणाली itself
 * मुख्यtains links to these inodes so that on-disk metadata are consistent.
 *
 * XFS implements a per-AG on-disk hash table of unlinked inodes.  The AGI
 * header contains a number of buckets that poपूर्णांक to an inode, and each inode
 * record has a poपूर्णांकer to the next inode in the hash chain.  This
 * singly-linked list causes scaling problems in the iunlink हटाओ function
 * because we must walk that list to find the inode that poपूर्णांकs to the inode
 * being हटाओd from the unlinked hash bucket list.
 *
 * What अगर we modelled the unlinked list as a collection of records capturing
 * "X.next_unlinked = Y" relations?  If we indexed those records on Y, we'd
 * have a fast way to look up unlinked list predecessors, which aव्योमs the
 * slow list walk.  That's exactly what we करो here (in-core) with a per-AG
 * rhashtable.
 *
 * Because this is a backref cache, we ignore operational failures since the
 * iunlink code can fall back to the slow bucket walk.  The only errors that
 * should bubble out are क्रम obviously incorrect situations.
 *
 * All users of the backref cache MUST hold the AGI buffer lock to serialize
 * access or have otherwise provided क्रम concurrency control.
 */

/* Capture a "X.next_unlinked = Y" relationship. */
काष्ठा xfs_iunlink अणु
	काष्ठा rhash_head	iu_rhash_head;
	xfs_agino_t		iu_agino;		/* X */
	xfs_agino_t		iu_next_unlinked;	/* Y */
पूर्ण;

/* Unlinked list predecessor lookup hashtable स्थिरruction */
अटल पूर्णांक
xfs_iunlink_obj_cmpfn(
	काष्ठा rhashtable_compare_arg	*arg,
	स्थिर व्योम			*obj)
अणु
	स्थिर xfs_agino_t		*key = arg->key;
	स्थिर काष्ठा xfs_iunlink	*iu = obj;

	अगर (iu->iu_next_unlinked != *key)
		वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params xfs_iunlink_hash_params = अणु
	.min_size		= XFS_AGI_UNLINKED_BUCKETS,
	.key_len		= माप(xfs_agino_t),
	.key_offset		= दुरत्व(काष्ठा xfs_iunlink,
					   iu_next_unlinked),
	.head_offset		= दुरत्व(काष्ठा xfs_iunlink, iu_rhash_head),
	.स्वतःmatic_shrinking	= true,
	.obj_cmpfn		= xfs_iunlink_obj_cmpfn,
पूर्ण;

/*
 * Return X, where X.next_unlinked == @agino.  Returns शून्यAGINO अगर no such
 * relation is found.
 */
अटल xfs_agino_t
xfs_iunlink_lookup_backref(
	काष्ठा xfs_perag	*pag,
	xfs_agino_t		agino)
अणु
	काष्ठा xfs_iunlink	*iu;

	iu = rhashtable_lookup_fast(&pag->pagi_unlinked_hash, &agino,
			xfs_iunlink_hash_params);
	वापस iu ? iu->iu_agino : शून्यAGINO;
पूर्ण

/*
 * Take ownership of an iunlink cache entry and insert it पूर्णांकo the hash table.
 * If successful, the entry will be owned by the cache; अगर not, it is मुक्तd.
 * Either way, the caller करोes not own @iu after this call.
 */
अटल पूर्णांक
xfs_iunlink_insert_backref(
	काष्ठा xfs_perag	*pag,
	काष्ठा xfs_iunlink	*iu)
अणु
	पूर्णांक			error;

	error = rhashtable_insert_fast(&pag->pagi_unlinked_hash,
			&iu->iu_rhash_head, xfs_iunlink_hash_params);
	/*
	 * Fail loudly अगर there alपढ़ोy was an entry because that's a sign of
	 * corruption of in-memory data.  Also fail loudly अगर we see an error
	 * code we didn't anticipate from the rhashtable code.  Currently we
	 * only anticipate ENOMEM.
	 */
	अगर (error) अणु
		WARN(error != -ENOMEM, "iunlink cache insert error %d", error);
		kmem_मुक्त(iu);
	पूर्ण
	/*
	 * Absorb any runसमय errors that aren't a result of corruption because
	 * this is a cache and we can always fall back to bucket list scanning.
	 */
	अगर (error != 0 && error != -EEXIST)
		error = 0;
	वापस error;
पूर्ण

/* Remember that @prev_agino.next_unlinked = @this_agino. */
अटल पूर्णांक
xfs_iunlink_add_backref(
	काष्ठा xfs_perag	*pag,
	xfs_agino_t		prev_agino,
	xfs_agino_t		this_agino)
अणु
	काष्ठा xfs_iunlink	*iu;

	अगर (XFS_TEST_ERROR(false, pag->pag_mount, XFS_ERRTAG_IUNLINK_FALLBACK))
		वापस 0;

	iu = kmem_zalloc(माप(*iu), KM_NOFS);
	iu->iu_agino = prev_agino;
	iu->iu_next_unlinked = this_agino;

	वापस xfs_iunlink_insert_backref(pag, iu);
पूर्ण

/*
 * Replace X.next_unlinked = @agino with X.next_unlinked = @next_unlinked.
 * If @next_unlinked is शून्यAGINO, we drop the backref and निकास.  If there
 * wasn't any such entry then we don't bother.
 */
अटल पूर्णांक
xfs_iunlink_change_backref(
	काष्ठा xfs_perag	*pag,
	xfs_agino_t		agino,
	xfs_agino_t		next_unlinked)
अणु
	काष्ठा xfs_iunlink	*iu;
	पूर्णांक			error;

	/* Look up the old entry; अगर there wasn't one then निकास. */
	iu = rhashtable_lookup_fast(&pag->pagi_unlinked_hash, &agino,
			xfs_iunlink_hash_params);
	अगर (!iu)
		वापस 0;

	/*
	 * Remove the entry.  This shouldn't ever वापस an error, but अगर we
	 * couldn't remove the old entry we don't want to add it again to the
	 * hash table, and अगर the entry disappeared on us then someone's
	 * violated the locking rules and we need to fail loudly.  Either way
	 * we cannot हटाओ the inode because पूर्णांकernal state is or would have
	 * been corrupt.
	 */
	error = rhashtable_हटाओ_fast(&pag->pagi_unlinked_hash,
			&iu->iu_rhash_head, xfs_iunlink_hash_params);
	अगर (error)
		वापस error;

	/* If there is no new next entry just मुक्त our item and वापस. */
	अगर (next_unlinked == शून्यAGINO) अणु
		kmem_मुक्त(iu);
		वापस 0;
	पूर्ण

	/* Update the entry and re-add it to the hash table. */
	iu->iu_next_unlinked = next_unlinked;
	वापस xfs_iunlink_insert_backref(pag, iu);
पूर्ण

/* Set up the in-core predecessor काष्ठाures. */
पूर्णांक
xfs_iunlink_init(
	काष्ठा xfs_perag	*pag)
अणु
	वापस rhashtable_init(&pag->pagi_unlinked_hash,
			&xfs_iunlink_hash_params);
पूर्ण

/* Free the in-core predecessor काष्ठाures. */
अटल व्योम
xfs_iunlink_मुक्त_item(
	व्योम			*ptr,
	व्योम			*arg)
अणु
	काष्ठा xfs_iunlink	*iu = ptr;
	bool			*मुक्तd_anything = arg;

	*मुक्तd_anything = true;
	kmem_मुक्त(iu);
पूर्ण

व्योम
xfs_iunlink_destroy(
	काष्ठा xfs_perag	*pag)
अणु
	bool			मुक्तd_anything = false;

	rhashtable_मुक्त_and_destroy(&pag->pagi_unlinked_hash,
			xfs_iunlink_मुक्त_item, &मुक्तd_anything);

	ASSERT(मुक्तd_anything == false || XFS_FORCED_SHUTDOWN(pag->pag_mount));
पूर्ण

/*
 * Poपूर्णांक the AGI unlinked bucket at an inode and log the results.  The caller
 * is responsible क्रम validating the old value.
 */
STATIC पूर्णांक
xfs_iunlink_update_bucket(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	काष्ठा xfs_buf		*agibp,
	अचिन्हित पूर्णांक		bucket_index,
	xfs_agino_t		new_agino)
अणु
	काष्ठा xfs_agi		*agi = agibp->b_addr;
	xfs_agino_t		old_value;
	पूर्णांक			offset;

	ASSERT(xfs_verअगरy_agino_or_null(tp->t_mountp, agno, new_agino));

	old_value = be32_to_cpu(agi->agi_unlinked[bucket_index]);
	trace_xfs_iunlink_update_bucket(tp->t_mountp, agno, bucket_index,
			old_value, new_agino);

	/*
	 * We should never find the head of the list alपढ़ोy set to the value
	 * passed in because either we're adding or removing ourselves from the
	 * head of the list.
	 */
	अगर (old_value == new_agino) अणु
		xfs_buf_mark_corrupt(agibp);
		वापस -EFSCORRUPTED;
	पूर्ण

	agi->agi_unlinked[bucket_index] = cpu_to_be32(new_agino);
	offset = दुरत्व(काष्ठा xfs_agi, agi_unlinked) +
			(माप(xfs_agino_t) * bucket_index);
	xfs_trans_log_buf(tp, agibp, offset, offset + माप(xfs_agino_t) - 1);
	वापस 0;
पूर्ण

/* Set an on-disk inode's next_unlinked poपूर्णांकer. */
STATIC व्योम
xfs_iunlink_update_dinode(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agino_t		agino,
	काष्ठा xfs_buf		*ibp,
	काष्ठा xfs_dinode	*dip,
	काष्ठा xfs_imap		*imap,
	xfs_agino_t		next_agino)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	पूर्णांक			offset;

	ASSERT(xfs_verअगरy_agino_or_null(mp, agno, next_agino));

	trace_xfs_iunlink_update_dinode(mp, agno, agino,
			be32_to_cpu(dip->di_next_unlinked), next_agino);

	dip->di_next_unlinked = cpu_to_be32(next_agino);
	offset = imap->im_boffset +
			दुरत्व(काष्ठा xfs_dinode, di_next_unlinked);

	/* need to recalc the inode CRC अगर appropriate */
	xfs_dinode_calc_crc(mp, dip);
	xfs_trans_inode_buf(tp, ibp);
	xfs_trans_log_buf(tp, ibp, offset, offset + माप(xfs_agino_t) - 1);
पूर्ण

/* Set an in-core inode's unlinked poपूर्णांकer and वापस the old value. */
STATIC पूर्णांक
xfs_iunlink_update_inode(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	xfs_agnumber_t		agno,
	xfs_agino_t		next_agino,
	xfs_agino_t		*old_next_agino)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_dinode	*dip;
	काष्ठा xfs_buf		*ibp;
	xfs_agino_t		old_value;
	पूर्णांक			error;

	ASSERT(xfs_verअगरy_agino_or_null(mp, agno, next_agino));

	error = xfs_imap_to_bp(mp, tp, &ip->i_imap, &ibp);
	अगर (error)
		वापस error;
	dip = xfs_buf_offset(ibp, ip->i_imap.im_boffset);

	/* Make sure the old poपूर्णांकer isn't garbage. */
	old_value = be32_to_cpu(dip->di_next_unlinked);
	अगर (!xfs_verअगरy_agino_or_null(mp, agno, old_value)) अणु
		xfs_inode_verअगरier_error(ip, -EFSCORRUPTED, __func__, dip,
				माप(*dip), __this_address);
		error = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	/*
	 * Since we're updating a linked list, we should never find that the
	 * current poपूर्णांकer is the same as the new value, unless we're
	 * terminating the list.
	 */
	*old_next_agino = old_value;
	अगर (old_value == next_agino) अणु
		अगर (next_agino != शून्यAGINO) अणु
			xfs_inode_verअगरier_error(ip, -EFSCORRUPTED, __func__,
					dip, माप(*dip), __this_address);
			error = -EFSCORRUPTED;
		पूर्ण
		जाओ out;
	पूर्ण

	/* Ok, update the new poपूर्णांकer. */
	xfs_iunlink_update_dinode(tp, agno, XFS_INO_TO_AGINO(mp, ip->i_ino),
			ibp, dip, &ip->i_imap, next_agino);
	वापस 0;
out:
	xfs_trans_brअन्यथा(tp, ibp);
	वापस error;
पूर्ण

/*
 * This is called when the inode's link count has gone to 0 or we are creating
 * a क्षणिक_ख via O_TMPखाता.  The inode @ip must have nlink == 0.
 *
 * We place the on-disk inode on a list in the AGI.  It will be pulled from this
 * list when the inode is मुक्तd.
 */
STATIC पूर्णांक
xfs_iunlink(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_agi		*agi;
	काष्ठा xfs_buf		*agibp;
	xfs_agino_t		next_agino;
	xfs_agnumber_t		agno = XFS_INO_TO_AGNO(mp, ip->i_ino);
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ip->i_ino);
	लघु			bucket_index = agino % XFS_AGI_UNLINKED_BUCKETS;
	पूर्णांक			error;

	ASSERT(VFS_I(ip)->i_nlink == 0);
	ASSERT(VFS_I(ip)->i_mode != 0);
	trace_xfs_iunlink(ip);

	/* Get the agi buffer first.  It ensures lock ordering on the list. */
	error = xfs_पढ़ो_agi(mp, tp, agno, &agibp);
	अगर (error)
		वापस error;
	agi = agibp->b_addr;

	/*
	 * Get the index पूर्णांकo the agi hash table क्रम the list this inode will
	 * go on.  Make sure the poपूर्णांकer isn't garbage and that this inode
	 * isn't alपढ़ोy on the list.
	 */
	next_agino = be32_to_cpu(agi->agi_unlinked[bucket_index]);
	अगर (next_agino == agino ||
	    !xfs_verअगरy_agino_or_null(mp, agno, next_agino)) अणु
		xfs_buf_mark_corrupt(agibp);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (next_agino != शून्यAGINO) अणु
		xfs_agino_t		old_agino;

		/*
		 * There is alपढ़ोy another inode in the bucket, so poपूर्णांक this
		 * inode to the current head of the list.
		 */
		error = xfs_iunlink_update_inode(tp, ip, agno, next_agino,
				&old_agino);
		अगर (error)
			वापस error;
		ASSERT(old_agino == शून्यAGINO);

		/*
		 * agino has been unlinked, add a backref from the next inode
		 * back to agino.
		 */
		error = xfs_iunlink_add_backref(agibp->b_pag, agino, next_agino);
		अगर (error)
			वापस error;
	पूर्ण

	/* Poपूर्णांक the head of the list to poपूर्णांक to this inode. */
	वापस xfs_iunlink_update_bucket(tp, agno, agibp, bucket_index, agino);
पूर्ण

/* Return the imap, dinode poपूर्णांकer, and buffer क्रम an inode. */
STATIC पूर्णांक
xfs_iunlink_map_ino(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agino_t		agino,
	काष्ठा xfs_imap		*imap,
	काष्ठा xfs_dinode	**dipp,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	पूर्णांक			error;

	imap->im_blkno = 0;
	error = xfs_imap(mp, tp, XFS_AGINO_TO_INO(mp, agno, agino), imap, 0);
	अगर (error) अणु
		xfs_warn(mp, "%s: xfs_imap returned error %d.",
				__func__, error);
		वापस error;
	पूर्ण

	error = xfs_imap_to_bp(mp, tp, imap, bpp);
	अगर (error) अणु
		xfs_warn(mp, "%s: xfs_imap_to_bp returned error %d.",
				__func__, error);
		वापस error;
	पूर्ण

	*dipp = xfs_buf_offset(*bpp, imap->im_boffset);
	वापस 0;
पूर्ण

/*
 * Walk the unlinked chain from @head_agino until we find the inode that
 * poपूर्णांकs to @target_agino.  Return the inode number, map, dinode poपूर्णांकer,
 * and inode cluster buffer of that inode as @agino, @imap, @dipp, and @bpp.
 *
 * @tp, @pag, @head_agino, and @target_agino are input parameters.
 * @agino, @imap, @dipp, and @bpp are all output parameters.
 *
 * Do not call this function अगर @target_agino is the head of the list.
 */
STATIC पूर्णांक
xfs_iunlink_map_prev(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agino_t		head_agino,
	xfs_agino_t		target_agino,
	xfs_agino_t		*agino,
	काष्ठा xfs_imap		*imap,
	काष्ठा xfs_dinode	**dipp,
	काष्ठा xfs_buf		**bpp,
	काष्ठा xfs_perag	*pag)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	xfs_agino_t		next_agino;
	पूर्णांक			error;

	ASSERT(head_agino != target_agino);
	*bpp = शून्य;

	/* See अगर our backref cache can find it faster. */
	*agino = xfs_iunlink_lookup_backref(pag, target_agino);
	अगर (*agino != शून्यAGINO) अणु
		error = xfs_iunlink_map_ino(tp, agno, *agino, imap, dipp, bpp);
		अगर (error)
			वापस error;

		अगर (be32_to_cpu((*dipp)->di_next_unlinked) == target_agino)
			वापस 0;

		/*
		 * If we get here the cache contents were corrupt, so drop the
		 * buffer and fall back to walking the bucket list.
		 */
		xfs_trans_brअन्यथा(tp, *bpp);
		*bpp = शून्य;
		WARN_ON_ONCE(1);
	पूर्ण

	trace_xfs_iunlink_map_prev_fallback(mp, agno);

	/* Otherwise, walk the entire bucket until we find it. */
	next_agino = head_agino;
	जबतक (next_agino != target_agino) अणु
		xfs_agino_t	unlinked_agino;

		अगर (*bpp)
			xfs_trans_brअन्यथा(tp, *bpp);

		*agino = next_agino;
		error = xfs_iunlink_map_ino(tp, agno, next_agino, imap, dipp,
				bpp);
		अगर (error)
			वापस error;

		unlinked_agino = be32_to_cpu((*dipp)->di_next_unlinked);
		/*
		 * Make sure this poपूर्णांकer is valid and isn't an obvious
		 * infinite loop.
		 */
		अगर (!xfs_verअगरy_agino(mp, agno, unlinked_agino) ||
		    next_agino == unlinked_agino) अणु
			XFS_CORRUPTION_ERROR(__func__,
					XFS_ERRLEVEL_LOW, mp,
					*dipp, माप(**dipp));
			error = -EFSCORRUPTED;
			वापस error;
		पूर्ण
		next_agino = unlinked_agino;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Pull the on-disk inode from the AGI unlinked list.
 */
STATIC पूर्णांक
xfs_iunlink_हटाओ(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_agi		*agi;
	काष्ठा xfs_buf		*agibp;
	काष्ठा xfs_buf		*last_ibp;
	काष्ठा xfs_dinode	*last_dip = शून्य;
	xfs_agnumber_t		agno = XFS_INO_TO_AGNO(mp, ip->i_ino);
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ip->i_ino);
	xfs_agino_t		next_agino;
	xfs_agino_t		head_agino;
	लघु			bucket_index = agino % XFS_AGI_UNLINKED_BUCKETS;
	पूर्णांक			error;

	trace_xfs_iunlink_हटाओ(ip);

	/* Get the agi buffer first.  It ensures lock ordering on the list. */
	error = xfs_पढ़ो_agi(mp, tp, agno, &agibp);
	अगर (error)
		वापस error;
	agi = agibp->b_addr;

	/*
	 * Get the index पूर्णांकo the agi hash table क्रम the list this inode will
	 * go on.  Make sure the head poपूर्णांकer isn't garbage.
	 */
	head_agino = be32_to_cpu(agi->agi_unlinked[bucket_index]);
	अगर (!xfs_verअगरy_agino(mp, agno, head_agino)) अणु
		XFS_CORRUPTION_ERROR(__func__, XFS_ERRLEVEL_LOW, mp,
				agi, माप(*agi));
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Set our inode's next_unlinked poपूर्णांकer to शून्य and then वापस
	 * the old poपूर्णांकer value so that we can update whatever was previous
	 * to us in the list to poपूर्णांक to whatever was next in the list.
	 */
	error = xfs_iunlink_update_inode(tp, ip, agno, शून्यAGINO, &next_agino);
	अगर (error)
		वापस error;

	/*
	 * If there was a backref poपूर्णांकing from the next inode back to this
	 * one, हटाओ it because we've हटाओd this inode from the list.
	 *
	 * Later, अगर this inode was in the middle of the list we'll update
	 * this inode's backref to poपूर्णांक from the next inode.
	 */
	अगर (next_agino != शून्यAGINO) अणु
		error = xfs_iunlink_change_backref(agibp->b_pag, next_agino,
				शून्यAGINO);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (head_agino != agino) अणु
		काष्ठा xfs_imap	imap;
		xfs_agino_t	prev_agino;

		/* We need to search the list क्रम the inode being मुक्तd. */
		error = xfs_iunlink_map_prev(tp, agno, head_agino, agino,
				&prev_agino, &imap, &last_dip, &last_ibp,
				agibp->b_pag);
		अगर (error)
			वापस error;

		/* Poपूर्णांक the previous inode on the list to the next inode. */
		xfs_iunlink_update_dinode(tp, agno, prev_agino, last_ibp,
				last_dip, &imap, next_agino);

		/*
		 * Now we deal with the backref क्रम this inode.  If this inode
		 * poपूर्णांकed at a real inode, change the backref that poपूर्णांकed to
		 * us to poपूर्णांक to our old next.  If this inode was the end of
		 * the list, delete the backref that poपूर्णांकed to us.  Note that
		 * change_backref takes care of deleting the backref अगर
		 * next_agino is शून्यAGINO.
		 */
		वापस xfs_iunlink_change_backref(agibp->b_pag, agino,
				next_agino);
	पूर्ण

	/* Poपूर्णांक the head of the list to the next unlinked inode. */
	वापस xfs_iunlink_update_bucket(tp, agno, agibp, bucket_index,
			next_agino);
पूर्ण

/*
 * Look up the inode number specअगरied and अगर it is not alपढ़ोy marked XFS_ISTALE
 * mark it stale. We should only find clean inodes in this lookup that aren't
 * alपढ़ोy stale.
 */
अटल व्योम
xfs_अगरree_mark_inode_stale(
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_inode	*मुक्त_ip,
	xfs_ino_t		inum)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_perag	*pag = bp->b_pag;
	काष्ठा xfs_inode_log_item *iip;
	काष्ठा xfs_inode	*ip;

retry:
	rcu_पढ़ो_lock();
	ip = radix_tree_lookup(&pag->pag_ici_root, XFS_INO_TO_AGINO(mp, inum));

	/* Inode not in memory, nothing to करो */
	अगर (!ip) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	/*
	 * because this is an RCU रक्षित lookup, we could find a recently
	 * मुक्तd or even पुनः_स्मृतिated inode during the lookup. We need to check
	 * under the i_flags_lock क्रम a valid inode here. Skip it अगर it is not
	 * valid, the wrong inode or stale.
	 */
	spin_lock(&ip->i_flags_lock);
	अगर (ip->i_ino != inum || __xfs_अगरlags_test(ip, XFS_ISTALE))
		जाओ out_अगरlags_unlock;

	/*
	 * Don't try to lock/unlock the current inode, but we _cannot_ skip the
	 * other inodes that we did not find in the list attached to the buffer
	 * and are not alपढ़ोy marked stale. If we can't lock it, back off and
	 * retry.
	 */
	अगर (ip != मुक्त_ip) अणु
		अगर (!xfs_ilock_noरुको(ip, XFS_ILOCK_EXCL)) अणु
			spin_unlock(&ip->i_flags_lock);
			rcu_पढ़ो_unlock();
			delay(1);
			जाओ retry;
		पूर्ण
	पूर्ण
	ip->i_flags |= XFS_ISTALE;

	/*
	 * If the inode is flushing, it is alपढ़ोy attached to the buffer.  All
	 * we needed to करो here is mark the inode stale so buffer IO completion
	 * will हटाओ it from the AIL.
	 */
	iip = ip->i_itemp;
	अगर (__xfs_अगरlags_test(ip, XFS_IFLUSHING)) अणु
		ASSERT(!list_empty(&iip->ili_item.li_bio_list));
		ASSERT(iip->ili_last_fields);
		जाओ out_iunlock;
	पूर्ण

	/*
	 * Inodes not attached to the buffer can be released immediately.
	 * Everything अन्यथा has to go through xfs_अगरlush_पात() on journal
	 * commit as the flock synchronises removal of the inode from the
	 * cluster buffer against inode reclaim.
	 */
	अगर (!iip || list_empty(&iip->ili_item.li_bio_list))
		जाओ out_iunlock;

	__xfs_अगरlags_set(ip, XFS_IFLUSHING);
	spin_unlock(&ip->i_flags_lock);
	rcu_पढ़ो_unlock();

	/* we have a dirty inode in memory that has not yet been flushed. */
	spin_lock(&iip->ili_lock);
	iip->ili_last_fields = iip->ili_fields;
	iip->ili_fields = 0;
	iip->ili_fsync_fields = 0;
	spin_unlock(&iip->ili_lock);
	ASSERT(iip->ili_last_fields);

	अगर (ip != मुक्त_ip)
		xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस;

out_iunlock:
	अगर (ip != मुक्त_ip)
		xfs_iunlock(ip, XFS_ILOCK_EXCL);
out_अगरlags_unlock:
	spin_unlock(&ip->i_flags_lock);
	rcu_पढ़ो_unlock();
पूर्ण

/*
 * A big issue when मुक्तing the inode cluster is that we _cannot_ skip any
 * inodes that are in memory - they all must be marked stale and attached to
 * the cluster buffer.
 */
STATIC पूर्णांक
xfs_अगरree_cluster(
	काष्ठा xfs_inode	*मुक्त_ip,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_icluster	*xic)
अणु
	काष्ठा xfs_mount	*mp = मुक्त_ip->i_mount;
	काष्ठा xfs_ino_geometry	*igeo = M_IGEO(mp);
	काष्ठा xfs_buf		*bp;
	xfs_daddr_t		blkno;
	xfs_ino_t		inum = xic->first_ino;
	पूर्णांक			nbufs;
	पूर्णांक			i, j;
	पूर्णांक			ioffset;
	पूर्णांक			error;

	nbufs = igeo->ialloc_blks / igeo->blocks_per_cluster;

	क्रम (j = 0; j < nbufs; j++, inum += igeo->inodes_per_cluster) अणु
		/*
		 * The allocation biपंचांगap tells us which inodes of the chunk were
		 * physically allocated. Skip the cluster अगर an inode falls पूर्णांकo
		 * a sparse region.
		 */
		ioffset = inum - xic->first_ino;
		अगर ((xic->alloc & XFS_INOBT_MASK(ioffset)) == 0) अणु
			ASSERT(ioffset % igeo->inodes_per_cluster == 0);
			जारी;
		पूर्ण

		blkno = XFS_AGB_TO_DADDR(mp, XFS_INO_TO_AGNO(mp, inum),
					 XFS_INO_TO_AGBNO(mp, inum));

		/*
		 * We obtain and lock the backing buffer first in the process
		 * here to ensure dirty inodes attached to the buffer reमुख्य in
		 * the flushing state जबतक we mark them stale.
		 *
		 * If we scan the in-memory inodes first, then buffer IO can
		 * complete beक्रमe we get a lock on it, and hence we may fail
		 * to mark all the active inodes on the buffer stale.
		 */
		error = xfs_trans_get_buf(tp, mp->m_ddev_targp, blkno,
				mp->m_bsize * igeo->blocks_per_cluster,
				XBF_UNMAPPED, &bp);
		अगर (error)
			वापस error;

		/*
		 * This buffer may not have been correctly initialised as we
		 * didn't read it from disk. That's not important because we are
		 * only using to mark the buffer as stale in the log, and to
		 * attach stale cached inodes on it. That means it will never be
		 * dispatched क्रम IO. If it is, we want to know about it, and we
		 * want it to fail. We can acheive this by adding a ग_लिखो
		 * verअगरier to the buffer.
		 */
		bp->b_ops = &xfs_inode_buf_ops;

		/*
		 * Now we need to set all the cached clean inodes as XFS_ISTALE,
		 * too. This requires lookups, and will skip inodes that we've
		 * alपढ़ोy marked XFS_ISTALE.
		 */
		क्रम (i = 0; i < igeo->inodes_per_cluster; i++)
			xfs_अगरree_mark_inode_stale(bp, मुक्त_ip, inum + i);

		xfs_trans_stale_inode_buf(tp, bp);
		xfs_trans_binval(tp, bp);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This is called to वापस an inode to the inode मुक्त list.
 * The inode should alपढ़ोy be truncated to 0 length and have
 * no pages associated with it.  This routine also assumes that
 * the inode is alपढ़ोy a part of the transaction.
 *
 * The on-disk copy of the inode will have been added to the list
 * of unlinked inodes in the AGI. We need to हटाओ the inode from
 * that list atomically with respect to मुक्तing it here.
 */
पूर्णांक
xfs_अगरree(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip)
अणु
	पूर्णांक			error;
	काष्ठा xfs_icluster	xic = अणु 0 पूर्ण;
	काष्ठा xfs_inode_log_item *iip = ip->i_itemp;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(VFS_I(ip)->i_nlink == 0);
	ASSERT(ip->i_df.अगर_nextents == 0);
	ASSERT(ip->i_disk_size == 0 || !S_ISREG(VFS_I(ip)->i_mode));
	ASSERT(ip->i_nblocks == 0);

	/*
	 * Pull the on-disk inode from the AGI unlinked list.
	 */
	error = xfs_iunlink_हटाओ(tp, ip);
	अगर (error)
		वापस error;

	error = xfs_dअगरree(tp, ip->i_ino, &xic);
	अगर (error)
		वापस error;

	/*
	 * Free any local-क्रमmat data sitting around beक्रमe we reset the
	 * data विभाजन to extents क्रमmat.  Note that the attr विभाजन data has
	 * alपढ़ोy been मुक्तd by xfs_attr_inactive.
	 */
	अगर (ip->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL) अणु
		kmem_मुक्त(ip->i_df.अगर_u1.अगर_data);
		ip->i_df.अगर_u1.अगर_data = शून्य;
		ip->i_df.अगर_bytes = 0;
	पूर्ण

	VFS_I(ip)->i_mode = 0;		/* mark incore inode as मुक्त */
	ip->i_dअगरlags = 0;
	ip->i_dअगरlags2 = ip->i_mount->m_ino_geo.new_dअगरlags2;
	ip->i_विभाजनoff = 0;		/* mark the attr विभाजन not in use */
	ip->i_df.अगर_क्रमmat = XFS_DINODE_FMT_EXTENTS;
	अगर (xfs_अगरlags_test(ip, XFS_IPRESERVE_DM_FIELDS))
		xfs_अगरlags_clear(ip, XFS_IPRESERVE_DM_FIELDS);

	/* Don't attempt to replay owner changes क्रम a deleted inode */
	spin_lock(&iip->ili_lock);
	iip->ili_fields &= ~(XFS_ILOG_AOWNER | XFS_ILOG_DOWNER);
	spin_unlock(&iip->ili_lock);

	/*
	 * Bump the generation count so no one will be confused
	 * by reincarnations of this inode.
	 */
	VFS_I(ip)->i_generation++;
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

	अगर (xic.deleted)
		error = xfs_अगरree_cluster(ip, tp, &xic);

	वापस error;
पूर्ण

/*
 * This is called to unpin an inode.  The caller must have the inode locked
 * in at least shared mode so that the buffer cannot be subsequently pinned
 * once someone is रुकोing क्रम it to be unpinned.
 */
अटल व्योम
xfs_iunpin(
	काष्ठा xfs_inode	*ip)
अणु
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL|XFS_ILOCK_SHARED));

	trace_xfs_inode_unpin_noरुको(ip, _RET_IP_);

	/* Give the log a push to start the unpinning I/O */
	xfs_log_क्रमce_lsn(ip->i_mount, ip->i_itemp->ili_last_lsn, 0, शून्य);

पूर्ण

अटल व्योम
__xfs_iunpin_रुको(
	काष्ठा xfs_inode	*ip)
अणु
	रुको_queue_head_t *wq = bit_रुकोqueue(&ip->i_flags, __XFS_IPINNED_BIT);
	DEFINE_WAIT_BIT(रुको, &ip->i_flags, __XFS_IPINNED_BIT);

	xfs_iunpin(ip);

	करो अणु
		prepare_to_रुको(wq, &रुको.wq_entry, TASK_UNINTERRUPTIBLE);
		अगर (xfs_ipincount(ip))
			io_schedule();
	पूर्ण जबतक (xfs_ipincount(ip));
	finish_रुको(wq, &रुको.wq_entry);
पूर्ण

व्योम
xfs_iunpin_रुको(
	काष्ठा xfs_inode	*ip)
अणु
	अगर (xfs_ipincount(ip))
		__xfs_iunpin_रुको(ip);
पूर्ण

/*
 * Removing an inode from the namespace involves removing the directory entry
 * and dropping the link count on the inode. Removing the directory entry can
 * result in locking an AGF (directory blocks were मुक्तd) and removing a link
 * count can result in placing the inode on an unlinked list which results in
 * locking an AGI.
 *
 * The big problem here is that we have an ordering स्थिरraपूर्णांक on AGF and AGI
 * locking - inode allocation locks the AGI, then can allocate a new extent क्रम
 * new inodes, locking the AGF after the AGI. Similarly, मुक्तing the inode
 * हटाओs the inode from the unlinked list, requiring that we lock the AGI
 * first, and then मुक्तing the inode can result in an inode chunk being मुक्तd
 * and hence मुक्तing disk space requiring that we lock an AGF.
 *
 * Hence the ordering that is imposed by other parts of the code is AGI beक्रमe
 * AGF. This means we cannot हटाओ the directory entry beक्रमe we drop the inode
 * reference count and put it on the unlinked list as this results in a lock
 * order of AGF then AGI, and this can deadlock against inode allocation and
 * मुक्तing. Thereक्रमe we must drop the link counts beक्रमe we हटाओ the
 * directory entry.
 *
 * This is still safe from a transactional poपूर्णांक of view - it is not until we
 * get to xfs_defer_finish() that we have the possibility of multiple
 * transactions in this operation. Hence as दीर्घ as we हटाओ the directory
 * entry and drop the link count in the first transaction of the हटाओ
 * operation, there are no transactional स्थिरraपूर्णांकs on the ordering here.
 */
पूर्णांक
xfs_हटाओ(
	xfs_inode_t             *dp,
	काष्ठा xfs_name		*name,
	xfs_inode_t		*ip)
अणु
	xfs_mount_t		*mp = dp->i_mount;
	xfs_trans_t             *tp = शून्य;
	पूर्णांक			is_dir = S_ISसूची(VFS_I(ip)->i_mode);
	पूर्णांक                     error = 0;
	uपूर्णांक			resblks;

	trace_xfs_हटाओ(dp, name);

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	error = xfs_qm_dqattach(dp);
	अगर (error)
		जाओ std_वापस;

	error = xfs_qm_dqattach(ip);
	अगर (error)
		जाओ std_वापस;

	/*
	 * We try to get the real space reservation first,
	 * allowing क्रम directory btree deletion(s) implying
	 * possible bmap insert(s).  If we can't get the space
	 * reservation then we use 0 instead, and aव्योम the bmap
	 * btree insert(s) in the directory code by, अगर the bmap
	 * insert tries to happen, instead trimming the LAST
	 * block from the directory.
	 */
	resblks = XFS_REMOVE_SPACE_RES(mp);
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_हटाओ, resblks, 0, 0, &tp);
	अगर (error == -ENOSPC) अणु
		resblks = 0;
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_हटाओ, 0, 0, 0,
				&tp);
	पूर्ण
	अगर (error) अणु
		ASSERT(error != -ENOSPC);
		जाओ std_वापस;
	पूर्ण

	xfs_lock_two_inodes(dp, XFS_ILOCK_EXCL, ip, XFS_ILOCK_EXCL);

	xfs_trans_ijoin(tp, dp, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);

	/*
	 * If we're removing a directory perक्रमm some additional validation.
	 */
	अगर (is_dir) अणु
		ASSERT(VFS_I(ip)->i_nlink >= 2);
		अगर (VFS_I(ip)->i_nlink != 2) अणु
			error = -ENOTEMPTY;
			जाओ out_trans_cancel;
		पूर्ण
		अगर (!xfs_dir_isempty(ip)) अणु
			error = -ENOTEMPTY;
			जाओ out_trans_cancel;
		पूर्ण

		/* Drop the link from ip's "..".  */
		error = xfs_droplink(tp, dp);
		अगर (error)
			जाओ out_trans_cancel;

		/* Drop the "." link from ip to self.  */
		error = xfs_droplink(tp, ip);
		अगर (error)
			जाओ out_trans_cancel;
	पूर्ण अन्यथा अणु
		/*
		 * When removing a non-directory we need to log the parent
		 * inode here.  For a directory this is करोne implicitly
		 * by the xfs_droplink call क्रम the ".." entry.
		 */
		xfs_trans_log_inode(tp, dp, XFS_ILOG_CORE);
	पूर्ण
	xfs_trans_ichgसमय(tp, dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);

	/* Drop the link from dp to ip. */
	error = xfs_droplink(tp, ip);
	अगर (error)
		जाओ out_trans_cancel;

	error = xfs_dir_हटाओname(tp, dp, name, ip->i_ino, resblks);
	अगर (error) अणु
		ASSERT(error != -ENOENT);
		जाओ out_trans_cancel;
	पूर्ण

	/*
	 * If this is a synchronous mount, make sure that the
	 * हटाओ transaction goes to disk beक्रमe वापसing to
	 * the user.
	 */
	अगर (mp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_सूचीSYNC))
		xfs_trans_set_sync(tp);

	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ std_वापस;

	अगर (is_dir && xfs_inode_is_filestream(ip))
		xfs_filestream_deassociate(ip);

	वापस 0;

 out_trans_cancel:
	xfs_trans_cancel(tp);
 std_वापस:
	वापस error;
पूर्ण

/*
 * Enter all inodes क्रम a नाम transaction पूर्णांकo a sorted array.
 */
#घोषणा __XFS_SORT_INODES	5
STATIC व्योम
xfs_sort_क्रम_नाम(
	काष्ठा xfs_inode	*dp1,	/* in: old (source) directory inode */
	काष्ठा xfs_inode	*dp2,	/* in: new (target) directory inode */
	काष्ठा xfs_inode	*ip1,	/* in: inode of old entry */
	काष्ठा xfs_inode	*ip2,	/* in: inode of new entry */
	काष्ठा xfs_inode	*wip,	/* in: whiteout inode */
	काष्ठा xfs_inode	**i_tab,/* out: sorted array of inodes */
	पूर्णांक			*num_inodes)  /* in/out: inodes in array */
अणु
	पूर्णांक			i, j;

	ASSERT(*num_inodes == __XFS_SORT_INODES);
	स_रखो(i_tab, 0, *num_inodes * माप(काष्ठा xfs_inode *));

	/*
	 * i_tab contains a list of poपूर्णांकers to inodes.  We initialize
	 * the table here & we'll sort it.  We will then use it to
	 * order the acquisition of the inode locks.
	 *
	 * Note that the table may contain duplicates.  e.g., dp1 == dp2.
	 */
	i = 0;
	i_tab[i++] = dp1;
	i_tab[i++] = dp2;
	i_tab[i++] = ip1;
	अगर (ip2)
		i_tab[i++] = ip2;
	अगर (wip)
		i_tab[i++] = wip;
	*num_inodes = i;

	/*
	 * Sort the elements via bubble sort.  (Remember, there are at
	 * most 5 elements to sort, so this is adequate.)
	 */
	क्रम (i = 0; i < *num_inodes; i++) अणु
		क्रम (j = 1; j < *num_inodes; j++) अणु
			अगर (i_tab[j]->i_ino < i_tab[j-1]->i_ino) अणु
				काष्ठा xfs_inode *temp = i_tab[j];
				i_tab[j] = i_tab[j-1];
				i_tab[j-1] = temp;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
xfs_finish_नाम(
	काष्ठा xfs_trans	*tp)
अणु
	/*
	 * If this is a synchronous mount, make sure that the नाम transaction
	 * goes to disk beक्रमe वापसing to the user.
	 */
	अगर (tp->t_mountp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_सूचीSYNC))
		xfs_trans_set_sync(tp);

	वापस xfs_trans_commit(tp);
पूर्ण

/*
 * xfs_cross_नाम()
 *
 * responsible क्रम handling RENAME_EXCHANGE flag in नामat2() syscall
 */
STATIC पूर्णांक
xfs_cross_नाम(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp1,
	काष्ठा xfs_name		*name1,
	काष्ठा xfs_inode	*ip1,
	काष्ठा xfs_inode	*dp2,
	काष्ठा xfs_name		*name2,
	काष्ठा xfs_inode	*ip2,
	पूर्णांक			spaceres)
अणु
	पूर्णांक		error = 0;
	पूर्णांक		ip1_flags = 0;
	पूर्णांक		ip2_flags = 0;
	पूर्णांक		dp2_flags = 0;

	/* Swap inode number क्रम dirent in first parent */
	error = xfs_dir_replace(tp, dp1, name1, ip2->i_ino, spaceres);
	अगर (error)
		जाओ out_trans_पात;

	/* Swap inode number क्रम dirent in second parent */
	error = xfs_dir_replace(tp, dp2, name2, ip1->i_ino, spaceres);
	अगर (error)
		जाओ out_trans_पात;

	/*
	 * If we're renaming one or more directories across dअगरferent parents,
	 * update the respective ".." entries (and link counts) to match the new
	 * parents.
	 */
	अगर (dp1 != dp2) अणु
		dp2_flags = XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG;

		अगर (S_ISसूची(VFS_I(ip2)->i_mode)) अणु
			error = xfs_dir_replace(tp, ip2, &xfs_name_करोtकरोt,
						dp1->i_ino, spaceres);
			अगर (error)
				जाओ out_trans_पात;

			/* transfer ip2 ".." reference to dp1 */
			अगर (!S_ISसूची(VFS_I(ip1)->i_mode)) अणु
				error = xfs_droplink(tp, dp2);
				अगर (error)
					जाओ out_trans_पात;
				xfs_bumplink(tp, dp1);
			पूर्ण

			/*
			 * Although ip1 isn't changed here, userspace needs
			 * to be warned about the change, so that applications
			 * relying on it (like backup ones), will properly
			 * notअगरy the change
			 */
			ip1_flags |= XFS_ICHGTIME_CHG;
			ip2_flags |= XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG;
		पूर्ण

		अगर (S_ISसूची(VFS_I(ip1)->i_mode)) अणु
			error = xfs_dir_replace(tp, ip1, &xfs_name_करोtकरोt,
						dp2->i_ino, spaceres);
			अगर (error)
				जाओ out_trans_पात;

			/* transfer ip1 ".." reference to dp2 */
			अगर (!S_ISसूची(VFS_I(ip2)->i_mode)) अणु
				error = xfs_droplink(tp, dp1);
				अगर (error)
					जाओ out_trans_पात;
				xfs_bumplink(tp, dp2);
			पूर्ण

			/*
			 * Although ip2 isn't changed here, userspace needs
			 * to be warned about the change, so that applications
			 * relying on it (like backup ones), will properly
			 * notअगरy the change
			 */
			ip1_flags |= XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG;
			ip2_flags |= XFS_ICHGTIME_CHG;
		पूर्ण
	पूर्ण

	अगर (ip1_flags) अणु
		xfs_trans_ichgसमय(tp, ip1, ip1_flags);
		xfs_trans_log_inode(tp, ip1, XFS_ILOG_CORE);
	पूर्ण
	अगर (ip2_flags) अणु
		xfs_trans_ichgसमय(tp, ip2, ip2_flags);
		xfs_trans_log_inode(tp, ip2, XFS_ILOG_CORE);
	पूर्ण
	अगर (dp2_flags) अणु
		xfs_trans_ichgसमय(tp, dp2, dp2_flags);
		xfs_trans_log_inode(tp, dp2, XFS_ILOG_CORE);
	पूर्ण
	xfs_trans_ichgसमय(tp, dp1, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, dp1, XFS_ILOG_CORE);
	वापस xfs_finish_नाम(tp);

out_trans_पात:
	xfs_trans_cancel(tp);
	वापस error;
पूर्ण

/*
 * xfs_नाम_alloc_whiteout()
 *
 * Return a referenced, unlinked, unlocked inode that can be used as a
 * whiteout in a नाम transaction. We use a क्षणिक_ख inode here so that अगर we
 * crash between allocating the inode and linking it पूर्णांकo the नाम transaction
 * recovery will मुक्त the inode and we won't leak it.
 */
अटल पूर्णांक
xfs_नाम_alloc_whiteout(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_inode	**wip)
अणु
	काष्ठा xfs_inode	*क्षणिक_ख;
	पूर्णांक			error;

	error = xfs_create_क्षणिक_ख(mnt_userns, dp, S_IFCHR | WHITEOUT_MODE,
				   &क्षणिक_ख);
	अगर (error)
		वापस error;

	/*
	 * Prepare the क्षणिक_ख inode as अगर it were created through the VFS.
	 * Complete the inode setup and flag it as linkable.  nlink is alपढ़ोy
	 * zero, so we can skip the drop_nlink.
	 */
	xfs_setup_iops(क्षणिक_ख);
	xfs_finish_inode_setup(क्षणिक_ख);
	VFS_I(क्षणिक_ख)->i_state |= I_LINKABLE;

	*wip = क्षणिक_ख;
	वापस 0;
पूर्ण

/*
 * xfs_नाम
 */
पूर्णांक
xfs_नाम(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा xfs_inode	*src_dp,
	काष्ठा xfs_name		*src_name,
	काष्ठा xfs_inode	*src_ip,
	काष्ठा xfs_inode	*target_dp,
	काष्ठा xfs_name		*target_name,
	काष्ठा xfs_inode	*target_ip,
	अचिन्हित पूर्णांक		flags)
अणु
	काष्ठा xfs_mount	*mp = src_dp->i_mount;
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_inode	*wip = शून्य;		/* whiteout inode */
	काष्ठा xfs_inode	*inodes[__XFS_SORT_INODES];
	पूर्णांक			i;
	पूर्णांक			num_inodes = __XFS_SORT_INODES;
	bool			new_parent = (src_dp != target_dp);
	bool			src_is_directory = S_ISसूची(VFS_I(src_ip)->i_mode);
	पूर्णांक			spaceres;
	पूर्णांक			error;

	trace_xfs_नाम(src_dp, target_dp, src_name, target_name);

	अगर ((flags & RENAME_EXCHANGE) && !target_ip)
		वापस -EINVAL;

	/*
	 * If we are करोing a whiteout operation, allocate the whiteout inode
	 * we will be placing at the target and ensure the type is set
	 * appropriately.
	 */
	अगर (flags & RENAME_WHITEOUT) अणु
		ASSERT(!(flags & (RENAME_NOREPLACE | RENAME_EXCHANGE)));
		error = xfs_नाम_alloc_whiteout(mnt_userns, target_dp, &wip);
		अगर (error)
			वापस error;

		/* setup target dirent info as whiteout */
		src_name->type = XFS_सूची3_FT_CHRDEV;
	पूर्ण

	xfs_sort_क्रम_नाम(src_dp, target_dp, src_ip, target_ip, wip,
				inodes, &num_inodes);

	spaceres = XFS_RENAME_SPACE_RES(mp, target_name->len);
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_नाम, spaceres, 0, 0, &tp);
	अगर (error == -ENOSPC) अणु
		spaceres = 0;
		error = xfs_trans_alloc(mp, &M_RES(mp)->tr_नाम, 0, 0, 0,
				&tp);
	पूर्ण
	अगर (error)
		जाओ out_release_wip;

	/*
	 * Attach the dquots to the inodes
	 */
	error = xfs_qm_vop_नाम_dqattach(inodes);
	अगर (error)
		जाओ out_trans_cancel;

	/*
	 * Lock all the participating inodes. Depending upon whether
	 * the target_name exists in the target directory, and
	 * whether the target directory is the same as the source
	 * directory, we can lock from 2 to 4 inodes.
	 */
	xfs_lock_inodes(inodes, num_inodes, XFS_ILOCK_EXCL);

	/*
	 * Join all the inodes to the transaction. From this poपूर्णांक on,
	 * we can rely on either trans_commit or trans_cancel to unlock
	 * them.
	 */
	xfs_trans_ijoin(tp, src_dp, XFS_ILOCK_EXCL);
	अगर (new_parent)
		xfs_trans_ijoin(tp, target_dp, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, src_ip, XFS_ILOCK_EXCL);
	अगर (target_ip)
		xfs_trans_ijoin(tp, target_ip, XFS_ILOCK_EXCL);
	अगर (wip)
		xfs_trans_ijoin(tp, wip, XFS_ILOCK_EXCL);

	/*
	 * If we are using project inheritance, we only allow नामs
	 * पूर्णांकo our tree when the project IDs are the same; अन्यथा the
	 * tree quota mechanism would be circumvented.
	 */
	अगर (unlikely((target_dp->i_dअगरlags & XFS_DIFLAG_PROJINHERIT) &&
		     target_dp->i_projid != src_ip->i_projid)) अणु
		error = -EXDEV;
		जाओ out_trans_cancel;
	पूर्ण

	/* RENAME_EXCHANGE is unique from here on. */
	अगर (flags & RENAME_EXCHANGE)
		वापस xfs_cross_नाम(tp, src_dp, src_name, src_ip,
					target_dp, target_name, target_ip,
					spaceres);

	/*
	 * Check क्रम expected errors beक्रमe we dirty the transaction
	 * so we can वापस an error without a transaction पात.
	 *
	 * Extent count overflow check:
	 *
	 * From the perspective of src_dp, a नाम operation is essentially a
	 * directory entry हटाओ operation. Hence the only place where we check
	 * क्रम extent count overflow क्रम src_dp is in
	 * xfs_bmap_del_extent_real(). xfs_bmap_del_extent_real() वापसs
	 * -ENOSPC when it detects a possible extent count overflow and in
	 * response, the higher layers of directory handling code करो the
	 * following:
	 * 1. Data/Free blocks: XFS lets these blocks linger until a
	 *    future हटाओ operation हटाओs them.
	 * 2. Dabtree blocks: XFS swaps the blocks with the last block in the
	 *    Leaf space and unmaps the last block.
	 *
	 * For target_dp, there are two हालs depending on whether the
	 * destination directory entry exists or not.
	 *
	 * When destination directory entry करोes not exist (i.e. target_ip ==
	 * शून्य), extent count overflow check is perक्रमmed only when transaction
	 * has a non-zero sized space reservation associated with it.  With a
	 * zero-sized space reservation, XFS allows a नाम operation to
	 * जारी only when the directory has sufficient मुक्त space in its
	 * data/leaf/मुक्त space blocks to hold the new entry.
	 *
	 * When destination directory entry exists (i.e. target_ip != शून्य), all
	 * we need to करो is change the inode number associated with the alपढ़ोy
	 * existing entry. Hence there is no need to perक्रमm an extent count
	 * overflow check.
	 */
	अगर (target_ip == शून्य) अणु
		/*
		 * If there's no space reservation, check the entry will
		 * fit beक्रमe actually inserting it.
		 */
		अगर (!spaceres) अणु
			error = xfs_dir_canenter(tp, target_dp, target_name);
			अगर (error)
				जाओ out_trans_cancel;
		पूर्ण अन्यथा अणु
			error = xfs_iext_count_may_overflow(target_dp,
					XFS_DATA_FORK,
					XFS_IEXT_सूची_MANIP_CNT(mp));
			अगर (error)
				जाओ out_trans_cancel;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * If target exists and it's a directory, check that whether
		 * it can be destroyed.
		 */
		अगर (S_ISसूची(VFS_I(target_ip)->i_mode) &&
		    (!xfs_dir_isempty(target_ip) ||
		     (VFS_I(target_ip)->i_nlink > 2))) अणु
			error = -EEXIST;
			जाओ out_trans_cancel;
		पूर्ण
	पूर्ण

	/*
	 * Lock the AGI buffers we need to handle bumping the nlink of the
	 * whiteout inode off the unlinked list and to handle dropping the
	 * nlink of the target inode.  Per locking order rules, करो this in
	 * increasing AG order and beक्रमe directory block allocation tries to
	 * grab AGFs because we grab AGIs beक्रमe AGFs.
	 *
	 * The (vfs) caller must ensure that अगर src is a directory then
	 * target_ip is either null or an empty directory.
	 */
	क्रम (i = 0; i < num_inodes && inodes[i] != शून्य; i++) अणु
		अगर (inodes[i] == wip ||
		    (inodes[i] == target_ip &&
		     (VFS_I(target_ip)->i_nlink == 1 || src_is_directory))) अणु
			काष्ठा xfs_buf	*bp;
			xfs_agnumber_t	agno;

			agno = XFS_INO_TO_AGNO(mp, inodes[i]->i_ino);
			error = xfs_पढ़ो_agi(mp, tp, agno, &bp);
			अगर (error)
				जाओ out_trans_cancel;
		पूर्ण
	पूर्ण

	/*
	 * Directory entry creation below may acquire the AGF. Remove
	 * the whiteout from the unlinked list first to preserve correct
	 * AGI/AGF locking order. This dirties the transaction so failures
	 * after this poपूर्णांक will पात and log recovery will clean up the
	 * mess.
	 *
	 * For whiteouts, we need to bump the link count on the whiteout
	 * inode. After this poपूर्णांक, we have a real link, clear the क्षणिक_ख
	 * state flag from the inode so it करोesn't accidentally get misused
	 * in future.
	 */
	अगर (wip) अणु
		ASSERT(VFS_I(wip)->i_nlink == 0);
		error = xfs_iunlink_हटाओ(tp, wip);
		अगर (error)
			जाओ out_trans_cancel;

		xfs_bumplink(tp, wip);
		VFS_I(wip)->i_state &= ~I_LINKABLE;
	पूर्ण

	/*
	 * Set up the target.
	 */
	अगर (target_ip == शून्य) अणु
		/*
		 * If target करोes not exist and the नाम crosses
		 * directories, adjust the target directory link count
		 * to account क्रम the ".." reference from the new entry.
		 */
		error = xfs_dir_createname(tp, target_dp, target_name,
					   src_ip->i_ino, spaceres);
		अगर (error)
			जाओ out_trans_cancel;

		xfs_trans_ichgसमय(tp, target_dp,
					XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);

		अगर (new_parent && src_is_directory) अणु
			xfs_bumplink(tp, target_dp);
		पूर्ण
	पूर्ण अन्यथा अणु /* target_ip != शून्य */
		/*
		 * Link the source inode under the target name.
		 * If the source inode is a directory and we are moving
		 * it across directories, its ".." entry will be
		 * inconsistent until we replace that करोwn below.
		 *
		 * In हाल there is alपढ़ोy an entry with the same
		 * name at the destination directory, हटाओ it first.
		 */
		error = xfs_dir_replace(tp, target_dp, target_name,
					src_ip->i_ino, spaceres);
		अगर (error)
			जाओ out_trans_cancel;

		xfs_trans_ichgसमय(tp, target_dp,
					XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);

		/*
		 * Decrement the link count on the target since the target
		 * dir no दीर्घer poपूर्णांकs to it.
		 */
		error = xfs_droplink(tp, target_ip);
		अगर (error)
			जाओ out_trans_cancel;

		अगर (src_is_directory) अणु
			/*
			 * Drop the link from the old "." entry.
			 */
			error = xfs_droplink(tp, target_ip);
			अगर (error)
				जाओ out_trans_cancel;
		पूर्ण
	पूर्ण /* target_ip != शून्य */

	/*
	 * Remove the source.
	 */
	अगर (new_parent && src_is_directory) अणु
		/*
		 * Reग_लिखो the ".." entry to poपूर्णांक to the new
		 * directory.
		 */
		error = xfs_dir_replace(tp, src_ip, &xfs_name_करोtकरोt,
					target_dp->i_ino, spaceres);
		ASSERT(error != -EEXIST);
		अगर (error)
			जाओ out_trans_cancel;
	पूर्ण

	/*
	 * We always want to hit the स_समय on the source inode.
	 *
	 * This isn't strictly required by the standards since the source
	 * inode isn't really being changed, but old unix file प्रणालीs did
	 * it and some incremental backup programs won't work without it.
	 */
	xfs_trans_ichgसमय(tp, src_ip, XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, src_ip, XFS_ILOG_CORE);

	/*
	 * Adjust the link count on src_dp.  This is necessary when
	 * renaming a directory, either within one parent when
	 * the target existed, or across two parent directories.
	 */
	अगर (src_is_directory && (new_parent || target_ip != शून्य)) अणु

		/*
		 * Decrement link count on src_directory since the
		 * entry that's moved no दीर्घer poपूर्णांकs to it.
		 */
		error = xfs_droplink(tp, src_dp);
		अगर (error)
			जाओ out_trans_cancel;
	पूर्ण

	/*
	 * For whiteouts, we only need to update the source dirent with the
	 * inode number of the whiteout inode rather than removing it
	 * altogether.
	 */
	अगर (wip) अणु
		error = xfs_dir_replace(tp, src_dp, src_name, wip->i_ino,
					spaceres);
	पूर्ण अन्यथा अणु
		/*
		 * NOTE: We करोn't need to check क्रम extent count overflow here
		 * because the dir हटाओ name code will leave the dir block in
		 * place अगर the extent count would overflow.
		 */
		error = xfs_dir_हटाओname(tp, src_dp, src_name, src_ip->i_ino,
					   spaceres);
	पूर्ण

	अगर (error)
		जाओ out_trans_cancel;

	xfs_trans_ichgसमय(tp, src_dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, src_dp, XFS_ILOG_CORE);
	अगर (new_parent)
		xfs_trans_log_inode(tp, target_dp, XFS_ILOG_CORE);

	error = xfs_finish_नाम(tp);
	अगर (wip)
		xfs_irele(wip);
	वापस error;

out_trans_cancel:
	xfs_trans_cancel(tp);
out_release_wip:
	अगर (wip)
		xfs_irele(wip);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_अगरlush(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_inode_log_item *iip = ip->i_itemp;
	काष्ठा xfs_dinode	*dip;
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			error;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL|XFS_ILOCK_SHARED));
	ASSERT(xfs_अगरlags_test(ip, XFS_IFLUSHING));
	ASSERT(ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_BTREE ||
	       ip->i_df.अगर_nextents > XFS_IFORK_MAXEXT(ip, XFS_DATA_FORK));
	ASSERT(iip->ili_item.li_buf == bp);

	dip = xfs_buf_offset(bp, ip->i_imap.im_boffset);

	/*
	 * We करोn't flush the inode अगर any of the following checks fail, but we
	 * करो still update the log item and attach to the backing buffer as अगर
	 * the flush happened. This is a क्रमmality to facilitate predictable
	 * error handling as the caller will shutकरोwn and fail the buffer.
	 */
	error = -EFSCORRUPTED;
	अगर (XFS_TEST_ERROR(dip->di_magic != cpu_to_be16(XFS_DINODE_MAGIC),
			       mp, XFS_ERRTAG_IFLUSH_1)) अणु
		xfs_alert_tag(mp, XFS_PTAG_IFLUSH,
			"%s: Bad inode %Lu magic number 0x%x, ptr "PTR_FMT,
			__func__, ip->i_ino, be16_to_cpu(dip->di_magic), dip);
		जाओ flush_out;
	पूर्ण
	अगर (S_ISREG(VFS_I(ip)->i_mode)) अणु
		अगर (XFS_TEST_ERROR(
		    ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_EXTENTS &&
		    ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_BTREE,
		    mp, XFS_ERRTAG_IFLUSH_3)) अणु
			xfs_alert_tag(mp, XFS_PTAG_IFLUSH,
				"%s: Bad regular inode %Lu, ptr "PTR_FMT,
				__func__, ip->i_ino, ip);
			जाओ flush_out;
		पूर्ण
	पूर्ण अन्यथा अगर (S_ISसूची(VFS_I(ip)->i_mode)) अणु
		अगर (XFS_TEST_ERROR(
		    ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_EXTENTS &&
		    ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_BTREE &&
		    ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_LOCAL,
		    mp, XFS_ERRTAG_IFLUSH_4)) अणु
			xfs_alert_tag(mp, XFS_PTAG_IFLUSH,
				"%s: Bad directory inode %Lu, ptr "PTR_FMT,
				__func__, ip->i_ino, ip);
			जाओ flush_out;
		पूर्ण
	पूर्ण
	अगर (XFS_TEST_ERROR(ip->i_df.अगर_nextents + xfs_अगरork_nextents(ip->i_afp) >
				ip->i_nblocks, mp, XFS_ERRTAG_IFLUSH_5)) अणु
		xfs_alert_tag(mp, XFS_PTAG_IFLUSH,
			"%s: detected corrupt incore inode %Lu, "
			"total extents = %d, nblocks = %Ld, ptr "PTR_FMT,
			__func__, ip->i_ino,
			ip->i_df.अगर_nextents + xfs_अगरork_nextents(ip->i_afp),
			ip->i_nblocks, ip);
		जाओ flush_out;
	पूर्ण
	अगर (XFS_TEST_ERROR(ip->i_विभाजनoff > mp->m_sb.sb_inodesize,
				mp, XFS_ERRTAG_IFLUSH_6)) अणु
		xfs_alert_tag(mp, XFS_PTAG_IFLUSH,
			"%s: bad inode %Lu, forkoff 0x%x, ptr "PTR_FMT,
			__func__, ip->i_ino, ip->i_विभाजनoff, ip);
		जाओ flush_out;
	पूर्ण

	/*
	 * Inode item log recovery क्रम v2 inodes are dependent on the flushiter
	 * count क्रम correct sequencing.  We bump the flush iteration count so
	 * we can detect flushes which postdate a log record during recovery.
	 * This is redundant as we now log every change and hence this can't
	 * happen but we need to still करो it to ensure backwards compatibility
	 * with old kernels that predate logging all inode changes.
	 */
	अगर (!xfs_sb_version_has_v3inode(&mp->m_sb))
		ip->i_flushiter++;

	/*
	 * If there are अंतरभूत क्रमmat data / attr विभाजनs attached to this inode,
	 * make sure they are not corrupt.
	 */
	अगर (ip->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL &&
	    xfs_अगरork_verअगरy_local_data(ip))
		जाओ flush_out;
	अगर (ip->i_afp && ip->i_afp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL &&
	    xfs_अगरork_verअगरy_local_attr(ip))
		जाओ flush_out;

	/*
	 * Copy the dirty parts of the inode पूर्णांकo the on-disk inode.  We always
	 * copy out the core of the inode, because अगर the inode is dirty at all
	 * the core must be.
	 */
	xfs_inode_to_disk(ip, dip, iip->ili_item.li_lsn);

	/* Wrap, we never let the log put out DI_MAX_FLUSH */
	अगर (!xfs_sb_version_has_v3inode(&mp->m_sb)) अणु
		अगर (ip->i_flushiter == DI_MAX_FLUSH)
			ip->i_flushiter = 0;
	पूर्ण

	xfs_अगरlush_विभाजन(ip, dip, iip, XFS_DATA_FORK);
	अगर (XFS_IFORK_Q(ip))
		xfs_अगरlush_विभाजन(ip, dip, iip, XFS_ATTR_FORK);

	/*
	 * We've recorded everything logged in the inode, so we'd like to clear
	 * the ili_fields bits so we करोn't log and flush things unnecessarily.
	 * However, we can't stop logging all this inक्रमmation until the data
	 * we've copied पूर्णांकo the disk buffer is written to disk.  If we did we
	 * might overग_लिखो the copy of the inode in the log with all the data
	 * after re-logging only part of it, and in the face of a crash we
	 * wouldn't have all the data we need to recover.
	 *
	 * What we करो is move the bits to the ili_last_fields field.  When
	 * logging the inode, these bits are moved back to the ili_fields field.
	 * In the xfs_buf_inode_ioकरोne() routine we clear ili_last_fields, since
	 * we know that the inक्रमmation those bits represent is permanently on
	 * disk.  As दीर्घ as the flush completes beक्रमe the inode is logged
	 * again, then both ili_fields and ili_last_fields will be cleared.
	 */
	error = 0;
flush_out:
	spin_lock(&iip->ili_lock);
	iip->ili_last_fields = iip->ili_fields;
	iip->ili_fields = 0;
	iip->ili_fsync_fields = 0;
	spin_unlock(&iip->ili_lock);

	/*
	 * Store the current LSN of the inode so that we can tell whether the
	 * item has moved in the AIL from xfs_buf_inode_ioकरोne().
	 */
	xfs_trans_ail_copy_lsn(mp->m_ail, &iip->ili_flush_lsn,
				&iip->ili_item.li_lsn);

	/* generate the checksum. */
	xfs_dinode_calc_crc(mp, dip);
	वापस error;
पूर्ण

/*
 * Non-blocking flush of dirty inode metadata पूर्णांकo the backing buffer.
 *
 * The caller must have a reference to the inode and hold the cluster buffer
 * locked. The function will walk across all the inodes on the cluster buffer it
 * can find and lock without blocking, and flush them to the cluster buffer.
 *
 * On successful flushing of at least one inode, the caller must ग_लिखो out the
 * buffer and release it. If no inodes are flushed, -EAGAIN will be वापसed and
 * the caller needs to release the buffer. On failure, the fileप्रणाली will be
 * shut करोwn, the buffer will have been unlocked and released, and EFSCORRUPTED
 * will be वापसed.
 */
पूर्णांक
xfs_अगरlush_cluster(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_log_item	*lip, *n;
	काष्ठा xfs_inode	*ip;
	काष्ठा xfs_inode_log_item *iip;
	पूर्णांक			clcount = 0;
	पूर्णांक			error = 0;

	/*
	 * We must use the safe variant here as on shutकरोwn xfs_अगरlush_पात()
	 * can हटाओ itself from the list.
	 */
	list_क्रम_each_entry_safe(lip, n, &bp->b_li_list, li_bio_list) अणु
		iip = (काष्ठा xfs_inode_log_item *)lip;
		ip = iip->ili_inode;

		/*
		 * Quick and dirty check to aव्योम locks अगर possible.
		 */
		अगर (__xfs_अगरlags_test(ip, XFS_IRECLAIM | XFS_IFLUSHING))
			जारी;
		अगर (xfs_ipincount(ip))
			जारी;

		/*
		 * The inode is still attached to the buffer, which means it is
		 * dirty but reclaim might try to grab it. Check carefully क्रम
		 * that, and grab the ilock जबतक still holding the i_flags_lock
		 * to guarantee reclaim will not be able to reclaim this inode
		 * once we drop the i_flags_lock.
		 */
		spin_lock(&ip->i_flags_lock);
		ASSERT(!__xfs_अगरlags_test(ip, XFS_ISTALE));
		अगर (__xfs_अगरlags_test(ip, XFS_IRECLAIM | XFS_IFLUSHING)) अणु
			spin_unlock(&ip->i_flags_lock);
			जारी;
		पूर्ण

		/*
		 * ILOCK will pin the inode against reclaim and prevent
		 * concurrent transactions modअगरying the inode जबतक we are
		 * flushing the inode. If we get the lock, set the flushing
		 * state beक्रमe we drop the i_flags_lock.
		 */
		अगर (!xfs_ilock_noरुको(ip, XFS_ILOCK_SHARED)) अणु
			spin_unlock(&ip->i_flags_lock);
			जारी;
		पूर्ण
		__xfs_अगरlags_set(ip, XFS_IFLUSHING);
		spin_unlock(&ip->i_flags_lock);

		/*
		 * Abort flushing this inode अगर we are shut करोwn because the
		 * inode may not currently be in the AIL. This can occur when
		 * log I/O failure unpins the inode without inserting पूर्णांकo the
		 * AIL, leaving a dirty/unpinned inode attached to the buffer
		 * that otherwise looks like it should be flushed.
		 */
		अगर (XFS_FORCED_SHUTDOWN(mp)) अणु
			xfs_iunpin_रुको(ip);
			xfs_अगरlush_पात(ip);
			xfs_iunlock(ip, XFS_ILOCK_SHARED);
			error = -EIO;
			जारी;
		पूर्ण

		/* करोn't block रुकोing on a log क्रमce to unpin dirty inodes */
		अगर (xfs_ipincount(ip)) अणु
			xfs_अगरlags_clear(ip, XFS_IFLUSHING);
			xfs_iunlock(ip, XFS_ILOCK_SHARED);
			जारी;
		पूर्ण

		अगर (!xfs_inode_clean(ip))
			error = xfs_अगरlush(ip, bp);
		अन्यथा
			xfs_अगरlags_clear(ip, XFS_IFLUSHING);
		xfs_iunlock(ip, XFS_ILOCK_SHARED);
		अगर (error)
			अवरोध;
		clcount++;
	पूर्ण

	अगर (error) अणु
		bp->b_flags |= XBF_ASYNC;
		xfs_buf_ioend_fail(bp);
		xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
		वापस error;
	पूर्ण

	अगर (!clcount)
		वापस -EAGAIN;

	XFS_STATS_INC(mp, xs_icluster_flushcnt);
	XFS_STATS_ADD(mp, xs_icluster_flushinode, clcount);
	वापस 0;

पूर्ण

/* Release an inode. */
व्योम
xfs_irele(
	काष्ठा xfs_inode	*ip)
अणु
	trace_xfs_irele(ip, _RET_IP_);
	iput(VFS_I(ip));
पूर्ण

/*
 * Ensure all commited transactions touching the inode are written to the log.
 */
पूर्णांक
xfs_log_क्रमce_inode(
	काष्ठा xfs_inode	*ip)
अणु
	xfs_lsn_t		lsn = 0;

	xfs_ilock(ip, XFS_ILOCK_SHARED);
	अगर (xfs_ipincount(ip))
		lsn = ip->i_itemp->ili_last_lsn;
	xfs_iunlock(ip, XFS_ILOCK_SHARED);

	अगर (!lsn)
		वापस 0;
	वापस xfs_log_क्रमce_lsn(ip->i_mount, lsn, XFS_LOG_SYNC, शून्य);
पूर्ण

/*
 * Grab the exclusive iolock क्रम a data copy from src to dest, making sure to
 * abide vfs locking order (lowest poपूर्णांकer value goes first) and अवरोधing the
 * layout leases beक्रमe proceeding.  The loop is needed because we cannot call
 * the blocking अवरोध_layout() with the iolocks held, and thereक्रमe have to
 * back out both locks.
 */
अटल पूर्णांक
xfs_iolock_two_inodes_and_अवरोध_layout(
	काष्ठा inode		*src,
	काष्ठा inode		*dest)
अणु
	पूर्णांक			error;

	अगर (src > dest)
		swap(src, dest);

retry:
	/* Wait to अवरोध both inodes' layouts beक्रमe we start locking. */
	error = अवरोध_layout(src, true);
	अगर (error)
		वापस error;
	अगर (src != dest) अणु
		error = अवरोध_layout(dest, true);
		अगर (error)
			वापस error;
	पूर्ण

	/* Lock one inode and make sure nobody got in and leased it. */
	inode_lock(src);
	error = अवरोध_layout(src, false);
	अगर (error) अणु
		inode_unlock(src);
		अगर (error == -EWOULDBLOCK)
			जाओ retry;
		वापस error;
	पूर्ण

	अगर (src == dest)
		वापस 0;

	/* Lock the other inode and make sure nobody got in and leased it. */
	inode_lock_nested(dest, I_MUTEX_NONसूची2);
	error = अवरोध_layout(dest, false);
	अगर (error) अणु
		inode_unlock(src);
		inode_unlock(dest);
		अगर (error == -EWOULDBLOCK)
			जाओ retry;
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Lock two inodes so that userspace cannot initiate I/O via file syscalls or
 * mmap activity.
 */
पूर्णांक
xfs_ilock2_io_mmap(
	काष्ठा xfs_inode	*ip1,
	काष्ठा xfs_inode	*ip2)
अणु
	पूर्णांक			ret;

	ret = xfs_iolock_two_inodes_and_अवरोध_layout(VFS_I(ip1), VFS_I(ip2));
	अगर (ret)
		वापस ret;
	अगर (ip1 == ip2)
		xfs_ilock(ip1, XFS_MMAPLOCK_EXCL);
	अन्यथा
		xfs_lock_two_inodes(ip1, XFS_MMAPLOCK_EXCL,
				    ip2, XFS_MMAPLOCK_EXCL);
	वापस 0;
पूर्ण

/* Unlock both inodes to allow IO and mmap activity. */
व्योम
xfs_iunlock2_io_mmap(
	काष्ठा xfs_inode	*ip1,
	काष्ठा xfs_inode	*ip2)
अणु
	bool			same_inode = (ip1 == ip2);

	xfs_iunlock(ip2, XFS_MMAPLOCK_EXCL);
	अगर (!same_inode)
		xfs_iunlock(ip1, XFS_MMAPLOCK_EXCL);
	inode_unlock(VFS_I(ip2));
	अगर (!same_inode)
		inode_unlock(VFS_I(ip1));
पूर्ण
