<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Request reply cache. This is currently a global cache, but this may
 * change in the future and be a per-client cache.
 *
 * This code is heavily inspired by the 44BSD implementation, although
 * it करोes things a bit dअगरferently.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/log2.h>
#समावेश <linux/hash.h>
#समावेश <net/checksum.h>

#समावेश "nfsd.h"
#समावेश "cache.h"
#समावेश "trace.h"

/*
 * We use this value to determine the number of hash buckets from the max
 * cache size, the idea being that when the cache is at its maximum number
 * of entries, then this should be the average number of entries per bucket.
 */
#घोषणा TARGET_BUCKET_SIZE	64

काष्ठा nfsd_drc_bucket अणु
	काष्ठा rb_root rb_head;
	काष्ठा list_head lru_head;
	spinlock_t cache_lock;
पूर्ण;

अटल काष्ठा kmem_cache	*drc_slab;

अटल पूर्णांक	nfsd_cache_append(काष्ठा svc_rqst *rqstp, काष्ठा kvec *vec);
अटल अचिन्हित दीर्घ nfsd_reply_cache_count(काष्ठा shrinker *shrink,
					    काष्ठा shrink_control *sc);
अटल अचिन्हित दीर्घ nfsd_reply_cache_scan(काष्ठा shrinker *shrink,
					   काष्ठा shrink_control *sc);

/*
 * Put a cap on the size of the DRC based on the amount of available
 * low memory in the machine.
 *
 *  64MB:    8192
 * 128MB:   11585
 * 256MB:   16384
 * 512MB:   23170
 *   1GB:   32768
 *   2GB:   46340
 *   4GB:   65536
 *   8GB:   92681
 *  16GB:  131072
 *
 * ...with a hard cap of 256k entries. In the worst हाल, each entry will be
 * ~1k, so the above numbers should give a rough max of the amount of memory
 * used in k.
 *
 * XXX: these limits are per-container, so memory used will increase
 * linearly with number of containers.  Maybe that's OK.
 */
अटल अचिन्हित पूर्णांक
nfsd_cache_size_limit(व्योम)
अणु
	अचिन्हित पूर्णांक limit;
	अचिन्हित दीर्घ low_pages = totalram_pages() - totalhigh_pages();

	limit = (16 * पूर्णांक_वर्ग_मूल(low_pages)) << (PAGE_SHIFT-10);
	वापस min_t(अचिन्हित पूर्णांक, limit, 256*1024);
पूर्ण

/*
 * Compute the number of hash buckets we need. Divide the max cachesize by
 * the "target" max bucket size, and round up to next घातer of two.
 */
अटल अचिन्हित पूर्णांक
nfsd_hashsize(अचिन्हित पूर्णांक limit)
अणु
	वापस roundup_घात_of_two(limit / TARGET_BUCKET_SIZE);
पूर्ण

अटल u32
nfsd_cache_hash(__be32 xid, काष्ठा nfsd_net *nn)
अणु
	वापस hash_32(be32_to_cpu(xid), nn->maskbits);
पूर्ण

अटल काष्ठा svc_cacherep *
nfsd_reply_cache_alloc(काष्ठा svc_rqst *rqstp, __wsum csum,
			काष्ठा nfsd_net *nn)
अणु
	काष्ठा svc_cacherep	*rp;

	rp = kmem_cache_alloc(drc_slab, GFP_KERNEL);
	अगर (rp) अणु
		rp->c_state = RC_UNUSED;
		rp->c_type = RC_NOCACHE;
		RB_CLEAR_NODE(&rp->c_node);
		INIT_LIST_HEAD(&rp->c_lru);

		स_रखो(&rp->c_key, 0, माप(rp->c_key));
		rp->c_key.k_xid = rqstp->rq_xid;
		rp->c_key.k_proc = rqstp->rq_proc;
		rpc_copy_addr((काष्ठा sockaddr *)&rp->c_key.k_addr, svc_addr(rqstp));
		rpc_set_port((काष्ठा sockaddr *)&rp->c_key.k_addr, rpc_get_port(svc_addr(rqstp)));
		rp->c_key.k_prot = rqstp->rq_prot;
		rp->c_key.k_vers = rqstp->rq_vers;
		rp->c_key.k_len = rqstp->rq_arg.len;
		rp->c_key.k_csum = csum;
	पूर्ण
	वापस rp;
पूर्ण

अटल व्योम
nfsd_reply_cache_मुक्त_locked(काष्ठा nfsd_drc_bucket *b, काष्ठा svc_cacherep *rp,
				काष्ठा nfsd_net *nn)
अणु
	अगर (rp->c_type == RC_REPLBUFF && rp->c_replvec.iov_base) अणु
		nfsd_stats_drc_mem_usage_sub(nn, rp->c_replvec.iov_len);
		kमुक्त(rp->c_replvec.iov_base);
	पूर्ण
	अगर (rp->c_state != RC_UNUSED) अणु
		rb_erase(&rp->c_node, &b->rb_head);
		list_del(&rp->c_lru);
		atomic_dec(&nn->num_drc_entries);
		nfsd_stats_drc_mem_usage_sub(nn, माप(*rp));
	पूर्ण
	kmem_cache_मुक्त(drc_slab, rp);
पूर्ण

अटल व्योम
nfsd_reply_cache_मुक्त(काष्ठा nfsd_drc_bucket *b, काष्ठा svc_cacherep *rp,
			काष्ठा nfsd_net *nn)
अणु
	spin_lock(&b->cache_lock);
	nfsd_reply_cache_मुक्त_locked(b, rp, nn);
	spin_unlock(&b->cache_lock);
पूर्ण

पूर्णांक nfsd_drc_slab_create(व्योम)
अणु
	drc_slab = kmem_cache_create("nfsd_drc",
				माप(काष्ठा svc_cacherep), 0, 0, शून्य);
	वापस drc_slab ? 0: -ENOMEM;
पूर्ण

व्योम nfsd_drc_slab_मुक्त(व्योम)
अणु
	kmem_cache_destroy(drc_slab);
पूर्ण

अटल पूर्णांक nfsd_reply_cache_stats_init(काष्ठा nfsd_net *nn)
अणु
	वापस nfsd_percpu_counters_init(nn->counter, NFSD_NET_COUNTERS_NUM);
पूर्ण

अटल व्योम nfsd_reply_cache_stats_destroy(काष्ठा nfsd_net *nn)
अणु
	nfsd_percpu_counters_destroy(nn->counter, NFSD_NET_COUNTERS_NUM);
पूर्ण

पूर्णांक nfsd_reply_cache_init(काष्ठा nfsd_net *nn)
अणु
	अचिन्हित पूर्णांक hashsize;
	अचिन्हित पूर्णांक i;
	पूर्णांक status = 0;

	nn->max_drc_entries = nfsd_cache_size_limit();
	atomic_set(&nn->num_drc_entries, 0);
	hashsize = nfsd_hashsize(nn->max_drc_entries);
	nn->maskbits = ilog2(hashsize);

	status = nfsd_reply_cache_stats_init(nn);
	अगर (status)
		जाओ out_nomem;

	nn->nfsd_reply_cache_shrinker.scan_objects = nfsd_reply_cache_scan;
	nn->nfsd_reply_cache_shrinker.count_objects = nfsd_reply_cache_count;
	nn->nfsd_reply_cache_shrinker.seeks = 1;
	status = रेजिस्टर_shrinker(&nn->nfsd_reply_cache_shrinker);
	अगर (status)
		जाओ out_stats_destroy;

	nn->drc_hashtbl = kvzalloc(array_size(hashsize,
				माप(*nn->drc_hashtbl)), GFP_KERNEL);
	अगर (!nn->drc_hashtbl)
		जाओ out_shrinker;

	क्रम (i = 0; i < hashsize; i++) अणु
		INIT_LIST_HEAD(&nn->drc_hashtbl[i].lru_head);
		spin_lock_init(&nn->drc_hashtbl[i].cache_lock);
	पूर्ण
	nn->drc_hashsize = hashsize;

	वापस 0;
out_shrinker:
	unरेजिस्टर_shrinker(&nn->nfsd_reply_cache_shrinker);
out_stats_destroy:
	nfsd_reply_cache_stats_destroy(nn);
out_nomem:
	prपूर्णांकk(KERN_ERR "nfsd: failed to allocate reply cache\n");
	वापस -ENOMEM;
पूर्ण

व्योम nfsd_reply_cache_shutकरोwn(काष्ठा nfsd_net *nn)
अणु
	काष्ठा svc_cacherep	*rp;
	अचिन्हित पूर्णांक i;

	nfsd_reply_cache_stats_destroy(nn);
	unरेजिस्टर_shrinker(&nn->nfsd_reply_cache_shrinker);

	क्रम (i = 0; i < nn->drc_hashsize; i++) अणु
		काष्ठा list_head *head = &nn->drc_hashtbl[i].lru_head;
		जबतक (!list_empty(head)) अणु
			rp = list_first_entry(head, काष्ठा svc_cacherep, c_lru);
			nfsd_reply_cache_मुक्त_locked(&nn->drc_hashtbl[i],
									rp, nn);
		पूर्ण
	पूर्ण

	kvमुक्त(nn->drc_hashtbl);
	nn->drc_hashtbl = शून्य;
	nn->drc_hashsize = 0;

पूर्ण

/*
 * Move cache entry to end of LRU list, and queue the cleaner to run अगर it's
 * not alपढ़ोy scheduled.
 */
अटल व्योम
lru_put_end(काष्ठा nfsd_drc_bucket *b, काष्ठा svc_cacherep *rp)
अणु
	rp->c_बारtamp = jअगरfies;
	list_move_tail(&rp->c_lru, &b->lru_head);
पूर्ण

अटल दीर्घ
prune_bucket(काष्ठा nfsd_drc_bucket *b, काष्ठा nfsd_net *nn)
अणु
	काष्ठा svc_cacherep *rp, *पंचांगp;
	दीर्घ मुक्तd = 0;

	list_क्रम_each_entry_safe(rp, पंचांगp, &b->lru_head, c_lru) अणु
		/*
		 * Don't मुक्त entries attached to calls that are still
		 * in-progress, but करो keep scanning the list.
		 */
		अगर (rp->c_state == RC_INPROG)
			जारी;
		अगर (atomic_पढ़ो(&nn->num_drc_entries) <= nn->max_drc_entries &&
		    समय_beक्रमe(jअगरfies, rp->c_बारtamp + RC_EXPIRE))
			अवरोध;
		nfsd_reply_cache_मुक्त_locked(b, rp, nn);
		मुक्तd++;
	पूर्ण
	वापस मुक्तd;
पूर्ण

/*
 * Walk the LRU list and prune off entries that are older than RC_EXPIRE.
 * Also prune the oldest ones when the total exceeds the max number of entries.
 */
अटल दीर्घ
prune_cache_entries(काष्ठा nfsd_net *nn)
अणु
	अचिन्हित पूर्णांक i;
	दीर्घ मुक्तd = 0;

	क्रम (i = 0; i < nn->drc_hashsize; i++) अणु
		काष्ठा nfsd_drc_bucket *b = &nn->drc_hashtbl[i];

		अगर (list_empty(&b->lru_head))
			जारी;
		spin_lock(&b->cache_lock);
		मुक्तd += prune_bucket(b, nn);
		spin_unlock(&b->cache_lock);
	पूर्ण
	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ
nfsd_reply_cache_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	काष्ठा nfsd_net *nn = container_of(shrink,
				काष्ठा nfsd_net, nfsd_reply_cache_shrinker);

	वापस atomic_पढ़ो(&nn->num_drc_entries);
पूर्ण

अटल अचिन्हित दीर्घ
nfsd_reply_cache_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	काष्ठा nfsd_net *nn = container_of(shrink,
				काष्ठा nfsd_net, nfsd_reply_cache_shrinker);

	वापस prune_cache_entries(nn);
पूर्ण
/*
 * Walk an xdr_buf and get a CRC क्रम at most the first RC_CSUMLEN bytes
 */
अटल __wsum
nfsd_cache_csum(काष्ठा svc_rqst *rqstp)
अणु
	पूर्णांक idx;
	अचिन्हित पूर्णांक base;
	__wsum csum;
	काष्ठा xdr_buf *buf = &rqstp->rq_arg;
	स्थिर अचिन्हित अक्षर *p = buf->head[0].iov_base;
	माप_प्रकार csum_len = min_t(माप_प्रकार, buf->head[0].iov_len + buf->page_len,
				RC_CSUMLEN);
	माप_प्रकार len = min(buf->head[0].iov_len, csum_len);

	/* rq_arg.head first */
	csum = csum_partial(p, len, 0);
	csum_len -= len;

	/* Continue पूर्णांकo page array */
	idx = buf->page_base / PAGE_SIZE;
	base = buf->page_base & ~PAGE_MASK;
	जबतक (csum_len) अणु
		p = page_address(buf->pages[idx]) + base;
		len = min_t(माप_प्रकार, PAGE_SIZE - base, csum_len);
		csum = csum_partial(p, len, csum);
		csum_len -= len;
		base = 0;
		++idx;
	पूर्ण
	वापस csum;
पूर्ण

अटल पूर्णांक
nfsd_cache_key_cmp(स्थिर काष्ठा svc_cacherep *key,
			स्थिर काष्ठा svc_cacherep *rp, काष्ठा nfsd_net *nn)
अणु
	अगर (key->c_key.k_xid == rp->c_key.k_xid &&
	    key->c_key.k_csum != rp->c_key.k_csum) अणु
		nfsd_stats_payload_misses_inc(nn);
		trace_nfsd_drc_mismatch(nn, key, rp);
	पूर्ण

	वापस स_भेद(&key->c_key, &rp->c_key, माप(key->c_key));
पूर्ण

/*
 * Search the request hash क्रम an entry that matches the given rqstp.
 * Must be called with cache_lock held. Returns the found entry or
 * inserts an empty key on failure.
 */
अटल काष्ठा svc_cacherep *
nfsd_cache_insert(काष्ठा nfsd_drc_bucket *b, काष्ठा svc_cacherep *key,
			काष्ठा nfsd_net *nn)
अणु
	काष्ठा svc_cacherep	*rp, *ret = key;
	काष्ठा rb_node		**p = &b->rb_head.rb_node,
				*parent = शून्य;
	अचिन्हित पूर्णांक		entries = 0;
	पूर्णांक cmp;

	जबतक (*p != शून्य) अणु
		++entries;
		parent = *p;
		rp = rb_entry(parent, काष्ठा svc_cacherep, c_node);

		cmp = nfsd_cache_key_cmp(key, rp, nn);
		अगर (cmp < 0)
			p = &parent->rb_left;
		अन्यथा अगर (cmp > 0)
			p = &parent->rb_right;
		अन्यथा अणु
			ret = rp;
			जाओ out;
		पूर्ण
	पूर्ण
	rb_link_node(&key->c_node, parent, p);
	rb_insert_color(&key->c_node, &b->rb_head);
out:
	/* tally hash chain length stats */
	अगर (entries > nn->दीर्घest_chain) अणु
		nn->दीर्घest_chain = entries;
		nn->दीर्घest_chain_cachesize = atomic_पढ़ो(&nn->num_drc_entries);
	पूर्ण अन्यथा अगर (entries == nn->दीर्घest_chain) अणु
		/* prefer to keep the smallest cachesize possible here */
		nn->दीर्घest_chain_cachesize = min_t(अचिन्हित पूर्णांक,
				nn->दीर्घest_chain_cachesize,
				atomic_पढ़ो(&nn->num_drc_entries));
	पूर्ण

	lru_put_end(b, ret);
	वापस ret;
पूर्ण

/**
 * nfsd_cache_lookup - Find an entry in the duplicate reply cache
 * @rqstp: Incoming Call to find
 *
 * Try to find an entry matching the current call in the cache. When none
 * is found, we try to grab the oldest expired entry off the LRU list. If
 * a suitable one isn't there, then drop the cache_lock and allocate a
 * new one, then search again in हाल one got inserted जबतक this thपढ़ो
 * didn't hold the lock.
 *
 * Return values:
 *   %RC_DOIT: Process the request normally
 *   %RC_REPLY: Reply from cache
 *   %RC_DROPIT: Do not process the request further
 */
पूर्णांक nfsd_cache_lookup(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	काष्ठा svc_cacherep	*rp, *found;
	__be32			xid = rqstp->rq_xid;
	__wsum			csum;
	u32 hash = nfsd_cache_hash(xid, nn);
	काष्ठा nfsd_drc_bucket *b = &nn->drc_hashtbl[hash];
	पूर्णांक type = rqstp->rq_cachetype;
	पूर्णांक rtn = RC_DOIT;

	rqstp->rq_cacherep = शून्य;
	अगर (type == RC_NOCACHE) अणु
		nfsd_stats_rc_nocache_inc();
		जाओ out;
	पूर्ण

	csum = nfsd_cache_csum(rqstp);

	/*
	 * Since the common हाल is a cache miss followed by an insert,
	 * pपुनः_स्मृतिate an entry.
	 */
	rp = nfsd_reply_cache_alloc(rqstp, csum, nn);
	अगर (!rp)
		जाओ out;

	spin_lock(&b->cache_lock);
	found = nfsd_cache_insert(b, rp, nn);
	अगर (found != rp) अणु
		nfsd_reply_cache_मुक्त_locked(शून्य, rp, nn);
		rp = found;
		जाओ found_entry;
	पूर्ण

	nfsd_stats_rc_misses_inc();
	rqstp->rq_cacherep = rp;
	rp->c_state = RC_INPROG;

	atomic_inc(&nn->num_drc_entries);
	nfsd_stats_drc_mem_usage_add(nn, माप(*rp));

	/* go ahead and prune the cache */
	prune_bucket(b, nn);

out_unlock:
	spin_unlock(&b->cache_lock);
out:
	वापस rtn;

found_entry:
	/* We found a matching entry which is either in progress or करोne. */
	nfsd_stats_rc_hits_inc();
	rtn = RC_DROPIT;

	/* Request being processed */
	अगर (rp->c_state == RC_INPROG)
		जाओ out_trace;

	/* From the hall of fame of impractical attacks:
	 * Is this a user who tries to snoop on the cache? */
	rtn = RC_DOIT;
	अगर (!test_bit(RQ_SECURE, &rqstp->rq_flags) && rp->c_secure)
		जाओ out_trace;

	/* Compose RPC reply header */
	चयन (rp->c_type) अणु
	हाल RC_NOCACHE:
		अवरोध;
	हाल RC_REPLSTAT:
		svc_putu32(&rqstp->rq_res.head[0], rp->c_replstat);
		rtn = RC_REPLY;
		अवरोध;
	हाल RC_REPLBUFF:
		अगर (!nfsd_cache_append(rqstp, &rp->c_replvec))
			जाओ out_unlock; /* should not happen */
		rtn = RC_REPLY;
		अवरोध;
	शेष:
		WARN_ONCE(1, "nfsd: bad repcache type %d\n", rp->c_type);
	पूर्ण

out_trace:
	trace_nfsd_drc_found(nn, rqstp, rtn);
	जाओ out_unlock;
पूर्ण

/**
 * nfsd_cache_update - Update an entry in the duplicate reply cache.
 * @rqstp: svc_rqst with a finished Reply
 * @cachetype: which cache to update
 * @statp: Reply's status code
 *
 * This is called from nfsd_dispatch when the procedure has been
 * executed and the complete reply is in rqstp->rq_res.
 *
 * We're copying around data here rather than swapping buffers because
 * the toplevel loop requires max-sized buffers, which would be a waste
 * of memory क्रम a cache with a max reply size of 100 bytes (diropokres).
 *
 * If we should start to use dअगरferent types of cache entries tailored
 * specअगरically क्रम attrstat and fh's, we may save even more space.
 *
 * Also note that a cachetype of RC_NOCACHE can legally be passed when
 * nfsd failed to encode a reply that otherwise would have been cached.
 * In this हाल, nfsd_cache_update is called with statp == शून्य.
 */
व्योम nfsd_cache_update(काष्ठा svc_rqst *rqstp, पूर्णांक cachetype, __be32 *statp)
अणु
	काष्ठा nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	काष्ठा svc_cacherep *rp = rqstp->rq_cacherep;
	काष्ठा kvec	*resv = &rqstp->rq_res.head[0], *cachv;
	u32		hash;
	काष्ठा nfsd_drc_bucket *b;
	पूर्णांक		len;
	माप_प्रकार		bufsize = 0;

	अगर (!rp)
		वापस;

	hash = nfsd_cache_hash(rp->c_key.k_xid, nn);
	b = &nn->drc_hashtbl[hash];

	len = resv->iov_len - ((अक्षर*)statp - (अक्षर*)resv->iov_base);
	len >>= 2;

	/* Don't cache excessive amounts of data and XDR failures */
	अगर (!statp || len > (256 >> 2)) अणु
		nfsd_reply_cache_मुक्त(b, rp, nn);
		वापस;
	पूर्ण

	चयन (cachetype) अणु
	हाल RC_REPLSTAT:
		अगर (len != 1)
			prपूर्णांकk("nfsd: RC_REPLSTAT/reply len %d!\n",len);
		rp->c_replstat = *statp;
		अवरोध;
	हाल RC_REPLBUFF:
		cachv = &rp->c_replvec;
		bufsize = len << 2;
		cachv->iov_base = kदो_स्मृति(bufsize, GFP_KERNEL);
		अगर (!cachv->iov_base) अणु
			nfsd_reply_cache_मुक्त(b, rp, nn);
			वापस;
		पूर्ण
		cachv->iov_len = bufsize;
		स_नकल(cachv->iov_base, statp, bufsize);
		अवरोध;
	हाल RC_NOCACHE:
		nfsd_reply_cache_मुक्त(b, rp, nn);
		वापस;
	पूर्ण
	spin_lock(&b->cache_lock);
	nfsd_stats_drc_mem_usage_add(nn, bufsize);
	lru_put_end(b, rp);
	rp->c_secure = test_bit(RQ_SECURE, &rqstp->rq_flags);
	rp->c_type = cachetype;
	rp->c_state = RC_DONE;
	spin_unlock(&b->cache_lock);
	वापस;
पूर्ण

/*
 * Copy cached reply to current reply buffer. Should always fit.
 * FIXME as reply is in a page, we should just attach the page, and
 * keep a refcount....
 */
अटल पूर्णांक
nfsd_cache_append(काष्ठा svc_rqst *rqstp, काष्ठा kvec *data)
अणु
	काष्ठा kvec	*vec = &rqstp->rq_res.head[0];

	अगर (vec->iov_len + data->iov_len > PAGE_SIZE) अणु
		prपूर्णांकk(KERN_WARNING "nfsd: cached reply too large (%zd).\n",
				data->iov_len);
		वापस 0;
	पूर्ण
	स_नकल((अक्षर*)vec->iov_base + vec->iov_len, data->iov_base, data->iov_len);
	vec->iov_len += data->iov_len;
	वापस 1;
पूर्ण

/*
 * Note that fields may be added, हटाओd or reordered in the future. Programs
 * scraping this file क्रम info should test the labels to ensure they're
 * getting the correct field.
 */
अटल पूर्णांक nfsd_reply_cache_stats_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा nfsd_net *nn = m->निजी;

	seq_म_लिखो(m, "max entries:           %u\n", nn->max_drc_entries);
	seq_म_लिखो(m, "num entries:           %u\n",
		   atomic_पढ़ो(&nn->num_drc_entries));
	seq_म_लिखो(m, "hash buckets:          %u\n", 1 << nn->maskbits);
	seq_म_लिखो(m, "mem usage:             %lld\n",
		   percpu_counter_sum_positive(&nn->counter[NFSD_NET_DRC_MEM_USAGE]));
	seq_म_लिखो(m, "cache hits:            %lld\n",
		   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_RC_HITS]));
	seq_म_लिखो(m, "cache misses:          %lld\n",
		   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_RC_MISSES]));
	seq_म_लिखो(m, "not cached:            %lld\n",
		   percpu_counter_sum_positive(&nfsdstats.counter[NFSD_STATS_RC_NOCACHE]));
	seq_म_लिखो(m, "payload misses:        %lld\n",
		   percpu_counter_sum_positive(&nn->counter[NFSD_NET_PAYLOAD_MISSES]));
	seq_म_लिखो(m, "longest chain len:     %u\n", nn->दीर्घest_chain);
	seq_म_लिखो(m, "cachesize at longest:  %u\n", nn->दीर्घest_chain_cachesize);
	वापस 0;
पूर्ण

पूर्णांक nfsd_reply_cache_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा nfsd_net *nn = net_generic(file_inode(file)->i_sb->s_fs_info,
								nfsd_net_id);

	वापस single_खोलो(file, nfsd_reply_cache_stats_show, nn);
पूर्ण
