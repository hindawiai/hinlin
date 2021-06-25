<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
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
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_trace.h"

/*
 * Prototypes क्रम पूर्णांकernal functions.
 */
अटल व्योम xfs_dir2_sf_addname_easy(xfs_da_args_t *args,
				     xfs_dir2_sf_entry_t *sfep,
				     xfs_dir2_data_aoff_t offset,
				     पूर्णांक new_isize);
अटल व्योम xfs_dir2_sf_addname_hard(xfs_da_args_t *args, पूर्णांक objchange,
				     पूर्णांक new_isize);
अटल पूर्णांक xfs_dir2_sf_addname_pick(xfs_da_args_t *args, पूर्णांक objchange,
				    xfs_dir2_sf_entry_t **sfepp,
				    xfs_dir2_data_aoff_t *offsetp);
#अगर_घोषित DEBUG
अटल व्योम xfs_dir2_sf_check(xfs_da_args_t *args);
#अन्यथा
#घोषणा	xfs_dir2_sf_check(args)
#पूर्ण_अगर /* DEBUG */

अटल व्योम xfs_dir2_sf_toino4(xfs_da_args_t *args);
अटल व्योम xfs_dir2_sf_toino8(xfs_da_args_t *args);

पूर्णांक
xfs_dir2_sf_entsize(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dir2_sf_hdr	*hdr,
	पूर्णांक			len)
अणु
	पूर्णांक			count = len;

	count += माप(काष्ठा xfs_dir2_sf_entry);	/* namelen + offset */
	count += hdr->i8count ? XFS_INO64_SIZE : XFS_INO32_SIZE; /* ino # */

	अगर (xfs_sb_version_hasftype(&mp->m_sb))
		count += माप(uपूर्णांक8_t);
	वापस count;
पूर्ण

काष्ठा xfs_dir2_sf_entry *
xfs_dir2_sf_nextentry(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dir2_sf_hdr	*hdr,
	काष्ठा xfs_dir2_sf_entry *sfep)
अणु
	वापस (व्योम *)sfep + xfs_dir2_sf_entsize(mp, hdr, sfep->namelen);
पूर्ण

/*
 * In लघु-क्रमm directory entries the inode numbers are stored at variable
 * offset behind the entry name. If the entry stores a filetype value, then it
 * sits between the name and the inode number.  The actual inode numbers can
 * come in two क्रमmats as well, either 4 bytes or 8 bytes wide.
 */
xfs_ino_t
xfs_dir2_sf_get_ino(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_sf_hdr		*hdr,
	काष्ठा xfs_dir2_sf_entry	*sfep)
अणु
	uपूर्णांक8_t				*from = sfep->name + sfep->namelen;

	अगर (xfs_sb_version_hasftype(&mp->m_sb))
		from++;

	अगर (!hdr->i8count)
		वापस get_unaligned_be32(from);
	वापस get_unaligned_be64(from) & XFS_MAXINUMBER;
पूर्ण

व्योम
xfs_dir2_sf_put_ino(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_sf_hdr		*hdr,
	काष्ठा xfs_dir2_sf_entry	*sfep,
	xfs_ino_t			ino)
अणु
	uपूर्णांक8_t				*to = sfep->name + sfep->namelen;

	ASSERT(ino <= XFS_MAXINUMBER);

	अगर (xfs_sb_version_hasftype(&mp->m_sb))
		to++;

	अगर (hdr->i8count)
		put_unaligned_be64(ino, to);
	अन्यथा
		put_unaligned_be32(ino, to);
पूर्ण

xfs_ino_t
xfs_dir2_sf_get_parent_ino(
	काष्ठा xfs_dir2_sf_hdr	*hdr)
अणु
	अगर (!hdr->i8count)
		वापस get_unaligned_be32(hdr->parent);
	वापस get_unaligned_be64(hdr->parent) & XFS_MAXINUMBER;
पूर्ण

व्योम
xfs_dir2_sf_put_parent_ino(
	काष्ठा xfs_dir2_sf_hdr		*hdr,
	xfs_ino_t			ino)
अणु
	ASSERT(ino <= XFS_MAXINUMBER);

	अगर (hdr->i8count)
		put_unaligned_be64(ino, hdr->parent);
	अन्यथा
		put_unaligned_be32(ino, hdr->parent);
पूर्ण

/*
 * The file type field is stored at the end of the name क्रम filetype enabled
 * लघुक्रमm directories, or not at all otherwise.
 */
uपूर्णांक8_t
xfs_dir2_sf_get_ftype(
	काष्ठा xfs_mount		*mp,
	काष्ठा xfs_dir2_sf_entry	*sfep)
अणु
	अगर (xfs_sb_version_hasftype(&mp->m_sb)) अणु
		uपूर्णांक8_t			ftype = sfep->name[sfep->namelen];

		अगर (ftype < XFS_सूची3_FT_MAX)
			वापस ftype;
	पूर्ण

	वापस XFS_सूची3_FT_UNKNOWN;
पूर्ण

व्योम
xfs_dir2_sf_put_ftype(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_dir2_sf_entry *sfep,
	uपूर्णांक8_t			ftype)
अणु
	ASSERT(ftype < XFS_सूची3_FT_MAX);

	अगर (xfs_sb_version_hasftype(&mp->m_sb))
		sfep->name[sfep->namelen] = ftype;
पूर्ण

/*
 * Given a block directory (dp/block), calculate its size as a लघुक्रमm (sf)
 * directory and a header क्रम the sf directory, अगर it will fit it the
 * space currently present in the inode.  If it won't fit, the output
 * size is too big (but not accurate).
 */
पूर्णांक						/* size क्रम sf क्रमm */
xfs_dir2_block_sfsize(
	xfs_inode_t		*dp,		/* incore inode poपूर्णांकer */
	xfs_dir2_data_hdr_t	*hdr,		/* block directory data */
	xfs_dir2_sf_hdr_t	*sfhp)		/* output: header क्रम sf क्रमm */
अणु
	xfs_dir2_dataptr_t	addr;		/* data entry address */
	xfs_dir2_leaf_entry_t	*blp;		/* leaf area of the block */
	xfs_dir2_block_tail_t	*btp;		/* tail area of the block */
	पूर्णांक			count;		/* लघुक्रमm entry count */
	xfs_dir2_data_entry_t	*dep;		/* data entry in the block */
	पूर्णांक			i;		/* block entry index */
	पूर्णांक			i8count;	/* count of big-inode entries */
	पूर्णांक			isकरोt;		/* entry is "." */
	पूर्णांक			isकरोtकरोt;	/* entry is ".." */
	xfs_mount_t		*mp;		/* mount काष्ठाure poपूर्णांकer */
	पूर्णांक			namelen;	/* total name bytes */
	xfs_ino_t		parent = 0;	/* parent inode number */
	पूर्णांक			size=0;		/* total computed size */
	पूर्णांक			has_ftype;
	काष्ठा xfs_da_geometry	*geo;

	mp = dp->i_mount;
	geo = mp->m_dir_geo;

	/*
	 * अगर there is a filetype field, add the extra byte to the namelen
	 * क्रम each entry that we see.
	 */
	has_ftype = xfs_sb_version_hasftype(&mp->m_sb) ? 1 : 0;

	count = i8count = namelen = 0;
	btp = xfs_dir2_block_tail_p(geo, hdr);
	blp = xfs_dir2_block_leaf_p(btp);

	/*
	 * Iterate over the block's data entries by using the leaf poपूर्णांकers.
	 */
	क्रम (i = 0; i < be32_to_cpu(btp->count); i++) अणु
		अगर ((addr = be32_to_cpu(blp[i].address)) == XFS_सूची2_शून्य_DATAPTR)
			जारी;
		/*
		 * Calculate the poपूर्णांकer to the entry at hand.
		 */
		dep = (xfs_dir2_data_entry_t *)((अक्षर *)hdr +
				xfs_dir2_dataptr_to_off(geo, addr));
		/*
		 * Detect . and .., so we can special-हाल them.
		 * . is not included in sf directories.
		 * .. is included by just the parent inode number.
		 */
		isकरोt = dep->namelen == 1 && dep->name[0] == '.';
		isकरोtकरोt =
			dep->namelen == 2 &&
			dep->name[0] == '.' && dep->name[1] == '.';

		अगर (!isकरोt)
			i8count += be64_to_cpu(dep->inumber) > XFS_सूची2_MAX_SHORT_INUM;

		/* take पूर्णांकo account the file type field */
		अगर (!isकरोt && !isकरोtकरोt) अणु
			count++;
			namelen += dep->namelen + has_ftype;
		पूर्ण अन्यथा अगर (isकरोtकरोt)
			parent = be64_to_cpu(dep->inumber);
		/*
		 * Calculate the new size, see अगर we should give up yet.
		 */
		size = xfs_dir2_sf_hdr_size(i8count) +	/* header */
		       count * 3 * माप(u8) +		/* namelen + offset */
		       namelen +			/* name */
		       (i8count ?			/* inumber */
				count * XFS_INO64_SIZE :
				count * XFS_INO32_SIZE);
		अगर (size > XFS_IFORK_DSIZE(dp))
			वापस size;		/* size value is a failure */
	पूर्ण
	/*
	 * Create the output header, अगर it worked.
	 */
	sfhp->count = count;
	sfhp->i8count = i8count;
	xfs_dir2_sf_put_parent_ino(sfhp, parent);
	वापस size;
पूर्ण

/*
 * Convert a block क्रमmat directory to लघुक्रमm.
 * Caller has alपढ़ोy checked that it will fit, and built us a header.
 */
पूर्णांक						/* error */
xfs_dir2_block_to_sf(
	काष्ठा xfs_da_args	*args,		/* operation arguments */
	काष्ठा xfs_buf		*bp,
	पूर्णांक			size,		/* लघुक्रमm directory size */
	काष्ठा xfs_dir2_sf_hdr	*sfhp)		/* लघुक्रमm directory hdr */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			logflags;	/* inode logging flags */
	काष्ठा xfs_dir2_sf_entry *sfep;		/* लघुक्रमm entry */
	काष्ठा xfs_dir2_sf_hdr	*sfp;		/* लघुक्रमm directory header */
	अचिन्हित पूर्णांक		offset = args->geo->data_entry_offset;
	अचिन्हित पूर्णांक		end;

	trace_xfs_dir2_block_to_sf(args);

	/*
	 * Allocate a temporary destination buffer the size of the inode to
	 * क्रमmat the data पूर्णांकo.  Once we have क्रमmatted the data, we can मुक्त
	 * the block and copy the क्रमmatted data पूर्णांकo the inode literal area.
	 */
	sfp = kmem_alloc(mp->m_sb.sb_inodesize, 0);
	स_नकल(sfp, sfhp, xfs_dir2_sf_hdr_size(sfhp->i8count));

	/*
	 * Loop over the active and unused entries.  Stop when we reach the
	 * leaf/tail portion of the block.
	 */
	end = xfs_dir3_data_end_offset(args->geo, bp->b_addr);
	sfep = xfs_dir2_sf_firstentry(sfp);
	जबतक (offset < end) अणु
		काष्ठा xfs_dir2_data_unused	*dup = bp->b_addr + offset;
		काष्ठा xfs_dir2_data_entry	*dep = bp->b_addr + offset;

		/*
		 * If it's unused, just skip over it.
		 */
		अगर (be16_to_cpu(dup->मुक्तtag) == XFS_सूची2_DATA_FREE_TAG) अणु
			offset += be16_to_cpu(dup->length);
			जारी;
		पूर्ण

		/*
		 * Skip .
		 */
		अगर (dep->namelen == 1 && dep->name[0] == '.')
			ASSERT(be64_to_cpu(dep->inumber) == dp->i_ino);
		/*
		 * Skip .., but make sure the inode number is right.
		 */
		अन्यथा अगर (dep->namelen == 2 &&
			 dep->name[0] == '.' && dep->name[1] == '.')
			ASSERT(be64_to_cpu(dep->inumber) ==
			       xfs_dir2_sf_get_parent_ino(sfp));
		/*
		 * Normal entry, copy it पूर्णांकo लघुक्रमm.
		 */
		अन्यथा अणु
			sfep->namelen = dep->namelen;
			xfs_dir2_sf_put_offset(sfep, offset);
			स_नकल(sfep->name, dep->name, dep->namelen);
			xfs_dir2_sf_put_ino(mp, sfp, sfep,
					      be64_to_cpu(dep->inumber));
			xfs_dir2_sf_put_ftype(mp, sfep,
					xfs_dir2_data_get_ftype(mp, dep));

			sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep);
		पूर्ण
		offset += xfs_dir2_data_entsize(mp, dep->namelen);
	पूर्ण
	ASSERT((अक्षर *)sfep - (अक्षर *)sfp == size);

	/* now we are करोne with the block, we can shrink the inode */
	logflags = XFS_ILOG_CORE;
	error = xfs_dir2_shrink_inode(args, args->geo->datablk, bp);
	अगर (error) अणु
		ASSERT(error != -ENOSPC);
		जाओ out;
	पूर्ण

	/*
	 * The buffer is now unconditionally gone, whether
	 * xfs_dir2_shrink_inode worked or not.
	 *
	 * Convert the inode to local क्रमmat and copy the data in.
	 */
	ASSERT(dp->i_df.अगर_bytes == 0);
	xfs_init_local_विभाजन(dp, XFS_DATA_FORK, sfp, size);
	dp->i_df.अगर_क्रमmat = XFS_DINODE_FMT_LOCAL;
	dp->i_disk_size = size;

	logflags |= XFS_ILOG_DDATA;
	xfs_dir2_sf_check(args);
out:
	xfs_trans_log_inode(args->trans, dp, logflags);
	kmem_मुक्त(sfp);
	वापस error;
पूर्ण

/*
 * Add a name to a लघुक्रमm directory.
 * There are two algorithms, "easy" and "hard" which we decide on
 * beक्रमe changing anything.
 * Convert to block क्रमm अगर necessary, अगर the new entry won't fit.
 */
पूर्णांक						/* error */
xfs_dir2_sf_addname(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	xfs_inode_t		*dp;		/* incore directory inode */
	पूर्णांक			error;		/* error वापस value */
	पूर्णांक			incr_isize;	/* total change in size */
	पूर्णांक			new_isize;	/* size after adding name */
	पूर्णांक			objchange;	/* changing to 8-byte inodes */
	xfs_dir2_data_aoff_t	offset = 0;	/* offset क्रम new entry */
	पूर्णांक			pick;		/* which algorithm to use */
	xfs_dir2_sf_hdr_t	*sfp;		/* लघुक्रमm काष्ठाure */
	xfs_dir2_sf_entry_t	*sfep = शून्य;	/* लघुक्रमm entry */

	trace_xfs_dir2_sf_addname(args);

	ASSERT(xfs_dir2_sf_lookup(args) == -ENOENT);
	dp = args->dp;
	ASSERT(dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	ASSERT(dp->i_disk_size >= दुरत्व(काष्ठा xfs_dir2_sf_hdr, parent));
	ASSERT(dp->i_df.अगर_bytes == dp->i_disk_size);
	ASSERT(dp->i_df.अगर_u1.अगर_data != शून्य);
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	ASSERT(dp->i_disk_size >= xfs_dir2_sf_hdr_size(sfp->i8count));
	/*
	 * Compute entry (and change in) size.
	 */
	incr_isize = xfs_dir2_sf_entsize(dp->i_mount, sfp, args->namelen);
	objchange = 0;

	/*
	 * Do we have to change to 8 byte inodes?
	 */
	अगर (args->inumber > XFS_सूची2_MAX_SHORT_INUM && sfp->i8count == 0) अणु
		/*
		 * Yes, adjust the inode size.  old count + (parent + new)
		 */
		incr_isize += (sfp->count + 2) * XFS_INO64_DIFF;
		objchange = 1;
	पूर्ण

	new_isize = (पूर्णांक)dp->i_disk_size + incr_isize;
	/*
	 * Won't fit as लघुक्रमm any more (due to size),
	 * or the pick routine says it won't (due to offset values).
	 */
	अगर (new_isize > XFS_IFORK_DSIZE(dp) ||
	    (pick =
	     xfs_dir2_sf_addname_pick(args, objchange, &sfep, &offset)) == 0) अणु
		/*
		 * Just checking or no space reservation, it करोesn't fit.
		 */
		अगर ((args->op_flags & XFS_DA_OP_JUSTCHECK) || args->total == 0)
			वापस -ENOSPC;
		/*
		 * Convert to block क्रमm then add the name.
		 */
		error = xfs_dir2_sf_to_block(args);
		अगर (error)
			वापस error;
		वापस xfs_dir2_block_addname(args);
	पूर्ण
	/*
	 * Just checking, it fits.
	 */
	अगर (args->op_flags & XFS_DA_OP_JUSTCHECK)
		वापस 0;
	/*
	 * Do it the easy way - just add it at the end.
	 */
	अगर (pick == 1)
		xfs_dir2_sf_addname_easy(args, sfep, offset, new_isize);
	/*
	 * Do it the hard way - look क्रम a place to insert the new entry.
	 * Convert to 8 byte inode numbers first अगर necessary.
	 */
	अन्यथा अणु
		ASSERT(pick == 2);
		अगर (objchange)
			xfs_dir2_sf_toino8(args);
		xfs_dir2_sf_addname_hard(args, objchange, new_isize);
	पूर्ण
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_DDATA);
	वापस 0;
पूर्ण

/*
 * Add the new entry the "easy" way.
 * This is copying the old directory and adding the new entry at the end.
 * Since it's sorted by "offset" we need room after the last offset
 * that's alपढ़ोy there, and then room to convert to a block directory.
 * This is alपढ़ोy checked by the pick routine.
 */
अटल व्योम
xfs_dir2_sf_addname_easy(
	xfs_da_args_t		*args,		/* operation arguments */
	xfs_dir2_sf_entry_t	*sfep,		/* poपूर्णांकer to new entry */
	xfs_dir2_data_aoff_t	offset,		/* offset to use क्रम new ent */
	पूर्णांक			new_isize)	/* new directory size */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			byteoff;	/* byte offset in sf dir */
	xfs_dir2_sf_hdr_t	*sfp;		/* लघुक्रमm काष्ठाure */

	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	byteoff = (पूर्णांक)((अक्षर *)sfep - (अक्षर *)sfp);
	/*
	 * Grow the in-inode space.
	 */
	xfs_idata_पुनः_स्मृति(dp, xfs_dir2_sf_entsize(mp, sfp, args->namelen),
			  XFS_DATA_FORK);
	/*
	 * Need to set up again due to पुनः_स्मृति of the inode data.
	 */
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	sfep = (xfs_dir2_sf_entry_t *)((अक्षर *)sfp + byteoff);
	/*
	 * Fill in the new entry.
	 */
	sfep->namelen = args->namelen;
	xfs_dir2_sf_put_offset(sfep, offset);
	स_नकल(sfep->name, args->name, sfep->namelen);
	xfs_dir2_sf_put_ino(mp, sfp, sfep, args->inumber);
	xfs_dir2_sf_put_ftype(mp, sfep, args->filetype);

	/*
	 * Update the header and inode.
	 */
	sfp->count++;
	अगर (args->inumber > XFS_सूची2_MAX_SHORT_INUM)
		sfp->i8count++;
	dp->i_disk_size = new_isize;
	xfs_dir2_sf_check(args);
पूर्ण

/*
 * Add the new entry the "hard" way.
 * The caller has alपढ़ोy converted to 8 byte inode numbers अगर necessary,
 * in which हाल we need to leave the i8count at 1.
 * Find a hole that the new entry will fit पूर्णांकo, and copy
 * the first part of the entries, the new entry, and the last part of
 * the entries.
 */
/* ARGSUSED */
अटल व्योम
xfs_dir2_sf_addname_hard(
	xfs_da_args_t		*args,		/* operation arguments */
	पूर्णांक			objchange,	/* changing inode number size */
	पूर्णांक			new_isize)	/* new directory size */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			add_datasize;	/* data size need क्रम new ent */
	अक्षर			*buf;		/* buffer क्रम old */
	पूर्णांक			eof;		/* reached end of old dir */
	पूर्णांक			nbytes;		/* temp क्रम byte copies */
	xfs_dir2_data_aoff_t	new_offset;	/* next offset value */
	xfs_dir2_data_aoff_t	offset;		/* current offset value */
	पूर्णांक			old_isize;	/* previous size */
	xfs_dir2_sf_entry_t	*oldsfep;	/* entry in original dir */
	xfs_dir2_sf_hdr_t	*oldsfp;	/* original लघुक्रमm dir */
	xfs_dir2_sf_entry_t	*sfep;		/* entry in new dir */
	xfs_dir2_sf_hdr_t	*sfp;		/* new लघुक्रमm dir */

	/*
	 * Copy the old directory to the stack buffer.
	 */
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	old_isize = (पूर्णांक)dp->i_disk_size;
	buf = kmem_alloc(old_isize, 0);
	oldsfp = (xfs_dir2_sf_hdr_t *)buf;
	स_नकल(oldsfp, sfp, old_isize);
	/*
	 * Loop over the old directory finding the place we're going
	 * to insert the new entry.
	 * If it's going to end up at the end then oldsfep will poपूर्णांक there.
	 */
	क्रम (offset = args->geo->data_first_offset,
	      oldsfep = xfs_dir2_sf_firstentry(oldsfp),
	      add_datasize = xfs_dir2_data_entsize(mp, args->namelen),
	      eof = (अक्षर *)oldsfep == &buf[old_isize];
	     !eof;
	     offset = new_offset + xfs_dir2_data_entsize(mp, oldsfep->namelen),
	      oldsfep = xfs_dir2_sf_nextentry(mp, oldsfp, oldsfep),
	      eof = (अक्षर *)oldsfep == &buf[old_isize]) अणु
		new_offset = xfs_dir2_sf_get_offset(oldsfep);
		अगर (offset + add_datasize <= new_offset)
			अवरोध;
	पूर्ण
	/*
	 * Get rid of the old directory, then allocate space क्रम
	 * the new one.  We करो this so xfs_idata_पुनः_स्मृति won't copy
	 * the data.
	 */
	xfs_idata_पुनः_स्मृति(dp, -old_isize, XFS_DATA_FORK);
	xfs_idata_पुनः_स्मृति(dp, new_isize, XFS_DATA_FORK);
	/*
	 * Reset the poपूर्णांकer since the buffer was पुनः_स्मृतिated.
	 */
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	/*
	 * Copy the first part of the directory, including the header.
	 */
	nbytes = (पूर्णांक)((अक्षर *)oldsfep - (अक्षर *)oldsfp);
	स_नकल(sfp, oldsfp, nbytes);
	sfep = (xfs_dir2_sf_entry_t *)((अक्षर *)sfp + nbytes);
	/*
	 * Fill in the new entry, and update the header counts.
	 */
	sfep->namelen = args->namelen;
	xfs_dir2_sf_put_offset(sfep, offset);
	स_नकल(sfep->name, args->name, sfep->namelen);
	xfs_dir2_sf_put_ino(mp, sfp, sfep, args->inumber);
	xfs_dir2_sf_put_ftype(mp, sfep, args->filetype);
	sfp->count++;
	अगर (args->inumber > XFS_सूची2_MAX_SHORT_INUM && !objchange)
		sfp->i8count++;
	/*
	 * If there's more left to copy, करो that.
	 */
	अगर (!eof) अणु
		sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep);
		स_नकल(sfep, oldsfep, old_isize - nbytes);
	पूर्ण
	kmem_मुक्त(buf);
	dp->i_disk_size = new_isize;
	xfs_dir2_sf_check(args);
पूर्ण

/*
 * Decide अगर the new entry will fit at all.
 * If it will fit, pick between adding the new entry to the end (easy)
 * or somewhere अन्यथा (hard).
 * Return 0 (won't fit), 1 (easy), 2 (hard).
 */
/*ARGSUSED*/
अटल पूर्णांक					/* pick result */
xfs_dir2_sf_addname_pick(
	xfs_da_args_t		*args,		/* operation arguments */
	पूर्णांक			objchange,	/* inode # size changes */
	xfs_dir2_sf_entry_t	**sfepp,	/* out(1): new entry ptr */
	xfs_dir2_data_aoff_t	*offsetp)	/* out(1): new offset */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			holefit;	/* found hole it will fit in */
	पूर्णांक			i;		/* entry number */
	xfs_dir2_data_aoff_t	offset;		/* data block offset */
	xfs_dir2_sf_entry_t	*sfep;		/* लघुक्रमm entry */
	xfs_dir2_sf_hdr_t	*sfp;		/* लघुक्रमm काष्ठाure */
	पूर्णांक			size;		/* entry's data size */
	पूर्णांक			used;		/* data bytes used */

	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	size = xfs_dir2_data_entsize(mp, args->namelen);
	offset = args->geo->data_first_offset;
	sfep = xfs_dir2_sf_firstentry(sfp);
	holefit = 0;
	/*
	 * Loop over sf entries.
	 * Keep track of data offset and whether we've seen a place
	 * to insert the new entry.
	 */
	क्रम (i = 0; i < sfp->count; i++) अणु
		अगर (!holefit)
			holefit = offset + size <= xfs_dir2_sf_get_offset(sfep);
		offset = xfs_dir2_sf_get_offset(sfep) +
			 xfs_dir2_data_entsize(mp, sfep->namelen);
		sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep);
	पूर्ण
	/*
	 * Calculate data bytes used excluding the new entry, अगर this
	 * was a data block (block क्रमm directory).
	 */
	used = offset +
	       (sfp->count + 3) * (uपूर्णांक)माप(xfs_dir2_leaf_entry_t) +
	       (uपूर्णांक)माप(xfs_dir2_block_tail_t);
	/*
	 * If it won't fit in a block form then we can't insert it,
	 * we'll go back, convert to block, then try the insert and convert
	 * to leaf.
	 */
	अगर (used + (holefit ? 0 : size) > args->geo->blksize)
		वापस 0;
	/*
	 * If changing the inode number size, करो it the hard way.
	 */
	अगर (objchange)
		वापस 2;
	/*
	 * If it won't fit at the end then करो it the hard way (use the hole).
	 */
	अगर (used + size > args->geo->blksize)
		वापस 2;
	/*
	 * Do it the easy way.
	 */
	*sfepp = sfep;
	*offsetp = offset;
	वापस 1;
पूर्ण

#अगर_घोषित DEBUG
/*
 * Check consistency of लघुक्रमm directory, निश्चित अगर bad.
 */
अटल व्योम
xfs_dir2_sf_check(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			i;		/* entry number */
	पूर्णांक			i8count;	/* number of big inode#s */
	xfs_ino_t		ino;		/* entry inode number */
	पूर्णांक			offset;		/* data offset */
	xfs_dir2_sf_entry_t	*sfep;		/* लघुक्रमm dir entry */
	xfs_dir2_sf_hdr_t	*sfp;		/* लघुक्रमm काष्ठाure */

	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	offset = args->geo->data_first_offset;
	ino = xfs_dir2_sf_get_parent_ino(sfp);
	i8count = ino > XFS_सूची2_MAX_SHORT_INUM;

	क्रम (i = 0, sfep = xfs_dir2_sf_firstentry(sfp);
	     i < sfp->count;
	     i++, sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep)) अणु
		ASSERT(xfs_dir2_sf_get_offset(sfep) >= offset);
		ino = xfs_dir2_sf_get_ino(mp, sfp, sfep);
		i8count += ino > XFS_सूची2_MAX_SHORT_INUM;
		offset =
			xfs_dir2_sf_get_offset(sfep) +
			xfs_dir2_data_entsize(mp, sfep->namelen);
		ASSERT(xfs_dir2_sf_get_ftype(mp, sfep) < XFS_सूची3_FT_MAX);
	पूर्ण
	ASSERT(i8count == sfp->i8count);
	ASSERT((अक्षर *)sfep - (अक्षर *)sfp == dp->i_disk_size);
	ASSERT(offset +
	       (sfp->count + 2) * (uपूर्णांक)माप(xfs_dir2_leaf_entry_t) +
	       (uपूर्णांक)माप(xfs_dir2_block_tail_t) <= args->geo->blksize);
पूर्ण
#पूर्ण_अगर	/* DEBUG */

/* Verअगरy the consistency of an अंतरभूत directory. */
xfs_failaddr_t
xfs_dir2_sf_verअगरy(
	काष्ठा xfs_inode		*ip)
अणु
	काष्ठा xfs_mount		*mp = ip->i_mount;
	काष्ठा xfs_अगरork		*अगरp = XFS_IFORK_PTR(ip, XFS_DATA_FORK);
	काष्ठा xfs_dir2_sf_hdr		*sfp;
	काष्ठा xfs_dir2_sf_entry	*sfep;
	काष्ठा xfs_dir2_sf_entry	*next_sfep;
	अक्षर				*endp;
	xfs_ino_t			ino;
	पूर्णांक				i;
	पूर्णांक				i8count;
	पूर्णांक				offset;
	पूर्णांक64_t				size;
	पूर्णांक				error;
	uपूर्णांक8_t				filetype;

	ASSERT(अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);

	sfp = (काष्ठा xfs_dir2_sf_hdr *)अगरp->अगर_u1.अगर_data;
	size = अगरp->अगर_bytes;

	/*
	 * Give up अगर the directory is way too लघु.
	 */
	अगर (size <= दुरत्व(काष्ठा xfs_dir2_sf_hdr, parent) ||
	    size < xfs_dir2_sf_hdr_size(sfp->i8count))
		वापस __this_address;

	endp = (अक्षर *)sfp + size;

	/* Check .. entry */
	ino = xfs_dir2_sf_get_parent_ino(sfp);
	i8count = ino > XFS_सूची2_MAX_SHORT_INUM;
	error = xfs_dir_ino_validate(mp, ino);
	अगर (error)
		वापस __this_address;
	offset = mp->m_dir_geo->data_first_offset;

	/* Check all reported entries */
	sfep = xfs_dir2_sf_firstentry(sfp);
	क्रम (i = 0; i < sfp->count; i++) अणु
		/*
		 * काष्ठा xfs_dir2_sf_entry has a variable length.
		 * Check the fixed-offset parts of the काष्ठाure are
		 * within the data buffer.
		 */
		अगर (((अक्षर *)sfep + माप(*sfep)) >= endp)
			वापस __this_address;

		/* Don't allow names with known bad length. */
		अगर (sfep->namelen == 0)
			वापस __this_address;

		/*
		 * Check that the variable-length part of the काष्ठाure is
		 * within the data buffer.  The next entry starts after the
		 * name component, so nextentry is an acceptable test.
		 */
		next_sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep);
		अगर (endp < (अक्षर *)next_sfep)
			वापस __this_address;

		/* Check that the offsets always increase. */
		अगर (xfs_dir2_sf_get_offset(sfep) < offset)
			वापस __this_address;

		/* Check the inode number. */
		ino = xfs_dir2_sf_get_ino(mp, sfp, sfep);
		i8count += ino > XFS_सूची2_MAX_SHORT_INUM;
		error = xfs_dir_ino_validate(mp, ino);
		अगर (error)
			वापस __this_address;

		/* Check the file type. */
		filetype = xfs_dir2_sf_get_ftype(mp, sfep);
		अगर (filetype >= XFS_सूची3_FT_MAX)
			वापस __this_address;

		offset = xfs_dir2_sf_get_offset(sfep) +
				xfs_dir2_data_entsize(mp, sfep->namelen);

		sfep = next_sfep;
	पूर्ण
	अगर (i8count != sfp->i8count)
		वापस __this_address;
	अगर ((व्योम *)sfep != (व्योम *)endp)
		वापस __this_address;

	/* Make sure this whole thing ought to be in local क्रमmat. */
	अगर (offset + (sfp->count + 2) * (uपूर्णांक)माप(xfs_dir2_leaf_entry_t) +
	    (uपूर्णांक)माप(xfs_dir2_block_tail_t) > mp->m_dir_geo->blksize)
		वापस __this_address;

	वापस शून्य;
पूर्ण

/*
 * Create a new (लघुक्रमm) directory.
 */
पूर्णांक					/* error, always 0 */
xfs_dir2_sf_create(
	xfs_da_args_t	*args,		/* operation arguments */
	xfs_ino_t	pino)		/* parent inode number */
अणु
	xfs_inode_t	*dp;		/* incore directory inode */
	पूर्णांक		i8count;	/* parent inode is an 8-byte number */
	xfs_dir2_sf_hdr_t *sfp;		/* लघुक्रमm काष्ठाure */
	पूर्णांक		size;		/* directory size */

	trace_xfs_dir2_sf_create(args);

	dp = args->dp;

	ASSERT(dp != शून्य);
	ASSERT(dp->i_disk_size == 0);
	/*
	 * If it's currently a zero-length extent file,
	 * convert it to local क्रमmat.
	 */
	अगर (dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_EXTENTS) अणु
		dp->i_df.अगर_क्रमmat = XFS_DINODE_FMT_LOCAL;
		xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE);
	पूर्ण
	ASSERT(dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	ASSERT(dp->i_df.अगर_bytes == 0);
	i8count = pino > XFS_सूची2_MAX_SHORT_INUM;
	size = xfs_dir2_sf_hdr_size(i8count);
	/*
	 * Make a buffer क्रम the data.
	 */
	xfs_idata_पुनः_स्मृति(dp, size, XFS_DATA_FORK);
	/*
	 * Fill in the header,
	 */
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	sfp->i8count = i8count;
	/*
	 * Now can put in the inode number, since i8count is set.
	 */
	xfs_dir2_sf_put_parent_ino(sfp, pino);
	sfp->count = 0;
	dp->i_disk_size = size;
	xfs_dir2_sf_check(args);
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_DDATA);
	वापस 0;
पूर्ण

/*
 * Lookup an entry in a लघुक्रमm directory.
 * Returns EEXIST अगर found, ENOENT अगर not found.
 */
पूर्णांक						/* error */
xfs_dir2_sf_lookup(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			i;		/* entry index */
	पूर्णांक			error;
	xfs_dir2_sf_entry_t	*sfep;		/* लघुक्रमm directory entry */
	xfs_dir2_sf_hdr_t	*sfp;		/* लघुक्रमm काष्ठाure */
	क्रमागत xfs_dacmp		cmp;		/* comparison result */
	xfs_dir2_sf_entry_t	*ci_sfep;	/* हाल-insens. entry */

	trace_xfs_dir2_sf_lookup(args);

	xfs_dir2_sf_check(args);

	ASSERT(dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	ASSERT(dp->i_disk_size >= दुरत्व(काष्ठा xfs_dir2_sf_hdr, parent));
	ASSERT(dp->i_df.अगर_bytes == dp->i_disk_size);
	ASSERT(dp->i_df.अगर_u1.अगर_data != शून्य);
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	ASSERT(dp->i_disk_size >= xfs_dir2_sf_hdr_size(sfp->i8count));
	/*
	 * Special हाल क्रम .
	 */
	अगर (args->namelen == 1 && args->name[0] == '.') अणु
		args->inumber = dp->i_ino;
		args->cmpresult = XFS_CMP_EXACT;
		args->filetype = XFS_सूची3_FT_सूची;
		वापस -EEXIST;
	पूर्ण
	/*
	 * Special हाल क्रम ..
	 */
	अगर (args->namelen == 2 &&
	    args->name[0] == '.' && args->name[1] == '.') अणु
		args->inumber = xfs_dir2_sf_get_parent_ino(sfp);
		args->cmpresult = XFS_CMP_EXACT;
		args->filetype = XFS_सूची3_FT_सूची;
		वापस -EEXIST;
	पूर्ण
	/*
	 * Loop over all the entries trying to match ours.
	 */
	ci_sfep = शून्य;
	क्रम (i = 0, sfep = xfs_dir2_sf_firstentry(sfp); i < sfp->count;
	     i++, sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep)) अणु
		/*
		 * Compare name and अगर it's an exact match, वापस the inode
		 * number. If it's the first हाल-insensitive match, store the
		 * inode number and जारी looking क्रम an exact match.
		 */
		cmp = xfs_dir2_compname(args, sfep->name, sfep->namelen);
		अगर (cmp != XFS_CMP_DIFFERENT && cmp != args->cmpresult) अणु
			args->cmpresult = cmp;
			args->inumber = xfs_dir2_sf_get_ino(mp, sfp, sfep);
			args->filetype = xfs_dir2_sf_get_ftype(mp, sfep);
			अगर (cmp == XFS_CMP_EXACT)
				वापस -EEXIST;
			ci_sfep = sfep;
		पूर्ण
	पूर्ण
	ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
	/*
	 * Here, we can only be करोing a lookup (not a नाम or replace).
	 * If a हाल-insensitive match was not found, वापस -ENOENT.
	 */
	अगर (!ci_sfep)
		वापस -ENOENT;
	/* otherwise process the CI match as required by the caller */
	error = xfs_dir_cilookup_result(args, ci_sfep->name, ci_sfep->namelen);
	वापस error;
पूर्ण

/*
 * Remove an entry from a लघुक्रमm directory.
 */
पूर्णांक						/* error */
xfs_dir2_sf_हटाओname(
	xfs_da_args_t		*args)
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			byteoff;	/* offset of हटाओd entry */
	पूर्णांक			entsize;	/* this entry's size */
	पूर्णांक			i;		/* लघुक्रमm entry index */
	पूर्णांक			newsize;	/* new inode size */
	पूर्णांक			oldsize;	/* old inode size */
	xfs_dir2_sf_entry_t	*sfep;		/* लघुक्रमm directory entry */
	xfs_dir2_sf_hdr_t	*sfp;		/* लघुक्रमm काष्ठाure */

	trace_xfs_dir2_sf_हटाओname(args);

	ASSERT(dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	oldsize = (पूर्णांक)dp->i_disk_size;
	ASSERT(oldsize >= दुरत्व(काष्ठा xfs_dir2_sf_hdr, parent));
	ASSERT(dp->i_df.अगर_bytes == oldsize);
	ASSERT(dp->i_df.अगर_u1.अगर_data != शून्य);
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	ASSERT(oldsize >= xfs_dir2_sf_hdr_size(sfp->i8count));
	/*
	 * Loop over the old directory entries.
	 * Find the one we're deleting.
	 */
	क्रम (i = 0, sfep = xfs_dir2_sf_firstentry(sfp); i < sfp->count;
	     i++, sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep)) अणु
		अगर (xfs_da_compname(args, sfep->name, sfep->namelen) ==
								XFS_CMP_EXACT) अणु
			ASSERT(xfs_dir2_sf_get_ino(mp, sfp, sfep) ==
			       args->inumber);
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * Didn't find it.
	 */
	अगर (i == sfp->count)
		वापस -ENOENT;
	/*
	 * Calculate sizes.
	 */
	byteoff = (पूर्णांक)((अक्षर *)sfep - (अक्षर *)sfp);
	entsize = xfs_dir2_sf_entsize(mp, sfp, args->namelen);
	newsize = oldsize - entsize;
	/*
	 * Copy the part अगर any after the हटाओd entry, sliding it करोwn.
	 */
	अगर (byteoff + entsize < oldsize)
		स_हटाओ((अक्षर *)sfp + byteoff, (अक्षर *)sfp + byteoff + entsize,
			oldsize - (byteoff + entsize));
	/*
	 * Fix up the header and file size.
	 */
	sfp->count--;
	dp->i_disk_size = newsize;
	/*
	 * Reallocate, making it smaller.
	 */
	xfs_idata_पुनः_स्मृति(dp, newsize - oldsize, XFS_DATA_FORK);
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	/*
	 * Are we changing inode number size?
	 */
	अगर (args->inumber > XFS_सूची2_MAX_SHORT_INUM) अणु
		अगर (sfp->i8count == 1)
			xfs_dir2_sf_toino4(args);
		अन्यथा
			sfp->i8count--;
	पूर्ण
	xfs_dir2_sf_check(args);
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_DDATA);
	वापस 0;
पूर्ण

/*
 * Check whether the sf dir replace operation need more blocks.
 */
अटल bool
xfs_dir2_sf_replace_needblock(
	काष्ठा xfs_inode	*dp,
	xfs_ino_t		inum)
अणु
	पूर्णांक			newsize;
	काष्ठा xfs_dir2_sf_hdr	*sfp;

	अगर (dp->i_df.अगर_क्रमmat != XFS_DINODE_FMT_LOCAL)
		वापस false;

	sfp = (काष्ठा xfs_dir2_sf_hdr *)dp->i_df.अगर_u1.अगर_data;
	newsize = dp->i_df.अगर_bytes + (sfp->count + 1) * XFS_INO64_DIFF;

	वापस inum > XFS_सूची2_MAX_SHORT_INUM &&
	       sfp->i8count == 0 && newsize > XFS_IFORK_DSIZE(dp);
पूर्ण

/*
 * Replace the inode number of an entry in a लघुक्रमm directory.
 */
पूर्णांक						/* error */
xfs_dir2_sf_replace(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	पूर्णांक			i;		/* entry index */
	xfs_ino_t		ino=0;		/* entry old inode number */
	पूर्णांक			i8elevated;	/* sf_toino8 set i8count=1 */
	xfs_dir2_sf_entry_t	*sfep;		/* लघुक्रमm directory entry */
	xfs_dir2_sf_hdr_t	*sfp;		/* लघुक्रमm काष्ठाure */

	trace_xfs_dir2_sf_replace(args);

	ASSERT(dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL);
	ASSERT(dp->i_disk_size >= दुरत्व(काष्ठा xfs_dir2_sf_hdr, parent));
	ASSERT(dp->i_df.अगर_bytes == dp->i_disk_size);
	ASSERT(dp->i_df.अगर_u1.अगर_data != शून्य);
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	ASSERT(dp->i_disk_size >= xfs_dir2_sf_hdr_size(sfp->i8count));

	/*
	 * New inode number is large, and need to convert to 8-byte inodes.
	 */
	अगर (args->inumber > XFS_सूची2_MAX_SHORT_INUM && sfp->i8count == 0) अणु
		पूर्णांक	error;			/* error वापस value */

		/*
		 * Won't fit as लघुक्रमm, convert to block then करो replace.
		 */
		अगर (xfs_dir2_sf_replace_needblock(dp, args->inumber)) अणु
			error = xfs_dir2_sf_to_block(args);
			अगर (error)
				वापस error;
			वापस xfs_dir2_block_replace(args);
		पूर्ण
		/*
		 * Still fits, convert to 8-byte now.
		 */
		xfs_dir2_sf_toino8(args);
		i8elevated = 1;
		sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	पूर्ण अन्यथा
		i8elevated = 0;

	ASSERT(args->namelen != 1 || args->name[0] != '.');
	/*
	 * Replace ..'s entry.
	 */
	अगर (args->namelen == 2 &&
	    args->name[0] == '.' && args->name[1] == '.') अणु
		ino = xfs_dir2_sf_get_parent_ino(sfp);
		ASSERT(args->inumber != ino);
		xfs_dir2_sf_put_parent_ino(sfp, args->inumber);
	पूर्ण
	/*
	 * Normal entry, look क्रम the name.
	 */
	अन्यथा अणु
		क्रम (i = 0, sfep = xfs_dir2_sf_firstentry(sfp); i < sfp->count;
		     i++, sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep)) अणु
			अगर (xfs_da_compname(args, sfep->name, sfep->namelen) ==
								XFS_CMP_EXACT) अणु
				ino = xfs_dir2_sf_get_ino(mp, sfp, sfep);
				ASSERT(args->inumber != ino);
				xfs_dir2_sf_put_ino(mp, sfp, sfep,
						args->inumber);
				xfs_dir2_sf_put_ftype(mp, sfep, args->filetype);
				अवरोध;
			पूर्ण
		पूर्ण
		/*
		 * Didn't find it.
		 */
		अगर (i == sfp->count) अणु
			ASSERT(args->op_flags & XFS_DA_OP_OKNOENT);
			अगर (i8elevated)
				xfs_dir2_sf_toino4(args);
			वापस -ENOENT;
		पूर्ण
	पूर्ण
	/*
	 * See अगर the old number was large, the new number is small.
	 */
	अगर (ino > XFS_सूची2_MAX_SHORT_INUM &&
	    args->inumber <= XFS_सूची2_MAX_SHORT_INUM) अणु
		/*
		 * And the old count was one, so need to convert to small.
		 */
		अगर (sfp->i8count == 1)
			xfs_dir2_sf_toino4(args);
		अन्यथा
			sfp->i8count--;
	पूर्ण
	/*
	 * See अगर the old number was small, the new number is large.
	 */
	अगर (ino <= XFS_सूची2_MAX_SHORT_INUM &&
	    args->inumber > XFS_सूची2_MAX_SHORT_INUM) अणु
		/*
		 * add to the i8count unless we just converted to 8-byte
		 * inodes (which करोes an implied i8count = 1)
		 */
		ASSERT(sfp->i8count != 0);
		अगर (!i8elevated)
			sfp->i8count++;
	पूर्ण
	xfs_dir2_sf_check(args);
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_DDATA);
	वापस 0;
पूर्ण

/*
 * Convert from 8-byte inode numbers to 4-byte inode numbers.
 * The last 8-byte inode number is gone, but the count is still 1.
 */
अटल व्योम
xfs_dir2_sf_toino4(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	अक्षर			*buf;		/* old dir's buffer */
	पूर्णांक			i;		/* entry index */
	पूर्णांक			newsize;	/* new inode size */
	xfs_dir2_sf_entry_t	*oldsfep;	/* old sf entry */
	xfs_dir2_sf_hdr_t	*oldsfp;	/* old sf directory */
	पूर्णांक			oldsize;	/* old inode size */
	xfs_dir2_sf_entry_t	*sfep;		/* new sf entry */
	xfs_dir2_sf_hdr_t	*sfp;		/* new sf directory */

	trace_xfs_dir2_sf_toino4(args);

	/*
	 * Copy the old directory to the buffer.
	 * Then nuke it from the inode, and add the new buffer to the inode.
	 * Don't want xfs_idata_पुनः_स्मृति copying the data here.
	 */
	oldsize = dp->i_df.अगर_bytes;
	buf = kmem_alloc(oldsize, 0);
	oldsfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	ASSERT(oldsfp->i8count == 1);
	स_नकल(buf, oldsfp, oldsize);
	/*
	 * Compute the new inode size.
	 */
	newsize = oldsize - (oldsfp->count + 1) * XFS_INO64_DIFF;
	xfs_idata_पुनः_स्मृति(dp, -oldsize, XFS_DATA_FORK);
	xfs_idata_पुनः_स्मृति(dp, newsize, XFS_DATA_FORK);
	/*
	 * Reset our poपूर्णांकers, the data has moved.
	 */
	oldsfp = (xfs_dir2_sf_hdr_t *)buf;
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	/*
	 * Fill in the new header.
	 */
	sfp->count = oldsfp->count;
	sfp->i8count = 0;
	xfs_dir2_sf_put_parent_ino(sfp, xfs_dir2_sf_get_parent_ino(oldsfp));
	/*
	 * Copy the entries field by field.
	 */
	क्रम (i = 0, sfep = xfs_dir2_sf_firstentry(sfp),
		    oldsfep = xfs_dir2_sf_firstentry(oldsfp);
	     i < sfp->count;
	     i++, sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep),
		  oldsfep = xfs_dir2_sf_nextentry(mp, oldsfp, oldsfep)) अणु
		sfep->namelen = oldsfep->namelen;
		स_नकल(sfep->offset, oldsfep->offset, माप(sfep->offset));
		स_नकल(sfep->name, oldsfep->name, sfep->namelen);
		xfs_dir2_sf_put_ino(mp, sfp, sfep,
				xfs_dir2_sf_get_ino(mp, oldsfp, oldsfep));
		xfs_dir2_sf_put_ftype(mp, sfep,
				xfs_dir2_sf_get_ftype(mp, oldsfep));
	पूर्ण
	/*
	 * Clean up the inode.
	 */
	kmem_मुक्त(buf);
	dp->i_disk_size = newsize;
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_DDATA);
पूर्ण

/*
 * Convert existing entries from 4-byte inode numbers to 8-byte inode numbers.
 * The new entry w/ an 8-byte inode number is not there yet; we leave with
 * i8count set to 1, but no corresponding 8-byte entry.
 */
अटल व्योम
xfs_dir2_sf_toino8(
	xfs_da_args_t		*args)		/* operation arguments */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	अक्षर			*buf;		/* old dir's buffer */
	पूर्णांक			i;		/* entry index */
	पूर्णांक			newsize;	/* new inode size */
	xfs_dir2_sf_entry_t	*oldsfep;	/* old sf entry */
	xfs_dir2_sf_hdr_t	*oldsfp;	/* old sf directory */
	पूर्णांक			oldsize;	/* old inode size */
	xfs_dir2_sf_entry_t	*sfep;		/* new sf entry */
	xfs_dir2_sf_hdr_t	*sfp;		/* new sf directory */

	trace_xfs_dir2_sf_toino8(args);

	/*
	 * Copy the old directory to the buffer.
	 * Then nuke it from the inode, and add the new buffer to the inode.
	 * Don't want xfs_idata_पुनः_स्मृति copying the data here.
	 */
	oldsize = dp->i_df.अगर_bytes;
	buf = kmem_alloc(oldsize, 0);
	oldsfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	ASSERT(oldsfp->i8count == 0);
	स_नकल(buf, oldsfp, oldsize);
	/*
	 * Compute the new inode size (nb: entry count + 1 क्रम parent)
	 */
	newsize = oldsize + (oldsfp->count + 1) * XFS_INO64_DIFF;
	xfs_idata_पुनः_स्मृति(dp, -oldsize, XFS_DATA_FORK);
	xfs_idata_पुनः_स्मृति(dp, newsize, XFS_DATA_FORK);
	/*
	 * Reset our poपूर्णांकers, the data has moved.
	 */
	oldsfp = (xfs_dir2_sf_hdr_t *)buf;
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	/*
	 * Fill in the new header.
	 */
	sfp->count = oldsfp->count;
	sfp->i8count = 1;
	xfs_dir2_sf_put_parent_ino(sfp, xfs_dir2_sf_get_parent_ino(oldsfp));
	/*
	 * Copy the entries field by field.
	 */
	क्रम (i = 0, sfep = xfs_dir2_sf_firstentry(sfp),
		    oldsfep = xfs_dir2_sf_firstentry(oldsfp);
	     i < sfp->count;
	     i++, sfep = xfs_dir2_sf_nextentry(mp, sfp, sfep),
		  oldsfep = xfs_dir2_sf_nextentry(mp, oldsfp, oldsfep)) अणु
		sfep->namelen = oldsfep->namelen;
		स_नकल(sfep->offset, oldsfep->offset, माप(sfep->offset));
		स_नकल(sfep->name, oldsfep->name, sfep->namelen);
		xfs_dir2_sf_put_ino(mp, sfp, sfep,
				xfs_dir2_sf_get_ino(mp, oldsfp, oldsfep));
		xfs_dir2_sf_put_ftype(mp, sfep,
				xfs_dir2_sf_get_ftype(mp, oldsfep));
	पूर्ण
	/*
	 * Clean up the inode.
	 */
	kmem_मुक्त(buf);
	dp->i_disk_size = newsize;
	xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE | XFS_ILOG_DDATA);
पूर्ण
