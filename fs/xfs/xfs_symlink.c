<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
 * Copyright (c) 2012-2013 Red Hat, Inc.
 * All rights reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_symlink.h"
#समावेश "xfs_trans_space.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"

/* ----- Kernel only functions below ----- */
पूर्णांक
xfs_पढ़ोlink_bmap_ilocked(
	काष्ठा xfs_inode	*ip,
	अक्षर			*link)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	काष्ठा xfs_bmbt_irec	mval[XFS_SYMLINK_MAPS];
	काष्ठा xfs_buf		*bp;
	xfs_daddr_t		d;
	अक्षर			*cur_chunk;
	पूर्णांक			pathlen = ip->i_disk_size;
	पूर्णांक			nmaps = XFS_SYMLINK_MAPS;
	पूर्णांक			byte_cnt;
	पूर्णांक			n;
	पूर्णांक			error = 0;
	पूर्णांक			fsblocks = 0;
	पूर्णांक			offset;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_SHARED | XFS_ILOCK_EXCL));

	fsblocks = xfs_symlink_blocks(mp, pathlen);
	error = xfs_bmapi_पढ़ो(ip, 0, fsblocks, mval, &nmaps, 0);
	अगर (error)
		जाओ out;

	offset = 0;
	क्रम (n = 0; n < nmaps; n++) अणु
		d = XFS_FSB_TO_DADDR(mp, mval[n].br_startblock);
		byte_cnt = XFS_FSB_TO_B(mp, mval[n].br_blockcount);

		error = xfs_buf_पढ़ो(mp->m_ddev_targp, d, BTOBB(byte_cnt), 0,
				&bp, &xfs_symlink_buf_ops);
		अगर (error)
			वापस error;
		byte_cnt = XFS_SYMLINK_BUF_SPACE(mp, byte_cnt);
		अगर (pathlen < byte_cnt)
			byte_cnt = pathlen;

		cur_chunk = bp->b_addr;
		अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
			अगर (!xfs_symlink_hdr_ok(ip->i_ino, offset,
							byte_cnt, bp)) अणु
				error = -EFSCORRUPTED;
				xfs_alert(mp,
"symlink header does not match required off/len/owner (0x%x/Ox%x,0x%llx)",
					offset, byte_cnt, ip->i_ino);
				xfs_buf_rअन्यथा(bp);
				जाओ out;

			पूर्ण

			cur_chunk += माप(काष्ठा xfs_dsymlink_hdr);
		पूर्ण

		स_नकल(link + offset, cur_chunk, byte_cnt);

		pathlen -= byte_cnt;
		offset += byte_cnt;

		xfs_buf_rअन्यथा(bp);
	पूर्ण
	ASSERT(pathlen == 0);

	link[ip->i_disk_size] = '\0';
	error = 0;

 out:
	वापस error;
पूर्ण

पूर्णांक
xfs_पढ़ोlink(
	काष्ठा xfs_inode *ip,
	अक्षर		*link)
अणु
	काष्ठा xfs_mount *mp = ip->i_mount;
	xfs_fमाप_प्रकार	pathlen;
	पूर्णांक		error = 0;

	trace_xfs_पढ़ोlink(ip);

	ASSERT(ip->i_df.अगर_क्रमmat != XFS_DINODE_FMT_LOCAL);

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	xfs_ilock(ip, XFS_ILOCK_SHARED);

	pathlen = ip->i_disk_size;
	अगर (!pathlen)
		जाओ out;

	अगर (pathlen < 0 || pathlen > XFS_SYMLINK_MAXLEN) अणु
		xfs_alert(mp, "%s: inode (%llu) bad symlink length (%lld)",
			 __func__, (अचिन्हित दीर्घ दीर्घ) ip->i_ino,
			 (दीर्घ दीर्घ) pathlen);
		ASSERT(0);
		error = -EFSCORRUPTED;
		जाओ out;
	पूर्ण


	error = xfs_पढ़ोlink_bmap_ilocked(ip, link);

 out:
	xfs_iunlock(ip, XFS_ILOCK_SHARED);
	वापस error;
पूर्ण

पूर्णांक
xfs_symlink(
	काष्ठा user_namespace	*mnt_userns,
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_name		*link_name,
	स्थिर अक्षर		*target_path,
	umode_t			mode,
	काष्ठा xfs_inode	**ipp)
अणु
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_trans	*tp = शून्य;
	काष्ठा xfs_inode	*ip = शून्य;
	पूर्णांक			error = 0;
	पूर्णांक			pathlen;
	bool                    unlock_dp_on_error = false;
	xfs_fileoff_t		first_fsb;
	xfs_filblks_t		fs_blocks;
	पूर्णांक			nmaps;
	काष्ठा xfs_bmbt_irec	mval[XFS_SYMLINK_MAPS];
	xfs_daddr_t		d;
	स्थिर अक्षर		*cur_chunk;
	पूर्णांक			byte_cnt;
	पूर्णांक			n;
	काष्ठा xfs_buf		*bp;
	prid_t			prid;
	काष्ठा xfs_dquot	*udqp = शून्य;
	काष्ठा xfs_dquot	*gdqp = शून्य;
	काष्ठा xfs_dquot	*pdqp = शून्य;
	uपूर्णांक			resblks;

	*ipp = शून्य;

	trace_xfs_symlink(dp, link_name);

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	/*
	 * Check component lengths of the target path name.
	 */
	pathlen = म_माप(target_path);
	अगर (pathlen >= XFS_SYMLINK_MAXLEN)      /* total string too दीर्घ */
		वापस -ENAMETOOLONG;
	ASSERT(pathlen > 0);

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

	/*
	 * The symlink will fit पूर्णांकo the inode data विभाजन?
	 * There can't be any attributes so we get the whole variable part.
	 */
	अगर (pathlen <= XFS_LITINO(mp))
		fs_blocks = 0;
	अन्यथा
		fs_blocks = xfs_symlink_blocks(mp, pathlen);
	resblks = XFS_SYMLINK_SPACE_RES(mp, link_name->len, fs_blocks);

	error = xfs_trans_alloc_icreate(mp, &M_RES(mp)->tr_symlink, udqp, gdqp,
			pdqp, resblks, &tp);
	अगर (error)
		जाओ out_release_dquots;

	xfs_ilock(dp, XFS_ILOCK_EXCL | XFS_ILOCK_PARENT);
	unlock_dp_on_error = true;

	/*
	 * Check whether the directory allows new symlinks or not.
	 */
	अगर (dp->i_dअगरlags & XFS_DIFLAG_NOSYMLINKS) अणु
		error = -EPERM;
		जाओ out_trans_cancel;
	पूर्ण

	error = xfs_iext_count_may_overflow(dp, XFS_DATA_FORK,
			XFS_IEXT_सूची_MANIP_CNT(mp));
	अगर (error)
		जाओ out_trans_cancel;

	/*
	 * Allocate an inode क्रम the symlink.
	 */
	error = xfs_dir_ialloc(mnt_userns, &tp, dp, S_IFLNK | (mode & ~S_IFMT),
			       1, 0, prid, false, &ip);
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

	/*
	 * Also attach the dquot(s) to it, अगर applicable.
	 */
	xfs_qm_vop_create_dqattach(tp, ip, udqp, gdqp, pdqp);

	resblks -= XFS_IALLOC_SPACE_RES(mp);
	/*
	 * If the symlink will fit पूर्णांकo the inode, ग_लिखो it अंतरभूत.
	 */
	अगर (pathlen <= XFS_IFORK_DSIZE(ip)) अणु
		xfs_init_local_विभाजन(ip, XFS_DATA_FORK, target_path, pathlen);

		ip->i_disk_size = pathlen;
		ip->i_df.अगर_क्रमmat = XFS_DINODE_FMT_LOCAL;
		xfs_trans_log_inode(tp, ip, XFS_ILOG_DDATA | XFS_ILOG_CORE);
	पूर्ण अन्यथा अणु
		पूर्णांक	offset;

		first_fsb = 0;
		nmaps = XFS_SYMLINK_MAPS;

		error = xfs_bmapi_ग_लिखो(tp, ip, first_fsb, fs_blocks,
				  XFS_BMAPI_METADATA, resblks, mval, &nmaps);
		अगर (error)
			जाओ out_trans_cancel;

		resblks -= fs_blocks;
		ip->i_disk_size = pathlen;
		xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);

		cur_chunk = target_path;
		offset = 0;
		क्रम (n = 0; n < nmaps; n++) अणु
			अक्षर	*buf;

			d = XFS_FSB_TO_DADDR(mp, mval[n].br_startblock);
			byte_cnt = XFS_FSB_TO_B(mp, mval[n].br_blockcount);
			error = xfs_trans_get_buf(tp, mp->m_ddev_targp, d,
					       BTOBB(byte_cnt), 0, &bp);
			अगर (error)
				जाओ out_trans_cancel;
			bp->b_ops = &xfs_symlink_buf_ops;

			byte_cnt = XFS_SYMLINK_BUF_SPACE(mp, byte_cnt);
			byte_cnt = min(byte_cnt, pathlen);

			buf = bp->b_addr;
			buf += xfs_symlink_hdr_set(mp, ip->i_ino, offset,
						   byte_cnt, bp);

			स_नकल(buf, cur_chunk, byte_cnt);

			cur_chunk += byte_cnt;
			pathlen -= byte_cnt;
			offset += byte_cnt;

			xfs_trans_buf_set_type(tp, bp, XFS_BLFT_SYMLINK_BUF);
			xfs_trans_log_buf(tp, bp, 0, (buf + byte_cnt - 1) -
							(अक्षर *)bp->b_addr);
		पूर्ण
		ASSERT(pathlen == 0);
	पूर्ण
	i_size_ग_लिखो(VFS_I(ip), ip->i_disk_size);

	/*
	 * Create the directory entry क्रम the symlink.
	 */
	error = xfs_dir_createname(tp, dp, link_name, ip->i_ino, resblks);
	अगर (error)
		जाओ out_trans_cancel;
	xfs_trans_ichgसमय(tp, dp, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	xfs_trans_log_inode(tp, dp, XFS_ILOG_CORE);

	/*
	 * If this is a synchronous mount, make sure that the
	 * symlink transaction goes to disk beक्रमe वापसing to
	 * the user.
	 */
	अगर (mp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_सूचीSYNC)) अणु
		xfs_trans_set_sync(tp);
	पूर्ण

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

/*
 * Free a symlink that has blocks associated with it.
 *
 * Note: zero length symlinks are not allowed to exist. When we set the size to
 * zero, also change it to a regular file so that it करोes not get written to
 * disk as a zero length symlink. The inode is on the unlinked list alपढ़ोy, so
 * userspace cannot find this inode anymore, so this change is not user visible
 * but allows us to catch corrupt zero-length symlinks in the verअगरiers.
 */
STATIC पूर्णांक
xfs_inactive_symlink_rmt(
	काष्ठा xfs_inode *ip)
अणु
	काष्ठा xfs_buf	*bp;
	पूर्णांक		करोne;
	पूर्णांक		error;
	पूर्णांक		i;
	xfs_mount_t	*mp;
	xfs_bmbt_irec_t	mval[XFS_SYMLINK_MAPS];
	पूर्णांक		nmaps;
	पूर्णांक		size;
	xfs_trans_t	*tp;

	mp = ip->i_mount;
	ASSERT(!xfs_need_iपढ़ो_extents(&ip->i_df));
	/*
	 * We're मुक्तing a symlink that has some
	 * blocks allocated to it.  Free the
	 * blocks here.  We know that we've got
	 * either 1 or 2 extents and that we can
	 * मुक्त them all in one bunmapi call.
	 */
	ASSERT(ip->i_df.अगर_nextents > 0 && ip->i_df.अगर_nextents <= 2);

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_itruncate, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, 0);

	/*
	 * Lock the inode, fix the size, turn it पूर्णांकo a regular file and join it
	 * to the transaction.  Hold it so in the normal path, we still have it
	 * locked क्रम the second transaction.  In the error paths we need it
	 * held so the cancel won't rele it, see below.
	 */
	size = (पूर्णांक)ip->i_disk_size;
	ip->i_disk_size = 0;
	VFS_I(ip)->i_mode = (VFS_I(ip)->i_mode & ~S_IFMT) | S_IFREG;
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	/*
	 * Find the block(s) so we can inval and unmap them.
	 */
	करोne = 0;
	nmaps = ARRAY_SIZE(mval);
	error = xfs_bmapi_पढ़ो(ip, 0, xfs_symlink_blocks(mp, size),
				mval, &nmaps, 0);
	अगर (error)
		जाओ error_trans_cancel;
	/*
	 * Invalidate the block(s). No validation is करोne.
	 */
	क्रम (i = 0; i < nmaps; i++) अणु
		error = xfs_trans_get_buf(tp, mp->m_ddev_targp,
				XFS_FSB_TO_DADDR(mp, mval[i].br_startblock),
				XFS_FSB_TO_BB(mp, mval[i].br_blockcount), 0,
				&bp);
		अगर (error)
			जाओ error_trans_cancel;
		xfs_trans_binval(tp, bp);
	पूर्ण
	/*
	 * Unmap the dead block(s) to the dfops.
	 */
	error = xfs_bunmapi(tp, ip, 0, size, 0, nmaps, &करोne);
	अगर (error)
		जाओ error_trans_cancel;
	ASSERT(करोne);

	/*
	 * Commit the transaction. This first logs the EFI and the inode, then
	 * rolls and commits the transaction that मुक्तs the extents.
	 */
	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	error = xfs_trans_commit(tp);
	अगर (error) अणु
		ASSERT(XFS_FORCED_SHUTDOWN(mp));
		जाओ error_unlock;
	पूर्ण

	/*
	 * Remove the memory क्रम extent descriptions (just bookkeeping).
	 */
	अगर (ip->i_df.अगर_bytes)
		xfs_idata_पुनः_स्मृति(ip, -ip->i_df.अगर_bytes, XFS_DATA_FORK);
	ASSERT(ip->i_df.अगर_bytes == 0);

	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस 0;

error_trans_cancel:
	xfs_trans_cancel(tp);
error_unlock:
	xfs_iunlock(ip, XFS_ILOCK_EXCL);
	वापस error;
पूर्ण

/*
 * xfs_inactive_symlink - मुक्त a symlink
 */
पूर्णांक
xfs_inactive_symlink(
	काष्ठा xfs_inode	*ip)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	पूर्णांक			pathlen;

	trace_xfs_inactive_symlink(ip);

	अगर (XFS_FORCED_SHUTDOWN(mp))
		वापस -EIO;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	pathlen = (पूर्णांक)ip->i_disk_size;
	ASSERT(pathlen);

	अगर (pathlen <= 0 || pathlen > XFS_SYMLINK_MAXLEN) अणु
		xfs_alert(mp, "%s: inode (0x%llx) bad symlink length (%d)",
			 __func__, (अचिन्हित दीर्घ दीर्घ)ip->i_ino, pathlen);
		xfs_iunlock(ip, XFS_ILOCK_EXCL);
		ASSERT(0);
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Inline विभाजन state माला_लो हटाओd by xfs_dअगरree() so we have nothing to
	 * करो here in that हाल.
	 */
	अगर (ip->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL) अणु
		xfs_iunlock(ip, XFS_ILOCK_EXCL);
		वापस 0;
	पूर्ण

	xfs_iunlock(ip, XFS_ILOCK_EXCL);

	/* हटाओ the remote symlink */
	वापस xfs_inactive_symlink_rmt(ip);
पूर्ण
