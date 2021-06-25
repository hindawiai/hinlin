<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_inode_item.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_bmap_util.h"
#समावेश "xfs_dquot_item.h"
#समावेश "xfs_dquot.h"
#समावेश "xfs_reflink.h"
#समावेश "xfs_ialloc.h"

#समावेश <linux/iversion.h>

/*
 * Allocate and initialise an xfs_inode.
 */
काष्ठा xfs_inode *
xfs_inode_alloc(
	काष्ठा xfs_mount	*mp,
	xfs_ino_t		ino)
अणु
	काष्ठा xfs_inode	*ip;

	/*
	 * XXX: If this didn't occur in transactions, we could drop GFP_NOFAIL
	 * and वापस शून्य here on ENOMEM.
	 */
	ip = kmem_cache_alloc(xfs_inode_zone, GFP_KERNEL | __GFP_NOFAIL);

	अगर (inode_init_always(mp->m_super, VFS_I(ip))) अणु
		kmem_cache_मुक्त(xfs_inode_zone, ip);
		वापस शून्य;
	पूर्ण

	/* VFS करोesn't initialise i_mode! */
	VFS_I(ip)->i_mode = 0;

	XFS_STATS_INC(mp, vn_active);
	ASSERT(atomic_पढ़ो(&ip->i_pincount) == 0);
	ASSERT(ip->i_ino == 0);

	/* initialise the xfs inode */
	ip->i_ino = ino;
	ip->i_mount = mp;
	स_रखो(&ip->i_imap, 0, माप(काष्ठा xfs_imap));
	ip->i_afp = शून्य;
	ip->i_cowfp = शून्य;
	स_रखो(&ip->i_df, 0, माप(ip->i_df));
	ip->i_flags = 0;
	ip->i_delayed_blks = 0;
	ip->i_dअगरlags2 = mp->m_ino_geo.new_dअगरlags2;
	ip->i_nblocks = 0;
	ip->i_विभाजनoff = 0;
	ip->i_sick = 0;
	ip->i_checked = 0;
	INIT_WORK(&ip->i_ioend_work, xfs_end_io);
	INIT_LIST_HEAD(&ip->i_ioend_list);
	spin_lock_init(&ip->i_ioend_lock);

	वापस ip;
पूर्ण

STATIC व्योम
xfs_inode_मुक्त_callback(
	काष्ठा rcu_head		*head)
अणु
	काष्ठा inode		*inode = container_of(head, काष्ठा inode, i_rcu);
	काष्ठा xfs_inode	*ip = XFS_I(inode);

	चयन (VFS_I(ip)->i_mode & S_IFMT) अणु
	हाल S_IFREG:
	हाल S_IFसूची:
	हाल S_IFLNK:
		xfs_idestroy_विभाजन(&ip->i_df);
		अवरोध;
	पूर्ण

	अगर (ip->i_afp) अणु
		xfs_idestroy_विभाजन(ip->i_afp);
		kmem_cache_मुक्त(xfs_अगरork_zone, ip->i_afp);
	पूर्ण
	अगर (ip->i_cowfp) अणु
		xfs_idestroy_विभाजन(ip->i_cowfp);
		kmem_cache_मुक्त(xfs_अगरork_zone, ip->i_cowfp);
	पूर्ण
	अगर (ip->i_itemp) अणु
		ASSERT(!test_bit(XFS_LI_IN_AIL,
				 &ip->i_itemp->ili_item.li_flags));
		xfs_inode_item_destroy(ip);
		ip->i_itemp = शून्य;
	पूर्ण

	kmem_cache_मुक्त(xfs_inode_zone, ip);
पूर्ण

अटल व्योम
__xfs_inode_मुक्त(
	काष्ठा xfs_inode	*ip)
अणु
	/* निश्चितs to verअगरy all state is correct here */
	ASSERT(atomic_पढ़ो(&ip->i_pincount) == 0);
	ASSERT(!ip->i_itemp || list_empty(&ip->i_itemp->ili_item.li_bio_list));
	XFS_STATS_DEC(ip->i_mount, vn_active);

	call_rcu(&VFS_I(ip)->i_rcu, xfs_inode_मुक्त_callback);
पूर्ण

व्योम
xfs_inode_मुक्त(
	काष्ठा xfs_inode	*ip)
अणु
	ASSERT(!xfs_अगरlags_test(ip, XFS_IFLUSHING));

	/*
	 * Because we use RCU मुक्तing we need to ensure the inode always
	 * appears to be reclaimed with an invalid inode number when in the
	 * मुक्त state. The ip->i_flags_lock provides the barrier against lookup
	 * races.
	 */
	spin_lock(&ip->i_flags_lock);
	ip->i_flags = XFS_IRECLAIM;
	ip->i_ino = 0;
	spin_unlock(&ip->i_flags_lock);

	__xfs_inode_मुक्त(ip);
पूर्ण

/*
 * Queue background inode reclaim work अगर there are reclaimable inodes and there
 * isn't reclaim work alपढ़ोy scheduled or in progress.
 */
अटल व्योम
xfs_reclaim_work_queue(
	काष्ठा xfs_mount        *mp)
अणु

	rcu_पढ़ो_lock();
	अगर (radix_tree_tagged(&mp->m_perag_tree, XFS_ICI_RECLAIM_TAG)) अणु
		queue_delayed_work(mp->m_reclaim_workqueue, &mp->m_reclaim_work,
			msecs_to_jअगरfies(xfs_syncd_centisecs / 6 * 10));
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
xfs_perag_set_reclaim_tag(
	काष्ठा xfs_perag	*pag)
अणु
	काष्ठा xfs_mount	*mp = pag->pag_mount;

	lockdep_निश्चित_held(&pag->pag_ici_lock);
	अगर (pag->pag_ici_reclaimable++)
		वापस;

	/* propagate the reclaim tag up पूर्णांकo the perag radix tree */
	spin_lock(&mp->m_perag_lock);
	radix_tree_tag_set(&mp->m_perag_tree, pag->pag_agno,
			   XFS_ICI_RECLAIM_TAG);
	spin_unlock(&mp->m_perag_lock);

	/* schedule periodic background inode reclaim */
	xfs_reclaim_work_queue(mp);

	trace_xfs_perag_set_reclaim(mp, pag->pag_agno, -1, _RET_IP_);
पूर्ण

अटल व्योम
xfs_perag_clear_reclaim_tag(
	काष्ठा xfs_perag	*pag)
अणु
	काष्ठा xfs_mount	*mp = pag->pag_mount;

	lockdep_निश्चित_held(&pag->pag_ici_lock);
	अगर (--pag->pag_ici_reclaimable)
		वापस;

	/* clear the reclaim tag from the perag radix tree */
	spin_lock(&mp->m_perag_lock);
	radix_tree_tag_clear(&mp->m_perag_tree, pag->pag_agno,
			     XFS_ICI_RECLAIM_TAG);
	spin_unlock(&mp->m_perag_lock);
	trace_xfs_perag_clear_reclaim(mp, pag->pag_agno, -1, _RET_IP_);
पूर्ण


/*
 * We set the inode flag atomically with the radix tree tag.
 * Once we get tag lookups on the radix tree, this inode flag
 * can go away.
 */
व्योम
xfs_inode_set_reclaim_tag(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_perag	*pag;

	pag = xfs_perag_get(mp, XFS_INO_TO_AGNO(mp, ip->i_ino));
	spin_lock(&pag->pag_ici_lock);
	spin_lock(&ip->i_flags_lock);

	radix_tree_tag_set(&pag->pag_ici_root, XFS_INO_TO_AGINO(mp, ip->i_ino),
			   XFS_ICI_RECLAIM_TAG);
	xfs_perag_set_reclaim_tag(pag);
	__xfs_अगरlags_set(ip, XFS_IRECLAIMABLE);

	spin_unlock(&ip->i_flags_lock);
	spin_unlock(&pag->pag_ici_lock);
	xfs_perag_put(pag);
पूर्ण

STATIC व्योम
xfs_inode_clear_reclaim_tag(
	काष्ठा xfs_perag	*pag,
	xfs_ino_t		ino)
अणु
	radix_tree_tag_clear(&pag->pag_ici_root,
			     XFS_INO_TO_AGINO(pag->pag_mount, ino),
			     XFS_ICI_RECLAIM_TAG);
	xfs_perag_clear_reclaim_tag(pag);
पूर्ण

अटल व्योम
xfs_inew_रुको(
	काष्ठा xfs_inode	*ip)
अणु
	रुको_queue_head_t *wq = bit_रुकोqueue(&ip->i_flags, __XFS_INEW_BIT);
	DEFINE_WAIT_BIT(रुको, &ip->i_flags, __XFS_INEW_BIT);

	करो अणु
		prepare_to_रुको(wq, &रुको.wq_entry, TASK_UNINTERRUPTIBLE);
		अगर (!xfs_अगरlags_test(ip, XFS_INEW))
			अवरोध;
		schedule();
	पूर्ण जबतक (true);
	finish_रुको(wq, &रुको.wq_entry);
पूर्ण

/*
 * When we recycle a reclaimable inode, we need to re-initialise the VFS inode
 * part of the काष्ठाure. This is made more complex by the fact we store
 * inक्रमmation about the on-disk values in the VFS inode and so we can't just
 * overग_लिखो the values unconditionally. Hence we save the parameters we
 * need to retain across reinitialisation, and reग_लिखो them पूर्णांकo the VFS inode
 * after reinitialisation even अगर it fails.
 */
अटल पूर्णांक
xfs_reinit_inode(
	काष्ठा xfs_mount	*mp,
	काष्ठा inode		*inode)
अणु
	पूर्णांक		error;
	uपूर्णांक32_t	nlink = inode->i_nlink;
	uपूर्णांक32_t	generation = inode->i_generation;
	uपूर्णांक64_t	version = inode_peek_iversion(inode);
	umode_t		mode = inode->i_mode;
	dev_t		dev = inode->i_rdev;
	kuid_t		uid = inode->i_uid;
	kgid_t		gid = inode->i_gid;

	error = inode_init_always(mp->m_super, inode);

	set_nlink(inode, nlink);
	inode->i_generation = generation;
	inode_set_iversion_queried(inode, version);
	inode->i_mode = mode;
	inode->i_rdev = dev;
	inode->i_uid = uid;
	inode->i_gid = gid;
	वापस error;
पूर्ण

/*
 * If we are allocating a new inode, then check what was वापसed is
 * actually a मुक्त, empty inode. If we are not allocating an inode,
 * then check we didn't find a मुक्त inode.
 *
 * Returns:
 *	0		अगर the inode मुक्त state matches the lookup context
 *	-ENOENT		अगर the inode is मुक्त and we are not allocating
 *	-EFSCORRUPTED	अगर there is any state mismatch at all
 */
अटल पूर्णांक
xfs_iget_check_मुक्त_state(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			flags)
अणु
	अगर (flags & XFS_IGET_CREATE) अणु
		/* should be a मुक्त inode */
		अगर (VFS_I(ip)->i_mode != 0) अणु
			xfs_warn(ip->i_mount,
"Corruption detected! Free inode 0x%llx not marked free! (mode 0x%x)",
				ip->i_ino, VFS_I(ip)->i_mode);
			वापस -EFSCORRUPTED;
		पूर्ण

		अगर (ip->i_nblocks != 0) अणु
			xfs_warn(ip->i_mount,
"Corruption detected! Free inode 0x%llx has blocks allocated!",
				ip->i_ino);
			वापस -EFSCORRUPTED;
		पूर्ण
		वापस 0;
	पूर्ण

	/* should be an allocated inode */
	अगर (VFS_I(ip)->i_mode == 0)
		वापस -ENOENT;

	वापस 0;
पूर्ण

/*
 * Check the validity of the inode we just found it the cache
 */
अटल पूर्णांक
xfs_iget_cache_hit(
	काष्ठा xfs_perag	*pag,
	काष्ठा xfs_inode	*ip,
	xfs_ino_t		ino,
	पूर्णांक			flags,
	पूर्णांक			lock_flags) __releases(RCU)
अणु
	काष्ठा inode		*inode = VFS_I(ip);
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			error;

	/*
	 * check क्रम re-use of an inode within an RCU grace period due to the
	 * radix tree nodes not being updated yet. We monitor क्रम this by
	 * setting the inode number to zero beक्रमe मुक्तing the inode काष्ठाure.
	 * If the inode has been पुनः_स्मृतिated and set up, then the inode number
	 * will not match, so check क्रम that, too.
	 */
	spin_lock(&ip->i_flags_lock);
	अगर (ip->i_ino != ino) अणु
		trace_xfs_iget_skip(ip);
		XFS_STATS_INC(mp, xs_ig_frecycle);
		error = -EAGAIN;
		जाओ out_error;
	पूर्ण


	/*
	 * If we are racing with another cache hit that is currently
	 * instantiating this inode or currently recycling it out of
	 * reclaimabe state, रुको क्रम the initialisation to complete
	 * beक्रमe continuing.
	 *
	 * XXX(hch): eventually we should करो something equivalent to
	 *	     रुको_on_inode to रुको क्रम these flags to be cleared
	 *	     instead of polling क्रम it.
	 */
	अगर (ip->i_flags & (XFS_INEW|XFS_IRECLAIM)) अणु
		trace_xfs_iget_skip(ip);
		XFS_STATS_INC(mp, xs_ig_frecycle);
		error = -EAGAIN;
		जाओ out_error;
	पूर्ण

	/*
	 * Check the inode मुक्त state is valid. This also detects lookup
	 * racing with unlinks.
	 */
	error = xfs_iget_check_मुक्त_state(ip, flags);
	अगर (error)
		जाओ out_error;

	/*
	 * If IRECLAIMABLE is set, we've torn करोwn the VFS inode alपढ़ोy.
	 * Need to carefully get it back पूर्णांकo useable state.
	 */
	अगर (ip->i_flags & XFS_IRECLAIMABLE) अणु
		trace_xfs_iget_reclaim(ip);

		अगर (flags & XFS_IGET_INCORE) अणु
			error = -EAGAIN;
			जाओ out_error;
		पूर्ण

		/*
		 * We need to set XFS_IRECLAIM to prevent xfs_reclaim_inode
		 * from stomping over us जबतक we recycle the inode.  We can't
		 * clear the radix tree reclaimable tag yet as it requires
		 * pag_ici_lock to be held exclusive.
		 */
		ip->i_flags |= XFS_IRECLAIM;

		spin_unlock(&ip->i_flags_lock);
		rcu_पढ़ो_unlock();

		ASSERT(!rwsem_is_locked(&inode->i_rwsem));
		error = xfs_reinit_inode(mp, inode);
		अगर (error) अणु
			bool wake;
			/*
			 * Re-initializing the inode failed, and we are in deep
			 * trouble.  Try to re-add it to the reclaim list.
			 */
			rcu_पढ़ो_lock();
			spin_lock(&ip->i_flags_lock);
			wake = !!__xfs_अगरlags_test(ip, XFS_INEW);
			ip->i_flags &= ~(XFS_INEW | XFS_IRECLAIM);
			अगर (wake)
				wake_up_bit(&ip->i_flags, __XFS_INEW_BIT);
			ASSERT(ip->i_flags & XFS_IRECLAIMABLE);
			trace_xfs_iget_reclaim_fail(ip);
			जाओ out_error;
		पूर्ण

		spin_lock(&pag->pag_ici_lock);
		spin_lock(&ip->i_flags_lock);

		/*
		 * Clear the per-lअगरeसमय state in the inode as we are now
		 * effectively a new inode and need to वापस to the initial
		 * state beक्रमe reuse occurs.
		 */
		ip->i_flags &= ~XFS_IRECLAIM_RESET_FLAGS;
		ip->i_flags |= XFS_INEW;
		xfs_inode_clear_reclaim_tag(pag, ip->i_ino);
		inode->i_state = I_NEW;
		ip->i_sick = 0;
		ip->i_checked = 0;

		spin_unlock(&ip->i_flags_lock);
		spin_unlock(&pag->pag_ici_lock);
	पूर्ण अन्यथा अणु
		/* If the VFS inode is being torn करोwn, छोड़ो and try again. */
		अगर (!igrab(inode)) अणु
			trace_xfs_iget_skip(ip);
			error = -EAGAIN;
			जाओ out_error;
		पूर्ण

		/* We've got a live one. */
		spin_unlock(&ip->i_flags_lock);
		rcu_पढ़ो_unlock();
		trace_xfs_iget_hit(ip);
	पूर्ण

	अगर (lock_flags != 0)
		xfs_ilock(ip, lock_flags);

	अगर (!(flags & XFS_IGET_INCORE))
		xfs_अगरlags_clear(ip, XFS_ISTALE);
	XFS_STATS_INC(mp, xs_ig_found);

	वापस 0;

out_error:
	spin_unlock(&ip->i_flags_lock);
	rcu_पढ़ो_unlock();
	वापस error;
पूर्ण


अटल पूर्णांक
xfs_iget_cache_miss(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_perag	*pag,
	xfs_trans_t		*tp,
	xfs_ino_t		ino,
	काष्ठा xfs_inode	**ipp,
	पूर्णांक			flags,
	पूर्णांक			lock_flags)
अणु
	काष्ठा xfs_inode	*ip;
	पूर्णांक			error;
	xfs_agino_t		agino = XFS_INO_TO_AGINO(mp, ino);
	पूर्णांक			अगरlags;

	ip = xfs_inode_alloc(mp, ino);
	अगर (!ip)
		वापस -ENOMEM;

	error = xfs_imap(mp, tp, ip->i_ino, &ip->i_imap, flags);
	अगर (error)
		जाओ out_destroy;

	/*
	 * For version 5 superblocks, अगर we are initialising a new inode and we
	 * are not utilising the XFS_MOUNT_IKEEP inode cluster mode, we can
	 * simply build the new inode core with a अक्रमom generation number.
	 *
	 * For version 4 (and older) superblocks, log recovery is dependent on
	 * the i_flushiter field being initialised from the current on-disk
	 * value and hence we must also पढ़ो the inode off disk even when
	 * initializing new inodes.
	 */
	अगर (xfs_sb_version_has_v3inode(&mp->m_sb) &&
	    (flags & XFS_IGET_CREATE) && !(mp->m_flags & XFS_MOUNT_IKEEP)) अणु
		VFS_I(ip)->i_generation = pअक्रमom_u32();
	पूर्ण अन्यथा अणु
		काष्ठा xfs_buf		*bp;

		error = xfs_imap_to_bp(mp, tp, &ip->i_imap, &bp);
		अगर (error)
			जाओ out_destroy;

		error = xfs_inode_from_disk(ip,
				xfs_buf_offset(bp, ip->i_imap.im_boffset));
		अगर (!error)
			xfs_buf_set_ref(bp, XFS_INO_REF);
		xfs_trans_brअन्यथा(tp, bp);

		अगर (error)
			जाओ out_destroy;
	पूर्ण

	trace_xfs_iget_miss(ip);

	/*
	 * Check the inode मुक्त state is valid. This also detects lookup
	 * racing with unlinks.
	 */
	error = xfs_iget_check_मुक्त_state(ip, flags);
	अगर (error)
		जाओ out_destroy;

	/*
	 * Preload the radix tree so we can insert safely under the
	 * ग_लिखो spinlock. Note that we cannot sleep inside the preload
	 * region. Since we can be called from transaction context, करोn't
	 * recurse पूर्णांकo the file प्रणाली.
	 */
	अगर (radix_tree_preload(GFP_NOFS)) अणु
		error = -EAGAIN;
		जाओ out_destroy;
	पूर्ण

	/*
	 * Because the inode hasn't been added to the radix-tree yet it can't
	 * be found by another thपढ़ो, so we can करो the non-sleeping lock here.
	 */
	अगर (lock_flags) अणु
		अगर (!xfs_ilock_noरुको(ip, lock_flags))
			BUG();
	पूर्ण

	/*
	 * These values must be set beक्रमe inserting the inode पूर्णांकo the radix
	 * tree as the moment it is inserted a concurrent lookup (allowed by the
	 * RCU locking mechanism) can find it and that lookup must see that this
	 * is an inode currently under स्थिरruction (i.e. that XFS_INEW is set).
	 * The ip->i_flags_lock that protects the XFS_INEW flag क्रमms the
	 * memory barrier that ensures this detection works correctly at lookup
	 * समय.
	 */
	अगरlags = XFS_INEW;
	अगर (flags & XFS_IGET_DONTCACHE)
		d_mark_करोntcache(VFS_I(ip));
	ip->i_udquot = शून्य;
	ip->i_gdquot = शून्य;
	ip->i_pdquot = शून्य;
	xfs_अगरlags_set(ip, अगरlags);

	/* insert the new inode */
	spin_lock(&pag->pag_ici_lock);
	error = radix_tree_insert(&pag->pag_ici_root, agino, ip);
	अगर (unlikely(error)) अणु
		WARN_ON(error != -EEXIST);
		XFS_STATS_INC(mp, xs_ig_dup);
		error = -EAGAIN;
		जाओ out_preload_end;
	पूर्ण
	spin_unlock(&pag->pag_ici_lock);
	radix_tree_preload_end();

	*ipp = ip;
	वापस 0;

out_preload_end:
	spin_unlock(&pag->pag_ici_lock);
	radix_tree_preload_end();
	अगर (lock_flags)
		xfs_iunlock(ip, lock_flags);
out_destroy:
	__destroy_inode(VFS_I(ip));
	xfs_inode_मुक्त(ip);
	वापस error;
पूर्ण

/*
 * Look up an inode by number in the given file प्रणाली.  The inode is looked up
 * in the cache held in each AG.  If the inode is found in the cache, initialise
 * the vfs inode अगर necessary.
 *
 * If it is not in core, पढ़ो it in from the file प्रणाली's device, add it to the
 * cache and initialise the vfs inode.
 *
 * The inode is locked according to the value of the lock_flags parameter.
 * Inode lookup is only करोne during metadata operations and not as part of the
 * data IO path. Hence we only allow locking of the XFS_ILOCK during lookup.
 */
पूर्णांक
xfs_iget(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_ino_t		ino,
	uपूर्णांक			flags,
	uपूर्णांक			lock_flags,
	काष्ठा xfs_inode	**ipp)
अणु
	काष्ठा xfs_inode	*ip;
	काष्ठा xfs_perag	*pag;
	xfs_agino_t		agino;
	पूर्णांक			error;

	ASSERT((lock_flags & (XFS_IOLOCK_EXCL | XFS_IOLOCK_SHARED)) == 0);

	/* reject inode numbers outside existing AGs */
	अगर (!ino || XFS_INO_TO_AGNO(mp, ino) >= mp->m_sb.sb_agcount)
		वापस -EINVAL;

	XFS_STATS_INC(mp, xs_ig_attempts);

	/* get the perag काष्ठाure and ensure that it's inode capable */
	pag = xfs_perag_get(mp, XFS_INO_TO_AGNO(mp, ino));
	agino = XFS_INO_TO_AGINO(mp, ino);

again:
	error = 0;
	rcu_पढ़ो_lock();
	ip = radix_tree_lookup(&pag->pag_ici_root, agino);

	अगर (ip) अणु
		error = xfs_iget_cache_hit(pag, ip, ino, flags, lock_flags);
		अगर (error)
			जाओ out_error_or_again;
	पूर्ण अन्यथा अणु
		rcu_पढ़ो_unlock();
		अगर (flags & XFS_IGET_INCORE) अणु
			error = -ENODATA;
			जाओ out_error_or_again;
		पूर्ण
		XFS_STATS_INC(mp, xs_ig_missed);

		error = xfs_iget_cache_miss(mp, pag, tp, ino, &ip,
							flags, lock_flags);
		अगर (error)
			जाओ out_error_or_again;
	पूर्ण
	xfs_perag_put(pag);

	*ipp = ip;

	/*
	 * If we have a real type क्रम an on-disk inode, we can setup the inode
	 * now.	 If it's a new inode being created, xfs_ialloc will handle it.
	 */
	अगर (xfs_अगरlags_test(ip, XFS_INEW) && VFS_I(ip)->i_mode != 0)
		xfs_setup_existing_inode(ip);
	वापस 0;

out_error_or_again:
	अगर (!(flags & XFS_IGET_INCORE) && error == -EAGAIN) अणु
		delay(1);
		जाओ again;
	पूर्ण
	xfs_perag_put(pag);
	वापस error;
पूर्ण

/*
 * "Is this a cached inode that's also allocated?"
 *
 * Look up an inode by number in the given file प्रणाली.  If the inode is
 * in cache and isn't in purgatory, वापस 1 अगर the inode is allocated
 * and 0 अगर it is not.  For all other हालs (not in cache, being torn
 * करोwn, etc.), वापस a negative error code.
 *
 * The caller has to prevent inode allocation and मुक्तing activity,
 * presumably by locking the AGI buffer.   This is to ensure that an
 * inode cannot transition from allocated to मुक्तd until the caller is
 * पढ़ोy to allow that.  If the inode is in an पूर्णांकermediate state (new,
 * reclaimable, or being reclaimed), -EAGAIN will be वापसed; अगर the
 * inode is not in the cache, -ENOENT will be वापसed.  The caller must
 * deal with these scenarios appropriately.
 *
 * This is a specialized use हाल क्रम the online scrubber; अगर you're
 * पढ़ोing this, you probably want xfs_iget.
 */
पूर्णांक
xfs_icache_inode_is_allocated(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_ino_t		ino,
	bool			*inuse)
अणु
	काष्ठा xfs_inode	*ip;
	पूर्णांक			error;

	error = xfs_iget(mp, tp, ino, XFS_IGET_INCORE, 0, &ip);
	अगर (error)
		वापस error;

	*inuse = !!(VFS_I(ip)->i_mode);
	xfs_irele(ip);
	वापस 0;
पूर्ण

/*
 * The inode lookup is करोne in batches to keep the amount of lock traffic and
 * radix tree lookups to a minimum. The batch size is a trade off between
 * lookup reduction and stack usage. This is in the reclaim path, so we can't
 * be too greedy.
 */
#घोषणा XFS_LOOKUP_BATCH	32

/*
 * Decide अगर the given @ip is eligible to be a part of the inode walk, and
 * grab it अगर so.  Returns true अगर it's पढ़ोy to go or false अगर we should just
 * ignore it.
 */
STATIC bool
xfs_inode_walk_ag_grab(
	काष्ठा xfs_inode	*ip,
	पूर्णांक			flags)
अणु
	काष्ठा inode		*inode = VFS_I(ip);
	bool			newinos = !!(flags & XFS_INODE_WALK_INEW_WAIT);

	ASSERT(rcu_पढ़ो_lock_held());

	/* Check क्रम stale RCU मुक्तd inode */
	spin_lock(&ip->i_flags_lock);
	अगर (!ip->i_ino)
		जाओ out_unlock_noent;

	/* aव्योम new or reclaimable inodes. Leave क्रम reclaim code to flush */
	अगर ((!newinos && __xfs_अगरlags_test(ip, XFS_INEW)) ||
	    __xfs_अगरlags_test(ip, XFS_IRECLAIMABLE | XFS_IRECLAIM))
		जाओ out_unlock_noent;
	spin_unlock(&ip->i_flags_lock);

	/* nothing to sync during shutकरोwn */
	अगर (XFS_FORCED_SHUTDOWN(ip->i_mount))
		वापस false;

	/* If we can't grab the inode, it must on it's way to reclaim. */
	अगर (!igrab(inode))
		वापस false;

	/* inode is valid */
	वापस true;

out_unlock_noent:
	spin_unlock(&ip->i_flags_lock);
	वापस false;
पूर्ण

/*
 * For a given per-AG काष्ठाure @pag, grab, @execute, and rele all incore
 * inodes with the given radix tree @tag.
 */
STATIC पूर्णांक
xfs_inode_walk_ag(
	काष्ठा xfs_perag	*pag,
	पूर्णांक			iter_flags,
	पूर्णांक			(*execute)(काष्ठा xfs_inode *ip, व्योम *args),
	व्योम			*args,
	पूर्णांक			tag)
अणु
	काष्ठा xfs_mount	*mp = pag->pag_mount;
	uपूर्णांक32_t		first_index;
	पूर्णांक			last_error = 0;
	पूर्णांक			skipped;
	bool			करोne;
	पूर्णांक			nr_found;

restart:
	करोne = false;
	skipped = 0;
	first_index = 0;
	nr_found = 0;
	करो अणु
		काष्ठा xfs_inode *batch[XFS_LOOKUP_BATCH];
		पूर्णांक		error = 0;
		पूर्णांक		i;

		rcu_पढ़ो_lock();

		अगर (tag == XFS_ICI_NO_TAG)
			nr_found = radix_tree_gang_lookup(&pag->pag_ici_root,
					(व्योम **)batch, first_index,
					XFS_LOOKUP_BATCH);
		अन्यथा
			nr_found = radix_tree_gang_lookup_tag(
					&pag->pag_ici_root,
					(व्योम **) batch, first_index,
					XFS_LOOKUP_BATCH, tag);

		अगर (!nr_found) अणु
			rcu_पढ़ो_unlock();
			अवरोध;
		पूर्ण

		/*
		 * Grab the inodes beक्रमe we drop the lock. अगर we found
		 * nothing, nr == 0 and the loop will be skipped.
		 */
		क्रम (i = 0; i < nr_found; i++) अणु
			काष्ठा xfs_inode *ip = batch[i];

			अगर (करोne || !xfs_inode_walk_ag_grab(ip, iter_flags))
				batch[i] = शून्य;

			/*
			 * Update the index क्रम the next lookup. Catch
			 * overflows पूर्णांकo the next AG range which can occur अगर
			 * we have inodes in the last block of the AG and we
			 * are currently poपूर्णांकing to the last inode.
			 *
			 * Because we may see inodes that are from the wrong AG
			 * due to RCU मुक्तing and पुनः_स्मृतिation, only update the
			 * index अगर it lies in this AG. It was a race that lead
			 * us to see this inode, so another lookup from the
			 * same index will not find it again.
			 */
			अगर (XFS_INO_TO_AGNO(mp, ip->i_ino) != pag->pag_agno)
				जारी;
			first_index = XFS_INO_TO_AGINO(mp, ip->i_ino + 1);
			अगर (first_index < XFS_INO_TO_AGINO(mp, ip->i_ino))
				करोne = true;
		पूर्ण

		/* unlock now we've grabbed the inodes. */
		rcu_पढ़ो_unlock();

		क्रम (i = 0; i < nr_found; i++) अणु
			अगर (!batch[i])
				जारी;
			अगर ((iter_flags & XFS_INODE_WALK_INEW_WAIT) &&
			    xfs_अगरlags_test(batch[i], XFS_INEW))
				xfs_inew_रुको(batch[i]);
			error = execute(batch[i], args);
			xfs_irele(batch[i]);
			अगर (error == -EAGAIN) अणु
				skipped++;
				जारी;
			पूर्ण
			अगर (error && last_error != -EFSCORRUPTED)
				last_error = error;
		पूर्ण

		/* bail out अगर the fileप्रणाली is corrupted.  */
		अगर (error == -EFSCORRUPTED)
			अवरोध;

		cond_resched();

	पूर्ण जबतक (nr_found && !करोne);

	अगर (skipped) अणु
		delay(1);
		जाओ restart;
	पूर्ण
	वापस last_error;
पूर्ण

/* Fetch the next (possibly tagged) per-AG काष्ठाure. */
अटल अंतरभूत काष्ठा xfs_perag *
xfs_inode_walk_get_perag(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno,
	पूर्णांक			tag)
अणु
	अगर (tag == XFS_ICI_NO_TAG)
		वापस xfs_perag_get(mp, agno);
	वापस xfs_perag_get_tag(mp, agno, tag);
पूर्ण

/*
 * Call the @execute function on all incore inodes matching the radix tree
 * @tag.
 */
पूर्णांक
xfs_inode_walk(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			iter_flags,
	पूर्णांक			(*execute)(काष्ठा xfs_inode *ip, व्योम *args),
	व्योम			*args,
	पूर्णांक			tag)
अणु
	काष्ठा xfs_perag	*pag;
	पूर्णांक			error = 0;
	पूर्णांक			last_error = 0;
	xfs_agnumber_t		ag;

	ag = 0;
	जबतक ((pag = xfs_inode_walk_get_perag(mp, ag, tag))) अणु
		ag = pag->pag_agno + 1;
		error = xfs_inode_walk_ag(pag, iter_flags, execute, args, tag);
		xfs_perag_put(pag);
		अगर (error) अणु
			last_error = error;
			अगर (error == -EFSCORRUPTED)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस last_error;
पूर्ण

/*
 * Grab the inode क्रम reclaim exclusively.
 *
 * We have found this inode via a lookup under RCU, so the inode may have
 * alपढ़ोy been मुक्तd, or it may be in the process of being recycled by
 * xfs_iget(). In both हालs, the inode will have XFS_IRECLAIM set. If the inode
 * has been fully recycled by the समय we get the i_flags_lock, XFS_IRECLAIMABLE
 * will not be set. Hence we need to check क्रम both these flag conditions to
 * aव्योम inodes that are no दीर्घer reclaim candidates.
 *
 * Note: checking क्रम other state flags here, under the i_flags_lock or not, is
 * racy and should be aव्योमed. Those races should be resolved only after we have
 * ensured that we are able to reclaim this inode and the world can see that we
 * are going to reclaim it.
 *
 * Return true अगर we grabbed it, false otherwise.
 */
अटल bool
xfs_reclaim_inode_grab(
	काष्ठा xfs_inode	*ip)
अणु
	ASSERT(rcu_पढ़ो_lock_held());

	spin_lock(&ip->i_flags_lock);
	अगर (!__xfs_अगरlags_test(ip, XFS_IRECLAIMABLE) ||
	    __xfs_अगरlags_test(ip, XFS_IRECLAIM)) अणु
		/* not a reclaim candidate. */
		spin_unlock(&ip->i_flags_lock);
		वापस false;
	पूर्ण
	__xfs_अगरlags_set(ip, XFS_IRECLAIM);
	spin_unlock(&ip->i_flags_lock);
	वापस true;
पूर्ण

/*
 * Inode reclaim is non-blocking, so the शेष action अगर progress cannot be
 * made is to "requeue" the inode क्रम reclaim by unlocking it and clearing the
 * XFS_IRECLAIM flag.  If we are in a shutकरोwn state, we करोn't care about
 * blocking anymore and hence we can रुको क्रम the inode to be able to reclaim
 * it.
 *
 * We करो no IO here - अगर callers require inodes to be cleaned they must push the
 * AIL first to trigger ग_लिखोback of dirty inodes.  This enables ग_लिखोback to be
 * करोne in the background in a non-blocking manner, and enables memory reclaim
 * to make progress without blocking.
 */
अटल व्योम
xfs_reclaim_inode(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_perag	*pag)
अणु
	xfs_ino_t		ino = ip->i_ino; /* क्रम radix_tree_delete */

	अगर (!xfs_ilock_noरुको(ip, XFS_ILOCK_EXCL))
		जाओ out;
	अगर (xfs_अगरlags_test_and_set(ip, XFS_IFLUSHING))
		जाओ out_iunlock;

	अगर (XFS_FORCED_SHUTDOWN(ip->i_mount)) अणु
		xfs_iunpin_रुको(ip);
		xfs_अगरlush_पात(ip);
		जाओ reclaim;
	पूर्ण
	अगर (xfs_ipincount(ip))
		जाओ out_clear_flush;
	अगर (!xfs_inode_clean(ip))
		जाओ out_clear_flush;

	xfs_अगरlags_clear(ip, XFS_IFLUSHING);
reclaim:

	/*
	 * Because we use RCU मुक्तing we need to ensure the inode always appears
	 * to be reclaimed with an invalid inode number when in the मुक्त state.
	 * We करो this as early as possible under the ILOCK so that
	 * xfs_अगरlush_cluster() and xfs_अगरree_cluster() can be guaranteed to
	 * detect races with us here. By करोing this, we guarantee that once
	 * xfs_अगरlush_cluster() or xfs_अगरree_cluster() has locked XFS_ILOCK that
	 * it will see either a valid inode that will serialise correctly, or it
	 * will see an invalid inode that it can skip.
	 */
	spin_lock(&ip->i_flags_lock);
	ip->i_flags = XFS_IRECLAIM;
	ip->i_ino = 0;
	spin_unlock(&ip->i_flags_lock);

	xfs_iunlock(ip, XFS_ILOCK_EXCL);

	XFS_STATS_INC(ip->i_mount, xs_ig_reclaims);
	/*
	 * Remove the inode from the per-AG radix tree.
	 *
	 * Because radix_tree_delete won't complain even अगर the item was never
	 * added to the tree निश्चित that it's been there beक्रमe to catch
	 * problems with the inode lअगरe समय early on.
	 */
	spin_lock(&pag->pag_ici_lock);
	अगर (!radix_tree_delete(&pag->pag_ici_root,
				XFS_INO_TO_AGINO(ip->i_mount, ino)))
		ASSERT(0);
	xfs_perag_clear_reclaim_tag(pag);
	spin_unlock(&pag->pag_ici_lock);

	/*
	 * Here we करो an (almost) spurious inode lock in order to coordinate
	 * with inode cache radix tree lookups.  This is because the lookup
	 * can reference the inodes in the cache without taking references.
	 *
	 * We make that OK here by ensuring that we रुको until the inode is
	 * unlocked after the lookup beक्रमe we go ahead and मुक्त it.
	 */
	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_qm_dqdetach(ip);
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	ASSERT(xfs_inode_clean(ip));

	__xfs_inode_मुक्त(ip);
	वापस;

out_clear_flush:
	xfs_अगरlags_clear(ip, XFS_IFLUSHING);
out_iunlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
out:
	xfs_अगरlags_clear(ip, XFS_IRECLAIM);
पूर्ण

/*
 * Walk the AGs and reclaim the inodes in them. Even अगर the fileप्रणाली is
 * corrupted, we still want to try to reclaim all the inodes. If we करोn't,
 * then a shut करोwn during fileप्रणाली unmount reclaim walk leak all the
 * unreclaimed inodes.
 *
 * Returns non-zero अगर any AGs or inodes were skipped in the reclaim pass
 * so that callers that want to block until all dirty inodes are written back
 * and reclaimed can sanely loop.
 */
अटल व्योम
xfs_reclaim_inodes_ag(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			*nr_to_scan)
अणु
	काष्ठा xfs_perag	*pag;
	xfs_agnumber_t		ag = 0;

	जबतक ((pag = xfs_perag_get_tag(mp, ag, XFS_ICI_RECLAIM_TAG))) अणु
		अचिन्हित दीर्घ	first_index = 0;
		पूर्णांक		करोne = 0;
		पूर्णांक		nr_found = 0;

		ag = pag->pag_agno + 1;

		first_index = READ_ONCE(pag->pag_ici_reclaim_cursor);
		करो अणु
			काष्ठा xfs_inode *batch[XFS_LOOKUP_BATCH];
			पूर्णांक	i;

			rcu_पढ़ो_lock();
			nr_found = radix_tree_gang_lookup_tag(
					&pag->pag_ici_root,
					(व्योम **)batch, first_index,
					XFS_LOOKUP_BATCH,
					XFS_ICI_RECLAIM_TAG);
			अगर (!nr_found) अणु
				करोne = 1;
				rcu_पढ़ो_unlock();
				अवरोध;
			पूर्ण

			/*
			 * Grab the inodes beक्रमe we drop the lock. अगर we found
			 * nothing, nr == 0 and the loop will be skipped.
			 */
			क्रम (i = 0; i < nr_found; i++) अणु
				काष्ठा xfs_inode *ip = batch[i];

				अगर (करोne || !xfs_reclaim_inode_grab(ip))
					batch[i] = शून्य;

				/*
				 * Update the index क्रम the next lookup. Catch
				 * overflows पूर्णांकo the next AG range which can
				 * occur अगर we have inodes in the last block of
				 * the AG and we are currently poपूर्णांकing to the
				 * last inode.
				 *
				 * Because we may see inodes that are from the
				 * wrong AG due to RCU मुक्तing and
				 * पुनः_स्मृतिation, only update the index अगर it
				 * lies in this AG. It was a race that lead us
				 * to see this inode, so another lookup from
				 * the same index will not find it again.
				 */
				अगर (XFS_INO_TO_AGNO(mp, ip->i_ino) !=
								pag->pag_agno)
					जारी;
				first_index = XFS_INO_TO_AGINO(mp, ip->i_ino + 1);
				अगर (first_index < XFS_INO_TO_AGINO(mp, ip->i_ino))
					करोne = 1;
			पूर्ण

			/* unlock now we've grabbed the inodes. */
			rcu_पढ़ो_unlock();

			क्रम (i = 0; i < nr_found; i++) अणु
				अगर (batch[i])
					xfs_reclaim_inode(batch[i], pag);
			पूर्ण

			*nr_to_scan -= XFS_LOOKUP_BATCH;
			cond_resched();
		पूर्ण जबतक (nr_found && !करोne && *nr_to_scan > 0);

		अगर (करोne)
			first_index = 0;
		WRITE_ONCE(pag->pag_ici_reclaim_cursor, first_index);
		xfs_perag_put(pag);
	पूर्ण
पूर्ण

व्योम
xfs_reclaim_inodes(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक		nr_to_scan = पूर्णांक_उच्च;

	जबतक (radix_tree_tagged(&mp->m_perag_tree, XFS_ICI_RECLAIM_TAG)) अणु
		xfs_ail_push_all_sync(mp->m_ail);
		xfs_reclaim_inodes_ag(mp, &nr_to_scan);
	पूर्ण
पूर्ण

/*
 * The shrinker infraकाष्ठाure determines how many inodes we should scan क्रम
 * reclaim. We want as many clean inodes पढ़ोy to reclaim as possible, so we
 * push the AIL here. We also want to proactively मुक्त up memory अगर we can to
 * minimise the amount of work memory reclaim has to करो so we kick the
 * background reclaim अगर it isn't alपढ़ोy scheduled.
 */
दीर्घ
xfs_reclaim_inodes_nr(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			nr_to_scan)
अणु
	/* kick background reclaimer and push the AIL */
	xfs_reclaim_work_queue(mp);
	xfs_ail_push_all(mp->m_ail);

	xfs_reclaim_inodes_ag(mp, &nr_to_scan);
	वापस 0;
पूर्ण

/*
 * Return the number of reclaimable inodes in the fileप्रणाली क्रम
 * the shrinker to determine how much to reclaim.
 */
पूर्णांक
xfs_reclaim_inodes_count(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_perag	*pag;
	xfs_agnumber_t		ag = 0;
	पूर्णांक			reclaimable = 0;

	जबतक ((pag = xfs_perag_get_tag(mp, ag, XFS_ICI_RECLAIM_TAG))) अणु
		ag = pag->pag_agno + 1;
		reclaimable += pag->pag_ici_reclaimable;
		xfs_perag_put(pag);
	पूर्ण
	वापस reclaimable;
पूर्ण

STATIC bool
xfs_inode_match_id(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_eofblocks	*eofb)
अणु
	अगर ((eofb->eof_flags & XFS_खातापूर्ण_FLAGS_UID) &&
	    !uid_eq(VFS_I(ip)->i_uid, eofb->eof_uid))
		वापस false;

	अगर ((eofb->eof_flags & XFS_खातापूर्ण_FLAGS_GID) &&
	    !gid_eq(VFS_I(ip)->i_gid, eofb->eof_gid))
		वापस false;

	अगर ((eofb->eof_flags & XFS_खातापूर्ण_FLAGS_PRID) &&
	    ip->i_projid != eofb->eof_prid)
		वापस false;

	वापस true;
पूर्ण

/*
 * A जोड़-based inode filtering algorithm. Process the inode अगर any of the
 * criteria match. This is क्रम global/पूर्णांकernal scans only.
 */
STATIC bool
xfs_inode_match_id_जोड़(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_eofblocks	*eofb)
अणु
	अगर ((eofb->eof_flags & XFS_खातापूर्ण_FLAGS_UID) &&
	    uid_eq(VFS_I(ip)->i_uid, eofb->eof_uid))
		वापस true;

	अगर ((eofb->eof_flags & XFS_खातापूर्ण_FLAGS_GID) &&
	    gid_eq(VFS_I(ip)->i_gid, eofb->eof_gid))
		वापस true;

	अगर ((eofb->eof_flags & XFS_खातापूर्ण_FLAGS_PRID) &&
	    ip->i_projid == eofb->eof_prid)
		वापस true;

	वापस false;
पूर्ण

/*
 * Is this inode @ip eligible क्रम eof/cow block reclamation, given some
 * filtering parameters @eofb?  The inode is eligible अगर @eofb is null or
 * अगर the predicate functions match.
 */
अटल bool
xfs_inode_matches_eofb(
	काष्ठा xfs_inode	*ip,
	काष्ठा xfs_eofblocks	*eofb)
अणु
	bool			match;

	अगर (!eofb)
		वापस true;

	अगर (eofb->eof_flags & XFS_खातापूर्ण_FLAGS_UNION)
		match = xfs_inode_match_id_जोड़(ip, eofb);
	अन्यथा
		match = xfs_inode_match_id(ip, eofb);
	अगर (!match)
		वापस false;

	/* skip the inode अगर the file size is too small */
	अगर ((eofb->eof_flags & XFS_खातापूर्ण_FLAGS_MINखाताSIZE) &&
	    XFS_ISIZE(ip) < eofb->eof_min_file_size)
		वापस false;

	वापस true;
पूर्ण

/*
 * This is a fast pass over the inode cache to try to get reclaim moving on as
 * many inodes as possible in a लघु period of समय. It kicks itself every few
 * seconds, as well as being kicked by the inode cache shrinker when memory
 * goes low.
 */
व्योम
xfs_reclaim_worker(
	काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xfs_mount *mp = container_of(to_delayed_work(work),
					काष्ठा xfs_mount, m_reclaim_work);
	पूर्णांक		nr_to_scan = पूर्णांक_उच्च;

	xfs_reclaim_inodes_ag(mp, &nr_to_scan);
	xfs_reclaim_work_queue(mp);
पूर्ण

STATIC पूर्णांक
xfs_inode_मुक्त_eofblocks(
	काष्ठा xfs_inode	*ip,
	व्योम			*args,
	अचिन्हित पूर्णांक		*lockflags)
अणु
	काष्ठा xfs_eofblocks	*eofb = args;
	bool			रुको;

	रुको = eofb && (eofb->eof_flags & XFS_खातापूर्ण_FLAGS_SYNC);

	अगर (!xfs_अगरlags_test(ip, XFS_Iखातापूर्णBLOCKS))
		वापस 0;

	/*
	 * If the mapping is dirty the operation can block and रुको क्रम some
	 * समय. Unless we are रुकोing, skip it.
	 */
	अगर (!रुको && mapping_tagged(VFS_I(ip)->i_mapping, PAGECACHE_TAG_सूचीTY))
		वापस 0;

	अगर (!xfs_inode_matches_eofb(ip, eofb))
		वापस 0;

	/*
	 * If the caller is रुकोing, वापस -EAGAIN to keep the background
	 * scanner moving and revisit the inode in a subsequent pass.
	 */
	अगर (!xfs_ilock_noरुको(ip, XFS_IOLOCK_EXCL)) अणु
		अगर (रुको)
			वापस -EAGAIN;
		वापस 0;
	पूर्ण
	*lockflags |= XFS_IOLOCK_EXCL;

	अगर (xfs_can_मुक्त_eofblocks(ip, false))
		वापस xfs_मुक्त_eofblocks(ip);

	/* inode could be pपुनः_स्मृतिated or append-only */
	trace_xfs_inode_मुक्त_eofblocks_invalid(ip);
	xfs_inode_clear_eofblocks_tag(ip);
	वापस 0;
पूर्ण

/*
 * Background scanning to trim pपुनः_स्मृतिated space. This is queued based on the
 * 'speculative_prealloc_lifetime' tunable (5m by शेष).
 */
अटल अंतरभूत व्योम
xfs_blockgc_queue(
	काष्ठा xfs_perag	*pag)
अणु
	rcu_पढ़ो_lock();
	अगर (radix_tree_tagged(&pag->pag_ici_root, XFS_ICI_BLOCKGC_TAG))
		queue_delayed_work(pag->pag_mount->m_gc_workqueue,
				   &pag->pag_blockgc_work,
				   msecs_to_jअगरfies(xfs_blockgc_secs * 1000));
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
xfs_blockgc_set_अगरlag(
	काष्ठा xfs_inode	*ip,
	अचिन्हित दीर्घ		अगरlag)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_perag	*pag;
	पूर्णांक			tagged;

	ASSERT((अगरlag & ~(XFS_Iखातापूर्णBLOCKS | XFS_ICOWBLOCKS)) == 0);

	/*
	 * Don't bother locking the AG and looking up in the radix trees
	 * अगर we alपढ़ोy know that we have the tag set.
	 */
	अगर (ip->i_flags & अगरlag)
		वापस;
	spin_lock(&ip->i_flags_lock);
	ip->i_flags |= अगरlag;
	spin_unlock(&ip->i_flags_lock);

	pag = xfs_perag_get(mp, XFS_INO_TO_AGNO(mp, ip->i_ino));
	spin_lock(&pag->pag_ici_lock);

	tagged = radix_tree_tagged(&pag->pag_ici_root, XFS_ICI_BLOCKGC_TAG);
	radix_tree_tag_set(&pag->pag_ici_root,
			   XFS_INO_TO_AGINO(ip->i_mount, ip->i_ino),
			   XFS_ICI_BLOCKGC_TAG);
	अगर (!tagged) अणु
		/* propagate the blockgc tag up पूर्णांकo the perag radix tree */
		spin_lock(&ip->i_mount->m_perag_lock);
		radix_tree_tag_set(&ip->i_mount->m_perag_tree,
				   XFS_INO_TO_AGNO(ip->i_mount, ip->i_ino),
				   XFS_ICI_BLOCKGC_TAG);
		spin_unlock(&ip->i_mount->m_perag_lock);

		/* kick off background trimming */
		xfs_blockgc_queue(pag);

		trace_xfs_perag_set_blockgc(ip->i_mount, pag->pag_agno, -1,
				_RET_IP_);
	पूर्ण

	spin_unlock(&pag->pag_ici_lock);
	xfs_perag_put(pag);
पूर्ण

व्योम
xfs_inode_set_eofblocks_tag(
	xfs_inode_t	*ip)
अणु
	trace_xfs_inode_set_eofblocks_tag(ip);
	वापस xfs_blockgc_set_अगरlag(ip, XFS_Iखातापूर्णBLOCKS);
पूर्ण

अटल व्योम
xfs_blockgc_clear_अगरlag(
	काष्ठा xfs_inode	*ip,
	अचिन्हित दीर्घ		अगरlag)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_perag	*pag;
	bool			clear_tag;

	ASSERT((अगरlag & ~(XFS_Iखातापूर्णBLOCKS | XFS_ICOWBLOCKS)) == 0);

	spin_lock(&ip->i_flags_lock);
	ip->i_flags &= ~अगरlag;
	clear_tag = (ip->i_flags & (XFS_Iखातापूर्णBLOCKS | XFS_ICOWBLOCKS)) == 0;
	spin_unlock(&ip->i_flags_lock);

	अगर (!clear_tag)
		वापस;

	pag = xfs_perag_get(mp, XFS_INO_TO_AGNO(mp, ip->i_ino));
	spin_lock(&pag->pag_ici_lock);

	radix_tree_tag_clear(&pag->pag_ici_root,
			     XFS_INO_TO_AGINO(ip->i_mount, ip->i_ino),
			     XFS_ICI_BLOCKGC_TAG);
	अगर (!radix_tree_tagged(&pag->pag_ici_root, XFS_ICI_BLOCKGC_TAG)) अणु
		/* clear the blockgc tag from the perag radix tree */
		spin_lock(&ip->i_mount->m_perag_lock);
		radix_tree_tag_clear(&ip->i_mount->m_perag_tree,
				     XFS_INO_TO_AGNO(ip->i_mount, ip->i_ino),
				     XFS_ICI_BLOCKGC_TAG);
		spin_unlock(&ip->i_mount->m_perag_lock);
		trace_xfs_perag_clear_blockgc(ip->i_mount, pag->pag_agno, -1,
				_RET_IP_);
	पूर्ण

	spin_unlock(&pag->pag_ici_lock);
	xfs_perag_put(pag);
पूर्ण

व्योम
xfs_inode_clear_eofblocks_tag(
	xfs_inode_t	*ip)
अणु
	trace_xfs_inode_clear_eofblocks_tag(ip);
	वापस xfs_blockgc_clear_अगरlag(ip, XFS_Iखातापूर्णBLOCKS);
पूर्ण

/*
 * Set ourselves up to मुक्त CoW blocks from this file.  If it's alपढ़ोy clean
 * then we can bail out quickly, but otherwise we must back off अगर the file
 * is undergoing some kind of ग_लिखो.
 */
अटल bool
xfs_prep_मुक्त_cowblocks(
	काष्ठा xfs_inode	*ip)
अणु
	/*
	 * Just clear the tag अगर we have an empty cow विभाजन or none at all. It's
	 * possible the inode was fully unshared since it was originally tagged.
	 */
	अगर (!xfs_inode_has_cow_data(ip)) अणु
		trace_xfs_inode_मुक्त_cowblocks_invalid(ip);
		xfs_inode_clear_cowblocks_tag(ip);
		वापस false;
	पूर्ण

	/*
	 * If the mapping is dirty or under ग_लिखोback we cannot touch the
	 * CoW विभाजन.  Leave it alone अगर we're in the midst of a directio.
	 */
	अगर ((VFS_I(ip)->i_state & I_सूचीTY_PAGES) ||
	    mapping_tagged(VFS_I(ip)->i_mapping, PAGECACHE_TAG_सूचीTY) ||
	    mapping_tagged(VFS_I(ip)->i_mapping, PAGECACHE_TAG_WRITEBACK) ||
	    atomic_पढ़ो(&VFS_I(ip)->i_dio_count))
		वापस false;

	वापस true;
पूर्ण

/*
 * Automatic CoW Reservation Freeing
 *
 * These functions स्वतःmatically garbage collect leftover CoW reservations
 * that were made on behalf of a cowextsize hपूर्णांक when we start to run out
 * of quota or when the reservations sit around क्रम too दीर्घ.  If the file
 * has dirty pages or is undergoing ग_लिखोback, its CoW reservations will
 * be retained.
 *
 * The actual garbage collection piggybacks off the same code that runs
 * the speculative खातापूर्ण pपुनः_स्मृतिation garbage collector.
 */
STATIC पूर्णांक
xfs_inode_मुक्त_cowblocks(
	काष्ठा xfs_inode	*ip,
	व्योम			*args,
	अचिन्हित पूर्णांक		*lockflags)
अणु
	काष्ठा xfs_eofblocks	*eofb = args;
	bool			रुको;
	पूर्णांक			ret = 0;

	रुको = eofb && (eofb->eof_flags & XFS_खातापूर्ण_FLAGS_SYNC);

	अगर (!xfs_अगरlags_test(ip, XFS_ICOWBLOCKS))
		वापस 0;

	अगर (!xfs_prep_मुक्त_cowblocks(ip))
		वापस 0;

	अगर (!xfs_inode_matches_eofb(ip, eofb))
		वापस 0;

	/*
	 * If the caller is रुकोing, वापस -EAGAIN to keep the background
	 * scanner moving and revisit the inode in a subsequent pass.
	 */
	अगर (!(*lockflags & XFS_IOLOCK_EXCL) &&
	    !xfs_ilock_noरुको(ip, XFS_IOLOCK_EXCL)) अणु
		अगर (रुको)
			वापस -EAGAIN;
		वापस 0;
	पूर्ण
	*lockflags |= XFS_IOLOCK_EXCL;

	अगर (!xfs_ilock_noरुको(ip, XFS_MMAPLOCK_EXCL)) अणु
		अगर (रुको)
			वापस -EAGAIN;
		वापस 0;
	पूर्ण
	*lockflags |= XFS_MMAPLOCK_EXCL;

	/*
	 * Check again, nobody अन्यथा should be able to dirty blocks or change
	 * the reflink अगरlag now that we have the first two locks held.
	 */
	अगर (xfs_prep_मुक्त_cowblocks(ip))
		ret = xfs_reflink_cancel_cow_range(ip, 0, शून्यखाताOFF, false);
	वापस ret;
पूर्ण

व्योम
xfs_inode_set_cowblocks_tag(
	xfs_inode_t	*ip)
अणु
	trace_xfs_inode_set_cowblocks_tag(ip);
	वापस xfs_blockgc_set_अगरlag(ip, XFS_ICOWBLOCKS);
पूर्ण

व्योम
xfs_inode_clear_cowblocks_tag(
	xfs_inode_t	*ip)
अणु
	trace_xfs_inode_clear_cowblocks_tag(ip);
	वापस xfs_blockgc_clear_अगरlag(ip, XFS_ICOWBLOCKS);
पूर्ण

#घोषणा क्रम_each_perag_tag(mp, next_agno, pag, tag) \
	क्रम ((next_agno) = 0, (pag) = xfs_perag_get_tag((mp), 0, (tag)); \
		(pag) != शून्य; \
		(next_agno) = (pag)->pag_agno + 1, \
		xfs_perag_put(pag), \
		(pag) = xfs_perag_get_tag((mp), (next_agno), (tag)))


/* Disable post-खातापूर्ण and CoW block स्वतः-reclamation. */
व्योम
xfs_blockgc_stop(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_perag	*pag;
	xfs_agnumber_t		agno;

	क्रम_each_perag_tag(mp, agno, pag, XFS_ICI_BLOCKGC_TAG)
		cancel_delayed_work_sync(&pag->pag_blockgc_work);
पूर्ण

/* Enable post-खातापूर्ण and CoW block स्वतः-reclamation. */
व्योम
xfs_blockgc_start(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_perag	*pag;
	xfs_agnumber_t		agno;

	क्रम_each_perag_tag(mp, agno, pag, XFS_ICI_BLOCKGC_TAG)
		xfs_blockgc_queue(pag);
पूर्ण

/* Scan one incore inode क्रम block pपुनः_स्मृतिations that we can हटाओ. */
अटल पूर्णांक
xfs_blockgc_scan_inode(
	काष्ठा xfs_inode	*ip,
	व्योम			*args)
अणु
	अचिन्हित पूर्णांक		lockflags = 0;
	पूर्णांक			error;

	error = xfs_inode_मुक्त_eofblocks(ip, args, &lockflags);
	अगर (error)
		जाओ unlock;

	error = xfs_inode_मुक्त_cowblocks(ip, args, &lockflags);
unlock:
	अगर (lockflags)
		xfs_iunlock(ip, lockflags);
	वापस error;
पूर्ण

/* Background worker that trims pपुनः_स्मृतिated space. */
व्योम
xfs_blockgc_worker(
	काष्ठा work_काष्ठा	*work)
अणु
	काष्ठा xfs_perag	*pag = container_of(to_delayed_work(work),
					काष्ठा xfs_perag, pag_blockgc_work);
	काष्ठा xfs_mount	*mp = pag->pag_mount;
	पूर्णांक			error;

	अगर (!sb_start_ग_लिखो_trylock(mp->m_super))
		वापस;
	error = xfs_inode_walk_ag(pag, 0, xfs_blockgc_scan_inode, शून्य,
			XFS_ICI_BLOCKGC_TAG);
	अगर (error)
		xfs_info(mp, "AG %u preallocation gc worker failed, err=%d",
				pag->pag_agno, error);
	sb_end_ग_लिखो(mp->m_super);
	xfs_blockgc_queue(pag);
पूर्ण

/*
 * Try to मुक्त space in the fileप्रणाली by purging eofblocks and cowblocks.
 */
पूर्णांक
xfs_blockgc_मुक्त_space(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_eofblocks	*eofb)
अणु
	trace_xfs_blockgc_मुक्त_space(mp, eofb, _RET_IP_);

	वापस xfs_inode_walk(mp, 0, xfs_blockgc_scan_inode, eofb,
			XFS_ICI_BLOCKGC_TAG);
पूर्ण

/*
 * Run cow/eofblocks scans on the supplied dquots.  We करोn't know exactly which
 * quota caused an allocation failure, so we make a best efक्रमt by including
 * each quota under low मुक्त space conditions (less than 1% मुक्त space) in the
 * scan.
 *
 * Callers must not hold any inode's ILOCK.  If requesting a synchronous scan
 * (XFS_खातापूर्ण_FLAGS_SYNC), the caller also must not hold any inode's IOLOCK or
 * MMAPLOCK.
 */
पूर्णांक
xfs_blockgc_मुक्त_dquots(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dquot	*udqp,
	काष्ठा xfs_dquot	*gdqp,
	काष्ठा xfs_dquot	*pdqp,
	अचिन्हित पूर्णांक		eof_flags)
अणु
	काष्ठा xfs_eofblocks	eofb = अणु0पूर्ण;
	bool			करो_work = false;

	अगर (!udqp && !gdqp && !pdqp)
		वापस 0;

	/*
	 * Run a scan to मुक्त blocks using the जोड़ filter to cover all
	 * applicable quotas in a single scan.
	 */
	eofb.eof_flags = XFS_खातापूर्ण_FLAGS_UNION | eof_flags;

	अगर (XFS_IS_UQUOTA_ENFORCED(mp) && udqp && xfs_dquot_lowsp(udqp)) अणु
		eofb.eof_uid = make_kuid(mp->m_super->s_user_ns, udqp->q_id);
		eofb.eof_flags |= XFS_खातापूर्ण_FLAGS_UID;
		करो_work = true;
	पूर्ण

	अगर (XFS_IS_UQUOTA_ENFORCED(mp) && gdqp && xfs_dquot_lowsp(gdqp)) अणु
		eofb.eof_gid = make_kgid(mp->m_super->s_user_ns, gdqp->q_id);
		eofb.eof_flags |= XFS_खातापूर्ण_FLAGS_GID;
		करो_work = true;
	पूर्ण

	अगर (XFS_IS_PQUOTA_ENFORCED(mp) && pdqp && xfs_dquot_lowsp(pdqp)) अणु
		eofb.eof_prid = pdqp->q_id;
		eofb.eof_flags |= XFS_खातापूर्ण_FLAGS_PRID;
		करो_work = true;
	पूर्ण

	अगर (!करो_work)
		वापस 0;

	वापस xfs_blockgc_मुक्त_space(mp, &eofb);
पूर्ण

/* Run cow/eofblocks scans on the quotas attached to the inode. */
पूर्णांक
xfs_blockgc_मुक्त_quota(
	काष्ठा xfs_inode	*ip,
	अचिन्हित पूर्णांक		eof_flags)
अणु
	वापस xfs_blockgc_मुक्त_dquots(ip->i_mount,
			xfs_inode_dquot(ip, XFS_DQTYPE_USER),
			xfs_inode_dquot(ip, XFS_DQTYPE_GROUP),
			xfs_inode_dquot(ip, XFS_DQTYPE_PROJ), eof_flags);
पूर्ण
