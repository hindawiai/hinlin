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
#समावेश "xfs_bit.h"
#समावेश "xfs_sb.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_rtalloc.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_log.h"
#समावेश "xfs_error.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_fsops.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_sysfs.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "xfs_reflink.h"
#समावेश "xfs_extent_busy.h"
#समावेश "xfs_health.h"
#समावेश "xfs_trace.h"

अटल DEFINE_MUTEX(xfs_uuid_table_mutex);
अटल पूर्णांक xfs_uuid_table_size;
अटल uuid_t *xfs_uuid_table;

व्योम
xfs_uuid_table_मुक्त(व्योम)
अणु
	अगर (xfs_uuid_table_size == 0)
		वापस;
	kmem_मुक्त(xfs_uuid_table);
	xfs_uuid_table = शून्य;
	xfs_uuid_table_size = 0;
पूर्ण

/*
 * See अगर the UUID is unique among mounted XFS fileप्रणालीs.
 * Mount fails अगर UUID is nil or a FS with the same UUID is alपढ़ोy mounted.
 */
STATIC पूर्णांक
xfs_uuid_mount(
	काष्ठा xfs_mount	*mp)
अणु
	uuid_t			*uuid = &mp->m_sb.sb_uuid;
	पूर्णांक			hole, i;

	/* Publish UUID in काष्ठा super_block */
	uuid_copy(&mp->m_super->s_uuid, uuid);

	अगर (mp->m_flags & XFS_MOUNT_NOUUID)
		वापस 0;

	अगर (uuid_is_null(uuid)) अणु
		xfs_warn(mp, "Filesystem has null UUID - can't mount");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&xfs_uuid_table_mutex);
	क्रम (i = 0, hole = -1; i < xfs_uuid_table_size; i++) अणु
		अगर (uuid_is_null(&xfs_uuid_table[i])) अणु
			hole = i;
			जारी;
		पूर्ण
		अगर (uuid_equal(uuid, &xfs_uuid_table[i]))
			जाओ out_duplicate;
	पूर्ण

	अगर (hole < 0) अणु
		xfs_uuid_table = kपुनः_स्मृति(xfs_uuid_table,
			(xfs_uuid_table_size + 1) * माप(*xfs_uuid_table),
			GFP_KERNEL | __GFP_NOFAIL);
		hole = xfs_uuid_table_size++;
	पूर्ण
	xfs_uuid_table[hole] = *uuid;
	mutex_unlock(&xfs_uuid_table_mutex);

	वापस 0;

 out_duplicate:
	mutex_unlock(&xfs_uuid_table_mutex);
	xfs_warn(mp, "Filesystem has duplicate UUID %pU - can't mount", uuid);
	वापस -EINVAL;
पूर्ण

STATIC व्योम
xfs_uuid_unmount(
	काष्ठा xfs_mount	*mp)
अणु
	uuid_t			*uuid = &mp->m_sb.sb_uuid;
	पूर्णांक			i;

	अगर (mp->m_flags & XFS_MOUNT_NOUUID)
		वापस;

	mutex_lock(&xfs_uuid_table_mutex);
	क्रम (i = 0; i < xfs_uuid_table_size; i++) अणु
		अगर (uuid_is_null(&xfs_uuid_table[i]))
			जारी;
		अगर (!uuid_equal(uuid, &xfs_uuid_table[i]))
			जारी;
		स_रखो(&xfs_uuid_table[i], 0, माप(uuid_t));
		अवरोध;
	पूर्ण
	ASSERT(i < xfs_uuid_table_size);
	mutex_unlock(&xfs_uuid_table_mutex);
पूर्ण


STATIC व्योम
__xfs_मुक्त_perag(
	काष्ठा rcu_head	*head)
अणु
	काष्ठा xfs_perag *pag = container_of(head, काष्ठा xfs_perag, rcu_head);

	ASSERT(!delayed_work_pending(&pag->pag_blockgc_work));
	ASSERT(atomic_पढ़ो(&pag->pag_ref) == 0);
	kmem_मुक्त(pag);
पूर्ण

/*
 * Free up the per-ag resources associated with the mount काष्ठाure.
 */
STATIC व्योम
xfs_मुक्त_perag(
	xfs_mount_t	*mp)
अणु
	xfs_agnumber_t	agno;
	काष्ठा xfs_perag *pag;

	क्रम (agno = 0; agno < mp->m_sb.sb_agcount; agno++) अणु
		spin_lock(&mp->m_perag_lock);
		pag = radix_tree_delete(&mp->m_perag_tree, agno);
		spin_unlock(&mp->m_perag_lock);
		ASSERT(pag);
		ASSERT(atomic_पढ़ो(&pag->pag_ref) == 0);
		cancel_delayed_work_sync(&pag->pag_blockgc_work);
		xfs_iunlink_destroy(pag);
		xfs_buf_hash_destroy(pag);
		call_rcu(&pag->rcu_head, __xfs_मुक्त_perag);
	पूर्ण
पूर्ण

/*
 * Check size of device based on the (data/realसमय) block count.
 * Note: this check is used by the growfs code as well as mount.
 */
पूर्णांक
xfs_sb_validate_fsb_count(
	xfs_sb_t	*sbp,
	uपूर्णांक64_t	nblocks)
अणु
	ASSERT(PAGE_SHIFT >= sbp->sb_blocklog);
	ASSERT(sbp->sb_blocklog >= BBSHIFT);

	/* Limited by अच_दीर्घ_उच्च of page cache index */
	अगर (nblocks >> (PAGE_SHIFT - sbp->sb_blocklog) > अच_दीर्घ_उच्च)
		वापस -EFBIG;
	वापस 0;
पूर्ण

पूर्णांक
xfs_initialize_perag(
	xfs_mount_t	*mp,
	xfs_agnumber_t	agcount,
	xfs_agnumber_t	*maxagi)
अणु
	xfs_agnumber_t	index;
	xfs_agnumber_t	first_initialised = शून्यAGNUMBER;
	xfs_perag_t	*pag;
	पूर्णांक		error = -ENOMEM;

	/*
	 * Walk the current per-ag tree so we करोn't try to initialise AGs
	 * that alपढ़ोy exist (growfs हाल). Allocate and insert all the
	 * AGs we करोn't find पढ़ोy क्रम initialisation.
	 */
	क्रम (index = 0; index < agcount; index++) अणु
		pag = xfs_perag_get(mp, index);
		अगर (pag) अणु
			xfs_perag_put(pag);
			जारी;
		पूर्ण

		pag = kmem_zalloc(माप(*pag), KM_MAYFAIL);
		अगर (!pag) अणु
			error = -ENOMEM;
			जाओ out_unwind_new_pags;
		पूर्ण
		pag->pag_agno = index;
		pag->pag_mount = mp;
		spin_lock_init(&pag->pag_ici_lock);
		INIT_DELAYED_WORK(&pag->pag_blockgc_work, xfs_blockgc_worker);
		INIT_RADIX_TREE(&pag->pag_ici_root, GFP_ATOMIC);

		error = xfs_buf_hash_init(pag);
		अगर (error)
			जाओ out_मुक्त_pag;
		init_रुकोqueue_head(&pag->pagb_रुको);
		spin_lock_init(&pag->pagb_lock);
		pag->pagb_count = 0;
		pag->pagb_tree = RB_ROOT;

		error = radix_tree_preload(GFP_NOFS);
		अगर (error)
			जाओ out_hash_destroy;

		spin_lock(&mp->m_perag_lock);
		अगर (radix_tree_insert(&mp->m_perag_tree, index, pag)) अणु
			WARN_ON_ONCE(1);
			spin_unlock(&mp->m_perag_lock);
			radix_tree_preload_end();
			error = -EEXIST;
			जाओ out_hash_destroy;
		पूर्ण
		spin_unlock(&mp->m_perag_lock);
		radix_tree_preload_end();
		/* first new pag is fully initialized */
		अगर (first_initialised == शून्यAGNUMBER)
			first_initialised = index;
		error = xfs_iunlink_init(pag);
		अगर (error)
			जाओ out_hash_destroy;
		spin_lock_init(&pag->pag_state_lock);
	पूर्ण

	index = xfs_set_inode_alloc(mp, agcount);

	अगर (maxagi)
		*maxagi = index;

	mp->m_ag_pपुनः_स्मृति_blocks = xfs_pपुनः_स्मृति_blocks(mp);
	वापस 0;

out_hash_destroy:
	xfs_buf_hash_destroy(pag);
out_मुक्त_pag:
	kmem_मुक्त(pag);
out_unwind_new_pags:
	/* unwind any prior newly initialized pags */
	क्रम (index = first_initialised; index < agcount; index++) अणु
		pag = radix_tree_delete(&mp->m_perag_tree, index);
		अगर (!pag)
			अवरोध;
		xfs_buf_hash_destroy(pag);
		xfs_iunlink_destroy(pag);
		kmem_मुक्त(pag);
	पूर्ण
	वापस error;
पूर्ण

/*
 * xfs_पढ़ोsb
 *
 * Does the initial पढ़ो of the superblock.
 */
पूर्णांक
xfs_पढ़ोsb(
	काष्ठा xfs_mount *mp,
	पूर्णांक		flags)
अणु
	अचिन्हित पूर्णांक	sector_size;
	काष्ठा xfs_buf	*bp;
	काष्ठा xfs_sb	*sbp = &mp->m_sb;
	पूर्णांक		error;
	पूर्णांक		loud = !(flags & XFS_MFSI_QUIET);
	स्थिर काष्ठा xfs_buf_ops *buf_ops;

	ASSERT(mp->m_sb_bp == शून्य);
	ASSERT(mp->m_ddev_targp != शून्य);

	/*
	 * For the initial पढ़ो, we must guess at the sector
	 * size based on the block device.  It's enough to
	 * get the sb_sectsize out of the superblock and
	 * then reपढ़ो with the proper length.
	 * We करोn't verअगरy it yet, because it may not be complete.
	 */
	sector_size = xfs_माला_लोize_buftarg(mp->m_ddev_targp);
	buf_ops = शून्य;

	/*
	 * Allocate a (locked) buffer to hold the superblock. This will be kept
	 * around at all बार to optimize access to the superblock. Thereक्रमe,
	 * set XBF_NO_IOACCT to make sure it करोesn't hold the buftarg count
	 * elevated.
	 */
reपढ़ो:
	error = xfs_buf_पढ़ो_uncached(mp->m_ddev_targp, XFS_SB_DADDR,
				      BTOBB(sector_size), XBF_NO_IOACCT, &bp,
				      buf_ops);
	अगर (error) अणु
		अगर (loud)
			xfs_warn(mp, "SB validate failed with error %d.", error);
		/* bad CRC means corrupted metadata */
		अगर (error == -EFSBADCRC)
			error = -EFSCORRUPTED;
		वापस error;
	पूर्ण

	/*
	 * Initialize the mount काष्ठाure from the superblock.
	 */
	xfs_sb_from_disk(sbp, bp->b_addr);

	/*
	 * If we haven't validated the superblock, करो so now beक्रमe we try
	 * to check the sector size and reपढ़ो the superblock appropriately.
	 */
	अगर (sbp->sb_magicnum != XFS_SB_MAGIC) अणु
		अगर (loud)
			xfs_warn(mp, "Invalid superblock magic number");
		error = -EINVAL;
		जाओ release_buf;
	पूर्ण

	/*
	 * We must be able to करो sector-sized and sector-aligned IO.
	 */
	अगर (sector_size > sbp->sb_sectsize) अणु
		अगर (loud)
			xfs_warn(mp, "device supports %u byte sectors (not %u)",
				sector_size, sbp->sb_sectsize);
		error = -ENOSYS;
		जाओ release_buf;
	पूर्ण

	अगर (buf_ops == शून्य) अणु
		/*
		 * Re-पढ़ो the superblock so the buffer is correctly sized,
		 * and properly verअगरied.
		 */
		xfs_buf_rअन्यथा(bp);
		sector_size = sbp->sb_sectsize;
		buf_ops = loud ? &xfs_sb_buf_ops : &xfs_sb_quiet_buf_ops;
		जाओ reपढ़ो;
	पूर्ण

	xfs_reinit_percpu_counters(mp);

	/* no need to be quiet anymore, so reset the buf ops */
	bp->b_ops = &xfs_sb_buf_ops;

	mp->m_sb_bp = bp;
	xfs_buf_unlock(bp);
	वापस 0;

release_buf:
	xfs_buf_rअन्यथा(bp);
	वापस error;
पूर्ण

/*
 * If the sunit/swidth change would move the precomputed root inode value, we
 * must reject the ondisk change because repair will stumble over that.
 * However, we allow the mount to proceed because we never rejected this
 * combination beक्रमe.  Returns true to update the sb, false otherwise.
 */
अटल अंतरभूत पूर्णांक
xfs_check_new_dalign(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			new_dalign,
	bool			*update_sb)
अणु
	काष्ठा xfs_sb		*sbp = &mp->m_sb;
	xfs_ino_t		calc_ino;

	calc_ino = xfs_ialloc_calc_rootino(mp, new_dalign);
	trace_xfs_check_new_dalign(mp, new_dalign, calc_ino);

	अगर (sbp->sb_rootino == calc_ino) अणु
		*update_sb = true;
		वापस 0;
	पूर्ण

	xfs_warn(mp,
"Cannot change stripe alignment; would require moving root inode.");

	/*
	 * XXX: Next समय we add a new incompat feature, this should start
	 * वापसing -EINVAL to fail the mount.  Until then, spit out a warning
	 * that we're ignoring the administrator's inकाष्ठाions.
	 */
	xfs_warn(mp, "Skipping superblock stripe alignment update.");
	*update_sb = false;
	वापस 0;
पूर्ण

/*
 * If we were provided with new sunit/swidth values as mount options, make sure
 * that they pass basic alignment and superblock feature checks, and convert
 * them पूर्णांकo the same units (FSB) that everything अन्यथा expects.  This step
 * /must/ be करोne beक्रमe computing the inode geometry.
 */
STATIC पूर्णांक
xfs_validate_new_dalign(
	काष्ठा xfs_mount	*mp)
अणु
	अगर (mp->m_dalign == 0)
		वापस 0;

	/*
	 * If stripe unit and stripe width are not multiples
	 * of the fs blocksize turn off alignment.
	 */
	अगर ((BBTOB(mp->m_dalign) & mp->m_blockmask) ||
	    (BBTOB(mp->m_swidth) & mp->m_blockmask)) अणु
		xfs_warn(mp,
	"alignment check failed: sunit/swidth vs. blocksize(%d)",
			mp->m_sb.sb_blocksize);
		वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/*
		 * Convert the stripe unit and width to FSBs.
		 */
		mp->m_dalign = XFS_BB_TO_FSBT(mp, mp->m_dalign);
		अगर (mp->m_dalign && (mp->m_sb.sb_agblocks % mp->m_dalign)) अणु
			xfs_warn(mp,
		"alignment check failed: sunit/swidth vs. agsize(%d)",
				 mp->m_sb.sb_agblocks);
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (mp->m_dalign) अणु
			mp->m_swidth = XFS_BB_TO_FSBT(mp, mp->m_swidth);
		पूर्ण अन्यथा अणु
			xfs_warn(mp,
		"alignment check failed: sunit(%d) less than bsize(%d)",
				 mp->m_dalign, mp->m_sb.sb_blocksize);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!xfs_sb_version_hasdalign(&mp->m_sb)) अणु
		xfs_warn(mp,
"cannot change alignment: superblock does not support data alignment");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Update alignment values based on mount options and sb values. */
STATIC पूर्णांक
xfs_update_alignment(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_sb		*sbp = &mp->m_sb;

	अगर (mp->m_dalign) अणु
		bool		update_sb;
		पूर्णांक		error;

		अगर (sbp->sb_unit == mp->m_dalign &&
		    sbp->sb_width == mp->m_swidth)
			वापस 0;

		error = xfs_check_new_dalign(mp, mp->m_dalign, &update_sb);
		अगर (error || !update_sb)
			वापस error;

		sbp->sb_unit = mp->m_dalign;
		sbp->sb_width = mp->m_swidth;
		mp->m_update_sb = true;
	पूर्ण अन्यथा अगर ((mp->m_flags & XFS_MOUNT_NOALIGN) != XFS_MOUNT_NOALIGN &&
		    xfs_sb_version_hasdalign(&mp->m_sb)) अणु
		mp->m_dalign = sbp->sb_unit;
		mp->m_swidth = sbp->sb_width;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * precalculate the low space thresholds क्रम dynamic speculative pपुनः_स्मृतिation.
 */
व्योम
xfs_set_low_space_thresholds(
	काष्ठा xfs_mount	*mp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < XFS_LOWSP_MAX; i++) अणु
		uपूर्णांक64_t space = mp->m_sb.sb_dblocks;

		करो_भाग(space, 100);
		mp->m_low_space[i] = space * (i + 1);
	पूर्ण
पूर्ण

/*
 * Check that the data (and log अगर separate) is an ok size.
 */
STATIC पूर्णांक
xfs_check_sizes(
	काष्ठा xfs_mount *mp)
अणु
	काष्ठा xfs_buf	*bp;
	xfs_daddr_t	d;
	पूर्णांक		error;

	d = (xfs_daddr_t)XFS_FSB_TO_BB(mp, mp->m_sb.sb_dblocks);
	अगर (XFS_BB_TO_FSB(mp, d) != mp->m_sb.sb_dblocks) अणु
		xfs_warn(mp, "filesystem size mismatch detected");
		वापस -EFBIG;
	पूर्ण
	error = xfs_buf_पढ़ो_uncached(mp->m_ddev_targp,
					d - XFS_FSS_TO_BB(mp, 1),
					XFS_FSS_TO_BB(mp, 1), 0, &bp, शून्य);
	अगर (error) अणु
		xfs_warn(mp, "last sector read failed");
		वापस error;
	पूर्ण
	xfs_buf_rअन्यथा(bp);

	अगर (mp->m_logdev_targp == mp->m_ddev_targp)
		वापस 0;

	d = (xfs_daddr_t)XFS_FSB_TO_BB(mp, mp->m_sb.sb_logblocks);
	अगर (XFS_BB_TO_FSB(mp, d) != mp->m_sb.sb_logblocks) अणु
		xfs_warn(mp, "log size mismatch detected");
		वापस -EFBIG;
	पूर्ण
	error = xfs_buf_पढ़ो_uncached(mp->m_logdev_targp,
					d - XFS_FSB_TO_BB(mp, 1),
					XFS_FSB_TO_BB(mp, 1), 0, &bp, शून्य);
	अगर (error) अणु
		xfs_warn(mp, "log device read failed");
		वापस error;
	पूर्ण
	xfs_buf_rअन्यथा(bp);
	वापस 0;
पूर्ण

/*
 * Clear the quotaflags in memory and in the superblock.
 */
पूर्णांक
xfs_mount_reset_sbqflags(
	काष्ठा xfs_mount	*mp)
अणु
	mp->m_qflags = 0;

	/* It is OK to look at sb_qflags in the mount path without m_sb_lock. */
	अगर (mp->m_sb.sb_qflags == 0)
		वापस 0;
	spin_lock(&mp->m_sb_lock);
	mp->m_sb.sb_qflags = 0;
	spin_unlock(&mp->m_sb_lock);

	अगर (!xfs_fs_writable(mp, SB_FREEZE_WRITE))
		वापस 0;

	वापस xfs_sync_sb(mp, false);
पूर्ण

uपूर्णांक64_t
xfs_शेष_resblks(xfs_mount_t *mp)
अणु
	uपूर्णांक64_t resblks;

	/*
	 * We शेष to 5% or 8192 fsbs of space reserved, whichever is
	 * smaller.  This is पूर्णांकended to cover concurrent allocation
	 * transactions when we initially hit enospc. These each require a 4
	 * block reservation. Hence by शेष we cover roughly 2000 concurrent
	 * allocation reservations.
	 */
	resblks = mp->m_sb.sb_dblocks;
	करो_भाग(resblks, 20);
	resblks = min_t(uपूर्णांक64_t, resblks, 8192);
	वापस resblks;
पूर्ण

/* Ensure the summary counts are correct. */
STATIC पूर्णांक
xfs_check_summary_counts(
	काष्ठा xfs_mount	*mp)
अणु
	/*
	 * The AG0 superblock verअगरier rejects in-progress fileप्रणालीs,
	 * so we should never see the flag set this far पूर्णांकo mounting.
	 */
	अगर (mp->m_sb.sb_inprogress) अणु
		xfs_err(mp, "sb_inprogress set after log recovery??");
		WARN_ON(1);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Now the log is mounted, we know अगर it was an unclean shutकरोwn or
	 * not. If it was, with the first phase of recovery has completed, we
	 * have consistent AG blocks on disk. We have not recovered EFIs yet,
	 * but they are recovered transactionally in the second recovery phase
	 * later.
	 *
	 * If the log was clean when we mounted, we can check the summary
	 * counters.  If any of them are obviously incorrect, we can recompute
	 * them from the AGF headers in the next step.
	 */
	अगर (XFS_LAST_UNMOUNT_WAS_CLEAN(mp) &&
	    (mp->m_sb.sb_fdblocks > mp->m_sb.sb_dblocks ||
	     !xfs_verअगरy_icount(mp, mp->m_sb.sb_icount) ||
	     mp->m_sb.sb_अगरree > mp->m_sb.sb_icount))
		xfs_fs_mark_sick(mp, XFS_SICK_FS_COUNTERS);

	/*
	 * We can safely re-initialise incore superblock counters from the
	 * per-ag data. These may not be correct अगर the fileप्रणाली was not
	 * cleanly unmounted, so we रुकोed क्रम recovery to finish beक्रमe करोing
	 * this.
	 *
	 * If the fileप्रणाली was cleanly unmounted or the previous check did
	 * not flag anything weird, then we can trust the values in the
	 * superblock to be correct and we करोn't need to करो anything here.
	 * Otherwise, recalculate the summary counters.
	 */
	अगर ((!xfs_sb_version_haslazysbcount(&mp->m_sb) ||
	     XFS_LAST_UNMOUNT_WAS_CLEAN(mp)) &&
	    !xfs_fs_has_sickness(mp, XFS_SICK_FS_COUNTERS))
		वापस 0;

	वापस xfs_initialize_perag_data(mp, mp->m_sb.sb_agcount);
पूर्ण

/*
 * Flush and reclaim dirty inodes in preparation क्रम unmount. Inodes and
 * पूर्णांकernal inode काष्ठाures can be sitting in the CIL and AIL at this poपूर्णांक,
 * so we need to unpin them, ग_लिखो them back and/or reclaim them beक्रमe unmount
 * can proceed.
 *
 * An inode cluster that has been मुक्तd can have its buffer still pinned in
 * memory because the transaction is still sitting in a iclog. The stale inodes
 * on that buffer will be pinned to the buffer until the transaction hits the
 * disk and the callbacks run. Pushing the AIL will skip the stale inodes and
 * may never see the pinned buffer, so nothing will push out the iclog and
 * unpin the buffer.
 *
 * Hence we need to क्रमce the log to unpin everything first. However, log
 * क्रमces करोn't रुको क्रम the discards they issue to complete, so we have to
 * explicitly रुको क्रम them to complete here as well.
 *
 * Then we can tell the world we are unmounting so that error handling knows
 * that the fileप्रणाली is going away and we should error out anything that we
 * have been retrying in the background.  This will prevent never-ending
 * retries in AIL pushing from hanging the unmount.
 *
 * Finally, we can push the AIL to clean all the reमुख्यing dirty objects, then
 * reclaim the reमुख्यing inodes that are still in memory at this poपूर्णांक in समय.
 */
अटल व्योम
xfs_unmount_flush_inodes(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_log_क्रमce(mp, XFS_LOG_SYNC);
	xfs_extent_busy_रुको_all(mp);
	flush_workqueue(xfs_discard_wq);

	mp->m_flags |= XFS_MOUNT_UNMOUNTING;

	xfs_ail_push_all_sync(mp->m_ail);
	cancel_delayed_work_sync(&mp->m_reclaim_work);
	xfs_reclaim_inodes(mp);
	xfs_health_unmount(mp);
पूर्ण

अटल व्योम
xfs_mount_setup_inode_geom(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_ino_geometry *igeo = M_IGEO(mp);

	igeo->attr_विभाजन_offset = xfs_bmap_compute_attr_offset(mp);
	ASSERT(igeo->attr_विभाजन_offset < XFS_LITINO(mp));

	xfs_ialloc_setup_geometry(mp);
पूर्ण

/*
 * This function करोes the following on an initial mount of a file प्रणाली:
 *	- पढ़ोs the superblock from disk and init the mount काष्ठा
 *	- अगर we're a 32-bit kernel, करो a size check on the superblock
 *		so we करोn't mount terabyte fileप्रणालीs
 *	- init mount काष्ठा realसमय fields
 *	- allocate inode hash table क्रम fs
 *	- init directory manager
 *	- perक्रमm recovery and init the log manager
 */
पूर्णांक
xfs_mountfs(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_sb		*sbp = &(mp->m_sb);
	काष्ठा xfs_inode	*rip;
	काष्ठा xfs_ino_geometry	*igeo = M_IGEO(mp);
	uपूर्णांक64_t		resblks;
	uपूर्णांक			quotamount = 0;
	uपूर्णांक			quotaflags = 0;
	पूर्णांक			error = 0;

	xfs_sb_mount_common(mp, sbp);

	/*
	 * Check क्रम a mismatched features2 values.  Older kernels पढ़ो & wrote
	 * पूर्णांकo the wrong sb offset क्रम sb_features2 on some platक्रमms due to
	 * xfs_sb_t not being 64bit size aligned when sb_features2 was added,
	 * which made older superblock पढ़ोing/writing routines swap it as a
	 * 64-bit value.
	 *
	 * For backwards compatibility, we make both slots equal.
	 *
	 * If we detect a mismatched field, we OR the set bits पूर्णांकo the existing
	 * features2 field in हाल it has alपढ़ोy been modअगरied; we करोn't want
	 * to lose any features.  We then update the bad location with the ORed
	 * value so that older kernels will see any features2 flags. The
	 * superblock ग_लिखोback code ensures the new sb_features2 is copied to
	 * sb_bad_features2 beक्रमe it is logged or written to disk.
	 */
	अगर (xfs_sb_has_mismatched_features2(sbp)) अणु
		xfs_warn(mp, "correcting sb_features alignment problem");
		sbp->sb_features2 |= sbp->sb_bad_features2;
		mp->m_update_sb = true;

		/*
		 * Re-check क्रम ATTR2 in हाल it was found in bad_features2
		 * slot.
		 */
		अगर (xfs_sb_version_hasattr2(&mp->m_sb) &&
		   !(mp->m_flags & XFS_MOUNT_NOATTR2))
			mp->m_flags |= XFS_MOUNT_ATTR2;
	पूर्ण

	अगर (xfs_sb_version_hasattr2(&mp->m_sb) &&
	   (mp->m_flags & XFS_MOUNT_NOATTR2)) अणु
		xfs_sb_version_हटाओattr2(&mp->m_sb);
		mp->m_update_sb = true;

		/* update sb_versionnum क्रम the clearing of the morebits */
		अगर (!sbp->sb_features2)
			mp->m_update_sb = true;
	पूर्ण

	/* always use v2 inodes by शेष now */
	अगर (!(mp->m_sb.sb_versionnum & XFS_SB_VERSION_NLINKBIT)) अणु
		mp->m_sb.sb_versionnum |= XFS_SB_VERSION_NLINKBIT;
		mp->m_update_sb = true;
	पूर्ण

	/*
	 * If we were given new sunit/swidth options, करो some basic validation
	 * checks and convert the incore dalign and swidth values to the
	 * same units (FSB) that everything अन्यथा uses.  This /must/ happen
	 * beक्रमe computing the inode geometry.
	 */
	error = xfs_validate_new_dalign(mp);
	अगर (error)
		जाओ out;

	xfs_alloc_compute_maxlevels(mp);
	xfs_bmap_compute_maxlevels(mp, XFS_DATA_FORK);
	xfs_bmap_compute_maxlevels(mp, XFS_ATTR_FORK);
	xfs_mount_setup_inode_geom(mp);
	xfs_rmapbt_compute_maxlevels(mp);
	xfs_refcountbt_compute_maxlevels(mp);

	/*
	 * Check अगर sb_agblocks is aligned at stripe boundary.  If sb_agblocks
	 * is NOT aligned turn off m_dalign since allocator alignment is within
	 * an ag, thereक्रमe ag has to be aligned at stripe boundary.  Note that
	 * we must compute the मुक्त space and rmap btree geometry beक्रमe करोing
	 * this.
	 */
	error = xfs_update_alignment(mp);
	अगर (error)
		जाओ out;

	/* enable fail_at_unmount as शेष */
	mp->m_fail_unmount = true;

	error = xfs_sysfs_init(&mp->m_kobj, &xfs_mp_ktype,
			       शून्य, mp->m_super->s_id);
	अगर (error)
		जाओ out;

	error = xfs_sysfs_init(&mp->m_stats.xs_kobj, &xfs_stats_ktype,
			       &mp->m_kobj, "stats");
	अगर (error)
		जाओ out_हटाओ_sysfs;

	error = xfs_error_sysfs_init(mp);
	अगर (error)
		जाओ out_del_stats;

	error = xfs_errortag_init(mp);
	अगर (error)
		जाओ out_हटाओ_error_sysfs;

	error = xfs_uuid_mount(mp);
	अगर (error)
		जाओ out_हटाओ_errortag;

	/*
	 * Update the preferred ग_लिखो size based on the inक्रमmation from the
	 * on-disk superblock.
	 */
	mp->m_allocsize_log =
		max_t(uपूर्णांक32_t, sbp->sb_blocklog, mp->m_allocsize_log);
	mp->m_allocsize_blocks = 1U << (mp->m_allocsize_log - sbp->sb_blocklog);

	/* set the low space thresholds क्रम dynamic pपुनः_स्मृतिation */
	xfs_set_low_space_thresholds(mp);

	/*
	 * If enabled, sparse inode chunk alignment is expected to match the
	 * cluster size. Full inode chunk alignment must match the chunk size,
	 * but that is checked on sb पढ़ो verअगरication...
	 */
	अगर (xfs_sb_version_hassparseinodes(&mp->m_sb) &&
	    mp->m_sb.sb_spino_align !=
			XFS_B_TO_FSBT(mp, igeo->inode_cluster_size_raw)) अणु
		xfs_warn(mp,
	"Sparse inode block alignment (%u) must match cluster size (%llu).",
			 mp->m_sb.sb_spino_align,
			 XFS_B_TO_FSBT(mp, igeo->inode_cluster_size_raw));
		error = -EINVAL;
		जाओ out_हटाओ_uuid;
	पूर्ण

	/*
	 * Check that the data (and log अगर separate) is an ok size.
	 */
	error = xfs_check_sizes(mp);
	अगर (error)
		जाओ out_हटाओ_uuid;

	/*
	 * Initialize realसमय fields in the mount काष्ठाure
	 */
	error = xfs_rपंचांगount_init(mp);
	अगर (error) अणु
		xfs_warn(mp, "RT mount failed");
		जाओ out_हटाओ_uuid;
	पूर्ण

	/*
	 *  Copies the low order bits of the बारtamp and the अक्रमomly
	 *  set "sequence" number out of a UUID.
	 */
	mp->m_fixedfsid[0] =
		(get_unaligned_be16(&sbp->sb_uuid.b[8]) << 16) |
		 get_unaligned_be16(&sbp->sb_uuid.b[4]);
	mp->m_fixedfsid[1] = get_unaligned_be32(&sbp->sb_uuid.b[0]);

	error = xfs_da_mount(mp);
	अगर (error) अणु
		xfs_warn(mp, "Failed dir/attr init: %d", error);
		जाओ out_हटाओ_uuid;
	पूर्ण

	/*
	 * Initialize the precomputed transaction reservations values.
	 */
	xfs_trans_init(mp);

	/*
	 * Allocate and initialize the per-ag data.
	 */
	error = xfs_initialize_perag(mp, sbp->sb_agcount, &mp->m_maxagi);
	अगर (error) अणु
		xfs_warn(mp, "Failed per-ag init: %d", error);
		जाओ out_मुक्त_dir;
	पूर्ण

	अगर (XFS_IS_CORRUPT(mp, !sbp->sb_logblocks)) अणु
		xfs_warn(mp, "no log defined");
		error = -EFSCORRUPTED;
		जाओ out_मुक्त_perag;
	पूर्ण

	/*
	 * Log's mount-समय initialization. The first part of recovery can place
	 * some items on the AIL, to be handled when recovery is finished or
	 * cancelled.
	 */
	error = xfs_log_mount(mp, mp->m_logdev_targp,
			      XFS_FSB_TO_DADDR(mp, sbp->sb_logstart),
			      XFS_FSB_TO_BB(mp, sbp->sb_logblocks));
	अगर (error) अणु
		xfs_warn(mp, "log mount failed");
		जाओ out_fail_रुको;
	पूर्ण

	/* Make sure the summary counts are ok. */
	error = xfs_check_summary_counts(mp);
	अगर (error)
		जाओ out_log_dealloc;

	/*
	 * Get and sanity-check the root inode.
	 * Save the poपूर्णांकer to it in the mount काष्ठाure.
	 */
	error = xfs_iget(mp, शून्य, sbp->sb_rootino, XFS_IGET_UNTRUSTED,
			 XFS_ILOCK_EXCL, &rip);
	अगर (error) अणु
		xfs_warn(mp,
			"Failed to read root inode 0x%llx, error %d",
			sbp->sb_rootino, -error);
		जाओ out_log_dealloc;
	पूर्ण

	ASSERT(rip != शून्य);

	अगर (XFS_IS_CORRUPT(mp, !S_ISसूची(VFS_I(rip)->i_mode))) अणु
		xfs_warn(mp, "corrupted root inode %llu: not a directory",
			(अचिन्हित दीर्घ दीर्घ)rip->i_ino);
		xfs_iunlock(rip, XFS_ILOCK_EXCL);
		error = -EFSCORRUPTED;
		जाओ out_rele_rip;
	पूर्ण
	mp->m_rootip = rip;	/* save it */

	xfs_iunlock(rip, XFS_ILOCK_EXCL);

	/*
	 * Initialize realसमय inode poपूर्णांकers in the mount काष्ठाure
	 */
	error = xfs_rपंचांगount_inodes(mp);
	अगर (error) अणु
		/*
		 * Free up the root inode.
		 */
		xfs_warn(mp, "failed to read RT inodes");
		जाओ out_rele_rip;
	पूर्ण

	/*
	 * If this is a पढ़ो-only mount defer the superblock updates until
	 * the next remount पूर्णांकo ग_लिखोable mode.  Otherwise we would never
	 * perक्रमm the update e.g. क्रम the root fileप्रणाली.
	 */
	अगर (mp->m_update_sb && !(mp->m_flags & XFS_MOUNT_RDONLY)) अणु
		error = xfs_sync_sb(mp, false);
		अगर (error) अणु
			xfs_warn(mp, "failed to write sb changes");
			जाओ out_rtunmount;
		पूर्ण
	पूर्ण

	/*
	 * Initialise the XFS quota management subप्रणाली क्रम this mount
	 */
	अगर (XFS_IS_QUOTA_RUNNING(mp)) अणु
		error = xfs_qm_newmount(mp, &quotamount, &quotaflags);
		अगर (error)
			जाओ out_rtunmount;
	पूर्ण अन्यथा अणु
		ASSERT(!XFS_IS_QUOTA_ON(mp));

		/*
		 * If a file प्रणाली had quotas running earlier, but decided to
		 * mount without -o uquota/pquota/gquota options, revoke the
		 * quotachecked license.
		 */
		अगर (mp->m_sb.sb_qflags & XFS_ALL_QUOTA_ACCT) अणु
			xfs_notice(mp, "resetting quota flags");
			error = xfs_mount_reset_sbqflags(mp);
			अगर (error)
				जाओ out_rtunmount;
		पूर्ण
	पूर्ण

	/*
	 * Finish recovering the file प्रणाली.  This part needed to be delayed
	 * until after the root and real-समय biपंचांगap inodes were consistently
	 * पढ़ो in.
	 */
	error = xfs_log_mount_finish(mp);
	अगर (error) अणु
		xfs_warn(mp, "log mount finish failed");
		जाओ out_rtunmount;
	पूर्ण

	/*
	 * Now the log is fully replayed, we can transition to full पढ़ो-only
	 * mode क्रम पढ़ो-only mounts. This will sync all the metadata and clean
	 * the log so that the recovery we just perक्रमmed करोes not have to be
	 * replayed again on the next mount.
	 *
	 * We use the same quiesce mechanism as the rw->ro remount, as they are
	 * semantically identical operations.
	 */
	अगर ((mp->m_flags & (XFS_MOUNT_RDONLY|XFS_MOUNT_NORECOVERY)) ==
							XFS_MOUNT_RDONLY) अणु
		xfs_log_clean(mp);
	पूर्ण

	/*
	 * Complete the quota initialisation, post-log-replay component.
	 */
	अगर (quotamount) अणु
		ASSERT(mp->m_qflags == 0);
		mp->m_qflags = quotaflags;

		xfs_qm_mount_quotas(mp);
	पूर्ण

	/*
	 * Now we are mounted, reserve a small amount of unused space क्रम
	 * privileged transactions. This is needed so that transaction
	 * space required क्रम critical operations can dip पूर्णांकo this pool
	 * when at ENOSPC. This is needed क्रम operations like create with
	 * attr, unwritten extent conversion at ENOSPC, etc. Data allocations
	 * are not allowed to use this reserved space.
	 *
	 * This may drive us straight to ENOSPC on mount, but that implies
	 * we were alपढ़ोy there on the last unmount. Warn अगर this occurs.
	 */
	अगर (!(mp->m_flags & XFS_MOUNT_RDONLY)) अणु
		resblks = xfs_शेष_resblks(mp);
		error = xfs_reserve_blocks(mp, &resblks, शून्य);
		अगर (error)
			xfs_warn(mp,
	"Unable to allocate reserve blocks. Continuing without reserve pool.");

		/* Recover any CoW blocks that never got remapped. */
		error = xfs_reflink_recover_cow(mp);
		अगर (error) अणु
			xfs_err(mp,
	"Error %d recovering leftover CoW allocations.", error);
			xfs_क्रमce_shutकरोwn(mp, SHUTDOWN_CORRUPT_INCORE);
			जाओ out_quota;
		पूर्ण

		/* Reserve AG blocks क्रम future btree expansion. */
		error = xfs_fs_reserve_ag_blocks(mp);
		अगर (error && error != -ENOSPC)
			जाओ out_agresv;
	पूर्ण

	वापस 0;

 out_agresv:
	xfs_fs_unreserve_ag_blocks(mp);
 out_quota:
	xfs_qm_unmount_quotas(mp);
 out_rtunmount:
	xfs_rtunmount_inodes(mp);
 out_rele_rip:
	xfs_irele(rip);
	/* Clean out dquots that might be in memory after quotacheck. */
	xfs_qm_unmount(mp);
	/*
	 * Flush all inode reclamation work and flush the log.
	 * We have to करो this /after/ rtunmount and qm_unmount because those
	 * two will have scheduled delayed reclaim क्रम the rt/quota inodes.
	 *
	 * This is slightly dअगरferent from the unmountfs call sequence
	 * because we could be tearing करोwn a partially set up mount.  In
	 * particular, अगर log_mount_finish fails we bail out without calling
	 * qm_unmount_quotas and thereक्रमe rely on qm_unmount to release the
	 * quota inodes.
	 */
	xfs_unmount_flush_inodes(mp);
 out_log_dealloc:
	xfs_log_mount_cancel(mp);
 out_fail_रुको:
	अगर (mp->m_logdev_targp && mp->m_logdev_targp != mp->m_ddev_targp)
		xfs_buftarg_drain(mp->m_logdev_targp);
	xfs_buftarg_drain(mp->m_ddev_targp);
 out_मुक्त_perag:
	xfs_मुक्त_perag(mp);
 out_मुक्त_dir:
	xfs_da_unmount(mp);
 out_हटाओ_uuid:
	xfs_uuid_unmount(mp);
 out_हटाओ_errortag:
	xfs_errortag_del(mp);
 out_हटाओ_error_sysfs:
	xfs_error_sysfs_del(mp);
 out_del_stats:
	xfs_sysfs_del(&mp->m_stats.xs_kobj);
 out_हटाओ_sysfs:
	xfs_sysfs_del(&mp->m_kobj);
 out:
	वापस error;
पूर्ण

/*
 * This flushes out the inodes,dquots and the superblock, unmounts the
 * log and makes sure that incore काष्ठाures are मुक्तd.
 */
व्योम
xfs_unmountfs(
	काष्ठा xfs_mount	*mp)
अणु
	uपूर्णांक64_t		resblks;
	पूर्णांक			error;

	xfs_blockgc_stop(mp);
	xfs_fs_unreserve_ag_blocks(mp);
	xfs_qm_unmount_quotas(mp);
	xfs_rtunmount_inodes(mp);
	xfs_irele(mp->m_rootip);

	xfs_unmount_flush_inodes(mp);

	xfs_qm_unmount(mp);

	/*
	 * Unreserve any blocks we have so that when we unmount we करोn't account
	 * the reserved मुक्त space as used. This is really only necessary क्रम
	 * lazy superblock counting because it trusts the incore superblock
	 * counters to be असलolutely correct on clean unmount.
	 *
	 * We करोn't bother correcting this अन्यथाwhere क्रम lazy superblock
	 * counting because on mount of an unclean fileप्रणाली we reस्थिरruct the
	 * correct counter value and this is irrelevant.
	 *
	 * For non-lazy counter fileप्रणालीs, this करोesn't matter at all because
	 * we only every apply deltas to the superblock and hence the incore
	 * value करोes not matter....
	 */
	resblks = 0;
	error = xfs_reserve_blocks(mp, &resblks, शून्य);
	अगर (error)
		xfs_warn(mp, "Unable to free reserved block pool. "
				"Freespace may not be correct on next mount.");

	xfs_log_unmount(mp);
	xfs_da_unmount(mp);
	xfs_uuid_unmount(mp);

#अगर defined(DEBUG)
	xfs_errortag_clearall(mp);
#पूर्ण_अगर
	xfs_मुक्त_perag(mp);

	xfs_errortag_del(mp);
	xfs_error_sysfs_del(mp);
	xfs_sysfs_del(&mp->m_stats.xs_kobj);
	xfs_sysfs_del(&mp->m_kobj);
पूर्ण

/*
 * Determine whether modअगरications can proceed. The caller specअगरies the minimum
 * मुक्तze level क्रम which modअगरications should not be allowed. This allows
 * certain operations to proceed जबतक the मुक्तze sequence is in progress, अगर
 * necessary.
 */
bool
xfs_fs_writable(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			level)
अणु
	ASSERT(level > SB_UNFROZEN);
	अगर ((mp->m_super->s_ग_लिखोrs.frozen >= level) ||
	    XFS_FORCED_SHUTDOWN(mp) || (mp->m_flags & XFS_MOUNT_RDONLY))
		वापस false;

	वापस true;
पूर्ण

/*
 * Deltas क्रम the block count can vary from 1 to very large, but lock contention
 * only occurs on frequent small block count updates such as in the delayed
 * allocation path क्रम buffered ग_लिखोs (page a समय updates). Hence we set
 * a large batch count (1024) to minimise global counter updates except when
 * we get near to ENOSPC and we have to be very accurate with our updates.
 */
#घोषणा XFS_FDBLOCKS_BATCH	1024
पूर्णांक
xfs_mod_fdblocks(
	काष्ठा xfs_mount	*mp,
	पूर्णांक64_t			delta,
	bool			rsvd)
अणु
	पूर्णांक64_t			lcounter;
	दीर्घ दीर्घ		res_used;
	s32			batch;
	uपूर्णांक64_t		set_aside;

	अगर (delta > 0) अणु
		/*
		 * If the reserve pool is depleted, put blocks back पूर्णांकo it
		 * first. Most of the समय the pool is full.
		 */
		अगर (likely(mp->m_resblks == mp->m_resblks_avail)) अणु
			percpu_counter_add(&mp->m_fdblocks, delta);
			वापस 0;
		पूर्ण

		spin_lock(&mp->m_sb_lock);
		res_used = (दीर्घ दीर्घ)(mp->m_resblks - mp->m_resblks_avail);

		अगर (res_used > delta) अणु
			mp->m_resblks_avail += delta;
		पूर्ण अन्यथा अणु
			delta -= res_used;
			mp->m_resblks_avail = mp->m_resblks;
			percpu_counter_add(&mp->m_fdblocks, delta);
		पूर्ण
		spin_unlock(&mp->m_sb_lock);
		वापस 0;
	पूर्ण

	/*
	 * Taking blocks away, need to be more accurate the बंदr we
	 * are to zero.
	 *
	 * If the counter has a value of less than 2 * max batch size,
	 * then make everything serialise as we are real बंद to
	 * ENOSPC.
	 */
	अगर (__percpu_counter_compare(&mp->m_fdblocks, 2 * XFS_FDBLOCKS_BATCH,
				     XFS_FDBLOCKS_BATCH) < 0)
		batch = 1;
	अन्यथा
		batch = XFS_FDBLOCKS_BATCH;

	/*
	 * Set aside allocbt blocks because these blocks are tracked as मुक्त
	 * space but not available क्रम allocation. Technically this means that a
	 * single reservation cannot consume all reमुख्यing मुक्त space, but the
	 * ratio of allocbt blocks to usable मुक्त blocks should be rather small.
	 * The tradeoff without this is that fileप्रणालीs that मुख्यtain high
	 * perag block reservations can over reserve physical block availability
	 * and fail physical allocation, which leads to much more serious
	 * problems (i.e. transaction पात, pagecache discards, etc.) than
	 * slightly premature -ENOSPC.
	 */
	set_aside = mp->m_alloc_set_aside + atomic64_पढ़ो(&mp->m_allocbt_blks);
	percpu_counter_add_batch(&mp->m_fdblocks, delta, batch);
	अगर (__percpu_counter_compare(&mp->m_fdblocks, set_aside,
				     XFS_FDBLOCKS_BATCH) >= 0) अणु
		/* we had space! */
		वापस 0;
	पूर्ण

	/*
	 * lock up the sb क्रम dipping पूर्णांकo reserves beक्रमe releasing the space
	 * that took us to ENOSPC.
	 */
	spin_lock(&mp->m_sb_lock);
	percpu_counter_add(&mp->m_fdblocks, -delta);
	अगर (!rsvd)
		जाओ fdblocks_enospc;

	lcounter = (दीर्घ दीर्घ)mp->m_resblks_avail + delta;
	अगर (lcounter >= 0) अणु
		mp->m_resblks_avail = lcounter;
		spin_unlock(&mp->m_sb_lock);
		वापस 0;
	पूर्ण
	xfs_warn_once(mp,
"Reserve blocks depleted! Consider increasing reserve pool size.");

fdblocks_enospc:
	spin_unlock(&mp->m_sb_lock);
	वापस -ENOSPC;
पूर्ण

पूर्णांक
xfs_mod_frextents(
	काष्ठा xfs_mount	*mp,
	पूर्णांक64_t			delta)
अणु
	पूर्णांक64_t			lcounter;
	पूर्णांक			ret = 0;

	spin_lock(&mp->m_sb_lock);
	lcounter = mp->m_sb.sb_frextents + delta;
	अगर (lcounter < 0)
		ret = -ENOSPC;
	अन्यथा
		mp->m_sb.sb_frextents = lcounter;
	spin_unlock(&mp->m_sb_lock);
	वापस ret;
पूर्ण

/*
 * Used to मुक्त the superblock aदीर्घ various error paths.
 */
व्योम
xfs_मुक्तsb(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_buf		*bp = mp->m_sb_bp;

	xfs_buf_lock(bp);
	mp->m_sb_bp = शून्य;
	xfs_buf_rअन्यथा(bp);
पूर्ण

/*
 * If the underlying (data/log/rt) device is पढ़ोonly, there are some
 * operations that cannot proceed.
 */
पूर्णांक
xfs_dev_is_पढ़ो_only(
	काष्ठा xfs_mount	*mp,
	अक्षर			*message)
अणु
	अगर (xfs_पढ़ोonly_buftarg(mp->m_ddev_targp) ||
	    xfs_पढ़ोonly_buftarg(mp->m_logdev_targp) ||
	    (mp->m_rtdev_targp && xfs_पढ़ोonly_buftarg(mp->m_rtdev_targp))) अणु
		xfs_notice(mp, "%s required on read-only device.", message);
		xfs_notice(mp, "write access unavailable, cannot proceed.");
		वापस -EROFS;
	पूर्ण
	वापस 0;
पूर्ण

/* Force the summary counters to be recalculated at next mount. */
व्योम
xfs_क्रमce_summary_recalc(
	काष्ठा xfs_mount	*mp)
अणु
	अगर (!xfs_sb_version_haslazysbcount(&mp->m_sb))
		वापस;

	xfs_fs_mark_sick(mp, XFS_SICK_FS_COUNTERS);
पूर्ण

/*
 * Update the in-core delayed block counter.
 *
 * We prefer to update the counter without having to take a spinlock क्रम every
 * counter update (i.e. batching).  Each change to delayed allocation
 * reservations can change can easily exceed the शेष percpu counter
 * batching, so we use a larger batch factor here.
 *
 * Note that we करोn't currently have any callers requiring fast summation
 * (e.g. percpu_counter_पढ़ो) so we can use a big batch value here.
 */
#घोषणा XFS_DELALLOC_BATCH	(4096)
व्योम
xfs_mod_delalloc(
	काष्ठा xfs_mount	*mp,
	पूर्णांक64_t			delta)
अणु
	percpu_counter_add_batch(&mp->m_delalloc_blks, delta,
			XFS_DELALLOC_BATCH);
पूर्ण
