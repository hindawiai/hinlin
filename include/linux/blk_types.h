<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Block data types and स्थिरants.  Directly include this file only to
 * अवरोध include dependency loop.
 */
#अगर_अघोषित __LINUX_BLK_TYPES_H
#घोषणा __LINUX_BLK_TYPES_H

#समावेश <linux/types.h>
#समावेश <linux/bvec.h>
#समावेश <linux/device.h>
#समावेश <linux/kसमय.स>

काष्ठा bio_set;
काष्ठा bio;
काष्ठा bio_पूर्णांकegrity_payload;
काष्ठा page;
काष्ठा io_context;
काष्ठा cgroup_subsys_state;
प्रकार व्योम (bio_end_io_t) (काष्ठा bio *);
काष्ठा bio_crypt_ctx;

काष्ठा block_device अणु
	sector_t		bd_start_sect;
	काष्ठा disk_stats __percpu *bd_stats;
	अचिन्हित दीर्घ		bd_stamp;
	bool			bd_पढ़ो_only;	/* पढ़ो-only policy */
	dev_t			bd_dev;
	पूर्णांक			bd_खोलोers;
	काष्ठा inode *		bd_inode;	/* will die */
	काष्ठा super_block *	bd_super;
	काष्ठा mutex		bd_mutex;	/* खोलो/बंद mutex */
	व्योम *			bd_claiming;
	काष्ठा device		bd_device;
	व्योम *			bd_holder;
	पूर्णांक			bd_holders;
	bool			bd_ग_लिखो_holder;
#अगर_घोषित CONFIG_SYSFS
	काष्ठा list_head	bd_holder_disks;
#पूर्ण_अगर
	काष्ठा kobject		*bd_holder_dir;
	u8			bd_partno;
	/* number of बार partitions within this device have been खोलोed. */
	अचिन्हित		bd_part_count;

	spinlock_t		bd_size_lock; /* क्रम bd_inode->i_size updates */
	काष्ठा gendisk *	bd_disk;
	काष्ठा backing_dev_info *bd_bdi;

	/* The counter of मुक्तze processes */
	पूर्णांक			bd_fsमुक्तze_count;
	/* Mutex क्रम मुक्तze */
	काष्ठा mutex		bd_fsमुक्तze_mutex;
	काष्ठा super_block	*bd_fsमुक्तze_sb;

	काष्ठा partition_meta_info *bd_meta_info;
#अगर_घोषित CONFIG_FAIL_MAKE_REQUEST
	bool			bd_make_it_fail;
#पूर्ण_अगर
पूर्ण __अक्रमomize_layout;

#घोषणा bdev_whole(_bdev) \
	((_bdev)->bd_disk->part0)

#घोषणा dev_to_bdev(device) \
	container_of((device), काष्ठा block_device, bd_device)

#घोषणा bdev_kobj(_bdev) \
	(&((_bdev)->bd_device.kobj))

/*
 * Block error status values.  See block/blk-core:blk_errors क्रम the details.
 * Alpha cannot ग_लिखो a byte atomically, so we need to use 32-bit value.
 */
#अगर defined(CONFIG_ALPHA) && !defined(__alpha_bwx__)
प्रकार u32 __bitwise blk_status_t;
#अन्यथा
प्रकार u8 __bitwise blk_status_t;
#पूर्ण_अगर
#घोषणा	BLK_STS_OK 0
#घोषणा BLK_STS_NOTSUPP		((__क्रमce blk_status_t)1)
#घोषणा BLK_STS_TIMEOUT		((__क्रमce blk_status_t)2)
#घोषणा BLK_STS_NOSPC		((__क्रमce blk_status_t)3)
#घोषणा BLK_STS_TRANSPORT	((__क्रमce blk_status_t)4)
#घोषणा BLK_STS_TARGET		((__क्रमce blk_status_t)5)
#घोषणा BLK_STS_NEXUS		((__क्रमce blk_status_t)6)
#घोषणा BLK_STS_MEDIUM		((__क्रमce blk_status_t)7)
#घोषणा BLK_STS_PROTECTION	((__क्रमce blk_status_t)8)
#घोषणा BLK_STS_RESOURCE	((__क्रमce blk_status_t)9)
#घोषणा BLK_STS_IOERR		((__क्रमce blk_status_t)10)

/* hack क्रम device mapper, करोn't use अन्यथाwhere: */
#घोषणा BLK_STS_DM_REQUEUE    ((__क्रमce blk_status_t)11)

#घोषणा BLK_STS_AGAIN		((__क्रमce blk_status_t)12)

/*
 * BLK_STS_DEV_RESOURCE is वापसed from the driver to the block layer अगर
 * device related resources are unavailable, but the driver can guarantee
 * that the queue will be rerun in the future once resources become
 * available again. This is typically the हाल क्रम device specअगरic
 * resources that are consumed क्रम IO. If the driver fails allocating these
 * resources, we know that inflight (or pending) IO will मुक्त these
 * resource upon completion.
 *
 * This is dअगरferent from BLK_STS_RESOURCE in that it explicitly references
 * a device specअगरic resource. For resources of wider scope, allocation
 * failure can happen without having pending IO. This means that we can't
 * rely on request completions मुक्तing these resources, as IO may not be in
 * flight. Examples of that are kernel memory allocations, DMA mappings, or
 * any other प्रणाली wide resources.
 */
#घोषणा BLK_STS_DEV_RESOURCE	((__क्रमce blk_status_t)13)

/*
 * BLK_STS_ZONE_RESOURCE is वापसed from the driver to the block layer अगर zone
 * related resources are unavailable, but the driver can guarantee the queue
 * will be rerun in the future once the resources become available again.
 *
 * This is dअगरferent from BLK_STS_DEV_RESOURCE in that it explicitly references
 * a zone specअगरic resource and IO to a dअगरferent zone on the same device could
 * still be served. Examples of that are zones that are ग_लिखो-locked, but a पढ़ो
 * to the same zone could be served.
 */
#घोषणा BLK_STS_ZONE_RESOURCE	((__क्रमce blk_status_t)14)

/*
 * BLK_STS_ZONE_OPEN_RESOURCE is वापसed from the driver in the completion
 * path अगर the device वापसs a status indicating that too many zone resources
 * are currently खोलो. The same command should be successful अगर resubmitted
 * after the number of खोलो zones decreases below the device's limits, which is
 * reported in the request_queue's max_खोलो_zones.
 */
#घोषणा BLK_STS_ZONE_OPEN_RESOURCE	((__क्रमce blk_status_t)15)

/*
 * BLK_STS_ZONE_ACTIVE_RESOURCE is वापसed from the driver in the completion
 * path अगर the device वापसs a status indicating that too many zone resources
 * are currently active. The same command should be successful अगर resubmitted
 * after the number of active zones decreases below the device's limits, which
 * is reported in the request_queue's max_active_zones.
 */
#घोषणा BLK_STS_ZONE_ACTIVE_RESOURCE	((__क्रमce blk_status_t)16)

/**
 * blk_path_error - वापसs true अगर error may be path related
 * @error: status the request was completed with
 *
 * Description:
 *     This classअगरies block error status पूर्णांकo non-retryable errors and ones
 *     that may be successful अगर retried on a failover path.
 *
 * Return:
 *     %false - retrying failover path will not help
 *     %true  - may succeed अगर retried
 */
अटल अंतरभूत bool blk_path_error(blk_status_t error)
अणु
	चयन (error) अणु
	हाल BLK_STS_NOTSUPP:
	हाल BLK_STS_NOSPC:
	हाल BLK_STS_TARGET:
	हाल BLK_STS_NEXUS:
	हाल BLK_STS_MEDIUM:
	हाल BLK_STS_PROTECTION:
		वापस false;
	पूर्ण

	/* Anything अन्यथा could be a path failure, so should be retried */
	वापस true;
पूर्ण

/*
 * From most signअगरicant bit:
 * 1 bit: reserved क्रम other usage, see below
 * 12 bits: original size of bio
 * 51 bits: issue समय of bio
 */
#घोषणा BIO_ISSUE_RES_BITS      1
#घोषणा BIO_ISSUE_SIZE_BITS     12
#घोषणा BIO_ISSUE_RES_SHIFT     (64 - BIO_ISSUE_RES_BITS)
#घोषणा BIO_ISSUE_SIZE_SHIFT    (BIO_ISSUE_RES_SHIFT - BIO_ISSUE_SIZE_BITS)
#घोषणा BIO_ISSUE_TIME_MASK     ((1ULL << BIO_ISSUE_SIZE_SHIFT) - 1)
#घोषणा BIO_ISSUE_SIZE_MASK     \
	(((1ULL << BIO_ISSUE_SIZE_BITS) - 1) << BIO_ISSUE_SIZE_SHIFT)
#घोषणा BIO_ISSUE_RES_MASK      (~((1ULL << BIO_ISSUE_RES_SHIFT) - 1))

/* Reserved bit क्रम blk-throtl */
#घोषणा BIO_ISSUE_THROTL_SKIP_LATENCY (1ULL << 63)

काष्ठा bio_issue अणु
	u64 value;
पूर्ण;

अटल अंतरभूत u64 __bio_issue_समय(u64 समय)
अणु
	वापस समय & BIO_ISSUE_TIME_MASK;
पूर्ण

अटल अंतरभूत u64 bio_issue_समय(काष्ठा bio_issue *issue)
अणु
	वापस __bio_issue_समय(issue->value);
पूर्ण

अटल अंतरभूत sector_t bio_issue_size(काष्ठा bio_issue *issue)
अणु
	वापस ((issue->value & BIO_ISSUE_SIZE_MASK) >> BIO_ISSUE_SIZE_SHIFT);
पूर्ण

अटल अंतरभूत व्योम bio_issue_init(काष्ठा bio_issue *issue,
				       sector_t size)
अणु
	size &= (1ULL << BIO_ISSUE_SIZE_BITS) - 1;
	issue->value = ((issue->value & BIO_ISSUE_RES_MASK) |
			(kसमय_get_ns() & BIO_ISSUE_TIME_MASK) |
			((u64)size << BIO_ISSUE_SIZE_SHIFT));
पूर्ण

/*
 * मुख्य unit of I/O क्रम the block layer and lower layers (ie drivers and
 * stacking drivers)
 */
काष्ठा bio अणु
	काष्ठा bio		*bi_next;	/* request queue link */
	काष्ठा block_device	*bi_bdev;
	अचिन्हित पूर्णांक		bi_opf;		/* bottom bits req flags,
						 * top bits REQ_OP. Use
						 * accessors.
						 */
	अचिन्हित लघु		bi_flags;	/* BIO_* below */
	अचिन्हित लघु		bi_ioprio;
	अचिन्हित लघु		bi_ग_लिखो_hपूर्णांक;
	blk_status_t		bi_status;
	atomic_t		__bi_reमुख्यing;

	काष्ठा bvec_iter	bi_iter;

	bio_end_io_t		*bi_end_io;

	व्योम			*bi_निजी;
#अगर_घोषित CONFIG_BLK_CGROUP
	/*
	 * Represents the association of the css and request_queue क्रम the bio.
	 * If a bio goes direct to device, it will not have a blkg as it will
	 * not have a request_queue associated with it.  The reference is put
	 * on release of the bio.
	 */
	काष्ठा blkcg_gq		*bi_blkg;
	काष्ठा bio_issue	bi_issue;
#अगर_घोषित CONFIG_BLK_CGROUP_IOCOST
	u64			bi_iocost_cost;
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_BLK_INLINE_ENCRYPTION
	काष्ठा bio_crypt_ctx	*bi_crypt_context;
#पूर्ण_अगर

	जोड़ अणु
#अगर defined(CONFIG_BLK_DEV_INTEGRITY)
		काष्ठा bio_पूर्णांकegrity_payload *bi_पूर्णांकegrity; /* data पूर्णांकegrity */
#पूर्ण_अगर
	पूर्ण;

	अचिन्हित लघु		bi_vcnt;	/* how many bio_vec's */

	/*
	 * Everything starting with bi_max_vecs will be preserved by bio_reset()
	 */

	अचिन्हित लघु		bi_max_vecs;	/* max bvl_vecs we can hold */

	atomic_t		__bi_cnt;	/* pin count */

	काष्ठा bio_vec		*bi_io_vec;	/* the actual vec list */

	काष्ठा bio_set		*bi_pool;

	/*
	 * We can अंतरभूत a number of vecs at the end of the bio, to aव्योम
	 * द्विगुन allocations क्रम a small number of bio_vecs. This member
	 * MUST obviously be kept at the very end of the bio.
	 */
	काष्ठा bio_vec		bi_अंतरभूत_vecs[];
पूर्ण;

#घोषणा BIO_RESET_BYTES		दुरत्व(काष्ठा bio, bi_max_vecs)

/*
 * bio flags
 */
क्रमागत अणु
	BIO_NO_PAGE_REF,	/* करोn't put release vec pages */
	BIO_CLONED,		/* करोesn't own data */
	BIO_BOUNCED,		/* bio is a bounce bio */
	BIO_WORKINGSET,		/* contains userspace workingset pages */
	BIO_QUIET,		/* Make BIO Quiet */
	BIO_CHAIN,		/* chained bio, ->bi_reमुख्यing in effect */
	BIO_REFFED,		/* bio has elevated ->bi_cnt */
	BIO_THROTTLED,		/* This bio has alपढ़ोy been subjected to
				 * throttling rules. Don't करो it again. */
	BIO_TRACE_COMPLETION,	/* bio_endio() should trace the final completion
				 * of this bio. */
	BIO_CGROUP_ACCT,	/* has been accounted to a cgroup */
	BIO_TRACKED,		/* set अगर bio goes through the rq_qos path */
	BIO_REMAPPED,
	BIO_FLAG_LAST
पूर्ण;

प्रकार __u32 __bitwise blk_mq_req_flags_t;

/*
 * Operations and flags common to the bio and request काष्ठाures.
 * We use 8 bits क्रम encoding the operation, and the reमुख्यing 24 क्रम flags.
 *
 * The least signअगरicant bit of the operation number indicates the data
 * transfer direction:
 *
 *   - अगर the least signअगरicant bit is set transfers are TO the device
 *   - अगर the least signअगरicant bit is not set transfers are FROM the device
 *
 * If a operation करोes not transfer data the least signअगरicant bit has no
 * meaning.
 */
#घोषणा REQ_OP_BITS	8
#घोषणा REQ_OP_MASK	((1 << REQ_OP_BITS) - 1)
#घोषणा REQ_FLAG_BITS	24

क्रमागत req_opf अणु
	/* पढ़ो sectors from the device */
	REQ_OP_READ		= 0,
	/* ग_लिखो sectors to the device */
	REQ_OP_WRITE		= 1,
	/* flush the अस्थिर ग_लिखो cache */
	REQ_OP_FLUSH		= 2,
	/* discard sectors */
	REQ_OP_DISCARD		= 3,
	/* securely erase sectors */
	REQ_OP_SECURE_ERASE	= 5,
	/* ग_लिखो the same sector many बार */
	REQ_OP_WRITE_SAME	= 7,
	/* ग_लिखो the zero filled sector many बार */
	REQ_OP_WRITE_ZEROES	= 9,
	/* Open a zone */
	REQ_OP_ZONE_OPEN	= 10,
	/* Close a zone */
	REQ_OP_ZONE_CLOSE	= 11,
	/* Transition a zone to full */
	REQ_OP_ZONE_FINISH	= 12,
	/* ग_लिखो data at the current zone ग_लिखो poपूर्णांकer */
	REQ_OP_ZONE_APPEND	= 13,
	/* reset a zone ग_लिखो poपूर्णांकer */
	REQ_OP_ZONE_RESET	= 15,
	/* reset all the zone present on the device */
	REQ_OP_ZONE_RESET_ALL	= 17,

	/* SCSI passthrough using काष्ठा scsi_request */
	REQ_OP_SCSI_IN		= 32,
	REQ_OP_SCSI_OUT		= 33,
	/* Driver निजी requests */
	REQ_OP_DRV_IN		= 34,
	REQ_OP_DRV_OUT		= 35,

	REQ_OP_LAST,
पूर्ण;

क्रमागत req_flag_bits अणु
	__REQ_FAILFAST_DEV =	/* no driver retries of device errors */
		REQ_OP_BITS,
	__REQ_FAILFAST_TRANSPORT, /* no driver retries of transport errors */
	__REQ_FAILFAST_DRIVER,	/* no driver retries of driver errors */
	__REQ_SYNC,		/* request is sync (sync ग_लिखो or पढ़ो) */
	__REQ_META,		/* metadata io request */
	__REQ_PRIO,		/* boost priority in cfq */
	__REQ_NOMERGE,		/* करोn't touch this क्रम merging */
	__REQ_IDLE,		/* anticipate more IO after this one */
	__REQ_INTEGRITY,	/* I/O includes block पूर्णांकegrity payload */
	__REQ_FUA,		/* क्रमced unit access */
	__REQ_PREFLUSH,		/* request क्रम cache flush */
	__REQ_RAHEAD,		/* पढ़ो ahead, can fail anyसमय */
	__REQ_BACKGROUND,	/* background IO */
	__REQ_NOWAIT,           /* Don't रुको अगर request will block */
	/*
	 * When a shared kthपढ़ो needs to issue a bio क्रम a cgroup, करोing
	 * so synchronously can lead to priority inversions as the kthपढ़ो
	 * can be trapped रुकोing क्रम that cgroup.  CGROUP_PUNT flag makes
	 * submit_bio() punt the actual issuing to a dedicated per-blkcg
	 * work item to aव्योम such priority inversions.
	 */
	__REQ_CGROUP_PUNT,

	/* command specअगरic flags क्रम REQ_OP_WRITE_ZEROES: */
	__REQ_NOUNMAP,		/* करो not मुक्त blocks when zeroing */

	__REQ_HIPRI,

	/* क्रम driver use */
	__REQ_DRV,
	__REQ_SWAP,		/* swapping request. */
	__REQ_NR_BITS,		/* stops here */
पूर्ण;

#घोषणा REQ_FAILFAST_DEV	(1ULL << __REQ_FAILFAST_DEV)
#घोषणा REQ_FAILFAST_TRANSPORT	(1ULL << __REQ_FAILFAST_TRANSPORT)
#घोषणा REQ_FAILFAST_DRIVER	(1ULL << __REQ_FAILFAST_DRIVER)
#घोषणा REQ_SYNC		(1ULL << __REQ_SYNC)
#घोषणा REQ_META		(1ULL << __REQ_META)
#घोषणा REQ_PRIO		(1ULL << __REQ_PRIO)
#घोषणा REQ_NOMERGE		(1ULL << __REQ_NOMERGE)
#घोषणा REQ_IDLE		(1ULL << __REQ_IDLE)
#घोषणा REQ_INTEGRITY		(1ULL << __REQ_INTEGRITY)
#घोषणा REQ_FUA			(1ULL << __REQ_FUA)
#घोषणा REQ_PREFLUSH		(1ULL << __REQ_PREFLUSH)
#घोषणा REQ_RAHEAD		(1ULL << __REQ_RAHEAD)
#घोषणा REQ_BACKGROUND		(1ULL << __REQ_BACKGROUND)
#घोषणा REQ_NOWAIT		(1ULL << __REQ_NOWAIT)
#घोषणा REQ_CGROUP_PUNT		(1ULL << __REQ_CGROUP_PUNT)

#घोषणा REQ_NOUNMAP		(1ULL << __REQ_NOUNMAP)
#घोषणा REQ_HIPRI		(1ULL << __REQ_HIPRI)

#घोषणा REQ_DRV			(1ULL << __REQ_DRV)
#घोषणा REQ_SWAP		(1ULL << __REQ_SWAP)

#घोषणा REQ_FAILFAST_MASK \
	(REQ_FAILFAST_DEV | REQ_FAILFAST_TRANSPORT | REQ_FAILFAST_DRIVER)

#घोषणा REQ_NOMERGE_FLAGS \
	(REQ_NOMERGE | REQ_PREFLUSH | REQ_FUA)

क्रमागत stat_group अणु
	STAT_READ,
	STAT_WRITE,
	STAT_DISCARD,
	STAT_FLUSH,

	NR_STAT_GROUPS
पूर्ण;

#घोषणा bio_op(bio) \
	((bio)->bi_opf & REQ_OP_MASK)
#घोषणा req_op(req) \
	((req)->cmd_flags & REQ_OP_MASK)

/* obsolete, करोn't use in new code */
अटल अंतरभूत व्योम bio_set_op_attrs(काष्ठा bio *bio, अचिन्हित op,
		अचिन्हित op_flags)
अणु
	bio->bi_opf = op | op_flags;
पूर्ण

अटल अंतरभूत bool op_is_ग_लिखो(अचिन्हित पूर्णांक op)
अणु
	वापस (op & 1);
पूर्ण

/*
 * Check अगर the bio or request is one that needs special treaपंचांगent in the
 * flush state machine.
 */
अटल अंतरभूत bool op_is_flush(अचिन्हित पूर्णांक op)
अणु
	वापस op & (REQ_FUA | REQ_PREFLUSH);
पूर्ण

/*
 * Reads are always treated as synchronous, as are requests with the FUA or
 * PREFLUSH flag.  Other operations may be marked as synchronous using the
 * REQ_SYNC flag.
 */
अटल अंतरभूत bool op_is_sync(अचिन्हित पूर्णांक op)
अणु
	वापस (op & REQ_OP_MASK) == REQ_OP_READ ||
		(op & (REQ_SYNC | REQ_FUA | REQ_PREFLUSH));
पूर्ण

अटल अंतरभूत bool op_is_discard(अचिन्हित पूर्णांक op)
अणु
	वापस (op & REQ_OP_MASK) == REQ_OP_DISCARD;
पूर्ण

/*
 * Check अगर a bio or request operation is a zone management operation, with
 * the exception of REQ_OP_ZONE_RESET_ALL which is treated as a special हाल
 * due to its dअगरferent handling in the block layer and device response in
 * हाल of command failure.
 */
अटल अंतरभूत bool op_is_zone_mgmt(क्रमागत req_opf op)
अणु
	चयन (op & REQ_OP_MASK) अणु
	हाल REQ_OP_ZONE_RESET:
	हाल REQ_OP_ZONE_OPEN:
	हाल REQ_OP_ZONE_CLOSE:
	हाल REQ_OP_ZONE_FINISH:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक op_stat_group(अचिन्हित पूर्णांक op)
अणु
	अगर (op_is_discard(op))
		वापस STAT_DISCARD;
	वापस op_is_ग_लिखो(op);
पूर्ण

प्रकार अचिन्हित पूर्णांक blk_qc_t;
#घोषणा BLK_QC_T_NONE		-1U
#घोषणा BLK_QC_T_SHIFT		16
#घोषणा BLK_QC_T_INTERNAL	(1U << 31)

अटल अंतरभूत bool blk_qc_t_valid(blk_qc_t cookie)
अणु
	वापस cookie != BLK_QC_T_NONE;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_qc_t_to_queue_num(blk_qc_t cookie)
अणु
	वापस (cookie & ~BLK_QC_T_INTERNAL) >> BLK_QC_T_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक blk_qc_t_to_tag(blk_qc_t cookie)
अणु
	वापस cookie & ((1u << BLK_QC_T_SHIFT) - 1);
पूर्ण

अटल अंतरभूत bool blk_qc_t_is_पूर्णांकernal(blk_qc_t cookie)
अणु
	वापस (cookie & BLK_QC_T_INTERNAL) != 0;
पूर्ण

काष्ठा blk_rq_stat अणु
	u64 mean;
	u64 min;
	u64 max;
	u32 nr_samples;
	u64 batch;
पूर्ण;

#पूर्ण_अगर /* __LINUX_BLK_TYPES_H */
