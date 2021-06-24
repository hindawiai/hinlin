<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/net/sunrpc/clnt.c
 *
 *  This file contains the high-level RPC पूर्णांकerface.
 *  It is modeled as a finite state machine to support both synchronous
 *  and asynchronous requests.
 *
 *  -	RPC header generation and argument serialization.
 *  -	Credential refresh.
 *  -	TCP connect handling.
 *  -	Retry of operation when it is suspected the operation failed because
 *	of uid squashing on the server, or when the credentials were stale
 *	and need to be refreshed, or when a packet was damaged in transit.
 *	This may be have to be moved to the VFS layer.
 *
 *  Copyright (C) 1992,1993 Rick Sladkey <jrs@world.std.com>
 *  Copyright (C) 1995,1996 Olaf Kirch <okir@monad.swb.de>
 */


#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/mm.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/slab.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/utsname.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/un.h>

#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <linux/sunrpc/metrics.h>
#समावेश <linux/sunrpc/bc_xprt.h>
#समावेश <trace/events/sunrpc.h>

#समावेश "sunrpc.h"
#समावेश "netns.h"

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_CALL
#पूर्ण_अगर

/*
 * All RPC clients are linked पूर्णांकo this list
 */

अटल DECLARE_WAIT_QUEUE_HEAD(destroy_रुको);


अटल व्योम	call_start(काष्ठा rpc_task *task);
अटल व्योम	call_reserve(काष्ठा rpc_task *task);
अटल व्योम	call_reserveresult(काष्ठा rpc_task *task);
अटल व्योम	call_allocate(काष्ठा rpc_task *task);
अटल व्योम	call_encode(काष्ठा rpc_task *task);
अटल व्योम	call_decode(काष्ठा rpc_task *task);
अटल व्योम	call_bind(काष्ठा rpc_task *task);
अटल व्योम	call_bind_status(काष्ठा rpc_task *task);
अटल व्योम	call_transmit(काष्ठा rpc_task *task);
अटल व्योम	call_status(काष्ठा rpc_task *task);
अटल व्योम	call_transmit_status(काष्ठा rpc_task *task);
अटल व्योम	call_refresh(काष्ठा rpc_task *task);
अटल व्योम	call_refreshresult(काष्ठा rpc_task *task);
अटल व्योम	call_connect(काष्ठा rpc_task *task);
अटल व्योम	call_connect_status(काष्ठा rpc_task *task);

अटल पूर्णांक	rpc_encode_header(काष्ठा rpc_task *task,
				  काष्ठा xdr_stream *xdr);
अटल पूर्णांक	rpc_decode_header(काष्ठा rpc_task *task,
				  काष्ठा xdr_stream *xdr);
अटल पूर्णांक	rpc_ping(काष्ठा rpc_clnt *clnt);
अटल व्योम	rpc_check_समयout(काष्ठा rpc_task *task);

अटल व्योम rpc_रेजिस्टर_client(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा net *net = rpc_net_ns(clnt);
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	spin_lock(&sn->rpc_client_lock);
	list_add(&clnt->cl_clients, &sn->all_clients);
	spin_unlock(&sn->rpc_client_lock);
पूर्ण

अटल व्योम rpc_unरेजिस्टर_client(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा net *net = rpc_net_ns(clnt);
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	spin_lock(&sn->rpc_client_lock);
	list_del(&clnt->cl_clients);
	spin_unlock(&sn->rpc_client_lock);
पूर्ण

अटल व्योम __rpc_clnt_हटाओ_pipedir(काष्ठा rpc_clnt *clnt)
अणु
	rpc_हटाओ_client_dir(clnt);
पूर्ण

अटल व्योम rpc_clnt_हटाओ_pipedir(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा net *net = rpc_net_ns(clnt);
	काष्ठा super_block *pipefs_sb;

	pipefs_sb = rpc_get_sb_net(net);
	अगर (pipefs_sb) अणु
		__rpc_clnt_हटाओ_pipedir(clnt);
		rpc_put_sb_net(net);
	पूर्ण
पूर्ण

अटल काष्ठा dentry *rpc_setup_pipedir_sb(काष्ठा super_block *sb,
				    काष्ठा rpc_clnt *clnt)
अणु
	अटल uपूर्णांक32_t clntid;
	स्थिर अक्षर *dir_name = clnt->cl_program->pipe_dir_name;
	अक्षर name[15];
	काष्ठा dentry *dir, *dentry;

	dir = rpc_d_lookup_sb(sb, dir_name);
	अगर (dir == शून्य) अणु
		pr_info("RPC: pipefs directory doesn't exist: %s\n", dir_name);
		वापस dir;
	पूर्ण
	क्रम (;;) अणु
		snम_लिखो(name, माप(name), "clnt%x", (अचिन्हित पूर्णांक)clntid++);
		name[माप(name) - 1] = '\0';
		dentry = rpc_create_client_dir(dir, name, clnt);
		अगर (!IS_ERR(dentry))
			अवरोध;
		अगर (dentry == ERR_PTR(-EEXIST))
			जारी;
		prपूर्णांकk(KERN_INFO "RPC: Couldn't create pipefs entry"
				" %s/%s, error %ld\n",
				dir_name, name, PTR_ERR(dentry));
		अवरोध;
	पूर्ण
	dput(dir);
	वापस dentry;
पूर्ण

अटल पूर्णांक
rpc_setup_pipedir(काष्ठा super_block *pipefs_sb, काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा dentry *dentry;

	अगर (clnt->cl_program->pipe_dir_name != शून्य) अणु
		dentry = rpc_setup_pipedir_sb(pipefs_sb, clnt);
		अगर (IS_ERR(dentry))
			वापस PTR_ERR(dentry);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rpc_clnt_skip_event(काष्ठा rpc_clnt *clnt, अचिन्हित दीर्घ event)
अणु
	अगर (clnt->cl_program->pipe_dir_name == शून्य)
		वापस 1;

	चयन (event) अणु
	हाल RPC_PIPEFS_MOUNT:
		अगर (clnt->cl_pipedir_objects.pdh_dentry != शून्य)
			वापस 1;
		अगर (atomic_पढ़ो(&clnt->cl_count) == 0)
			वापस 1;
		अवरोध;
	हाल RPC_PIPEFS_UMOUNT:
		अगर (clnt->cl_pipedir_objects.pdh_dentry == शून्य)
			वापस 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __rpc_clnt_handle_event(काष्ठा rpc_clnt *clnt, अचिन्हित दीर्घ event,
				   काष्ठा super_block *sb)
अणु
	काष्ठा dentry *dentry;

	चयन (event) अणु
	हाल RPC_PIPEFS_MOUNT:
		dentry = rpc_setup_pipedir_sb(sb, clnt);
		अगर (!dentry)
			वापस -ENOENT;
		अगर (IS_ERR(dentry))
			वापस PTR_ERR(dentry);
		अवरोध;
	हाल RPC_PIPEFS_UMOUNT:
		__rpc_clnt_हटाओ_pipedir(clnt);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "%s: unknown event: %ld\n", __func__, event);
		वापस -ENOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __rpc_pipefs_event(काष्ठा rpc_clnt *clnt, अचिन्हित दीर्घ event,
				काष्ठा super_block *sb)
अणु
	पूर्णांक error = 0;

	क्रम (;; clnt = clnt->cl_parent) अणु
		अगर (!rpc_clnt_skip_event(clnt, event))
			error = __rpc_clnt_handle_event(clnt, event, sb);
		अगर (error || clnt == clnt->cl_parent)
			अवरोध;
	पूर्ण
	वापस error;
पूर्ण

अटल काष्ठा rpc_clnt *rpc_get_client_क्रम_event(काष्ठा net *net, पूर्णांक event)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	काष्ठा rpc_clnt *clnt;

	spin_lock(&sn->rpc_client_lock);
	list_क्रम_each_entry(clnt, &sn->all_clients, cl_clients) अणु
		अगर (rpc_clnt_skip_event(clnt, event))
			जारी;
		spin_unlock(&sn->rpc_client_lock);
		वापस clnt;
	पूर्ण
	spin_unlock(&sn->rpc_client_lock);
	वापस शून्य;
पूर्ण

अटल पूर्णांक rpc_pipefs_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			    व्योम *ptr)
अणु
	काष्ठा super_block *sb = ptr;
	काष्ठा rpc_clnt *clnt;
	पूर्णांक error = 0;

	जबतक ((clnt = rpc_get_client_क्रम_event(sb->s_fs_info, event))) अणु
		error = __rpc_pipefs_event(clnt, event, sb);
		अगर (error)
			अवरोध;
	पूर्ण
	वापस error;
पूर्ण

अटल काष्ठा notअगरier_block rpc_clients_block = अणु
	.notअगरier_call	= rpc_pipefs_event,
	.priority	= SUNRPC_PIPEFS_RPC_PRIO,
पूर्ण;

पूर्णांक rpc_clients_notअगरier_रेजिस्टर(व्योम)
अणु
	वापस rpc_pipefs_notअगरier_रेजिस्टर(&rpc_clients_block);
पूर्ण

व्योम rpc_clients_notअगरier_unरेजिस्टर(व्योम)
अणु
	वापस rpc_pipefs_notअगरier_unरेजिस्टर(&rpc_clients_block);
पूर्ण

अटल काष्ठा rpc_xprt *rpc_clnt_set_transport(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt *xprt,
		स्थिर काष्ठा rpc_समयout *समयout)
अणु
	काष्ठा rpc_xprt *old;

	spin_lock(&clnt->cl_lock);
	old = rcu_dereference_रक्षित(clnt->cl_xprt,
			lockdep_is_held(&clnt->cl_lock));

	अगर (!xprt_bound(xprt))
		clnt->cl_स्वतःbind = 1;

	clnt->cl_समयout = समयout;
	rcu_assign_poपूर्णांकer(clnt->cl_xprt, xprt);
	spin_unlock(&clnt->cl_lock);

	वापस old;
पूर्ण

अटल व्योम rpc_clnt_set_nodename(काष्ठा rpc_clnt *clnt, स्थिर अक्षर *nodename)
अणु
	clnt->cl_nodelen = strlcpy(clnt->cl_nodename,
			nodename, माप(clnt->cl_nodename));
पूर्ण

अटल पूर्णांक rpc_client_रेजिस्टर(काष्ठा rpc_clnt *clnt,
			       rpc_authflavor_t pseuकरोflavor,
			       स्थिर अक्षर *client_name)
अणु
	काष्ठा rpc_auth_create_args auth_args = अणु
		.pseuकरोflavor = pseuकरोflavor,
		.target_name = client_name,
	पूर्ण;
	काष्ठा rpc_auth *auth;
	काष्ठा net *net = rpc_net_ns(clnt);
	काष्ठा super_block *pipefs_sb;
	पूर्णांक err;

	rpc_clnt_debugfs_रेजिस्टर(clnt);

	pipefs_sb = rpc_get_sb_net(net);
	अगर (pipefs_sb) अणु
		err = rpc_setup_pipedir(pipefs_sb, clnt);
		अगर (err)
			जाओ out;
	पूर्ण

	rpc_रेजिस्टर_client(clnt);
	अगर (pipefs_sb)
		rpc_put_sb_net(net);

	auth = rpcauth_create(&auth_args, clnt);
	अगर (IS_ERR(auth)) अणु
		dprपूर्णांकk("RPC:       Couldn't create auth handle (flavor %u)\n",
				pseuकरोflavor);
		err = PTR_ERR(auth);
		जाओ err_auth;
	पूर्ण
	वापस 0;
err_auth:
	pipefs_sb = rpc_get_sb_net(net);
	rpc_unरेजिस्टर_client(clnt);
	__rpc_clnt_हटाओ_pipedir(clnt);
out:
	अगर (pipefs_sb)
		rpc_put_sb_net(net);
	rpc_clnt_debugfs_unरेजिस्टर(clnt);
	वापस err;
पूर्ण

अटल DEFINE_IDA(rpc_clids);

व्योम rpc_cleanup_clids(व्योम)
अणु
	ida_destroy(&rpc_clids);
पूर्ण

अटल पूर्णांक rpc_alloc_clid(काष्ठा rpc_clnt *clnt)
अणु
	पूर्णांक clid;

	clid = ida_simple_get(&rpc_clids, 0, 0, GFP_KERNEL);
	अगर (clid < 0)
		वापस clid;
	clnt->cl_clid = clid;
	वापस 0;
पूर्ण

अटल व्योम rpc_मुक्त_clid(काष्ठा rpc_clnt *clnt)
अणु
	ida_simple_हटाओ(&rpc_clids, clnt->cl_clid);
पूर्ण

अटल काष्ठा rpc_clnt * rpc_new_client(स्थिर काष्ठा rpc_create_args *args,
		काष्ठा rpc_xprt_चयन *xps,
		काष्ठा rpc_xprt *xprt,
		काष्ठा rpc_clnt *parent)
अणु
	स्थिर काष्ठा rpc_program *program = args->program;
	स्थिर काष्ठा rpc_version *version;
	काष्ठा rpc_clnt *clnt = शून्य;
	स्थिर काष्ठा rpc_समयout *समयout;
	स्थिर अक्षर *nodename = args->nodename;
	पूर्णांक err;

	err = rpciod_up();
	अगर (err)
		जाओ out_no_rpciod;

	err = -EINVAL;
	अगर (args->version >= program->nrvers)
		जाओ out_err;
	version = program->version[args->version];
	अगर (version == शून्य)
		जाओ out_err;

	err = -ENOMEM;
	clnt = kzalloc(माप(*clnt), GFP_KERNEL);
	अगर (!clnt)
		जाओ out_err;
	clnt->cl_parent = parent ? : clnt;

	err = rpc_alloc_clid(clnt);
	अगर (err)
		जाओ out_no_clid;

	clnt->cl_cred	  = get_cred(args->cred);
	clnt->cl_procinfo = version->procs;
	clnt->cl_maxproc  = version->nrprocs;
	clnt->cl_prog     = args->prognumber ? : program->number;
	clnt->cl_vers     = version->number;
	clnt->cl_stats    = program->stats;
	clnt->cl_metrics  = rpc_alloc_iostats(clnt);
	rpc_init_pipe_dir_head(&clnt->cl_pipedir_objects);
	err = -ENOMEM;
	अगर (clnt->cl_metrics == शून्य)
		जाओ out_no_stats;
	clnt->cl_program  = program;
	INIT_LIST_HEAD(&clnt->cl_tasks);
	spin_lock_init(&clnt->cl_lock);

	समयout = xprt->समयout;
	अगर (args->समयout != शून्य) अणु
		स_नकल(&clnt->cl_समयout_शेष, args->समयout,
				माप(clnt->cl_समयout_शेष));
		समयout = &clnt->cl_समयout_शेष;
	पूर्ण

	rpc_clnt_set_transport(clnt, xprt, समयout);
	xprt_iter_init(&clnt->cl_xpi, xps);
	xprt_चयन_put(xps);

	clnt->cl_rtt = &clnt->cl_rtt_शेष;
	rpc_init_rtt(&clnt->cl_rtt_शेष, clnt->cl_समयout->to_initval);

	atomic_set(&clnt->cl_count, 1);

	अगर (nodename == शून्य)
		nodename = utsname()->nodename;
	/* save the nodename */
	rpc_clnt_set_nodename(clnt, nodename);

	err = rpc_client_रेजिस्टर(clnt, args->authflavor, args->client_name);
	अगर (err)
		जाओ out_no_path;
	अगर (parent)
		atomic_inc(&parent->cl_count);

	trace_rpc_clnt_new(clnt, xprt, program->name, args->servername);
	वापस clnt;

out_no_path:
	rpc_मुक्त_iostats(clnt->cl_metrics);
out_no_stats:
	put_cred(clnt->cl_cred);
	rpc_मुक्त_clid(clnt);
out_no_clid:
	kमुक्त(clnt);
out_err:
	rpciod_करोwn();
out_no_rpciod:
	xprt_चयन_put(xps);
	xprt_put(xprt);
	trace_rpc_clnt_new_err(program->name, args->servername, err);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा rpc_clnt *rpc_create_xprt(काष्ठा rpc_create_args *args,
					काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpc_clnt *clnt = शून्य;
	काष्ठा rpc_xprt_चयन *xps;

	अगर (args->bc_xprt && args->bc_xprt->xpt_bc_xps) अणु
		WARN_ON_ONCE(!(args->protocol & XPRT_TRANSPORT_BC));
		xps = args->bc_xprt->xpt_bc_xps;
		xprt_चयन_get(xps);
	पूर्ण अन्यथा अणु
		xps = xprt_चयन_alloc(xprt, GFP_KERNEL);
		अगर (xps == शून्य) अणु
			xprt_put(xprt);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण
		अगर (xprt->bc_xprt) अणु
			xprt_चयन_get(xps);
			xprt->bc_xprt->xpt_bc_xps = xps;
		पूर्ण
	पूर्ण
	clnt = rpc_new_client(args, xps, xprt, शून्य);
	अगर (IS_ERR(clnt))
		वापस clnt;

	अगर (!(args->flags & RPC_CLNT_CREATE_NOPING)) अणु
		पूर्णांक err = rpc_ping(clnt);
		अगर (err != 0) अणु
			rpc_shutकरोwn_client(clnt);
			वापस ERR_PTR(err);
		पूर्ण
	पूर्ण

	clnt->cl_softrtry = 1;
	अगर (args->flags & (RPC_CLNT_CREATE_HARDRTRY|RPC_CLNT_CREATE_SOFTERR)) अणु
		clnt->cl_softrtry = 0;
		अगर (args->flags & RPC_CLNT_CREATE_SOFTERR)
			clnt->cl_softerr = 1;
	पूर्ण

	अगर (args->flags & RPC_CLNT_CREATE_AUTOBIND)
		clnt->cl_स्वतःbind = 1;
	अगर (args->flags & RPC_CLNT_CREATE_NO_RETRANS_TIMEOUT)
		clnt->cl_noretransसमयo = 1;
	अगर (args->flags & RPC_CLNT_CREATE_DISCRTRY)
		clnt->cl_discrtry = 1;
	अगर (!(args->flags & RPC_CLNT_CREATE_QUIET))
		clnt->cl_chatty = 1;

	वापस clnt;
पूर्ण

/**
 * rpc_create - create an RPC client and transport with one call
 * @args: rpc_clnt create argument काष्ठाure
 *
 * Creates and initializes an RPC transport and an RPC client.
 *
 * It can ping the server in order to determine अगर it is up, and to see अगर
 * it supports this program and version.  RPC_CLNT_CREATE_NOPING disables
 * this behavior so asynchronous tasks can also use rpc_create.
 */
काष्ठा rpc_clnt *rpc_create(काष्ठा rpc_create_args *args)
अणु
	काष्ठा rpc_xprt *xprt;
	काष्ठा xprt_create xprtargs = अणु
		.net = args->net,
		.ident = args->protocol,
		.srcaddr = args->saddress,
		.dstaddr = args->address,
		.addrlen = args->addrsize,
		.servername = args->servername,
		.bc_xprt = args->bc_xprt,
	पूर्ण;
	अक्षर servername[48];
	काष्ठा rpc_clnt *clnt;
	पूर्णांक i;

	अगर (args->bc_xprt) अणु
		WARN_ON_ONCE(!(args->protocol & XPRT_TRANSPORT_BC));
		xprt = args->bc_xprt->xpt_bc_xprt;
		अगर (xprt) अणु
			xprt_get(xprt);
			वापस rpc_create_xprt(args, xprt);
		पूर्ण
	पूर्ण

	अगर (args->flags & RPC_CLNT_CREATE_INFINITE_SLOTS)
		xprtargs.flags |= XPRT_CREATE_INFINITE_SLOTS;
	अगर (args->flags & RPC_CLNT_CREATE_NO_IDLE_TIMEOUT)
		xprtargs.flags |= XPRT_CREATE_NO_IDLE_TIMEOUT;
	/*
	 * If the caller chooses not to specअगरy a hostname, whip
	 * up a string representation of the passed-in address.
	 */
	अगर (xprtargs.servername == शून्य) अणु
		काष्ठा sockaddr_un *sun =
				(काष्ठा sockaddr_un *)args->address;
		काष्ठा sockaddr_in *sin =
				(काष्ठा sockaddr_in *)args->address;
		काष्ठा sockaddr_in6 *sin6 =
				(काष्ठा sockaddr_in6 *)args->address;

		servername[0] = '\0';
		चयन (args->address->sa_family) अणु
		हाल AF_LOCAL:
			snम_लिखो(servername, माप(servername), "%s",
				 sun->sun_path);
			अवरोध;
		हाल AF_INET:
			snम_लिखो(servername, माप(servername), "%pI4",
				 &sin->sin_addr.s_addr);
			अवरोध;
		हाल AF_INET6:
			snम_लिखो(servername, माप(servername), "%pI6",
				 &sin6->sin6_addr);
			अवरोध;
		शेष:
			/* caller wants शेष server name, but
			 * address family isn't recognized. */
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		xprtargs.servername = servername;
	पूर्ण

	xprt = xprt_create_transport(&xprtargs);
	अगर (IS_ERR(xprt))
		वापस (काष्ठा rpc_clnt *)xprt;

	/*
	 * By शेष, kernel RPC client connects from a reserved port.
	 * CAP_NET_BIND_SERVICE will not be set क्रम unprivileged requesters,
	 * but it is always enabled क्रम rpciod, which handles the connect
	 * operation.
	 */
	xprt->resvport = 1;
	अगर (args->flags & RPC_CLNT_CREATE_NONPRIVPORT)
		xprt->resvport = 0;
	xprt->reuseport = 0;
	अगर (args->flags & RPC_CLNT_CREATE_REUSEPORT)
		xprt->reuseport = 1;

	clnt = rpc_create_xprt(args, xprt);
	अगर (IS_ERR(clnt) || args->nconnect <= 1)
		वापस clnt;

	क्रम (i = 0; i < args->nconnect - 1; i++) अणु
		अगर (rpc_clnt_add_xprt(clnt, &xprtargs, शून्य, शून्य) < 0)
			अवरोध;
	पूर्ण
	वापस clnt;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_create);

/*
 * This function clones the RPC client काष्ठाure. It allows us to share the
 * same transport जबतक varying parameters such as the authentication
 * flavour.
 */
अटल काष्ठा rpc_clnt *__rpc_clone_client(काष्ठा rpc_create_args *args,
					   काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_xprt_चयन *xps;
	काष्ठा rpc_xprt *xprt;
	काष्ठा rpc_clnt *new;
	पूर्णांक err;

	err = -ENOMEM;
	rcu_पढ़ो_lock();
	xprt = xprt_get(rcu_dereference(clnt->cl_xprt));
	xps = xprt_चयन_get(rcu_dereference(clnt->cl_xpi.xpi_xpचयन));
	rcu_पढ़ो_unlock();
	अगर (xprt == शून्य || xps == शून्य) अणु
		xprt_put(xprt);
		xprt_चयन_put(xps);
		जाओ out_err;
	पूर्ण
	args->servername = xprt->servername;
	args->nodename = clnt->cl_nodename;

	new = rpc_new_client(args, xps, xprt, clnt);
	अगर (IS_ERR(new))
		वापस new;

	/* Turn off स्वतःbind on clones */
	new->cl_स्वतःbind = 0;
	new->cl_softrtry = clnt->cl_softrtry;
	new->cl_softerr = clnt->cl_softerr;
	new->cl_noretransसमयo = clnt->cl_noretransसमयo;
	new->cl_discrtry = clnt->cl_discrtry;
	new->cl_chatty = clnt->cl_chatty;
	new->cl_principal = clnt->cl_principal;
	वापस new;

out_err:
	trace_rpc_clnt_clone_err(clnt, err);
	वापस ERR_PTR(err);
पूर्ण

/**
 * rpc_clone_client - Clone an RPC client काष्ठाure
 *
 * @clnt: RPC client whose parameters are copied
 *
 * Returns a fresh RPC client or an ERR_PTR.
 */
काष्ठा rpc_clnt *rpc_clone_client(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_create_args args = अणु
		.program	= clnt->cl_program,
		.prognumber	= clnt->cl_prog,
		.version	= clnt->cl_vers,
		.authflavor	= clnt->cl_auth->au_flavor,
		.cred		= clnt->cl_cred,
	पूर्ण;
	वापस __rpc_clone_client(&args, clnt);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clone_client);

/**
 * rpc_clone_client_set_auth - Clone an RPC client काष्ठाure and set its auth
 *
 * @clnt: RPC client whose parameters are copied
 * @flavor: security flavor क्रम new client
 *
 * Returns a fresh RPC client or an ERR_PTR.
 */
काष्ठा rpc_clnt *
rpc_clone_client_set_auth(काष्ठा rpc_clnt *clnt, rpc_authflavor_t flavor)
अणु
	काष्ठा rpc_create_args args = अणु
		.program	= clnt->cl_program,
		.prognumber	= clnt->cl_prog,
		.version	= clnt->cl_vers,
		.authflavor	= flavor,
		.cred		= clnt->cl_cred,
	पूर्ण;
	वापस __rpc_clone_client(&args, clnt);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clone_client_set_auth);

/**
 * rpc_चयन_client_transport: चयन the RPC transport on the fly
 * @clnt: poपूर्णांकer to a काष्ठा rpc_clnt
 * @args: poपूर्णांकer to the new transport arguments
 * @समयout: poपूर्णांकer to the new समयout parameters
 *
 * This function allows the caller to चयन the RPC transport क्रम the
 * rpc_clnt काष्ठाure 'clnt' to allow it to connect to a mirrored NFS
 * server, क्रम instance.  It assumes that the caller has ensured that
 * there are no active RPC tasks by using some क्रमm of locking.
 *
 * Returns zero अगर "clnt" is now using the new xprt.  Otherwise a
 * negative त्रुटि_सं is वापसed, and "clnt" जारीs to use the old
 * xprt.
 */
पूर्णांक rpc_चयन_client_transport(काष्ठा rpc_clnt *clnt,
		काष्ठा xprt_create *args,
		स्थिर काष्ठा rpc_समयout *समयout)
अणु
	स्थिर काष्ठा rpc_समयout *old_समयo;
	rpc_authflavor_t pseuकरोflavor;
	काष्ठा rpc_xprt_चयन *xps, *oldxps;
	काष्ठा rpc_xprt *xprt, *old;
	काष्ठा rpc_clnt *parent;
	पूर्णांक err;

	xprt = xprt_create_transport(args);
	अगर (IS_ERR(xprt))
		वापस PTR_ERR(xprt);

	xps = xprt_चयन_alloc(xprt, GFP_KERNEL);
	अगर (xps == शून्य) अणु
		xprt_put(xprt);
		वापस -ENOMEM;
	पूर्ण

	pseuकरोflavor = clnt->cl_auth->au_flavor;

	old_समयo = clnt->cl_समयout;
	old = rpc_clnt_set_transport(clnt, xprt, समयout);
	oldxps = xprt_iter_xchg_चयन(&clnt->cl_xpi, xps);

	rpc_unरेजिस्टर_client(clnt);
	__rpc_clnt_हटाओ_pipedir(clnt);
	rpc_clnt_debugfs_unरेजिस्टर(clnt);

	/*
	 * A new transport was created.  "clnt" thereक्रमe
	 * becomes the root of a new cl_parent tree.  clnt's
	 * children, अगर it has any, still poपूर्णांक to the old xprt.
	 */
	parent = clnt->cl_parent;
	clnt->cl_parent = clnt;

	/*
	 * The old rpc_auth cache cannot be re-used.  GSS
	 * contexts in particular are between a single
	 * client and server.
	 */
	err = rpc_client_रेजिस्टर(clnt, pseuकरोflavor, शून्य);
	अगर (err)
		जाओ out_revert;

	synchronize_rcu();
	अगर (parent != clnt)
		rpc_release_client(parent);
	xprt_चयन_put(oldxps);
	xprt_put(old);
	trace_rpc_clnt_replace_xprt(clnt);
	वापस 0;

out_revert:
	xps = xprt_iter_xchg_चयन(&clnt->cl_xpi, oldxps);
	rpc_clnt_set_transport(clnt, old, old_समयo);
	clnt->cl_parent = parent;
	rpc_client_रेजिस्टर(clnt, pseuकरोflavor, शून्य);
	xprt_चयन_put(xps);
	xprt_put(xprt);
	trace_rpc_clnt_replace_xprt_err(clnt);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_चयन_client_transport);

अटल
पूर्णांक rpc_clnt_xprt_iter_init(काष्ठा rpc_clnt *clnt, काष्ठा rpc_xprt_iter *xpi)
अणु
	काष्ठा rpc_xprt_चयन *xps;

	rcu_पढ़ो_lock();
	xps = xprt_चयन_get(rcu_dereference(clnt->cl_xpi.xpi_xpचयन));
	rcu_पढ़ो_unlock();
	अगर (xps == शून्य)
		वापस -EAGAIN;
	xprt_iter_init_listall(xpi, xps);
	xprt_चयन_put(xps);
	वापस 0;
पूर्ण

/**
 * rpc_clnt_iterate_क्रम_each_xprt - Apply a function to all transports
 * @clnt: poपूर्णांकer to client
 * @fn: function to apply
 * @data: व्योम poपूर्णांकer to function data
 *
 * Iterates through the list of RPC transports currently attached to the
 * client and applies the function fn(clnt, xprt, data).
 *
 * On error, the iteration stops, and the function वापसs the error value.
 */
पूर्णांक rpc_clnt_iterate_क्रम_each_xprt(काष्ठा rpc_clnt *clnt,
		पूर्णांक (*fn)(काष्ठा rpc_clnt *, काष्ठा rpc_xprt *, व्योम *),
		व्योम *data)
अणु
	काष्ठा rpc_xprt_iter xpi;
	पूर्णांक ret;

	ret = rpc_clnt_xprt_iter_init(clnt, &xpi);
	अगर (ret)
		वापस ret;
	क्रम (;;) अणु
		काष्ठा rpc_xprt *xprt = xprt_iter_get_next(&xpi);

		अगर (!xprt)
			अवरोध;
		ret = fn(clnt, xprt, data);
		xprt_put(xprt);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	xprt_iter_destroy(&xpi);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_iterate_क्रम_each_xprt);

/*
 * Kill all tasks क्रम the given client.
 * XXX: समाप्त their descendants as well?
 */
व्योम rpc_समाप्तall_tasks(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_task	*rovr;


	अगर (list_empty(&clnt->cl_tasks))
		वापस;

	/*
	 * Spin lock all_tasks to prevent changes...
	 */
	trace_rpc_clnt_समाप्तall(clnt);
	spin_lock(&clnt->cl_lock);
	list_क्रम_each_entry(rovr, &clnt->cl_tasks, tk_task)
		rpc_संकेत_task(rovr);
	spin_unlock(&clnt->cl_lock);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_समाप्तall_tasks);

/*
 * Properly shut करोwn an RPC client, terminating all outstanding
 * requests.
 */
व्योम rpc_shutकरोwn_client(काष्ठा rpc_clnt *clnt)
अणु
	might_sleep();

	trace_rpc_clnt_shutकरोwn(clnt);

	जबतक (!list_empty(&clnt->cl_tasks)) अणु
		rpc_समाप्तall_tasks(clnt);
		रुको_event_समयout(destroy_रुको,
			list_empty(&clnt->cl_tasks), 1*HZ);
	पूर्ण

	rpc_release_client(clnt);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_shutकरोwn_client);

/*
 * Free an RPC client
 */
अटल व्योम rpc_मुक्त_client_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rpc_clnt *clnt = container_of(work, काष्ठा rpc_clnt, cl_work);

	trace_rpc_clnt_मुक्त(clnt);

	/* These might block on processes that might allocate memory,
	 * so they cannot be called in rpciod, so they are handled separately
	 * here.
	 */
	rpc_clnt_debugfs_unरेजिस्टर(clnt);
	rpc_मुक्त_clid(clnt);
	rpc_clnt_हटाओ_pipedir(clnt);
	xprt_put(rcu_dereference_raw(clnt->cl_xprt));

	kमुक्त(clnt);
	rpciod_करोwn();
पूर्ण
अटल काष्ठा rpc_clnt *
rpc_मुक्त_client(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_clnt *parent = शून्य;

	trace_rpc_clnt_release(clnt);
	अगर (clnt->cl_parent != clnt)
		parent = clnt->cl_parent;
	rpc_unरेजिस्टर_client(clnt);
	rpc_मुक्त_iostats(clnt->cl_metrics);
	clnt->cl_metrics = शून्य;
	xprt_iter_destroy(&clnt->cl_xpi);
	put_cred(clnt->cl_cred);

	INIT_WORK(&clnt->cl_work, rpc_मुक्त_client_work);
	schedule_work(&clnt->cl_work);
	वापस parent;
पूर्ण

/*
 * Free an RPC client
 */
अटल काष्ठा rpc_clnt *
rpc_मुक्त_auth(काष्ठा rpc_clnt *clnt)
अणु
	अगर (clnt->cl_auth == शून्य)
		वापस rpc_मुक्त_client(clnt);

	/*
	 * Note: RPCSEC_GSS may need to send शून्य RPC calls in order to
	 *       release reमुख्यing GSS contexts. This mechanism ensures
	 *       that it can करो so safely.
	 */
	atomic_inc(&clnt->cl_count);
	rpcauth_release(clnt->cl_auth);
	clnt->cl_auth = शून्य;
	अगर (atomic_dec_and_test(&clnt->cl_count))
		वापस rpc_मुक्त_client(clnt);
	वापस शून्य;
पूर्ण

/*
 * Release reference to the RPC client
 */
व्योम
rpc_release_client(काष्ठा rpc_clnt *clnt)
अणु
	करो अणु
		अगर (list_empty(&clnt->cl_tasks))
			wake_up(&destroy_रुको);
		अगर (!atomic_dec_and_test(&clnt->cl_count))
			अवरोध;
		clnt = rpc_मुक्त_auth(clnt);
	पूर्ण जबतक (clnt != शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_release_client);

/**
 * rpc_bind_new_program - bind a new RPC program to an existing client
 * @old: old rpc_client
 * @program: rpc program to set
 * @vers: rpc program version
 *
 * Clones the rpc client and sets up a new RPC program. This is मुख्यly
 * of use क्रम enabling dअगरferent RPC programs to share the same transport.
 * The Sun NFSv2/v3 ACL protocol can करो this.
 */
काष्ठा rpc_clnt *rpc_bind_new_program(काष्ठा rpc_clnt *old,
				      स्थिर काष्ठा rpc_program *program,
				      u32 vers)
अणु
	काष्ठा rpc_create_args args = अणु
		.program	= program,
		.prognumber	= program->number,
		.version	= vers,
		.authflavor	= old->cl_auth->au_flavor,
		.cred		= old->cl_cred,
	पूर्ण;
	काष्ठा rpc_clnt *clnt;
	पूर्णांक err;

	clnt = __rpc_clone_client(&args, old);
	अगर (IS_ERR(clnt))
		जाओ out;
	err = rpc_ping(clnt);
	अगर (err != 0) अणु
		rpc_shutकरोwn_client(clnt);
		clnt = ERR_PTR(err);
	पूर्ण
out:
	वापस clnt;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_bind_new_program);

काष्ठा rpc_xprt *
rpc_task_get_xprt(काष्ठा rpc_clnt *clnt, काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpc_xprt_चयन *xps;

	अगर (!xprt)
		वापस शून्य;
	rcu_पढ़ो_lock();
	xps = rcu_dereference(clnt->cl_xpi.xpi_xpचयन);
	atomic_दीर्घ_inc(&xps->xps_queuelen);
	rcu_पढ़ो_unlock();
	atomic_दीर्घ_inc(&xprt->queuelen);

	वापस xprt;
पूर्ण

अटल व्योम
rpc_task_release_xprt(काष्ठा rpc_clnt *clnt, काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpc_xprt_चयन *xps;

	atomic_दीर्घ_dec(&xprt->queuelen);
	rcu_पढ़ो_lock();
	xps = rcu_dereference(clnt->cl_xpi.xpi_xpचयन);
	atomic_दीर्घ_dec(&xps->xps_queuelen);
	rcu_पढ़ो_unlock();

	xprt_put(xprt);
पूर्ण

व्योम rpc_task_release_transport(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt *xprt = task->tk_xprt;

	अगर (xprt) अणु
		task->tk_xprt = शून्य;
		अगर (task->tk_client)
			rpc_task_release_xprt(task->tk_client, xprt);
		अन्यथा
			xprt_put(xprt);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rpc_task_release_transport);

व्योम rpc_task_release_client(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_clnt *clnt = task->tk_client;

	rpc_task_release_transport(task);
	अगर (clnt != शून्य) अणु
		/* Remove from client task list */
		spin_lock(&clnt->cl_lock);
		list_del(&task->tk_task);
		spin_unlock(&clnt->cl_lock);
		task->tk_client = शून्य;

		rpc_release_client(clnt);
	पूर्ण
पूर्ण

अटल काष्ठा rpc_xprt *
rpc_task_get_first_xprt(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_xprt *xprt;

	rcu_पढ़ो_lock();
	xprt = xprt_get(rcu_dereference(clnt->cl_xprt));
	rcu_पढ़ो_unlock();
	वापस rpc_task_get_xprt(clnt, xprt);
पूर्ण

अटल काष्ठा rpc_xprt *
rpc_task_get_next_xprt(काष्ठा rpc_clnt *clnt)
अणु
	वापस rpc_task_get_xprt(clnt, xprt_iter_get_next(&clnt->cl_xpi));
पूर्ण

अटल
व्योम rpc_task_set_transport(काष्ठा rpc_task *task, काष्ठा rpc_clnt *clnt)
अणु
	अगर (task->tk_xprt)
		वापस;
	अगर (task->tk_flags & RPC_TASK_NO_ROUND_ROBIN)
		task->tk_xprt = rpc_task_get_first_xprt(clnt);
	अन्यथा
		task->tk_xprt = rpc_task_get_next_xprt(clnt);
पूर्ण

अटल
व्योम rpc_task_set_client(काष्ठा rpc_task *task, काष्ठा rpc_clnt *clnt)
अणु

	अगर (clnt != शून्य) अणु
		rpc_task_set_transport(task, clnt);
		task->tk_client = clnt;
		atomic_inc(&clnt->cl_count);
		अगर (clnt->cl_softrtry)
			task->tk_flags |= RPC_TASK_SOFT;
		अगर (clnt->cl_softerr)
			task->tk_flags |= RPC_TASK_TIMEOUT;
		अगर (clnt->cl_noretransसमयo)
			task->tk_flags |= RPC_TASK_NO_RETRANS_TIMEOUT;
		अगर (atomic_पढ़ो(&clnt->cl_swapper))
			task->tk_flags |= RPC_TASK_SWAPPER;
		/* Add to the client's list of all tasks */
		spin_lock(&clnt->cl_lock);
		list_add_tail(&task->tk_task, &clnt->cl_tasks);
		spin_unlock(&clnt->cl_lock);
	पूर्ण
पूर्ण

अटल व्योम
rpc_task_set_rpc_message(काष्ठा rpc_task *task, स्थिर काष्ठा rpc_message *msg)
अणु
	अगर (msg != शून्य) अणु
		task->tk_msg.rpc_proc = msg->rpc_proc;
		task->tk_msg.rpc_argp = msg->rpc_argp;
		task->tk_msg.rpc_resp = msg->rpc_resp;
		task->tk_msg.rpc_cred = msg->rpc_cred;
		अगर (!(task->tk_flags & RPC_TASK_CRED_NOREF))
			get_cred(task->tk_msg.rpc_cred);
	पूर्ण
पूर्ण

/*
 * Default callback क्रम async RPC calls
 */
अटल व्योम
rpc_शेष_callback(काष्ठा rpc_task *task, व्योम *data)
अणु
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops rpc_शेष_ops = अणु
	.rpc_call_करोne = rpc_शेष_callback,
पूर्ण;

/**
 * rpc_run_task - Allocate a new RPC task, then run rpc_execute against it
 * @task_setup_data: poपूर्णांकer to task initialisation data
 */
काष्ठा rpc_task *rpc_run_task(स्थिर काष्ठा rpc_task_setup *task_setup_data)
अणु
	काष्ठा rpc_task *task;

	task = rpc_new_task(task_setup_data);

	अगर (!RPC_IS_ASYNC(task))
		task->tk_flags |= RPC_TASK_CRED_NOREF;

	rpc_task_set_client(task, task_setup_data->rpc_client);
	rpc_task_set_rpc_message(task, task_setup_data->rpc_message);

	अगर (task->tk_action == शून्य)
		rpc_call_start(task);

	atomic_inc(&task->tk_count);
	rpc_execute(task);
	वापस task;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_run_task);

/**
 * rpc_call_sync - Perक्रमm a synchronous RPC call
 * @clnt: poपूर्णांकer to RPC client
 * @msg: RPC call parameters
 * @flags: RPC call flags
 */
पूर्णांक rpc_call_sync(काष्ठा rpc_clnt *clnt, स्थिर काष्ठा rpc_message *msg, पूर्णांक flags)
अणु
	काष्ठा rpc_task	*task;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = clnt,
		.rpc_message = msg,
		.callback_ops = &rpc_शेष_ops,
		.flags = flags,
	पूर्ण;
	पूर्णांक status;

	WARN_ON_ONCE(flags & RPC_TASK_ASYNC);
	अगर (flags & RPC_TASK_ASYNC) अणु
		rpc_release_calldata(task_setup_data.callback_ops,
			task_setup_data.callback_data);
		वापस -EINVAL;
	पूर्ण

	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	status = task->tk_status;
	rpc_put_task(task);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_call_sync);

/**
 * rpc_call_async - Perक्रमm an asynchronous RPC call
 * @clnt: poपूर्णांकer to RPC client
 * @msg: RPC call parameters
 * @flags: RPC call flags
 * @tk_ops: RPC call ops
 * @data: user call data
 */
पूर्णांक
rpc_call_async(काष्ठा rpc_clnt *clnt, स्थिर काष्ठा rpc_message *msg, पूर्णांक flags,
	       स्थिर काष्ठा rpc_call_ops *tk_ops, व्योम *data)
अणु
	काष्ठा rpc_task	*task;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = clnt,
		.rpc_message = msg,
		.callback_ops = tk_ops,
		.callback_data = data,
		.flags = flags|RPC_TASK_ASYNC,
	पूर्ण;

	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	rpc_put_task(task);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_call_async);

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
अटल व्योम call_bc_encode(काष्ठा rpc_task *task);

/**
 * rpc_run_bc_task - Allocate a new RPC task क्रम backchannel use, then run
 * rpc_execute against it
 * @req: RPC request
 */
काष्ठा rpc_task *rpc_run_bc_task(काष्ठा rpc_rqst *req)
अणु
	काष्ठा rpc_task *task;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.callback_ops = &rpc_शेष_ops,
		.flags = RPC_TASK_SOFTCONN |
			RPC_TASK_NO_RETRANS_TIMEOUT,
	पूर्ण;

	dprपूर्णांकk("RPC: rpc_run_bc_task req= %p\n", req);
	/*
	 * Create an rpc_task to send the data
	 */
	task = rpc_new_task(&task_setup_data);
	xprt_init_bc_request(req, task);

	task->tk_action = call_bc_encode;
	atomic_inc(&task->tk_count);
	WARN_ON_ONCE(atomic_पढ़ो(&task->tk_count) != 2);
	rpc_execute(task);

	dprपूर्णांकk("RPC: rpc_run_bc_task: task= %p\n", task);
	वापस task;
पूर्ण
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */

/**
 * rpc_prepare_reply_pages - Prepare to receive a reply data payload पूर्णांकo pages
 * @req: RPC request to prepare
 * @pages: vector of काष्ठा page poपूर्णांकers
 * @base: offset in first page where receive should start, in bytes
 * @len: expected size of the upper layer data payload, in bytes
 * @hdrsize: expected size of upper layer reply header, in XDR words
 *
 */
व्योम rpc_prepare_reply_pages(काष्ठा rpc_rqst *req, काष्ठा page **pages,
			     अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len,
			     अचिन्हित पूर्णांक hdrsize)
अणु
	hdrsize += RPC_REPHDRSIZE + req->rq_cred->cr_auth->au_ralign;

	xdr_अंतरभूत_pages(&req->rq_rcv_buf, hdrsize << 2, pages, base, len);
	trace_rpc_xdr_reply_pages(req->rq_task, &req->rq_rcv_buf);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_prepare_reply_pages);

व्योम
rpc_call_start(काष्ठा rpc_task *task)
अणु
	task->tk_action = call_start;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_call_start);

/**
 * rpc_peeraddr - extract remote peer address from clnt's xprt
 * @clnt: RPC client काष्ठाure
 * @buf: target buffer
 * @bufsize: length of target buffer
 *
 * Returns the number of bytes that are actually in the stored address.
 */
माप_प्रकार rpc_peeraddr(काष्ठा rpc_clnt *clnt, काष्ठा sockaddr *buf, माप_प्रकार bufsize)
अणु
	माप_प्रकार bytes;
	काष्ठा rpc_xprt *xprt;

	rcu_पढ़ो_lock();
	xprt = rcu_dereference(clnt->cl_xprt);

	bytes = xprt->addrlen;
	अगर (bytes > bufsize)
		bytes = bufsize;
	स_नकल(buf, &xprt->addr, bytes);
	rcu_पढ़ो_unlock();

	वापस bytes;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_peeraddr);

/**
 * rpc_peeraddr2str - वापस remote peer address in prपूर्णांकable क्रमmat
 * @clnt: RPC client काष्ठाure
 * @क्रमmat: address क्रमmat
 *
 * NB: the lअगरeसमय of the memory referenced by the वापसed poपूर्णांकer is
 * the same as the rpc_xprt itself.  As दीर्घ as the caller uses this
 * poपूर्णांकer, it must hold the RCU पढ़ो lock.
 */
स्थिर अक्षर *rpc_peeraddr2str(काष्ठा rpc_clnt *clnt,
			     क्रमागत rpc_display_क्रमmat_t क्रमmat)
अणु
	काष्ठा rpc_xprt *xprt;

	xprt = rcu_dereference(clnt->cl_xprt);

	अगर (xprt->address_strings[क्रमmat] != शून्य)
		वापस xprt->address_strings[क्रमmat];
	अन्यथा
		वापस "unprintable";
पूर्ण
EXPORT_SYMBOL_GPL(rpc_peeraddr2str);

अटल स्थिर काष्ठा sockaddr_in rpc_inaddr_loopback = अणु
	.sin_family		= AF_INET,
	.sin_addr.s_addr	= htonl(INADDR_ANY),
पूर्ण;

अटल स्थिर काष्ठा sockaddr_in6 rpc_in6addr_loopback = अणु
	.sin6_family		= AF_INET6,
	.sin6_addr		= IN6ADDR_ANY_INIT,
पूर्ण;

/*
 * Try a माला_लोockname() on a connected datagram socket.  Using a
 * connected datagram socket prevents leaving a socket in TIME_WAIT.
 * This conserves the ephemeral port number space.
 *
 * Returns zero and fills in "buf" अगर successful; otherwise, a
 * negative त्रुटि_सं is वापसed.
 */
अटल पूर्णांक rpc_sockname(काष्ठा net *net, काष्ठा sockaddr *sap, माप_प्रकार salen,
			काष्ठा sockaddr *buf)
अणु
	काष्ठा socket *sock;
	पूर्णांक err;

	err = __sock_create(net, sap->sa_family,
				SOCK_DGRAM, IPPROTO_UDP, &sock, 1);
	अगर (err < 0) अणु
		dprपूर्णांकk("RPC:       can't create UDP socket (%d)\n", err);
		जाओ out;
	पूर्ण

	चयन (sap->sa_family) अणु
	हाल AF_INET:
		err = kernel_bind(sock,
				(काष्ठा sockaddr *)&rpc_inaddr_loopback,
				माप(rpc_inaddr_loopback));
		अवरोध;
	हाल AF_INET6:
		err = kernel_bind(sock,
				(काष्ठा sockaddr *)&rpc_in6addr_loopback,
				माप(rpc_in6addr_loopback));
		अवरोध;
	शेष:
		err = -EAFNOSUPPORT;
		जाओ out;
	पूर्ण
	अगर (err < 0) अणु
		dprपूर्णांकk("RPC:       can't bind UDP socket (%d)\n", err);
		जाओ out_release;
	पूर्ण

	err = kernel_connect(sock, sap, salen, 0);
	अगर (err < 0) अणु
		dprपूर्णांकk("RPC:       can't connect UDP socket (%d)\n", err);
		जाओ out_release;
	पूर्ण

	err = kernel_माला_लोockname(sock, buf);
	अगर (err < 0) अणु
		dprपूर्णांकk("RPC:       getsockname failed (%d)\n", err);
		जाओ out_release;
	पूर्ण

	err = 0;
	अगर (buf->sa_family == AF_INET6) अणु
		काष्ठा sockaddr_in6 *sin6 = (काष्ठा sockaddr_in6 *)buf;
		sin6->sin6_scope_id = 0;
	पूर्ण
	dprपूर्णांकk("RPC:       %s succeeded\n", __func__);

out_release:
	sock_release(sock);
out:
	वापस err;
पूर्ण

/*
 * Scraping a connected socket failed, so we करोn't have a useable
 * local address.  Fallback: generate an address that will prevent
 * the server from calling us back.
 *
 * Returns zero and fills in "buf" अगर successful; otherwise, a
 * negative त्रुटि_सं is वापसed.
 */
अटल पूर्णांक rpc_anyaddr(पूर्णांक family, काष्ठा sockaddr *buf, माप_प्रकार buflen)
अणु
	चयन (family) अणु
	हाल AF_INET:
		अगर (buflen < माप(rpc_inaddr_loopback))
			वापस -EINVAL;
		स_नकल(buf, &rpc_inaddr_loopback,
				माप(rpc_inaddr_loopback));
		अवरोध;
	हाल AF_INET6:
		अगर (buflen < माप(rpc_in6addr_loopback))
			वापस -EINVAL;
		स_नकल(buf, &rpc_in6addr_loopback,
				माप(rpc_in6addr_loopback));
		अवरोध;
	शेष:
		dprपूर्णांकk("RPC:       %s: address family not supported\n",
			__func__);
		वापस -EAFNOSUPPORT;
	पूर्ण
	dprपूर्णांकk("RPC:       %s: succeeded\n", __func__);
	वापस 0;
पूर्ण

/**
 * rpc_localaddr - discover local endpoपूर्णांक address क्रम an RPC client
 * @clnt: RPC client काष्ठाure
 * @buf: target buffer
 * @buflen: size of target buffer, in bytes
 *
 * Returns zero and fills in "buf" and "buflen" अगर successful;
 * otherwise, a negative त्रुटि_सं is वापसed.
 *
 * This works even अगर the underlying transport is not currently connected,
 * or अगर the upper layer never previously provided a source address.
 *
 * The result of this function call is transient: multiple calls in
 * succession may give dअगरferent results, depending on how local
 * networking configuration changes over समय.
 */
पूर्णांक rpc_localaddr(काष्ठा rpc_clnt *clnt, काष्ठा sockaddr *buf, माप_प्रकार buflen)
अणु
	काष्ठा sockaddr_storage address;
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&address;
	काष्ठा rpc_xprt *xprt;
	काष्ठा net *net;
	माप_प्रकार salen;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	xprt = rcu_dereference(clnt->cl_xprt);
	salen = xprt->addrlen;
	स_नकल(sap, &xprt->addr, salen);
	net = get_net(xprt->xprt_net);
	rcu_पढ़ो_unlock();

	rpc_set_port(sap, 0);
	err = rpc_sockname(net, sap, salen, buf);
	put_net(net);
	अगर (err != 0)
		/* Couldn't discover local address, वापस ANYADDR */
		वापस rpc_anyaddr(sap->sa_family, buf, buflen);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_localaddr);

व्योम
rpc_रखो_बफsize(काष्ठा rpc_clnt *clnt, अचिन्हित पूर्णांक sndsize, अचिन्हित पूर्णांक rcvsize)
अणु
	काष्ठा rpc_xprt *xprt;

	rcu_पढ़ो_lock();
	xprt = rcu_dereference(clnt->cl_xprt);
	अगर (xprt->ops->set_buffer_size)
		xprt->ops->set_buffer_size(xprt, sndsize, rcvsize);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(rpc_रखो_बफsize);

/**
 * rpc_net_ns - Get the network namespace क्रम this RPC client
 * @clnt: RPC client to query
 *
 */
काष्ठा net *rpc_net_ns(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा net *ret;

	rcu_पढ़ो_lock();
	ret = rcu_dereference(clnt->cl_xprt)->xprt_net;
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_net_ns);

/**
 * rpc_max_payload - Get maximum payload size क्रम a transport, in bytes
 * @clnt: RPC client to query
 *
 * For stream transports, this is one RPC record fragment (see RFC
 * 1831), as we करोn't support multi-record requests yet.  For datagram
 * transports, this is the size of an IP packet minus the IP, UDP, and
 * RPC header sizes.
 */
माप_प्रकार rpc_max_payload(काष्ठा rpc_clnt *clnt)
अणु
	माप_प्रकार ret;

	rcu_पढ़ो_lock();
	ret = rcu_dereference(clnt->cl_xprt)->max_payload;
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_max_payload);

/**
 * rpc_max_bc_payload - Get maximum backchannel payload size, in bytes
 * @clnt: RPC client to query
 */
माप_प्रकार rpc_max_bc_payload(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_xprt *xprt;
	माप_प्रकार ret;

	rcu_पढ़ो_lock();
	xprt = rcu_dereference(clnt->cl_xprt);
	ret = xprt->ops->bc_maxpayload(xprt);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_max_bc_payload);

अचिन्हित पूर्णांक rpc_num_bc_slots(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_xprt *xprt;
	अचिन्हित पूर्णांक ret;

	rcu_पढ़ो_lock();
	xprt = rcu_dereference(clnt->cl_xprt);
	ret = xprt->ops->bc_num_slots(xprt);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_num_bc_slots);

/**
 * rpc_क्रमce_rebind - क्रमce transport to check that remote port is unchanged
 * @clnt: client to rebind
 *
 */
व्योम rpc_क्रमce_rebind(काष्ठा rpc_clnt *clnt)
अणु
	अगर (clnt->cl_स्वतःbind) अणु
		rcu_पढ़ो_lock();
		xprt_clear_bound(rcu_dereference(clnt->cl_xprt));
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rpc_क्रमce_rebind);

अटल पूर्णांक
__rpc_restart_call(काष्ठा rpc_task *task, व्योम (*action)(काष्ठा rpc_task *))
अणु
	task->tk_status = 0;
	task->tk_rpc_status = 0;
	task->tk_action = action;
	वापस 1;
पूर्ण

/*
 * Restart an (async) RPC call. Usually called from within the
 * निकास handler.
 */
पूर्णांक
rpc_restart_call(काष्ठा rpc_task *task)
अणु
	वापस __rpc_restart_call(task, call_start);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_restart_call);

/*
 * Restart an (async) RPC call from the call_prepare state.
 * Usually called from within the निकास handler.
 */
पूर्णांक
rpc_restart_call_prepare(काष्ठा rpc_task *task)
अणु
	अगर (task->tk_ops->rpc_call_prepare != शून्य)
		वापस __rpc_restart_call(task, rpc_prepare_task);
	वापस rpc_restart_call(task);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_restart_call_prepare);

स्थिर अक्षर
*rpc_proc_name(स्थिर काष्ठा rpc_task *task)
अणु
	स्थिर काष्ठा rpc_procinfo *proc = task->tk_msg.rpc_proc;

	अगर (proc) अणु
		अगर (proc->p_name)
			वापस proc->p_name;
		अन्यथा
			वापस "NULL";
	पूर्ण अन्यथा
		वापस "no proc";
पूर्ण

अटल व्योम
__rpc_call_rpcerror(काष्ठा rpc_task *task, पूर्णांक tk_status, पूर्णांक rpc_status)
अणु
	trace_rpc_call_rpcerror(task, tk_status, rpc_status);
	task->tk_rpc_status = rpc_status;
	rpc_निकास(task, tk_status);
पूर्ण

अटल व्योम
rpc_call_rpcerror(काष्ठा rpc_task *task, पूर्णांक status)
अणु
	__rpc_call_rpcerror(task, status, status);
पूर्ण

/*
 * 0.  Initial state
 *
 *     Other FSM states can be visited zero or more बार, but
 *     this state is visited exactly once क्रम each RPC.
 */
अटल व्योम
call_start(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_clnt	*clnt = task->tk_client;
	पूर्णांक idx = task->tk_msg.rpc_proc->p_statidx;

	trace_rpc_request(task);

	/* Increment call count (version might not be valid क्रम ping) */
	अगर (clnt->cl_program->version[clnt->cl_vers])
		clnt->cl_program->version[clnt->cl_vers]->counts[idx]++;
	clnt->cl_stats->rpccnt++;
	task->tk_action = call_reserve;
	rpc_task_set_transport(task, clnt);
पूर्ण

/*
 * 1.	Reserve an RPC call slot
 */
अटल व्योम
call_reserve(काष्ठा rpc_task *task)
अणु
	task->tk_status  = 0;
	task->tk_action  = call_reserveresult;
	xprt_reserve(task);
पूर्ण

अटल व्योम call_retry_reserve(काष्ठा rpc_task *task);

/*
 * 1b.	Grok the result of xprt_reserve()
 */
अटल व्योम
call_reserveresult(काष्ठा rpc_task *task)
अणु
	पूर्णांक status = task->tk_status;

	/*
	 * After a call to xprt_reserve(), we must have either
	 * a request slot or अन्यथा an error status.
	 */
	task->tk_status = 0;
	अगर (status >= 0) अणु
		अगर (task->tk_rqstp) अणु
			task->tk_action = call_refresh;
			वापस;
		पूर्ण

		rpc_call_rpcerror(task, -EIO);
		वापस;
	पूर्ण

	चयन (status) अणु
	हाल -ENOMEM:
		rpc_delay(task, HZ >> 2);
		fallthrough;
	हाल -EAGAIN:	/* woken up; retry */
		task->tk_action = call_retry_reserve;
		वापस;
	शेष:
		rpc_call_rpcerror(task, status);
	पूर्ण
पूर्ण

/*
 * 1c.	Retry reserving an RPC call slot
 */
अटल व्योम
call_retry_reserve(काष्ठा rpc_task *task)
अणु
	task->tk_status  = 0;
	task->tk_action  = call_reserveresult;
	xprt_retry_reserve(task);
पूर्ण

/*
 * 2.	Bind and/or refresh the credentials
 */
अटल व्योम
call_refresh(काष्ठा rpc_task *task)
अणु
	task->tk_action = call_refreshresult;
	task->tk_status = 0;
	task->tk_client->cl_stats->rpcauthrefresh++;
	rpcauth_refreshcred(task);
पूर्ण

/*
 * 2a.	Process the results of a credential refresh
 */
अटल व्योम
call_refreshresult(काष्ठा rpc_task *task)
अणु
	पूर्णांक status = task->tk_status;

	task->tk_status = 0;
	task->tk_action = call_refresh;
	चयन (status) अणु
	हाल 0:
		अगर (rpcauth_uptodatecred(task)) अणु
			task->tk_action = call_allocate;
			वापस;
		पूर्ण
		/* Use rate-limiting and a max number of retries अगर refresh
		 * had status 0 but failed to update the cred.
		 */
		fallthrough;
	हाल -ETIMEDOUT:
		rpc_delay(task, 3*HZ);
		fallthrough;
	हाल -EAGAIN:
		status = -EACCES;
		fallthrough;
	हाल -EKEYEXPIRED:
		अगर (!task->tk_cred_retry)
			अवरोध;
		task->tk_cred_retry--;
		trace_rpc_retry_refresh_status(task);
		वापस;
	पूर्ण
	trace_rpc_refresh_status(task);
	rpc_call_rpcerror(task, status);
पूर्ण

/*
 * 2b.	Allocate the buffer. For details, see sched.c:rpc_दो_स्मृति.
 *	(Note: buffer memory is मुक्तd in xprt_release).
 */
अटल व्योम
call_allocate(काष्ठा rpc_task *task)
अणु
	स्थिर काष्ठा rpc_auth *auth = task->tk_rqstp->rq_cred->cr_auth;
	काष्ठा rpc_rqst *req = task->tk_rqstp;
	काष्ठा rpc_xprt *xprt = req->rq_xprt;
	स्थिर काष्ठा rpc_procinfo *proc = task->tk_msg.rpc_proc;
	पूर्णांक status;

	task->tk_status = 0;
	task->tk_action = call_encode;

	अगर (req->rq_buffer)
		वापस;

	अगर (proc->p_proc != 0) अणु
		BUG_ON(proc->p_arglen == 0);
		अगर (proc->p_decode != शून्य)
			BUG_ON(proc->p_replen == 0);
	पूर्ण

	/*
	 * Calculate the size (in quads) of the RPC call
	 * and reply headers, and convert both values
	 * to byte sizes.
	 */
	req->rq_callsize = RPC_CALLHDRSIZE + (auth->au_cslack << 1) +
			   proc->p_arglen;
	req->rq_callsize <<= 2;
	/*
	 * Note: the reply buffer must at minimum allocate enough space
	 * क्रम the 'struct accepted_reply' from RFC5531.
	 */
	req->rq_rcvsize = RPC_REPHDRSIZE + auth->au_rslack + \
			max_t(माप_प्रकार, proc->p_replen, 2);
	req->rq_rcvsize <<= 2;

	status = xprt->ops->buf_alloc(task);
	trace_rpc_buf_alloc(task, status);
	अगर (status == 0)
		वापस;
	अगर (status != -ENOMEM) अणु
		rpc_call_rpcerror(task, status);
		वापस;
	पूर्ण

	अगर (RPC_IS_ASYNC(task) || !fatal_संकेत_pending(current)) अणु
		task->tk_action = call_allocate;
		rpc_delay(task, HZ>>4);
		वापस;
	पूर्ण

	rpc_call_rpcerror(task, -ERESTARTSYS);
पूर्ण

अटल पूर्णांक
rpc_task_need_encode(काष्ठा rpc_task *task)
अणु
	वापस test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate) == 0 &&
		(!(task->tk_flags & RPC_TASK_SENT) ||
		 !(task->tk_flags & RPC_TASK_NO_RETRANS_TIMEOUT) ||
		 xprt_request_need_retransmit(task));
पूर्ण

अटल व्योम
rpc_xdr_encode(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst	*req = task->tk_rqstp;
	काष्ठा xdr_stream xdr;

	xdr_buf_init(&req->rq_snd_buf,
		     req->rq_buffer,
		     req->rq_callsize);
	xdr_buf_init(&req->rq_rcv_buf,
		     req->rq_rbuffer,
		     req->rq_rcvsize);

	req->rq_reply_bytes_recvd = 0;
	req->rq_snd_buf.head[0].iov_len = 0;
	xdr_init_encode(&xdr, &req->rq_snd_buf,
			req->rq_snd_buf.head[0].iov_base, req);
	xdr_मुक्त_bvec(&req->rq_snd_buf);
	अगर (rpc_encode_header(task, &xdr))
		वापस;

	task->tk_status = rpcauth_wrap_req(task, &xdr);
पूर्ण

/*
 * 3.	Encode arguments of an RPC call
 */
अटल व्योम
call_encode(काष्ठा rpc_task *task)
अणु
	अगर (!rpc_task_need_encode(task))
		जाओ out;

	/* Dequeue task from the receive queue जबतक we're encoding */
	xprt_request_dequeue_xprt(task);
	/* Encode here so that rpcsec_gss can use correct sequence number. */
	rpc_xdr_encode(task);
	/* Did the encode result in an error condition? */
	अगर (task->tk_status != 0) अणु
		/* Was the error nonfatal? */
		चयन (task->tk_status) अणु
		हाल -EAGAIN:
		हाल -ENOMEM:
			rpc_delay(task, HZ >> 4);
			अवरोध;
		हाल -EKEYEXPIRED:
			अगर (!task->tk_cred_retry) अणु
				rpc_निकास(task, task->tk_status);
			पूर्ण अन्यथा अणु
				task->tk_action = call_refresh;
				task->tk_cred_retry--;
				trace_rpc_retry_refresh_status(task);
			पूर्ण
			अवरोध;
		शेष:
			rpc_call_rpcerror(task, task->tk_status);
		पूर्ण
		वापस;
	पूर्ण

	/* Add task to reply queue beक्रमe transmission to aव्योम races */
	अगर (rpc_reply_expected(task))
		xprt_request_enqueue_receive(task);
	xprt_request_enqueue_transmit(task);
out:
	task->tk_action = call_transmit;
	/* Check that the connection is OK */
	अगर (!xprt_bound(task->tk_xprt))
		task->tk_action = call_bind;
	अन्यथा अगर (!xprt_connected(task->tk_xprt))
		task->tk_action = call_connect;
पूर्ण

/*
 * Helpers to check अगर the task was alपढ़ोy transmitted, and
 * to take action when that is the हाल.
 */
अटल bool
rpc_task_transmitted(काष्ठा rpc_task *task)
अणु
	वापस !test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate);
पूर्ण

अटल व्योम
rpc_task_handle_transmitted(काष्ठा rpc_task *task)
अणु
	xprt_end_transmit(task);
	task->tk_action = call_transmit_status;
पूर्ण

/*
 * 4.	Get the server port number अगर not yet set
 */
अटल व्योम
call_bind(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt *xprt = task->tk_rqstp->rq_xprt;

	अगर (rpc_task_transmitted(task)) अणु
		rpc_task_handle_transmitted(task);
		वापस;
	पूर्ण

	अगर (xprt_bound(xprt)) अणु
		task->tk_action = call_connect;
		वापस;
	पूर्ण

	task->tk_action = call_bind_status;
	अगर (!xprt_prepare_transmit(task))
		वापस;

	xprt->ops->rpcbind(task);
पूर्ण

/*
 * 4a.	Sort out bind result
 */
अटल व्योम
call_bind_status(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt *xprt = task->tk_rqstp->rq_xprt;
	पूर्णांक status = -EIO;

	अगर (rpc_task_transmitted(task)) अणु
		rpc_task_handle_transmitted(task);
		वापस;
	पूर्ण

	अगर (task->tk_status >= 0)
		जाओ out_next;
	अगर (xprt_bound(xprt)) अणु
		task->tk_status = 0;
		जाओ out_next;
	पूर्ण

	चयन (task->tk_status) अणु
	हाल -ENOMEM:
		rpc_delay(task, HZ >> 2);
		जाओ retry_समयout;
	हाल -EACCES:
		trace_rpcb_prog_unavail_err(task);
		/* fail immediately अगर this is an RPC ping */
		अगर (task->tk_msg.rpc_proc->p_proc == 0) अणु
			status = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		अगर (task->tk_rebind_retry == 0)
			अवरोध;
		task->tk_rebind_retry--;
		rpc_delay(task, 3*HZ);
		जाओ retry_समयout;
	हाल -ENOBUFS:
		rpc_delay(task, HZ >> 2);
		जाओ retry_समयout;
	हाल -EAGAIN:
		जाओ retry_समयout;
	हाल -ETIMEDOUT:
		trace_rpcb_समयout_err(task);
		जाओ retry_समयout;
	हाल -EPFNOSUPPORT:
		/* server करोesn't support any rpcbind version we know of */
		trace_rpcb_bind_version_err(task);
		अवरोध;
	हाल -EPROTONOSUPPORT:
		trace_rpcb_bind_version_err(task);
		जाओ retry_समयout;
	हाल -ECONNREFUSED:		/* connection problems */
	हाल -ECONNRESET:
	हाल -ECONNABORTED:
	हाल -ENOTCONN:
	हाल -EHOSTDOWN:
	हाल -ENETDOWN:
	हाल -EHOSTUNREACH:
	हाल -ENETUNREACH:
	हाल -EPIPE:
		trace_rpcb_unreachable_err(task);
		अगर (!RPC_IS_SOFTCONN(task)) अणु
			rpc_delay(task, 5*HZ);
			जाओ retry_समयout;
		पूर्ण
		status = task->tk_status;
		अवरोध;
	शेष:
		trace_rpcb_unrecognized_err(task);
	पूर्ण

	rpc_call_rpcerror(task, status);
	वापस;
out_next:
	task->tk_action = call_connect;
	वापस;
retry_समयout:
	task->tk_status = 0;
	task->tk_action = call_bind;
	rpc_check_समयout(task);
पूर्ण

/*
 * 4b.	Connect to the RPC server
 */
अटल व्योम
call_connect(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt *xprt = task->tk_rqstp->rq_xprt;

	अगर (rpc_task_transmitted(task)) अणु
		rpc_task_handle_transmitted(task);
		वापस;
	पूर्ण

	अगर (xprt_connected(xprt)) अणु
		task->tk_action = call_transmit;
		वापस;
	पूर्ण

	task->tk_action = call_connect_status;
	अगर (task->tk_status < 0)
		वापस;
	अगर (task->tk_flags & RPC_TASK_NOCONNECT) अणु
		rpc_call_rpcerror(task, -ENOTCONN);
		वापस;
	पूर्ण
	अगर (!xprt_prepare_transmit(task))
		वापस;
	xprt_connect(task);
पूर्ण

/*
 * 4c.	Sort out connect result
 */
अटल व्योम
call_connect_status(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_xprt *xprt = task->tk_rqstp->rq_xprt;
	काष्ठा rpc_clnt *clnt = task->tk_client;
	पूर्णांक status = task->tk_status;

	अगर (rpc_task_transmitted(task)) अणु
		rpc_task_handle_transmitted(task);
		वापस;
	पूर्ण

	trace_rpc_connect_status(task);

	अगर (task->tk_status == 0) अणु
		clnt->cl_stats->netreconn++;
		जाओ out_next;
	पूर्ण
	अगर (xprt_connected(xprt)) अणु
		task->tk_status = 0;
		जाओ out_next;
	पूर्ण

	task->tk_status = 0;
	चयन (status) अणु
	हाल -ECONNREFUSED:
		/* A positive refusal suggests a rebind is needed. */
		अगर (RPC_IS_SOFTCONN(task))
			अवरोध;
		अगर (clnt->cl_स्वतःbind) अणु
			rpc_क्रमce_rebind(clnt);
			जाओ out_retry;
		पूर्ण
		fallthrough;
	हाल -ECONNRESET:
	हाल -ECONNABORTED:
	हाल -ENETDOWN:
	हाल -ENETUNREACH:
	हाल -EHOSTUNREACH:
	हाल -EPIPE:
	हाल -EPROTO:
		xprt_conditional_disconnect(task->tk_rqstp->rq_xprt,
					    task->tk_rqstp->rq_connect_cookie);
		अगर (RPC_IS_SOFTCONN(task))
			अवरोध;
		/* retry with existing socket, after a delay */
		rpc_delay(task, 3*HZ);
		fallthrough;
	हाल -EADDRINUSE:
	हाल -ENOTCONN:
	हाल -EAGAIN:
	हाल -ETIMEDOUT:
		जाओ out_retry;
	हाल -ENOBUFS:
		rpc_delay(task, HZ >> 2);
		जाओ out_retry;
	पूर्ण
	rpc_call_rpcerror(task, status);
	वापस;
out_next:
	task->tk_action = call_transmit;
	वापस;
out_retry:
	/* Check क्रम समयouts beक्रमe looping back to call_bind */
	task->tk_action = call_bind;
	rpc_check_समयout(task);
पूर्ण

/*
 * 5.	Transmit the RPC request, and रुको क्रम reply
 */
अटल व्योम
call_transmit(काष्ठा rpc_task *task)
अणु
	अगर (rpc_task_transmitted(task)) अणु
		rpc_task_handle_transmitted(task);
		वापस;
	पूर्ण

	task->tk_action = call_transmit_status;
	अगर (!xprt_prepare_transmit(task))
		वापस;
	task->tk_status = 0;
	अगर (test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate)) अणु
		अगर (!xprt_connected(task->tk_xprt)) अणु
			task->tk_status = -ENOTCONN;
			वापस;
		पूर्ण
		xprt_transmit(task);
	पूर्ण
	xprt_end_transmit(task);
पूर्ण

/*
 * 5a.	Handle cleanup after a transmission
 */
अटल व्योम
call_transmit_status(काष्ठा rpc_task *task)
अणु
	task->tk_action = call_status;

	/*
	 * Common हाल: success.  Force the compiler to put this
	 * test first.
	 */
	अगर (rpc_task_transmitted(task)) अणु
		task->tk_status = 0;
		xprt_request_रुको_receive(task);
		वापस;
	पूर्ण

	चयन (task->tk_status) अणु
	शेष:
		अवरोध;
	हाल -EBADMSG:
		task->tk_status = 0;
		task->tk_action = call_encode;
		अवरोध;
		/*
		 * Special हालs: अगर we've been रुकोing on the
		 * socket's ग_लिखो_space() callback, or अगर the
		 * socket just वापसed a connection error,
		 * then hold onto the transport lock.
		 */
	हाल -ENOBUFS:
		rpc_delay(task, HZ>>2);
		fallthrough;
	हाल -EBADSLT:
	हाल -EAGAIN:
		task->tk_action = call_transmit;
		task->tk_status = 0;
		अवरोध;
	हाल -ECONNREFUSED:
	हाल -EHOSTDOWN:
	हाल -ENETDOWN:
	हाल -EHOSTUNREACH:
	हाल -ENETUNREACH:
	हाल -EPERM:
		अगर (RPC_IS_SOFTCONN(task)) अणु
			अगर (!task->tk_msg.rpc_proc->p_proc)
				trace_xprt_ping(task->tk_xprt,
						task->tk_status);
			rpc_call_rpcerror(task, task->tk_status);
			वापस;
		पूर्ण
		fallthrough;
	हाल -ECONNRESET:
	हाल -ECONNABORTED:
	हाल -EADDRINUSE:
	हाल -ENOTCONN:
	हाल -EPIPE:
		task->tk_action = call_bind;
		task->tk_status = 0;
		अवरोध;
	पूर्ण
	rpc_check_समयout(task);
पूर्ण

#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
अटल व्योम call_bc_transmit(काष्ठा rpc_task *task);
अटल व्योम call_bc_transmit_status(काष्ठा rpc_task *task);

अटल व्योम
call_bc_encode(काष्ठा rpc_task *task)
अणु
	xprt_request_enqueue_transmit(task);
	task->tk_action = call_bc_transmit;
पूर्ण

/*
 * 5b.	Send the backchannel RPC reply.  On error, drop the reply.  In
 * addition, disconnect on connectivity errors.
 */
अटल व्योम
call_bc_transmit(काष्ठा rpc_task *task)
अणु
	task->tk_action = call_bc_transmit_status;
	अगर (test_bit(RPC_TASK_NEED_XMIT, &task->tk_runstate)) अणु
		अगर (!xprt_prepare_transmit(task))
			वापस;
		task->tk_status = 0;
		xprt_transmit(task);
	पूर्ण
	xprt_end_transmit(task);
पूर्ण

अटल व्योम
call_bc_transmit_status(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *req = task->tk_rqstp;

	अगर (rpc_task_transmitted(task))
		task->tk_status = 0;

	चयन (task->tk_status) अणु
	हाल 0:
		/* Success */
	हाल -ENETDOWN:
	हाल -EHOSTDOWN:
	हाल -EHOSTUNREACH:
	हाल -ENETUNREACH:
	हाल -ECONNRESET:
	हाल -ECONNREFUSED:
	हाल -EADDRINUSE:
	हाल -ENOTCONN:
	हाल -EPIPE:
		अवरोध;
	हाल -ENOBUFS:
		rpc_delay(task, HZ>>2);
		fallthrough;
	हाल -EBADSLT:
	हाल -EAGAIN:
		task->tk_status = 0;
		task->tk_action = call_bc_transmit;
		वापस;
	हाल -ETIMEDOUT:
		/*
		 * Problem reaching the server.  Disconnect and let the
		 * क्रमechannel reestablish the connection.  The server will
		 * have to retransmit the backchannel request and we'll
		 * reprocess it.  Since these ops are idempotent, there's no
		 * need to cache our reply at this समय.
		 */
		prपूर्णांकk(KERN_NOTICE "RPC: Could not send backchannel reply "
			"error: %d\n", task->tk_status);
		xprt_conditional_disconnect(req->rq_xprt,
			req->rq_connect_cookie);
		अवरोध;
	शेष:
		/*
		 * We were unable to reply and will have to drop the
		 * request.  The server should reconnect and retransmit.
		 */
		prपूर्णांकk(KERN_NOTICE "RPC: Could not send backchannel reply "
			"error: %d\n", task->tk_status);
		अवरोध;
	पूर्ण
	task->tk_action = rpc_निकास_task;
पूर्ण
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */

/*
 * 6.	Sort out the RPC call status
 */
अटल व्योम
call_status(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_clnt	*clnt = task->tk_client;
	पूर्णांक		status;

	अगर (!task->tk_msg.rpc_proc->p_proc)
		trace_xprt_ping(task->tk_xprt, task->tk_status);

	status = task->tk_status;
	अगर (status >= 0) अणु
		task->tk_action = call_decode;
		वापस;
	पूर्ण

	trace_rpc_call_status(task);
	task->tk_status = 0;
	चयन(status) अणु
	हाल -EHOSTDOWN:
	हाल -ENETDOWN:
	हाल -EHOSTUNREACH:
	हाल -ENETUNREACH:
	हाल -EPERM:
		अगर (RPC_IS_SOFTCONN(task))
			जाओ out_निकास;
		/*
		 * Delay any retries क्रम 3 seconds, then handle as अगर it
		 * were a समयout.
		 */
		rpc_delay(task, 3*HZ);
		fallthrough;
	हाल -ETIMEDOUT:
		अवरोध;
	हाल -ECONNREFUSED:
	हाल -ECONNRESET:
	हाल -ECONNABORTED:
	हाल -ENOTCONN:
		rpc_क्रमce_rebind(clnt);
		अवरोध;
	हाल -EADDRINUSE:
		rpc_delay(task, 3*HZ);
		fallthrough;
	हाल -EPIPE:
	हाल -EAGAIN:
		अवरोध;
	हाल -EIO:
		/* shutकरोwn or soft समयout */
		जाओ out_निकास;
	शेष:
		अगर (clnt->cl_chatty)
			prपूर्णांकk("%s: RPC call returned error %d\n",
			       clnt->cl_program->name, -status);
		जाओ out_निकास;
	पूर्ण
	task->tk_action = call_encode;
	अगर (status != -ECONNRESET && status != -ECONNABORTED)
		rpc_check_समयout(task);
	वापस;
out_निकास:
	rpc_call_rpcerror(task, status);
पूर्ण

अटल bool
rpc_check_connected(स्थिर काष्ठा rpc_rqst *req)
अणु
	/* No allocated request or transport? वापस true */
	अगर (!req || !req->rq_xprt)
		वापस true;
	वापस xprt_connected(req->rq_xprt);
पूर्ण

अटल व्योम
rpc_check_समयout(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_clnt	*clnt = task->tk_client;

	अगर (RPC_SIGNALLED(task)) अणु
		rpc_call_rpcerror(task, -ERESTARTSYS);
		वापस;
	पूर्ण

	अगर (xprt_adjust_समयout(task->tk_rqstp) == 0)
		वापस;

	trace_rpc_समयout_status(task);
	task->tk_समयouts++;

	अगर (RPC_IS_SOFTCONN(task) && !rpc_check_connected(task->tk_rqstp)) अणु
		rpc_call_rpcerror(task, -ETIMEDOUT);
		वापस;
	पूर्ण

	अगर (RPC_IS_SOFT(task)) अणु
		/*
		 * Once a "no retrans timeout" soft tasks (a.k.a NFSv4) has
		 * been sent, it should समय out only अगर the transport
		 * connection माला_लो terminally broken.
		 */
		अगर ((task->tk_flags & RPC_TASK_NO_RETRANS_TIMEOUT) &&
		    rpc_check_connected(task->tk_rqstp))
			वापस;

		अगर (clnt->cl_chatty) अणु
			pr_notice_ratelimited(
				"%s: server %s not responding, timed out\n",
				clnt->cl_program->name,
				task->tk_xprt->servername);
		पूर्ण
		अगर (task->tk_flags & RPC_TASK_TIMEOUT)
			rpc_call_rpcerror(task, -ETIMEDOUT);
		अन्यथा
			__rpc_call_rpcerror(task, -EIO, -ETIMEDOUT);
		वापस;
	पूर्ण

	अगर (!(task->tk_flags & RPC_CALL_MAJORSEEN)) अणु
		task->tk_flags |= RPC_CALL_MAJORSEEN;
		अगर (clnt->cl_chatty) अणु
			pr_notice_ratelimited(
				"%s: server %s not responding, still trying\n",
				clnt->cl_program->name,
				task->tk_xprt->servername);
		पूर्ण
	पूर्ण
	rpc_क्रमce_rebind(clnt);
	/*
	 * Did our request समय out due to an RPCSEC_GSS out-of-sequence
	 * event? RFC2203 requires the server to drop all such requests.
	 */
	rpcauth_invalcred(task);
पूर्ण

/*
 * 7.	Decode the RPC reply
 */
अटल व्योम
call_decode(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_clnt	*clnt = task->tk_client;
	काष्ठा rpc_rqst	*req = task->tk_rqstp;
	काष्ठा xdr_stream xdr;
	पूर्णांक err;

	अगर (!task->tk_msg.rpc_proc->p_decode) अणु
		task->tk_action = rpc_निकास_task;
		वापस;
	पूर्ण

	अगर (task->tk_flags & RPC_CALL_MAJORSEEN) अणु
		अगर (clnt->cl_chatty) अणु
			pr_notice_ratelimited("%s: server %s OK\n",
				clnt->cl_program->name,
				task->tk_xprt->servername);
		पूर्ण
		task->tk_flags &= ~RPC_CALL_MAJORSEEN;
	पूर्ण

	/*
	 * Did we ever call xprt_complete_rqst()? If not, we should assume
	 * the message is incomplete.
	 */
	err = -EAGAIN;
	अगर (!req->rq_reply_bytes_recvd)
		जाओ out;

	/* Ensure that we see all ग_लिखोs made by xprt_complete_rqst()
	 * beक्रमe it changed req->rq_reply_bytes_recvd.
	 */
	smp_rmb();

	req->rq_rcv_buf.len = req->rq_निजी_buf.len;
	trace_rpc_xdr_recvfrom(task, &req->rq_rcv_buf);

	/* Check that the softirq receive buffer is valid */
	WARN_ON(स_भेद(&req->rq_rcv_buf, &req->rq_निजी_buf,
				माप(req->rq_rcv_buf)) != 0);

	xdr_init_decode(&xdr, &req->rq_rcv_buf,
			req->rq_rcv_buf.head[0].iov_base, req);
	err = rpc_decode_header(task, &xdr);
out:
	चयन (err) अणु
	हाल 0:
		task->tk_action = rpc_निकास_task;
		task->tk_status = rpcauth_unwrap_resp(task, &xdr);
		वापस;
	हाल -EAGAIN:
		task->tk_status = 0;
		अगर (task->tk_client->cl_discrtry)
			xprt_conditional_disconnect(req->rq_xprt,
						    req->rq_connect_cookie);
		task->tk_action = call_encode;
		rpc_check_समयout(task);
		अवरोध;
	हाल -EKEYREJECTED:
		task->tk_action = call_reserve;
		rpc_check_समयout(task);
		rpcauth_invalcred(task);
		/* Ensure we obtain a new XID अगर we retry! */
		xprt_release(task);
	पूर्ण
पूर्ण

अटल पूर्णांक
rpc_encode_header(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_clnt *clnt = task->tk_client;
	काष्ठा rpc_rqst	*req = task->tk_rqstp;
	__be32 *p;
	पूर्णांक error;

	error = -EMSGSIZE;
	p = xdr_reserve_space(xdr, RPC_CALLHDRSIZE << 2);
	अगर (!p)
		जाओ out_fail;
	*p++ = req->rq_xid;
	*p++ = rpc_call;
	*p++ = cpu_to_be32(RPC_VERSION);
	*p++ = cpu_to_be32(clnt->cl_prog);
	*p++ = cpu_to_be32(clnt->cl_vers);
	*p   = cpu_to_be32(task->tk_msg.rpc_proc->p_proc);

	error = rpcauth_marshcred(task, xdr);
	अगर (error < 0)
		जाओ out_fail;
	वापस 0;
out_fail:
	trace_rpc_bad_callhdr(task);
	rpc_call_rpcerror(task, error);
	वापस error;
पूर्ण

अटल noअंतरभूत पूर्णांक
rpc_decode_header(काष्ठा rpc_task *task, काष्ठा xdr_stream *xdr)
अणु
	काष्ठा rpc_clnt *clnt = task->tk_client;
	पूर्णांक error;
	__be32 *p;

	/* RFC-1014 says that the representation of XDR data must be a
	 * multiple of four bytes
	 * - अगर it isn't poपूर्णांकer subtraction in the NFS client may give
	 *   undefined results
	 */
	अगर (task->tk_rqstp->rq_rcv_buf.len & 3)
		जाओ out_unparsable;

	p = xdr_अंतरभूत_decode(xdr, 3 * माप(*p));
	अगर (!p)
		जाओ out_unparsable;
	p++;	/* skip XID */
	अगर (*p++ != rpc_reply)
		जाओ out_unparsable;
	अगर (*p++ != rpc_msg_accepted)
		जाओ out_msg_denied;

	error = rpcauth_checkverf(task, xdr);
	अगर (error)
		जाओ out_verअगरier;

	p = xdr_अंतरभूत_decode(xdr, माप(*p));
	अगर (!p)
		जाओ out_unparsable;
	चयन (*p) अणु
	हाल rpc_success:
		वापस 0;
	हाल rpc_prog_unavail:
		trace_rpc__prog_unavail(task);
		error = -EPFNOSUPPORT;
		जाओ out_err;
	हाल rpc_prog_mismatch:
		trace_rpc__prog_mismatch(task);
		error = -EPROTONOSUPPORT;
		जाओ out_err;
	हाल rpc_proc_unavail:
		trace_rpc__proc_unavail(task);
		error = -EOPNOTSUPP;
		जाओ out_err;
	हाल rpc_garbage_args:
	हाल rpc_प्रणाली_err:
		trace_rpc__garbage_args(task);
		error = -EIO;
		अवरोध;
	शेष:
		जाओ out_unparsable;
	पूर्ण

out_garbage:
	clnt->cl_stats->rpcgarbage++;
	अगर (task->tk_garb_retry) अणु
		task->tk_garb_retry--;
		task->tk_action = call_encode;
		वापस -EAGAIN;
	पूर्ण
out_err:
	rpc_call_rpcerror(task, error);
	वापस error;

out_unparsable:
	trace_rpc__unparsable(task);
	error = -EIO;
	जाओ out_garbage;

out_verअगरier:
	trace_rpc_bad_verअगरier(task);
	जाओ out_garbage;

out_msg_denied:
	error = -EACCES;
	p = xdr_अंतरभूत_decode(xdr, माप(*p));
	अगर (!p)
		जाओ out_unparsable;
	चयन (*p++) अणु
	हाल rpc_auth_error:
		अवरोध;
	हाल rpc_mismatch:
		trace_rpc__mismatch(task);
		error = -EPROTONOSUPPORT;
		जाओ out_err;
	शेष:
		जाओ out_unparsable;
	पूर्ण

	p = xdr_अंतरभूत_decode(xdr, माप(*p));
	अगर (!p)
		जाओ out_unparsable;
	चयन (*p++) अणु
	हाल rpc_autherr_rejectedcred:
	हाल rpc_autherr_rejectedverf:
	हाल rpcsec_gsserr_credproblem:
	हाल rpcsec_gsserr_ctxproblem:
		अगर (!task->tk_cred_retry)
			अवरोध;
		task->tk_cred_retry--;
		trace_rpc__stale_creds(task);
		वापस -EKEYREJECTED;
	हाल rpc_autherr_badcred:
	हाल rpc_autherr_badverf:
		/* possibly garbled cred/verf? */
		अगर (!task->tk_garb_retry)
			अवरोध;
		task->tk_garb_retry--;
		trace_rpc__bad_creds(task);
		task->tk_action = call_encode;
		वापस -EAGAIN;
	हाल rpc_autherr_tooweak:
		trace_rpc__auth_tooweak(task);
		pr_warn("RPC: server %s requires stronger authentication.\n",
			task->tk_xprt->servername);
		अवरोध;
	शेष:
		जाओ out_unparsable;
	पूर्ण
	जाओ out_err;
पूर्ण

अटल व्योम rpcproc_encode_null(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		स्थिर व्योम *obj)
अणु
पूर्ण

अटल पूर्णांक rpcproc_decode_null(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		व्योम *obj)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rpc_procinfo rpcproc_null = अणु
	.p_encode = rpcproc_encode_null,
	.p_decode = rpcproc_decode_null,
पूर्ण;

अटल पूर्णांक rpc_ping(काष्ठा rpc_clnt *clnt)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &rpcproc_null,
	पूर्ण;
	पूर्णांक err;
	err = rpc_call_sync(clnt, &msg, RPC_TASK_SOFT | RPC_TASK_SOFTCONN |
			    RPC_TASK_शून्यCREDS);
	वापस err;
पूर्ण

अटल
काष्ठा rpc_task *rpc_call_null_helper(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt *xprt, काष्ठा rpc_cred *cred, पूर्णांक flags,
		स्थिर काष्ठा rpc_call_ops *ops, व्योम *data)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &rpcproc_null,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = clnt,
		.rpc_xprt = xprt,
		.rpc_message = &msg,
		.rpc_op_cred = cred,
		.callback_ops = (ops != शून्य) ? ops : &rpc_शेष_ops,
		.callback_data = data,
		.flags = flags | RPC_TASK_SOFT | RPC_TASK_SOFTCONN |
			 RPC_TASK_शून्यCREDS,
	पूर्ण;

	वापस rpc_run_task(&task_setup_data);
पूर्ण

काष्ठा rpc_task *rpc_call_null(काष्ठा rpc_clnt *clnt, काष्ठा rpc_cred *cred, पूर्णांक flags)
अणु
	वापस rpc_call_null_helper(clnt, शून्य, cred, flags, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_call_null);

काष्ठा rpc_cb_add_xprt_calldata अणु
	काष्ठा rpc_xprt_चयन *xps;
	काष्ठा rpc_xprt *xprt;
पूर्ण;

अटल व्योम rpc_cb_add_xprt_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा rpc_cb_add_xprt_calldata *data = calldata;

	अगर (task->tk_status == 0)
		rpc_xprt_चयन_add_xprt(data->xps, data->xprt);
पूर्ण

अटल व्योम rpc_cb_add_xprt_release(व्योम *calldata)
अणु
	काष्ठा rpc_cb_add_xprt_calldata *data = calldata;

	xprt_put(data->xprt);
	xprt_चयन_put(data->xps);
	kमुक्त(data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops rpc_cb_add_xprt_call_ops = अणु
	.rpc_call_करोne = rpc_cb_add_xprt_करोne,
	.rpc_release = rpc_cb_add_xprt_release,
पूर्ण;

/**
 * rpc_clnt_test_and_add_xprt - Test and add a new transport to a rpc_clnt
 * @clnt: poपूर्णांकer to काष्ठा rpc_clnt
 * @xps: poपूर्णांकer to काष्ठा rpc_xprt_चयन,
 * @xprt: poपूर्णांकer काष्ठा rpc_xprt
 * @dummy: unused
 */
पूर्णांक rpc_clnt_test_and_add_xprt(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt_चयन *xps, काष्ठा rpc_xprt *xprt,
		व्योम *dummy)
अणु
	काष्ठा rpc_cb_add_xprt_calldata *data;
	काष्ठा rpc_task *task;

	data = kदो_स्मृति(माप(*data), GFP_NOFS);
	अगर (!data)
		वापस -ENOMEM;
	data->xps = xprt_चयन_get(xps);
	data->xprt = xprt_get(xprt);
	अगर (rpc_xprt_चयन_has_addr(data->xps, (काष्ठा sockaddr *)&xprt->addr)) अणु
		rpc_cb_add_xprt_release(data);
		जाओ success;
	पूर्ण

	task = rpc_call_null_helper(clnt, xprt, शून्य, RPC_TASK_ASYNC,
			&rpc_cb_add_xprt_call_ops, data);

	rpc_put_task(task);
success:
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_test_and_add_xprt);

/**
 * rpc_clnt_setup_test_and_add_xprt()
 *
 * This is an rpc_clnt_add_xprt setup() function which वापसs 1 so:
 *   1) caller of the test function must dereference the rpc_xprt_चयन
 *   and the rpc_xprt.
 *   2) test function must call rpc_xprt_चयन_add_xprt, usually in
 *   the rpc_call_करोne routine.
 *
 * Upon success (वापस of 1), the test function adds the new
 * transport to the rpc_clnt xprt चयन
 *
 * @clnt: काष्ठा rpc_clnt to get the new transport
 * @xps:  the rpc_xprt_चयन to hold the new transport
 * @xprt: the rpc_xprt to test
 * @data: a काष्ठा rpc_add_xprt_test poपूर्णांकer that holds the test function
 *        and test function call data
 */
पूर्णांक rpc_clnt_setup_test_and_add_xprt(काष्ठा rpc_clnt *clnt,
				     काष्ठा rpc_xprt_चयन *xps,
				     काष्ठा rpc_xprt *xprt,
				     व्योम *data)
अणु
	काष्ठा rpc_task *task;
	काष्ठा rpc_add_xprt_test *xtest = (काष्ठा rpc_add_xprt_test *)data;
	पूर्णांक status = -EADDRINUSE;

	xprt = xprt_get(xprt);
	xprt_चयन_get(xps);

	अगर (rpc_xprt_चयन_has_addr(xps, (काष्ठा sockaddr *)&xprt->addr))
		जाओ out_err;

	/* Test the connection */
	task = rpc_call_null_helper(clnt, xprt, शून्य, 0, शून्य, शून्य);
	अगर (IS_ERR(task)) अणु
		status = PTR_ERR(task);
		जाओ out_err;
	पूर्ण
	status = task->tk_status;
	rpc_put_task(task);

	अगर (status < 0)
		जाओ out_err;

	/* rpc_xprt_चयन and rpc_xprt are deferrenced by add_xprt_test() */
	xtest->add_xprt_test(clnt, xprt, xtest->data);

	xprt_put(xprt);
	xprt_चयन_put(xps);

	/* so that rpc_clnt_add_xprt करोes not call rpc_xprt_चयन_add_xprt */
	वापस 1;
out_err:
	xprt_put(xprt);
	xprt_चयन_put(xps);
	pr_info("RPC:   rpc_clnt_test_xprt failed: %d addr %s not added\n",
		status, xprt->address_strings[RPC_DISPLAY_ADDR]);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_setup_test_and_add_xprt);

/**
 * rpc_clnt_add_xprt - Add a new transport to a rpc_clnt
 * @clnt: poपूर्णांकer to काष्ठा rpc_clnt
 * @xprtargs: poपूर्णांकer to काष्ठा xprt_create
 * @setup: callback to test and/or set up the connection
 * @data: poपूर्णांकer to setup function data
 *
 * Creates a new transport using the parameters set in args and
 * adds it to clnt.
 * If ping is set, then test that connectivity succeeds beक्रमe
 * adding the new transport.
 *
 */
पूर्णांक rpc_clnt_add_xprt(काष्ठा rpc_clnt *clnt,
		काष्ठा xprt_create *xprtargs,
		पूर्णांक (*setup)(काष्ठा rpc_clnt *,
			काष्ठा rpc_xprt_चयन *,
			काष्ठा rpc_xprt *,
			व्योम *),
		व्योम *data)
अणु
	काष्ठा rpc_xprt_चयन *xps;
	काष्ठा rpc_xprt *xprt;
	अचिन्हित दीर्घ connect_समयout;
	अचिन्हित दीर्घ reconnect_समयout;
	अचिन्हित अक्षर resvport, reuseport;
	पूर्णांक ret = 0;

	rcu_पढ़ो_lock();
	xps = xprt_चयन_get(rcu_dereference(clnt->cl_xpi.xpi_xpचयन));
	xprt = xprt_iter_xprt(&clnt->cl_xpi);
	अगर (xps == शून्य || xprt == शून्य) अणु
		rcu_पढ़ो_unlock();
		xprt_चयन_put(xps);
		वापस -EAGAIN;
	पूर्ण
	resvport = xprt->resvport;
	reuseport = xprt->reuseport;
	connect_समयout = xprt->connect_समयout;
	reconnect_समयout = xprt->max_reconnect_समयout;
	rcu_पढ़ो_unlock();

	xprt = xprt_create_transport(xprtargs);
	अगर (IS_ERR(xprt)) अणु
		ret = PTR_ERR(xprt);
		जाओ out_put_चयन;
	पूर्ण
	xprt->resvport = resvport;
	xprt->reuseport = reuseport;
	अगर (xprt->ops->set_connect_समयout != शून्य)
		xprt->ops->set_connect_समयout(xprt,
				connect_समयout,
				reconnect_समयout);

	rpc_xprt_चयन_set_roundrobin(xps);
	अगर (setup) अणु
		ret = setup(clnt, xps, xprt, data);
		अगर (ret != 0)
			जाओ out_put_xprt;
	पूर्ण
	rpc_xprt_चयन_add_xprt(xps, xprt);
out_put_xprt:
	xprt_put(xprt);
out_put_चयन:
	xprt_चयन_put(xps);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_add_xprt);

काष्ठा connect_समयout_data अणु
	अचिन्हित दीर्घ connect_समयout;
	अचिन्हित दीर्घ reconnect_समयout;
पूर्ण;

अटल पूर्णांक
rpc_xprt_set_connect_समयout(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt *xprt,
		व्योम *data)
अणु
	काष्ठा connect_समयout_data *समयo = data;

	अगर (xprt->ops->set_connect_समयout)
		xprt->ops->set_connect_समयout(xprt,
				समयo->connect_समयout,
				समयo->reconnect_समयout);
	वापस 0;
पूर्ण

व्योम
rpc_set_connect_समयout(काष्ठा rpc_clnt *clnt,
		अचिन्हित दीर्घ connect_समयout,
		अचिन्हित दीर्घ reconnect_समयout)
अणु
	काष्ठा connect_समयout_data समयout = अणु
		.connect_समयout = connect_समयout,
		.reconnect_समयout = reconnect_समयout,
	पूर्ण;
	rpc_clnt_iterate_क्रम_each_xprt(clnt,
			rpc_xprt_set_connect_समयout,
			&समयout);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_set_connect_समयout);

व्योम rpc_clnt_xprt_चयन_put(काष्ठा rpc_clnt *clnt)
अणु
	rcu_पढ़ो_lock();
	xprt_चयन_put(rcu_dereference(clnt->cl_xpi.xpi_xpचयन));
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_xprt_चयन_put);

व्योम rpc_clnt_xprt_चयन_add_xprt(काष्ठा rpc_clnt *clnt, काष्ठा rpc_xprt *xprt)
अणु
	rcu_पढ़ो_lock();
	rpc_xprt_चयन_add_xprt(rcu_dereference(clnt->cl_xpi.xpi_xpचयन),
				 xprt);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_xprt_चयन_add_xprt);

bool rpc_clnt_xprt_चयन_has_addr(काष्ठा rpc_clnt *clnt,
				   स्थिर काष्ठा sockaddr *sap)
अणु
	काष्ठा rpc_xprt_चयन *xps;
	bool ret;

	rcu_पढ़ो_lock();
	xps = rcu_dereference(clnt->cl_xpi.xpi_xpचयन);
	ret = rpc_xprt_चयन_has_addr(xps, sap);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_xprt_चयन_has_addr);

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
अटल व्योम rpc_show_header(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "-pid- flgs status -client- --rqstp- "
		"-timeout ---ops--\n");
पूर्ण

अटल व्योम rpc_show_task(स्थिर काष्ठा rpc_clnt *clnt,
			  स्थिर काष्ठा rpc_task *task)
अणु
	स्थिर अक्षर *rpc_रुकोq = "none";

	अगर (RPC_IS_QUEUED(task))
		rpc_रुकोq = rpc_qname(task->tk_रुकोqueue);

	prपूर्णांकk(KERN_INFO "%5u %04x %6d %8p %8p %8ld %8p %sv%u %s a:%ps q:%s\n",
		task->tk_pid, task->tk_flags, task->tk_status,
		clnt, task->tk_rqstp, rpc_task_समयout(task), task->tk_ops,
		clnt->cl_program->name, clnt->cl_vers, rpc_proc_name(task),
		task->tk_action, rpc_रुकोq);
पूर्ण

व्योम rpc_show_tasks(काष्ठा net *net)
अणु
	काष्ठा rpc_clnt *clnt;
	काष्ठा rpc_task *task;
	पूर्णांक header = 0;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	spin_lock(&sn->rpc_client_lock);
	list_क्रम_each_entry(clnt, &sn->all_clients, cl_clients) अणु
		spin_lock(&clnt->cl_lock);
		list_क्रम_each_entry(task, &clnt->cl_tasks, tk_task) अणु
			अगर (!header) अणु
				rpc_show_header();
				header++;
			पूर्ण
			rpc_show_task(clnt, task);
		पूर्ण
		spin_unlock(&clnt->cl_lock);
	पूर्ण
	spin_unlock(&sn->rpc_client_lock);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SUNRPC_SWAP)
अटल पूर्णांक
rpc_clnt_swap_activate_callback(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt *xprt,
		व्योम *dummy)
अणु
	वापस xprt_enable_swap(xprt);
पूर्ण

पूर्णांक
rpc_clnt_swap_activate(काष्ठा rpc_clnt *clnt)
अणु
	अगर (atomic_inc_वापस(&clnt->cl_swapper) == 1)
		वापस rpc_clnt_iterate_क्रम_each_xprt(clnt,
				rpc_clnt_swap_activate_callback, शून्य);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_swap_activate);

अटल पूर्णांक
rpc_clnt_swap_deactivate_callback(काष्ठा rpc_clnt *clnt,
		काष्ठा rpc_xprt *xprt,
		व्योम *dummy)
अणु
	xprt_disable_swap(xprt);
	वापस 0;
पूर्ण

व्योम
rpc_clnt_swap_deactivate(काष्ठा rpc_clnt *clnt)
अणु
	अगर (atomic_dec_अगर_positive(&clnt->cl_swapper) == 0)
		rpc_clnt_iterate_क्रम_each_xprt(clnt,
				rpc_clnt_swap_deactivate_callback, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(rpc_clnt_swap_deactivate);
#पूर्ण_अगर /* CONFIG_SUNRPC_SWAP */
