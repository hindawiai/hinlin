<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/lockd/mon.c
 *
 * The kernel statd client.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>

#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/xprtsock.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/lockd/lockd.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "netns.h"

#घोषणा NLMDBG_FACILITY		NLMDBG_MONITOR
#घोषणा NSM_PROGRAM		100024
#घोषणा NSM_VERSION		1

क्रमागत अणु
	NSMPROC_शून्य,
	NSMPROC_STAT,
	NSMPROC_MON,
	NSMPROC_UNMON,
	NSMPROC_UNMON_ALL,
	NSMPROC_SIMU_CRASH,
	NSMPROC_NOTIFY,
पूर्ण;

काष्ठा nsm_args अणु
	काष्ठा nsm_निजी	*priv;
	u32			prog;		/* RPC callback info */
	u32			vers;
	u32			proc;

	अक्षर			*mon_name;
	स्थिर अक्षर		*nodename;
पूर्ण;

काष्ठा nsm_res अणु
	u32			status;
	u32			state;
पूर्ण;

अटल स्थिर काष्ठा rpc_program	nsm_program;
अटल				DEFINE_SPINLOCK(nsm_lock);

/*
 * Local NSM state
 */
u32	__पढ़ो_mostly		nsm_local_state;
bool	__पढ़ो_mostly		nsm_use_hostnames;

अटल अंतरभूत काष्ठा sockaddr *nsm_addr(स्थिर काष्ठा nsm_handle *nsm)
अणु
	वापस (काष्ठा sockaddr *)&nsm->sm_addr;
पूर्ण

अटल काष्ठा rpc_clnt *nsm_create(काष्ठा net *net, स्थिर अक्षर *nodename)
अणु
	काष्ठा sockaddr_in sin = अणु
		.sin_family		= AF_INET,
		.sin_addr.s_addr	= htonl(INADDR_LOOPBACK),
	पूर्ण;
	काष्ठा rpc_create_args args = अणु
		.net			= net,
		.protocol		= XPRT_TRANSPORT_TCP,
		.address		= (काष्ठा sockaddr *)&sin,
		.addrsize		= माप(sin),
		.servername		= "rpc.statd",
		.nodename		= nodename,
		.program		= &nsm_program,
		.version		= NSM_VERSION,
		.authflavor		= RPC_AUTH_शून्य,
		.flags			= RPC_CLNT_CREATE_NOPING,
		.cred			= current_cred(),
	पूर्ण;

	वापस rpc_create(&args);
पूर्ण

अटल पूर्णांक nsm_mon_unmon(काष्ठा nsm_handle *nsm, u32 proc, काष्ठा nsm_res *res,
			 स्थिर काष्ठा nlm_host *host)
अणु
	पूर्णांक		status;
	काष्ठा rpc_clnt *clnt;
	काष्ठा nsm_args args = अणु
		.priv		= &nsm->sm_priv,
		.prog		= NLM_PROGRAM,
		.vers		= 3,
		.proc		= NLMPROC_NSM_NOTIFY,
		.mon_name	= nsm->sm_mon_name,
		.nodename	= host->nodename,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_argp	= &args,
		.rpc_resp	= res,
	पूर्ण;

	स_रखो(res, 0, माप(*res));

	clnt = nsm_create(host->net, host->nodename);
	अगर (IS_ERR(clnt)) अणु
		dprपूर्णांकk("lockd: failed to create NSM upcall transport, "
			"status=%ld, net=%x\n", PTR_ERR(clnt),
			host->net->ns.inum);
		वापस PTR_ERR(clnt);
	पूर्ण

	msg.rpc_proc = &clnt->cl_procinfo[proc];
	status = rpc_call_sync(clnt, &msg, RPC_TASK_SOFTCONN);
	अगर (status == -ECONNREFUSED) अणु
		dprपूर्णांकk("lockd:	NSM upcall RPC failed, status=%d, forcing rebind\n",
				status);
		rpc_क्रमce_rebind(clnt);
		status = rpc_call_sync(clnt, &msg, RPC_TASK_SOFTCONN);
	पूर्ण
	अगर (status < 0)
		dprपूर्णांकk("lockd: NSM upcall RPC failed, status=%d\n",
				status);
	अन्यथा
		status = 0;

	rpc_shutकरोwn_client(clnt);
	वापस status;
पूर्ण

/**
 * nsm_monitor - Notअगरy a peer in हाल we reboot
 * @host: poपूर्णांकer to nlm_host of peer to notअगरy
 *
 * If this peer is not alपढ़ोy monitored, this function sends an
 * upcall to the local rpc.statd to record the name/address of
 * the peer to notअगरy in हाल we reboot.
 *
 * Returns zero अगर the peer is monitored by the local rpc.statd;
 * otherwise a negative त्रुटि_सं value is वापसed.
 */
पूर्णांक nsm_monitor(स्थिर काष्ठा nlm_host *host)
अणु
	काष्ठा nsm_handle *nsm = host->h_nsmhandle;
	काष्ठा nsm_res	res;
	पूर्णांक		status;

	dprपूर्णांकk("lockd: nsm_monitor(%s)\n", nsm->sm_name);

	अगर (nsm->sm_monitored)
		वापस 0;

	/*
	 * Choose whether to record the caller_name or IP address of
	 * this peer in the local rpc.statd's database.
	 */
	nsm->sm_mon_name = nsm_use_hostnames ? nsm->sm_name : nsm->sm_addrbuf;

	status = nsm_mon_unmon(nsm, NSMPROC_MON, &res, host);
	अगर (unlikely(res.status != 0))
		status = -EIO;
	अगर (unlikely(status < 0)) अणु
		pr_notice_ratelimited("lockd: cannot monitor %s\n", nsm->sm_name);
		वापस status;
	पूर्ण

	nsm->sm_monitored = 1;
	अगर (unlikely(nsm_local_state != res.state)) अणु
		nsm_local_state = res.state;
		dprपूर्णांकk("lockd: NSM state changed to %d\n", nsm_local_state);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * nsm_unmonitor - Unरेजिस्टर peer notअगरication
 * @host: poपूर्णांकer to nlm_host of peer to stop monitoring
 *
 * If this peer is monitored, this function sends an upcall to
 * tell the local rpc.statd not to send this peer a notअगरication
 * when we reboot.
 */
व्योम nsm_unmonitor(स्थिर काष्ठा nlm_host *host)
अणु
	काष्ठा nsm_handle *nsm = host->h_nsmhandle;
	काष्ठा nsm_res	res;
	पूर्णांक status;

	अगर (refcount_पढ़ो(&nsm->sm_count) == 1
	 && nsm->sm_monitored && !nsm->sm_sticky) अणु
		dprपूर्णांकk("lockd: nsm_unmonitor(%s)\n", nsm->sm_name);

		status = nsm_mon_unmon(nsm, NSMPROC_UNMON, &res, host);
		अगर (res.status != 0)
			status = -EIO;
		अगर (status < 0)
			prपूर्णांकk(KERN_NOTICE "lockd: cannot unmonitor %s\n",
					nsm->sm_name);
		अन्यथा
			nsm->sm_monitored = 0;
	पूर्ण
पूर्ण

अटल काष्ठा nsm_handle *nsm_lookup_hostname(स्थिर काष्ठा list_head *nsm_handles,
					स्थिर अक्षर *hostname, स्थिर माप_प्रकार len)
अणु
	काष्ठा nsm_handle *nsm;

	list_क्रम_each_entry(nsm, nsm_handles, sm_link)
		अगर (म_माप(nsm->sm_name) == len &&
		    स_भेद(nsm->sm_name, hostname, len) == 0)
			वापस nsm;
	वापस शून्य;
पूर्ण

अटल काष्ठा nsm_handle *nsm_lookup_addr(स्थिर काष्ठा list_head *nsm_handles,
					स्थिर काष्ठा sockaddr *sap)
अणु
	काष्ठा nsm_handle *nsm;

	list_क्रम_each_entry(nsm, nsm_handles, sm_link)
		अगर (rpc_cmp_addr(nsm_addr(nsm), sap))
			वापस nsm;
	वापस शून्य;
पूर्ण

अटल काष्ठा nsm_handle *nsm_lookup_priv(स्थिर काष्ठा list_head *nsm_handles,
					स्थिर काष्ठा nsm_निजी *priv)
अणु
	काष्ठा nsm_handle *nsm;

	list_क्रम_each_entry(nsm, nsm_handles, sm_link)
		अगर (स_भेद(nsm->sm_priv.data, priv->data,
					माप(priv->data)) == 0)
			वापस nsm;
	वापस शून्य;
पूर्ण

/*
 * Conकाष्ठा a unique cookie to match this nsm_handle to this monitored
 * host.  It is passed to the local rpc.statd via NSMPROC_MON, and
 * वापसed via NLMPROC_SM_NOTIFY, in the "priv" field of these
 * requests.
 *
 * The NSM protocol requires that these cookies be unique जबतक the
 * प्रणाली is running.  We prefer a stronger requirement of making them
 * unique across reboots.  If user space bugs cause a stale cookie to
 * be sent to the kernel, it could cause the wrong host to lose its
 * lock state अगर cookies were not unique across reboots.
 *
 * The cookies are exposed only to local user space via loopback.  They
 * करो not appear on the physical network.  If we want greater security
 * क्रम some reason, nsm_init_निजी() could perक्रमm a one-way hash to
 * obscure the contents of the cookie.
 */
अटल व्योम nsm_init_निजी(काष्ठा nsm_handle *nsm)
अणु
	u64 *p = (u64 *)&nsm->sm_priv.data;
	s64 ns;

	ns = kसमय_get_ns();
	put_unaligned(ns, p);
	put_unaligned((अचिन्हित दीर्घ)nsm, p + 1);
पूर्ण

अटल काष्ठा nsm_handle *nsm_create_handle(स्थिर काष्ठा sockaddr *sap,
					    स्थिर माप_प्रकार salen,
					    स्थिर अक्षर *hostname,
					    स्थिर माप_प्रकार hostname_len)
अणु
	काष्ठा nsm_handle *new;

	new = kzalloc(माप(*new) + hostname_len + 1, GFP_KERNEL);
	अगर (unlikely(new == शून्य))
		वापस शून्य;

	refcount_set(&new->sm_count, 1);
	new->sm_name = (अक्षर *)(new + 1);
	स_नकल(nsm_addr(new), sap, salen);
	new->sm_addrlen = salen;
	nsm_init_निजी(new);

	अगर (rpc_ntop(nsm_addr(new), new->sm_addrbuf,
					माप(new->sm_addrbuf)) == 0)
		(व्योम)snम_लिखो(new->sm_addrbuf, माप(new->sm_addrbuf),
				"unsupported address family");
	स_नकल(new->sm_name, hostname, hostname_len);
	new->sm_name[hostname_len] = '\0';

	वापस new;
पूर्ण

/**
 * nsm_get_handle - Find or create a cached nsm_handle
 * @net: network namespace
 * @sap: poपूर्णांकer to socket address of handle to find
 * @salen: length of socket address
 * @hostname: poपूर्णांकer to C string containing hostname to find
 * @hostname_len: length of C string
 *
 * Behavior is modulated by the global nsm_use_hostnames variable.
 *
 * Returns a cached nsm_handle after bumping its ref count, or
 * वापसs a fresh nsm_handle अगर a handle that matches @sap and/or
 * @hostname cannot be found in the handle cache.  Returns शून्य अगर
 * an error occurs.
 */
काष्ठा nsm_handle *nsm_get_handle(स्थिर काष्ठा net *net,
				  स्थिर काष्ठा sockaddr *sap,
				  स्थिर माप_प्रकार salen, स्थिर अक्षर *hostname,
				  स्थिर माप_प्रकार hostname_len)
अणु
	काष्ठा nsm_handle *cached, *new = शून्य;
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

	अगर (hostname && स_प्रथम(hostname, '/', hostname_len) != शून्य) अणु
		अगर (prपूर्णांकk_ratelimit()) अणु
			prपूर्णांकk(KERN_WARNING "Invalid hostname \"%.*s\" "
					    "in NFS lock request\n",
				(पूर्णांक)hostname_len, hostname);
		पूर्ण
		वापस शून्य;
	पूर्ण

retry:
	spin_lock(&nsm_lock);

	अगर (nsm_use_hostnames && hostname != शून्य)
		cached = nsm_lookup_hostname(&ln->nsm_handles,
					hostname, hostname_len);
	अन्यथा
		cached = nsm_lookup_addr(&ln->nsm_handles, sap);

	अगर (cached != शून्य) अणु
		refcount_inc(&cached->sm_count);
		spin_unlock(&nsm_lock);
		kमुक्त(new);
		dprपूर्णांकk("lockd: found nsm_handle for %s (%s), "
				"cnt %d\n", cached->sm_name,
				cached->sm_addrbuf,
				refcount_पढ़ो(&cached->sm_count));
		वापस cached;
	पूर्ण

	अगर (new != शून्य) अणु
		list_add(&new->sm_link, &ln->nsm_handles);
		spin_unlock(&nsm_lock);
		dprपूर्णांकk("lockd: created nsm_handle for %s (%s)\n",
				new->sm_name, new->sm_addrbuf);
		वापस new;
	पूर्ण

	spin_unlock(&nsm_lock);

	new = nsm_create_handle(sap, salen, hostname, hostname_len);
	अगर (unlikely(new == शून्य))
		वापस शून्य;
	जाओ retry;
पूर्ण

/**
 * nsm_reboot_lookup - match NLMPROC_SM_NOTIFY arguments to an nsm_handle
 * @net:  network namespace
 * @info: poपूर्णांकer to NLMPROC_SM_NOTIFY arguments
 *
 * Returns a matching nsm_handle अगर found in the nsm cache. The वापसed
 * nsm_handle's reference count is bumped. Otherwise वापसs शून्य अगर some
 * error occurred.
 */
काष्ठा nsm_handle *nsm_reboot_lookup(स्थिर काष्ठा net *net,
				स्थिर काष्ठा nlm_reboot *info)
अणु
	काष्ठा nsm_handle *cached;
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

	spin_lock(&nsm_lock);

	cached = nsm_lookup_priv(&ln->nsm_handles, &info->priv);
	अगर (unlikely(cached == शून्य)) अणु
		spin_unlock(&nsm_lock);
		dprपूर्णांकk("lockd: never saw rebooted peer '%.*s' before\n",
				info->len, info->mon);
		वापस cached;
	पूर्ण

	refcount_inc(&cached->sm_count);
	spin_unlock(&nsm_lock);

	dprपूर्णांकk("lockd: host %s (%s) rebooted, cnt %d\n",
			cached->sm_name, cached->sm_addrbuf,
			refcount_पढ़ो(&cached->sm_count));
	वापस cached;
पूर्ण

/**
 * nsm_release - Release an NSM handle
 * @nsm: poपूर्णांकer to handle to be released
 *
 */
व्योम nsm_release(काष्ठा nsm_handle *nsm)
अणु
	अगर (refcount_dec_and_lock(&nsm->sm_count, &nsm_lock)) अणु
		list_del(&nsm->sm_link);
		spin_unlock(&nsm_lock);
		dprपूर्णांकk("lockd: destroyed nsm_handle for %s (%s)\n",
				nsm->sm_name, nsm->sm_addrbuf);
		kमुक्त(nsm);
	पूर्ण
पूर्ण

/*
 * XDR functions क्रम NSM.
 *
 * See https://www.खोलोgroup.org/ क्रम details on the Network
 * Status Monitor wire protocol.
 */

अटल व्योम encode_nsm_string(काष्ठा xdr_stream *xdr, स्थिर अक्षर *string)
अणु
	स्थिर u32 len = म_माप(string);
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 + len);
	xdr_encode_opaque(p, string, len);
पूर्ण

/*
 * "mon_name" specअगरies the host to be monitored.
 */
अटल व्योम encode_mon_name(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nsm_args *argp)
अणु
	encode_nsm_string(xdr, argp->mon_name);
पूर्ण

/*
 * The "my_id" argument specअगरies the hostname and RPC procedure
 * to be called when the status manager receives notअगरication
 * (via the NLMPROC_SM_NOTIFY call) that the state of host "mon_name"
 * has changed.
 */
अटल व्योम encode_my_id(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nsm_args *argp)
अणु
	__be32 *p;

	encode_nsm_string(xdr, argp->nodename);
	p = xdr_reserve_space(xdr, 4 + 4 + 4);
	*p++ = cpu_to_be32(argp->prog);
	*p++ = cpu_to_be32(argp->vers);
	*p = cpu_to_be32(argp->proc);
पूर्ण

/*
 * The "mon_id" argument specअगरies the non-निजी arguments
 * of an NSMPROC_MON or NSMPROC_UNMON call.
 */
अटल व्योम encode_mon_id(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nsm_args *argp)
अणु
	encode_mon_name(xdr, argp);
	encode_my_id(xdr, argp);
पूर्ण

/*
 * The "priv" argument may contain निजी inक्रमmation required
 * by the NSMPROC_MON call. This inक्रमmation will be supplied in the
 * NLMPROC_SM_NOTIFY call.
 */
अटल व्योम encode_priv(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nsm_args *argp)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, SM_PRIV_SIZE);
	xdr_encode_opaque_fixed(p, argp->priv->data, SM_PRIV_SIZE);
पूर्ण

अटल व्योम nsm_xdr_enc_mon(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			    स्थिर व्योम *argp)
अणु
	encode_mon_id(xdr, argp);
	encode_priv(xdr, argp);
पूर्ण

अटल व्योम nsm_xdr_enc_unmon(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
			      स्थिर व्योम *argp)
अणु
	encode_mon_id(xdr, argp);
पूर्ण

अटल पूर्णांक nsm_xdr_dec_stat_res(काष्ठा rpc_rqst *rqstp,
				काष्ठा xdr_stream *xdr,
				व्योम *data)
अणु
	काष्ठा nsm_res *resp = data;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4 + 4);
	अगर (unlikely(p == शून्य))
		वापस -EIO;
	resp->status = be32_to_cpup(p++);
	resp->state = be32_to_cpup(p);

	dprपूर्णांकk("lockd: %s status %d state %d\n",
		__func__, resp->status, resp->state);
	वापस 0;
पूर्ण

अटल पूर्णांक nsm_xdr_dec_stat(काष्ठा rpc_rqst *rqstp,
			    काष्ठा xdr_stream *xdr,
			    व्योम *data)
अणु
	काष्ठा nsm_res *resp = data;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस -EIO;
	resp->state = be32_to_cpup(p);

	dprपूर्णांकk("lockd: %s state %d\n", __func__, resp->state);
	वापस 0;
पूर्ण

#घोषणा SM_my_name_sz	(1+XDR_QUADLEN(SM_MAXSTRLEN))
#घोषणा SM_my_id_sz	(SM_my_name_sz+3)
#घोषणा SM_mon_name_sz	(1+XDR_QUADLEN(SM_MAXSTRLEN))
#घोषणा SM_mon_id_sz	(SM_mon_name_sz+SM_my_id_sz)
#घोषणा SM_priv_sz	(XDR_QUADLEN(SM_PRIV_SIZE))
#घोषणा SM_mon_sz	(SM_mon_id_sz+SM_priv_sz)
#घोषणा SM_monres_sz	2
#घोषणा SM_unmonres_sz	1

अटल स्थिर काष्ठा rpc_procinfo nsm_procedures[] = अणु
[NSMPROC_MON] = अणु
		.p_proc		= NSMPROC_MON,
		.p_encode	= nsm_xdr_enc_mon,
		.p_decode	= nsm_xdr_dec_stat_res,
		.p_arglen	= SM_mon_sz,
		.p_replen	= SM_monres_sz,
		.p_statidx	= NSMPROC_MON,
		.p_name		= "MONITOR",
	पूर्ण,
[NSMPROC_UNMON] = अणु
		.p_proc		= NSMPROC_UNMON,
		.p_encode	= nsm_xdr_enc_unmon,
		.p_decode	= nsm_xdr_dec_stat,
		.p_arglen	= SM_mon_id_sz,
		.p_replen	= SM_unmonres_sz,
		.p_statidx	= NSMPROC_UNMON,
		.p_name		= "UNMONITOR",
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक nsm_version1_counts[ARRAY_SIZE(nsm_procedures)];
अटल स्थिर काष्ठा rpc_version nsm_version1 = अणु
	.number		= 1,
	.nrprocs	= ARRAY_SIZE(nsm_procedures),
	.procs		= nsm_procedures,
	.counts		= nsm_version1_counts,
पूर्ण;

अटल स्थिर काष्ठा rpc_version *nsm_version[] = अणु
	[1] = &nsm_version1,
पूर्ण;

अटल काष्ठा rpc_stat		nsm_stats;

अटल स्थिर काष्ठा rpc_program nsm_program = अणु
	.name		= "statd",
	.number		= NSM_PROGRAM,
	.nrvers		= ARRAY_SIZE(nsm_version),
	.version	= nsm_version,
	.stats		= &nsm_stats
पूर्ण;
