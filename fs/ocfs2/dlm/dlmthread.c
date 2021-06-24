<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmthपढ़ो.c
 *
 * standalone DLM module
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */


#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/socket.h>
#समावेश <linux/inet.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>


#समावेश "../cluster/heartbeat.h"
#समावेश "../cluster/nodemanager.h"
#समावेश "../cluster/tcp.h"

#समावेश "dlmapi.h"
#समावेश "dlmcommon.h"
#समावेश "dlmdomain.h"

#घोषणा MLOG_MASK_PREFIX (ML_DLM|ML_DLM_THREAD)
#समावेश "../cluster/masklog.h"

अटल पूर्णांक dlm_thपढ़ो(व्योम *data);
अटल व्योम dlm_flush_asts(काष्ठा dlm_ctxt *dlm);

/* will निकास holding res->spinlock, but may drop in function */
/* रुकोs until flags are cleared on res->state */
व्योम __dlm_रुको_on_lockres_flags(काष्ठा dlm_lock_resource *res, पूर्णांक flags)
अणु
	DECLARE_WAITQUEUE(रुको, current);

	निश्चित_spin_locked(&res->spinlock);

	add_रुको_queue(&res->wq, &रुको);
repeat:
	set_current_state(TASK_UNINTERRUPTIBLE);
	अगर (res->state & flags) अणु
		spin_unlock(&res->spinlock);
		schedule();
		spin_lock(&res->spinlock);
		जाओ repeat;
	पूर्ण
	हटाओ_रुको_queue(&res->wq, &रुको);
	__set_current_state(TASK_RUNNING);
पूर्ण

पूर्णांक __dlm_lockres_has_locks(काष्ठा dlm_lock_resource *res)
अणु
	अगर (list_empty(&res->granted) &&
	    list_empty(&res->converting) &&
	    list_empty(&res->blocked))
		वापस 0;
	वापस 1;
पूर्ण

/* "unused": the lockres has no locks, is not on the dirty list,
 * has no inflight locks (in the gap between mastery and acquiring
 * the first lock), and has no bits in its refmap.
 * truly पढ़ोy to be मुक्तd. */
पूर्णांक __dlm_lockres_unused(काष्ठा dlm_lock_resource *res)
अणु
	पूर्णांक bit;

	निश्चित_spin_locked(&res->spinlock);

	अगर (__dlm_lockres_has_locks(res))
		वापस 0;

	/* Locks are in the process of being created */
	अगर (res->inflight_locks)
		वापस 0;

	अगर (!list_empty(&res->dirty) || res->state & DLM_LOCK_RES_सूचीTY)
		वापस 0;

	अगर (res->state & (DLM_LOCK_RES_RECOVERING|
			DLM_LOCK_RES_RECOVERY_WAITING))
		वापस 0;

	/* Another node has this resource with this node as the master */
	bit = find_next_bit(res->refmap, O2NM_MAX_NODES, 0);
	अगर (bit < O2NM_MAX_NODES)
		वापस 0;

	वापस 1;
पूर्ण


/* Call whenever you may have added or deleted something from one of
 * the lockres queue's. This will figure out whether it beदीर्घs on the
 * unused list or not and करोes the appropriate thing. */
व्योम __dlm_lockres_calc_usage(काष्ठा dlm_ctxt *dlm,
			      काष्ठा dlm_lock_resource *res)
अणु
	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&res->spinlock);

	अगर (__dlm_lockres_unused(res))अणु
		अगर (list_empty(&res->purge)) अणु
			mlog(0, "%s: Adding res %.*s to purge list\n",
			     dlm->name, res->lockname.len, res->lockname.name);

			res->last_used = jअगरfies;
			dlm_lockres_get(res);
			list_add_tail(&res->purge, &dlm->purge_list);
			dlm->purge_count++;
		पूर्ण
	पूर्ण अन्यथा अगर (!list_empty(&res->purge)) अणु
		mlog(0, "%s: Removing res %.*s from purge list\n",
		     dlm->name, res->lockname.len, res->lockname.name);

		list_del_init(&res->purge);
		dlm_lockres_put(res);
		dlm->purge_count--;
	पूर्ण
पूर्ण

व्योम dlm_lockres_calc_usage(काष्ठा dlm_ctxt *dlm,
			    काष्ठा dlm_lock_resource *res)
अणु
	spin_lock(&dlm->spinlock);
	spin_lock(&res->spinlock);

	__dlm_lockres_calc_usage(dlm, res);

	spin_unlock(&res->spinlock);
	spin_unlock(&dlm->spinlock);
पूर्ण

/*
 * Do the real purge work:
 *     unhash the lockres, and
 *     clear flag DLM_LOCK_RES_DROPPING_REF.
 * It requires dlm and lockres spinlock to be taken.
 */
व्योम __dlm_करो_purge_lockres(काष्ठा dlm_ctxt *dlm,
		काष्ठा dlm_lock_resource *res)
अणु
	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&res->spinlock);

	अगर (!list_empty(&res->purge)) अणु
		mlog(0, "%s: Removing res %.*s from purgelist\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		list_del_init(&res->purge);
		dlm_lockres_put(res);
		dlm->purge_count--;
	पूर्ण

	अगर (!__dlm_lockres_unused(res)) अणु
		mlog(ML_ERROR, "%s: res %.*s in use after deref\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		__dlm_prपूर्णांक_one_lock_resource(res);
		BUG();
	पूर्ण

	__dlm_unhash_lockres(dlm, res);

	spin_lock(&dlm->track_lock);
	अगर (!list_empty(&res->tracking))
		list_del_init(&res->tracking);
	अन्यथा अणु
		mlog(ML_ERROR, "%s: Resource %.*s not on the Tracking list\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		__dlm_prपूर्णांक_one_lock_resource(res);
	पूर्ण
	spin_unlock(&dlm->track_lock);

	/*
	 * lockres is not in the hash now. drop the flag and wake up
	 * any processes रुकोing in dlm_get_lock_resource.
	 */
	res->state &= ~DLM_LOCK_RES_DROPPING_REF;
पूर्ण

अटल व्योम dlm_purge_lockres(काष्ठा dlm_ctxt *dlm,
			     काष्ठा dlm_lock_resource *res)
अणु
	पूर्णांक master;
	पूर्णांक ret = 0;

	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&res->spinlock);

	master = (res->owner == dlm->node_num);

	mlog(0, "%s: Purging res %.*s, master %d\n", dlm->name,
	     res->lockname.len, res->lockname.name, master);

	अगर (!master) अणु
		अगर (res->state & DLM_LOCK_RES_DROPPING_REF) अणु
			mlog(ML_NOTICE, "%s: res %.*s already in DLM_LOCK_RES_DROPPING_REF state\n",
				dlm->name, res->lockname.len, res->lockname.name);
			spin_unlock(&res->spinlock);
			वापस;
		पूर्ण

		res->state |= DLM_LOCK_RES_DROPPING_REF;
		/* drop spinlock...  retake below */
		spin_unlock(&res->spinlock);
		spin_unlock(&dlm->spinlock);

		spin_lock(&res->spinlock);
		/* This ensures that clear refmap is sent after the set */
		__dlm_रुको_on_lockres_flags(res, DLM_LOCK_RES_SETREF_INPROG);
		spin_unlock(&res->spinlock);

		/* clear our bit from the master's refmap, ignore errors */
		ret = dlm_drop_lockres_ref(dlm, res);
		अगर (ret < 0) अणु
			अगर (!dlm_is_host_करोwn(ret))
				BUG();
		पूर्ण
		spin_lock(&dlm->spinlock);
		spin_lock(&res->spinlock);
	पूर्ण

	अगर (!list_empty(&res->purge)) अणु
		mlog(0, "%s: Removing res %.*s from purgelist, master %d\n",
		     dlm->name, res->lockname.len, res->lockname.name, master);
		list_del_init(&res->purge);
		dlm_lockres_put(res);
		dlm->purge_count--;
	पूर्ण

	अगर (!master && ret == DLM_DEREF_RESPONSE_INPROG) अणु
		mlog(0, "%s: deref %.*s in progress\n",
			dlm->name, res->lockname.len, res->lockname.name);
		spin_unlock(&res->spinlock);
		वापस;
	पूर्ण

	अगर (!__dlm_lockres_unused(res)) अणु
		mlog(ML_ERROR, "%s: res %.*s in use after deref\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		__dlm_prपूर्णांक_one_lock_resource(res);
		BUG();
	पूर्ण

	__dlm_unhash_lockres(dlm, res);

	spin_lock(&dlm->track_lock);
	अगर (!list_empty(&res->tracking))
		list_del_init(&res->tracking);
	अन्यथा अणु
		mlog(ML_ERROR, "Resource %.*s not on the Tracking list\n",
				res->lockname.len, res->lockname.name);
		__dlm_prपूर्णांक_one_lock_resource(res);
	पूर्ण
	spin_unlock(&dlm->track_lock);

	/* lockres is not in the hash now.  drop the flag and wake up
	 * any processes रुकोing in dlm_get_lock_resource. */
	अगर (!master) अणु
		res->state &= ~DLM_LOCK_RES_DROPPING_REF;
		spin_unlock(&res->spinlock);
		wake_up(&res->wq);
	पूर्ण अन्यथा
		spin_unlock(&res->spinlock);
पूर्ण

अटल व्योम dlm_run_purge_list(काष्ठा dlm_ctxt *dlm,
			       पूर्णांक purge_now)
अणु
	अचिन्हित पूर्णांक run_max, unused;
	अचिन्हित दीर्घ purge_jअगरfies;
	काष्ठा dlm_lock_resource *lockres;

	spin_lock(&dlm->spinlock);
	run_max = dlm->purge_count;

	जबतक(run_max && !list_empty(&dlm->purge_list)) अणु
		run_max--;

		lockres = list_entry(dlm->purge_list.next,
				     काष्ठा dlm_lock_resource, purge);

		spin_lock(&lockres->spinlock);

		purge_jअगरfies = lockres->last_used +
			msecs_to_jअगरfies(DLM_PURGE_INTERVAL_MS);

		/* Make sure that we want to be processing this guy at
		 * this समय. */
		अगर (!purge_now && समय_after(purge_jअगरfies, jअगरfies)) अणु
			/* Since resources are added to the purge list
			 * in tail order, we can stop at the first
			 * unpurgable resource -- anyone added after
			 * him will have a greater last_used value */
			spin_unlock(&lockres->spinlock);
			अवरोध;
		पूर्ण

		/* Status of the lockres *might* change so द्विगुन
		 * check. If the lockres is unused, holding the dlm
		 * spinlock will prevent people from getting and more
		 * refs on it. */
		unused = __dlm_lockres_unused(lockres);
		अगर (!unused ||
		    (lockres->state & DLM_LOCK_RES_MIGRATING) ||
		    (lockres->inflight_निश्चित_workers != 0)) अणु
			mlog(0, "%s: res %.*s is in use or being remastered, "
			     "used %d, state %d, assert master workers %u\n",
			     dlm->name, lockres->lockname.len,
			     lockres->lockname.name,
			     !unused, lockres->state,
			     lockres->inflight_निश्चित_workers);
			list_move_tail(&lockres->purge, &dlm->purge_list);
			spin_unlock(&lockres->spinlock);
			जारी;
		पूर्ण

		dlm_lockres_get(lockres);

		dlm_purge_lockres(dlm, lockres);

		dlm_lockres_put(lockres);

		/* Aव्योम adding any scheduling latencies */
		cond_resched_lock(&dlm->spinlock);
	पूर्ण

	spin_unlock(&dlm->spinlock);
पूर्ण

अटल व्योम dlm_shuffle_lists(काष्ठा dlm_ctxt *dlm,
			      काष्ठा dlm_lock_resource *res)
अणु
	काष्ठा dlm_lock *lock, *target;
	पूर्णांक can_grant = 1;

	/*
	 * Because this function is called with the lockres
	 * spinlock, and because we know that it is not migrating/
	 * recovering/in-progress, it is fine to reserve asts and
	 * basts right beक्रमe queueing them all throughout
	 */
	निश्चित_spin_locked(&dlm->ast_lock);
	निश्चित_spin_locked(&res->spinlock);
	BUG_ON((res->state & (DLM_LOCK_RES_MIGRATING|
			      DLM_LOCK_RES_RECOVERING|
			      DLM_LOCK_RES_IN_PROGRESS)));

converting:
	अगर (list_empty(&res->converting))
		जाओ blocked;
	mlog(0, "%s: res %.*s has locks on the convert queue\n", dlm->name,
	     res->lockname.len, res->lockname.name);

	target = list_entry(res->converting.next, काष्ठा dlm_lock, list);
	अगर (target->ml.convert_type == LKM_IVMODE) अणु
		mlog(ML_ERROR, "%s: res %.*s converting lock to invalid mode\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		BUG();
	पूर्ण
	list_क्रम_each_entry(lock, &res->granted, list) अणु
		अगर (lock==target)
			जारी;
		अगर (!dlm_lock_compatible(lock->ml.type,
					 target->ml.convert_type)) अणु
			can_grant = 0;
			/* queue the BAST अगर not alपढ़ोy */
			अगर (lock->ml.highest_blocked == LKM_IVMODE) अणु
				__dlm_lockres_reserve_ast(res);
				__dlm_queue_bast(dlm, lock);
			पूर्ण
			/* update the highest_blocked अगर needed */
			अगर (lock->ml.highest_blocked < target->ml.convert_type)
				lock->ml.highest_blocked =
					target->ml.convert_type;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(lock, &res->converting, list) अणु
		अगर (lock==target)
			जारी;
		अगर (!dlm_lock_compatible(lock->ml.type,
					 target->ml.convert_type)) अणु
			can_grant = 0;
			अगर (lock->ml.highest_blocked == LKM_IVMODE) अणु
				__dlm_lockres_reserve_ast(res);
				__dlm_queue_bast(dlm, lock);
			पूर्ण
			अगर (lock->ml.highest_blocked < target->ml.convert_type)
				lock->ml.highest_blocked =
					target->ml.convert_type;
		पूर्ण
	पूर्ण

	/* we can convert the lock */
	अगर (can_grant) अणु
		spin_lock(&target->spinlock);
		BUG_ON(target->ml.highest_blocked != LKM_IVMODE);

		mlog(0, "%s: res %.*s, AST for Converting lock %u:%llu, type "
		     "%d => %d, node %u\n", dlm->name, res->lockname.len,
		     res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(target->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(target->ml.cookie)),
		     target->ml.type,
		     target->ml.convert_type, target->ml.node);

		target->ml.type = target->ml.convert_type;
		target->ml.convert_type = LKM_IVMODE;
		list_move_tail(&target->list, &res->granted);

		BUG_ON(!target->lksb);
		target->lksb->status = DLM_NORMAL;

		spin_unlock(&target->spinlock);

		__dlm_lockres_reserve_ast(res);
		__dlm_queue_ast(dlm, target);
		/* go back and check क्रम more */
		जाओ converting;
	पूर्ण

blocked:
	अगर (list_empty(&res->blocked))
		जाओ leave;
	target = list_entry(res->blocked.next, काष्ठा dlm_lock, list);

	list_क्रम_each_entry(lock, &res->granted, list) अणु
		अगर (lock==target)
			जारी;
		अगर (!dlm_lock_compatible(lock->ml.type, target->ml.type)) अणु
			can_grant = 0;
			अगर (lock->ml.highest_blocked == LKM_IVMODE) अणु
				__dlm_lockres_reserve_ast(res);
				__dlm_queue_bast(dlm, lock);
			पूर्ण
			अगर (lock->ml.highest_blocked < target->ml.type)
				lock->ml.highest_blocked = target->ml.type;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(lock, &res->converting, list) अणु
		अगर (lock==target)
			जारी;
		अगर (!dlm_lock_compatible(lock->ml.type, target->ml.type)) अणु
			can_grant = 0;
			अगर (lock->ml.highest_blocked == LKM_IVMODE) अणु
				__dlm_lockres_reserve_ast(res);
				__dlm_queue_bast(dlm, lock);
			पूर्ण
			अगर (lock->ml.highest_blocked < target->ml.type)
				lock->ml.highest_blocked = target->ml.type;
		पूर्ण
	पूर्ण

	/* we can grant the blocked lock (only
	 * possible अगर converting list empty) */
	अगर (can_grant) अणु
		spin_lock(&target->spinlock);
		BUG_ON(target->ml.highest_blocked != LKM_IVMODE);

		mlog(0, "%s: res %.*s, AST for Blocked lock %u:%llu, type %d, "
		     "node %u\n", dlm->name, res->lockname.len,
		     res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(target->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(target->ml.cookie)),
		     target->ml.type, target->ml.node);

		/* target->ml.type is alपढ़ोy correct */
		list_move_tail(&target->list, &res->granted);

		BUG_ON(!target->lksb);
		target->lksb->status = DLM_NORMAL;

		spin_unlock(&target->spinlock);

		__dlm_lockres_reserve_ast(res);
		__dlm_queue_ast(dlm, target);
		/* go back and check क्रम more */
		जाओ converting;
	पूर्ण

leave:
	वापस;
पूर्ण

/* must have NO locks when calling this with res !=शून्य * */
व्योम dlm_kick_thपढ़ो(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res)
अणु
	अगर (res) अणु
		spin_lock(&dlm->spinlock);
		spin_lock(&res->spinlock);
		__dlm_dirty_lockres(dlm, res);
		spin_unlock(&res->spinlock);
		spin_unlock(&dlm->spinlock);
	पूर्ण
	wake_up(&dlm->dlm_thपढ़ो_wq);
पूर्ण

व्योम __dlm_dirty_lockres(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res)
अणु
	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&res->spinlock);

	/* करोn't shuffle secondary queues */
	अगर (res->owner == dlm->node_num) अणु
		अगर (res->state & (DLM_LOCK_RES_MIGRATING |
				  DLM_LOCK_RES_BLOCK_सूचीTY))
		    वापस;

		अगर (list_empty(&res->dirty)) अणु
			/* ref क्रम dirty_list */
			dlm_lockres_get(res);
			list_add_tail(&res->dirty, &dlm->dirty_list);
			res->state |= DLM_LOCK_RES_सूचीTY;
		पूर्ण
	पूर्ण

	mlog(0, "%s: res %.*s\n", dlm->name, res->lockname.len,
	     res->lockname.name);
पूर्ण


/* Launch the NM thपढ़ो क्रम the mounted volume */
पूर्णांक dlm_launch_thपढ़ो(काष्ठा dlm_ctxt *dlm)
अणु
	mlog(0, "Starting dlm_thread...\n");

	dlm->dlm_thपढ़ो_task = kthपढ़ो_run(dlm_thपढ़ो, dlm, "dlm-%s",
			dlm->name);
	अगर (IS_ERR(dlm->dlm_thपढ़ो_task)) अणु
		mlog_त्रुटि_सं(PTR_ERR(dlm->dlm_thपढ़ो_task));
		dlm->dlm_thपढ़ो_task = शून्य;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dlm_complete_thपढ़ो(काष्ठा dlm_ctxt *dlm)
अणु
	अगर (dlm->dlm_thपढ़ो_task) अणु
		mlog(ML_KTHREAD, "Waiting for dlm thread to exit\n");
		kthपढ़ो_stop(dlm->dlm_thपढ़ो_task);
		dlm->dlm_thपढ़ो_task = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक dlm_dirty_list_empty(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक empty;

	spin_lock(&dlm->spinlock);
	empty = list_empty(&dlm->dirty_list);
	spin_unlock(&dlm->spinlock);

	वापस empty;
पूर्ण

अटल व्योम dlm_flush_asts(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक ret;
	काष्ठा dlm_lock *lock;
	काष्ठा dlm_lock_resource *res;
	u8 hi;

	spin_lock(&dlm->ast_lock);
	जबतक (!list_empty(&dlm->pending_asts)) अणु
		lock = list_entry(dlm->pending_asts.next,
				  काष्ठा dlm_lock, ast_list);
		/* get an extra ref on lock */
		dlm_lock_get(lock);
		res = lock->lockres;
		mlog(0, "%s: res %.*s, Flush AST for lock %u:%llu, type %d, "
		     "node %u\n", dlm->name, res->lockname.len,
		     res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		     lock->ml.type, lock->ml.node);

		BUG_ON(!lock->ast_pending);

		/* हटाओ from list (including ref) */
		list_del_init(&lock->ast_list);
		dlm_lock_put(lock);
		spin_unlock(&dlm->ast_lock);

		अगर (lock->ml.node != dlm->node_num) अणु
			ret = dlm_करो_remote_ast(dlm, res, lock);
			अगर (ret < 0)
				mlog_त्रुटि_सं(ret);
		पूर्ण अन्यथा
			dlm_करो_local_ast(dlm, res, lock);

		spin_lock(&dlm->ast_lock);

		/* possible that another ast was queued जबतक
		 * we were delivering the last one */
		अगर (!list_empty(&lock->ast_list)) अणु
			mlog(0, "%s: res %.*s, AST queued while flushing last "
			     "one\n", dlm->name, res->lockname.len,
			     res->lockname.name);
		पूर्ण अन्यथा
			lock->ast_pending = 0;

		/* drop the extra ref.
		 * this may drop it completely. */
		dlm_lock_put(lock);
		dlm_lockres_release_ast(dlm, res);
	पूर्ण

	जबतक (!list_empty(&dlm->pending_basts)) अणु
		lock = list_entry(dlm->pending_basts.next,
				  काष्ठा dlm_lock, bast_list);
		/* get an extra ref on lock */
		dlm_lock_get(lock);
		res = lock->lockres;

		BUG_ON(!lock->bast_pending);

		/* get the highest blocked lock, and reset */
		spin_lock(&lock->spinlock);
		BUG_ON(lock->ml.highest_blocked <= LKM_IVMODE);
		hi = lock->ml.highest_blocked;
		lock->ml.highest_blocked = LKM_IVMODE;
		spin_unlock(&lock->spinlock);

		/* हटाओ from list (including ref) */
		list_del_init(&lock->bast_list);
		dlm_lock_put(lock);
		spin_unlock(&dlm->ast_lock);

		mlog(0, "%s: res %.*s, Flush BAST for lock %u:%llu, "
		     "blocked %d, node %u\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		     hi, lock->ml.node);

		अगर (lock->ml.node != dlm->node_num) अणु
			ret = dlm_send_proxy_bast(dlm, res, lock, hi);
			अगर (ret < 0)
				mlog_त्रुटि_सं(ret);
		पूर्ण अन्यथा
			dlm_करो_local_bast(dlm, res, lock, hi);

		spin_lock(&dlm->ast_lock);

		/* possible that another bast was queued जबतक
		 * we were delivering the last one */
		अगर (!list_empty(&lock->bast_list)) अणु
			mlog(0, "%s: res %.*s, BAST queued while flushing last "
			     "one\n", dlm->name, res->lockname.len,
			     res->lockname.name);
		पूर्ण अन्यथा
			lock->bast_pending = 0;

		/* drop the extra ref.
		 * this may drop it completely. */
		dlm_lock_put(lock);
		dlm_lockres_release_ast(dlm, res);
	पूर्ण
	wake_up(&dlm->ast_wq);
	spin_unlock(&dlm->ast_lock);
पूर्ण


#घोषणा DLM_THREAD_TIMEOUT_MS (4 * 1000)
#घोषणा DLM_THREAD_MAX_सूचीTY  100

अटल पूर्णांक dlm_thपढ़ो(व्योम *data)
अणु
	काष्ठा dlm_lock_resource *res;
	काष्ठा dlm_ctxt *dlm = data;
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(DLM_THREAD_TIMEOUT_MS);

	mlog(0, "dlm thread running for %s...\n", dlm->name);

	जबतक (!kthपढ़ो_should_stop()) अणु
		पूर्णांक n = DLM_THREAD_MAX_सूचीTY;

		/* dlm_shutting_करोwn is very poपूर्णांक-in-समय, but that
		 * करोesn't matter as we'll just loop back around अगर we
		 * get false on the leading edge of a state
		 * transition. */
		dlm_run_purge_list(dlm, dlm_shutting_करोwn(dlm));

		/* We really करोn't want to hold dlm->spinlock जबतक
		 * calling dlm_shuffle_lists on each lockres that
		 * needs to have its queues adjusted and AST/BASTs
		 * run.  So let's pull each entry off the dirty_list
		 * and drop dlm->spinlock ASAP.  Once off the list,
		 * res->spinlock needs to be taken again to protect
		 * the queues जबतक calling dlm_shuffle_lists.  */
		spin_lock(&dlm->spinlock);
		जबतक (!list_empty(&dlm->dirty_list)) अणु
			पूर्णांक delay = 0;
			res = list_entry(dlm->dirty_list.next,
					 काष्ठा dlm_lock_resource, dirty);

			/* peel a lockres off, हटाओ it from the list,
			 * unset the dirty flag and drop the dlm lock */
			BUG_ON(!res);
			dlm_lockres_get(res);

			spin_lock(&res->spinlock);
			/* We clear the DLM_LOCK_RES_सूचीTY state once we shuffle lists below */
			list_del_init(&res->dirty);
			spin_unlock(&res->spinlock);
			spin_unlock(&dlm->spinlock);
			/* Drop dirty_list ref */
			dlm_lockres_put(res);

		 	/* lockres can be re-dirtied/re-added to the
			 * dirty_list in this gap, but that is ok */

			spin_lock(&dlm->ast_lock);
			spin_lock(&res->spinlock);
			अगर (res->owner != dlm->node_num) अणु
				__dlm_prपूर्णांक_one_lock_resource(res);
				mlog(ML_ERROR, "%s: inprog %d, mig %d, reco %d,"
				     " dirty %d\n", dlm->name,
				     !!(res->state & DLM_LOCK_RES_IN_PROGRESS),
				     !!(res->state & DLM_LOCK_RES_MIGRATING),
				     !!(res->state & DLM_LOCK_RES_RECOVERING),
				     !!(res->state & DLM_LOCK_RES_सूचीTY));
			पूर्ण
			BUG_ON(res->owner != dlm->node_num);

			/* it is now ok to move lockreses in these states
			 * to the dirty list, assuming that they will only be
			 * dirty क्रम a लघु जबतक. */
			BUG_ON(res->state & DLM_LOCK_RES_MIGRATING);
			अगर (res->state & (DLM_LOCK_RES_IN_PROGRESS |
					  DLM_LOCK_RES_RECOVERING |
					  DLM_LOCK_RES_RECOVERY_WAITING)) अणु
				/* move it to the tail and keep going */
				res->state &= ~DLM_LOCK_RES_सूचीTY;
				spin_unlock(&res->spinlock);
				spin_unlock(&dlm->ast_lock);
				mlog(0, "%s: res %.*s, inprogress, delay list "
				     "shuffle, state %d\n", dlm->name,
				     res->lockname.len, res->lockname.name,
				     res->state);
				delay = 1;
				जाओ in_progress;
			पूर्ण

			/* at this poपूर्णांक the lockres is not migrating/
			 * recovering/in-progress.  we have the lockres
			 * spinlock and करो NOT have the dlm lock.
			 * safe to reserve/queue asts and run the lists. */

			/* called जबतक holding lockres lock */
			dlm_shuffle_lists(dlm, res);
			res->state &= ~DLM_LOCK_RES_सूचीTY;
			spin_unlock(&res->spinlock);
			spin_unlock(&dlm->ast_lock);

			dlm_lockres_calc_usage(dlm, res);

in_progress:

			spin_lock(&dlm->spinlock);
			/* अगर the lock was in-progress, stick
			 * it on the back of the list */
			अगर (delay) अणु
				spin_lock(&res->spinlock);
				__dlm_dirty_lockres(dlm, res);
				spin_unlock(&res->spinlock);
			पूर्ण
			dlm_lockres_put(res);

			/* unlikely, but we may need to give समय to
			 * other tasks */
			अगर (!--n) अणु
				mlog(0, "%s: Throttling dlm thread\n",
				     dlm->name);
				अवरोध;
			पूर्ण
		पूर्ण

		spin_unlock(&dlm->spinlock);
		dlm_flush_asts(dlm);

		/* yield and जारी right away अगर there is more work to करो */
		अगर (!n) अणु
			cond_resched();
			जारी;
		पूर्ण

		रुको_event_पूर्णांकerruptible_समयout(dlm->dlm_thपढ़ो_wq,
						 !dlm_dirty_list_empty(dlm) ||
						 kthपढ़ो_should_stop(),
						 समयout);
	पूर्ण

	mlog(0, "quitting DLM thread\n");
	वापस 0;
पूर्ण
