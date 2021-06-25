<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions related to sysfs handling
 */
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/blktrace_api.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blk-cgroup.h>
#समावेश <linux/debugfs.h>

#समावेश "blk.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-debugfs.h"
#समावेश "blk-wbt.h"

काष्ठा queue_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा request_queue *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा request_queue *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल sमाप_प्रकार
queue_var_show(अचिन्हित दीर्घ var, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%lu\n", var);
पूर्ण

अटल sमाप_प्रकार
queue_var_store(अचिन्हित दीर्घ *var, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ v;

	err = kम_से_अदीर्घ(page, 10, &v);
	अगर (err || v > अच_पूर्णांक_उच्च)
		वापस -EINVAL;

	*var = v;

	वापस count;
पूर्ण

अटल sमाप_प्रकार queue_var_store64(s64 *var, स्थिर अक्षर *page)
अणु
	पूर्णांक err;
	s64 v;

	err = kstrtos64(page, 10, &v);
	अगर (err < 0)
		वापस err;

	*var = v;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार queue_requests_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(q->nr_requests, page);
पूर्ण

अटल sमाप_प्रकार
queue_requests_store(काष्ठा request_queue *q, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ nr;
	पूर्णांक ret, err;

	अगर (!queue_is_mq(q))
		वापस -EINVAL;

	ret = queue_var_store(&nr, page, count);
	अगर (ret < 0)
		वापस ret;

	अगर (nr < BLKDEV_MIN_RQ)
		nr = BLKDEV_MIN_RQ;

	err = blk_mq_update_nr_requests(q, nr);
	अगर (err)
		वापस err;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार queue_ra_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	अचिन्हित दीर्घ ra_kb = q->backing_dev_info->ra_pages <<
					(PAGE_SHIFT - 10);

	वापस queue_var_show(ra_kb, (page));
पूर्ण

अटल sमाप_प्रकार
queue_ra_store(काष्ठा request_queue *q, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ ra_kb;
	sमाप_प्रकार ret = queue_var_store(&ra_kb, page, count);

	अगर (ret < 0)
		वापस ret;

	q->backing_dev_info->ra_pages = ra_kb >> (PAGE_SHIFT - 10);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार queue_max_sectors_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	पूर्णांक max_sectors_kb = queue_max_sectors(q) >> 1;

	वापस queue_var_show(max_sectors_kb, (page));
पूर्ण

अटल sमाप_प्रकार queue_max_segments_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(queue_max_segments(q), (page));
पूर्ण

अटल sमाप_प्रकार queue_max_discard_segments_show(काष्ठा request_queue *q,
		अक्षर *page)
अणु
	वापस queue_var_show(queue_max_discard_segments(q), (page));
पूर्ण

अटल sमाप_प्रकार queue_max_पूर्णांकegrity_segments_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(q->limits.max_पूर्णांकegrity_segments, (page));
पूर्ण

अटल sमाप_प्रकार queue_max_segment_size_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(queue_max_segment_size(q), (page));
पूर्ण

अटल sमाप_प्रकार queue_logical_block_size_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(queue_logical_block_size(q), page);
पूर्ण

अटल sमाप_प्रकार queue_physical_block_size_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(queue_physical_block_size(q), page);
पूर्ण

अटल sमाप_प्रकार queue_chunk_sectors_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(q->limits.chunk_sectors, page);
पूर्ण

अटल sमाप_प्रकार queue_io_min_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(queue_io_min(q), page);
पूर्ण

अटल sमाप_प्रकार queue_io_opt_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(queue_io_opt(q), page);
पूर्ण

अटल sमाप_प्रकार queue_discard_granularity_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(q->limits.discard_granularity, page);
पूर्ण

अटल sमाप_प्रकार queue_discard_max_hw_show(काष्ठा request_queue *q, अक्षर *page)
अणु

	वापस प्र_लिखो(page, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ)q->limits.max_hw_discard_sectors << 9);
पूर्ण

अटल sमाप_प्रकार queue_discard_max_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)q->limits.max_discard_sectors << 9);
पूर्ण

अटल sमाप_प्रकार queue_discard_max_store(काष्ठा request_queue *q,
				       स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ max_discard;
	sमाप_प्रकार ret = queue_var_store(&max_discard, page, count);

	अगर (ret < 0)
		वापस ret;

	अगर (max_discard & (q->limits.discard_granularity - 1))
		वापस -EINVAL;

	max_discard >>= 9;
	अगर (max_discard > अच_पूर्णांक_उच्च)
		वापस -EINVAL;

	अगर (max_discard > q->limits.max_hw_discard_sectors)
		max_discard = q->limits.max_hw_discard_sectors;

	q->limits.max_discard_sectors = max_discard;
	वापस ret;
पूर्ण

अटल sमाप_प्रकार queue_discard_zeroes_data_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(0, page);
पूर्ण

अटल sमाप_प्रकार queue_ग_लिखो_same_max_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ)q->limits.max_ग_लिखो_same_sectors << 9);
पूर्ण

अटल sमाप_प्रकार queue_ग_लिखो_zeroes_max_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n",
		(अचिन्हित दीर्घ दीर्घ)q->limits.max_ग_लिखो_zeroes_sectors << 9);
पूर्ण

अटल sमाप_प्रकार queue_zone_ग_लिखो_granularity_show(काष्ठा request_queue *q,
						 अक्षर *page)
अणु
	वापस queue_var_show(queue_zone_ग_लिखो_granularity(q), page);
पूर्ण

अटल sमाप_प्रकार queue_zone_append_max_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	अचिन्हित दीर्घ दीर्घ max_sectors = q->limits.max_zone_append_sectors;

	वापस प्र_लिखो(page, "%llu\n", max_sectors << SECTOR_SHIFT);
पूर्ण

अटल sमाप_प्रकार
queue_max_sectors_store(काष्ठा request_queue *q, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ max_sectors_kb,
		max_hw_sectors_kb = queue_max_hw_sectors(q) >> 1,
			page_kb = 1 << (PAGE_SHIFT - 10);
	sमाप_प्रकार ret = queue_var_store(&max_sectors_kb, page, count);

	अगर (ret < 0)
		वापस ret;

	max_hw_sectors_kb = min_not_zero(max_hw_sectors_kb, (अचिन्हित दीर्घ)
					 q->limits.max_dev_sectors >> 1);

	अगर (max_sectors_kb > max_hw_sectors_kb || max_sectors_kb < page_kb)
		वापस -EINVAL;

	spin_lock_irq(&q->queue_lock);
	q->limits.max_sectors = max_sectors_kb << 1;
	q->backing_dev_info->io_pages = max_sectors_kb >> (PAGE_SHIFT - 10);
	spin_unlock_irq(&q->queue_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार queue_max_hw_sectors_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	पूर्णांक max_hw_sectors_kb = queue_max_hw_sectors(q) >> 1;

	वापस queue_var_show(max_hw_sectors_kb, (page));
पूर्ण

अटल sमाप_प्रकार queue_virt_boundary_mask_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(q->limits.virt_boundary_mask, (page));
पूर्ण

#घोषणा QUEUE_SYSFS_BIT_FNS(name, flag, neg)				\
अटल sमाप_प्रकार								\
queue_##name##_show(काष्ठा request_queue *q, अक्षर *page)		\
अणु									\
	पूर्णांक bit;							\
	bit = test_bit(QUEUE_FLAG_##flag, &q->queue_flags);		\
	वापस queue_var_show(neg ? !bit : bit, page);			\
पूर्ण									\
अटल sमाप_प्रकार								\
queue_##name##_store(काष्ठा request_queue *q, स्थिर अक्षर *page, माप_प्रकार count) \
अणु									\
	अचिन्हित दीर्घ val;						\
	sमाप_प्रकार ret;							\
	ret = queue_var_store(&val, page, count);			\
	अगर (ret < 0)							\
		 वापस ret;						\
	अगर (neg)							\
		val = !val;						\
									\
	अगर (val)							\
		blk_queue_flag_set(QUEUE_FLAG_##flag, q);		\
	अन्यथा								\
		blk_queue_flag_clear(QUEUE_FLAG_##flag, q);		\
	वापस ret;							\
पूर्ण

QUEUE_SYSFS_BIT_FNS(nonrot, NONROT, 1);
QUEUE_SYSFS_BIT_FNS(अक्रमom, ADD_RANDOM, 0);
QUEUE_SYSFS_BIT_FNS(iostats, IO_STAT, 0);
QUEUE_SYSFS_BIT_FNS(stable_ग_लिखोs, STABLE_WRITES, 0);
#अघोषित QUEUE_SYSFS_BIT_FNS

अटल sमाप_प्रकार queue_zoned_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	चयन (blk_queue_zoned_model(q)) अणु
	हाल BLK_ZONED_HA:
		वापस प्र_लिखो(page, "host-aware\n");
	हाल BLK_ZONED_HM:
		वापस प्र_लिखो(page, "host-managed\n");
	शेष:
		वापस प्र_लिखो(page, "none\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार queue_nr_zones_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(blk_queue_nr_zones(q), page);
पूर्ण

अटल sमाप_प्रकार queue_max_खोलो_zones_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(queue_max_खोलो_zones(q), page);
पूर्ण

अटल sमाप_प्रकार queue_max_active_zones_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(queue_max_active_zones(q), page);
पूर्ण

अटल sमाप_प्रकार queue_nomerges_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show((blk_queue_nomerges(q) << 1) |
			       blk_queue_noxmerges(q), page);
पूर्ण

अटल sमाप_प्रकार queue_nomerges_store(काष्ठा request_queue *q, स्थिर अक्षर *page,
				    माप_प्रकार count)
अणु
	अचिन्हित दीर्घ nm;
	sमाप_प्रकार ret = queue_var_store(&nm, page, count);

	अगर (ret < 0)
		वापस ret;

	blk_queue_flag_clear(QUEUE_FLAG_NOMERGES, q);
	blk_queue_flag_clear(QUEUE_FLAG_NOXMERGES, q);
	अगर (nm == 2)
		blk_queue_flag_set(QUEUE_FLAG_NOMERGES, q);
	अन्यथा अगर (nm)
		blk_queue_flag_set(QUEUE_FLAG_NOXMERGES, q);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार queue_rq_affinity_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	bool set = test_bit(QUEUE_FLAG_SAME_COMP, &q->queue_flags);
	bool क्रमce = test_bit(QUEUE_FLAG_SAME_FORCE, &q->queue_flags);

	वापस queue_var_show(set << क्रमce, page);
पूर्ण

अटल sमाप_प्रकार
queue_rq_affinity_store(काष्ठा request_queue *q, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	sमाप_प्रकार ret = -EINVAL;
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ val;

	ret = queue_var_store(&val, page, count);
	अगर (ret < 0)
		वापस ret;

	अगर (val == 2) अणु
		blk_queue_flag_set(QUEUE_FLAG_SAME_COMP, q);
		blk_queue_flag_set(QUEUE_FLAG_SAME_FORCE, q);
	पूर्ण अन्यथा अगर (val == 1) अणु
		blk_queue_flag_set(QUEUE_FLAG_SAME_COMP, q);
		blk_queue_flag_clear(QUEUE_FLAG_SAME_FORCE, q);
	पूर्ण अन्यथा अगर (val == 0) अणु
		blk_queue_flag_clear(QUEUE_FLAG_SAME_COMP, q);
		blk_queue_flag_clear(QUEUE_FLAG_SAME_FORCE, q);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण

अटल sमाप_प्रकार queue_poll_delay_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	पूर्णांक val;

	अगर (q->poll_nsec == BLK_MQ_POLL_CLASSIC)
		val = BLK_MQ_POLL_CLASSIC;
	अन्यथा
		val = q->poll_nsec / 1000;

	वापस प्र_लिखो(page, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार queue_poll_delay_store(काष्ठा request_queue *q, स्थिर अक्षर *page,
				माप_प्रकार count)
अणु
	पूर्णांक err, val;

	अगर (!q->mq_ops || !q->mq_ops->poll)
		वापस -EINVAL;

	err = kstrtoपूर्णांक(page, 10, &val);
	अगर (err < 0)
		वापस err;

	अगर (val == BLK_MQ_POLL_CLASSIC)
		q->poll_nsec = BLK_MQ_POLL_CLASSIC;
	अन्यथा अगर (val >= 0)
		q->poll_nsec = val * 1000;
	अन्यथा
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल sमाप_प्रकार queue_poll_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(test_bit(QUEUE_FLAG_POLL, &q->queue_flags), page);
पूर्ण

अटल sमाप_प्रकार queue_poll_store(काष्ठा request_queue *q, स्थिर अक्षर *page,
				माप_प्रकार count)
अणु
	अचिन्हित दीर्घ poll_on;
	sमाप_प्रकार ret;

	अगर (!q->tag_set || q->tag_set->nr_maps <= HCTX_TYPE_POLL ||
	    !q->tag_set->map[HCTX_TYPE_POLL].nr_queues)
		वापस -EINVAL;

	ret = queue_var_store(&poll_on, page, count);
	अगर (ret < 0)
		वापस ret;

	अगर (poll_on) अणु
		blk_queue_flag_set(QUEUE_FLAG_POLL, q);
	पूर्ण अन्यथा अणु
		blk_mq_मुक्तze_queue(q);
		blk_queue_flag_clear(QUEUE_FLAG_POLL, q);
		blk_mq_unमुक्तze_queue(q);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार queue_io_समयout_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", jअगरfies_to_msecs(q->rq_समयout));
पूर्ण

अटल sमाप_प्रकार queue_io_समयout_store(काष्ठा request_queue *q, स्थिर अक्षर *page,
				  माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = kstrtou32(page, 10, &val);
	अगर (err || val == 0)
		वापस -EINVAL;

	blk_queue_rq_समयout(q, msecs_to_jअगरfies(val));

	वापस count;
पूर्ण

अटल sमाप_प्रकार queue_wb_lat_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	अगर (!wbt_rq_qos(q))
		वापस -EINVAL;

	वापस प्र_लिखो(page, "%llu\n", भाग_u64(wbt_get_min_lat(q), 1000));
पूर्ण

अटल sमाप_प्रकार queue_wb_lat_store(काष्ठा request_queue *q, स्थिर अक्षर *page,
				  माप_प्रकार count)
अणु
	काष्ठा rq_qos *rqos;
	sमाप_प्रकार ret;
	s64 val;

	ret = queue_var_store64(&val, page);
	अगर (ret < 0)
		वापस ret;
	अगर (val < -1)
		वापस -EINVAL;

	rqos = wbt_rq_qos(q);
	अगर (!rqos) अणु
		ret = wbt_init(q);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (val == -1)
		val = wbt_शेष_latency_nsec(q);
	अन्यथा अगर (val >= 0)
		val *= 1000ULL;

	अगर (wbt_get_min_lat(q) == val)
		वापस count;

	/*
	 * Ensure that the queue is idled, in हाल the latency update
	 * ends up either enabling or disabling wbt completely. We can't
	 * have IO inflight अगर that happens.
	 */
	blk_mq_मुक्तze_queue(q);
	blk_mq_quiesce_queue(q);

	wbt_set_min_lat(q, val);

	blk_mq_unquiesce_queue(q);
	blk_mq_unमुक्तze_queue(q);

	वापस count;
पूर्ण

अटल sमाप_प्रकार queue_wc_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	अगर (test_bit(QUEUE_FLAG_WC, &q->queue_flags))
		वापस प्र_लिखो(page, "write back\n");

	वापस प्र_लिखो(page, "write through\n");
पूर्ण

अटल sमाप_प्रकार queue_wc_store(काष्ठा request_queue *q, स्थिर अक्षर *page,
			      माप_प्रकार count)
अणु
	पूर्णांक set = -1;

	अगर (!म_भेदन(page, "write back", 10))
		set = 1;
	अन्यथा अगर (!म_भेदन(page, "write through", 13) ||
		 !म_भेदन(page, "none", 4))
		set = 0;

	अगर (set == -1)
		वापस -EINVAL;

	अगर (set)
		blk_queue_flag_set(QUEUE_FLAG_WC, q);
	अन्यथा
		blk_queue_flag_clear(QUEUE_FLAG_WC, q);

	वापस count;
पूर्ण

अटल sमाप_प्रकार queue_fua_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", test_bit(QUEUE_FLAG_FUA, &q->queue_flags));
पूर्ण

अटल sमाप_प्रकार queue_dax_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	वापस queue_var_show(blk_queue_dax(q), page);
पूर्ण

#घोषणा QUEUE_RO_ENTRY(_prefix, _name)			\
अटल काष्ठा queue_sysfs_entry _prefix##_entry = अणु	\
	.attr	= अणु .name = _name, .mode = 0444 पूर्ण,	\
	.show	= _prefix##_show,			\
पूर्ण;

#घोषणा QUEUE_RW_ENTRY(_prefix, _name)			\
अटल काष्ठा queue_sysfs_entry _prefix##_entry = अणु	\
	.attr	= अणु .name = _name, .mode = 0644 पूर्ण,	\
	.show	= _prefix##_show,			\
	.store	= _prefix##_store,			\
पूर्ण;

QUEUE_RW_ENTRY(queue_requests, "nr_requests");
QUEUE_RW_ENTRY(queue_ra, "read_ahead_kb");
QUEUE_RW_ENTRY(queue_max_sectors, "max_sectors_kb");
QUEUE_RO_ENTRY(queue_max_hw_sectors, "max_hw_sectors_kb");
QUEUE_RO_ENTRY(queue_max_segments, "max_segments");
QUEUE_RO_ENTRY(queue_max_पूर्णांकegrity_segments, "max_integrity_segments");
QUEUE_RO_ENTRY(queue_max_segment_size, "max_segment_size");
QUEUE_RW_ENTRY(elv_iosched, "scheduler");

QUEUE_RO_ENTRY(queue_logical_block_size, "logical_block_size");
QUEUE_RO_ENTRY(queue_physical_block_size, "physical_block_size");
QUEUE_RO_ENTRY(queue_chunk_sectors, "chunk_sectors");
QUEUE_RO_ENTRY(queue_io_min, "minimum_io_size");
QUEUE_RO_ENTRY(queue_io_opt, "optimal_io_size");

QUEUE_RO_ENTRY(queue_max_discard_segments, "max_discard_segments");
QUEUE_RO_ENTRY(queue_discard_granularity, "discard_granularity");
QUEUE_RO_ENTRY(queue_discard_max_hw, "discard_max_hw_bytes");
QUEUE_RW_ENTRY(queue_discard_max, "discard_max_bytes");
QUEUE_RO_ENTRY(queue_discard_zeroes_data, "discard_zeroes_data");

QUEUE_RO_ENTRY(queue_ग_लिखो_same_max, "write_same_max_bytes");
QUEUE_RO_ENTRY(queue_ग_लिखो_zeroes_max, "write_zeroes_max_bytes");
QUEUE_RO_ENTRY(queue_zone_append_max, "zone_append_max_bytes");
QUEUE_RO_ENTRY(queue_zone_ग_लिखो_granularity, "zone_write_granularity");

QUEUE_RO_ENTRY(queue_zoned, "zoned");
QUEUE_RO_ENTRY(queue_nr_zones, "nr_zones");
QUEUE_RO_ENTRY(queue_max_खोलो_zones, "max_open_zones");
QUEUE_RO_ENTRY(queue_max_active_zones, "max_active_zones");

QUEUE_RW_ENTRY(queue_nomerges, "nomerges");
QUEUE_RW_ENTRY(queue_rq_affinity, "rq_affinity");
QUEUE_RW_ENTRY(queue_poll, "io_poll");
QUEUE_RW_ENTRY(queue_poll_delay, "io_poll_delay");
QUEUE_RW_ENTRY(queue_wc, "write_cache");
QUEUE_RO_ENTRY(queue_fua, "fua");
QUEUE_RO_ENTRY(queue_dax, "dax");
QUEUE_RW_ENTRY(queue_io_समयout, "io_timeout");
QUEUE_RW_ENTRY(queue_wb_lat, "wbt_lat_usec");
QUEUE_RO_ENTRY(queue_virt_boundary_mask, "virt_boundary_mask");

#अगर_घोषित CONFIG_BLK_DEV_THROTTLING_LOW
QUEUE_RW_ENTRY(blk_throtl_sample_समय, "throttle_sample_time");
#पूर्ण_अगर

/* legacy alias क्रम logical_block_size: */
अटल काष्ठा queue_sysfs_entry queue_hw_sector_size_entry = अणु
	.attr = अणु.name = "hw_sector_size", .mode = 0444 पूर्ण,
	.show = queue_logical_block_size_show,
पूर्ण;

QUEUE_RW_ENTRY(queue_nonrot, "rotational");
QUEUE_RW_ENTRY(queue_iostats, "iostats");
QUEUE_RW_ENTRY(queue_अक्रमom, "add_random");
QUEUE_RW_ENTRY(queue_stable_ग_लिखोs, "stable_writes");

अटल काष्ठा attribute *queue_attrs[] = अणु
	&queue_requests_entry.attr,
	&queue_ra_entry.attr,
	&queue_max_hw_sectors_entry.attr,
	&queue_max_sectors_entry.attr,
	&queue_max_segments_entry.attr,
	&queue_max_discard_segments_entry.attr,
	&queue_max_पूर्णांकegrity_segments_entry.attr,
	&queue_max_segment_size_entry.attr,
	&elv_iosched_entry.attr,
	&queue_hw_sector_size_entry.attr,
	&queue_logical_block_size_entry.attr,
	&queue_physical_block_size_entry.attr,
	&queue_chunk_sectors_entry.attr,
	&queue_io_min_entry.attr,
	&queue_io_opt_entry.attr,
	&queue_discard_granularity_entry.attr,
	&queue_discard_max_entry.attr,
	&queue_discard_max_hw_entry.attr,
	&queue_discard_zeroes_data_entry.attr,
	&queue_ग_लिखो_same_max_entry.attr,
	&queue_ग_लिखो_zeroes_max_entry.attr,
	&queue_zone_append_max_entry.attr,
	&queue_zone_ग_लिखो_granularity_entry.attr,
	&queue_nonrot_entry.attr,
	&queue_zoned_entry.attr,
	&queue_nr_zones_entry.attr,
	&queue_max_खोलो_zones_entry.attr,
	&queue_max_active_zones_entry.attr,
	&queue_nomerges_entry.attr,
	&queue_rq_affinity_entry.attr,
	&queue_iostats_entry.attr,
	&queue_stable_ग_लिखोs_entry.attr,
	&queue_अक्रमom_entry.attr,
	&queue_poll_entry.attr,
	&queue_wc_entry.attr,
	&queue_fua_entry.attr,
	&queue_dax_entry.attr,
	&queue_wb_lat_entry.attr,
	&queue_poll_delay_entry.attr,
	&queue_io_समयout_entry.attr,
#अगर_घोषित CONFIG_BLK_DEV_THROTTLING_LOW
	&blk_throtl_sample_समय_entry.attr,
#पूर्ण_अगर
	&queue_virt_boundary_mask_entry.attr,
	शून्य,
पूर्ण;

अटल umode_t queue_attr_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				पूर्णांक n)
अणु
	काष्ठा request_queue *q =
		container_of(kobj, काष्ठा request_queue, kobj);

	अगर (attr == &queue_io_समयout_entry.attr &&
		(!q->mq_ops || !q->mq_ops->समयout))
			वापस 0;

	अगर ((attr == &queue_max_खोलो_zones_entry.attr ||
	     attr == &queue_max_active_zones_entry.attr) &&
	    !blk_queue_is_zoned(q))
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute_group queue_attr_group = अणु
	.attrs = queue_attrs,
	.is_visible = queue_attr_visible,
पूर्ण;


#घोषणा to_queue(atr) container_of((atr), काष्ठा queue_sysfs_entry, attr)

अटल sमाप_प्रकार
queue_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr, अक्षर *page)
अणु
	काष्ठा queue_sysfs_entry *entry = to_queue(attr);
	काष्ठा request_queue *q =
		container_of(kobj, काष्ठा request_queue, kobj);
	sमाप_प्रकार res;

	अगर (!entry->show)
		वापस -EIO;
	mutex_lock(&q->sysfs_lock);
	res = entry->show(q, page);
	mutex_unlock(&q->sysfs_lock);
	वापस res;
पूर्ण

अटल sमाप_प्रकार
queue_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
		    स्थिर अक्षर *page, माप_प्रकार length)
अणु
	काष्ठा queue_sysfs_entry *entry = to_queue(attr);
	काष्ठा request_queue *q;
	sमाप_प्रकार res;

	अगर (!entry->store)
		वापस -EIO;

	q = container_of(kobj, काष्ठा request_queue, kobj);
	mutex_lock(&q->sysfs_lock);
	res = entry->store(q, page, length);
	mutex_unlock(&q->sysfs_lock);
	वापस res;
पूर्ण

अटल व्योम blk_मुक्त_queue_rcu(काष्ठा rcu_head *rcu_head)
अणु
	काष्ठा request_queue *q = container_of(rcu_head, काष्ठा request_queue,
					       rcu_head);
	kmem_cache_मुक्त(blk_requestq_cachep, q);
पूर्ण

/* Unconfigure the I/O scheduler and dissociate from the cgroup controller. */
अटल व्योम blk_निकास_queue(काष्ठा request_queue *q)
अणु
	/*
	 * Since the I/O scheduler निकास code may access cgroup inक्रमmation,
	 * perक्रमm I/O scheduler निकास beक्रमe disassociating from the block
	 * cgroup controller.
	 */
	अगर (q->elevator) अणु
		ioc_clear_queue(q);
		__elevator_निकास(q, q->elevator);
	पूर्ण

	/*
	 * Remove all references to @q from the block cgroup controller beक्रमe
	 * restoring @q->queue_lock to aव्योम that restoring this poपूर्णांकer causes
	 * e.g. blkcg_prपूर्णांक_blkgs() to crash.
	 */
	blkcg_निकास_queue(q);

	/*
	 * Since the cgroup code may dereference the @q->backing_dev_info
	 * poपूर्णांकer, only decrease its reference count after having हटाओd the
	 * association with the block cgroup controller.
	 */
	bdi_put(q->backing_dev_info);
पूर्ण

/**
 * blk_release_queue - releases all allocated resources of the request_queue
 * @kobj: poपूर्णांकer to a kobject, whose container is a request_queue
 *
 * This function releases all allocated resources of the request queue.
 *
 * The काष्ठा request_queue refcount is incremented with blk_get_queue() and
 * decremented with blk_put_queue(). Once the refcount reaches 0 this function
 * is called.
 *
 * For drivers that have a request_queue on a gendisk and added with
 * __device_add_disk() the refcount to request_queue will reach 0 with
 * the last put_disk() called by the driver. For drivers which करोn't use
 * __device_add_disk() this happens with blk_cleanup_queue().
 *
 * Drivers exist which depend on the release of the request_queue to be
 * synchronous, it should not be deferred.
 *
 * Context: can sleep
 */
अटल व्योम blk_release_queue(काष्ठा kobject *kobj)
अणु
	काष्ठा request_queue *q =
		container_of(kobj, काष्ठा request_queue, kobj);

	might_sleep();

	अगर (test_bit(QUEUE_FLAG_POLL_STATS, &q->queue_flags))
		blk_stat_हटाओ_callback(q, q->poll_cb);
	blk_stat_मुक्त_callback(q->poll_cb);

	blk_मुक्त_queue_stats(q->stats);

	अगर (queue_is_mq(q)) अणु
		काष्ठा blk_mq_hw_ctx *hctx;
		पूर्णांक i;

		cancel_delayed_work_sync(&q->requeue_work);

		queue_क्रम_each_hw_ctx(q, hctx, i)
			cancel_delayed_work_sync(&hctx->run_work);
	पूर्ण

	blk_निकास_queue(q);

	blk_queue_मुक्त_zone_biपंचांगaps(q);

	अगर (queue_is_mq(q))
		blk_mq_release(q);

	blk_trace_shutकरोwn(q);
	mutex_lock(&q->debugfs_mutex);
	debugfs_हटाओ_recursive(q->debugfs_dir);
	mutex_unlock(&q->debugfs_mutex);

	अगर (queue_is_mq(q))
		blk_mq_debugfs_unरेजिस्टर(q);

	bioset_निकास(&q->bio_split);

	ida_simple_हटाओ(&blk_queue_ida, q->id);
	call_rcu(&q->rcu_head, blk_मुक्त_queue_rcu);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops queue_sysfs_ops = अणु
	.show	= queue_attr_show,
	.store	= queue_attr_store,
पूर्ण;

काष्ठा kobj_type blk_queue_ktype = अणु
	.sysfs_ops	= &queue_sysfs_ops,
	.release	= blk_release_queue,
पूर्ण;

/**
 * blk_रेजिस्टर_queue - रेजिस्टर a block layer queue with sysfs
 * @disk: Disk of which the request queue should be रेजिस्टरed with sysfs.
 */
पूर्णांक blk_रेजिस्टर_queue(काष्ठा gendisk *disk)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = disk_to_dev(disk);
	काष्ठा request_queue *q = disk->queue;

	अगर (WARN_ON(!q))
		वापस -ENXIO;

	WARN_ONCE(blk_queue_रेजिस्टरed(q),
		  "%s is registering an already registered queue\n",
		  kobject_name(&dev->kobj));

	/*
	 * SCSI probing may synchronously create and destroy a lot of
	 * request_queues क्रम non-existent devices.  Shutting करोwn a fully
	 * functional queue takes measureable wallघड़ी समय as RCU grace
	 * periods are involved.  To aव्योम excessive latency in these
	 * हालs, a request_queue starts out in a degraded mode which is
	 * faster to shut करोwn and is made fully functional here as
	 * request_queues क्रम non-existent devices never get रेजिस्टरed.
	 */
	अगर (!blk_queue_init_करोne(q)) अणु
		blk_queue_flag_set(QUEUE_FLAG_INIT_DONE, q);
		percpu_ref_चयन_to_percpu(&q->q_usage_counter);
	पूर्ण

	blk_queue_update_पढ़ोahead(q);

	ret = blk_trace_init_sysfs(dev);
	अगर (ret)
		वापस ret;

	mutex_lock(&q->sysfs_dir_lock);

	ret = kobject_add(&q->kobj, kobject_get(&dev->kobj), "%s", "queue");
	अगर (ret < 0) अणु
		blk_trace_हटाओ_sysfs(dev);
		जाओ unlock;
	पूर्ण

	ret = sysfs_create_group(&q->kobj, &queue_attr_group);
	अगर (ret) अणु
		blk_trace_हटाओ_sysfs(dev);
		kobject_del(&q->kobj);
		kobject_put(&dev->kobj);
		जाओ unlock;
	पूर्ण

	mutex_lock(&q->debugfs_mutex);
	q->debugfs_dir = debugfs_create_dir(kobject_name(q->kobj.parent),
					    blk_debugfs_root);
	mutex_unlock(&q->debugfs_mutex);

	अगर (queue_is_mq(q)) अणु
		__blk_mq_रेजिस्टर_dev(dev, q);
		blk_mq_debugfs_रेजिस्टर(q);
	पूर्ण

	mutex_lock(&q->sysfs_lock);
	अगर (q->elevator) अणु
		ret = elv_रेजिस्टर_queue(q, false);
		अगर (ret) अणु
			mutex_unlock(&q->sysfs_lock);
			mutex_unlock(&q->sysfs_dir_lock);
			kobject_del(&q->kobj);
			blk_trace_हटाओ_sysfs(dev);
			kobject_put(&dev->kobj);
			वापस ret;
		पूर्ण
	पूर्ण

	blk_queue_flag_set(QUEUE_FLAG_REGISTERED, q);
	wbt_enable_शेष(q);
	blk_throtl_रेजिस्टर_queue(q);

	/* Now everything is पढ़ोy and send out KOBJ_ADD uevent */
	kobject_uevent(&q->kobj, KOBJ_ADD);
	अगर (q->elevator)
		kobject_uevent(&q->elevator->kobj, KOBJ_ADD);
	mutex_unlock(&q->sysfs_lock);

	ret = 0;
unlock:
	mutex_unlock(&q->sysfs_dir_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blk_रेजिस्टर_queue);

/**
 * blk_unरेजिस्टर_queue - counterpart of blk_रेजिस्टर_queue()
 * @disk: Disk of which the request queue should be unरेजिस्टरed from sysfs.
 *
 * Note: the caller is responsible क्रम guaranteeing that this function is called
 * after blk_रेजिस्टर_queue() has finished.
 */
व्योम blk_unरेजिस्टर_queue(काष्ठा gendisk *disk)
अणु
	काष्ठा request_queue *q = disk->queue;

	अगर (WARN_ON(!q))
		वापस;

	/* Return early अगर disk->queue was never रेजिस्टरed. */
	अगर (!blk_queue_रेजिस्टरed(q))
		वापस;

	/*
	 * Since sysfs_हटाओ_dir() prevents adding new directory entries
	 * beक्रमe removal of existing entries starts, protect against
	 * concurrent elv_iosched_store() calls.
	 */
	mutex_lock(&q->sysfs_lock);
	blk_queue_flag_clear(QUEUE_FLAG_REGISTERED, q);
	mutex_unlock(&q->sysfs_lock);

	mutex_lock(&q->sysfs_dir_lock);
	/*
	 * Remove the sysfs attributes beक्रमe unरेजिस्टरing the queue data
	 * काष्ठाures that can be modअगरied through sysfs.
	 */
	अगर (queue_is_mq(q))
		blk_mq_unरेजिस्टर_dev(disk_to_dev(disk), q);

	kobject_uevent(&q->kobj, KOBJ_REMOVE);
	kobject_del(&q->kobj);
	blk_trace_हटाओ_sysfs(disk_to_dev(disk));

	mutex_lock(&q->sysfs_lock);
	अगर (q->elevator)
		elv_unरेजिस्टर_queue(q);
	mutex_unlock(&q->sysfs_lock);
	mutex_unlock(&q->sysfs_dir_lock);

	kobject_put(&disk_to_dev(disk)->kobj);
पूर्ण
