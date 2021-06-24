<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/lockd/clntproc.c
 *
 * RPC procedures क्रम the client side NLM implementation
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/utsname.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/lockd/lockd.h>

#घोषणा NLMDBG_FACILITY		NLMDBG_CLIENT
#घोषणा NLMCLNT_GRACE_WAIT	(5*HZ)
#घोषणा NLMCLNT_POLL_TIMEOUT	(30*HZ)
#घोषणा NLMCLNT_MAX_RETRIES	3

अटल पूर्णांक	nlmclnt_test(काष्ठा nlm_rqst *, काष्ठा file_lock *);
अटल पूर्णांक	nlmclnt_lock(काष्ठा nlm_rqst *, काष्ठा file_lock *);
अटल पूर्णांक	nlmclnt_unlock(काष्ठा nlm_rqst *, काष्ठा file_lock *);
अटल पूर्णांक	nlm_stat_to_त्रुटि_सं(__be32 stat);
अटल व्योम	nlmclnt_locks_init_निजी(काष्ठा file_lock *fl, काष्ठा nlm_host *host);
अटल पूर्णांक	nlmclnt_cancel(काष्ठा nlm_host *, पूर्णांक , काष्ठा file_lock *);

अटल स्थिर काष्ठा rpc_call_ops nlmclnt_unlock_ops;
अटल स्थिर काष्ठा rpc_call_ops nlmclnt_cancel_ops;

/*
 * Cookie counter क्रम NLM requests
 */
अटल atomic_t	nlm_cookie = ATOMIC_INIT(0x1234);

व्योम nlmclnt_next_cookie(काष्ठा nlm_cookie *c)
अणु
	u32	cookie = atomic_inc_वापस(&nlm_cookie);

	स_नकल(c->data, &cookie, 4);
	c->len=4;
पूर्ण

अटल काष्ठा nlm_lockowner *
nlmclnt_get_lockowner(काष्ठा nlm_lockowner *lockowner)
अणु
	refcount_inc(&lockowner->count);
	वापस lockowner;
पूर्ण

अटल व्योम nlmclnt_put_lockowner(काष्ठा nlm_lockowner *lockowner)
अणु
	अगर (!refcount_dec_and_lock(&lockowner->count, &lockowner->host->h_lock))
		वापस;
	list_del(&lockowner->list);
	spin_unlock(&lockowner->host->h_lock);
	nlmclnt_release_host(lockowner->host);
	kमुक्त(lockowner);
पूर्ण

अटल अंतरभूत पूर्णांक nlm_pidbusy(काष्ठा nlm_host *host, uपूर्णांक32_t pid)
अणु
	काष्ठा nlm_lockowner *lockowner;
	list_क्रम_each_entry(lockowner, &host->h_lockowners, list) अणु
		अगर (lockowner->pid == pid)
			वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t __nlm_alloc_pid(काष्ठा nlm_host *host)
अणु
	uपूर्णांक32_t res;
	करो अणु
		res = host->h_pidcount++;
	पूर्ण जबतक (nlm_pidbusy(host, res) < 0);
	वापस res;
पूर्ण

अटल काष्ठा nlm_lockowner *__nlmclnt_find_lockowner(काष्ठा nlm_host *host, fl_owner_t owner)
अणु
	काष्ठा nlm_lockowner *lockowner;
	list_क्रम_each_entry(lockowner, &host->h_lockowners, list) अणु
		अगर (lockowner->owner != owner)
			जारी;
		वापस nlmclnt_get_lockowner(lockowner);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा nlm_lockowner *nlmclnt_find_lockowner(काष्ठा nlm_host *host, fl_owner_t owner)
अणु
	काष्ठा nlm_lockowner *res, *new = शून्य;

	spin_lock(&host->h_lock);
	res = __nlmclnt_find_lockowner(host, owner);
	अगर (res == शून्य) अणु
		spin_unlock(&host->h_lock);
		new = kदो_स्मृति(माप(*new), GFP_KERNEL);
		spin_lock(&host->h_lock);
		res = __nlmclnt_find_lockowner(host, owner);
		अगर (res == शून्य && new != शून्य) अणु
			res = new;
			refcount_set(&new->count, 1);
			new->owner = owner;
			new->pid = __nlm_alloc_pid(host);
			new->host = nlm_get_host(host);
			list_add(&new->list, &host->h_lockowners);
			new = शून्य;
		पूर्ण
	पूर्ण
	spin_unlock(&host->h_lock);
	kमुक्त(new);
	वापस res;
पूर्ण

/*
 * Initialize arguments क्रम TEST/LOCK/UNLOCK/CANCEL calls
 */
अटल व्योम nlmclnt_setlockargs(काष्ठा nlm_rqst *req, काष्ठा file_lock *fl)
अणु
	काष्ठा nlm_args	*argp = &req->a_args;
	काष्ठा nlm_lock	*lock = &argp->lock;
	अक्षर *nodename = req->a_host->h_rpcclnt->cl_nodename;

	nlmclnt_next_cookie(&argp->cookie);
	स_नकल(&lock->fh, NFS_FH(locks_inode(fl->fl_file)), माप(काष्ठा nfs_fh));
	lock->caller  = nodename;
	lock->oh.data = req->a_owner;
	lock->oh.len  = snम_लिखो(req->a_owner, माप(req->a_owner), "%u@%s",
				(अचिन्हित पूर्णांक)fl->fl_u.nfs_fl.owner->pid,
				nodename);
	lock->svid = fl->fl_u.nfs_fl.owner->pid;
	lock->fl.fl_start = fl->fl_start;
	lock->fl.fl_end = fl->fl_end;
	lock->fl.fl_type = fl->fl_type;
पूर्ण

अटल व्योम nlmclnt_release_lockargs(काष्ठा nlm_rqst *req)
अणु
	WARN_ON_ONCE(req->a_args.lock.fl.fl_ops != शून्य);
पूर्ण

/**
 * nlmclnt_proc - Perक्रमm a single client-side lock request
 * @host: address of a valid nlm_host context representing the NLM server
 * @cmd: fcntl-style file lock operation to perक्रमm
 * @fl: address of arguments क्रम the lock operation
 * @data: address of data to be sent to callback operations
 *
 */
पूर्णांक nlmclnt_proc(काष्ठा nlm_host *host, पूर्णांक cmd, काष्ठा file_lock *fl, व्योम *data)
अणु
	काष्ठा nlm_rqst		*call;
	पूर्णांक			status;
	स्थिर काष्ठा nlmclnt_operations *nlmclnt_ops = host->h_nlmclnt_ops;

	call = nlm_alloc_call(host);
	अगर (call == शून्य)
		वापस -ENOMEM;

	अगर (nlmclnt_ops && nlmclnt_ops->nlmclnt_alloc_call)
		nlmclnt_ops->nlmclnt_alloc_call(data);

	nlmclnt_locks_init_निजी(fl, host);
	अगर (!fl->fl_u.nfs_fl.owner) अणु
		/* lockowner allocation has failed */
		nlmclnt_release_call(call);
		वापस -ENOMEM;
	पूर्ण
	/* Set up the argument काष्ठा */
	nlmclnt_setlockargs(call, fl);
	call->a_callback_data = data;

	अगर (IS_SETLK(cmd) || IS_SETLKW(cmd)) अणु
		अगर (fl->fl_type != F_UNLCK) अणु
			call->a_args.block = IS_SETLKW(cmd) ? 1 : 0;
			status = nlmclnt_lock(call, fl);
		पूर्ण अन्यथा
			status = nlmclnt_unlock(call, fl);
	पूर्ण अन्यथा अगर (IS_GETLK(cmd))
		status = nlmclnt_test(call, fl);
	अन्यथा
		status = -EINVAL;
	fl->fl_ops->fl_release_निजी(fl);
	fl->fl_ops = शून्य;

	dprपूर्णांकk("lockd: clnt proc returns %d\n", status);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(nlmclnt_proc);

/*
 * Allocate an NLM RPC call काष्ठा
 */
काष्ठा nlm_rqst *nlm_alloc_call(काष्ठा nlm_host *host)
अणु
	काष्ठा nlm_rqst	*call;

	क्रम(;;) अणु
		call = kzalloc(माप(*call), GFP_KERNEL);
		अगर (call != शून्य) अणु
			refcount_set(&call->a_count, 1);
			locks_init_lock(&call->a_args.lock.fl);
			locks_init_lock(&call->a_res.lock.fl);
			call->a_host = nlm_get_host(host);
			वापस call;
		पूर्ण
		अगर (संकेतled())
			अवरोध;
		prपूर्णांकk("nlm_alloc_call: failed, waiting for memory\n");
		schedule_समयout_पूर्णांकerruptible(5*HZ);
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम nlmclnt_release_call(काष्ठा nlm_rqst *call)
अणु
	स्थिर काष्ठा nlmclnt_operations *nlmclnt_ops = call->a_host->h_nlmclnt_ops;

	अगर (!refcount_dec_and_test(&call->a_count))
		वापस;
	अगर (nlmclnt_ops && nlmclnt_ops->nlmclnt_release_call)
		nlmclnt_ops->nlmclnt_release_call(call->a_callback_data);
	nlmclnt_release_host(call->a_host);
	nlmclnt_release_lockargs(call);
	kमुक्त(call);
पूर्ण

अटल व्योम nlmclnt_rpc_release(व्योम *data)
अणु
	nlmclnt_release_call(data);
पूर्ण

अटल पूर्णांक nlm_रुको_on_grace(रुको_queue_head_t *queue)
अणु
	DEFINE_WAIT(रुको);
	पूर्णांक status = -EINTR;

	prepare_to_रुको(queue, &रुको, TASK_INTERRUPTIBLE);
	अगर (!संकेतled ()) अणु
		schedule_समयout(NLMCLNT_GRACE_WAIT);
		try_to_मुक्तze();
		अगर (!संकेतled ())
			status = 0;
	पूर्ण
	finish_रुको(queue, &रुको);
	वापस status;
पूर्ण

/*
 * Generic NLM call
 */
अटल पूर्णांक
nlmclnt_call(स्थिर काष्ठा cred *cred, काष्ठा nlm_rqst *req, u32 proc)
अणु
	काष्ठा nlm_host	*host = req->a_host;
	काष्ठा rpc_clnt	*clnt;
	काष्ठा nlm_args	*argp = &req->a_args;
	काष्ठा nlm_res	*resp = &req->a_res;
	काष्ठा rpc_message msg = अणु
		.rpc_argp	= argp,
		.rpc_resp	= resp,
		.rpc_cred	= cred,
	पूर्ण;
	पूर्णांक		status;

	dprपूर्णांकk("lockd: call procedure %d on %s\n",
			(पूर्णांक)proc, host->h_name);

	करो अणु
		अगर (host->h_reclaiming && !argp->reclaim)
			जाओ in_grace_period;

		/* If we have no RPC client yet, create one. */
		अगर ((clnt = nlm_bind_host(host)) == शून्य)
			वापस -ENOLCK;
		msg.rpc_proc = &clnt->cl_procinfo[proc];

		/* Perक्रमm the RPC call. If an error occurs, try again */
		अगर ((status = rpc_call_sync(clnt, &msg, 0)) < 0) अणु
			dprपूर्णांकk("lockd: rpc_call returned error %d\n", -status);
			चयन (status) अणु
			हाल -EPROTONOSUPPORT:
				status = -EINVAL;
				अवरोध;
			हाल -ECONNREFUSED:
			हाल -ETIMEDOUT:
			हाल -ENOTCONN:
				nlm_rebind_host(host);
				status = -EAGAIN;
				अवरोध;
			हाल -ERESTARTSYS:
				वापस संकेतled () ? -EINTR : status;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा
		अगर (resp->status == nlm_lck_denied_grace_period) अणु
			dprपूर्णांकk("lockd: server in grace period\n");
			अगर (argp->reclaim) अणु
				prपूर्णांकk(KERN_WARNING
				     "lockd: spurious grace period reject?!\n");
				वापस -ENOLCK;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!argp->reclaim) अणु
				/* We appear to be out of the grace period */
				wake_up_all(&host->h_graceरुको);
			पूर्ण
			dprपूर्णांकk("lockd: server returns status %d\n",
				ntohl(resp->status));
			वापस 0;	/* Okay, call complete */
		पूर्ण

in_grace_period:
		/*
		 * The server has rebooted and appears to be in the grace
		 * period during which locks are only allowed to be
		 * reclaimed.
		 * We can only back off and try again later.
		 */
		status = nlm_रुको_on_grace(&host->h_graceरुको);
	पूर्ण जबतक (status == 0);

	वापस status;
पूर्ण

/*
 * Generic NLM call, async version.
 */
अटल काष्ठा rpc_task *__nlm_async_call(काष्ठा nlm_rqst *req, u32 proc, काष्ठा rpc_message *msg, स्थिर काष्ठा rpc_call_ops *tk_ops)
अणु
	काष्ठा nlm_host	*host = req->a_host;
	काष्ठा rpc_clnt	*clnt;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_message = msg,
		.callback_ops = tk_ops,
		.callback_data = req,
		.flags = RPC_TASK_ASYNC,
	पूर्ण;

	dprपूर्णांकk("lockd: call procedure %d on %s (async)\n",
			(पूर्णांक)proc, host->h_name);

	/* If we have no RPC client yet, create one. */
	clnt = nlm_bind_host(host);
	अगर (clnt == शून्य)
		जाओ out_err;
	msg->rpc_proc = &clnt->cl_procinfo[proc];
	task_setup_data.rpc_client = clnt;

        /* bootstrap and kick off the async RPC call */
	वापस rpc_run_task(&task_setup_data);
out_err:
	tk_ops->rpc_release(req);
	वापस ERR_PTR(-ENOLCK);
पूर्ण

अटल पूर्णांक nlm_करो_async_call(काष्ठा nlm_rqst *req, u32 proc, काष्ठा rpc_message *msg, स्थिर काष्ठा rpc_call_ops *tk_ops)
अणु
	काष्ठा rpc_task *task;

	task = __nlm_async_call(req, proc, msg, tk_ops);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	rpc_put_task(task);
	वापस 0;
पूर्ण

/*
 * NLM asynchronous call.
 */
पूर्णांक nlm_async_call(काष्ठा nlm_rqst *req, u32 proc, स्थिर काष्ठा rpc_call_ops *tk_ops)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_argp	= &req->a_args,
		.rpc_resp	= &req->a_res,
	पूर्ण;
	वापस nlm_करो_async_call(req, proc, &msg, tk_ops);
पूर्ण

पूर्णांक nlm_async_reply(काष्ठा nlm_rqst *req, u32 proc, स्थिर काष्ठा rpc_call_ops *tk_ops)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_argp	= &req->a_res,
	पूर्ण;
	वापस nlm_करो_async_call(req, proc, &msg, tk_ops);
पूर्ण

/*
 * NLM client asynchronous call.
 *
 * Note that although the calls are asynchronous, and are thereक्रमe
 *      guaranteed to complete, we still always attempt to रुको क्रम
 *      completion in order to be able to correctly track the lock
 *      state.
 */
अटल पूर्णांक nlmclnt_async_call(स्थिर काष्ठा cred *cred, काष्ठा nlm_rqst *req, u32 proc, स्थिर काष्ठा rpc_call_ops *tk_ops)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_argp	= &req->a_args,
		.rpc_resp	= &req->a_res,
		.rpc_cred	= cred,
	पूर्ण;
	काष्ठा rpc_task *task;
	पूर्णांक err;

	task = __nlm_async_call(req, proc, &msg, tk_ops);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	err = rpc_रुको_क्रम_completion_task(task);
	rpc_put_task(task);
	वापस err;
पूर्ण

/*
 * TEST क्रम the presence of a conflicting lock
 */
अटल पूर्णांक
nlmclnt_test(काष्ठा nlm_rqst *req, काष्ठा file_lock *fl)
अणु
	पूर्णांक	status;

	status = nlmclnt_call(nfs_file_cred(fl->fl_file), req, NLMPROC_TEST);
	अगर (status < 0)
		जाओ out;

	चयन (req->a_res.status) अणु
		हाल nlm_granted:
			fl->fl_type = F_UNLCK;
			अवरोध;
		हाल nlm_lck_denied:
			/*
			 * Report the conflicting lock back to the application.
			 */
			fl->fl_start = req->a_res.lock.fl.fl_start;
			fl->fl_end = req->a_res.lock.fl.fl_end;
			fl->fl_type = req->a_res.lock.fl.fl_type;
			fl->fl_pid = -req->a_res.lock.fl.fl_pid;
			अवरोध;
		शेष:
			status = nlm_stat_to_त्रुटि_सं(req->a_res.status);
	पूर्ण
out:
	nlmclnt_release_call(req);
	वापस status;
पूर्ण

अटल व्योम nlmclnt_locks_copy_lock(काष्ठा file_lock *new, काष्ठा file_lock *fl)
अणु
	spin_lock(&fl->fl_u.nfs_fl.owner->host->h_lock);
	new->fl_u.nfs_fl.state = fl->fl_u.nfs_fl.state;
	new->fl_u.nfs_fl.owner = nlmclnt_get_lockowner(fl->fl_u.nfs_fl.owner);
	list_add_tail(&new->fl_u.nfs_fl.list, &fl->fl_u.nfs_fl.owner->host->h_granted);
	spin_unlock(&fl->fl_u.nfs_fl.owner->host->h_lock);
पूर्ण

अटल व्योम nlmclnt_locks_release_निजी(काष्ठा file_lock *fl)
अणु
	spin_lock(&fl->fl_u.nfs_fl.owner->host->h_lock);
	list_del(&fl->fl_u.nfs_fl.list);
	spin_unlock(&fl->fl_u.nfs_fl.owner->host->h_lock);
	nlmclnt_put_lockowner(fl->fl_u.nfs_fl.owner);
पूर्ण

अटल स्थिर काष्ठा file_lock_operations nlmclnt_lock_ops = अणु
	.fl_copy_lock = nlmclnt_locks_copy_lock,
	.fl_release_निजी = nlmclnt_locks_release_निजी,
पूर्ण;

अटल व्योम nlmclnt_locks_init_निजी(काष्ठा file_lock *fl, काष्ठा nlm_host *host)
अणु
	fl->fl_u.nfs_fl.state = 0;
	fl->fl_u.nfs_fl.owner = nlmclnt_find_lockowner(host, fl->fl_owner);
	INIT_LIST_HEAD(&fl->fl_u.nfs_fl.list);
	fl->fl_ops = &nlmclnt_lock_ops;
पूर्ण

अटल पूर्णांक करो_vfs_lock(काष्ठा file_lock *fl)
अणु
	वापस locks_lock_file_रुको(fl->fl_file, fl);
पूर्ण

/*
 * LOCK: Try to create a lock
 *
 *			Programmer Harassment Alert
 *
 * When given a blocking lock request in a sync RPC call, the HPUX lockd
 * will faithfully वापस LCK_BLOCKED but never cares to notअगरy us when
 * the lock could be granted. This way, our local process could hang
 * around क्रमever रुकोing क्रम the callback.
 *
 *  Solution A:	Implement busy-रुकोing
 *  Solution B: Use the async version of the call (NLM_LOCK_अणुMSG,RESपूर्ण)
 *
 * For now I am implementing solution A, because I hate the idea of
 * re-implementing lockd क्रम a third समय in two months. The async
 * calls shouldn't be too hard to करो, however.
 *
 * This is one of the lovely things about standards in the NFS area:
 * they're so soft and squishy you can't really blame HP क्रम करोing this.
 */
अटल पूर्णांक
nlmclnt_lock(काष्ठा nlm_rqst *req, काष्ठा file_lock *fl)
अणु
	स्थिर काष्ठा cred *cred = nfs_file_cred(fl->fl_file);
	काष्ठा nlm_host	*host = req->a_host;
	काष्ठा nlm_res	*resp = &req->a_res;
	काष्ठा nlm_रुको *block = शून्य;
	अचिन्हित अक्षर fl_flags = fl->fl_flags;
	अचिन्हित अक्षर fl_type;
	पूर्णांक status = -ENOLCK;

	अगर (nsm_monitor(host) < 0)
		जाओ out;
	req->a_args.state = nsm_local_state;

	fl->fl_flags |= FL_ACCESS;
	status = करो_vfs_lock(fl);
	fl->fl_flags = fl_flags;
	अगर (status < 0)
		जाओ out;

	block = nlmclnt_prepare_block(host, fl);
again:
	/*
	 * Initialise resp->status to a valid non-zero value,
	 * since 0 == nlm_lck_granted
	 */
	resp->status = nlm_lck_blocked;
	क्रम(;;) अणु
		/* Reboot protection */
		fl->fl_u.nfs_fl.state = host->h_state;
		status = nlmclnt_call(cred, req, NLMPROC_LOCK);
		अगर (status < 0)
			अवरोध;
		/* Did a reclaimer thपढ़ो notअगरy us of a server reboot? */
		अगर (resp->status ==  nlm_lck_denied_grace_period)
			जारी;
		अगर (resp->status != nlm_lck_blocked)
			अवरोध;
		/* Wait on an NLM blocking lock */
		status = nlmclnt_block(block, req, NLMCLNT_POLL_TIMEOUT);
		अगर (status < 0)
			अवरोध;
		अगर (resp->status != nlm_lck_blocked)
			अवरोध;
	पूर्ण

	/* अगर we were पूर्णांकerrupted जबतक blocking, then cancel the lock request
	 * and निकास
	 */
	अगर (resp->status == nlm_lck_blocked) अणु
		अगर (!req->a_args.block)
			जाओ out_unlock;
		अगर (nlmclnt_cancel(host, req->a_args.block, fl) == 0)
			जाओ out_unblock;
	पूर्ण

	अगर (resp->status == nlm_granted) अणु
		करोwn_पढ़ो(&host->h_rwsem);
		/* Check whether or not the server has rebooted */
		अगर (fl->fl_u.nfs_fl.state != host->h_state) अणु
			up_पढ़ो(&host->h_rwsem);
			जाओ again;
		पूर्ण
		/* Ensure the resulting lock will get added to granted list */
		fl->fl_flags |= FL_SLEEP;
		अगर (करो_vfs_lock(fl) < 0)
			prपूर्णांकk(KERN_WARNING "%s: VFS is out of sync with lock manager!\n", __func__);
		up_पढ़ो(&host->h_rwsem);
		fl->fl_flags = fl_flags;
		status = 0;
	पूर्ण
	अगर (status < 0)
		जाओ out_unlock;
	/*
	 * EAGAIN करोesn't make sense क्रम sleeping locks, and in some
	 * हालs NLM_LCK_DENIED is वापसed क्रम a permanent error.  So
	 * turn it पूर्णांकo an ENOLCK.
	 */
	अगर (resp->status == nlm_lck_denied && (fl_flags & FL_SLEEP))
		status = -ENOLCK;
	अन्यथा
		status = nlm_stat_to_त्रुटि_सं(resp->status);
out_unblock:
	nlmclnt_finish_block(block);
out:
	nlmclnt_release_call(req);
	वापस status;
out_unlock:
	/* Fatal error: ensure that we हटाओ the lock altogether */
	dprपूर्णांकk("lockd: lock attempt ended in fatal error.\n"
		"       Attempting to unlock.\n");
	nlmclnt_finish_block(block);
	fl_type = fl->fl_type;
	fl->fl_type = F_UNLCK;
	करोwn_पढ़ो(&host->h_rwsem);
	करो_vfs_lock(fl);
	up_पढ़ो(&host->h_rwsem);
	fl->fl_type = fl_type;
	fl->fl_flags = fl_flags;
	nlmclnt_async_call(cred, req, NLMPROC_UNLOCK, &nlmclnt_unlock_ops);
	वापस status;
पूर्ण

/*
 * RECLAIM: Try to reclaim a lock
 */
पूर्णांक
nlmclnt_reclaim(काष्ठा nlm_host *host, काष्ठा file_lock *fl,
		काष्ठा nlm_rqst *req)
अणु
	पूर्णांक		status;

	स_रखो(req, 0, माप(*req));
	locks_init_lock(&req->a_args.lock.fl);
	locks_init_lock(&req->a_res.lock.fl);
	req->a_host  = host;

	/* Set up the argument काष्ठा */
	nlmclnt_setlockargs(req, fl);
	req->a_args.reclaim = 1;

	status = nlmclnt_call(nfs_file_cred(fl->fl_file), req, NLMPROC_LOCK);
	अगर (status >= 0 && req->a_res.status == nlm_granted)
		वापस 0;

	prपूर्णांकk(KERN_WARNING "lockd: failed to reclaim lock for pid %d "
				"(errno %d, status %d)\n", fl->fl_pid,
				status, ntohl(req->a_res.status));

	/*
	 * FIXME: This is a serious failure. We can
	 *
	 *  a.	Ignore the problem
	 *  b.	Send the owning process some संकेत (Linux करोesn't have
	 *	SIGLOST, though...)
	 *  c.	Retry the operation
	 *
	 * Until someone comes up with a simple implementation
	 * क्रम b or c, I'll choose option a.
	 */

	वापस -ENOLCK;
पूर्ण

/*
 * UNLOCK: हटाओ an existing lock
 */
अटल पूर्णांक
nlmclnt_unlock(काष्ठा nlm_rqst *req, काष्ठा file_lock *fl)
अणु
	काष्ठा nlm_host	*host = req->a_host;
	काष्ठा nlm_res	*resp = &req->a_res;
	पूर्णांक status;
	अचिन्हित अक्षर fl_flags = fl->fl_flags;

	/*
	 * Note: the server is supposed to either grant us the unlock
	 * request, or to deny it with NLM_LCK_DENIED_GRACE_PERIOD. In either
	 * हाल, we want to unlock.
	 */
	fl->fl_flags |= FL_EXISTS;
	करोwn_पढ़ो(&host->h_rwsem);
	status = करो_vfs_lock(fl);
	up_पढ़ो(&host->h_rwsem);
	fl->fl_flags = fl_flags;
	अगर (status == -ENOENT) अणु
		status = 0;
		जाओ out;
	पूर्ण

	refcount_inc(&req->a_count);
	status = nlmclnt_async_call(nfs_file_cred(fl->fl_file), req,
			NLMPROC_UNLOCK, &nlmclnt_unlock_ops);
	अगर (status < 0)
		जाओ out;

	अगर (resp->status == nlm_granted)
		जाओ out;

	अगर (resp->status != nlm_lck_denied_nolocks)
		prपूर्णांकk("lockd: unexpected unlock status: %d\n",
			ntohl(resp->status));
	/* What to करो now? I'm out of my depth... */
	status = -ENOLCK;
out:
	nlmclnt_release_call(req);
	वापस status;
पूर्ण

अटल व्योम nlmclnt_unlock_prepare(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nlm_rqst	*req = data;
	स्थिर काष्ठा nlmclnt_operations *nlmclnt_ops = req->a_host->h_nlmclnt_ops;
	bool defer_call = false;

	अगर (nlmclnt_ops && nlmclnt_ops->nlmclnt_unlock_prepare)
		defer_call = nlmclnt_ops->nlmclnt_unlock_prepare(task, req->a_callback_data);

	अगर (!defer_call)
		rpc_call_start(task);
पूर्ण

अटल व्योम nlmclnt_unlock_callback(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nlm_rqst	*req = data;
	u32 status = ntohl(req->a_res.status);

	अगर (RPC_SIGNALLED(task))
		जाओ die;

	अगर (task->tk_status < 0) अणु
		dprपूर्णांकk("lockd: unlock failed (err = %d)\n", -task->tk_status);
		चयन (task->tk_status) अणु
		हाल -EACCES:
		हाल -EIO:
			जाओ die;
		शेष:
			जाओ retry_rebind;
		पूर्ण
	पूर्ण
	अगर (status == NLM_LCK_DENIED_GRACE_PERIOD) अणु
		rpc_delay(task, NLMCLNT_GRACE_WAIT);
		जाओ retry_unlock;
	पूर्ण
	अगर (status != NLM_LCK_GRANTED)
		prपूर्णांकk(KERN_WARNING "lockd: unexpected unlock status: %d\n", status);
die:
	वापस;
 retry_rebind:
	nlm_rebind_host(req->a_host);
 retry_unlock:
	rpc_restart_call(task);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nlmclnt_unlock_ops = अणु
	.rpc_call_prepare = nlmclnt_unlock_prepare,
	.rpc_call_करोne = nlmclnt_unlock_callback,
	.rpc_release = nlmclnt_rpc_release,
पूर्ण;

/*
 * Cancel a blocked lock request.
 * We always use an async RPC call क्रम this in order not to hang a
 * process that has been Ctrl-C'ed.
 */
अटल पूर्णांक nlmclnt_cancel(काष्ठा nlm_host *host, पूर्णांक block, काष्ठा file_lock *fl)
अणु
	काष्ठा nlm_rqst	*req;
	पूर्णांक status;

	dprपूर्णांकk("lockd: blocking lock attempt was interrupted by a signal.\n"
		"       Attempting to cancel lock.\n");

	req = nlm_alloc_call(host);
	अगर (!req)
		वापस -ENOMEM;
	req->a_flags = RPC_TASK_ASYNC;

	nlmclnt_setlockargs(req, fl);
	req->a_args.block = block;

	refcount_inc(&req->a_count);
	status = nlmclnt_async_call(nfs_file_cred(fl->fl_file), req,
			NLMPROC_CANCEL, &nlmclnt_cancel_ops);
	अगर (status == 0 && req->a_res.status == nlm_lck_denied)
		status = -ENOLCK;
	nlmclnt_release_call(req);
	वापस status;
पूर्ण

अटल व्योम nlmclnt_cancel_callback(काष्ठा rpc_task *task, व्योम *data)
अणु
	काष्ठा nlm_rqst	*req = data;
	u32 status = ntohl(req->a_res.status);

	अगर (RPC_SIGNALLED(task))
		जाओ die;

	अगर (task->tk_status < 0) अणु
		dprपूर्णांकk("lockd: CANCEL call error %d, retrying.\n",
					task->tk_status);
		जाओ retry_cancel;
	पूर्ण

	dprपूर्णांकk("lockd: cancel status %u (task %u)\n",
			status, task->tk_pid);

	चयन (status) अणु
	हाल NLM_LCK_GRANTED:
	हाल NLM_LCK_DENIED_GRACE_PERIOD:
	हाल NLM_LCK_DENIED:
		/* Everything's good */
		अवरोध;
	हाल NLM_LCK_DENIED_NOLOCKS:
		dprपूर्णांकk("lockd: CANCEL failed (server has no locks)\n");
		जाओ retry_cancel;
	शेष:
		prपूर्णांकk(KERN_NOTICE "lockd: weird return %d for CANCEL call\n",
			status);
	पूर्ण

die:
	वापस;

retry_cancel:
	/* Don't ever retry more than 3 बार */
	अगर (req->a_retries++ >= NLMCLNT_MAX_RETRIES)
		जाओ die;
	nlm_rebind_host(req->a_host);
	rpc_restart_call(task);
	rpc_delay(task, 30 * HZ);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nlmclnt_cancel_ops = अणु
	.rpc_call_करोne = nlmclnt_cancel_callback,
	.rpc_release = nlmclnt_rpc_release,
पूर्ण;

/*
 * Convert an NLM status code to a generic kernel त्रुटि_सं
 */
अटल पूर्णांक
nlm_stat_to_त्रुटि_सं(__be32 status)
अणु
	चयन(ntohl(status)) अणु
	हाल NLM_LCK_GRANTED:
		वापस 0;
	हाल NLM_LCK_DENIED:
		वापस -EAGAIN;
	हाल NLM_LCK_DENIED_NOLOCKS:
	हाल NLM_LCK_DENIED_GRACE_PERIOD:
		वापस -ENOLCK;
	हाल NLM_LCK_BLOCKED:
		prपूर्णांकk(KERN_NOTICE "lockd: unexpected status NLM_BLOCKED\n");
		वापस -ENOLCK;
#अगर_घोषित CONFIG_LOCKD_V4
	हाल NLM_DEADLCK:
		वापस -EDEADLK;
	हाल NLM_ROFS:
		वापस -EROFS;
	हाल NLM_STALE_FH:
		वापस -ESTALE;
	हाल NLM_FBIG:
		वापस -EOVERFLOW;
	हाल NLM_FAILED:
		वापस -ENOLCK;
#पूर्ण_अगर
	पूर्ण
	prपूर्णांकk(KERN_NOTICE "lockd: unexpected server status %d\n",
		 ntohl(status));
	वापस -ENOLCK;
पूर्ण
