<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011, 2012 STRATO.  All rights reserved.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/sched/mm.h>
#समावेश <crypto/hash.h>
#समावेश "ctree.h"
#समावेश "discard.h"
#समावेश "volumes.h"
#समावेश "disk-io.h"
#समावेश "ordered-data.h"
#समावेश "transaction.h"
#समावेश "backref.h"
#समावेश "extent_io.h"
#समावेश "dev-replace.h"
#समावेश "check-integrity.h"
#समावेश "rcu-string.h"
#समावेश "raid56.h"
#समावेश "block-group.h"
#समावेश "zoned.h"

/*
 * This is only the first step towards a full-features scrub. It पढ़ोs all
 * extent and super block and verअगरies the checksums. In हाल a bad checksum
 * is found or the extent cannot be पढ़ो, good data will be written back अगर
 * any can be found.
 *
 * Future enhancements:
 *  - In हाल an unrepairable extent is encountered, track which files are
 *    affected and report them
 *  - track and record media errors, throw out bad devices
 *  - add a mode to also पढ़ो unallocated space
 */

काष्ठा scrub_block;
काष्ठा scrub_ctx;

/*
 * the following three values only influence the perक्रमmance.
 * The last one configures the number of parallel and outstanding I/O
 * operations. The first two values configure an upper limit क्रम the number
 * of (dynamically allocated) pages that are added to a bio.
 */
#घोषणा SCRUB_PAGES_PER_RD_BIO	32	/* 128k per bio */
#घोषणा SCRUB_PAGES_PER_WR_BIO	32	/* 128k per bio */
#घोषणा SCRUB_BIOS_PER_SCTX	64	/* 8MB per device in flight */

/*
 * the following value बार PAGE_SIZE needs to be large enough to match the
 * largest node/leaf/sector size that shall be supported.
 * Values larger than BTRFS_STRIPE_LEN are not supported.
 */
#घोषणा SCRUB_MAX_PAGES_PER_BLOCK	16	/* 64k per node/leaf/sector */

काष्ठा scrub_recover अणु
	refcount_t		refs;
	काष्ठा btrfs_bio	*bbio;
	u64			map_length;
पूर्ण;

काष्ठा scrub_page अणु
	काष्ठा scrub_block	*sblock;
	काष्ठा page		*page;
	काष्ठा btrfs_device	*dev;
	काष्ठा list_head	list;
	u64			flags;  /* extent flags */
	u64			generation;
	u64			logical;
	u64			physical;
	u64			physical_क्रम_dev_replace;
	atomic_t		refs;
	u8			mirror_num;
	पूर्णांक			have_csum:1;
	पूर्णांक			io_error:1;
	u8			csum[BTRFS_CSUM_SIZE];

	काष्ठा scrub_recover	*recover;
पूर्ण;

काष्ठा scrub_bio अणु
	पूर्णांक			index;
	काष्ठा scrub_ctx	*sctx;
	काष्ठा btrfs_device	*dev;
	काष्ठा bio		*bio;
	blk_status_t		status;
	u64			logical;
	u64			physical;
#अगर SCRUB_PAGES_PER_WR_BIO >= SCRUB_PAGES_PER_RD_BIO
	काष्ठा scrub_page	*pagev[SCRUB_PAGES_PER_WR_BIO];
#अन्यथा
	काष्ठा scrub_page	*pagev[SCRUB_PAGES_PER_RD_BIO];
#पूर्ण_अगर
	पूर्णांक			page_count;
	पूर्णांक			next_मुक्त;
	काष्ठा btrfs_work	work;
पूर्ण;

काष्ठा scrub_block अणु
	काष्ठा scrub_page	*pagev[SCRUB_MAX_PAGES_PER_BLOCK];
	पूर्णांक			page_count;
	atomic_t		outstanding_pages;
	refcount_t		refs; /* मुक्त mem on transition to zero */
	काष्ठा scrub_ctx	*sctx;
	काष्ठा scrub_parity	*sparity;
	काष्ठा अणु
		अचिन्हित पूर्णांक	header_error:1;
		अचिन्हित पूर्णांक	checksum_error:1;
		अचिन्हित पूर्णांक	no_io_error_seen:1;
		अचिन्हित पूर्णांक	generation_error:1; /* also sets header_error */

		/* The following is क्रम the data used to check parity */
		/* It is क्रम the data with checksum */
		अचिन्हित पूर्णांक	data_corrected:1;
	पूर्ण;
	काष्ठा btrfs_work	work;
पूर्ण;

/* Used क्रम the chunks with parity stripe such RAID5/6 */
काष्ठा scrub_parity अणु
	काष्ठा scrub_ctx	*sctx;

	काष्ठा btrfs_device	*scrub_dev;

	u64			logic_start;

	u64			logic_end;

	पूर्णांक			nsectors;

	u32			stripe_len;

	refcount_t		refs;

	काष्ठा list_head	spages;

	/* Work of parity check and repair */
	काष्ठा btrfs_work	work;

	/* Mark the parity blocks which have data */
	अचिन्हित दीर्घ		*dbiपंचांगap;

	/*
	 * Mark the parity blocks which have data, but errors happen when
	 * पढ़ो data or check data
	 */
	अचिन्हित दीर्घ		*ebiपंचांगap;

	अचिन्हित दीर्घ		biपंचांगap[];
पूर्ण;

काष्ठा scrub_ctx अणु
	काष्ठा scrub_bio	*bios[SCRUB_BIOS_PER_SCTX];
	काष्ठा btrfs_fs_info	*fs_info;
	पूर्णांक			first_मुक्त;
	पूर्णांक			curr;
	atomic_t		bios_in_flight;
	atomic_t		workers_pending;
	spinlock_t		list_lock;
	रुको_queue_head_t	list_रुको;
	काष्ठा list_head	csum_list;
	atomic_t		cancel_req;
	पूर्णांक			पढ़ोonly;
	पूर्णांक			pages_per_rd_bio;

	पूर्णांक			is_dev_replace;
	u64			ग_लिखो_poपूर्णांकer;

	काष्ठा scrub_bio        *wr_curr_bio;
	काष्ठा mutex            wr_lock;
	पूर्णांक                     pages_per_wr_bio; /* <= SCRUB_PAGES_PER_WR_BIO */
	काष्ठा btrfs_device     *wr_tgtdev;
	bool                    flush_all_ग_लिखोs;

	/*
	 * statistics
	 */
	काष्ठा btrfs_scrub_progress stat;
	spinlock_t		stat_lock;

	/*
	 * Use a ref counter to aव्योम use-after-मुक्त issues. Scrub workers
	 * decrement bios_in_flight and workers_pending and then करो a wakeup
	 * on the list_रुको रुको queue. We must ensure the मुख्य scrub task
	 * करोesn't मुक्त the scrub context beक्रमe or जबतक the workers are
	 * करोing the wakeup() call.
	 */
	refcount_t              refs;
पूर्ण;

काष्ठा scrub_warning अणु
	काष्ठा btrfs_path	*path;
	u64			extent_item_size;
	स्थिर अक्षर		*errstr;
	u64			physical;
	u64			logical;
	काष्ठा btrfs_device	*dev;
पूर्ण;

काष्ठा full_stripe_lock अणु
	काष्ठा rb_node node;
	u64 logical;
	u64 refs;
	काष्ठा mutex mutex;
पूर्ण;

अटल पूर्णांक scrub_setup_recheck_block(काष्ठा scrub_block *original_sblock,
				     काष्ठा scrub_block *sblocks_क्रम_recheck);
अटल व्योम scrub_recheck_block(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा scrub_block *sblock,
				पूर्णांक retry_failed_mirror);
अटल व्योम scrub_recheck_block_checksum(काष्ठा scrub_block *sblock);
अटल पूर्णांक scrub_repair_block_from_good_copy(काष्ठा scrub_block *sblock_bad,
					     काष्ठा scrub_block *sblock_good);
अटल पूर्णांक scrub_repair_page_from_good_copy(काष्ठा scrub_block *sblock_bad,
					    काष्ठा scrub_block *sblock_good,
					    पूर्णांक page_num, पूर्णांक क्रमce_ग_लिखो);
अटल व्योम scrub_ग_लिखो_block_to_dev_replace(काष्ठा scrub_block *sblock);
अटल पूर्णांक scrub_ग_लिखो_page_to_dev_replace(काष्ठा scrub_block *sblock,
					   पूर्णांक page_num);
अटल पूर्णांक scrub_checksum_data(काष्ठा scrub_block *sblock);
अटल पूर्णांक scrub_checksum_tree_block(काष्ठा scrub_block *sblock);
अटल पूर्णांक scrub_checksum_super(काष्ठा scrub_block *sblock);
अटल व्योम scrub_block_put(काष्ठा scrub_block *sblock);
अटल व्योम scrub_page_get(काष्ठा scrub_page *spage);
अटल व्योम scrub_page_put(काष्ठा scrub_page *spage);
अटल व्योम scrub_parity_get(काष्ठा scrub_parity *sparity);
अटल व्योम scrub_parity_put(काष्ठा scrub_parity *sparity);
अटल पूर्णांक scrub_pages(काष्ठा scrub_ctx *sctx, u64 logical, u32 len,
		       u64 physical, काष्ठा btrfs_device *dev, u64 flags,
		       u64 gen, पूर्णांक mirror_num, u8 *csum,
		       u64 physical_क्रम_dev_replace);
अटल व्योम scrub_bio_end_io(काष्ठा bio *bio);
अटल व्योम scrub_bio_end_io_worker(काष्ठा btrfs_work *work);
अटल व्योम scrub_block_complete(काष्ठा scrub_block *sblock);
अटल व्योम scrub_remap_extent(काष्ठा btrfs_fs_info *fs_info,
			       u64 extent_logical, u32 extent_len,
			       u64 *extent_physical,
			       काष्ठा btrfs_device **extent_dev,
			       पूर्णांक *extent_mirror_num);
अटल पूर्णांक scrub_add_page_to_wr_bio(काष्ठा scrub_ctx *sctx,
				    काष्ठा scrub_page *spage);
अटल व्योम scrub_wr_submit(काष्ठा scrub_ctx *sctx);
अटल व्योम scrub_wr_bio_end_io(काष्ठा bio *bio);
अटल व्योम scrub_wr_bio_end_io_worker(काष्ठा btrfs_work *work);
अटल व्योम scrub_put_ctx(काष्ठा scrub_ctx *sctx);

अटल अंतरभूत पूर्णांक scrub_is_page_on_raid56(काष्ठा scrub_page *spage)
अणु
	वापस spage->recover &&
	       (spage->recover->bbio->map_type & BTRFS_BLOCK_GROUP_RAID56_MASK);
पूर्ण

अटल व्योम scrub_pending_bio_inc(काष्ठा scrub_ctx *sctx)
अणु
	refcount_inc(&sctx->refs);
	atomic_inc(&sctx->bios_in_flight);
पूर्ण

अटल व्योम scrub_pending_bio_dec(काष्ठा scrub_ctx *sctx)
अणु
	atomic_dec(&sctx->bios_in_flight);
	wake_up(&sctx->list_रुको);
	scrub_put_ctx(sctx);
पूर्ण

अटल व्योम __scrub_blocked_अगर_needed(काष्ठा btrfs_fs_info *fs_info)
अणु
	जबतक (atomic_पढ़ो(&fs_info->scrub_छोड़ो_req)) अणु
		mutex_unlock(&fs_info->scrub_lock);
		रुको_event(fs_info->scrub_छोड़ो_रुको,
		   atomic_पढ़ो(&fs_info->scrub_छोड़ो_req) == 0);
		mutex_lock(&fs_info->scrub_lock);
	पूर्ण
पूर्ण

अटल व्योम scrub_छोड़ो_on(काष्ठा btrfs_fs_info *fs_info)
अणु
	atomic_inc(&fs_info->scrubs_छोड़ोd);
	wake_up(&fs_info->scrub_छोड़ो_रुको);
पूर्ण

अटल व्योम scrub_छोड़ो_off(काष्ठा btrfs_fs_info *fs_info)
अणु
	mutex_lock(&fs_info->scrub_lock);
	__scrub_blocked_अगर_needed(fs_info);
	atomic_dec(&fs_info->scrubs_छोड़ोd);
	mutex_unlock(&fs_info->scrub_lock);

	wake_up(&fs_info->scrub_छोड़ो_रुको);
पूर्ण

अटल व्योम scrub_blocked_अगर_needed(काष्ठा btrfs_fs_info *fs_info)
अणु
	scrub_छोड़ो_on(fs_info);
	scrub_छोड़ो_off(fs_info);
पूर्ण

/*
 * Insert new full stripe lock पूर्णांकo full stripe locks tree
 *
 * Return poपूर्णांकer to existing or newly inserted full_stripe_lock काष्ठाure अगर
 * everything works well.
 * Return ERR_PTR(-ENOMEM) अगर we failed to allocate memory
 *
 * NOTE: caller must hold full_stripe_locks_root->lock beक्रमe calling this
 * function
 */
अटल काष्ठा full_stripe_lock *insert_full_stripe_lock(
		काष्ठा btrfs_full_stripe_locks_tree *locks_root,
		u64 fstripe_logical)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा full_stripe_lock *entry;
	काष्ठा full_stripe_lock *ret;

	lockdep_निश्चित_held(&locks_root->lock);

	p = &locks_root->root.rb_node;
	जबतक (*p) अणु
		parent = *p;
		entry = rb_entry(parent, काष्ठा full_stripe_lock, node);
		अगर (fstripe_logical < entry->logical) अणु
			p = &(*p)->rb_left;
		पूर्ण अन्यथा अगर (fstripe_logical > entry->logical) अणु
			p = &(*p)->rb_right;
		पूर्ण अन्यथा अणु
			entry->refs++;
			वापस entry;
		पूर्ण
	पूर्ण

	/*
	 * Insert new lock.
	 */
	ret = kदो_स्मृति(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस ERR_PTR(-ENOMEM);
	ret->logical = fstripe_logical;
	ret->refs = 1;
	mutex_init(&ret->mutex);

	rb_link_node(&ret->node, parent, p);
	rb_insert_color(&ret->node, &locks_root->root);
	वापस ret;
पूर्ण

/*
 * Search क्रम a full stripe lock of a block group
 *
 * Return poपूर्णांकer to existing full stripe lock अगर found
 * Return शून्य अगर not found
 */
अटल काष्ठा full_stripe_lock *search_full_stripe_lock(
		काष्ठा btrfs_full_stripe_locks_tree *locks_root,
		u64 fstripe_logical)
अणु
	काष्ठा rb_node *node;
	काष्ठा full_stripe_lock *entry;

	lockdep_निश्चित_held(&locks_root->lock);

	node = locks_root->root.rb_node;
	जबतक (node) अणु
		entry = rb_entry(node, काष्ठा full_stripe_lock, node);
		अगर (fstripe_logical < entry->logical)
			node = node->rb_left;
		अन्यथा अगर (fstripe_logical > entry->logical)
			node = node->rb_right;
		अन्यथा
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Helper to get full stripe logical from a normal bytenr.
 *
 * Caller must ensure @cache is a RAID56 block group.
 */
अटल u64 get_full_stripe_logical(काष्ठा btrfs_block_group *cache, u64 bytenr)
अणु
	u64 ret;

	/*
	 * Due to chunk item size limit, full stripe length should not be
	 * larger than U32_MAX. Just a sanity check here.
	 */
	WARN_ON_ONCE(cache->full_stripe_len >= U32_MAX);

	/*
	 * round_करोwn() can only handle घातer of 2, जबतक RAID56 full
	 * stripe length can be 64KiB * n, so we need to manually round करोwn.
	 */
	ret = भाग64_u64(bytenr - cache->start, cache->full_stripe_len) *
			cache->full_stripe_len + cache->start;
	वापस ret;
पूर्ण

/*
 * Lock a full stripe to aव्योम concurrency of recovery and पढ़ो
 *
 * It's only used क्रम profiles with parities (RAID5/6), क्रम other profiles it
 * करोes nothing.
 *
 * Return 0 अगर we locked full stripe covering @bytenr, with a mutex held.
 * So caller must call unlock_full_stripe() at the same context.
 *
 * Return <0 अगर encounters error.
 */
अटल पूर्णांक lock_full_stripe(काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			    bool *locked_ret)
अणु
	काष्ठा btrfs_block_group *bg_cache;
	काष्ठा btrfs_full_stripe_locks_tree *locks_root;
	काष्ठा full_stripe_lock *existing;
	u64 fstripe_start;
	पूर्णांक ret = 0;

	*locked_ret = false;
	bg_cache = btrfs_lookup_block_group(fs_info, bytenr);
	अगर (!bg_cache) अणु
		ASSERT(0);
		वापस -ENOENT;
	पूर्ण

	/* Profiles not based on parity करोn't need full stripe lock */
	अगर (!(bg_cache->flags & BTRFS_BLOCK_GROUP_RAID56_MASK))
		जाओ out;
	locks_root = &bg_cache->full_stripe_locks_root;

	fstripe_start = get_full_stripe_logical(bg_cache, bytenr);

	/* Now insert the full stripe lock */
	mutex_lock(&locks_root->lock);
	existing = insert_full_stripe_lock(locks_root, fstripe_start);
	mutex_unlock(&locks_root->lock);
	अगर (IS_ERR(existing)) अणु
		ret = PTR_ERR(existing);
		जाओ out;
	पूर्ण
	mutex_lock(&existing->mutex);
	*locked_ret = true;
out:
	btrfs_put_block_group(bg_cache);
	वापस ret;
पूर्ण

/*
 * Unlock a full stripe.
 *
 * NOTE: Caller must ensure it's the same context calling corresponding
 * lock_full_stripe().
 *
 * Return 0 अगर we unlock full stripe without problem.
 * Return <0 क्रम error
 */
अटल पूर्णांक unlock_full_stripe(काष्ठा btrfs_fs_info *fs_info, u64 bytenr,
			      bool locked)
अणु
	काष्ठा btrfs_block_group *bg_cache;
	काष्ठा btrfs_full_stripe_locks_tree *locks_root;
	काष्ठा full_stripe_lock *fstripe_lock;
	u64 fstripe_start;
	bool मुक्तit = false;
	पूर्णांक ret = 0;

	/* If we didn't acquire full stripe lock, no need to जारी */
	अगर (!locked)
		वापस 0;

	bg_cache = btrfs_lookup_block_group(fs_info, bytenr);
	अगर (!bg_cache) अणु
		ASSERT(0);
		वापस -ENOENT;
	पूर्ण
	अगर (!(bg_cache->flags & BTRFS_BLOCK_GROUP_RAID56_MASK))
		जाओ out;

	locks_root = &bg_cache->full_stripe_locks_root;
	fstripe_start = get_full_stripe_logical(bg_cache, bytenr);

	mutex_lock(&locks_root->lock);
	fstripe_lock = search_full_stripe_lock(locks_root, fstripe_start);
	/* Unpaired unlock_full_stripe() detected */
	अगर (!fstripe_lock) अणु
		WARN_ON(1);
		ret = -ENOENT;
		mutex_unlock(&locks_root->lock);
		जाओ out;
	पूर्ण

	अगर (fstripe_lock->refs == 0) अणु
		WARN_ON(1);
		btrfs_warn(fs_info, "full stripe lock at %llu refcount underflow",
			fstripe_lock->logical);
	पूर्ण अन्यथा अणु
		fstripe_lock->refs--;
	पूर्ण

	अगर (fstripe_lock->refs == 0) अणु
		rb_erase(&fstripe_lock->node, &locks_root->root);
		मुक्तit = true;
	पूर्ण
	mutex_unlock(&locks_root->lock);

	mutex_unlock(&fstripe_lock->mutex);
	अगर (मुक्तit)
		kमुक्त(fstripe_lock);
out:
	btrfs_put_block_group(bg_cache);
	वापस ret;
पूर्ण

अटल व्योम scrub_मुक्त_csums(काष्ठा scrub_ctx *sctx)
अणु
	जबतक (!list_empty(&sctx->csum_list)) अणु
		काष्ठा btrfs_ordered_sum *sum;
		sum = list_first_entry(&sctx->csum_list,
				       काष्ठा btrfs_ordered_sum, list);
		list_del(&sum->list);
		kमुक्त(sum);
	पूर्ण
पूर्ण

अटल noअंतरभूत_क्रम_stack व्योम scrub_मुक्त_ctx(काष्ठा scrub_ctx *sctx)
अणु
	पूर्णांक i;

	अगर (!sctx)
		वापस;

	/* this can happen when scrub is cancelled */
	अगर (sctx->curr != -1) अणु
		काष्ठा scrub_bio *sbio = sctx->bios[sctx->curr];

		क्रम (i = 0; i < sbio->page_count; i++) अणु
			WARN_ON(!sbio->pagev[i]->page);
			scrub_block_put(sbio->pagev[i]->sblock);
		पूर्ण
		bio_put(sbio->bio);
	पूर्ण

	क्रम (i = 0; i < SCRUB_BIOS_PER_SCTX; ++i) अणु
		काष्ठा scrub_bio *sbio = sctx->bios[i];

		अगर (!sbio)
			अवरोध;
		kमुक्त(sbio);
	पूर्ण

	kमुक्त(sctx->wr_curr_bio);
	scrub_मुक्त_csums(sctx);
	kमुक्त(sctx);
पूर्ण

अटल व्योम scrub_put_ctx(काष्ठा scrub_ctx *sctx)
अणु
	अगर (refcount_dec_and_test(&sctx->refs))
		scrub_मुक्त_ctx(sctx);
पूर्ण

अटल noअंतरभूत_क्रम_stack काष्ठा scrub_ctx *scrub_setup_ctx(
		काष्ठा btrfs_fs_info *fs_info, पूर्णांक is_dev_replace)
अणु
	काष्ठा scrub_ctx *sctx;
	पूर्णांक		i;

	sctx = kzalloc(माप(*sctx), GFP_KERNEL);
	अगर (!sctx)
		जाओ nomem;
	refcount_set(&sctx->refs, 1);
	sctx->is_dev_replace = is_dev_replace;
	sctx->pages_per_rd_bio = SCRUB_PAGES_PER_RD_BIO;
	sctx->curr = -1;
	sctx->fs_info = fs_info;
	INIT_LIST_HEAD(&sctx->csum_list);
	क्रम (i = 0; i < SCRUB_BIOS_PER_SCTX; ++i) अणु
		काष्ठा scrub_bio *sbio;

		sbio = kzalloc(माप(*sbio), GFP_KERNEL);
		अगर (!sbio)
			जाओ nomem;
		sctx->bios[i] = sbio;

		sbio->index = i;
		sbio->sctx = sctx;
		sbio->page_count = 0;
		btrfs_init_work(&sbio->work, scrub_bio_end_io_worker, शून्य,
				शून्य);

		अगर (i != SCRUB_BIOS_PER_SCTX - 1)
			sctx->bios[i]->next_मुक्त = i + 1;
		अन्यथा
			sctx->bios[i]->next_मुक्त = -1;
	पूर्ण
	sctx->first_मुक्त = 0;
	atomic_set(&sctx->bios_in_flight, 0);
	atomic_set(&sctx->workers_pending, 0);
	atomic_set(&sctx->cancel_req, 0);

	spin_lock_init(&sctx->list_lock);
	spin_lock_init(&sctx->stat_lock);
	init_रुकोqueue_head(&sctx->list_रुको);

	WARN_ON(sctx->wr_curr_bio != शून्य);
	mutex_init(&sctx->wr_lock);
	sctx->wr_curr_bio = शून्य;
	अगर (is_dev_replace) अणु
		WARN_ON(!fs_info->dev_replace.tgtdev);
		sctx->pages_per_wr_bio = SCRUB_PAGES_PER_WR_BIO;
		sctx->wr_tgtdev = fs_info->dev_replace.tgtdev;
		sctx->flush_all_ग_लिखोs = false;
	पूर्ण

	वापस sctx;

nomem:
	scrub_मुक्त_ctx(sctx);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल पूर्णांक scrub_prपूर्णांक_warning_inode(u64 inum, u64 offset, u64 root,
				     व्योम *warn_ctx)
अणु
	u64 isize;
	u32 nlink;
	पूर्णांक ret;
	पूर्णांक i;
	अचिन्हित nofs_flag;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_inode_item *inode_item;
	काष्ठा scrub_warning *swarn = warn_ctx;
	काष्ठा btrfs_fs_info *fs_info = swarn->dev->fs_info;
	काष्ठा inode_fs_paths *ipath = शून्य;
	काष्ठा btrfs_root *local_root;
	काष्ठा btrfs_key key;

	local_root = btrfs_get_fs_root(fs_info, root, true);
	अगर (IS_ERR(local_root)) अणु
		ret = PTR_ERR(local_root);
		जाओ err;
	पूर्ण

	/*
	 * this makes the path poपूर्णांक to (inum INODE_ITEM ioff)
	 */
	key.objectid = inum;
	key.type = BTRFS_INODE_ITEM_KEY;
	key.offset = 0;

	ret = btrfs_search_slot(शून्य, local_root, &key, swarn->path, 0, 0);
	अगर (ret) अणु
		btrfs_put_root(local_root);
		btrfs_release_path(swarn->path);
		जाओ err;
	पूर्ण

	eb = swarn->path->nodes[0];
	inode_item = btrfs_item_ptr(eb, swarn->path->slots[0],
					काष्ठा btrfs_inode_item);
	isize = btrfs_inode_size(eb, inode_item);
	nlink = btrfs_inode_nlink(eb, inode_item);
	btrfs_release_path(swarn->path);

	/*
	 * init_path might indirectly call vदो_स्मृति, or use GFP_KERNEL. Scrub
	 * uses GFP_NOFS in this context, so we keep it consistent but it करोes
	 * not seem to be strictly necessary.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	ipath = init_ipath(4096, local_root, swarn->path);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (IS_ERR(ipath)) अणु
		btrfs_put_root(local_root);
		ret = PTR_ERR(ipath);
		ipath = शून्य;
		जाओ err;
	पूर्ण
	ret = paths_from_inode(inum, ipath);

	अगर (ret < 0)
		जाओ err;

	/*
	 * we deliberately ignore the bit ipath might have been too small to
	 * hold all of the paths here
	 */
	क्रम (i = 0; i < ipath->fspath->elem_cnt; ++i)
		btrfs_warn_in_rcu(fs_info,
"%s at logical %llu on dev %s, physical %llu, root %llu, inode %llu, offset %llu, length %llu, links %u (path: %s)",
				  swarn->errstr, swarn->logical,
				  rcu_str_deref(swarn->dev->name),
				  swarn->physical,
				  root, inum, offset,
				  min(isize - offset, (u64)PAGE_SIZE), nlink,
				  (अक्षर *)(अचिन्हित दीर्घ)ipath->fspath->val[i]);

	btrfs_put_root(local_root);
	मुक्त_ipath(ipath);
	वापस 0;

err:
	btrfs_warn_in_rcu(fs_info,
			  "%s at logical %llu on dev %s, physical %llu, root %llu, inode %llu, offset %llu: path resolving failed with ret=%d",
			  swarn->errstr, swarn->logical,
			  rcu_str_deref(swarn->dev->name),
			  swarn->physical,
			  root, inum, offset, ret);

	मुक्त_ipath(ipath);
	वापस 0;
पूर्ण

अटल व्योम scrub_prपूर्णांक_warning(स्थिर अक्षर *errstr, काष्ठा scrub_block *sblock)
अणु
	काष्ठा btrfs_device *dev;
	काष्ठा btrfs_fs_info *fs_info;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_key found_key;
	काष्ठा extent_buffer *eb;
	काष्ठा btrfs_extent_item *ei;
	काष्ठा scrub_warning swarn;
	अचिन्हित दीर्घ ptr = 0;
	u64 extent_item_pos;
	u64 flags = 0;
	u64 ref_root;
	u32 item_size;
	u8 ref_level = 0;
	पूर्णांक ret;

	WARN_ON(sblock->page_count < 1);
	dev = sblock->pagev[0]->dev;
	fs_info = sblock->sctx->fs_info;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस;

	swarn.physical = sblock->pagev[0]->physical;
	swarn.logical = sblock->pagev[0]->logical;
	swarn.errstr = errstr;
	swarn.dev = शून्य;

	ret = extent_from_logical(fs_info, swarn.logical, path, &found_key,
				  &flags);
	अगर (ret < 0)
		जाओ out;

	extent_item_pos = swarn.logical - found_key.objectid;
	swarn.extent_item_size = found_key.offset;

	eb = path->nodes[0];
	ei = btrfs_item_ptr(eb, path->slots[0], काष्ठा btrfs_extent_item);
	item_size = btrfs_item_size_nr(eb, path->slots[0]);

	अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) अणु
		करो अणु
			ret = tree_backref_क्रम_extent(&ptr, eb, &found_key, ei,
						      item_size, &ref_root,
						      &ref_level);
			btrfs_warn_in_rcu(fs_info,
"%s at logical %llu on dev %s, physical %llu: metadata %s (level %d) in tree %llu",
				errstr, swarn.logical,
				rcu_str_deref(dev->name),
				swarn.physical,
				ref_level ? "node" : "leaf",
				ret < 0 ? -1 : ref_level,
				ret < 0 ? -1 : ref_root);
		पूर्ण जबतक (ret != 1);
		btrfs_release_path(path);
	पूर्ण अन्यथा अणु
		btrfs_release_path(path);
		swarn.path = path;
		swarn.dev = dev;
		iterate_extent_inodes(fs_info, found_key.objectid,
					extent_item_pos, 1,
					scrub_prपूर्णांक_warning_inode, &swarn, false);
	पूर्ण

out:
	btrfs_मुक्त_path(path);
पूर्ण

अटल अंतरभूत व्योम scrub_get_recover(काष्ठा scrub_recover *recover)
अणु
	refcount_inc(&recover->refs);
पूर्ण

अटल अंतरभूत व्योम scrub_put_recover(काष्ठा btrfs_fs_info *fs_info,
				     काष्ठा scrub_recover *recover)
अणु
	अगर (refcount_dec_and_test(&recover->refs)) अणु
		btrfs_bio_counter_dec(fs_info);
		btrfs_put_bbio(recover->bbio);
		kमुक्त(recover);
	पूर्ण
पूर्ण

/*
 * scrub_handle_errored_block माला_लो called when either verअगरication of the
 * pages failed or the bio failed to पढ़ो, e.g. with EIO. In the latter
 * हाल, this function handles all pages in the bio, even though only one
 * may be bad.
 * The goal of this function is to repair the errored block by using the
 * contents of one of the mirrors.
 */
अटल पूर्णांक scrub_handle_errored_block(काष्ठा scrub_block *sblock_to_check)
अणु
	काष्ठा scrub_ctx *sctx = sblock_to_check->sctx;
	काष्ठा btrfs_device *dev;
	काष्ठा btrfs_fs_info *fs_info;
	u64 logical;
	अचिन्हित पूर्णांक failed_mirror_index;
	अचिन्हित पूर्णांक is_metadata;
	अचिन्हित पूर्णांक have_csum;
	काष्ठा scrub_block *sblocks_क्रम_recheck; /* holds one क्रम each mirror */
	काष्ठा scrub_block *sblock_bad;
	पूर्णांक ret;
	पूर्णांक mirror_index;
	पूर्णांक page_num;
	पूर्णांक success;
	bool full_stripe_locked;
	अचिन्हित पूर्णांक nofs_flag;
	अटल DEFINE_RATELIMIT_STATE(rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);

	BUG_ON(sblock_to_check->page_count < 1);
	fs_info = sctx->fs_info;
	अगर (sblock_to_check->pagev[0]->flags & BTRFS_EXTENT_FLAG_SUPER) अणु
		/*
		 * अगर we find an error in a super block, we just report it.
		 * They will get written with the next transaction commit
		 * anyway
		 */
		spin_lock(&sctx->stat_lock);
		++sctx->stat.super_errors;
		spin_unlock(&sctx->stat_lock);
		वापस 0;
	पूर्ण
	logical = sblock_to_check->pagev[0]->logical;
	BUG_ON(sblock_to_check->pagev[0]->mirror_num < 1);
	failed_mirror_index = sblock_to_check->pagev[0]->mirror_num - 1;
	is_metadata = !(sblock_to_check->pagev[0]->flags &
			BTRFS_EXTENT_FLAG_DATA);
	have_csum = sblock_to_check->pagev[0]->have_csum;
	dev = sblock_to_check->pagev[0]->dev;

	अगर (btrfs_is_zoned(fs_info) && !sctx->is_dev_replace)
		वापस btrfs_repair_one_zone(fs_info, logical);

	/*
	 * We must use GFP_NOFS because the scrub task might be रुकोing क्रम a
	 * worker task executing this function and in turn a transaction commit
	 * might be रुकोing the scrub task to छोड़ो (which needs to रुको क्रम all
	 * the worker tasks to complete beक्रमe pausing).
	 * We करो allocations in the workers through insert_full_stripe_lock()
	 * and scrub_add_page_to_wr_bio(), which happens करोwn the call chain of
	 * this function.
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	/*
	 * For RAID5/6, race can happen क्रम a dअगरferent device scrub thपढ़ो.
	 * For data corruption, Parity and Data thपढ़ोs will both try
	 * to recovery the data.
	 * Race can lead to करोubly added csum error, or even unrecoverable
	 * error.
	 */
	ret = lock_full_stripe(fs_info, logical, &full_stripe_locked);
	अगर (ret < 0) अणु
		meदो_स्मृति_nofs_restore(nofs_flag);
		spin_lock(&sctx->stat_lock);
		अगर (ret == -ENOMEM)
			sctx->stat.दो_स्मृति_errors++;
		sctx->stat.पढ़ो_errors++;
		sctx->stat.uncorrectable_errors++;
		spin_unlock(&sctx->stat_lock);
		वापस ret;
	पूर्ण

	/*
	 * पढ़ो all mirrors one after the other. This includes to
	 * re-पढ़ो the extent or metadata block that failed (that was
	 * the cause that this fixup code is called) another समय,
	 * page by page this समय in order to know which pages
	 * caused I/O errors and which ones are good (क्रम all mirrors).
	 * It is the goal to handle the situation when more than one
	 * mirror contains I/O errors, but the errors करो not
	 * overlap, i.e. the data can be repaired by selecting the
	 * pages from those mirrors without I/O error on the
	 * particular pages. One example (with blocks >= 2 * PAGE_SIZE)
	 * would be that mirror #1 has an I/O error on the first page,
	 * the second page is good, and mirror #2 has an I/O error on
	 * the second page, but the first page is good.
	 * Then the first page of the first mirror can be repaired by
	 * taking the first page of the second mirror, and the
	 * second page of the second mirror can be repaired by
	 * copying the contents of the 2nd page of the 1st mirror.
	 * One more note: अगर the pages of one mirror contain I/O
	 * errors, the checksum cannot be verअगरied. In order to get
	 * the best data क्रम repairing, the first attempt is to find
	 * a mirror without I/O errors and with a validated checksum.
	 * Only अगर this is not possible, the pages are picked from
	 * mirrors with I/O errors without considering the checksum.
	 * If the latter is the हाल, at the end, the checksum of the
	 * repaired area is verअगरied in order to correctly मुख्यtain
	 * the statistics.
	 */

	sblocks_क्रम_recheck = kसुस्मृति(BTRFS_MAX_MIRRORS,
				      माप(*sblocks_क्रम_recheck), GFP_KERNEL);
	अगर (!sblocks_क्रम_recheck) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.दो_स्मृति_errors++;
		sctx->stat.पढ़ो_errors++;
		sctx->stat.uncorrectable_errors++;
		spin_unlock(&sctx->stat_lock);
		btrfs_dev_stat_inc_and_prपूर्णांक(dev, BTRFS_DEV_STAT_READ_ERRS);
		जाओ out;
	पूर्ण

	/* setup the context, map the logical blocks and alloc the pages */
	ret = scrub_setup_recheck_block(sblock_to_check, sblocks_क्रम_recheck);
	अगर (ret) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.पढ़ो_errors++;
		sctx->stat.uncorrectable_errors++;
		spin_unlock(&sctx->stat_lock);
		btrfs_dev_stat_inc_and_prपूर्णांक(dev, BTRFS_DEV_STAT_READ_ERRS);
		जाओ out;
	पूर्ण
	BUG_ON(failed_mirror_index >= BTRFS_MAX_MIRRORS);
	sblock_bad = sblocks_क्रम_recheck + failed_mirror_index;

	/* build and submit the bios क्रम the failed mirror, check checksums */
	scrub_recheck_block(fs_info, sblock_bad, 1);

	अगर (!sblock_bad->header_error && !sblock_bad->checksum_error &&
	    sblock_bad->no_io_error_seen) अणु
		/*
		 * the error disappeared after पढ़ोing page by page, or
		 * the area was part of a huge bio and other parts of the
		 * bio caused I/O errors, or the block layer merged several
		 * पढ़ो requests पूर्णांकo one and the error is caused by a
		 * dअगरferent bio (usually one of the two latter हालs is
		 * the cause)
		 */
		spin_lock(&sctx->stat_lock);
		sctx->stat.unverअगरied_errors++;
		sblock_to_check->data_corrected = 1;
		spin_unlock(&sctx->stat_lock);

		अगर (sctx->is_dev_replace)
			scrub_ग_लिखो_block_to_dev_replace(sblock_bad);
		जाओ out;
	पूर्ण

	अगर (!sblock_bad->no_io_error_seen) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.पढ़ो_errors++;
		spin_unlock(&sctx->stat_lock);
		अगर (__ratelimit(&rs))
			scrub_prपूर्णांक_warning("i/o error", sblock_to_check);
		btrfs_dev_stat_inc_and_prपूर्णांक(dev, BTRFS_DEV_STAT_READ_ERRS);
	पूर्ण अन्यथा अगर (sblock_bad->checksum_error) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.csum_errors++;
		spin_unlock(&sctx->stat_lock);
		अगर (__ratelimit(&rs))
			scrub_prपूर्णांक_warning("checksum error", sblock_to_check);
		btrfs_dev_stat_inc_and_prपूर्णांक(dev,
					     BTRFS_DEV_STAT_CORRUPTION_ERRS);
	पूर्ण अन्यथा अगर (sblock_bad->header_error) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.verअगरy_errors++;
		spin_unlock(&sctx->stat_lock);
		अगर (__ratelimit(&rs))
			scrub_prपूर्णांक_warning("checksum/header error",
					    sblock_to_check);
		अगर (sblock_bad->generation_error)
			btrfs_dev_stat_inc_and_prपूर्णांक(dev,
				BTRFS_DEV_STAT_GENERATION_ERRS);
		अन्यथा
			btrfs_dev_stat_inc_and_prपूर्णांक(dev,
				BTRFS_DEV_STAT_CORRUPTION_ERRS);
	पूर्ण

	अगर (sctx->पढ़ोonly) अणु
		ASSERT(!sctx->is_dev_replace);
		जाओ out;
	पूर्ण

	/*
	 * now build and submit the bios क्रम the other mirrors, check
	 * checksums.
	 * First try to pick the mirror which is completely without I/O
	 * errors and also करोes not have a checksum error.
	 * If one is found, and अगर a checksum is present, the full block
	 * that is known to contain an error is rewritten. Afterwards
	 * the block is known to be corrected.
	 * If a mirror is found which is completely correct, and no
	 * checksum is present, only those pages are rewritten that had
	 * an I/O error in the block to be repaired, since it cannot be
	 * determined, which copy of the other pages is better (and it
	 * could happen otherwise that a correct page would be
	 * overwritten by a bad one).
	 */
	क्रम (mirror_index = 0; ;mirror_index++) अणु
		काष्ठा scrub_block *sblock_other;

		अगर (mirror_index == failed_mirror_index)
			जारी;

		/* raid56's mirror can be more than BTRFS_MAX_MIRRORS */
		अगर (!scrub_is_page_on_raid56(sblock_bad->pagev[0])) अणु
			अगर (mirror_index >= BTRFS_MAX_MIRRORS)
				अवरोध;
			अगर (!sblocks_क्रम_recheck[mirror_index].page_count)
				अवरोध;

			sblock_other = sblocks_क्रम_recheck + mirror_index;
		पूर्ण अन्यथा अणु
			काष्ठा scrub_recover *r = sblock_bad->pagev[0]->recover;
			पूर्णांक max_allowed = r->bbio->num_stripes -
						r->bbio->num_tgtdevs;

			अगर (mirror_index >= max_allowed)
				अवरोध;
			अगर (!sblocks_क्रम_recheck[1].page_count)
				अवरोध;

			ASSERT(failed_mirror_index == 0);
			sblock_other = sblocks_क्रम_recheck + 1;
			sblock_other->pagev[0]->mirror_num = 1 + mirror_index;
		पूर्ण

		/* build and submit the bios, check checksums */
		scrub_recheck_block(fs_info, sblock_other, 0);

		अगर (!sblock_other->header_error &&
		    !sblock_other->checksum_error &&
		    sblock_other->no_io_error_seen) अणु
			अगर (sctx->is_dev_replace) अणु
				scrub_ग_लिखो_block_to_dev_replace(sblock_other);
				जाओ corrected_error;
			पूर्ण अन्यथा अणु
				ret = scrub_repair_block_from_good_copy(
						sblock_bad, sblock_other);
				अगर (!ret)
					जाओ corrected_error;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (sblock_bad->no_io_error_seen && !sctx->is_dev_replace)
		जाओ did_not_correct_error;

	/*
	 * In हाल of I/O errors in the area that is supposed to be
	 * repaired, जारी by picking good copies of those pages.
	 * Select the good pages from mirrors to reग_लिखो bad pages from
	 * the area to fix. Afterwards verअगरy the checksum of the block
	 * that is supposed to be repaired. This verअगरication step is
	 * only करोne क्रम the purpose of statistic counting and क्रम the
	 * final scrub report, whether errors reमुख्य.
	 * A perfect algorithm could make use of the checksum and try
	 * all possible combinations of pages from the dअगरferent mirrors
	 * until the checksum verअगरication succeeds. For example, when
	 * the 2nd page of mirror #1 faces I/O errors, and the 2nd page
	 * of mirror #2 is पढ़ोable but the final checksum test fails,
	 * then the 2nd page of mirror #3 could be tried, whether now
	 * the final checksum succeeds. But this would be a rare
	 * exception and is thereक्रमe not implemented. At least it is
	 * aव्योमed that the good copy is overwritten.
	 * A more useful improvement would be to pick the sectors
	 * without I/O error based on sector sizes (512 bytes on legacy
	 * disks) instead of on PAGE_SIZE. Then maybe 512 byte of one
	 * mirror could be repaired by taking 512 byte of a dअगरferent
	 * mirror, even अगर other 512 byte sectors in the same PAGE_SIZE
	 * area are unपढ़ोable.
	 */
	success = 1;
	क्रम (page_num = 0; page_num < sblock_bad->page_count;
	     page_num++) अणु
		काष्ठा scrub_page *spage_bad = sblock_bad->pagev[page_num];
		काष्ठा scrub_block *sblock_other = शून्य;

		/* skip no-io-error page in scrub */
		अगर (!spage_bad->io_error && !sctx->is_dev_replace)
			जारी;

		अगर (scrub_is_page_on_raid56(sblock_bad->pagev[0])) अणु
			/*
			 * In हाल of dev replace, अगर raid56 rebuild process
			 * didn't work out correct data, then copy the content
			 * in sblock_bad to make sure target device is identical
			 * to source device, instead of writing garbage data in
			 * sblock_क्रम_recheck array to target device.
			 */
			sblock_other = शून्य;
		पूर्ण अन्यथा अगर (spage_bad->io_error) अणु
			/* try to find no-io-error page in mirrors */
			क्रम (mirror_index = 0;
			     mirror_index < BTRFS_MAX_MIRRORS &&
			     sblocks_क्रम_recheck[mirror_index].page_count > 0;
			     mirror_index++) अणु
				अगर (!sblocks_क्रम_recheck[mirror_index].
				    pagev[page_num]->io_error) अणु
					sblock_other = sblocks_क्रम_recheck +
						       mirror_index;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!sblock_other)
				success = 0;
		पूर्ण

		अगर (sctx->is_dev_replace) अणु
			/*
			 * did not find a mirror to fetch the page
			 * from. scrub_ग_लिखो_page_to_dev_replace()
			 * handles this हाल (page->io_error), by
			 * filling the block with zeros beक्रमe
			 * submitting the ग_लिखो request
			 */
			अगर (!sblock_other)
				sblock_other = sblock_bad;

			अगर (scrub_ग_लिखो_page_to_dev_replace(sblock_other,
							    page_num) != 0) अणु
				atomic64_inc(
					&fs_info->dev_replace.num_ग_लिखो_errors);
				success = 0;
			पूर्ण
		पूर्ण अन्यथा अगर (sblock_other) अणु
			ret = scrub_repair_page_from_good_copy(sblock_bad,
							       sblock_other,
							       page_num, 0);
			अगर (0 == ret)
				spage_bad->io_error = 0;
			अन्यथा
				success = 0;
		पूर्ण
	पूर्ण

	अगर (success && !sctx->is_dev_replace) अणु
		अगर (is_metadata || have_csum) अणु
			/*
			 * need to verअगरy the checksum now that all
			 * sectors on disk are repaired (the ग_लिखो
			 * request क्रम data to be repaired is on its way).
			 * Just be lazy and use scrub_recheck_block()
			 * which re-पढ़ोs the data beक्रमe the checksum
			 * is verअगरied, but most likely the data comes out
			 * of the page cache.
			 */
			scrub_recheck_block(fs_info, sblock_bad, 1);
			अगर (!sblock_bad->header_error &&
			    !sblock_bad->checksum_error &&
			    sblock_bad->no_io_error_seen)
				जाओ corrected_error;
			अन्यथा
				जाओ did_not_correct_error;
		पूर्ण अन्यथा अणु
corrected_error:
			spin_lock(&sctx->stat_lock);
			sctx->stat.corrected_errors++;
			sblock_to_check->data_corrected = 1;
			spin_unlock(&sctx->stat_lock);
			btrfs_err_rl_in_rcu(fs_info,
				"fixed up error at logical %llu on dev %s",
				logical, rcu_str_deref(dev->name));
		पूर्ण
	पूर्ण अन्यथा अणु
did_not_correct_error:
		spin_lock(&sctx->stat_lock);
		sctx->stat.uncorrectable_errors++;
		spin_unlock(&sctx->stat_lock);
		btrfs_err_rl_in_rcu(fs_info,
			"unable to fixup (regular) error at logical %llu on dev %s",
			logical, rcu_str_deref(dev->name));
	पूर्ण

out:
	अगर (sblocks_क्रम_recheck) अणु
		क्रम (mirror_index = 0; mirror_index < BTRFS_MAX_MIRRORS;
		     mirror_index++) अणु
			काष्ठा scrub_block *sblock = sblocks_क्रम_recheck +
						     mirror_index;
			काष्ठा scrub_recover *recover;
			पूर्णांक page_index;

			क्रम (page_index = 0; page_index < sblock->page_count;
			     page_index++) अणु
				sblock->pagev[page_index]->sblock = शून्य;
				recover = sblock->pagev[page_index]->recover;
				अगर (recover) अणु
					scrub_put_recover(fs_info, recover);
					sblock->pagev[page_index]->recover =
									शून्य;
				पूर्ण
				scrub_page_put(sblock->pagev[page_index]);
			पूर्ण
		पूर्ण
		kमुक्त(sblocks_क्रम_recheck);
	पूर्ण

	ret = unlock_full_stripe(fs_info, logical, full_stripe_locked);
	meदो_स्मृति_nofs_restore(nofs_flag);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक scrub_nr_raid_mirrors(काष्ठा btrfs_bio *bbio)
अणु
	अगर (bbio->map_type & BTRFS_BLOCK_GROUP_RAID5)
		वापस 2;
	अन्यथा अगर (bbio->map_type & BTRFS_BLOCK_GROUP_RAID6)
		वापस 3;
	अन्यथा
		वापस (पूर्णांक)bbio->num_stripes;
पूर्ण

अटल अंतरभूत व्योम scrub_stripe_index_and_offset(u64 logical, u64 map_type,
						 u64 *raid_map,
						 u64 mapped_length,
						 पूर्णांक nstripes, पूर्णांक mirror,
						 पूर्णांक *stripe_index,
						 u64 *stripe_offset)
अणु
	पूर्णांक i;

	अगर (map_type & BTRFS_BLOCK_GROUP_RAID56_MASK) अणु
		/* RAID5/6 */
		क्रम (i = 0; i < nstripes; i++) अणु
			अगर (raid_map[i] == RAID6_Q_STRIPE ||
			    raid_map[i] == RAID5_P_STRIPE)
				जारी;

			अगर (logical >= raid_map[i] &&
			    logical < raid_map[i] + mapped_length)
				अवरोध;
		पूर्ण

		*stripe_index = i;
		*stripe_offset = logical - raid_map[i];
	पूर्ण अन्यथा अणु
		/* The other RAID type */
		*stripe_index = mirror;
		*stripe_offset = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक scrub_setup_recheck_block(काष्ठा scrub_block *original_sblock,
				     काष्ठा scrub_block *sblocks_क्रम_recheck)
अणु
	काष्ठा scrub_ctx *sctx = original_sblock->sctx;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	u64 length = original_sblock->page_count * PAGE_SIZE;
	u64 logical = original_sblock->pagev[0]->logical;
	u64 generation = original_sblock->pagev[0]->generation;
	u64 flags = original_sblock->pagev[0]->flags;
	u64 have_csum = original_sblock->pagev[0]->have_csum;
	काष्ठा scrub_recover *recover;
	काष्ठा btrfs_bio *bbio;
	u64 sublen;
	u64 mapped_length;
	u64 stripe_offset;
	पूर्णांक stripe_index;
	पूर्णांक page_index = 0;
	पूर्णांक mirror_index;
	पूर्णांक nmirrors;
	पूर्णांक ret;

	/*
	 * note: the two members refs and outstanding_pages
	 * are not used (and not set) in the blocks that are used क्रम
	 * the recheck procedure
	 */

	जबतक (length > 0) अणु
		sublen = min_t(u64, length, PAGE_SIZE);
		mapped_length = sublen;
		bbio = शून्य;

		/*
		 * with a length of PAGE_SIZE, each वापसed stripe
		 * represents one mirror
		 */
		btrfs_bio_counter_inc_blocked(fs_info);
		ret = btrfs_map_sblock(fs_info, BTRFS_MAP_GET_READ_MIRRORS,
				logical, &mapped_length, &bbio);
		अगर (ret || !bbio || mapped_length < sublen) अणु
			btrfs_put_bbio(bbio);
			btrfs_bio_counter_dec(fs_info);
			वापस -EIO;
		पूर्ण

		recover = kzalloc(माप(काष्ठा scrub_recover), GFP_NOFS);
		अगर (!recover) अणु
			btrfs_put_bbio(bbio);
			btrfs_bio_counter_dec(fs_info);
			वापस -ENOMEM;
		पूर्ण

		refcount_set(&recover->refs, 1);
		recover->bbio = bbio;
		recover->map_length = mapped_length;

		BUG_ON(page_index >= SCRUB_MAX_PAGES_PER_BLOCK);

		nmirrors = min(scrub_nr_raid_mirrors(bbio), BTRFS_MAX_MIRRORS);

		क्रम (mirror_index = 0; mirror_index < nmirrors;
		     mirror_index++) अणु
			काष्ठा scrub_block *sblock;
			काष्ठा scrub_page *spage;

			sblock = sblocks_क्रम_recheck + mirror_index;
			sblock->sctx = sctx;

			spage = kzalloc(माप(*spage), GFP_NOFS);
			अगर (!spage) अणु
leave_nomem:
				spin_lock(&sctx->stat_lock);
				sctx->stat.दो_स्मृति_errors++;
				spin_unlock(&sctx->stat_lock);
				scrub_put_recover(fs_info, recover);
				वापस -ENOMEM;
			पूर्ण
			scrub_page_get(spage);
			sblock->pagev[page_index] = spage;
			spage->sblock = sblock;
			spage->flags = flags;
			spage->generation = generation;
			spage->logical = logical;
			spage->have_csum = have_csum;
			अगर (have_csum)
				स_नकल(spage->csum,
				       original_sblock->pagev[0]->csum,
				       sctx->fs_info->csum_size);

			scrub_stripe_index_and_offset(logical,
						      bbio->map_type,
						      bbio->raid_map,
						      mapped_length,
						      bbio->num_stripes -
						      bbio->num_tgtdevs,
						      mirror_index,
						      &stripe_index,
						      &stripe_offset);
			spage->physical = bbio->stripes[stripe_index].physical +
					 stripe_offset;
			spage->dev = bbio->stripes[stripe_index].dev;

			BUG_ON(page_index >= original_sblock->page_count);
			spage->physical_क्रम_dev_replace =
				original_sblock->pagev[page_index]->
				physical_क्रम_dev_replace;
			/* क्रम missing devices, dev->bdev is शून्य */
			spage->mirror_num = mirror_index + 1;
			sblock->page_count++;
			spage->page = alloc_page(GFP_NOFS);
			अगर (!spage->page)
				जाओ leave_nomem;

			scrub_get_recover(recover);
			spage->recover = recover;
		पूर्ण
		scrub_put_recover(fs_info, recover);
		length -= sublen;
		logical += sublen;
		page_index++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम scrub_bio_रुको_endio(काष्ठा bio *bio)
अणु
	complete(bio->bi_निजी);
पूर्ण

अटल पूर्णांक scrub_submit_raid56_bio_रुको(काष्ठा btrfs_fs_info *fs_info,
					काष्ठा bio *bio,
					काष्ठा scrub_page *spage)
अणु
	DECLARE_COMPLETION_ONSTACK(करोne);
	पूर्णांक ret;
	पूर्णांक mirror_num;

	bio->bi_iter.bi_sector = spage->logical >> 9;
	bio->bi_निजी = &करोne;
	bio->bi_end_io = scrub_bio_रुको_endio;

	mirror_num = spage->sblock->pagev[0]->mirror_num;
	ret = raid56_parity_recover(fs_info, bio, spage->recover->bbio,
				    spage->recover->map_length,
				    mirror_num, 0);
	अगर (ret)
		वापस ret;

	रुको_क्रम_completion_io(&करोne);
	वापस blk_status_to_त्रुटि_सं(bio->bi_status);
पूर्ण

अटल व्योम scrub_recheck_block_on_raid56(काष्ठा btrfs_fs_info *fs_info,
					  काष्ठा scrub_block *sblock)
अणु
	काष्ठा scrub_page *first_page = sblock->pagev[0];
	काष्ठा bio *bio;
	पूर्णांक page_num;

	/* All pages in sblock beदीर्घ to the same stripe on the same device. */
	ASSERT(first_page->dev);
	अगर (!first_page->dev->bdev)
		जाओ out;

	bio = btrfs_io_bio_alloc(BIO_MAX_VECS);
	bio_set_dev(bio, first_page->dev->bdev);

	क्रम (page_num = 0; page_num < sblock->page_count; page_num++) अणु
		काष्ठा scrub_page *spage = sblock->pagev[page_num];

		WARN_ON(!spage->page);
		bio_add_page(bio, spage->page, PAGE_SIZE, 0);
	पूर्ण

	अगर (scrub_submit_raid56_bio_रुको(fs_info, bio, first_page)) अणु
		bio_put(bio);
		जाओ out;
	पूर्ण

	bio_put(bio);

	scrub_recheck_block_checksum(sblock);

	वापस;
out:
	क्रम (page_num = 0; page_num < sblock->page_count; page_num++)
		sblock->pagev[page_num]->io_error = 1;

	sblock->no_io_error_seen = 0;
पूर्ण

/*
 * this function will check the on disk data क्रम checksum errors, header
 * errors and पढ़ो I/O errors. If any I/O errors happen, the exact pages
 * which are errored are marked as being bad. The goal is to enable scrub
 * to take those pages that are not errored from all the mirrors so that
 * the pages that are errored in the just handled mirror can be repaired.
 */
अटल व्योम scrub_recheck_block(काष्ठा btrfs_fs_info *fs_info,
				काष्ठा scrub_block *sblock,
				पूर्णांक retry_failed_mirror)
अणु
	पूर्णांक page_num;

	sblock->no_io_error_seen = 1;

	/* लघु cut क्रम raid56 */
	अगर (!retry_failed_mirror && scrub_is_page_on_raid56(sblock->pagev[0]))
		वापस scrub_recheck_block_on_raid56(fs_info, sblock);

	क्रम (page_num = 0; page_num < sblock->page_count; page_num++) अणु
		काष्ठा bio *bio;
		काष्ठा scrub_page *spage = sblock->pagev[page_num];

		अगर (spage->dev->bdev == शून्य) अणु
			spage->io_error = 1;
			sblock->no_io_error_seen = 0;
			जारी;
		पूर्ण

		WARN_ON(!spage->page);
		bio = btrfs_io_bio_alloc(1);
		bio_set_dev(bio, spage->dev->bdev);

		bio_add_page(bio, spage->page, PAGE_SIZE, 0);
		bio->bi_iter.bi_sector = spage->physical >> 9;
		bio->bi_opf = REQ_OP_READ;

		अगर (btrfsic_submit_bio_रुको(bio)) अणु
			spage->io_error = 1;
			sblock->no_io_error_seen = 0;
		पूर्ण

		bio_put(bio);
	पूर्ण

	अगर (sblock->no_io_error_seen)
		scrub_recheck_block_checksum(sblock);
पूर्ण

अटल अंतरभूत पूर्णांक scrub_check_fsid(u8 fsid[],
				   काष्ठा scrub_page *spage)
अणु
	काष्ठा btrfs_fs_devices *fs_devices = spage->dev->fs_devices;
	पूर्णांक ret;

	ret = स_भेद(fsid, fs_devices->fsid, BTRFS_FSID_SIZE);
	वापस !ret;
पूर्ण

अटल व्योम scrub_recheck_block_checksum(काष्ठा scrub_block *sblock)
अणु
	sblock->header_error = 0;
	sblock->checksum_error = 0;
	sblock->generation_error = 0;

	अगर (sblock->pagev[0]->flags & BTRFS_EXTENT_FLAG_DATA)
		scrub_checksum_data(sblock);
	अन्यथा
		scrub_checksum_tree_block(sblock);
पूर्ण

अटल पूर्णांक scrub_repair_block_from_good_copy(काष्ठा scrub_block *sblock_bad,
					     काष्ठा scrub_block *sblock_good)
अणु
	पूर्णांक page_num;
	पूर्णांक ret = 0;

	क्रम (page_num = 0; page_num < sblock_bad->page_count; page_num++) अणु
		पूर्णांक ret_sub;

		ret_sub = scrub_repair_page_from_good_copy(sblock_bad,
							   sblock_good,
							   page_num, 1);
		अगर (ret_sub)
			ret = ret_sub;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक scrub_repair_page_from_good_copy(काष्ठा scrub_block *sblock_bad,
					    काष्ठा scrub_block *sblock_good,
					    पूर्णांक page_num, पूर्णांक क्रमce_ग_लिखो)
अणु
	काष्ठा scrub_page *spage_bad = sblock_bad->pagev[page_num];
	काष्ठा scrub_page *spage_good = sblock_good->pagev[page_num];
	काष्ठा btrfs_fs_info *fs_info = sblock_bad->sctx->fs_info;

	BUG_ON(spage_bad->page == शून्य);
	BUG_ON(spage_good->page == शून्य);
	अगर (क्रमce_ग_लिखो || sblock_bad->header_error ||
	    sblock_bad->checksum_error || spage_bad->io_error) अणु
		काष्ठा bio *bio;
		पूर्णांक ret;

		अगर (!spage_bad->dev->bdev) अणु
			btrfs_warn_rl(fs_info,
				"scrub_repair_page_from_good_copy(bdev == NULL) is unexpected");
			वापस -EIO;
		पूर्ण

		bio = btrfs_io_bio_alloc(1);
		bio_set_dev(bio, spage_bad->dev->bdev);
		bio->bi_iter.bi_sector = spage_bad->physical >> 9;
		bio->bi_opf = REQ_OP_WRITE;

		ret = bio_add_page(bio, spage_good->page, PAGE_SIZE, 0);
		अगर (PAGE_SIZE != ret) अणु
			bio_put(bio);
			वापस -EIO;
		पूर्ण

		अगर (btrfsic_submit_bio_रुको(bio)) अणु
			btrfs_dev_stat_inc_and_prपूर्णांक(spage_bad->dev,
				BTRFS_DEV_STAT_WRITE_ERRS);
			atomic64_inc(&fs_info->dev_replace.num_ग_लिखो_errors);
			bio_put(bio);
			वापस -EIO;
		पूर्ण
		bio_put(bio);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम scrub_ग_लिखो_block_to_dev_replace(काष्ठा scrub_block *sblock)
अणु
	काष्ठा btrfs_fs_info *fs_info = sblock->sctx->fs_info;
	पूर्णांक page_num;

	/*
	 * This block is used क्रम the check of the parity on the source device,
	 * so the data needn't be written पूर्णांकo the destination device.
	 */
	अगर (sblock->sparity)
		वापस;

	क्रम (page_num = 0; page_num < sblock->page_count; page_num++) अणु
		पूर्णांक ret;

		ret = scrub_ग_लिखो_page_to_dev_replace(sblock, page_num);
		अगर (ret)
			atomic64_inc(&fs_info->dev_replace.num_ग_लिखो_errors);
	पूर्ण
पूर्ण

अटल पूर्णांक scrub_ग_लिखो_page_to_dev_replace(काष्ठा scrub_block *sblock,
					   पूर्णांक page_num)
अणु
	काष्ठा scrub_page *spage = sblock->pagev[page_num];

	BUG_ON(spage->page == शून्य);
	अगर (spage->io_error)
		clear_page(page_address(spage->page));

	वापस scrub_add_page_to_wr_bio(sblock->sctx, spage);
पूर्ण

अटल पूर्णांक fill_ग_लिखोr_poपूर्णांकer_gap(काष्ठा scrub_ctx *sctx, u64 physical)
अणु
	पूर्णांक ret = 0;
	u64 length;

	अगर (!btrfs_is_zoned(sctx->fs_info))
		वापस 0;

	अगर (!btrfs_dev_is_sequential(sctx->wr_tgtdev, physical))
		वापस 0;

	अगर (sctx->ग_लिखो_poपूर्णांकer < physical) अणु
		length = physical - sctx->ग_लिखो_poपूर्णांकer;

		ret = btrfs_zoned_issue_zeroout(sctx->wr_tgtdev,
						sctx->ग_लिखो_poपूर्णांकer, length);
		अगर (!ret)
			sctx->ग_लिखो_poपूर्णांकer = physical;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक scrub_add_page_to_wr_bio(काष्ठा scrub_ctx *sctx,
				    काष्ठा scrub_page *spage)
अणु
	काष्ठा scrub_bio *sbio;
	पूर्णांक ret;

	mutex_lock(&sctx->wr_lock);
again:
	अगर (!sctx->wr_curr_bio) अणु
		sctx->wr_curr_bio = kzalloc(माप(*sctx->wr_curr_bio),
					      GFP_KERNEL);
		अगर (!sctx->wr_curr_bio) अणु
			mutex_unlock(&sctx->wr_lock);
			वापस -ENOMEM;
		पूर्ण
		sctx->wr_curr_bio->sctx = sctx;
		sctx->wr_curr_bio->page_count = 0;
	पूर्ण
	sbio = sctx->wr_curr_bio;
	अगर (sbio->page_count == 0) अणु
		काष्ठा bio *bio;

		ret = fill_ग_लिखोr_poपूर्णांकer_gap(sctx,
					      spage->physical_क्रम_dev_replace);
		अगर (ret) अणु
			mutex_unlock(&sctx->wr_lock);
			वापस ret;
		पूर्ण

		sbio->physical = spage->physical_क्रम_dev_replace;
		sbio->logical = spage->logical;
		sbio->dev = sctx->wr_tgtdev;
		bio = sbio->bio;
		अगर (!bio) अणु
			bio = btrfs_io_bio_alloc(sctx->pages_per_wr_bio);
			sbio->bio = bio;
		पूर्ण

		bio->bi_निजी = sbio;
		bio->bi_end_io = scrub_wr_bio_end_io;
		bio_set_dev(bio, sbio->dev->bdev);
		bio->bi_iter.bi_sector = sbio->physical >> 9;
		bio->bi_opf = REQ_OP_WRITE;
		sbio->status = 0;
	पूर्ण अन्यथा अगर (sbio->physical + sbio->page_count * PAGE_SIZE !=
		   spage->physical_क्रम_dev_replace ||
		   sbio->logical + sbio->page_count * PAGE_SIZE !=
		   spage->logical) अणु
		scrub_wr_submit(sctx);
		जाओ again;
	पूर्ण

	ret = bio_add_page(sbio->bio, spage->page, PAGE_SIZE, 0);
	अगर (ret != PAGE_SIZE) अणु
		अगर (sbio->page_count < 1) अणु
			bio_put(sbio->bio);
			sbio->bio = शून्य;
			mutex_unlock(&sctx->wr_lock);
			वापस -EIO;
		पूर्ण
		scrub_wr_submit(sctx);
		जाओ again;
	पूर्ण

	sbio->pagev[sbio->page_count] = spage;
	scrub_page_get(spage);
	sbio->page_count++;
	अगर (sbio->page_count == sctx->pages_per_wr_bio)
		scrub_wr_submit(sctx);
	mutex_unlock(&sctx->wr_lock);

	वापस 0;
पूर्ण

अटल व्योम scrub_wr_submit(काष्ठा scrub_ctx *sctx)
अणु
	काष्ठा scrub_bio *sbio;

	अगर (!sctx->wr_curr_bio)
		वापस;

	sbio = sctx->wr_curr_bio;
	sctx->wr_curr_bio = शून्य;
	WARN_ON(!sbio->bio->bi_bdev);
	scrub_pending_bio_inc(sctx);
	/* process all ग_लिखोs in a single worker thपढ़ो. Then the block layer
	 * orders the requests beक्रमe sending them to the driver which
	 * द्विगुनd the ग_लिखो perक्रमmance on spinning disks when measured
	 * with Linux 3.5 */
	btrfsic_submit_bio(sbio->bio);

	अगर (btrfs_is_zoned(sctx->fs_info))
		sctx->ग_लिखो_poपूर्णांकer = sbio->physical + sbio->page_count * PAGE_SIZE;
पूर्ण

अटल व्योम scrub_wr_bio_end_io(काष्ठा bio *bio)
अणु
	काष्ठा scrub_bio *sbio = bio->bi_निजी;
	काष्ठा btrfs_fs_info *fs_info = sbio->dev->fs_info;

	sbio->status = bio->bi_status;
	sbio->bio = bio;

	btrfs_init_work(&sbio->work, scrub_wr_bio_end_io_worker, शून्य, शून्य);
	btrfs_queue_work(fs_info->scrub_wr_completion_workers, &sbio->work);
पूर्ण

अटल व्योम scrub_wr_bio_end_io_worker(काष्ठा btrfs_work *work)
अणु
	काष्ठा scrub_bio *sbio = container_of(work, काष्ठा scrub_bio, work);
	काष्ठा scrub_ctx *sctx = sbio->sctx;
	पूर्णांक i;

	WARN_ON(sbio->page_count > SCRUB_PAGES_PER_WR_BIO);
	अगर (sbio->status) अणु
		काष्ठा btrfs_dev_replace *dev_replace =
			&sbio->sctx->fs_info->dev_replace;

		क्रम (i = 0; i < sbio->page_count; i++) अणु
			काष्ठा scrub_page *spage = sbio->pagev[i];

			spage->io_error = 1;
			atomic64_inc(&dev_replace->num_ग_लिखो_errors);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < sbio->page_count; i++)
		scrub_page_put(sbio->pagev[i]);

	bio_put(sbio->bio);
	kमुक्त(sbio);
	scrub_pending_bio_dec(sctx);
पूर्ण

अटल पूर्णांक scrub_checksum(काष्ठा scrub_block *sblock)
अणु
	u64 flags;
	पूर्णांक ret;

	/*
	 * No need to initialize these stats currently,
	 * because this function only use वापस value
	 * instead of these stats value.
	 *
	 * Toकरो:
	 * always use stats
	 */
	sblock->header_error = 0;
	sblock->generation_error = 0;
	sblock->checksum_error = 0;

	WARN_ON(sblock->page_count < 1);
	flags = sblock->pagev[0]->flags;
	ret = 0;
	अगर (flags & BTRFS_EXTENT_FLAG_DATA)
		ret = scrub_checksum_data(sblock);
	अन्यथा अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK)
		ret = scrub_checksum_tree_block(sblock);
	अन्यथा अगर (flags & BTRFS_EXTENT_FLAG_SUPER)
		(व्योम)scrub_checksum_super(sblock);
	अन्यथा
		WARN_ON(1);
	अगर (ret)
		scrub_handle_errored_block(sblock);

	वापस ret;
पूर्ण

अटल पूर्णांक scrub_checksum_data(काष्ठा scrub_block *sblock)
अणु
	काष्ठा scrub_ctx *sctx = sblock->sctx;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	u8 csum[BTRFS_CSUM_SIZE];
	काष्ठा scrub_page *spage;
	अक्षर *kaddr;

	BUG_ON(sblock->page_count < 1);
	spage = sblock->pagev[0];
	अगर (!spage->have_csum)
		वापस 0;

	kaddr = page_address(spage->page);

	shash->tfm = fs_info->csum_shash;
	crypto_shash_init(shash);

	/*
	 * In scrub_pages() and scrub_pages_क्रम_parity() we ensure each spage
	 * only contains one sector of data.
	 */
	crypto_shash_digest(shash, kaddr, fs_info->sectorsize, csum);

	अगर (स_भेद(csum, spage->csum, fs_info->csum_size))
		sblock->checksum_error = 1;
	वापस sblock->checksum_error;
पूर्ण

अटल पूर्णांक scrub_checksum_tree_block(काष्ठा scrub_block *sblock)
अणु
	काष्ठा scrub_ctx *sctx = sblock->sctx;
	काष्ठा btrfs_header *h;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	u8 calculated_csum[BTRFS_CSUM_SIZE];
	u8 on_disk_csum[BTRFS_CSUM_SIZE];
	/*
	 * This is करोne in sectorsize steps even क्रम metadata as there's a
	 * स्थिरraपूर्णांक क्रम nodesize to be aligned to sectorsize. This will need
	 * to change so we करोn't misuse data and metadata units like that.
	 */
	स्थिर u32 sectorsize = sctx->fs_info->sectorsize;
	स्थिर पूर्णांक num_sectors = fs_info->nodesize >> fs_info->sectorsize_bits;
	पूर्णांक i;
	काष्ठा scrub_page *spage;
	अक्षर *kaddr;

	BUG_ON(sblock->page_count < 1);

	/* Each member in pagev is just one block, not a full page */
	ASSERT(sblock->page_count == num_sectors);

	spage = sblock->pagev[0];
	kaddr = page_address(spage->page);
	h = (काष्ठा btrfs_header *)kaddr;
	स_नकल(on_disk_csum, h->csum, sctx->fs_info->csum_size);

	/*
	 * we करोn't use the getter functions here, as we
	 * a) करोn't have an extent buffer and
	 * b) the page is alपढ़ोy kmapped
	 */
	अगर (spage->logical != btrfs_stack_header_bytenr(h))
		sblock->header_error = 1;

	अगर (spage->generation != btrfs_stack_header_generation(h)) अणु
		sblock->header_error = 1;
		sblock->generation_error = 1;
	पूर्ण

	अगर (!scrub_check_fsid(h->fsid, spage))
		sblock->header_error = 1;

	अगर (स_भेद(h->chunk_tree_uuid, fs_info->chunk_tree_uuid,
		   BTRFS_UUID_SIZE))
		sblock->header_error = 1;

	shash->tfm = fs_info->csum_shash;
	crypto_shash_init(shash);
	crypto_shash_update(shash, kaddr + BTRFS_CSUM_SIZE,
			    sectorsize - BTRFS_CSUM_SIZE);

	क्रम (i = 1; i < num_sectors; i++) अणु
		kaddr = page_address(sblock->pagev[i]->page);
		crypto_shash_update(shash, kaddr, sectorsize);
	पूर्ण

	crypto_shash_final(shash, calculated_csum);
	अगर (स_भेद(calculated_csum, on_disk_csum, sctx->fs_info->csum_size))
		sblock->checksum_error = 1;

	वापस sblock->header_error || sblock->checksum_error;
पूर्ण

अटल पूर्णांक scrub_checksum_super(काष्ठा scrub_block *sblock)
अणु
	काष्ठा btrfs_super_block *s;
	काष्ठा scrub_ctx *sctx = sblock->sctx;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	SHASH_DESC_ON_STACK(shash, fs_info->csum_shash);
	u8 calculated_csum[BTRFS_CSUM_SIZE];
	काष्ठा scrub_page *spage;
	अक्षर *kaddr;
	पूर्णांक fail_gen = 0;
	पूर्णांक fail_cor = 0;

	BUG_ON(sblock->page_count < 1);
	spage = sblock->pagev[0];
	kaddr = page_address(spage->page);
	s = (काष्ठा btrfs_super_block *)kaddr;

	अगर (spage->logical != btrfs_super_bytenr(s))
		++fail_cor;

	अगर (spage->generation != btrfs_super_generation(s))
		++fail_gen;

	अगर (!scrub_check_fsid(s->fsid, spage))
		++fail_cor;

	shash->tfm = fs_info->csum_shash;
	crypto_shash_init(shash);
	crypto_shash_digest(shash, kaddr + BTRFS_CSUM_SIZE,
			BTRFS_SUPER_INFO_SIZE - BTRFS_CSUM_SIZE, calculated_csum);

	अगर (स_भेद(calculated_csum, s->csum, sctx->fs_info->csum_size))
		++fail_cor;

	अगर (fail_cor + fail_gen) अणु
		/*
		 * अगर we find an error in a super block, we just report it.
		 * They will get written with the next transaction commit
		 * anyway
		 */
		spin_lock(&sctx->stat_lock);
		++sctx->stat.super_errors;
		spin_unlock(&sctx->stat_lock);
		अगर (fail_cor)
			btrfs_dev_stat_inc_and_prपूर्णांक(spage->dev,
				BTRFS_DEV_STAT_CORRUPTION_ERRS);
		अन्यथा
			btrfs_dev_stat_inc_and_prपूर्णांक(spage->dev,
				BTRFS_DEV_STAT_GENERATION_ERRS);
	पूर्ण

	वापस fail_cor + fail_gen;
पूर्ण

अटल व्योम scrub_block_get(काष्ठा scrub_block *sblock)
अणु
	refcount_inc(&sblock->refs);
पूर्ण

अटल व्योम scrub_block_put(काष्ठा scrub_block *sblock)
अणु
	अगर (refcount_dec_and_test(&sblock->refs)) अणु
		पूर्णांक i;

		अगर (sblock->sparity)
			scrub_parity_put(sblock->sparity);

		क्रम (i = 0; i < sblock->page_count; i++)
			scrub_page_put(sblock->pagev[i]);
		kमुक्त(sblock);
	पूर्ण
पूर्ण

अटल व्योम scrub_page_get(काष्ठा scrub_page *spage)
अणु
	atomic_inc(&spage->refs);
पूर्ण

अटल व्योम scrub_page_put(काष्ठा scrub_page *spage)
अणु
	अगर (atomic_dec_and_test(&spage->refs)) अणु
		अगर (spage->page)
			__मुक्त_page(spage->page);
		kमुक्त(spage);
	पूर्ण
पूर्ण

अटल व्योम scrub_submit(काष्ठा scrub_ctx *sctx)
अणु
	काष्ठा scrub_bio *sbio;

	अगर (sctx->curr == -1)
		वापस;

	sbio = sctx->bios[sctx->curr];
	sctx->curr = -1;
	scrub_pending_bio_inc(sctx);
	btrfsic_submit_bio(sbio->bio);
पूर्ण

अटल पूर्णांक scrub_add_page_to_rd_bio(काष्ठा scrub_ctx *sctx,
				    काष्ठा scrub_page *spage)
अणु
	काष्ठा scrub_block *sblock = spage->sblock;
	काष्ठा scrub_bio *sbio;
	पूर्णांक ret;

again:
	/*
	 * grab a fresh bio or रुको क्रम one to become available
	 */
	जबतक (sctx->curr == -1) अणु
		spin_lock(&sctx->list_lock);
		sctx->curr = sctx->first_मुक्त;
		अगर (sctx->curr != -1) अणु
			sctx->first_मुक्त = sctx->bios[sctx->curr]->next_मुक्त;
			sctx->bios[sctx->curr]->next_मुक्त = -1;
			sctx->bios[sctx->curr]->page_count = 0;
			spin_unlock(&sctx->list_lock);
		पूर्ण अन्यथा अणु
			spin_unlock(&sctx->list_lock);
			रुको_event(sctx->list_रुको, sctx->first_मुक्त != -1);
		पूर्ण
	पूर्ण
	sbio = sctx->bios[sctx->curr];
	अगर (sbio->page_count == 0) अणु
		काष्ठा bio *bio;

		sbio->physical = spage->physical;
		sbio->logical = spage->logical;
		sbio->dev = spage->dev;
		bio = sbio->bio;
		अगर (!bio) अणु
			bio = btrfs_io_bio_alloc(sctx->pages_per_rd_bio);
			sbio->bio = bio;
		पूर्ण

		bio->bi_निजी = sbio;
		bio->bi_end_io = scrub_bio_end_io;
		bio_set_dev(bio, sbio->dev->bdev);
		bio->bi_iter.bi_sector = sbio->physical >> 9;
		bio->bi_opf = REQ_OP_READ;
		sbio->status = 0;
	पूर्ण अन्यथा अगर (sbio->physical + sbio->page_count * PAGE_SIZE !=
		   spage->physical ||
		   sbio->logical + sbio->page_count * PAGE_SIZE !=
		   spage->logical ||
		   sbio->dev != spage->dev) अणु
		scrub_submit(sctx);
		जाओ again;
	पूर्ण

	sbio->pagev[sbio->page_count] = spage;
	ret = bio_add_page(sbio->bio, spage->page, PAGE_SIZE, 0);
	अगर (ret != PAGE_SIZE) अणु
		अगर (sbio->page_count < 1) अणु
			bio_put(sbio->bio);
			sbio->bio = शून्य;
			वापस -EIO;
		पूर्ण
		scrub_submit(sctx);
		जाओ again;
	पूर्ण

	scrub_block_get(sblock); /* one क्रम the page added to the bio */
	atomic_inc(&sblock->outstanding_pages);
	sbio->page_count++;
	अगर (sbio->page_count == sctx->pages_per_rd_bio)
		scrub_submit(sctx);

	वापस 0;
पूर्ण

अटल व्योम scrub_missing_raid56_end_io(काष्ठा bio *bio)
अणु
	काष्ठा scrub_block *sblock = bio->bi_निजी;
	काष्ठा btrfs_fs_info *fs_info = sblock->sctx->fs_info;

	अगर (bio->bi_status)
		sblock->no_io_error_seen = 0;

	bio_put(bio);

	btrfs_queue_work(fs_info->scrub_workers, &sblock->work);
पूर्ण

अटल व्योम scrub_missing_raid56_worker(काष्ठा btrfs_work *work)
अणु
	काष्ठा scrub_block *sblock = container_of(work, काष्ठा scrub_block, work);
	काष्ठा scrub_ctx *sctx = sblock->sctx;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	u64 logical;
	काष्ठा btrfs_device *dev;

	logical = sblock->pagev[0]->logical;
	dev = sblock->pagev[0]->dev;

	अगर (sblock->no_io_error_seen)
		scrub_recheck_block_checksum(sblock);

	अगर (!sblock->no_io_error_seen) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.पढ़ो_errors++;
		spin_unlock(&sctx->stat_lock);
		btrfs_err_rl_in_rcu(fs_info,
			"IO error rebuilding logical %llu for dev %s",
			logical, rcu_str_deref(dev->name));
	पूर्ण अन्यथा अगर (sblock->header_error || sblock->checksum_error) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.uncorrectable_errors++;
		spin_unlock(&sctx->stat_lock);
		btrfs_err_rl_in_rcu(fs_info,
			"failed to rebuild valid logical %llu for dev %s",
			logical, rcu_str_deref(dev->name));
	पूर्ण अन्यथा अणु
		scrub_ग_लिखो_block_to_dev_replace(sblock);
	पूर्ण

	अगर (sctx->is_dev_replace && sctx->flush_all_ग_लिखोs) अणु
		mutex_lock(&sctx->wr_lock);
		scrub_wr_submit(sctx);
		mutex_unlock(&sctx->wr_lock);
	पूर्ण

	scrub_block_put(sblock);
	scrub_pending_bio_dec(sctx);
पूर्ण

अटल व्योम scrub_missing_raid56_pages(काष्ठा scrub_block *sblock)
अणु
	काष्ठा scrub_ctx *sctx = sblock->sctx;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	u64 length = sblock->page_count * PAGE_SIZE;
	u64 logical = sblock->pagev[0]->logical;
	काष्ठा btrfs_bio *bbio = शून्य;
	काष्ठा bio *bio;
	काष्ठा btrfs_raid_bio *rbio;
	पूर्णांक ret;
	पूर्णांक i;

	btrfs_bio_counter_inc_blocked(fs_info);
	ret = btrfs_map_sblock(fs_info, BTRFS_MAP_GET_READ_MIRRORS, logical,
			&length, &bbio);
	अगर (ret || !bbio || !bbio->raid_map)
		जाओ bbio_out;

	अगर (WARN_ON(!sctx->is_dev_replace ||
		    !(bbio->map_type & BTRFS_BLOCK_GROUP_RAID56_MASK))) अणु
		/*
		 * We shouldn't be scrubbing a missing device. Even क्रम dev
		 * replace, we should only get here क्रम RAID 5/6. We either
		 * managed to mount something with no mirrors reमुख्यing or
		 * there's a bug in scrub_remap_extent()/btrfs_map_block().
		 */
		जाओ bbio_out;
	पूर्ण

	bio = btrfs_io_bio_alloc(0);
	bio->bi_iter.bi_sector = logical >> 9;
	bio->bi_निजी = sblock;
	bio->bi_end_io = scrub_missing_raid56_end_io;

	rbio = raid56_alloc_missing_rbio(fs_info, bio, bbio, length);
	अगर (!rbio)
		जाओ rbio_out;

	क्रम (i = 0; i < sblock->page_count; i++) अणु
		काष्ठा scrub_page *spage = sblock->pagev[i];

		raid56_add_scrub_pages(rbio, spage->page, spage->logical);
	पूर्ण

	btrfs_init_work(&sblock->work, scrub_missing_raid56_worker, शून्य, शून्य);
	scrub_block_get(sblock);
	scrub_pending_bio_inc(sctx);
	raid56_submit_missing_rbio(rbio);
	वापस;

rbio_out:
	bio_put(bio);
bbio_out:
	btrfs_bio_counter_dec(fs_info);
	btrfs_put_bbio(bbio);
	spin_lock(&sctx->stat_lock);
	sctx->stat.दो_स्मृति_errors++;
	spin_unlock(&sctx->stat_lock);
पूर्ण

अटल पूर्णांक scrub_pages(काष्ठा scrub_ctx *sctx, u64 logical, u32 len,
		       u64 physical, काष्ठा btrfs_device *dev, u64 flags,
		       u64 gen, पूर्णांक mirror_num, u8 *csum,
		       u64 physical_क्रम_dev_replace)
अणु
	काष्ठा scrub_block *sblock;
	स्थिर u32 sectorsize = sctx->fs_info->sectorsize;
	पूर्णांक index;

	sblock = kzalloc(माप(*sblock), GFP_KERNEL);
	अगर (!sblock) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.दो_स्मृति_errors++;
		spin_unlock(&sctx->stat_lock);
		वापस -ENOMEM;
	पूर्ण

	/* one ref inside this function, plus one क्रम each page added to
	 * a bio later on */
	refcount_set(&sblock->refs, 1);
	sblock->sctx = sctx;
	sblock->no_io_error_seen = 1;

	क्रम (index = 0; len > 0; index++) अणु
		काष्ठा scrub_page *spage;
		/*
		 * Here we will allocate one page क्रम one sector to scrub.
		 * This is fine अगर PAGE_SIZE == sectorsize, but will cost
		 * more memory क्रम PAGE_SIZE > sectorsize हाल.
		 */
		u32 l = min(sectorsize, len);

		spage = kzalloc(माप(*spage), GFP_KERNEL);
		अगर (!spage) अणु
leave_nomem:
			spin_lock(&sctx->stat_lock);
			sctx->stat.दो_स्मृति_errors++;
			spin_unlock(&sctx->stat_lock);
			scrub_block_put(sblock);
			वापस -ENOMEM;
		पूर्ण
		BUG_ON(index >= SCRUB_MAX_PAGES_PER_BLOCK);
		scrub_page_get(spage);
		sblock->pagev[index] = spage;
		spage->sblock = sblock;
		spage->dev = dev;
		spage->flags = flags;
		spage->generation = gen;
		spage->logical = logical;
		spage->physical = physical;
		spage->physical_क्रम_dev_replace = physical_क्रम_dev_replace;
		spage->mirror_num = mirror_num;
		अगर (csum) अणु
			spage->have_csum = 1;
			स_नकल(spage->csum, csum, sctx->fs_info->csum_size);
		पूर्ण अन्यथा अणु
			spage->have_csum = 0;
		पूर्ण
		sblock->page_count++;
		spage->page = alloc_page(GFP_KERNEL);
		अगर (!spage->page)
			जाओ leave_nomem;
		len -= l;
		logical += l;
		physical += l;
		physical_क्रम_dev_replace += l;
	पूर्ण

	WARN_ON(sblock->page_count == 0);
	अगर (test_bit(BTRFS_DEV_STATE_MISSING, &dev->dev_state)) अणु
		/*
		 * This हाल should only be hit क्रम RAID 5/6 device replace. See
		 * the comment in scrub_missing_raid56_pages() क्रम details.
		 */
		scrub_missing_raid56_pages(sblock);
	पूर्ण अन्यथा अणु
		क्रम (index = 0; index < sblock->page_count; index++) अणु
			काष्ठा scrub_page *spage = sblock->pagev[index];
			पूर्णांक ret;

			ret = scrub_add_page_to_rd_bio(sctx, spage);
			अगर (ret) अणु
				scrub_block_put(sblock);
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (flags & BTRFS_EXTENT_FLAG_SUPER)
			scrub_submit(sctx);
	पूर्ण

	/* last one मुक्तs, either here or in bio completion क्रम last page */
	scrub_block_put(sblock);
	वापस 0;
पूर्ण

अटल व्योम scrub_bio_end_io(काष्ठा bio *bio)
अणु
	काष्ठा scrub_bio *sbio = bio->bi_निजी;
	काष्ठा btrfs_fs_info *fs_info = sbio->dev->fs_info;

	sbio->status = bio->bi_status;
	sbio->bio = bio;

	btrfs_queue_work(fs_info->scrub_workers, &sbio->work);
पूर्ण

अटल व्योम scrub_bio_end_io_worker(काष्ठा btrfs_work *work)
अणु
	काष्ठा scrub_bio *sbio = container_of(work, काष्ठा scrub_bio, work);
	काष्ठा scrub_ctx *sctx = sbio->sctx;
	पूर्णांक i;

	BUG_ON(sbio->page_count > SCRUB_PAGES_PER_RD_BIO);
	अगर (sbio->status) अणु
		क्रम (i = 0; i < sbio->page_count; i++) अणु
			काष्ठा scrub_page *spage = sbio->pagev[i];

			spage->io_error = 1;
			spage->sblock->no_io_error_seen = 0;
		पूर्ण
	पूर्ण

	/* now complete the scrub_block items that have all pages completed */
	क्रम (i = 0; i < sbio->page_count; i++) अणु
		काष्ठा scrub_page *spage = sbio->pagev[i];
		काष्ठा scrub_block *sblock = spage->sblock;

		अगर (atomic_dec_and_test(&sblock->outstanding_pages))
			scrub_block_complete(sblock);
		scrub_block_put(sblock);
	पूर्ण

	bio_put(sbio->bio);
	sbio->bio = शून्य;
	spin_lock(&sctx->list_lock);
	sbio->next_मुक्त = sctx->first_मुक्त;
	sctx->first_मुक्त = sbio->index;
	spin_unlock(&sctx->list_lock);

	अगर (sctx->is_dev_replace && sctx->flush_all_ग_लिखोs) अणु
		mutex_lock(&sctx->wr_lock);
		scrub_wr_submit(sctx);
		mutex_unlock(&sctx->wr_lock);
	पूर्ण

	scrub_pending_bio_dec(sctx);
पूर्ण

अटल अंतरभूत व्योम __scrub_mark_biपंचांगap(काष्ठा scrub_parity *sparity,
				       अचिन्हित दीर्घ *biपंचांगap,
				       u64 start, u32 len)
अणु
	u64 offset;
	u32 nsectors;
	u32 sectorsize_bits = sparity->sctx->fs_info->sectorsize_bits;

	अगर (len >= sparity->stripe_len) अणु
		biपंचांगap_set(biपंचांगap, 0, sparity->nsectors);
		वापस;
	पूर्ण

	start -= sparity->logic_start;
	start = भाग64_u64_rem(start, sparity->stripe_len, &offset);
	offset = offset >> sectorsize_bits;
	nsectors = len >> sectorsize_bits;

	अगर (offset + nsectors <= sparity->nsectors) अणु
		biपंचांगap_set(biपंचांगap, offset, nsectors);
		वापस;
	पूर्ण

	biपंचांगap_set(biपंचांगap, offset, sparity->nsectors - offset);
	biपंचांगap_set(biपंचांगap, 0, nsectors - (sparity->nsectors - offset));
पूर्ण

अटल अंतरभूत व्योम scrub_parity_mark_sectors_error(काष्ठा scrub_parity *sparity,
						   u64 start, u32 len)
अणु
	__scrub_mark_biपंचांगap(sparity, sparity->ebiपंचांगap, start, len);
पूर्ण

अटल अंतरभूत व्योम scrub_parity_mark_sectors_data(काष्ठा scrub_parity *sparity,
						  u64 start, u32 len)
अणु
	__scrub_mark_biपंचांगap(sparity, sparity->dbiपंचांगap, start, len);
पूर्ण

अटल व्योम scrub_block_complete(काष्ठा scrub_block *sblock)
अणु
	पूर्णांक corrupted = 0;

	अगर (!sblock->no_io_error_seen) अणु
		corrupted = 1;
		scrub_handle_errored_block(sblock);
	पूर्ण अन्यथा अणु
		/*
		 * अगर has checksum error, ग_लिखो via repair mechanism in
		 * dev replace हाल, otherwise ग_लिखो here in dev replace
		 * हाल.
		 */
		corrupted = scrub_checksum(sblock);
		अगर (!corrupted && sblock->sctx->is_dev_replace)
			scrub_ग_लिखो_block_to_dev_replace(sblock);
	पूर्ण

	अगर (sblock->sparity && corrupted && !sblock->data_corrected) अणु
		u64 start = sblock->pagev[0]->logical;
		u64 end = sblock->pagev[sblock->page_count - 1]->logical +
			  PAGE_SIZE;

		ASSERT(end - start <= U32_MAX);
		scrub_parity_mark_sectors_error(sblock->sparity,
						start, end - start);
	पूर्ण
पूर्ण

अटल व्योम drop_csum_range(काष्ठा scrub_ctx *sctx, काष्ठा btrfs_ordered_sum *sum)
अणु
	sctx->stat.csum_discards += sum->len >> sctx->fs_info->sectorsize_bits;
	list_del(&sum->list);
	kमुक्त(sum);
पूर्ण

/*
 * Find the desired csum क्रम range [logical, logical + sectorsize), and store
 * the csum पूर्णांकo @csum.
 *
 * The search source is sctx->csum_list, which is a pre-populated list
 * storing bytenr ordered csum ranges.  We're reponsible to cleanup any range
 * that is beक्रमe @logical.
 *
 * Return 0 अगर there is no csum क्रम the range.
 * Return 1 अगर there is csum क्रम the range and copied to @csum.
 */
अटल पूर्णांक scrub_find_csum(काष्ठा scrub_ctx *sctx, u64 logical, u8 *csum)
अणु
	bool found = false;

	जबतक (!list_empty(&sctx->csum_list)) अणु
		काष्ठा btrfs_ordered_sum *sum = शून्य;
		अचिन्हित दीर्घ index;
		अचिन्हित दीर्घ num_sectors;

		sum = list_first_entry(&sctx->csum_list,
				       काष्ठा btrfs_ordered_sum, list);
		/* The current csum range is beyond our range, no csum found */
		अगर (sum->bytenr > logical)
			अवरोध;

		/*
		 * The current sum is beक्रमe our bytenr, since scrub is always
		 * करोne in bytenr order, the csum will never be used anymore,
		 * clean it up so that later calls won't bother with the range,
		 * and जारी search the next range.
		 */
		अगर (sum->bytenr + sum->len <= logical) अणु
			drop_csum_range(sctx, sum);
			जारी;
		पूर्ण

		/* Now the csum range covers our bytenr, copy the csum */
		found = true;
		index = (logical - sum->bytenr) >> sctx->fs_info->sectorsize_bits;
		num_sectors = sum->len >> sctx->fs_info->sectorsize_bits;

		स_नकल(csum, sum->sums + index * sctx->fs_info->csum_size,
		       sctx->fs_info->csum_size);

		/* Cleanup the range अगर we're at the end of the csum range */
		अगर (index == num_sectors - 1)
			drop_csum_range(sctx, sum);
		अवरोध;
	पूर्ण
	अगर (!found)
		वापस 0;
	वापस 1;
पूर्ण

/* scrub extent tries to collect up to 64 kB क्रम each bio */
अटल पूर्णांक scrub_extent(काष्ठा scrub_ctx *sctx, काष्ठा map_lookup *map,
			u64 logical, u32 len,
			u64 physical, काष्ठा btrfs_device *dev, u64 flags,
			u64 gen, पूर्णांक mirror_num, u64 physical_क्रम_dev_replace)
अणु
	पूर्णांक ret;
	u8 csum[BTRFS_CSUM_SIZE];
	u32 blocksize;

	अगर (flags & BTRFS_EXTENT_FLAG_DATA) अणु
		अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK)
			blocksize = map->stripe_len;
		अन्यथा
			blocksize = sctx->fs_info->sectorsize;
		spin_lock(&sctx->stat_lock);
		sctx->stat.data_extents_scrubbed++;
		sctx->stat.data_bytes_scrubbed += len;
		spin_unlock(&sctx->stat_lock);
	पूर्ण अन्यथा अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) अणु
		अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK)
			blocksize = map->stripe_len;
		अन्यथा
			blocksize = sctx->fs_info->nodesize;
		spin_lock(&sctx->stat_lock);
		sctx->stat.tree_extents_scrubbed++;
		sctx->stat.tree_bytes_scrubbed += len;
		spin_unlock(&sctx->stat_lock);
	पूर्ण अन्यथा अणु
		blocksize = sctx->fs_info->sectorsize;
		WARN_ON(1);
	पूर्ण

	जबतक (len) अणु
		u32 l = min(len, blocksize);
		पूर्णांक have_csum = 0;

		अगर (flags & BTRFS_EXTENT_FLAG_DATA) अणु
			/* push csums to sbio */
			have_csum = scrub_find_csum(sctx, logical, csum);
			अगर (have_csum == 0)
				++sctx->stat.no_csum;
		पूर्ण
		ret = scrub_pages(sctx, logical, l, physical, dev, flags, gen,
				  mirror_num, have_csum ? csum : शून्य,
				  physical_क्रम_dev_replace);
		अगर (ret)
			वापस ret;
		len -= l;
		logical += l;
		physical += l;
		physical_क्रम_dev_replace += l;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक scrub_pages_क्रम_parity(काष्ठा scrub_parity *sparity,
				  u64 logical, u32 len,
				  u64 physical, काष्ठा btrfs_device *dev,
				  u64 flags, u64 gen, पूर्णांक mirror_num, u8 *csum)
अणु
	काष्ठा scrub_ctx *sctx = sparity->sctx;
	काष्ठा scrub_block *sblock;
	स्थिर u32 sectorsize = sctx->fs_info->sectorsize;
	पूर्णांक index;

	ASSERT(IS_ALIGNED(len, sectorsize));

	sblock = kzalloc(माप(*sblock), GFP_KERNEL);
	अगर (!sblock) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.दो_स्मृति_errors++;
		spin_unlock(&sctx->stat_lock);
		वापस -ENOMEM;
	पूर्ण

	/* one ref inside this function, plus one क्रम each page added to
	 * a bio later on */
	refcount_set(&sblock->refs, 1);
	sblock->sctx = sctx;
	sblock->no_io_error_seen = 1;
	sblock->sparity = sparity;
	scrub_parity_get(sparity);

	क्रम (index = 0; len > 0; index++) अणु
		काष्ठा scrub_page *spage;

		spage = kzalloc(माप(*spage), GFP_KERNEL);
		अगर (!spage) अणु
leave_nomem:
			spin_lock(&sctx->stat_lock);
			sctx->stat.दो_स्मृति_errors++;
			spin_unlock(&sctx->stat_lock);
			scrub_block_put(sblock);
			वापस -ENOMEM;
		पूर्ण
		BUG_ON(index >= SCRUB_MAX_PAGES_PER_BLOCK);
		/* For scrub block */
		scrub_page_get(spage);
		sblock->pagev[index] = spage;
		/* For scrub parity */
		scrub_page_get(spage);
		list_add_tail(&spage->list, &sparity->spages);
		spage->sblock = sblock;
		spage->dev = dev;
		spage->flags = flags;
		spage->generation = gen;
		spage->logical = logical;
		spage->physical = physical;
		spage->mirror_num = mirror_num;
		अगर (csum) अणु
			spage->have_csum = 1;
			स_नकल(spage->csum, csum, sctx->fs_info->csum_size);
		पूर्ण अन्यथा अणु
			spage->have_csum = 0;
		पूर्ण
		sblock->page_count++;
		spage->page = alloc_page(GFP_KERNEL);
		अगर (!spage->page)
			जाओ leave_nomem;


		/* Iterate over the stripe range in sectorsize steps */
		len -= sectorsize;
		logical += sectorsize;
		physical += sectorsize;
	पूर्ण

	WARN_ON(sblock->page_count == 0);
	क्रम (index = 0; index < sblock->page_count; index++) अणु
		काष्ठा scrub_page *spage = sblock->pagev[index];
		पूर्णांक ret;

		ret = scrub_add_page_to_rd_bio(sctx, spage);
		अगर (ret) अणु
			scrub_block_put(sblock);
			वापस ret;
		पूर्ण
	पूर्ण

	/* last one मुक्तs, either here or in bio completion क्रम last page */
	scrub_block_put(sblock);
	वापस 0;
पूर्ण

अटल पूर्णांक scrub_extent_क्रम_parity(काष्ठा scrub_parity *sparity,
				   u64 logical, u32 len,
				   u64 physical, काष्ठा btrfs_device *dev,
				   u64 flags, u64 gen, पूर्णांक mirror_num)
अणु
	काष्ठा scrub_ctx *sctx = sparity->sctx;
	पूर्णांक ret;
	u8 csum[BTRFS_CSUM_SIZE];
	u32 blocksize;

	अगर (test_bit(BTRFS_DEV_STATE_MISSING, &dev->dev_state)) अणु
		scrub_parity_mark_sectors_error(sparity, logical, len);
		वापस 0;
	पूर्ण

	अगर (flags & BTRFS_EXTENT_FLAG_DATA) अणु
		blocksize = sparity->stripe_len;
	पूर्ण अन्यथा अगर (flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) अणु
		blocksize = sparity->stripe_len;
	पूर्ण अन्यथा अणु
		blocksize = sctx->fs_info->sectorsize;
		WARN_ON(1);
	पूर्ण

	जबतक (len) अणु
		u32 l = min(len, blocksize);
		पूर्णांक have_csum = 0;

		अगर (flags & BTRFS_EXTENT_FLAG_DATA) अणु
			/* push csums to sbio */
			have_csum = scrub_find_csum(sctx, logical, csum);
			अगर (have_csum == 0)
				जाओ skip;
		पूर्ण
		ret = scrub_pages_क्रम_parity(sparity, logical, l, physical, dev,
					     flags, gen, mirror_num,
					     have_csum ? csum : शून्य);
		अगर (ret)
			वापस ret;
skip:
		len -= l;
		logical += l;
		physical += l;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Given a physical address, this will calculate it's
 * logical offset. अगर this is a parity stripe, it will वापस
 * the most left data stripe's logical offset.
 *
 * वापस 0 अगर it is a data stripe, 1 means parity stripe.
 */
अटल पूर्णांक get_raid56_logic_offset(u64 physical, पूर्णांक num,
				   काष्ठा map_lookup *map, u64 *offset,
				   u64 *stripe_start)
अणु
	पूर्णांक i;
	पूर्णांक j = 0;
	u64 stripe_nr;
	u64 last_offset;
	u32 stripe_index;
	u32 rot;
	स्थिर पूर्णांक data_stripes = nr_data_stripes(map);

	last_offset = (physical - map->stripes[num].physical) * data_stripes;
	अगर (stripe_start)
		*stripe_start = last_offset;

	*offset = last_offset;
	क्रम (i = 0; i < data_stripes; i++) अणु
		*offset = last_offset + i * map->stripe_len;

		stripe_nr = भाग64_u64(*offset, map->stripe_len);
		stripe_nr = भाग_u64(stripe_nr, data_stripes);

		/* Work out the disk rotation on this stripe-set */
		stripe_nr = भाग_u64_rem(stripe_nr, map->num_stripes, &rot);
		/* calculate which stripe this data locates */
		rot += i;
		stripe_index = rot % map->num_stripes;
		अगर (stripe_index == num)
			वापस 0;
		अगर (stripe_index < num)
			j++;
	पूर्ण
	*offset = last_offset + j * map->stripe_len;
	वापस 1;
पूर्ण

अटल व्योम scrub_मुक्त_parity(काष्ठा scrub_parity *sparity)
अणु
	काष्ठा scrub_ctx *sctx = sparity->sctx;
	काष्ठा scrub_page *curr, *next;
	पूर्णांक nbits;

	nbits = biपंचांगap_weight(sparity->ebiपंचांगap, sparity->nsectors);
	अगर (nbits) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.पढ़ो_errors += nbits;
		sctx->stat.uncorrectable_errors += nbits;
		spin_unlock(&sctx->stat_lock);
	पूर्ण

	list_क्रम_each_entry_safe(curr, next, &sparity->spages, list) अणु
		list_del_init(&curr->list);
		scrub_page_put(curr);
	पूर्ण

	kमुक्त(sparity);
पूर्ण

अटल व्योम scrub_parity_bio_endio_worker(काष्ठा btrfs_work *work)
अणु
	काष्ठा scrub_parity *sparity = container_of(work, काष्ठा scrub_parity,
						    work);
	काष्ठा scrub_ctx *sctx = sparity->sctx;

	scrub_मुक्त_parity(sparity);
	scrub_pending_bio_dec(sctx);
पूर्ण

अटल व्योम scrub_parity_bio_endio(काष्ठा bio *bio)
अणु
	काष्ठा scrub_parity *sparity = (काष्ठा scrub_parity *)bio->bi_निजी;
	काष्ठा btrfs_fs_info *fs_info = sparity->sctx->fs_info;

	अगर (bio->bi_status)
		biपंचांगap_or(sparity->ebiपंचांगap, sparity->ebiपंचांगap, sparity->dbiपंचांगap,
			  sparity->nsectors);

	bio_put(bio);

	btrfs_init_work(&sparity->work, scrub_parity_bio_endio_worker, शून्य,
			शून्य);
	btrfs_queue_work(fs_info->scrub_parity_workers, &sparity->work);
पूर्ण

अटल व्योम scrub_parity_check_and_repair(काष्ठा scrub_parity *sparity)
अणु
	काष्ठा scrub_ctx *sctx = sparity->sctx;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	काष्ठा bio *bio;
	काष्ठा btrfs_raid_bio *rbio;
	काष्ठा btrfs_bio *bbio = शून्य;
	u64 length;
	पूर्णांक ret;

	अगर (!biपंचांगap_andnot(sparity->dbiपंचांगap, sparity->dbiपंचांगap, sparity->ebiपंचांगap,
			   sparity->nsectors))
		जाओ out;

	length = sparity->logic_end - sparity->logic_start;

	btrfs_bio_counter_inc_blocked(fs_info);
	ret = btrfs_map_sblock(fs_info, BTRFS_MAP_WRITE, sparity->logic_start,
			       &length, &bbio);
	अगर (ret || !bbio || !bbio->raid_map)
		जाओ bbio_out;

	bio = btrfs_io_bio_alloc(0);
	bio->bi_iter.bi_sector = sparity->logic_start >> 9;
	bio->bi_निजी = sparity;
	bio->bi_end_io = scrub_parity_bio_endio;

	rbio = raid56_parity_alloc_scrub_rbio(fs_info, bio, bbio,
					      length, sparity->scrub_dev,
					      sparity->dbiपंचांगap,
					      sparity->nsectors);
	अगर (!rbio)
		जाओ rbio_out;

	scrub_pending_bio_inc(sctx);
	raid56_parity_submit_scrub_rbio(rbio);
	वापस;

rbio_out:
	bio_put(bio);
bbio_out:
	btrfs_bio_counter_dec(fs_info);
	btrfs_put_bbio(bbio);
	biपंचांगap_or(sparity->ebiपंचांगap, sparity->ebiपंचांगap, sparity->dbiपंचांगap,
		  sparity->nsectors);
	spin_lock(&sctx->stat_lock);
	sctx->stat.दो_स्मृति_errors++;
	spin_unlock(&sctx->stat_lock);
out:
	scrub_मुक्त_parity(sparity);
पूर्ण

अटल अंतरभूत पूर्णांक scrub_calc_parity_biपंचांगap_len(पूर्णांक nsectors)
अणु
	वापस DIV_ROUND_UP(nsectors, BITS_PER_LONG) * माप(दीर्घ);
पूर्ण

अटल व्योम scrub_parity_get(काष्ठा scrub_parity *sparity)
अणु
	refcount_inc(&sparity->refs);
पूर्ण

अटल व्योम scrub_parity_put(काष्ठा scrub_parity *sparity)
अणु
	अगर (!refcount_dec_and_test(&sparity->refs))
		वापस;

	scrub_parity_check_and_repair(sparity);
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक scrub_raid56_parity(काष्ठा scrub_ctx *sctx,
						  काष्ठा map_lookup *map,
						  काष्ठा btrfs_device *sdev,
						  काष्ठा btrfs_path *path,
						  u64 logic_start,
						  u64 logic_end)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	काष्ठा btrfs_root *root = fs_info->extent_root;
	काष्ठा btrfs_root *csum_root = fs_info->csum_root;
	काष्ठा btrfs_extent_item *extent;
	काष्ठा btrfs_bio *bbio = शून्य;
	u64 flags;
	पूर्णांक ret;
	पूर्णांक slot;
	काष्ठा extent_buffer *l;
	काष्ठा btrfs_key key;
	u64 generation;
	u64 extent_logical;
	u64 extent_physical;
	/* Check the comment in scrub_stripe() क्रम why u32 is enough here */
	u32 extent_len;
	u64 mapped_length;
	काष्ठा btrfs_device *extent_dev;
	काष्ठा scrub_parity *sparity;
	पूर्णांक nsectors;
	पूर्णांक biपंचांगap_len;
	पूर्णांक extent_mirror_num;
	पूर्णांक stop_loop = 0;

	ASSERT(map->stripe_len <= U32_MAX);
	nsectors = map->stripe_len >> fs_info->sectorsize_bits;
	biपंचांगap_len = scrub_calc_parity_biपंचांगap_len(nsectors);
	sparity = kzalloc(माप(काष्ठा scrub_parity) + 2 * biपंचांगap_len,
			  GFP_NOFS);
	अगर (!sparity) अणु
		spin_lock(&sctx->stat_lock);
		sctx->stat.दो_स्मृति_errors++;
		spin_unlock(&sctx->stat_lock);
		वापस -ENOMEM;
	पूर्ण

	ASSERT(map->stripe_len <= U32_MAX);
	sparity->stripe_len = map->stripe_len;
	sparity->nsectors = nsectors;
	sparity->sctx = sctx;
	sparity->scrub_dev = sdev;
	sparity->logic_start = logic_start;
	sparity->logic_end = logic_end;
	refcount_set(&sparity->refs, 1);
	INIT_LIST_HEAD(&sparity->spages);
	sparity->dbiपंचांगap = sparity->biपंचांगap;
	sparity->ebiपंचांगap = (व्योम *)sparity->biपंचांगap + biपंचांगap_len;

	ret = 0;
	जबतक (logic_start < logic_end) अणु
		अगर (btrfs_fs_incompat(fs_info, SKINNY_METADATA))
			key.type = BTRFS_METADATA_ITEM_KEY;
		अन्यथा
			key.type = BTRFS_EXTENT_ITEM_KEY;
		key.objectid = logic_start;
		key.offset = (u64)-1;

		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		अगर (ret < 0)
			जाओ out;

		अगर (ret > 0) अणु
			ret = btrfs_previous_extent_item(root, path, 0);
			अगर (ret < 0)
				जाओ out;
			अगर (ret > 0) अणु
				btrfs_release_path(path);
				ret = btrfs_search_slot(शून्य, root, &key,
							path, 0, 0);
				अगर (ret < 0)
					जाओ out;
			पूर्ण
		पूर्ण

		stop_loop = 0;
		जबतक (1) अणु
			u64 bytes;

			l = path->nodes[0];
			slot = path->slots[0];
			अगर (slot >= btrfs_header_nritems(l)) अणु
				ret = btrfs_next_leaf(root, path);
				अगर (ret == 0)
					जारी;
				अगर (ret < 0)
					जाओ out;

				stop_loop = 1;
				अवरोध;
			पूर्ण
			btrfs_item_key_to_cpu(l, &key, slot);

			अगर (key.type != BTRFS_EXTENT_ITEM_KEY &&
			    key.type != BTRFS_METADATA_ITEM_KEY)
				जाओ next;

			अगर (key.type == BTRFS_METADATA_ITEM_KEY)
				bytes = fs_info->nodesize;
			अन्यथा
				bytes = key.offset;

			अगर (key.objectid + bytes <= logic_start)
				जाओ next;

			अगर (key.objectid >= logic_end) अणु
				stop_loop = 1;
				अवरोध;
			पूर्ण

			जबतक (key.objectid >= logic_start + map->stripe_len)
				logic_start += map->stripe_len;

			extent = btrfs_item_ptr(l, slot,
						काष्ठा btrfs_extent_item);
			flags = btrfs_extent_flags(l, extent);
			generation = btrfs_extent_generation(l, extent);

			अगर ((flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) &&
			    (key.objectid < logic_start ||
			     key.objectid + bytes >
			     logic_start + map->stripe_len)) अणु
				btrfs_err(fs_info,
					  "scrub: tree block %llu spanning stripes, ignored. logical=%llu",
					  key.objectid, logic_start);
				spin_lock(&sctx->stat_lock);
				sctx->stat.uncorrectable_errors++;
				spin_unlock(&sctx->stat_lock);
				जाओ next;
			पूर्ण
again:
			extent_logical = key.objectid;
			ASSERT(bytes <= U32_MAX);
			extent_len = bytes;

			अगर (extent_logical < logic_start) अणु
				extent_len -= logic_start - extent_logical;
				extent_logical = logic_start;
			पूर्ण

			अगर (extent_logical + extent_len >
			    logic_start + map->stripe_len)
				extent_len = logic_start + map->stripe_len -
					     extent_logical;

			scrub_parity_mark_sectors_data(sparity, extent_logical,
						       extent_len);

			mapped_length = extent_len;
			bbio = शून्य;
			ret = btrfs_map_block(fs_info, BTRFS_MAP_READ,
					extent_logical, &mapped_length, &bbio,
					0);
			अगर (!ret) अणु
				अगर (!bbio || mapped_length < extent_len)
					ret = -EIO;
			पूर्ण
			अगर (ret) अणु
				btrfs_put_bbio(bbio);
				जाओ out;
			पूर्ण
			extent_physical = bbio->stripes[0].physical;
			extent_mirror_num = bbio->mirror_num;
			extent_dev = bbio->stripes[0].dev;
			btrfs_put_bbio(bbio);

			ret = btrfs_lookup_csums_range(csum_root,
						extent_logical,
						extent_logical + extent_len - 1,
						&sctx->csum_list, 1);
			अगर (ret)
				जाओ out;

			ret = scrub_extent_क्रम_parity(sparity, extent_logical,
						      extent_len,
						      extent_physical,
						      extent_dev, flags,
						      generation,
						      extent_mirror_num);

			scrub_मुक्त_csums(sctx);

			अगर (ret)
				जाओ out;

			अगर (extent_logical + extent_len <
			    key.objectid + bytes) अणु
				logic_start += map->stripe_len;

				अगर (logic_start >= logic_end) अणु
					stop_loop = 1;
					अवरोध;
				पूर्ण

				अगर (logic_start < key.objectid + bytes) अणु
					cond_resched();
					जाओ again;
				पूर्ण
			पूर्ण
next:
			path->slots[0]++;
		पूर्ण

		btrfs_release_path(path);

		अगर (stop_loop)
			अवरोध;

		logic_start += map->stripe_len;
	पूर्ण
out:
	अगर (ret < 0) अणु
		ASSERT(logic_end - logic_start <= U32_MAX);
		scrub_parity_mark_sectors_error(sparity, logic_start,
						logic_end - logic_start);
	पूर्ण
	scrub_parity_put(sparity);
	scrub_submit(sctx);
	mutex_lock(&sctx->wr_lock);
	scrub_wr_submit(sctx);
	mutex_unlock(&sctx->wr_lock);

	btrfs_release_path(path);
	वापस ret < 0 ? ret : 0;
पूर्ण

अटल व्योम sync_replace_क्रम_zoned(काष्ठा scrub_ctx *sctx)
अणु
	अगर (!btrfs_is_zoned(sctx->fs_info))
		वापस;

	sctx->flush_all_ग_लिखोs = true;
	scrub_submit(sctx);
	mutex_lock(&sctx->wr_lock);
	scrub_wr_submit(sctx);
	mutex_unlock(&sctx->wr_lock);

	रुको_event(sctx->list_रुको, atomic_पढ़ो(&sctx->bios_in_flight) == 0);
पूर्ण

अटल पूर्णांक sync_ग_लिखो_poपूर्णांकer_क्रम_zoned(काष्ठा scrub_ctx *sctx, u64 logical,
					u64 physical, u64 physical_end)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	पूर्णांक ret = 0;

	अगर (!btrfs_is_zoned(fs_info))
		वापस 0;

	रुको_event(sctx->list_रुको, atomic_पढ़ो(&sctx->bios_in_flight) == 0);

	mutex_lock(&sctx->wr_lock);
	अगर (sctx->ग_लिखो_poपूर्णांकer < physical_end) अणु
		ret = btrfs_sync_zone_ग_लिखो_poपूर्णांकer(sctx->wr_tgtdev, logical,
						    physical,
						    sctx->ग_लिखो_poपूर्णांकer);
		अगर (ret)
			btrfs_err(fs_info,
				  "zoned: failed to recover write pointer");
	पूर्ण
	mutex_unlock(&sctx->wr_lock);
	btrfs_dev_clear_zone_empty(sctx->wr_tgtdev, physical);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक scrub_stripe(काष्ठा scrub_ctx *sctx,
					   काष्ठा map_lookup *map,
					   काष्ठा btrfs_device *scrub_dev,
					   पूर्णांक num, u64 base, u64 length,
					   काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_path *path, *ppath;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	काष्ठा btrfs_root *root = fs_info->extent_root;
	काष्ठा btrfs_root *csum_root = fs_info->csum_root;
	काष्ठा btrfs_extent_item *extent;
	काष्ठा blk_plug plug;
	u64 flags;
	पूर्णांक ret;
	पूर्णांक slot;
	u64 nstripes;
	काष्ठा extent_buffer *l;
	u64 physical;
	u64 logical;
	u64 logic_end;
	u64 physical_end;
	u64 generation;
	पूर्णांक mirror_num;
	काष्ठा पढ़ोa_control *पढ़ोa1;
	काष्ठा पढ़ोa_control *पढ़ोa2;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key key_end;
	u64 increment = map->stripe_len;
	u64 offset;
	u64 extent_logical;
	u64 extent_physical;
	/*
	 * Unlike chunk length, extent length should never go beyond
	 * BTRFS_MAX_EXTENT_SIZE, thus u32 is enough here.
	 */
	u32 extent_len;
	u64 stripe_logical;
	u64 stripe_end;
	काष्ठा btrfs_device *extent_dev;
	पूर्णांक extent_mirror_num;
	पूर्णांक stop_loop = 0;

	physical = map->stripes[num].physical;
	offset = 0;
	nstripes = भाग64_u64(length, map->stripe_len);
	अगर (map->type & BTRFS_BLOCK_GROUP_RAID0) अणु
		offset = map->stripe_len * num;
		increment = map->stripe_len * map->num_stripes;
		mirror_num = 1;
	पूर्ण अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID10) अणु
		पूर्णांक factor = map->num_stripes / map->sub_stripes;
		offset = map->stripe_len * (num / map->sub_stripes);
		increment = map->stripe_len * factor;
		mirror_num = num % map->sub_stripes + 1;
	पूर्ण अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID1_MASK) अणु
		increment = map->stripe_len;
		mirror_num = num % map->num_stripes + 1;
	पूर्ण अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_DUP) अणु
		increment = map->stripe_len;
		mirror_num = num % map->num_stripes + 1;
	पूर्ण अन्यथा अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK) अणु
		get_raid56_logic_offset(physical, num, map, &offset, शून्य);
		increment = map->stripe_len * nr_data_stripes(map);
		mirror_num = 1;
	पूर्ण अन्यथा अणु
		increment = map->stripe_len;
		mirror_num = 1;
	पूर्ण

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	ppath = btrfs_alloc_path();
	अगर (!ppath) अणु
		btrfs_मुक्त_path(path);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * work on commit root. The related disk blocks are अटल as
	 * दीर्घ as COW is applied. This means, it is save to reग_लिखो
	 * them to repair disk errors without any race conditions
	 */
	path->search_commit_root = 1;
	path->skip_locking = 1;

	ppath->search_commit_root = 1;
	ppath->skip_locking = 1;
	/*
	 * trigger the पढ़ोahead क्रम extent tree csum tree and रुको क्रम
	 * completion. During पढ़ोahead, the scrub is officially छोड़ोd
	 * to not hold off transaction commits
	 */
	logical = base + offset;
	physical_end = physical + nstripes * map->stripe_len;
	अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK) अणु
		get_raid56_logic_offset(physical_end, num,
					map, &logic_end, शून्य);
		logic_end += base;
	पूर्ण अन्यथा अणु
		logic_end = logical + increment * nstripes;
	पूर्ण
	रुको_event(sctx->list_रुको,
		   atomic_पढ़ो(&sctx->bios_in_flight) == 0);
	scrub_blocked_अगर_needed(fs_info);

	/* FIXME it might be better to start पढ़ोahead at commit root */
	key.objectid = logical;
	key.type = BTRFS_EXTENT_ITEM_KEY;
	key.offset = (u64)0;
	key_end.objectid = logic_end;
	key_end.type = BTRFS_METADATA_ITEM_KEY;
	key_end.offset = (u64)-1;
	पढ़ोa1 = btrfs_पढ़ोa_add(root, &key, &key_end);

	अगर (cache->flags & BTRFS_BLOCK_GROUP_DATA) अणु
		key.objectid = BTRFS_EXTENT_CSUM_OBJECTID;
		key.type = BTRFS_EXTENT_CSUM_KEY;
		key.offset = logical;
		key_end.objectid = BTRFS_EXTENT_CSUM_OBJECTID;
		key_end.type = BTRFS_EXTENT_CSUM_KEY;
		key_end.offset = logic_end;
		पढ़ोa2 = btrfs_पढ़ोa_add(csum_root, &key, &key_end);
	पूर्ण अन्यथा अणु
		पढ़ोa2 = शून्य;
	पूर्ण

	अगर (!IS_ERR(पढ़ोa1))
		btrfs_पढ़ोa_रुको(पढ़ोa1);
	अगर (!IS_ERR_OR_शून्य(पढ़ोa2))
		btrfs_पढ़ोa_रुको(पढ़ोa2);


	/*
	 * collect all data csums क्रम the stripe to aव्योम seeking during
	 * the scrub. This might currently (crc32) end up to be about 1MB
	 */
	blk_start_plug(&plug);

	अगर (sctx->is_dev_replace &&
	    btrfs_dev_is_sequential(sctx->wr_tgtdev, physical)) अणु
		mutex_lock(&sctx->wr_lock);
		sctx->ग_लिखो_poपूर्णांकer = physical;
		mutex_unlock(&sctx->wr_lock);
		sctx->flush_all_ग_लिखोs = true;
	पूर्ण

	/*
	 * now find all extents क्रम each stripe and scrub them
	 */
	ret = 0;
	जबतक (physical < physical_end) अणु
		/*
		 * canceled?
		 */
		अगर (atomic_पढ़ो(&fs_info->scrub_cancel_req) ||
		    atomic_पढ़ो(&sctx->cancel_req)) अणु
			ret = -ECANCELED;
			जाओ out;
		पूर्ण
		/*
		 * check to see अगर we have to छोड़ो
		 */
		अगर (atomic_पढ़ो(&fs_info->scrub_छोड़ो_req)) अणु
			/* push queued extents */
			sctx->flush_all_ग_लिखोs = true;
			scrub_submit(sctx);
			mutex_lock(&sctx->wr_lock);
			scrub_wr_submit(sctx);
			mutex_unlock(&sctx->wr_lock);
			रुको_event(sctx->list_रुको,
				   atomic_पढ़ो(&sctx->bios_in_flight) == 0);
			sctx->flush_all_ग_लिखोs = false;
			scrub_blocked_अगर_needed(fs_info);
		पूर्ण

		अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK) अणु
			ret = get_raid56_logic_offset(physical, num, map,
						      &logical,
						      &stripe_logical);
			logical += base;
			अगर (ret) अणु
				/* it is parity strip */
				stripe_logical += base;
				stripe_end = stripe_logical + increment;
				ret = scrub_raid56_parity(sctx, map, scrub_dev,
							  ppath, stripe_logical,
							  stripe_end);
				अगर (ret)
					जाओ out;
				जाओ skip;
			पूर्ण
		पूर्ण

		अगर (btrfs_fs_incompat(fs_info, SKINNY_METADATA))
			key.type = BTRFS_METADATA_ITEM_KEY;
		अन्यथा
			key.type = BTRFS_EXTENT_ITEM_KEY;
		key.objectid = logical;
		key.offset = (u64)-1;

		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		अगर (ret < 0)
			जाओ out;

		अगर (ret > 0) अणु
			ret = btrfs_previous_extent_item(root, path, 0);
			अगर (ret < 0)
				जाओ out;
			अगर (ret > 0) अणु
				/* there's no smaller item, so stick with the
				 * larger one */
				btrfs_release_path(path);
				ret = btrfs_search_slot(शून्य, root, &key,
							path, 0, 0);
				अगर (ret < 0)
					जाओ out;
			पूर्ण
		पूर्ण

		stop_loop = 0;
		जबतक (1) अणु
			u64 bytes;

			l = path->nodes[0];
			slot = path->slots[0];
			अगर (slot >= btrfs_header_nritems(l)) अणु
				ret = btrfs_next_leaf(root, path);
				अगर (ret == 0)
					जारी;
				अगर (ret < 0)
					जाओ out;

				stop_loop = 1;
				अवरोध;
			पूर्ण
			btrfs_item_key_to_cpu(l, &key, slot);

			अगर (key.type != BTRFS_EXTENT_ITEM_KEY &&
			    key.type != BTRFS_METADATA_ITEM_KEY)
				जाओ next;

			अगर (key.type == BTRFS_METADATA_ITEM_KEY)
				bytes = fs_info->nodesize;
			अन्यथा
				bytes = key.offset;

			अगर (key.objectid + bytes <= logical)
				जाओ next;

			अगर (key.objectid >= logical + map->stripe_len) अणु
				/* out of this device extent */
				अगर (key.objectid >= logic_end)
					stop_loop = 1;
				अवरोध;
			पूर्ण

			/*
			 * If our block group was हटाओd in the meanजबतक, just
			 * stop scrubbing since there is no poपूर्णांक in continuing.
			 * Continuing would prevent reusing its device extents
			 * क्रम new block groups क्रम a दीर्घ समय.
			 */
			spin_lock(&cache->lock);
			अगर (cache->हटाओd) अणु
				spin_unlock(&cache->lock);
				ret = 0;
				जाओ out;
			पूर्ण
			spin_unlock(&cache->lock);

			extent = btrfs_item_ptr(l, slot,
						काष्ठा btrfs_extent_item);
			flags = btrfs_extent_flags(l, extent);
			generation = btrfs_extent_generation(l, extent);

			अगर ((flags & BTRFS_EXTENT_FLAG_TREE_BLOCK) &&
			    (key.objectid < logical ||
			     key.objectid + bytes >
			     logical + map->stripe_len)) अणु
				btrfs_err(fs_info,
					   "scrub: tree block %llu spanning stripes, ignored. logical=%llu",
				       key.objectid, logical);
				spin_lock(&sctx->stat_lock);
				sctx->stat.uncorrectable_errors++;
				spin_unlock(&sctx->stat_lock);
				जाओ next;
			पूर्ण

again:
			extent_logical = key.objectid;
			ASSERT(bytes <= U32_MAX);
			extent_len = bytes;

			/*
			 * trim extent to this stripe
			 */
			अगर (extent_logical < logical) अणु
				extent_len -= logical - extent_logical;
				extent_logical = logical;
			पूर्ण
			अगर (extent_logical + extent_len >
			    logical + map->stripe_len) अणु
				extent_len = logical + map->stripe_len -
					     extent_logical;
			पूर्ण

			extent_physical = extent_logical - logical + physical;
			extent_dev = scrub_dev;
			extent_mirror_num = mirror_num;
			अगर (sctx->is_dev_replace)
				scrub_remap_extent(fs_info, extent_logical,
						   extent_len, &extent_physical,
						   &extent_dev,
						   &extent_mirror_num);

			अगर (flags & BTRFS_EXTENT_FLAG_DATA) अणु
				ret = btrfs_lookup_csums_range(csum_root,
						extent_logical,
						extent_logical + extent_len - 1,
						&sctx->csum_list, 1);
				अगर (ret)
					जाओ out;
			पूर्ण

			ret = scrub_extent(sctx, map, extent_logical, extent_len,
					   extent_physical, extent_dev, flags,
					   generation, extent_mirror_num,
					   extent_logical - logical + physical);

			scrub_मुक्त_csums(sctx);

			अगर (ret)
				जाओ out;

			अगर (sctx->is_dev_replace)
				sync_replace_क्रम_zoned(sctx);

			अगर (extent_logical + extent_len <
			    key.objectid + bytes) अणु
				अगर (map->type & BTRFS_BLOCK_GROUP_RAID56_MASK) अणु
					/*
					 * loop until we find next data stripe
					 * or we have finished all stripes.
					 */
loop:
					physical += map->stripe_len;
					ret = get_raid56_logic_offset(physical,
							num, map, &logical,
							&stripe_logical);
					logical += base;

					अगर (ret && physical < physical_end) अणु
						stripe_logical += base;
						stripe_end = stripe_logical +
								increment;
						ret = scrub_raid56_parity(sctx,
							map, scrub_dev, ppath,
							stripe_logical,
							stripe_end);
						अगर (ret)
							जाओ out;
						जाओ loop;
					पूर्ण
				पूर्ण अन्यथा अणु
					physical += map->stripe_len;
					logical += increment;
				पूर्ण
				अगर (logical < key.objectid + bytes) अणु
					cond_resched();
					जाओ again;
				पूर्ण

				अगर (physical >= physical_end) अणु
					stop_loop = 1;
					अवरोध;
				पूर्ण
			पूर्ण
next:
			path->slots[0]++;
		पूर्ण
		btrfs_release_path(path);
skip:
		logical += increment;
		physical += map->stripe_len;
		spin_lock(&sctx->stat_lock);
		अगर (stop_loop)
			sctx->stat.last_physical = map->stripes[num].physical +
						   length;
		अन्यथा
			sctx->stat.last_physical = physical;
		spin_unlock(&sctx->stat_lock);
		अगर (stop_loop)
			अवरोध;
	पूर्ण
out:
	/* push queued extents */
	scrub_submit(sctx);
	mutex_lock(&sctx->wr_lock);
	scrub_wr_submit(sctx);
	mutex_unlock(&sctx->wr_lock);

	blk_finish_plug(&plug);
	btrfs_मुक्त_path(path);
	btrfs_मुक्त_path(ppath);

	अगर (sctx->is_dev_replace && ret >= 0) अणु
		पूर्णांक ret2;

		ret2 = sync_ग_लिखो_poपूर्णांकer_क्रम_zoned(sctx, base + offset,
						    map->stripes[num].physical,
						    physical_end);
		अगर (ret2)
			ret = ret2;
	पूर्ण

	वापस ret < 0 ? ret : 0;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक scrub_chunk(काष्ठा scrub_ctx *sctx,
					  काष्ठा btrfs_device *scrub_dev,
					  u64 chunk_offset, u64 length,
					  u64 dev_offset,
					  काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	काष्ठा extent_map_tree *map_tree = &fs_info->mapping_tree;
	काष्ठा map_lookup *map;
	काष्ठा extent_map *em;
	पूर्णांक i;
	पूर्णांक ret = 0;

	पढ़ो_lock(&map_tree->lock);
	em = lookup_extent_mapping(map_tree, chunk_offset, 1);
	पढ़ो_unlock(&map_tree->lock);

	अगर (!em) अणु
		/*
		 * Might have been an unused block group deleted by the cleaner
		 * kthपढ़ो or relocation.
		 */
		spin_lock(&cache->lock);
		अगर (!cache->हटाओd)
			ret = -EINVAL;
		spin_unlock(&cache->lock);

		वापस ret;
	पूर्ण

	map = em->map_lookup;
	अगर (em->start != chunk_offset)
		जाओ out;

	अगर (em->len < length)
		जाओ out;

	क्रम (i = 0; i < map->num_stripes; ++i) अणु
		अगर (map->stripes[i].dev->bdev == scrub_dev->bdev &&
		    map->stripes[i].physical == dev_offset) अणु
			ret = scrub_stripe(sctx, map, scrub_dev, i,
					   chunk_offset, length, cache);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण
out:
	मुक्त_extent_map(em);

	वापस ret;
पूर्ण

अटल पूर्णांक finish_extent_ग_लिखोs_क्रम_zoned(काष्ठा btrfs_root *root,
					  काष्ठा btrfs_block_group *cache)
अणु
	काष्ठा btrfs_fs_info *fs_info = cache->fs_info;
	काष्ठा btrfs_trans_handle *trans;

	अगर (!btrfs_is_zoned(fs_info))
		वापस 0;

	btrfs_रुको_block_group_reservations(cache);
	btrfs_रुको_nocow_ग_लिखोrs(cache);
	btrfs_रुको_ordered_roots(fs_info, U64_MAX, cache->start, cache->length);

	trans = btrfs_join_transaction(root);
	अगर (IS_ERR(trans))
		वापस PTR_ERR(trans);
	वापस btrfs_commit_transaction(trans);
पूर्ण

अटल noअंतरभूत_क्रम_stack
पूर्णांक scrub_क्रमागतerate_chunks(काष्ठा scrub_ctx *sctx,
			   काष्ठा btrfs_device *scrub_dev, u64 start, u64 end)
अणु
	काष्ठा btrfs_dev_extent *dev_extent = शून्य;
	काष्ठा btrfs_path *path;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;
	काष्ठा btrfs_root *root = fs_info->dev_root;
	u64 length;
	u64 chunk_offset;
	पूर्णांक ret = 0;
	पूर्णांक ro_set;
	पूर्णांक slot;
	काष्ठा extent_buffer *l;
	काष्ठा btrfs_key key;
	काष्ठा btrfs_key found_key;
	काष्ठा btrfs_block_group *cache;
	काष्ठा btrfs_dev_replace *dev_replace = &fs_info->dev_replace;

	path = btrfs_alloc_path();
	अगर (!path)
		वापस -ENOMEM;

	path->पढ़ोa = READA_FORWARD;
	path->search_commit_root = 1;
	path->skip_locking = 1;

	key.objectid = scrub_dev->devid;
	key.offset = 0ull;
	key.type = BTRFS_DEV_EXTENT_KEY;

	जबतक (1) अणु
		ret = btrfs_search_slot(शून्य, root, &key, path, 0, 0);
		अगर (ret < 0)
			अवरोध;
		अगर (ret > 0) अणु
			अगर (path->slots[0] >=
			    btrfs_header_nritems(path->nodes[0])) अणु
				ret = btrfs_next_leaf(root, path);
				अगर (ret < 0)
					अवरोध;
				अगर (ret > 0) अणु
					ret = 0;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				ret = 0;
			पूर्ण
		पूर्ण

		l = path->nodes[0];
		slot = path->slots[0];

		btrfs_item_key_to_cpu(l, &found_key, slot);

		अगर (found_key.objectid != scrub_dev->devid)
			अवरोध;

		अगर (found_key.type != BTRFS_DEV_EXTENT_KEY)
			अवरोध;

		अगर (found_key.offset >= end)
			अवरोध;

		अगर (found_key.offset < key.offset)
			अवरोध;

		dev_extent = btrfs_item_ptr(l, slot, काष्ठा btrfs_dev_extent);
		length = btrfs_dev_extent_length(l, dev_extent);

		अगर (found_key.offset + length <= start)
			जाओ skip;

		chunk_offset = btrfs_dev_extent_chunk_offset(l, dev_extent);

		/*
		 * get a reference on the corresponding block group to prevent
		 * the chunk from going away जबतक we scrub it
		 */
		cache = btrfs_lookup_block_group(fs_info, chunk_offset);

		/* some chunks are हटाओd but not committed to disk yet,
		 * जारी scrubbing */
		अगर (!cache)
			जाओ skip;

		अगर (sctx->is_dev_replace && btrfs_is_zoned(fs_info)) अणु
			spin_lock(&cache->lock);
			अगर (!cache->to_copy) अणु
				spin_unlock(&cache->lock);
				btrfs_put_block_group(cache);
				जाओ skip;
			पूर्ण
			spin_unlock(&cache->lock);
		पूर्ण

		/*
		 * Make sure that जबतक we are scrubbing the corresponding block
		 * group करोesn't get its logical address and its device extents
		 * reused क्रम another block group, which can possibly be of a
		 * dअगरferent type and dअगरferent profile. We करो this to prevent
		 * false error detections and crashes due to bogus attempts to
		 * repair extents.
		 */
		spin_lock(&cache->lock);
		अगर (cache->हटाओd) अणु
			spin_unlock(&cache->lock);
			btrfs_put_block_group(cache);
			जाओ skip;
		पूर्ण
		btrfs_मुक्तze_block_group(cache);
		spin_unlock(&cache->lock);

		/*
		 * we need call btrfs_inc_block_group_ro() with scrubs_छोड़ोd,
		 * to aव्योम deadlock caused by:
		 * btrfs_inc_block_group_ro()
		 * -> btrfs_रुको_क्रम_commit()
		 * -> btrfs_commit_transaction()
		 * -> btrfs_scrub_छोड़ो()
		 */
		scrub_छोड़ो_on(fs_info);

		/*
		 * Don't करो chunk pपुनः_स्मृतिation क्रम scrub.
		 *
		 * This is especially important क्रम SYSTEM bgs, or we can hit
		 * -EFBIG from btrfs_finish_chunk_alloc() like:
		 * 1. The only SYSTEM bg is marked RO.
		 *    Since SYSTEM bg is small, that's pretty common.
		 * 2. New SYSTEM bg will be allocated
		 *    Due to regular version will allocate new chunk.
		 * 3. New SYSTEM bg is empty and will get cleaned up
		 *    Beक्रमe cleanup really happens, it's marked RO again.
		 * 4. Empty SYSTEM bg get scrubbed
		 *    We go back to 2.
		 *
		 * This can easily boost the amount of SYSTEM chunks अगर cleaner
		 * thपढ़ो can't be triggered fast enough, and use up all space
		 * of btrfs_super_block::sys_chunk_array
		 *
		 * While क्रम dev replace, we need to try our best to mark block
		 * group RO, to prevent race between:
		 * - Write duplication
		 *   Contains latest data
		 * - Scrub copy
		 *   Contains data from commit tree
		 *
		 * If target block group is not marked RO, nocow ग_लिखोs can
		 * be overwritten by scrub copy, causing data corruption.
		 * So क्रम dev-replace, it's not allowed to जारी अगर a block
		 * group is not RO.
		 */
		ret = btrfs_inc_block_group_ro(cache, sctx->is_dev_replace);
		अगर (!ret && sctx->is_dev_replace) अणु
			ret = finish_extent_ग_लिखोs_क्रम_zoned(root, cache);
			अगर (ret) अणु
				btrfs_dec_block_group_ro(cache);
				scrub_छोड़ो_off(fs_info);
				btrfs_put_block_group(cache);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ret == 0) अणु
			ro_set = 1;
		पूर्ण अन्यथा अगर (ret == -ENOSPC && !sctx->is_dev_replace) अणु
			/*
			 * btrfs_inc_block_group_ro वापस -ENOSPC when it
			 * failed in creating new chunk क्रम metadata.
			 * It is not a problem क्रम scrub, because
			 * metadata are always cowed, and our scrub छोड़ोd
			 * commit_transactions.
			 */
			ro_set = 0;
		पूर्ण अन्यथा अगर (ret == -ETXTBSY) अणु
			btrfs_warn(fs_info,
		   "skipping scrub of block group %llu due to active swapfile",
				   cache->start);
			scrub_छोड़ो_off(fs_info);
			ret = 0;
			जाओ skip_unमुक्तze;
		पूर्ण अन्यथा अणु
			btrfs_warn(fs_info,
				   "failed setting block group ro: %d", ret);
			btrfs_unमुक्तze_block_group(cache);
			btrfs_put_block_group(cache);
			scrub_छोड़ो_off(fs_info);
			अवरोध;
		पूर्ण

		/*
		 * Now the target block is marked RO, रुको क्रम nocow ग_लिखोs to
		 * finish beक्रमe dev-replace.
		 * COW is fine, as COW never overग_लिखोs extents in commit tree.
		 */
		अगर (sctx->is_dev_replace) अणु
			btrfs_रुको_nocow_ग_लिखोrs(cache);
			btrfs_रुको_ordered_roots(fs_info, U64_MAX, cache->start,
					cache->length);
		पूर्ण

		scrub_छोड़ो_off(fs_info);
		करोwn_ग_लिखो(&dev_replace->rwsem);
		dev_replace->cursor_right = found_key.offset + length;
		dev_replace->cursor_left = found_key.offset;
		dev_replace->item_needs_ग_लिखोback = 1;
		up_ग_लिखो(&dev_replace->rwsem);

		ret = scrub_chunk(sctx, scrub_dev, chunk_offset, length,
				  found_key.offset, cache);

		/*
		 * flush, submit all pending पढ़ो and ग_लिखो bios, afterwards
		 * रुको क्रम them.
		 * Note that in the dev replace हाल, a पढ़ो request causes
		 * ग_लिखो requests that are submitted in the पढ़ो completion
		 * worker. Thereक्रमe in the current situation, it is required
		 * that all ग_लिखो requests are flushed, so that all पढ़ो and
		 * ग_लिखो requests are really completed when bios_in_flight
		 * changes to 0.
		 */
		sctx->flush_all_ग_लिखोs = true;
		scrub_submit(sctx);
		mutex_lock(&sctx->wr_lock);
		scrub_wr_submit(sctx);
		mutex_unlock(&sctx->wr_lock);

		रुको_event(sctx->list_रुको,
			   atomic_पढ़ो(&sctx->bios_in_flight) == 0);

		scrub_छोड़ो_on(fs_info);

		/*
		 * must be called beक्रमe we decrease @scrub_छोड़ोd.
		 * make sure we करोn't block transaction commit जबतक
		 * we are रुकोing pending workers finished.
		 */
		रुको_event(sctx->list_रुको,
			   atomic_पढ़ो(&sctx->workers_pending) == 0);
		sctx->flush_all_ग_लिखोs = false;

		scrub_छोड़ो_off(fs_info);

		अगर (sctx->is_dev_replace &&
		    !btrfs_finish_block_group_to_copy(dev_replace->srcdev,
						      cache, found_key.offset))
			ro_set = 0;

		करोwn_ग_लिखो(&dev_replace->rwsem);
		dev_replace->cursor_left = dev_replace->cursor_right;
		dev_replace->item_needs_ग_लिखोback = 1;
		up_ग_लिखो(&dev_replace->rwsem);

		अगर (ro_set)
			btrfs_dec_block_group_ro(cache);

		/*
		 * We might have prevented the cleaner kthपढ़ो from deleting
		 * this block group अगर it was alपढ़ोy unused because we raced
		 * and set it to RO mode first. So add it back to the unused
		 * list, otherwise it might not ever be deleted unless a manual
		 * balance is triggered or it becomes used and unused again.
		 */
		spin_lock(&cache->lock);
		अगर (!cache->हटाओd && !cache->ro && cache->reserved == 0 &&
		    cache->used == 0) अणु
			spin_unlock(&cache->lock);
			अगर (btrfs_test_opt(fs_info, DISCARD_ASYNC))
				btrfs_discard_queue_work(&fs_info->discard_ctl,
							 cache);
			अन्यथा
				btrfs_mark_bg_unused(cache);
		पूर्ण अन्यथा अणु
			spin_unlock(&cache->lock);
		पूर्ण
skip_unमुक्तze:
		btrfs_unमुक्तze_block_group(cache);
		btrfs_put_block_group(cache);
		अगर (ret)
			अवरोध;
		अगर (sctx->is_dev_replace &&
		    atomic64_पढ़ो(&dev_replace->num_ग_लिखो_errors) > 0) अणु
			ret = -EIO;
			अवरोध;
		पूर्ण
		अगर (sctx->stat.दो_स्मृति_errors > 0) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
skip:
		key.offset = found_key.offset + length;
		btrfs_release_path(path);
	पूर्ण

	btrfs_मुक्त_path(path);

	वापस ret;
पूर्ण

अटल noअंतरभूत_क्रम_stack पूर्णांक scrub_supers(काष्ठा scrub_ctx *sctx,
					   काष्ठा btrfs_device *scrub_dev)
अणु
	पूर्णांक	i;
	u64	bytenr;
	u64	gen;
	पूर्णांक	ret;
	काष्ठा btrfs_fs_info *fs_info = sctx->fs_info;

	अगर (test_bit(BTRFS_FS_STATE_ERROR, &fs_info->fs_state))
		वापस -EROFS;

	/* Seed devices of a new fileप्रणाली has their own generation. */
	अगर (scrub_dev->fs_devices != fs_info->fs_devices)
		gen = scrub_dev->generation;
	अन्यथा
		gen = fs_info->last_trans_committed;

	क्रम (i = 0; i < BTRFS_SUPER_MIRROR_MAX; i++) अणु
		bytenr = btrfs_sb_offset(i);
		अगर (bytenr + BTRFS_SUPER_INFO_SIZE >
		    scrub_dev->commit_total_bytes)
			अवरोध;
		अगर (!btrfs_check_super_location(scrub_dev, bytenr))
			जारी;

		ret = scrub_pages(sctx, bytenr, BTRFS_SUPER_INFO_SIZE, bytenr,
				  scrub_dev, BTRFS_EXTENT_FLAG_SUPER, gen, i,
				  शून्य, bytenr);
		अगर (ret)
			वापस ret;
	पूर्ण
	रुको_event(sctx->list_रुको, atomic_पढ़ो(&sctx->bios_in_flight) == 0);

	वापस 0;
पूर्ण

अटल व्योम scrub_workers_put(काष्ठा btrfs_fs_info *fs_info)
अणु
	अगर (refcount_dec_and_mutex_lock(&fs_info->scrub_workers_refcnt,
					&fs_info->scrub_lock)) अणु
		काष्ठा btrfs_workqueue *scrub_workers = शून्य;
		काष्ठा btrfs_workqueue *scrub_wr_comp = शून्य;
		काष्ठा btrfs_workqueue *scrub_parity = शून्य;

		scrub_workers = fs_info->scrub_workers;
		scrub_wr_comp = fs_info->scrub_wr_completion_workers;
		scrub_parity = fs_info->scrub_parity_workers;

		fs_info->scrub_workers = शून्य;
		fs_info->scrub_wr_completion_workers = शून्य;
		fs_info->scrub_parity_workers = शून्य;
		mutex_unlock(&fs_info->scrub_lock);

		btrfs_destroy_workqueue(scrub_workers);
		btrfs_destroy_workqueue(scrub_wr_comp);
		btrfs_destroy_workqueue(scrub_parity);
	पूर्ण
पूर्ण

/*
 * get a reference count on fs_info->scrub_workers. start worker अगर necessary
 */
अटल noअंतरभूत_क्रम_stack पूर्णांक scrub_workers_get(काष्ठा btrfs_fs_info *fs_info,
						पूर्णांक is_dev_replace)
अणु
	काष्ठा btrfs_workqueue *scrub_workers = शून्य;
	काष्ठा btrfs_workqueue *scrub_wr_comp = शून्य;
	काष्ठा btrfs_workqueue *scrub_parity = शून्य;
	अचिन्हित पूर्णांक flags = WQ_FREEZABLE | WQ_UNBOUND;
	पूर्णांक max_active = fs_info->thपढ़ो_pool_size;
	पूर्णांक ret = -ENOMEM;

	अगर (refcount_inc_not_zero(&fs_info->scrub_workers_refcnt))
		वापस 0;

	scrub_workers = btrfs_alloc_workqueue(fs_info, "scrub", flags,
					      is_dev_replace ? 1 : max_active, 4);
	अगर (!scrub_workers)
		जाओ fail_scrub_workers;

	scrub_wr_comp = btrfs_alloc_workqueue(fs_info, "scrubwrc", flags,
					      max_active, 2);
	अगर (!scrub_wr_comp)
		जाओ fail_scrub_wr_completion_workers;

	scrub_parity = btrfs_alloc_workqueue(fs_info, "scrubparity", flags,
					     max_active, 2);
	अगर (!scrub_parity)
		जाओ fail_scrub_parity_workers;

	mutex_lock(&fs_info->scrub_lock);
	अगर (refcount_पढ़ो(&fs_info->scrub_workers_refcnt) == 0) अणु
		ASSERT(fs_info->scrub_workers == शून्य &&
		       fs_info->scrub_wr_completion_workers == शून्य &&
		       fs_info->scrub_parity_workers == शून्य);
		fs_info->scrub_workers = scrub_workers;
		fs_info->scrub_wr_completion_workers = scrub_wr_comp;
		fs_info->scrub_parity_workers = scrub_parity;
		refcount_set(&fs_info->scrub_workers_refcnt, 1);
		mutex_unlock(&fs_info->scrub_lock);
		वापस 0;
	पूर्ण
	/* Other thपढ़ो raced in and created the workers क्रम us */
	refcount_inc(&fs_info->scrub_workers_refcnt);
	mutex_unlock(&fs_info->scrub_lock);

	ret = 0;
	btrfs_destroy_workqueue(scrub_parity);
fail_scrub_parity_workers:
	btrfs_destroy_workqueue(scrub_wr_comp);
fail_scrub_wr_completion_workers:
	btrfs_destroy_workqueue(scrub_workers);
fail_scrub_workers:
	वापस ret;
पूर्ण

पूर्णांक btrfs_scrub_dev(काष्ठा btrfs_fs_info *fs_info, u64 devid, u64 start,
		    u64 end, काष्ठा btrfs_scrub_progress *progress,
		    पूर्णांक पढ़ोonly, पूर्णांक is_dev_replace)
अणु
	काष्ठा scrub_ctx *sctx;
	पूर्णांक ret;
	काष्ठा btrfs_device *dev;
	अचिन्हित पूर्णांक nofs_flag;

	अगर (btrfs_fs_closing(fs_info))
		वापस -EAGAIN;

	अगर (fs_info->nodesize > BTRFS_STRIPE_LEN) अणु
		/*
		 * in this हाल scrub is unable to calculate the checksum
		 * the way scrub is implemented. Do not handle this
		 * situation at all because it won't ever happen.
		 */
		btrfs_err(fs_info,
			   "scrub: size assumption nodesize <= BTRFS_STRIPE_LEN (%d <= %d) fails",
		       fs_info->nodesize,
		       BTRFS_STRIPE_LEN);
		वापस -EINVAL;
	पूर्ण

	अगर (fs_info->nodesize >
	    PAGE_SIZE * SCRUB_MAX_PAGES_PER_BLOCK ||
	    fs_info->sectorsize > PAGE_SIZE * SCRUB_MAX_PAGES_PER_BLOCK) अणु
		/*
		 * would exhaust the array bounds of pagev member in
		 * काष्ठा scrub_block
		 */
		btrfs_err(fs_info,
			  "scrub: size assumption nodesize and sectorsize <= SCRUB_MAX_PAGES_PER_BLOCK (%d <= %d && %d <= %d) fails",
		       fs_info->nodesize,
		       SCRUB_MAX_PAGES_PER_BLOCK,
		       fs_info->sectorsize,
		       SCRUB_MAX_PAGES_PER_BLOCK);
		वापस -EINVAL;
	पूर्ण

	/* Allocate outside of device_list_mutex */
	sctx = scrub_setup_ctx(fs_info, is_dev_replace);
	अगर (IS_ERR(sctx))
		वापस PTR_ERR(sctx);

	ret = scrub_workers_get(fs_info, is_dev_replace);
	अगर (ret)
		जाओ out_मुक्त_ctx;

	mutex_lock(&fs_info->fs_devices->device_list_mutex);
	dev = btrfs_find_device(fs_info->fs_devices, devid, शून्य, शून्य);
	अगर (!dev || (test_bit(BTRFS_DEV_STATE_MISSING, &dev->dev_state) &&
		     !is_dev_replace)) अणु
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!is_dev_replace && !पढ़ोonly &&
	    !test_bit(BTRFS_DEV_STATE_WRITEABLE, &dev->dev_state)) अणु
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		btrfs_err_in_rcu(fs_info,
			"scrub on devid %llu: filesystem on %s is not writable",
				 devid, rcu_str_deref(dev->name));
		ret = -EROFS;
		जाओ out;
	पूर्ण

	mutex_lock(&fs_info->scrub_lock);
	अगर (!test_bit(BTRFS_DEV_STATE_IN_FS_METADATA, &dev->dev_state) ||
	    test_bit(BTRFS_DEV_STATE_REPLACE_TGT, &dev->dev_state)) अणु
		mutex_unlock(&fs_info->scrub_lock);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		ret = -EIO;
		जाओ out;
	पूर्ण

	करोwn_पढ़ो(&fs_info->dev_replace.rwsem);
	अगर (dev->scrub_ctx ||
	    (!is_dev_replace &&
	     btrfs_dev_replace_is_ongoing(&fs_info->dev_replace))) अणु
		up_पढ़ो(&fs_info->dev_replace.rwsem);
		mutex_unlock(&fs_info->scrub_lock);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
		ret = -EINPROGRESS;
		जाओ out;
	पूर्ण
	up_पढ़ो(&fs_info->dev_replace.rwsem);

	sctx->पढ़ोonly = पढ़ोonly;
	dev->scrub_ctx = sctx;
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);

	/*
	 * checking @scrub_छोड़ो_req here, we can aव्योम
	 * race between committing transaction and scrubbing.
	 */
	__scrub_blocked_अगर_needed(fs_info);
	atomic_inc(&fs_info->scrubs_running);
	mutex_unlock(&fs_info->scrub_lock);

	/*
	 * In order to aव्योम deadlock with reclaim when there is a transaction
	 * trying to छोड़ो scrub, make sure we use GFP_NOFS क्रम all the
	 * allocations करोne at btrfs_scrub_pages() and scrub_pages_क्रम_parity()
	 * invoked by our callees. The pausing request is करोne when the
	 * transaction commit starts, and it blocks the transaction until scrub
	 * is छोड़ोd (करोne at specअगरic poपूर्णांकs at scrub_stripe() or right above
	 * beक्रमe incrementing fs_info->scrubs_running).
	 */
	nofs_flag = meदो_स्मृति_nofs_save();
	अगर (!is_dev_replace) अणु
		btrfs_info(fs_info, "scrub: started on devid %llu", devid);
		/*
		 * by holding device list mutex, we can
		 * kick off writing super in log tree sync.
		 */
		mutex_lock(&fs_info->fs_devices->device_list_mutex);
		ret = scrub_supers(sctx, dev);
		mutex_unlock(&fs_info->fs_devices->device_list_mutex);
	पूर्ण

	अगर (!ret)
		ret = scrub_क्रमागतerate_chunks(sctx, dev, start, end);
	meदो_स्मृति_nofs_restore(nofs_flag);

	रुको_event(sctx->list_रुको, atomic_पढ़ो(&sctx->bios_in_flight) == 0);
	atomic_dec(&fs_info->scrubs_running);
	wake_up(&fs_info->scrub_छोड़ो_रुको);

	रुको_event(sctx->list_रुको, atomic_पढ़ो(&sctx->workers_pending) == 0);

	अगर (progress)
		स_नकल(progress, &sctx->stat, माप(*progress));

	अगर (!is_dev_replace)
		btrfs_info(fs_info, "scrub: %s on devid %llu with status: %d",
			ret ? "not finished" : "finished", devid, ret);

	mutex_lock(&fs_info->scrub_lock);
	dev->scrub_ctx = शून्य;
	mutex_unlock(&fs_info->scrub_lock);

	scrub_workers_put(fs_info);
	scrub_put_ctx(sctx);

	वापस ret;
out:
	scrub_workers_put(fs_info);
out_मुक्त_ctx:
	scrub_मुक्त_ctx(sctx);

	वापस ret;
पूर्ण

व्योम btrfs_scrub_छोड़ो(काष्ठा btrfs_fs_info *fs_info)
अणु
	mutex_lock(&fs_info->scrub_lock);
	atomic_inc(&fs_info->scrub_छोड़ो_req);
	जबतक (atomic_पढ़ो(&fs_info->scrubs_छोड़ोd) !=
	       atomic_पढ़ो(&fs_info->scrubs_running)) अणु
		mutex_unlock(&fs_info->scrub_lock);
		रुको_event(fs_info->scrub_छोड़ो_रुको,
			   atomic_पढ़ो(&fs_info->scrubs_छोड़ोd) ==
			   atomic_पढ़ो(&fs_info->scrubs_running));
		mutex_lock(&fs_info->scrub_lock);
	पूर्ण
	mutex_unlock(&fs_info->scrub_lock);
पूर्ण

व्योम btrfs_scrub_जारी(काष्ठा btrfs_fs_info *fs_info)
अणु
	atomic_dec(&fs_info->scrub_छोड़ो_req);
	wake_up(&fs_info->scrub_छोड़ो_रुको);
पूर्ण

पूर्णांक btrfs_scrub_cancel(काष्ठा btrfs_fs_info *fs_info)
अणु
	mutex_lock(&fs_info->scrub_lock);
	अगर (!atomic_पढ़ो(&fs_info->scrubs_running)) अणु
		mutex_unlock(&fs_info->scrub_lock);
		वापस -ENOTCONN;
	पूर्ण

	atomic_inc(&fs_info->scrub_cancel_req);
	जबतक (atomic_पढ़ो(&fs_info->scrubs_running)) अणु
		mutex_unlock(&fs_info->scrub_lock);
		रुको_event(fs_info->scrub_छोड़ो_रुको,
			   atomic_पढ़ो(&fs_info->scrubs_running) == 0);
		mutex_lock(&fs_info->scrub_lock);
	पूर्ण
	atomic_dec(&fs_info->scrub_cancel_req);
	mutex_unlock(&fs_info->scrub_lock);

	वापस 0;
पूर्ण

पूर्णांक btrfs_scrub_cancel_dev(काष्ठा btrfs_device *dev)
अणु
	काष्ठा btrfs_fs_info *fs_info = dev->fs_info;
	काष्ठा scrub_ctx *sctx;

	mutex_lock(&fs_info->scrub_lock);
	sctx = dev->scrub_ctx;
	अगर (!sctx) अणु
		mutex_unlock(&fs_info->scrub_lock);
		वापस -ENOTCONN;
	पूर्ण
	atomic_inc(&sctx->cancel_req);
	जबतक (dev->scrub_ctx) अणु
		mutex_unlock(&fs_info->scrub_lock);
		रुको_event(fs_info->scrub_छोड़ो_रुको,
			   dev->scrub_ctx == शून्य);
		mutex_lock(&fs_info->scrub_lock);
	पूर्ण
	mutex_unlock(&fs_info->scrub_lock);

	वापस 0;
पूर्ण

पूर्णांक btrfs_scrub_progress(काष्ठा btrfs_fs_info *fs_info, u64 devid,
			 काष्ठा btrfs_scrub_progress *progress)
अणु
	काष्ठा btrfs_device *dev;
	काष्ठा scrub_ctx *sctx = शून्य;

	mutex_lock(&fs_info->fs_devices->device_list_mutex);
	dev = btrfs_find_device(fs_info->fs_devices, devid, शून्य, शून्य);
	अगर (dev)
		sctx = dev->scrub_ctx;
	अगर (sctx)
		स_नकल(progress, &sctx->stat, माप(*progress));
	mutex_unlock(&fs_info->fs_devices->device_list_mutex);

	वापस dev ? (sctx ? 0 : -ENOTCONN) : -ENODEV;
पूर्ण

अटल व्योम scrub_remap_extent(काष्ठा btrfs_fs_info *fs_info,
			       u64 extent_logical, u32 extent_len,
			       u64 *extent_physical,
			       काष्ठा btrfs_device **extent_dev,
			       पूर्णांक *extent_mirror_num)
अणु
	u64 mapped_length;
	काष्ठा btrfs_bio *bbio = शून्य;
	पूर्णांक ret;

	mapped_length = extent_len;
	ret = btrfs_map_block(fs_info, BTRFS_MAP_READ, extent_logical,
			      &mapped_length, &bbio, 0);
	अगर (ret || !bbio || mapped_length < extent_len ||
	    !bbio->stripes[0].dev->bdev) अणु
		btrfs_put_bbio(bbio);
		वापस;
	पूर्ण

	*extent_physical = bbio->stripes[0].physical;
	*extent_mirror_num = bbio->mirror_num;
	*extent_dev = bbio->stripes[0].dev;
	btrfs_put_bbio(bbio);
पूर्ण
