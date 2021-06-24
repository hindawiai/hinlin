<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ext4_jbd2.h
 *
 * Written by Stephen C. Tweedie <sct@redhat.com>, 1999
 *
 * Copyright 1998--1999 Red Hat corp --- All Rights Reserved
 *
 * Ext4-specअगरic journaling extensions.
 */

#अगर_अघोषित _EXT4_JBD2_H
#घोषणा _EXT4_JBD2_H

#समावेश <linux/fs.h>
#समावेश <linux/jbd2.h>
#समावेश "ext4.h"

#घोषणा EXT4_JOURNAL(inode)	(EXT4_SB((inode)->i_sb)->s_journal)

/* Define the number of blocks we need to account to a transaction to
 * modअगरy one block of data.
 *
 * We may have to touch one inode, one biपंचांगap buffer, up to three
 * indirection blocks, the group and superblock summaries, and the data
 * block to complete the transaction.
 *
 * For extents-enabled fs we may have to allocate and modअगरy up to
 * 5 levels of tree, data block (क्रम each of these we need biपंचांगap + group
 * summaries), root which is stored in the inode, sb
 */

#घोषणा EXT4_SINGLEDATA_TRANS_BLOCKS(sb)				\
	(ext4_has_feature_extents(sb) ? 20U : 8U)

/* Extended attribute operations touch at most two data buffers,
 * two biपंचांगap buffers, and two group summaries, in addition to the inode
 * and the superblock, which are alपढ़ोy accounted क्रम. */

#घोषणा EXT4_XATTR_TRANS_BLOCKS		6U

/* Define the minimum size क्रम a transaction which modअगरies data.  This
 * needs to take पूर्णांकo account the fact that we may end up modअगरying two
 * quota files too (one क्रम the group, one क्रम the user quota).  The
 * superblock only माला_लो updated once, of course, so करोn't bother
 * counting that again क्रम the quota updates. */

#घोषणा EXT4_DATA_TRANS_BLOCKS(sb)	(EXT4_SINGLEDATA_TRANS_BLOCKS(sb) + \
					 EXT4_XATTR_TRANS_BLOCKS - 2 + \
					 EXT4_MAXQUOTAS_TRANS_BLOCKS(sb))

/*
 * Define the number of metadata blocks we need to account to modअगरy data.
 *
 * This include super block, inode block, quota blocks and xattr blocks
 */
#घोषणा EXT4_META_TRANS_BLOCKS(sb)	(EXT4_XATTR_TRANS_BLOCKS + \
					EXT4_MAXQUOTAS_TRANS_BLOCKS(sb))

/* Define an arbitrary limit क्रम the amount of data we will anticipate
 * writing to any given transaction.  For unbounded transactions such as
 * ग_लिखो(2) and truncate(2) we can ग_लिखो more than this, but we always
 * start off at the maximum transaction size and grow the transaction
 * optimistically as we go. */

#घोषणा EXT4_MAX_TRANS_DATA		64U

/* We अवरोध up a large truncate or ग_लिखो transaction once the handle's
 * buffer credits माला_लो this low, we need either to extend the
 * transaction or to start a new one.  Reserve enough space here क्रम
 * inode, biपंचांगap, superblock, group and indirection updates क्रम at least
 * one block, plus two quota updates.  Quota allocations are not
 * needed. */

#घोषणा EXT4_RESERVE_TRANS_BLOCKS	12U

/*
 * Number of credits needed अगर we need to insert an entry पूर्णांकo a
 * directory.  For each new index block, we need 4 blocks (old index
 * block, new index block, biपंचांगap block, bg summary).  For normal
 * htree directories there are 2 levels; अगर the largedir feature
 * enabled it's 3 levels.
 */
#घोषणा EXT4_INDEX_EXTRA_TRANS_BLOCKS	12U

#अगर_घोषित CONFIG_QUOTA
/* Amount of blocks needed क्रम quota update - we know that the काष्ठाure was
 * allocated so we need to update only data block */
#घोषणा EXT4_QUOTA_TRANS_BLOCKS(sb) ((ext4_quota_capable(sb)) ? 1 : 0)
/* Amount of blocks needed क्रम quota insert/delete - we करो some block ग_लिखोs
 * but inode, sb and group updates are करोne only once */
#घोषणा EXT4_QUOTA_INIT_BLOCKS(sb) ((ext4_quota_capable(sb)) ?\
		(DQUOT_INIT_ALLOC*(EXT4_SINGLEDATA_TRANS_BLOCKS(sb)-3)\
		 +3+DQUOT_INIT_REWRITE) : 0)

#घोषणा EXT4_QUOTA_DEL_BLOCKS(sb) ((ext4_quota_capable(sb)) ?\
		(DQUOT_DEL_ALLOC*(EXT4_SINGLEDATA_TRANS_BLOCKS(sb)-3)\
		 +3+DQUOT_DEL_REWRITE) : 0)
#अन्यथा
#घोषणा EXT4_QUOTA_TRANS_BLOCKS(sb) 0
#घोषणा EXT4_QUOTA_INIT_BLOCKS(sb) 0
#घोषणा EXT4_QUOTA_DEL_BLOCKS(sb) 0
#पूर्ण_अगर
#घोषणा EXT4_MAXQUOTAS_TRANS_BLOCKS(sb) (EXT4_MAXQUOTAS*EXT4_QUOTA_TRANS_BLOCKS(sb))
#घोषणा EXT4_MAXQUOTAS_INIT_BLOCKS(sb) (EXT4_MAXQUOTAS*EXT4_QUOTA_INIT_BLOCKS(sb))
#घोषणा EXT4_MAXQUOTAS_DEL_BLOCKS(sb) (EXT4_MAXQUOTAS*EXT4_QUOTA_DEL_BLOCKS(sb))

/*
 * Ext4 handle operation types -- क्रम logging purposes
 */
#घोषणा EXT4_HT_MISC             0
#घोषणा EXT4_HT_INODE            1
#घोषणा EXT4_HT_WRITE_PAGE       2
#घोषणा EXT4_HT_MAP_BLOCKS       3
#घोषणा EXT4_HT_सूची              4
#घोषणा EXT4_HT_TRUNCATE         5
#घोषणा EXT4_HT_QUOTA            6
#घोषणा EXT4_HT_RESIZE           7
#घोषणा EXT4_HT_MIGRATE          8
#घोषणा EXT4_HT_MOVE_EXTENTS     9
#घोषणा EXT4_HT_XATTR           10
#घोषणा EXT4_HT_EXT_CONVERT     11
#घोषणा EXT4_HT_MAX             12

/**
 *   काष्ठा ext4_journal_cb_entry - Base काष्ठाure क्रम callback inक्रमmation.
 *
 *   This काष्ठा is a 'seed' काष्ठाure क्रम a using with your own callback
 *   काष्ठाs. If you are using callbacks you must allocate one of these
 *   or another काष्ठा of your own definition which has this काष्ठा
 *   as it's first element and pass it to ext4_journal_callback_add().
 */
काष्ठा ext4_journal_cb_entry अणु
	/* list inक्रमmation क्रम other callbacks attached to the same handle */
	काष्ठा list_head jce_list;

	/*  Function to call with this callback काष्ठाure */
	व्योम (*jce_func)(काष्ठा super_block *sb,
			 काष्ठा ext4_journal_cb_entry *jce, पूर्णांक error);

	/* user data goes here */
पूर्ण;

/**
 * ext4_journal_callback_add: add a function to call after transaction commit
 * @handle: active journal transaction handle to रेजिस्टर callback on
 * @func: callback function to call after the transaction has committed:
 *        @sb: superblock of current fileप्रणाली क्रम transaction
 *        @jce: वापसed journal callback data
 *        @rc: journal state at commit (0 = transaction committed properly)
 * @jce: journal callback data (पूर्णांकernal and function निजी data काष्ठा)
 *
 * The रेजिस्टरed function will be called in the context of the journal thपढ़ो
 * after the transaction क्रम which the handle was created has completed.
 *
 * No locks are held when the callback function is called, so it is safe to
 * call blocking functions from within the callback, but the callback should
 * not block or run क्रम too दीर्घ, or the fileप्रणाली will be blocked रुकोing क्रम
 * the next transaction to commit. No journaling functions can be used, or
 * there is a risk of deadlock.
 *
 * There is no guaranteed calling order of multiple रेजिस्टरed callbacks on
 * the same transaction.
 */
अटल अंतरभूत व्योम _ext4_journal_callback_add(handle_t *handle,
			काष्ठा ext4_journal_cb_entry *jce)
अणु
	/* Add the jce to transaction's निजी list */
	list_add_tail(&jce->jce_list, &handle->h_transaction->t_निजी_list);
पूर्ण

अटल अंतरभूत व्योम ext4_journal_callback_add(handle_t *handle,
			व्योम (*func)(काष्ठा super_block *sb,
				     काष्ठा ext4_journal_cb_entry *jce,
				     पूर्णांक rc),
			काष्ठा ext4_journal_cb_entry *jce)
अणु
	काष्ठा ext4_sb_info *sbi =
			EXT4_SB(handle->h_transaction->t_journal->j_निजी);

	/* Add the jce to transaction's निजी list */
	jce->jce_func = func;
	spin_lock(&sbi->s_md_lock);
	_ext4_journal_callback_add(handle, jce);
	spin_unlock(&sbi->s_md_lock);
पूर्ण


/**
 * ext4_journal_callback_del: delete a रेजिस्टरed callback
 * @handle: active journal transaction handle on which callback was रेजिस्टरed
 * @jce: रेजिस्टरed journal callback entry to unरेजिस्टर
 * Return true अगर object was successfully हटाओd
 */
अटल अंतरभूत bool ext4_journal_callback_try_del(handle_t *handle,
					     काष्ठा ext4_journal_cb_entry *jce)
अणु
	bool deleted;
	काष्ठा ext4_sb_info *sbi =
			EXT4_SB(handle->h_transaction->t_journal->j_निजी);

	spin_lock(&sbi->s_md_lock);
	deleted = !list_empty(&jce->jce_list);
	list_del_init(&jce->jce_list);
	spin_unlock(&sbi->s_md_lock);
	वापस deleted;
पूर्ण

पूर्णांक
ext4_mark_iloc_dirty(handle_t *handle,
		     काष्ठा inode *inode,
		     काष्ठा ext4_iloc *iloc);

/*
 * On success, We end up with an outstanding reference count against
 * iloc->bh.  This _must_ be cleaned up later.
 */

पूर्णांक ext4_reserve_inode_ग_लिखो(handle_t *handle, काष्ठा inode *inode,
			काष्ठा ext4_iloc *iloc);

#घोषणा ext4_mark_inode_dirty(__h, __i)					\
		__ext4_mark_inode_dirty((__h), (__i), __func__, __LINE__)
पूर्णांक __ext4_mark_inode_dirty(handle_t *handle, काष्ठा inode *inode,
				स्थिर अक्षर *func, अचिन्हित पूर्णांक line);

पूर्णांक ext4_expand_extra_isize(काष्ठा inode *inode,
			    अचिन्हित पूर्णांक new_extra_isize,
			    काष्ठा ext4_iloc *iloc);
/*
 * Wrapper functions with which ext4 calls पूर्णांकo JBD.
 */
पूर्णांक __ext4_journal_get_ग_लिखो_access(स्थिर अक्षर *where, अचिन्हित पूर्णांक line,
				    handle_t *handle, काष्ठा buffer_head *bh);

पूर्णांक __ext4_क्रमget(स्थिर अक्षर *where, अचिन्हित पूर्णांक line, handle_t *handle,
		  पूर्णांक is_metadata, काष्ठा inode *inode,
		  काष्ठा buffer_head *bh, ext4_fsblk_t blocknr);

पूर्णांक __ext4_journal_get_create_access(स्थिर अक्षर *where, अचिन्हित पूर्णांक line,
				handle_t *handle, काष्ठा buffer_head *bh);

पूर्णांक __ext4_handle_dirty_metadata(स्थिर अक्षर *where, अचिन्हित पूर्णांक line,
				 handle_t *handle, काष्ठा inode *inode,
				 काष्ठा buffer_head *bh);

#घोषणा ext4_journal_get_ग_लिखो_access(handle, bh) \
	__ext4_journal_get_ग_लिखो_access(__func__, __LINE__, (handle), (bh))
#घोषणा ext4_क्रमget(handle, is_metadata, inode, bh, block_nr) \
	__ext4_क्रमget(__func__, __LINE__, (handle), (is_metadata), (inode), \
		      (bh), (block_nr))
#घोषणा ext4_journal_get_create_access(handle, bh) \
	__ext4_journal_get_create_access(__func__, __LINE__, (handle), (bh))
#घोषणा ext4_handle_dirty_metadata(handle, inode, bh) \
	__ext4_handle_dirty_metadata(__func__, __LINE__, (handle), (inode), \
				     (bh))

handle_t *__ext4_journal_start_sb(काष्ठा super_block *sb, अचिन्हित पूर्णांक line,
				  पूर्णांक type, पूर्णांक blocks, पूर्णांक rsv_blocks,
				  पूर्णांक revoke_creds);
पूर्णांक __ext4_journal_stop(स्थिर अक्षर *where, अचिन्हित पूर्णांक line, handle_t *handle);

#घोषणा EXT4_NOJOURNAL_MAX_REF_COUNT ((अचिन्हित दीर्घ) 4096)

/* Note:  Do not use this क्रम शून्य handles.  This is only to determine अगर
 * a properly allocated handle is using a journal or not. */
अटल अंतरभूत पूर्णांक ext4_handle_valid(handle_t *handle)
अणु
	अगर ((अचिन्हित दीर्घ)handle < EXT4_NOJOURNAL_MAX_REF_COUNT)
		वापस 0;
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम ext4_handle_sync(handle_t *handle)
अणु
	अगर (ext4_handle_valid(handle))
		handle->h_sync = 1;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_handle_is_पातed(handle_t *handle)
अणु
	अगर (ext4_handle_valid(handle))
		वापस is_handle_पातed(handle);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_मुक्त_metadata_revoke_credits(काष्ठा super_block *sb,
						    पूर्णांक blocks)
अणु
	/* Freeing each metadata block can result in मुक्तing one cluster */
	वापस blocks * EXT4_SB(sb)->s_cluster_ratio;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_trans_शेष_revoke_credits(काष्ठा super_block *sb)
अणु
	वापस ext4_मुक्त_metadata_revoke_credits(sb, 8);
पूर्ण

#घोषणा ext4_journal_start_sb(sb, type, nblocks)			\
	__ext4_journal_start_sb((sb), __LINE__, (type), (nblocks), 0,	\
				ext4_trans_शेष_revoke_credits(sb))

#घोषणा ext4_journal_start(inode, type, nblocks)			\
	__ext4_journal_start((inode), __LINE__, (type), (nblocks), 0,	\
			     ext4_trans_शेष_revoke_credits((inode)->i_sb))

#घोषणा ext4_journal_start_with_reserve(inode, type, blocks, rsv_blocks)\
	__ext4_journal_start((inode), __LINE__, (type), (blocks), (rsv_blocks),\
			     ext4_trans_शेष_revoke_credits((inode)->i_sb))

#घोषणा ext4_journal_start_with_revoke(inode, type, blocks, revoke_creds) \
	__ext4_journal_start((inode), __LINE__, (type), (blocks), 0,	\
			     (revoke_creds))

अटल अंतरभूत handle_t *__ext4_journal_start(काष्ठा inode *inode,
					     अचिन्हित पूर्णांक line, पूर्णांक type,
					     पूर्णांक blocks, पूर्णांक rsv_blocks,
					     पूर्णांक revoke_creds)
अणु
	वापस __ext4_journal_start_sb(inode->i_sb, line, type, blocks,
				       rsv_blocks, revoke_creds);
पूर्ण

#घोषणा ext4_journal_stop(handle) \
	__ext4_journal_stop(__func__, __LINE__, (handle))

#घोषणा ext4_journal_start_reserved(handle, type) \
	__ext4_journal_start_reserved((handle), __LINE__, (type))

handle_t *__ext4_journal_start_reserved(handle_t *handle, अचिन्हित पूर्णांक line,
					पूर्णांक type);

अटल अंतरभूत handle_t *ext4_journal_current_handle(व्योम)
अणु
	वापस journal_current_handle();
पूर्ण

अटल अंतरभूत पूर्णांक ext4_journal_extend(handle_t *handle, पूर्णांक nblocks, पूर्णांक revoke)
अणु
	अगर (ext4_handle_valid(handle))
		वापस jbd2_journal_extend(handle, nblocks, revoke);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_journal_restart(handle_t *handle, पूर्णांक nblocks,
				       पूर्णांक revoke)
अणु
	अगर (ext4_handle_valid(handle))
		वापस jbd2__journal_restart(handle, nblocks, revoke, GFP_NOFS);
	वापस 0;
पूर्ण

पूर्णांक __ext4_journal_ensure_credits(handle_t *handle, पूर्णांक check_cred,
				  पूर्णांक extend_cred, पूर्णांक revoke_cred);


/*
 * Ensure @handle has at least @check_creds credits available. If not,
 * transaction will be extended or restarted to contain at least @extend_cred
 * credits. Beक्रमe restarting transaction @fn is executed to allow क्रम cleanup
 * beक्रमe the transaction is restarted.
 *
 * The वापस value is < 0 in हाल of error, 0 in हाल the handle has enough
 * credits or transaction extension succeeded, 1 in हाल transaction had to be
 * restarted.
 */
#घोषणा ext4_journal_ensure_credits_fn(handle, check_cred, extend_cred,	\
				       revoke_cred, fn) \
(अणु									\
	__label__ __ensure_end;						\
	पूर्णांक err = __ext4_journal_ensure_credits((handle), (check_cred),	\
					(extend_cred), (revoke_cred));	\
									\
	अगर (err <= 0)							\
		जाओ __ensure_end;					\
	err = (fn);							\
	अगर (err < 0)							\
		जाओ __ensure_end;					\
	err = ext4_journal_restart((handle), (extend_cred), (revoke_cred)); \
	अगर (err == 0)							\
		err = 1;						\
__ensure_end:								\
	err;								\
पूर्ण)

/*
 * Ensure given handle has at least requested amount of credits available,
 * possibly restarting transaction अगर needed. We also make sure the transaction
 * has space क्रम at least ext4_trans_शेष_revoke_credits(sb) revoke records
 * as मुक्तing one or two blocks is very common pattern and requesting this is
 * very cheap.
 */
अटल अंतरभूत पूर्णांक ext4_journal_ensure_credits(handle_t *handle, पूर्णांक credits,
					      पूर्णांक revoke_creds)
अणु
	वापस ext4_journal_ensure_credits_fn(handle, credits, credits,
				revoke_creds, 0);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_journal_blocks_per_page(काष्ठा inode *inode)
अणु
	अगर (EXT4_JOURNAL(inode) != शून्य)
		वापस jbd2_journal_blocks_per_page(inode);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_journal_क्रमce_commit(journal_t *journal)
अणु
	अगर (journal)
		वापस jbd2_journal_क्रमce_commit(journal);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_jbd2_inode_add_ग_लिखो(handle_t *handle,
		काष्ठा inode *inode, loff_t start_byte, loff_t length)
अणु
	अगर (ext4_handle_valid(handle))
		वापस jbd2_journal_inode_ranged_ग_लिखो(handle,
				EXT4_I(inode)->jinode, start_byte, length);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_jbd2_inode_add_रुको(handle_t *handle,
		काष्ठा inode *inode, loff_t start_byte, loff_t length)
अणु
	अगर (ext4_handle_valid(handle))
		वापस jbd2_journal_inode_ranged_रुको(handle,
				EXT4_I(inode)->jinode, start_byte, length);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ext4_update_inode_fsync_trans(handle_t *handle,
						 काष्ठा inode *inode,
						 पूर्णांक datasync)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	अगर (ext4_handle_valid(handle) && !is_handle_पातed(handle)) अणु
		ei->i_sync_tid = handle->h_transaction->t_tid;
		अगर (datasync)
			ei->i_datasync_tid = handle->h_transaction->t_tid;
	पूर्ण
पूर्ण

/* super.c */
पूर्णांक ext4_क्रमce_commit(काष्ठा super_block *sb);

/*
 * Ext4 inode journal modes
 */
#घोषणा EXT4_INODE_JOURNAL_DATA_MODE	0x01 /* journal data mode */
#घोषणा EXT4_INODE_ORDERED_DATA_MODE	0x02 /* ordered data mode */
#घोषणा EXT4_INODE_WRITEBACK_DATA_MODE	0x04 /* ग_लिखोback data mode */

पूर्णांक ext4_inode_journal_mode(काष्ठा inode *inode);

अटल अंतरभूत पूर्णांक ext4_should_journal_data(काष्ठा inode *inode)
अणु
	वापस ext4_inode_journal_mode(inode) & EXT4_INODE_JOURNAL_DATA_MODE;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_should_order_data(काष्ठा inode *inode)
अणु
	वापस ext4_inode_journal_mode(inode) & EXT4_INODE_ORDERED_DATA_MODE;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_should_ग_लिखोback_data(काष्ठा inode *inode)
अणु
	वापस ext4_inode_journal_mode(inode) & EXT4_INODE_WRITEBACK_DATA_MODE;
पूर्ण

अटल अंतरभूत पूर्णांक ext4_मुक्त_data_revoke_credits(काष्ठा inode *inode, पूर्णांक blocks)
अणु
	अगर (test_opt(inode->i_sb, DATA_FLAGS) == EXT4_MOUNT_JOURNAL_DATA)
		वापस 0;
	अगर (!ext4_should_journal_data(inode))
		वापस 0;
	/*
	 * Data blocks in one extent are contiguous, just account क्रम partial
	 * clusters at extent boundaries
	 */
	वापस blocks + 2*(EXT4_SB(inode->i_sb)->s_cluster_ratio - 1);
पूर्ण

/*
 * This function controls whether or not we should try to go करोwn the
 * dioपढ़ो_nolock code paths, which makes it safe to aव्योम taking
 * i_mutex क्रम direct I/O पढ़ोs.  This only works क्रम extent-based
 * files, and it करोesn't work अगर data journaling is enabled, since the
 * dioपढ़ो_nolock code uses b_निजी to pass inक्रमmation back to the
 * I/O completion handler, and this conflicts with the jbd's use of
 * b_निजी.
 */
अटल अंतरभूत पूर्णांक ext4_should_dioपढ़ो_nolock(काष्ठा inode *inode)
अणु
	अगर (!test_opt(inode->i_sb, DIOREAD_NOLOCK))
		वापस 0;
	अगर (!S_ISREG(inode->i_mode))
		वापस 0;
	अगर (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)))
		वापस 0;
	अगर (ext4_should_journal_data(inode))
		वापस 0;
	/* temporary fix to prevent generic/422 test failures */
	अगर (!test_opt(inode->i_sb, DELALLOC))
		वापस 0;
	वापस 1;
पूर्ण

#पूर्ण_अगर	/* _EXT4_JBD2_H */
