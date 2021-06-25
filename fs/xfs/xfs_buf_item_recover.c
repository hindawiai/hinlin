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
#समावेश "xfs_bit.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_trans_priv.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_log.h"
#समावेश "xfs_log_priv.h"
#समावेश "xfs_log_recover.h"
#समावेश "xfs_error.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_quota.h"

/*
 * This काष्ठाure is used during recovery to record the buf log items which
 * have been canceled and should not be replayed.
 */
काष्ठा xfs_buf_cancel अणु
	xfs_daddr_t		bc_blkno;
	uपूर्णांक			bc_len;
	पूर्णांक			bc_refcount;
	काष्ठा list_head	bc_list;
पूर्ण;

अटल काष्ठा xfs_buf_cancel *
xlog_find_buffer_cancelled(
	काष्ठा xlog		*log,
	xfs_daddr_t		blkno,
	uपूर्णांक			len)
अणु
	काष्ठा list_head	*bucket;
	काष्ठा xfs_buf_cancel	*bcp;

	अगर (!log->l_buf_cancel_table)
		वापस शून्य;

	bucket = XLOG_BUF_CANCEL_BUCKET(log, blkno);
	list_क्रम_each_entry(bcp, bucket, bc_list) अणु
		अगर (bcp->bc_blkno == blkno && bcp->bc_len == len)
			वापस bcp;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool
xlog_add_buffer_cancelled(
	काष्ठा xlog		*log,
	xfs_daddr_t		blkno,
	uपूर्णांक			len)
अणु
	काष्ठा xfs_buf_cancel	*bcp;

	/*
	 * If we find an existing cancel record, this indicates that the buffer
	 * was cancelled multiple बार.  To ensure that during pass 2 we keep
	 * the record in the table until we reach its last occurrence in the
	 * log, a reference count is kept to tell how many बार we expect to
	 * see this record during the second pass.
	 */
	bcp = xlog_find_buffer_cancelled(log, blkno, len);
	अगर (bcp) अणु
		bcp->bc_refcount++;
		वापस false;
	पूर्ण

	bcp = kmem_alloc(माप(काष्ठा xfs_buf_cancel), 0);
	bcp->bc_blkno = blkno;
	bcp->bc_len = len;
	bcp->bc_refcount = 1;
	list_add_tail(&bcp->bc_list, XLOG_BUF_CANCEL_BUCKET(log, blkno));
	वापस true;
पूर्ण

/*
 * Check अगर there is and entry क्रम blkno, len in the buffer cancel record table.
 */
bool
xlog_is_buffer_cancelled(
	काष्ठा xlog		*log,
	xfs_daddr_t		blkno,
	uपूर्णांक			len)
अणु
	वापस xlog_find_buffer_cancelled(log, blkno, len) != शून्य;
पूर्ण

/*
 * Check अगर there is and entry क्रम blkno, len in the buffer cancel record table,
 * and decremented the reference count on it अगर there is one.
 *
 * Remove the cancel record once the refcount hits zero, so that अगर the same
 * buffer is re-used again after its last cancellation we actually replay the
 * changes made at that poपूर्णांक.
 */
अटल bool
xlog_put_buffer_cancelled(
	काष्ठा xlog		*log,
	xfs_daddr_t		blkno,
	uपूर्णांक			len)
अणु
	काष्ठा xfs_buf_cancel	*bcp;

	bcp = xlog_find_buffer_cancelled(log, blkno, len);
	अगर (!bcp) अणु
		ASSERT(0);
		वापस false;
	पूर्ण

	अगर (--bcp->bc_refcount == 0) अणु
		list_del(&bcp->bc_list);
		kmem_मुक्त(bcp);
	पूर्ण
	वापस true;
पूर्ण

/* log buffer item recovery */

/*
 * Sort buffer items क्रम log recovery.  Most buffer items should end up on the
 * buffer list and are recovered first, with the following exceptions:
 *
 * 1. XFS_BLF_CANCEL buffers must be processed last because some log items
 *    might depend on the incor ecancellation record, and replaying a cancelled
 *    buffer item can हटाओ the incore record.
 *
 * 2. XFS_BLF_INODE_BUF buffers are handled after most regular items so that
 *    we replay di_next_unlinked only after flushing the inode 'free' state
 *    to the inode buffer.
 *
 * See xlog_recover_reorder_trans क्रम more details.
 */
STATIC क्रमागत xlog_recover_reorder
xlog_recover_buf_reorder(
	काष्ठा xlog_recover_item	*item)
अणु
	काष्ठा xfs_buf_log_क्रमmat	*buf_f = item->ri_buf[0].i_addr;

	अगर (buf_f->blf_flags & XFS_BLF_CANCEL)
		वापस XLOG_REORDER_CANCEL_LIST;
	अगर (buf_f->blf_flags & XFS_BLF_INODE_BUF)
		वापस XLOG_REORDER_INODE_BUFFER_LIST;
	वापस XLOG_REORDER_BUFFER_LIST;
पूर्ण

STATIC व्योम
xlog_recover_buf_ra_pass2(
	काष्ठा xlog                     *log,
	काष्ठा xlog_recover_item        *item)
अणु
	काष्ठा xfs_buf_log_क्रमmat	*buf_f = item->ri_buf[0].i_addr;

	xlog_buf_पढ़ोahead(log, buf_f->blf_blkno, buf_f->blf_len, शून्य);
पूर्ण

/*
 * Build up the table of buf cancel records so that we करोn't replay cancelled
 * data in the second pass.
 */
अटल पूर्णांक
xlog_recover_buf_commit_pass1(
	काष्ठा xlog			*log,
	काष्ठा xlog_recover_item	*item)
अणु
	काष्ठा xfs_buf_log_क्रमmat	*bf = item->ri_buf[0].i_addr;

	अगर (!xfs_buf_log_check_iovec(&item->ri_buf[0])) अणु
		xfs_err(log->l_mp, "bad buffer log item size (%d)",
				item->ri_buf[0].i_len);
		वापस -EFSCORRUPTED;
	पूर्ण

	अगर (!(bf->blf_flags & XFS_BLF_CANCEL))
		trace_xfs_log_recover_buf_not_cancel(log, bf);
	अन्यथा अगर (xlog_add_buffer_cancelled(log, bf->blf_blkno, bf->blf_len))
		trace_xfs_log_recover_buf_cancel_add(log, bf);
	अन्यथा
		trace_xfs_log_recover_buf_cancel_ref_inc(log, bf);
	वापस 0;
पूर्ण

/*
 * Validate the recovered buffer is of the correct type and attach the
 * appropriate buffer operations to them क्रम ग_लिखोback. Magic numbers are in a
 * few places:
 *	the first 16 bits of the buffer (inode buffer, dquot buffer),
 *	the first 32 bits of the buffer (most blocks),
 *	inside a काष्ठा xfs_da_blkinfo at the start of the buffer.
 */
अटल व्योम
xlog_recover_validate_buf_type(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_buf			*bp,
	काष्ठा xfs_buf_log_क्रमmat	*buf_f,
	xfs_lsn_t			current_lsn)
अणु
	काष्ठा xfs_da_blkinfo		*info = bp->b_addr;
	uपूर्णांक32_t			magic32;
	uपूर्णांक16_t			magic16;
	uपूर्णांक16_t			magicda;
	अक्षर				*warnmsg = शून्य;

	/*
	 * We can only करो post recovery validation on items on CRC enabled
	 * fielप्रणालीs as we need to know when the buffer was written to be able
	 * to determine अगर we should have replayed the item. If we replay old
	 * metadata over a newer buffer, then it will enter a temporarily
	 * inconsistent state resulting in verअगरication failures. Hence क्रम now
	 * just aव्योम the verअगरication stage क्रम non-crc fileप्रणालीs
	 */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	magic32 = be32_to_cpu(*(__be32 *)bp->b_addr);
	magic16 = be16_to_cpu(*(__be16*)bp->b_addr);
	magicda = be16_to_cpu(info->magic);
	चयन (xfs_blft_from_flags(buf_f)) अणु
	हाल XFS_BLFT_BTREE_BUF:
		चयन (magic32) अणु
		हाल XFS_ABTB_CRC_MAGIC:
		हाल XFS_ABTB_MAGIC:
			bp->b_ops = &xfs_bnobt_buf_ops;
			अवरोध;
		हाल XFS_ABTC_CRC_MAGIC:
		हाल XFS_ABTC_MAGIC:
			bp->b_ops = &xfs_cntbt_buf_ops;
			अवरोध;
		हाल XFS_IBT_CRC_MAGIC:
		हाल XFS_IBT_MAGIC:
			bp->b_ops = &xfs_inobt_buf_ops;
			अवरोध;
		हाल XFS_FIBT_CRC_MAGIC:
		हाल XFS_FIBT_MAGIC:
			bp->b_ops = &xfs_finobt_buf_ops;
			अवरोध;
		हाल XFS_BMAP_CRC_MAGIC:
		हाल XFS_BMAP_MAGIC:
			bp->b_ops = &xfs_bmbt_buf_ops;
			अवरोध;
		हाल XFS_RMAP_CRC_MAGIC:
			bp->b_ops = &xfs_rmapbt_buf_ops;
			अवरोध;
		हाल XFS_REFC_CRC_MAGIC:
			bp->b_ops = &xfs_refcountbt_buf_ops;
			अवरोध;
		शेष:
			warnmsg = "Bad btree block magic!";
			अवरोध;
		पूर्ण
		अवरोध;
	हाल XFS_BLFT_AGF_BUF:
		अगर (magic32 != XFS_AGF_MAGIC) अणु
			warnmsg = "Bad AGF block magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_agf_buf_ops;
		अवरोध;
	हाल XFS_BLFT_AGFL_BUF:
		अगर (magic32 != XFS_AGFL_MAGIC) अणु
			warnmsg = "Bad AGFL block magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_agfl_buf_ops;
		अवरोध;
	हाल XFS_BLFT_AGI_BUF:
		अगर (magic32 != XFS_AGI_MAGIC) अणु
			warnmsg = "Bad AGI block magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_agi_buf_ops;
		अवरोध;
	हाल XFS_BLFT_UDQUOT_BUF:
	हाल XFS_BLFT_PDQUOT_BUF:
	हाल XFS_BLFT_GDQUOT_BUF:
#अगर_घोषित CONFIG_XFS_QUOTA
		अगर (magic16 != XFS_DQUOT_MAGIC) अणु
			warnmsg = "Bad DQUOT block magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_dquot_buf_ops;
#अन्यथा
		xfs_alert(mp,
	"Trying to recover dquots without QUOTA support built in!");
		ASSERT(0);
#पूर्ण_अगर
		अवरोध;
	हाल XFS_BLFT_DINO_BUF:
		अगर (magic16 != XFS_DINODE_MAGIC) अणु
			warnmsg = "Bad INODE block magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_inode_buf_ops;
		अवरोध;
	हाल XFS_BLFT_SYMLINK_BUF:
		अगर (magic32 != XFS_SYMLINK_MAGIC) अणु
			warnmsg = "Bad symlink block magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_symlink_buf_ops;
		अवरोध;
	हाल XFS_BLFT_सूची_BLOCK_BUF:
		अगर (magic32 != XFS_सूची2_BLOCK_MAGIC &&
		    magic32 != XFS_सूची3_BLOCK_MAGIC) अणु
			warnmsg = "Bad dir block magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_dir3_block_buf_ops;
		अवरोध;
	हाल XFS_BLFT_सूची_DATA_BUF:
		अगर (magic32 != XFS_सूची2_DATA_MAGIC &&
		    magic32 != XFS_सूची3_DATA_MAGIC) अणु
			warnmsg = "Bad dir data magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_dir3_data_buf_ops;
		अवरोध;
	हाल XFS_BLFT_सूची_FREE_BUF:
		अगर (magic32 != XFS_सूची2_FREE_MAGIC &&
		    magic32 != XFS_सूची3_FREE_MAGIC) अणु
			warnmsg = "Bad dir3 free magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_dir3_मुक्त_buf_ops;
		अवरोध;
	हाल XFS_BLFT_सूची_LEAF1_BUF:
		अगर (magicda != XFS_सूची2_LEAF1_MAGIC &&
		    magicda != XFS_सूची3_LEAF1_MAGIC) अणु
			warnmsg = "Bad dir leaf1 magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_dir3_leaf1_buf_ops;
		अवरोध;
	हाल XFS_BLFT_सूची_LEAFN_BUF:
		अगर (magicda != XFS_सूची2_LEAFN_MAGIC &&
		    magicda != XFS_सूची3_LEAFN_MAGIC) अणु
			warnmsg = "Bad dir leafn magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_dir3_leafn_buf_ops;
		अवरोध;
	हाल XFS_BLFT_DA_NODE_BUF:
		अगर (magicda != XFS_DA_NODE_MAGIC &&
		    magicda != XFS_DA3_NODE_MAGIC) अणु
			warnmsg = "Bad da node magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_da3_node_buf_ops;
		अवरोध;
	हाल XFS_BLFT_ATTR_LEAF_BUF:
		अगर (magicda != XFS_ATTR_LEAF_MAGIC &&
		    magicda != XFS_ATTR3_LEAF_MAGIC) अणु
			warnmsg = "Bad attr leaf magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_attr3_leaf_buf_ops;
		अवरोध;
	हाल XFS_BLFT_ATTR_RMT_BUF:
		अगर (magic32 != XFS_ATTR3_RMT_MAGIC) अणु
			warnmsg = "Bad attr remote magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_attr3_rmt_buf_ops;
		अवरोध;
	हाल XFS_BLFT_SB_BUF:
		अगर (magic32 != XFS_SB_MAGIC) अणु
			warnmsg = "Bad SB block magic!";
			अवरोध;
		पूर्ण
		bp->b_ops = &xfs_sb_buf_ops;
		अवरोध;
#अगर_घोषित CONFIG_XFS_RT
	हाल XFS_BLFT_RTBITMAP_BUF:
	हाल XFS_BLFT_RTSUMMARY_BUF:
		/* no magic numbers क्रम verअगरication of RT buffers */
		bp->b_ops = &xfs_rtbuf_ops;
		अवरोध;
#पूर्ण_अगर /* CONFIG_XFS_RT */
	शेष:
		xfs_warn(mp, "Unknown buffer type %d!",
			 xfs_blft_from_flags(buf_f));
		अवरोध;
	पूर्ण

	/*
	 * Nothing अन्यथा to करो in the हाल of a शून्य current LSN as this means
	 * the buffer is more recent than the change in the log and will be
	 * skipped.
	 */
	अगर (current_lsn == शून्यCOMMITLSN)
		वापस;

	अगर (warnmsg) अणु
		xfs_warn(mp, warnmsg);
		ASSERT(0);
	पूर्ण

	/*
	 * We must update the metadata LSN of the buffer as it is written out to
	 * ensure that older transactions never replay over this one and corrupt
	 * the buffer. This can occur अगर log recovery is पूर्णांकerrupted at some
	 * poपूर्णांक after the current transaction completes, at which poपूर्णांक a
	 * subsequent mount starts recovery from the beginning.
	 *
	 * Write verअगरiers update the metadata LSN from log items attached to
	 * the buffer. Thereक्रमe, initialize a bli purely to carry the LSN to
	 * the verअगरier.
	 */
	अगर (bp->b_ops) अणु
		काष्ठा xfs_buf_log_item	*bip;

		bp->b_flags |= _XBF_LOGRECOVERY;
		xfs_buf_item_init(bp, mp);
		bip = bp->b_log_item;
		bip->bli_item.li_lsn = current_lsn;
	पूर्ण
पूर्ण

/*
 * Perक्रमm a 'normal' buffer recovery.  Each logged region of the
 * buffer should be copied over the corresponding region in the
 * given buffer.  The biपंचांगap in the buf log क्रमmat काष्ठाure indicates
 * where to place the logged data.
 */
STATIC व्योम
xlog_recover_करो_reg_buffer(
	काष्ठा xfs_mount		*mp,
	काष्ठा xlog_recover_item	*item,
	काष्ठा xfs_buf			*bp,
	काष्ठा xfs_buf_log_क्रमmat	*buf_f,
	xfs_lsn_t			current_lsn)
अणु
	पूर्णांक			i;
	पूर्णांक			bit;
	पूर्णांक			nbits;
	xfs_failaddr_t		fa;
	स्थिर माप_प्रकार		size_disk_dquot = माप(काष्ठा xfs_disk_dquot);

	trace_xfs_log_recover_buf_reg_buf(mp->m_log, buf_f);

	bit = 0;
	i = 1;  /* 0 is the buf क्रमmat काष्ठाure */
	जबतक (1) अणु
		bit = xfs_next_bit(buf_f->blf_data_map,
				   buf_f->blf_map_size, bit);
		अगर (bit == -1)
			अवरोध;
		nbits = xfs_contig_bits(buf_f->blf_data_map,
					buf_f->blf_map_size, bit);
		ASSERT(nbits > 0);
		ASSERT(item->ri_buf[i].i_addr != शून्य);
		ASSERT(item->ri_buf[i].i_len % XFS_BLF_CHUNK == 0);
		ASSERT(BBTOB(bp->b_length) >=
		       ((uपूर्णांक)bit << XFS_BLF_SHIFT) + (nbits << XFS_BLF_SHIFT));

		/*
		 * The dirty regions logged in the buffer, even though
		 * contiguous, may span multiple chunks. This is because the
		 * dirty region may span a physical page boundary in a buffer
		 * and hence be split पूर्णांकo two separate vectors क्रम writing पूर्णांकo
		 * the log. Hence we need to trim nbits back to the length of
		 * the current region being copied out of the log.
		 */
		अगर (item->ri_buf[i].i_len < (nbits << XFS_BLF_SHIFT))
			nbits = item->ri_buf[i].i_len >> XFS_BLF_SHIFT;

		/*
		 * Do a sanity check अगर this is a dquot buffer. Just checking
		 * the first dquot in the buffer should करो. XXXThis is
		 * probably a good thing to करो क्रम other buf types also.
		 */
		fa = शून्य;
		अगर (buf_f->blf_flags &
		   (XFS_BLF_UDQUOT_BUF|XFS_BLF_PDQUOT_BUF|XFS_BLF_GDQUOT_BUF)) अणु
			अगर (item->ri_buf[i].i_addr == शून्य) अणु
				xfs_alert(mp,
					"XFS: NULL dquot in %s.", __func__);
				जाओ next;
			पूर्ण
			अगर (item->ri_buf[i].i_len < size_disk_dquot) अणु
				xfs_alert(mp,
					"XFS: dquot too small (%d) in %s.",
					item->ri_buf[i].i_len, __func__);
				जाओ next;
			पूर्ण
			fa = xfs_dquot_verअगरy(mp, item->ri_buf[i].i_addr, -1);
			अगर (fa) अणु
				xfs_alert(mp,
	"dquot corrupt at %pS trying to replay into block 0x%llx",
					fa, bp->b_bn);
				जाओ next;
			पूर्ण
		पूर्ण

		स_नकल(xfs_buf_offset(bp,
			(uपूर्णांक)bit << XFS_BLF_SHIFT),	/* dest */
			item->ri_buf[i].i_addr,		/* source */
			nbits<<XFS_BLF_SHIFT);		/* length */
 next:
		i++;
		bit += nbits;
	पूर्ण

	/* Shouldn't be any more regions */
	ASSERT(i == item->ri_total);

	xlog_recover_validate_buf_type(mp, bp, buf_f, current_lsn);
पूर्ण

/*
 * Perक्रमm a dquot buffer recovery.
 * Simple algorithm: अगर we have found a QUOTAOFF log item of the same type
 * (ie. USR or GRP), then just toss this buffer away; करोn't recover it.
 * Else, treat it as a regular buffer and करो recovery.
 *
 * Return false अगर the buffer was tossed and true अगर we recovered the buffer to
 * indicate to the caller अगर the buffer needs writing.
 */
STATIC bool
xlog_recover_करो_dquot_buffer(
	काष्ठा xfs_mount		*mp,
	काष्ठा xlog			*log,
	काष्ठा xlog_recover_item	*item,
	काष्ठा xfs_buf			*bp,
	काष्ठा xfs_buf_log_क्रमmat	*buf_f)
अणु
	uपूर्णांक			type;

	trace_xfs_log_recover_buf_dquot_buf(log, buf_f);

	/*
	 * Fileप्रणालीs are required to send in quota flags at mount समय.
	 */
	अगर (!mp->m_qflags)
		वापस false;

	type = 0;
	अगर (buf_f->blf_flags & XFS_BLF_UDQUOT_BUF)
		type |= XFS_DQTYPE_USER;
	अगर (buf_f->blf_flags & XFS_BLF_PDQUOT_BUF)
		type |= XFS_DQTYPE_PROJ;
	अगर (buf_f->blf_flags & XFS_BLF_GDQUOT_BUF)
		type |= XFS_DQTYPE_GROUP;
	/*
	 * This type of quotas was turned off, so ignore this buffer
	 */
	अगर (log->l_quotaoffs_flag & type)
		वापस false;

	xlog_recover_करो_reg_buffer(mp, item, bp, buf_f, शून्यCOMMITLSN);
	वापस true;
पूर्ण

/*
 * Perक्रमm recovery क्रम a buffer full of inodes.  In these buffers, the only
 * data which should be recovered is that which corresponds to the
 * di_next_unlinked poपूर्णांकers in the on disk inode काष्ठाures.  The rest of the
 * data क्रम the inodes is always logged through the inodes themselves rather
 * than the inode buffer and is recovered in xlog_recover_inode_pass2().
 *
 * The only समय when buffers full of inodes are fully recovered is when the
 * buffer is full of newly allocated inodes.  In this हाल the buffer will
 * not be marked as an inode buffer and so will be sent to
 * xlog_recover_करो_reg_buffer() below during recovery.
 */
STATIC पूर्णांक
xlog_recover_करो_inode_buffer(
	काष्ठा xfs_mount		*mp,
	काष्ठा xlog_recover_item	*item,
	काष्ठा xfs_buf			*bp,
	काष्ठा xfs_buf_log_क्रमmat	*buf_f)
अणु
	पूर्णांक				i;
	पूर्णांक				item_index = 0;
	पूर्णांक				bit = 0;
	पूर्णांक				nbits = 0;
	पूर्णांक				reg_buf_offset = 0;
	पूर्णांक				reg_buf_bytes = 0;
	पूर्णांक				next_unlinked_offset;
	पूर्णांक				inodes_per_buf;
	xfs_agino_t			*logged_nextp;
	xfs_agino_t			*buffer_nextp;

	trace_xfs_log_recover_buf_inode_buf(mp->m_log, buf_f);

	/*
	 * Post recovery validation only works properly on CRC enabled
	 * fileप्रणालीs.
	 */
	अगर (xfs_sb_version_hascrc(&mp->m_sb))
		bp->b_ops = &xfs_inode_buf_ops;

	inodes_per_buf = BBTOB(bp->b_length) >> mp->m_sb.sb_inodelog;
	क्रम (i = 0; i < inodes_per_buf; i++) अणु
		next_unlinked_offset = (i * mp->m_sb.sb_inodesize) +
			दुरत्व(xfs_dinode_t, di_next_unlinked);

		जबतक (next_unlinked_offset >=
		       (reg_buf_offset + reg_buf_bytes)) अणु
			/*
			 * The next di_next_unlinked field is beyond
			 * the current logged region.  Find the next
			 * logged region that contains or is beyond
			 * the current di_next_unlinked field.
			 */
			bit += nbits;
			bit = xfs_next_bit(buf_f->blf_data_map,
					   buf_f->blf_map_size, bit);

			/*
			 * If there are no more logged regions in the
			 * buffer, then we're करोne.
			 */
			अगर (bit == -1)
				वापस 0;

			nbits = xfs_contig_bits(buf_f->blf_data_map,
						buf_f->blf_map_size, bit);
			ASSERT(nbits > 0);
			reg_buf_offset = bit << XFS_BLF_SHIFT;
			reg_buf_bytes = nbits << XFS_BLF_SHIFT;
			item_index++;
		पूर्ण

		/*
		 * If the current logged region starts after the current
		 * di_next_unlinked field, then move on to the next
		 * di_next_unlinked field.
		 */
		अगर (next_unlinked_offset < reg_buf_offset)
			जारी;

		ASSERT(item->ri_buf[item_index].i_addr != शून्य);
		ASSERT((item->ri_buf[item_index].i_len % XFS_BLF_CHUNK) == 0);
		ASSERT((reg_buf_offset + reg_buf_bytes) <= BBTOB(bp->b_length));

		/*
		 * The current logged region contains a copy of the
		 * current di_next_unlinked field.  Extract its value
		 * and copy it to the buffer copy.
		 */
		logged_nextp = item->ri_buf[item_index].i_addr +
				next_unlinked_offset - reg_buf_offset;
		अगर (XFS_IS_CORRUPT(mp, *logged_nextp == 0)) अणु
			xfs_alert(mp,
		"Bad inode buffer log record (ptr = "PTR_FMT", bp = "PTR_FMT"). "
		"Trying to replay bad (0) inode di_next_unlinked field.",
				item, bp);
			वापस -EFSCORRUPTED;
		पूर्ण

		buffer_nextp = xfs_buf_offset(bp, next_unlinked_offset);
		*buffer_nextp = *logged_nextp;

		/*
		 * If necessary, recalculate the CRC in the on-disk inode. We
		 * have to leave the inode in a consistent state क्रम whoever
		 * पढ़ोs it next....
		 */
		xfs_dinode_calc_crc(mp,
				xfs_buf_offset(bp, i * mp->m_sb.sb_inodesize));

	पूर्ण

	वापस 0;
पूर्ण

/*
 * V5 fileप्रणालीs know the age of the buffer on disk being recovered. We can
 * have newer objects on disk than we are replaying, and so क्रम these हालs we
 * करोn't want to replay the current change as that will make the buffer contents
 * temporarily invalid on disk.
 *
 * The magic number might not match the buffer type we are going to recover
 * (e.g. पुनः_स्मृतिated blocks), so we ignore the xfs_buf_log_क्रमmat flags.  Hence
 * extract the LSN of the existing object in the buffer based on it's current
 * magic number.  If we करोn't recognise the magic number in the buffer, then
 * वापस a LSN of -1 so that the caller knows it was an unrecognised block and
 * so can recover the buffer.
 *
 * Note: we cannot rely solely on magic number matches to determine that the
 * buffer has a valid LSN - we also need to verअगरy that it beदीर्घs to this
 * fileप्रणाली, so we need to extract the object's LSN and compare it to that
 * which we पढ़ो from the superblock. If the UUIDs करोn't match, then we've got a
 * stale metadata block from an old fileप्रणाली instance that we need to recover
 * over the top of.
 */
अटल xfs_lsn_t
xlog_recover_get_buf_lsn(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_buf		*bp)
अणु
	uपूर्णांक32_t		magic32;
	uपूर्णांक16_t		magic16;
	uपूर्णांक16_t		magicda;
	व्योम			*blk = bp->b_addr;
	uuid_t			*uuid;
	xfs_lsn_t		lsn = -1;

	/* v4 fileप्रणालीs always recover immediately */
	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		जाओ recover_immediately;

	magic32 = be32_to_cpu(*(__be32 *)blk);
	चयन (magic32) अणु
	हाल XFS_ABTB_CRC_MAGIC:
	हाल XFS_ABTC_CRC_MAGIC:
	हाल XFS_ABTB_MAGIC:
	हाल XFS_ABTC_MAGIC:
	हाल XFS_RMAP_CRC_MAGIC:
	हाल XFS_REFC_CRC_MAGIC:
	हाल XFS_FIBT_CRC_MAGIC:
	हाल XFS_FIBT_MAGIC:
	हाल XFS_IBT_CRC_MAGIC:
	हाल XFS_IBT_MAGIC: अणु
		काष्ठा xfs_btree_block *btb = blk;

		lsn = be64_to_cpu(btb->bb_u.s.bb_lsn);
		uuid = &btb->bb_u.s.bb_uuid;
		अवरोध;
	पूर्ण
	हाल XFS_BMAP_CRC_MAGIC:
	हाल XFS_BMAP_MAGIC: अणु
		काष्ठा xfs_btree_block *btb = blk;

		lsn = be64_to_cpu(btb->bb_u.l.bb_lsn);
		uuid = &btb->bb_u.l.bb_uuid;
		अवरोध;
	पूर्ण
	हाल XFS_AGF_MAGIC:
		lsn = be64_to_cpu(((काष्ठा xfs_agf *)blk)->agf_lsn);
		uuid = &((काष्ठा xfs_agf *)blk)->agf_uuid;
		अवरोध;
	हाल XFS_AGFL_MAGIC:
		lsn = be64_to_cpu(((काष्ठा xfs_agfl *)blk)->agfl_lsn);
		uuid = &((काष्ठा xfs_agfl *)blk)->agfl_uuid;
		अवरोध;
	हाल XFS_AGI_MAGIC:
		lsn = be64_to_cpu(((काष्ठा xfs_agi *)blk)->agi_lsn);
		uuid = &((काष्ठा xfs_agi *)blk)->agi_uuid;
		अवरोध;
	हाल XFS_SYMLINK_MAGIC:
		lsn = be64_to_cpu(((काष्ठा xfs_dsymlink_hdr *)blk)->sl_lsn);
		uuid = &((काष्ठा xfs_dsymlink_hdr *)blk)->sl_uuid;
		अवरोध;
	हाल XFS_सूची3_BLOCK_MAGIC:
	हाल XFS_सूची3_DATA_MAGIC:
	हाल XFS_सूची3_FREE_MAGIC:
		lsn = be64_to_cpu(((काष्ठा xfs_dir3_blk_hdr *)blk)->lsn);
		uuid = &((काष्ठा xfs_dir3_blk_hdr *)blk)->uuid;
		अवरोध;
	हाल XFS_ATTR3_RMT_MAGIC:
		/*
		 * Remote attr blocks are written synchronously, rather than
		 * being logged. That means they करो not contain a valid LSN
		 * (i.e. transactionally ordered) in them, and hence any समय we
		 * see a buffer to replay over the top of a remote attribute
		 * block we should simply करो so.
		 */
		जाओ recover_immediately;
	हाल XFS_SB_MAGIC:
		/*
		 * superblock uuids are magic. We may or may not have a
		 * sb_meta_uuid on disk, but it will be set in the in-core
		 * superblock. We set the uuid poपूर्णांकer क्रम verअगरication
		 * according to the superblock feature mask to ensure we check
		 * the relevant UUID in the superblock.
		 */
		lsn = be64_to_cpu(((काष्ठा xfs_dsb *)blk)->sb_lsn);
		अगर (xfs_sb_version_hयंत्रetauuid(&mp->m_sb))
			uuid = &((काष्ठा xfs_dsb *)blk)->sb_meta_uuid;
		अन्यथा
			uuid = &((काष्ठा xfs_dsb *)blk)->sb_uuid;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (lsn != (xfs_lsn_t)-1) अणु
		अगर (!uuid_equal(&mp->m_sb.sb_meta_uuid, uuid))
			जाओ recover_immediately;
		वापस lsn;
	पूर्ण

	magicda = be16_to_cpu(((काष्ठा xfs_da_blkinfo *)blk)->magic);
	चयन (magicda) अणु
	हाल XFS_सूची3_LEAF1_MAGIC:
	हाल XFS_सूची3_LEAFN_MAGIC:
	हाल XFS_DA3_NODE_MAGIC:
		lsn = be64_to_cpu(((काष्ठा xfs_da3_blkinfo *)blk)->lsn);
		uuid = &((काष्ठा xfs_da3_blkinfo *)blk)->uuid;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (lsn != (xfs_lsn_t)-1) अणु
		अगर (!uuid_equal(&mp->m_sb.sb_uuid, uuid))
			जाओ recover_immediately;
		वापस lsn;
	पूर्ण

	/*
	 * We करो inभागidual object checks on dquot and inode buffers as they
	 * have their own inभागidual LSN records. Also, we could have a stale
	 * buffer here, so we have to at least recognise these buffer types.
	 *
	 * A notd complनिकासy here is inode unlinked list processing - it logs
	 * the inode directly in the buffer, but we करोn't know which inodes have
	 * been modअगरied, and there is no global buffer LSN. Hence we need to
	 * recover all inode buffer types immediately. This problem will be
	 * fixed by logical logging of the unlinked list modअगरications.
	 */
	magic16 = be16_to_cpu(*(__be16 *)blk);
	चयन (magic16) अणु
	हाल XFS_DQUOT_MAGIC:
	हाल XFS_DINODE_MAGIC:
		जाओ recover_immediately;
	शेष:
		अवरोध;
	पूर्ण

	/* unknown buffer contents, recover immediately */

recover_immediately:
	वापस (xfs_lsn_t)-1;

पूर्ण

/*
 * This routine replays a modअगरication made to a buffer at runसमय.
 * There are actually two types of buffer, regular and inode, which
 * are handled dअगरferently.  Inode buffers are handled dअगरferently
 * in that we only recover a specअगरic set of data from them, namely
 * the inode di_next_unlinked fields.  This is because all other inode
 * data is actually logged via inode records and any data we replay
 * here which overlaps that may be stale.
 *
 * When meta-data buffers are मुक्तd at run समय we log a buffer item
 * with the XFS_BLF_CANCEL bit set to indicate that previous copies
 * of the buffer in the log should not be replayed at recovery समय.
 * This is so that अगर the blocks covered by the buffer are reused क्रम
 * file data beक्रमe we crash we करोn't end up replaying old, मुक्तd
 * meta-data पूर्णांकo a user's file.
 *
 * To handle the cancellation of buffer log items, we make two passes
 * over the log during recovery.  During the first we build a table of
 * those buffers which have been cancelled, and during the second we
 * only replay those buffers which करो not have corresponding cancel
 * records in the table.  See xlog_recover_buf_pass[1,2] above
 * क्रम more details on the implementation of the table of cancel records.
 */
STATIC पूर्णांक
xlog_recover_buf_commit_pass2(
	काष्ठा xlog			*log,
	काष्ठा list_head		*buffer_list,
	काष्ठा xlog_recover_item	*item,
	xfs_lsn_t			current_lsn)
अणु
	काष्ठा xfs_buf_log_क्रमmat	*buf_f = item->ri_buf[0].i_addr;
	काष्ठा xfs_mount		*mp = log->l_mp;
	काष्ठा xfs_buf			*bp;
	पूर्णांक				error;
	uपूर्णांक				buf_flags;
	xfs_lsn_t			lsn;

	/*
	 * In this pass we only want to recover all the buffers which have
	 * not been cancelled and are not cancellation buffers themselves.
	 */
	अगर (buf_f->blf_flags & XFS_BLF_CANCEL) अणु
		अगर (xlog_put_buffer_cancelled(log, buf_f->blf_blkno,
				buf_f->blf_len))
			जाओ cancelled;
	पूर्ण अन्यथा अणु

		अगर (xlog_is_buffer_cancelled(log, buf_f->blf_blkno,
				buf_f->blf_len))
			जाओ cancelled;
	पूर्ण

	trace_xfs_log_recover_buf_recover(log, buf_f);

	buf_flags = 0;
	अगर (buf_f->blf_flags & XFS_BLF_INODE_BUF)
		buf_flags |= XBF_UNMAPPED;

	error = xfs_buf_पढ़ो(mp->m_ddev_targp, buf_f->blf_blkno, buf_f->blf_len,
			  buf_flags, &bp, शून्य);
	अगर (error)
		वापस error;

	/*
	 * Recover the buffer only अगर we get an LSN from it and it's less than
	 * the lsn of the transaction we are replaying.
	 *
	 * Note that we have to be extremely careful of पढ़ोahead here.
	 * Readahead करोes not attach verfiers to the buffers so अगर we करोn't
	 * actually करो any replay after पढ़ोahead because of the LSN we found
	 * in the buffer अगर more recent than that current transaction then we
	 * need to attach the verअगरier directly. Failure to करो so can lead to
	 * future recovery actions (e.g. EFI and unlinked list recovery) can
	 * operate on the buffers and they won't get the verअगरier attached. This
	 * can lead to blocks on disk having the correct content but a stale
	 * CRC.
	 *
	 * It is safe to assume these clean buffers are currently up to date.
	 * If the buffer is dirtied by a later transaction being replayed, then
	 * the verअगरier will be reset to match whatever recover turns that
	 * buffer पूर्णांकo.
	 */
	lsn = xlog_recover_get_buf_lsn(mp, bp);
	अगर (lsn && lsn != -1 && XFS_LSN_CMP(lsn, current_lsn) >= 0) अणु
		trace_xfs_log_recover_buf_skip(log, buf_f);
		xlog_recover_validate_buf_type(mp, bp, buf_f, शून्यCOMMITLSN);
		जाओ out_release;
	पूर्ण

	अगर (buf_f->blf_flags & XFS_BLF_INODE_BUF) अणु
		error = xlog_recover_करो_inode_buffer(mp, item, bp, buf_f);
		अगर (error)
			जाओ out_release;
	पूर्ण अन्यथा अगर (buf_f->blf_flags &
		  (XFS_BLF_UDQUOT_BUF|XFS_BLF_PDQUOT_BUF|XFS_BLF_GDQUOT_BUF)) अणु
		bool	dirty;

		dirty = xlog_recover_करो_dquot_buffer(mp, log, item, bp, buf_f);
		अगर (!dirty)
			जाओ out_release;
	पूर्ण अन्यथा अणु
		xlog_recover_करो_reg_buffer(mp, item, bp, buf_f, current_lsn);
	पूर्ण

	/*
	 * Perक्रमm delayed ग_लिखो on the buffer.  Asynchronous ग_लिखोs will be
	 * slower when taking पूर्णांकo account all the buffers to be flushed.
	 *
	 * Also make sure that only inode buffers with good sizes stay in
	 * the buffer cache.  The kernel moves inodes in buffers of 1 block
	 * or inode_cluster_size bytes, whichever is bigger.  The inode
	 * buffers in the log can be a dअगरferent size अगर the log was generated
	 * by an older kernel using unclustered inode buffers or a newer kernel
	 * running with a dअगरferent inode cluster size.  Regardless, अगर
	 * the inode buffer size isn't max(blocksize, inode_cluster_size)
	 * क्रम *our* value of inode_cluster_size, then we need to keep
	 * the buffer out of the buffer cache so that the buffer won't
	 * overlap with future पढ़ोs of those inodes.
	 */
	अगर (XFS_DINODE_MAGIC ==
	    be16_to_cpu(*((__be16 *)xfs_buf_offset(bp, 0))) &&
	    (BBTOB(bp->b_length) != M_IGEO(log->l_mp)->inode_cluster_size)) अणु
		xfs_buf_stale(bp);
		error = xfs_bग_लिखो(bp);
	पूर्ण अन्यथा अणु
		ASSERT(bp->b_mount == mp);
		bp->b_flags |= _XBF_LOGRECOVERY;
		xfs_buf_delwri_queue(bp, buffer_list);
	पूर्ण

out_release:
	xfs_buf_rअन्यथा(bp);
	वापस error;
cancelled:
	trace_xfs_log_recover_buf_cancel(log, buf_f);
	वापस 0;
पूर्ण

स्थिर काष्ठा xlog_recover_item_ops xlog_buf_item_ops = अणु
	.item_type		= XFS_LI_BUF,
	.reorder		= xlog_recover_buf_reorder,
	.ra_pass2		= xlog_recover_buf_ra_pass2,
	.commit_pass1		= xlog_recover_buf_commit_pass1,
	.commit_pass2		= xlog_recover_buf_commit_pass2,
पूर्ण;
