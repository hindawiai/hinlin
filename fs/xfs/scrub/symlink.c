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
#समावेश "xfs_inode.h"
#समावेश "xfs_symlink.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"

/* Set us up to scrub a symbolic link. */
पूर्णांक
xchk_setup_symlink(
	काष्ठा xfs_scrub	*sc)
अणु
	/* Allocate the buffer without the inode lock held. */
	sc->buf = kvzalloc(XFS_SYMLINK_MAXLEN + 1, GFP_KERNEL);
	अगर (!sc->buf)
		वापस -ENOMEM;

	वापस xchk_setup_inode_contents(sc, 0);
पूर्ण

/* Symbolic links. */

पूर्णांक
xchk_symlink(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_inode	*ip = sc->ip;
	काष्ठा xfs_अगरork	*अगरp;
	loff_t			len;
	पूर्णांक			error = 0;

	अगर (!S_ISLNK(VFS_I(ip)->i_mode))
		वापस -ENOENT;
	अगरp = XFS_IFORK_PTR(ip, XFS_DATA_FORK);
	len = ip->i_disk_size;

	/* Plausible size? */
	अगर (len > XFS_SYMLINK_MAXLEN || len <= 0) अणु
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		जाओ out;
	पूर्ण

	/* Inline symlink? */
	अगर (अगरp->अगर_क्रमmat == XFS_DINODE_FMT_LOCAL) अणु
		अगर (len > XFS_IFORK_DSIZE(ip) ||
		    len > strnlen(अगरp->अगर_u1.अगर_data, XFS_IFORK_DSIZE(ip)))
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		जाओ out;
	पूर्ण

	/* Remote symlink; must पढ़ो the contents. */
	error = xfs_पढ़ोlink_bmap_ilocked(sc->ip, sc->buf);
	अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, 0, &error))
		जाओ out;
	अगर (strnlen(sc->buf, XFS_SYMLINK_MAXLEN) < len)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
out:
	वापस error;
पूर्ण
