<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2000-2001,2005 Silicon Graphics, Inc.
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
#समावेश "xfs_bmap.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "xfs_errortag.h"
#समावेश "xfs_error.h"
#समावेश "xfs_trace.h"

काष्ठा xfs_name xfs_name_करोtकरोt = अणु (अचिन्हित अक्षर *)"..", 2, XFS_सूची3_FT_सूची पूर्ण;

/*
 * Convert inode mode to directory entry filetype
 */
अचिन्हित अक्षर
xfs_mode_to_ftype(
	पूर्णांक		mode)
अणु
	चयन (mode & S_IFMT) अणु
	हाल S_IFREG:
		वापस XFS_सूची3_FT_REG_खाता;
	हाल S_IFसूची:
		वापस XFS_सूची3_FT_सूची;
	हाल S_IFCHR:
		वापस XFS_सूची3_FT_CHRDEV;
	हाल S_IFBLK:
		वापस XFS_सूची3_FT_BLKDEV;
	हाल S_IFIFO:
		वापस XFS_सूची3_FT_FIFO;
	हाल S_IFSOCK:
		वापस XFS_सूची3_FT_SOCK;
	हाल S_IFLNK:
		वापस XFS_सूची3_FT_SYMLINK;
	शेष:
		वापस XFS_सूची3_FT_UNKNOWN;
	पूर्ण
पूर्ण

/*
 * ASCII हाल-insensitive (ie. A-Z) support क्रम directories that was
 * used in IRIX.
 */
xfs_dahash_t
xfs_ascii_ci_hashname(
	काष्ठा xfs_name	*name)
अणु
	xfs_dahash_t	hash;
	पूर्णांक		i;

	क्रम (i = 0, hash = 0; i < name->len; i++)
		hash = छोटे(name->name[i]) ^ rol32(hash, 7);

	वापस hash;
पूर्ण

क्रमागत xfs_dacmp
xfs_ascii_ci_compname(
	काष्ठा xfs_da_args	*args,
	स्थिर अचिन्हित अक्षर	*name,
	पूर्णांक			len)
अणु
	क्रमागत xfs_dacmp		result;
	पूर्णांक			i;

	अगर (args->namelen != len)
		वापस XFS_CMP_DIFFERENT;

	result = XFS_CMP_EXACT;
	क्रम (i = 0; i < len; i++) अणु
		अगर (args->name[i] == name[i])
			जारी;
		अगर (छोटे(args->name[i]) != छोटे(name[i]))
			वापस XFS_CMP_DIFFERENT;
		result = XFS_CMP_CASE;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक
xfs_da_mount(
	काष्ठा xfs_mount	*mp)
अणु
	काष्ठा xfs_da_geometry	*dageo;


	ASSERT(mp->m_sb.sb_versionnum & XFS_SB_VERSION_सूचीV2BIT);
	ASSERT(xfs_dir2_dirblock_bytes(&mp->m_sb) <= XFS_MAX_BLOCKSIZE);

	mp->m_dir_geo = kmem_zalloc(माप(काष्ठा xfs_da_geometry),
				    KM_MAYFAIL);
	mp->m_attr_geo = kmem_zalloc(माप(काष्ठा xfs_da_geometry),
				     KM_MAYFAIL);
	अगर (!mp->m_dir_geo || !mp->m_attr_geo) अणु
		kmem_मुक्त(mp->m_dir_geo);
		kmem_मुक्त(mp->m_attr_geo);
		वापस -ENOMEM;
	पूर्ण

	/* set up directory geometry */
	dageo = mp->m_dir_geo;
	dageo->blklog = mp->m_sb.sb_blocklog + mp->m_sb.sb_dirblklog;
	dageo->fsblog = mp->m_sb.sb_blocklog;
	dageo->blksize = xfs_dir2_dirblock_bytes(&mp->m_sb);
	dageo->fsbcount = 1 << mp->m_sb.sb_dirblklog;
	अगर (xfs_sb_version_hascrc(&mp->m_sb)) अणु
		dageo->node_hdr_size = माप(काष्ठा xfs_da3_node_hdr);
		dageo->leaf_hdr_size = माप(काष्ठा xfs_dir3_leaf_hdr);
		dageo->मुक्त_hdr_size = माप(काष्ठा xfs_dir3_मुक्त_hdr);
		dageo->data_entry_offset =
				माप(काष्ठा xfs_dir3_data_hdr);
	पूर्ण अन्यथा अणु
		dageo->node_hdr_size = माप(काष्ठा xfs_da_node_hdr);
		dageo->leaf_hdr_size = माप(काष्ठा xfs_dir2_leaf_hdr);
		dageo->मुक्त_hdr_size = माप(काष्ठा xfs_dir2_मुक्त_hdr);
		dageo->data_entry_offset =
				माप(काष्ठा xfs_dir2_data_hdr);
	पूर्ण
	dageo->leaf_max_ents = (dageo->blksize - dageo->leaf_hdr_size) /
			माप(काष्ठा xfs_dir2_leaf_entry);
	dageo->मुक्त_max_bests = (dageo->blksize - dageo->मुक्त_hdr_size) /
			माप(xfs_dir2_data_off_t);

	dageo->data_first_offset = dageo->data_entry_offset +
			xfs_dir2_data_entsize(mp, 1) +
			xfs_dir2_data_entsize(mp, 2);

	/*
	 * Now we've set up the block conversion variables, we can calculate the
	 * segment block स्थिरants using the geometry काष्ठाure.
	 */
	dageo->datablk = xfs_dir2_byte_to_da(dageo, XFS_सूची2_DATA_OFFSET);
	dageo->leafblk = xfs_dir2_byte_to_da(dageo, XFS_सूची2_LEAF_OFFSET);
	dageo->मुक्तblk = xfs_dir2_byte_to_da(dageo, XFS_सूची2_FREE_OFFSET);
	dageo->node_ents = (dageo->blksize - dageo->node_hdr_size) /
				(uपूर्णांक)माप(xfs_da_node_entry_t);
	dageo->magicpct = (dageo->blksize * 37) / 100;

	/* set up attribute geometry - single fsb only */
	dageo = mp->m_attr_geo;
	dageo->blklog = mp->m_sb.sb_blocklog;
	dageo->fsblog = mp->m_sb.sb_blocklog;
	dageo->blksize = 1 << dageo->blklog;
	dageo->fsbcount = 1;
	dageo->node_hdr_size = mp->m_dir_geo->node_hdr_size;
	dageo->node_ents = (dageo->blksize - dageo->node_hdr_size) /
				(uपूर्णांक)माप(xfs_da_node_entry_t);
	dageo->magicpct = (dageo->blksize * 37) / 100;
	वापस 0;
पूर्ण

व्योम
xfs_da_unmount(
	काष्ठा xfs_mount	*mp)
अणु
	kmem_मुक्त(mp->m_dir_geo);
	kmem_मुक्त(mp->m_attr_geo);
पूर्ण

/*
 * Return 1 अगर directory contains only "." and "..".
 */
पूर्णांक
xfs_dir_isempty(
	xfs_inode_t	*dp)
अणु
	xfs_dir2_sf_hdr_t	*sfp;

	ASSERT(S_ISसूची(VFS_I(dp)->i_mode));
	अगर (dp->i_disk_size == 0)	/* might happen during shutकरोwn. */
		वापस 1;
	अगर (dp->i_disk_size > XFS_IFORK_DSIZE(dp))
		वापस 0;
	sfp = (xfs_dir2_sf_hdr_t *)dp->i_df.अगर_u1.अगर_data;
	वापस !sfp->count;
पूर्ण

/*
 * Validate a given inode number.
 */
पूर्णांक
xfs_dir_ino_validate(
	xfs_mount_t	*mp,
	xfs_ino_t	ino)
अणु
	bool		ino_ok = xfs_verअगरy_dir_ino(mp, ino);

	अगर (XFS_IS_CORRUPT(mp, !ino_ok) ||
	    XFS_TEST_ERROR(false, mp, XFS_ERRTAG_सूची_INO_VALIDATE)) अणु
		xfs_warn(mp, "Invalid inode number 0x%Lx",
				(अचिन्हित दीर्घ दीर्घ) ino);
		वापस -EFSCORRUPTED;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Initialize a directory with its "." and ".." entries.
 */
पूर्णांक
xfs_dir_init(
	xfs_trans_t	*tp,
	xfs_inode_t	*dp,
	xfs_inode_t	*pdp)
अणु
	काष्ठा xfs_da_args *args;
	पूर्णांक		error;

	ASSERT(S_ISसूची(VFS_I(dp)->i_mode));
	error = xfs_dir_ino_validate(tp->t_mountp, pdp->i_ino);
	अगर (error)
		वापस error;

	args = kmem_zalloc(माप(*args), KM_NOFS);
	अगर (!args)
		वापस -ENOMEM;

	args->geo = dp->i_mount->m_dir_geo;
	args->dp = dp;
	args->trans = tp;
	error = xfs_dir2_sf_create(args, pdp->i_ino);
	kmem_मुक्त(args);
	वापस error;
पूर्ण

/*
 * Enter a name in a directory, or check क्रम available space.
 * If inum is 0, only the available space test is perक्रमmed.
 */
पूर्णांक
xfs_dir_createname(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_name		*name,
	xfs_ino_t		inum,		/* new entry inode number */
	xfs_extlen_t		total)		/* bmap's total block count */
अणु
	काष्ठा xfs_da_args	*args;
	पूर्णांक			rval;
	पूर्णांक			v;		/* type-checking value */

	ASSERT(S_ISसूची(VFS_I(dp)->i_mode));

	अगर (inum) अणु
		rval = xfs_dir_ino_validate(tp->t_mountp, inum);
		अगर (rval)
			वापस rval;
		XFS_STATS_INC(dp->i_mount, xs_dir_create);
	पूर्ण

	args = kmem_zalloc(माप(*args), KM_NOFS);
	अगर (!args)
		वापस -ENOMEM;

	args->geo = dp->i_mount->m_dir_geo;
	args->name = name->name;
	args->namelen = name->len;
	args->filetype = name->type;
	args->hashval = xfs_dir2_hashname(dp->i_mount, name);
	args->inumber = inum;
	args->dp = dp;
	args->total = total;
	args->whichविभाजन = XFS_DATA_FORK;
	args->trans = tp;
	args->op_flags = XFS_DA_OP_ADDNAME | XFS_DA_OP_OKNOENT;
	अगर (!inum)
		args->op_flags |= XFS_DA_OP_JUSTCHECK;

	अगर (dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL) अणु
		rval = xfs_dir2_sf_addname(args);
		जाओ out_मुक्त;
	पूर्ण

	rval = xfs_dir2_isblock(args, &v);
	अगर (rval)
		जाओ out_मुक्त;
	अगर (v) अणु
		rval = xfs_dir2_block_addname(args);
		जाओ out_मुक्त;
	पूर्ण

	rval = xfs_dir2_isleaf(args, &v);
	अगर (rval)
		जाओ out_मुक्त;
	अगर (v)
		rval = xfs_dir2_leaf_addname(args);
	अन्यथा
		rval = xfs_dir2_node_addname(args);

out_मुक्त:
	kmem_मुक्त(args);
	वापस rval;
पूर्ण

/*
 * If करोing a CI lookup and हाल-insensitive match, dup actual name पूर्णांकo
 * args.value. Return EEXIST क्रम success (ie. name found) or an error.
 */
पूर्णांक
xfs_dir_cilookup_result(
	काष्ठा xfs_da_args *args,
	स्थिर अचिन्हित अक्षर *name,
	पूर्णांक		len)
अणु
	अगर (args->cmpresult == XFS_CMP_DIFFERENT)
		वापस -ENOENT;
	अगर (args->cmpresult != XFS_CMP_CASE ||
					!(args->op_flags & XFS_DA_OP_CILOOKUP))
		वापस -EEXIST;

	args->value = kmem_alloc(len, KM_NOFS | KM_MAYFAIL);
	अगर (!args->value)
		वापस -ENOMEM;

	स_नकल(args->value, name, len);
	args->valuelen = len;
	वापस -EEXIST;
पूर्ण

/*
 * Lookup a name in a directory, give back the inode number.
 * If ci_name is not शून्य, वापसs the actual name in ci_name अगर it dअगरfers
 * to name, or ci_name->name is set to शून्य क्रम an exact match.
 */

पूर्णांक
xfs_dir_lookup(
	xfs_trans_t	*tp,
	xfs_inode_t	*dp,
	काष्ठा xfs_name	*name,
	xfs_ino_t	*inum,		/* out: inode number */
	काष्ठा xfs_name *ci_name)	/* out: actual name अगर CI match */
अणु
	काष्ठा xfs_da_args *args;
	पूर्णांक		rval;
	पूर्णांक		v;		/* type-checking value */
	पूर्णांक		lock_mode;

	ASSERT(S_ISसूची(VFS_I(dp)->i_mode));
	XFS_STATS_INC(dp->i_mount, xs_dir_lookup);

	/*
	 * We need to use KM_NOFS here so that lockdep will not throw false
	 * positive deadlock warnings on a non-transactional lookup path. It is
	 * safe to recurse पूर्णांकo inode recalim in that हाल, but lockdep can't
	 * easily be taught about it. Hence KM_NOFS aव्योमs having to add more
	 * lockdep Doing this aव्योमs having to add a bunch of lockdep class
	 * annotations पूर्णांकo the reclaim path क्रम the ilock.
	 */
	args = kmem_zalloc(माप(*args), KM_NOFS);
	args->geo = dp->i_mount->m_dir_geo;
	args->name = name->name;
	args->namelen = name->len;
	args->filetype = name->type;
	args->hashval = xfs_dir2_hashname(dp->i_mount, name);
	args->dp = dp;
	args->whichविभाजन = XFS_DATA_FORK;
	args->trans = tp;
	args->op_flags = XFS_DA_OP_OKNOENT;
	अगर (ci_name)
		args->op_flags |= XFS_DA_OP_CILOOKUP;

	lock_mode = xfs_ilock_data_map_shared(dp);
	अगर (dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL) अणु
		rval = xfs_dir2_sf_lookup(args);
		जाओ out_check_rval;
	पूर्ण

	rval = xfs_dir2_isblock(args, &v);
	अगर (rval)
		जाओ out_मुक्त;
	अगर (v) अणु
		rval = xfs_dir2_block_lookup(args);
		जाओ out_check_rval;
	पूर्ण

	rval = xfs_dir2_isleaf(args, &v);
	अगर (rval)
		जाओ out_मुक्त;
	अगर (v)
		rval = xfs_dir2_leaf_lookup(args);
	अन्यथा
		rval = xfs_dir2_node_lookup(args);

out_check_rval:
	अगर (rval == -EEXIST)
		rval = 0;
	अगर (!rval) अणु
		*inum = args->inumber;
		अगर (ci_name) अणु
			ci_name->name = args->value;
			ci_name->len = args->valuelen;
		पूर्ण
	पूर्ण
out_मुक्त:
	xfs_iunlock(dp, lock_mode);
	kmem_मुक्त(args);
	वापस rval;
पूर्ण

/*
 * Remove an entry from a directory.
 */
पूर्णांक
xfs_dir_हटाओname(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_name		*name,
	xfs_ino_t		ino,
	xfs_extlen_t		total)		/* bmap's total block count */
अणु
	काष्ठा xfs_da_args	*args;
	पूर्णांक			rval;
	पूर्णांक			v;		/* type-checking value */

	ASSERT(S_ISसूची(VFS_I(dp)->i_mode));
	XFS_STATS_INC(dp->i_mount, xs_dir_हटाओ);

	args = kmem_zalloc(माप(*args), KM_NOFS);
	अगर (!args)
		वापस -ENOMEM;

	args->geo = dp->i_mount->m_dir_geo;
	args->name = name->name;
	args->namelen = name->len;
	args->filetype = name->type;
	args->hashval = xfs_dir2_hashname(dp->i_mount, name);
	args->inumber = ino;
	args->dp = dp;
	args->total = total;
	args->whichविभाजन = XFS_DATA_FORK;
	args->trans = tp;

	अगर (dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL) अणु
		rval = xfs_dir2_sf_हटाओname(args);
		जाओ out_मुक्त;
	पूर्ण

	rval = xfs_dir2_isblock(args, &v);
	अगर (rval)
		जाओ out_मुक्त;
	अगर (v) अणु
		rval = xfs_dir2_block_हटाओname(args);
		जाओ out_मुक्त;
	पूर्ण

	rval = xfs_dir2_isleaf(args, &v);
	अगर (rval)
		जाओ out_मुक्त;
	अगर (v)
		rval = xfs_dir2_leaf_हटाओname(args);
	अन्यथा
		rval = xfs_dir2_node_हटाओname(args);
out_मुक्त:
	kmem_मुक्त(args);
	वापस rval;
पूर्ण

/*
 * Replace the inode number of a directory entry.
 */
पूर्णांक
xfs_dir_replace(
	काष्ठा xfs_trans	*tp,
	काष्ठा xfs_inode	*dp,
	काष्ठा xfs_name		*name,		/* name of entry to replace */
	xfs_ino_t		inum,		/* new inode number */
	xfs_extlen_t		total)		/* bmap's total block count */
अणु
	काष्ठा xfs_da_args	*args;
	पूर्णांक			rval;
	पूर्णांक			v;		/* type-checking value */

	ASSERT(S_ISसूची(VFS_I(dp)->i_mode));

	rval = xfs_dir_ino_validate(tp->t_mountp, inum);
	अगर (rval)
		वापस rval;

	args = kmem_zalloc(माप(*args), KM_NOFS);
	अगर (!args)
		वापस -ENOMEM;

	args->geo = dp->i_mount->m_dir_geo;
	args->name = name->name;
	args->namelen = name->len;
	args->filetype = name->type;
	args->hashval = xfs_dir2_hashname(dp->i_mount, name);
	args->inumber = inum;
	args->dp = dp;
	args->total = total;
	args->whichविभाजन = XFS_DATA_FORK;
	args->trans = tp;

	अगर (dp->i_df.अगर_क्रमmat == XFS_DINODE_FMT_LOCAL) अणु
		rval = xfs_dir2_sf_replace(args);
		जाओ out_मुक्त;
	पूर्ण

	rval = xfs_dir2_isblock(args, &v);
	अगर (rval)
		जाओ out_मुक्त;
	अगर (v) अणु
		rval = xfs_dir2_block_replace(args);
		जाओ out_मुक्त;
	पूर्ण

	rval = xfs_dir2_isleaf(args, &v);
	अगर (rval)
		जाओ out_मुक्त;
	अगर (v)
		rval = xfs_dir2_leaf_replace(args);
	अन्यथा
		rval = xfs_dir2_node_replace(args);
out_मुक्त:
	kmem_मुक्त(args);
	वापस rval;
पूर्ण

/*
 * See अगर this entry can be added to the directory without allocating space.
 */
पूर्णांक
xfs_dir_canenter(
	xfs_trans_t	*tp,
	xfs_inode_t	*dp,
	काष्ठा xfs_name	*name)		/* name of entry to add */
अणु
	वापस xfs_dir_createname(tp, dp, name, 0, 0);
पूर्ण

/*
 * Utility routines.
 */

/*
 * Add a block to the directory.
 *
 * This routine is क्रम data and मुक्त blocks, not leaf/node blocks which are
 * handled by xfs_da_grow_inode.
 */
पूर्णांक
xfs_dir2_grow_inode(
	काष्ठा xfs_da_args	*args,
	पूर्णांक			space,	/* v2 dir's space XFS_सूची2_xxx_SPACE */
	xfs_dir2_db_t		*dbp)	/* out: block number added */
अणु
	काष्ठा xfs_inode	*dp = args->dp;
	काष्ठा xfs_mount	*mp = dp->i_mount;
	xfs_fileoff_t		bno;	/* directory offset of new block */
	पूर्णांक			count;	/* count of fileप्रणाली blocks */
	पूर्णांक			error;

	trace_xfs_dir2_grow_inode(args, space);

	/*
	 * Set lowest possible block in the space requested.
	 */
	bno = XFS_B_TO_FSBT(mp, space * XFS_सूची2_SPACE_SIZE);
	count = args->geo->fsbcount;

	error = xfs_da_grow_inode_पूर्णांक(args, &bno, count);
	अगर (error)
		वापस error;

	*dbp = xfs_dir2_da_to_db(args->geo, (xfs_dablk_t)bno);

	/*
	 * Update file's size अगर this is the data space and it grew.
	 */
	अगर (space == XFS_सूची2_DATA_SPACE) अणु
		xfs_fमाप_प्रकार	size;		/* directory file (data) size */

		size = XFS_FSB_TO_B(mp, bno + count);
		अगर (size > dp->i_disk_size) अणु
			dp->i_disk_size = size;
			xfs_trans_log_inode(args->trans, dp, XFS_ILOG_CORE);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * See अगर the directory is a single-block क्रमm directory.
 */
पूर्णांक
xfs_dir2_isblock(
	काष्ठा xfs_da_args	*args,
	पूर्णांक			*vp)	/* out: 1 is block, 0 is not block */
अणु
	xfs_fileoff_t		last;	/* last file offset */
	पूर्णांक			rval;

	अगर ((rval = xfs_bmap_last_offset(args->dp, &last, XFS_DATA_FORK)))
		वापस rval;
	rval = XFS_FSB_TO_B(args->dp->i_mount, last) == args->geo->blksize;
	अगर (XFS_IS_CORRUPT(args->dp->i_mount,
			   rval != 0 &&
			   args->dp->i_disk_size != args->geo->blksize))
		वापस -EFSCORRUPTED;
	*vp = rval;
	वापस 0;
पूर्ण

/*
 * See अगर the directory is a single-leaf क्रमm directory.
 */
पूर्णांक
xfs_dir2_isleaf(
	काष्ठा xfs_da_args	*args,
	पूर्णांक			*vp)	/* out: 1 is block, 0 is not block */
अणु
	xfs_fileoff_t		last;	/* last file offset */
	पूर्णांक			rval;

	अगर ((rval = xfs_bmap_last_offset(args->dp, &last, XFS_DATA_FORK)))
		वापस rval;
	*vp = last == args->geo->leafblk + args->geo->fsbcount;
	वापस 0;
पूर्ण

/*
 * Remove the given block from the directory.
 * This routine is used क्रम data and मुक्त blocks, leaf/node are करोne
 * by xfs_da_shrink_inode.
 */
पूर्णांक
xfs_dir2_shrink_inode(
	काष्ठा xfs_da_args	*args,
	xfs_dir2_db_t		db,
	काष्ठा xfs_buf		*bp)
अणु
	xfs_fileoff_t		bno;		/* directory file offset */
	xfs_dablk_t		da;		/* directory file offset */
	पूर्णांक			करोne;		/* bunmap is finished */
	काष्ठा xfs_inode	*dp;
	पूर्णांक			error;
	काष्ठा xfs_mount	*mp;
	काष्ठा xfs_trans	*tp;

	trace_xfs_dir2_shrink_inode(args, db);

	dp = args->dp;
	mp = dp->i_mount;
	tp = args->trans;
	da = xfs_dir2_db_to_da(args->geo, db);

	/* Unmap the fsblock(s). */
	error = xfs_bunmapi(tp, dp, da, args->geo->fsbcount, 0, 0, &करोne);
	अगर (error) अणु
		/*
		 * ENOSPC actually can happen अगर we're in a हटाओname with no
		 * space reservation, and the resulting block removal would
		 * cause a bmap btree split or conversion from extents to btree.
		 * This can only happen क्रम un-fragmented directory blocks,
		 * since you need to be punching out the middle of an extent.
		 * In this हाल we need to leave the block in the file, and not
		 * binval it.  So the block has to be in a consistent empty
		 * state and appropriately logged.  We करोn't मुक्त up the buffer,
		 * the caller can tell it hasn't happened since it got an error
		 * back.
		 */
		वापस error;
	पूर्ण
	ASSERT(करोne);
	/*
	 * Invalidate the buffer from the transaction.
	 */
	xfs_trans_binval(tp, bp);
	/*
	 * If it's not a data block, we're करोne.
	 */
	अगर (db >= xfs_dir2_byte_to_db(args->geo, XFS_सूची2_LEAF_OFFSET))
		वापस 0;
	/*
	 * If the block isn't the last one in the directory, we're करोne.
	 */
	अगर (dp->i_disk_size > xfs_dir2_db_off_to_byte(args->geo, db + 1, 0))
		वापस 0;
	bno = da;
	अगर ((error = xfs_bmap_last_beक्रमe(tp, dp, &bno, XFS_DATA_FORK))) अणु
		/*
		 * This can't really happen unless there's kernel corruption.
		 */
		वापस error;
	पूर्ण
	अगर (db == args->geo->datablk)
		ASSERT(bno == 0);
	अन्यथा
		ASSERT(bno > 0);
	/*
	 * Set the size to the new last block.
	 */
	dp->i_disk_size = XFS_FSB_TO_B(mp, bno);
	xfs_trans_log_inode(tp, dp, XFS_ILOG_CORE);
	वापस 0;
पूर्ण

/* Returns true अगर the directory entry name is valid. */
bool
xfs_dir2_namecheck(
	स्थिर व्योम	*name,
	माप_प्रकार		length)
अणु
	/*
	 * MAXNAMELEN includes the trailing null, but (name/length) leave it
	 * out, so use >= क्रम the length check.
	 */
	अगर (length >= MAXNAMELEN)
		वापस false;

	/* There shouldn't be any slashes or nulls here */
	वापस !स_प्रथम(name, '/', length) && !स_प्रथम(name, 0, length);
पूर्ण

xfs_dahash_t
xfs_dir2_hashname(
	काष्ठा xfs_mount	*mp,
	काष्ठा xfs_name		*name)
अणु
	अगर (unlikely(xfs_sb_version_hasasciici(&mp->m_sb)))
		वापस xfs_ascii_ci_hashname(name);
	वापस xfs_da_hashname(name->name, name->len);
पूर्ण

क्रमागत xfs_dacmp
xfs_dir2_compname(
	काष्ठा xfs_da_args	*args,
	स्थिर अचिन्हित अक्षर	*name,
	पूर्णांक			len)
अणु
	अगर (unlikely(xfs_sb_version_hasasciici(&args->dp->i_mount->m_sb)))
		वापस xfs_ascii_ci_compname(args, name, len);
	वापस xfs_da_compname(args, name, len);
पूर्ण
