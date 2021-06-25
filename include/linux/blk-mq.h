<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BLK_MQ_H
#घोषणा BLK_MQ_H

#समावेश <linux/blkdev.h>
#समावेश <linux/sbiपंचांगap.h>
#समावेश <linux/srcu.h>
#समावेश <linux/lockdep.h>

काष्ठा blk_mq_tags;
काष्ठा blk_flush_queue;

/**
 * काष्ठा blk_mq_hw_ctx - State क्रम a hardware queue facing the hardware
 * block device
 */
काष्ठा blk_mq_hw_ctx अणु
	काष्ठा अणु
		/** @lock: Protects the dispatch list. */
		spinlock_t		lock;
		/**
		 * @dispatch: Used क्रम requests that are पढ़ोy to be
		 * dispatched to the hardware but क्रम some reason (e.g. lack of
		 * resources) could not be sent to the hardware. As soon as the
		 * driver can send new requests, requests at this list will
		 * be sent first क्रम a fairer dispatch.
		 */
		काष्ठा list_head	dispatch;
		 /**
		  * @state: BLK_MQ_S_* flags. Defines the state of the hw
		  * queue (active, scheduled to restart, stopped).
		  */
		अचिन्हित दीर्घ		state;
	पूर्ण ____cacheline_aligned_in_smp;

	/**
	 * @run_work: Used क्रम scheduling a hardware queue run at a later समय.
	 */
	काष्ठा delayed_work	run_work;
	/** @cpumask: Map of available CPUs where this hctx can run. */
	cpumask_var_t		cpumask;
	/**
	 * @next_cpu: Used by blk_mq_hctx_next_cpu() क्रम round-robin CPU
	 * selection from @cpumask.
	 */
	पूर्णांक			next_cpu;
	/**
	 * @next_cpu_batch: Counter of how many works left in the batch beक्रमe
	 * changing to the next CPU.
	 */
	पूर्णांक			next_cpu_batch;

	/** @flags: BLK_MQ_F_* flags. Defines the behaviour of the queue. */
	अचिन्हित दीर्घ		flags;

	/**
	 * @sched_data: Poपूर्णांकer owned by the IO scheduler attached to a request
	 * queue. It's up to the IO scheduler how to use this poपूर्णांकer.
	 */
	व्योम			*sched_data;
	/**
	 * @queue: Poपूर्णांकer to the request queue that owns this hardware context.
	 */
	काष्ठा request_queue	*queue;
	/** @fq: Queue of requests that need to perक्रमm a flush operation. */
	काष्ठा blk_flush_queue	*fq;

	/**
	 * @driver_data: Poपूर्णांकer to data owned by the block driver that created
	 * this hctx
	 */
	व्योम			*driver_data;

	/**
	 * @ctx_map: Biपंचांगap क्रम each software queue. If bit is on, there is a
	 * pending request in that software queue.
	 */
	काष्ठा sbiपंचांगap		ctx_map;

	/**
	 * @dispatch_from: Software queue to be used when no scheduler was
	 * selected.
	 */
	काष्ठा blk_mq_ctx	*dispatch_from;
	/**
	 * @dispatch_busy: Number used by blk_mq_update_dispatch_busy() to
	 * decide अगर the hw_queue is busy using Exponential Weighted Moving
	 * Average algorithm.
	 */
	अचिन्हित पूर्णांक		dispatch_busy;

	/** @type: HCTX_TYPE_* flags. Type of hardware queue. */
	अचिन्हित लघु		type;
	/** @nr_ctx: Number of software queues. */
	अचिन्हित लघु		nr_ctx;
	/** @ctxs: Array of software queues. */
	काष्ठा blk_mq_ctx	**ctxs;

	/** @dispatch_रुको_lock: Lock क्रम dispatch_रुको queue. */
	spinlock_t		dispatch_रुको_lock;
	/**
	 * @dispatch_रुको: Waitqueue to put requests when there is no tag
	 * available at the moment, to रुको क्रम another try in the future.
	 */
	रुको_queue_entry_t	dispatch_रुको;

	/**
	 * @रुको_index: Index of next available dispatch_रुको queue to insert
	 * requests.
	 */
	atomic_t		रुको_index;

	/**
	 * @tags: Tags owned by the block driver. A tag at this set is only
	 * asचिन्हित when a request is dispatched from a hardware queue.
	 */
	काष्ठा blk_mq_tags	*tags;
	/**
	 * @sched_tags: Tags owned by I/O scheduler. If there is an I/O
	 * scheduler associated with a request queue, a tag is asचिन्हित when
	 * that request is allocated. Else, this member is not used.
	 */
	काष्ठा blk_mq_tags	*sched_tags;

	/** @queued: Number of queued requests. */
	अचिन्हित दीर्घ		queued;
	/** @run: Number of dispatched requests. */
	अचिन्हित दीर्घ		run;
#घोषणा BLK_MQ_MAX_DISPATCH_ORDER	7
	/** @dispatched: Number of dispatch requests by queue. */
	अचिन्हित दीर्घ		dispatched[BLK_MQ_MAX_DISPATCH_ORDER];

	/** @numa_node: NUMA node the storage adapter has been connected to. */
	अचिन्हित पूर्णांक		numa_node;
	/** @queue_num: Index of this hardware queue. */
	अचिन्हित पूर्णांक		queue_num;

	/**
	 * @nr_active: Number of active requests. Only used when a tag set is
	 * shared across request queues.
	 */
	atomic_t		nr_active;

	/** @cpuhp_online: List to store request अगर CPU is going to die */
	काष्ठा hlist_node	cpuhp_online;
	/** @cpuhp_dead: List to store request अगर some CPU die. */
	काष्ठा hlist_node	cpuhp_dead;
	/** @kobj: Kernel object क्रम sysfs. */
	काष्ठा kobject		kobj;

	/** @poll_considered: Count बार blk_poll() was called. */
	अचिन्हित दीर्घ		poll_considered;
	/** @poll_invoked: Count how many requests blk_poll() polled. */
	अचिन्हित दीर्घ		poll_invoked;
	/** @poll_success: Count how many polled requests were completed. */
	अचिन्हित दीर्घ		poll_success;

#अगर_घोषित CONFIG_BLK_DEBUG_FS
	/**
	 * @debugfs_dir: debugfs directory क्रम this hardware queue. Named
	 * as cpu<cpu_number>.
	 */
	काष्ठा dentry		*debugfs_dir;
	/** @sched_debugfs_dir:	debugfs directory क्रम the scheduler. */
	काष्ठा dentry		*sched_debugfs_dir;
#पूर्ण_अगर

	/**
	 * @hctx_list: अगर this hctx is not in use, this is an entry in
	 * q->unused_hctx_list.
	 */
	काष्ठा list_head	hctx_list;

	/**
	 * @srcu: Sleepable RCU. Use as lock when type of the hardware queue is
	 * blocking (BLK_MQ_F_BLOCKING). Must be the last member - see also
	 * blk_mq_hw_ctx_size().
	 */
	काष्ठा srcu_काष्ठा	srcu[];
पूर्ण;

/**
 * काष्ठा blk_mq_queue_map - Map software queues to hardware queues
 * @mq_map:       CPU ID to hardware queue index map. This is an array
 *	with nr_cpu_ids elements. Each element has a value in the range
 *	[@queue_offset, @queue_offset + @nr_queues).
 * @nr_queues:    Number of hardware queues to map CPU IDs onto.
 * @queue_offset: First hardware queue to map onto. Used by the PCIe NVMe
 *	driver to map each hardware queue type (क्रमागत hctx_type) onto a distinct
 *	set of hardware queues.
 */
काष्ठा blk_mq_queue_map अणु
	अचिन्हित पूर्णांक *mq_map;
	अचिन्हित पूर्णांक nr_queues;
	अचिन्हित पूर्णांक queue_offset;
पूर्ण;

/**
 * क्रमागत hctx_type - Type of hardware queue
 * @HCTX_TYPE_DEFAULT:	All I/O not otherwise accounted क्रम.
 * @HCTX_TYPE_READ:	Just क्रम READ I/O.
 * @HCTX_TYPE_POLL:	Polled I/O of any kind.
 * @HCTX_MAX_TYPES:	Number of types of hctx.
 */
क्रमागत hctx_type अणु
	HCTX_TYPE_DEFAULT,
	HCTX_TYPE_READ,
	HCTX_TYPE_POLL,

	HCTX_MAX_TYPES,
पूर्ण;

/**
 * काष्ठा blk_mq_tag_set - tag set that can be shared between request queues
 * @map:	   One or more ctx -> hctx mappings. One map exists क्रम each
 *		   hardware queue type (क्रमागत hctx_type) that the driver wishes
 *		   to support. There are no restrictions on maps being of the
 *		   same size, and it's perfectly legal to share maps between
 *		   types.
 * @nr_maps:	   Number of elements in the @map array. A number in the range
 *		   [1, HCTX_MAX_TYPES].
 * @ops:	   Poपूर्णांकers to functions that implement block driver behavior.
 * @nr_hw_queues:  Number of hardware queues supported by the block driver that
 *		   owns this data काष्ठाure.
 * @queue_depth:   Number of tags per hardware queue, reserved tags included.
 * @reserved_tags: Number of tags to set aside क्रम BLK_MQ_REQ_RESERVED tag
 *		   allocations.
 * @cmd_size:	   Number of additional bytes to allocate per request. The block
 *		   driver owns these additional bytes.
 * @numa_node:	   NUMA node the storage adapter has been connected to.
 * @समयout:	   Request processing समयout in jअगरfies.
 * @flags:	   Zero or more BLK_MQ_F_* flags.
 * @driver_data:   Poपूर्णांकer to data owned by the block driver that created this
 *		   tag set.
 * @active_queues_shared_sbiपंचांगap:
 * 		   number of active request queues per tag set.
 * @__biपंचांगap_tags: A shared tags sbiपंचांगap, used over all hctx's
 * @__breserved_tags:
 *		   A shared reserved tags sbiपंचांगap, used over all hctx's
 * @tags:	   Tag sets. One tag set per hardware queue. Has @nr_hw_queues
 *		   elements.
 * @tag_list_lock: Serializes tag_list accesses.
 * @tag_list:	   List of the request queues that use this tag set. See also
 *		   request_queue.tag_set_list.
 */
काष्ठा blk_mq_tag_set अणु
	काष्ठा blk_mq_queue_map	map[HCTX_MAX_TYPES];
	अचिन्हित पूर्णांक		nr_maps;
	स्थिर काष्ठा blk_mq_ops	*ops;
	अचिन्हित पूर्णांक		nr_hw_queues;
	अचिन्हित पूर्णांक		queue_depth;
	अचिन्हित पूर्णांक		reserved_tags;
	अचिन्हित पूर्णांक		cmd_size;
	पूर्णांक			numa_node;
	अचिन्हित पूर्णांक		समयout;
	अचिन्हित पूर्णांक		flags;
	व्योम			*driver_data;
	atomic_t		active_queues_shared_sbiपंचांगap;

	काष्ठा sbiपंचांगap_queue	__biपंचांगap_tags;
	काष्ठा sbiपंचांगap_queue	__breserved_tags;
	काष्ठा blk_mq_tags	**tags;

	काष्ठा mutex		tag_list_lock;
	काष्ठा list_head	tag_list;
पूर्ण;

/**
 * काष्ठा blk_mq_queue_data - Data about a request inserted in a queue
 *
 * @rq:   Request poपूर्णांकer.
 * @last: If it is the last request in the queue.
 */
काष्ठा blk_mq_queue_data अणु
	काष्ठा request *rq;
	bool last;
पूर्ण;

प्रकार bool (busy_iter_fn)(काष्ठा blk_mq_hw_ctx *, काष्ठा request *, व्योम *,
		bool);
प्रकार bool (busy_tag_iter_fn)(काष्ठा request *, व्योम *, bool);

/**
 * काष्ठा blk_mq_ops - Callback functions that implements block driver
 * behaviour.
 */
काष्ठा blk_mq_ops अणु
	/**
	 * @queue_rq: Queue a new request from block IO.
	 */
	blk_status_t (*queue_rq)(काष्ठा blk_mq_hw_ctx *,
				 स्थिर काष्ठा blk_mq_queue_data *);

	/**
	 * @commit_rqs: If a driver uses bd->last to judge when to submit
	 * requests to hardware, it must define this function. In हाल of errors
	 * that make us stop issuing further requests, this hook serves the
	 * purpose of kicking the hardware (which the last request otherwise
	 * would have करोne).
	 */
	व्योम (*commit_rqs)(काष्ठा blk_mq_hw_ctx *);

	/**
	 * @get_budget: Reserve budget beक्रमe queue request, once .queue_rq is
	 * run, it is driver's responsibility to release the
	 * reserved budget. Also we have to handle failure हाल
	 * of .get_budget क्रम aव्योमing I/O deadlock.
	 */
	पूर्णांक (*get_budget)(काष्ठा request_queue *);

	/**
	 * @put_budget: Release the reserved budget.
	 */
	व्योम (*put_budget)(काष्ठा request_queue *, पूर्णांक);

	/**
	 * @set_rq_budget_token: store rq's budget token
	 */
	व्योम (*set_rq_budget_token)(काष्ठा request *, पूर्णांक);
	/**
	 * @get_rq_budget_token: retrieve rq's budget token
	 */
	पूर्णांक (*get_rq_budget_token)(काष्ठा request *);

	/**
	 * @समयout: Called on request समयout.
	 */
	क्रमागत blk_eh_समयr_वापस (*समयout)(काष्ठा request *, bool);

	/**
	 * @poll: Called to poll क्रम completion of a specअगरic tag.
	 */
	पूर्णांक (*poll)(काष्ठा blk_mq_hw_ctx *);

	/**
	 * @complete: Mark the request as complete.
	 */
	व्योम (*complete)(काष्ठा request *);

	/**
	 * @init_hctx: Called when the block layer side of a hardware queue has
	 * been set up, allowing the driver to allocate/init matching
	 * काष्ठाures.
	 */
	पूर्णांक (*init_hctx)(काष्ठा blk_mq_hw_ctx *, व्योम *, अचिन्हित पूर्णांक);
	/**
	 * @निकास_hctx: Ditto क्रम निकास/tearकरोwn.
	 */
	व्योम (*निकास_hctx)(काष्ठा blk_mq_hw_ctx *, अचिन्हित पूर्णांक);

	/**
	 * @init_request: Called क्रम every command allocated by the block layer
	 * to allow the driver to set up driver specअगरic data.
	 *
	 * Tag greater than or equal to queue_depth is क्रम setting up
	 * flush request.
	 */
	पूर्णांक (*init_request)(काष्ठा blk_mq_tag_set *set, काष्ठा request *,
			    अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
	/**
	 * @निकास_request: Ditto क्रम निकास/tearकरोwn.
	 */
	व्योम (*निकास_request)(काष्ठा blk_mq_tag_set *set, काष्ठा request *,
			     अचिन्हित पूर्णांक);

	/**
	 * @initialize_rq_fn: Called from inside blk_get_request().
	 */
	व्योम (*initialize_rq_fn)(काष्ठा request *rq);

	/**
	 * @cleanup_rq: Called beक्रमe मुक्तing one request which isn't completed
	 * yet, and usually क्रम मुक्तing the driver निजी data.
	 */
	व्योम (*cleanup_rq)(काष्ठा request *);

	/**
	 * @busy: If set, वापसs whether or not this queue currently is busy.
	 */
	bool (*busy)(काष्ठा request_queue *);

	/**
	 * @map_queues: This allows drivers specअगरy their own queue mapping by
	 * overriding the setup-समय function that builds the mq_map.
	 */
	पूर्णांक (*map_queues)(काष्ठा blk_mq_tag_set *set);

#अगर_घोषित CONFIG_BLK_DEBUG_FS
	/**
	 * @show_rq: Used by the debugfs implementation to show driver-specअगरic
	 * inक्रमmation about a request.
	 */
	व्योम (*show_rq)(काष्ठा seq_file *m, काष्ठा request *rq);
#पूर्ण_अगर
पूर्ण;

क्रमागत अणु
	BLK_MQ_F_SHOULD_MERGE	= 1 << 0,
	BLK_MQ_F_TAG_QUEUE_SHARED = 1 << 1,
	/*
	 * Set when this device requires underlying blk-mq device क्रम
	 * completing IO:
	 */
	BLK_MQ_F_STACKING	= 1 << 2,
	BLK_MQ_F_TAG_HCTX_SHARED = 1 << 3,
	BLK_MQ_F_BLOCKING	= 1 << 5,
	BLK_MQ_F_NO_SCHED	= 1 << 6,
	BLK_MQ_F_ALLOC_POLICY_START_BIT = 8,
	BLK_MQ_F_ALLOC_POLICY_BITS = 1,

	BLK_MQ_S_STOPPED	= 0,
	BLK_MQ_S_TAG_ACTIVE	= 1,
	BLK_MQ_S_SCHED_RESTART	= 2,

	/* hw queue is inactive after all its CPUs become offline */
	BLK_MQ_S_INACTIVE	= 3,

	BLK_MQ_MAX_DEPTH	= 10240,

	BLK_MQ_CPU_WORK_BATCH	= 8,
पूर्ण;
#घोषणा BLK_MQ_FLAG_TO_ALLOC_POLICY(flags) \
	((flags >> BLK_MQ_F_ALLOC_POLICY_START_BIT) & \
		((1 << BLK_MQ_F_ALLOC_POLICY_BITS) - 1))
#घोषणा BLK_ALLOC_POLICY_TO_MQ_FLAG(policy) \
	((policy & ((1 << BLK_MQ_F_ALLOC_POLICY_BITS) - 1)) \
		<< BLK_MQ_F_ALLOC_POLICY_START_BIT)

काष्ठा request_queue *blk_mq_init_queue(काष्ठा blk_mq_tag_set *);
काष्ठा request_queue *blk_mq_init_queue_data(काष्ठा blk_mq_tag_set *set,
		व्योम *queuedata);
काष्ठा request_queue *blk_mq_init_allocated_queue(काष्ठा blk_mq_tag_set *set,
						  काष्ठा request_queue *q,
						  bool elevator_init);
काष्ठा request_queue *blk_mq_init_sq_queue(काष्ठा blk_mq_tag_set *set,
						स्थिर काष्ठा blk_mq_ops *ops,
						अचिन्हित पूर्णांक queue_depth,
						अचिन्हित पूर्णांक set_flags);
व्योम blk_mq_unरेजिस्टर_dev(काष्ठा device *, काष्ठा request_queue *);

पूर्णांक blk_mq_alloc_tag_set(काष्ठा blk_mq_tag_set *set);
व्योम blk_mq_मुक्त_tag_set(काष्ठा blk_mq_tag_set *set);

व्योम blk_mq_flush_plug_list(काष्ठा blk_plug *plug, bool from_schedule);

व्योम blk_mq_मुक्त_request(काष्ठा request *rq);

bool blk_mq_queue_inflight(काष्ठा request_queue *q);

क्रमागत अणु
	/* वापस when out of requests */
	BLK_MQ_REQ_NOWAIT	= (__क्रमce blk_mq_req_flags_t)(1 << 0),
	/* allocate from reserved pool */
	BLK_MQ_REQ_RESERVED	= (__क्रमce blk_mq_req_flags_t)(1 << 1),
	/* set RQF_PM */
	BLK_MQ_REQ_PM		= (__क्रमce blk_mq_req_flags_t)(1 << 2),
पूर्ण;

काष्ठा request *blk_mq_alloc_request(काष्ठा request_queue *q, अचिन्हित पूर्णांक op,
		blk_mq_req_flags_t flags);
काष्ठा request *blk_mq_alloc_request_hctx(काष्ठा request_queue *q,
		अचिन्हित पूर्णांक op, blk_mq_req_flags_t flags,
		अचिन्हित पूर्णांक hctx_idx);
काष्ठा request *blk_mq_tag_to_rq(काष्ठा blk_mq_tags *tags, अचिन्हित पूर्णांक tag);

क्रमागत अणु
	BLK_MQ_UNIQUE_TAG_BITS = 16,
	BLK_MQ_UNIQUE_TAG_MASK = (1 << BLK_MQ_UNIQUE_TAG_BITS) - 1,
पूर्ण;

u32 blk_mq_unique_tag(काष्ठा request *rq);

अटल अंतरभूत u16 blk_mq_unique_tag_to_hwq(u32 unique_tag)
अणु
	वापस unique_tag >> BLK_MQ_UNIQUE_TAG_BITS;
पूर्ण

अटल अंतरभूत u16 blk_mq_unique_tag_to_tag(u32 unique_tag)
अणु
	वापस unique_tag & BLK_MQ_UNIQUE_TAG_MASK;
पूर्ण

/**
 * blk_mq_rq_state() - पढ़ो the current MQ_RQ_* state of a request
 * @rq: target request.
 */
अटल अंतरभूत क्रमागत mq_rq_state blk_mq_rq_state(काष्ठा request *rq)
अणु
	वापस READ_ONCE(rq->state);
पूर्ण

अटल अंतरभूत पूर्णांक blk_mq_request_started(काष्ठा request *rq)
अणु
	वापस blk_mq_rq_state(rq) != MQ_RQ_IDLE;
पूर्ण

अटल अंतरभूत पूर्णांक blk_mq_request_completed(काष्ठा request *rq)
अणु
	वापस blk_mq_rq_state(rq) == MQ_RQ_COMPLETE;
पूर्ण

/*
 * 
 * Set the state to complete when completing a request from inside ->queue_rq.
 * This is used by drivers that want to ensure special complete actions that
 * need access to the request are called on failure, e.g. by nvme क्रम
 * multipathing.
 */
अटल अंतरभूत व्योम blk_mq_set_request_complete(काष्ठा request *rq)
अणु
	WRITE_ONCE(rq->state, MQ_RQ_COMPLETE);
पूर्ण

व्योम blk_mq_start_request(काष्ठा request *rq);
व्योम blk_mq_end_request(काष्ठा request *rq, blk_status_t error);
व्योम __blk_mq_end_request(काष्ठा request *rq, blk_status_t error);

व्योम blk_mq_requeue_request(काष्ठा request *rq, bool kick_requeue_list);
व्योम blk_mq_kick_requeue_list(काष्ठा request_queue *q);
व्योम blk_mq_delay_kick_requeue_list(काष्ठा request_queue *q, अचिन्हित दीर्घ msecs);
व्योम blk_mq_complete_request(काष्ठा request *rq);
bool blk_mq_complete_request_remote(काष्ठा request *rq);
bool blk_mq_queue_stopped(काष्ठा request_queue *q);
व्योम blk_mq_stop_hw_queue(काष्ठा blk_mq_hw_ctx *hctx);
व्योम blk_mq_start_hw_queue(काष्ठा blk_mq_hw_ctx *hctx);
व्योम blk_mq_stop_hw_queues(काष्ठा request_queue *q);
व्योम blk_mq_start_hw_queues(काष्ठा request_queue *q);
व्योम blk_mq_start_stopped_hw_queue(काष्ठा blk_mq_hw_ctx *hctx, bool async);
व्योम blk_mq_start_stopped_hw_queues(काष्ठा request_queue *q, bool async);
व्योम blk_mq_quiesce_queue(काष्ठा request_queue *q);
व्योम blk_mq_unquiesce_queue(काष्ठा request_queue *q);
व्योम blk_mq_delay_run_hw_queue(काष्ठा blk_mq_hw_ctx *hctx, अचिन्हित दीर्घ msecs);
व्योम blk_mq_run_hw_queue(काष्ठा blk_mq_hw_ctx *hctx, bool async);
व्योम blk_mq_run_hw_queues(काष्ठा request_queue *q, bool async);
व्योम blk_mq_delay_run_hw_queues(काष्ठा request_queue *q, अचिन्हित दीर्घ msecs);
व्योम blk_mq_tagset_busy_iter(काष्ठा blk_mq_tag_set *tagset,
		busy_tag_iter_fn *fn, व्योम *priv);
व्योम blk_mq_tagset_रुको_completed_request(काष्ठा blk_mq_tag_set *tagset);
व्योम blk_mq_मुक्तze_queue(काष्ठा request_queue *q);
व्योम blk_mq_unमुक्तze_queue(काष्ठा request_queue *q);
व्योम blk_मुक्तze_queue_start(काष्ठा request_queue *q);
व्योम blk_mq_मुक्तze_queue_रुको(काष्ठा request_queue *q);
पूर्णांक blk_mq_मुक्तze_queue_रुको_समयout(काष्ठा request_queue *q,
				     अचिन्हित दीर्घ समयout);

पूर्णांक blk_mq_map_queues(काष्ठा blk_mq_queue_map *qmap);
व्योम blk_mq_update_nr_hw_queues(काष्ठा blk_mq_tag_set *set, पूर्णांक nr_hw_queues);

व्योम blk_mq_quiesce_queue_noरुको(काष्ठा request_queue *q);

अचिन्हित पूर्णांक blk_mq_rq_cpu(काष्ठा request *rq);

bool __blk_should_fake_समयout(काष्ठा request_queue *q);
अटल अंतरभूत bool blk_should_fake_समयout(काष्ठा request_queue *q)
अणु
	अगर (IS_ENABLED(CONFIG_FAIL_IO_TIMEOUT) &&
	    test_bit(QUEUE_FLAG_FAIL_IO, &q->queue_flags))
		वापस __blk_should_fake_समयout(q);
	वापस false;
पूर्ण

/**
 * blk_mq_rq_from_pdu - cast a PDU to a request
 * @pdu: the PDU (Protocol Data Unit) to be casted
 *
 * Return: request
 *
 * Driver command data is immediately after the request. So subtract request
 * size to get back to the original request.
 */
अटल अंतरभूत काष्ठा request *blk_mq_rq_from_pdu(व्योम *pdu)
अणु
	वापस pdu - माप(काष्ठा request);
पूर्ण

/**
 * blk_mq_rq_to_pdu - cast a request to a PDU
 * @rq: the request to be casted
 *
 * Return: poपूर्णांकer to the PDU
 *
 * Driver command data is immediately after the request. So add request to get
 * the PDU.
 */
अटल अंतरभूत व्योम *blk_mq_rq_to_pdu(काष्ठा request *rq)
अणु
	वापस rq + 1;
पूर्ण

#घोषणा queue_क्रम_each_hw_ctx(q, hctx, i)				\
	क्रम ((i) = 0; (i) < (q)->nr_hw_queues &&			\
	     (अणु hctx = (q)->queue_hw_ctx[i]; 1; पूर्ण); (i)++)

#घोषणा hctx_क्रम_each_ctx(hctx, ctx, i)					\
	क्रम ((i) = 0; (i) < (hctx)->nr_ctx &&				\
	     (अणु ctx = (hctx)->ctxs[(i)]; 1; पूर्ण); (i)++)

अटल अंतरभूत blk_qc_t request_to_qc_t(काष्ठा blk_mq_hw_ctx *hctx,
		काष्ठा request *rq)
अणु
	अगर (rq->tag != -1)
		वापस rq->tag | (hctx->queue_num << BLK_QC_T_SHIFT);

	वापस rq->पूर्णांकernal_tag | (hctx->queue_num << BLK_QC_T_SHIFT) |
			BLK_QC_T_INTERNAL;
पूर्ण

अटल अंतरभूत व्योम blk_mq_cleanup_rq(काष्ठा request *rq)
अणु
	अगर (rq->q->mq_ops->cleanup_rq)
		rq->q->mq_ops->cleanup_rq(rq);
पूर्ण

अटल अंतरभूत व्योम blk_rq_bio_prep(काष्ठा request *rq, काष्ठा bio *bio,
		अचिन्हित पूर्णांक nr_segs)
अणु
	rq->nr_phys_segments = nr_segs;
	rq->__data_len = bio->bi_iter.bi_size;
	rq->bio = rq->biotail = bio;
	rq->ioprio = bio_prio(bio);

	अगर (bio->bi_bdev)
		rq->rq_disk = bio->bi_bdev->bd_disk;
पूर्ण

blk_qc_t blk_mq_submit_bio(काष्ठा bio *bio);
व्योम blk_mq_hctx_set_fq_lock_class(काष्ठा blk_mq_hw_ctx *hctx,
		काष्ठा lock_class_key *key);

#पूर्ण_अगर
