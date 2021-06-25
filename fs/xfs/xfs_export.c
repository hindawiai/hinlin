<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2004-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 */
#समावेश "xfs.h"
#समावेश "xfs_shared.h"
#समावेश "xfs_format.h"
#समावेश "xfs_log_format.h"
#समावेश "xfs_trans_resv.h"
#समावेश "xfs_mount.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_export.h"
#समावेश "xfs_inode.h"
#समावेश "xfs_trans.h"
#समावेश "xfs_inode_item.h"
#समावेश "xfs_icache.h"
#समावेश "xfs_pnfs.h"

/*
 * Note that we only accept fileids which are दीर्घ enough rather than allow
 * the parent generation number to शेष to zero.  XFS considers zero a
 * valid generation number not an invalid/wildcard value.
 */
अटल पूर्णांक xfs_fileid_length(पूर्णांक fileid_type)
अणु
	चयन (fileid_type) अणु
	हाल खाताID_INO32_GEN:
		वापस 2;
	हाल खाताID_INO32_GEN_PARENT:
		वापस 4;
	हाल खाताID_INO32_GEN | XFS_खाताID_TYPE_64FLAG:
		वापस 3;
	हाल खाताID_INO32_GEN_PARENT | XFS_खाताID_TYPE_64FLAG:
		वापस 6;
	पूर्ण
	वापस खाताID_INVALID;
पूर्ण

STATIC पूर्णांक
xfs_fs_encode_fh(
	काष्ठा inode	*inode,
	__u32		*fh,
	पूर्णांक		*max_len,
	काष्ठा inode	*parent)
अणु
	काष्ठा fid		*fid = (काष्ठा fid *)fh;
	काष्ठा xfs_fid64	*fid64 = (काष्ठा xfs_fid64 *)fh;
	पूर्णांक			fileid_type;
	पूर्णांक			len;

	/* Directories करोn't need their parent encoded, they have ".." */
	अगर (!parent)
		fileid_type = खाताID_INO32_GEN;
	अन्यथा
		fileid_type = खाताID_INO32_GEN_PARENT;

	/*
	 * If the fileप्रणाली may contain 64bit inode numbers, we need
	 * to use larger file handles that can represent them.
	 *
	 * While we only allocate inodes that करो not fit पूर्णांकo 32 bits any
	 * large enough fileप्रणाली may contain them, thus the slightly
	 * confusing looking conditional below.
	 */
	अगर (!(XFS_M(inode->i_sb)->m_flags & XFS_MOUNT_SMALL_INUMS) ||
	    (XFS_M(inode->i_sb)->m_flags & XFS_MOUNT_32BITINODES))
		fileid_type |= XFS_खाताID_TYPE_64FLAG;

	/*
	 * Only encode अगर there is enough space given.  In practice
	 * this means we can't export a fileप्रणाली with 64bit inodes
	 * over NFSv2 with the subtree_check export option; the other
	 * seven combinations work.  The real answer is "don't use v2".
	 */
	len = xfs_fileid_length(fileid_type);
	अगर (*max_len < len) अणु
		*max_len = len;
		वापस खाताID_INVALID;
	पूर्ण
	*max_len = len;

	चयन (fileid_type) अणु
	हाल खाताID_INO32_GEN_PARENT:
		fid->i32.parent_ino = XFS_I(parent)->i_ino;
		fid->i32.parent_gen = parent->i_generation;
		/*FALLTHRU*/
	हाल खाताID_INO32_GEN:
		fid->i32.ino = XFS_I(inode)->i_ino;
		fid->i32.gen = inode->i_generation;
		अवरोध;
	हाल खाताID_INO32_GEN_PARENT | XFS_खाताID_TYPE_64FLAG:
		fid64->parent_ino = XFS_I(parent)->i_ino;
		fid64->parent_gen = parent->i_generation;
		/*FALLTHRU*/
	हाल खाताID_INO32_GEN | XFS_खाताID_TYPE_64FLAG:
		fid64->ino = XFS_I(inode)->i_ino;
		fid64->gen = inode->i_generation;
		अवरोध;
	पूर्ण

	वापस fileid_type;
पूर्ण

STATIC काष्ठा inode *
xfs_nfs_get_inode(
	काष्ठा super_block	*sb,
	u64			ino,
	u32			generation)
अणु
 	xfs_mount_t		*mp = XFS_M(sb);
	xfs_inode_t		*ip;
	पूर्णांक			error;

	/*
	 * NFS can someबार send requests क्रम ino 0.  Fail them gracefully.
	 */
	अगर (ino == 0)
		वापस ERR_PTR(-ESTALE);

	/*
	 * The XFS_IGET_UNTRUSTED means that an invalid inode number is just
	 * fine and not an indication of a corrupted fileप्रणाली as clients can
	 * send invalid file handles and we have to handle it gracefully..
	 */
	error = xfs_iget(mp, शून्य, ino, XFS_IGET_UNTRUSTED, 0, &ip);
	अगर (error) अणु

		/*
		 * EINVAL means the inode cluster करोesn't exist anymore.
		 * EFSCORRUPTED means the metadata poपूर्णांकing to the inode cluster
		 * or the inode cluster itself is corrupt.  This implies the
		 * filehandle is stale, so we should translate it here.
		 * We करोn't use ESTALE directly करोwn the chain to not
		 * confuse applications using bulkstat that expect EINVAL.
		 */
		चयन (error) अणु
		हाल -EINVAL:
		हाल -ENOENT:
		हाल -EFSCORRUPTED:
			error = -ESTALE;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		वापस ERR_PTR(error);
	पूर्ण

	अगर (VFS_I(ip)->i_generation != generation) अणु
		xfs_irele(ip);
		वापस ERR_PTR(-ESTALE);
	पूर्ण

	वापस VFS_I(ip);
पूर्ण

STATIC काष्ठा dentry *
xfs_fs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		 पूर्णांक fh_len, पूर्णांक fileid_type)
अणु
	काष्ठा xfs_fid64	*fid64 = (काष्ठा xfs_fid64 *)fid;
	काष्ठा inode		*inode = शून्य;

	अगर (fh_len < xfs_fileid_length(fileid_type))
		वापस शून्य;

	चयन (fileid_type) अणु
	हाल खाताID_INO32_GEN_PARENT:
	हाल खाताID_INO32_GEN:
		inode = xfs_nfs_get_inode(sb, fid->i32.ino, fid->i32.gen);
		अवरोध;
	हाल खाताID_INO32_GEN_PARENT | XFS_खाताID_TYPE_64FLAG:
	हाल खाताID_INO32_GEN | XFS_खाताID_TYPE_64FLAG:
		inode = xfs_nfs_get_inode(sb, fid64->ino, fid64->gen);
		अवरोध;
	पूर्ण

	वापस d_obtain_alias(inode);
पूर्ण

STATIC काष्ठा dentry *
xfs_fs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		 पूर्णांक fh_len, पूर्णांक fileid_type)
अणु
	काष्ठा xfs_fid64	*fid64 = (काष्ठा xfs_fid64 *)fid;
	काष्ठा inode		*inode = शून्य;

	अगर (fh_len < xfs_fileid_length(fileid_type))
		वापस शून्य;

	चयन (fileid_type) अणु
	हाल खाताID_INO32_GEN_PARENT:
		inode = xfs_nfs_get_inode(sb, fid->i32.parent_ino,
					      fid->i32.parent_gen);
		अवरोध;
	हाल खाताID_INO32_GEN_PARENT | XFS_खाताID_TYPE_64FLAG:
		inode = xfs_nfs_get_inode(sb, fid64->parent_ino,
					      fid64->parent_gen);
		अवरोध;
	पूर्ण

	वापस d_obtain_alias(inode);
पूर्ण

STATIC काष्ठा dentry *
xfs_fs_get_parent(
	काष्ठा dentry		*child)
अणु
	पूर्णांक			error;
	काष्ठा xfs_inode	*cip;

	error = xfs_lookup(XFS_I(d_inode(child)), &xfs_name_करोtकरोt, &cip, शून्य);
	अगर (unlikely(error))
		वापस ERR_PTR(error);

	वापस d_obtain_alias(VFS_I(cip));
पूर्ण

STATIC पूर्णांक
xfs_fs_nfs_commit_metadata(
	काष्ठा inode		*inode)
अणु
	वापस xfs_log_क्रमce_inode(XFS_I(inode));
पूर्ण

स्थिर काष्ठा export_operations xfs_export_operations = अणु
	.encode_fh		= xfs_fs_encode_fh,
	.fh_to_dentry		= xfs_fs_fh_to_dentry,
	.fh_to_parent		= xfs_fs_fh_to_parent,
	.get_parent		= xfs_fs_get_parent,
	.commit_metadata	= xfs_fs_nfs_commit_metadata,
#अगर_घोषित CONFIG_EXPORTFS_BLOCK_OPS
	.get_uuid		= xfs_fs_get_uuid,
	.map_blocks		= xfs_fs_map_blocks,
	.commit_blocks		= xfs_fs_commit_blocks,
#पूर्ण_अगर
पूर्ण;
