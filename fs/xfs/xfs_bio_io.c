<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 Christoph Hellwig.
 */
#समावेश "xfs.h"

अटल अंतरभूत अचिन्हित पूर्णांक bio_max_vecs(अचिन्हित पूर्णांक count)
अणु
	वापस bio_max_segs(howmany(count, PAGE_SIZE));
पूर्ण

पूर्णांक
xfs_rw_bdev(
	काष्ठा block_device	*bdev,
	sector_t		sector,
	अचिन्हित पूर्णांक		count,
	अक्षर			*data,
	अचिन्हित पूर्णांक		op)

अणु
	अचिन्हित पूर्णांक		is_vदो_स्मृति = is_vदो_स्मृति_addr(data);
	अचिन्हित पूर्णांक		left = count;
	पूर्णांक			error;
	काष्ठा bio		*bio;

	अगर (is_vदो_स्मृति && op == REQ_OP_WRITE)
		flush_kernel_vmap_range(data, count);

	bio = bio_alloc(GFP_KERNEL, bio_max_vecs(left));
	bio_set_dev(bio, bdev);
	bio->bi_iter.bi_sector = sector;
	bio->bi_opf = op | REQ_META | REQ_SYNC;

	करो अणु
		काष्ठा page	*page = kmem_to_page(data);
		अचिन्हित पूर्णांक	off = offset_in_page(data);
		अचिन्हित पूर्णांक	len = min_t(अचिन्हित, left, PAGE_SIZE - off);

		जबतक (bio_add_page(bio, page, len, off) != len) अणु
			काष्ठा bio	*prev = bio;

			bio = bio_alloc(GFP_KERNEL, bio_max_vecs(left));
			bio_copy_dev(bio, prev);
			bio->bi_iter.bi_sector = bio_end_sector(prev);
			bio->bi_opf = prev->bi_opf;
			bio_chain(prev, bio);

			submit_bio(prev);
		पूर्ण

		data += len;
		left -= len;
	पूर्ण जबतक (left > 0);

	error = submit_bio_रुको(bio);
	bio_put(bio);

	अगर (is_vदो_स्मृति && op == REQ_OP_READ)
		invalidate_kernel_vmap_range(data, count);
	वापस error;
पूर्ण
