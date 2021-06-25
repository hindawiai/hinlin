<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS file locking support
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश "internal.h"

#घोषणा AFS_LOCK_GRANTED	0
#घोषणा AFS_LOCK_PENDING	1
#घोषणा AFS_LOCK_YOUR_TRY	2

काष्ठा workqueue_काष्ठा *afs_lock_manager;

अटल व्योम afs_next_locker(काष्ठा afs_vnode *vnode, पूर्णांक error);
अटल व्योम afs_fl_copy_lock(काष्ठा file_lock *new, काष्ठा file_lock *fl);
अटल व्योम afs_fl_release_निजी(काष्ठा file_lock *fl);

अटल स्थिर काष्ठा file_lock_operations afs_lock_ops = अणु
	.fl_copy_lock		= afs_fl_copy_lock,
	.fl_release_निजी	= afs_fl_release_निजी,
पूर्ण;

अटल अंतरभूत व्योम afs_set_lock_state(काष्ठा afs_vnode *vnode, क्रमागत afs_lock_state state)
अणु
	_debug("STATE %u -> %u", vnode->lock_state, state);
	vnode->lock_state = state;
पूर्ण

अटल atomic_t afs_file_lock_debug_id;

/*
 * अगर the callback is broken on this vnode, then the lock may now be available
 */
व्योम afs_lock_may_be_available(काष्ठा afs_vnode *vnode)
अणु
	_enter("{%llx:%llu}", vnode->fid.vid, vnode->fid.vnode);

	spin_lock(&vnode->lock);
	अगर (vnode->lock_state == AFS_VNODE_LOCK_WAITING_FOR_CB)
		afs_next_locker(vnode, 0);
	trace_afs_flock_ev(vnode, शून्य, afs_flock_callback_अवरोध, 0);
	spin_unlock(&vnode->lock);
पूर्ण

/*
 * the lock will समय out in 5 minutes unless we extend it, so schedule
 * extension in a bit less than that समय
 */
अटल व्योम afs_schedule_lock_extension(काष्ठा afs_vnode *vnode)
अणु
	kसमय_प्रकार expires_at, now, duration;
	u64 duration_j;

	expires_at = kसमय_add_ms(vnode->locked_at, AFS_LOCKWAIT * 1000 / 2);
	now = kसमय_get_real();
	duration = kसमय_sub(expires_at, now);
	अगर (duration <= 0)
		duration_j = 0;
	अन्यथा
		duration_j = nsecs_to_jअगरfies(kसमय_प्रकारo_ns(duration));

	queue_delayed_work(afs_lock_manager, &vnode->lock_work, duration_j);
पूर्ण

/*
 * In the हाल of successful completion of a lock operation, record the समय
 * the reply appeared and start the lock extension समयr.
 */
व्योम afs_lock_op_करोne(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode *vnode = op->file[0].vnode;

	अगर (call->error == 0) अणु
		spin_lock(&vnode->lock);
		trace_afs_flock_ev(vnode, शून्य, afs_flock_बारtamp, 0);
		vnode->locked_at = call->reply_समय;
		afs_schedule_lock_extension(vnode);
		spin_unlock(&vnode->lock);
	पूर्ण
पूर्ण

/*
 * grant one or more locks (पढ़ोlocks are allowed to jump the queue अगर the
 * first lock in the queue is itself a पढ़ोlock)
 * - the caller must hold the vnode lock
 */
अटल व्योम afs_grant_locks(काष्ठा afs_vnode *vnode)
अणु
	काष्ठा file_lock *p, *_p;
	bool exclusive = (vnode->lock_type == AFS_LOCK_WRITE);

	list_क्रम_each_entry_safe(p, _p, &vnode->pending_locks, fl_u.afs.link) अणु
		अगर (!exclusive && p->fl_type == F_WRLCK)
			जारी;

		list_move_tail(&p->fl_u.afs.link, &vnode->granted_locks);
		p->fl_u.afs.state = AFS_LOCK_GRANTED;
		trace_afs_flock_op(vnode, p, afs_flock_op_grant);
		wake_up(&p->fl_रुको);
	पूर्ण
पूर्ण

/*
 * If an error is specअगरied, reject every pending lock that matches the
 * authentication and type of the lock we failed to get.  If there are any
 * reमुख्यing lockers, try to wake up one of them to have a go.
 */
अटल व्योम afs_next_locker(काष्ठा afs_vnode *vnode, पूर्णांक error)
अणु
	काष्ठा file_lock *p, *_p, *next = शून्य;
	काष्ठा key *key = vnode->lock_key;
	अचिन्हित पूर्णांक fl_type = F_RDLCK;

	_enter("");

	अगर (vnode->lock_type == AFS_LOCK_WRITE)
		fl_type = F_WRLCK;

	list_क्रम_each_entry_safe(p, _p, &vnode->pending_locks, fl_u.afs.link) अणु
		अगर (error &&
		    p->fl_type == fl_type &&
		    afs_file_key(p->fl_file) == key) अणु
			list_del_init(&p->fl_u.afs.link);
			p->fl_u.afs.state = error;
			wake_up(&p->fl_रुको);
		पूर्ण

		/* Select the next locker to hand off to. */
		अगर (next &&
		    (next->fl_type == F_WRLCK || p->fl_type == F_RDLCK))
			जारी;
		next = p;
	पूर्ण

	vnode->lock_key = शून्य;
	key_put(key);

	अगर (next) अणु
		afs_set_lock_state(vnode, AFS_VNODE_LOCK_SETTING);
		next->fl_u.afs.state = AFS_LOCK_YOUR_TRY;
		trace_afs_flock_op(vnode, next, afs_flock_op_wake);
		wake_up(&next->fl_रुको);
	पूर्ण अन्यथा अणु
		afs_set_lock_state(vnode, AFS_VNODE_LOCK_NONE);
		trace_afs_flock_ev(vnode, शून्य, afs_flock_no_lockers, 0);
	पूर्ण

	_leave("");
पूर्ण

/*
 * Kill off all रुकोers in the the pending lock queue due to the vnode being
 * deleted.
 */
अटल व्योम afs_समाप्त_lockers_enoent(काष्ठा afs_vnode *vnode)
अणु
	काष्ठा file_lock *p;

	afs_set_lock_state(vnode, AFS_VNODE_LOCK_DELETED);

	जबतक (!list_empty(&vnode->pending_locks)) अणु
		p = list_entry(vnode->pending_locks.next,
			       काष्ठा file_lock, fl_u.afs.link);
		list_del_init(&p->fl_u.afs.link);
		p->fl_u.afs.state = -ENOENT;
		wake_up(&p->fl_रुको);
	पूर्ण

	key_put(vnode->lock_key);
	vnode->lock_key = शून्य;
पूर्ण

अटल व्योम afs_lock_success(काष्ठा afs_operation *op)
अणु
	_enter("op=%08x", op->debug_id);
	afs_vnode_commit_status(op, &op->file[0]);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_set_lock_operation = अणु
	.issue_afs_rpc	= afs_fs_set_lock,
	.issue_yfs_rpc	= yfs_fs_set_lock,
	.success	= afs_lock_success,
	.पातed	= afs_check_क्रम_remote_deletion,
पूर्ण;

/*
 * Get a lock on a file
 */
अटल पूर्णांक afs_set_lock(काष्ठा afs_vnode *vnode, काष्ठा key *key,
			afs_lock_type_t type)
अणु
	काष्ठा afs_operation *op;

	_enter("%s{%llx:%llu.%u},%x,%u",
	       vnode->volume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(key), type);

	op = afs_alloc_operation(key, vnode->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, vnode);

	op->lock.type	= type;
	op->ops		= &afs_set_lock_operation;
	वापस afs_करो_sync_operation(op);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_extend_lock_operation = अणु
	.issue_afs_rpc	= afs_fs_extend_lock,
	.issue_yfs_rpc	= yfs_fs_extend_lock,
	.success	= afs_lock_success,
पूर्ण;

/*
 * Extend a lock on a file
 */
अटल पूर्णांक afs_extend_lock(काष्ठा afs_vnode *vnode, काष्ठा key *key)
अणु
	काष्ठा afs_operation *op;

	_enter("%s{%llx:%llu.%u},%x",
	       vnode->volume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(key));

	op = afs_alloc_operation(key, vnode->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, vnode);

	op->flags	|= AFS_OPERATION_UNINTR;
	op->ops		= &afs_extend_lock_operation;
	वापस afs_करो_sync_operation(op);
पूर्ण

अटल स्थिर काष्ठा afs_operation_ops afs_release_lock_operation = अणु
	.issue_afs_rpc	= afs_fs_release_lock,
	.issue_yfs_rpc	= yfs_fs_release_lock,
	.success	= afs_lock_success,
पूर्ण;

/*
 * Release a lock on a file
 */
अटल पूर्णांक afs_release_lock(काष्ठा afs_vnode *vnode, काष्ठा key *key)
अणु
	काष्ठा afs_operation *op;

	_enter("%s{%llx:%llu.%u},%x",
	       vnode->volume->name,
	       vnode->fid.vid,
	       vnode->fid.vnode,
	       vnode->fid.unique,
	       key_serial(key));

	op = afs_alloc_operation(key, vnode->volume);
	अगर (IS_ERR(op))
		वापस PTR_ERR(op);

	afs_op_set_vnode(op, 0, vnode);

	op->flags	|= AFS_OPERATION_UNINTR;
	op->ops		= &afs_release_lock_operation;
	वापस afs_करो_sync_operation(op);
पूर्ण

/*
 * करो work क्रम a lock, including:
 * - probing क्रम a lock we're waiting on but didn't get immediately
 * - extending a lock that's बंद to timing out
 */
व्योम afs_lock_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा afs_vnode *vnode =
		container_of(work, काष्ठा afs_vnode, lock_work.work);
	काष्ठा key *key;
	पूर्णांक ret;

	_enter("{%llx:%llu}", vnode->fid.vid, vnode->fid.vnode);

	spin_lock(&vnode->lock);

again:
	_debug("wstate %u for %p", vnode->lock_state, vnode);
	चयन (vnode->lock_state) अणु
	हाल AFS_VNODE_LOCK_NEED_UNLOCK:
		afs_set_lock_state(vnode, AFS_VNODE_LOCK_UNLOCKING);
		trace_afs_flock_ev(vnode, शून्य, afs_flock_work_unlocking, 0);
		spin_unlock(&vnode->lock);

		/* attempt to release the server lock; अगर it fails, we just
		 * रुको 5 minutes and it'll expire anyway */
		ret = afs_release_lock(vnode, vnode->lock_key);
		अगर (ret < 0 && vnode->lock_state != AFS_VNODE_LOCK_DELETED) अणु
			trace_afs_flock_ev(vnode, शून्य, afs_flock_release_fail,
					   ret);
			prपूर्णांकk(KERN_WARNING "AFS:"
			       " Failed to release lock on {%llx:%llx} error %d\n",
			       vnode->fid.vid, vnode->fid.vnode, ret);
		पूर्ण

		spin_lock(&vnode->lock);
		अगर (ret == -ENOENT)
			afs_समाप्त_lockers_enoent(vnode);
		अन्यथा
			afs_next_locker(vnode, 0);
		spin_unlock(&vnode->lock);
		वापस;

	/* If we've alपढ़ोy got a lock, then it must be समय to extend that
	 * lock as AFS locks समय out after 5 minutes.
	 */
	हाल AFS_VNODE_LOCK_GRANTED:
		_debug("extend");

		ASSERT(!list_empty(&vnode->granted_locks));

		key = key_get(vnode->lock_key);
		afs_set_lock_state(vnode, AFS_VNODE_LOCK_EXTENDING);
		trace_afs_flock_ev(vnode, शून्य, afs_flock_work_extending, 0);
		spin_unlock(&vnode->lock);

		ret = afs_extend_lock(vnode, key); /* RPC */
		key_put(key);

		अगर (ret < 0) अणु
			trace_afs_flock_ev(vnode, शून्य, afs_flock_extend_fail,
					   ret);
			pr_warn("AFS: Failed to extend lock on {%llx:%llx} error %d\n",
				vnode->fid.vid, vnode->fid.vnode, ret);
		पूर्ण

		spin_lock(&vnode->lock);

		अगर (ret == -ENOENT) अणु
			afs_समाप्त_lockers_enoent(vnode);
			spin_unlock(&vnode->lock);
			वापस;
		पूर्ण

		अगर (vnode->lock_state != AFS_VNODE_LOCK_EXTENDING)
			जाओ again;
		afs_set_lock_state(vnode, AFS_VNODE_LOCK_GRANTED);

		अगर (ret != 0)
			queue_delayed_work(afs_lock_manager, &vnode->lock_work,
					   HZ * 10);
		spin_unlock(&vnode->lock);
		_leave(" [ext]");
		वापस;

	/* If we're waiting for a callback to indicate lock release, we can't
	 * actually rely on this, so need to recheck at regular पूर्णांकervals.  The
	 * problem is that the server might not notअगरy us अगर the lock just
	 * expires (say because a client died) rather than being explicitly
	 * released.
	 */
	हाल AFS_VNODE_LOCK_WAITING_FOR_CB:
		_debug("retry");
		afs_next_locker(vnode, 0);
		spin_unlock(&vnode->lock);
		वापस;

	हाल AFS_VNODE_LOCK_DELETED:
		afs_समाप्त_lockers_enoent(vnode);
		spin_unlock(&vnode->lock);
		वापस;

	शेष:
		/* Looks like a lock request was withdrawn. */
		spin_unlock(&vnode->lock);
		_leave(" [no]");
		वापस;
	पूर्ण
पूर्ण

/*
 * pass responsibility क्रम the unlocking of a vnode on the server to the
 * manager thपढ़ो, lest a pending संकेत in the calling thपढ़ो पूर्णांकerrupt
 * AF_RXRPC
 * - the caller must hold the vnode lock
 */
अटल व्योम afs_defer_unlock(काष्ठा afs_vnode *vnode)
अणु
	_enter("%u", vnode->lock_state);

	अगर (list_empty(&vnode->granted_locks) &&
	    (vnode->lock_state == AFS_VNODE_LOCK_GRANTED ||
	     vnode->lock_state == AFS_VNODE_LOCK_EXTENDING)) अणु
		cancel_delayed_work(&vnode->lock_work);

		afs_set_lock_state(vnode, AFS_VNODE_LOCK_NEED_UNLOCK);
		trace_afs_flock_ev(vnode, शून्य, afs_flock_defer_unlock, 0);
		queue_delayed_work(afs_lock_manager, &vnode->lock_work, 0);
	पूर्ण
पूर्ण

/*
 * Check that our view of the file metadata is up to date and check to see
 * whether we think that we have a locking permit.
 */
अटल पूर्णांक afs_करो_setlk_check(काष्ठा afs_vnode *vnode, काष्ठा key *key,
			      क्रमागत afs_flock_mode mode, afs_lock_type_t type)
अणु
	afs_access_t access;
	पूर्णांक ret;

	/* Make sure we've got a callback on this file and that our view of the
	 * data version is up to date.
	 */
	ret = afs_validate(vnode, key);
	अगर (ret < 0)
		वापस ret;

	/* Check the permission set to see अगर we're actually going to be
	 * allowed to get a lock on this file.
	 */
	ret = afs_check_permit(vnode, key, &access);
	अगर (ret < 0)
		वापस ret;

	/* At a rough estimation, you need LOCK, WRITE or INSERT perm to
	 * पढ़ो-lock a file and WRITE or INSERT perm to ग_लिखो-lock a file.
	 *
	 * We can't rely on the server to करो this क्रम us since अगर we want to
	 * share a पढ़ो lock that we alपढ़ोy have, we won't go the server.
	 */
	अगर (type == AFS_LOCK_READ) अणु
		अगर (!(access & (AFS_ACE_INSERT | AFS_ACE_WRITE | AFS_ACE_LOCK)))
			वापस -EACCES;
	पूर्ण अन्यथा अणु
		अगर (!(access & (AFS_ACE_INSERT | AFS_ACE_WRITE)))
			वापस -EACCES;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * request a lock on a file on the server
 */
अटल पूर्णांक afs_करो_setlk(काष्ठा file *file, काष्ठा file_lock *fl)
अणु
	काष्ठा inode *inode = locks_inode(file);
	काष्ठा afs_vnode *vnode = AFS_FS_I(inode);
	क्रमागत afs_flock_mode mode = AFS_FS_S(inode->i_sb)->flock_mode;
	afs_lock_type_t type;
	काष्ठा key *key = afs_file_key(file);
	bool partial, no_server_lock = false;
	पूर्णांक ret;

	अगर (mode == afs_flock_mode_unset)
		mode = afs_flock_mode_खोलोafs;

	_enter("{%llx:%llu},%llu-%llu,%u,%u",
	       vnode->fid.vid, vnode->fid.vnode,
	       fl->fl_start, fl->fl_end, fl->fl_type, mode);

	fl->fl_ops = &afs_lock_ops;
	INIT_LIST_HEAD(&fl->fl_u.afs.link);
	fl->fl_u.afs.state = AFS_LOCK_PENDING;

	partial = (fl->fl_start != 0 || fl->fl_end != OFFSET_MAX);
	type = (fl->fl_type == F_RDLCK) ? AFS_LOCK_READ : AFS_LOCK_WRITE;
	अगर (mode == afs_flock_mode_ग_लिखो && partial)
		type = AFS_LOCK_WRITE;

	ret = afs_करो_setlk_check(vnode, key, mode, type);
	अगर (ret < 0)
		वापस ret;

	trace_afs_flock_op(vnode, fl, afs_flock_op_set_lock);

	/* AFS3 protocol only supports full-file locks and करोesn't provide any
	 * method of upgrade/करोwngrade, so we need to emulate क्रम partial-file
	 * locks.
	 *
	 * The OpenAFS client only माला_लो a server lock क्रम a full-file lock and
	 * keeps partial-file locks local.  Allow this behaviour to be emulated
	 * (as the शेष).
	 */
	अगर (mode == afs_flock_mode_local ||
	    (partial && mode == afs_flock_mode_खोलोafs)) अणु
		no_server_lock = true;
		जाओ skip_server_lock;
	पूर्ण

	spin_lock(&vnode->lock);
	list_add_tail(&fl->fl_u.afs.link, &vnode->pending_locks);

	ret = -ENOENT;
	अगर (vnode->lock_state == AFS_VNODE_LOCK_DELETED)
		जाओ error_unlock;

	/* If we've alपढ़ोy got a lock on the server then try to move to having
	 * the VFS grant the requested lock.  Note that this means that other
	 * clients may get starved out.
	 */
	_debug("try %u", vnode->lock_state);
	अगर (vnode->lock_state == AFS_VNODE_LOCK_GRANTED) अणु
		अगर (type == AFS_LOCK_READ) अणु
			_debug("instant readlock");
			list_move_tail(&fl->fl_u.afs.link, &vnode->granted_locks);
			fl->fl_u.afs.state = AFS_LOCK_GRANTED;
			जाओ vnode_is_locked_u;
		पूर्ण

		अगर (vnode->lock_type == AFS_LOCK_WRITE) अणु
			_debug("instant writelock");
			list_move_tail(&fl->fl_u.afs.link, &vnode->granted_locks);
			fl->fl_u.afs.state = AFS_LOCK_GRANTED;
			जाओ vnode_is_locked_u;
		पूर्ण
	पूर्ण

	अगर (vnode->lock_state == AFS_VNODE_LOCK_NONE &&
	    !(fl->fl_flags & FL_SLEEP)) अणु
		ret = -EAGAIN;
		अगर (type == AFS_LOCK_READ) अणु
			अगर (vnode->status.lock_count == -1)
				जाओ lock_is_contended; /* Write locked */
		पूर्ण अन्यथा अणु
			अगर (vnode->status.lock_count != 0)
				जाओ lock_is_contended; /* Locked */
		पूर्ण
	पूर्ण

	अगर (vnode->lock_state != AFS_VNODE_LOCK_NONE)
		जाओ need_to_रुको;

try_to_lock:
	/* We करोn't have a lock on this vnode and we aren't currently रुकोing
	 * क्रम one either, so ask the server क्रम a lock.
	 *
	 * Note that we need to be careful अगर we get पूर्णांकerrupted by a संकेत
	 * after dispatching the request as we may still get the lock, even
	 * though we करोn't wait for the reply (it's not too bad a problem - the
	 * lock will expire in 5 mins anyway).
	 */
	trace_afs_flock_ev(vnode, fl, afs_flock_try_to_lock, 0);
	vnode->lock_key = key_get(key);
	vnode->lock_type = type;
	afs_set_lock_state(vnode, AFS_VNODE_LOCK_SETTING);
	spin_unlock(&vnode->lock);

	ret = afs_set_lock(vnode, key, type); /* RPC */

	spin_lock(&vnode->lock);
	चयन (ret) अणु
	हाल -EKEYREJECTED:
	हाल -EKEYEXPIRED:
	हाल -EKEYREVOKED:
	हाल -EPERM:
	हाल -EACCES:
		fl->fl_u.afs.state = ret;
		trace_afs_flock_ev(vnode, fl, afs_flock_fail_perm, ret);
		list_del_init(&fl->fl_u.afs.link);
		afs_next_locker(vnode, ret);
		जाओ error_unlock;

	हाल -ENOENT:
		fl->fl_u.afs.state = ret;
		trace_afs_flock_ev(vnode, fl, afs_flock_fail_other, ret);
		list_del_init(&fl->fl_u.afs.link);
		afs_समाप्त_lockers_enoent(vnode);
		जाओ error_unlock;

	शेष:
		fl->fl_u.afs.state = ret;
		trace_afs_flock_ev(vnode, fl, afs_flock_fail_other, ret);
		list_del_init(&fl->fl_u.afs.link);
		afs_next_locker(vnode, 0);
		जाओ error_unlock;

	हाल -EWOULDBLOCK:
		/* The server करोesn't have a lock-रुकोing queue, so the client
		 * will have to retry.  The server will अवरोध the outstanding
		 * callbacks on a file when a lock is released.
		 */
		ASSERT(list_empty(&vnode->granted_locks));
		ASSERTCMP(vnode->pending_locks.next, ==, &fl->fl_u.afs.link);
		जाओ lock_is_contended;

	हाल 0:
		afs_set_lock_state(vnode, AFS_VNODE_LOCK_GRANTED);
		trace_afs_flock_ev(vnode, fl, afs_flock_acquired, type);
		afs_grant_locks(vnode);
		जाओ vnode_is_locked_u;
	पूर्ण

vnode_is_locked_u:
	spin_unlock(&vnode->lock);
vnode_is_locked:
	/* the lock has been granted by the server... */
	ASSERTCMP(fl->fl_u.afs.state, ==, AFS_LOCK_GRANTED);

skip_server_lock:
	/* ... but the VFS still needs to distribute access on this client. */
	trace_afs_flock_ev(vnode, fl, afs_flock_vfs_locking, 0);
	ret = locks_lock_file_रुको(file, fl);
	trace_afs_flock_ev(vnode, fl, afs_flock_vfs_lock, ret);
	अगर (ret < 0)
		जाओ vfs_rejected_lock;

	/* Again, make sure we've got a callback on this file and, again, make
	 * sure that our view of the data version is up to date (we ignore
	 * errors incurred here and deal with the consequences अन्यथाwhere).
	 */
	afs_validate(vnode, key);
	_leave(" = 0");
	वापस 0;

lock_is_contended:
	अगर (!(fl->fl_flags & FL_SLEEP)) अणु
		list_del_init(&fl->fl_u.afs.link);
		afs_next_locker(vnode, 0);
		ret = -EAGAIN;
		जाओ error_unlock;
	पूर्ण

	afs_set_lock_state(vnode, AFS_VNODE_LOCK_WAITING_FOR_CB);
	trace_afs_flock_ev(vnode, fl, afs_flock_would_block, ret);
	queue_delayed_work(afs_lock_manager, &vnode->lock_work, HZ * 5);

need_to_रुको:
	/* We're going to have to wait.  Either this client doesn't have a lock
	 * on the server yet and we need to रुको क्रम a callback to occur, or
	 * the client करोes have a lock on the server, but it's shared and we
	 * need an exclusive lock.
	 */
	spin_unlock(&vnode->lock);

	trace_afs_flock_ev(vnode, fl, afs_flock_रुकोing, 0);
	ret = रुको_event_पूर्णांकerruptible(fl->fl_रुको,
				       fl->fl_u.afs.state != AFS_LOCK_PENDING);
	trace_afs_flock_ev(vnode, fl, afs_flock_रुकोed, ret);

	अगर (fl->fl_u.afs.state >= 0 && fl->fl_u.afs.state != AFS_LOCK_GRANTED) अणु
		spin_lock(&vnode->lock);

		चयन (fl->fl_u.afs.state) अणु
		हाल AFS_LOCK_YOUR_TRY:
			fl->fl_u.afs.state = AFS_LOCK_PENDING;
			जाओ try_to_lock;
		हाल AFS_LOCK_PENDING:
			अगर (ret > 0) अणु
				/* We need to retry the lock.  We may not be
				 * notअगरied by the server अगर it just expired
				 * rather than being released.
				 */
				ASSERTCMP(vnode->lock_state, ==, AFS_VNODE_LOCK_WAITING_FOR_CB);
				afs_set_lock_state(vnode, AFS_VNODE_LOCK_SETTING);
				fl->fl_u.afs.state = AFS_LOCK_PENDING;
				जाओ try_to_lock;
			पूर्ण
			जाओ error_unlock;
		हाल AFS_LOCK_GRANTED:
		शेष:
			अवरोध;
		पूर्ण

		spin_unlock(&vnode->lock);
	पूर्ण

	अगर (fl->fl_u.afs.state == AFS_LOCK_GRANTED)
		जाओ vnode_is_locked;
	ret = fl->fl_u.afs.state;
	जाओ error;

vfs_rejected_lock:
	/* The VFS rejected the lock we just obtained, so we have to discard
	 * what we just got.  We defer this to the lock manager work item to
	 * deal with.
	 */
	_debug("vfs refused %d", ret);
	अगर (no_server_lock)
		जाओ error;
	spin_lock(&vnode->lock);
	list_del_init(&fl->fl_u.afs.link);
	afs_defer_unlock(vnode);

error_unlock:
	spin_unlock(&vnode->lock);
error:
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * unlock on a file on the server
 */
अटल पूर्णांक afs_करो_unlk(काष्ठा file *file, काष्ठा file_lock *fl)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(locks_inode(file));
	पूर्णांक ret;

	_enter("{%llx:%llu},%u", vnode->fid.vid, vnode->fid.vnode, fl->fl_type);

	trace_afs_flock_op(vnode, fl, afs_flock_op_unlock);

	/* Flush all pending ग_लिखोs beक्रमe करोing anything with locks. */
	vfs_fsync(file, 0);

	ret = locks_lock_file_रुको(file, fl);
	_leave(" = %d [%u]", ret, vnode->lock_state);
	वापस ret;
पूर्ण

/*
 * वापस inक्रमmation about a lock we currently hold, अगर indeed we hold one
 */
अटल पूर्णांक afs_करो_getlk(काष्ठा file *file, काष्ठा file_lock *fl)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(locks_inode(file));
	काष्ठा key *key = afs_file_key(file);
	पूर्णांक ret, lock_count;

	_enter("");

	अगर (vnode->lock_state == AFS_VNODE_LOCK_DELETED)
		वापस -ENOENT;

	fl->fl_type = F_UNLCK;

	/* check local lock records first */
	posix_test_lock(file, fl);
	अगर (fl->fl_type == F_UNLCK) अणु
		/* no local locks; consult the server */
		ret = afs_fetch_status(vnode, key, false, शून्य);
		अगर (ret < 0)
			जाओ error;

		lock_count = READ_ONCE(vnode->status.lock_count);
		अगर (lock_count != 0) अणु
			अगर (lock_count > 0)
				fl->fl_type = F_RDLCK;
			अन्यथा
				fl->fl_type = F_WRLCK;
			fl->fl_start = 0;
			fl->fl_end = OFFSET_MAX;
			fl->fl_pid = 0;
		पूर्ण
	पूर्ण

	ret = 0;
error:
	_leave(" = %d [%hd]", ret, fl->fl_type);
	वापस ret;
पूर्ण

/*
 * manage POSIX locks on a file
 */
पूर्णांक afs_lock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(locks_inode(file));
	क्रमागत afs_flock_operation op;
	पूर्णांक ret;

	_enter("{%llx:%llu},%d,{t=%x,fl=%x,r=%Ld:%Ld}",
	       vnode->fid.vid, vnode->fid.vnode, cmd,
	       fl->fl_type, fl->fl_flags,
	       (दीर्घ दीर्घ) fl->fl_start, (दीर्घ दीर्घ) fl->fl_end);

	/* AFS करोesn't support mandatory locks */
	अगर (__mandatory_lock(&vnode->vfs_inode) && fl->fl_type != F_UNLCK)
		वापस -ENOLCK;

	अगर (IS_GETLK(cmd))
		वापस afs_करो_getlk(file, fl);

	fl->fl_u.afs.debug_id = atomic_inc_वापस(&afs_file_lock_debug_id);
	trace_afs_flock_op(vnode, fl, afs_flock_op_lock);

	अगर (fl->fl_type == F_UNLCK)
		ret = afs_करो_unlk(file, fl);
	अन्यथा
		ret = afs_करो_setlk(file, fl);

	चयन (ret) अणु
	हाल 0:		op = afs_flock_op_वापस_ok; अवरोध;
	हाल -EAGAIN:	op = afs_flock_op_वापस_eagain; अवरोध;
	हाल -EDEADLK:	op = afs_flock_op_वापस_edeadlk; अवरोध;
	शेष:	op = afs_flock_op_वापस_error; अवरोध;
	पूर्ण
	trace_afs_flock_op(vnode, fl, op);
	वापस ret;
पूर्ण

/*
 * manage FLOCK locks on a file
 */
पूर्णांक afs_flock(काष्ठा file *file, पूर्णांक cmd, काष्ठा file_lock *fl)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(locks_inode(file));
	क्रमागत afs_flock_operation op;
	पूर्णांक ret;

	_enter("{%llx:%llu},%d,{t=%x,fl=%x}",
	       vnode->fid.vid, vnode->fid.vnode, cmd,
	       fl->fl_type, fl->fl_flags);

	/*
	 * No BSD flocks over NFS allowed.
	 * Note: we could try to fake a POSIX lock request here by
	 * using ((u32) filp | 0x80000000) or some such as the pid.
	 * Not sure whether that would be unique, though, or whether
	 * that would अवरोध in other places.
	 */
	अगर (!(fl->fl_flags & FL_FLOCK))
		वापस -ENOLCK;

	fl->fl_u.afs.debug_id = atomic_inc_वापस(&afs_file_lock_debug_id);
	trace_afs_flock_op(vnode, fl, afs_flock_op_flock);

	/* we're simulating flock() locks using posix locks on the server */
	अगर (fl->fl_type == F_UNLCK)
		ret = afs_करो_unlk(file, fl);
	अन्यथा
		ret = afs_करो_setlk(file, fl);

	चयन (ret) अणु
	हाल 0:		op = afs_flock_op_वापस_ok; अवरोध;
	हाल -EAGAIN:	op = afs_flock_op_वापस_eagain; अवरोध;
	हाल -EDEADLK:	op = afs_flock_op_वापस_edeadlk; अवरोध;
	शेष:	op = afs_flock_op_वापस_error; अवरोध;
	पूर्ण
	trace_afs_flock_op(vnode, fl, op);
	वापस ret;
पूर्ण

/*
 * the POSIX lock management core VFS code copies the lock record and adds the
 * copy पूर्णांकo its own list, so we need to add that copy to the vnode's lock
 * queue in the same place as the original (which will be deleted लघुly
 * after)
 */
अटल व्योम afs_fl_copy_lock(काष्ठा file_lock *new, काष्ठा file_lock *fl)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(locks_inode(fl->fl_file));

	_enter("");

	new->fl_u.afs.debug_id = atomic_inc_वापस(&afs_file_lock_debug_id);

	spin_lock(&vnode->lock);
	trace_afs_flock_op(vnode, new, afs_flock_op_copy_lock);
	list_add(&new->fl_u.afs.link, &fl->fl_u.afs.link);
	spin_unlock(&vnode->lock);
पूर्ण

/*
 * need to हटाओ this lock from the vnode queue when it's हटाओd from the
 * VFS's list
 */
अटल व्योम afs_fl_release_निजी(काष्ठा file_lock *fl)
अणु
	काष्ठा afs_vnode *vnode = AFS_FS_I(locks_inode(fl->fl_file));

	_enter("");

	spin_lock(&vnode->lock);

	trace_afs_flock_op(vnode, fl, afs_flock_op_release_lock);
	list_del_init(&fl->fl_u.afs.link);
	अगर (list_empty(&vnode->granted_locks))
		afs_defer_unlock(vnode);

	_debug("state %u for %p", vnode->lock_state, vnode);
	spin_unlock(&vnode->lock);
पूर्ण
