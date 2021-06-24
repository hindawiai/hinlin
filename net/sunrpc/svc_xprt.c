<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/svc_xprt.c
 *
 * Author: Tom Tucker <tom@खोलोgridcomputing.com>
 */

#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/xprt.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <trace/events/sunrpc.h>

#घोषणा RPCDBG_FACILITY	RPCDBG_SVCXPRT

अटल अचिन्हित पूर्णांक svc_rpc_per_connection_limit __पढ़ो_mostly;
module_param(svc_rpc_per_connection_limit, uपूर्णांक, 0644);


अटल काष्ठा svc_deferred_req *svc_deferred_dequeue(काष्ठा svc_xprt *xprt);
अटल पूर्णांक svc_deferred_recv(काष्ठा svc_rqst *rqstp);
अटल काष्ठा cache_deferred_req *svc_defer(काष्ठा cache_req *req);
अटल व्योम svc_age_temp_xprts(काष्ठा समयr_list *t);
अटल व्योम svc_delete_xprt(काष्ठा svc_xprt *xprt);

/* apparently the "standard" is that clients बंद
 * idle connections after 5 minutes, servers after
 * 6 minutes
 *   http://nfsv4bat.org/Documents/ConnectAThon/1996/nfstcp.pdf
 */
अटल पूर्णांक svc_conn_age_period = 6*60;

/* List of रेजिस्टरed transport classes */
अटल DEFINE_SPINLOCK(svc_xprt_class_lock);
अटल LIST_HEAD(svc_xprt_class_list);

/* SMP locking strategy:
 *
 *	svc_pool->sp_lock protects most of the fields of that pool.
 *	svc_serv->sv_lock protects sv_tempsocks, sv_permsocks, sv_पंचांगpcnt.
 *	when both need to be taken (rare), svc_serv->sv_lock is first.
 *	The "service mutex" protects svc_serv->sv_nrthपढ़ो.
 *	svc_sock->sk_lock protects the svc_sock->sk_deferred list
 *             and the ->sk_info_authunix cache.
 *
 *	The XPT_BUSY bit in xprt->xpt_flags prevents a transport being
 *	enqueued multiply. During normal transport processing this bit
 *	is set by svc_xprt_enqueue and cleared by svc_xprt_received.
 *	Providers should not manipulate this bit directly.
 *
 *	Some flags can be set to certain values at any समय
 *	providing that certain rules are followed:
 *
 *	XPT_CONN, XPT_DATA:
 *		- Can be set or cleared at any समय.
 *		- After a set, svc_xprt_enqueue must be called to enqueue
 *		  the transport क्रम processing.
 *		- After a clear, the transport must be पढ़ो/accepted.
 *		  If this succeeds, it must be set again.
 *	XPT_CLOSE:
 *		- Can set at any समय. It is never cleared.
 *      XPT_DEAD:
 *		- Can only be set जबतक XPT_BUSY is held which ensures
 *		  that no other thपढ़ो will be using the transport or will
 *		  try to set XPT_DEAD.
 */
पूर्णांक svc_reg_xprt_class(काष्ठा svc_xprt_class *xcl)
अणु
	काष्ठा svc_xprt_class *cl;
	पूर्णांक res = -EEXIST;

	dprपूर्णांकk("svc: Adding svc transport class '%s'\n", xcl->xcl_name);

	INIT_LIST_HEAD(&xcl->xcl_list);
	spin_lock(&svc_xprt_class_lock);
	/* Make sure there isn't alपढ़ोy a class with the same name */
	list_क्रम_each_entry(cl, &svc_xprt_class_list, xcl_list) अणु
		अगर (म_भेद(xcl->xcl_name, cl->xcl_name) == 0)
			जाओ out;
	पूर्ण
	list_add_tail(&xcl->xcl_list, &svc_xprt_class_list);
	res = 0;
out:
	spin_unlock(&svc_xprt_class_lock);
	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(svc_reg_xprt_class);

व्योम svc_unreg_xprt_class(काष्ठा svc_xprt_class *xcl)
अणु
	dprपूर्णांकk("svc: Removing svc transport class '%s'\n", xcl->xcl_name);
	spin_lock(&svc_xprt_class_lock);
	list_del_init(&xcl->xcl_list);
	spin_unlock(&svc_xprt_class_lock);
पूर्ण
EXPORT_SYMBOL_GPL(svc_unreg_xprt_class);

/**
 * svc_prपूर्णांक_xprts - Format the transport list क्रम prपूर्णांकing
 * @buf: target buffer क्रम क्रमmatted address
 * @maxlen: length of target buffer
 *
 * Fills in @buf with a string containing a list of transport names, each name
 * terminated with '\n'. If the buffer is too small, some entries may be
 * missing, but it is guaranteed that all lines in the output buffer are
 * complete.
 *
 * Returns positive length of the filled-in string.
 */
पूर्णांक svc_prपूर्णांक_xprts(अक्षर *buf, पूर्णांक maxlen)
अणु
	काष्ठा svc_xprt_class *xcl;
	अक्षर पंचांगpstr[80];
	पूर्णांक len = 0;
	buf[0] = '\0';

	spin_lock(&svc_xprt_class_lock);
	list_क्रम_each_entry(xcl, &svc_xprt_class_list, xcl_list) अणु
		पूर्णांक slen;

		slen = snम_लिखो(पंचांगpstr, माप(पंचांगpstr), "%s %d\n",
				xcl->xcl_name, xcl->xcl_max_payload);
		अगर (slen >= माप(पंचांगpstr) || len + slen >= maxlen)
			अवरोध;
		len += slen;
		म_जोड़ो(buf, पंचांगpstr);
	पूर्ण
	spin_unlock(&svc_xprt_class_lock);

	वापस len;
पूर्ण

/**
 * svc_xprt_deferred_बंद - Close a transport
 * @xprt: transport instance
 *
 * Used in contexts that need to defer the work of shutting करोwn
 * the transport to an nfsd thपढ़ो.
 */
व्योम svc_xprt_deferred_बंद(काष्ठा svc_xprt *xprt)
अणु
	अगर (!test_and_set_bit(XPT_CLOSE, &xprt->xpt_flags))
		svc_xprt_enqueue(xprt);
पूर्ण
EXPORT_SYMBOL_GPL(svc_xprt_deferred_बंद);

अटल व्योम svc_xprt_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा svc_xprt *xprt =
		container_of(kref, काष्ठा svc_xprt, xpt_ref);
	काष्ठा module *owner = xprt->xpt_class->xcl_owner;
	अगर (test_bit(XPT_CACHE_AUTH, &xprt->xpt_flags))
		svcauth_unix_info_release(xprt);
	put_cred(xprt->xpt_cred);
	put_net(xprt->xpt_net);
	/* See comment on corresponding get in xs_setup_bc_tcp(): */
	अगर (xprt->xpt_bc_xprt)
		xprt_put(xprt->xpt_bc_xprt);
	अगर (xprt->xpt_bc_xps)
		xprt_चयन_put(xprt->xpt_bc_xps);
	trace_svc_xprt_मुक्त(xprt);
	xprt->xpt_ops->xpo_मुक्त(xprt);
	module_put(owner);
पूर्ण

व्योम svc_xprt_put(काष्ठा svc_xprt *xprt)
अणु
	kref_put(&xprt->xpt_ref, svc_xprt_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(svc_xprt_put);

/*
 * Called by transport drivers to initialize the transport independent
 * portion of the transport instance.
 */
व्योम svc_xprt_init(काष्ठा net *net, काष्ठा svc_xprt_class *xcl,
		   काष्ठा svc_xprt *xprt, काष्ठा svc_serv *serv)
अणु
	स_रखो(xprt, 0, माप(*xprt));
	xprt->xpt_class = xcl;
	xprt->xpt_ops = xcl->xcl_ops;
	kref_init(&xprt->xpt_ref);
	xprt->xpt_server = serv;
	INIT_LIST_HEAD(&xprt->xpt_list);
	INIT_LIST_HEAD(&xprt->xpt_पढ़ोy);
	INIT_LIST_HEAD(&xprt->xpt_deferred);
	INIT_LIST_HEAD(&xprt->xpt_users);
	mutex_init(&xprt->xpt_mutex);
	spin_lock_init(&xprt->xpt_lock);
	set_bit(XPT_BUSY, &xprt->xpt_flags);
	xprt->xpt_net = get_net(net);
	म_नकल(xprt->xpt_remotebuf, "uninitialized");
पूर्ण
EXPORT_SYMBOL_GPL(svc_xprt_init);

अटल काष्ठा svc_xprt *__svc_xpo_create(काष्ठा svc_xprt_class *xcl,
					 काष्ठा svc_serv *serv,
					 काष्ठा net *net,
					 स्थिर पूर्णांक family,
					 स्थिर अचिन्हित लघु port,
					 पूर्णांक flags)
अणु
	काष्ठा sockaddr_in sin = अणु
		.sin_family		= AF_INET,
		.sin_addr.s_addr	= htonl(INADDR_ANY),
		.sin_port		= htons(port),
	पूर्ण;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा sockaddr_in6 sin6 = अणु
		.sin6_family		= AF_INET6,
		.sin6_addr		= IN6ADDR_ANY_INIT,
		.sin6_port		= htons(port),
	पूर्ण;
#पूर्ण_अगर
	काष्ठा svc_xprt *xprt;
	काष्ठा sockaddr *sap;
	माप_प्रकार len;

	चयन (family) अणु
	हाल PF_INET:
		sap = (काष्ठा sockaddr *)&sin;
		len = माप(sin);
		अवरोध;
#अगर IS_ENABLED(CONFIG_IPV6)
	हाल PF_INET6:
		sap = (काष्ठा sockaddr *)&sin6;
		len = माप(sin6);
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस ERR_PTR(-EAFNOSUPPORT);
	पूर्ण

	xprt = xcl->xcl_ops->xpo_create(serv, net, sap, len, flags);
	अगर (IS_ERR(xprt))
		trace_svc_xprt_create_err(serv->sv_program->pg_name,
					  xcl->xcl_name, sap, xprt);
	वापस xprt;
पूर्ण

/**
 * svc_xprt_received - start next receiver thपढ़ो
 * @xprt: controlling transport
 *
 * The caller must hold the XPT_BUSY bit and must
 * not thereafter touch transport data.
 *
 * Note: XPT_DATA only माला_लो cleared when a पढ़ो-attempt finds no (or
 * insufficient) data.
 */
व्योम svc_xprt_received(काष्ठा svc_xprt *xprt)
अणु
	अगर (!test_bit(XPT_BUSY, &xprt->xpt_flags)) अणु
		WARN_ONCE(1, "xprt=0x%p already busy!", xprt);
		वापस;
	पूर्ण

	trace_svc_xprt_received(xprt);

	/* As soon as we clear busy, the xprt could be बंदd and
	 * 'put', so we need a reference to call svc_enqueue_xprt with:
	 */
	svc_xprt_get(xprt);
	smp_mb__beक्रमe_atomic();
	clear_bit(XPT_BUSY, &xprt->xpt_flags);
	xprt->xpt_server->sv_ops->svo_enqueue_xprt(xprt);
	svc_xprt_put(xprt);
पूर्ण
EXPORT_SYMBOL_GPL(svc_xprt_received);

व्योम svc_add_new_perm_xprt(काष्ठा svc_serv *serv, काष्ठा svc_xprt *new)
अणु
	clear_bit(XPT_TEMP, &new->xpt_flags);
	spin_lock_bh(&serv->sv_lock);
	list_add(&new->xpt_list, &serv->sv_permsocks);
	spin_unlock_bh(&serv->sv_lock);
	svc_xprt_received(new);
पूर्ण

अटल पूर्णांक _svc_create_xprt(काष्ठा svc_serv *serv, स्थिर अक्षर *xprt_name,
			    काष्ठा net *net, स्थिर पूर्णांक family,
			    स्थिर अचिन्हित लघु port, पूर्णांक flags,
			    स्थिर काष्ठा cred *cred)
अणु
	काष्ठा svc_xprt_class *xcl;

	spin_lock(&svc_xprt_class_lock);
	list_क्रम_each_entry(xcl, &svc_xprt_class_list, xcl_list) अणु
		काष्ठा svc_xprt *newxprt;
		अचिन्हित लघु newport;

		अगर (म_भेद(xprt_name, xcl->xcl_name))
			जारी;

		अगर (!try_module_get(xcl->xcl_owner))
			जाओ err;

		spin_unlock(&svc_xprt_class_lock);
		newxprt = __svc_xpo_create(xcl, serv, net, family, port, flags);
		अगर (IS_ERR(newxprt)) अणु
			module_put(xcl->xcl_owner);
			वापस PTR_ERR(newxprt);
		पूर्ण
		newxprt->xpt_cred = get_cred(cred);
		svc_add_new_perm_xprt(serv, newxprt);
		newport = svc_xprt_local_port(newxprt);
		वापस newport;
	पूर्ण
 err:
	spin_unlock(&svc_xprt_class_lock);
	/* This त्रुटि_सं is exposed to user space.  Provide a reasonable
	 * लिखो_त्रुटि msg क्रम a bad transport. */
	वापस -EPROTONOSUPPORT;
पूर्ण

पूर्णांक svc_create_xprt(काष्ठा svc_serv *serv, स्थिर अक्षर *xprt_name,
		    काष्ठा net *net, स्थिर पूर्णांक family,
		    स्थिर अचिन्हित लघु port, पूर्णांक flags,
		    स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक err;

	err = _svc_create_xprt(serv, xprt_name, net, family, port, flags, cred);
	अगर (err == -EPROTONOSUPPORT) अणु
		request_module("svc%s", xprt_name);
		err = _svc_create_xprt(serv, xprt_name, net, family, port, flags, cred);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(svc_create_xprt);

/*
 * Copy the local and remote xprt addresses to the rqstp काष्ठाure
 */
व्योम svc_xprt_copy_addrs(काष्ठा svc_rqst *rqstp, काष्ठा svc_xprt *xprt)
अणु
	स_नकल(&rqstp->rq_addr, &xprt->xpt_remote, xprt->xpt_remotelen);
	rqstp->rq_addrlen = xprt->xpt_remotelen;

	/*
	 * Destination address in request is needed क्रम binding the
	 * source address in RPC replies/callbacks later.
	 */
	स_नकल(&rqstp->rq_daddr, &xprt->xpt_local, xprt->xpt_locallen);
	rqstp->rq_daddrlen = xprt->xpt_locallen;
पूर्ण
EXPORT_SYMBOL_GPL(svc_xprt_copy_addrs);

/**
 * svc_prपूर्णांक_addr - Format rq_addr field क्रम prपूर्णांकing
 * @rqstp: svc_rqst काष्ठा containing address to prपूर्णांक
 * @buf: target buffer क्रम क्रमmatted address
 * @len: length of target buffer
 *
 */
अक्षर *svc_prपूर्णांक_addr(काष्ठा svc_rqst *rqstp, अक्षर *buf, माप_प्रकार len)
अणु
	वापस __svc_prपूर्णांक_addr(svc_addr(rqstp), buf, len);
पूर्ण
EXPORT_SYMBOL_GPL(svc_prपूर्णांक_addr);

अटल bool svc_xprt_slots_in_range(काष्ठा svc_xprt *xprt)
अणु
	अचिन्हित पूर्णांक limit = svc_rpc_per_connection_limit;
	पूर्णांक nrqsts = atomic_पढ़ो(&xprt->xpt_nr_rqsts);

	वापस limit == 0 || (nrqsts >= 0 && nrqsts < limit);
पूर्ण

अटल bool svc_xprt_reserve_slot(काष्ठा svc_rqst *rqstp, काष्ठा svc_xprt *xprt)
अणु
	अगर (!test_bit(RQ_DATA, &rqstp->rq_flags)) अणु
		अगर (!svc_xprt_slots_in_range(xprt))
			वापस false;
		atomic_inc(&xprt->xpt_nr_rqsts);
		set_bit(RQ_DATA, &rqstp->rq_flags);
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम svc_xprt_release_slot(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_xprt	*xprt = rqstp->rq_xprt;
	अगर (test_and_clear_bit(RQ_DATA, &rqstp->rq_flags)) अणु
		atomic_dec(&xprt->xpt_nr_rqsts);
		smp_wmb(); /* See smp_rmb() in svc_xprt_पढ़ोy() */
		svc_xprt_enqueue(xprt);
	पूर्ण
पूर्ण

अटल bool svc_xprt_पढ़ोy(काष्ठा svc_xprt *xprt)
अणु
	अचिन्हित दीर्घ xpt_flags;

	/*
	 * If another cpu has recently updated xpt_flags,
	 * sk_sock->flags, xpt_reserved, or xpt_nr_rqsts, we need to
	 * know about it; otherwise it's possible that both that cpu and
	 * this one could call svc_xprt_enqueue() without either
	 * svc_xprt_enqueue() recognizing that the conditions below
	 * are satisfied, and we could stall indefinitely:
	 */
	smp_rmb();
	xpt_flags = READ_ONCE(xprt->xpt_flags);

	अगर (xpt_flags & (BIT(XPT_CONN) | BIT(XPT_CLOSE)))
		वापस true;
	अगर (xpt_flags & (BIT(XPT_DATA) | BIT(XPT_DEFERRED))) अणु
		अगर (xprt->xpt_ops->xpo_has_wspace(xprt) &&
		    svc_xprt_slots_in_range(xprt))
			वापस true;
		trace_svc_xprt_no_ग_लिखो_space(xprt);
		वापस false;
	पूर्ण
	वापस false;
पूर्ण

व्योम svc_xprt_करो_enqueue(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_pool *pool;
	काष्ठा svc_rqst	*rqstp = शून्य;
	पूर्णांक cpu;

	अगर (!svc_xprt_पढ़ोy(xprt))
		वापस;

	/* Mark transport as busy. It will reमुख्य in this state until
	 * the provider calls svc_xprt_received. We update XPT_BUSY
	 * atomically because it also guards against trying to enqueue
	 * the transport twice.
	 */
	अगर (test_and_set_bit(XPT_BUSY, &xprt->xpt_flags))
		वापस;

	cpu = get_cpu();
	pool = svc_pool_क्रम_cpu(xprt->xpt_server, cpu);

	atomic_दीर्घ_inc(&pool->sp_stats.packets);

	spin_lock_bh(&pool->sp_lock);
	list_add_tail(&xprt->xpt_पढ़ोy, &pool->sp_sockets);
	pool->sp_stats.sockets_queued++;
	spin_unlock_bh(&pool->sp_lock);

	/* find a thपढ़ो क्रम this xprt */
	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(rqstp, &pool->sp_all_thपढ़ोs, rq_all) अणु
		अगर (test_and_set_bit(RQ_BUSY, &rqstp->rq_flags))
			जारी;
		atomic_दीर्घ_inc(&pool->sp_stats.thपढ़ोs_woken);
		rqstp->rq_qसमय = kसमय_get();
		wake_up_process(rqstp->rq_task);
		जाओ out_unlock;
	पूर्ण
	set_bit(SP_CONGESTED, &pool->sp_flags);
	rqstp = शून्य;
out_unlock:
	rcu_पढ़ो_unlock();
	put_cpu();
	trace_svc_xprt_करो_enqueue(xprt, rqstp);
पूर्ण
EXPORT_SYMBOL_GPL(svc_xprt_करो_enqueue);

/*
 * Queue up a transport with data pending. If there are idle nfsd
 * processes, wake 'em up.
 *
 */
व्योम svc_xprt_enqueue(काष्ठा svc_xprt *xprt)
अणु
	अगर (test_bit(XPT_BUSY, &xprt->xpt_flags))
		वापस;
	xprt->xpt_server->sv_ops->svo_enqueue_xprt(xprt);
पूर्ण
EXPORT_SYMBOL_GPL(svc_xprt_enqueue);

/*
 * Dequeue the first transport, अगर there is one.
 */
अटल काष्ठा svc_xprt *svc_xprt_dequeue(काष्ठा svc_pool *pool)
अणु
	काष्ठा svc_xprt	*xprt = शून्य;

	अगर (list_empty(&pool->sp_sockets))
		जाओ out;

	spin_lock_bh(&pool->sp_lock);
	अगर (likely(!list_empty(&pool->sp_sockets))) अणु
		xprt = list_first_entry(&pool->sp_sockets,
					काष्ठा svc_xprt, xpt_पढ़ोy);
		list_del_init(&xprt->xpt_पढ़ोy);
		svc_xprt_get(xprt);
	पूर्ण
	spin_unlock_bh(&pool->sp_lock);
out:
	वापस xprt;
पूर्ण

/**
 * svc_reserve - change the space reserved क्रम the reply to a request.
 * @rqstp:  The request in question
 * @space: new max space to reserve
 *
 * Each request reserves some space on the output queue of the transport
 * to make sure the reply fits.  This function reduces that reserved
 * space to be the amount of space used alपढ़ोy, plus @space.
 *
 */
व्योम svc_reserve(काष्ठा svc_rqst *rqstp, पूर्णांक space)
अणु
	काष्ठा svc_xprt *xprt = rqstp->rq_xprt;

	space += rqstp->rq_res.head[0].iov_len;

	अगर (xprt && space < rqstp->rq_reserved) अणु
		atomic_sub((rqstp->rq_reserved - space), &xprt->xpt_reserved);
		rqstp->rq_reserved = space;
		smp_wmb(); /* See smp_rmb() in svc_xprt_पढ़ोy() */
		svc_xprt_enqueue(xprt);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(svc_reserve);

अटल व्योम svc_xprt_release(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_xprt	*xprt = rqstp->rq_xprt;

	xprt->xpt_ops->xpo_release_rqst(rqstp);

	kमुक्त(rqstp->rq_deferred);
	rqstp->rq_deferred = शून्य;

	svc_मुक्त_res_pages(rqstp);
	rqstp->rq_res.page_len = 0;
	rqstp->rq_res.page_base = 0;

	/* Reset response buffer and release
	 * the reservation.
	 * But first, check that enough space was reserved
	 * क्रम the reply, otherwise we have a bug!
	 */
	अगर ((rqstp->rq_res.len) >  rqstp->rq_reserved)
		prपूर्णांकk(KERN_ERR "RPC request reserved %d but used %d\n",
		       rqstp->rq_reserved,
		       rqstp->rq_res.len);

	rqstp->rq_res.head[0].iov_len = 0;
	svc_reserve(rqstp, 0);
	svc_xprt_release_slot(rqstp);
	rqstp->rq_xprt = शून्य;
	svc_xprt_put(xprt);
पूर्ण

/*
 * Some svc_serv's will have occasional work to करो, even when a xprt is not
 * रुकोing to be serviced. This function is there to "kick" a task in one of
 * those services so that it can wake up and करो that work. Note that we only
 * bother with pool 0 as we करोn't need to wake up more than one thपढ़ो क्रम
 * this purpose.
 */
व्योम svc_wake_up(काष्ठा svc_serv *serv)
अणु
	काष्ठा svc_rqst	*rqstp;
	काष्ठा svc_pool *pool;

	pool = &serv->sv_pools[0];

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(rqstp, &pool->sp_all_thपढ़ोs, rq_all) अणु
		/* skip any that aren't queued */
		अगर (test_bit(RQ_BUSY, &rqstp->rq_flags))
			जारी;
		rcu_पढ़ो_unlock();
		wake_up_process(rqstp->rq_task);
		trace_svc_wake_up(rqstp->rq_task->pid);
		वापस;
	पूर्ण
	rcu_पढ़ो_unlock();

	/* No मुक्त entries available */
	set_bit(SP_TASK_PENDING, &pool->sp_flags);
	smp_wmb();
	trace_svc_wake_up(0);
पूर्ण
EXPORT_SYMBOL_GPL(svc_wake_up);

पूर्णांक svc_port_is_privileged(काष्ठा sockaddr *sin)
अणु
	चयन (sin->sa_family) अणु
	हाल AF_INET:
		वापस ntohs(((काष्ठा sockaddr_in *)sin)->sin_port)
			< PROT_SOCK;
	हाल AF_INET6:
		वापस ntohs(((काष्ठा sockaddr_in6 *)sin)->sin6_port)
			< PROT_SOCK;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Make sure that we करोn't have too many active connections. If we have,
 * something must be dropped. It's not clear what will happen अगर we allow
 * "too many" connections, but when dealing with network-facing software,
 * we have to code defensively. Here we करो that by imposing hard limits.
 *
 * There's no poपूर्णांक in trying to करो अक्रमom drop here क्रम DoS
 * prevention. The NFS clients करोes 1 reconnect in 15 seconds. An
 * attacker can easily beat that.
 *
 * The only somewhat efficient mechanism would be अगर drop old
 * connections from the same IP first. But right now we करोn't even
 * record the client IP in svc_sock.
 *
 * single-thपढ़ोed services that expect a lot of clients will probably
 * need to set sv_maxconn to override the शेष value which is based
 * on the number of thपढ़ोs
 */
अटल व्योम svc_check_conn_limits(काष्ठा svc_serv *serv)
अणु
	अचिन्हित पूर्णांक limit = serv->sv_maxconn ? serv->sv_maxconn :
				(serv->sv_nrthपढ़ोs+3) * 20;

	अगर (serv->sv_पंचांगpcnt > limit) अणु
		काष्ठा svc_xprt *xprt = शून्य;
		spin_lock_bh(&serv->sv_lock);
		अगर (!list_empty(&serv->sv_tempsocks)) अणु
			/* Try to help the admin */
			net_notice_ratelimited("%s: too many open connections, consider increasing the %s\n",
					       serv->sv_name, serv->sv_maxconn ?
					       "max number of connections" :
					       "number of threads");
			/*
			 * Always select the oldest connection. It's not fair,
			 * but so is lअगरe
			 */
			xprt = list_entry(serv->sv_tempsocks.prev,
					  काष्ठा svc_xprt,
					  xpt_list);
			set_bit(XPT_CLOSE, &xprt->xpt_flags);
			svc_xprt_get(xprt);
		पूर्ण
		spin_unlock_bh(&serv->sv_lock);

		अगर (xprt) अणु
			svc_xprt_enqueue(xprt);
			svc_xprt_put(xprt);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक svc_alloc_arg(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_serv *serv = rqstp->rq_server;
	काष्ठा xdr_buf *arg = &rqstp->rq_arg;
	अचिन्हित दीर्घ pages, filled;

	pages = (serv->sv_max_mesg + 2 * PAGE_SIZE) >> PAGE_SHIFT;
	अगर (pages > RPCSVC_MAXPAGES) अणु
		pr_warn_once("svc: warning: pages=%lu > RPCSVC_MAXPAGES=%lu\n",
			     pages, RPCSVC_MAXPAGES);
		/* use as many pages as possible */
		pages = RPCSVC_MAXPAGES;
	पूर्ण

	क्रम (;;) अणु
		filled = alloc_pages_bulk_array(GFP_KERNEL, pages,
						rqstp->rq_pages);
		अगर (filled == pages)
			अवरोध;

		set_current_state(TASK_INTERRUPTIBLE);
		अगर (संकेतled() || kthपढ़ो_should_stop()) अणु
			set_current_state(TASK_RUNNING);
			वापस -EINTR;
		पूर्ण
		schedule_समयout(msecs_to_jअगरfies(500));
	पूर्ण
	rqstp->rq_page_end = &rqstp->rq_pages[pages];
	rqstp->rq_pages[pages] = शून्य; /* this might be seen in nfsd_splice_actor() */

	/* Make arg->head poपूर्णांक to first page and arg->pages poपूर्णांक to rest */
	arg->head[0].iov_base = page_address(rqstp->rq_pages[0]);
	arg->head[0].iov_len = PAGE_SIZE;
	arg->pages = rqstp->rq_pages + 1;
	arg->page_base = 0;
	/* save at least one page क्रम response */
	arg->page_len = (pages-2)*PAGE_SIZE;
	arg->len = (pages-1)*PAGE_SIZE;
	arg->tail[0].iov_len = 0;
	वापस 0;
पूर्ण

अटल bool
rqst_should_sleep(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_pool		*pool = rqstp->rq_pool;

	/* did someone call svc_wake_up? */
	अगर (test_and_clear_bit(SP_TASK_PENDING, &pool->sp_flags))
		वापस false;

	/* was a socket queued? */
	अगर (!list_empty(&pool->sp_sockets))
		वापस false;

	/* are we shutting करोwn? */
	अगर (संकेतled() || kthपढ़ो_should_stop())
		वापस false;

	/* are we मुक्तzing? */
	अगर (मुक्तzing(current))
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा svc_xprt *svc_get_next_xprt(काष्ठा svc_rqst *rqstp, दीर्घ समयout)
अणु
	काष्ठा svc_pool		*pool = rqstp->rq_pool;
	दीर्घ			समय_left = 0;

	/* rq_xprt should be clear on entry */
	WARN_ON_ONCE(rqstp->rq_xprt);

	rqstp->rq_xprt = svc_xprt_dequeue(pool);
	अगर (rqstp->rq_xprt)
		जाओ out_found;

	/*
	 * We have to be able to पूर्णांकerrupt this रुको
	 * to bring करोwn the daemons ...
	 */
	set_current_state(TASK_INTERRUPTIBLE);
	smp_mb__beक्रमe_atomic();
	clear_bit(SP_CONGESTED, &pool->sp_flags);
	clear_bit(RQ_BUSY, &rqstp->rq_flags);
	smp_mb__after_atomic();

	अगर (likely(rqst_should_sleep(rqstp)))
		समय_left = schedule_समयout(समयout);
	अन्यथा
		__set_current_state(TASK_RUNNING);

	try_to_मुक्तze();

	set_bit(RQ_BUSY, &rqstp->rq_flags);
	smp_mb__after_atomic();
	rqstp->rq_xprt = svc_xprt_dequeue(pool);
	अगर (rqstp->rq_xprt)
		जाओ out_found;

	अगर (!समय_left)
		atomic_दीर्घ_inc(&pool->sp_stats.thपढ़ोs_समयकरोut);

	अगर (संकेतled() || kthपढ़ो_should_stop())
		वापस ERR_PTR(-EINTR);
	वापस ERR_PTR(-EAGAIN);
out_found:
	/* Normally we will रुको up to 5 seconds क्रम any required
	 * cache inक्रमmation to be provided.
	 */
	अगर (!test_bit(SP_CONGESTED, &pool->sp_flags))
		rqstp->rq_chandle.thपढ़ो_रुको = 5*HZ;
	अन्यथा
		rqstp->rq_chandle.thपढ़ो_रुको = 1*HZ;
	trace_svc_xprt_dequeue(rqstp);
	वापस rqstp->rq_xprt;
पूर्ण

अटल व्योम svc_add_new_temp_xprt(काष्ठा svc_serv *serv, काष्ठा svc_xprt *newxpt)
अणु
	spin_lock_bh(&serv->sv_lock);
	set_bit(XPT_TEMP, &newxpt->xpt_flags);
	list_add(&newxpt->xpt_list, &serv->sv_tempsocks);
	serv->sv_पंचांगpcnt++;
	अगर (serv->sv_tempसमयr.function == शून्य) अणु
		/* setup समयr to age temp transports */
		serv->sv_tempसमयr.function = svc_age_temp_xprts;
		mod_समयr(&serv->sv_tempसमयr,
			  jअगरfies + svc_conn_age_period * HZ);
	पूर्ण
	spin_unlock_bh(&serv->sv_lock);
	svc_xprt_received(newxpt);
पूर्ण

अटल पूर्णांक svc_handle_xprt(काष्ठा svc_rqst *rqstp, काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_serv *serv = rqstp->rq_server;
	पूर्णांक len = 0;

	अगर (test_bit(XPT_CLOSE, &xprt->xpt_flags)) अणु
		अगर (test_and_clear_bit(XPT_KILL_TEMP, &xprt->xpt_flags))
			xprt->xpt_ops->xpo_समाप्त_temp_xprt(xprt);
		svc_delete_xprt(xprt);
		/* Leave XPT_BUSY set on the dead xprt: */
		जाओ out;
	पूर्ण
	अगर (test_bit(XPT_LISTENER, &xprt->xpt_flags)) अणु
		काष्ठा svc_xprt *newxpt;
		/*
		 * We know this module_get will succeed because the
		 * listener holds a reference too
		 */
		__module_get(xprt->xpt_class->xcl_owner);
		svc_check_conn_limits(xprt->xpt_server);
		newxpt = xprt->xpt_ops->xpo_accept(xprt);
		अगर (newxpt) अणु
			newxpt->xpt_cred = get_cred(xprt->xpt_cred);
			svc_add_new_temp_xprt(serv, newxpt);
			trace_svc_xprt_accept(newxpt, serv->sv_name);
		पूर्ण अन्यथा अणु
			module_put(xprt->xpt_class->xcl_owner);
		पूर्ण
		svc_xprt_received(xprt);
	पूर्ण अन्यथा अगर (svc_xprt_reserve_slot(rqstp, xprt)) अणु
		/* XPT_DATA|XPT_DEFERRED हाल: */
		dprपूर्णांकk("svc: server %p, pool %u, transport %p, inuse=%d\n",
			rqstp, rqstp->rq_pool->sp_id, xprt,
			kref_पढ़ो(&xprt->xpt_ref));
		rqstp->rq_deferred = svc_deferred_dequeue(xprt);
		अगर (rqstp->rq_deferred)
			len = svc_deferred_recv(rqstp);
		अन्यथा
			len = xprt->xpt_ops->xpo_recvfrom(rqstp);
		rqstp->rq_sसमय = kसमय_get();
		rqstp->rq_reserved = serv->sv_max_mesg;
		atomic_add(rqstp->rq_reserved, &xprt->xpt_reserved);
	पूर्ण
out:
	trace_svc_handle_xprt(xprt, len);
	वापस len;
पूर्ण

/*
 * Receive the next request on any transport.  This code is carefully
 * organised not to touch any cachelines in the shared svc_serv
 * काष्ठाure, only cachelines in the local svc_pool.
 */
पूर्णांक svc_recv(काष्ठा svc_rqst *rqstp, दीर्घ समयout)
अणु
	काष्ठा svc_xprt		*xprt = शून्य;
	काष्ठा svc_serv		*serv = rqstp->rq_server;
	पूर्णांक			len, err;

	err = svc_alloc_arg(rqstp);
	अगर (err)
		जाओ out;

	try_to_मुक्तze();
	cond_resched();
	err = -EINTR;
	अगर (संकेतled() || kthपढ़ो_should_stop())
		जाओ out;

	xprt = svc_get_next_xprt(rqstp, समयout);
	अगर (IS_ERR(xprt)) अणु
		err = PTR_ERR(xprt);
		जाओ out;
	पूर्ण

	len = svc_handle_xprt(rqstp, xprt);

	/* No data, incomplete (TCP) पढ़ो, or accept() */
	err = -EAGAIN;
	अगर (len <= 0)
		जाओ out_release;
	trace_svc_xdr_recvfrom(&rqstp->rq_arg);

	clear_bit(XPT_OLD, &xprt->xpt_flags);

	xprt->xpt_ops->xpo_secure_port(rqstp);
	rqstp->rq_chandle.defer = svc_defer;
	rqstp->rq_xid = svc_getu32(&rqstp->rq_arg.head[0]);

	अगर (serv->sv_stats)
		serv->sv_stats->netcnt++;
	वापस len;
out_release:
	rqstp->rq_res.len = 0;
	svc_xprt_release(rqstp);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(svc_recv);

/*
 * Drop request
 */
व्योम svc_drop(काष्ठा svc_rqst *rqstp)
अणु
	trace_svc_drop(rqstp);
	svc_xprt_release(rqstp);
पूर्ण
EXPORT_SYMBOL_GPL(svc_drop);

/*
 * Return reply to client.
 */
पूर्णांक svc_send(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_xprt	*xprt;
	पूर्णांक		len = -EFAULT;
	काष्ठा xdr_buf	*xb;

	xprt = rqstp->rq_xprt;
	अगर (!xprt)
		जाओ out;

	/* calculate over-all length */
	xb = &rqstp->rq_res;
	xb->len = xb->head[0].iov_len +
		xb->page_len +
		xb->tail[0].iov_len;
	trace_svc_xdr_sendto(rqstp->rq_xid, xb);
	trace_svc_stats_latency(rqstp);

	len = xprt->xpt_ops->xpo_sendto(rqstp);

	trace_svc_send(rqstp, len);
	svc_xprt_release(rqstp);

	अगर (len == -ECONNREFUSED || len == -ENOTCONN || len == -EAGAIN)
		len = 0;
out:
	वापस len;
पूर्ण

/*
 * Timer function to बंद old temporary transports, using
 * a mark-and-sweep algorithm.
 */
अटल व्योम svc_age_temp_xprts(काष्ठा समयr_list *t)
अणु
	काष्ठा svc_serv *serv = from_समयr(serv, t, sv_tempसमयr);
	काष्ठा svc_xprt *xprt;
	काष्ठा list_head *le, *next;

	dprपूर्णांकk("svc_age_temp_xprts\n");

	अगर (!spin_trylock_bh(&serv->sv_lock)) अणु
		/* busy, try again 1 sec later */
		dprपूर्णांकk("svc_age_temp_xprts: busy\n");
		mod_समयr(&serv->sv_tempसमयr, jअगरfies + HZ);
		वापस;
	पूर्ण

	list_क्रम_each_safe(le, next, &serv->sv_tempsocks) अणु
		xprt = list_entry(le, काष्ठा svc_xprt, xpt_list);

		/* First समय through, just mark it OLD. Second समय
		 * through, बंद it. */
		अगर (!test_and_set_bit(XPT_OLD, &xprt->xpt_flags))
			जारी;
		अगर (kref_पढ़ो(&xprt->xpt_ref) > 1 ||
		    test_bit(XPT_BUSY, &xprt->xpt_flags))
			जारी;
		list_del_init(le);
		set_bit(XPT_CLOSE, &xprt->xpt_flags);
		dprपूर्णांकk("queuing xprt %p for closing\n", xprt);

		/* a thपढ़ो will dequeue and बंद it soon */
		svc_xprt_enqueue(xprt);
	पूर्ण
	spin_unlock_bh(&serv->sv_lock);

	mod_समयr(&serv->sv_tempसमयr, jअगरfies + svc_conn_age_period * HZ);
पूर्ण

/* Close temporary transports whose xpt_local matches server_addr immediately
 * instead of रुकोing क्रम them to be picked up by the समयr.
 *
 * This is meant to be called from a notअगरier_block that runs when an ip
 * address is deleted.
 */
व्योम svc_age_temp_xprts_now(काष्ठा svc_serv *serv, काष्ठा sockaddr *server_addr)
अणु
	काष्ठा svc_xprt *xprt;
	काष्ठा list_head *le, *next;
	LIST_HEAD(to_be_बंदd);

	spin_lock_bh(&serv->sv_lock);
	list_क्रम_each_safe(le, next, &serv->sv_tempsocks) अणु
		xprt = list_entry(le, काष्ठा svc_xprt, xpt_list);
		अगर (rpc_cmp_addr(server_addr, (काष्ठा sockaddr *)
				&xprt->xpt_local)) अणु
			dprपूर्णांकk("svc_age_temp_xprts_now: found %p\n", xprt);
			list_move(le, &to_be_बंदd);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&serv->sv_lock);

	जबतक (!list_empty(&to_be_बंदd)) अणु
		le = to_be_बंदd.next;
		list_del_init(le);
		xprt = list_entry(le, काष्ठा svc_xprt, xpt_list);
		set_bit(XPT_CLOSE, &xprt->xpt_flags);
		set_bit(XPT_KILL_TEMP, &xprt->xpt_flags);
		dprपूर्णांकk("svc_age_temp_xprts_now: queuing xprt %p for closing\n",
				xprt);
		svc_xprt_enqueue(xprt);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(svc_age_temp_xprts_now);

अटल व्योम call_xpt_users(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_xpt_user *u;

	spin_lock(&xprt->xpt_lock);
	जबतक (!list_empty(&xprt->xpt_users)) अणु
		u = list_first_entry(&xprt->xpt_users, काष्ठा svc_xpt_user, list);
		list_del_init(&u->list);
		u->callback(u);
	पूर्ण
	spin_unlock(&xprt->xpt_lock);
पूर्ण

/*
 * Remove a dead transport
 */
अटल व्योम svc_delete_xprt(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_serv	*serv = xprt->xpt_server;
	काष्ठा svc_deferred_req *dr;

	अगर (test_and_set_bit(XPT_DEAD, &xprt->xpt_flags))
		वापस;

	trace_svc_xprt_detach(xprt);
	xprt->xpt_ops->xpo_detach(xprt);
	अगर (xprt->xpt_bc_xprt)
		xprt->xpt_bc_xprt->ops->बंद(xprt->xpt_bc_xprt);

	spin_lock_bh(&serv->sv_lock);
	list_del_init(&xprt->xpt_list);
	WARN_ON_ONCE(!list_empty(&xprt->xpt_पढ़ोy));
	अगर (test_bit(XPT_TEMP, &xprt->xpt_flags))
		serv->sv_पंचांगpcnt--;
	spin_unlock_bh(&serv->sv_lock);

	जबतक ((dr = svc_deferred_dequeue(xprt)) != शून्य)
		kमुक्त(dr);

	call_xpt_users(xprt);
	svc_xprt_put(xprt);
पूर्ण

व्योम svc_बंद_xprt(काष्ठा svc_xprt *xprt)
अणु
	trace_svc_xprt_बंद(xprt);
	set_bit(XPT_CLOSE, &xprt->xpt_flags);
	अगर (test_and_set_bit(XPT_BUSY, &xprt->xpt_flags))
		/* someone अन्यथा will have to effect the बंद */
		वापस;
	/*
	 * We expect svc_बंद_xprt() to work even when no thपढ़ोs are
	 * running (e.g., जबतक configuring the server beक्रमe starting
	 * any thपढ़ोs), so अगर the transport isn't busy, we delete
	 * it ourself:
	 */
	svc_delete_xprt(xprt);
पूर्ण
EXPORT_SYMBOL_GPL(svc_बंद_xprt);

अटल पूर्णांक svc_बंद_list(काष्ठा svc_serv *serv, काष्ठा list_head *xprt_list, काष्ठा net *net)
अणु
	काष्ठा svc_xprt *xprt;
	पूर्णांक ret = 0;

	spin_lock_bh(&serv->sv_lock);
	list_क्रम_each_entry(xprt, xprt_list, xpt_list) अणु
		अगर (xprt->xpt_net != net)
			जारी;
		ret++;
		set_bit(XPT_CLOSE, &xprt->xpt_flags);
		svc_xprt_enqueue(xprt);
	पूर्ण
	spin_unlock_bh(&serv->sv_lock);
	वापस ret;
पूर्ण

अटल काष्ठा svc_xprt *svc_dequeue_net(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	काष्ठा svc_pool *pool;
	काष्ठा svc_xprt *xprt;
	काष्ठा svc_xprt *पंचांगp;
	पूर्णांक i;

	क्रम (i = 0; i < serv->sv_nrpools; i++) अणु
		pool = &serv->sv_pools[i];

		spin_lock_bh(&pool->sp_lock);
		list_क्रम_each_entry_safe(xprt, पंचांगp, &pool->sp_sockets, xpt_पढ़ोy) अणु
			अगर (xprt->xpt_net != net)
				जारी;
			list_del_init(&xprt->xpt_पढ़ोy);
			spin_unlock_bh(&pool->sp_lock);
			वापस xprt;
		पूर्ण
		spin_unlock_bh(&pool->sp_lock);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम svc_clean_up_xprts(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	काष्ठा svc_xprt *xprt;

	जबतक ((xprt = svc_dequeue_net(serv, net))) अणु
		set_bit(XPT_CLOSE, &xprt->xpt_flags);
		svc_delete_xprt(xprt);
	पूर्ण
पूर्ण

/*
 * Server thपढ़ोs may still be running (especially in the हाल where the
 * service is still running in other network namespaces).
 *
 * So we shut करोwn sockets the same way we would on a running server, by
 * setting XPT_CLOSE, enqueuing, and letting a thपढ़ो pick it up to करो
 * the बंद.  In the हाल there are no such other thपढ़ोs,
 * thपढ़ोs running, svc_clean_up_xprts() करोes a simple version of a
 * server's मुख्य event loop, and in the हाल where there are other
 * thपढ़ोs, we may need to रुको a little जबतक and then check again to
 * see अगर they're करोne.
 */
व्योम svc_बंद_net(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	पूर्णांक delay = 0;

	जबतक (svc_बंद_list(serv, &serv->sv_permsocks, net) +
	       svc_बंद_list(serv, &serv->sv_tempsocks, net)) अणु

		svc_clean_up_xprts(serv, net);
		msleep(delay++);
	पूर्ण
पूर्ण

/*
 * Handle defer and revisit of requests
 */

अटल व्योम svc_revisit(काष्ठा cache_deferred_req *dreq, पूर्णांक too_many)
अणु
	काष्ठा svc_deferred_req *dr =
		container_of(dreq, काष्ठा svc_deferred_req, handle);
	काष्ठा svc_xprt *xprt = dr->xprt;

	spin_lock(&xprt->xpt_lock);
	set_bit(XPT_DEFERRED, &xprt->xpt_flags);
	अगर (too_many || test_bit(XPT_DEAD, &xprt->xpt_flags)) अणु
		spin_unlock(&xprt->xpt_lock);
		trace_svc_defer_drop(dr);
		svc_xprt_put(xprt);
		kमुक्त(dr);
		वापस;
	पूर्ण
	dr->xprt = शून्य;
	list_add(&dr->handle.recent, &xprt->xpt_deferred);
	spin_unlock(&xprt->xpt_lock);
	trace_svc_defer_queue(dr);
	svc_xprt_enqueue(xprt);
	svc_xprt_put(xprt);
पूर्ण

/*
 * Save the request off क्रम later processing. The request buffer looks
 * like this:
 *
 * <xprt-header><rpc-header><rpc-pagelist><rpc-tail>
 *
 * This code can only handle requests that consist of an xprt-header
 * and rpc-header.
 */
अटल काष्ठा cache_deferred_req *svc_defer(काष्ठा cache_req *req)
अणु
	काष्ठा svc_rqst *rqstp = container_of(req, काष्ठा svc_rqst, rq_chandle);
	काष्ठा svc_deferred_req *dr;

	अगर (rqstp->rq_arg.page_len || !test_bit(RQ_USEDEFERRAL, &rqstp->rq_flags))
		वापस शून्य; /* अगर more than a page, give up FIXME */
	अगर (rqstp->rq_deferred) अणु
		dr = rqstp->rq_deferred;
		rqstp->rq_deferred = शून्य;
	पूर्ण अन्यथा अणु
		माप_प्रकार skip;
		माप_प्रकार size;
		/* FIXME maybe discard अगर size too large */
		size = माप(काष्ठा svc_deferred_req) + rqstp->rq_arg.len;
		dr = kदो_स्मृति(size, GFP_KERNEL);
		अगर (dr == शून्य)
			वापस शून्य;

		dr->handle.owner = rqstp->rq_server;
		dr->prot = rqstp->rq_prot;
		स_नकल(&dr->addr, &rqstp->rq_addr, rqstp->rq_addrlen);
		dr->addrlen = rqstp->rq_addrlen;
		dr->daddr = rqstp->rq_daddr;
		dr->argslen = rqstp->rq_arg.len >> 2;
		dr->xprt_hlen = rqstp->rq_xprt_hlen;

		/* back up head to the start of the buffer and copy */
		skip = rqstp->rq_arg.len - rqstp->rq_arg.head[0].iov_len;
		स_नकल(dr->args, rqstp->rq_arg.head[0].iov_base - skip,
		       dr->argslen << 2);
	पूर्ण
	trace_svc_defer(rqstp);
	svc_xprt_get(rqstp->rq_xprt);
	dr->xprt = rqstp->rq_xprt;
	set_bit(RQ_DROPME, &rqstp->rq_flags);

	dr->handle.revisit = svc_revisit;
	वापस &dr->handle;
पूर्ण

/*
 * recv data from a deferred request पूर्णांकo an active one
 */
अटल noअंतरभूत पूर्णांक svc_deferred_recv(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_deferred_req *dr = rqstp->rq_deferred;

	trace_svc_defer_recv(dr);

	/* setup iov_base past transport header */
	rqstp->rq_arg.head[0].iov_base = dr->args + (dr->xprt_hlen>>2);
	/* The iov_len करोes not include the transport header bytes */
	rqstp->rq_arg.head[0].iov_len = (dr->argslen<<2) - dr->xprt_hlen;
	rqstp->rq_arg.page_len = 0;
	/* The rq_arg.len includes the transport header bytes */
	rqstp->rq_arg.len     = dr->argslen<<2;
	rqstp->rq_prot        = dr->prot;
	स_नकल(&rqstp->rq_addr, &dr->addr, dr->addrlen);
	rqstp->rq_addrlen     = dr->addrlen;
	/* Save off transport header len in हाल we get deferred again */
	rqstp->rq_xprt_hlen   = dr->xprt_hlen;
	rqstp->rq_daddr       = dr->daddr;
	rqstp->rq_respages    = rqstp->rq_pages;
	svc_xprt_received(rqstp->rq_xprt);
	वापस (dr->argslen<<2) - dr->xprt_hlen;
पूर्ण


अटल काष्ठा svc_deferred_req *svc_deferred_dequeue(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svc_deferred_req *dr = शून्य;

	अगर (!test_bit(XPT_DEFERRED, &xprt->xpt_flags))
		वापस शून्य;
	spin_lock(&xprt->xpt_lock);
	अगर (!list_empty(&xprt->xpt_deferred)) अणु
		dr = list_entry(xprt->xpt_deferred.next,
				काष्ठा svc_deferred_req,
				handle.recent);
		list_del_init(&dr->handle.recent);
	पूर्ण अन्यथा
		clear_bit(XPT_DEFERRED, &xprt->xpt_flags);
	spin_unlock(&xprt->xpt_lock);
	वापस dr;
पूर्ण

/**
 * svc_find_xprt - find an RPC transport instance
 * @serv: poपूर्णांकer to svc_serv to search
 * @xcl_name: C string containing transport's class name
 * @net: owner net poपूर्णांकer
 * @af: Address family of transport's local address
 * @port: transport's IP port number
 *
 * Return the transport instance poपूर्णांकer क्रम the endpoपूर्णांक accepting
 * connections/peer traffic from the specअगरied transport class,
 * address family and port.
 *
 * Specअगरying 0 क्रम the address family or port is effectively a
 * wild-card, and will result in matching the first transport in the
 * service's list that has a matching class name.
 */
काष्ठा svc_xprt *svc_find_xprt(काष्ठा svc_serv *serv, स्थिर अक्षर *xcl_name,
			       काष्ठा net *net, स्थिर sa_family_t af,
			       स्थिर अचिन्हित लघु port)
अणु
	काष्ठा svc_xprt *xprt;
	काष्ठा svc_xprt *found = शून्य;

	/* Sanity check the args */
	अगर (serv == शून्य || xcl_name == शून्य)
		वापस found;

	spin_lock_bh(&serv->sv_lock);
	list_क्रम_each_entry(xprt, &serv->sv_permsocks, xpt_list) अणु
		अगर (xprt->xpt_net != net)
			जारी;
		अगर (म_भेद(xprt->xpt_class->xcl_name, xcl_name))
			जारी;
		अगर (af != AF_UNSPEC && af != xprt->xpt_local.ss_family)
			जारी;
		अगर (port != 0 && port != svc_xprt_local_port(xprt))
			जारी;
		found = xprt;
		svc_xprt_get(xprt);
		अवरोध;
	पूर्ण
	spin_unlock_bh(&serv->sv_lock);
	वापस found;
पूर्ण
EXPORT_SYMBOL_GPL(svc_find_xprt);

अटल पूर्णांक svc_one_xprt_name(स्थिर काष्ठा svc_xprt *xprt,
			     अक्षर *pos, पूर्णांक reमुख्यing)
अणु
	पूर्णांक len;

	len = snम_लिखो(pos, reमुख्यing, "%s %u\n",
			xprt->xpt_class->xcl_name,
			svc_xprt_local_port(xprt));
	अगर (len >= reमुख्यing)
		वापस -ENAMETOOLONG;
	वापस len;
पूर्ण

/**
 * svc_xprt_names - क्रमmat a buffer with a list of transport names
 * @serv: poपूर्णांकer to an RPC service
 * @buf: poपूर्णांकer to a buffer to be filled in
 * @buflen: length of buffer to be filled in
 *
 * Fills in @buf with a string containing a list of transport names,
 * each name terminated with '\n'.
 *
 * Returns positive length of the filled-in string on success; otherwise
 * a negative त्रुटि_सं value is वापसed अगर an error occurs.
 */
पूर्णांक svc_xprt_names(काष्ठा svc_serv *serv, अक्षर *buf, स्थिर पूर्णांक buflen)
अणु
	काष्ठा svc_xprt *xprt;
	पूर्णांक len, totlen;
	अक्षर *pos;

	/* Sanity check args */
	अगर (!serv)
		वापस 0;

	spin_lock_bh(&serv->sv_lock);

	pos = buf;
	totlen = 0;
	list_क्रम_each_entry(xprt, &serv->sv_permsocks, xpt_list) अणु
		len = svc_one_xprt_name(xprt, pos, buflen - totlen);
		अगर (len < 0) अणु
			*buf = '\0';
			totlen = len;
		पूर्ण
		अगर (len <= 0)
			अवरोध;

		pos += len;
		totlen += len;
	पूर्ण

	spin_unlock_bh(&serv->sv_lock);
	वापस totlen;
पूर्ण
EXPORT_SYMBOL_GPL(svc_xprt_names);


/*----------------------------------------------------------------------------*/

अटल व्योम *svc_pool_stats_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	अचिन्हित पूर्णांक pidx = (अचिन्हित पूर्णांक)*pos;
	काष्ठा svc_serv *serv = m->निजी;

	dprपूर्णांकk("svc_pool_stats_start, *pidx=%u\n", pidx);

	अगर (!pidx)
		वापस SEQ_START_TOKEN;
	वापस (pidx > serv->sv_nrpools ? शून्य : &serv->sv_pools[pidx-1]);
पूर्ण

अटल व्योम *svc_pool_stats_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	काष्ठा svc_pool *pool = p;
	काष्ठा svc_serv *serv = m->निजी;

	dprपूर्णांकk("svc_pool_stats_next, *pos=%llu\n", *pos);

	अगर (p == SEQ_START_TOKEN) अणु
		pool = &serv->sv_pools[0];
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक pidx = (pool - &serv->sv_pools[0]);
		अगर (pidx < serv->sv_nrpools-1)
			pool = &serv->sv_pools[pidx+1];
		अन्यथा
			pool = शून्य;
	पूर्ण
	++*pos;
	वापस pool;
पूर्ण

अटल व्योम svc_pool_stats_stop(काष्ठा seq_file *m, व्योम *p)
अणु
पूर्ण

अटल पूर्णांक svc_pool_stats_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा svc_pool *pool = p;

	अगर (p == SEQ_START_TOKEN) अणु
		seq_माला_दो(m, "# pool packets-arrived sockets-enqueued threads-woken threads-timedout\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(m, "%u %lu %lu %lu %lu\n",
		pool->sp_id,
		(अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&pool->sp_stats.packets),
		pool->sp_stats.sockets_queued,
		(अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&pool->sp_stats.thपढ़ोs_woken),
		(अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&pool->sp_stats.thपढ़ोs_समयकरोut));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations svc_pool_stats_seq_ops = अणु
	.start	= svc_pool_stats_start,
	.next	= svc_pool_stats_next,
	.stop	= svc_pool_stats_stop,
	.show	= svc_pool_stats_show,
पूर्ण;

पूर्णांक svc_pool_stats_खोलो(काष्ठा svc_serv *serv, काष्ठा file *file)
अणु
	पूर्णांक err;

	err = seq_खोलो(file, &svc_pool_stats_seq_ops);
	अगर (!err)
		((काष्ठा seq_file *) file->निजी_data)->निजी = serv;
	वापस err;
पूर्ण
EXPORT_SYMBOL(svc_pool_stats_खोलो);

/*----------------------------------------------------------------------------*/
