<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * fs/ext4/fast_commit.c
 *
 * Written by Harshad Shirwadkar <harshadshirwadkar@gmail.com>
 *
 * Ext4 fast commits routines.
 */
#समावेश "ext4.h"
#समावेश "ext4_jbd2.h"
#समावेश "ext4_extents.h"
#समावेश "mballoc.h"

/*
 * Ext4 Fast Commits
 * -----------------
 *
 * Ext4 fast commits implement fine grained journalling क्रम Ext4.
 *
 * Fast commits are organized as a log of tag-length-value (TLV) काष्ठाs. (See
 * काष्ठा ext4_fc_tl). Each TLV contains some delta that is replayed TLV by
 * TLV during the recovery phase. For the scenarios क्रम which we currently
 * करोn't have replay code, fast commit falls back to full commits.
 * Fast commits record delta in one of the following three categories.
 *
 * (A) Directory entry updates:
 *
 * - EXT4_FC_TAG_UNLINK		- records directory entry unlink
 * - EXT4_FC_TAG_LINK		- records directory entry link
 * - EXT4_FC_TAG_CREAT		- records inode and directory entry creation
 *
 * (B) File specअगरic data range updates:
 *
 * - EXT4_FC_TAG_ADD_RANGE	- records addition of new blocks to an inode
 * - EXT4_FC_TAG_DEL_RANGE	- records deletion of blocks from an inode
 *
 * (C) Inode metadata (mसमय / स_समय etc):
 *
 * - EXT4_FC_TAG_INODE		- record the inode that should be replayed
 *				  during recovery. Note that iblocks field is
 *				  not replayed and instead derived during
 *				  replay.
 * Commit Operation
 * ----------------
 * With fast commits, we मुख्यtain all the directory entry operations in the
 * order in which they are issued in an in-memory queue. This queue is flushed
 * to disk during the commit operation. We also मुख्यtain a list of inodes
 * that need to be committed during a fast commit in another in memory queue of
 * inodes. During the commit operation, we commit in the following order:
 *
 * [1] Lock inodes क्रम any further data updates by setting COMMITTING state
 * [2] Submit data buffers of all the inodes
 * [3] Wait क्रम [2] to complete
 * [4] Commit all the directory entry updates in the fast commit space
 * [5] Commit all the changed inode काष्ठाures
 * [6] Write tail tag (this tag ensures the atomicity, please पढ़ो the following
 *     section क्रम more details).
 * [7] Wait क्रम [4], [5] and [6] to complete.
 *
 * All the inode updates must call ext4_fc_start_update() beक्रमe starting an
 * update. If such an ongoing update is present, fast commit रुकोs क्रम it to
 * complete. The completion of such an update is marked by
 * ext4_fc_stop_update().
 *
 * Fast Commit Ineligibility
 * -------------------------
 * Not all operations are supported by fast commits today (e.g extended
 * attributes). Fast commit ineligibility is marked by calling one of the
 * two following functions:
 *
 * - ext4_fc_mark_ineligible(): This makes next fast commit operation to fall
 *   back to full commit. This is useful in हाल of transient errors.
 *
 * - ext4_fc_start_ineligible() and ext4_fc_stop_ineligible() - This makes all
 *   the fast commits happening between ext4_fc_start_ineligible() and
 *   ext4_fc_stop_ineligible() and one fast commit after the call to
 *   ext4_fc_stop_ineligible() to fall back to full commits. It is important to
 *   make one more fast commit to fall back to full commit after stop call so
 *   that it guaranteed that the fast commit ineligible operation contained
 *   within ext4_fc_start_ineligible() and ext4_fc_stop_ineligible() is
 *   followed by at least 1 full commit.
 *
 * Atomicity of commits
 * --------------------
 * In order to guarantee atomicity during the commit operation, fast commit
 * uses "EXT4_FC_TAG_TAIL" tag that marks a fast commit as complete. Tail
 * tag contains CRC of the contents and TID of the transaction after which
 * this fast commit should be applied. Recovery code replays fast commit
 * logs only अगर there's at least 1 valid tail present. For every fast commit
 * operation, there is 1 tail. This means, we may end up with multiple tails
 * in the fast commit space. Here's an example:
 *
 * - Create a new file A and हटाओ existing file B
 * - fsync()
 * - Append contents to file A
 * - Truncate file A
 * - fsync()
 *
 * The fast commit space at the end of above operations would look like this:
 *      [HEAD] [CREAT A] [UNLINK B] [TAIL] [ADD_RANGE A] [DEL_RANGE A] [TAIL]
 *             |<---  Fast Commit 1   --->|<---      Fast Commit 2     ---->|
 *
 * Replay code should thus check क्रम all the valid tails in the FC area.
 *
 * Fast Commit Replay Idempotence
 * ------------------------------
 *
 * Fast commits tags are idempotent in nature provided the recovery code follows
 * certain rules. The guiding principle that the commit path follows जबतक
 * committing is that it stores the result of a particular operation instead of
 * storing the procedure.
 *
 * Let's consider this rename operation: 'mv /a /b'. Let's assume dirent '/a'
 * was associated with inode 10. During fast commit, instead of storing this
 * operation as a procedure "rename a to b", we store the resulting file प्रणाली
 * state as a "series" of outcomes:
 *
 * - Link dirent b to inode 10
 * - Unlink dirent a
 * - Inode <10> with valid refcount
 *
 * Now when recovery code runs, it needs "enforce" this state on the file
 * प्रणाली. This is what guarantees idempotence of fast commit replay.
 *
 * Let's take an example of a procedure that is not idempotent and see how fast
 * commits make it idempotent. Consider following sequence of operations:
 *
 *     rm A;    mv B A;    पढ़ो A
 *  (x)     (y)        (z)
 *
 * (x), (y) and (z) are the poपूर्णांकs at which we can crash. If we store this
 * sequence of operations as is then the replay is not idempotent. Let's say
 * जबतक in replay, we crash at (z). During the second replay, file A (which was
 * actually created as a result of "mv B A" operation) would get deleted. Thus,
 * file named A would be असलent when we try to पढ़ो A. So, this sequence of
 * operations is not idempotent. However, as mentioned above, instead of storing
 * the procedure fast commits store the outcome of each procedure. Thus the fast
 * commit log क्रम above procedure would be as follows:
 *
 * (Let's assume dirent A was linked to inode 10 and dirent B was linked to
 * inode 11 beक्रमe the replay)
 *
 *    [Unlink A]   [Link A to inode 11]   [Unlink B]   [Inode 11]
 * (w)          (x)                    (y)          (z)
 *
 * If we crash at (z), we will have file A linked to inode 11. During the second
 * replay, we will हटाओ file A (inode 11). But we will create it back and make
 * it poपूर्णांक to inode 11. We won't find B, so we'll just skip that step. At this
 * poपूर्णांक, the refcount क्रम inode 11 is not reliable, but that माला_लो fixed by the
 * replay of last inode 11 tag. Crashes at poपूर्णांकs (w), (x) and (y) get handled
 * similarly. Thus, by converting a non-idempotent procedure पूर्णांकo a series of
 * idempotent outcomes, fast commits ensured idempotence during the replay.
 *
 * TODOs
 * -----
 *
 * 0) Fast commit replay path hardening: Fast commit replay code should use
 *    journal handles to make sure all the updates it करोes during the replay
 *    path are atomic. With that अगर we crash during fast commit replay, after
 *    trying to करो recovery again, we will find a file प्रणाली where fast commit
 *    area is invalid (because new full commit would be found). In order to deal
 *    with that, fast commit replay code should ensure that the "FC_REPLAY"
 *    superblock state is persisted beक्रमe starting the replay, so that after
 *    the crash, fast commit recovery code can look at that flag and perक्रमm
 *    fast commit recovery even अगर that area is invalidated by later full
 *    commits.
 *
 * 1) Make fast commit atomic updates more fine grained. Today, a fast commit
 *    eligible update must be रक्षित within ext4_fc_start_update() and
 *    ext4_fc_stop_update(). These routines are called at much higher
 *    routines. This can be made more fine grained by combining with
 *    ext4_journal_start().
 *
 * 2) Same above क्रम ext4_fc_start_ineligible() and ext4_fc_stop_ineligible()
 *
 * 3) Handle more ineligible हालs.
 */

#समावेश <trace/events/ext4.h>
अटल काष्ठा kmem_cache *ext4_fc_dentry_cachep;

अटल व्योम ext4_end_buffer_io_sync(काष्ठा buffer_head *bh, पूर्णांक uptodate)
अणु
	BUFFER_TRACE(bh, "");
	अगर (uptodate) अणु
		ext4_debug("%s: Block %lld up-to-date",
			   __func__, bh->b_blocknr);
		set_buffer_uptodate(bh);
	पूर्ण अन्यथा अणु
		ext4_debug("%s: Block %lld not up-to-date",
			   __func__, bh->b_blocknr);
		clear_buffer_uptodate(bh);
	पूर्ण

	unlock_buffer(bh);
पूर्ण

अटल अंतरभूत व्योम ext4_fc_reset_inode(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	ei->i_fc_lblk_start = 0;
	ei->i_fc_lblk_len = 0;
पूर्ण

व्योम ext4_fc_init_inode(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	ext4_fc_reset_inode(inode);
	ext4_clear_inode_state(inode, EXT4_STATE_FC_COMMITTING);
	INIT_LIST_HEAD(&ei->i_fc_list);
	init_रुकोqueue_head(&ei->i_fc_रुको);
	atomic_set(&ei->i_fc_updates, 0);
पूर्ण

/* This function must be called with sbi->s_fc_lock held. */
अटल व्योम ext4_fc_रुको_committing_inode(काष्ठा inode *inode)
__releases(&EXT4_SB(inode->i_sb)->s_fc_lock)
अणु
	रुको_queue_head_t *wq;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

#अगर (BITS_PER_LONG < 64)
	DEFINE_WAIT_BIT(रुको, &ei->i_state_flags,
			EXT4_STATE_FC_COMMITTING);
	wq = bit_रुकोqueue(&ei->i_state_flags,
				EXT4_STATE_FC_COMMITTING);
#अन्यथा
	DEFINE_WAIT_BIT(रुको, &ei->i_flags,
			EXT4_STATE_FC_COMMITTING);
	wq = bit_रुकोqueue(&ei->i_flags,
				EXT4_STATE_FC_COMMITTING);
#पूर्ण_अगर
	lockdep_निश्चित_held(&EXT4_SB(inode->i_sb)->s_fc_lock);
	prepare_to_रुको(wq, &रुको.wq_entry, TASK_UNINTERRUPTIBLE);
	spin_unlock(&EXT4_SB(inode->i_sb)->s_fc_lock);
	schedule();
	finish_रुको(wq, &रुको.wq_entry);
पूर्ण

/*
 * Inक्रमm Ext4's fast about start of an inode update
 *
 * This function is called by the high level call VFS callbacks beक्रमe
 * perक्रमming any inode update. This function blocks अगर there's an ongoing
 * fast commit on the inode in question.
 */
व्योम ext4_fc_start_update(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	अगर (!test_opt2(inode->i_sb, JOURNAL_FAST_COMMIT) ||
	    (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY))
		वापस;

restart:
	spin_lock(&EXT4_SB(inode->i_sb)->s_fc_lock);
	अगर (list_empty(&ei->i_fc_list))
		जाओ out;

	अगर (ext4_test_inode_state(inode, EXT4_STATE_FC_COMMITTING)) अणु
		ext4_fc_रुको_committing_inode(inode);
		जाओ restart;
	पूर्ण
out:
	atomic_inc(&ei->i_fc_updates);
	spin_unlock(&EXT4_SB(inode->i_sb)->s_fc_lock);
पूर्ण

/*
 * Stop inode update and wake up रुकोing fast commits अगर any.
 */
व्योम ext4_fc_stop_update(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	अगर (!test_opt2(inode->i_sb, JOURNAL_FAST_COMMIT) ||
	    (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY))
		वापस;

	अगर (atomic_dec_and_test(&ei->i_fc_updates))
		wake_up_all(&ei->i_fc_रुको);
पूर्ण

/*
 * Remove inode from fast commit list. If the inode is being committed
 * we रुको until inode commit is करोne.
 */
व्योम ext4_fc_del(काष्ठा inode *inode)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);

	अगर (!test_opt2(inode->i_sb, JOURNAL_FAST_COMMIT) ||
	    (EXT4_SB(inode->i_sb)->s_mount_state & EXT4_FC_REPLAY))
		वापस;

restart:
	spin_lock(&EXT4_SB(inode->i_sb)->s_fc_lock);
	अगर (list_empty(&ei->i_fc_list)) अणु
		spin_unlock(&EXT4_SB(inode->i_sb)->s_fc_lock);
		वापस;
	पूर्ण

	अगर (ext4_test_inode_state(inode, EXT4_STATE_FC_COMMITTING)) अणु
		ext4_fc_रुको_committing_inode(inode);
		जाओ restart;
	पूर्ण
	list_del_init(&ei->i_fc_list);
	spin_unlock(&EXT4_SB(inode->i_sb)->s_fc_lock);
पूर्ण

/*
 * Mark file प्रणाली as fast commit ineligible. This means that next commit
 * operation would result in a full jbd2 commit.
 */
व्योम ext4_fc_mark_ineligible(काष्ठा super_block *sb, पूर्णांक reason)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (!test_opt2(sb, JOURNAL_FAST_COMMIT) ||
	    (EXT4_SB(sb)->s_mount_state & EXT4_FC_REPLAY))
		वापस;

	ext4_set_mount_flag(sb, EXT4_MF_FC_INELIGIBLE);
	WARN_ON(reason >= EXT4_FC_REASON_MAX);
	sbi->s_fc_stats.fc_ineligible_reason_count[reason]++;
पूर्ण

/*
 * Start a fast commit ineligible update. Any commits that happen जबतक
 * such an operation is in progress fall back to full commits.
 */
व्योम ext4_fc_start_ineligible(काष्ठा super_block *sb, पूर्णांक reason)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	अगर (!test_opt2(sb, JOURNAL_FAST_COMMIT) ||
	    (EXT4_SB(sb)->s_mount_state & EXT4_FC_REPLAY))
		वापस;

	WARN_ON(reason >= EXT4_FC_REASON_MAX);
	sbi->s_fc_stats.fc_ineligible_reason_count[reason]++;
	atomic_inc(&sbi->s_fc_ineligible_updates);
पूर्ण

/*
 * Stop a fast commit ineligible update. We set EXT4_MF_FC_INELIGIBLE flag here
 * to ensure that after stopping the ineligible update, at least one full
 * commit takes place.
 */
व्योम ext4_fc_stop_ineligible(काष्ठा super_block *sb)
अणु
	अगर (!test_opt2(sb, JOURNAL_FAST_COMMIT) ||
	    (EXT4_SB(sb)->s_mount_state & EXT4_FC_REPLAY))
		वापस;

	ext4_set_mount_flag(sb, EXT4_MF_FC_INELIGIBLE);
	atomic_dec(&EXT4_SB(sb)->s_fc_ineligible_updates);
पूर्ण

अटल अंतरभूत पूर्णांक ext4_fc_is_ineligible(काष्ठा super_block *sb)
अणु
	वापस (ext4_test_mount_flag(sb, EXT4_MF_FC_INELIGIBLE) ||
		atomic_पढ़ो(&EXT4_SB(sb)->s_fc_ineligible_updates));
पूर्ण

/*
 * Generic fast commit tracking function. If this is the first समय this we are
 * called after a full commit, we initialize fast commit fields and then call
 * __fc_track_fn() with update = 0. If we have alपढ़ोy been called after a full
 * commit, we pass update = 1. Based on that, the track function can determine
 * अगर it needs to track a field क्रम the first समय or अगर it needs to just
 * update the previously tracked value.
 *
 * If enqueue is set, this function enqueues the inode in fast commit list.
 */
अटल पूर्णांक ext4_fc_track_ढाँचा(
	handle_t *handle, काष्ठा inode *inode,
	पूर्णांक (*__fc_track_fn)(काष्ठा inode *, व्योम *, bool),
	व्योम *args, पूर्णांक enqueue)
अणु
	bool update = false;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	tid_t tid = 0;
	पूर्णांक ret;

	अगर (!test_opt2(inode->i_sb, JOURNAL_FAST_COMMIT) ||
	    (sbi->s_mount_state & EXT4_FC_REPLAY))
		वापस -EOPNOTSUPP;

	अगर (ext4_fc_is_ineligible(inode->i_sb))
		वापस -EINVAL;

	tid = handle->h_transaction->t_tid;
	mutex_lock(&ei->i_fc_lock);
	अगर (tid == ei->i_sync_tid) अणु
		update = true;
	पूर्ण अन्यथा अणु
		ext4_fc_reset_inode(inode);
		ei->i_sync_tid = tid;
	पूर्ण
	ret = __fc_track_fn(inode, args, update);
	mutex_unlock(&ei->i_fc_lock);

	अगर (!enqueue)
		वापस ret;

	spin_lock(&sbi->s_fc_lock);
	अगर (list_empty(&EXT4_I(inode)->i_fc_list))
		list_add_tail(&EXT4_I(inode)->i_fc_list,
				(ext4_test_mount_flag(inode->i_sb, EXT4_MF_FC_COMMITTING)) ?
				&sbi->s_fc_q[FC_Q_STAGING] :
				&sbi->s_fc_q[FC_Q_MAIN]);
	spin_unlock(&sbi->s_fc_lock);

	वापस ret;
पूर्ण

काष्ठा __track_dentry_update_args अणु
	काष्ठा dentry *dentry;
	पूर्णांक op;
पूर्ण;

/* __track_fn क्रम directory entry updates. Called with ei->i_fc_lock. */
अटल पूर्णांक __track_dentry_update(काष्ठा inode *inode, व्योम *arg, bool update)
अणु
	काष्ठा ext4_fc_dentry_update *node;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा __track_dentry_update_args *dentry_update =
		(काष्ठा __track_dentry_update_args *)arg;
	काष्ठा dentry *dentry = dentry_update->dentry;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	mutex_unlock(&ei->i_fc_lock);
	node = kmem_cache_alloc(ext4_fc_dentry_cachep, GFP_NOFS);
	अगर (!node) अणु
		ext4_fc_mark_ineligible(inode->i_sb, EXT4_FC_REASON_NOMEM);
		mutex_lock(&ei->i_fc_lock);
		वापस -ENOMEM;
	पूर्ण

	node->fcd_op = dentry_update->op;
	node->fcd_parent = dentry->d_parent->d_inode->i_ino;
	node->fcd_ino = inode->i_ino;
	अगर (dentry->d_name.len > DNAME_INLINE_LEN) अणु
		node->fcd_name.name = kदो_स्मृति(dentry->d_name.len, GFP_NOFS);
		अगर (!node->fcd_name.name) अणु
			kmem_cache_मुक्त(ext4_fc_dentry_cachep, node);
			ext4_fc_mark_ineligible(inode->i_sb,
				EXT4_FC_REASON_NOMEM);
			mutex_lock(&ei->i_fc_lock);
			वापस -ENOMEM;
		पूर्ण
		स_नकल((u8 *)node->fcd_name.name, dentry->d_name.name,
			dentry->d_name.len);
	पूर्ण अन्यथा अणु
		स_नकल(node->fcd_iname, dentry->d_name.name,
			dentry->d_name.len);
		node->fcd_name.name = node->fcd_iname;
	पूर्ण
	node->fcd_name.len = dentry->d_name.len;

	spin_lock(&sbi->s_fc_lock);
	अगर (ext4_test_mount_flag(inode->i_sb, EXT4_MF_FC_COMMITTING))
		list_add_tail(&node->fcd_list,
				&sbi->s_fc_dentry_q[FC_Q_STAGING]);
	अन्यथा
		list_add_tail(&node->fcd_list, &sbi->s_fc_dentry_q[FC_Q_MAIN]);
	spin_unlock(&sbi->s_fc_lock);
	mutex_lock(&ei->i_fc_lock);

	वापस 0;
पूर्ण

व्योम __ext4_fc_track_unlink(handle_t *handle,
		काष्ठा inode *inode, काष्ठा dentry *dentry)
अणु
	काष्ठा __track_dentry_update_args args;
	पूर्णांक ret;

	args.dentry = dentry;
	args.op = EXT4_FC_TAG_UNLINK;

	ret = ext4_fc_track_ढाँचा(handle, inode, __track_dentry_update,
					(व्योम *)&args, 0);
	trace_ext4_fc_track_unlink(inode, dentry, ret);
पूर्ण

व्योम ext4_fc_track_unlink(handle_t *handle, काष्ठा dentry *dentry)
अणु
	__ext4_fc_track_unlink(handle, d_inode(dentry), dentry);
पूर्ण

व्योम __ext4_fc_track_link(handle_t *handle,
	काष्ठा inode *inode, काष्ठा dentry *dentry)
अणु
	काष्ठा __track_dentry_update_args args;
	पूर्णांक ret;

	args.dentry = dentry;
	args.op = EXT4_FC_TAG_LINK;

	ret = ext4_fc_track_ढाँचा(handle, inode, __track_dentry_update,
					(व्योम *)&args, 0);
	trace_ext4_fc_track_link(inode, dentry, ret);
पूर्ण

व्योम ext4_fc_track_link(handle_t *handle, काष्ठा dentry *dentry)
अणु
	__ext4_fc_track_link(handle, d_inode(dentry), dentry);
पूर्ण

व्योम __ext4_fc_track_create(handle_t *handle, काष्ठा inode *inode,
			  काष्ठा dentry *dentry)
अणु
	काष्ठा __track_dentry_update_args args;
	पूर्णांक ret;

	args.dentry = dentry;
	args.op = EXT4_FC_TAG_CREAT;

	ret = ext4_fc_track_ढाँचा(handle, inode, __track_dentry_update,
					(व्योम *)&args, 0);
	trace_ext4_fc_track_create(inode, dentry, ret);
पूर्ण

व्योम ext4_fc_track_create(handle_t *handle, काष्ठा dentry *dentry)
अणु
	__ext4_fc_track_create(handle, d_inode(dentry), dentry);
पूर्ण

/* __track_fn क्रम inode tracking */
अटल पूर्णांक __track_inode(काष्ठा inode *inode, व्योम *arg, bool update)
अणु
	अगर (update)
		वापस -EEXIST;

	EXT4_I(inode)->i_fc_lblk_len = 0;

	वापस 0;
पूर्ण

व्योम ext4_fc_track_inode(handle_t *handle, काष्ठा inode *inode)
अणु
	पूर्णांक ret;

	अगर (S_ISसूची(inode->i_mode))
		वापस;

	अगर (ext4_should_journal_data(inode)) अणु
		ext4_fc_mark_ineligible(inode->i_sb,
					EXT4_FC_REASON_INODE_JOURNAL_DATA);
		वापस;
	पूर्ण

	ret = ext4_fc_track_ढाँचा(handle, inode, __track_inode, शून्य, 1);
	trace_ext4_fc_track_inode(inode, ret);
पूर्ण

काष्ठा __track_range_args अणु
	ext4_lblk_t start, end;
पूर्ण;

/* __track_fn क्रम tracking data updates */
अटल पूर्णांक __track_range(काष्ठा inode *inode, व्योम *arg, bool update)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	ext4_lblk_t oldstart;
	काष्ठा __track_range_args *__arg =
		(काष्ठा __track_range_args *)arg;

	अगर (inode->i_ino < EXT4_FIRST_INO(inode->i_sb)) अणु
		ext4_debug("Special inode %ld being modified\n", inode->i_ino);
		वापस -ECANCELED;
	पूर्ण

	oldstart = ei->i_fc_lblk_start;

	अगर (update && ei->i_fc_lblk_len > 0) अणु
		ei->i_fc_lblk_start = min(ei->i_fc_lblk_start, __arg->start);
		ei->i_fc_lblk_len =
			max(oldstart + ei->i_fc_lblk_len - 1, __arg->end) -
				ei->i_fc_lblk_start + 1;
	पूर्ण अन्यथा अणु
		ei->i_fc_lblk_start = __arg->start;
		ei->i_fc_lblk_len = __arg->end - __arg->start + 1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ext4_fc_track_range(handle_t *handle, काष्ठा inode *inode, ext4_lblk_t start,
			 ext4_lblk_t end)
अणु
	काष्ठा __track_range_args args;
	पूर्णांक ret;

	अगर (S_ISसूची(inode->i_mode))
		वापस;

	args.start = start;
	args.end = end;

	ret = ext4_fc_track_ढाँचा(handle, inode,  __track_range, &args, 1);

	trace_ext4_fc_track_range(inode, start, end, ret);
पूर्ण

अटल व्योम ext4_fc_submit_bh(काष्ठा super_block *sb, bool is_tail)
अणु
	पूर्णांक ग_लिखो_flags = REQ_SYNC;
	काष्ठा buffer_head *bh = EXT4_SB(sb)->s_fc_bh;

	/* Add REQ_FUA | REQ_PREFLUSH only its tail */
	अगर (test_opt(sb, BARRIER) && is_tail)
		ग_लिखो_flags |= REQ_FUA | REQ_PREFLUSH;
	lock_buffer(bh);
	set_buffer_dirty(bh);
	set_buffer_uptodate(bh);
	bh->b_end_io = ext4_end_buffer_io_sync;
	submit_bh(REQ_OP_WRITE, ग_लिखो_flags, bh);
	EXT4_SB(sb)->s_fc_bh = शून्य;
पूर्ण

/* Ext4 commit path routines */

/* memzero and update CRC */
अटल व्योम *ext4_fc_memzero(काष्ठा super_block *sb, व्योम *dst, पूर्णांक len,
				u32 *crc)
अणु
	व्योम *ret;

	ret = स_रखो(dst, 0, len);
	अगर (crc)
		*crc = ext4_chksum(EXT4_SB(sb), *crc, dst, len);
	वापस ret;
पूर्ण

/*
 * Allocate len bytes on a fast commit buffer.
 *
 * During the commit समय this function is used to manage fast commit
 * block space. We करोn't split a fast commit log onto dअगरferent
 * blocks. So this function makes sure that अगर there's not enough space
 * on the current block, the reमुख्यing space in the current block is
 * marked as unused by adding EXT4_FC_TAG_PAD tag. In that हाल,
 * new block is from jbd2 and CRC is updated to reflect the padding
 * we added.
 */
अटल u8 *ext4_fc_reserve_space(काष्ठा super_block *sb, पूर्णांक len, u32 *crc)
अणु
	काष्ठा ext4_fc_tl *tl;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा buffer_head *bh;
	पूर्णांक bsize = sbi->s_journal->j_blocksize;
	पूर्णांक ret, off = sbi->s_fc_bytes % bsize;
	पूर्णांक pad_len;

	/*
	 * After allocating len, we should have space at least क्रम a 0 byte
	 * padding.
	 */
	अगर (len + माप(काष्ठा ext4_fc_tl) > bsize)
		वापस शून्य;

	अगर (bsize - off - 1 > len + माप(काष्ठा ext4_fc_tl)) अणु
		/*
		 * Only allocate from current buffer अगर we have enough space क्रम
		 * this request AND we have space to add a zero byte padding.
		 */
		अगर (!sbi->s_fc_bh) अणु
			ret = jbd2_fc_get_buf(EXT4_SB(sb)->s_journal, &bh);
			अगर (ret)
				वापस शून्य;
			sbi->s_fc_bh = bh;
		पूर्ण
		sbi->s_fc_bytes += len;
		वापस sbi->s_fc_bh->b_data + off;
	पूर्ण
	/* Need to add PAD tag */
	tl = (काष्ठा ext4_fc_tl *)(sbi->s_fc_bh->b_data + off);
	tl->fc_tag = cpu_to_le16(EXT4_FC_TAG_PAD);
	pad_len = bsize - off - 1 - माप(काष्ठा ext4_fc_tl);
	tl->fc_len = cpu_to_le16(pad_len);
	अगर (crc)
		*crc = ext4_chksum(sbi, *crc, tl, माप(*tl));
	अगर (pad_len > 0)
		ext4_fc_memzero(sb, tl + 1, pad_len, crc);
	ext4_fc_submit_bh(sb, false);

	ret = jbd2_fc_get_buf(EXT4_SB(sb)->s_journal, &bh);
	अगर (ret)
		वापस शून्य;
	sbi->s_fc_bh = bh;
	sbi->s_fc_bytes = (sbi->s_fc_bytes / bsize + 1) * bsize + len;
	वापस sbi->s_fc_bh->b_data;
पूर्ण

/* स_नकल to fc reserved space and update CRC */
अटल व्योम *ext4_fc_स_नकल(काष्ठा super_block *sb, व्योम *dst, स्थिर व्योम *src,
				पूर्णांक len, u32 *crc)
अणु
	अगर (crc)
		*crc = ext4_chksum(EXT4_SB(sb), *crc, src, len);
	वापस स_नकल(dst, src, len);
पूर्ण

/*
 * Complete a fast commit by writing tail tag.
 *
 * Writing tail tag marks the end of a fast commit. In order to guarantee
 * atomicity, after writing tail tag, even अगर there's space reमुख्यing
 * in the block, next commit shouldn't use it. That's why tail tag
 * has the length as that of the reमुख्यing space on the block.
 */
अटल पूर्णांक ext4_fc_ग_लिखो_tail(काष्ठा super_block *sb, u32 crc)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_fc_tl tl;
	काष्ठा ext4_fc_tail tail;
	पूर्णांक off, bsize = sbi->s_journal->j_blocksize;
	u8 *dst;

	/*
	 * ext4_fc_reserve_space takes care of allocating an extra block अगर
	 * there's no enough space on this block क्रम accommodating this tail.
	 */
	dst = ext4_fc_reserve_space(sb, माप(tl) + माप(tail), &crc);
	अगर (!dst)
		वापस -ENOSPC;

	off = sbi->s_fc_bytes % bsize;

	tl.fc_tag = cpu_to_le16(EXT4_FC_TAG_TAIL);
	tl.fc_len = cpu_to_le16(bsize - off - 1 + माप(काष्ठा ext4_fc_tail));
	sbi->s_fc_bytes = round_up(sbi->s_fc_bytes, bsize);

	ext4_fc_स_नकल(sb, dst, &tl, माप(tl), &crc);
	dst += माप(tl);
	tail.fc_tid = cpu_to_le32(sbi->s_journal->j_running_transaction->t_tid);
	ext4_fc_स_नकल(sb, dst, &tail.fc_tid, माप(tail.fc_tid), &crc);
	dst += माप(tail.fc_tid);
	tail.fc_crc = cpu_to_le32(crc);
	ext4_fc_स_नकल(sb, dst, &tail.fc_crc, माप(tail.fc_crc), शून्य);

	ext4_fc_submit_bh(sb, true);

	वापस 0;
पूर्ण

/*
 * Adds tag, length, value and updates CRC. Returns true अगर tlv was added.
 * Returns false अगर there's not enough space.
 */
अटल bool ext4_fc_add_tlv(काष्ठा super_block *sb, u16 tag, u16 len, u8 *val,
			   u32 *crc)
अणु
	काष्ठा ext4_fc_tl tl;
	u8 *dst;

	dst = ext4_fc_reserve_space(sb, माप(tl) + len, crc);
	अगर (!dst)
		वापस false;

	tl.fc_tag = cpu_to_le16(tag);
	tl.fc_len = cpu_to_le16(len);

	ext4_fc_स_नकल(sb, dst, &tl, माप(tl), crc);
	ext4_fc_स_नकल(sb, dst + माप(tl), val, len, crc);

	वापस true;
पूर्ण

/* Same as above, but adds dentry tlv. */
अटल  bool ext4_fc_add_dentry_tlv(काष्ठा super_block *sb, u16 tag,
					पूर्णांक parent_ino, पूर्णांक ino, पूर्णांक dlen,
					स्थिर अचिन्हित अक्षर *dname,
					u32 *crc)
अणु
	काष्ठा ext4_fc_dentry_info fcd;
	काष्ठा ext4_fc_tl tl;
	u8 *dst = ext4_fc_reserve_space(sb, माप(tl) + माप(fcd) + dlen,
					crc);

	अगर (!dst)
		वापस false;

	fcd.fc_parent_ino = cpu_to_le32(parent_ino);
	fcd.fc_ino = cpu_to_le32(ino);
	tl.fc_tag = cpu_to_le16(tag);
	tl.fc_len = cpu_to_le16(माप(fcd) + dlen);
	ext4_fc_स_नकल(sb, dst, &tl, माप(tl), crc);
	dst += माप(tl);
	ext4_fc_स_नकल(sb, dst, &fcd, माप(fcd), crc);
	dst += माप(fcd);
	ext4_fc_स_नकल(sb, dst, dname, dlen, crc);
	dst += dlen;

	वापस true;
पूर्ण

/*
 * Writes inode in the fast commit space under TLV with tag @tag.
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक ext4_fc_ग_लिखो_inode(काष्ठा inode *inode, u32 *crc)
अणु
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	पूर्णांक inode_len = EXT4_GOOD_OLD_INODE_SIZE;
	पूर्णांक ret;
	काष्ठा ext4_iloc iloc;
	काष्ठा ext4_fc_inode fc_inode;
	काष्ठा ext4_fc_tl tl;
	u8 *dst;

	ret = ext4_get_inode_loc(inode, &iloc);
	अगर (ret)
		वापस ret;

	अगर (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE)
		inode_len += ei->i_extra_isize;

	fc_inode.fc_ino = cpu_to_le32(inode->i_ino);
	tl.fc_tag = cpu_to_le16(EXT4_FC_TAG_INODE);
	tl.fc_len = cpu_to_le16(inode_len + माप(fc_inode.fc_ino));

	dst = ext4_fc_reserve_space(inode->i_sb,
			माप(tl) + inode_len + माप(fc_inode.fc_ino), crc);
	अगर (!dst)
		वापस -ECANCELED;

	अगर (!ext4_fc_स_नकल(inode->i_sb, dst, &tl, माप(tl), crc))
		वापस -ECANCELED;
	dst += माप(tl);
	अगर (!ext4_fc_स_नकल(inode->i_sb, dst, &fc_inode, माप(fc_inode), crc))
		वापस -ECANCELED;
	dst += माप(fc_inode);
	अगर (!ext4_fc_स_नकल(inode->i_sb, dst, (u8 *)ext4_raw_inode(&iloc),
					inode_len, crc))
		वापस -ECANCELED;

	वापस 0;
पूर्ण

/*
 * Writes updated data ranges क्रम the inode in question. Updates CRC.
 * Returns 0 on success, error otherwise.
 */
अटल पूर्णांक ext4_fc_ग_लिखो_inode_data(काष्ठा inode *inode, u32 *crc)
अणु
	ext4_lblk_t old_blk_size, cur_lblk_off, new_blk_size;
	काष्ठा ext4_inode_info *ei = EXT4_I(inode);
	काष्ठा ext4_map_blocks map;
	काष्ठा ext4_fc_add_range fc_ext;
	काष्ठा ext4_fc_del_range lrange;
	काष्ठा ext4_extent *ex;
	पूर्णांक ret;

	mutex_lock(&ei->i_fc_lock);
	अगर (ei->i_fc_lblk_len == 0) अणु
		mutex_unlock(&ei->i_fc_lock);
		वापस 0;
	पूर्ण
	old_blk_size = ei->i_fc_lblk_start;
	new_blk_size = ei->i_fc_lblk_start + ei->i_fc_lblk_len - 1;
	ei->i_fc_lblk_len = 0;
	mutex_unlock(&ei->i_fc_lock);

	cur_lblk_off = old_blk_size;
	jbd_debug(1, "%s: will try writing %d to %d for inode %ld\n",
		  __func__, cur_lblk_off, new_blk_size, inode->i_ino);

	जबतक (cur_lblk_off <= new_blk_size) अणु
		map.m_lblk = cur_lblk_off;
		map.m_len = new_blk_size - cur_lblk_off + 1;
		ret = ext4_map_blocks(शून्य, inode, &map, 0);
		अगर (ret < 0)
			वापस -ECANCELED;

		अगर (map.m_len == 0) अणु
			cur_lblk_off++;
			जारी;
		पूर्ण

		अगर (ret == 0) अणु
			lrange.fc_ino = cpu_to_le32(inode->i_ino);
			lrange.fc_lblk = cpu_to_le32(map.m_lblk);
			lrange.fc_len = cpu_to_le32(map.m_len);
			अगर (!ext4_fc_add_tlv(inode->i_sb, EXT4_FC_TAG_DEL_RANGE,
					    माप(lrange), (u8 *)&lrange, crc))
				वापस -ENOSPC;
		पूर्ण अन्यथा अणु
			fc_ext.fc_ino = cpu_to_le32(inode->i_ino);
			ex = (काष्ठा ext4_extent *)&fc_ext.fc_ex;
			ex->ee_block = cpu_to_le32(map.m_lblk);
			ex->ee_len = cpu_to_le16(map.m_len);
			ext4_ext_store_pblock(ex, map.m_pblk);
			अगर (map.m_flags & EXT4_MAP_UNWRITTEN)
				ext4_ext_mark_unwritten(ex);
			अन्यथा
				ext4_ext_mark_initialized(ex);
			अगर (!ext4_fc_add_tlv(inode->i_sb, EXT4_FC_TAG_ADD_RANGE,
					    माप(fc_ext), (u8 *)&fc_ext, crc))
				वापस -ENOSPC;
		पूर्ण

		cur_lblk_off += map.m_len;
	पूर्ण

	वापस 0;
पूर्ण


/* Submit data क्रम all the fast commit inodes */
अटल पूर्णांक ext4_fc_submit_inode_data_all(journal_t *journal)
अणु
	काष्ठा super_block *sb = (काष्ठा super_block *)(journal->j_निजी);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_inode_info *ei;
	पूर्णांक ret = 0;

	spin_lock(&sbi->s_fc_lock);
	ext4_set_mount_flag(sb, EXT4_MF_FC_COMMITTING);
	list_क्रम_each_entry(ei, &sbi->s_fc_q[FC_Q_MAIN], i_fc_list) अणु
		ext4_set_inode_state(&ei->vfs_inode, EXT4_STATE_FC_COMMITTING);
		जबतक (atomic_पढ़ो(&ei->i_fc_updates)) अणु
			DEFINE_WAIT(रुको);

			prepare_to_रुको(&ei->i_fc_रुको, &रुको,
						TASK_UNINTERRUPTIBLE);
			अगर (atomic_पढ़ो(&ei->i_fc_updates)) अणु
				spin_unlock(&sbi->s_fc_lock);
				schedule();
				spin_lock(&sbi->s_fc_lock);
			पूर्ण
			finish_रुको(&ei->i_fc_रुको, &रुको);
		पूर्ण
		spin_unlock(&sbi->s_fc_lock);
		ret = jbd2_submit_inode_data(ei->jinode);
		अगर (ret)
			वापस ret;
		spin_lock(&sbi->s_fc_lock);
	पूर्ण
	spin_unlock(&sbi->s_fc_lock);

	वापस ret;
पूर्ण

/* Wait क्रम completion of data क्रम all the fast commit inodes */
अटल पूर्णांक ext4_fc_रुको_inode_data_all(journal_t *journal)
अणु
	काष्ठा super_block *sb = (काष्ठा super_block *)(journal->j_निजी);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_inode_info *pos, *n;
	पूर्णांक ret = 0;

	spin_lock(&sbi->s_fc_lock);
	list_क्रम_each_entry_safe(pos, n, &sbi->s_fc_q[FC_Q_MAIN], i_fc_list) अणु
		अगर (!ext4_test_inode_state(&pos->vfs_inode,
					   EXT4_STATE_FC_COMMITTING))
			जारी;
		spin_unlock(&sbi->s_fc_lock);

		ret = jbd2_रुको_inode_data(journal, pos->jinode);
		अगर (ret)
			वापस ret;
		spin_lock(&sbi->s_fc_lock);
	पूर्ण
	spin_unlock(&sbi->s_fc_lock);

	वापस 0;
पूर्ण

/* Commit all the directory entry updates */
अटल पूर्णांक ext4_fc_commit_dentry_updates(journal_t *journal, u32 *crc)
__acquires(&sbi->s_fc_lock)
__releases(&sbi->s_fc_lock)
अणु
	काष्ठा super_block *sb = (काष्ठा super_block *)(journal->j_निजी);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_fc_dentry_update *fc_dentry, *fc_dentry_n;
	काष्ठा inode *inode;
	काष्ठा ext4_inode_info *ei, *ei_n;
	पूर्णांक ret;

	अगर (list_empty(&sbi->s_fc_dentry_q[FC_Q_MAIN]))
		वापस 0;
	list_क्रम_each_entry_safe(fc_dentry, fc_dentry_n,
				 &sbi->s_fc_dentry_q[FC_Q_MAIN], fcd_list) अणु
		अगर (fc_dentry->fcd_op != EXT4_FC_TAG_CREAT) अणु
			spin_unlock(&sbi->s_fc_lock);
			अगर (!ext4_fc_add_dentry_tlv(
				sb, fc_dentry->fcd_op,
				fc_dentry->fcd_parent, fc_dentry->fcd_ino,
				fc_dentry->fcd_name.len,
				fc_dentry->fcd_name.name, crc)) अणु
				ret = -ENOSPC;
				जाओ lock_and_निकास;
			पूर्ण
			spin_lock(&sbi->s_fc_lock);
			जारी;
		पूर्ण

		inode = शून्य;
		list_क्रम_each_entry_safe(ei, ei_n, &sbi->s_fc_q[FC_Q_MAIN],
					 i_fc_list) अणु
			अगर (ei->vfs_inode.i_ino == fc_dentry->fcd_ino) अणु
				inode = &ei->vfs_inode;
				अवरोध;
			पूर्ण
		पूर्ण
		/*
		 * If we करोn't find inode in our list, then it was deleted,
		 * in which हाल, we करोn't need to record it's create tag.
		 */
		अगर (!inode)
			जारी;
		spin_unlock(&sbi->s_fc_lock);

		/*
		 * We first ग_लिखो the inode and then the create dirent. This
		 * allows the recovery code to create an unnamed inode first
		 * and then link it to a directory entry. This allows us
		 * to use namei.c routines almost as is and simplअगरies
		 * the recovery code.
		 */
		ret = ext4_fc_ग_लिखो_inode(inode, crc);
		अगर (ret)
			जाओ lock_and_निकास;

		ret = ext4_fc_ग_लिखो_inode_data(inode, crc);
		अगर (ret)
			जाओ lock_and_निकास;

		अगर (!ext4_fc_add_dentry_tlv(
			sb, fc_dentry->fcd_op,
			fc_dentry->fcd_parent, fc_dentry->fcd_ino,
			fc_dentry->fcd_name.len,
			fc_dentry->fcd_name.name, crc)) अणु
			ret = -ENOSPC;
			जाओ lock_and_निकास;
		पूर्ण

		spin_lock(&sbi->s_fc_lock);
	पूर्ण
	वापस 0;
lock_and_निकास:
	spin_lock(&sbi->s_fc_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_fc_perक्रमm_commit(journal_t *journal)
अणु
	काष्ठा super_block *sb = (काष्ठा super_block *)(journal->j_निजी);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_inode_info *iter;
	काष्ठा ext4_fc_head head;
	काष्ठा inode *inode;
	काष्ठा blk_plug plug;
	पूर्णांक ret = 0;
	u32 crc = 0;

	ret = ext4_fc_submit_inode_data_all(journal);
	अगर (ret)
		वापस ret;

	ret = ext4_fc_रुको_inode_data_all(journal);
	अगर (ret)
		वापस ret;

	/*
	 * If file प्रणाली device is dअगरferent from journal device, issue a cache
	 * flush beक्रमe we start writing fast commit blocks.
	 */
	अगर (journal->j_fs_dev != journal->j_dev)
		blkdev_issue_flush(journal->j_fs_dev);

	blk_start_plug(&plug);
	अगर (sbi->s_fc_bytes == 0) अणु
		/*
		 * Add a head tag only अगर this is the first fast commit
		 * in this TID.
		 */
		head.fc_features = cpu_to_le32(EXT4_FC_SUPPORTED_FEATURES);
		head.fc_tid = cpu_to_le32(
			sbi->s_journal->j_running_transaction->t_tid);
		अगर (!ext4_fc_add_tlv(sb, EXT4_FC_TAG_HEAD, माप(head),
			(u8 *)&head, &crc)) अणु
			ret = -ENOSPC;
			जाओ out;
		पूर्ण
	पूर्ण

	spin_lock(&sbi->s_fc_lock);
	ret = ext4_fc_commit_dentry_updates(journal, &crc);
	अगर (ret) अणु
		spin_unlock(&sbi->s_fc_lock);
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(iter, &sbi->s_fc_q[FC_Q_MAIN], i_fc_list) अणु
		inode = &iter->vfs_inode;
		अगर (!ext4_test_inode_state(inode, EXT4_STATE_FC_COMMITTING))
			जारी;

		spin_unlock(&sbi->s_fc_lock);
		ret = ext4_fc_ग_लिखो_inode_data(inode, &crc);
		अगर (ret)
			जाओ out;
		ret = ext4_fc_ग_लिखो_inode(inode, &crc);
		अगर (ret)
			जाओ out;
		spin_lock(&sbi->s_fc_lock);
	पूर्ण
	spin_unlock(&sbi->s_fc_lock);

	ret = ext4_fc_ग_लिखो_tail(sb, crc);

out:
	blk_finish_plug(&plug);
	वापस ret;
पूर्ण

/*
 * The मुख्य commit entry poपूर्णांक. Perक्रमms a fast commit क्रम transaction
 * commit_tid अगर needed. If it's not possible to perक्रमm a fast commit
 * due to various reasons, we fall back to full commit. Returns 0
 * on success, error otherwise.
 */
पूर्णांक ext4_fc_commit(journal_t *journal, tid_t commit_tid)
अणु
	काष्ठा super_block *sb = (काष्ठा super_block *)(journal->j_निजी);
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	पूर्णांक nblks = 0, ret, bsize = journal->j_blocksize;
	पूर्णांक subtid = atomic_पढ़ो(&sbi->s_fc_subtid);
	पूर्णांक reason = EXT4_FC_REASON_OK, fc_bufs_beक्रमe = 0;
	kसमय_प्रकार start_समय, commit_समय;

	trace_ext4_fc_commit_start(sb);

	start_समय = kसमय_get();

	अगर (!test_opt2(sb, JOURNAL_FAST_COMMIT) ||
		(ext4_fc_is_ineligible(sb))) अणु
		reason = EXT4_FC_REASON_INELIGIBLE;
		जाओ out;
	पूर्ण

restart_fc:
	ret = jbd2_fc_begin_commit(journal, commit_tid);
	अगर (ret == -EALREADY) अणु
		/* There was an ongoing commit, check अगर we need to restart */
		अगर (atomic_पढ़ो(&sbi->s_fc_subtid) <= subtid &&
			commit_tid > journal->j_commit_sequence)
			जाओ restart_fc;
		reason = EXT4_FC_REASON_ALREADY_COMMITTED;
		जाओ out;
	पूर्ण अन्यथा अगर (ret) अणु
		sbi->s_fc_stats.fc_ineligible_reason_count[EXT4_FC_COMMIT_FAILED]++;
		reason = EXT4_FC_REASON_FC_START_FAILED;
		जाओ out;
	पूर्ण

	fc_bufs_beक्रमe = (sbi->s_fc_bytes + bsize - 1) / bsize;
	ret = ext4_fc_perक्रमm_commit(journal);
	अगर (ret < 0) अणु
		sbi->s_fc_stats.fc_ineligible_reason_count[EXT4_FC_COMMIT_FAILED]++;
		reason = EXT4_FC_REASON_FC_FAILED;
		जाओ out;
	पूर्ण
	nblks = (sbi->s_fc_bytes + bsize - 1) / bsize - fc_bufs_beक्रमe;
	ret = jbd2_fc_रुको_bufs(journal, nblks);
	अगर (ret < 0) अणु
		sbi->s_fc_stats.fc_ineligible_reason_count[EXT4_FC_COMMIT_FAILED]++;
		reason = EXT4_FC_REASON_FC_FAILED;
		जाओ out;
	पूर्ण
	atomic_inc(&sbi->s_fc_subtid);
	jbd2_fc_end_commit(journal);
out:
	/* Has any ineligible update happened since we started? */
	अगर (reason == EXT4_FC_REASON_OK && ext4_fc_is_ineligible(sb)) अणु
		sbi->s_fc_stats.fc_ineligible_reason_count[EXT4_FC_COMMIT_FAILED]++;
		reason = EXT4_FC_REASON_INELIGIBLE;
	पूर्ण

	spin_lock(&sbi->s_fc_lock);
	अगर (reason != EXT4_FC_REASON_OK &&
		reason != EXT4_FC_REASON_ALREADY_COMMITTED) अणु
		sbi->s_fc_stats.fc_ineligible_commits++;
	पूर्ण अन्यथा अणु
		sbi->s_fc_stats.fc_num_commits++;
		sbi->s_fc_stats.fc_numblks += nblks;
	पूर्ण
	spin_unlock(&sbi->s_fc_lock);
	nblks = (reason == EXT4_FC_REASON_OK) ? nblks : 0;
	trace_ext4_fc_commit_stop(sb, nblks, reason);
	commit_समय = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), start_समय));
	/*
	 * weight the commit समय higher than the average समय so we करोn't
	 * react too strongly to vast changes in the commit समय
	 */
	अगर (likely(sbi->s_fc_avg_commit_समय))
		sbi->s_fc_avg_commit_समय = (commit_समय +
				sbi->s_fc_avg_commit_समय * 3) / 4;
	अन्यथा
		sbi->s_fc_avg_commit_समय = commit_समय;
	jbd_debug(1,
		"Fast commit ended with blks = %d, reason = %d, subtid - %d",
		nblks, reason, subtid);
	अगर (reason == EXT4_FC_REASON_FC_FAILED)
		वापस jbd2_fc_end_commit_fallback(journal);
	अगर (reason == EXT4_FC_REASON_FC_START_FAILED ||
		reason == EXT4_FC_REASON_INELIGIBLE)
		वापस jbd2_complete_transaction(journal, commit_tid);
	वापस 0;
पूर्ण

/*
 * Fast commit cleanup routine. This is called after every fast commit and
 * full commit. full is true अगर we are called after a full commit.
 */
अटल व्योम ext4_fc_cleanup(journal_t *journal, पूर्णांक full)
अणु
	काष्ठा super_block *sb = journal->j_निजी;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_inode_info *iter, *iter_n;
	काष्ठा ext4_fc_dentry_update *fc_dentry;

	अगर (full && sbi->s_fc_bh)
		sbi->s_fc_bh = शून्य;

	jbd2_fc_release_bufs(journal);

	spin_lock(&sbi->s_fc_lock);
	list_क्रम_each_entry_safe(iter, iter_n, &sbi->s_fc_q[FC_Q_MAIN],
				 i_fc_list) अणु
		list_del_init(&iter->i_fc_list);
		ext4_clear_inode_state(&iter->vfs_inode,
				       EXT4_STATE_FC_COMMITTING);
		ext4_fc_reset_inode(&iter->vfs_inode);
		/* Make sure EXT4_STATE_FC_COMMITTING bit is clear */
		smp_mb();
#अगर (BITS_PER_LONG < 64)
		wake_up_bit(&iter->i_state_flags, EXT4_STATE_FC_COMMITTING);
#अन्यथा
		wake_up_bit(&iter->i_flags, EXT4_STATE_FC_COMMITTING);
#पूर्ण_अगर
	पूर्ण

	जबतक (!list_empty(&sbi->s_fc_dentry_q[FC_Q_MAIN])) अणु
		fc_dentry = list_first_entry(&sbi->s_fc_dentry_q[FC_Q_MAIN],
					     काष्ठा ext4_fc_dentry_update,
					     fcd_list);
		list_del_init(&fc_dentry->fcd_list);
		spin_unlock(&sbi->s_fc_lock);

		अगर (fc_dentry->fcd_name.name &&
			fc_dentry->fcd_name.len > DNAME_INLINE_LEN)
			kमुक्त(fc_dentry->fcd_name.name);
		kmem_cache_मुक्त(ext4_fc_dentry_cachep, fc_dentry);
		spin_lock(&sbi->s_fc_lock);
	पूर्ण

	list_splice_init(&sbi->s_fc_dentry_q[FC_Q_STAGING],
				&sbi->s_fc_dentry_q[FC_Q_MAIN]);
	list_splice_init(&sbi->s_fc_q[FC_Q_STAGING],
				&sbi->s_fc_q[FC_Q_MAIN]);

	ext4_clear_mount_flag(sb, EXT4_MF_FC_COMMITTING);
	ext4_clear_mount_flag(sb, EXT4_MF_FC_INELIGIBLE);

	अगर (full)
		sbi->s_fc_bytes = 0;
	spin_unlock(&sbi->s_fc_lock);
	trace_ext4_fc_stats(sb);
पूर्ण

/* Ext4 Replay Path Routines */

/* Helper काष्ठा क्रम dentry replay routines */
काष्ठा dentry_info_args अणु
	पूर्णांक parent_ino, dname_len, ino, inode_len;
	अक्षर *dname;
पूर्ण;

अटल अंतरभूत व्योम tl_to_darg(काष्ठा dentry_info_args *darg,
			      काष्ठा  ext4_fc_tl *tl, u8 *val)
अणु
	काष्ठा ext4_fc_dentry_info fcd;

	स_नकल(&fcd, val, माप(fcd));

	darg->parent_ino = le32_to_cpu(fcd.fc_parent_ino);
	darg->ino = le32_to_cpu(fcd.fc_ino);
	darg->dname = val + दुरत्व(काष्ठा ext4_fc_dentry_info, fc_dname);
	darg->dname_len = le16_to_cpu(tl->fc_len) -
		माप(काष्ठा ext4_fc_dentry_info);
पूर्ण

/* Unlink replay function */
अटल पूर्णांक ext4_fc_replay_unlink(काष्ठा super_block *sb, काष्ठा ext4_fc_tl *tl,
				 u8 *val)
अणु
	काष्ठा inode *inode, *old_parent;
	काष्ठा qstr entry;
	काष्ठा dentry_info_args darg;
	पूर्णांक ret = 0;

	tl_to_darg(&darg, tl, val);

	trace_ext4_fc_replay(sb, EXT4_FC_TAG_UNLINK, darg.ino,
			darg.parent_ino, darg.dname_len);

	entry.name = darg.dname;
	entry.len = darg.dname_len;
	inode = ext4_iget(sb, darg.ino, EXT4_IGET_NORMAL);

	अगर (IS_ERR(inode)) अणु
		jbd_debug(1, "Inode %d not found", darg.ino);
		वापस 0;
	पूर्ण

	old_parent = ext4_iget(sb, darg.parent_ino,
				EXT4_IGET_NORMAL);
	अगर (IS_ERR(old_parent)) अणु
		jbd_debug(1, "Dir with inode  %d not found", darg.parent_ino);
		iput(inode);
		वापस 0;
	पूर्ण

	ret = __ext4_unlink(शून्य, old_parent, &entry, inode);
	/* -ENOENT ok coz it might not exist anymore. */
	अगर (ret == -ENOENT)
		ret = 0;
	iput(old_parent);
	iput(inode);
	वापस ret;
पूर्ण

अटल पूर्णांक ext4_fc_replay_link_पूर्णांकernal(काष्ठा super_block *sb,
				काष्ठा dentry_info_args *darg,
				काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = शून्य;
	काष्ठा dentry *dentry_dir = शून्य, *dentry_inode = शून्य;
	काष्ठा qstr qstr_dname = QSTR_INIT(darg->dname, darg->dname_len);
	पूर्णांक ret = 0;

	dir = ext4_iget(sb, darg->parent_ino, EXT4_IGET_NORMAL);
	अगर (IS_ERR(dir)) अणु
		jbd_debug(1, "Dir with inode %d not found.", darg->parent_ino);
		dir = शून्य;
		जाओ out;
	पूर्ण

	dentry_dir = d_obtain_alias(dir);
	अगर (IS_ERR(dentry_dir)) अणु
		jbd_debug(1, "Failed to obtain dentry");
		dentry_dir = शून्य;
		जाओ out;
	पूर्ण

	dentry_inode = d_alloc(dentry_dir, &qstr_dname);
	अगर (!dentry_inode) अणु
		jbd_debug(1, "Inode dentry not created.");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = __ext4_link(dir, inode, dentry_inode);
	/*
	 * It's possible that link alपढ़ोy existed since data blocks
	 * क्रम the dir in question got persisted beक्रमe we crashed OR
	 * we replayed this tag and crashed beक्रमe the entire replay
	 * could complete.
	 */
	अगर (ret && ret != -EEXIST) अणु
		jbd_debug(1, "Failed to link\n");
		जाओ out;
	पूर्ण

	ret = 0;
out:
	अगर (dentry_dir) अणु
		d_drop(dentry_dir);
		dput(dentry_dir);
	पूर्ण अन्यथा अगर (dir) अणु
		iput(dir);
	पूर्ण
	अगर (dentry_inode) अणु
		d_drop(dentry_inode);
		dput(dentry_inode);
	पूर्ण

	वापस ret;
पूर्ण

/* Link replay function */
अटल पूर्णांक ext4_fc_replay_link(काष्ठा super_block *sb, काष्ठा ext4_fc_tl *tl,
			       u8 *val)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry_info_args darg;
	पूर्णांक ret = 0;

	tl_to_darg(&darg, tl, val);
	trace_ext4_fc_replay(sb, EXT4_FC_TAG_LINK, darg.ino,
			darg.parent_ino, darg.dname_len);

	inode = ext4_iget(sb, darg.ino, EXT4_IGET_NORMAL);
	अगर (IS_ERR(inode)) अणु
		jbd_debug(1, "Inode not found.");
		वापस 0;
	पूर्ण

	ret = ext4_fc_replay_link_पूर्णांकernal(sb, &darg, inode);
	iput(inode);
	वापस ret;
पूर्ण

/*
 * Record all the modअगरied inodes during replay. We use this later to setup
 * block biपंचांगaps correctly.
 */
अटल पूर्णांक ext4_fc_record_modअगरied_inode(काष्ठा super_block *sb, पूर्णांक ino)
अणु
	काष्ठा ext4_fc_replay_state *state;
	पूर्णांक i;

	state = &EXT4_SB(sb)->s_fc_replay_state;
	क्रम (i = 0; i < state->fc_modअगरied_inodes_used; i++)
		अगर (state->fc_modअगरied_inodes[i] == ino)
			वापस 0;
	अगर (state->fc_modअगरied_inodes_used == state->fc_modअगरied_inodes_size) अणु
		state->fc_modअगरied_inodes_size +=
			EXT4_FC_REPLAY_REALLOC_INCREMENT;
		state->fc_modअगरied_inodes = kपुनः_स्मृति(
					state->fc_modअगरied_inodes, माप(पूर्णांक) *
					state->fc_modअगरied_inodes_size,
					GFP_KERNEL);
		अगर (!state->fc_modअगरied_inodes)
			वापस -ENOMEM;
	पूर्ण
	state->fc_modअगरied_inodes[state->fc_modअगरied_inodes_used++] = ino;
	वापस 0;
पूर्ण

/*
 * Inode replay function
 */
अटल पूर्णांक ext4_fc_replay_inode(काष्ठा super_block *sb, काष्ठा ext4_fc_tl *tl,
				u8 *val)
अणु
	काष्ठा ext4_fc_inode fc_inode;
	काष्ठा ext4_inode *raw_inode;
	काष्ठा ext4_inode *raw_fc_inode;
	काष्ठा inode *inode = शून्य;
	काष्ठा ext4_iloc iloc;
	पूर्णांक inode_len, ino, ret, tag = le16_to_cpu(tl->fc_tag);
	काष्ठा ext4_extent_header *eh;

	स_नकल(&fc_inode, val, माप(fc_inode));

	ino = le32_to_cpu(fc_inode.fc_ino);
	trace_ext4_fc_replay(sb, tag, ino, 0, 0);

	inode = ext4_iget(sb, ino, EXT4_IGET_NORMAL);
	अगर (!IS_ERR(inode)) अणु
		ext4_ext_clear_bb(inode);
		iput(inode);
	पूर्ण
	inode = शून्य;

	ext4_fc_record_modअगरied_inode(sb, ino);

	raw_fc_inode = (काष्ठा ext4_inode *)
		(val + दुरत्व(काष्ठा ext4_fc_inode, fc_raw_inode));
	ret = ext4_get_fc_inode_loc(sb, ino, &iloc);
	अगर (ret)
		जाओ out;

	inode_len = le16_to_cpu(tl->fc_len) - माप(काष्ठा ext4_fc_inode);
	raw_inode = ext4_raw_inode(&iloc);

	स_नकल(raw_inode, raw_fc_inode, दुरत्व(काष्ठा ext4_inode, i_block));
	स_नकल(&raw_inode->i_generation, &raw_fc_inode->i_generation,
		inode_len - दुरत्व(काष्ठा ext4_inode, i_generation));
	अगर (le32_to_cpu(raw_inode->i_flags) & EXT4_EXTENTS_FL) अणु
		eh = (काष्ठा ext4_extent_header *)(&raw_inode->i_block[0]);
		अगर (eh->eh_magic != EXT4_EXT_MAGIC) अणु
			स_रखो(eh, 0, माप(*eh));
			eh->eh_magic = EXT4_EXT_MAGIC;
			eh->eh_max = cpu_to_le16(
				(माप(raw_inode->i_block) -
				 माप(काष्ठा ext4_extent_header))
				 / माप(काष्ठा ext4_extent));
		पूर्ण
	पूर्ण अन्यथा अगर (le32_to_cpu(raw_inode->i_flags) & EXT4_INLINE_DATA_FL) अणु
		स_नकल(raw_inode->i_block, raw_fc_inode->i_block,
			माप(raw_inode->i_block));
	पूर्ण

	/* Immediately update the inode on disk. */
	ret = ext4_handle_dirty_metadata(शून्य, शून्य, iloc.bh);
	अगर (ret)
		जाओ out;
	ret = sync_dirty_buffer(iloc.bh);
	अगर (ret)
		जाओ out;
	ret = ext4_mark_inode_used(sb, ino);
	अगर (ret)
		जाओ out;

	/* Given that we just wrote the inode on disk, this SHOULD succeed. */
	inode = ext4_iget(sb, ino, EXT4_IGET_NORMAL);
	अगर (IS_ERR(inode)) अणु
		jbd_debug(1, "Inode not found.");
		वापस -EFSCORRUPTED;
	पूर्ण

	/*
	 * Our allocator could have made dअगरferent decisions than beक्रमe
	 * crashing. This should be fixed but until then, we calculate
	 * the number of blocks the inode.
	 */
	ext4_ext_replay_set_iblocks(inode);

	inode->i_generation = le32_to_cpu(ext4_raw_inode(&iloc)->i_generation);
	ext4_reset_inode_seed(inode);

	ext4_inode_csum_set(inode, ext4_raw_inode(&iloc), EXT4_I(inode));
	ret = ext4_handle_dirty_metadata(शून्य, शून्य, iloc.bh);
	sync_dirty_buffer(iloc.bh);
	brअन्यथा(iloc.bh);
out:
	iput(inode);
	अगर (!ret)
		blkdev_issue_flush(sb->s_bdev);

	वापस 0;
पूर्ण

/*
 * Dentry create replay function.
 *
 * EXT4_FC_TAG_CREAT is preceded by EXT4_FC_TAG_INODE_FULL. Which means, the
 * inode क्रम which we are trying to create a dentry here, should alपढ़ोy have
 * been replayed beक्रमe we start here.
 */
अटल पूर्णांक ext4_fc_replay_create(काष्ठा super_block *sb, काष्ठा ext4_fc_tl *tl,
				 u8 *val)
अणु
	पूर्णांक ret = 0;
	काष्ठा inode *inode = शून्य;
	काष्ठा inode *dir = शून्य;
	काष्ठा dentry_info_args darg;

	tl_to_darg(&darg, tl, val);

	trace_ext4_fc_replay(sb, EXT4_FC_TAG_CREAT, darg.ino,
			darg.parent_ino, darg.dname_len);

	/* This takes care of update group descriptor and other metadata */
	ret = ext4_mark_inode_used(sb, darg.ino);
	अगर (ret)
		जाओ out;

	inode = ext4_iget(sb, darg.ino, EXT4_IGET_NORMAL);
	अगर (IS_ERR(inode)) अणु
		jbd_debug(1, "inode %d not found.", darg.ino);
		inode = शून्य;
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (S_ISसूची(inode->i_mode)) अणु
		/*
		 * If we are creating a directory, we need to make sure that the
		 * करोt and करोt करोt dirents are setup properly.
		 */
		dir = ext4_iget(sb, darg.parent_ino, EXT4_IGET_NORMAL);
		अगर (IS_ERR(dir)) अणु
			jbd_debug(1, "Dir %d not found.", darg.ino);
			जाओ out;
		पूर्ण
		ret = ext4_init_new_dir(शून्य, dir, inode);
		iput(dir);
		अगर (ret) अणु
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	ret = ext4_fc_replay_link_पूर्णांकernal(sb, &darg, inode);
	अगर (ret)
		जाओ out;
	set_nlink(inode, 1);
	ext4_mark_inode_dirty(शून्य, inode);
out:
	अगर (inode)
		iput(inode);
	वापस ret;
पूर्ण

/*
 * Record physical disk regions which are in use as per fast commit area. Our
 * simple replay phase allocator excludes these regions from allocation.
 */
अटल पूर्णांक ext4_fc_record_regions(काष्ठा super_block *sb, पूर्णांक ino,
		ext4_lblk_t lblk, ext4_fsblk_t pblk, पूर्णांक len)
अणु
	काष्ठा ext4_fc_replay_state *state;
	काष्ठा ext4_fc_alloc_region *region;

	state = &EXT4_SB(sb)->s_fc_replay_state;
	अगर (state->fc_regions_used == state->fc_regions_size) अणु
		state->fc_regions_size +=
			EXT4_FC_REPLAY_REALLOC_INCREMENT;
		state->fc_regions = kपुनः_स्मृति(
					state->fc_regions,
					state->fc_regions_size *
					माप(काष्ठा ext4_fc_alloc_region),
					GFP_KERNEL);
		अगर (!state->fc_regions)
			वापस -ENOMEM;
	पूर्ण
	region = &state->fc_regions[state->fc_regions_used++];
	region->ino = ino;
	region->lblk = lblk;
	region->pblk = pblk;
	region->len = len;

	वापस 0;
पूर्ण

/* Replay add range tag */
अटल पूर्णांक ext4_fc_replay_add_range(काष्ठा super_block *sb,
				    काष्ठा ext4_fc_tl *tl, u8 *val)
अणु
	काष्ठा ext4_fc_add_range fc_add_ex;
	काष्ठा ext4_extent newex, *ex;
	काष्ठा inode *inode;
	ext4_lblk_t start, cur;
	पूर्णांक reमुख्यing, len;
	ext4_fsblk_t start_pblk;
	काष्ठा ext4_map_blocks map;
	काष्ठा ext4_ext_path *path = शून्य;
	पूर्णांक ret;

	स_नकल(&fc_add_ex, val, माप(fc_add_ex));
	ex = (काष्ठा ext4_extent *)&fc_add_ex.fc_ex;

	trace_ext4_fc_replay(sb, EXT4_FC_TAG_ADD_RANGE,
		le32_to_cpu(fc_add_ex.fc_ino), le32_to_cpu(ex->ee_block),
		ext4_ext_get_actual_len(ex));

	inode = ext4_iget(sb, le32_to_cpu(fc_add_ex.fc_ino), EXT4_IGET_NORMAL);
	अगर (IS_ERR(inode)) अणु
		jbd_debug(1, "Inode not found.");
		वापस 0;
	पूर्ण

	ret = ext4_fc_record_modअगरied_inode(sb, inode->i_ino);

	start = le32_to_cpu(ex->ee_block);
	start_pblk = ext4_ext_pblock(ex);
	len = ext4_ext_get_actual_len(ex);

	cur = start;
	reमुख्यing = len;
	jbd_debug(1, "ADD_RANGE, lblk %d, pblk %lld, len %d, unwritten %d, inode %ld\n",
		  start, start_pblk, len, ext4_ext_is_unwritten(ex),
		  inode->i_ino);

	जबतक (reमुख्यing > 0) अणु
		map.m_lblk = cur;
		map.m_len = reमुख्यing;
		map.m_pblk = 0;
		ret = ext4_map_blocks(शून्य, inode, &map, 0);

		अगर (ret < 0) अणु
			iput(inode);
			वापस 0;
		पूर्ण

		अगर (ret == 0) अणु
			/* Range is not mapped */
			path = ext4_find_extent(inode, cur, शून्य, 0);
			अगर (IS_ERR(path)) अणु
				iput(inode);
				वापस 0;
			पूर्ण
			स_रखो(&newex, 0, माप(newex));
			newex.ee_block = cpu_to_le32(cur);
			ext4_ext_store_pblock(
				&newex, start_pblk + cur - start);
			newex.ee_len = cpu_to_le16(map.m_len);
			अगर (ext4_ext_is_unwritten(ex))
				ext4_ext_mark_unwritten(&newex);
			करोwn_ग_लिखो(&EXT4_I(inode)->i_data_sem);
			ret = ext4_ext_insert_extent(
				शून्य, inode, &path, &newex, 0);
			up_ग_लिखो((&EXT4_I(inode)->i_data_sem));
			ext4_ext_drop_refs(path);
			kमुक्त(path);
			अगर (ret) अणु
				iput(inode);
				वापस 0;
			पूर्ण
			जाओ next;
		पूर्ण

		अगर (start_pblk + cur - start != map.m_pblk) अणु
			/*
			 * Logical to physical mapping changed. This can happen
			 * अगर this range was हटाओd and then पुनः_स्मृतिated to
			 * map to new physical blocks during a fast commit.
			 */
			ret = ext4_ext_replay_update_ex(inode, cur, map.m_len,
					ext4_ext_is_unwritten(ex),
					start_pblk + cur - start);
			अगर (ret) अणु
				iput(inode);
				वापस 0;
			पूर्ण
			/*
			 * Mark the old blocks as मुक्त since they aren't used
			 * anymore. We मुख्यtain an array of all the modअगरied
			 * inodes. In हाल these blocks are still used at either
			 * a dअगरferent logical range in the same inode or in
			 * some dअगरferent inode, we will mark them as allocated
			 * at the end of the FC replay using our array of
			 * modअगरied inodes.
			 */
			ext4_mb_mark_bb(inode->i_sb, map.m_pblk, map.m_len, 0);
			जाओ next;
		पूर्ण

		/* Range is mapped and needs a state change */
		jbd_debug(1, "Converting from %ld to %d %lld",
				map.m_flags & EXT4_MAP_UNWRITTEN,
			ext4_ext_is_unwritten(ex), map.m_pblk);
		ret = ext4_ext_replay_update_ex(inode, cur, map.m_len,
					ext4_ext_is_unwritten(ex), map.m_pblk);
		अगर (ret) अणु
			iput(inode);
			वापस 0;
		पूर्ण
		/*
		 * We may have split the extent tree जबतक toggling the state.
		 * Try to shrink the extent tree now.
		 */
		ext4_ext_replay_shrink_inode(inode, start + len);
next:
		cur += map.m_len;
		reमुख्यing -= map.m_len;
	पूर्ण
	ext4_ext_replay_shrink_inode(inode, i_size_पढ़ो(inode) >>
					sb->s_blocksize_bits);
	iput(inode);
	वापस 0;
पूर्ण

/* Replay DEL_RANGE tag */
अटल पूर्णांक
ext4_fc_replay_del_range(काष्ठा super_block *sb, काष्ठा ext4_fc_tl *tl,
			 u8 *val)
अणु
	काष्ठा inode *inode;
	काष्ठा ext4_fc_del_range lrange;
	काष्ठा ext4_map_blocks map;
	ext4_lblk_t cur, reमुख्यing;
	पूर्णांक ret;

	स_नकल(&lrange, val, माप(lrange));
	cur = le32_to_cpu(lrange.fc_lblk);
	reमुख्यing = le32_to_cpu(lrange.fc_len);

	trace_ext4_fc_replay(sb, EXT4_FC_TAG_DEL_RANGE,
		le32_to_cpu(lrange.fc_ino), cur, reमुख्यing);

	inode = ext4_iget(sb, le32_to_cpu(lrange.fc_ino), EXT4_IGET_NORMAL);
	अगर (IS_ERR(inode)) अणु
		jbd_debug(1, "Inode %d not found", le32_to_cpu(lrange.fc_ino));
		वापस 0;
	पूर्ण

	ret = ext4_fc_record_modअगरied_inode(sb, inode->i_ino);

	jbd_debug(1, "DEL_RANGE, inode %ld, lblk %d, len %d\n",
			inode->i_ino, le32_to_cpu(lrange.fc_lblk),
			le32_to_cpu(lrange.fc_len));
	जबतक (reमुख्यing > 0) अणु
		map.m_lblk = cur;
		map.m_len = reमुख्यing;

		ret = ext4_map_blocks(शून्य, inode, &map, 0);
		अगर (ret < 0) अणु
			iput(inode);
			वापस 0;
		पूर्ण
		अगर (ret > 0) अणु
			reमुख्यing -= ret;
			cur += ret;
			ext4_mb_mark_bb(inode->i_sb, map.m_pblk, map.m_len, 0);
		पूर्ण अन्यथा अणु
			reमुख्यing -= map.m_len;
			cur += map.m_len;
		पूर्ण
	पूर्ण

	ret = ext4_punch_hole(inode,
		le32_to_cpu(lrange.fc_lblk) << sb->s_blocksize_bits,
		le32_to_cpu(lrange.fc_len) <<  sb->s_blocksize_bits);
	अगर (ret)
		jbd_debug(1, "ext4_punch_hole returned %d", ret);
	ext4_ext_replay_shrink_inode(inode,
		i_size_पढ़ो(inode) >> sb->s_blocksize_bits);
	ext4_mark_inode_dirty(शून्य, inode);
	iput(inode);

	वापस 0;
पूर्ण

अटल व्योम ext4_fc_set_biपंचांगaps_and_counters(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_fc_replay_state *state;
	काष्ठा inode *inode;
	काष्ठा ext4_ext_path *path = शून्य;
	काष्ठा ext4_map_blocks map;
	पूर्णांक i, ret, j;
	ext4_lblk_t cur, end;

	state = &EXT4_SB(sb)->s_fc_replay_state;
	क्रम (i = 0; i < state->fc_modअगरied_inodes_used; i++) अणु
		inode = ext4_iget(sb, state->fc_modअगरied_inodes[i],
			EXT4_IGET_NORMAL);
		अगर (IS_ERR(inode)) अणु
			jbd_debug(1, "Inode %d not found.",
				state->fc_modअगरied_inodes[i]);
			जारी;
		पूर्ण
		cur = 0;
		end = EXT_MAX_BLOCKS;
		जबतक (cur < end) अणु
			map.m_lblk = cur;
			map.m_len = end - cur;

			ret = ext4_map_blocks(शून्य, inode, &map, 0);
			अगर (ret < 0)
				अवरोध;

			अगर (ret > 0) अणु
				path = ext4_find_extent(inode, map.m_lblk, शून्य, 0);
				अगर (!IS_ERR(path)) अणु
					क्रम (j = 0; j < path->p_depth; j++)
						ext4_mb_mark_bb(inode->i_sb,
							path[j].p_block, 1, 1);
					ext4_ext_drop_refs(path);
					kमुक्त(path);
				पूर्ण
				cur += ret;
				ext4_mb_mark_bb(inode->i_sb, map.m_pblk,
							map.m_len, 1);
			पूर्ण अन्यथा अणु
				cur = cur + (map.m_len ? map.m_len : 1);
			पूर्ण
		पूर्ण
		iput(inode);
	पूर्ण
पूर्ण

/*
 * Check अगर block is in excluded regions क्रम block allocation. The simple
 * allocator that runs during replay phase is calls this function to see
 * अगर it is okay to use a block.
 */
bool ext4_fc_replay_check_excluded(काष्ठा super_block *sb, ext4_fsblk_t blk)
अणु
	पूर्णांक i;
	काष्ठा ext4_fc_replay_state *state;

	state = &EXT4_SB(sb)->s_fc_replay_state;
	क्रम (i = 0; i < state->fc_regions_valid; i++) अणु
		अगर (state->fc_regions[i].ino == 0 ||
			state->fc_regions[i].len == 0)
			जारी;
		अगर (blk >= state->fc_regions[i].pblk &&
		    blk < state->fc_regions[i].pblk + state->fc_regions[i].len)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* Cleanup function called after replay */
व्योम ext4_fc_replay_cleanup(काष्ठा super_block *sb)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);

	sbi->s_mount_state &= ~EXT4_FC_REPLAY;
	kमुक्त(sbi->s_fc_replay_state.fc_regions);
	kमुक्त(sbi->s_fc_replay_state.fc_modअगरied_inodes);
पूर्ण

/*
 * Recovery Scan phase handler
 *
 * This function is called during the scan phase and is responsible
 * क्रम करोing following things:
 * - Make sure the fast commit area has valid tags क्रम replay
 * - Count number of tags that need to be replayed by the replay handler
 * - Verअगरy CRC
 * - Create a list of excluded blocks क्रम allocation during replay phase
 *
 * This function वापसs JBD2_FC_REPLAY_CONTINUE to indicate that SCAN is
 * incomplete and JBD2 should send more blocks. It वापसs JBD2_FC_REPLAY_STOP
 * to indicate that scan has finished and JBD2 can now start replay phase.
 * It वापसs a negative error to indicate that there was an error. At the end
 * of a successful scan phase, sbi->s_fc_replay_state.fc_replay_num_tags is set
 * to indicate the number of tags that need to replayed during the replay phase.
 */
अटल पूर्णांक ext4_fc_replay_scan(journal_t *journal,
				काष्ठा buffer_head *bh, पूर्णांक off,
				tid_t expected_tid)
अणु
	काष्ठा super_block *sb = journal->j_निजी;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_fc_replay_state *state;
	पूर्णांक ret = JBD2_FC_REPLAY_CONTINUE;
	काष्ठा ext4_fc_add_range ext;
	काष्ठा ext4_fc_tl tl;
	काष्ठा ext4_fc_tail tail;
	__u8 *start, *end, *cur, *val;
	काष्ठा ext4_fc_head head;
	काष्ठा ext4_extent *ex;

	state = &sbi->s_fc_replay_state;

	start = (u8 *)bh->b_data;
	end = (__u8 *)bh->b_data + journal->j_blocksize - 1;

	अगर (state->fc_replay_expected_off == 0) अणु
		state->fc_cur_tag = 0;
		state->fc_replay_num_tags = 0;
		state->fc_crc = 0;
		state->fc_regions = शून्य;
		state->fc_regions_valid = state->fc_regions_used =
			state->fc_regions_size = 0;
		/* Check अगर we can stop early */
		अगर (le16_to_cpu(((काष्ठा ext4_fc_tl *)start)->fc_tag)
			!= EXT4_FC_TAG_HEAD)
			वापस 0;
	पूर्ण

	अगर (off != state->fc_replay_expected_off) अणु
		ret = -EFSCORRUPTED;
		जाओ out_err;
	पूर्ण

	state->fc_replay_expected_off++;
	क्रम (cur = start; cur < end; cur = cur + माप(tl) + le16_to_cpu(tl.fc_len)) अणु
		स_नकल(&tl, cur, माप(tl));
		val = cur + माप(tl);
		jbd_debug(3, "Scan phase, tag:%s, blk %lld\n",
			  tag2str(le16_to_cpu(tl.fc_tag)), bh->b_blocknr);
		चयन (le16_to_cpu(tl.fc_tag)) अणु
		हाल EXT4_FC_TAG_ADD_RANGE:
			स_नकल(&ext, val, माप(ext));
			ex = (काष्ठा ext4_extent *)&ext.fc_ex;
			ret = ext4_fc_record_regions(sb,
				le32_to_cpu(ext.fc_ino),
				le32_to_cpu(ex->ee_block), ext4_ext_pblock(ex),
				ext4_ext_get_actual_len(ex));
			अगर (ret < 0)
				अवरोध;
			ret = JBD2_FC_REPLAY_CONTINUE;
			fallthrough;
		हाल EXT4_FC_TAG_DEL_RANGE:
		हाल EXT4_FC_TAG_LINK:
		हाल EXT4_FC_TAG_UNLINK:
		हाल EXT4_FC_TAG_CREAT:
		हाल EXT4_FC_TAG_INODE:
		हाल EXT4_FC_TAG_PAD:
			state->fc_cur_tag++;
			state->fc_crc = ext4_chksum(sbi, state->fc_crc, cur,
					माप(tl) + le16_to_cpu(tl.fc_len));
			अवरोध;
		हाल EXT4_FC_TAG_TAIL:
			state->fc_cur_tag++;
			स_नकल(&tail, val, माप(tail));
			state->fc_crc = ext4_chksum(sbi, state->fc_crc, cur,
						माप(tl) +
						दुरत्व(काष्ठा ext4_fc_tail,
						fc_crc));
			अगर (le32_to_cpu(tail.fc_tid) == expected_tid &&
				le32_to_cpu(tail.fc_crc) == state->fc_crc) अणु
				state->fc_replay_num_tags = state->fc_cur_tag;
				state->fc_regions_valid =
					state->fc_regions_used;
			पूर्ण अन्यथा अणु
				ret = state->fc_replay_num_tags ?
					JBD2_FC_REPLAY_STOP : -EFSBADCRC;
			पूर्ण
			state->fc_crc = 0;
			अवरोध;
		हाल EXT4_FC_TAG_HEAD:
			स_नकल(&head, val, माप(head));
			अगर (le32_to_cpu(head.fc_features) &
				~EXT4_FC_SUPPORTED_FEATURES) अणु
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			अगर (le32_to_cpu(head.fc_tid) != expected_tid) अणु
				ret = JBD2_FC_REPLAY_STOP;
				अवरोध;
			पूर्ण
			state->fc_cur_tag++;
			state->fc_crc = ext4_chksum(sbi, state->fc_crc, cur,
					    माप(tl) + le16_to_cpu(tl.fc_len));
			अवरोध;
		शेष:
			ret = state->fc_replay_num_tags ?
				JBD2_FC_REPLAY_STOP : -ECANCELED;
		पूर्ण
		अगर (ret < 0 || ret == JBD2_FC_REPLAY_STOP)
			अवरोध;
	पूर्ण

out_err:
	trace_ext4_fc_replay_scan(sb, ret, off);
	वापस ret;
पूर्ण

/*
 * Main recovery path entry poपूर्णांक.
 * The meaning of वापस codes is similar as above.
 */
अटल पूर्णांक ext4_fc_replay(journal_t *journal, काष्ठा buffer_head *bh,
				क्रमागत passtype pass, पूर्णांक off, tid_t expected_tid)
अणु
	काष्ठा super_block *sb = journal->j_निजी;
	काष्ठा ext4_sb_info *sbi = EXT4_SB(sb);
	काष्ठा ext4_fc_tl tl;
	__u8 *start, *end, *cur, *val;
	पूर्णांक ret = JBD2_FC_REPLAY_CONTINUE;
	काष्ठा ext4_fc_replay_state *state = &sbi->s_fc_replay_state;
	काष्ठा ext4_fc_tail tail;

	अगर (pass == PASS_SCAN) अणु
		state->fc_current_pass = PASS_SCAN;
		वापस ext4_fc_replay_scan(journal, bh, off, expected_tid);
	पूर्ण

	अगर (state->fc_current_pass != pass) अणु
		state->fc_current_pass = pass;
		sbi->s_mount_state |= EXT4_FC_REPLAY;
	पूर्ण
	अगर (!sbi->s_fc_replay_state.fc_replay_num_tags) अणु
		jbd_debug(1, "Replay stops\n");
		ext4_fc_set_biपंचांगaps_and_counters(sb);
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_EXT4_DEBUG
	अगर (sbi->s_fc_debug_max_replay && off >= sbi->s_fc_debug_max_replay) अणु
		pr_warn("Dropping fc block %d because max_replay set\n", off);
		वापस JBD2_FC_REPLAY_STOP;
	पूर्ण
#पूर्ण_अगर

	start = (u8 *)bh->b_data;
	end = (__u8 *)bh->b_data + journal->j_blocksize - 1;

	क्रम (cur = start; cur < end; cur = cur + माप(tl) + le16_to_cpu(tl.fc_len)) अणु
		स_नकल(&tl, cur, माप(tl));
		val = cur + माप(tl);

		अगर (state->fc_replay_num_tags == 0) अणु
			ret = JBD2_FC_REPLAY_STOP;
			ext4_fc_set_biपंचांगaps_and_counters(sb);
			अवरोध;
		पूर्ण
		jbd_debug(3, "Replay phase, tag:%s\n",
				tag2str(le16_to_cpu(tl.fc_tag)));
		state->fc_replay_num_tags--;
		चयन (le16_to_cpu(tl.fc_tag)) अणु
		हाल EXT4_FC_TAG_LINK:
			ret = ext4_fc_replay_link(sb, &tl, val);
			अवरोध;
		हाल EXT4_FC_TAG_UNLINK:
			ret = ext4_fc_replay_unlink(sb, &tl, val);
			अवरोध;
		हाल EXT4_FC_TAG_ADD_RANGE:
			ret = ext4_fc_replay_add_range(sb, &tl, val);
			अवरोध;
		हाल EXT4_FC_TAG_CREAT:
			ret = ext4_fc_replay_create(sb, &tl, val);
			अवरोध;
		हाल EXT4_FC_TAG_DEL_RANGE:
			ret = ext4_fc_replay_del_range(sb, &tl, val);
			अवरोध;
		हाल EXT4_FC_TAG_INODE:
			ret = ext4_fc_replay_inode(sb, &tl, val);
			अवरोध;
		हाल EXT4_FC_TAG_PAD:
			trace_ext4_fc_replay(sb, EXT4_FC_TAG_PAD, 0,
					     le16_to_cpu(tl.fc_len), 0);
			अवरोध;
		हाल EXT4_FC_TAG_TAIL:
			trace_ext4_fc_replay(sb, EXT4_FC_TAG_TAIL, 0,
					     le16_to_cpu(tl.fc_len), 0);
			स_नकल(&tail, val, माप(tail));
			WARN_ON(le32_to_cpu(tail.fc_tid) != expected_tid);
			अवरोध;
		हाल EXT4_FC_TAG_HEAD:
			अवरोध;
		शेष:
			trace_ext4_fc_replay(sb, le16_to_cpu(tl.fc_tag), 0,
					     le16_to_cpu(tl.fc_len), 0);
			ret = -ECANCELED;
			अवरोध;
		पूर्ण
		अगर (ret < 0)
			अवरोध;
		ret = JBD2_FC_REPLAY_CONTINUE;
	पूर्ण
	वापस ret;
पूर्ण

व्योम ext4_fc_init(काष्ठा super_block *sb, journal_t *journal)
अणु
	/*
	 * We set replay callback even अगर fast commit disabled because we may
	 * could still have fast commit blocks that need to be replayed even अगर
	 * fast commit has now been turned off.
	 */
	journal->j_fc_replay_callback = ext4_fc_replay;
	अगर (!test_opt2(sb, JOURNAL_FAST_COMMIT))
		वापस;
	journal->j_fc_cleanup_callback = ext4_fc_cleanup;
पूर्ण

अटल स्थिर अक्षर *fc_ineligible_reasons[] = अणु
	"Extended attributes changed",
	"Cross rename",
	"Journal flag changed",
	"Insufficient memory",
	"Swap boot",
	"Resize",
	"Dir renamed",
	"Falloc range op",
	"Data journalling",
	"FC Commit Failed"
पूर्ण;

पूर्णांक ext4_fc_info_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ext4_sb_info *sbi = EXT4_SB((काष्ठा super_block *)seq->निजी);
	काष्ठा ext4_fc_stats *stats = &sbi->s_fc_stats;
	पूर्णांक i;

	अगर (v != SEQ_START_TOKEN)
		वापस 0;

	seq_म_लिखो(seq,
		"fc stats:\n%ld commits\n%ld ineligible\n%ld numblks\n%lluus avg_commit_time\n",
		   stats->fc_num_commits, stats->fc_ineligible_commits,
		   stats->fc_numblks,
		   भाग_u64(sbi->s_fc_avg_commit_समय, 1000));
	seq_माला_दो(seq, "Ineligible reasons:\n");
	क्रम (i = 0; i < EXT4_FC_REASON_MAX; i++)
		seq_म_लिखो(seq, "\"%s\":\t%d\n", fc_ineligible_reasons[i],
			stats->fc_ineligible_reason_count[i]);

	वापस 0;
पूर्ण

पूर्णांक __init ext4_fc_init_dentry_cache(व्योम)
अणु
	ext4_fc_dentry_cachep = KMEM_CACHE(ext4_fc_dentry_update,
					   SLAB_RECLAIM_ACCOUNT);

	अगर (ext4_fc_dentry_cachep == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
