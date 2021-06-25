<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Central processing क्रम nfsd.
 *
 * Authors:	Olaf Kirch (okir@monad.swb.de)
 *
 * Copyright (C) 1995, 1996, 1997 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/sched/संकेत.स>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/module.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/swap.h>

#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <linux/lockd/bind.h>
#समावेश <linux/nfsacl.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/inetdevice.h>
#समावेश <net/addrconf.h>
#समावेश <net/ipv6.h>
#समावेश <net/net_namespace.h>
#समावेश "nfsd.h"
#समावेश "cache.h"
#समावेश "vfs.h"
#समावेश "netns.h"
#समावेश "filecache.h"

#समावेश "trace.h"

#घोषणा NFSDDBG_FACILITY	NFSDDBG_SVC

बाह्य काष्ठा svc_program	nfsd_program;
अटल पूर्णांक			nfsd(व्योम *vrqstp);
#अगर defined(CONFIG_NFSD_V2_ACL) || defined(CONFIG_NFSD_V3_ACL)
अटल पूर्णांक			nfsd_acl_rpcbind_set(काष्ठा net *,
						     स्थिर काष्ठा svc_program *,
						     u32, पूर्णांक,
						     अचिन्हित लघु,
						     अचिन्हित लघु);
अटल __be32			nfsd_acl_init_request(काष्ठा svc_rqst *,
						स्थिर काष्ठा svc_program *,
						काष्ठा svc_process_info *);
#पूर्ण_अगर
अटल पूर्णांक			nfsd_rpcbind_set(काष्ठा net *,
						 स्थिर काष्ठा svc_program *,
						 u32, पूर्णांक,
						 अचिन्हित लघु,
						 अचिन्हित लघु);
अटल __be32			nfsd_init_request(काष्ठा svc_rqst *,
						स्थिर काष्ठा svc_program *,
						काष्ठा svc_process_info *);

/*
 * nfsd_mutex protects nn->nfsd_serv -- both the poपूर्णांकer itself and the members
 * of the svc_serv काष्ठा. In particular, ->sv_nrthपढ़ोs but also to some
 * extent ->sv_temp_socks and ->sv_permsocks. It also protects nfsdstats.th_cnt
 *
 * If (out side the lock) nn->nfsd_serv is non-शून्य, then it must poपूर्णांक to a
 * properly initialised 'struct svc_serv' with ->sv_nrthपढ़ोs > 0. That number
 * of nfsd thपढ़ोs must exist and each must listed in ->sp_all_thपढ़ोs in each
 * entry of ->sv_pools[].
 *
 * Transitions of the thपढ़ो count between zero and non-zero are of particular
 * पूर्णांकerest since the svc_serv needs to be created and initialized at that
 * poपूर्णांक, or मुक्तd.
 *
 * Finally, the nfsd_mutex also protects some of the global variables that are
 * accessed when nfsd starts and that are settable via the ग_लिखो_* routines in
 * nfsctl.c. In particular:
 *
 *	user_recovery_स_नाम
 *	user_lease_समय
 *	nfsd_versions
 */
DEFINE_MUTEX(nfsd_mutex);

/*
 * nfsd_drc_lock protects nfsd_drc_max_pages and nfsd_drc_pages_used.
 * nfsd_drc_max_pages limits the total amount of memory available क्रम
 * version 4.1 DRC caches.
 * nfsd_drc_pages_used tracks the current version 4.1 DRC memory usage.
 */
DEFINE_SPINLOCK(nfsd_drc_lock);
अचिन्हित दीर्घ	nfsd_drc_max_mem;
अचिन्हित दीर्घ	nfsd_drc_mem_used;

#अगर defined(CONFIG_NFSD_V2_ACL) || defined(CONFIG_NFSD_V3_ACL)
अटल काष्ठा svc_stat	nfsd_acl_svcstats;
अटल स्थिर काष्ठा svc_version *nfsd_acl_version[] = अणु
	[2] = &nfsd_acl_version2,
	[3] = &nfsd_acl_version3,
पूर्ण;

#घोषणा NFSD_ACL_MINVERS            2
#घोषणा NFSD_ACL_NRVERS		ARRAY_SIZE(nfsd_acl_version)

अटल काष्ठा svc_program	nfsd_acl_program = अणु
	.pg_prog		= NFS_ACL_PROGRAM,
	.pg_nvers		= NFSD_ACL_NRVERS,
	.pg_vers		= nfsd_acl_version,
	.pg_name		= "nfsacl",
	.pg_class		= "nfsd",
	.pg_stats		= &nfsd_acl_svcstats,
	.pg_authenticate	= &svc_set_client,
	.pg_init_request	= nfsd_acl_init_request,
	.pg_rpcbind_set		= nfsd_acl_rpcbind_set,
पूर्ण;

अटल काष्ठा svc_stat	nfsd_acl_svcstats = अणु
	.program	= &nfsd_acl_program,
पूर्ण;
#पूर्ण_अगर /* defined(CONFIG_NFSD_V2_ACL) || defined(CONFIG_NFSD_V3_ACL) */

अटल स्थिर काष्ठा svc_version *nfsd_version[] = अणु
	[2] = &nfsd_version2,
#अगर defined(CONFIG_NFSD_V3)
	[3] = &nfsd_version3,
#पूर्ण_अगर
#अगर defined(CONFIG_NFSD_V4)
	[4] = &nfsd_version4,
#पूर्ण_अगर
पूर्ण;

#घोषणा NFSD_MINVERS    	2
#घोषणा NFSD_NRVERS		ARRAY_SIZE(nfsd_version)

काष्ठा svc_program		nfsd_program = अणु
#अगर defined(CONFIG_NFSD_V2_ACL) || defined(CONFIG_NFSD_V3_ACL)
	.pg_next		= &nfsd_acl_program,
#पूर्ण_अगर
	.pg_prog		= NFS_PROGRAM,		/* program number */
	.pg_nvers		= NFSD_NRVERS,		/* nr of entries in nfsd_version */
	.pg_vers		= nfsd_version,		/* version table */
	.pg_name		= "nfsd",		/* program name */
	.pg_class		= "nfsd",		/* authentication class */
	.pg_stats		= &nfsd_svcstats,	/* version table */
	.pg_authenticate	= &svc_set_client,	/* export authentication */
	.pg_init_request	= nfsd_init_request,
	.pg_rpcbind_set		= nfsd_rpcbind_set,
पूर्ण;

अटल bool
nfsd_support_version(पूर्णांक vers)
अणु
	अगर (vers >= NFSD_MINVERS && vers < NFSD_NRVERS)
		वापस nfsd_version[vers] != शून्य;
	वापस false;
पूर्ण

अटल bool *
nfsd_alloc_versions(व्योम)
अणु
	bool *vers = kदो_स्मृति_array(NFSD_NRVERS, माप(bool), GFP_KERNEL);
	अचिन्हित i;

	अगर (vers) अणु
		/* All compiled versions are enabled by शेष */
		क्रम (i = 0; i < NFSD_NRVERS; i++)
			vers[i] = nfsd_support_version(i);
	पूर्ण
	वापस vers;
पूर्ण

अटल bool *
nfsd_alloc_minorversions(व्योम)
अणु
	bool *vers = kदो_स्मृति_array(NFSD_SUPPORTED_MINOR_VERSION + 1,
			माप(bool), GFP_KERNEL);
	अचिन्हित i;

	अगर (vers) अणु
		/* All minor versions are enabled by शेष */
		क्रम (i = 0; i <= NFSD_SUPPORTED_MINOR_VERSION; i++)
			vers[i] = nfsd_support_version(4);
	पूर्ण
	वापस vers;
पूर्ण

व्योम
nfsd_netns_मुक्त_versions(काष्ठा nfsd_net *nn)
अणु
	kमुक्त(nn->nfsd_versions);
	kमुक्त(nn->nfsd4_minorversions);
	nn->nfsd_versions = शून्य;
	nn->nfsd4_minorversions = शून्य;
पूर्ण

अटल व्योम
nfsd_netns_init_versions(काष्ठा nfsd_net *nn)
अणु
	अगर (!nn->nfsd_versions) अणु
		nn->nfsd_versions = nfsd_alloc_versions();
		nn->nfsd4_minorversions = nfsd_alloc_minorversions();
		अगर (!nn->nfsd_versions || !nn->nfsd4_minorversions)
			nfsd_netns_मुक्त_versions(nn);
	पूर्ण
पूर्ण

पूर्णांक nfsd_vers(काष्ठा nfsd_net *nn, पूर्णांक vers, क्रमागत vers_op change)
अणु
	अगर (vers < NFSD_MINVERS || vers >= NFSD_NRVERS)
		वापस 0;
	चयन(change) अणु
	हाल NFSD_SET:
		अगर (nn->nfsd_versions)
			nn->nfsd_versions[vers] = nfsd_support_version(vers);
		अवरोध;
	हाल NFSD_CLEAR:
		nfsd_netns_init_versions(nn);
		अगर (nn->nfsd_versions)
			nn->nfsd_versions[vers] = false;
		अवरोध;
	हाल NFSD_TEST:
		अगर (nn->nfsd_versions)
			वापस nn->nfsd_versions[vers];
		fallthrough;
	हाल NFSD_AVAIL:
		वापस nfsd_support_version(vers);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
nfsd_adjust_nfsd_versions4(काष्ठा nfsd_net *nn)
अणु
	अचिन्हित i;

	क्रम (i = 0; i <= NFSD_SUPPORTED_MINOR_VERSION; i++) अणु
		अगर (nn->nfsd4_minorversions[i])
			वापस;
	पूर्ण
	nfsd_vers(nn, 4, NFSD_CLEAR);
पूर्ण

पूर्णांक nfsd_minorversion(काष्ठा nfsd_net *nn, u32 minorversion, क्रमागत vers_op change)
अणु
	अगर (minorversion > NFSD_SUPPORTED_MINOR_VERSION &&
	    change != NFSD_AVAIL)
		वापस -1;

	चयन(change) अणु
	हाल NFSD_SET:
		अगर (nn->nfsd4_minorversions) अणु
			nfsd_vers(nn, 4, NFSD_SET);
			nn->nfsd4_minorversions[minorversion] =
				nfsd_vers(nn, 4, NFSD_TEST);
		पूर्ण
		अवरोध;
	हाल NFSD_CLEAR:
		nfsd_netns_init_versions(nn);
		अगर (nn->nfsd4_minorversions) अणु
			nn->nfsd4_minorversions[minorversion] = false;
			nfsd_adjust_nfsd_versions4(nn);
		पूर्ण
		अवरोध;
	हाल NFSD_TEST:
		अगर (nn->nfsd4_minorversions)
			वापस nn->nfsd4_minorversions[minorversion];
		वापस nfsd_vers(nn, 4, NFSD_TEST);
	हाल NFSD_AVAIL:
		वापस minorversion <= NFSD_SUPPORTED_MINOR_VERSION &&
			nfsd_vers(nn, 4, NFSD_AVAIL);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Maximum number of nfsd processes
 */
#घोषणा	NFSD_MAXSERVS		8192

पूर्णांक nfsd_nrthपढ़ोs(काष्ठा net *net)
अणु
	पूर्णांक rv = 0;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	mutex_lock(&nfsd_mutex);
	अगर (nn->nfsd_serv)
		rv = nn->nfsd_serv->sv_nrthपढ़ोs;
	mutex_unlock(&nfsd_mutex);
	वापस rv;
पूर्ण

अटल पूर्णांक nfsd_init_socks(काष्ठा net *net, स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक error;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	अगर (!list_empty(&nn->nfsd_serv->sv_permsocks))
		वापस 0;

	error = svc_create_xprt(nn->nfsd_serv, "udp", net, PF_INET, NFS_PORT,
					SVC_SOCK_DEFAULTS, cred);
	अगर (error < 0)
		वापस error;

	error = svc_create_xprt(nn->nfsd_serv, "tcp", net, PF_INET, NFS_PORT,
					SVC_SOCK_DEFAULTS, cred);
	अगर (error < 0)
		वापस error;

	वापस 0;
पूर्ण

अटल पूर्णांक nfsd_users = 0;

अटल पूर्णांक nfsd_startup_generic(व्योम)
अणु
	पूर्णांक ret;

	अगर (nfsd_users++)
		वापस 0;

	ret = nfsd_file_cache_init();
	अगर (ret)
		जाओ dec_users;

	ret = nfs4_state_start();
	अगर (ret)
		जाओ out_file_cache;
	वापस 0;

out_file_cache:
	nfsd_file_cache_shutकरोwn();
dec_users:
	nfsd_users--;
	वापस ret;
पूर्ण

अटल व्योम nfsd_shutकरोwn_generic(व्योम)
अणु
	अगर (--nfsd_users)
		वापस;

	nfs4_state_shutकरोwn();
	nfsd_file_cache_shutकरोwn();
पूर्ण

अटल bool nfsd_needs_lockd(काष्ठा nfsd_net *nn)
अणु
	वापस nfsd_vers(nn, 2, NFSD_TEST) || nfsd_vers(nn, 3, NFSD_TEST);
पूर्ण

व्योम nfsd_copy_boot_verअगरier(__be32 verf[2], काष्ठा nfsd_net *nn)
अणु
	पूर्णांक seq = 0;

	करो अणु
		पढ़ो_seqbegin_or_lock(&nn->boot_lock, &seq);
		/*
		 * This is opaque to client, so no need to byte-swap. Use
		 * __क्रमce to keep sparse happy. y2038 समय_प्रकार overflow is
		 * irrelevant in this usage
		 */
		verf[0] = (__क्रमce __be32)nn->nfssvc_boot.tv_sec;
		verf[1] = (__क्रमce __be32)nn->nfssvc_boot.tv_nsec;
	पूर्ण जबतक (need_seqretry(&nn->boot_lock, seq));
	करोne_seqretry(&nn->boot_lock, seq);
पूर्ण

अटल व्योम nfsd_reset_boot_verअगरier_locked(काष्ठा nfsd_net *nn)
अणु
	kसमय_get_real_ts64(&nn->nfssvc_boot);
पूर्ण

व्योम nfsd_reset_boot_verअगरier(काष्ठा nfsd_net *nn)
अणु
	ग_लिखो_seqlock(&nn->boot_lock);
	nfsd_reset_boot_verअगरier_locked(nn);
	ग_लिखो_sequnlock(&nn->boot_lock);
पूर्ण

अटल पूर्णांक nfsd_startup_net(काष्ठा net *net, स्थिर काष्ठा cred *cred)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	पूर्णांक ret;

	अगर (nn->nfsd_net_up)
		वापस 0;

	ret = nfsd_startup_generic();
	अगर (ret)
		वापस ret;
	ret = nfsd_init_socks(net, cred);
	अगर (ret)
		जाओ out_socks;

	अगर (nfsd_needs_lockd(nn) && !nn->lockd_up) अणु
		ret = lockd_up(net, cred);
		अगर (ret)
			जाओ out_socks;
		nn->lockd_up = true;
	पूर्ण

	ret = nfsd_file_cache_start_net(net);
	अगर (ret)
		जाओ out_lockd;
	ret = nfs4_state_start_net(net);
	अगर (ret)
		जाओ out_filecache;

	nn->nfsd_net_up = true;
	वापस 0;

out_filecache:
	nfsd_file_cache_shutकरोwn_net(net);
out_lockd:
	अगर (nn->lockd_up) अणु
		lockd_करोwn(net);
		nn->lockd_up = false;
	पूर्ण
out_socks:
	nfsd_shutकरोwn_generic();
	वापस ret;
पूर्ण

अटल व्योम nfsd_shutकरोwn_net(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	nfsd_file_cache_shutकरोwn_net(net);
	nfs4_state_shutकरोwn_net(net);
	अगर (nn->lockd_up) अणु
		lockd_करोwn(net);
		nn->lockd_up = false;
	पूर्ण
	nn->nfsd_net_up = false;
	nfsd_shutकरोwn_generic();
पूर्ण

अटल पूर्णांक nfsd_inetaddr_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
	व्योम *ptr)
अणु
	काष्ठा in_अगरaddr *अगरa = (काष्ठा in_अगरaddr *)ptr;
	काष्ठा net_device *dev = अगरa->अगरa_dev->dev;
	काष्ठा net *net = dev_net(dev);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	काष्ठा sockaddr_in sin;

	अगर ((event != NETDEV_DOWN) ||
	    !atomic_inc_not_zero(&nn->ntf_refcnt))
		जाओ out;

	अगर (nn->nfsd_serv) अणु
		dprपूर्णांकk("nfsd_inetaddr_event: removed %pI4\n", &अगरa->अगरa_local);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = अगरa->अगरa_local;
		svc_age_temp_xprts_now(nn->nfsd_serv, (काष्ठा sockaddr *)&sin);
	पूर्ण
	atomic_dec(&nn->ntf_refcnt);
	wake_up(&nn->ntf_wq);

out:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nfsd_inetaddr_notअगरier = अणु
	.notअगरier_call = nfsd_inetaddr_event,
पूर्ण;

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक nfsd_inet6addr_event(काष्ठा notअगरier_block *this,
	अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा inet6_अगरaddr *अगरa = (काष्ठा inet6_अगरaddr *)ptr;
	काष्ठा net_device *dev = अगरa->idev->dev;
	काष्ठा net *net = dev_net(dev);
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	काष्ठा sockaddr_in6 sin6;

	अगर ((event != NETDEV_DOWN) ||
	    !atomic_inc_not_zero(&nn->ntf_refcnt))
		जाओ out;

	अगर (nn->nfsd_serv) अणु
		dprपूर्णांकk("nfsd_inet6addr_event: removed %pI6\n", &अगरa->addr);
		sin6.sin6_family = AF_INET6;
		sin6.sin6_addr = अगरa->addr;
		अगर (ipv6_addr_type(&sin6.sin6_addr) & IPV6_ADDR_LINKLOCAL)
			sin6.sin6_scope_id = अगरa->idev->dev->अगरindex;
		svc_age_temp_xprts_now(nn->nfsd_serv, (काष्ठा sockaddr *)&sin6);
	पूर्ण
	atomic_dec(&nn->ntf_refcnt);
	wake_up(&nn->ntf_wq);
out:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block nfsd_inet6addr_notअगरier = अणु
	.notअगरier_call = nfsd_inet6addr_event,
पूर्ण;
#पूर्ण_अगर

/* Only used under nfsd_mutex, so this atomic may be overसमाप्त: */
अटल atomic_t nfsd_notअगरier_refcount = ATOMIC_INIT(0);

अटल व्योम nfsd_last_thपढ़ो(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	atomic_dec(&nn->ntf_refcnt);
	/* check अगर the notअगरier still has clients */
	अगर (atomic_dec_वापस(&nfsd_notअगरier_refcount) == 0) अणु
		unरेजिस्टर_inetaddr_notअगरier(&nfsd_inetaddr_notअगरier);
#अगर IS_ENABLED(CONFIG_IPV6)
		unरेजिस्टर_inet6addr_notअगरier(&nfsd_inet6addr_notअगरier);
#पूर्ण_अगर
	पूर्ण
	रुको_event(nn->ntf_wq, atomic_पढ़ो(&nn->ntf_refcnt) == 0);

	/*
	 * ग_लिखो_ports can create the server without actually starting
	 * any thपढ़ोs--अगर we get shut करोwn beक्रमe any thपढ़ोs are
	 * started, then nfsd_last_thपढ़ो will be run beक्रमe any of this
	 * other initialization has been करोne except the rpcb inक्रमmation.
	 */
	svc_rpcb_cleanup(serv, net);
	अगर (!nn->nfsd_net_up)
		वापस;

	nfsd_shutकरोwn_net(net);
	pr_info("nfsd: last server has exited, flushing export cache\n");
	nfsd_export_flush(net);
पूर्ण

व्योम nfsd_reset_versions(काष्ठा nfsd_net *nn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NFSD_NRVERS; i++)
		अगर (nfsd_vers(nn, i, NFSD_TEST))
			वापस;

	क्रम (i = 0; i < NFSD_NRVERS; i++)
		अगर (i != 4)
			nfsd_vers(nn, i, NFSD_SET);
		अन्यथा अणु
			पूर्णांक minor = 0;
			जबतक (nfsd_minorversion(nn, minor, NFSD_SET) >= 0)
				minor++;
		पूर्ण
पूर्ण

/*
 * Each session guarantees a negotiated per slot memory cache क्रम replies
 * which in turn consumes memory beyond the v2/v3/v4.0 server. A dedicated
 * NFSv4.1 server might want to use more memory क्रम a DRC than a machine
 * with mutiple services.
 *
 * Impose a hard limit on the number of pages क्रम the DRC which varies
 * according to the machines मुक्त pages. This is of course only a शेष.
 *
 * For now this is a #घोषणाd shअगरt which could be under admin control
 * in the future.
 */
अटल व्योम set_max_drc(व्योम)
अणु
	#घोषणा NFSD_DRC_SIZE_SHIFT	7
	nfsd_drc_max_mem = (nr_मुक्त_buffer_pages()
					>> NFSD_DRC_SIZE_SHIFT) * PAGE_SIZE;
	nfsd_drc_mem_used = 0;
	dprपूर्णांकk("%s nfsd_drc_max_mem %lu \n", __func__, nfsd_drc_max_mem);
पूर्ण

अटल पूर्णांक nfsd_get_शेष_max_blksize(व्योम)
अणु
	काष्ठा sysinfo i;
	अचिन्हित दीर्घ दीर्घ target;
	अचिन्हित दीर्घ ret;

	si_meminfo(&i);
	target = (i.totalram - i.totalhigh) << PAGE_SHIFT;
	/*
	 * Aim क्रम 1/4096 of memory per thपढ़ो This gives 1MB on 4Gig
	 * machines, but only uses 32K on 128M machines.  Bottom out at
	 * 8K on 32M and smaller.  Of course, this is only a शेष.
	 */
	target >>= 12;

	ret = NFSSVC_MAXBLKSIZE;
	जबतक (ret > target && ret >= 8*1024*2)
		ret /= 2;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा svc_serv_ops nfsd_thपढ़ो_sv_ops = अणु
	.svo_shutकरोwn		= nfsd_last_thपढ़ो,
	.svo_function		= nfsd,
	.svo_enqueue_xprt	= svc_xprt_करो_enqueue,
	.svo_setup		= svc_set_num_thपढ़ोs,
	.svo_module		= THIS_MODULE,
पूर्ण;

अटल व्योम nfsd_complete_shutकरोwn(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	WARN_ON(!mutex_is_locked(&nfsd_mutex));

	nn->nfsd_serv = शून्य;
	complete(&nn->nfsd_shutकरोwn_complete);
पूर्ण

व्योम nfsd_shutकरोwn_thपढ़ोs(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	काष्ठा svc_serv *serv;

	mutex_lock(&nfsd_mutex);
	serv = nn->nfsd_serv;
	अगर (serv == शून्य) अणु
		mutex_unlock(&nfsd_mutex);
		वापस;
	पूर्ण

	svc_get(serv);
	/* Kill outstanding nfsd thपढ़ोs */
	serv->sv_ops->svo_setup(serv, शून्य, 0);
	nfsd_destroy(net);
	mutex_unlock(&nfsd_mutex);
	/* Wait क्रम shutकरोwn of nfsd_serv to complete */
	रुको_क्रम_completion(&nn->nfsd_shutकरोwn_complete);
पूर्ण

bool i_am_nfsd(व्योम)
अणु
	वापस kthपढ़ो_func(current) == nfsd;
पूर्ण

पूर्णांक nfsd_create_serv(काष्ठा net *net)
अणु
	पूर्णांक error;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	WARN_ON(!mutex_is_locked(&nfsd_mutex));
	अगर (nn->nfsd_serv) अणु
		svc_get(nn->nfsd_serv);
		वापस 0;
	पूर्ण
	अगर (nfsd_max_blksize == 0)
		nfsd_max_blksize = nfsd_get_शेष_max_blksize();
	nfsd_reset_versions(nn);
	nn->nfsd_serv = svc_create_pooled(&nfsd_program, nfsd_max_blksize,
						&nfsd_thपढ़ो_sv_ops);
	अगर (nn->nfsd_serv == शून्य)
		वापस -ENOMEM;
	init_completion(&nn->nfsd_shutकरोwn_complete);

	nn->nfsd_serv->sv_maxconn = nn->max_connections;
	error = svc_bind(nn->nfsd_serv, net);
	अगर (error < 0) अणु
		svc_destroy(nn->nfsd_serv);
		nfsd_complete_shutकरोwn(net);
		वापस error;
	पूर्ण

	set_max_drc();
	/* check अगर the notअगरier is alपढ़ोy set */
	अगर (atomic_inc_वापस(&nfsd_notअगरier_refcount) == 1) अणु
		रेजिस्टर_inetaddr_notअगरier(&nfsd_inetaddr_notअगरier);
#अगर IS_ENABLED(CONFIG_IPV6)
		रेजिस्टर_inet6addr_notअगरier(&nfsd_inet6addr_notअगरier);
#पूर्ण_अगर
	पूर्ण
	atomic_inc(&nn->ntf_refcnt);
	nfsd_reset_boot_verअगरier(nn);
	वापस 0;
पूर्ण

पूर्णांक nfsd_nrpools(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	अगर (nn->nfsd_serv == शून्य)
		वापस 0;
	अन्यथा
		वापस nn->nfsd_serv->sv_nrpools;
पूर्ण

पूर्णांक nfsd_get_nrthपढ़ोs(पूर्णांक n, पूर्णांक *nthपढ़ोs, काष्ठा net *net)
अणु
	पूर्णांक i = 0;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	अगर (nn->nfsd_serv != शून्य) अणु
		क्रम (i = 0; i < nn->nfsd_serv->sv_nrpools && i < n; i++)
			nthपढ़ोs[i] = nn->nfsd_serv->sv_pools[i].sp_nrthपढ़ोs;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nfsd_destroy(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	पूर्णांक destroy = (nn->nfsd_serv->sv_nrthपढ़ोs == 1);

	अगर (destroy)
		svc_shutकरोwn_net(nn->nfsd_serv, net);
	svc_destroy(nn->nfsd_serv);
	अगर (destroy)
		nfsd_complete_shutकरोwn(net);
पूर्ण

पूर्णांक nfsd_set_nrthपढ़ोs(पूर्णांक n, पूर्णांक *nthपढ़ोs, काष्ठा net *net)
अणु
	पूर्णांक i = 0;
	पूर्णांक tot = 0;
	पूर्णांक err = 0;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	WARN_ON(!mutex_is_locked(&nfsd_mutex));

	अगर (nn->nfsd_serv == शून्य || n <= 0)
		वापस 0;

	अगर (n > nn->nfsd_serv->sv_nrpools)
		n = nn->nfsd_serv->sv_nrpools;

	/* enक्रमce a global maximum number of thपढ़ोs */
	tot = 0;
	क्रम (i = 0; i < n; i++) अणु
		nthपढ़ोs[i] = min(nthपढ़ोs[i], NFSD_MAXSERVS);
		tot += nthपढ़ोs[i];
	पूर्ण
	अगर (tot > NFSD_MAXSERVS) अणु
		/* total too large: scale करोwn requested numbers */
		क्रम (i = 0; i < n && tot > 0; i++) अणु
		    	पूर्णांक new = nthपढ़ोs[i] * NFSD_MAXSERVS / tot;
			tot -= (nthपढ़ोs[i] - new);
			nthपढ़ोs[i] = new;
		पूर्ण
		क्रम (i = 0; i < n && tot > 0; i++) अणु
			nthपढ़ोs[i]--;
			tot--;
		पूर्ण
	पूर्ण

	/*
	 * There must always be a thपढ़ो in pool 0; the admin
	 * can't shut करोwn NFS completely using pool_thपढ़ोs.
	 */
	अगर (nthपढ़ोs[0] == 0)
		nthपढ़ोs[0] = 1;

	/* apply the new numbers */
	svc_get(nn->nfsd_serv);
	क्रम (i = 0; i < n; i++) अणु
		err = nn->nfsd_serv->sv_ops->svo_setup(nn->nfsd_serv,
				&nn->nfsd_serv->sv_pools[i], nthपढ़ोs[i]);
		अगर (err)
			अवरोध;
	पूर्ण
	nfsd_destroy(net);
	वापस err;
पूर्ण

/*
 * Adjust the number of thपढ़ोs and वापस the new number of thपढ़ोs.
 * This is also the function that starts the server अगर necessary, अगर
 * this is the first समय nrservs is nonzero.
 */
पूर्णांक
nfsd_svc(पूर्णांक nrservs, काष्ठा net *net, स्थिर काष्ठा cred *cred)
अणु
	पूर्णांक	error;
	bool	nfsd_up_beक्रमe;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	mutex_lock(&nfsd_mutex);
	dprपूर्णांकk("nfsd: creating service\n");

	nrservs = max(nrservs, 0);
	nrservs = min(nrservs, NFSD_MAXSERVS);
	error = 0;

	अगर (nrservs == 0 && nn->nfsd_serv == शून्य)
		जाओ out;

	strlcpy(nn->nfsd_name, utsname()->nodename,
		माप(nn->nfsd_name));

	error = nfsd_create_serv(net);
	अगर (error)
		जाओ out;

	nfsd_up_beक्रमe = nn->nfsd_net_up;

	error = nfsd_startup_net(net, cred);
	अगर (error)
		जाओ out_destroy;
	error = nn->nfsd_serv->sv_ops->svo_setup(nn->nfsd_serv,
			शून्य, nrservs);
	अगर (error)
		जाओ out_shutकरोwn;
	/* We are holding a reference to nn->nfsd_serv which
	 * we करोn't want to count in the वापस value,
	 * so subtract 1
	 */
	error = nn->nfsd_serv->sv_nrthपढ़ोs - 1;
out_shutकरोwn:
	अगर (error < 0 && !nfsd_up_beक्रमe)
		nfsd_shutकरोwn_net(net);
out_destroy:
	nfsd_destroy(net);		/* Release server */
out:
	mutex_unlock(&nfsd_mutex);
	वापस error;
पूर्ण

#अगर defined(CONFIG_NFSD_V2_ACL) || defined(CONFIG_NFSD_V3_ACL)
अटल bool
nfsd_support_acl_version(पूर्णांक vers)
अणु
	अगर (vers >= NFSD_ACL_MINVERS && vers < NFSD_ACL_NRVERS)
		वापस nfsd_acl_version[vers] != शून्य;
	वापस false;
पूर्ण

अटल पूर्णांक
nfsd_acl_rpcbind_set(काष्ठा net *net, स्थिर काष्ठा svc_program *progp,
		     u32 version, पूर्णांक family, अचिन्हित लघु proto,
		     अचिन्हित लघु port)
अणु
	अगर (!nfsd_support_acl_version(version) ||
	    !nfsd_vers(net_generic(net, nfsd_net_id), version, NFSD_TEST))
		वापस 0;
	वापस svc_generic_rpcbind_set(net, progp, version, family,
			proto, port);
पूर्ण

अटल __be32
nfsd_acl_init_request(काष्ठा svc_rqst *rqstp,
		      स्थिर काष्ठा svc_program *progp,
		      काष्ठा svc_process_info *ret)
अणु
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	पूर्णांक i;

	अगर (likely(nfsd_support_acl_version(rqstp->rq_vers) &&
	    nfsd_vers(nn, rqstp->rq_vers, NFSD_TEST)))
		वापस svc_generic_init_request(rqstp, progp, ret);

	ret->mismatch.lovers = NFSD_ACL_NRVERS;
	क्रम (i = NFSD_ACL_MINVERS; i < NFSD_ACL_NRVERS; i++) अणु
		अगर (nfsd_support_acl_version(rqstp->rq_vers) &&
		    nfsd_vers(nn, i, NFSD_TEST)) अणु
			ret->mismatch.lovers = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret->mismatch.lovers == NFSD_ACL_NRVERS)
		वापस rpc_prog_unavail;
	ret->mismatch.hivers = NFSD_ACL_MINVERS;
	क्रम (i = NFSD_ACL_NRVERS - 1; i >= NFSD_ACL_MINVERS; i--) अणु
		अगर (nfsd_support_acl_version(rqstp->rq_vers) &&
		    nfsd_vers(nn, i, NFSD_TEST)) अणु
			ret->mismatch.hivers = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rpc_prog_mismatch;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
nfsd_rpcbind_set(काष्ठा net *net, स्थिर काष्ठा svc_program *progp,
		 u32 version, पूर्णांक family, अचिन्हित लघु proto,
		 अचिन्हित लघु port)
अणु
	अगर (!nfsd_vers(net_generic(net, nfsd_net_id), version, NFSD_TEST))
		वापस 0;
	वापस svc_generic_rpcbind_set(net, progp, version, family,
			proto, port);
पूर्ण

अटल __be32
nfsd_init_request(काष्ठा svc_rqst *rqstp,
		  स्थिर काष्ठा svc_program *progp,
		  काष्ठा svc_process_info *ret)
अणु
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	पूर्णांक i;

	अगर (likely(nfsd_vers(nn, rqstp->rq_vers, NFSD_TEST)))
		वापस svc_generic_init_request(rqstp, progp, ret);

	ret->mismatch.lovers = NFSD_NRVERS;
	क्रम (i = NFSD_MINVERS; i < NFSD_NRVERS; i++) अणु
		अगर (nfsd_vers(nn, i, NFSD_TEST)) अणु
			ret->mismatch.lovers = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret->mismatch.lovers == NFSD_NRVERS)
		वापस rpc_prog_unavail;
	ret->mismatch.hivers = NFSD_MINVERS;
	क्रम (i = NFSD_NRVERS - 1; i >= NFSD_MINVERS; i--) अणु
		अगर (nfsd_vers(nn, i, NFSD_TEST)) अणु
			ret->mismatch.hivers = i;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rpc_prog_mismatch;
पूर्ण

/*
 * This is the NFS server kernel thपढ़ो
 */
अटल पूर्णांक
nfsd(व्योम *vrqstp)
अणु
	काष्ठा svc_rqst *rqstp = (काष्ठा svc_rqst *) vrqstp;
	काष्ठा svc_xprt *perm_sock = list_entry(rqstp->rq_server->sv_permsocks.next, typeof(काष्ठा svc_xprt), xpt_list);
	काष्ठा net *net = perm_sock->xpt_net;
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);
	पूर्णांक err;

	/* Lock module and set up kernel thपढ़ो */
	mutex_lock(&nfsd_mutex);

	/* At this poपूर्णांक, the thपढ़ो shares current->fs
	 * with the init process. We need to create files with the
	 * umask as defined by the client instead of init's umask. */
	अगर (unshare_fs_काष्ठा() < 0) अणु
		prपूर्णांकk("Unable to start nfsd thread: out of memory\n");
		जाओ out;
	पूर्ण

	current->fs->umask = 0;

	/*
	 * thपढ़ो is spawned with all संकेतs set to संक_छोड़ो, re-enable
	 * the ones that will bring करोwn the thपढ़ो
	 */
	allow_संकेत(SIGKILL);
	allow_संकेत(SIGHUP);
	allow_संकेत(संक_विघ्न);
	allow_संकेत(SIGQUIT);

	nfsdstats.th_cnt++;
	mutex_unlock(&nfsd_mutex);

	set_मुक्तzable();

	/*
	 * The मुख्य request loop
	 */
	क्रम (;;) अणु
		/* Update sv_maxconn अगर it has changed */
		rqstp->rq_server->sv_maxconn = nn->max_connections;

		/*
		 * Find a socket with data available and call its
		 * recvfrom routine.
		 */
		जबतक ((err = svc_recv(rqstp, 60*60*HZ)) == -EAGAIN)
			;
		अगर (err == -EINTR)
			अवरोध;
		validate_process_creds();
		svc_process(rqstp);
		validate_process_creds();
	पूर्ण

	/* Clear संकेतs beक्रमe calling svc_निकास_thपढ़ो() */
	flush_संकेतs(current);

	mutex_lock(&nfsd_mutex);
	nfsdstats.th_cnt --;

out:
	rqstp->rq_server = शून्य;

	/* Release the thपढ़ो */
	svc_निकास_thपढ़ो(rqstp);

	nfsd_destroy(net);

	/* Release module */
	mutex_unlock(&nfsd_mutex);
	module_put_and_निकास(0);
	वापस 0;
पूर्ण

/**
 * nfsd_dispatch - Process an NFS or NFSACL Request
 * @rqstp: incoming request
 * @statp: poपूर्णांकer to location of accept_stat field in RPC Reply buffer
 *
 * This RPC dispatcher पूर्णांकegrates the NFS server's duplicate reply cache.
 *
 * Return values:
 *  %0: Processing complete; करो not send a Reply
 *  %1: Processing complete; send Reply in rqstp->rq_res
 */
पूर्णांक nfsd_dispatch(काष्ठा svc_rqst *rqstp, __be32 *statp)
अणु
	स्थिर काष्ठा svc_procedure *proc = rqstp->rq_procinfo;
	काष्ठा kvec *argv = &rqstp->rq_arg.head[0];
	काष्ठा kvec *resv = &rqstp->rq_res.head[0];
	__be32 *p;

	/*
	 * Give the xdr decoder a chance to change this अगर it wants
	 * (necessary in the NFSv4.0 compound हाल)
	 */
	rqstp->rq_cachetype = proc->pc_cachetype;

	svcxdr_init_decode(rqstp);
	अगर (!proc->pc_decode(rqstp, argv->iov_base))
		जाओ out_decode_err;

	चयन (nfsd_cache_lookup(rqstp)) अणु
	हाल RC_DOIT:
		अवरोध;
	हाल RC_REPLY:
		जाओ out_cached_reply;
	हाल RC_DROPIT:
		जाओ out_dropit;
	पूर्ण

	/*
	 * Need to grab the location to store the status, as
	 * NFSv4 करोes some encoding जबतक processing
	 */
	p = resv->iov_base + resv->iov_len;
	svcxdr_init_encode(rqstp);

	*statp = proc->pc_func(rqstp);
	अगर (*statp == rpc_drop_reply || test_bit(RQ_DROPME, &rqstp->rq_flags))
		जाओ out_update_drop;

	अगर (!proc->pc_encode(rqstp, p))
		जाओ out_encode_err;

	nfsd_cache_update(rqstp, rqstp->rq_cachetype, statp + 1);
out_cached_reply:
	वापस 1;

out_decode_err:
	trace_nfsd_garbage_args_err(rqstp);
	*statp = rpc_garbage_args;
	वापस 1;

out_update_drop:
	nfsd_cache_update(rqstp, RC_NOCACHE, शून्य);
out_dropit:
	वापस 0;

out_encode_err:
	trace_nfsd_cant_encode_err(rqstp);
	nfsd_cache_update(rqstp, RC_NOCACHE, शून्य);
	*statp = rpc_प्रणाली_err;
	वापस 1;
पूर्ण

/**
 * nfssvc_decode_व्योमarg - Decode व्योम arguments
 * @rqstp: Server RPC transaction context
 * @p: buffer containing arguments to decode
 *
 * Return values:
 *   %0: Arguments were not valid
 *   %1: Decoding was successful
 */
पूर्णांक nfssvc_decode_व्योमarg(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	वापस 1;
पूर्ण

/**
 * nfssvc_encode_व्योमres - Encode व्योम results
 * @rqstp: Server RPC transaction context
 * @p: buffer in which to encode results
 *
 * Return values:
 *   %0: Local error जबतक encoding
 *   %1: Encoding was successful
 */
पूर्णांक nfssvc_encode_व्योमres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	वापस 1;
पूर्ण

पूर्णांक nfsd_pool_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा nfsd_net *nn = net_generic(inode->i_sb->s_fs_info, nfsd_net_id);

	mutex_lock(&nfsd_mutex);
	अगर (nn->nfsd_serv == शून्य) अणु
		mutex_unlock(&nfsd_mutex);
		वापस -ENODEV;
	पूर्ण
	/* bump up the psuकरो refcount जबतक traversing */
	svc_get(nn->nfsd_serv);
	ret = svc_pool_stats_खोलो(nn->nfsd_serv, file);
	mutex_unlock(&nfsd_mutex);
	वापस ret;
पूर्ण

पूर्णांक nfsd_pool_stats_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = seq_release(inode, file);
	काष्ठा net *net = inode->i_sb->s_fs_info;

	mutex_lock(&nfsd_mutex);
	/* this function really, really should have been called svc_put() */
	nfsd_destroy(net);
	mutex_unlock(&nfsd_mutex);
	वापस ret;
पूर्ण
