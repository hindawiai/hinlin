<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * journal.c
 *
 * Defines functions of journalling api
 *
 * Copyright (C) 2003, 2004 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/समय.स>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/delay.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "blockcheck.h"
#समावेश "dir.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "heartbeat.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "localalloc.h"
#समावेश "slot_map.h"
#समावेश "super.h"
#समावेश "sysfile.h"
#समावेश "uptodate.h"
#समावेश "quota.h"
#समावेश "file.h"
#समावेश "namei.h"

#समावेश "buffer_head_io.h"
#समावेश "ocfs2_trace.h"

DEFINE_SPINLOCK(trans_inc_lock);

#घोषणा ORPHAN_SCAN_SCHEDULE_TIMEOUT 300000

अटल पूर्णांक ocfs2_क्रमce_पढ़ो_journal(काष्ठा inode *inode);
अटल पूर्णांक ocfs2_recover_node(काष्ठा ocfs2_super *osb,
			      पूर्णांक node_num, पूर्णांक slot_num);
अटल पूर्णांक __ocfs2_recovery_thपढ़ो(व्योम *arg);
अटल पूर्णांक ocfs2_commit_cache(काष्ठा ocfs2_super *osb);
अटल पूर्णांक __ocfs2_रुको_on_mount(काष्ठा ocfs2_super *osb, पूर्णांक quota);
अटल पूर्णांक ocfs2_journal_toggle_dirty(काष्ठा ocfs2_super *osb,
				      पूर्णांक dirty, पूर्णांक replayed);
अटल पूर्णांक ocfs2_trylock_journal(काष्ठा ocfs2_super *osb,
				 पूर्णांक slot_num);
अटल पूर्णांक ocfs2_recover_orphans(काष्ठा ocfs2_super *osb,
				 पूर्णांक slot,
				 क्रमागत ocfs2_orphan_reco_type orphan_reco_type);
अटल पूर्णांक ocfs2_commit_thपढ़ो(व्योम *arg);
अटल व्योम ocfs2_queue_recovery_completion(काष्ठा ocfs2_journal *journal,
					    पूर्णांक slot_num,
					    काष्ठा ocfs2_dinode *la_dinode,
					    काष्ठा ocfs2_dinode *tl_dinode,
					    काष्ठा ocfs2_quota_recovery *qrec,
					    क्रमागत ocfs2_orphan_reco_type orphan_reco_type);

अटल अंतरभूत पूर्णांक ocfs2_रुको_on_mount(काष्ठा ocfs2_super *osb)
अणु
	वापस __ocfs2_रुको_on_mount(osb, 0);
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_रुको_on_quotas(काष्ठा ocfs2_super *osb)
अणु
	वापस __ocfs2_रुको_on_mount(osb, 1);
पूर्ण

/*
 * This replay_map is to track online/offline slots, so we could recover
 * offline slots during recovery and mount
 */

क्रमागत ocfs2_replay_state अणु
	REPLAY_UNNEEDED = 0,	/* Replay is not needed, so ignore this map */
	REPLAY_NEEDED, 		/* Replay slots marked in rm_replay_slots */
	REPLAY_DONE 		/* Replay was alपढ़ोy queued */
पूर्ण;

काष्ठा ocfs2_replay_map अणु
	अचिन्हित पूर्णांक rm_slots;
	क्रमागत ocfs2_replay_state rm_state;
	अचिन्हित अक्षर rm_replay_slots[];
पूर्ण;

अटल व्योम ocfs2_replay_map_set_state(काष्ठा ocfs2_super *osb, पूर्णांक state)
अणु
	अगर (!osb->replay_map)
		वापस;

	/* If we've already queued the replay, we don't have any more to करो */
	अगर (osb->replay_map->rm_state == REPLAY_DONE)
		वापस;

	osb->replay_map->rm_state = state;
पूर्ण

पूर्णांक ocfs2_compute_replay_slots(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_replay_map *replay_map;
	पूर्णांक i, node_num;

	/* If replay map is alपढ़ोy set, we करोn't करो it again */
	अगर (osb->replay_map)
		वापस 0;

	replay_map = kzalloc(माप(काष्ठा ocfs2_replay_map) +
			     (osb->max_slots * माप(अक्षर)), GFP_KERNEL);

	अगर (!replay_map) अणु
		mlog_त्रुटि_सं(-ENOMEM);
		वापस -ENOMEM;
	पूर्ण

	spin_lock(&osb->osb_lock);

	replay_map->rm_slots = osb->max_slots;
	replay_map->rm_state = REPLAY_UNNEEDED;

	/* set rm_replay_slots क्रम offline slot(s) */
	क्रम (i = 0; i < replay_map->rm_slots; i++) अणु
		अगर (ocfs2_slot_to_node_num_locked(osb, i, &node_num) == -ENOENT)
			replay_map->rm_replay_slots[i] = 1;
	पूर्ण

	osb->replay_map = replay_map;
	spin_unlock(&osb->osb_lock);
	वापस 0;
पूर्ण

अटल व्योम ocfs2_queue_replay_slots(काष्ठा ocfs2_super *osb,
		क्रमागत ocfs2_orphan_reco_type orphan_reco_type)
अणु
	काष्ठा ocfs2_replay_map *replay_map = osb->replay_map;
	पूर्णांक i;

	अगर (!replay_map)
		वापस;

	अगर (replay_map->rm_state != REPLAY_NEEDED)
		वापस;

	क्रम (i = 0; i < replay_map->rm_slots; i++)
		अगर (replay_map->rm_replay_slots[i])
			ocfs2_queue_recovery_completion(osb->journal, i, शून्य,
							शून्य, शून्य,
							orphan_reco_type);
	replay_map->rm_state = REPLAY_DONE;
पूर्ण

अटल व्योम ocfs2_मुक्त_replay_slots(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_replay_map *replay_map = osb->replay_map;

	अगर (!osb->replay_map)
		वापस;

	kमुक्त(replay_map);
	osb->replay_map = शून्य;
पूर्ण

पूर्णांक ocfs2_recovery_init(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_recovery_map *rm;

	mutex_init(&osb->recovery_lock);
	osb->disable_recovery = 0;
	osb->recovery_thपढ़ो_task = शून्य;
	init_रुकोqueue_head(&osb->recovery_event);

	rm = kzalloc(माप(काष्ठा ocfs2_recovery_map) +
		     osb->max_slots * माप(अचिन्हित पूर्णांक),
		     GFP_KERNEL);
	अगर (!rm) अणु
		mlog_त्रुटि_सं(-ENOMEM);
		वापस -ENOMEM;
	पूर्ण

	rm->rm_entries = (अचिन्हित पूर्णांक *)((अक्षर *)rm +
					  माप(काष्ठा ocfs2_recovery_map));
	osb->recovery_map = rm;

	वापस 0;
पूर्ण

/* we can't grab the goofy sem lock from inside रुको_event, so we use
 * memory barriers to make sure that we'll see the null task beक्रमe
 * being woken up */
अटल पूर्णांक ocfs2_recovery_thपढ़ो_running(काष्ठा ocfs2_super *osb)
अणु
	mb();
	वापस osb->recovery_thपढ़ो_task != शून्य;
पूर्ण

व्योम ocfs2_recovery_निकास(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_recovery_map *rm;

	/* disable any new recovery thपढ़ोs and रुको क्रम any currently
	 * running ones to निकास. Do this beक्रमe setting the vol_state. */
	mutex_lock(&osb->recovery_lock);
	osb->disable_recovery = 1;
	mutex_unlock(&osb->recovery_lock);
	रुको_event(osb->recovery_event, !ocfs2_recovery_thपढ़ो_running(osb));

	/* At this poपूर्णांक, we know that no more recovery thपढ़ोs can be
	 * launched, so रुको क्रम any recovery completion work to
	 * complete. */
	अगर (osb->ocfs2_wq)
		flush_workqueue(osb->ocfs2_wq);

	/*
	 * Now that recovery is shut करोwn, and the osb is about to be
	 * मुक्तd,  the osb_lock is not taken here.
	 */
	rm = osb->recovery_map;
	/* XXX: Should we bug अगर there are dirty entries? */

	kमुक्त(rm);
पूर्ण

अटल पूर्णांक __ocfs2_recovery_map_test(काष्ठा ocfs2_super *osb,
				     अचिन्हित पूर्णांक node_num)
अणु
	पूर्णांक i;
	काष्ठा ocfs2_recovery_map *rm = osb->recovery_map;

	निश्चित_spin_locked(&osb->osb_lock);

	क्रम (i = 0; i < rm->rm_used; i++) अणु
		अगर (rm->rm_entries[i] == node_num)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* Behaves like test-and-set.  Returns the previous value */
अटल पूर्णांक ocfs2_recovery_map_set(काष्ठा ocfs2_super *osb,
				  अचिन्हित पूर्णांक node_num)
अणु
	काष्ठा ocfs2_recovery_map *rm = osb->recovery_map;

	spin_lock(&osb->osb_lock);
	अगर (__ocfs2_recovery_map_test(osb, node_num)) अणु
		spin_unlock(&osb->osb_lock);
		वापस 1;
	पूर्ण

	/* XXX: Can this be exploited? Not from o2dlm... */
	BUG_ON(rm->rm_used >= osb->max_slots);

	rm->rm_entries[rm->rm_used] = node_num;
	rm->rm_used++;
	spin_unlock(&osb->osb_lock);

	वापस 0;
पूर्ण

अटल व्योम ocfs2_recovery_map_clear(काष्ठा ocfs2_super *osb,
				     अचिन्हित पूर्णांक node_num)
अणु
	पूर्णांक i;
	काष्ठा ocfs2_recovery_map *rm = osb->recovery_map;

	spin_lock(&osb->osb_lock);

	क्रम (i = 0; i < rm->rm_used; i++) अणु
		अगर (rm->rm_entries[i] == node_num)
			अवरोध;
	पूर्ण

	अगर (i < rm->rm_used) अणु
		/* XXX: be careful with the poपूर्णांकer math */
		स_हटाओ(&(rm->rm_entries[i]), &(rm->rm_entries[i + 1]),
			(rm->rm_used - i - 1) * माप(अचिन्हित पूर्णांक));
		rm->rm_used--;
	पूर्ण

	spin_unlock(&osb->osb_lock);
पूर्ण

अटल पूर्णांक ocfs2_commit_cache(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक flushed;
	काष्ठा ocfs2_journal *journal = शून्य;

	journal = osb->journal;

	/* Flush all pending commits and checkpoपूर्णांक the journal. */
	करोwn_ग_लिखो(&journal->j_trans_barrier);

	flushed = atomic_पढ़ो(&journal->j_num_trans);
	trace_ocfs2_commit_cache_begin(flushed);
	अगर (flushed == 0) अणु
		up_ग_लिखो(&journal->j_trans_barrier);
		जाओ finally;
	पूर्ण

	jbd2_journal_lock_updates(journal->j_journal);
	status = jbd2_journal_flush(journal->j_journal);
	jbd2_journal_unlock_updates(journal->j_journal);
	अगर (status < 0) अणु
		up_ग_लिखो(&journal->j_trans_barrier);
		mlog_त्रुटि_सं(status);
		जाओ finally;
	पूर्ण

	ocfs2_inc_trans_id(journal);

	flushed = atomic_पढ़ो(&journal->j_num_trans);
	atomic_set(&journal->j_num_trans, 0);
	up_ग_लिखो(&journal->j_trans_barrier);

	trace_ocfs2_commit_cache_end(journal->j_trans_id, flushed);

	ocfs2_wake_करोwnconvert_thपढ़ो(osb);
	wake_up(&journal->j_checkpoपूर्णांकed);
finally:
	वापस status;
पूर्ण

handle_t *ocfs2_start_trans(काष्ठा ocfs2_super *osb, पूर्णांक max_buffs)
अणु
	journal_t *journal = osb->journal->j_journal;
	handle_t *handle;

	BUG_ON(!osb || !osb->journal->j_journal);

	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		वापस ERR_PTR(-EROFS);

	BUG_ON(osb->journal->j_state == OCFS2_JOURNAL_FREE);
	BUG_ON(max_buffs <= 0);

	/* Nested transaction? Just वापस the handle... */
	अगर (journal_current_handle())
		वापस jbd2_journal_start(journal, max_buffs);

	sb_start_पूर्णांकग_लिखो(osb->sb);

	करोwn_पढ़ो(&osb->journal->j_trans_barrier);

	handle = jbd2_journal_start(journal, max_buffs);
	अगर (IS_ERR(handle)) अणु
		up_पढ़ो(&osb->journal->j_trans_barrier);
		sb_end_पूर्णांकग_लिखो(osb->sb);

		mlog_त्रुटि_सं(PTR_ERR(handle));

		अगर (is_journal_पातed(journal)) अणु
			ocfs2_पात(osb->sb, "Detected aborted journal\n");
			handle = ERR_PTR(-EROFS);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!ocfs2_mount_local(osb))
			atomic_inc(&(osb->journal->j_num_trans));
	पूर्ण

	वापस handle;
पूर्ण

पूर्णांक ocfs2_commit_trans(काष्ठा ocfs2_super *osb,
		       handle_t *handle)
अणु
	पूर्णांक ret, nested;
	काष्ठा ocfs2_journal *journal = osb->journal;

	BUG_ON(!handle);

	nested = handle->h_ref > 1;
	ret = jbd2_journal_stop(handle);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

	अगर (!nested) अणु
		up_पढ़ो(&journal->j_trans_barrier);
		sb_end_पूर्णांकग_लिखो(osb->sb);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * 'nblocks' is what you want to add to the current transaction.
 *
 * This might call jbd2_journal_restart() which will commit dirty buffers
 * and then restart the transaction. Beक्रमe calling
 * ocfs2_extend_trans(), any changed blocks should have been
 * dirtied. After calling it, all blocks which need to be changed must
 * go through another set of journal_access/journal_dirty calls.
 *
 * WARNING: This will not release any semaphores or disk locks taken
 * during the transaction, so make sure they were taken *beक्रमe*
 * start_trans or we'll have ordering deadlocks.
 *
 * WARNING2: Note that we करो *not* drop j_trans_barrier here. This is
 * good because transaction ids haven't yet been recorded on the
 * cluster locks associated with this handle.
 */
पूर्णांक ocfs2_extend_trans(handle_t *handle, पूर्णांक nblocks)
अणु
	पूर्णांक status, old_nblocks;

	BUG_ON(!handle);
	BUG_ON(nblocks < 0);

	अगर (!nblocks)
		वापस 0;

	old_nblocks = jbd2_handle_buffer_credits(handle);

	trace_ocfs2_extend_trans(old_nblocks, nblocks);

#अगर_घोषित CONFIG_OCFS2_DEBUG_FS
	status = 1;
#अन्यथा
	status = jbd2_journal_extend(handle, nblocks, 0);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
#पूर्ण_अगर

	अगर (status > 0) अणु
		trace_ocfs2_extend_trans_restart(old_nblocks + nblocks);
		status = jbd2_journal_restart(handle,
					      old_nblocks + nblocks);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	status = 0;
bail:
	वापस status;
पूर्ण

/*
 * If we have fewer than thresh credits, extend by OCFS2_MAX_TRANS_DATA.
 * If that fails, restart the transaction & regain ग_लिखो access क्रम the
 * buffer head which is used क्रम metadata modअगरications.
 * Taken from Ext4: extend_or_restart_transaction()
 */
पूर्णांक ocfs2_allocate_extend_trans(handle_t *handle, पूर्णांक thresh)
अणु
	पूर्णांक status, old_nblks;

	BUG_ON(!handle);

	old_nblks = jbd2_handle_buffer_credits(handle);
	trace_ocfs2_allocate_extend_trans(old_nblks, thresh);

	अगर (old_nblks < thresh)
		वापस 0;

	status = jbd2_journal_extend(handle, OCFS2_MAX_TRANS_DATA, 0);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	अगर (status > 0) अणु
		status = jbd2_journal_restart(handle, OCFS2_MAX_TRANS_DATA);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
	पूर्ण

bail:
	वापस status;
पूर्ण


काष्ठा ocfs2_triggers अणु
	काष्ठा jbd2_buffer_trigger_type	ot_triggers;
	पूर्णांक				ot_offset;
पूर्ण;

अटल अंतरभूत काष्ठा ocfs2_triggers *to_ocfs2_trigger(काष्ठा jbd2_buffer_trigger_type *triggers)
अणु
	वापस container_of(triggers, काष्ठा ocfs2_triggers, ot_triggers);
पूर्ण

अटल व्योम ocfs2_frozen_trigger(काष्ठा jbd2_buffer_trigger_type *triggers,
				 काष्ठा buffer_head *bh,
				 व्योम *data, माप_प्रकार size)
अणु
	काष्ठा ocfs2_triggers *ot = to_ocfs2_trigger(triggers);

	/*
	 * We aren't guaranteed to have the superblock here, so we
	 * must unconditionally compute the ecc data.
	 * __ocfs2_journal_access() will only set the triggers अगर
	 * metaecc is enabled.
	 */
	ocfs2_block_check_compute(data, size, data + ot->ot_offset);
पूर्ण

/*
 * Quota blocks have their own trigger because the काष्ठा ocfs2_block_check
 * offset depends on the blocksize.
 */
अटल व्योम ocfs2_dq_frozen_trigger(काष्ठा jbd2_buffer_trigger_type *triggers,
				 काष्ठा buffer_head *bh,
				 व्योम *data, माप_प्रकार size)
अणु
	काष्ठा ocfs2_disk_dqtrailer *dqt =
		ocfs2_block_dqtrailer(size, data);

	/*
	 * We aren't guaranteed to have the superblock here, so we
	 * must unconditionally compute the ecc data.
	 * __ocfs2_journal_access() will only set the triggers अगर
	 * metaecc is enabled.
	 */
	ocfs2_block_check_compute(data, size, &dqt->dq_check);
पूर्ण

/*
 * Directory blocks also have their own trigger because the
 * काष्ठा ocfs2_block_check offset depends on the blocksize.
 */
अटल व्योम ocfs2_db_frozen_trigger(काष्ठा jbd2_buffer_trigger_type *triggers,
				 काष्ठा buffer_head *bh,
				 व्योम *data, माप_प्रकार size)
अणु
	काष्ठा ocfs2_dir_block_trailer *trailer =
		ocfs2_dir_trailer_from_size(size, data);

	/*
	 * We aren't guaranteed to have the superblock here, so we
	 * must unconditionally compute the ecc data.
	 * __ocfs2_journal_access() will only set the triggers अगर
	 * metaecc is enabled.
	 */
	ocfs2_block_check_compute(data, size, &trailer->db_check);
पूर्ण

अटल व्योम ocfs2_पात_trigger(काष्ठा jbd2_buffer_trigger_type *triggers,
				काष्ठा buffer_head *bh)
अणु
	mlog(ML_ERROR,
	     "ocfs2_abort_trigger called by JBD2.  bh = 0x%lx, "
	     "bh->b_blocknr = %llu\n",
	     (अचिन्हित दीर्घ)bh,
	     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	ocfs2_error(bh->b_bdev->bd_super,
		    "JBD2 has aborted our journal, ocfs2 cannot continue\n");
पूर्ण

अटल काष्ठा ocfs2_triggers di_triggers = अणु
	.ot_triggers = अणु
		.t_frozen = ocfs2_frozen_trigger,
		.t_पात = ocfs2_पात_trigger,
	पूर्ण,
	.ot_offset	= दुरत्व(काष्ठा ocfs2_dinode, i_check),
पूर्ण;

अटल काष्ठा ocfs2_triggers eb_triggers = अणु
	.ot_triggers = अणु
		.t_frozen = ocfs2_frozen_trigger,
		.t_पात = ocfs2_पात_trigger,
	पूर्ण,
	.ot_offset	= दुरत्व(काष्ठा ocfs2_extent_block, h_check),
पूर्ण;

अटल काष्ठा ocfs2_triggers rb_triggers = अणु
	.ot_triggers = अणु
		.t_frozen = ocfs2_frozen_trigger,
		.t_पात = ocfs2_पात_trigger,
	पूर्ण,
	.ot_offset	= दुरत्व(काष्ठा ocfs2_refcount_block, rf_check),
पूर्ण;

अटल काष्ठा ocfs2_triggers gd_triggers = अणु
	.ot_triggers = अणु
		.t_frozen = ocfs2_frozen_trigger,
		.t_पात = ocfs2_पात_trigger,
	पूर्ण,
	.ot_offset	= दुरत्व(काष्ठा ocfs2_group_desc, bg_check),
पूर्ण;

अटल काष्ठा ocfs2_triggers db_triggers = अणु
	.ot_triggers = अणु
		.t_frozen = ocfs2_db_frozen_trigger,
		.t_पात = ocfs2_पात_trigger,
	पूर्ण,
पूर्ण;

अटल काष्ठा ocfs2_triggers xb_triggers = अणु
	.ot_triggers = अणु
		.t_frozen = ocfs2_frozen_trigger,
		.t_पात = ocfs2_पात_trigger,
	पूर्ण,
	.ot_offset	= दुरत्व(काष्ठा ocfs2_xattr_block, xb_check),
पूर्ण;

अटल काष्ठा ocfs2_triggers dq_triggers = अणु
	.ot_triggers = अणु
		.t_frozen = ocfs2_dq_frozen_trigger,
		.t_पात = ocfs2_पात_trigger,
	पूर्ण,
पूर्ण;

अटल काष्ठा ocfs2_triggers dr_triggers = अणु
	.ot_triggers = अणु
		.t_frozen = ocfs2_frozen_trigger,
		.t_पात = ocfs2_पात_trigger,
	पूर्ण,
	.ot_offset	= दुरत्व(काष्ठा ocfs2_dx_root_block, dr_check),
पूर्ण;

अटल काष्ठा ocfs2_triggers dl_triggers = अणु
	.ot_triggers = अणु
		.t_frozen = ocfs2_frozen_trigger,
		.t_पात = ocfs2_पात_trigger,
	पूर्ण,
	.ot_offset	= दुरत्व(काष्ठा ocfs2_dx_leaf, dl_check),
पूर्ण;

अटल पूर्णांक __ocfs2_journal_access(handle_t *handle,
				  काष्ठा ocfs2_caching_info *ci,
				  काष्ठा buffer_head *bh,
				  काष्ठा ocfs2_triggers *triggers,
				  पूर्णांक type)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_super *osb =
		OCFS2_SB(ocfs2_metadata_cache_get_super(ci));

	BUG_ON(!ci || !ci->ci_ops);
	BUG_ON(!handle);
	BUG_ON(!bh);

	trace_ocfs2_journal_access(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, type, bh->b_size);

	/* we can safely हटाओ this निश्चितion after testing. */
	अगर (!buffer_uptodate(bh)) अणु
		mlog(ML_ERROR, "giving me a buffer that's not uptodate!\n");
		mlog(ML_ERROR, "b_blocknr=%llu, b_state=0x%lx\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, bh->b_state);

		lock_buffer(bh);
		/*
		 * A previous transaction with a couple of buffer heads fail
		 * to checkpoपूर्णांक, so all the bhs are marked as BH_Write_EIO.
		 * For current transaction, the bh is just among those error
		 * bhs which previous transaction handle. We can't just clear
		 * its BH_Write_EIO and reuse directly, since other bhs are
		 * not written to disk yet and that will cause metadata
		 * inconsistency. So we should set fs पढ़ो-only to aव्योम
		 * further damage.
		 */
		अगर (buffer_ग_लिखो_io_error(bh) && !buffer_uptodate(bh)) अणु
			unlock_buffer(bh);
			वापस ocfs2_error(osb->sb, "A previous attempt to "
					"write this buffer head failed\n");
		पूर्ण
		unlock_buffer(bh);
	पूर्ण

	/* Set the current transaction inक्रमmation on the ci so
	 * that the locking code knows whether it can drop it's locks
	 * on this ci or not. We're रक्षित from the commit
	 * thपढ़ो updating the current transaction id until
	 * ocfs2_commit_trans() because ocfs2_start_trans() took
	 * j_trans_barrier क्रम us. */
	ocfs2_set_ci_lock_trans(osb->journal, ci);

	ocfs2_metadata_cache_io_lock(ci);
	चयन (type) अणु
	हाल OCFS2_JOURNAL_ACCESS_CREATE:
	हाल OCFS2_JOURNAL_ACCESS_WRITE:
		status = jbd2_journal_get_ग_लिखो_access(handle, bh);
		अवरोध;

	हाल OCFS2_JOURNAL_ACCESS_UNDO:
		status = jbd2_journal_get_unकरो_access(handle, bh);
		अवरोध;

	शेष:
		status = -EINVAL;
		mlog(ML_ERROR, "Unknown access type!\n");
	पूर्ण
	अगर (!status && ocfs2_meta_ecc(osb) && triggers)
		jbd2_journal_set_triggers(bh, &triggers->ot_triggers);
	ocfs2_metadata_cache_io_unlock(ci);

	अगर (status < 0)
		mlog(ML_ERROR, "Error %d getting %d access to buffer!\n",
		     status, type);

	वापस status;
पूर्ण

पूर्णांक ocfs2_journal_access_di(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, &di_triggers, type);
पूर्ण

पूर्णांक ocfs2_journal_access_eb(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, &eb_triggers, type);
पूर्ण

पूर्णांक ocfs2_journal_access_rb(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, &rb_triggers,
				      type);
पूर्ण

पूर्णांक ocfs2_journal_access_gd(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, &gd_triggers, type);
पूर्ण

पूर्णांक ocfs2_journal_access_db(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, &db_triggers, type);
पूर्ण

पूर्णांक ocfs2_journal_access_xb(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, &xb_triggers, type);
पूर्ण

पूर्णांक ocfs2_journal_access_dq(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, &dq_triggers, type);
पूर्ण

पूर्णांक ocfs2_journal_access_dr(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, &dr_triggers, type);
पूर्ण

पूर्णांक ocfs2_journal_access_dl(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, &dl_triggers, type);
पूर्ण

पूर्णांक ocfs2_journal_access(handle_t *handle, काष्ठा ocfs2_caching_info *ci,
			 काष्ठा buffer_head *bh, पूर्णांक type)
अणु
	वापस __ocfs2_journal_access(handle, ci, bh, शून्य, type);
पूर्ण

व्योम ocfs2_journal_dirty(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	पूर्णांक status;

	trace_ocfs2_journal_dirty((अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	status = jbd2_journal_dirty_metadata(handle, bh);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		अगर (!is_handle_पातed(handle)) अणु
			journal_t *journal = handle->h_transaction->t_journal;
			काष्ठा super_block *sb = bh->b_bdev->bd_super;

			mlog(ML_ERROR, "jbd2_journal_dirty_metadata failed. "
					"Aborting transaction and journal.\n");
			handle->h_err = status;
			jbd2_journal_पात_handle(handle);
			jbd2_journal_पात(journal, status);
			ocfs2_पात(sb, "Journal already aborted.\n");
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा OCFS2_DEFAULT_COMMIT_INTERVAL	(HZ * JBD2_DEFAULT_MAX_COMMIT_AGE)

व्योम ocfs2_set_journal_params(काष्ठा ocfs2_super *osb)
अणु
	journal_t *journal = osb->journal->j_journal;
	अचिन्हित दीर्घ commit_पूर्णांकerval = OCFS2_DEFAULT_COMMIT_INTERVAL;

	अगर (osb->osb_commit_पूर्णांकerval)
		commit_पूर्णांकerval = osb->osb_commit_पूर्णांकerval;

	ग_लिखो_lock(&journal->j_state_lock);
	journal->j_commit_पूर्णांकerval = commit_पूर्णांकerval;
	अगर (osb->s_mount_opt & OCFS2_MOUNT_BARRIER)
		journal->j_flags |= JBD2_BARRIER;
	अन्यथा
		journal->j_flags &= ~JBD2_BARRIER;
	ग_लिखो_unlock(&journal->j_state_lock);
पूर्ण

पूर्णांक ocfs2_journal_init(काष्ठा ocfs2_journal *journal, पूर्णांक *dirty)
अणु
	पूर्णांक status = -1;
	काष्ठा inode *inode = शून्य; /* the journal inode */
	journal_t *j_journal = शून्य;
	काष्ठा ocfs2_dinode *di = शून्य;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_super *osb;
	पूर्णांक inode_lock = 0;

	BUG_ON(!journal);

	osb = journal->j_osb;

	/* alपढ़ोy have the inode क्रम our journal */
	inode = ocfs2_get_प्रणाली_file_inode(osb, JOURNAL_SYSTEM_INODE,
					    osb->slot_num);
	अगर (inode == शून्य) अणु
		status = -EACCES;
		mlog_त्रुटि_सं(status);
		जाओ करोne;
	पूर्ण
	अगर (is_bad_inode(inode)) अणु
		mlog(ML_ERROR, "access error (bad inode)\n");
		iput(inode);
		inode = शून्य;
		status = -EACCES;
		जाओ करोne;
	पूर्ण

	SET_INODE_JOURNAL(inode);
	OCFS2_I(inode)->ip_खोलो_count++;

	/* Skip recovery रुकोs here - journal inode metadata never
	 * changes in a live cluster so it can be considered an
	 * exception to the rule. */
	status = ocfs2_inode_lock_full(inode, &bh, 1, OCFS2_META_LOCK_RECOVERY);
	अगर (status < 0) अणु
		अगर (status != -ERESTARTSYS)
			mlog(ML_ERROR, "Could not get lock on journal!\n");
		जाओ करोne;
	पूर्ण

	inode_lock = 1;
	di = (काष्ठा ocfs2_dinode *)bh->b_data;

	अगर (i_size_पढ़ो(inode) <  OCFS2_MIN_JOURNAL_SIZE) अणु
		mlog(ML_ERROR, "Journal file size (%lld) is too small!\n",
		     i_size_पढ़ो(inode));
		status = -EINVAL;
		जाओ करोne;
	पूर्ण

	trace_ocfs2_journal_init(i_size_पढ़ो(inode),
				 (अचिन्हित दीर्घ दीर्घ)inode->i_blocks,
				 OCFS2_I(inode)->ip_clusters);

	/* call the kernels journal init function now */
	j_journal = jbd2_journal_init_inode(inode);
	अगर (j_journal == शून्य) अणु
		mlog(ML_ERROR, "Linux journal layer error\n");
		status = -EINVAL;
		जाओ करोne;
	पूर्ण

	trace_ocfs2_journal_init_maxlen(j_journal->j_total_len);

	*dirty = (le32_to_cpu(di->id1.journal1.ij_flags) &
		  OCFS2_JOURNAL_सूचीTY_FL);

	journal->j_journal = j_journal;
	journal->j_journal->j_submit_inode_data_buffers =
		jbd2_journal_submit_inode_data_buffers;
	journal->j_journal->j_finish_inode_data_buffers =
		jbd2_journal_finish_inode_data_buffers;
	journal->j_inode = inode;
	journal->j_bh = bh;

	ocfs2_set_journal_params(osb);

	journal->j_state = OCFS2_JOURNAL_LOADED;

	status = 0;
करोne:
	अगर (status < 0) अणु
		अगर (inode_lock)
			ocfs2_inode_unlock(inode, 1);
		brअन्यथा(bh);
		अगर (inode) अणु
			OCFS2_I(inode)->ip_खोलो_count--;
			iput(inode);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम ocfs2_bump_recovery_generation(काष्ठा ocfs2_dinode *di)
अणु
	le32_add_cpu(&(di->id1.journal1.ij_recovery_generation), 1);
पूर्ण

अटल u32 ocfs2_get_recovery_generation(काष्ठा ocfs2_dinode *di)
अणु
	वापस le32_to_cpu(di->id1.journal1.ij_recovery_generation);
पूर्ण

अटल पूर्णांक ocfs2_journal_toggle_dirty(काष्ठा ocfs2_super *osb,
				      पूर्णांक dirty, पूर्णांक replayed)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक flags;
	काष्ठा ocfs2_journal *journal = osb->journal;
	काष्ठा buffer_head *bh = journal->j_bh;
	काष्ठा ocfs2_dinode *fe;

	fe = (काष्ठा ocfs2_dinode *)bh->b_data;

	/* The journal bh on the osb always comes from ocfs2_journal_init()
	 * and was validated there inside ocfs2_inode_lock_full().  It's a
	 * code bug अगर we mess it up. */
	BUG_ON(!OCFS2_IS_VALID_DINODE(fe));

	flags = le32_to_cpu(fe->id1.journal1.ij_flags);
	अगर (dirty)
		flags |= OCFS2_JOURNAL_सूचीTY_FL;
	अन्यथा
		flags &= ~OCFS2_JOURNAL_सूचीTY_FL;
	fe->id1.journal1.ij_flags = cpu_to_le32(flags);

	अगर (replayed)
		ocfs2_bump_recovery_generation(fe);

	ocfs2_compute_meta_ecc(osb->sb, bh->b_data, &fe->i_check);
	status = ocfs2_ग_लिखो_block(osb, bh, INODE_CACHE(journal->j_inode));
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

/*
 * If the journal has been kदो_स्मृति'd it needs to be मुक्तd after this
 * call.
 */
व्योम ocfs2_journal_shutकरोwn(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_journal *journal = शून्य;
	पूर्णांक status = 0;
	काष्ठा inode *inode = शून्य;
	पूर्णांक num_running_trans = 0;

	BUG_ON(!osb);

	journal = osb->journal;
	अगर (!journal)
		जाओ करोne;

	inode = journal->j_inode;

	अगर (journal->j_state != OCFS2_JOURNAL_LOADED)
		जाओ करोne;

	/* need to inc inode use count - jbd2_journal_destroy will iput. */
	अगर (!igrab(inode))
		BUG();

	num_running_trans = atomic_पढ़ो(&(osb->journal->j_num_trans));
	trace_ocfs2_journal_shutकरोwn(num_running_trans);

	/* Do a commit_cache here. It will flush our journal, *and*
	 * release any locks that are still held.
	 * set the SHUTDOWN flag and release the trans lock.
	 * the commit thपढ़ो will take the trans lock क्रम us below. */
	journal->j_state = OCFS2_JOURNAL_IN_SHUTDOWN;

	/* The OCFS2_JOURNAL_IN_SHUTDOWN will संकेत to commit_cache to not
	 * drop the trans_lock (which we want to hold until we
	 * completely destroy the journal. */
	अगर (osb->commit_task) अणु
		/* Wait क्रम the commit thपढ़ो */
		trace_ocfs2_journal_shutकरोwn_रुको(osb->commit_task);
		kthपढ़ो_stop(osb->commit_task);
		osb->commit_task = शून्य;
	पूर्ण

	BUG_ON(atomic_पढ़ो(&(osb->journal->j_num_trans)) != 0);

	अगर (ocfs2_mount_local(osb)) अणु
		jbd2_journal_lock_updates(journal->j_journal);
		status = jbd2_journal_flush(journal->j_journal);
		jbd2_journal_unlock_updates(journal->j_journal);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
	पूर्ण

	/* Shutकरोwn the kernel journal प्रणाली */
	अगर (!jbd2_journal_destroy(journal->j_journal) && !status) अणु
		/*
		 * Do not toggle अगर flush was unsuccessful otherwise
		 * will leave dirty metadata in a "clean" journal
		 */
		status = ocfs2_journal_toggle_dirty(osb, 0, 0);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
	पूर्ण
	journal->j_journal = शून्य;

	OCFS2_I(inode)->ip_खोलो_count--;

	/* unlock our journal */
	ocfs2_inode_unlock(inode, 1);

	brअन्यथा(journal->j_bh);
	journal->j_bh = शून्य;

	journal->j_state = OCFS2_JOURNAL_FREE;

//	up_ग_लिखो(&journal->j_trans_barrier);
करोne:
	iput(inode);
पूर्ण

अटल व्योम ocfs2_clear_journal_error(काष्ठा super_block *sb,
				      journal_t *journal,
				      पूर्णांक slot)
अणु
	पूर्णांक olderr;

	olderr = jbd2_journal_त्रुटि_सं(journal);
	अगर (olderr) अणु
		mlog(ML_ERROR, "File system error %d recorded in "
		     "journal %u.\n", olderr, slot);
		mlog(ML_ERROR, "File system on device %s needs checking.\n",
		     sb->s_id);

		jbd2_journal_ack_err(journal);
		jbd2_journal_clear_err(journal);
	पूर्ण
पूर्ण

पूर्णांक ocfs2_journal_load(काष्ठा ocfs2_journal *journal, पूर्णांक local, पूर्णांक replayed)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_super *osb;

	BUG_ON(!journal);

	osb = journal->j_osb;

	status = jbd2_journal_load(journal->j_journal);
	अगर (status < 0) अणु
		mlog(ML_ERROR, "Failed to load journal!\n");
		जाओ करोne;
	पूर्ण

	ocfs2_clear_journal_error(osb->sb, journal->j_journal, osb->slot_num);

	अगर (replayed) अणु
		jbd2_journal_lock_updates(journal->j_journal);
		status = jbd2_journal_flush(journal->j_journal);
		jbd2_journal_unlock_updates(journal->j_journal);
		अगर (status < 0)
			mlog_त्रुटि_सं(status);
	पूर्ण

	status = ocfs2_journal_toggle_dirty(osb, 1, replayed);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ करोne;
	पूर्ण

	/* Launch the commit thपढ़ो */
	अगर (!local) अणु
		osb->commit_task = kthपढ़ो_run(ocfs2_commit_thपढ़ो, osb,
				"ocfs2cmt-%s", osb->uuid_str);
		अगर (IS_ERR(osb->commit_task)) अणु
			status = PTR_ERR(osb->commit_task);
			osb->commit_task = शून्य;
			mlog(ML_ERROR, "unable to launch ocfs2commit thread, "
			     "error=%d", status);
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा
		osb->commit_task = शून्य;

करोne:
	वापस status;
पूर्ण


/* 'full' flag tells us whether we clear out all blocks or अगर we just
 * mark the journal clean */
पूर्णांक ocfs2_journal_wipe(काष्ठा ocfs2_journal *journal, पूर्णांक full)
अणु
	पूर्णांक status;

	BUG_ON(!journal);

	status = jbd2_journal_wipe(journal->j_journal, full);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_journal_toggle_dirty(journal->j_osb, 0, 0);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

bail:
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_recovery_completed(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक empty;
	काष्ठा ocfs2_recovery_map *rm = osb->recovery_map;

	spin_lock(&osb->osb_lock);
	empty = (rm->rm_used == 0);
	spin_unlock(&osb->osb_lock);

	वापस empty;
पूर्ण

व्योम ocfs2_रुको_क्रम_recovery(काष्ठा ocfs2_super *osb)
अणु
	रुको_event(osb->recovery_event, ocfs2_recovery_completed(osb));
पूर्ण

/*
 * JBD Might पढ़ो a cached version of another nodes journal file. We
 * करोn't want this as this file changes often and we get no
 * notअगरication on those changes. The only way to be sure that we've
 * got the most up to date version of those blocks then is to क्रमce
 * पढ़ो them off disk. Just searching through the buffer cache won't
 * work as there may be pages backing this file which are still marked
 * up to date. We know things can't change on this file underneath us
 * as we have the lock by now :)
 */
अटल पूर्णांक ocfs2_क्रमce_पढ़ो_journal(काष्ठा inode *inode)
अणु
	पूर्णांक status = 0;
	पूर्णांक i;
	u64 v_blkno, p_blkno, p_blocks, num_blocks;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	num_blocks = ocfs2_blocks_क्रम_bytes(inode->i_sb, i_size_पढ़ो(inode));
	v_blkno = 0;
	जबतक (v_blkno < num_blocks) अणु
		status = ocfs2_extent_map_get_blocks(inode, v_blkno,
						     &p_blkno, &p_blocks, शून्य);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		क्रम (i = 0; i < p_blocks; i++, p_blkno++) अणु
			bh = __find_get_block(osb->sb->s_bdev, p_blkno,
					osb->sb->s_blocksize);
			/* block not cached. */
			अगर (!bh)
				जारी;

			brअन्यथा(bh);
			bh = शून्य;
			/* We are पढ़ोing journal data which should not
			 * be put in the uptodate cache.
			 */
			status = ocfs2_पढ़ो_blocks_sync(osb, p_blkno, 1, &bh);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण

			brअन्यथा(bh);
			bh = शून्य;
		पूर्ण

		v_blkno += p_blocks;
	पूर्ण

bail:
	वापस status;
पूर्ण

काष्ठा ocfs2_la_recovery_item अणु
	काष्ठा list_head	lri_list;
	पूर्णांक			lri_slot;
	काष्ठा ocfs2_dinode	*lri_la_dinode;
	काष्ठा ocfs2_dinode	*lri_tl_dinode;
	काष्ठा ocfs2_quota_recovery *lri_qrec;
	क्रमागत ocfs2_orphan_reco_type  lri_orphan_reco_type;
पूर्ण;

/* Does the second half of the recovery process. By this poपूर्णांक, the
 * node is marked clean and can actually be considered recovered,
 * hence it's no longer in the recovery map, but there's still some
 * cleanup we can करो which shouldn't happen within the recovery thपढ़ो
 * as locking in that context becomes very dअगरficult अगर we are to take
 * recovering nodes पूर्णांकo account.
 *
 * NOTE: This function can and will sleep on recovery of other nodes
 * during cluster locking, just like any other ocfs2 process.
 */
व्योम ocfs2_complete_recovery(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_journal *journal =
		container_of(work, काष्ठा ocfs2_journal, j_recovery_work);
	काष्ठा ocfs2_super *osb = journal->j_osb;
	काष्ठा ocfs2_dinode *la_dinode, *tl_dinode;
	काष्ठा ocfs2_la_recovery_item *item, *n;
	काष्ठा ocfs2_quota_recovery *qrec;
	क्रमागत ocfs2_orphan_reco_type orphan_reco_type;
	LIST_HEAD(पंचांगp_la_list);

	trace_ocfs2_complete_recovery(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(journal->j_inode)->ip_blkno);

	spin_lock(&journal->j_lock);
	list_splice_init(&journal->j_la_cleanups, &पंचांगp_la_list);
	spin_unlock(&journal->j_lock);

	list_क्रम_each_entry_safe(item, n, &पंचांगp_la_list, lri_list) अणु
		list_del_init(&item->lri_list);

		ocfs2_रुको_on_quotas(osb);

		la_dinode = item->lri_la_dinode;
		tl_dinode = item->lri_tl_dinode;
		qrec = item->lri_qrec;
		orphan_reco_type = item->lri_orphan_reco_type;

		trace_ocfs2_complete_recovery_slot(item->lri_slot,
			la_dinode ? le64_to_cpu(la_dinode->i_blkno) : 0,
			tl_dinode ? le64_to_cpu(tl_dinode->i_blkno) : 0,
			qrec);

		अगर (la_dinode) अणु
			ret = ocfs2_complete_local_alloc_recovery(osb,
								  la_dinode);
			अगर (ret < 0)
				mlog_त्रुटि_सं(ret);

			kमुक्त(la_dinode);
		पूर्ण

		अगर (tl_dinode) अणु
			ret = ocfs2_complete_truncate_log_recovery(osb,
								   tl_dinode);
			अगर (ret < 0)
				mlog_त्रुटि_सं(ret);

			kमुक्त(tl_dinode);
		पूर्ण

		ret = ocfs2_recover_orphans(osb, item->lri_slot,
				orphan_reco_type);
		अगर (ret < 0)
			mlog_त्रुटि_सं(ret);

		अगर (qrec) अणु
			ret = ocfs2_finish_quota_recovery(osb, qrec,
							  item->lri_slot);
			अगर (ret < 0)
				mlog_त्रुटि_सं(ret);
			/* Recovery info is alपढ़ोy मुक्तd now */
		पूर्ण

		kमुक्त(item);
	पूर्ण

	trace_ocfs2_complete_recovery_end(ret);
पूर्ण

/* NOTE: This function always eats your references to la_dinode and
 * tl_dinode, either manually on error, or by passing them to
 * ocfs2_complete_recovery */
अटल व्योम ocfs2_queue_recovery_completion(काष्ठा ocfs2_journal *journal,
					    पूर्णांक slot_num,
					    काष्ठा ocfs2_dinode *la_dinode,
					    काष्ठा ocfs2_dinode *tl_dinode,
					    काष्ठा ocfs2_quota_recovery *qrec,
					    क्रमागत ocfs2_orphan_reco_type orphan_reco_type)
अणु
	काष्ठा ocfs2_la_recovery_item *item;

	item = kदो_स्मृति(माप(काष्ठा ocfs2_la_recovery_item), GFP_NOFS);
	अगर (!item) अणु
		/* Though we wish to aव्योम it, we are in fact safe in
		 * skipping local alloc cleanup as fsck.ocfs2 is more
		 * than capable of reclaiming unused space. */
		kमुक्त(la_dinode);
		kमुक्त(tl_dinode);

		अगर (qrec)
			ocfs2_मुक्त_quota_recovery(qrec);

		mlog_त्रुटि_सं(-ENOMEM);
		वापस;
	पूर्ण

	INIT_LIST_HEAD(&item->lri_list);
	item->lri_la_dinode = la_dinode;
	item->lri_slot = slot_num;
	item->lri_tl_dinode = tl_dinode;
	item->lri_qrec = qrec;
	item->lri_orphan_reco_type = orphan_reco_type;

	spin_lock(&journal->j_lock);
	list_add_tail(&item->lri_list, &journal->j_la_cleanups);
	queue_work(journal->j_osb->ocfs2_wq, &journal->j_recovery_work);
	spin_unlock(&journal->j_lock);
पूर्ण

/* Called by the mount code to queue recovery the last part of
 * recovery क्रम it's own and offline slot(s). */
व्योम ocfs2_complete_mount_recovery(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_journal *journal = osb->journal;

	अगर (ocfs2_is_hard_पढ़ोonly(osb))
		वापस;

	/* No need to queue up our truncate_log as regular cleanup will catch
	 * that */
	ocfs2_queue_recovery_completion(journal, osb->slot_num,
					osb->local_alloc_copy, शून्य, शून्य,
					ORPHAN_NEED_TRUNCATE);
	ocfs2_schedule_truncate_log_flush(osb, 0);

	osb->local_alloc_copy = शून्य;

	/* queue to recover orphan slots क्रम all offline slots */
	ocfs2_replay_map_set_state(osb, REPLAY_NEEDED);
	ocfs2_queue_replay_slots(osb, ORPHAN_NEED_TRUNCATE);
	ocfs2_मुक्त_replay_slots(osb);
पूर्ण

व्योम ocfs2_complete_quota_recovery(काष्ठा ocfs2_super *osb)
अणु
	अगर (osb->quota_rec) अणु
		ocfs2_queue_recovery_completion(osb->journal,
						osb->slot_num,
						शून्य,
						शून्य,
						osb->quota_rec,
						ORPHAN_NEED_TRUNCATE);
		osb->quota_rec = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __ocfs2_recovery_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक status, node_num, slot_num;
	काष्ठा ocfs2_super *osb = arg;
	काष्ठा ocfs2_recovery_map *rm = osb->recovery_map;
	पूर्णांक *rm_quota = शून्य;
	पूर्णांक rm_quota_used = 0, i;
	काष्ठा ocfs2_quota_recovery *qrec;

	/* Whether the quota supported. */
	पूर्णांक quota_enabled = OCFS2_HAS_RO_COMPAT_FEATURE(osb->sb,
			OCFS2_FEATURE_RO_COMPAT_USRQUOTA)
		|| OCFS2_HAS_RO_COMPAT_FEATURE(osb->sb,
			OCFS2_FEATURE_RO_COMPAT_GRPQUOTA);

	status = ocfs2_रुको_on_mount(osb);
	अगर (status < 0) अणु
		जाओ bail;
	पूर्ण

	अगर (quota_enabled) अणु
		rm_quota = kसुस्मृति(osb->max_slots, माप(पूर्णांक), GFP_NOFS);
		अगर (!rm_quota) अणु
			status = -ENOMEM;
			जाओ bail;
		पूर्ण
	पूर्ण
restart:
	status = ocfs2_super_lock(osb, 1);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_compute_replay_slots(osb);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	/* queue recovery क्रम our own slot */
	ocfs2_queue_recovery_completion(osb->journal, osb->slot_num, शून्य,
					शून्य, शून्य, ORPHAN_NO_NEED_TRUNCATE);

	spin_lock(&osb->osb_lock);
	जबतक (rm->rm_used) अणु
		/* It's always safe to remove entry zero, as we won't
		 * clear it until ocfs2_recover_node() has succeeded. */
		node_num = rm->rm_entries[0];
		spin_unlock(&osb->osb_lock);
		slot_num = ocfs2_node_num_to_slot(osb, node_num);
		trace_ocfs2_recovery_thपढ़ो_node(node_num, slot_num);
		अगर (slot_num == -ENOENT) अणु
			status = 0;
			जाओ skip_recovery;
		पूर्ण

		/* It is a bit subtle with quota recovery. We cannot करो it
		 * immediately because we have to obtain cluster locks from
		 * quota files and we also करोn't want to just skip it because
		 * then quota usage would be out of sync until some node takes
		 * the slot. So we remember which nodes need quota recovery
		 * and when everything अन्यथा is करोne, we recover quotas. */
		अगर (quota_enabled) अणु
			क्रम (i = 0; i < rm_quota_used
					&& rm_quota[i] != slot_num; i++)
				;

			अगर (i == rm_quota_used)
				rm_quota[rm_quota_used++] = slot_num;
		पूर्ण

		status = ocfs2_recover_node(osb, node_num, slot_num);
skip_recovery:
		अगर (!status) अणु
			ocfs2_recovery_map_clear(osb, node_num);
		पूर्ण अन्यथा अणु
			mlog(ML_ERROR,
			     "Error %d recovering node %d on device (%u,%u)!\n",
			     status, node_num,
			     MAJOR(osb->sb->s_dev), MINOR(osb->sb->s_dev));
			mlog(ML_ERROR, "Volume requires unmount.\n");
		पूर्ण

		spin_lock(&osb->osb_lock);
	पूर्ण
	spin_unlock(&osb->osb_lock);
	trace_ocfs2_recovery_thपढ़ो_end(status);

	/* Refresh all journal recovery generations from disk */
	status = ocfs2_check_journals_nolocks(osb);
	status = (status == -EROFS) ? 0 : status;
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	/* Now it is right समय to recover quotas... We have to करो this under
	 * superblock lock so that no one can start using the slot (and crash)
	 * beक्रमe we recover it */
	अगर (quota_enabled) अणु
		क्रम (i = 0; i < rm_quota_used; i++) अणु
			qrec = ocfs2_begin_quota_recovery(osb, rm_quota[i]);
			अगर (IS_ERR(qrec)) अणु
				status = PTR_ERR(qrec);
				mlog_त्रुटि_सं(status);
				जारी;
			पूर्ण
			ocfs2_queue_recovery_completion(osb->journal,
					rm_quota[i],
					शून्य, शून्य, qrec,
					ORPHAN_NEED_TRUNCATE);
		पूर्ण
	पूर्ण

	ocfs2_super_unlock(osb, 1);

	/* queue recovery क्रम offline slots */
	ocfs2_queue_replay_slots(osb, ORPHAN_NEED_TRUNCATE);

bail:
	mutex_lock(&osb->recovery_lock);
	अगर (!status && !ocfs2_recovery_completed(osb)) अणु
		mutex_unlock(&osb->recovery_lock);
		जाओ restart;
	पूर्ण

	ocfs2_मुक्त_replay_slots(osb);
	osb->recovery_thपढ़ो_task = शून्य;
	mb(); /* sync with ocfs2_recovery_thपढ़ो_running */
	wake_up(&osb->recovery_event);

	mutex_unlock(&osb->recovery_lock);

	अगर (quota_enabled)
		kमुक्त(rm_quota);

	/* no one is callपूर्णांक kthपढ़ो_stop() क्रम us so the kthपढ़ो() api
	 * requires that we call करो_निकास().  And it isn't exported, but
	 * complete_and_निकास() seems to be a minimal wrapper around it. */
	complete_and_निकास(शून्य, status);
पूर्ण

व्योम ocfs2_recovery_thपढ़ो(काष्ठा ocfs2_super *osb, पूर्णांक node_num)
अणु
	mutex_lock(&osb->recovery_lock);

	trace_ocfs2_recovery_thपढ़ो(node_num, osb->node_num,
		osb->disable_recovery, osb->recovery_thपढ़ो_task,
		osb->disable_recovery ?
		-1 : ocfs2_recovery_map_set(osb, node_num));

	अगर (osb->disable_recovery)
		जाओ out;

	अगर (osb->recovery_thपढ़ो_task)
		जाओ out;

	osb->recovery_thपढ़ो_task =  kthपढ़ो_run(__ocfs2_recovery_thपढ़ो, osb,
			"ocfs2rec-%s", osb->uuid_str);
	अगर (IS_ERR(osb->recovery_thपढ़ो_task)) अणु
		mlog_त्रुटि_सं((पूर्णांक)PTR_ERR(osb->recovery_thपढ़ो_task));
		osb->recovery_thपढ़ो_task = शून्य;
	पूर्ण

out:
	mutex_unlock(&osb->recovery_lock);
	wake_up(&osb->recovery_event);
पूर्ण

अटल पूर्णांक ocfs2_पढ़ो_journal_inode(काष्ठा ocfs2_super *osb,
				    पूर्णांक slot_num,
				    काष्ठा buffer_head **bh,
				    काष्ठा inode **ret_inode)
अणु
	पूर्णांक status = -EACCES;
	काष्ठा inode *inode = शून्य;

	BUG_ON(slot_num >= osb->max_slots);

	inode = ocfs2_get_प्रणाली_file_inode(osb, JOURNAL_SYSTEM_INODE,
					    slot_num);
	अगर (!inode || is_bad_inode(inode)) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	SET_INODE_JOURNAL(inode);

	status = ocfs2_पढ़ो_inode_block_full(inode, bh, OCFS2_BH_IGNORE_CACHE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = 0;

bail:
	अगर (inode) अणु
		अगर (status || !ret_inode)
			iput(inode);
		अन्यथा
			*ret_inode = inode;
	पूर्ण
	वापस status;
पूर्ण

/* Does the actual journal replay and marks the journal inode as
 * clean. Will only replay अगर the journal inode is marked dirty. */
अटल पूर्णांक ocfs2_replay_journal(काष्ठा ocfs2_super *osb,
				पूर्णांक node_num,
				पूर्णांक slot_num)
अणु
	पूर्णांक status;
	पूर्णांक got_lock = 0;
	अचिन्हित पूर्णांक flags;
	काष्ठा inode *inode = शून्य;
	काष्ठा ocfs2_dinode *fe;
	journal_t *journal = शून्य;
	काष्ठा buffer_head *bh = शून्य;
	u32 slot_reco_gen;

	status = ocfs2_पढ़ो_journal_inode(osb, slot_num, &bh, &inode);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ करोne;
	पूर्ण

	fe = (काष्ठा ocfs2_dinode *)bh->b_data;
	slot_reco_gen = ocfs2_get_recovery_generation(fe);
	brअन्यथा(bh);
	bh = शून्य;

	/*
	 * As the fs recovery is asynchronous, there is a small chance that
	 * another node mounted (and recovered) the slot beक्रमe the recovery
	 * thपढ़ो could get the lock. To handle that, we dirty पढ़ो the journal
	 * inode क्रम that slot to get the recovery generation. If it is
	 * dअगरferent than what we expected, the slot has been recovered.
	 * If not, it needs recovery.
	 */
	अगर (osb->slot_recovery_generations[slot_num] != slot_reco_gen) अणु
		trace_ocfs2_replay_journal_recovered(slot_num,
		     osb->slot_recovery_generations[slot_num], slot_reco_gen);
		osb->slot_recovery_generations[slot_num] = slot_reco_gen;
		status = -EBUSY;
		जाओ करोne;
	पूर्ण

	/* Continue with recovery as the journal has not yet been recovered */

	status = ocfs2_inode_lock_full(inode, &bh, 1, OCFS2_META_LOCK_RECOVERY);
	अगर (status < 0) अणु
		trace_ocfs2_replay_journal_lock_err(status);
		अगर (status != -ERESTARTSYS)
			mlog(ML_ERROR, "Could not lock journal!\n");
		जाओ करोne;
	पूर्ण
	got_lock = 1;

	fe = (काष्ठा ocfs2_dinode *) bh->b_data;

	flags = le32_to_cpu(fe->id1.journal1.ij_flags);
	slot_reco_gen = ocfs2_get_recovery_generation(fe);

	अगर (!(flags & OCFS2_JOURNAL_सूचीTY_FL)) अणु
		trace_ocfs2_replay_journal_skip(node_num);
		/* Refresh recovery generation क्रम the slot */
		osb->slot_recovery_generations[slot_num] = slot_reco_gen;
		जाओ करोne;
	पूर्ण

	/* we need to run complete recovery क्रम offline orphan slots */
	ocfs2_replay_map_set_state(osb, REPLAY_NEEDED);

	prपूर्णांकk(KERN_NOTICE "ocfs2: Begin replay journal (node %d, slot %d) on "\
	       "device (%u,%u)\n", node_num, slot_num, MAJOR(osb->sb->s_dev),
	       MINOR(osb->sb->s_dev));

	OCFS2_I(inode)->ip_clusters = le32_to_cpu(fe->i_clusters);

	status = ocfs2_क्रमce_पढ़ो_journal(inode);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ करोne;
	पूर्ण

	journal = jbd2_journal_init_inode(inode);
	अगर (journal == शून्य) अणु
		mlog(ML_ERROR, "Linux journal layer error\n");
		status = -EIO;
		जाओ करोne;
	पूर्ण

	status = jbd2_journal_load(journal);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		अगर (!igrab(inode))
			BUG();
		jbd2_journal_destroy(journal);
		जाओ करोne;
	पूर्ण

	ocfs2_clear_journal_error(osb->sb, journal, slot_num);

	/* wipe the journal */
	jbd2_journal_lock_updates(journal);
	status = jbd2_journal_flush(journal);
	jbd2_journal_unlock_updates(journal);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	/* This will mark the node clean */
	flags = le32_to_cpu(fe->id1.journal1.ij_flags);
	flags &= ~OCFS2_JOURNAL_सूचीTY_FL;
	fe->id1.journal1.ij_flags = cpu_to_le32(flags);

	/* Increment recovery generation to indicate successful recovery */
	ocfs2_bump_recovery_generation(fe);
	osb->slot_recovery_generations[slot_num] =
					ocfs2_get_recovery_generation(fe);

	ocfs2_compute_meta_ecc(osb->sb, bh->b_data, &fe->i_check);
	status = ocfs2_ग_लिखो_block(osb, bh, INODE_CACHE(inode));
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	अगर (!igrab(inode))
		BUG();

	jbd2_journal_destroy(journal);

	prपूर्णांकk(KERN_NOTICE "ocfs2: End replay journal (node %d, slot %d) on "\
	       "device (%u,%u)\n", node_num, slot_num, MAJOR(osb->sb->s_dev),
	       MINOR(osb->sb->s_dev));
करोne:
	/* drop the lock on this nodes journal */
	अगर (got_lock)
		ocfs2_inode_unlock(inode, 1);

	iput(inode);
	brअन्यथा(bh);

	वापस status;
पूर्ण

/*
 * Do the most important parts of node recovery:
 *  - Replay it's journal
 *  - Stamp a clean local allocator file
 *  - Stamp a clean truncate log
 *  - Mark the node clean
 *
 * If this function completes without error, a node in OCFS2 can be
 * said to have been safely recovered. As a result, failure during the
 * second part of a nodes recovery process (local alloc recovery) is
 * far less concerning.
 */
अटल पूर्णांक ocfs2_recover_node(काष्ठा ocfs2_super *osb,
			      पूर्णांक node_num, पूर्णांक slot_num)
अणु
	पूर्णांक status = 0;
	काष्ठा ocfs2_dinode *la_copy = शून्य;
	काष्ठा ocfs2_dinode *tl_copy = शून्य;

	trace_ocfs2_recover_node(node_num, slot_num, osb->node_num);

	/* Should not ever be called to recover ourselves -- in that
	 * हाल we should've called ocfs2_journal_load instead. */
	BUG_ON(osb->node_num == node_num);

	status = ocfs2_replay_journal(osb, node_num, slot_num);
	अगर (status < 0) अणु
		अगर (status == -EBUSY) अणु
			trace_ocfs2_recover_node_skip(slot_num, node_num);
			status = 0;
			जाओ करोne;
		पूर्ण
		mlog_त्रुटि_सं(status);
		जाओ करोne;
	पूर्ण

	/* Stamp a clean local alloc file AFTER recovering the journal... */
	status = ocfs2_begin_local_alloc_recovery(osb, slot_num, &la_copy);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ करोne;
	पूर्ण

	/* An error from begin_truncate_log_recovery is not
	 * serious enough to warrant halting the rest of
	 * recovery. */
	status = ocfs2_begin_truncate_log_recovery(osb, slot_num, &tl_copy);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	/* Likewise, this would be a strange but ultimately not so
	 * harmful place to get an error... */
	status = ocfs2_clear_slot(osb, slot_num);
	अगर (status < 0)
		mlog_त्रुटि_सं(status);

	/* This will kमुक्त the memory poपूर्णांकed to by la_copy and tl_copy */
	ocfs2_queue_recovery_completion(osb->journal, slot_num, la_copy,
					tl_copy, शून्य, ORPHAN_NEED_TRUNCATE);

	status = 0;
करोne:

	वापस status;
पूर्ण

/* Test node liveness by trylocking his journal. If we get the lock,
 * we drop it here. Return 0 अगर we got the lock, -EAGAIN अगर node is
 * still alive (we couldn't get the lock) and < 0 on error. */
अटल पूर्णांक ocfs2_trylock_journal(काष्ठा ocfs2_super *osb,
				 पूर्णांक slot_num)
अणु
	पूर्णांक status, flags;
	काष्ठा inode *inode = शून्य;

	inode = ocfs2_get_प्रणाली_file_inode(osb, JOURNAL_SYSTEM_INODE,
					    slot_num);
	अगर (inode == शून्य) अणु
		mlog(ML_ERROR, "access error\n");
		status = -EACCES;
		जाओ bail;
	पूर्ण
	अगर (is_bad_inode(inode)) अणु
		mlog(ML_ERROR, "access error (bad inode)\n");
		iput(inode);
		inode = शून्य;
		status = -EACCES;
		जाओ bail;
	पूर्ण
	SET_INODE_JOURNAL(inode);

	flags = OCFS2_META_LOCK_RECOVERY | OCFS2_META_LOCK_NOQUEUE;
	status = ocfs2_inode_lock_full(inode, शून्य, 1, flags);
	अगर (status < 0) अणु
		अगर (status != -EAGAIN)
			mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ocfs2_inode_unlock(inode, 1);
bail:
	iput(inode);

	वापस status;
पूर्ण

/* Call this underneath ocfs2_super_lock. It also assumes that the
 * slot info काष्ठा has been updated from disk. */
पूर्णांक ocfs2_mark_dead_nodes(काष्ठा ocfs2_super *osb)
अणु
	अचिन्हित पूर्णांक node_num;
	पूर्णांक status, i;
	u32 gen;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा ocfs2_dinode *di;

	/* This is called with the super block cluster lock, so we
	 * know that the slot map can't change underneath us. */

	क्रम (i = 0; i < osb->max_slots; i++) अणु
		/* Read journal inode to get the recovery generation */
		status = ocfs2_पढ़ो_journal_inode(osb, i, &bh, शून्य);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		di = (काष्ठा ocfs2_dinode *)bh->b_data;
		gen = ocfs2_get_recovery_generation(di);
		brअन्यथा(bh);
		bh = शून्य;

		spin_lock(&osb->osb_lock);
		osb->slot_recovery_generations[i] = gen;

		trace_ocfs2_mark_dead_nodes(i,
					    osb->slot_recovery_generations[i]);

		अगर (i == osb->slot_num) अणु
			spin_unlock(&osb->osb_lock);
			जारी;
		पूर्ण

		status = ocfs2_slot_to_node_num_locked(osb, i, &node_num);
		अगर (status == -ENOENT) अणु
			spin_unlock(&osb->osb_lock);
			जारी;
		पूर्ण

		अगर (__ocfs2_recovery_map_test(osb, node_num)) अणु
			spin_unlock(&osb->osb_lock);
			जारी;
		पूर्ण
		spin_unlock(&osb->osb_lock);

		/* Ok, we have a slot occupied by another node which
		 * is not in the recovery map. We trylock his journal
		 * file here to test अगर he's alive. */
		status = ocfs2_trylock_journal(osb, i);
		अगर (!status) अणु
			/* Since we're called from mount, we know that
			 * the recovery thपढ़ो can't race us on
			 * setting / checking the recovery bits. */
			ocfs2_recovery_thपढ़ो(osb, node_num);
		पूर्ण अन्यथा अगर ((status < 0) && (status != -EAGAIN)) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	status = 0;
bail:
	वापस status;
पूर्ण

/*
 * Scan समयr should get fired every ORPHAN_SCAN_SCHEDULE_TIMEOUT. Add some
 * अक्रमomness to the समयout to minimize multple nodes firing the समयr at the
 * same समय.
 */
अटल अंतरभूत अचिन्हित दीर्घ ocfs2_orphan_scan_समयout(व्योम)
अणु
	अचिन्हित दीर्घ समय;

	get_अक्रमom_bytes(&समय, माप(समय));
	समय = ORPHAN_SCAN_SCHEDULE_TIMEOUT + (समय % 5000);
	वापस msecs_to_jअगरfies(समय);
पूर्ण

/*
 * ocfs2_queue_orphan_scan calls ocfs2_queue_recovery_completion क्रम
 * every slot, queuing a recovery of the slot on the ocfs2_wq thपढ़ो. This
 * is करोne to catch any orphans that are left over in orphan directories.
 *
 * It scans all slots, even ones that are in use. It करोes so to handle the
 * हाल described below:
 *
 *   Node 1 has an inode it was using. The dentry went away due to memory
 *   pressure.  Node 1 बंदs the inode, but it's on the मुक्त list. The node
 *   has the खोलो lock.
 *   Node 2 unlinks the inode. It grअसल the dentry lock to notअगरy others,
 *   but node 1 has no dentry and करोesn't get the message. It trylocks the
 *   खोलो lock, sees that another node has a PR, and करोes nothing.
 *   Later node 2 runs its orphan dir. It iमाला_लो the inode, trylocks the
 *   खोलो lock, sees the PR still, and करोes nothing.
 *   Basically, we have to trigger an orphan iput on node 1. The only way
 *   क्रम this to happen is अगर node 1 runs node 2's orphan dir.
 *
 * ocfs2_queue_orphan_scan माला_लो called every ORPHAN_SCAN_SCHEDULE_TIMEOUT
 * seconds.  It माला_लो an EX lock on os_lockres and checks sequence number
 * stored in LVB. If the sequence number has changed, it means some other
 * node has करोne the scan.  This node skips the scan and tracks the
 * sequence number.  If the sequence number didn't change, it means a scan
 * hasn't happened.  The node queues a scan and increments the
 * sequence number in the LVB.
 */
अटल व्योम ocfs2_queue_orphan_scan(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_orphan_scan *os;
	पूर्णांक status, i;
	u32 seqno = 0;

	os = &osb->osb_orphan_scan;

	अगर (atomic_पढ़ो(&os->os_state) == ORPHAN_SCAN_INACTIVE)
		जाओ out;

	trace_ocfs2_queue_orphan_scan_begin(os->os_count, os->os_seqno,
					    atomic_पढ़ो(&os->os_state));

	status = ocfs2_orphan_scan_lock(osb, &seqno);
	अगर (status < 0) अणु
		अगर (status != -EAGAIN)
			mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	/* Do no queue the tasks अगर the volume is being umounted */
	अगर (atomic_पढ़ो(&os->os_state) == ORPHAN_SCAN_INACTIVE)
		जाओ unlock;

	अगर (os->os_seqno != seqno) अणु
		os->os_seqno = seqno;
		जाओ unlock;
	पूर्ण

	क्रम (i = 0; i < osb->max_slots; i++)
		ocfs2_queue_recovery_completion(osb->journal, i, शून्य, शून्य,
						शून्य, ORPHAN_NO_NEED_TRUNCATE);
	/*
	 * We queued a recovery on orphan slots, increment the sequence
	 * number and update LVB so other node will skip the scan क्रम a जबतक
	 */
	seqno++;
	os->os_count++;
	os->os_scanसमय = kसमय_get_seconds();
unlock:
	ocfs2_orphan_scan_unlock(osb, seqno);
out:
	trace_ocfs2_queue_orphan_scan_end(os->os_count, os->os_seqno,
					  atomic_पढ़ो(&os->os_state));
	वापस;
पूर्ण

/* Worker task that माला_लो fired every ORPHAN_SCAN_SCHEDULE_TIMEOUT millsec */
अटल व्योम ocfs2_orphan_scan_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ocfs2_orphan_scan *os;
	काष्ठा ocfs2_super *osb;

	os = container_of(work, काष्ठा ocfs2_orphan_scan,
			  os_orphan_scan_work.work);
	osb = os->os_osb;

	mutex_lock(&os->os_lock);
	ocfs2_queue_orphan_scan(osb);
	अगर (atomic_पढ़ो(&os->os_state) == ORPHAN_SCAN_ACTIVE)
		queue_delayed_work(osb->ocfs2_wq, &os->os_orphan_scan_work,
				      ocfs2_orphan_scan_समयout());
	mutex_unlock(&os->os_lock);
पूर्ण

व्योम ocfs2_orphan_scan_stop(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_orphan_scan *os;

	os = &osb->osb_orphan_scan;
	अगर (atomic_पढ़ो(&os->os_state) == ORPHAN_SCAN_ACTIVE) अणु
		atomic_set(&os->os_state, ORPHAN_SCAN_INACTIVE);
		mutex_lock(&os->os_lock);
		cancel_delayed_work(&os->os_orphan_scan_work);
		mutex_unlock(&os->os_lock);
	पूर्ण
पूर्ण

व्योम ocfs2_orphan_scan_init(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_orphan_scan *os;

	os = &osb->osb_orphan_scan;
	os->os_osb = osb;
	os->os_count = 0;
	os->os_seqno = 0;
	mutex_init(&os->os_lock);
	INIT_DELAYED_WORK(&os->os_orphan_scan_work, ocfs2_orphan_scan_work);
पूर्ण

व्योम ocfs2_orphan_scan_start(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा ocfs2_orphan_scan *os;

	os = &osb->osb_orphan_scan;
	os->os_scanसमय = kसमय_get_seconds();
	अगर (ocfs2_is_hard_पढ़ोonly(osb) || ocfs2_mount_local(osb))
		atomic_set(&os->os_state, ORPHAN_SCAN_INACTIVE);
	अन्यथा अणु
		atomic_set(&os->os_state, ORPHAN_SCAN_ACTIVE);
		queue_delayed_work(osb->ocfs2_wq, &os->os_orphan_scan_work,
				   ocfs2_orphan_scan_समयout());
	पूर्ण
पूर्ण

काष्ठा ocfs2_orphan_filldir_priv अणु
	काष्ठा dir_context	ctx;
	काष्ठा inode		*head;
	काष्ठा ocfs2_super	*osb;
	क्रमागत ocfs2_orphan_reco_type orphan_reco_type;
पूर्ण;

अटल पूर्णांक ocfs2_orphan_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
				पूर्णांक name_len, loff_t pos, u64 ino,
				अचिन्हित type)
अणु
	काष्ठा ocfs2_orphan_filldir_priv *p =
		container_of(ctx, काष्ठा ocfs2_orphan_filldir_priv, ctx);
	काष्ठा inode *iter;

	अगर (name_len == 1 && !म_भेदन(".", name, 1))
		वापस 0;
	अगर (name_len == 2 && !म_भेदन("..", name, 2))
		वापस 0;

	/* करो not include dio entry in हाल of orphan scan */
	अगर ((p->orphan_reco_type == ORPHAN_NO_NEED_TRUNCATE) &&
			(!म_भेदन(name, OCFS2_DIO_ORPHAN_PREFIX,
			OCFS2_DIO_ORPHAN_PREFIX_LEN)))
		वापस 0;

	/* Skip bad inodes so that recovery can जारी */
	iter = ocfs2_iget(p->osb, ino,
			  OCFS2_FI_FLAG_ORPHAN_RECOVERY, 0);
	अगर (IS_ERR(iter))
		वापस 0;

	अगर (!म_भेदन(name, OCFS2_DIO_ORPHAN_PREFIX,
			OCFS2_DIO_ORPHAN_PREFIX_LEN))
		OCFS2_I(iter)->ip_flags |= OCFS2_INODE_DIO_ORPHAN_ENTRY;

	/* Skip inodes which are alपढ़ोy added to recover list, since dio may
	 * happen concurrently with unlink/नाम */
	अगर (OCFS2_I(iter)->ip_next_orphan) अणु
		iput(iter);
		वापस 0;
	पूर्ण

	trace_ocfs2_orphan_filldir((अचिन्हित दीर्घ दीर्घ)OCFS2_I(iter)->ip_blkno);
	/* No locking is required क्रम the next_orphan queue as there
	 * is only ever a single process करोing orphan recovery. */
	OCFS2_I(iter)->ip_next_orphan = p->head;
	p->head = iter;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_queue_orphans(काष्ठा ocfs2_super *osb,
			       पूर्णांक slot,
			       काष्ठा inode **head,
			       क्रमागत ocfs2_orphan_reco_type orphan_reco_type)
अणु
	पूर्णांक status;
	काष्ठा inode *orphan_dir_inode = शून्य;
	काष्ठा ocfs2_orphan_filldir_priv priv = अणु
		.ctx.actor = ocfs2_orphan_filldir,
		.osb = osb,
		.head = *head,
		.orphan_reco_type = orphan_reco_type
	पूर्ण;

	orphan_dir_inode = ocfs2_get_प्रणाली_file_inode(osb,
						       ORPHAN_सूची_SYSTEM_INODE,
						       slot);
	अगर  (!orphan_dir_inode) अणु
		status = -ENOENT;
		mlog_त्रुटि_सं(status);
		वापस status;
	पूर्ण

	inode_lock(orphan_dir_inode);
	status = ocfs2_inode_lock(orphan_dir_inode, शून्य, 0);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ out;
	पूर्ण

	status = ocfs2_dir_क्रमeach(orphan_dir_inode, &priv.ctx);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_cluster;
	पूर्ण

	*head = priv.head;

out_cluster:
	ocfs2_inode_unlock(orphan_dir_inode, 0);
out:
	inode_unlock(orphan_dir_inode);
	iput(orphan_dir_inode);
	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_orphan_recovery_can_जारी(काष्ठा ocfs2_super *osb,
					      पूर्णांक slot)
अणु
	पूर्णांक ret;

	spin_lock(&osb->osb_lock);
	ret = !osb->osb_orphan_wipes[slot];
	spin_unlock(&osb->osb_lock);
	वापस ret;
पूर्ण

अटल व्योम ocfs2_mark_recovering_orphan_dir(काष्ठा ocfs2_super *osb,
					     पूर्णांक slot)
अणु
	spin_lock(&osb->osb_lock);
	/* Mark ourselves such that new processes in delete_inode()
	 * know to quit early. */
	ocfs2_node_map_set_bit(osb, &osb->osb_recovering_orphan_dirs, slot);
	जबतक (osb->osb_orphan_wipes[slot]) अणु
		/* If any processes are alपढ़ोy in the middle of an
		 * orphan wipe on this dir, then we need to रुको क्रम
		 * them. */
		spin_unlock(&osb->osb_lock);
		रुको_event_पूर्णांकerruptible(osb->osb_wipe_event,
					 ocfs2_orphan_recovery_can_जारी(osb, slot));
		spin_lock(&osb->osb_lock);
	पूर्ण
	spin_unlock(&osb->osb_lock);
पूर्ण

अटल व्योम ocfs2_clear_recovering_orphan_dir(काष्ठा ocfs2_super *osb,
					      पूर्णांक slot)
अणु
	ocfs2_node_map_clear_bit(osb, &osb->osb_recovering_orphan_dirs, slot);
पूर्ण

/*
 * Orphan recovery. Each mounted node has it's own orphan dir which we
 * must run during recovery. Our strategy here is to build a list of
 * the inodes in the orphan dir and iget/iput them. The VFS करोes
 * (most) of the rest of the work.
 *
 * Orphan recovery can happen at any समय, not just mount so we have a
 * couple of extra considerations.
 *
 * - We grab as many inodes as we can under the orphan dir lock -
 *   करोing iget() outside the orphan dir risks getting a reference on
 *   an invalid inode.
 * - We must be sure not to deadlock with other processes on the
 *   प्रणाली wanting to run delete_inode(). This can happen when they go
 *   to lock the orphan dir and the orphan recovery process attempts to
 *   iget() inside the orphan dir lock. This can be aव्योमed by
 *   advertising our state to ocfs2_delete_inode().
 */
अटल पूर्णांक ocfs2_recover_orphans(काष्ठा ocfs2_super *osb,
				 पूर्णांक slot,
				 क्रमागत ocfs2_orphan_reco_type orphan_reco_type)
अणु
	पूर्णांक ret = 0;
	काष्ठा inode *inode = शून्य;
	काष्ठा inode *iter;
	काष्ठा ocfs2_inode_info *oi;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di = शून्य;

	trace_ocfs2_recover_orphans(slot);

	ocfs2_mark_recovering_orphan_dir(osb, slot);
	ret = ocfs2_queue_orphans(osb, slot, &inode, orphan_reco_type);
	ocfs2_clear_recovering_orphan_dir(osb, slot);

	/* Error here should be noted, but we want to जारी with as
	 * many queued inodes as we've got. */
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	जबतक (inode) अणु
		oi = OCFS2_I(inode);
		trace_ocfs2_recover_orphans_iput(
					(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);

		iter = oi->ip_next_orphan;
		oi->ip_next_orphan = शून्य;

		अगर (oi->ip_flags & OCFS2_INODE_DIO_ORPHAN_ENTRY) अणु
			inode_lock(inode);
			ret = ocfs2_rw_lock(inode, 1);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				जाओ unlock_mutex;
			पूर्ण
			/*
			 * We need to take and drop the inode lock to
			 * क्रमce पढ़ो inode from disk.
			 */
			ret = ocfs2_inode_lock(inode, &di_bh, 1);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ unlock_rw;
			पूर्ण

			di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

			अगर (di->i_flags & cpu_to_le32(OCFS2_DIO_ORPHANED_FL)) अणु
				ret = ocfs2_truncate_file(inode, di_bh,
						i_size_पढ़ो(inode));
				अगर (ret < 0) अणु
					अगर (ret != -ENOSPC)
						mlog_त्रुटि_सं(ret);
					जाओ unlock_inode;
				पूर्ण

				ret = ocfs2_del_inode_from_orphan(osb, inode,
						di_bh, 0, 0);
				अगर (ret)
					mlog_त्रुटि_सं(ret);
			पूर्ण
unlock_inode:
			ocfs2_inode_unlock(inode, 1);
			brअन्यथा(di_bh);
			di_bh = शून्य;
unlock_rw:
			ocfs2_rw_unlock(inode, 1);
unlock_mutex:
			inode_unlock(inode);

			/* clear dio flag in ocfs2_inode_info */
			oi->ip_flags &= ~OCFS2_INODE_DIO_ORPHAN_ENTRY;
		पूर्ण अन्यथा अणु
			spin_lock(&oi->ip_lock);
			/* Set the proper inक्रमmation to get us going पूर्णांकo
			 * ocfs2_delete_inode. */
			oi->ip_flags |= OCFS2_INODE_MAYBE_ORPHANED;
			spin_unlock(&oi->ip_lock);
		पूर्ण

		iput(inode);
		inode = iter;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_रुको_on_mount(काष्ठा ocfs2_super *osb, पूर्णांक quota)
अणु
	/* This check is good because ocfs2 will रुको on our recovery
	 * thपढ़ो beक्रमe changing it to something other than MOUNTED
	 * or DISABLED. */
	रुको_event(osb->osb_mount_event,
		  (!quota && atomic_पढ़ो(&osb->vol_state) == VOLUME_MOUNTED) ||
		   atomic_पढ़ो(&osb->vol_state) == VOLUME_MOUNTED_QUOTAS ||
		   atomic_पढ़ो(&osb->vol_state) == VOLUME_DISABLED);

	/* If there's an error on mount, then we may never get to the
	 * MOUNTED flag, but this is set right beक्रमe
	 * dismount_volume() so we can trust it. */
	अगर (atomic_पढ़ो(&osb->vol_state) == VOLUME_DISABLED) अणु
		trace_ocfs2_रुको_on_mount(VOLUME_DISABLED);
		mlog(0, "mount error, exiting!\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_commit_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक status;
	काष्ठा ocfs2_super *osb = arg;
	काष्ठा ocfs2_journal *journal = osb->journal;

	/* we can trust j_num_trans here because _should_stop() is only set in
	 * shutकरोwn and nobody other than ourselves should be able to start
	 * transactions.  committing on shutकरोwn might take a few iterations
	 * as final transactions put deleted inodes on the list */
	जबतक (!(kthपढ़ो_should_stop() &&
		 atomic_पढ़ो(&journal->j_num_trans) == 0)) अणु

		रुको_event_पूर्णांकerruptible(osb->checkpoपूर्णांक_event,
					 atomic_पढ़ो(&journal->j_num_trans)
					 || kthपढ़ो_should_stop());

		status = ocfs2_commit_cache(osb);
		अगर (status < 0) अणु
			अटल अचिन्हित दीर्घ पात_warn_समय;

			/* Warn about this once per minute */
			अगर (prपूर्णांकk_समयd_ratelimit(&पात_warn_समय, 60*HZ))
				mlog(ML_ERROR, "status = %d, journal is "
						"already aborted.\n", status);
			/*
			 * After ocfs2_commit_cache() fails, j_num_trans has a
			 * non-zero value.  Sleep here to aव्योम a busy-रुको
			 * loop.
			 */
			msleep_पूर्णांकerruptible(1000);
		पूर्ण

		अगर (kthपढ़ो_should_stop() && atomic_पढ़ो(&journal->j_num_trans))अणु
			mlog(ML_KTHREAD,
			     "commit_thread: %u transactions pending on "
			     "shutdown\n",
			     atomic_पढ़ो(&journal->j_num_trans));
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Reads all the journal inodes without taking any cluster locks. Used
 * क्रम hard पढ़ोonly access to determine whether any journal requires
 * recovery. Also used to refresh the recovery generation numbers after
 * a journal has been recovered by another node.
 */
पूर्णांक ocfs2_check_journals_nolocks(काष्ठा ocfs2_super *osb)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक slot;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	पूर्णांक journal_dirty = 0;

	क्रम(slot = 0; slot < osb->max_slots; slot++) अणु
		ret = ocfs2_पढ़ो_journal_inode(osb, slot, &di_bh, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		di = (काष्ठा ocfs2_dinode *) di_bh->b_data;

		osb->slot_recovery_generations[slot] =
					ocfs2_get_recovery_generation(di);

		अगर (le32_to_cpu(di->id1.journal1.ij_flags) &
		    OCFS2_JOURNAL_सूचीTY_FL)
			journal_dirty = 1;

		brअन्यथा(di_bh);
		di_bh = शून्य;
	पूर्ण

out:
	अगर (journal_dirty)
		ret = -EROFS;
	वापस ret;
पूर्ण
