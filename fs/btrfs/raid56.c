<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 Fusion-io  All rights reserved.
 * Copyright (C) 2012 Intel Corp. All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/bपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/raid/pq.h>
#समावेश <linux/hash.h>
#समावेश <linux/list_sort.h>
#समावेश <linux/raid/xor.h>
#समावेश <linux/mm.h>
#समावेश "misc.h"
#समावेश "ctree.h"
#समावेश "disk-io.h"
#समावेश "volumes.h"
#समावेश "raid56.h"
#समावेश "async-thread.h"

/* set when additional merges to this rbio are not allowed */
#घोषणा RBIO_RMW_LOCKED_BIT	1

/*
 * set when this rbio is sitting in the hash, but it is just a cache
 * of past RMW
 */
#घोषणा RBIO_CACHE_BIT		2

/*
 * set when it is safe to trust the stripe_pages क्रम caching
 */
#घोषणा RBIO_CACHE_READY_BIT	3

#घोषणा RBIO_CACHE_SIZE 1024

#घोषणा BTRFS_STRIPE_HASH_TABLE_BITS				11

/* Used by the raid56 code to lock stripes क्रम पढ़ो/modअगरy/ग_लिखो */
काष्ठा btrfs_stripe_hash अणु
	काष्ठा list_head hash_list;
	spinlock_t lock;
पूर्ण;

/* Used by the raid56 code to lock stripes क्रम पढ़ो/modअगरy/ग_लिखो */
काष्ठा btrfs_stripe_hash_table अणु
	काष्ठा list_head stripe_cache;
	spinlock_t cache_lock;
	पूर्णांक cache_size;
	काष्ठा btrfs_stripe_hash table[];
पूर्ण;

क्रमागत btrfs_rbio_ops अणु
	BTRFS_RBIO_WRITE,
	BTRFS_RBIO_READ_REBUILD,
	BTRFS_RBIO_PARITY_SCRUB,
	BTRFS_RBIO_REBUILD_MISSING,
पूर्ण;

काष्ठा btrfs_raid_bio अणु
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_bio *bbio;

	/* जबतक we're करोing rmw on a stripe
	 * we put it पूर्णांकo a hash table so we can
	 * lock the stripe and merge more rbios
	 * पूर्णांकo it.
	 */
	काष्ठा list_head hash_list;

	/*
	 * LRU list क्रम the stripe cache
	 */
	काष्ठा list_head stripe_cache;

	/*
	 * क्रम scheduling work in the helper thपढ़ोs
	 */
	काष्ठा btrfs_work work;

	/*
	 * bio list and bio_list_lock are used
	 * to add more bios पूर्णांकo the stripe
	 * in hopes of aव्योमing the full rmw
	 */
	काष्ठा bio_list bio_list;
	spinlock_t bio_list_lock;

	/* also रक्षित by the bio_list_lock, the
	 * plug list is used by the plugging code
	 * to collect partial bios जबतक plugged.  The
	 * stripe locking code also uses it to hand off
	 * the stripe lock to the next pending IO
	 */
	काष्ठा list_head plug_list;

	/*
	 * flags that tell us अगर it is safe to
	 * merge with this bio
	 */
	अचिन्हित दीर्घ flags;

	/* size of each inभागidual stripe on disk */
	पूर्णांक stripe_len;

	/* number of data stripes (no p/q) */
	पूर्णांक nr_data;

	पूर्णांक real_stripes;

	पूर्णांक stripe_npages;
	/*
	 * set अगर we're करोing a parity rebuild
	 * क्रम a पढ़ो from higher up, which is handled
	 * dअगरferently from a parity rebuild as part of
	 * rmw
	 */
	क्रमागत btrfs_rbio_ops operation;

	/* first bad stripe */
	पूर्णांक faila;

	/* second bad stripe (क्रम raid6 use) */
	पूर्णांक failb;

	पूर्णांक scrubp;
	/*
	 * number of pages needed to represent the full
	 * stripe
	 */
	पूर्णांक nr_pages;

	/*
	 * size of all the bios in the bio_list.  This
	 * helps us decide अगर the rbio maps to a full
	 * stripe or not
	 */
	पूर्णांक bio_list_bytes;

	पूर्णांक generic_bio_cnt;

	refcount_t refs;

	atomic_t stripes_pending;

	atomic_t error;
	/*
	 * these are two arrays of poपूर्णांकers.  We allocate the
	 * rbio big enough to hold them both and setup their
	 * locations when the rbio is allocated
	 */

	/* poपूर्णांकers to pages that we allocated क्रम
	 * पढ़ोing/writing stripes directly from the disk (including P/Q)
	 */
	काष्ठा page **stripe_pages;

	/*
	 * poपूर्णांकers to the pages in the bio_list.  Stored
	 * here क्रम faster lookup
	 */
	काष्ठा page **bio_pages;

	/*
	 * biपंचांगap to record which horizontal stripe has data
	 */
	अचिन्हित दीर्घ *dbiपंचांगap;

	/* allocated with real_stripes-many poपूर्णांकers क्रम finish_*() calls */
	व्योम **finish_poपूर्णांकers;

	/* allocated with stripe_npages-many bits क्रम finish_*() calls */
	अचिन्हित दीर्घ *finish_pbiपंचांगap;
पूर्ण;

अटल पूर्णांक __raid56_parity_recover(काष्ठा btrfs_raid_bio *rbio);
अटल noअंतरभूत व्योम finish_rmw(काष्ठा btrfs_raid_bio *rbio);
अटल व्योम rmw_work(काष्ठा btrfs_work *work);
अटल व्योम पढ़ो_rebuild_work(काष्ठा btrfs_work *work);
अटल पूर्णांक fail_bio_stripe(काष्ठा btrfs_raid_bio *rbio, काष्ठा bio *bio);
अटल पूर्णांक fail_rbio_index(काष्ठा btrfs_raid_bio *rbio, पूर्णांक failed);
अटल व्योम __मुक्त_raid_bio(काष्ठा btrfs_raid_bio *rbio);
अटल व्योम index_rbio_pages(काष्ठा btrfs_raid_bio *rbio);
अटल पूर्णांक alloc_rbio_pages(काष्ठा btrfs_raid_bio *rbio);

अटल noअंतरभूत व्योम finish_parity_scrub(काष्ठा btrfs_raid_bio *rbio,
					 पूर्णांक need_check);
अटल व्योम scrub_parity_work(काष्ठा btrfs_work *work);

अटल व्योम start_async_work(काष्ठा btrfs_raid_bio *rbio, btrfs_func_t work_func)
अणु
	btrfs_init_work(&rbio->work, work_func, शून्य, शून्य);
	btrfs_queue_work(rbio->fs_info->rmw_workers, &rbio->work);
पूर्ण

/*
 * the stripe hash table is used क्रम locking, and to collect
 * bios in hopes of making a full stripe
 */
पूर्णांक btrfs_alloc_stripe_hash_table(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा btrfs_stripe_hash_table *table;
	काष्ठा btrfs_stripe_hash_table *x;
	काष्ठा btrfs_stripe_hash *cur;
	काष्ठा btrfs_stripe_hash *h;
	पूर्णांक num_entries = 1 << BTRFS_STRIPE_HASH_TABLE_BITS;
	पूर्णांक i;

	अगर (info->stripe_hash_table)
		वापस 0;

	/*
	 * The table is large, starting with order 4 and can go as high as
	 * order 7 in हाल lock debugging is turned on.
	 *
	 * Try harder to allocate and fallback to vदो_स्मृति to lower the chance
	 * of a failing mount.
	 */
	table = kvzalloc(काष्ठा_size(table, table, num_entries), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	spin_lock_init(&table->cache_lock);
	INIT_LIST_HEAD(&table->stripe_cache);

	h = table->table;

	क्रम (i = 0; i < num_entries; i++) अणु
		cur = h + i;
		INIT_LIST_HEAD(&cur->hash_list);
		spin_lock_init(&cur->lock);
	पूर्ण

	x = cmpxchg(&info->stripe_hash_table, शून्य, table);
	kvमुक्त(x);
	वापस 0;
पूर्ण

/*
 * caching an rbio means to copy anything from the
 * bio_pages array पूर्णांकo the stripe_pages array.  We
 * use the page uptodate bit in the stripe cache array
 * to indicate अगर it has valid data
 *
 * once the caching is करोne, we set the cache पढ़ोy
 * bit.
 */
अटल व्योम cache_rbio_pages(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	ret = alloc_rbio_pages(rbio);
	अगर (ret)
		वापस;

	क्रम (i = 0; i < rbio->nr_pages; i++) अणु
		अगर (!rbio->bio_pages[i])
			जारी;

		copy_highpage(rbio->stripe_pages[i], rbio->bio_pages[i]);
		SetPageUptodate(rbio->stripe_pages[i]);
	पूर्ण
	set_bit(RBIO_CACHE_READY_BIT, &rbio->flags);
पूर्ण

/*
 * we hash on the first logical address of the stripe
 */
अटल पूर्णांक rbio_bucket(काष्ठा btrfs_raid_bio *rbio)
अणु
	u64 num = rbio->bbio->raid_map[0];

	/*
	 * we shअगरt करोwn quite a bit.  We're using byte
	 * addressing, and most of the lower bits are zeros.
	 * This tends to upset hash_64, and it consistently
	 * वापसs just one or two dअगरferent values.
	 *
	 * shअगरting off the lower bits fixes things.
	 */
	वापस hash_64(num >> 16, BTRFS_STRIPE_HASH_TABLE_BITS);
पूर्ण

/*
 * stealing an rbio means taking all the uptodate pages from the stripe
 * array in the source rbio and putting them पूर्णांकo the destination rbio
 */
अटल व्योम steal_rbio(काष्ठा btrfs_raid_bio *src, काष्ठा btrfs_raid_bio *dest)
अणु
	पूर्णांक i;
	काष्ठा page *s;
	काष्ठा page *d;

	अगर (!test_bit(RBIO_CACHE_READY_BIT, &src->flags))
		वापस;

	क्रम (i = 0; i < dest->nr_pages; i++) अणु
		s = src->stripe_pages[i];
		अगर (!s || !PageUptodate(s)) अणु
			जारी;
		पूर्ण

		d = dest->stripe_pages[i];
		अगर (d)
			__मुक्त_page(d);

		dest->stripe_pages[i] = s;
		src->stripe_pages[i] = शून्य;
	पूर्ण
पूर्ण

/*
 * merging means we take the bio_list from the victim and
 * splice it पूर्णांकo the destination.  The victim should
 * be discarded afterwards.
 *
 * must be called with dest->rbio_list_lock held
 */
अटल व्योम merge_rbio(काष्ठा btrfs_raid_bio *dest,
		       काष्ठा btrfs_raid_bio *victim)
अणु
	bio_list_merge(&dest->bio_list, &victim->bio_list);
	dest->bio_list_bytes += victim->bio_list_bytes;
	dest->generic_bio_cnt += victim->generic_bio_cnt;
	bio_list_init(&victim->bio_list);
पूर्ण

/*
 * used to prune items that are in the cache.  The caller
 * must hold the hash table lock.
 */
अटल व्योम __हटाओ_rbio_from_cache(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक bucket = rbio_bucket(rbio);
	काष्ठा btrfs_stripe_hash_table *table;
	काष्ठा btrfs_stripe_hash *h;
	पूर्णांक मुक्तit = 0;

	/*
	 * check the bit again under the hash table lock.
	 */
	अगर (!test_bit(RBIO_CACHE_BIT, &rbio->flags))
		वापस;

	table = rbio->fs_info->stripe_hash_table;
	h = table->table + bucket;

	/* hold the lock क्रम the bucket because we may be
	 * removing it from the hash table
	 */
	spin_lock(&h->lock);

	/*
	 * hold the lock क्रम the bio list because we need
	 * to make sure the bio list is empty
	 */
	spin_lock(&rbio->bio_list_lock);

	अगर (test_and_clear_bit(RBIO_CACHE_BIT, &rbio->flags)) अणु
		list_del_init(&rbio->stripe_cache);
		table->cache_size -= 1;
		मुक्तit = 1;

		/* अगर the bio list isn't empty, this rbio is
		 * still involved in an IO.  We take it out
		 * of the cache list, and drop the ref that
		 * was held क्रम the list.
		 *
		 * If the bio_list was empty, we also हटाओ
		 * the rbio from the hash_table, and drop
		 * the corresponding ref
		 */
		अगर (bio_list_empty(&rbio->bio_list)) अणु
			अगर (!list_empty(&rbio->hash_list)) अणु
				list_del_init(&rbio->hash_list);
				refcount_dec(&rbio->refs);
				BUG_ON(!list_empty(&rbio->plug_list));
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock(&rbio->bio_list_lock);
	spin_unlock(&h->lock);

	अगर (मुक्तit)
		__मुक्त_raid_bio(rbio);
पूर्ण

/*
 * prune a given rbio from the cache
 */
अटल व्योम हटाओ_rbio_from_cache(काष्ठा btrfs_raid_bio *rbio)
अणु
	काष्ठा btrfs_stripe_hash_table *table;
	अचिन्हित दीर्घ flags;

	अगर (!test_bit(RBIO_CACHE_BIT, &rbio->flags))
		वापस;

	table = rbio->fs_info->stripe_hash_table;

	spin_lock_irqsave(&table->cache_lock, flags);
	__हटाओ_rbio_from_cache(rbio);
	spin_unlock_irqrestore(&table->cache_lock, flags);
पूर्ण

/*
 * हटाओ everything in the cache
 */
अटल व्योम btrfs_clear_rbio_cache(काष्ठा btrfs_fs_info *info)
अणु
	काष्ठा btrfs_stripe_hash_table *table;
	अचिन्हित दीर्घ flags;
	काष्ठा btrfs_raid_bio *rbio;

	table = info->stripe_hash_table;

	spin_lock_irqsave(&table->cache_lock, flags);
	जबतक (!list_empty(&table->stripe_cache)) अणु
		rbio = list_entry(table->stripe_cache.next,
				  काष्ठा btrfs_raid_bio,
				  stripe_cache);
		__हटाओ_rbio_from_cache(rbio);
	पूर्ण
	spin_unlock_irqrestore(&table->cache_lock, flags);
पूर्ण

/*
 * हटाओ all cached entries and मुक्त the hash table
 * used by unmount
 */
व्योम btrfs_मुक्त_stripe_hash_table(काष्ठा btrfs_fs_info *info)
अणु
	अगर (!info->stripe_hash_table)
		वापस;
	btrfs_clear_rbio_cache(info);
	kvमुक्त(info->stripe_hash_table);
	info->stripe_hash_table = शून्य;
पूर्ण

/*
 * insert an rbio पूर्णांकo the stripe cache.  It
 * must have alपढ़ोy been prepared by calling
 * cache_rbio_pages
 *
 * If this rbio was alपढ़ोy cached, it माला_लो
 * moved to the front of the lru.
 *
 * If the size of the rbio cache is too big, we
 * prune an item.
 */
अटल व्योम cache_rbio(काष्ठा btrfs_raid_bio *rbio)
अणु
	काष्ठा btrfs_stripe_hash_table *table;
	अचिन्हित दीर्घ flags;

	अगर (!test_bit(RBIO_CACHE_READY_BIT, &rbio->flags))
		वापस;

	table = rbio->fs_info->stripe_hash_table;

	spin_lock_irqsave(&table->cache_lock, flags);
	spin_lock(&rbio->bio_list_lock);

	/* bump our ref अगर we were not in the list beक्रमe */
	अगर (!test_and_set_bit(RBIO_CACHE_BIT, &rbio->flags))
		refcount_inc(&rbio->refs);

	अगर (!list_empty(&rbio->stripe_cache))अणु
		list_move(&rbio->stripe_cache, &table->stripe_cache);
	पूर्ण अन्यथा अणु
		list_add(&rbio->stripe_cache, &table->stripe_cache);
		table->cache_size += 1;
	पूर्ण

	spin_unlock(&rbio->bio_list_lock);

	अगर (table->cache_size > RBIO_CACHE_SIZE) अणु
		काष्ठा btrfs_raid_bio *found;

		found = list_entry(table->stripe_cache.prev,
				  काष्ठा btrfs_raid_bio,
				  stripe_cache);

		अगर (found != rbio)
			__हटाओ_rbio_from_cache(found);
	पूर्ण

	spin_unlock_irqrestore(&table->cache_lock, flags);
पूर्ण

/*
 * helper function to run the xor_blocks api.  It is only
 * able to करो MAX_XOR_BLOCKS at a समय, so we need to
 * loop through.
 */
अटल व्योम run_xor(व्योम **pages, पूर्णांक src_cnt, sमाप_प्रकार len)
अणु
	पूर्णांक src_off = 0;
	पूर्णांक xor_src_cnt = 0;
	व्योम *dest = pages[src_cnt];

	जबतक(src_cnt > 0) अणु
		xor_src_cnt = min(src_cnt, MAX_XOR_BLOCKS);
		xor_blocks(xor_src_cnt, len, dest, pages + src_off);

		src_cnt -= xor_src_cnt;
		src_off += xor_src_cnt;
	पूर्ण
पूर्ण

/*
 * Returns true अगर the bio list inside this rbio covers an entire stripe (no
 * rmw required).
 */
अटल पूर्णांक rbio_is_full(काष्ठा btrfs_raid_bio *rbio)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ size = rbio->bio_list_bytes;
	पूर्णांक ret = 1;

	spin_lock_irqsave(&rbio->bio_list_lock, flags);
	अगर (size != rbio->nr_data * rbio->stripe_len)
		ret = 0;
	BUG_ON(size > rbio->nr_data * rbio->stripe_len);
	spin_unlock_irqrestore(&rbio->bio_list_lock, flags);

	वापस ret;
पूर्ण

/*
 * वापसs 1 अगर it is safe to merge two rbios together.
 * The merging is safe अगर the two rbios correspond to
 * the same stripe and अगर they are both going in the same
 * direction (पढ़ो vs ग_लिखो), and अगर neither one is
 * locked क्रम final IO
 *
 * The caller is responsible क्रम locking such that
 * rmw_locked is safe to test
 */
अटल पूर्णांक rbio_can_merge(काष्ठा btrfs_raid_bio *last,
			  काष्ठा btrfs_raid_bio *cur)
अणु
	अगर (test_bit(RBIO_RMW_LOCKED_BIT, &last->flags) ||
	    test_bit(RBIO_RMW_LOCKED_BIT, &cur->flags))
		वापस 0;

	/*
	 * we can't merge with cached rbios, since the
	 * idea is that when we merge the destination
	 * rbio is going to run our IO क्रम us.  We can
	 * steal from cached rbios though, other functions
	 * handle that.
	 */
	अगर (test_bit(RBIO_CACHE_BIT, &last->flags) ||
	    test_bit(RBIO_CACHE_BIT, &cur->flags))
		वापस 0;

	अगर (last->bbio->raid_map[0] !=
	    cur->bbio->raid_map[0])
		वापस 0;

	/* we can't merge with dअगरferent operations */
	अगर (last->operation != cur->operation)
		वापस 0;
	/*
	 * We've need पढ़ो the full stripe from the drive.
	 * check and repair the parity and ग_लिखो the new results.
	 *
	 * We're not allowed to add any new bios to the
	 * bio list here, anyone अन्यथा that wants to
	 * change this stripe needs to करो their own rmw.
	 */
	अगर (last->operation == BTRFS_RBIO_PARITY_SCRUB)
		वापस 0;

	अगर (last->operation == BTRFS_RBIO_REBUILD_MISSING)
		वापस 0;

	अगर (last->operation == BTRFS_RBIO_READ_REBUILD) अणु
		पूर्णांक fa = last->faila;
		पूर्णांक fb = last->failb;
		पूर्णांक cur_fa = cur->faila;
		पूर्णांक cur_fb = cur->failb;

		अगर (last->faila >= last->failb) अणु
			fa = last->failb;
			fb = last->faila;
		पूर्ण

		अगर (cur->faila >= cur->failb) अणु
			cur_fa = cur->failb;
			cur_fb = cur->faila;
		पूर्ण

		अगर (fa != cur_fa || fb != cur_fb)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक rbio_stripe_page_index(काष्ठा btrfs_raid_bio *rbio, पूर्णांक stripe,
				  पूर्णांक index)
अणु
	वापस stripe * rbio->stripe_npages + index;
पूर्ण

/*
 * these are just the pages from the rbio array, not from anything
 * the FS sent करोwn to us
 */
अटल काष्ठा page *rbio_stripe_page(काष्ठा btrfs_raid_bio *rbio, पूर्णांक stripe,
				     पूर्णांक index)
अणु
	वापस rbio->stripe_pages[rbio_stripe_page_index(rbio, stripe, index)];
पूर्ण

/*
 * helper to index पूर्णांकo the pstripe
 */
अटल काष्ठा page *rbio_pstripe_page(काष्ठा btrfs_raid_bio *rbio, पूर्णांक index)
अणु
	वापस rbio_stripe_page(rbio, rbio->nr_data, index);
पूर्ण

/*
 * helper to index पूर्णांकo the qstripe, वापसs null
 * अगर there is no qstripe
 */
अटल काष्ठा page *rbio_qstripe_page(काष्ठा btrfs_raid_bio *rbio, पूर्णांक index)
अणु
	अगर (rbio->nr_data + 1 == rbio->real_stripes)
		वापस शून्य;
	वापस rbio_stripe_page(rbio, rbio->nr_data + 1, index);
पूर्ण

/*
 * The first stripe in the table क्रम a logical address
 * has the lock.  rbios are added in one of three ways:
 *
 * 1) Nobody has the stripe locked yet.  The rbio is given
 * the lock and 0 is वापसed.  The caller must start the IO
 * themselves.
 *
 * 2) Someone has the stripe locked, but we're able to merge
 * with the lock owner.  The rbio is मुक्तd and the IO will
 * start स्वतःmatically aदीर्घ with the existing rbio.  1 is वापसed.
 *
 * 3) Someone has the stripe locked, but we're not able to merge.
 * The rbio is added to the lock owner's plug list, or merged पूर्णांकo
 * an rbio alपढ़ोy on the plug list.  When the lock owner unlocks,
 * the next rbio on the list is run and the IO is started स्वतःmatically.
 * 1 is वापसed
 *
 * If we वापस 0, the caller still owns the rbio and must जारी with
 * IO submission.  If we वापस 1, the caller must assume the rbio has
 * alपढ़ोy been मुक्तd.
 */
अटल noअंतरभूत पूर्णांक lock_stripe_add(काष्ठा btrfs_raid_bio *rbio)
अणु
	काष्ठा btrfs_stripe_hash *h;
	काष्ठा btrfs_raid_bio *cur;
	काष्ठा btrfs_raid_bio *pending;
	अचिन्हित दीर्घ flags;
	काष्ठा btrfs_raid_bio *मुक्तit = शून्य;
	काष्ठा btrfs_raid_bio *cache_drop = शून्य;
	पूर्णांक ret = 0;

	h = rbio->fs_info->stripe_hash_table->table + rbio_bucket(rbio);

	spin_lock_irqsave(&h->lock, flags);
	list_क्रम_each_entry(cur, &h->hash_list, hash_list) अणु
		अगर (cur->bbio->raid_map[0] != rbio->bbio->raid_map[0])
			जारी;

		spin_lock(&cur->bio_list_lock);

		/* Can we steal this cached rbio's pages? */
		अगर (bio_list_empty(&cur->bio_list) &&
		    list_empty(&cur->plug_list) &&
		    test_bit(RBIO_CACHE_BIT, &cur->flags) &&
		    !test_bit(RBIO_RMW_LOCKED_BIT, &cur->flags)) अणु
			list_del_init(&cur->hash_list);
			refcount_dec(&cur->refs);

			steal_rbio(cur, rbio);
			cache_drop = cur;
			spin_unlock(&cur->bio_list_lock);

			जाओ lockit;
		पूर्ण

		/* Can we merge पूर्णांकo the lock owner? */
		अगर (rbio_can_merge(cur, rbio)) अणु
			merge_rbio(cur, rbio);
			spin_unlock(&cur->bio_list_lock);
			मुक्तit = rbio;
			ret = 1;
			जाओ out;
		पूर्ण


		/*
		 * We couldn't merge with the running rbio, see अगर we can merge
		 * with the pending ones.  We करोn't have to check क्रम rmw_locked
		 * because there is no way they are inside finish_rmw right now
		 */
		list_क्रम_each_entry(pending, &cur->plug_list, plug_list) अणु
			अगर (rbio_can_merge(pending, rbio)) अणु
				merge_rbio(pending, rbio);
				spin_unlock(&cur->bio_list_lock);
				मुक्तit = rbio;
				ret = 1;
				जाओ out;
			पूर्ण
		पूर्ण

		/*
		 * No merging, put us on the tail of the plug list, our rbio
		 * will be started with the currently running rbio unlocks
		 */
		list_add_tail(&rbio->plug_list, &cur->plug_list);
		spin_unlock(&cur->bio_list_lock);
		ret = 1;
		जाओ out;
	पूर्ण
lockit:
	refcount_inc(&rbio->refs);
	list_add(&rbio->hash_list, &h->hash_list);
out:
	spin_unlock_irqrestore(&h->lock, flags);
	अगर (cache_drop)
		हटाओ_rbio_from_cache(cache_drop);
	अगर (मुक्तit)
		__मुक्त_raid_bio(मुक्तit);
	वापस ret;
पूर्ण

/*
 * called as rmw or parity rebuild is completed.  If the plug list has more
 * rbios रुकोing क्रम this stripe, the next one on the list will be started
 */
अटल noअंतरभूत व्योम unlock_stripe(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक bucket;
	काष्ठा btrfs_stripe_hash *h;
	अचिन्हित दीर्घ flags;
	पूर्णांक keep_cache = 0;

	bucket = rbio_bucket(rbio);
	h = rbio->fs_info->stripe_hash_table->table + bucket;

	अगर (list_empty(&rbio->plug_list))
		cache_rbio(rbio);

	spin_lock_irqsave(&h->lock, flags);
	spin_lock(&rbio->bio_list_lock);

	अगर (!list_empty(&rbio->hash_list)) अणु
		/*
		 * अगर we're still cached and there is no other IO
		 * to perक्रमm, just leave this rbio here क्रम others
		 * to steal from later
		 */
		अगर (list_empty(&rbio->plug_list) &&
		    test_bit(RBIO_CACHE_BIT, &rbio->flags)) अणु
			keep_cache = 1;
			clear_bit(RBIO_RMW_LOCKED_BIT, &rbio->flags);
			BUG_ON(!bio_list_empty(&rbio->bio_list));
			जाओ करोne;
		पूर्ण

		list_del_init(&rbio->hash_list);
		refcount_dec(&rbio->refs);

		/*
		 * we use the plug list to hold all the rbios
		 * रुकोing क्रम the chance to lock this stripe.
		 * hand the lock over to one of them.
		 */
		अगर (!list_empty(&rbio->plug_list)) अणु
			काष्ठा btrfs_raid_bio *next;
			काष्ठा list_head *head = rbio->plug_list.next;

			next = list_entry(head, काष्ठा btrfs_raid_bio,
					  plug_list);

			list_del_init(&rbio->plug_list);

			list_add(&next->hash_list, &h->hash_list);
			refcount_inc(&next->refs);
			spin_unlock(&rbio->bio_list_lock);
			spin_unlock_irqrestore(&h->lock, flags);

			अगर (next->operation == BTRFS_RBIO_READ_REBUILD)
				start_async_work(next, पढ़ो_rebuild_work);
			अन्यथा अगर (next->operation == BTRFS_RBIO_REBUILD_MISSING) अणु
				steal_rbio(rbio, next);
				start_async_work(next, पढ़ो_rebuild_work);
			पूर्ण अन्यथा अगर (next->operation == BTRFS_RBIO_WRITE) अणु
				steal_rbio(rbio, next);
				start_async_work(next, rmw_work);
			पूर्ण अन्यथा अगर (next->operation == BTRFS_RBIO_PARITY_SCRUB) अणु
				steal_rbio(rbio, next);
				start_async_work(next, scrub_parity_work);
			पूर्ण

			जाओ करोne_nolock;
		पूर्ण
	पूर्ण
करोne:
	spin_unlock(&rbio->bio_list_lock);
	spin_unlock_irqrestore(&h->lock, flags);

करोne_nolock:
	अगर (!keep_cache)
		हटाओ_rbio_from_cache(rbio);
पूर्ण

अटल व्योम __मुक्त_raid_bio(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक i;

	अगर (!refcount_dec_and_test(&rbio->refs))
		वापस;

	WARN_ON(!list_empty(&rbio->stripe_cache));
	WARN_ON(!list_empty(&rbio->hash_list));
	WARN_ON(!bio_list_empty(&rbio->bio_list));

	क्रम (i = 0; i < rbio->nr_pages; i++) अणु
		अगर (rbio->stripe_pages[i]) अणु
			__मुक्त_page(rbio->stripe_pages[i]);
			rbio->stripe_pages[i] = शून्य;
		पूर्ण
	पूर्ण

	btrfs_put_bbio(rbio->bbio);
	kमुक्त(rbio);
पूर्ण

अटल व्योम rbio_endio_bio_list(काष्ठा bio *cur, blk_status_t err)
अणु
	काष्ठा bio *next;

	जबतक (cur) अणु
		next = cur->bi_next;
		cur->bi_next = शून्य;
		cur->bi_status = err;
		bio_endio(cur);
		cur = next;
	पूर्ण
पूर्ण

/*
 * this मुक्तs the rbio and runs through all the bios in the
 * bio_list and calls end_io on them
 */
अटल व्योम rbio_orig_end_io(काष्ठा btrfs_raid_bio *rbio, blk_status_t err)
अणु
	काष्ठा bio *cur = bio_list_get(&rbio->bio_list);
	काष्ठा bio *extra;

	अगर (rbio->generic_bio_cnt)
		btrfs_bio_counter_sub(rbio->fs_info, rbio->generic_bio_cnt);

	/*
	 * At this moment, rbio->bio_list is empty, however since rbio करोes not
	 * always have RBIO_RMW_LOCKED_BIT set and rbio is still linked on the
	 * hash list, rbio may be merged with others so that rbio->bio_list
	 * becomes non-empty.
	 * Once unlock_stripe() is करोne, rbio->bio_list will not be updated any
	 * more and we can call bio_endio() on all queued bios.
	 */
	unlock_stripe(rbio);
	extra = bio_list_get(&rbio->bio_list);
	__मुक्त_raid_bio(rbio);

	rbio_endio_bio_list(cur, err);
	अगर (extra)
		rbio_endio_bio_list(extra, err);
पूर्ण

/*
 * end io function used by finish_rmw.  When we finally
 * get here, we've written a full stripe
 */
अटल व्योम raid_ग_लिखो_end_io(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_raid_bio *rbio = bio->bi_निजी;
	blk_status_t err = bio->bi_status;
	पूर्णांक max_errors;

	अगर (err)
		fail_bio_stripe(rbio, bio);

	bio_put(bio);

	अगर (!atomic_dec_and_test(&rbio->stripes_pending))
		वापस;

	err = BLK_STS_OK;

	/* OK, we have पढ़ो all the stripes we need to. */
	max_errors = (rbio->operation == BTRFS_RBIO_PARITY_SCRUB) ?
		     0 : rbio->bbio->max_errors;
	अगर (atomic_पढ़ो(&rbio->error) > max_errors)
		err = BLK_STS_IOERR;

	rbio_orig_end_io(rbio, err);
पूर्ण

/*
 * the पढ़ो/modअगरy/ग_लिखो code wants to use the original bio क्रम
 * any pages it included, and then use the rbio क्रम everything
 * अन्यथा.  This function decides अगर a given index (stripe number)
 * and page number in that stripe fall inside the original bio
 * or the rbio.
 *
 * अगर you set bio_list_only, you'll get a शून्य back क्रम any ranges
 * that are outside the bio_list
 *
 * This करोesn't take any refs on anything, you get a bare page poपूर्णांकer
 * and the caller must bump refs as required.
 *
 * You must call index_rbio_pages once beक्रमe you can trust
 * the answers from this function.
 */
अटल काष्ठा page *page_in_rbio(काष्ठा btrfs_raid_bio *rbio,
				 पूर्णांक index, पूर्णांक pagenr, पूर्णांक bio_list_only)
अणु
	पूर्णांक chunk_page;
	काष्ठा page *p = शून्य;

	chunk_page = index * (rbio->stripe_len >> PAGE_SHIFT) + pagenr;

	spin_lock_irq(&rbio->bio_list_lock);
	p = rbio->bio_pages[chunk_page];
	spin_unlock_irq(&rbio->bio_list_lock);

	अगर (p || bio_list_only)
		वापस p;

	वापस rbio->stripe_pages[chunk_page];
पूर्ण

/*
 * number of pages we need क्रम the entire stripe across all the
 * drives
 */
अटल अचिन्हित दीर्घ rbio_nr_pages(अचिन्हित दीर्घ stripe_len, पूर्णांक nr_stripes)
अणु
	वापस DIV_ROUND_UP(stripe_len, PAGE_SIZE) * nr_stripes;
पूर्ण

/*
 * allocation and initial setup क्रम the btrfs_raid_bio.  Not
 * this करोes not allocate any pages क्रम rbio->pages.
 */
अटल काष्ठा btrfs_raid_bio *alloc_rbio(काष्ठा btrfs_fs_info *fs_info,
					 काष्ठा btrfs_bio *bbio,
					 u64 stripe_len)
अणु
	काष्ठा btrfs_raid_bio *rbio;
	पूर्णांक nr_data = 0;
	पूर्णांक real_stripes = bbio->num_stripes - bbio->num_tgtdevs;
	पूर्णांक num_pages = rbio_nr_pages(stripe_len, real_stripes);
	पूर्णांक stripe_npages = DIV_ROUND_UP(stripe_len, PAGE_SIZE);
	व्योम *p;

	rbio = kzalloc(माप(*rbio) +
		       माप(*rbio->stripe_pages) * num_pages +
		       माप(*rbio->bio_pages) * num_pages +
		       माप(*rbio->finish_poपूर्णांकers) * real_stripes +
		       माप(*rbio->dbiपंचांगap) * BITS_TO_LONGS(stripe_npages) +
		       माप(*rbio->finish_pbiपंचांगap) *
				BITS_TO_LONGS(stripe_npages),
		       GFP_NOFS);
	अगर (!rbio)
		वापस ERR_PTR(-ENOMEM);

	bio_list_init(&rbio->bio_list);
	INIT_LIST_HEAD(&rbio->plug_list);
	spin_lock_init(&rbio->bio_list_lock);
	INIT_LIST_HEAD(&rbio->stripe_cache);
	INIT_LIST_HEAD(&rbio->hash_list);
	rbio->bbio = bbio;
	rbio->fs_info = fs_info;
	rbio->stripe_len = stripe_len;
	rbio->nr_pages = num_pages;
	rbio->real_stripes = real_stripes;
	rbio->stripe_npages = stripe_npages;
	rbio->faila = -1;
	rbio->failb = -1;
	refcount_set(&rbio->refs, 1);
	atomic_set(&rbio->error, 0);
	atomic_set(&rbio->stripes_pending, 0);

	/*
	 * the stripe_pages, bio_pages, etc arrays poपूर्णांक to the extra
	 * memory we allocated past the end of the rbio
	 */
	p = rbio + 1;
#घोषणा CONSUME_ALLOC(ptr, count)	करो अणु				\
		ptr = p;						\
		p = (अचिन्हित अक्षर *)p + माप(*(ptr)) * (count);	\
	पूर्ण जबतक (0)
	CONSUME_ALLOC(rbio->stripe_pages, num_pages);
	CONSUME_ALLOC(rbio->bio_pages, num_pages);
	CONSUME_ALLOC(rbio->finish_poपूर्णांकers, real_stripes);
	CONSUME_ALLOC(rbio->dbiपंचांगap, BITS_TO_LONGS(stripe_npages));
	CONSUME_ALLOC(rbio->finish_pbiपंचांगap, BITS_TO_LONGS(stripe_npages));
#अघोषित  CONSUME_ALLOC

	अगर (bbio->map_type & BTRFS_BLOCK_GROUP_RAID5)
		nr_data = real_stripes - 1;
	अन्यथा अगर (bbio->map_type & BTRFS_BLOCK_GROUP_RAID6)
		nr_data = real_stripes - 2;
	अन्यथा
		BUG();

	rbio->nr_data = nr_data;
	वापस rbio;
पूर्ण

/* allocate pages क्रम all the stripes in the bio, including parity */
अटल पूर्णांक alloc_rbio_pages(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक i;
	काष्ठा page *page;

	क्रम (i = 0; i < rbio->nr_pages; i++) अणु
		अगर (rbio->stripe_pages[i])
			जारी;
		page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
		अगर (!page)
			वापस -ENOMEM;
		rbio->stripe_pages[i] = page;
	पूर्ण
	वापस 0;
पूर्ण

/* only allocate pages क्रम p/q stripes */
अटल पूर्णांक alloc_rbio_parity_pages(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक i;
	काष्ठा page *page;

	i = rbio_stripe_page_index(rbio, rbio->nr_data, 0);

	क्रम (; i < rbio->nr_pages; i++) अणु
		अगर (rbio->stripe_pages[i])
			जारी;
		page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
		अगर (!page)
			वापस -ENOMEM;
		rbio->stripe_pages[i] = page;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * add a single page from a specअगरic stripe पूर्णांकo our list of bios क्रम IO
 * this will try to merge पूर्णांकo existing bios अगर possible, and वापसs
 * zero अगर all went well.
 */
अटल पूर्णांक rbio_add_io_page(काष्ठा btrfs_raid_bio *rbio,
			    काष्ठा bio_list *bio_list,
			    काष्ठा page *page,
			    पूर्णांक stripe_nr,
			    अचिन्हित दीर्घ page_index,
			    अचिन्हित दीर्घ bio_max_len)
अणु
	काष्ठा bio *last = bio_list->tail;
	पूर्णांक ret;
	काष्ठा bio *bio;
	काष्ठा btrfs_bio_stripe *stripe;
	u64 disk_start;

	stripe = &rbio->bbio->stripes[stripe_nr];
	disk_start = stripe->physical + (page_index << PAGE_SHIFT);

	/* अगर the device is missing, just fail this stripe */
	अगर (!stripe->dev->bdev)
		वापस fail_rbio_index(rbio, stripe_nr);

	/* see अगर we can add this page onto our existing bio */
	अगर (last) अणु
		u64 last_end = last->bi_iter.bi_sector << 9;
		last_end += last->bi_iter.bi_size;

		/*
		 * we can't merge these अगर they are from dअगरferent
		 * devices or अगर they are not contiguous
		 */
		अगर (last_end == disk_start && !last->bi_status &&
		    last->bi_bdev == stripe->dev->bdev) अणु
			ret = bio_add_page(last, page, PAGE_SIZE, 0);
			अगर (ret == PAGE_SIZE)
				वापस 0;
		पूर्ण
	पूर्ण

	/* put a new bio on the list */
	bio = btrfs_io_bio_alloc(bio_max_len >> PAGE_SHIFT ?: 1);
	btrfs_io_bio(bio)->device = stripe->dev;
	bio->bi_iter.bi_size = 0;
	bio_set_dev(bio, stripe->dev->bdev);
	bio->bi_iter.bi_sector = disk_start >> 9;

	bio_add_page(bio, page, PAGE_SIZE, 0);
	bio_list_add(bio_list, bio);
	वापस 0;
पूर्ण

/*
 * जबतक we're करोing the पढ़ो/modअगरy/ग_लिखो cycle, we could
 * have errors in पढ़ोing pages off the disk.  This checks
 * क्रम errors and अगर we're not able to read the page it'll
 * trigger parity reस्थिरruction.  The rmw will be finished
 * after we've reस्थिरructed the failed stripes
 */
अटल व्योम validate_rbio_क्रम_rmw(काष्ठा btrfs_raid_bio *rbio)
अणु
	अगर (rbio->faila >= 0 || rbio->failb >= 0) अणु
		BUG_ON(rbio->faila == rbio->real_stripes - 1);
		__raid56_parity_recover(rbio);
	पूर्ण अन्यथा अणु
		finish_rmw(rbio);
	पूर्ण
पूर्ण

/*
 * helper function to walk our bio list and populate the bio_pages array with
 * the result.  This seems expensive, but it is faster than स्थिरantly
 * searching through the bio list as we setup the IO in finish_rmw or stripe
 * reस्थिरruction.
 *
 * This must be called beक्रमe you trust the answers from page_in_rbio
 */
अटल व्योम index_rbio_pages(काष्ठा btrfs_raid_bio *rbio)
अणु
	काष्ठा bio *bio;
	u64 start;
	अचिन्हित दीर्घ stripe_offset;
	अचिन्हित दीर्घ page_index;

	spin_lock_irq(&rbio->bio_list_lock);
	bio_list_क्रम_each(bio, &rbio->bio_list) अणु
		काष्ठा bio_vec bvec;
		काष्ठा bvec_iter iter;
		पूर्णांक i = 0;

		start = bio->bi_iter.bi_sector << 9;
		stripe_offset = start - rbio->bbio->raid_map[0];
		page_index = stripe_offset >> PAGE_SHIFT;

		अगर (bio_flagged(bio, BIO_CLONED))
			bio->bi_iter = btrfs_io_bio(bio)->iter;

		bio_क्रम_each_segment(bvec, bio, iter) अणु
			rbio->bio_pages[page_index + i] = bvec.bv_page;
			i++;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&rbio->bio_list_lock);
पूर्ण

/*
 * this is called from one of two situations.  We either
 * have a full stripe from the higher layers, or we've पढ़ो all
 * the missing bits off disk.
 *
 * This will calculate the parity and then send करोwn any
 * changed blocks.
 */
अटल noअंतरभूत व्योम finish_rmw(काष्ठा btrfs_raid_bio *rbio)
अणु
	काष्ठा btrfs_bio *bbio = rbio->bbio;
	व्योम **poपूर्णांकers = rbio->finish_poपूर्णांकers;
	पूर्णांक nr_data = rbio->nr_data;
	पूर्णांक stripe;
	पूर्णांक pagenr;
	bool has_qstripe;
	काष्ठा bio_list bio_list;
	काष्ठा bio *bio;
	पूर्णांक ret;

	bio_list_init(&bio_list);

	अगर (rbio->real_stripes - rbio->nr_data == 1)
		has_qstripe = false;
	अन्यथा अगर (rbio->real_stripes - rbio->nr_data == 2)
		has_qstripe = true;
	अन्यथा
		BUG();

	/* at this poपूर्णांक we either have a full stripe,
	 * or we've पढ़ो the full stripe from the drive.
	 * recalculate the parity and ग_लिखो the new results.
	 *
	 * We're not allowed to add any new bios to the
	 * bio list here, anyone अन्यथा that wants to
	 * change this stripe needs to करो their own rmw.
	 */
	spin_lock_irq(&rbio->bio_list_lock);
	set_bit(RBIO_RMW_LOCKED_BIT, &rbio->flags);
	spin_unlock_irq(&rbio->bio_list_lock);

	atomic_set(&rbio->error, 0);

	/*
	 * now that we've set rmw_locked, run through the
	 * bio list one last समय and map the page poपूर्णांकers
	 *
	 * We करोn't cache full rbios because we're assuming
	 * the higher layers are unlikely to use this area of
	 * the disk again soon.  If they करो use it again,
	 * hopefully they will send another full bio.
	 */
	index_rbio_pages(rbio);
	अगर (!rbio_is_full(rbio))
		cache_rbio_pages(rbio);
	अन्यथा
		clear_bit(RBIO_CACHE_READY_BIT, &rbio->flags);

	क्रम (pagenr = 0; pagenr < rbio->stripe_npages; pagenr++) अणु
		काष्ठा page *p;
		/* first collect one page from each data stripe */
		क्रम (stripe = 0; stripe < nr_data; stripe++) अणु
			p = page_in_rbio(rbio, stripe, pagenr, 0);
			poपूर्णांकers[stripe] = kmap_local_page(p);
		पूर्ण

		/* then add the parity stripe */
		p = rbio_pstripe_page(rbio, pagenr);
		SetPageUptodate(p);
		poपूर्णांकers[stripe++] = kmap_local_page(p);

		अगर (has_qstripe) अणु

			/*
			 * raid6, add the qstripe and call the
			 * library function to fill in our p/q
			 */
			p = rbio_qstripe_page(rbio, pagenr);
			SetPageUptodate(p);
			poपूर्णांकers[stripe++] = kmap_local_page(p);

			raid6_call.gen_syndrome(rbio->real_stripes, PAGE_SIZE,
						poपूर्णांकers);
		पूर्ण अन्यथा अणु
			/* raid5 */
			copy_page(poपूर्णांकers[nr_data], poपूर्णांकers[0]);
			run_xor(poपूर्णांकers + 1, nr_data - 1, PAGE_SIZE);
		पूर्ण
		क्रम (stripe = stripe - 1; stripe >= 0; stripe--)
			kunmap_local(poपूर्णांकers[stripe]);
	पूर्ण

	/*
	 * समय to start writing.  Make bios क्रम everything from the
	 * higher layers (the bio_list in our rbio) and our p/q.  Ignore
	 * everything अन्यथा.
	 */
	क्रम (stripe = 0; stripe < rbio->real_stripes; stripe++) अणु
		क्रम (pagenr = 0; pagenr < rbio->stripe_npages; pagenr++) अणु
			काष्ठा page *page;
			अगर (stripe < rbio->nr_data) अणु
				page = page_in_rbio(rbio, stripe, pagenr, 1);
				अगर (!page)
					जारी;
			पूर्ण अन्यथा अणु
			       page = rbio_stripe_page(rbio, stripe, pagenr);
			पूर्ण

			ret = rbio_add_io_page(rbio, &bio_list,
				       page, stripe, pagenr, rbio->stripe_len);
			अगर (ret)
				जाओ cleanup;
		पूर्ण
	पूर्ण

	अगर (likely(!bbio->num_tgtdevs))
		जाओ ग_लिखो_data;

	क्रम (stripe = 0; stripe < rbio->real_stripes; stripe++) अणु
		अगर (!bbio->tgtdev_map[stripe])
			जारी;

		क्रम (pagenr = 0; pagenr < rbio->stripe_npages; pagenr++) अणु
			काष्ठा page *page;
			अगर (stripe < rbio->nr_data) अणु
				page = page_in_rbio(rbio, stripe, pagenr, 1);
				अगर (!page)
					जारी;
			पूर्ण अन्यथा अणु
			       page = rbio_stripe_page(rbio, stripe, pagenr);
			पूर्ण

			ret = rbio_add_io_page(rbio, &bio_list, page,
					       rbio->bbio->tgtdev_map[stripe],
					       pagenr, rbio->stripe_len);
			अगर (ret)
				जाओ cleanup;
		पूर्ण
	पूर्ण

ग_लिखो_data:
	atomic_set(&rbio->stripes_pending, bio_list_size(&bio_list));
	BUG_ON(atomic_पढ़ो(&rbio->stripes_pending) == 0);

	जबतक ((bio = bio_list_pop(&bio_list))) अणु
		bio->bi_निजी = rbio;
		bio->bi_end_io = raid_ग_लिखो_end_io;
		bio->bi_opf = REQ_OP_WRITE;

		submit_bio(bio);
	पूर्ण
	वापस;

cleanup:
	rbio_orig_end_io(rbio, BLK_STS_IOERR);

	जबतक ((bio = bio_list_pop(&bio_list)))
		bio_put(bio);
पूर्ण

/*
 * helper to find the stripe number क्रम a given bio.  Used to figure out which
 * stripe has failed.  This expects the bio to correspond to a physical disk,
 * so it looks up based on physical sector numbers.
 */
अटल पूर्णांक find_bio_stripe(काष्ठा btrfs_raid_bio *rbio,
			   काष्ठा bio *bio)
अणु
	u64 physical = bio->bi_iter.bi_sector;
	पूर्णांक i;
	काष्ठा btrfs_bio_stripe *stripe;

	physical <<= 9;

	क्रम (i = 0; i < rbio->bbio->num_stripes; i++) अणु
		stripe = &rbio->bbio->stripes[i];
		अगर (in_range(physical, stripe->physical, rbio->stripe_len) &&
		    stripe->dev->bdev && bio->bi_bdev == stripe->dev->bdev) अणु
			वापस i;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

/*
 * helper to find the stripe number क्रम a given
 * bio (beक्रमe mapping).  Used to figure out which stripe has
 * failed.  This looks up based on logical block numbers.
 */
अटल पूर्णांक find_logical_bio_stripe(काष्ठा btrfs_raid_bio *rbio,
				   काष्ठा bio *bio)
अणु
	u64 logical = bio->bi_iter.bi_sector << 9;
	पूर्णांक i;

	क्रम (i = 0; i < rbio->nr_data; i++) अणु
		u64 stripe_start = rbio->bbio->raid_map[i];

		अगर (in_range(logical, stripe_start, rbio->stripe_len))
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

/*
 * वापसs -EIO अगर we had too many failures
 */
अटल पूर्णांक fail_rbio_index(काष्ठा btrfs_raid_bio *rbio, पूर्णांक failed)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&rbio->bio_list_lock, flags);

	/* we alपढ़ोy know this stripe is bad, move on */
	अगर (rbio->faila == failed || rbio->failb == failed)
		जाओ out;

	अगर (rbio->faila == -1) अणु
		/* first failure on this rbio */
		rbio->faila = failed;
		atomic_inc(&rbio->error);
	पूर्ण अन्यथा अगर (rbio->failb == -1) अणु
		/* second failure on this rbio */
		rbio->failb = failed;
		atomic_inc(&rbio->error);
	पूर्ण अन्यथा अणु
		ret = -EIO;
	पूर्ण
out:
	spin_unlock_irqrestore(&rbio->bio_list_lock, flags);

	वापस ret;
पूर्ण

/*
 * helper to fail a stripe based on a physical disk
 * bio.
 */
अटल पूर्णांक fail_bio_stripe(काष्ठा btrfs_raid_bio *rbio,
			   काष्ठा bio *bio)
अणु
	पूर्णांक failed = find_bio_stripe(rbio, bio);

	अगर (failed < 0)
		वापस -EIO;

	वापस fail_rbio_index(rbio, failed);
पूर्ण

/*
 * this sets each page in the bio uptodate.  It should only be used on निजी
 * rbio pages, nothing that comes in from the higher layers
 */
अटल व्योम set_bio_pages_uptodate(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	ASSERT(!bio_flagged(bio, BIO_CLONED));

	bio_क्रम_each_segment_all(bvec, bio, iter_all)
		SetPageUptodate(bvec->bv_page);
पूर्ण

/*
 * end io क्रम the पढ़ो phase of the rmw cycle.  All the bios here are physical
 * stripe bios we've पढ़ो from the disk so we can recalculate the parity of the
 * stripe.
 *
 * This will usually kick off finish_rmw once all the bios are पढ़ो in, but it
 * may trigger parity reस्थिरruction अगर we had any errors aदीर्घ the way
 */
अटल व्योम raid_rmw_end_io(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_raid_bio *rbio = bio->bi_निजी;

	अगर (bio->bi_status)
		fail_bio_stripe(rbio, bio);
	अन्यथा
		set_bio_pages_uptodate(bio);

	bio_put(bio);

	अगर (!atomic_dec_and_test(&rbio->stripes_pending))
		वापस;

	अगर (atomic_पढ़ो(&rbio->error) > rbio->bbio->max_errors)
		जाओ cleanup;

	/*
	 * this will normally call finish_rmw to start our ग_लिखो
	 * but अगर there are any failed stripes we'll reस्थिरruct
	 * from parity first
	 */
	validate_rbio_क्रम_rmw(rbio);
	वापस;

cleanup:

	rbio_orig_end_io(rbio, BLK_STS_IOERR);
पूर्ण

/*
 * the stripe must be locked by the caller.  It will
 * unlock after all the ग_लिखोs are करोne
 */
अटल पूर्णांक raid56_rmw_stripe(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक bios_to_पढ़ो = 0;
	काष्ठा bio_list bio_list;
	पूर्णांक ret;
	पूर्णांक pagenr;
	पूर्णांक stripe;
	काष्ठा bio *bio;

	bio_list_init(&bio_list);

	ret = alloc_rbio_pages(rbio);
	अगर (ret)
		जाओ cleanup;

	index_rbio_pages(rbio);

	atomic_set(&rbio->error, 0);
	/*
	 * build a list of bios to पढ़ो all the missing parts of this
	 * stripe
	 */
	क्रम (stripe = 0; stripe < rbio->nr_data; stripe++) अणु
		क्रम (pagenr = 0; pagenr < rbio->stripe_npages; pagenr++) अणु
			काष्ठा page *page;
			/*
			 * we want to find all the pages missing from
			 * the rbio and पढ़ो them from the disk.  If
			 * page_in_rbio finds a page in the bio list
			 * we करोn't need to पढ़ो it off the stripe.
			 */
			page = page_in_rbio(rbio, stripe, pagenr, 1);
			अगर (page)
				जारी;

			page = rbio_stripe_page(rbio, stripe, pagenr);
			/*
			 * the bio cache may have handed us an uptodate
			 * page.  If so, be happy and use it
			 */
			अगर (PageUptodate(page))
				जारी;

			ret = rbio_add_io_page(rbio, &bio_list, page,
				       stripe, pagenr, rbio->stripe_len);
			अगर (ret)
				जाओ cleanup;
		पूर्ण
	पूर्ण

	bios_to_पढ़ो = bio_list_size(&bio_list);
	अगर (!bios_to_पढ़ो) अणु
		/*
		 * this can happen अगर others have merged with
		 * us, it means there is nothing left to पढ़ो.
		 * But अगर there are missing devices it may not be
		 * safe to करो the full stripe ग_लिखो yet.
		 */
		जाओ finish;
	पूर्ण

	/*
	 * the bbio may be मुक्तd once we submit the last bio.  Make sure
	 * not to touch it after that
	 */
	atomic_set(&rbio->stripes_pending, bios_to_पढ़ो);
	जबतक ((bio = bio_list_pop(&bio_list))) अणु
		bio->bi_निजी = rbio;
		bio->bi_end_io = raid_rmw_end_io;
		bio->bi_opf = REQ_OP_READ;

		btrfs_bio_wq_end_io(rbio->fs_info, bio, BTRFS_WQ_ENDIO_RAID56);

		submit_bio(bio);
	पूर्ण
	/* the actual ग_लिखो will happen once the पढ़ोs are करोne */
	वापस 0;

cleanup:
	rbio_orig_end_io(rbio, BLK_STS_IOERR);

	जबतक ((bio = bio_list_pop(&bio_list)))
		bio_put(bio);

	वापस -EIO;

finish:
	validate_rbio_क्रम_rmw(rbio);
	वापस 0;
पूर्ण

/*
 * अगर the upper layers pass in a full stripe, we thank them by only allocating
 * enough pages to hold the parity, and sending it all करोwn quickly.
 */
अटल पूर्णांक full_stripe_ग_लिखो(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक ret;

	ret = alloc_rbio_parity_pages(rbio);
	अगर (ret) अणु
		__मुक्त_raid_bio(rbio);
		वापस ret;
	पूर्ण

	ret = lock_stripe_add(rbio);
	अगर (ret == 0)
		finish_rmw(rbio);
	वापस 0;
पूर्ण

/*
 * partial stripe ग_लिखोs get handed over to async helpers.
 * We're really hoping to merge a few more ग_लिखोs पूर्णांकo this
 * rbio beक्रमe calculating new parity
 */
अटल पूर्णांक partial_stripe_ग_लिखो(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक ret;

	ret = lock_stripe_add(rbio);
	अगर (ret == 0)
		start_async_work(rbio, rmw_work);
	वापस 0;
पूर्ण

/*
 * someबार जबतक we were पढ़ोing from the drive to
 * recalculate parity, enough new bios come पूर्णांकo create
 * a full stripe.  So we करो a check here to see अगर we can
 * go directly to finish_rmw
 */
अटल पूर्णांक __raid56_parity_ग_लिखो(काष्ठा btrfs_raid_bio *rbio)
अणु
	/* head off पूर्णांकo rmw land अगर we करोn't have a full stripe */
	अगर (!rbio_is_full(rbio))
		वापस partial_stripe_ग_लिखो(rbio);
	वापस full_stripe_ग_लिखो(rbio);
पूर्ण

/*
 * We use plugging call backs to collect full stripes.
 * Any समय we get a partial stripe ग_लिखो जबतक plugged
 * we collect it पूर्णांकo a list.  When the unplug comes करोwn,
 * we sort the list by logical block number and merge
 * everything we can पूर्णांकo the same rbios
 */
काष्ठा btrfs_plug_cb अणु
	काष्ठा blk_plug_cb cb;
	काष्ठा btrfs_fs_info *info;
	काष्ठा list_head rbio_list;
	काष्ठा btrfs_work work;
पूर्ण;

/*
 * rbios on the plug list are sorted क्रम easier merging.
 */
अटल पूर्णांक plug_cmp(व्योम *priv, स्थिर काष्ठा list_head *a,
		    स्थिर काष्ठा list_head *b)
अणु
	काष्ठा btrfs_raid_bio *ra = container_of(a, काष्ठा btrfs_raid_bio,
						 plug_list);
	काष्ठा btrfs_raid_bio *rb = container_of(b, काष्ठा btrfs_raid_bio,
						 plug_list);
	u64 a_sector = ra->bio_list.head->bi_iter.bi_sector;
	u64 b_sector = rb->bio_list.head->bi_iter.bi_sector;

	अगर (a_sector < b_sector)
		वापस -1;
	अगर (a_sector > b_sector)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम run_plug(काष्ठा btrfs_plug_cb *plug)
अणु
	काष्ठा btrfs_raid_bio *cur;
	काष्ठा btrfs_raid_bio *last = शून्य;

	/*
	 * sort our plug list then try to merge
	 * everything we can in hopes of creating full
	 * stripes.
	 */
	list_sort(शून्य, &plug->rbio_list, plug_cmp);
	जबतक (!list_empty(&plug->rbio_list)) अणु
		cur = list_entry(plug->rbio_list.next,
				 काष्ठा btrfs_raid_bio, plug_list);
		list_del_init(&cur->plug_list);

		अगर (rbio_is_full(cur)) अणु
			पूर्णांक ret;

			/* we have a full stripe, send it करोwn */
			ret = full_stripe_ग_लिखो(cur);
			BUG_ON(ret);
			जारी;
		पूर्ण
		अगर (last) अणु
			अगर (rbio_can_merge(last, cur)) अणु
				merge_rbio(last, cur);
				__मुक्त_raid_bio(cur);
				जारी;

			पूर्ण
			__raid56_parity_ग_लिखो(last);
		पूर्ण
		last = cur;
	पूर्ण
	अगर (last) अणु
		__raid56_parity_ग_लिखो(last);
	पूर्ण
	kमुक्त(plug);
पूर्ण

/*
 * अगर the unplug comes from schedule, we have to push the
 * work off to a helper thपढ़ो
 */
अटल व्योम unplug_work(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_plug_cb *plug;
	plug = container_of(work, काष्ठा btrfs_plug_cb, work);
	run_plug(plug);
पूर्ण

अटल व्योम btrfs_raid_unplug(काष्ठा blk_plug_cb *cb, bool from_schedule)
अणु
	काष्ठा btrfs_plug_cb *plug;
	plug = container_of(cb, काष्ठा btrfs_plug_cb, cb);

	अगर (from_schedule) अणु
		btrfs_init_work(&plug->work, unplug_work, शून्य, शून्य);
		btrfs_queue_work(plug->info->rmw_workers,
				 &plug->work);
		वापस;
	पूर्ण
	run_plug(plug);
पूर्ण

/*
 * our मुख्य entry poपूर्णांक क्रम ग_लिखोs from the rest of the FS.
 */
पूर्णांक raid56_parity_ग_लिखो(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			काष्ठा btrfs_bio *bbio, u64 stripe_len)
अणु
	काष्ठा btrfs_raid_bio *rbio;
	काष्ठा btrfs_plug_cb *plug = शून्य;
	काष्ठा blk_plug_cb *cb;
	पूर्णांक ret;

	rbio = alloc_rbio(fs_info, bbio, stripe_len);
	अगर (IS_ERR(rbio)) अणु
		btrfs_put_bbio(bbio);
		वापस PTR_ERR(rbio);
	पूर्ण
	bio_list_add(&rbio->bio_list, bio);
	rbio->bio_list_bytes = bio->bi_iter.bi_size;
	rbio->operation = BTRFS_RBIO_WRITE;

	btrfs_bio_counter_inc_noblocked(fs_info);
	rbio->generic_bio_cnt = 1;

	/*
	 * करोn't plug on full rbios, just get them out the करोor
	 * as quickly as we can
	 */
	अगर (rbio_is_full(rbio)) अणु
		ret = full_stripe_ग_लिखो(rbio);
		अगर (ret)
			btrfs_bio_counter_dec(fs_info);
		वापस ret;
	पूर्ण

	cb = blk_check_plugged(btrfs_raid_unplug, fs_info, माप(*plug));
	अगर (cb) अणु
		plug = container_of(cb, काष्ठा btrfs_plug_cb, cb);
		अगर (!plug->info) अणु
			plug->info = fs_info;
			INIT_LIST_HEAD(&plug->rbio_list);
		पूर्ण
		list_add_tail(&rbio->plug_list, &plug->rbio_list);
		ret = 0;
	पूर्ण अन्यथा अणु
		ret = __raid56_parity_ग_लिखो(rbio);
		अगर (ret)
			btrfs_bio_counter_dec(fs_info);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * all parity reस्थिरruction happens here.  We've पढ़ो in everything
 * we can find from the drives and this करोes the heavy lअगरting of
 * sorting the good from the bad.
 */
अटल व्योम __raid_recover_end_io(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक pagenr, stripe;
	व्योम **poपूर्णांकers;
	व्योम **unmap_array;
	पूर्णांक faila = -1, failb = -1;
	काष्ठा page *page;
	blk_status_t err;
	पूर्णांक i;

	poपूर्णांकers = kसुस्मृति(rbio->real_stripes, माप(व्योम *), GFP_NOFS);
	अगर (!poपूर्णांकers) अणु
		err = BLK_STS_RESOURCE;
		जाओ cleanup_io;
	पूर्ण

	/*
	 * Store copy of poपूर्णांकers that करोes not get reordered during
	 * reस्थिरruction so that kunmap_local works.
	 */
	unmap_array = kसुस्मृति(rbio->real_stripes, माप(व्योम *), GFP_NOFS);
	अगर (!unmap_array) अणु
		err = BLK_STS_RESOURCE;
		जाओ cleanup_poपूर्णांकers;
	पूर्ण

	faila = rbio->faila;
	failb = rbio->failb;

	अगर (rbio->operation == BTRFS_RBIO_READ_REBUILD ||
	    rbio->operation == BTRFS_RBIO_REBUILD_MISSING) अणु
		spin_lock_irq(&rbio->bio_list_lock);
		set_bit(RBIO_RMW_LOCKED_BIT, &rbio->flags);
		spin_unlock_irq(&rbio->bio_list_lock);
	पूर्ण

	index_rbio_pages(rbio);

	क्रम (pagenr = 0; pagenr < rbio->stripe_npages; pagenr++) अणु
		/*
		 * Now we just use biपंचांगap to mark the horizontal stripes in
		 * which we have data when करोing parity scrub.
		 */
		अगर (rbio->operation == BTRFS_RBIO_PARITY_SCRUB &&
		    !test_bit(pagenr, rbio->dbiपंचांगap))
			जारी;

		/*
		 * Setup our array of poपूर्णांकers with pages from each stripe
		 *
		 * NOTE: store a duplicate array of poपूर्णांकers to preserve the
		 * poपूर्णांकer order
		 */
		क्रम (stripe = 0; stripe < rbio->real_stripes; stripe++) अणु
			/*
			 * अगर we're rebuilding a पढ़ो, we have to use
			 * pages from the bio list
			 */
			अगर ((rbio->operation == BTRFS_RBIO_READ_REBUILD ||
			     rbio->operation == BTRFS_RBIO_REBUILD_MISSING) &&
			    (stripe == faila || stripe == failb)) अणु
				page = page_in_rbio(rbio, stripe, pagenr, 0);
			पूर्ण अन्यथा अणु
				page = rbio_stripe_page(rbio, stripe, pagenr);
			पूर्ण
			poपूर्णांकers[stripe] = kmap_local_page(page);
			unmap_array[stripe] = poपूर्णांकers[stripe];
		पूर्ण

		/* all raid6 handling here */
		अगर (rbio->bbio->map_type & BTRFS_BLOCK_GROUP_RAID6) अणु
			/*
			 * single failure, rebuild from parity raid5
			 * style
			 */
			अगर (failb < 0) अणु
				अगर (faila == rbio->nr_data) अणु
					/*
					 * Just the P stripe has failed, without
					 * a bad data or Q stripe.
					 * TODO, we should reकरो the xor here.
					 */
					err = BLK_STS_IOERR;
					जाओ cleanup;
				पूर्ण
				/*
				 * a single failure in raid6 is rebuilt
				 * in the pstripe code below
				 */
				जाओ pstripe;
			पूर्ण

			/* make sure our ps and qs are in order */
			अगर (faila > failb)
				swap(faila, failb);

			/* अगर the q stripe is failed, करो a pstripe reस्थिरruction
			 * from the xors.
			 * If both the q stripe and the P stripe are failed, we're
			 * here due to a crc mismatch and we can't give them the
			 * data they want
			 */
			अगर (rbio->bbio->raid_map[failb] == RAID6_Q_STRIPE) अणु
				अगर (rbio->bbio->raid_map[faila] ==
				    RAID5_P_STRIPE) अणु
					err = BLK_STS_IOERR;
					जाओ cleanup;
				पूर्ण
				/*
				 * otherwise we have one bad data stripe and
				 * a good P stripe.  raid5!
				 */
				जाओ pstripe;
			पूर्ण

			अगर (rbio->bbio->raid_map[failb] == RAID5_P_STRIPE) अणु
				raid6_datap_recov(rbio->real_stripes,
						  PAGE_SIZE, faila, poपूर्णांकers);
			पूर्ण अन्यथा अणु
				raid6_2data_recov(rbio->real_stripes,
						  PAGE_SIZE, faila, failb,
						  poपूर्णांकers);
			पूर्ण
		पूर्ण अन्यथा अणु
			व्योम *p;

			/* rebuild from P stripe here (raid5 or raid6) */
			BUG_ON(failb != -1);
pstripe:
			/* Copy parity block पूर्णांकo failed block to start with */
			copy_page(poपूर्णांकers[faila], poपूर्णांकers[rbio->nr_data]);

			/* rearrange the poपूर्णांकer array */
			p = poपूर्णांकers[faila];
			क्रम (stripe = faila; stripe < rbio->nr_data - 1; stripe++)
				poपूर्णांकers[stripe] = poपूर्णांकers[stripe + 1];
			poपूर्णांकers[rbio->nr_data - 1] = p;

			/* xor in the rest */
			run_xor(poपूर्णांकers, rbio->nr_data - 1, PAGE_SIZE);
		पूर्ण
		/* अगर we're करोing this rebuild as part of an rmw, go through
		 * and set all of our निजी rbio pages in the
		 * failed stripes as uptodate.  This way finish_rmw will
		 * know they can be trusted.  If this was a पढ़ो reस्थिरruction,
		 * other endio functions will fiddle the uptodate bits
		 */
		अगर (rbio->operation == BTRFS_RBIO_WRITE) अणु
			क्रम (i = 0;  i < rbio->stripe_npages; i++) अणु
				अगर (faila != -1) अणु
					page = rbio_stripe_page(rbio, faila, i);
					SetPageUptodate(page);
				पूर्ण
				अगर (failb != -1) अणु
					page = rbio_stripe_page(rbio, failb, i);
					SetPageUptodate(page);
				पूर्ण
			पूर्ण
		पूर्ण
		क्रम (stripe = rbio->real_stripes - 1; stripe >= 0; stripe--)
			kunmap_local(unmap_array[stripe]);
	पूर्ण

	err = BLK_STS_OK;
cleanup:
	kमुक्त(unmap_array);
cleanup_poपूर्णांकers:
	kमुक्त(poपूर्णांकers);

cleanup_io:
	/*
	 * Similar to READ_REBUILD, REBUILD_MISSING at this poपूर्णांक also has a
	 * valid rbio which is consistent with ondisk content, thus such a
	 * valid rbio can be cached to aव्योम further disk पढ़ोs.
	 */
	अगर (rbio->operation == BTRFS_RBIO_READ_REBUILD ||
	    rbio->operation == BTRFS_RBIO_REBUILD_MISSING) अणु
		/*
		 * - In हाल of two failures, where rbio->failb != -1:
		 *
		 *   Do not cache this rbio since the above पढ़ो reस्थिरruction
		 *   (raid6_datap_recov() or raid6_2data_recov()) may have
		 *   changed some content of stripes which are not identical to
		 *   on-disk content any more, otherwise, a later ग_लिखो/recover
		 *   may steal stripe_pages from this rbio and end up with
		 *   corruptions or rebuild failures.
		 *
		 * - In हाल of single failure, where rbio->failb == -1:
		 *
		 *   Cache this rbio अगरf the above पढ़ो reस्थिरruction is
		 *   executed without problems.
		 */
		अगर (err == BLK_STS_OK && rbio->failb < 0)
			cache_rbio_pages(rbio);
		अन्यथा
			clear_bit(RBIO_CACHE_READY_BIT, &rbio->flags);

		rbio_orig_end_io(rbio, err);
	पूर्ण अन्यथा अगर (err == BLK_STS_OK) अणु
		rbio->faila = -1;
		rbio->failb = -1;

		अगर (rbio->operation == BTRFS_RBIO_WRITE)
			finish_rmw(rbio);
		अन्यथा अगर (rbio->operation == BTRFS_RBIO_PARITY_SCRUB)
			finish_parity_scrub(rbio, 0);
		अन्यथा
			BUG();
	पूर्ण अन्यथा अणु
		rbio_orig_end_io(rbio, err);
	पूर्ण
पूर्ण

/*
 * This is called only क्रम stripes we've पढ़ो from disk to
 * reस्थिरruct the parity.
 */
अटल व्योम raid_recover_end_io(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_raid_bio *rbio = bio->bi_निजी;

	/*
	 * we only पढ़ो stripe pages off the disk, set them
	 * up to date अगर there were no errors
	 */
	अगर (bio->bi_status)
		fail_bio_stripe(rbio, bio);
	अन्यथा
		set_bio_pages_uptodate(bio);
	bio_put(bio);

	अगर (!atomic_dec_and_test(&rbio->stripes_pending))
		वापस;

	अगर (atomic_पढ़ो(&rbio->error) > rbio->bbio->max_errors)
		rbio_orig_end_io(rbio, BLK_STS_IOERR);
	अन्यथा
		__raid_recover_end_io(rbio);
पूर्ण

/*
 * पढ़ोs everything we need off the disk to reस्थिरruct
 * the parity. endio handlers trigger final reस्थिरruction
 * when the IO is करोne.
 *
 * This is used both क्रम पढ़ोs from the higher layers and क्रम
 * parity स्थिरruction required to finish a rmw cycle.
 */
अटल पूर्णांक __raid56_parity_recover(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक bios_to_पढ़ो = 0;
	काष्ठा bio_list bio_list;
	पूर्णांक ret;
	पूर्णांक pagenr;
	पूर्णांक stripe;
	काष्ठा bio *bio;

	bio_list_init(&bio_list);

	ret = alloc_rbio_pages(rbio);
	अगर (ret)
		जाओ cleanup;

	atomic_set(&rbio->error, 0);

	/*
	 * पढ़ो everything that hasn't failed.  Thanks to the
	 * stripe cache, it is possible that some or all of these
	 * pages are going to be uptodate.
	 */
	क्रम (stripe = 0; stripe < rbio->real_stripes; stripe++) अणु
		अगर (rbio->faila == stripe || rbio->failb == stripe) अणु
			atomic_inc(&rbio->error);
			जारी;
		पूर्ण

		क्रम (pagenr = 0; pagenr < rbio->stripe_npages; pagenr++) अणु
			काष्ठा page *p;

			/*
			 * the rmw code may have alपढ़ोy पढ़ो this
			 * page in
			 */
			p = rbio_stripe_page(rbio, stripe, pagenr);
			अगर (PageUptodate(p))
				जारी;

			ret = rbio_add_io_page(rbio, &bio_list,
				       rbio_stripe_page(rbio, stripe, pagenr),
				       stripe, pagenr, rbio->stripe_len);
			अगर (ret < 0)
				जाओ cleanup;
		पूर्ण
	पूर्ण

	bios_to_पढ़ो = bio_list_size(&bio_list);
	अगर (!bios_to_पढ़ो) अणु
		/*
		 * we might have no bios to पढ़ो just because the pages
		 * were up to date, or we might have no bios to पढ़ो because
		 * the devices were gone.
		 */
		अगर (atomic_पढ़ो(&rbio->error) <= rbio->bbio->max_errors) अणु
			__raid_recover_end_io(rbio);
			वापस 0;
		पूर्ण अन्यथा अणु
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/*
	 * the bbio may be मुक्तd once we submit the last bio.  Make sure
	 * not to touch it after that
	 */
	atomic_set(&rbio->stripes_pending, bios_to_पढ़ो);
	जबतक ((bio = bio_list_pop(&bio_list))) अणु
		bio->bi_निजी = rbio;
		bio->bi_end_io = raid_recover_end_io;
		bio->bi_opf = REQ_OP_READ;

		btrfs_bio_wq_end_io(rbio->fs_info, bio, BTRFS_WQ_ENDIO_RAID56);

		submit_bio(bio);
	पूर्ण

	वापस 0;

cleanup:
	अगर (rbio->operation == BTRFS_RBIO_READ_REBUILD ||
	    rbio->operation == BTRFS_RBIO_REBUILD_MISSING)
		rbio_orig_end_io(rbio, BLK_STS_IOERR);

	जबतक ((bio = bio_list_pop(&bio_list)))
		bio_put(bio);

	वापस -EIO;
पूर्ण

/*
 * the मुख्य entry poपूर्णांक क्रम पढ़ोs from the higher layers.  This
 * is really only called when the normal पढ़ो path had a failure,
 * so we assume the bio they send करोwn corresponds to a failed part
 * of the drive.
 */
पूर्णांक raid56_parity_recover(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			  काष्ठा btrfs_bio *bbio, u64 stripe_len,
			  पूर्णांक mirror_num, पूर्णांक generic_io)
अणु
	काष्ठा btrfs_raid_bio *rbio;
	पूर्णांक ret;

	अगर (generic_io) अणु
		ASSERT(bbio->mirror_num == mirror_num);
		btrfs_io_bio(bio)->mirror_num = mirror_num;
	पूर्ण

	rbio = alloc_rbio(fs_info, bbio, stripe_len);
	अगर (IS_ERR(rbio)) अणु
		अगर (generic_io)
			btrfs_put_bbio(bbio);
		वापस PTR_ERR(rbio);
	पूर्ण

	rbio->operation = BTRFS_RBIO_READ_REBUILD;
	bio_list_add(&rbio->bio_list, bio);
	rbio->bio_list_bytes = bio->bi_iter.bi_size;

	rbio->faila = find_logical_bio_stripe(rbio, bio);
	अगर (rbio->faila == -1) अणु
		btrfs_warn(fs_info,
	"%s could not find the bad stripe in raid56 so that we cannot recover any more (bio has logical %llu len %llu, bbio has map_type %llu)",
			   __func__, bio->bi_iter.bi_sector << 9,
			   (u64)bio->bi_iter.bi_size, bbio->map_type);
		अगर (generic_io)
			btrfs_put_bbio(bbio);
		kमुक्त(rbio);
		वापस -EIO;
	पूर्ण

	अगर (generic_io) अणु
		btrfs_bio_counter_inc_noblocked(fs_info);
		rbio->generic_bio_cnt = 1;
	पूर्ण अन्यथा अणु
		btrfs_get_bbio(bbio);
	पूर्ण

	/*
	 * Loop retry:
	 * क्रम 'mirror == 2', reस्थिरruct from all other stripes.
	 * क्रम 'mirror_num > 2', select a stripe to fail on every retry.
	 */
	अगर (mirror_num > 2) अणु
		/*
		 * 'mirror == 3' is to fail the p stripe and
		 * reस्थिरruct from the q stripe.  'mirror > 3' is to
		 * fail a data stripe and reस्थिरruct from p+q stripe.
		 */
		rbio->failb = rbio->real_stripes - (mirror_num - 1);
		ASSERT(rbio->failb > 0);
		अगर (rbio->failb <= rbio->faila)
			rbio->failb--;
	पूर्ण

	ret = lock_stripe_add(rbio);

	/*
	 * __raid56_parity_recover will end the bio with
	 * any errors it hits.  We करोn't want to वापस
	 * its error value up the stack because our caller
	 * will end up calling bio_endio with any nonzero
	 * वापस
	 */
	अगर (ret == 0)
		__raid56_parity_recover(rbio);
	/*
	 * our rbio has been added to the list of
	 * rbios that will be handled after the
	 * currently lock owner is करोne
	 */
	वापस 0;

पूर्ण

अटल व्योम rmw_work(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_raid_bio *rbio;

	rbio = container_of(work, काष्ठा btrfs_raid_bio, work);
	raid56_rmw_stripe(rbio);
पूर्ण

अटल व्योम पढ़ो_rebuild_work(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_raid_bio *rbio;

	rbio = container_of(work, काष्ठा btrfs_raid_bio, work);
	__raid56_parity_recover(rbio);
पूर्ण

/*
 * The following code is used to scrub/replace the parity stripe
 *
 * Caller must have alपढ़ोy increased bio_counter क्रम getting @bbio.
 *
 * Note: We need make sure all the pages that add पूर्णांकo the scrub/replace
 * raid bio are correct and not be changed during the scrub/replace. That
 * is those pages just hold metadata or file data with checksum.
 */

काष्ठा btrfs_raid_bio *
raid56_parity_alloc_scrub_rbio(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			       काष्ठा btrfs_bio *bbio, u64 stripe_len,
			       काष्ठा btrfs_device *scrub_dev,
			       अचिन्हित दीर्घ *dbiपंचांगap, पूर्णांक stripe_nsectors)
अणु
	काष्ठा btrfs_raid_bio *rbio;
	पूर्णांक i;

	rbio = alloc_rbio(fs_info, bbio, stripe_len);
	अगर (IS_ERR(rbio))
		वापस शून्य;
	bio_list_add(&rbio->bio_list, bio);
	/*
	 * This is a special bio which is used to hold the completion handler
	 * and make the scrub rbio is similar to the other types
	 */
	ASSERT(!bio->bi_iter.bi_size);
	rbio->operation = BTRFS_RBIO_PARITY_SCRUB;

	/*
	 * After mapping bbio with BTRFS_MAP_WRITE, parities have been sorted
	 * to the end position, so this search can start from the first parity
	 * stripe.
	 */
	क्रम (i = rbio->nr_data; i < rbio->real_stripes; i++) अणु
		अगर (bbio->stripes[i].dev == scrub_dev) अणु
			rbio->scrubp = i;
			अवरोध;
		पूर्ण
	पूर्ण
	ASSERT(i < rbio->real_stripes);

	/* Now we just support the sectorsize equals to page size */
	ASSERT(fs_info->sectorsize == PAGE_SIZE);
	ASSERT(rbio->stripe_npages == stripe_nsectors);
	biपंचांगap_copy(rbio->dbiपंचांगap, dbiपंचांगap, stripe_nsectors);

	/*
	 * We have alपढ़ोy increased bio_counter when getting bbio, record it
	 * so we can मुक्त it at rbio_orig_end_io().
	 */
	rbio->generic_bio_cnt = 1;

	वापस rbio;
पूर्ण

/* Used क्रम both parity scrub and missing. */
व्योम raid56_add_scrub_pages(काष्ठा btrfs_raid_bio *rbio, काष्ठा page *page,
			    u64 logical)
अणु
	पूर्णांक stripe_offset;
	पूर्णांक index;

	ASSERT(logical >= rbio->bbio->raid_map[0]);
	ASSERT(logical + PAGE_SIZE <= rbio->bbio->raid_map[0] +
				rbio->stripe_len * rbio->nr_data);
	stripe_offset = (पूर्णांक)(logical - rbio->bbio->raid_map[0]);
	index = stripe_offset >> PAGE_SHIFT;
	rbio->bio_pages[index] = page;
पूर्ण

/*
 * We just scrub the parity that we have correct data on the same horizontal,
 * so we needn't allocate all pages क्रम all the stripes.
 */
अटल पूर्णांक alloc_rbio_essential_pages(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक i;
	पूर्णांक bit;
	पूर्णांक index;
	काष्ठा page *page;

	क्रम_each_set_bit(bit, rbio->dbiपंचांगap, rbio->stripe_npages) अणु
		क्रम (i = 0; i < rbio->real_stripes; i++) अणु
			index = i * rbio->stripe_npages + bit;
			अगर (rbio->stripe_pages[index])
				जारी;

			page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
			अगर (!page)
				वापस -ENOMEM;
			rbio->stripe_pages[index] = page;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल noअंतरभूत व्योम finish_parity_scrub(काष्ठा btrfs_raid_bio *rbio,
					 पूर्णांक need_check)
अणु
	काष्ठा btrfs_bio *bbio = rbio->bbio;
	व्योम **poपूर्णांकers = rbio->finish_poपूर्णांकers;
	अचिन्हित दीर्घ *pbiपंचांगap = rbio->finish_pbiपंचांगap;
	पूर्णांक nr_data = rbio->nr_data;
	पूर्णांक stripe;
	पूर्णांक pagenr;
	bool has_qstripe;
	काष्ठा page *p_page = शून्य;
	काष्ठा page *q_page = शून्य;
	काष्ठा bio_list bio_list;
	काष्ठा bio *bio;
	पूर्णांक is_replace = 0;
	पूर्णांक ret;

	bio_list_init(&bio_list);

	अगर (rbio->real_stripes - rbio->nr_data == 1)
		has_qstripe = false;
	अन्यथा अगर (rbio->real_stripes - rbio->nr_data == 2)
		has_qstripe = true;
	अन्यथा
		BUG();

	अगर (bbio->num_tgtdevs && bbio->tgtdev_map[rbio->scrubp]) अणु
		is_replace = 1;
		biपंचांगap_copy(pbiपंचांगap, rbio->dbiपंचांगap, rbio->stripe_npages);
	पूर्ण

	/*
	 * Because the higher layers(scrubber) are unlikely to
	 * use this area of the disk again soon, so करोn't cache
	 * it.
	 */
	clear_bit(RBIO_CACHE_READY_BIT, &rbio->flags);

	अगर (!need_check)
		जाओ ग_लिखोback;

	p_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
	अगर (!p_page)
		जाओ cleanup;
	SetPageUptodate(p_page);

	अगर (has_qstripe) अणु
		/* RAID6, allocate and map temp space क्रम the Q stripe */
		q_page = alloc_page(GFP_NOFS | __GFP_HIGHMEM);
		अगर (!q_page) अणु
			__मुक्त_page(p_page);
			जाओ cleanup;
		पूर्ण
		SetPageUptodate(q_page);
		poपूर्णांकers[rbio->real_stripes - 1] = kmap_local_page(q_page);
	पूर्ण

	atomic_set(&rbio->error, 0);

	/* Map the parity stripe just once */
	poपूर्णांकers[nr_data] = kmap_local_page(p_page);

	क्रम_each_set_bit(pagenr, rbio->dbiपंचांगap, rbio->stripe_npages) अणु
		काष्ठा page *p;
		व्योम *parity;
		/* first collect one page from each data stripe */
		क्रम (stripe = 0; stripe < nr_data; stripe++) अणु
			p = page_in_rbio(rbio, stripe, pagenr, 0);
			poपूर्णांकers[stripe] = kmap_local_page(p);
		पूर्ण

		अगर (has_qstripe) अणु
			/* RAID6, call the library function to fill in our P/Q */
			raid6_call.gen_syndrome(rbio->real_stripes, PAGE_SIZE,
						poपूर्णांकers);
		पूर्ण अन्यथा अणु
			/* raid5 */
			copy_page(poपूर्णांकers[nr_data], poपूर्णांकers[0]);
			run_xor(poपूर्णांकers + 1, nr_data - 1, PAGE_SIZE);
		पूर्ण

		/* Check scrubbing parity and repair it */
		p = rbio_stripe_page(rbio, rbio->scrubp, pagenr);
		parity = kmap_local_page(p);
		अगर (स_भेद(parity, poपूर्णांकers[rbio->scrubp], PAGE_SIZE))
			copy_page(parity, poपूर्णांकers[rbio->scrubp]);
		अन्यथा
			/* Parity is right, needn't ग_लिखोback */
			biपंचांगap_clear(rbio->dbiपंचांगap, pagenr, 1);
		kunmap_local(parity);

		क्रम (stripe = nr_data - 1; stripe >= 0; stripe--)
			kunmap_local(poपूर्णांकers[stripe]);
	पूर्ण

	kunmap_local(poपूर्णांकers[nr_data]);
	__मुक्त_page(p_page);
	अगर (q_page) अणु
		kunmap_local(poपूर्णांकers[rbio->real_stripes - 1]);
		__मुक्त_page(q_page);
	पूर्ण

ग_लिखोback:
	/*
	 * समय to start writing.  Make bios क्रम everything from the
	 * higher layers (the bio_list in our rbio) and our p/q.  Ignore
	 * everything अन्यथा.
	 */
	क्रम_each_set_bit(pagenr, rbio->dbiपंचांगap, rbio->stripe_npages) अणु
		काष्ठा page *page;

		page = rbio_stripe_page(rbio, rbio->scrubp, pagenr);
		ret = rbio_add_io_page(rbio, &bio_list,
			       page, rbio->scrubp, pagenr, rbio->stripe_len);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	अगर (!is_replace)
		जाओ submit_ग_लिखो;

	क्रम_each_set_bit(pagenr, pbiपंचांगap, rbio->stripe_npages) अणु
		काष्ठा page *page;

		page = rbio_stripe_page(rbio, rbio->scrubp, pagenr);
		ret = rbio_add_io_page(rbio, &bio_list, page,
				       bbio->tgtdev_map[rbio->scrubp],
				       pagenr, rbio->stripe_len);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

submit_ग_लिखो:
	nr_data = bio_list_size(&bio_list);
	अगर (!nr_data) अणु
		/* Every parity is right */
		rbio_orig_end_io(rbio, BLK_STS_OK);
		वापस;
	पूर्ण

	atomic_set(&rbio->stripes_pending, nr_data);

	जबतक ((bio = bio_list_pop(&bio_list))) अणु
		bio->bi_निजी = rbio;
		bio->bi_end_io = raid_ग_लिखो_end_io;
		bio->bi_opf = REQ_OP_WRITE;

		submit_bio(bio);
	पूर्ण
	वापस;

cleanup:
	rbio_orig_end_io(rbio, BLK_STS_IOERR);

	जबतक ((bio = bio_list_pop(&bio_list)))
		bio_put(bio);
पूर्ण

अटल अंतरभूत पूर्णांक is_data_stripe(काष्ठा btrfs_raid_bio *rbio, पूर्णांक stripe)
अणु
	अगर (stripe >= 0 && stripe < rbio->nr_data)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * While we're करोing the parity check and repair, we could have errors
 * in पढ़ोing pages off the disk.  This checks क्रम errors and अगर we're
 * not able to पढ़ो the page it'll trigger parity reस्थिरruction.  The
 * parity scrub will be finished after we've reस्थिरructed the failed
 * stripes
 */
अटल व्योम validate_rbio_क्रम_parity_scrub(काष्ठा btrfs_raid_bio *rbio)
अणु
	अगर (atomic_पढ़ो(&rbio->error) > rbio->bbio->max_errors)
		जाओ cleanup;

	अगर (rbio->faila >= 0 || rbio->failb >= 0) अणु
		पूर्णांक dfail = 0, failp = -1;

		अगर (is_data_stripe(rbio, rbio->faila))
			dfail++;
		अन्यथा अगर (is_parity_stripe(rbio->faila))
			failp = rbio->faila;

		अगर (is_data_stripe(rbio, rbio->failb))
			dfail++;
		अन्यथा अगर (is_parity_stripe(rbio->failb))
			failp = rbio->failb;

		/*
		 * Because we can not use a scrubbing parity to repair
		 * the data, so the capability of the repair is declined.
		 * (In the हाल of RAID5, we can not repair anything)
		 */
		अगर (dfail > rbio->bbio->max_errors - 1)
			जाओ cleanup;

		/*
		 * If all data is good, only parity is correctly, just
		 * repair the parity.
		 */
		अगर (dfail == 0) अणु
			finish_parity_scrub(rbio, 0);
			वापस;
		पूर्ण

		/*
		 * Here means we got one corrupted data stripe and one
		 * corrupted parity on RAID6, अगर the corrupted parity
		 * is scrubbing parity, luckily, use the other one to repair
		 * the data, or we can not repair the data stripe.
		 */
		अगर (failp != rbio->scrubp)
			जाओ cleanup;

		__raid_recover_end_io(rbio);
	पूर्ण अन्यथा अणु
		finish_parity_scrub(rbio, 1);
	पूर्ण
	वापस;

cleanup:
	rbio_orig_end_io(rbio, BLK_STS_IOERR);
पूर्ण

/*
 * end io क्रम the पढ़ो phase of the rmw cycle.  All the bios here are physical
 * stripe bios we've पढ़ो from the disk so we can recalculate the parity of the
 * stripe.
 *
 * This will usually kick off finish_rmw once all the bios are पढ़ो in, but it
 * may trigger parity reस्थिरruction अगर we had any errors aदीर्घ the way
 */
अटल व्योम raid56_parity_scrub_end_io(काष्ठा bio *bio)
अणु
	काष्ठा btrfs_raid_bio *rbio = bio->bi_निजी;

	अगर (bio->bi_status)
		fail_bio_stripe(rbio, bio);
	अन्यथा
		set_bio_pages_uptodate(bio);

	bio_put(bio);

	अगर (!atomic_dec_and_test(&rbio->stripes_pending))
		वापस;

	/*
	 * this will normally call finish_rmw to start our ग_लिखो
	 * but अगर there are any failed stripes we'll reस्थिरruct
	 * from parity first
	 */
	validate_rbio_क्रम_parity_scrub(rbio);
पूर्ण

अटल व्योम raid56_parity_scrub_stripe(काष्ठा btrfs_raid_bio *rbio)
अणु
	पूर्णांक bios_to_पढ़ो = 0;
	काष्ठा bio_list bio_list;
	पूर्णांक ret;
	पूर्णांक pagenr;
	पूर्णांक stripe;
	काष्ठा bio *bio;

	bio_list_init(&bio_list);

	ret = alloc_rbio_essential_pages(rbio);
	अगर (ret)
		जाओ cleanup;

	atomic_set(&rbio->error, 0);
	/*
	 * build a list of bios to पढ़ो all the missing parts of this
	 * stripe
	 */
	क्रम (stripe = 0; stripe < rbio->real_stripes; stripe++) अणु
		क्रम_each_set_bit(pagenr, rbio->dbiपंचांगap, rbio->stripe_npages) अणु
			काष्ठा page *page;
			/*
			 * we want to find all the pages missing from
			 * the rbio and पढ़ो them from the disk.  If
			 * page_in_rbio finds a page in the bio list
			 * we करोn't need to पढ़ो it off the stripe.
			 */
			page = page_in_rbio(rbio, stripe, pagenr, 1);
			अगर (page)
				जारी;

			page = rbio_stripe_page(rbio, stripe, pagenr);
			/*
			 * the bio cache may have handed us an uptodate
			 * page.  If so, be happy and use it
			 */
			अगर (PageUptodate(page))
				जारी;

			ret = rbio_add_io_page(rbio, &bio_list, page,
				       stripe, pagenr, rbio->stripe_len);
			अगर (ret)
				जाओ cleanup;
		पूर्ण
	पूर्ण

	bios_to_पढ़ो = bio_list_size(&bio_list);
	अगर (!bios_to_पढ़ो) अणु
		/*
		 * this can happen अगर others have merged with
		 * us, it means there is nothing left to पढ़ो.
		 * But अगर there are missing devices it may not be
		 * safe to करो the full stripe ग_लिखो yet.
		 */
		जाओ finish;
	पूर्ण

	/*
	 * the bbio may be मुक्तd once we submit the last bio.  Make sure
	 * not to touch it after that
	 */
	atomic_set(&rbio->stripes_pending, bios_to_पढ़ो);
	जबतक ((bio = bio_list_pop(&bio_list))) अणु
		bio->bi_निजी = rbio;
		bio->bi_end_io = raid56_parity_scrub_end_io;
		bio->bi_opf = REQ_OP_READ;

		btrfs_bio_wq_end_io(rbio->fs_info, bio, BTRFS_WQ_ENDIO_RAID56);

		submit_bio(bio);
	पूर्ण
	/* the actual ग_लिखो will happen once the पढ़ोs are करोne */
	वापस;

cleanup:
	rbio_orig_end_io(rbio, BLK_STS_IOERR);

	जबतक ((bio = bio_list_pop(&bio_list)))
		bio_put(bio);

	वापस;

finish:
	validate_rbio_क्रम_parity_scrub(rbio);
पूर्ण

अटल व्योम scrub_parity_work(काष्ठा btrfs_work *work)
अणु
	काष्ठा btrfs_raid_bio *rbio;

	rbio = container_of(work, काष्ठा btrfs_raid_bio, work);
	raid56_parity_scrub_stripe(rbio);
पूर्ण

व्योम raid56_parity_submit_scrub_rbio(काष्ठा btrfs_raid_bio *rbio)
अणु
	अगर (!lock_stripe_add(rbio))
		start_async_work(rbio, scrub_parity_work);
पूर्ण

/* The following code is used क्रम dev replace of a missing RAID 5/6 device. */

काष्ठा btrfs_raid_bio *
raid56_alloc_missing_rbio(काष्ठा btrfs_fs_info *fs_info, काष्ठा bio *bio,
			  काष्ठा btrfs_bio *bbio, u64 length)
अणु
	काष्ठा btrfs_raid_bio *rbio;

	rbio = alloc_rbio(fs_info, bbio, length);
	अगर (IS_ERR(rbio))
		वापस शून्य;

	rbio->operation = BTRFS_RBIO_REBUILD_MISSING;
	bio_list_add(&rbio->bio_list, bio);
	/*
	 * This is a special bio which is used to hold the completion handler
	 * and make the scrub rbio is similar to the other types
	 */
	ASSERT(!bio->bi_iter.bi_size);

	rbio->faila = find_logical_bio_stripe(rbio, bio);
	अगर (rbio->faila == -1) अणु
		BUG();
		kमुक्त(rbio);
		वापस शून्य;
	पूर्ण

	/*
	 * When we get bbio, we have alपढ़ोy increased bio_counter, record it
	 * so we can मुक्त it at rbio_orig_end_io()
	 */
	rbio->generic_bio_cnt = 1;

	वापस rbio;
पूर्ण

व्योम raid56_submit_missing_rbio(काष्ठा btrfs_raid_bio *rbio)
अणु
	अगर (!lock_stripe_add(rbio))
		start_async_work(rbio, पढ़ो_rebuild_work);
पूर्ण
