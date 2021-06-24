<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/lockd/svघड़ी.c
 *
 * Handling of server-side locks, mostly of the blocked variety.
 * This is the ugliest part of lockd because we tपढ़ो on very thin ice.
 * GRANT and CANCEL calls may get stuck, meet in mid-flight, etc.
 * IMNSHO पूर्णांकroducing the grant callback पूर्णांकo the NLM protocol was one
 * of the worst ideas Sun ever had. Except maybe क्रम the idea of करोing
 * NFS file locking at all.
 *
 * I'm trying hard to aव्योम race conditions by protecting most accesses
 * to a file's list of blocked locks through a semaphore. The global
 * list of blocked locks is not रक्षित in this fashion however.
 * Thereक्रमe, some functions (such as the RPC callback क्रम the async grant
 * call) move blocked locks towards the head of the list *जबतक some other
 * process might be traversing it*. This should not be a problem in
 * practice, because this will only cause functions traversing the list
 * to visit some blocks twice.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <linux/lockd/nlm.h>
#समावेश <linux/lockd/lockd.h>
#समावेश <linux/kthपढ़ो.h>

#घोषणा NLMDBG_FACILITY		NLMDBG_SVCLOCK

#अगर_घोषित CONFIG_LOCKD_V4
#घोषणा nlm_deadlock	nlm4_deadlock
#अन्यथा
#घोषणा nlm_deadlock	nlm_lck_denied
#पूर्ण_अगर

अटल व्योम nlmsvc_release_block(काष्ठा nlm_block *block);
अटल व्योम	nlmsvc_insert_block(काष्ठा nlm_block *block, अचिन्हित दीर्घ);
अटल व्योम	nlmsvc_हटाओ_block(काष्ठा nlm_block *block);

अटल पूर्णांक nlmsvc_setgrantargs(काष्ठा nlm_rqst *call, काष्ठा nlm_lock *lock);
अटल व्योम nlmsvc_मुक्तgrantargs(काष्ठा nlm_rqst *call);
अटल स्थिर काष्ठा rpc_call_ops nlmsvc_grant_ops;

/*
 * The list of blocked locks to retry
 */
अटल LIST_HEAD(nlm_blocked);
अटल DEFINE_SPINLOCK(nlm_blocked_lock);

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
अटल स्थिर अक्षर *nlmdbg_cookie2a(स्थिर काष्ठा nlm_cookie *cookie)
अणु
	/*
	 * We can get away with a अटल buffer because this is only called
	 * from lockd, which is single-thपढ़ोed.
	 */
	अटल अक्षर buf[2*NLM_MAXCOOKIELEN+1];
	अचिन्हित पूर्णांक i, len = माप(buf);
	अक्षर *p = buf;

	len--;	/* allow क्रम trailing \0 */
	अगर (len < 3)
		वापस "???";
	क्रम (i = 0 ; i < cookie->len ; i++) अणु
		अगर (len < 2) अणु
			म_नकल(p-3, "...");
			अवरोध;
		पूर्ण
		प्र_लिखो(p, "%02x", cookie->data[i]);
		p += 2;
		len -= 2;
	पूर्ण
	*p = '\0';

	वापस buf;
पूर्ण
#पूर्ण_अगर

/*
 * Insert a blocked lock पूर्णांकo the global list
 */
अटल व्योम
nlmsvc_insert_block_locked(काष्ठा nlm_block *block, अचिन्हित दीर्घ when)
अणु
	काष्ठा nlm_block *b;
	काष्ठा list_head *pos;

	dprपूर्णांकk("lockd: nlmsvc_insert_block(%p, %ld)\n", block, when);
	अगर (list_empty(&block->b_list)) अणु
		kref_get(&block->b_count);
	पूर्ण अन्यथा अणु
		list_del_init(&block->b_list);
	पूर्ण

	pos = &nlm_blocked;
	अगर (when != NLM_NEVER) अणु
		अगर ((when += jअगरfies) == NLM_NEVER)
			when ++;
		list_क्रम_each(pos, &nlm_blocked) अणु
			b = list_entry(pos, काष्ठा nlm_block, b_list);
			अगर (समय_after(b->b_when,when) || b->b_when == NLM_NEVER)
				अवरोध;
		पूर्ण
		/* On normal निकास from the loop, pos == &nlm_blocked,
		 * so we will be adding to the end of the list - good
		 */
	पूर्ण

	list_add_tail(&block->b_list, pos);
	block->b_when = when;
पूर्ण

अटल व्योम nlmsvc_insert_block(काष्ठा nlm_block *block, अचिन्हित दीर्घ when)
अणु
	spin_lock(&nlm_blocked_lock);
	nlmsvc_insert_block_locked(block, when);
	spin_unlock(&nlm_blocked_lock);
पूर्ण

/*
 * Remove a block from the global list
 */
अटल अंतरभूत व्योम
nlmsvc_हटाओ_block(काष्ठा nlm_block *block)
अणु
	अगर (!list_empty(&block->b_list)) अणु
		spin_lock(&nlm_blocked_lock);
		list_del_init(&block->b_list);
		spin_unlock(&nlm_blocked_lock);
		nlmsvc_release_block(block);
	पूर्ण
पूर्ण

/*
 * Find a block क्रम a given lock
 */
अटल काष्ठा nlm_block *
nlmsvc_lookup_block(काष्ठा nlm_file *file, काष्ठा nlm_lock *lock)
अणु
	काष्ठा nlm_block	*block;
	काष्ठा file_lock	*fl;

	dprपूर्णांकk("lockd: nlmsvc_lookup_block f=%p pd=%d %Ld-%Ld ty=%d\n",
				file, lock->fl.fl_pid,
				(दीर्घ दीर्घ)lock->fl.fl_start,
				(दीर्घ दीर्घ)lock->fl.fl_end, lock->fl.fl_type);
	list_क्रम_each_entry(block, &nlm_blocked, b_list) अणु
		fl = &block->b_call->a_args.lock.fl;
		dprपूर्णांकk("lockd: check f=%p pd=%d %Ld-%Ld ty=%d cookie=%s\n",
				block->b_file, fl->fl_pid,
				(दीर्घ दीर्घ)fl->fl_start,
				(दीर्घ दीर्घ)fl->fl_end, fl->fl_type,
				nlmdbg_cookie2a(&block->b_call->a_args.cookie));
		अगर (block->b_file == file && nlm_compare_locks(fl, &lock->fl)) अणु
			kref_get(&block->b_count);
			वापस block;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक nlm_cookie_match(काष्ठा nlm_cookie *a, काष्ठा nlm_cookie *b)
अणु
	अगर (a->len != b->len)
		वापस 0;
	अगर (स_भेद(a->data, b->data, a->len))
		वापस 0;
	वापस 1;
पूर्ण

/*
 * Find a block with a given NLM cookie.
 */
अटल अंतरभूत काष्ठा nlm_block *
nlmsvc_find_block(काष्ठा nlm_cookie *cookie)
अणु
	काष्ठा nlm_block *block;

	list_क्रम_each_entry(block, &nlm_blocked, b_list) अणु
		अगर (nlm_cookie_match(&block->b_call->a_args.cookie,cookie))
			जाओ found;
	पूर्ण

	वापस शून्य;

found:
	dprपूर्णांकk("nlmsvc_find_block(%s): block=%p\n", nlmdbg_cookie2a(cookie), block);
	kref_get(&block->b_count);
	वापस block;
पूर्ण

/*
 * Create a block and initialize it.
 *
 * Note: we explicitly set the cookie of the grant reply to that of
 * the blocked lock request. The spec explicitly mentions that the client
 * should _not_ rely on the callback containing the same cookie as the
 * request, but (as I found out later) that's because some implementations
 * करो just this. Never mind the standards comittees, they support our
 * logging industries.
 *
 * 10 years later: I hope we can safely ignore these old and broken
 * clients by now. Let's fix this so we can uniquely identअगरy an incoming
 * GRANTED_RES message by cookie, without having to rely on the client's IP
 * address. --okir
 */
अटल काष्ठा nlm_block *
nlmsvc_create_block(काष्ठा svc_rqst *rqstp, काष्ठा nlm_host *host,
		    काष्ठा nlm_file *file, काष्ठा nlm_lock *lock,
		    काष्ठा nlm_cookie *cookie)
अणु
	काष्ठा nlm_block	*block;
	काष्ठा nlm_rqst		*call = शून्य;

	call = nlm_alloc_call(host);
	अगर (call == शून्य)
		वापस शून्य;

	/* Allocate memory क्रम block, and initialize arguments */
	block = kzalloc(माप(*block), GFP_KERNEL);
	अगर (block == शून्य)
		जाओ failed;
	kref_init(&block->b_count);
	INIT_LIST_HEAD(&block->b_list);
	INIT_LIST_HEAD(&block->b_flist);

	अगर (!nlmsvc_setgrantargs(call, lock))
		जाओ failed_मुक्त;

	/* Set notअगरier function क्रम VFS, and init args */
	call->a_args.lock.fl.fl_flags |= FL_SLEEP;
	call->a_args.lock.fl.fl_lmops = &nlmsvc_lock_operations;
	nlmclnt_next_cookie(&call->a_args.cookie);

	dprपूर्णांकk("lockd: created block %p...\n", block);

	/* Create and initialize the block */
	block->b_daemon = rqstp->rq_server;
	block->b_host   = host;
	block->b_file   = file;
	file->f_count++;

	/* Add to file's list of blocks */
	list_add(&block->b_flist, &file->f_blocks);

	/* Set up RPC arguments क्रम callback */
	block->b_call = call;
	call->a_flags   = RPC_TASK_ASYNC;
	call->a_block = block;

	वापस block;

failed_मुक्त:
	kमुक्त(block);
failed:
	nlmsvc_release_call(call);
	वापस शून्य;
पूर्ण

/*
 * Delete a block.
 * It is the caller's responsibility to check whether the file
 * can be बंदd hereafter.
 */
अटल पूर्णांक nlmsvc_unlink_block(काष्ठा nlm_block *block)
अणु
	पूर्णांक status;
	dprपूर्णांकk("lockd: unlinking block %p...\n", block);

	/* Remove block from list */
	status = locks_delete_block(&block->b_call->a_args.lock.fl);
	nlmsvc_हटाओ_block(block);
	वापस status;
पूर्ण

अटल व्योम nlmsvc_मुक्त_block(काष्ठा kref *kref)
अणु
	काष्ठा nlm_block *block = container_of(kref, काष्ठा nlm_block, b_count);
	काष्ठा nlm_file		*file = block->b_file;

	dprपूर्णांकk("lockd: freeing block %p...\n", block);

	/* Remove block from file's list of blocks */
	list_del_init(&block->b_flist);
	mutex_unlock(&file->f_mutex);

	nlmsvc_मुक्तgrantargs(block->b_call);
	nlmsvc_release_call(block->b_call);
	nlm_release_file(block->b_file);
	kमुक्त(block);
पूर्ण

अटल व्योम nlmsvc_release_block(काष्ठा nlm_block *block)
अणु
	अगर (block != शून्य)
		kref_put_mutex(&block->b_count, nlmsvc_मुक्त_block, &block->b_file->f_mutex);
पूर्ण

/*
 * Loop over all blocks and delete blocks held by
 * a matching host.
 */
व्योम nlmsvc_traverse_blocks(काष्ठा nlm_host *host,
			काष्ठा nlm_file *file,
			nlm_host_match_fn_t match)
अणु
	काष्ठा nlm_block *block, *next;

restart:
	mutex_lock(&file->f_mutex);
	list_क्रम_each_entry_safe(block, next, &file->f_blocks, b_flist) अणु
		अगर (!match(block->b_host, host))
			जारी;
		/* Do not destroy blocks that are not on
		 * the global retry list - why? */
		अगर (list_empty(&block->b_list))
			जारी;
		kref_get(&block->b_count);
		mutex_unlock(&file->f_mutex);
		nlmsvc_unlink_block(block);
		nlmsvc_release_block(block);
		जाओ restart;
	पूर्ण
	mutex_unlock(&file->f_mutex);
पूर्ण

अटल काष्ठा nlm_lockowner *
nlmsvc_get_lockowner(काष्ठा nlm_lockowner *lockowner)
अणु
	refcount_inc(&lockowner->count);
	वापस lockowner;
पूर्ण

अटल व्योम nlmsvc_put_lockowner(काष्ठा nlm_lockowner *lockowner)
अणु
	अगर (!refcount_dec_and_lock(&lockowner->count, &lockowner->host->h_lock))
		वापस;
	list_del(&lockowner->list);
	spin_unlock(&lockowner->host->h_lock);
	nlmsvc_release_host(lockowner->host);
	kमुक्त(lockowner);
पूर्ण

अटल काष्ठा nlm_lockowner *__nlmsvc_find_lockowner(काष्ठा nlm_host *host, pid_t pid)
अणु
	काष्ठा nlm_lockowner *lockowner;
	list_क्रम_each_entry(lockowner, &host->h_lockowners, list) अणु
		अगर (lockowner->pid != pid)
			जारी;
		वापस nlmsvc_get_lockowner(lockowner);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nlm_lockowner *nlmsvc_find_lockowner(काष्ठा nlm_host *host, pid_t pid)
अणु
	काष्ठा nlm_lockowner *res, *new = शून्य;

	spin_lock(&host->h_lock);
	res = __nlmsvc_find_lockowner(host, pid);

	अगर (res == शून्य) अणु
		spin_unlock(&host->h_lock);
		new = kदो_स्मृति(माप(*res), GFP_KERNEL);
		spin_lock(&host->h_lock);
		res = __nlmsvc_find_lockowner(host, pid);
		अगर (res == शून्य && new != शून्य) अणु
			res = new;
			/* fs/locks.c will manage the refcount through lock_ops */
			refcount_set(&new->count, 1);
			new->pid = pid;
			new->host = nlm_get_host(host);
			list_add(&new->list, &host->h_lockowners);
			new = शून्य;
		पूर्ण
	पूर्ण

	spin_unlock(&host->h_lock);
	kमुक्त(new);
	वापस res;
पूर्ण

व्योम
nlmsvc_release_lockowner(काष्ठा nlm_lock *lock)
अणु
	अगर (lock->fl.fl_owner)
		nlmsvc_put_lockowner(lock->fl.fl_owner);
पूर्ण

अटल व्योम nlmsvc_locks_copy_lock(काष्ठा file_lock *new, काष्ठा file_lock *fl)
अणु
	काष्ठा nlm_lockowner *nlm_lo = (काष्ठा nlm_lockowner *)fl->fl_owner;
	new->fl_owner = nlmsvc_get_lockowner(nlm_lo);
पूर्ण

अटल व्योम nlmsvc_locks_release_निजी(काष्ठा file_lock *fl)
अणु
	nlmsvc_put_lockowner((काष्ठा nlm_lockowner *)fl->fl_owner);
पूर्ण

अटल स्थिर काष्ठा file_lock_operations nlmsvc_lock_ops = अणु
	.fl_copy_lock = nlmsvc_locks_copy_lock,
	.fl_release_निजी = nlmsvc_locks_release_निजी,
पूर्ण;

व्योम nlmsvc_locks_init_निजी(काष्ठा file_lock *fl, काष्ठा nlm_host *host,
						pid_t pid)
अणु
	fl->fl_owner = nlmsvc_find_lockowner(host, pid);
	अगर (fl->fl_owner != शून्य)
		fl->fl_ops = &nlmsvc_lock_ops;
पूर्ण

/*
 * Initialize arguments क्रम GRANTED call. The nlm_rqst काष्ठाure
 * has been cleared alपढ़ोy.
 */
अटल पूर्णांक nlmsvc_setgrantargs(काष्ठा nlm_rqst *call, काष्ठा nlm_lock *lock)
अणु
	locks_copy_lock(&call->a_args.lock.fl, &lock->fl);
	स_नकल(&call->a_args.lock.fh, &lock->fh, माप(call->a_args.lock.fh));
	call->a_args.lock.caller = utsname()->nodename;
	call->a_args.lock.oh.len = lock->oh.len;

	/* set शेष data area */
	call->a_args.lock.oh.data = call->a_owner;
	call->a_args.lock.svid = ((काष्ठा nlm_lockowner *)lock->fl.fl_owner)->pid;

	अगर (lock->oh.len > NLMCLNT_OHSIZE) अणु
		व्योम *data = kदो_स्मृति(lock->oh.len, GFP_KERNEL);
		अगर (!data)
			वापस 0;
		call->a_args.lock.oh.data = (u8 *) data;
	पूर्ण

	स_नकल(call->a_args.lock.oh.data, lock->oh.data, lock->oh.len);
	वापस 1;
पूर्ण

अटल व्योम nlmsvc_मुक्तgrantargs(काष्ठा nlm_rqst *call)
अणु
	अगर (call->a_args.lock.oh.data != call->a_owner)
		kमुक्त(call->a_args.lock.oh.data);

	locks_release_निजी(&call->a_args.lock.fl);
पूर्ण

/*
 * Deferred lock request handling क्रम non-blocking lock
 */
अटल __be32
nlmsvc_defer_lock_rqst(काष्ठा svc_rqst *rqstp, काष्ठा nlm_block *block)
अणु
	__be32 status = nlm_lck_denied_nolocks;

	block->b_flags |= B_QUEUED;

	nlmsvc_insert_block(block, NLM_TIMEOUT);

	block->b_cache_req = &rqstp->rq_chandle;
	अगर (rqstp->rq_chandle.defer) अणु
		block->b_deferred_req =
			rqstp->rq_chandle.defer(block->b_cache_req);
		अगर (block->b_deferred_req != शून्य)
			status = nlm_drop_reply;
	पूर्ण
	dprपूर्णांकk("lockd: nlmsvc_defer_lock_rqst block %p flags %d status %d\n",
		block, block->b_flags, ntohl(status));

	वापस status;
पूर्ण

/*
 * Attempt to establish a lock, and अगर it can't be granted, block it
 * अगर required.
 */
__be32
nlmsvc_lock(काष्ठा svc_rqst *rqstp, काष्ठा nlm_file *file,
	    काष्ठा nlm_host *host, काष्ठा nlm_lock *lock, पूर्णांक रुको,
	    काष्ठा nlm_cookie *cookie, पूर्णांक reclaim)
अणु
	काष्ठा nlm_block	*block = शून्य;
	पूर्णांक			error;
	__be32			ret;

	dprपूर्णांकk("lockd: nlmsvc_lock(%s/%ld, ty=%d, pi=%d, %Ld-%Ld, bl=%d)\n",
				locks_inode(file->f_file)->i_sb->s_id,
				locks_inode(file->f_file)->i_ino,
				lock->fl.fl_type, lock->fl.fl_pid,
				(दीर्घ दीर्घ)lock->fl.fl_start,
				(दीर्घ दीर्घ)lock->fl.fl_end,
				रुको);

	/* Lock file against concurrent access */
	mutex_lock(&file->f_mutex);
	/* Get existing block (in हाल client is busy-रुकोing)
	 * or create new block
	 */
	block = nlmsvc_lookup_block(file, lock);
	अगर (block == शून्य) अणु
		block = nlmsvc_create_block(rqstp, host, file, lock, cookie);
		ret = nlm_lck_denied_nolocks;
		अगर (block == शून्य)
			जाओ out;
		lock = &block->b_call->a_args.lock;
	पूर्ण अन्यथा
		lock->fl.fl_flags &= ~FL_SLEEP;

	अगर (block->b_flags & B_QUEUED) अणु
		dprपूर्णांकk("lockd: nlmsvc_lock deferred block %p flags %d\n",
							block, block->b_flags);
		अगर (block->b_granted) अणु
			nlmsvc_unlink_block(block);
			ret = nlm_granted;
			जाओ out;
		पूर्ण
		अगर (block->b_flags & B_TIMED_OUT) अणु
			nlmsvc_unlink_block(block);
			ret = nlm_lck_denied;
			जाओ out;
		पूर्ण
		ret = nlm_drop_reply;
		जाओ out;
	पूर्ण

	अगर (locks_in_grace(SVC_NET(rqstp)) && !reclaim) अणु
		ret = nlm_lck_denied_grace_period;
		जाओ out;
	पूर्ण
	अगर (reclaim && !locks_in_grace(SVC_NET(rqstp))) अणु
		ret = nlm_lck_denied_grace_period;
		जाओ out;
	पूर्ण

	अगर (!रुको)
		lock->fl.fl_flags &= ~FL_SLEEP;
	error = vfs_lock_file(file->f_file, F_SETLK, &lock->fl, शून्य);
	lock->fl.fl_flags &= ~FL_SLEEP;

	dprपूर्णांकk("lockd: vfs_lock_file returned %d\n", error);
	चयन (error) अणु
		हाल 0:
			ret = nlm_granted;
			जाओ out;
		हाल -EAGAIN:
			/*
			 * If this is a blocking request क्रम an
			 * alपढ़ोy pending lock request then we need
			 * to put it back on lockd's block list
			 */
			अगर (रुको)
				अवरोध;
			ret = nlm_lck_denied;
			जाओ out;
		हाल खाता_LOCK_DEFERRED:
			अगर (रुको)
				अवरोध;
			/* Fileप्रणाली lock operation is in progress
			   Add it to the queue रुकोing क्रम callback */
			ret = nlmsvc_defer_lock_rqst(rqstp, block);
			जाओ out;
		हाल -EDEADLK:
			ret = nlm_deadlock;
			जाओ out;
		शेष:			/* includes ENOLCK */
			ret = nlm_lck_denied_nolocks;
			जाओ out;
	पूर्ण

	ret = nlm_lck_blocked;

	/* Append to list of blocked */
	nlmsvc_insert_block(block, NLM_NEVER);
out:
	mutex_unlock(&file->f_mutex);
	nlmsvc_release_block(block);
	dprपूर्णांकk("lockd: nlmsvc_lock returned %u\n", ret);
	वापस ret;
पूर्ण

/*
 * Test क्रम presence of a conflicting lock.
 */
__be32
nlmsvc_testlock(काष्ठा svc_rqst *rqstp, काष्ठा nlm_file *file,
		काष्ठा nlm_host *host, काष्ठा nlm_lock *lock,
		काष्ठा nlm_lock *conflock, काष्ठा nlm_cookie *cookie)
अणु
	पूर्णांक			error;
	__be32			ret;
	काष्ठा nlm_lockowner	*test_owner;

	dprपूर्णांकk("lockd: nlmsvc_testlock(%s/%ld, ty=%d, %Ld-%Ld)\n",
				locks_inode(file->f_file)->i_sb->s_id,
				locks_inode(file->f_file)->i_ino,
				lock->fl.fl_type,
				(दीर्घ दीर्घ)lock->fl.fl_start,
				(दीर्घ दीर्घ)lock->fl.fl_end);

	अगर (locks_in_grace(SVC_NET(rqstp))) अणु
		ret = nlm_lck_denied_grace_period;
		जाओ out;
	पूर्ण

	/* If there's a conflicting lock, remember to clean up the test lock */
	test_owner = (काष्ठा nlm_lockowner *)lock->fl.fl_owner;

	error = vfs_test_lock(file->f_file, &lock->fl);
	अगर (error) अणु
		/* We can't currently deal with deferred test requests */
		अगर (error == खाता_LOCK_DEFERRED)
			WARN_ON_ONCE(1);

		ret = nlm_lck_denied_nolocks;
		जाओ out;
	पूर्ण

	अगर (lock->fl.fl_type == F_UNLCK) अणु
		ret = nlm_granted;
		जाओ out;
	पूर्ण

	dprपूर्णांकk("lockd: conflicting lock(ty=%d, %Ld-%Ld)\n",
		lock->fl.fl_type, (दीर्घ दीर्घ)lock->fl.fl_start,
		(दीर्घ दीर्घ)lock->fl.fl_end);
	conflock->caller = "somehost";	/* FIXME */
	conflock->len = म_माप(conflock->caller);
	conflock->oh.len = 0;		/* करोn't वापस OH info */
	conflock->svid = ((काष्ठा nlm_lockowner *)lock->fl.fl_owner)->pid;
	conflock->fl.fl_type = lock->fl.fl_type;
	conflock->fl.fl_start = lock->fl.fl_start;
	conflock->fl.fl_end = lock->fl.fl_end;
	locks_release_निजी(&lock->fl);

	/* Clean up the test lock */
	lock->fl.fl_owner = शून्य;
	nlmsvc_put_lockowner(test_owner);

	ret = nlm_lck_denied;
out:
	वापस ret;
पूर्ण

/*
 * Remove a lock.
 * This implies a CANCEL call: We send a GRANT_MSG, the client replies
 * with a GRANT_RES call which माला_लो lost, and calls UNLOCK immediately
 * afterwards. In this हाल the block will still be there, and hence
 * must be हटाओd.
 */
__be32
nlmsvc_unlock(काष्ठा net *net, काष्ठा nlm_file *file, काष्ठा nlm_lock *lock)
अणु
	पूर्णांक	error;

	dprपूर्णांकk("lockd: nlmsvc_unlock(%s/%ld, pi=%d, %Ld-%Ld)\n",
				locks_inode(file->f_file)->i_sb->s_id,
				locks_inode(file->f_file)->i_ino,
				lock->fl.fl_pid,
				(दीर्घ दीर्घ)lock->fl.fl_start,
				(दीर्घ दीर्घ)lock->fl.fl_end);

	/* First, cancel any lock that might be there */
	nlmsvc_cancel_blocked(net, file, lock);

	lock->fl.fl_type = F_UNLCK;
	error = vfs_lock_file(file->f_file, F_SETLK, &lock->fl, शून्य);

	वापस (error < 0)? nlm_lck_denied_nolocks : nlm_granted;
पूर्ण

/*
 * Cancel a previously blocked request.
 *
 * A cancel request always overrides any grant that may currently
 * be in progress.
 * The calling procedure must check whether the file can be बंदd.
 */
__be32
nlmsvc_cancel_blocked(काष्ठा net *net, काष्ठा nlm_file *file, काष्ठा nlm_lock *lock)
अणु
	काष्ठा nlm_block	*block;
	पूर्णांक status = 0;

	dprपूर्णांकk("lockd: nlmsvc_cancel(%s/%ld, pi=%d, %Ld-%Ld)\n",
				locks_inode(file->f_file)->i_sb->s_id,
				locks_inode(file->f_file)->i_ino,
				lock->fl.fl_pid,
				(दीर्घ दीर्घ)lock->fl.fl_start,
				(दीर्घ दीर्घ)lock->fl.fl_end);

	अगर (locks_in_grace(net))
		वापस nlm_lck_denied_grace_period;

	mutex_lock(&file->f_mutex);
	block = nlmsvc_lookup_block(file, lock);
	mutex_unlock(&file->f_mutex);
	अगर (block != शून्य) अणु
		vfs_cancel_lock(block->b_file->f_file,
				&block->b_call->a_args.lock.fl);
		status = nlmsvc_unlink_block(block);
		nlmsvc_release_block(block);
	पूर्ण
	वापस status ? nlm_lck_denied : nlm_granted;
पूर्ण

/*
 * This is a callback from the fileप्रणाली क्रम VFS file lock requests.
 * It will be used अगर lm_grant is defined and the fileप्रणाली can not
 * respond to the request immediately.
 * For SETLK or SETLKW request it will get the local posix lock.
 * In all हालs it will move the block to the head of nlm_blocked q where
 * nlmsvc_retry_blocked() can send back a reply क्रम SETLKW or revisit the
 * deferred rpc क्रम GETLK and SETLK.
 */
अटल व्योम
nlmsvc_update_deferred_block(काष्ठा nlm_block *block, पूर्णांक result)
अणु
	block->b_flags |= B_GOT_CALLBACK;
	अगर (result == 0)
		block->b_granted = 1;
	अन्यथा
		block->b_flags |= B_TIMED_OUT;
पूर्ण

अटल पूर्णांक nlmsvc_grant_deferred(काष्ठा file_lock *fl, पूर्णांक result)
अणु
	काष्ठा nlm_block *block;
	पूर्णांक rc = -ENOENT;

	spin_lock(&nlm_blocked_lock);
	list_क्रम_each_entry(block, &nlm_blocked, b_list) अणु
		अगर (nlm_compare_locks(&block->b_call->a_args.lock.fl, fl)) अणु
			dprपूर्णांकk("lockd: nlmsvc_notify_blocked block %p flags %d\n",
							block, block->b_flags);
			अगर (block->b_flags & B_QUEUED) अणु
				अगर (block->b_flags & B_TIMED_OUT) अणु
					rc = -ENOLCK;
					अवरोध;
				पूर्ण
				nlmsvc_update_deferred_block(block, result);
			पूर्ण अन्यथा अगर (result == 0)
				block->b_granted = 1;

			nlmsvc_insert_block_locked(block, 0);
			svc_wake_up(block->b_daemon);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&nlm_blocked_lock);
	अगर (rc == -ENOENT)
		prपूर्णांकk(KERN_WARNING "lockd: grant for unknown block\n");
	वापस rc;
पूर्ण

/*
 * Unblock a blocked lock request. This is a callback invoked from the
 * VFS layer when a lock on which we blocked is हटाओd.
 *
 * This function करोesn't grant the blocked lock instantly, but rather moves
 * the block to the head of nlm_blocked where it can be picked up by lockd.
 */
अटल व्योम
nlmsvc_notअगरy_blocked(काष्ठा file_lock *fl)
अणु
	काष्ठा nlm_block	*block;

	dprपूर्णांकk("lockd: VFS unblock notification for block %p\n", fl);
	spin_lock(&nlm_blocked_lock);
	list_क्रम_each_entry(block, &nlm_blocked, b_list) अणु
		अगर (nlm_compare_locks(&block->b_call->a_args.lock.fl, fl)) अणु
			nlmsvc_insert_block_locked(block, 0);
			spin_unlock(&nlm_blocked_lock);
			svc_wake_up(block->b_daemon);
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock(&nlm_blocked_lock);
	prपूर्णांकk(KERN_WARNING "lockd: notification for unknown block!\n");
पूर्ण

स्थिर काष्ठा lock_manager_operations nlmsvc_lock_operations = अणु
	.lm_notअगरy = nlmsvc_notअगरy_blocked,
	.lm_grant = nlmsvc_grant_deferred,
पूर्ण;

/*
 * Try to claim a lock that was previously blocked.
 *
 * Note that we use both the RPC_GRANTED_MSG call _and_ an async
 * RPC thपढ़ो when notअगरying the client. This seems like overसमाप्त...
 * Here's why:
 *  -	we करोn't want to use a synchronous RPC thपढ़ो, otherwise
 *	we might find ourselves hanging on a dead porपंचांगapper.
 *  -	Some lockd implementations (e.g. HP) करोn't react to
 *	RPC_GRANTED calls; they seem to insist on RPC_GRANTED_MSG calls.
 */
अटल व्योम
nlmsvc_grant_blocked(काष्ठा nlm_block *block)
अणु
	काष्ठा nlm_file		*file = block->b_file;
	काष्ठा nlm_lock		*lock = &block->b_call->a_args.lock;
	पूर्णांक			error;
	loff_t			fl_start, fl_end;

	dprपूर्णांकk("lockd: grant blocked lock %p\n", block);

	kref_get(&block->b_count);

	/* Unlink block request from list */
	nlmsvc_unlink_block(block);

	/* If b_granted is true this means we've been here beक्रमe.
	 * Just retry the grant callback, possibly refreshing the RPC
	 * binding */
	अगर (block->b_granted) अणु
		nlm_rebind_host(block->b_host);
		जाओ callback;
	पूर्ण

	/* Try the lock operation again */
	/* vfs_lock_file() can mangle fl_start and fl_end, but we need
	 * them unchanged क्रम the GRANT_MSG
	 */
	lock->fl.fl_flags |= FL_SLEEP;
	fl_start = lock->fl.fl_start;
	fl_end = lock->fl.fl_end;
	error = vfs_lock_file(file->f_file, F_SETLK, &lock->fl, शून्य);
	lock->fl.fl_flags &= ~FL_SLEEP;
	lock->fl.fl_start = fl_start;
	lock->fl.fl_end = fl_end;

	चयन (error) अणु
	हाल 0:
		अवरोध;
	हाल खाता_LOCK_DEFERRED:
		dprपूर्णांकk("lockd: lock still blocked error %d\n", error);
		nlmsvc_insert_block(block, NLM_NEVER);
		nlmsvc_release_block(block);
		वापस;
	शेष:
		prपूर्णांकk(KERN_WARNING "lockd: unexpected error %d in %s!\n",
				-error, __func__);
		nlmsvc_insert_block(block, 10 * HZ);
		nlmsvc_release_block(block);
		वापस;
	पूर्ण

callback:
	/* Lock was granted by VFS. */
	dprपूर्णांकk("lockd: GRANTing blocked lock.\n");
	block->b_granted = 1;

	/* keep block on the list, but करोn't reattempt until the RPC
	 * completes or the submission fails
	 */
	nlmsvc_insert_block(block, NLM_NEVER);

	/* Call the client -- use a soft RPC task since nlmsvc_retry_blocked
	 * will queue up a new one अगर this one बार out
	 */
	error = nlm_async_call(block->b_call, NLMPROC_GRANTED_MSG,
				&nlmsvc_grant_ops);

	/* RPC submission failed, रुको a bit and retry */
	अगर (error < 0)
		nlmsvc_insert_block(block, 10 * HZ);
पूर्ण

/*
 * This is the callback from the RPC layer when the NLM_GRANTED_MSG
 * RPC call has succeeded or समयd out.
 * Like all RPC callbacks, it is invoked by the rpciod process, so it
 * better not sleep. Thereक्रमe, we put the blocked lock on the nlm_blocked
 * chain once more in order to have it हटाओd by lockd itself (which can
 * then sleep on the file semaphore without disrupting e.g. the nfs client).
 */
अटल व्योम nlmsvc_grant_callback(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nlm_rqst		*call = data;
	काष्ठा nlm_block	*block = call->a_block;
	अचिन्हित दीर्घ		समयout;

	dprपूर्णांकk("lockd: GRANT_MSG RPC callback\n");

	spin_lock(&nlm_blocked_lock);
	/* अगर the block is not on a list at this poपूर्णांक then it has
	 * been invalidated. Don't try to requeue it.
	 *
	 * FIXME: it's possible that the block is हटाओd from the list
	 * after this check but beक्रमe the nlmsvc_insert_block. In that
	 * हाल it will be added back. Perhaps we need better locking
	 * क्रम nlm_blocked?
	 */
	अगर (list_empty(&block->b_list))
		जाओ out;

	/* Technically, we should करोwn the file semaphore here. Since we
	 * move the block towards the head of the queue only, no harm
	 * can be करोne, though. */
	अगर (task->tk_status < 0) अणु
		/* RPC error: Re-insert क्रम retransmission */
		समयout = 10 * HZ;
	पूर्ण अन्यथा अणु
		/* Call was successful, now रुको क्रम client callback */
		समयout = 60 * HZ;
	पूर्ण
	nlmsvc_insert_block_locked(block, समयout);
	svc_wake_up(block->b_daemon);
out:
	spin_unlock(&nlm_blocked_lock);
पूर्ण

/*
 * FIXME: nlmsvc_release_block() grअसल a mutex.  This is not allowed क्रम an
 * .rpc_release rpc_call_op
 */
अटल व्योम nlmsvc_grant_release(व्योम *data)
अणु
	काष्ठा nlm_rqst		*call = data;
	nlmsvc_release_block(call->a_block);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nlmsvc_grant_ops = अणु
	.rpc_call_करोne = nlmsvc_grant_callback,
	.rpc_release = nlmsvc_grant_release,
पूर्ण;

/*
 * We received a GRANT_RES callback. Try to find the corresponding
 * block.
 */
व्योम
nlmsvc_grant_reply(काष्ठा nlm_cookie *cookie, __be32 status)
अणु
	काष्ठा nlm_block	*block;

	dprपूर्णांकk("grant_reply: looking for cookie %x, s=%d \n",
		*(अचिन्हित पूर्णांक *)(cookie->data), status);
	अगर (!(block = nlmsvc_find_block(cookie)))
		वापस;

	अगर (status == nlm_lck_denied_grace_period) अणु
		/* Try again in a couple of seconds */
		nlmsvc_insert_block(block, 10 * HZ);
	पूर्ण अन्यथा अणु
		/*
		 * Lock is now held by client, or has been rejected.
		 * In both हालs, the block should be हटाओd.
		 */
		nlmsvc_unlink_block(block);
	पूर्ण
	nlmsvc_release_block(block);
पूर्ण

/* Helper function to handle retry of a deferred block.
 * If it is a blocking lock, call grant_blocked.
 * For a non-blocking lock or test lock, revisit the request.
 */
अटल व्योम
retry_deferred_block(काष्ठा nlm_block *block)
अणु
	अगर (!(block->b_flags & B_GOT_CALLBACK))
		block->b_flags |= B_TIMED_OUT;
	nlmsvc_insert_block(block, NLM_TIMEOUT);
	dprपूर्णांकk("revisit block %p flags %d\n",	block, block->b_flags);
	अगर (block->b_deferred_req) अणु
		block->b_deferred_req->revisit(block->b_deferred_req, 0);
		block->b_deferred_req = शून्य;
	पूर्ण
पूर्ण

/*
 * Retry all blocked locks that have been notअगरied. This is where lockd
 * picks up locks that can be granted, or grant notअगरications that must
 * be retransmitted.
 */
अचिन्हित दीर्घ
nlmsvc_retry_blocked(व्योम)
अणु
	अचिन्हित दीर्घ	समयout = MAX_SCHEDULE_TIMEOUT;
	काष्ठा nlm_block *block;

	spin_lock(&nlm_blocked_lock);
	जबतक (!list_empty(&nlm_blocked) && !kthपढ़ो_should_stop()) अणु
		block = list_entry(nlm_blocked.next, काष्ठा nlm_block, b_list);

		अगर (block->b_when == NLM_NEVER)
			अवरोध;
		अगर (समय_after(block->b_when, jअगरfies)) अणु
			समयout = block->b_when - jअगरfies;
			अवरोध;
		पूर्ण
		spin_unlock(&nlm_blocked_lock);

		dprपूर्णांकk("nlmsvc_retry_blocked(%p, when=%ld)\n",
			block, block->b_when);
		अगर (block->b_flags & B_QUEUED) अणु
			dprपूर्णांकk("nlmsvc_retry_blocked delete block (%p, granted=%d, flags=%d)\n",
				block, block->b_granted, block->b_flags);
			retry_deferred_block(block);
		पूर्ण अन्यथा
			nlmsvc_grant_blocked(block);
		spin_lock(&nlm_blocked_lock);
	पूर्ण
	spin_unlock(&nlm_blocked_lock);

	वापस समयout;
पूर्ण
