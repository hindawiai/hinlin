<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BCACHE_WRITEBACK_H
#घोषणा _BCACHE_WRITEBACK_H

#घोषणा CUTOFF_WRITEBACK	40
#घोषणा CUTOFF_WRITEBACK_SYNC	70

#घोषणा CUTOFF_WRITEBACK_MAX		70
#घोषणा CUTOFF_WRITEBACK_SYNC_MAX	90

#घोषणा MAX_WRITEBACKS_IN_PASS  5
#घोषणा MAX_WRITESIZE_IN_PASS   5000	/* *512b */

#घोषणा WRITEBACK_RATE_UPDATE_SECS_MAX		60
#घोषणा WRITEBACK_RATE_UPDATE_SECS_DEFAULT	5

#घोषणा BCH_AUTO_GC_सूचीTY_THRESHOLD	50

#घोषणा BCH_WRITEBACK_FRAGMENT_THRESHOLD_LOW 50
#घोषणा BCH_WRITEBACK_FRAGMENT_THRESHOLD_MID 57
#घोषणा BCH_WRITEBACK_FRAGMENT_THRESHOLD_HIGH 64

#घोषणा BCH_सूचीTY_INIT_THRD_MAX	64
/*
 * 14 (16384ths) is chosen here as something that each backing device
 * should be a reasonable fraction of the share, and not to blow up
 * until inभागidual backing devices are a petabyte.
 */
#घोषणा WRITEBACK_SHARE_SHIFT   14

काष्ठा bch_dirty_init_state;
काष्ठा dirty_init_thrd_info अणु
	काष्ठा bch_dirty_init_state	*state;
	काष्ठा task_काष्ठा		*thपढ़ो;
पूर्ण;

काष्ठा bch_dirty_init_state अणु
	काष्ठा cache_set		*c;
	काष्ठा bcache_device		*d;
	पूर्णांक				total_thपढ़ोs;
	पूर्णांक				key_idx;
	spinlock_t			idx_lock;
	atomic_t			started;
	atomic_t			enough;
	रुको_queue_head_t		रुको;
	काष्ठा dirty_init_thrd_info	infos[BCH_सूचीTY_INIT_THRD_MAX];
पूर्ण;

अटल अंतरभूत uपूर्णांक64_t bcache_dev_sectors_dirty(काष्ठा bcache_device *d)
अणु
	uपूर्णांक64_t i, ret = 0;

	क्रम (i = 0; i < d->nr_stripes; i++)
		ret += atomic_पढ़ो(d->stripe_sectors_dirty + i);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक offset_to_stripe(काष्ठा bcache_device *d,
					uपूर्णांक64_t offset)
अणु
	करो_भाग(offset, d->stripe_size);

	/* d->nr_stripes is in range [1, पूर्णांक_उच्च] */
	अगर (unlikely(offset >= d->nr_stripes)) अणु
		pr_err("Invalid stripe %llu (>= nr_stripes %d).\n",
			offset, d->nr_stripes);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Here offset is definitly smaller than पूर्णांक_उच्च,
	 * वापस it as पूर्णांक will never overflow.
	 */
	वापस offset;
पूर्ण

अटल अंतरभूत bool bcache_dev_stripe_dirty(काष्ठा cached_dev *dc,
					   uपूर्णांक64_t offset,
					   अचिन्हित पूर्णांक nr_sectors)
अणु
	पूर्णांक stripe = offset_to_stripe(&dc->disk, offset);

	अगर (stripe < 0)
		वापस false;

	जबतक (1) अणु
		अगर (atomic_पढ़ो(dc->disk.stripe_sectors_dirty + stripe))
			वापस true;

		अगर (nr_sectors <= dc->disk.stripe_size)
			वापस false;

		nr_sectors -= dc->disk.stripe_size;
		stripe++;
	पूर्ण
पूर्ण

बाह्य अचिन्हित पूर्णांक bch_cutoff_ग_लिखोback;
बाह्य अचिन्हित पूर्णांक bch_cutoff_ग_लिखोback_sync;

अटल अंतरभूत bool should_ग_लिखोback(काष्ठा cached_dev *dc, काष्ठा bio *bio,
				    अचिन्हित पूर्णांक cache_mode, bool would_skip)
अणु
	अचिन्हित पूर्णांक in_use = dc->disk.c->gc_stats.in_use;

	अगर (cache_mode != CACHE_MODE_WRITEBACK ||
	    test_bit(BCACHE_DEV_DETACHING, &dc->disk.flags) ||
	    in_use > bch_cutoff_ग_लिखोback_sync)
		वापस false;

	अगर (bio_op(bio) == REQ_OP_DISCARD)
		वापस false;

	अगर (dc->partial_stripes_expensive &&
	    bcache_dev_stripe_dirty(dc, bio->bi_iter.bi_sector,
				    bio_sectors(bio)))
		वापस true;

	अगर (would_skip)
		वापस false;

	वापस (op_is_sync(bio->bi_opf) ||
		bio->bi_opf & (REQ_META|REQ_PRIO) ||
		in_use <= bch_cutoff_ग_लिखोback);
पूर्ण

अटल अंतरभूत व्योम bch_ग_लिखोback_queue(काष्ठा cached_dev *dc)
अणु
	अगर (!IS_ERR_OR_शून्य(dc->ग_लिखोback_thपढ़ो))
		wake_up_process(dc->ग_लिखोback_thपढ़ो);
पूर्ण

अटल अंतरभूत व्योम bch_ग_लिखोback_add(काष्ठा cached_dev *dc)
अणु
	अगर (!atomic_पढ़ो(&dc->has_dirty) &&
	    !atomic_xchg(&dc->has_dirty, 1)) अणु
		अगर (BDEV_STATE(&dc->sb) != BDEV_STATE_सूचीTY) अणु
			SET_BDEV_STATE(&dc->sb, BDEV_STATE_सूचीTY);
			/* XXX: should करो this synchronously */
			bch_ग_लिखो_bdev_super(dc, शून्य);
		पूर्ण

		bch_ग_लिखोback_queue(dc);
	पूर्ण
पूर्ण

व्योम bcache_dev_sectors_dirty_add(काष्ठा cache_set *c, अचिन्हित पूर्णांक inode,
				  uपूर्णांक64_t offset, पूर्णांक nr_sectors);

व्योम bch_sectors_dirty_init(काष्ठा bcache_device *d);
व्योम bch_cached_dev_ग_लिखोback_init(काष्ठा cached_dev *dc);
पूर्णांक bch_cached_dev_ग_लिखोback_start(काष्ठा cached_dev *dc);

#पूर्ण_अगर
