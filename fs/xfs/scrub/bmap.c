<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Oracle.  All Rights Reserved.
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */
#समावेश "xfs.h"
#समावेश "xfs_fs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_btree.h"
#समावेश "xfs_bit.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_alloc.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_bmap_btree.h"
#समावेश "xfs_rmap.h"
#समावेश "xfs_rmap_btree.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/btree.h"

/* Set us up with an inode's bmap. */
पूर्णांक
xchk_setup_inode_bmap(
	काष्ठा xfs_scrub	*sc)
अणु
	पूर्णांक			error;

	error = xchk_get_inode(sc);
	अगर (error)
		जाओ out;

	sc->ilock_flags = XFS_IOLOCK_EXCL | XFS_MMAPLOCK_EXCL;
	xfs_ilock(sc->ip, sc->ilock_flags);

	/*
	 * We करोn't want any ephemeral data विभाजन updates sitting around
	 * जबतक we inspect block mappings, so रुको क्रम directio to finish
	 * and flush dirty data अगर we have delalloc reservations.
	 */
	अगर (S_ISREG(VFS_I(sc->ip)->i_mode) &&
	    sc->sm->sm_type == XFS_SCRUB_TYPE_BMBTD) अणु
		काष्ठा address_space	*mapping = VFS_I(sc->ip)->i_mapping;

		inode_dio_रुको(VFS_I(sc->ip));

		/*
		 * Try to flush all incore state to disk beक्रमe we examine the
		 * space mappings क्रम the data विभाजन.  Leave accumulated errors
		 * in the mapping क्रम the ग_लिखोr thपढ़ोs to consume.
		 *
		 * On ENOSPC or EIO ग_लिखोback errors, we जारी पूर्णांकo the
		 * extent mapping checks because ग_लिखो failures करो not
		 * necessarily imply anything about the correctness of the file
		 * metadata.  The metadata and the file data could be on
		 * completely separate devices; a media failure might only
		 * affect a subset of the disk, etc.  We can handle delalloc
		 * extents in the scrubber, so leaving them in memory is fine.
		 */
		error = filemap_fdataग_लिखो(mapping);
		अगर (!error)
			error = filemap_fdataरुको_keep_errors(mapping);
		अगर (error && (error != -ENOSPC && error != -EIO))
			जाओ out;
	पूर्ण

	/* Got the inode, lock it and we're पढ़ोy to go. */
	error = xchk_trans_alloc(sc, 0);
	अगर (error)
		जाओ out;
	sc->ilock_flags |= XFS_ILOCK_EXCL;
	xfs_ilock(sc->ip, XFS_ILOCK_EXCL);

out:
	/* scrub tearकरोwn will unlock and release the inode */
	वापस error;
पूर्ण

/*
 * Inode विभाजन block mapping (BMBT) scrubber.
 * More complex than the others because we have to scrub
 * all the extents regardless of whether or not the विभाजन
 * is in btree क्रमmat.
 */

काष्ठा xchk_bmap_info अणु
	काष्ठा xfs_scrub	*sc;
	xfs_fileoff_t		lastoff;
	bool			is_rt;
	bool			is_shared;
	bool			was_loaded;
	पूर्णांक			whichविभाजन;
पूर्ण;

/* Look क्रम a corresponding rmap क्रम this irec. */
अटल अंतरभूत bool
xchk_bmap_get_rmap(
	काष्ठा xchk_bmap_info	*info,
	काष्ठा xfs_bmbt_irec	*irec,
	xfs_agblock_t		agbno,
	uपूर्णांक64_t		owner,
	काष्ठा xfs_rmap_irec	*rmap)
अणु
	xfs_fileoff_t		offset;
	अचिन्हित पूर्णांक		rflags = 0;
	पूर्णांक			has_rmap;
	पूर्णांक			error;

	अगर (info->whichविभाजन == XFS_ATTR_FORK)
		rflags |= XFS_RMAP_ATTR_FORK;
	अगर (irec->br_state == XFS_EXT_UNWRITTEN)
		rflags |= XFS_RMAP_UNWRITTEN;

	/*
	 * CoW staging extents are owned (on disk) by the refcountbt, so
	 * their rmaps करो not have offsets.
	 */
	अगर (info->whichविभाजन == XFS_COW_FORK)
		offset = 0;
	अन्यथा
		offset = irec->br_startoff;

	/*
	 * If the caller thinks this could be a shared bmbt extent (IOWs,
	 * any data विभाजन extent of a reflink inode) then we have to use the
	 * range rmap lookup to make sure we get the correct owner/offset.
	 */
	अगर (info->is_shared) अणु
		error = xfs_rmap_lookup_le_range(info->sc->sa.rmap_cur, agbno,
				owner, offset, rflags, rmap, &has_rmap);
		अगर (!xchk_should_check_xref(info->sc, &error,
				&info->sc->sa.rmap_cur))
			वापस false;
		जाओ out;
	पूर्ण

	/*
	 * Otherwise, use the (faster) regular lookup.
	 */
	error = xfs_rmap_lookup_le(info->sc->sa.rmap_cur, agbno, 0, owner,
			offset, rflags, &has_rmap);
	अगर (!xchk_should_check_xref(info->sc, &error,
			&info->sc->sa.rmap_cur))
		वापस false;
	अगर (!has_rmap)
		जाओ out;

	error = xfs_rmap_get_rec(info->sc->sa.rmap_cur, rmap, &has_rmap);
	अगर (!xchk_should_check_xref(info->sc, &error,
			&info->sc->sa.rmap_cur))
		वापस false;

out:
	अगर (!has_rmap)
		xchk_fblock_xref_set_corrupt(info->sc, info->whichविभाजन,
			irec->br_startoff);
	वापस has_rmap;
पूर्ण

/* Make sure that we have rmapbt records क्रम this extent. */
STATIC व्योम
xchk_bmap_xref_rmap(
	काष्ठा xchk_bmap_info	*info,
	काष्ठा xfs_bmbt_irec	*irec,
	xfs_agblock_t		agbno)
अणु
	काष्ठा xfs_rmap_irec	rmap;
	अचिन्हित दीर्घ दीर्घ	rmap_end;
	uपूर्णांक64_t		owner;

	अगर (!info->sc->sa.rmap_cur || xchk_skip_xref(info->sc->sm))
		वापस;

	अगर (info->whichविभाजन == XFS_COW_FORK)
		owner = XFS_RMAP_OWN_COW;
	अन्यथा
		owner = info->sc->ip->i_ino;

	/* Find the rmap record क्रम this irec. */
	अगर (!xchk_bmap_get_rmap(info, irec, agbno, owner, &rmap))
		वापस;

	/* Check the rmap. */
	rmap_end = (अचिन्हित दीर्घ दीर्घ)rmap.rm_startblock + rmap.rm_blockcount;
	अगर (rmap.rm_startblock > agbno ||
	    agbno + irec->br_blockcount > rmap_end)
		xchk_fblock_xref_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	/*
	 * Check the logical offsets अगर applicable.  CoW staging extents
	 * करोn't track logical offsets since the mappings only exist in
	 * memory.
	 */
	अगर (info->whichविभाजन != XFS_COW_FORK) अणु
		rmap_end = (अचिन्हित दीर्घ दीर्घ)rmap.rm_offset +
				rmap.rm_blockcount;
		अगर (rmap.rm_offset > irec->br_startoff ||
		    irec->br_startoff + irec->br_blockcount > rmap_end)
			xchk_fblock_xref_set_corrupt(info->sc,
					info->whichविभाजन, irec->br_startoff);
	पूर्ण

	अगर (rmap.rm_owner != owner)
		xchk_fblock_xref_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	/*
	 * Check क्रम discrepancies between the unwritten flag in the irec and
	 * the rmap.  Note that the (in-memory) CoW विभाजन distinguishes between
	 * unwritten and written extents, but we करोn't track that in the rmap
	 * records because the blocks are owned (on-disk) by the refcountbt,
	 * which करोesn't track unwritten state.
	 */
	अगर (owner != XFS_RMAP_OWN_COW &&
	    !!(irec->br_state == XFS_EXT_UNWRITTEN) !=
	    !!(rmap.rm_flags & XFS_RMAP_UNWRITTEN))
		xchk_fblock_xref_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	अगर (!!(info->whichविभाजन == XFS_ATTR_FORK) !=
	    !!(rmap.rm_flags & XFS_RMAP_ATTR_FORK))
		xchk_fblock_xref_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);
	अगर (rmap.rm_flags & XFS_RMAP_BMBT_BLOCK)
		xchk_fblock_xref_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);
पूर्ण

/* Cross-reference a single rtdev extent record. */
STATIC व्योम
xchk_bmap_rt_iextent_xref(
	काष्ठा xfs_inode	*ip,
	काष्ठा xchk_bmap_info	*info,
	काष्ठा xfs_bmbt_irec	*irec)
अणु
	xchk_xref_is_used_rt_space(info->sc, irec->br_startblock,
			irec->br_blockcount);
पूर्ण

/* Cross-reference a single datadev extent record. */
STATIC व्योम
xchk_bmap_iextent_xref(
	काष्ठा xfs_inode	*ip,
	काष्ठा xchk_bmap_info	*info,
	काष्ठा xfs_bmbt_irec	*irec)
अणु
	काष्ठा xfs_mount	*mp = info->sc->mp;
	xfs_agnumber_t		agno;
	xfs_agblock_t		agbno;
	xfs_extlen_t		len;
	पूर्णांक			error;

	agno = XFS_FSB_TO_AGNO(mp, irec->br_startblock);
	agbno = XFS_FSB_TO_AGBNO(mp, irec->br_startblock);
	len = irec->br_blockcount;

	error = xchk_ag_init(info->sc, agno, &info->sc->sa);
	अगर (!xchk_fblock_process_error(info->sc, info->whichविभाजन,
			irec->br_startoff, &error))
		वापस;

	xchk_xref_is_used_space(info->sc, agbno, len);
	xchk_xref_is_not_inode_chunk(info->sc, agbno, len);
	xchk_bmap_xref_rmap(info, irec, agbno);
	चयन (info->whichविभाजन) अणु
	हाल XFS_DATA_FORK:
		अगर (xfs_is_reflink_inode(info->sc->ip))
			अवरोध;
		/* fall through */
	हाल XFS_ATTR_FORK:
		xchk_xref_is_not_shared(info->sc, agbno,
				irec->br_blockcount);
		अवरोध;
	हाल XFS_COW_FORK:
		xchk_xref_is_cow_staging(info->sc, agbno,
				irec->br_blockcount);
		अवरोध;
	पूर्ण

	xchk_ag_मुक्त(info->sc, &info->sc->sa);
पूर्ण

/*
 * Directories and attr विभाजनs should never have blocks that can't be addressed
 * by a xfs_dablk_t.
 */
STATIC व्योम
xchk_bmap_dirattr_extent(
	काष्ठा xfs_inode	*ip,
	काष्ठा xchk_bmap_info	*info,
	काष्ठा xfs_bmbt_irec	*irec)
अणु
	काष्ठा xfs_mount	*mp = ip->i_mount;
	xfs_fileoff_t		off;

	अगर (!S_ISसूची(VFS_I(ip)->i_mode) && info->whichविभाजन != XFS_ATTR_FORK)
		वापस;

	अगर (!xfs_verअगरy_dablk(mp, irec->br_startoff))
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	off = irec->br_startoff + irec->br_blockcount - 1;
	अगर (!xfs_verअगरy_dablk(mp, off))
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन, off);
पूर्ण

/* Scrub a single extent record. */
STATIC पूर्णांक
xchk_bmap_iextent(
	काष्ठा xfs_inode	*ip,
	काष्ठा xchk_bmap_info	*info,
	काष्ठा xfs_bmbt_irec	*irec)
अणु
	काष्ठा xfs_mount	*mp = info->sc->mp;
	पूर्णांक			error = 0;

	/*
	 * Check क्रम out-of-order extents.  This record could have come
	 * from the incore list, क्रम which there is no ordering check.
	 */
	अगर (irec->br_startoff < info->lastoff)
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	अगर (!xfs_verअगरy_fileext(mp, irec->br_startoff, irec->br_blockcount))
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	xchk_bmap_dirattr_extent(ip, info, irec);

	/* There should never be a "hole" extent in either extent list. */
	अगर (irec->br_startblock == HOLESTARTBLOCK)
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	/*
	 * Check क्रम delalloc extents.  We never iterate the ones in the
	 * in-core extent scan, and we should never see these in the bmbt.
	 */
	अगर (isnullstartblock(irec->br_startblock))
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	/* Make sure the extent poपूर्णांकs to a valid place. */
	अगर (irec->br_blockcount > MAXEXTLEN)
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);
	अगर (info->is_rt &&
	    !xfs_verअगरy_rtext(mp, irec->br_startblock, irec->br_blockcount))
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);
	अगर (!info->is_rt &&
	    !xfs_verअगरy_fsbext(mp, irec->br_startblock, irec->br_blockcount))
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	/* We करोn't allow unwritten extents on attr विभाजनs. */
	अगर (irec->br_state == XFS_EXT_UNWRITTEN &&
	    info->whichविभाजन == XFS_ATTR_FORK)
		xchk_fblock_set_corrupt(info->sc, info->whichविभाजन,
				irec->br_startoff);

	अगर (info->sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस 0;

	अगर (info->is_rt)
		xchk_bmap_rt_iextent_xref(ip, info, irec);
	अन्यथा
		xchk_bmap_iextent_xref(ip, info, irec);

	info->lastoff = irec->br_startoff + irec->br_blockcount;
	वापस error;
पूर्ण

/* Scrub a bmbt record. */
STATIC पूर्णांक
xchk_bmapbt_rec(
	काष्ठा xchk_btree	*bs,
	जोड़ xfs_btree_rec	*rec)
अणु
	काष्ठा xfs_bmbt_irec	irec;
	काष्ठा xfs_bmbt_irec	iext_irec;
	काष्ठा xfs_iext_cursor	icur;
	काष्ठा xchk_bmap_info	*info = bs->निजी;
	काष्ठा xfs_inode	*ip = bs->cur->bc_ino.ip;
	काष्ठा xfs_buf		*bp = शून्य;
	काष्ठा xfs_btree_block	*block;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, info->whichविभाजन);
	uपूर्णांक64_t		owner;
	पूर्णांक			i;

	/*
	 * Check the owners of the btree blocks up to the level below
	 * the root since the verअगरiers करोn't करो that.
	 */
	अगर (xfs_sb_version_hascrc(&bs->cur->bc_mp->m_sb) &&
	    bs->cur->bc_ptrs[0] == 1) अणु
		क्रम (i = 0; i < bs->cur->bc_nlevels - 1; i++) अणु
			block = xfs_btree_get_block(bs->cur, i, &bp);
			owner = be64_to_cpu(block->bb_u.l.bb_owner);
			अगर (owner != ip->i_ino)
				xchk_fblock_set_corrupt(bs->sc,
						info->whichविभाजन, 0);
		पूर्ण
	पूर्ण

	/*
	 * Check that the incore extent tree contains an extent that matches
	 * this one exactly.  We validate those cached bmaps later, so we करोn't
	 * need to check them here.  If the incore extent tree was just loaded
	 * from disk by the scrubber, we assume that its contents match what's
	 * on disk (we still hold the ILOCK) and skip the equivalence check.
	 */
	अगर (!info->was_loaded)
		वापस 0;

	xfs_bmbt_disk_get_all(&rec->bmbt, &irec);
	अगर (!xfs_iext_lookup_extent(ip, अगरp, irec.br_startoff, &icur,
				&iext_irec) ||
	    irec.br_startoff != iext_irec.br_startoff ||
	    irec.br_startblock != iext_irec.br_startblock ||
	    irec.br_blockcount != iext_irec.br_blockcount ||
	    irec.br_state != iext_irec.br_state)
		xchk_fblock_set_corrupt(bs->sc, info->whichविभाजन,
				irec.br_startoff);
	वापस 0;
पूर्ण

/* Scan the btree records. */
STATIC पूर्णांक
xchk_bmap_btree(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			whichविभाजन,
	काष्ठा xchk_bmap_info	*info)
अणु
	काष्ठा xfs_owner_info	oinfo;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(sc->ip, whichविभाजन);
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_inode	*ip = sc->ip;
	काष्ठा xfs_btree_cur	*cur;
	पूर्णांक			error;

	/* Load the incore bmap cache अगर it's not loaded. */
	info->was_loaded = !xfs_need_iपढ़ो_extents(अगरp);

	error = xfs_iपढ़ो_extents(sc->tp, ip, whichविभाजन);
	अगर (!xchk_fblock_process_error(sc, whichविभाजन, 0, &error))
		जाओ out;

	/* Check the btree काष्ठाure. */
	cur = xfs_bmbt_init_cursor(mp, sc->tp, ip, whichविभाजन);
	xfs_rmap_ino_bmbt_owner(&oinfo, ip->i_ino, whichविभाजन);
	error = xchk_btree(sc, cur, xchk_bmapbt_rec, &oinfo, info);
	xfs_btree_del_cursor(cur, error);
out:
	वापस error;
पूर्ण

काष्ठा xchk_bmap_check_rmap_info अणु
	काष्ठा xfs_scrub	*sc;
	पूर्णांक			whichविभाजन;
	काष्ठा xfs_iext_cursor	icur;
पूर्ण;

/* Can we find bmaps that fit this rmap? */
STATIC पूर्णांक
xchk_bmap_check_rmap(
	काष्ठा xfs_btree_cur		*cur,
	काष्ठा xfs_rmap_irec		*rec,
	व्योम				*priv)
अणु
	काष्ठा xfs_bmbt_irec		irec;
	काष्ठा xchk_bmap_check_rmap_info	*sbcri = priv;
	काष्ठा xfs_अगरork		*अगरp;
	काष्ठा xfs_scrub		*sc = sbcri->sc;
	bool				have_map;

	/* Is this even the right विभाजन? */
	अगर (rec->rm_owner != sc->ip->i_ino)
		वापस 0;
	अगर ((sbcri->whichविभाजन == XFS_ATTR_FORK) ^
	    !!(rec->rm_flags & XFS_RMAP_ATTR_FORK))
		वापस 0;
	अगर (rec->rm_flags & XFS_RMAP_BMBT_BLOCK)
		वापस 0;

	/* Now look up the bmbt record. */
	अगरp = XFS_IFORK_PTR(sc->ip, sbcri->whichविभाजन);
	अगर (!अगरp) अणु
		xchk_fblock_set_corrupt(sc, sbcri->whichविभाजन,
				rec->rm_offset);
		जाओ out;
	पूर्ण
	have_map = xfs_iext_lookup_extent(sc->ip, अगरp, rec->rm_offset,
			&sbcri->icur, &irec);
	अगर (!have_map)
		xchk_fblock_set_corrupt(sc, sbcri->whichविभाजन,
				rec->rm_offset);
	/*
	 * bmap extent record lengths are स्थिरrained to 2^21 blocks in length
	 * because of space स्थिरraपूर्णांकs in the on-disk metadata काष्ठाure.
	 * However, rmap extent record lengths are स्थिरrained only by AG
	 * length, so we have to loop through the bmbt to make sure that the
	 * entire rmap is covered by bmbt records.
	 */
	जबतक (have_map) अणु
		अगर (irec.br_startoff != rec->rm_offset)
			xchk_fblock_set_corrupt(sc, sbcri->whichविभाजन,
					rec->rm_offset);
		अगर (irec.br_startblock != XFS_AGB_TO_FSB(sc->mp,
				cur->bc_ag.agno, rec->rm_startblock))
			xchk_fblock_set_corrupt(sc, sbcri->whichविभाजन,
					rec->rm_offset);
		अगर (irec.br_blockcount > rec->rm_blockcount)
			xchk_fblock_set_corrupt(sc, sbcri->whichविभाजन,
					rec->rm_offset);
		अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
			अवरोध;
		rec->rm_startblock += irec.br_blockcount;
		rec->rm_offset += irec.br_blockcount;
		rec->rm_blockcount -= irec.br_blockcount;
		अगर (rec->rm_blockcount == 0)
			अवरोध;
		have_map = xfs_iext_next_extent(अगरp, &sbcri->icur, &irec);
		अगर (!have_map)
			xchk_fblock_set_corrupt(sc, sbcri->whichविभाजन,
					rec->rm_offset);
	पूर्ण

out:
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस -ECANCELED;
	वापस 0;
पूर्ण

/* Make sure each rmap has a corresponding bmbt entry. */
STATIC पूर्णांक
xchk_bmap_check_ag_rmaps(
	काष्ठा xfs_scrub		*sc,
	पूर्णांक				whichविभाजन,
	xfs_agnumber_t			agno)
अणु
	काष्ठा xchk_bmap_check_rmap_info	sbcri;
	काष्ठा xfs_btree_cur		*cur;
	काष्ठा xfs_buf			*agf;
	पूर्णांक				error;

	error = xfs_alloc_पढ़ो_agf(sc->mp, sc->tp, agno, 0, &agf);
	अगर (error)
		वापस error;

	cur = xfs_rmapbt_init_cursor(sc->mp, sc->tp, agf, agno);

	sbcri.sc = sc;
	sbcri.whichविभाजन = whichविभाजन;
	error = xfs_rmap_query_all(cur, xchk_bmap_check_rmap, &sbcri);
	अगर (error == -ECANCELED)
		error = 0;

	xfs_btree_del_cursor(cur, error);
	xfs_trans_brअन्यथा(sc->tp, agf);
	वापस error;
पूर्ण

/* Make sure each rmap has a corresponding bmbt entry. */
STATIC पूर्णांक
xchk_bmap_check_rmaps(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(sc->ip, whichविभाजन);
	xfs_agnumber_t		agno;
	bool			zero_size;
	पूर्णांक			error;

	अगर (!xfs_sb_version_hasrmapbt(&sc->mp->m_sb) ||
	    whichविभाजन == XFS_COW_FORK ||
	    (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
		वापस 0;

	/* Don't support realसमय rmap checks yet. */
	अगर (XFS_IS_REALTIME_INODE(sc->ip) && whichविभाजन == XFS_DATA_FORK)
		वापस 0;

	ASSERT(XFS_IFORK_PTR(sc->ip, whichविभाजन) != शून्य);

	/*
	 * Only करो this क्रम complex maps that are in btree क्रमmat, or क्रम
	 * situations where we would seem to have a size but zero extents.
	 * The inode repair code can zap broken अगरorks, which means we have
	 * to flag this bmap as corrupt अगर there are rmaps that need to be
	 * reattached.
	 */

	अगर (whichविभाजन == XFS_DATA_FORK)
		zero_size = i_size_पढ़ो(VFS_I(sc->ip)) == 0;
	अन्यथा
		zero_size = false;

	अगर (अगरp->अगर_क्रमmat != XFS_DINODE_FMT_BTREE &&
	    (zero_size || अगरp->अगर_nextents > 0))
		वापस 0;

	क्रम (agno = 0; agno < sc->mp->m_sb.sb_agcount; agno++) अणु
		error = xchk_bmap_check_ag_rmaps(sc, whichविभाजन, agno);
		अगर (error)
			वापस error;
		अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Scrub an inode विभाजन's block mappings.
 *
 * First we scan every record in every btree block, अगर applicable.
 * Then we unconditionally scan the incore extent cache.
 */
STATIC पूर्णांक
xchk_bmap(
	काष्ठा xfs_scrub	*sc,
	पूर्णांक			whichविभाजन)
अणु
	काष्ठा xfs_bmbt_irec	irec;
	काष्ठा xchk_bmap_info	info = अणु शून्य पूर्ण;
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_inode	*ip = sc->ip;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	xfs_fileoff_t		enकरोff;
	काष्ठा xfs_iext_cursor	icur;
	पूर्णांक			error = 0;

	/* Non-existent विभाजनs can be ignored. */
	अगर (!अगरp)
		जाओ out;

	info.is_rt = whichविभाजन == XFS_DATA_FORK && XFS_IS_REALTIME_INODE(ip);
	info.whichविभाजन = whichविभाजन;
	info.is_shared = whichविभाजन == XFS_DATA_FORK && xfs_is_reflink_inode(ip);
	info.sc = sc;

	चयन (whichविभाजन) अणु
	हाल XFS_COW_FORK:
		/* No CoW विभाजनs on non-reflink inodes/fileप्रणालीs. */
		अगर (!xfs_is_reflink_inode(ip)) अणु
			xchk_ino_set_corrupt(sc, sc->ip->i_ino);
			जाओ out;
		पूर्ण
		अवरोध;
	हाल XFS_ATTR_FORK:
		अगर (!xfs_sb_version_hasattr(&mp->m_sb) &&
		    !xfs_sb_version_hasattr2(&mp->m_sb))
			xchk_ino_set_corrupt(sc, sc->ip->i_ino);
		अवरोध;
	शेष:
		ASSERT(whichविभाजन == XFS_DATA_FORK);
		अवरोध;
	पूर्ण

	/* Check the विभाजन values */
	चयन (अगरp->अगर_क्रमmat) अणु
	हाल XFS_DINODE_FMT_UUID:
	हाल XFS_DINODE_FMT_DEV:
	हाल XFS_DINODE_FMT_LOCAL:
		/* No mappings to check. */
		जाओ out;
	हाल XFS_DINODE_FMT_EXTENTS:
		अवरोध;
	हाल XFS_DINODE_FMT_BTREE:
		अगर (whichविभाजन == XFS_COW_FORK) अणु
			xchk_fblock_set_corrupt(sc, whichविभाजन, 0);
			जाओ out;
		पूर्ण

		error = xchk_bmap_btree(sc, whichविभाजन, &info);
		अगर (error)
			जाओ out;
		अवरोध;
	शेष:
		xchk_fblock_set_corrupt(sc, whichविभाजन, 0);
		जाओ out;
	पूर्ण

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/* Find the offset of the last extent in the mapping. */
	error = xfs_bmap_last_offset(ip, &enकरोff, whichविभाजन);
	अगर (!xchk_fblock_process_error(sc, whichविभाजन, 0, &error))
		जाओ out;

	/* Scrub extent records. */
	info.lastoff = 0;
	अगरp = XFS_IFORK_PTR(ip, whichविभाजन);
	क्रम_each_xfs_iext(अगरp, &icur, &irec) अणु
		अगर (xchk_should_terminate(sc, &error) ||
		    (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT))
			जाओ out;
		अगर (isnullstartblock(irec.br_startblock))
			जारी;
		अगर (irec.br_startoff >= enकरोff) अणु
			xchk_fblock_set_corrupt(sc, whichविभाजन,
					irec.br_startoff);
			जाओ out;
		पूर्ण
		error = xchk_bmap_iextent(ip, &info, &irec);
		अगर (error)
			जाओ out;
	पूर्ण

	error = xchk_bmap_check_rmaps(sc, whichविभाजन);
	अगर (!xchk_fblock_xref_process_error(sc, whichविभाजन, 0, &error))
		जाओ out;
out:
	वापस error;
पूर्ण

/* Scrub an inode's data विभाजन. */
पूर्णांक
xchk_bmap_data(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_bmap(sc, XFS_DATA_FORK);
पूर्ण

/* Scrub an inode's attr विभाजन. */
पूर्णांक
xchk_bmap_attr(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_bmap(sc, XFS_ATTR_FORK);
पूर्ण

/* Scrub an inode's CoW विभाजन. */
पूर्णांक
xchk_bmap_cow(
	काष्ठा xfs_scrub	*sc)
अणु
	अगर (!xfs_is_reflink_inode(sc->ip))
		वापस -ENOENT;

	वापस xchk_bmap(sc, XFS_COW_FORK);
पूर्ण
