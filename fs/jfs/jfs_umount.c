<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 */

/*
 *	jfs_umount.c
 *
 * note: file प्रणाली in transition to aggregate/fileset:
 * (ref. jfs_mount.c)
 *
 * file प्रणाली unmount is पूर्णांकerpreted as mount of the single/only
 * fileset in the aggregate and, अगर unmount of the last fileset,
 * as unmount of the aggerate;
 */

#समावेश <linux/fs.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_filsys.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_imap.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_debug.h"

/*
 * NAME:	jfs_umount(vfsp, flags, crp)
 *
 * FUNCTION:	vfs_umount()
 *
 * PARAMETERS:	vfsp	- भव file प्रणाली poपूर्णांकer
 *		flags	- unmount क्रम shutकरोwn
 *		crp	- credential
 *
 * RETURN :	EBUSY	- device has खोलो files
 */
पूर्णांक jfs_umount(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा inode *ipbmap = sbi->ipbmap;
	काष्ठा inode *ipimap = sbi->ipimap;
	काष्ठा inode *ipaimap = sbi->ipaimap;
	काष्ठा inode *ipaimap2 = sbi->ipaimap2;
	काष्ठा jfs_log *log;
	पूर्णांक rc = 0;

	jfs_info("UnMount JFS: sb:0x%p", sb);

	/*
	 *	update superblock and बंद log
	 *
	 * अगर mounted पढ़ो-ग_लिखो and log based recovery was enabled
	 */
	अगर ((log = sbi->log))
		/*
		 * Wait क्रम outstanding transactions to be written to log:
		 */
		jfs_flush_journal(log, 2);

	/*
	 * बंद fileset inode allocation map (aka fileset inode)
	 */
	diUnmount(ipimap, 0);

	diFreeSpecial(ipimap);
	sbi->ipimap = शून्य;

	/*
	 * बंद secondary aggregate inode allocation map
	 */
	ipaimap2 = sbi->ipaimap2;
	अगर (ipaimap2) अणु
		diUnmount(ipaimap2, 0);
		diFreeSpecial(ipaimap2);
		sbi->ipaimap2 = शून्य;
	पूर्ण

	/*
	 * बंद aggregate inode allocation map
	 */
	ipaimap = sbi->ipaimap;
	diUnmount(ipaimap, 0);
	diFreeSpecial(ipaimap);
	sbi->ipaimap = शून्य;

	/*
	 * बंद aggregate block allocation map
	 */
	dbUnmount(ipbmap, 0);

	diFreeSpecial(ipbmap);
	sbi->ipimap = शून्य;

	/*
	 * Make sure all metadata makes it to disk beक्रमe we mark
	 * the superblock as clean
	 */
	filemap_ग_लिखो_and_रुको(sbi->direct_inode->i_mapping);

	/*
	 * ensure all file प्रणाली file pages are propagated to their
	 * home blocks on disk (and their in-memory buffer pages are
	 * invalidated) BEFORE updating file प्रणाली superblock state
	 * (to signअगरy file प्रणाली is unmounted cleanly, and thus in
	 * consistent state) and log superblock active file प्रणाली
	 * list (to signअगरy skip logreकरो()).
	 */
	अगर (log) अणु		/* log = शून्य अगर पढ़ो-only mount */
		updateSuper(sb, FM_CLEAN);

		/*
		 * बंद log:
		 *
		 * हटाओ file प्रणाली from log active file प्रणाली list.
		 */
		rc = lmLogClose(sb);
	पूर्ण
	jfs_info("UnMount JFS Complete: rc = %d", rc);
	वापस rc;
पूर्ण


पूर्णांक jfs_umount_rw(काष्ठा super_block *sb)
अणु
	काष्ठा jfs_sb_info *sbi = JFS_SBI(sb);
	काष्ठा jfs_log *log = sbi->log;

	अगर (!log)
		वापस 0;

	/*
	 * बंद log:
	 *
	 * हटाओ file प्रणाली from log active file प्रणाली list.
	 */
	jfs_flush_journal(log, 2);

	/*
	 * Make sure all metadata makes it to disk
	 */
	dbSync(sbi->ipbmap);
	diSync(sbi->ipimap);

	/*
	 * Note that we have to करो this even अगर sync_blockdev() will
	 * करो exactly the same a few inकाष्ठाions later:  We can't
	 * mark the superblock clean beक्रमe everything is flushed to
	 * disk.
	 */
	filemap_ग_लिखो_and_रुको(sbi->direct_inode->i_mapping);

	updateSuper(sb, FM_CLEAN);

	वापस lmLogClose(sb);
पूर्ण
