<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmconvert.c
 *
 * underlying calls क्रम lock conversion
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


#समावेश "../cluster/heartbeat.h"
#समावेश "../cluster/nodemanager.h"
#समावेश "../cluster/tcp.h"

#समावेश "dlmapi.h"
#समावेश "dlmcommon.h"

#समावेश "dlmconvert.h"

#घोषणा MLOG_MASK_PREFIX ML_DLM
#समावेश "../cluster/masklog.h"

/* NOTE: __dlmconvert_master is the only function in here that
 * needs a spinlock held on entry (res->spinlock) and it is the
 * only one that holds a lock on निकास (res->spinlock).
 * All other functions in here need no locks and drop all of
 * the locks that they acquire. */
अटल क्रमागत dlm_status __dlmconvert_master(काष्ठा dlm_ctxt *dlm,
					   काष्ठा dlm_lock_resource *res,
					   काष्ठा dlm_lock *lock, पूर्णांक flags,
					   पूर्णांक type, पूर्णांक *call_ast,
					   पूर्णांक *kick_thपढ़ो);
अटल क्रमागत dlm_status dlm_send_remote_convert_request(काष्ठा dlm_ctxt *dlm,
					   काष्ठा dlm_lock_resource *res,
					   काष्ठा dlm_lock *lock, पूर्णांक flags, पूर्णांक type);

/*
 * this is only called directly by dlmlock(), and only when the
 * local node is the owner of the lockres
 * locking:
 *   caller needs:  none
 *   taken:         takes and drops res->spinlock
 *   held on निकास:  none
 * वापसs: see __dlmconvert_master
 */
क्रमागत dlm_status dlmconvert_master(काष्ठा dlm_ctxt *dlm,
				  काष्ठा dlm_lock_resource *res,
				  काष्ठा dlm_lock *lock, पूर्णांक flags, पूर्णांक type)
अणु
	पूर्णांक call_ast = 0, kick_thपढ़ो = 0;
	क्रमागत dlm_status status;

	spin_lock(&res->spinlock);
	/* we are not in a network handler, this is fine */
	__dlm_रुको_on_lockres(res);
	__dlm_lockres_reserve_ast(res);
	res->state |= DLM_LOCK_RES_IN_PROGRESS;

	status = __dlmconvert_master(dlm, res, lock, flags, type,
				     &call_ast, &kick_thपढ़ो);

	res->state &= ~DLM_LOCK_RES_IN_PROGRESS;
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);
	अगर (status != DLM_NORMAL && status != DLM_NOTQUEUED)
		dlm_error(status);

	/* either queue the ast or release it */
	अगर (call_ast)
		dlm_queue_ast(dlm, lock);
	अन्यथा
		dlm_lockres_release_ast(dlm, res);

	अगर (kick_thपढ़ो)
		dlm_kick_thपढ़ो(dlm, res);

	वापस status;
पूर्ण

/* perक्रमms lock conversion at the lockres master site
 * locking:
 *   caller needs:  res->spinlock
 *   taken:         takes and drops lock->spinlock
 *   held on निकास:  res->spinlock
 * वापसs: DLM_NORMAL, DLM_NOTQUEUED, DLM_DENIED
 *   call_ast: whether ast should be called क्रम this lock
 *   kick_thपढ़ो: whether dlm_kick_thपढ़ो should be called
 */
अटल क्रमागत dlm_status __dlmconvert_master(काष्ठा dlm_ctxt *dlm,
					   काष्ठा dlm_lock_resource *res,
					   काष्ठा dlm_lock *lock, पूर्णांक flags,
					   पूर्णांक type, पूर्णांक *call_ast,
					   पूर्णांक *kick_thपढ़ो)
अणु
	क्रमागत dlm_status status = DLM_NORMAL;
	काष्ठा dlm_lock *पंचांगplock=शून्य;

	निश्चित_spin_locked(&res->spinlock);

	mlog(0, "type=%d, convert_type=%d, new convert_type=%d\n",
	     lock->ml.type, lock->ml.convert_type, type);

	spin_lock(&lock->spinlock);

	/* alपढ़ोy converting? */
	अगर (lock->ml.convert_type != LKM_IVMODE) अणु
		mlog(ML_ERROR, "attempted to convert a lock with a lock "
		     "conversion pending\n");
		status = DLM_DENIED;
		जाओ unlock_निकास;
	पूर्ण

	/* must be on grant queue to convert */
	अगर (!dlm_lock_on_list(&res->granted, lock)) अणु
		mlog(ML_ERROR, "attempted to convert a lock not on grant "
		     "queue\n");
		status = DLM_DENIED;
		जाओ unlock_निकास;
	पूर्ण

	अगर (flags & LKM_VALBLK) अणु
		चयन (lock->ml.type) अणु
			हाल LKM_EXMODE:
				/* EX + LKM_VALBLK + convert == set lvb */
				mlog(0, "will set lvb: converting %s->%s\n",
				     dlm_lock_mode_name(lock->ml.type),
				     dlm_lock_mode_name(type));
				lock->lksb->flags |= DLM_LKSB_PUT_LVB;
				अवरोध;
			हाल LKM_PRMODE:
			हाल LKM_NLMODE:
				/* refetch अगर new level is not NL */
				अगर (type > LKM_NLMODE) अणु
					mlog(0, "will fetch new value into "
					     "lvb: converting %s->%s\n",
					     dlm_lock_mode_name(lock->ml.type),
					     dlm_lock_mode_name(type));
					lock->lksb->flags |= DLM_LKSB_GET_LVB;
				पूर्ण अन्यथा अणु
					mlog(0, "will NOT fetch new value "
					     "into lvb: converting %s->%s\n",
					     dlm_lock_mode_name(lock->ml.type),
					     dlm_lock_mode_name(type));
					flags &= ~(LKM_VALBLK);
				पूर्ण
				अवरोध;
		पूर्ण
	पूर्ण


	/* in-place करोwnconvert? */
	अगर (type <= lock->ml.type)
		जाओ grant;

	/* upconvert from here on */
	status = DLM_NORMAL;
	list_क्रम_each_entry(पंचांगplock, &res->granted, list) अणु
		अगर (पंचांगplock == lock)
			जारी;
		अगर (!dlm_lock_compatible(पंचांगplock->ml.type, type))
			जाओ चयन_queues;
	पूर्ण

	list_क्रम_each_entry(पंचांगplock, &res->converting, list) अणु
		अगर (!dlm_lock_compatible(पंचांगplock->ml.type, type))
			जाओ चयन_queues;
		/* existing conversion requests take precedence */
		अगर (!dlm_lock_compatible(पंचांगplock->ml.convert_type, type))
			जाओ चयन_queues;
	पूर्ण

	/* fall thru to grant */

grant:
	mlog(0, "res %.*s, granting %s lock\n", res->lockname.len,
	     res->lockname.name, dlm_lock_mode_name(type));
	/* immediately grant the new lock type */
	lock->lksb->status = DLM_NORMAL;
	अगर (lock->ml.node == dlm->node_num)
		mlog(0, "doing in-place convert for nonlocal lock\n");
	lock->ml.type = type;
	अगर (lock->lksb->flags & DLM_LKSB_PUT_LVB)
		स_नकल(res->lvb, lock->lksb->lvb, DLM_LVB_LEN);

	/*
	 * Move the lock to the tail because it may be the only lock which has
	 * an invalid lvb.
	 */
	list_move_tail(&lock->list, &res->granted);

	status = DLM_NORMAL;
	*call_ast = 1;
	जाओ unlock_निकास;

चयन_queues:
	अगर (flags & LKM_NOQUEUE) अणु
		mlog(0, "failed to convert NOQUEUE lock %.*s from "
		     "%d to %d...\n", res->lockname.len, res->lockname.name,
		     lock->ml.type, type);
		status = DLM_NOTQUEUED;
		जाओ unlock_निकास;
	पूर्ण
	mlog(0, "res %.*s, queueing...\n", res->lockname.len,
	     res->lockname.name);

	lock->ml.convert_type = type;
	/* करो not alter lock refcount.  चयनing lists. */
	list_move_tail(&lock->list, &res->converting);

unlock_निकास:
	spin_unlock(&lock->spinlock);
	अगर (status == DLM_DENIED) अणु
		__dlm_prपूर्णांक_one_lock_resource(res);
	पूर्ण
	अगर (status == DLM_NORMAL)
		*kick_thपढ़ो = 1;
	वापस status;
पूर्ण

व्योम dlm_revert_pending_convert(काष्ठा dlm_lock_resource *res,
				काष्ठा dlm_lock *lock)
अणु
	/* करो not alter lock refcount.  चयनing lists. */
	list_move_tail(&lock->list, &res->granted);
	lock->ml.convert_type = LKM_IVMODE;
	lock->lksb->flags &= ~(DLM_LKSB_GET_LVB|DLM_LKSB_PUT_LVB);
पूर्ण

/* messages the master site to करो lock conversion
 * locking:
 *   caller needs:  none
 *   taken:         takes and drops res->spinlock, uses DLM_LOCK_RES_IN_PROGRESS
 *   held on निकास:  none
 * वापसs: DLM_NORMAL, DLM_RECOVERING, status from remote node
 */
क्रमागत dlm_status dlmconvert_remote(काष्ठा dlm_ctxt *dlm,
				  काष्ठा dlm_lock_resource *res,
				  काष्ठा dlm_lock *lock, पूर्णांक flags, पूर्णांक type)
अणु
	क्रमागत dlm_status status;

	mlog(0, "type=%d, convert_type=%d, busy=%d\n", lock->ml.type,
	     lock->ml.convert_type, res->state & DLM_LOCK_RES_IN_PROGRESS);

	spin_lock(&res->spinlock);
	अगर (res->state & DLM_LOCK_RES_RECOVERING) अणु
		mlog(0, "bailing out early since res is RECOVERING "
		     "on secondary queue\n");
		/* __dlm_prपूर्णांक_one_lock_resource(res); */
		status = DLM_RECOVERING;
		जाओ bail;
	पूर्ण
	/* will निकास this call with spinlock held */
	__dlm_रुको_on_lockres(res);

	अगर (lock->ml.convert_type != LKM_IVMODE) अणु
		__dlm_prपूर्णांक_one_lock_resource(res);
		mlog(ML_ERROR, "converting a remote lock that is already "
		     "converting! (cookie=%u:%llu, conv=%d)\n",
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		     lock->ml.convert_type);
		status = DLM_DENIED;
		जाओ bail;
	पूर्ण

	अगर (lock->ml.type == type && lock->ml.convert_type == LKM_IVMODE) अणु
		mlog(0, "last convert request returned DLM_RECOVERING, but "
		     "owner has already queued and sent ast to me. res %.*s, "
		     "(cookie=%u:%llu, type=%d, conv=%d)\n",
		     res->lockname.len, res->lockname.name,
		     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
		     lock->ml.type, lock->ml.convert_type);
		status = DLM_NORMAL;
		जाओ bail;
	पूर्ण

	res->state |= DLM_LOCK_RES_IN_PROGRESS;
	/* move lock to local convert queue */
	/* करो not alter lock refcount.  चयनing lists. */
	list_move_tail(&lock->list, &res->converting);
	lock->convert_pending = 1;
	lock->ml.convert_type = type;

	अगर (flags & LKM_VALBLK) अणु
		अगर (lock->ml.type == LKM_EXMODE) अणु
			flags |= LKM_PUT_LVB;
			lock->lksb->flags |= DLM_LKSB_PUT_LVB;
		पूर्ण अन्यथा अणु
			अगर (lock->ml.convert_type == LKM_NLMODE)
				flags &= ~LKM_VALBLK;
			अन्यथा अणु
				flags |= LKM_GET_LVB;
				lock->lksb->flags |= DLM_LKSB_GET_LVB;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&res->spinlock);

	/* no locks held here.
	 * need to रुको क्रम a reply as to whether it got queued or not. */
	status = dlm_send_remote_convert_request(dlm, res, lock, flags, type);

	spin_lock(&res->spinlock);
	res->state &= ~DLM_LOCK_RES_IN_PROGRESS;
	/* अगर it failed, move it back to granted queue.
	 * अगर master वापसs DLM_NORMAL and then करोwn beक्रमe sending ast,
	 * it may have alपढ़ोy been moved to granted queue, reset to
	 * DLM_RECOVERING and retry convert */
	अगर (status != DLM_NORMAL) अणु
		अगर (status != DLM_NOTQUEUED)
			dlm_error(status);
		dlm_revert_pending_convert(res, lock);
	पूर्ण अन्यथा अगर (!lock->convert_pending) अणु
		mlog(0, "%s: res %.*s, owner died and lock has been moved back "
				"to granted list, retry convert.\n",
				dlm->name, res->lockname.len, res->lockname.name);
		status = DLM_RECOVERING;
	पूर्ण

	lock->convert_pending = 0;
bail:
	spin_unlock(&res->spinlock);

	/* TODO: should this be a wake_one? */
	/* wake up any IN_PROGRESS रुकोers */
	wake_up(&res->wq);

	वापस status;
पूर्ण

/* sends DLM_CONVERT_LOCK_MSG to master site
 * locking:
 *   caller needs:  none
 *   taken:         none
 *   held on निकास:  none
 * वापसs: DLM_NOLOCKMGR, status from remote node
 */
अटल क्रमागत dlm_status dlm_send_remote_convert_request(काष्ठा dlm_ctxt *dlm,
					   काष्ठा dlm_lock_resource *res,
					   काष्ठा dlm_lock *lock, पूर्णांक flags, पूर्णांक type)
अणु
	काष्ठा dlm_convert_lock convert;
	पूर्णांक पंचांगpret;
	क्रमागत dlm_status ret;
	पूर्णांक status = 0;
	काष्ठा kvec vec[2];
	माप_प्रकार veclen = 1;

	mlog(0, "%.*s\n", res->lockname.len, res->lockname.name);

	स_रखो(&convert, 0, माप(काष्ठा dlm_convert_lock));
	convert.node_idx = dlm->node_num;
	convert.requested_type = type;
	convert.cookie = lock->ml.cookie;
	convert.namelen = res->lockname.len;
	convert.flags = cpu_to_be32(flags);
	स_नकल(convert.name, res->lockname.name, convert.namelen);

	vec[0].iov_len = माप(काष्ठा dlm_convert_lock);
	vec[0].iov_base = &convert;

	अगर (flags & LKM_PUT_LVB) अणु
		/* extra data to send अगर we are updating lvb */
		vec[1].iov_len = DLM_LVB_LEN;
		vec[1].iov_base = lock->lksb->lvb;
		veclen++;
	पूर्ण

	पंचांगpret = o2net_send_message_vec(DLM_CONVERT_LOCK_MSG, dlm->key,
					vec, veclen, res->owner, &status);
	अगर (पंचांगpret >= 0) अणु
		// successfully sent and received
		ret = status;  // this is alपढ़ोy a dlm_status
		अगर (ret == DLM_RECOVERING) अणु
			mlog(0, "node %u returned DLM_RECOVERING from convert "
			     "message!\n", res->owner);
		पूर्ण अन्यथा अगर (ret == DLM_MIGRATING) अणु
			mlog(0, "node %u returned DLM_MIGRATING from convert "
			     "message!\n", res->owner);
		पूर्ण अन्यथा अगर (ret == DLM_FORWARD) अणु
			mlog(0, "node %u returned DLM_FORWARD from convert "
			     "message!\n", res->owner);
		पूर्ण अन्यथा अगर (ret != DLM_NORMAL && ret != DLM_NOTQUEUED)
			dlm_error(ret);
	पूर्ण अन्यथा अणु
		mlog(ML_ERROR, "Error %d when sending message %u (key 0x%x) to "
		     "node %u\n", पंचांगpret, DLM_CONVERT_LOCK_MSG, dlm->key,
		     res->owner);
		अगर (dlm_is_host_करोwn(पंचांगpret)) अणु
			/* instead of logging the same network error over
			 * and over, sleep here and रुको क्रम the heartbeat
			 * to notice the node is dead.  बार out after 5s. */
			dlm_रुको_क्रम_node_death(dlm, res->owner,
						DLM_NODE_DEATH_WAIT_MAX);
			ret = DLM_RECOVERING;
			mlog(0, "node %u died so returning DLM_RECOVERING "
			     "from convert message!\n", res->owner);
		पूर्ण अन्यथा अणु
			ret = dlm_err_to_dlm_status(पंचांगpret);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/* handler क्रम DLM_CONVERT_LOCK_MSG on master site
 * locking:
 *   caller needs:  none
 *   taken:         takes and drop res->spinlock
 *   held on निकास:  none
 * वापसs: DLM_NORMAL, DLM_IVLOCKID, DLM_BADARGS,
 *          status from __dlmconvert_master
 */
पूर्णांक dlm_convert_lock_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			     व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_convert_lock *cnv = (काष्ठा dlm_convert_lock *)msg->buf;
	काष्ठा dlm_lock_resource *res = शून्य;
	काष्ठा dlm_lock *lock = शून्य;
	काष्ठा dlm_lock *पंचांगp_lock;
	काष्ठा dlm_lockstatus *lksb;
	क्रमागत dlm_status status = DLM_NORMAL;
	u32 flags;
	पूर्णांक call_ast = 0, kick_thपढ़ो = 0, ast_reserved = 0, wake = 0;

	अगर (!dlm_grab(dlm)) अणु
		dlm_error(DLM_REJECTED);
		वापस DLM_REJECTED;
	पूर्ण

	mlog_bug_on_msg(!dlm_करोमुख्य_fully_joined(dlm),
			"Domain %s not fully joined!\n", dlm->name);

	अगर (cnv->namelen > DLM_LOCKID_NAME_MAX) अणु
		status = DLM_IVBUFLEN;
		dlm_error(status);
		जाओ leave;
	पूर्ण

	flags = be32_to_cpu(cnv->flags);

	अगर ((flags & (LKM_PUT_LVB|LKM_GET_LVB)) ==
	     (LKM_PUT_LVB|LKM_GET_LVB)) अणु
		mlog(ML_ERROR, "both PUT and GET lvb specified\n");
		status = DLM_BADARGS;
		जाओ leave;
	पूर्ण

	mlog(0, "lvb: %s\n", flags & LKM_PUT_LVB ? "put lvb" :
	     (flags & LKM_GET_LVB ? "get lvb" : "none"));

	status = DLM_IVLOCKID;
	res = dlm_lookup_lockres(dlm, cnv->name, cnv->namelen);
	अगर (!res) अणु
		dlm_error(status);
		जाओ leave;
	पूर्ण

	spin_lock(&res->spinlock);
	status = __dlm_lockres_state_to_status(res);
	अगर (status != DLM_NORMAL) अणु
		spin_unlock(&res->spinlock);
		dlm_error(status);
		जाओ leave;
	पूर्ण
	list_क्रम_each_entry(पंचांगp_lock, &res->granted, list) अणु
		अगर (पंचांगp_lock->ml.cookie == cnv->cookie &&
		    पंचांगp_lock->ml.node == cnv->node_idx) अणु
			lock = पंचांगp_lock;
			dlm_lock_get(lock);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&res->spinlock);
	अगर (!lock) अणु
		status = DLM_IVLOCKID;
		mlog(ML_ERROR, "did not find lock to convert on grant queue! "
			       "cookie=%u:%llu\n",
		     dlm_get_lock_cookie_node(be64_to_cpu(cnv->cookie)),
		     dlm_get_lock_cookie_seq(be64_to_cpu(cnv->cookie)));
		dlm_prपूर्णांक_one_lock_resource(res);
		जाओ leave;
	पूर्ण

	/* found the lock */
	lksb = lock->lksb;

	/* see अगर caller needed to get/put lvb */
	अगर (flags & LKM_PUT_LVB) अणु
		BUG_ON(lksb->flags & (DLM_LKSB_PUT_LVB|DLM_LKSB_GET_LVB));
		lksb->flags |= DLM_LKSB_PUT_LVB;
		स_नकल(&lksb->lvb[0], &cnv->lvb[0], DLM_LVB_LEN);
	पूर्ण अन्यथा अगर (flags & LKM_GET_LVB) अणु
		BUG_ON(lksb->flags & (DLM_LKSB_PUT_LVB|DLM_LKSB_GET_LVB));
		lksb->flags |= DLM_LKSB_GET_LVB;
	पूर्ण

	spin_lock(&res->spinlock);
	status = __dlm_lockres_state_to_status(res);
	अगर (status == DLM_NORMAL) अणु
		__dlm_lockres_reserve_ast(res);
		ast_reserved = 1;
		res->state |= DLM_LOCK_RES_IN_PROGRESS;
		status = __dlmconvert_master(dlm, res, lock, flags,
					     cnv->requested_type,
					     &call_ast, &kick_thपढ़ो);
		res->state &= ~DLM_LOCK_RES_IN_PROGRESS;
		wake = 1;
	पूर्ण
	spin_unlock(&res->spinlock);
	अगर (wake)
		wake_up(&res->wq);

	अगर (status != DLM_NORMAL) अणु
		अगर (status != DLM_NOTQUEUED)
			dlm_error(status);
		lksb->flags &= ~(DLM_LKSB_GET_LVB|DLM_LKSB_PUT_LVB);
	पूर्ण

leave:
	अगर (lock)
		dlm_lock_put(lock);

	/* either queue the ast or release it, अगर reserved */
	अगर (call_ast)
		dlm_queue_ast(dlm, lock);
	अन्यथा अगर (ast_reserved)
		dlm_lockres_release_ast(dlm, res);

	अगर (kick_thपढ़ो)
		dlm_kick_thपढ़ो(dlm, res);

	अगर (res)
		dlm_lockres_put(res);

	dlm_put(dlm);

	वापस status;
पूर्ण
