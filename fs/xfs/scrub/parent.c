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
#समावेश "xfs_icache.h"
#समावेश "xfs_dir2.h"
#समावेश "xfs_dir2_priv.h"
#समावेश "scrub/scrub.h"
#समावेश "scrub/common.h"

/* Set us up to scrub parents. */
पूर्णांक
xchk_setup_parent(
	काष्ठा xfs_scrub	*sc)
अणु
	वापस xchk_setup_inode_contents(sc, 0);
पूर्ण

/* Parent poपूर्णांकers */

/* Look क्रम an entry in a parent poपूर्णांकing to this inode. */

काष्ठा xchk_parent_ctx अणु
	काष्ठा dir_context	dc;
	काष्ठा xfs_scrub	*sc;
	xfs_ino_t		ino;
	xfs_nlink_t		nlink;
	bool			cancelled;
पूर्ण;

/* Look क्रम a single entry in a directory poपूर्णांकing to an inode. */
STATIC पूर्णांक
xchk_parent_actor(
	काष्ठा dir_context	*dc,
	स्थिर अक्षर		*name,
	पूर्णांक			namelen,
	loff_t			pos,
	u64			ino,
	अचिन्हित		type)
अणु
	काष्ठा xchk_parent_ctx	*spc;
	पूर्णांक			error = 0;

	spc = container_of(dc, काष्ठा xchk_parent_ctx, dc);
	अगर (spc->ino == ino)
		spc->nlink++;

	/*
	 * If we're facing a fatal संकेत, bail out.  Store the cancellation
	 * status separately because the VFS सूची_पढ़ो code squashes error codes
	 * पूर्णांकo लघु directory पढ़ोs.
	 */
	अगर (xchk_should_terminate(spc->sc, &error))
		spc->cancelled = true;

	वापस error;
पूर्ण

/* Count the number of dentries in the parent dir that poपूर्णांक to this inode. */
STATIC पूर्णांक
xchk_parent_count_parent_dentries(
	काष्ठा xfs_scrub	*sc,
	काष्ठा xfs_inode	*parent,
	xfs_nlink_t		*nlink)
अणु
	काष्ठा xchk_parent_ctx	spc = अणु
		.dc.actor	= xchk_parent_actor,
		.ino		= sc->ip->i_ino,
		.sc		= sc,
	पूर्ण;
	माप_प्रकार			bufsize;
	loff_t			oldpos;
	uपूर्णांक			lock_mode;
	पूर्णांक			error = 0;

	/*
	 * If there are any blocks, पढ़ो-ahead block 0 as we're almost
	 * certain to have the next operation be a पढ़ो there.  This is
	 * how we guarantee that the parent's extent map has been loaded,
	 * अगर there is one.
	 */
	lock_mode = xfs_ilock_data_map_shared(parent);
	अगर (parent->i_df.अगर_nextents > 0)
		error = xfs_dir3_data_पढ़ोahead(parent, 0, 0);
	xfs_iunlock(parent, lock_mode);
	अगर (error)
		वापस error;

	/*
	 * Iterate the parent dir to confirm that there is
	 * exactly one entry poपूर्णांकing back to the inode being
	 * scanned.
	 */
	bufsize = (माप_प्रकार)min_t(loff_t, XFS_READसूची_बफ_मानE,
			parent->i_disk_size);
	oldpos = 0;
	जबतक (true) अणु
		error = xfs_सूची_पढ़ो(sc->tp, parent, &spc.dc, bufsize);
		अगर (error)
			जाओ out;
		अगर (spc.cancelled) अणु
			error = -EAGAIN;
			जाओ out;
		पूर्ण
		अगर (oldpos == spc.dc.pos)
			अवरोध;
		oldpos = spc.dc.pos;
	पूर्ण
	*nlink = spc.nlink;
out:
	वापस error;
पूर्ण

/*
 * Given the inode number of the alleged parent of the inode being
 * scrubbed, try to validate that the parent has exactly one directory
 * entry poपूर्णांकing back to the inode being scrubbed.
 */
STATIC पूर्णांक
xchk_parent_validate(
	काष्ठा xfs_scrub	*sc,
	xfs_ino_t		dnum,
	bool			*try_again)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	काष्ठा xfs_inode	*dp = शून्य;
	xfs_nlink_t		expected_nlink;
	xfs_nlink_t		nlink;
	पूर्णांक			error = 0;

	*try_again = false;

	अगर (sc->sm->sm_flags & XFS_SCRUB_OFLAG_CORRUPT)
		जाओ out;

	/* '..' must not poपूर्णांक to ourselves. */
	अगर (sc->ip->i_ino == dnum) अणु
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		जाओ out;
	पूर्ण

	/*
	 * If we're an unlinked directory, the parent /won't/ have a link
	 * to us.  Otherwise, it should have one link.
	 */
	expected_nlink = VFS_I(sc->ip)->i_nlink == 0 ? 0 : 1;

	/*
	 * Grab this parent inode.  We release the inode beक्रमe we
	 * cancel the scrub transaction.  Since we're don't know a
	 * priori that releasing the inode won't trigger eofblocks
	 * cleanup (which allocates what would be a nested transaction)
	 * अगर the parent poपूर्णांकer erroneously poपूर्णांकs to a file, we
	 * can't use DONTCACHE here because DONTCACHE inodes can trigger
	 * immediate inactive cleanup of the inode.
	 *
	 * If _iget वापसs -EINVAL or -ENOENT then the parent inode number is
	 * garbage and the directory is corrupt.  If the _iget वापसs
	 * -EFSCORRUPTED or -EFSBADCRC then the parent is corrupt which is a
	 *  cross referencing error.  Any other error is an operational error.
	 */
	error = xfs_iget(mp, sc->tp, dnum, XFS_IGET_UNTRUSTED, 0, &dp);
	अगर (error == -EINVAL || error == -ENOENT) अणु
		error = -EFSCORRUPTED;
		xchk_fblock_process_error(sc, XFS_DATA_FORK, 0, &error);
		जाओ out;
	पूर्ण
	अगर (!xchk_fblock_xref_process_error(sc, XFS_DATA_FORK, 0, &error))
		जाओ out;
	अगर (dp == sc->ip || !S_ISसूची(VFS_I(dp)->i_mode)) अणु
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		जाओ out_rele;
	पूर्ण

	/*
	 * We prefer to keep the inode locked जबतक we lock and search
	 * its alleged parent क्रम a क्रमward reference.  If we can grab
	 * the iolock, validate the poपूर्णांकers and we're करोne.  We must
	 * use noरुको here to aव्योम an ABBA deadlock on the parent and
	 * the child inodes.
	 */
	अगर (xfs_ilock_noरुको(dp, XFS_IOLOCK_SHARED)) अणु
		error = xchk_parent_count_parent_dentries(sc, dp, &nlink);
		अगर (!xchk_fblock_xref_process_error(sc, XFS_DATA_FORK, 0,
				&error))
			जाओ out_unlock;
		अगर (nlink != expected_nlink)
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		जाओ out_unlock;
	पूर्ण

	/*
	 * The game changes अगर we get here.  We failed to lock the parent,
	 * so we're going to try to verअगरy both poपूर्णांकers जबतक only holding
	 * one lock so as to aव्योम deadlocking with something that's actually
	 * trying to traverse करोwn the directory tree.
	 */
	xfs_iunlock(sc->ip, sc->ilock_flags);
	sc->ilock_flags = 0;
	error = xchk_ilock_inverted(dp, XFS_IOLOCK_SHARED);
	अगर (error)
		जाओ out_rele;

	/* Go looking क्रम our dentry. */
	error = xchk_parent_count_parent_dentries(sc, dp, &nlink);
	अगर (!xchk_fblock_xref_process_error(sc, XFS_DATA_FORK, 0, &error))
		जाओ out_unlock;

	/* Drop the parent lock, relock this inode. */
	xfs_iunlock(dp, XFS_IOLOCK_SHARED);
	error = xchk_ilock_inverted(sc->ip, XFS_IOLOCK_EXCL);
	अगर (error)
		जाओ out_rele;
	sc->ilock_flags = XFS_IOLOCK_EXCL;

	/*
	 * If we're an unlinked directory, the parent /won't/ have a link
	 * to us.  Otherwise, it should have one link.  We have to re-set
	 * it here because we dropped the lock on sc->ip.
	 */
	expected_nlink = VFS_I(sc->ip)->i_nlink == 0 ? 0 : 1;

	/* Look up '..' to see अगर the inode changed. */
	error = xfs_dir_lookup(sc->tp, sc->ip, &xfs_name_करोtकरोt, &dnum, शून्य);
	अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, 0, &error))
		जाओ out_rele;

	/* Drat, parent changed.  Try again! */
	अगर (dnum != dp->i_ino) अणु
		xfs_irele(dp);
		*try_again = true;
		वापस 0;
	पूर्ण
	xfs_irele(dp);

	/*
	 * '..' didn't change, so check that there was only one entry
	 * क्रम us in the parent.
	 */
	अगर (nlink != expected_nlink)
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
	वापस error;

out_unlock:
	xfs_iunlock(dp, XFS_IOLOCK_SHARED);
out_rele:
	xfs_irele(dp);
out:
	वापस error;
पूर्ण

/* Scrub a parent poपूर्णांकer. */
पूर्णांक
xchk_parent(
	काष्ठा xfs_scrub	*sc)
अणु
	काष्ठा xfs_mount	*mp = sc->mp;
	xfs_ino_t		dnum;
	bool			try_again;
	पूर्णांक			tries = 0;
	पूर्णांक			error = 0;

	/*
	 * If we're a directory, check that the '..' link poपूर्णांकs up to
	 * a directory that has one entry poपूर्णांकing to us.
	 */
	अगर (!S_ISसूची(VFS_I(sc->ip)->i_mode))
		वापस -ENOENT;

	/* We're not a special inode, are we? */
	अगर (!xfs_verअगरy_dir_ino(mp, sc->ip->i_ino)) अणु
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		जाओ out;
	पूर्ण

	/*
	 * The VFS grअसल a पढ़ो or ग_लिखो lock via i_rwsem beक्रमe it पढ़ोs
	 * or ग_लिखोs to a directory.  If we've gotten this far we've
	 * alपढ़ोy obtained IOLOCK_EXCL, which (since 4.10) is the same as
	 * getting a ग_लिखो lock on i_rwsem.  Thereक्रमe, it is safe क्रम us
	 * to drop the ILOCK here in order to करो directory lookups.
	 */
	sc->ilock_flags &= ~(XFS_ILOCK_EXCL | XFS_MMAPLOCK_EXCL);
	xfs_iunlock(sc->ip, XFS_ILOCK_EXCL | XFS_MMAPLOCK_EXCL);

	/* Look up '..' */
	error = xfs_dir_lookup(sc->tp, sc->ip, &xfs_name_करोtकरोt, &dnum, शून्य);
	अगर (!xchk_fblock_process_error(sc, XFS_DATA_FORK, 0, &error))
		जाओ out;
	अगर (!xfs_verअगरy_dir_ino(mp, dnum)) अणु
		xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		जाओ out;
	पूर्ण

	/* Is this the root dir?  Then '..' must poपूर्णांक to itself. */
	अगर (sc->ip == mp->m_rootip) अणु
		अगर (sc->ip->i_ino != mp->m_sb.sb_rootino ||
		    sc->ip->i_ino != dnum)
			xchk_fblock_set_corrupt(sc, XFS_DATA_FORK, 0);
		जाओ out;
	पूर्ण

	करो अणु
		error = xchk_parent_validate(sc, dnum, &try_again);
		अगर (error)
			जाओ out;
	पूर्ण जबतक (try_again && ++tries < 20);

	/*
	 * We gave it our best shot but failed, so mark this scrub
	 * incomplete.  Userspace can decide अगर it wants to try again.
	 */
	अगर (try_again && tries == 20)
		xchk_set_incomplete(sc);
out:
	/*
	 * If we failed to lock the parent inode even after a retry, just mark
	 * this scrub incomplete and वापस.
	 */
	अगर ((sc->flags & XCHK_TRY_HARDER) && error == -EDEADLOCK) अणु
		error = 0;
		xchk_set_incomplete(sc);
	पूर्ण
	वापस error;
पूर्ण
