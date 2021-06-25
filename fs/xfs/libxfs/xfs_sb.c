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
#समावेश "xfs_ialloc.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_alloc_btree.h"
#समावेश "xfs_log.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "xfs_refcount_btree.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_health.h"

/*
 * Physical superblock buffer manipulations. Shared with libxfs in userspace.
 */

/*
 * Reference counting access wrappers to the perag काष्ठाures.
 * Because we never मुक्त per-ag काष्ठाures, the only thing we
 * have to protect against changes is the tree काष्ठाure itself.
 */
काष्ठा xfs_perag *
xfs_perag_get(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		agno)
अणु
	काष्ठा xfs_perag	*pag;
	पूर्णांक			ref = 0;

	rcu_पढ़ो_lock();
	pag = radix_tree_lookup(&mp->m_perag_tree, agno);
	अगर (pag) अणु
		ASSERT(atomic_पढ़ो(&pag->pag_ref) >= 0);
		ref = atomic_inc_वापस(&pag->pag_ref);
	पूर्ण
	rcu_पढ़ो_unlock();
	trace_xfs_perag_get(mp, agno, ref, _RET_IP_);
	वापस pag;
पूर्ण

/*
 * search from @first to find the next perag with the given tag set.
 */
काष्ठा xfs_perag *
xfs_perag_get_tag(
	काष्ठा xfs_mount	*mp,
	xfs_agnumber_t		first,
	पूर्णांक			tag)
अणु
	काष्ठा xfs_perag	*pag;
	पूर्णांक			found;
	पूर्णांक			ref;

	rcu_पढ़ो_lock();
	found = radix_tree_gang_lookup_tag(&mp->m_perag_tree,
					(व्योम **)&pag, first, 1, tag);
	अगर (found <= 0) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण
	ref = atomic_inc_वापस(&pag->pag_ref);
	rcu_पढ़ो_unlock();
	trace_xfs_perag_get_tag(mp, pag->pag_agno, ref, _RET_IP_);
	वापस pag;
पूर्ण

व्योम
xfs_perag_put(
	काष्ठा xfs_perag	*pag)
अणु
	पूर्णांक	ref;

	ASSERT(atomic_पढ़ो(&pag->pag_ref) > 0);
	ref = atomic_dec_वापस(&pag->pag_ref);
	trace_xfs_perag_put(pag->pag_mount, pag->pag_agno, ref, _RET_IP_);
पूर्ण

/* Check all the superblock fields we care about when पढ़ोing one in. */
STATIC पूर्णांक
xfs_validate_sb_पढ़ो(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_sb		*sbp)
अणु
	अगर (XFS_SB_VERSION_NUM(sbp) != XFS_SB_VERSION_5)
		वापस 0;

	/*
	 * Version 5 superblock feature mask validation. Reject combinations
	 * the kernel cannot support up front beक्रमe checking anything अन्यथा.
	 */
	अगर (xfs_sb_has_compat_feature(sbp, XFS_SB_FEAT_COMPAT_UNKNOWN)) अणु
		xfs_warn(mp,
"Superblock has unknown compatible features (0x%x) enabled.",
			(sbp->sb_features_compat & XFS_SB_FEAT_COMPAT_UNKNOWN));
		xfs_warn(mp,
"Using a more recent kernel is recommended.");
	पूर्ण

	अगर (xfs_sb_has_ro_compat_feature(sbp, XFS_SB_FEAT_RO_COMPAT_UNKNOWN)) अणु
		xfs_alert(mp,
"Superblock has unknown read-only compatible features (0x%x) enabled.",
			(sbp->sb_features_ro_compat &
					XFS_SB_FEAT_RO_COMPAT_UNKNOWN));
		अगर (!(mp->m_flags & XFS_MOUNT_RDONLY)) अणु
			xfs_warn(mp,
"Attempted to mount read-only compatible filesystem read-write.");
			xfs_warn(mp,
"Filesystem can only be safely mounted read only.");

			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (xfs_sb_has_incompat_feature(sbp, XFS_SB_FEAT_INCOMPAT_UNKNOWN)) अणु
		xfs_warn(mp,
"Superblock has unknown incompatible features (0x%x) enabled.",
			(sbp->sb_features_incompat &
					XFS_SB_FEAT_INCOMPAT_UNKNOWN));
		xfs_warn(mp,
"Filesystem cannot be safely mounted by this kernel.");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Check all the superblock fields we care about when writing one out. */
STATIC पूर्णांक
xfs_validate_sb_ग_लिखो(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_sb		*sbp)
अणु
	/*
	 * Carry out additional sb summary counter sanity checks when we ग_लिखो
	 * the superblock.  We skip this in the पढ़ो validator because there
	 * could be newer superblocks in the log and अगर the values are garbage
	 * even after replay we'll recalculate them at the end of log mount.
	 *
	 * mkfs has traditionally written zeroed counters to inprogress and
	 * secondary superblocks, so allow this usage to जारी because
	 * we never पढ़ो counters from such superblocks.
	 */
	अगर (XFS_BUF_ADDR(bp) == XFS_SB_DADDR && !sbp->sb_inprogress &&
	    (sbp->sb_fdblocks > sbp->sb_dblocks ||
	     !xfs_verअगरy_icount(mp, sbp->sb_icount) ||
	     sbp->sb_अगरree > sbp->sb_icount)) अणु
		xfs_warn(mp, "SB summary counter sanity check failed");
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (XFS_SB_VERSION_NUM(sbp) != XFS_SB_VERSION_5)
		वापस 0;

	/*
	 * Version 5 superblock feature mask validation. Reject combinations
	 * the kernel cannot support since we checked क्रम unsupported bits in
	 * the पढ़ो verअगरier, which means that memory is corrupt.
	 */
	अगर (xfs_sb_has_compat_feature(sbp, XFS_SB_FEAT_COMPAT_UNKNOWN)) अणु
		xfs_warn(mp,
"Corruption detected in superblock compatible features (0x%x)!",
			(sbp->sb_features_compat & XFS_SB_FEAT_COMPAT_UNKNOWN));
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (xfs_sb_has_ro_compat_feature(sbp, XFS_SB_FEAT_RO_COMPAT_UNKNOWN)) अणु
		xfs_alert(mp,
"Corruption detected in superblock read-only compatible features (0x%x)!",
			(sbp->sb_features_ro_compat &
					XFS_SB_FEAT_RO_COMPAT_UNKNOWN));
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर (xfs_sb_has_incompat_feature(sbp, XFS_SB_FEAT_INCOMPAT_UNKNOWN)) अणु
		xfs_warn(mp,
"Corruption detected in superblock incompatible features (0x%x)!",
			(sbp->sb_features_incompat &
					XFS_SB_FEAT_INCOMPAT_UNKNOWN));
		वापस -EFSCORRUPTED;
	पूर्ण
	अगर (xfs_sb_has_incompat_log_feature(sbp,
			XFS_SB_FEAT_INCOMPAT_LOG_UNKNOWN)) अणु
		xfs_warn(mp,
"Corruption detected in superblock incompatible log features (0x%x)!",
			(sbp->sb_features_log_incompat &
					XFS_SB_FEAT_INCOMPAT_LOG_UNKNOWN));
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * We can't पढ़ो verअगरy the sb LSN because the पढ़ो verअगरier is called
	 * beक्रमe the log is allocated and processed. We know the log is set up
	 * beक्रमe ग_लिखो verअगरier calls, so check it here.
	 */
	अगर (!xfs_log_check_lsn(mp, sbp->sb_lsn))
		वापस -EFSCORRUPTED;

	वापस 0;
पूर्ण

/* Check the validity of the SB. */
STATIC पूर्णांक
xfs_validate_sb_common(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp,
	काष्ठा xfs_sb		*sbp)
अणु
	काष्ठा xfs_dsb		*dsb = bp->b_addr;
	uपूर्णांक32_t		agcount = 0;
	uपूर्णांक32_t		rem;

	अगर (!xfs_verअगरy_magic(bp, dsb->sb_magicnum)) अणु
		xfs_warn(mp, "bad magic number");
		वापस -EWRONGFS;
	पूर्ण

	अगर (!xfs_sb_good_version(sbp)) अणु
		xfs_warn(mp, "bad version");
		वापस -EWRONGFS;
	पूर्ण

	अगर (xfs_sb_version_has_pquotino(sbp)) अणु
		अगर (sbp->sb_qflags & (XFS_OQUOTA_ENFD | XFS_OQUOTA_CHKD)) अणु
			xfs_notice(mp,
			   "Version 5 of Super block has XFS_OQUOTA bits.");
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण अन्यथा अगर (sbp->sb_qflags & (XFS_PQUOTA_ENFD | XFS_GQUOTA_ENFD |
				XFS_PQUOTA_CHKD | XFS_GQUOTA_CHKD)) अणु
			xfs_notice(mp,
"Superblock earlier than Version 5 has XFS_{P|G}QUOTA_{ENFD|CHKD} bits.");
			वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Full inode chunks must be aligned to inode chunk size when
	 * sparse inodes are enabled to support the sparse chunk
	 * allocation algorithm and prevent overlapping inode records.
	 */
	अगर (xfs_sb_version_hassparseinodes(sbp)) अणु
		uपूर्णांक32_t	align;

		align = XFS_INODES_PER_CHUNK * sbp->sb_inodesize
				>> sbp->sb_blocklog;
		अगर (sbp->sb_inoalignmt != align) अणु
			xfs_warn(mp,
"Inode block alignment (%u) must match chunk size (%u) for sparse inodes.",
				 sbp->sb_inoalignmt, align);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (unlikely(
	    sbp->sb_logstart == 0 && mp->m_logdev_targp == mp->m_ddev_targp)) अणु
		xfs_warn(mp,
		"filesystem is marked as having an external log; "
		"specify logdev on the mount command line.");
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(
	    sbp->sb_logstart != 0 && mp->m_logdev_targp != mp->m_ddev_targp)) अणु
		xfs_warn(mp,
		"filesystem is marked as having an internal log; "
		"do not specify logdev on the mount command line.");
		वापस -EINVAL;
	पूर्ण

	/* Compute agcount क्रम this number of dblocks and agblocks */
	अगर (sbp->sb_agblocks) अणु
		agcount = भाग_u64_rem(sbp->sb_dblocks, sbp->sb_agblocks, &rem);
		अगर (rem)
			agcount++;
	पूर्ण

	/*
	 * More sanity checking.  Most of these were stolen directly from
	 * xfs_repair.
	 */
	अगर (unlikely(
	    sbp->sb_agcount <= 0					||
	    sbp->sb_sectsize < XFS_MIN_SECTORSIZE			||
	    sbp->sb_sectsize > XFS_MAX_SECTORSIZE			||
	    sbp->sb_sectlog < XFS_MIN_SECTORSIZE_LOG			||
	    sbp->sb_sectlog > XFS_MAX_SECTORSIZE_LOG			||
	    sbp->sb_sectsize != (1 << sbp->sb_sectlog)			||
	    sbp->sb_blocksize < XFS_MIN_BLOCKSIZE			||
	    sbp->sb_blocksize > XFS_MAX_BLOCKSIZE			||
	    sbp->sb_blocklog < XFS_MIN_BLOCKSIZE_LOG			||
	    sbp->sb_blocklog > XFS_MAX_BLOCKSIZE_LOG			||
	    sbp->sb_blocksize != (1 << sbp->sb_blocklog)		||
	    sbp->sb_dirblklog + sbp->sb_blocklog > XFS_MAX_BLOCKSIZE_LOG ||
	    sbp->sb_inodesize < XFS_DINODE_MIN_SIZE			||
	    sbp->sb_inodesize > XFS_DINODE_MAX_SIZE			||
	    sbp->sb_inodelog < XFS_DINODE_MIN_LOG			||
	    sbp->sb_inodelog > XFS_DINODE_MAX_LOG			||
	    sbp->sb_inodesize != (1 << sbp->sb_inodelog)		||
	    sbp->sb_logsunit > XLOG_MAX_RECORD_BSIZE			||
	    sbp->sb_inopblock != howmany(sbp->sb_blocksize,sbp->sb_inodesize) ||
	    XFS_FSB_TO_B(mp, sbp->sb_agblocks) < XFS_MIN_AG_BYTES	||
	    XFS_FSB_TO_B(mp, sbp->sb_agblocks) > XFS_MAX_AG_BYTES	||
	    sbp->sb_agblklog != xfs_highbit32(sbp->sb_agblocks - 1) + 1	||
	    agcount == 0 || agcount != sbp->sb_agcount			||
	    (sbp->sb_blocklog - sbp->sb_inodelog != sbp->sb_inopblog)	||
	    (sbp->sb_rextsize * sbp->sb_blocksize > XFS_MAX_RTEXTSIZE)	||
	    (sbp->sb_rextsize * sbp->sb_blocksize < XFS_MIN_RTEXTSIZE)	||
	    (sbp->sb_imax_pct > 100 /* zero sb_imax_pct is valid */)	||
	    sbp->sb_dblocks == 0					||
	    sbp->sb_dblocks > XFS_MAX_DBLOCKS(sbp)			||
	    sbp->sb_dblocks < XFS_MIN_DBLOCKS(sbp)			||
	    sbp->sb_shared_vn != 0)) अणु
		xfs_notice(mp, "SB sanity check failed");
		वापस -EFSCORRUPTED;
	पूर्ण

	/* Validate the realसमय geometry; stolen from xfs_repair */
	अगर (sbp->sb_rextsize * sbp->sb_blocksize > XFS_MAX_RTEXTSIZE ||
	    sbp->sb_rextsize * sbp->sb_blocksize < XFS_MIN_RTEXTSIZE) अणु
		xfs_notice(mp,
			"realtime extent sanity check failed");
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (sbp->sb_rblocks == 0) अणु
		अगर (sbp->sb_rextents != 0 || sbp->sb_rbmblocks != 0 ||
		    sbp->sb_rextslog != 0 || sbp->sb_frextents != 0) अणु
			xfs_notice(mp,
				"realtime zeroed geometry check failed");
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण अन्यथा अणु
		uपूर्णांक64_t	rexts;
		uपूर्णांक64_t	rbmblocks;

		rexts = भाग_u64(sbp->sb_rblocks, sbp->sb_rextsize);
		rbmblocks = howmany_64(sbp->sb_rextents,
				       NBBY * sbp->sb_blocksize);

		अगर (sbp->sb_rextents != rexts ||
		    sbp->sb_rextslog != xfs_highbit32(sbp->sb_rextents) ||
		    sbp->sb_rbmblocks != rbmblocks) अणु
			xfs_notice(mp,
				"realtime geometry sanity check failed");
			वापस -EFSCORRUPTED;
		पूर्ण
	पूर्ण

	/*
	 * Either (sb_unit and !hasdalign) or (!sb_unit and hasdalign)
	 * would imply the image is corrupted.
	 */
	अगर (!!sbp->sb_unit ^ xfs_sb_version_hasdalign(sbp)) अणु
		xfs_notice(mp, "SB stripe alignment sanity check failed");
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (!xfs_validate_stripe_geometry(mp, XFS_FSB_TO_B(mp, sbp->sb_unit),
			XFS_FSB_TO_B(mp, sbp->sb_width), 0, false))
		वापस -EFSCORRUPTED;

	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	    sbp->sb_blocksize < XFS_MIN_CRC_BLOCKSIZE) अणु
		xfs_notice(mp, "v5 SB sanity check failed");
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Currently only very few inode sizes are supported.
	 */
	चयन (sbp->sb_inodesize) अणु
	हाल 256:
	हाल 512:
	हाल 1024:
	हाल 2048:
		अवरोध;
	शेष:
		xfs_warn(mp, "inode size of %d bytes not supported",
				sbp->sb_inodesize);
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
xfs_sb_quota_from_disk(काष्ठा xfs_sb *sbp)
अणु
	/*
	 * older mkfs करोesn't initialize quota inodes to शून्यFSINO. This
	 * leads to in-core values having two dअगरferent values क्रम a quota
	 * inode to be invalid: 0 and शून्यFSINO. Change it to a single value
	 * शून्यFSINO.
	 *
	 * Note that this change affect only the in-core values. These
	 * values are not written back to disk unless any quota inक्रमmation
	 * is written to the disk. Even in that हाल, sb_pquotino field is
	 * not written to disk unless the superblock supports pquotino.
	 */
	अगर (sbp->sb_uquotino == 0)
		sbp->sb_uquotino = शून्यFSINO;
	अगर (sbp->sb_gquotino == 0)
		sbp->sb_gquotino = शून्यFSINO;
	अगर (sbp->sb_pquotino == 0)
		sbp->sb_pquotino = शून्यFSINO;

	/*
	 * We need to करो these manipilations only अगर we are working
	 * with an older version of on-disk superblock.
	 */
	अगर (xfs_sb_version_has_pquotino(sbp))
		वापस;

	अगर (sbp->sb_qflags & XFS_OQUOTA_ENFD)
		sbp->sb_qflags |= (sbp->sb_qflags & XFS_PQUOTA_ACCT) ?
					XFS_PQUOTA_ENFD : XFS_GQUOTA_ENFD;
	अगर (sbp->sb_qflags & XFS_OQUOTA_CHKD)
		sbp->sb_qflags |= (sbp->sb_qflags & XFS_PQUOTA_ACCT) ?
					XFS_PQUOTA_CHKD : XFS_GQUOTA_CHKD;
	sbp->sb_qflags &= ~(XFS_OQUOTA_ENFD | XFS_OQUOTA_CHKD);

	अगर (sbp->sb_qflags & XFS_PQUOTA_ACCT &&
	    sbp->sb_gquotino != शून्यFSINO)  अणु
		/*
		 * In older version of superblock, on-disk superblock only
		 * has sb_gquotino, and in-core superblock has both sb_gquotino
		 * and sb_pquotino. But, only one of them is supported at any
		 * poपूर्णांक of समय. So, अगर PQUOTA is set in disk superblock,
		 * copy over sb_gquotino to sb_pquotino.  The शून्यFSINO test
		 * above is to make sure we करोn't करो this twice and wipe them
		 * both out!
		 */
		sbp->sb_pquotino = sbp->sb_gquotino;
		sbp->sb_gquotino = शून्यFSINO;
	पूर्ण
पूर्ण

अटल व्योम
__xfs_sb_from_disk(
	काष्ठा xfs_sb	*to,
	xfs_dsb_t	*from,
	bool		convert_xquota)
अणु
	to->sb_magicnum = be32_to_cpu(from->sb_magicnum);
	to->sb_blocksize = be32_to_cpu(from->sb_blocksize);
	to->sb_dblocks = be64_to_cpu(from->sb_dblocks);
	to->sb_rblocks = be64_to_cpu(from->sb_rblocks);
	to->sb_rextents = be64_to_cpu(from->sb_rextents);
	स_नकल(&to->sb_uuid, &from->sb_uuid, माप(to->sb_uuid));
	to->sb_logstart = be64_to_cpu(from->sb_logstart);
	to->sb_rootino = be64_to_cpu(from->sb_rootino);
	to->sb_rbmino = be64_to_cpu(from->sb_rbmino);
	to->sb_rsumino = be64_to_cpu(from->sb_rsumino);
	to->sb_rextsize = be32_to_cpu(from->sb_rextsize);
	to->sb_agblocks = be32_to_cpu(from->sb_agblocks);
	to->sb_agcount = be32_to_cpu(from->sb_agcount);
	to->sb_rbmblocks = be32_to_cpu(from->sb_rbmblocks);
	to->sb_logblocks = be32_to_cpu(from->sb_logblocks);
	to->sb_versionnum = be16_to_cpu(from->sb_versionnum);
	to->sb_sectsize = be16_to_cpu(from->sb_sectsize);
	to->sb_inodesize = be16_to_cpu(from->sb_inodesize);
	to->sb_inopblock = be16_to_cpu(from->sb_inopblock);
	स_नकल(&to->sb_fname, &from->sb_fname, माप(to->sb_fname));
	to->sb_blocklog = from->sb_blocklog;
	to->sb_sectlog = from->sb_sectlog;
	to->sb_inodelog = from->sb_inodelog;
	to->sb_inopblog = from->sb_inopblog;
	to->sb_agblklog = from->sb_agblklog;
	to->sb_rextslog = from->sb_rextslog;
	to->sb_inprogress = from->sb_inprogress;
	to->sb_imax_pct = from->sb_imax_pct;
	to->sb_icount = be64_to_cpu(from->sb_icount);
	to->sb_अगरree = be64_to_cpu(from->sb_अगरree);
	to->sb_fdblocks = be64_to_cpu(from->sb_fdblocks);
	to->sb_frextents = be64_to_cpu(from->sb_frextents);
	to->sb_uquotino = be64_to_cpu(from->sb_uquotino);
	to->sb_gquotino = be64_to_cpu(from->sb_gquotino);
	to->sb_qflags = be16_to_cpu(from->sb_qflags);
	to->sb_flags = from->sb_flags;
	to->sb_shared_vn = from->sb_shared_vn;
	to->sb_inoalignmt = be32_to_cpu(from->sb_inoalignmt);
	to->sb_unit = be32_to_cpu(from->sb_unit);
	to->sb_width = be32_to_cpu(from->sb_width);
	to->sb_dirblklog = from->sb_dirblklog;
	to->sb_logsectlog = from->sb_logsectlog;
	to->sb_logsectsize = be16_to_cpu(from->sb_logsectsize);
	to->sb_logsunit = be32_to_cpu(from->sb_logsunit);
	to->sb_features2 = be32_to_cpu(from->sb_features2);
	to->sb_bad_features2 = be32_to_cpu(from->sb_bad_features2);
	to->sb_features_compat = be32_to_cpu(from->sb_features_compat);
	to->sb_features_ro_compat = be32_to_cpu(from->sb_features_ro_compat);
	to->sb_features_incompat = be32_to_cpu(from->sb_features_incompat);
	to->sb_features_log_incompat =
				be32_to_cpu(from->sb_features_log_incompat);
	/* crc is only used on disk, not in memory; just init to 0 here. */
	to->sb_crc = 0;
	to->sb_spino_align = be32_to_cpu(from->sb_spino_align);
	to->sb_pquotino = be64_to_cpu(from->sb_pquotino);
	to->sb_lsn = be64_to_cpu(from->sb_lsn);
	/*
	 * sb_meta_uuid is only on disk अगर it dअगरfers from sb_uuid and the
	 * feature flag is set; अगर not set we keep it only in memory.
	 */
	अगर (xfs_sb_version_hयंत्रetauuid(to))
		uuid_copy(&to->sb_meta_uuid, &from->sb_meta_uuid);
	अन्यथा
		uuid_copy(&to->sb_meta_uuid, &from->sb_uuid);
	/* Convert on-disk flags to in-memory flags? */
	अगर (convert_xquota)
		xfs_sb_quota_from_disk(to);
पूर्ण

व्योम
xfs_sb_from_disk(
	काष्ठा xfs_sb	*to,
	xfs_dsb_t	*from)
अणु
	__xfs_sb_from_disk(to, from, true);
पूर्ण

अटल व्योम
xfs_sb_quota_to_disk(
	काष्ठा xfs_dsb	*to,
	काष्ठा xfs_sb	*from)
अणु
	uपूर्णांक16_t	qflags = from->sb_qflags;

	to->sb_uquotino = cpu_to_be64(from->sb_uquotino);
	अगर (xfs_sb_version_has_pquotino(from)) अणु
		to->sb_qflags = cpu_to_be16(from->sb_qflags);
		to->sb_gquotino = cpu_to_be64(from->sb_gquotino);
		to->sb_pquotino = cpu_to_be64(from->sb_pquotino);
		वापस;
	पूर्ण

	/*
	 * The in-core version of sb_qflags करो not have XFS_OQUOTA_*
	 * flags, whereas the on-disk version करोes.  So, convert incore
	 * XFS_अणुPGपूर्णQUOTA_* flags to on-disk XFS_OQUOTA_* flags.
	 */
	qflags &= ~(XFS_PQUOTA_ENFD | XFS_PQUOTA_CHKD |
			XFS_GQUOTA_ENFD | XFS_GQUOTA_CHKD);

	अगर (from->sb_qflags &
			(XFS_PQUOTA_ENFD | XFS_GQUOTA_ENFD))
		qflags |= XFS_OQUOTA_ENFD;
	अगर (from->sb_qflags &
			(XFS_PQUOTA_CHKD | XFS_GQUOTA_CHKD))
		qflags |= XFS_OQUOTA_CHKD;
	to->sb_qflags = cpu_to_be16(qflags);

	/*
	 * GQUOTINO and PQUOTINO cannot be used together in versions
	 * of superblock that करो not have pquotino. from->sb_flags
	 * tells us which quota is active and should be copied to
	 * disk. If neither are active, we should शून्य the inode.
	 *
	 * In all हालs, the separate pquotino must reमुख्य 0 because it
	 * is beyond the "end" of the valid non-pquotino superblock.
	 */
	अगर (from->sb_qflags & XFS_GQUOTA_ACCT)
		to->sb_gquotino = cpu_to_be64(from->sb_gquotino);
	अन्यथा अगर (from->sb_qflags & XFS_PQUOTA_ACCT)
		to->sb_gquotino = cpu_to_be64(from->sb_pquotino);
	अन्यथा अणु
		/*
		 * We can't rely on just the fields being logged to tell us
		 * that it is safe to ग_लिखो शून्यFSINO - we should only करो that
		 * अगर quotas are not actually enabled. Hence only ग_लिखो
		 * शून्यFSINO अगर both in-core quota inodes are शून्य.
		 */
		अगर (from->sb_gquotino == शून्यFSINO &&
		    from->sb_pquotino == शून्यFSINO)
			to->sb_gquotino = cpu_to_be64(शून्यFSINO);
	पूर्ण

	to->sb_pquotino = 0;
पूर्ण

व्योम
xfs_sb_to_disk(
	काष्ठा xfs_dsb	*to,
	काष्ठा xfs_sb	*from)
अणु
	xfs_sb_quota_to_disk(to, from);

	to->sb_magicnum = cpu_to_be32(from->sb_magicnum);
	to->sb_blocksize = cpu_to_be32(from->sb_blocksize);
	to->sb_dblocks = cpu_to_be64(from->sb_dblocks);
	to->sb_rblocks = cpu_to_be64(from->sb_rblocks);
	to->sb_rextents = cpu_to_be64(from->sb_rextents);
	स_नकल(&to->sb_uuid, &from->sb_uuid, माप(to->sb_uuid));
	to->sb_logstart = cpu_to_be64(from->sb_logstart);
	to->sb_rootino = cpu_to_be64(from->sb_rootino);
	to->sb_rbmino = cpu_to_be64(from->sb_rbmino);
	to->sb_rsumino = cpu_to_be64(from->sb_rsumino);
	to->sb_rextsize = cpu_to_be32(from->sb_rextsize);
	to->sb_agblocks = cpu_to_be32(from->sb_agblocks);
	to->sb_agcount = cpu_to_be32(from->sb_agcount);
	to->sb_rbmblocks = cpu_to_be32(from->sb_rbmblocks);
	to->sb_logblocks = cpu_to_be32(from->sb_logblocks);
	to->sb_versionnum = cpu_to_be16(from->sb_versionnum);
	to->sb_sectsize = cpu_to_be16(from->sb_sectsize);
	to->sb_inodesize = cpu_to_be16(from->sb_inodesize);
	to->sb_inopblock = cpu_to_be16(from->sb_inopblock);
	स_नकल(&to->sb_fname, &from->sb_fname, माप(to->sb_fname));
	to->sb_blocklog = from->sb_blocklog;
	to->sb_sectlog = from->sb_sectlog;
	to->sb_inodelog = from->sb_inodelog;
	to->sb_inopblog = from->sb_inopblog;
	to->sb_agblklog = from->sb_agblklog;
	to->sb_rextslog = from->sb_rextslog;
	to->sb_inprogress = from->sb_inprogress;
	to->sb_imax_pct = from->sb_imax_pct;
	to->sb_icount = cpu_to_be64(from->sb_icount);
	to->sb_अगरree = cpu_to_be64(from->sb_अगरree);
	to->sb_fdblocks = cpu_to_be64(from->sb_fdblocks);
	to->sb_frextents = cpu_to_be64(from->sb_frextents);

	to->sb_flags = from->sb_flags;
	to->sb_shared_vn = from->sb_shared_vn;
	to->sb_inoalignmt = cpu_to_be32(from->sb_inoalignmt);
	to->sb_unit = cpu_to_be32(from->sb_unit);
	to->sb_width = cpu_to_be32(from->sb_width);
	to->sb_dirblklog = from->sb_dirblklog;
	to->sb_logsectlog = from->sb_logsectlog;
	to->sb_logsectsize = cpu_to_be16(from->sb_logsectsize);
	to->sb_logsunit = cpu_to_be32(from->sb_logsunit);

	/*
	 * We need to ensure that bad_features2 always matches features2.
	 * Hence we enक्रमce that here rather than having to remember to करो it
	 * everywhere अन्यथा that updates features2.
	 */
	from->sb_bad_features2 = from->sb_features2;
	to->sb_features2 = cpu_to_be32(from->sb_features2);
	to->sb_bad_features2 = cpu_to_be32(from->sb_bad_features2);

	अगर (xfs_sb_version_hascrc(from)) अणु
		to->sb_features_compat = cpu_to_be32(from->sb_features_compat);
		to->sb_features_ro_compat =
				cpu_to_be32(from->sb_features_ro_compat);
		to->sb_features_incompat =
				cpu_to_be32(from->sb_features_incompat);
		to->sb_features_log_incompat =
				cpu_to_be32(from->sb_features_log_incompat);
		to->sb_spino_align = cpu_to_be32(from->sb_spino_align);
		to->sb_lsn = cpu_to_be64(from->sb_lsn);
		अगर (xfs_sb_version_hयंत्रetauuid(from))
			uuid_copy(&to->sb_meta_uuid, &from->sb_meta_uuid);
	पूर्ण
पूर्ण

/*
 * If the superblock has the CRC feature bit set or the CRC field is non-null,
 * check that the CRC is valid.  We check the CRC field is non-null because a
 * single bit error could clear the feature bit and unused parts of the
 * superblock are supposed to be zero. Hence a non-null crc field indicates that
 * we've potentially lost a feature bit and we should check it anyway.
 *
 * However, past bugs (i.e. in growfs) left non-zeroed regions beyond the
 * last field in V4 secondary superblocks.  So क्रम secondary superblocks,
 * we are more क्रमgiving, and ignore CRC failures अगर the primary करोesn't
 * indicate that the fs version is V5.
 */
अटल व्योम
xfs_sb_पढ़ो_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_sb		sb;
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_dsb		*dsb = bp->b_addr;
	पूर्णांक			error;

	/*
	 * खोलो code the version check to aव्योम needing to convert the entire
	 * superblock from disk order just to check the version number
	 */
	अगर (dsb->sb_magicnum == cpu_to_be32(XFS_SB_MAGIC) &&
	    (((be16_to_cpu(dsb->sb_versionnum) & XFS_SB_VERSION_NUMBITS) ==
						XFS_SB_VERSION_5) ||
	     dsb->sb_crc != 0)) अणु

		अगर (!xfs_buf_verअगरy_cksum(bp, XFS_SB_CRC_OFF)) अणु
			/* Only fail bad secondaries on a known V5 fileप्रणाली */
			अगर (bp->b_bn == XFS_SB_DADDR ||
			    xfs_sb_version_hascrc(&mp->m_sb)) अणु
				error = -EFSBADCRC;
				जाओ out_error;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Check all the superblock fields.  Don't byteswap the xquota flags
	 * because _verअगरy_common checks the on-disk values.
	 */
	__xfs_sb_from_disk(&sb, dsb, false);
	error = xfs_validate_sb_common(mp, bp, &sb);
	अगर (error)
		जाओ out_error;
	error = xfs_validate_sb_पढ़ो(mp, &sb);

out_error:
	अगर (error == -EFSCORRUPTED || error == -EFSBADCRC)
		xfs_verअगरier_error(bp, error, __this_address);
	अन्यथा अगर (error)
		xfs_buf_ioerror(bp, error);
पूर्ण

/*
 * We may be probed क्रम a fileप्रणाली match, so we may not want to emit
 * messages when the superblock buffer is not actually an XFS superblock.
 * If we find an XFS superblock, then run a normal, noisy mount because we are
 * really going to mount it and want to know about errors.
 */
अटल व्योम
xfs_sb_quiet_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_dsb	*dsb = bp->b_addr;

	अगर (dsb->sb_magicnum == cpu_to_be32(XFS_SB_MAGIC)) अणु
		/* XFS fileप्रणाली, verअगरy noisily! */
		xfs_sb_पढ़ो_verअगरy(bp);
		वापस;
	पूर्ण
	/* quietly fail */
	xfs_buf_ioerror(bp, -EWRONGFS);
पूर्ण

अटल व्योम
xfs_sb_ग_लिखो_verअगरy(
	काष्ठा xfs_buf		*bp)
अणु
	काष्ठा xfs_sb		sb;
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	काष्ठा xfs_dsb		*dsb = bp->b_addr;
	पूर्णांक			error;

	/*
	 * Check all the superblock fields.  Don't byteswap the xquota flags
	 * because _verअगरy_common checks the on-disk values.
	 */
	__xfs_sb_from_disk(&sb, dsb, false);
	error = xfs_validate_sb_common(mp, bp, &sb);
	अगर (error)
		जाओ out_error;
	error = xfs_validate_sb_ग_लिखो(mp, bp, &sb);
	अगर (error)
		जाओ out_error;

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (bip)
		dsb->sb_lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_SB_CRC_OFF);
	वापस;

out_error:
	xfs_verअगरier_error(bp, error, __this_address);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_sb_buf_ops = अणु
	.name = "xfs_sb",
	.magic = अणु cpu_to_be32(XFS_SB_MAGIC), cpu_to_be32(XFS_SB_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_sb_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_sb_ग_लिखो_verअगरy,
पूर्ण;

स्थिर काष्ठा xfs_buf_ops xfs_sb_quiet_buf_ops = अणु
	.name = "xfs_sb_quiet",
	.magic = अणु cpu_to_be32(XFS_SB_MAGIC), cpu_to_be32(XFS_SB_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_sb_quiet_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_sb_ग_लिखो_verअगरy,
पूर्ण;

/*
 * xfs_mount_common
 *
 * Mount initialization code establishing various mount
 * fields from the superblock associated with the given
 * mount काष्ठाure.
 *
 * Inode geometry are calculated in xfs_ialloc_setup_geometry.
 */
व्योम
xfs_sb_mount_common(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_sb		*sbp)
अणु
	mp->m_agfrotor = mp->m_agirotor = 0;
	mp->m_maxagi = mp->m_sb.sb_agcount;
	mp->m_blkbit_log = sbp->sb_blocklog + XFS_NBBYLOG;
	mp->m_blkbb_log = sbp->sb_blocklog - BBSHIFT;
	mp->m_sectbb_log = sbp->sb_sectlog - BBSHIFT;
	mp->m_agno_log = xfs_highbit32(sbp->sb_agcount - 1) + 1;
	mp->m_blockmask = sbp->sb_blocksize - 1;
	mp->m_blockwsize = sbp->sb_blocksize >> XFS_WORDLOG;
	mp->m_blockwmask = mp->m_blockwsize - 1;

	mp->m_alloc_mxr[0] = xfs_allocbt_maxrecs(mp, sbp->sb_blocksize, 1);
	mp->m_alloc_mxr[1] = xfs_allocbt_maxrecs(mp, sbp->sb_blocksize, 0);
	mp->m_alloc_mnr[0] = mp->m_alloc_mxr[0] / 2;
	mp->m_alloc_mnr[1] = mp->m_alloc_mxr[1] / 2;

	mp->m_bmap_dmxr[0] = xfs_bmbt_maxrecs(mp, sbp->sb_blocksize, 1);
	mp->m_bmap_dmxr[1] = xfs_bmbt_maxrecs(mp, sbp->sb_blocksize, 0);
	mp->m_bmap_dmnr[0] = mp->m_bmap_dmxr[0] / 2;
	mp->m_bmap_dmnr[1] = mp->m_bmap_dmxr[1] / 2;

	mp->m_rmap_mxr[0] = xfs_rmapbt_maxrecs(sbp->sb_blocksize, 1);
	mp->m_rmap_mxr[1] = xfs_rmapbt_maxrecs(sbp->sb_blocksize, 0);
	mp->m_rmap_mnr[0] = mp->m_rmap_mxr[0] / 2;
	mp->m_rmap_mnr[1] = mp->m_rmap_mxr[1] / 2;

	mp->m_refc_mxr[0] = xfs_refcountbt_maxrecs(sbp->sb_blocksize, true);
	mp->m_refc_mxr[1] = xfs_refcountbt_maxrecs(sbp->sb_blocksize, false);
	mp->m_refc_mnr[0] = mp->m_refc_mxr[0] / 2;
	mp->m_refc_mnr[1] = mp->m_refc_mxr[1] / 2;

	mp->m_bsize = XFS_FSB_TO_BB(mp, 1);
	mp->m_alloc_set_aside = xfs_alloc_set_aside(mp);
	mp->m_ag_max_usable = xfs_alloc_ag_max_usable(mp);
पूर्ण

/*
 * xfs_initialize_perag_data
 *
 * Read in each per-ag काष्ठाure so we can count up the number of
 * allocated inodes, मुक्त inodes and used fileप्रणाली blocks as this
 * inक्रमmation is no दीर्घer persistent in the superblock. Once we have
 * this inक्रमmation, ग_लिखो it पूर्णांकo the in-core superblock काष्ठाure.
 */
पूर्णांक
xfs_initialize_perag_data(
	काष्ठा xfs_mount *mp,
	xfs_agnumber_t	agcount)
अणु
	xfs_agnumber_t	index;
	xfs_perag_t	*pag;
	xfs_sb_t	*sbp = &mp->m_sb;
	uपूर्णांक64_t	अगरree = 0;
	uपूर्णांक64_t	ialloc = 0;
	uपूर्णांक64_t	bमुक्त = 0;
	uपूर्णांक64_t	bमुक्तlst = 0;
	uपूर्णांक64_t	btree = 0;
	uपूर्णांक64_t	fdblocks;
	पूर्णांक		error = 0;

	क्रम (index = 0; index < agcount; index++) अणु
		/*
		 * पढ़ो the agf, then the agi. This माला_लो us
		 * all the inक्रमmation we need and populates the
		 * per-ag काष्ठाures क्रम us.
		 */
		error = xfs_alloc_pagf_init(mp, शून्य, index, 0);
		अगर (error)
			वापस error;

		error = xfs_ialloc_pagi_init(mp, शून्य, index);
		अगर (error)
			वापस error;
		pag = xfs_perag_get(mp, index);
		अगरree += pag->pagi_मुक्तcount;
		ialloc += pag->pagi_count;
		bमुक्त += pag->pagf_मुक्तblks;
		bमुक्तlst += pag->pagf_flcount;
		btree += pag->pagf_btreeblks;
		xfs_perag_put(pag);
	पूर्ण
	fdblocks = bमुक्त + bमुक्तlst + btree;

	/*
	 * If the new summary counts are obviously incorrect, fail the
	 * mount operation because that implies the AGFs are also corrupt.
	 * Clear FS_COUNTERS so that we करोn't unmount with a dirty log, which
	 * will prevent xfs_repair from fixing anything.
	 */
	अगर (fdblocks > sbp->sb_dblocks || अगरree > ialloc) अणु
		xfs_alert(mp, "AGF corruption. Please run xfs_repair.");
		error = -EFSCORRUPTED;
		जाओ out;
	पूर्ण

	/* Overग_लिखो incore superblock counters with just-पढ़ो data */
	spin_lock(&mp->m_sb_lock);
	sbp->sb_अगरree = अगरree;
	sbp->sb_icount = ialloc;
	sbp->sb_fdblocks = fdblocks;
	spin_unlock(&mp->m_sb_lock);

	xfs_reinit_percpu_counters(mp);
out:
	xfs_fs_mark_healthy(mp, XFS_SICK_FS_COUNTERS);
	वापस error;
पूर्ण

/*
 * xfs_log_sb() can be used to copy arbitrary changes to the in-core superblock
 * पूर्णांकo the superblock buffer to be logged.  It करोes not provide the higher
 * level of locking that is needed to protect the in-core superblock from
 * concurrent access.
 */
व्योम
xfs_log_sb(
	काष्ठा xfs_trans	*tp)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_buf		*bp = xfs_trans_माला_लोb(tp);

	/*
	 * Lazy sb counters करोn't update the in-core superblock so करो that now.
	 * If this is at unmount, the counters will be exactly correct, but at
	 * any other समय they will only be ballpark correct because of
	 * reservations that have been taken out percpu counters. If we have an
	 * unclean shutकरोwn, this will be corrected by log recovery rebuilding
	 * the counters from the AGF block counts.
	 */
	अगर (xfs_sb_version_haslazysbcount(&mp->m_sb)) अणु
		mp->m_sb.sb_icount = percpu_counter_sum(&mp->m_icount);
		mp->m_sb.sb_अगरree = percpu_counter_sum(&mp->m_अगरree);
		mp->m_sb.sb_fdblocks = percpu_counter_sum(&mp->m_fdblocks);
	पूर्ण

	xfs_sb_to_disk(bp->b_addr, &mp->m_sb);
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_SB_BUF);
	xfs_trans_log_buf(tp, bp, 0, माप(काष्ठा xfs_dsb) - 1);
पूर्ण

/*
 * xfs_sync_sb
 *
 * Sync the superblock to disk.
 *
 * Note that the caller is responsible क्रम checking the frozen state of the
 * fileप्रणाली. This procedure uses the non-blocking transaction allocator and
 * thus will allow modअगरications to a frozen fs. This is required because this
 * code can be called during the process of मुक्तzing where use of the high-level
 * allocator would deadlock.
 */
पूर्णांक
xfs_sync_sb(
	काष्ठा xfs_mount	*mp,
	bool			रुको)
अणु
	काष्ठा xfs_trans	*tp;
	पूर्णांक			error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_sb, 0, 0,
			XFS_TRANS_NO_WRITECOUNT, &tp);
	अगर (error)
		वापस error;

	xfs_log_sb(tp);
	अगर (रुको)
		xfs_trans_set_sync(tp);
	वापस xfs_trans_commit(tp);
पूर्ण

/*
 * Update all the secondary superblocks to match the new state of the primary.
 * Because we are completely overwriting all the existing fields in the
 * secondary superblock buffers, there is no need to पढ़ो them in from disk.
 * Just get a new buffer, stamp it and ग_लिखो it.
 *
 * The sb buffers need to be cached here so that we serialise against other
 * operations that access the secondary superblocks, but we करोn't want to keep
 * them in memory once it is written so we mark it as a one-shot buffer.
 */
पूर्णांक
xfs_update_secondary_sbs(
	काष्ठा xfs_mount	*mp)
अणु
	xfs_agnumber_t		agno;
	पूर्णांक			saved_error = 0;
	पूर्णांक			error = 0;
	LIST_HEAD		(buffer_list);

	/* update secondary superblocks. */
	क्रम (agno = 1; agno < mp->m_sb.sb_agcount; agno++) अणु
		काष्ठा xfs_buf		*bp;

		error = xfs_buf_get(mp->m_ddev_targp,
				 XFS_AG_DADDR(mp, agno, XFS_SB_DADDR),
				 XFS_FSS_TO_BB(mp, 1), &bp);
		/*
		 * If we get an error पढ़ोing or writing alternate superblocks,
		 * जारी.  xfs_repair chooses the "best" superblock based
		 * on most matches; अगर we अवरोध early, we'll leave more
		 * superblocks un-updated than updated, and xfs_repair may
		 * pick them over the properly-updated primary.
		 */
		अगर (error) अणु
			xfs_warn(mp,
		"error allocating secondary superblock for ag %d",
				agno);
			अगर (!saved_error)
				saved_error = error;
			जारी;
		पूर्ण

		bp->b_ops = &xfs_sb_buf_ops;
		xfs_buf_oneshot(bp);
		xfs_buf_zero(bp, 0, BBTOB(bp->b_length));
		xfs_sb_to_disk(bp->b_addr, &mp->m_sb);
		xfs_buf_delwri_queue(bp, &buffer_list);
		xfs_buf_rअन्यथा(bp);

		/* करोn't hold too many buffers at once */
		अगर (agno % 16)
			जारी;

		error = xfs_buf_delwri_submit(&buffer_list);
		अगर (error) अणु
			xfs_warn(mp,
		"write error %d updating a secondary superblock near ag %d",
				error, agno);
			अगर (!saved_error)
				saved_error = error;
			जारी;
		पूर्ण
	पूर्ण
	error = xfs_buf_delwri_submit(&buffer_list);
	अगर (error) अणु
		xfs_warn(mp,
		"write error %d updating a secondary superblock near ag %d",
			error, agno);
	पूर्ण

	वापस saved_error ? saved_error : error;
पूर्ण

/*
 * Same behavior as xfs_sync_sb, except that it is always synchronous and it
 * also ग_लिखोs the superblock buffer to disk sector 0 immediately.
 */
पूर्णांक
xfs_sync_sb_buf(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_trans	*tp;
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_sb, 0, 0, 0, &tp);
	अगर (error)
		वापस error;

	bp = xfs_trans_माला_लोb(tp);
	xfs_log_sb(tp);
	xfs_trans_bhold(tp, bp);
	xfs_trans_set_sync(tp);
	error = xfs_trans_commit(tp);
	अगर (error)
		जाओ out;
	/*
	 * ग_लिखो out the sb buffer to get the changes to disk
	 */
	error = xfs_bग_लिखो(bp);
out:
	xfs_buf_rअन्यथा(bp);
	वापस error;
पूर्ण

व्योम
xfs_fs_geometry(
	काष्ठा xfs_sb		*sbp,
	काष्ठा xfs_fsop_geom	*geo,
	पूर्णांक			काष्ठा_version)
अणु
	स_रखो(geo, 0, माप(काष्ठा xfs_fsop_geom));

	geo->blocksize = sbp->sb_blocksize;
	geo->rtextsize = sbp->sb_rextsize;
	geo->agblocks = sbp->sb_agblocks;
	geo->agcount = sbp->sb_agcount;
	geo->logblocks = sbp->sb_logblocks;
	geo->sectsize = sbp->sb_sectsize;
	geo->inodesize = sbp->sb_inodesize;
	geo->imaxpct = sbp->sb_imax_pct;
	geo->datablocks = sbp->sb_dblocks;
	geo->rtblocks = sbp->sb_rblocks;
	geo->rtextents = sbp->sb_rextents;
	geo->logstart = sbp->sb_logstart;
	BUILD_BUG_ON(माप(geo->uuid) != माप(sbp->sb_uuid));
	स_नकल(geo->uuid, &sbp->sb_uuid, माप(sbp->sb_uuid));

	अगर (काष्ठा_version < 2)
		वापस;

	geo->sunit = sbp->sb_unit;
	geo->swidth = sbp->sb_width;

	अगर (काष्ठा_version < 3)
		वापस;

	geo->version = XFS_FSOP_GEOM_VERSION;
	geo->flags = XFS_FSOP_GEOM_FLAGS_NLINK |
		     XFS_FSOP_GEOM_FLAGS_सूचीV2 |
		     XFS_FSOP_GEOM_FLAGS_EXTFLG;
	अगर (xfs_sb_version_hasattr(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_ATTR;
	अगर (xfs_sb_version_hasquota(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_QUOTA;
	अगर (xfs_sb_version_hasalign(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_IALIGN;
	अगर (xfs_sb_version_hasdalign(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_DALIGN;
	अगर (xfs_sb_version_hassector(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_SECTOR;
	अगर (xfs_sb_version_hasasciici(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_सूचीV2CI;
	अगर (xfs_sb_version_haslazysbcount(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_LAZYSB;
	अगर (xfs_sb_version_hasattr2(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_ATTR2;
	अगर (xfs_sb_version_hasprojid32bit(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_PROJID32;
	अगर (xfs_sb_version_hascrc(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_V5SB;
	अगर (xfs_sb_version_hasftype(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_FTYPE;
	अगर (xfs_sb_version_hasfinobt(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_FINOBT;
	अगर (xfs_sb_version_hassparseinodes(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_SPINODES;
	अगर (xfs_sb_version_hasrmapbt(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_RMAPBT;
	अगर (xfs_sb_version_hasreflink(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_REFLINK;
	अगर (xfs_sb_version_hasbigसमय(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_BIGTIME;
	अगर (xfs_sb_version_hasinobtcounts(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_INOBTCNT;
	अगर (xfs_sb_version_hassector(sbp))
		geo->logsectsize = sbp->sb_logsectsize;
	अन्यथा
		geo->logsectsize = BBSIZE;
	geo->rtsectsize = sbp->sb_blocksize;
	geo->dirblocksize = xfs_dir2_dirblock_bytes(sbp);

	अगर (काष्ठा_version < 4)
		वापस;

	अगर (xfs_sb_version_haslogv2(sbp))
		geo->flags |= XFS_FSOP_GEOM_FLAGS_LOGV2;

	geo->logsunit = sbp->sb_logsunit;

	अगर (काष्ठा_version < 5)
		वापस;

	geo->version = XFS_FSOP_GEOM_VERSION_V5;
पूर्ण

/* Read a secondary superblock. */
पूर्णांक
xfs_sb_पढ़ो_secondary(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	ASSERT(agno != 0 && agno != शून्यAGNUMBER);
	error = xfs_trans_पढ़ो_buf(mp, tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, agno, XFS_SB_BLOCK(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &bp, &xfs_sb_buf_ops);
	अगर (error)
		वापस error;
	xfs_buf_set_ref(bp, XFS_SSB_REF);
	*bpp = bp;
	वापस 0;
पूर्ण

/* Get an uninitialised secondary superblock buffer. */
पूर्णांक
xfs_sb_get_secondary(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_buf		*bp;
	पूर्णांक			error;

	ASSERT(agno != 0 && agno != शून्यAGNUMBER);
	error = xfs_trans_get_buf(tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, agno, XFS_SB_BLOCK(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, &bp);
	अगर (error)
		वापस error;
	bp->b_ops = &xfs_sb_buf_ops;
	xfs_buf_oneshot(bp);
	*bpp = bp;
	वापस 0;
पूर्ण

/*
 * sunit, swidth, sectorsize(optional with 0) should be all in bytes,
 * so users won't be confused by values in error messages.
 */
bool
xfs_validate_stripe_geometry(
	काष्ठा xfs_mount	*mp,
	__s64			sunit,
	__s64			swidth,
	पूर्णांक			sectorsize,
	bool			silent)
अणु
	अगर (swidth > पूर्णांक_उच्च) अणु
		अगर (!silent)
			xfs_notice(mp,
"stripe width (%lld) is too large", swidth);
		वापस false;
	पूर्ण

	अगर (sunit > swidth) अणु
		अगर (!silent)
			xfs_notice(mp,
"stripe unit (%lld) is larger than the stripe width (%lld)", sunit, swidth);
		वापस false;
	पूर्ण

	अगर (sectorsize && (पूर्णांक)sunit % sectorsize) अणु
		अगर (!silent)
			xfs_notice(mp,
"stripe unit (%lld) must be a multiple of the sector size (%d)",
				   sunit, sectorsize);
		वापस false;
	पूर्ण

	अगर (sunit && !swidth) अणु
		अगर (!silent)
			xfs_notice(mp,
"invalid stripe unit (%lld) and stripe width of 0", sunit);
		वापस false;
	पूर्ण

	अगर (!sunit && swidth) अणु
		अगर (!silent)
			xfs_notice(mp,
"invalid stripe width (%lld) and stripe unit of 0", swidth);
		वापस false;
	पूर्ण

	अगर (sunit && (पूर्णांक)swidth % (पूर्णांक)sunit) अणु
		अगर (!silent)
			xfs_notice(mp,
"stripe width (%lld) must be a multiple of the stripe unit (%lld)",
				   swidth, sunit);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण
