<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions related to generic helpers functions
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/scatterlist.h>

#समावेश "blk.h"

काष्ठा bio *blk_next_bio(काष्ठा bio *bio, अचिन्हित पूर्णांक nr_pages, gfp_t gfp)
अणु
	काष्ठा bio *new = bio_alloc(gfp, nr_pages);

	अगर (bio) अणु
		bio_chain(bio, new);
		submit_bio(bio);
	पूर्ण

	वापस new;
पूर्ण

पूर्णांक __blkdev_issue_discard(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, पूर्णांक flags,
		काष्ठा bio **biop)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	काष्ठा bio *bio = *biop;
	अचिन्हित पूर्णांक op;
	sector_t bs_mask, part_offset = 0;

	अगर (!q)
		वापस -ENXIO;

	अगर (bdev_पढ़ो_only(bdev))
		वापस -EPERM;

	अगर (flags & BLKDEV_DISCARD_SECURE) अणु
		अगर (!blk_queue_secure_erase(q))
			वापस -EOPNOTSUPP;
		op = REQ_OP_SECURE_ERASE;
	पूर्ण अन्यथा अणु
		अगर (!blk_queue_discard(q))
			वापस -EOPNOTSUPP;
		op = REQ_OP_DISCARD;
	पूर्ण

	/* In हाल the discard granularity isn't set by buggy device driver */
	अगर (WARN_ON_ONCE(!q->limits.discard_granularity)) अणु
		अक्षर dev_name[BDEVNAME_SIZE];

		bdevname(bdev, dev_name);
		pr_err_ratelimited("%s: Error: discard_granularity is 0.\n", dev_name);
		वापस -EOPNOTSUPP;
	पूर्ण

	bs_mask = (bdev_logical_block_size(bdev) >> 9) - 1;
	अगर ((sector | nr_sects) & bs_mask)
		वापस -EINVAL;

	अगर (!nr_sects)
		वापस -EINVAL;

	/* In हाल the discard request is in a partition */
	अगर (bdev_is_partition(bdev))
		part_offset = bdev->bd_start_sect;

	जबतक (nr_sects) अणु
		sector_t granularity_aligned_lba, req_sects;
		sector_t sector_mapped = sector + part_offset;

		granularity_aligned_lba = round_up(sector_mapped,
				q->limits.discard_granularity >> SECTOR_SHIFT);

		/*
		 * Check whether the discard bio starts at a discard_granularity
		 * aligned LBA,
		 * - If no: set (granularity_aligned_lba - sector_mapped) to
		 *   bi_size of the first split bio, then the second bio will
		 *   start at a discard_granularity aligned LBA on the device.
		 * - If yes: use bio_aligned_discard_max_sectors() as the max
		 *   possible bi_size of the first split bio. Then when this bio
		 *   is split in device drive, the split ones are very probably
		 *   to be aligned to discard_granularity of the device's queue.
		 */
		अगर (granularity_aligned_lba == sector_mapped)
			req_sects = min_t(sector_t, nr_sects,
					  bio_aligned_discard_max_sectors(q));
		अन्यथा
			req_sects = min_t(sector_t, nr_sects,
					  granularity_aligned_lba - sector_mapped);

		WARN_ON_ONCE((req_sects << 9) > अच_पूर्णांक_उच्च);

		bio = blk_next_bio(bio, 0, gfp_mask);
		bio->bi_iter.bi_sector = sector;
		bio_set_dev(bio, bdev);
		bio_set_op_attrs(bio, op, 0);

		bio->bi_iter.bi_size = req_sects << 9;
		sector += req_sects;
		nr_sects -= req_sects;

		/*
		 * We can loop क्रम a दीर्घ समय in here, अगर someone करोes
		 * full device discards (like mkfs). Be nice and allow
		 * us to schedule out to aव्योम softlocking अगर preempt
		 * is disabled.
		 */
		cond_resched();
	पूर्ण

	*biop = bio;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(__blkdev_issue_discard);

/**
 * blkdev_issue_discard - queue a discard
 * @bdev:	blockdev to issue discard क्रम
 * @sector:	start sector
 * @nr_sects:	number of sectors to discard
 * @gfp_mask:	memory allocation flags (क्रम bio_alloc)
 * @flags:	BLKDEV_DISCARD_* flags to control behaviour
 *
 * Description:
 *    Issue a discard request क्रम the sectors in question.
 */
पूर्णांक blkdev_issue_discard(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, अचिन्हित दीर्घ flags)
अणु
	काष्ठा bio *bio = शून्य;
	काष्ठा blk_plug plug;
	पूर्णांक ret;

	blk_start_plug(&plug);
	ret = __blkdev_issue_discard(bdev, sector, nr_sects, gfp_mask, flags,
			&bio);
	अगर (!ret && bio) अणु
		ret = submit_bio_रुको(bio);
		अगर (ret == -EOPNOTSUPP)
			ret = 0;
		bio_put(bio);
	पूर्ण
	blk_finish_plug(&plug);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(blkdev_issue_discard);

/**
 * __blkdev_issue_ग_लिखो_same - generate number of bios with same page
 * @bdev:	target blockdev
 * @sector:	start sector
 * @nr_sects:	number of sectors to ग_लिखो
 * @gfp_mask:	memory allocation flags (क्रम bio_alloc)
 * @page:	page containing data to ग_लिखो
 * @biop:	poपूर्णांकer to anchor bio
 *
 * Description:
 *  Generate and issue number of bios(REQ_OP_WRITE_SAME) with same page.
 */
अटल पूर्णांक __blkdev_issue_ग_लिखो_same(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, काष्ठा page *page,
		काष्ठा bio **biop)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	अचिन्हित पूर्णांक max_ग_लिखो_same_sectors;
	काष्ठा bio *bio = *biop;
	sector_t bs_mask;

	अगर (!q)
		वापस -ENXIO;

	अगर (bdev_पढ़ो_only(bdev))
		वापस -EPERM;

	bs_mask = (bdev_logical_block_size(bdev) >> 9) - 1;
	अगर ((sector | nr_sects) & bs_mask)
		वापस -EINVAL;

	अगर (!bdev_ग_लिखो_same(bdev))
		वापस -EOPNOTSUPP;

	/* Ensure that max_ग_लिखो_same_sectors करोesn't overflow bi_size */
	max_ग_लिखो_same_sectors = bio_allowed_max_sectors(q);

	जबतक (nr_sects) अणु
		bio = blk_next_bio(bio, 1, gfp_mask);
		bio->bi_iter.bi_sector = sector;
		bio_set_dev(bio, bdev);
		bio->bi_vcnt = 1;
		bio->bi_io_vec->bv_page = page;
		bio->bi_io_vec->bv_offset = 0;
		bio->bi_io_vec->bv_len = bdev_logical_block_size(bdev);
		bio_set_op_attrs(bio, REQ_OP_WRITE_SAME, 0);

		अगर (nr_sects > max_ग_लिखो_same_sectors) अणु
			bio->bi_iter.bi_size = max_ग_लिखो_same_sectors << 9;
			nr_sects -= max_ग_लिखो_same_sectors;
			sector += max_ग_लिखो_same_sectors;
		पूर्ण अन्यथा अणु
			bio->bi_iter.bi_size = nr_sects << 9;
			nr_sects = 0;
		पूर्ण
		cond_resched();
	पूर्ण

	*biop = bio;
	वापस 0;
पूर्ण

/**
 * blkdev_issue_ग_लिखो_same - queue a ग_लिखो same operation
 * @bdev:	target blockdev
 * @sector:	start sector
 * @nr_sects:	number of sectors to ग_लिखो
 * @gfp_mask:	memory allocation flags (क्रम bio_alloc)
 * @page:	page containing data
 *
 * Description:
 *    Issue a ग_लिखो same request क्रम the sectors in question.
 */
पूर्णांक blkdev_issue_ग_लिखो_same(काष्ठा block_device *bdev, sector_t sector,
				sector_t nr_sects, gfp_t gfp_mask,
				काष्ठा page *page)
अणु
	काष्ठा bio *bio = शून्य;
	काष्ठा blk_plug plug;
	पूर्णांक ret;

	blk_start_plug(&plug);
	ret = __blkdev_issue_ग_लिखो_same(bdev, sector, nr_sects, gfp_mask, page,
			&bio);
	अगर (ret == 0 && bio) अणु
		ret = submit_bio_रुको(bio);
		bio_put(bio);
	पूर्ण
	blk_finish_plug(&plug);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(blkdev_issue_ग_लिखो_same);

अटल पूर्णांक __blkdev_issue_ग_लिखो_zeroes(काष्ठा block_device *bdev,
		sector_t sector, sector_t nr_sects, gfp_t gfp_mask,
		काष्ठा bio **biop, अचिन्हित flags)
अणु
	काष्ठा bio *bio = *biop;
	अचिन्हित पूर्णांक max_ग_लिखो_zeroes_sectors;
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (!q)
		वापस -ENXIO;

	अगर (bdev_पढ़ो_only(bdev))
		वापस -EPERM;

	/* Ensure that max_ग_लिखो_zeroes_sectors करोesn't overflow bi_size */
	max_ग_लिखो_zeroes_sectors = bdev_ग_लिखो_zeroes_sectors(bdev);

	अगर (max_ग_लिखो_zeroes_sectors == 0)
		वापस -EOPNOTSUPP;

	जबतक (nr_sects) अणु
		bio = blk_next_bio(bio, 0, gfp_mask);
		bio->bi_iter.bi_sector = sector;
		bio_set_dev(bio, bdev);
		bio->bi_opf = REQ_OP_WRITE_ZEROES;
		अगर (flags & BLKDEV_ZERO_NOUNMAP)
			bio->bi_opf |= REQ_NOUNMAP;

		अगर (nr_sects > max_ग_लिखो_zeroes_sectors) अणु
			bio->bi_iter.bi_size = max_ग_लिखो_zeroes_sectors << 9;
			nr_sects -= max_ग_लिखो_zeroes_sectors;
			sector += max_ग_लिखो_zeroes_sectors;
		पूर्ण अन्यथा अणु
			bio->bi_iter.bi_size = nr_sects << 9;
			nr_sects = 0;
		पूर्ण
		cond_resched();
	पूर्ण

	*biop = bio;
	वापस 0;
पूर्ण

/*
 * Convert a number of 512B sectors to a number of pages.
 * The result is limited to a number of pages that can fit पूर्णांकo a BIO.
 * Also make sure that the result is always at least 1 (page) क्रम the हालs
 * where nr_sects is lower than the number of sectors in a page.
 */
अटल अचिन्हित पूर्णांक __blkdev_sectors_to_bio_pages(sector_t nr_sects)
अणु
	sector_t pages = DIV_ROUND_UP_SECTOR_T(nr_sects, PAGE_SIZE / 512);

	वापस min(pages, (sector_t)BIO_MAX_VECS);
पूर्ण

अटल पूर्णांक __blkdev_issue_zero_pages(काष्ठा block_device *bdev,
		sector_t sector, sector_t nr_sects, gfp_t gfp_mask,
		काष्ठा bio **biop)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);
	काष्ठा bio *bio = *biop;
	पूर्णांक bi_size = 0;
	अचिन्हित पूर्णांक sz;

	अगर (!q)
		वापस -ENXIO;

	अगर (bdev_पढ़ो_only(bdev))
		वापस -EPERM;

	जबतक (nr_sects != 0) अणु
		bio = blk_next_bio(bio, __blkdev_sectors_to_bio_pages(nr_sects),
				   gfp_mask);
		bio->bi_iter.bi_sector = sector;
		bio_set_dev(bio, bdev);
		bio_set_op_attrs(bio, REQ_OP_WRITE, 0);

		जबतक (nr_sects != 0) अणु
			sz = min((sector_t) PAGE_SIZE, nr_sects << 9);
			bi_size = bio_add_page(bio, ZERO_PAGE(0), sz, 0);
			nr_sects -= bi_size >> 9;
			sector += bi_size >> 9;
			अगर (bi_size < sz)
				अवरोध;
		पूर्ण
		cond_resched();
	पूर्ण

	*biop = bio;
	वापस 0;
पूर्ण

/**
 * __blkdev_issue_zeroout - generate number of zero filed ग_लिखो bios
 * @bdev:	blockdev to issue
 * @sector:	start sector
 * @nr_sects:	number of sectors to ग_लिखो
 * @gfp_mask:	memory allocation flags (क्रम bio_alloc)
 * @biop:	poपूर्णांकer to anchor bio
 * @flags:	controls detailed behavior
 *
 * Description:
 *  Zero-fill a block range, either using hardware offload or by explicitly
 *  writing zeroes to the device.
 *
 *  If a device is using logical block provisioning, the underlying space will
 *  not be released अगर %flags contains BLKDEV_ZERO_NOUNMAP.
 *
 *  If %flags contains BLKDEV_ZERO_NOFALLBACK, the function will वापस
 *  -EOPNOTSUPP अगर no explicit hardware offload क्रम zeroing is provided.
 */
पूर्णांक __blkdev_issue_zeroout(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, काष्ठा bio **biop,
		अचिन्हित flags)
अणु
	पूर्णांक ret;
	sector_t bs_mask;

	bs_mask = (bdev_logical_block_size(bdev) >> 9) - 1;
	अगर ((sector | nr_sects) & bs_mask)
		वापस -EINVAL;

	ret = __blkdev_issue_ग_लिखो_zeroes(bdev, sector, nr_sects, gfp_mask,
			biop, flags);
	अगर (ret != -EOPNOTSUPP || (flags & BLKDEV_ZERO_NOFALLBACK))
		वापस ret;

	वापस __blkdev_issue_zero_pages(bdev, sector, nr_sects, gfp_mask,
					 biop);
पूर्ण
EXPORT_SYMBOL(__blkdev_issue_zeroout);

/**
 * blkdev_issue_zeroout - zero-fill a block range
 * @bdev:	blockdev to ग_लिखो
 * @sector:	start sector
 * @nr_sects:	number of sectors to ग_लिखो
 * @gfp_mask:	memory allocation flags (क्रम bio_alloc)
 * @flags:	controls detailed behavior
 *
 * Description:
 *  Zero-fill a block range, either using hardware offload or by explicitly
 *  writing zeroes to the device.  See __blkdev_issue_zeroout() क्रम the
 *  valid values क्रम %flags.
 */
पूर्णांक blkdev_issue_zeroout(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, अचिन्हित flags)
अणु
	पूर्णांक ret = 0;
	sector_t bs_mask;
	काष्ठा bio *bio;
	काष्ठा blk_plug plug;
	bool try_ग_लिखो_zeroes = !!bdev_ग_लिखो_zeroes_sectors(bdev);

	bs_mask = (bdev_logical_block_size(bdev) >> 9) - 1;
	अगर ((sector | nr_sects) & bs_mask)
		वापस -EINVAL;

retry:
	bio = शून्य;
	blk_start_plug(&plug);
	अगर (try_ग_लिखो_zeroes) अणु
		ret = __blkdev_issue_ग_लिखो_zeroes(bdev, sector, nr_sects,
						  gfp_mask, &bio, flags);
	पूर्ण अन्यथा अगर (!(flags & BLKDEV_ZERO_NOFALLBACK)) अणु
		ret = __blkdev_issue_zero_pages(bdev, sector, nr_sects,
						gfp_mask, &bio);
	पूर्ण अन्यथा अणु
		/* No zeroing offload support */
		ret = -EOPNOTSUPP;
	पूर्ण
	अगर (ret == 0 && bio) अणु
		ret = submit_bio_रुको(bio);
		bio_put(bio);
	पूर्ण
	blk_finish_plug(&plug);
	अगर (ret && try_ग_लिखो_zeroes) अणु
		अगर (!(flags & BLKDEV_ZERO_NOFALLBACK)) अणु
			try_ग_लिखो_zeroes = false;
			जाओ retry;
		पूर्ण
		अगर (!bdev_ग_लिखो_zeroes_sectors(bdev)) अणु
			/*
			 * Zeroing offload support was indicated, but the
			 * device reported ILLEGAL REQUEST (क्रम some devices
			 * there is no non-deकाष्ठाive way to verअगरy whether
			 * WRITE ZEROES is actually supported).
			 */
			ret = -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(blkdev_issue_zeroout);
