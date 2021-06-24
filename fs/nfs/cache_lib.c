<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/cache_lib.c
 *
 * Helper routines क्रम the NFS client caches
 *
 * Copyright (c) 2009 Trond Myklebust <Trond.Myklebust@netapp.com>
 */
#समावेश <linux/kmod.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunrpc/cache.h>
#समावेश <linux/sunrpc/rpc_pipe_fs.h>
#समावेश <net/net_namespace.h>

#समावेश "cache_lib.h"

#घोषणा NFS_CACHE_UPCALL_PATHLEN 256
#घोषणा NFS_CACHE_UPCALL_TIMEOUT 15

अटल अक्षर nfs_cache_getent_prog[NFS_CACHE_UPCALL_PATHLEN] =
				"/sbin/nfs_cache_getent";
अटल अचिन्हित दीर्घ nfs_cache_getent_समयout = NFS_CACHE_UPCALL_TIMEOUT;

module_param_string(cache_getent, nfs_cache_getent_prog,
		माप(nfs_cache_getent_prog), 0600);
MODULE_PARM_DESC(cache_getent, "Path to the client cache upcall program");
module_param_named(cache_getent_समयout, nfs_cache_getent_समयout, uदीर्घ, 0600);
MODULE_PARM_DESC(cache_getent_समयout, "Timeout (in seconds) after which "
		"the cache upcall is assumed to have failed");

पूर्णांक nfs_cache_upcall(काष्ठा cache_detail *cd, अक्षर *entry_name)
अणु
	अटल अक्षर *envp[] = अणु "HOME=/",
		"TERM=linux",
		"PATH=/sbin:/usr/sbin:/bin:/usr/bin",
		शून्य
	पूर्ण;
	अक्षर *argv[] = अणु
		nfs_cache_getent_prog,
		cd->name,
		entry_name,
		शून्य
	पूर्ण;
	पूर्णांक ret = -EACCES;

	अगर (nfs_cache_getent_prog[0] == '\0')
		जाओ out;
	ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
	/*
	 * Disable the upcall mechanism अगर we're getting an ENOENT or
	 * EACCES error. The admin can re-enable it on the fly by using
	 * sysfs to set the 'cache_getent' parameter once the problem
	 * has been fixed.
	 */
	अगर (ret == -ENOENT || ret == -EACCES)
		nfs_cache_getent_prog[0] = '\0';
out:
	वापस ret > 0 ? 0 : ret;
पूर्ण

/*
 * Deferred request handling
 */
व्योम nfs_cache_defer_req_put(काष्ठा nfs_cache_defer_req *dreq)
अणु
	अगर (refcount_dec_and_test(&dreq->count))
		kमुक्त(dreq);
पूर्ण

अटल व्योम nfs_dns_cache_revisit(काष्ठा cache_deferred_req *d, पूर्णांक toomany)
अणु
	काष्ठा nfs_cache_defer_req *dreq;

	dreq = container_of(d, काष्ठा nfs_cache_defer_req, deferred_req);

	complete(&dreq->completion);
	nfs_cache_defer_req_put(dreq);
पूर्ण

अटल काष्ठा cache_deferred_req *nfs_dns_cache_defer(काष्ठा cache_req *req)
अणु
	काष्ठा nfs_cache_defer_req *dreq;

	dreq = container_of(req, काष्ठा nfs_cache_defer_req, req);
	dreq->deferred_req.revisit = nfs_dns_cache_revisit;
	refcount_inc(&dreq->count);

	वापस &dreq->deferred_req;
पूर्ण

काष्ठा nfs_cache_defer_req *nfs_cache_defer_req_alloc(व्योम)
अणु
	काष्ठा nfs_cache_defer_req *dreq;

	dreq = kzalloc(माप(*dreq), GFP_KERNEL);
	अगर (dreq) अणु
		init_completion(&dreq->completion);
		refcount_set(&dreq->count, 1);
		dreq->req.defer = nfs_dns_cache_defer;
	पूर्ण
	वापस dreq;
पूर्ण

पूर्णांक nfs_cache_रुको_क्रम_upcall(काष्ठा nfs_cache_defer_req *dreq)
अणु
	अगर (रुको_क्रम_completion_समयout(&dreq->completion,
			nfs_cache_getent_समयout * HZ) == 0)
		वापस -ETIMEDOUT;
	वापस 0;
पूर्ण

पूर्णांक nfs_cache_रेजिस्टर_sb(काष्ठा super_block *sb, काष्ठा cache_detail *cd)
अणु
	पूर्णांक ret;
	काष्ठा dentry *dir;

	dir = rpc_d_lookup_sb(sb, "cache");
	ret = sunrpc_cache_रेजिस्टर_pipefs(dir, cd->name, 0600, cd);
	dput(dir);
	वापस ret;
पूर्ण

पूर्णांक nfs_cache_रेजिस्टर_net(काष्ठा net *net, काष्ठा cache_detail *cd)
अणु
	काष्ठा super_block *pipefs_sb;
	पूर्णांक ret = 0;

	sunrpc_init_cache_detail(cd);
	pipefs_sb = rpc_get_sb_net(net);
	अगर (pipefs_sb) अणु
		ret = nfs_cache_रेजिस्टर_sb(pipefs_sb, cd);
		rpc_put_sb_net(net);
		अगर (ret)
			sunrpc_destroy_cache_detail(cd);
	पूर्ण
	वापस ret;
पूर्ण

व्योम nfs_cache_unरेजिस्टर_sb(काष्ठा super_block *sb, काष्ठा cache_detail *cd)
अणु
	sunrpc_cache_unरेजिस्टर_pipefs(cd);
पूर्ण

व्योम nfs_cache_unरेजिस्टर_net(काष्ठा net *net, काष्ठा cache_detail *cd)
अणु
	काष्ठा super_block *pipefs_sb;

	pipefs_sb = rpc_get_sb_net(net);
	अगर (pipefs_sb) अणु
		nfs_cache_unरेजिस्टर_sb(pipefs_sb, cd);
		rpc_put_sb_net(net);
	पूर्ण
	sunrpc_destroy_cache_detail(cd);
पूर्ण
