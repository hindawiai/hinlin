<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/lockd/svc4proc.c
 *
 * Lockd server procedures. We करोn't implement the NLM_*_RES 
 * procedures because we करोn't use the async procedures.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <linux/lockd/lockd.h>
#समावेश <linux/lockd/share.h>
#समावेश <linux/sunrpc/svc_xprt.h>

#घोषणा NLMDBG_FACILITY		NLMDBG_CLIENT

/*
 * Obtain client and file from arguments
 */
अटल __be32
nlm4svc_retrieve_args(काष्ठा svc_rqst *rqstp, काष्ठा nlm_args *argp,
			काष्ठा nlm_host **hostp, काष्ठा nlm_file **filp)
अणु
	काष्ठा nlm_host		*host = शून्य;
	काष्ठा nlm_file		*file = शून्य;
	काष्ठा nlm_lock		*lock = &argp->lock;
	__be32			error = 0;

	/* nfsd callbacks must have been installed क्रम this procedure */
	अगर (!nlmsvc_ops)
		वापस nlm_lck_denied_nolocks;

	/* Obtain host handle */
	अगर (!(host = nlmsvc_lookup_host(rqstp, lock->caller, lock->len))
	 || (argp->monitor && nsm_monitor(host) < 0))
		जाओ no_locks;
	*hostp = host;

	/* Obtain file poपूर्णांकer. Not used by FREE_ALL call. */
	अगर (filp != शून्य) अणु
		अगर ((error = nlm_lookup_file(rqstp, &file, &lock->fh)) != 0)
			जाओ no_locks;
		*filp = file;

		/* Set up the missing parts of the file_lock काष्ठाure */
		lock->fl.fl_file  = file->f_file;
		lock->fl.fl_pid = current->tgid;
		lock->fl.fl_lmops = &nlmsvc_lock_operations;
		nlmsvc_locks_init_निजी(&lock->fl, host, (pid_t)lock->svid);
		अगर (!lock->fl.fl_owner) अणु
			/* lockowner allocation has failed */
			nlmsvc_release_host(host);
			वापस nlm_lck_denied_nolocks;
		पूर्ण
	पूर्ण

	वापस 0;

no_locks:
	nlmsvc_release_host(host);
 	अगर (error)
		वापस error;	
	वापस nlm_lck_denied_nolocks;
पूर्ण

/*
 * शून्य: Test क्रम presence of service
 */
अटल __be32
nlm4svc_proc_null(काष्ठा svc_rqst *rqstp)
अणु
	dprपूर्णांकk("lockd: NULL          called\n");
	वापस rpc_success;
पूर्ण

/*
 * TEST: Check क्रम conflicting lock
 */
अटल __be32
__nlm4svc_proc_test(काष्ठा svc_rqst *rqstp, काष्ठा nlm_res *resp)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_host	*host;
	काष्ठा nlm_file	*file;
	__be32 rc = rpc_success;

	dprपूर्णांकk("lockd: TEST4        called\n");
	resp->cookie = argp->cookie;

	/* Obtain client and file */
	अगर ((resp->status = nlm4svc_retrieve_args(rqstp, argp, &host, &file)))
		वापस resp->status == nlm_drop_reply ? rpc_drop_reply :rpc_success;

	/* Now check क्रम conflicting locks */
	resp->status = nlmsvc_testlock(rqstp, file, host, &argp->lock, &resp->lock, &resp->cookie);
	अगर (resp->status == nlm_drop_reply)
		rc = rpc_drop_reply;
	अन्यथा
		dprपूर्णांकk("lockd: TEST4        status %d\n", ntohl(resp->status));

	nlmsvc_release_lockowner(&argp->lock);
	nlmsvc_release_host(host);
	nlm_release_file(file);
	वापस rc;
पूर्ण

अटल __be32
nlm4svc_proc_test(काष्ठा svc_rqst *rqstp)
अणु
	वापस __nlm4svc_proc_test(rqstp, rqstp->rq_resp);
पूर्ण

अटल __be32
__nlm4svc_proc_lock(काष्ठा svc_rqst *rqstp, काष्ठा nlm_res *resp)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_host	*host;
	काष्ठा nlm_file	*file;
	__be32 rc = rpc_success;

	dprपूर्णांकk("lockd: LOCK          called\n");

	resp->cookie = argp->cookie;

	/* Obtain client and file */
	अगर ((resp->status = nlm4svc_retrieve_args(rqstp, argp, &host, &file)))
		वापस resp->status == nlm_drop_reply ? rpc_drop_reply :rpc_success;

#अगर 0
	/* If supplied state करोesn't match current state, we assume it's
	 * an old request that समय-warped somehow. Any error वापस would
	 * करो in this हाल because it's irrelevant anyway.
	 *
	 * NB: We करोn't retrieve the remote host's state yet.
	 */
	अगर (host->h_nsmstate && host->h_nsmstate != argp->state) अणु
		resp->status = nlm_lck_denied_nolocks;
	पूर्ण अन्यथा
#पूर्ण_अगर

	/* Now try to lock the file */
	resp->status = nlmsvc_lock(rqstp, file, host, &argp->lock,
					argp->block, &argp->cookie,
					argp->reclaim);
	अगर (resp->status == nlm_drop_reply)
		rc = rpc_drop_reply;
	अन्यथा
		dprपूर्णांकk("lockd: LOCK         status %d\n", ntohl(resp->status));

	nlmsvc_release_lockowner(&argp->lock);
	nlmsvc_release_host(host);
	nlm_release_file(file);
	वापस rc;
पूर्ण

अटल __be32
nlm4svc_proc_lock(काष्ठा svc_rqst *rqstp)
अणु
	वापस __nlm4svc_proc_lock(rqstp, rqstp->rq_resp);
पूर्ण

अटल __be32
__nlm4svc_proc_cancel(काष्ठा svc_rqst *rqstp, काष्ठा nlm_res *resp)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_host	*host;
	काष्ठा nlm_file	*file;

	dprपूर्णांकk("lockd: CANCEL        called\n");

	resp->cookie = argp->cookie;

	/* Don't accept requests during grace period */
	अगर (locks_in_grace(SVC_NET(rqstp))) अणु
		resp->status = nlm_lck_denied_grace_period;
		वापस rpc_success;
	पूर्ण

	/* Obtain client and file */
	अगर ((resp->status = nlm4svc_retrieve_args(rqstp, argp, &host, &file)))
		वापस resp->status == nlm_drop_reply ? rpc_drop_reply :rpc_success;

	/* Try to cancel request. */
	resp->status = nlmsvc_cancel_blocked(SVC_NET(rqstp), file, &argp->lock);

	dprपूर्णांकk("lockd: CANCEL        status %d\n", ntohl(resp->status));
	nlmsvc_release_lockowner(&argp->lock);
	nlmsvc_release_host(host);
	nlm_release_file(file);
	वापस rpc_success;
पूर्ण

अटल __be32
nlm4svc_proc_cancel(काष्ठा svc_rqst *rqstp)
अणु
	वापस __nlm4svc_proc_cancel(rqstp, rqstp->rq_resp);
पूर्ण

/*
 * UNLOCK: release a lock
 */
अटल __be32
__nlm4svc_proc_unlock(काष्ठा svc_rqst *rqstp, काष्ठा nlm_res *resp)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_host	*host;
	काष्ठा nlm_file	*file;

	dprपूर्णांकk("lockd: UNLOCK        called\n");

	resp->cookie = argp->cookie;

	/* Don't accept new lock requests during grace period */
	अगर (locks_in_grace(SVC_NET(rqstp))) अणु
		resp->status = nlm_lck_denied_grace_period;
		वापस rpc_success;
	पूर्ण

	/* Obtain client and file */
	अगर ((resp->status = nlm4svc_retrieve_args(rqstp, argp, &host, &file)))
		वापस resp->status == nlm_drop_reply ? rpc_drop_reply :rpc_success;

	/* Now try to हटाओ the lock */
	resp->status = nlmsvc_unlock(SVC_NET(rqstp), file, &argp->lock);

	dprपूर्णांकk("lockd: UNLOCK        status %d\n", ntohl(resp->status));
	nlmsvc_release_lockowner(&argp->lock);
	nlmsvc_release_host(host);
	nlm_release_file(file);
	वापस rpc_success;
पूर्ण

अटल __be32
nlm4svc_proc_unlock(काष्ठा svc_rqst *rqstp)
अणु
	वापस __nlm4svc_proc_unlock(rqstp, rqstp->rq_resp);
पूर्ण

/*
 * GRANTED: A server calls us to tell that a process' lock request
 * was granted
 */
अटल __be32
__nlm4svc_proc_granted(काष्ठा svc_rqst *rqstp, काष्ठा nlm_res *resp)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;

	resp->cookie = argp->cookie;

	dprपूर्णांकk("lockd: GRANTED       called\n");
	resp->status = nlmclnt_grant(svc_addr(rqstp), &argp->lock);
	dprपूर्णांकk("lockd: GRANTED       status %d\n", ntohl(resp->status));
	वापस rpc_success;
पूर्ण

अटल __be32
nlm4svc_proc_granted(काष्ठा svc_rqst *rqstp)
अणु
	वापस __nlm4svc_proc_granted(rqstp, rqstp->rq_resp);
पूर्ण

/*
 * This is the generic lockd callback क्रम async RPC calls
 */
अटल व्योम nlm4svc_callback_निकास(काष्ठा rpc_task *task, व्योम *data)
अणु
	dprपूर्णांकk("lockd: %5u callback returned %d\n", task->tk_pid,
			-task->tk_status);
पूर्ण

अटल व्योम nlm4svc_callback_release(व्योम *data)
अणु
	nlmsvc_release_call(data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nlm4svc_callback_ops = अणु
	.rpc_call_करोne = nlm4svc_callback_निकास,
	.rpc_release = nlm4svc_callback_release,
पूर्ण;

/*
 * `Async' versions of the above service routines. They aren't really,
 * because we send the callback beक्रमe the reply proper. I hope this
 * करोesn't अवरोध any clients.
 */
अटल __be32 nlm4svc_callback(काष्ठा svc_rqst *rqstp, u32 proc,
		__be32 (*func)(काष्ठा svc_rqst *,  काष्ठा nlm_res *))
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_host	*host;
	काष्ठा nlm_rqst	*call;
	__be32 stat;

	host = nlmsvc_lookup_host(rqstp,
				  argp->lock.caller,
				  argp->lock.len);
	अगर (host == शून्य)
		वापस rpc_प्रणाली_err;

	call = nlm_alloc_call(host);
	nlmsvc_release_host(host);
	अगर (call == शून्य)
		वापस rpc_प्रणाली_err;

	stat = func(rqstp, &call->a_res);
	अगर (stat != 0) अणु
		nlmsvc_release_call(call);
		वापस stat;
	पूर्ण

	call->a_flags = RPC_TASK_ASYNC;
	अगर (nlm_async_reply(call, proc, &nlm4svc_callback_ops) < 0)
		वापस rpc_प्रणाली_err;
	वापस rpc_success;
पूर्ण

अटल __be32 nlm4svc_proc_test_msg(काष्ठा svc_rqst *rqstp)
अणु
	dprपूर्णांकk("lockd: TEST_MSG      called\n");
	वापस nlm4svc_callback(rqstp, NLMPROC_TEST_RES, __nlm4svc_proc_test);
पूर्ण

अटल __be32 nlm4svc_proc_lock_msg(काष्ठा svc_rqst *rqstp)
अणु
	dprपूर्णांकk("lockd: LOCK_MSG      called\n");
	वापस nlm4svc_callback(rqstp, NLMPROC_LOCK_RES, __nlm4svc_proc_lock);
पूर्ण

अटल __be32 nlm4svc_proc_cancel_msg(काष्ठा svc_rqst *rqstp)
अणु
	dprपूर्णांकk("lockd: CANCEL_MSG    called\n");
	वापस nlm4svc_callback(rqstp, NLMPROC_CANCEL_RES, __nlm4svc_proc_cancel);
पूर्ण

अटल __be32 nlm4svc_proc_unlock_msg(काष्ठा svc_rqst *rqstp)
अणु
	dprपूर्णांकk("lockd: UNLOCK_MSG    called\n");
	वापस nlm4svc_callback(rqstp, NLMPROC_UNLOCK_RES, __nlm4svc_proc_unlock);
पूर्ण

अटल __be32 nlm4svc_proc_granted_msg(काष्ठा svc_rqst *rqstp)
अणु
	dprपूर्णांकk("lockd: GRANTED_MSG   called\n");
	वापस nlm4svc_callback(rqstp, NLMPROC_GRANTED_RES, __nlm4svc_proc_granted);
पूर्ण

/*
 * SHARE: create a DOS share or alter existing share.
 */
अटल __be32
nlm4svc_proc_share(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_res *resp = rqstp->rq_resp;
	काष्ठा nlm_host	*host;
	काष्ठा nlm_file	*file;

	dprपूर्णांकk("lockd: SHARE         called\n");

	resp->cookie = argp->cookie;

	/* Don't accept new lock requests during grace period */
	अगर (locks_in_grace(SVC_NET(rqstp)) && !argp->reclaim) अणु
		resp->status = nlm_lck_denied_grace_period;
		वापस rpc_success;
	पूर्ण

	/* Obtain client and file */
	अगर ((resp->status = nlm4svc_retrieve_args(rqstp, argp, &host, &file)))
		वापस resp->status == nlm_drop_reply ? rpc_drop_reply :rpc_success;

	/* Now try to create the share */
	resp->status = nlmsvc_share_file(host, file, argp);

	dprपूर्णांकk("lockd: SHARE         status %d\n", ntohl(resp->status));
	nlmsvc_release_lockowner(&argp->lock);
	nlmsvc_release_host(host);
	nlm_release_file(file);
	वापस rpc_success;
पूर्ण

/*
 * UNSHARE: Release a DOS share.
 */
अटल __be32
nlm4svc_proc_unshare(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_res *resp = rqstp->rq_resp;
	काष्ठा nlm_host	*host;
	काष्ठा nlm_file	*file;

	dprपूर्णांकk("lockd: UNSHARE       called\n");

	resp->cookie = argp->cookie;

	/* Don't accept requests during grace period */
	अगर (locks_in_grace(SVC_NET(rqstp))) अणु
		resp->status = nlm_lck_denied_grace_period;
		वापस rpc_success;
	पूर्ण

	/* Obtain client and file */
	अगर ((resp->status = nlm4svc_retrieve_args(rqstp, argp, &host, &file)))
		वापस resp->status == nlm_drop_reply ? rpc_drop_reply :rpc_success;

	/* Now try to lock the file */
	resp->status = nlmsvc_unshare_file(host, file, argp);

	dprपूर्णांकk("lockd: UNSHARE       status %d\n", ntohl(resp->status));
	nlmsvc_release_lockowner(&argp->lock);
	nlmsvc_release_host(host);
	nlm_release_file(file);
	वापस rpc_success;
पूर्ण

/*
 * NM_LOCK: Create an unmonitored lock
 */
अटल __be32
nlm4svc_proc_nm_lock(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;

	dprपूर्णांकk("lockd: NM_LOCK       called\n");

	argp->monitor = 0;		/* just clean the monitor flag */
	वापस nlm4svc_proc_lock(rqstp);
पूर्ण

/*
 * FREE_ALL: Release all locks and shares held by client
 */
अटल __be32
nlm4svc_proc_मुक्त_all(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_host	*host;

	/* Obtain client */
	अगर (nlm4svc_retrieve_args(rqstp, argp, &host, शून्य))
		वापस rpc_success;

	nlmsvc_मुक्त_host_resources(host);
	nlmsvc_release_host(host);
	वापस rpc_success;
पूर्ण

/*
 * SM_NOTIFY: निजी callback from statd (not part of official NLM proto)
 */
अटल __be32
nlm4svc_proc_sm_notअगरy(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nlm_reboot *argp = rqstp->rq_argp;

	dprपूर्णांकk("lockd: SM_NOTIFY     called\n");

	अगर (!nlm_privileged_requester(rqstp)) अणु
		अक्षर buf[RPC_MAX_ADDRBUFLEN];
		prपूर्णांकk(KERN_WARNING "lockd: rejected NSM callback from %s\n",
				svc_prपूर्णांक_addr(rqstp, buf, माप(buf)));
		वापस rpc_प्रणाली_err;
	पूर्ण

	nlm_host_rebooted(SVC_NET(rqstp), argp);
	वापस rpc_success;
पूर्ण

/*
 * client sent a GRANTED_RES, let's हटाओ the associated block
 */
अटल __be32
nlm4svc_proc_granted_res(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nlm_res *argp = rqstp->rq_argp;

        अगर (!nlmsvc_ops)
                वापस rpc_success;

        dprपूर्णांकk("lockd: GRANTED_RES   called\n");

        nlmsvc_grant_reply(&argp->cookie, argp->status);
        वापस rpc_success;
पूर्ण

अटल __be32
nlm4svc_proc_unused(काष्ठा svc_rqst *rqstp)
अणु
	वापस rpc_proc_unavail;
पूर्ण


/*
 * NLM Server procedures.
 */

काष्ठा nlm_व्योम			अणु पूर्णांक dummy; पूर्ण;

#घोषणा	Ck	(1+XDR_QUADLEN(NLM_MAXCOOKIELEN))	/* cookie */
#घोषणा	No	(1+1024/4)				/* netobj */
#घोषणा	St	1					/* status */
#घोषणा	Rg	4					/* range (offset + length) */

स्थिर काष्ठा svc_procedure nlmsvc_procedures4[24] = अणु
	[NLMPROC_शून्य] = अणु
		.pc_func = nlm4svc_proc_null,
		.pc_decode = nlm4svc_decode_व्योम,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_व्योम),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "NULL",
	पूर्ण,
	[NLMPROC_TEST] = अणु
		.pc_func = nlm4svc_proc_test,
		.pc_decode = nlm4svc_decode_testargs,
		.pc_encode = nlm4svc_encode_testres,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_res),
		.pc_xdrressize = Ck+St+2+No+Rg,
		.pc_name = "TEST",
	पूर्ण,
	[NLMPROC_LOCK] = अणु
		.pc_func = nlm4svc_proc_lock,
		.pc_decode = nlm4svc_decode_lockargs,
		.pc_encode = nlm4svc_encode_res,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_res),
		.pc_xdrressize = Ck+St,
		.pc_name = "LOCK",
	पूर्ण,
	[NLMPROC_CANCEL] = अणु
		.pc_func = nlm4svc_proc_cancel,
		.pc_decode = nlm4svc_decode_cancargs,
		.pc_encode = nlm4svc_encode_res,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_res),
		.pc_xdrressize = Ck+St,
		.pc_name = "CANCEL",
	पूर्ण,
	[NLMPROC_UNLOCK] = अणु
		.pc_func = nlm4svc_proc_unlock,
		.pc_decode = nlm4svc_decode_unlockargs,
		.pc_encode = nlm4svc_encode_res,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_res),
		.pc_xdrressize = Ck+St,
		.pc_name = "UNLOCK",
	पूर्ण,
	[NLMPROC_GRANTED] = अणु
		.pc_func = nlm4svc_proc_granted,
		.pc_decode = nlm4svc_decode_testargs,
		.pc_encode = nlm4svc_encode_res,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_res),
		.pc_xdrressize = Ck+St,
		.pc_name = "GRANTED",
	पूर्ण,
	[NLMPROC_TEST_MSG] = अणु
		.pc_func = nlm4svc_proc_test_msg,
		.pc_decode = nlm4svc_decode_testargs,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "TEST_MSG",
	पूर्ण,
	[NLMPROC_LOCK_MSG] = अणु
		.pc_func = nlm4svc_proc_lock_msg,
		.pc_decode = nlm4svc_decode_lockargs,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "LOCK_MSG",
	पूर्ण,
	[NLMPROC_CANCEL_MSG] = अणु
		.pc_func = nlm4svc_proc_cancel_msg,
		.pc_decode = nlm4svc_decode_cancargs,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "CANCEL_MSG",
	पूर्ण,
	[NLMPROC_UNLOCK_MSG] = अणु
		.pc_func = nlm4svc_proc_unlock_msg,
		.pc_decode = nlm4svc_decode_unlockargs,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "UNLOCK_MSG",
	पूर्ण,
	[NLMPROC_GRANTED_MSG] = अणु
		.pc_func = nlm4svc_proc_granted_msg,
		.pc_decode = nlm4svc_decode_testargs,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "GRANTED_MSG",
	पूर्ण,
	[NLMPROC_TEST_RES] = अणु
		.pc_func = nlm4svc_proc_null,
		.pc_decode = nlm4svc_decode_व्योम,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_res),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "TEST_RES",
	पूर्ण,
	[NLMPROC_LOCK_RES] = अणु
		.pc_func = nlm4svc_proc_null,
		.pc_decode = nlm4svc_decode_व्योम,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_res),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "LOCK_RES",
	पूर्ण,
	[NLMPROC_CANCEL_RES] = अणु
		.pc_func = nlm4svc_proc_null,
		.pc_decode = nlm4svc_decode_व्योम,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_res),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "CANCEL_RES",
	पूर्ण,
	[NLMPROC_UNLOCK_RES] = अणु
		.pc_func = nlm4svc_proc_null,
		.pc_decode = nlm4svc_decode_व्योम,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_res),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "UNLOCK_RES",
	पूर्ण,
	[NLMPROC_GRANTED_RES] = अणु
		.pc_func = nlm4svc_proc_granted_res,
		.pc_decode = nlm4svc_decode_res,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_res),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "GRANTED_RES",
	पूर्ण,
	[NLMPROC_NSM_NOTIFY] = अणु
		.pc_func = nlm4svc_proc_sm_notअगरy,
		.pc_decode = nlm4svc_decode_reboot,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_reboot),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "SM_NOTIFY",
	पूर्ण,
	[17] = अणु
		.pc_func = nlm4svc_proc_unused,
		.pc_decode = nlm4svc_decode_व्योम,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_व्योम),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = 0,
		.pc_name = "UNUSED",
	पूर्ण,
	[18] = अणु
		.pc_func = nlm4svc_proc_unused,
		.pc_decode = nlm4svc_decode_व्योम,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_व्योम),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = 0,
		.pc_name = "UNUSED",
	पूर्ण,
	[19] = अणु
		.pc_func = nlm4svc_proc_unused,
		.pc_decode = nlm4svc_decode_व्योम,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_व्योम),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = 0,
		.pc_name = "UNUSED",
	पूर्ण,
	[NLMPROC_SHARE] = अणु
		.pc_func = nlm4svc_proc_share,
		.pc_decode = nlm4svc_decode_shareargs,
		.pc_encode = nlm4svc_encode_shareres,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_res),
		.pc_xdrressize = Ck+St+1,
		.pc_name = "SHARE",
	पूर्ण,
	[NLMPROC_UNSHARE] = अणु
		.pc_func = nlm4svc_proc_unshare,
		.pc_decode = nlm4svc_decode_shareargs,
		.pc_encode = nlm4svc_encode_shareres,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_res),
		.pc_xdrressize = Ck+St+1,
		.pc_name = "UNSHARE",
	पूर्ण,
	[NLMPROC_NM_LOCK] = अणु
		.pc_func = nlm4svc_proc_nm_lock,
		.pc_decode = nlm4svc_decode_lockargs,
		.pc_encode = nlm4svc_encode_res,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_res),
		.pc_xdrressize = Ck+St,
		.pc_name = "NM_LOCK",
	पूर्ण,
	[NLMPROC_FREE_ALL] = अणु
		.pc_func = nlm4svc_proc_मुक्त_all,
		.pc_decode = nlm4svc_decode_notअगरy,
		.pc_encode = nlm4svc_encode_व्योम,
		.pc_argsize = माप(काष्ठा nlm_args),
		.pc_ressize = माप(काष्ठा nlm_व्योम),
		.pc_xdrressize = St,
		.pc_name = "FREE_ALL",
	पूर्ण,
पूर्ण;
