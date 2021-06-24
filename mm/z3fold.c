<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * z3fold.c
 *
 * Author: Vitaly Wool <vitaly.wool@konsulko.com>
 * Copyright (C) 2016, Sony Mobile Communications Inc.
 *
 * This implementation is based on zbud written by Seth Jennings.
 *
 * z3fold is an special purpose allocator क्रम storing compressed pages. It
 * can store up to three compressed pages per page which improves the
 * compression ratio of zbud जबतक retaining its मुख्य concepts (e. g. always
 * storing an पूर्णांकegral number of objects per page) and simplicity.
 * It still has simple and deterministic reclaim properties that make it
 * preferable to a higher density approach (with no requirement on पूर्णांकegral
 * number of object per page) when reclaim is used.
 *
 * As in zbud, pages are भागided पूर्णांकo "chunks".  The size of the chunks is
 * fixed at compile समय and is determined by NCHUNKS_ORDER below.
 *
 * z3fold करोesn't export any API and is meant to be used via zpool API.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/migrate.h>
#समावेश <linux/node.h>
#समावेश <linux/compaction.h>
#समावेश <linux/percpu.h>
#समावेश <linux/mount.h>
#समावेश <linux/pseuकरो_fs.h>
#समावेश <linux/fs.h>
#समावेश <linux/preempt.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/zpool.h>
#समावेश <linux/magic.h>
#समावेश <linux/kmemleak.h>

/*
 * NCHUNKS_ORDER determines the पूर्णांकernal allocation granularity, effectively
 * adjusting पूर्णांकernal fragmentation.  It also determines the number of
 * मुक्तlists मुख्यtained in each pool. NCHUNKS_ORDER of 6 means that the
 * allocation granularity will be in chunks of size PAGE_SIZE/64. Some chunks
 * in the beginning of an allocated page are occupied by z3fold header, so
 * NCHUNKS will be calculated to 63 (or 62 in हाल CONFIG_DEBUG_SPINLOCK=y),
 * which shows the max number of मुक्त chunks in z3fold page, also there will
 * be 63, or 62, respectively, मुक्तlists per pool.
 */
#घोषणा NCHUNKS_ORDER	6

#घोषणा CHUNK_SHIFT	(PAGE_SHIFT - NCHUNKS_ORDER)
#घोषणा CHUNK_SIZE	(1 << CHUNK_SHIFT)
#घोषणा ZHDR_SIZE_ALIGNED round_up(माप(काष्ठा z3fold_header), CHUNK_SIZE)
#घोषणा ZHDR_CHUNKS	(ZHDR_SIZE_ALIGNED >> CHUNK_SHIFT)
#घोषणा TOTAL_CHUNKS	(PAGE_SIZE >> CHUNK_SHIFT)
#घोषणा NCHUNKS		((PAGE_SIZE - ZHDR_SIZE_ALIGNED) >> CHUNK_SHIFT)

#घोषणा BUDDY_MASK	(0x3)
#घोषणा BUDDY_SHIFT	2
#घोषणा SLOTS_ALIGN	(0x40)

/*****************
 * Structures
*****************/
काष्ठा z3fold_pool;
काष्ठा z3fold_ops अणु
	पूर्णांक (*evict)(काष्ठा z3fold_pool *pool, अचिन्हित दीर्घ handle);
पूर्ण;

क्रमागत buddy अणु
	HEADLESS = 0,
	FIRST,
	MIDDLE,
	LAST,
	BUDDIES_MAX = LAST
पूर्ण;

काष्ठा z3fold_buddy_slots अणु
	/*
	 * we are using BUDDY_MASK in handle_to_buddy etc. so there should
	 * be enough slots to hold all possible variants
	 */
	अचिन्हित दीर्घ slot[BUDDY_MASK + 1];
	अचिन्हित दीर्घ pool; /* back link */
	rwlock_t lock;
पूर्ण;
#घोषणा HANDLE_FLAG_MASK	(0x03)

/*
 * काष्ठा z3fold_header - z3fold page metadata occupying first chunks of each
 *			z3fold page, except क्रम HEADLESS pages
 * @buddy:		links the z3fold page पूर्णांकo the relevant list in the
 *			pool
 * @page_lock:		per-page lock
 * @refcount:		reference count क्रम the z3fold page
 * @work:		work_काष्ठा क्रम page layout optimization
 * @slots:		poपूर्णांकer to the काष्ठाure holding buddy slots
 * @pool:		poपूर्णांकer to the containing pool
 * @cpu:		CPU which this page "belongs" to
 * @first_chunks:	the size of the first buddy in chunks, 0 अगर मुक्त
 * @middle_chunks:	the size of the middle buddy in chunks, 0 अगर मुक्त
 * @last_chunks:	the size of the last buddy in chunks, 0 अगर मुक्त
 * @first_num:		the starting number (क्रम the first handle)
 * @mapped_count:	the number of objects currently mapped
 */
काष्ठा z3fold_header अणु
	काष्ठा list_head buddy;
	spinlock_t page_lock;
	काष्ठा kref refcount;
	काष्ठा work_काष्ठा work;
	काष्ठा z3fold_buddy_slots *slots;
	काष्ठा z3fold_pool *pool;
	लघु cpu;
	अचिन्हित लघु first_chunks;
	अचिन्हित लघु middle_chunks;
	अचिन्हित लघु last_chunks;
	अचिन्हित लघु start_middle;
	अचिन्हित लघु first_num:2;
	अचिन्हित लघु mapped_count:2;
	अचिन्हित लघु क्रमeign_handles:2;
पूर्ण;

/**
 * काष्ठा z3fold_pool - stores metadata क्रम each z3fold pool
 * @name:	pool name
 * @lock:	protects pool unbuddied/lru lists
 * @stale_lock:	protects pool stale page list
 * @unbuddied:	per-cpu array of lists tracking z3fold pages that contain 2-
 *		buddies; the list each z3fold page is added to depends on
 *		the size of its मुक्त region.
 * @lru:	list tracking the z3fold pages in LRU order by most recently
 *		added buddy.
 * @stale:	list of pages marked क्रम मुक्तing
 * @pages_nr:	number of z3fold pages in the pool.
 * @c_handle:	cache क्रम z3fold_buddy_slots allocation
 * @ops:	poपूर्णांकer to a काष्ठाure of user defined operations specअगरied at
 *		pool creation समय.
 * @compact_wq:	workqueue क्रम page layout background optimization
 * @release_wq:	workqueue क्रम safe page release
 * @work:	work_काष्ठा क्रम safe page release
 * @inode:	inode क्रम z3fold pseuकरो fileप्रणाली
 *
 * This काष्ठाure is allocated at pool creation समय and मुख्यtains metadata
 * pertaining to a particular z3fold pool.
 */
काष्ठा z3fold_pool अणु
	स्थिर अक्षर *name;
	spinlock_t lock;
	spinlock_t stale_lock;
	काष्ठा list_head *unbuddied;
	काष्ठा list_head lru;
	काष्ठा list_head stale;
	atomic64_t pages_nr;
	काष्ठा kmem_cache *c_handle;
	स्थिर काष्ठा z3fold_ops *ops;
	काष्ठा zpool *zpool;
	स्थिर काष्ठा zpool_ops *zpool_ops;
	काष्ठा workqueue_काष्ठा *compact_wq;
	काष्ठा workqueue_काष्ठा *release_wq;
	काष्ठा work_काष्ठा work;
	काष्ठा inode *inode;
पूर्ण;

/*
 * Internal z3fold page flags
 */
क्रमागत z3fold_page_flags अणु
	PAGE_HEADLESS = 0,
	MIDDLE_CHUNK_MAPPED,
	NEEDS_COMPACTING,
	PAGE_STALE,
	PAGE_CLAIMED, /* by either reclaim or मुक्त */
पूर्ण;

/*
 * handle flags, go under HANDLE_FLAG_MASK
 */
क्रमागत z3fold_handle_flags अणु
	HANDLES_NOFREE = 0,
पूर्ण;

/*
 * Forward declarations
 */
अटल काष्ठा z3fold_header *__z3fold_alloc(काष्ठा z3fold_pool *, माप_प्रकार, bool);
अटल व्योम compact_page_work(काष्ठा work_काष्ठा *w);

/*****************
 * Helpers
*****************/

/* Converts an allocation size in bytes to size in z3fold chunks */
अटल पूर्णांक माप_प्रकारo_chunks(माप_प्रकार size)
अणु
	वापस (size + CHUNK_SIZE - 1) >> CHUNK_SHIFT;
पूर्ण

#घोषणा क्रम_each_unbuddied_list(_iter, _begin) \
	क्रम ((_iter) = (_begin); (_iter) < NCHUNKS; (_iter)++)

अटल अंतरभूत काष्ठा z3fold_buddy_slots *alloc_slots(काष्ठा z3fold_pool *pool,
							gfp_t gfp)
अणु
	काष्ठा z3fold_buddy_slots *slots;

	slots = kmem_cache_zalloc(pool->c_handle,
				 (gfp & ~(__GFP_HIGHMEM | __GFP_MOVABLE)));

	अगर (slots) अणु
		/* It will be मुक्तd separately in मुक्त_handle(). */
		kmemleak_not_leak(slots);
		slots->pool = (अचिन्हित दीर्घ)pool;
		rwlock_init(&slots->lock);
	पूर्ण

	वापस slots;
पूर्ण

अटल अंतरभूत काष्ठा z3fold_pool *slots_to_pool(काष्ठा z3fold_buddy_slots *s)
अणु
	वापस (काष्ठा z3fold_pool *)(s->pool & ~HANDLE_FLAG_MASK);
पूर्ण

अटल अंतरभूत काष्ठा z3fold_buddy_slots *handle_to_slots(अचिन्हित दीर्घ handle)
अणु
	वापस (काष्ठा z3fold_buddy_slots *)(handle & ~(SLOTS_ALIGN - 1));
पूर्ण

/* Lock a z3fold page */
अटल अंतरभूत व्योम z3fold_page_lock(काष्ठा z3fold_header *zhdr)
अणु
	spin_lock(&zhdr->page_lock);
पूर्ण

/* Try to lock a z3fold page */
अटल अंतरभूत पूर्णांक z3fold_page_trylock(काष्ठा z3fold_header *zhdr)
अणु
	वापस spin_trylock(&zhdr->page_lock);
पूर्ण

/* Unlock a z3fold page */
अटल अंतरभूत व्योम z3fold_page_unlock(काष्ठा z3fold_header *zhdr)
अणु
	spin_unlock(&zhdr->page_lock);
पूर्ण


अटल अंतरभूत काष्ठा z3fold_header *__get_z3fold_header(अचिन्हित दीर्घ handle,
							bool lock)
अणु
	काष्ठा z3fold_buddy_slots *slots;
	काष्ठा z3fold_header *zhdr;
	पूर्णांक locked = 0;

	अगर (!(handle & (1 << PAGE_HEADLESS))) अणु
		slots = handle_to_slots(handle);
		करो अणु
			अचिन्हित दीर्घ addr;

			पढ़ो_lock(&slots->lock);
			addr = *(अचिन्हित दीर्घ *)handle;
			zhdr = (काष्ठा z3fold_header *)(addr & PAGE_MASK);
			अगर (lock)
				locked = z3fold_page_trylock(zhdr);
			पढ़ो_unlock(&slots->lock);
			अगर (locked)
				अवरोध;
			cpu_relax();
		पूर्ण जबतक (lock);
	पूर्ण अन्यथा अणु
		zhdr = (काष्ठा z3fold_header *)(handle & PAGE_MASK);
	पूर्ण

	वापस zhdr;
पूर्ण

/* Returns the z3fold page where a given handle is stored */
अटल अंतरभूत काष्ठा z3fold_header *handle_to_z3fold_header(अचिन्हित दीर्घ h)
अणु
	वापस __get_z3fold_header(h, false);
पूर्ण

/* वापस locked z3fold page अगर it's not headless */
अटल अंतरभूत काष्ठा z3fold_header *get_z3fold_header(अचिन्हित दीर्घ h)
अणु
	वापस __get_z3fold_header(h, true);
पूर्ण

अटल अंतरभूत व्योम put_z3fold_header(काष्ठा z3fold_header *zhdr)
अणु
	काष्ठा page *page = virt_to_page(zhdr);

	अगर (!test_bit(PAGE_HEADLESS, &page->निजी))
		z3fold_page_unlock(zhdr);
पूर्ण

अटल अंतरभूत व्योम मुक्त_handle(अचिन्हित दीर्घ handle, काष्ठा z3fold_header *zhdr)
अणु
	काष्ठा z3fold_buddy_slots *slots;
	पूर्णांक i;
	bool is_मुक्त;

	अगर (handle & (1 << PAGE_HEADLESS))
		वापस;

	अगर (WARN_ON(*(अचिन्हित दीर्घ *)handle == 0))
		वापस;

	slots = handle_to_slots(handle);
	ग_लिखो_lock(&slots->lock);
	*(अचिन्हित दीर्घ *)handle = 0;

	अगर (test_bit(HANDLES_NOFREE, &slots->pool)) अणु
		ग_लिखो_unlock(&slots->lock);
		वापस; /* simple हाल, nothing अन्यथा to करो */
	पूर्ण

	अगर (zhdr->slots != slots)
		zhdr->क्रमeign_handles--;

	is_मुक्त = true;
	क्रम (i = 0; i <= BUDDY_MASK; i++) अणु
		अगर (slots->slot[i]) अणु
			is_मुक्त = false;
			अवरोध;
		पूर्ण
	पूर्ण
	ग_लिखो_unlock(&slots->lock);

	अगर (is_मुक्त) अणु
		काष्ठा z3fold_pool *pool = slots_to_pool(slots);

		अगर (zhdr->slots == slots)
			zhdr->slots = शून्य;
		kmem_cache_मुक्त(pool->c_handle, slots);
	पूर्ण
पूर्ण

अटल पूर्णांक z3fold_init_fs_context(काष्ठा fs_context *fc)
अणु
	वापस init_pseuकरो(fc, Z3FOLD_MAGIC) ? 0 : -ENOMEM;
पूर्ण

अटल काष्ठा file_प्रणाली_type z3fold_fs = अणु
	.name		= "z3fold",
	.init_fs_context = z3fold_init_fs_context,
	.समाप्त_sb	= समाप्त_anon_super,
पूर्ण;

अटल काष्ठा vfsmount *z3fold_mnt;
अटल पूर्णांक z3fold_mount(व्योम)
अणु
	पूर्णांक ret = 0;

	z3fold_mnt = kern_mount(&z3fold_fs);
	अगर (IS_ERR(z3fold_mnt))
		ret = PTR_ERR(z3fold_mnt);

	वापस ret;
पूर्ण

अटल व्योम z3fold_unmount(व्योम)
अणु
	kern_unmount(z3fold_mnt);
पूर्ण

अटल स्थिर काष्ठा address_space_operations z3fold_aops;
अटल पूर्णांक z3fold_रेजिस्टर_migration(काष्ठा z3fold_pool *pool)
अणु
	pool->inode = alloc_anon_inode(z3fold_mnt->mnt_sb);
	अगर (IS_ERR(pool->inode)) अणु
		pool->inode = शून्य;
		वापस 1;
	पूर्ण

	pool->inode->i_mapping->निजी_data = pool;
	pool->inode->i_mapping->a_ops = &z3fold_aops;
	वापस 0;
पूर्ण

अटल व्योम z3fold_unरेजिस्टर_migration(काष्ठा z3fold_pool *pool)
अणु
	अगर (pool->inode)
		iput(pool->inode);
पूर्ण

/* Initializes the z3fold header of a newly allocated z3fold page */
अटल काष्ठा z3fold_header *init_z3fold_page(काष्ठा page *page, bool headless,
					काष्ठा z3fold_pool *pool, gfp_t gfp)
अणु
	काष्ठा z3fold_header *zhdr = page_address(page);
	काष्ठा z3fold_buddy_slots *slots;

	INIT_LIST_HEAD(&page->lru);
	clear_bit(PAGE_HEADLESS, &page->निजी);
	clear_bit(MIDDLE_CHUNK_MAPPED, &page->निजी);
	clear_bit(NEEDS_COMPACTING, &page->निजी);
	clear_bit(PAGE_STALE, &page->निजी);
	clear_bit(PAGE_CLAIMED, &page->निजी);
	अगर (headless)
		वापस zhdr;

	slots = alloc_slots(pool, gfp);
	अगर (!slots)
		वापस शून्य;

	स_रखो(zhdr, 0, माप(*zhdr));
	spin_lock_init(&zhdr->page_lock);
	kref_init(&zhdr->refcount);
	zhdr->cpu = -1;
	zhdr->slots = slots;
	zhdr->pool = pool;
	INIT_LIST_HEAD(&zhdr->buddy);
	INIT_WORK(&zhdr->work, compact_page_work);
	वापस zhdr;
पूर्ण

/* Resets the काष्ठा page fields and मुक्तs the page */
अटल व्योम मुक्त_z3fold_page(काष्ठा page *page, bool headless)
अणु
	अगर (!headless) अणु
		lock_page(page);
		__ClearPageMovable(page);
		unlock_page(page);
	पूर्ण
	ClearPagePrivate(page);
	__मुक्त_page(page);
पूर्ण

/* Helper function to build the index */
अटल अंतरभूत पूर्णांक __idx(काष्ठा z3fold_header *zhdr, क्रमागत buddy bud)
अणु
	वापस (bud + zhdr->first_num) & BUDDY_MASK;
पूर्ण

/*
 * Encodes the handle of a particular buddy within a z3fold page
 * Pool lock should be held as this function accesses first_num
 */
अटल अचिन्हित दीर्घ __encode_handle(काष्ठा z3fold_header *zhdr,
				काष्ठा z3fold_buddy_slots *slots,
				क्रमागत buddy bud)
अणु
	अचिन्हित दीर्घ h = (अचिन्हित दीर्घ)zhdr;
	पूर्णांक idx = 0;

	/*
	 * For a headless page, its handle is its poपूर्णांकer with the extra
	 * PAGE_HEADLESS bit set
	 */
	अगर (bud == HEADLESS)
		वापस h | (1 << PAGE_HEADLESS);

	/* otherwise, वापस poपूर्णांकer to encoded handle */
	idx = __idx(zhdr, bud);
	h += idx;
	अगर (bud == LAST)
		h |= (zhdr->last_chunks << BUDDY_SHIFT);

	ग_लिखो_lock(&slots->lock);
	slots->slot[idx] = h;
	ग_लिखो_unlock(&slots->lock);
	वापस (अचिन्हित दीर्घ)&slots->slot[idx];
पूर्ण

अटल अचिन्हित दीर्घ encode_handle(काष्ठा z3fold_header *zhdr, क्रमागत buddy bud)
अणु
	वापस __encode_handle(zhdr, zhdr->slots, bud);
पूर्ण

/* only क्रम LAST bud, वापसs zero otherwise */
अटल अचिन्हित लघु handle_to_chunks(अचिन्हित दीर्घ handle)
अणु
	काष्ठा z3fold_buddy_slots *slots = handle_to_slots(handle);
	अचिन्हित दीर्घ addr;

	पढ़ो_lock(&slots->lock);
	addr = *(अचिन्हित दीर्घ *)handle;
	पढ़ो_unlock(&slots->lock);
	वापस (addr & ~PAGE_MASK) >> BUDDY_SHIFT;
पूर्ण

/*
 * (handle & BUDDY_MASK) < zhdr->first_num is possible in encode_handle
 *  but that करोesn't matter. because the masking will result in the
 *  correct buddy number.
 */
अटल क्रमागत buddy handle_to_buddy(अचिन्हित दीर्घ handle)
अणु
	काष्ठा z3fold_header *zhdr;
	काष्ठा z3fold_buddy_slots *slots = handle_to_slots(handle);
	अचिन्हित दीर्घ addr;

	पढ़ो_lock(&slots->lock);
	WARN_ON(handle & (1 << PAGE_HEADLESS));
	addr = *(अचिन्हित दीर्घ *)handle;
	पढ़ो_unlock(&slots->lock);
	zhdr = (काष्ठा z3fold_header *)(addr & PAGE_MASK);
	वापस (addr - zhdr->first_num) & BUDDY_MASK;
पूर्ण

अटल अंतरभूत काष्ठा z3fold_pool *zhdr_to_pool(काष्ठा z3fold_header *zhdr)
अणु
	वापस zhdr->pool;
पूर्ण

अटल व्योम __release_z3fold_page(काष्ठा z3fold_header *zhdr, bool locked)
अणु
	काष्ठा page *page = virt_to_page(zhdr);
	काष्ठा z3fold_pool *pool = zhdr_to_pool(zhdr);

	WARN_ON(!list_empty(&zhdr->buddy));
	set_bit(PAGE_STALE, &page->निजी);
	clear_bit(NEEDS_COMPACTING, &page->निजी);
	spin_lock(&pool->lock);
	अगर (!list_empty(&page->lru))
		list_del_init(&page->lru);
	spin_unlock(&pool->lock);

	अगर (locked)
		z3fold_page_unlock(zhdr);

	spin_lock(&pool->stale_lock);
	list_add(&zhdr->buddy, &pool->stale);
	queue_work(pool->release_wq, &pool->work);
	spin_unlock(&pool->stale_lock);
पूर्ण

अटल व्योम release_z3fold_page(काष्ठा kref *ref)
अणु
	काष्ठा z3fold_header *zhdr = container_of(ref, काष्ठा z3fold_header,
						refcount);
	__release_z3fold_page(zhdr, false);
पूर्ण

अटल व्योम release_z3fold_page_locked(काष्ठा kref *ref)
अणु
	काष्ठा z3fold_header *zhdr = container_of(ref, काष्ठा z3fold_header,
						refcount);
	WARN_ON(z3fold_page_trylock(zhdr));
	__release_z3fold_page(zhdr, true);
पूर्ण

अटल व्योम release_z3fold_page_locked_list(काष्ठा kref *ref)
अणु
	काष्ठा z3fold_header *zhdr = container_of(ref, काष्ठा z3fold_header,
					       refcount);
	काष्ठा z3fold_pool *pool = zhdr_to_pool(zhdr);

	spin_lock(&pool->lock);
	list_del_init(&zhdr->buddy);
	spin_unlock(&pool->lock);

	WARN_ON(z3fold_page_trylock(zhdr));
	__release_z3fold_page(zhdr, true);
पूर्ण

अटल व्योम मुक्त_pages_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा z3fold_pool *pool = container_of(w, काष्ठा z3fold_pool, work);

	spin_lock(&pool->stale_lock);
	जबतक (!list_empty(&pool->stale)) अणु
		काष्ठा z3fold_header *zhdr = list_first_entry(&pool->stale,
						काष्ठा z3fold_header, buddy);
		काष्ठा page *page = virt_to_page(zhdr);

		list_del(&zhdr->buddy);
		अगर (WARN_ON(!test_bit(PAGE_STALE, &page->निजी)))
			जारी;
		spin_unlock(&pool->stale_lock);
		cancel_work_sync(&zhdr->work);
		मुक्त_z3fold_page(page, false);
		cond_resched();
		spin_lock(&pool->stale_lock);
	पूर्ण
	spin_unlock(&pool->stale_lock);
पूर्ण

/*
 * Returns the number of मुक्त chunks in a z3fold page.
 * NB: can't be used with HEADLESS pages.
 */
अटल पूर्णांक num_मुक्त_chunks(काष्ठा z3fold_header *zhdr)
अणु
	पूर्णांक nमुक्त;
	/*
	 * If there is a middle object, pick up the bigger मुक्त space
	 * either beक्रमe or after it. Otherwise just subtract the number
	 * of chunks occupied by the first and the last objects.
	 */
	अगर (zhdr->middle_chunks != 0) अणु
		पूर्णांक nमुक्त_beक्रमe = zhdr->first_chunks ?
			0 : zhdr->start_middle - ZHDR_CHUNKS;
		पूर्णांक nमुक्त_after = zhdr->last_chunks ?
			0 : TOTAL_CHUNKS -
				(zhdr->start_middle + zhdr->middle_chunks);
		nमुक्त = max(nमुक्त_beक्रमe, nमुक्त_after);
	पूर्ण अन्यथा
		nमुक्त = NCHUNKS - zhdr->first_chunks - zhdr->last_chunks;
	वापस nमुक्त;
पूर्ण

/* Add to the appropriate unbuddied list */
अटल अंतरभूत व्योम add_to_unbuddied(काष्ठा z3fold_pool *pool,
				काष्ठा z3fold_header *zhdr)
अणु
	अगर (zhdr->first_chunks == 0 || zhdr->last_chunks == 0 ||
			zhdr->middle_chunks == 0) अणु
		काष्ठा list_head *unbuddied;
		पूर्णांक मुक्तchunks = num_मुक्त_chunks(zhdr);

		migrate_disable();
		unbuddied = this_cpu_ptr(pool->unbuddied);
		spin_lock(&pool->lock);
		list_add(&zhdr->buddy, &unbuddied[मुक्तchunks]);
		spin_unlock(&pool->lock);
		zhdr->cpu = smp_processor_id();
		migrate_enable();
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत buddy get_मुक्त_buddy(काष्ठा z3fold_header *zhdr, पूर्णांक chunks)
अणु
	क्रमागत buddy bud = HEADLESS;

	अगर (zhdr->middle_chunks) अणु
		अगर (!zhdr->first_chunks &&
		    chunks <= zhdr->start_middle - ZHDR_CHUNKS)
			bud = FIRST;
		अन्यथा अगर (!zhdr->last_chunks)
			bud = LAST;
	पूर्ण अन्यथा अणु
		अगर (!zhdr->first_chunks)
			bud = FIRST;
		अन्यथा अगर (!zhdr->last_chunks)
			bud = LAST;
		अन्यथा
			bud = MIDDLE;
	पूर्ण

	वापस bud;
पूर्ण

अटल अंतरभूत व्योम *mchunk_स_हटाओ(काष्ठा z3fold_header *zhdr,
				अचिन्हित लघु dst_chunk)
अणु
	व्योम *beg = zhdr;
	वापस स_हटाओ(beg + (dst_chunk << CHUNK_SHIFT),
		       beg + (zhdr->start_middle << CHUNK_SHIFT),
		       zhdr->middle_chunks << CHUNK_SHIFT);
पूर्ण

अटल अंतरभूत bool buddy_single(काष्ठा z3fold_header *zhdr)
अणु
	वापस !((zhdr->first_chunks && zhdr->middle_chunks) ||
			(zhdr->first_chunks && zhdr->last_chunks) ||
			(zhdr->middle_chunks && zhdr->last_chunks));
पूर्ण

अटल काष्ठा z3fold_header *compact_single_buddy(काष्ठा z3fold_header *zhdr)
अणु
	काष्ठा z3fold_pool *pool = zhdr_to_pool(zhdr);
	व्योम *p = zhdr;
	अचिन्हित दीर्घ old_handle = 0;
	माप_प्रकार sz = 0;
	काष्ठा z3fold_header *new_zhdr = शून्य;
	पूर्णांक first_idx = __idx(zhdr, FIRST);
	पूर्णांक middle_idx = __idx(zhdr, MIDDLE);
	पूर्णांक last_idx = __idx(zhdr, LAST);
	अचिन्हित लघु *moved_chunks = शून्य;

	/*
	 * No need to protect slots here -- all the slots are "local" and
	 * the page lock is alपढ़ोy taken
	 */
	अगर (zhdr->first_chunks && zhdr->slots->slot[first_idx]) अणु
		p += ZHDR_SIZE_ALIGNED;
		sz = zhdr->first_chunks << CHUNK_SHIFT;
		old_handle = (अचिन्हित दीर्घ)&zhdr->slots->slot[first_idx];
		moved_chunks = &zhdr->first_chunks;
	पूर्ण अन्यथा अगर (zhdr->middle_chunks && zhdr->slots->slot[middle_idx]) अणु
		p += zhdr->start_middle << CHUNK_SHIFT;
		sz = zhdr->middle_chunks << CHUNK_SHIFT;
		old_handle = (अचिन्हित दीर्घ)&zhdr->slots->slot[middle_idx];
		moved_chunks = &zhdr->middle_chunks;
	पूर्ण अन्यथा अगर (zhdr->last_chunks && zhdr->slots->slot[last_idx]) अणु
		p += PAGE_SIZE - (zhdr->last_chunks << CHUNK_SHIFT);
		sz = zhdr->last_chunks << CHUNK_SHIFT;
		old_handle = (अचिन्हित दीर्घ)&zhdr->slots->slot[last_idx];
		moved_chunks = &zhdr->last_chunks;
	पूर्ण

	अगर (sz > 0) अणु
		क्रमागत buddy new_bud = HEADLESS;
		लघु chunks = माप_प्रकारo_chunks(sz);
		व्योम *q;

		new_zhdr = __z3fold_alloc(pool, sz, false);
		अगर (!new_zhdr)
			वापस शून्य;

		अगर (WARN_ON(new_zhdr == zhdr))
			जाओ out_fail;

		new_bud = get_मुक्त_buddy(new_zhdr, chunks);
		q = new_zhdr;
		चयन (new_bud) अणु
		हाल FIRST:
			new_zhdr->first_chunks = chunks;
			q += ZHDR_SIZE_ALIGNED;
			अवरोध;
		हाल MIDDLE:
			new_zhdr->middle_chunks = chunks;
			new_zhdr->start_middle =
				new_zhdr->first_chunks + ZHDR_CHUNKS;
			q += new_zhdr->start_middle << CHUNK_SHIFT;
			अवरोध;
		हाल LAST:
			new_zhdr->last_chunks = chunks;
			q += PAGE_SIZE - (new_zhdr->last_chunks << CHUNK_SHIFT);
			अवरोध;
		शेष:
			जाओ out_fail;
		पूर्ण
		new_zhdr->क्रमeign_handles++;
		स_नकल(q, p, sz);
		ग_लिखो_lock(&zhdr->slots->lock);
		*(अचिन्हित दीर्घ *)old_handle = (अचिन्हित दीर्घ)new_zhdr +
			__idx(new_zhdr, new_bud);
		अगर (new_bud == LAST)
			*(अचिन्हित दीर्घ *)old_handle |=
					(new_zhdr->last_chunks << BUDDY_SHIFT);
		ग_लिखो_unlock(&zhdr->slots->lock);
		add_to_unbuddied(pool, new_zhdr);
		z3fold_page_unlock(new_zhdr);

		*moved_chunks = 0;
	पूर्ण

	वापस new_zhdr;

out_fail:
	अगर (new_zhdr) अणु
		अगर (kref_put(&new_zhdr->refcount, release_z3fold_page_locked))
			atomic64_dec(&pool->pages_nr);
		अन्यथा अणु
			add_to_unbuddied(pool, new_zhdr);
			z3fold_page_unlock(new_zhdr);
		पूर्ण
	पूर्ण
	वापस शून्य;

पूर्ण

#घोषणा BIG_CHUNK_GAP	3
/* Has to be called with lock held */
अटल पूर्णांक z3fold_compact_page(काष्ठा z3fold_header *zhdr)
अणु
	काष्ठा page *page = virt_to_page(zhdr);

	अगर (test_bit(MIDDLE_CHUNK_MAPPED, &page->निजी))
		वापस 0; /* can't move middle chunk, it's used */

	अगर (unlikely(PageIsolated(page)))
		वापस 0;

	अगर (zhdr->middle_chunks == 0)
		वापस 0; /* nothing to compact */

	अगर (zhdr->first_chunks == 0 && zhdr->last_chunks == 0) अणु
		/* move to the beginning */
		mchunk_स_हटाओ(zhdr, ZHDR_CHUNKS);
		zhdr->first_chunks = zhdr->middle_chunks;
		zhdr->middle_chunks = 0;
		zhdr->start_middle = 0;
		zhdr->first_num++;
		वापस 1;
	पूर्ण

	/*
	 * moving data is expensive, so let's only करो that अगर
	 * there's substantial gain (at least BIG_CHUNK_GAP chunks)
	 */
	अगर (zhdr->first_chunks != 0 && zhdr->last_chunks == 0 &&
	    zhdr->start_middle - (zhdr->first_chunks + ZHDR_CHUNKS) >=
			BIG_CHUNK_GAP) अणु
		mchunk_स_हटाओ(zhdr, zhdr->first_chunks + ZHDR_CHUNKS);
		zhdr->start_middle = zhdr->first_chunks + ZHDR_CHUNKS;
		वापस 1;
	पूर्ण अन्यथा अगर (zhdr->last_chunks != 0 && zhdr->first_chunks == 0 &&
		   TOTAL_CHUNKS - (zhdr->last_chunks + zhdr->start_middle
					+ zhdr->middle_chunks) >=
			BIG_CHUNK_GAP) अणु
		अचिन्हित लघु new_start = TOTAL_CHUNKS - zhdr->last_chunks -
			zhdr->middle_chunks;
		mchunk_स_हटाओ(zhdr, new_start);
		zhdr->start_middle = new_start;
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम करो_compact_page(काष्ठा z3fold_header *zhdr, bool locked)
अणु
	काष्ठा z3fold_pool *pool = zhdr_to_pool(zhdr);
	काष्ठा page *page;

	page = virt_to_page(zhdr);
	अगर (locked)
		WARN_ON(z3fold_page_trylock(zhdr));
	अन्यथा
		z3fold_page_lock(zhdr);
	अगर (WARN_ON(!test_and_clear_bit(NEEDS_COMPACTING, &page->निजी))) अणु
		z3fold_page_unlock(zhdr);
		वापस;
	पूर्ण
	spin_lock(&pool->lock);
	list_del_init(&zhdr->buddy);
	spin_unlock(&pool->lock);

	अगर (kref_put(&zhdr->refcount, release_z3fold_page_locked)) अणु
		atomic64_dec(&pool->pages_nr);
		वापस;
	पूर्ण

	अगर (test_bit(PAGE_STALE, &page->निजी) ||
	    test_and_set_bit(PAGE_CLAIMED, &page->निजी)) अणु
		z3fold_page_unlock(zhdr);
		वापस;
	पूर्ण

	अगर (!zhdr->क्रमeign_handles && buddy_single(zhdr) &&
	    zhdr->mapped_count == 0 && compact_single_buddy(zhdr)) अणु
		अगर (kref_put(&zhdr->refcount, release_z3fold_page_locked))
			atomic64_dec(&pool->pages_nr);
		अन्यथा अणु
			clear_bit(PAGE_CLAIMED, &page->निजी);
			z3fold_page_unlock(zhdr);
		पूर्ण
		वापस;
	पूर्ण

	z3fold_compact_page(zhdr);
	add_to_unbuddied(pool, zhdr);
	clear_bit(PAGE_CLAIMED, &page->निजी);
	z3fold_page_unlock(zhdr);
पूर्ण

अटल व्योम compact_page_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा z3fold_header *zhdr = container_of(w, काष्ठा z3fold_header,
						work);

	करो_compact_page(zhdr, false);
पूर्ण

/* वापसs _locked_ z3fold page header or शून्य */
अटल अंतरभूत काष्ठा z3fold_header *__z3fold_alloc(काष्ठा z3fold_pool *pool,
						माप_प्रकार size, bool can_sleep)
अणु
	काष्ठा z3fold_header *zhdr = शून्य;
	काष्ठा page *page;
	काष्ठा list_head *unbuddied;
	पूर्णांक chunks = माप_प्रकारo_chunks(size), i;

lookup:
	migrate_disable();
	/* First, try to find an unbuddied z3fold page. */
	unbuddied = this_cpu_ptr(pool->unbuddied);
	क्रम_each_unbuddied_list(i, chunks) अणु
		काष्ठा list_head *l = &unbuddied[i];

		zhdr = list_first_entry_or_null(READ_ONCE(l),
					काष्ठा z3fold_header, buddy);

		अगर (!zhdr)
			जारी;

		/* Re-check under lock. */
		spin_lock(&pool->lock);
		l = &unbuddied[i];
		अगर (unlikely(zhdr != list_first_entry(READ_ONCE(l),
						काष्ठा z3fold_header, buddy)) ||
		    !z3fold_page_trylock(zhdr)) अणु
			spin_unlock(&pool->lock);
			zhdr = शून्य;
			migrate_enable();
			अगर (can_sleep)
				cond_resched();
			जाओ lookup;
		पूर्ण
		list_del_init(&zhdr->buddy);
		zhdr->cpu = -1;
		spin_unlock(&pool->lock);

		page = virt_to_page(zhdr);
		अगर (test_bit(NEEDS_COMPACTING, &page->निजी) ||
		    test_bit(PAGE_CLAIMED, &page->निजी)) अणु
			z3fold_page_unlock(zhdr);
			zhdr = शून्य;
			migrate_enable();
			अगर (can_sleep)
				cond_resched();
			जाओ lookup;
		पूर्ण

		/*
		 * this page could not be हटाओd from its unbuddied
		 * list जबतक pool lock was held, and then we've taken
		 * page lock so kref_put could not be called beक्रमe
		 * we got here, so it's safe to just call kref_get()
		 */
		kref_get(&zhdr->refcount);
		अवरोध;
	पूर्ण
	migrate_enable();

	अगर (!zhdr) अणु
		पूर्णांक cpu;

		/* look क्रम _exact_ match on other cpus' lists */
		क्रम_each_online_cpu(cpu) अणु
			काष्ठा list_head *l;

			unbuddied = per_cpu_ptr(pool->unbuddied, cpu);
			spin_lock(&pool->lock);
			l = &unbuddied[chunks];

			zhdr = list_first_entry_or_null(READ_ONCE(l),
						काष्ठा z3fold_header, buddy);

			अगर (!zhdr || !z3fold_page_trylock(zhdr)) अणु
				spin_unlock(&pool->lock);
				zhdr = शून्य;
				जारी;
			पूर्ण
			list_del_init(&zhdr->buddy);
			zhdr->cpu = -1;
			spin_unlock(&pool->lock);

			page = virt_to_page(zhdr);
			अगर (test_bit(NEEDS_COMPACTING, &page->निजी) ||
			    test_bit(PAGE_CLAIMED, &page->निजी)) अणु
				z3fold_page_unlock(zhdr);
				zhdr = शून्य;
				अगर (can_sleep)
					cond_resched();
				जारी;
			पूर्ण
			kref_get(&zhdr->refcount);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (zhdr && !zhdr->slots)
		zhdr->slots = alloc_slots(pool,
					can_sleep ? GFP_NOIO : GFP_ATOMIC);
	वापस zhdr;
पूर्ण

/*
 * API Functions
 */

/**
 * z3fold_create_pool() - create a new z3fold pool
 * @name:	pool name
 * @gfp:	gfp flags when allocating the z3fold pool काष्ठाure
 * @ops:	user-defined operations क्रम the z3fold pool
 *
 * Return: poपूर्णांकer to the new z3fold pool or शून्य अगर the metadata allocation
 * failed.
 */
अटल काष्ठा z3fold_pool *z3fold_create_pool(स्थिर अक्षर *name, gfp_t gfp,
		स्थिर काष्ठा z3fold_ops *ops)
अणु
	काष्ठा z3fold_pool *pool = शून्य;
	पूर्णांक i, cpu;

	pool = kzalloc(माप(काष्ठा z3fold_pool), gfp);
	अगर (!pool)
		जाओ out;
	pool->c_handle = kmem_cache_create("z3fold_handle",
				माप(काष्ठा z3fold_buddy_slots),
				SLOTS_ALIGN, 0, शून्य);
	अगर (!pool->c_handle)
		जाओ out_c;
	spin_lock_init(&pool->lock);
	spin_lock_init(&pool->stale_lock);
	pool->unbuddied = __alloc_percpu(माप(काष्ठा list_head)*NCHUNKS, 2);
	अगर (!pool->unbuddied)
		जाओ out_pool;
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा list_head *unbuddied =
				per_cpu_ptr(pool->unbuddied, cpu);
		क्रम_each_unbuddied_list(i, 0)
			INIT_LIST_HEAD(&unbuddied[i]);
	पूर्ण
	INIT_LIST_HEAD(&pool->lru);
	INIT_LIST_HEAD(&pool->stale);
	atomic64_set(&pool->pages_nr, 0);
	pool->name = name;
	pool->compact_wq = create_singlethपढ़ो_workqueue(pool->name);
	अगर (!pool->compact_wq)
		जाओ out_unbuddied;
	pool->release_wq = create_singlethपढ़ो_workqueue(pool->name);
	अगर (!pool->release_wq)
		जाओ out_wq;
	अगर (z3fold_रेजिस्टर_migration(pool))
		जाओ out_rwq;
	INIT_WORK(&pool->work, मुक्त_pages_work);
	pool->ops = ops;
	वापस pool;

out_rwq:
	destroy_workqueue(pool->release_wq);
out_wq:
	destroy_workqueue(pool->compact_wq);
out_unbuddied:
	मुक्त_percpu(pool->unbuddied);
out_pool:
	kmem_cache_destroy(pool->c_handle);
out_c:
	kमुक्त(pool);
out:
	वापस शून्य;
पूर्ण

/**
 * z3fold_destroy_pool() - destroys an existing z3fold pool
 * @pool:	the z3fold pool to be destroyed
 *
 * The pool should be emptied beक्रमe this function is called.
 */
अटल व्योम z3fold_destroy_pool(काष्ठा z3fold_pool *pool)
अणु
	kmem_cache_destroy(pool->c_handle);

	/*
	 * We need to destroy pool->compact_wq beक्रमe pool->release_wq,
	 * as any pending work on pool->compact_wq will call
	 * queue_work(pool->release_wq, &pool->work).
	 *
	 * There are still outstanding pages until both workqueues are drained,
	 * so we cannot unरेजिस्टर migration until then.
	 */

	destroy_workqueue(pool->compact_wq);
	destroy_workqueue(pool->release_wq);
	z3fold_unरेजिस्टर_migration(pool);
	kमुक्त(pool);
पूर्ण

/**
 * z3fold_alloc() - allocates a region of a given size
 * @pool:	z3fold pool from which to allocate
 * @size:	size in bytes of the desired allocation
 * @gfp:	gfp flags used अगर the pool needs to grow
 * @handle:	handle of the new allocation
 *
 * This function will attempt to find a मुक्त region in the pool large enough to
 * satisfy the allocation request.  A search of the unbuddied lists is
 * perक्रमmed first. If no suitable मुक्त region is found, then a new page is
 * allocated and added to the pool to satisfy the request.
 *
 * gfp should not set __GFP_HIGHMEM as highmem pages cannot be used
 * as z3fold pool pages.
 *
 * Return: 0 अगर success and handle is set, otherwise -EINVAL अगर the size or
 * gfp arguments are invalid or -ENOMEM अगर the pool was unable to allocate
 * a new page.
 */
अटल पूर्णांक z3fold_alloc(काष्ठा z3fold_pool *pool, माप_प्रकार size, gfp_t gfp,
			अचिन्हित दीर्घ *handle)
अणु
	पूर्णांक chunks = माप_प्रकारo_chunks(size);
	काष्ठा z3fold_header *zhdr = शून्य;
	काष्ठा page *page = शून्य;
	क्रमागत buddy bud;
	bool can_sleep = gfpflags_allow_blocking(gfp);

	अगर (!size)
		वापस -EINVAL;

	अगर (size > PAGE_SIZE)
		वापस -ENOSPC;

	अगर (size > PAGE_SIZE - ZHDR_SIZE_ALIGNED - CHUNK_SIZE)
		bud = HEADLESS;
	अन्यथा अणु
retry:
		zhdr = __z3fold_alloc(pool, size, can_sleep);
		अगर (zhdr) अणु
			bud = get_मुक्त_buddy(zhdr, chunks);
			अगर (bud == HEADLESS) अणु
				अगर (kref_put(&zhdr->refcount,
					     release_z3fold_page_locked))
					atomic64_dec(&pool->pages_nr);
				अन्यथा
					z3fold_page_unlock(zhdr);
				pr_err("No free chunks in unbuddied\n");
				WARN_ON(1);
				जाओ retry;
			पूर्ण
			page = virt_to_page(zhdr);
			जाओ found;
		पूर्ण
		bud = FIRST;
	पूर्ण

	page = शून्य;
	अगर (can_sleep) अणु
		spin_lock(&pool->stale_lock);
		zhdr = list_first_entry_or_null(&pool->stale,
						काष्ठा z3fold_header, buddy);
		/*
		 * Beक्रमe allocating a page, let's see अगर we can take one from
		 * the stale pages list. cancel_work_sync() can sleep so we
		 * limit this हाल to the contexts where we can sleep
		 */
		अगर (zhdr) अणु
			list_del(&zhdr->buddy);
			spin_unlock(&pool->stale_lock);
			cancel_work_sync(&zhdr->work);
			page = virt_to_page(zhdr);
		पूर्ण अन्यथा अणु
			spin_unlock(&pool->stale_lock);
		पूर्ण
	पूर्ण
	अगर (!page)
		page = alloc_page(gfp);

	अगर (!page)
		वापस -ENOMEM;

	zhdr = init_z3fold_page(page, bud == HEADLESS, pool, gfp);
	अगर (!zhdr) अणु
		__मुक्त_page(page);
		वापस -ENOMEM;
	पूर्ण
	atomic64_inc(&pool->pages_nr);

	अगर (bud == HEADLESS) अणु
		set_bit(PAGE_HEADLESS, &page->निजी);
		जाओ headless;
	पूर्ण
	अगर (can_sleep) अणु
		lock_page(page);
		__SetPageMovable(page, pool->inode->i_mapping);
		unlock_page(page);
	पूर्ण अन्यथा अणु
		अगर (trylock_page(page)) अणु
			__SetPageMovable(page, pool->inode->i_mapping);
			unlock_page(page);
		पूर्ण
	पूर्ण
	z3fold_page_lock(zhdr);

found:
	अगर (bud == FIRST)
		zhdr->first_chunks = chunks;
	अन्यथा अगर (bud == LAST)
		zhdr->last_chunks = chunks;
	अन्यथा अणु
		zhdr->middle_chunks = chunks;
		zhdr->start_middle = zhdr->first_chunks + ZHDR_CHUNKS;
	पूर्ण
	add_to_unbuddied(pool, zhdr);

headless:
	spin_lock(&pool->lock);
	/* Add/move z3fold page to beginning of LRU */
	अगर (!list_empty(&page->lru))
		list_del(&page->lru);

	list_add(&page->lru, &pool->lru);

	*handle = encode_handle(zhdr, bud);
	spin_unlock(&pool->lock);
	अगर (bud != HEADLESS)
		z3fold_page_unlock(zhdr);

	वापस 0;
पूर्ण

/**
 * z3fold_मुक्त() - मुक्तs the allocation associated with the given handle
 * @pool:	pool in which the allocation resided
 * @handle:	handle associated with the allocation वापसed by z3fold_alloc()
 *
 * In the हाल that the z3fold page in which the allocation resides is under
 * reclaim, as indicated by the PG_reclaim flag being set, this function
 * only sets the first|last_chunks to 0.  The page is actually मुक्तd
 * once both buddies are evicted (see z3fold_reclaim_page() below).
 */
अटल व्योम z3fold_मुक्त(काष्ठा z3fold_pool *pool, अचिन्हित दीर्घ handle)
अणु
	काष्ठा z3fold_header *zhdr;
	काष्ठा page *page;
	क्रमागत buddy bud;
	bool page_claimed;

	zhdr = get_z3fold_header(handle);
	page = virt_to_page(zhdr);
	page_claimed = test_and_set_bit(PAGE_CLAIMED, &page->निजी);

	अगर (test_bit(PAGE_HEADLESS, &page->निजी)) अणु
		/* अगर a headless page is under reclaim, just leave.
		 * NB: we use test_and_set_bit क्रम a reason: अगर the bit
		 * has not been set beक्रमe, we release this page
		 * immediately so we करोn't care about its value any more.
		 */
		अगर (!page_claimed) अणु
			spin_lock(&pool->lock);
			list_del(&page->lru);
			spin_unlock(&pool->lock);
			put_z3fold_header(zhdr);
			मुक्त_z3fold_page(page, true);
			atomic64_dec(&pool->pages_nr);
		पूर्ण
		वापस;
	पूर्ण

	/* Non-headless हाल */
	bud = handle_to_buddy(handle);

	चयन (bud) अणु
	हाल FIRST:
		zhdr->first_chunks = 0;
		अवरोध;
	हाल MIDDLE:
		zhdr->middle_chunks = 0;
		अवरोध;
	हाल LAST:
		zhdr->last_chunks = 0;
		अवरोध;
	शेष:
		pr_err("%s: unknown bud %d\n", __func__, bud);
		WARN_ON(1);
		put_z3fold_header(zhdr);
		वापस;
	पूर्ण

	अगर (!page_claimed)
		मुक्त_handle(handle, zhdr);
	अगर (kref_put(&zhdr->refcount, release_z3fold_page_locked_list)) अणु
		atomic64_dec(&pool->pages_nr);
		वापस;
	पूर्ण
	अगर (page_claimed) अणु
		/* the page has not been claimed by us */
		z3fold_page_unlock(zhdr);
		वापस;
	पूर्ण
	अगर (test_and_set_bit(NEEDS_COMPACTING, &page->निजी)) अणु
		put_z3fold_header(zhdr);
		clear_bit(PAGE_CLAIMED, &page->निजी);
		वापस;
	पूर्ण
	अगर (zhdr->cpu < 0 || !cpu_online(zhdr->cpu)) अणु
		spin_lock(&pool->lock);
		list_del_init(&zhdr->buddy);
		spin_unlock(&pool->lock);
		zhdr->cpu = -1;
		kref_get(&zhdr->refcount);
		clear_bit(PAGE_CLAIMED, &page->निजी);
		करो_compact_page(zhdr, true);
		वापस;
	पूर्ण
	kref_get(&zhdr->refcount);
	clear_bit(PAGE_CLAIMED, &page->निजी);
	queue_work_on(zhdr->cpu, pool->compact_wq, &zhdr->work);
	put_z3fold_header(zhdr);
पूर्ण

/**
 * z3fold_reclaim_page() - evicts allocations from a pool page and मुक्तs it
 * @pool:	pool from which a page will attempt to be evicted
 * @retries:	number of pages on the LRU list क्रम which eviction will
 *		be attempted beक्रमe failing
 *
 * z3fold reclaim is dअगरferent from normal प्रणाली reclaim in that it is करोne
 * from the bottom, up. This is because only the bottom layer, z3fold, has
 * inक्रमmation on how the allocations are organized within each z3fold page.
 * This has the potential to create पूर्णांकeresting locking situations between
 * z3fold and the user, however.
 *
 * To aव्योम these, this is how z3fold_reclaim_page() should be called:
 *
 * The user detects a page should be reclaimed and calls z3fold_reclaim_page().
 * z3fold_reclaim_page() will हटाओ a z3fold page from the pool LRU list and
 * call the user-defined eviction handler with the pool and handle as
 * arguments.
 *
 * If the handle can not be evicted, the eviction handler should वापस
 * non-zero. z3fold_reclaim_page() will add the z3fold page back to the
 * appropriate list and try the next z3fold page on the LRU up to
 * a user defined number of retries.
 *
 * If the handle is successfully evicted, the eviction handler should
 * वापस 0 _and_ should have called z3fold_मुक्त() on the handle. z3fold_मुक्त()
 * contains logic to delay मुक्तing the page अगर the page is under reclaim,
 * as indicated by the setting of the PG_reclaim flag on the underlying page.
 *
 * If all buddies in the z3fold page are successfully evicted, then the
 * z3fold page can be मुक्तd.
 *
 * Returns: 0 अगर page is successfully मुक्तd, otherwise -EINVAL अगर there are
 * no pages to evict or an eviction handler is not रेजिस्टरed, -EAGAIN अगर
 * the retry limit was hit.
 */
अटल पूर्णांक z3fold_reclaim_page(काष्ठा z3fold_pool *pool, अचिन्हित पूर्णांक retries)
अणु
	पूर्णांक i, ret = -1;
	काष्ठा z3fold_header *zhdr = शून्य;
	काष्ठा page *page = शून्य;
	काष्ठा list_head *pos;
	अचिन्हित दीर्घ first_handle = 0, middle_handle = 0, last_handle = 0;
	काष्ठा z3fold_buddy_slots slots __attribute__((aligned(SLOTS_ALIGN)));

	rwlock_init(&slots.lock);
	slots.pool = (अचिन्हित दीर्घ)pool | (1 << HANDLES_NOFREE);

	spin_lock(&pool->lock);
	अगर (!pool->ops || !pool->ops->evict || retries == 0) अणु
		spin_unlock(&pool->lock);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < retries; i++) अणु
		अगर (list_empty(&pool->lru)) अणु
			spin_unlock(&pool->lock);
			वापस -EINVAL;
		पूर्ण
		list_क्रम_each_prev(pos, &pool->lru) अणु
			page = list_entry(pos, काष्ठा page, lru);

			zhdr = page_address(page);
			अगर (test_bit(PAGE_HEADLESS, &page->निजी)) अणु
				/*
				 * For non-headless pages, we रुको to करो this
				 * until we have the page lock to aव्योम racing
				 * with __z3fold_alloc(). Headless pages करोn't
				 * have a lock (and __z3fold_alloc() will never
				 * see them), but we still need to test and set
				 * PAGE_CLAIMED to aव्योम racing with
				 * z3fold_मुक्त(), so just करो it now beक्रमe
				 * leaving the loop.
				 */
				अगर (test_and_set_bit(PAGE_CLAIMED, &page->निजी))
					जारी;

				अवरोध;
			पूर्ण

			अगर (kref_get_unless_zero(&zhdr->refcount) == 0) अणु
				zhdr = शून्य;
				अवरोध;
			पूर्ण
			अगर (!z3fold_page_trylock(zhdr)) अणु
				अगर (kref_put(&zhdr->refcount,
						release_z3fold_page))
					atomic64_dec(&pool->pages_nr);
				zhdr = शून्य;
				जारी; /* can't evict at this poपूर्णांक */
			पूर्ण

			/* test_and_set_bit is of course atomic, but we still
			 * need to करो it under page lock, otherwise checking
			 * that bit in __z3fold_alloc wouldn't make sense
			 */
			अगर (zhdr->क्रमeign_handles ||
			    test_and_set_bit(PAGE_CLAIMED, &page->निजी)) अणु
				अगर (kref_put(&zhdr->refcount,
						release_z3fold_page))
					atomic64_dec(&pool->pages_nr);
				अन्यथा
					z3fold_page_unlock(zhdr);
				zhdr = शून्य;
				जारी; /* can't evict such page */
			पूर्ण
			list_del_init(&zhdr->buddy);
			zhdr->cpu = -1;
			अवरोध;
		पूर्ण

		अगर (!zhdr)
			अवरोध;

		list_del_init(&page->lru);
		spin_unlock(&pool->lock);

		अगर (!test_bit(PAGE_HEADLESS, &page->निजी)) अणु
			/*
			 * We need encode the handles beक्रमe unlocking, and
			 * use our local slots काष्ठाure because z3fold_मुक्त
			 * can zero out zhdr->slots and we can't करो much
			 * about that
			 */
			first_handle = 0;
			last_handle = 0;
			middle_handle = 0;
			स_रखो(slots.slot, 0, माप(slots.slot));
			अगर (zhdr->first_chunks)
				first_handle = __encode_handle(zhdr, &slots,
								FIRST);
			अगर (zhdr->middle_chunks)
				middle_handle = __encode_handle(zhdr, &slots,
								MIDDLE);
			अगर (zhdr->last_chunks)
				last_handle = __encode_handle(zhdr, &slots,
								LAST);
			/*
			 * it's safe to unlock here because we hold a
			 * reference to this page
			 */
			z3fold_page_unlock(zhdr);
		पूर्ण अन्यथा अणु
			first_handle = encode_handle(zhdr, HEADLESS);
			last_handle = middle_handle = 0;
		पूर्ण
		/* Issue the eviction callback(s) */
		अगर (middle_handle) अणु
			ret = pool->ops->evict(pool, middle_handle);
			अगर (ret)
				जाओ next;
		पूर्ण
		अगर (first_handle) अणु
			ret = pool->ops->evict(pool, first_handle);
			अगर (ret)
				जाओ next;
		पूर्ण
		अगर (last_handle) अणु
			ret = pool->ops->evict(pool, last_handle);
			अगर (ret)
				जाओ next;
		पूर्ण
next:
		अगर (test_bit(PAGE_HEADLESS, &page->निजी)) अणु
			अगर (ret == 0) अणु
				मुक्त_z3fold_page(page, true);
				atomic64_dec(&pool->pages_nr);
				वापस 0;
			पूर्ण
			spin_lock(&pool->lock);
			list_add(&page->lru, &pool->lru);
			spin_unlock(&pool->lock);
			clear_bit(PAGE_CLAIMED, &page->निजी);
		पूर्ण अन्यथा अणु
			काष्ठा z3fold_buddy_slots *slots = zhdr->slots;
			z3fold_page_lock(zhdr);
			अगर (kref_put(&zhdr->refcount,
					release_z3fold_page_locked)) अणु
				kmem_cache_मुक्त(pool->c_handle, slots);
				atomic64_dec(&pool->pages_nr);
				वापस 0;
			पूर्ण
			/*
			 * अगर we are here, the page is still not completely
			 * मुक्त. Take the global pool lock then to be able
			 * to add it back to the lru list
			 */
			spin_lock(&pool->lock);
			list_add(&page->lru, &pool->lru);
			spin_unlock(&pool->lock);
			z3fold_page_unlock(zhdr);
			clear_bit(PAGE_CLAIMED, &page->निजी);
		पूर्ण

		/* We started off locked to we need to lock the pool back */
		spin_lock(&pool->lock);
	पूर्ण
	spin_unlock(&pool->lock);
	वापस -EAGAIN;
पूर्ण

/**
 * z3fold_map() - maps the allocation associated with the given handle
 * @pool:	pool in which the allocation resides
 * @handle:	handle associated with the allocation to be mapped
 *
 * Extracts the buddy number from handle and स्थिरructs the poपूर्णांकer to the
 * correct starting chunk within the page.
 *
 * Returns: a poपूर्णांकer to the mapped allocation
 */
अटल व्योम *z3fold_map(काष्ठा z3fold_pool *pool, अचिन्हित दीर्घ handle)
अणु
	काष्ठा z3fold_header *zhdr;
	काष्ठा page *page;
	व्योम *addr;
	क्रमागत buddy buddy;

	zhdr = get_z3fold_header(handle);
	addr = zhdr;
	page = virt_to_page(zhdr);

	अगर (test_bit(PAGE_HEADLESS, &page->निजी))
		जाओ out;

	buddy = handle_to_buddy(handle);
	चयन (buddy) अणु
	हाल FIRST:
		addr += ZHDR_SIZE_ALIGNED;
		अवरोध;
	हाल MIDDLE:
		addr += zhdr->start_middle << CHUNK_SHIFT;
		set_bit(MIDDLE_CHUNK_MAPPED, &page->निजी);
		अवरोध;
	हाल LAST:
		addr += PAGE_SIZE - (handle_to_chunks(handle) << CHUNK_SHIFT);
		अवरोध;
	शेष:
		pr_err("unknown buddy id %d\n", buddy);
		WARN_ON(1);
		addr = शून्य;
		अवरोध;
	पूर्ण

	अगर (addr)
		zhdr->mapped_count++;
out:
	put_z3fold_header(zhdr);
	वापस addr;
पूर्ण

/**
 * z3fold_unmap() - unmaps the allocation associated with the given handle
 * @pool:	pool in which the allocation resides
 * @handle:	handle associated with the allocation to be unmapped
 */
अटल व्योम z3fold_unmap(काष्ठा z3fold_pool *pool, अचिन्हित दीर्घ handle)
अणु
	काष्ठा z3fold_header *zhdr;
	काष्ठा page *page;
	क्रमागत buddy buddy;

	zhdr = get_z3fold_header(handle);
	page = virt_to_page(zhdr);

	अगर (test_bit(PAGE_HEADLESS, &page->निजी))
		वापस;

	buddy = handle_to_buddy(handle);
	अगर (buddy == MIDDLE)
		clear_bit(MIDDLE_CHUNK_MAPPED, &page->निजी);
	zhdr->mapped_count--;
	put_z3fold_header(zhdr);
पूर्ण

/**
 * z3fold_get_pool_size() - माला_लो the z3fold pool size in pages
 * @pool:	pool whose size is being queried
 *
 * Returns: size in pages of the given pool.
 */
अटल u64 z3fold_get_pool_size(काष्ठा z3fold_pool *pool)
अणु
	वापस atomic64_पढ़ो(&pool->pages_nr);
पूर्ण

अटल bool z3fold_page_isolate(काष्ठा page *page, isolate_mode_t mode)
अणु
	काष्ठा z3fold_header *zhdr;
	काष्ठा z3fold_pool *pool;

	VM_BUG_ON_PAGE(!PageMovable(page), page);
	VM_BUG_ON_PAGE(PageIsolated(page), page);

	अगर (test_bit(PAGE_HEADLESS, &page->निजी))
		वापस false;

	zhdr = page_address(page);
	z3fold_page_lock(zhdr);
	अगर (test_bit(NEEDS_COMPACTING, &page->निजी) ||
	    test_bit(PAGE_STALE, &page->निजी))
		जाओ out;

	अगर (zhdr->mapped_count != 0 || zhdr->क्रमeign_handles != 0)
		जाओ out;

	अगर (test_and_set_bit(PAGE_CLAIMED, &page->निजी))
		जाओ out;
	pool = zhdr_to_pool(zhdr);
	spin_lock(&pool->lock);
	अगर (!list_empty(&zhdr->buddy))
		list_del_init(&zhdr->buddy);
	अगर (!list_empty(&page->lru))
		list_del_init(&page->lru);
	spin_unlock(&pool->lock);

	kref_get(&zhdr->refcount);
	z3fold_page_unlock(zhdr);
	वापस true;

out:
	z3fold_page_unlock(zhdr);
	वापस false;
पूर्ण

अटल पूर्णांक z3fold_page_migrate(काष्ठा address_space *mapping, काष्ठा page *newpage,
			       काष्ठा page *page, क्रमागत migrate_mode mode)
अणु
	काष्ठा z3fold_header *zhdr, *new_zhdr;
	काष्ठा z3fold_pool *pool;
	काष्ठा address_space *new_mapping;

	VM_BUG_ON_PAGE(!PageMovable(page), page);
	VM_BUG_ON_PAGE(!PageIsolated(page), page);
	VM_BUG_ON_PAGE(!test_bit(PAGE_CLAIMED, &page->निजी), page);
	VM_BUG_ON_PAGE(!PageLocked(newpage), newpage);

	zhdr = page_address(page);
	pool = zhdr_to_pool(zhdr);

	अगर (!z3fold_page_trylock(zhdr))
		वापस -EAGAIN;
	अगर (zhdr->mapped_count != 0 || zhdr->क्रमeign_handles != 0) अणु
		z3fold_page_unlock(zhdr);
		clear_bit(PAGE_CLAIMED, &page->निजी);
		वापस -EBUSY;
	पूर्ण
	अगर (work_pending(&zhdr->work)) अणु
		z3fold_page_unlock(zhdr);
		वापस -EAGAIN;
	पूर्ण
	new_zhdr = page_address(newpage);
	स_नकल(new_zhdr, zhdr, PAGE_SIZE);
	newpage->निजी = page->निजी;
	page->निजी = 0;
	z3fold_page_unlock(zhdr);
	spin_lock_init(&new_zhdr->page_lock);
	INIT_WORK(&new_zhdr->work, compact_page_work);
	/*
	 * z3fold_page_isolate() ensures that new_zhdr->buddy is empty,
	 * so we only have to reinitialize it.
	 */
	INIT_LIST_HEAD(&new_zhdr->buddy);
	new_mapping = page_mapping(page);
	__ClearPageMovable(page);
	ClearPagePrivate(page);

	get_page(newpage);
	z3fold_page_lock(new_zhdr);
	अगर (new_zhdr->first_chunks)
		encode_handle(new_zhdr, FIRST);
	अगर (new_zhdr->last_chunks)
		encode_handle(new_zhdr, LAST);
	अगर (new_zhdr->middle_chunks)
		encode_handle(new_zhdr, MIDDLE);
	set_bit(NEEDS_COMPACTING, &newpage->निजी);
	new_zhdr->cpu = smp_processor_id();
	spin_lock(&pool->lock);
	list_add(&newpage->lru, &pool->lru);
	spin_unlock(&pool->lock);
	__SetPageMovable(newpage, new_mapping);
	z3fold_page_unlock(new_zhdr);

	queue_work_on(new_zhdr->cpu, pool->compact_wq, &new_zhdr->work);

	page_mapcount_reset(page);
	clear_bit(PAGE_CLAIMED, &page->निजी);
	put_page(page);
	वापस 0;
पूर्ण

अटल व्योम z3fold_page_putback(काष्ठा page *page)
अणु
	काष्ठा z3fold_header *zhdr;
	काष्ठा z3fold_pool *pool;

	zhdr = page_address(page);
	pool = zhdr_to_pool(zhdr);

	z3fold_page_lock(zhdr);
	अगर (!list_empty(&zhdr->buddy))
		list_del_init(&zhdr->buddy);
	INIT_LIST_HEAD(&page->lru);
	अगर (kref_put(&zhdr->refcount, release_z3fold_page_locked)) अणु
		atomic64_dec(&pool->pages_nr);
		वापस;
	पूर्ण
	spin_lock(&pool->lock);
	list_add(&page->lru, &pool->lru);
	spin_unlock(&pool->lock);
	clear_bit(PAGE_CLAIMED, &page->निजी);
	z3fold_page_unlock(zhdr);
पूर्ण

अटल स्थिर काष्ठा address_space_operations z3fold_aops = अणु
	.isolate_page = z3fold_page_isolate,
	.migratepage = z3fold_page_migrate,
	.putback_page = z3fold_page_putback,
पूर्ण;

/*****************
 * zpool
 ****************/

अटल पूर्णांक z3fold_zpool_evict(काष्ठा z3fold_pool *pool, अचिन्हित दीर्घ handle)
अणु
	अगर (pool->zpool && pool->zpool_ops && pool->zpool_ops->evict)
		वापस pool->zpool_ops->evict(pool->zpool, handle);
	अन्यथा
		वापस -ENOENT;
पूर्ण

अटल स्थिर काष्ठा z3fold_ops z3fold_zpool_ops = अणु
	.evict =	z3fold_zpool_evict
पूर्ण;

अटल व्योम *z3fold_zpool_create(स्थिर अक्षर *name, gfp_t gfp,
			       स्थिर काष्ठा zpool_ops *zpool_ops,
			       काष्ठा zpool *zpool)
अणु
	काष्ठा z3fold_pool *pool;

	pool = z3fold_create_pool(name, gfp,
				zpool_ops ? &z3fold_zpool_ops : शून्य);
	अगर (pool) अणु
		pool->zpool = zpool;
		pool->zpool_ops = zpool_ops;
	पूर्ण
	वापस pool;
पूर्ण

अटल व्योम z3fold_zpool_destroy(व्योम *pool)
अणु
	z3fold_destroy_pool(pool);
पूर्ण

अटल पूर्णांक z3fold_zpool_दो_स्मृति(व्योम *pool, माप_प्रकार size, gfp_t gfp,
			अचिन्हित दीर्घ *handle)
अणु
	वापस z3fold_alloc(pool, size, gfp, handle);
पूर्ण
अटल व्योम z3fold_zpool_मुक्त(व्योम *pool, अचिन्हित दीर्घ handle)
अणु
	z3fold_मुक्त(pool, handle);
पूर्ण

अटल पूर्णांक z3fold_zpool_shrink(व्योम *pool, अचिन्हित पूर्णांक pages,
			अचिन्हित पूर्णांक *reclaimed)
अणु
	अचिन्हित पूर्णांक total = 0;
	पूर्णांक ret = -EINVAL;

	जबतक (total < pages) अणु
		ret = z3fold_reclaim_page(pool, 8);
		अगर (ret < 0)
			अवरोध;
		total++;
	पूर्ण

	अगर (reclaimed)
		*reclaimed = total;

	वापस ret;
पूर्ण

अटल व्योम *z3fold_zpool_map(व्योम *pool, अचिन्हित दीर्घ handle,
			क्रमागत zpool_mapmode mm)
अणु
	वापस z3fold_map(pool, handle);
पूर्ण
अटल व्योम z3fold_zpool_unmap(व्योम *pool, अचिन्हित दीर्घ handle)
अणु
	z3fold_unmap(pool, handle);
पूर्ण

अटल u64 z3fold_zpool_total_size(व्योम *pool)
अणु
	वापस z3fold_get_pool_size(pool) * PAGE_SIZE;
पूर्ण

अटल काष्ठा zpool_driver z3fold_zpool_driver = अणु
	.type =		"z3fold",
	.sleep_mapped = true,
	.owner =	THIS_MODULE,
	.create =	z3fold_zpool_create,
	.destroy =	z3fold_zpool_destroy,
	.दो_स्मृति =	z3fold_zpool_दो_स्मृति,
	.मुक्त =		z3fold_zpool_मुक्त,
	.shrink =	z3fold_zpool_shrink,
	.map =		z3fold_zpool_map,
	.unmap =	z3fold_zpool_unmap,
	.total_size =	z3fold_zpool_total_size,
पूर्ण;

MODULE_ALIAS("zpool-z3fold");

अटल पूर्णांक __init init_z3fold(व्योम)
अणु
	पूर्णांक ret;

	/* Make sure the z3fold header is not larger than the page size */
	BUILD_BUG_ON(ZHDR_SIZE_ALIGNED > PAGE_SIZE);
	ret = z3fold_mount();
	अगर (ret)
		वापस ret;

	zpool_रेजिस्टर_driver(&z3fold_zpool_driver);

	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_z3fold(व्योम)
अणु
	z3fold_unmount();
	zpool_unरेजिस्टर_driver(&z3fold_zpool_driver);
पूर्ण

module_init(init_z3fold);
module_निकास(निकास_z3fold);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vitaly Wool <vitalywool@gmail.com>");
MODULE_DESCRIPTION("3-Fold Allocator for Compressed Pages");
