<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/callback.c
 *
 * Copyright (C) 2004 Trond Myklebust
 *
 * NFSv4 callback handling
 */

#समावेश <linux/completion.h>
#समावेश <linux/ip.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sunrpc/svcauth_gss.h>
#समावेश <linux/sunrpc/bc_xprt.h>

#समावेश <net/inet_sock.h>

#समावेश "nfs4_fs.h"
#समावेश "callback.h"
#समावेश "internal.h"
#समावेश "netns.h"

#घोषणा NFSDBG_FACILITY NFSDBG_CALLBACK

काष्ठा nfs_callback_data अणु
	अचिन्हित पूर्णांक users;
	काष्ठा svc_serv *serv;
पूर्ण;

अटल काष्ठा nfs_callback_data nfs_callback_info[NFS4_MAX_MINOR_VERSION + 1];
अटल DEFINE_MUTEX(nfs_callback_mutex);
अटल काष्ठा svc_program nfs4_callback_program;

अटल पूर्णांक nfs4_callback_up_net(काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	पूर्णांक ret;
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	ret = svc_create_xprt(serv, "tcp", net, PF_INET,
				nfs_callback_set_tcpport, SVC_SOCK_ANONYMOUS,
				cred);
	अगर (ret <= 0)
		जाओ out_err;
	nn->nfs_callback_tcpport = ret;
	dprपूर्णांकk("NFS: Callback listener port = %u (af %u, net %x)\n",
		nn->nfs_callback_tcpport, PF_INET, net->ns.inum);

	ret = svc_create_xprt(serv, "tcp", net, PF_INET6,
				nfs_callback_set_tcpport, SVC_SOCK_ANONYMOUS,
				cred);
	अगर (ret > 0) अणु
		nn->nfs_callback_tcpport6 = ret;
		dprपूर्णांकk("NFS: Callback listener port = %u (af %u, net %x)\n",
			nn->nfs_callback_tcpport6, PF_INET6, net->ns.inum);
	पूर्ण अन्यथा अगर (ret != -EAFNOSUPPORT)
		जाओ out_err;
	वापस 0;

out_err:
	वापस (ret) ? ret : -ENOMEM;
पूर्ण

/*
 * This is the NFSv4 callback kernel thपढ़ो.
 */
अटल पूर्णांक
nfs4_callback_svc(व्योम *vrqstp)
अणु
	पूर्णांक err;
	काष्ठा svc_rqst *rqstp = vrqstp;

	set_मुक्तzable();

	जबतक (!kthपढ़ो_मुक्तzable_should_stop(शून्य)) अणु

		अगर (संकेत_pending(current))
			flush_संकेतs(current);
		/*
		 * Listen क्रम a request on the socket
		 */
		err = svc_recv(rqstp, MAX_SCHEDULE_TIMEOUT);
		अगर (err == -EAGAIN || err == -EINTR)
			जारी;
		svc_process(rqstp);
	पूर्ण
	svc_निकास_thपढ़ो(rqstp);
	module_put_and_निकास(0);
	वापस 0;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
/*
 * The callback service क्रम NFSv4.1 callbacks
 */
अटल पूर्णांक
nfs41_callback_svc(व्योम *vrqstp)
अणु
	काष्ठा svc_rqst *rqstp = vrqstp;
	काष्ठा svc_serv *serv = rqstp->rq_server;
	काष्ठा rpc_rqst *req;
	पूर्णांक error;
	DEFINE_WAIT(wq);

	set_मुक्तzable();

	जबतक (!kthपढ़ो_मुक्तzable_should_stop(शून्य)) अणु

		अगर (संकेत_pending(current))
			flush_संकेतs(current);

		prepare_to_रुको(&serv->sv_cb_रुकोq, &wq, TASK_INTERRUPTIBLE);
		spin_lock_bh(&serv->sv_cb_lock);
		अगर (!list_empty(&serv->sv_cb_list)) अणु
			req = list_first_entry(&serv->sv_cb_list,
					काष्ठा rpc_rqst, rq_bc_list);
			list_del(&req->rq_bc_list);
			spin_unlock_bh(&serv->sv_cb_lock);
			finish_रुको(&serv->sv_cb_रुकोq, &wq);
			dprपूर्णांकk("Invoking bc_svc_process()\n");
			error = bc_svc_process(serv, req, rqstp);
			dprपूर्णांकk("bc_svc_process() returned w/ error code= %d\n",
				error);
		पूर्ण अन्यथा अणु
			spin_unlock_bh(&serv->sv_cb_lock);
			अगर (!kthपढ़ो_should_stop())
				schedule();
			finish_रुको(&serv->sv_cb_रुकोq, &wq);
		पूर्ण
	पूर्ण
	svc_निकास_thपढ़ो(rqstp);
	module_put_and_निकास(0);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nfs_callback_bc_serv(u32 minorversion, काष्ठा rpc_xprt *xprt,
		काष्ठा svc_serv *serv)
अणु
	अगर (minorversion)
		/*
		 * Save the svc_serv in the transport so that it can
		 * be referenced when the session backchannel is initialized
		 */
		xprt->bc_serv = serv;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम nfs_callback_bc_serv(u32 minorversion, काष्ठा rpc_xprt *xprt,
		काष्ठा svc_serv *serv)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

अटल पूर्णांक nfs_callback_start_svc(पूर्णांक minorversion, काष्ठा rpc_xprt *xprt,
				  काष्ठा svc_serv *serv)
अणु
	पूर्णांक nrservs = nfs_callback_nr_thपढ़ोs;
	पूर्णांक ret;

	nfs_callback_bc_serv(minorversion, xprt, serv);

	अगर (nrservs < NFS4_MIN_NR_CALLBACK_THREADS)
		nrservs = NFS4_MIN_NR_CALLBACK_THREADS;

	अगर (serv->sv_nrthपढ़ोs-1 == nrservs)
		वापस 0;

	ret = serv->sv_ops->svo_setup(serv, शून्य, nrservs);
	अगर (ret) अणु
		serv->sv_ops->svo_setup(serv, शून्य, 0);
		वापस ret;
	पूर्ण
	dprपूर्णांकk("nfs_callback_up: service started\n");
	वापस 0;
पूर्ण

अटल व्योम nfs_callback_करोwn_net(u32 minorversion, काष्ठा svc_serv *serv, काष्ठा net *net)
अणु
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	अगर (--nn->cb_users[minorversion])
		वापस;

	dprपूर्णांकk("NFS: destroy per-net callback data; net=%x\n", net->ns.inum);
	svc_shutकरोwn_net(serv, net);
पूर्ण

अटल पूर्णांक nfs_callback_up_net(पूर्णांक minorversion, काष्ठा svc_serv *serv,
			       काष्ठा net *net, काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);
	पूर्णांक ret;

	अगर (nn->cb_users[minorversion]++)
		वापस 0;

	dprपूर्णांकk("NFS: create per-net callback data; net=%x\n", net->ns.inum);

	ret = svc_bind(serv, net);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING "NFS: bind callback service failed\n");
		जाओ err_bind;
	पूर्ण

	ret = 0;
	अगर (!IS_ENABLED(CONFIG_NFS_V4_1) || minorversion == 0)
		ret = nfs4_callback_up_net(serv, net);
	अन्यथा अगर (xprt->ops->bc_setup)
		set_bc_enabled(serv);
	अन्यथा
		ret = -EPROTONOSUPPORT;

	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "NFS: callback service start failed\n");
		जाओ err_socks;
	पूर्ण
	वापस 0;

err_socks:
	svc_rpcb_cleanup(serv, net);
err_bind:
	nn->cb_users[minorversion]--;
	dprपूर्णांकk("NFS: Couldn't create callback socket: err = %d; "
			"net = %x\n", ret, net->ns.inum);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा svc_serv_ops nfs40_cb_sv_ops = अणु
	.svo_function		= nfs4_callback_svc,
	.svo_enqueue_xprt	= svc_xprt_करो_enqueue,
	.svo_setup		= svc_set_num_thपढ़ोs_sync,
	.svo_module		= THIS_MODULE,
पूर्ण;
#अगर defined(CONFIG_NFS_V4_1)
अटल स्थिर काष्ठा svc_serv_ops nfs41_cb_sv_ops = अणु
	.svo_function		= nfs41_callback_svc,
	.svo_enqueue_xprt	= svc_xprt_करो_enqueue,
	.svo_setup		= svc_set_num_thपढ़ोs_sync,
	.svo_module		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा svc_serv_ops *nfs4_cb_sv_ops[] = अणु
	[0] = &nfs40_cb_sv_ops,
	[1] = &nfs41_cb_sv_ops,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा svc_serv_ops *nfs4_cb_sv_ops[] = अणु
	[0] = &nfs40_cb_sv_ops,
	[1] = शून्य,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा svc_serv *nfs_callback_create_svc(पूर्णांक minorversion)
अणु
	काष्ठा nfs_callback_data *cb_info = &nfs_callback_info[minorversion];
	स्थिर काष्ठा svc_serv_ops *sv_ops;
	काष्ठा svc_serv *serv;

	/*
	 * Check whether we're alपढ़ोy up and running.
	 */
	अगर (cb_info->serv) अणु
		/*
		 * Note: increase service usage, because later in हाल of error
		 * svc_destroy() will be called.
		 */
		svc_get(cb_info->serv);
		वापस cb_info->serv;
	पूर्ण

	चयन (minorversion) अणु
	हाल 0:
		sv_ops = nfs4_cb_sv_ops[0];
		अवरोध;
	शेष:
		sv_ops = nfs4_cb_sv_ops[1];
	पूर्ण

	अगर (sv_ops == शून्य)
		वापस ERR_PTR(-ENOTSUPP);

	/*
	 * Sanity check: अगर there's no task,
	 * we should be the first user ...
	 */
	अगर (cb_info->users)
		prपूर्णांकk(KERN_WARNING "nfs_callback_create_svc: no kthread, %d users??\n",
			cb_info->users);

	serv = svc_create_pooled(&nfs4_callback_program, NFS4_CALLBACK_बफ_मानE, sv_ops);
	अगर (!serv) अणु
		prपूर्णांकk(KERN_ERR "nfs_callback_create_svc: create service failed\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	cb_info->serv = serv;
	/* As there is only one thपढ़ो we need to over-ride the
	 * शेष maximum of 80 connections
	 */
	serv->sv_maxconn = 1024;
	dprपूर्णांकk("nfs_callback_create_svc: service created\n");
	वापस serv;
पूर्ण

/*
 * Bring up the callback thपढ़ो अगर it is not alपढ़ोy up.
 */
पूर्णांक nfs_callback_up(u32 minorversion, काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा svc_serv *serv;
	काष्ठा nfs_callback_data *cb_info = &nfs_callback_info[minorversion];
	पूर्णांक ret;
	काष्ठा net *net = xprt->xprt_net;

	mutex_lock(&nfs_callback_mutex);

	serv = nfs_callback_create_svc(minorversion);
	अगर (IS_ERR(serv)) अणु
		ret = PTR_ERR(serv);
		जाओ err_create;
	पूर्ण

	ret = nfs_callback_up_net(minorversion, serv, net, xprt);
	अगर (ret < 0)
		जाओ err_net;

	ret = nfs_callback_start_svc(minorversion, xprt, serv);
	अगर (ret < 0)
		जाओ err_start;

	cb_info->users++;
	/*
	 * svc_create creates the svc_serv with sv_nrthपढ़ोs == 1, and then
	 * svc_prepare_thपढ़ो increments that. So we need to call svc_destroy
	 * on both success and failure so that the refcount is 1 when the
	 * thपढ़ो निकासs.
	 */
err_net:
	अगर (!cb_info->users)
		cb_info->serv = शून्य;
	svc_destroy(serv);
err_create:
	mutex_unlock(&nfs_callback_mutex);
	वापस ret;

err_start:
	nfs_callback_करोwn_net(minorversion, serv, net);
	dprपूर्णांकk("NFS: Couldn't create server thread; err = %d\n", ret);
	जाओ err_net;
पूर्ण

/*
 * Kill the callback thपढ़ो अगर it's no दीर्घer being used.
 */
व्योम nfs_callback_करोwn(पूर्णांक minorversion, काष्ठा net *net)
अणु
	काष्ठा nfs_callback_data *cb_info = &nfs_callback_info[minorversion];
	काष्ठा svc_serv *serv;

	mutex_lock(&nfs_callback_mutex);
	serv = cb_info->serv;
	nfs_callback_करोwn_net(minorversion, serv, net);
	cb_info->users--;
	अगर (cb_info->users == 0) अणु
		svc_get(serv);
		serv->sv_ops->svo_setup(serv, शून्य, 0);
		svc_destroy(serv);
		dprपूर्णांकk("nfs_callback_down: service destroyed\n");
		cb_info->serv = शून्य;
	पूर्ण
	mutex_unlock(&nfs_callback_mutex);
पूर्ण

/* Boolean check of RPC_AUTH_GSS principal */
पूर्णांक
check_gss_callback_principal(काष्ठा nfs_client *clp, काष्ठा svc_rqst *rqstp)
अणु
	अक्षर *p = rqstp->rq_cred.cr_principal;

	अगर (rqstp->rq_authop->flavour != RPC_AUTH_GSS)
		वापस 1;

	/* No RPC_AUTH_GSS on NFSv4.1 back channel yet */
	अगर (clp->cl_minorversion != 0)
		वापस 0;
	/*
	 * It might just be a normal user principal, in which हाल
	 * userspace won't bother to tell us the name at all.
	 */
	अगर (p == शून्य)
		वापस 0;

	/*
	 * Did we get the acceptor from userland during the SETCLIENID
	 * negotiation?
	 */
	अगर (clp->cl_acceptor)
		वापस !म_भेद(p, clp->cl_acceptor);

	/*
	 * Otherwise try to verअगरy it using the cl_hostname. Note that this
	 * करोesn't work अगर a non-canonical hostname was used in the devname.
	 */

	/* Expect a GSS_C_NT_HOSTBASED_NAME like "nfs@serverhostname" */

	अगर (स_भेद(p, "nfs@", 4) != 0)
		वापस 0;
	p += 4;
	अगर (म_भेद(p, clp->cl_hostname) != 0)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * pg_authenticate method क्रम nfsv4 callback thपढ़ोs.
 *
 * The authflavor has been negotiated, so an incorrect flavor is a server
 * bug. Deny packets with incorrect authflavor.
 *
 * All other checking करोne after NFS decoding where the nfs_client can be
 * found in nfs4_callback_compound
 */
अटल पूर्णांक nfs_callback_authenticate(काष्ठा svc_rqst *rqstp)
अणु
	चयन (rqstp->rq_authop->flavour) अणु
	हाल RPC_AUTH_शून्य:
		अगर (rqstp->rq_proc != CB_शून्य)
			वापस SVC_DENIED;
		अवरोध;
	हाल RPC_AUTH_GSS:
		/* No RPC_AUTH_GSS support yet in NFSv4.1 */
		 अगर (svc_is_backchannel(rqstp))
			वापस SVC_DENIED;
	पूर्ण
	वापस SVC_OK;
पूर्ण

/*
 * Define NFS4 callback program
 */
अटल स्थिर काष्ठा svc_version *nfs4_callback_version[] = अणु
	[1] = &nfs4_callback_version1,
	[4] = &nfs4_callback_version4,
पूर्ण;

अटल काष्ठा svc_stat nfs4_callback_stats;

अटल काष्ठा svc_program nfs4_callback_program = अणु
	.pg_prog = NFS4_CALLBACK,			/* RPC service number */
	.pg_nvers = ARRAY_SIZE(nfs4_callback_version),	/* Number of entries */
	.pg_vers = nfs4_callback_version,		/* version table */
	.pg_name = "NFSv4 callback",			/* service name */
	.pg_class = "nfs",				/* authentication class */
	.pg_stats = &nfs4_callback_stats,
	.pg_authenticate = nfs_callback_authenticate,
	.pg_init_request = svc_generic_init_request,
	.pg_rpcbind_set	= svc_generic_rpcbind_set,
पूर्ण;
