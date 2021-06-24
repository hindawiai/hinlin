<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bio-पूर्णांकegrity.c - bio data पूर्णांकegrity extensions
 *
 * Copyright (C) 2007, 2008, 2009 Oracle Corporation
 * Written by: Martin K. Petersen <martin.petersen@oracle.com>
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/mempool.h>
#समावेश <linux/export.h>
#समावेश <linux/bपन.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/slab.h>
#समावेश "blk.h"

अटल काष्ठा kmem_cache *bip_slab;
अटल काष्ठा workqueue_काष्ठा *kपूर्णांकegrityd_wq;

व्योम blk_flush_पूर्णांकegrity(व्योम)
अणु
	flush_workqueue(kपूर्णांकegrityd_wq);
पूर्ण

अटल व्योम __bio_पूर्णांकegrity_मुक्त(काष्ठा bio_set *bs,
				 काष्ठा bio_पूर्णांकegrity_payload *bip)
अणु
	अगर (bs && mempool_initialized(&bs->bio_पूर्णांकegrity_pool)) अणु
		अगर (bip->bip_vec)
			bvec_मुक्त(&bs->bvec_पूर्णांकegrity_pool, bip->bip_vec,
				  bip->bip_max_vcnt);
		mempool_मुक्त(bip, &bs->bio_पूर्णांकegrity_pool);
	पूर्ण अन्यथा अणु
		kमुक्त(bip);
	पूर्ण
पूर्ण

/**
 * bio_पूर्णांकegrity_alloc - Allocate पूर्णांकegrity payload and attach it to bio
 * @bio:	bio to attach पूर्णांकegrity metadata to
 * @gfp_mask:	Memory allocation mask
 * @nr_vecs:	Number of पूर्णांकegrity metadata scatter-gather elements
 *
 * Description: This function prepares a bio क्रम attaching पूर्णांकegrity
 * metadata.  nr_vecs specअगरies the maximum number of pages containing
 * पूर्णांकegrity metadata that can be attached.
 */
काष्ठा bio_पूर्णांकegrity_payload *bio_पूर्णांकegrity_alloc(काष्ठा bio *bio,
						  gfp_t gfp_mask,
						  अचिन्हित पूर्णांक nr_vecs)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip;
	काष्ठा bio_set *bs = bio->bi_pool;
	अचिन्हित अंतरभूत_vecs;

	अगर (WARN_ON_ONCE(bio_has_crypt_ctx(bio)))
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (!bs || !mempool_initialized(&bs->bio_पूर्णांकegrity_pool)) अणु
		bip = kदो_स्मृति(काष्ठा_size(bip, bip_अंतरभूत_vecs, nr_vecs), gfp_mask);
		अंतरभूत_vecs = nr_vecs;
	पूर्ण अन्यथा अणु
		bip = mempool_alloc(&bs->bio_पूर्णांकegrity_pool, gfp_mask);
		अंतरभूत_vecs = BIO_INLINE_VECS;
	पूर्ण

	अगर (unlikely(!bip))
		वापस ERR_PTR(-ENOMEM);

	स_रखो(bip, 0, माप(*bip));

	अगर (nr_vecs > अंतरभूत_vecs) अणु
		bip->bip_max_vcnt = nr_vecs;
		bip->bip_vec = bvec_alloc(&bs->bvec_पूर्णांकegrity_pool,
					  &bip->bip_max_vcnt, gfp_mask);
		अगर (!bip->bip_vec)
			जाओ err;
	पूर्ण अन्यथा अणु
		bip->bip_vec = bip->bip_अंतरभूत_vecs;
		bip->bip_max_vcnt = अंतरभूत_vecs;
	पूर्ण

	bip->bip_bio = bio;
	bio->bi_पूर्णांकegrity = bip;
	bio->bi_opf |= REQ_INTEGRITY;

	वापस bip;
err:
	__bio_पूर्णांकegrity_मुक्त(bs, bip);
	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL(bio_पूर्णांकegrity_alloc);

/**
 * bio_पूर्णांकegrity_मुक्त - Free bio पूर्णांकegrity payload
 * @bio:	bio containing bip to be मुक्तd
 *
 * Description: Used to मुक्त the पूर्णांकegrity portion of a bio. Usually
 * called from bio_मुक्त().
 */
व्योम bio_पूर्णांकegrity_मुक्त(काष्ठा bio *bio)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
	काष्ठा bio_set *bs = bio->bi_pool;

	अगर (bip->bip_flags & BIP_BLOCK_INTEGRITY)
		kमुक्त(page_address(bip->bip_vec->bv_page) +
		      bip->bip_vec->bv_offset);

	__bio_पूर्णांकegrity_मुक्त(bs, bip);
	bio->bi_पूर्णांकegrity = शून्य;
	bio->bi_opf &= ~REQ_INTEGRITY;
पूर्ण

/**
 * bio_पूर्णांकegrity_add_page - Attach पूर्णांकegrity metadata
 * @bio:	bio to update
 * @page:	page containing पूर्णांकegrity metadata
 * @len:	number of bytes of पूर्णांकegrity metadata in page
 * @offset:	start offset within page
 *
 * Description: Attach a page containing पूर्णांकegrity metadata to bio.
 */
पूर्णांक bio_पूर्णांकegrity_add_page(काष्ठा bio *bio, काष्ठा page *page,
			   अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
	काष्ठा bio_vec *iv;

	अगर (bip->bip_vcnt >= bip->bip_max_vcnt) अणु
		prपूर्णांकk(KERN_ERR "%s: bip_vec full\n", __func__);
		वापस 0;
	पूर्ण

	iv = bip->bip_vec + bip->bip_vcnt;

	अगर (bip->bip_vcnt &&
	    bvec_gap_to_prev(bio->bi_bdev->bd_disk->queue,
			     &bip->bip_vec[bip->bip_vcnt - 1], offset))
		वापस 0;

	iv->bv_page = page;
	iv->bv_len = len;
	iv->bv_offset = offset;
	bip->bip_vcnt++;

	वापस len;
पूर्ण
EXPORT_SYMBOL(bio_पूर्णांकegrity_add_page);

/**
 * bio_पूर्णांकegrity_process - Process पूर्णांकegrity metadata क्रम a bio
 * @bio:	bio to generate/verअगरy पूर्णांकegrity metadata क्रम
 * @proc_iter:  iterator to process
 * @proc_fn:	Poपूर्णांकer to the relevant processing function
 */
अटल blk_status_t bio_पूर्णांकegrity_process(काष्ठा bio *bio,
		काष्ठा bvec_iter *proc_iter, पूर्णांकegrity_processing_fn *proc_fn)
अणु
	काष्ठा blk_पूर्णांकegrity *bi = blk_get_पूर्णांकegrity(bio->bi_bdev->bd_disk);
	काष्ठा blk_पूर्णांकegrity_iter iter;
	काष्ठा bvec_iter bviter;
	काष्ठा bio_vec bv;
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
	blk_status_t ret = BLK_STS_OK;
	व्योम *prot_buf = page_address(bip->bip_vec->bv_page) +
		bip->bip_vec->bv_offset;

	iter.disk_name = bio->bi_bdev->bd_disk->disk_name;
	iter.पूर्णांकerval = 1 << bi->पूर्णांकerval_exp;
	iter.seed = proc_iter->bi_sector;
	iter.prot_buf = prot_buf;

	__bio_क्रम_each_segment(bv, bio, bviter, *proc_iter) अणु
		व्योम *kaddr = kmap_atomic(bv.bv_page);

		iter.data_buf = kaddr + bv.bv_offset;
		iter.data_size = bv.bv_len;

		ret = proc_fn(&iter);
		अगर (ret) अणु
			kunmap_atomic(kaddr);
			वापस ret;
		पूर्ण

		kunmap_atomic(kaddr);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * bio_पूर्णांकegrity_prep - Prepare bio क्रम पूर्णांकegrity I/O
 * @bio:	bio to prepare
 *
 * Description:  Checks अगर the bio alपढ़ोy has an पूर्णांकegrity payload attached.
 * If it करोes, the payload has been generated by another kernel subप्रणाली,
 * and we just pass it through. Otherwise allocates पूर्णांकegrity payload.
 * The bio must have data direction, target device and start sector set priot
 * to calling.  In the WRITE हाल, पूर्णांकegrity metadata will be generated using
 * the block device's पूर्णांकegrity function.  In the READ हाल, the buffer
 * will be prepared क्रम DMA and a suitable end_io handler set up.
 */
bool bio_पूर्णांकegrity_prep(काष्ठा bio *bio)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip;
	काष्ठा blk_पूर्णांकegrity *bi = blk_get_पूर्णांकegrity(bio->bi_bdev->bd_disk);
	व्योम *buf;
	अचिन्हित दीर्घ start, end;
	अचिन्हित पूर्णांक len, nr_pages;
	अचिन्हित पूर्णांक bytes, offset, i;
	अचिन्हित पूर्णांक पूर्णांकervals;
	blk_status_t status;

	अगर (!bi)
		वापस true;

	अगर (bio_op(bio) != REQ_OP_READ && bio_op(bio) != REQ_OP_WRITE)
		वापस true;

	अगर (!bio_sectors(bio))
		वापस true;

	/* Alपढ़ोy रक्षित? */
	अगर (bio_पूर्णांकegrity(bio))
		वापस true;

	अगर (bio_data_dir(bio) == READ) अणु
		अगर (!bi->profile->verअगरy_fn ||
		    !(bi->flags & BLK_INTEGRITY_VERIFY))
			वापस true;
	पूर्ण अन्यथा अणु
		अगर (!bi->profile->generate_fn ||
		    !(bi->flags & BLK_INTEGRITY_GENERATE))
			वापस true;
	पूर्ण
	पूर्णांकervals = bio_पूर्णांकegrity_पूर्णांकervals(bi, bio_sectors(bio));

	/* Allocate kernel buffer क्रम protection data */
	len = पूर्णांकervals * bi->tuple_size;
	buf = kदो_स्मृति(len, GFP_NOIO);
	status = BLK_STS_RESOURCE;
	अगर (unlikely(buf == शून्य)) अणु
		prपूर्णांकk(KERN_ERR "could not allocate integrity buffer\n");
		जाओ err_end_io;
	पूर्ण

	end = (((अचिन्हित दीर्घ) buf) + len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	start = ((अचिन्हित दीर्घ) buf) >> PAGE_SHIFT;
	nr_pages = end - start;

	/* Allocate bio पूर्णांकegrity payload and पूर्णांकegrity vectors */
	bip = bio_पूर्णांकegrity_alloc(bio, GFP_NOIO, nr_pages);
	अगर (IS_ERR(bip)) अणु
		prपूर्णांकk(KERN_ERR "could not allocate data integrity bioset\n");
		kमुक्त(buf);
		status = BLK_STS_RESOURCE;
		जाओ err_end_io;
	पूर्ण

	bip->bip_flags |= BIP_BLOCK_INTEGRITY;
	bip->bip_iter.bi_size = len;
	bip_set_seed(bip, bio->bi_iter.bi_sector);

	अगर (bi->flags & BLK_INTEGRITY_IP_CHECKSUM)
		bip->bip_flags |= BIP_IP_CHECKSUM;

	/* Map it */
	offset = offset_in_page(buf);
	क्रम (i = 0 ; i < nr_pages ; i++) अणु
		पूर्णांक ret;
		bytes = PAGE_SIZE - offset;

		अगर (len <= 0)
			अवरोध;

		अगर (bytes > len)
			bytes = len;

		ret = bio_पूर्णांकegrity_add_page(bio, virt_to_page(buf),
					     bytes, offset);

		अगर (ret == 0) अणु
			prपूर्णांकk(KERN_ERR "could not attach integrity payload\n");
			status = BLK_STS_RESOURCE;
			जाओ err_end_io;
		पूर्ण

		अगर (ret < bytes)
			अवरोध;

		buf += bytes;
		len -= bytes;
		offset = 0;
	पूर्ण

	/* Auto-generate पूर्णांकegrity metadata अगर this is a ग_लिखो */
	अगर (bio_data_dir(bio) == WRITE) अणु
		bio_पूर्णांकegrity_process(bio, &bio->bi_iter,
				      bi->profile->generate_fn);
	पूर्ण अन्यथा अणु
		bip->bio_iter = bio->bi_iter;
	पूर्ण
	वापस true;

err_end_io:
	bio->bi_status = status;
	bio_endio(bio);
	वापस false;

पूर्ण
EXPORT_SYMBOL(bio_पूर्णांकegrity_prep);

/**
 * bio_पूर्णांकegrity_verअगरy_fn - Integrity I/O completion worker
 * @work:	Work काष्ठा stored in bio to be verअगरied
 *
 * Description: This workqueue function is called to complete a READ
 * request.  The function verअगरies the transferred पूर्णांकegrity metadata
 * and then calls the original bio end_io function.
 */
अटल व्योम bio_पूर्णांकegrity_verअगरy_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip =
		container_of(work, काष्ठा bio_पूर्णांकegrity_payload, bip_work);
	काष्ठा bio *bio = bip->bip_bio;
	काष्ठा blk_पूर्णांकegrity *bi = blk_get_पूर्णांकegrity(bio->bi_bdev->bd_disk);

	/*
	 * At the moment verअगरy is called bio's iterator was advanced
	 * during split and completion, we need to शुरुआत iterator to
	 * it's original position.
	 */
	bio->bi_status = bio_पूर्णांकegrity_process(bio, &bip->bio_iter,
						bi->profile->verअगरy_fn);
	bio_पूर्णांकegrity_मुक्त(bio);
	bio_endio(bio);
पूर्ण

/**
 * __bio_पूर्णांकegrity_endio - Integrity I/O completion function
 * @bio:	Protected bio
 *
 * Description: Completion क्रम पूर्णांकegrity I/O
 *
 * Normally I/O completion is करोne in पूर्णांकerrupt context.  However,
 * verअगरying I/O पूर्णांकegrity is a समय-consuming task which must be run
 * in process context.	This function postpones completion
 * accordingly.
 */
bool __bio_पूर्णांकegrity_endio(काष्ठा bio *bio)
अणु
	काष्ठा blk_पूर्णांकegrity *bi = blk_get_पूर्णांकegrity(bio->bi_bdev->bd_disk);
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);

	अगर (bio_op(bio) == REQ_OP_READ && !bio->bi_status &&
	    (bip->bip_flags & BIP_BLOCK_INTEGRITY) && bi->profile->verअगरy_fn) अणु
		INIT_WORK(&bip->bip_work, bio_पूर्णांकegrity_verअगरy_fn);
		queue_work(kपूर्णांकegrityd_wq, &bip->bip_work);
		वापस false;
	पूर्ण

	bio_पूर्णांकegrity_मुक्त(bio);
	वापस true;
पूर्ण

/**
 * bio_पूर्णांकegrity_advance - Advance पूर्णांकegrity vector
 * @bio:	bio whose पूर्णांकegrity vector to update
 * @bytes_करोne:	number of data bytes that have been completed
 *
 * Description: This function calculates how many पूर्णांकegrity bytes the
 * number of completed data bytes correspond to and advances the
 * पूर्णांकegrity vector accordingly.
 */
व्योम bio_पूर्णांकegrity_advance(काष्ठा bio *bio, अचिन्हित पूर्णांक bytes_करोne)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
	काष्ठा blk_पूर्णांकegrity *bi = blk_get_पूर्णांकegrity(bio->bi_bdev->bd_disk);
	अचिन्हित bytes = bio_पूर्णांकegrity_bytes(bi, bytes_करोne >> 9);

	bip->bip_iter.bi_sector += bytes_करोne >> 9;
	bvec_iter_advance(bip->bip_vec, &bip->bip_iter, bytes);
पूर्ण

/**
 * bio_पूर्णांकegrity_trim - Trim पूर्णांकegrity vector
 * @bio:	bio whose पूर्णांकegrity vector to update
 *
 * Description: Used to trim the पूर्णांकegrity vector in a cloned bio.
 */
व्योम bio_पूर्णांकegrity_trim(काष्ठा bio *bio)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
	काष्ठा blk_पूर्णांकegrity *bi = blk_get_पूर्णांकegrity(bio->bi_bdev->bd_disk);

	bip->bip_iter.bi_size = bio_पूर्णांकegrity_bytes(bi, bio_sectors(bio));
पूर्ण
EXPORT_SYMBOL(bio_पूर्णांकegrity_trim);

/**
 * bio_पूर्णांकegrity_clone - Callback क्रम cloning bios with पूर्णांकegrity metadata
 * @bio:	New bio
 * @bio_src:	Original bio
 * @gfp_mask:	Memory allocation mask
 *
 * Description:	Called to allocate a bip when cloning a bio
 */
पूर्णांक bio_पूर्णांकegrity_clone(काष्ठा bio *bio, काष्ठा bio *bio_src,
			gfp_t gfp_mask)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip_src = bio_पूर्णांकegrity(bio_src);
	काष्ठा bio_पूर्णांकegrity_payload *bip;

	BUG_ON(bip_src == शून्य);

	bip = bio_पूर्णांकegrity_alloc(bio, gfp_mask, bip_src->bip_vcnt);
	अगर (IS_ERR(bip))
		वापस PTR_ERR(bip);

	स_नकल(bip->bip_vec, bip_src->bip_vec,
	       bip_src->bip_vcnt * माप(काष्ठा bio_vec));

	bip->bip_vcnt = bip_src->bip_vcnt;
	bip->bip_iter = bip_src->bip_iter;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(bio_पूर्णांकegrity_clone);

पूर्णांक bioset_पूर्णांकegrity_create(काष्ठा bio_set *bs, पूर्णांक pool_size)
अणु
	अगर (mempool_initialized(&bs->bio_पूर्णांकegrity_pool))
		वापस 0;

	अगर (mempool_init_slab_pool(&bs->bio_पूर्णांकegrity_pool,
				   pool_size, bip_slab))
		वापस -1;

	अगर (biovec_init_pool(&bs->bvec_पूर्णांकegrity_pool, pool_size)) अणु
		mempool_निकास(&bs->bio_पूर्णांकegrity_pool);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(bioset_पूर्णांकegrity_create);

व्योम bioset_पूर्णांकegrity_मुक्त(काष्ठा bio_set *bs)
अणु
	mempool_निकास(&bs->bio_पूर्णांकegrity_pool);
	mempool_निकास(&bs->bvec_पूर्णांकegrity_pool);
पूर्ण

व्योम __init bio_पूर्णांकegrity_init(व्योम)
अणु
	/*
	 * kपूर्णांकegrityd won't block much but may burn a lot of CPU cycles.
	 * Make it highpri CPU पूर्णांकensive wq with max concurrency of 1.
	 */
	kपूर्णांकegrityd_wq = alloc_workqueue("kintegrityd", WQ_MEM_RECLAIM |
					 WQ_HIGHPRI | WQ_CPU_INTENSIVE, 1);
	अगर (!kपूर्णांकegrityd_wq)
		panic("Failed to create kintegrityd\n");

	bip_slab = kmem_cache_create("bio_integrity_payload",
				     माप(काष्ठा bio_पूर्णांकegrity_payload) +
				     माप(काष्ठा bio_vec) * BIO_INLINE_VECS,
				     0, SLAB_HWCACHE_ALIGN|SLAB_PANIC, शून्य);
पूर्ण
