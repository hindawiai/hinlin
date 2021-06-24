<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/lockd/svc.c
 *
 * This is the central lockd service.
 *
 * FIXME: Separate the lockd NFS server functionality from the lockd NFS
 * 	  client functionality. Oh why didn't Sun create two separate
 *	  services in the first place?
 *
 * Authors:	Olaf Kirch (okir@monad.swb.de)
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/moduleparam.h>

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/in.h>
#समावेश <linux/uपन.स>
#समावेश <linux/smp.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/inetdevice.h>

#समावेश <linux/sunrpc/types.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <net/ip.h>
#समावेश <net/addrconf.h>
#समावेश <net/ipv6.h>
#समावेश <linux/lockd/lockd.h>
#समावेश <linux/nfs.h>

#समावेश "netns.h"
#समावेश "procfs.h"

#घोषणा NLMDBG_FACILITY		NLMDBG_SVC
#घोषणा LOCKD_बफ_मानE		(1024 + NLMSVC_XDRSIZE)
#घोषणा ALLOWED_SIGS		(sigmask(SIGKILL))

अटल काष्ठा svc_program	nlmsvc_program;

स्थिर काष्ठा nlmsvc_binding	*nlmsvc_ops;
EXPORT_SYMBOL_GPL(nlmsvc_ops);

अटल DEFINE_MUTEX(nlmsvc_mutex);
अटल अचिन्हित पूर्णांक		nlmsvc_users;
अटल काष्ठा task_काष्ठा	*nlmsvc_task;
अटल काष्ठा svc_rqst		*nlmsvc_rqst;
अचिन्हित दीर्घ			nlmsvc_समयout;

अटल atomic_t nlm_ntf_refcnt = ATOMIC_INIT(0);
अटल DECLARE_WAIT_QUEUE_HEAD(nlm_ntf_wq);

अचिन्हित पूर्णांक lockd_net_id;

/*
 * These can be set at insmod समय (useful क्रम NFS as root fileप्रणाली),
 * and also changed through the sysctl पूर्णांकerface.  -- Jamie Lokier, Aug 2003
 */
अटल अचिन्हित दीर्घ		nlm_grace_period;
अटल अचिन्हित दीर्घ		nlm_समयout = LOCKD_DFLT_TIMEO;
अटल पूर्णांक			nlm_udpport, nlm_tcpport;

/* RLIM_NOखाता शेषs to 1024. That seems like a reasonable शेष here. */
अटल अचिन्हित पूर्णांक		nlm_max_connections = 1024;

/*
 * Constants needed क्रम the sysctl पूर्णांकerface.
 */
अटल स्थिर अचिन्हित दीर्घ	nlm_grace_period_min = 0;
अटल स्थिर अचिन्हित दीर्घ	nlm_grace_period_max = 240;
अटल स्थिर अचिन्हित दीर्घ	nlm_समयout_min = 3;
अटल स्थिर अचिन्हित दीर्घ	nlm_समयout_max = 20;
अटल स्थिर पूर्णांक		nlm_port_min = 0, nlm_port_max = 65535;

#अगर_घोषित CONFIG_SYSCTL
अटल काष्ठा ctl_table_header * nlm_sysctl_table;
#पूर्ण_अगर

अटल अचिन्हित दीर्घ get_lockd_grace_period(व्योम)
अणु
	/* Note: nlm_समयout should always be nonzero */
	अगर (nlm_grace_period)
		वापस roundup(nlm_grace_period, nlm_समयout) * HZ;
	अन्यथा
		वापस nlm_समयout * 5 * HZ;
पूर्ण

अटल व्योम grace_ender(काष्ठा work_काष्ठा *grace)
अणु
	काष्ठा delayed_work *dwork = to_delayed_work(grace);
	काष्ठा lockd_net *ln = container_of(dwork, काष्ठा lockd_net,
					    grace_period_end);

	locks_end_grace(&ln->lockd_manager);
पूर्ण

अटल व्योम set_grace_period(काष्ठा net *net)
अणु
	अचिन्हित दीर्घ grace_period = get_lockd_grace_period();
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

	locks_start_grace(net, &ln->lockd_manager);
	cancel_delayed_work_sync(&ln->grace_period_end);
	schedule_delayed_work(&ln->grace_period_end, grace_period);
पूर्ण

अटल व्योम restart_grace(व्योम)
अणु
	अगर (nlmsvc_ops) अणु
		काष्ठा net *net = &init_net;
		काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

		cancel_delayed_work_sync(&ln->grace_period_end);
		locks_end_grace(&ln->lockd_manager);
		nlmsvc_invalidate_all();
		set_grace_period(net);
	पूर्ण
पूर्ण

/*
 * This is the lockd kernel thपढ़ो
 */
अटल पूर्णांक
lockd(व्योम *vrqstp)
अणु
	पूर्णांक		err = 0;
	काष्ठा svc_rqst *rqstp = vrqstp;
	काष्ठा net *net = &init_net;
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

	/* try_to_मुक्तze() is called from svc_recv() */
	set_मुक्तzable();

	/* Allow SIGKILL to tell lockd to drop all of its locks */
	allow_संकेत(SIGKILL);

	dprपूर्णांकk("NFS locking service started (ver " LOCKD_VERSION ").\n");

	/*
	 * The मुख्य request loop. We करोn't terminate until the last
	 * NFS mount or NFS daemon has gone away.
	 */
	जबतक (!kthपढ़ो_should_stop()) अणु
		दीर्घ समयout = MAX_SCHEDULE_TIMEOUT;
		RPC_IFDEBUG(अक्षर buf[RPC_MAX_ADDRBUFLEN]);

		/* update sv_maxconn अगर it has changed */
		rqstp->rq_server->sv_maxconn = nlm_max_connections;

		अगर (संकेतled()) अणु
			flush_संकेतs(current);
			restart_grace();
			जारी;
		पूर्ण

		समयout = nlmsvc_retry_blocked();

		/*
		 * Find a socket with data available and call its
		 * recvfrom routine.
		 */
		err = svc_recv(rqstp, समयout);
		अगर (err == -EAGAIN || err == -EINTR)
			जारी;
		dprपूर्णांकk("lockd: request from %s\n",
				svc_prपूर्णांक_addr(rqstp, buf, माप(buf)));

		svc_process(rqstp);
	पूर्ण
	flush_संकेतs(current);
	अगर (nlmsvc_ops)
		nlmsvc_invalidate_all();
	nlm_shutकरोwn_hosts();
	cancel_delayed_work_sync(&ln->grace_period_end);
	locks_end_grace(&ln->lockd_manager);
	वापस 0;
पूर्ण

अटल पूर्णांक create_lockd_listener(काष्ठा svc_serv *serv, स्थिर अक्षर *name,
				 काष्ठा net *net, स्थिर पूर्णांक family,
				 स्थिर अचिन्हित लघु port,
				 स्थिर काष्ठा cred *cred)
अणु
	काष्ठा svc_xprt *xprt;

	xprt = svc_find_xprt(serv, name, net, family, 0);
	अगर (xprt == शून्य)
		वापस svc_create_xprt(serv, name, net, family, port,
						SVC_SOCK_DEFAULTS, cred);
	svc_xprt_put(xprt);
	वापस 0;
पूर्ण

अटल पूर्णांक create_lockd_family(काष्ठा svc_serv *serv, काष्ठा net *net,
			       स्थिर पूर्णांक family, स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक err;

	err = create_lockd_listener(serv, "udp", net, family, nlm_udpport,
			cred);
	अगर (err < 0)
		वापस err;

	वापस create_lockd_listener(serv, "tcp", net, family, nlm_tcpport,
			cred);
पूर्ण

/*
 * Ensure there are active UDP and TCP listeners क्रम lockd.
 *
 * Even अगर we have only TCP NFS mounts and/or TCP NFSDs, some
 * local services (such as rpc.statd) still require UDP, and
 * some NFS servers करो not yet support NLM over TCP.
 *
 * Returns zero अगर all listeners are available; otherwise a
 * negative त्रुटि_सं value is वापसed.
 */
अटल पूर्णांक make_socks(काष्ठा svc_serv *serv, काष्ठा net *net,
		स्थिर काष्ठा cred *cred)
अणु
	अटल पूर्णांक warned;
	पूर्णांक err;

	err = create_lockd_family(serv, net, PF_INET, cred);
	अगर (err < 0)
		जाओ out_err;

	err = create_lockd_family(serv, net, PF_INET6, cred);
	अगर (err < 0 && err != -EAFNOSUPPORT)
		जाओ out_err;

	warned = 0;
	वापस 0;

out_err:
	अगर (warned++ == 0)
		prपूर्णांकk(KERN_WARNING
			"lockd_up: makesock failed, error=%d\n", err);
	svc_shutकरोwn_net(serv, net);
	वापस err;
पूर्ण

अटल पूर्णांक lockd_up_net(काष्ठा svc_serv *serv, काष्ठा net *net,
		स्थिर काष्ठा cred *cred)
अणु
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);
	पूर्णांक error;

	अगर (ln->nlmsvc_users++)
		वापस 0;

	error = svc_bind(serv, net);
	अगर (error)
		जाओ err_bind;

	error = make_socks(serv, net, cred);
	अगर (error < 0)
		जाओ err_bind;
	set_grace_period(net);
	dprपूर्णांकk("%s: per-net data created; net=%x\n", __func__, net->ns.inum);
	वापस 0;

err_bind:
	ln->nlmsvc_users--;
	वापस error;
पूर्ण

अटल व्योम lockd_करोwn_net(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

	अगर (ln->nlmsvc_users) अणु
		अगर (--ln->nlmsvc_users == 0) अणु
			nlm_shutकरोwn_hosts_net(net);
			cancel_delayed_work_sync(&ln->grace_period_end);
			locks_end_grace(&ln->lockd_manager);
			svc_shutकरोwn_net(serv, net);
			dprपूर्णांकk("%s: per-net data destroyed; net=%x\n",
				__func__, net->ns.inum);
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("%s: no users! task=%p, net=%x\n",
			__func__, nlmsvc_task, net->ns.inum);
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक lockd_inetaddr_event(काष्ठा notअगरier_block *this,
	अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = (काष्ठा in_अगरaddr *)ptr;
	काष्ठा sockaddr_in sin;

	अगर ((event != NETDEV_DOWN) ||
	    !atomic_inc_not_zero(&nlm_ntf_refcnt))
		जाओ out;

	अगर (nlmsvc_rqst) अणु
		dprपूर्णांकk("lockd_inetaddr_event: removed %pI4\n",
			&अगरa->अगरa_local);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = अगरa->अगरa_local;
		svc_age_temp_xprts_now(nlmsvc_rqst->rq_server,
			(काष्ठा sockaddr *)&sin);
	पूर्ण
	atomic_dec(&nlm_ntf_refcnt);
	wake_up(&nlm_ntf_wq);

out:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block lockd_inetaddr_notअगरier = अणु
	.notअगरier_call = lockd_inetaddr_event,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक lockd_inet6addr_event(काष्ठा notअगरier_block *this,
	अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा inet6_अगरaddr *अगरa = (काष्ठा inet6_अगरaddr *)ptr;
	काष्ठा sockaddr_in6 sin6;

	अगर ((event != NETDEV_DOWN) ||
	    !atomic_inc_not_zero(&nlm_ntf_refcnt))
		जाओ out;

	अगर (nlmsvc_rqst) अणु
		dprपूर्णांकk("lockd_inet6addr_event: removed %pI6\n", &अगरa->addr);
		sin6.sin6_family = AF_INET6;
		sin6.sin6_addr = अगरa->addr;
		अगर (ipv6_addr_type(&sin6.sin6_addr) & IPV6_ADDR_LINKLOCAL)
			sin6.sin6_scope_id = अगरa->idev->dev->अगरindex;
		svc_age_temp_xprts_now(nlmsvc_rqst->rq_server,
			(काष्ठा sockaddr *)&sin6);
	पूर्ण
	atomic_dec(&nlm_ntf_refcnt);
	wake_up(&nlm_ntf_wq);

out:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block lockd_inet6addr_notअगरier = अणु
	.notअगरier_call = lockd_inet6addr_event,
पूर्ण;
#पूर्ण_अगर

अटल व्योम lockd_unरेजिस्टर_notअगरiers(व्योम)
अणु
	unरेजिस्टर_inetaddr_notअगरier(&lockd_inetaddr_notअगरier);
#अगर IS_ENABLED(CONFIG_IPV6)
	unरेजिस्टर_inet6addr_notअगरier(&lockd_inet6addr_notअगरier);
#पूर्ण_अगर
	रुको_event(nlm_ntf_wq, atomic_पढ़ो(&nlm_ntf_refcnt) == 0);
पूर्ण

अटल व्योम lockd_svc_निकास_thपढ़ो(व्योम)
अणु
	atomic_dec(&nlm_ntf_refcnt);
	lockd_unरेजिस्टर_notअगरiers();
	svc_निकास_thपढ़ो(nlmsvc_rqst);
पूर्ण

अटल पूर्णांक lockd_start_svc(काष्ठा svc_serv *serv)
अणु
	पूर्णांक error;

	अगर (nlmsvc_rqst)
		वापस 0;

	/*
	 * Create the kernel thपढ़ो and रुको क्रम it to start.
	 */
	nlmsvc_rqst = svc_prepare_thपढ़ो(serv, &serv->sv_pools[0], NUMA_NO_NODE);
	अगर (IS_ERR(nlmsvc_rqst)) अणु
		error = PTR_ERR(nlmsvc_rqst);
		prपूर्णांकk(KERN_WARNING
			"lockd_up: svc_rqst allocation failed, error=%d\n",
			error);
		lockd_unरेजिस्टर_notअगरiers();
		जाओ out_rqst;
	पूर्ण

	atomic_inc(&nlm_ntf_refcnt);
	svc_sock_update_bufs(serv);
	serv->sv_maxconn = nlm_max_connections;

	nlmsvc_task = kthपढ़ो_create(lockd, nlmsvc_rqst, "%s", serv->sv_name);
	अगर (IS_ERR(nlmsvc_task)) अणु
		error = PTR_ERR(nlmsvc_task);
		prपूर्णांकk(KERN_WARNING
			"lockd_up: kthread_run failed, error=%d\n", error);
		जाओ out_task;
	पूर्ण
	nlmsvc_rqst->rq_task = nlmsvc_task;
	wake_up_process(nlmsvc_task);

	dprपूर्णांकk("lockd_up: service started\n");
	वापस 0;

out_task:
	lockd_svc_निकास_thपढ़ो();
	nlmsvc_task = शून्य;
out_rqst:
	nlmsvc_rqst = शून्य;
	वापस error;
पूर्ण

अटल स्थिर काष्ठा svc_serv_ops lockd_sv_ops = अणु
	.svo_shutकरोwn		= svc_rpcb_cleanup,
	.svo_enqueue_xprt	= svc_xprt_करो_enqueue,
पूर्ण;

अटल काष्ठा svc_serv *lockd_create_svc(व्योम)
अणु
	काष्ठा svc_serv *serv;

	/*
	 * Check whether we're alपढ़ोy up and running.
	 */
	अगर (nlmsvc_rqst) अणु
		/*
		 * Note: increase service usage, because later in हाल of error
		 * svc_destroy() will be called.
		 */
		svc_get(nlmsvc_rqst->rq_server);
		वापस nlmsvc_rqst->rq_server;
	पूर्ण

	/*
	 * Sanity check: अगर there's no pid,
	 * we should be the first user ...
	 */
	अगर (nlmsvc_users)
		prपूर्णांकk(KERN_WARNING
			"lockd_up: no pid, %d users??\n", nlmsvc_users);

	अगर (!nlm_समयout)
		nlm_समयout = LOCKD_DFLT_TIMEO;
	nlmsvc_समयout = nlm_समयout * HZ;

	serv = svc_create(&nlmsvc_program, LOCKD_बफ_मानE, &lockd_sv_ops);
	अगर (!serv) अणु
		prपूर्णांकk(KERN_WARNING "lockd_up: create service failed\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	रेजिस्टर_inetaddr_notअगरier(&lockd_inetaddr_notअगरier);
#अगर IS_ENABLED(CONFIG_IPV6)
	रेजिस्टर_inet6addr_notअगरier(&lockd_inet6addr_notअगरier);
#पूर्ण_अगर
	dprपूर्णांकk("lockd_up: service created\n");
	वापस serv;
पूर्ण

/*
 * Bring up the lockd process अगर it's not alपढ़ोy up.
 */
पूर्णांक lockd_up(काष्ठा net *net, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा svc_serv *serv;
	पूर्णांक error;

	mutex_lock(&nlmsvc_mutex);

	serv = lockd_create_svc();
	अगर (IS_ERR(serv)) अणु
		error = PTR_ERR(serv);
		जाओ err_create;
	पूर्ण

	error = lockd_up_net(serv, net, cred);
	अगर (error < 0) अणु
		lockd_unरेजिस्टर_notअगरiers();
		जाओ err_put;
	पूर्ण

	error = lockd_start_svc(serv);
	अगर (error < 0) अणु
		lockd_करोwn_net(serv, net);
		जाओ err_put;
	पूर्ण
	nlmsvc_users++;
	/*
	 * Note: svc_serv काष्ठाures have an initial use count of 1,
	 * so we निकास through here on both success and failure.
	 */
err_put:
	svc_destroy(serv);
err_create:
	mutex_unlock(&nlmsvc_mutex);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(lockd_up);

/*
 * Decrement the user count and bring करोwn lockd अगर we're the last.
 */
व्योम
lockd_करोwn(काष्ठा net *net)
अणु
	mutex_lock(&nlmsvc_mutex);
	lockd_करोwn_net(nlmsvc_rqst->rq_server, net);
	अगर (nlmsvc_users) अणु
		अगर (--nlmsvc_users)
			जाओ out;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "lockd_down: no users! task=%p\n",
			nlmsvc_task);
		BUG();
	पूर्ण

	अगर (!nlmsvc_task) अणु
		prपूर्णांकk(KERN_ERR "lockd_down: no lockd running.\n");
		BUG();
	पूर्ण
	kthपढ़ो_stop(nlmsvc_task);
	dprपूर्णांकk("lockd_down: service stopped\n");
	lockd_svc_निकास_thपढ़ो();
	dprपूर्णांकk("lockd_down: service destroyed\n");
	nlmsvc_task = शून्य;
	nlmsvc_rqst = शून्य;
out:
	mutex_unlock(&nlmsvc_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(lockd_करोwn);

#अगर_घोषित CONFIG_SYSCTL

/*
 * Sysctl parameters (same as module parameters, dअगरferent पूर्णांकerface).
 */

अटल काष्ठा ctl_table nlm_sysctls[] = अणु
	अणु
		.procname	= "nlm_grace_period",
		.data		= &nlm_grace_period,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
		.extra1		= (अचिन्हित दीर्घ *) &nlm_grace_period_min,
		.extra2		= (अचिन्हित दीर्घ *) &nlm_grace_period_max,
	पूर्ण,
	अणु
		.procname	= "nlm_timeout",
		.data		= &nlm_समयout,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
		.extra1		= (अचिन्हित दीर्घ *) &nlm_समयout_min,
		.extra2		= (अचिन्हित दीर्घ *) &nlm_समयout_max,
	पूर्ण,
	अणु
		.procname	= "nlm_udpport",
		.data		= &nlm_udpport,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (पूर्णांक *) &nlm_port_min,
		.extra2		= (पूर्णांक *) &nlm_port_max,
	पूर्ण,
	अणु
		.procname	= "nlm_tcpport",
		.data		= &nlm_tcpport,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (पूर्णांक *) &nlm_port_min,
		.extra2		= (पूर्णांक *) &nlm_port_max,
	पूर्ण,
	अणु
		.procname	= "nsm_use_hostnames",
		.data		= &nsm_use_hostnames,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "nsm_local_state",
		.data		= &nsm_local_state,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table nlm_sysctl_dir[] = अणु
	अणु
		.procname	= "nfs",
		.mode		= 0555,
		.child		= nlm_sysctls,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table nlm_sysctl_root[] = अणु
	अणु
		.procname	= "fs",
		.mode		= 0555,
		.child		= nlm_sysctl_dir,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

#पूर्ण_अगर	/* CONFIG_SYSCTL */

/*
 * Module (and sysfs) parameters.
 */

#घोषणा param_set_min_max(name, type, which_म_से_दीर्घ, min, max)		\
अटल पूर्णांक param_set_##name(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp) \
अणु									\
	अक्षर *endp;							\
	__typeof__(type) num = which_म_से_दीर्घ(val, &endp, 0);		\
	अगर (endp == val || *endp || num < (min) || num > (max))		\
		वापस -EINVAL;						\
	*((type *) kp->arg) = num;					\
	वापस 0;							\
पूर्ण

अटल अंतरभूत पूर्णांक is_callback(u32 proc)
अणु
	वापस proc == NLMPROC_GRANTED
		|| proc == NLMPROC_GRANTED_MSG
		|| proc == NLMPROC_TEST_RES
		|| proc == NLMPROC_LOCK_RES
		|| proc == NLMPROC_CANCEL_RES
		|| proc == NLMPROC_UNLOCK_RES
		|| proc == NLMPROC_NSM_NOTIFY;
पूर्ण


अटल पूर्णांक lockd_authenticate(काष्ठा svc_rqst *rqstp)
अणु
	rqstp->rq_client = शून्य;
	चयन (rqstp->rq_authop->flavour) अणु
		हाल RPC_AUTH_शून्य:
		हाल RPC_AUTH_UNIX:
			अगर (rqstp->rq_proc == 0)
				वापस SVC_OK;
			अगर (is_callback(rqstp->rq_proc)) अणु
				/* Leave it to inभागidual procedures to
				 * call nlmsvc_lookup_host(rqstp)
				 */
				वापस SVC_OK;
			पूर्ण
			वापस svc_set_client(rqstp);
	पूर्ण
	वापस SVC_DENIED;
पूर्ण


param_set_min_max(port, पूर्णांक, simple_म_से_दीर्घ, 0, 65535)
param_set_min_max(grace_period, अचिन्हित दीर्घ, simple_म_से_अदीर्घ,
		  nlm_grace_period_min, nlm_grace_period_max)
param_set_min_max(समयout, अचिन्हित दीर्घ, simple_म_से_अदीर्घ,
		  nlm_समयout_min, nlm_समयout_max)

MODULE_AUTHOR("Olaf Kirch <okir@monad.swb.de>");
MODULE_DESCRIPTION("NFS file locking service version " LOCKD_VERSION ".");
MODULE_LICENSE("GPL");

module_param_call(nlm_grace_period, param_set_grace_period, param_get_uदीर्घ,
		  &nlm_grace_period, 0644);
module_param_call(nlm_समयout, param_set_समयout, param_get_uदीर्घ,
		  &nlm_समयout, 0644);
module_param_call(nlm_udpport, param_set_port, param_get_पूर्णांक,
		  &nlm_udpport, 0644);
module_param_call(nlm_tcpport, param_set_port, param_get_पूर्णांक,
		  &nlm_tcpport, 0644);
module_param(nsm_use_hostnames, bool, 0644);
module_param(nlm_max_connections, uपूर्णांक, 0644);

अटल पूर्णांक lockd_init_net(काष्ठा net *net)
अणु
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

	INIT_DELAYED_WORK(&ln->grace_period_end, grace_ender);
	INIT_LIST_HEAD(&ln->lockd_manager.list);
	ln->lockd_manager.block_खोलोs = false;
	INIT_LIST_HEAD(&ln->nsm_handles);
	वापस 0;
पूर्ण

अटल व्योम lockd_निकास_net(काष्ठा net *net)
अणु
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

	WARN_ONCE(!list_empty(&ln->lockd_manager.list),
		  "net %x %s: lockd_manager.list is not empty\n",
		  net->ns.inum, __func__);
	WARN_ONCE(!list_empty(&ln->nsm_handles),
		  "net %x %s: nsm_handles list is not empty\n",
		  net->ns.inum, __func__);
	WARN_ONCE(delayed_work_pending(&ln->grace_period_end),
		  "net %x %s: grace_period_end was not cancelled\n",
		  net->ns.inum, __func__);
पूर्ण

अटल काष्ठा pernet_operations lockd_net_ops = अणु
	.init = lockd_init_net,
	.निकास = lockd_निकास_net,
	.id = &lockd_net_id,
	.size = माप(काष्ठा lockd_net),
पूर्ण;


/*
 * Initialising and terminating the module.
 */

अटल पूर्णांक __init init_nlm(व्योम)
अणु
	पूर्णांक err;

#अगर_घोषित CONFIG_SYSCTL
	err = -ENOMEM;
	nlm_sysctl_table = रेजिस्टर_sysctl_table(nlm_sysctl_root);
	अगर (nlm_sysctl_table == शून्य)
		जाओ err_sysctl;
#पूर्ण_अगर
	err = रेजिस्टर_pernet_subsys(&lockd_net_ops);
	अगर (err)
		जाओ err_pernet;

	err = lockd_create_procfs();
	अगर (err)
		जाओ err_procfs;

	वापस 0;

err_procfs:
	unरेजिस्टर_pernet_subsys(&lockd_net_ops);
err_pernet:
#अगर_घोषित CONFIG_SYSCTL
	unरेजिस्टर_sysctl_table(nlm_sysctl_table);
err_sysctl:
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास निकास_nlm(व्योम)
अणु
	/* FIXME: delete all NLM clients */
	nlm_shutकरोwn_hosts();
	lockd_हटाओ_procfs();
	unरेजिस्टर_pernet_subsys(&lockd_net_ops);
#अगर_घोषित CONFIG_SYSCTL
	unरेजिस्टर_sysctl_table(nlm_sysctl_table);
#पूर्ण_अगर
पूर्ण

module_init(init_nlm);
module_निकास(निकास_nlm);

/*
 * Define NLM program and procedures
 */
अटल अचिन्हित पूर्णांक nlmsvc_version1_count[17];
अटल स्थिर काष्ठा svc_version	nlmsvc_version1 = अणु
	.vs_vers	= 1,
	.vs_nproc	= 17,
	.vs_proc	= nlmsvc_procedures,
	.vs_count	= nlmsvc_version1_count,
	.vs_xdrsize	= NLMSVC_XDRSIZE,
पूर्ण;
अटल अचिन्हित पूर्णांक nlmsvc_version3_count[24];
अटल स्थिर काष्ठा svc_version	nlmsvc_version3 = अणु
	.vs_vers	= 3,
	.vs_nproc	= 24,
	.vs_proc	= nlmsvc_procedures,
	.vs_count	= nlmsvc_version3_count,
	.vs_xdrsize	= NLMSVC_XDRSIZE,
पूर्ण;
#अगर_घोषित CONFIG_LOCKD_V4
अटल अचिन्हित पूर्णांक nlmsvc_version4_count[24];
अटल स्थिर काष्ठा svc_version	nlmsvc_version4 = अणु
	.vs_vers	= 4,
	.vs_nproc	= 24,
	.vs_proc	= nlmsvc_procedures4,
	.vs_count	= nlmsvc_version4_count,
	.vs_xdrsize	= NLMSVC_XDRSIZE,
पूर्ण;
#पूर्ण_अगर
अटल स्थिर काष्ठा svc_version *nlmsvc_version[] = अणु
	[1] = &nlmsvc_version1,
	[3] = &nlmsvc_version3,
#अगर_घोषित CONFIG_LOCKD_V4
	[4] = &nlmsvc_version4,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा svc_stat		nlmsvc_stats;

#घोषणा NLM_NRVERS	ARRAY_SIZE(nlmsvc_version)
अटल काष्ठा svc_program	nlmsvc_program = अणु
	.pg_prog		= NLM_PROGRAM,		/* program number */
	.pg_nvers		= NLM_NRVERS,		/* number of entries in nlmsvc_version */
	.pg_vers		= nlmsvc_version,	/* version table */
	.pg_name		= "lockd",		/* service name */
	.pg_class		= "nfsd",		/* share authentication with nfsd */
	.pg_stats		= &nlmsvc_stats,	/* stats table */
	.pg_authenticate	= &lockd_authenticate,	/* export authentication */
	.pg_init_request	= svc_generic_init_request,
	.pg_rpcbind_set		= svc_generic_rpcbind_set,
पूर्ण;
