<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2006 Silicon Graphics, Inc.
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
#समावेश "xfs_inode_item.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_log.h"
#समावेश "xfs_error.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_log_recover.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_bmap_btree.h"

STATIC व्योम
xlog_recover_inode_ra_pass2(
	काष्ठा xlog                     *log,
	काष्ठा xlog_recover_item        *item)
अणु
	अगर (item->ri_buf[0].i_len == माप(काष्ठा xfs_inode_log_क्रमmat)) अणु
		काष्ठा xfs_inode_log_क्रमmat	*ilfp = item->ri_buf[0].i_addr;

		xlog_buf_पढ़ोahead(log, ilfp->ilf_blkno, ilfp->ilf_len,
				   &xfs_inode_buf_ra_ops);
	पूर्ण अन्यथा अणु
		काष्ठा xfs_inode_log_क्रमmat_32	*ilfp = item->ri_buf[0].i_addr;

		xlog_buf_पढ़ोahead(log, ilfp->ilf_blkno, ilfp->ilf_len,
				   &xfs_inode_buf_ra_ops);
	पूर्ण
पूर्ण

/*
 * Inode विभाजन owner changes
 *
 * If we have been told that we have to reparent the inode विभाजन, it's because an
 * extent swap operation on a CRC enabled fileप्रणाली has been करोne and we are
 * replaying it. We need to walk the BMBT of the appropriate विभाजन and change the
 * owners of it.
 *
 * The complनिकासy here is that we करोn't have an inode context to work with, so
 * after we've replayed the inode we need to instantiate one.  This is where the
 * fun begins.
 *
 * We are in the middle of log recovery, so we can't run transactions. That
 * means we cannot use cache coherent inode instantiation via xfs_iget(), as
 * that will result in the corresponding iput() running the inode through
 * xfs_inactive(). If we've just replayed an inode core that changes the link
 * count to zero (i.e. it's been unlinked), then xfs_inactive() will run
 * transactions (bad!).
 *
 * So, to aव्योम this, we instantiate an inode directly from the inode core we've
 * just recovered. We have the buffer still locked, and all we really need to
 * instantiate is the inode core and the विभाजनs being modअगरied. We can करो this
 * manually, then run the inode btree owner change, and then tear करोwn the
 * xfs_inode without having to run any transactions at all.
 *
 * Also, because we करोn't have a transaction context available here but need to
 * gather all the buffers we modअगरy क्रम ग_लिखोback so we pass the buffer_list
 * instead क्रम the operation to use.
 */

STATIC पूर्णांक
xfs_recover_inode_owner_change(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dinode	*dip,
	काष्ठा xfs_inode_log_क्रमmat *in_f,
	काष्ठा list_head	*buffer_list)
अणु
	काष्ठा xfs_inode	*ip;
	पूर्णांक			error;

	ASSERT(in_f->ilf_fields & (XFS_ILOG_DOWNER|XFS_ILOG_AOWNER));

	ip = xfs_inode_alloc(mp, in_f->ilf_ino);
	अगर (!ip)
		वापस -ENOMEM;

	/* instantiate the inode */
	ASSERT(dip->di_version >= 3);

	error = xfs_inode_from_disk(ip, dip);
	अगर (error)
		जाओ out_मुक्त_ip;

	अगर (in_f->ilf_fields & XFS_ILOG_DOWNER) अणु
		ASSERT(in_f->ilf_fields & XFS_ILOG_DBROOT);
		error = xfs_bmbt_change_owner(शून्य, ip, XFS_DATA_FORK,
					      ip->i_ino, buffer_list);
		अगर (error)
			जाओ out_मुक्त_ip;
	पूर्ण

	अगर (in_f->ilf_fields & XFS_ILOG_AOWNER) अणु
		ASSERT(in_f->ilf_fields & XFS_ILOG_ABROOT);
		error = xfs_bmbt_change_owner(शून्य, ip, XFS_ATTR_FORK,
					      ip->i_ino, buffer_list);
		अगर (error)
			जाओ out_मुक्त_ip;
	पूर्ण

out_मुक्त_ip:
	xfs_inode_मुक्त(ip);
	वापस error;
पूर्ण

अटल अंतरभूत bool xfs_log_dinode_has_bigसमय(स्थिर काष्ठा xfs_log_dinode *ld)
अणु
	वापस ld->di_version >= 3 &&
	       (ld->di_flags2 & XFS_DIFLAG2_BIGTIME);
पूर्ण

/* Convert a log बारtamp to an ondisk बारtamp. */
अटल अंतरभूत xfs_बारtamp_t
xfs_log_dinode_to_disk_ts(
	काष्ठा xfs_log_dinode		*from,
	स्थिर xfs_log_बारtamp_t	its)
अणु
	काष्ठा xfs_legacy_बारtamp	*lts;
	काष्ठा xfs_log_legacy_बारtamp	*lits;
	xfs_बारtamp_t			ts;

	अगर (xfs_log_dinode_has_bigसमय(from))
		वापस cpu_to_be64(its);

	lts = (काष्ठा xfs_legacy_बारtamp *)&ts;
	lits = (काष्ठा xfs_log_legacy_बारtamp *)&its;
	lts->t_sec = cpu_to_be32(lits->t_sec);
	lts->t_nsec = cpu_to_be32(lits->t_nsec);

	वापस ts;
पूर्ण

STATIC व्योम
xfs_log_dinode_to_disk(
	काष्ठा xfs_log_dinode	*from,
	काष्ठा xfs_dinode	*to)
अणु
	to->di_magic = cpu_to_be16(from->di_magic);
	to->di_mode = cpu_to_be16(from->di_mode);
	to->di_version = from->di_version;
	to->di_क्रमmat = from->di_क्रमmat;
	to->di_onlink = 0;
	to->di_uid = cpu_to_be32(from->di_uid);
	to->di_gid = cpu_to_be32(from->di_gid);
	to->di_nlink = cpu_to_be32(from->di_nlink);
	to->di_projid_lo = cpu_to_be16(from->di_projid_lo);
	to->di_projid_hi = cpu_to_be16(from->di_projid_hi);
	स_नकल(to->di_pad, from->di_pad, माप(to->di_pad));

	to->di_aसमय = xfs_log_dinode_to_disk_ts(from, from->di_aसमय);
	to->di_mसमय = xfs_log_dinode_to_disk_ts(from, from->di_mसमय);
	to->di_स_समय = xfs_log_dinode_to_disk_ts(from, from->di_स_समय);

	to->di_size = cpu_to_be64(from->di_size);
	to->di_nblocks = cpu_to_be64(from->di_nblocks);
	to->di_extsize = cpu_to_be32(from->di_extsize);
	to->di_nextents = cpu_to_be32(from->di_nextents);
	to->di_anextents = cpu_to_be16(from->di_anextents);
	to->di_विभाजनoff = from->di_विभाजनoff;
	to->di_aक्रमmat = from->di_aक्रमmat;
	to->di_dmevmask = cpu_to_be32(from->di_dmevmask);
	to->di_dmstate = cpu_to_be16(from->di_dmstate);
	to->di_flags = cpu_to_be16(from->di_flags);
	to->di_gen = cpu_to_be32(from->di_gen);

	अगर (from->di_version == 3) अणु
		to->di_changecount = cpu_to_be64(from->di_changecount);
		to->di_crसमय = xfs_log_dinode_to_disk_ts(from,
							  from->di_crसमय);
		to->di_flags2 = cpu_to_be64(from->di_flags2);
		to->di_cowextsize = cpu_to_be32(from->di_cowextsize);
		to->di_ino = cpu_to_be64(from->di_ino);
		to->di_lsn = cpu_to_be64(from->di_lsn);
		स_नकल(to->di_pad2, from->di_pad2, माप(to->di_pad2));
		uuid_copy(&to->di_uuid, &from->di_uuid);
		to->di_flushiter = 0;
	पूर्ण अन्यथा अणु
		to->di_flushiter = cpu_to_be16(from->di_flushiter);
	पूर्ण
पूर्ण

STATIC पूर्णांक
xlog_recover_inode_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			current_lsn)
अणु
	काष्ठा xfs_inode_log_क्रमmat	*in_f;
	काष्ठा xfs_mount		*mp = log->l_mp;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_dinode		*dip;
	पूर्णांक				len;
	अक्षर				*src;
	अक्षर				*dest;
	पूर्णांक				error;
	पूर्णांक				attr_index;
	uपूर्णांक				fields;
	काष्ठा xfs_log_dinode		*ldip;
	uपूर्णांक				isize;
	पूर्णांक				need_मुक्त = 0;

	अगर (item->ri_buf[0].i_len == माप(काष्ठा xfs_inode_log_क्रमmat)) अणु
		in_f = item->ri_buf[0].i_addr;
	पूर्ण अन्यथा अणु
		in_f = kmem_alloc(माप(काष्ठा xfs_inode_log_क्रमmat), 0);
		need_मुक्त = 1;
		error = xfs_inode_item_क्रमmat_convert(&item->ri_buf[0], in_f);
		अगर (error)
			जाओ error;
	पूर्ण

	/*
	 * Inode buffers can be मुक्तd, look out क्रम it,
	 * and करो not replay the inode.
	 */
	अगर (xlog_is_buffer_cancelled(log, in_f->ilf_blkno, in_f->ilf_len)) अणु
		error = 0;
		trace_xfs_log_recover_inode_cancel(log, in_f);
		जाओ error;
	पूर्ण
	trace_xfs_log_recover_inode_recover(log, in_f);

	error = xfs_buf_पढ़ो(mp->m_ddev_targp, in_f->ilf_blkno, in_f->ilf_len,
			0, &bp, &xfs_inode_buf_ops);
	अगर (error)
		जाओ error;
	ASSERT(in_f->ilf_fields & XFS_ILOG_CORE);
	dip = xfs_buf_offset(bp, in_f->ilf_boffset);

	/*
	 * Make sure the place we're flushing out to really looks
	 * like an inode!
	 */
	अगर (XFS_IS_CORRUPT(mp, !xfs_verअगरy_magic16(bp, dip->di_magic))) अणु
		xfs_alert(mp,
	"%s: Bad inode magic number, dip = "PTR_FMT", dino bp = "PTR_FMT", ino = %Ld",
			__func__, dip, bp, in_f->ilf_ino);
		error = -EFSCORRUPTED;
		जाओ out_release;
	पूर्ण
	ldip = item->ri_buf[1].i_addr;
	अगर (XFS_IS_CORRUPT(mp, ldip->di_magic != XFS_DINODE_MAGIC)) अणु
		xfs_alert(mp,
			"%s: Bad inode log record, rec ptr "PTR_FMT", ino %Ld",
			__func__, item, in_f->ilf_ino);
		error = -EFSCORRUPTED;
		जाओ out_release;
	पूर्ण

	/*
	 * If the inode has an LSN in it, recover the inode only अगर it's less
	 * than the lsn of the transaction we are replaying. Note: we still
	 * need to replay an owner change even though the inode is more recent
	 * than the transaction as there is no guarantee that all the btree
	 * blocks are more recent than this transaction, too.
	 */
	अगर (dip->di_version >= 3) अणु
		xfs_lsn_t	lsn = be64_to_cpu(dip->di_lsn);

		अगर (lsn && lsn != -1 && XFS_LSN_CMP(lsn, current_lsn) >= 0) अणु
			trace_xfs_log_recover_inode_skip(log, in_f);
			error = 0;
			जाओ out_owner_change;
		पूर्ण
	पूर्ण

	/*
	 * di_flushiter is only valid क्रम v1/2 inodes. All changes क्रम v3 inodes
	 * are transactional and अगर ordering is necessary we can determine that
	 * more accurately by the LSN field in the V3 inode core. Don't trust
	 * the inode versions we might be changing them here - use the
	 * superblock flag to determine whether we need to look at di_flushiter
	 * to skip replay when the on disk inode is newer than the log one
	 */
	अगर (!xfs_sb_version_has_v3inode(&mp->m_sb) &&
	    ldip->di_flushiter < be16_to_cpu(dip->di_flushiter)) अणु
		/*
		 * Deal with the wrap हाल, DI_MAX_FLUSH is less
		 * than smaller numbers
		 */
		अगर (be16_to_cpu(dip->di_flushiter) == DI_MAX_FLUSH &&
		    ldip->di_flushiter < (DI_MAX_FLUSH >> 1)) अणु
			/* करो nothing */
		पूर्ण अन्यथा अणु
			trace_xfs_log_recover_inode_skip(log, in_f);
			error = 0;
			जाओ out_release;
		पूर्ण
	पूर्ण

	/* Take the opportunity to reset the flush iteration count */
	ldip->di_flushiter = 0;

	अगर (unlikely(S_ISREG(ldip->di_mode))) अणु
		अगर ((ldip->di_क्रमmat != XFS_DINODE_FMT_EXTENTS) &&
		    (ldip->di_क्रमmat != XFS_DINODE_FMT_BTREE)) अणु
			XFS_CORRUPTION_ERROR("xlog_recover_inode_pass2(3)",
					 XFS_ERRLEVEL_LOW, mp, ldip,
					 माप(*ldip));
			xfs_alert(mp,
		"%s: Bad regular inode log record, rec ptr "PTR_FMT", "
		"ino ptr = "PTR_FMT", ino bp = "PTR_FMT", ino %Ld",
				__func__, item, dip, bp, in_f->ilf_ino);
			error = -EFSCORRUPTED;
			जाओ out_release;
		पूर्ण
	पूर्ण अन्यथा अगर (unlikely(S_ISसूची(ldip->di_mode))) अणु
		अगर ((ldip->di_क्रमmat != XFS_DINODE_FMT_EXTENTS) &&
		    (ldip->di_क्रमmat != XFS_DINODE_FMT_BTREE) &&
		    (ldip->di_क्रमmat != XFS_DINODE_FMT_LOCAL)) अणु
			XFS_CORRUPTION_ERROR("xlog_recover_inode_pass2(4)",
					     XFS_ERRLEVEL_LOW, mp, ldip,
					     माप(*ldip));
			xfs_alert(mp,
		"%s: Bad dir inode log record, rec ptr "PTR_FMT", "
		"ino ptr = "PTR_FMT", ino bp = "PTR_FMT", ino %Ld",
				__func__, item, dip, bp, in_f->ilf_ino);
			error = -EFSCORRUPTED;
			जाओ out_release;
		पूर्ण
	पूर्ण
	अगर (unlikely(ldip->di_nextents + ldip->di_anextents > ldip->di_nblocks))अणु
		XFS_CORRUPTION_ERROR("xlog_recover_inode_pass2(5)",
				     XFS_ERRLEVEL_LOW, mp, ldip,
				     माप(*ldip));
		xfs_alert(mp,
	"%s: Bad inode log record, rec ptr "PTR_FMT", dino ptr "PTR_FMT", "
	"dino bp "PTR_FMT", ino %Ld, total extents = %d, nblocks = %Ld",
			__func__, item, dip, bp, in_f->ilf_ino,
			ldip->di_nextents + ldip->di_anextents,
			ldip->di_nblocks);
		error = -EFSCORRUPTED;
		जाओ out_release;
	पूर्ण
	अगर (unlikely(ldip->di_विभाजनoff > mp->m_sb.sb_inodesize)) अणु
		XFS_CORRUPTION_ERROR("xlog_recover_inode_pass2(6)",
				     XFS_ERRLEVEL_LOW, mp, ldip,
				     माप(*ldip));
		xfs_alert(mp,
	"%s: Bad inode log record, rec ptr "PTR_FMT", dino ptr "PTR_FMT", "
	"dino bp "PTR_FMT", ino %Ld, forkoff 0x%x", __func__,
			item, dip, bp, in_f->ilf_ino, ldip->di_विभाजनoff);
		error = -EFSCORRUPTED;
		जाओ out_release;
	पूर्ण
	isize = xfs_log_dinode_size(mp);
	अगर (unlikely(item->ri_buf[1].i_len > isize)) अणु
		XFS_CORRUPTION_ERROR("xlog_recover_inode_pass2(7)",
				     XFS_ERRLEVEL_LOW, mp, ldip,
				     माप(*ldip));
		xfs_alert(mp,
			"%s: Bad inode log record length %d, rec ptr "PTR_FMT,
			__func__, item->ri_buf[1].i_len, item);
		error = -EFSCORRUPTED;
		जाओ out_release;
	पूर्ण

	/* recover the log dinode inode पूर्णांकo the on disk inode */
	xfs_log_dinode_to_disk(ldip, dip);

	fields = in_f->ilf_fields;
	अगर (fields & XFS_ILOG_DEV)
		xfs_dinode_put_rdev(dip, in_f->ilf_u.ilfu_rdev);

	अगर (in_f->ilf_size == 2)
		जाओ out_owner_change;
	len = item->ri_buf[2].i_len;
	src = item->ri_buf[2].i_addr;
	ASSERT(in_f->ilf_size <= 4);
	ASSERT((in_f->ilf_size == 3) || (fields & XFS_ILOG_AFORK));
	ASSERT(!(fields & XFS_ILOG_DFORK) ||
	       (len == in_f->ilf_dsize));

	चयन (fields & XFS_ILOG_DFORK) अणु
	हाल XFS_ILOG_DDATA:
	हाल XFS_ILOG_DEXT:
		स_नकल(XFS_DFORK_DPTR(dip), src, len);
		अवरोध;

	हाल XFS_ILOG_DBROOT:
		xfs_bmbt_to_bmdr(mp, (काष्ठा xfs_btree_block *)src, len,
				 (काष्ठा xfs_bmdr_block *)XFS_DFORK_DPTR(dip),
				 XFS_DFORK_DSIZE(dip, mp));
		अवरोध;

	शेष:
		/*
		 * There are no data विभाजन flags set.
		 */
		ASSERT((fields & XFS_ILOG_DFORK) == 0);
		अवरोध;
	पूर्ण

	/*
	 * If we logged any attribute data, recover it.  There may or
	 * may not have been any other non-core data logged in this
	 * transaction.
	 */
	अगर (in_f->ilf_fields & XFS_ILOG_AFORK) अणु
		अगर (in_f->ilf_fields & XFS_ILOG_DFORK) अणु
			attr_index = 3;
		पूर्ण अन्यथा अणु
			attr_index = 2;
		पूर्ण
		len = item->ri_buf[attr_index].i_len;
		src = item->ri_buf[attr_index].i_addr;
		ASSERT(len == in_f->ilf_asize);

		चयन (in_f->ilf_fields & XFS_ILOG_AFORK) अणु
		हाल XFS_ILOG_ADATA:
		हाल XFS_ILOG_AEXT:
			dest = XFS_DFORK_APTR(dip);
			ASSERT(len <= XFS_DFORK_ASIZE(dip, mp));
			स_नकल(dest, src, len);
			अवरोध;

		हाल XFS_ILOG_ABROOT:
			dest = XFS_DFORK_APTR(dip);
			xfs_bmbt_to_bmdr(mp, (काष्ठा xfs_btree_block *)src,
					 len, (काष्ठा xfs_bmdr_block *)dest,
					 XFS_DFORK_ASIZE(dip, mp));
			अवरोध;

		शेष:
			xfs_warn(log->l_mp, "%s: Invalid flag", __func__);
			ASSERT(0);
			error = -EFSCORRUPTED;
			जाओ out_release;
		पूर्ण
	पूर्ण

out_owner_change:
	/* Recover the swapext owner change unless inode has been deleted */
	अगर ((in_f->ilf_fields & (XFS_ILOG_DOWNER|XFS_ILOG_AOWNER)) &&
	    (dip->di_mode != 0))
		error = xfs_recover_inode_owner_change(mp, dip, in_f,
						       buffer_list);
	/* re-generate the checksum. */
	xfs_dinode_calc_crc(log->l_mp, dip);

	ASSERT(bp->b_mount == mp);
	bp->b_flags |= _XBF_LOGRECOVERY;
	xfs_buf_delwri_queue(bp, buffer_list);

out_release:
	xfs_buf_rअन्यथा(bp);
error:
	अगर (need_मुक्त)
		kmem_मुक्त(in_f);
	वापस error;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_inode_item_ops = अणु
	.item_type		= XFS_LI_INODE,
	.ra_pass2		= xlog_recover_inode_ra_pass2,
	.commit_pass2		= xlog_recover_inode_commit_pass2,
पूर्ण;
