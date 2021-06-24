<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmunlock.c
 *
 * underlying calls क्रम unlocking locks
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
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>

#समावेश "../cluster/heartbeat.h"
#समावेश "../cluster/nodemanager.h"
#समावेश "../cluster/tcp.h"

#समावेश "dlmapi.h"
#समावेश "dlmcommon.h"

#घोषणा MLOG_MASK_PREFIX ML_DLM
#समावेश "../cluster/masklog.h"

#घोषणा DLM_UNLOCK_FREE_LOCK           0x00000001
#घोषणा DLM_UNLOCK_CALL_AST            0x00000002
#घोषणा DLM_UNLOCK_REMOVE_LOCK         0x00000004
#घोषणा DLM_UNLOCK_REGRANT_LOCK        0x00000008
#घोषणा DLM_UNLOCK_CLEAR_CONVERT_TYPE  0x00000010


अटल क्रमागत dlm_status dlm_get_cancel_actions(काष्ठा dlm_ctxt *dlm,
					      काष्ठा dlm_lock_resource *res,
					      काष्ठा dlm_lock *lock,
					      काष्ठा dlm_lockstatus *lksb,
					      पूर्णांक *actions);
अटल क्रमागत dlm_status dlm_get_unlock_actions(काष्ठा dlm_ctxt *dlm,
					      काष्ठा dlm_lock_resource *res,
					      काष्ठा dlm_lock *lock,
					      काष्ठा dlm_lockstatus *lksb,
					      पूर्णांक *actions);

अटल क्रमागत dlm_status dlm_send_remote_unlock_request(काष्ठा dlm_ctxt *dlm,
						 काष्ठा dlm_lock_resource *res,
						 काष्ठा dlm_lock *lock,
						 काष्ठा dlm_lockstatus *lksb,
						 पूर्णांक flags,
						 u8 owner);


/*
 * according to the spec:
 * http://खोलोdlm.sourceक्रमge.net/cvsmirror/खोलोdlm/करोcs/dlmbook_final.pdf
 *
 *  flags & LKM_CANCEL != 0: must be converting or blocked
 *  flags & LKM_CANCEL == 0: must be granted
 *
 * So to unlock a converting lock, you must first cancel the
 * convert (passing LKM_CANCEL in flags), then call the unlock
 * again (with no LKM_CANCEL in flags).
 */


/*
 * locking:
 *   caller needs:  none
 *   taken:         res->spinlock and lock->spinlock taken and dropped
 *   held on निकास:  none
 * वापसs: DLM_NORMAL, DLM_NOLOCKMGR, status from network
 * all callers should have taken an extra ref on lock coming in
 */
अटल क्रमागत dlm_status dlmunlock_common(काष्ठा dlm_ctxt *dlm,
					काष्ठा dlm_lock_resource *res,
					काष्ठा dlm_lock *lock,
					काष्ठा dlm_lockstatus *lksb,
					पूर्णांक flags, पूर्णांक *call_ast,
					पूर्णांक master_node)
अणु
	क्रमागत dlm_status status;
	पूर्णांक actions = 0;
	पूर्णांक in_use;
	u8 owner;
	पूर्णांक recovery_रुको = 0;

	mlog(0, "master_node = %d, valblk = %d\n", master_node,
	     flags & LKM_VALBLK);

	अगर (master_node)
		BUG_ON(res->owner != dlm->node_num);
	अन्यथा
		BUG_ON(res->owner == dlm->node_num);

	spin_lock(&dlm->ast_lock);
	/* We want to be sure that we're not मुक्तing a lock
	 * that still has AST's pending... */
	in_use = !list_empty(&lock->ast_list);
	spin_unlock(&dlm->ast_lock);
	अगर (in_use && !(flags & LKM_CANCEL)) अणु
	       mlog(ML_ERROR, "lockres %.*s: Someone is calling dlmunlock "
		    "while waiting for an ast!", res->lockname.len,
		    res->lockname.name);
		वापस DLM_BADPARAM;
	पूर्ण

	spin_lock(&res->spinlock);
	अगर (res->state & DLM_LOCK_RES_IN_PROGRESS) अणु
		अगर (master_node && !(flags & LKM_CANCEL)) अणु
			mlog(ML_ERROR, "lockres in progress!\n");
			spin_unlock(&res->spinlock);
			वापस DLM_FORWARD;
		पूर्ण
		/* ok क्रम this to sleep अगर not in a network handler */
		__dlm_रुको_on_lockres(res);
		res->state |= DLM_LOCK_RES_IN_PROGRESS;
	पूर्ण
	spin_lock(&lock->spinlock);

	अगर (res->state & DLM_LOCK_RES_RECOVERING) अणु
		status = DLM_RECOVERING;
		जाओ leave;
	पूर्ण

	अगर (res->state & DLM_LOCK_RES_MIGRATING) अणु
		status = DLM_MIGRATING;
		जाओ leave;
	पूर्ण

	/* see above क्रम what the spec says about
	 * LKM_CANCEL and the lock queue state */
	अगर (flags & LKM_CANCEL)
		status = dlm_get_cancel_actions(dlm, res, lock, lksb, &actions);
	अन्यथा
		status = dlm_get_unlock_actions(dlm, res, lock, lksb, &actions);

	अगर (status != DLM_NORMAL && (status != DLM_CANCELGRANT || !master_node))
		जाओ leave;

	/* By now this has been masked out of cancel requests. */
	अगर (flags & LKM_VALBLK) अणु
		/* make the final update to the lvb */
		अगर (master_node)
			स_नकल(res->lvb, lksb->lvb, DLM_LVB_LEN);
		अन्यथा
			flags |= LKM_PUT_LVB; /* let the send function
					       * handle it. */
	पूर्ण

	अगर (!master_node) अणु
		owner = res->owner;
		/* drop locks and send message */
		अगर (flags & LKM_CANCEL)
			lock->cancel_pending = 1;
		अन्यथा
			lock->unlock_pending = 1;
		spin_unlock(&lock->spinlock);
		spin_unlock(&res->spinlock);
		status = dlm_send_remote_unlock_request(dlm, res, lock, lksb,
							flags, owner);
		spin_lock(&res->spinlock);
		spin_lock(&lock->spinlock);
		/* अगर the master told us the lock was alपढ़ोy granted,
		 * let the ast handle all of these actions */
		अगर (status == DLM_CANCELGRANT) अणु
			actions &= ~(DLM_UNLOCK_REMOVE_LOCK|
				     DLM_UNLOCK_REGRANT_LOCK|
				     DLM_UNLOCK_CLEAR_CONVERT_TYPE);
		पूर्ण अन्यथा अगर (status == DLM_RECOVERING ||
			   status == DLM_MIGRATING ||
			   status == DLM_FORWARD ||
			   status == DLM_NOLOCKMGR
			   ) अणु
			/* must clear the actions because this unlock
			 * is about to be retried.  cannot मुक्त or करो
			 * any list manipulation. */
			mlog(0, "%s:%.*s: clearing actions, %s\n",
			     dlm->name, res->lockname.len,
			     res->lockname.name,
			     status==DLM_RECOVERING?"recovering":
			     (status==DLM_MIGRATING?"migrating":
				(status == DLM_FORWARD ? "forward" :
						"nolockmanager")));
			actions = 0;
		पूर्ण
		अगर (flags & LKM_CANCEL)
			lock->cancel_pending = 0;
		अन्यथा अणु
			अगर (!lock->unlock_pending)
				recovery_रुको = 1;
			अन्यथा
				lock->unlock_pending = 0;
		पूर्ण
	पूर्ण

	/* get an extra ref on lock.  अगर we are just चयनing
	 * lists here, we करोnt want the lock to go away. */
	dlm_lock_get(lock);

	अगर (actions & DLM_UNLOCK_REMOVE_LOCK) अणु
		list_del_init(&lock->list);
		dlm_lock_put(lock);
	पूर्ण
	अगर (actions & DLM_UNLOCK_REGRANT_LOCK) अणु
		dlm_lock_get(lock);
		list_add_tail(&lock->list, &res->granted);
	पूर्ण
	अगर (actions & DLM_UNLOCK_CLEAR_CONVERT_TYPE) अणु
		mlog(0, "clearing convert_type at %smaster node\n",
		     master_node ? "" : "non-");
		lock->ml.convert_type = LKM_IVMODE;
	पूर्ण

	/* हटाओ the extra ref on lock */
	dlm_lock_put(lock);

leave:
	res->state &= ~DLM_LOCK_RES_IN_PROGRESS;
	अगर (!dlm_lock_on_list(&res->converting, lock))
		BUG_ON(lock->ml.convert_type != LKM_IVMODE);
	अन्यथा
		BUG_ON(lock->ml.convert_type == LKM_IVMODE);
	spin_unlock(&lock->spinlock);
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);

	अगर (recovery_रुको) अणु
		spin_lock(&res->spinlock);
		/* Unlock request will directly succeed after owner dies,
		 * and the lock is alपढ़ोy हटाओd from grant list. We have to
		 * रुको क्रम RECOVERING करोne or we miss the chance to purge it
		 * since the हटाओment is much faster than RECOVERING proc.
		 */
		__dlm_रुको_on_lockres_flags(res, DLM_LOCK_RES_RECOVERING);
		spin_unlock(&res->spinlock);
	पूर्ण

	/* let the caller's final dlm_lock_put handle the actual kमुक्त */
	अगर (actions & DLM_UNLOCK_FREE_LOCK) अणु
		/* this should always be coupled with list removal */
		BUG_ON(!(actions & DLM_UNLOCK_REMOVE_LOCK));
		mlog(0, "lock %u:%llu should be gone now! refs=%d\n",
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		     kref_पढ़ो(&lock->lock_refs)-1);
		dlm_lock_put(lock);
	पूर्ण
	अगर (actions & DLM_UNLOCK_CALL_AST)
		*call_ast = 1;

	/* अगर cancel or unlock succeeded, lvb work is करोne */
	अगर (status == DLM_NORMAL)
		lksb->flags &= ~(DLM_LKSB_PUT_LVB|DLM_LKSB_GET_LVB);

	वापस status;
पूर्ण

व्योम dlm_commit_pending_unlock(काष्ठा dlm_lock_resource *res,
			       काष्ठा dlm_lock *lock)
अणु
	/* leave DLM_LKSB_PUT_LVB on the lksb so any final
	 * update of the lvb will be sent to the new master */
	list_del_init(&lock->list);
पूर्ण

व्योम dlm_commit_pending_cancel(काष्ठा dlm_lock_resource *res,
			       काष्ठा dlm_lock *lock)
अणु
	list_move_tail(&lock->list, &res->granted);
	lock->ml.convert_type = LKM_IVMODE;
पूर्ण


अटल अंतरभूत क्रमागत dlm_status dlmunlock_master(काष्ठा dlm_ctxt *dlm,
					  काष्ठा dlm_lock_resource *res,
					  काष्ठा dlm_lock *lock,
					  काष्ठा dlm_lockstatus *lksb,
					  पूर्णांक flags,
					  पूर्णांक *call_ast)
अणु
	वापस dlmunlock_common(dlm, res, lock, lksb, flags, call_ast, 1);
पूर्ण

अटल अंतरभूत क्रमागत dlm_status dlmunlock_remote(काष्ठा dlm_ctxt *dlm,
					  काष्ठा dlm_lock_resource *res,
					  काष्ठा dlm_lock *lock,
					  काष्ठा dlm_lockstatus *lksb,
					  पूर्णांक flags, पूर्णांक *call_ast)
अणु
	वापस dlmunlock_common(dlm, res, lock, lksb, flags, call_ast, 0);
पूर्ण

/*
 * locking:
 *   caller needs:  none
 *   taken:         none
 *   held on निकास:  none
 * वापसs: DLM_NORMAL, DLM_NOLOCKMGR, status from network
 */
अटल क्रमागत dlm_status dlm_send_remote_unlock_request(काष्ठा dlm_ctxt *dlm,
						 काष्ठा dlm_lock_resource *res,
						 काष्ठा dlm_lock *lock,
						 काष्ठा dlm_lockstatus *lksb,
						 पूर्णांक flags,
						 u8 owner)
अणु
	काष्ठा dlm_unlock_lock unlock;
	पूर्णांक पंचांगpret;
	क्रमागत dlm_status ret;
	पूर्णांक status = 0;
	काष्ठा kvec vec[2];
	माप_प्रकार veclen = 1;

	mlog(0, "%.*s\n", res->lockname.len, res->lockname.name);

	अगर (owner == dlm->node_num) अणु
		/* ended up trying to contact ourself.  this means
		 * that the lockres had been remote but became local
		 * via a migration.  just retry it, now as local */
		mlog(0, "%s:%.*s: this node became the master due to a "
		     "migration, re-evaluate now\n", dlm->name,
		     res->lockname.len, res->lockname.name);
		वापस DLM_FORWARD;
	पूर्ण

	स_रखो(&unlock, 0, माप(unlock));
	unlock.node_idx = dlm->node_num;
	unlock.flags = cpu_to_be32(flags);
	unlock.cookie = lock->ml.cookie;
	unlock.namelen = res->lockname.len;
	स_नकल(unlock.name, res->lockname.name, unlock.namelen);

	vec[0].iov_len = माप(काष्ठा dlm_unlock_lock);
	vec[0].iov_base = &unlock;

	अगर (flags & LKM_PUT_LVB) अणु
		/* extra data to send अगर we are updating lvb */
		vec[1].iov_len = DLM_LVB_LEN;
		vec[1].iov_base = lock->lksb->lvb;
		veclen++;
	पूर्ण

	पंचांगpret = o2net_send_message_vec(DLM_UNLOCK_LOCK_MSG, dlm->key,
					vec, veclen, owner, &status);
	अगर (पंचांगpret >= 0) अणु
		// successfully sent and received
		अगर (status == DLM_FORWARD)
			mlog(0, "master was in-progress.  retry\n");
		ret = status;
	पूर्ण अन्यथा अणु
		mlog(ML_ERROR, "Error %d when sending message %u (key 0x%x) to "
		     "node %u\n", पंचांगpret, DLM_UNLOCK_LOCK_MSG, dlm->key, owner);
		अगर (dlm_is_host_करोwn(पंचांगpret)) अणु
			/* NOTE: this seems strange, but it is what we want.
			 * when the master goes करोwn during a cancel or
			 * unlock, the recovery code completes the operation
			 * as अगर the master had not died, then passes the
			 * updated state to the recovery master.  this thपढ़ो
			 * just needs to finish out the operation and call
			 * the unlockast. */
			अगर (dlm_is_node_dead(dlm, owner))
				ret = DLM_NORMAL;
			अन्यथा
				ret = DLM_NOLOCKMGR;
		पूर्ण अन्यथा अणु
			/* something bad.  this will BUG in ocfs2 */
			ret = dlm_err_to_dlm_status(पंचांगpret);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * locking:
 *   caller needs:  none
 *   taken:         takes and drops res->spinlock
 *   held on निकास:  none
 * वापसs: DLM_NORMAL, DLM_BADARGS, DLM_IVLOCKID,
 *          वापस value from dlmunlock_master
 */
पूर्णांक dlm_unlock_lock_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			    व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_unlock_lock *unlock = (काष्ठा dlm_unlock_lock *)msg->buf;
	काष्ठा dlm_lock_resource *res = शून्य;
	काष्ठा dlm_lock *lock = शून्य;
	क्रमागत dlm_status status = DLM_NORMAL;
	पूर्णांक found = 0, i;
	काष्ठा dlm_lockstatus *lksb = शून्य;
	पूर्णांक ignore;
	u32 flags;
	काष्ठा list_head *queue;

	flags = be32_to_cpu(unlock->flags);

	अगर (flags & LKM_GET_LVB) अणु
		mlog(ML_ERROR, "bad args!  GET_LVB specified on unlock!\n");
		वापस DLM_BADARGS;
	पूर्ण

	अगर ((flags & (LKM_PUT_LVB|LKM_CANCEL)) == (LKM_PUT_LVB|LKM_CANCEL)) अणु
		mlog(ML_ERROR, "bad args!  cannot modify lvb on a CANCEL "
		     "request!\n");
		वापस DLM_BADARGS;
	पूर्ण

	अगर (unlock->namelen > DLM_LOCKID_NAME_MAX) अणु
		mlog(ML_ERROR, "Invalid name length in unlock handler!\n");
		वापस DLM_IVBUFLEN;
	पूर्ण

	अगर (!dlm_grab(dlm))
		वापस DLM_FORWARD;

	mlog_bug_on_msg(!dlm_करोमुख्य_fully_joined(dlm),
			"Domain %s not fully joined!\n", dlm->name);

	mlog(0, "lvb: %s\n", flags & LKM_PUT_LVB ? "put lvb" : "none");

	res = dlm_lookup_lockres(dlm, unlock->name, unlock->namelen);
	अगर (!res) अणु
		/* We assume here that a no lock resource simply means
		 * it was migrated away and destroyed beक्रमe the other
		 * node could detect it. */
		mlog(0, "returning DLM_FORWARD -- res no longer exists\n");
		status = DLM_FORWARD;
		जाओ not_found;
	पूर्ण

	queue=&res->granted;
	found = 0;
	spin_lock(&res->spinlock);
	अगर (res->state & DLM_LOCK_RES_RECOVERING) अणु
		spin_unlock(&res->spinlock);
		mlog(0, "returning DLM_RECOVERING\n");
		status = DLM_RECOVERING;
		जाओ leave;
	पूर्ण

	अगर (res->state & DLM_LOCK_RES_MIGRATING) अणु
		spin_unlock(&res->spinlock);
		mlog(0, "returning DLM_MIGRATING\n");
		status = DLM_MIGRATING;
		जाओ leave;
	पूर्ण

	अगर (res->owner != dlm->node_num) अणु
		spin_unlock(&res->spinlock);
		mlog(0, "returning DLM_FORWARD -- not master\n");
		status = DLM_FORWARD;
		जाओ leave;
	पूर्ण

	क्रम (i=0; i<3; i++) अणु
		list_क्रम_each_entry(lock, queue, list) अणु
			अगर (lock->ml.cookie == unlock->cookie &&
		    	    lock->ml.node == unlock->node_idx) अणु
				dlm_lock_get(lock);
				found = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (found)
			अवरोध;
		/* scan granted -> converting -> blocked queues */
		queue++;
	पूर्ण
	spin_unlock(&res->spinlock);
	अगर (!found) अणु
		status = DLM_IVLOCKID;
		जाओ not_found;
	पूर्ण

	/* lock was found on queue */
	lksb = lock->lksb;
	अगर (flags & (LKM_VALBLK|LKM_PUT_LVB) &&
	    lock->ml.type != LKM_EXMODE)
		flags &= ~(LKM_VALBLK|LKM_PUT_LVB);

	/* unlockast only called on originating node */
	अगर (flags & LKM_PUT_LVB) अणु
		lksb->flags |= DLM_LKSB_PUT_LVB;
		स_नकल(&lksb->lvb[0], &unlock->lvb[0], DLM_LVB_LEN);
	पूर्ण

	/* अगर this is in-progress, propagate the DLM_FORWARD
	 * all the way back out */
	status = dlmunlock_master(dlm, res, lock, lksb, flags, &ignore);
	अगर (status == DLM_FORWARD)
		mlog(0, "lockres is in progress\n");

	अगर (flags & LKM_PUT_LVB)
		lksb->flags &= ~DLM_LKSB_PUT_LVB;

	dlm_lockres_calc_usage(dlm, res);
	dlm_kick_thपढ़ो(dlm, res);

not_found:
	अगर (!found)
		mlog(ML_ERROR, "failed to find lock to unlock! "
			       "cookie=%u:%llu\n",
		     dlm_get_lock_cookie_node(be64_to_cpu(unlock->cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(unlock->cookie)));
	अन्यथा
		dlm_lock_put(lock);

leave:
	अगर (res)
		dlm_lockres_put(res);

	dlm_put(dlm);

	वापस status;
पूर्ण


अटल क्रमागत dlm_status dlm_get_cancel_actions(काष्ठा dlm_ctxt *dlm,
					      काष्ठा dlm_lock_resource *res,
					      काष्ठा dlm_lock *lock,
					      काष्ठा dlm_lockstatus *lksb,
					      पूर्णांक *actions)
अणु
	क्रमागत dlm_status status;

	अगर (dlm_lock_on_list(&res->blocked, lock)) अणु
		/* cancel this outright */
		status = DLM_NORMAL;
		*actions = (DLM_UNLOCK_CALL_AST |
			    DLM_UNLOCK_REMOVE_LOCK);
	पूर्ण अन्यथा अगर (dlm_lock_on_list(&res->converting, lock)) अणु
		/* cancel the request, put back on granted */
		status = DLM_NORMAL;
		*actions = (DLM_UNLOCK_CALL_AST |
			    DLM_UNLOCK_REMOVE_LOCK |
			    DLM_UNLOCK_REGRANT_LOCK |
			    DLM_UNLOCK_CLEAR_CONVERT_TYPE);
	पूर्ण अन्यथा अगर (dlm_lock_on_list(&res->granted, lock)) अणु
		/* too late, alपढ़ोy granted. */
		status = DLM_CANCELGRANT;
		*actions = DLM_UNLOCK_CALL_AST;
	पूर्ण अन्यथा अणु
		mlog(ML_ERROR, "lock to cancel is not on any list!\n");
		status = DLM_IVLOCKID;
		*actions = 0;
	पूर्ण
	वापस status;
पूर्ण

अटल क्रमागत dlm_status dlm_get_unlock_actions(काष्ठा dlm_ctxt *dlm,
					      काष्ठा dlm_lock_resource *res,
					      काष्ठा dlm_lock *lock,
					      काष्ठा dlm_lockstatus *lksb,
					      पूर्णांक *actions)
अणु
	क्रमागत dlm_status status;

	/* unlock request */
	अगर (!dlm_lock_on_list(&res->granted, lock)) अणु
		status = DLM_DENIED;
		dlm_error(status);
		*actions = 0;
	पूर्ण अन्यथा अणु
		/* unlock granted lock */
		status = DLM_NORMAL;
		*actions = (DLM_UNLOCK_FREE_LOCK |
			    DLM_UNLOCK_CALL_AST |
			    DLM_UNLOCK_REMOVE_LOCK);
	पूर्ण
	वापस status;
पूर्ण

/* there seems to be no poपूर्णांक in करोing this async
 * since (even क्रम the remote हाल) there is really
 * no work to queue up... so just करो it and fire the
 * unlockast by hand when करोne... */
क्रमागत dlm_status dlmunlock(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lockstatus *lksb,
			  पूर्णांक flags, dlm_astunlockfunc_t *unlockast, व्योम *data)
अणु
	क्रमागत dlm_status status;
	काष्ठा dlm_lock_resource *res;
	काष्ठा dlm_lock *lock = शून्य;
	पूर्णांक call_ast, is_master;

	अगर (!lksb) अणु
		dlm_error(DLM_BADARGS);
		वापस DLM_BADARGS;
	पूर्ण

	अगर (flags & ~(LKM_CANCEL | LKM_VALBLK | LKM_INVVALBLK)) अणु
		dlm_error(DLM_BADPARAM);
		वापस DLM_BADPARAM;
	पूर्ण

	अगर ((flags & (LKM_VALBLK | LKM_CANCEL)) == (LKM_VALBLK | LKM_CANCEL)) अणु
		mlog(0, "VALBLK given with CANCEL: ignoring VALBLK\n");
		flags &= ~LKM_VALBLK;
	पूर्ण

	अगर (!lksb->lockid || !lksb->lockid->lockres) अणु
		dlm_error(DLM_BADPARAM);
		वापस DLM_BADPARAM;
	पूर्ण

	lock = lksb->lockid;
	BUG_ON(!lock);
	dlm_lock_get(lock);

	res = lock->lockres;
	BUG_ON(!res);
	dlm_lockres_get(res);
retry:
	call_ast = 0;
	/* need to retry up here because owner may have changed */
	mlog(0, "lock=%p res=%p\n", lock, res);

	spin_lock(&res->spinlock);
	is_master = (res->owner == dlm->node_num);
	अगर (flags & LKM_VALBLK && lock->ml.type != LKM_EXMODE)
		flags &= ~LKM_VALBLK;
	spin_unlock(&res->spinlock);

	अगर (is_master) अणु
		status = dlmunlock_master(dlm, res, lock, lksb, flags,
					  &call_ast);
		mlog(0, "done calling dlmunlock_master: returned %d, "
		     "call_ast is %d\n", status, call_ast);
	पूर्ण अन्यथा अणु
		status = dlmunlock_remote(dlm, res, lock, lksb, flags,
					  &call_ast);
		mlog(0, "done calling dlmunlock_remote: returned %d, "
		     "call_ast is %d\n", status, call_ast);
	पूर्ण

	अगर (status == DLM_RECOVERING ||
	    status == DLM_MIGRATING ||
	    status == DLM_FORWARD ||
	    status == DLM_NOLOCKMGR) अणु

		/* We want to go away क्रम a tiny bit to allow recovery
		 * / migration to complete on this resource. I करोn't
		 * know of any रुको queue we could sleep on as this
		 * may be happening on another node. Perhaps the
		 * proper solution is to queue up requests on the
		 * other end? */

		/* करो we want to yield(); ?? */
		msleep(50);

		mlog(0, "retrying unlock due to pending recovery/"
		     "migration/in-progress/reconnect\n");
		जाओ retry;
	पूर्ण

	अगर (call_ast) अणु
		mlog(0, "calling unlockast(%p, %d)\n", data, status);
		अगर (is_master) अणु
			/* it is possible that there is one last bast
			 * pending.  make sure it is flushed, then
			 * call the unlockast.
			 * not an issue अगर this is a mastered remotely,
			 * since this lock has been हटाओd from the
			 * lockres queues and cannot be found. */
			dlm_kick_thपढ़ो(dlm, शून्य);
			रुको_event(dlm->ast_wq,
				   dlm_lock_basts_flushed(dlm, lock));
		पूर्ण
		(*unlockast)(data, status);
	पूर्ण

	अगर (status == DLM_CANCELGRANT)
		status = DLM_NORMAL;

	अगर (status == DLM_NORMAL) अणु
		mlog(0, "kicking the thread\n");
		dlm_kick_thपढ़ो(dlm, res);
	पूर्ण अन्यथा
		dlm_error(status);

	dlm_lockres_calc_usage(dlm, res);
	dlm_lockres_put(res);
	dlm_lock_put(lock);

	mlog(0, "returning status=%d!\n", status);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(dlmunlock);

