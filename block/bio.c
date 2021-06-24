<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 Jens Axboe <axboe@kernel.dk>
 */
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/uपन.स>
#समावेश <linux/iocontext.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/mempool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/blk-cgroup.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/blk-crypto.h>
#समावेश <linux/xarray.h>

#समावेश <trace/events/block.h>
#समावेश "blk.h"
#समावेश "blk-rq-qos.h"

अटल काष्ठा biovec_slab अणु
	पूर्णांक nr_vecs;
	अक्षर *name;
	काष्ठा kmem_cache *slab;
पूर्ण bvec_sद_असल[] __पढ़ो_mostly = अणु
	अणु .nr_vecs = 16, .name = "biovec-16" पूर्ण,
	अणु .nr_vecs = 64, .name = "biovec-64" पूर्ण,
	अणु .nr_vecs = 128, .name = "biovec-128" पूर्ण,
	अणु .nr_vecs = BIO_MAX_VECS, .name = "biovec-max" पूर्ण,
पूर्ण;

अटल काष्ठा biovec_slab *biovec_slab(अचिन्हित लघु nr_vecs)
अणु
	चयन (nr_vecs) अणु
	/* smaller bios use अंतरभूत vecs */
	हाल 5 ... 16:
		वापस &bvec_sद_असल[0];
	हाल 17 ... 64:
		वापस &bvec_sद_असल[1];
	हाल 65 ... 128:
		वापस &bvec_sद_असल[2];
	हाल 129 ... BIO_MAX_VECS:
		वापस &bvec_sद_असल[3];
	शेष:
		BUG();
		वापस शून्य;
	पूर्ण
पूर्ण

/*
 * fs_bio_set is the bio_set containing bio and iovec memory pools used by
 * IO code that करोes not need निजी memory pools.
 */
काष्ठा bio_set fs_bio_set;
EXPORT_SYMBOL(fs_bio_set);

/*
 * Our slab pool management
 */
काष्ठा bio_slab अणु
	काष्ठा kmem_cache *slab;
	अचिन्हित पूर्णांक slab_ref;
	अचिन्हित पूर्णांक slab_size;
	अक्षर name[8];
पूर्ण;
अटल DEFINE_MUTEX(bio_slab_lock);
अटल DEFINE_XARRAY(bio_sद_असल);

अटल काष्ठा bio_slab *create_bio_slab(अचिन्हित पूर्णांक size)
अणु
	काष्ठा bio_slab *bslab = kzalloc(माप(*bslab), GFP_KERNEL);

	अगर (!bslab)
		वापस शून्य;

	snम_लिखो(bslab->name, माप(bslab->name), "bio-%d", size);
	bslab->slab = kmem_cache_create(bslab->name, size,
			ARCH_KMALLOC_MINALIGN, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!bslab->slab)
		जाओ fail_alloc_slab;

	bslab->slab_ref = 1;
	bslab->slab_size = size;

	अगर (!xa_err(xa_store(&bio_sद_असल, size, bslab, GFP_KERNEL)))
		वापस bslab;

	kmem_cache_destroy(bslab->slab);

fail_alloc_slab:
	kमुक्त(bslab);
	वापस शून्य;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bs_bio_slab_size(काष्ठा bio_set *bs)
अणु
	वापस bs->front_pad + माप(काष्ठा bio) + bs->back_pad;
पूर्ण

अटल काष्ठा kmem_cache *bio_find_or_create_slab(काष्ठा bio_set *bs)
अणु
	अचिन्हित पूर्णांक size = bs_bio_slab_size(bs);
	काष्ठा bio_slab *bslab;

	mutex_lock(&bio_slab_lock);
	bslab = xa_load(&bio_sद_असल, size);
	अगर (bslab)
		bslab->slab_ref++;
	अन्यथा
		bslab = create_bio_slab(size);
	mutex_unlock(&bio_slab_lock);

	अगर (bslab)
		वापस bslab->slab;
	वापस शून्य;
पूर्ण

अटल व्योम bio_put_slab(काष्ठा bio_set *bs)
अणु
	काष्ठा bio_slab *bslab = शून्य;
	अचिन्हित पूर्णांक slab_size = bs_bio_slab_size(bs);

	mutex_lock(&bio_slab_lock);

	bslab = xa_load(&bio_sद_असल, slab_size);
	अगर (WARN(!bslab, KERN_ERR "bio: unable to find slab!\n"))
		जाओ out;

	WARN_ON_ONCE(bslab->slab != bs->bio_slab);

	WARN_ON(!bslab->slab_ref);

	अगर (--bslab->slab_ref)
		जाओ out;

	xa_erase(&bio_sद_असल, slab_size);

	kmem_cache_destroy(bslab->slab);
	kमुक्त(bslab);

out:
	mutex_unlock(&bio_slab_lock);
पूर्ण

व्योम bvec_मुक्त(mempool_t *pool, काष्ठा bio_vec *bv, अचिन्हित लघु nr_vecs)
अणु
	BIO_BUG_ON(nr_vecs > BIO_MAX_VECS);

	अगर (nr_vecs == BIO_MAX_VECS)
		mempool_मुक्त(bv, pool);
	अन्यथा अगर (nr_vecs > BIO_INLINE_VECS)
		kmem_cache_मुक्त(biovec_slab(nr_vecs)->slab, bv);
पूर्ण

/*
 * Make the first allocation restricted and करोn't dump info on allocation
 * failures, since we'll fall back to the mempool in हाल of failure.
 */
अटल अंतरभूत gfp_t bvec_alloc_gfp(gfp_t gfp)
अणु
	वापस (gfp & ~(__GFP_सूचीECT_RECLAIM | __GFP_IO)) |
		__GFP_NOMEMALLOC | __GFP_NORETRY | __GFP_NOWARN;
पूर्ण

काष्ठा bio_vec *bvec_alloc(mempool_t *pool, अचिन्हित लघु *nr_vecs,
		gfp_t gfp_mask)
अणु
	काष्ठा biovec_slab *bvs = biovec_slab(*nr_vecs);

	अगर (WARN_ON_ONCE(!bvs))
		वापस शून्य;

	/*
	 * Upgrade the nr_vecs request to take full advantage of the allocation.
	 * We also rely on this in the bvec_मुक्त path.
	 */
	*nr_vecs = bvs->nr_vecs;

	/*
	 * Try a slab allocation first क्रम all smaller allocations.  If that
	 * fails and __GFP_सूचीECT_RECLAIM is set retry with the mempool.
	 * The mempool is sized to handle up to BIO_MAX_VECS entries.
	 */
	अगर (*nr_vecs < BIO_MAX_VECS) अणु
		काष्ठा bio_vec *bvl;

		bvl = kmem_cache_alloc(bvs->slab, bvec_alloc_gfp(gfp_mask));
		अगर (likely(bvl) || !(gfp_mask & __GFP_सूचीECT_RECLAIM))
			वापस bvl;
		*nr_vecs = BIO_MAX_VECS;
	पूर्ण

	वापस mempool_alloc(pool, gfp_mask);
पूर्ण

व्योम bio_uninit(काष्ठा bio *bio)
अणु
#अगर_घोषित CONFIG_BLK_CGROUP
	अगर (bio->bi_blkg) अणु
		blkg_put(bio->bi_blkg);
		bio->bi_blkg = शून्य;
	पूर्ण
#पूर्ण_अगर
	अगर (bio_पूर्णांकegrity(bio))
		bio_पूर्णांकegrity_मुक्त(bio);

	bio_crypt_मुक्त_ctx(bio);
पूर्ण
EXPORT_SYMBOL(bio_uninit);

अटल व्योम bio_मुक्त(काष्ठा bio *bio)
अणु
	काष्ठा bio_set *bs = bio->bi_pool;
	व्योम *p;

	bio_uninit(bio);

	अगर (bs) अणु
		bvec_मुक्त(&bs->bvec_pool, bio->bi_io_vec, bio->bi_max_vecs);

		/*
		 * If we have front padding, adjust the bio poपूर्णांकer beक्रमe मुक्तing
		 */
		p = bio;
		p -= bs->front_pad;

		mempool_मुक्त(p, &bs->bio_pool);
	पूर्ण अन्यथा अणु
		/* Bio was allocated by bio_kदो_स्मृति() */
		kमुक्त(bio);
	पूर्ण
पूर्ण

/*
 * Users of this function have their own bio allocation. Subsequently,
 * they must remember to pair any call to bio_init() with bio_uninit()
 * when IO has completed, or when the bio is released.
 */
व्योम bio_init(काष्ठा bio *bio, काष्ठा bio_vec *table,
	      अचिन्हित लघु max_vecs)
अणु
	स_रखो(bio, 0, माप(*bio));
	atomic_set(&bio->__bi_reमुख्यing, 1);
	atomic_set(&bio->__bi_cnt, 1);

	bio->bi_io_vec = table;
	bio->bi_max_vecs = max_vecs;
पूर्ण
EXPORT_SYMBOL(bio_init);

/**
 * bio_reset - reinitialize a bio
 * @bio:	bio to reset
 *
 * Description:
 *   After calling bio_reset(), @bio will be in the same state as a freshly
 *   allocated bio वापसed bio bio_alloc_bioset() - the only fields that are
 *   preserved are the ones that are initialized by bio_alloc_bioset(). See
 *   comment in काष्ठा bio.
 */
व्योम bio_reset(काष्ठा bio *bio)
अणु
	bio_uninit(bio);
	स_रखो(bio, 0, BIO_RESET_BYTES);
	atomic_set(&bio->__bi_reमुख्यing, 1);
पूर्ण
EXPORT_SYMBOL(bio_reset);

अटल काष्ठा bio *__bio_chain_endio(काष्ठा bio *bio)
अणु
	काष्ठा bio *parent = bio->bi_निजी;

	अगर (bio->bi_status && !parent->bi_status)
		parent->bi_status = bio->bi_status;
	bio_put(bio);
	वापस parent;
पूर्ण

अटल व्योम bio_chain_endio(काष्ठा bio *bio)
अणु
	bio_endio(__bio_chain_endio(bio));
पूर्ण

/**
 * bio_chain - chain bio completions
 * @bio: the target bio
 * @parent: the parent bio of @bio
 *
 * The caller won't have a bi_end_io called when @bio completes - instead,
 * @parent's bi_end_io won't be called until both @parent and @bio have
 * completed; the chained bio will also be मुक्तd when it completes.
 *
 * The caller must not set bi_निजी or bi_end_io in @bio.
 */
व्योम bio_chain(काष्ठा bio *bio, काष्ठा bio *parent)
अणु
	BUG_ON(bio->bi_निजी || bio->bi_end_io);

	bio->bi_निजी = parent;
	bio->bi_end_io	= bio_chain_endio;
	bio_inc_reमुख्यing(parent);
पूर्ण
EXPORT_SYMBOL(bio_chain);

अटल व्योम bio_alloc_rescue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bio_set *bs = container_of(work, काष्ठा bio_set, rescue_work);
	काष्ठा bio *bio;

	जबतक (1) अणु
		spin_lock(&bs->rescue_lock);
		bio = bio_list_pop(&bs->rescue_list);
		spin_unlock(&bs->rescue_lock);

		अगर (!bio)
			अवरोध;

		submit_bio_noacct(bio);
	पूर्ण
पूर्ण

अटल व्योम punt_bios_to_rescuer(काष्ठा bio_set *bs)
अणु
	काष्ठा bio_list punt, nopunt;
	काष्ठा bio *bio;

	अगर (WARN_ON_ONCE(!bs->rescue_workqueue))
		वापस;
	/*
	 * In order to guarantee क्रमward progress we must punt only bios that
	 * were allocated from this bio_set; otherwise, अगर there was a bio on
	 * there क्रम a stacking driver higher up in the stack, processing it
	 * could require allocating bios from this bio_set, and करोing that from
	 * our own rescuer would be bad.
	 *
	 * Since bio lists are singly linked, pop them all instead of trying to
	 * हटाओ from the middle of the list:
	 */

	bio_list_init(&punt);
	bio_list_init(&nopunt);

	जबतक ((bio = bio_list_pop(&current->bio_list[0])))
		bio_list_add(bio->bi_pool == bs ? &punt : &nopunt, bio);
	current->bio_list[0] = nopunt;

	bio_list_init(&nopunt);
	जबतक ((bio = bio_list_pop(&current->bio_list[1])))
		bio_list_add(bio->bi_pool == bs ? &punt : &nopunt, bio);
	current->bio_list[1] = nopunt;

	spin_lock(&bs->rescue_lock);
	bio_list_merge(&bs->rescue_list, &punt);
	spin_unlock(&bs->rescue_lock);

	queue_work(bs->rescue_workqueue, &bs->rescue_work);
पूर्ण

/**
 * bio_alloc_bioset - allocate a bio क्रम I/O
 * @gfp_mask:   the GFP_* mask given to the slab allocator
 * @nr_iovecs:	number of iovecs to pre-allocate
 * @bs:		the bio_set to allocate from.
 *
 * Allocate a bio from the mempools in @bs.
 *
 * If %__GFP_सूचीECT_RECLAIM is set then bio_alloc will always be able to
 * allocate a bio.  This is due to the mempool guarantees.  To make this work,
 * callers must never allocate more than 1 bio at a समय from the general pool.
 * Callers that need to allocate more than 1 bio must always submit the
 * previously allocated bio क्रम IO beक्रमe attempting to allocate a new one.
 * Failure to करो so can cause deadlocks under memory pressure.
 *
 * Note that when running under submit_bio_noacct() (i.e. any block driver),
 * bios are not submitted until after you वापस - see the code in
 * submit_bio_noacct() that converts recursion पूर्णांकo iteration, to prevent
 * stack overflows.
 *
 * This would normally mean allocating multiple bios under submit_bio_noacct()
 * would be susceptible to deadlocks, but we have
 * deadlock aव्योमance code that resubmits any blocked bios from a rescuer
 * thपढ़ो.
 *
 * However, we करो not guarantee क्रमward progress क्रम allocations from other
 * mempools. Doing multiple allocations from the same mempool under
 * submit_bio_noacct() should be aव्योमed - instead, use bio_set's front_pad
 * क्रम per bio allocations.
 *
 * Returns: Poपूर्णांकer to new bio on success, शून्य on failure.
 */
काष्ठा bio *bio_alloc_bioset(gfp_t gfp_mask, अचिन्हित लघु nr_iovecs,
			     काष्ठा bio_set *bs)
अणु
	gfp_t saved_gfp = gfp_mask;
	काष्ठा bio *bio;
	व्योम *p;

	/* should not use nobvec bioset क्रम nr_iovecs > 0 */
	अगर (WARN_ON_ONCE(!mempool_initialized(&bs->bvec_pool) && nr_iovecs > 0))
		वापस शून्य;

	/*
	 * submit_bio_noacct() converts recursion to iteration; this means अगर
	 * we're running beneath it, any bios we allocate and submit will not be
	 * submitted (and thus मुक्तd) until after we वापस.
	 *
	 * This exposes us to a potential deadlock अगर we allocate multiple bios
	 * from the same bio_set() जबतक running underneath submit_bio_noacct().
	 * If we were to allocate multiple bios (say a stacking block driver
	 * that was splitting bios), we would deadlock अगर we exhausted the
	 * mempool's reserve.
	 *
	 * We solve this, and guarantee क्रमward progress, with a rescuer
	 * workqueue per bio_set. If we go to allocate and there are bios on
	 * current->bio_list, we first try the allocation without
	 * __GFP_सूचीECT_RECLAIM; अगर that fails, we punt those bios we would be
	 * blocking to the rescuer workqueue beक्रमe we retry with the original
	 * gfp_flags.
	 */
	अगर (current->bio_list &&
	    (!bio_list_empty(&current->bio_list[0]) ||
	     !bio_list_empty(&current->bio_list[1])) &&
	    bs->rescue_workqueue)
		gfp_mask &= ~__GFP_सूचीECT_RECLAIM;

	p = mempool_alloc(&bs->bio_pool, gfp_mask);
	अगर (!p && gfp_mask != saved_gfp) अणु
		punt_bios_to_rescuer(bs);
		gfp_mask = saved_gfp;
		p = mempool_alloc(&bs->bio_pool, gfp_mask);
	पूर्ण
	अगर (unlikely(!p))
		वापस शून्य;

	bio = p + bs->front_pad;
	अगर (nr_iovecs > BIO_INLINE_VECS) अणु
		काष्ठा bio_vec *bvl = शून्य;

		bvl = bvec_alloc(&bs->bvec_pool, &nr_iovecs, gfp_mask);
		अगर (!bvl && gfp_mask != saved_gfp) अणु
			punt_bios_to_rescuer(bs);
			gfp_mask = saved_gfp;
			bvl = bvec_alloc(&bs->bvec_pool, &nr_iovecs, gfp_mask);
		पूर्ण
		अगर (unlikely(!bvl))
			जाओ err_मुक्त;

		bio_init(bio, bvl, nr_iovecs);
	पूर्ण अन्यथा अगर (nr_iovecs) अणु
		bio_init(bio, bio->bi_अंतरभूत_vecs, BIO_INLINE_VECS);
	पूर्ण अन्यथा अणु
		bio_init(bio, शून्य, 0);
	पूर्ण

	bio->bi_pool = bs;
	वापस bio;

err_मुक्त:
	mempool_मुक्त(p, &bs->bio_pool);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(bio_alloc_bioset);

/**
 * bio_kदो_स्मृति - kदो_स्मृति a bio क्रम I/O
 * @gfp_mask:   the GFP_* mask given to the slab allocator
 * @nr_iovecs:	number of iovecs to pre-allocate
 *
 * Use kदो_स्मृति to allocate and initialize a bio.
 *
 * Returns: Poपूर्णांकer to new bio on success, शून्य on failure.
 */
काष्ठा bio *bio_kदो_स्मृति(gfp_t gfp_mask, अचिन्हित लघु nr_iovecs)
अणु
	काष्ठा bio *bio;

	अगर (nr_iovecs > UIO_MAXIOV)
		वापस शून्य;

	bio = kदो_स्मृति(काष्ठा_size(bio, bi_अंतरभूत_vecs, nr_iovecs), gfp_mask);
	अगर (unlikely(!bio))
		वापस शून्य;
	bio_init(bio, nr_iovecs ? bio->bi_अंतरभूत_vecs : शून्य, nr_iovecs);
	bio->bi_pool = शून्य;
	वापस bio;
पूर्ण
EXPORT_SYMBOL(bio_kदो_स्मृति);

व्योम zero_fill_bio(काष्ठा bio *bio)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा bio_vec bv;
	काष्ठा bvec_iter iter;

	bio_क्रम_each_segment(bv, bio, iter) अणु
		अक्षर *data = bvec_kmap_irq(&bv, &flags);
		स_रखो(data, 0, bv.bv_len);
		flush_dcache_page(bv.bv_page);
		bvec_kunmap_irq(data, &flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(zero_fill_bio);

/**
 * bio_truncate - truncate the bio to small size of @new_size
 * @bio:	the bio to be truncated
 * @new_size:	new size क्रम truncating the bio
 *
 * Description:
 *   Truncate the bio to new size of @new_size. If bio_op(bio) is
 *   REQ_OP_READ, zero the truncated part. This function should only
 *   be used क्रम handling corner हालs, such as bio eod.
 */
व्योम bio_truncate(काष्ठा bio *bio, अचिन्हित new_size)
अणु
	काष्ठा bio_vec bv;
	काष्ठा bvec_iter iter;
	अचिन्हित पूर्णांक करोne = 0;
	bool truncated = false;

	अगर (new_size >= bio->bi_iter.bi_size)
		वापस;

	अगर (bio_op(bio) != REQ_OP_READ)
		जाओ निकास;

	bio_क्रम_each_segment(bv, bio, iter) अणु
		अगर (करोne + bv.bv_len > new_size) अणु
			अचिन्हित offset;

			अगर (!truncated)
				offset = new_size - करोne;
			अन्यथा
				offset = 0;
			zero_user(bv.bv_page, offset, bv.bv_len - offset);
			truncated = true;
		पूर्ण
		करोne += bv.bv_len;
	पूर्ण

 निकास:
	/*
	 * Don't touch bvec table here and make it really immutable, since
	 * fs bio user has to retrieve all pages via bio_क्रम_each_segment_all
	 * in its .end_bio() callback.
	 *
	 * It is enough to truncate bio by updating .bi_size since we can make
	 * correct bvec with the updated .bi_size क्रम drivers.
	 */
	bio->bi_iter.bi_size = new_size;
पूर्ण

/**
 * guard_bio_eod - truncate a BIO to fit the block device
 * @bio:	bio to truncate
 *
 * This allows us to करो IO even on the odd last sectors of a device, even अगर the
 * block size is some multiple of the physical sector size.
 *
 * We'll just truncate the bio to the size of the device, and clear the end of
 * the buffer head manually.  Truly out-of-range accesses will turn पूर्णांकo actual
 * I/O errors, this only handles the "we need to be able to करो I/O at the final
 * sector" हाल.
 */
व्योम guard_bio_eod(काष्ठा bio *bio)
अणु
	sector_t maxsector = bdev_nr_sectors(bio->bi_bdev);

	अगर (!maxsector)
		वापस;

	/*
	 * If the *whole* IO is past the end of the device,
	 * let it through, and the IO layer will turn it पूर्णांकo
	 * an EIO.
	 */
	अगर (unlikely(bio->bi_iter.bi_sector >= maxsector))
		वापस;

	maxsector -= bio->bi_iter.bi_sector;
	अगर (likely((bio->bi_iter.bi_size >> 9) <= maxsector))
		वापस;

	bio_truncate(bio, maxsector << 9);
पूर्ण

/**
 * bio_put - release a reference to a bio
 * @bio:   bio to release reference to
 *
 * Description:
 *   Put a reference to a &काष्ठा bio, either one you have gotten with
 *   bio_alloc, bio_get or bio_clone_*. The last put of a bio will मुक्त it.
 **/
व्योम bio_put(काष्ठा bio *bio)
अणु
	अगर (!bio_flagged(bio, BIO_REFFED))
		bio_मुक्त(bio);
	अन्यथा अणु
		BIO_BUG_ON(!atomic_पढ़ो(&bio->__bi_cnt));

		/*
		 * last put मुक्तs it
		 */
		अगर (atomic_dec_and_test(&bio->__bi_cnt))
			bio_मुक्त(bio);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(bio_put);

/**
 * 	__bio_clone_fast - clone a bio that shares the original bio's biovec
 * 	@bio: destination bio
 * 	@bio_src: bio to clone
 *
 *	Clone a &bio. Caller will own the वापसed bio, but not
 *	the actual data it poपूर्णांकs to. Reference count of वापसed
 * 	bio will be one.
 *
 * 	Caller must ensure that @bio_src is not मुक्तd beक्रमe @bio.
 */
व्योम __bio_clone_fast(काष्ठा bio *bio, काष्ठा bio *bio_src)
अणु
	WARN_ON_ONCE(bio->bi_pool && bio->bi_max_vecs);

	/*
	 * most users will be overriding ->bi_bdev with a new target,
	 * so we करोn't set nor calculate new physical/hw segment counts here
	 */
	bio->bi_bdev = bio_src->bi_bdev;
	bio_set_flag(bio, BIO_CLONED);
	अगर (bio_flagged(bio_src, BIO_THROTTLED))
		bio_set_flag(bio, BIO_THROTTLED);
	अगर (bio_flagged(bio_src, BIO_REMAPPED))
		bio_set_flag(bio, BIO_REMAPPED);
	bio->bi_opf = bio_src->bi_opf;
	bio->bi_ioprio = bio_src->bi_ioprio;
	bio->bi_ग_लिखो_hपूर्णांक = bio_src->bi_ग_लिखो_hपूर्णांक;
	bio->bi_iter = bio_src->bi_iter;
	bio->bi_io_vec = bio_src->bi_io_vec;

	bio_clone_blkg_association(bio, bio_src);
	blkcg_bio_issue_init(bio);
पूर्ण
EXPORT_SYMBOL(__bio_clone_fast);

/**
 *	bio_clone_fast - clone a bio that shares the original bio's biovec
 *	@bio: bio to clone
 *	@gfp_mask: allocation priority
 *	@bs: bio_set to allocate from
 *
 * 	Like __bio_clone_fast, only also allocates the वापसed bio
 */
काष्ठा bio *bio_clone_fast(काष्ठा bio *bio, gfp_t gfp_mask, काष्ठा bio_set *bs)
अणु
	काष्ठा bio *b;

	b = bio_alloc_bioset(gfp_mask, 0, bs);
	अगर (!b)
		वापस शून्य;

	__bio_clone_fast(b, bio);

	अगर (bio_crypt_clone(b, bio, gfp_mask) < 0)
		जाओ err_put;

	अगर (bio_पूर्णांकegrity(bio) &&
	    bio_पूर्णांकegrity_clone(b, bio, gfp_mask) < 0)
		जाओ err_put;

	वापस b;

err_put:
	bio_put(b);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(bio_clone_fast);

स्थिर अक्षर *bio_devname(काष्ठा bio *bio, अक्षर *buf)
अणु
	वापस bdevname(bio->bi_bdev, buf);
पूर्ण
EXPORT_SYMBOL(bio_devname);

अटल अंतरभूत bool page_is_mergeable(स्थिर काष्ठा bio_vec *bv,
		काष्ठा page *page, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off,
		bool *same_page)
अणु
	माप_प्रकार bv_end = bv->bv_offset + bv->bv_len;
	phys_addr_t vec_end_addr = page_to_phys(bv->bv_page) + bv_end - 1;
	phys_addr_t page_addr = page_to_phys(page);

	अगर (vec_end_addr + 1 != page_addr + off)
		वापस false;
	अगर (xen_करोमुख्य() && !xen_biovec_phys_mergeable(bv, page))
		वापस false;

	*same_page = ((vec_end_addr & PAGE_MASK) == page_addr);
	अगर (*same_page)
		वापस true;
	वापस (bv->bv_page + bv_end / PAGE_SIZE) == (page + off / PAGE_SIZE);
पूर्ण

/*
 * Try to merge a page पूर्णांकo a segment, जबतक obeying the hardware segment
 * size limit.  This is not क्रम normal पढ़ो/ग_लिखो bios, but क्रम passthrough
 * or Zone Append operations that we can't split.
 */
अटल bool bio_try_merge_hw_seg(काष्ठा request_queue *q, काष्ठा bio *bio,
				 काष्ठा page *page, अचिन्हित len,
				 अचिन्हित offset, bool *same_page)
अणु
	काष्ठा bio_vec *bv = &bio->bi_io_vec[bio->bi_vcnt - 1];
	अचिन्हित दीर्घ mask = queue_segment_boundary(q);
	phys_addr_t addr1 = page_to_phys(bv->bv_page) + bv->bv_offset;
	phys_addr_t addr2 = page_to_phys(page) + offset + len - 1;

	अगर ((addr1 | mask) != (addr2 | mask))
		वापस false;
	अगर (bv->bv_len + len > queue_max_segment_size(q))
		वापस false;
	वापस __bio_try_merge_page(bio, page, len, offset, same_page);
पूर्ण

/**
 * bio_add_hw_page - attempt to add a page to a bio with hw स्थिरraपूर्णांकs
 * @q: the target queue
 * @bio: destination bio
 * @page: page to add
 * @len: vec entry length
 * @offset: vec entry offset
 * @max_sectors: maximum number of sectors that can be added
 * @same_page: वापस अगर the segment has been merged inside the same page
 *
 * Add a page to a bio जबतक respecting the hardware max_sectors, max_segment
 * and gap limitations.
 */
पूर्णांक bio_add_hw_page(काष्ठा request_queue *q, काष्ठा bio *bio,
		काष्ठा page *page, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक max_sectors, bool *same_page)
अणु
	काष्ठा bio_vec *bvec;

	अगर (WARN_ON_ONCE(bio_flagged(bio, BIO_CLONED)))
		वापस 0;

	अगर (((bio->bi_iter.bi_size + len) >> 9) > max_sectors)
		वापस 0;

	अगर (bio->bi_vcnt > 0) अणु
		अगर (bio_try_merge_hw_seg(q, bio, page, len, offset, same_page))
			वापस len;

		/*
		 * If the queue करोesn't support SG gaps and adding this segment
		 * would create a gap, disallow it.
		 */
		bvec = &bio->bi_io_vec[bio->bi_vcnt - 1];
		अगर (bvec_gap_to_prev(q, bvec, offset))
			वापस 0;
	पूर्ण

	अगर (bio_full(bio, len))
		वापस 0;

	अगर (bio->bi_vcnt >= queue_max_segments(q))
		वापस 0;

	bvec = &bio->bi_io_vec[bio->bi_vcnt];
	bvec->bv_page = page;
	bvec->bv_len = len;
	bvec->bv_offset = offset;
	bio->bi_vcnt++;
	bio->bi_iter.bi_size += len;
	वापस len;
पूर्ण

/**
 * bio_add_pc_page	- attempt to add page to passthrough bio
 * @q: the target queue
 * @bio: destination bio
 * @page: page to add
 * @len: vec entry length
 * @offset: vec entry offset
 *
 * Attempt to add a page to the bio_vec maplist. This can fail क्रम a
 * number of reasons, such as the bio being full or target block device
 * limitations. The target block device must allow bio's up to PAGE_SIZE,
 * so it is always possible to add a single page to an empty bio.
 *
 * This should only be used by passthrough bios.
 */
पूर्णांक bio_add_pc_page(काष्ठा request_queue *q, काष्ठा bio *bio,
		काष्ठा page *page, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset)
अणु
	bool same_page = false;
	वापस bio_add_hw_page(q, bio, page, len, offset,
			queue_max_hw_sectors(q), &same_page);
पूर्ण
EXPORT_SYMBOL(bio_add_pc_page);

/**
 * bio_add_zone_append_page - attempt to add page to zone-append bio
 * @bio: destination bio
 * @page: page to add
 * @len: vec entry length
 * @offset: vec entry offset
 *
 * Attempt to add a page to the bio_vec maplist of a bio that will be submitted
 * क्रम a zone-append request. This can fail क्रम a number of reasons, such as the
 * bio being full or the target block device is not a zoned block device or
 * other limitations of the target block device. The target block device must
 * allow bio's up to PAGE_SIZE, so it is always possible to add a single page
 * to an empty bio.
 *
 * Returns: number of bytes added to the bio, or 0 in हाल of a failure.
 */
पूर्णांक bio_add_zone_append_page(काष्ठा bio *bio, काष्ठा page *page,
			     अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;
	bool same_page = false;

	अगर (WARN_ON_ONCE(bio_op(bio) != REQ_OP_ZONE_APPEND))
		वापस 0;

	अगर (WARN_ON_ONCE(!blk_queue_is_zoned(q)))
		वापस 0;

	वापस bio_add_hw_page(q, bio, page, len, offset,
			       queue_max_zone_append_sectors(q), &same_page);
पूर्ण
EXPORT_SYMBOL_GPL(bio_add_zone_append_page);

/**
 * __bio_try_merge_page - try appending data to an existing bvec.
 * @bio: destination bio
 * @page: start page to add
 * @len: length of the data to add
 * @off: offset of the data relative to @page
 * @same_page: वापस अगर the segment has been merged inside the same page
 *
 * Try to add the data at @page + @off to the last bvec of @bio.  This is a
 * useful optimisation क्रम file प्रणालीs with a block size smaller than the
 * page size.
 *
 * Warn अगर (@len, @off) crosses pages in हाल that @same_page is true.
 *
 * Return %true on success or %false on failure.
 */
bool __bio_try_merge_page(काष्ठा bio *bio, काष्ठा page *page,
		अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off, bool *same_page)
अणु
	अगर (WARN_ON_ONCE(bio_flagged(bio, BIO_CLONED)))
		वापस false;

	अगर (bio->bi_vcnt > 0) अणु
		काष्ठा bio_vec *bv = &bio->bi_io_vec[bio->bi_vcnt - 1];

		अगर (page_is_mergeable(bv, page, len, off, same_page)) अणु
			अगर (bio->bi_iter.bi_size > अच_पूर्णांक_उच्च - len) अणु
				*same_page = false;
				वापस false;
			पूर्ण
			bv->bv_len += len;
			bio->bi_iter.bi_size += len;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(__bio_try_merge_page);

/**
 * __bio_add_page - add page(s) to a bio in a new segment
 * @bio: destination bio
 * @page: start page to add
 * @len: length of the data to add, may cross pages
 * @off: offset of the data relative to @page, may cross pages
 *
 * Add the data at @page + @off to @bio as a new bvec.  The caller must ensure
 * that @bio has space क्रम another bvec.
 */
व्योम __bio_add_page(काष्ठा bio *bio, काष्ठा page *page,
		अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off)
अणु
	काष्ठा bio_vec *bv = &bio->bi_io_vec[bio->bi_vcnt];

	WARN_ON_ONCE(bio_flagged(bio, BIO_CLONED));
	WARN_ON_ONCE(bio_full(bio, len));

	bv->bv_page = page;
	bv->bv_offset = off;
	bv->bv_len = len;

	bio->bi_iter.bi_size += len;
	bio->bi_vcnt++;

	अगर (!bio_flagged(bio, BIO_WORKINGSET) && unlikely(PageWorkingset(page)))
		bio_set_flag(bio, BIO_WORKINGSET);
पूर्ण
EXPORT_SYMBOL_GPL(__bio_add_page);

/**
 *	bio_add_page	-	attempt to add page(s) to bio
 *	@bio: destination bio
 *	@page: start page to add
 *	@len: vec entry length, may cross pages
 *	@offset: vec entry offset relative to @page, may cross pages
 *
 *	Attempt to add page(s) to the bio_vec maplist. This will only fail
 *	अगर either bio->bi_vcnt == bio->bi_max_vecs or it's a cloned bio.
 */
पूर्णांक bio_add_page(काष्ठा bio *bio, काष्ठा page *page,
		 अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset)
अणु
	bool same_page = false;

	अगर (!__bio_try_merge_page(bio, page, len, offset, &same_page)) अणु
		अगर (bio_full(bio, len))
			वापस 0;
		__bio_add_page(bio, page, len, offset);
	पूर्ण
	वापस len;
पूर्ण
EXPORT_SYMBOL(bio_add_page);

व्योम bio_release_pages(काष्ठा bio *bio, bool mark_dirty)
अणु
	काष्ठा bvec_iter_all iter_all;
	काष्ठा bio_vec *bvec;

	अगर (bio_flagged(bio, BIO_NO_PAGE_REF))
		वापस;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		अगर (mark_dirty && !PageCompound(bvec->bv_page))
			set_page_dirty_lock(bvec->bv_page);
		put_page(bvec->bv_page);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bio_release_pages);

अटल व्योम __bio_iov_bvec_set(काष्ठा bio *bio, काष्ठा iov_iter *iter)
अणु
	WARN_ON_ONCE(bio->bi_max_vecs);

	bio->bi_vcnt = iter->nr_segs;
	bio->bi_io_vec = (काष्ठा bio_vec *)iter->bvec;
	bio->bi_iter.bi_bvec_करोne = iter->iov_offset;
	bio->bi_iter.bi_size = iter->count;
	bio_set_flag(bio, BIO_NO_PAGE_REF);
	bio_set_flag(bio, BIO_CLONED);
पूर्ण

अटल पूर्णांक bio_iov_bvec_set(काष्ठा bio *bio, काष्ठा iov_iter *iter)
अणु
	__bio_iov_bvec_set(bio, iter);
	iov_iter_advance(iter, iter->count);
	वापस 0;
पूर्ण

अटल पूर्णांक bio_iov_bvec_set_append(काष्ठा bio *bio, काष्ठा iov_iter *iter)
अणु
	काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;
	काष्ठा iov_iter i = *iter;

	iov_iter_truncate(&i, queue_max_zone_append_sectors(q) << 9);
	__bio_iov_bvec_set(bio, &i);
	iov_iter_advance(iter, i.count);
	वापस 0;
पूर्ण

#घोषणा PAGE_PTRS_PER_BVEC     (माप(काष्ठा bio_vec) / माप(काष्ठा page *))

/**
 * __bio_iov_iter_get_pages - pin user or kernel pages and add them to a bio
 * @bio: bio to add pages to
 * @iter: iov iterator describing the region to be mapped
 *
 * Pins pages from *iter and appends them to @bio's bvec array. The
 * pages will have to be released using put_page() when करोne.
 * For multi-segment *iter, this function only adds pages from the
 * next non-empty segment of the iov iterator.
 */
अटल पूर्णांक __bio_iov_iter_get_pages(काष्ठा bio *bio, काष्ठा iov_iter *iter)
अणु
	अचिन्हित लघु nr_pages = bio->bi_max_vecs - bio->bi_vcnt;
	अचिन्हित लघु entries_left = bio->bi_max_vecs - bio->bi_vcnt;
	काष्ठा bio_vec *bv = bio->bi_io_vec + bio->bi_vcnt;
	काष्ठा page **pages = (काष्ठा page **)bv;
	bool same_page = false;
	sमाप_प्रकार size, left;
	अचिन्हित len, i;
	माप_प्रकार offset;

	/*
	 * Move page array up in the allocated memory क्रम the bio vecs as far as
	 * possible so that we can start filling biovecs from the beginning
	 * without overwriting the temporary page array.
	*/
	BUILD_BUG_ON(PAGE_PTRS_PER_BVEC < 2);
	pages += entries_left * (PAGE_PTRS_PER_BVEC - 1);

	size = iov_iter_get_pages(iter, pages, दीर्घ_उच्च, nr_pages, &offset);
	अगर (unlikely(size <= 0))
		वापस size ? size : -EFAULT;

	क्रम (left = size, i = 0; left > 0; left -= len, i++) अणु
		काष्ठा page *page = pages[i];

		len = min_t(माप_प्रकार, PAGE_SIZE - offset, left);

		अगर (__bio_try_merge_page(bio, page, len, offset, &same_page)) अणु
			अगर (same_page)
				put_page(page);
		पूर्ण अन्यथा अणु
			अगर (WARN_ON_ONCE(bio_full(bio, len)))
                                वापस -EINVAL;
			__bio_add_page(bio, page, len, offset);
		पूर्ण
		offset = 0;
	पूर्ण

	iov_iter_advance(iter, size);
	वापस 0;
पूर्ण

अटल पूर्णांक __bio_iov_append_get_pages(काष्ठा bio *bio, काष्ठा iov_iter *iter)
अणु
	अचिन्हित लघु nr_pages = bio->bi_max_vecs - bio->bi_vcnt;
	अचिन्हित लघु entries_left = bio->bi_max_vecs - bio->bi_vcnt;
	काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;
	अचिन्हित पूर्णांक max_append_sectors = queue_max_zone_append_sectors(q);
	काष्ठा bio_vec *bv = bio->bi_io_vec + bio->bi_vcnt;
	काष्ठा page **pages = (काष्ठा page **)bv;
	sमाप_प्रकार size, left;
	अचिन्हित len, i;
	माप_प्रकार offset;
	पूर्णांक ret = 0;

	अगर (WARN_ON_ONCE(!max_append_sectors))
		वापस 0;

	/*
	 * Move page array up in the allocated memory क्रम the bio vecs as far as
	 * possible so that we can start filling biovecs from the beginning
	 * without overwriting the temporary page array.
	 */
	BUILD_BUG_ON(PAGE_PTRS_PER_BVEC < 2);
	pages += entries_left * (PAGE_PTRS_PER_BVEC - 1);

	size = iov_iter_get_pages(iter, pages, दीर्घ_उच्च, nr_pages, &offset);
	अगर (unlikely(size <= 0))
		वापस size ? size : -EFAULT;

	क्रम (left = size, i = 0; left > 0; left -= len, i++) अणु
		काष्ठा page *page = pages[i];
		bool same_page = false;

		len = min_t(माप_प्रकार, PAGE_SIZE - offset, left);
		अगर (bio_add_hw_page(q, bio, page, len, offset,
				max_append_sectors, &same_page) != len) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (same_page)
			put_page(page);
		offset = 0;
	पूर्ण

	iov_iter_advance(iter, size - left);
	वापस ret;
पूर्ण

/**
 * bio_iov_iter_get_pages - add user or kernel pages to a bio
 * @bio: bio to add pages to
 * @iter: iov iterator describing the region to be added
 *
 * This takes either an iterator poपूर्णांकing to user memory, or one poपूर्णांकing to
 * kernel pages (BVEC iterator). If we're adding user pages, we pin them and
 * map them पूर्णांकo the kernel. On IO completion, the caller should put those
 * pages. For bvec based iterators bio_iov_iter_get_pages() uses the provided
 * bvecs rather than copying them. Hence anyone issuing kiocb based IO needs
 * to ensure the bvecs and pages stay referenced until the submitted I/O is
 * completed by a call to ->ki_complete() or वापसs with an error other than
 * -EIOCBQUEUED. The caller needs to check अगर the bio is flagged BIO_NO_PAGE_REF
 * on IO completion. If it isn't, then pages should be released.
 *
 * The function tries, but करोes not guarantee, to pin as many pages as
 * fit पूर्णांकo the bio, or are requested in @iter, whatever is smaller. If
 * MM encounters an error pinning the requested pages, it stops. Error
 * is वापसed only अगर 0 pages could be pinned.
 *
 * It's intended for direct IO, so doesn't करो PSI tracking, the caller is
 * responsible क्रम setting BIO_WORKINGSET अगर necessary.
 */
पूर्णांक bio_iov_iter_get_pages(काष्ठा bio *bio, काष्ठा iov_iter *iter)
अणु
	पूर्णांक ret = 0;

	अगर (iov_iter_is_bvec(iter)) अणु
		अगर (bio_op(bio) == REQ_OP_ZONE_APPEND)
			वापस bio_iov_bvec_set_append(bio, iter);
		वापस bio_iov_bvec_set(bio, iter);
	पूर्ण

	करो अणु
		अगर (bio_op(bio) == REQ_OP_ZONE_APPEND)
			ret = __bio_iov_append_get_pages(bio, iter);
		अन्यथा
			ret = __bio_iov_iter_get_pages(bio, iter);
	पूर्ण जबतक (!ret && iov_iter_count(iter) && !bio_full(bio, 0));

	/* करोn't account direct I/O as memory stall */
	bio_clear_flag(bio, BIO_WORKINGSET);
	वापस bio->bi_vcnt ? 0 : ret;
पूर्ण
EXPORT_SYMBOL_GPL(bio_iov_iter_get_pages);

अटल व्योम submit_bio_रुको_endio(काष्ठा bio *bio)
अणु
	complete(bio->bi_निजी);
पूर्ण

/**
 * submit_bio_रुको - submit a bio, and रुको until it completes
 * @bio: The &काष्ठा bio which describes the I/O
 *
 * Simple wrapper around submit_bio(). Returns 0 on success, or the error from
 * bio_endio() on failure.
 *
 * WARNING: Unlike to how submit_bio() is usually used, this function करोes not
 * result in bio reference to be consumed. The caller must drop the reference
 * on his own.
 */
पूर्णांक submit_bio_रुको(काष्ठा bio *bio)
अणु
	DECLARE_COMPLETION_ONSTACK_MAP(करोne,
			bio->bi_bdev->bd_disk->lockdep_map);
	अचिन्हित दीर्घ hang_check;

	bio->bi_निजी = &करोne;
	bio->bi_end_io = submit_bio_रुको_endio;
	bio->bi_opf |= REQ_SYNC;
	submit_bio(bio);

	/* Prevent hang_check समयr from firing at us during very दीर्घ I/O */
	hang_check = sysctl_hung_task_समयout_secs;
	अगर (hang_check)
		जबतक (!रुको_क्रम_completion_io_समयout(&करोne,
					hang_check * (HZ/2)))
			;
	अन्यथा
		रुको_क्रम_completion_io(&करोne);

	वापस blk_status_to_त्रुटि_सं(bio->bi_status);
पूर्ण
EXPORT_SYMBOL(submit_bio_रुको);

/**
 * bio_advance - increment/complete a bio by some number of bytes
 * @bio:	bio to advance
 * @bytes:	number of bytes to complete
 *
 * This updates bi_sector, bi_size and bi_idx; अगर the number of bytes to
 * complete करोesn't align with a bvec boundary, then bv_len and bv_offset will
 * be updated on the last bvec as well.
 *
 * @bio will then represent the reमुख्यing, uncompleted portion of the io.
 */
व्योम bio_advance(काष्ठा bio *bio, अचिन्हित bytes)
अणु
	अगर (bio_पूर्णांकegrity(bio))
		bio_पूर्णांकegrity_advance(bio, bytes);

	bio_crypt_advance(bio, bytes);
	bio_advance_iter(bio, &bio->bi_iter, bytes);
पूर्ण
EXPORT_SYMBOL(bio_advance);

व्योम bio_copy_data_iter(काष्ठा bio *dst, काष्ठा bvec_iter *dst_iter,
			काष्ठा bio *src, काष्ठा bvec_iter *src_iter)
अणु
	काष्ठा bio_vec src_bv, dst_bv;
	व्योम *src_p, *dst_p;
	अचिन्हित bytes;

	जबतक (src_iter->bi_size && dst_iter->bi_size) अणु
		src_bv = bio_iter_iovec(src, *src_iter);
		dst_bv = bio_iter_iovec(dst, *dst_iter);

		bytes = min(src_bv.bv_len, dst_bv.bv_len);

		src_p = kmap_atomic(src_bv.bv_page);
		dst_p = kmap_atomic(dst_bv.bv_page);

		स_नकल(dst_p + dst_bv.bv_offset,
		       src_p + src_bv.bv_offset,
		       bytes);

		kunmap_atomic(dst_p);
		kunmap_atomic(src_p);

		flush_dcache_page(dst_bv.bv_page);

		bio_advance_iter_single(src, src_iter, bytes);
		bio_advance_iter_single(dst, dst_iter, bytes);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(bio_copy_data_iter);

/**
 * bio_copy_data - copy contents of data buffers from one bio to another
 * @src: source bio
 * @dst: destination bio
 *
 * Stops when it reaches the end of either @src or @dst - that is, copies
 * min(src->bi_size, dst->bi_size) bytes (or the equivalent क्रम lists of bios).
 */
व्योम bio_copy_data(काष्ठा bio *dst, काष्ठा bio *src)
अणु
	काष्ठा bvec_iter src_iter = src->bi_iter;
	काष्ठा bvec_iter dst_iter = dst->bi_iter;

	bio_copy_data_iter(dst, &dst_iter, src, &src_iter);
पूर्ण
EXPORT_SYMBOL(bio_copy_data);

व्योम bio_मुक्त_pages(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all)
		__मुक्त_page(bvec->bv_page);
पूर्ण
EXPORT_SYMBOL(bio_मुक्त_pages);

/*
 * bio_set_pages_dirty() and bio_check_pages_dirty() are support functions
 * क्रम perक्रमming direct-IO in BIOs.
 *
 * The problem is that we cannot run set_page_dirty() from पूर्णांकerrupt context
 * because the required locks are not पूर्णांकerrupt-safe.  So what we can करो is to
 * mark the pages dirty _beक्रमe_ perक्रमming IO.  And in पूर्णांकerrupt context,
 * check that the pages are still dirty.   If so, fine.  If not, redirty them
 * in process context.
 *
 * We special-हाल compound pages here: normally this means पढ़ोs पूर्णांकo hugetlb
 * pages.  The logic in here करोesn't really work right क्रम compound pages
 * because the VM करोes not unअगरormly chase करोwn the head page in all हालs.
 * But dirtiness of compound pages is pretty meaningless anyway: the VM करोesn't
 * handle them at all.  So we skip compound pages here at an early stage.
 *
 * Note that this code is very hard to test under normal circumstances because
 * direct-io pins the pages with get_user_pages().  This makes
 * is_page_cache_मुक्तable वापस false, and the VM will not clean the pages.
 * But other code (eg, flusher thपढ़ोs) could clean the pages अगर they are mapped
 * pagecache.
 *
 * Simply disabling the call to bio_set_pages_dirty() is a good way to test the
 * deferred bio dirtying paths.
 */

/*
 * bio_set_pages_dirty() will mark all the bio's pages as dirty.
 */
व्योम bio_set_pages_dirty(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		अगर (!PageCompound(bvec->bv_page))
			set_page_dirty_lock(bvec->bv_page);
	पूर्ण
पूर्ण

/*
 * bio_check_pages_dirty() will check that all the BIO's pages are still dirty.
 * If they are, then fine.  If, however, some pages are clean then they must
 * have been written out during the direct-IO पढ़ो.  So we take another ref on
 * the BIO and re-dirty the pages in process context.
 *
 * It is expected that bio_check_pages_dirty() will wholly own the BIO from
 * here on.  It will run one put_page() against each page and will run one
 * bio_put() against the BIO.
 */

अटल व्योम bio_dirty_fn(काष्ठा work_काष्ठा *work);

अटल DECLARE_WORK(bio_dirty_work, bio_dirty_fn);
अटल DEFINE_SPINLOCK(bio_dirty_lock);
अटल काष्ठा bio *bio_dirty_list;

/*
 * This runs in process context
 */
अटल व्योम bio_dirty_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bio *bio, *next;

	spin_lock_irq(&bio_dirty_lock);
	next = bio_dirty_list;
	bio_dirty_list = शून्य;
	spin_unlock_irq(&bio_dirty_lock);

	जबतक ((bio = next) != शून्य) अणु
		next = bio->bi_निजी;

		bio_release_pages(bio, true);
		bio_put(bio);
	पूर्ण
पूर्ण

व्योम bio_check_pages_dirty(काष्ठा bio *bio)
अणु
	काष्ठा bio_vec *bvec;
	अचिन्हित दीर्घ flags;
	काष्ठा bvec_iter_all iter_all;

	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		अगर (!PageDirty(bvec->bv_page) && !PageCompound(bvec->bv_page))
			जाओ defer;
	पूर्ण

	bio_release_pages(bio, false);
	bio_put(bio);
	वापस;
defer:
	spin_lock_irqsave(&bio_dirty_lock, flags);
	bio->bi_निजी = bio_dirty_list;
	bio_dirty_list = bio;
	spin_unlock_irqrestore(&bio_dirty_lock, flags);
	schedule_work(&bio_dirty_work);
पूर्ण

अटल अंतरभूत bool bio_reमुख्यing_करोne(काष्ठा bio *bio)
अणु
	/*
	 * If we're not chaining, then ->__bi_reमुख्यing is always 1 and
	 * we always end io on the first invocation.
	 */
	अगर (!bio_flagged(bio, BIO_CHAIN))
		वापस true;

	BUG_ON(atomic_पढ़ो(&bio->__bi_reमुख्यing) <= 0);

	अगर (atomic_dec_and_test(&bio->__bi_reमुख्यing)) अणु
		bio_clear_flag(bio, BIO_CHAIN);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * bio_endio - end I/O on a bio
 * @bio:	bio
 *
 * Description:
 *   bio_endio() will end I/O on the whole bio. bio_endio() is the preferred
 *   way to end I/O on a bio. No one should call bi_end_io() directly on a
 *   bio unless they own it and thus know that it has an end_io function.
 *
 *   bio_endio() can be called several बार on a bio that has been chained
 *   using bio_chain().  The ->bi_end_io() function will only be called the
 *   last समय.  At this poपूर्णांक the BLK_TA_COMPLETE tracing event will be
 *   generated अगर BIO_TRACE_COMPLETION is set.
 **/
व्योम bio_endio(काष्ठा bio *bio)
अणु
again:
	अगर (!bio_reमुख्यing_करोne(bio))
		वापस;
	अगर (!bio_पूर्णांकegrity_endio(bio))
		वापस;

	अगर (bio->bi_bdev)
		rq_qos_करोne_bio(bio->bi_bdev->bd_disk->queue, bio);

	/*
	 * Need to have a real endio function क्रम chained bios, otherwise
	 * various corner हालs will अवरोध (like stacking block devices that
	 * save/restore bi_end_io) - however, we want to aव्योम unbounded
	 * recursion and blowing the stack. Tail call optimization would
	 * handle this, but compiling with frame poपूर्णांकers also disables
	 * gcc's sibling call optimization.
	 */
	अगर (bio->bi_end_io == bio_chain_endio) अणु
		bio = __bio_chain_endio(bio);
		जाओ again;
	पूर्ण

	अगर (bio->bi_bdev && bio_flagged(bio, BIO_TRACE_COMPLETION)) अणु
		trace_block_bio_complete(bio->bi_bdev->bd_disk->queue, bio);
		bio_clear_flag(bio, BIO_TRACE_COMPLETION);
	पूर्ण

	blk_throtl_bio_endio(bio);
	/* release cgroup info */
	bio_uninit(bio);
	अगर (bio->bi_end_io)
		bio->bi_end_io(bio);
पूर्ण
EXPORT_SYMBOL(bio_endio);

/**
 * bio_split - split a bio
 * @bio:	bio to split
 * @sectors:	number of sectors to split from the front of @bio
 * @gfp:	gfp mask
 * @bs:		bio set to allocate from
 *
 * Allocates and वापसs a new bio which represents @sectors from the start of
 * @bio, and updates @bio to represent the reमुख्यing sectors.
 *
 * Unless this is a discard request the newly allocated bio will poपूर्णांक
 * to @bio's bi_io_vec. It is the caller's responsibility to ensure that
 * neither @bio nor @bs are मुक्तd beक्रमe the split bio.
 */
काष्ठा bio *bio_split(काष्ठा bio *bio, पूर्णांक sectors,
		      gfp_t gfp, काष्ठा bio_set *bs)
अणु
	काष्ठा bio *split;

	BUG_ON(sectors <= 0);
	BUG_ON(sectors >= bio_sectors(bio));

	/* Zone append commands cannot be split */
	अगर (WARN_ON_ONCE(bio_op(bio) == REQ_OP_ZONE_APPEND))
		वापस शून्य;

	split = bio_clone_fast(bio, gfp, bs);
	अगर (!split)
		वापस शून्य;

	split->bi_iter.bi_size = sectors << 9;

	अगर (bio_पूर्णांकegrity(split))
		bio_पूर्णांकegrity_trim(split);

	bio_advance(bio, split->bi_iter.bi_size);

	अगर (bio_flagged(bio, BIO_TRACE_COMPLETION))
		bio_set_flag(split, BIO_TRACE_COMPLETION);

	वापस split;
पूर्ण
EXPORT_SYMBOL(bio_split);

/**
 * bio_trim - trim a bio
 * @bio:	bio to trim
 * @offset:	number of sectors to trim from the front of @bio
 * @size:	size we want to trim @bio to, in sectors
 */
व्योम bio_trim(काष्ठा bio *bio, पूर्णांक offset, पूर्णांक size)
अणु
	/* 'bio' is a cloned bio which we need to trim to match
	 * the given offset and size.
	 */

	size <<= 9;
	अगर (offset == 0 && size == bio->bi_iter.bi_size)
		वापस;

	bio_advance(bio, offset << 9);
	bio->bi_iter.bi_size = size;

	अगर (bio_पूर्णांकegrity(bio))
		bio_पूर्णांकegrity_trim(bio);

पूर्ण
EXPORT_SYMBOL_GPL(bio_trim);

/*
 * create memory pools क्रम biovec's in a bio_set.
 * use the global biovec sद_असल created क्रम general use.
 */
पूर्णांक biovec_init_pool(mempool_t *pool, पूर्णांक pool_entries)
अणु
	काष्ठा biovec_slab *bp = bvec_sद_असल + ARRAY_SIZE(bvec_sद_असल) - 1;

	वापस mempool_init_slab_pool(pool, pool_entries, bp->slab);
पूर्ण

/*
 * bioset_निकास - निकास a bioset initialized with bioset_init()
 *
 * May be called on a zeroed but uninitialized bioset (i.e. allocated with
 * kzalloc()).
 */
व्योम bioset_निकास(काष्ठा bio_set *bs)
अणु
	अगर (bs->rescue_workqueue)
		destroy_workqueue(bs->rescue_workqueue);
	bs->rescue_workqueue = शून्य;

	mempool_निकास(&bs->bio_pool);
	mempool_निकास(&bs->bvec_pool);

	bioset_पूर्णांकegrity_मुक्त(bs);
	अगर (bs->bio_slab)
		bio_put_slab(bs);
	bs->bio_slab = शून्य;
पूर्ण
EXPORT_SYMBOL(bioset_निकास);

/**
 * bioset_init - Initialize a bio_set
 * @bs:		pool to initialize
 * @pool_size:	Number of bio and bio_vecs to cache in the mempool
 * @front_pad:	Number of bytes to allocate in front of the वापसed bio
 * @flags:	Flags to modअगरy behavior, currently %BIOSET_NEED_BVECS
 *              and %BIOSET_NEED_RESCUER
 *
 * Description:
 *    Set up a bio_set to be used with @bio_alloc_bioset. Allows the caller
 *    to ask क्रम a number of bytes to be allocated in front of the bio.
 *    Front pad allocation is useful क्रम embedding the bio inside
 *    another काष्ठाure, to aव्योम allocating extra data to go with the bio.
 *    Note that the bio must be embedded at the END of that काष्ठाure always,
 *    or things will अवरोध badly.
 *    If %BIOSET_NEED_BVECS is set in @flags, a separate pool will be allocated
 *    क्रम allocating iovecs.  This pool is not needed e.g. क्रम bio_clone_fast().
 *    If %BIOSET_NEED_RESCUER is set, a workqueue is created which can be used to
 *    dispatch queued requests when the mempool runs out of space.
 *
 */
पूर्णांक bioset_init(काष्ठा bio_set *bs,
		अचिन्हित पूर्णांक pool_size,
		अचिन्हित पूर्णांक front_pad,
		पूर्णांक flags)
अणु
	bs->front_pad = front_pad;
	अगर (flags & BIOSET_NEED_BVECS)
		bs->back_pad = BIO_INLINE_VECS * माप(काष्ठा bio_vec);
	अन्यथा
		bs->back_pad = 0;

	spin_lock_init(&bs->rescue_lock);
	bio_list_init(&bs->rescue_list);
	INIT_WORK(&bs->rescue_work, bio_alloc_rescue);

	bs->bio_slab = bio_find_or_create_slab(bs);
	अगर (!bs->bio_slab)
		वापस -ENOMEM;

	अगर (mempool_init_slab_pool(&bs->bio_pool, pool_size, bs->bio_slab))
		जाओ bad;

	अगर ((flags & BIOSET_NEED_BVECS) &&
	    biovec_init_pool(&bs->bvec_pool, pool_size))
		जाओ bad;

	अगर (!(flags & BIOSET_NEED_RESCUER))
		वापस 0;

	bs->rescue_workqueue = alloc_workqueue("bioset", WQ_MEM_RECLAIM, 0);
	अगर (!bs->rescue_workqueue)
		जाओ bad;

	वापस 0;
bad:
	bioset_निकास(bs);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(bioset_init);

/*
 * Initialize and setup a new bio_set, based on the settings from
 * another bio_set.
 */
पूर्णांक bioset_init_from_src(काष्ठा bio_set *bs, काष्ठा bio_set *src)
अणु
	पूर्णांक flags;

	flags = 0;
	अगर (src->bvec_pool.min_nr)
		flags |= BIOSET_NEED_BVECS;
	अगर (src->rescue_workqueue)
		flags |= BIOSET_NEED_RESCUER;

	वापस bioset_init(bs, src->bio_pool.min_nr, src->front_pad, flags);
पूर्ण
EXPORT_SYMBOL(bioset_init_from_src);

अटल पूर्णांक __init init_bio(व्योम)
अणु
	पूर्णांक i;

	bio_पूर्णांकegrity_init();

	क्रम (i = 0; i < ARRAY_SIZE(bvec_sद_असल); i++) अणु
		काष्ठा biovec_slab *bvs = bvec_sद_असल + i;

		bvs->slab = kmem_cache_create(bvs->name,
				bvs->nr_vecs * माप(काष्ठा bio_vec), 0,
				SLAB_HWCACHE_ALIGN | SLAB_PANIC, शून्य);
	पूर्ण

	अगर (bioset_init(&fs_bio_set, BIO_POOL_SIZE, 0, BIOSET_NEED_BVECS))
		panic("bio: can't allocate bios\n");

	अगर (bioset_पूर्णांकegrity_create(&fs_bio_set, BIO_POOL_SIZE))
		panic("bio: can't create integrity pool\n");

	वापस 0;
पूर्ण
subsys_initcall(init_bio);
