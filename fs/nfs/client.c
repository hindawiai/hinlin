<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* client.c: NFS client sharing and management code
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */


#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/unistd.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/sunrpc/metrics.h>
#समावेश <linux/sunrpc/xprtsock.h>
#समावेश <linux/sunrpc/xprtrdma.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/nfs_mount.h>
#समावेश <linux/nfs4_mount.h>
#समावेश <linux/lockd/bind.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/mount.h>
#समावेश <linux/vfs.h>
#समावेश <linux/inet.h>
#समावेश <linux/in6.h>
#समावेश <linux/slab.h>
#समावेश <linux/idr.h>
#समावेश <net/ipv6.h>
#समावेश <linux/nfs_xdr.h>
#समावेश <linux/sunrpc/bc_xprt.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/pid_namespace.h>


#समावेश "nfs4_fs.h"
#समावेश "callback.h"
#समावेश "delegation.h"
#समावेश "iostat.h"
#समावेश "internal.h"
#समावेश "fscache.h"
#समावेश "pnfs.h"
#समावेश "nfs.h"
#समावेश "netns.h"
#समावेश "sysfs.h"
#समावेश "nfs42.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_CLIENT

अटल DECLARE_WAIT_QUEUE_HEAD(nfs_client_active_wq);
अटल DEFINE_SPINLOCK(nfs_version_lock);
अटल DEFINE_MUTEX(nfs_version_mutex);
अटल LIST_HEAD(nfs_versions);

/*
 * RPC cruft क्रम NFS
 */
अटल स्थिर काष्ठा rpc_version *nfs_version[5] = अणु
	[2] = शून्य,
	[3] = शून्य,
	[4] = शून्य,
पूर्ण;

स्थिर काष्ठा rpc_program nfs_program = अणु
	.name			= "nfs",
	.number			= NFS_PROGRAM,
	.nrvers			= ARRAY_SIZE(nfs_version),
	.version		= nfs_version,
	.stats			= &nfs_rpcstat,
	.pipe_dir_name		= NFS_PIPE_सूचीNAME,
पूर्ण;

काष्ठा rpc_stat nfs_rpcstat = अणु
	.program		= &nfs_program
पूर्ण;

अटल काष्ठा nfs_subversion *find_nfs_version(अचिन्हित पूर्णांक version)
अणु
	काष्ठा nfs_subversion *nfs;
	spin_lock(&nfs_version_lock);

	list_क्रम_each_entry(nfs, &nfs_versions, list) अणु
		अगर (nfs->rpc_ops->version == version) अणु
			spin_unlock(&nfs_version_lock);
			वापस nfs;
		पूर्ण
	पूर्ण

	spin_unlock(&nfs_version_lock);
	वापस ERR_PTR(-EPROTONOSUPPORT);
पूर्ण

काष्ठा nfs_subversion *get_nfs_version(अचिन्हित पूर्णांक version)
अणु
	काष्ठा nfs_subversion *nfs = find_nfs_version(version);

	अगर (IS_ERR(nfs)) अणु
		mutex_lock(&nfs_version_mutex);
		request_module("nfsv%d", version);
		nfs = find_nfs_version(version);
		mutex_unlock(&nfs_version_mutex);
	पूर्ण

	अगर (!IS_ERR(nfs) && !try_module_get(nfs->owner))
		वापस ERR_PTR(-EAGAIN);
	वापस nfs;
पूर्ण

व्योम put_nfs_version(काष्ठा nfs_subversion *nfs)
अणु
	module_put(nfs->owner);
पूर्ण

व्योम रेजिस्टर_nfs_version(काष्ठा nfs_subversion *nfs)
अणु
	spin_lock(&nfs_version_lock);

	list_add(&nfs->list, &nfs_versions);
	nfs_version[nfs->rpc_ops->version] = nfs->rpc_vers;

	spin_unlock(&nfs_version_lock);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_nfs_version);

व्योम unरेजिस्टर_nfs_version(काष्ठा nfs_subversion *nfs)
अणु
	spin_lock(&nfs_version_lock);

	nfs_version[nfs->rpc_ops->version] = शून्य;
	list_del(&nfs->list);

	spin_unlock(&nfs_version_lock);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_nfs_version);

/*
 * Allocate a shared client record
 *
 * Since these are allocated/deallocated very rarely, we करोn't
 * bother putting them in a slab cache...
 */
काष्ठा nfs_client *nfs_alloc_client(स्थिर काष्ठा nfs_client_initdata *cl_init)
अणु
	काष्ठा nfs_client *clp;
	पूर्णांक err = -ENOMEM;

	अगर ((clp = kzalloc(माप(*clp), GFP_KERNEL)) == शून्य)
		जाओ error_0;

	clp->cl_minorversion = cl_init->minorversion;
	clp->cl_nfs_mod = cl_init->nfs_mod;
	अगर (!try_module_get(clp->cl_nfs_mod->owner))
		जाओ error_dealloc;

	clp->rpc_ops = clp->cl_nfs_mod->rpc_ops;

	refcount_set(&clp->cl_count, 1);
	clp->cl_cons_state = NFS_CS_INITING;

	स_नकल(&clp->cl_addr, cl_init->addr, cl_init->addrlen);
	clp->cl_addrlen = cl_init->addrlen;

	अगर (cl_init->hostname) अणु
		err = -ENOMEM;
		clp->cl_hostname = kstrdup(cl_init->hostname, GFP_KERNEL);
		अगर (!clp->cl_hostname)
			जाओ error_cleanup;
	पूर्ण

	INIT_LIST_HEAD(&clp->cl_superblocks);
	clp->cl_rpcclient = ERR_PTR(-EINVAL);

	clp->cl_proto = cl_init->proto;
	clp->cl_nconnect = cl_init->nconnect;
	clp->cl_net = get_net(cl_init->net);

	clp->cl_principal = "*";
	nfs_fscache_get_client_cookie(clp);

	वापस clp;

error_cleanup:
	put_nfs_version(clp->cl_nfs_mod);
error_dealloc:
	kमुक्त(clp);
error_0:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_alloc_client);

#अगर IS_ENABLED(CONFIG_NFS_V4)
अटल व्योम nfs_cleanup_cb_ident_idr(काष्ठा net *net)
अणु
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	idr_destroy(&nn->cb_ident_idr);
पूर्ण

/* nfs_client_lock held */
अटल व्योम nfs_cb_idr_हटाओ_locked(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);

	अगर (clp->cl_cb_ident)
		idr_हटाओ(&nn->cb_ident_idr, clp->cl_cb_ident);
पूर्ण

अटल व्योम pnfs_init_server(काष्ठा nfs_server *server)
अणु
	rpc_init_रुको_queue(&server->roc_rpcरुकोq, "pNFS ROC");
पूर्ण

#अन्यथा
अटल व्योम nfs_cleanup_cb_ident_idr(काष्ठा net *net)
अणु
पूर्ण

अटल व्योम nfs_cb_idr_हटाओ_locked(काष्ठा nfs_client *clp)
अणु
पूर्ण

अटल व्योम pnfs_init_server(काष्ठा nfs_server *server)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_NFS_V4 */

/*
 * Destroy a shared client record
 */
व्योम nfs_मुक्त_client(काष्ठा nfs_client *clp)
अणु
	nfs_fscache_release_client_cookie(clp);

	/* -EIO all pending I/O */
	अगर (!IS_ERR(clp->cl_rpcclient))
		rpc_shutकरोwn_client(clp->cl_rpcclient);

	put_net(clp->cl_net);
	put_nfs_version(clp->cl_nfs_mod);
	kमुक्त(clp->cl_hostname);
	kमुक्त(clp->cl_acceptor);
	kमुक्त(clp);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_मुक्त_client);

/*
 * Release a reference to a shared client record
 */
व्योम nfs_put_client(काष्ठा nfs_client *clp)
अणु
	काष्ठा nfs_net *nn;

	अगर (!clp)
		वापस;

	nn = net_generic(clp->cl_net, nfs_net_id);

	अगर (refcount_dec_and_lock(&clp->cl_count, &nn->nfs_client_lock)) अणु
		list_del(&clp->cl_share_link);
		nfs_cb_idr_हटाओ_locked(clp);
		spin_unlock(&nn->nfs_client_lock);

		WARN_ON_ONCE(!list_empty(&clp->cl_superblocks));

		clp->rpc_ops->मुक्त_client(clp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nfs_put_client);

/*
 * Find an nfs_client on the list that matches the initialisation data
 * that is supplied.
 */
अटल काष्ठा nfs_client *nfs_match_client(स्थिर काष्ठा nfs_client_initdata *data)
अणु
	काष्ठा nfs_client *clp;
	स्थिर काष्ठा sockaddr *sap = data->addr;
	काष्ठा nfs_net *nn = net_generic(data->net, nfs_net_id);
	पूर्णांक error;

again:
	list_क्रम_each_entry(clp, &nn->nfs_client_list, cl_share_link) अणु
	        स्थिर काष्ठा sockaddr *clap = (काष्ठा sockaddr *)&clp->cl_addr;
		/* Don't match clients that failed to initialise properly */
		अगर (clp->cl_cons_state < 0)
			जारी;

		/* If a client is still initializing then we need to रुको */
		अगर (clp->cl_cons_state > NFS_CS_READY) अणु
			refcount_inc(&clp->cl_count);
			spin_unlock(&nn->nfs_client_lock);
			error = nfs_रुको_client_init_complete(clp);
			nfs_put_client(clp);
			spin_lock(&nn->nfs_client_lock);
			अगर (error < 0)
				वापस ERR_PTR(error);
			जाओ again;
		पूर्ण

		/* Dअगरferent NFS versions cannot share the same nfs_client */
		अगर (clp->rpc_ops != data->nfs_mod->rpc_ops)
			जारी;

		अगर (clp->cl_proto != data->proto)
			जारी;
		/* Match nfsv4 minorversion */
		अगर (clp->cl_minorversion != data->minorversion)
			जारी;

		/* Match request क्रम a dedicated DS */
		अगर (test_bit(NFS_CS_DS, &data->init_flags) !=
		    test_bit(NFS_CS_DS, &clp->cl_flags))
			जारी;

		/* Match the full socket address */
		अगर (!rpc_cmp_addr_port(sap, clap))
			/* Match all xprt_चयन full socket addresses */
			अगर (IS_ERR(clp->cl_rpcclient) ||
                            !rpc_clnt_xprt_चयन_has_addr(clp->cl_rpcclient,
							   sap))
				जारी;

		refcount_inc(&clp->cl_count);
		वापस clp;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Return true अगर @clp is करोne initializing, false अगर still working on it.
 *
 * Use nfs_client_init_status to check अगर it was successful.
 */
bool nfs_client_init_is_complete(स्थिर काष्ठा nfs_client *clp)
अणु
	वापस clp->cl_cons_state <= NFS_CS_READY;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_client_init_is_complete);

/*
 * Return 0 अगर @clp was successfully initialized, -त्रुटि_सं otherwise.
 *
 * This must be called *after* nfs_client_init_is_complete() वापसs true,
 * otherwise it will pop WARN_ON_ONCE and वापस -EINVAL
 */
पूर्णांक nfs_client_init_status(स्थिर काष्ठा nfs_client *clp)
अणु
	/* called without checking nfs_client_init_is_complete */
	अगर (clp->cl_cons_state > NFS_CS_READY) अणु
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण
	वापस clp->cl_cons_state;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_client_init_status);

पूर्णांक nfs_रुको_client_init_complete(स्थिर काष्ठा nfs_client *clp)
अणु
	वापस रुको_event_समाप्तable(nfs_client_active_wq,
			nfs_client_init_is_complete(clp));
पूर्ण
EXPORT_SYMBOL_GPL(nfs_रुको_client_init_complete);

/*
 * Found an existing client.  Make sure it's पढ़ोy beक्रमe वापसing.
 */
अटल काष्ठा nfs_client *
nfs_found_client(स्थिर काष्ठा nfs_client_initdata *cl_init,
		 काष्ठा nfs_client *clp)
अणु
	पूर्णांक error;

	error = nfs_रुको_client_init_complete(clp);
	अगर (error < 0) अणु
		nfs_put_client(clp);
		वापस ERR_PTR(-ERESTARTSYS);
	पूर्ण

	अगर (clp->cl_cons_state < NFS_CS_READY) अणु
		error = clp->cl_cons_state;
		nfs_put_client(clp);
		वापस ERR_PTR(error);
	पूर्ण

	smp_rmb();
	वापस clp;
पूर्ण

/*
 * Look up a client by IP address and protocol version
 * - creates a new record अगर one करोesn't yet exist
 */
काष्ठा nfs_client *nfs_get_client(स्थिर काष्ठा nfs_client_initdata *cl_init)
अणु
	काष्ठा nfs_client *clp, *new = शून्य;
	काष्ठा nfs_net *nn = net_generic(cl_init->net, nfs_net_id);
	स्थिर काष्ठा nfs_rpc_ops *rpc_ops = cl_init->nfs_mod->rpc_ops;

	अगर (cl_init->hostname == शून्य) अणु
		WARN_ON(1);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* see अगर the client alपढ़ोy exists */
	करो अणु
		spin_lock(&nn->nfs_client_lock);

		clp = nfs_match_client(cl_init);
		अगर (clp) अणु
			spin_unlock(&nn->nfs_client_lock);
			अगर (new)
				new->rpc_ops->मुक्त_client(new);
			अगर (IS_ERR(clp))
				वापस clp;
			वापस nfs_found_client(cl_init, clp);
		पूर्ण
		अगर (new) अणु
			list_add_tail(&new->cl_share_link,
					&nn->nfs_client_list);
			spin_unlock(&nn->nfs_client_lock);
			new->cl_flags = cl_init->init_flags;
			वापस rpc_ops->init_client(new, cl_init);
		पूर्ण

		spin_unlock(&nn->nfs_client_lock);

		new = rpc_ops->alloc_client(cl_init);
	पूर्ण जबतक (!IS_ERR(new));

	वापस new;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_get_client);

/*
 * Mark a server as पढ़ोy or failed
 */
व्योम nfs_mark_client_पढ़ोy(काष्ठा nfs_client *clp, पूर्णांक state)
अणु
	smp_wmb();
	clp->cl_cons_state = state;
	wake_up_all(&nfs_client_active_wq);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_mark_client_पढ़ोy);

/*
 * Initialise the समयout values क्रम a connection
 */
व्योम nfs_init_समयout_values(काष्ठा rpc_समयout *to, पूर्णांक proto,
				    पूर्णांक समयo, पूर्णांक retrans)
अणु
	to->to_initval = समयo * HZ / 10;
	to->to_retries = retrans;

	चयन (proto) अणु
	हाल XPRT_TRANSPORT_TCP:
	हाल XPRT_TRANSPORT_RDMA:
		अगर (retrans == NFS_UNSPEC_RETRANS)
			to->to_retries = NFS_DEF_TCP_RETRANS;
		अगर (समयo == NFS_UNSPEC_TIMEO || to->to_initval == 0)
			to->to_initval = NFS_DEF_TCP_TIMEO * HZ / 10;
		अगर (to->to_initval > NFS_MAX_TCP_TIMEOUT)
			to->to_initval = NFS_MAX_TCP_TIMEOUT;
		to->to_increment = to->to_initval;
		to->to_maxval = to->to_initval + (to->to_increment * to->to_retries);
		अगर (to->to_maxval > NFS_MAX_TCP_TIMEOUT)
			to->to_maxval = NFS_MAX_TCP_TIMEOUT;
		अगर (to->to_maxval < to->to_initval)
			to->to_maxval = to->to_initval;
		to->to_exponential = 0;
		अवरोध;
	हाल XPRT_TRANSPORT_UDP:
		अगर (retrans == NFS_UNSPEC_RETRANS)
			to->to_retries = NFS_DEF_UDP_RETRANS;
		अगर (समयo == NFS_UNSPEC_TIMEO || to->to_initval == 0)
			to->to_initval = NFS_DEF_UDP_TIMEO * HZ / 10;
		अगर (to->to_initval > NFS_MAX_UDP_TIMEOUT)
			to->to_initval = NFS_MAX_UDP_TIMEOUT;
		to->to_maxval = NFS_MAX_UDP_TIMEOUT;
		to->to_exponential = 1;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(nfs_init_समयout_values);

/*
 * Create an RPC client handle
 */
पूर्णांक nfs_create_rpc_client(काष्ठा nfs_client *clp,
			  स्थिर काष्ठा nfs_client_initdata *cl_init,
			  rpc_authflavor_t flavor)
अणु
	काष्ठा rpc_clnt		*clnt = शून्य;
	काष्ठा rpc_create_args args = अणु
		.net		= clp->cl_net,
		.protocol	= clp->cl_proto,
		.nconnect	= clp->cl_nconnect,
		.address	= (काष्ठा sockaddr *)&clp->cl_addr,
		.addrsize	= clp->cl_addrlen,
		.समयout	= cl_init->समयparms,
		.servername	= clp->cl_hostname,
		.nodename	= cl_init->nodename,
		.program	= &nfs_program,
		.version	= clp->rpc_ops->version,
		.authflavor	= flavor,
		.cred		= cl_init->cred,
	पूर्ण;

	अगर (test_bit(NFS_CS_DISCRTRY, &clp->cl_flags))
		args.flags |= RPC_CLNT_CREATE_DISCRTRY;
	अगर (test_bit(NFS_CS_NO_RETRANS_TIMEOUT, &clp->cl_flags))
		args.flags |= RPC_CLNT_CREATE_NO_RETRANS_TIMEOUT;
	अगर (test_bit(NFS_CS_NORESVPORT, &clp->cl_flags))
		args.flags |= RPC_CLNT_CREATE_NONPRIVPORT;
	अगर (test_bit(NFS_CS_INFINITE_SLOTS, &clp->cl_flags))
		args.flags |= RPC_CLNT_CREATE_INFINITE_SLOTS;
	अगर (test_bit(NFS_CS_NOPING, &clp->cl_flags))
		args.flags |= RPC_CLNT_CREATE_NOPING;
	अगर (test_bit(NFS_CS_REUSEPORT, &clp->cl_flags))
		args.flags |= RPC_CLNT_CREATE_REUSEPORT;

	अगर (!IS_ERR(clp->cl_rpcclient))
		वापस 0;

	clnt = rpc_create(&args);
	अगर (IS_ERR(clnt)) अणु
		dprपूर्णांकk("%s: cannot create RPC client. Error = %ld\n",
				__func__, PTR_ERR(clnt));
		वापस PTR_ERR(clnt);
	पूर्ण

	clnt->cl_principal = clp->cl_principal;
	clp->cl_rpcclient = clnt;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_create_rpc_client);

/*
 * Version 2 or 3 client deकाष्ठाion
 */
अटल व्योम nfs_destroy_server(काष्ठा nfs_server *server)
अणु
	अगर (server->nlm_host)
		nlmclnt_करोne(server->nlm_host);
पूर्ण

/*
 * Version 2 or 3 lockd setup
 */
अटल पूर्णांक nfs_start_lockd(काष्ठा nfs_server *server)
अणु
	काष्ठा nlm_host *host;
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nlmclnt_initdata nlm_init = अणु
		.hostname	= clp->cl_hostname,
		.address	= (काष्ठा sockaddr *)&clp->cl_addr,
		.addrlen	= clp->cl_addrlen,
		.nfs_version	= clp->rpc_ops->version,
		.noresvport	= server->flags & NFS_MOUNT_NORESVPORT ?
					1 : 0,
		.net		= clp->cl_net,
		.nlmclnt_ops 	= clp->cl_nfs_mod->rpc_ops->nlmclnt_ops,
		.cred		= server->cred,
	पूर्ण;

	अगर (nlm_init.nfs_version > 3)
		वापस 0;
	अगर ((server->flags & NFS_MOUNT_LOCAL_FLOCK) &&
			(server->flags & NFS_MOUNT_LOCAL_FCNTL))
		वापस 0;

	चयन (clp->cl_proto) अणु
		शेष:
			nlm_init.protocol = IPPROTO_TCP;
			अवरोध;
#अगर_अघोषित CONFIG_NFS_DISABLE_UDP_SUPPORT
		हाल XPRT_TRANSPORT_UDP:
			nlm_init.protocol = IPPROTO_UDP;
#पूर्ण_अगर
	पूर्ण

	host = nlmclnt_init(&nlm_init);
	अगर (IS_ERR(host))
		वापस PTR_ERR(host);

	server->nlm_host = host;
	server->destroy = nfs_destroy_server;
	वापस 0;
पूर्ण

/*
 * Create a general RPC client
 */
पूर्णांक nfs_init_server_rpcclient(काष्ठा nfs_server *server,
		स्थिर काष्ठा rpc_समयout *समयo,
		rpc_authflavor_t pseuकरोflavour)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;

	server->client = rpc_clone_client_set_auth(clp->cl_rpcclient,
							pseuकरोflavour);
	अगर (IS_ERR(server->client)) अणु
		dprपूर्णांकk("%s: couldn't create rpc_client!\n", __func__);
		वापस PTR_ERR(server->client);
	पूर्ण

	स_नकल(&server->client->cl_समयout_शेष,
			समयo,
			माप(server->client->cl_समयout_शेष));
	server->client->cl_समयout = &server->client->cl_समयout_शेष;
	server->client->cl_softrtry = 0;
	अगर (server->flags & NFS_MOUNT_SOFTERR)
		server->client->cl_softerr = 1;
	अगर (server->flags & NFS_MOUNT_SOFT)
		server->client->cl_softrtry = 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_init_server_rpcclient);

/**
 * nfs_init_client - Initialise an NFS2 or NFS3 client
 *
 * @clp: nfs_client to initialise
 * @cl_init: Initialisation parameters
 *
 * Returns poपूर्णांकer to an NFS client, or an ERR_PTR value.
 */
काष्ठा nfs_client *nfs_init_client(काष्ठा nfs_client *clp,
				   स्थिर काष्ठा nfs_client_initdata *cl_init)
अणु
	पूर्णांक error;

	/* the client is alपढ़ोy initialised */
	अगर (clp->cl_cons_state == NFS_CS_READY)
		वापस clp;

	/*
	 * Create a client RPC handle क्रम करोing FSSTAT with UNIX auth only
	 * - RFC 2623, sec 2.3.2
	 */
	error = nfs_create_rpc_client(clp, cl_init, RPC_AUTH_UNIX);
	nfs_mark_client_पढ़ोy(clp, error == 0 ? NFS_CS_READY : error);
	अगर (error < 0) अणु
		nfs_put_client(clp);
		clp = ERR_PTR(error);
	पूर्ण
	वापस clp;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_init_client);

/*
 * Create a version 2 or 3 client
 */
अटल पूर्णांक nfs_init_server(काष्ठा nfs_server *server,
			   स्थिर काष्ठा fs_context *fc)
अणु
	स्थिर काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा rpc_समयout समयparms;
	काष्ठा nfs_client_initdata cl_init = अणु
		.hostname = ctx->nfs_server.hostname,
		.addr = (स्थिर काष्ठा sockaddr *)&ctx->nfs_server.address,
		.addrlen = ctx->nfs_server.addrlen,
		.nfs_mod = ctx->nfs_mod,
		.proto = ctx->nfs_server.protocol,
		.net = fc->net_ns,
		.समयparms = &समयparms,
		.cred = server->cred,
		.nconnect = ctx->nfs_server.nconnect,
		.init_flags = (1UL << NFS_CS_REUSEPORT),
	पूर्ण;
	काष्ठा nfs_client *clp;
	पूर्णांक error;

	nfs_init_समयout_values(&समयparms, ctx->nfs_server.protocol,
				ctx->समयo, ctx->retrans);
	अगर (ctx->flags & NFS_MOUNT_NORESVPORT)
		set_bit(NFS_CS_NORESVPORT, &cl_init.init_flags);

	/* Allocate or find a client reference we can use */
	clp = nfs_get_client(&cl_init);
	अगर (IS_ERR(clp))
		वापस PTR_ERR(clp);

	server->nfs_client = clp;

	/* Initialise the client representation from the mount data */
	server->flags = ctx->flags;
	server->options = ctx->options;
	server->caps |= NFS_CAP_HARDLINKS | NFS_CAP_SYMLINKS;

	चयन (clp->rpc_ops->version) अणु
	हाल 2:
		server->fattr_valid = NFS_ATTR_FATTR_V2;
		अवरोध;
	हाल 3:
		server->fattr_valid = NFS_ATTR_FATTR_V3;
		अवरोध;
	शेष:
		server->fattr_valid = NFS_ATTR_FATTR_V4;
	पूर्ण

	अगर (ctx->rsize)
		server->rsize = nfs_block_size(ctx->rsize, शून्य);
	अगर (ctx->wsize)
		server->wsize = nfs_block_size(ctx->wsize, शून्य);

	server->acregmin = ctx->acregmin * HZ;
	server->acregmax = ctx->acregmax * HZ;
	server->acdirmin = ctx->acdirmin * HZ;
	server->acdirmax = ctx->acdirmax * HZ;

	/* Start lockd here, beक्रमe we might error out */
	error = nfs_start_lockd(server);
	अगर (error < 0)
		जाओ error;

	server->port = ctx->nfs_server.port;
	server->auth_info = ctx->auth_info;

	error = nfs_init_server_rpcclient(server, &समयparms,
					  ctx->selected_flavor);
	अगर (error < 0)
		जाओ error;

	/* Preserve the values of mount_server-related mount options */
	अगर (ctx->mount_server.addrlen) अणु
		स_नकल(&server->mountd_address, &ctx->mount_server.address,
			ctx->mount_server.addrlen);
		server->mountd_addrlen = ctx->mount_server.addrlen;
	पूर्ण
	server->mountd_version = ctx->mount_server.version;
	server->mountd_port = ctx->mount_server.port;
	server->mountd_protocol = ctx->mount_server.protocol;

	server->namelen  = ctx->namlen;
	वापस 0;

error:
	server->nfs_client = शून्य;
	nfs_put_client(clp);
	वापस error;
पूर्ण

/*
 * Load up the server record from inक्रमmation gained in an fsinfo record
 */
अटल व्योम nfs_server_set_fsinfo(काष्ठा nfs_server *server,
				  काष्ठा nfs_fsinfo *fsinfo)
अणु
	अचिन्हित दीर्घ max_rpc_payload, raw_max_rpc_payload;

	/* Work out a lot of parameters */
	अगर (server->rsize == 0)
		server->rsize = nfs_block_size(fsinfo->rtpref, शून्य);
	अगर (server->wsize == 0)
		server->wsize = nfs_block_size(fsinfo->wtpref, शून्य);

	अगर (fsinfo->rपंचांगax >= 512 && server->rsize > fsinfo->rपंचांगax)
		server->rsize = nfs_block_size(fsinfo->rपंचांगax, शून्य);
	अगर (fsinfo->wपंचांगax >= 512 && server->wsize > fsinfo->wपंचांगax)
		server->wsize = nfs_block_size(fsinfo->wपंचांगax, शून्य);

	raw_max_rpc_payload = rpc_max_payload(server->client);
	max_rpc_payload = nfs_block_size(raw_max_rpc_payload, शून्य);

	अगर (server->rsize > max_rpc_payload)
		server->rsize = max_rpc_payload;
	अगर (server->rsize > NFS_MAX_खाता_IO_SIZE)
		server->rsize = NFS_MAX_खाता_IO_SIZE;
	server->rpages = (server->rsize + PAGE_SIZE - 1) >> PAGE_SHIFT;

	अगर (server->wsize > max_rpc_payload)
		server->wsize = max_rpc_payload;
	अगर (server->wsize > NFS_MAX_खाता_IO_SIZE)
		server->wsize = NFS_MAX_खाता_IO_SIZE;
	server->wpages = (server->wsize + PAGE_SIZE - 1) >> PAGE_SHIFT;

	server->wपंचांगult = nfs_block_bits(fsinfo->wपंचांगult, शून्य);

	server->dtsize = nfs_block_size(fsinfo->dtpref, शून्य);
	अगर (server->dtsize > NFS_MAX_खाता_IO_SIZE)
		server->dtsize = NFS_MAX_खाता_IO_SIZE;
	अगर (server->dtsize > server->rsize)
		server->dtsize = server->rsize;

	अगर (server->flags & NFS_MOUNT_NOAC) अणु
		server->acregmin = server->acregmax = 0;
		server->acdirmin = server->acdirmax = 0;
	पूर्ण

	server->maxfilesize = fsinfo->maxfilesize;

	server->समय_delta = fsinfo->समय_delta;
	server->change_attr_type = fsinfo->change_attr_type;

	server->clone_blksize = fsinfo->clone_blksize;
	/* We're airborne Set socket buffersize */
	rpc_रखो_बफsize(server->client, server->wsize + 100, server->rsize + 100);

#अगर_घोषित CONFIG_NFS_V4_2
	/*
	 * Defaults until limited by the session parameters.
	 */
	server->gxasize = min_t(अचिन्हित पूर्णांक, raw_max_rpc_payload,
				XATTR_SIZE_MAX);
	server->sxasize = min_t(अचिन्हित पूर्णांक, raw_max_rpc_payload,
				XATTR_SIZE_MAX);
	server->lxasize = min_t(अचिन्हित पूर्णांक, raw_max_rpc_payload,
				nfs42_listxattr_xdrsize(XATTR_LIST_MAX));

	अगर (fsinfo->xattr_support)
		server->caps |= NFS_CAP_XATTR;
#पूर्ण_अगर
पूर्ण

/*
 * Probe fileप्रणाली inक्रमmation, including the FSID on v2/v3
 */
पूर्णांक nfs_probe_fsinfo(काष्ठा nfs_server *server, काष्ठा nfs_fh *mntfh, काष्ठा nfs_fattr *fattr)
अणु
	काष्ठा nfs_fsinfo fsinfo;
	काष्ठा nfs_client *clp = server->nfs_client;
	पूर्णांक error;

	अगर (clp->rpc_ops->set_capabilities != शून्य) अणु
		error = clp->rpc_ops->set_capabilities(server, mntfh);
		अगर (error < 0)
			वापस error;
	पूर्ण

	fsinfo.fattr = fattr;
	fsinfo.nlayouttypes = 0;
	स_रखो(fsinfo.layouttype, 0, माप(fsinfo.layouttype));
	error = clp->rpc_ops->fsinfo(server, mntfh, &fsinfo);
	अगर (error < 0)
		वापस error;

	nfs_server_set_fsinfo(server, &fsinfo);

	/* Get some general file प्रणाली info */
	अगर (server->namelen == 0) अणु
		काष्ठा nfs_pathconf pathinfo;

		pathinfo.fattr = fattr;
		nfs_fattr_init(fattr);

		अगर (clp->rpc_ops->pathconf(server, mntfh, &pathinfo) >= 0)
			server->namelen = pathinfo.max_namelen;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_probe_fsinfo);

/*
 * Copy useful inक्रमmation when duplicating a server record
 */
व्योम nfs_server_copy_userdata(काष्ठा nfs_server *target, काष्ठा nfs_server *source)
अणु
	target->flags = source->flags;
	target->rsize = source->rsize;
	target->wsize = source->wsize;
	target->acregmin = source->acregmin;
	target->acregmax = source->acregmax;
	target->acdirmin = source->acdirmin;
	target->acdirmax = source->acdirmax;
	target->caps = source->caps;
	target->options = source->options;
	target->auth_info = source->auth_info;
	target->port = source->port;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_server_copy_userdata);

व्योम nfs_server_insert_lists(काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);

	spin_lock(&nn->nfs_client_lock);
	list_add_tail_rcu(&server->client_link, &clp->cl_superblocks);
	list_add_tail(&server->master_link, &nn->nfs_volume_list);
	clear_bit(NFS_CS_STOP_RENEW, &clp->cl_res_state);
	spin_unlock(&nn->nfs_client_lock);

पूर्ण
EXPORT_SYMBOL_GPL(nfs_server_insert_lists);

व्योम nfs_server_हटाओ_lists(काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_client *clp = server->nfs_client;
	काष्ठा nfs_net *nn;

	अगर (clp == शून्य)
		वापस;
	nn = net_generic(clp->cl_net, nfs_net_id);
	spin_lock(&nn->nfs_client_lock);
	list_del_rcu(&server->client_link);
	अगर (list_empty(&clp->cl_superblocks))
		set_bit(NFS_CS_STOP_RENEW, &clp->cl_res_state);
	list_del(&server->master_link);
	spin_unlock(&nn->nfs_client_lock);

	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(nfs_server_हटाओ_lists);

/*
 * Allocate and initialise a server record
 */
काष्ठा nfs_server *nfs_alloc_server(व्योम)
अणु
	काष्ठा nfs_server *server;

	server = kzalloc(माप(काष्ठा nfs_server), GFP_KERNEL);
	अगर (!server)
		वापस शून्य;

	server->client = server->client_acl = ERR_PTR(-EINVAL);

	/* Zero out the NFS state stuff */
	INIT_LIST_HEAD(&server->client_link);
	INIT_LIST_HEAD(&server->master_link);
	INIT_LIST_HEAD(&server->delegations);
	INIT_LIST_HEAD(&server->layouts);
	INIT_LIST_HEAD(&server->state_owners_lru);
	INIT_LIST_HEAD(&server->ss_copies);

	atomic_set(&server->active, 0);

	server->io_stats = nfs_alloc_iostats();
	अगर (!server->io_stats) अणु
		kमुक्त(server);
		वापस शून्य;
	पूर्ण

	server->change_attr_type = NFS4_CHANGE_TYPE_IS_UNDEFINED;

	ida_init(&server->खोलोowner_id);
	ida_init(&server->lockowner_id);
	pnfs_init_server(server);
	rpc_init_रुको_queue(&server->uoc_rpcरुकोq, "NFS UOC");

	वापस server;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_alloc_server);

/*
 * Free up a server record
 */
व्योम nfs_मुक्त_server(काष्ठा nfs_server *server)
अणु
	nfs_server_हटाओ_lists(server);

	अगर (server->destroy != शून्य)
		server->destroy(server);

	अगर (!IS_ERR(server->client_acl))
		rpc_shutकरोwn_client(server->client_acl);
	अगर (!IS_ERR(server->client))
		rpc_shutकरोwn_client(server->client);

	nfs_put_client(server->nfs_client);

	ida_destroy(&server->lockowner_id);
	ida_destroy(&server->खोलोowner_id);
	nfs_मुक्त_iostats(server->io_stats);
	put_cred(server->cred);
	kमुक्त(server);
	nfs_release_स्वतःmount_समयr();
पूर्ण
EXPORT_SYMBOL_GPL(nfs_मुक्त_server);

/*
 * Create a version 2 or 3 volume record
 * - keyed on server and FSID
 */
काष्ठा nfs_server *nfs_create_server(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा nfs_server *server;
	काष्ठा nfs_fattr *fattr;
	पूर्णांक error;

	server = nfs_alloc_server();
	अगर (!server)
		वापस ERR_PTR(-ENOMEM);

	server->cred = get_cred(fc->cred);

	error = -ENOMEM;
	fattr = nfs_alloc_fattr();
	अगर (fattr == शून्य)
		जाओ error;

	/* Get a client representation */
	error = nfs_init_server(server, fc);
	अगर (error < 0)
		जाओ error;

	/* Probe the root fh to retrieve its FSID */
	error = nfs_probe_fsinfo(server, ctx->mntfh, fattr);
	अगर (error < 0)
		जाओ error;
	अगर (server->nfs_client->rpc_ops->version == 3) अणु
		अगर (server->namelen == 0 || server->namelen > NFS3_MAXNAMLEN)
			server->namelen = NFS3_MAXNAMLEN;
		अगर (!(ctx->flags & NFS_MOUNT_NORसूचीPLUS))
			server->caps |= NFS_CAP_READसूचीPLUS;
	पूर्ण अन्यथा अणु
		अगर (server->namelen == 0 || server->namelen > NFS2_MAXNAMLEN)
			server->namelen = NFS2_MAXNAMLEN;
	पूर्ण

	अगर (!(fattr->valid & NFS_ATTR_FATTR)) अणु
		error = ctx->nfs_mod->rpc_ops->getattr(server, ctx->mntfh,
						       fattr, शून्य, शून्य);
		अगर (error < 0) अणु
			dprपूर्णांकk("nfs_create_server: getattr error = %d\n", -error);
			जाओ error;
		पूर्ण
	पूर्ण
	स_नकल(&server->fsid, &fattr->fsid, माप(server->fsid));

	dprपूर्णांकk("Server FSID: %llx:%llx\n",
		(अचिन्हित दीर्घ दीर्घ) server->fsid.major,
		(अचिन्हित दीर्घ दीर्घ) server->fsid.minor);

	nfs_server_insert_lists(server);
	server->mount_समय = jअगरfies;
	nfs_मुक्त_fattr(fattr);
	वापस server;

error:
	nfs_मुक्त_fattr(fattr);
	nfs_मुक्त_server(server);
	वापस ERR_PTR(error);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_create_server);

/*
 * Clone an NFS2, NFS3 or NFS4 server record
 */
काष्ठा nfs_server *nfs_clone_server(काष्ठा nfs_server *source,
				    काष्ठा nfs_fh *fh,
				    काष्ठा nfs_fattr *fattr,
				    rpc_authflavor_t flavor)
अणु
	काष्ठा nfs_server *server;
	काष्ठा nfs_fattr *fattr_fsinfo;
	पूर्णांक error;

	server = nfs_alloc_server();
	अगर (!server)
		वापस ERR_PTR(-ENOMEM);

	server->cred = get_cred(source->cred);

	error = -ENOMEM;
	fattr_fsinfo = nfs_alloc_fattr();
	अगर (fattr_fsinfo == शून्य)
		जाओ out_मुक्त_server;

	/* Copy data from the source */
	server->nfs_client = source->nfs_client;
	server->destroy = source->destroy;
	refcount_inc(&server->nfs_client->cl_count);
	nfs_server_copy_userdata(server, source);

	server->fsid = fattr->fsid;

	error = nfs_init_server_rpcclient(server,
			source->client->cl_समयout,
			flavor);
	अगर (error < 0)
		जाओ out_मुक्त_server;

	/* probe the fileप्रणाली info क्रम this server fileप्रणाली */
	error = nfs_probe_fsinfo(server, fh, fattr_fsinfo);
	अगर (error < 0)
		जाओ out_मुक्त_server;

	अगर (server->namelen == 0 || server->namelen > NFS4_MAXNAMLEN)
		server->namelen = NFS4_MAXNAMLEN;

	error = nfs_start_lockd(server);
	अगर (error < 0)
		जाओ out_मुक्त_server;

	nfs_server_insert_lists(server);
	server->mount_समय = jअगरfies;

	nfs_मुक्त_fattr(fattr_fsinfo);
	वापस server;

out_मुक्त_server:
	nfs_मुक्त_fattr(fattr_fsinfo);
	nfs_मुक्त_server(server);
	वापस ERR_PTR(error);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_clone_server);

व्योम nfs_clients_init(काष्ठा net *net)
अणु
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	INIT_LIST_HEAD(&nn->nfs_client_list);
	INIT_LIST_HEAD(&nn->nfs_volume_list);
#अगर IS_ENABLED(CONFIG_NFS_V4)
	idr_init(&nn->cb_ident_idr);
#पूर्ण_अगर
	spin_lock_init(&nn->nfs_client_lock);
	nn->boot_समय = kसमय_get_real();

	nfs_netns_sysfs_setup(nn, net);
पूर्ण

व्योम nfs_clients_निकास(काष्ठा net *net)
अणु
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	nfs_netns_sysfs_destroy(nn);
	nfs_cleanup_cb_ident_idr(net);
	WARN_ON_ONCE(!list_empty(&nn->nfs_client_list));
	WARN_ON_ONCE(!list_empty(&nn->nfs_volume_list));
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल व्योम *nfs_server_list_start(काष्ठा seq_file *p, loff_t *pos);
अटल व्योम *nfs_server_list_next(काष्ठा seq_file *p, व्योम *v, loff_t *pos);
अटल व्योम nfs_server_list_stop(काष्ठा seq_file *p, व्योम *v);
अटल पूर्णांक nfs_server_list_show(काष्ठा seq_file *m, व्योम *v);

अटल स्थिर काष्ठा seq_operations nfs_server_list_ops = अणु
	.start	= nfs_server_list_start,
	.next	= nfs_server_list_next,
	.stop	= nfs_server_list_stop,
	.show	= nfs_server_list_show,
पूर्ण;

अटल व्योम *nfs_volume_list_start(काष्ठा seq_file *p, loff_t *pos);
अटल व्योम *nfs_volume_list_next(काष्ठा seq_file *p, व्योम *v, loff_t *pos);
अटल व्योम nfs_volume_list_stop(काष्ठा seq_file *p, व्योम *v);
अटल पूर्णांक nfs_volume_list_show(काष्ठा seq_file *m, व्योम *v);

अटल स्थिर काष्ठा seq_operations nfs_volume_list_ops = अणु
	.start	= nfs_volume_list_start,
	.next	= nfs_volume_list_next,
	.stop	= nfs_volume_list_stop,
	.show	= nfs_volume_list_show,
पूर्ण;

/*
 * set up the iterator to start पढ़ोing from the server list and वापस the first item
 */
अटल व्योम *nfs_server_list_start(काष्ठा seq_file *m, loff_t *_pos)
				__acquires(&nn->nfs_client_lock)
अणु
	काष्ठा nfs_net *nn = net_generic(seq_file_net(m), nfs_net_id);

	/* lock the list against modअगरication */
	spin_lock(&nn->nfs_client_lock);
	वापस seq_list_start_head(&nn->nfs_client_list, *_pos);
पूर्ण

/*
 * move to next server
 */
अटल व्योम *nfs_server_list_next(काष्ठा seq_file *p, व्योम *v, loff_t *pos)
अणु
	काष्ठा nfs_net *nn = net_generic(seq_file_net(p), nfs_net_id);

	वापस seq_list_next(v, &nn->nfs_client_list, pos);
पूर्ण

/*
 * clean up after पढ़ोing from the transports list
 */
अटल व्योम nfs_server_list_stop(काष्ठा seq_file *p, व्योम *v)
				__releases(&nn->nfs_client_lock)
अणु
	काष्ठा nfs_net *nn = net_generic(seq_file_net(p), nfs_net_id);

	spin_unlock(&nn->nfs_client_lock);
पूर्ण

/*
 * display a header line followed by a load of call lines
 */
अटल पूर्णांक nfs_server_list_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा nfs_client *clp;
	काष्ठा nfs_net *nn = net_generic(seq_file_net(m), nfs_net_id);

	/* display header on line 1 */
	अगर (v == &nn->nfs_client_list) अणु
		seq_माला_दो(m, "NV SERVER   PORT USE HOSTNAME\n");
		वापस 0;
	पूर्ण

	/* display one transport per line on subsequent lines */
	clp = list_entry(v, काष्ठा nfs_client, cl_share_link);

	/* Check अगर the client is initialized */
	अगर (clp->cl_cons_state != NFS_CS_READY)
		वापस 0;

	rcu_पढ़ो_lock();
	seq_म_लिखो(m, "v%u %s %s %3d %s\n",
		   clp->rpc_ops->version,
		   rpc_peeraddr2str(clp->cl_rpcclient, RPC_DISPLAY_HEX_ADDR),
		   rpc_peeraddr2str(clp->cl_rpcclient, RPC_DISPLAY_HEX_PORT),
		   refcount_पढ़ो(&clp->cl_count),
		   clp->cl_hostname);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

/*
 * set up the iterator to start पढ़ोing from the volume list and वापस the first item
 */
अटल व्योम *nfs_volume_list_start(काष्ठा seq_file *m, loff_t *_pos)
				__acquires(&nn->nfs_client_lock)
अणु
	काष्ठा nfs_net *nn = net_generic(seq_file_net(m), nfs_net_id);

	/* lock the list against modअगरication */
	spin_lock(&nn->nfs_client_lock);
	वापस seq_list_start_head(&nn->nfs_volume_list, *_pos);
पूर्ण

/*
 * move to next volume
 */
अटल व्योम *nfs_volume_list_next(काष्ठा seq_file *p, व्योम *v, loff_t *pos)
अणु
	काष्ठा nfs_net *nn = net_generic(seq_file_net(p), nfs_net_id);

	वापस seq_list_next(v, &nn->nfs_volume_list, pos);
पूर्ण

/*
 * clean up after पढ़ोing from the transports list
 */
अटल व्योम nfs_volume_list_stop(काष्ठा seq_file *p, व्योम *v)
				__releases(&nn->nfs_client_lock)
अणु
	काष्ठा nfs_net *nn = net_generic(seq_file_net(p), nfs_net_id);

	spin_unlock(&nn->nfs_client_lock);
पूर्ण

/*
 * display a header line followed by a load of call lines
 */
अटल पूर्णांक nfs_volume_list_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा nfs_server *server;
	काष्ठा nfs_client *clp;
	अक्षर dev[13];	// 8 क्रम 2^24, 1 क्रम ':', 3 for 2^8, 1 for '\0'
	अक्षर fsid[34];	// 2 * 16 क्रम %llx, 1 क्रम ':', 1 for '\0'
	काष्ठा nfs_net *nn = net_generic(seq_file_net(m), nfs_net_id);

	/* display header on line 1 */
	अगर (v == &nn->nfs_volume_list) अणु
		seq_माला_दो(m, "NV SERVER   PORT DEV          FSID"
			    "                              FSC\n");
		वापस 0;
	पूर्ण
	/* display one transport per line on subsequent lines */
	server = list_entry(v, काष्ठा nfs_server, master_link);
	clp = server->nfs_client;

	snम_लिखो(dev, माप(dev), "%u:%u",
		 MAJOR(server->s_dev), MINOR(server->s_dev));

	snम_लिखो(fsid, माप(fsid), "%llx:%llx",
		 (अचिन्हित दीर्घ दीर्घ) server->fsid.major,
		 (अचिन्हित दीर्घ दीर्घ) server->fsid.minor);

	rcu_पढ़ो_lock();
	seq_म_लिखो(m, "v%u %s %s %-12s %-33s %s\n",
		   clp->rpc_ops->version,
		   rpc_peeraddr2str(clp->cl_rpcclient, RPC_DISPLAY_HEX_ADDR),
		   rpc_peeraddr2str(clp->cl_rpcclient, RPC_DISPLAY_HEX_PORT),
		   dev,
		   fsid,
		   nfs_server_fscache_state(server));
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

पूर्णांक nfs_fs_proc_net_init(काष्ठा net *net)
अणु
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);
	काष्ठा proc_dir_entry *p;

	nn->proc_nfsfs = proc_net_सूची_गढ़ो(net, "nfsfs", net->proc_net);
	अगर (!nn->proc_nfsfs)
		जाओ error_0;

	/* a file of servers with which we're dealing */
	p = proc_create_net("servers", S_IFREG|S_IRUGO, nn->proc_nfsfs,
			&nfs_server_list_ops, माप(काष्ठा seq_net_निजी));
	अगर (!p)
		जाओ error_1;

	/* a file of volumes that we have mounted */
	p = proc_create_net("volumes", S_IFREG|S_IRUGO, nn->proc_nfsfs,
			&nfs_volume_list_ops, माप(काष्ठा seq_net_निजी));
	अगर (!p)
		जाओ error_1;
	वापस 0;

error_1:
	हटाओ_proc_subtree("nfsfs", net->proc_net);
error_0:
	वापस -ENOMEM;
पूर्ण

व्योम nfs_fs_proc_net_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_subtree("nfsfs", net->proc_net);
पूर्ण

/*
 * initialise the /proc/fs/nfsfs/ directory
 */
पूर्णांक __init nfs_fs_proc_init(व्योम)
अणु
	अगर (!proc_सूची_गढ़ो("fs/nfsfs", शून्य))
		जाओ error_0;

	/* a file of servers with which we're dealing */
	अगर (!proc_symlink("fs/nfsfs/servers", शून्य, "../../net/nfsfs/servers"))
		जाओ error_1;

	/* a file of volumes that we have mounted */
	अगर (!proc_symlink("fs/nfsfs/volumes", शून्य, "../../net/nfsfs/volumes"))
		जाओ error_1;

	वापस 0;
error_1:
	हटाओ_proc_subtree("fs/nfsfs", शून्य);
error_0:
	वापस -ENOMEM;
पूर्ण

/*
 * clean up the /proc/fs/nfsfs/ directory
 */
व्योम nfs_fs_proc_निकास(व्योम)
अणु
	हटाओ_proc_subtree("fs/nfsfs", शून्य);
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_FS */
