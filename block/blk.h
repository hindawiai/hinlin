<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BLK_INTERNAL_H
#घोषणा BLK_INTERNAL_H

#समावेश <linux/idr.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/part_स्थिति.स>
#समावेश <linux/blk-crypto.h>
#समावेश <linux/memblock.h>	/* क्रम max_pfn/max_low_pfn */
#समावेश <xen/xen.h>
#समावेश "blk-crypto-internal.h"
#समावेश "blk-mq.h"
#समावेश "blk-mq-sched.h"

/* Max future समयr expiry क्रम समयouts */
#घोषणा BLK_MAX_TIMEOUT		(5 * HZ)

बाह्य काष्ठा dentry *blk_debugfs_root;

काष्ठा blk_flush_queue अणु
	अचिन्हित पूर्णांक		flush_pending_idx:1;
	अचिन्हित पूर्णांक		flush_running_idx:1;
	blk_status_t 		rq_status;
	अचिन्हित दीर्घ		flush_pending_since;
	काष्ठा list_head	flush_queue[2];
	काष्ठा list_head	flush_data_in_flight;
	काष्ठा request		*flush_rq;

	spinlock_t		mq_flush_lock;
पूर्ण;

बाह्य काष्ठा kmem_cache *blk_requestq_cachep;
बाह्य काष्ठा kobj_type blk_queue_ktype;
बाह्य काष्ठा ida blk_queue_ida;

अटल अंतरभूत काष्ठा blk_flush_queue *
blk_get_flush_queue(काष्ठा request_queue *q, काष्ठा blk_mq_ctx *ctx)
अणु
	वापस blk_mq_map_queue(q, REQ_OP_FLUSH, ctx)->fq;
पूर्ण

अटल अंतरभूत व्योम __blk_get_queue(काष्ठा request_queue *q)
अणु
	kobject_get(&q->kobj);
पूर्ण

अटल अंतरभूत bool
is_flush_rq(काष्ठा request *req, काष्ठा blk_mq_hw_ctx *hctx)
अणु
	वापस hctx->fq->flush_rq == req;
पूर्ण

काष्ठा blk_flush_queue *blk_alloc_flush_queue(पूर्णांक node, पूर्णांक cmd_size,
					      gfp_t flags);
व्योम blk_मुक्त_flush_queue(काष्ठा blk_flush_queue *q);

व्योम blk_मुक्तze_queue(काष्ठा request_queue *q);

#घोषणा BIO_INLINE_VECS 4
काष्ठा bio_vec *bvec_alloc(mempool_t *pool, अचिन्हित लघु *nr_vecs,
		gfp_t gfp_mask);
व्योम bvec_मुक्त(mempool_t *pool, काष्ठा bio_vec *bv, अचिन्हित लघु nr_vecs);

अटल अंतरभूत bool biovec_phys_mergeable(काष्ठा request_queue *q,
		काष्ठा bio_vec *vec1, काष्ठा bio_vec *vec2)
अणु
	अचिन्हित दीर्घ mask = queue_segment_boundary(q);
	phys_addr_t addr1 = page_to_phys(vec1->bv_page) + vec1->bv_offset;
	phys_addr_t addr2 = page_to_phys(vec2->bv_page) + vec2->bv_offset;

	अगर (addr1 + vec1->bv_len != addr2)
		वापस false;
	अगर (xen_करोमुख्य() && !xen_biovec_phys_mergeable(vec1, vec2->bv_page))
		वापस false;
	अगर ((addr1 | mask) != ((addr2 + vec2->bv_len - 1) | mask))
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool __bvec_gap_to_prev(काष्ठा request_queue *q,
		काष्ठा bio_vec *bprv, अचिन्हित पूर्णांक offset)
अणु
	वापस (offset & queue_virt_boundary(q)) ||
		((bprv->bv_offset + bprv->bv_len) & queue_virt_boundary(q));
पूर्ण

/*
 * Check अगर adding a bio_vec after bprv with offset would create a gap in
 * the SG list. Most drivers करोn't care about this, but some करो.
 */
अटल अंतरभूत bool bvec_gap_to_prev(काष्ठा request_queue *q,
		काष्ठा bio_vec *bprv, अचिन्हित पूर्णांक offset)
अणु
	अगर (!queue_virt_boundary(q))
		वापस false;
	वापस __bvec_gap_to_prev(q, bprv, offset);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
व्योम blk_flush_पूर्णांकegrity(व्योम);
bool __bio_पूर्णांकegrity_endio(काष्ठा bio *);
व्योम bio_पूर्णांकegrity_मुक्त(काष्ठा bio *bio);
अटल अंतरभूत bool bio_पूर्णांकegrity_endio(काष्ठा bio *bio)
अणु
	अगर (bio_पूर्णांकegrity(bio))
		वापस __bio_पूर्णांकegrity_endio(bio);
	वापस true;
पूर्ण

bool blk_पूर्णांकegrity_merge_rq(काष्ठा request_queue *, काष्ठा request *,
		काष्ठा request *);
bool blk_पूर्णांकegrity_merge_bio(काष्ठा request_queue *, काष्ठा request *,
		काष्ठा bio *);

अटल अंतरभूत bool पूर्णांकegrity_req_gap_back_merge(काष्ठा request *req,
		काष्ठा bio *next)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(req->bio);
	काष्ठा bio_पूर्णांकegrity_payload *bip_next = bio_पूर्णांकegrity(next);

	वापस bvec_gap_to_prev(req->q, &bip->bip_vec[bip->bip_vcnt - 1],
				bip_next->bip_vec[0].bv_offset);
पूर्ण

अटल अंतरभूत bool पूर्णांकegrity_req_gap_front_merge(काष्ठा request *req,
		काष्ठा bio *bio)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
	काष्ठा bio_पूर्णांकegrity_payload *bip_next = bio_पूर्णांकegrity(req->bio);

	वापस bvec_gap_to_prev(req->q, &bip->bip_vec[bip->bip_vcnt - 1],
				bip_next->bip_vec[0].bv_offset);
पूर्ण

व्योम blk_पूर्णांकegrity_add(काष्ठा gendisk *);
व्योम blk_पूर्णांकegrity_del(काष्ठा gendisk *);
#अन्यथा /* CONFIG_BLK_DEV_INTEGRITY */
अटल अंतरभूत bool blk_पूर्णांकegrity_merge_rq(काष्ठा request_queue *rq,
		काष्ठा request *r1, काष्ठा request *r2)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool blk_पूर्णांकegrity_merge_bio(काष्ठा request_queue *rq,
		काष्ठा request *r, काष्ठा bio *b)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool पूर्णांकegrity_req_gap_back_merge(काष्ठा request *req,
		काष्ठा bio *next)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत bool पूर्णांकegrity_req_gap_front_merge(काष्ठा request *req,
		काष्ठा bio *bio)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम blk_flush_पूर्णांकegrity(व्योम)
अणु
पूर्ण
अटल अंतरभूत bool bio_पूर्णांकegrity_endio(काष्ठा bio *bio)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत व्योम bio_पूर्णांकegrity_मुक्त(काष्ठा bio *bio)
अणु
पूर्ण
अटल अंतरभूत व्योम blk_पूर्णांकegrity_add(काष्ठा gendisk *disk)
अणु
पूर्ण
अटल अंतरभूत व्योम blk_पूर्णांकegrity_del(काष्ठा gendisk *disk)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INTEGRITY */

अचिन्हित दीर्घ blk_rq_समयout(अचिन्हित दीर्घ समयout);
व्योम blk_add_समयr(काष्ठा request *req);

bool blk_attempt_plug_merge(काष्ठा request_queue *q, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs, काष्ठा request **same_queue_rq);
bool blk_bio_list_merge(काष्ठा request_queue *q, काष्ठा list_head *list,
			काष्ठा bio *bio, अचिन्हित पूर्णांक nr_segs);

व्योम blk_account_io_start(काष्ठा request *req);
व्योम blk_account_io_करोne(काष्ठा request *req, u64 now);

/*
 * Internal elevator पूर्णांकerface
 */
#घोषणा ELV_ON_HASH(rq) ((rq)->rq_flags & RQF_HASHED)

व्योम blk_insert_flush(काष्ठा request *rq);

व्योम elevator_init_mq(काष्ठा request_queue *q);
पूर्णांक elevator_चयन_mq(काष्ठा request_queue *q,
			      काष्ठा elevator_type *new_e);
व्योम __elevator_निकास(काष्ठा request_queue *, काष्ठा elevator_queue *);
पूर्णांक elv_रेजिस्टर_queue(काष्ठा request_queue *q, bool uevent);
व्योम elv_unरेजिस्टर_queue(काष्ठा request_queue *q);

अटल अंतरभूत व्योम elevator_निकास(काष्ठा request_queue *q,
		काष्ठा elevator_queue *e)
अणु
	lockdep_निश्चित_held(&q->sysfs_lock);

	blk_mq_sched_मुक्त_requests(q);
	__elevator_निकास(q, e);
पूर्ण

sमाप_प्रकार part_size_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf);
sमाप_प्रकार part_stat_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf);
sमाप_प्रकार part_inflight_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf);
sमाप_प्रकार part_fail_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf);
sमाप_प्रकार part_fail_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf, माप_प्रकार count);
sमाप_प्रकार part_समयout_show(काष्ठा device *, काष्ठा device_attribute *, अक्षर *);
sमाप_प्रकार part_समयout_store(काष्ठा device *, काष्ठा device_attribute *,
				स्थिर अक्षर *, माप_प्रकार);

व्योम __blk_queue_split(काष्ठा bio **bio, अचिन्हित पूर्णांक *nr_segs);
पूर्णांक ll_back_merge_fn(काष्ठा request *req, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs);
पूर्णांक blk_attempt_req_merge(काष्ठा request_queue *q, काष्ठा request *rq,
				काष्ठा request *next);
अचिन्हित पूर्णांक blk_recalc_rq_segments(काष्ठा request *rq);
व्योम blk_rq_set_mixed_merge(काष्ठा request *rq);
bool blk_rq_merge_ok(काष्ठा request *rq, काष्ठा bio *bio);
क्रमागत elv_merge blk_try_merge(काष्ठा request *rq, काष्ठा bio *bio);

पूर्णांक blk_dev_init(व्योम);

/*
 * Contribute to IO statistics IFF:
 *
 *	a) it's attached to a gendisk, and
 *	b) the queue had IO stats enabled when this request was started
 */
अटल अंतरभूत bool blk_करो_io_stat(काष्ठा request *rq)
अणु
	वापस rq->rq_disk && (rq->rq_flags & RQF_IO_STAT);
पूर्ण

अटल अंतरभूत व्योम req_set_nomerge(काष्ठा request_queue *q, काष्ठा request *req)
अणु
	req->cmd_flags |= REQ_NOMERGE;
	अगर (req == q->last_merge)
		q->last_merge = शून्य;
पूर्ण

/*
 * The max size one bio can handle is अच_पूर्णांक_उच्च becasue bvec_iter.bi_size
 * is defined as 'unsigned int', meanसमय it has to aligned to with logical
 * block size which is the minimum accepted unit by hardware.
 */
अटल अंतरभूत अचिन्हित पूर्णांक bio_allowed_max_sectors(काष्ठा request_queue *q)
अणु
	वापस round_करोwn(अच_पूर्णांक_उच्च, queue_logical_block_size(q)) >> 9;
पूर्ण

/*
 * The max bio size which is aligned to q->limits.discard_granularity. This
 * is a hपूर्णांक to split large discard bio in generic block layer, then अगर device
 * driver needs to split the discard bio पूर्णांकo smaller ones, their bi_size can
 * be very probably and easily aligned to discard_granularity of the device's
 * queue.
 */
अटल अंतरभूत अचिन्हित पूर्णांक bio_aligned_discard_max_sectors(
					काष्ठा request_queue *q)
अणु
	वापस round_करोwn(अच_पूर्णांक_उच्च, q->limits.discard_granularity) >>
			SECTOR_SHIFT;
पूर्ण

/*
 * Internal io_context पूर्णांकerface
 */
व्योम get_io_context(काष्ठा io_context *ioc);
काष्ठा io_cq *ioc_lookup_icq(काष्ठा io_context *ioc, काष्ठा request_queue *q);
काष्ठा io_cq *ioc_create_icq(काष्ठा io_context *ioc, काष्ठा request_queue *q,
			     gfp_t gfp_mask);
व्योम ioc_clear_queue(काष्ठा request_queue *q);

पूर्णांक create_task_io_context(काष्ठा task_काष्ठा *task, gfp_t gfp_mask, पूर्णांक node);

/*
 * Internal throttling पूर्णांकerface
 */
#अगर_घोषित CONFIG_BLK_DEV_THROTTLING
बाह्य पूर्णांक blk_throtl_init(काष्ठा request_queue *q);
बाह्य व्योम blk_throtl_निकास(काष्ठा request_queue *q);
बाह्य व्योम blk_throtl_रेजिस्टर_queue(काष्ठा request_queue *q);
bool blk_throtl_bio(काष्ठा bio *bio);
#अन्यथा /* CONFIG_BLK_DEV_THROTTLING */
अटल अंतरभूत पूर्णांक blk_throtl_init(काष्ठा request_queue *q) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम blk_throtl_निकास(काष्ठा request_queue *q) अणु पूर्ण
अटल अंतरभूत व्योम blk_throtl_रेजिस्टर_queue(काष्ठा request_queue *q) अणु पूर्ण
अटल अंतरभूत bool blk_throtl_bio(काष्ठा bio *bio) अणु वापस false; पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_THROTTLING */
#अगर_घोषित CONFIG_BLK_DEV_THROTTLING_LOW
बाह्य sमाप_प्रकार blk_throtl_sample_समय_show(काष्ठा request_queue *q, अक्षर *page);
बाह्य sमाप_प्रकार blk_throtl_sample_समय_store(काष्ठा request_queue *q,
	स्थिर अक्षर *page, माप_प्रकार count);
बाह्य व्योम blk_throtl_bio_endio(काष्ठा bio *bio);
बाह्य व्योम blk_throtl_stat_add(काष्ठा request *rq, u64 समय);
#अन्यथा
अटल अंतरभूत व्योम blk_throtl_bio_endio(काष्ठा bio *bio) अणु पूर्ण
अटल अंतरभूत व्योम blk_throtl_stat_add(काष्ठा request *rq, u64 समय) अणु पूर्ण
#पूर्ण_अगर

व्योम __blk_queue_bounce(काष्ठा request_queue *q, काष्ठा bio **bio);

अटल अंतरभूत bool blk_queue_may_bounce(काष्ठा request_queue *q)
अणु
	वापस IS_ENABLED(CONFIG_BOUNCE) &&
		q->limits.bounce == BLK_BOUNCE_HIGH &&
		max_low_pfn >= max_pfn;
पूर्ण

अटल अंतरभूत व्योम blk_queue_bounce(काष्ठा request_queue *q, काष्ठा bio **bio)
अणु
	अगर (unlikely(blk_queue_may_bounce(q) && bio_has_data(*bio)))
		__blk_queue_bounce(q, bio);	
पूर्ण

#अगर_घोषित CONFIG_BLK_CGROUP_IOLATENCY
बाह्य पूर्णांक blk_iolatency_init(काष्ठा request_queue *q);
#अन्यथा
अटल अंतरभूत पूर्णांक blk_iolatency_init(काष्ठा request_queue *q) अणु वापस 0; पूर्ण
#पूर्ण_अगर

काष्ठा bio *blk_next_bio(काष्ठा bio *bio, अचिन्हित पूर्णांक nr_pages, gfp_t gfp);

#अगर_घोषित CONFIG_BLK_DEV_ZONED
व्योम blk_queue_मुक्त_zone_biपंचांगaps(काष्ठा request_queue *q);
व्योम blk_queue_clear_zone_settings(काष्ठा request_queue *q);
#अन्यथा
अटल अंतरभूत व्योम blk_queue_मुक्त_zone_biपंचांगaps(काष्ठा request_queue *q) अणुपूर्ण
अटल अंतरभूत व्योम blk_queue_clear_zone_settings(काष्ठा request_queue *q) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक blk_alloc_devt(काष्ठा block_device *part, dev_t *devt);
व्योम blk_मुक्त_devt(dev_t devt);
अक्षर *disk_name(काष्ठा gendisk *hd, पूर्णांक partno, अक्षर *buf);
#घोषणा ADDPART_FLAG_NONE	0
#घोषणा ADDPART_FLAG_RAID	1
#घोषणा ADDPART_FLAG_WHOLEDISK	2
पूर्णांक bdev_add_partition(काष्ठा block_device *bdev, पूर्णांक partno,
		sector_t start, sector_t length);
पूर्णांक bdev_del_partition(काष्ठा block_device *bdev, पूर्णांक partno);
पूर्णांक bdev_resize_partition(काष्ठा block_device *bdev, पूर्णांक partno,
		sector_t start, sector_t length);

पूर्णांक bio_add_hw_page(काष्ठा request_queue *q, काष्ठा bio *bio,
		काष्ठा page *page, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक offset,
		अचिन्हित पूर्णांक max_sectors, bool *same_page);

#पूर्ण_अगर /* BLK_INTERNAL_H */
