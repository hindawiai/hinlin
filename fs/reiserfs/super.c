<शैली गुरु>
/*
 * Copyright 2000 by Hans Reiser, licensing governed by reiserfs/README
 *
 * Trivial changes by Alan Cox to add the LFS fixes
 *
 * Trivial Changes:
 * Rights granted to Hans Reiser to redistribute under other terms providing
 * he accepts all liability including but not limited to patent, fitness
 * क्रम purpose, and direct or indirect claims arising from failure to perक्रमm.
 *
 * NO WARRANTY
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/समय.स>
#समावेश <linux/uaccess.h>
#समावेश "reiserfs.h"
#समावेश "acl.h"
#समावेश "xattr.h"
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/vfs.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/crc32.h>
#समावेश <linux/seq_file.h>

काष्ठा file_प्रणाली_type reiserfs_fs_type;

अटल स्थिर अक्षर reiserfs_3_5_magic_string[] = REISERFS_SUPER_MAGIC_STRING;
अटल स्थिर अक्षर reiserfs_3_6_magic_string[] = REISER2FS_SUPER_MAGIC_STRING;
अटल स्थिर अक्षर reiserfs_jr_magic_string[] = REISER2FS_JR_SUPER_MAGIC_STRING;

पूर्णांक is_reiserfs_3_5(काष्ठा reiserfs_super_block *rs)
अणु
	वापस !म_भेदन(rs->s_v1.s_magic, reiserfs_3_5_magic_string,
			म_माप(reiserfs_3_5_magic_string));
पूर्ण

पूर्णांक is_reiserfs_3_6(काष्ठा reiserfs_super_block *rs)
अणु
	वापस !म_भेदन(rs->s_v1.s_magic, reiserfs_3_6_magic_string,
			म_माप(reiserfs_3_6_magic_string));
पूर्ण

पूर्णांक is_reiserfs_jr(काष्ठा reiserfs_super_block *rs)
अणु
	वापस !म_भेदन(rs->s_v1.s_magic, reiserfs_jr_magic_string,
			म_माप(reiserfs_jr_magic_string));
पूर्ण

अटल पूर्णांक is_any_reiserfs_magic_string(काष्ठा reiserfs_super_block *rs)
अणु
	वापस (is_reiserfs_3_5(rs) || is_reiserfs_3_6(rs) ||
		is_reiserfs_jr(rs));
पूर्ण

अटल पूर्णांक reiserfs_remount(काष्ठा super_block *s, पूर्णांक *flags, अक्षर *data);
अटल पूर्णांक reiserfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf);

अटल पूर्णांक reiserfs_sync_fs(काष्ठा super_block *s, पूर्णांक रुको)
अणु
	काष्ठा reiserfs_transaction_handle th;

	/*
	 * Writeback quota in non-journalled quota हाल - journalled quota has
	 * no dirty dquots
	 */
	dquot_ग_लिखोback_dquots(s, -1);
	reiserfs_ग_लिखो_lock(s);
	अगर (!journal_begin(&th, s, 1))
		अगर (!journal_end_sync(&th))
			reiserfs_flush_old_commits(s);
	reiserfs_ग_लिखो_unlock(s);
	वापस 0;
पूर्ण

अटल व्योम flush_old_commits(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा reiserfs_sb_info *sbi;
	काष्ठा super_block *s;

	sbi = container_of(work, काष्ठा reiserfs_sb_info, old_work.work);
	s = sbi->s_journal->j_work_sb;

	/*
	 * We need s_umount क्रम protecting quota ग_लिखोback. We have to use
	 * trylock as reiserfs_cancel_old_flush() may be रुकोing क्रम this work
	 * to complete with s_umount held.
	 */
	अगर (!करोwn_पढ़ो_trylock(&s->s_umount)) अणु
		/* Requeue work अगर we are not cancelling it */
		spin_lock(&sbi->old_work_lock);
		अगर (sbi->work_queued == 1)
			queue_delayed_work(प्रणाली_दीर्घ_wq, &sbi->old_work, HZ);
		spin_unlock(&sbi->old_work_lock);
		वापस;
	पूर्ण
	spin_lock(&sbi->old_work_lock);
	/* Aव्योम clobbering the cancel state... */
	अगर (sbi->work_queued == 1)
		sbi->work_queued = 0;
	spin_unlock(&sbi->old_work_lock);

	reiserfs_sync_fs(s, 1);
	up_पढ़ो(&s->s_umount);
पूर्ण

व्योम reiserfs_schedule_old_flush(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_sb_info *sbi = REISERFS_SB(s);
	अचिन्हित दीर्घ delay;

	/*
	 * Aव्योम scheduling flush when sb is being shut करोwn. It can race
	 * with journal shutकरोwn and मुक्त still queued delayed work.
	 */
	अगर (sb_rकरोnly(s) || !(s->s_flags & SB_ACTIVE))
		वापस;

	spin_lock(&sbi->old_work_lock);
	अगर (!sbi->work_queued) अणु
		delay = msecs_to_jअगरfies(dirty_ग_लिखोback_पूर्णांकerval * 10);
		queue_delayed_work(प्रणाली_दीर्घ_wq, &sbi->old_work, delay);
		sbi->work_queued = 1;
	पूर्ण
	spin_unlock(&sbi->old_work_lock);
पूर्ण

व्योम reiserfs_cancel_old_flush(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_sb_info *sbi = REISERFS_SB(s);

	spin_lock(&sbi->old_work_lock);
	/* Make sure no new flushes will be queued */
	sbi->work_queued = 2;
	spin_unlock(&sbi->old_work_lock);
	cancel_delayed_work_sync(&REISERFS_SB(s)->old_work);
पूर्ण

अटल पूर्णांक reiserfs_मुक्तze(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_transaction_handle th;

	reiserfs_cancel_old_flush(s);

	reiserfs_ग_लिखो_lock(s);
	अगर (!sb_rकरोnly(s)) अणु
		पूर्णांक err = journal_begin(&th, s, 1);
		अगर (err) अणु
			reiserfs_block_ग_लिखोs(&th);
		पूर्ण अन्यथा अणु
			reiserfs_prepare_क्रम_journal(s, SB_BUFFER_WITH_SB(s),
						     1);
			journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));
			reiserfs_block_ग_लिखोs(&th);
			journal_end_sync(&th);
		पूर्ण
	पूर्ण
	reiserfs_ग_लिखो_unlock(s);
	वापस 0;
पूर्ण

अटल पूर्णांक reiserfs_unमुक्तze(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_sb_info *sbi = REISERFS_SB(s);

	reiserfs_allow_ग_लिखोs(s);
	spin_lock(&sbi->old_work_lock);
	/* Allow old_work to run again */
	sbi->work_queued = 0;
	spin_unlock(&sbi->old_work_lock);
	वापस 0;
पूर्ण

बाह्य स्थिर काष्ठा in_core_key MAX_IN_CORE_KEY;

/*
 * this is used to delete "save link" when there are no items of a
 * file it poपूर्णांकs to. It can either happen अगर unlink is completed but
 * "save unlink" removal, or अगर file has both unlink and truncate
 * pending and as unlink completes first (because key of "save link"
 * protecting unlink is bigger that a key lf "save link" which
 * protects truncate), so there left no items to make truncate
 * completion on
 */
अटल पूर्णांक हटाओ_save_link_only(काष्ठा super_block *s,
				 काष्ठा reiserfs_key *key, पूर्णांक oid_मुक्त)
अणु
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक err;

	/* we are going to करो one balancing */
	err = journal_begin(&th, s, JOURNAL_PER_BALANCE_CNT);
	अगर (err)
		वापस err;

	reiserfs_delete_solid_item(&th, शून्य, key);
	अगर (oid_मुक्त)
		/* removals are रक्षित by direct items */
		reiserfs_release_objectid(&th, le32_to_cpu(key->k_objectid));

	वापस journal_end(&th);
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक reiserfs_quota_on_mount(काष्ठा super_block *, पूर्णांक);
#पूर्ण_अगर

/*
 * Look क्रम uncompleted unlinks and truncates and complete them
 *
 * Called with superblock ग_लिखो locked.  If quotas are enabled, we have to
 * release/retake lest we call dquot_quota_on_mount(), proceed to
 * schedule_on_each_cpu() in invalidate_bdev() and deadlock रुकोing क्रम the per
 * cpu worklets to complete flush_async_commits() that in turn रुको क्रम the
 * superblock ग_लिखो lock.
 */
अटल पूर्णांक finish_unfinished(काष्ठा super_block *s)
अणु
	INITIALIZE_PATH(path);
	काष्ठा cpu_key max_cpu_key, obj_key;
	काष्ठा reiserfs_key save_link_key, last_inode_key;
	पूर्णांक retval = 0;
	काष्ठा item_head *ih;
	काष्ठा buffer_head *bh;
	पूर्णांक item_pos;
	अक्षर *item;
	पूर्णांक करोne;
	काष्ठा inode *inode;
	पूर्णांक truncate;
#अगर_घोषित CONFIG_QUOTA
	पूर्णांक i;
	पूर्णांक ms_active_set;
	पूर्णांक quota_enabled[REISERFS_MAXQUOTAS];
#पूर्ण_अगर

	/* compose key to look क्रम "save" links */
	max_cpu_key.version = KEY_FORMAT_3_5;
	max_cpu_key.on_disk_key.k_dir_id = ~0U;
	max_cpu_key.on_disk_key.k_objectid = ~0U;
	set_cpu_key_k_offset(&max_cpu_key, ~0U);
	max_cpu_key.key_length = 3;

	स_रखो(&last_inode_key, 0, माप(last_inode_key));

#अगर_घोषित CONFIG_QUOTA
	/* Needed क्रम iput() to work correctly and not trash data */
	अगर (s->s_flags & SB_ACTIVE) अणु
		ms_active_set = 0;
	पूर्ण अन्यथा अणु
		ms_active_set = 1;
		s->s_flags |= SB_ACTIVE;
	पूर्ण
	/* Turn on quotas so that they are updated correctly */
	क्रम (i = 0; i < REISERFS_MAXQUOTAS; i++) अणु
		quota_enabled[i] = 1;
		अगर (REISERFS_SB(s)->s_qf_names[i]) अणु
			पूर्णांक ret;

			अगर (sb_has_quota_active(s, i)) अणु
				quota_enabled[i] = 0;
				जारी;
			पूर्ण
			reiserfs_ग_लिखो_unlock(s);
			ret = reiserfs_quota_on_mount(s, i);
			reiserfs_ग_लिखो_lock(s);
			अगर (ret < 0)
				reiserfs_warning(s, "reiserfs-2500",
						 "cannot turn on journaled "
						 "quota: error %d", ret);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	करोne = 0;
	REISERFS_SB(s)->s_is_unlinked_ok = 1;
	जबतक (!retval) अणु
		पूर्णांक depth;
		retval = search_item(s, &max_cpu_key, &path);
		अगर (retval != ITEM_NOT_FOUND) अणु
			reiserfs_error(s, "vs-2140",
				       "search_by_key returned %d", retval);
			अवरोध;
		पूर्ण

		bh = get_last_bh(&path);
		item_pos = get_item_pos(&path);
		अगर (item_pos != B_NR_ITEMS(bh)) अणु
			reiserfs_warning(s, "vs-2060",
					 "wrong position found");
			अवरोध;
		पूर्ण
		item_pos--;
		ih = item_head(bh, item_pos);

		अगर (le32_to_cpu(ih->ih_key.k_dir_id) != MAX_KEY_OBJECTID)
			/* there are no "save" links anymore */
			अवरोध;

		save_link_key = ih->ih_key;
		अगर (is_indirect_le_ih(ih))
			truncate = 1;
		अन्यथा
			truncate = 0;

		/* reiserfs_iget needs k_dirid and k_objectid only */
		item = ih_item_body(bh, ih);
		obj_key.on_disk_key.k_dir_id = le32_to_cpu(*(__le32 *) item);
		obj_key.on_disk_key.k_objectid =
		    le32_to_cpu(ih->ih_key.k_objectid);
		obj_key.on_disk_key.k_offset = 0;
		obj_key.on_disk_key.k_type = 0;

		pathrअन्यथा(&path);

		inode = reiserfs_iget(s, &obj_key);
		अगर (IS_ERR_OR_शून्य(inode)) अणु
			/*
			 * the unlink almost completed, it just did not
			 * manage to हटाओ "save" link and release objectid
			 */
			reiserfs_warning(s, "vs-2180", "iget failed for %K",
					 &obj_key);
			retval = हटाओ_save_link_only(s, &save_link_key, 1);
			जारी;
		पूर्ण

		अगर (!truncate && inode->i_nlink) अणु
			/* file is not unlinked */
			reiserfs_warning(s, "vs-2185",
					 "file %K is not unlinked",
					 &obj_key);
			retval = हटाओ_save_link_only(s, &save_link_key, 0);
			जारी;
		पूर्ण
		depth = reiserfs_ग_लिखो_unlock_nested(inode->i_sb);
		dquot_initialize(inode);
		reiserfs_ग_लिखो_lock_nested(inode->i_sb, depth);

		अगर (truncate && S_ISसूची(inode->i_mode)) अणु
			/*
			 * We got a truncate request क्रम a dir which
			 * is impossible.  The only imaginable way is to
			 * execute unfinished truncate request then boot
			 * पूर्णांकo old kernel, हटाओ the file and create dir
			 * with the same key.
			 */
			reiserfs_warning(s, "green-2101",
					 "impossible truncate on a "
					 "directory %k. Please report",
					 INODE_PKEY(inode));
			retval = हटाओ_save_link_only(s, &save_link_key, 0);
			truncate = 0;
			iput(inode);
			जारी;
		पूर्ण

		अगर (truncate) अणु
			REISERFS_I(inode)->i_flags |=
			    i_link_saved_truncate_mask;
			/*
			 * not completed truncate found. New size was
			 * committed together with "save" link
			 */
			reiserfs_info(s, "Truncating %k to %lld ..",
				      INODE_PKEY(inode), inode->i_size);

			/* करोn't update modअगरication समय */
			reiserfs_truncate_file(inode, 0);

			retval = हटाओ_save_link(inode, truncate);
		पूर्ण अन्यथा अणु
			REISERFS_I(inode)->i_flags |= i_link_saved_unlink_mask;
			/* not completed unlink (सूची_हटाओ) found */
			reiserfs_info(s, "Removing %k..", INODE_PKEY(inode));
			अगर (स_भेद(&last_inode_key, INODE_PKEY(inode),
					माप(last_inode_key)))अणु
				last_inode_key = *INODE_PKEY(inode);
				/* removal माला_लो completed in iput */
				retval = 0;
			पूर्ण अन्यथा अणु
				reiserfs_warning(s, "super-2189", "Dead loop "
						 "in finish_unfinished "
						 "detected, just remove "
						 "save link\n");
				retval = हटाओ_save_link_only(s,
							&save_link_key, 0);
			पूर्ण
		पूर्ण

		iput(inode);
		prपूर्णांकk("done\n");
		करोne++;
	पूर्ण
	REISERFS_SB(s)->s_is_unlinked_ok = 0;

#अगर_घोषित CONFIG_QUOTA
	/* Turn quotas off */
	reiserfs_ग_लिखो_unlock(s);
	क्रम (i = 0; i < REISERFS_MAXQUOTAS; i++) अणु
		अगर (sb_dqopt(s)->files[i] && quota_enabled[i])
			dquot_quota_off(s, i);
	पूर्ण
	reiserfs_ग_लिखो_lock(s);
	अगर (ms_active_set)
		/* Restore the flag back */
		s->s_flags &= ~SB_ACTIVE;
#पूर्ण_अगर
	pathrअन्यथा(&path);
	अगर (करोne)
		reiserfs_info(s, "There were %d uncompleted unlinks/truncates. "
			      "Completed\n", करोne);
	वापस retval;
पूर्ण

/*
 * to protect file being unlinked from getting lost we "safe" link files
 * being unlinked. This link will be deleted in the same transaction with last
 * item of file. mounting the fileप्रणाली we scan all these links and हटाओ
 * files which almost got lost
 */
व्योम add_save_link(काष्ठा reiserfs_transaction_handle *th,
		   काष्ठा inode *inode, पूर्णांक truncate)
अणु
	INITIALIZE_PATH(path);
	पूर्णांक retval;
	काष्ठा cpu_key key;
	काष्ठा item_head ih;
	__le32 link;

	BUG_ON(!th->t_trans_id);

	/* file can only get one "save link" of each kind */
	RFALSE(truncate &&
	       (REISERFS_I(inode)->i_flags & i_link_saved_truncate_mask),
	       "saved link already exists for truncated inode %lx",
	       (दीर्घ)inode->i_ino);
	RFALSE(!truncate &&
	       (REISERFS_I(inode)->i_flags & i_link_saved_unlink_mask),
	       "saved link already exists for unlinked inode %lx",
	       (दीर्घ)inode->i_ino);

	/* setup key of "save" link */
	key.version = KEY_FORMAT_3_5;
	key.on_disk_key.k_dir_id = MAX_KEY_OBJECTID;
	key.on_disk_key.k_objectid = inode->i_ino;
	अगर (!truncate) अणु
		/* unlink, सूची_हटाओ, नाम */
		set_cpu_key_k_offset(&key, 1 + inode->i_sb->s_blocksize);
		set_cpu_key_k_type(&key, TYPE_सूचीECT);

		/* item head of "safe" link */
		make_le_item_head(&ih, &key, key.version,
				  1 + inode->i_sb->s_blocksize, TYPE_सूचीECT,
				  4 /*length */ , 0xffff /*मुक्त space */ );
	पूर्ण अन्यथा अणु
		/* truncate */
		अगर (S_ISसूची(inode->i_mode))
			reiserfs_warning(inode->i_sb, "green-2102",
					 "Adding a truncate savelink for "
					 "a directory %k! Please report",
					 INODE_PKEY(inode));
		set_cpu_key_k_offset(&key, 1);
		set_cpu_key_k_type(&key, TYPE_INसूचीECT);

		/* item head of "safe" link */
		make_le_item_head(&ih, &key, key.version, 1, TYPE_INसूचीECT,
				  4 /*length */ , 0 /*मुक्त space */ );
	पूर्ण
	key.key_length = 3;

	/* look क्रम its place in the tree */
	retval = search_item(inode->i_sb, &key, &path);
	अगर (retval != ITEM_NOT_FOUND) अणु
		अगर (retval != -ENOSPC)
			reiserfs_error(inode->i_sb, "vs-2100",
				       "search_by_key (%K) returned %d", &key,
				       retval);
		pathrअन्यथा(&path);
		वापस;
	पूर्ण

	/* body of "save" link */
	link = INODE_PKEY(inode)->k_dir_id;

	/* put "save" link पूर्णांकo tree, करोn't अक्षरge quota to anyone */
	retval =
	    reiserfs_insert_item(th, &path, &key, &ih, शून्य, (अक्षर *)&link);
	अगर (retval) अणु
		अगर (retval != -ENOSPC)
			reiserfs_error(inode->i_sb, "vs-2120",
				       "insert_item returned %d", retval);
	पूर्ण अन्यथा अणु
		अगर (truncate)
			REISERFS_I(inode)->i_flags |=
			    i_link_saved_truncate_mask;
		अन्यथा
			REISERFS_I(inode)->i_flags |= i_link_saved_unlink_mask;
	पूर्ण
पूर्ण

/* this खोलोs transaction unlike add_save_link */
पूर्णांक हटाओ_save_link(काष्ठा inode *inode, पूर्णांक truncate)
अणु
	काष्ठा reiserfs_transaction_handle th;
	काष्ठा reiserfs_key key;
	पूर्णांक err;

	/* we are going to करो one balancing only */
	err = journal_begin(&th, inode->i_sb, JOURNAL_PER_BALANCE_CNT);
	अगर (err)
		वापस err;

	/* setup key of "save" link */
	key.k_dir_id = cpu_to_le32(MAX_KEY_OBJECTID);
	key.k_objectid = INODE_PKEY(inode)->k_objectid;
	अगर (!truncate) अणु
		/* unlink, सूची_हटाओ, नाम */
		set_le_key_k_offset(KEY_FORMAT_3_5, &key,
				    1 + inode->i_sb->s_blocksize);
		set_le_key_k_type(KEY_FORMAT_3_5, &key, TYPE_सूचीECT);
	पूर्ण अन्यथा अणु
		/* truncate */
		set_le_key_k_offset(KEY_FORMAT_3_5, &key, 1);
		set_le_key_k_type(KEY_FORMAT_3_5, &key, TYPE_INसूचीECT);
	पूर्ण

	अगर ((truncate &&
	     (REISERFS_I(inode)->i_flags & i_link_saved_truncate_mask)) ||
	    (!truncate &&
	     (REISERFS_I(inode)->i_flags & i_link_saved_unlink_mask)))
		/* करोn't take quota bytes from anywhere */
		reiserfs_delete_solid_item(&th, शून्य, &key);
	अगर (!truncate) अणु
		reiserfs_release_objectid(&th, inode->i_ino);
		REISERFS_I(inode)->i_flags &= ~i_link_saved_unlink_mask;
	पूर्ण अन्यथा
		REISERFS_I(inode)->i_flags &= ~i_link_saved_truncate_mask;

	वापस journal_end(&th);
पूर्ण

अटल व्योम reiserfs_समाप्त_sb(काष्ठा super_block *s)
अणु
	अगर (REISERFS_SB(s)) अणु
		reiserfs_proc_info_करोne(s);
		/*
		 * Force any pending inode evictions to occur now. Any
		 * inodes to be हटाओd that have extended attributes
		 * associated with them need to clean them up beक्रमe
		 * we can release the extended attribute root dentries.
		 * shrink_dcache_क्रम_umount will BUG अगर we करोn't release
		 * those beक्रमe it's called so ->put_super is too late.
		 */
		shrink_dcache_sb(s);

		dput(REISERFS_SB(s)->xattr_root);
		REISERFS_SB(s)->xattr_root = शून्य;
		dput(REISERFS_SB(s)->priv_root);
		REISERFS_SB(s)->priv_root = शून्य;
	पूर्ण

	समाप्त_block_super(s);
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक reiserfs_quota_off(काष्ठा super_block *sb, पूर्णांक type);

अटल व्योम reiserfs_quota_off_umount(काष्ठा super_block *s)
अणु
	पूर्णांक type;

	क्रम (type = 0; type < REISERFS_MAXQUOTAS; type++)
		reiserfs_quota_off(s, type);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम reiserfs_quota_off_umount(काष्ठा super_block *s)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम reiserfs_put_super(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_transaction_handle th;
	th.t_trans_id = 0;

	reiserfs_quota_off_umount(s);

	reiserfs_ग_लिखो_lock(s);

	/*
	 * change file प्रणाली state to current state अगर it was mounted
	 * with पढ़ो-ग_लिखो permissions
	 */
	अगर (!sb_rकरोnly(s)) अणु
		अगर (!journal_begin(&th, s, 10)) अणु
			reiserfs_prepare_क्रम_journal(s, SB_BUFFER_WITH_SB(s),
						     1);
			set_sb_umount_state(SB_DISK_SUPER_BLOCK(s),
					    REISERFS_SB(s)->s_mount_state);
			journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));
		पूर्ण
	पूर्ण

	/*
	 * note, journal_release checks क्रम पढ़ोonly mount, and can
	 * decide not to करो a journal_end
	 */
	journal_release(&th, s);

	reiserfs_मुक्त_biपंचांगap_cache(s);

	brअन्यथा(SB_BUFFER_WITH_SB(s));

	prपूर्णांक_statistics(s);

	अगर (REISERFS_SB(s)->reserved_blocks != 0) अणु
		reiserfs_warning(s, "green-2005", "reserved blocks left %d",
				 REISERFS_SB(s)->reserved_blocks);
	पूर्ण

	reiserfs_ग_लिखो_unlock(s);
	mutex_destroy(&REISERFS_SB(s)->lock);
	destroy_workqueue(REISERFS_SB(s)->commit_wq);
	kमुक्त(REISERFS_SB(s)->s_jdev);
	kमुक्त(s->s_fs_info);
	s->s_fs_info = शून्य;
पूर्ण

अटल काष्ठा kmem_cache *reiserfs_inode_cachep;

अटल काष्ठा inode *reiserfs_alloc_inode(काष्ठा super_block *sb)
अणु
	काष्ठा reiserfs_inode_info *ei;
	ei = kmem_cache_alloc(reiserfs_inode_cachep, GFP_KERNEL);
	अगर (!ei)
		वापस शून्य;
	atomic_set(&ei->खोलोers, 0);
	mutex_init(&ei->tailpack);
#अगर_घोषित CONFIG_QUOTA
	स_रखो(&ei->i_dquot, 0, माप(ei->i_dquot));
#पूर्ण_अगर

	वापस &ei->vfs_inode;
पूर्ण

अटल व्योम reiserfs_मुक्त_inode(काष्ठा inode *inode)
अणु
	kmem_cache_मुक्त(reiserfs_inode_cachep, REISERFS_I(inode));
पूर्ण

अटल व्योम init_once(व्योम *foo)
अणु
	काष्ठा reiserfs_inode_info *ei = (काष्ठा reiserfs_inode_info *)foo;

	INIT_LIST_HEAD(&ei->i_pपुनः_स्मृति_list);
	inode_init_once(&ei->vfs_inode);
पूर्ण

अटल पूर्णांक __init init_inodecache(व्योम)
अणु
	reiserfs_inode_cachep = kmem_cache_create("reiser_inode_cache",
						  माप(काष्ठा
							 reiserfs_inode_info),
						  0, (SLAB_RECLAIM_ACCOUNT|
						      SLAB_MEM_SPREAD|
						      SLAB_ACCOUNT),
						  init_once);
	अगर (reiserfs_inode_cachep == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम destroy_inodecache(व्योम)
अणु
	/*
	 * Make sure all delayed rcu मुक्त inodes are flushed beक्रमe we
	 * destroy cache.
	 */
	rcu_barrier();
	kmem_cache_destroy(reiserfs_inode_cachep);
पूर्ण

/* we करोn't mark inodes dirty, we just log them */
अटल व्योम reiserfs_dirty_inode(काष्ठा inode *inode, पूर्णांक flags)
अणु
	काष्ठा reiserfs_transaction_handle th;

	पूर्णांक err = 0;

	अगर (sb_rकरोnly(inode->i_sb)) अणु
		reiserfs_warning(inode->i_sb, "clm-6006",
				 "writing inode %lu on readonly FS",
				 inode->i_ino);
		वापस;
	पूर्ण
	reiserfs_ग_लिखो_lock(inode->i_sb);

	/*
	 * this is really only used क्रम aसमय updates, so they करोn't have
	 * to be included in O_SYNC or fsync
	 */
	err = journal_begin(&th, inode->i_sb, 1);
	अगर (err)
		जाओ out;

	reiserfs_update_sd(&th, inode);
	journal_end(&th);

out:
	reiserfs_ग_लिखो_unlock(inode->i_sb);
पूर्ण

अटल पूर्णांक reiserfs_show_options(काष्ठा seq_file *seq, काष्ठा dentry *root)
अणु
	काष्ठा super_block *s = root->d_sb;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	दीर्घ opts = REISERFS_SB(s)->s_mount_opt;

	अगर (opts & (1 << REISERFS_LARGETAIL))
		seq_माला_दो(seq, ",tails=on");
	अन्यथा अगर (!(opts & (1 << REISERFS_SMALLTAIL)))
		seq_माला_दो(seq, ",notail");
	/* tails=small is शेष so we करोn't show it */

	अगर (!(opts & (1 << REISERFS_BARRIER_FLUSH)))
		seq_माला_दो(seq, ",barrier=none");
	/* barrier=flush is शेष so we करोn't show it */

	अगर (opts & (1 << REISERFS_ERROR_CONTINUE))
		seq_माला_दो(seq, ",errors=continue");
	अन्यथा अगर (opts & (1 << REISERFS_ERROR_PANIC))
		seq_माला_दो(seq, ",errors=panic");
	/* errors=ro is शेष so we करोn't show it */

	अगर (opts & (1 << REISERFS_DATA_LOG))
		seq_माला_दो(seq, ",data=journal");
	अन्यथा अगर (opts & (1 << REISERFS_DATA_WRITEBACK))
		seq_माला_दो(seq, ",data=writeback");
	/* data=ordered is शेष so we करोn't show it */

	अगर (opts & (1 << REISERFS_ATTRS))
		seq_माला_दो(seq, ",attrs");

	अगर (opts & (1 << REISERFS_XATTRS_USER))
		seq_माला_दो(seq, ",user_xattr");

	अगर (opts & (1 << REISERFS_EXPOSE_PRIVROOT))
		seq_माला_दो(seq, ",expose_privroot");

	अगर (opts & (1 << REISERFS_POSIXACL))
		seq_माला_दो(seq, ",acl");

	अगर (REISERFS_SB(s)->s_jdev)
		seq_show_option(seq, "jdev", REISERFS_SB(s)->s_jdev);

	अगर (journal->j_max_commit_age != journal->j_शेष_max_commit_age)
		seq_म_लिखो(seq, ",commit=%d", journal->j_max_commit_age);

#अगर_घोषित CONFIG_QUOTA
	अगर (REISERFS_SB(s)->s_qf_names[USRQUOTA])
		seq_show_option(seq, "usrjquota",
				REISERFS_SB(s)->s_qf_names[USRQUOTA]);
	अन्यथा अगर (opts & (1 << REISERFS_USRQUOTA))
		seq_माला_दो(seq, ",usrquota");
	अगर (REISERFS_SB(s)->s_qf_names[GRPQUOTA])
		seq_show_option(seq, "grpjquota",
				REISERFS_SB(s)->s_qf_names[GRPQUOTA]);
	अन्यथा अगर (opts & (1 << REISERFS_GRPQUOTA))
		seq_माला_दो(seq, ",grpquota");
	अगर (REISERFS_SB(s)->s_jquota_fmt) अणु
		अगर (REISERFS_SB(s)->s_jquota_fmt == QFMT_VFS_OLD)
			seq_माला_दो(seq, ",jqfmt=vfsold");
		अन्यथा अगर (REISERFS_SB(s)->s_jquota_fmt == QFMT_VFS_V0)
			seq_माला_दो(seq, ",jqfmt=vfsv0");
	पूर्ण
#पूर्ण_अगर

	/* Block allocator options */
	अगर (opts & (1 << REISERFS_NO_BORDER))
		seq_माला_दो(seq, ",block-allocator=noborder");
	अगर (opts & (1 << REISERFS_NO_UNHASHED_RELOCATION))
		seq_माला_दो(seq, ",block-allocator=no_unhashed_relocation");
	अगर (opts & (1 << REISERFS_HASHED_RELOCATION))
		seq_माला_दो(seq, ",block-allocator=hashed_relocation");
	अगर (opts & (1 << REISERFS_TEST4))
		seq_माला_दो(seq, ",block-allocator=test4");
	show_alloc_options(seq, s);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल sमाप_प्रकार reiserfs_quota_ग_लिखो(काष्ठा super_block *, पूर्णांक, स्थिर अक्षर *,
				    माप_प्रकार, loff_t);
अटल sमाप_प्रकार reiserfs_quota_पढ़ो(काष्ठा super_block *, पूर्णांक, अक्षर *, माप_प्रकार,
				   loff_t);

अटल काष्ठा dquot **reiserfs_get_dquots(काष्ठा inode *inode)
अणु
	वापस REISERFS_I(inode)->i_dquot;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा super_operations reiserfs_sops = अणु
	.alloc_inode = reiserfs_alloc_inode,
	.मुक्त_inode = reiserfs_मुक्त_inode,
	.ग_लिखो_inode = reiserfs_ग_लिखो_inode,
	.dirty_inode = reiserfs_dirty_inode,
	.evict_inode = reiserfs_evict_inode,
	.put_super = reiserfs_put_super,
	.sync_fs = reiserfs_sync_fs,
	.मुक्तze_fs = reiserfs_मुक्तze,
	.unमुक्तze_fs = reiserfs_unमुक्तze,
	.statfs = reiserfs_statfs,
	.remount_fs = reiserfs_remount,
	.show_options = reiserfs_show_options,
#अगर_घोषित CONFIG_QUOTA
	.quota_पढ़ो = reiserfs_quota_पढ़ो,
	.quota_ग_लिखो = reiserfs_quota_ग_लिखो,
	.get_dquots = reiserfs_get_dquots,
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_QUOTA
#घोषणा QTYPE2NAME(t) ((t)==USRQUOTA?"user":"group")

अटल पूर्णांक reiserfs_ग_लिखो_dquot(काष्ठा dquot *);
अटल पूर्णांक reiserfs_acquire_dquot(काष्ठा dquot *);
अटल पूर्णांक reiserfs_release_dquot(काष्ठा dquot *);
अटल पूर्णांक reiserfs_mark_dquot_dirty(काष्ठा dquot *);
अटल पूर्णांक reiserfs_ग_लिखो_info(काष्ठा super_block *, पूर्णांक);
अटल पूर्णांक reiserfs_quota_on(काष्ठा super_block *, पूर्णांक, पूर्णांक, स्थिर काष्ठा path *);

अटल स्थिर काष्ठा dquot_operations reiserfs_quota_operations = अणु
	.ग_लिखो_dquot = reiserfs_ग_लिखो_dquot,
	.acquire_dquot = reiserfs_acquire_dquot,
	.release_dquot = reiserfs_release_dquot,
	.mark_dirty = reiserfs_mark_dquot_dirty,
	.ग_लिखो_info = reiserfs_ग_लिखो_info,
	.alloc_dquot	= dquot_alloc,
	.destroy_dquot	= dquot_destroy,
	.get_next_id	= dquot_get_next_id,
पूर्ण;

अटल स्थिर काष्ठा quotactl_ops reiserfs_qctl_operations = अणु
	.quota_on = reiserfs_quota_on,
	.quota_off = reiserfs_quota_off,
	.quota_sync = dquot_quota_sync,
	.get_state = dquot_get_state,
	.set_info = dquot_set_dqinfo,
	.get_dqblk = dquot_get_dqblk,
	.set_dqblk = dquot_set_dqblk,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा export_operations reiserfs_export_ops = अणु
	.encode_fh = reiserfs_encode_fh,
	.fh_to_dentry = reiserfs_fh_to_dentry,
	.fh_to_parent = reiserfs_fh_to_parent,
	.get_parent = reiserfs_get_parent,
पूर्ण;

/*
 * this काष्ठा is used in reiserfs_getopt () क्रम containing the value क्रम
 * those mount options that have values rather than being toggles.
 */
प्रकार काष्ठा अणु
	अक्षर *value;
	/*
	 * biपंचांगask which is to set on mount_options biपंचांगask
	 * when this value is found, 0 is no bits are to be changed.
	 */
	पूर्णांक seपंचांगask;
	/*
	 * biपंचांगask which is to clear on mount_options biपंचांगask
	 * when this value is found, 0 is no bits are to be changed.
	 * This is applied BEFORE seपंचांगask
	 */
	पूर्णांक clrmask;
पूर्ण arg_desc_t;

/* Set this bit in arg_required to allow empty arguments */
#घोषणा REISERFS_OPT_ALLOWEMPTY 31

/*
 * this काष्ठा is used in reiserfs_getopt() क्रम describing the
 * set of reiserfs mount options
 */
प्रकार काष्ठा अणु
	अक्षर *option_name;

	/* 0 अगर argument is not required, not 0 otherwise */
	पूर्णांक arg_required;

	/* list of values accepted by an option */
	स्थिर arg_desc_t *values;

	/*
	 * biपंचांगask which is to set on mount_options biपंचांगask
	 * when this value is found, 0 is no bits are to be changed.
	 */
	पूर्णांक seपंचांगask;

	/*
	 * biपंचांगask which is to clear on mount_options biपंचांगask
	 * when this value is found, 0 is no bits are to be changed.
	 * This is applied BEFORE seपंचांगask
	 */
	पूर्णांक clrmask;
पूर्ण opt_desc_t;

/* possible values क्रम -o data= */
अटल स्थिर arg_desc_t logging_mode[] = अणु
	अणु"ordered", 1 << REISERFS_DATA_ORDERED,
	 (1 << REISERFS_DATA_LOG | 1 << REISERFS_DATA_WRITEBACK)पूर्ण,
	अणु"journal", 1 << REISERFS_DATA_LOG,
	 (1 << REISERFS_DATA_ORDERED | 1 << REISERFS_DATA_WRITEBACK)पूर्ण,
	अणु"writeback", 1 << REISERFS_DATA_WRITEBACK,
	 (1 << REISERFS_DATA_ORDERED | 1 << REISERFS_DATA_LOG)पूर्ण,
	अणु.value = शून्यपूर्ण
पूर्ण;

/* possible values क्रम -o barrier= */
अटल स्थिर arg_desc_t barrier_mode[] = अणु
	अणु"none", 1 << REISERFS_BARRIER_NONE, 1 << REISERFS_BARRIER_FLUSHपूर्ण,
	अणु"flush", 1 << REISERFS_BARRIER_FLUSH, 1 << REISERFS_BARRIER_NONEपूर्ण,
	अणु.value = शून्यपूर्ण
पूर्ण;

/*
 * possible values क्रम "-o block-allocator=" and bits which are to be set in
 * s_mount_opt of reiserfs specअगरic part of in-core super block
 */
अटल स्थिर arg_desc_t balloc[] = अणु
	अणु"noborder", 1 << REISERFS_NO_BORDER, 0पूर्ण,
	अणु"border", 0, 1 << REISERFS_NO_BORDERपूर्ण,
	अणु"no_unhashed_relocation", 1 << REISERFS_NO_UNHASHED_RELOCATION, 0पूर्ण,
	अणु"hashed_relocation", 1 << REISERFS_HASHED_RELOCATION, 0पूर्ण,
	अणु"test4", 1 << REISERFS_TEST4, 0पूर्ण,
	अणु"notest4", 0, 1 << REISERFS_TEST4पूर्ण,
	अणुशून्य, 0, 0पूर्ण
पूर्ण;

अटल स्थिर arg_desc_t tails[] = अणु
	अणु"on", 1 << REISERFS_LARGETAIL, 1 << REISERFS_SMALLTAILपूर्ण,
	अणु"off", 0, (1 << REISERFS_LARGETAIL) | (1 << REISERFS_SMALLTAIL)पूर्ण,
	अणु"small", 1 << REISERFS_SMALLTAIL, 1 << REISERFS_LARGETAILपूर्ण,
	अणुशून्य, 0, 0पूर्ण
पूर्ण;

अटल स्थिर arg_desc_t error_actions[] = अणु
	अणु"panic", 1 << REISERFS_ERROR_PANIC,
	 (1 << REISERFS_ERROR_RO | 1 << REISERFS_ERROR_CONTINUE)पूर्ण,
	अणु"ro-remount", 1 << REISERFS_ERROR_RO,
	 (1 << REISERFS_ERROR_PANIC | 1 << REISERFS_ERROR_CONTINUE)पूर्ण,
#अगर_घोषित REISERFS_JOURNAL_ERROR_ALLOWS_NO_LOG
	अणु"continue", 1 << REISERFS_ERROR_CONTINUE,
	 (1 << REISERFS_ERROR_PANIC | 1 << REISERFS_ERROR_RO)पूर्ण,
#पूर्ण_अगर
	अणुशून्य, 0, 0पूर्ण,
पूर्ण;

/*
 * proceed only one option from a list *cur - string containing of mount
 * options
 * opts - array of options which are accepted
 * opt_arg - अगर option is found and requires an argument and अगर it is specअगरed
 * in the input - poपूर्णांकer to the argument is stored here
 * bit_flags - अगर option requires to set a certain bit - it is set here
 * वापस -1 अगर unknown option is found, opt->arg_required otherwise
 */
अटल पूर्णांक reiserfs_getopt(काष्ठा super_block *s, अक्षर **cur, opt_desc_t * opts,
			   अक्षर **opt_arg, अचिन्हित दीर्घ *bit_flags)
अणु
	अक्षर *p;
	/*
	 * foo=bar,
	 * ^   ^  ^
	 * |   |  +-- option_end
	 * |   +-- arg_start
	 * +-- option_start
	 */
	स्थिर opt_desc_t *opt;
	स्थिर arg_desc_t *arg;

	p = *cur;

	/* assume argument cannot contain commas */
	*cur = म_अक्षर(p, ',');
	अगर (*cur) अणु
		*(*cur) = '\0';
		(*cur)++;
	पूर्ण

	अगर (!म_भेदन(p, "alloc=", 6)) अणु
		/*
		 * Ugly special हाल, probably we should reकरो options
		 * parser so that it can understand several arguments क्रम
		 * some options, also so that it can fill several bitfields
		 * with option values.
		 */
		अगर (reiserfs_parse_alloc_options(s, p + 6)) अणु
			वापस -1;
		पूर्ण अन्यथा अणु
			वापस 0;
		पूर्ण
	पूर्ण

	/* क्रम every option in the list */
	क्रम (opt = opts; opt->option_name; opt++) अणु
		अगर (!म_भेदन(p, opt->option_name, म_माप(opt->option_name))) अणु
			अगर (bit_flags) अणु
				अगर (opt->clrmask ==
				    (1 << REISERFS_UNSUPPORTED_OPT))
					reiserfs_warning(s, "super-6500",
							 "%s not supported.\n",
							 p);
				अन्यथा
					*bit_flags &= ~opt->clrmask;
				अगर (opt->seपंचांगask ==
				    (1 << REISERFS_UNSUPPORTED_OPT))
					reiserfs_warning(s, "super-6501",
							 "%s not supported.\n",
							 p);
				अन्यथा
					*bit_flags |= opt->seपंचांगask;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!opt->option_name) अणु
		reiserfs_warning(s, "super-6502",
				 "unknown mount option \"%s\"", p);
		वापस -1;
	पूर्ण

	p += म_माप(opt->option_name);
	चयन (*p) अणु
	हाल '=':
		अगर (!opt->arg_required) अणु
			reiserfs_warning(s, "super-6503",
					 "the option \"%s\" does not "
					 "require an argument\n",
					 opt->option_name);
			वापस -1;
		पूर्ण
		अवरोध;

	हाल 0:
		अगर (opt->arg_required) अणु
			reiserfs_warning(s, "super-6504",
					 "the option \"%s\" requires an "
					 "argument\n", opt->option_name);
			वापस -1;
		पूर्ण
		अवरोध;
	शेष:
		reiserfs_warning(s, "super-6505",
				 "head of option \"%s\" is only correct\n",
				 opt->option_name);
		वापस -1;
	पूर्ण

	/*
	 * move to the argument, or to next option अगर argument is not
	 * required
	 */
	p++;

	अगर (opt->arg_required
	    && !(opt->arg_required & (1 << REISERFS_OPT_ALLOWEMPTY))
	    && !म_माप(p)) अणु
		/* this catches "option=," अगर not allowed */
		reiserfs_warning(s, "super-6506",
				 "empty argument for \"%s\"\n",
				 opt->option_name);
		वापस -1;
	पूर्ण

	अगर (!opt->values) अणु
		/* *=शून्यopt_arg contains poपूर्णांकer to argument */
		*opt_arg = p;
		वापस opt->arg_required & ~(1 << REISERFS_OPT_ALLOWEMPTY);
	पूर्ण

	/* values possible क्रम this option are listed in opt->values */
	क्रम (arg = opt->values; arg->value; arg++) अणु
		अगर (!म_भेद(p, arg->value)) अणु
			अगर (bit_flags) अणु
				*bit_flags &= ~arg->clrmask;
				*bit_flags |= arg->seपंचांगask;
			पूर्ण
			वापस opt->arg_required;
		पूर्ण
	पूर्ण

	reiserfs_warning(s, "super-6506",
			 "bad value \"%s\" for option \"%s\"\n", p,
			 opt->option_name);
	वापस -1;
पूर्ण

/* वापसs 0 अगर something is wrong in option string, 1 - otherwise */
अटल पूर्णांक reiserfs_parse_options(काष्ठा super_block *s,

				  /* string given via mount's -o */
				  अक्षर *options,

				  /*
				   * after the parsing phase, contains the
				   * collection of bitflags defining what
				   * mount options were selected.
				   */
				  अचिन्हित दीर्घ *mount_options,

				  /* म_से_दीर्घ-ed from NNN of resize=NNN */
				  अचिन्हित दीर्घ *blocks,
				  अक्षर **jdev_name,
				  अचिन्हित पूर्णांक *commit_max_age,
				  अक्षर **qf_names,
				  अचिन्हित पूर्णांक *qfmt)
अणु
	पूर्णांक c;
	अक्षर *arg = शून्य;
	अक्षर *pos;
	opt_desc_t opts[] = अणु
		/*
		 * Compatibility stuff, so that -o notail क्रम old
		 * setups still work
		 */
		अणु"tails",.arg_required = 't',.values = tailsपूर्ण,
		अणु"notail",.clrmask =
		 (1 << REISERFS_LARGETAIL) | (1 << REISERFS_SMALLTAIL)पूर्ण,
		अणु"conv",.seपंचांगask = 1 << REISERFS_CONVERTपूर्ण,
		अणु"attrs",.seपंचांगask = 1 << REISERFS_ATTRSपूर्ण,
		अणु"noattrs",.clrmask = 1 << REISERFS_ATTRSपूर्ण,
		अणु"expose_privroot", .seपंचांगask = 1 << REISERFS_EXPOSE_PRIVROOTपूर्ण,
#अगर_घोषित CONFIG_REISERFS_FS_XATTR
		अणु"user_xattr",.seपंचांगask = 1 << REISERFS_XATTRS_USERपूर्ण,
		अणु"nouser_xattr",.clrmask = 1 << REISERFS_XATTRS_USERपूर्ण,
#अन्यथा
		अणु"user_xattr",.seपंचांगask = 1 << REISERFS_UNSUPPORTED_OPTपूर्ण,
		अणु"nouser_xattr",.clrmask = 1 << REISERFS_UNSUPPORTED_OPTपूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_REISERFS_FS_POSIX_ACL
		अणु"acl",.seपंचांगask = 1 << REISERFS_POSIXACLपूर्ण,
		अणु"noacl",.clrmask = 1 << REISERFS_POSIXACLपूर्ण,
#अन्यथा
		अणु"acl",.seपंचांगask = 1 << REISERFS_UNSUPPORTED_OPTपूर्ण,
		अणु"noacl",.clrmask = 1 << REISERFS_UNSUPPORTED_OPTपूर्ण,
#पूर्ण_अगर
		अणु.option_name = "nolog"पूर्ण,
		अणु"replayonly",.seपंचांगask = 1 << REPLAYONLYपूर्ण,
		अणु"block-allocator",.arg_required = 'a',.values = ballocपूर्ण,
		अणु"data",.arg_required = 'd',.values = logging_modeपूर्ण,
		अणु"barrier",.arg_required = 'b',.values = barrier_modeपूर्ण,
		अणु"resize",.arg_required = 'r',.values = शून्यपूर्ण,
		अणु"jdev",.arg_required = 'j',.values = शून्यपूर्ण,
		अणु"nolargeio",.arg_required = 'w',.values = शून्यपूर्ण,
		अणु"commit",.arg_required = 'c',.values = शून्यपूर्ण,
		अणु"usrquota",.seपंचांगask = 1 << REISERFS_USRQUOTAपूर्ण,
		अणु"grpquota",.seपंचांगask = 1 << REISERFS_GRPQUOTAपूर्ण,
		अणु"noquota",.clrmask = 1 << REISERFS_USRQUOTA | 1 << REISERFS_GRPQUOTAपूर्ण,
		अणु"errors",.arg_required = 'e',.values = error_actionsपूर्ण,
		अणु"usrjquota",.arg_required =
		 'u' | (1 << REISERFS_OPT_ALLOWEMPTY),.values = शून्यपूर्ण,
		अणु"grpjquota",.arg_required =
		 'g' | (1 << REISERFS_OPT_ALLOWEMPTY),.values = शून्यपूर्ण,
		अणु"jqfmt",.arg_required = 'f',.values = शून्यपूर्ण,
		अणु.option_name = शून्यपूर्ण
	पूर्ण;

	*blocks = 0;
	अगर (!options || !*options)
		/*
		 * use शेष configuration: create tails, journaling on, no
		 * conversion to newest क्रमmat
		 */
		वापस 1;

	क्रम (pos = options; pos;) अणु
		c = reiserfs_getopt(s, &pos, opts, &arg, mount_options);
		अगर (c == -1)
			/* wrong option is given */
			वापस 0;

		अगर (c == 'r') अणु
			अक्षर *p;

			p = शून्य;
			/* "resize=NNN" or "resize=auto" */

			अगर (!म_भेद(arg, "auto")) अणु
				/* From JFS code, to स्वतः-get the size. */
				*blocks =
				    i_size_पढ़ो(s->s_bdev->bd_inode) >> s->
				    s_blocksize_bits;
			पूर्ण अन्यथा अणु
				*blocks = simple_म_से_अदीर्घ(arg, &p, 0);
				अगर (*p != '\0') अणु
					/* NNN करोes not look like a number */
					reiserfs_warning(s, "super-6507",
							 "bad value %s for "
							 "-oresize\n", arg);
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (c == 'c') अणु
			अक्षर *p = शून्य;
			अचिन्हित दीर्घ val = simple_म_से_अदीर्घ(arg, &p, 0);
			/* commit=NNN (समय in seconds) */
			अगर (*p != '\0' || val >= (अचिन्हित पूर्णांक)-1) अणु
				reiserfs_warning(s, "super-6508",
						 "bad value %s for -ocommit\n",
						 arg);
				वापस 0;
			पूर्ण
			*commit_max_age = (अचिन्हित पूर्णांक)val;
		पूर्ण

		अगर (c == 'w') अणु
			reiserfs_warning(s, "super-6509", "nolargeio option "
					 "is no longer supported");
			वापस 0;
		पूर्ण

		अगर (c == 'j') अणु
			अगर (arg && *arg && jdev_name) अणु
				/* Hm, alपढ़ोy asचिन्हित? */
				अगर (*jdev_name) अणु
					reiserfs_warning(s, "super-6510",
							 "journal device was "
							 "already specified to "
							 "be %s", *jdev_name);
					वापस 0;
				पूर्ण
				*jdev_name = arg;
			पूर्ण
		पूर्ण
#अगर_घोषित CONFIG_QUOTA
		अगर (c == 'u' || c == 'g') अणु
			पूर्णांक qtype = c == 'u' ? USRQUOTA : GRPQUOTA;

			अगर (sb_any_quota_loaded(s) &&
			    (!*arg != !REISERFS_SB(s)->s_qf_names[qtype])) अणु
				reiserfs_warning(s, "super-6511",
						 "cannot change journaled "
						 "quota options when quota "
						 "turned on.");
				वापस 0;
			पूर्ण
			अगर (qf_names[qtype] !=
			    REISERFS_SB(s)->s_qf_names[qtype])
				kमुक्त(qf_names[qtype]);
			qf_names[qtype] = शून्य;
			अगर (*arg) अणु	/* Some filename specअगरied? */
				अगर (REISERFS_SB(s)->s_qf_names[qtype]
				    && म_भेद(REISERFS_SB(s)->s_qf_names[qtype],
					      arg)) अणु
					reiserfs_warning(s, "super-6512",
							 "%s quota file "
							 "already specified.",
							 QTYPE2NAME(qtype));
					वापस 0;
				पूर्ण
				अगर (म_अक्षर(arg, '/')) अणु
					reiserfs_warning(s, "super-6513",
							 "quotafile must be "
							 "on filesystem root.");
					वापस 0;
				पूर्ण
				qf_names[qtype] = kstrdup(arg, GFP_KERNEL);
				अगर (!qf_names[qtype]) अणु
					reiserfs_warning(s, "reiserfs-2502",
							 "not enough memory "
							 "for storing "
							 "quotafile name.");
					वापस 0;
				पूर्ण
				अगर (qtype == USRQUOTA)
					*mount_options |= 1 << REISERFS_USRQUOTA;
				अन्यथा
					*mount_options |= 1 << REISERFS_GRPQUOTA;
			पूर्ण अन्यथा अणु
				अगर (qtype == USRQUOTA)
					*mount_options &= ~(1 << REISERFS_USRQUOTA);
				अन्यथा
					*mount_options &= ~(1 << REISERFS_GRPQUOTA);
			पूर्ण
		पूर्ण
		अगर (c == 'f') अणु
			अगर (!म_भेद(arg, "vfsold"))
				*qfmt = QFMT_VFS_OLD;
			अन्यथा अगर (!म_भेद(arg, "vfsv0"))
				*qfmt = QFMT_VFS_V0;
			अन्यथा अणु
				reiserfs_warning(s, "super-6514",
						 "unknown quota format "
						 "specified.");
				वापस 0;
			पूर्ण
			अगर (sb_any_quota_loaded(s) &&
			    *qfmt != REISERFS_SB(s)->s_jquota_fmt) अणु
				reiserfs_warning(s, "super-6515",
						 "cannot change journaled "
						 "quota options when quota "
						 "turned on.");
				वापस 0;
			पूर्ण
		पूर्ण
#अन्यथा
		अगर (c == 'u' || c == 'g' || c == 'f') अणु
			reiserfs_warning(s, "reiserfs-2503", "journaled "
					 "quota options not supported.");
			वापस 0;
		पूर्ण
#पूर्ण_अगर
	पूर्ण

#अगर_घोषित CONFIG_QUOTA
	अगर (!REISERFS_SB(s)->s_jquota_fmt && !*qfmt
	    && (qf_names[USRQUOTA] || qf_names[GRPQUOTA])) अणु
		reiserfs_warning(s, "super-6515",
				 "journaled quota format not specified.");
		वापस 0;
	पूर्ण
	अगर ((!(*mount_options & (1 << REISERFS_USRQUOTA)) &&
	       sb_has_quota_loaded(s, USRQUOTA)) ||
	    (!(*mount_options & (1 << REISERFS_GRPQUOTA)) &&
	       sb_has_quota_loaded(s, GRPQUOTA))) अणु
		reiserfs_warning(s, "super-6516", "quota options must "
				 "be present when quota is turned on.");
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	वापस 1;
पूर्ण

अटल व्योम चयन_data_mode(काष्ठा super_block *s, अचिन्हित दीर्घ mode)
अणु
	REISERFS_SB(s)->s_mount_opt &= ~((1 << REISERFS_DATA_LOG) |
					 (1 << REISERFS_DATA_ORDERED) |
					 (1 << REISERFS_DATA_WRITEBACK));
	REISERFS_SB(s)->s_mount_opt |= (1 << mode);
पूर्ण

अटल व्योम handle_data_mode(काष्ठा super_block *s, अचिन्हित दीर्घ mount_options)
अणु
	अगर (mount_options & (1 << REISERFS_DATA_LOG)) अणु
		अगर (!reiserfs_data_log(s)) अणु
			चयन_data_mode(s, REISERFS_DATA_LOG);
			reiserfs_info(s, "switching to journaled data mode\n");
		पूर्ण
	पूर्ण अन्यथा अगर (mount_options & (1 << REISERFS_DATA_ORDERED)) अणु
		अगर (!reiserfs_data_ordered(s)) अणु
			चयन_data_mode(s, REISERFS_DATA_ORDERED);
			reiserfs_info(s, "switching to ordered data mode\n");
		पूर्ण
	पूर्ण अन्यथा अगर (mount_options & (1 << REISERFS_DATA_WRITEBACK)) अणु
		अगर (!reiserfs_data_ग_लिखोback(s)) अणु
			चयन_data_mode(s, REISERFS_DATA_WRITEBACK);
			reiserfs_info(s, "switching to writeback data mode\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम handle_barrier_mode(काष्ठा super_block *s, अचिन्हित दीर्घ bits)
अणु
	पूर्णांक flush = (1 << REISERFS_BARRIER_FLUSH);
	पूर्णांक none = (1 << REISERFS_BARRIER_NONE);
	पूर्णांक all_barrier = flush | none;

	अगर (bits & all_barrier) अणु
		REISERFS_SB(s)->s_mount_opt &= ~all_barrier;
		अगर (bits & flush) अणु
			REISERFS_SB(s)->s_mount_opt |= flush;
			prपूर्णांकk("reiserfs: enabling write barrier flush mode\n");
		पूर्ण अन्यथा अगर (bits & none) अणु
			REISERFS_SB(s)->s_mount_opt |= none;
			prपूर्णांकk("reiserfs: write barriers turned off\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम handle_attrs(काष्ठा super_block *s)
अणु
	काष्ठा reiserfs_super_block *rs = SB_DISK_SUPER_BLOCK(s);

	अगर (reiserfs_attrs(s)) अणु
		अगर (old_क्रमmat_only(s)) अणु
			reiserfs_warning(s, "super-6517", "cannot support "
					 "attributes on 3.5.x disk format");
			REISERFS_SB(s)->s_mount_opt &= ~(1 << REISERFS_ATTRS);
			वापस;
		पूर्ण
		अगर (!(le32_to_cpu(rs->s_flags) & reiserfs_attrs_cleared)) अणु
			reiserfs_warning(s, "super-6518", "cannot support "
					 "attributes until flag is set in "
					 "super-block");
			REISERFS_SB(s)->s_mount_opt &= ~(1 << REISERFS_ATTRS);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल व्योम handle_quota_files(काष्ठा super_block *s, अक्षर **qf_names,
			       अचिन्हित पूर्णांक *qfmt)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < REISERFS_MAXQUOTAS; i++) अणु
		अगर (qf_names[i] != REISERFS_SB(s)->s_qf_names[i])
			kमुक्त(REISERFS_SB(s)->s_qf_names[i]);
		REISERFS_SB(s)->s_qf_names[i] = qf_names[i];
	पूर्ण
	अगर (*qfmt)
		REISERFS_SB(s)->s_jquota_fmt = *qfmt;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक reiserfs_remount(काष्ठा super_block *s, पूर्णांक *mount_flags, अक्षर *arg)
अणु
	काष्ठा reiserfs_super_block *rs;
	काष्ठा reiserfs_transaction_handle th;
	अचिन्हित दीर्घ blocks;
	अचिन्हित दीर्घ mount_options = REISERFS_SB(s)->s_mount_opt;
	अचिन्हित दीर्घ safe_mask = 0;
	अचिन्हित पूर्णांक commit_max_age = (अचिन्हित पूर्णांक)-1;
	काष्ठा reiserfs_journal *journal = SB_JOURNAL(s);
	अक्षर *new_opts;
	पूर्णांक err;
	अक्षर *qf_names[REISERFS_MAXQUOTAS];
	अचिन्हित पूर्णांक qfmt = 0;
#अगर_घोषित CONFIG_QUOTA
	पूर्णांक i;
#पूर्ण_अगर

	new_opts = kstrdup(arg, GFP_KERNEL);
	अगर (arg && !new_opts)
		वापस -ENOMEM;

	sync_fileप्रणाली(s);
	reiserfs_ग_लिखो_lock(s);

#अगर_घोषित CONFIG_QUOTA
	स_नकल(qf_names, REISERFS_SB(s)->s_qf_names, माप(qf_names));
#पूर्ण_अगर

	rs = SB_DISK_SUPER_BLOCK(s);

	अगर (!reiserfs_parse_options
	    (s, arg, &mount_options, &blocks, शून्य, &commit_max_age,
	    qf_names, &qfmt)) अणु
#अगर_घोषित CONFIG_QUOTA
		क्रम (i = 0; i < REISERFS_MAXQUOTAS; i++)
			अगर (qf_names[i] != REISERFS_SB(s)->s_qf_names[i])
				kमुक्त(qf_names[i]);
#पूर्ण_अगर
		err = -EINVAL;
		जाओ out_err_unlock;
	पूर्ण
#अगर_घोषित CONFIG_QUOTA
	handle_quota_files(s, qf_names, &qfmt);
#पूर्ण_अगर

	handle_attrs(s);

	/* Add options that are safe here */
	safe_mask |= 1 << REISERFS_SMALLTAIL;
	safe_mask |= 1 << REISERFS_LARGETAIL;
	safe_mask |= 1 << REISERFS_NO_BORDER;
	safe_mask |= 1 << REISERFS_NO_UNHASHED_RELOCATION;
	safe_mask |= 1 << REISERFS_HASHED_RELOCATION;
	safe_mask |= 1 << REISERFS_TEST4;
	safe_mask |= 1 << REISERFS_ATTRS;
	safe_mask |= 1 << REISERFS_XATTRS_USER;
	safe_mask |= 1 << REISERFS_POSIXACL;
	safe_mask |= 1 << REISERFS_BARRIER_FLUSH;
	safe_mask |= 1 << REISERFS_BARRIER_NONE;
	safe_mask |= 1 << REISERFS_ERROR_RO;
	safe_mask |= 1 << REISERFS_ERROR_CONTINUE;
	safe_mask |= 1 << REISERFS_ERROR_PANIC;
	safe_mask |= 1 << REISERFS_USRQUOTA;
	safe_mask |= 1 << REISERFS_GRPQUOTA;

	/*
	 * Update the biपंचांगask, taking care to keep
	 * the bits we're not allowed to change here
	 */
	REISERFS_SB(s)->s_mount_opt =
	    (REISERFS_SB(s)->
	     s_mount_opt & ~safe_mask) | (mount_options & safe_mask);

	अगर (commit_max_age != 0 && commit_max_age != (अचिन्हित पूर्णांक)-1) अणु
		journal->j_max_commit_age = commit_max_age;
		journal->j_max_trans_age = commit_max_age;
	पूर्ण अन्यथा अगर (commit_max_age == 0) अणु
		/* 0 means restore शेषs. */
		journal->j_max_commit_age = journal->j_शेष_max_commit_age;
		journal->j_max_trans_age = JOURNAL_MAX_TRANS_AGE;
	पूर्ण

	अगर (blocks) अणु
		err = reiserfs_resize(s, blocks);
		अगर (err != 0)
			जाओ out_err_unlock;
	पूर्ण

	अगर (*mount_flags & SB_RDONLY) अणु
		reiserfs_ग_लिखो_unlock(s);
		reiserfs_xattr_init(s, *mount_flags);
		/* remount पढ़ो-only */
		अगर (sb_rकरोnly(s))
			/* it is पढ़ो-only alपढ़ोy */
			जाओ out_ok_unlocked;

		err = dquot_suspend(s, -1);
		अगर (err < 0)
			जाओ out_err;

		/* try to remount file प्रणाली with पढ़ो-only permissions */
		अगर (sb_umount_state(rs) == REISERFS_VALID_FS
		    || REISERFS_SB(s)->s_mount_state != REISERFS_VALID_FS) अणु
			जाओ out_ok_unlocked;
		पूर्ण

		reiserfs_ग_लिखो_lock(s);

		err = journal_begin(&th, s, 10);
		अगर (err)
			जाओ out_err_unlock;

		/* Mounting a rw partition पढ़ो-only. */
		reiserfs_prepare_क्रम_journal(s, SB_BUFFER_WITH_SB(s), 1);
		set_sb_umount_state(rs, REISERFS_SB(s)->s_mount_state);
		journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));
	पूर्ण अन्यथा अणु
		/* remount पढ़ो-ग_लिखो */
		अगर (!sb_rकरोnly(s)) अणु
			reiserfs_ग_लिखो_unlock(s);
			reiserfs_xattr_init(s, *mount_flags);
			जाओ out_ok_unlocked;	/* We are पढ़ो-ग_लिखो alपढ़ोy */
		पूर्ण

		अगर (reiserfs_is_journal_पातed(journal)) अणु
			err = journal->j_त्रुटि_सं;
			जाओ out_err_unlock;
		पूर्ण

		handle_data_mode(s, mount_options);
		handle_barrier_mode(s, mount_options);
		REISERFS_SB(s)->s_mount_state = sb_umount_state(rs);

		/* now it is safe to call journal_begin */
		s->s_flags &= ~SB_RDONLY;
		err = journal_begin(&th, s, 10);
		अगर (err)
			जाओ out_err_unlock;

		/* Mount a partition which is पढ़ो-only, पढ़ो-ग_लिखो */
		reiserfs_prepare_क्रम_journal(s, SB_BUFFER_WITH_SB(s), 1);
		REISERFS_SB(s)->s_mount_state = sb_umount_state(rs);
		s->s_flags &= ~SB_RDONLY;
		set_sb_umount_state(rs, REISERFS_ERROR_FS);
		अगर (!old_क्रमmat_only(s))
			set_sb_mnt_count(rs, sb_mnt_count(rs) + 1);
		/* mark_buffer_dirty (SB_BUFFER_WITH_SB (s), 1); */
		journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));
		REISERFS_SB(s)->s_mount_state = REISERFS_VALID_FS;
	पूर्ण
	/* this will क्रमce a full flush of all journal lists */
	SB_JOURNAL(s)->j_must_रुको = 1;
	err = journal_end(&th);
	अगर (err)
		जाओ out_err_unlock;

	reiserfs_ग_लिखो_unlock(s);
	अगर (!(*mount_flags & SB_RDONLY)) अणु
		dquot_resume(s, -1);
		reiserfs_ग_लिखो_lock(s);
		finish_unfinished(s);
		reiserfs_ग_लिखो_unlock(s);
		reiserfs_xattr_init(s, *mount_flags);
	पूर्ण

out_ok_unlocked:
	वापस 0;

out_err_unlock:
	reiserfs_ग_लिखो_unlock(s);
out_err:
	kमुक्त(new_opts);
	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_super_block(काष्ठा super_block *s, पूर्णांक offset)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा reiserfs_super_block *rs;
	पूर्णांक fs_blocksize;

	bh = sb_bपढ़ो(s, offset / s->s_blocksize);
	अगर (!bh) अणु
		reiserfs_warning(s, "sh-2006",
				 "bread failed (dev %s, block %lu, size %lu)",
				 s->s_id, offset / s->s_blocksize,
				 s->s_blocksize);
		वापस 1;
	पूर्ण

	rs = (काष्ठा reiserfs_super_block *)bh->b_data;
	अगर (!is_any_reiserfs_magic_string(rs)) अणु
		brअन्यथा(bh);
		वापस 1;
	पूर्ण
	/*
	 * ok, reiserfs signature (old or new) found in at the given offset
	 */
	fs_blocksize = sb_blocksize(rs);
	brअन्यथा(bh);
	sb_set_blocksize(s, fs_blocksize);

	bh = sb_bपढ़ो(s, offset / s->s_blocksize);
	अगर (!bh) अणु
		reiserfs_warning(s, "sh-2007",
				 "bread failed (dev %s, block %lu, size %lu)",
				 s->s_id, offset / s->s_blocksize,
				 s->s_blocksize);
		वापस 1;
	पूर्ण

	rs = (काष्ठा reiserfs_super_block *)bh->b_data;
	अगर (sb_blocksize(rs) != s->s_blocksize) अणु
		reiserfs_warning(s, "sh-2011", "can't find a reiserfs "
				 "filesystem on (dev %s, block %llu, size %lu)",
				 s->s_id,
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 s->s_blocksize);
		brअन्यथा(bh);
		वापस 1;
	पूर्ण

	अगर (rs->s_v1.s_root_block == cpu_to_le32(-1)) अणु
		brअन्यथा(bh);
		reiserfs_warning(s, "super-6519", "Unfinished reiserfsck "
				 "--rebuild-tree run detected. Please run\n"
				 "reiserfsck --rebuild-tree and wait for a "
				 "completion. If that fails\n"
				 "get newer reiserfsprogs package");
		वापस 1;
	पूर्ण

	SB_BUFFER_WITH_SB(s) = bh;
	SB_DISK_SUPER_BLOCK(s) = rs;

	/*
	 * magic is of non-standard journal fileप्रणाली, look at s_version to
	 * find which क्रमmat is in use
	 */
	अगर (is_reiserfs_jr(rs)) अणु
		अगर (sb_version(rs) == REISERFS_VERSION_2)
			reiserfs_info(s, "found reiserfs format \"3.6\""
				      " with non-standard journal\n");
		अन्यथा अगर (sb_version(rs) == REISERFS_VERSION_1)
			reiserfs_info(s, "found reiserfs format \"3.5\""
				      " with non-standard journal\n");
		अन्यथा अणु
			reiserfs_warning(s, "sh-2012", "found unknown "
					 "format \"%u\" of reiserfs with "
					 "non-standard magic", sb_version(rs));
			वापस 1;
		पूर्ण
	पूर्ण अन्यथा
		/*
		 * s_version of standard क्रमmat may contain incorrect
		 * inक्रमmation, so we just look at the magic string
		 */
		reiserfs_info(s,
			      "found reiserfs format \"%s\" with standard journal\n",
			      is_reiserfs_3_5(rs) ? "3.5" : "3.6");

	s->s_op = &reiserfs_sops;
	s->s_export_op = &reiserfs_export_ops;
#अगर_घोषित CONFIG_QUOTA
	s->s_qcop = &reiserfs_qctl_operations;
	s->dq_op = &reiserfs_quota_operations;
	s->s_quota_types = QTYPE_MASK_USR | QTYPE_MASK_GRP;
#पूर्ण_अगर

	/*
	 * new क्रमmat is limited by the 32 bit wide i_blocks field, want to
	 * be one full block below that.
	 */
	s->s_maxbytes = (512LL << 32) - s->s_blocksize;
	वापस 0;
पूर्ण

/* after journal replay, reपढ़ो all biपंचांगap and super blocks */
अटल पूर्णांक reपढ़ो_meta_blocks(काष्ठा super_block *s)
अणु
	ll_rw_block(REQ_OP_READ, 0, 1, &SB_BUFFER_WITH_SB(s));
	रुको_on_buffer(SB_BUFFER_WITH_SB(s));
	अगर (!buffer_uptodate(SB_BUFFER_WITH_SB(s))) अणु
		reiserfs_warning(s, "reiserfs-2504", "error reading the super");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* hash detection stuff */

/*
 * अगर root directory is empty - we set शेष - Yura's - hash and
 * warn about it
 * FIXME: we look क्रम only one name in a directory. If tea and yura
 * both have the same value - we ask user to send report to the
 * mailing list
 */
अटल __u32 find_hash_out(काष्ठा super_block *s)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode;
	काष्ठा cpu_key key;
	INITIALIZE_PATH(path);
	काष्ठा reiserfs_dir_entry de;
	काष्ठा reiserfs_de_head *deh;
	__u32 hash = DEFAULT_HASH;
	__u32 deh_hashval, teahash, r5hash, yurahash;

	inode = d_inode(s->s_root);

	make_cpu_key(&key, inode, ~0, TYPE_सूचीENTRY, 3);
	retval = search_by_entry_key(s, &key, &path, &de);
	अगर (retval == IO_ERROR) अणु
		pathrअन्यथा(&path);
		वापस UNSET_HASH;
	पूर्ण
	अगर (retval == NAME_NOT_FOUND)
		de.de_entry_num--;

	set_de_name_and_namelen(&de);
	deh = de.de_deh + de.de_entry_num;

	अगर (deh_offset(deh) == DOT_DOT_OFFSET) अणु
		/* allow override in this हाल */
		अगर (reiserfs_rupasov_hash(s))
			hash = YURA_HASH;
		reiserfs_info(s, "FS seems to be empty, autodetect is using the default hash\n");
		जाओ out;
	पूर्ण

	deh_hashval = GET_HASH_VALUE(deh_offset(deh));
	r5hash = GET_HASH_VALUE(r5_hash(de.de_name, de.de_namelen));
	teahash = GET_HASH_VALUE(keyed_hash(de.de_name, de.de_namelen));
	yurahash = GET_HASH_VALUE(yura_hash(de.de_name, de.de_namelen));

	अगर ((teahash == r5hash && deh_hashval == r5hash) ||
	    (teahash == yurahash && deh_hashval == yurahash) ||
	    (r5hash == yurahash && deh_hashval == yurahash)) अणु
		reiserfs_warning(s, "reiserfs-2506",
				 "Unable to automatically detect hash "
				 "function. Please mount with -o "
				 "hash={tea,rupasov,r5}");
		hash = UNSET_HASH;
		जाओ out;
	पूर्ण

	अगर (deh_hashval == yurahash)
		hash = YURA_HASH;
	अन्यथा अगर (deh_hashval == teahash)
		hash = TEA_HASH;
	अन्यथा अगर (deh_hashval == r5hash)
		hash = R5_HASH;
	अन्यथा अणु
		reiserfs_warning(s, "reiserfs-2506",
				 "Unrecognised hash function");
		hash = UNSET_HASH;
	पूर्ण
out:
	pathrअन्यथा(&path);
	वापस hash;
पूर्ण

/* finds out which hash names are sorted with */
अटल पूर्णांक what_hash(काष्ठा super_block *s)
अणु
	__u32 code;

	code = sb_hash_function_code(SB_DISK_SUPER_BLOCK(s));

	/*
	 * reiserfs_hash_detect() == true अगर any of the hash mount options
	 * were used.  We must check them to make sure the user isn't
	 * using a bad hash value
	 */
	अगर (code == UNSET_HASH || reiserfs_hash_detect(s))
		code = find_hash_out(s);

	अगर (code != UNSET_HASH && reiserfs_hash_detect(s)) अणु
		/*
		 * detection has found the hash, and we must check against the
		 * mount options
		 */
		अगर (reiserfs_rupasov_hash(s) && code != YURA_HASH) अणु
			reiserfs_warning(s, "reiserfs-2507",
					 "Error, %s hash detected, "
					 "unable to force rupasov hash",
					 reiserfs_hashname(code));
			code = UNSET_HASH;
		पूर्ण अन्यथा अगर (reiserfs_tea_hash(s) && code != TEA_HASH) अणु
			reiserfs_warning(s, "reiserfs-2508",
					 "Error, %s hash detected, "
					 "unable to force tea hash",
					 reiserfs_hashname(code));
			code = UNSET_HASH;
		पूर्ण अन्यथा अगर (reiserfs_r5_hash(s) && code != R5_HASH) अणु
			reiserfs_warning(s, "reiserfs-2509",
					 "Error, %s hash detected, "
					 "unable to force r5 hash",
					 reiserfs_hashname(code));
			code = UNSET_HASH;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * find_hash_out was not called or
		 * could not determine the hash
		 */
		अगर (reiserfs_rupasov_hash(s)) अणु
			code = YURA_HASH;
		पूर्ण अन्यथा अगर (reiserfs_tea_hash(s)) अणु
			code = TEA_HASH;
		पूर्ण अन्यथा अगर (reiserfs_r5_hash(s)) अणु
			code = R5_HASH;
		पूर्ण
	पूर्ण

	/*
	 * अगर we are mounted RW, and we have a new valid hash code, update
	 * the super
	 */
	अगर (code != UNSET_HASH &&
	    !sb_rकरोnly(s) &&
	    code != sb_hash_function_code(SB_DISK_SUPER_BLOCK(s))) अणु
		set_sb_hash_function_code(SB_DISK_SUPER_BLOCK(s), code);
	पूर्ण
	वापस code;
पूर्ण

/* वापस poपूर्णांकer to appropriate function */
अटल hashf_t hash_function(काष्ठा super_block *s)
अणु
	चयन (what_hash(s)) अणु
	हाल TEA_HASH:
		reiserfs_info(s, "Using tea hash to sort names\n");
		वापस keyed_hash;
	हाल YURA_HASH:
		reiserfs_info(s, "Using rupasov hash to sort names\n");
		वापस yura_hash;
	हाल R5_HASH:
		reiserfs_info(s, "Using r5 hash to sort names\n");
		वापस r5_hash;
	पूर्ण
	वापस शून्य;
पूर्ण

/* this is used to set up correct value क्रम old partitions */
अटल पूर्णांक function2code(hashf_t func)
अणु
	अगर (func == keyed_hash)
		वापस TEA_HASH;
	अगर (func == yura_hash)
		वापस YURA_HASH;
	अगर (func == r5_hash)
		वापस R5_HASH;

	BUG();			/* should never happen */

	वापस 0;
पूर्ण

#घोषणा SWARN(silent, s, id, ...)			\
	अगर (!(silent))				\
		reiserfs_warning(s, id, __VA_ARGS__)

अटल पूर्णांक reiserfs_fill_super(काष्ठा super_block *s, व्योम *data, पूर्णांक silent)
अणु
	काष्ठा inode *root_inode;
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक old_क्रमmat = 0;
	अचिन्हित दीर्घ blocks;
	अचिन्हित पूर्णांक commit_max_age = 0;
	पूर्णांक jinit_करोne = 0;
	काष्ठा reiserfs_iget_args args;
	काष्ठा reiserfs_super_block *rs;
	अक्षर *jdev_name;
	काष्ठा reiserfs_sb_info *sbi;
	पूर्णांक errval = -EINVAL;
	अक्षर *qf_names[REISERFS_MAXQUOTAS] = अणुपूर्ण;
	अचिन्हित पूर्णांक qfmt = 0;

	sbi = kzalloc(माप(काष्ठा reiserfs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;
	s->s_fs_info = sbi;
	/* Set शेष values क्रम options: non-aggressive tails, RO on errors */
	sbi->s_mount_opt |= (1 << REISERFS_SMALLTAIL);
	sbi->s_mount_opt |= (1 << REISERFS_ERROR_RO);
	sbi->s_mount_opt |= (1 << REISERFS_BARRIER_FLUSH);
	/* no pपुनः_स्मृतिation minimum, be smart in reiserfs_file_ग_लिखो instead */
	sbi->s_alloc_options.pपुनः_स्मृतिmin = 0;
	/* Pपुनः_स्मृतिate by 16 blocks (17-1) at once */
	sbi->s_alloc_options.pपुनः_स्मृतिsize = 17;
	/* setup शेष block allocator options */
	reiserfs_init_alloc_options(s);

	spin_lock_init(&sbi->old_work_lock);
	INIT_DELAYED_WORK(&sbi->old_work, flush_old_commits);
	mutex_init(&sbi->lock);
	sbi->lock_depth = -1;

	sbi->commit_wq = alloc_workqueue("reiserfs/%s", WQ_MEM_RECLAIM, 0,
					 s->s_id);
	अगर (!sbi->commit_wq) अणु
		SWARN(silent, s, "", "Cannot allocate commit workqueue");
		errval = -ENOMEM;
		जाओ error_unlocked;
	पूर्ण

	jdev_name = शून्य;
	अगर (reiserfs_parse_options
	    (s, (अक्षर *)data, &sbi->s_mount_opt, &blocks, &jdev_name,
	     &commit_max_age, qf_names, &qfmt) == 0) अणु
		जाओ error_unlocked;
	पूर्ण
	अगर (jdev_name && jdev_name[0]) अणु
		sbi->s_jdev = kstrdup(jdev_name, GFP_KERNEL);
		अगर (!sbi->s_jdev) अणु
			SWARN(silent, s, "", "Cannot allocate memory for "
				"journal device name");
			जाओ error_unlocked;
		पूर्ण
	पूर्ण
#अगर_घोषित CONFIG_QUOTA
	handle_quota_files(s, qf_names, &qfmt);
#पूर्ण_अगर

	अगर (blocks) अणु
		SWARN(silent, s, "jmacd-7", "resize option for remount only");
		जाओ error_unlocked;
	पूर्ण

	/*
	 * try old क्रमmat (undistributed biपंचांगap, super block in 8-th 1k
	 * block of a device)
	 */
	अगर (!पढ़ो_super_block(s, REISERFS_OLD_DISK_OFFSET_IN_BYTES))
		old_क्रमmat = 1;

	/*
	 * try new क्रमmat (64-th 1k block), which can contain reiserfs
	 * super block
	 */
	अन्यथा अगर (पढ़ो_super_block(s, REISERFS_DISK_OFFSET_IN_BYTES)) अणु
		SWARN(silent, s, "sh-2021", "can not find reiserfs on %s",
		      s->s_id);
		जाओ error_unlocked;
	पूर्ण

	s->s_समय_min = 0;
	s->s_समय_max = U32_MAX;

	rs = SB_DISK_SUPER_BLOCK(s);
	/*
	 * Let's करो basic sanity check to verअगरy that underlying device is not
	 * smaller than the fileप्रणाली. If the check fails then पात and
	 * scream, because bad stuff will happen otherwise.
	 */
	अगर (s->s_bdev && s->s_bdev->bd_inode
	    && i_size_पढ़ो(s->s_bdev->bd_inode) <
	    sb_block_count(rs) * sb_blocksize(rs)) अणु
		SWARN(silent, s, "", "Filesystem cannot be "
		      "mounted because it is bigger than the device");
		SWARN(silent, s, "", "You may need to run fsck "
		      "or increase size of your LVM partition");
		SWARN(silent, s, "", "Or may be you forgot to "
		      "reboot after fdisk when it told you to");
		जाओ error_unlocked;
	पूर्ण

	sbi->s_mount_state = SB_REISERFS_STATE(s);
	sbi->s_mount_state = REISERFS_VALID_FS;

	अगर ((errval = reiserfs_init_biपंचांगap_cache(s))) अणु
		SWARN(silent, s, "jmacd-8", "unable to read bitmap");
		जाओ error_unlocked;
	पूर्ण

	errval = -EINVAL;
#अगर_घोषित CONFIG_REISERFS_CHECK
	SWARN(silent, s, "", "CONFIG_REISERFS_CHECK is set ON");
	SWARN(silent, s, "", "- it is slow mode for debugging.");
#पूर्ण_अगर

	/* make data=ordered the शेष */
	अगर (!reiserfs_data_log(s) && !reiserfs_data_ordered(s) &&
	    !reiserfs_data_ग_लिखोback(s)) अणु
		sbi->s_mount_opt |= (1 << REISERFS_DATA_ORDERED);
	पूर्ण

	अगर (reiserfs_data_log(s)) अणु
		reiserfs_info(s, "using journaled data mode\n");
	पूर्ण अन्यथा अगर (reiserfs_data_ordered(s)) अणु
		reiserfs_info(s, "using ordered data mode\n");
	पूर्ण अन्यथा अणु
		reiserfs_info(s, "using writeback data mode\n");
	पूर्ण
	अगर (reiserfs_barrier_flush(s)) अणु
		prपूर्णांकk("reiserfs: using flush barriers\n");
	पूर्ण

	अगर (journal_init(s, jdev_name, old_क्रमmat, commit_max_age)) अणु
		SWARN(silent, s, "sh-2022",
		      "unable to initialize journal space");
		जाओ error_unlocked;
	पूर्ण अन्यथा अणु
		/*
		 * once this is set, journal_release must be called
		 * अगर we error out of the mount
		 */
		jinit_करोne = 1;
	पूर्ण

	अगर (reपढ़ो_meta_blocks(s)) अणु
		SWARN(silent, s, "jmacd-9",
		      "unable to reread meta blocks after journal init");
		जाओ error_unlocked;
	पूर्ण

	अगर (replay_only(s))
		जाओ error_unlocked;

	s->s_xattr = reiserfs_xattr_handlers;

	अगर (bdev_पढ़ो_only(s->s_bdev) && !sb_rकरोnly(s)) अणु
		SWARN(silent, s, "clm-7000",
		      "Detected readonly device, marking FS readonly");
		s->s_flags |= SB_RDONLY;
	पूर्ण
	args.objectid = REISERFS_ROOT_OBJECTID;
	args.dirid = REISERFS_ROOT_PARENT_OBJECTID;
	root_inode =
	    iget5_locked(s, REISERFS_ROOT_OBJECTID, reiserfs_find_actor,
			 reiserfs_init_locked_inode, (व्योम *)&args);
	अगर (!root_inode) अणु
		SWARN(silent, s, "jmacd-10", "get root inode failed");
		जाओ error_unlocked;
	पूर्ण

	/*
	 * This path assumed to be called with the BKL in the old बार.
	 * Now we have inherited the big reiserfs lock from it and many
	 * reiserfs helpers called in the mount path and अन्यथाwhere require
	 * this lock to be held even अगर it's not always necessary. Let's be
	 * conservative and hold it early. The winकरोw can be reduced after
	 * careful review of the code.
	 */
	reiserfs_ग_लिखो_lock(s);

	अगर (root_inode->i_state & I_NEW) अणु
		reiserfs_पढ़ो_locked_inode(root_inode, &args);
		unlock_new_inode(root_inode);
	पूर्ण

	s->s_root = d_make_root(root_inode);
	अगर (!s->s_root)
		जाओ error;
	/* define and initialize hash function */
	sbi->s_hash_function = hash_function(s);
	अगर (sbi->s_hash_function == शून्य) अणु
		dput(s->s_root);
		s->s_root = शून्य;
		जाओ error;
	पूर्ण

	अगर (is_reiserfs_3_5(rs)
	    || (is_reiserfs_jr(rs) && SB_VERSION(s) == REISERFS_VERSION_1))
		set_bit(REISERFS_3_5, &sbi->s_properties);
	अन्यथा अगर (old_क्रमmat)
		set_bit(REISERFS_OLD_FORMAT, &sbi->s_properties);
	अन्यथा
		set_bit(REISERFS_3_6, &sbi->s_properties);

	अगर (!sb_rकरोnly(s)) अणु

		errval = journal_begin(&th, s, 1);
		अगर (errval) अणु
			dput(s->s_root);
			s->s_root = शून्य;
			जाओ error;
		पूर्ण
		reiserfs_prepare_क्रम_journal(s, SB_BUFFER_WITH_SB(s), 1);

		set_sb_umount_state(rs, REISERFS_ERROR_FS);
		set_sb_fs_state(rs, 0);

		/*
		 * Clear out s_bmap_nr अगर it would wrap. We can handle this
		 * हाल, but older revisions can't. This will cause the
		 * file प्रणाली to fail mount on those older implementations,
		 * aव्योमing corruption. -jeffm
		 */
		अगर (bmap_would_wrap(reiserfs_bmap_count(s)) &&
		    sb_bmap_nr(rs) != 0) अणु
			reiserfs_warning(s, "super-2030", "This file system "
					"claims to use %u bitmap blocks in "
					"its super block, but requires %u. "
					"Clearing to zero.", sb_bmap_nr(rs),
					reiserfs_bmap_count(s));

			set_sb_bmap_nr(rs, 0);
		पूर्ण

		अगर (old_क्रमmat_only(s)) अणु
			/*
			 * fileप्रणाली of क्रमmat 3.5 either with standard
			 * or non-standard journal
			 */
			अगर (convert_reiserfs(s)) अणु
				/* and -o conv is given */
				अगर (!silent)
					reiserfs_info(s,
						      "converting 3.5 filesystem to the 3.6 format");

				अगर (is_reiserfs_3_5(rs))
					/*
					 * put magic string of 3.6 क्रमmat.
					 * 2.2 will not be able to
					 * mount this fileप्रणाली anymore
					 */
					स_नकल(rs->s_v1.s_magic,
					       reiserfs_3_6_magic_string,
					       माप
					       (reiserfs_3_6_magic_string));

				set_sb_version(rs, REISERFS_VERSION_2);
				reiserfs_convert_objectid_map_v1(s);
				set_bit(REISERFS_3_6, &sbi->s_properties);
				clear_bit(REISERFS_3_5, &sbi->s_properties);
			पूर्ण अन्यथा अगर (!silent) अणु
				reiserfs_info(s, "using 3.5.x disk format\n");
			पूर्ण
		पूर्ण अन्यथा
			set_sb_mnt_count(rs, sb_mnt_count(rs) + 1);


		journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));
		errval = journal_end(&th);
		अगर (errval) अणु
			dput(s->s_root);
			s->s_root = शून्य;
			जाओ error;
		पूर्ण

		reiserfs_ग_लिखो_unlock(s);
		अगर ((errval = reiserfs_lookup_privroot(s)) ||
		    (errval = reiserfs_xattr_init(s, s->s_flags))) अणु
			dput(s->s_root);
			s->s_root = शून्य;
			जाओ error_unlocked;
		पूर्ण
		reiserfs_ग_लिखो_lock(s);

		/*
		 * look क्रम files which were to be हटाओd in previous session
		 */
		finish_unfinished(s);
	पूर्ण अन्यथा अणु
		अगर (old_क्रमmat_only(s) && !silent) अणु
			reiserfs_info(s, "using 3.5.x disk format\n");
		पूर्ण

		reiserfs_ग_लिखो_unlock(s);
		अगर ((errval = reiserfs_lookup_privroot(s)) ||
		    (errval = reiserfs_xattr_init(s, s->s_flags))) अणु
			dput(s->s_root);
			s->s_root = शून्य;
			जाओ error_unlocked;
		पूर्ण
		reiserfs_ग_लिखो_lock(s);
	पूर्ण
	/*
	 * mark hash in super block: it could be unset. overग_लिखो should be ok
	 */
	set_sb_hash_function_code(rs, function2code(sbi->s_hash_function));

	handle_attrs(s);

	reiserfs_proc_info_init(s);

	init_रुकोqueue_head(&(sbi->s_रुको));
	spin_lock_init(&sbi->biपंचांगap_lock);

	reiserfs_ग_लिखो_unlock(s);

	वापस (0);

error:
	reiserfs_ग_लिखो_unlock(s);

error_unlocked:
	/* समाप्त the commit thपढ़ो, मुक्त journal ram */
	अगर (jinit_करोne) अणु
		reiserfs_ग_लिखो_lock(s);
		journal_release_error(शून्य, s);
		reiserfs_ग_लिखो_unlock(s);
	पूर्ण

	अगर (sbi->commit_wq)
		destroy_workqueue(sbi->commit_wq);

	reiserfs_cancel_old_flush(s);

	reiserfs_मुक्त_biपंचांगap_cache(s);
	अगर (SB_BUFFER_WITH_SB(s))
		brअन्यथा(SB_BUFFER_WITH_SB(s));
#अगर_घोषित CONFIG_QUOTA
	अणु
		पूर्णांक j;
		क्रम (j = 0; j < REISERFS_MAXQUOTAS; j++)
			kमुक्त(qf_names[j]);
	पूर्ण
#पूर्ण_अगर
	kमुक्त(sbi->s_jdev);
	kमुक्त(sbi);

	s->s_fs_info = शून्य;
	वापस errval;
पूर्ण

अटल पूर्णांक reiserfs_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा reiserfs_super_block *rs = SB_DISK_SUPER_BLOCK(dentry->d_sb);

	buf->f_namelen = (REISERFS_MAX_NAME(s->s_blocksize));
	buf->f_bमुक्त = sb_मुक्त_blocks(rs);
	buf->f_bavail = buf->f_bमुक्त;
	buf->f_blocks = sb_block_count(rs) - sb_bmap_nr(rs) - 1;
	buf->f_bsize = dentry->d_sb->s_blocksize;
	/* changed to accommodate gcc folks. */
	buf->f_type = REISERFS_SUPER_MAGIC;
	buf->f_fsid.val[0] = (u32)crc32_le(0, rs->s_uuid, माप(rs->s_uuid)/2);
	buf->f_fsid.val[1] = (u32)crc32_le(0, rs->s_uuid + माप(rs->s_uuid)/2,
				माप(rs->s_uuid)/2);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_QUOTA
अटल पूर्णांक reiserfs_ग_लिखो_dquot(काष्ठा dquot *dquot)
अणु
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक ret, err;
	पूर्णांक depth;

	reiserfs_ग_लिखो_lock(dquot->dq_sb);
	ret =
	    journal_begin(&th, dquot->dq_sb,
			  REISERFS_QUOTA_TRANS_BLOCKS(dquot->dq_sb));
	अगर (ret)
		जाओ out;
	depth = reiserfs_ग_लिखो_unlock_nested(dquot->dq_sb);
	ret = dquot_commit(dquot);
	reiserfs_ग_लिखो_lock_nested(dquot->dq_sb, depth);
	err = journal_end(&th);
	अगर (!ret && err)
		ret = err;
out:
	reiserfs_ग_लिखो_unlock(dquot->dq_sb);
	वापस ret;
पूर्ण

अटल पूर्णांक reiserfs_acquire_dquot(काष्ठा dquot *dquot)
अणु
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक ret, err;
	पूर्णांक depth;

	reiserfs_ग_लिखो_lock(dquot->dq_sb);
	ret =
	    journal_begin(&th, dquot->dq_sb,
			  REISERFS_QUOTA_INIT_BLOCKS(dquot->dq_sb));
	अगर (ret)
		जाओ out;
	depth = reiserfs_ग_लिखो_unlock_nested(dquot->dq_sb);
	ret = dquot_acquire(dquot);
	reiserfs_ग_लिखो_lock_nested(dquot->dq_sb, depth);
	err = journal_end(&th);
	अगर (!ret && err)
		ret = err;
out:
	reiserfs_ग_लिखो_unlock(dquot->dq_sb);
	वापस ret;
पूर्ण

अटल पूर्णांक reiserfs_release_dquot(काष्ठा dquot *dquot)
अणु
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक ret, err;

	reiserfs_ग_लिखो_lock(dquot->dq_sb);
	ret =
	    journal_begin(&th, dquot->dq_sb,
			  REISERFS_QUOTA_DEL_BLOCKS(dquot->dq_sb));
	reiserfs_ग_लिखो_unlock(dquot->dq_sb);
	अगर (ret) अणु
		/* Release dquot anyway to aव्योम endless cycle in dqput() */
		dquot_release(dquot);
		जाओ out;
	पूर्ण
	ret = dquot_release(dquot);
	reiserfs_ग_लिखो_lock(dquot->dq_sb);
	err = journal_end(&th);
	अगर (!ret && err)
		ret = err;
	reiserfs_ग_लिखो_unlock(dquot->dq_sb);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक reiserfs_mark_dquot_dirty(काष्ठा dquot *dquot)
अणु
	/* Are we journaling quotas? */
	अगर (REISERFS_SB(dquot->dq_sb)->s_qf_names[USRQUOTA] ||
	    REISERFS_SB(dquot->dq_sb)->s_qf_names[GRPQUOTA]) अणु
		dquot_mark_dquot_dirty(dquot);
		वापस reiserfs_ग_लिखो_dquot(dquot);
	पूर्ण अन्यथा
		वापस dquot_mark_dquot_dirty(dquot);
पूर्ण

अटल पूर्णांक reiserfs_ग_लिखो_info(काष्ठा super_block *sb, पूर्णांक type)
अणु
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक ret, err;
	पूर्णांक depth;

	/* Data block + inode block */
	reiserfs_ग_लिखो_lock(sb);
	ret = journal_begin(&th, sb, 2);
	अगर (ret)
		जाओ out;
	depth = reiserfs_ग_लिखो_unlock_nested(sb);
	ret = dquot_commit_info(sb, type);
	reiserfs_ग_लिखो_lock_nested(sb, depth);
	err = journal_end(&th);
	अगर (!ret && err)
		ret = err;
out:
	reiserfs_ग_लिखो_unlock(sb);
	वापस ret;
पूर्ण

/*
 * Turn on quotas during mount समय - we need to find the quota file and such...
 */
अटल पूर्णांक reiserfs_quota_on_mount(काष्ठा super_block *sb, पूर्णांक type)
अणु
	वापस dquot_quota_on_mount(sb, REISERFS_SB(sb)->s_qf_names[type],
					REISERFS_SB(sb)->s_jquota_fmt, type);
पूर्ण

/*
 * Standard function to be called on quota_on
 */
अटल पूर्णांक reiserfs_quota_on(काष्ठा super_block *sb, पूर्णांक type, पूर्णांक क्रमmat_id,
			     स्थिर काष्ठा path *path)
अणु
	पूर्णांक err;
	काष्ठा inode *inode;
	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक opt = type == USRQUOTA ? REISERFS_USRQUOTA : REISERFS_GRPQUOTA;

	reiserfs_ग_लिखो_lock(sb);
	अगर (!(REISERFS_SB(sb)->s_mount_opt & (1 << opt))) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Quotafile not on the same fileप्रणाली? */
	अगर (path->dentry->d_sb != sb) अणु
		err = -EXDEV;
		जाओ out;
	पूर्ण
	inode = d_inode(path->dentry);
	/*
	 * We must not pack tails क्रम quota files on reiserfs क्रम quota
	 * IO to work
	 */
	अगर (!(REISERFS_I(inode)->i_flags & i_nopack_mask)) अणु
		err = reiserfs_unpack(inode);
		अगर (err) अणु
			reiserfs_warning(sb, "super-6520",
				"Unpacking tail of quota file failed"
				" (%d). Cannot turn on quotas.", err);
			err = -EINVAL;
			जाओ out;
		पूर्ण
		mark_inode_dirty(inode);
	पूर्ण
	/* Journaling quota? */
	अगर (REISERFS_SB(sb)->s_qf_names[type]) अणु
		/* Quotafile not of fs root? */
		अगर (path->dentry->d_parent != sb->s_root)
			reiserfs_warning(sb, "super-6521",
				 "Quota file not on filesystem root. "
				 "Journalled quota will not work.");
	पूर्ण

	/*
	 * When we journal data on quota file, we have to flush journal to see
	 * all updates to the file when we bypass pagecache...
	 */
	अगर (reiserfs_file_data_log(inode)) अणु
		/* Just start temporary transaction and finish it */
		err = journal_begin(&th, sb, 1);
		अगर (err)
			जाओ out;
		err = journal_end_sync(&th);
		अगर (err)
			जाओ out;
	पूर्ण
	reiserfs_ग_लिखो_unlock(sb);
	err = dquot_quota_on(sb, type, क्रमmat_id, path);
	अगर (!err) अणु
		inode_lock(inode);
		REISERFS_I(inode)->i_attrs |= REISERFS_IMMUTABLE_FL |
					      REISERFS_NOATIME_FL;
		inode_set_flags(inode, S_IMMUTABLE | S_NOATIME,
				S_IMMUTABLE | S_NOATIME);
		inode_unlock(inode);
		mark_inode_dirty(inode);
	पूर्ण
	वापस err;
out:
	reiserfs_ग_लिखो_unlock(sb);
	वापस err;
पूर्ण

अटल पूर्णांक reiserfs_quota_off(काष्ठा super_block *sb, पूर्णांक type)
अणु
	पूर्णांक err;
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];

	अगर (!inode || !igrab(inode))
		जाओ out;

	err = dquot_quota_off(sb, type);
	अगर (err)
		जाओ out_put;

	inode_lock(inode);
	REISERFS_I(inode)->i_attrs &= ~(REISERFS_IMMUTABLE_FL |
					REISERFS_NOATIME_FL);
	inode_set_flags(inode, 0, S_IMMUTABLE | S_NOATIME);
	inode_unlock(inode);
	mark_inode_dirty(inode);
out_put:
	iput(inode);
	वापस err;
out:
	वापस dquot_quota_off(sb, type);
पूर्ण

/*
 * Read data from quotafile - aव्योम pagecache and such because we cannot afक्रमd
 * acquiring the locks... As quota files are never truncated and quota code
 * itself serializes the operations (and no one अन्यथा should touch the files)
 * we करोn't have to be afraid of races
 */
अटल sमाप_प्रकार reiserfs_quota_पढ़ो(काष्ठा super_block *sb, पूर्णांक type, अक्षर *data,
				   माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	अचिन्हित दीर्घ blk = off >> sb->s_blocksize_bits;
	पूर्णांक err = 0, offset = off & (sb->s_blocksize - 1), tocopy;
	माप_प्रकार toपढ़ो;
	काष्ठा buffer_head पंचांगp_bh, *bh;
	loff_t i_size = i_size_पढ़ो(inode);

	अगर (off > i_size)
		वापस 0;
	अगर (off + len > i_size)
		len = i_size - off;
	toपढ़ो = len;
	जबतक (toपढ़ो > 0) अणु
		tocopy =
		    sb->s_blocksize - offset <
		    toपढ़ो ? sb->s_blocksize - offset : toपढ़ो;
		पंचांगp_bh.b_state = 0;
		/*
		 * Quota files are without tails so we can safely
		 * use this function
		 */
		reiserfs_ग_लिखो_lock(sb);
		err = reiserfs_get_block(inode, blk, &पंचांगp_bh, 0);
		reiserfs_ग_लिखो_unlock(sb);
		अगर (err)
			वापस err;
		अगर (!buffer_mapped(&पंचांगp_bh))	/* A hole? */
			स_रखो(data, 0, tocopy);
		अन्यथा अणु
			bh = sb_bपढ़ो(sb, पंचांगp_bh.b_blocknr);
			अगर (!bh)
				वापस -EIO;
			स_नकल(data, bh->b_data + offset, tocopy);
			brअन्यथा(bh);
		पूर्ण
		offset = 0;
		toपढ़ो -= tocopy;
		data += tocopy;
		blk++;
	पूर्ण
	वापस len;
पूर्ण

/*
 * Write to quotafile (we know the transaction is alपढ़ोy started and has
 * enough credits)
 */
अटल sमाप_प्रकार reiserfs_quota_ग_लिखो(काष्ठा super_block *sb, पूर्णांक type,
				    स्थिर अक्षर *data, माप_प्रकार len, loff_t off)
अणु
	काष्ठा inode *inode = sb_dqopt(sb)->files[type];
	अचिन्हित दीर्घ blk = off >> sb->s_blocksize_bits;
	पूर्णांक err = 0, offset = off & (sb->s_blocksize - 1), tocopy;
	पूर्णांक journal_quota = REISERFS_SB(sb)->s_qf_names[type] != शून्य;
	माप_प्रकार toग_लिखो = len;
	काष्ठा buffer_head पंचांगp_bh, *bh;

	अगर (!current->journal_info) अणु
		prपूर्णांकk(KERN_WARNING "reiserfs: Quota write (off=%llu, len=%llu) cancelled because transaction is not started.\n",
			(अचिन्हित दीर्घ दीर्घ)off, (अचिन्हित दीर्घ दीर्घ)len);
		वापस -EIO;
	पूर्ण
	जबतक (toग_लिखो > 0) अणु
		tocopy = sb->s_blocksize - offset < toग_लिखो ?
		    sb->s_blocksize - offset : toग_लिखो;
		पंचांगp_bh.b_state = 0;
		reiserfs_ग_लिखो_lock(sb);
		err = reiserfs_get_block(inode, blk, &पंचांगp_bh, GET_BLOCK_CREATE);
		reiserfs_ग_लिखो_unlock(sb);
		अगर (err)
			जाओ out;
		अगर (offset || tocopy != sb->s_blocksize)
			bh = sb_bपढ़ो(sb, पंचांगp_bh.b_blocknr);
		अन्यथा
			bh = sb_getblk(sb, पंचांगp_bh.b_blocknr);
		अगर (!bh) अणु
			err = -EIO;
			जाओ out;
		पूर्ण
		lock_buffer(bh);
		स_नकल(bh->b_data + offset, data, tocopy);
		flush_dcache_page(bh->b_page);
		set_buffer_uptodate(bh);
		unlock_buffer(bh);
		reiserfs_ग_लिखो_lock(sb);
		reiserfs_prepare_क्रम_journal(sb, bh, 1);
		journal_mark_dirty(current->journal_info, bh);
		अगर (!journal_quota)
			reiserfs_add_ordered_list(inode, bh);
		reiserfs_ग_लिखो_unlock(sb);
		brअन्यथा(bh);
		offset = 0;
		toग_लिखो -= tocopy;
		data += tocopy;
		blk++;
	पूर्ण
out:
	अगर (len == toग_लिखो)
		वापस err;
	अगर (inode->i_size < off + len - toग_लिखो)
		i_size_ग_लिखो(inode, off + len - toग_लिखो);
	inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
	वापस len - toग_लिखो;
पूर्ण

#पूर्ण_अगर

अटल काष्ठा dentry *get_super_block(काष्ठा file_प्रणाली_type *fs_type,
			   पूर्णांक flags, स्थिर अक्षर *dev_name,
			   व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, reiserfs_fill_super);
पूर्ण

अटल पूर्णांक __init init_reiserfs_fs(व्योम)
अणु
	पूर्णांक ret;

	ret = init_inodecache();
	अगर (ret)
		वापस ret;

	reiserfs_proc_info_global_init();

	ret = रेजिस्टर_fileप्रणाली(&reiserfs_fs_type);
	अगर (ret)
		जाओ out;

	वापस 0;
out:
	reiserfs_proc_info_global_करोne();
	destroy_inodecache();

	वापस ret;
पूर्ण

अटल व्योम __निकास निकास_reiserfs_fs(व्योम)
अणु
	reiserfs_proc_info_global_करोne();
	unरेजिस्टर_fileप्रणाली(&reiserfs_fs_type);
	destroy_inodecache();
पूर्ण

काष्ठा file_प्रणाली_type reiserfs_fs_type = अणु
	.owner = THIS_MODULE,
	.name = "reiserfs",
	.mount = get_super_block,
	.समाप्त_sb = reiserfs_समाप्त_sb,
	.fs_flags = FS_REQUIRES_DEV,
पूर्ण;
MODULE_ALIAS_FS("reiserfs");

MODULE_DESCRIPTION("ReiserFS journaled filesystem");
MODULE_AUTHOR("Hans Reiser <reiser@namesys.com>");
MODULE_LICENSE("GPL");

module_init(init_reiserfs_fs);
module_निकास(निकास_reiserfs_fs);
