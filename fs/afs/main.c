<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS client file प्रणाली
 *
 * Copyright (C) 2002,5 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/completion.h>
#समावेश <linux/sched.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/proc_fs.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश "internal.h"

MODULE_DESCRIPTION("AFS Client File System");
MODULE_AUTHOR("Red Hat, Inc.");
MODULE_LICENSE("GPL");

अचिन्हित afs_debug;
module_param_named(debug, afs_debug, uपूर्णांक, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(debug, "AFS debugging mask");

अटल अक्षर *rootcell;

module_param(rootcell, अक्षरp, 0);
MODULE_PARM_DESC(rootcell, "root AFS cell name and VL server IP addr list");

काष्ठा workqueue_काष्ठा *afs_wq;
अटल काष्ठा proc_dir_entry *afs_proc_symlink;

#अगर defined(CONFIG_ALPHA)
स्थिर अक्षर afs_init_sysname[] = "alpha_linux26";
#या_अगर defined(CONFIG_X86_64)
स्थिर अक्षर afs_init_sysname[] = "amd64_linux26";
#या_अगर defined(CONFIG_ARM)
स्थिर अक्षर afs_init_sysname[] = "arm_linux26";
#या_अगर defined(CONFIG_ARM64)
स्थिर अक्षर afs_init_sysname[] = "aarch64_linux26";
#या_अगर defined(CONFIG_X86_32)
स्थिर अक्षर afs_init_sysname[] = "i386_linux26";
#या_अगर defined(CONFIG_IA64)
स्थिर अक्षर afs_init_sysname[] = "ia64_linux26";
#या_अगर defined(CONFIG_PPC64)
स्थिर अक्षर afs_init_sysname[] = "ppc64_linux26";
#या_अगर defined(CONFIG_PPC32)
स्थिर अक्षर afs_init_sysname[] = "ppc_linux26";
#या_अगर defined(CONFIG_S390)
#अगर_घोषित CONFIG_64BIT
स्थिर अक्षर afs_init_sysname[] = "s390x_linux26";
#अन्यथा
स्थिर अक्षर afs_init_sysname[] = "s390_linux26";
#पूर्ण_अगर
#या_अगर defined(CONFIG_SPARC64)
स्थिर अक्षर afs_init_sysname[] = "sparc64_linux26";
#या_अगर defined(CONFIG_SPARC32)
स्थिर अक्षर afs_init_sysname[] = "sparc_linux26";
#अन्यथा
स्थिर अक्षर afs_init_sysname[] = "unknown_linux26";
#पूर्ण_अगर

/*
 * Initialise an AFS network namespace record.
 */
अटल पूर्णांक __net_init afs_net_init(काष्ठा net *net_ns)
अणु
	काष्ठा afs_sysnames *sysnames;
	काष्ठा afs_net *net = afs_net(net_ns);
	पूर्णांक ret;

	net->net = net_ns;
	net->live = true;
	generate_अक्रमom_uuid((अचिन्हित अक्षर *)&net->uuid);

	INIT_WORK(&net->अक्षरge_pपुनः_स्मृतिation_work, afs_अक्षरge_pपुनः_स्मृतिation);
	mutex_init(&net->socket_mutex);

	net->cells = RB_ROOT;
	init_rwsem(&net->cells_lock);
	INIT_WORK(&net->cells_manager, afs_manage_cells);
	समयr_setup(&net->cells_समयr, afs_cells_समयr, 0);

	mutex_init(&net->cells_alias_lock);
	mutex_init(&net->proc_cells_lock);
	INIT_HLIST_HEAD(&net->proc_cells);

	seqlock_init(&net->fs_lock);
	net->fs_servers = RB_ROOT;
	INIT_LIST_HEAD(&net->fs_probe_fast);
	INIT_LIST_HEAD(&net->fs_probe_slow);
	INIT_HLIST_HEAD(&net->fs_proc);

	INIT_HLIST_HEAD(&net->fs_addresses4);
	INIT_HLIST_HEAD(&net->fs_addresses6);
	seqlock_init(&net->fs_addr_lock);

	INIT_WORK(&net->fs_manager, afs_manage_servers);
	समयr_setup(&net->fs_समयr, afs_servers_समयr, 0);
	INIT_WORK(&net->fs_prober, afs_fs_probe_dispatcher);
	समयr_setup(&net->fs_probe_समयr, afs_fs_probe_समयr, 0);
	atomic_set(&net->servers_outstanding, 1);

	ret = -ENOMEM;
	sysnames = kzalloc(माप(*sysnames), GFP_KERNEL);
	अगर (!sysnames)
		जाओ error_sysnames;
	sysnames->subs[0] = (अक्षर *)&afs_init_sysname;
	sysnames->nr = 1;
	refcount_set(&sysnames->usage, 1);
	net->sysnames = sysnames;
	rwlock_init(&net->sysnames_lock);

	/* Register the /proc stuff */
	ret = afs_proc_init(net);
	अगर (ret < 0)
		जाओ error_proc;

	/* Initialise the cell DB */
	ret = afs_cell_init(net, rootcell);
	अगर (ret < 0)
		जाओ error_cell_init;

	/* Create the RxRPC transport */
	ret = afs_खोलो_socket(net);
	अगर (ret < 0)
		जाओ error_खोलो_socket;

	वापस 0;

error_खोलो_socket:
	net->live = false;
	afs_fs_probe_cleanup(net);
	afs_cell_purge(net);
	afs_purge_servers(net);
error_cell_init:
	net->live = false;
	afs_proc_cleanup(net);
error_proc:
	afs_put_sysnames(net->sysnames);
error_sysnames:
	net->live = false;
	वापस ret;
पूर्ण

/*
 * Clean up and destroy an AFS network namespace record.
 */
अटल व्योम __net_निकास afs_net_निकास(काष्ठा net *net_ns)
अणु
	काष्ठा afs_net *net = afs_net(net_ns);

	net->live = false;
	afs_fs_probe_cleanup(net);
	afs_cell_purge(net);
	afs_purge_servers(net);
	afs_बंद_socket(net);
	afs_proc_cleanup(net);
	afs_put_sysnames(net->sysnames);
पूर्ण

अटल काष्ठा pernet_operations afs_net_ops = अणु
	.init	= afs_net_init,
	.निकास	= afs_net_निकास,
	.id	= &afs_net_id,
	.size	= माप(काष्ठा afs_net),
पूर्ण;

/*
 * initialise the AFS client FS module
 */
अटल पूर्णांक __init afs_init(व्योम)
अणु
	पूर्णांक ret = -ENOMEM;

	prपूर्णांकk(KERN_INFO "kAFS: Red Hat AFS client v0.1 registering.\n");

	afs_wq = alloc_workqueue("afs", 0, 0);
	अगर (!afs_wq)
		जाओ error_afs_wq;
	afs_async_calls = alloc_workqueue("kafsd", WQ_MEM_RECLAIM, 0);
	अगर (!afs_async_calls)
		जाओ error_async;
	afs_lock_manager = alloc_workqueue("kafs_lockd", WQ_MEM_RECLAIM, 0);
	अगर (!afs_lock_manager)
		जाओ error_lockmgr;

#अगर_घोषित CONFIG_AFS_FSCACHE
	/* we want to be able to cache */
	ret = fscache_रेजिस्टर_netfs(&afs_cache_netfs);
	अगर (ret < 0)
		जाओ error_cache;
#पूर्ण_अगर

	ret = रेजिस्टर_pernet_device(&afs_net_ops);
	अगर (ret < 0)
		जाओ error_net;

	/* रेजिस्टर the fileप्रणालीs */
	ret = afs_fs_init();
	अगर (ret < 0)
		जाओ error_fs;

	afs_proc_symlink = proc_symlink("fs/afs", शून्य, "../self/net/afs");
	अगर (!afs_proc_symlink) अणु
		ret = -ENOMEM;
		जाओ error_proc;
	पूर्ण

	वापस ret;

error_proc:
	afs_fs_निकास();
error_fs:
	unरेजिस्टर_pernet_device(&afs_net_ops);
error_net:
#अगर_घोषित CONFIG_AFS_FSCACHE
	fscache_unरेजिस्टर_netfs(&afs_cache_netfs);
error_cache:
#पूर्ण_अगर
	destroy_workqueue(afs_lock_manager);
error_lockmgr:
	destroy_workqueue(afs_async_calls);
error_async:
	destroy_workqueue(afs_wq);
error_afs_wq:
	rcu_barrier();
	prपूर्णांकk(KERN_ERR "kAFS: failed to register: %d\n", ret);
	वापस ret;
पूर्ण

/* XXX late_initcall is kludgy, but the only alternative seems to create
 * a transport upon the first mount, which is worse. Or is it?
 */
late_initcall(afs_init);	/* must be called after net/ to create socket */

/*
 * clean up on module removal
 */
अटल व्योम __निकास afs_निकास(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "kAFS: Red Hat AFS client v0.1 unregistering.\n");

	proc_हटाओ(afs_proc_symlink);
	afs_fs_निकास();
	unरेजिस्टर_pernet_device(&afs_net_ops);
#अगर_घोषित CONFIG_AFS_FSCACHE
	fscache_unरेजिस्टर_netfs(&afs_cache_netfs);
#पूर्ण_अगर
	destroy_workqueue(afs_lock_manager);
	destroy_workqueue(afs_async_calls);
	destroy_workqueue(afs_wq);
	afs_clean_up_permit_cache();
	rcu_barrier();
पूर्ण

module_निकास(afs_निकास);
