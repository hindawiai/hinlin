<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Request reply cache. This was heavily inspired by the
 * implementation in 4.3BSD/4.4BSD.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित NFSCACHE_H
#घोषणा NFSCACHE_H

#समावेश <linux/sunrpc/svc.h>
#समावेश "netns.h"

/*
 * Representation of a reply cache entry.
 *
 * Note that we use a sockaddr_in6 to hold the address instead of the more
 * typical sockaddr_storage. This is क्रम space reasons, since sockaddr_storage
 * is much larger than a sockaddr_in6.
 */
काष्ठा svc_cacherep अणु
	काष्ठा अणु
		/* Keep often-पढ़ो xid, csum in the same cache line: */
		__be32			k_xid;
		__wsum			k_csum;
		u32			k_proc;
		u32			k_prot;
		u32			k_vers;
		अचिन्हित पूर्णांक		k_len;
		काष्ठा sockaddr_in6	k_addr;
	पूर्ण c_key;

	काष्ठा rb_node		c_node;
	काष्ठा list_head	c_lru;
	अचिन्हित अक्षर		c_state,	/* unused, inprog, करोne */
				c_type,		/* status, buffer */
				c_secure : 1;	/* req came from port < 1024 */
	अचिन्हित दीर्घ		c_बारtamp;
	जोड़ अणु
		काष्ठा kvec	u_vec;
		__be32		u_status;
	पूर्ण			c_u;
पूर्ण;

#घोषणा c_replvec		c_u.u_vec
#घोषणा c_replstat		c_u.u_status

/* cache entry states */
क्रमागत अणु
	RC_UNUSED,
	RC_INPROG,
	RC_DONE
पूर्ण;

/* वापस values */
क्रमागत अणु
	RC_DROPIT,
	RC_REPLY,
	RC_DOIT
पूर्ण;

/*
 * Cache types.
 * We may want to add more types one day, e.g. क्रम diropres and
 * attrstat replies. Using cache entries with fixed length instead
 * of buffer poपूर्णांकers may be more efficient.
 */
क्रमागत अणु
	RC_NOCACHE,
	RC_REPLSTAT,
	RC_REPLBUFF,
पूर्ण;

/* Cache entries expire after this समय period */
#घोषणा RC_EXPIRE		(120 * HZ)

/* Checksum this amount of the request */
#घोषणा RC_CSUMLEN		(256U)

पूर्णांक	nfsd_drc_slab_create(व्योम);
व्योम	nfsd_drc_slab_मुक्त(व्योम);
पूर्णांक	nfsd_reply_cache_init(काष्ठा nfsd_net *);
व्योम	nfsd_reply_cache_shutकरोwn(काष्ठा nfsd_net *);
पूर्णांक	nfsd_cache_lookup(काष्ठा svc_rqst *);
व्योम	nfsd_cache_update(काष्ठा svc_rqst *, पूर्णांक, __be32 *);
पूर्णांक	nfsd_reply_cache_stats_खोलो(काष्ठा inode *, काष्ठा file *);

#पूर्ण_अगर /* NFSCACHE_H */
