<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Helper routines क्रम the NFS client caches
 *
 * Copyright (c) 2009 Trond Myklebust <Trond.Myklebust@netapp.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/sunrpc/cache.h>
#समावेश <linux/atomic.h>

/*
 * Deferred request handling
 */
काष्ठा nfs_cache_defer_req अणु
	काष्ठा cache_req req;
	काष्ठा cache_deferred_req deferred_req;
	काष्ठा completion completion;
	refcount_t count;
पूर्ण;

बाह्य पूर्णांक nfs_cache_upcall(काष्ठा cache_detail *cd, अक्षर *entry_name);
बाह्य काष्ठा nfs_cache_defer_req *nfs_cache_defer_req_alloc(व्योम);
बाह्य व्योम nfs_cache_defer_req_put(काष्ठा nfs_cache_defer_req *dreq);
बाह्य पूर्णांक nfs_cache_रुको_क्रम_upcall(काष्ठा nfs_cache_defer_req *dreq);

बाह्य पूर्णांक nfs_cache_रेजिस्टर_net(काष्ठा net *net, काष्ठा cache_detail *cd);
बाह्य व्योम nfs_cache_unरेजिस्टर_net(काष्ठा net *net, काष्ठा cache_detail *cd);
बाह्य पूर्णांक nfs_cache_रेजिस्टर_sb(काष्ठा super_block *sb,
				 काष्ठा cache_detail *cd);
बाह्य व्योम nfs_cache_unरेजिस्टर_sb(काष्ठा super_block *sb,
				    काष्ठा cache_detail *cd);
