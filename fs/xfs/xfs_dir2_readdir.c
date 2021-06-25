<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2005 Silicon Graphics, Inc.
 * Copyright (c) 2013 Red Hat, Inc.
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
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_trace.h"
#समावेश "xfs_bmap.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_error.h"

/*
 * Directory file type support functions
 */
अटल अचिन्हित अक्षर xfs_dir3_filetype_table[] = अणु
	DT_UNKNOWN, DT_REG, DT_सूची, DT_CHR, DT_BLK,
	DT_FIFO, DT_SOCK, DT_LNK, DT_WHT,
पूर्ण;

अचिन्हित अक्षर
xfs_dir3_get_dtype(
	काष्ठा xfs_mount	*mp,
	uपूर्णांक8_t			filetype)
अणु
	अगर (!xfs_sb_version_hasftype(&mp->m_sb))
		वापस DT_UNKNOWN;

	अगर (filetype >= XFS_सूची3_FT_MAX)
		वापस DT_UNKNOWN;

	वापस xfs_dir3_filetype_table[filetype];
पूर्ण

STATIC पूर्णांक
xfs_dir2_sf_getdents(
	काष्ठा xfs_da_args	*args,
	काष्ठा dir_context	*ctx)
अणु
	पूर्णांक			i;		/* लघुक्रमm entry number */
	काष्ठा xfs_inode	*dp = args->dp;	/* incore directory inode */
	काष्ठा xfs_mount	*mp = dp->i_mount;
	xfs_dir2_dataptr_t	off;		/* current entry's offset */
	xfs_dir2_sf_entry_t	*sfep;		/* लघुक्रमm directory entry */
	xfs_dir2_sf_hdr_t	*sfp;		/* लघुक्रमm काष्ठाure */
	xfs_dir2_dataptr_t	करोt_offset;
	xfs_dir2_dataptr_t	करोtकरोt_offset;
	xfs_ino_t		ino;
	काष्ठा xfs_da_geometry	*geo = args->geo;

	ASSERT(dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	ASSERT(dp->i_df.अगर_bytes == dp->i_disk_size);
	ASSERT(dp->i_df.अगर_u1.अगर_data != शून्य);

	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;

	/*
	 * If the block number in the offset is out of range, we're करोne.
	 */
	अगर (xfs_dir2_dataptr_to_db(geo, ctx->pos) > geo->datablk)
		वापस 0;

	/*
	 * Precalculate offsets क्रम "." and ".." as we will always need them.
	 * This relies on the fact that directories always start with the
	 * entries क्रम "." and "..".
	 */
	करोt_offset = xfs_dir2_db_off_to_dataptr(geo, geo->datablk,
			geo->data_entry_offset);
	करोtकरोt_offset = xfs_dir2_db_off_to_dataptr(geo, geo->datablk,
			geo->data_entry_offset +
			xfs_dir2_data_entsize(mp, माप(".") - 1));

	/*
	 * Put . entry unless we're starting past it.
	 */
	अगर (ctx->pos <= करोt_offset) अणु
		ctx->pos = करोt_offset & 0x7fffffff;
		अगर (!dir_emit(ctx, ".", 1, dp->i_ino, DT_सूची))
			वापस 0;
	पूर्ण

	/*
	 * Put .. entry unless we're starting past it.
	 */
	अगर (ctx->pos <= करोtकरोt_offset) अणु
		ino = xfs_dir2_sf_get_parent_ino(sfp);
		ctx->pos = करोtकरोt_offset & 0x7fffffff;
		अगर (!dir_emit(ctx, "..", 2, ino, DT_सूची))
			वापस 0;
	पूर्ण

	/*
	 * Loop जबतक there are more entries and put'ing works.
	 */
	sfep = xfs_dir2_sf_firstentry(sfp);
	क्रम (i = 0; i < sfp->count; i++) अणु
		uपूर्णांक8_t filetype;

		off = xfs_dir2_db_off_to_dataptr(geo, geo->datablk,
				xfs_dir2_sf_get_offset(sfep));

		अगर (ctx->pos > off) अणु
			sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep);
			जारी;
		पूर्ण

		ino = xfs_dir2_sf_get_ino(mp, sfp, sfep);
		filetype = xfs_dir2_sf_get_ftype(mp, sfep);
		ctx->pos = off & 0x7fffffff;
		अगर (XFS_IS_CORRUPT(dp->i_mount,
				   !xfs_dir2_namecheck(sfep->name,
						       sfep->namelen)))
			वापस -EFSCORRUPTED;
		अगर (!dir_emit(ctx, (अक्षर *)sfep->name, sfep->namelen, ino,
			    xfs_dir3_get_dtype(mp, filetype)))
			वापस 0;
		sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep);
	पूर्ण

	ctx->pos = xfs_dir2_db_off_to_dataptr(geo, geo->datablk + 1, 0) &
								0x7fffffff;
	वापस 0;
पूर्ण

/*
 * Readdir क्रम block directories.
 */
STATIC पूर्णांक
xfs_dir2_block_getdents(
	काष्ठा xfs_da_args	*args,
	काष्ठा dir_context	*ctx)
अणु
	काष्ठा xfs_inode	*dp = args->dp;	/* incore directory inode */
	काष्ठा xfs_buf		*bp;		/* buffer क्रम block */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			wantoff;	/* starting block offset */
	xfs_off_t		cook;
	काष्ठा xfs_da_geometry	*geo = args->geo;
	पूर्णांक			lock_mode;
	अचिन्हित पूर्णांक		offset, next_offset;
	अचिन्हित पूर्णांक		end;

	/*
	 * If the block number in the offset is out of range, we're करोne.
	 */
	अगर (xfs_dir2_dataptr_to_db(geo, ctx->pos) > geo->datablk)
		वापस 0;

	lock_mode = xfs_ilock_data_map_shared(dp);
	error = xfs_dir3_block_पढ़ो(args->trans, dp, &bp);
	xfs_iunlock(dp, lock_mode);
	अगर (error)
		वापस error;

	/*
	 * Extract the byte offset we start at from the seek poपूर्णांकer.
	 * We'll skip entries beक्रमe this.
	 */
	wantoff = xfs_dir2_dataptr_to_off(geo, ctx->pos);
	xfs_dir3_data_check(dp, bp);

	/*
	 * Loop over the data portion of the block.
	 * Each object is a real entry (dep) or an unused one (dup).
	 */
	end = xfs_dir3_data_end_offset(geo, bp->b_addr);
	क्रम (offset = geo->data_entry_offset;
	     offset < end;
	     offset = next_offset) अणु
		काष्ठा xfs_dir2_data_unused	*dup = bp->b_addr + offset;
		काष्ठा xfs_dir2_data_entry	*dep = bp->b_addr + offset;
		uपूर्णांक8_t filetype;

		/*
		 * Unused, skip it.
		 */
		अगर (be16_to_cpu(dup->मुक्तtag) == XFS_सूची2_DATA_FREE_TAG) अणु
			next_offset = offset + be16_to_cpu(dup->length);
			जारी;
		पूर्ण

		/*
		 * Bump poपूर्णांकer क्रम the next iteration.
		 */
		next_offset = offset +
			xfs_dir2_data_entsize(dp->i_mount, dep->namelen);

		/*
		 * The entry is beक्रमe the desired starting poपूर्णांक, skip it.
		 */
		अगर (offset < wantoff)
			जारी;

		cook = xfs_dir2_db_off_to_dataptr(geo, geo->datablk, offset);

		ctx->pos = cook & 0x7fffffff;
		filetype = xfs_dir2_data_get_ftype(dp->i_mount, dep);
		/*
		 * If it didn't fit, set the final offset to here & वापस.
		 */
		अगर (XFS_IS_CORRUPT(dp->i_mount,
				   !xfs_dir2_namecheck(dep->name,
						       dep->namelen))) अणु
			error = -EFSCORRUPTED;
			जाओ out_rele;
		पूर्ण
		अगर (!dir_emit(ctx, (अक्षर *)dep->name, dep->namelen,
			    be64_to_cpu(dep->inumber),
			    xfs_dir3_get_dtype(dp->i_mount, filetype)))
			जाओ out_rele;
	पूर्ण

	/*
	 * Reached the end of the block.
	 * Set the offset to a non-existent block 1 and वापस.
	 */
	ctx->pos = xfs_dir2_db_off_to_dataptr(geo, geo->datablk + 1, 0) &
								0x7fffffff;
out_rele:
	xfs_trans_brअन्यथा(args->trans, bp);
	वापस error;
पूर्ण

/*
 * Read a directory block and initiate पढ़ोahead क्रम blocks beyond that.
 * We मुख्यtain a sliding पढ़ोahead winकरोw of the reमुख्यing space in the
 * buffer rounded up to the nearest block.
 */
STATIC पूर्णांक
xfs_dir2_leaf_पढ़ोbuf(
	काष्ठा xfs_da_args	*args,
	माप_प्रकार			bufsize,
	xfs_dir2_off_t		*cur_off,
	xfs_dablk_t		*ra_blk,
	काष्ठा xfs_buf		**bpp)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_buf		*bp = शून्य;
	काष्ठा xfs_da_geometry	*geo = args->geo;
	काष्ठा xfs_अगरork	*अगरp = XFS_IFORK_PTR(dp, XFS_DATA_FORK);
	काष्ठा xfs_bmbt_irec	map;
	काष्ठा blk_plug		plug;
	xfs_dir2_off_t		new_off;
	xfs_dablk_t		next_ra;
	xfs_dablk_t		map_off;
	xfs_dablk_t		last_da;
	काष्ठा xfs_iext_cursor	icur;
	पूर्णांक			ra_want;
	पूर्णांक			error = 0;

	error = xfs_iपढ़ो_extents(args->trans, dp, XFS_DATA_FORK);
	अगर (error)
		जाओ out;

	/*
	 * Look क्रम mapped directory blocks at or above the current offset.
	 * Truncate करोwn to the nearest directory block to start the scanning
	 * operation.
	 */
	last_da = xfs_dir2_byte_to_da(geo, XFS_सूची2_LEAF_OFFSET);
	map_off = xfs_dir2_db_to_da(geo, xfs_dir2_byte_to_db(geo, *cur_off));
	अगर (!xfs_iext_lookup_extent(dp, अगरp, map_off, &icur, &map))
		जाओ out;
	अगर (map.br_startoff >= last_da)
		जाओ out;
	xfs_trim_extent(&map, map_off, last_da - map_off);

	/* Read the directory block of that first mapping. */
	new_off = xfs_dir2_da_to_byte(geo, map.br_startoff);
	अगर (new_off > *cur_off)
		*cur_off = new_off;
	error = xfs_dir3_data_पढ़ो(args->trans, dp, map.br_startoff, 0, &bp);
	अगर (error)
		जाओ out;

	/*
	 * Start पढ़ोahead क्रम the next bufsize's worth of dir data blocks.
	 * We may have alपढ़ोy issued पढ़ोahead क्रम some of that range;
	 * ra_blk tracks the last block we tried to पढ़ो(ahead).
	 */
	ra_want = howmany(bufsize + geo->blksize, (1 << geo->fsblog));
	अगर (*ra_blk >= last_da)
		जाओ out;
	अन्यथा अगर (*ra_blk == 0)
		*ra_blk = map.br_startoff;
	next_ra = map.br_startoff + geo->fsbcount;
	अगर (next_ra >= last_da)
		जाओ out_no_ra;
	अगर (map.br_blockcount < geo->fsbcount &&
	    !xfs_iext_next_extent(अगरp, &icur, &map))
		जाओ out_no_ra;
	अगर (map.br_startoff >= last_da)
		जाओ out_no_ra;
	xfs_trim_extent(&map, next_ra, last_da - next_ra);

	/* Start ra क्रम each dir (not fs) block that has a mapping. */
	blk_start_plug(&plug);
	जबतक (ra_want > 0) अणु
		next_ra = roundup((xfs_dablk_t)map.br_startoff, geo->fsbcount);
		जबतक (ra_want > 0 &&
		       next_ra < map.br_startoff + map.br_blockcount) अणु
			अगर (next_ra >= last_da) अणु
				*ra_blk = last_da;
				अवरोध;
			पूर्ण
			अगर (next_ra > *ra_blk) अणु
				xfs_dir3_data_पढ़ोahead(dp, next_ra,
							XFS_DABUF_MAP_HOLE_OK);
				*ra_blk = next_ra;
			पूर्ण
			ra_want -= geo->fsbcount;
			next_ra += geo->fsbcount;
		पूर्ण
		अगर (!xfs_iext_next_extent(अगरp, &icur, &map)) अणु
			*ra_blk = last_da;
			अवरोध;
		पूर्ण
	पूर्ण
	blk_finish_plug(&plug);

out:
	*bpp = bp;
	वापस error;
out_no_ra:
	*ra_blk = last_da;
	जाओ out;
पूर्ण

/*
 * Getdents (सूची_पढ़ो) क्रम leaf and node directories.
 * This पढ़ोs the data blocks only, so is the same क्रम both क्रमms.
 */
STATIC पूर्णांक
xfs_dir2_leaf_getdents(
	काष्ठा xfs_da_args	*args,
	काष्ठा dir_context	*ctx,
	माप_प्रकार			bufsize)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	काष्ठा xfs_buf		*bp = शून्य;	/* data block buffer */
	xfs_dir2_data_entry_t	*dep;		/* data entry */
	xfs_dir2_data_unused_t	*dup;		/* unused entry */
	काष्ठा xfs_da_geometry	*geo = args->geo;
	xfs_dablk_t		rablk = 0;	/* current पढ़ोahead block */
	xfs_dir2_off_t		curoff;		/* current overall offset */
	पूर्णांक			length;		/* temporary length value */
	पूर्णांक			byteoff;	/* offset in current block */
	पूर्णांक			lock_mode;
	अचिन्हित पूर्णांक		offset = 0;
	पूर्णांक			error = 0;	/* error वापस value */

	/*
	 * If the offset is at or past the largest allowed value,
	 * give up right away.
	 */
	अगर (ctx->pos >= XFS_सूची2_MAX_DATAPTR)
		वापस 0;

	/*
	 * Inside the loop we keep the मुख्य offset value as a byte offset
	 * in the directory file.
	 */
	curoff = xfs_dir2_dataptr_to_byte(ctx->pos);

	/*
	 * Loop over directory entries until we reach the end offset.
	 * Get more blocks and पढ़ोahead as necessary.
	 */
	जबतक (curoff < XFS_सूची2_LEAF_OFFSET) अणु
		uपूर्णांक8_t filetype;

		/*
		 * If we have no buffer, or we're off the end of the
		 * current buffer, need to get another one.
		 */
		अगर (!bp || offset >= geo->blksize) अणु
			अगर (bp) अणु
				xfs_trans_brअन्यथा(args->trans, bp);
				bp = शून्य;
			पूर्ण

			lock_mode = xfs_ilock_data_map_shared(dp);
			error = xfs_dir2_leaf_पढ़ोbuf(args, bufsize, &curoff,
					&rablk, &bp);
			xfs_iunlock(dp, lock_mode);
			अगर (error || !bp)
				अवरोध;

			xfs_dir3_data_check(dp, bp);
			/*
			 * Find our position in the block.
			 */
			offset = geo->data_entry_offset;
			byteoff = xfs_dir2_byte_to_off(geo, curoff);
			/*
			 * Skip past the header.
			 */
			अगर (byteoff == 0)
				curoff += geo->data_entry_offset;
			/*
			 * Skip past entries until we reach our offset.
			 */
			अन्यथा अणु
				जबतक (offset < byteoff) अणु
					dup = bp->b_addr + offset;

					अगर (be16_to_cpu(dup->मुक्तtag)
						  == XFS_सूची2_DATA_FREE_TAG) अणु

						length = be16_to_cpu(dup->length);
						offset += length;
						जारी;
					पूर्ण
					dep = bp->b_addr + offset;
					length = xfs_dir2_data_entsize(mp,
							dep->namelen);
					offset += length;
				पूर्ण
				/*
				 * Now set our real offset.
				 */
				curoff =
					xfs_dir2_db_off_to_byte(geo,
					    xfs_dir2_byte_to_db(geo, curoff),
					    offset);
				अगर (offset >= geo->blksize)
					जारी;
			पूर्ण
		पूर्ण

		/*
		 * We have a poपूर्णांकer to an entry.  Is it a live one?
		 */
		dup = bp->b_addr + offset;

		/*
		 * No, it's unused, skip over it.
		 */
		अगर (be16_to_cpu(dup->मुक्तtag) == XFS_सूची2_DATA_FREE_TAG) अणु
			length = be16_to_cpu(dup->length);
			offset += length;
			curoff += length;
			जारी;
		पूर्ण

		dep = bp->b_addr + offset;
		length = xfs_dir2_data_entsize(mp, dep->namelen);
		filetype = xfs_dir2_data_get_ftype(mp, dep);

		ctx->pos = xfs_dir2_byte_to_dataptr(curoff) & 0x7fffffff;
		अगर (XFS_IS_CORRUPT(dp->i_mount,
				   !xfs_dir2_namecheck(dep->name,
						       dep->namelen))) अणु
			error = -EFSCORRUPTED;
			अवरोध;
		पूर्ण
		अगर (!dir_emit(ctx, (अक्षर *)dep->name, dep->namelen,
			    be64_to_cpu(dep->inumber),
			    xfs_dir3_get_dtype(dp->i_mount, filetype)))
			अवरोध;

		/*
		 * Advance to next entry in the block.
		 */
		offset += length;
		curoff += length;
		/* bufsize may have just been a guess; करोn't go negative */
		bufsize = bufsize > length ? bufsize - length : 0;
	पूर्ण

	/*
	 * All करोne.  Set output offset value to current offset.
	 */
	अगर (curoff > xfs_dir2_dataptr_to_byte(XFS_सूची2_MAX_DATAPTR))
		ctx->pos = XFS_सूची2_MAX_DATAPTR & 0x7fffffff;
	अन्यथा
		ctx->pos = xfs_dir2_byte_to_dataptr(curoff) & 0x7fffffff;
	अगर (bp)
		xfs_trans_brअन्यथा(args->trans, bp);
	वापस error;
पूर्ण

/*
 * Read a directory.
 *
 * If supplied, the transaction collects locked dir buffers to aव्योम
 * nested buffer deadlocks.  This function करोes not dirty the
 * transaction.  The caller should ensure that the inode is locked
 * beक्रमe calling this function.
 */
पूर्णांक
xfs_सूची_पढ़ो(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	काष्ठा dir_context	*ctx,
	माप_प्रकार			bufsize)
अणु
	काष्ठा xfs_da_args	args = अणु शून्य पूर्ण;
	पूर्णांक			rval;
	पूर्णांक			v;

	trace_xfs_सूची_पढ़ो(dp);

	अगर (XFS_FORCED_SHUTDOWN(dp->i_mount))
		वापस -EIO;

	ASSERT(S_ISसूची(VFS_I(dp)->i_mode));
	XFS_STATS_INC(dp->i_mount, xs_dir_getdents);

	args.dp = dp;
	args.geo = dp->i_mount->m_dir_geo;
	args.trans = tp;

	अगर (dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL)
		rval = xfs_dir2_sf_getdents(&args, ctx);
	अन्यथा अगर ((rval = xfs_dir2_isblock(&args, &v)))
		;
	अन्यथा अगर (v)
		rval = xfs_dir2_block_getdents(&args, ctx);
	अन्यथा
		rval = xfs_dir2_leaf_getdents(&args, ctx, bufsize);

	वापस rval;
पूर्ण
