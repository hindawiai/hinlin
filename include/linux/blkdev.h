<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BLKDEV_H
#घोषणा _LINUX_BLKDEV_H

#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/major.h>
#समावेश <linux/genhd.h>
#समावेश <linux/list.h>
#समावेश <linux/llist.h>
#समावेश <linux/minmax.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/backing-dev-defs.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mempool.h>
#समावेश <linux/pfn.h>
#समावेश <linux/bपन.स>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/gfp.h>
#समावेश <linux/bsg.h>
#समावेश <linux/smp.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/percpu-refcount.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/blkzoned.h>
#समावेश <linux/pm.h>

काष्ठा module;
काष्ठा scsi_ioctl_command;

काष्ठा request_queue;
काष्ठा elevator_queue;
काष्ठा blk_trace;
काष्ठा request;
काष्ठा sg_io_hdr;
काष्ठा bsg_job;
काष्ठा blkcg_gq;
काष्ठा blk_flush_queue;
काष्ठा pr_ops;
काष्ठा rq_qos;
काष्ठा blk_queue_stats;
काष्ठा blk_stat_callback;
काष्ठा blk_keyslot_manager;

#घोषणा BLKDEV_MIN_RQ	4
#घोषणा BLKDEV_MAX_RQ	128	/* Default maximum */

/* Must be consistent with blk_mq_poll_stats_bkt() */
#घोषणा BLK_MQ_POLL_STATS_BKTS 16

/* Doing classic polling */
#घोषणा BLK_MQ_POLL_CLASSIC -1

/*
 * Maximum number of blkcg policies allowed to be रेजिस्टरed concurrently.
 * Defined here to simplअगरy include dependency.
 */
#घोषणा BLKCG_MAX_POLS		5

प्रकार व्योम (rq_end_io_fn)(काष्ठा request *, blk_status_t);

/*
 * request flags */
प्रकार __u32 __bitwise req_flags_t;

/* drive alपढ़ोy may have started this one */
#घोषणा RQF_STARTED		((__क्रमce req_flags_t)(1 << 1))
/* may not be passed by ioscheduler */
#घोषणा RQF_SOFTBARRIER		((__क्रमce req_flags_t)(1 << 3))
/* request क्रम flush sequence */
#घोषणा RQF_FLUSH_SEQ		((__क्रमce req_flags_t)(1 << 4))
/* merge of dअगरferent types, fail separately */
#घोषणा RQF_MIXED_MERGE		((__क्रमce req_flags_t)(1 << 5))
/* track inflight क्रम MQ */
#घोषणा RQF_MQ_INFLIGHT		((__क्रमce req_flags_t)(1 << 6))
/* करोn't call prep क्रम this one */
#घोषणा RQF_DONTPREP		((__क्रमce req_flags_t)(1 << 7))
/* vaguely specअगरied driver पूर्णांकernal error.  Ignored by the block layer */
#घोषणा RQF_FAILED		((__क्रमce req_flags_t)(1 << 10))
/* करोn't warn about errors */
#घोषणा RQF_QUIET		((__क्रमce req_flags_t)(1 << 11))
/* elevator निजी data attached */
#घोषणा RQF_ELVPRIV		((__क्रमce req_flags_t)(1 << 12))
/* account पूर्णांकo disk and partition IO statistics */
#घोषणा RQF_IO_STAT		((__क्रमce req_flags_t)(1 << 13))
/* runसमय pm request */
#घोषणा RQF_PM			((__क्रमce req_flags_t)(1 << 15))
/* on IO scheduler merge hash */
#घोषणा RQF_HASHED		((__क्रमce req_flags_t)(1 << 16))
/* track IO completion समय */
#घोषणा RQF_STATS		((__क्रमce req_flags_t)(1 << 17))
/* Look at ->special_vec क्रम the actual data payload instead of the
   bio chain. */
#घोषणा RQF_SPECIAL_PAYLOAD	((__क्रमce req_flags_t)(1 << 18))
/* The per-zone ग_लिखो lock is held क्रम this request */
#घोषणा RQF_ZONE_WRITE_LOCKED	((__क्रमce req_flags_t)(1 << 19))
/* alपढ़ोy slept क्रम hybrid poll */
#घोषणा RQF_MQ_POLL_SLEPT	((__क्रमce req_flags_t)(1 << 20))
/* ->समयout has been called, करोn't expire again */
#घोषणा RQF_TIMED_OUT		((__क्रमce req_flags_t)(1 << 21))

/* flags that prevent us from merging requests: */
#घोषणा RQF_NOMERGE_FLAGS \
	(RQF_STARTED | RQF_SOFTBARRIER | RQF_FLUSH_SEQ | RQF_SPECIAL_PAYLOAD)

/*
 * Request state क्रम blk-mq.
 */
क्रमागत mq_rq_state अणु
	MQ_RQ_IDLE		= 0,
	MQ_RQ_IN_FLIGHT		= 1,
	MQ_RQ_COMPLETE		= 2,
पूर्ण;

/*
 * Try to put the fields that are referenced together in the same cacheline.
 *
 * If you modअगरy this काष्ठाure, make sure to update blk_rq_init() and
 * especially blk_mq_rq_ctx_init() to take care of the added fields.
 */
काष्ठा request अणु
	काष्ठा request_queue *q;
	काष्ठा blk_mq_ctx *mq_ctx;
	काष्ठा blk_mq_hw_ctx *mq_hctx;

	अचिन्हित पूर्णांक cmd_flags;		/* op and common flags */
	req_flags_t rq_flags;

	पूर्णांक tag;
	पूर्णांक पूर्णांकernal_tag;

	/* the following two fields are पूर्णांकernal, NEVER access directly */
	अचिन्हित पूर्णांक __data_len;	/* total data len */
	sector_t __sector;		/* sector cursor */

	काष्ठा bio *bio;
	काष्ठा bio *biotail;

	काष्ठा list_head queuelist;

	/*
	 * The hash is used inside the scheduler, and समाप्तed once the
	 * request reaches the dispatch list. The ipi_list is only used
	 * to queue the request क्रम softirq completion, which is दीर्घ
	 * after the request has been unhashed (and even हटाओd from
	 * the dispatch list).
	 */
	जोड़ अणु
		काष्ठा hlist_node hash;	/* merge hash */
		काष्ठा llist_node ipi_list;
	पूर्ण;

	/*
	 * The rb_node is only used inside the io scheduler, requests
	 * are pruned when moved to the dispatch queue. So let the
	 * completion_data share space with the rb_node.
	 */
	जोड़ अणु
		काष्ठा rb_node rb_node;	/* sort/lookup */
		काष्ठा bio_vec special_vec;
		व्योम *completion_data;
		पूर्णांक error_count; /* क्रम legacy drivers, करोn't use */
	पूर्ण;

	/*
	 * Three poपूर्णांकers are available क्रम the IO schedulers, अगर they need
	 * more they have to dynamically allocate it.  Flush requests are
	 * never put on the IO scheduler. So let the flush fields share
	 * space with the elevator data.
	 */
	जोड़ अणु
		काष्ठा अणु
			काष्ठा io_cq		*icq;
			व्योम			*priv[2];
		पूर्ण elv;

		काष्ठा अणु
			अचिन्हित पूर्णांक		seq;
			काष्ठा list_head	list;
			rq_end_io_fn		*saved_end_io;
		पूर्ण flush;
	पूर्ण;

	काष्ठा gendisk *rq_disk;
	काष्ठा block_device *part;
#अगर_घोषित CONFIG_BLK_RQ_ALLOC_TIME
	/* Time that the first bio started allocating this request. */
	u64 alloc_समय_ns;
#पूर्ण_अगर
	/* Time that this request was allocated क्रम this IO. */
	u64 start_समय_ns;
	/* Time that I/O was submitted to the device. */
	u64 io_start_समय_ns;

#अगर_घोषित CONFIG_BLK_WBT
	अचिन्हित लघु wbt_flags;
#पूर्ण_अगर
	/*
	 * rq sectors used क्रम blk stats. It has the same value
	 * with blk_rq_sectors(rq), except that it never be zeroed
	 * by completion.
	 */
	अचिन्हित लघु stats_sectors;

	/*
	 * Number of scatter-gather DMA addr+len pairs after
	 * physical address coalescing is perक्रमmed.
	 */
	अचिन्हित लघु nr_phys_segments;

#अगर defined(CONFIG_BLK_DEV_INTEGRITY)
	अचिन्हित लघु nr_पूर्णांकegrity_segments;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION
	काष्ठा bio_crypt_ctx *crypt_ctx;
	काष्ठा blk_ksm_keyslot *crypt_keyslot;
#पूर्ण_अगर

	अचिन्हित लघु ग_लिखो_hपूर्णांक;
	अचिन्हित लघु ioprio;

	क्रमागत mq_rq_state state;
	refcount_t ref;

	अचिन्हित पूर्णांक समयout;
	अचिन्हित दीर्घ deadline;

	जोड़ अणु
		काष्ठा __call_single_data csd;
		u64 fअगरo_समय;
	पूर्ण;

	/*
	 * completion callback.
	 */
	rq_end_io_fn *end_io;
	व्योम *end_io_data;
पूर्ण;

अटल अंतरभूत bool blk_op_is_scsi(अचिन्हित पूर्णांक op)
अणु
	वापस op == REQ_OP_SCSI_IN || op == REQ_OP_SCSI_OUT;
पूर्ण

अटल अंतरभूत bool blk_op_is_निजी(अचिन्हित पूर्णांक op)
अणु
	वापस op == REQ_OP_DRV_IN || op == REQ_OP_DRV_OUT;
पूर्ण

अटल अंतरभूत bool blk_rq_is_scsi(काष्ठा request *rq)
अणु
	वापस blk_op_is_scsi(req_op(rq));
पूर्ण

अटल अंतरभूत bool blk_rq_is_निजी(काष्ठा request *rq)
अणु
	वापस blk_op_is_निजी(req_op(rq));
पूर्ण

अटल अंतरभूत bool blk_rq_is_passthrough(काष्ठा request *rq)
अणु
	वापस blk_rq_is_scsi(rq) || blk_rq_is_निजी(rq);
पूर्ण

अटल अंतरभूत bool bio_is_passthrough(काष्ठा bio *bio)
अणु
	अचिन्हित op = bio_op(bio);

	वापस blk_op_is_scsi(op) || blk_op_is_निजी(op);
पूर्ण

अटल अंतरभूत bool blk_op_is_passthrough(अचिन्हित पूर्णांक op)
अणु
	वापस (blk_op_is_scsi(op & REQ_OP_MASK) ||
			blk_op_is_निजी(op & REQ_OP_MASK));
पूर्ण

अटल अंतरभूत अचिन्हित लघु req_get_ioprio(काष्ठा request *req)
अणु
	वापस req->ioprio;
पूर्ण

#समावेश <linux/elevator.h>

काष्ठा blk_queue_ctx;

काष्ठा bio_vec;

क्रमागत blk_eh_समयr_वापस अणु
	BLK_EH_DONE,		/* drivers has completed the command */
	BLK_EH_RESET_TIMER,	/* reset समयr and try again */
पूर्ण;

क्रमागत blk_queue_state अणु
	Queue_करोwn,
	Queue_up,
पूर्ण;

#घोषणा BLK_TAG_ALLOC_FIFO 0 /* allocate starting from 0 */
#घोषणा BLK_TAG_ALLOC_RR 1 /* allocate starting from last allocated tag */

#घोषणा BLK_SCSI_MAX_CMDS	(256)
#घोषणा BLK_SCSI_CMD_PER_LONG	(BLK_SCSI_MAX_CMDS / (माप(दीर्घ) * 8))

/*
 * Zoned block device models (zoned limit).
 *
 * Note: This needs to be ordered from the least to the most severe
 * restrictions क्रम the inheritance in blk_stack_limits() to work.
 */
क्रमागत blk_zoned_model अणु
	BLK_ZONED_NONE = 0,	/* Regular block device */
	BLK_ZONED_HA,		/* Host-aware zoned block device */
	BLK_ZONED_HM,		/* Host-managed zoned block device */
पूर्ण;

/*
 * BLK_BOUNCE_NONE:	never bounce (शेष)
 * BLK_BOUNCE_HIGH:	bounce all highmem pages
 */
क्रमागत blk_bounce अणु
	BLK_BOUNCE_NONE,
	BLK_BOUNCE_HIGH,
पूर्ण;

काष्ठा queue_limits अणु
	क्रमागत blk_bounce		bounce;
	अचिन्हित दीर्घ		seg_boundary_mask;
	अचिन्हित दीर्घ		virt_boundary_mask;

	अचिन्हित पूर्णांक		max_hw_sectors;
	अचिन्हित पूर्णांक		max_dev_sectors;
	अचिन्हित पूर्णांक		chunk_sectors;
	अचिन्हित पूर्णांक		max_sectors;
	अचिन्हित पूर्णांक		max_segment_size;
	अचिन्हित पूर्णांक		physical_block_size;
	अचिन्हित पूर्णांक		logical_block_size;
	अचिन्हित पूर्णांक		alignment_offset;
	अचिन्हित पूर्णांक		io_min;
	अचिन्हित पूर्णांक		io_opt;
	अचिन्हित पूर्णांक		max_discard_sectors;
	अचिन्हित पूर्णांक		max_hw_discard_sectors;
	अचिन्हित पूर्णांक		max_ग_लिखो_same_sectors;
	अचिन्हित पूर्णांक		max_ग_लिखो_zeroes_sectors;
	अचिन्हित पूर्णांक		max_zone_append_sectors;
	अचिन्हित पूर्णांक		discard_granularity;
	अचिन्हित पूर्णांक		discard_alignment;
	अचिन्हित पूर्णांक		zone_ग_लिखो_granularity;

	अचिन्हित लघु		max_segments;
	अचिन्हित लघु		max_पूर्णांकegrity_segments;
	अचिन्हित लघु		max_discard_segments;

	अचिन्हित अक्षर		misaligned;
	अचिन्हित अक्षर		discard_misaligned;
	अचिन्हित अक्षर		raid_partial_stripes_expensive;
	क्रमागत blk_zoned_model	zoned;
पूर्ण;

प्रकार पूर्णांक (*report_zones_cb)(काष्ठा blk_zone *zone, अचिन्हित पूर्णांक idx,
			       व्योम *data);

व्योम blk_queue_set_zoned(काष्ठा gendisk *disk, क्रमागत blk_zoned_model model);

#अगर_घोषित CONFIG_BLK_DEV_ZONED

#घोषणा BLK_ALL_ZONES  ((अचिन्हित पूर्णांक)-1)
पूर्णांक blkdev_report_zones(काष्ठा block_device *bdev, sector_t sector,
			अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data);
अचिन्हित पूर्णांक blkdev_nr_zones(काष्ठा gendisk *disk);
बाह्य पूर्णांक blkdev_zone_mgmt(काष्ठा block_device *bdev, क्रमागत req_opf op,
			    sector_t sectors, sector_t nr_sectors,
			    gfp_t gfp_mask);
पूर्णांक blk_revalidate_disk_zones(काष्ठा gendisk *disk,
			      व्योम (*update_driver_data)(काष्ठा gendisk *disk));

बाह्य पूर्णांक blkdev_report_zones_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
				     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
बाह्य पूर्णांक blkdev_zone_mgmt_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
				  अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

#अन्यथा /* CONFIG_BLK_DEV_ZONED */

अटल अंतरभूत अचिन्हित पूर्णांक blkdev_nr_zones(काष्ठा gendisk *disk)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक blkdev_report_zones_ioctl(काष्ठा block_device *bdev,
					    भ_शेषe_t mode, अचिन्हित पूर्णांक cmd,
					    अचिन्हित दीर्घ arg)
अणु
	वापस -ENOTTY;
पूर्ण

अटल अंतरभूत पूर्णांक blkdev_zone_mgmt_ioctl(काष्ठा block_device *bdev,
					 भ_शेषe_t mode, अचिन्हित पूर्णांक cmd,
					 अचिन्हित दीर्घ arg)
अणु
	वापस -ENOTTY;
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_DEV_ZONED */

काष्ठा request_queue अणु
	काष्ठा request		*last_merge;
	काष्ठा elevator_queue	*elevator;

	काष्ठा percpu_ref	q_usage_counter;

	काष्ठा blk_queue_stats	*stats;
	काष्ठा rq_qos		*rq_qos;

	स्थिर काष्ठा blk_mq_ops	*mq_ops;

	/* sw queues */
	काष्ठा blk_mq_ctx __percpu	*queue_ctx;

	अचिन्हित पूर्णांक		queue_depth;

	/* hw dispatch queues */
	काष्ठा blk_mq_hw_ctx	**queue_hw_ctx;
	अचिन्हित पूर्णांक		nr_hw_queues;

	काष्ठा backing_dev_info	*backing_dev_info;

	/*
	 * The queue owner माला_लो to use this क्रम whatever they like.
	 * ll_rw_blk करोesn't touch it.
	 */
	व्योम			*queuedata;

	/*
	 * various queue flags, see QUEUE_* below
	 */
	अचिन्हित दीर्घ		queue_flags;
	/*
	 * Number of contexts that have called blk_set_pm_only(). If this
	 * counter is above zero then only RQF_PM requests are processed.
	 */
	atomic_t		pm_only;

	/*
	 * ida allocated id क्रम this queue.  Used to index queues from
	 * ioctx.
	 */
	पूर्णांक			id;

	spinlock_t		queue_lock;

	/*
	 * queue kobject
	 */
	काष्ठा kobject kobj;

	/*
	 * mq queue kobject
	 */
	काष्ठा kobject *mq_kobj;

#अगर_घोषित  CONFIG_BLK_DEV_INTEGRITY
	काष्ठा blk_पूर्णांकegrity पूर्णांकegrity;
#पूर्ण_अगर	/* CONFIG_BLK_DEV_INTEGRITY */

#अगर_घोषित CONFIG_PM
	काष्ठा device		*dev;
	क्रमागत rpm_status		rpm_status;
#पूर्ण_अगर

	/*
	 * queue settings
	 */
	अचिन्हित दीर्घ		nr_requests;	/* Max # of requests */

	अचिन्हित पूर्णांक		dma_pad_mask;
	अचिन्हित पूर्णांक		dma_alignment;

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION
	/* Inline crypto capabilities */
	काष्ठा blk_keyslot_manager *ksm;
#पूर्ण_अगर

	अचिन्हित पूर्णांक		rq_समयout;
	पूर्णांक			poll_nsec;

	काष्ठा blk_stat_callback	*poll_cb;
	काष्ठा blk_rq_stat	poll_stat[BLK_MQ_POLL_STATS_BKTS];

	काष्ठा समयr_list	समयout;
	काष्ठा work_काष्ठा	समयout_work;

	atomic_t		nr_active_requests_shared_sbiपंचांगap;

	काष्ठा list_head	icq_list;
#अगर_घोषित CONFIG_BLK_CGROUP
	DECLARE_BITMAP		(blkcg_pols, BLKCG_MAX_POLS);
	काष्ठा blkcg_gq		*root_blkg;
	काष्ठा list_head	blkg_list;
#पूर्ण_अगर

	काष्ठा queue_limits	limits;

	अचिन्हित पूर्णांक		required_elevator_features;

#अगर_घोषित CONFIG_BLK_DEV_ZONED
	/*
	 * Zoned block device inक्रमmation क्रम request dispatch control.
	 * nr_zones is the total number of zones of the device. This is always
	 * 0 क्रम regular block devices. conv_zones_biपंचांगap is a biपंचांगap of nr_zones
	 * bits which indicates अगर a zone is conventional (bit set) or
	 * sequential (bit clear). seq_zones_wlock is a biपंचांगap of nr_zones
	 * bits which indicates अगर a zone is ग_लिखो locked, that is, अगर a ग_लिखो
	 * request targeting the zone was dispatched. All three fields are
	 * initialized by the low level device driver (e.g. scsi/sd.c).
	 * Stacking drivers (device mappers) may or may not initialize
	 * these fields.
	 *
	 * Reads of this inक्रमmation must be रक्षित with blk_queue_enter() /
	 * blk_queue_निकास(). Modअगरying this inक्रमmation is only allowed जबतक
	 * no requests are being processed. See also blk_mq_मुक्तze_queue() and
	 * blk_mq_unमुक्तze_queue().
	 */
	अचिन्हित पूर्णांक		nr_zones;
	अचिन्हित दीर्घ		*conv_zones_biपंचांगap;
	अचिन्हित दीर्घ		*seq_zones_wlock;
	अचिन्हित पूर्णांक		max_खोलो_zones;
	अचिन्हित पूर्णांक		max_active_zones;
#पूर्ण_अगर /* CONFIG_BLK_DEV_ZONED */

	/*
	 * sg stuff
	 */
	अचिन्हित पूर्णांक		sg_समयout;
	अचिन्हित पूर्णांक		sg_reserved_size;
	पूर्णांक			node;
	काष्ठा mutex		debugfs_mutex;
#अगर_घोषित CONFIG_BLK_DEV_IO_TRACE
	काष्ठा blk_trace __rcu	*blk_trace;
#पूर्ण_अगर
	/*
	 * क्रम flush operations
	 */
	काष्ठा blk_flush_queue	*fq;

	काष्ठा list_head	requeue_list;
	spinlock_t		requeue_lock;
	काष्ठा delayed_work	requeue_work;

	काष्ठा mutex		sysfs_lock;
	काष्ठा mutex		sysfs_dir_lock;

	/*
	 * क्रम reusing dead hctx instance in हाल of updating
	 * nr_hw_queues
	 */
	काष्ठा list_head	unused_hctx_list;
	spinlock_t		unused_hctx_lock;

	पूर्णांक			mq_मुक्तze_depth;

#अगर defined(CONFIG_BLK_DEV_BSG)
	काष्ठा bsg_class_device bsg_dev;
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_DEV_THROTTLING
	/* Throttle data */
	काष्ठा throtl_data *td;
#पूर्ण_अगर
	काष्ठा rcu_head		rcu_head;
	रुको_queue_head_t	mq_मुक्तze_wq;
	/*
	 * Protect concurrent access to q_usage_counter by
	 * percpu_ref_समाप्त() and percpu_ref_reinit().
	 */
	काष्ठा mutex		mq_मुक्तze_lock;

	काष्ठा blk_mq_tag_set	*tag_set;
	काष्ठा list_head	tag_set_list;
	काष्ठा bio_set		bio_split;

	काष्ठा dentry		*debugfs_dir;

#अगर_घोषित CONFIG_BLK_DEBUG_FS
	काष्ठा dentry		*sched_debugfs_dir;
	काष्ठा dentry		*rqos_debugfs_dir;
#पूर्ण_अगर

	bool			mq_sysfs_init_करोne;

	माप_प्रकार			cmd_size;

#घोषणा BLK_MAX_WRITE_HINTS	5
	u64			ग_लिखो_hपूर्णांकs[BLK_MAX_WRITE_HINTS];
पूर्ण;

/* Keep blk_queue_flag_name[] in sync with the definitions below */
#घोषणा QUEUE_FLAG_STOPPED	0	/* queue is stopped */
#घोषणा QUEUE_FLAG_DYING	1	/* queue being torn करोwn */
#घोषणा QUEUE_FLAG_NOMERGES     3	/* disable merge attempts */
#घोषणा QUEUE_FLAG_SAME_COMP	4	/* complete on same CPU-group */
#घोषणा QUEUE_FLAG_FAIL_IO	5	/* fake समयout */
#घोषणा QUEUE_FLAG_NONROT	6	/* non-rotational device (SSD) */
#घोषणा QUEUE_FLAG_VIRT		QUEUE_FLAG_NONROT /* paravirt device */
#घोषणा QUEUE_FLAG_IO_STAT	7	/* करो disk/partitions IO accounting */
#घोषणा QUEUE_FLAG_DISCARD	8	/* supports DISCARD */
#घोषणा QUEUE_FLAG_NOXMERGES	9	/* No extended merges */
#घोषणा QUEUE_FLAG_ADD_RANDOM	10	/* Contributes to अक्रमom pool */
#घोषणा QUEUE_FLAG_SECERASE	11	/* supports secure erase */
#घोषणा QUEUE_FLAG_SAME_FORCE	12	/* क्रमce complete on same CPU */
#घोषणा QUEUE_FLAG_DEAD		13	/* queue tear-करोwn finished */
#घोषणा QUEUE_FLAG_INIT_DONE	14	/* queue is initialized */
#घोषणा QUEUE_FLAG_STABLE_WRITES 15	/* करोn't modअगरy blks until WB is करोne */
#घोषणा QUEUE_FLAG_POLL		16	/* IO polling enabled अगर set */
#घोषणा QUEUE_FLAG_WC		17	/* Write back caching */
#घोषणा QUEUE_FLAG_FUA		18	/* device supports FUA ग_लिखोs */
#घोषणा QUEUE_FLAG_DAX		19	/* device supports DAX */
#घोषणा QUEUE_FLAG_STATS	20	/* track IO start and completion बार */
#घोषणा QUEUE_FLAG_POLL_STATS	21	/* collecting stats क्रम hybrid polling */
#घोषणा QUEUE_FLAG_REGISTERED	22	/* queue has been रेजिस्टरed to a disk */
#घोषणा QUEUE_FLAG_SCSI_PASSTHROUGH 23	/* queue supports SCSI commands */
#घोषणा QUEUE_FLAG_QUIESCED	24	/* queue has been quiesced */
#घोषणा QUEUE_FLAG_PCI_P2PDMA	25	/* device supports PCI p2p requests */
#घोषणा QUEUE_FLAG_ZONE_RESETALL 26	/* supports Zone Reset All */
#घोषणा QUEUE_FLAG_RQ_ALLOC_TIME 27	/* record rq->alloc_समय_ns */
#घोषणा QUEUE_FLAG_HCTX_ACTIVE	28	/* at least one blk-mq hctx is active */
#घोषणा QUEUE_FLAG_NOWAIT       29	/* device supports NOWAIT */

#घोषणा QUEUE_FLAG_MQ_DEFAULT	((1 << QUEUE_FLAG_IO_STAT) |		\
				 (1 << QUEUE_FLAG_SAME_COMP) |		\
				 (1 << QUEUE_FLAG_NOWAIT))

व्योम blk_queue_flag_set(अचिन्हित पूर्णांक flag, काष्ठा request_queue *q);
व्योम blk_queue_flag_clear(अचिन्हित पूर्णांक flag, काष्ठा request_queue *q);
bool blk_queue_flag_test_and_set(अचिन्हित पूर्णांक flag, काष्ठा request_queue *q);

#घोषणा blk_queue_stopped(q)	test_bit(QUEUE_FLAG_STOPPED, &(q)->queue_flags)
#घोषणा blk_queue_dying(q)	test_bit(QUEUE_FLAG_DYING, &(q)->queue_flags)
#घोषणा blk_queue_dead(q)	test_bit(QUEUE_FLAG_DEAD, &(q)->queue_flags)
#घोषणा blk_queue_init_करोne(q)	test_bit(QUEUE_FLAG_INIT_DONE, &(q)->queue_flags)
#घोषणा blk_queue_nomerges(q)	test_bit(QUEUE_FLAG_NOMERGES, &(q)->queue_flags)
#घोषणा blk_queue_noxmerges(q)	\
	test_bit(QUEUE_FLAG_NOXMERGES, &(q)->queue_flags)
#घोषणा blk_queue_nonrot(q)	test_bit(QUEUE_FLAG_NONROT, &(q)->queue_flags)
#घोषणा blk_queue_stable_ग_लिखोs(q) \
	test_bit(QUEUE_FLAG_STABLE_WRITES, &(q)->queue_flags)
#घोषणा blk_queue_io_stat(q)	test_bit(QUEUE_FLAG_IO_STAT, &(q)->queue_flags)
#घोषणा blk_queue_add_अक्रमom(q)	test_bit(QUEUE_FLAG_ADD_RANDOM, &(q)->queue_flags)
#घोषणा blk_queue_discard(q)	test_bit(QUEUE_FLAG_DISCARD, &(q)->queue_flags)
#घोषणा blk_queue_zone_resetall(q)	\
	test_bit(QUEUE_FLAG_ZONE_RESETALL, &(q)->queue_flags)
#घोषणा blk_queue_secure_erase(q) \
	(test_bit(QUEUE_FLAG_SECERASE, &(q)->queue_flags))
#घोषणा blk_queue_dax(q)	test_bit(QUEUE_FLAG_DAX, &(q)->queue_flags)
#घोषणा blk_queue_scsi_passthrough(q)	\
	test_bit(QUEUE_FLAG_SCSI_PASSTHROUGH, &(q)->queue_flags)
#घोषणा blk_queue_pci_p2pdma(q)	\
	test_bit(QUEUE_FLAG_PCI_P2PDMA, &(q)->queue_flags)
#अगर_घोषित CONFIG_BLK_RQ_ALLOC_TIME
#घोषणा blk_queue_rq_alloc_समय(q)	\
	test_bit(QUEUE_FLAG_RQ_ALLOC_TIME, &(q)->queue_flags)
#अन्यथा
#घोषणा blk_queue_rq_alloc_समय(q)	false
#पूर्ण_अगर

#घोषणा blk_noretry_request(rq) \
	((rq)->cmd_flags & (REQ_FAILFAST_DEV|REQ_FAILFAST_TRANSPORT| \
			     REQ_FAILFAST_DRIVER))
#घोषणा blk_queue_quiesced(q)	test_bit(QUEUE_FLAG_QUIESCED, &(q)->queue_flags)
#घोषणा blk_queue_pm_only(q)	atomic_पढ़ो(&(q)->pm_only)
#घोषणा blk_queue_fua(q)	test_bit(QUEUE_FLAG_FUA, &(q)->queue_flags)
#घोषणा blk_queue_रेजिस्टरed(q)	test_bit(QUEUE_FLAG_REGISTERED, &(q)->queue_flags)
#घोषणा blk_queue_noरुको(q)	test_bit(QUEUE_FLAG_NOWAIT, &(q)->queue_flags)

बाह्य व्योम blk_set_pm_only(काष्ठा request_queue *q);
बाह्य व्योम blk_clear_pm_only(काष्ठा request_queue *q);

#घोषणा list_entry_rq(ptr)	list_entry((ptr), काष्ठा request, queuelist)

#घोषणा rq_data_dir(rq)		(op_is_ग_लिखो(req_op(rq)) ? WRITE : READ)

#घोषणा rq_dma_dir(rq) \
	(op_is_ग_लिखो(req_op(rq)) ? DMA_TO_DEVICE : DMA_FROM_DEVICE)

#घोषणा dma_map_bvec(dev, bv, dir, attrs) \
	dma_map_page_attrs(dev, (bv)->bv_page, (bv)->bv_offset, (bv)->bv_len, \
	(dir), (attrs))

#घोषणा queue_to_disk(q)	(dev_to_disk(kobj_to_dev((q)->kobj.parent)))

अटल अंतरभूत bool queue_is_mq(काष्ठा request_queue *q)
अणु
	वापस q->mq_ops;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल अंतरभूत क्रमागत rpm_status queue_rpm_status(काष्ठा request_queue *q)
अणु
	वापस q->rpm_status;
पूर्ण
#अन्यथा
अटल अंतरभूत क्रमागत rpm_status queue_rpm_status(काष्ठा request_queue *q)
अणु
	वापस RPM_ACTIVE;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत क्रमागत blk_zoned_model
blk_queue_zoned_model(काष्ठा request_queue *q)
अणु
	अगर (IS_ENABLED(CONFIG_BLK_DEV_ZONED))
		वापस q->limits.zoned;
	वापस BLK_ZONED_NONE;
पूर्ण

अटल अंतरभूत bool blk_queue_is_zoned(काष्ठा request_queue *q)
अणु
	चयन (blk_queue_zoned_model(q)) अणु
	हाल BLK_ZONED_HA:
	हाल BLK_ZONED_HM:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत sector_t blk_queue_zone_sectors(काष्ठा request_queue *q)
अणु
	वापस blk_queue_is_zoned(q) ? q->limits.chunk_sectors : 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED
अटल अंतरभूत अचिन्हित पूर्णांक blk_queue_nr_zones(काष्ठा request_queue *q)
अणु
	वापस blk_queue_is_zoned(q) ? q->nr_zones : 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_queue_zone_no(काष्ठा request_queue *q,
					     sector_t sector)
अणु
	अगर (!blk_queue_is_zoned(q))
		वापस 0;
	वापस sector >> ilog2(q->limits.chunk_sectors);
पूर्ण

अटल अंतरभूत bool blk_queue_zone_is_seq(काष्ठा request_queue *q,
					 sector_t sector)
अणु
	अगर (!blk_queue_is_zoned(q))
		वापस false;
	अगर (!q->conv_zones_biपंचांगap)
		वापस true;
	वापस !test_bit(blk_queue_zone_no(q, sector), q->conv_zones_biपंचांगap);
पूर्ण

अटल अंतरभूत व्योम blk_queue_max_खोलो_zones(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक max_खोलो_zones)
अणु
	q->max_खोलो_zones = max_खोलो_zones;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_max_खोलो_zones(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->max_खोलो_zones;
पूर्ण

अटल अंतरभूत व्योम blk_queue_max_active_zones(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक max_active_zones)
अणु
	q->max_active_zones = max_active_zones;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_max_active_zones(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->max_active_zones;
पूर्ण
#अन्यथा /* CONFIG_BLK_DEV_ZONED */
अटल अंतरभूत अचिन्हित पूर्णांक blk_queue_nr_zones(काष्ठा request_queue *q)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool blk_queue_zone_is_seq(काष्ठा request_queue *q,
					 sector_t sector)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक blk_queue_zone_no(काष्ठा request_queue *q,
					     sector_t sector)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक queue_max_खोलो_zones(स्थिर काष्ठा request_queue *q)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक queue_max_active_zones(स्थिर काष्ठा request_queue *q)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_ZONED */

अटल अंतरभूत bool rq_is_sync(काष्ठा request *rq)
अणु
	वापस op_is_sync(rq->cmd_flags);
पूर्ण

अटल अंतरभूत bool rq_mergeable(काष्ठा request *rq)
अणु
	अगर (blk_rq_is_passthrough(rq))
		वापस false;

	अगर (req_op(rq) == REQ_OP_FLUSH)
		वापस false;

	अगर (req_op(rq) == REQ_OP_WRITE_ZEROES)
		वापस false;

	अगर (req_op(rq) == REQ_OP_ZONE_APPEND)
		वापस false;

	अगर (rq->cmd_flags & REQ_NOMERGE_FLAGS)
		वापस false;
	अगर (rq->rq_flags & RQF_NOMERGE_FLAGS)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत bool blk_ग_लिखो_same_mergeable(काष्ठा bio *a, काष्ठा bio *b)
अणु
	अगर (bio_page(a) == bio_page(b) &&
	    bio_offset(a) == bio_offset(b))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_queue_depth(काष्ठा request_queue *q)
अणु
	अगर (q->queue_depth)
		वापस q->queue_depth;

	वापस q->nr_requests;
पूर्ण

/*
 * शेष समयout क्रम SG_IO अगर none specअगरied
 */
#घोषणा BLK_DEFAULT_SG_TIMEOUT	(60 * HZ)
#घोषणा BLK_MIN_SG_TIMEOUT	(7 * HZ)

काष्ठा rq_map_data अणु
	काष्ठा page **pages;
	पूर्णांक page_order;
	पूर्णांक nr_entries;
	अचिन्हित दीर्घ offset;
	पूर्णांक null_mapped;
	पूर्णांक from_user;
पूर्ण;

काष्ठा req_iterator अणु
	काष्ठा bvec_iter iter;
	काष्ठा bio *bio;
पूर्ण;

/* This should not be used directly - use rq_क्रम_each_segment */
#घोषणा क्रम_each_bio(_bio)		\
	क्रम (; _bio; _bio = _bio->bi_next)
#घोषणा __rq_क्रम_each_bio(_bio, rq)	\
	अगर ((rq->bio))			\
		क्रम (_bio = (rq)->bio; _bio; _bio = _bio->bi_next)

#घोषणा rq_क्रम_each_segment(bvl, _rq, _iter)			\
	__rq_क्रम_each_bio(_iter.bio, _rq)			\
		bio_क्रम_each_segment(bvl, _iter.bio, _iter.iter)

#घोषणा rq_क्रम_each_bvec(bvl, _rq, _iter)			\
	__rq_क्रम_each_bio(_iter.bio, _rq)			\
		bio_क्रम_each_bvec(bvl, _iter.bio, _iter.iter)

#घोषणा rq_iter_last(bvec, _iter)				\
		(_iter.bio->bi_next == शून्य &&			\
		 bio_iter_last(bvec, _iter.iter))

#अगर_अघोषित ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE
# error	"You should define ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE for your platform"
#पूर्ण_अगर
#अगर ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE
बाह्य व्योम rq_flush_dcache_pages(काष्ठा request *rq);
#अन्यथा
अटल अंतरभूत व्योम rq_flush_dcache_pages(काष्ठा request *rq)
अणु
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक blk_रेजिस्टर_queue(काष्ठा gendisk *disk);
बाह्य व्योम blk_unरेजिस्टर_queue(काष्ठा gendisk *disk);
blk_qc_t submit_bio_noacct(काष्ठा bio *bio);
बाह्य व्योम blk_rq_init(काष्ठा request_queue *q, काष्ठा request *rq);
बाह्य व्योम blk_put_request(काष्ठा request *);
बाह्य काष्ठा request *blk_get_request(काष्ठा request_queue *, अचिन्हित पूर्णांक op,
				       blk_mq_req_flags_t flags);
बाह्य पूर्णांक blk_lld_busy(काष्ठा request_queue *q);
बाह्य पूर्णांक blk_rq_prep_clone(काष्ठा request *rq, काष्ठा request *rq_src,
			     काष्ठा bio_set *bs, gfp_t gfp_mask,
			     पूर्णांक (*bio_ctr)(काष्ठा bio *, काष्ठा bio *, व्योम *),
			     व्योम *data);
बाह्य व्योम blk_rq_unprep_clone(काष्ठा request *rq);
बाह्य blk_status_t blk_insert_cloned_request(काष्ठा request_queue *q,
				     काष्ठा request *rq);
पूर्णांक blk_rq_append_bio(काष्ठा request *rq, काष्ठा bio *bio);
बाह्य व्योम blk_queue_split(काष्ठा bio **);
बाह्य पूर्णांक scsi_verअगरy_blk_ioctl(काष्ठा block_device *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक scsi_cmd_blk_ioctl(काष्ठा block_device *, भ_शेषe_t,
			      अचिन्हित पूर्णांक, व्योम __user *);
बाह्य पूर्णांक scsi_cmd_ioctl(काष्ठा request_queue *, काष्ठा gendisk *, भ_शेषe_t,
			  अचिन्हित पूर्णांक, व्योम __user *);
बाह्य पूर्णांक sg_scsi_ioctl(काष्ठा request_queue *, काष्ठा gendisk *, भ_शेषe_t,
			 काष्ठा scsi_ioctl_command __user *);
बाह्य पूर्णांक get_sg_io_hdr(काष्ठा sg_io_hdr *hdr, स्थिर व्योम __user *argp);
बाह्य पूर्णांक put_sg_io_hdr(स्थिर काष्ठा sg_io_hdr *hdr, व्योम __user *argp);

बाह्य पूर्णांक blk_queue_enter(काष्ठा request_queue *q, blk_mq_req_flags_t flags);
बाह्य व्योम blk_queue_निकास(काष्ठा request_queue *q);
बाह्य व्योम blk_sync_queue(काष्ठा request_queue *q);
बाह्य पूर्णांक blk_rq_map_user(काष्ठा request_queue *, काष्ठा request *,
			   काष्ठा rq_map_data *, व्योम __user *, अचिन्हित दीर्घ,
			   gfp_t);
बाह्य पूर्णांक blk_rq_unmap_user(काष्ठा bio *);
बाह्य पूर्णांक blk_rq_map_kern(काष्ठा request_queue *, काष्ठा request *, व्योम *, अचिन्हित पूर्णांक, gfp_t);
बाह्य पूर्णांक blk_rq_map_user_iov(काष्ठा request_queue *, काष्ठा request *,
			       काष्ठा rq_map_data *, स्थिर काष्ठा iov_iter *,
			       gfp_t);
बाह्य व्योम blk_execute_rq(काष्ठा gendisk *, काष्ठा request *, पूर्णांक);
बाह्य व्योम blk_execute_rq_noरुको(काष्ठा gendisk *,
				  काष्ठा request *, पूर्णांक, rq_end_io_fn *);

/* Helper to convert REQ_OP_XXX to its string क्रमmat XXX */
बाह्य स्थिर अक्षर *blk_op_str(अचिन्हित पूर्णांक op);

पूर्णांक blk_status_to_त्रुटि_सं(blk_status_t status);
blk_status_t त्रुटि_सं_to_blk_status(पूर्णांक त्रुटि_सं);

पूर्णांक blk_poll(काष्ठा request_queue *q, blk_qc_t cookie, bool spin);

अटल अंतरभूत काष्ठा request_queue *bdev_get_queue(काष्ठा block_device *bdev)
अणु
	वापस bdev->bd_disk->queue;	/* this is never शून्य */
पूर्ण

/*
 * The basic unit of block I/O is a sector. It is used in a number of contexts
 * in Linux (blk, bio, genhd). The size of one sector is 512 = 2**9
 * bytes. Variables of type sector_t represent an offset or size that is a
 * multiple of 512 bytes. Hence these two स्थिरants.
 */
#अगर_अघोषित SECTOR_SHIFT
#घोषणा SECTOR_SHIFT 9
#पूर्ण_अगर
#अगर_अघोषित SECTOR_SIZE
#घोषणा SECTOR_SIZE (1 << SECTOR_SHIFT)
#पूर्ण_अगर

/*
 * blk_rq_pos()			: the current sector
 * blk_rq_bytes()		: bytes left in the entire request
 * blk_rq_cur_bytes()		: bytes left in the current segment
 * blk_rq_err_bytes()		: bytes left till the next error boundary
 * blk_rq_sectors()		: sectors left in the entire request
 * blk_rq_cur_sectors()		: sectors left in the current segment
 * blk_rq_stats_sectors()	: sectors of the entire request used क्रम stats
 */
अटल अंतरभूत sector_t blk_rq_pos(स्थिर काष्ठा request *rq)
अणु
	वापस rq->__sector;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_bytes(स्थिर काष्ठा request *rq)
अणु
	वापस rq->__data_len;
पूर्ण

अटल अंतरभूत पूर्णांक blk_rq_cur_bytes(स्थिर काष्ठा request *rq)
अणु
	वापस rq->bio ? bio_cur_bytes(rq->bio) : 0;
पूर्ण

बाह्य अचिन्हित पूर्णांक blk_rq_err_bytes(स्थिर काष्ठा request *rq);

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_sectors(स्थिर काष्ठा request *rq)
अणु
	वापस blk_rq_bytes(rq) >> SECTOR_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_cur_sectors(स्थिर काष्ठा request *rq)
अणु
	वापस blk_rq_cur_bytes(rq) >> SECTOR_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_stats_sectors(स्थिर काष्ठा request *rq)
अणु
	वापस rq->stats_sectors;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_ZONED

/* Helper to convert BLK_ZONE_ZONE_XXX to its string क्रमmat XXX */
स्थिर अक्षर *blk_zone_cond_str(क्रमागत blk_zone_cond zone_cond);

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_zone_no(काष्ठा request *rq)
अणु
	वापस blk_queue_zone_no(rq->q, blk_rq_pos(rq));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_zone_is_seq(काष्ठा request *rq)
अणु
	वापस blk_queue_zone_is_seq(rq->q, blk_rq_pos(rq));
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_ZONED */

/*
 * Some commands like WRITE SAME have a payload or data transfer size which
 * is dअगरferent from the size of the request.  Any driver that supports such
 * commands using the RQF_SPECIAL_PAYLOAD flag needs to use this helper to
 * calculate the data transfer size.
 */
अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_payload_bytes(काष्ठा request *rq)
अणु
	अगर (rq->rq_flags & RQF_SPECIAL_PAYLOAD)
		वापस rq->special_vec.bv_len;
	वापस blk_rq_bytes(rq);
पूर्ण

/*
 * Return the first full biovec in the request.  The caller needs to check that
 * there are any bvecs beक्रमe calling this helper.
 */
अटल अंतरभूत काष्ठा bio_vec req_bvec(काष्ठा request *rq)
अणु
	अगर (rq->rq_flags & RQF_SPECIAL_PAYLOAD)
		वापस rq->special_vec;
	वापस mp_bvec_iter_bvec(rq->bio->bi_io_vec, rq->bio->bi_iter);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_queue_get_max_sectors(काष्ठा request_queue *q,
						     पूर्णांक op)
अणु
	अगर (unlikely(op == REQ_OP_DISCARD || op == REQ_OP_SECURE_ERASE))
		वापस min(q->limits.max_discard_sectors,
			   अच_पूर्णांक_उच्च >> SECTOR_SHIFT);

	अगर (unlikely(op == REQ_OP_WRITE_SAME))
		वापस q->limits.max_ग_लिखो_same_sectors;

	अगर (unlikely(op == REQ_OP_WRITE_ZEROES))
		वापस q->limits.max_ग_लिखो_zeroes_sectors;

	वापस q->limits.max_sectors;
पूर्ण

/*
 * Return maximum size of a request at given offset. Only valid क्रम
 * file प्रणाली requests.
 */
अटल अंतरभूत अचिन्हित पूर्णांक blk_max_size_offset(काष्ठा request_queue *q,
					       sector_t offset,
					       अचिन्हित पूर्णांक chunk_sectors)
अणु
	अगर (!chunk_sectors) अणु
		अगर (q->limits.chunk_sectors)
			chunk_sectors = q->limits.chunk_sectors;
		अन्यथा
			वापस q->limits.max_sectors;
	पूर्ण

	अगर (likely(is_घातer_of_2(chunk_sectors)))
		chunk_sectors -= offset & (chunk_sectors - 1);
	अन्यथा
		chunk_sectors -= sector_भाग(offset, chunk_sectors);

	वापस min(q->limits.max_sectors, chunk_sectors);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_get_max_sectors(काष्ठा request *rq,
						  sector_t offset)
अणु
	काष्ठा request_queue *q = rq->q;

	अगर (blk_rq_is_passthrough(rq))
		वापस q->limits.max_hw_sectors;

	अगर (!q->limits.chunk_sectors ||
	    req_op(rq) == REQ_OP_DISCARD ||
	    req_op(rq) == REQ_OP_SECURE_ERASE)
		वापस blk_queue_get_max_sectors(q, req_op(rq));

	वापस min(blk_max_size_offset(q, offset, 0),
			blk_queue_get_max_sectors(q, req_op(rq)));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_rq_count_bios(काष्ठा request *rq)
अणु
	अचिन्हित पूर्णांक nr_bios = 0;
	काष्ठा bio *bio;

	__rq_क्रम_each_bio(bio, rq)
		nr_bios++;

	वापस nr_bios;
पूर्ण

व्योम blk_steal_bios(काष्ठा bio_list *list, काष्ठा request *rq);

/*
 * Request completion related functions.
 *
 * blk_update_request() completes given number of bytes and updates
 * the request without completing it.
 */
बाह्य bool blk_update_request(काष्ठा request *rq, blk_status_t error,
			       अचिन्हित पूर्णांक nr_bytes);

बाह्य व्योम blk_पात_request(काष्ठा request *);

/*
 * Access functions क्रम manipulating queue properties
 */
बाह्य व्योम blk_cleanup_queue(काष्ठा request_queue *);
व्योम blk_queue_bounce_limit(काष्ठा request_queue *q, क्रमागत blk_bounce limit);
बाह्य व्योम blk_queue_max_hw_sectors(काष्ठा request_queue *, अचिन्हित पूर्णांक);
बाह्य व्योम blk_queue_chunk_sectors(काष्ठा request_queue *, अचिन्हित पूर्णांक);
बाह्य व्योम blk_queue_max_segments(काष्ठा request_queue *, अचिन्हित लघु);
बाह्य व्योम blk_queue_max_discard_segments(काष्ठा request_queue *,
		अचिन्हित लघु);
बाह्य व्योम blk_queue_max_segment_size(काष्ठा request_queue *, अचिन्हित पूर्णांक);
बाह्य व्योम blk_queue_max_discard_sectors(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक max_discard_sectors);
बाह्य व्योम blk_queue_max_ग_लिखो_same_sectors(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक max_ग_लिखो_same_sectors);
बाह्य व्योम blk_queue_max_ग_लिखो_zeroes_sectors(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक max_ग_लिखो_same_sectors);
बाह्य व्योम blk_queue_logical_block_size(काष्ठा request_queue *, अचिन्हित पूर्णांक);
बाह्य व्योम blk_queue_max_zone_append_sectors(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक max_zone_append_sectors);
बाह्य व्योम blk_queue_physical_block_size(काष्ठा request_queue *, अचिन्हित पूर्णांक);
व्योम blk_queue_zone_ग_लिखो_granularity(काष्ठा request_queue *q,
				      अचिन्हित पूर्णांक size);
बाह्य व्योम blk_queue_alignment_offset(काष्ठा request_queue *q,
				       अचिन्हित पूर्णांक alignment);
व्योम blk_queue_update_पढ़ोahead(काष्ठा request_queue *q);
बाह्य व्योम blk_limits_io_min(काष्ठा queue_limits *limits, अचिन्हित पूर्णांक min);
बाह्य व्योम blk_queue_io_min(काष्ठा request_queue *q, अचिन्हित पूर्णांक min);
बाह्य व्योम blk_limits_io_opt(काष्ठा queue_limits *limits, अचिन्हित पूर्णांक opt);
बाह्य व्योम blk_queue_io_opt(काष्ठा request_queue *q, अचिन्हित पूर्णांक opt);
बाह्य व्योम blk_set_queue_depth(काष्ठा request_queue *q, अचिन्हित पूर्णांक depth);
बाह्य व्योम blk_set_शेष_limits(काष्ठा queue_limits *lim);
बाह्य व्योम blk_set_stacking_limits(काष्ठा queue_limits *lim);
बाह्य पूर्णांक blk_stack_limits(काष्ठा queue_limits *t, काष्ठा queue_limits *b,
			    sector_t offset);
बाह्य व्योम disk_stack_limits(काष्ठा gendisk *disk, काष्ठा block_device *bdev,
			      sector_t offset);
बाह्य व्योम blk_queue_update_dma_pad(काष्ठा request_queue *, अचिन्हित पूर्णांक);
बाह्य व्योम blk_queue_segment_boundary(काष्ठा request_queue *, अचिन्हित दीर्घ);
बाह्य व्योम blk_queue_virt_boundary(काष्ठा request_queue *, अचिन्हित दीर्घ);
बाह्य व्योम blk_queue_dma_alignment(काष्ठा request_queue *, पूर्णांक);
बाह्य व्योम blk_queue_update_dma_alignment(काष्ठा request_queue *, पूर्णांक);
बाह्य व्योम blk_queue_rq_समयout(काष्ठा request_queue *, अचिन्हित पूर्णांक);
बाह्य व्योम blk_queue_ग_लिखो_cache(काष्ठा request_queue *q, bool enabled, bool fua);
बाह्य व्योम blk_queue_required_elevator_features(काष्ठा request_queue *q,
						 अचिन्हित पूर्णांक features);
बाह्य bool blk_queue_can_use_dma_map_merging(काष्ठा request_queue *q,
					      काष्ठा device *dev);

/*
 * Number of physical segments as sent to the device.
 *
 * Normally this is the number of discontiguous data segments sent by the
 * submitter.  But क्रम data-less command like discard we might have no
 * actual data segments submitted, but the driver might have to add it's
 * own special payload.  In that हाल we still वापस 1 here so that this
 * special payload will be mapped.
 */
अटल अंतरभूत अचिन्हित लघु blk_rq_nr_phys_segments(काष्ठा request *rq)
अणु
	अगर (rq->rq_flags & RQF_SPECIAL_PAYLOAD)
		वापस 1;
	वापस rq->nr_phys_segments;
पूर्ण

/*
 * Number of discard segments (or ranges) the driver needs to fill in.
 * Each discard bio merged पूर्णांकo a request is counted as one segment.
 */
अटल अंतरभूत अचिन्हित लघु blk_rq_nr_discard_segments(काष्ठा request *rq)
अणु
	वापस max_t(अचिन्हित लघु, rq->nr_phys_segments, 1);
पूर्ण

पूर्णांक __blk_rq_map_sg(काष्ठा request_queue *q, काष्ठा request *rq,
		काष्ठा scatterlist *sglist, काष्ठा scatterlist **last_sg);
अटल अंतरभूत पूर्णांक blk_rq_map_sg(काष्ठा request_queue *q, काष्ठा request *rq,
		काष्ठा scatterlist *sglist)
अणु
	काष्ठा scatterlist *last_sg = शून्य;

	वापस __blk_rq_map_sg(q, rq, sglist, &last_sg);
पूर्ण
बाह्य व्योम blk_dump_rq_flags(काष्ठा request *, अक्षर *);

bool __must_check blk_get_queue(काष्ठा request_queue *);
काष्ठा request_queue *blk_alloc_queue(पूर्णांक node_id);
बाह्य व्योम blk_put_queue(काष्ठा request_queue *);
बाह्य व्योम blk_set_queue_dying(काष्ठा request_queue *);

#अगर_घोषित CONFIG_BLOCK
/*
 * blk_plug permits building a queue of related requests by holding the I/O
 * fragments क्रम a लघु period. This allows merging of sequential requests
 * पूर्णांकo single larger request. As the requests are moved from a per-task list to
 * the device's request_queue in a batch, this results in improved scalability
 * as the lock contention क्रम request_queue lock is reduced.
 *
 * It is ok not to disable preemption when adding the request to the plug list
 * or when attempting a merge, because blk_schedule_flush_list() will only flush
 * the plug list when the task sleeps by itself. For details, please see
 * schedule() where blk_schedule_flush_plug() is called.
 */
काष्ठा blk_plug अणु
	काष्ठा list_head mq_list; /* blk-mq requests */
	काष्ठा list_head cb_list; /* md requires an unplug callback */
	अचिन्हित लघु rq_count;
	bool multiple_queues;
	bool noरुको;
पूर्ण;
#घोषणा BLK_MAX_REQUEST_COUNT 16
#घोषणा BLK_PLUG_FLUSH_SIZE (128 * 1024)

काष्ठा blk_plug_cb;
प्रकार व्योम (*blk_plug_cb_fn)(काष्ठा blk_plug_cb *, bool);
काष्ठा blk_plug_cb अणु
	काष्ठा list_head list;
	blk_plug_cb_fn callback;
	व्योम *data;
पूर्ण;
बाह्य काष्ठा blk_plug_cb *blk_check_plugged(blk_plug_cb_fn unplug,
					     व्योम *data, पूर्णांक size);
बाह्य व्योम blk_start_plug(काष्ठा blk_plug *);
बाह्य व्योम blk_finish_plug(काष्ठा blk_plug *);
बाह्य व्योम blk_flush_plug_list(काष्ठा blk_plug *, bool);

अटल अंतरभूत व्योम blk_flush_plug(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा blk_plug *plug = tsk->plug;

	अगर (plug)
		blk_flush_plug_list(plug, false);
पूर्ण

अटल अंतरभूत व्योम blk_schedule_flush_plug(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा blk_plug *plug = tsk->plug;

	अगर (plug)
		blk_flush_plug_list(plug, true);
पूर्ण

अटल अंतरभूत bool blk_needs_flush_plug(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा blk_plug *plug = tsk->plug;

	वापस plug &&
		 (!list_empty(&plug->mq_list) ||
		 !list_empty(&plug->cb_list));
पूर्ण

पूर्णांक blkdev_issue_flush(काष्ठा block_device *bdev);
दीर्घ nr_blockdev_pages(व्योम);
#अन्यथा /* CONFIG_BLOCK */
काष्ठा blk_plug अणु
पूर्ण;

अटल अंतरभूत व्योम blk_start_plug(काष्ठा blk_plug *plug)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_finish_plug(काष्ठा blk_plug *plug)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_flush_plug(काष्ठा task_काष्ठा *task)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_schedule_flush_plug(काष्ठा task_काष्ठा *task)
अणु
पूर्ण


अटल अंतरभूत bool blk_needs_flush_plug(काष्ठा task_काष्ठा *tsk)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक blkdev_issue_flush(काष्ठा block_device *bdev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत दीर्घ nr_blockdev_pages(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLOCK */

बाह्य व्योम blk_io_schedule(व्योम);

बाह्य पूर्णांक blkdev_issue_ग_लिखो_same(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, काष्ठा page *page);

#घोषणा BLKDEV_DISCARD_SECURE	(1 << 0)	/* issue a secure erase */

बाह्य पूर्णांक blkdev_issue_discard(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, अचिन्हित दीर्घ flags);
बाह्य पूर्णांक __blkdev_issue_discard(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, पूर्णांक flags,
		काष्ठा bio **biop);

#घोषणा BLKDEV_ZERO_NOUNMAP	(1 << 0)  /* करो not मुक्त blocks */
#घोषणा BLKDEV_ZERO_NOFALLBACK	(1 << 1)  /* करोn't ग_लिखो explicit zeroes */

बाह्य पूर्णांक __blkdev_issue_zeroout(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, काष्ठा bio **biop,
		अचिन्हित flags);
बाह्य पूर्णांक blkdev_issue_zeroout(काष्ठा block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, अचिन्हित flags);

अटल अंतरभूत पूर्णांक sb_issue_discard(काष्ठा super_block *sb, sector_t block,
		sector_t nr_blocks, gfp_t gfp_mask, अचिन्हित दीर्घ flags)
अणु
	वापस blkdev_issue_discard(sb->s_bdev,
				    block << (sb->s_blocksize_bits -
					      SECTOR_SHIFT),
				    nr_blocks << (sb->s_blocksize_bits -
						  SECTOR_SHIFT),
				    gfp_mask, flags);
पूर्ण
अटल अंतरभूत पूर्णांक sb_issue_zeroout(काष्ठा super_block *sb, sector_t block,
		sector_t nr_blocks, gfp_t gfp_mask)
अणु
	वापस blkdev_issue_zeroout(sb->s_bdev,
				    block << (sb->s_blocksize_bits -
					      SECTOR_SHIFT),
				    nr_blocks << (sb->s_blocksize_bits -
						  SECTOR_SHIFT),
				    gfp_mask, 0);
पूर्ण

बाह्य पूर्णांक blk_verअगरy_command(अचिन्हित अक्षर *cmd, भ_शेषe_t mode);

अटल अंतरभूत bool bdev_is_partition(काष्ठा block_device *bdev)
अणु
	वापस bdev->bd_partno;
पूर्ण

क्रमागत blk_शेष_limits अणु
	BLK_MAX_SEGMENTS	= 128,
	BLK_SAFE_MAX_SECTORS	= 255,
	BLK_DEF_MAX_SECTORS	= 2560,
	BLK_MAX_SEGMENT_SIZE	= 65536,
	BLK_SEG_BOUNDARY_MASK	= 0xFFFFFFFFUL,
पूर्ण;

अटल अंतरभूत अचिन्हित दीर्घ queue_segment_boundary(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.seg_boundary_mask;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ queue_virt_boundary(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.virt_boundary_mask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_max_sectors(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.max_sectors;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_max_hw_sectors(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.max_hw_sectors;
पूर्ण

अटल अंतरभूत अचिन्हित लघु queue_max_segments(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.max_segments;
पूर्ण

अटल अंतरभूत अचिन्हित लघु queue_max_discard_segments(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.max_discard_segments;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_max_segment_size(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.max_segment_size;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_max_zone_append_sectors(स्थिर काष्ठा request_queue *q)
अणु

	स्थिर काष्ठा queue_limits *l = &q->limits;

	वापस min(l->max_zone_append_sectors, l->max_sectors);
पूर्ण

अटल अंतरभूत अचिन्हित queue_logical_block_size(स्थिर काष्ठा request_queue *q)
अणु
	पूर्णांक retval = 512;

	अगर (q && q->limits.logical_block_size)
		retval = q->limits.logical_block_size;

	वापस retval;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bdev_logical_block_size(काष्ठा block_device *bdev)
अणु
	वापस queue_logical_block_size(bdev_get_queue(bdev));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_physical_block_size(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.physical_block_size;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bdev_physical_block_size(काष्ठा block_device *bdev)
अणु
	वापस queue_physical_block_size(bdev_get_queue(bdev));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_io_min(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.io_min;
पूर्ण

अटल अंतरभूत पूर्णांक bdev_io_min(काष्ठा block_device *bdev)
अणु
	वापस queue_io_min(bdev_get_queue(bdev));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक queue_io_opt(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.io_opt;
पूर्ण

अटल अंतरभूत पूर्णांक bdev_io_opt(काष्ठा block_device *bdev)
अणु
	वापस queue_io_opt(bdev_get_queue(bdev));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
queue_zone_ग_लिखो_granularity(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.zone_ग_लिखो_granularity;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
bdev_zone_ग_लिखो_granularity(काष्ठा block_device *bdev)
अणु
	वापस queue_zone_ग_लिखो_granularity(bdev_get_queue(bdev));
पूर्ण

अटल अंतरभूत पूर्णांक queue_alignment_offset(स्थिर काष्ठा request_queue *q)
अणु
	अगर (q->limits.misaligned)
		वापस -1;

	वापस q->limits.alignment_offset;
पूर्ण

अटल अंतरभूत पूर्णांक queue_limit_alignment_offset(काष्ठा queue_limits *lim, sector_t sector)
अणु
	अचिन्हित पूर्णांक granularity = max(lim->physical_block_size, lim->io_min);
	अचिन्हित पूर्णांक alignment = sector_भाग(sector, granularity >> SECTOR_SHIFT)
		<< SECTOR_SHIFT;

	वापस (granularity + lim->alignment_offset - alignment) % granularity;
पूर्ण

अटल अंतरभूत पूर्णांक bdev_alignment_offset(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (q->limits.misaligned)
		वापस -1;
	अगर (bdev_is_partition(bdev))
		वापस queue_limit_alignment_offset(&q->limits,
				bdev->bd_start_sect);
	वापस q->limits.alignment_offset;
पूर्ण

अटल अंतरभूत पूर्णांक queue_discard_alignment(स्थिर काष्ठा request_queue *q)
अणु
	अगर (q->limits.discard_misaligned)
		वापस -1;

	वापस q->limits.discard_alignment;
पूर्ण

अटल अंतरभूत पूर्णांक queue_limit_discard_alignment(काष्ठा queue_limits *lim, sector_t sector)
अणु
	अचिन्हित पूर्णांक alignment, granularity, offset;

	अगर (!lim->max_discard_sectors)
		वापस 0;

	/* Why are these in bytes, not sectors? */
	alignment = lim->discard_alignment >> SECTOR_SHIFT;
	granularity = lim->discard_granularity >> SECTOR_SHIFT;
	अगर (!granularity)
		वापस 0;

	/* Offset of the partition start in 'granularity' sectors */
	offset = sector_भाग(sector, granularity);

	/* And why करो we करो this modulus *again* in blkdev_issue_discard()? */
	offset = (granularity + alignment - offset) % granularity;

	/* Turn it back पूर्णांकo bytes, gaah */
	वापस offset << SECTOR_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक bdev_discard_alignment(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (bdev_is_partition(bdev))
		वापस queue_limit_discard_alignment(&q->limits,
				bdev->bd_start_sect);
	वापस q->limits.discard_alignment;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bdev_ग_लिखो_same(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (q)
		वापस q->limits.max_ग_लिखो_same_sectors;

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bdev_ग_लिखो_zeroes_sectors(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (q)
		वापस q->limits.max_ग_लिखो_zeroes_sectors;

	वापस 0;
पूर्ण

अटल अंतरभूत क्रमागत blk_zoned_model bdev_zoned_model(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (q)
		वापस blk_queue_zoned_model(q);

	वापस BLK_ZONED_NONE;
पूर्ण

अटल अंतरभूत bool bdev_is_zoned(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (q)
		वापस blk_queue_is_zoned(q);

	वापस false;
पूर्ण

अटल अंतरभूत sector_t bdev_zone_sectors(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (q)
		वापस blk_queue_zone_sectors(q);
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bdev_max_खोलो_zones(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (q)
		वापस queue_max_खोलो_zones(q);
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bdev_max_active_zones(काष्ठा block_device *bdev)
अणु
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (q)
		वापस queue_max_active_zones(q);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक queue_dma_alignment(स्थिर काष्ठा request_queue *q)
अणु
	वापस q ? q->dma_alignment : 511;
पूर्ण

अटल अंतरभूत पूर्णांक blk_rq_aligned(काष्ठा request_queue *q, अचिन्हित दीर्घ addr,
				 अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक alignment = queue_dma_alignment(q) | q->dma_pad_mask;
	वापस !(addr & alignment) && !(len & alignment);
पूर्ण

/* assumes size > 256 */
अटल अंतरभूत अचिन्हित पूर्णांक blksize_bits(अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक bits = 8;
	करो अणु
		bits++;
		size >>= 1;
	पूर्ण जबतक (size > 256);
	वापस bits;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक block_size(काष्ठा block_device *bdev)
अणु
	वापस 1 << bdev->bd_inode->i_blkbits;
पूर्ण

पूर्णांक kblockd_schedule_work(काष्ठा work_काष्ठा *work);
पूर्णांक kblockd_mod_delayed_work_on(पूर्णांक cpu, काष्ठा delayed_work *dwork, अचिन्हित दीर्घ delay);

#घोषणा MODULE_ALIAS_BLOCKDEV(major,minor) \
	MODULE_ALIAS("block-major-" __stringअगरy(major) "-" __stringअगरy(minor))
#घोषणा MODULE_ALIAS_BLOCKDEV_MAJOR(major) \
	MODULE_ALIAS("block-major-" __stringअगरy(major) "-*")

#अगर defined(CONFIG_BLK_DEV_INTEGRITY)

क्रमागत blk_पूर्णांकegrity_flags अणु
	BLK_INTEGRITY_VERIFY		= 1 << 0,
	BLK_INTEGRITY_GENERATE		= 1 << 1,
	BLK_INTEGRITY_DEVICE_CAPABLE	= 1 << 2,
	BLK_INTEGRITY_IP_CHECKSUM	= 1 << 3,
पूर्ण;

काष्ठा blk_पूर्णांकegrity_iter अणु
	व्योम			*prot_buf;
	व्योम			*data_buf;
	sector_t		seed;
	अचिन्हित पूर्णांक		data_size;
	अचिन्हित लघु		पूर्णांकerval;
	स्थिर अक्षर		*disk_name;
पूर्ण;

प्रकार blk_status_t (पूर्णांकegrity_processing_fn) (काष्ठा blk_पूर्णांकegrity_iter *);
प्रकार व्योम (पूर्णांकegrity_prepare_fn) (काष्ठा request *);
प्रकार व्योम (पूर्णांकegrity_complete_fn) (काष्ठा request *, अचिन्हित पूर्णांक);

काष्ठा blk_पूर्णांकegrity_profile अणु
	पूर्णांकegrity_processing_fn		*generate_fn;
	पूर्णांकegrity_processing_fn		*verअगरy_fn;
	पूर्णांकegrity_prepare_fn		*prepare_fn;
	पूर्णांकegrity_complete_fn		*complete_fn;
	स्थिर अक्षर			*name;
पूर्ण;

बाह्य व्योम blk_पूर्णांकegrity_रेजिस्टर(काष्ठा gendisk *, काष्ठा blk_पूर्णांकegrity *);
बाह्य व्योम blk_पूर्णांकegrity_unरेजिस्टर(काष्ठा gendisk *);
बाह्य पूर्णांक blk_पूर्णांकegrity_compare(काष्ठा gendisk *, काष्ठा gendisk *);
बाह्य पूर्णांक blk_rq_map_पूर्णांकegrity_sg(काष्ठा request_queue *, काष्ठा bio *,
				   काष्ठा scatterlist *);
बाह्य पूर्णांक blk_rq_count_पूर्णांकegrity_sg(काष्ठा request_queue *, काष्ठा bio *);

अटल अंतरभूत काष्ठा blk_पूर्णांकegrity *blk_get_पूर्णांकegrity(काष्ठा gendisk *disk)
अणु
	काष्ठा blk_पूर्णांकegrity *bi = &disk->queue->पूर्णांकegrity;

	अगर (!bi->profile)
		वापस शून्य;

	वापस bi;
पूर्ण

अटल अंतरभूत
काष्ठा blk_पूर्णांकegrity *bdev_get_पूर्णांकegrity(काष्ठा block_device *bdev)
अणु
	वापस blk_get_पूर्णांकegrity(bdev->bd_disk);
पूर्ण

अटल अंतरभूत bool
blk_पूर्णांकegrity_queue_supports_पूर्णांकegrity(काष्ठा request_queue *q)
अणु
	वापस q->पूर्णांकegrity.profile;
पूर्ण

अटल अंतरभूत bool blk_पूर्णांकegrity_rq(काष्ठा request *rq)
अणु
	वापस rq->cmd_flags & REQ_INTEGRITY;
पूर्ण

अटल अंतरभूत व्योम blk_queue_max_पूर्णांकegrity_segments(काष्ठा request_queue *q,
						    अचिन्हित पूर्णांक segs)
अणु
	q->limits.max_पूर्णांकegrity_segments = segs;
पूर्ण

अटल अंतरभूत अचिन्हित लघु
queue_max_पूर्णांकegrity_segments(स्थिर काष्ठा request_queue *q)
अणु
	वापस q->limits.max_पूर्णांकegrity_segments;
पूर्ण

/**
 * bio_पूर्णांकegrity_पूर्णांकervals - Return number of पूर्णांकegrity पूर्णांकervals क्रम a bio
 * @bi:		blk_पूर्णांकegrity profile क्रम device
 * @sectors:	Size of the bio in 512-byte sectors
 *
 * Description: The block layer calculates everything in 512 byte
 * sectors but पूर्णांकegrity metadata is करोne in terms of the data पूर्णांकegrity
 * पूर्णांकerval size of the storage device.  Convert the block layer sectors
 * to the appropriate number of पूर्णांकegrity पूर्णांकervals.
 */
अटल अंतरभूत अचिन्हित पूर्णांक bio_पूर्णांकegrity_पूर्णांकervals(काष्ठा blk_पूर्णांकegrity *bi,
						   अचिन्हित पूर्णांक sectors)
अणु
	वापस sectors >> (bi->पूर्णांकerval_exp - 9);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bio_पूर्णांकegrity_bytes(काष्ठा blk_पूर्णांकegrity *bi,
					       अचिन्हित पूर्णांक sectors)
अणु
	वापस bio_पूर्णांकegrity_पूर्णांकervals(bi, sectors) * bi->tuple_size;
पूर्ण

/*
 * Return the first bvec that contains पूर्णांकegrity data.  Only drivers that are
 * limited to a single पूर्णांकegrity segment should use this helper.
 */
अटल अंतरभूत काष्ठा bio_vec *rq_पूर्णांकegrity_vec(काष्ठा request *rq)
अणु
	अगर (WARN_ON_ONCE(queue_max_पूर्णांकegrity_segments(rq->q) > 1))
		वापस शून्य;
	वापस rq->bio->bi_पूर्णांकegrity->bip_vec;
पूर्ण

#अन्यथा /* CONFIG_BLK_DEV_INTEGRITY */

काष्ठा bio;
काष्ठा block_device;
काष्ठा gendisk;
काष्ठा blk_पूर्णांकegrity;

अटल अंतरभूत पूर्णांक blk_पूर्णांकegrity_rq(काष्ठा request *rq)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक blk_rq_count_पूर्णांकegrity_sg(काष्ठा request_queue *q,
					    काष्ठा bio *b)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक blk_rq_map_पूर्णांकegrity_sg(काष्ठा request_queue *q,
					  काष्ठा bio *b,
					  काष्ठा scatterlist *s)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा blk_पूर्णांकegrity *bdev_get_पूर्णांकegrity(काष्ठा block_device *b)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा blk_पूर्णांकegrity *blk_get_पूर्णांकegrity(काष्ठा gendisk *disk)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत bool
blk_पूर्णांकegrity_queue_supports_पूर्णांकegrity(काष्ठा request_queue *q)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक blk_पूर्णांकegrity_compare(काष्ठा gendisk *a, काष्ठा gendisk *b)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम blk_पूर्णांकegrity_रेजिस्टर(काष्ठा gendisk *d,
					 काष्ठा blk_पूर्णांकegrity *b)
अणु
पूर्ण
अटल अंतरभूत व्योम blk_पूर्णांकegrity_unरेजिस्टर(काष्ठा gendisk *d)
अणु
पूर्ण
अटल अंतरभूत व्योम blk_queue_max_पूर्णांकegrity_segments(काष्ठा request_queue *q,
						    अचिन्हित पूर्णांक segs)
अणु
पूर्ण
अटल अंतरभूत अचिन्हित लघु queue_max_पूर्णांकegrity_segments(स्थिर काष्ठा request_queue *q)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bio_पूर्णांकegrity_पूर्णांकervals(काष्ठा blk_पूर्णांकegrity *bi,
						   अचिन्हित पूर्णांक sectors)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक bio_पूर्णांकegrity_bytes(काष्ठा blk_पूर्णांकegrity *bi,
					       अचिन्हित पूर्णांक sectors)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा bio_vec *rq_पूर्णांकegrity_vec(काष्ठा request *rq)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_DEV_INTEGRITY */

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION

bool blk_ksm_रेजिस्टर(काष्ठा blk_keyslot_manager *ksm, काष्ठा request_queue *q);

व्योम blk_ksm_unरेजिस्टर(काष्ठा request_queue *q);

#अन्यथा /* CONFIG_BLK_INLINE_ENCRYPTION */

अटल अंतरभूत bool blk_ksm_रेजिस्टर(काष्ठा blk_keyslot_manager *ksm,
				    काष्ठा request_queue *q)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम blk_ksm_unरेजिस्टर(काष्ठा request_queue *q) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_BLK_INLINE_ENCRYPTION */


काष्ठा block_device_operations अणु
	blk_qc_t (*submit_bio) (काष्ठा bio *bio);
	पूर्णांक (*खोलो) (काष्ठा block_device *, भ_शेषe_t);
	व्योम (*release) (काष्ठा gendisk *, भ_शेषe_t);
	पूर्णांक (*rw_page)(काष्ठा block_device *, sector_t, काष्ठा page *, अचिन्हित पूर्णांक);
	पूर्णांक (*ioctl) (काष्ठा block_device *, भ_शेषe_t, अचिन्हित, अचिन्हित दीर्घ);
	पूर्णांक (*compat_ioctl) (काष्ठा block_device *, भ_शेषe_t, अचिन्हित, अचिन्हित दीर्घ);
	अचिन्हित पूर्णांक (*check_events) (काष्ठा gendisk *disk,
				      अचिन्हित पूर्णांक clearing);
	व्योम (*unlock_native_capacity) (काष्ठा gendisk *);
	पूर्णांक (*getgeo)(काष्ठा block_device *, काष्ठा hd_geometry *);
	पूर्णांक (*set_पढ़ो_only)(काष्ठा block_device *bdev, bool ro);
	/* this callback is with swap_lock and someबार page table lock held */
	व्योम (*swap_slot_मुक्त_notअगरy) (काष्ठा block_device *, अचिन्हित दीर्घ);
	पूर्णांक (*report_zones)(काष्ठा gendisk *, sector_t sector,
			अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data);
	अक्षर *(*devnode)(काष्ठा gendisk *disk, umode_t *mode);
	काष्ठा module *owner;
	स्थिर काष्ठा pr_ops *pr_ops;
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
बाह्य पूर्णांक blkdev_compat_ptr_ioctl(काष्ठा block_device *, भ_शेषe_t,
				      अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
#अन्यथा
#घोषणा blkdev_compat_ptr_ioctl शून्य
#पूर्ण_अगर

बाह्य पूर्णांक bdev_पढ़ो_page(काष्ठा block_device *, sector_t, काष्ठा page *);
बाह्य पूर्णांक bdev_ग_लिखो_page(काष्ठा block_device *, sector_t, काष्ठा page *,
						काष्ठा ग_लिखोback_control *);

#अगर_घोषित CONFIG_BLK_DEV_ZONED
bool blk_req_needs_zone_ग_लिखो_lock(काष्ठा request *rq);
bool blk_req_zone_ग_लिखो_trylock(काष्ठा request *rq);
व्योम __blk_req_zone_ग_लिखो_lock(काष्ठा request *rq);
व्योम __blk_req_zone_ग_लिखो_unlock(काष्ठा request *rq);

अटल अंतरभूत व्योम blk_req_zone_ग_लिखो_lock(काष्ठा request *rq)
अणु
	अगर (blk_req_needs_zone_ग_लिखो_lock(rq))
		__blk_req_zone_ग_लिखो_lock(rq);
पूर्ण

अटल अंतरभूत व्योम blk_req_zone_ग_लिखो_unlock(काष्ठा request *rq)
अणु
	अगर (rq->rq_flags & RQF_ZONE_WRITE_LOCKED)
		__blk_req_zone_ग_लिखो_unlock(rq);
पूर्ण

अटल अंतरभूत bool blk_req_zone_is_ग_लिखो_locked(काष्ठा request *rq)
अणु
	वापस rq->q->seq_zones_wlock &&
		test_bit(blk_rq_zone_no(rq), rq->q->seq_zones_wlock);
पूर्ण

अटल अंतरभूत bool blk_req_can_dispatch_to_zone(काष्ठा request *rq)
अणु
	अगर (!blk_req_needs_zone_ग_लिखो_lock(rq))
		वापस true;
	वापस !blk_req_zone_is_ग_लिखो_locked(rq);
पूर्ण
#अन्यथा
अटल अंतरभूत bool blk_req_needs_zone_ग_लिखो_lock(काष्ठा request *rq)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम blk_req_zone_ग_लिखो_lock(काष्ठा request *rq)
अणु
पूर्ण

अटल अंतरभूत व्योम blk_req_zone_ग_लिखो_unlock(काष्ठा request *rq)
अणु
पूर्ण
अटल अंतरभूत bool blk_req_zone_is_ग_लिखो_locked(काष्ठा request *rq)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool blk_req_can_dispatch_to_zone(काष्ठा request *rq)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_ZONED */

अटल अंतरभूत व्योम blk_wake_io_task(काष्ठा task_काष्ठा *रुकोer)
अणु
	/*
	 * If we're polling, the task itself is करोing the completions. For
	 * that हाल, we करोn't need to signal a wakeup, it's enough to just
	 * mark us as RUNNING.
	 */
	अगर (रुकोer == current)
		__set_current_state(TASK_RUNNING);
	अन्यथा
		wake_up_process(रुकोer);
पूर्ण

अचिन्हित दीर्घ disk_start_io_acct(काष्ठा gendisk *disk, अचिन्हित पूर्णांक sectors,
		अचिन्हित पूर्णांक op);
व्योम disk_end_io_acct(काष्ठा gendisk *disk, अचिन्हित पूर्णांक op,
		अचिन्हित दीर्घ start_समय);

अचिन्हित दीर्घ bio_start_io_acct(काष्ठा bio *bio);
व्योम bio_end_io_acct_remapped(काष्ठा bio *bio, अचिन्हित दीर्घ start_समय,
		काष्ठा block_device *orig_bdev);

/**
 * bio_end_io_acct - end I/O accounting क्रम bio based drivers
 * @bio:	bio to end account क्रम
 * @start:	start समय वापसed by bio_start_io_acct()
 */
अटल अंतरभूत व्योम bio_end_io_acct(काष्ठा bio *bio, अचिन्हित दीर्घ start_समय)
अणु
	वापस bio_end_io_acct_remapped(bio, start_समय, bio->bi_bdev);
पूर्ण

पूर्णांक bdev_पढ़ो_only(काष्ठा block_device *bdev);
पूर्णांक set_blocksize(काष्ठा block_device *bdev, पूर्णांक size);

स्थिर अक्षर *bdevname(काष्ठा block_device *bdev, अक्षर *buffer);
पूर्णांक lookup_bdev(स्थिर अक्षर *pathname, dev_t *dev);

व्योम blkdev_show(काष्ठा seq_file *seqf, off_t offset);

#घोषणा BDEVNAME_SIZE	32	/* Largest string क्रम a blockdev identअगरier */
#घोषणा BDEVT_SIZE	10	/* Largest string क्रम MAJ:MIN क्रम blkdev */
#अगर_घोषित CONFIG_BLOCK
#घोषणा BLKDEV_MAJOR_MAX	512
#अन्यथा
#घोषणा BLKDEV_MAJOR_MAX	0
#पूर्ण_अगर

काष्ठा block_device *blkdev_get_by_path(स्थिर अक्षर *path, भ_शेषe_t mode,
		व्योम *holder);
काष्ठा block_device *blkdev_get_by_dev(dev_t dev, भ_शेषe_t mode, व्योम *holder);
पूर्णांक bd_prepare_to_claim(काष्ठा block_device *bdev, व्योम *holder);
व्योम bd_पात_claiming(काष्ठा block_device *bdev, व्योम *holder);
व्योम blkdev_put(काष्ठा block_device *bdev, भ_शेषe_t mode);

/* just क्रम blk-cgroup, करोn't use अन्यथाwhere */
काष्ठा block_device *blkdev_get_no_खोलो(dev_t dev);
व्योम blkdev_put_no_खोलो(काष्ठा block_device *bdev);

काष्ठा block_device *bdev_alloc(काष्ठा gendisk *disk, u8 partno);
व्योम bdev_add(काष्ठा block_device *bdev, dev_t dev);
काष्ठा block_device *I_BDEV(काष्ठा inode *inode);
काष्ठा block_device *bdgrab(काष्ठा block_device *bdev);
व्योम bdput(काष्ठा block_device *);
पूर्णांक truncate_bdev_range(काष्ठा block_device *bdev, भ_शेषe_t mode, loff_t lstart,
		loff_t lend);

#अगर_घोषित CONFIG_BLOCK
व्योम invalidate_bdev(काष्ठा block_device *bdev);
पूर्णांक sync_blockdev(काष्ठा block_device *bdev);
#अन्यथा
अटल अंतरभूत व्योम invalidate_bdev(काष्ठा block_device *bdev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक sync_blockdev(काष्ठा block_device *bdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
पूर्णांक fsync_bdev(काष्ठा block_device *bdev);

पूर्णांक मुक्तze_bdev(काष्ठा block_device *bdev);
पूर्णांक thaw_bdev(काष्ठा block_device *bdev);

#पूर्ण_अगर /* _LINUX_BLKDEV_H */
