<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
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
#समावेश "xfs_btree.h"
#समावेश "xfs_ialloc.h"
#समावेश "xfs_ialloc_btree.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_buf_item.h"
#समावेश "xfs_icreate_item.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_log.h"
#समावेश "xfs_rmap.h"

/*
 * Lookup a record by ino in the btree given by cur.
 */
पूर्णांक					/* error */
xfs_inobt_lookup(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_agino_t		ino,	/* starting inode of chunk */
	xfs_lookup_t		dir,	/* <=, >=, == */
	पूर्णांक			*stat)	/* success/failure */
अणु
	cur->bc_rec.i.ir_startino = ino;
	cur->bc_rec.i.ir_holemask = 0;
	cur->bc_rec.i.ir_count = 0;
	cur->bc_rec.i.ir_मुक्तcount = 0;
	cur->bc_rec.i.ir_मुक्त = 0;
	वापस xfs_btree_lookup(cur, dir, stat);
पूर्ण

/*
 * Update the record referred to by cur to the value given.
 * This either works (वापस 0) or माला_लो an EFSCORRUPTED error.
 */
STATIC पूर्णांक				/* error */
xfs_inobt_update(
	काष्ठा xfs_btree_cur	*cur,	/* btree cursor */
	xfs_inobt_rec_incore_t	*irec)	/* btree record */
अणु
	जोड़ xfs_btree_rec	rec;

	rec.inobt.ir_startino = cpu_to_be32(irec->ir_startino);
	अगर (xfs_sb_version_hassparseinodes(&cur->bc_mp->m_sb)) अणु
		rec.inobt.ir_u.sp.ir_holemask = cpu_to_be16(irec->ir_holemask);
		rec.inobt.ir_u.sp.ir_count = irec->ir_count;
		rec.inobt.ir_u.sp.ir_मुक्तcount = irec->ir_मुक्तcount;
	पूर्ण अन्यथा अणु
		/* ir_holemask/ir_count not supported on-disk */
		rec.inobt.ir_u.f.ir_मुक्तcount = cpu_to_be32(irec->ir_मुक्तcount);
	पूर्ण
	rec.inobt.ir_मुक्त = cpu_to_be64(irec->ir_मुक्त);
	वापस xfs_btree_update(cur, &rec);
पूर्ण

/* Convert on-disk btree record to incore inobt record. */
व्योम
xfs_inobt_btrec_to_irec(
	काष्ठा xfs_mount		*mp,
	जोड़ xfs_btree_rec		*rec,
	काष्ठा xfs_inobt_rec_incore	*irec)
अणु
	irec->ir_startino = be32_to_cpu(rec->inobt.ir_startino);
	अगर (xfs_sb_version_hassparseinodes(&mp->m_sb)) अणु
		irec->ir_holemask = be16_to_cpu(rec->inobt.ir_u.sp.ir_holemask);
		irec->ir_count = rec->inobt.ir_u.sp.ir_count;
		irec->ir_मुक्तcount = rec->inobt.ir_u.sp.ir_मुक्तcount;
	पूर्ण अन्यथा अणु
		/*
		 * ir_holemask/ir_count not supported on-disk. Fill in hardcoded
		 * values क्रम full inode chunks.
		 */
		irec->ir_holemask = XFS_INOBT_HOLEMASK_FULL;
		irec->ir_count = XFS_INODES_PER_CHUNK;
		irec->ir_मुक्तcount =
				be32_to_cpu(rec->inobt.ir_u.f.ir_मुक्तcount);
	पूर्ण
	irec->ir_मुक्त = be64_to_cpu(rec->inobt.ir_मुक्त);
पूर्ण

/*
 * Get the data from the poपूर्णांकed-to record.
 */
पूर्णांक
xfs_inobt_get_rec(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_inobt_rec_incore	*irec,
	पूर्णांक				*stat)
अणु
	काष्ठा xfs_mount		*mp = cur->bc_mp;
	xfs_agnumber_t			agno = cur->bc_ag.agno;
	जोड़ xfs_btree_rec		*rec;
	पूर्णांक				error;
	uपूर्णांक64_t			realमुक्त;

	error = xfs_btree_get_rec(cur, &rec, stat);
	अगर (error || *stat == 0)
		वापस error;

	xfs_inobt_btrec_to_irec(mp, rec, irec);

	अगर (!xfs_verअगरy_agino(mp, agno, irec->ir_startino))
		जाओ out_bad_rec;
	अगर (irec->ir_count < XFS_INODES_PER_HOLEMASK_BIT ||
	    irec->ir_count > XFS_INODES_PER_CHUNK)
		जाओ out_bad_rec;
	अगर (irec->ir_मुक्तcount > XFS_INODES_PER_CHUNK)
		जाओ out_bad_rec;

	/* अगर there are no holes, वापस the first available offset */
	अगर (!xfs_inobt_issparse(irec->ir_holemask))
		realमुक्त = irec->ir_मुक्त;
	अन्यथा
		realमुक्त = irec->ir_मुक्त & xfs_inobt_irec_to_allocmask(irec);
	अगर (hweight64(realमुक्त) != irec->ir_मुक्तcount)
		जाओ out_bad_rec;

	वापस 0;

out_bad_rec:
	xfs_warn(mp,
		"%s Inode BTree record corruption in AG %d detected!",
		cur->bc_btnum == XFS_BTNUM_INO ? "Used" : "Free", agno);
	xfs_warn(mp,
"start inode 0x%x, count 0x%x, free 0x%x freemask 0x%llx, holemask 0x%x",
		irec->ir_startino, irec->ir_count, irec->ir_मुक्तcount,
		irec->ir_मुक्त, irec->ir_holemask);
	वापस -EFSCORRUPTED;
पूर्ण

/*
 * Insert a single inobt record. Cursor must alपढ़ोy poपूर्णांक to desired location.
 */
पूर्णांक
xfs_inobt_insert_rec(
	काष्ठा xfs_btree_cur	*cur,
	uपूर्णांक16_t		holemask,
	uपूर्णांक8_t			count,
	पूर्णांक32_t			मुक्तcount,
	xfs_inoमुक्त_t		मुक्त,
	पूर्णांक			*stat)
अणु
	cur->bc_rec.i.ir_holemask = holemask;
	cur->bc_rec.i.ir_count = count;
	cur->bc_rec.i.ir_मुक्तcount = मुक्तcount;
	cur->bc_rec.i.ir_मुक्त = मुक्त;
	वापस xfs_btree_insert(cur, stat);
पूर्ण

/*
 * Insert records describing a newly allocated inode chunk पूर्णांकo the inobt.
 */
STATIC पूर्णांक
xfs_inobt_insert(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp,
	xfs_agino_t		newino,
	xfs_agino_t		newlen,
	xfs_btnum_t		btnum)
अणु
	काष्ठा xfs_btree_cur	*cur;
	काष्ठा xfs_agi		*agi = agbp->b_addr;
	xfs_agnumber_t		agno = be32_to_cpu(agi->agi_seqno);
	xfs_agino_t		thisino;
	पूर्णांक			i;
	पूर्णांक			error;

	cur = xfs_inobt_init_cursor(mp, tp, agbp, agno, btnum);

	क्रम (thisino = newino;
	     thisino < newino + newlen;
	     thisino += XFS_INODES_PER_CHUNK) अणु
		error = xfs_inobt_lookup(cur, thisino, XFS_LOOKUP_EQ, &i);
		अगर (error) अणु
			xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);
			वापस error;
		पूर्ण
		ASSERT(i == 0);

		error = xfs_inobt_insert_rec(cur, XFS_INOBT_HOLEMASK_FULL,
					     XFS_INODES_PER_CHUNK,
					     XFS_INODES_PER_CHUNK,
					     XFS_INOBT_ALL_FREE, &i);
		अगर (error) अणु
			xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);
			वापस error;
		पूर्ण
		ASSERT(i == 1);
	पूर्ण

	xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);

	वापस 0;
पूर्ण

/*
 * Verअगरy that the number of मुक्त inodes in the AGI is correct.
 */
#अगर_घोषित DEBUG
STATIC पूर्णांक
xfs_check_agi_मुक्तcount(
	काष्ठा xfs_btree_cur	*cur,
	काष्ठा xfs_agi		*agi)
अणु
	अगर (cur->bc_nlevels == 1) अणु
		xfs_inobt_rec_incore_t rec;
		पूर्णांक		मुक्तcount = 0;
		पूर्णांक		error;
		पूर्णांक		i;

		error = xfs_inobt_lookup(cur, 0, XFS_LOOKUP_GE, &i);
		अगर (error)
			वापस error;

		करो अणु
			error = xfs_inobt_get_rec(cur, &rec, &i);
			अगर (error)
				वापस error;

			अगर (i) अणु
				मुक्तcount += rec.ir_मुक्तcount;
				error = xfs_btree_increment(cur, 0, &i);
				अगर (error)
					वापस error;
			पूर्ण
		पूर्ण जबतक (i == 1);

		अगर (!XFS_FORCED_SHUTDOWN(cur->bc_mp))
			ASSERT(मुक्तcount == be32_to_cpu(agi->agi_मुक्तcount));
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा xfs_check_agi_मुक्तcount(cur, agi)	0
#पूर्ण_अगर

/*
 * Initialise a new set of inodes. When called without a transaction context
 * (e.g. from recovery) we initiate a delayed ग_लिखो of the inode buffers rather
 * than logging them (which in a transaction context माला_दो them पूर्णांकo the AIL
 * क्रम ग_लिखोback rather than the xfsbufd queue).
 */
पूर्णांक
xfs_ialloc_inode_init(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	काष्ठा list_head	*buffer_list,
	पूर्णांक			icount,
	xfs_agnumber_t		agno,
	xfs_agblock_t		agbno,
	xfs_agblock_t		length,
	अचिन्हित पूर्णांक		gen)
अणु
	काष्ठा xfs_buf		*fbuf;
	काष्ठा xfs_dinode	*मुक्त;
	पूर्णांक			nbufs;
	पूर्णांक			version;
	पूर्णांक			i, j;
	xfs_daddr_t		d;
	xfs_ino_t		ino = 0;
	पूर्णांक			error;

	/*
	 * Loop over the new block(s), filling in the inodes.  For small block
	 * sizes, manipulate the inodes in buffers  which are multiples of the
	 * blocks size.
	 */
	nbufs = length / M_IGEO(mp)->blocks_per_cluster;

	/*
	 * Figure out what version number to use in the inodes we create.  If
	 * the superblock version has caught up to the one that supports the new
	 * inode क्रमmat, then use the new inode version.  Otherwise use the old
	 * version so that old kernels will जारी to be able to use the file
	 * प्रणाली.
	 *
	 * For v3 inodes, we also need to ग_लिखो the inode number पूर्णांकo the inode,
	 * so calculate the first inode number of the chunk here as
	 * XFS_AGB_TO_AGINO() only works within a fileप्रणाली block, not
	 * across multiple fileप्रणाली blocks (such as a cluster) and so cannot
	 * be used in the cluster buffer loop below.
	 *
	 * Further, because we are writing the inode directly पूर्णांकo the buffer
	 * and calculating a CRC on the entire inode, we have ot log the entire
	 * inode so that the entire range the CRC covers is present in the log.
	 * That means क्रम v3 inode we log the entire buffer rather than just the
	 * inode cores.
	 */
	अगर (xfs_sb_version_has_v3inode(&mp->m_sb)) अणु
		version = 3;
		ino = XFS_AGINO_TO_INO(mp, agno, XFS_AGB_TO_AGINO(mp, agbno));

		/*
		 * log the initialisation that is about to take place as an
		 * logical operation. This means the transaction करोes not
		 * need to log the physical changes to the inode buffers as log
		 * recovery will know what initialisation is actually needed.
		 * Hence we only need to log the buffers as "ordered" buffers so
		 * they track in the AIL as अगर they were physically logged.
		 */
		अगर (tp)
			xfs_icreate_log(tp, agno, agbno, icount,
					mp->m_sb.sb_inodesize, length, gen);
	पूर्ण अन्यथा
		version = 2;

	क्रम (j = 0; j < nbufs; j++) अणु
		/*
		 * Get the block.
		 */
		d = XFS_AGB_TO_DADDR(mp, agno, agbno +
				(j * M_IGEO(mp)->blocks_per_cluster));
		error = xfs_trans_get_buf(tp, mp->m_ddev_targp, d,
				mp->m_bsize * M_IGEO(mp)->blocks_per_cluster,
				XBF_UNMAPPED, &fbuf);
		अगर (error)
			वापस error;

		/* Initialize the inode buffers and log them appropriately. */
		fbuf->b_ops = &xfs_inode_buf_ops;
		xfs_buf_zero(fbuf, 0, BBTOB(fbuf->b_length));
		क्रम (i = 0; i < M_IGEO(mp)->inodes_per_cluster; i++) अणु
			पूर्णांक	ioffset = i << mp->m_sb.sb_inodelog;
			uपूर्णांक	isize = XFS_DINODE_SIZE(&mp->m_sb);

			मुक्त = xfs_make_iptr(mp, fbuf, i);
			मुक्त->di_magic = cpu_to_be16(XFS_DINODE_MAGIC);
			मुक्त->di_version = version;
			मुक्त->di_gen = cpu_to_be32(gen);
			मुक्त->di_next_unlinked = cpu_to_be32(शून्यAGINO);

			अगर (version == 3) अणु
				मुक्त->di_ino = cpu_to_be64(ino);
				ino++;
				uuid_copy(&मुक्त->di_uuid,
					  &mp->m_sb.sb_meta_uuid);
				xfs_dinode_calc_crc(mp, मुक्त);
			पूर्ण अन्यथा अगर (tp) अणु
				/* just log the inode core */
				xfs_trans_log_buf(tp, fbuf, ioffset,
						  ioffset + isize - 1);
			पूर्ण
		पूर्ण

		अगर (tp) अणु
			/*
			 * Mark the buffer as an inode allocation buffer so it
			 * sticks in AIL at the poपूर्णांक of this allocation
			 * transaction. This ensures the they are on disk beक्रमe
			 * the tail of the log can be moved past this
			 * transaction (i.e. by preventing relogging from moving
			 * it क्रमward in the log).
			 */
			xfs_trans_inode_alloc_buf(tp, fbuf);
			अगर (version == 3) अणु
				/*
				 * Mark the buffer as ordered so that they are
				 * not physically logged in the transaction but
				 * still tracked in the AIL as part of the
				 * transaction and pin the log appropriately.
				 */
				xfs_trans_ordered_buf(tp, fbuf);
			पूर्ण
		पूर्ण अन्यथा अणु
			fbuf->b_flags |= XBF_DONE;
			xfs_buf_delwri_queue(fbuf, buffer_list);
			xfs_buf_rअन्यथा(fbuf);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Align startino and allocmask क्रम a recently allocated sparse chunk such that
 * they are fit क्रम insertion (or merge) पूर्णांकo the on-disk inode btrees.
 *
 * Background:
 *
 * When enabled, sparse inode support increases the inode alignment from cluster
 * size to inode chunk size. This means that the minimum range between two
 * non-adjacent inode records in the inobt is large enough क्रम a full inode
 * record. This allows क्रम cluster sized, cluster aligned block allocation
 * without need to worry about whether the resulting inode record overlaps with
 * another record in the tree. Without this basic rule, we would have to deal
 * with the consequences of overlap by potentially unकरोing recent allocations in
 * the inode allocation codepath.
 *
 * Because of this alignment rule (which is enक्रमced on mount), there are two
 * inobt possibilities क्रम newly allocated sparse chunks. One is that the
 * aligned inode record क्रम the chunk covers a range of inodes not alपढ़ोy
 * covered in the inobt (i.e., it is safe to insert a new sparse record). The
 * other is that a record alपढ़ोy exists at the aligned startino that considers
 * the newly allocated range as sparse. In the latter हाल, record content is
 * merged in hope that sparse inode chunks fill to full chunks over समय.
 */
STATIC व्योम
xfs_align_sparse_ino(
	काष्ठा xfs_mount		*mp,
	xfs_agino_t			*startino,
	uपूर्णांक16_t			*allocmask)
अणु
	xfs_agblock_t			agbno;
	xfs_agblock_t			mod;
	पूर्णांक				offset;

	agbno = XFS_AGINO_TO_AGBNO(mp, *startino);
	mod = agbno % mp->m_sb.sb_inoalignmt;
	अगर (!mod)
		वापस;

	/* calculate the inode offset and align startino */
	offset = XFS_AGB_TO_AGINO(mp, mod);
	*startino -= offset;

	/*
	 * Since startino has been aligned करोwn, left shअगरt allocmask such that
	 * it जारीs to represent the same physical inodes relative to the
	 * new startino.
	 */
	*allocmask <<= offset / XFS_INODES_PER_HOLEMASK_BIT;
पूर्ण

/*
 * Determine whether the source inode record can merge पूर्णांकo the target. Both
 * records must be sparse, the inode ranges must match and there must be no
 * allocation overlap between the records.
 */
STATIC bool
__xfs_inobt_can_merge(
	काष्ठा xfs_inobt_rec_incore	*trec,	/* tgt record */
	काष्ठा xfs_inobt_rec_incore	*srec)	/* src record */
अणु
	uपूर्णांक64_t			talloc;
	uपूर्णांक64_t			salloc;

	/* records must cover the same inode range */
	अगर (trec->ir_startino != srec->ir_startino)
		वापस false;

	/* both records must be sparse */
	अगर (!xfs_inobt_issparse(trec->ir_holemask) ||
	    !xfs_inobt_issparse(srec->ir_holemask))
		वापस false;

	/* both records must track some inodes */
	अगर (!trec->ir_count || !srec->ir_count)
		वापस false;

	/* can't exceed capacity of a full record */
	अगर (trec->ir_count + srec->ir_count > XFS_INODES_PER_CHUNK)
		वापस false;

	/* verअगरy there is no allocation overlap */
	talloc = xfs_inobt_irec_to_allocmask(trec);
	salloc = xfs_inobt_irec_to_allocmask(srec);
	अगर (talloc & salloc)
		वापस false;

	वापस true;
पूर्ण

/*
 * Merge the source inode record पूर्णांकo the target. The caller must call
 * __xfs_inobt_can_merge() to ensure the merge is valid.
 */
STATIC व्योम
__xfs_inobt_rec_merge(
	काष्ठा xfs_inobt_rec_incore	*trec,	/* target */
	काष्ठा xfs_inobt_rec_incore	*srec)	/* src */
अणु
	ASSERT(trec->ir_startino == srec->ir_startino);

	/* combine the counts */
	trec->ir_count += srec->ir_count;
	trec->ir_मुक्तcount += srec->ir_मुक्तcount;

	/*
	 * Merge the holemask and मुक्त mask. For both fields, 0 bits refer to
	 * allocated inodes. We combine the allocated ranges with bitwise AND.
	 */
	trec->ir_holemask &= srec->ir_holemask;
	trec->ir_मुक्त &= srec->ir_मुक्त;
पूर्ण

/*
 * Insert a new sparse inode chunk पूर्णांकo the associated inode btree. The inode
 * record क्रम the sparse chunk is pre-aligned to a startino that should match
 * any pre-existing sparse inode record in the tree. This allows sparse chunks
 * to fill over समय.
 *
 * This function supports two modes of handling preexisting records depending on
 * the merge flag. If merge is true, the provided record is merged with the
 * existing record and updated in place. The merged record is वापसed in nrec.
 * If merge is false, an existing record is replaced with the provided record.
 * If no preexisting record exists, the provided record is always inserted.
 *
 * It is considered corruption अगर a merge is requested and not possible. Given
 * the sparse inode alignment स्थिरraपूर्णांकs, this should never happen.
 */
STATIC पूर्णांक
xfs_inobt_insert_sprec(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_buf			*agbp,
	पूर्णांक				btnum,
	काष्ठा xfs_inobt_rec_incore	*nrec,	/* in/out: new/merged rec. */
	bool				merge)	/* merge or replace */
अणु
	काष्ठा xfs_btree_cur		*cur;
	काष्ठा xfs_agi			*agi = agbp->b_addr;
	xfs_agnumber_t			agno = be32_to_cpu(agi->agi_seqno);
	पूर्णांक				error;
	पूर्णांक				i;
	काष्ठा xfs_inobt_rec_incore	rec;

	cur = xfs_inobt_init_cursor(mp, tp, agbp, agno, btnum);

	/* the new record is pre-aligned so we know where to look */
	error = xfs_inobt_lookup(cur, nrec->ir_startino, XFS_LOOKUP_EQ, &i);
	अगर (error)
		जाओ error;
	/* अगर nothing there, insert a new record and वापस */
	अगर (i == 0) अणु
		error = xfs_inobt_insert_rec(cur, nrec->ir_holemask,
					     nrec->ir_count, nrec->ir_मुक्तcount,
					     nrec->ir_मुक्त, &i);
		अगर (error)
			जाओ error;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error;
		पूर्ण

		जाओ out;
	पूर्ण

	/*
	 * A record exists at this startino. Merge or replace the record
	 * depending on what we've been asked to करो.
	 */
	अगर (merge) अणु
		error = xfs_inobt_get_rec(cur, &rec, &i);
		अगर (error)
			जाओ error;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error;
		पूर्ण
		अगर (XFS_IS_CORRUPT(mp, rec.ir_startino != nrec->ir_startino)) अणु
			error = -EFSCORRUPTED;
			जाओ error;
		पूर्ण

		/*
		 * This should never fail. If we have coexisting records that
		 * cannot merge, something is seriously wrong.
		 */
		अगर (XFS_IS_CORRUPT(mp, !__xfs_inobt_can_merge(nrec, &rec))) अणु
			error = -EFSCORRUPTED;
			जाओ error;
		पूर्ण

		trace_xfs_irec_merge_pre(mp, agno, rec.ir_startino,
					 rec.ir_holemask, nrec->ir_startino,
					 nrec->ir_holemask);

		/* merge to nrec to output the updated record */
		__xfs_inobt_rec_merge(nrec, &rec);

		trace_xfs_irec_merge_post(mp, agno, nrec->ir_startino,
					  nrec->ir_holemask);

		error = xfs_inobt_rec_check_count(mp, nrec);
		अगर (error)
			जाओ error;
	पूर्ण

	error = xfs_inobt_update(cur, nrec);
	अगर (error)
		जाओ error;

out:
	xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
	वापस 0;
error:
	xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Allocate new inodes in the allocation group specअगरied by agbp.
 * Returns 0 अगर inodes were allocated in this AG; 1 अगर there was no space
 * in this AG; or the usual negative error code.
 */
STATIC पूर्णांक
xfs_ialloc_ag_alloc(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp)
अणु
	काष्ठा xfs_agi		*agi;
	काष्ठा xfs_alloc_arg	args;
	xfs_agnumber_t		agno;
	पूर्णांक			error;
	xfs_agino_t		newino;		/* new first inode's number */
	xfs_agino_t		newlen;		/* new number of inodes */
	पूर्णांक			isaligned = 0;	/* inode allocation at stripe */
						/* unit boundary */
	/* init. to full chunk */
	uपूर्णांक16_t		allocmask = (uपूर्णांक16_t) -1;
	काष्ठा xfs_inobt_rec_incore rec;
	काष्ठा xfs_perag	*pag;
	काष्ठा xfs_ino_geometry	*igeo = M_IGEO(tp->t_mountp);
	पूर्णांक			करो_sparse = 0;

	स_रखो(&args, 0, माप(args));
	args.tp = tp;
	args.mp = tp->t_mountp;
	args.fsbno = शून्यFSBLOCK;
	args.oinfo = XFS_RMAP_OINFO_INODES;

#अगर_घोषित DEBUG
	/* अक्रमomly करो sparse inode allocations */
	अगर (xfs_sb_version_hassparseinodes(&tp->t_mountp->m_sb) &&
	    igeo->ialloc_min_blks < igeo->ialloc_blks)
		करो_sparse = pअक्रमom_u32() & 1;
#पूर्ण_अगर

	/*
	 * Locking will ensure that we करोn't have two callers in here
	 * at one समय.
	 */
	newlen = igeo->ialloc_inos;
	अगर (igeo->maxicount &&
	    percpu_counter_पढ़ो_positive(&args.mp->m_icount) + newlen >
							igeo->maxicount)
		वापस -ENOSPC;
	args.minlen = args.maxlen = igeo->ialloc_blks;
	/*
	 * First try to allocate inodes contiguous with the last-allocated
	 * chunk of inodes.  If the fileप्रणाली is striped, this will fill
	 * an entire stripe unit with inodes.
	 */
	agi = agbp->b_addr;
	newino = be32_to_cpu(agi->agi_newino);
	agno = be32_to_cpu(agi->agi_seqno);
	args.agbno = XFS_AGINO_TO_AGBNO(args.mp, newino) +
		     igeo->ialloc_blks;
	अगर (करो_sparse)
		जाओ sparse_alloc;
	अगर (likely(newino != शून्यAGINO &&
		  (args.agbno < be32_to_cpu(agi->agi_length)))) अणु
		args.fsbno = XFS_AGB_TO_FSB(args.mp, agno, args.agbno);
		args.type = XFS_ALLOCTYPE_THIS_BNO;
		args.prod = 1;

		/*
		 * We need to take पूर्णांकo account alignment here to ensure that
		 * we करोn't modअगरy the मुक्त list अगर we fail to have an exact
		 * block. If we करोn't have an exact match, and every oher
		 * attempt allocation attempt fails, we'll end up cancelling
		 * a dirty transaction and shutting करोwn.
		 *
		 * For an exact allocation, alignment must be 1,
		 * however we need to take cluster alignment पूर्णांकo account when
		 * fixing up the मुक्तlist. Use the minalignslop field to
		 * indicate that extra blocks might be required क्रम alignment,
		 * but not to use them in the actual exact allocation.
		 */
		args.alignment = 1;
		args.minalignslop = igeo->cluster_align - 1;

		/* Allow space क्रम the inode btree to split. */
		args.minleft = igeo->inobt_maxlevels;
		अगर ((error = xfs_alloc_vextent(&args)))
			वापस error;

		/*
		 * This request might have dirtied the transaction अगर the AG can
		 * satisfy the request, but the exact block was not available.
		 * If the allocation did fail, subsequent requests will relax
		 * the exact agbno requirement and increase the alignment
		 * instead. It is critical that the total size of the request
		 * (len + alignment + slop) करोes not increase from this poपूर्णांक
		 * on, so reset minalignslop to ensure it is not included in
		 * subsequent requests.
		 */
		args.minalignslop = 0;
	पूर्ण

	अगर (unlikely(args.fsbno == शून्यFSBLOCK)) अणु
		/*
		 * Set the alignment क्रम the allocation.
		 * If stripe alignment is turned on then align at stripe unit
		 * boundary.
		 * If the cluster size is smaller than a fileप्रणाली block
		 * then we're करोing I/O क्रम inodes in fileप्रणाली block size
		 * pieces, so करोn't need alignment anyway.
		 */
		isaligned = 0;
		अगर (igeo->ialloc_align) अणु
			ASSERT(!(args.mp->m_flags & XFS_MOUNT_NOALIGN));
			args.alignment = args.mp->m_dalign;
			isaligned = 1;
		पूर्ण अन्यथा
			args.alignment = igeo->cluster_align;
		/*
		 * Need to figure out where to allocate the inode blocks.
		 * Ideally they should be spaced out through the a.g.
		 * For now, just allocate blocks up front.
		 */
		args.agbno = be32_to_cpu(agi->agi_root);
		args.fsbno = XFS_AGB_TO_FSB(args.mp, agno, args.agbno);
		/*
		 * Allocate a fixed-size extent of inodes.
		 */
		args.type = XFS_ALLOCTYPE_NEAR_BNO;
		args.prod = 1;
		/*
		 * Allow space क्रम the inode btree to split.
		 */
		args.minleft = igeo->inobt_maxlevels;
		अगर ((error = xfs_alloc_vextent(&args)))
			वापस error;
	पूर्ण

	/*
	 * If stripe alignment is turned on, then try again with cluster
	 * alignment.
	 */
	अगर (isaligned && args.fsbno == शून्यFSBLOCK) अणु
		args.type = XFS_ALLOCTYPE_NEAR_BNO;
		args.agbno = be32_to_cpu(agi->agi_root);
		args.fsbno = XFS_AGB_TO_FSB(args.mp, agno, args.agbno);
		args.alignment = igeo->cluster_align;
		अगर ((error = xfs_alloc_vextent(&args)))
			वापस error;
	पूर्ण

	/*
	 * Finally, try a sparse allocation अगर the fileप्रणाली supports it and
	 * the sparse allocation length is smaller than a full chunk.
	 */
	अगर (xfs_sb_version_hassparseinodes(&args.mp->m_sb) &&
	    igeo->ialloc_min_blks < igeo->ialloc_blks &&
	    args.fsbno == शून्यFSBLOCK) अणु
sparse_alloc:
		args.type = XFS_ALLOCTYPE_NEAR_BNO;
		args.agbno = be32_to_cpu(agi->agi_root);
		args.fsbno = XFS_AGB_TO_FSB(args.mp, agno, args.agbno);
		args.alignment = args.mp->m_sb.sb_spino_align;
		args.prod = 1;

		args.minlen = igeo->ialloc_min_blks;
		args.maxlen = args.minlen;

		/*
		 * The inode record will be aligned to full chunk size. We must
		 * prevent sparse allocation from AG boundaries that result in
		 * invalid inode records, such as records that start at agbno 0
		 * or extend beyond the AG.
		 *
		 * Set min agbno to the first aligned, non-zero agbno and max to
		 * the last aligned agbno that is at least one full chunk from
		 * the end of the AG.
		 */
		args.min_agbno = args.mp->m_sb.sb_inoalignmt;
		args.max_agbno = round_करोwn(args.mp->m_sb.sb_agblocks,
					    args.mp->m_sb.sb_inoalignmt) -
				 igeo->ialloc_blks;

		error = xfs_alloc_vextent(&args);
		अगर (error)
			वापस error;

		newlen = XFS_AGB_TO_AGINO(args.mp, args.len);
		ASSERT(newlen <= XFS_INODES_PER_CHUNK);
		allocmask = (1 << (newlen / XFS_INODES_PER_HOLEMASK_BIT)) - 1;
	पूर्ण

	अगर (args.fsbno == शून्यFSBLOCK)
		वापस 1;

	ASSERT(args.len == args.minlen);

	/*
	 * Stamp and ग_लिखो the inode buffers.
	 *
	 * Seed the new inode cluster with a अक्रमom generation number. This
	 * prevents लघु-term reuse of generation numbers अगर a chunk is
	 * मुक्तd and then immediately पुनः_स्मृतिated. We use अक्रमom numbers
	 * rather than a linear progression to prevent the next generation
	 * number from being easily guessable.
	 */
	error = xfs_ialloc_inode_init(args.mp, tp, शून्य, newlen, agno,
			args.agbno, args.len, pअक्रमom_u32());

	अगर (error)
		वापस error;
	/*
	 * Convert the results.
	 */
	newino = XFS_AGB_TO_AGINO(args.mp, args.agbno);

	अगर (xfs_inobt_issparse(~allocmask)) अणु
		/*
		 * We've allocated a sparse chunk. Align the startino and mask.
		 */
		xfs_align_sparse_ino(args.mp, &newino, &allocmask);

		rec.ir_startino = newino;
		rec.ir_holemask = ~allocmask;
		rec.ir_count = newlen;
		rec.ir_मुक्तcount = newlen;
		rec.ir_मुक्त = XFS_INOBT_ALL_FREE;

		/*
		 * Insert the sparse record पूर्णांकo the inobt and allow क्रम a merge
		 * अगर necessary. If a merge करोes occur, rec is updated to the
		 * merged record.
		 */
		error = xfs_inobt_insert_sprec(args.mp, tp, agbp, XFS_BTNUM_INO,
					       &rec, true);
		अगर (error == -EFSCORRUPTED) अणु
			xfs_alert(args.mp,
	"invalid sparse inode record: ino 0x%llx holemask 0x%x count %u",
				  XFS_AGINO_TO_INO(args.mp, agno,
						   rec.ir_startino),
				  rec.ir_holemask, rec.ir_count);
			xfs_क्रमce_shutकरोwn(args.mp, SHUTDOWN_CORRUPT_INCORE);
		पूर्ण
		अगर (error)
			वापस error;

		/*
		 * We can't merge the part we've just allocated as क्रम the inobt
		 * due to finobt semantics. The original record may or may not
		 * exist independent of whether physical inodes exist in this
		 * sparse chunk.
		 *
		 * We must update the finobt record based on the inobt record.
		 * rec contains the fully merged and up to date inobt record
		 * from the previous call. Set merge false to replace any
		 * existing record with this one.
		 */
		अगर (xfs_sb_version_hasfinobt(&args.mp->m_sb)) अणु
			error = xfs_inobt_insert_sprec(args.mp, tp, agbp,
						       XFS_BTNUM_FINO, &rec,
						       false);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* full chunk - insert new records to both btrees */
		error = xfs_inobt_insert(args.mp, tp, agbp, newino, newlen,
					 XFS_BTNUM_INO);
		अगर (error)
			वापस error;

		अगर (xfs_sb_version_hasfinobt(&args.mp->m_sb)) अणु
			error = xfs_inobt_insert(args.mp, tp, agbp, newino,
						 newlen, XFS_BTNUM_FINO);
			अगर (error)
				वापस error;
		पूर्ण
	पूर्ण

	/*
	 * Update AGI counts and newino.
	 */
	be32_add_cpu(&agi->agi_count, newlen);
	be32_add_cpu(&agi->agi_मुक्तcount, newlen);
	pag = agbp->b_pag;
	pag->pagi_मुक्तcount += newlen;
	pag->pagi_count += newlen;
	agi->agi_newino = cpu_to_be32(newino);

	/*
	 * Log allocation group header fields
	 */
	xfs_ialloc_log_agi(tp, agbp,
		XFS_AGI_COUNT | XFS_AGI_FREECOUNT | XFS_AGI_NEWINO);
	/*
	 * Modअगरy/log superblock values क्रम inode count and inode मुक्त count.
	 */
	xfs_trans_mod_sb(tp, XFS_TRANS_SB_ICOUNT, (दीर्घ)newlen);
	xfs_trans_mod_sb(tp, XFS_TRANS_SB_IFREE, (दीर्घ)newlen);
	वापस 0;
पूर्ण

STATIC xfs_agnumber_t
xfs_ialloc_next_ag(
	xfs_mount_t	*mp)
अणु
	xfs_agnumber_t	agno;

	spin_lock(&mp->m_agirotor_lock);
	agno = mp->m_agirotor;
	अगर (++mp->m_agirotor >= mp->m_maxagi)
		mp->m_agirotor = 0;
	spin_unlock(&mp->m_agirotor_lock);

	वापस agno;
पूर्ण

/*
 * Select an allocation group to look क्रम a मुक्त inode in, based on the parent
 * inode and the mode.  Return the allocation group buffer.
 */
STATIC xfs_agnumber_t
xfs_ialloc_ag_select(
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_ino_t	parent,		/* parent directory inode number */
	umode_t		mode)		/* bits set to indicate file type */
अणु
	xfs_agnumber_t	agcount;	/* number of ag's in the fileप्रणाली */
	xfs_agnumber_t	agno;		/* current ag number */
	पूर्णांक		flags;		/* alloc buffer locking flags */
	xfs_extlen_t	ineed;		/* blocks needed क्रम inode allocation */
	xfs_extlen_t	दीर्घest = 0;	/* दीर्घest extent available */
	xfs_mount_t	*mp;		/* mount poपूर्णांक काष्ठाure */
	पूर्णांक		needspace;	/* file mode implies space allocated */
	xfs_perag_t	*pag;		/* per allocation group data */
	xfs_agnumber_t	pagno;		/* parent (starting) ag number */
	पूर्णांक		error;

	/*
	 * Files of these types need at least one block अगर length > 0
	 * (and they won't fit in the inode, but that's hard to figure out).
	 */
	needspace = S_ISसूची(mode) || S_ISREG(mode) || S_ISLNK(mode);
	mp = tp->t_mountp;
	agcount = mp->m_maxagi;
	अगर (S_ISसूची(mode))
		pagno = xfs_ialloc_next_ag(mp);
	अन्यथा अणु
		pagno = XFS_INO_TO_AGNO(mp, parent);
		अगर (pagno >= agcount)
			pagno = 0;
	पूर्ण

	ASSERT(pagno < agcount);

	/*
	 * Loop through allocation groups, looking क्रम one with a little
	 * मुक्त space in it.  Note we करोn't look क्रम मुक्त inodes, exactly.
	 * Instead, we include whether there is a need to allocate inodes
	 * to mean that blocks must be allocated क्रम them,
	 * अगर none are currently मुक्त.
	 */
	agno = pagno;
	flags = XFS_ALLOC_FLAG_TRYLOCK;
	क्रम (;;) अणु
		pag = xfs_perag_get(mp, agno);
		अगर (!pag->pagi_inodeok) अणु
			xfs_ialloc_next_ag(mp);
			जाओ nextag;
		पूर्ण

		अगर (!pag->pagi_init) अणु
			error = xfs_ialloc_pagi_init(mp, tp, agno);
			अगर (error)
				जाओ nextag;
		पूर्ण

		अगर (pag->pagi_मुक्तcount) अणु
			xfs_perag_put(pag);
			वापस agno;
		पूर्ण

		अगर (!pag->pagf_init) अणु
			error = xfs_alloc_pagf_init(mp, tp, agno, flags);
			अगर (error)
				जाओ nextag;
		पूर्ण

		/*
		 * Check that there is enough मुक्त space क्रम the file plus a
		 * chunk of inodes अगर we need to allocate some. If this is the
		 * first pass across the AGs, take पूर्णांकo account the potential
		 * space needed क्रम alignment of inode chunks when checking the
		 * दीर्घest contiguous मुक्त space in the AG - this prevents us
		 * from getting ENOSPC because we have मुक्त space larger than
		 * ialloc_blks but alignment स्थिरraपूर्णांकs prevent us from using
		 * it.
		 *
		 * If we can't find an AG with space क्रम full alignment slack to
		 * be taken पूर्णांकo account, we must be near ENOSPC in all AGs.
		 * Hence we करोn't include alignment क्रम the second pass and so
		 * अगर we fail allocation due to alignment issues then it is most
		 * likely a real ENOSPC condition.
		 */
		ineed = M_IGEO(mp)->ialloc_min_blks;
		अगर (flags && ineed > 1)
			ineed += M_IGEO(mp)->cluster_align;
		दीर्घest = pag->pagf_दीर्घest;
		अगर (!दीर्घest)
			दीर्घest = pag->pagf_flcount > 0;

		अगर (pag->pagf_मुक्तblks >= needspace + ineed &&
		    दीर्घest >= ineed) अणु
			xfs_perag_put(pag);
			वापस agno;
		पूर्ण
nextag:
		xfs_perag_put(pag);
		/*
		 * No poपूर्णांक in iterating over the rest, अगर we're shutting
		 * करोwn.
		 */
		अगर (XFS_FORCED_SHUTDOWN(mp))
			वापस शून्यAGNUMBER;
		agno++;
		अगर (agno >= agcount)
			agno = 0;
		अगर (agno == pagno) अणु
			अगर (flags == 0)
				वापस शून्यAGNUMBER;
			flags = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Try to retrieve the next record to the left/right from the current one.
 */
STATIC पूर्णांक
xfs_ialloc_next_rec(
	काष्ठा xfs_btree_cur	*cur,
	xfs_inobt_rec_incore_t	*rec,
	पूर्णांक			*करोne,
	पूर्णांक			left)
अणु
	पूर्णांक                     error;
	पूर्णांक			i;

	अगर (left)
		error = xfs_btree_decrement(cur, 0, &i);
	अन्यथा
		error = xfs_btree_increment(cur, 0, &i);

	अगर (error)
		वापस error;
	*करोne = !i;
	अगर (i) अणु
		error = xfs_inobt_get_rec(cur, rec, &i);
		अगर (error)
			वापस error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1))
			वापस -EFSCORRUPTED;
	पूर्ण

	वापस 0;
पूर्ण

STATIC पूर्णांक
xfs_ialloc_get_rec(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agino_t		agino,
	xfs_inobt_rec_incore_t	*rec,
	पूर्णांक			*करोne)
अणु
	पूर्णांक                     error;
	पूर्णांक			i;

	error = xfs_inobt_lookup(cur, agino, XFS_LOOKUP_EQ, &i);
	अगर (error)
		वापस error;
	*करोne = !i;
	अगर (i) अणु
		error = xfs_inobt_get_rec(cur, rec, &i);
		अगर (error)
			वापस error;
		अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1))
			वापस -EFSCORRUPTED;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Return the offset of the first मुक्त inode in the record. If the inode chunk
 * is sparsely allocated, we convert the record holemask to inode granularity
 * and mask off the unallocated regions from the inode मुक्त mask.
 */
STATIC पूर्णांक
xfs_inobt_first_मुक्त_inode(
	काष्ठा xfs_inobt_rec_incore	*rec)
अणु
	xfs_inoमुक्त_t			realमुक्त;

	/* अगर there are no holes, वापस the first available offset */
	अगर (!xfs_inobt_issparse(rec->ir_holemask))
		वापस xfs_lowbit64(rec->ir_मुक्त);

	realमुक्त = xfs_inobt_irec_to_allocmask(rec);
	realमुक्त &= rec->ir_मुक्त;

	वापस xfs_lowbit64(realमुक्त);
पूर्ण

/*
 * Allocate an inode using the inobt-only algorithm.
 */
STATIC पूर्णांक
xfs_dialloc_ag_inobt(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp,
	xfs_ino_t		parent,
	xfs_ino_t		*inop)
अणु
	काष्ठा xfs_mount	*mp = tp->t_mountp;
	काष्ठा xfs_agi		*agi = agbp->b_addr;
	xfs_agnumber_t		agno = be32_to_cpu(agi->agi_seqno);
	xfs_agnumber_t		pagno = XFS_INO_TO_AGNO(mp, parent);
	xfs_agino_t		pagino = XFS_INO_TO_AGINO(mp, parent);
	काष्ठा xfs_perag	*pag = agbp->b_pag;
	काष्ठा xfs_btree_cur	*cur, *tcur;
	काष्ठा xfs_inobt_rec_incore rec, trec;
	xfs_ino_t		ino;
	पूर्णांक			error;
	पूर्णांक			offset;
	पूर्णांक			i, j;
	पूर्णांक			searchdistance = 10;

	ASSERT(pag->pagi_init);
	ASSERT(pag->pagi_inodeok);
	ASSERT(pag->pagi_मुक्तcount > 0);

 restart_pagno:
	cur = xfs_inobt_init_cursor(mp, tp, agbp, agno, XFS_BTNUM_INO);
	/*
	 * If pagino is 0 (this is the root inode allocation) use newino.
	 * This must work because we've just allocated some.
	 */
	अगर (!pagino)
		pagino = be32_to_cpu(agi->agi_newino);

	error = xfs_check_agi_मुक्तcount(cur, agi);
	अगर (error)
		जाओ error0;

	/*
	 * If in the same AG as the parent, try to get near the parent.
	 */
	अगर (pagno == agno) अणु
		पूर्णांक		करोneleft;	/* करोne, to the left */
		पूर्णांक		करोneright;	/* करोne, to the right */

		error = xfs_inobt_lookup(cur, pagino, XFS_LOOKUP_LE, &i);
		अगर (error)
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण

		error = xfs_inobt_get_rec(cur, &rec, &j);
		अगर (error)
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, j != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण

		अगर (rec.ir_मुक्तcount > 0) अणु
			/*
			 * Found a मुक्त inode in the same chunk
			 * as the parent, करोne.
			 */
			जाओ alloc_inode;
		पूर्ण


		/*
		 * In the same AG as parent, but parent's chunk is full.
		 */

		/* duplicate the cursor, search left & right simultaneously */
		error = xfs_btree_dup_cursor(cur, &tcur);
		अगर (error)
			जाओ error0;

		/*
		 * Skip to last blocks looked up अगर same parent inode.
		 */
		अगर (pagino != शून्यAGINO &&
		    pag->pagl_pagino == pagino &&
		    pag->pagl_leftrec != शून्यAGINO &&
		    pag->pagl_rightrec != शून्यAGINO) अणु
			error = xfs_ialloc_get_rec(tcur, pag->pagl_leftrec,
						   &trec, &करोneleft);
			अगर (error)
				जाओ error1;

			error = xfs_ialloc_get_rec(cur, pag->pagl_rightrec,
						   &rec, &करोneright);
			अगर (error)
				जाओ error1;
		पूर्ण अन्यथा अणु
			/* search left with tcur, back up 1 record */
			error = xfs_ialloc_next_rec(tcur, &trec, &करोneleft, 1);
			अगर (error)
				जाओ error1;

			/* search right with cur, go क्रमward 1 record. */
			error = xfs_ialloc_next_rec(cur, &rec, &करोneright, 0);
			अगर (error)
				जाओ error1;
		पूर्ण

		/*
		 * Loop until we find an inode chunk with a मुक्त inode.
		 */
		जबतक (--searchdistance > 0 && (!करोneleft || !करोneright)) अणु
			पूर्णांक	useleft;  /* using left inode chunk this समय */

			/* figure out the बंदr block अगर both are valid. */
			अगर (!करोneleft && !करोneright) अणु
				useleft = pagino -
				 (trec.ir_startino + XFS_INODES_PER_CHUNK - 1) <
				  rec.ir_startino - pagino;
			पूर्ण अन्यथा अणु
				useleft = !करोneleft;
			पूर्ण

			/* मुक्त inodes to the left? */
			अगर (useleft && trec.ir_मुक्तcount) अणु
				xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
				cur = tcur;

				pag->pagl_leftrec = trec.ir_startino;
				pag->pagl_rightrec = rec.ir_startino;
				pag->pagl_pagino = pagino;
				rec = trec;
				जाओ alloc_inode;
			पूर्ण

			/* मुक्त inodes to the right? */
			अगर (!useleft && rec.ir_मुक्तcount) अणु
				xfs_btree_del_cursor(tcur, XFS_BTREE_NOERROR);

				pag->pagl_leftrec = trec.ir_startino;
				pag->pagl_rightrec = rec.ir_startino;
				pag->pagl_pagino = pagino;
				जाओ alloc_inode;
			पूर्ण

			/* get next record to check */
			अगर (useleft) अणु
				error = xfs_ialloc_next_rec(tcur, &trec,
								 &करोneleft, 1);
			पूर्ण अन्यथा अणु
				error = xfs_ialloc_next_rec(cur, &rec,
								 &करोneright, 0);
			पूर्ण
			अगर (error)
				जाओ error1;
		पूर्ण

		अगर (searchdistance <= 0) अणु
			/*
			 * Not in range - save last search
			 * location and allocate a new inode
			 */
			xfs_btree_del_cursor(tcur, XFS_BTREE_NOERROR);
			pag->pagl_leftrec = trec.ir_startino;
			pag->pagl_rightrec = rec.ir_startino;
			pag->pagl_pagino = pagino;

		पूर्ण अन्यथा अणु
			/*
			 * We've reached the end of the btree. because
			 * we are only searching a small chunk of the
			 * btree each search, there is obviously मुक्त
			 * inodes बंदr to the parent inode than we
			 * are now. restart the search again.
			 */
			pag->pagl_pagino = शून्यAGINO;
			pag->pagl_leftrec = शून्यAGINO;
			pag->pagl_rightrec = शून्यAGINO;
			xfs_btree_del_cursor(tcur, XFS_BTREE_NOERROR);
			xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
			जाओ restart_pagno;
		पूर्ण
	पूर्ण

	/*
	 * In a dअगरferent AG from the parent.
	 * See अगर the most recently allocated block has any मुक्त.
	 */
	अगर (agi->agi_newino != cpu_to_be32(शून्यAGINO)) अणु
		error = xfs_inobt_lookup(cur, be32_to_cpu(agi->agi_newino),
					 XFS_LOOKUP_EQ, &i);
		अगर (error)
			जाओ error0;

		अगर (i == 1) अणु
			error = xfs_inobt_get_rec(cur, &rec, &j);
			अगर (error)
				जाओ error0;

			अगर (j == 1 && rec.ir_मुक्तcount > 0) अणु
				/*
				 * The last chunk allocated in the group
				 * still has a मुक्त inode.
				 */
				जाओ alloc_inode;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * None left in the last group, search the whole AG
	 */
	error = xfs_inobt_lookup(cur, 0, XFS_LOOKUP_GE, &i);
	अगर (error)
		जाओ error0;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण

	क्रम (;;) अणु
		error = xfs_inobt_get_rec(cur, &rec, &i);
		अगर (error)
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
		अगर (rec.ir_मुक्तcount > 0)
			अवरोध;
		error = xfs_btree_increment(cur, 0, &i);
		अगर (error)
			जाओ error0;
		अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error0;
		पूर्ण
	पूर्ण

alloc_inode:
	offset = xfs_inobt_first_मुक्त_inode(&rec);
	ASSERT(offset >= 0);
	ASSERT(offset < XFS_INODES_PER_CHUNK);
	ASSERT((XFS_AGINO_TO_OFFSET(mp, rec.ir_startino) %
				   XFS_INODES_PER_CHUNK) == 0);
	ino = XFS_AGINO_TO_INO(mp, agno, rec.ir_startino + offset);
	rec.ir_मुक्त &= ~XFS_INOBT_MASK(offset);
	rec.ir_मुक्तcount--;
	error = xfs_inobt_update(cur, &rec);
	अगर (error)
		जाओ error0;
	be32_add_cpu(&agi->agi_मुक्तcount, -1);
	xfs_ialloc_log_agi(tp, agbp, XFS_AGI_FREECOUNT);
	pag->pagi_मुक्तcount--;

	error = xfs_check_agi_मुक्तcount(cur, agi);
	अगर (error)
		जाओ error0;

	xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
	xfs_trans_mod_sb(tp, XFS_TRANS_SB_IFREE, -1);
	*inop = ino;
	वापस 0;
error1:
	xfs_btree_del_cursor(tcur, XFS_BTREE_ERROR);
error0:
	xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Use the मुक्त inode btree to allocate an inode based on distance from the
 * parent. Note that the provided cursor may be deleted and replaced.
 */
STATIC पूर्णांक
xfs_dialloc_ag_finobt_near(
	xfs_agino_t			pagino,
	काष्ठा xfs_btree_cur		**ocur,
	काष्ठा xfs_inobt_rec_incore	*rec)
अणु
	काष्ठा xfs_btree_cur		*lcur = *ocur;	/* left search cursor */
	काष्ठा xfs_btree_cur		*rcur;	/* right search cursor */
	काष्ठा xfs_inobt_rec_incore	rrec;
	पूर्णांक				error;
	पूर्णांक				i, j;

	error = xfs_inobt_lookup(lcur, pagino, XFS_LOOKUP_LE, &i);
	अगर (error)
		वापस error;

	अगर (i == 1) अणु
		error = xfs_inobt_get_rec(lcur, rec, &i);
		अगर (error)
			वापस error;
		अगर (XFS_IS_CORRUPT(lcur->bc_mp, i != 1))
			वापस -EFSCORRUPTED;

		/*
		 * See अगर we've landed in the parent inode record. The finobt
		 * only tracks chunks with at least one मुक्त inode, so record
		 * existence is enough.
		 */
		अगर (pagino >= rec->ir_startino &&
		    pagino < (rec->ir_startino + XFS_INODES_PER_CHUNK))
			वापस 0;
	पूर्ण

	error = xfs_btree_dup_cursor(lcur, &rcur);
	अगर (error)
		वापस error;

	error = xfs_inobt_lookup(rcur, pagino, XFS_LOOKUP_GE, &j);
	अगर (error)
		जाओ error_rcur;
	अगर (j == 1) अणु
		error = xfs_inobt_get_rec(rcur, &rrec, &j);
		अगर (error)
			जाओ error_rcur;
		अगर (XFS_IS_CORRUPT(lcur->bc_mp, j != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error_rcur;
		पूर्ण
	पूर्ण

	अगर (XFS_IS_CORRUPT(lcur->bc_mp, i != 1 && j != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ error_rcur;
	पूर्ण
	अगर (i == 1 && j == 1) अणु
		/*
		 * Both the left and right records are valid. Choose the बंदr
		 * inode chunk to the target.
		 */
		अगर ((pagino - rec->ir_startino + XFS_INODES_PER_CHUNK - 1) >
		    (rrec.ir_startino - pagino)) अणु
			*rec = rrec;
			xfs_btree_del_cursor(lcur, XFS_BTREE_NOERROR);
			*ocur = rcur;
		पूर्ण अन्यथा अणु
			xfs_btree_del_cursor(rcur, XFS_BTREE_NOERROR);
		पूर्ण
	पूर्ण अन्यथा अगर (j == 1) अणु
		/* only the right record is valid */
		*rec = rrec;
		xfs_btree_del_cursor(lcur, XFS_BTREE_NOERROR);
		*ocur = rcur;
	पूर्ण अन्यथा अगर (i == 1) अणु
		/* only the left record is valid */
		xfs_btree_del_cursor(rcur, XFS_BTREE_NOERROR);
	पूर्ण

	वापस 0;

error_rcur:
	xfs_btree_del_cursor(rcur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Use the मुक्त inode btree to find a मुक्त inode based on a newino hपूर्णांक. If
 * the hपूर्णांक is शून्य, find the first मुक्त inode in the AG.
 */
STATIC पूर्णांक
xfs_dialloc_ag_finobt_newino(
	काष्ठा xfs_agi			*agi,
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_inobt_rec_incore	*rec)
अणु
	पूर्णांक error;
	पूर्णांक i;

	अगर (agi->agi_newino != cpu_to_be32(शून्यAGINO)) अणु
		error = xfs_inobt_lookup(cur, be32_to_cpu(agi->agi_newino),
					 XFS_LOOKUP_EQ, &i);
		अगर (error)
			वापस error;
		अगर (i == 1) अणु
			error = xfs_inobt_get_rec(cur, rec, &i);
			अगर (error)
				वापस error;
			अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1))
				वापस -EFSCORRUPTED;
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Find the first inode available in the AG.
	 */
	error = xfs_inobt_lookup(cur, 0, XFS_LOOKUP_GE, &i);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1))
		वापस -EFSCORRUPTED;

	error = xfs_inobt_get_rec(cur, rec, &i);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1))
		वापस -EFSCORRUPTED;

	वापस 0;
पूर्ण

/*
 * Update the inobt based on a modअगरication made to the finobt. Also ensure that
 * the records from both trees are equivalent post-modअगरication.
 */
STATIC पूर्णांक
xfs_dialloc_ag_update_inobt(
	काष्ठा xfs_btree_cur		*cur,	/* inobt cursor */
	काष्ठा xfs_inobt_rec_incore	*frec,	/* finobt record */
	पूर्णांक				offset) /* inode offset */
अणु
	काष्ठा xfs_inobt_rec_incore	rec;
	पूर्णांक				error;
	पूर्णांक				i;

	error = xfs_inobt_lookup(cur, frec->ir_startino, XFS_LOOKUP_EQ, &i);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1))
		वापस -EFSCORRUPTED;

	error = xfs_inobt_get_rec(cur, &rec, &i);
	अगर (error)
		वापस error;
	अगर (XFS_IS_CORRUPT(cur->bc_mp, i != 1))
		वापस -EFSCORRUPTED;
	ASSERT((XFS_AGINO_TO_OFFSET(cur->bc_mp, rec.ir_startino) %
				   XFS_INODES_PER_CHUNK) == 0);

	rec.ir_मुक्त &= ~XFS_INOBT_MASK(offset);
	rec.ir_मुक्तcount--;

	अगर (XFS_IS_CORRUPT(cur->bc_mp,
			   rec.ir_मुक्त != frec->ir_मुक्त ||
			   rec.ir_मुक्तcount != frec->ir_मुक्तcount))
		वापस -EFSCORRUPTED;

	वापस xfs_inobt_update(cur, &rec);
पूर्ण

/*
 * Allocate an inode using the मुक्त inode btree, अगर available. Otherwise, fall
 * back to the inobt search algorithm.
 *
 * The caller selected an AG क्रम us, and made sure that मुक्त inodes are
 * available.
 */
पूर्णांक
xfs_dialloc_ag(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_buf		*agbp,
	xfs_ino_t		parent,
	xfs_ino_t		*inop)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	काष्ठा xfs_agi			*agi = agbp->b_addr;
	xfs_agnumber_t			agno = be32_to_cpu(agi->agi_seqno);
	xfs_agnumber_t			pagno = XFS_INO_TO_AGNO(mp, parent);
	xfs_agino_t			pagino = XFS_INO_TO_AGINO(mp, parent);
	काष्ठा xfs_btree_cur		*cur;	/* finobt cursor */
	काष्ठा xfs_btree_cur		*icur;	/* inobt cursor */
	काष्ठा xfs_inobt_rec_incore	rec;
	xfs_ino_t			ino;
	पूर्णांक				error;
	पूर्णांक				offset;
	पूर्णांक				i;

	अगर (!xfs_sb_version_hasfinobt(&mp->m_sb))
		वापस xfs_dialloc_ag_inobt(tp, agbp, parent, inop);

	/*
	 * If pagino is 0 (this is the root inode allocation) use newino.
	 * This must work because we've just allocated some.
	 */
	अगर (!pagino)
		pagino = be32_to_cpu(agi->agi_newino);

	cur = xfs_inobt_init_cursor(mp, tp, agbp, agno, XFS_BTNUM_FINO);

	error = xfs_check_agi_मुक्तcount(cur, agi);
	अगर (error)
		जाओ error_cur;

	/*
	 * The search algorithm depends on whether we're in the same AG as the
	 * parent. If so, find the बंदst available inode to the parent. If
	 * not, consider the agi hपूर्णांक or find the first मुक्त inode in the AG.
	 */
	अगर (agno == pagno)
		error = xfs_dialloc_ag_finobt_near(pagino, &cur, &rec);
	अन्यथा
		error = xfs_dialloc_ag_finobt_newino(agi, cur, &rec);
	अगर (error)
		जाओ error_cur;

	offset = xfs_inobt_first_मुक्त_inode(&rec);
	ASSERT(offset >= 0);
	ASSERT(offset < XFS_INODES_PER_CHUNK);
	ASSERT((XFS_AGINO_TO_OFFSET(mp, rec.ir_startino) %
				   XFS_INODES_PER_CHUNK) == 0);
	ino = XFS_AGINO_TO_INO(mp, agno, rec.ir_startino + offset);

	/*
	 * Modअगरy or हटाओ the finobt record.
	 */
	rec.ir_मुक्त &= ~XFS_INOBT_MASK(offset);
	rec.ir_मुक्तcount--;
	अगर (rec.ir_मुक्तcount)
		error = xfs_inobt_update(cur, &rec);
	अन्यथा
		error = xfs_btree_delete(cur, &i);
	अगर (error)
		जाओ error_cur;

	/*
	 * The finobt has now been updated appropriately. We haven't updated the
	 * agi and superblock yet, so we can create an inobt cursor and validate
	 * the original मुक्तcount. If all is well, make the equivalent update to
	 * the inobt using the finobt record and offset inक्रमmation.
	 */
	icur = xfs_inobt_init_cursor(mp, tp, agbp, agno, XFS_BTNUM_INO);

	error = xfs_check_agi_मुक्तcount(icur, agi);
	अगर (error)
		जाओ error_icur;

	error = xfs_dialloc_ag_update_inobt(icur, &rec, offset);
	अगर (error)
		जाओ error_icur;

	/*
	 * Both trees have now been updated. We must update the perag and
	 * superblock beक्रमe we can check the मुक्तcount क्रम each btree.
	 */
	be32_add_cpu(&agi->agi_मुक्तcount, -1);
	xfs_ialloc_log_agi(tp, agbp, XFS_AGI_FREECOUNT);
	agbp->b_pag->pagi_मुक्तcount--;

	xfs_trans_mod_sb(tp, XFS_TRANS_SB_IFREE, -1);

	error = xfs_check_agi_मुक्तcount(icur, agi);
	अगर (error)
		जाओ error_icur;
	error = xfs_check_agi_मुक्तcount(cur, agi);
	अगर (error)
		जाओ error_icur;

	xfs_btree_del_cursor(icur, XFS_BTREE_NOERROR);
	xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
	*inop = ino;
	वापस 0;

error_icur:
	xfs_btree_del_cursor(icur, XFS_BTREE_ERROR);
error_cur:
	xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

अटल पूर्णांक
xfs_dialloc_roll(
	काष्ठा xfs_trans	**tpp,
	काष्ठा xfs_buf		*agibp)
अणु
	काष्ठा xfs_trans	*tp = *tpp;
	काष्ठा xfs_dquot_acct	*dqinfo;
	पूर्णांक			error;

	/*
	 * Hold to on to the agibp across the commit so no other allocation can
	 * come in and take the मुक्त inodes we just allocated क्रम our caller.
	 */
	xfs_trans_bhold(tp, agibp);

	/*
	 * We want the quota changes to be associated with the next transaction,
	 * NOT this one. So, detach the dqinfo from this and attach it to the
	 * next transaction.
	 */
	dqinfo = tp->t_dqinfo;
	tp->t_dqinfo = शून्य;

	error = xfs_trans_roll(&tp);

	/* Re-attach the quota info that we detached from prev trx. */
	tp->t_dqinfo = dqinfo;

	*tpp = tp;
	अगर (error)
		वापस error;
	xfs_trans_bjoin(tp, agibp);
	वापस 0;
पूर्ण

/*
 * Select and prepare an AG क्रम inode allocation.
 *
 * Mode is used to tell whether the new inode is a directory and hence where to
 * locate it.
 *
 * This function will ensure that the selected AG has मुक्त inodes available to
 * allocate from. The selected AGI will be वापसed locked to the caller, and it
 * will allocate more मुक्त inodes अगर required. If no मुक्त inodes are found or
 * can be allocated, no AGI will be वापसed.
 */
पूर्णांक
xfs_dialloc_select_ag(
	काष्ठा xfs_trans	**tpp,
	xfs_ino_t		parent,
	umode_t			mode,
	काष्ठा xfs_buf		**IO_agbp)
अणु
	काष्ठा xfs_mount	*mp = (*tpp)->t_mountp;
	काष्ठा xfs_buf		*agbp;
	xfs_agnumber_t		agno;
	पूर्णांक			error;
	bool			noroom = false;
	xfs_agnumber_t		start_agno;
	काष्ठा xfs_perag	*pag;
	काष्ठा xfs_ino_geometry	*igeo = M_IGEO(mp);
	bool			okalloc = true;

	*IO_agbp = शून्य;

	/*
	 * We करो not have an agbp, so select an initial allocation
	 * group क्रम inode allocation.
	 */
	start_agno = xfs_ialloc_ag_select(*tpp, parent, mode);
	अगर (start_agno == शून्यAGNUMBER)
		वापस 0;

	/*
	 * If we have alपढ़ोy hit the उच्चमानing of inode blocks then clear
	 * okalloc so we scan all available agi काष्ठाures क्रम a मुक्त
	 * inode.
	 *
	 * Read rough value of mp->m_icount by percpu_counter_पढ़ो_positive,
	 * which will sacrअगरice the preciseness but improve the perक्रमmance.
	 */
	अगर (igeo->maxicount &&
	    percpu_counter_पढ़ो_positive(&mp->m_icount) + igeo->ialloc_inos
							> igeo->maxicount) अणु
		noroom = true;
		okalloc = false;
	पूर्ण

	/*
	 * Loop until we find an allocation group that either has मुक्त inodes
	 * or in which we can allocate some inodes.  Iterate through the
	 * allocation groups upward, wrapping at the end.
	 */
	agno = start_agno;
	क्रम (;;) अणु
		pag = xfs_perag_get(mp, agno);
		अगर (!pag->pagi_inodeok) अणु
			xfs_ialloc_next_ag(mp);
			जाओ nextag;
		पूर्ण

		अगर (!pag->pagi_init) अणु
			error = xfs_ialloc_pagi_init(mp, *tpp, agno);
			अगर (error)
				अवरोध;
		पूर्ण

		/*
		 * Do a first racy fast path check अगर this AG is usable.
		 */
		अगर (!pag->pagi_मुक्तcount && !okalloc)
			जाओ nextag;

		/*
		 * Then पढ़ो in the AGI buffer and recheck with the AGI buffer
		 * lock held.
		 */
		error = xfs_ialloc_पढ़ो_agi(mp, *tpp, agno, &agbp);
		अगर (error)
			अवरोध;

		अगर (pag->pagi_मुक्तcount) अणु
			xfs_perag_put(pag);
			जाओ found_ag;
		पूर्ण

		अगर (!okalloc)
			जाओ nextag_rअन्यथा_buffer;

		error = xfs_ialloc_ag_alloc(*tpp, agbp);
		अगर (error < 0) अणु
			xfs_trans_brअन्यथा(*tpp, agbp);

			अगर (error == -ENOSPC)
				error = 0;
			अवरोध;
		पूर्ण

		अगर (error == 0) अणु
			/*
			 * We successfully allocated space क्रम an inode cluster
			 * in this AG.  Roll the transaction so that we can
			 * allocate one of the new inodes.
			 */
			ASSERT(pag->pagi_मुक्तcount > 0);
			xfs_perag_put(pag);

			error = xfs_dialloc_roll(tpp, agbp);
			अगर (error) अणु
				xfs_buf_rअन्यथा(agbp);
				वापस error;
			पूर्ण
			जाओ found_ag;
		पूर्ण

nextag_rअन्यथा_buffer:
		xfs_trans_brअन्यथा(*tpp, agbp);
nextag:
		xfs_perag_put(pag);
		अगर (++agno == mp->m_sb.sb_agcount)
			agno = 0;
		अगर (agno == start_agno)
			वापस noroom ? -ENOSPC : 0;
	पूर्ण

	xfs_perag_put(pag);
	वापस error;
found_ag:
	*IO_agbp = agbp;
	वापस 0;
पूर्ण

/*
 * Free the blocks of an inode chunk. We must consider that the inode chunk
 * might be sparse and only मुक्त the regions that are allocated as part of the
 * chunk.
 */
STATIC व्योम
xfs_dअगरree_inode_chunk(
	काष्ठा xfs_trans		*tp,
	xfs_agnumber_t			agno,
	काष्ठा xfs_inobt_rec_incore	*rec)
अणु
	काष्ठा xfs_mount		*mp = tp->t_mountp;
	xfs_agblock_t			sagbno = XFS_AGINO_TO_AGBNO(mp,
							rec->ir_startino);
	पूर्णांक				startidx, endidx;
	पूर्णांक				nextbit;
	xfs_agblock_t			agbno;
	पूर्णांक				contigblk;
	DECLARE_BITMAP(holemask, XFS_INOBT_HOLEMASK_BITS);

	अगर (!xfs_inobt_issparse(rec->ir_holemask)) अणु
		/* not sparse, calculate extent info directly */
		xfs_bmap_add_मुक्त(tp, XFS_AGB_TO_FSB(mp, agno, sagbno),
				  M_IGEO(mp)->ialloc_blks,
				  &XFS_RMAP_OINFO_INODES);
		वापस;
	पूर्ण

	/* holemask is only 16-bits (fits in an अचिन्हित दीर्घ) */
	ASSERT(माप(rec->ir_holemask) <= माप(holemask[0]));
	holemask[0] = rec->ir_holemask;

	/*
	 * Find contiguous ranges of zeroes (i.e., allocated regions) in the
	 * holemask and convert the start/end index of each range to an extent.
	 * We start with the start and end index both poपूर्णांकing at the first 0 in
	 * the mask.
	 */
	startidx = endidx = find_first_zero_bit(holemask,
						XFS_INOBT_HOLEMASK_BITS);
	nextbit = startidx + 1;
	जबतक (startidx < XFS_INOBT_HOLEMASK_BITS) अणु
		nextbit = find_next_zero_bit(holemask, XFS_INOBT_HOLEMASK_BITS,
					     nextbit);
		/*
		 * If the next zero bit is contiguous, update the end index of
		 * the current range and जारी.
		 */
		अगर (nextbit != XFS_INOBT_HOLEMASK_BITS &&
		    nextbit == endidx + 1) अणु
			endidx = nextbit;
			जाओ next;
		पूर्ण

		/*
		 * nextbit is not contiguous with the current end index. Convert
		 * the current start/end to an extent and add it to the मुक्त
		 * list.
		 */
		agbno = sagbno + (startidx * XFS_INODES_PER_HOLEMASK_BIT) /
				  mp->m_sb.sb_inopblock;
		contigblk = ((endidx - startidx + 1) *
			     XFS_INODES_PER_HOLEMASK_BIT) /
			    mp->m_sb.sb_inopblock;

		ASSERT(agbno % mp->m_sb.sb_spino_align == 0);
		ASSERT(contigblk % mp->m_sb.sb_spino_align == 0);
		xfs_bmap_add_मुक्त(tp, XFS_AGB_TO_FSB(mp, agno, agbno),
				  contigblk, &XFS_RMAP_OINFO_INODES);

		/* reset range to current bit and carry on... */
		startidx = endidx = nextbit;

next:
		nextbit++;
	पूर्ण
पूर्ण

STATIC पूर्णांक
xfs_dअगरree_inobt(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_buf			*agbp,
	xfs_agino_t			agino,
	काष्ठा xfs_icluster		*xic,
	काष्ठा xfs_inobt_rec_incore	*orec)
अणु
	काष्ठा xfs_agi			*agi = agbp->b_addr;
	xfs_agnumber_t			agno = be32_to_cpu(agi->agi_seqno);
	काष्ठा xfs_btree_cur		*cur;
	काष्ठा xfs_inobt_rec_incore	rec;
	पूर्णांक				ilen;
	पूर्णांक				error;
	पूर्णांक				i;
	पूर्णांक				off;

	ASSERT(agi->agi_magicnum == cpu_to_be32(XFS_AGI_MAGIC));
	ASSERT(XFS_AGINO_TO_AGBNO(mp, agino) < be32_to_cpu(agi->agi_length));

	/*
	 * Initialize the cursor.
	 */
	cur = xfs_inobt_init_cursor(mp, tp, agbp, agno, XFS_BTNUM_INO);

	error = xfs_check_agi_मुक्तcount(cur, agi);
	अगर (error)
		जाओ error0;

	/*
	 * Look क्रम the entry describing this inode.
	 */
	अगर ((error = xfs_inobt_lookup(cur, agino, XFS_LOOKUP_LE, &i))) अणु
		xfs_warn(mp, "%s: xfs_inobt_lookup() returned error %d.",
			__func__, error);
		जाओ error0;
	पूर्ण
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	error = xfs_inobt_get_rec(cur, &rec, &i);
	अगर (error) अणु
		xfs_warn(mp, "%s: xfs_inobt_get_rec() returned error %d.",
			__func__, error);
		जाओ error0;
	पूर्ण
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ error0;
	पूर्ण
	/*
	 * Get the offset in the inode chunk.
	 */
	off = agino - rec.ir_startino;
	ASSERT(off >= 0 && off < XFS_INODES_PER_CHUNK);
	ASSERT(!(rec.ir_मुक्त & XFS_INOBT_MASK(off)));
	/*
	 * Mark the inode मुक्त & increment the count.
	 */
	rec.ir_मुक्त |= XFS_INOBT_MASK(off);
	rec.ir_मुक्तcount++;

	/*
	 * When an inode chunk is मुक्त, it becomes eligible क्रम removal. Don't
	 * हटाओ the chunk अगर the block size is large enough क्रम multiple inode
	 * chunks (that might not be मुक्त).
	 */
	अगर (!(mp->m_flags & XFS_MOUNT_IKEEP) &&
	    rec.ir_मुक्त == XFS_INOBT_ALL_FREE &&
	    mp->m_sb.sb_inopblock <= XFS_INODES_PER_CHUNK) अणु
		काष्ठा xfs_perag	*pag = agbp->b_pag;

		xic->deleted = true;
		xic->first_ino = XFS_AGINO_TO_INO(mp, agno, rec.ir_startino);
		xic->alloc = xfs_inobt_irec_to_allocmask(&rec);

		/*
		 * Remove the inode cluster from the AGI B+Tree, adjust the
		 * AGI and Superblock inode counts, and mark the disk space
		 * to be मुक्तd when the transaction is committed.
		 */
		ilen = rec.ir_मुक्तcount;
		be32_add_cpu(&agi->agi_count, -ilen);
		be32_add_cpu(&agi->agi_मुक्तcount, -(ilen - 1));
		xfs_ialloc_log_agi(tp, agbp, XFS_AGI_COUNT | XFS_AGI_FREECOUNT);
		pag->pagi_मुक्तcount -= ilen - 1;
		pag->pagi_count -= ilen;
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_ICOUNT, -ilen);
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_IFREE, -(ilen - 1));

		अगर ((error = xfs_btree_delete(cur, &i))) अणु
			xfs_warn(mp, "%s: xfs_btree_delete returned error %d.",
				__func__, error);
			जाओ error0;
		पूर्ण

		xfs_dअगरree_inode_chunk(tp, agno, &rec);
	पूर्ण अन्यथा अणु
		xic->deleted = false;

		error = xfs_inobt_update(cur, &rec);
		अगर (error) अणु
			xfs_warn(mp, "%s: xfs_inobt_update returned error %d.",
				__func__, error);
			जाओ error0;
		पूर्ण

		/* 
		 * Change the inode मुक्त counts and log the ag/sb changes.
		 */
		be32_add_cpu(&agi->agi_मुक्तcount, 1);
		xfs_ialloc_log_agi(tp, agbp, XFS_AGI_FREECOUNT);
		agbp->b_pag->pagi_मुक्तcount++;
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_IFREE, 1);
	पूर्ण

	error = xfs_check_agi_मुक्तcount(cur, agi);
	अगर (error)
		जाओ error0;

	*orec = rec;
	xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
	वापस 0;

error0:
	xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Free an inode in the मुक्त inode btree.
 */
STATIC पूर्णांक
xfs_dअगरree_finobt(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_trans		*tp,
	काष्ठा xfs_buf			*agbp,
	xfs_agino_t			agino,
	काष्ठा xfs_inobt_rec_incore	*ibtrec) /* inobt record */
अणु
	काष्ठा xfs_agi			*agi = agbp->b_addr;
	xfs_agnumber_t			agno = be32_to_cpu(agi->agi_seqno);
	काष्ठा xfs_btree_cur		*cur;
	काष्ठा xfs_inobt_rec_incore	rec;
	पूर्णांक				offset = agino - ibtrec->ir_startino;
	पूर्णांक				error;
	पूर्णांक				i;

	cur = xfs_inobt_init_cursor(mp, tp, agbp, agno, XFS_BTNUM_FINO);

	error = xfs_inobt_lookup(cur, ibtrec->ir_startino, XFS_LOOKUP_EQ, &i);
	अगर (error)
		जाओ error;
	अगर (i == 0) अणु
		/*
		 * If the record करोes not exist in the finobt, we must have just
		 * मुक्तd an inode in a previously fully allocated chunk. If not,
		 * something is out of sync.
		 */
		अगर (XFS_IS_CORRUPT(mp, ibtrec->ir_मुक्तcount != 1)) अणु
			error = -EFSCORRUPTED;
			जाओ error;
		पूर्ण

		error = xfs_inobt_insert_rec(cur, ibtrec->ir_holemask,
					     ibtrec->ir_count,
					     ibtrec->ir_मुक्तcount,
					     ibtrec->ir_मुक्त, &i);
		अगर (error)
			जाओ error;
		ASSERT(i == 1);

		जाओ out;
	पूर्ण

	/*
	 * Read and update the existing record. We could just copy the ibtrec
	 * across here, but that would defeat the purpose of having redundant
	 * metadata. By making the modअगरications independently, we can catch
	 * corruptions that we wouldn't see अगर we just copied from one record
	 * to another.
	 */
	error = xfs_inobt_get_rec(cur, &rec, &i);
	अगर (error)
		जाओ error;
	अगर (XFS_IS_CORRUPT(mp, i != 1)) अणु
		error = -EFSCORRUPTED;
		जाओ error;
	पूर्ण

	rec.ir_मुक्त |= XFS_INOBT_MASK(offset);
	rec.ir_मुक्तcount++;

	अगर (XFS_IS_CORRUPT(mp,
			   rec.ir_मुक्त != ibtrec->ir_मुक्त ||
			   rec.ir_मुक्तcount != ibtrec->ir_मुक्तcount)) अणु
		error = -EFSCORRUPTED;
		जाओ error;
	पूर्ण

	/*
	 * The content of inobt records should always match between the inobt
	 * and finobt. The lअगरecycle of records in the finobt is dअगरferent from
	 * the inobt in that the finobt only tracks records with at least one
	 * मुक्त inode. Hence, अगर all of the inodes are मुक्त and we aren't
	 * keeping inode chunks permanently on disk, हटाओ the record.
	 * Otherwise, update the record with the new inक्रमmation.
	 *
	 * Note that we currently can't मुक्त chunks when the block size is large
	 * enough क्रम multiple chunks. Leave the finobt record to reमुख्य in sync
	 * with the inobt.
	 */
	अगर (rec.ir_मुक्त == XFS_INOBT_ALL_FREE &&
	    mp->m_sb.sb_inopblock <= XFS_INODES_PER_CHUNK &&
	    !(mp->m_flags & XFS_MOUNT_IKEEP)) अणु
		error = xfs_btree_delete(cur, &i);
		अगर (error)
			जाओ error;
		ASSERT(i == 1);
	पूर्ण अन्यथा अणु
		error = xfs_inobt_update(cur, &rec);
		अगर (error)
			जाओ error;
	पूर्ण

out:
	error = xfs_check_agi_मुक्तcount(cur, agi);
	अगर (error)
		जाओ error;

	xfs_btree_del_cursor(cur, XFS_BTREE_NOERROR);
	वापस 0;

error:
	xfs_btree_del_cursor(cur, XFS_BTREE_ERROR);
	वापस error;
पूर्ण

/*
 * Free disk inode.  Carefully aव्योमs touching the incore inode, all
 * manipulations incore are the caller's responsibility.
 * The on-disk inode is not changed by this operation, only the
 * btree (मुक्त inode mask) is changed.
 */
पूर्णांक
xfs_dअगरree(
	काष्ठा xfs_trans	*tp,		/* transaction poपूर्णांकer */
	xfs_ino_t		inode,		/* inode to be मुक्तd */
	काष्ठा xfs_icluster	*xic)	/* cluster info अगर deleted */
अणु
	/* REFERENCED */
	xfs_agblock_t		agbno;	/* block number containing inode */
	काष्ठा xfs_buf		*agbp;	/* buffer क्रम allocation group header */
	xfs_agino_t		agino;	/* allocation group inode number */
	xfs_agnumber_t		agno;	/* allocation group number */
	पूर्णांक			error;	/* error वापस value */
	काष्ठा xfs_mount	*mp;	/* mount काष्ठाure क्रम fileप्रणाली */
	काष्ठा xfs_inobt_rec_incore rec;/* btree record */

	mp = tp->t_mountp;

	/*
	 * Break up inode number पूर्णांकo its components.
	 */
	agno = XFS_INO_TO_AGNO(mp, inode);
	अगर (agno >= mp->m_sb.sb_agcount)  अणु
		xfs_warn(mp, "%s: agno >= mp->m_sb.sb_agcount (%d >= %d).",
			__func__, agno, mp->m_sb.sb_agcount);
		ASSERT(0);
		वापस -EINVAL;
	पूर्ण
	agino = XFS_INO_TO_AGINO(mp, inode);
	अगर (inode != XFS_AGINO_TO_INO(mp, agno, agino))  अणु
		xfs_warn(mp, "%s: inode != XFS_AGINO_TO_INO() (%llu != %llu).",
			__func__, (अचिन्हित दीर्घ दीर्घ)inode,
			(अचिन्हित दीर्घ दीर्घ)XFS_AGINO_TO_INO(mp, agno, agino));
		ASSERT(0);
		वापस -EINVAL;
	पूर्ण
	agbno = XFS_AGINO_TO_AGBNO(mp, agino);
	अगर (agbno >= mp->m_sb.sb_agblocks)  अणु
		xfs_warn(mp, "%s: agbno >= mp->m_sb.sb_agblocks (%d >= %d).",
			__func__, agbno, mp->m_sb.sb_agblocks);
		ASSERT(0);
		वापस -EINVAL;
	पूर्ण
	/*
	 * Get the allocation group header.
	 */
	error = xfs_ialloc_पढ़ो_agi(mp, tp, agno, &agbp);
	अगर (error) अणु
		xfs_warn(mp, "%s: xfs_ialloc_read_agi() returned error %d.",
			__func__, error);
		वापस error;
	पूर्ण

	/*
	 * Fix up the inode allocation btree.
	 */
	error = xfs_dअगरree_inobt(mp, tp, agbp, agino, xic, &rec);
	अगर (error)
		जाओ error0;

	/*
	 * Fix up the मुक्त inode btree.
	 */
	अगर (xfs_sb_version_hasfinobt(&mp->m_sb)) अणु
		error = xfs_dअगरree_finobt(mp, tp, agbp, agino, &rec);
		अगर (error)
			जाओ error0;
	पूर्ण

	वापस 0;

error0:
	वापस error;
पूर्ण

STATIC पूर्णांक
xfs_imap_lookup(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_trans	*tp,
	xfs_agnumber_t		agno,
	xfs_agino_t		agino,
	xfs_agblock_t		agbno,
	xfs_agblock_t		*chunk_agbno,
	xfs_agblock_t		*offset_agbno,
	पूर्णांक			flags)
अणु
	काष्ठा xfs_inobt_rec_incore rec;
	काष्ठा xfs_btree_cur	*cur;
	काष्ठा xfs_buf		*agbp;
	पूर्णांक			error;
	पूर्णांक			i;

	error = xfs_ialloc_पढ़ो_agi(mp, tp, agno, &agbp);
	अगर (error) अणु
		xfs_alert(mp,
			"%s: xfs_ialloc_read_agi() returned error %d, agno %d",
			__func__, error, agno);
		वापस error;
	पूर्ण

	/*
	 * Lookup the inode record क्रम the given agino. If the record cannot be
	 * found, then it's an invalid inode number and we should पात. Once
	 * we have a record, we need to ensure it contains the inode number
	 * we are looking up.
	 */
	cur = xfs_inobt_init_cursor(mp, tp, agbp, agno, XFS_BTNUM_INO);
	error = xfs_inobt_lookup(cur, agino, XFS_LOOKUP_LE, &i);
	अगर (!error) अणु
		अगर (i)
			error = xfs_inobt_get_rec(cur, &rec, &i);
		अगर (!error && i == 0)
			error = -EINVAL;
	पूर्ण

	xfs_trans_brअन्यथा(tp, agbp);
	xfs_btree_del_cursor(cur, error);
	अगर (error)
		वापस error;

	/* check that the वापसed record contains the required inode */
	अगर (rec.ir_startino > agino ||
	    rec.ir_startino + M_IGEO(mp)->ialloc_inos <= agino)
		वापस -EINVAL;

	/* क्रम untrusted inodes check it is allocated first */
	अगर ((flags & XFS_IGET_UNTRUSTED) &&
	    (rec.ir_मुक्त & XFS_INOBT_MASK(agino - rec.ir_startino)))
		वापस -EINVAL;

	*chunk_agbno = XFS_AGINO_TO_AGBNO(mp, rec.ir_startino);
	*offset_agbno = agbno - *chunk_agbno;
	वापस 0;
पूर्ण

/*
 * Return the location of the inode in imap, क्रम mapping it पूर्णांकo a buffer.
 */
पूर्णांक
xfs_imap(
	xfs_mount_t	 *mp,	/* file प्रणाली mount काष्ठाure */
	xfs_trans_t	 *tp,	/* transaction poपूर्णांकer */
	xfs_ino_t	ino,	/* inode to locate */
	काष्ठा xfs_imap	*imap,	/* location map काष्ठाure */
	uपूर्णांक		flags)	/* flags क्रम inode btree lookup */
अणु
	xfs_agblock_t	agbno;	/* block number of inode in the alloc group */
	xfs_agino_t	agino;	/* inode number within alloc group */
	xfs_agnumber_t	agno;	/* allocation group number */
	xfs_agblock_t	chunk_agbno;	/* first block in inode chunk */
	xfs_agblock_t	cluster_agbno;	/* first block in inode cluster */
	पूर्णांक		error;	/* error code */
	पूर्णांक		offset;	/* index of inode in its buffer */
	xfs_agblock_t	offset_agbno;	/* blks from chunk start to inode */

	ASSERT(ino != शून्यFSINO);

	/*
	 * Split up the inode number पूर्णांकo its parts.
	 */
	agno = XFS_INO_TO_AGNO(mp, ino);
	agino = XFS_INO_TO_AGINO(mp, ino);
	agbno = XFS_AGINO_TO_AGBNO(mp, agino);
	अगर (agno >= mp->m_sb.sb_agcount || agbno >= mp->m_sb.sb_agblocks ||
	    ino != XFS_AGINO_TO_INO(mp, agno, agino)) अणु
#अगर_घोषित DEBUG
		/*
		 * Don't output diagnostic inक्रमmation क्रम untrusted inodes
		 * as they can be invalid without implying corruption.
		 */
		अगर (flags & XFS_IGET_UNTRUSTED)
			वापस -EINVAL;
		अगर (agno >= mp->m_sb.sb_agcount) अणु
			xfs_alert(mp,
				"%s: agno (%d) >= mp->m_sb.sb_agcount (%d)",
				__func__, agno, mp->m_sb.sb_agcount);
		पूर्ण
		अगर (agbno >= mp->m_sb.sb_agblocks) अणु
			xfs_alert(mp,
		"%s: agbno (0x%llx) >= mp->m_sb.sb_agblocks (0x%lx)",
				__func__, (अचिन्हित दीर्घ दीर्घ)agbno,
				(अचिन्हित दीर्घ)mp->m_sb.sb_agblocks);
		पूर्ण
		अगर (ino != XFS_AGINO_TO_INO(mp, agno, agino)) अणु
			xfs_alert(mp,
		"%s: ino (0x%llx) != XFS_AGINO_TO_INO() (0x%llx)",
				__func__, ino,
				XFS_AGINO_TO_INO(mp, agno, agino));
		पूर्ण
		xfs_stack_trace();
#पूर्ण_अगर /* DEBUG */
		वापस -EINVAL;
	पूर्ण

	/*
	 * For bulkstat and handle lookups, we have an untrusted inode number
	 * that we have to verअगरy is valid. We cannot करो this just by पढ़ोing
	 * the inode buffer as it may have been unlinked and हटाओd leaving
	 * inodes in stale state on disk. Hence we have to करो a btree lookup
	 * in all हालs where an untrusted inode number is passed.
	 */
	अगर (flags & XFS_IGET_UNTRUSTED) अणु
		error = xfs_imap_lookup(mp, tp, agno, agino, agbno,
					&chunk_agbno, &offset_agbno, flags);
		अगर (error)
			वापस error;
		जाओ out_map;
	पूर्ण

	/*
	 * If the inode cluster size is the same as the blocksize or
	 * smaller we get to the buffer by simple arithmetics.
	 */
	अगर (M_IGEO(mp)->blocks_per_cluster == 1) अणु
		offset = XFS_INO_TO_OFFSET(mp, ino);
		ASSERT(offset < mp->m_sb.sb_inopblock);

		imap->im_blkno = XFS_AGB_TO_DADDR(mp, agno, agbno);
		imap->im_len = XFS_FSB_TO_BB(mp, 1);
		imap->im_boffset = (अचिन्हित लघु)(offset <<
							mp->m_sb.sb_inodelog);
		वापस 0;
	पूर्ण

	/*
	 * If the inode chunks are aligned then use simple maths to
	 * find the location. Otherwise we have to करो a btree
	 * lookup to find the location.
	 */
	अगर (M_IGEO(mp)->inoalign_mask) अणु
		offset_agbno = agbno & M_IGEO(mp)->inoalign_mask;
		chunk_agbno = agbno - offset_agbno;
	पूर्ण अन्यथा अणु
		error = xfs_imap_lookup(mp, tp, agno, agino, agbno,
					&chunk_agbno, &offset_agbno, flags);
		अगर (error)
			वापस error;
	पूर्ण

out_map:
	ASSERT(agbno >= chunk_agbno);
	cluster_agbno = chunk_agbno +
		((offset_agbno / M_IGEO(mp)->blocks_per_cluster) *
		 M_IGEO(mp)->blocks_per_cluster);
	offset = ((agbno - cluster_agbno) * mp->m_sb.sb_inopblock) +
		XFS_INO_TO_OFFSET(mp, ino);

	imap->im_blkno = XFS_AGB_TO_DADDR(mp, agno, cluster_agbno);
	imap->im_len = XFS_FSB_TO_BB(mp, M_IGEO(mp)->blocks_per_cluster);
	imap->im_boffset = (अचिन्हित लघु)(offset << mp->m_sb.sb_inodelog);

	/*
	 * If the inode number maps to a block outside the bounds
	 * of the file प्रणाली then वापस शून्य rather than calling
	 * पढ़ो_buf and panicing when we get an error from the
	 * driver.
	 */
	अगर ((imap->im_blkno + imap->im_len) >
	    XFS_FSB_TO_BB(mp, mp->m_sb.sb_dblocks)) अणु
		xfs_alert(mp,
	"%s: (im_blkno (0x%llx) + im_len (0x%llx)) > sb_dblocks (0x%llx)",
			__func__, (अचिन्हित दीर्घ दीर्घ) imap->im_blkno,
			(अचिन्हित दीर्घ दीर्घ) imap->im_len,
			XFS_FSB_TO_BB(mp, mp->m_sb.sb_dblocks));
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Log specअगरied fields क्रम the ag hdr (inode section). The growth of the agi
 * काष्ठाure over समय requires that we पूर्णांकerpret the buffer as two logical
 * regions delineated by the end of the unlinked list. This is due to the size
 * of the hash table and its location in the middle of the agi.
 *
 * For example, a request to log a field beक्रमe agi_unlinked and a field after
 * agi_unlinked could cause us to log the entire hash table and use an excessive
 * amount of log space. To aव्योम this behavior, log the region up through
 * agi_unlinked in one call and the region after agi_unlinked through the end of
 * the काष्ठाure in another.
 */
व्योम
xfs_ialloc_log_agi(
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	काष्ठा xfs_buf	*bp,		/* allocation group header buffer */
	पूर्णांक		fields)		/* biपंचांगask of fields to log */
अणु
	पूर्णांक			first;		/* first byte number */
	पूर्णांक			last;		/* last byte number */
	अटल स्थिर लघु	offsets[] = अणु	/* field starting offsets */
					/* keep in sync with bit definitions */
		दुरत्व(xfs_agi_t, agi_magicnum),
		दुरत्व(xfs_agi_t, agi_versionnum),
		दुरत्व(xfs_agi_t, agi_seqno),
		दुरत्व(xfs_agi_t, agi_length),
		दुरत्व(xfs_agi_t, agi_count),
		दुरत्व(xfs_agi_t, agi_root),
		दुरत्व(xfs_agi_t, agi_level),
		दुरत्व(xfs_agi_t, agi_मुक्तcount),
		दुरत्व(xfs_agi_t, agi_newino),
		दुरत्व(xfs_agi_t, agi_dirino),
		दुरत्व(xfs_agi_t, agi_unlinked),
		दुरत्व(xfs_agi_t, agi_मुक्त_root),
		दुरत्व(xfs_agi_t, agi_मुक्त_level),
		दुरत्व(xfs_agi_t, agi_iblocks),
		माप(xfs_agi_t)
	पूर्ण;
#अगर_घोषित DEBUG
	काष्ठा xfs_agi		*agi = bp->b_addr;

	ASSERT(agi->agi_magicnum == cpu_to_be32(XFS_AGI_MAGIC));
#पूर्ण_अगर

	/*
	 * Compute byte offsets क्रम the first and last fields in the first
	 * region and log the agi buffer. This only logs up through
	 * agi_unlinked.
	 */
	अगर (fields & XFS_AGI_ALL_BITS_R1) अणु
		xfs_btree_offsets(fields, offsets, XFS_AGI_NUM_BITS_R1,
				  &first, &last);
		xfs_trans_log_buf(tp, bp, first, last);
	पूर्ण

	/*
	 * Mask off the bits in the first region and calculate the first and
	 * last field offsets क्रम any bits in the second region.
	 */
	fields &= ~XFS_AGI_ALL_BITS_R1;
	अगर (fields) अणु
		xfs_btree_offsets(fields, offsets, XFS_AGI_NUM_BITS_R2,
				  &first, &last);
		xfs_trans_log_buf(tp, bp, first, last);
	पूर्ण
पूर्ण

अटल xfs_failaddr_t
xfs_agi_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	काष्ठा xfs_agi	*agi = bp->b_addr;
	पूर्णांक		i;

	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		अगर (!uuid_equal(&agi->agi_uuid, &mp->m_sb.sb_meta_uuid))
			वापस __this_address;
		अगर (!xfs_log_check_lsn(mp, be64_to_cpu(agi->agi_lsn)))
			वापस __this_address;
	पूर्ण

	/*
	 * Validate the magic number of the agi block.
	 */
	अगर (!xfs_verअगरy_magic(bp, agi->agi_magicnum))
		वापस __this_address;
	अगर (!XFS_AGI_GOOD_VERSION(be32_to_cpu(agi->agi_versionnum)))
		वापस __this_address;

	अगर (be32_to_cpu(agi->agi_level) < 1 ||
	    be32_to_cpu(agi->agi_level) > M_IGEO(mp)->inobt_maxlevels)
		वापस __this_address;

	अगर (xfs_sb_version_hasfinobt(&mp->m_sb) &&
	    (be32_to_cpu(agi->agi_मुक्त_level) < 1 ||
	     be32_to_cpu(agi->agi_मुक्त_level) > M_IGEO(mp)->inobt_maxlevels))
		वापस __this_address;

	/*
	 * during growfs operations, the perag is not fully initialised,
	 * so we can't use it for any useful checking. growfs ensures we can't
	 * use it by using uncached buffers that करोn't have the perag attached
	 * so we can detect and aव्योम this problem.
	 */
	अगर (bp->b_pag && be32_to_cpu(agi->agi_seqno) != bp->b_pag->pag_agno)
		वापस __this_address;

	क्रम (i = 0; i < XFS_AGI_UNLINKED_BUCKETS; i++) अणु
		अगर (agi->agi_unlinked[i] == cpu_to_be32(शून्यAGINO))
			जारी;
		अगर (!xfs_verअगरy_ino(mp, be32_to_cpu(agi->agi_unlinked[i])))
			वापस __this_address;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
xfs_agi_पढ़ो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount *mp = bp->b_mount;
	xfs_failaddr_t	fa;

	अगर (xfs_sb_version_hascrc(&mp->m_sb) &&
	    !xfs_buf_verअगरy_cksum(bp, XFS_AGI_CRC_OFF))
		xfs_verअगरier_error(bp, -EFSBADCRC, __this_address);
	अन्यथा अणु
		fa = xfs_agi_verअगरy(bp);
		अगर (XFS_TEST_ERROR(fa, mp, XFS_ERRTAG_IALLOC_READ_AGI))
			xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
	पूर्ण
पूर्ण

अटल व्योम
xfs_agi_ग_लिखो_verअगरy(
	काष्ठा xfs_buf	*bp)
अणु
	काष्ठा xfs_mount	*mp = bp->b_mount;
	काष्ठा xfs_buf_log_item	*bip = bp->b_log_item;
	काष्ठा xfs_agi		*agi = bp->b_addr;
	xfs_failaddr_t		fa;

	fa = xfs_agi_verअगरy(bp);
	अगर (fa) अणु
		xfs_verअगरier_error(bp, -EFSCORRUPTED, fa);
		वापस;
	पूर्ण

	अगर (!xfs_sb_version_hascrc(&mp->m_sb))
		वापस;

	अगर (bip)
		agi->agi_lsn = cpu_to_be64(bip->bli_item.li_lsn);
	xfs_buf_update_cksum(bp, XFS_AGI_CRC_OFF);
पूर्ण

स्थिर काष्ठा xfs_buf_ops xfs_agi_buf_ops = अणु
	.name = "xfs_agi",
	.magic = अणु cpu_to_be32(XFS_AGI_MAGIC), cpu_to_be32(XFS_AGI_MAGIC) पूर्ण,
	.verअगरy_पढ़ो = xfs_agi_पढ़ो_verअगरy,
	.verअगरy_ग_लिखो = xfs_agi_ग_लिखो_verअगरy,
	.verअगरy_काष्ठा = xfs_agi_verअगरy,
पूर्ण;

/*
 * Read in the allocation group header (inode allocation section)
 */
पूर्णांक
xfs_पढ़ो_agi(
	काष्ठा xfs_mount	*mp,	/* file प्रणाली mount काष्ठाure */
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	xfs_agnumber_t		agno,	/* allocation group number */
	काष्ठा xfs_buf		**bpp)	/* allocation group hdr buf */
अणु
	पूर्णांक			error;

	trace_xfs_पढ़ो_agi(mp, agno);

	ASSERT(agno != शून्यAGNUMBER);
	error = xfs_trans_पढ़ो_buf(mp, tp, mp->m_ddev_targp,
			XFS_AG_DADDR(mp, agno, XFS_AGI_DADDR(mp)),
			XFS_FSS_TO_BB(mp, 1), 0, bpp, &xfs_agi_buf_ops);
	अगर (error)
		वापस error;
	अगर (tp)
		xfs_trans_buf_set_type(tp, *bpp, XFS_BLFT_AGI_BUF);

	xfs_buf_set_ref(*bpp, XFS_AGI_REF);
	वापस 0;
पूर्ण

पूर्णांक
xfs_ialloc_पढ़ो_agi(
	काष्ठा xfs_mount	*mp,	/* file प्रणाली mount काष्ठाure */
	काष्ठा xfs_trans	*tp,	/* transaction poपूर्णांकer */
	xfs_agnumber_t		agno,	/* allocation group number */
	काष्ठा xfs_buf		**bpp)	/* allocation group hdr buf */
अणु
	काष्ठा xfs_agi		*agi;	/* allocation group header */
	काष्ठा xfs_perag	*pag;	/* per allocation group data */
	पूर्णांक			error;

	trace_xfs_ialloc_पढ़ो_agi(mp, agno);

	error = xfs_पढ़ो_agi(mp, tp, agno, bpp);
	अगर (error)
		वापस error;

	agi = (*bpp)->b_addr;
	pag = (*bpp)->b_pag;
	अगर (!pag->pagi_init) अणु
		pag->pagi_मुक्तcount = be32_to_cpu(agi->agi_मुक्तcount);
		pag->pagi_count = be32_to_cpu(agi->agi_count);
		pag->pagi_init = 1;
	पूर्ण

	/*
	 * It's possible क्रम these to be out of sync अगर
	 * we are in the middle of a क्रमced shutकरोwn.
	 */
	ASSERT(pag->pagi_मुक्तcount == be32_to_cpu(agi->agi_मुक्तcount) ||
		XFS_FORCED_SHUTDOWN(mp));
	वापस 0;
पूर्ण

/*
 * Read in the agi to initialise the per-ag data in the mount काष्ठाure
 */
पूर्णांक
xfs_ialloc_pagi_init(
	xfs_mount_t	*mp,		/* file प्रणाली mount काष्ठाure */
	xfs_trans_t	*tp,		/* transaction poपूर्णांकer */
	xfs_agnumber_t	agno)		/* allocation group number */
अणु
	काष्ठा xfs_buf	*bp = शून्य;
	पूर्णांक		error;

	error = xfs_ialloc_पढ़ो_agi(mp, tp, agno, &bp);
	अगर (error)
		वापस error;
	अगर (bp)
		xfs_trans_brअन्यथा(tp, bp);
	वापस 0;
पूर्ण

/* Is there an inode record covering a given range of inode numbers? */
पूर्णांक
xfs_ialloc_has_inode_record(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agino_t		low,
	xfs_agino_t		high,
	bool			*exists)
अणु
	काष्ठा xfs_inobt_rec_incore	irec;
	xfs_agino_t		agino;
	uपूर्णांक16_t		holemask;
	पूर्णांक			has_record;
	पूर्णांक			i;
	पूर्णांक			error;

	*exists = false;
	error = xfs_inobt_lookup(cur, low, XFS_LOOKUP_LE, &has_record);
	जबतक (error == 0 && has_record) अणु
		error = xfs_inobt_get_rec(cur, &irec, &has_record);
		अगर (error || irec.ir_startino > high)
			अवरोध;

		agino = irec.ir_startino;
		holemask = irec.ir_holemask;
		क्रम (i = 0; i < XFS_INOBT_HOLEMASK_BITS; holemask >>= 1,
				i++, agino += XFS_INODES_PER_HOLEMASK_BIT) अणु
			अगर (holemask & 1)
				जारी;
			अगर (agino + XFS_INODES_PER_HOLEMASK_BIT > low &&
					agino <= high) अणु
				*exists = true;
				वापस 0;
			पूर्ण
		पूर्ण

		error = xfs_btree_increment(cur, 0, &has_record);
	पूर्ण
	वापस error;
पूर्ण

/* Is there an inode record covering a given extent? */
पूर्णांक
xfs_ialloc_has_inodes_at_extent(
	काष्ठा xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	xfs_extlen_t		len,
	bool			*exists)
अणु
	xfs_agino_t		low;
	xfs_agino_t		high;

	low = XFS_AGB_TO_AGINO(cur->bc_mp, bno);
	high = XFS_AGB_TO_AGINO(cur->bc_mp, bno + len) - 1;

	वापस xfs_ialloc_has_inode_record(cur, low, high, exists);
पूर्ण

काष्ठा xfs_ialloc_count_inodes अणु
	xfs_agino_t			count;
	xfs_agino_t			मुक्तcount;
पूर्ण;

/* Record inode counts across all inobt records. */
STATIC पूर्णांक
xfs_ialloc_count_inodes_rec(
	काष्ठा xfs_btree_cur		*cur,
	जोड़ xfs_btree_rec		*rec,
	व्योम				*priv)
अणु
	काष्ठा xfs_inobt_rec_incore	irec;
	काष्ठा xfs_ialloc_count_inodes	*ci = priv;

	xfs_inobt_btrec_to_irec(cur->bc_mp, rec, &irec);
	ci->count += irec.ir_count;
	ci->मुक्तcount += irec.ir_मुक्तcount;

	वापस 0;
पूर्ण

/* Count allocated and मुक्त inodes under an inobt. */
पूर्णांक
xfs_ialloc_count_inodes(
	काष्ठा xfs_btree_cur		*cur,
	xfs_agino_t			*count,
	xfs_agino_t			*मुक्तcount)
अणु
	काष्ठा xfs_ialloc_count_inodes	ci = अणु0पूर्ण;
	पूर्णांक				error;

	ASSERT(cur->bc_btnum == XFS_BTNUM_INO);
	error = xfs_btree_query_all(cur, xfs_ialloc_count_inodes_rec, &ci);
	अगर (error)
		वापस error;

	*count = ci.count;
	*मुक्तcount = ci.मुक्तcount;
	वापस 0;
पूर्ण

/*
 * Initialize inode-related geometry inक्रमmation.
 *
 * Compute the inode btree min and max levels and set maxicount.
 *
 * Set the inode cluster size.  This may still be overridden by the file
 * प्रणाली block size अगर it is larger than the chosen cluster size.
 *
 * For v5 fileप्रणालीs, scale the cluster size with the inode size to keep a
 * स्थिरant ratio of inode per cluster buffer, but only अगर mkfs has set the
 * inode alignment value appropriately क्रम larger cluster sizes.
 *
 * Then compute the inode cluster alignment inक्रमmation.
 */
व्योम
xfs_ialloc_setup_geometry(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_sb		*sbp = &mp->m_sb;
	काष्ठा xfs_ino_geometry	*igeo = M_IGEO(mp);
	uपूर्णांक64_t		icount;
	uपूर्णांक			inodes;

	igeo->new_dअगरlags2 = 0;
	अगर (xfs_sb_version_hasbigसमय(&mp->m_sb))
		igeo->new_dअगरlags2 |= XFS_DIFLAG2_BIGTIME;

	/* Compute inode btree geometry. */
	igeo->agino_log = sbp->sb_inopblog + sbp->sb_agblklog;
	igeo->inobt_mxr[0] = xfs_inobt_maxrecs(mp, sbp->sb_blocksize, 1);
	igeo->inobt_mxr[1] = xfs_inobt_maxrecs(mp, sbp->sb_blocksize, 0);
	igeo->inobt_mnr[0] = igeo->inobt_mxr[0] / 2;
	igeo->inobt_mnr[1] = igeo->inobt_mxr[1] / 2;

	igeo->ialloc_inos = max_t(uपूर्णांक16_t, XFS_INODES_PER_CHUNK,
			sbp->sb_inopblock);
	igeo->ialloc_blks = igeo->ialloc_inos >> sbp->sb_inopblog;

	अगर (sbp->sb_spino_align)
		igeo->ialloc_min_blks = sbp->sb_spino_align;
	अन्यथा
		igeo->ialloc_min_blks = igeo->ialloc_blks;

	/* Compute and fill in value of m_ino_geo.inobt_maxlevels. */
	inodes = (1LL << XFS_INO_AGINO_BITS(mp)) >> XFS_INODES_PER_CHUNK_LOG;
	igeo->inobt_maxlevels = xfs_btree_compute_maxlevels(igeo->inobt_mnr,
			inodes);

	/*
	 * Set the maximum inode count क्रम this fileप्रणाली, being careful not
	 * to use obviously garbage sb_inopblog/sb_inopblock values.  Regular
	 * users should never get here due to failing sb verअगरication, but
	 * certain users (xfs_db) need to be usable even with corrupt metadata.
	 */
	अगर (sbp->sb_imax_pct && igeo->ialloc_blks) अणु
		/*
		 * Make sure the maximum inode count is a multiple
		 * of the units we allocate inodes in.
		 */
		icount = sbp->sb_dblocks * sbp->sb_imax_pct;
		करो_भाग(icount, 100);
		करो_भाग(icount, igeo->ialloc_blks);
		igeo->maxicount = XFS_FSB_TO_INO(mp,
				icount * igeo->ialloc_blks);
	पूर्ण अन्यथा अणु
		igeo->maxicount = 0;
	पूर्ण

	/*
	 * Compute the desired size of an inode cluster buffer size, which
	 * starts at 8K and (on v5 fileप्रणालीs) scales up with larger inode
	 * sizes.
	 *
	 * Preserve the desired inode cluster size because the sparse inodes
	 * feature uses that desired size (not the actual size) to compute the
	 * sparse inode alignment.  The mount code validates this value, so we
	 * cannot change the behavior.
	 */
	igeo->inode_cluster_size_raw = XFS_INODE_BIG_CLUSTER_SIZE;
	अगर (xfs_sb_version_has_v3inode(&mp->m_sb)) अणु
		पूर्णांक	new_size = igeo->inode_cluster_size_raw;

		new_size *= mp->m_sb.sb_inodesize / XFS_DINODE_MIN_SIZE;
		अगर (mp->m_sb.sb_inoalignmt >= XFS_B_TO_FSBT(mp, new_size))
			igeo->inode_cluster_size_raw = new_size;
	पूर्ण

	/* Calculate inode cluster ratios. */
	अगर (igeo->inode_cluster_size_raw > mp->m_sb.sb_blocksize)
		igeo->blocks_per_cluster = XFS_B_TO_FSBT(mp,
				igeo->inode_cluster_size_raw);
	अन्यथा
		igeo->blocks_per_cluster = 1;
	igeo->inode_cluster_size = XFS_FSB_TO_B(mp, igeo->blocks_per_cluster);
	igeo->inodes_per_cluster = XFS_FSB_TO_INO(mp, igeo->blocks_per_cluster);

	/* Calculate inode cluster alignment. */
	अगर (xfs_sb_version_hasalign(&mp->m_sb) &&
	    mp->m_sb.sb_inoalignmt >= igeo->blocks_per_cluster)
		igeo->cluster_align = mp->m_sb.sb_inoalignmt;
	अन्यथा
		igeo->cluster_align = 1;
	igeo->inoalign_mask = igeo->cluster_align - 1;
	igeo->cluster_align_inodes = XFS_FSB_TO_INO(mp, igeo->cluster_align);

	/*
	 * If we are using stripe alignment, check whether
	 * the stripe unit is a multiple of the inode alignment
	 */
	अगर (mp->m_dalign && igeo->inoalign_mask &&
	    !(mp->m_dalign & igeo->inoalign_mask))
		igeo->ialloc_align = mp->m_dalign;
	अन्यथा
		igeo->ialloc_align = 0;
पूर्ण

/* Compute the location of the root directory inode that is laid out by mkfs. */
xfs_ino_t
xfs_ialloc_calc_rootino(
	काष्ठा xfs_mount	*mp,
	पूर्णांक			sunit)
अणु
	काष्ठा xfs_ino_geometry	*igeo = M_IGEO(mp);
	xfs_agblock_t		first_bno;

	/*
	 * Pre-calculate the geometry of AG 0.  We know what it looks like
	 * because libxfs knows how to create allocation groups now.
	 *
	 * first_bno is the first block in which mkfs could possibly have
	 * allocated the root directory inode, once we factor in the metadata
	 * that mkfs क्रमmats beक्रमe it.  Namely, the four AG headers...
	 */
	first_bno = howmany(4 * mp->m_sb.sb_sectsize, mp->m_sb.sb_blocksize);

	/* ...the two मुक्त space btree roots... */
	first_bno += 2;

	/* ...the inode btree root... */
	first_bno += 1;

	/* ...the initial AGFL... */
	first_bno += xfs_alloc_min_मुक्तlist(mp, शून्य);

	/* ...the मुक्त inode btree root... */
	अगर (xfs_sb_version_hasfinobt(&mp->m_sb))
		first_bno++;

	/* ...the reverse mapping btree root... */
	अगर (xfs_sb_version_hasrmapbt(&mp->m_sb))
		first_bno++;

	/* ...the reference count btree... */
	अगर (xfs_sb_version_hasreflink(&mp->m_sb))
		first_bno++;

	/*
	 * ...and the log, अगर it is allocated in the first allocation group.
	 *
	 * This can happen with fileप्रणालीs that only have a single
	 * allocation group, or very odd geometries created by old mkfs
	 * versions on very small fileप्रणालीs.
	 */
	अगर (mp->m_sb.sb_logstart &&
	    XFS_FSB_TO_AGNO(mp, mp->m_sb.sb_logstart) == 0)
		 first_bno += mp->m_sb.sb_logblocks;

	/*
	 * Now round first_bno up to whatever allocation alignment is given
	 * by the fileप्रणाली or was passed in.
	 */
	अगर (xfs_sb_version_hasdalign(&mp->m_sb) && igeo->ialloc_align > 0)
		first_bno = roundup(first_bno, sunit);
	अन्यथा अगर (xfs_sb_version_hasalign(&mp->m_sb) &&
			mp->m_sb.sb_inoalignmt > 1)
		first_bno = roundup(first_bno, mp->m_sb.sb_inoalignmt);

	वापस XFS_AGINO_TO_INO(mp, 0, XFS_AGB_TO_AGINO(mp, first_bno));
पूर्ण
