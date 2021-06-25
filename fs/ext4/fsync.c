<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/ext4/fsync.c
 *
 *  Copyright (C) 1993  Stephen Tweedie (sct@redhat.com)
 *  from
 *  Copyright (C) 1992  Remy Card (card@masi.ibp.fr)
 *                      Laborम_से_पre MASI - Institut Blaise Pascal
 *                      Universite Pierre et Marie Curie (Paris VI)
 *  from
 *  linux/fs/minix/truncate.c   Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext4fs fsync primitive
 *
 *  Big-endian to little-endian byte-swapping/biपंचांगaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 *
 *  Removed unnecessary code duplication क्रम little endian machines
 *  and excessive __अंतरभूत__s.
 *        Andi Kleen, 1997
 *
 * Major simplications and cleanup - we only need to करो the metadata, because
 * we can depend on generic_block_fdatasync() to sync the data blocks.
 */

#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/sched.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>

#समावेश "ext4.h"
#समावेश "ext4_jbd2.h"

#समावेश <trace/events/ext4.h>

/*
 * If we're not journaling and this is a just-created file, we have to
 * sync our parent directory (अगर it was freshly created) since
 * otherwise it will only be written by ग_लिखोback, leaving a huge
 * winकरोw during which a crash may lose the file.  This may apply क्रम
 * the parent directory's parent as well, and so on recursively, अगर
 * they are also freshly created.
 */
अटल पूर्णांक ext4_sync_parent(काष्ठा inode *inode)
अणु
	काष्ठा dentry *dentry, *next;
	पूर्णांक ret = 0;

	अगर (!ext4_test_inode_state(inode, EXT4_STATE_NEWENTRY))
		वापस 0;
	dentry = d_find_any_alias(inode);
	अगर (!dentry)
		वापस 0;
	जबतक (ext4_test_inode_state(inode, EXT4_STATE_NEWENTRY)) अणु
		ext4_clear_inode_state(inode, EXT4_STATE_NEWENTRY);

		next = dget_parent(dentry);
		dput(dentry);
		dentry = next;
		inode = dentry->d_inode;

		/*
		 * The directory inode may have gone through सूची_हटाओ by now. But
		 * the inode itself and its blocks are still allocated (we hold
		 * a reference to the inode via its dentry), so it didn't go
		 * through ext4_evict_inode()) and so we are safe to flush
		 * metadata blocks and the inode.
		 */
		ret = sync_mapping_buffers(inode->i_mapping);
		अगर (ret)
			अवरोध;
		ret = sync_inode_metadata(inode, 1);
		अगर (ret)
			अवरोध;
	पूर्ण
	dput(dentry);
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_fsync_nojournal(काष्ठा inode *inode, bool datasync,
				bool *needs_barrier)
अणु
	पूर्णांक ret, err;

	ret = sync_mapping_buffers(inode->i_mapping);
	अगर (!(inode->i_state & I_सूचीTY_ALL))
		वापस ret;
	अगर (datasync && !(inode->i_state & I_सूचीTY_DATASYNC))
		वापस ret;

	err = sync_inode_metadata(inode, 1);
	अगर (!ret)
		ret = err;

	अगर (!ret)
		ret = ext4_sync_parent(inode);
	अगर (test_opt(inode->i_sb, BARRIER))
		*needs_barrier = true;

	वापस ret;
पूर्ण

अटल पूर्णांक ext4_fsync_journal(काष्ठा inode *inode, bool datasync,
			     bool *needs_barrier)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	journal_t *journal = EXT4_SB(inode->i_sb)->s_journal;
	tid_t commit_tid = datasync ? ei->i_datasync_tid : ei->i_sync_tid;

	अगर (journal->j_flags & JBD2_BARRIER &&
	    !jbd2_trans_will_send_data_barrier(journal, commit_tid))
		*needs_barrier = true;

	वापस ext4_fc_commit(journal, commit_tid);
पूर्ण

/*
 * akpm: A new design क्रम ext4_sync_file().
 *
 * This is only called from sys_fsync(), sys_fdatasync() and sys_msync().
 * There cannot be a transaction खोलो by this task.
 * Another task could have dirtied this inode.  Its data can be in any
 * state in the journalling प्रणाली.
 *
 * What we करो is just kick off a commit and रुको on it.  This will snapshot the
 * inode to disk.
 */
पूर्णांक ext4_sync_file(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	पूर्णांक ret = 0, err;
	bool needs_barrier = false;
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	अगर (unlikely(ext4_क्रमced_shutकरोwn(sbi)))
		वापस -EIO;

	ASSERT(ext4_journal_current_handle() == शून्य);

	trace_ext4_sync_file_enter(file, datasync);

	अगर (sb_rकरोnly(inode->i_sb)) अणु
		/* Make sure that we पढ़ो updated s_mount_flags value */
		smp_rmb();
		अगर (ext4_test_mount_flag(inode->i_sb, EXT4_MF_FS_ABORTED))
			ret = -EROFS;
		जाओ out;
	पूर्ण

	ret = file_ग_लिखो_and_रुको_range(file, start, end);
	अगर (ret)
		जाओ out;

	/*
	 * data=ग_लिखोback,ordered:
	 *  The caller's filemap_fdataग_लिखो()/रुको will sync the data.
	 *  Metadata is in the journal, we रुको क्रम proper transaction to
	 *  commit here.
	 *
	 * data=journal:
	 *  filemap_fdataग_लिखो won't करो anything (the buffers are clean).
	 *  ext4_क्रमce_commit will ग_लिखो the file data पूर्णांकo the journal and
	 *  will रुको on that.
	 *  filemap_fdataरुको() will encounter a ton of newly-dirtied pages
	 *  (they were dirtied by commit).  But that's OK - the blocks are
	 *  safe in-journal, which is all fsync() needs to ensure.
	 */
	अगर (!sbi->s_journal)
		ret = ext4_fsync_nojournal(inode, datasync, &needs_barrier);
	अन्यथा अगर (ext4_should_journal_data(inode))
		ret = ext4_क्रमce_commit(inode->i_sb);
	अन्यथा
		ret = ext4_fsync_journal(inode, datasync, &needs_barrier);

	अगर (needs_barrier) अणु
		err = blkdev_issue_flush(inode->i_sb->s_bdev);
		अगर (!ret)
			ret = err;
	पूर्ण
out:
	err = file_check_and_advance_wb_err(file);
	अगर (ret == 0)
		ret = err;
	trace_ext4_sync_file_निकास(inode, ret);
	वापस ret;
पूर्ण
