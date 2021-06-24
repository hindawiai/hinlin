<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Some low level IO code, and hacks क्रम various block layer limitations
 *
 * Copyright 2010, 2011 Kent Overstreet <kent.overstreet@gmail.com>
 * Copyright 2012 Google, Inc.
 */

#समावेश "bcache.h"
#समावेश "bset.h"
#समावेश "debug.h"

#समावेश <linux/blkdev.h>

/* Bios with headers */

व्योम bch_bbio_मुक्त(काष्ठा bio *bio, काष्ठा cache_set *c)
अणु
	काष्ठा bbio *b = container_of(bio, काष्ठा bbio, bio);

	mempool_मुक्त(b, &c->bio_meta);
पूर्ण

काष्ठा bio *bch_bbio_alloc(काष्ठा cache_set *c)
अणु
	काष्ठा bbio *b = mempool_alloc(&c->bio_meta, GFP_NOIO);
	काष्ठा bio *bio = &b->bio;

	bio_init(bio, bio->bi_अंतरभूत_vecs, meta_bucket_pages(&c->cache->sb));

	वापस bio;
पूर्ण

व्योम __bch_submit_bbio(काष्ठा bio *bio, काष्ठा cache_set *c)
अणु
	काष्ठा bbio *b = container_of(bio, काष्ठा bbio, bio);

	bio->bi_iter.bi_sector	= PTR_OFFSET(&b->key, 0);
	bio_set_dev(bio, c->cache->bdev);

	b->submit_समय_us = local_घड़ी_us();
	closure_bio_submit(c, bio, bio->bi_निजी);
पूर्ण

व्योम bch_submit_bbio(काष्ठा bio *bio, काष्ठा cache_set *c,
		     काष्ठा bkey *k, अचिन्हित पूर्णांक ptr)
अणु
	काष्ठा bbio *b = container_of(bio, काष्ठा bbio, bio);

	bch_bkey_copy_single_ptr(&b->key, k, ptr);
	__bch_submit_bbio(bio, c);
पूर्ण

/* IO errors */
व्योम bch_count_backing_io_errors(काष्ठा cached_dev *dc, काष्ठा bio *bio)
अणु
	अचिन्हित पूर्णांक errors;

	WARN_ONCE(!dc, "NULL pointer of struct cached_dev");

	/*
	 * Read-ahead requests on a degrading and recovering md raid
	 * (e.g. raid6) device might be failured immediately by md
	 * raid code, which is not a real hardware media failure. So
	 * we shouldn't count failed REQ_RAHEAD bio to dc->io_errors.
	 */
	अगर (bio->bi_opf & REQ_RAHEAD) अणु
		pr_warn_ratelimited("%s: Read-ahead I/O failed on backing device, ignore\n",
				    dc->backing_dev_name);
		वापस;
	पूर्ण

	errors = atomic_add_वापस(1, &dc->io_errors);
	अगर (errors < dc->error_limit)
		pr_err("%s: IO error on backing device, unrecoverable\n",
			dc->backing_dev_name);
	अन्यथा
		bch_cached_dev_error(dc);
पूर्ण

व्योम bch_count_io_errors(काष्ठा cache *ca,
			 blk_status_t error,
			 पूर्णांक is_पढ़ो,
			 स्थिर अक्षर *m)
अणु
	/*
	 * The halflअगरe of an error is:
	 * log2(1/2)/log2(127/128) * refresh ~= 88 * refresh
	 */

	अगर (ca->set->error_decay) अणु
		अचिन्हित पूर्णांक count = atomic_inc_वापस(&ca->io_count);

		जबतक (count > ca->set->error_decay) अणु
			अचिन्हित पूर्णांक errors;
			अचिन्हित पूर्णांक old = count;
			अचिन्हित पूर्णांक new = count - ca->set->error_decay;

			/*
			 * First we subtract refresh from count; each समय we
			 * successfully करो so, we rescale the errors once:
			 */

			count = atomic_cmpxchg(&ca->io_count, old, new);

			अगर (count == old) अणु
				count = new;

				errors = atomic_पढ़ो(&ca->io_errors);
				करो अणु
					old = errors;
					new = ((uपूर्णांक64_t) errors * 127) / 128;
					errors = atomic_cmpxchg(&ca->io_errors,
								old, new);
				पूर्ण जबतक (old != errors);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (error) अणु
		अचिन्हित पूर्णांक errors = atomic_add_वापस(1 << IO_ERROR_SHIFT,
						    &ca->io_errors);
		errors >>= IO_ERROR_SHIFT;

		अगर (errors < ca->set->error_limit)
			pr_err("%s: IO error on %s%s\n",
			       ca->cache_dev_name, m,
			       is_पढ़ो ? ", recovering." : ".");
		अन्यथा
			bch_cache_set_error(ca->set,
					    "%s: too many IO errors %s\n",
					    ca->cache_dev_name, m);
	पूर्ण
पूर्ण

व्योम bch_bbio_count_io_errors(काष्ठा cache_set *c, काष्ठा bio *bio,
			      blk_status_t error, स्थिर अक्षर *m)
अणु
	काष्ठा bbio *b = container_of(bio, काष्ठा bbio, bio);
	काष्ठा cache *ca = c->cache;
	पूर्णांक is_पढ़ो = (bio_data_dir(bio) == READ ? 1 : 0);

	अचिन्हित पूर्णांक threshold = op_is_ग_लिखो(bio_op(bio))
		? c->congested_ग_लिखो_threshold_us
		: c->congested_पढ़ो_threshold_us;

	अगर (threshold) अणु
		अचिन्हित पूर्णांक t = local_घड़ी_us();
		पूर्णांक us = t - b->submit_समय_us;
		पूर्णांक congested = atomic_पढ़ो(&c->congested);

		अगर (us > (पूर्णांक) threshold) अणु
			पूर्णांक ms = us / 1024;

			c->congested_last_us = t;

			ms = min(ms, CONGESTED_MAX + congested);
			atomic_sub(ms, &c->congested);
		पूर्ण अन्यथा अगर (congested < 0)
			atomic_inc(&c->congested);
	पूर्ण

	bch_count_io_errors(ca, error, is_पढ़ो, m);
पूर्ण

व्योम bch_bbio_endio(काष्ठा cache_set *c, काष्ठा bio *bio,
		    blk_status_t error, स्थिर अक्षर *m)
अणु
	काष्ठा closure *cl = bio->bi_निजी;

	bch_bbio_count_io_errors(c, bio, error, m);
	bio_put(bio);
	closure_put(cl);
पूर्ण
