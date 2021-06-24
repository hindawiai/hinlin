<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Header file क्रम the BFQ I/O scheduler: data काष्ठाures and
 * prototypes of पूर्णांकerface functions among BFQ components.
 */
#अगर_अघोषित _BFQ_H
#घोषणा _BFQ_H

#समावेश <linux/blktrace_api.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/blk-cgroup.h>

#समावेश "blk-cgroup-rwstat.h"

#घोषणा BFQ_IOPRIO_CLASSES	3
#घोषणा BFQ_CL_IDLE_TIMEOUT	(HZ/5)

#घोषणा BFQ_MIN_WEIGHT			1
#घोषणा BFQ_MAX_WEIGHT			1000
#घोषणा BFQ_WEIGHT_CONVERSION_COEFF	10

#घोषणा BFQ_DEFAULT_QUEUE_IOPRIO	4

#घोषणा BFQ_WEIGHT_LEGACY_DFL	100
#घोषणा BFQ_DEFAULT_GRP_IOPRIO	0
#घोषणा BFQ_DEFAULT_GRP_CLASS	IOPRIO_CLASS_BE

#घोषणा MAX_PID_STR_LENGTH 12

/*
 * Soft real-समय applications are extremely more latency sensitive
 * than पूर्णांकeractive ones. Over-उठाओ the weight of the क्रमmer to
 * privilege them against the latter.
 */
#घोषणा BFQ_SOFTRT_WEIGHT_FACTOR	100

काष्ठा bfq_entity;

/**
 * काष्ठा bfq_service_tree - per ioprio_class service tree.
 *
 * Each service tree represents a B-WF2Q+ scheduler on its own.  Each
 * ioprio_class has its own independent scheduler, and so its own
 * bfq_service_tree.  All the fields are रक्षित by the queue lock
 * of the containing bfqd.
 */
काष्ठा bfq_service_tree अणु
	/* tree क्रम active entities (i.e., those backlogged) */
	काष्ठा rb_root active;
	/* tree क्रम idle entities (i.e., not backlogged, with V < F_i)*/
	काष्ठा rb_root idle;

	/* idle entity with minimum F_i */
	काष्ठा bfq_entity *first_idle;
	/* idle entity with maximum F_i */
	काष्ठा bfq_entity *last_idle;

	/* scheduler भव समय */
	u64 vसमय;
	/* scheduler weight sum; active and idle entities contribute to it */
	अचिन्हित दीर्घ wsum;
पूर्ण;

/**
 * काष्ठा bfq_sched_data - multi-class scheduler.
 *
 * bfq_sched_data is the basic scheduler queue.  It supports three
 * ioprio_classes, and can be used either as a toplevel queue or as an
 * पूर्णांकermediate queue in a hierarchical setup.
 *
 * The supported ioprio_classes are the same as in CFQ, in descending
 * priority order, IOPRIO_CLASS_RT, IOPRIO_CLASS_BE, IOPRIO_CLASS_IDLE.
 * Requests from higher priority queues are served beक्रमe all the
 * requests from lower priority queues; among requests of the same
 * queue requests are served according to B-WF2Q+.
 *
 * The schedule is implemented by the service trees, plus the field
 * @next_in_service, which poपूर्णांकs to the entity on the active trees
 * that will be served next, अगर 1) no changes in the schedule occurs
 * beक्रमe the current in-service entity is expired, 2) the in-service
 * queue becomes idle when it expires, and 3) अगर the entity poपूर्णांकed by
 * in_service_entity is not a queue, then the in-service child entity
 * of the entity poपूर्णांकed by in_service_entity becomes idle on
 * expiration. This peculiar definition allows क्रम the following
 * optimization, not yet exploited: जबतक a given entity is still in
 * service, we alपढ़ोy know which is the best candidate क्रम next
 * service among the other active entities in the same parent
 * entity. We can then quickly compare the बारtamps of the
 * in-service entity with those of such best candidate.
 *
 * All fields are रक्षित by the lock of the containing bfqd.
 */
काष्ठा bfq_sched_data अणु
	/* entity in service */
	काष्ठा bfq_entity *in_service_entity;
	/* head-of-line entity (see comments above) */
	काष्ठा bfq_entity *next_in_service;
	/* array of service trees, one per ioprio_class */
	काष्ठा bfq_service_tree service_tree[BFQ_IOPRIO_CLASSES];
	/* last समय CLASS_IDLE was served */
	अचिन्हित दीर्घ bfq_class_idle_last_service;

पूर्ण;

/**
 * काष्ठा bfq_weight_counter - counter of the number of all active queues
 *                             with a given weight.
 */
काष्ठा bfq_weight_counter अणु
	अचिन्हित पूर्णांक weight; /* weight of the queues this counter refers to */
	अचिन्हित पूर्णांक num_active; /* nr of active queues with this weight */
	/*
	 * Weights tree member (see bfq_data's @queue_weights_tree)
	 */
	काष्ठा rb_node weights_node;
पूर्ण;

/**
 * काष्ठा bfq_entity - schedulable entity.
 *
 * A bfq_entity is used to represent either a bfq_queue (leaf node in the
 * cgroup hierarchy) or a bfq_group पूर्णांकo the upper level scheduler.  Each
 * entity beदीर्घs to the sched_data of the parent group in the cgroup
 * hierarchy.  Non-leaf entities have also their own sched_data, stored
 * in @my_sched_data.
 *
 * Each entity stores independently its priority values; this would
 * allow dअगरferent weights on dअगरferent devices, but this
 * functionality is not exported to userspace by now.  Priorities and
 * weights are updated lazily, first storing the new values पूर्णांकo the
 * new_* fields, then setting the @prio_changed flag.  As soon as
 * there is a transition in the entity state that allows the priority
 * update to take place the effective and the requested priority
 * values are synchronized.
 *
 * Unless cgroups are used, the weight value is calculated from the
 * ioprio to export the same पूर्णांकerface as CFQ.  When dealing with
 * "well-behaved" queues (i.e., queues that करो not spend too much
 * समय to consume their budget and have true sequential behavior, and
 * when there are no बाह्यal factors अवरोधing anticipation) the
 * relative weights at each level of the cgroups hierarchy should be
 * guaranteed.  All the fields are रक्षित by the queue lock of the
 * containing bfqd.
 */
काष्ठा bfq_entity अणु
	/* service_tree member */
	काष्ठा rb_node rb_node;

	/*
	 * Flag, true अगर the entity is on a tree (either the active or
	 * the idle one of its service_tree) or is in service.
	 */
	bool on_st_or_in_serv;

	/* B-WF2Q+ start and finish बारtamps [sectors/weight] */
	u64 start, finish;

	/* tree the entity is enqueued पूर्णांकo; %शून्य अगर not on a tree */
	काष्ठा rb_root *tree;

	/*
	 * minimum start समय of the (active) subtree rooted at this
	 * entity; used क्रम O(log N) lookups पूर्णांकo active trees
	 */
	u64 min_start;

	/* amount of service received during the last service slot */
	पूर्णांक service;

	/* budget, used also to calculate F_i: F_i = S_i + @budget / @weight */
	पूर्णांक budget;

	/* device weight, अगर non-zero, it overrides the शेष weight of
	 * bfq_group_data */
	पूर्णांक dev_weight;
	/* weight of the queue */
	पूर्णांक weight;
	/* next weight अगर a change is in progress */
	पूर्णांक new_weight;

	/* original weight, used to implement weight boosting */
	पूर्णांक orig_weight;

	/* parent entity, क्रम hierarchical scheduling */
	काष्ठा bfq_entity *parent;

	/*
	 * For non-leaf nodes in the hierarchy, the associated
	 * scheduler queue, %शून्य on leaf nodes.
	 */
	काष्ठा bfq_sched_data *my_sched_data;
	/* the scheduler queue this entity beदीर्घs to */
	काष्ठा bfq_sched_data *sched_data;

	/* flag, set to request a weight, ioprio or ioprio_class change  */
	पूर्णांक prio_changed;

	/* flag, set अगर the entity is counted in groups_with_pending_reqs */
	bool in_groups_with_pending_reqs;

	/* last child queue of entity created (क्रम non-leaf entities) */
	काष्ठा bfq_queue *last_bfqq_created;
पूर्ण;

काष्ठा bfq_group;

/**
 * काष्ठा bfq_tसमय - per process thinkसमय stats.
 */
काष्ठा bfq_tसमय अणु
	/* completion समय of the last request */
	u64 last_end_request;

	/* total process thinkसमय */
	u64 tसमय_प्रकारotal;
	/* number of thinkसमय samples */
	अचिन्हित दीर्घ tसमय_samples;
	/* average process thinkसमय */
	u64 tसमय_mean;
पूर्ण;

/**
 * काष्ठा bfq_queue - leaf schedulable entity.
 *
 * A bfq_queue is a leaf request queue; it can be associated with an
 * io_context or more, अगर it  is  async or shared  between  cooperating
 * processes. @cgroup holds a reference to the cgroup, to be sure that it
 * करोes not disappear जबतक a bfqq still references it (mostly to aव्योम
 * races between request issuing and task migration followed by cgroup
 * deकाष्ठाion).
 * All the fields are रक्षित by the queue lock of the containing bfqd.
 */
काष्ठा bfq_queue अणु
	/* reference counter */
	पूर्णांक ref;
	/* counter of references from other queues क्रम delayed stable merge */
	पूर्णांक stable_ref;
	/* parent bfq_data */
	काष्ठा bfq_data *bfqd;

	/* current ioprio and ioprio class */
	अचिन्हित लघु ioprio, ioprio_class;
	/* next ioprio and ioprio class अगर a change is in progress */
	अचिन्हित लघु new_ioprio, new_ioprio_class;

	/* last total-service-समय sample, see bfq_update_inject_limit() */
	u64 last_serv_समय_ns;
	/* limit क्रम request injection */
	अचिन्हित पूर्णांक inject_limit;
	/* last समय the inject limit has been decreased, in jअगरfies */
	अचिन्हित दीर्घ decrease_समय_jअगर;

	/*
	 * Shared bfq_queue अगर queue is cooperating with one or more
	 * other queues.
	 */
	काष्ठा bfq_queue *new_bfqq;
	/* request-position tree member (see bfq_group's @rq_pos_tree) */
	काष्ठा rb_node pos_node;
	/* request-position tree root (see bfq_group's @rq_pos_tree) */
	काष्ठा rb_root *pos_root;

	/* sorted list of pending requests */
	काष्ठा rb_root sort_list;
	/* अगर fअगरo isn't expired, next request to serve */
	काष्ठा request *next_rq;
	/* number of sync and async requests queued */
	पूर्णांक queued[2];
	/* number of requests currently allocated */
	पूर्णांक allocated;
	/* number of pending metadata requests */
	पूर्णांक meta_pending;
	/* fअगरo list of requests in sort_list */
	काष्ठा list_head fअगरo;

	/* entity representing this queue in the scheduler */
	काष्ठा bfq_entity entity;

	/* poपूर्णांकer to the weight counter associated with this entity */
	काष्ठा bfq_weight_counter *weight_counter;

	/* maximum budget allowed from the feedback mechanism */
	पूर्णांक max_budget;
	/* budget expiration (in jअगरfies) */
	अचिन्हित दीर्घ budget_समयout;

	/* number of requests on the dispatch list or inside driver */
	पूर्णांक dispatched;

	/* status flags */
	अचिन्हित दीर्घ flags;

	/* node क्रम active/idle bfqq list inside parent bfqd */
	काष्ठा list_head bfqq_list;

	/* associated @bfq_tसमय काष्ठा */
	काष्ठा bfq_tसमय tसमय;

	/* when bfqq started to करो I/O within the last observation winकरोw */
	u64 io_start_समय;
	/* how दीर्घ bfqq has reमुख्यed empty during the last observ. winकरोw */
	u64 tot_idle_समय;

	/* bit vector: a 1 क्रम each seeky requests in history */
	u32 seek_history;

	/* node क्रम the device's burst list */
	काष्ठा hlist_node burst_list_node;

	/* position of the last request enqueued */
	sector_t last_request_pos;

	/* Number of consecutive pairs of request completion and
	 * arrival, such that the queue becomes idle after the
	 * completion, but the next request arrives within an idle
	 * समय slice; used only अगर the queue's IO_bound flag has been
	 * cleared.
	 */
	अचिन्हित पूर्णांक requests_within_समयr;

	/* pid of the process owning the queue, used क्रम logging purposes */
	pid_t pid;

	/*
	 * Poपूर्णांकer to the bfq_io_cq owning the bfq_queue, set to %शून्य
	 * अगर the queue is shared.
	 */
	काष्ठा bfq_io_cq *bic;

	/* current maximum weight-raising समय क्रम this queue */
	अचिन्हित दीर्घ wr_cur_max_समय;
	/*
	 * Minimum समय instant such that, only अगर a new request is
	 * enqueued after this समय instant in an idle @bfq_queue with
	 * no outstanding requests, then the task associated with the
	 * queue it is deemed as soft real-समय (see the comments on
	 * the function bfq_bfqq_softrt_next_start())
	 */
	अचिन्हित दीर्घ soft_rt_next_start;
	/*
	 * Start समय of the current weight-raising period अगर
	 * the @bfq-queue is being weight-उठाओd, otherwise
	 * finish समय of the last weight-raising period.
	 */
	अचिन्हित दीर्घ last_wr_start_finish;
	/* factor by which the weight of this queue is multiplied */
	अचिन्हित पूर्णांक wr_coeff;
	/*
	 * Time of the last transition of the @bfq_queue from idle to
	 * backlogged.
	 */
	अचिन्हित दीर्घ last_idle_bklogged;
	/*
	 * Cumulative service received from the @bfq_queue since the
	 * last transition from idle to backlogged.
	 */
	अचिन्हित दीर्घ service_from_backlogged;
	/*
	 * Cumulative service received from the @bfq_queue since its
	 * last transition to weight-उठाओd state.
	 */
	अचिन्हित दीर्घ service_from_wr;

	/*
	 * Value of wr start समय when चयनing to soft rt
	 */
	अचिन्हित दीर्घ wr_start_at_चयन_to_srt;

	अचिन्हित दीर्घ split_समय; /* समय of last split */

	अचिन्हित दीर्घ first_IO_समय; /* समय of first I/O क्रम this queue */

	अचिन्हित दीर्घ creation_समय; /* when this queue is created */

	/* max service rate measured so far */
	u32 max_service_rate;

	/*
	 * Poपूर्णांकer to the waker queue क्रम this queue, i.e., to the
	 * queue Q such that this queue happens to get new I/O right
	 * after some I/O request of Q is completed. For details, see
	 * the comments on the choice of the queue क्रम injection in
	 * bfq_select_queue().
	 */
	काष्ठा bfq_queue *waker_bfqq;
	/* poपूर्णांकer to the curr. tentative waker queue, see bfq_check_waker() */
	काष्ठा bfq_queue *tentative_waker_bfqq;
	/* number of बार the same tentative waker has been detected */
	अचिन्हित पूर्णांक num_waker_detections;

	/* node क्रम woken_list, see below */
	काष्ठा hlist_node woken_list_node;
	/*
	 * Head of the list of the woken queues क्रम this queue, i.e.,
	 * of the list of the queues क्रम which this queue is a waker
	 * queue. This list is used to reset the waker_bfqq poपूर्णांकer in
	 * the woken queues when this queue निकासs.
	 */
	काष्ठा hlist_head woken_list;
पूर्ण;

/**
 * काष्ठा bfq_io_cq - per (request_queue, io_context) काष्ठाure.
 */
काष्ठा bfq_io_cq अणु
	/* associated io_cq काष्ठाure */
	काष्ठा io_cq icq; /* must be the first member */
	/* array of two process queues, the sync and the async */
	काष्ठा bfq_queue *bfqq[2];
	/* per (request_queue, blkcg) ioprio */
	पूर्णांक ioprio;
#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
	uपूर्णांक64_t blkcg_serial_nr; /* the current blkcg serial */
#पूर्ण_अगर
	/*
	 * Snapshot of the has_लघु_समय flag beक्रमe merging; taken
	 * to remember its value जबतक the queue is merged, so as to
	 * be able to restore it in हाल of split.
	 */
	bool saved_has_लघु_tसमय;
	/*
	 * Same purpose as the previous two fields क्रम the I/O bound
	 * classअगरication of a queue.
	 */
	bool saved_IO_bound;

	u64 saved_io_start_समय;
	u64 saved_tot_idle_समय;

	/*
	 * Same purpose as the previous fields क्रम the value of the
	 * field keeping the queue's beदीर्घing to a large burst
	 */
	bool saved_in_large_burst;
	/*
	 * True अगर the queue beदीर्घed to a burst list beक्रमe its merge
	 * with another cooperating queue.
	 */
	bool was_in_burst_list;

	/*
	 * Save the weight when a merge occurs, to be able
	 * to restore it in हाल of split. If the weight is not
	 * correctly resumed when the queue is recycled,
	 * then the weight of the recycled queue could dअगरfer
	 * from the weight of the original queue.
	 */
	अचिन्हित पूर्णांक saved_weight;

	/*
	 * Similar to previous fields: save wr inक्रमmation.
	 */
	अचिन्हित दीर्घ saved_wr_coeff;
	अचिन्हित दीर्घ saved_last_wr_start_finish;
	अचिन्हित दीर्घ saved_service_from_wr;
	अचिन्हित दीर्घ saved_wr_start_at_चयन_to_srt;
	अचिन्हित पूर्णांक saved_wr_cur_max_समय;
	काष्ठा bfq_tसमय saved_tसमय;

	/* Save also injection state */
	u64 saved_last_serv_समय_ns;
	अचिन्हित पूर्णांक saved_inject_limit;
	अचिन्हित दीर्घ saved_decrease_समय_jअगर;

	/* candidate queue क्रम a stable merge (due to बंद creation समय) */
	काष्ठा bfq_queue *stable_merge_bfqq;

	bool stably_merged;	/* non splittable अगर true */
पूर्ण;

/**
 * काष्ठा bfq_data - per-device data काष्ठाure.
 *
 * All the fields are रक्षित by @lock.
 */
काष्ठा bfq_data अणु
	/* device request queue */
	काष्ठा request_queue *queue;
	/* dispatch queue */
	काष्ठा list_head dispatch;

	/* root bfq_group क्रम the device */
	काष्ठा bfq_group *root_group;

	/*
	 * rbtree of weight counters of @bfq_queues, sorted by
	 * weight. Used to keep track of whether all @bfq_queues have
	 * the same weight. The tree contains one counter क्रम each
	 * distinct weight associated to some active and not
	 * weight-उठाओd @bfq_queue (see the comments to the functions
	 * bfq_weights_tree_[add|हटाओ] क्रम further details).
	 */
	काष्ठा rb_root_cached queue_weights_tree;

	/*
	 * Number of groups with at least one descendant process that
	 * has at least one request रुकोing क्रम completion. Note that
	 * this accounts क्रम also requests alपढ़ोy dispatched, but not
	 * yet completed. Thereक्रमe this number of groups may dअगरfer
	 * (be larger) than the number of active groups, as a group is
	 * considered active only अगर its corresponding entity has
	 * descendant queues with at least one request queued. This
	 * number is used to decide whether a scenario is symmetric.
	 * For a detailed explanation see comments on the computation
	 * of the variable asymmetric_scenario in the function
	 * bfq_better_to_idle().
	 *
	 * However, it is hard to compute this number exactly, क्रम
	 * groups with multiple descendant processes. Consider a group
	 * that is inactive, i.e., that has no descendant process with
	 * pending I/O inside BFQ queues. Then suppose that
	 * num_groups_with_pending_reqs is still accounting क्रम this
	 * group, because the group has descendant processes with some
	 * I/O request still in flight. num_groups_with_pending_reqs
	 * should be decremented when the in-flight request of the
	 * last descendant process is finally completed (assuming that
	 * nothing अन्यथा has changed क्रम the group in the meanसमय, in
	 * terms of composition of the group and active/inactive state of child
	 * groups and processes). To accomplish this, an additional
	 * pending-request counter must be added to entities, and must
	 * be updated correctly. To aव्योम this additional field and operations,
	 * we resort to the following tradeoff between simplicity and
	 * accuracy: क्रम an inactive group that is still counted in
	 * num_groups_with_pending_reqs, we decrement
	 * num_groups_with_pending_reqs when the first descendant
	 * process of the group reमुख्यs with no request रुकोing क्रम
	 * completion.
	 *
	 * Even this simpler decrement strategy requires a little
	 * carefulness: to aव्योम multiple decrements, we flag a group,
	 * more precisely an entity representing a group, as still
	 * counted in num_groups_with_pending_reqs when it becomes
	 * inactive. Then, when the first descendant queue of the
	 * entity reमुख्यs with no request रुकोing क्रम completion,
	 * num_groups_with_pending_reqs is decremented, and this flag
	 * is reset. After this flag is reset क्रम the entity,
	 * num_groups_with_pending_reqs won't be decremented any
	 * दीर्घer in हाल a new descendant queue of the entity reमुख्यs
	 * with no request रुकोing क्रम completion.
	 */
	अचिन्हित पूर्णांक num_groups_with_pending_reqs;

	/*
	 * Per-class (RT, BE, IDLE) number of bfq_queues containing
	 * requests (including the queue in service, even अगर it is
	 * idling).
	 */
	अचिन्हित पूर्णांक busy_queues[3];
	/* number of weight-उठाओd busy @bfq_queues */
	पूर्णांक wr_busy_queues;
	/* number of queued requests */
	पूर्णांक queued;
	/* number of requests dispatched and रुकोing क्रम completion */
	पूर्णांक rq_in_driver;

	/* true अगर the device is non rotational and perक्रमms queueing */
	bool nonrot_with_queueing;

	/*
	 * Maximum number of requests in driver in the last
	 * @hw_tag_samples completed requests.
	 */
	पूर्णांक max_rq_in_driver;
	/* number of samples used to calculate hw_tag */
	पूर्णांक hw_tag_samples;
	/* flag set to one अगर the driver is showing a queueing behavior */
	पूर्णांक hw_tag;

	/* number of budमाला_लो asचिन्हित */
	पूर्णांक budमाला_लो_asचिन्हित;

	/*
	 * Timer set when idling (रुकोing) क्रम the next request from
	 * the queue in service.
	 */
	काष्ठा hrसमयr idle_slice_समयr;

	/* bfq_queue in service */
	काष्ठा bfq_queue *in_service_queue;

	/* on-disk position of the last served request */
	sector_t last_position;

	/* position of the last served request क्रम the in-service queue */
	sector_t in_serv_last_pos;

	/* समय of last request completion (ns) */
	u64 last_completion;

	/* bfqq owning the last completed rq */
	काष्ठा bfq_queue *last_completed_rq_bfqq;

	/* last bfqq created, among those in the root group */
	काष्ठा bfq_queue *last_bfqq_created;

	/* समय of last transition from empty to non-empty (ns) */
	u64 last_empty_occupied_ns;

	/*
	 * Flag set to activate the sampling of the total service समय
	 * of a just-arrived first I/O request (see
	 * bfq_update_inject_limit()). This will cause the setting of
	 * रुकोed_rq when the request is finally dispatched.
	 */
	bool रुको_dispatch;
	/*
	 *  If set, then bfq_update_inject_limit() is invoked when
	 *  रुकोed_rq is eventually completed.
	 */
	काष्ठा request *रुकोed_rq;
	/*
	 * True अगर some request has been injected during the last service hole.
	 */
	bool rqs_injected;

	/* समय of first rq dispatch in current observation पूर्णांकerval (ns) */
	u64 first_dispatch;
	/* समय of last rq dispatch in current observation पूर्णांकerval (ns) */
	u64 last_dispatch;

	/* beginning of the last budget */
	kसमय_प्रकार last_budget_start;
	/* beginning of the last idle slice */
	kसमय_प्रकार last_idling_start;
	अचिन्हित दीर्घ last_idling_start_jअगरfies;

	/* number of samples in current observation पूर्णांकerval */
	पूर्णांक peak_rate_samples;
	/* num of samples of seq dispatches in current observation पूर्णांकerval */
	u32 sequential_samples;
	/* total num of sectors transferred in current observation पूर्णांकerval */
	u64 tot_sectors_dispatched;
	/* max rq size seen during current observation पूर्णांकerval (sectors) */
	u32 last_rq_max_size;
	/* समय elapsed from first dispatch in current observ. पूर्णांकerval (us) */
	u64 delta_from_first;
	/*
	 * Current estimate of the device peak rate, measured in
	 * [(sectors/usec) / 2^BFQ_RATE_SHIFT]. The left-shअगरt by
	 * BFQ_RATE_SHIFT is perक्रमmed to increase precision in
	 * fixed-poपूर्णांक calculations.
	 */
	u32 peak_rate;

	/* maximum budget allotted to a bfq_queue beक्रमe rescheduling */
	पूर्णांक bfq_max_budget;

	/* list of all the bfq_queues active on the device */
	काष्ठा list_head active_list;
	/* list of all the bfq_queues idle on the device */
	काष्ठा list_head idle_list;

	/*
	 * Timeout क्रम async/sync requests; when it fires, requests
	 * are served in fअगरo order.
	 */
	u64 bfq_fअगरo_expire[2];
	/* weight of backward seeks wrt क्रमward ones */
	अचिन्हित पूर्णांक bfq_back_penalty;
	/* maximum allowed backward seek */
	अचिन्हित पूर्णांक bfq_back_max;
	/* maximum idling समय */
	u32 bfq_slice_idle;

	/* user-configured max budget value (0 क्रम स्वतः-tuning) */
	पूर्णांक bfq_user_max_budget;
	/*
	 * Timeout क्रम bfq_queues to consume their budget; used to
	 * prevent seeky queues from imposing दीर्घ latencies to
	 * sequential or quasi-sequential ones (this also implies that
	 * seeky queues cannot receive guarantees in the service
	 * करोमुख्य; after a समयout they are अक्षरged क्रम the समय they
	 * have been in service, to preserve fairness among them, but
	 * without service-करोमुख्य guarantees).
	 */
	अचिन्हित पूर्णांक bfq_समयout;

	/*
	 * Force device idling whenever needed to provide accurate
	 * service guarantees, without caring about throughput
	 * issues. CAVEAT: this may even increase latencies, in हाल
	 * of useless idling क्रम processes that did stop करोing I/O.
	 */
	bool strict_guarantees;

	/*
	 * Last समय at which a queue entered the current burst of
	 * queues being activated लघुly after each other; क्रम more
	 * details about this and the following parameters related to
	 * a burst of activations, see the comments on the function
	 * bfq_handle_burst.
	 */
	अचिन्हित दीर्घ last_ins_in_burst;
	/*
	 * Reference समय पूर्णांकerval used to decide whether a queue has
	 * been activated लघुly after @last_ins_in_burst.
	 */
	अचिन्हित दीर्घ bfq_burst_पूर्णांकerval;
	/* number of queues in the current burst of queue activations */
	पूर्णांक burst_size;

	/* common parent entity क्रम the queues in the burst */
	काष्ठा bfq_entity *burst_parent_entity;
	/* Maximum burst size above which the current queue-activation
	 * burst is deemed as 'large'.
	 */
	अचिन्हित दीर्घ bfq_large_burst_thresh;
	/* true अगर a large queue-activation burst is in progress */
	bool large_burst;
	/*
	 * Head of the burst list (as क्रम the above fields, more
	 * details in the comments on the function bfq_handle_burst).
	 */
	काष्ठा hlist_head burst_list;

	/* अगर set to true, low-latency heuristics are enabled */
	bool low_latency;
	/*
	 * Maximum factor by which the weight of a weight-उठाओd queue
	 * is multiplied.
	 */
	अचिन्हित पूर्णांक bfq_wr_coeff;
	/* maximum duration of a weight-raising period (jअगरfies) */
	अचिन्हित पूर्णांक bfq_wr_max_समय;

	/* Maximum weight-raising duration क्रम soft real-समय processes */
	अचिन्हित पूर्णांक bfq_wr_rt_max_समय;
	/*
	 * Minimum idle period after which weight-raising may be
	 * reactivated क्रम a queue (in jअगरfies).
	 */
	अचिन्हित पूर्णांक bfq_wr_min_idle_समय;
	/*
	 * Minimum period between request arrivals after which
	 * weight-raising may be reactivated क्रम an alपढ़ोy busy async
	 * queue (in jअगरfies).
	 */
	अचिन्हित दीर्घ bfq_wr_min_पूर्णांकer_arr_async;

	/* Max service-rate क्रम a soft real-समय queue, in sectors/sec */
	अचिन्हित पूर्णांक bfq_wr_max_softrt_rate;
	/*
	 * Cached value of the product ref_rate*ref_wr_duration, used
	 * क्रम computing the maximum duration of weight raising
	 * स्वतःmatically.
	 */
	u64 rate_dur_prod;

	/* fallback dummy bfqq क्रम extreme OOM conditions */
	काष्ठा bfq_queue oom_bfqq;

	spinlock_t lock;

	/*
	 * bic associated with the task issuing current bio क्रम
	 * merging. This and the next field are used as a support to
	 * be able to perक्रमm the bic lookup, needed by bio-merge
	 * functions, beक्रमe the scheduler lock is taken, and thus
	 * aव्योम taking the request-queue lock जबतक the scheduler
	 * lock is being held.
	 */
	काष्ठा bfq_io_cq *bio_bic;
	/* bfqq associated with the task issuing current bio क्रम merging */
	काष्ठा bfq_queue *bio_bfqq;

	/*
	 * Depth limits used in bfq_limit_depth (see comments on the
	 * function)
	 */
	अचिन्हित पूर्णांक word_depths[2][2];
पूर्ण;

क्रमागत bfqq_state_flags अणु
	BFQQF_just_created = 0,	/* queue just allocated */
	BFQQF_busy,		/* has requests or is in service */
	BFQQF_रुको_request,	/* रुकोing क्रम a request */
	BFQQF_non_blocking_रुको_rq, /*
				     * रुकोing क्रम a request
				     * without idling the device
				     */
	BFQQF_fअगरo_expire,	/* FIFO checked in this slice */
	BFQQF_has_लघु_tसमय,	/* queue has a लघु think समय */
	BFQQF_sync,		/* synchronous queue */
	BFQQF_IO_bound,		/*
				 * bfqq has समयd-out at least once
				 * having consumed at most 2/10 of
				 * its budget
				 */
	BFQQF_in_large_burst,	/*
				 * bfqq activated in a large burst,
				 * see comments to bfq_handle_burst.
				 */
	BFQQF_softrt_update,	/*
				 * may need softrt-next-start
				 * update
				 */
	BFQQF_coop,		/* bfqq is shared */
	BFQQF_split_coop,	/* shared bfqq will be split */
पूर्ण;

#घोषणा BFQ_BFQQ_FNS(name)						\
व्योम bfq_mark_bfqq_##name(काष्ठा bfq_queue *bfqq);			\
व्योम bfq_clear_bfqq_##name(काष्ठा bfq_queue *bfqq);			\
पूर्णांक bfq_bfqq_##name(स्थिर काष्ठा bfq_queue *bfqq);

BFQ_BFQQ_FNS(just_created);
BFQ_BFQQ_FNS(busy);
BFQ_BFQQ_FNS(रुको_request);
BFQ_BFQQ_FNS(non_blocking_रुको_rq);
BFQ_BFQQ_FNS(fअगरo_expire);
BFQ_BFQQ_FNS(has_लघु_tसमय);
BFQ_BFQQ_FNS(sync);
BFQ_BFQQ_FNS(IO_bound);
BFQ_BFQQ_FNS(in_large_burst);
BFQ_BFQQ_FNS(coop);
BFQ_BFQQ_FNS(split_coop);
BFQ_BFQQ_FNS(softrt_update);
#अघोषित BFQ_BFQQ_FNS

/* Expiration reasons. */
क्रमागत bfqq_expiration अणु
	BFQQE_TOO_IDLE = 0,		/*
					 * queue has been idling क्रम
					 * too दीर्घ
					 */
	BFQQE_BUDGET_TIMEOUT,	/* budget took too दीर्घ to be used */
	BFQQE_BUDGET_EXHAUSTED,	/* budget consumed */
	BFQQE_NO_MORE_REQUESTS,	/* the queue has no more requests */
	BFQQE_PREEMPTED		/* preemption in progress */
पूर्ण;

काष्ठा bfq_stat अणु
	काष्ठा percpu_counter		cpu_cnt;
	atomic64_t			aux_cnt;
पूर्ण;

काष्ठा bfqg_stats अणु
	/* basic stats */
	काष्ठा blkg_rwstat		bytes;
	काष्ठा blkg_rwstat		ios;
#अगर_घोषित CONFIG_BFQ_CGROUP_DEBUG
	/* number of ios merged */
	काष्ठा blkg_rwstat		merged;
	/* total समय spent on device in ns, may not be accurate w/ queueing */
	काष्ठा blkg_rwstat		service_समय;
	/* total समय spent रुकोing in scheduler queue in ns */
	काष्ठा blkg_rwstat		रुको_समय;
	/* number of IOs queued up */
	काष्ठा blkg_rwstat		queued;
	/* total disk समय and nr sectors dispatched by this group */
	काष्ठा bfq_stat		समय;
	/* sum of number of ios queued across all samples */
	काष्ठा bfq_stat		avg_queue_size_sum;
	/* count of samples taken क्रम average */
	काष्ठा bfq_stat		avg_queue_size_samples;
	/* how many बार this group has been हटाओd from service tree */
	काष्ठा bfq_stat		dequeue;
	/* total समय spent रुकोing क्रम it to be asचिन्हित a बारlice. */
	काष्ठा bfq_stat		group_रुको_समय;
	/* समय spent idling क्रम this blkcg_gq */
	काष्ठा bfq_stat		idle_समय;
	/* total समय with empty current active q with other requests queued */
	काष्ठा bfq_stat		empty_समय;
	/* fields after this shouldn't be cleared on stat reset */
	u64				start_group_रुको_समय;
	u64				start_idle_समय;
	u64				start_empty_समय;
	uपूर्णांक16_t			flags;
#पूर्ण_अगर /* CONFIG_BFQ_CGROUP_DEBUG */
पूर्ण;

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED

/*
 * काष्ठा bfq_group_data - per-blkcg storage क्रम the blkio subप्रणाली.
 *
 * @ps: @blkcg_policy_storage that this काष्ठाure inherits
 * @weight: weight of the bfq_group
 */
काष्ठा bfq_group_data अणु
	/* must be the first member */
	काष्ठा blkcg_policy_data pd;

	अचिन्हित पूर्णांक weight;
पूर्ण;

/**
 * काष्ठा bfq_group - per (device, cgroup) data काष्ठाure.
 * @entity: schedulable entity to insert पूर्णांकo the parent group sched_data.
 * @sched_data: own sched_data, to contain child entities (they may be
 *              both bfq_queues and bfq_groups).
 * @bfqd: the bfq_data क्रम the device this group acts upon.
 * @async_bfqq: array of async queues क्रम all the tasks beदीर्घing to
 *              the group, one queue per ioprio value per ioprio_class,
 *              except क्रम the idle class that has only one queue.
 * @async_idle_bfqq: async queue क्रम the idle class (ioprio is ignored).
 * @my_entity: poपूर्णांकer to @entity, %शून्य क्रम the toplevel group; used
 *             to aव्योम too many special हालs during group creation/
 *             migration.
 * @stats: stats क्रम this bfqg.
 * @active_entities: number of active entities beदीर्घing to the group;
 *                   unused क्रम the root group. Used to know whether there
 *                   are groups with more than one active @bfq_entity
 *                   (see the comments to the function
 *                   bfq_bfqq_may_idle()).
 * @rq_pos_tree: rbtree sorted by next_request position, used when
 *               determining अगर two or more queues have पूर्णांकerleaving
 *               requests (see bfq_find_बंद_coचालक()).
 *
 * Each (device, cgroup) pair has its own bfq_group, i.e., क्रम each cgroup
 * there is a set of bfq_groups, each one collecting the lower-level
 * entities beदीर्घing to the group that are acting on the same device.
 *
 * Locking works as follows:
 *    o @bfqd is रक्षित by the queue lock, RCU is used to access it
 *      from the पढ़ोers.
 *    o All the other fields are रक्षित by the @bfqd queue lock.
 */
काष्ठा bfq_group अणु
	/* must be the first member */
	काष्ठा blkg_policy_data pd;

	/* cached path क्रम this blkg (see comments in bfq_bic_update_cgroup) */
	अक्षर blkg_path[128];

	/* reference counter (see comments in bfq_bic_update_cgroup) */
	पूर्णांक ref;

	काष्ठा bfq_entity entity;
	काष्ठा bfq_sched_data sched_data;

	व्योम *bfqd;

	काष्ठा bfq_queue *async_bfqq[2][IOPRIO_BE_NR];
	काष्ठा bfq_queue *async_idle_bfqq;

	काष्ठा bfq_entity *my_entity;

	पूर्णांक active_entities;

	काष्ठा rb_root rq_pos_tree;

	काष्ठा bfqg_stats stats;
पूर्ण;

#अन्यथा
काष्ठा bfq_group अणु
	काष्ठा bfq_entity entity;
	काष्ठा bfq_sched_data sched_data;

	काष्ठा bfq_queue *async_bfqq[2][IOPRIO_BE_NR];
	काष्ठा bfq_queue *async_idle_bfqq;

	काष्ठा rb_root rq_pos_tree;
पूर्ण;
#पूर्ण_अगर

काष्ठा bfq_queue *bfq_entity_to_bfqq(काष्ठा bfq_entity *entity);

/* --------------- मुख्य algorithm पूर्णांकerface ----------------- */

#घोषणा BFQ_SERVICE_TREE_INIT	((काष्ठा bfq_service_tree)		\
				अणु RB_ROOT, RB_ROOT, शून्य, शून्य, 0, 0 पूर्ण)

बाह्य स्थिर पूर्णांक bfq_समयout;

काष्ठा bfq_queue *bic_to_bfqq(काष्ठा bfq_io_cq *bic, bool is_sync);
व्योम bic_set_bfqq(काष्ठा bfq_io_cq *bic, काष्ठा bfq_queue *bfqq, bool is_sync);
काष्ठा bfq_data *bic_to_bfqd(काष्ठा bfq_io_cq *bic);
व्योम bfq_pos_tree_add_move(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq);
व्योम bfq_weights_tree_add(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			  काष्ठा rb_root_cached *root);
व्योम __bfq_weights_tree_हटाओ(काष्ठा bfq_data *bfqd,
			       काष्ठा bfq_queue *bfqq,
			       काष्ठा rb_root_cached *root);
व्योम bfq_weights_tree_हटाओ(काष्ठा bfq_data *bfqd,
			     काष्ठा bfq_queue *bfqq);
व्योम bfq_bfqq_expire(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		     bool compensate, क्रमागत bfqq_expiration reason);
व्योम bfq_put_queue(काष्ठा bfq_queue *bfqq);
व्योम bfq_end_wr_async_queues(काष्ठा bfq_data *bfqd, काष्ठा bfq_group *bfqg);
व्योम bfq_release_process_ref(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq);
व्योम bfq_schedule_dispatch(काष्ठा bfq_data *bfqd);
व्योम bfq_put_async_queues(काष्ठा bfq_data *bfqd, काष्ठा bfq_group *bfqg);

/* ------------ end of मुख्य algorithm पूर्णांकerface -------------- */

/* ---------------- cgroups-support पूर्णांकerface ---------------- */

व्योम bfqg_stats_update_legacy_io(काष्ठा request_queue *q, काष्ठा request *rq);
व्योम bfqg_stats_update_io_add(काष्ठा bfq_group *bfqg, काष्ठा bfq_queue *bfqq,
			      अचिन्हित पूर्णांक op);
व्योम bfqg_stats_update_io_हटाओ(काष्ठा bfq_group *bfqg, अचिन्हित पूर्णांक op);
व्योम bfqg_stats_update_io_merged(काष्ठा bfq_group *bfqg, अचिन्हित पूर्णांक op);
व्योम bfqg_stats_update_completion(काष्ठा bfq_group *bfqg, u64 start_समय_ns,
				  u64 io_start_समय_ns, अचिन्हित पूर्णांक op);
व्योम bfqg_stats_update_dequeue(काष्ठा bfq_group *bfqg);
व्योम bfqg_stats_set_start_empty_समय(काष्ठा bfq_group *bfqg);
व्योम bfqg_stats_update_idle_समय(काष्ठा bfq_group *bfqg);
व्योम bfqg_stats_set_start_idle_समय(काष्ठा bfq_group *bfqg);
व्योम bfqg_stats_update_avg_queue_size(काष्ठा bfq_group *bfqg);
व्योम bfq_bfqq_move(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		   काष्ठा bfq_group *bfqg);

व्योम bfq_init_entity(काष्ठा bfq_entity *entity, काष्ठा bfq_group *bfqg);
व्योम bfq_bic_update_cgroup(काष्ठा bfq_io_cq *bic, काष्ठा bio *bio);
व्योम bfq_end_wr_async(काष्ठा bfq_data *bfqd);
काष्ठा bfq_group *bfq_find_set_group(काष्ठा bfq_data *bfqd,
				     काष्ठा blkcg *blkcg);
काष्ठा blkcg_gq *bfqg_to_blkg(काष्ठा bfq_group *bfqg);
काष्ठा bfq_group *bfqq_group(काष्ठा bfq_queue *bfqq);
काष्ठा bfq_group *bfq_create_group_hierarchy(काष्ठा bfq_data *bfqd, पूर्णांक node);
व्योम bfqg_and_blkg_put(काष्ठा bfq_group *bfqg);

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
बाह्य काष्ठा cftype bfq_blkcg_legacy_files[];
बाह्य काष्ठा cftype bfq_blkg_files[];
बाह्य काष्ठा blkcg_policy blkcg_policy_bfq;
#पूर्ण_अगर

/* ------------- end of cgroups-support पूर्णांकerface ------------- */

/* - पूर्णांकerface of the पूर्णांकernal hierarchical B-WF2Q+ scheduler - */

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
/* both next loops stop at one of the child entities of the root group */
#घोषणा क्रम_each_entity(entity)	\
	क्रम (; entity ; entity = entity->parent)

/*
 * For each iteration, compute parent in advance, so as to be safe अगर
 * entity is deallocated during the iteration. Such a deallocation may
 * happen as a consequence of a bfq_put_queue that मुक्तs the bfq_queue
 * containing entity.
 */
#घोषणा क्रम_each_entity_safe(entity, parent) \
	क्रम (; entity && (अणु parent = entity->parent; 1; पूर्ण); entity = parent)

#अन्यथा /* CONFIG_BFQ_GROUP_IOSCHED */
/*
 * Next two macros are fake loops when cgroups support is not
 * enabled. I fact, in such a हाल, there is only one level to go up
 * (to reach the root group).
 */
#घोषणा क्रम_each_entity(entity)	\
	क्रम (; entity ; entity = शून्य)

#घोषणा क्रम_each_entity_safe(entity, parent) \
	क्रम (parent = शून्य; entity ; entity = parent)
#पूर्ण_अगर /* CONFIG_BFQ_GROUP_IOSCHED */

काष्ठा bfq_group *bfq_bfqq_to_bfqg(काष्ठा bfq_queue *bfqq);
काष्ठा bfq_queue *bfq_entity_to_bfqq(काष्ठा bfq_entity *entity);
अचिन्हित पूर्णांक bfq_tot_busy_queues(काष्ठा bfq_data *bfqd);
काष्ठा bfq_service_tree *bfq_entity_service_tree(काष्ठा bfq_entity *entity);
काष्ठा bfq_entity *bfq_entity_of(काष्ठा rb_node *node);
अचिन्हित लघु bfq_ioprio_to_weight(पूर्णांक ioprio);
व्योम bfq_put_idle_entity(काष्ठा bfq_service_tree *st,
			 काष्ठा bfq_entity *entity);
काष्ठा bfq_service_tree *
__bfq_entity_update_weight_prio(काष्ठा bfq_service_tree *old_st,
				काष्ठा bfq_entity *entity,
				bool update_class_too);
व्योम bfq_bfqq_served(काष्ठा bfq_queue *bfqq, पूर्णांक served);
व्योम bfq_bfqq_अक्षरge_समय(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			  अचिन्हित दीर्घ समय_ms);
bool __bfq_deactivate_entity(काष्ठा bfq_entity *entity,
			     bool ins_पूर्णांकo_idle_tree);
bool next_queue_may_preempt(काष्ठा bfq_data *bfqd);
काष्ठा bfq_queue *bfq_get_next_queue(काष्ठा bfq_data *bfqd);
bool __bfq_bfqd_reset_in_service(काष्ठा bfq_data *bfqd);
व्योम bfq_deactivate_bfqq(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
			 bool ins_पूर्णांकo_idle_tree, bool expiration);
व्योम bfq_activate_bfqq(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq);
व्योम bfq_requeue_bfqq(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		      bool expiration);
व्योम bfq_del_bfqq_busy(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq,
		       bool expiration);
व्योम bfq_add_bfqq_busy(काष्ठा bfq_data *bfqd, काष्ठा bfq_queue *bfqq);

/* --------------- end of पूर्णांकerface of B-WF2Q+ ---------------- */

/* Logging facilities. */
अटल अंतरभूत व्योम bfq_pid_to_str(पूर्णांक pid, अक्षर *str, पूर्णांक len)
अणु
	अगर (pid != -1)
		snम_लिखो(str, len, "%d", pid);
	अन्यथा
		snम_लिखो(str, len, "SHARED-");
पूर्ण

#अगर_घोषित CONFIG_BFQ_GROUP_IOSCHED
काष्ठा bfq_group *bfqq_group(काष्ठा bfq_queue *bfqq);

#घोषणा bfq_log_bfqq(bfqd, bfqq, fmt, args...)	करो अणु			\
	अक्षर pid_str[MAX_PID_STR_LENGTH];	\
	अगर (likely(!blk_trace_note_message_enabled((bfqd)->queue)))	\
		अवरोध;							\
	bfq_pid_to_str((bfqq)->pid, pid_str, MAX_PID_STR_LENGTH);	\
	blk_add_cgroup_trace_msg((bfqd)->queue,				\
			bfqg_to_blkg(bfqq_group(bfqq))->blkcg,		\
			"bfq%s%c " fmt, pid_str,			\
			bfq_bfqq_sync((bfqq)) ? 'S' : 'A', ##args);	\
पूर्ण जबतक (0)

#घोषणा bfq_log_bfqg(bfqd, bfqg, fmt, args...)	करो अणु			\
	blk_add_cgroup_trace_msg((bfqd)->queue,				\
		bfqg_to_blkg(bfqg)->blkcg, fmt, ##args);		\
पूर्ण जबतक (0)

#अन्यथा /* CONFIG_BFQ_GROUP_IOSCHED */

#घोषणा bfq_log_bfqq(bfqd, bfqq, fmt, args...) करो अणु	\
	अक्षर pid_str[MAX_PID_STR_LENGTH];	\
	अगर (likely(!blk_trace_note_message_enabled((bfqd)->queue)))	\
		अवरोध;							\
	bfq_pid_to_str((bfqq)->pid, pid_str, MAX_PID_STR_LENGTH);	\
	blk_add_trace_msg((bfqd)->queue, "bfq%s%c " fmt, pid_str,	\
			bfq_bfqq_sync((bfqq)) ? 'S' : 'A',		\
				##args);	\
पूर्ण जबतक (0)
#घोषणा bfq_log_bfqg(bfqd, bfqg, fmt, args...)		करो अणुपूर्ण जबतक (0)

#पूर्ण_अगर /* CONFIG_BFQ_GROUP_IOSCHED */

#घोषणा bfq_log(bfqd, fmt, args...) \
	blk_add_trace_msg((bfqd)->queue, "bfq " fmt, ##args)

#पूर्ण_अगर /* _BFQ_H */
