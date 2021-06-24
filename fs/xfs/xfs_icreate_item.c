<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2008-2010, 2013 Dave Chinner
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
#समावेश "xfs_icreate_item.h"
#समावेश "xfs_log.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_log_recover.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_trace.h"

kmem_zone_t	*xfs_icreate_zone;		/* inode create item zone */

अटल अंतरभूत काष्ठा xfs_icreate_item *ICR_ITEM(काष्ठा xfs_log_item *lip)
अणु
	वापस container_of(lip, काष्ठा xfs_icreate_item, ic_item);
पूर्ण

/*
 * This वापसs the number of iovecs needed to log the given inode item.
 *
 * We only need one iovec क्रम the icreate log काष्ठाure.
 */
STATIC व्योम
xfs_icreate_item_size(
	काष्ठा xfs_log_item	*lip,
	पूर्णांक			*nvecs,
	पूर्णांक			*nbytes)
अणु
	*nvecs += 1;
	*nbytes += माप(काष्ठा xfs_icreate_log);
पूर्ण

/*
 * This is called to fill in the vector of log iovecs क्रम the
 * given inode create log item.
 */
STATIC व्योम
xfs_icreate_item_क्रमmat(
	काष्ठा xfs_log_item	*lip,
	काष्ठा xfs_log_vec	*lv)
अणु
	काष्ठा xfs_icreate_item	*icp = ICR_ITEM(lip);
	काष्ठा xfs_log_iovec	*vecp = शून्य;

	xlog_copy_iovec(lv, &vecp, XLOG_REG_TYPE_ICREATE,
			&icp->ic_क्रमmat,
			माप(काष्ठा xfs_icreate_log));
पूर्ण

STATIC व्योम
xfs_icreate_item_release(
	काष्ठा xfs_log_item	*lip)
अणु
	kmem_cache_मुक्त(xfs_icreate_zone, ICR_ITEM(lip));
पूर्ण

अटल स्थिर काष्ठा xfs_item_ops xfs_icreate_item_ops = अणु
	.flags		= XFS_ITEM_RELEASE_WHEN_COMMITTED,
	.iop_size	= xfs_icreate_item_size,
	.iop_क्रमmat	= xfs_icreate_item_क्रमmat,
	.iop_release	= xfs_icreate_item_release,
पूर्ण;


/*
 * Initialize the inode log item क्रम a newly allocated (in-core) inode.
 *
 * Inode extents can only reside within an AG. Hence specअगरy the starting
 * block क्रम the inode chunk by offset within an AG as well as the
 * length of the allocated extent.
 *
 * This joins the item to the transaction and marks it dirty so
 * that we करोn't need a separate call to करो this, nor करोes the
 * caller need to know anything about the icreate item.
 */
व्योम
xfs_icreate_log(
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agblock_t		agbno,
	अचिन्हित पूर्णांक		count,
	अचिन्हित पूर्णांक		inode_size,
	xfs_agblock_t		length,
	अचिन्हित पूर्णांक		generation)
अणु
	काष्ठा xfs_icreate_item	*icp;

	icp = kmem_cache_zalloc(xfs_icreate_zone, GFP_KERNEL | __GFP_NOFAIL);

	xfs_log_item_init(tp->t_mountp, &icp->ic_item, XFS_LI_ICREATE,
			  &xfs_icreate_item_ops);

	icp->ic_क्रमmat.icl_type = XFS_LI_ICREATE;
	icp->ic_क्रमmat.icl_size = 1;	/* single vector */
	icp->ic_क्रमmat.icl_ag = cpu_to_be32(agno);
	icp->ic_क्रमmat.icl_agbno = cpu_to_be32(agbno);
	icp->ic_क्रमmat.icl_count = cpu_to_be32(count);
	icp->ic_क्रमmat.icl_isize = cpu_to_be32(inode_size);
	icp->ic_क्रमmat.icl_length = cpu_to_be32(length);
	icp->ic_क्रमmat.icl_gen = cpu_to_be32(generation);

	xfs_trans_add_item(tp, &icp->ic_item);
	tp->t_flags |= XFS_TRANS_सूचीTY;
	set_bit(XFS_LI_सूचीTY, &icp->ic_item.li_flags);
पूर्ण

अटल क्रमागत xlog_recover_reorder
xlog_recover_icreate_reorder(
		काष्ठा xlog_recover_item *item)
अणु
	/*
	 * Inode allocation buffers must be replayed beक्रमe subsequent inode
	 * items try to modअगरy those buffers.  ICREATE items are the logical
	 * equivalent of logging a newly initialized inode buffer, so recover
	 * these at the same समय that we recover logged buffers.
	 */
	वापस XLOG_REORDER_BUFFER_LIST;
पूर्ण

/*
 * This routine is called when an inode create क्रमmat काष्ठाure is found in a
 * committed transaction in the log.  It's purpose is to initialise the inodes
 * being allocated on disk. This requires us to get inode cluster buffers that
 * match the range to be initialised, stamped with inode ढाँचाs and written
 * by delayed ग_लिखो so that subsequent modअगरications will hit the cached buffer
 * and only need writing out at the end of recovery.
 */
STATIC पूर्णांक
xlog_recover_icreate_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			lsn)
अणु
	काष्ठा xfs_mount		*mp = log->l_mp;
	काष्ठा xfs_icreate_log		*icl;
	काष्ठा xfs_ino_geometry		*igeo = M_IGEO(mp);
	xfs_agnumber_t			agno;
	xfs_agblock_t			agbno;
	अचिन्हित पूर्णांक			count;
	अचिन्हित पूर्णांक			isize;
	xfs_agblock_t			length;
	पूर्णांक				bb_per_cluster;
	पूर्णांक				cancel_count;
	पूर्णांक				nbufs;
	पूर्णांक				i;

	icl = (काष्ठा xfs_icreate_log *)item->ri_buf[0].i_addr;
	अगर (icl->icl_type != XFS_LI_ICREATE) अणु
		xfs_warn(log->l_mp, "xlog_recover_do_icreate_trans: bad type");
		वापस -EINVAL;
	पूर्ण

	अगर (icl->icl_size != 1) अणु
		xfs_warn(log->l_mp, "xlog_recover_do_icreate_trans: bad icl size");
		वापस -EINVAL;
	पूर्ण

	agno = be32_to_cpu(icl->icl_ag);
	अगर (agno >= mp->m_sb.sb_agcount) अणु
		xfs_warn(log->l_mp, "xlog_recover_do_icreate_trans: bad agno");
		वापस -EINVAL;
	पूर्ण
	agbno = be32_to_cpu(icl->icl_agbno);
	अगर (!agbno || agbno == शून्यAGBLOCK || agbno >= mp->m_sb.sb_agblocks) अणु
		xfs_warn(log->l_mp, "xlog_recover_do_icreate_trans: bad agbno");
		वापस -EINVAL;
	पूर्ण
	isize = be32_to_cpu(icl->icl_isize);
	अगर (isize != mp->m_sb.sb_inodesize) अणु
		xfs_warn(log->l_mp, "xlog_recover_do_icreate_trans: bad isize");
		वापस -EINVAL;
	पूर्ण
	count = be32_to_cpu(icl->icl_count);
	अगर (!count) अणु
		xfs_warn(log->l_mp, "xlog_recover_do_icreate_trans: bad count");
		वापस -EINVAL;
	पूर्ण
	length = be32_to_cpu(icl->icl_length);
	अगर (!length || length >= mp->m_sb.sb_agblocks) अणु
		xfs_warn(log->l_mp, "xlog_recover_do_icreate_trans: bad length");
		वापस -EINVAL;
	पूर्ण

	/*
	 * The inode chunk is either full or sparse and we only support
	 * m_ino_geo.ialloc_min_blks sized sparse allocations at this समय.
	 */
	अगर (length != igeo->ialloc_blks &&
	    length != igeo->ialloc_min_blks) अणु
		xfs_warn(log->l_mp,
			 "%s: unsupported chunk length", __FUNCTION__);
		वापस -EINVAL;
	पूर्ण

	/* verअगरy inode count is consistent with extent length */
	अगर ((count >> mp->m_sb.sb_inopblog) != length) अणु
		xfs_warn(log->l_mp,
			 "%s: inconsistent inode count and chunk length",
			 __FUNCTION__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * The icreate transaction can cover multiple cluster buffers and these
	 * buffers could have been मुक्तd and reused. Check the inभागidual
	 * buffers क्रम cancellation so we करोn't overग_लिखो anything written after
	 * a cancellation.
	 */
	bb_per_cluster = XFS_FSB_TO_BB(mp, igeo->blocks_per_cluster);
	nbufs = length / igeo->blocks_per_cluster;
	क्रम (i = 0, cancel_count = 0; i < nbufs; i++) अणु
		xfs_daddr_t	daddr;

		daddr = XFS_AGB_TO_DADDR(mp, agno,
				agbno + i * igeo->blocks_per_cluster);
		अगर (xlog_is_buffer_cancelled(log, daddr, bb_per_cluster))
			cancel_count++;
	पूर्ण

	/*
	 * We currently only use icreate क्रम a single allocation at a समय. This
	 * means we should expect either all or none of the buffers to be
	 * cancelled. Be conservative and skip replay अगर at least one buffer is
	 * cancelled, but warn the user that something is awry अगर the buffers
	 * are not consistent.
	 *
	 * XXX: This must be refined to only skip cancelled clusters once we use
	 * icreate क्रम multiple chunk allocations.
	 */
	ASSERT(!cancel_count || cancel_count == nbufs);
	अगर (cancel_count) अणु
		अगर (cancel_count != nbufs)
			xfs_warn(mp,
	"WARNING: partial inode chunk cancellation, skipped icreate.");
		trace_xfs_log_recover_icreate_cancel(log, icl);
		वापस 0;
	पूर्ण

	trace_xfs_log_recover_icreate_recover(log, icl);
	वापस xfs_ialloc_inode_init(mp, शून्य, buffer_list, count, agno, agbno,
				     length, be32_to_cpu(icl->icl_gen));
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_icreate_item_ops = अणु
	.item_type		= XFS_LI_ICREATE,
	.reorder		= xlog_recover_icreate_reorder,
	.commit_pass2		= xlog_recover_icreate_commit_pass2,
पूर्ण;
