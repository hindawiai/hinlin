<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * Copyright (C) 2010 Red Hat, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_da_format.h"
#समावेश "xfs_da_btree.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_quota.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_qm.h"
#समावेश "xfs_trans_space.h"

#घोषणा _ALLOC	true
#घोषणा _FREE	false

/*
 * A buffer has a क्रमmat काष्ठाure overhead in the log in addition
 * to the data, so we need to take this पूर्णांकo account when reserving
 * space in a transaction क्रम a buffer.  Round the space required up
 * to a multiple of 128 bytes so that we करोn't change the historical
 * reservation that has been used क्रम this overhead.
 */
STATIC uपूर्णांक
xfs_buf_log_overhead(व्योम)
अणु
	वापस round_up(माप(काष्ठा xlog_op_header) +
			माप(काष्ठा xfs_buf_log_क्रमmat), 128);
पूर्ण

/*
 * Calculate out transaction log reservation per item in bytes.
 *
 * The nbufs argument is used to indicate the number of items that
 * will be changed in a transaction.  size is used to tell how many
 * bytes should be reserved per item.
 */
STATIC uपूर्णांक
xfs_calc_buf_res(
	uपूर्णांक		nbufs,
	uपूर्णांक		size)
अणु
	वापस nbufs * (size + xfs_buf_log_overhead());
पूर्ण

/*
 * Per-extent log reservation क्रम the btree changes involved in मुक्तing or
 * allocating an extent.  In classic XFS there were two trees that will be
 * modअगरied (bnobt + cntbt).  With rmap enabled, there are three trees
 * (rmapbt).  With reflink, there are four trees (refcountbt).  The number of
 * blocks reserved is based on the क्रमmula:
 *
 * num trees * ((2 blocks/level * max depth) - 1)
 *
 * Keep in mind that max depth is calculated separately क्रम each type of tree.
 */
uपूर्णांक
xfs_allocमुक्त_log_count(
	काष्ठा xfs_mount *mp,
	uपूर्णांक		num_ops)
अणु
	uपूर्णांक		blocks;

	blocks = num_ops * 2 * (2 * mp->m_ag_maxlevels - 1);
	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb))
		blocks += num_ops * (2 * mp->m_rmap_maxlevels - 1);
	अगर (xfs_sb_version_hasreflink(&mp->m_sb))
		blocks += num_ops * (2 * mp->m_refc_maxlevels - 1);

	वापस blocks;
पूर्ण

/*
 * Logging inodes is really tricksy. They are logged in memory क्रमmat,
 * which means that what we ग_लिखो पूर्णांकo the log करोesn't directly translate पूर्णांकo
 * the amount of space they use on disk.
 *
 * Case in poपूर्णांक - btree क्रमmat विभाजनs in memory क्रमmat use more space than the
 * on-disk क्रमmat. In memory, the buffer contains a normal btree block header so
 * the btree code can treat it as though it is just another generic buffer.
 * However, when we ग_लिखो it to the inode विभाजन, we करोn't ग_लिखो all of this
 * header as it isn't needed. e.g. the root is only ever in the inode, so
 * there's no need क्रम sibling poपूर्णांकers which would waste 16 bytes of space.
 *
 * Hence when we have an inode with a maximally sized btree क्रमmat विभाजन, then
 * amount of inक्रमmation we actually log is greater than the size of the inode
 * on disk. Hence we need an inode reservation function that calculates all this
 * correctly. So, we log:
 *
 * - 4 log op headers क्रम object
 *	- क्रम the ilf, the inode core and 2 विभाजनs
 * - inode log क्रमmat object
 * - the inode core
 * - two inode विभाजनs containing bmap btree root blocks.
 *	- the btree data contained by both विभाजनs will fit पूर्णांकo the inode size,
 *	  hence when combined with the inode core above, we have a total of the
 *	  actual inode size.
 *	- the BMBT headers need to be accounted separately, as they are
 *	  additional to the records and poपूर्णांकers that fit inside the inode
 *	  विभाजनs.
 */
STATIC uपूर्णांक
xfs_calc_inode_res(
	काष्ठा xfs_mount	*mp,
	uपूर्णांक			ninodes)
अणु
	वापस ninodes *
		(4 * माप(काष्ठा xlog_op_header) +
		 माप(काष्ठा xfs_inode_log_क्रमmat) +
		 mp->m_sb.sb_inodesize +
		 2 * XFS_BMBT_BLOCK_LEN(mp));
पूर्ण

/*
 * Inode btree record insertion/removal modअगरies the inode btree and मुक्त space
 * btrees (since the inobt करोes not use the agfl). This requires the following
 * reservation:
 *
 * the inode btree: max depth * blocksize
 * the allocation btrees: 2 trees * (max depth - 1) * block size
 *
 * The caller must account क्रम SB and AG header modअगरications, etc.
 */
STATIC uपूर्णांक
xfs_calc_inobt_res(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_buf_res(M_IGEO(mp)->inobt_maxlevels,
			XFS_FSB_TO_B(mp, 1)) +
				xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 1),
			XFS_FSB_TO_B(mp, 1));
पूर्ण

/*
 * The मुक्त inode btree is a conditional feature. The behavior dअगरfers slightly
 * from that of the traditional inode btree in that the finobt tracks records
 * क्रम inode chunks with at least one मुक्त inode. A record can be हटाओd from
 * the tree during inभागidual inode allocation. Thereक्रमe the finobt
 * reservation is unconditional क्रम both the inode chunk allocation and
 * inभागidual inode allocation (modअगरy) हालs.
 *
 * Behavior aside, the reservation क्रम finobt modअगरication is equivalent to the
 * traditional inobt: cover a full finobt shape change plus block allocation.
 */
STATIC uपूर्णांक
xfs_calc_finobt_res(
	काष्ठा xfs_mount	*mp)
अणु
	अगर (!xfs_sb_version_hasfinobt(&mp->m_sb))
		वापस 0;

	वापस xfs_calc_inobt_res(mp);
पूर्ण

/*
 * Calculate the reservation required to allocate or मुक्त an inode chunk. This
 * includes:
 *
 * the allocation btrees: 2 trees * (max depth - 1) * block size
 * the inode chunk: m_ino_geo.ialloc_blks * N
 *
 * The size N of the inode chunk reservation depends on whether it is क्रम
 * allocation or मुक्त and which type of create transaction is in use. An inode
 * chunk मुक्त always invalidates the buffers and only requires reservation क्रम
 * headers (N == 0). An inode chunk allocation requires a chunk sized
 * reservation on v4 and older superblocks to initialize the chunk. No chunk
 * reservation is required क्रम allocation on v5 supers, which use ordered
 * buffers to initialize.
 */
STATIC uपूर्णांक
xfs_calc_inode_chunk_res(
	काष्ठा xfs_mount	*mp,
	bool			alloc)
अणु
	uपूर्णांक			res, size = 0;

	res = xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 1),
			       XFS_FSB_TO_B(mp, 1));
	अगर (alloc) अणु
		/* icreate tx uses ordered buffers */
		अगर (xfs_sb_version_has_v3inode(&mp->m_sb))
			वापस res;
		size = XFS_FSB_TO_B(mp, 1);
	पूर्ण

	res += xfs_calc_buf_res(M_IGEO(mp)->ialloc_blks, size);
	वापस res;
पूर्ण

/*
 * Per-extent log reservation क्रम the btree changes involved in मुक्तing or
 * allocating a realसमय extent.  We have to be able to log as many rtbiपंचांगap
 * blocks as needed to mark inuse MAXEXTLEN blocks' worth of realसमय extents,
 * as well as the realसमय summary block.
 */
अटल अचिन्हित पूर्णांक
xfs_rtalloc_log_count(
	काष्ठा xfs_mount	*mp,
	अचिन्हित पूर्णांक		num_ops)
अणु
	अचिन्हित पूर्णांक		blksz = XFS_FSB_TO_B(mp, 1);
	अचिन्हित पूर्णांक		rtbmp_bytes;

	rtbmp_bytes = (MAXEXTLEN / mp->m_sb.sb_rextsize) / NBBY;
	वापस (howmany(rtbmp_bytes, blksz) + 1) * num_ops;
पूर्ण

/*
 * Various log reservation values.
 *
 * These are based on the size of the file प्रणाली block because that is what
 * most transactions manipulate.  Each adds in an additional 128 bytes per
 * item logged to try to account क्रम the overhead of the transaction mechanism.
 *
 * Note:  Most of the reservations underestimate the number of allocation
 * groups पूर्णांकo which they could मुक्त extents in the xfs_defer_finish() call.
 * This is because the number in the worst हाल is quite high and quite
 * unusual.  In order to fix this we need to change xfs_defer_finish() to मुक्त
 * extents in only a single AG at a समय.  This will require changes to the
 * EFI code as well, however, so that the EFI क्रम the extents not मुक्तd is
 * logged again in each transaction.  See SGI PV #261917.
 *
 * Reservation functions here aव्योम a huge stack in xfs_trans_init due to
 * रेजिस्टर overflow from temporaries in the calculations.
 */


/*
 * In a ग_लिखो transaction we can allocate a maximum of 2
 * extents.  This gives (t1):
 *    the inode getting the new extents: inode size
 *    the inode's bmap btree: max depth * block size
 *    the agfs of the ags from which the extents are allocated: 2 * sector
 *    the superblock मुक्त block counter: sector size
 *    the allocation btrees: 2 exts * 2 trees * (2 * max depth - 1) * block size
 * Or, अगर we're writing to a realसमय file (t2):
 *    the inode getting the new extents: inode size
 *    the inode's bmap btree: max depth * block size
 *    the agfs of the ags from which the extents are allocated: 2 * sector
 *    the superblock मुक्त block counter: sector size
 *    the realसमय biपंचांगap: ((MAXEXTLEN / rtextsize) / NBBY) bytes
 *    the realसमय summary: 1 block
 *    the allocation btrees: 2 trees * (2 * max depth - 1) * block size
 * And the bmap_finish transaction can मुक्त bmap blocks in a join (t3):
 *    the agfs of the ags containing the blocks: 2 * sector size
 *    the agfls of the ags containing the blocks: 2 * sector size
 *    the super block मुक्त block counter: sector size
 *    the allocation btrees: 2 exts * 2 trees * (2 * max depth - 1) * block size
 */
STATIC uपूर्णांक
xfs_calc_ग_लिखो_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	अचिन्हित पूर्णांक		t1, t2, t3;
	अचिन्हित पूर्णांक		blksz = XFS_FSB_TO_B(mp, 1);

	t1 = xfs_calc_inode_res(mp, 1) +
	     xfs_calc_buf_res(XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK), blksz) +
	     xfs_calc_buf_res(3, mp->m_sb.sb_sectsize) +
	     xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 2), blksz);

	अगर (xfs_sb_version_hasrealसमय(&mp->m_sb)) अणु
		t2 = xfs_calc_inode_res(mp, 1) +
		     xfs_calc_buf_res(XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK),
				     blksz) +
		     xfs_calc_buf_res(3, mp->m_sb.sb_sectsize) +
		     xfs_calc_buf_res(xfs_rtalloc_log_count(mp, 1), blksz) +
		     xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 1), blksz);
	पूर्ण अन्यथा अणु
		t2 = 0;
	पूर्ण

	t3 = xfs_calc_buf_res(5, mp->m_sb.sb_sectsize) +
	     xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 2), blksz);

	वापस XFS_DQUOT_LOGRES(mp) + max3(t1, t2, t3);
पूर्ण

/*
 * In truncating a file we मुक्त up to two extents at once.  We can modअगरy (t1):
 *    the inode being truncated: inode size
 *    the inode's bmap btree: (max depth + 1) * block size
 * And the bmap_finish transaction can मुक्त the blocks and bmap blocks (t2):
 *    the agf क्रम each of the ags: 4 * sector size
 *    the agfl क्रम each of the ags: 4 * sector size
 *    the super block to reflect the मुक्तd blocks: sector size
 *    worst हाल split in allocation btrees per extent assuming 4 extents:
 *		4 exts * 2 trees * (2 * max depth - 1) * block size
 * Or, अगर it's a realसमय file (t3):
 *    the agf क्रम each of the ags: 2 * sector size
 *    the agfl क्रम each of the ags: 2 * sector size
 *    the super block to reflect the मुक्तd blocks: sector size
 *    the realसमय biपंचांगap: 2 exts * ((MAXEXTLEN / rtextsize) / NBBY) bytes
 *    the realसमय summary: 2 exts * 1 block
 *    worst हाल split in allocation btrees per extent assuming 2 extents:
 *		2 exts * 2 trees * (2 * max depth - 1) * block size
 */
STATIC uपूर्णांक
xfs_calc_itruncate_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	अचिन्हित पूर्णांक		t1, t2, t3;
	अचिन्हित पूर्णांक		blksz = XFS_FSB_TO_B(mp, 1);

	t1 = xfs_calc_inode_res(mp, 1) +
	     xfs_calc_buf_res(XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK) + 1, blksz);

	t2 = xfs_calc_buf_res(9, mp->m_sb.sb_sectsize) +
	     xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 4), blksz);

	अगर (xfs_sb_version_hasrealसमय(&mp->m_sb)) अणु
		t3 = xfs_calc_buf_res(5, mp->m_sb.sb_sectsize) +
		     xfs_calc_buf_res(xfs_rtalloc_log_count(mp, 2), blksz) +
		     xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 2), blksz);
	पूर्ण अन्यथा अणु
		t3 = 0;
	पूर्ण

	वापस XFS_DQUOT_LOGRES(mp) + max3(t1, t2, t3);
पूर्ण

/*
 * In renaming a files we can modअगरy:
 *    the four inodes involved: 4 * inode size
 *    the two directory btrees: 2 * (max depth + v2) * dir block size
 *    the two directory bmap btrees: 2 * max depth * block size
 * And the bmap_finish transaction can मुक्त dir and bmap blocks (two sets
 *	of bmap blocks) giving:
 *    the agf क्रम the ags in which the blocks live: 3 * sector size
 *    the agfl क्रम the ags in which the blocks live: 3 * sector size
 *    the superblock क्रम the मुक्त block count: sector size
 *    the allocation btrees: 3 exts * 2 trees * (2 * max depth - 1) * block size
 */
STATIC uपूर्णांक
xfs_calc_नाम_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस XFS_DQUOT_LOGRES(mp) +
		max((xfs_calc_inode_res(mp, 4) +
		     xfs_calc_buf_res(2 * XFS_सूचीOP_LOG_COUNT(mp),
				      XFS_FSB_TO_B(mp, 1))),
		    (xfs_calc_buf_res(7, mp->m_sb.sb_sectsize) +
		     xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 3),
				      XFS_FSB_TO_B(mp, 1))));
पूर्ण

/*
 * For removing an inode from unlinked list at first, we can modअगरy:
 *    the agi hash list and counters: sector size
 *    the on disk inode beक्रमe ours in the agi hash list: inode cluster size
 *    the on disk inode in the agi hash list: inode cluster size
 */
STATIC uपूर्णांक
xfs_calc_iunlink_हटाओ_reservation(
	काष्ठा xfs_mount        *mp)
अणु
	वापस xfs_calc_buf_res(1, mp->m_sb.sb_sectsize) +
	       2 * M_IGEO(mp)->inode_cluster_size;
पूर्ण

/*
 * For creating a link to an inode:
 *    the parent directory inode: inode size
 *    the linked inode: inode size
 *    the directory btree could split: (max depth + v2) * dir block size
 *    the directory bmap btree could join or split: (max depth + v2) * blocksize
 * And the bmap_finish transaction can मुक्त some bmap blocks giving:
 *    the agf क्रम the ag in which the blocks live: sector size
 *    the agfl क्रम the ag in which the blocks live: sector size
 *    the superblock क्रम the मुक्त block count: sector size
 *    the allocation btrees: 2 trees * (2 * max depth - 1) * block size
 */
STATIC uपूर्णांक
xfs_calc_link_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस XFS_DQUOT_LOGRES(mp) +
		xfs_calc_iunlink_हटाओ_reservation(mp) +
		max((xfs_calc_inode_res(mp, 2) +
		     xfs_calc_buf_res(XFS_सूचीOP_LOG_COUNT(mp),
				      XFS_FSB_TO_B(mp, 1))),
		    (xfs_calc_buf_res(3, mp->m_sb.sb_sectsize) +
		     xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 1),
				      XFS_FSB_TO_B(mp, 1))));
पूर्ण

/*
 * For adding an inode to unlinked list we can modअगरy:
 *    the agi hash list: sector size
 *    the on disk inode: inode cluster size
 */
STATIC uपूर्णांक
xfs_calc_iunlink_add_reservation(xfs_mount_t *mp)
अणु
	वापस xfs_calc_buf_res(1, mp->m_sb.sb_sectsize) +
			M_IGEO(mp)->inode_cluster_size;
पूर्ण

/*
 * For removing a directory entry we can modअगरy:
 *    the parent directory inode: inode size
 *    the हटाओd inode: inode size
 *    the directory btree could join: (max depth + v2) * dir block size
 *    the directory bmap btree could join or split: (max depth + v2) * blocksize
 * And the bmap_finish transaction can मुक्त the dir and bmap blocks giving:
 *    the agf क्रम the ag in which the blocks live: 2 * sector size
 *    the agfl क्रम the ag in which the blocks live: 2 * sector size
 *    the superblock क्रम the मुक्त block count: sector size
 *    the allocation btrees: 2 exts * 2 trees * (2 * max depth - 1) * block size
 */
STATIC uपूर्णांक
xfs_calc_हटाओ_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस XFS_DQUOT_LOGRES(mp) +
		xfs_calc_iunlink_add_reservation(mp) +
		max((xfs_calc_inode_res(mp, 1) +
		     xfs_calc_buf_res(XFS_सूचीOP_LOG_COUNT(mp),
				      XFS_FSB_TO_B(mp, 1))),
		    (xfs_calc_buf_res(4, mp->m_sb.sb_sectsize) +
		     xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 2),
				      XFS_FSB_TO_B(mp, 1))));
पूर्ण

/*
 * For create, अवरोध it in to the two हालs that the transaction
 * covers. We start with the modअगरy हाल - allocation करोne by modअगरication
 * of the state of existing inodes - and the allocation हाल.
 */

/*
 * For create we can modअगरy:
 *    the parent directory inode: inode size
 *    the new inode: inode size
 *    the inode btree entry: block size
 *    the superblock क्रम the nlink flag: sector size
 *    the directory btree: (max depth + v2) * dir block size
 *    the directory inode's bmap btree: (max depth + v2) * block size
 *    the finobt (record modअगरication and allocation btrees)
 */
STATIC uपूर्णांक
xfs_calc_create_resv_modअगरy(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_inode_res(mp, 2) +
		xfs_calc_buf_res(1, mp->m_sb.sb_sectsize) +
		(uपूर्णांक)XFS_FSB_TO_B(mp, 1) +
		xfs_calc_buf_res(XFS_सूचीOP_LOG_COUNT(mp), XFS_FSB_TO_B(mp, 1)) +
		xfs_calc_finobt_res(mp);
पूर्ण

/*
 * For icreate we can allocate some inodes giving:
 *    the agi and agf of the ag getting the new inodes: 2 * sectorsize
 *    the superblock क्रम the nlink flag: sector size
 *    the inode chunk (allocation, optional init)
 *    the inobt (record insertion)
 *    the finobt (optional, record insertion)
 */
STATIC uपूर्णांक
xfs_calc_icreate_resv_alloc(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_buf_res(2, mp->m_sb.sb_sectsize) +
		mp->m_sb.sb_sectsize +
		xfs_calc_inode_chunk_res(mp, _ALLOC) +
		xfs_calc_inobt_res(mp) +
		xfs_calc_finobt_res(mp);
पूर्ण

STATIC uपूर्णांक
xfs_calc_icreate_reservation(xfs_mount_t *mp)
अणु
	वापस XFS_DQUOT_LOGRES(mp) +
		max(xfs_calc_icreate_resv_alloc(mp),
		    xfs_calc_create_resv_modअगरy(mp));
पूर्ण

STATIC uपूर्णांक
xfs_calc_create_क्षणिक_ख_reservation(
	काष्ठा xfs_mount        *mp)
अणु
	uपूर्णांक	res = XFS_DQUOT_LOGRES(mp);

	res += xfs_calc_icreate_resv_alloc(mp);
	वापस res + xfs_calc_iunlink_add_reservation(mp);
पूर्ण

/*
 * Making a new directory is the same as creating a new file.
 */
STATIC uपूर्णांक
xfs_calc_सूची_गढ़ो_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_icreate_reservation(mp);
पूर्ण


/*
 * Making a new symplink is the same as creating a new file, but
 * with the added blocks क्रम remote symlink data which can be up to 1kB in
 * length (XFS_SYMLINK_MAXLEN).
 */
STATIC uपूर्णांक
xfs_calc_symlink_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_icreate_reservation(mp) +
	       xfs_calc_buf_res(1, XFS_SYMLINK_MAXLEN);
पूर्ण

/*
 * In मुक्तing an inode we can modअगरy:
 *    the inode being मुक्तd: inode size
 *    the super block मुक्त inode counter, AGF and AGFL: sector size
 *    the on disk inode (agi unlinked list removal)
 *    the inode chunk (invalidated, headers only)
 *    the inode btree
 *    the finobt (record insertion, removal or modअगरication)
 *
 * Note that the inode chunk res. includes an allocमुक्त res. क्रम मुक्तing of the
 * inode chunk. This is technically extraneous because the inode chunk मुक्त is
 * deferred (it occurs after a transaction roll). Include the extra reservation
 * anyways since we've had reports of अगरree transaction overruns due to too many
 * agfl fixups during inode chunk मुक्तs.
 */
STATIC uपूर्णांक
xfs_calc_अगरree_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस XFS_DQUOT_LOGRES(mp) +
		xfs_calc_inode_res(mp, 1) +
		xfs_calc_buf_res(3, mp->m_sb.sb_sectsize) +
		xfs_calc_iunlink_हटाओ_reservation(mp) +
		xfs_calc_inode_chunk_res(mp, _FREE) +
		xfs_calc_inobt_res(mp) +
		xfs_calc_finobt_res(mp);
पूर्ण

/*
 * When only changing the inode we log the inode and possibly the superblock
 * We also add a bit of slop क्रम the transaction stuff.
 */
STATIC uपूर्णांक
xfs_calc_ichange_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस XFS_DQUOT_LOGRES(mp) +
		xfs_calc_inode_res(mp, 1) +
		xfs_calc_buf_res(1, mp->m_sb.sb_sectsize);

पूर्ण

/*
 * Growing the data section of the fileप्रणाली.
 *	superblock
 *	agi and agf
 *	allocation btrees
 */
STATIC uपूर्णांक
xfs_calc_growdata_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_buf_res(3, mp->m_sb.sb_sectsize) +
		xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 1),
				 XFS_FSB_TO_B(mp, 1));
पूर्ण

/*
 * Growing the rt section of the fileप्रणाली.
 * In the first set of transactions (ALLOC) we allocate space to the
 * biपंचांगap or summary files.
 *	superblock: sector size
 *	agf of the ag from which the extent is allocated: sector size
 *	bmap btree क्रम biपंचांगap/summary inode: max depth * blocksize
 *	biपंचांगap/summary inode: inode size
 *	allocation btrees क्रम 1 block alloc: 2 * (2 * maxdepth - 1) * blocksize
 */
STATIC uपूर्णांक
xfs_calc_growrtalloc_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_buf_res(2, mp->m_sb.sb_sectsize) +
		xfs_calc_buf_res(XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK),
				 XFS_FSB_TO_B(mp, 1)) +
		xfs_calc_inode_res(mp, 1) +
		xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 1),
				 XFS_FSB_TO_B(mp, 1));
पूर्ण

/*
 * Growing the rt section of the fileप्रणाली.
 * In the second set of transactions (ZERO) we zero the new metadata blocks.
 *	one biपंचांगap/summary block: blocksize
 */
STATIC uपूर्णांक
xfs_calc_growrtzero_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_buf_res(1, mp->m_sb.sb_blocksize);
पूर्ण

/*
 * Growing the rt section of the fileप्रणाली.
 * In the third set of transactions (FREE) we update metadata without
 * allocating any new blocks.
 *	superblock: sector size
 *	biपंचांगap inode: inode size
 *	summary inode: inode size
 *	one biपंचांगap block: blocksize
 *	summary blocks: new summary size
 */
STATIC uपूर्णांक
xfs_calc_growrtमुक्त_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_buf_res(1, mp->m_sb.sb_sectsize) +
		xfs_calc_inode_res(mp, 2) +
		xfs_calc_buf_res(1, mp->m_sb.sb_blocksize) +
		xfs_calc_buf_res(1, mp->m_rsumsize);
पूर्ण

/*
 * Logging the inode modअगरication बारtamp on a synchronous ग_लिखो.
 *	inode
 */
STATIC uपूर्णांक
xfs_calc_sग_लिखो_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_inode_res(mp, 1);
पूर्ण

/*
 * Logging the inode mode bits when writing a setuid/setgid file
 *	inode
 */
STATIC uपूर्णांक
xfs_calc_ग_लिखोid_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_inode_res(mp, 1);
पूर्ण

/*
 * Converting the inode from non-attributed to attributed.
 *	the inode being converted: inode size
 *	agf block and superblock (क्रम block allocation)
 *	the new block (directory sized)
 *	bmap blocks क्रम the new directory block
 *	allocation btrees
 */
STATIC uपूर्णांक
xfs_calc_addaविभाजन_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस XFS_DQUOT_LOGRES(mp) +
		xfs_calc_inode_res(mp, 1) +
		xfs_calc_buf_res(2, mp->m_sb.sb_sectsize) +
		xfs_calc_buf_res(1, mp->m_dir_geo->blksize) +
		xfs_calc_buf_res(XFS_DAENTER_BMAP1B(mp, XFS_DATA_FORK) + 1,
				 XFS_FSB_TO_B(mp, 1)) +
		xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 1),
				 XFS_FSB_TO_B(mp, 1));
पूर्ण

/*
 * Removing the attribute विभाजन of a file
 *    the inode being truncated: inode size
 *    the inode's bmap btree: max depth * block size
 * And the bmap_finish transaction can मुक्त the blocks and bmap blocks:
 *    the agf क्रम each of the ags: 4 * sector size
 *    the agfl क्रम each of the ags: 4 * sector size
 *    the super block to reflect the मुक्तd blocks: sector size
 *    worst हाल split in allocation btrees per extent assuming 4 extents:
 *		4 exts * 2 trees * (2 * max depth - 1) * block size
 */
STATIC uपूर्णांक
xfs_calc_attrinval_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस max((xfs_calc_inode_res(mp, 1) +
		    xfs_calc_buf_res(XFS_BM_MAXLEVELS(mp, XFS_ATTR_FORK),
				     XFS_FSB_TO_B(mp, 1))),
		   (xfs_calc_buf_res(9, mp->m_sb.sb_sectsize) +
		    xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 4),
				     XFS_FSB_TO_B(mp, 1))));
पूर्ण

/*
 * Setting an attribute at mount समय.
 *	the inode getting the attribute
 *	the superblock क्रम allocations
 *	the agfs extents are allocated from
 *	the attribute btree * max depth
 *	the inode allocation btree
 * Since attribute transaction space is dependent on the size of the attribute,
 * the calculation is करोne partially at mount समय and partially at runसमय(see
 * below).
 */
STATIC uपूर्णांक
xfs_calc_attrseपंचांग_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस XFS_DQUOT_LOGRES(mp) +
		xfs_calc_inode_res(mp, 1) +
		xfs_calc_buf_res(1, mp->m_sb.sb_sectsize) +
		xfs_calc_buf_res(XFS_DA_NODE_MAXDEPTH, XFS_FSB_TO_B(mp, 1));
पूर्ण

/*
 * Setting an attribute at runसमय, transaction space unit per block.
 * 	the superblock क्रम allocations: sector size
 *	the inode bmap btree could join or split: max depth * block size
 * Since the runसमय attribute transaction space is dependent on the total
 * blocks needed क्रम the 1st bmap, here we calculate out the space unit क्रम
 * one block so that the caller could figure out the total space according
 * to the attibute extent length in blocks by:
 *	ext * M_RES(mp)->tr_attrsetrt.tr_logres
 */
STATIC uपूर्णांक
xfs_calc_attrsetrt_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_buf_res(1, mp->m_sb.sb_sectsize) +
		xfs_calc_buf_res(XFS_BM_MAXLEVELS(mp, XFS_ATTR_FORK),
				 XFS_FSB_TO_B(mp, 1));
पूर्ण

/*
 * Removing an attribute.
 *    the inode: inode size
 *    the attribute btree could join: max depth * block size
 *    the inode bmap btree could join or split: max depth * block size
 * And the bmap_finish transaction can मुक्त the attr blocks मुक्तd giving:
 *    the agf क्रम the ag in which the blocks live: 2 * sector size
 *    the agfl क्रम the ag in which the blocks live: 2 * sector size
 *    the superblock क्रम the मुक्त block count: sector size
 *    the allocation btrees: 2 exts * 2 trees * (2 * max depth - 1) * block size
 */
STATIC uपूर्णांक
xfs_calc_attrrm_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस XFS_DQUOT_LOGRES(mp) +
		max((xfs_calc_inode_res(mp, 1) +
		     xfs_calc_buf_res(XFS_DA_NODE_MAXDEPTH,
				      XFS_FSB_TO_B(mp, 1)) +
		     (uपूर्णांक)XFS_FSB_TO_B(mp,
					XFS_BM_MAXLEVELS(mp, XFS_ATTR_FORK)) +
		     xfs_calc_buf_res(XFS_BM_MAXLEVELS(mp, XFS_DATA_FORK), 0)),
		    (xfs_calc_buf_res(5, mp->m_sb.sb_sectsize) +
		     xfs_calc_buf_res(xfs_allocमुक्त_log_count(mp, 2),
				      XFS_FSB_TO_B(mp, 1))));
पूर्ण

/*
 * Clearing a bad agino number in an agi hash bucket.
 */
STATIC uपूर्णांक
xfs_calc_clear_agi_bucket_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_buf_res(1, mp->m_sb.sb_sectsize);
पूर्ण

/*
 * Adjusting quota limits.
 *    the disk quota buffer: माप(काष्ठा xfs_disk_dquot)
 */
STATIC uपूर्णांक
xfs_calc_qm_setqlim_reservation(व्योम)
अणु
	वापस xfs_calc_buf_res(1, माप(काष्ठा xfs_disk_dquot));
पूर्ण

/*
 * Allocating quota on disk अगर needed.
 *	the ग_लिखो transaction log space क्रम quota file extent allocation
 *	the unit of quota allocation: one प्रणाली block size
 */
STATIC uपूर्णांक
xfs_calc_qm_dqalloc_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_ग_लिखो_reservation(mp) +
		xfs_calc_buf_res(1,
			XFS_FSB_TO_B(mp, XFS_DQUOT_CLUSTER_SIZE_FSB) - 1);
पूर्ण

/*
 * Turning off quotas.
 *    the quota off logitems: माप(काष्ठा xfs_qoff_logitem) * 2
 *    the superblock क्रम the quota flags: sector size
 */
STATIC uपूर्णांक
xfs_calc_qm_quotaoff_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस माप(काष्ठा xfs_qoff_logitem) * 2 +
		xfs_calc_buf_res(1, mp->m_sb.sb_sectsize);
पूर्ण

/*
 * End of turning off quotas.
 *    the quota off logitems: माप(काष्ठा xfs_qoff_logitem) * 2
 */
STATIC uपूर्णांक
xfs_calc_qm_quotaoff_end_reservation(व्योम)
अणु
	वापस माप(काष्ठा xfs_qoff_logitem) * 2;
पूर्ण

/*
 * Syncing the incore super block changes to disk.
 *     the super block to reflect the changes: sector size
 */
STATIC uपूर्णांक
xfs_calc_sb_reservation(
	काष्ठा xfs_mount	*mp)
अणु
	वापस xfs_calc_buf_res(1, mp->m_sb.sb_sectsize);
पूर्ण

व्योम
xfs_trans_resv_calc(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans_resv	*resp)
अणु
	/*
	 * The following transactions are logged in physical क्रमmat and
	 * require a permanent reservation on space.
	 */
	resp->tr_ग_लिखो.tr_logres = xfs_calc_ग_लिखो_reservation(mp);
	अगर (xfs_sb_version_hasreflink(&mp->m_sb))
		resp->tr_ग_लिखो.tr_logcount = XFS_WRITE_LOG_COUNT_REFLINK;
	अन्यथा
		resp->tr_ग_लिखो.tr_logcount = XFS_WRITE_LOG_COUNT;
	resp->tr_ग_लिखो.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_itruncate.tr_logres = xfs_calc_itruncate_reservation(mp);
	अगर (xfs_sb_version_hasreflink(&mp->m_sb))
		resp->tr_itruncate.tr_logcount =
				XFS_ITRUNCATE_LOG_COUNT_REFLINK;
	अन्यथा
		resp->tr_itruncate.tr_logcount = XFS_ITRUNCATE_LOG_COUNT;
	resp->tr_itruncate.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_नाम.tr_logres = xfs_calc_नाम_reservation(mp);
	resp->tr_नाम.tr_logcount = XFS_RENAME_LOG_COUNT;
	resp->tr_नाम.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_link.tr_logres = xfs_calc_link_reservation(mp);
	resp->tr_link.tr_logcount = XFS_LINK_LOG_COUNT;
	resp->tr_link.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_हटाओ.tr_logres = xfs_calc_हटाओ_reservation(mp);
	resp->tr_हटाओ.tr_logcount = XFS_REMOVE_LOG_COUNT;
	resp->tr_हटाओ.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_symlink.tr_logres = xfs_calc_symlink_reservation(mp);
	resp->tr_symlink.tr_logcount = XFS_SYMLINK_LOG_COUNT;
	resp->tr_symlink.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_create.tr_logres = xfs_calc_icreate_reservation(mp);
	resp->tr_create.tr_logcount = XFS_CREATE_LOG_COUNT;
	resp->tr_create.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_create_क्षणिक_ख.tr_logres =
			xfs_calc_create_क्षणिक_ख_reservation(mp);
	resp->tr_create_क्षणिक_ख.tr_logcount = XFS_CREATE_TMPखाता_LOG_COUNT;
	resp->tr_create_क्षणिक_ख.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_सूची_गढ़ो.tr_logres = xfs_calc_सूची_गढ़ो_reservation(mp);
	resp->tr_सूची_गढ़ो.tr_logcount = XFS_MKसूची_LOG_COUNT;
	resp->tr_सूची_गढ़ो.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_अगरree.tr_logres = xfs_calc_अगरree_reservation(mp);
	resp->tr_अगरree.tr_logcount = XFS_INACTIVE_LOG_COUNT;
	resp->tr_अगरree.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_addaविभाजन.tr_logres = xfs_calc_addaविभाजन_reservation(mp);
	resp->tr_addaविभाजन.tr_logcount = XFS_ADDAFORK_LOG_COUNT;
	resp->tr_addaविभाजन.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_attrinval.tr_logres = xfs_calc_attrinval_reservation(mp);
	resp->tr_attrinval.tr_logcount = XFS_ATTRINVAL_LOG_COUNT;
	resp->tr_attrinval.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_attrseपंचांग.tr_logres = xfs_calc_attrseपंचांग_reservation(mp);
	resp->tr_attrseपंचांग.tr_logcount = XFS_ATTRSET_LOG_COUNT;
	resp->tr_attrseपंचांग.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_attrrm.tr_logres = xfs_calc_attrrm_reservation(mp);
	resp->tr_attrrm.tr_logcount = XFS_ATTRRM_LOG_COUNT;
	resp->tr_attrrm.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_growrtalloc.tr_logres = xfs_calc_growrtalloc_reservation(mp);
	resp->tr_growrtalloc.tr_logcount = XFS_DEFAULT_PERM_LOG_COUNT;
	resp->tr_growrtalloc.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	resp->tr_qm_dqalloc.tr_logres = xfs_calc_qm_dqalloc_reservation(mp);
	अगर (xfs_sb_version_hasreflink(&mp->m_sb))
		resp->tr_qm_dqalloc.tr_logcount = XFS_WRITE_LOG_COUNT_REFLINK;
	अन्यथा
		resp->tr_qm_dqalloc.tr_logcount = XFS_WRITE_LOG_COUNT;
	resp->tr_qm_dqalloc.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	/*
	 * The following transactions are logged in logical क्रमmat with
	 * a शेष log count.
	 */
	resp->tr_qm_setqlim.tr_logres = xfs_calc_qm_setqlim_reservation();
	resp->tr_qm_setqlim.tr_logcount = XFS_DEFAULT_LOG_COUNT;

	resp->tr_qm_quotaoff.tr_logres = xfs_calc_qm_quotaoff_reservation(mp);
	resp->tr_qm_quotaoff.tr_logcount = XFS_DEFAULT_LOG_COUNT;

	resp->tr_qm_equotaoff.tr_logres =
		xfs_calc_qm_quotaoff_end_reservation();
	resp->tr_qm_equotaoff.tr_logcount = XFS_DEFAULT_LOG_COUNT;

	resp->tr_sb.tr_logres = xfs_calc_sb_reservation(mp);
	resp->tr_sb.tr_logcount = XFS_DEFAULT_LOG_COUNT;

	/* growdata requires permanent res; it can मुक्त space to the last AG */
	resp->tr_growdata.tr_logres = xfs_calc_growdata_reservation(mp);
	resp->tr_growdata.tr_logcount = XFS_DEFAULT_PERM_LOG_COUNT;
	resp->tr_growdata.tr_logflags |= XFS_TRANS_PERM_LOG_RES;

	/* The following transaction are logged in logical क्रमmat */
	resp->tr_ichange.tr_logres = xfs_calc_ichange_reservation(mp);
	resp->tr_fsyncts.tr_logres = xfs_calc_sग_लिखो_reservation(mp);
	resp->tr_ग_लिखोid.tr_logres = xfs_calc_ग_लिखोid_reservation(mp);
	resp->tr_attrsetrt.tr_logres = xfs_calc_attrsetrt_reservation(mp);
	resp->tr_clearagi.tr_logres = xfs_calc_clear_agi_bucket_reservation(mp);
	resp->tr_growrtzero.tr_logres = xfs_calc_growrtzero_reservation(mp);
	resp->tr_growrtमुक्त.tr_logres = xfs_calc_growrtमुक्त_reservation(mp);
पूर्ण
