<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interface क्रम controlling IO bandwidth on a request queue
 *
 * Copyright (C) 2010 Vivek Goyal <vgoyal@redhat.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blktrace_api.h>
#समावेश <linux/blk-cgroup.h>
#समावेश "blk.h"
#समावेश "blk-cgroup-rwstat.h"

/* Max dispatch from a group in 1 round */
#घोषणा THROTL_GRP_QUANTUM 8

/* Total max dispatch from all groups in one round */
#घोषणा THROTL_QUANTUM 32

/* Throttling is perक्रमmed over a slice and after that slice is renewed */
#घोषणा DFL_THROTL_SLICE_HD (HZ / 10)
#घोषणा DFL_THROTL_SLICE_SSD (HZ / 50)
#घोषणा MAX_THROTL_SLICE (HZ)
#घोषणा MAX_IDLE_TIME (5L * 1000 * 1000) /* 5 s */
#घोषणा MIN_THROTL_BPS (320 * 1024)
#घोषणा MIN_THROTL_IOPS (10)
#घोषणा DFL_LATENCY_TARGET (-1L)
#घोषणा DFL_IDLE_THRESHOLD (0)
#घोषणा DFL_HD_BASELINE_LATENCY (4000L) /* 4ms */
#घोषणा LATENCY_FILTERED_SSD (0)
/*
 * For HD, very small latency comes from sequential IO. Such IO is helpless to
 * help determine अगर its IO is impacted by others, hence we ignore the IO
 */
#घोषणा LATENCY_FILTERED_HD (1000L) /* 1ms */

अटल काष्ठा blkcg_policy blkcg_policy_throtl;

/* A workqueue to queue throttle related work */
अटल काष्ठा workqueue_काष्ठा *kthrotld_workqueue;

/*
 * To implement hierarchical throttling, throtl_grps क्रमm a tree and bios
 * are dispatched upwards level by level until they reach the top and get
 * issued.  When dispatching bios from the children and local group at each
 * level, अगर the bios are dispatched पूर्णांकo a single bio_list, there's a risk
 * of a local or child group which can queue many bios at once filling up
 * the list starving others.
 *
 * To aव्योम such starvation, dispatched bios are queued separately
 * according to where they came from.  When they are again dispatched to
 * the parent, they're popped in round-robin order so that no single source
 * hogs the dispatch winकरोw.
 *
 * throtl_qnode is used to keep the queued bios separated by their sources.
 * Bios are queued to throtl_qnode which in turn is queued to
 * throtl_service_queue and then dispatched in round-robin order.
 *
 * It's also used to track the reference counts on blkg's.  A qnode always
 * beदीर्घs to a throtl_grp and माला_लो queued on itself or the parent, so
 * incrementing the reference of the associated throtl_grp when a qnode is
 * queued and decrementing when dequeued is enough to keep the whole blkg
 * tree pinned जबतक bios are in flight.
 */
काष्ठा throtl_qnode अणु
	काष्ठा list_head	node;		/* service_queue->queued[] */
	काष्ठा bio_list		bios;		/* queued bios */
	काष्ठा throtl_grp	*tg;		/* tg this qnode beदीर्घs to */
पूर्ण;

काष्ठा throtl_service_queue अणु
	काष्ठा throtl_service_queue *parent_sq;	/* the parent service_queue */

	/*
	 * Bios queued directly to this service_queue or dispatched from
	 * children throtl_grp's.
	 */
	काष्ठा list_head	queued[2];	/* throtl_qnode [READ/WRITE] */
	अचिन्हित पूर्णांक		nr_queued[2];	/* number of queued bios */

	/*
	 * RB tree of active children throtl_grp's, which are sorted by
	 * their ->dispसमय.
	 */
	काष्ठा rb_root_cached	pending_tree;	/* RB tree of active tgs */
	अचिन्हित पूर्णांक		nr_pending;	/* # queued in the tree */
	अचिन्हित दीर्घ		first_pending_dispसमय;	/* dispसमय of the first tg */
	काष्ठा समयr_list	pending_समयr;	/* fires on first_pending_dispसमय */
पूर्ण;

क्रमागत tg_state_flags अणु
	THROTL_TG_PENDING	= 1 << 0,	/* on parent's pending tree */
	THROTL_TG_WAS_EMPTY	= 1 << 1,	/* bio_lists[] became non-empty */
पूर्ण;

#घोषणा rb_entry_tg(node)	rb_entry((node), काष्ठा throtl_grp, rb_node)

क्रमागत अणु
	LIMIT_LOW,
	LIMIT_MAX,
	LIMIT_CNT,
पूर्ण;

काष्ठा throtl_grp अणु
	/* must be the first member */
	काष्ठा blkg_policy_data pd;

	/* active throtl group service_queue member */
	काष्ठा rb_node rb_node;

	/* throtl_data this group beदीर्घs to */
	काष्ठा throtl_data *td;

	/* this group's service queue */
	काष्ठा throtl_service_queue service_queue;

	/*
	 * qnode_on_self is used when bios are directly queued to this
	 * throtl_grp so that local bios compete fairly with bios
	 * dispatched from children.  qnode_on_parent is used when bios are
	 * dispatched from this throtl_grp पूर्णांकo its parent and will compete
	 * with the sibling qnode_on_parents and the parent's
	 * qnode_on_self.
	 */
	काष्ठा throtl_qnode qnode_on_self[2];
	काष्ठा throtl_qnode qnode_on_parent[2];

	/*
	 * Dispatch समय in jअगरfies. This is the estimated समय when group
	 * will unthrottle and is पढ़ोy to dispatch more bio. It is used as
	 * key to sort active groups in service tree.
	 */
	अचिन्हित दीर्घ dispसमय;

	अचिन्हित पूर्णांक flags;

	/* are there any throtl rules between this group and td? */
	bool has_rules[2];

	/* पूर्णांकernally used bytes per second rate limits */
	uपूर्णांक64_t bps[2][LIMIT_CNT];
	/* user configured bps limits */
	uपूर्णांक64_t bps_conf[2][LIMIT_CNT];

	/* पूर्णांकernally used IOPS limits */
	अचिन्हित पूर्णांक iops[2][LIMIT_CNT];
	/* user configured IOPS limits */
	अचिन्हित पूर्णांक iops_conf[2][LIMIT_CNT];

	/* Number of bytes dispatched in current slice */
	uपूर्णांक64_t bytes_disp[2];
	/* Number of bio's dispatched in current slice */
	अचिन्हित पूर्णांक io_disp[2];

	अचिन्हित दीर्घ last_low_overflow_समय[2];

	uपूर्णांक64_t last_bytes_disp[2];
	अचिन्हित पूर्णांक last_io_disp[2];

	अचिन्हित दीर्घ last_check_समय;

	अचिन्हित दीर्घ latency_target; /* us */
	अचिन्हित दीर्घ latency_target_conf; /* us */
	/* When did we start a new slice */
	अचिन्हित दीर्घ slice_start[2];
	अचिन्हित दीर्घ slice_end[2];

	अचिन्हित दीर्घ last_finish_समय; /* ns / 1024 */
	अचिन्हित दीर्घ checked_last_finish_समय; /* ns / 1024 */
	अचिन्हित दीर्घ avg_idleसमय; /* ns / 1024 */
	अचिन्हित दीर्घ idleसमय_प्रकारhreshold; /* us */
	अचिन्हित दीर्घ idleसमय_प्रकारhreshold_conf; /* us */

	अचिन्हित पूर्णांक bio_cnt; /* total bios */
	अचिन्हित पूर्णांक bad_bio_cnt; /* bios exceeding latency threshold */
	अचिन्हित दीर्घ bio_cnt_reset_समय;

	काष्ठा blkg_rwstat stat_bytes;
	काष्ठा blkg_rwstat stat_ios;
पूर्ण;

/* We measure latency क्रम request size from <= 4k to >= 1M */
#घोषणा LATENCY_BUCKET_SIZE 9

काष्ठा latency_bucket अणु
	अचिन्हित दीर्घ total_latency; /* ns / 1024 */
	पूर्णांक samples;
पूर्ण;

काष्ठा avg_latency_bucket अणु
	अचिन्हित दीर्घ latency; /* ns / 1024 */
	bool valid;
पूर्ण;

काष्ठा throtl_data
अणु
	/* service tree क्रम active throtl groups */
	काष्ठा throtl_service_queue service_queue;

	काष्ठा request_queue *queue;

	/* Total Number of queued bios on READ and WRITE lists */
	अचिन्हित पूर्णांक nr_queued[2];

	अचिन्हित पूर्णांक throtl_slice;

	/* Work क्रम dispatching throttled bios */
	काष्ठा work_काष्ठा dispatch_work;
	अचिन्हित पूर्णांक limit_index;
	bool limit_valid[LIMIT_CNT];

	अचिन्हित दीर्घ low_upgrade_समय;
	अचिन्हित दीर्घ low_करोwngrade_समय;

	अचिन्हित पूर्णांक scale;

	काष्ठा latency_bucket पंचांगp_buckets[2][LATENCY_BUCKET_SIZE];
	काष्ठा avg_latency_bucket avg_buckets[2][LATENCY_BUCKET_SIZE];
	काष्ठा latency_bucket __percpu *latency_buckets[2];
	अचिन्हित दीर्घ last_calculate_समय;
	अचिन्हित दीर्घ filtered_latency;

	bool track_bio_latency;
पूर्ण;

अटल व्योम throtl_pending_समयr_fn(काष्ठा समयr_list *t);

अटल अंतरभूत काष्ठा throtl_grp *pd_to_tg(काष्ठा blkg_policy_data *pd)
अणु
	वापस pd ? container_of(pd, काष्ठा throtl_grp, pd) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा throtl_grp *blkg_to_tg(काष्ठा blkcg_gq *blkg)
अणु
	वापस pd_to_tg(blkg_to_pd(blkg, &blkcg_policy_throtl));
पूर्ण

अटल अंतरभूत काष्ठा blkcg_gq *tg_to_blkg(काष्ठा throtl_grp *tg)
अणु
	वापस pd_to_blkg(&tg->pd);
पूर्ण

/**
 * sq_to_tg - वापस the throl_grp the specअगरied service queue beदीर्घs to
 * @sq: the throtl_service_queue of पूर्णांकerest
 *
 * Return the throtl_grp @sq beदीर्घs to.  If @sq is the top-level one
 * embedded in throtl_data, %शून्य is वापसed.
 */
अटल काष्ठा throtl_grp *sq_to_tg(काष्ठा throtl_service_queue *sq)
अणु
	अगर (sq && sq->parent_sq)
		वापस container_of(sq, काष्ठा throtl_grp, service_queue);
	अन्यथा
		वापस शून्य;
पूर्ण

/**
 * sq_to_td - वापस throtl_data the specअगरied service queue beदीर्घs to
 * @sq: the throtl_service_queue of पूर्णांकerest
 *
 * A service_queue can be embedded in either a throtl_grp or throtl_data.
 * Determine the associated throtl_data accordingly and वापस it.
 */
अटल काष्ठा throtl_data *sq_to_td(काष्ठा throtl_service_queue *sq)
अणु
	काष्ठा throtl_grp *tg = sq_to_tg(sq);

	अगर (tg)
		वापस tg->td;
	अन्यथा
		वापस container_of(sq, काष्ठा throtl_data, service_queue);
पूर्ण

/*
 * cgroup's limit in LIMIT_MAX is scaled अगर low limit is set. This scale is to
 * make the IO dispatch more smooth.
 * Scale up: linearly scale up according to lapsed समय since upgrade. For
 *           every throtl_slice, the limit scales up 1/2 .low limit till the
 *           limit hits .max limit
 * Scale करोwn: exponentially scale करोwn अगर a cgroup करोesn't hit its .low limit
 */
अटल uपूर्णांक64_t throtl_adjusted_limit(uपूर्णांक64_t low, काष्ठा throtl_data *td)
अणु
	/* arbitrary value to aव्योम too big scale */
	अगर (td->scale < 4096 && समय_after_eq(jअगरfies,
	    td->low_upgrade_समय + td->scale * td->throtl_slice))
		td->scale = (jअगरfies - td->low_upgrade_समय) / td->throtl_slice;

	वापस low + (low >> 1) * td->scale;
पूर्ण

अटल uपूर्णांक64_t tg_bps_limit(काष्ठा throtl_grp *tg, पूर्णांक rw)
अणु
	काष्ठा blkcg_gq *blkg = tg_to_blkg(tg);
	काष्ठा throtl_data *td;
	uपूर्णांक64_t ret;

	अगर (cgroup_subsys_on_dfl(io_cgrp_subsys) && !blkg->parent)
		वापस U64_MAX;

	td = tg->td;
	ret = tg->bps[rw][td->limit_index];
	अगर (ret == 0 && td->limit_index == LIMIT_LOW) अणु
		/* पूर्णांकermediate node or iops isn't 0 */
		अगर (!list_empty(&blkg->blkcg->css.children) ||
		    tg->iops[rw][td->limit_index])
			वापस U64_MAX;
		अन्यथा
			वापस MIN_THROTL_BPS;
	पूर्ण

	अगर (td->limit_index == LIMIT_MAX && tg->bps[rw][LIMIT_LOW] &&
	    tg->bps[rw][LIMIT_LOW] != tg->bps[rw][LIMIT_MAX]) अणु
		uपूर्णांक64_t adjusted;

		adjusted = throtl_adjusted_limit(tg->bps[rw][LIMIT_LOW], td);
		ret = min(tg->bps[rw][LIMIT_MAX], adjusted);
	पूर्ण
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक tg_iops_limit(काष्ठा throtl_grp *tg, पूर्णांक rw)
अणु
	काष्ठा blkcg_gq *blkg = tg_to_blkg(tg);
	काष्ठा throtl_data *td;
	अचिन्हित पूर्णांक ret;

	अगर (cgroup_subsys_on_dfl(io_cgrp_subsys) && !blkg->parent)
		वापस अच_पूर्णांक_उच्च;

	td = tg->td;
	ret = tg->iops[rw][td->limit_index];
	अगर (ret == 0 && tg->td->limit_index == LIMIT_LOW) अणु
		/* पूर्णांकermediate node or bps isn't 0 */
		अगर (!list_empty(&blkg->blkcg->css.children) ||
		    tg->bps[rw][td->limit_index])
			वापस अच_पूर्णांक_उच्च;
		अन्यथा
			वापस MIN_THROTL_IOPS;
	पूर्ण

	अगर (td->limit_index == LIMIT_MAX && tg->iops[rw][LIMIT_LOW] &&
	    tg->iops[rw][LIMIT_LOW] != tg->iops[rw][LIMIT_MAX]) अणु
		uपूर्णांक64_t adjusted;

		adjusted = throtl_adjusted_limit(tg->iops[rw][LIMIT_LOW], td);
		अगर (adjusted > अच_पूर्णांक_उच्च)
			adjusted = अच_पूर्णांक_उच्च;
		ret = min_t(अचिन्हित पूर्णांक, tg->iops[rw][LIMIT_MAX], adjusted);
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा request_bucket_index(sectors) \
	clamp_t(पूर्णांक, order_base_2(sectors) - 3, 0, LATENCY_BUCKET_SIZE - 1)

/**
 * throtl_log - log debug message via blktrace
 * @sq: the service_queue being reported
 * @fmt: म_लिखो क्रमmat string
 * @args: म_लिखो args
 *
 * The messages are prefixed with "throtl BLKG_NAME" अगर @sq beदीर्घs to a
 * throtl_grp; otherwise, just "throtl".
 */
#घोषणा throtl_log(sq, fmt, args...)	करो अणु				\
	काष्ठा throtl_grp *__tg = sq_to_tg((sq));			\
	काष्ठा throtl_data *__td = sq_to_td((sq));			\
									\
	(व्योम)__td;							\
	अगर (likely(!blk_trace_note_message_enabled(__td->queue)))	\
		अवरोध;							\
	अगर ((__tg)) अणु							\
		blk_add_cgroup_trace_msg(__td->queue,			\
			tg_to_blkg(__tg)->blkcg, "throtl " fmt, ##args);\
	पूर्ण अन्यथा अणु							\
		blk_add_trace_msg(__td->queue, "throtl " fmt, ##args);	\
	पूर्ण								\
पूर्ण जबतक (0)

अटल अंतरभूत अचिन्हित पूर्णांक throtl_bio_data_size(काष्ठा bio *bio)
अणु
	/* assume it's one sector */
	अगर (unlikely(bio_op(bio) == REQ_OP_DISCARD))
		वापस 512;
	वापस bio->bi_iter.bi_size;
पूर्ण

अटल व्योम throtl_qnode_init(काष्ठा throtl_qnode *qn, काष्ठा throtl_grp *tg)
अणु
	INIT_LIST_HEAD(&qn->node);
	bio_list_init(&qn->bios);
	qn->tg = tg;
पूर्ण

/**
 * throtl_qnode_add_bio - add a bio to a throtl_qnode and activate it
 * @bio: bio being added
 * @qn: qnode to add bio to
 * @queued: the service_queue->queued[] list @qn beदीर्घs to
 *
 * Add @bio to @qn and put @qn on @queued अगर it's not alपढ़ोy on.
 * @qn->tg's reference count is bumped when @qn is activated.  See the
 * comment on top of throtl_qnode definition क्रम details.
 */
अटल व्योम throtl_qnode_add_bio(काष्ठा bio *bio, काष्ठा throtl_qnode *qn,
				 काष्ठा list_head *queued)
अणु
	bio_list_add(&qn->bios, bio);
	अगर (list_empty(&qn->node)) अणु
		list_add_tail(&qn->node, queued);
		blkg_get(tg_to_blkg(qn->tg));
	पूर्ण
पूर्ण

/**
 * throtl_peek_queued - peek the first bio on a qnode list
 * @queued: the qnode list to peek
 */
अटल काष्ठा bio *throtl_peek_queued(काष्ठा list_head *queued)
अणु
	काष्ठा throtl_qnode *qn;
	काष्ठा bio *bio;

	अगर (list_empty(queued))
		वापस शून्य;

	qn = list_first_entry(queued, काष्ठा throtl_qnode, node);
	bio = bio_list_peek(&qn->bios);
	WARN_ON_ONCE(!bio);
	वापस bio;
पूर्ण

/**
 * throtl_pop_queued - pop the first bio क्रमm a qnode list
 * @queued: the qnode list to pop a bio from
 * @tg_to_put: optional out argument क्रम throtl_grp to put
 *
 * Pop the first bio from the qnode list @queued.  After popping, the first
 * qnode is हटाओd from @queued अगर empty or moved to the end of @queued so
 * that the popping order is round-robin.
 *
 * When the first qnode is हटाओd, its associated throtl_grp should be put
 * too.  If @tg_to_put is शून्य, this function स्वतःmatically माला_दो it;
 * otherwise, *@tg_to_put is set to the throtl_grp to put and the caller is
 * responsible क्रम putting it.
 */
अटल काष्ठा bio *throtl_pop_queued(काष्ठा list_head *queued,
				     काष्ठा throtl_grp **tg_to_put)
अणु
	काष्ठा throtl_qnode *qn;
	काष्ठा bio *bio;

	अगर (list_empty(queued))
		वापस शून्य;

	qn = list_first_entry(queued, काष्ठा throtl_qnode, node);
	bio = bio_list_pop(&qn->bios);
	WARN_ON_ONCE(!bio);

	अगर (bio_list_empty(&qn->bios)) अणु
		list_del_init(&qn->node);
		अगर (tg_to_put)
			*tg_to_put = qn->tg;
		अन्यथा
			blkg_put(tg_to_blkg(qn->tg));
	पूर्ण अन्यथा अणु
		list_move_tail(&qn->node, queued);
	पूर्ण

	वापस bio;
पूर्ण

/* init a service_queue, assumes the caller zeroed it */
अटल व्योम throtl_service_queue_init(काष्ठा throtl_service_queue *sq)
अणु
	INIT_LIST_HEAD(&sq->queued[0]);
	INIT_LIST_HEAD(&sq->queued[1]);
	sq->pending_tree = RB_ROOT_CACHED;
	समयr_setup(&sq->pending_समयr, throtl_pending_समयr_fn, 0);
पूर्ण

अटल काष्ठा blkg_policy_data *throtl_pd_alloc(gfp_t gfp,
						काष्ठा request_queue *q,
						काष्ठा blkcg *blkcg)
अणु
	काष्ठा throtl_grp *tg;
	पूर्णांक rw;

	tg = kzalloc_node(माप(*tg), gfp, q->node);
	अगर (!tg)
		वापस शून्य;

	अगर (blkg_rwstat_init(&tg->stat_bytes, gfp))
		जाओ err_मुक्त_tg;

	अगर (blkg_rwstat_init(&tg->stat_ios, gfp))
		जाओ err_निकास_stat_bytes;

	throtl_service_queue_init(&tg->service_queue);

	क्रम (rw = READ; rw <= WRITE; rw++) अणु
		throtl_qnode_init(&tg->qnode_on_self[rw], tg);
		throtl_qnode_init(&tg->qnode_on_parent[rw], tg);
	पूर्ण

	RB_CLEAR_NODE(&tg->rb_node);
	tg->bps[READ][LIMIT_MAX] = U64_MAX;
	tg->bps[WRITE][LIMIT_MAX] = U64_MAX;
	tg->iops[READ][LIMIT_MAX] = अच_पूर्णांक_उच्च;
	tg->iops[WRITE][LIMIT_MAX] = अच_पूर्णांक_उच्च;
	tg->bps_conf[READ][LIMIT_MAX] = U64_MAX;
	tg->bps_conf[WRITE][LIMIT_MAX] = U64_MAX;
	tg->iops_conf[READ][LIMIT_MAX] = अच_पूर्णांक_उच्च;
	tg->iops_conf[WRITE][LIMIT_MAX] = अच_पूर्णांक_उच्च;
	/* LIMIT_LOW will have शेष value 0 */

	tg->latency_target = DFL_LATENCY_TARGET;
	tg->latency_target_conf = DFL_LATENCY_TARGET;
	tg->idleसमय_प्रकारhreshold = DFL_IDLE_THRESHOLD;
	tg->idleसमय_प्रकारhreshold_conf = DFL_IDLE_THRESHOLD;

	वापस &tg->pd;

err_निकास_stat_bytes:
	blkg_rwstat_निकास(&tg->stat_bytes);
err_मुक्त_tg:
	kमुक्त(tg);
	वापस शून्य;
पूर्ण

अटल व्योम throtl_pd_init(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा throtl_grp *tg = pd_to_tg(pd);
	काष्ठा blkcg_gq *blkg = tg_to_blkg(tg);
	काष्ठा throtl_data *td = blkg->q->td;
	काष्ठा throtl_service_queue *sq = &tg->service_queue;

	/*
	 * If on the शेष hierarchy, we चयन to properly hierarchical
	 * behavior where limits on a given throtl_grp are applied to the
	 * whole subtree rather than just the group itself.  e.g. If 16M
	 * पढ़ो_bps limit is set on the root group, the whole प्रणाली can't
	 * exceed 16M क्रम the device.
	 *
	 * If not on the शेष hierarchy, the broken flat hierarchy
	 * behavior is retained where all throtl_grps are treated as अगर
	 * they're all separate root groups right below throtl_data.
	 * Limits of a group करोn't पूर्णांकeract with limits of other groups
	 * regardless of the position of the group in the hierarchy.
	 */
	sq->parent_sq = &td->service_queue;
	अगर (cgroup_subsys_on_dfl(io_cgrp_subsys) && blkg->parent)
		sq->parent_sq = &blkg_to_tg(blkg->parent)->service_queue;
	tg->td = td;
पूर्ण

/*
 * Set has_rules[] अगर @tg or any of its parents have limits configured.
 * This करोesn't require walking up to the top of the hierarchy as the
 * parent's has_rules[] is guaranteed to be correct.
 */
अटल व्योम tg_update_has_rules(काष्ठा throtl_grp *tg)
अणु
	काष्ठा throtl_grp *parent_tg = sq_to_tg(tg->service_queue.parent_sq);
	काष्ठा throtl_data *td = tg->td;
	पूर्णांक rw;

	क्रम (rw = READ; rw <= WRITE; rw++)
		tg->has_rules[rw] = (parent_tg && parent_tg->has_rules[rw]) ||
			(td->limit_valid[td->limit_index] &&
			 (tg_bps_limit(tg, rw) != U64_MAX ||
			  tg_iops_limit(tg, rw) != अच_पूर्णांक_उच्च));
पूर्ण

अटल व्योम throtl_pd_online(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा throtl_grp *tg = pd_to_tg(pd);
	/*
	 * We करोn't want new groups to escape the limits of its ancestors.
	 * Update has_rules[] after a new group is brought online.
	 */
	tg_update_has_rules(tg);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_THROTTLING_LOW
अटल व्योम blk_throtl_update_limit_valid(काष्ठा throtl_data *td)
अणु
	काष्ठा cgroup_subsys_state *pos_css;
	काष्ठा blkcg_gq *blkg;
	bool low_valid = false;

	rcu_पढ़ो_lock();
	blkg_क्रम_each_descendant_post(blkg, pos_css, td->queue->root_blkg) अणु
		काष्ठा throtl_grp *tg = blkg_to_tg(blkg);

		अगर (tg->bps[READ][LIMIT_LOW] || tg->bps[WRITE][LIMIT_LOW] ||
		    tg->iops[READ][LIMIT_LOW] || tg->iops[WRITE][LIMIT_LOW]) अणु
			low_valid = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	td->limit_valid[LIMIT_LOW] = low_valid;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम blk_throtl_update_limit_valid(काष्ठा throtl_data *td)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम throtl_upgrade_state(काष्ठा throtl_data *td);
अटल व्योम throtl_pd_offline(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा throtl_grp *tg = pd_to_tg(pd);

	tg->bps[READ][LIMIT_LOW] = 0;
	tg->bps[WRITE][LIMIT_LOW] = 0;
	tg->iops[READ][LIMIT_LOW] = 0;
	tg->iops[WRITE][LIMIT_LOW] = 0;

	blk_throtl_update_limit_valid(tg->td);

	अगर (!tg->td->limit_valid[tg->td->limit_index])
		throtl_upgrade_state(tg->td);
पूर्ण

अटल व्योम throtl_pd_मुक्त(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा throtl_grp *tg = pd_to_tg(pd);

	del_समयr_sync(&tg->service_queue.pending_समयr);
	blkg_rwstat_निकास(&tg->stat_bytes);
	blkg_rwstat_निकास(&tg->stat_ios);
	kमुक्त(tg);
पूर्ण

अटल काष्ठा throtl_grp *
throtl_rb_first(काष्ठा throtl_service_queue *parent_sq)
अणु
	काष्ठा rb_node *n;

	n = rb_first_cached(&parent_sq->pending_tree);
	WARN_ON_ONCE(!n);
	अगर (!n)
		वापस शून्य;
	वापस rb_entry_tg(n);
पूर्ण

अटल व्योम throtl_rb_erase(काष्ठा rb_node *n,
			    काष्ठा throtl_service_queue *parent_sq)
अणु
	rb_erase_cached(n, &parent_sq->pending_tree);
	RB_CLEAR_NODE(n);
	--parent_sq->nr_pending;
पूर्ण

अटल व्योम update_min_dispatch_समय(काष्ठा throtl_service_queue *parent_sq)
अणु
	काष्ठा throtl_grp *tg;

	tg = throtl_rb_first(parent_sq);
	अगर (!tg)
		वापस;

	parent_sq->first_pending_dispसमय = tg->dispसमय;
पूर्ण

अटल व्योम tg_service_queue_add(काष्ठा throtl_grp *tg)
अणु
	काष्ठा throtl_service_queue *parent_sq = tg->service_queue.parent_sq;
	काष्ठा rb_node **node = &parent_sq->pending_tree.rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा throtl_grp *__tg;
	अचिन्हित दीर्घ key = tg->dispसमय;
	bool lefपंचांगost = true;

	जबतक (*node != शून्य) अणु
		parent = *node;
		__tg = rb_entry_tg(parent);

		अगर (समय_beक्रमe(key, __tg->dispसमय))
			node = &parent->rb_left;
		अन्यथा अणु
			node = &parent->rb_right;
			lefपंचांगost = false;
		पूर्ण
	पूर्ण

	rb_link_node(&tg->rb_node, parent, node);
	rb_insert_color_cached(&tg->rb_node, &parent_sq->pending_tree,
			       lefपंचांगost);
पूर्ण

अटल व्योम throtl_enqueue_tg(काष्ठा throtl_grp *tg)
अणु
	अगर (!(tg->flags & THROTL_TG_PENDING)) अणु
		tg_service_queue_add(tg);
		tg->flags |= THROTL_TG_PENDING;
		tg->service_queue.parent_sq->nr_pending++;
	पूर्ण
पूर्ण

अटल व्योम throtl_dequeue_tg(काष्ठा throtl_grp *tg)
अणु
	अगर (tg->flags & THROTL_TG_PENDING) अणु
		throtl_rb_erase(&tg->rb_node, tg->service_queue.parent_sq);
		tg->flags &= ~THROTL_TG_PENDING;
	पूर्ण
पूर्ण

/* Call with queue lock held */
अटल व्योम throtl_schedule_pending_समयr(काष्ठा throtl_service_queue *sq,
					  अचिन्हित दीर्घ expires)
अणु
	अचिन्हित दीर्घ max_expire = jअगरfies + 8 * sq_to_td(sq)->throtl_slice;

	/*
	 * Since we are adjusting the throttle limit dynamically, the sleep
	 * समय calculated according to previous limit might be invalid. It's
	 * possible the cgroup sleep समय is very दीर्घ and no other cgroups
	 * have IO running so notअगरy the limit changes. Make sure the cgroup
	 * करोesn't sleep too दीर्घ to aव्योम the missed notअगरication.
	 */
	अगर (समय_after(expires, max_expire))
		expires = max_expire;
	mod_समयr(&sq->pending_समयr, expires);
	throtl_log(sq, "schedule timer. delay=%lu jiffies=%lu",
		   expires - jअगरfies, jअगरfies);
पूर्ण

/**
 * throtl_schedule_next_dispatch - schedule the next dispatch cycle
 * @sq: the service_queue to schedule dispatch क्रम
 * @क्रमce: क्रमce scheduling
 *
 * Arm @sq->pending_समयr so that the next dispatch cycle starts on the
 * dispatch समय of the first pending child.  Returns %true अगर either समयr
 * is armed or there's no pending child left.  %false अगर the current
 * dispatch winकरोw is still खोलो and the caller should जारी
 * dispatching.
 *
 * If @क्रमce is %true, the dispatch समयr is always scheduled and this
 * function is guaranteed to वापस %true.  This is to be used when the
 * caller can't dispatch itself and needs to invoke pending_समयr
 * unconditionally.  Note that क्रमced scheduling is likely to induce लघु
 * delay beक्रमe dispatch starts even अगर @sq->first_pending_dispसमय is not
 * in the future and thus shouldn't be used in hot paths.
 */
अटल bool throtl_schedule_next_dispatch(काष्ठा throtl_service_queue *sq,
					  bool क्रमce)
अणु
	/* any pending children left? */
	अगर (!sq->nr_pending)
		वापस true;

	update_min_dispatch_समय(sq);

	/* is the next dispatch समय in the future? */
	अगर (क्रमce || समय_after(sq->first_pending_dispसमय, jअगरfies)) अणु
		throtl_schedule_pending_समयr(sq, sq->first_pending_dispसमय);
		वापस true;
	पूर्ण

	/* tell the caller to जारी dispatching */
	वापस false;
पूर्ण

अटल अंतरभूत व्योम throtl_start_new_slice_with_credit(काष्ठा throtl_grp *tg,
		bool rw, अचिन्हित दीर्घ start)
अणु
	tg->bytes_disp[rw] = 0;
	tg->io_disp[rw] = 0;

	/*
	 * Previous slice has expired. We must have trimmed it after last
	 * bio dispatch. That means since start of last slice, we never used
	 * that bandwidth. Do try to make use of that bandwidth जबतक giving
	 * credit.
	 */
	अगर (समय_after_eq(start, tg->slice_start[rw]))
		tg->slice_start[rw] = start;

	tg->slice_end[rw] = jअगरfies + tg->td->throtl_slice;
	throtl_log(&tg->service_queue,
		   "[%c] new slice with credit start=%lu end=%lu jiffies=%lu",
		   rw == READ ? 'R' : 'W', tg->slice_start[rw],
		   tg->slice_end[rw], jअगरfies);
पूर्ण

अटल अंतरभूत व्योम throtl_start_new_slice(काष्ठा throtl_grp *tg, bool rw)
अणु
	tg->bytes_disp[rw] = 0;
	tg->io_disp[rw] = 0;
	tg->slice_start[rw] = jअगरfies;
	tg->slice_end[rw] = jअगरfies + tg->td->throtl_slice;
	throtl_log(&tg->service_queue,
		   "[%c] new slice start=%lu end=%lu jiffies=%lu",
		   rw == READ ? 'R' : 'W', tg->slice_start[rw],
		   tg->slice_end[rw], jअगरfies);
पूर्ण

अटल अंतरभूत व्योम throtl_set_slice_end(काष्ठा throtl_grp *tg, bool rw,
					अचिन्हित दीर्घ jअगरfy_end)
अणु
	tg->slice_end[rw] = roundup(jअगरfy_end, tg->td->throtl_slice);
पूर्ण

अटल अंतरभूत व्योम throtl_extend_slice(काष्ठा throtl_grp *tg, bool rw,
				       अचिन्हित दीर्घ jअगरfy_end)
अणु
	throtl_set_slice_end(tg, rw, jअगरfy_end);
	throtl_log(&tg->service_queue,
		   "[%c] extend slice start=%lu end=%lu jiffies=%lu",
		   rw == READ ? 'R' : 'W', tg->slice_start[rw],
		   tg->slice_end[rw], jअगरfies);
पूर्ण

/* Determine अगर previously allocated or extended slice is complete or not */
अटल bool throtl_slice_used(काष्ठा throtl_grp *tg, bool rw)
अणु
	अगर (समय_in_range(jअगरfies, tg->slice_start[rw], tg->slice_end[rw]))
		वापस false;

	वापस true;
पूर्ण

/* Trim the used slices and adjust slice start accordingly */
अटल अंतरभूत व्योम throtl_trim_slice(काष्ठा throtl_grp *tg, bool rw)
अणु
	अचिन्हित दीर्घ nr_slices, समय_elapsed, io_trim;
	u64 bytes_trim, पंचांगp;

	BUG_ON(समय_beक्रमe(tg->slice_end[rw], tg->slice_start[rw]));

	/*
	 * If bps are unlimited (-1), then समय slice करोn't get
	 * renewed. Don't try to trim the slice अगर slice is used. A new
	 * slice will start when appropriate.
	 */
	अगर (throtl_slice_used(tg, rw))
		वापस;

	/*
	 * A bio has been dispatched. Also adjust slice_end. It might happen
	 * that initially cgroup limit was very low resulting in high
	 * slice_end, but later limit was bumped up and bio was dispatched
	 * sooner, then we need to reduce slice_end. A high bogus slice_end
	 * is bad because it करोes not allow new slice to start.
	 */

	throtl_set_slice_end(tg, rw, jअगरfies + tg->td->throtl_slice);

	समय_elapsed = jअगरfies - tg->slice_start[rw];

	nr_slices = समय_elapsed / tg->td->throtl_slice;

	अगर (!nr_slices)
		वापस;
	पंचांगp = tg_bps_limit(tg, rw) * tg->td->throtl_slice * nr_slices;
	करो_भाग(पंचांगp, HZ);
	bytes_trim = पंचांगp;

	io_trim = (tg_iops_limit(tg, rw) * tg->td->throtl_slice * nr_slices) /
		HZ;

	अगर (!bytes_trim && !io_trim)
		वापस;

	अगर (tg->bytes_disp[rw] >= bytes_trim)
		tg->bytes_disp[rw] -= bytes_trim;
	अन्यथा
		tg->bytes_disp[rw] = 0;

	अगर (tg->io_disp[rw] >= io_trim)
		tg->io_disp[rw] -= io_trim;
	अन्यथा
		tg->io_disp[rw] = 0;

	tg->slice_start[rw] += nr_slices * tg->td->throtl_slice;

	throtl_log(&tg->service_queue,
		   "[%c] trim slice nr=%lu bytes=%llu io=%lu start=%lu end=%lu jiffies=%lu",
		   rw == READ ? 'R' : 'W', nr_slices, bytes_trim, io_trim,
		   tg->slice_start[rw], tg->slice_end[rw], jअगरfies);
पूर्ण

अटल bool tg_with_in_iops_limit(काष्ठा throtl_grp *tg, काष्ठा bio *bio,
				  u32 iops_limit, अचिन्हित दीर्घ *रुको)
अणु
	bool rw = bio_data_dir(bio);
	अचिन्हित पूर्णांक io_allowed;
	अचिन्हित दीर्घ jअगरfy_elapsed, jअगरfy_रुको, jअगरfy_elapsed_rnd;
	u64 पंचांगp;

	अगर (iops_limit == अच_पूर्णांक_उच्च) अणु
		अगर (रुको)
			*रुको = 0;
		वापस true;
	पूर्ण

	jअगरfy_elapsed = jअगरfies - tg->slice_start[rw];

	/* Round up to the next throttle slice, रुको समय must be nonzero */
	jअगरfy_elapsed_rnd = roundup(jअगरfy_elapsed + 1, tg->td->throtl_slice);

	/*
	 * jअगरfy_elapsed_rnd should not be a big value as minimum iops can be
	 * 1 then at max jअगरfy elapsed should be equivalent of 1 second as we
	 * will allow dispatch after 1 second and after that slice should
	 * have been trimmed.
	 */

	पंचांगp = (u64)iops_limit * jअगरfy_elapsed_rnd;
	करो_भाग(पंचांगp, HZ);

	अगर (पंचांगp > अच_पूर्णांक_उच्च)
		io_allowed = अच_पूर्णांक_उच्च;
	अन्यथा
		io_allowed = पंचांगp;

	अगर (tg->io_disp[rw] + 1 <= io_allowed) अणु
		अगर (रुको)
			*रुको = 0;
		वापस true;
	पूर्ण

	/* Calc approx समय to dispatch */
	jअगरfy_रुको = jअगरfy_elapsed_rnd - jअगरfy_elapsed;

	अगर (रुको)
		*रुको = jअगरfy_रुको;
	वापस false;
पूर्ण

अटल bool tg_with_in_bps_limit(काष्ठा throtl_grp *tg, काष्ठा bio *bio,
				 u64 bps_limit, अचिन्हित दीर्घ *रुको)
अणु
	bool rw = bio_data_dir(bio);
	u64 bytes_allowed, extra_bytes, पंचांगp;
	अचिन्हित दीर्घ jअगरfy_elapsed, jअगरfy_रुको, jअगरfy_elapsed_rnd;
	अचिन्हित पूर्णांक bio_size = throtl_bio_data_size(bio);

	अगर (bps_limit == U64_MAX) अणु
		अगर (रुको)
			*रुको = 0;
		वापस true;
	पूर्ण

	jअगरfy_elapsed = jअगरfy_elapsed_rnd = jअगरfies - tg->slice_start[rw];

	/* Slice has just started. Consider one slice पूर्णांकerval */
	अगर (!jअगरfy_elapsed)
		jअगरfy_elapsed_rnd = tg->td->throtl_slice;

	jअगरfy_elapsed_rnd = roundup(jअगरfy_elapsed_rnd, tg->td->throtl_slice);

	पंचांगp = bps_limit * jअगरfy_elapsed_rnd;
	करो_भाग(पंचांगp, HZ);
	bytes_allowed = पंचांगp;

	अगर (tg->bytes_disp[rw] + bio_size <= bytes_allowed) अणु
		अगर (रुको)
			*रुको = 0;
		वापस true;
	पूर्ण

	/* Calc approx समय to dispatch */
	extra_bytes = tg->bytes_disp[rw] + bio_size - bytes_allowed;
	jअगरfy_रुको = भाग64_u64(extra_bytes * HZ, bps_limit);

	अगर (!jअगरfy_रुको)
		jअगरfy_रुको = 1;

	/*
	 * This रुको समय is without taking पूर्णांकo consideration the rounding
	 * up we did. Add that समय also.
	 */
	jअगरfy_रुको = jअगरfy_रुको + (jअगरfy_elapsed_rnd - jअगरfy_elapsed);
	अगर (रुको)
		*रुको = jअगरfy_रुको;
	वापस false;
पूर्ण

/*
 * Returns whether one can dispatch a bio or not. Also वापसs approx number
 * of jअगरfies to रुको beक्रमe this bio is with-in IO rate and can be dispatched
 */
अटल bool tg_may_dispatch(काष्ठा throtl_grp *tg, काष्ठा bio *bio,
			    अचिन्हित दीर्घ *रुको)
अणु
	bool rw = bio_data_dir(bio);
	अचिन्हित दीर्घ bps_रुको = 0, iops_रुको = 0, max_रुको = 0;
	u64 bps_limit = tg_bps_limit(tg, rw);
	u32 iops_limit = tg_iops_limit(tg, rw);

	/*
 	 * Currently whole state machine of group depends on first bio
	 * queued in the group bio list. So one should not be calling
	 * this function with a dअगरferent bio अगर there are other bios
	 * queued.
	 */
	BUG_ON(tg->service_queue.nr_queued[rw] &&
	       bio != throtl_peek_queued(&tg->service_queue.queued[rw]));

	/* If tg->bps = -1, then BW is unlimited */
	अगर (bps_limit == U64_MAX && iops_limit == अच_पूर्णांक_उच्च) अणु
		अगर (रुको)
			*रुको = 0;
		वापस true;
	पूर्ण

	/*
	 * If previous slice expired, start a new one otherwise renew/extend
	 * existing slice to make sure it is at least throtl_slice पूर्णांकerval
	 * दीर्घ since now. New slice is started only क्रम empty throttle group.
	 * If there is queued bio, that means there should be an active
	 * slice and it should be extended instead.
	 */
	अगर (throtl_slice_used(tg, rw) && !(tg->service_queue.nr_queued[rw]))
		throtl_start_new_slice(tg, rw);
	अन्यथा अणु
		अगर (समय_beक्रमe(tg->slice_end[rw],
		    jअगरfies + tg->td->throtl_slice))
			throtl_extend_slice(tg, rw,
				jअगरfies + tg->td->throtl_slice);
	पूर्ण

	अगर (tg_with_in_bps_limit(tg, bio, bps_limit, &bps_रुको) &&
	    tg_with_in_iops_limit(tg, bio, iops_limit, &iops_रुको)) अणु
		अगर (रुको)
			*रुको = 0;
		वापस true;
	पूर्ण

	max_रुको = max(bps_रुको, iops_रुको);

	अगर (रुको)
		*रुको = max_रुको;

	अगर (समय_beक्रमe(tg->slice_end[rw], jअगरfies + max_रुको))
		throtl_extend_slice(tg, rw, jअगरfies + max_रुको);

	वापस false;
पूर्ण

अटल व्योम throtl_अक्षरge_bio(काष्ठा throtl_grp *tg, काष्ठा bio *bio)
अणु
	bool rw = bio_data_dir(bio);
	अचिन्हित पूर्णांक bio_size = throtl_bio_data_size(bio);

	/* Charge the bio to the group */
	tg->bytes_disp[rw] += bio_size;
	tg->io_disp[rw]++;
	tg->last_bytes_disp[rw] += bio_size;
	tg->last_io_disp[rw]++;

	/*
	 * BIO_THROTTLED is used to prevent the same bio to be throttled
	 * more than once as a throttled bio will go through blk-throtl the
	 * second समय when it eventually माला_लो issued.  Set it when a bio
	 * is being अक्षरged to a tg.
	 */
	अगर (!bio_flagged(bio, BIO_THROTTLED))
		bio_set_flag(bio, BIO_THROTTLED);
पूर्ण

/**
 * throtl_add_bio_tg - add a bio to the specअगरied throtl_grp
 * @bio: bio to add
 * @qn: qnode to use
 * @tg: the target throtl_grp
 *
 * Add @bio to @tg's service_queue using @qn.  If @qn is not specअगरied,
 * tg->qnode_on_self[] is used.
 */
अटल व्योम throtl_add_bio_tg(काष्ठा bio *bio, काष्ठा throtl_qnode *qn,
			      काष्ठा throtl_grp *tg)
अणु
	काष्ठा throtl_service_queue *sq = &tg->service_queue;
	bool rw = bio_data_dir(bio);

	अगर (!qn)
		qn = &tg->qnode_on_self[rw];

	/*
	 * If @tg करोesn't currently have any bios queued in the same
	 * direction, queueing @bio can change when @tg should be
	 * dispatched.  Mark that @tg was empty.  This is स्वतःmatically
	 * cleared on the next tg_update_dispसमय().
	 */
	अगर (!sq->nr_queued[rw])
		tg->flags |= THROTL_TG_WAS_EMPTY;

	throtl_qnode_add_bio(bio, qn, &sq->queued[rw]);

	sq->nr_queued[rw]++;
	throtl_enqueue_tg(tg);
पूर्ण

अटल व्योम tg_update_dispसमय(काष्ठा throtl_grp *tg)
अणु
	काष्ठा throtl_service_queue *sq = &tg->service_queue;
	अचिन्हित दीर्घ पढ़ो_रुको = -1, ग_लिखो_रुको = -1, min_रुको = -1, dispसमय;
	काष्ठा bio *bio;

	bio = throtl_peek_queued(&sq->queued[READ]);
	अगर (bio)
		tg_may_dispatch(tg, bio, &पढ़ो_रुको);

	bio = throtl_peek_queued(&sq->queued[WRITE]);
	अगर (bio)
		tg_may_dispatch(tg, bio, &ग_लिखो_रुको);

	min_रुको = min(पढ़ो_रुको, ग_लिखो_रुको);
	dispसमय = jअगरfies + min_रुको;

	/* Update dispatch समय */
	throtl_dequeue_tg(tg);
	tg->dispसमय = dispसमय;
	throtl_enqueue_tg(tg);

	/* see throtl_add_bio_tg() */
	tg->flags &= ~THROTL_TG_WAS_EMPTY;
पूर्ण

अटल व्योम start_parent_slice_with_credit(काष्ठा throtl_grp *child_tg,
					काष्ठा throtl_grp *parent_tg, bool rw)
अणु
	अगर (throtl_slice_used(parent_tg, rw)) अणु
		throtl_start_new_slice_with_credit(parent_tg, rw,
				child_tg->slice_start[rw]);
	पूर्ण

पूर्ण

अटल व्योम tg_dispatch_one_bio(काष्ठा throtl_grp *tg, bool rw)
अणु
	काष्ठा throtl_service_queue *sq = &tg->service_queue;
	काष्ठा throtl_service_queue *parent_sq = sq->parent_sq;
	काष्ठा throtl_grp *parent_tg = sq_to_tg(parent_sq);
	काष्ठा throtl_grp *tg_to_put = शून्य;
	काष्ठा bio *bio;

	/*
	 * @bio is being transferred from @tg to @parent_sq.  Popping a bio
	 * from @tg may put its reference and @parent_sq might end up
	 * getting released prematurely.  Remember the tg to put and put it
	 * after @bio is transferred to @parent_sq.
	 */
	bio = throtl_pop_queued(&sq->queued[rw], &tg_to_put);
	sq->nr_queued[rw]--;

	throtl_अक्षरge_bio(tg, bio);

	/*
	 * If our parent is another tg, we just need to transfer @bio to
	 * the parent using throtl_add_bio_tg().  If our parent is
	 * @td->service_queue, @bio is पढ़ोy to be issued.  Put it on its
	 * bio_lists[] and decrease total number queued.  The caller is
	 * responsible क्रम issuing these bios.
	 */
	अगर (parent_tg) अणु
		throtl_add_bio_tg(bio, &tg->qnode_on_parent[rw], parent_tg);
		start_parent_slice_with_credit(tg, parent_tg, rw);
	पूर्ण अन्यथा अणु
		throtl_qnode_add_bio(bio, &tg->qnode_on_parent[rw],
				     &parent_sq->queued[rw]);
		BUG_ON(tg->td->nr_queued[rw] <= 0);
		tg->td->nr_queued[rw]--;
	पूर्ण

	throtl_trim_slice(tg, rw);

	अगर (tg_to_put)
		blkg_put(tg_to_blkg(tg_to_put));
पूर्ण

अटल पूर्णांक throtl_dispatch_tg(काष्ठा throtl_grp *tg)
अणु
	काष्ठा throtl_service_queue *sq = &tg->service_queue;
	अचिन्हित पूर्णांक nr_पढ़ोs = 0, nr_ग_लिखोs = 0;
	अचिन्हित पूर्णांक max_nr_पढ़ोs = THROTL_GRP_QUANTUM * 3 / 4;
	अचिन्हित पूर्णांक max_nr_ग_लिखोs = THROTL_GRP_QUANTUM - max_nr_पढ़ोs;
	काष्ठा bio *bio;

	/* Try to dispatch 75% READS and 25% WRITES */

	जबतक ((bio = throtl_peek_queued(&sq->queued[READ])) &&
	       tg_may_dispatch(tg, bio, शून्य)) अणु

		tg_dispatch_one_bio(tg, bio_data_dir(bio));
		nr_पढ़ोs++;

		अगर (nr_पढ़ोs >= max_nr_पढ़ोs)
			अवरोध;
	पूर्ण

	जबतक ((bio = throtl_peek_queued(&sq->queued[WRITE])) &&
	       tg_may_dispatch(tg, bio, शून्य)) अणु

		tg_dispatch_one_bio(tg, bio_data_dir(bio));
		nr_ग_लिखोs++;

		अगर (nr_ग_लिखोs >= max_nr_ग_लिखोs)
			अवरोध;
	पूर्ण

	वापस nr_पढ़ोs + nr_ग_लिखोs;
पूर्ण

अटल पूर्णांक throtl_select_dispatch(काष्ठा throtl_service_queue *parent_sq)
अणु
	अचिन्हित पूर्णांक nr_disp = 0;

	जबतक (1) अणु
		काष्ठा throtl_grp *tg;
		काष्ठा throtl_service_queue *sq;

		अगर (!parent_sq->nr_pending)
			अवरोध;

		tg = throtl_rb_first(parent_sq);
		अगर (!tg)
			अवरोध;

		अगर (समय_beक्रमe(jअगरfies, tg->dispसमय))
			अवरोध;

		throtl_dequeue_tg(tg);

		nr_disp += throtl_dispatch_tg(tg);

		sq = &tg->service_queue;
		अगर (sq->nr_queued[0] || sq->nr_queued[1])
			tg_update_dispसमय(tg);

		अगर (nr_disp >= THROTL_QUANTUM)
			अवरोध;
	पूर्ण

	वापस nr_disp;
पूर्ण

अटल bool throtl_can_upgrade(काष्ठा throtl_data *td,
	काष्ठा throtl_grp *this_tg);
/**
 * throtl_pending_समयr_fn - समयr function क्रम service_queue->pending_समयr
 * @t: the pending_समयr member of the throtl_service_queue being serviced
 *
 * This समयr is armed when a child throtl_grp with active bio's become
 * pending and queued on the service_queue's pending_tree and expires when
 * the first child throtl_grp should be dispatched.  This function
 * dispatches bio's from the children throtl_grps to the parent
 * service_queue.
 *
 * If the parent's parent is another throtl_grp, dispatching is propagated
 * by either arming its pending_समयr or repeating dispatch directly.  If
 * the top-level service_tree is reached, throtl_data->dispatch_work is
 * kicked so that the पढ़ोy bio's are issued.
 */
अटल व्योम throtl_pending_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा throtl_service_queue *sq = from_समयr(sq, t, pending_समयr);
	काष्ठा throtl_grp *tg = sq_to_tg(sq);
	काष्ठा throtl_data *td = sq_to_td(sq);
	काष्ठा request_queue *q = td->queue;
	काष्ठा throtl_service_queue *parent_sq;
	bool dispatched;
	पूर्णांक ret;

	spin_lock_irq(&q->queue_lock);
	अगर (throtl_can_upgrade(td, शून्य))
		throtl_upgrade_state(td);

again:
	parent_sq = sq->parent_sq;
	dispatched = false;

	जबतक (true) अणु
		throtl_log(sq, "dispatch nr_queued=%u read=%u write=%u",
			   sq->nr_queued[READ] + sq->nr_queued[WRITE],
			   sq->nr_queued[READ], sq->nr_queued[WRITE]);

		ret = throtl_select_dispatch(sq);
		अगर (ret) अणु
			throtl_log(sq, "bios disp=%u", ret);
			dispatched = true;
		पूर्ण

		अगर (throtl_schedule_next_dispatch(sq, false))
			अवरोध;

		/* this dispatch winकरोws is still खोलो, relax and repeat */
		spin_unlock_irq(&q->queue_lock);
		cpu_relax();
		spin_lock_irq(&q->queue_lock);
	पूर्ण

	अगर (!dispatched)
		जाओ out_unlock;

	अगर (parent_sq) अणु
		/* @parent_sq is another throl_grp, propagate dispatch */
		अगर (tg->flags & THROTL_TG_WAS_EMPTY) अणु
			tg_update_dispसमय(tg);
			अगर (!throtl_schedule_next_dispatch(parent_sq, false)) अणु
				/* winकरोw is alपढ़ोy खोलो, repeat dispatching */
				sq = parent_sq;
				tg = sq_to_tg(sq);
				जाओ again;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* reached the top-level, queue issuing */
		queue_work(kthrotld_workqueue, &td->dispatch_work);
	पूर्ण
out_unlock:
	spin_unlock_irq(&q->queue_lock);
पूर्ण

/**
 * blk_throtl_dispatch_work_fn - work function क्रम throtl_data->dispatch_work
 * @work: work item being executed
 *
 * This function is queued क्रम execution when bios reach the bio_lists[]
 * of throtl_data->service_queue.  Those bios are पढ़ोy and issued by this
 * function.
 */
अटल व्योम blk_throtl_dispatch_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा throtl_data *td = container_of(work, काष्ठा throtl_data,
					      dispatch_work);
	काष्ठा throtl_service_queue *td_sq = &td->service_queue;
	काष्ठा request_queue *q = td->queue;
	काष्ठा bio_list bio_list_on_stack;
	काष्ठा bio *bio;
	काष्ठा blk_plug plug;
	पूर्णांक rw;

	bio_list_init(&bio_list_on_stack);

	spin_lock_irq(&q->queue_lock);
	क्रम (rw = READ; rw <= WRITE; rw++)
		जबतक ((bio = throtl_pop_queued(&td_sq->queued[rw], शून्य)))
			bio_list_add(&bio_list_on_stack, bio);
	spin_unlock_irq(&q->queue_lock);

	अगर (!bio_list_empty(&bio_list_on_stack)) अणु
		blk_start_plug(&plug);
		जबतक ((bio = bio_list_pop(&bio_list_on_stack)))
			submit_bio_noacct(bio);
		blk_finish_plug(&plug);
	पूर्ण
पूर्ण

अटल u64 tg_prfill_conf_u64(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
			      पूर्णांक off)
अणु
	काष्ठा throtl_grp *tg = pd_to_tg(pd);
	u64 v = *(u64 *)((व्योम *)tg + off);

	अगर (v == U64_MAX)
		वापस 0;
	वापस __blkg_prfill_u64(sf, pd, v);
पूर्ण

अटल u64 tg_prfill_conf_uपूर्णांक(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
			       पूर्णांक off)
अणु
	काष्ठा throtl_grp *tg = pd_to_tg(pd);
	अचिन्हित पूर्णांक v = *(अचिन्हित पूर्णांक *)((व्योम *)tg + off);

	अगर (v == अच_पूर्णांक_उच्च)
		वापस 0;
	वापस __blkg_prfill_u64(sf, pd, v);
पूर्ण

अटल पूर्णांक tg_prपूर्णांक_conf_u64(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)), tg_prfill_conf_u64,
			  &blkcg_policy_throtl, seq_cft(sf)->निजी, false);
	वापस 0;
पूर्ण

अटल पूर्णांक tg_prपूर्णांक_conf_uपूर्णांक(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)), tg_prfill_conf_uपूर्णांक,
			  &blkcg_policy_throtl, seq_cft(sf)->निजी, false);
	वापस 0;
पूर्ण

अटल व्योम tg_conf_updated(काष्ठा throtl_grp *tg, bool global)
अणु
	काष्ठा throtl_service_queue *sq = &tg->service_queue;
	काष्ठा cgroup_subsys_state *pos_css;
	काष्ठा blkcg_gq *blkg;

	throtl_log(&tg->service_queue,
		   "limit change rbps=%llu wbps=%llu riops=%u wiops=%u",
		   tg_bps_limit(tg, READ), tg_bps_limit(tg, WRITE),
		   tg_iops_limit(tg, READ), tg_iops_limit(tg, WRITE));

	/*
	 * Update has_rules[] flags क्रम the updated tg's subtree.  A tg is
	 * considered to have rules अगर either the tg itself or any of its
	 * ancestors has rules.  This identअगरies groups without any
	 * restrictions in the whole hierarchy and allows them to bypass
	 * blk-throttle.
	 */
	blkg_क्रम_each_descendant_pre(blkg, pos_css,
			global ? tg->td->queue->root_blkg : tg_to_blkg(tg)) अणु
		काष्ठा throtl_grp *this_tg = blkg_to_tg(blkg);
		काष्ठा throtl_grp *parent_tg;

		tg_update_has_rules(this_tg);
		/* ignore root/second level */
		अगर (!cgroup_subsys_on_dfl(io_cgrp_subsys) || !blkg->parent ||
		    !blkg->parent->parent)
			जारी;
		parent_tg = blkg_to_tg(blkg->parent);
		/*
		 * make sure all children has lower idle समय threshold and
		 * higher latency target
		 */
		this_tg->idleसमय_प्रकारhreshold = min(this_tg->idleसमय_प्रकारhreshold,
				parent_tg->idleसमय_प्रकारhreshold);
		this_tg->latency_target = max(this_tg->latency_target,
				parent_tg->latency_target);
	पूर्ण

	/*
	 * We're already holding queue_lock and know @tg is valid.  Let's
	 * apply the new config directly.
	 *
	 * Restart the slices क्रम both READ and WRITES. It might happen
	 * that a group's limit are dropped suddenly and we don't want to
	 * account recently dispatched IO with new low rate.
	 */
	throtl_start_new_slice(tg, READ);
	throtl_start_new_slice(tg, WRITE);

	अगर (tg->flags & THROTL_TG_PENDING) अणु
		tg_update_dispसमय(tg);
		throtl_schedule_next_dispatch(sq->parent_sq, true);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार tg_set_conf(काष्ठा kernfs_खोलो_file *of,
			   अक्षर *buf, माप_प्रकार nbytes, loff_t off, bool is_u64)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(of_css(of));
	काष्ठा blkg_conf_ctx ctx;
	काष्ठा throtl_grp *tg;
	पूर्णांक ret;
	u64 v;

	ret = blkg_conf_prep(blkcg, &blkcg_policy_throtl, buf, &ctx);
	अगर (ret)
		वापस ret;

	ret = -EINVAL;
	अगर (माला_पूछो(ctx.body, "%llu", &v) != 1)
		जाओ out_finish;
	अगर (!v)
		v = U64_MAX;

	tg = blkg_to_tg(ctx.blkg);

	अगर (is_u64)
		*(u64 *)((व्योम *)tg + of_cft(of)->निजी) = v;
	अन्यथा
		*(अचिन्हित पूर्णांक *)((व्योम *)tg + of_cft(of)->निजी) = v;

	tg_conf_updated(tg, false);
	ret = 0;
out_finish:
	blkg_conf_finish(&ctx);
	वापस ret ?: nbytes;
पूर्ण

अटल sमाप_प्रकार tg_set_conf_u64(काष्ठा kernfs_खोलो_file *of,
			       अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	वापस tg_set_conf(of, buf, nbytes, off, true);
पूर्ण

अटल sमाप_प्रकार tg_set_conf_uपूर्णांक(काष्ठा kernfs_खोलो_file *of,
				अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	वापस tg_set_conf(of, buf, nbytes, off, false);
पूर्ण

अटल पूर्णांक tg_prपूर्णांक_rwstat(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)),
			  blkg_prfill_rwstat, &blkcg_policy_throtl,
			  seq_cft(sf)->निजी, true);
	वापस 0;
पूर्ण

अटल u64 tg_prfill_rwstat_recursive(काष्ठा seq_file *sf,
				      काष्ठा blkg_policy_data *pd, पूर्णांक off)
अणु
	काष्ठा blkg_rwstat_sample sum;

	blkg_rwstat_recursive_sum(pd_to_blkg(pd), &blkcg_policy_throtl, off,
				  &sum);
	वापस __blkg_prfill_rwstat(sf, pd, &sum);
पूर्ण

अटल पूर्णांक tg_prपूर्णांक_rwstat_recursive(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)),
			  tg_prfill_rwstat_recursive, &blkcg_policy_throtl,
			  seq_cft(sf)->निजी, true);
	वापस 0;
पूर्ण

अटल काष्ठा cftype throtl_legacy_files[] = अणु
	अणु
		.name = "throttle.read_bps_device",
		.निजी = दुरत्व(काष्ठा throtl_grp, bps[READ][LIMIT_MAX]),
		.seq_show = tg_prपूर्णांक_conf_u64,
		.ग_लिखो = tg_set_conf_u64,
	पूर्ण,
	अणु
		.name = "throttle.write_bps_device",
		.निजी = दुरत्व(काष्ठा throtl_grp, bps[WRITE][LIMIT_MAX]),
		.seq_show = tg_prपूर्णांक_conf_u64,
		.ग_लिखो = tg_set_conf_u64,
	पूर्ण,
	अणु
		.name = "throttle.read_iops_device",
		.निजी = दुरत्व(काष्ठा throtl_grp, iops[READ][LIMIT_MAX]),
		.seq_show = tg_prपूर्णांक_conf_uपूर्णांक,
		.ग_लिखो = tg_set_conf_uपूर्णांक,
	पूर्ण,
	अणु
		.name = "throttle.write_iops_device",
		.निजी = दुरत्व(काष्ठा throtl_grp, iops[WRITE][LIMIT_MAX]),
		.seq_show = tg_prपूर्णांक_conf_uपूर्णांक,
		.ग_लिखो = tg_set_conf_uपूर्णांक,
	पूर्ण,
	अणु
		.name = "throttle.io_service_bytes",
		.निजी = दुरत्व(काष्ठा throtl_grp, stat_bytes),
		.seq_show = tg_prपूर्णांक_rwstat,
	पूर्ण,
	अणु
		.name = "throttle.io_service_bytes_recursive",
		.निजी = दुरत्व(काष्ठा throtl_grp, stat_bytes),
		.seq_show = tg_prपूर्णांक_rwstat_recursive,
	पूर्ण,
	अणु
		.name = "throttle.io_serviced",
		.निजी = दुरत्व(काष्ठा throtl_grp, stat_ios),
		.seq_show = tg_prपूर्णांक_rwstat,
	पूर्ण,
	अणु
		.name = "throttle.io_serviced_recursive",
		.निजी = दुरत्व(काष्ठा throtl_grp, stat_ios),
		.seq_show = tg_prपूर्णांक_rwstat_recursive,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

अटल u64 tg_prfill_limit(काष्ठा seq_file *sf, काष्ठा blkg_policy_data *pd,
			 पूर्णांक off)
अणु
	काष्ठा throtl_grp *tg = pd_to_tg(pd);
	स्थिर अक्षर *dname = blkg_dev_name(pd->blkg);
	अक्षर bufs[4][21] = अणु "max", "max", "max", "max" पूर्ण;
	u64 bps_dft;
	अचिन्हित पूर्णांक iops_dft;
	अक्षर idle_समय[26] = "";
	अक्षर latency_समय[26] = "";

	अगर (!dname)
		वापस 0;

	अगर (off == LIMIT_LOW) अणु
		bps_dft = 0;
		iops_dft = 0;
	पूर्ण अन्यथा अणु
		bps_dft = U64_MAX;
		iops_dft = अच_पूर्णांक_उच्च;
	पूर्ण

	अगर (tg->bps_conf[READ][off] == bps_dft &&
	    tg->bps_conf[WRITE][off] == bps_dft &&
	    tg->iops_conf[READ][off] == iops_dft &&
	    tg->iops_conf[WRITE][off] == iops_dft &&
	    (off != LIMIT_LOW ||
	     (tg->idleसमय_प्रकारhreshold_conf == DFL_IDLE_THRESHOLD &&
	      tg->latency_target_conf == DFL_LATENCY_TARGET)))
		वापस 0;

	अगर (tg->bps_conf[READ][off] != U64_MAX)
		snम_लिखो(bufs[0], माप(bufs[0]), "%llu",
			tg->bps_conf[READ][off]);
	अगर (tg->bps_conf[WRITE][off] != U64_MAX)
		snम_लिखो(bufs[1], माप(bufs[1]), "%llu",
			tg->bps_conf[WRITE][off]);
	अगर (tg->iops_conf[READ][off] != अच_पूर्णांक_उच्च)
		snम_लिखो(bufs[2], माप(bufs[2]), "%u",
			tg->iops_conf[READ][off]);
	अगर (tg->iops_conf[WRITE][off] != अच_पूर्णांक_उच्च)
		snम_लिखो(bufs[3], माप(bufs[3]), "%u",
			tg->iops_conf[WRITE][off]);
	अगर (off == LIMIT_LOW) अणु
		अगर (tg->idleसमय_प्रकारhreshold_conf == अच_दीर्घ_उच्च)
			म_नकल(idle_समय, " idle=max");
		अन्यथा
			snम_लिखो(idle_समय, माप(idle_समय), " idle=%lu",
				tg->idleसमय_प्रकारhreshold_conf);

		अगर (tg->latency_target_conf == अच_दीर्घ_उच्च)
			म_नकल(latency_समय, " latency=max");
		अन्यथा
			snम_लिखो(latency_समय, माप(latency_समय),
				" latency=%lu", tg->latency_target_conf);
	पूर्ण

	seq_म_लिखो(sf, "%s rbps=%s wbps=%s riops=%s wiops=%s%s%s\n",
		   dname, bufs[0], bufs[1], bufs[2], bufs[3], idle_समय,
		   latency_समय);
	वापस 0;
पूर्ण

अटल पूर्णांक tg_prपूर्णांक_limit(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)), tg_prfill_limit,
			  &blkcg_policy_throtl, seq_cft(sf)->निजी, false);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार tg_set_limit(काष्ठा kernfs_खोलो_file *of,
			  अक्षर *buf, माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(of_css(of));
	काष्ठा blkg_conf_ctx ctx;
	काष्ठा throtl_grp *tg;
	u64 v[4];
	अचिन्हित दीर्घ idle_समय;
	अचिन्हित दीर्घ latency_समय;
	पूर्णांक ret;
	पूर्णांक index = of_cft(of)->निजी;

	ret = blkg_conf_prep(blkcg, &blkcg_policy_throtl, buf, &ctx);
	अगर (ret)
		वापस ret;

	tg = blkg_to_tg(ctx.blkg);

	v[0] = tg->bps_conf[READ][index];
	v[1] = tg->bps_conf[WRITE][index];
	v[2] = tg->iops_conf[READ][index];
	v[3] = tg->iops_conf[WRITE][index];

	idle_समय = tg->idleसमय_प्रकारhreshold_conf;
	latency_समय = tg->latency_target_conf;
	जबतक (true) अणु
		अक्षर tok[27];	/* wiops=18446744073709551616 */
		अक्षर *p;
		u64 val = U64_MAX;
		पूर्णांक len;

		अगर (माला_पूछो(ctx.body, "%26s%n", tok, &len) != 1)
			अवरोध;
		अगर (tok[0] == '\0')
			अवरोध;
		ctx.body += len;

		ret = -EINVAL;
		p = tok;
		strsep(&p, "=");
		अगर (!p || (माला_पूछो(p, "%llu", &val) != 1 && म_भेद(p, "max")))
			जाओ out_finish;

		ret = -दुस्फल;
		अगर (!val)
			जाओ out_finish;

		ret = -EINVAL;
		अगर (!म_भेद(tok, "rbps") && val > 1)
			v[0] = val;
		अन्यथा अगर (!म_भेद(tok, "wbps") && val > 1)
			v[1] = val;
		अन्यथा अगर (!म_भेद(tok, "riops") && val > 1)
			v[2] = min_t(u64, val, अच_पूर्णांक_उच्च);
		अन्यथा अगर (!म_भेद(tok, "wiops") && val > 1)
			v[3] = min_t(u64, val, अच_पूर्णांक_उच्च);
		अन्यथा अगर (off == LIMIT_LOW && !म_भेद(tok, "idle"))
			idle_समय = val;
		अन्यथा अगर (off == LIMIT_LOW && !म_भेद(tok, "latency"))
			latency_समय = val;
		अन्यथा
			जाओ out_finish;
	पूर्ण

	tg->bps_conf[READ][index] = v[0];
	tg->bps_conf[WRITE][index] = v[1];
	tg->iops_conf[READ][index] = v[2];
	tg->iops_conf[WRITE][index] = v[3];

	अगर (index == LIMIT_MAX) अणु
		tg->bps[READ][index] = v[0];
		tg->bps[WRITE][index] = v[1];
		tg->iops[READ][index] = v[2];
		tg->iops[WRITE][index] = v[3];
	पूर्ण
	tg->bps[READ][LIMIT_LOW] = min(tg->bps_conf[READ][LIMIT_LOW],
		tg->bps_conf[READ][LIMIT_MAX]);
	tg->bps[WRITE][LIMIT_LOW] = min(tg->bps_conf[WRITE][LIMIT_LOW],
		tg->bps_conf[WRITE][LIMIT_MAX]);
	tg->iops[READ][LIMIT_LOW] = min(tg->iops_conf[READ][LIMIT_LOW],
		tg->iops_conf[READ][LIMIT_MAX]);
	tg->iops[WRITE][LIMIT_LOW] = min(tg->iops_conf[WRITE][LIMIT_LOW],
		tg->iops_conf[WRITE][LIMIT_MAX]);
	tg->idleसमय_प्रकारhreshold_conf = idle_समय;
	tg->latency_target_conf = latency_समय;

	/* क्रमce user to configure all settings क्रम low limit  */
	अगर (!(tg->bps[READ][LIMIT_LOW] || tg->iops[READ][LIMIT_LOW] ||
	      tg->bps[WRITE][LIMIT_LOW] || tg->iops[WRITE][LIMIT_LOW]) ||
	    tg->idleसमय_प्रकारhreshold_conf == DFL_IDLE_THRESHOLD ||
	    tg->latency_target_conf == DFL_LATENCY_TARGET) अणु
		tg->bps[READ][LIMIT_LOW] = 0;
		tg->bps[WRITE][LIMIT_LOW] = 0;
		tg->iops[READ][LIMIT_LOW] = 0;
		tg->iops[WRITE][LIMIT_LOW] = 0;
		tg->idleसमय_प्रकारhreshold = DFL_IDLE_THRESHOLD;
		tg->latency_target = DFL_LATENCY_TARGET;
	पूर्ण अन्यथा अगर (index == LIMIT_LOW) अणु
		tg->idleसमय_प्रकारhreshold = tg->idleसमय_प्रकारhreshold_conf;
		tg->latency_target = tg->latency_target_conf;
	पूर्ण

	blk_throtl_update_limit_valid(tg->td);
	अगर (tg->td->limit_valid[LIMIT_LOW]) अणु
		अगर (index == LIMIT_LOW)
			tg->td->limit_index = LIMIT_LOW;
	पूर्ण अन्यथा
		tg->td->limit_index = LIMIT_MAX;
	tg_conf_updated(tg, index == LIMIT_LOW &&
		tg->td->limit_valid[LIMIT_LOW]);
	ret = 0;
out_finish:
	blkg_conf_finish(&ctx);
	वापस ret ?: nbytes;
पूर्ण

अटल काष्ठा cftype throtl_files[] = अणु
#अगर_घोषित CONFIG_BLK_DEV_THROTTLING_LOW
	अणु
		.name = "low",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = tg_prपूर्णांक_limit,
		.ग_लिखो = tg_set_limit,
		.निजी = LIMIT_LOW,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.name = "max",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = tg_prपूर्णांक_limit,
		.ग_लिखो = tg_set_limit,
		.निजी = LIMIT_MAX,
	पूर्ण,
	अणु पूर्ण	/* terminate */
पूर्ण;

अटल व्योम throtl_shutकरोwn_wq(काष्ठा request_queue *q)
अणु
	काष्ठा throtl_data *td = q->td;

	cancel_work_sync(&td->dispatch_work);
पूर्ण

अटल काष्ठा blkcg_policy blkcg_policy_throtl = अणु
	.dfl_cftypes		= throtl_files,
	.legacy_cftypes		= throtl_legacy_files,

	.pd_alloc_fn		= throtl_pd_alloc,
	.pd_init_fn		= throtl_pd_init,
	.pd_online_fn		= throtl_pd_online,
	.pd_offline_fn		= throtl_pd_offline,
	.pd_मुक्त_fn		= throtl_pd_मुक्त,
पूर्ण;

अटल अचिन्हित दीर्घ __tg_last_low_overflow_समय(काष्ठा throtl_grp *tg)
अणु
	अचिन्हित दीर्घ rसमय = jअगरfies, wसमय = jअगरfies;

	अगर (tg->bps[READ][LIMIT_LOW] || tg->iops[READ][LIMIT_LOW])
		rसमय = tg->last_low_overflow_समय[READ];
	अगर (tg->bps[WRITE][LIMIT_LOW] || tg->iops[WRITE][LIMIT_LOW])
		wसमय = tg->last_low_overflow_समय[WRITE];
	वापस min(rसमय, wसमय);
पूर्ण

/* tg should not be an पूर्णांकermediate node */
अटल अचिन्हित दीर्घ tg_last_low_overflow_समय(काष्ठा throtl_grp *tg)
अणु
	काष्ठा throtl_service_queue *parent_sq;
	काष्ठा throtl_grp *parent = tg;
	अचिन्हित दीर्घ ret = __tg_last_low_overflow_समय(tg);

	जबतक (true) अणु
		parent_sq = parent->service_queue.parent_sq;
		parent = sq_to_tg(parent_sq);
		अगर (!parent)
			अवरोध;

		/*
		 * The parent करोesn't have low limit, it always reaches low
		 * limit. Its overflow समय is useless क्रम children
		 */
		अगर (!parent->bps[READ][LIMIT_LOW] &&
		    !parent->iops[READ][LIMIT_LOW] &&
		    !parent->bps[WRITE][LIMIT_LOW] &&
		    !parent->iops[WRITE][LIMIT_LOW])
			जारी;
		अगर (समय_after(__tg_last_low_overflow_समय(parent), ret))
			ret = __tg_last_low_overflow_समय(parent);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool throtl_tg_is_idle(काष्ठा throtl_grp *tg)
अणु
	/*
	 * cgroup is idle अगर:
	 * - single idle is too दीर्घ, दीर्घer than a fixed value (in हाल user
	 *   configure a too big threshold) or 4 बार of idleसमय threshold
	 * - average think समय is more than threshold
	 * - IO latency is largely below threshold
	 */
	अचिन्हित दीर्घ समय;
	bool ret;

	समय = min_t(अचिन्हित दीर्घ, MAX_IDLE_TIME, 4 * tg->idleसमय_प्रकारhreshold);
	ret = tg->latency_target == DFL_LATENCY_TARGET ||
	      tg->idleसमय_प्रकारhreshold == DFL_IDLE_THRESHOLD ||
	      (kसमय_get_ns() >> 10) - tg->last_finish_समय > समय ||
	      tg->avg_idleसमय > tg->idleसमय_प्रकारhreshold ||
	      (tg->latency_target && tg->bio_cnt &&
		tg->bad_bio_cnt * 5 < tg->bio_cnt);
	throtl_log(&tg->service_queue,
		"avg_idle=%ld, idle_threshold=%ld, bad_bio=%d, total_bio=%d, is_idle=%d, scale=%d",
		tg->avg_idleसमय, tg->idleसमय_प्रकारhreshold, tg->bad_bio_cnt,
		tg->bio_cnt, ret, tg->td->scale);
	वापस ret;
पूर्ण

अटल bool throtl_tg_can_upgrade(काष्ठा throtl_grp *tg)
अणु
	काष्ठा throtl_service_queue *sq = &tg->service_queue;
	bool पढ़ो_limit, ग_लिखो_limit;

	/*
	 * अगर cgroup reaches low limit (अगर low limit is 0, the cgroup always
	 * reaches), it's ok to upgrade to next limit
	 */
	पढ़ो_limit = tg->bps[READ][LIMIT_LOW] || tg->iops[READ][LIMIT_LOW];
	ग_लिखो_limit = tg->bps[WRITE][LIMIT_LOW] || tg->iops[WRITE][LIMIT_LOW];
	अगर (!पढ़ो_limit && !ग_लिखो_limit)
		वापस true;
	अगर (पढ़ो_limit && sq->nr_queued[READ] &&
	    (!ग_लिखो_limit || sq->nr_queued[WRITE]))
		वापस true;
	अगर (ग_लिखो_limit && sq->nr_queued[WRITE] &&
	    (!पढ़ो_limit || sq->nr_queued[READ]))
		वापस true;

	अगर (समय_after_eq(jअगरfies,
		tg_last_low_overflow_समय(tg) + tg->td->throtl_slice) &&
	    throtl_tg_is_idle(tg))
		वापस true;
	वापस false;
पूर्ण

अटल bool throtl_hierarchy_can_upgrade(काष्ठा throtl_grp *tg)
अणु
	जबतक (true) अणु
		अगर (throtl_tg_can_upgrade(tg))
			वापस true;
		tg = sq_to_tg(tg->service_queue.parent_sq);
		अगर (!tg || !tg_to_blkg(tg)->parent)
			वापस false;
	पूर्ण
	वापस false;
पूर्ण

अटल bool throtl_can_upgrade(काष्ठा throtl_data *td,
	काष्ठा throtl_grp *this_tg)
अणु
	काष्ठा cgroup_subsys_state *pos_css;
	काष्ठा blkcg_gq *blkg;

	अगर (td->limit_index != LIMIT_LOW)
		वापस false;

	अगर (समय_beक्रमe(jअगरfies, td->low_करोwngrade_समय + td->throtl_slice))
		वापस false;

	rcu_पढ़ो_lock();
	blkg_क्रम_each_descendant_post(blkg, pos_css, td->queue->root_blkg) अणु
		काष्ठा throtl_grp *tg = blkg_to_tg(blkg);

		अगर (tg == this_tg)
			जारी;
		अगर (!list_empty(&tg_to_blkg(tg)->blkcg->css.children))
			जारी;
		अगर (!throtl_hierarchy_can_upgrade(tg)) अणु
			rcu_पढ़ो_unlock();
			वापस false;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस true;
पूर्ण

अटल व्योम throtl_upgrade_check(काष्ठा throtl_grp *tg)
अणु
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (tg->td->limit_index != LIMIT_LOW)
		वापस;

	अगर (समय_after(tg->last_check_समय + tg->td->throtl_slice, now))
		वापस;

	tg->last_check_समय = now;

	अगर (!समय_after_eq(now,
	     __tg_last_low_overflow_समय(tg) + tg->td->throtl_slice))
		वापस;

	अगर (throtl_can_upgrade(tg->td, शून्य))
		throtl_upgrade_state(tg->td);
पूर्ण

अटल व्योम throtl_upgrade_state(काष्ठा throtl_data *td)
अणु
	काष्ठा cgroup_subsys_state *pos_css;
	काष्ठा blkcg_gq *blkg;

	throtl_log(&td->service_queue, "upgrade to max");
	td->limit_index = LIMIT_MAX;
	td->low_upgrade_समय = jअगरfies;
	td->scale = 0;
	rcu_पढ़ो_lock();
	blkg_क्रम_each_descendant_post(blkg, pos_css, td->queue->root_blkg) अणु
		काष्ठा throtl_grp *tg = blkg_to_tg(blkg);
		काष्ठा throtl_service_queue *sq = &tg->service_queue;

		tg->dispसमय = jअगरfies - 1;
		throtl_select_dispatch(sq);
		throtl_schedule_next_dispatch(sq, true);
	पूर्ण
	rcu_पढ़ो_unlock();
	throtl_select_dispatch(&td->service_queue);
	throtl_schedule_next_dispatch(&td->service_queue, true);
	queue_work(kthrotld_workqueue, &td->dispatch_work);
पूर्ण

अटल व्योम throtl_करोwngrade_state(काष्ठा throtl_data *td)
अणु
	td->scale /= 2;

	throtl_log(&td->service_queue, "downgrade, scale %d", td->scale);
	अगर (td->scale) अणु
		td->low_upgrade_समय = jअगरfies - td->scale * td->throtl_slice;
		वापस;
	पूर्ण

	td->limit_index = LIMIT_LOW;
	td->low_करोwngrade_समय = jअगरfies;
पूर्ण

अटल bool throtl_tg_can_करोwngrade(काष्ठा throtl_grp *tg)
अणु
	काष्ठा throtl_data *td = tg->td;
	अचिन्हित दीर्घ now = jअगरfies;

	/*
	 * If cgroup is below low limit, consider करोwngrade and throttle other
	 * cgroups
	 */
	अगर (समय_after_eq(now, td->low_upgrade_समय + td->throtl_slice) &&
	    समय_after_eq(now, tg_last_low_overflow_समय(tg) +
					td->throtl_slice) &&
	    (!throtl_tg_is_idle(tg) ||
	     !list_empty(&tg_to_blkg(tg)->blkcg->css.children)))
		वापस true;
	वापस false;
पूर्ण

अटल bool throtl_hierarchy_can_करोwngrade(काष्ठा throtl_grp *tg)
अणु
	जबतक (true) अणु
		अगर (!throtl_tg_can_करोwngrade(tg))
			वापस false;
		tg = sq_to_tg(tg->service_queue.parent_sq);
		अगर (!tg || !tg_to_blkg(tg)->parent)
			अवरोध;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम throtl_करोwngrade_check(काष्ठा throtl_grp *tg)
अणु
	uपूर्णांक64_t bps;
	अचिन्हित पूर्णांक iops;
	अचिन्हित दीर्घ elapsed_समय;
	अचिन्हित दीर्घ now = jअगरfies;

	अगर (tg->td->limit_index != LIMIT_MAX ||
	    !tg->td->limit_valid[LIMIT_LOW])
		वापस;
	अगर (!list_empty(&tg_to_blkg(tg)->blkcg->css.children))
		वापस;
	अगर (समय_after(tg->last_check_समय + tg->td->throtl_slice, now))
		वापस;

	elapsed_समय = now - tg->last_check_समय;
	tg->last_check_समय = now;

	अगर (समय_beक्रमe(now, tg_last_low_overflow_समय(tg) +
			tg->td->throtl_slice))
		वापस;

	अगर (tg->bps[READ][LIMIT_LOW]) अणु
		bps = tg->last_bytes_disp[READ] * HZ;
		करो_भाग(bps, elapsed_समय);
		अगर (bps >= tg->bps[READ][LIMIT_LOW])
			tg->last_low_overflow_समय[READ] = now;
	पूर्ण

	अगर (tg->bps[WRITE][LIMIT_LOW]) अणु
		bps = tg->last_bytes_disp[WRITE] * HZ;
		करो_भाग(bps, elapsed_समय);
		अगर (bps >= tg->bps[WRITE][LIMIT_LOW])
			tg->last_low_overflow_समय[WRITE] = now;
	पूर्ण

	अगर (tg->iops[READ][LIMIT_LOW]) अणु
		iops = tg->last_io_disp[READ] * HZ / elapsed_समय;
		अगर (iops >= tg->iops[READ][LIMIT_LOW])
			tg->last_low_overflow_समय[READ] = now;
	पूर्ण

	अगर (tg->iops[WRITE][LIMIT_LOW]) अणु
		iops = tg->last_io_disp[WRITE] * HZ / elapsed_समय;
		अगर (iops >= tg->iops[WRITE][LIMIT_LOW])
			tg->last_low_overflow_समय[WRITE] = now;
	पूर्ण

	/*
	 * If cgroup is below low limit, consider करोwngrade and throttle other
	 * cgroups
	 */
	अगर (throtl_hierarchy_can_करोwngrade(tg))
		throtl_करोwngrade_state(tg->td);

	tg->last_bytes_disp[READ] = 0;
	tg->last_bytes_disp[WRITE] = 0;
	tg->last_io_disp[READ] = 0;
	tg->last_io_disp[WRITE] = 0;
पूर्ण

अटल व्योम blk_throtl_update_idleसमय(काष्ठा throtl_grp *tg)
अणु
	अचिन्हित दीर्घ now;
	अचिन्हित दीर्घ last_finish_समय = tg->last_finish_समय;

	अगर (last_finish_समय == 0)
		वापस;

	now = kसमय_get_ns() >> 10;
	अगर (now <= last_finish_समय ||
	    last_finish_समय == tg->checked_last_finish_समय)
		वापस;

	tg->avg_idleसमय = (tg->avg_idleसमय * 7 + now - last_finish_समय) >> 3;
	tg->checked_last_finish_समय = last_finish_समय;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_THROTTLING_LOW
अटल व्योम throtl_update_latency_buckets(काष्ठा throtl_data *td)
अणु
	काष्ठा avg_latency_bucket avg_latency[2][LATENCY_BUCKET_SIZE];
	पूर्णांक i, cpu, rw;
	अचिन्हित दीर्घ last_latency[2] = अणु 0 पूर्ण;
	अचिन्हित दीर्घ latency[2];

	अगर (!blk_queue_nonrot(td->queue) || !td->limit_valid[LIMIT_LOW])
		वापस;
	अगर (समय_beक्रमe(jअगरfies, td->last_calculate_समय + HZ))
		वापस;
	td->last_calculate_समय = jअगरfies;

	स_रखो(avg_latency, 0, माप(avg_latency));
	क्रम (rw = READ; rw <= WRITE; rw++) अणु
		क्रम (i = 0; i < LATENCY_BUCKET_SIZE; i++) अणु
			काष्ठा latency_bucket *पंचांगp = &td->पंचांगp_buckets[rw][i];

			क्रम_each_possible_cpu(cpu) अणु
				काष्ठा latency_bucket *bucket;

				/* this isn't race मुक्त, but ok in practice */
				bucket = per_cpu_ptr(td->latency_buckets[rw],
					cpu);
				पंचांगp->total_latency += bucket[i].total_latency;
				पंचांगp->samples += bucket[i].samples;
				bucket[i].total_latency = 0;
				bucket[i].samples = 0;
			पूर्ण

			अगर (पंचांगp->samples >= 32) अणु
				पूर्णांक samples = पंचांगp->samples;

				latency[rw] = पंचांगp->total_latency;

				पंचांगp->total_latency = 0;
				पंचांगp->samples = 0;
				latency[rw] /= samples;
				अगर (latency[rw] == 0)
					जारी;
				avg_latency[rw][i].latency = latency[rw];
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (rw = READ; rw <= WRITE; rw++) अणु
		क्रम (i = 0; i < LATENCY_BUCKET_SIZE; i++) अणु
			अगर (!avg_latency[rw][i].latency) अणु
				अगर (td->avg_buckets[rw][i].latency < last_latency[rw])
					td->avg_buckets[rw][i].latency =
						last_latency[rw];
				जारी;
			पूर्ण

			अगर (!td->avg_buckets[rw][i].valid)
				latency[rw] = avg_latency[rw][i].latency;
			अन्यथा
				latency[rw] = (td->avg_buckets[rw][i].latency * 7 +
					avg_latency[rw][i].latency) >> 3;

			td->avg_buckets[rw][i].latency = max(latency[rw],
				last_latency[rw]);
			td->avg_buckets[rw][i].valid = true;
			last_latency[rw] = td->avg_buckets[rw][i].latency;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < LATENCY_BUCKET_SIZE; i++)
		throtl_log(&td->service_queue,
			"Latency bucket %d: read latency=%ld, read valid=%d, "
			"write latency=%ld, write valid=%d", i,
			td->avg_buckets[READ][i].latency,
			td->avg_buckets[READ][i].valid,
			td->avg_buckets[WRITE][i].latency,
			td->avg_buckets[WRITE][i].valid);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम throtl_update_latency_buckets(काष्ठा throtl_data *td)
अणु
पूर्ण
#पूर्ण_अगर

bool blk_throtl_bio(काष्ठा bio *bio)
अणु
	काष्ठा request_queue *q = bio->bi_bdev->bd_disk->queue;
	काष्ठा blkcg_gq *blkg = bio->bi_blkg;
	काष्ठा throtl_qnode *qn = शून्य;
	काष्ठा throtl_grp *tg = blkg_to_tg(blkg);
	काष्ठा throtl_service_queue *sq;
	bool rw = bio_data_dir(bio);
	bool throttled = false;
	काष्ठा throtl_data *td = tg->td;

	rcu_पढ़ो_lock();

	/* see throtl_अक्षरge_bio() */
	अगर (bio_flagged(bio, BIO_THROTTLED))
		जाओ out;

	अगर (!cgroup_subsys_on_dfl(io_cgrp_subsys)) अणु
		blkg_rwstat_add(&tg->stat_bytes, bio->bi_opf,
				bio->bi_iter.bi_size);
		blkg_rwstat_add(&tg->stat_ios, bio->bi_opf, 1);
	पूर्ण

	अगर (!tg->has_rules[rw])
		जाओ out;

	spin_lock_irq(&q->queue_lock);

	throtl_update_latency_buckets(td);

	blk_throtl_update_idleसमय(tg);

	sq = &tg->service_queue;

again:
	जबतक (true) अणु
		अगर (tg->last_low_overflow_समय[rw] == 0)
			tg->last_low_overflow_समय[rw] = jअगरfies;
		throtl_करोwngrade_check(tg);
		throtl_upgrade_check(tg);
		/* throtl is FIFO - अगर bios are alपढ़ोy queued, should queue */
		अगर (sq->nr_queued[rw])
			अवरोध;

		/* अगर above limits, अवरोध to queue */
		अगर (!tg_may_dispatch(tg, bio, शून्य)) अणु
			tg->last_low_overflow_समय[rw] = jअगरfies;
			अगर (throtl_can_upgrade(td, tg)) अणु
				throtl_upgrade_state(td);
				जाओ again;
			पूर्ण
			अवरोध;
		पूर्ण

		/* within limits, let's अक्षरge and dispatch directly */
		throtl_अक्षरge_bio(tg, bio);

		/*
		 * We need to trim slice even when bios are not being queued
		 * otherwise it might happen that a bio is not queued क्रम
		 * a दीर्घ समय and slice keeps on extending and trim is not
		 * called क्रम a दीर्घ समय. Now अगर limits are reduced suddenly
		 * we take पूर्णांकo account all the IO dispatched so far at new
		 * low rate and * newly queued IO माला_लो a really दीर्घ dispatch
		 * समय.
		 *
		 * So keep on trimming slice even अगर bio is not queued.
		 */
		throtl_trim_slice(tg, rw);

		/*
		 * @bio passed through this layer without being throttled.
		 * Climb up the ladder.  If we're alपढ़ोy at the top, it
		 * can be executed directly.
		 */
		qn = &tg->qnode_on_parent[rw];
		sq = sq->parent_sq;
		tg = sq_to_tg(sq);
		अगर (!tg)
			जाओ out_unlock;
	पूर्ण

	/* out-of-limit, queue to @tg */
	throtl_log(sq, "[%c] bio. bdisp=%llu sz=%u bps=%llu iodisp=%u iops=%u queued=%d/%d",
		   rw == READ ? 'R' : 'W',
		   tg->bytes_disp[rw], bio->bi_iter.bi_size,
		   tg_bps_limit(tg, rw),
		   tg->io_disp[rw], tg_iops_limit(tg, rw),
		   sq->nr_queued[READ], sq->nr_queued[WRITE]);

	tg->last_low_overflow_समय[rw] = jअगरfies;

	td->nr_queued[rw]++;
	throtl_add_bio_tg(bio, qn, tg);
	throttled = true;

	/*
	 * Update @tg's dispatch समय and क्रमce schedule dispatch अगर @tg
	 * was empty beक्रमe @bio.  The क्रमced scheduling isn't likely to
	 * cause undue delay as @bio is likely to be dispatched directly अगर
	 * its @tg's dispसमय is not in the future.
	 */
	अगर (tg->flags & THROTL_TG_WAS_EMPTY) अणु
		tg_update_dispसमय(tg);
		throtl_schedule_next_dispatch(tg->service_queue.parent_sq, true);
	पूर्ण

out_unlock:
	spin_unlock_irq(&q->queue_lock);
out:
	bio_set_flag(bio, BIO_THROTTLED);

#अगर_घोषित CONFIG_BLK_DEV_THROTTLING_LOW
	अगर (throttled || !td->track_bio_latency)
		bio->bi_issue.value |= BIO_ISSUE_THROTL_SKIP_LATENCY;
#पूर्ण_अगर
	rcu_पढ़ो_unlock();
	वापस throttled;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_THROTTLING_LOW
अटल व्योम throtl_track_latency(काष्ठा throtl_data *td, sector_t size,
	पूर्णांक op, अचिन्हित दीर्घ समय)
अणु
	काष्ठा latency_bucket *latency;
	पूर्णांक index;

	अगर (!td || td->limit_index != LIMIT_LOW ||
	    !(op == REQ_OP_READ || op == REQ_OP_WRITE) ||
	    !blk_queue_nonrot(td->queue))
		वापस;

	index = request_bucket_index(size);

	latency = get_cpu_ptr(td->latency_buckets[op]);
	latency[index].total_latency += समय;
	latency[index].samples++;
	put_cpu_ptr(td->latency_buckets[op]);
पूर्ण

व्योम blk_throtl_stat_add(काष्ठा request *rq, u64 समय_ns)
अणु
	काष्ठा request_queue *q = rq->q;
	काष्ठा throtl_data *td = q->td;

	throtl_track_latency(td, blk_rq_stats_sectors(rq), req_op(rq),
			     समय_ns >> 10);
पूर्ण

व्योम blk_throtl_bio_endio(काष्ठा bio *bio)
अणु
	काष्ठा blkcg_gq *blkg;
	काष्ठा throtl_grp *tg;
	u64 finish_समय_ns;
	अचिन्हित दीर्घ finish_समय;
	अचिन्हित दीर्घ start_समय;
	अचिन्हित दीर्घ lat;
	पूर्णांक rw = bio_data_dir(bio);

	blkg = bio->bi_blkg;
	अगर (!blkg)
		वापस;
	tg = blkg_to_tg(blkg);
	अगर (!tg->td->limit_valid[LIMIT_LOW])
		वापस;

	finish_समय_ns = kसमय_get_ns();
	tg->last_finish_समय = finish_समय_ns >> 10;

	start_समय = bio_issue_समय(&bio->bi_issue) >> 10;
	finish_समय = __bio_issue_समय(finish_समय_ns) >> 10;
	अगर (!start_समय || finish_समय <= start_समय)
		वापस;

	lat = finish_समय - start_समय;
	/* this is only क्रम bio based driver */
	अगर (!(bio->bi_issue.value & BIO_ISSUE_THROTL_SKIP_LATENCY))
		throtl_track_latency(tg->td, bio_issue_size(&bio->bi_issue),
				     bio_op(bio), lat);

	अगर (tg->latency_target && lat >= tg->td->filtered_latency) अणु
		पूर्णांक bucket;
		अचिन्हित पूर्णांक threshold;

		bucket = request_bucket_index(bio_issue_size(&bio->bi_issue));
		threshold = tg->td->avg_buckets[rw][bucket].latency +
			tg->latency_target;
		अगर (lat > threshold)
			tg->bad_bio_cnt++;
		/*
		 * Not race मुक्त, could get wrong count, which means cgroups
		 * will be throttled
		 */
		tg->bio_cnt++;
	पूर्ण

	अगर (समय_after(jअगरfies, tg->bio_cnt_reset_समय) || tg->bio_cnt > 1024) अणु
		tg->bio_cnt_reset_समय = tg->td->throtl_slice + jअगरfies;
		tg->bio_cnt /= 2;
		tg->bad_bio_cnt /= 2;
	पूर्ण
पूर्ण
#पूर्ण_अगर

पूर्णांक blk_throtl_init(काष्ठा request_queue *q)
अणु
	काष्ठा throtl_data *td;
	पूर्णांक ret;

	td = kzalloc_node(माप(*td), GFP_KERNEL, q->node);
	अगर (!td)
		वापस -ENOMEM;
	td->latency_buckets[READ] = __alloc_percpu(माप(काष्ठा latency_bucket) *
		LATENCY_BUCKET_SIZE, __alignof__(u64));
	अगर (!td->latency_buckets[READ]) अणु
		kमुक्त(td);
		वापस -ENOMEM;
	पूर्ण
	td->latency_buckets[WRITE] = __alloc_percpu(माप(काष्ठा latency_bucket) *
		LATENCY_BUCKET_SIZE, __alignof__(u64));
	अगर (!td->latency_buckets[WRITE]) अणु
		मुक्त_percpu(td->latency_buckets[READ]);
		kमुक्त(td);
		वापस -ENOMEM;
	पूर्ण

	INIT_WORK(&td->dispatch_work, blk_throtl_dispatch_work_fn);
	throtl_service_queue_init(&td->service_queue);

	q->td = td;
	td->queue = q;

	td->limit_valid[LIMIT_MAX] = true;
	td->limit_index = LIMIT_MAX;
	td->low_upgrade_समय = jअगरfies;
	td->low_करोwngrade_समय = jअगरfies;

	/* activate policy */
	ret = blkcg_activate_policy(q, &blkcg_policy_throtl);
	अगर (ret) अणु
		मुक्त_percpu(td->latency_buckets[READ]);
		मुक्त_percpu(td->latency_buckets[WRITE]);
		kमुक्त(td);
	पूर्ण
	वापस ret;
पूर्ण

व्योम blk_throtl_निकास(काष्ठा request_queue *q)
अणु
	BUG_ON(!q->td);
	throtl_shutकरोwn_wq(q);
	blkcg_deactivate_policy(q, &blkcg_policy_throtl);
	मुक्त_percpu(q->td->latency_buckets[READ]);
	मुक्त_percpu(q->td->latency_buckets[WRITE]);
	kमुक्त(q->td);
पूर्ण

व्योम blk_throtl_रेजिस्टर_queue(काष्ठा request_queue *q)
अणु
	काष्ठा throtl_data *td;
	पूर्णांक i;

	td = q->td;
	BUG_ON(!td);

	अगर (blk_queue_nonrot(q)) अणु
		td->throtl_slice = DFL_THROTL_SLICE_SSD;
		td->filtered_latency = LATENCY_FILTERED_SSD;
	पूर्ण अन्यथा अणु
		td->throtl_slice = DFL_THROTL_SLICE_HD;
		td->filtered_latency = LATENCY_FILTERED_HD;
		क्रम (i = 0; i < LATENCY_BUCKET_SIZE; i++) अणु
			td->avg_buckets[READ][i].latency = DFL_HD_BASELINE_LATENCY;
			td->avg_buckets[WRITE][i].latency = DFL_HD_BASELINE_LATENCY;
		पूर्ण
	पूर्ण
#अगर_अघोषित CONFIG_BLK_DEV_THROTTLING_LOW
	/* अगर no low limit, use previous शेष */
	td->throtl_slice = DFL_THROTL_SLICE_HD;
#पूर्ण_अगर

	td->track_bio_latency = !queue_is_mq(q);
	अगर (!td->track_bio_latency)
		blk_stat_enable_accounting(q);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_THROTTLING_LOW
sमाप_प्रकार blk_throtl_sample_समय_show(काष्ठा request_queue *q, अक्षर *page)
अणु
	अगर (!q->td)
		वापस -EINVAL;
	वापस प्र_लिखो(page, "%u\n", jअगरfies_to_msecs(q->td->throtl_slice));
पूर्ण

sमाप_प्रकार blk_throtl_sample_समय_store(काष्ठा request_queue *q,
	स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ v;
	अचिन्हित दीर्घ t;

	अगर (!q->td)
		वापस -EINVAL;
	अगर (kम_से_अदीर्घ(page, 10, &v))
		वापस -EINVAL;
	t = msecs_to_jअगरfies(v);
	अगर (t == 0 || t > MAX_THROTL_SLICE)
		वापस -EINVAL;
	q->td->throtl_slice = t;
	वापस count;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init throtl_init(व्योम)
अणु
	kthrotld_workqueue = alloc_workqueue("kthrotld", WQ_MEM_RECLAIM, 0);
	अगर (!kthrotld_workqueue)
		panic("Failed to create kthrotld\n");

	वापस blkcg_policy_रेजिस्टर(&blkcg_policy_throtl);
पूर्ण

module_init(throtl_init);
