<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/sunrpc_syms.c
 *
 * Symbols exported by the sunrpc module.
 *
 * Copyright (C) 1997 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/module.h>

#समावेश <linux/types.h>
#समावेश <linux/uपन.स>
#समावेश <linux/unistd.h>
#समावेश <linux/init.h>

#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/auth.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <linux/sunrpc/xprtsock.h>

#समावेश "sunrpc.h"
#समावेश "netns.h"

अचिन्हित पूर्णांक sunrpc_net_id;
EXPORT_SYMBOL_GPL(sunrpc_net_id);

अटल __net_init पूर्णांक sunrpc_init_net(काष्ठा net *net)
अणु
	पूर्णांक err;
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	err = rpc_proc_init(net);
	अगर (err)
		जाओ err_proc;

	err = ip_map_cache_create(net);
	अगर (err)
		जाओ err_ipmap;

	err = unix_gid_cache_create(net);
	अगर (err)
		जाओ err_unixgid;

	err = rpc_pipefs_init_net(net);
	अगर (err)
		जाओ err_pipefs;

	INIT_LIST_HEAD(&sn->all_clients);
	spin_lock_init(&sn->rpc_client_lock);
	spin_lock_init(&sn->rpcb_clnt_lock);
	वापस 0;

err_pipefs:
	unix_gid_cache_destroy(net);
err_unixgid:
	ip_map_cache_destroy(net);
err_ipmap:
	rpc_proc_निकास(net);
err_proc:
	वापस err;
पूर्ण

अटल __net_निकास व्योम sunrpc_निकास_net(काष्ठा net *net)
अणु
	काष्ठा sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	rpc_pipefs_निकास_net(net);
	unix_gid_cache_destroy(net);
	ip_map_cache_destroy(net);
	rpc_proc_निकास(net);
	WARN_ON_ONCE(!list_empty(&sn->all_clients));
पूर्ण

अटल काष्ठा pernet_operations sunrpc_net_ops = अणु
	.init = sunrpc_init_net,
	.निकास = sunrpc_निकास_net,
	.id = &sunrpc_net_id,
	.size = माप(काष्ठा sunrpc_net),
पूर्ण;

अटल पूर्णांक __init
init_sunrpc(व्योम)
अणु
	पूर्णांक err = rpc_init_mempool();
	अगर (err)
		जाओ out;
	err = rpcauth_init_module();
	अगर (err)
		जाओ out2;

	cache_initialize();

	err = रेजिस्टर_pernet_subsys(&sunrpc_net_ops);
	अगर (err)
		जाओ out3;

	err = रेजिस्टर_rpc_pipefs();
	अगर (err)
		जाओ out4;

	sunrpc_debugfs_init();
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
	rpc_रेजिस्टर_sysctl();
#पूर्ण_अगर
	svc_init_xprt_sock();	/* svc sock transport */
	init_socket_xprt();	/* clnt sock transport */
	वापस 0;

out4:
	unरेजिस्टर_pernet_subsys(&sunrpc_net_ops);
out3:
	rpcauth_हटाओ_module();
out2:
	rpc_destroy_mempool();
out:
	वापस err;
पूर्ण

अटल व्योम __निकास
cleanup_sunrpc(व्योम)
अणु
	rpc_cleanup_clids();
	rpcauth_हटाओ_module();
	cleanup_socket_xprt();
	svc_cleanup_xprt_sock();
	sunrpc_debugfs_निकास();
	unरेजिस्टर_rpc_pipefs();
	rpc_destroy_mempool();
	unरेजिस्टर_pernet_subsys(&sunrpc_net_ops);
	auth_करोमुख्य_cleanup();
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
	rpc_unरेजिस्टर_sysctl();
#पूर्ण_अगर
	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */
पूर्ण
MODULE_LICENSE("GPL");
fs_initcall(init_sunrpc); /* Ensure we're initialised beक्रमe nfs */
module_निकास(cleanup_sunrpc);
