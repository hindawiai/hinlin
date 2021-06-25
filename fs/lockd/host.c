<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/lockd/host.c
 *
 * Management क्रम NLM peer hosts. The nlm_host काष्ठा is shared
 * between client and server implementation. The only reason to
 * करो so is to reduce code bloat.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/lockd/lockd.h>
#समावेश <linux/mutex.h>

#समावेश <linux/sunrpc/svc_xprt.h>

#समावेश <net/ipv6.h>

#समावेश "netns.h"

#घोषणा NLMDBG_FACILITY		NLMDBG_HOSTCACHE
#घोषणा NLM_HOST_NRHASH		32
#घोषणा NLM_HOST_REBIND		(60 * HZ)
#घोषणा NLM_HOST_EXPIRE		(300 * HZ)
#घोषणा NLM_HOST_COLLECT	(120 * HZ)

अटल काष्ठा hlist_head	nlm_server_hosts[NLM_HOST_NRHASH];
अटल काष्ठा hlist_head	nlm_client_hosts[NLM_HOST_NRHASH];

#घोषणा क्रम_each_host(host, chain, table) \
	क्रम ((chain) = (table); \
	     (chain) < (table) + NLM_HOST_NRHASH; ++(chain)) \
		hlist_क्रम_each_entry((host), (chain), h_hash)

#घोषणा क्रम_each_host_safe(host, next, chain, table) \
	क्रम ((chain) = (table); \
	     (chain) < (table) + NLM_HOST_NRHASH; ++(chain)) \
		hlist_क्रम_each_entry_safe((host), (next), \
						(chain), h_hash)

अटल अचिन्हित दीर्घ		nrhosts;
अटल DEFINE_MUTEX(nlm_host_mutex);

अटल व्योम			nlm_gc_hosts(काष्ठा net *net);

काष्ठा nlm_lookup_host_info अणु
	स्थिर पूर्णांक		server;		/* search क्रम server|client */
	स्थिर काष्ठा sockaddr	*sap;		/* address to search क्रम */
	स्थिर माप_प्रकार		salen;		/* it's length */
	स्थिर अचिन्हित लघु	protocol;	/* transport to search क्रम*/
	स्थिर u32		version;	/* NLM version to search क्रम */
	स्थिर अक्षर		*hostname;	/* remote's hostname */
	स्थिर माप_प्रकार		hostname_len;	/* it's length */
	स्थिर पूर्णांक		noresvport;	/* use non-priv port */
	काष्ठा net		*net;		/* network namespace to bind */
	स्थिर काष्ठा cred	*cred;
पूर्ण;

/*
 * Hash function must work well on big- and little-endian platक्रमms
 */
अटल अचिन्हित पूर्णांक __nlm_hash32(स्थिर __be32 n)
अणु
	अचिन्हित पूर्णांक hash = (__क्रमce u32)n ^ ((__क्रमce u32)n >> 16);
	वापस hash ^ (hash >> 8);
पूर्ण

अटल अचिन्हित पूर्णांक __nlm_hash_addr4(स्थिर काष्ठा sockaddr *sap)
अणु
	स्थिर काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)sap;
	वापस __nlm_hash32(sin->sin_addr.s_addr);
पूर्ण

अटल अचिन्हित पूर्णांक __nlm_hash_addr6(स्थिर काष्ठा sockaddr *sap)
अणु
	स्थिर काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)sap;
	स्थिर काष्ठा in6_addr addr = sin6->sin6_addr;
	वापस __nlm_hash32(addr.s6_addr32[0]) ^
	       __nlm_hash32(addr.s6_addr32[1]) ^
	       __nlm_hash32(addr.s6_addr32[2]) ^
	       __nlm_hash32(addr.s6_addr32[3]);
पूर्ण

अटल अचिन्हित पूर्णांक nlm_hash_address(स्थिर काष्ठा sockaddr *sap)
अणु
	अचिन्हित पूर्णांक hash;

	चयन (sap->sa_family) अणु
	हाल AF_INET:
		hash = __nlm_hash_addr4(sap);
		अवरोध;
	हाल AF_INET6:
		hash = __nlm_hash_addr6(sap);
		अवरोध;
	शेष:
		hash = 0;
	पूर्ण
	वापस hash & (NLM_HOST_NRHASH - 1);
पूर्ण

/*
 * Allocate and initialize an nlm_host.  Common to both client and server.
 */
अटल काष्ठा nlm_host *nlm_alloc_host(काष्ठा nlm_lookup_host_info *ni,
				       काष्ठा nsm_handle *nsm)
अणु
	काष्ठा nlm_host *host = शून्य;
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (nsm != शून्य)
		refcount_inc(&nsm->sm_count);
	अन्यथा अणु
		host = शून्य;
		nsm = nsm_get_handle(ni->net, ni->sap, ni->salen,
					ni->hostname, ni->hostname_len);
		अगर (unlikely(nsm == शून्य)) अणु
			dprपूर्णांकk("lockd: %s failed; no nsm handle\n",
				__func__);
			जाओ out;
		पूर्ण
	पूर्ण

	host = kदो_स्मृति(माप(*host), GFP_KERNEL);
	अगर (unlikely(host == शून्य)) अणु
		dprपूर्णांकk("lockd: %s failed; no memory\n", __func__);
		nsm_release(nsm);
		जाओ out;
	पूर्ण

	स_नकल(nlm_addr(host), ni->sap, ni->salen);
	host->h_addrlen    = ni->salen;
	rpc_set_port(nlm_addr(host), 0);
	host->h_srcaddrlen = 0;

	host->h_rpcclnt    = शून्य;
	host->h_name	   = nsm->sm_name;
	host->h_version    = ni->version;
	host->h_proto      = ni->protocol;
	host->h_reclaiming = 0;
	host->h_server     = ni->server;
	host->h_noresvport = ni->noresvport;
	host->h_inuse      = 0;
	init_रुकोqueue_head(&host->h_graceरुको);
	init_rwsem(&host->h_rwsem);
	host->h_state      = 0;
	host->h_nsmstate   = 0;
	host->h_pidcount   = 0;
	refcount_set(&host->h_count, 1);
	mutex_init(&host->h_mutex);
	host->h_nextrebind = now + NLM_HOST_REBIND;
	host->h_expires    = now + NLM_HOST_EXPIRE;
	INIT_LIST_HEAD(&host->h_lockowners);
	spin_lock_init(&host->h_lock);
	INIT_LIST_HEAD(&host->h_granted);
	INIT_LIST_HEAD(&host->h_reclaim);
	host->h_nsmhandle  = nsm;
	host->h_addrbuf    = nsm->sm_addrbuf;
	host->net	   = ni->net;
	host->h_cred	   = get_cred(ni->cred);
	strlcpy(host->nodename, utsname()->nodename, माप(host->nodename));

out:
	वापस host;
पूर्ण

/*
 * Destroy an nlm_host and मुक्त associated resources
 *
 * Caller must hold nlm_host_mutex.
 */
अटल व्योम nlm_destroy_host_locked(काष्ठा nlm_host *host)
अणु
	काष्ठा rpc_clnt	*clnt;
	काष्ठा lockd_net *ln = net_generic(host->net, lockd_net_id);

	dprपूर्णांकk("lockd: destroy host %s\n", host->h_name);

	hlist_del_init(&host->h_hash);

	nsm_unmonitor(host);
	nsm_release(host->h_nsmhandle);

	clnt = host->h_rpcclnt;
	अगर (clnt != शून्य)
		rpc_shutकरोwn_client(clnt);
	put_cred(host->h_cred);
	kमुक्त(host);

	ln->nrhosts--;
	nrhosts--;
पूर्ण

/**
 * nlmclnt_lookup_host - Find an NLM host handle matching a remote server
 * @sap: network address of server
 * @salen: length of server address
 * @protocol: transport protocol to use
 * @version: NLM protocol version
 * @hostname: '\0'-terminated hostname of server
 * @noresvport: 1 अगर non-privileged port should be used
 * @net: poपूर्णांकer to net namespace
 * @cred: poपूर्णांकer to cred
 *
 * Returns an nlm_host काष्ठाure that matches the passed-in
 * [server address, transport protocol, NLM version, server hostname].
 * If one करोesn't alपढ़ोy exist in the host cache, a new handle is
 * created and वापसed.
 */
काष्ठा nlm_host *nlmclnt_lookup_host(स्थिर काष्ठा sockaddr *sap,
				     स्थिर माप_प्रकार salen,
				     स्थिर अचिन्हित लघु protocol,
				     स्थिर u32 version,
				     स्थिर अक्षर *hostname,
				     पूर्णांक noresvport,
				     काष्ठा net *net,
				     स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nlm_lookup_host_info ni = अणु
		.server		= 0,
		.sap		= sap,
		.salen		= salen,
		.protocol	= protocol,
		.version	= version,
		.hostname	= hostname,
		.hostname_len	= म_माप(hostname),
		.noresvport	= noresvport,
		.net		= net,
		.cred		= cred,
	पूर्ण;
	काष्ठा hlist_head *chain;
	काष्ठा nlm_host	*host;
	काष्ठा nsm_handle *nsm = शून्य;
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

	dprपूर्णांकk("lockd: %s(host='%s', vers=%u, proto=%s)\n", __func__,
			(hostname ? hostname : "<none>"), version,
			(protocol == IPPROTO_UDP ? "udp" : "tcp"));

	mutex_lock(&nlm_host_mutex);

	chain = &nlm_client_hosts[nlm_hash_address(sap)];
	hlist_क्रम_each_entry(host, chain, h_hash) अणु
		अगर (host->net != net)
			जारी;
		अगर (!rpc_cmp_addr(nlm_addr(host), sap))
			जारी;

		/* Same address. Share an NSM handle अगर we alपढ़ोy have one */
		अगर (nsm == शून्य)
			nsm = host->h_nsmhandle;

		अगर (host->h_proto != protocol)
			जारी;
		अगर (host->h_version != version)
			जारी;

		nlm_get_host(host);
		dprपूर्णांकk("lockd: %s found host %s (%s)\n", __func__,
			host->h_name, host->h_addrbuf);
		जाओ out;
	पूर्ण

	host = nlm_alloc_host(&ni, nsm);
	अगर (unlikely(host == शून्य))
		जाओ out;

	hlist_add_head(&host->h_hash, chain);
	ln->nrhosts++;
	nrhosts++;

	dprपूर्णांकk("lockd: %s created host %s (%s)\n", __func__,
		host->h_name, host->h_addrbuf);

out:
	mutex_unlock(&nlm_host_mutex);
	वापस host;
पूर्ण

/**
 * nlmclnt_release_host - release client nlm_host
 * @host: nlm_host to release
 *
 */
व्योम nlmclnt_release_host(काष्ठा nlm_host *host)
अणु
	अगर (host == शून्य)
		वापस;

	dprपूर्णांकk("lockd: release client host %s\n", host->h_name);

	WARN_ON_ONCE(host->h_server);

	अगर (refcount_dec_and_mutex_lock(&host->h_count, &nlm_host_mutex)) अणु
		WARN_ON_ONCE(!list_empty(&host->h_lockowners));
		WARN_ON_ONCE(!list_empty(&host->h_granted));
		WARN_ON_ONCE(!list_empty(&host->h_reclaim));

		nlm_destroy_host_locked(host);
		mutex_unlock(&nlm_host_mutex);
	पूर्ण
पूर्ण

/**
 * nlmsvc_lookup_host - Find an NLM host handle matching a remote client
 * @rqstp: incoming NLM request
 * @hostname: name of client host
 * @hostname_len: length of client hostname
 *
 * Returns an nlm_host काष्ठाure that matches the [client address,
 * transport protocol, NLM version, client hostname] of the passed-in
 * NLM request.  If one करोesn't alपढ़ोy exist in the host cache, a
 * new handle is created and वापसed.
 *
 * Beक्रमe possibly creating a new nlm_host, स्थिरruct a sockaddr
 * क्रम a specअगरic source address in हाल the local प्रणाली has
 * multiple network addresses.  The family of the address in
 * rq_daddr is guaranteed to be the same as the family of the
 * address in rq_addr, so it's safe to use the same family क्रम
 * the source address.
 */
काष्ठा nlm_host *nlmsvc_lookup_host(स्थिर काष्ठा svc_rqst *rqstp,
				    स्थिर अक्षर *hostname,
				    स्थिर माप_प्रकार hostname_len)
अणु
	काष्ठा hlist_head *chain;
	काष्ठा nlm_host	*host = शून्य;
	काष्ठा nsm_handle *nsm = शून्य;
	काष्ठा sockaddr *src_sap = svc_daddr(rqstp);
	माप_प्रकार src_len = rqstp->rq_daddrlen;
	काष्ठा net *net = SVC_NET(rqstp);
	काष्ठा nlm_lookup_host_info ni = अणु
		.server		= 1,
		.sap		= svc_addr(rqstp),
		.salen		= rqstp->rq_addrlen,
		.protocol	= rqstp->rq_prot,
		.version	= rqstp->rq_vers,
		.hostname	= hostname,
		.hostname_len	= hostname_len,
		.net		= net,
	पूर्ण;
	काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

	dprपूर्णांकk("lockd: %s(host='%.*s', vers=%u, proto=%s)\n", __func__,
			(पूर्णांक)hostname_len, hostname, rqstp->rq_vers,
			(rqstp->rq_prot == IPPROTO_UDP ? "udp" : "tcp"));

	mutex_lock(&nlm_host_mutex);

	अगर (समय_after_eq(jअगरfies, ln->next_gc))
		nlm_gc_hosts(net);

	chain = &nlm_server_hosts[nlm_hash_address(ni.sap)];
	hlist_क्रम_each_entry(host, chain, h_hash) अणु
		अगर (host->net != net)
			जारी;
		अगर (!rpc_cmp_addr(nlm_addr(host), ni.sap))
			जारी;

		/* Same address. Share an NSM handle अगर we alपढ़ोy have one */
		अगर (nsm == शून्य)
			nsm = host->h_nsmhandle;

		अगर (host->h_proto != ni.protocol)
			जारी;
		अगर (host->h_version != ni.version)
			जारी;
		अगर (!rpc_cmp_addr(nlm_srcaddr(host), src_sap))
			जारी;

		/* Move to head of hash chain. */
		hlist_del(&host->h_hash);
		hlist_add_head(&host->h_hash, chain);

		nlm_get_host(host);
		dprपूर्णांकk("lockd: %s found host %s (%s)\n",
			__func__, host->h_name, host->h_addrbuf);
		जाओ out;
	पूर्ण

	host = nlm_alloc_host(&ni, nsm);
	अगर (unlikely(host == शून्य))
		जाओ out;

	स_नकल(nlm_srcaddr(host), src_sap, src_len);
	host->h_srcaddrlen = src_len;
	hlist_add_head(&host->h_hash, chain);
	ln->nrhosts++;
	nrhosts++;

	refcount_inc(&host->h_count);

	dprपूर्णांकk("lockd: %s created host %s (%s)\n",
		__func__, host->h_name, host->h_addrbuf);

out:
	mutex_unlock(&nlm_host_mutex);
	वापस host;
पूर्ण

/**
 * nlmsvc_release_host - release server nlm_host
 * @host: nlm_host to release
 *
 * Host is destroyed later in nlm_gc_host().
 */
व्योम nlmsvc_release_host(काष्ठा nlm_host *host)
अणु
	अगर (host == शून्य)
		वापस;

	dprपूर्णांकk("lockd: release server host %s\n", host->h_name);

	WARN_ON_ONCE(!host->h_server);
	refcount_dec(&host->h_count);
पूर्ण

/*
 * Create the NLM RPC client क्रम an NLM peer
 */
काष्ठा rpc_clnt *
nlm_bind_host(काष्ठा nlm_host *host)
अणु
	काष्ठा rpc_clnt	*clnt;

	dprपूर्णांकk("lockd: nlm_bind_host %s (%s)\n",
			host->h_name, host->h_addrbuf);

	/* Lock host handle */
	mutex_lock(&host->h_mutex);

	/* If we've alपढ़ोy created an RPC client, check whether
	 * RPC rebind is required
	 */
	अगर ((clnt = host->h_rpcclnt) != शून्य) अणु
		nlm_rebind_host(host);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ increment = nlmsvc_समयout;
		काष्ठा rpc_समयout समयparms = अणु
			.to_initval	= increment,
			.to_increment	= increment,
			.to_maxval	= increment * 6UL,
			.to_retries	= 5U,
		पूर्ण;
		काष्ठा rpc_create_args args = अणु
			.net		= host->net,
			.protocol	= host->h_proto,
			.address	= nlm_addr(host),
			.addrsize	= host->h_addrlen,
			.समयout	= &समयparms,
			.servername	= host->h_name,
			.program	= &nlm_program,
			.version	= host->h_version,
			.authflavor	= RPC_AUTH_UNIX,
			.flags		= (RPC_CLNT_CREATE_NOPING |
					   RPC_CLNT_CREATE_AUTOBIND |
					   RPC_CLNT_CREATE_REUSEPORT),
			.cred		= host->h_cred,
		पूर्ण;

		/*
		 * lockd retries server side blocks स्वतःmatically so we want
		 * those to be soft RPC calls. Client side calls need to be
		 * hard RPC tasks.
		 */
		अगर (!host->h_server)
			args.flags |= RPC_CLNT_CREATE_HARDRTRY;
		अगर (host->h_noresvport)
			args.flags |= RPC_CLNT_CREATE_NONPRIVPORT;
		अगर (host->h_srcaddrlen)
			args.saddress = nlm_srcaddr(host);

		clnt = rpc_create(&args);
		अगर (!IS_ERR(clnt))
			host->h_rpcclnt = clnt;
		अन्यथा अणु
			prपूर्णांकk("lockd: couldn't create RPC handle for %s\n", host->h_name);
			clnt = शून्य;
		पूर्ण
	पूर्ण

	mutex_unlock(&host->h_mutex);
	वापस clnt;
पूर्ण

/**
 * nlm_rebind_host - If needed, क्रमce a porपंचांगap lookup of the peer's lockd port
 * @host: NLM host handle क्रम peer
 *
 * This is not needed when using a connection-oriented protocol, such as TCP.
 * The existing स्वतःbind mechanism is sufficient to क्रमce a rebind when
 * required, e.g. on connection state transitions.
 */
व्योम
nlm_rebind_host(काष्ठा nlm_host *host)
अणु
	अगर (host->h_proto != IPPROTO_UDP)
		वापस;

	अगर (host->h_rpcclnt && समय_after_eq(jअगरfies, host->h_nextrebind)) अणु
		rpc_क्रमce_rebind(host->h_rpcclnt);
		host->h_nextrebind = jअगरfies + NLM_HOST_REBIND;
	पूर्ण
पूर्ण

/*
 * Increment NLM host count
 */
काष्ठा nlm_host * nlm_get_host(काष्ठा nlm_host *host)
अणु
	अगर (host) अणु
		dprपूर्णांकk("lockd: get host %s\n", host->h_name);
		refcount_inc(&host->h_count);
		host->h_expires = jअगरfies + NLM_HOST_EXPIRE;
	पूर्ण
	वापस host;
पूर्ण

अटल काष्ठा nlm_host *next_host_state(काष्ठा hlist_head *cache,
					काष्ठा nsm_handle *nsm,
					स्थिर काष्ठा nlm_reboot *info)
अणु
	काष्ठा nlm_host *host;
	काष्ठा hlist_head *chain;

	mutex_lock(&nlm_host_mutex);
	क्रम_each_host(host, chain, cache) अणु
		अगर (host->h_nsmhandle == nsm
		    && host->h_nsmstate != info->state) अणु
			host->h_nsmstate = info->state;
			host->h_state++;

			nlm_get_host(host);
			mutex_unlock(&nlm_host_mutex);
			वापस host;
		पूर्ण
	पूर्ण

	mutex_unlock(&nlm_host_mutex);
	वापस शून्य;
पूर्ण

/**
 * nlm_host_rebooted - Release all resources held by rebooted host
 * @net:  network namespace
 * @info: poपूर्णांकer to decoded results of NLM_SM_NOTIFY call
 *
 * We were notअगरied that the specअगरied host has rebooted.  Release
 * all resources held by that peer.
 */
व्योम nlm_host_rebooted(स्थिर काष्ठा net *net, स्थिर काष्ठा nlm_reboot *info)
अणु
	काष्ठा nsm_handle *nsm;
	काष्ठा nlm_host	*host;

	nsm = nsm_reboot_lookup(net, info);
	अगर (unlikely(nsm == शून्य))
		वापस;

	/* Mark all hosts tied to this NSM state as having rebooted.
	 * We run the loop repeatedly, because we drop the host table
	 * lock क्रम this.
	 * To aव्योम processing a host several बार, we match the nsmstate.
	 */
	जबतक ((host = next_host_state(nlm_server_hosts, nsm, info)) != शून्य) अणु
		nlmsvc_मुक्त_host_resources(host);
		nlmsvc_release_host(host);
	पूर्ण
	जबतक ((host = next_host_state(nlm_client_hosts, nsm, info)) != शून्य) अणु
		nlmclnt_recovery(host);
		nlmclnt_release_host(host);
	पूर्ण

	nsm_release(nsm);
पूर्ण

अटल व्योम nlm_complain_hosts(काष्ठा net *net)
अणु
	काष्ठा hlist_head *chain;
	काष्ठा nlm_host	*host;

	अगर (net) अणु
		काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

		अगर (ln->nrhosts == 0)
			वापस;
		pr_warn("lockd: couldn't shutdown host module for net %x!\n",
			net->ns.inum);
		dprपूर्णांकk("lockd: %lu hosts left in net %x:\n", ln->nrhosts,
			net->ns.inum);
	पूर्ण अन्यथा अणु
		अगर (nrhosts == 0)
			वापस;
		prपूर्णांकk(KERN_WARNING "lockd: couldn't shutdown host module!\n");
		dprपूर्णांकk("lockd: %lu hosts left:\n", nrhosts);
	पूर्ण

	क्रम_each_host(host, chain, nlm_server_hosts) अणु
		अगर (net && host->net != net)
			जारी;
		dprपूर्णांकk("       %s (cnt %d use %d exp %ld net %x)\n",
			host->h_name, refcount_पढ़ो(&host->h_count),
			host->h_inuse, host->h_expires, host->net->ns.inum);
	पूर्ण
पूर्ण

व्योम
nlm_shutकरोwn_hosts_net(काष्ठा net *net)
अणु
	काष्ठा hlist_head *chain;
	काष्ठा nlm_host	*host;

	mutex_lock(&nlm_host_mutex);

	/* First, make all hosts eligible क्रम gc */
	dprपूर्णांकk("lockd: nuking all hosts in net %x...\n",
		net ? net->ns.inum : 0);
	क्रम_each_host(host, chain, nlm_server_hosts) अणु
		अगर (net && host->net != net)
			जारी;
		host->h_expires = jअगरfies - 1;
		अगर (host->h_rpcclnt) अणु
			rpc_shutकरोwn_client(host->h_rpcclnt);
			host->h_rpcclnt = शून्य;
		पूर्ण
	पूर्ण

	/* Then, perक्रमm a garbage collection pass */
	nlm_gc_hosts(net);
	nlm_complain_hosts(net);
	mutex_unlock(&nlm_host_mutex);
पूर्ण

/*
 * Shut करोwn the hosts module.
 * Note that this routine is called only at server shutकरोwn समय.
 */
व्योम
nlm_shutकरोwn_hosts(व्योम)
अणु
	dprपूर्णांकk("lockd: shutting down host module\n");
	nlm_shutकरोwn_hosts_net(शून्य);
पूर्ण

/*
 * Garbage collect any unused NLM hosts.
 * This GC combines reference counting क्रम async operations with
 * mark & sweep क्रम resources held by remote clients.
 */
अटल व्योम
nlm_gc_hosts(काष्ठा net *net)
अणु
	काष्ठा hlist_head *chain;
	काष्ठा hlist_node *next;
	काष्ठा nlm_host	*host;

	dprपूर्णांकk("lockd: host garbage collection for net %x\n",
		net ? net->ns.inum : 0);
	क्रम_each_host(host, chain, nlm_server_hosts) अणु
		अगर (net && host->net != net)
			जारी;
		host->h_inuse = 0;
	पूर्ण

	/* Mark all hosts that hold locks, blocks or shares */
	nlmsvc_mark_resources(net);

	क्रम_each_host_safe(host, next, chain, nlm_server_hosts) अणु
		अगर (net && host->net != net)
			जारी;
		अगर (host->h_inuse || समय_beक्रमe(jअगरfies, host->h_expires)) अणु
			dprपूर्णांकk("nlm_gc_hosts skipping %s "
				"(cnt %d use %d exp %ld net %x)\n",
				host->h_name, refcount_पढ़ो(&host->h_count),
				host->h_inuse, host->h_expires,
				host->net->ns.inum);
			जारी;
		पूर्ण
		अगर (refcount_dec_अगर_one(&host->h_count))
			nlm_destroy_host_locked(host);
	पूर्ण

	अगर (net) अणु
		काष्ठा lockd_net *ln = net_generic(net, lockd_net_id);

		ln->next_gc = jअगरfies + NLM_HOST_COLLECT;
	पूर्ण
पूर्ण
