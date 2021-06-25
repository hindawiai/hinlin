<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_inode_item.h"

#समावेश <linux/iversion.h>

/*
 * Add a locked inode to the transaction.
 *
 * The inode must be locked, and it cannot be associated with any transaction.
 * If lock_flags is non-zero the inode will be unlocked on transaction commit.
 */
व्योम
xfs_trans_ijoin(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	uपूर्णांक			lock_flags)
अणु
	काष्ठा xfs_inode_log_item *iip;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	अगर (ip->i_itemp == शून्य)
		xfs_inode_item_init(ip, ip->i_mount);
	iip = ip->i_itemp;

	ASSERT(iip->ili_lock_flags == 0);
	iip->ili_lock_flags = lock_flags;
	ASSERT(!xfs_अगरlags_test(ip, XFS_ISTALE));

	/*
	 * Get a log_item_desc to poपूर्णांक at the new item.
	 */
	xfs_trans_add_item(tp, &iip->ili_item);
पूर्ण

/*
 * Transactional inode बारtamp update. Requires the inode to be locked and
 * joined to the transaction supplied. Relies on the transaction subप्रणाली to
 * track dirty state and update/ग_लिखोback the inode accordingly.
 */
व्योम
xfs_trans_ichgसमय(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	पूर्णांक			flags)
अणु
	काष्ठा inode		*inode = VFS_I(ip);
	काष्ठा बारpec64	tv;

	ASSERT(tp);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	tv = current_समय(inode);

	अगर (flags & XFS_ICHGTIME_MOD)
		inode->i_mसमय = tv;
	अगर (flags & XFS_ICHGTIME_CHG)
		inode->i_स_समय = tv;
	अगर (flags & XFS_ICHGTIME_CREATE)
		ip->i_crसमय = tv;
पूर्ण

/*
 * This is called to mark the fields indicated in fieldmask as needing to be
 * logged when the transaction is committed.  The inode must alपढ़ोy be
 * associated with the given transaction.
 *
 * The values क्रम fieldmask are defined in xfs_inode_item.h.  We always log all
 * of the core inode अगर any of it has changed, and we always log all of the
 * अंतरभूत data/extents/b-tree root अगर any of them has changed.
 *
 * Grab and pin the cluster buffer associated with this inode to aव्योम RMW
 * cycles at inode ग_लिखोback समय. Aव्योम the need to add error handling to every
 * xfs_trans_log_inode() call by shutting करोwn on पढ़ो error.  This will cause
 * transactions to fail and everything to error out, just like अगर we वापस a
 * पढ़ो error in a dirty transaction and cancel it.
 */
व्योम
xfs_trans_log_inode(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*ip,
	uपूर्णांक			flags)
अणु
	काष्ठा xfs_inode_log_item *iip = ip->i_itemp;
	काष्ठा inode		*inode = VFS_I(ip);
	uपूर्णांक			iversion_flags = 0;

	ASSERT(iip);
	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));
	ASSERT(!xfs_अगरlags_test(ip, XFS_ISTALE));

	tp->t_flags |= XFS_TRANS_सूचीTY;

	/*
	 * Don't bother with i_lock क्रम the I_सूचीTY_TIME check here, as races
	 * करोn't matter - we either will need an extra transaction in 24 hours
	 * to log the बारtamps, or will clear alपढ़ोy cleared fields in the
	 * worst हाल.
	 */
	अगर (inode->i_state & I_सूचीTY_TIME) अणु
		spin_lock(&inode->i_lock);
		inode->i_state &= ~I_सूचीTY_TIME;
		spin_unlock(&inode->i_lock);
	पूर्ण

	/*
	 * First समय we log the inode in a transaction, bump the inode change
	 * counter अगर it is configured क्रम this to occur. While we have the
	 * inode locked exclusively क्रम metadata modअगरication, we can usually
	 * aव्योम setting XFS_ILOG_CORE अगर no one has queried the value since
	 * the last समय it was incremented. If we have XFS_ILOG_CORE alपढ़ोy
	 * set however, then go ahead and bump the i_version counter
	 * unconditionally.
	 */
	अगर (!test_and_set_bit(XFS_LI_सूचीTY, &iip->ili_item.li_flags)) अणु
		अगर (IS_I_VERSION(inode) &&
		    inode_maybe_inc_iversion(inode, flags & XFS_ILOG_CORE))
			iversion_flags = XFS_ILOG_CORE;
	पूर्ण

	/*
	 * If we're updating the inode core or the timestamps and it's possible
	 * to upgrade this inode to bigसमय क्रमmat, करो so now.
	 */
	अगर ((flags & (XFS_ILOG_CORE | XFS_ILOG_TIMESTAMP)) &&
	    xfs_sb_version_hasbigसमय(&ip->i_mount->m_sb) &&
	    !xfs_inode_has_bigसमय(ip)) अणु
		ip->i_dअगरlags2 |= XFS_DIFLAG2_BIGTIME;
		flags |= XFS_ILOG_CORE;
	पूर्ण

	/*
	 * Inode verअगरiers on older kernels करोn't check that the extent size
	 * hपूर्णांक is an पूर्णांकeger multiple of the rt extent size on a directory
	 * with both rtinherit and extszinherit flags set.  If we're logging a
	 * directory that is misconfigured in this way, clear the hपूर्णांक.
	 */
	अगर ((ip->i_dअगरlags & XFS_DIFLAG_RTINHERIT) &&
	    (ip->i_dअगरlags & XFS_DIFLAG_EXTSZINHERIT) &&
	    (ip->i_extsize % ip->i_mount->m_sb.sb_rextsize) > 0) अणु
		xfs_info_once(ip->i_mount,
	"Correcting misaligned extent size hint in inode 0x%llx.", ip->i_ino);
		ip->i_dअगरlags &= ~(XFS_DIFLAG_EXTSIZE |
				   XFS_DIFLAG_EXTSZINHERIT);
		ip->i_extsize = 0;
		flags |= XFS_ILOG_CORE;
	पूर्ण

	/*
	 * Record the specअगरic change क्रम fdatasync optimisation. This allows
	 * fdatasync to skip log क्रमces क्रम inodes that are only बारtamp
	 * dirty.
	 */
	spin_lock(&iip->ili_lock);
	iip->ili_fsync_fields |= flags;

	अगर (!iip->ili_item.li_buf) अणु
		काष्ठा xfs_buf	*bp;
		पूर्णांक		error;

		/*
		 * We hold the ILOCK here, so this inode is not going to be
		 * flushed जबतक we are here. Further, because there is no
		 * buffer attached to the item, we know that there is no IO in
		 * progress, so nothing will clear the ili_fields जबतक we पढ़ो
		 * in the buffer. Hence we can safely drop the spin lock and
		 * पढ़ो the buffer knowing that the state will not change from
		 * here.
		 */
		spin_unlock(&iip->ili_lock);
		error = xfs_imap_to_bp(ip->i_mount, tp, &ip->i_imap, &bp);
		अगर (error) अणु
			xfs_क्रमce_shutकरोwn(ip->i_mount, SHUTDOWN_META_IO_ERROR);
			वापस;
		पूर्ण

		/*
		 * We need an explicit buffer reference क्रम the log item but
		 * करोn't want the buffer to reमुख्य attached to the transaction.
		 * Hold the buffer but release the transaction reference once
		 * we've attached the inode log item to the buffer log item
		 * list.
		 */
		xfs_buf_hold(bp);
		spin_lock(&iip->ili_lock);
		iip->ili_item.li_buf = bp;
		bp->b_flags |= _XBF_INODES;
		list_add_tail(&iip->ili_item.li_bio_list, &bp->b_li_list);
		xfs_trans_brअन्यथा(tp, bp);
	पूर्ण

	/*
	 * Always OR in the bits from the ili_last_fields field.  This is to
	 * coordinate with the xfs_अगरlush() and xfs_buf_inode_ioकरोne() routines
	 * in the eventual clearing of the ili_fields bits.  See the big comment
	 * in xfs_अगरlush() क्रम an explanation of this coordination mechanism.
	 */
	iip->ili_fields |= (flags | iip->ili_last_fields | iversion_flags);
	spin_unlock(&iip->ili_lock);
पूर्ण

पूर्णांक
xfs_trans_roll_inode(
	काष्ठा xfs_trans	**tpp,
	काष्ठा xfs_inode	*ip)
अणु
	पूर्णांक			error;

	xfs_trans_log_inode(*tpp, ip, XFS_ILOG_CORE);
	error = xfs_trans_roll(tpp);
	अगर (!error)
		xfs_trans_ijoin(*tpp, ip, 0);
	वापस error;
पूर्ण
