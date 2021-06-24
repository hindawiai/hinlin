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
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"
#समावेश "scrub/dabtree.h"

/* Set us up to scrub directories. */
पूर्णांक
xchk_setup_directory(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_setup_inode_contents(sc, 0);
पूर्ण

/* Directories */

/* Scrub a directory entry. */

काष्ठा xchk_dir_ctx अणु
	/* VFS fill-directory iterator */
	काष्ठा dir_context	dir_iter;

	काष्ठा xfs_scrub	*sc;
पूर्ण;

/* Check that an inode's mode matches a given DT_ type. */
STATIC पूर्णांक
xchk_dir_check_ftype(
	काष्ठा xchk_dir_ctx	*sdc,
	xfs_fileoff_t		offset,
	xfs_ino_t		inum,
	पूर्णांक			dtype)
अणु
	काष्ठा xfs_mount	*mp = sdc->sc->mp;
	काष्ठा xfs_inode	*ip;
	पूर्णांक			ino_dtype;
	पूर्णांक			error = 0;

	अगर (!xfs_sb_version_hasftype(&mp->m_sb)) अणु
		अगर (dtype != DT_UNKNOWN && dtype != DT_सूची)
			xchk_fblock_set_corrupt(sdc->sc, XFS_DATA_FORK,
					offset);
		जाओ out;
	पूर्ण

	/*
	 * Grab the inode poपूर्णांकed to by the dirent.  We release the
	 * inode beक्रमe we cancel the scrub transaction.  Since we're
	 * करोn't know a priori that releasing the inode won't trigger
	 * eofblocks cleanup (which allocates what would be a nested
	 * transaction), we can't use DONTCACHE here because DONTCACHE
	 * inodes can trigger immediate inactive cleanup of the inode.
	 *
	 * If _iget वापसs -EINVAL or -ENOENT then the child inode number is
	 * garbage and the directory is corrupt.  If the _iget वापसs
	 * -EFSCORRUPTED or -EFSBADCRC then the child is corrupt which is a
	 *  cross referencing error.  Any other error is an operational error.
	 */
	error = xfs_iget(mp, sdc->sc->tp, inum, 0, 0, &ip);
	अगर (error == -EINVAL || error == -ENOENT) अणु
		error = -EFSCORRUPTED;
		xchk_fblock_process_error(sdc->sc, XFS_DATA_FORK, 0, &error);
		जाओ out;
	पूर्ण
	अगर (!xchk_fblock_xref_process_error(sdc->sc, XFS_DATA_FORK, offset,
			&error))
		जाओ out;

	/* Convert mode to the DT_* values that dir_emit uses. */
	ino_dtype = xfs_dir3_get_dtype(mp,
			xfs_mode_to_ftype(VFS_I(ip)->i_mode));
	अगर (ino_dtype != dtype)
		xchk_fblock_set_corrupt(sdc->sc, XFS_DATA_FORK, offset);
	xfs_irele(ip);
out:
	वापस error;
पूर्ण

/*
 * Scrub a single directory entry.
 *
 * We use the VFS directory iterator (i.e. सूची_पढ़ो) to call this
 * function क्रम every directory entry in a directory.  Once we're here,
 * we check the inode number to make sure it's sane, then we check that
 * we can look up this filename.  Finally, we check the ftype.
 */
STATIC पूर्णांक
xchk_dir_actor(
	काष्ठा dir_context	*dir_iter,
	स्थिर अक्षर		*name,
	पूर्णांक			namelen,
	loff_t			pos,
	u64			ino,
	अचिन्हित		type)
अणु
	काष्ठा xfs_mount	*mp;
	काष्ठा xfs_inode	*ip;
	काष्ठा xchk_dir_ctx	*sdc;
	काष्ठा xfs_name		xname;
	xfs_ino_t		lookup_ino;
	xfs_dablk_t		offset;
	bool			checked_ftype = false;
	पूर्णांक			error = 0;

	sdc = container_of(dir_iter, काष्ठा xchk_dir_ctx, dir_iter);
	ip = sdc->sc->ip;
	mp = ip->i_mount;
	offset = xfs_dir2_db_to_da(mp->m_dir_geo,
			xfs_dir2_dataptr_to_db(mp->m_dir_geo, pos));

	अगर (xchk_should_terminate(sdc->sc, &error))
		वापस error;

	/* Does this inode number make sense? */
	अगर (!xfs_verअगरy_dir_ino(mp, ino)) अणु
		xchk_fblock_set_corrupt(sdc->sc, XFS_DATA_FORK, offset);
		जाओ out;
	पूर्ण

	/* Does this name make sense? */
	अगर (!xfs_dir2_namecheck(name, namelen)) अणु
		xchk_fblock_set_corrupt(sdc->sc, XFS_DATA_FORK, offset);
		जाओ out;
	पूर्ण

	अगर (!म_भेदन(".", name, namelen)) अणु
		/* If this is "." then check that the inum matches the dir. */
		अगर (xfs_sb_version_hasftype(&mp->m_sb) && type != DT_सूची)
			xchk_fblock_set_corrupt(sdc->sc, XFS_DATA_FORK,
					offset);
		checked_ftype = true;
		अगर (ino != ip->i_ino)
			xchk_fblock_set_corrupt(sdc->sc, XFS_DATA_FORK,
					offset);
	पूर्ण अन्यथा अगर (!म_भेदन("..", name, namelen)) अणु
		/*
		 * If this is ".." in the root inode, check that the inum
		 * matches this dir.
		 */
		अगर (xfs_sb_version_hasftype(&mp->m_sb) && type != DT_सूची)
			xchk_fblock_set_corrupt(sdc->sc, XFS_DATA_FORK,
					offset);
		checked_ftype = true;
		अगर (ip->i_ino == mp->m_sb.sb_rootino && ino != ip->i_ino)
			xchk_fblock_set_corrupt(sdc->sc, XFS_DATA_FORK,
					offset);
	पूर्ण

	/* Verअगरy that we can look up this name by hash. */
	xname.name = name;
	xname.len = namelen;
	xname.type = XFS_सूची3_FT_UNKNOWN;

	error = xfs_dir_lookup(sdc->sc->tp, ip, &xname, &lookup_ino, शून्य);
	/* ENOENT means the hash lookup failed and the dir is corrupt */
	अगर (error == -ENOENT)
		error = -EFSCORRUPTED;
	अगर (!xchk_fblock_process_error(sdc->sc, XFS_DATA_FORK, offset,
			&error))
		जाओ out;
	अगर (lookup_ino != ino) अणु
		xchk_fblock_set_corrupt(sdc->sc, XFS_DATA_FORK, offset);
		जाओ out;
	पूर्ण

	/* Verअगरy the file type.  This function असलorbs error codes. */
	अगर (!checked_ftype) अणु
		error = xchk_dir_check_ftype(sdc, offset, lookup_ino, type);
		अगर (error)
			जाओ out;
	पूर्ण
out:
	/*
	 * A negative error code वापसed here is supposed to cause the
	 * dir_emit caller (xfs_सूची_पढ़ो) to पात the directory iteration
	 * and वापस zero to xchk_directory.
	 */
	अगर (error == 0 && sdc->sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस -EFSCORRUPTED;
	वापस error;
पूर्ण

/* Scrub a directory btree record. */
STATIC पूर्णांक
xchk_dir_rec(
	काष्ठा xchk_da_btree		*ds,
	पूर्णांक				level)
अणु
	काष्ठा xfs_da_state_blk		*blk = &ds->state->path.blk[level];
	काष्ठा xfs_mount		*mp = ds->state->mp;
	काष्ठा xfs_inode		*dp = ds->dargs.dp;
	काष्ठा xfs_da_geometry		*geo = mp->m_dir_geo;
	काष्ठा xfs_dir2_data_entry	*dent;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_dir2_leaf_entry	*ent;
	अचिन्हित पूर्णांक			end;
	अचिन्हित पूर्णांक			iter_off;
	xfs_ino_t			ino;
	xfs_dablk_t			rec_bno;
	xfs_dir2_db_t			db;
	xfs_dir2_data_aoff_t		off;
	xfs_dir2_dataptr_t		ptr;
	xfs_dahash_t			calc_hash;
	xfs_dahash_t			hash;
	काष्ठा xfs_dir3_icleaf_hdr	hdr;
	अचिन्हित पूर्णांक			tag;
	पूर्णांक				error;

	ASSERT(blk->magic == XFS_सूची2_LEAF1_MAGIC ||
	       blk->magic == XFS_सूची2_LEAFN_MAGIC);

	xfs_dir2_leaf_hdr_from_disk(mp, &hdr, blk->bp->b_addr);
	ent = hdr.ents + blk->index;

	/* Check the hash of the entry. */
	error = xchk_da_btree_hash(ds, level, &ent->hashval);
	अगर (error)
		जाओ out;

	/* Valid hash poपूर्णांकer? */
	ptr = be32_to_cpu(ent->address);
	अगर (ptr == 0)
		वापस 0;

	/* Find the directory entry's location. */
	db = xfs_dir2_dataptr_to_db(geo, ptr);
	off = xfs_dir2_dataptr_to_off(geo, ptr);
	rec_bno = xfs_dir2_db_to_da(geo, db);

	अगर (rec_bno >= geo->leafblk) अणु
		xchk_da_set_corrupt(ds, level);
		जाओ out;
	पूर्ण
	error = xfs_dir3_data_पढ़ो(ds->dargs.trans, dp, rec_bno,
			XFS_DABUF_MAP_HOLE_OK, &bp);
	अगर (!xchk_fblock_process_error(ds->sc, XFS_DATA_FORK, rec_bno,
			&error))
		जाओ out;
	अगर (!bp) अणु
		xchk_fblock_set_corrupt(ds->sc, XFS_DATA_FORK, rec_bno);
		जाओ out;
	पूर्ण
	xchk_buffer_recheck(ds->sc, bp);

	अगर (ds->sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out_rअन्यथा;

	dent = bp->b_addr + off;

	/* Make sure we got a real directory entry. */
	iter_off = geo->data_entry_offset;
	end = xfs_dir3_data_end_offset(geo, bp->b_addr);
	अगर (!end) अणु
		xchk_fblock_set_corrupt(ds->sc, XFS_DATA_FORK, rec_bno);
		जाओ out_rअन्यथा;
	पूर्ण
	क्रम (;;) अणु
		काष्ठा xfs_dir2_data_entry	*dep = bp->b_addr + iter_off;
		काष्ठा xfs_dir2_data_unused	*dup = bp->b_addr + iter_off;

		अगर (iter_off >= end) अणु
			xchk_fblock_set_corrupt(ds->sc, XFS_DATA_FORK, rec_bno);
			जाओ out_rअन्यथा;
		पूर्ण

		अगर (be16_to_cpu(dup->मुक्तtag) == XFS_सूची2_DATA_FREE_TAG) अणु
			iter_off += be16_to_cpu(dup->length);
			जारी;
		पूर्ण
		अगर (dep == dent)
			अवरोध;
		iter_off += xfs_dir2_data_entsize(mp, dep->namelen);
	पूर्ण

	/* Retrieve the entry, sanity check it, and compare hashes. */
	ino = be64_to_cpu(dent->inumber);
	hash = be32_to_cpu(ent->hashval);
	tag = be16_to_cpup(xfs_dir2_data_entry_tag_p(mp, dent));
	अगर (!xfs_verअगरy_dir_ino(mp, ino) || tag != off)
		xchk_fblock_set_corrupt(ds->sc, XFS_DATA_FORK, rec_bno);
	अगर (dent->namelen == 0) अणु
		xchk_fblock_set_corrupt(ds->sc, XFS_DATA_FORK, rec_bno);
		जाओ out_rअन्यथा;
	पूर्ण
	calc_hash = xfs_da_hashname(dent->name, dent->namelen);
	अगर (calc_hash != hash)
		xchk_fblock_set_corrupt(ds->sc, XFS_DATA_FORK, rec_bno);

out_rअन्यथा:
	xfs_trans_brअन्यथा(ds->dargs.trans, bp);
out:
	वापस error;
पूर्ण

/*
 * Is this unused entry either in the bestमुक्त or smaller than all of
 * them?  We've alपढ़ोy checked that the bestमुक्तs are sorted दीर्घest to
 * लघुest, and that there aren't any bogus entries.
 */
STATIC व्योम
xchk_directory_check_मुक्त_entry(
	काष्ठा xfs_scrub		*sc,
	xfs_dablk_t			lblk,
	काष्ठा xfs_dir2_data_मुक्त	*bf,
	काष्ठा xfs_dir2_data_unused	*dup)
अणु
	काष्ठा xfs_dir2_data_मुक्त	*dfp;
	अचिन्हित पूर्णांक			dup_length;

	dup_length = be16_to_cpu(dup->length);

	/* Unused entry is लघुer than any of the bestमुक्तs */
	अगर (dup_length < be16_to_cpu(bf[XFS_सूची2_DATA_FD_COUNT - 1].length))
		वापस;

	क्रम (dfp = &bf[XFS_सूची2_DATA_FD_COUNT - 1]; dfp >= bf; dfp--)
		अगर (dup_length == be16_to_cpu(dfp->length))
			वापस;

	/* Unused entry should be in the bestमुक्तs but wasn't found. */
	xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
पूर्ण

/* Check मुक्त space info in a directory data block. */
STATIC पूर्णांक
xchk_directory_data_bestमुक्त(
	काष्ठा xfs_scrub		*sc,
	xfs_dablk_t			lblk,
	bool				is_block)
अणु
	काष्ठा xfs_dir2_data_unused	*dup;
	काष्ठा xfs_dir2_data_मुक्त	*dfp;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_dir2_data_मुक्त	*bf;
	काष्ठा xfs_mount		*mp = sc->mp;
	u16				tag;
	अचिन्हित पूर्णांक			nr_bestमुक्तs = 0;
	अचिन्हित पूर्णांक			nr_मुक्तs = 0;
	अचिन्हित पूर्णांक			smallest_bestमुक्त;
	पूर्णांक				newlen;
	अचिन्हित पूर्णांक			offset;
	अचिन्हित पूर्णांक			end;
	पूर्णांक				error;

	अगर (is_block) अणु
		/* dir block क्रमmat */
		अगर (lblk != XFS_B_TO_FSBT(mp, XFS_सूची2_DATA_OFFSET))
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
		error = xfs_dir3_block_पढ़ो(sc->tp, sc->ip, &bp);
	पूर्ण अन्यथा अणु
		/* dir data क्रमmat */
		error = xfs_dir3_data_पढ़ो(sc->tp, sc->ip, lblk, 0, &bp);
	पूर्ण
	अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, lblk, &error))
		जाओ out;
	xchk_buffer_recheck(sc, bp);

	/* XXX: Check xfs_dir3_data_hdr.pad is zero once we start setting it. */

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out_buf;

	/* Do the bestमुक्तs correspond to actual मुक्त space? */
	bf = xfs_dir2_data_bestमुक्त_p(mp, bp->b_addr);
	smallest_bestमुक्त = अच_पूर्णांक_उच्च;
	क्रम (dfp = &bf[0]; dfp < &bf[XFS_सूची2_DATA_FD_COUNT]; dfp++) अणु
		offset = be16_to_cpu(dfp->offset);
		अगर (offset == 0)
			जारी;
		अगर (offset >= mp->m_dir_geo->blksize) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
			जाओ out_buf;
		पूर्ण
		dup = bp->b_addr + offset;
		tag = be16_to_cpu(*xfs_dir2_data_unused_tag_p(dup));

		/* bestमुक्त करोesn't match the entry it poपूर्णांकs at? */
		अगर (dup->मुक्तtag != cpu_to_be16(XFS_सूची2_DATA_FREE_TAG) ||
		    be16_to_cpu(dup->length) != be16_to_cpu(dfp->length) ||
		    tag != offset) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
			जाओ out_buf;
		पूर्ण

		/* bestमुक्त records should be ordered largest to smallest */
		अगर (smallest_bestमुक्त < be16_to_cpu(dfp->length)) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
			जाओ out_buf;
		पूर्ण

		smallest_bestमुक्त = be16_to_cpu(dfp->length);
		nr_bestमुक्तs++;
	पूर्ण

	/* Make sure the bestमुक्तs are actually the best मुक्त spaces. */
	offset = mp->m_dir_geo->data_entry_offset;
	end = xfs_dir3_data_end_offset(mp->m_dir_geo, bp->b_addr);

	/* Iterate the entries, stopping when we hit or go past the end. */
	जबतक (offset < end) अणु
		dup = bp->b_addr + offset;

		/* Skip real entries */
		अगर (dup->मुक्तtag != cpu_to_be16(XFS_सूची2_DATA_FREE_TAG)) अणु
			काष्ठा xfs_dir2_data_entry *dep = bp->b_addr + offset;

			newlen = xfs_dir2_data_entsize(mp, dep->namelen);
			अगर (newlen <= 0) अणु
				xchk_fblock_set_corrupt(sc, XFS_DATA_FORK,
						lblk);
				जाओ out_buf;
			पूर्ण
			offset += newlen;
			जारी;
		पूर्ण

		/* Spot check this मुक्त entry */
		tag = be16_to_cpu(*xfs_dir2_data_unused_tag_p(dup));
		अगर (tag != offset) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
			जाओ out_buf;
		पूर्ण

		/*
		 * Either this entry is a bestमुक्त or it's smaller than
		 * any of the bestमुक्तs.
		 */
		xchk_directory_check_मुक्त_entry(sc, lblk, bf, dup);
		अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
			जाओ out_buf;

		/* Move on. */
		newlen = be16_to_cpu(dup->length);
		अगर (newlen <= 0) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
			जाओ out_buf;
		पूर्ण
		offset += newlen;
		अगर (offset <= end)
			nr_मुक्तs++;
	पूर्ण

	/* We're required to fill all the space. */
	अगर (offset != end)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);

	/* Did we see at least as many मुक्त slots as there are bestमुक्तs? */
	अगर (nr_मुक्तs < nr_bestमुक्तs)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
out_buf:
	xfs_trans_brअन्यथा(sc->tp, bp);
out:
	वापस error;
पूर्ण

/*
 * Does the मुक्त space length in the मुक्त space index block ($len) match
 * the दीर्घest length in the directory data block's bestमुक्त array?
 * Assume that we've already checked that the data block's bestमुक्त
 * array is in order.
 */
STATIC व्योम
xchk_directory_check_मुक्तsp(
	काष्ठा xfs_scrub		*sc,
	xfs_dablk_t			lblk,
	काष्ठा xfs_buf			*dbp,
	अचिन्हित पूर्णांक			len)
अणु
	काष्ठा xfs_dir2_data_मुक्त	*dfp;

	dfp = xfs_dir2_data_bestमुक्त_p(sc->mp, dbp->b_addr);

	अगर (len != be16_to_cpu(dfp->length))
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);

	अगर (len > 0 && be16_to_cpu(dfp->offset) == 0)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
पूर्ण

/* Check मुक्त space info in a directory leaf1 block. */
STATIC पूर्णांक
xchk_directory_leaf1_bestमुक्त(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_da_args		*args,
	xfs_dablk_t			lblk)
अणु
	काष्ठा xfs_dir3_icleaf_hdr	leafhdr;
	काष्ठा xfs_dir2_leaf_tail	*ltp;
	काष्ठा xfs_dir2_leaf		*leaf;
	काष्ठा xfs_buf			*dbp;
	काष्ठा xfs_buf			*bp;
	काष्ठा xfs_da_geometry		*geo = sc->mp->m_dir_geo;
	__be16				*bestp;
	__u16				best;
	__u32				hash;
	__u32				lasthash = 0;
	__u32				bestcount;
	अचिन्हित पूर्णांक			stale = 0;
	पूर्णांक				i;
	पूर्णांक				error;

	/* Read the मुक्त space block. */
	error = xfs_dir3_leaf_पढ़ो(sc->tp, sc->ip, lblk, &bp);
	अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, lblk, &error))
		वापस error;
	xchk_buffer_recheck(sc, bp);

	leaf = bp->b_addr;
	xfs_dir2_leaf_hdr_from_disk(sc->ip->i_mount, &leafhdr, leaf);
	ltp = xfs_dir2_leaf_tail_p(geo, leaf);
	bestcount = be32_to_cpu(ltp->bestcount);
	bestp = xfs_dir2_leaf_bests_p(ltp);

	अगर (xfs_sb_version_hascrc(&sc->mp->m_sb)) अणु
		काष्ठा xfs_dir3_leaf_hdr	*hdr3 = bp->b_addr;

		अगर (hdr3->pad != cpu_to_be32(0))
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
	पूर्ण

	/*
	 * There should be as many bestमुक्त slots as there are dir data
	 * blocks that can fit under i_size.
	 */
	अगर (bestcount != xfs_dir2_byte_to_db(geo, sc->ip->i_disk_size)) अणु
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
		जाओ out;
	पूर्ण

	/* Is the leaf count even remotely sane? */
	अगर (leafhdr.count > geo->leaf_max_ents) अणु
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
		जाओ out;
	पूर्ण

	/* Leaves and bests करोn't overlap in leaf क्रमmat. */
	अगर ((अक्षर *)&leafhdr.ents[leafhdr.count] > (अक्षर *)bestp) अणु
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
		जाओ out;
	पूर्ण

	/* Check hash value order, count stale entries.  */
	क्रम (i = 0; i < leafhdr.count; i++) अणु
		hash = be32_to_cpu(leafhdr.ents[i].hashval);
		अगर (i > 0 && lasthash > hash)
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
		lasthash = hash;
		अगर (leafhdr.ents[i].address ==
		    cpu_to_be32(XFS_सूची2_शून्य_DATAPTR))
			stale++;
	पूर्ण
	अगर (leafhdr.stale != stale)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/* Check all the bestमुक्त entries. */
	क्रम (i = 0; i < bestcount; i++, bestp++) अणु
		best = be16_to_cpu(*bestp);
		error = xfs_dir3_data_पढ़ो(sc->tp, sc->ip,
				xfs_dir2_db_to_da(args->geo, i),
				XFS_DABUF_MAP_HOLE_OK,
				&dbp);
		अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, lblk,
				&error))
			अवरोध;

		अगर (!dbp) अणु
			अगर (best != शून्यDATAOFF) अणु
				xchk_fblock_set_corrupt(sc, XFS_DATA_FORK,
						lblk);
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण

		अगर (best == शून्यDATAOFF)
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
		अन्यथा
			xchk_directory_check_मुक्तsp(sc, lblk, dbp, best);
		xfs_trans_brअन्यथा(sc->tp, dbp);
		अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
			अवरोध;
	पूर्ण
out:
	xfs_trans_brअन्यथा(sc->tp, bp);
	वापस error;
पूर्ण

/* Check मुक्त space info in a directory मुक्तspace block. */
STATIC पूर्णांक
xchk_directory_मुक्त_bestमुक्त(
	काष्ठा xfs_scrub		*sc,
	काष्ठा xfs_da_args		*args,
	xfs_dablk_t			lblk)
अणु
	काष्ठा xfs_dir3_icमुक्त_hdr	मुक्तhdr;
	काष्ठा xfs_buf			*dbp;
	काष्ठा xfs_buf			*bp;
	__u16				best;
	अचिन्हित पूर्णांक			stale = 0;
	पूर्णांक				i;
	पूर्णांक				error;

	/* Read the मुक्त space block */
	error = xfs_dir2_मुक्त_पढ़ो(sc->tp, sc->ip, lblk, &bp);
	अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, lblk, &error))
		वापस error;
	xchk_buffer_recheck(sc, bp);

	अगर (xfs_sb_version_hascrc(&sc->mp->m_sb)) अणु
		काष्ठा xfs_dir3_मुक्त_hdr	*hdr3 = bp->b_addr;

		अगर (hdr3->pad != cpu_to_be32(0))
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
	पूर्ण

	/* Check all the entries. */
	xfs_dir2_मुक्त_hdr_from_disk(sc->ip->i_mount, &मुक्तhdr, bp->b_addr);
	क्रम (i = 0; i < मुक्तhdr.nvalid; i++) अणु
		best = be16_to_cpu(मुक्तhdr.bests[i]);
		अगर (best == शून्यDATAOFF) अणु
			stale++;
			जारी;
		पूर्ण
		error = xfs_dir3_data_पढ़ो(sc->tp, sc->ip,
				(मुक्तhdr.firstdb + i) * args->geo->fsbcount,
				0, &dbp);
		अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, lblk,
				&error))
			जाओ out;
		xchk_directory_check_मुक्तsp(sc, lblk, dbp, best);
		xfs_trans_brअन्यथा(sc->tp, dbp);
	पूर्ण

	अगर (मुक्तhdr.nused + stale != मुक्तhdr.nvalid)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
out:
	xfs_trans_brअन्यथा(sc->tp, bp);
	वापस error;
पूर्ण

/* Check मुक्त space inक्रमmation in directories. */
STATIC पूर्णांक
xchk_directory_blocks(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_bmbt_irec	got;
	काष्ठा xfs_da_args	args;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(sc->ip, XFS_DATA_FORK);
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_fileoff_t		leaf_lblk;
	xfs_fileoff_t		मुक्त_lblk;
	xfs_fileoff_t		lblk;
	काष्ठा xfs_iext_cursor	icur;
	xfs_dablk_t		dabno;
	bool			found;
	पूर्णांक			is_block = 0;
	पूर्णांक			error;

	/* Ignore local क्रमmat directories. */
	अगर (अगरp->अगर_क्रमmat != XFS_DINODE_FMT_EXTENTS &&
	    अगरp->अगर_क्रमmat != XFS_DINODE_FMT_BTREE)
		वापस 0;

	lblk = XFS_B_TO_FSB(mp, XFS_सूची2_DATA_OFFSET);
	leaf_lblk = XFS_B_TO_FSB(mp, XFS_सूची2_LEAF_OFFSET);
	मुक्त_lblk = XFS_B_TO_FSB(mp, XFS_सूची2_FREE_OFFSET);

	/* Is this a block dir? */
	args.dp = sc->ip;
	args.geo = mp->m_dir_geo;
	args.trans = sc->tp;
	error = xfs_dir2_isblock(&args, &is_block);
	अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, lblk, &error))
		जाओ out;

	/* Iterate all the data extents in the directory... */
	found = xfs_iext_lookup_extent(sc->ip, अगरp, lblk, &icur, &got);
	जबतक (found && !(sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)) अणु
		/* No more data blocks... */
		अगर (got.br_startoff >= leaf_lblk)
			अवरोध;

		/*
		 * Check each data block's bestमुक्त data.
		 *
		 * Iterate all the fsbcount-aligned block offsets in
		 * this directory.  The directory block पढ़ोing code is
		 * smart enough to करो its own bmap lookups to handle
		 * discontiguous directory blocks.  When we're करोne
		 * with the extent record, re-query the bmap at the
		 * next fsbcount-aligned offset to aव्योम redundant
		 * block checks.
		 */
		क्रम (lblk = roundup((xfs_dablk_t)got.br_startoff,
				args.geo->fsbcount);
		     lblk < got.br_startoff + got.br_blockcount;
		     lblk += args.geo->fsbcount) अणु
			error = xchk_directory_data_bestमुक्त(sc, lblk,
					is_block);
			अगर (error)
				जाओ out;
		पूर्ण
		dabno = got.br_startoff + got.br_blockcount;
		lblk = roundup(dabno, args.geo->fsbcount);
		found = xfs_iext_lookup_extent(sc->ip, अगरp, lblk, &icur, &got);
	पूर्ण

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/* Look क्रम a leaf1 block, which has मुक्त info. */
	अगर (xfs_iext_lookup_extent(sc->ip, अगरp, leaf_lblk, &icur, &got) &&
	    got.br_startoff == leaf_lblk &&
	    got.br_blockcount == args.geo->fsbcount &&
	    !xfs_iext_next_extent(अगरp, &icur, &got)) अणु
		अगर (is_block) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
			जाओ out;
		पूर्ण
		error = xchk_directory_leaf1_bestमुक्त(sc, &args,
				leaf_lblk);
		अगर (error)
			जाओ out;
	पूर्ण

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/* Scan क्रम मुक्त blocks */
	lblk = मुक्त_lblk;
	found = xfs_iext_lookup_extent(sc->ip, अगरp, lblk, &icur, &got);
	जबतक (found && !(sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)) अणु
		/*
		 * Dirs can't have blocks mapped above 2^32.
		 * Single-block dirs shouldn't even be here.
		 */
		lblk = got.br_startoff;
		अगर (lblk & ~0xFFFFFFFFULL) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
			जाओ out;
		पूर्ण
		अगर (is_block) अणु
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, lblk);
			जाओ out;
		पूर्ण

		/*
		 * Check each dir मुक्त block's bestमुक्त data.
		 *
		 * Iterate all the fsbcount-aligned block offsets in
		 * this directory.  The directory block पढ़ोing code is
		 * smart enough to करो its own bmap lookups to handle
		 * discontiguous directory blocks.  When we're करोne
		 * with the extent record, re-query the bmap at the
		 * next fsbcount-aligned offset to aव्योम redundant
		 * block checks.
		 */
		क्रम (lblk = roundup((xfs_dablk_t)got.br_startoff,
				args.geo->fsbcount);
		     lblk < got.br_startoff + got.br_blockcount;
		     lblk += args.geo->fsbcount) अणु
			error = xchk_directory_मुक्त_bestमुक्त(sc, &args,
					lblk);
			अगर (error)
				जाओ out;
		पूर्ण
		dabno = got.br_startoff + got.br_blockcount;
		lblk = roundup(dabno, args.geo->fsbcount);
		found = xfs_iext_lookup_extent(sc->ip, अगरp, lblk, &icur, &got);
	पूर्ण
out:
	वापस error;
पूर्ण

/* Scrub a whole directory. */
पूर्णांक
xchk_directory(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xchk_dir_ctx	sdc = अणु
		.dir_iter.actor = xchk_dir_actor,
		.dir_iter.pos = 0,
		.sc = sc,
	पूर्ण;
	माप_प्रकार			bufsize;
	loff_t			oldpos;
	पूर्णांक			error = 0;

	अगर (!S_ISसूची(VFS_I(sc->ip)->i_mode))
		वापस -ENOENT;

	/* Plausible size? */
	अगर (sc->ip->i_disk_size < xfs_dir2_sf_hdr_size(0)) अणु
		xchk_ino_set_corrupt(sc, sc->ip->i_ino);
		जाओ out;
	पूर्ण

	/* Check directory tree काष्ठाure */
	error = xchk_da_btree(sc, XFS_DATA_FORK, xchk_dir_rec, शून्य);
	अगर (error)
		वापस error;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस error;

	/* Check the मुक्तspace. */
	error = xchk_directory_blocks(sc);
	अगर (error)
		वापस error;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		वापस error;

	/*
	 * Check that every dirent we see can also be looked up by hash.
	 * Userspace usually asks क्रम a 32k buffer, so we will too.
	 */
	bufsize = (माप_प्रकार)min_t(loff_t, XFS_READसूची_बफ_मानE,
			sc->ip->i_disk_size);

	/*
	 * Look up every name in this directory by hash.
	 *
	 * Use the xfs_सूची_पढ़ो function to call xchk_dir_actor on
	 * every directory entry in this directory.  In _actor, we check
	 * the name, inode number, and ftype (अगर applicable) of the
	 * entry.  xfs_सूची_पढ़ो uses the VFS filldir functions to provide
	 * iteration context.
	 *
	 * The VFS grअसल a पढ़ो or ग_लिखो lock via i_rwsem beक्रमe it पढ़ोs
	 * or ग_लिखोs to a directory.  If we've gotten this far we've
	 * alपढ़ोy obtained IOLOCK_EXCL, which (since 4.10) is the same as
	 * getting a ग_लिखो lock on i_rwsem.  Thereक्रमe, it is safe क्रम us
	 * to drop the ILOCK here in order to reuse the _सूची_पढ़ो and
	 * _dir_lookup routines, which करो their own ILOCK locking.
	 */
	oldpos = 0;
	sc->ilock_flags &= ~XFS_ILOCK_EXCL;
	xfs_iunlock(sc->ip, XFS_ILOCK_EXCL);
	जबतक (true) अणु
		error = xfs_सूची_पढ़ो(sc->tp, sc->ip, &sdc.dir_iter, bufsize);
		अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, 0,
				&error))
			जाओ out;
		अगर (oldpos == sdc.dir_iter.pos)
			अवरोध;
		oldpos = sdc.dir_iter.pos;
	पूर्ण

out:
	वापस error;
पूर्ण
