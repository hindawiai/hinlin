<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interface between ext4 and JBD
 */

#समावेश "ext4_jbd2.h"

#समावेश <trace/events/ext4.h>

पूर्णांक ext4_inode_journal_mode(काष्ठा inode *inode)
अणु
	अगर (EXT4_JOURNAL(inode) == शून्य)
		वापस EXT4_INODE_WRITEBACK_DATA_MODE;	/* ग_लिखोback */
	/* We करो not support data journalling with delayed allocation */
	अगर (!S_ISREG(inode->i_mode) ||
	    ext4_test_inode_flag(inode, EXT4_INODE_EA_INODE) ||
	    test_opt(inode->i_sb, DATA_FLAGS) == EXT4_MOUNT_JOURNAL_DATA ||
	    (ext4_test_inode_flag(inode, EXT4_INODE_JOURNAL_DATA) &&
	    !test_opt(inode->i_sb, DELALLOC))) अणु
		/* We करो not support data journalling क्रम encrypted data */
		अगर (S_ISREG(inode->i_mode) && IS_ENCRYPTED(inode))
			वापस EXT4_INODE_ORDERED_DATA_MODE;  /* ordered */
		वापस EXT4_INODE_JOURNAL_DATA_MODE;	/* journal data */
	पूर्ण
	अगर (test_opt(inode->i_sb, DATA_FLAGS) == EXT4_MOUNT_ORDERED_DATA)
		वापस EXT4_INODE_ORDERED_DATA_MODE;	/* ordered */
	अगर (test_opt(inode->i_sb, DATA_FLAGS) == EXT4_MOUNT_WRITEBACK_DATA)
		वापस EXT4_INODE_WRITEBACK_DATA_MODE;	/* ग_लिखोback */
	BUG();
पूर्ण

/* Just increment the non-poपूर्णांकer handle value */
अटल handle_t *ext4_get_nojournal(व्योम)
अणु
	handle_t *handle = current->journal_info;
	अचिन्हित दीर्घ ref_cnt = (अचिन्हित दीर्घ)handle;

	BUG_ON(ref_cnt >= EXT4_NOJOURNAL_MAX_REF_COUNT);

	ref_cnt++;
	handle = (handle_t *)ref_cnt;

	current->journal_info = handle;
	वापस handle;
पूर्ण


/* Decrement the non-poपूर्णांकer handle value */
अटल व्योम ext4_put_nojournal(handle_t *handle)
अणु
	अचिन्हित दीर्घ ref_cnt = (अचिन्हित दीर्घ)handle;

	BUG_ON(ref_cnt == 0);

	ref_cnt--;
	handle = (handle_t *)ref_cnt;

	current->journal_info = handle;
पूर्ण

/*
 * Wrappers क्रम jbd2_journal_start/end.
 */
अटल पूर्णांक ext4_journal_check_start(काष्ठा super_block *sb)
अणु
	journal_t *journal;

	might_sleep();

	अगर (unlikely(ext4_क्रमced_shutकरोwn(EXT4_SB(sb))))
		वापस -EIO;

	अगर (sb_rकरोnly(sb))
		वापस -EROFS;
	WARN_ON(sb->s_ग_लिखोrs.frozen == SB_FREEZE_COMPLETE);
	journal = EXT4_SB(sb)->s_journal;
	/*
	 * Special हाल here: अगर the journal has पातed behind our
	 * backs (eg. EIO in the commit thपढ़ो), then we still need to
	 * take the FS itself पढ़ोonly cleanly.
	 */
	अगर (journal && is_journal_पातed(journal)) अणु
		ext4_पात(sb, -journal->j_त्रुटि_सं, "Detected aborted journal");
		वापस -EROFS;
	पूर्ण
	वापस 0;
पूर्ण

handle_t *__ext4_journal_start_sb(काष्ठा super_block *sb, अचिन्हित पूर्णांक line,
				  पूर्णांक type, पूर्णांक blocks, पूर्णांक rsv_blocks,
				  पूर्णांक revoke_creds)
अणु
	journal_t *journal;
	पूर्णांक err;

	trace_ext4_journal_start(sb, blocks, rsv_blocks, revoke_creds,
				 _RET_IP_);
	err = ext4_journal_check_start(sb);
	अगर (err < 0)
		वापस ERR_PTR(err);

	journal = EXT4_SB(sb)->s_journal;
	अगर (!journal || (EXT4_SB(sb)->s_mount_state & EXT4_FC_REPLAY))
		वापस ext4_get_nojournal();
	वापस jbd2__journal_start(journal, blocks, rsv_blocks, revoke_creds,
				   GFP_NOFS, type, line);
पूर्ण

पूर्णांक __ext4_journal_stop(स्थिर अक्षर *where, अचिन्हित पूर्णांक line, handle_t *handle)
अणु
	काष्ठा super_block *sb;
	पूर्णांक err;
	पूर्णांक rc;

	अगर (!ext4_handle_valid(handle)) अणु
		ext4_put_nojournal(handle);
		वापस 0;
	पूर्ण

	err = handle->h_err;
	अगर (!handle->h_transaction) अणु
		rc = jbd2_journal_stop(handle);
		वापस err ? err : rc;
	पूर्ण

	sb = handle->h_transaction->t_journal->j_निजी;
	rc = jbd2_journal_stop(handle);

	अगर (!err)
		err = rc;
	अगर (err)
		__ext4_std_error(sb, where, line, err);
	वापस err;
पूर्ण

handle_t *__ext4_journal_start_reserved(handle_t *handle, अचिन्हित पूर्णांक line,
					पूर्णांक type)
अणु
	काष्ठा super_block *sb;
	पूर्णांक err;

	अगर (!ext4_handle_valid(handle))
		वापस ext4_get_nojournal();

	sb = handle->h_journal->j_निजी;
	trace_ext4_journal_start_reserved(sb,
				jbd2_handle_buffer_credits(handle), _RET_IP_);
	err = ext4_journal_check_start(sb);
	अगर (err < 0) अणु
		jbd2_journal_मुक्त_reserved(handle);
		वापस ERR_PTR(err);
	पूर्ण

	err = jbd2_journal_start_reserved(handle, type, line);
	अगर (err < 0)
		वापस ERR_PTR(err);
	वापस handle;
पूर्ण

पूर्णांक __ext4_journal_ensure_credits(handle_t *handle, पूर्णांक check_cred,
				  पूर्णांक extend_cred, पूर्णांक revoke_cred)
अणु
	अगर (!ext4_handle_valid(handle))
		वापस 0;
	अगर (jbd2_handle_buffer_credits(handle) >= check_cred &&
	    handle->h_revoke_credits >= revoke_cred)
		वापस 0;
	extend_cred = max(0, extend_cred - jbd2_handle_buffer_credits(handle));
	revoke_cred = max(0, revoke_cred - handle->h_revoke_credits);
	वापस ext4_journal_extend(handle, extend_cred, revoke_cred);
पूर्ण

अटल व्योम ext4_journal_पात_handle(स्थिर अक्षर *caller, अचिन्हित पूर्णांक line,
				      स्थिर अक्षर *err_fn,
				      काष्ठा buffer_head *bh,
				      handle_t *handle, पूर्णांक err)
अणु
	अक्षर nbuf[16];
	स्थिर अक्षर *errstr = ext4_decode_error(शून्य, err, nbuf);

	BUG_ON(!ext4_handle_valid(handle));

	अगर (bh)
		BUFFER_TRACE(bh, "abort");

	अगर (!handle->h_err)
		handle->h_err = err;

	अगर (is_handle_पातed(handle))
		वापस;

	prपूर्णांकk(KERN_ERR "EXT4-fs: %s:%d: aborting transaction: %s in %s\n",
	       caller, line, errstr, err_fn);

	jbd2_journal_पात_handle(handle);
पूर्ण

अटल व्योम ext4_check_bdev_ग_लिखो_error(काष्ठा super_block *sb)
अणु
	काष्ठा address_space *mapping = sb->s_bdev->bd_inode->i_mapping;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक err;

	/*
	 * If the block device has ग_लिखो error flag, it may have failed to
	 * async ग_लिखो out metadata buffers in the background. In this हाल,
	 * we could पढ़ो old data from disk and ग_लिखो it out again, which
	 * may lead to on-disk fileप्रणाली inconsistency.
	 */
	अगर (errseq_check(&mapping->wb_err, READ_ONCE(sbi->s_bdev_wb_err))) अणु
		spin_lock(&sbi->s_bdev_wb_lock);
		err = errseq_check_and_advance(&mapping->wb_err, &sbi->s_bdev_wb_err);
		spin_unlock(&sbi->s_bdev_wb_lock);
		अगर (err)
			ext4_error_err(sb, -err,
				       "Error while async write back metadata");
	पूर्ण
पूर्ण

पूर्णांक __ext4_journal_get_ग_लिखो_access(स्थिर अक्षर *where, अचिन्हित पूर्णांक line,
				    handle_t *handle, काष्ठा buffer_head *bh)
अणु
	पूर्णांक err = 0;

	might_sleep();

	अगर (bh->b_bdev->bd_super)
		ext4_check_bdev_ग_लिखो_error(bh->b_bdev->bd_super);

	अगर (ext4_handle_valid(handle)) अणु
		err = jbd2_journal_get_ग_लिखो_access(handle, bh);
		अगर (err)
			ext4_journal_पात_handle(where, line, __func__, bh,
						  handle, err);
	पूर्ण
	वापस err;
पूर्ण

/*
 * The ext4 क्रमget function must perक्रमm a revoke अगर we are मुक्तing data
 * which has been journaled.  Metadata (eg. indirect blocks) must be
 * revoked in all हालs.
 *
 * "bh" may be शून्य: a metadata block may have been मुक्तd from memory
 * but there may still be a record of it in the journal, and that record
 * still needs to be revoked.
 *
 * If the handle isn't valid we're not journaling, but we still need to
 * call पूर्णांकo ext4_journal_revoke() to put the buffer head.
 */
पूर्णांक __ext4_क्रमget(स्थिर अक्षर *where, अचिन्हित पूर्णांक line, handle_t *handle,
		  पूर्णांक is_metadata, काष्ठा inode *inode,
		  काष्ठा buffer_head *bh, ext4_fsblk_t blocknr)
अणु
	पूर्णांक err;

	might_sleep();

	trace_ext4_क्रमget(inode, is_metadata, blocknr);
	BUFFER_TRACE(bh, "enter");

	jbd_debug(4, "forgetting bh %p: is_metadata = %d, mode %o, "
		  "data mode %x\n",
		  bh, is_metadata, inode->i_mode,
		  test_opt(inode->i_sb, DATA_FLAGS));

	/* In the no journal हाल, we can just करो a bक्रमget and वापस */
	अगर (!ext4_handle_valid(handle)) अणु
		bक्रमget(bh);
		वापस 0;
	पूर्ण

	/* Never use the revoke function अगर we are करोing full data
	 * journaling: there is no need to, and a V1 superblock won't
	 * support it.  Otherwise, only skip the revoke on un-journaled
	 * data blocks. */

	अगर (test_opt(inode->i_sb, DATA_FLAGS) == EXT4_MOUNT_JOURNAL_DATA ||
	    (!is_metadata && !ext4_should_journal_data(inode))) अणु
		अगर (bh) अणु
			BUFFER_TRACE(bh, "call jbd2_journal_forget");
			err = jbd2_journal_क्रमget(handle, bh);
			अगर (err)
				ext4_journal_पात_handle(where, line, __func__,
							  bh, handle, err);
			वापस err;
		पूर्ण
		वापस 0;
	पूर्ण

	/*
	 * data!=journal && (is_metadata || should_journal_data(inode))
	 */
	BUFFER_TRACE(bh, "call jbd2_journal_revoke");
	err = jbd2_journal_revoke(handle, blocknr, bh);
	अगर (err) अणु
		ext4_journal_पात_handle(where, line, __func__,
					  bh, handle, err);
		__ext4_error(inode->i_sb, where, line, true, -err, 0,
			     "error %d when attempting revoke", err);
	पूर्ण
	BUFFER_TRACE(bh, "exit");
	वापस err;
पूर्ण

पूर्णांक __ext4_journal_get_create_access(स्थिर अक्षर *where, अचिन्हित पूर्णांक line,
				handle_t *handle, काष्ठा buffer_head *bh)
अणु
	पूर्णांक err = 0;

	अगर (ext4_handle_valid(handle)) अणु
		err = jbd2_journal_get_create_access(handle, bh);
		अगर (err)
			ext4_journal_पात_handle(where, line, __func__,
						  bh, handle, err);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक __ext4_handle_dirty_metadata(स्थिर अक्षर *where, अचिन्हित पूर्णांक line,
				 handle_t *handle, काष्ठा inode *inode,
				 काष्ठा buffer_head *bh)
अणु
	पूर्णांक err = 0;

	might_sleep();

	set_buffer_meta(bh);
	set_buffer_prio(bh);
	अगर (ext4_handle_valid(handle)) अणु
		err = jbd2_journal_dirty_metadata(handle, bh);
		/* Errors can only happen due to पातed journal or a nasty bug */
		अगर (!is_handle_पातed(handle) && WARN_ON_ONCE(err)) अणु
			ext4_journal_पात_handle(where, line, __func__, bh,
						  handle, err);
			अगर (inode == शून्य) अणु
				pr_err("EXT4: jbd2_journal_dirty_metadata "
				       "failed: handle type %u started at "
				       "line %u, credits %u/%u, errcode %d",
				       handle->h_type,
				       handle->h_line_no,
				       handle->h_requested_credits,
				       jbd2_handle_buffer_credits(handle), err);
				वापस err;
			पूर्ण
			ext4_error_inode(inode, where, line,
					 bh->b_blocknr,
					 "journal_dirty_metadata failed: "
					 "handle type %u started at line %u, "
					 "credits %u/%u, errcode %d",
					 handle->h_type,
					 handle->h_line_no,
					 handle->h_requested_credits,
					 jbd2_handle_buffer_credits(handle),
					 err);
		पूर्ण
	पूर्ण अन्यथा अणु
		set_buffer_uptodate(bh);
		अगर (inode)
			mark_buffer_dirty_inode(bh, inode);
		अन्यथा
			mark_buffer_dirty(bh);
		अगर (inode && inode_needs_sync(inode)) अणु
			sync_dirty_buffer(bh);
			अगर (buffer_req(bh) && !buffer_uptodate(bh)) अणु
				ext4_error_inode_err(inode, where, line,
						     bh->b_blocknr, EIO,
					"IO error syncing itable block");
				err = -EIO;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण
