<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2001 Jens Axboe <axboe@suse.de>
 */
#अगर_अघोषित __LINUX_BIO_H
#घोषणा __LINUX_BIO_H

#समावेश <linux/highस्मृति.स>
#समावेश <linux/mempool.h>
#समावेश <linux/ioprपन.स>
/* काष्ठा bio, bio_vec and BIO_* flags are defined in blk_types.h */
#समावेश <linux/blk_types.h>
#समावेश <linux/uपन.स>

#घोषणा BIO_DEBUG

#अगर_घोषित BIO_DEBUG
#घोषणा BIO_BUG_ON	BUG_ON
#अन्यथा
#घोषणा BIO_BUG_ON
#पूर्ण_अगर

#घोषणा BIO_MAX_VECS		256U

अटल अंतरभूत अचिन्हित पूर्णांक bio_max_segs(अचिन्हित पूर्णांक nr_segs)
अणु
	वापस min(nr_segs, BIO_MAX_VECS);
पूर्ण

#घोषणा bio_prio(bio)			(bio)->bi_ioprio
#घोषणा bio_set_prio(bio, prio)		((bio)->bi_ioprio = prio)

#घोषणा bio_iter_iovec(bio, iter)				\
	bvec_iter_bvec((bio)->bi_io_vec, (iter))

#घोषणा bio_iter_page(bio, iter)				\
	bvec_iter_page((bio)->bi_io_vec, (iter))
#घोषणा bio_iter_len(bio, iter)					\
	bvec_iter_len((bio)->bi_io_vec, (iter))
#घोषणा bio_iter_offset(bio, iter)				\
	bvec_iter_offset((bio)->bi_io_vec, (iter))

#घोषणा bio_page(bio)		bio_iter_page((bio), (bio)->bi_iter)
#घोषणा bio_offset(bio)		bio_iter_offset((bio), (bio)->bi_iter)
#घोषणा bio_iovec(bio)		bio_iter_iovec((bio), (bio)->bi_iter)

#घोषणा bio_multiple_segments(bio)				\
	((bio)->bi_iter.bi_size != bio_iovec(bio).bv_len)

#घोषणा bvec_iter_sectors(iter)	((iter).bi_size >> 9)
#घोषणा bvec_iter_end_sector(iter) ((iter).bi_sector + bvec_iter_sectors((iter)))

#घोषणा bio_sectors(bio)	bvec_iter_sectors((bio)->bi_iter)
#घोषणा bio_end_sector(bio)	bvec_iter_end_sector((bio)->bi_iter)

/*
 * Return the data direction, READ or WRITE.
 */
#घोषणा bio_data_dir(bio) \
	(op_is_ग_लिखो(bio_op(bio)) ? WRITE : READ)

/*
 * Check whether this bio carries any data or not. A शून्य bio is allowed.
 */
अटल अंतरभूत bool bio_has_data(काष्ठा bio *bio)
अणु
	अगर (bio &&
	    bio->bi_iter.bi_size &&
	    bio_op(bio) != REQ_OP_DISCARD &&
	    bio_op(bio) != REQ_OP_SECURE_ERASE &&
	    bio_op(bio) != REQ_OP_WRITE_ZEROES)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool bio_no_advance_iter(स्थिर काष्ठा bio *bio)
अणु
	वापस bio_op(bio) == REQ_OP_DISCARD ||
	       bio_op(bio) == REQ_OP_SECURE_ERASE ||
	       bio_op(bio) == REQ_OP_WRITE_SAME ||
	       bio_op(bio) == REQ_OP_WRITE_ZEROES;
पूर्ण

अटल अंतरभूत bool bio_mergeable(काष्ठा bio *bio)
अणु
	अगर (bio->bi_opf & REQ_NOMERGE_FLAGS)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bio_cur_bytes(काष्ठा bio *bio)
अणु
	अगर (bio_has_data(bio))
		वापस bio_iovec(bio).bv_len;
	अन्यथा /* dataless requests such as discard */
		वापस bio->bi_iter.bi_size;
पूर्ण

अटल अंतरभूत व्योम *bio_data(काष्ठा bio *bio)
अणु
	अगर (bio_has_data(bio))
		वापस page_address(bio_page(bio)) + bio_offset(bio);

	वापस शून्य;
पूर्ण

/**
 * bio_full - check अगर the bio is full
 * @bio:	bio to check
 * @len:	length of one segment to be added
 *
 * Return true अगर @bio is full and one segment with @len bytes can't be
 * added to the bio, otherwise वापस false
 */
अटल अंतरभूत bool bio_full(काष्ठा bio *bio, अचिन्हित len)
अणु
	अगर (bio->bi_vcnt >= bio->bi_max_vecs)
		वापस true;

	अगर (bio->bi_iter.bi_size > अच_पूर्णांक_उच्च - len)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool bio_next_segment(स्थिर काष्ठा bio *bio,
				    काष्ठा bvec_iter_all *iter)
अणु
	अगर (iter->idx >= bio->bi_vcnt)
		वापस false;

	bvec_advance(&bio->bi_io_vec[iter->idx], iter);
	वापस true;
पूर्ण

/*
 * drivers should _never_ use the all version - the bio may have been split
 * beक्रमe it got to the driver and the driver won't own all of it
 */
#घोषणा bio_क्रम_each_segment_all(bvl, bio, iter) \
	क्रम (bvl = bvec_init_iter_all(&iter); bio_next_segment((bio), &iter); )

अटल अंतरभूत व्योम bio_advance_iter(स्थिर काष्ठा bio *bio,
				    काष्ठा bvec_iter *iter, अचिन्हित पूर्णांक bytes)
अणु
	iter->bi_sector += bytes >> 9;

	अगर (bio_no_advance_iter(bio))
		iter->bi_size -= bytes;
	अन्यथा
		bvec_iter_advance(bio->bi_io_vec, iter, bytes);
		/* TODO: It is reasonable to complete bio with error here. */
पूर्ण

/* @bytes should be less or equal to bvec[i->bi_idx].bv_len */
अटल अंतरभूत व्योम bio_advance_iter_single(स्थिर काष्ठा bio *bio,
					   काष्ठा bvec_iter *iter,
					   अचिन्हित पूर्णांक bytes)
अणु
	iter->bi_sector += bytes >> 9;

	अगर (bio_no_advance_iter(bio))
		iter->bi_size -= bytes;
	अन्यथा
		bvec_iter_advance_single(bio->bi_io_vec, iter, bytes);
पूर्ण

#घोषणा __bio_क्रम_each_segment(bvl, bio, iter, start)			\
	क्रम (iter = (start);						\
	     (iter).bi_size &&						\
		((bvl = bio_iter_iovec((bio), (iter))), 1);		\
	     bio_advance_iter_single((bio), &(iter), (bvl).bv_len))

#घोषणा bio_क्रम_each_segment(bvl, bio, iter)				\
	__bio_क्रम_each_segment(bvl, bio, iter, (bio)->bi_iter)

#घोषणा __bio_क्रम_each_bvec(bvl, bio, iter, start)		\
	क्रम (iter = (start);						\
	     (iter).bi_size &&						\
		((bvl = mp_bvec_iter_bvec((bio)->bi_io_vec, (iter))), 1); \
	     bio_advance_iter_single((bio), &(iter), (bvl).bv_len))

/* iterate over multi-page bvec */
#घोषणा bio_क्रम_each_bvec(bvl, bio, iter)			\
	__bio_क्रम_each_bvec(bvl, bio, iter, (bio)->bi_iter)

/*
 * Iterate over all multi-page bvecs. Drivers shouldn't use this version क्रम the
 * same reasons as bio_क्रम_each_segment_all().
 */
#घोषणा bio_क्रम_each_bvec_all(bvl, bio, i)		\
	क्रम (i = 0, bvl = bio_first_bvec_all(bio);	\
	     i < (bio)->bi_vcnt; i++, bvl++)		\

#घोषणा bio_iter_last(bvec, iter) ((iter).bi_size == (bvec).bv_len)

अटल अंतरभूत अचिन्हित bio_segments(काष्ठा bio *bio)
अणु
	अचिन्हित segs = 0;
	काष्ठा bio_vec bv;
	काष्ठा bvec_iter iter;

	/*
	 * We special हाल discard/ग_लिखो same/ग_लिखो zeroes, because they
	 * पूर्णांकerpret bi_size dअगरferently:
	 */

	चयन (bio_op(bio)) अणु
	हाल REQ_OP_DISCARD:
	हाल REQ_OP_SECURE_ERASE:
	हाल REQ_OP_WRITE_ZEROES:
		वापस 0;
	हाल REQ_OP_WRITE_SAME:
		वापस 1;
	शेष:
		अवरोध;
	पूर्ण

	bio_क्रम_each_segment(bv, bio, iter)
		segs++;

	वापस segs;
पूर्ण

/*
 * get a reference to a bio, so it won't disappear. the पूर्णांकended use is
 * something like:
 *
 * bio_get(bio);
 * submit_bio(rw, bio);
 * अगर (bio->bi_flags ...)
 *	करो_something
 * bio_put(bio);
 *
 * without the bio_get(), it could potentially complete I/O beक्रमe submit_bio
 * वापसs. and then bio would be मुक्तd memory when अगर (bio->bi_flags ...)
 * runs
 */
अटल अंतरभूत व्योम bio_get(काष्ठा bio *bio)
अणु
	bio->bi_flags |= (1 << BIO_REFFED);
	smp_mb__beक्रमe_atomic();
	atomic_inc(&bio->__bi_cnt);
पूर्ण

अटल अंतरभूत व्योम bio_cnt_set(काष्ठा bio *bio, अचिन्हित पूर्णांक count)
अणु
	अगर (count != 1) अणु
		bio->bi_flags |= (1 << BIO_REFFED);
		smp_mb();
	पूर्ण
	atomic_set(&bio->__bi_cnt, count);
पूर्ण

अटल अंतरभूत bool bio_flagged(काष्ठा bio *bio, अचिन्हित पूर्णांक bit)
अणु
	वापस (bio->bi_flags & (1U << bit)) != 0;
पूर्ण

अटल अंतरभूत व्योम bio_set_flag(काष्ठा bio *bio, अचिन्हित पूर्णांक bit)
अणु
	bio->bi_flags |= (1U << bit);
पूर्ण

अटल अंतरभूत व्योम bio_clear_flag(काष्ठा bio *bio, अचिन्हित पूर्णांक bit)
अणु
	bio->bi_flags &= ~(1U << bit);
पूर्ण

अटल अंतरभूत व्योम bio_get_first_bvec(काष्ठा bio *bio, काष्ठा bio_vec *bv)
अणु
	*bv = bio_iovec(bio);
पूर्ण

अटल अंतरभूत व्योम bio_get_last_bvec(काष्ठा bio *bio, काष्ठा bio_vec *bv)
अणु
	काष्ठा bvec_iter iter = bio->bi_iter;
	पूर्णांक idx;

	अगर (unlikely(!bio_multiple_segments(bio))) अणु
		*bv = bio_iovec(bio);
		वापस;
	पूर्ण

	bio_advance_iter(bio, &iter, iter.bi_size);

	अगर (!iter.bi_bvec_करोne)
		idx = iter.bi_idx - 1;
	अन्यथा	/* in the middle of bvec */
		idx = iter.bi_idx;

	*bv = bio->bi_io_vec[idx];

	/*
	 * iter.bi_bvec_करोne records actual length of the last bvec
	 * अगर this bio ends in the middle of one io vector
	 */
	अगर (iter.bi_bvec_करोne)
		bv->bv_len = iter.bi_bvec_करोne;
पूर्ण

अटल अंतरभूत काष्ठा bio_vec *bio_first_bvec_all(काष्ठा bio *bio)
अणु
	WARN_ON_ONCE(bio_flagged(bio, BIO_CLONED));
	वापस bio->bi_io_vec;
पूर्ण

अटल अंतरभूत काष्ठा page *bio_first_page_all(काष्ठा bio *bio)
अणु
	वापस bio_first_bvec_all(bio)->bv_page;
पूर्ण

अटल अंतरभूत काष्ठा bio_vec *bio_last_bvec_all(काष्ठा bio *bio)
अणु
	WARN_ON_ONCE(bio_flagged(bio, BIO_CLONED));
	वापस &bio->bi_io_vec[bio->bi_vcnt - 1];
पूर्ण

क्रमागत bip_flags अणु
	BIP_BLOCK_INTEGRITY	= 1 << 0, /* block layer owns पूर्णांकegrity data */
	BIP_MAPPED_INTEGRITY	= 1 << 1, /* ref tag has been remapped */
	BIP_CTRL_NOCHECK	= 1 << 2, /* disable HBA पूर्णांकegrity checking */
	BIP_DISK_NOCHECK	= 1 << 3, /* disable disk पूर्णांकegrity checking */
	BIP_IP_CHECKSUM		= 1 << 4, /* IP checksum */
पूर्ण;

/*
 * bio पूर्णांकegrity payload
 */
काष्ठा bio_पूर्णांकegrity_payload अणु
	काष्ठा bio		*bip_bio;	/* parent bio */

	काष्ठा bvec_iter	bip_iter;

	अचिन्हित लघु		bip_vcnt;	/* # of पूर्णांकegrity bio_vecs */
	अचिन्हित लघु		bip_max_vcnt;	/* पूर्णांकegrity bio_vec slots */
	अचिन्हित लघु		bip_flags;	/* control flags */

	काष्ठा bvec_iter	bio_iter;	/* क्रम शुरुआतing parent bio */

	काष्ठा work_काष्ठा	bip_work;	/* I/O completion */

	काष्ठा bio_vec		*bip_vec;
	काष्ठा bio_vec		bip_अंतरभूत_vecs[];/* embedded bvec array */
पूर्ण;

#अगर defined(CONFIG_BLK_DEV_INTEGRITY)

अटल अंतरभूत काष्ठा bio_पूर्णांकegrity_payload *bio_पूर्णांकegrity(काष्ठा bio *bio)
अणु
	अगर (bio->bi_opf & REQ_INTEGRITY)
		वापस bio->bi_पूर्णांकegrity;

	वापस शून्य;
पूर्ण

अटल अंतरभूत bool bio_पूर्णांकegrity_flagged(काष्ठा bio *bio, क्रमागत bip_flags flag)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);

	अगर (bip)
		वापस bip->bip_flags & flag;

	वापस false;
पूर्ण

अटल अंतरभूत sector_t bip_get_seed(काष्ठा bio_पूर्णांकegrity_payload *bip)
अणु
	वापस bip->bip_iter.bi_sector;
पूर्ण

अटल अंतरभूत व्योम bip_set_seed(काष्ठा bio_पूर्णांकegrity_payload *bip,
				sector_t seed)
अणु
	bip->bip_iter.bi_sector = seed;
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_DEV_INTEGRITY */

बाह्य व्योम bio_trim(काष्ठा bio *bio, पूर्णांक offset, पूर्णांक size);
बाह्य काष्ठा bio *bio_split(काष्ठा bio *bio, पूर्णांक sectors,
			     gfp_t gfp, काष्ठा bio_set *bs);

/**
 * bio_next_split - get next @sectors from a bio, splitting अगर necessary
 * @bio:	bio to split
 * @sectors:	number of sectors to split from the front of @bio
 * @gfp:	gfp mask
 * @bs:		bio set to allocate from
 *
 * Returns a bio representing the next @sectors of @bio - अगर the bio is smaller
 * than @sectors, वापसs the original bio unchanged.
 */
अटल अंतरभूत काष्ठा bio *bio_next_split(काष्ठा bio *bio, पूर्णांक sectors,
					 gfp_t gfp, काष्ठा bio_set *bs)
अणु
	अगर (sectors >= bio_sectors(bio))
		वापस bio;

	वापस bio_split(bio, sectors, gfp, bs);
पूर्ण

क्रमागत अणु
	BIOSET_NEED_BVECS = BIT(0),
	BIOSET_NEED_RESCUER = BIT(1),
पूर्ण;
बाह्य पूर्णांक bioset_init(काष्ठा bio_set *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, पूर्णांक flags);
बाह्य व्योम bioset_निकास(काष्ठा bio_set *);
बाह्य पूर्णांक biovec_init_pool(mempool_t *pool, पूर्णांक pool_entries);
बाह्य पूर्णांक bioset_init_from_src(काष्ठा bio_set *bs, काष्ठा bio_set *src);

काष्ठा bio *bio_alloc_bioset(gfp_t gfp, अचिन्हित लघु nr_iovecs,
		काष्ठा bio_set *bs);
काष्ठा bio *bio_kदो_स्मृति(gfp_t gfp_mask, अचिन्हित लघु nr_iovecs);
बाह्य व्योम bio_put(काष्ठा bio *);

बाह्य व्योम __bio_clone_fast(काष्ठा bio *, काष्ठा bio *);
बाह्य काष्ठा bio *bio_clone_fast(काष्ठा bio *, gfp_t, काष्ठा bio_set *);

बाह्य काष्ठा bio_set fs_bio_set;

अटल अंतरभूत काष्ठा bio *bio_alloc(gfp_t gfp_mask, अचिन्हित लघु nr_iovecs)
अणु
	वापस bio_alloc_bioset(gfp_mask, nr_iovecs, &fs_bio_set);
पूर्ण

बाह्य blk_qc_t submit_bio(काष्ठा bio *);

बाह्य व्योम bio_endio(काष्ठा bio *);

अटल अंतरभूत व्योम bio_io_error(काष्ठा bio *bio)
अणु
	bio->bi_status = BLK_STS_IOERR;
	bio_endio(bio);
पूर्ण

अटल अंतरभूत व्योम bio_wouldblock_error(काष्ठा bio *bio)
अणु
	bio_set_flag(bio, BIO_QUIET);
	bio->bi_status = BLK_STS_AGAIN;
	bio_endio(bio);
पूर्ण

/*
 * Calculate number of bvec segments that should be allocated to fit data
 * poपूर्णांकed by @iter. If @iter is backed by bvec it's going to be reused
 * instead of allocating a new one.
 */
अटल अंतरभूत पूर्णांक bio_iov_vecs_to_alloc(काष्ठा iov_iter *iter, पूर्णांक max_segs)
अणु
	अगर (iov_iter_is_bvec(iter))
		वापस 0;
	वापस iov_iter_npages(iter, max_segs);
पूर्ण

काष्ठा request_queue;

बाह्य पूर्णांक submit_bio_रुको(काष्ठा bio *bio);
बाह्य व्योम bio_advance(काष्ठा bio *, अचिन्हित);

बाह्य व्योम bio_init(काष्ठा bio *bio, काष्ठा bio_vec *table,
		     अचिन्हित लघु max_vecs);
बाह्य व्योम bio_uninit(काष्ठा bio *);
बाह्य व्योम bio_reset(काष्ठा bio *);
व्योम bio_chain(काष्ठा bio *, काष्ठा bio *);

बाह्य पूर्णांक bio_add_page(काष्ठा bio *, काष्ठा page *, अचिन्हित पूर्णांक,अचिन्हित पूर्णांक);
बाह्य पूर्णांक bio_add_pc_page(काष्ठा request_queue *, काष्ठा bio *, काष्ठा page *,
			   अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
पूर्णांक bio_add_zone_append_page(काष्ठा bio *bio, काष्ठा page *page,
			     अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset);
bool __bio_try_merge_page(काष्ठा bio *bio, काष्ठा page *page,
		अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off, bool *same_page);
व्योम __bio_add_page(काष्ठा bio *bio, काष्ठा page *page,
		अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off);
पूर्णांक bio_iov_iter_get_pages(काष्ठा bio *bio, काष्ठा iov_iter *iter);
व्योम bio_release_pages(काष्ठा bio *bio, bool mark_dirty);
बाह्य व्योम bio_set_pages_dirty(काष्ठा bio *bio);
बाह्य व्योम bio_check_pages_dirty(काष्ठा bio *bio);

बाह्य व्योम bio_copy_data_iter(काष्ठा bio *dst, काष्ठा bvec_iter *dst_iter,
			       काष्ठा bio *src, काष्ठा bvec_iter *src_iter);
बाह्य व्योम bio_copy_data(काष्ठा bio *dst, काष्ठा bio *src);
बाह्य व्योम bio_मुक्त_pages(काष्ठा bio *bio);
व्योम bio_truncate(काष्ठा bio *bio, अचिन्हित new_size);
व्योम guard_bio_eod(काष्ठा bio *bio);
व्योम zero_fill_bio(काष्ठा bio *bio);

बाह्य स्थिर अक्षर *bio_devname(काष्ठा bio *bio, अक्षर *buffer);

#घोषणा bio_set_dev(bio, bdev) 				\
करो अणु							\
	bio_clear_flag(bio, BIO_REMAPPED);		\
	अगर ((bio)->bi_bdev != (bdev))			\
		bio_clear_flag(bio, BIO_THROTTLED);	\
	(bio)->bi_bdev = (bdev);			\
	bio_associate_blkg(bio);			\
पूर्ण जबतक (0)

#घोषणा bio_copy_dev(dst, src)			\
करो अणु						\
	bio_clear_flag(dst, BIO_REMAPPED);		\
	(dst)->bi_bdev = (src)->bi_bdev;	\
	bio_clone_blkg_association(dst, src);	\
पूर्ण जबतक (0)

#घोषणा bio_dev(bio) \
	disk_devt((bio)->bi_bdev->bd_disk)

#अगर_घोषित CONFIG_BLK_CGROUP
व्योम bio_associate_blkg(काष्ठा bio *bio);
व्योम bio_associate_blkg_from_css(काष्ठा bio *bio,
				 काष्ठा cgroup_subsys_state *css);
व्योम bio_clone_blkg_association(काष्ठा bio *dst, काष्ठा bio *src);
#अन्यथा	/* CONFIG_BLK_CGROUP */
अटल अंतरभूत व्योम bio_associate_blkg(काष्ठा bio *bio) अणु पूर्ण
अटल अंतरभूत व्योम bio_associate_blkg_from_css(काष्ठा bio *bio,
					       काष्ठा cgroup_subsys_state *css)
अणु पूर्ण
अटल अंतरभूत व्योम bio_clone_blkg_association(काष्ठा bio *dst,
					      काष्ठा bio *src) अणु पूर्ण
#पूर्ण_अगर	/* CONFIG_BLK_CGROUP */

#अगर_घोषित CONFIG_HIGHMEM
/*
 * remember never ever reenable पूर्णांकerrupts between a bvec_kmap_irq and
 * bvec_kunmap_irq!
 */
अटल अंतरभूत अक्षर *bvec_kmap_irq(काष्ठा bio_vec *bvec, अचिन्हित दीर्घ *flags)
अणु
	अचिन्हित दीर्घ addr;

	/*
	 * might not be a highmem page, but the preempt/irq count
	 * balancing is a lot nicer this way
	 */
	local_irq_save(*flags);
	addr = (अचिन्हित दीर्घ) kmap_atomic(bvec->bv_page);

	BUG_ON(addr & ~PAGE_MASK);

	वापस (अक्षर *) addr + bvec->bv_offset;
पूर्ण

अटल अंतरभूत व्योम bvec_kunmap_irq(अक्षर *buffer, अचिन्हित दीर्घ *flags)
अणु
	अचिन्हित दीर्घ ptr = (अचिन्हित दीर्घ) buffer & PAGE_MASK;

	kunmap_atomic((व्योम *) ptr);
	local_irq_restore(*flags);
पूर्ण

#अन्यथा
अटल अंतरभूत अक्षर *bvec_kmap_irq(काष्ठा bio_vec *bvec, अचिन्हित दीर्घ *flags)
अणु
	वापस page_address(bvec->bv_page) + bvec->bv_offset;
पूर्ण

अटल अंतरभूत व्योम bvec_kunmap_irq(अक्षर *buffer, अचिन्हित दीर्घ *flags)
अणु
	*flags = 0;
पूर्ण
#पूर्ण_अगर

/*
 * BIO list management क्रम use by remapping drivers (e.g. DM or MD) and loop.
 *
 * A bio_list anchors a singly-linked list of bios chained through the bi_next
 * member of the bio.  The bio_list also caches the last list member to allow
 * fast access to the tail.
 */
काष्ठा bio_list अणु
	काष्ठा bio *head;
	काष्ठा bio *tail;
पूर्ण;

अटल अंतरभूत पूर्णांक bio_list_empty(स्थिर काष्ठा bio_list *bl)
अणु
	वापस bl->head == शून्य;
पूर्ण

अटल अंतरभूत व्योम bio_list_init(काष्ठा bio_list *bl)
अणु
	bl->head = bl->tail = शून्य;
पूर्ण

#घोषणा BIO_EMPTY_LIST	अणु शून्य, शून्य पूर्ण

#घोषणा bio_list_क्रम_each(bio, bl) \
	क्रम (bio = (bl)->head; bio; bio = bio->bi_next)

अटल अंतरभूत अचिन्हित bio_list_size(स्थिर काष्ठा bio_list *bl)
अणु
	अचिन्हित sz = 0;
	काष्ठा bio *bio;

	bio_list_क्रम_each(bio, bl)
		sz++;

	वापस sz;
पूर्ण

अटल अंतरभूत व्योम bio_list_add(काष्ठा bio_list *bl, काष्ठा bio *bio)
अणु
	bio->bi_next = शून्य;

	अगर (bl->tail)
		bl->tail->bi_next = bio;
	अन्यथा
		bl->head = bio;

	bl->tail = bio;
पूर्ण

अटल अंतरभूत व्योम bio_list_add_head(काष्ठा bio_list *bl, काष्ठा bio *bio)
अणु
	bio->bi_next = bl->head;

	bl->head = bio;

	अगर (!bl->tail)
		bl->tail = bio;
पूर्ण

अटल अंतरभूत व्योम bio_list_merge(काष्ठा bio_list *bl, काष्ठा bio_list *bl2)
अणु
	अगर (!bl2->head)
		वापस;

	अगर (bl->tail)
		bl->tail->bi_next = bl2->head;
	अन्यथा
		bl->head = bl2->head;

	bl->tail = bl2->tail;
पूर्ण

अटल अंतरभूत व्योम bio_list_merge_head(काष्ठा bio_list *bl,
				       काष्ठा bio_list *bl2)
अणु
	अगर (!bl2->head)
		वापस;

	अगर (bl->head)
		bl2->tail->bi_next = bl->head;
	अन्यथा
		bl->tail = bl2->tail;

	bl->head = bl2->head;
पूर्ण

अटल अंतरभूत काष्ठा bio *bio_list_peek(काष्ठा bio_list *bl)
अणु
	वापस bl->head;
पूर्ण

अटल अंतरभूत काष्ठा bio *bio_list_pop(काष्ठा bio_list *bl)
अणु
	काष्ठा bio *bio = bl->head;

	अगर (bio) अणु
		bl->head = bl->head->bi_next;
		अगर (!bl->head)
			bl->tail = शून्य;

		bio->bi_next = शून्य;
	पूर्ण

	वापस bio;
पूर्ण

अटल अंतरभूत काष्ठा bio *bio_list_get(काष्ठा bio_list *bl)
अणु
	काष्ठा bio *bio = bl->head;

	bl->head = bl->tail = शून्य;

	वापस bio;
पूर्ण

/*
 * Increment chain count क्रम the bio. Make sure the CHAIN flag update
 * is visible beक्रमe the उठाओd count.
 */
अटल अंतरभूत व्योम bio_inc_reमुख्यing(काष्ठा bio *bio)
अणु
	bio_set_flag(bio, BIO_CHAIN);
	smp_mb__beक्रमe_atomic();
	atomic_inc(&bio->__bi_reमुख्यing);
पूर्ण

/*
 * bio_set is used to allow other portions of the IO प्रणाली to
 * allocate their own निजी memory pools क्रम bio and iovec काष्ठाures.
 * These memory pools in turn all allocate from the bio_slab
 * and the bvec_sद_असल[].
 */
#घोषणा BIO_POOL_SIZE 2

काष्ठा bio_set अणु
	काष्ठा kmem_cache *bio_slab;
	अचिन्हित पूर्णांक front_pad;

	mempool_t bio_pool;
	mempool_t bvec_pool;
#अगर defined(CONFIG_BLK_DEV_INTEGRITY)
	mempool_t bio_पूर्णांकegrity_pool;
	mempool_t bvec_पूर्णांकegrity_pool;
#पूर्ण_अगर

	अचिन्हित पूर्णांक back_pad;
	/*
	 * Deadlock aव्योमance क्रम stacking block drivers: see comments in
	 * bio_alloc_bioset() क्रम details
	 */
	spinlock_t		rescue_lock;
	काष्ठा bio_list		rescue_list;
	काष्ठा work_काष्ठा	rescue_work;
	काष्ठा workqueue_काष्ठा	*rescue_workqueue;
पूर्ण;

अटल अंतरभूत bool bioset_initialized(काष्ठा bio_set *bs)
अणु
	वापस bs->bio_slab != शून्य;
पूर्ण

#अगर defined(CONFIG_BLK_DEV_INTEGRITY)

#घोषणा bip_क्रम_each_vec(bvl, bip, iter)				\
	क्रम_each_bvec(bvl, (bip)->bip_vec, iter, (bip)->bip_iter)

#घोषणा bio_क्रम_each_पूर्णांकegrity_vec(_bvl, _bio, _iter)			\
	क्रम_each_bio(_bio)						\
		bip_क्रम_each_vec(_bvl, _bio->bi_पूर्णांकegrity, _iter)

बाह्य काष्ठा bio_पूर्णांकegrity_payload *bio_पूर्णांकegrity_alloc(काष्ठा bio *, gfp_t, अचिन्हित पूर्णांक);
बाह्य पूर्णांक bio_पूर्णांकegrity_add_page(काष्ठा bio *, काष्ठा page *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
बाह्य bool bio_पूर्णांकegrity_prep(काष्ठा bio *);
बाह्य व्योम bio_पूर्णांकegrity_advance(काष्ठा bio *, अचिन्हित पूर्णांक);
बाह्य व्योम bio_पूर्णांकegrity_trim(काष्ठा bio *);
बाह्य पूर्णांक bio_पूर्णांकegrity_clone(काष्ठा bio *, काष्ठा bio *, gfp_t);
बाह्य पूर्णांक bioset_पूर्णांकegrity_create(काष्ठा bio_set *, पूर्णांक);
बाह्य व्योम bioset_पूर्णांकegrity_मुक्त(काष्ठा bio_set *);
बाह्य व्योम bio_पूर्णांकegrity_init(व्योम);

#अन्यथा /* CONFIG_BLK_DEV_INTEGRITY */

अटल अंतरभूत व्योम *bio_पूर्णांकegrity(काष्ठा bio *bio)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक bioset_पूर्णांकegrity_create(काष्ठा bio_set *bs, पूर्णांक pool_size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bioset_पूर्णांकegrity_मुक्त (काष्ठा bio_set *bs)
अणु
	वापस;
पूर्ण

अटल अंतरभूत bool bio_पूर्णांकegrity_prep(काष्ठा bio *bio)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक bio_पूर्णांकegrity_clone(काष्ठा bio *bio, काष्ठा bio *bio_src,
				      gfp_t gfp_mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bio_पूर्णांकegrity_advance(काष्ठा bio *bio,
					 अचिन्हित पूर्णांक bytes_करोne)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम bio_पूर्णांकegrity_trim(काष्ठा bio *bio)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम bio_पूर्णांकegrity_init(व्योम)
अणु
	वापस;
पूर्ण

अटल अंतरभूत bool bio_पूर्णांकegrity_flagged(काष्ठा bio *bio, क्रमागत bip_flags flag)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम *bio_पूर्णांकegrity_alloc(काष्ठा bio * bio, gfp_t gfp,
								अचिन्हित पूर्णांक nr)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत पूर्णांक bio_पूर्णांकegrity_add_page(काष्ठा bio *bio, काष्ठा page *page,
					अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_DEV_INTEGRITY */

/*
 * Mark a bio as polled. Note that क्रम async polled IO, the caller must
 * expect -EWOULDBLOCK अगर we cannot allocate a request (or other resources).
 * We cannot block रुकोing क्रम requests on polled IO, as those completions
 * must be found by the caller. This is dअगरferent than IRQ driven IO, where
 * it's safe to रुको क्रम IO to complete.
 */
अटल अंतरभूत व्योम bio_set_polled(काष्ठा bio *bio, काष्ठा kiocb *kiocb)
अणु
	bio->bi_opf |= REQ_HIPRI;
	अगर (!is_sync_kiocb(kiocb))
		bio->bi_opf |= REQ_NOWAIT;
पूर्ण

#पूर्ण_अगर /* __LINUX_BIO_H */
