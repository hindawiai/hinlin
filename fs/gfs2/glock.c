<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2008 Red Hat, Inc.  All rights reserved.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/delay.h>
#समावेश <linux/sort.h>
#समावेश <linux/hash.h>
#समावेश <linux/jhash.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rculist_bl.h>
#समावेश <linux/bit_spinlock.h>
#समावेश <linux/percpu.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/lockref.h>
#समावेश <linux/rhashtable.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "inode.h"
#समावेश "lops.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "super.h"
#समावेश "util.h"
#समावेश "bmap.h"
#घोषणा CREATE_TRACE_POINTS
#समावेश "trace_gfs2.h"

काष्ठा gfs2_glock_iter अणु
	काष्ठा gfs2_sbd *sdp;		/* incore superblock           */
	काष्ठा rhashtable_iter hti;	/* rhashtable iterator         */
	काष्ठा gfs2_glock *gl;		/* current glock काष्ठा        */
	loff_t last_pos;		/* last position               */
पूर्ण;

प्रकार व्योम (*glock_examiner) (काष्ठा gfs2_glock * gl);

अटल व्योम करो_xmote(काष्ठा gfs2_glock *gl, काष्ठा gfs2_holder *gh, अचिन्हित पूर्णांक target);

अटल काष्ठा dentry *gfs2_root;
अटल काष्ठा workqueue_काष्ठा *glock_workqueue;
काष्ठा workqueue_काष्ठा *gfs2_delete_workqueue;
अटल LIST_HEAD(lru_list);
अटल atomic_t lru_count = ATOMIC_INIT(0);
अटल DEFINE_SPINLOCK(lru_lock);

#घोषणा GFS2_GL_HASH_SHIFT      15
#घोषणा GFS2_GL_HASH_SIZE       BIT(GFS2_GL_HASH_SHIFT)

अटल स्थिर काष्ठा rhashtable_params ht_parms = अणु
	.nelem_hपूर्णांक = GFS2_GL_HASH_SIZE * 3 / 4,
	.key_len = दुरत्वend(काष्ठा lm_lockname, ln_type),
	.key_offset = दुरत्व(काष्ठा gfs2_glock, gl_name),
	.head_offset = दुरत्व(काष्ठा gfs2_glock, gl_node),
पूर्ण;

अटल काष्ठा rhashtable gl_hash_table;

#घोषणा GLOCK_WAIT_TABLE_BITS 12
#घोषणा GLOCK_WAIT_TABLE_SIZE (1 << GLOCK_WAIT_TABLE_BITS)
अटल रुको_queue_head_t glock_रुको_table[GLOCK_WAIT_TABLE_SIZE] __cacheline_aligned;

काष्ठा रुको_glock_queue अणु
	काष्ठा lm_lockname *name;
	रुको_queue_entry_t रुको;
पूर्ण;

अटल पूर्णांक glock_wake_function(रुको_queue_entry_t *रुको, अचिन्हित पूर्णांक mode,
			       पूर्णांक sync, व्योम *key)
अणु
	काष्ठा रुको_glock_queue *रुको_glock =
		container_of(रुको, काष्ठा रुको_glock_queue, रुको);
	काष्ठा lm_lockname *रुको_name = रुको_glock->name;
	काष्ठा lm_lockname *wake_name = key;

	अगर (wake_name->ln_sbd != रुको_name->ln_sbd ||
	    wake_name->ln_number != रुको_name->ln_number ||
	    wake_name->ln_type != रुको_name->ln_type)
		वापस 0;
	वापस स्वतःहटाओ_wake_function(रुको, mode, sync, key);
पूर्ण

अटल रुको_queue_head_t *glock_रुकोqueue(काष्ठा lm_lockname *name)
अणु
	u32 hash = jhash2((u32 *)name, ht_parms.key_len / 4, 0);

	वापस glock_रुको_table + hash_32(hash, GLOCK_WAIT_TABLE_BITS);
पूर्ण

/**
 * wake_up_glock  -  Wake up रुकोers on a glock
 * @gl: the glock
 */
अटल व्योम wake_up_glock(काष्ठा gfs2_glock *gl)
अणु
	रुको_queue_head_t *wq = glock_रुकोqueue(&gl->gl_name);

	अगर (रुकोqueue_active(wq))
		__wake_up(wq, TASK_NORMAL, 1, &gl->gl_name);
पूर्ण

अटल व्योम gfs2_glock_dealloc(काष्ठा rcu_head *rcu)
अणु
	काष्ठा gfs2_glock *gl = container_of(rcu, काष्ठा gfs2_glock, gl_rcu);

	kमुक्त(gl->gl_lksb.sb_lvbptr);
	अगर (gl->gl_ops->go_flags & GLOF_ASPACE)
		kmem_cache_मुक्त(gfs2_glock_aspace_cachep, gl);
	अन्यथा
		kmem_cache_मुक्त(gfs2_glock_cachep, gl);
पूर्ण

/**
 * glock_blocked_by_withdraw - determine अगर we can still use a glock
 * @gl: the glock
 *
 * We need to allow some glocks to be enqueued, dequeued, promoted, and demoted
 * when we're withdrawn. For example, to मुख्यtain metadata पूर्णांकegrity, we should
 * disallow the use of inode and rgrp glocks when withdrawn. Other glocks, like
 * iखोलो or the transaction glocks may be safely used because none of their
 * metadata goes through the journal. So in general, we should disallow all
 * glocks that are journaled, and allow all the others. One exception is:
 * we need to allow our active journal to be promoted and demoted so others
 * may recover it and we can reacquire it when they're करोne.
 */
अटल bool glock_blocked_by_withdraw(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;

	अगर (likely(!gfs2_withdrawn(sdp)))
		वापस false;
	अगर (gl->gl_ops->go_flags & GLOF_NONDISK)
		वापस false;
	अगर (!sdp->sd_jdesc ||
	    gl->gl_name.ln_number == sdp->sd_jdesc->jd_no_addr)
		वापस false;
	वापस true;
पूर्ण

व्योम gfs2_glock_मुक्त(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;

	gfs2_glock_निश्चित_withdraw(gl, atomic_पढ़ो(&gl->gl_revokes) == 0);
	rhashtable_हटाओ_fast(&gl_hash_table, &gl->gl_node, ht_parms);
	smp_mb();
	wake_up_glock(gl);
	call_rcu(&gl->gl_rcu, gfs2_glock_dealloc);
	अगर (atomic_dec_and_test(&sdp->sd_glock_disposal))
		wake_up(&sdp->sd_glock_रुको);
पूर्ण

/**
 * gfs2_glock_hold() - increment reference count on glock
 * @gl: The glock to hold
 *
 */

व्योम gfs2_glock_hold(काष्ठा gfs2_glock *gl)
अणु
	GLOCK_BUG_ON(gl, __lockref_is_dead(&gl->gl_lockref));
	lockref_get(&gl->gl_lockref);
पूर्ण

/**
 * demote_ok - Check to see अगर it's ok to unlock a glock
 * @gl: the glock
 *
 * Returns: 1 अगर it's ok
 */

अटल पूर्णांक demote_ok(स्थिर काष्ठा gfs2_glock *gl)
अणु
	स्थिर काष्ठा gfs2_glock_operations *glops = gl->gl_ops;

	अगर (gl->gl_state == LM_ST_UNLOCKED)
		वापस 0;
	अगर (!list_empty(&gl->gl_holders))
		वापस 0;
	अगर (glops->go_demote_ok)
		वापस glops->go_demote_ok(gl);
	वापस 1;
पूर्ण


व्योम gfs2_glock_add_to_lru(काष्ठा gfs2_glock *gl)
अणु
	अगर (!(gl->gl_ops->go_flags & GLOF_LRU))
		वापस;

	spin_lock(&lru_lock);

	list_del(&gl->gl_lru);
	list_add_tail(&gl->gl_lru, &lru_list);

	अगर (!test_bit(GLF_LRU, &gl->gl_flags)) अणु
		set_bit(GLF_LRU, &gl->gl_flags);
		atomic_inc(&lru_count);
	पूर्ण

	spin_unlock(&lru_lock);
पूर्ण

अटल व्योम gfs2_glock_हटाओ_from_lru(काष्ठा gfs2_glock *gl)
अणु
	अगर (!(gl->gl_ops->go_flags & GLOF_LRU))
		वापस;

	spin_lock(&lru_lock);
	अगर (test_bit(GLF_LRU, &gl->gl_flags)) अणु
		list_del_init(&gl->gl_lru);
		atomic_dec(&lru_count);
		clear_bit(GLF_LRU, &gl->gl_flags);
	पूर्ण
	spin_unlock(&lru_lock);
पूर्ण

/*
 * Enqueue the glock on the work queue.  Passes one glock reference on to the
 * work queue.
 */
अटल व्योम __gfs2_glock_queue_work(काष्ठा gfs2_glock *gl, अचिन्हित दीर्घ delay) अणु
	अगर (!queue_delayed_work(glock_workqueue, &gl->gl_work, delay)) अणु
		/*
		 * We are holding the lockref spinlock, and the work was still
		 * queued above.  The queued work (glock_work_func) takes that
		 * spinlock beक्रमe dropping its glock reference(s), so it
		 * cannot have dropped them in the meanसमय.
		 */
		GLOCK_BUG_ON(gl, gl->gl_lockref.count < 2);
		gl->gl_lockref.count--;
	पूर्ण
पूर्ण

अटल व्योम gfs2_glock_queue_work(काष्ठा gfs2_glock *gl, अचिन्हित दीर्घ delay) अणु
	spin_lock(&gl->gl_lockref.lock);
	__gfs2_glock_queue_work(gl, delay);
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

अटल व्योम __gfs2_glock_put(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा address_space *mapping = gfs2_glock2aspace(gl);

	lockref_mark_dead(&gl->gl_lockref);

	gfs2_glock_हटाओ_from_lru(gl);
	spin_unlock(&gl->gl_lockref.lock);
	GLOCK_BUG_ON(gl, !list_empty(&gl->gl_holders));
	अगर (mapping) अणु
		truncate_inode_pages_final(mapping);
		अगर (!gfs2_withdrawn(sdp))
			GLOCK_BUG_ON(gl, !mapping_empty(mapping));
	पूर्ण
	trace_gfs2_glock_put(gl);
	sdp->sd_lockकाष्ठा.ls_ops->lm_put_lock(gl);
पूर्ण

/*
 * Cause the glock to be put in work queue context.
 */
व्योम gfs2_glock_queue_put(काष्ठा gfs2_glock *gl)
अणु
	gfs2_glock_queue_work(gl, 0);
पूर्ण

/**
 * gfs2_glock_put() - Decrement reference count on glock
 * @gl: The glock to put
 *
 */

व्योम gfs2_glock_put(काष्ठा gfs2_glock *gl)
अणु
	अगर (lockref_put_or_lock(&gl->gl_lockref))
		वापस;

	__gfs2_glock_put(gl);
पूर्ण

/**
 * may_grant - check अगर its ok to grant a new lock
 * @gl: The glock
 * @gh: The lock request which we wish to grant
 *
 * Returns: true अगर its ok to grant the lock
 */

अटल अंतरभूत पूर्णांक may_grant(स्थिर काष्ठा gfs2_glock *gl, स्थिर काष्ठा gfs2_holder *gh)
अणु
	स्थिर काष्ठा gfs2_holder *gh_head = list_first_entry(&gl->gl_holders, स्थिर काष्ठा gfs2_holder, gh_list);

	अगर (gh != gh_head) अणु
		/**
		 * Here we make a special exception to grant holders who agree
		 * to share the EX lock with other holders who also have the
		 * bit set. If the original holder has the LM_FLAG_NODE_SCOPE bit
		 * is set, we grant more holders with the bit set.
		 */
		अगर (gh_head->gh_state == LM_ST_EXCLUSIVE &&
		    (gh_head->gh_flags & LM_FLAG_NODE_SCOPE) &&
		    gh->gh_state == LM_ST_EXCLUSIVE &&
		    (gh->gh_flags & LM_FLAG_NODE_SCOPE))
			वापस 1;
		अगर ((gh->gh_state == LM_ST_EXCLUSIVE ||
		     gh_head->gh_state == LM_ST_EXCLUSIVE))
			वापस 0;
	पूर्ण
	अगर (gl->gl_state == gh->gh_state)
		वापस 1;
	अगर (gh->gh_flags & GL_EXACT)
		वापस 0;
	अगर (gl->gl_state == LM_ST_EXCLUSIVE) अणु
		अगर (gh->gh_state == LM_ST_SHARED && gh_head->gh_state == LM_ST_SHARED)
			वापस 1;
		अगर (gh->gh_state == LM_ST_DEFERRED && gh_head->gh_state == LM_ST_DEFERRED)
			वापस 1;
	पूर्ण
	अगर (gl->gl_state != LM_ST_UNLOCKED && (gh->gh_flags & LM_FLAG_ANY))
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम gfs2_holder_wake(काष्ठा gfs2_holder *gh)
अणु
	clear_bit(HIF_WAIT, &gh->gh_अगरlags);
	smp_mb__after_atomic();
	wake_up_bit(&gh->gh_अगरlags, HIF_WAIT);
	अगर (gh->gh_flags & GL_ASYNC) अणु
		काष्ठा gfs2_sbd *sdp = gh->gh_gl->gl_name.ln_sbd;

		wake_up(&sdp->sd_async_glock_रुको);
	पूर्ण
पूर्ण

/**
 * करो_error - Something unexpected has happened during a lock request
 * @gl: The glock
 * @ret: The status from the DLM
 */

अटल व्योम करो_error(काष्ठा gfs2_glock *gl, स्थिर पूर्णांक ret)
अणु
	काष्ठा gfs2_holder *gh, *पंचांगp;

	list_क्रम_each_entry_safe(gh, पंचांगp, &gl->gl_holders, gh_list) अणु
		अगर (test_bit(HIF_HOLDER, &gh->gh_अगरlags))
			जारी;
		अगर (ret & LM_OUT_ERROR)
			gh->gh_error = -EIO;
		अन्यथा अगर (gh->gh_flags & (LM_FLAG_TRY | LM_FLAG_TRY_1CB))
			gh->gh_error = GLR_TRYFAILED;
		अन्यथा
			जारी;
		list_del_init(&gh->gh_list);
		trace_gfs2_glock_queue(gh, 0);
		gfs2_holder_wake(gh);
	पूर्ण
पूर्ण

/**
 * करो_promote - promote as many requests as possible on the current queue
 * @gl: The glock
 * 
 * Returns: 1 अगर there is a blocked holder at the head of the list, or 2
 *          अगर a type specअगरic operation is underway.
 */

अटल पूर्णांक करो_promote(काष्ठा gfs2_glock *gl)
__releases(&gl->gl_lockref.lock)
__acquires(&gl->gl_lockref.lock)
अणु
	स्थिर काष्ठा gfs2_glock_operations *glops = gl->gl_ops;
	काष्ठा gfs2_holder *gh, *पंचांगp;
	पूर्णांक ret;

restart:
	list_क्रम_each_entry_safe(gh, पंचांगp, &gl->gl_holders, gh_list) अणु
		अगर (test_bit(HIF_HOLDER, &gh->gh_अगरlags))
			जारी;
		अगर (may_grant(gl, gh)) अणु
			अगर (gh->gh_list.prev == &gl->gl_holders &&
			    glops->go_lock) अणु
				spin_unlock(&gl->gl_lockref.lock);
				/* FIXME: eliminate this eventually */
				ret = glops->go_lock(gh);
				spin_lock(&gl->gl_lockref.lock);
				अगर (ret) अणु
					अगर (ret == 1)
						वापस 2;
					gh->gh_error = ret;
					list_del_init(&gh->gh_list);
					trace_gfs2_glock_queue(gh, 0);
					gfs2_holder_wake(gh);
					जाओ restart;
				पूर्ण
				set_bit(HIF_HOLDER, &gh->gh_अगरlags);
				trace_gfs2_promote(gh, 1);
				gfs2_holder_wake(gh);
				जाओ restart;
			पूर्ण
			set_bit(HIF_HOLDER, &gh->gh_अगरlags);
			trace_gfs2_promote(gh, 0);
			gfs2_holder_wake(gh);
			जारी;
		पूर्ण
		अगर (gh->gh_list.prev == &gl->gl_holders)
			वापस 1;
		करो_error(gl, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * find_first_रुकोer - find the first gh that's रुकोing क्रम the glock
 * @gl: the glock
 */

अटल अंतरभूत काष्ठा gfs2_holder *find_first_रुकोer(स्थिर काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_holder *gh;

	list_क्रम_each_entry(gh, &gl->gl_holders, gh_list) अणु
		अगर (!test_bit(HIF_HOLDER, &gh->gh_अगरlags))
			वापस gh;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * state_change - record that the glock is now in a dअगरferent state
 * @gl: the glock
 * @new_state: the new state
 */

अटल व्योम state_change(काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक new_state)
अणु
	पूर्णांक held1, held2;

	held1 = (gl->gl_state != LM_ST_UNLOCKED);
	held2 = (new_state != LM_ST_UNLOCKED);

	अगर (held1 != held2) अणु
		GLOCK_BUG_ON(gl, __lockref_is_dead(&gl->gl_lockref));
		अगर (held2)
			gl->gl_lockref.count++;
		अन्यथा
			gl->gl_lockref.count--;
	पूर्ण
	अगर (new_state != gl->gl_target)
		/* लघुen our minimum hold समय */
		gl->gl_hold_समय = max(gl->gl_hold_समय - GL_GLOCK_HOLD_DECR,
				       GL_GLOCK_MIN_HOLD);
	gl->gl_state = new_state;
	gl->gl_tchange = jअगरfies;
पूर्ण

अटल व्योम gfs2_set_demote(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;

	set_bit(GLF_DEMOTE, &gl->gl_flags);
	smp_mb();
	wake_up(&sdp->sd_async_glock_रुको);
पूर्ण

अटल व्योम gfs2_demote_wake(काष्ठा gfs2_glock *gl)
अणु
	gl->gl_demote_state = LM_ST_EXCLUSIVE;
	clear_bit(GLF_DEMOTE, &gl->gl_flags);
	smp_mb__after_atomic();
	wake_up_bit(&gl->gl_flags, GLF_DEMOTE);
पूर्ण

/**
 * finish_xmote - The DLM has replied to one of our lock requests
 * @gl: The glock
 * @ret: The status from the DLM
 *
 */

अटल व्योम finish_xmote(काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक ret)
अणु
	स्थिर काष्ठा gfs2_glock_operations *glops = gl->gl_ops;
	काष्ठा gfs2_holder *gh;
	अचिन्हित state = ret & LM_OUT_ST_MASK;
	पूर्णांक rv;

	spin_lock(&gl->gl_lockref.lock);
	trace_gfs2_glock_state_change(gl, state);
	state_change(gl, state);
	gh = find_first_रुकोer(gl);

	/* Demote to UN request arrived during demote to SH or DF */
	अगर (test_bit(GLF_DEMOTE_IN_PROGRESS, &gl->gl_flags) &&
	    state != LM_ST_UNLOCKED && gl->gl_demote_state == LM_ST_UNLOCKED)
		gl->gl_target = LM_ST_UNLOCKED;

	/* Check क्रम state != पूर्णांकended state */
	अगर (unlikely(state != gl->gl_target)) अणु
		अगर (gh && !test_bit(GLF_DEMOTE_IN_PROGRESS, &gl->gl_flags)) अणु
			/* move to back of queue and try next entry */
			अगर (ret & LM_OUT_CANCELED) अणु
				अगर ((gh->gh_flags & LM_FLAG_PRIORITY) == 0)
					list_move_tail(&gh->gh_list, &gl->gl_holders);
				gh = find_first_रुकोer(gl);
				gl->gl_target = gh->gh_state;
				जाओ retry;
			पूर्ण
			/* Some error or failed "try lock" - report it */
			अगर ((ret & LM_OUT_ERROR) ||
			    (gh->gh_flags & (LM_FLAG_TRY | LM_FLAG_TRY_1CB))) अणु
				gl->gl_target = gl->gl_state;
				करो_error(gl, ret);
				जाओ out;
			पूर्ण
		पूर्ण
		चयन(state) अणु
		/* Unlocked due to conversion deadlock, try again */
		हाल LM_ST_UNLOCKED:
retry:
			करो_xmote(gl, gh, gl->gl_target);
			अवरोध;
		/* Conversion fails, unlock and try again */
		हाल LM_ST_SHARED:
		हाल LM_ST_DEFERRED:
			करो_xmote(gl, gh, LM_ST_UNLOCKED);
			अवरोध;
		शेष: /* Everything अन्यथा */
			fs_err(gl->gl_name.ln_sbd, "wanted %u got %u\n",
			       gl->gl_target, state);
			GLOCK_BUG_ON(gl, 1);
		पूर्ण
		spin_unlock(&gl->gl_lockref.lock);
		वापस;
	पूर्ण

	/* Fast path - we got what we asked क्रम */
	अगर (test_and_clear_bit(GLF_DEMOTE_IN_PROGRESS, &gl->gl_flags))
		gfs2_demote_wake(gl);
	अगर (state != LM_ST_UNLOCKED) अणु
		अगर (glops->go_xmote_bh) अणु
			spin_unlock(&gl->gl_lockref.lock);
			rv = glops->go_xmote_bh(gl);
			spin_lock(&gl->gl_lockref.lock);
			अगर (rv) अणु
				करो_error(gl, rv);
				जाओ out;
			पूर्ण
		पूर्ण
		rv = करो_promote(gl);
		अगर (rv == 2)
			जाओ out_locked;
	पूर्ण
out:
	clear_bit(GLF_LOCK, &gl->gl_flags);
out_locked:
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

अटल bool is_प्रणाली_glock(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा gfs2_inode *m_ip = GFS2_I(sdp->sd_statfs_inode);

	अगर (gl == m_ip->i_gl)
		वापस true;
	वापस false;
पूर्ण

/**
 * करो_xmote - Calls the DLM to change the state of a lock
 * @gl: The lock state
 * @gh: The holder (only क्रम promotes)
 * @target: The target lock state
 *
 */

अटल व्योम करो_xmote(काष्ठा gfs2_glock *gl, काष्ठा gfs2_holder *gh, अचिन्हित पूर्णांक target)
__releases(&gl->gl_lockref.lock)
__acquires(&gl->gl_lockref.lock)
अणु
	स्थिर काष्ठा gfs2_glock_operations *glops = gl->gl_ops;
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	अचिन्हित पूर्णांक lck_flags = (अचिन्हित पूर्णांक)(gh ? gh->gh_flags : 0);
	पूर्णांक ret;

	अगर (target != LM_ST_UNLOCKED && glock_blocked_by_withdraw(gl) &&
	    gh && !(gh->gh_flags & LM_FLAG_NOEXP))
		वापस;
	lck_flags &= (LM_FLAG_TRY | LM_FLAG_TRY_1CB | LM_FLAG_NOEXP |
		      LM_FLAG_PRIORITY);
	GLOCK_BUG_ON(gl, gl->gl_state == target);
	GLOCK_BUG_ON(gl, gl->gl_state == gl->gl_target);
	अगर ((target == LM_ST_UNLOCKED || target == LM_ST_DEFERRED) &&
	    glops->go_inval) अणु
		/*
		 * If another process is alपढ़ोy करोing the invalidate, let that
		 * finish first.  The glock state machine will get back to this
		 * holder again later.
		 */
		अगर (test_and_set_bit(GLF_INVALIDATE_IN_PROGRESS,
				     &gl->gl_flags))
			वापस;
		करो_error(gl, 0); /* Fail queued try locks */
	पूर्ण
	gl->gl_req = target;
	set_bit(GLF_BLOCKING, &gl->gl_flags);
	अगर ((gl->gl_req == LM_ST_UNLOCKED) ||
	    (gl->gl_state == LM_ST_EXCLUSIVE) ||
	    (lck_flags & (LM_FLAG_TRY|LM_FLAG_TRY_1CB)))
		clear_bit(GLF_BLOCKING, &gl->gl_flags);
	spin_unlock(&gl->gl_lockref.lock);
	अगर (glops->go_sync) अणु
		ret = glops->go_sync(gl);
		/* If we had a problem syncing (due to io errors or whatever,
		 * we should not invalidate the metadata or tell dlm to
		 * release the glock to other nodes.
		 */
		अगर (ret) अणु
			अगर (cmpxchg(&sdp->sd_log_error, 0, ret)) अणु
				fs_err(sdp, "Error %d syncing glock \n", ret);
				gfs2_dump_glock(शून्य, gl, true);
			पूर्ण
			जाओ skip_inval;
		पूर्ण
	पूर्ण
	अगर (test_bit(GLF_INVALIDATE_IN_PROGRESS, &gl->gl_flags)) अणु
		/*
		 * The call to go_sync should have cleared out the ail list.
		 * If there are still items, we have a problem. We ought to
		 * withdraw, but we can't because the withdraw code also uses
		 * glocks. Warn about the error, dump the glock, then fall
		 * through and रुको क्रम logd to करो the withdraw क्रम us.
		 */
		अगर ((atomic_पढ़ो(&gl->gl_ail_count) != 0) &&
		    (!cmpxchg(&sdp->sd_log_error, 0, -EIO))) अणु
			gfs2_glock_निश्चित_warn(gl,
					       !atomic_पढ़ो(&gl->gl_ail_count));
			gfs2_dump_glock(शून्य, gl, true);
		पूर्ण
		glops->go_inval(gl, target == LM_ST_DEFERRED ? 0 : DIO_METADATA);
		clear_bit(GLF_INVALIDATE_IN_PROGRESS, &gl->gl_flags);
	पूर्ण

skip_inval:
	gfs2_glock_hold(gl);
	/*
	 * Check क्रम an error encountered since we called go_sync and go_inval.
	 * If so, we can't withdraw from the glock code because the withdraw
	 * code itself uses glocks (see function संकेत_our_withdraw) to
	 * change the mount to पढ़ो-only. Most importantly, we must not call
	 * dlm to unlock the glock until the journal is in a known good state
	 * (after journal replay) otherwise other nodes may use the object
	 * (rgrp or dinode) and then later, journal replay will corrupt the
	 * file प्रणाली. The best we can करो here is रुको क्रम the logd daemon
	 * to see sd_log_error and withdraw, and in the meanसमय, requeue the
	 * work क्रम later.
	 *
	 * We make a special exception क्रम some प्रणाली glocks, such as the
	 * प्रणाली statfs inode glock, which needs to be granted beक्रमe the
	 * gfs2_quotad daemon can निकास, and that निकास needs to finish beक्रमe
	 * we can unmount the withdrawn file प्रणाली.
	 *
	 * However, अगर we're just unlocking the lock (say, क्रम unmount, when
	 * gfs2_gl_hash_clear calls clear_glock) and recovery is complete
	 * then it's okay to tell dlm to unlock it.
	 */
	अगर (unlikely(sdp->sd_log_error && !gfs2_withdrawn(sdp)))
		gfs2_withdraw_delayed(sdp);
	अगर (glock_blocked_by_withdraw(gl) &&
	    (target != LM_ST_UNLOCKED ||
	     test_bit(SDF_WITHDRAW_RECOVERY, &sdp->sd_flags))) अणु
		अगर (!is_प्रणाली_glock(gl)) अणु
			gfs2_glock_queue_work(gl, GL_GLOCK_DFT_HOLD);
			जाओ out;
		पूर्ण अन्यथा अणु
			clear_bit(GLF_INVALIDATE_IN_PROGRESS, &gl->gl_flags);
		पूर्ण
	पूर्ण

	अगर (sdp->sd_lockकाष्ठा.ls_ops->lm_lock)	अणु
		/* lock_dlm */
		ret = sdp->sd_lockकाष्ठा.ls_ops->lm_lock(gl, target, lck_flags);
		अगर (ret == -EINVAL && gl->gl_target == LM_ST_UNLOCKED &&
		    target == LM_ST_UNLOCKED &&
		    test_bit(SDF_SKIP_DLM_UNLOCK, &sdp->sd_flags)) अणु
			finish_xmote(gl, target);
			gfs2_glock_queue_work(gl, 0);
		पूर्ण अन्यथा अगर (ret) अणु
			fs_err(sdp, "lm_lock ret %d\n", ret);
			GLOCK_BUG_ON(gl, !gfs2_withdrawn(sdp));
		पूर्ण
	पूर्ण अन्यथा अणु /* lock_nolock */
		finish_xmote(gl, target);
		gfs2_glock_queue_work(gl, 0);
	पूर्ण
out:
	spin_lock(&gl->gl_lockref.lock);
पूर्ण

/**
 * find_first_holder - find the first "holder" gh
 * @gl: the glock
 */

अटल अंतरभूत काष्ठा gfs2_holder *find_first_holder(स्थिर काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_holder *gh;

	अगर (!list_empty(&gl->gl_holders)) अणु
		gh = list_first_entry(&gl->gl_holders, काष्ठा gfs2_holder, gh_list);
		अगर (test_bit(HIF_HOLDER, &gh->gh_अगरlags))
			वापस gh;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * run_queue - करो all outstanding tasks related to a glock
 * @gl: The glock in question
 * @nonblock: True अगर we must not block in run_queue
 *
 */

अटल व्योम run_queue(काष्ठा gfs2_glock *gl, स्थिर पूर्णांक nonblock)
__releases(&gl->gl_lockref.lock)
__acquires(&gl->gl_lockref.lock)
अणु
	काष्ठा gfs2_holder *gh = शून्य;
	पूर्णांक ret;

	अगर (test_and_set_bit(GLF_LOCK, &gl->gl_flags))
		वापस;

	GLOCK_BUG_ON(gl, test_bit(GLF_DEMOTE_IN_PROGRESS, &gl->gl_flags));

	अगर (test_bit(GLF_DEMOTE, &gl->gl_flags) &&
	    gl->gl_demote_state != gl->gl_state) अणु
		अगर (find_first_holder(gl))
			जाओ out_unlock;
		अगर (nonblock)
			जाओ out_sched;
		set_bit(GLF_DEMOTE_IN_PROGRESS, &gl->gl_flags);
		GLOCK_BUG_ON(gl, gl->gl_demote_state == LM_ST_EXCLUSIVE);
		gl->gl_target = gl->gl_demote_state;
	पूर्ण अन्यथा अणु
		अगर (test_bit(GLF_DEMOTE, &gl->gl_flags))
			gfs2_demote_wake(gl);
		ret = करो_promote(gl);
		अगर (ret == 0)
			जाओ out_unlock;
		अगर (ret == 2)
			जाओ out;
		gh = find_first_रुकोer(gl);
		gl->gl_target = gh->gh_state;
		अगर (!(gh->gh_flags & (LM_FLAG_TRY | LM_FLAG_TRY_1CB)))
			करो_error(gl, 0); /* Fail queued try locks */
	पूर्ण
	करो_xmote(gl, gh, gl->gl_target);
out:
	वापस;

out_sched:
	clear_bit(GLF_LOCK, &gl->gl_flags);
	smp_mb__after_atomic();
	gl->gl_lockref.count++;
	__gfs2_glock_queue_work(gl, 0);
	वापस;

out_unlock:
	clear_bit(GLF_LOCK, &gl->gl_flags);
	smp_mb__after_atomic();
	वापस;
पूर्ण

व्योम gfs2_inode_remember_delete(काष्ठा gfs2_glock *gl, u64 generation)
अणु
	काष्ठा gfs2_inode_lvb *ri = (व्योम *)gl->gl_lksb.sb_lvbptr;

	अगर (ri->ri_magic == 0)
		ri->ri_magic = cpu_to_be32(GFS2_MAGIC);
	अगर (ri->ri_magic == cpu_to_be32(GFS2_MAGIC))
		ri->ri_generation_deleted = cpu_to_be64(generation);
पूर्ण

bool gfs2_inode_alपढ़ोy_deleted(काष्ठा gfs2_glock *gl, u64 generation)
अणु
	काष्ठा gfs2_inode_lvb *ri = (व्योम *)gl->gl_lksb.sb_lvbptr;

	अगर (ri->ri_magic != cpu_to_be32(GFS2_MAGIC))
		वापस false;
	वापस generation <= be64_to_cpu(ri->ri_generation_deleted);
पूर्ण

अटल व्योम gfs2_glock_poke(काष्ठा gfs2_glock *gl)
अणु
	पूर्णांक flags = LM_FLAG_TRY_1CB | LM_FLAG_ANY | GL_SKIP;
	काष्ठा gfs2_holder gh;
	पूर्णांक error;

	gfs2_holder_init(gl, LM_ST_SHARED, flags, &gh);
	error = gfs2_glock_nq(&gh);
	अगर (!error)
		gfs2_glock_dq(&gh);
	gfs2_holder_uninit(&gh);
पूर्ण

अटल bool gfs2_try_evict(काष्ठा gfs2_glock *gl)
अणु
	काष्ठा gfs2_inode *ip;
	bool evicted = false;

	/*
	 * If there is contention on the iखोलो glock and we have an inode, try
	 * to grab and release the inode so that it can be evicted.  This will
	 * allow the remote node to go ahead and delete the inode without us
	 * having to करो it, which will aव्योम rgrp glock thrashing.
	 *
	 * The remote node is likely still holding the corresponding inode
	 * glock, so it will run beक्रमe we get to verअगरy that the delete has
	 * happened below.
	 */
	spin_lock(&gl->gl_lockref.lock);
	ip = gl->gl_object;
	अगर (ip && !igrab(&ip->i_inode))
		ip = शून्य;
	spin_unlock(&gl->gl_lockref.lock);
	अगर (ip) अणु
		काष्ठा gfs2_glock *inode_gl = शून्य;

		gl->gl_no_क्रमmal_ino = ip->i_no_क्रमmal_ino;
		set_bit(GIF_DEFERRED_DELETE, &ip->i_flags);
		d_prune_aliases(&ip->i_inode);
		iput(&ip->i_inode);

		/* If the inode was evicted, gl->gl_object will now be शून्य. */
		spin_lock(&gl->gl_lockref.lock);
		ip = gl->gl_object;
		अगर (ip) अणु
			inode_gl = ip->i_gl;
			lockref_get(&inode_gl->gl_lockref);
			clear_bit(GIF_DEFERRED_DELETE, &ip->i_flags);
		पूर्ण
		spin_unlock(&gl->gl_lockref.lock);
		अगर (inode_gl) अणु
			gfs2_glock_poke(inode_gl);
			gfs2_glock_put(inode_gl);
		पूर्ण
		evicted = !ip;
	पूर्ण
	वापस evicted;
पूर्ण

अटल व्योम delete_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(work);
	काष्ठा gfs2_glock *gl = container_of(dwork, काष्ठा gfs2_glock, gl_delete);
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा inode *inode;
	u64 no_addr = gl->gl_name.ln_number;

	spin_lock(&gl->gl_lockref.lock);
	clear_bit(GLF_PENDING_DELETE, &gl->gl_flags);
	spin_unlock(&gl->gl_lockref.lock);

	अगर (test_bit(GLF_DEMOTE, &gl->gl_flags)) अणु
		/*
		 * If we can evict the inode, give the remote node trying to
		 * delete the inode some समय beक्रमe verअगरying that the delete
		 * has happened.  Otherwise, अगर we cause contention on the inode glock
		 * immediately, the remote node will think that we still have
		 * the inode in use, and so it will give up रुकोing.
		 *
		 * If we can't evict the inode, संकेत to the remote node that
		 * the inode is still in use.  We'll later try to delete the
		 * inode locally in gfs2_evict_inode.
		 *
		 * FIXME: We only need to verअगरy that the remote node has
		 * deleted the inode because nodes beक्रमe this remote delete
		 * rework won't cooperate.  At a later समय, when we no दीर्घer
		 * care about compatibility with such nodes, we can skip this
		 * step entirely.
		 */
		अगर (gfs2_try_evict(gl)) अणु
			अगर (gfs2_queue_delete_work(gl, 5 * HZ))
				वापस;
		पूर्ण
		जाओ out;
	पूर्ण

	inode = gfs2_lookup_by_inum(sdp, no_addr, gl->gl_no_क्रमmal_ino,
				    GFS2_BLKST_UNLINKED);
	अगर (!IS_ERR_OR_शून्य(inode)) अणु
		d_prune_aliases(inode);
		iput(inode);
	पूर्ण
out:
	gfs2_glock_put(gl);
पूर्ण

अटल व्योम glock_work_func(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ delay = 0;
	काष्ठा gfs2_glock *gl = container_of(work, काष्ठा gfs2_glock, gl_work.work);
	अचिन्हित पूर्णांक drop_refs = 1;

	अगर (test_and_clear_bit(GLF_REPLY_PENDING, &gl->gl_flags)) अणु
		finish_xmote(gl, gl->gl_reply);
		drop_refs++;
	पूर्ण
	spin_lock(&gl->gl_lockref.lock);
	अगर (test_bit(GLF_PENDING_DEMOTE, &gl->gl_flags) &&
	    gl->gl_state != LM_ST_UNLOCKED &&
	    gl->gl_demote_state != LM_ST_EXCLUSIVE) अणु
		अचिन्हित दीर्घ holdसमय, now = jअगरfies;

		holdसमय = gl->gl_tchange + gl->gl_hold_समय;
		अगर (समय_beक्रमe(now, holdसमय))
			delay = holdसमय - now;

		अगर (!delay) अणु
			clear_bit(GLF_PENDING_DEMOTE, &gl->gl_flags);
			gfs2_set_demote(gl);
		पूर्ण
	पूर्ण
	run_queue(gl, 0);
	अगर (delay) अणु
		/* Keep one glock reference क्रम the work we requeue. */
		drop_refs--;
		अगर (gl->gl_name.ln_type != LM_TYPE_INODE)
			delay = 0;
		__gfs2_glock_queue_work(gl, delay);
	पूर्ण

	/*
	 * Drop the reमुख्यing glock references manually here. (Mind that
	 * __gfs2_glock_queue_work depends on the lockref spinlock begin held
	 * here as well.)
	 */
	gl->gl_lockref.count -= drop_refs;
	अगर (!gl->gl_lockref.count) अणु
		__gfs2_glock_put(gl);
		वापस;
	पूर्ण
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

अटल काष्ठा gfs2_glock *find_insert_glock(काष्ठा lm_lockname *name,
					    काष्ठा gfs2_glock *new)
अणु
	काष्ठा रुको_glock_queue रुको;
	रुको_queue_head_t *wq = glock_रुकोqueue(name);
	काष्ठा gfs2_glock *gl;

	रुको.name = name;
	init_रुको(&रुको.रुको);
	रुको.रुको.func = glock_wake_function;

again:
	prepare_to_रुको(wq, &रुको.रुको, TASK_UNINTERRUPTIBLE);
	rcu_पढ़ो_lock();
	अगर (new) अणु
		gl = rhashtable_lookup_get_insert_fast(&gl_hash_table,
			&new->gl_node, ht_parms);
		अगर (IS_ERR(gl))
			जाओ out;
	पूर्ण अन्यथा अणु
		gl = rhashtable_lookup_fast(&gl_hash_table,
			name, ht_parms);
	पूर्ण
	अगर (gl && !lockref_get_not_dead(&gl->gl_lockref)) अणु
		rcu_पढ़ो_unlock();
		schedule();
		जाओ again;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	finish_रुको(wq, &रुको.रुको);
	वापस gl;
पूर्ण

/**
 * gfs2_glock_get() - Get a glock, or create one अगर one करोesn't exist
 * @sdp: The GFS2 superblock
 * @number: the lock number
 * @glops: The glock_operations to use
 * @create: If 0, करोn't create the glock if it doesn't exist
 * @glp: the glock is वापसed here
 *
 * This करोes not lock a glock, just finds/creates काष्ठाures क्रम one.
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_glock_get(काष्ठा gfs2_sbd *sdp, u64 number,
		   स्थिर काष्ठा gfs2_glock_operations *glops, पूर्णांक create,
		   काष्ठा gfs2_glock **glp)
अणु
	काष्ठा super_block *s = sdp->sd_vfs;
	काष्ठा lm_lockname name = अणु .ln_number = number,
				    .ln_type = glops->go_type,
				    .ln_sbd = sdp पूर्ण;
	काष्ठा gfs2_glock *gl, *पंचांगp;
	काष्ठा address_space *mapping;
	काष्ठा kmem_cache *cachep;
	पूर्णांक ret = 0;

	gl = find_insert_glock(&name, शून्य);
	अगर (gl) अणु
		*glp = gl;
		वापस 0;
	पूर्ण
	अगर (!create)
		वापस -ENOENT;

	अगर (glops->go_flags & GLOF_ASPACE)
		cachep = gfs2_glock_aspace_cachep;
	अन्यथा
		cachep = gfs2_glock_cachep;
	gl = kmem_cache_alloc(cachep, GFP_NOFS);
	अगर (!gl)
		वापस -ENOMEM;

	स_रखो(&gl->gl_lksb, 0, माप(काष्ठा dlm_lksb));

	अगर (glops->go_flags & GLOF_LVB) अणु
		gl->gl_lksb.sb_lvbptr = kzalloc(GDLM_LVB_SIZE, GFP_NOFS);
		अगर (!gl->gl_lksb.sb_lvbptr) अणु
			kmem_cache_मुक्त(cachep, gl);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	atomic_inc(&sdp->sd_glock_disposal);
	gl->gl_node.next = शून्य;
	gl->gl_flags = 0;
	gl->gl_name = name;
	lockdep_set_subclass(&gl->gl_lockref.lock, glops->go_subclass);
	gl->gl_lockref.count = 1;
	gl->gl_state = LM_ST_UNLOCKED;
	gl->gl_target = LM_ST_UNLOCKED;
	gl->gl_demote_state = LM_ST_EXCLUSIVE;
	gl->gl_ops = glops;
	gl->gl_dstamp = 0;
	preempt_disable();
	/* We use the global stats to estimate the initial per-glock stats */
	gl->gl_stats = this_cpu_ptr(sdp->sd_lkstats)->lkstats[glops->go_type];
	preempt_enable();
	gl->gl_stats.stats[GFS2_LKS_DCOUNT] = 0;
	gl->gl_stats.stats[GFS2_LKS_QCOUNT] = 0;
	gl->gl_tchange = jअगरfies;
	gl->gl_object = शून्य;
	gl->gl_hold_समय = GL_GLOCK_DFT_HOLD;
	INIT_DELAYED_WORK(&gl->gl_work, glock_work_func);
	अगर (gl->gl_name.ln_type == LM_TYPE_IOPEN)
		INIT_DELAYED_WORK(&gl->gl_delete, delete_work_func);

	mapping = gfs2_glock2aspace(gl);
	अगर (mapping) अणु
                mapping->a_ops = &gfs2_meta_aops;
		mapping->host = s->s_bdev->bd_inode;
		mapping->flags = 0;
		mapping_set_gfp_mask(mapping, GFP_NOFS);
		mapping->निजी_data = शून्य;
		mapping->ग_लिखोback_index = 0;
	पूर्ण

	पंचांगp = find_insert_glock(&name, gl);
	अगर (!पंचांगp) अणु
		*glp = gl;
		जाओ out;
	पूर्ण
	अगर (IS_ERR(पंचांगp)) अणु
		ret = PTR_ERR(पंचांगp);
		जाओ out_मुक्त;
	पूर्ण
	*glp = पंचांगp;

out_मुक्त:
	kमुक्त(gl->gl_lksb.sb_lvbptr);
	kmem_cache_मुक्त(cachep, gl);
	अगर (atomic_dec_and_test(&sdp->sd_glock_disposal))
		wake_up(&sdp->sd_glock_रुको);

out:
	वापस ret;
पूर्ण

/**
 * gfs2_holder_init - initialize a काष्ठा gfs2_holder in the शेष way
 * @gl: the glock
 * @state: the state we're requesting
 * @flags: the modअगरier flags
 * @gh: the holder काष्ठाure
 *
 */

व्योम gfs2_holder_init(काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक state, u16 flags,
		      काष्ठा gfs2_holder *gh)
अणु
	INIT_LIST_HEAD(&gh->gh_list);
	gh->gh_gl = gl;
	gh->gh_ip = _RET_IP_;
	gh->gh_owner_pid = get_pid(task_pid(current));
	gh->gh_state = state;
	gh->gh_flags = flags;
	gh->gh_error = 0;
	gh->gh_अगरlags = 0;
	gfs2_glock_hold(gl);
पूर्ण

/**
 * gfs2_holder_reinit - reinitialize a काष्ठा gfs2_holder so we can requeue it
 * @state: the state we're requesting
 * @flags: the modअगरier flags
 * @gh: the holder काष्ठाure
 *
 * Don't mess with the glock.
 *
 */

व्योम gfs2_holder_reinit(अचिन्हित पूर्णांक state, u16 flags, काष्ठा gfs2_holder *gh)
अणु
	gh->gh_state = state;
	gh->gh_flags = flags;
	gh->gh_अगरlags = 0;
	gh->gh_ip = _RET_IP_;
	put_pid(gh->gh_owner_pid);
	gh->gh_owner_pid = get_pid(task_pid(current));
पूर्ण

/**
 * gfs2_holder_uninit - uninitialize a holder काष्ठाure (drop glock reference)
 * @gh: the holder काष्ठाure
 *
 */

व्योम gfs2_holder_uninit(काष्ठा gfs2_holder *gh)
अणु
	put_pid(gh->gh_owner_pid);
	gfs2_glock_put(gh->gh_gl);
	gfs2_holder_mark_uninitialized(gh);
	gh->gh_ip = 0;
पूर्ण

अटल व्योम gfs2_glock_update_hold_समय(काष्ठा gfs2_glock *gl,
					अचिन्हित दीर्घ start_समय)
अणु
	/* Have we रुकोed दीर्घer that a second? */
	अगर (समय_after(jअगरfies, start_समय + HZ)) अणु
		/* Lengthen the minimum hold समय. */
		gl->gl_hold_समय = min(gl->gl_hold_समय + GL_GLOCK_HOLD_INCR,
				       GL_GLOCK_MAX_HOLD);
	पूर्ण
पूर्ण

/**
 * gfs2_glock_रुको - रुको on a glock acquisition
 * @gh: the glock holder
 *
 * Returns: 0 on success
 */

पूर्णांक gfs2_glock_रुको(काष्ठा gfs2_holder *gh)
अणु
	अचिन्हित दीर्घ start_समय = jअगरfies;

	might_sleep();
	रुको_on_bit(&gh->gh_अगरlags, HIF_WAIT, TASK_UNINTERRUPTIBLE);
	gfs2_glock_update_hold_समय(gh->gh_gl, start_समय);
	वापस gh->gh_error;
पूर्ण

अटल पूर्णांक glocks_pending(अचिन्हित पूर्णांक num_gh, काष्ठा gfs2_holder *ghs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_gh; i++)
		अगर (test_bit(HIF_WAIT, &ghs[i].gh_अगरlags))
			वापस 1;
	वापस 0;
पूर्ण

/**
 * gfs2_glock_async_रुको - रुको on multiple asynchronous glock acquisitions
 * @num_gh: the number of holders in the array
 * @ghs: the glock holder array
 *
 * Returns: 0 on success, meaning all glocks have been granted and are held.
 *          -ESTALE अगर the request समयd out, meaning all glocks were released,
 *          and the caller should retry the operation.
 */

पूर्णांक gfs2_glock_async_रुको(अचिन्हित पूर्णांक num_gh, काष्ठा gfs2_holder *ghs)
अणु
	काष्ठा gfs2_sbd *sdp = ghs[0].gh_gl->gl_name.ln_sbd;
	पूर्णांक i, ret = 0, समयout = 0;
	अचिन्हित दीर्घ start_समय = jअगरfies;
	bool keep_रुकोing;

	might_sleep();
	/*
	 * Total up the (minimum hold समय * 2) of all glocks and use that to
	 * determine the max amount of समय we should रुको.
	 */
	क्रम (i = 0; i < num_gh; i++)
		समयout += ghs[i].gh_gl->gl_hold_समय << 1;

रुको_क्रम_dlm:
	अगर (!रुको_event_समयout(sdp->sd_async_glock_रुको,
				!glocks_pending(num_gh, ghs), समयout))
		ret = -ESTALE; /* request समयd out. */

	/*
	 * If dlm granted all our requests, we need to adjust the glock
	 * minimum hold समय values according to how दीर्घ we रुकोed.
	 *
	 * If our request समयd out, we need to repeatedly release any held
	 * glocks we acquired thus far to allow dlm to acquire the reमुख्यing
	 * glocks without deadlocking.  We cannot currently cancel outstanding
	 * glock acquisitions.
	 *
	 * The HIF_WAIT bit tells us which requests still need a response from
	 * dlm.
	 *
	 * If dlm sent us any errors, we वापस the first error we find.
	 */
	keep_रुकोing = false;
	क्रम (i = 0; i < num_gh; i++) अणु
		/* Skip holders we have alपढ़ोy dequeued below. */
		अगर (!gfs2_holder_queued(&ghs[i]))
			जारी;
		/* Skip holders with a pending DLM response. */
		अगर (test_bit(HIF_WAIT, &ghs[i].gh_अगरlags)) अणु
			keep_रुकोing = true;
			जारी;
		पूर्ण

		अगर (test_bit(HIF_HOLDER, &ghs[i].gh_अगरlags)) अणु
			अगर (ret == -ESTALE)
				gfs2_glock_dq(&ghs[i]);
			अन्यथा
				gfs2_glock_update_hold_समय(ghs[i].gh_gl,
							    start_समय);
		पूर्ण
		अगर (!ret)
			ret = ghs[i].gh_error;
	पूर्ण

	अगर (keep_रुकोing)
		जाओ रुको_क्रम_dlm;

	/*
	 * At this poपूर्णांक, we've either acquired all locks or released them all.
	 */
	वापस ret;
पूर्ण

/**
 * handle_callback - process a demote request
 * @gl: the glock
 * @state: the state the caller wants us to change to
 * @delay: zero to demote immediately; otherwise pending demote
 * @remote: true अगर this came from a dअगरferent cluster node
 *
 * There are only two requests that we are going to see in actual
 * practise: LM_ST_SHARED and LM_ST_UNLOCKED
 */

अटल व्योम handle_callback(काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक state,
			    अचिन्हित दीर्घ delay, bool remote)
अणु
	अगर (delay)
		set_bit(GLF_PENDING_DEMOTE, &gl->gl_flags);
	अन्यथा
		gfs2_set_demote(gl);
	अगर (gl->gl_demote_state == LM_ST_EXCLUSIVE) अणु
		gl->gl_demote_state = state;
		gl->gl_demote_समय = jअगरfies;
	पूर्ण अन्यथा अगर (gl->gl_demote_state != LM_ST_UNLOCKED &&
			gl->gl_demote_state != state) अणु
		gl->gl_demote_state = LM_ST_UNLOCKED;
	पूर्ण
	अगर (gl->gl_ops->go_callback)
		gl->gl_ops->go_callback(gl, remote);
	trace_gfs2_demote_rq(gl, remote);
पूर्ण

व्योम gfs2_prपूर्णांक_dbg(काष्ठा seq_file *seq, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	अगर (seq) अणु
		seq_भ_लिखो(seq, fmt, args);
	पूर्ण अन्यथा अणु
		vaf.fmt = fmt;
		vaf.va = &args;

		pr_err("%pV", &vaf);
	पूर्ण

	बहु_पूर्ण(args);
पूर्ण

/**
 * add_to_queue - Add a holder to the रुको queue (but look क्रम recursion)
 * @gh: the holder काष्ठाure to add
 *
 * Eventually we should move the recursive locking trap to a
 * debugging option or something like that. This is the fast
 * path and needs to have the minimum number of distractions.
 * 
 */

अटल अंतरभूत व्योम add_to_queue(काष्ठा gfs2_holder *gh)
__releases(&gl->gl_lockref.lock)
__acquires(&gl->gl_lockref.lock)
अणु
	काष्ठा gfs2_glock *gl = gh->gh_gl;
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	काष्ठा list_head *insert_pt = शून्य;
	काष्ठा gfs2_holder *gh2;
	पूर्णांक try_futile = 0;

	GLOCK_BUG_ON(gl, gh->gh_owner_pid == शून्य);
	अगर (test_and_set_bit(HIF_WAIT, &gh->gh_अगरlags))
		GLOCK_BUG_ON(gl, true);

	अगर (gh->gh_flags & (LM_FLAG_TRY | LM_FLAG_TRY_1CB)) अणु
		अगर (test_bit(GLF_LOCK, &gl->gl_flags))
			try_futile = !may_grant(gl, gh);
		अगर (test_bit(GLF_INVALIDATE_IN_PROGRESS, &gl->gl_flags))
			जाओ fail;
	पूर्ण

	list_क्रम_each_entry(gh2, &gl->gl_holders, gh_list) अणु
		अगर (unlikely(gh2->gh_owner_pid == gh->gh_owner_pid &&
		    (gh->gh_gl->gl_ops->go_type != LM_TYPE_FLOCK)))
			जाओ trap_recursive;
		अगर (try_futile &&
		    !(gh2->gh_flags & (LM_FLAG_TRY | LM_FLAG_TRY_1CB))) अणु
fail:
			gh->gh_error = GLR_TRYFAILED;
			gfs2_holder_wake(gh);
			वापस;
		पूर्ण
		अगर (test_bit(HIF_HOLDER, &gh2->gh_अगरlags))
			जारी;
		अगर (unlikely((gh->gh_flags & LM_FLAG_PRIORITY) && !insert_pt))
			insert_pt = &gh2->gh_list;
	पूर्ण
	trace_gfs2_glock_queue(gh, 1);
	gfs2_glstats_inc(gl, GFS2_LKS_QCOUNT);
	gfs2_sbstats_inc(gl, GFS2_LKS_QCOUNT);
	अगर (likely(insert_pt == शून्य)) अणु
		list_add_tail(&gh->gh_list, &gl->gl_holders);
		अगर (unlikely(gh->gh_flags & LM_FLAG_PRIORITY))
			जाओ करो_cancel;
		वापस;
	पूर्ण
	list_add_tail(&gh->gh_list, insert_pt);
करो_cancel:
	gh = list_first_entry(&gl->gl_holders, काष्ठा gfs2_holder, gh_list);
	अगर (!(gh->gh_flags & LM_FLAG_PRIORITY)) अणु
		spin_unlock(&gl->gl_lockref.lock);
		अगर (sdp->sd_lockकाष्ठा.ls_ops->lm_cancel)
			sdp->sd_lockकाष्ठा.ls_ops->lm_cancel(gl);
		spin_lock(&gl->gl_lockref.lock);
	पूर्ण
	वापस;

trap_recursive:
	fs_err(sdp, "original: %pSR\n", (व्योम *)gh2->gh_ip);
	fs_err(sdp, "pid: %d\n", pid_nr(gh2->gh_owner_pid));
	fs_err(sdp, "lock type: %d req lock state : %d\n",
	       gh2->gh_gl->gl_name.ln_type, gh2->gh_state);
	fs_err(sdp, "new: %pSR\n", (व्योम *)gh->gh_ip);
	fs_err(sdp, "pid: %d\n", pid_nr(gh->gh_owner_pid));
	fs_err(sdp, "lock type: %d req lock state : %d\n",
	       gh->gh_gl->gl_name.ln_type, gh->gh_state);
	gfs2_dump_glock(शून्य, gl, true);
	BUG();
पूर्ण

/**
 * gfs2_glock_nq - enqueue a काष्ठा gfs2_holder onto a glock (acquire a glock)
 * @gh: the holder काष्ठाure
 *
 * अगर (gh->gh_flags & GL_ASYNC), this never वापसs an error
 *
 * Returns: 0, GLR_TRYFAILED, or त्रुटि_सं on failure
 */

पूर्णांक gfs2_glock_nq(काष्ठा gfs2_holder *gh)
अणु
	काष्ठा gfs2_glock *gl = gh->gh_gl;
	पूर्णांक error = 0;

	अगर (glock_blocked_by_withdraw(gl) && !(gh->gh_flags & LM_FLAG_NOEXP))
		वापस -EIO;

	अगर (test_bit(GLF_LRU, &gl->gl_flags))
		gfs2_glock_हटाओ_from_lru(gl);

	spin_lock(&gl->gl_lockref.lock);
	add_to_queue(gh);
	अगर (unlikely((LM_FLAG_NOEXP & gh->gh_flags) &&
		     test_and_clear_bit(GLF_FROZEN, &gl->gl_flags))) अणु
		set_bit(GLF_REPLY_PENDING, &gl->gl_flags);
		gl->gl_lockref.count++;
		__gfs2_glock_queue_work(gl, 0);
	पूर्ण
	run_queue(gl, 1);
	spin_unlock(&gl->gl_lockref.lock);

	अगर (!(gh->gh_flags & GL_ASYNC))
		error = gfs2_glock_रुको(gh);

	वापस error;
पूर्ण

/**
 * gfs2_glock_poll - poll to see अगर an async request has been completed
 * @gh: the holder
 *
 * Returns: 1 अगर the request is पढ़ोy to be gfs2_glock_रुको()ed on
 */

पूर्णांक gfs2_glock_poll(काष्ठा gfs2_holder *gh)
अणु
	वापस test_bit(HIF_WAIT, &gh->gh_अगरlags) ? 0 : 1;
पूर्ण

/**
 * gfs2_glock_dq - dequeue a काष्ठा gfs2_holder from a glock (release a glock)
 * @gh: the glock holder
 *
 */

व्योम gfs2_glock_dq(काष्ठा gfs2_holder *gh)
अणु
	काष्ठा gfs2_glock *gl = gh->gh_gl;
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	अचिन्हित delay = 0;
	पूर्णांक fast_path = 0;

	spin_lock(&gl->gl_lockref.lock);
	/*
	 * If we're in the process of file प्रणाली withdraw, we cannot just
	 * dequeue any glocks until our journal is recovered, lest we
	 * पूर्णांकroduce file प्रणाली corruption. We need two exceptions to this
	 * rule: We need to allow unlocking of nondisk glocks and the glock
	 * क्रम our own journal that needs recovery.
	 */
	अगर (test_bit(SDF_WITHDRAW_RECOVERY, &sdp->sd_flags) &&
	    glock_blocked_by_withdraw(gl) &&
	    gh->gh_gl != sdp->sd_jinode_gl) अणु
		sdp->sd_glock_dqs_held++;
		spin_unlock(&gl->gl_lockref.lock);
		might_sleep();
		रुको_on_bit(&sdp->sd_flags, SDF_WITHDRAW_RECOVERY,
			    TASK_UNINTERRUPTIBLE);
		spin_lock(&gl->gl_lockref.lock);
	पूर्ण
	अगर (gh->gh_flags & GL_NOCACHE)
		handle_callback(gl, LM_ST_UNLOCKED, 0, false);

	list_del_init(&gh->gh_list);
	clear_bit(HIF_HOLDER, &gh->gh_अगरlags);
	अगर (find_first_holder(gl) == शून्य) अणु
		अगर (list_empty(&gl->gl_holders) &&
		    !test_bit(GLF_PENDING_DEMOTE, &gl->gl_flags) &&
		    !test_bit(GLF_DEMOTE, &gl->gl_flags))
			fast_path = 1;
	पूर्ण
	अगर (!test_bit(GLF_LFLUSH, &gl->gl_flags) && demote_ok(gl))
		gfs2_glock_add_to_lru(gl);

	trace_gfs2_glock_queue(gh, 0);
	अगर (unlikely(!fast_path)) अणु
		gl->gl_lockref.count++;
		अगर (test_bit(GLF_PENDING_DEMOTE, &gl->gl_flags) &&
		    !test_bit(GLF_DEMOTE, &gl->gl_flags) &&
		    gl->gl_name.ln_type == LM_TYPE_INODE)
			delay = gl->gl_hold_समय;
		__gfs2_glock_queue_work(gl, delay);
	पूर्ण
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

व्योम gfs2_glock_dq_रुको(काष्ठा gfs2_holder *gh)
अणु
	काष्ठा gfs2_glock *gl = gh->gh_gl;
	gfs2_glock_dq(gh);
	might_sleep();
	रुको_on_bit(&gl->gl_flags, GLF_DEMOTE, TASK_UNINTERRUPTIBLE);
पूर्ण

/**
 * gfs2_glock_dq_uninit - dequeue a holder from a glock and initialize it
 * @gh: the holder काष्ठाure
 *
 */

व्योम gfs2_glock_dq_uninit(काष्ठा gfs2_holder *gh)
अणु
	gfs2_glock_dq(gh);
	gfs2_holder_uninit(gh);
पूर्ण

/**
 * gfs2_glock_nq_num - acquire a glock based on lock number
 * @sdp: the fileप्रणाली
 * @number: the lock number
 * @glops: the glock operations क्रम the type of glock
 * @state: the state to acquire the glock in
 * @flags: modअगरier flags क्रम the acquisition
 * @gh: the काष्ठा gfs2_holder
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_glock_nq_num(काष्ठा gfs2_sbd *sdp, u64 number,
		      स्थिर काष्ठा gfs2_glock_operations *glops,
		      अचिन्हित पूर्णांक state, u16 flags, काष्ठा gfs2_holder *gh)
अणु
	काष्ठा gfs2_glock *gl;
	पूर्णांक error;

	error = gfs2_glock_get(sdp, number, glops, CREATE, &gl);
	अगर (!error) अणु
		error = gfs2_glock_nq_init(gl, state, flags, gh);
		gfs2_glock_put(gl);
	पूर्ण

	वापस error;
पूर्ण

/**
 * glock_compare - Compare two काष्ठा gfs2_glock काष्ठाures क्रम sorting
 * @arg_a: the first काष्ठाure
 * @arg_b: the second काष्ठाure
 *
 */

अटल पूर्णांक glock_compare(स्थिर व्योम *arg_a, स्थिर व्योम *arg_b)
अणु
	स्थिर काष्ठा gfs2_holder *gh_a = *(स्थिर काष्ठा gfs2_holder **)arg_a;
	स्थिर काष्ठा gfs2_holder *gh_b = *(स्थिर काष्ठा gfs2_holder **)arg_b;
	स्थिर काष्ठा lm_lockname *a = &gh_a->gh_gl->gl_name;
	स्थिर काष्ठा lm_lockname *b = &gh_b->gh_gl->gl_name;

	अगर (a->ln_number > b->ln_number)
		वापस 1;
	अगर (a->ln_number < b->ln_number)
		वापस -1;
	BUG_ON(gh_a->gh_gl->gl_ops->go_type == gh_b->gh_gl->gl_ops->go_type);
	वापस 0;
पूर्ण

/**
 * nq_m_sync - synchonously acquire more than one glock in deadlock मुक्त order
 * @num_gh: the number of काष्ठाures
 * @ghs: an array of काष्ठा gfs2_holder काष्ठाures
 * @p: placeholder क्रम the holder काष्ठाure to pass back
 *
 * Returns: 0 on success (all glocks acquired),
 *          त्रुटि_सं on failure (no glocks acquired)
 */

अटल पूर्णांक nq_m_sync(अचिन्हित पूर्णांक num_gh, काष्ठा gfs2_holder *ghs,
		     काष्ठा gfs2_holder **p)
अणु
	अचिन्हित पूर्णांक x;
	पूर्णांक error = 0;

	क्रम (x = 0; x < num_gh; x++)
		p[x] = &ghs[x];

	sort(p, num_gh, माप(काष्ठा gfs2_holder *), glock_compare, शून्य);

	क्रम (x = 0; x < num_gh; x++) अणु
		p[x]->gh_flags &= ~(LM_FLAG_TRY | GL_ASYNC);

		error = gfs2_glock_nq(p[x]);
		अगर (error) अणु
			जबतक (x--)
				gfs2_glock_dq(p[x]);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस error;
पूर्ण

/**
 * gfs2_glock_nq_m - acquire multiple glocks
 * @num_gh: the number of काष्ठाures
 * @ghs: an array of काष्ठा gfs2_holder काष्ठाures
 *
 *
 * Returns: 0 on success (all glocks acquired),
 *          त्रुटि_सं on failure (no glocks acquired)
 */

पूर्णांक gfs2_glock_nq_m(अचिन्हित पूर्णांक num_gh, काष्ठा gfs2_holder *ghs)
अणु
	काष्ठा gfs2_holder *पंचांगp[4];
	काष्ठा gfs2_holder **pph = पंचांगp;
	पूर्णांक error = 0;

	चयन(num_gh) अणु
	हाल 0:
		वापस 0;
	हाल 1:
		ghs->gh_flags &= ~(LM_FLAG_TRY | GL_ASYNC);
		वापस gfs2_glock_nq(ghs);
	शेष:
		अगर (num_gh <= 4)
			अवरोध;
		pph = kदो_स्मृति_array(num_gh, माप(काष्ठा gfs2_holder *),
				    GFP_NOFS);
		अगर (!pph)
			वापस -ENOMEM;
	पूर्ण

	error = nq_m_sync(num_gh, ghs, pph);

	अगर (pph != पंचांगp)
		kमुक्त(pph);

	वापस error;
पूर्ण

/**
 * gfs2_glock_dq_m - release multiple glocks
 * @num_gh: the number of काष्ठाures
 * @ghs: an array of काष्ठा gfs2_holder काष्ठाures
 *
 */

व्योम gfs2_glock_dq_m(अचिन्हित पूर्णांक num_gh, काष्ठा gfs2_holder *ghs)
अणु
	जबतक (num_gh--)
		gfs2_glock_dq(&ghs[num_gh]);
पूर्ण

व्योम gfs2_glock_cb(काष्ठा gfs2_glock *gl, अचिन्हित पूर्णांक state)
अणु
	अचिन्हित दीर्घ delay = 0;
	अचिन्हित दीर्घ holdसमय;
	अचिन्हित दीर्घ now = jअगरfies;

	gfs2_glock_hold(gl);
	spin_lock(&gl->gl_lockref.lock);
	holdसमय = gl->gl_tchange + gl->gl_hold_समय;
	अगर (!list_empty(&gl->gl_holders) &&
	    gl->gl_name.ln_type == LM_TYPE_INODE) अणु
		अगर (समय_beक्रमe(now, holdसमय))
			delay = holdसमय - now;
		अगर (test_bit(GLF_REPLY_PENDING, &gl->gl_flags))
			delay = gl->gl_hold_समय;
	पूर्ण
	handle_callback(gl, state, delay, true);
	__gfs2_glock_queue_work(gl, delay);
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

/**
 * gfs2_should_मुक्तze - Figure out अगर glock should be frozen
 * @gl: The glock in question
 *
 * Glocks are not frozen अगर (a) the result of the dlm operation is
 * an error, (b) the locking operation was an unlock operation or
 * (c) अगर there is a "noexp" flagged request anywhere in the queue
 *
 * Returns: 1 अगर मुक्तzing should occur, 0 otherwise
 */

अटल पूर्णांक gfs2_should_मुक्तze(स्थिर काष्ठा gfs2_glock *gl)
अणु
	स्थिर काष्ठा gfs2_holder *gh;

	अगर (gl->gl_reply & ~LM_OUT_ST_MASK)
		वापस 0;
	अगर (gl->gl_target == LM_ST_UNLOCKED)
		वापस 0;

	list_क्रम_each_entry(gh, &gl->gl_holders, gh_list) अणु
		अगर (test_bit(HIF_HOLDER, &gh->gh_अगरlags))
			जारी;
		अगर (LM_FLAG_NOEXP & gh->gh_flags)
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/**
 * gfs2_glock_complete - Callback used by locking
 * @gl: Poपूर्णांकer to the glock
 * @ret: The वापस value from the dlm
 *
 * The gl_reply field is under the gl_lockref.lock lock so that it is ok
 * to use a bitfield shared with other glock state fields.
 */

व्योम gfs2_glock_complete(काष्ठा gfs2_glock *gl, पूर्णांक ret)
अणु
	काष्ठा lm_lockकाष्ठा *ls = &gl->gl_name.ln_sbd->sd_lockकाष्ठा;

	spin_lock(&gl->gl_lockref.lock);
	gl->gl_reply = ret;

	अगर (unlikely(test_bit(DFL_BLOCK_LOCKS, &ls->ls_recover_flags))) अणु
		अगर (gfs2_should_मुक्तze(gl)) अणु
			set_bit(GLF_FROZEN, &gl->gl_flags);
			spin_unlock(&gl->gl_lockref.lock);
			वापस;
		पूर्ण
	पूर्ण

	gl->gl_lockref.count++;
	set_bit(GLF_REPLY_PENDING, &gl->gl_flags);
	__gfs2_glock_queue_work(gl, 0);
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

अटल पूर्णांक glock_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
		     स्थिर काष्ठा list_head *b)
अणु
	काष्ठा gfs2_glock *gla, *glb;

	gla = list_entry(a, काष्ठा gfs2_glock, gl_lru);
	glb = list_entry(b, काष्ठा gfs2_glock, gl_lru);

	अगर (gla->gl_name.ln_number > glb->gl_name.ln_number)
		वापस 1;
	अगर (gla->gl_name.ln_number < glb->gl_name.ln_number)
		वापस -1;

	वापस 0;
पूर्ण

/**
 * gfs2_dispose_glock_lru - Demote a list of glocks
 * @list: The list to dispose of
 *
 * Disposing of glocks may involve disk accesses, so that here we sort
 * the glocks by number (i.e. disk location of the inodes) so that अगर
 * there are any such accesses, they'll be sent in order (mostly).
 *
 * Must be called under the lru_lock, but may drop and retake this
 * lock. While the lru_lock is dropped, entries may vanish from the
 * list, but no new entries will appear on the list (since it is
 * निजी)
 */

अटल व्योम gfs2_dispose_glock_lru(काष्ठा list_head *list)
__releases(&lru_lock)
__acquires(&lru_lock)
अणु
	काष्ठा gfs2_glock *gl;

	list_sort(शून्य, list, glock_cmp);

	जबतक(!list_empty(list)) अणु
		gl = list_first_entry(list, काष्ठा gfs2_glock, gl_lru);
		list_del_init(&gl->gl_lru);
		clear_bit(GLF_LRU, &gl->gl_flags);
		अगर (!spin_trylock(&gl->gl_lockref.lock)) अणु
add_back_to_lru:
			list_add(&gl->gl_lru, &lru_list);
			set_bit(GLF_LRU, &gl->gl_flags);
			atomic_inc(&lru_count);
			जारी;
		पूर्ण
		अगर (test_and_set_bit(GLF_LOCK, &gl->gl_flags)) अणु
			spin_unlock(&gl->gl_lockref.lock);
			जाओ add_back_to_lru;
		पूर्ण
		gl->gl_lockref.count++;
		अगर (demote_ok(gl))
			handle_callback(gl, LM_ST_UNLOCKED, 0, false);
		WARN_ON(!test_and_clear_bit(GLF_LOCK, &gl->gl_flags));
		__gfs2_glock_queue_work(gl, 0);
		spin_unlock(&gl->gl_lockref.lock);
		cond_resched_lock(&lru_lock);
	पूर्ण
पूर्ण

/**
 * gfs2_scan_glock_lru - Scan the LRU looking क्रम locks to demote
 * @nr: The number of entries to scan
 *
 * This function selects the entries on the LRU which are able to
 * be demoted, and then kicks off the process by calling
 * gfs2_dispose_glock_lru() above.
 */

अटल दीर्घ gfs2_scan_glock_lru(पूर्णांक nr)
अणु
	काष्ठा gfs2_glock *gl;
	LIST_HEAD(skipped);
	LIST_HEAD(dispose);
	दीर्घ मुक्तd = 0;

	spin_lock(&lru_lock);
	जबतक ((nr-- >= 0) && !list_empty(&lru_list)) अणु
		gl = list_first_entry(&lru_list, काष्ठा gfs2_glock, gl_lru);

		/* Test क्रम being demotable */
		अगर (!test_bit(GLF_LOCK, &gl->gl_flags)) अणु
			list_move(&gl->gl_lru, &dispose);
			atomic_dec(&lru_count);
			मुक्तd++;
			जारी;
		पूर्ण

		list_move(&gl->gl_lru, &skipped);
	पूर्ण
	list_splice(&skipped, &lru_list);
	अगर (!list_empty(&dispose))
		gfs2_dispose_glock_lru(&dispose);
	spin_unlock(&lru_lock);

	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ gfs2_glock_shrink_scan(काष्ठा shrinker *shrink,
					    काष्ठा shrink_control *sc)
अणु
	अगर (!(sc->gfp_mask & __GFP_FS))
		वापस SHRINK_STOP;
	वापस gfs2_scan_glock_lru(sc->nr_to_scan);
पूर्ण

अटल अचिन्हित दीर्घ gfs2_glock_shrink_count(काष्ठा shrinker *shrink,
					     काष्ठा shrink_control *sc)
अणु
	वापस vfs_pressure_ratio(atomic_पढ़ो(&lru_count));
पूर्ण

अटल काष्ठा shrinker glock_shrinker = अणु
	.seeks = DEFAULT_SEEKS,
	.count_objects = gfs2_glock_shrink_count,
	.scan_objects = gfs2_glock_shrink_scan,
पूर्ण;

/**
 * glock_hash_walk - Call a function क्रम glock in a hash bucket
 * @examiner: the function
 * @sdp: the fileप्रणाली
 *
 * Note that the function can be called multiple बार on the same
 * object.  So the user must ensure that the function can cope with
 * that.
 */

अटल व्योम glock_hash_walk(glock_examiner examiner, स्थिर काष्ठा gfs2_sbd *sdp)
अणु
	काष्ठा gfs2_glock *gl;
	काष्ठा rhashtable_iter iter;

	rhashtable_walk_enter(&gl_hash_table, &iter);

	करो अणु
		rhashtable_walk_start(&iter);

		जबतक ((gl = rhashtable_walk_next(&iter)) && !IS_ERR(gl))
			अगर (gl->gl_name.ln_sbd == sdp &&
			    lockref_get_not_dead(&gl->gl_lockref))
				examiner(gl);

		rhashtable_walk_stop(&iter);
	पूर्ण जबतक (cond_resched(), gl == ERR_PTR(-EAGAIN));

	rhashtable_walk_निकास(&iter);
पूर्ण

bool gfs2_queue_delete_work(काष्ठा gfs2_glock *gl, अचिन्हित दीर्घ delay)
अणु
	bool queued;

	spin_lock(&gl->gl_lockref.lock);
	queued = queue_delayed_work(gfs2_delete_workqueue,
				    &gl->gl_delete, delay);
	अगर (queued)
		set_bit(GLF_PENDING_DELETE, &gl->gl_flags);
	spin_unlock(&gl->gl_lockref.lock);
	वापस queued;
पूर्ण

व्योम gfs2_cancel_delete_work(काष्ठा gfs2_glock *gl)
अणु
	अगर (cancel_delayed_work_sync(&gl->gl_delete)) अणु
		clear_bit(GLF_PENDING_DELETE, &gl->gl_flags);
		gfs2_glock_put(gl);
	पूर्ण
पूर्ण

bool gfs2_delete_work_queued(स्थिर काष्ठा gfs2_glock *gl)
अणु
	वापस test_bit(GLF_PENDING_DELETE, &gl->gl_flags);
पूर्ण

अटल व्योम flush_delete_work(काष्ठा gfs2_glock *gl)
अणु
	अगर (gl->gl_name.ln_type == LM_TYPE_IOPEN) अणु
		अगर (cancel_delayed_work(&gl->gl_delete)) अणु
			queue_delayed_work(gfs2_delete_workqueue,
					   &gl->gl_delete, 0);
		पूर्ण
	पूर्ण
	gfs2_glock_queue_work(gl, 0);
पूर्ण

व्योम gfs2_flush_delete_work(काष्ठा gfs2_sbd *sdp)
अणु
	glock_hash_walk(flush_delete_work, sdp);
	flush_workqueue(gfs2_delete_workqueue);
पूर्ण

/**
 * thaw_glock - thaw out a glock which has an unprocessed reply रुकोing
 * @gl: The glock to thaw
 *
 */

अटल व्योम thaw_glock(काष्ठा gfs2_glock *gl)
अणु
	अगर (!test_and_clear_bit(GLF_FROZEN, &gl->gl_flags)) अणु
		gfs2_glock_put(gl);
		वापस;
	पूर्ण
	set_bit(GLF_REPLY_PENDING, &gl->gl_flags);
	gfs2_glock_queue_work(gl, 0);
पूर्ण

/**
 * clear_glock - look at a glock and see अगर we can मुक्त it from glock cache
 * @gl: the glock to look at
 *
 */

अटल व्योम clear_glock(काष्ठा gfs2_glock *gl)
अणु
	gfs2_glock_हटाओ_from_lru(gl);

	spin_lock(&gl->gl_lockref.lock);
	अगर (gl->gl_state != LM_ST_UNLOCKED)
		handle_callback(gl, LM_ST_UNLOCKED, 0, false);
	__gfs2_glock_queue_work(gl, 0);
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

/**
 * gfs2_glock_thaw - Thaw any frozen glocks
 * @sdp: The super block
 *
 */

व्योम gfs2_glock_thaw(काष्ठा gfs2_sbd *sdp)
अणु
	glock_hash_walk(thaw_glock, sdp);
पूर्ण

अटल व्योम dump_glock(काष्ठा seq_file *seq, काष्ठा gfs2_glock *gl, bool fsid)
अणु
	spin_lock(&gl->gl_lockref.lock);
	gfs2_dump_glock(seq, gl, fsid);
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

अटल व्योम dump_glock_func(काष्ठा gfs2_glock *gl)
अणु
	dump_glock(शून्य, gl, true);
पूर्ण

/**
 * gfs2_gl_hash_clear - Empty out the glock hash table
 * @sdp: the fileप्रणाली
 *
 * Called when unmounting the fileप्रणाली.
 */

व्योम gfs2_gl_hash_clear(काष्ठा gfs2_sbd *sdp)
अणु
	set_bit(SDF_SKIP_DLM_UNLOCK, &sdp->sd_flags);
	flush_workqueue(glock_workqueue);
	glock_hash_walk(clear_glock, sdp);
	flush_workqueue(glock_workqueue);
	रुको_event_समयout(sdp->sd_glock_रुको,
			   atomic_पढ़ो(&sdp->sd_glock_disposal) == 0,
			   HZ * 600);
	glock_hash_walk(dump_glock_func, sdp);
पूर्ण

व्योम gfs2_glock_finish_truncate(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_glock *gl = ip->i_gl;
	पूर्णांक ret;

	ret = gfs2_truncatei_resume(ip);
	gfs2_glock_निश्चित_withdraw(gl, ret == 0);

	spin_lock(&gl->gl_lockref.lock);
	clear_bit(GLF_LOCK, &gl->gl_flags);
	run_queue(gl, 1);
	spin_unlock(&gl->gl_lockref.lock);
पूर्ण

अटल स्थिर अक्षर *state2str(अचिन्हित state)
अणु
	चयन(state) अणु
	हाल LM_ST_UNLOCKED:
		वापस "UN";
	हाल LM_ST_SHARED:
		वापस "SH";
	हाल LM_ST_DEFERRED:
		वापस "DF";
	हाल LM_ST_EXCLUSIVE:
		वापस "EX";
	पूर्ण
	वापस "??";
पूर्ण

अटल स्थिर अक्षर *hflags2str(अक्षर *buf, u16 flags, अचिन्हित दीर्घ अगरlags)
अणु
	अक्षर *p = buf;
	अगर (flags & LM_FLAG_TRY)
		*p++ = 't';
	अगर (flags & LM_FLAG_TRY_1CB)
		*p++ = 'T';
	अगर (flags & LM_FLAG_NOEXP)
		*p++ = 'e';
	अगर (flags & LM_FLAG_ANY)
		*p++ = 'A';
	अगर (flags & LM_FLAG_PRIORITY)
		*p++ = 'p';
	अगर (flags & LM_FLAG_NODE_SCOPE)
		*p++ = 'n';
	अगर (flags & GL_ASYNC)
		*p++ = 'a';
	अगर (flags & GL_EXACT)
		*p++ = 'E';
	अगर (flags & GL_NOCACHE)
		*p++ = 'c';
	अगर (test_bit(HIF_HOLDER, &अगरlags))
		*p++ = 'H';
	अगर (test_bit(HIF_WAIT, &अगरlags))
		*p++ = 'W';
	अगर (test_bit(HIF_FIRST, &अगरlags))
		*p++ = 'F';
	*p = 0;
	वापस buf;
पूर्ण

/**
 * dump_holder - prपूर्णांक inक्रमmation about a glock holder
 * @seq: the seq_file काष्ठा
 * @gh: the glock holder
 * @fs_id_buf: poपूर्णांकer to file प्रणाली id (अगर requested)
 *
 */

अटल व्योम dump_holder(काष्ठा seq_file *seq, स्थिर काष्ठा gfs2_holder *gh,
			स्थिर अक्षर *fs_id_buf)
अणु
	काष्ठा task_काष्ठा *gh_owner = शून्य;
	अक्षर flags_buf[32];

	rcu_पढ़ो_lock();
	अगर (gh->gh_owner_pid)
		gh_owner = pid_task(gh->gh_owner_pid, PIDTYPE_PID);
	gfs2_prपूर्णांक_dbg(seq, "%s H: s:%s f:%s e:%d p:%ld [%s] %pS\n",
		       fs_id_buf, state2str(gh->gh_state),
		       hflags2str(flags_buf, gh->gh_flags, gh->gh_अगरlags),
		       gh->gh_error,
		       gh->gh_owner_pid ? (दीर्घ)pid_nr(gh->gh_owner_pid) : -1,
		       gh_owner ? gh_owner->comm : "(ended)",
		       (व्योम *)gh->gh_ip);
	rcu_पढ़ो_unlock();
पूर्ण

अटल स्थिर अक्षर *gflags2str(अक्षर *buf, स्थिर काष्ठा gfs2_glock *gl)
अणु
	स्थिर अचिन्हित दीर्घ *gflags = &gl->gl_flags;
	अक्षर *p = buf;

	अगर (test_bit(GLF_LOCK, gflags))
		*p++ = 'l';
	अगर (test_bit(GLF_DEMOTE, gflags))
		*p++ = 'D';
	अगर (test_bit(GLF_PENDING_DEMOTE, gflags))
		*p++ = 'd';
	अगर (test_bit(GLF_DEMOTE_IN_PROGRESS, gflags))
		*p++ = 'p';
	अगर (test_bit(GLF_सूचीTY, gflags))
		*p++ = 'y';
	अगर (test_bit(GLF_LFLUSH, gflags))
		*p++ = 'f';
	अगर (test_bit(GLF_INVALIDATE_IN_PROGRESS, gflags))
		*p++ = 'i';
	अगर (test_bit(GLF_REPLY_PENDING, gflags))
		*p++ = 'r';
	अगर (test_bit(GLF_INITIAL, gflags))
		*p++ = 'I';
	अगर (test_bit(GLF_FROZEN, gflags))
		*p++ = 'F';
	अगर (!list_empty(&gl->gl_holders))
		*p++ = 'q';
	अगर (test_bit(GLF_LRU, gflags))
		*p++ = 'L';
	अगर (gl->gl_object)
		*p++ = 'o';
	अगर (test_bit(GLF_BLOCKING, gflags))
		*p++ = 'b';
	अगर (test_bit(GLF_PENDING_DELETE, gflags))
		*p++ = 'P';
	अगर (test_bit(GLF_FREEING, gflags))
		*p++ = 'x';
	*p = 0;
	वापस buf;
पूर्ण

/**
 * gfs2_dump_glock - prपूर्णांक inक्रमmation about a glock
 * @seq: The seq_file काष्ठा
 * @gl: the glock
 * @fsid: If true, also dump the file प्रणाली id
 *
 * The file क्रमmat is as follows:
 * One line per object, capital letters are used to indicate objects
 * G = glock, I = Inode, R = rgrp, H = holder. Glocks are not indented,
 * other objects are indented by a single space and follow the glock to
 * which they are related. Fields are indicated by lower हाल letters
 * followed by a colon and the field value, except क्रम strings which are in
 * [] so that its possible to see अगर they are composed of spaces क्रम
 * example. The field's are n = number (id of the object), f = flags,
 * t = type, s = state, r = refcount, e = error, p = pid.
 *
 */

व्योम gfs2_dump_glock(काष्ठा seq_file *seq, काष्ठा gfs2_glock *gl, bool fsid)
अणु
	स्थिर काष्ठा gfs2_glock_operations *glops = gl->gl_ops;
	अचिन्हित दीर्घ दीर्घ dसमय;
	स्थिर काष्ठा gfs2_holder *gh;
	अक्षर gflags_buf[32];
	काष्ठा gfs2_sbd *sdp = gl->gl_name.ln_sbd;
	अक्षर fs_id_buf[माप(sdp->sd_fsname) + 7];
	अचिन्हित दीर्घ nrpages = 0;

	अगर (gl->gl_ops->go_flags & GLOF_ASPACE) अणु
		काष्ठा address_space *mapping = gfs2_glock2aspace(gl);

		nrpages = mapping->nrpages;
	पूर्ण
	स_रखो(fs_id_buf, 0, माप(fs_id_buf));
	अगर (fsid && sdp) /* safety precaution */
		प्र_लिखो(fs_id_buf, "fsid=%s: ", sdp->sd_fsname);
	dसमय = jअगरfies - gl->gl_demote_समय;
	dसमय *= 1000000/HZ; /* demote समय in uSec */
	अगर (!test_bit(GLF_DEMOTE, &gl->gl_flags))
		dसमय = 0;
	gfs2_prपूर्णांक_dbg(seq, "%sG:  s:%s n:%u/%llx f:%s t:%s d:%s/%llu a:%d "
		       "v:%d r:%d m:%ld p:%lu\n",
		       fs_id_buf, state2str(gl->gl_state),
		       gl->gl_name.ln_type,
		       (अचिन्हित दीर्घ दीर्घ)gl->gl_name.ln_number,
		       gflags2str(gflags_buf, gl),
		       state2str(gl->gl_target),
		       state2str(gl->gl_demote_state), dसमय,
		       atomic_पढ़ो(&gl->gl_ail_count),
		       atomic_पढ़ो(&gl->gl_revokes),
		       (पूर्णांक)gl->gl_lockref.count, gl->gl_hold_समय, nrpages);

	list_क्रम_each_entry(gh, &gl->gl_holders, gh_list)
		dump_holder(seq, gh, fs_id_buf);

	अगर (gl->gl_state != LM_ST_UNLOCKED && glops->go_dump)
		glops->go_dump(seq, gl, fs_id_buf);
पूर्ण

अटल पूर्णांक gfs2_glstats_seq_show(काष्ठा seq_file *seq, व्योम *iter_ptr)
अणु
	काष्ठा gfs2_glock *gl = iter_ptr;

	seq_म_लिखो(seq, "G: n:%u/%llx rtt:%llu/%llu rttb:%llu/%llu irt:%llu/%llu dcnt: %llu qcnt: %llu\n",
		   gl->gl_name.ln_type,
		   (अचिन्हित दीर्घ दीर्घ)gl->gl_name.ln_number,
		   (अचिन्हित दीर्घ दीर्घ)gl->gl_stats.stats[GFS2_LKS_SRTT],
		   (अचिन्हित दीर्घ दीर्घ)gl->gl_stats.stats[GFS2_LKS_SRTTVAR],
		   (अचिन्हित दीर्घ दीर्घ)gl->gl_stats.stats[GFS2_LKS_SRTTB],
		   (अचिन्हित दीर्घ दीर्घ)gl->gl_stats.stats[GFS2_LKS_SRTTVARB],
		   (अचिन्हित दीर्घ दीर्घ)gl->gl_stats.stats[GFS2_LKS_SIRT],
		   (अचिन्हित दीर्घ दीर्घ)gl->gl_stats.stats[GFS2_LKS_SIRTVAR],
		   (अचिन्हित दीर्घ दीर्घ)gl->gl_stats.stats[GFS2_LKS_DCOUNT],
		   (अचिन्हित दीर्घ दीर्घ)gl->gl_stats.stats[GFS2_LKS_QCOUNT]);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *gfs2_gltype[] = अणु
	"type",
	"reserved",
	"nondisk",
	"inode",
	"rgrp",
	"meta",
	"iopen",
	"flock",
	"plock",
	"quota",
	"journal",
पूर्ण;

अटल स्थिर अक्षर *gfs2_stype[] = अणु
	[GFS2_LKS_SRTT]		= "srtt",
	[GFS2_LKS_SRTTVAR]	= "srttvar",
	[GFS2_LKS_SRTTB]	= "srttb",
	[GFS2_LKS_SRTTVARB]	= "srttvarb",
	[GFS2_LKS_SIRT]		= "sirt",
	[GFS2_LKS_SIRTVAR]	= "sirtvar",
	[GFS2_LKS_DCOUNT]	= "dlm",
	[GFS2_LKS_QCOUNT]	= "queue",
पूर्ण;

#घोषणा GFS2_NR_SBSTATS (ARRAY_SIZE(gfs2_gltype) * ARRAY_SIZE(gfs2_stype))

अटल पूर्णांक gfs2_sbstats_seq_show(काष्ठा seq_file *seq, व्योम *iter_ptr)
अणु
	काष्ठा gfs2_sbd *sdp = seq->निजी;
	loff_t pos = *(loff_t *)iter_ptr;
	अचिन्हित index = pos >> 3;
	अचिन्हित subindex = pos & 0x07;
	पूर्णांक i;

	अगर (index == 0 && subindex != 0)
		वापस 0;

	seq_म_लिखो(seq, "%-10s %8s:", gfs2_gltype[index],
		   (index == 0) ? "cpu": gfs2_stype[subindex]);

	क्रम_each_possible_cpu(i) अणु
                स्थिर काष्ठा gfs2_pcpu_lkstats *lkstats = per_cpu_ptr(sdp->sd_lkstats, i);

		अगर (index == 0)
			seq_म_लिखो(seq, " %15u", i);
		अन्यथा
			seq_म_लिखो(seq, " %15llu", (अचिन्हित दीर्घ दीर्घ)lkstats->
				   lkstats[index - 1].stats[subindex]);
	पूर्ण
	seq_अ_दो(seq, '\n');
	वापस 0;
पूर्ण

पूर्णांक __init gfs2_glock_init(व्योम)
अणु
	पूर्णांक i, ret;

	ret = rhashtable_init(&gl_hash_table, &ht_parms);
	अगर (ret < 0)
		वापस ret;

	glock_workqueue = alloc_workqueue("glock_workqueue", WQ_MEM_RECLAIM |
					  WQ_HIGHPRI | WQ_FREEZABLE, 0);
	अगर (!glock_workqueue) अणु
		rhashtable_destroy(&gl_hash_table);
		वापस -ENOMEM;
	पूर्ण
	gfs2_delete_workqueue = alloc_workqueue("delete_workqueue",
						WQ_MEM_RECLAIM | WQ_FREEZABLE,
						0);
	अगर (!gfs2_delete_workqueue) अणु
		destroy_workqueue(glock_workqueue);
		rhashtable_destroy(&gl_hash_table);
		वापस -ENOMEM;
	पूर्ण

	ret = रेजिस्टर_shrinker(&glock_shrinker);
	अगर (ret) अणु
		destroy_workqueue(gfs2_delete_workqueue);
		destroy_workqueue(glock_workqueue);
		rhashtable_destroy(&gl_hash_table);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < GLOCK_WAIT_TABLE_SIZE; i++)
		init_रुकोqueue_head(glock_रुको_table + i);

	वापस 0;
पूर्ण

व्योम gfs2_glock_निकास(व्योम)
अणु
	unरेजिस्टर_shrinker(&glock_shrinker);
	rhashtable_destroy(&gl_hash_table);
	destroy_workqueue(glock_workqueue);
	destroy_workqueue(gfs2_delete_workqueue);
पूर्ण

अटल व्योम gfs2_glock_iter_next(काष्ठा gfs2_glock_iter *gi, loff_t n)
अणु
	काष्ठा gfs2_glock *gl = gi->gl;

	अगर (gl) अणु
		अगर (n == 0)
			वापस;
		अगर (!lockref_put_not_zero(&gl->gl_lockref))
			gfs2_glock_queue_put(gl);
	पूर्ण
	क्रम (;;) अणु
		gl = rhashtable_walk_next(&gi->hti);
		अगर (IS_ERR_OR_शून्य(gl)) अणु
			अगर (gl == ERR_PTR(-EAGAIN)) अणु
				n = 1;
				जारी;
			पूर्ण
			gl = शून्य;
			अवरोध;
		पूर्ण
		अगर (gl->gl_name.ln_sbd != gi->sdp)
			जारी;
		अगर (n <= 1) अणु
			अगर (!lockref_get_not_dead(&gl->gl_lockref))
				जारी;
			अवरोध;
		पूर्ण अन्यथा अणु
			अगर (__lockref_is_dead(&gl->gl_lockref))
				जारी;
			n--;
		पूर्ण
	पूर्ण
	gi->gl = gl;
पूर्ण

अटल व्योम *gfs2_glock_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा gfs2_glock_iter *gi = seq->निजी;
	loff_t n;

	/*
	 * We can either stay where we are, skip to the next hash table
	 * entry, or start from the beginning.
	 */
	अगर (*pos < gi->last_pos) अणु
		rhashtable_walk_निकास(&gi->hti);
		rhashtable_walk_enter(&gl_hash_table, &gi->hti);
		n = *pos + 1;
	पूर्ण अन्यथा अणु
		n = *pos - gi->last_pos;
	पूर्ण

	rhashtable_walk_start(&gi->hti);

	gfs2_glock_iter_next(gi, n);
	gi->last_pos = *pos;
	वापस gi->gl;
पूर्ण

अटल व्योम *gfs2_glock_seq_next(काष्ठा seq_file *seq, व्योम *iter_ptr,
				 loff_t *pos)
अणु
	काष्ठा gfs2_glock_iter *gi = seq->निजी;

	(*pos)++;
	gi->last_pos = *pos;
	gfs2_glock_iter_next(gi, 1);
	वापस gi->gl;
पूर्ण

अटल व्योम gfs2_glock_seq_stop(काष्ठा seq_file *seq, व्योम *iter_ptr)
	__releases(RCU)
अणु
	काष्ठा gfs2_glock_iter *gi = seq->निजी;

	rhashtable_walk_stop(&gi->hti);
पूर्ण

अटल पूर्णांक gfs2_glock_seq_show(काष्ठा seq_file *seq, व्योम *iter_ptr)
अणु
	dump_glock(seq, iter_ptr, false);
	वापस 0;
पूर्ण

अटल व्योम *gfs2_sbstats_seq_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	preempt_disable();
	अगर (*pos >= GFS2_NR_SBSTATS)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *gfs2_sbstats_seq_next(काष्ठा seq_file *seq, व्योम *iter_ptr,
				   loff_t *pos)
अणु
	(*pos)++;
	अगर (*pos >= GFS2_NR_SBSTATS)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम gfs2_sbstats_seq_stop(काष्ठा seq_file *seq, व्योम *iter_ptr)
अणु
	preempt_enable();
पूर्ण

अटल स्थिर काष्ठा seq_operations gfs2_glock_seq_ops = अणु
	.start = gfs2_glock_seq_start,
	.next  = gfs2_glock_seq_next,
	.stop  = gfs2_glock_seq_stop,
	.show  = gfs2_glock_seq_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations gfs2_glstats_seq_ops = अणु
	.start = gfs2_glock_seq_start,
	.next  = gfs2_glock_seq_next,
	.stop  = gfs2_glock_seq_stop,
	.show  = gfs2_glstats_seq_show,
पूर्ण;

अटल स्थिर काष्ठा seq_operations gfs2_sbstats_sops = अणु
	.start = gfs2_sbstats_seq_start,
	.next  = gfs2_sbstats_seq_next,
	.stop  = gfs2_sbstats_seq_stop,
	.show  = gfs2_sbstats_seq_show,
पूर्ण;

#घोषणा GFS2_SEQ_GOODSIZE min(PAGE_SIZE << PAGE_ALLOC_COSTLY_ORDER, 65536UL)

अटल पूर्णांक __gfs2_glocks_खोलो(काष्ठा inode *inode, काष्ठा file *file,
			      स्थिर काष्ठा seq_operations *ops)
अणु
	पूर्णांक ret = seq_खोलो_निजी(file, ops, माप(काष्ठा gfs2_glock_iter));
	अगर (ret == 0) अणु
		काष्ठा seq_file *seq = file->निजी_data;
		काष्ठा gfs2_glock_iter *gi = seq->निजी;

		gi->sdp = inode->i_निजी;
		seq->buf = kदो_स्मृति(GFS2_SEQ_GOODSIZE, GFP_KERNEL | __GFP_NOWARN);
		अगर (seq->buf)
			seq->size = GFS2_SEQ_GOODSIZE;
		/*
		 * Initially, we are "before" the first hash table entry; the
		 * first call to rhashtable_walk_next माला_लो us the first entry.
		 */
		gi->last_pos = -1;
		gi->gl = शून्य;
		rhashtable_walk_enter(&gl_hash_table, &gi->hti);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gfs2_glocks_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस __gfs2_glocks_खोलो(inode, file, &gfs2_glock_seq_ops);
पूर्ण

अटल पूर्णांक gfs2_glocks_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = file->निजी_data;
	काष्ठा gfs2_glock_iter *gi = seq->निजी;

	अगर (gi->gl)
		gfs2_glock_put(gi->gl);
	rhashtable_walk_निकास(&gi->hti);
	वापस seq_release_निजी(inode, file);
पूर्ण

अटल पूर्णांक gfs2_glstats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस __gfs2_glocks_खोलो(inode, file, &gfs2_glstats_seq_ops);
पूर्ण

अटल स्थिर काष्ठा file_operations gfs2_glocks_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = gfs2_glocks_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = gfs2_glocks_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations gfs2_glstats_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = gfs2_glstats_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = gfs2_glocks_release,
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(gfs2_sbstats);

व्योम gfs2_create_debugfs_file(काष्ठा gfs2_sbd *sdp)
अणु
	sdp->debugfs_dir = debugfs_create_dir(sdp->sd_table_name, gfs2_root);

	debugfs_create_file("glocks", S_IFREG | S_IRUGO, sdp->debugfs_dir, sdp,
			    &gfs2_glocks_fops);

	debugfs_create_file("glstats", S_IFREG | S_IRUGO, sdp->debugfs_dir, sdp,
			    &gfs2_glstats_fops);

	debugfs_create_file("sbstats", S_IFREG | S_IRUGO, sdp->debugfs_dir, sdp,
			    &gfs2_sbstats_fops);
पूर्ण

व्योम gfs2_delete_debugfs_file(काष्ठा gfs2_sbd *sdp)
अणु
	debugfs_हटाओ_recursive(sdp->debugfs_dir);
	sdp->debugfs_dir = शून्य;
पूर्ण

व्योम gfs2_रेजिस्टर_debugfs(व्योम)
अणु
	gfs2_root = debugfs_create_dir("gfs2", शून्य);
पूर्ण

व्योम gfs2_unरेजिस्टर_debugfs(व्योम)
अणु
	debugfs_हटाओ(gfs2_root);
	gfs2_root = शून्य;
पूर्ण
