<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions related to segment and merge handling
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/scatterlist.h>

#समावेश <trace/events/block.h>

#समावेश "blk.h"
#समावेश "blk-rq-qos.h"

अटल अंतरभूत bool bio_will_gap(काष्ठा request_queue *q,
		काष्ठा request *prev_rq, काष्ठा bio *prev, काष्ठा bio *next)
अणु
	काष्ठा bio_vec pb, nb;

	अगर (!bio_has_data(prev) || !queue_virt_boundary(q))
		वापस false;

	/*
	 * Don't merge अगर the 1st bio starts with non-zero offset, otherwise it
	 * is quite dअगरficult to respect the sg gap limit.  We work hard to
	 * merge a huge number of small single bios in हाल of mkfs.
	 */
	अगर (prev_rq)
		bio_get_first_bvec(prev_rq->bio, &pb);
	अन्यथा
		bio_get_first_bvec(prev, &pb);
	अगर (pb.bv_offset & queue_virt_boundary(q))
		वापस true;

	/*
	 * We करोn't need to worry about the situation that the merged segment
	 * ends in unaligned virt boundary:
	 *
	 * - अगर 'pb' ends aligned, the merged segment ends aligned
	 * - अगर 'pb' ends unaligned, the next bio must include
	 *   one single bvec of 'nb', otherwise the 'nb' can't
	 *   merge with 'pb'
	 */
	bio_get_last_bvec(prev, &pb);
	bio_get_first_bvec(next, &nb);
	अगर (biovec_phys_mergeable(q, &pb, &nb))
		वापस false;
	वापस __bvec_gap_to_prev(q, &pb, nb.bv_offset);
पूर्ण

अटल अंतरभूत bool req_gap_back_merge(काष्ठा request *req, काष्ठा bio *bio)
अणु
	वापस bio_will_gap(req->q, req, req->biotail, bio);
पूर्ण

अटल अंतरभूत bool req_gap_front_merge(काष्ठा request *req, काष्ठा bio *bio)
अणु
	वापस bio_will_gap(req->q, शून्य, bio, req->bio);
पूर्ण

अटल काष्ठा bio *blk_bio_discard_split(काष्ठा request_queue *q,
					 काष्ठा bio *bio,
					 काष्ठा bio_set *bs,
					 अचिन्हित *nsegs)
अणु
	अचिन्हित पूर्णांक max_discard_sectors, granularity;
	पूर्णांक alignment;
	sector_t पंचांगp;
	अचिन्हित split_sectors;

	*nsegs = 1;

	/* Zero-sector (unknown) and one-sector granularities are the same.  */
	granularity = max(q->limits.discard_granularity >> 9, 1U);

	max_discard_sectors = min(q->limits.max_discard_sectors,
			bio_allowed_max_sectors(q));
	max_discard_sectors -= max_discard_sectors % granularity;

	अगर (unlikely(!max_discard_sectors)) अणु
		/* XXX: warn */
		वापस शून्य;
	पूर्ण

	अगर (bio_sectors(bio) <= max_discard_sectors)
		वापस शून्य;

	split_sectors = max_discard_sectors;

	/*
	 * If the next starting sector would be misaligned, stop the discard at
	 * the previous aligned sector.
	 */
	alignment = (q->limits.discard_alignment >> 9) % granularity;

	पंचांगp = bio->bi_iter.bi_sector + split_sectors - alignment;
	पंचांगp = sector_भाग(पंचांगp, granularity);

	अगर (split_sectors > पंचांगp)
		split_sectors -= पंचांगp;

	वापस bio_split(bio, split_sectors, GFP_NOIO, bs);
पूर्ण

अटल काष्ठा bio *blk_bio_ग_लिखो_zeroes_split(काष्ठा request_queue *q,
		काष्ठा bio *bio, काष्ठा bio_set *bs, अचिन्हित *nsegs)
अणु
	*nsegs = 0;

	अगर (!q->limits.max_ग_लिखो_zeroes_sectors)
		वापस शून्य;

	अगर (bio_sectors(bio) <= q->limits.max_ग_लिखो_zeroes_sectors)
		वापस शून्य;

	वापस bio_split(bio, q->limits.max_ग_लिखो_zeroes_sectors, GFP_NOIO, bs);
पूर्ण

अटल काष्ठा bio *blk_bio_ग_लिखो_same_split(काष्ठा request_queue *q,
					    काष्ठा bio *bio,
					    काष्ठा bio_set *bs,
					    अचिन्हित *nsegs)
अणु
	*nsegs = 1;

	अगर (!q->limits.max_ग_लिखो_same_sectors)
		वापस शून्य;

	अगर (bio_sectors(bio) <= q->limits.max_ग_लिखो_same_sectors)
		वापस शून्य;

	वापस bio_split(bio, q->limits.max_ग_लिखो_same_sectors, GFP_NOIO, bs);
पूर्ण

/*
 * Return the maximum number of sectors from the start of a bio that may be
 * submitted as a single request to a block device. If enough sectors reमुख्य,
 * align the end to the physical block size. Otherwise align the end to the
 * logical block size. This approach minimizes the number of non-aligned
 * requests that are submitted to a block device अगर the start of a bio is not
 * aligned to a physical block boundary.
 */
अटल अंतरभूत अचिन्हित get_max_io_size(काष्ठा request_queue *q,
				       काष्ठा bio *bio)
अणु
	अचिन्हित sectors = blk_max_size_offset(q, bio->bi_iter.bi_sector, 0);
	अचिन्हित max_sectors = sectors;
	अचिन्हित pbs = queue_physical_block_size(q) >> SECTOR_SHIFT;
	अचिन्हित lbs = queue_logical_block_size(q) >> SECTOR_SHIFT;
	अचिन्हित start_offset = bio->bi_iter.bi_sector & (pbs - 1);

	max_sectors += start_offset;
	max_sectors &= ~(pbs - 1);
	अगर (max_sectors > start_offset)
		वापस max_sectors - start_offset;

	वापस sectors & ~(lbs - 1);
पूर्ण

अटल अंतरभूत अचिन्हित get_max_segment_size(स्थिर काष्ठा request_queue *q,
					    काष्ठा page *start_page,
					    अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ mask = queue_segment_boundary(q);

	offset = mask & (page_to_phys(start_page) + offset);

	/*
	 * overflow may be triggered in हाल of zero page physical address
	 * on 32bit arch, use queue's max segment size when that happens.
	 */
	वापस min_not_zero(mask - offset + 1,
			(अचिन्हित दीर्घ)queue_max_segment_size(q));
पूर्ण

/**
 * bvec_split_segs - verअगरy whether or not a bvec should be split in the middle
 * @q:        [in] request queue associated with the bio associated with @bv
 * @bv:       [in] bvec to examine
 * @nsegs:    [in,out] Number of segments in the bio being built. Incremented
 *            by the number of segments from @bv that may be appended to that
 *            bio without exceeding @max_segs
 * @sectors:  [in,out] Number of sectors in the bio being built. Incremented
 *            by the number of sectors from @bv that may be appended to that
 *            bio without exceeding @max_sectors
 * @max_segs: [in] upper bound क्रम *@nsegs
 * @max_sectors: [in] upper bound क्रम *@sectors
 *
 * When splitting a bio, it can happen that a bvec is encountered that is too
 * big to fit in a single segment and hence that it has to be split in the
 * middle. This function verअगरies whether or not that should happen. The value
 * %true is वापसed अगर and only अगर appending the entire @bv to a bio with
 * *@nsegs segments and *@sectors sectors would make that bio unacceptable क्रम
 * the block driver.
 */
अटल bool bvec_split_segs(स्थिर काष्ठा request_queue *q,
			    स्थिर काष्ठा bio_vec *bv, अचिन्हित *nsegs,
			    अचिन्हित *sectors, अचिन्हित max_segs,
			    अचिन्हित max_sectors)
अणु
	अचिन्हित max_len = (min(max_sectors, अच_पूर्णांक_उच्च >> 9) - *sectors) << 9;
	अचिन्हित len = min(bv->bv_len, max_len);
	अचिन्हित total_len = 0;
	अचिन्हित seg_size = 0;

	जबतक (len && *nsegs < max_segs) अणु
		seg_size = get_max_segment_size(q, bv->bv_page,
						bv->bv_offset + total_len);
		seg_size = min(seg_size, len);

		(*nsegs)++;
		total_len += seg_size;
		len -= seg_size;

		अगर ((bv->bv_offset + total_len) & queue_virt_boundary(q))
			अवरोध;
	पूर्ण

	*sectors += total_len >> 9;

	/* tell the caller to split the bvec अगर it is too big to fit */
	वापस len > 0 || bv->bv_len > max_len;
पूर्ण

/**
 * blk_bio_segment_split - split a bio in two bios
 * @q:    [in] request queue poपूर्णांकer
 * @bio:  [in] bio to be split
 * @bs:	  [in] bio set to allocate the clone from
 * @segs: [out] number of segments in the bio with the first half of the sectors
 *
 * Clone @bio, update the bi_iter of the clone to represent the first sectors
 * of @bio and update @bio->bi_iter to represent the reमुख्यing sectors. The
 * following is guaranteed क्रम the cloned bio:
 * - That it has at most get_max_io_size(@q, @bio) sectors.
 * - That it has at most queue_max_segments(@q) segments.
 *
 * Except क्रम discard requests the cloned bio will poपूर्णांक at the bi_io_vec of
 * the original bio. It is the responsibility of the caller to ensure that the
 * original bio is not मुक्तd beक्रमe the cloned bio. The caller is also
 * responsible क्रम ensuring that @bs is only destroyed after processing of the
 * split bio has finished.
 */
अटल काष्ठा bio *blk_bio_segment_split(काष्ठा request_queue *q,
					 काष्ठा bio *bio,
					 काष्ठा bio_set *bs,
					 अचिन्हित *segs)
अणु
	काष्ठा bio_vec bv, bvprv, *bvprvp = शून्य;
	काष्ठा bvec_iter iter;
	अचिन्हित nsegs = 0, sectors = 0;
	स्थिर अचिन्हित max_sectors = get_max_io_size(q, bio);
	स्थिर अचिन्हित max_segs = queue_max_segments(q);

	bio_क्रम_each_bvec(bv, bio, iter) अणु
		/*
		 * If the queue करोesn't support SG gaps and adding this
		 * offset would create a gap, disallow it.
		 */
		अगर (bvprvp && bvec_gap_to_prev(q, bvprvp, bv.bv_offset))
			जाओ split;

		अगर (nsegs < max_segs &&
		    sectors + (bv.bv_len >> 9) <= max_sectors &&
		    bv.bv_offset + bv.bv_len <= PAGE_SIZE) अणु
			nsegs++;
			sectors += bv.bv_len >> 9;
		पूर्ण अन्यथा अगर (bvec_split_segs(q, &bv, &nsegs, &sectors, max_segs,
					 max_sectors)) अणु
			जाओ split;
		पूर्ण

		bvprv = bv;
		bvprvp = &bvprv;
	पूर्ण

	*segs = nsegs;
	वापस शून्य;
split:
	*segs = nsegs;

	/*
	 * Bio splitting may cause subtle trouble such as hang when करोing sync
	 * iopoll in direct IO routine. Given perक्रमmance gain of iopoll क्रम
	 * big IO can be trival, disable iopoll when split needed.
	 */
	bio->bi_opf &= ~REQ_HIPRI;

	वापस bio_split(bio, sectors, GFP_NOIO, bs);
पूर्ण

/**
 * __blk_queue_split - split a bio and submit the second half
 * @bio:     [in, out] bio to be split
 * @nr_segs: [out] number of segments in the first bio
 *
 * Split a bio पूर्णांकo two bios, chain the two bios, submit the second half and
 * store a poपूर्णांकer to the first half in *@bio. If the second bio is still too
 * big it will be split by a recursive call to this function. Since this
 * function may allocate a new bio from q->bio_split, it is the responsibility
 * of the caller to ensure that q->bio_split is only released after processing
 * of the split bio has finished.
 */
व्योम __blk_queue_split(काष्ठा bio **bio, अचिन्हित पूर्णांक *nr_segs)
अणु
	काष्ठा request_queue *q = (*bio)->bi_bdev->bd_disk->queue;
	काष्ठा bio *split = शून्य;

	चयन (bio_op(*bio)) अणु
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_SECURE_ERASE:
		split = blk_bio_discard_split(q, *bio, &q->bio_split, nr_segs);
		अवरोध;
	हाल REQ_OP_WRITE_ZEROES:
		split = blk_bio_ग_लिखो_zeroes_split(q, *bio, &q->bio_split,
				nr_segs);
		अवरोध;
	हाल REQ_OP_WRITE_SAME:
		split = blk_bio_ग_लिखो_same_split(q, *bio, &q->bio_split,
				nr_segs);
		अवरोध;
	शेष:
		/*
		 * All drivers must accept single-segments bios that are <=
		 * PAGE_SIZE.  This is a quick and dirty check that relies on
		 * the fact that bi_io_vec[0] is always valid अगर a bio has data.
		 * The check might lead to occasional false negatives when bios
		 * are cloned, but compared to the perक्रमmance impact of cloned
		 * bios themselves the loop below करोesn't matter anyway.
		 */
		अगर (!q->limits.chunk_sectors &&
		    (*bio)->bi_vcnt == 1 &&
		    ((*bio)->bi_io_vec[0].bv_len +
		     (*bio)->bi_io_vec[0].bv_offset) <= PAGE_SIZE) अणु
			*nr_segs = 1;
			अवरोध;
		पूर्ण
		split = blk_bio_segment_split(q, *bio, &q->bio_split, nr_segs);
		अवरोध;
	पूर्ण

	अगर (split) अणु
		/* there isn't chance to merge the splitted bio */
		split->bi_opf |= REQ_NOMERGE;

		bio_chain(split, *bio);
		trace_block_split(split, (*bio)->bi_iter.bi_sector);
		submit_bio_noacct(*bio);
		*bio = split;
	पूर्ण
पूर्ण

/**
 * blk_queue_split - split a bio and submit the second half
 * @bio: [in, out] bio to be split
 *
 * Split a bio पूर्णांकo two bios, chains the two bios, submit the second half and
 * store a poपूर्णांकer to the first half in *@bio. Since this function may allocate
 * a new bio from q->bio_split, it is the responsibility of the caller to ensure
 * that q->bio_split is only released after processing of the split bio has
 * finished.
 */
व्योम blk_queue_split(काष्ठा bio **bio)
अणु
	अचिन्हित पूर्णांक nr_segs;

	__blk_queue_split(bio, &nr_segs);
पूर्ण
EXPORT_SYMBOL(blk_queue_split);

अचिन्हित पूर्णांक blk_recalc_rq_segments(काष्ठा request *rq)
अणु
	अचिन्हित पूर्णांक nr_phys_segs = 0;
	अचिन्हित पूर्णांक nr_sectors = 0;
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bv;

	अगर (!rq->bio)
		वापस 0;

	चयन (bio_op(rq->bio)) अणु
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_SECURE_ERASE:
		अगर (queue_max_discard_segments(rq->q) > 1) अणु
			काष्ठा bio *bio = rq->bio;

			क्रम_each_bio(bio)
				nr_phys_segs++;
			वापस nr_phys_segs;
		पूर्ण
		वापस 1;
	हाल REQ_OP_WRITE_ZEROES:
		वापस 0;
	हाल REQ_OP_WRITE_SAME:
		वापस 1;
	पूर्ण

	rq_क्रम_each_bvec(bv, rq, iter)
		bvec_split_segs(rq->q, &bv, &nr_phys_segs, &nr_sectors,
				अच_पूर्णांक_उच्च, अच_पूर्णांक_उच्च);
	वापस nr_phys_segs;
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *blk_next_sg(काष्ठा scatterlist **sg,
		काष्ठा scatterlist *sglist)
अणु
	अगर (!*sg)
		वापस sglist;

	/*
	 * If the driver previously mapped a लघुer list, we could see a
	 * termination bit prematurely unless it fully inits the sg table
	 * on each mapping. We KNOW that there must be more entries here
	 * or the driver would be buggy, so क्रमce clear the termination bit
	 * to aव्योम करोing a full sg_init_table() in drivers क्रम each command.
	 */
	sg_unmark_end(*sg);
	वापस sg_next(*sg);
पूर्ण

अटल अचिन्हित blk_bvec_map_sg(काष्ठा request_queue *q,
		काष्ठा bio_vec *bvec, काष्ठा scatterlist *sglist,
		काष्ठा scatterlist **sg)
अणु
	अचिन्हित nbytes = bvec->bv_len;
	अचिन्हित nsegs = 0, total = 0;

	जबतक (nbytes > 0) अणु
		अचिन्हित offset = bvec->bv_offset + total;
		अचिन्हित len = min(get_max_segment_size(q, bvec->bv_page,
					offset), nbytes);
		काष्ठा page *page = bvec->bv_page;

		/*
		 * Unक्रमtunately a fair number of drivers barf on scatterlists
		 * that have an offset larger than PAGE_SIZE, despite other
		 * subप्रणालीs dealing with that invariant just fine.  For now
		 * stick to the legacy क्रमmat where we never present those from
		 * the block layer, but the code below should be हटाओd once
		 * these offenders (mostly MMC/SD drivers) are fixed.
		 */
		page += (offset >> PAGE_SHIFT);
		offset &= ~PAGE_MASK;

		*sg = blk_next_sg(sg, sglist);
		sg_set_page(*sg, page, len, offset);

		total += len;
		nbytes -= len;
		nsegs++;
	पूर्ण

	वापस nsegs;
पूर्ण

अटल अंतरभूत पूर्णांक __blk_bvec_map_sg(काष्ठा bio_vec bv,
		काष्ठा scatterlist *sglist, काष्ठा scatterlist **sg)
अणु
	*sg = blk_next_sg(sg, sglist);
	sg_set_page(*sg, bv.bv_page, bv.bv_len, bv.bv_offset);
	वापस 1;
पूर्ण

/* only try to merge bvecs पूर्णांकo one sg अगर they are from two bios */
अटल अंतरभूत bool
__blk_segment_map_sg_merge(काष्ठा request_queue *q, काष्ठा bio_vec *bvec,
			   काष्ठा bio_vec *bvprv, काष्ठा scatterlist **sg)
अणु

	पूर्णांक nbytes = bvec->bv_len;

	अगर (!*sg)
		वापस false;

	अगर ((*sg)->length + nbytes > queue_max_segment_size(q))
		वापस false;

	अगर (!biovec_phys_mergeable(q, bvprv, bvec))
		वापस false;

	(*sg)->length += nbytes;

	वापस true;
पूर्ण

अटल पूर्णांक __blk_bios_map_sg(काष्ठा request_queue *q, काष्ठा bio *bio,
			     काष्ठा scatterlist *sglist,
			     काष्ठा scatterlist **sg)
अणु
	काष्ठा bio_vec bvec, bvprv = अणु शून्य पूर्ण;
	काष्ठा bvec_iter iter;
	पूर्णांक nsegs = 0;
	bool new_bio = false;

	क्रम_each_bio(bio) अणु
		bio_क्रम_each_bvec(bvec, bio, iter) अणु
			/*
			 * Only try to merge bvecs from two bios given we
			 * have करोne bio पूर्णांकernal merge when adding pages
			 * to bio
			 */
			अगर (new_bio &&
			    __blk_segment_map_sg_merge(q, &bvec, &bvprv, sg))
				जाओ next_bvec;

			अगर (bvec.bv_offset + bvec.bv_len <= PAGE_SIZE)
				nsegs += __blk_bvec_map_sg(bvec, sglist, sg);
			अन्यथा
				nsegs += blk_bvec_map_sg(q, &bvec, sglist, sg);
 next_bvec:
			new_bio = false;
		पूर्ण
		अगर (likely(bio->bi_iter.bi_size)) अणु
			bvprv = bvec;
			new_bio = true;
		पूर्ण
	पूर्ण

	वापस nsegs;
पूर्ण

/*
 * map a request to scatterlist, वापस number of sg entries setup. Caller
 * must make sure sg can hold rq->nr_phys_segments entries
 */
पूर्णांक __blk_rq_map_sg(काष्ठा request_queue *q, काष्ठा request *rq,
		काष्ठा scatterlist *sglist, काष्ठा scatterlist **last_sg)
अणु
	पूर्णांक nsegs = 0;

	अगर (rq->rq_flags & RQF_SPECIAL_PAYLOAD)
		nsegs = __blk_bvec_map_sg(rq->special_vec, sglist, last_sg);
	अन्यथा अगर (rq->bio && bio_op(rq->bio) == REQ_OP_WRITE_SAME)
		nsegs = __blk_bvec_map_sg(bio_iovec(rq->bio), sglist, last_sg);
	अन्यथा अगर (rq->bio)
		nsegs = __blk_bios_map_sg(q, rq->bio, sglist, last_sg);

	अगर (*last_sg)
		sg_mark_end(*last_sg);

	/*
	 * Something must have been wrong अगर the figured number of
	 * segment is bigger than number of req's physical segments
	 */
	WARN_ON(nsegs > blk_rq_nr_phys_segments(rq));

	वापस nsegs;
पूर्ण
EXPORT_SYMBOL(__blk_rq_map_sg);

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_get_max_segments(काष्ठा request *rq)
अणु
	अगर (req_op(rq) == REQ_OP_DISCARD)
		वापस queue_max_discard_segments(rq->q);
	वापस queue_max_segments(rq->q);
पूर्ण

अटल अंतरभूत पूर्णांक ll_new_hw_segment(काष्ठा request *req, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_phys_segs)
अणु
	अगर (req->nr_phys_segments + nr_phys_segs > blk_rq_get_max_segments(req))
		जाओ no_merge;

	अगर (blk_पूर्णांकegrity_merge_bio(req->q, req, bio) == false)
		जाओ no_merge;

	/*
	 * This will क्रमm the start of a new hw segment.  Bump both
	 * counters.
	 */
	req->nr_phys_segments += nr_phys_segs;
	वापस 1;

no_merge:
	req_set_nomerge(req->q, req);
	वापस 0;
पूर्ण

पूर्णांक ll_back_merge_fn(काष्ठा request *req, काष्ठा bio *bio, अचिन्हित पूर्णांक nr_segs)
अणु
	अगर (req_gap_back_merge(req, bio))
		वापस 0;
	अगर (blk_पूर्णांकegrity_rq(req) &&
	    पूर्णांकegrity_req_gap_back_merge(req, bio))
		वापस 0;
	अगर (!bio_crypt_ctx_back_mergeable(req, bio))
		वापस 0;
	अगर (blk_rq_sectors(req) + bio_sectors(bio) >
	    blk_rq_get_max_sectors(req, blk_rq_pos(req))) अणु
		req_set_nomerge(req->q, req);
		वापस 0;
	पूर्ण

	वापस ll_new_hw_segment(req, bio, nr_segs);
पूर्ण

अटल पूर्णांक ll_front_merge_fn(काष्ठा request *req, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs)
अणु
	अगर (req_gap_front_merge(req, bio))
		वापस 0;
	अगर (blk_पूर्णांकegrity_rq(req) &&
	    पूर्णांकegrity_req_gap_front_merge(req, bio))
		वापस 0;
	अगर (!bio_crypt_ctx_front_mergeable(req, bio))
		वापस 0;
	अगर (blk_rq_sectors(req) + bio_sectors(bio) >
	    blk_rq_get_max_sectors(req, bio->bi_iter.bi_sector)) अणु
		req_set_nomerge(req->q, req);
		वापस 0;
	पूर्ण

	वापस ll_new_hw_segment(req, bio, nr_segs);
पूर्ण

अटल bool req_attempt_discard_merge(काष्ठा request_queue *q, काष्ठा request *req,
		काष्ठा request *next)
अणु
	अचिन्हित लघु segments = blk_rq_nr_discard_segments(req);

	अगर (segments >= queue_max_discard_segments(q))
		जाओ no_merge;
	अगर (blk_rq_sectors(req) + bio_sectors(next->bio) >
	    blk_rq_get_max_sectors(req, blk_rq_pos(req)))
		जाओ no_merge;

	req->nr_phys_segments = segments + blk_rq_nr_discard_segments(next);
	वापस true;
no_merge:
	req_set_nomerge(q, req);
	वापस false;
पूर्ण

अटल पूर्णांक ll_merge_requests_fn(काष्ठा request_queue *q, काष्ठा request *req,
				काष्ठा request *next)
अणु
	पूर्णांक total_phys_segments;

	अगर (req_gap_back_merge(req, next->bio))
		वापस 0;

	/*
	 * Will it become too large?
	 */
	अगर ((blk_rq_sectors(req) + blk_rq_sectors(next)) >
	    blk_rq_get_max_sectors(req, blk_rq_pos(req)))
		वापस 0;

	total_phys_segments = req->nr_phys_segments + next->nr_phys_segments;
	अगर (total_phys_segments > blk_rq_get_max_segments(req))
		वापस 0;

	अगर (blk_पूर्णांकegrity_merge_rq(q, req, next) == false)
		वापस 0;

	अगर (!bio_crypt_ctx_merge_rq(req, next))
		वापस 0;

	/* Merge is OK... */
	req->nr_phys_segments = total_phys_segments;
	वापस 1;
पूर्ण

/**
 * blk_rq_set_mixed_merge - mark a request as mixed merge
 * @rq: request to mark as mixed merge
 *
 * Description:
 *     @rq is about to be mixed merged.  Make sure the attributes
 *     which can be mixed are set in each bio and mark @rq as mixed
 *     merged.
 */
व्योम blk_rq_set_mixed_merge(काष्ठा request *rq)
अणु
	अचिन्हित पूर्णांक ff = rq->cmd_flags & REQ_FAILFAST_MASK;
	काष्ठा bio *bio;

	अगर (rq->rq_flags & RQF_MIXED_MERGE)
		वापस;

	/*
	 * @rq will no दीर्घer represent mixable attributes क्रम all the
	 * contained bios.  It will just track those of the first one.
	 * Distributes the attributs to each bio.
	 */
	क्रम (bio = rq->bio; bio; bio = bio->bi_next) अणु
		WARN_ON_ONCE((bio->bi_opf & REQ_FAILFAST_MASK) &&
			     (bio->bi_opf & REQ_FAILFAST_MASK) != ff);
		bio->bi_opf |= ff;
	पूर्ण
	rq->rq_flags |= RQF_MIXED_MERGE;
पूर्ण

अटल व्योम blk_account_io_merge_request(काष्ठा request *req)
अणु
	अगर (blk_करो_io_stat(req)) अणु
		part_stat_lock();
		part_stat_inc(req->part, merges[op_stat_group(req_op(req))]);
		part_stat_unlock();
	पूर्ण
पूर्ण

/*
 * Two हालs of handling DISCARD merge:
 * If max_discard_segments > 1, the driver takes every bio
 * as a range and send them to controller together. The ranges
 * needn't to be contiguous.
 * Otherwise, the bios/requests will be handled as same as
 * others which should be contiguous.
 */
अटल अंतरभूत bool blk_discard_mergable(काष्ठा request *req)
अणु
	अगर (req_op(req) == REQ_OP_DISCARD &&
	    queue_max_discard_segments(req->q) > 1)
		वापस true;
	वापस false;
पूर्ण

अटल क्रमागत elv_merge blk_try_req_merge(काष्ठा request *req,
					काष्ठा request *next)
अणु
	अगर (blk_discard_mergable(req))
		वापस ELEVATOR_DISCARD_MERGE;
	अन्यथा अगर (blk_rq_pos(req) + blk_rq_sectors(req) == blk_rq_pos(next))
		वापस ELEVATOR_BACK_MERGE;

	वापस ELEVATOR_NO_MERGE;
पूर्ण

/*
 * For non-mq, this has to be called with the request spinlock acquired.
 * For mq with scheduling, the appropriate queue wide lock should be held.
 */
अटल काष्ठा request *attempt_merge(काष्ठा request_queue *q,
				     काष्ठा request *req, काष्ठा request *next)
अणु
	अगर (!rq_mergeable(req) || !rq_mergeable(next))
		वापस शून्य;

	अगर (req_op(req) != req_op(next))
		वापस शून्य;

	अगर (rq_data_dir(req) != rq_data_dir(next)
	    || req->rq_disk != next->rq_disk)
		वापस शून्य;

	अगर (req_op(req) == REQ_OP_WRITE_SAME &&
	    !blk_ग_लिखो_same_mergeable(req->bio, next->bio))
		वापस शून्य;

	/*
	 * Don't allow merge of dअगरferent ग_लिखो hपूर्णांकs, or क्रम a hपूर्णांक with
	 * non-hपूर्णांक IO.
	 */
	अगर (req->ग_लिखो_hपूर्णांक != next->ग_लिखो_hपूर्णांक)
		वापस शून्य;

	अगर (req->ioprio != next->ioprio)
		वापस शून्य;

	/*
	 * If we are allowed to merge, then append bio list
	 * from next to rq and release next. merge_requests_fn
	 * will have updated segment counts, update sector
	 * counts here. Handle DISCARDs separately, as they
	 * have separate settings.
	 */

	चयन (blk_try_req_merge(req, next)) अणु
	हाल ELEVATOR_DISCARD_MERGE:
		अगर (!req_attempt_discard_merge(q, req, next))
			वापस शून्य;
		अवरोध;
	हाल ELEVATOR_BACK_MERGE:
		अगर (!ll_merge_requests_fn(q, req, next))
			वापस शून्य;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	/*
	 * If failfast settings disagree or any of the two is alपढ़ोy
	 * a mixed merge, mark both as mixed beक्रमe proceeding.  This
	 * makes sure that all involved bios have mixable attributes
	 * set properly.
	 */
	अगर (((req->rq_flags | next->rq_flags) & RQF_MIXED_MERGE) ||
	    (req->cmd_flags & REQ_FAILFAST_MASK) !=
	    (next->cmd_flags & REQ_FAILFAST_MASK)) अणु
		blk_rq_set_mixed_merge(req);
		blk_rq_set_mixed_merge(next);
	पूर्ण

	/*
	 * At this poपूर्णांक we have either करोne a back merge or front merge. We
	 * need the smaller start_समय_ns of the merged requests to be the
	 * current request क्रम accounting purposes.
	 */
	अगर (next->start_समय_ns < req->start_समय_ns)
		req->start_समय_ns = next->start_समय_ns;

	req->biotail->bi_next = next->bio;
	req->biotail = next->biotail;

	req->__data_len += blk_rq_bytes(next);

	अगर (!blk_discard_mergable(req))
		elv_merge_requests(q, req, next);

	/*
	 * 'next' is going away, so update stats accordingly
	 */
	blk_account_io_merge_request(next);

	trace_block_rq_merge(next);

	/*
	 * ownership of bio passed from next to req, वापस 'next' क्रम
	 * the caller to मुक्त
	 */
	next->bio = शून्य;
	वापस next;
पूर्ण

अटल काष्ठा request *attempt_back_merge(काष्ठा request_queue *q,
		काष्ठा request *rq)
अणु
	काष्ठा request *next = elv_latter_request(q, rq);

	अगर (next)
		वापस attempt_merge(q, rq, next);

	वापस शून्य;
पूर्ण

अटल काष्ठा request *attempt_front_merge(काष्ठा request_queue *q,
		काष्ठा request *rq)
अणु
	काष्ठा request *prev = elv_क्रमmer_request(q, rq);

	अगर (prev)
		वापस attempt_merge(q, prev, rq);

	वापस शून्य;
पूर्ण

पूर्णांक blk_attempt_req_merge(काष्ठा request_queue *q, काष्ठा request *rq,
			  काष्ठा request *next)
अणु
	काष्ठा request *मुक्त;

	मुक्त = attempt_merge(q, rq, next);
	अगर (मुक्त) अणु
		blk_put_request(मुक्त);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

bool blk_rq_merge_ok(काष्ठा request *rq, काष्ठा bio *bio)
अणु
	अगर (!rq_mergeable(rq) || !bio_mergeable(bio))
		वापस false;

	अगर (req_op(rq) != bio_op(bio))
		वापस false;

	/* dअगरferent data direction or alपढ़ोy started, करोn't merge */
	अगर (bio_data_dir(bio) != rq_data_dir(rq))
		वापस false;

	/* must be same device */
	अगर (rq->rq_disk != bio->bi_bdev->bd_disk)
		वापस false;

	/* only merge पूर्णांकegrity रक्षित bio पूर्णांकo ditto rq */
	अगर (blk_पूर्णांकegrity_merge_bio(rq->q, rq, bio) == false)
		वापस false;

	/* Only merge अगर the crypt contexts are compatible */
	अगर (!bio_crypt_rq_ctx_compatible(rq, bio))
		वापस false;

	/* must be using the same buffer */
	अगर (req_op(rq) == REQ_OP_WRITE_SAME &&
	    !blk_ग_लिखो_same_mergeable(rq->bio, bio))
		वापस false;

	/*
	 * Don't allow merge of dअगरferent ग_लिखो hपूर्णांकs, or क्रम a hपूर्णांक with
	 * non-hपूर्णांक IO.
	 */
	अगर (rq->ग_लिखो_hपूर्णांक != bio->bi_ग_लिखो_hपूर्णांक)
		वापस false;

	अगर (rq->ioprio != bio_prio(bio))
		वापस false;

	वापस true;
पूर्ण

क्रमागत elv_merge blk_try_merge(काष्ठा request *rq, काष्ठा bio *bio)
अणु
	अगर (blk_discard_mergable(rq))
		वापस ELEVATOR_DISCARD_MERGE;
	अन्यथा अगर (blk_rq_pos(rq) + blk_rq_sectors(rq) == bio->bi_iter.bi_sector)
		वापस ELEVATOR_BACK_MERGE;
	अन्यथा अगर (blk_rq_pos(rq) - bio_sectors(bio) == bio->bi_iter.bi_sector)
		वापस ELEVATOR_FRONT_MERGE;
	वापस ELEVATOR_NO_MERGE;
पूर्ण

अटल व्योम blk_account_io_merge_bio(काष्ठा request *req)
अणु
	अगर (!blk_करो_io_stat(req))
		वापस;

	part_stat_lock();
	part_stat_inc(req->part, merges[op_stat_group(req_op(req))]);
	part_stat_unlock();
पूर्ण

क्रमागत bio_merge_status अणु
	BIO_MERGE_OK,
	BIO_MERGE_NONE,
	BIO_MERGE_FAILED,
पूर्ण;

अटल क्रमागत bio_merge_status bio_attempt_back_merge(काष्ठा request *req,
		काष्ठा bio *bio, अचिन्हित पूर्णांक nr_segs)
अणु
	स्थिर पूर्णांक ff = bio->bi_opf & REQ_FAILFAST_MASK;

	अगर (!ll_back_merge_fn(req, bio, nr_segs))
		वापस BIO_MERGE_FAILED;

	trace_block_bio_backmerge(bio);
	rq_qos_merge(req->q, req, bio);

	अगर ((req->cmd_flags & REQ_FAILFAST_MASK) != ff)
		blk_rq_set_mixed_merge(req);

	req->biotail->bi_next = bio;
	req->biotail = bio;
	req->__data_len += bio->bi_iter.bi_size;

	bio_crypt_मुक्त_ctx(bio);

	blk_account_io_merge_bio(req);
	वापस BIO_MERGE_OK;
पूर्ण

अटल क्रमागत bio_merge_status bio_attempt_front_merge(काष्ठा request *req,
		काष्ठा bio *bio, अचिन्हित पूर्णांक nr_segs)
अणु
	स्थिर पूर्णांक ff = bio->bi_opf & REQ_FAILFAST_MASK;

	अगर (!ll_front_merge_fn(req, bio, nr_segs))
		वापस BIO_MERGE_FAILED;

	trace_block_bio_fronपंचांगerge(bio);
	rq_qos_merge(req->q, req, bio);

	अगर ((req->cmd_flags & REQ_FAILFAST_MASK) != ff)
		blk_rq_set_mixed_merge(req);

	bio->bi_next = req->bio;
	req->bio = bio;

	req->__sector = bio->bi_iter.bi_sector;
	req->__data_len += bio->bi_iter.bi_size;

	bio_crypt_करो_front_merge(req, bio);

	blk_account_io_merge_bio(req);
	वापस BIO_MERGE_OK;
पूर्ण

अटल क्रमागत bio_merge_status bio_attempt_discard_merge(काष्ठा request_queue *q,
		काष्ठा request *req, काष्ठा bio *bio)
अणु
	अचिन्हित लघु segments = blk_rq_nr_discard_segments(req);

	अगर (segments >= queue_max_discard_segments(q))
		जाओ no_merge;
	अगर (blk_rq_sectors(req) + bio_sectors(bio) >
	    blk_rq_get_max_sectors(req, blk_rq_pos(req)))
		जाओ no_merge;

	rq_qos_merge(q, req, bio);

	req->biotail->bi_next = bio;
	req->biotail = bio;
	req->__data_len += bio->bi_iter.bi_size;
	req->nr_phys_segments = segments + 1;

	blk_account_io_merge_bio(req);
	वापस BIO_MERGE_OK;
no_merge:
	req_set_nomerge(q, req);
	वापस BIO_MERGE_FAILED;
पूर्ण

अटल क्रमागत bio_merge_status blk_attempt_bio_merge(काष्ठा request_queue *q,
						   काष्ठा request *rq,
						   काष्ठा bio *bio,
						   अचिन्हित पूर्णांक nr_segs,
						   bool sched_allow_merge)
अणु
	अगर (!blk_rq_merge_ok(rq, bio))
		वापस BIO_MERGE_NONE;

	चयन (blk_try_merge(rq, bio)) अणु
	हाल ELEVATOR_BACK_MERGE:
		अगर (!sched_allow_merge || blk_mq_sched_allow_merge(q, rq, bio))
			वापस bio_attempt_back_merge(rq, bio, nr_segs);
		अवरोध;
	हाल ELEVATOR_FRONT_MERGE:
		अगर (!sched_allow_merge || blk_mq_sched_allow_merge(q, rq, bio))
			वापस bio_attempt_front_merge(rq, bio, nr_segs);
		अवरोध;
	हाल ELEVATOR_DISCARD_MERGE:
		वापस bio_attempt_discard_merge(q, rq, bio);
	शेष:
		वापस BIO_MERGE_NONE;
	पूर्ण

	वापस BIO_MERGE_FAILED;
पूर्ण

/**
 * blk_attempt_plug_merge - try to merge with %current's plugged list
 * @q: request_queue new bio is being queued at
 * @bio: new bio being queued
 * @nr_segs: number of segments in @bio
 * @same_queue_rq: poपूर्णांकer to &काष्ठा request that माला_लो filled in when
 * another request associated with @q is found on the plug list
 * (optional, may be %शून्य)
 *
 * Determine whether @bio being queued on @q can be merged with a request
 * on %current's plugged list.  Returns %true अगर merge was successful,
 * otherwise %false.
 *
 * Plugging coalesces IOs from the same issuer क्रम the same purpose without
 * going through @q->queue_lock.  As such it's more of an issuing mechanism
 * than scheduling, and the request, जबतक may have elvpriv data, is not
 * added on the elevator at this poपूर्णांक.  In addition, we करोn't have
 * reliable access to the elevator outside queue lock.  Only check basic
 * merging parameters without querying the elevator.
 *
 * Caller must ensure !blk_queue_nomerges(q) beक्रमehand.
 */
bool blk_attempt_plug_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs, काष्ठा request **same_queue_rq)
अणु
	काष्ठा blk_plug *plug;
	काष्ठा request *rq;
	काष्ठा list_head *plug_list;

	plug = blk_mq_plug(q, bio);
	अगर (!plug)
		वापस false;

	plug_list = &plug->mq_list;

	list_क्रम_each_entry_reverse(rq, plug_list, queuelist) अणु
		अगर (rq->q == q && same_queue_rq) अणु
			/*
			 * Only blk-mq multiple hardware queues हाल checks the
			 * rq in the same queue, there should be only one such
			 * rq in a queue
			 **/
			*same_queue_rq = rq;
		पूर्ण

		अगर (rq->q != q)
			जारी;

		अगर (blk_attempt_bio_merge(q, rq, bio, nr_segs, false) ==
		    BIO_MERGE_OK)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Iterate list of requests and see अगर we can merge this bio with any
 * of them.
 */
bool blk_bio_list_merge(काष्ठा request_queue *q, काष्ठा list_head *list,
			काष्ठा bio *bio, अचिन्हित पूर्णांक nr_segs)
अणु
	काष्ठा request *rq;
	पूर्णांक checked = 8;

	list_क्रम_each_entry_reverse(rq, list, queuelist) अणु
		अगर (!checked--)
			अवरोध;

		चयन (blk_attempt_bio_merge(q, rq, bio, nr_segs, true)) अणु
		हाल BIO_MERGE_NONE:
			जारी;
		हाल BIO_MERGE_OK:
			वापस true;
		हाल BIO_MERGE_FAILED:
			वापस false;
		पूर्ण

	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(blk_bio_list_merge);

bool blk_mq_sched_try_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs, काष्ठा request **merged_request)
अणु
	काष्ठा request *rq;

	चयन (elv_merge(q, &rq, bio)) अणु
	हाल ELEVATOR_BACK_MERGE:
		अगर (!blk_mq_sched_allow_merge(q, rq, bio))
			वापस false;
		अगर (bio_attempt_back_merge(rq, bio, nr_segs) != BIO_MERGE_OK)
			वापस false;
		*merged_request = attempt_back_merge(q, rq);
		अगर (!*merged_request)
			elv_merged_request(q, rq, ELEVATOR_BACK_MERGE);
		वापस true;
	हाल ELEVATOR_FRONT_MERGE:
		अगर (!blk_mq_sched_allow_merge(q, rq, bio))
			वापस false;
		अगर (bio_attempt_front_merge(rq, bio, nr_segs) != BIO_MERGE_OK)
			वापस false;
		*merged_request = attempt_front_merge(q, rq);
		अगर (!*merged_request)
			elv_merged_request(q, rq, ELEVATOR_FRONT_MERGE);
		वापस true;
	हाल ELEVATOR_DISCARD_MERGE:
		वापस bio_attempt_discard_merge(q, rq, bio) == BIO_MERGE_OK;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(blk_mq_sched_try_merge);
