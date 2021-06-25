<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * zswap.c - zswap driver file
 *
 * zswap is a backend क्रम frontswap that takes pages that are in the process
 * of being swapped out and attempts to compress and store them in a
 * RAM-based memory pool.  This can result in a signअगरicant I/O reduction on
 * the swap device and, in the हाल where decompressing from RAM is faster
 * than पढ़ोing from the swap device, can also improve workload perक्रमmance.
 *
 * Copyright (C) 2012  Seth Jennings <sjenning@linux.vnet.ibm.com>
*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/cpu.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <linux/atomic.h>
#समावेश <linux/frontswap.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/swap.h>
#समावेश <linux/crypto.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/mempool.h>
#समावेश <linux/zpool.h>
#समावेश <crypto/acompress.h>

#समावेश <linux/mm_types.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/swapops.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/workqueue.h>

/*********************************
* statistics
**********************************/
/* Total bytes used by the compressed storage */
अटल u64 zswap_pool_total_size;
/* The number of compressed pages currently stored in zswap */
अटल atomic_t zswap_stored_pages = ATOMIC_INIT(0);
/* The number of same-value filled pages currently stored in zswap */
अटल atomic_t zswap_same_filled_pages = ATOMIC_INIT(0);

/*
 * The statistics below are not रक्षित from concurrent access क्रम
 * perक्रमmance reasons so they may not be a 100% accurate.  However,
 * they करो provide useful inक्रमmation on roughly how many बार a
 * certain event is occurring.
*/

/* Pool limit was hit (see zswap_max_pool_percent) */
अटल u64 zswap_pool_limit_hit;
/* Pages written back when pool limit was reached */
अटल u64 zswap_written_back_pages;
/* Store failed due to a reclaim failure after pool limit was reached */
अटल u64 zswap_reject_reclaim_fail;
/* Compressed page was too big क्रम the allocator to (optimally) store */
अटल u64 zswap_reject_compress_poor;
/* Store failed because underlying allocator could not get memory */
अटल u64 zswap_reject_alloc_fail;
/* Store failed because the entry metadata could not be allocated (rare) */
अटल u64 zswap_reject_kmemcache_fail;
/* Duplicate store was encountered (rare) */
अटल u64 zswap_duplicate_entry;

/* Shrinker work queue */
अटल काष्ठा workqueue_काष्ठा *shrink_wq;
/* Pool limit was hit, we need to calm करोwn */
अटल bool zswap_pool_reached_full;

/*********************************
* tunables
**********************************/

#घोषणा ZSWAP_PARAM_UNSET ""

/* Enable/disable zswap */
अटल bool zswap_enabled = IS_ENABLED(CONFIG_ZSWAP_DEFAULT_ON);
अटल पूर्णांक zswap_enabled_param_set(स्थिर अक्षर *,
				   स्थिर काष्ठा kernel_param *);
अटल स्थिर काष्ठा kernel_param_ops zswap_enabled_param_ops = अणु
	.set =		zswap_enabled_param_set,
	.get =		param_get_bool,
पूर्ण;
module_param_cb(enabled, &zswap_enabled_param_ops, &zswap_enabled, 0644);

/* Crypto compressor to use */
अटल अक्षर *zswap_compressor = CONFIG_ZSWAP_COMPRESSOR_DEFAULT;
अटल पूर्णांक zswap_compressor_param_set(स्थिर अक्षर *,
				      स्थिर काष्ठा kernel_param *);
अटल स्थिर काष्ठा kernel_param_ops zswap_compressor_param_ops = अणु
	.set =		zswap_compressor_param_set,
	.get =		param_get_अक्षरp,
	.मुक्त =		param_मुक्त_अक्षरp,
पूर्ण;
module_param_cb(compressor, &zswap_compressor_param_ops,
		&zswap_compressor, 0644);

/* Compressed storage zpool to use */
अटल अक्षर *zswap_zpool_type = CONFIG_ZSWAP_ZPOOL_DEFAULT;
अटल पूर्णांक zswap_zpool_param_set(स्थिर अक्षर *, स्थिर काष्ठा kernel_param *);
अटल स्थिर काष्ठा kernel_param_ops zswap_zpool_param_ops = अणु
	.set =		zswap_zpool_param_set,
	.get =		param_get_अक्षरp,
	.मुक्त =		param_मुक्त_अक्षरp,
पूर्ण;
module_param_cb(zpool, &zswap_zpool_param_ops, &zswap_zpool_type, 0644);

/* The maximum percentage of memory that the compressed pool can occupy */
अटल अचिन्हित पूर्णांक zswap_max_pool_percent = 20;
module_param_named(max_pool_percent, zswap_max_pool_percent, uपूर्णांक, 0644);

/* The threshold क्रम accepting new pages after the max_pool_percent was hit */
अटल अचिन्हित पूर्णांक zswap_accept_thr_percent = 90; /* of max pool size */
module_param_named(accept_threshold_percent, zswap_accept_thr_percent,
		   uपूर्णांक, 0644);

/* Enable/disable handling same-value filled pages (enabled by शेष) */
अटल bool zswap_same_filled_pages_enabled = true;
module_param_named(same_filled_pages_enabled, zswap_same_filled_pages_enabled,
		   bool, 0644);

/*********************************
* data काष्ठाures
**********************************/

काष्ठा crypto_acomp_ctx अणु
	काष्ठा crypto_acomp *acomp;
	काष्ठा acomp_req *req;
	काष्ठा crypto_रुको रुको;
	u8 *dsपंचांगem;
	काष्ठा mutex *mutex;
पूर्ण;

काष्ठा zswap_pool अणु
	काष्ठा zpool *zpool;
	काष्ठा crypto_acomp_ctx __percpu *acomp_ctx;
	काष्ठा kref kref;
	काष्ठा list_head list;
	काष्ठा work_काष्ठा release_work;
	काष्ठा work_काष्ठा shrink_work;
	काष्ठा hlist_node node;
	अक्षर tfm_name[CRYPTO_MAX_ALG_NAME];
पूर्ण;

/*
 * काष्ठा zswap_entry
 *
 * This काष्ठाure contains the metadata क्रम tracking a single compressed
 * page within zswap.
 *
 * rbnode - links the entry पूर्णांकo red-black tree क्रम the appropriate swap type
 * offset - the swap offset क्रम the entry.  Index पूर्णांकo the red-black tree.
 * refcount - the number of outstanding reference to the entry. This is needed
 *            to protect against premature मुक्तing of the entry by code
 *            concurrent calls to load, invalidate, and ग_लिखोback.  The lock
 *            क्रम the zswap_tree काष्ठाure that contains the entry must
 *            be held जबतक changing the refcount.  Since the lock must
 *            be held, there is no reason to also make refcount atomic.
 * length - the length in bytes of the compressed page data.  Needed during
 *          decompression. For a same value filled page length is 0.
 * pool - the zswap_pool the entry's data is in
 * handle - zpool allocation handle that stores the compressed page data
 * value - value of the same-value filled pages which have same content
 */
काष्ठा zswap_entry अणु
	काष्ठा rb_node rbnode;
	pgoff_t offset;
	पूर्णांक refcount;
	अचिन्हित पूर्णांक length;
	काष्ठा zswap_pool *pool;
	जोड़ अणु
		अचिन्हित दीर्घ handle;
		अचिन्हित दीर्घ value;
	पूर्ण;
पूर्ण;

काष्ठा zswap_header अणु
	swp_entry_t swpentry;
पूर्ण;

/*
 * The tree lock in the zswap_tree काष्ठा protects a few things:
 * - the rbtree
 * - the refcount field of each entry in the tree
 */
काष्ठा zswap_tree अणु
	काष्ठा rb_root rbroot;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा zswap_tree *zswap_trees[MAX_SWAPखाताS];

/* RCU-रक्षित iteration */
अटल LIST_HEAD(zswap_pools);
/* protects zswap_pools list modअगरication */
अटल DEFINE_SPINLOCK(zswap_pools_lock);
/* pool counter to provide unique names to zpool */
अटल atomic_t zswap_pools_count = ATOMIC_INIT(0);

/* used by param callback function */
अटल bool zswap_init_started;

/* fatal error during init */
अटल bool zswap_init_failed;

/* init completed, but couldn't create the initial pool */
अटल bool zswap_has_pool;

/*********************************
* helpers and fwd declarations
**********************************/

#घोषणा zswap_pool_debug(msg, p)				\
	pr_debug("%s pool %s/%s\n", msg, (p)->tfm_name,		\
		 zpool_get_type((p)->zpool))

अटल पूर्णांक zswap_ग_लिखोback_entry(काष्ठा zpool *pool, अचिन्हित दीर्घ handle);
अटल पूर्णांक zswap_pool_get(काष्ठा zswap_pool *pool);
अटल व्योम zswap_pool_put(काष्ठा zswap_pool *pool);

अटल स्थिर काष्ठा zpool_ops zswap_zpool_ops = अणु
	.evict = zswap_ग_लिखोback_entry
पूर्ण;

अटल bool zswap_is_full(व्योम)
अणु
	वापस totalram_pages() * zswap_max_pool_percent / 100 <
			DIV_ROUND_UP(zswap_pool_total_size, PAGE_SIZE);
पूर्ण

अटल bool zswap_can_accept(व्योम)
अणु
	वापस totalram_pages() * zswap_accept_thr_percent / 100 *
				zswap_max_pool_percent / 100 >
			DIV_ROUND_UP(zswap_pool_total_size, PAGE_SIZE);
पूर्ण

अटल व्योम zswap_update_total_size(व्योम)
अणु
	काष्ठा zswap_pool *pool;
	u64 total = 0;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(pool, &zswap_pools, list)
		total += zpool_get_total_size(pool->zpool);

	rcu_पढ़ो_unlock();

	zswap_pool_total_size = total;
पूर्ण

/*********************************
* zswap entry functions
**********************************/
अटल काष्ठा kmem_cache *zswap_entry_cache;

अटल पूर्णांक __init zswap_entry_cache_create(व्योम)
अणु
	zswap_entry_cache = KMEM_CACHE(zswap_entry, 0);
	वापस zswap_entry_cache == शून्य;
पूर्ण

अटल व्योम __init zswap_entry_cache_destroy(व्योम)
अणु
	kmem_cache_destroy(zswap_entry_cache);
पूर्ण

अटल काष्ठा zswap_entry *zswap_entry_cache_alloc(gfp_t gfp)
अणु
	काष्ठा zswap_entry *entry;
	entry = kmem_cache_alloc(zswap_entry_cache, gfp);
	अगर (!entry)
		वापस शून्य;
	entry->refcount = 1;
	RB_CLEAR_NODE(&entry->rbnode);
	वापस entry;
पूर्ण

अटल व्योम zswap_entry_cache_मुक्त(काष्ठा zswap_entry *entry)
अणु
	kmem_cache_मुक्त(zswap_entry_cache, entry);
पूर्ण

/*********************************
* rbtree functions
**********************************/
अटल काष्ठा zswap_entry *zswap_rb_search(काष्ठा rb_root *root, pgoff_t offset)
अणु
	काष्ठा rb_node *node = root->rb_node;
	काष्ठा zswap_entry *entry;

	जबतक (node) अणु
		entry = rb_entry(node, काष्ठा zswap_entry, rbnode);
		अगर (entry->offset > offset)
			node = node->rb_left;
		अन्यथा अगर (entry->offset < offset)
			node = node->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * In the हाल that a entry with the same offset is found, a poपूर्णांकer to
 * the existing entry is stored in dupentry and the function वापसs -EEXIST
 */
अटल पूर्णांक zswap_rb_insert(काष्ठा rb_root *root, काष्ठा zswap_entry *entry,
			काष्ठा zswap_entry **dupentry)
अणु
	काष्ठा rb_node **link = &root->rb_node, *parent = शून्य;
	काष्ठा zswap_entry *myentry;

	जबतक (*link) अणु
		parent = *link;
		myentry = rb_entry(parent, काष्ठा zswap_entry, rbnode);
		अगर (myentry->offset > entry->offset)
			link = &(*link)->rb_left;
		अन्यथा अगर (myentry->offset < entry->offset)
			link = &(*link)->rb_right;
		अन्यथा अणु
			*dupentry = myentry;
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	rb_link_node(&entry->rbnode, parent, link);
	rb_insert_color(&entry->rbnode, root);
	वापस 0;
पूर्ण

अटल व्योम zswap_rb_erase(काष्ठा rb_root *root, काष्ठा zswap_entry *entry)
अणु
	अगर (!RB_EMPTY_NODE(&entry->rbnode)) अणु
		rb_erase(&entry->rbnode, root);
		RB_CLEAR_NODE(&entry->rbnode);
	पूर्ण
पूर्ण

/*
 * Carries out the common pattern of मुक्तing and entry's zpool allocation,
 * मुक्तing the entry itself, and decrementing the number of stored pages.
 */
अटल व्योम zswap_मुक्त_entry(काष्ठा zswap_entry *entry)
अणु
	अगर (!entry->length)
		atomic_dec(&zswap_same_filled_pages);
	अन्यथा अणु
		zpool_मुक्त(entry->pool->zpool, entry->handle);
		zswap_pool_put(entry->pool);
	पूर्ण
	zswap_entry_cache_मुक्त(entry);
	atomic_dec(&zswap_stored_pages);
	zswap_update_total_size();
पूर्ण

/* caller must hold the tree lock */
अटल व्योम zswap_entry_get(काष्ठा zswap_entry *entry)
अणु
	entry->refcount++;
पूर्ण

/* caller must hold the tree lock
* हटाओ from the tree and मुक्त it, अगर nobody reference the entry
*/
अटल व्योम zswap_entry_put(काष्ठा zswap_tree *tree,
			काष्ठा zswap_entry *entry)
अणु
	पूर्णांक refcount = --entry->refcount;

	BUG_ON(refcount < 0);
	अगर (refcount == 0) अणु
		zswap_rb_erase(&tree->rbroot, entry);
		zswap_मुक्त_entry(entry);
	पूर्ण
पूर्ण

/* caller must hold the tree lock */
अटल काष्ठा zswap_entry *zswap_entry_find_get(काष्ठा rb_root *root,
				pgoff_t offset)
अणु
	काष्ठा zswap_entry *entry;

	entry = zswap_rb_search(root, offset);
	अगर (entry)
		zswap_entry_get(entry);

	वापस entry;
पूर्ण

/*********************************
* per-cpu code
**********************************/
अटल DEFINE_PER_CPU(u8 *, zswap_dsपंचांगem);
/*
 * If users dynamically change the zpool type and compressor at runसमय, i.e.
 * zswap is running, zswap can have more than one zpool on one cpu, but they
 * are sharing dtsmem. So we need this mutex to be per-cpu.
 */
अटल DEFINE_PER_CPU(काष्ठा mutex *, zswap_mutex);

अटल पूर्णांक zswap_dsपंचांगem_prepare(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा mutex *mutex;
	u8 *dst;

	dst = kदो_स्मृति_node(PAGE_SIZE * 2, GFP_KERNEL, cpu_to_node(cpu));
	अगर (!dst)
		वापस -ENOMEM;

	mutex = kदो_स्मृति_node(माप(*mutex), GFP_KERNEL, cpu_to_node(cpu));
	अगर (!mutex) अणु
		kमुक्त(dst);
		वापस -ENOMEM;
	पूर्ण

	mutex_init(mutex);
	per_cpu(zswap_dsपंचांगem, cpu) = dst;
	per_cpu(zswap_mutex, cpu) = mutex;
	वापस 0;
पूर्ण

अटल पूर्णांक zswap_dsपंचांगem_dead(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा mutex *mutex;
	u8 *dst;

	mutex = per_cpu(zswap_mutex, cpu);
	kमुक्त(mutex);
	per_cpu(zswap_mutex, cpu) = शून्य;

	dst = per_cpu(zswap_dsपंचांगem, cpu);
	kमुक्त(dst);
	per_cpu(zswap_dsपंचांगem, cpu) = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक zswap_cpu_comp_prepare(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा zswap_pool *pool = hlist_entry(node, काष्ठा zswap_pool, node);
	काष्ठा crypto_acomp_ctx *acomp_ctx = per_cpu_ptr(pool->acomp_ctx, cpu);
	काष्ठा crypto_acomp *acomp;
	काष्ठा acomp_req *req;

	acomp = crypto_alloc_acomp_node(pool->tfm_name, 0, 0, cpu_to_node(cpu));
	अगर (IS_ERR(acomp)) अणु
		pr_err("could not alloc crypto acomp %s : %ld\n",
				pool->tfm_name, PTR_ERR(acomp));
		वापस PTR_ERR(acomp);
	पूर्ण
	acomp_ctx->acomp = acomp;

	req = acomp_request_alloc(acomp_ctx->acomp);
	अगर (!req) अणु
		pr_err("could not alloc crypto acomp_request %s\n",
		       pool->tfm_name);
		crypto_मुक्त_acomp(acomp_ctx->acomp);
		वापस -ENOMEM;
	पूर्ण
	acomp_ctx->req = req;

	crypto_init_रुको(&acomp_ctx->रुको);
	/*
	 * अगर the backend of acomp is async zip, crypto_req_करोne() will wakeup
	 * crypto_रुको_req(); अगर the backend of acomp is scomp, the callback
	 * won't be called, crypto_रुको_req() will वापस without blocking.
	 */
	acomp_request_set_callback(req, CRYPTO_TFM_REQ_MAY_BACKLOG,
				   crypto_req_करोne, &acomp_ctx->रुको);

	acomp_ctx->mutex = per_cpu(zswap_mutex, cpu);
	acomp_ctx->dsपंचांगem = per_cpu(zswap_dsपंचांगem, cpu);

	वापस 0;
पूर्ण

अटल पूर्णांक zswap_cpu_comp_dead(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा zswap_pool *pool = hlist_entry(node, काष्ठा zswap_pool, node);
	काष्ठा crypto_acomp_ctx *acomp_ctx = per_cpu_ptr(pool->acomp_ctx, cpu);

	अगर (!IS_ERR_OR_शून्य(acomp_ctx)) अणु
		अगर (!IS_ERR_OR_शून्य(acomp_ctx->req))
			acomp_request_मुक्त(acomp_ctx->req);
		अगर (!IS_ERR_OR_शून्य(acomp_ctx->acomp))
			crypto_मुक्त_acomp(acomp_ctx->acomp);
	पूर्ण

	वापस 0;
पूर्ण

/*********************************
* pool functions
**********************************/

अटल काष्ठा zswap_pool *__zswap_pool_current(व्योम)
अणु
	काष्ठा zswap_pool *pool;

	pool = list_first_or_null_rcu(&zswap_pools, typeof(*pool), list);
	WARN_ONCE(!pool && zswap_has_pool,
		  "%s: no page storage pool!\n", __func__);

	वापस pool;
पूर्ण

अटल काष्ठा zswap_pool *zswap_pool_current(व्योम)
अणु
	निश्चित_spin_locked(&zswap_pools_lock);

	वापस __zswap_pool_current();
पूर्ण

अटल काष्ठा zswap_pool *zswap_pool_current_get(व्योम)
अणु
	काष्ठा zswap_pool *pool;

	rcu_पढ़ो_lock();

	pool = __zswap_pool_current();
	अगर (!zswap_pool_get(pool))
		pool = शून्य;

	rcu_पढ़ो_unlock();

	वापस pool;
पूर्ण

अटल काष्ठा zswap_pool *zswap_pool_last_get(व्योम)
अणु
	काष्ठा zswap_pool *pool, *last = शून्य;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(pool, &zswap_pools, list)
		last = pool;
	WARN_ONCE(!last && zswap_has_pool,
		  "%s: no page storage pool!\n", __func__);
	अगर (!zswap_pool_get(last))
		last = शून्य;

	rcu_पढ़ो_unlock();

	वापस last;
पूर्ण

/* type and compressor must be null-terminated */
अटल काष्ठा zswap_pool *zswap_pool_find_get(अक्षर *type, अक्षर *compressor)
अणु
	काष्ठा zswap_pool *pool;

	निश्चित_spin_locked(&zswap_pools_lock);

	list_क्रम_each_entry_rcu(pool, &zswap_pools, list) अणु
		अगर (म_भेद(pool->tfm_name, compressor))
			जारी;
		अगर (म_भेद(zpool_get_type(pool->zpool), type))
			जारी;
		/* अगर we can't get it, it's about to be destroyed */
		अगर (!zswap_pool_get(pool))
			जारी;
		वापस pool;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम shrink_worker(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा zswap_pool *pool = container_of(w, typeof(*pool),
						shrink_work);

	अगर (zpool_shrink(pool->zpool, 1, शून्य))
		zswap_reject_reclaim_fail++;
	zswap_pool_put(pool);
पूर्ण

अटल काष्ठा zswap_pool *zswap_pool_create(अक्षर *type, अक्षर *compressor)
अणु
	काष्ठा zswap_pool *pool;
	अक्षर name[38]; /* 'zswap' + 32 अक्षर (max) num + \0 */
	gfp_t gfp = __GFP_NORETRY | __GFP_NOWARN | __GFP_KSWAPD_RECLAIM;
	पूर्णांक ret;

	अगर (!zswap_has_pool) अणु
		/* अगर either are unset, pool initialization failed, and we
		 * need both params to be set correctly beक्रमe trying to
		 * create a pool.
		 */
		अगर (!म_भेद(type, ZSWAP_PARAM_UNSET))
			वापस शून्य;
		अगर (!म_भेद(compressor, ZSWAP_PARAM_UNSET))
			वापस शून्य;
	पूर्ण

	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस शून्य;

	/* unique name क्रम each pool specअगरically required by zsदो_स्मृति */
	snम_लिखो(name, 38, "zswap%x", atomic_inc_वापस(&zswap_pools_count));

	pool->zpool = zpool_create_pool(type, name, gfp, &zswap_zpool_ops);
	अगर (!pool->zpool) अणु
		pr_err("%s zpool not available\n", type);
		जाओ error;
	पूर्ण
	pr_debug("using %s zpool\n", zpool_get_type(pool->zpool));

	strscpy(pool->tfm_name, compressor, माप(pool->tfm_name));

	pool->acomp_ctx = alloc_percpu(*pool->acomp_ctx);
	अगर (!pool->acomp_ctx) अणु
		pr_err("percpu alloc failed\n");
		जाओ error;
	पूर्ण

	ret = cpuhp_state_add_instance(CPUHP_MM_ZSWP_POOL_PREPARE,
				       &pool->node);
	अगर (ret)
		जाओ error;
	pr_debug("using %s compressor\n", pool->tfm_name);

	/* being the current pool takes 1 ref; this func expects the
	 * caller to always add the new pool as the current pool
	 */
	kref_init(&pool->kref);
	INIT_LIST_HEAD(&pool->list);
	INIT_WORK(&pool->shrink_work, shrink_worker);

	zswap_pool_debug("created", pool);

	वापस pool;

error:
	अगर (pool->acomp_ctx)
		मुक्त_percpu(pool->acomp_ctx);
	अगर (pool->zpool)
		zpool_destroy_pool(pool->zpool);
	kमुक्त(pool);
	वापस शून्य;
पूर्ण

अटल __init काष्ठा zswap_pool *__zswap_pool_create_fallback(व्योम)
अणु
	bool has_comp, has_zpool;

	has_comp = crypto_has_acomp(zswap_compressor, 0, 0);
	अगर (!has_comp && म_भेद(zswap_compressor,
				CONFIG_ZSWAP_COMPRESSOR_DEFAULT)) अणु
		pr_err("compressor %s not available, using default %s\n",
		       zswap_compressor, CONFIG_ZSWAP_COMPRESSOR_DEFAULT);
		param_मुक्त_अक्षरp(&zswap_compressor);
		zswap_compressor = CONFIG_ZSWAP_COMPRESSOR_DEFAULT;
		has_comp = crypto_has_acomp(zswap_compressor, 0, 0);
	पूर्ण
	अगर (!has_comp) अणु
		pr_err("default compressor %s not available\n",
		       zswap_compressor);
		param_मुक्त_अक्षरp(&zswap_compressor);
		zswap_compressor = ZSWAP_PARAM_UNSET;
	पूर्ण

	has_zpool = zpool_has_pool(zswap_zpool_type);
	अगर (!has_zpool && म_भेद(zswap_zpool_type,
				 CONFIG_ZSWAP_ZPOOL_DEFAULT)) अणु
		pr_err("zpool %s not available, using default %s\n",
		       zswap_zpool_type, CONFIG_ZSWAP_ZPOOL_DEFAULT);
		param_मुक्त_अक्षरp(&zswap_zpool_type);
		zswap_zpool_type = CONFIG_ZSWAP_ZPOOL_DEFAULT;
		has_zpool = zpool_has_pool(zswap_zpool_type);
	पूर्ण
	अगर (!has_zpool) अणु
		pr_err("default zpool %s not available\n",
		       zswap_zpool_type);
		param_मुक्त_अक्षरp(&zswap_zpool_type);
		zswap_zpool_type = ZSWAP_PARAM_UNSET;
	पूर्ण

	अगर (!has_comp || !has_zpool)
		वापस शून्य;

	वापस zswap_pool_create(zswap_zpool_type, zswap_compressor);
पूर्ण

अटल व्योम zswap_pool_destroy(काष्ठा zswap_pool *pool)
अणु
	zswap_pool_debug("destroying", pool);

	cpuhp_state_हटाओ_instance(CPUHP_MM_ZSWP_POOL_PREPARE, &pool->node);
	मुक्त_percpu(pool->acomp_ctx);
	zpool_destroy_pool(pool->zpool);
	kमुक्त(pool);
पूर्ण

अटल पूर्णांक __must_check zswap_pool_get(काष्ठा zswap_pool *pool)
अणु
	अगर (!pool)
		वापस 0;

	वापस kref_get_unless_zero(&pool->kref);
पूर्ण

अटल व्योम __zswap_pool_release(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा zswap_pool *pool = container_of(work, typeof(*pool),
						release_work);

	synchronize_rcu();

	/* nobody should have been able to get a kref... */
	WARN_ON(kref_get_unless_zero(&pool->kref));

	/* pool is now off zswap_pools list and has no references. */
	zswap_pool_destroy(pool);
पूर्ण

अटल व्योम __zswap_pool_empty(काष्ठा kref *kref)
अणु
	काष्ठा zswap_pool *pool;

	pool = container_of(kref, typeof(*pool), kref);

	spin_lock(&zswap_pools_lock);

	WARN_ON(pool == zswap_pool_current());

	list_del_rcu(&pool->list);

	INIT_WORK(&pool->release_work, __zswap_pool_release);
	schedule_work(&pool->release_work);

	spin_unlock(&zswap_pools_lock);
पूर्ण

अटल व्योम zswap_pool_put(काष्ठा zswap_pool *pool)
अणु
	kref_put(&pool->kref, __zswap_pool_empty);
पूर्ण

/*********************************
* param callbacks
**********************************/

/* val must be a null-terminated string */
अटल पूर्णांक __zswap_param_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp,
			     अक्षर *type, अक्षर *compressor)
अणु
	काष्ठा zswap_pool *pool, *put_pool = शून्य;
	अक्षर *s = म_मालाip((अक्षर *)val);
	पूर्णांक ret;

	अगर (zswap_init_failed) अणु
		pr_err("can't set param, initialization failed\n");
		वापस -ENODEV;
	पूर्ण

	/* no change required */
	अगर (!म_भेद(s, *(अक्षर **)kp->arg) && zswap_has_pool)
		वापस 0;

	/* अगर this is load-समय (pre-init) param setting,
	 * करोn't create a pool; that's करोne during init.
	 */
	अगर (!zswap_init_started)
		वापस param_set_अक्षरp(s, kp);

	अगर (!type) अणु
		अगर (!zpool_has_pool(s)) अणु
			pr_err("zpool %s not available\n", s);
			वापस -ENOENT;
		पूर्ण
		type = s;
	पूर्ण अन्यथा अगर (!compressor) अणु
		अगर (!crypto_has_acomp(s, 0, 0)) अणु
			pr_err("compressor %s not available\n", s);
			वापस -ENOENT;
		पूर्ण
		compressor = s;
	पूर्ण अन्यथा अणु
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	spin_lock(&zswap_pools_lock);

	pool = zswap_pool_find_get(type, compressor);
	अगर (pool) अणु
		zswap_pool_debug("using existing", pool);
		WARN_ON(pool == zswap_pool_current());
		list_del_rcu(&pool->list);
	पूर्ण

	spin_unlock(&zswap_pools_lock);

	अगर (!pool)
		pool = zswap_pool_create(type, compressor);

	अगर (pool)
		ret = param_set_अक्षरp(s, kp);
	अन्यथा
		ret = -EINVAL;

	spin_lock(&zswap_pools_lock);

	अगर (!ret) अणु
		put_pool = zswap_pool_current();
		list_add_rcu(&pool->list, &zswap_pools);
		zswap_has_pool = true;
	पूर्ण अन्यथा अगर (pool) अणु
		/* add the possibly pre-existing pool to the end of the pools
		 * list; अगर it's new (and empty) then it'll be हटाओd and
		 * destroyed by the put after we drop the lock
		 */
		list_add_tail_rcu(&pool->list, &zswap_pools);
		put_pool = pool;
	पूर्ण

	spin_unlock(&zswap_pools_lock);

	अगर (!zswap_has_pool && !pool) अणु
		/* अगर initial pool creation failed, and this pool creation also
		 * failed, maybe both compressor and zpool params were bad.
		 * Allow changing this param, so pool creation will succeed
		 * when the other param is changed. We alपढ़ोy verअगरied this
		 * param is ok in the zpool_has_pool() or crypto_has_acomp()
		 * checks above.
		 */
		ret = param_set_अक्षरp(s, kp);
	पूर्ण

	/* drop the ref from either the old current pool,
	 * or the new pool we failed to add
	 */
	अगर (put_pool)
		zswap_pool_put(put_pool);

	वापस ret;
पूर्ण

अटल पूर्णांक zswap_compressor_param_set(स्थिर अक्षर *val,
				      स्थिर काष्ठा kernel_param *kp)
अणु
	वापस __zswap_param_set(val, kp, zswap_zpool_type, शून्य);
पूर्ण

अटल पूर्णांक zswap_zpool_param_set(स्थिर अक्षर *val,
				 स्थिर काष्ठा kernel_param *kp)
अणु
	वापस __zswap_param_set(val, kp, शून्य, zswap_compressor);
पूर्ण

अटल पूर्णांक zswap_enabled_param_set(स्थिर अक्षर *val,
				   स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (zswap_init_failed) अणु
		pr_err("can't enable, initialization failed\n");
		वापस -ENODEV;
	पूर्ण
	अगर (!zswap_has_pool && zswap_init_started) अणु
		pr_err("can't enable, no pool configured\n");
		वापस -ENODEV;
	पूर्ण

	वापस param_set_bool(val, kp);
पूर्ण

/*********************************
* ग_लिखोback code
**********************************/
/* वापस क्रमागत क्रम zswap_get_swap_cache_page */
क्रमागत zswap_get_swap_ret अणु
	ZSWAP_SWAPCACHE_NEW,
	ZSWAP_SWAPCACHE_EXIST,
	ZSWAP_SWAPCACHE_FAIL,
पूर्ण;

/*
 * zswap_get_swap_cache_page
 *
 * This is an adaption of पढ़ो_swap_cache_async()
 *
 * This function tries to find a page with the given swap entry
 * in the swapper_space address space (the swap cache).  If the page
 * is found, it is वापसed in retpage.  Otherwise, a page is allocated,
 * added to the swap cache, and वापसed in retpage.
 *
 * If success, the swap cache page is वापसed in retpage
 * Returns ZSWAP_SWAPCACHE_EXIST अगर page was alपढ़ोy in the swap cache
 * Returns ZSWAP_SWAPCACHE_NEW अगर the new page needs to be populated,
 *     the new page is added to swapcache and locked
 * Returns ZSWAP_SWAPCACHE_FAIL on error
 */
अटल पूर्णांक zswap_get_swap_cache_page(swp_entry_t entry,
				काष्ठा page **retpage)
अणु
	bool page_was_allocated;

	*retpage = __पढ़ो_swap_cache_async(entry, GFP_KERNEL,
			शून्य, 0, &page_was_allocated);
	अगर (page_was_allocated)
		वापस ZSWAP_SWAPCACHE_NEW;
	अगर (!*retpage)
		वापस ZSWAP_SWAPCACHE_FAIL;
	वापस ZSWAP_SWAPCACHE_EXIST;
पूर्ण

/*
 * Attempts to मुक्त an entry by adding a page to the swap cache,
 * decompressing the entry data पूर्णांकo the page, and issuing a
 * bio ग_लिखो to ग_लिखो the page back to the swap device.
 *
 * This can be thought of as a "resumed writeback" of the page
 * to the swap device.  We are basically resuming the same swap
 * ग_लिखोback path that was पूर्णांकercepted with the frontswap_store()
 * in the first place.  After the page has been decompressed पूर्णांकo
 * the swap cache, the compressed version stored by zswap can be
 * मुक्तd.
 */
अटल पूर्णांक zswap_ग_लिखोback_entry(काष्ठा zpool *pool, अचिन्हित दीर्घ handle)
अणु
	काष्ठा zswap_header *zhdr;
	swp_entry_t swpentry;
	काष्ठा zswap_tree *tree;
	pgoff_t offset;
	काष्ठा zswap_entry *entry;
	काष्ठा page *page;
	काष्ठा scatterlist input, output;
	काष्ठा crypto_acomp_ctx *acomp_ctx;

	u8 *src, *पंचांगp = शून्य;
	अचिन्हित पूर्णांक dlen;
	पूर्णांक ret;
	काष्ठा ग_लिखोback_control wbc = अणु
		.sync_mode = WB_SYNC_NONE,
	पूर्ण;

	अगर (!zpool_can_sleep_mapped(pool)) अणु
		पंचांगp = kदो_स्मृति(PAGE_SIZE, GFP_ATOMIC);
		अगर (!पंचांगp)
			वापस -ENOMEM;
	पूर्ण

	/* extract swpentry from data */
	zhdr = zpool_map_handle(pool, handle, ZPOOL_MM_RO);
	swpentry = zhdr->swpentry; /* here */
	tree = zswap_trees[swp_type(swpentry)];
	offset = swp_offset(swpentry);

	/* find and ref zswap entry */
	spin_lock(&tree->lock);
	entry = zswap_entry_find_get(&tree->rbroot, offset);
	अगर (!entry) अणु
		/* entry was invalidated */
		spin_unlock(&tree->lock);
		zpool_unmap_handle(pool, handle);
		kमुक्त(पंचांगp);
		वापस 0;
	पूर्ण
	spin_unlock(&tree->lock);
	BUG_ON(offset != entry->offset);

	/* try to allocate swap cache page */
	चयन (zswap_get_swap_cache_page(swpentry, &page)) अणु
	हाल ZSWAP_SWAPCACHE_FAIL: /* no memory or invalidate happened */
		ret = -ENOMEM;
		जाओ fail;

	हाल ZSWAP_SWAPCACHE_EXIST:
		/* page is alपढ़ोy in the swap cache, ignore क्रम now */
		put_page(page);
		ret = -EEXIST;
		जाओ fail;

	हाल ZSWAP_SWAPCACHE_NEW: /* page is locked */
		/* decompress */
		acomp_ctx = raw_cpu_ptr(entry->pool->acomp_ctx);

		dlen = PAGE_SIZE;
		src = (u8 *)zhdr + माप(काष्ठा zswap_header);

		अगर (!zpool_can_sleep_mapped(pool)) अणु

			स_नकल(पंचांगp, src, entry->length);
			src = पंचांगp;

			zpool_unmap_handle(pool, handle);
		पूर्ण

		mutex_lock(acomp_ctx->mutex);
		sg_init_one(&input, src, entry->length);
		sg_init_table(&output, 1);
		sg_set_page(&output, page, PAGE_SIZE, 0);
		acomp_request_set_params(acomp_ctx->req, &input, &output, entry->length, dlen);
		ret = crypto_रुको_req(crypto_acomp_decompress(acomp_ctx->req), &acomp_ctx->रुको);
		dlen = acomp_ctx->req->dlen;
		mutex_unlock(acomp_ctx->mutex);

		BUG_ON(ret);
		BUG_ON(dlen != PAGE_SIZE);

		/* page is up to date */
		SetPageUptodate(page);
	पूर्ण

	/* move it to the tail of the inactive list after end_ग_लिखोback */
	SetPageReclaim(page);

	/* start ग_लिखोback */
	__swap_ग_लिखोpage(page, &wbc, end_swap_bio_ग_लिखो);
	put_page(page);
	zswap_written_back_pages++;

	spin_lock(&tree->lock);
	/* drop local reference */
	zswap_entry_put(tree, entry);

	/*
	* There are two possible situations क्रम entry here:
	* (1) refcount is 1(normal हाल),  entry is valid and on the tree
	* (2) refcount is 0, entry is मुक्तd and not on the tree
	*     because invalidate happened during ग_लिखोback
	*  search the tree and मुक्त the entry अगर find entry
	*/
	अगर (entry == zswap_rb_search(&tree->rbroot, offset))
		zswap_entry_put(tree, entry);
	spin_unlock(&tree->lock);

	जाओ end;

	/*
	* अगर we get here due to ZSWAP_SWAPCACHE_EXIST
	* a load may be happening concurrently.
	* it is safe and okay to not मुक्त the entry.
	* अगर we मुक्त the entry in the following put
	* it is also okay to वापस !0
	*/
fail:
	spin_lock(&tree->lock);
	zswap_entry_put(tree, entry);
	spin_unlock(&tree->lock);

end:
	अगर (zpool_can_sleep_mapped(pool))
		zpool_unmap_handle(pool, handle);
	अन्यथा
		kमुक्त(पंचांगp);

	वापस ret;
पूर्ण

अटल पूर्णांक zswap_is_page_same_filled(व्योम *ptr, अचिन्हित दीर्घ *value)
अणु
	अचिन्हित पूर्णांक pos;
	अचिन्हित दीर्घ *page;

	page = (अचिन्हित दीर्घ *)ptr;
	क्रम (pos = 1; pos < PAGE_SIZE / माप(*page); pos++) अणु
		अगर (page[pos] != page[0])
			वापस 0;
	पूर्ण
	*value = page[0];
	वापस 1;
पूर्ण

अटल व्योम zswap_fill_page(व्योम *ptr, अचिन्हित दीर्घ value)
अणु
	अचिन्हित दीर्घ *page;

	page = (अचिन्हित दीर्घ *)ptr;
	स_रखो_l(page, value, PAGE_SIZE / माप(अचिन्हित दीर्घ));
पूर्ण

/*********************************
* frontswap hooks
**********************************/
/* attempts to compress and store an single page */
अटल पूर्णांक zswap_frontswap_store(अचिन्हित type, pgoff_t offset,
				काष्ठा page *page)
अणु
	काष्ठा zswap_tree *tree = zswap_trees[type];
	काष्ठा zswap_entry *entry, *dupentry;
	काष्ठा scatterlist input, output;
	काष्ठा crypto_acomp_ctx *acomp_ctx;
	पूर्णांक ret;
	अचिन्हित पूर्णांक hlen, dlen = PAGE_SIZE;
	अचिन्हित दीर्घ handle, value;
	अक्षर *buf;
	u8 *src, *dst;
	काष्ठा zswap_header zhdr = अणु .swpentry = swp_entry(type, offset) पूर्ण;
	gfp_t gfp;

	/* THP isn't supported */
	अगर (PageTransHuge(page)) अणु
		ret = -EINVAL;
		जाओ reject;
	पूर्ण

	अगर (!zswap_enabled || !tree) अणु
		ret = -ENODEV;
		जाओ reject;
	पूर्ण

	/* reclaim space अगर needed */
	अगर (zswap_is_full()) अणु
		काष्ठा zswap_pool *pool;

		zswap_pool_limit_hit++;
		zswap_pool_reached_full = true;
		pool = zswap_pool_last_get();
		अगर (pool)
			queue_work(shrink_wq, &pool->shrink_work);
		ret = -ENOMEM;
		जाओ reject;
	पूर्ण

	अगर (zswap_pool_reached_full) अणु
	       अगर (!zswap_can_accept()) अणु
			ret = -ENOMEM;
			जाओ reject;
		पूर्ण अन्यथा
			zswap_pool_reached_full = false;
	पूर्ण

	/* allocate entry */
	entry = zswap_entry_cache_alloc(GFP_KERNEL);
	अगर (!entry) अणु
		zswap_reject_kmemcache_fail++;
		ret = -ENOMEM;
		जाओ reject;
	पूर्ण

	अगर (zswap_same_filled_pages_enabled) अणु
		src = kmap_atomic(page);
		अगर (zswap_is_page_same_filled(src, &value)) अणु
			kunmap_atomic(src);
			entry->offset = offset;
			entry->length = 0;
			entry->value = value;
			atomic_inc(&zswap_same_filled_pages);
			जाओ insert_entry;
		पूर्ण
		kunmap_atomic(src);
	पूर्ण

	/* अगर entry is successfully added, it keeps the reference */
	entry->pool = zswap_pool_current_get();
	अगर (!entry->pool) अणु
		ret = -EINVAL;
		जाओ मुक्तpage;
	पूर्ण

	/* compress */
	acomp_ctx = raw_cpu_ptr(entry->pool->acomp_ctx);

	mutex_lock(acomp_ctx->mutex);

	dst = acomp_ctx->dsपंचांगem;
	sg_init_table(&input, 1);
	sg_set_page(&input, page, PAGE_SIZE, 0);

	/* zswap_dsपंचांगem is of size (PAGE_SIZE * 2). Reflect same in sg_list */
	sg_init_one(&output, dst, PAGE_SIZE * 2);
	acomp_request_set_params(acomp_ctx->req, &input, &output, PAGE_SIZE, dlen);
	/*
	 * it maybe looks a little bit silly that we send an asynchronous request,
	 * then रुको क्रम its completion synchronously. This makes the process look
	 * synchronous in fact.
	 * Theoretically, acomp supports users send multiple acomp requests in one
	 * acomp instance, then get those requests करोne simultaneously. but in this
	 * हाल, frontswap actually करोes store and load page by page, there is no
	 * existing method to send the second page beक्रमe the first page is करोne
	 * in one thपढ़ो करोing frontswap.
	 * but in dअगरferent thपढ़ोs running on dअगरferent cpu, we have dअगरferent
	 * acomp instance, so multiple thपढ़ोs can करो (de)compression in parallel.
	 */
	ret = crypto_रुको_req(crypto_acomp_compress(acomp_ctx->req), &acomp_ctx->रुको);
	dlen = acomp_ctx->req->dlen;

	अगर (ret) अणु
		ret = -EINVAL;
		जाओ put_dsपंचांगem;
	पूर्ण

	/* store */
	hlen = zpool_evictable(entry->pool->zpool) ? माप(zhdr) : 0;
	gfp = __GFP_NORETRY | __GFP_NOWARN | __GFP_KSWAPD_RECLAIM;
	अगर (zpool_दो_स्मृति_support_movable(entry->pool->zpool))
		gfp |= __GFP_HIGHMEM | __GFP_MOVABLE;
	ret = zpool_दो_स्मृति(entry->pool->zpool, hlen + dlen, gfp, &handle);
	अगर (ret == -ENOSPC) अणु
		zswap_reject_compress_poor++;
		जाओ put_dsपंचांगem;
	पूर्ण
	अगर (ret) अणु
		zswap_reject_alloc_fail++;
		जाओ put_dsपंचांगem;
	पूर्ण
	buf = zpool_map_handle(entry->pool->zpool, handle, ZPOOL_MM_RW);
	स_नकल(buf, &zhdr, hlen);
	स_नकल(buf + hlen, dst, dlen);
	zpool_unmap_handle(entry->pool->zpool, handle);
	mutex_unlock(acomp_ctx->mutex);

	/* populate entry */
	entry->offset = offset;
	entry->handle = handle;
	entry->length = dlen;

insert_entry:
	/* map */
	spin_lock(&tree->lock);
	करो अणु
		ret = zswap_rb_insert(&tree->rbroot, entry, &dupentry);
		अगर (ret == -EEXIST) अणु
			zswap_duplicate_entry++;
			/* हटाओ from rbtree */
			zswap_rb_erase(&tree->rbroot, dupentry);
			zswap_entry_put(tree, dupentry);
		पूर्ण
	पूर्ण जबतक (ret == -EEXIST);
	spin_unlock(&tree->lock);

	/* update stats */
	atomic_inc(&zswap_stored_pages);
	zswap_update_total_size();

	वापस 0;

put_dsपंचांगem:
	mutex_unlock(acomp_ctx->mutex);
	zswap_pool_put(entry->pool);
मुक्तpage:
	zswap_entry_cache_मुक्त(entry);
reject:
	वापस ret;
पूर्ण

/*
 * वापसs 0 अगर the page was successfully decompressed
 * वापस -1 on entry not found or error
*/
अटल पूर्णांक zswap_frontswap_load(अचिन्हित type, pgoff_t offset,
				काष्ठा page *page)
अणु
	काष्ठा zswap_tree *tree = zswap_trees[type];
	काष्ठा zswap_entry *entry;
	काष्ठा scatterlist input, output;
	काष्ठा crypto_acomp_ctx *acomp_ctx;
	u8 *src, *dst, *पंचांगp;
	अचिन्हित पूर्णांक dlen;
	पूर्णांक ret;

	/* find */
	spin_lock(&tree->lock);
	entry = zswap_entry_find_get(&tree->rbroot, offset);
	अगर (!entry) अणु
		/* entry was written back */
		spin_unlock(&tree->lock);
		वापस -1;
	पूर्ण
	spin_unlock(&tree->lock);

	अगर (!entry->length) अणु
		dst = kmap_atomic(page);
		zswap_fill_page(dst, entry->value);
		kunmap_atomic(dst);
		ret = 0;
		जाओ मुक्तentry;
	पूर्ण

	अगर (!zpool_can_sleep_mapped(entry->pool->zpool)) अणु

		पंचांगp = kदो_स्मृति(entry->length, GFP_ATOMIC);
		अगर (!पंचांगp) अणु
			ret = -ENOMEM;
			जाओ मुक्तentry;
		पूर्ण
	पूर्ण

	/* decompress */
	dlen = PAGE_SIZE;
	src = zpool_map_handle(entry->pool->zpool, entry->handle, ZPOOL_MM_RO);
	अगर (zpool_evictable(entry->pool->zpool))
		src += माप(काष्ठा zswap_header);

	अगर (!zpool_can_sleep_mapped(entry->pool->zpool)) अणु

		स_नकल(पंचांगp, src, entry->length);
		src = पंचांगp;

		zpool_unmap_handle(entry->pool->zpool, entry->handle);
	पूर्ण

	acomp_ctx = raw_cpu_ptr(entry->pool->acomp_ctx);
	mutex_lock(acomp_ctx->mutex);
	sg_init_one(&input, src, entry->length);
	sg_init_table(&output, 1);
	sg_set_page(&output, page, PAGE_SIZE, 0);
	acomp_request_set_params(acomp_ctx->req, &input, &output, entry->length, dlen);
	ret = crypto_रुको_req(crypto_acomp_decompress(acomp_ctx->req), &acomp_ctx->रुको);
	mutex_unlock(acomp_ctx->mutex);

	अगर (zpool_can_sleep_mapped(entry->pool->zpool))
		zpool_unmap_handle(entry->pool->zpool, entry->handle);
	अन्यथा
		kमुक्त(पंचांगp);

	BUG_ON(ret);

मुक्तentry:
	spin_lock(&tree->lock);
	zswap_entry_put(tree, entry);
	spin_unlock(&tree->lock);

	वापस ret;
पूर्ण

/* मुक्तs an entry in zswap */
अटल व्योम zswap_frontswap_invalidate_page(अचिन्हित type, pgoff_t offset)
अणु
	काष्ठा zswap_tree *tree = zswap_trees[type];
	काष्ठा zswap_entry *entry;

	/* find */
	spin_lock(&tree->lock);
	entry = zswap_rb_search(&tree->rbroot, offset);
	अगर (!entry) अणु
		/* entry was written back */
		spin_unlock(&tree->lock);
		वापस;
	पूर्ण

	/* हटाओ from rbtree */
	zswap_rb_erase(&tree->rbroot, entry);

	/* drop the initial reference from entry creation */
	zswap_entry_put(tree, entry);

	spin_unlock(&tree->lock);
पूर्ण

/* मुक्तs all zswap entries क्रम the given swap type */
अटल व्योम zswap_frontswap_invalidate_area(अचिन्हित type)
अणु
	काष्ठा zswap_tree *tree = zswap_trees[type];
	काष्ठा zswap_entry *entry, *n;

	अगर (!tree)
		वापस;

	/* walk the tree and मुक्त everything */
	spin_lock(&tree->lock);
	rbtree_postorder_क्रम_each_entry_safe(entry, n, &tree->rbroot, rbnode)
		zswap_मुक्त_entry(entry);
	tree->rbroot = RB_ROOT;
	spin_unlock(&tree->lock);
	kमुक्त(tree);
	zswap_trees[type] = शून्य;
पूर्ण

अटल व्योम zswap_frontswap_init(अचिन्हित type)
अणु
	काष्ठा zswap_tree *tree;

	tree = kzalloc(माप(*tree), GFP_KERNEL);
	अगर (!tree) अणु
		pr_err("alloc failed, zswap disabled for swap type %d\n", type);
		वापस;
	पूर्ण

	tree->rbroot = RB_ROOT;
	spin_lock_init(&tree->lock);
	zswap_trees[type] = tree;
पूर्ण

अटल काष्ठा frontswap_ops zswap_frontswap_ops = अणु
	.store = zswap_frontswap_store,
	.load = zswap_frontswap_load,
	.invalidate_page = zswap_frontswap_invalidate_page,
	.invalidate_area = zswap_frontswap_invalidate_area,
	.init = zswap_frontswap_init
पूर्ण;

/*********************************
* debugfs functions
**********************************/
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>

अटल काष्ठा dentry *zswap_debugfs_root;

अटल पूर्णांक __init zswap_debugfs_init(व्योम)
अणु
	अगर (!debugfs_initialized())
		वापस -ENODEV;

	zswap_debugfs_root = debugfs_create_dir("zswap", शून्य);

	debugfs_create_u64("pool_limit_hit", 0444,
			   zswap_debugfs_root, &zswap_pool_limit_hit);
	debugfs_create_u64("reject_reclaim_fail", 0444,
			   zswap_debugfs_root, &zswap_reject_reclaim_fail);
	debugfs_create_u64("reject_alloc_fail", 0444,
			   zswap_debugfs_root, &zswap_reject_alloc_fail);
	debugfs_create_u64("reject_kmemcache_fail", 0444,
			   zswap_debugfs_root, &zswap_reject_kmemcache_fail);
	debugfs_create_u64("reject_compress_poor", 0444,
			   zswap_debugfs_root, &zswap_reject_compress_poor);
	debugfs_create_u64("written_back_pages", 0444,
			   zswap_debugfs_root, &zswap_written_back_pages);
	debugfs_create_u64("duplicate_entry", 0444,
			   zswap_debugfs_root, &zswap_duplicate_entry);
	debugfs_create_u64("pool_total_size", 0444,
			   zswap_debugfs_root, &zswap_pool_total_size);
	debugfs_create_atomic_t("stored_pages", 0444,
				zswap_debugfs_root, &zswap_stored_pages);
	debugfs_create_atomic_t("same_filled_pages", 0444,
				zswap_debugfs_root, &zswap_same_filled_pages);

	वापस 0;
पूर्ण

अटल व्योम __निकास zswap_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(zswap_debugfs_root);
पूर्ण
#अन्यथा
अटल पूर्णांक __init zswap_debugfs_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास zswap_debugfs_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*********************************
* module init and निकास
**********************************/
अटल पूर्णांक __init init_zswap(व्योम)
अणु
	काष्ठा zswap_pool *pool;
	पूर्णांक ret;

	zswap_init_started = true;

	अगर (zswap_entry_cache_create()) अणु
		pr_err("entry cache creation failed\n");
		जाओ cache_fail;
	पूर्ण

	ret = cpuhp_setup_state(CPUHP_MM_ZSWP_MEM_PREPARE, "mm/zswap:prepare",
				zswap_dsपंचांगem_prepare, zswap_dsपंचांगem_dead);
	अगर (ret) अणु
		pr_err("dstmem alloc failed\n");
		जाओ dsपंचांगem_fail;
	पूर्ण

	ret = cpuhp_setup_state_multi(CPUHP_MM_ZSWP_POOL_PREPARE,
				      "mm/zswap_pool:prepare",
				      zswap_cpu_comp_prepare,
				      zswap_cpu_comp_dead);
	अगर (ret)
		जाओ hp_fail;

	pool = __zswap_pool_create_fallback();
	अगर (pool) अणु
		pr_info("loaded using pool %s/%s\n", pool->tfm_name,
			zpool_get_type(pool->zpool));
		list_add(&pool->list, &zswap_pools);
		zswap_has_pool = true;
	पूर्ण अन्यथा अणु
		pr_err("pool creation failed\n");
		zswap_enabled = false;
	पूर्ण

	shrink_wq = create_workqueue("zswap-shrink");
	अगर (!shrink_wq)
		जाओ fallback_fail;

	frontswap_रेजिस्टर_ops(&zswap_frontswap_ops);
	अगर (zswap_debugfs_init())
		pr_warn("debugfs initialization failed\n");
	वापस 0;

fallback_fail:
	अगर (pool)
		zswap_pool_destroy(pool);
hp_fail:
	cpuhp_हटाओ_state(CPUHP_MM_ZSWP_MEM_PREPARE);
dsपंचांगem_fail:
	zswap_entry_cache_destroy();
cache_fail:
	/* अगर built-in, we aren't unloaded on failure; don't allow use */
	zswap_init_failed = true;
	zswap_enabled = false;
	वापस -ENOMEM;
पूर्ण
/* must be late so crypto has समय to come up */
late_initcall(init_zswap);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Seth Jennings <sjennings@variantweb.net>");
MODULE_DESCRIPTION("Compressed cache for swap pages");
