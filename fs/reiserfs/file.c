<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 */

#समावेश <linux/समय.स>
#समावेश "reiserfs.h"
#समावेश "acl.h"
#समावेश "xattr.h"
#समावेश <linux/uaccess.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/swap.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/quotaops.h>

/*
 * We pack the tails of files on file बंद, not at the समय they are written.
 * This implies an unnecessary copy of the tail and an unnecessary indirect item
 * insertion/balancing, क्रम files that are written in one ग_लिखो.
 * It aव्योमs unnecessary tail packings (balances) क्रम files that are written in
 * multiple ग_लिखोs and are small enough to have tails.
 *
 * file_release is called by the VFS layer when the file is बंदd.  If
 * this is the last खोलो file descriptor, and the file
 * small enough to have a tail, and the tail is currently in an
 * unक्रमmatted node, the tail is converted back पूर्णांकo a direct item.
 *
 * We use reiserfs_truncate_file to pack the tail, since it alपढ़ोy has
 * all the conditions coded.
 */
अटल पूर्णांक reiserfs_file_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु

	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक err;
	पूर्णांक jbegin_failure = 0;

	BUG_ON(!S_ISREG(inode->i_mode));

	अगर (!atomic_dec_and_mutex_lock(&REISERFS_I(inode)->खोलोers,
				       &REISERFS_I(inode)->tailpack))
		वापस 0;

	/* fast out क्रम when nothing needs to be करोne */
	अगर ((!(REISERFS_I(inode)->i_flags & i_pack_on_बंद_mask) ||
	     !tail_has_to_be_packed(inode)) &&
	    REISERFS_I(inode)->i_pपुनः_स्मृति_count <= 0) अणु
		mutex_unlock(&REISERFS_I(inode)->tailpack);
		वापस 0;
	पूर्ण

	reiserfs_ग_लिखो_lock(inode->i_sb);
	/*
	 * मुक्तing pपुनः_स्मृतिation only involves relogging blocks that
	 * are alपढ़ोy in the current transaction.  pपुनः_स्मृतिation माला_लो
	 * मुक्तd at the end of each transaction, so it is impossible क्रम
	 * us to log any additional blocks (including quota blocks)
	 */
	err = journal_begin(&th, inode->i_sb, 1);
	अगर (err) अणु
		/*
		 * uh oh, we can't allow the inode to go away जबतक there
		 * is still pपुनः_स्मृतिation blocks pending.  Try to join the
		 * पातed transaction
		 */
		jbegin_failure = err;
		err = journal_join_पात(&th, inode->i_sb);

		अगर (err) अणु
			/*
			 * hmpf, our choices here aren't good.  We can pin
			 * the inode which will disallow unmount from ever
			 * happening, we can करो nothing, which will corrupt
			 * अक्रमom memory on unmount, or we can क्रमcibly
			 * हटाओ the file from the pपुनः_स्मृतिation list, which
			 * will leak blocks on disk.  Lets pin the inode
			 * and let the admin know what is going on.
			 */
			igrab(inode);
			reiserfs_warning(inode->i_sb, "clm-9001",
					 "pinning inode %lu because the "
					 "preallocation can't be freed",
					 inode->i_ino);
			जाओ out;
		पूर्ण
	पूर्ण
	reiserfs_update_inode_transaction(inode);

#अगर_घोषित REISERFS_PREALLOCATE
	reiserfs_discard_pपुनः_स्मृति(&th, inode);
#पूर्ण_अगर
	err = journal_end(&th);

	/* copy back the error code from journal_begin */
	अगर (!err)
		err = jbegin_failure;

	अगर (!err &&
	    (REISERFS_I(inode)->i_flags & i_pack_on_बंद_mask) &&
	    tail_has_to_be_packed(inode)) अणु

		/*
		 * अगर regular file is released by last holder and it has been
		 * appended (we append by unक्रमmatted node only) or its direct
		 * item(s) had to be converted, then it may have to be
		 * indirect2direct converted
		 */
		err = reiserfs_truncate_file(inode, 0);
	पूर्ण
out:
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	mutex_unlock(&REISERFS_I(inode)->tailpack);
	वापस err;
पूर्ण

अटल पूर्णांक reiserfs_file_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err = dquot_file_खोलो(inode, file);

	/* somebody might be tailpacking on final बंद; रुको क्रम it */
        अगर (!atomic_inc_not_zero(&REISERFS_I(inode)->खोलोers)) अणु
		mutex_lock(&REISERFS_I(inode)->tailpack);
		atomic_inc(&REISERFS_I(inode)->खोलोers);
		mutex_unlock(&REISERFS_I(inode)->tailpack);
	पूर्ण
	वापस err;
पूर्ण

व्योम reiserfs_vfs_truncate_file(काष्ठा inode *inode)
अणु
	mutex_lock(&REISERFS_I(inode)->tailpack);
	reiserfs_truncate_file(inode, 1);
	mutex_unlock(&REISERFS_I(inode)->tailpack);
पूर्ण

/* Sync a reiserfs file. */

/*
 * FIXME: sync_mapping_buffers() never has anything to sync.  Can
 * be हटाओd...
 */

अटल पूर्णांक reiserfs_sync_file(काष्ठा file *filp, loff_t start, loff_t end,
			      पूर्णांक datasync)
अणु
	काष्ठा inode *inode = filp->f_mapping->host;
	पूर्णांक err;
	पूर्णांक barrier_करोne;

	err = file_ग_लिखो_and_रुको_range(filp, start, end);
	अगर (err)
		वापस err;

	inode_lock(inode);
	BUG_ON(!S_ISREG(inode->i_mode));
	err = sync_mapping_buffers(inode->i_mapping);
	reiserfs_ग_लिखो_lock(inode->i_sb);
	barrier_करोne = reiserfs_commit_क्रम_inode(inode);
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	अगर (barrier_करोne != 1 && reiserfs_barrier_flush(inode->i_sb))
		blkdev_issue_flush(inode->i_sb->s_bdev);
	inode_unlock(inode);
	अगर (barrier_करोne < 0)
		वापस barrier_करोne;
	वापस (err < 0) ? -EIO : 0;
पूर्ण

/* taken fs/buffer.c:__block_commit_ग_लिखो */
पूर्णांक reiserfs_commit_page(काष्ठा inode *inode, काष्ठा page *page,
			 अचिन्हित from, अचिन्हित to)
अणु
	अचिन्हित block_start, block_end;
	पूर्णांक partial = 0;
	अचिन्हित blocksize;
	काष्ठा buffer_head *bh, *head;
	अचिन्हित दीर्घ i_size_index = inode->i_size >> PAGE_SHIFT;
	पूर्णांक new;
	पूर्णांक logit = reiserfs_file_data_log(inode);
	काष्ठा super_block *s = inode->i_sb;
	पूर्णांक bh_per_page = PAGE_SIZE / s->s_blocksize;
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक ret = 0;

	th.t_trans_id = 0;
	blocksize = i_blocksize(inode);

	अगर (logit) अणु
		reiserfs_ग_लिखो_lock(s);
		ret = journal_begin(&th, s, bh_per_page + 1);
		अगर (ret)
			जाओ drop_ग_लिखो_lock;
		reiserfs_update_inode_transaction(inode);
	पूर्ण
	क्रम (bh = head = page_buffers(page), block_start = 0;
	     bh != head || !block_start;
	     block_start = block_end, bh = bh->b_this_page) अणु

		new = buffer_new(bh);
		clear_buffer_new(bh);
		block_end = block_start + blocksize;
		अगर (block_end <= from || block_start >= to) अणु
			अगर (!buffer_uptodate(bh))
				partial = 1;
		पूर्ण अन्यथा अणु
			set_buffer_uptodate(bh);
			अगर (logit) अणु
				reiserfs_prepare_क्रम_journal(s, bh, 1);
				journal_mark_dirty(&th, bh);
			पूर्ण अन्यथा अगर (!buffer_dirty(bh)) अणु
				mark_buffer_dirty(bh);
				/*
				 * करो data=ordered on any page past the end
				 * of file and any buffer marked BH_New.
				 */
				अगर (reiserfs_data_ordered(inode->i_sb) &&
				    (new || page->index >= i_size_index)) अणु
					reiserfs_add_ordered_list(inode, bh);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (logit) अणु
		ret = journal_end(&th);
drop_ग_लिखो_lock:
		reiserfs_ग_लिखो_unlock(s);
	पूर्ण
	/*
	 * If this is a partial ग_लिखो which happened to make all buffers
	 * uptodate then we can optimize away a bogus पढ़ोpage() क्रम
	 * the next पढ़ो(). Here we 'discover' whether the page went
	 * uptodate as a result of this (potentially partial) ग_लिखो.
	 */
	अगर (!partial)
		SetPageUptodate(page);
	वापस ret;
पूर्ण

स्थिर काष्ठा file_operations reiserfs_file_operations = अणु
	.unlocked_ioctl = reiserfs_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = reiserfs_compat_ioctl,
#पूर्ण_अगर
	.mmap = generic_file_mmap,
	.खोलो = reiserfs_file_खोलो,
	.release = reiserfs_file_release,
	.fsync = reiserfs_sync_file,
	.पढ़ो_iter = generic_file_पढ़ो_iter,
	.ग_लिखो_iter = generic_file_ग_लिखो_iter,
	.splice_पढ़ो = generic_file_splice_पढ़ो,
	.splice_ग_लिखो = iter_file_splice_ग_लिखो,
	.llseek = generic_file_llseek,
पूर्ण;

स्थिर काष्ठा inode_operations reiserfs_file_inode_operations = अणु
	.setattr = reiserfs_setattr,
	.listxattr = reiserfs_listxattr,
	.permission = reiserfs_permission,
	.get_acl = reiserfs_get_acl,
	.set_acl = reiserfs_set_acl,
	.fileattr_get = reiserfs_fileattr_get,
	.fileattr_set = reiserfs_fileattr_set,
पूर्ण;
