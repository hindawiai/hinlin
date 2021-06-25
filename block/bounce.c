<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* bounce buffer handling क्रम block devices
 *
 * - Split from highmem.c
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/swap.h>
#समावेश <linux/gfp.h>
#समावेश <linux/bपन.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/mempool.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/init.h>
#समावेश <linux/hash.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <trace/events/block.h>
#समावेश "blk.h"

#घोषणा POOL_SIZE	64
#घोषणा ISA_POOL_SIZE	16

अटल काष्ठा bio_set bounce_bio_set, bounce_bio_split;
अटल mempool_t page_pool;

अटल व्योम init_bounce_bioset(व्योम)
अणु
	अटल bool bounce_bs_setup;
	पूर्णांक ret;

	अगर (bounce_bs_setup)
		वापस;

	ret = bioset_init(&bounce_bio_set, BIO_POOL_SIZE, 0, BIOSET_NEED_BVECS);
	BUG_ON(ret);
	अगर (bioset_पूर्णांकegrity_create(&bounce_bio_set, BIO_POOL_SIZE))
		BUG_ON(1);

	ret = bioset_init(&bounce_bio_split, BIO_POOL_SIZE, 0, 0);
	BUG_ON(ret);
	bounce_bs_setup = true;
पूर्ण

अटल __init पूर्णांक init_emergency_pool(व्योम)
अणु
	पूर्णांक ret;

#अगर_अघोषित CONFIG_MEMORY_HOTPLUG
	अगर (max_pfn <= max_low_pfn)
		वापस 0;
#पूर्ण_अगर

	ret = mempool_init_page_pool(&page_pool, POOL_SIZE, 0);
	BUG_ON(ret);
	pr_info("pool size: %d pages\n", POOL_SIZE);

	init_bounce_bioset();
	वापस 0;
पूर्ण

__initcall(init_emergency_pool);

/*
 * highmem version, map in to vec
 */
अटल व्योम bounce_copy_vec(काष्ठा bio_vec *to, अचिन्हित अक्षर *vfrom)
अणु
	अचिन्हित अक्षर *vto;

	vto = kmap_atomic(to->bv_page);
	स_नकल(vto + to->bv_offset, vfrom, to->bv_len);
	kunmap_atomic(vto);
पूर्ण

/*
 * Simple bounce buffer support क्रम highmem pages. Depending on the
 * queue gfp mask set, *to may or may not be a highmem page. kmap it
 * always, it will करो the Right Thing
 */
अटल व्योम copy_to_high_bio_irq(काष्ठा bio *to, काष्ठा bio *from)
अणु
	अचिन्हित अक्षर *vfrom;
	काष्ठा bio_vec tovec, fromvec;
	काष्ठा bvec_iter iter;
	/*
	 * The bio of @from is created by bounce, so we can iterate
	 * its bvec from start to end, but the @from->bi_iter can't be
	 * trusted because it might be changed by splitting.
	 */
	काष्ठा bvec_iter from_iter = BVEC_ITER_ALL_INIT;

	bio_क्रम_each_segment(tovec, to, iter) अणु
		fromvec = bio_iter_iovec(from, from_iter);
		अगर (tovec.bv_page != fromvec.bv_page) अणु
			/*
			 * fromvec->bv_offset and fromvec->bv_len might have
			 * been modअगरied by the block layer, so use the original
			 * copy, bounce_copy_vec alपढ़ोy uses tovec->bv_len
			 */
			vfrom = page_address(fromvec.bv_page) +
				tovec.bv_offset;

			bounce_copy_vec(&tovec, vfrom);
			flush_dcache_page(tovec.bv_page);
		पूर्ण
		bio_advance_iter(from, &from_iter, tovec.bv_len);
	पूर्ण
पूर्ण

अटल व्योम bounce_end_io(काष्ठा bio *bio)
अणु
	काष्ठा bio *bio_orig = bio->bi_निजी;
	काष्ठा bio_vec *bvec, orig_vec;
	काष्ठा bvec_iter orig_iter = bio_orig->bi_iter;
	काष्ठा bvec_iter_all iter_all;

	/*
	 * मुक्त up bounce indirect pages used
	 */
	bio_क्रम_each_segment_all(bvec, bio, iter_all) अणु
		orig_vec = bio_iter_iovec(bio_orig, orig_iter);
		अगर (bvec->bv_page != orig_vec.bv_page) अणु
			dec_zone_page_state(bvec->bv_page, NR_BOUNCE);
			mempool_मुक्त(bvec->bv_page, &page_pool);
		पूर्ण
		bio_advance_iter(bio_orig, &orig_iter, orig_vec.bv_len);
	पूर्ण

	bio_orig->bi_status = bio->bi_status;
	bio_endio(bio_orig);
	bio_put(bio);
पूर्ण

अटल व्योम bounce_end_io_ग_लिखो(काष्ठा bio *bio)
अणु
	bounce_end_io(bio);
पूर्ण

अटल व्योम bounce_end_io_पढ़ो(काष्ठा bio *bio)
अणु
	काष्ठा bio *bio_orig = bio->bi_निजी;

	अगर (!bio->bi_status)
		copy_to_high_bio_irq(bio_orig, bio);

	bounce_end_io(bio);
पूर्ण

अटल काष्ठा bio *bounce_clone_bio(काष्ठा bio *bio_src)
अणु
	काष्ठा bvec_iter iter;
	काष्ठा bio_vec bv;
	काष्ठा bio *bio;

	/*
	 * Pre immutable biovecs, __bio_clone() used to just करो a स_नकल from
	 * bio_src->bi_io_vec to bio->bi_io_vec.
	 *
	 * We can't करो that anymore, because:
	 *
	 *  - The poपूर्णांक of cloning the biovec is to produce a bio with a biovec
	 *    the caller can modअगरy: bi_idx and bi_bvec_करोne should be 0.
	 *
	 *  - The original bio could've had more than BIO_MAX_VECS biovecs; अगर
	 *    we tried to clone the whole thing bio_alloc_bioset() would fail.
	 *    But the clone should succeed as दीर्घ as the number of biovecs we
	 *    actually need to allocate is fewer than BIO_MAX_VECS.
	 *
	 *  - Lastly, bi_vcnt should not be looked at or relied upon by code
	 *    that करोes not own the bio - reason being drivers करोn't use it क्रम
	 *    iterating over the biovec anymore, so expecting it to be kept up
	 *    to date (i.e. क्रम clones that share the parent biovec) is just
	 *    asking क्रम trouble and would क्रमce extra work on
	 *    __bio_clone_fast() anyways.
	 */
	bio = bio_alloc_bioset(GFP_NOIO, bio_segments(bio_src),
			       &bounce_bio_set);
	bio->bi_bdev		= bio_src->bi_bdev;
	अगर (bio_flagged(bio_src, BIO_REMAPPED))
		bio_set_flag(bio, BIO_REMAPPED);
	bio->bi_opf		= bio_src->bi_opf;
	bio->bi_ioprio		= bio_src->bi_ioprio;
	bio->bi_ग_लिखो_hपूर्णांक	= bio_src->bi_ग_लिखो_hपूर्णांक;
	bio->bi_iter.bi_sector	= bio_src->bi_iter.bi_sector;
	bio->bi_iter.bi_size	= bio_src->bi_iter.bi_size;

	चयन (bio_op(bio)) अणु
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_SECURE_ERASE:
	हाल REQ_OP_WRITE_ZEROES:
		अवरोध;
	हाल REQ_OP_WRITE_SAME:
		bio->bi_io_vec[bio->bi_vcnt++] = bio_src->bi_io_vec[0];
		अवरोध;
	शेष:
		bio_क्रम_each_segment(bv, bio_src, iter)
			bio->bi_io_vec[bio->bi_vcnt++] = bv;
		अवरोध;
	पूर्ण

	अगर (bio_crypt_clone(bio, bio_src, GFP_NOIO) < 0)
		जाओ err_put;

	अगर (bio_पूर्णांकegrity(bio_src) &&
	    bio_पूर्णांकegrity_clone(bio, bio_src, GFP_NOIO) < 0)
		जाओ err_put;

	bio_clone_blkg_association(bio, bio_src);
	blkcg_bio_issue_init(bio);

	वापस bio;

err_put:
	bio_put(bio);
	वापस शून्य;
पूर्ण

व्योम __blk_queue_bounce(काष्ठा request_queue *q, काष्ठा bio **bio_orig)
अणु
	काष्ठा bio *bio;
	पूर्णांक rw = bio_data_dir(*bio_orig);
	काष्ठा bio_vec *to, from;
	काष्ठा bvec_iter iter;
	अचिन्हित i = 0;
	bool bounce = false;
	पूर्णांक sectors = 0;

	bio_क्रम_each_segment(from, *bio_orig, iter) अणु
		अगर (i++ < BIO_MAX_VECS)
			sectors += from.bv_len >> 9;
		अगर (PageHighMem(from.bv_page))
			bounce = true;
	पूर्ण
	अगर (!bounce)
		वापस;

	अगर (sectors < bio_sectors(*bio_orig)) अणु
		bio = bio_split(*bio_orig, sectors, GFP_NOIO, &bounce_bio_split);
		bio_chain(bio, *bio_orig);
		submit_bio_noacct(*bio_orig);
		*bio_orig = bio;
	पूर्ण
	bio = bounce_clone_bio(*bio_orig);

	/*
	 * Bvec table can't be updated by bio_क्रम_each_segment_all(),
	 * so retrieve bvec from the table directly. This way is safe
	 * because the 'bio' is single-page bvec.
	 */
	क्रम (i = 0, to = bio->bi_io_vec; i < bio->bi_vcnt; to++, i++) अणु
		काष्ठा page *page = to->bv_page;

		अगर (!PageHighMem(page))
			जारी;

		to->bv_page = mempool_alloc(&page_pool, GFP_NOIO);
		inc_zone_page_state(to->bv_page, NR_BOUNCE);

		अगर (rw == WRITE) अणु
			अक्षर *vto, *vfrom;

			flush_dcache_page(page);

			vto = page_address(to->bv_page) + to->bv_offset;
			vfrom = kmap_atomic(page) + to->bv_offset;
			स_नकल(vto, vfrom, to->bv_len);
			kunmap_atomic(vfrom);
		पूर्ण
	पूर्ण

	trace_block_bio_bounce(*bio_orig);

	bio->bi_flags |= (1 << BIO_BOUNCED);

	अगर (rw == READ)
		bio->bi_end_io = bounce_end_io_पढ़ो;
	अन्यथा
		bio->bi_end_io = bounce_end_io_ग_लिखो;

	bio->bi_निजी = *bio_orig;
	*bio_orig = bio;
पूर्ण
