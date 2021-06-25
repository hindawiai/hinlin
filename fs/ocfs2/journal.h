<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * journal.h
 *
 * Defines journalling api and काष्ठाures.
 *
 * Copyright (C) 2003, 2005 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_JOURNAL_H
#घोषणा OCFS2_JOURNAL_H

#समावेश <linux/fs.h>
#समावेश <linux/jbd2.h>

क्रमागत ocfs2_journal_state अणु
	OCFS2_JOURNAL_FREE = 0,
	OCFS2_JOURNAL_LOADED,
	OCFS2_JOURNAL_IN_SHUTDOWN,
पूर्ण;

काष्ठा ocfs2_super;
काष्ठा ocfs2_dinode;

/*
 * The recovery_list is a simple linked list of node numbers to recover.
 * It is रक्षित by the recovery_lock.
 */

काष्ठा ocfs2_recovery_map अणु
	अचिन्हित पूर्णांक rm_used;
	अचिन्हित पूर्णांक *rm_entries;
पूर्ण;


काष्ठा ocfs2_journal अणु
	क्रमागत ocfs2_journal_state   j_state;    /* Journals current state   */

	journal_t                 *j_journal; /* The kernels journal type */
	काष्ठा inode              *j_inode;   /* Kernel inode poपूर्णांकing to
					       * this journal             */
	काष्ठा ocfs2_super        *j_osb;     /* poपूर्णांकer to the super
					       * block क्रम the node
					       * we're currently
					       * running on -- not
					       * necessarily the super
					       * block from the node
					       * which we usually run
					       * from (recovery,
					       * etc)                     */
	काष्ठा buffer_head        *j_bh;      /* Journal disk inode block */
	atomic_t                  j_num_trans; /* Number of transactions
					        * currently in the प्रणाली. */
	spinlock_t                j_lock;
	अचिन्हित दीर्घ             j_trans_id;
	काष्ठा rw_semaphore       j_trans_barrier;
	रुको_queue_head_t         j_checkpoपूर्णांकed;

	/* both fields रक्षित by j_lock*/
	काष्ठा list_head          j_la_cleanups;
	काष्ठा work_काष्ठा        j_recovery_work;
पूर्ण;

बाह्य spinlock_t trans_inc_lock;

/* wrap j_trans_id so we never have it equal to zero. */
अटल अंतरभूत अचिन्हित दीर्घ ocfs2_inc_trans_id(काष्ठा ocfs2_journal *j)
अणु
	अचिन्हित दीर्घ old_id;
	spin_lock(&trans_inc_lock);
	old_id = j->j_trans_id++;
	अगर (unlikely(!j->j_trans_id))
		j->j_trans_id = 1;
	spin_unlock(&trans_inc_lock);
	वापस old_id;
पूर्ण

अटल अंतरभूत व्योम ocfs2_set_ci_lock_trans(काष्ठा ocfs2_journal *journal,
					   काष्ठा ocfs2_caching_info *ci)
अणु
	spin_lock(&trans_inc_lock);
	ci->ci_last_trans = journal->j_trans_id;
	spin_unlock(&trans_inc_lock);
पूर्ण

/* Used to figure out whether it's safe to drop a metadata lock on an
 * cached object. Returns true अगर all the object's changes have been
 * checkpoपूर्णांकed to disk. You should be holding the spinlock on the
 * metadata lock जबतक calling this to be sure that nobody can take
 * the lock and put it on another transaction. */
अटल अंतरभूत पूर्णांक ocfs2_ci_fully_checkpoपूर्णांकed(काष्ठा ocfs2_caching_info *ci)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_journal *journal =
		OCFS2_SB(ocfs2_metadata_cache_get_super(ci))->journal;

	spin_lock(&trans_inc_lock);
	ret = समय_after(journal->j_trans_id, ci->ci_last_trans);
	spin_unlock(&trans_inc_lock);
	वापस ret;
पूर्ण

/* convenience function to check अगर an object backed by काष्ठा
 * ocfs2_caching_info  is still new (has never hit disk) Will करो you a
 * favor and set created_trans = 0 when you've
 * been checkpoपूर्णांकed.  वापसs '1' अगर the ci is still new. */
अटल अंतरभूत पूर्णांक ocfs2_ci_is_new(काष्ठा ocfs2_caching_info *ci)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_journal *journal =
		OCFS2_SB(ocfs2_metadata_cache_get_super(ci))->journal;

	spin_lock(&trans_inc_lock);
	ret = !(समय_after(journal->j_trans_id, ci->ci_created_trans));
	अगर (!ret)
		ci->ci_created_trans = 0;
	spin_unlock(&trans_inc_lock);
	वापस ret;
पूर्ण

/* Wrapper क्रम inodes so we can check प्रणाली files */
अटल अंतरभूत पूर्णांक ocfs2_inode_is_new(काष्ठा inode *inode)
अणु
	/* System files are never "new" as they're written out by
	 * mkfs. This helps us early during mount, beक्रमe we have the
	 * journal खोलो and j_trans_id could be junk. */
	अगर (OCFS2_I(inode)->ip_flags & OCFS2_INODE_SYSTEM_खाता)
		वापस 0;

	वापस ocfs2_ci_is_new(INODE_CACHE(inode));
पूर्ण

अटल अंतरभूत व्योम ocfs2_ci_set_new(काष्ठा ocfs2_super *osb,
				    काष्ठा ocfs2_caching_info *ci)
अणु
	spin_lock(&trans_inc_lock);
	ci->ci_created_trans = osb->journal->j_trans_id;
	spin_unlock(&trans_inc_lock);
पूर्ण

/* Exported only क्रम the journal काष्ठा init code in super.c. Do not call. */
व्योम ocfs2_orphan_scan_init(काष्ठा ocfs2_super *osb);
व्योम ocfs2_orphan_scan_start(काष्ठा ocfs2_super *osb);
व्योम ocfs2_orphan_scan_stop(काष्ठा ocfs2_super *osb);

व्योम ocfs2_complete_recovery(काष्ठा work_काष्ठा *work);
व्योम ocfs2_रुको_क्रम_recovery(काष्ठा ocfs2_super *osb);

पूर्णांक ocfs2_recovery_init(काष्ठा ocfs2_super *osb);
व्योम ocfs2_recovery_निकास(काष्ठा ocfs2_super *osb);

पूर्णांक ocfs2_compute_replay_slots(काष्ठा ocfs2_super *osb);
/*
 *  Journal Control:
 *  Initialize, Load, Shutकरोwn, Wipe a journal.
 *
 *  ocfs2_journal_init     - Initialize journal काष्ठाures in the OSB.
 *  ocfs2_journal_load     - Load the given journal off disk. Replay it अगर
 *                          there's transactions still in there.
 *  ocfs2_journal_shutकरोwn - Shutकरोwn a journal, this will flush all
 *                          uncommitted, uncheckpoपूर्णांकed transactions.
 *  ocfs2_journal_wipe     - Wipe transactions from a journal. Optionally
 *                          zero out each block.
 *  ocfs2_recovery_thपढ़ो  - Perक्रमm recovery on a node. osb is our own osb.
 *  ocfs2_mark_dead_nodes - Start recovery on nodes we won't get a heartbeat
 *                          event on.
 *  ocfs2_start_checkpoपूर्णांक - Kick the commit thपढ़ो to करो a checkpoपूर्णांक.
 */
व्योम   ocfs2_set_journal_params(काष्ठा ocfs2_super *osb);
पूर्णांक    ocfs2_journal_init(काष्ठा ocfs2_journal *journal,
			  पूर्णांक *dirty);
व्योम   ocfs2_journal_shutकरोwn(काष्ठा ocfs2_super *osb);
पूर्णांक    ocfs2_journal_wipe(काष्ठा ocfs2_journal *journal,
			  पूर्णांक full);
पूर्णांक    ocfs2_journal_load(काष्ठा ocfs2_journal *journal, पूर्णांक local,
			  पूर्णांक replayed);
पूर्णांक    ocfs2_check_journals_nolocks(काष्ठा ocfs2_super *osb);
व्योम   ocfs2_recovery_thपढ़ो(काष्ठा ocfs2_super *osb,
			     पूर्णांक node_num);
पूर्णांक    ocfs2_mark_dead_nodes(काष्ठा ocfs2_super *osb);
व्योम   ocfs2_complete_mount_recovery(काष्ठा ocfs2_super *osb);
व्योम ocfs2_complete_quota_recovery(काष्ठा ocfs2_super *osb);

अटल अंतरभूत व्योम ocfs2_start_checkpoपूर्णांक(काष्ठा ocfs2_super *osb)
अणु
	wake_up(&osb->checkpoपूर्णांक_event);
पूर्ण

अटल अंतरभूत व्योम ocfs2_checkpoपूर्णांक_inode(काष्ठा inode *inode)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (ocfs2_mount_local(osb))
		वापस;

	अगर (!ocfs2_ci_fully_checkpoपूर्णांकed(INODE_CACHE(inode))) अणु
		/* WARNING: This only kicks off a single
		 * checkpoपूर्णांक. If someone races you and adds more
		 * metadata to the journal, you won't know, and will
		 * wind up रुकोing *a lot* दीर्घer than necessary. Right
		 * now we only use this in clear_inode so that's
		 * OK. */
		ocfs2_start_checkpoपूर्णांक(osb);

		रुको_event(osb->journal->j_checkpoपूर्णांकed,
			   ocfs2_ci_fully_checkpoपूर्णांकed(INODE_CACHE(inode)));
	पूर्ण
पूर्ण

/*
 *  Transaction Handling:
 *  Manage the lअगरeसमय of a transaction handle.
 *
 *  ocfs2_start_trans      - Begin a transaction. Give it an upper estimate of
 *                          the number of blocks that will be changed during
 *                          this handle.
 *  ocfs2_commit_trans - Complete a handle. It might वापस -EIO अगर
 *                       the journal was पातed. The majority of paths करोn't
 *                       check the वापस value as an error there comes too
 *                       late to करो anything (and will be picked up in a
 *                       later transaction).
 *  ocfs2_extend_trans     - Extend a handle by nblocks credits. This may
 *                          commit the handle to disk in the process, but will
 *                          not release any locks taken during the transaction.
 *  ocfs2_journal_access* - Notअगरy the handle that we want to journal this
 *                          buffer. Will have to call ocfs2_journal_dirty once
 *                          we've actually dirtied it. Type is one of . or .
 *                          Always call the specअगरic flavor of
 *                          ocfs2_journal_access_*() unless you पूर्णांकend to
 *                          manage the checksum by hand.
 *  ocfs2_journal_dirty    - Mark a journalled buffer as having dirty data.
 *  ocfs2_jbd2_inode_add_ग_लिखो  - Mark an inode with range so that its data goes
 *                                out beक्रमe the current handle commits.
 */

/* You must always start_trans with a number of buffs > 0, but it's
 * perfectly legal to go through an entire transaction without having
 * dirtied any buffers. */
handle_t		    *ocfs2_start_trans(काष्ठा ocfs2_super *osb,
					       पूर्णांक max_buffs);
पूर्णांक			     ocfs2_commit_trans(काष्ठा ocfs2_super *osb,
						handle_t *handle);
पूर्णांक			     ocfs2_extend_trans(handle_t *handle, पूर्णांक nblocks);
पूर्णांक			     ocfs2_allocate_extend_trans(handle_t *handle,
						पूर्णांक thresh);

/*
 * Define an arbitrary limit क्रम the amount of data we will anticipate
 * writing to any given transaction.  For unbounded transactions such as
 * fallocate(2) we can ग_लिखो more than this, but we always
 * start off at the maximum transaction size and grow the transaction
 * optimistically as we go.
 */
#घोषणा OCFS2_MAX_TRANS_DATA	64U

/*
 * Create access is क्रम when we get a newly created buffer and we're
 * not gonna पढ़ो it off disk, but rather fill it ourselves.  Right
 * now, we करोn't करो anything special with this (it turns पूर्णांकo a ग_लिखो
 * request), but this is a good placeholder in हाल we करो...
 *
 * Write access is क्रम when we पढ़ो a block off disk and are going to
 * modअगरy it. This way the journalling layer knows it may need to make
 * a copy of that block (अगर it's part of another, uncommitted
 * transaction) beक्रमe we करो so.
 */
#घोषणा OCFS2_JOURNAL_ACCESS_CREATE 0
#घोषणा OCFS2_JOURNAL_ACCESS_WRITE  1
#घोषणा OCFS2_JOURNAL_ACCESS_UNDO   2


/* ocfs2_inode */
पूर्णांक ocfs2_journal_access_di(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type);
/* ocfs2_extent_block */
पूर्णांक ocfs2_journal_access_eb(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type);
/* ocfs2_refcount_block */
पूर्णांक ocfs2_journal_access_rb(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type);
/* ocfs2_group_desc */
पूर्णांक ocfs2_journal_access_gd(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type);
/* ocfs2_xattr_block */
पूर्णांक ocfs2_journal_access_xb(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type);
/* quota blocks */
पूर्णांक ocfs2_journal_access_dq(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type);
/* dirblock */
पूर्णांक ocfs2_journal_access_db(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type);
/* ocfs2_dx_root_block */
पूर्णांक ocfs2_journal_access_dr(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type);
/* ocfs2_dx_leaf */
पूर्णांक ocfs2_journal_access_dl(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type);
/* Anything that has no ecc */
पूर्णांक ocfs2_journal_access(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			 काष्ठा buffer_head *bh, पूर्णांक type);

/*
 * A word about the journal_access/journal_dirty "dance". It is
 * entirely legal to journal_access a buffer more than once (as दीर्घ
 * as the access type is the same -- I'm not sure what will happen अगर
 * access type is dअगरferent but this should never happen anyway) It is
 * also legal to journal_dirty a buffer more than once. In fact, you
 * can even journal_access a buffer after you've करोne a
 * journal_access/journal_dirty pair. The only thing you cannot करो
 * however, is journal_dirty a buffer which you haven't yet passed to
 * journal_access at least once.
 *
 * That said, 99% of the समय this करोesn't matter and this is what the
 * path looks like:
 *
 *	<पढ़ो a bh>
 *	ocfs2_journal_access(handle, bh,	OCFS2_JOURNAL_ACCESS_WRITE);
 *	<modअगरy the bh>
 * 	ocfs2_journal_dirty(handle, bh);
 */
व्योम ocfs2_journal_dirty(handle_t *handle, काष्ठा buffer_head *bh);

/*
 *  Credit Macros:
 *  Convenience macros to calculate number of credits needed.
 *
 *  For convenience sake, I have a set of macros here which calculate
 *  the *maximum* number of sectors which will be changed क्रम various
 *  metadata updates.
 */

/* simple file updates like chmod, etc. */
#घोषणा OCFS2_INODE_UPDATE_CREDITS 1

/* extended attribute block update */
#घोषणा OCFS2_XATTR_BLOCK_UPDATE_CREDITS 1

/* Update of a single quota block */
#घोषणा OCFS2_QUOTA_BLOCK_UPDATE_CREDITS 1

/* global quotafile inode update, data block */
#घोषणा OCFS2_QINFO_WRITE_CREDITS (OCFS2_INODE_UPDATE_CREDITS + \
				   OCFS2_QUOTA_BLOCK_UPDATE_CREDITS)

#घोषणा OCFS2_LOCAL_QINFO_WRITE_CREDITS OCFS2_QUOTA_BLOCK_UPDATE_CREDITS
/*
 * The two ग_लिखोs below can accidentally see global info dirty due
 * to set_info() quotactl so make them prepared क्रम the ग_लिखोs.
 */
/* quota data block, global info */
/* Write to local quota file */
#घोषणा OCFS2_QWRITE_CREDITS (OCFS2_QINFO_WRITE_CREDITS + \
			      OCFS2_QUOTA_BLOCK_UPDATE_CREDITS)

/* global quota data block, local quota data block, global quota inode,
 * global quota info */
#घोषणा OCFS2_QSYNC_CREDITS (OCFS2_QINFO_WRITE_CREDITS + \
			     2 * OCFS2_QUOTA_BLOCK_UPDATE_CREDITS)

अटल अंतरभूत पूर्णांक ocfs2_quota_trans_credits(काष्ठा super_block *sb)
अणु
	पूर्णांक credits = 0;

	अगर (OCFS2_HAS_RO_COMPAT_FEATURE(sb, OCFS2_FEATURE_RO_COMPAT_USRQUOTA))
		credits += OCFS2_QWRITE_CREDITS;
	अगर (OCFS2_HAS_RO_COMPAT_FEATURE(sb, OCFS2_FEATURE_RO_COMPAT_GRPQUOTA))
		credits += OCFS2_QWRITE_CREDITS;
	वापस credits;
पूर्ण

/* group extend. inode update and last group update. */
#घोषणा OCFS2_GROUP_EXTEND_CREDITS	(OCFS2_INODE_UPDATE_CREDITS + 1)

/* group add. inode update and the new group update. */
#घोषणा OCFS2_GROUP_ADD_CREDITS	(OCFS2_INODE_UPDATE_CREDITS + 1)

/* get one bit out of a suballocator: dinode + group descriptor +
 * prev. group desc. अगर we relink. */
#घोषणा OCFS2_SUBALLOC_ALLOC (3)

अटल अंतरभूत पूर्णांक ocfs2_अंतरभूत_to_extents_credits(काष्ठा super_block *sb)
अणु
	वापस OCFS2_SUBALLOC_ALLOC + OCFS2_INODE_UPDATE_CREDITS +
	       ocfs2_quota_trans_credits(sb);
पूर्ण

/* dinode + group descriptor update. We करोn't relink on मुक्त yet. */
#घोषणा OCFS2_SUBALLOC_FREE  (2)

#घोषणा OCFS2_TRUNCATE_LOG_UPDATE OCFS2_INODE_UPDATE_CREDITS
#घोषणा OCFS2_TRUNCATE_LOG_FLUSH_ONE_REC (OCFS2_SUBALLOC_FREE 		      \
					 + OCFS2_TRUNCATE_LOG_UPDATE)

अटल अंतरभूत पूर्णांक ocfs2_हटाओ_extent_credits(काष्ठा super_block *sb)
अणु
	वापस OCFS2_TRUNCATE_LOG_UPDATE + OCFS2_INODE_UPDATE_CREDITS +
	       ocfs2_quota_trans_credits(sb);
पूर्ण

/* data block क्रम new dir/symlink, allocation of directory block, dx_root
 * update क्रम मुक्त list */
#घोषणा OCFS2_सूची_LINK_ADDITIONAL_CREDITS (1 + OCFS2_SUBALLOC_ALLOC + 1)

अटल अंतरभूत पूर्णांक ocfs2_add_dir_index_credits(काष्ठा super_block *sb)
अणु
	/* 1 block क्रम index, 2 allocs (data, metadata), 1 clusters
	 * worth of blocks क्रम initial extent. */
	वापस 1 + 2 * OCFS2_SUBALLOC_ALLOC +
		ocfs2_clusters_to_blocks(sb, 1);
पूर्ण

/* parent fe, parent block, new file entry, index leaf, inode alloc fe, inode
 * alloc group descriptor + सूची_गढ़ो/symlink blocks + dir blocks + xattr
 * blocks + quota update */
अटल अंतरभूत पूर्णांक ocfs2_mknod_credits(काष्ठा super_block *sb, पूर्णांक is_dir,
				      पूर्णांक xattr_credits)
अणु
	पूर्णांक dir_credits = OCFS2_सूची_LINK_ADDITIONAL_CREDITS;

	अगर (is_dir)
		dir_credits += ocfs2_add_dir_index_credits(sb);

	वापस 4 + OCFS2_SUBALLOC_ALLOC + dir_credits + xattr_credits +
	       ocfs2_quota_trans_credits(sb);
पूर्ण

/* local alloc metadata change + मुख्य biपंचांगap updates */
#घोषणा OCFS2_WINDOW_MOVE_CREDITS (OCFS2_INODE_UPDATE_CREDITS                 \
				  + OCFS2_SUBALLOC_ALLOC + OCFS2_SUBALLOC_FREE)

/* used when we करोn't need an allocation change क्रम a dir extend. One
 * क्रम the dinode, one क्रम the new block. */
#घोषणा OCFS2_SIMPLE_सूची_EXTEND_CREDITS (2)

/* file update (nlink, etc) + directory mसमय/स_समय + dir entry block + quota
 * update on dir + index leaf + dx root update क्रम मुक्त list +
 * previous dirblock update in the मुक्त list */
अटल अंतरभूत पूर्णांक ocfs2_link_credits(काष्ठा super_block *sb)
अणु
	वापस 2 * OCFS2_INODE_UPDATE_CREDITS + 4 +
	       ocfs2_quota_trans_credits(sb);
पूर्ण

/* inode + dir inode (अगर we unlink a dir), + dir entry block + orphan
 * dir inode link + dir inode index leaf + dir index root */
अटल अंतरभूत पूर्णांक ocfs2_unlink_credits(काष्ठा super_block *sb)
अणु
	/* The quota update from ocfs2_link_credits is unused here... */
	वापस 2 * OCFS2_INODE_UPDATE_CREDITS + 3 + ocfs2_link_credits(sb);
पूर्ण

/* dinode + orphan dir dinode + inode alloc dinode + orphan dir entry +
 * inode alloc group descriptor + orphan dir index root +
 * orphan dir index leaf */
#घोषणा OCFS2_DELETE_INODE_CREDITS (3 * OCFS2_INODE_UPDATE_CREDITS + 4)

/* dinode + orphan dir dinode + extent tree leaf block + orphan dir entry +
 * orphan dir index root + orphan dir index leaf */
#घोषणा OCFS2_INODE_ADD_TO_ORPHAN_CREDITS  (2 * OCFS2_INODE_UPDATE_CREDITS + 4)
#घोषणा OCFS2_INODE_DEL_FROM_ORPHAN_CREDITS  OCFS2_INODE_ADD_TO_ORPHAN_CREDITS

/* dinode update, old dir dinode update, new dir dinode update, old
 * dir dir entry, new dir dir entry, dir entry update क्रम renaming
 * directory + target unlink + 3 x dir index leaves */
अटल अंतरभूत पूर्णांक ocfs2_नाम_credits(काष्ठा super_block *sb)
अणु
	वापस 3 * OCFS2_INODE_UPDATE_CREDITS + 6 + ocfs2_unlink_credits(sb);
पूर्ण

/* global biपंचांगap dinode, group desc., relinked group,
 * suballocator dinode, group desc., relinked group,
 * dinode, xattr block */
#घोषणा OCFS2_XATTR_BLOCK_CREATE_CREDITS (OCFS2_SUBALLOC_ALLOC * 2 + \
					  + OCFS2_INODE_UPDATE_CREDITS \
					  + OCFS2_XATTR_BLOCK_UPDATE_CREDITS)

/* inode update, removal of dx root block from allocator */
#घोषणा OCFS2_DX_ROOT_REMOVE_CREDITS (OCFS2_INODE_UPDATE_CREDITS +	\
				      OCFS2_SUBALLOC_FREE)

अटल अंतरभूत पूर्णांक ocfs2_calc_dxi_expand_credits(काष्ठा super_block *sb)
अणु
	पूर्णांक credits = 1 + OCFS2_SUBALLOC_ALLOC;

	credits += ocfs2_clusters_to_blocks(sb, 1);
	credits += ocfs2_quota_trans_credits(sb);

	वापस credits;
पूर्ण

/* inode update, new refcount block and its allocation credits. */
#घोषणा OCFS2_REFCOUNT_TREE_CREATE_CREDITS (OCFS2_INODE_UPDATE_CREDITS + 1 \
					    + OCFS2_SUBALLOC_ALLOC)

/* inode and the refcount block update. */
#घोषणा OCFS2_REFCOUNT_TREE_SET_CREDITS (OCFS2_INODE_UPDATE_CREDITS + 1)

/*
 * inode and the refcount block update.
 * It करोesn't include the credits क्रम sub alloc change.
 * So अगर we need to मुक्त the bit, OCFS2_SUBALLOC_FREE needs to be added.
 */
#घोषणा OCFS2_REFCOUNT_TREE_REMOVE_CREDITS (OCFS2_INODE_UPDATE_CREDITS + 1)

/* 2 metadata alloc, 2 new blocks and root refcount block */
#घोषणा OCFS2_EXPAND_REFCOUNT_TREE_CREDITS (OCFS2_SUBALLOC_ALLOC * 2 + 3)

/*
 * Please note that the caller must make sure that root_el is the root
 * of extent tree. So क्रम an inode, it should be &fe->id2.i_list. Otherwise
 * the result may be wrong.
 */
अटल अंतरभूत पूर्णांक ocfs2_calc_extend_credits(काष्ठा super_block *sb,
					    काष्ठा ocfs2_extent_list *root_el)
अणु
	पूर्णांक biपंचांगap_blocks, sysfile_biपंचांगap_blocks, extent_blocks;

	/* biपंचांगap dinode, group desc. + relinked group. */
	biपंचांगap_blocks = OCFS2_SUBALLOC_ALLOC;

	/* we might need to shअगरt tree depth so lets assume an
	 * असलolute worst हाल of complete fragmentation.  Even with
	 * that, we only need one update क्रम the dinode, and then
	 * however many metadata chunks needed * a reमुख्यing suballoc
	 * alloc. */
	sysfile_biपंचांगap_blocks = 1 +
		(OCFS2_SUBALLOC_ALLOC - 1) * ocfs2_extend_meta_needed(root_el);

	/* this करोes not include *new* metadata blocks, which are
	 * accounted क्रम in sysfile_biपंचांगap_blocks. root_el +
	 * prev. last_eb_blk + blocks aदीर्घ edge of tree.
	 * calc_symlink_credits passes because we just need 1
	 * credit क्रम the dinode there. */
	extent_blocks = 1 + 1 + le16_to_cpu(root_el->l_tree_depth);

	वापस biपंचांगap_blocks + sysfile_biपंचांगap_blocks + extent_blocks +
	       ocfs2_quota_trans_credits(sb);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_calc_symlink_credits(काष्ठा super_block *sb)
अणु
	पूर्णांक blocks = ocfs2_mknod_credits(sb, 0, 0);

	/* links can be दीर्घer than one block so we may update many
	 * within our single allocated extent. */
	blocks += ocfs2_clusters_to_blocks(sb, 1);

	वापस blocks + ocfs2_quota_trans_credits(sb);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_calc_group_alloc_credits(काष्ठा super_block *sb,
						 अचिन्हित पूर्णांक cpg)
अणु
	पूर्णांक blocks;
	पूर्णांक biपंचांगap_blocks = OCFS2_SUBALLOC_ALLOC + 1;
	/* parent inode update + new block group header + biपंचांगap inode update
	   + biपंचांगap blocks affected */
	blocks = 1 + 1 + 1 + biपंचांगap_blocks;
	वापस blocks;
पूर्ण

/*
 * Allocating a discontiguous block group requires the credits from
 * ocfs2_calc_group_alloc_credits() as well as enough credits to fill
 * the group descriptor's extent list.  The caller alपढ़ोy has started
 * the transaction with ocfs2_calc_group_alloc_credits().  They extend
 * it with these credits.
 */
अटल अंतरभूत पूर्णांक ocfs2_calc_bg_discontig_credits(काष्ठा super_block *sb)
अणु
	वापस ocfs2_extent_recs_per_gd(sb);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_jbd2_inode_add_ग_लिखो(handle_t *handle, काष्ठा inode *inode,
					     loff_t start_byte, loff_t length)
अणु
	वापस jbd2_journal_inode_ranged_ग_लिखो(handle,
					       &OCFS2_I(inode)->ip_jinode,
					       start_byte, length);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_begin_ordered_truncate(काष्ठा inode *inode,
					       loff_t new_size)
अणु
	वापस jbd2_journal_begin_ordered_truncate(
				OCFS2_SB(inode->i_sb)->journal->j_journal,
				&OCFS2_I(inode)->ip_jinode,
				new_size);
पूर्ण

अटल अंतरभूत व्योम ocfs2_update_inode_fsync_trans(handle_t *handle,
						  काष्ठा inode *inode,
						  पूर्णांक datasync)
अणु
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);

	अगर (!is_handle_पातed(handle)) अणु
		oi->i_sync_tid = handle->h_transaction->t_tid;
		अगर (datasync)
			oi->i_datasync_tid = handle->h_transaction->t_tid;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* OCFS2_JOURNAL_H */
