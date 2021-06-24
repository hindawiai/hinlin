<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmlock.c
 *
 * underlying calls क्रम lock creation
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */


#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
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

#समावेश "dlmconvert.h"

#घोषणा MLOG_MASK_PREFIX ML_DLM
#समावेश "../cluster/masklog.h"

अटल काष्ठा kmem_cache *dlm_lock_cache;

अटल DEFINE_SPINLOCK(dlm_cookie_lock);
अटल u64 dlm_next_cookie = 1;

अटल क्रमागत dlm_status dlm_send_remote_lock_request(काष्ठा dlm_ctxt *dlm,
					       काष्ठा dlm_lock_resource *res,
					       काष्ठा dlm_lock *lock, पूर्णांक flags);
अटल व्योम dlm_init_lock(काष्ठा dlm_lock *newlock, पूर्णांक type,
			  u8 node, u64 cookie);
अटल व्योम dlm_lock_release(काष्ठा kref *kref);
अटल व्योम dlm_lock_detach_lockres(काष्ठा dlm_lock *lock);

पूर्णांक dlm_init_lock_cache(व्योम)
अणु
	dlm_lock_cache = kmem_cache_create("o2dlm_lock",
					   माप(काष्ठा dlm_lock),
					   0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (dlm_lock_cache == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम dlm_destroy_lock_cache(व्योम)
अणु
	kmem_cache_destroy(dlm_lock_cache);
पूर्ण

/* Tell us whether we can grant a new lock request.
 * locking:
 *   caller needs:  res->spinlock
 *   taken:         none
 *   held on निकास:  none
 * वापसs: 1 अगर the lock can be granted, 0 otherwise.
 */
अटल पूर्णांक dlm_can_grant_new_lock(काष्ठा dlm_lock_resource *res,
				  काष्ठा dlm_lock *lock)
अणु
	काष्ठा dlm_lock *पंचांगplock;

	list_क्रम_each_entry(पंचांगplock, &res->granted, list) अणु
		अगर (!dlm_lock_compatible(पंचांगplock->ml.type, lock->ml.type))
			वापस 0;
	पूर्ण

	list_क्रम_each_entry(पंचांगplock, &res->converting, list) अणु
		अगर (!dlm_lock_compatible(पंचांगplock->ml.type, lock->ml.type))
			वापस 0;
		अगर (!dlm_lock_compatible(पंचांगplock->ml.convert_type,
					 lock->ml.type))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/* perक्रमms lock creation at the lockres master site
 * locking:
 *   caller needs:  none
 *   taken:         takes and drops res->spinlock
 *   held on निकास:  none
 * वापसs: DLM_NORMAL, DLM_NOTQUEUED
 */
अटल क्रमागत dlm_status dlmlock_master(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_lock_resource *res,
				      काष्ठा dlm_lock *lock, पूर्णांक flags)
अणु
	पूर्णांक call_ast = 0, kick_thपढ़ो = 0;
	क्रमागत dlm_status status = DLM_NORMAL;

	mlog(0, "type=%d\n", lock->ml.type);

	spin_lock(&res->spinlock);
	/* अगर called from dlm_create_lock_handler, need to
	 * ensure it will not sleep in dlm_रुको_on_lockres */
	status = __dlm_lockres_state_to_status(res);
	अगर (status != DLM_NORMAL &&
	    lock->ml.node != dlm->node_num) अणु
		/* erf.  state changed after lock was dropped. */
		spin_unlock(&res->spinlock);
		dlm_error(status);
		वापस status;
	पूर्ण
	__dlm_रुको_on_lockres(res);
	__dlm_lockres_reserve_ast(res);

	अगर (dlm_can_grant_new_lock(res, lock)) अणु
		mlog(0, "I can grant this lock right away\n");
		/* got it right away */
		lock->lksb->status = DLM_NORMAL;
		status = DLM_NORMAL;
		dlm_lock_get(lock);
		list_add_tail(&lock->list, &res->granted);

		/* क्रम the recovery lock, we can't allow the ast
		 * to be queued since the dlmthपढ़ो is alपढ़ोy
		 * frozen.  but the recovery lock is always locked
		 * with LKM_NOQUEUE so we करो not need the ast in
		 * this special हाल */
		अगर (!dlm_is_recovery_lock(res->lockname.name,
					  res->lockname.len)) अणु
			kick_thपढ़ो = 1;
			call_ast = 1;
		पूर्ण अन्यथा अणु
			mlog(0, "%s: returning DLM_NORMAL to "
			     "node %u for reco lock\n", dlm->name,
			     lock->ml.node);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* क्रम NOQUEUE request, unless we get the
		 * lock right away, वापस DLM_NOTQUEUED */
		अगर (flags & LKM_NOQUEUE) अणु
			status = DLM_NOTQUEUED;
			अगर (dlm_is_recovery_lock(res->lockname.name,
						 res->lockname.len)) अणु
				mlog(0, "%s: returning NOTQUEUED to "
				     "node %u for reco lock\n", dlm->name,
				     lock->ml.node);
			पूर्ण
		पूर्ण अन्यथा अणु
			status = DLM_NORMAL;
			dlm_lock_get(lock);
			list_add_tail(&lock->list, &res->blocked);
			kick_thपढ़ो = 1;
		पूर्ण
	पूर्ण

	spin_unlock(&res->spinlock);
	wake_up(&res->wq);

	/* either queue the ast or release it */
	अगर (call_ast)
		dlm_queue_ast(dlm, lock);
	अन्यथा
		dlm_lockres_release_ast(dlm, res);

	dlm_lockres_calc_usage(dlm, res);
	अगर (kick_thपढ़ो)
		dlm_kick_thपढ़ो(dlm, res);

	वापस status;
पूर्ण

व्योम dlm_revert_pending_lock(काष्ठा dlm_lock_resource *res,
			     काष्ठा dlm_lock *lock)
अणु
	/* हटाओ from local queue अगर it failed */
	list_del_init(&lock->list);
	lock->lksb->flags &= ~DLM_LKSB_GET_LVB;
पूर्ण


/*
 * locking:
 *   caller needs:  none
 *   taken:         takes and drops res->spinlock
 *   held on निकास:  none
 * वापसs: DLM_DENIED, DLM_RECOVERING, or net status
 */
अटल क्रमागत dlm_status dlmlock_remote(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_lock_resource *res,
				      काष्ठा dlm_lock *lock, पूर्णांक flags)
अणु
	क्रमागत dlm_status status = DLM_DENIED;
	पूर्णांक lockres_changed = 1;

	mlog(0, "type=%d, lockres %.*s, flags = 0x%x\n",
	     lock->ml.type, res->lockname.len,
	     res->lockname.name, flags);

	/*
	 * Wait अगर resource is getting recovered, remastered, etc.
	 * If the resource was remastered and new owner is self, then निकास.
	 */
	spin_lock(&res->spinlock);
	__dlm_रुको_on_lockres(res);
	अगर (res->owner == dlm->node_num) अणु
		spin_unlock(&res->spinlock);
		वापस DLM_RECOVERING;
	पूर्ण
	res->state |= DLM_LOCK_RES_IN_PROGRESS;

	/* add lock to local (secondary) queue */
	dlm_lock_get(lock);
	list_add_tail(&lock->list, &res->blocked);
	lock->lock_pending = 1;
	spin_unlock(&res->spinlock);

	/* spec seems to say that you will get DLM_NORMAL when the lock
	 * has been queued, meaning we need to रुको क्रम a reply here. */
	status = dlm_send_remote_lock_request(dlm, res, lock, flags);

	spin_lock(&res->spinlock);
	res->state &= ~DLM_LOCK_RES_IN_PROGRESS;
	lock->lock_pending = 0;
	अगर (status != DLM_NORMAL) अणु
		अगर (status == DLM_RECOVERING &&
		    dlm_is_recovery_lock(res->lockname.name,
					 res->lockname.len)) अणु
			/* recovery lock was mastered by dead node.
			 * we need to have calc_usage shoot करोwn this
			 * lockres and completely remaster it. */
			mlog(0, "%s: recovery lock was owned by "
			     "dead node %u, remaster it now.\n",
			     dlm->name, res->owner);
		पूर्ण अन्यथा अगर (status != DLM_NOTQUEUED) अणु
			/*
			 * DO NOT call calc_usage, as this would unhash
			 * the remote lockres beक्रमe we ever get to use
			 * it.  treat as अगर we never made any change to
			 * the lockres.
			 */
			lockres_changed = 0;
			dlm_error(status);
		पूर्ण
		dlm_revert_pending_lock(res, lock);
		dlm_lock_put(lock);
	पूर्ण अन्यथा अगर (dlm_is_recovery_lock(res->lockname.name,
					res->lockname.len)) अणु
		/* special हाल क्रम the $RECOVERY lock.
		 * there will never be an AST delivered to put
		 * this lock on the proper secondary queue
		 * (granted), so करो it manually. */
		mlog(0, "%s: $RECOVERY lock for this node (%u) is "
		     "mastered by %u; got lock, manually granting (no ast)\n",
		     dlm->name, dlm->node_num, res->owner);
		list_move_tail(&lock->list, &res->granted);
	पूर्ण
	spin_unlock(&res->spinlock);

	अगर (lockres_changed)
		dlm_lockres_calc_usage(dlm, res);

	wake_up(&res->wq);
	वापस status;
पूर्ण


/* क्रम remote lock creation.
 * locking:
 *   caller needs:  none, but need res->state & DLM_LOCK_RES_IN_PROGRESS
 *   taken:         none
 *   held on निकास:  none
 * वापसs: DLM_NOLOCKMGR, or net status
 */
अटल क्रमागत dlm_status dlm_send_remote_lock_request(काष्ठा dlm_ctxt *dlm,
					       काष्ठा dlm_lock_resource *res,
					       काष्ठा dlm_lock *lock, पूर्णांक flags)
अणु
	काष्ठा dlm_create_lock create;
	पूर्णांक पंचांगpret, status = 0;
	क्रमागत dlm_status ret;

	स_रखो(&create, 0, माप(create));
	create.node_idx = dlm->node_num;
	create.requested_type = lock->ml.type;
	create.cookie = lock->ml.cookie;
	create.namelen = res->lockname.len;
	create.flags = cpu_to_be32(flags);
	स_नकल(create.name, res->lockname.name, create.namelen);

	पंचांगpret = o2net_send_message(DLM_CREATE_LOCK_MSG, dlm->key, &create,
				    माप(create), res->owner, &status);
	अगर (पंचांगpret >= 0) अणु
		ret = status;
		अगर (ret == DLM_REJECTED) अणु
			mlog(ML_ERROR, "%s: res %.*s, Stale lockres no longer "
			     "owned by node %u. That node is coming back up "
			     "currently.\n", dlm->name, create.namelen,
			     create.name, res->owner);
			dlm_prपूर्णांक_one_lock_resource(res);
			BUG();
		पूर्ण
	पूर्ण अन्यथा अणु
		mlog(ML_ERROR, "%s: res %.*s, Error %d send CREATE LOCK to "
		     "node %u\n", dlm->name, create.namelen, create.name,
		     पंचांगpret, res->owner);
		अगर (dlm_is_host_करोwn(पंचांगpret))
			ret = DLM_RECOVERING;
		अन्यथा
			ret = dlm_err_to_dlm_status(पंचांगpret);
	पूर्ण

	वापस ret;
पूर्ण

व्योम dlm_lock_get(काष्ठा dlm_lock *lock)
अणु
	kref_get(&lock->lock_refs);
पूर्ण

व्योम dlm_lock_put(काष्ठा dlm_lock *lock)
अणु
	kref_put(&lock->lock_refs, dlm_lock_release);
पूर्ण

अटल व्योम dlm_lock_release(काष्ठा kref *kref)
अणु
	काष्ठा dlm_lock *lock;

	lock = container_of(kref, काष्ठा dlm_lock, lock_refs);

	BUG_ON(!list_empty(&lock->list));
	BUG_ON(!list_empty(&lock->ast_list));
	BUG_ON(!list_empty(&lock->bast_list));
	BUG_ON(lock->ast_pending);
	BUG_ON(lock->bast_pending);

	dlm_lock_detach_lockres(lock);

	अगर (lock->lksb_kernel_allocated) अणु
		mlog(0, "freeing kernel-allocated lksb\n");
		kमुक्त(lock->lksb);
	पूर्ण
	kmem_cache_मुक्त(dlm_lock_cache, lock);
पूर्ण

/* associate a lock with it's lockres, getting a ref on the lockres */
व्योम dlm_lock_attach_lockres(काष्ठा dlm_lock *lock,
			     काष्ठा dlm_lock_resource *res)
अणु
	dlm_lockres_get(res);
	lock->lockres = res;
पूर्ण

/* drop ref on lockres, अगर there is still one associated with lock */
अटल व्योम dlm_lock_detach_lockres(काष्ठा dlm_lock *lock)
अणु
	काष्ठा dlm_lock_resource *res;

	res = lock->lockres;
	अगर (res) अणु
		lock->lockres = शून्य;
		mlog(0, "removing lock's lockres reference\n");
		dlm_lockres_put(res);
	पूर्ण
पूर्ण

अटल व्योम dlm_init_lock(काष्ठा dlm_lock *newlock, पूर्णांक type,
			  u8 node, u64 cookie)
अणु
	INIT_LIST_HEAD(&newlock->list);
	INIT_LIST_HEAD(&newlock->ast_list);
	INIT_LIST_HEAD(&newlock->bast_list);
	spin_lock_init(&newlock->spinlock);
	newlock->ml.type = type;
	newlock->ml.convert_type = LKM_IVMODE;
	newlock->ml.highest_blocked = LKM_IVMODE;
	newlock->ml.node = node;
	newlock->ml.pad1 = 0;
	newlock->ml.list = 0;
	newlock->ml.flags = 0;
	newlock->ast = शून्य;
	newlock->bast = शून्य;
	newlock->astdata = शून्य;
	newlock->ml.cookie = cpu_to_be64(cookie);
	newlock->ast_pending = 0;
	newlock->bast_pending = 0;
	newlock->convert_pending = 0;
	newlock->lock_pending = 0;
	newlock->unlock_pending = 0;
	newlock->cancel_pending = 0;
	newlock->lksb_kernel_allocated = 0;

	kref_init(&newlock->lock_refs);
पूर्ण

काष्ठा dlm_lock * dlm_new_lock(पूर्णांक type, u8 node, u64 cookie,
			       काष्ठा dlm_lockstatus *lksb)
अणु
	काष्ठा dlm_lock *lock;
	पूर्णांक kernel_allocated = 0;

	lock = kmem_cache_zalloc(dlm_lock_cache, GFP_NOFS);
	अगर (!lock)
		वापस शून्य;

	अगर (!lksb) अणु
		/* zero memory only अगर kernel-allocated */
		lksb = kzalloc(माप(*lksb), GFP_NOFS);
		अगर (!lksb) अणु
			kmem_cache_मुक्त(dlm_lock_cache, lock);
			वापस शून्य;
		पूर्ण
		kernel_allocated = 1;
	पूर्ण

	dlm_init_lock(lock, type, node, cookie);
	अगर (kernel_allocated)
		lock->lksb_kernel_allocated = 1;
	lock->lksb = lksb;
	lksb->lockid = lock;
	वापस lock;
पूर्ण

/* handler क्रम lock creation net message
 * locking:
 *   caller needs:  none
 *   taken:         takes and drops res->spinlock
 *   held on निकास:  none
 * वापसs: DLM_NORMAL, DLM_SYSERR, DLM_IVLOCKID, DLM_NOTQUEUED
 */
पूर्णांक dlm_create_lock_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			    व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_create_lock *create = (काष्ठा dlm_create_lock *)msg->buf;
	काष्ठा dlm_lock_resource *res = शून्य;
	काष्ठा dlm_lock *newlock = शून्य;
	काष्ठा dlm_lockstatus *lksb = शून्य;
	क्रमागत dlm_status status = DLM_NORMAL;
	अक्षर *name;
	अचिन्हित पूर्णांक namelen;

	BUG_ON(!dlm);

	अगर (!dlm_grab(dlm))
		वापस DLM_REJECTED;

	name = create->name;
	namelen = create->namelen;
	status = DLM_REJECTED;
	अगर (!dlm_करोमुख्य_fully_joined(dlm)) अणु
		mlog(ML_ERROR, "Domain %s not fully joined, but node %u is "
		     "sending a create_lock message for lock %.*s!\n",
		     dlm->name, create->node_idx, namelen, name);
		dlm_error(status);
		जाओ leave;
	पूर्ण

	status = DLM_IVBUFLEN;
	अगर (namelen > DLM_LOCKID_NAME_MAX) अणु
		dlm_error(status);
		जाओ leave;
	पूर्ण

	status = DLM_SYSERR;
	newlock = dlm_new_lock(create->requested_type,
			       create->node_idx,
			       be64_to_cpu(create->cookie), शून्य);
	अगर (!newlock) अणु
		dlm_error(status);
		जाओ leave;
	पूर्ण

	lksb = newlock->lksb;

	अगर (be32_to_cpu(create->flags) & LKM_GET_LVB) अणु
		lksb->flags |= DLM_LKSB_GET_LVB;
		mlog(0, "set DLM_LKSB_GET_LVB flag\n");
	पूर्ण

	status = DLM_IVLOCKID;
	res = dlm_lookup_lockres(dlm, name, namelen);
	अगर (!res) अणु
		dlm_error(status);
		जाओ leave;
	पूर्ण

	spin_lock(&res->spinlock);
	status = __dlm_lockres_state_to_status(res);
	spin_unlock(&res->spinlock);

	अगर (status != DLM_NORMAL) अणु
		mlog(0, "lockres recovering/migrating/in-progress\n");
		जाओ leave;
	पूर्ण

	dlm_lock_attach_lockres(newlock, res);

	status = dlmlock_master(dlm, res, newlock, be32_to_cpu(create->flags));
leave:
	अगर (status != DLM_NORMAL)
		अगर (newlock)
			dlm_lock_put(newlock);

	अगर (res)
		dlm_lockres_put(res);

	dlm_put(dlm);

	वापस status;
पूर्ण


/* fetch next node-local (u8 nodक्रमागत + u56 cookie) पूर्णांकo u64 */
अटल अंतरभूत व्योम dlm_get_next_cookie(u8 node_num, u64 *cookie)
अणु
	u64 पंचांगpnode = node_num;

	/* shअगरt single byte of node num पूर्णांकo top 8 bits */
	पंचांगpnode <<= 56;

	spin_lock(&dlm_cookie_lock);
	*cookie = (dlm_next_cookie | पंचांगpnode);
	अगर (++dlm_next_cookie & 0xff00000000000000ull) अणु
		mlog(0, "This node's cookie will now wrap!\n");
		dlm_next_cookie = 1;
	पूर्ण
	spin_unlock(&dlm_cookie_lock);
पूर्ण

क्रमागत dlm_status dlmlock(काष्ठा dlm_ctxt *dlm, पूर्णांक mode,
			काष्ठा dlm_lockstatus *lksb, पूर्णांक flags,
			स्थिर अक्षर *name, पूर्णांक namelen, dlm_astlockfunc_t *ast,
			व्योम *data, dlm_bastlockfunc_t *bast)
अणु
	क्रमागत dlm_status status;
	काष्ठा dlm_lock_resource *res = शून्य;
	काष्ठा dlm_lock *lock = शून्य;
	पूर्णांक convert = 0, recovery = 0;

	/* yes this function is a mess.
	 * TODO: clean this up.  lots of common code in the
	 *       lock and convert paths, especially in the retry blocks */
	अगर (!lksb) अणु
		dlm_error(DLM_BADARGS);
		वापस DLM_BADARGS;
	पूर्ण

	status = DLM_BADPARAM;
	अगर (mode != LKM_EXMODE && mode != LKM_PRMODE && mode != LKM_NLMODE) अणु
		dlm_error(status);
		जाओ error;
	पूर्ण

	अगर (flags & ~LKM_VALID_FLAGS) अणु
		dlm_error(status);
		जाओ error;
	पूर्ण

	convert = (flags & LKM_CONVERT);
	recovery = (flags & LKM_RECOVERY);

	अगर (recovery &&
	    (!dlm_is_recovery_lock(name, namelen) || convert) ) अणु
		dlm_error(status);
		जाओ error;
	पूर्ण
	अगर (convert && (flags & LKM_LOCAL)) अणु
		mlog(ML_ERROR, "strange LOCAL convert request!\n");
		जाओ error;
	पूर्ण

	अगर (convert) अणु
		/* CONVERT request */

		/* अगर converting, must pass in a valid dlm_lock */
		lock = lksb->lockid;
		अगर (!lock) अणु
			mlog(ML_ERROR, "NULL lock pointer in convert "
			     "request\n");
			जाओ error;
		पूर्ण

		res = lock->lockres;
		अगर (!res) अणु
			mlog(ML_ERROR, "NULL lockres pointer in convert "
			     "request\n");
			जाओ error;
		पूर्ण
		dlm_lockres_get(res);

		/* XXX: क्रम ocfs2 purposes, the ast/bast/astdata/lksb are
	 	 * अटल after the original lock call.  convert requests will
		 * ensure that everything is the same, or वापस DLM_BADARGS.
	 	 * this means that DLM_DENIED_NOASTS will never be वापसed.
	 	 */
		अगर (lock->lksb != lksb || lock->ast != ast ||
		    lock->bast != bast || lock->astdata != data) अणु
			status = DLM_BADARGS;
			mlog(ML_ERROR, "new args:  lksb=%p, ast=%p, bast=%p, "
			     "astdata=%p\n", lksb, ast, bast, data);
			mlog(ML_ERROR, "orig args: lksb=%p, ast=%p, bast=%p, "
			     "astdata=%p\n", lock->lksb, lock->ast,
			     lock->bast, lock->astdata);
			जाओ error;
		पूर्ण
retry_convert:
		dlm_रुको_क्रम_recovery(dlm);

		अगर (res->owner == dlm->node_num)
			status = dlmconvert_master(dlm, res, lock, flags, mode);
		अन्यथा
			status = dlmconvert_remote(dlm, res, lock, flags, mode);
		अगर (status == DLM_RECOVERING || status == DLM_MIGRATING ||
		    status == DLM_FORWARD) अणु
			/* क्रम now, see how this works without sleeping
			 * and just retry right away.  I suspect the reco
			 * or migration will complete fast enough that
			 * no रुकोing will be necessary */
			mlog(0, "retrying convert with migration/recovery/"
			     "in-progress\n");
			msleep(100);
			जाओ retry_convert;
		पूर्ण
	पूर्ण अन्यथा अणु
		u64 पंचांगpcookie;

		/* LOCK request */
		status = DLM_BADARGS;
		अगर (!name) अणु
			dlm_error(status);
			जाओ error;
		पूर्ण

		status = DLM_IVBUFLEN;
		अगर (namelen > DLM_LOCKID_NAME_MAX || namelen < 1) अणु
			dlm_error(status);
			जाओ error;
		पूर्ण

		dlm_get_next_cookie(dlm->node_num, &पंचांगpcookie);
		lock = dlm_new_lock(mode, dlm->node_num, पंचांगpcookie, lksb);
		अगर (!lock) अणु
			dlm_error(status);
			जाओ error;
		पूर्ण

		अगर (!recovery)
			dlm_रुको_क्रम_recovery(dlm);

		/* find or create the lock resource */
		res = dlm_get_lock_resource(dlm, name, namelen, flags);
		अगर (!res) अणु
			status = DLM_IVLOCKID;
			dlm_error(status);
			जाओ error;
		पूर्ण

		mlog(0, "type=%d, flags = 0x%x\n", mode, flags);
		mlog(0, "creating lock: lock=%p res=%p\n", lock, res);

		dlm_lock_attach_lockres(lock, res);
		lock->ast = ast;
		lock->bast = bast;
		lock->astdata = data;

retry_lock:
		अगर (flags & LKM_VALBLK) अणु
			mlog(0, "LKM_VALBLK passed by caller\n");

			/* LVB requests क्रम non PR, PW or EX locks are
			 * ignored. */
			अगर (mode < LKM_PRMODE)
				flags &= ~LKM_VALBLK;
			अन्यथा अणु
				flags |= LKM_GET_LVB;
				lock->lksb->flags |= DLM_LKSB_GET_LVB;
			पूर्ण
		पूर्ण

		अगर (res->owner == dlm->node_num)
			status = dlmlock_master(dlm, res, lock, flags);
		अन्यथा
			status = dlmlock_remote(dlm, res, lock, flags);

		अगर (status == DLM_RECOVERING || status == DLM_MIGRATING ||
		    status == DLM_FORWARD) अणु
			msleep(100);
			अगर (recovery) अणु
				अगर (status != DLM_RECOVERING)
					जाओ retry_lock;
				/* रुको to see the node go करोwn, then
				 * drop करोwn and allow the lockres to
				 * get cleaned up.  need to remaster. */
				dlm_रुको_क्रम_node_death(dlm, res->owner,
						DLM_NODE_DEATH_WAIT_MAX);
			पूर्ण अन्यथा अणु
				dlm_रुको_क्रम_recovery(dlm);
				जाओ retry_lock;
			पूर्ण
		पूर्ण

		/* Inflight taken in dlm_get_lock_resource() is dropped here */
		spin_lock(&res->spinlock);
		dlm_lockres_drop_inflight_ref(dlm, res);
		spin_unlock(&res->spinlock);

		dlm_lockres_calc_usage(dlm, res);
		dlm_kick_thपढ़ो(dlm, res);

		अगर (status != DLM_NORMAL) अणु
			lock->lksb->flags &= ~DLM_LKSB_GET_LVB;
			अगर (status != DLM_NOTQUEUED)
				dlm_error(status);
			जाओ error;
		पूर्ण
	पूर्ण

error:
	अगर (status != DLM_NORMAL) अणु
		अगर (lock && !convert)
			dlm_lock_put(lock);
		// this is kind of unnecessary
		lksb->status = status;
	पूर्ण

	/* put lockres ref from the convert path
	 * or from dlm_get_lock_resource */
	अगर (res)
		dlm_lockres_put(res);

	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(dlmlock);
