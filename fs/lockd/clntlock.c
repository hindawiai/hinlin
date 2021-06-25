<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/lockd/clntlock.c
 *
 * Lock handling क्रम the client side NLM implementation
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/lockd/lockd.h>
#समावेश <linux/kthपढ़ो.h>

#घोषणा NLMDBG_FACILITY		NLMDBG_CLIENT

/*
 * Local function prototypes
 */
अटल पूर्णांक			reclaimer(व्योम *ptr);

/*
 * The following functions handle blocking and granting from the
 * client perspective.
 */

/*
 * This is the representation of a blocked client lock.
 */
काष्ठा nlm_रुको अणु
	काष्ठा list_head	b_list;		/* linked list */
	रुको_queue_head_t	b_रुको;		/* where to रुको on */
	काष्ठा nlm_host *	b_host;
	काष्ठा file_lock *	b_lock;		/* local file lock */
	अचिन्हित लघु		b_reclaim;	/* got to reclaim lock */
	__be32			b_status;	/* grant callback status */
पूर्ण;

अटल LIST_HEAD(nlm_blocked);
अटल DEFINE_SPINLOCK(nlm_blocked_lock);

/**
 * nlmclnt_init - Set up per-NFS mount poपूर्णांक lockd data काष्ठाures
 * @nlm_init: poपूर्णांकer to arguments काष्ठाure
 *
 * Returns poपूर्णांकer to an appropriate nlm_host काष्ठा,
 * or an ERR_PTR value.
 */
काष्ठा nlm_host *nlmclnt_init(स्थिर काष्ठा nlmclnt_initdata *nlm_init)
अणु
	काष्ठा nlm_host *host;
	u32 nlm_version = (nlm_init->nfs_version == 2) ? 1 : 4;
	पूर्णांक status;

	status = lockd_up(nlm_init->net, nlm_init->cred);
	अगर (status < 0)
		वापस ERR_PTR(status);

	host = nlmclnt_lookup_host(nlm_init->address, nlm_init->addrlen,
				   nlm_init->protocol, nlm_version,
				   nlm_init->hostname, nlm_init->noresvport,
				   nlm_init->net, nlm_init->cred);
	अगर (host == शून्य)
		जाओ out_nohost;
	अगर (host->h_rpcclnt == शून्य && nlm_bind_host(host) == शून्य)
		जाओ out_nobind;

	host->h_nlmclnt_ops = nlm_init->nlmclnt_ops;
	वापस host;
out_nobind:
	nlmclnt_release_host(host);
out_nohost:
	lockd_करोwn(nlm_init->net);
	वापस ERR_PTR(-ENOLCK);
पूर्ण
EXPORT_SYMBOL_GPL(nlmclnt_init);

/**
 * nlmclnt_करोne - Release resources allocated by nlmclnt_init()
 * @host: nlm_host काष्ठाure reserved by nlmclnt_init()
 *
 */
व्योम nlmclnt_करोne(काष्ठा nlm_host *host)
अणु
	काष्ठा net *net = host->net;

	nlmclnt_release_host(host);
	lockd_करोwn(net);
पूर्ण
EXPORT_SYMBOL_GPL(nlmclnt_करोne);

/*
 * Queue up a lock क्रम blocking so that the GRANTED request can see it
 */
काष्ठा nlm_रुको *nlmclnt_prepare_block(काष्ठा nlm_host *host, काष्ठा file_lock *fl)
अणु
	काष्ठा nlm_रुको *block;

	block = kदो_स्मृति(माप(*block), GFP_KERNEL);
	अगर (block != शून्य) अणु
		block->b_host = host;
		block->b_lock = fl;
		init_रुकोqueue_head(&block->b_रुको);
		block->b_status = nlm_lck_blocked;

		spin_lock(&nlm_blocked_lock);
		list_add(&block->b_list, &nlm_blocked);
		spin_unlock(&nlm_blocked_lock);
	पूर्ण
	वापस block;
पूर्ण

व्योम nlmclnt_finish_block(काष्ठा nlm_रुको *block)
अणु
	अगर (block == शून्य)
		वापस;
	spin_lock(&nlm_blocked_lock);
	list_del(&block->b_list);
	spin_unlock(&nlm_blocked_lock);
	kमुक्त(block);
पूर्ण

/*
 * Block on a lock
 */
पूर्णांक nlmclnt_block(काष्ठा nlm_रुको *block, काष्ठा nlm_rqst *req, दीर्घ समयout)
अणु
	दीर्घ ret;

	/* A borken server might ask us to block even अगर we didn't
	 * request it. Just say no!
	 */
	अगर (block == शून्य)
		वापस -EAGAIN;

	/* Go to sleep रुकोing क्रम GRANT callback. Some servers seem
	 * to lose callbacks, however, so we're going to poll from
	 * समय to समय just to make sure.
	 *
	 * For now, the retry frequency is pretty high; normally 
	 * a 1 minute समयout would करो. See the comment beक्रमe
	 * nlmclnt_lock क्रम an explanation.
	 */
	ret = रुको_event_पूर्णांकerruptible_समयout(block->b_रुको,
			block->b_status != nlm_lck_blocked,
			समयout);
	अगर (ret < 0)
		वापस -ERESTARTSYS;
	/* Reset the lock status after a server reboot so we resend */
	अगर (block->b_status == nlm_lck_denied_grace_period)
		block->b_status = nlm_lck_blocked;
	req->a_res.status = block->b_status;
	वापस 0;
पूर्ण

/*
 * The server lockd has called us back to tell us the lock was granted
 */
__be32 nlmclnt_grant(स्थिर काष्ठा sockaddr *addr, स्थिर काष्ठा nlm_lock *lock)
अणु
	स्थिर काष्ठा file_lock *fl = &lock->fl;
	स्थिर काष्ठा nfs_fh *fh = &lock->fh;
	काष्ठा nlm_रुको	*block;
	__be32 res = nlm_lck_denied;

	/*
	 * Look up blocked request based on arguments. 
	 * Warning: must not use cookie to match it!
	 */
	spin_lock(&nlm_blocked_lock);
	list_क्रम_each_entry(block, &nlm_blocked, b_list) अणु
		काष्ठा file_lock *fl_blocked = block->b_lock;

		अगर (fl_blocked->fl_start != fl->fl_start)
			जारी;
		अगर (fl_blocked->fl_end != fl->fl_end)
			जारी;
		/*
		 * Careful! The NLM server will वापस the 32-bit "pid" that
		 * we put on the wire: in this हाल the lockowner "pid".
		 */
		अगर (fl_blocked->fl_u.nfs_fl.owner->pid != lock->svid)
			जारी;
		अगर (!rpc_cmp_addr(nlm_addr(block->b_host), addr))
			जारी;
		अगर (nfs_compare_fh(NFS_FH(locks_inode(fl_blocked->fl_file)), fh) != 0)
			जारी;
		/* Alright, we found a lock. Set the वापस status
		 * and wake up the caller
		 */
		block->b_status = nlm_granted;
		wake_up(&block->b_रुको);
		res = nlm_granted;
	पूर्ण
	spin_unlock(&nlm_blocked_lock);
	वापस res;
पूर्ण

/*
 * The following procedures deal with the recovery of locks after a
 * server crash.
 */

/*
 * Reclaim all locks on server host. We करो this by spawning a separate
 * reclaimer thपढ़ो.
 */
व्योम
nlmclnt_recovery(काष्ठा nlm_host *host)
अणु
	काष्ठा task_काष्ठा *task;

	अगर (!host->h_reclaiming++) अणु
		nlm_get_host(host);
		task = kthपढ़ो_run(reclaimer, host, "%s-reclaim", host->h_name);
		अगर (IS_ERR(task))
			prपूर्णांकk(KERN_ERR "lockd: unable to spawn reclaimer "
				"thread. Locks for %s won't be reclaimed! "
				"(%ld)\n", host->h_name, PTR_ERR(task));
	पूर्ण
पूर्ण

अटल पूर्णांक
reclaimer(व्योम *ptr)
अणु
	काष्ठा nlm_host	  *host = (काष्ठा nlm_host *) ptr;
	काष्ठा nlm_रुको	  *block;
	काष्ठा nlm_rqst   *req;
	काष्ठा file_lock *fl, *next;
	u32 nsmstate;
	काष्ठा net *net = host->net;

	req = kदो_स्मृति(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस 0;

	allow_संकेत(SIGKILL);

	करोwn_ग_लिखो(&host->h_rwsem);
	lockd_up(net, शून्य);	/* note: this cannot fail as lockd is alपढ़ोy running */

	dprपूर्णांकk("lockd: reclaiming locks for host %s\n", host->h_name);

restart:
	nsmstate = host->h_nsmstate;

	/* Force a porपंचांगap getport - the peer's lockd will
	 * most likely end up on a dअगरferent port.
	 */
	host->h_nextrebind = jअगरfies;
	nlm_rebind_host(host);

	/* First, reclaim all locks that have been granted. */
	list_splice_init(&host->h_granted, &host->h_reclaim);
	list_क्रम_each_entry_safe(fl, next, &host->h_reclaim, fl_u.nfs_fl.list) अणु
		list_del_init(&fl->fl_u.nfs_fl.list);

		/*
		 * sending this thपढ़ो a SIGKILL will result in any unreclaimed
		 * locks being हटाओd from the h_granted list. This means that
		 * the kernel will not attempt to reclaim them again अगर a new
		 * reclaimer thपढ़ो is spawned क्रम this host.
		 */
		अगर (संकेतled())
			जारी;
		अगर (nlmclnt_reclaim(host, fl, req) != 0)
			जारी;
		list_add_tail(&fl->fl_u.nfs_fl.list, &host->h_granted);
		अगर (host->h_nsmstate != nsmstate) अणु
			/* Argh! The server rebooted again! */
			जाओ restart;
		पूर्ण
	पूर्ण

	host->h_reclaiming = 0;
	up_ग_लिखो(&host->h_rwsem);
	dprपूर्णांकk("NLM: done reclaiming locks for host %s\n", host->h_name);

	/* Now, wake up all processes that sleep on a blocked lock */
	spin_lock(&nlm_blocked_lock);
	list_क्रम_each_entry(block, &nlm_blocked, b_list) अणु
		अगर (block->b_host == host) अणु
			block->b_status = nlm_lck_denied_grace_period;
			wake_up(&block->b_रुको);
		पूर्ण
	पूर्ण
	spin_unlock(&nlm_blocked_lock);

	/* Release host handle after use */
	nlmclnt_release_host(host);
	lockd_करोwn(net);
	kमुक्त(req);
	वापस 0;
पूर्ण
