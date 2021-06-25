<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Block rq-qos base io controller
 *
 * This works similar to wbt with a few exceptions
 *
 * - It's bio based, so the latency covers the whole block layer in addition to
 *   the actual io.
 * - We will throttle all IO that comes in here अगर we need to.
 * - We use the mean latency over the 100ms winकरोw.  This is because ग_लिखोs can
 *   be particularly fast, which could give us a false sense of the impact of
 *   other workloads on our रक्षित workload.
 * - By शेष there's no throttling, we set the queue_depth to अच_पूर्णांक_उच्च so
 *   that we can have as many outstanding bio's as we're allowed to.  Only at
 *   throttle समय करो we pay attention to the actual queue depth.
 *
 * The hierarchy works like the cpu controller करोes, we track the latency at
 * every configured node, and each configured node has it's own independent
 * queue depth.  This means that we only care about our latency tarमाला_लो at the
 * peer level.  Some group at the bottom of the hierarchy isn't going to affect
 * a group at the end of some other path अगर we're only configred at leaf level.
 *
 * Consider the following
 *
 *                   root blkg
 *             /                     \
 *        fast (target=5ms)     slow (target=10ms)
 *         /     \                  /        \
 *       a        b          normal(15ms)   unloved
 *
 * "a" and "b" have no target, but their combined io under "fast" cannot exceed
 * an average latency of 5ms.  If it करोes then we will throttle the "slow"
 * group.  In the हाल of "normal", अगर it exceeds its 15ms target, we will
 * throttle "unloved", but nobody अन्यथा.
 *
 * In this example "fast", "slow", and "normal" will be the only groups actually
 * accounting their io latencies.  We have to walk up the heirarchy to the root
 * on every submit and complete so we can करो the appropriate stat recording and
 * adjust the queue depth of ourselves अगर needed.
 *
 * There are 2 ways we throttle IO.
 *
 * 1) Queue depth throttling.  As we throttle करोwn we will adjust the maximum
 * number of IO's we're allowed to have in flight.  This starts at (u64)-1 करोwn
 * to 1.  If the group is only ever submitting IO क्रम itself then this is the
 * only way we throttle.
 *
 * 2) Induced delay throttling.  This is क्रम the हाल that a group is generating
 * IO that has to be issued by the root cg to aव्योम priority inversion. So think
 * REQ_META or REQ_SWAP.  If we are alपढ़ोy at qd == 1 and we're getting a lot
 * of work करोne क्रम us on behalf of the root cg and are being asked to scale
 * करोwn more then we induce a latency at userspace वापस.  We accumulate the
 * total amount of समय we need to be punished by करोing
 *
 * total_समय += min_lat_nsec - actual_io_completion
 *
 * and then at throttle समय will करो
 *
 * throttle_समय = min(total_समय, NSEC_PER_SEC)
 *
 * This induced delay will throttle back the activity that is generating the
 * root cg issued io's, wethere that's some metadata पूर्णांकensive operation or the
 * group is using so much memory that it is pushing us पूर्णांकo swap.
 *
 * Copyright (C) 2018 Josef Bacik
 */
#समावेश <linux/kernel.h>
#समावेश <linux/blk_types.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/module.h>
#समावेश <linux/समयr.h>
#समावेश <linux/memcontrol.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <trace/events/block.h>
#समावेश <linux/blk-mq.h>
#समावेश "blk-rq-qos.h"
#समावेश "blk-stat.h"
#समावेश "blk.h"

#घोषणा DEFAULT_SCALE_COOKIE 1000000U

अटल काष्ठा blkcg_policy blkcg_policy_iolatency;
काष्ठा iolatency_grp;

काष्ठा blk_iolatency अणु
	काष्ठा rq_qos rqos;
	काष्ठा समयr_list समयr;
	atomic_t enabled;
पूर्ण;

अटल अंतरभूत काष्ठा blk_iolatency *BLKIOLATENCY(काष्ठा rq_qos *rqos)
अणु
	वापस container_of(rqos, काष्ठा blk_iolatency, rqos);
पूर्ण

अटल अंतरभूत bool blk_iolatency_enabled(काष्ठा blk_iolatency *blkiolat)
अणु
	वापस atomic_पढ़ो(&blkiolat->enabled) > 0;
पूर्ण

काष्ठा child_latency_info अणु
	spinlock_t lock;

	/* Last समय we adjusted the scale of everybody. */
	u64 last_scale_event;

	/* The latency that we missed. */
	u64 scale_lat;

	/* Total io's from all of our children क्रम the last summation. */
	u64 nr_samples;

	/* The guy who actually changed the latency numbers. */
	काष्ठा iolatency_grp *scale_grp;

	/* Cookie to tell अगर we need to scale up or करोwn. */
	atomic_t scale_cookie;
पूर्ण;

काष्ठा percentile_stats अणु
	u64 total;
	u64 missed;
पूर्ण;

काष्ठा latency_stat अणु
	जोड़ अणु
		काष्ठा percentile_stats ps;
		काष्ठा blk_rq_stat rqs;
	पूर्ण;
पूर्ण;

काष्ठा iolatency_grp अणु
	काष्ठा blkg_policy_data pd;
	काष्ठा latency_stat __percpu *stats;
	काष्ठा latency_stat cur_stat;
	काष्ठा blk_iolatency *blkiolat;
	काष्ठा rq_depth rq_depth;
	काष्ठा rq_रुको rq_रुको;
	atomic64_t winकरोw_start;
	atomic_t scale_cookie;
	u64 min_lat_nsec;
	u64 cur_win_nsec;

	/* total running average of our io latency. */
	u64 lat_avg;

	/* Our current number of IO's क्रम the last summation. */
	u64 nr_samples;

	bool ssd;
	काष्ठा child_latency_info child_lat;
पूर्ण;

#घोषणा BLKIOLATENCY_MIN_WIN_SIZE (100 * NSEC_PER_MSEC)
#घोषणा BLKIOLATENCY_MAX_WIN_SIZE NSEC_PER_SEC
/*
 * These are the स्थिरants used to fake the fixed-poपूर्णांक moving average
 * calculation just like load average.  The call to calc_load() folds
 * (FIXED_1 (2048) - exp_factor) * new_sample पूर्णांकo lat_avg.  The sampling
 * winकरोw size is bucketed to try to approximately calculate average
 * latency such that 1/exp (decay rate) is [1 min, 2.5 min) when winकरोws
 * elapse immediately.  Note, winकरोws only elapse with IO activity.  Idle
 * periods extend the most recent winकरोw.
 */
#घोषणा BLKIOLATENCY_NR_EXP_FACTORS 5
#घोषणा BLKIOLATENCY_EXP_BUCKET_SIZE (BLKIOLATENCY_MAX_WIN_SIZE / \
				      (BLKIOLATENCY_NR_EXP_FACTORS - 1))
अटल स्थिर u64 iolatency_exp_factors[BLKIOLATENCY_NR_EXP_FACTORS] = अणु
	2045, // exp(1/600) - 600 samples
	2039, // exp(1/240) - 240 samples
	2031, // exp(1/120) - 120 samples
	2023, // exp(1/80)  - 80 samples
	2014, // exp(1/60)  - 60 samples
पूर्ण;

अटल अंतरभूत काष्ठा iolatency_grp *pd_to_lat(काष्ठा blkg_policy_data *pd)
अणु
	वापस pd ? container_of(pd, काष्ठा iolatency_grp, pd) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा iolatency_grp *blkg_to_lat(काष्ठा blkcg_gq *blkg)
अणु
	वापस pd_to_lat(blkg_to_pd(blkg, &blkcg_policy_iolatency));
पूर्ण

अटल अंतरभूत काष्ठा blkcg_gq *lat_to_blkg(काष्ठा iolatency_grp *iolat)
अणु
	वापस pd_to_blkg(&iolat->pd);
पूर्ण

अटल अंतरभूत व्योम latency_stat_init(काष्ठा iolatency_grp *iolat,
				     काष्ठा latency_stat *stat)
अणु
	अगर (iolat->ssd) अणु
		stat->ps.total = 0;
		stat->ps.missed = 0;
	पूर्ण अन्यथा
		blk_rq_stat_init(&stat->rqs);
पूर्ण

अटल अंतरभूत व्योम latency_stat_sum(काष्ठा iolatency_grp *iolat,
				    काष्ठा latency_stat *sum,
				    काष्ठा latency_stat *stat)
अणु
	अगर (iolat->ssd) अणु
		sum->ps.total += stat->ps.total;
		sum->ps.missed += stat->ps.missed;
	पूर्ण अन्यथा
		blk_rq_stat_sum(&sum->rqs, &stat->rqs);
पूर्ण

अटल अंतरभूत व्योम latency_stat_record_समय(काष्ठा iolatency_grp *iolat,
					    u64 req_समय)
अणु
	काष्ठा latency_stat *stat = get_cpu_ptr(iolat->stats);
	अगर (iolat->ssd) अणु
		अगर (req_समय >= iolat->min_lat_nsec)
			stat->ps.missed++;
		stat->ps.total++;
	पूर्ण अन्यथा
		blk_rq_stat_add(&stat->rqs, req_समय);
	put_cpu_ptr(stat);
पूर्ण

अटल अंतरभूत bool latency_sum_ok(काष्ठा iolatency_grp *iolat,
				  काष्ठा latency_stat *stat)
अणु
	अगर (iolat->ssd) अणु
		u64 thresh = भाग64_u64(stat->ps.total, 10);
		thresh = max(thresh, 1ULL);
		वापस stat->ps.missed < thresh;
	पूर्ण
	वापस stat->rqs.mean <= iolat->min_lat_nsec;
पूर्ण

अटल अंतरभूत u64 latency_stat_samples(काष्ठा iolatency_grp *iolat,
				       काष्ठा latency_stat *stat)
अणु
	अगर (iolat->ssd)
		वापस stat->ps.total;
	वापस stat->rqs.nr_samples;
पूर्ण

अटल अंतरभूत व्योम iolat_update_total_lat_avg(काष्ठा iolatency_grp *iolat,
					      काष्ठा latency_stat *stat)
अणु
	पूर्णांक exp_idx;

	अगर (iolat->ssd)
		वापस;

	/*
	 * calc_load() takes in a number stored in fixed poपूर्णांक representation.
	 * Because we are using this क्रम IO समय in ns, the values stored
	 * are signअगरicantly larger than the FIXED_1 denominator (2048).
	 * Thereक्रमe, rounding errors in the calculation are negligible and
	 * can be ignored.
	 */
	exp_idx = min_t(पूर्णांक, BLKIOLATENCY_NR_EXP_FACTORS - 1,
			भाग64_u64(iolat->cur_win_nsec,
				  BLKIOLATENCY_EXP_BUCKET_SIZE));
	iolat->lat_avg = calc_load(iolat->lat_avg,
				   iolatency_exp_factors[exp_idx],
				   stat->rqs.mean);
पूर्ण

अटल व्योम iolat_cleanup_cb(काष्ठा rq_रुको *rqw, व्योम *निजी_data)
अणु
	atomic_dec(&rqw->inflight);
	wake_up(&rqw->रुको);
पूर्ण

अटल bool iolat_acquire_inflight(काष्ठा rq_रुको *rqw, व्योम *निजी_data)
अणु
	काष्ठा iolatency_grp *iolat = निजी_data;
	वापस rq_रुको_inc_below(rqw, iolat->rq_depth.max_depth);
पूर्ण

अटल व्योम __blkcg_iolatency_throttle(काष्ठा rq_qos *rqos,
				       काष्ठा iolatency_grp *iolat,
				       bool issue_as_root,
				       bool use_memdelay)
अणु
	काष्ठा rq_रुको *rqw = &iolat->rq_रुको;
	अचिन्हित use_delay = atomic_पढ़ो(&lat_to_blkg(iolat)->use_delay);

	अगर (use_delay)
		blkcg_schedule_throttle(rqos->q, use_memdelay);

	/*
	 * To aव्योम priority inversions we want to just take a slot अगर we are
	 * issuing as root.  If we're being killed off there's no poपूर्णांक in
	 * delaying things, we may have been समाप्तed by OOM so throttling may
	 * make recovery take even दीर्घer, so just let the IO's through so the
	 * task can go away.
	 */
	अगर (issue_as_root || fatal_संकेत_pending(current)) अणु
		atomic_inc(&rqw->inflight);
		वापस;
	पूर्ण

	rq_qos_रुको(rqw, iolat, iolat_acquire_inflight, iolat_cleanup_cb);
पूर्ण

#घोषणा SCALE_DOWN_FACTOR 2
#घोषणा SCALE_UP_FACTOR 4

अटल अंतरभूत अचिन्हित दीर्घ scale_amount(अचिन्हित दीर्घ qd, bool up)
अणु
	वापस max(up ? qd >> SCALE_UP_FACTOR : qd >> SCALE_DOWN_FACTOR, 1UL);
पूर्ण

/*
 * We scale the qd करोwn faster than we scale up, so we need to use this helper
 * to adjust the scale_cookie accordingly so we करोn't prematurely get
 * scale_cookie at DEFAULT_SCALE_COOKIE and unthrottle too much.
 *
 * Each group has their own local copy of the last scale cookie they saw, so अगर
 * the global scale cookie goes up or करोwn they know which way they need to go
 * based on their last knowledge of it.
 */
अटल व्योम scale_cookie_change(काष्ठा blk_iolatency *blkiolat,
				काष्ठा child_latency_info *lat_info,
				bool up)
अणु
	अचिन्हित दीर्घ qd = blkiolat->rqos.q->nr_requests;
	अचिन्हित दीर्घ scale = scale_amount(qd, up);
	अचिन्हित दीर्घ old = atomic_पढ़ो(&lat_info->scale_cookie);
	अचिन्हित दीर्घ max_scale = qd << 1;
	अचिन्हित दीर्घ dअगरf = 0;

	अगर (old < DEFAULT_SCALE_COOKIE)
		dअगरf = DEFAULT_SCALE_COOKIE - old;

	अगर (up) अणु
		अगर (scale + old > DEFAULT_SCALE_COOKIE)
			atomic_set(&lat_info->scale_cookie,
				   DEFAULT_SCALE_COOKIE);
		अन्यथा अगर (dअगरf > qd)
			atomic_inc(&lat_info->scale_cookie);
		अन्यथा
			atomic_add(scale, &lat_info->scale_cookie);
	पूर्ण अन्यथा अणु
		/*
		 * We करोn't want to dig a hole so deep that it takes us hours to
		 * dig out of it.  Just enough that we करोn't throttle/unthrottle
		 * with jagged workloads but can still unthrottle once pressure
		 * has sufficiently dissipated.
		 */
		अगर (dअगरf > qd) अणु
			अगर (dअगरf < max_scale)
				atomic_dec(&lat_info->scale_cookie);
		पूर्ण अन्यथा अणु
			atomic_sub(scale, &lat_info->scale_cookie);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Change the queue depth of the iolatency_grp.  We add/subtract 1/16th of the
 * queue depth at a समय so we करोn't get wild swings and hopefully dial in to
 * fairer distribution of the overall queue depth.
 */
अटल व्योम scale_change(काष्ठा iolatency_grp *iolat, bool up)
अणु
	अचिन्हित दीर्घ qd = iolat->blkiolat->rqos.q->nr_requests;
	अचिन्हित दीर्घ scale = scale_amount(qd, up);
	अचिन्हित दीर्घ old = iolat->rq_depth.max_depth;

	अगर (old > qd)
		old = qd;

	अगर (up) अणु
		अगर (old == 1 && blkcg_unuse_delay(lat_to_blkg(iolat)))
			वापस;

		अगर (old < qd) अणु
			old += scale;
			old = min(old, qd);
			iolat->rq_depth.max_depth = old;
			wake_up_all(&iolat->rq_रुको.रुको);
		पूर्ण
	पूर्ण अन्यथा अणु
		old >>= 1;
		iolat->rq_depth.max_depth = max(old, 1UL);
	पूर्ण
पूर्ण

/* Check our parent and see अगर the scale cookie has changed. */
अटल व्योम check_scale_change(काष्ठा iolatency_grp *iolat)
अणु
	काष्ठा iolatency_grp *parent;
	काष्ठा child_latency_info *lat_info;
	अचिन्हित पूर्णांक cur_cookie;
	अचिन्हित पूर्णांक our_cookie = atomic_पढ़ो(&iolat->scale_cookie);
	u64 scale_lat;
	अचिन्हित पूर्णांक old;
	पूर्णांक direction = 0;

	अगर (lat_to_blkg(iolat)->parent == शून्य)
		वापस;

	parent = blkg_to_lat(lat_to_blkg(iolat)->parent);
	अगर (!parent)
		वापस;

	lat_info = &parent->child_lat;
	cur_cookie = atomic_पढ़ो(&lat_info->scale_cookie);
	scale_lat = READ_ONCE(lat_info->scale_lat);

	अगर (cur_cookie < our_cookie)
		direction = -1;
	अन्यथा अगर (cur_cookie > our_cookie)
		direction = 1;
	अन्यथा
		वापस;

	old = atomic_cmpxchg(&iolat->scale_cookie, our_cookie, cur_cookie);

	/* Somebody beat us to the punch, just bail. */
	अगर (old != our_cookie)
		वापस;

	अगर (direction < 0 && iolat->min_lat_nsec) अणु
		u64 samples_thresh;

		अगर (!scale_lat || iolat->min_lat_nsec <= scale_lat)
			वापस;

		/*
		 * Someबार high priority groups are their own worst enemy, so
		 * instead of taking it out on some poor other group that did 5%
		 * or less of the IO's क्रम the last summation just skip this
		 * scale करोwn event.
		 */
		samples_thresh = lat_info->nr_samples * 5;
		samples_thresh = max(1ULL, भाग64_u64(samples_thresh, 100));
		अगर (iolat->nr_samples <= samples_thresh)
			वापस;
	पूर्ण

	/* We're as low as we can go. */
	अगर (iolat->rq_depth.max_depth == 1 && direction < 0) अणु
		blkcg_use_delay(lat_to_blkg(iolat));
		वापस;
	पूर्ण

	/* We're back to the शेष cookie, unthrottle all the things. */
	अगर (cur_cookie == DEFAULT_SCALE_COOKIE) अणु
		blkcg_clear_delay(lat_to_blkg(iolat));
		iolat->rq_depth.max_depth = अच_पूर्णांक_उच्च;
		wake_up_all(&iolat->rq_रुको.रुको);
		वापस;
	पूर्ण

	scale_change(iolat, direction > 0);
पूर्ण

अटल व्योम blkcg_iolatency_throttle(काष्ठा rq_qos *rqos, काष्ठा bio *bio)
अणु
	काष्ठा blk_iolatency *blkiolat = BLKIOLATENCY(rqos);
	काष्ठा blkcg_gq *blkg = bio->bi_blkg;
	bool issue_as_root = bio_issue_as_root_blkg(bio);

	अगर (!blk_iolatency_enabled(blkiolat))
		वापस;

	जबतक (blkg && blkg->parent) अणु
		काष्ठा iolatency_grp *iolat = blkg_to_lat(blkg);
		अगर (!iolat) अणु
			blkg = blkg->parent;
			जारी;
		पूर्ण

		check_scale_change(iolat);
		__blkcg_iolatency_throttle(rqos, iolat, issue_as_root,
				     (bio->bi_opf & REQ_SWAP) == REQ_SWAP);
		blkg = blkg->parent;
	पूर्ण
	अगर (!समयr_pending(&blkiolat->समयr))
		mod_समयr(&blkiolat->समयr, jअगरfies + HZ);
पूर्ण

अटल व्योम iolatency_record_समय(काष्ठा iolatency_grp *iolat,
				  काष्ठा bio_issue *issue, u64 now,
				  bool issue_as_root)
अणु
	u64 start = bio_issue_समय(issue);
	u64 req_समय;

	/*
	 * Have to करो this so we are truncated to the correct समय that our
	 * issue is truncated to.
	 */
	now = __bio_issue_समय(now);

	अगर (now <= start)
		वापस;

	req_समय = now - start;

	/*
	 * We करोn't want to count issue_as_root bio's in the cgroups latency
	 * statistics as it could skew the numbers करोwnwards.
	 */
	अगर (unlikely(issue_as_root && iolat->rq_depth.max_depth != अच_पूर्णांक_उच्च)) अणु
		u64 sub = iolat->min_lat_nsec;
		अगर (req_समय < sub)
			blkcg_add_delay(lat_to_blkg(iolat), now, sub - req_समय);
		वापस;
	पूर्ण

	latency_stat_record_समय(iolat, req_समय);
पूर्ण

#घोषणा BLKIOLATENCY_MIN_ADJUST_TIME (500 * NSEC_PER_MSEC)
#घोषणा BLKIOLATENCY_MIN_GOOD_SAMPLES 5

अटल व्योम iolatency_check_latencies(काष्ठा iolatency_grp *iolat, u64 now)
अणु
	काष्ठा blkcg_gq *blkg = lat_to_blkg(iolat);
	काष्ठा iolatency_grp *parent;
	काष्ठा child_latency_info *lat_info;
	काष्ठा latency_stat stat;
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu;

	latency_stat_init(iolat, &stat);
	preempt_disable();
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा latency_stat *s;
		s = per_cpu_ptr(iolat->stats, cpu);
		latency_stat_sum(iolat, &stat, s);
		latency_stat_init(iolat, s);
	पूर्ण
	preempt_enable();

	parent = blkg_to_lat(blkg->parent);
	अगर (!parent)
		वापस;

	lat_info = &parent->child_lat;

	iolat_update_total_lat_avg(iolat, &stat);

	/* Everything is ok and we करोn't need to adjust the scale. */
	अगर (latency_sum_ok(iolat, &stat) &&
	    atomic_पढ़ो(&lat_info->scale_cookie) == DEFAULT_SCALE_COOKIE)
		वापस;

	/* Somebody beat us to the punch, just bail. */
	spin_lock_irqsave(&lat_info->lock, flags);

	latency_stat_sum(iolat, &iolat->cur_stat, &stat);
	lat_info->nr_samples -= iolat->nr_samples;
	lat_info->nr_samples += latency_stat_samples(iolat, &iolat->cur_stat);
	iolat->nr_samples = latency_stat_samples(iolat, &iolat->cur_stat);

	अगर ((lat_info->last_scale_event >= now ||
	    now - lat_info->last_scale_event < BLKIOLATENCY_MIN_ADJUST_TIME))
		जाओ out;

	अगर (latency_sum_ok(iolat, &iolat->cur_stat) &&
	    latency_sum_ok(iolat, &stat)) अणु
		अगर (latency_stat_samples(iolat, &iolat->cur_stat) <
		    BLKIOLATENCY_MIN_GOOD_SAMPLES)
			जाओ out;
		अगर (lat_info->scale_grp == iolat) अणु
			lat_info->last_scale_event = now;
			scale_cookie_change(iolat->blkiolat, lat_info, true);
		पूर्ण
	पूर्ण अन्यथा अगर (lat_info->scale_lat == 0 ||
		   lat_info->scale_lat >= iolat->min_lat_nsec) अणु
		lat_info->last_scale_event = now;
		अगर (!lat_info->scale_grp ||
		    lat_info->scale_lat > iolat->min_lat_nsec) अणु
			WRITE_ONCE(lat_info->scale_lat, iolat->min_lat_nsec);
			lat_info->scale_grp = iolat;
		पूर्ण
		scale_cookie_change(iolat->blkiolat, lat_info, false);
	पूर्ण
	latency_stat_init(iolat, &iolat->cur_stat);
out:
	spin_unlock_irqrestore(&lat_info->lock, flags);
पूर्ण

अटल व्योम blkcg_iolatency_करोne_bio(काष्ठा rq_qos *rqos, काष्ठा bio *bio)
अणु
	काष्ठा blkcg_gq *blkg;
	काष्ठा rq_रुको *rqw;
	काष्ठा iolatency_grp *iolat;
	u64 winकरोw_start;
	u64 now;
	bool issue_as_root = bio_issue_as_root_blkg(bio);
	bool enabled = false;
	पूर्णांक inflight = 0;

	blkg = bio->bi_blkg;
	अगर (!blkg || !bio_flagged(bio, BIO_TRACKED))
		वापस;

	iolat = blkg_to_lat(bio->bi_blkg);
	अगर (!iolat)
		वापस;

	enabled = blk_iolatency_enabled(iolat->blkiolat);
	अगर (!enabled)
		वापस;

	now = kसमय_प्रकारo_ns(kसमय_get());
	जबतक (blkg && blkg->parent) अणु
		iolat = blkg_to_lat(blkg);
		अगर (!iolat) अणु
			blkg = blkg->parent;
			जारी;
		पूर्ण
		rqw = &iolat->rq_रुको;

		inflight = atomic_dec_वापस(&rqw->inflight);
		WARN_ON_ONCE(inflight < 0);
		/*
		 * If bi_status is BLK_STS_AGAIN, the bio wasn't actually
		 * submitted, so करो not account क्रम it.
		 */
		अगर (iolat->min_lat_nsec && bio->bi_status != BLK_STS_AGAIN) अणु
			iolatency_record_समय(iolat, &bio->bi_issue, now,
					      issue_as_root);
			winकरोw_start = atomic64_पढ़ो(&iolat->winकरोw_start);
			अगर (now > winकरोw_start &&
			    (now - winकरोw_start) >= iolat->cur_win_nsec) अणु
				अगर (atomic64_cmpxchg(&iolat->winकरोw_start,
					     winकरोw_start, now) == winकरोw_start)
					iolatency_check_latencies(iolat, now);
			पूर्ण
		पूर्ण
		wake_up(&rqw->रुको);
		blkg = blkg->parent;
	पूर्ण
पूर्ण

अटल व्योम blkcg_iolatency_निकास(काष्ठा rq_qos *rqos)
अणु
	काष्ठा blk_iolatency *blkiolat = BLKIOLATENCY(rqos);

	del_समयr_sync(&blkiolat->समयr);
	blkcg_deactivate_policy(rqos->q, &blkcg_policy_iolatency);
	kमुक्त(blkiolat);
पूर्ण

अटल काष्ठा rq_qos_ops blkcg_iolatency_ops = अणु
	.throttle = blkcg_iolatency_throttle,
	.करोne_bio = blkcg_iolatency_करोne_bio,
	.निकास = blkcg_iolatency_निकास,
पूर्ण;

अटल व्योम blkiolatency_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा blk_iolatency *blkiolat = from_समयr(blkiolat, t, समयr);
	काष्ठा blkcg_gq *blkg;
	काष्ठा cgroup_subsys_state *pos_css;
	u64 now = kसमय_प्रकारo_ns(kसमय_get());

	rcu_पढ़ो_lock();
	blkg_क्रम_each_descendant_pre(blkg, pos_css,
				     blkiolat->rqos.q->root_blkg) अणु
		काष्ठा iolatency_grp *iolat;
		काष्ठा child_latency_info *lat_info;
		अचिन्हित दीर्घ flags;
		u64 cookie;

		/*
		 * We could be निकासing, करोn't access the pd unless we have a
		 * ref on the blkg.
		 */
		अगर (!blkg_tryget(blkg))
			जारी;

		iolat = blkg_to_lat(blkg);
		अगर (!iolat)
			जाओ next;

		lat_info = &iolat->child_lat;
		cookie = atomic_पढ़ो(&lat_info->scale_cookie);

		अगर (cookie >= DEFAULT_SCALE_COOKIE)
			जाओ next;

		spin_lock_irqsave(&lat_info->lock, flags);
		अगर (lat_info->last_scale_event >= now)
			जाओ next_lock;

		/*
		 * We scaled करोwn but करोn't have a scale_grp, scale up and carry
		 * on.
		 */
		अगर (lat_info->scale_grp == शून्य) अणु
			scale_cookie_change(iolat->blkiolat, lat_info, true);
			जाओ next_lock;
		पूर्ण

		/*
		 * It's been 5 seconds since our last scale event, clear the
		 * scale grp in हाल the group that needed the scale करोwn isn't
		 * करोing any IO currently.
		 */
		अगर (now - lat_info->last_scale_event >=
		    ((u64)NSEC_PER_SEC * 5))
			lat_info->scale_grp = शून्य;
next_lock:
		spin_unlock_irqrestore(&lat_info->lock, flags);
next:
		blkg_put(blkg);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक blk_iolatency_init(काष्ठा request_queue *q)
अणु
	काष्ठा blk_iolatency *blkiolat;
	काष्ठा rq_qos *rqos;
	पूर्णांक ret;

	blkiolat = kzalloc(माप(*blkiolat), GFP_KERNEL);
	अगर (!blkiolat)
		वापस -ENOMEM;

	rqos = &blkiolat->rqos;
	rqos->id = RQ_QOS_LATENCY;
	rqos->ops = &blkcg_iolatency_ops;
	rqos->q = q;

	rq_qos_add(q, rqos);

	ret = blkcg_activate_policy(q, &blkcg_policy_iolatency);
	अगर (ret) अणु
		rq_qos_del(q, rqos);
		kमुक्त(blkiolat);
		वापस ret;
	पूर्ण

	समयr_setup(&blkiolat->समयr, blkiolatency_समयr_fn, 0);

	वापस 0;
पूर्ण

/*
 * वापस 1 क्रम enabling iolatency, वापस -1 क्रम disabling iolatency, otherwise
 * वापस 0.
 */
अटल पूर्णांक iolatency_set_min_lat_nsec(काष्ठा blkcg_gq *blkg, u64 val)
अणु
	काष्ठा iolatency_grp *iolat = blkg_to_lat(blkg);
	u64 oldval = iolat->min_lat_nsec;

	iolat->min_lat_nsec = val;
	iolat->cur_win_nsec = max_t(u64, val << 4, BLKIOLATENCY_MIN_WIN_SIZE);
	iolat->cur_win_nsec = min_t(u64, iolat->cur_win_nsec,
				    BLKIOLATENCY_MAX_WIN_SIZE);

	अगर (!oldval && val)
		वापस 1;
	अगर (oldval && !val) अणु
		blkcg_clear_delay(blkg);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम iolatency_clear_scaling(काष्ठा blkcg_gq *blkg)
अणु
	अगर (blkg->parent) अणु
		काष्ठा iolatency_grp *iolat = blkg_to_lat(blkg->parent);
		काष्ठा child_latency_info *lat_info;
		अगर (!iolat)
			वापस;

		lat_info = &iolat->child_lat;
		spin_lock(&lat_info->lock);
		atomic_set(&lat_info->scale_cookie, DEFAULT_SCALE_COOKIE);
		lat_info->last_scale_event = 0;
		lat_info->scale_grp = शून्य;
		lat_info->scale_lat = 0;
		spin_unlock(&lat_info->lock);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार iolatency_set_limit(काष्ठा kernfs_खोलो_file *of, अक्षर *buf,
			     माप_प्रकार nbytes, loff_t off)
अणु
	काष्ठा blkcg *blkcg = css_to_blkcg(of_css(of));
	काष्ठा blkcg_gq *blkg;
	काष्ठा blkg_conf_ctx ctx;
	काष्ठा iolatency_grp *iolat;
	अक्षर *p, *tok;
	u64 lat_val = 0;
	u64 oldval;
	पूर्णांक ret;
	पूर्णांक enable = 0;

	ret = blkg_conf_prep(blkcg, &blkcg_policy_iolatency, buf, &ctx);
	अगर (ret)
		वापस ret;

	iolat = blkg_to_lat(ctx.blkg);
	p = ctx.body;

	ret = -EINVAL;
	जबतक ((tok = strsep(&p, " "))) अणु
		अक्षर key[16];
		अक्षर val[21];	/* 18446744073709551616 */

		अगर (माला_पूछो(tok, "%15[^=]=%20s", key, val) != 2)
			जाओ out;

		अगर (!म_भेद(key, "target")) अणु
			u64 v;

			अगर (!म_भेद(val, "max"))
				lat_val = 0;
			अन्यथा अगर (माला_पूछो(val, "%llu", &v) == 1)
				lat_val = v * NSEC_PER_USEC;
			अन्यथा
				जाओ out;
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण
	पूर्ण

	/* Walk up the tree to see अगर our new val is lower than it should be. */
	blkg = ctx.blkg;
	oldval = iolat->min_lat_nsec;

	enable = iolatency_set_min_lat_nsec(blkg, lat_val);
	अगर (enable) अणु
		WARN_ON_ONCE(!blk_get_queue(blkg->q));
		blkg_get(blkg);
	पूर्ण

	अगर (oldval != iolat->min_lat_nsec) अणु
		iolatency_clear_scaling(blkg);
	पूर्ण

	ret = 0;
out:
	blkg_conf_finish(&ctx);
	अगर (ret == 0 && enable) अणु
		काष्ठा iolatency_grp *पंचांगp = blkg_to_lat(blkg);
		काष्ठा blk_iolatency *blkiolat = पंचांगp->blkiolat;

		blk_mq_मुक्तze_queue(blkg->q);

		अगर (enable == 1)
			atomic_inc(&blkiolat->enabled);
		अन्यथा अगर (enable == -1)
			atomic_dec(&blkiolat->enabled);
		अन्यथा
			WARN_ON_ONCE(1);

		blk_mq_unमुक्तze_queue(blkg->q);

		blkg_put(blkg);
		blk_put_queue(blkg->q);
	पूर्ण
	वापस ret ?: nbytes;
पूर्ण

अटल u64 iolatency_prfill_limit(काष्ठा seq_file *sf,
				  काष्ठा blkg_policy_data *pd, पूर्णांक off)
अणु
	काष्ठा iolatency_grp *iolat = pd_to_lat(pd);
	स्थिर अक्षर *dname = blkg_dev_name(pd->blkg);

	अगर (!dname || !iolat->min_lat_nsec)
		वापस 0;
	seq_म_लिखो(sf, "%s target=%llu\n",
		   dname, भाग_u64(iolat->min_lat_nsec, NSEC_PER_USEC));
	वापस 0;
पूर्ण

अटल पूर्णांक iolatency_prपूर्णांक_limit(काष्ठा seq_file *sf, व्योम *v)
अणु
	blkcg_prपूर्णांक_blkgs(sf, css_to_blkcg(seq_css(sf)),
			  iolatency_prfill_limit,
			  &blkcg_policy_iolatency, seq_cft(sf)->निजी, false);
	वापस 0;
पूर्ण

अटल माप_प्रकार iolatency_ssd_stat(काष्ठा iolatency_grp *iolat, अक्षर *buf,
				 माप_प्रकार size)
अणु
	काष्ठा latency_stat stat;
	पूर्णांक cpu;

	latency_stat_init(iolat, &stat);
	preempt_disable();
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा latency_stat *s;
		s = per_cpu_ptr(iolat->stats, cpu);
		latency_stat_sum(iolat, &stat, s);
	पूर्ण
	preempt_enable();

	अगर (iolat->rq_depth.max_depth == अच_पूर्णांक_उच्च)
		वापस scnम_लिखो(buf, size, " missed=%llu total=%llu depth=max",
				 (अचिन्हित दीर्घ दीर्घ)stat.ps.missed,
				 (अचिन्हित दीर्घ दीर्घ)stat.ps.total);
	वापस scnम_लिखो(buf, size, " missed=%llu total=%llu depth=%u",
			 (अचिन्हित दीर्घ दीर्घ)stat.ps.missed,
			 (अचिन्हित दीर्घ दीर्घ)stat.ps.total,
			 iolat->rq_depth.max_depth);
पूर्ण

अटल माप_प्रकार iolatency_pd_stat(काष्ठा blkg_policy_data *pd, अक्षर *buf,
				माप_प्रकार size)
अणु
	काष्ठा iolatency_grp *iolat = pd_to_lat(pd);
	अचिन्हित दीर्घ दीर्घ avg_lat;
	अचिन्हित दीर्घ दीर्घ cur_win;

	अगर (!blkcg_debug_stats)
		वापस 0;

	अगर (iolat->ssd)
		वापस iolatency_ssd_stat(iolat, buf, size);

	avg_lat = भाग64_u64(iolat->lat_avg, NSEC_PER_USEC);
	cur_win = भाग64_u64(iolat->cur_win_nsec, NSEC_PER_MSEC);
	अगर (iolat->rq_depth.max_depth == अच_पूर्णांक_उच्च)
		वापस scnम_लिखो(buf, size, " depth=max avg_lat=%llu win=%llu",
				 avg_lat, cur_win);

	वापस scnम_लिखो(buf, size, " depth=%u avg_lat=%llu win=%llu",
			 iolat->rq_depth.max_depth, avg_lat, cur_win);
पूर्ण


अटल काष्ठा blkg_policy_data *iolatency_pd_alloc(gfp_t gfp,
						   काष्ठा request_queue *q,
						   काष्ठा blkcg *blkcg)
अणु
	काष्ठा iolatency_grp *iolat;

	iolat = kzalloc_node(माप(*iolat), gfp, q->node);
	अगर (!iolat)
		वापस शून्य;
	iolat->stats = __alloc_percpu_gfp(माप(काष्ठा latency_stat),
				       __alignof__(काष्ठा latency_stat), gfp);
	अगर (!iolat->stats) अणु
		kमुक्त(iolat);
		वापस शून्य;
	पूर्ण
	वापस &iolat->pd;
पूर्ण

अटल व्योम iolatency_pd_init(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा iolatency_grp *iolat = pd_to_lat(pd);
	काष्ठा blkcg_gq *blkg = lat_to_blkg(iolat);
	काष्ठा rq_qos *rqos = blkcg_rq_qos(blkg->q);
	काष्ठा blk_iolatency *blkiolat = BLKIOLATENCY(rqos);
	u64 now = kसमय_प्रकारo_ns(kसमय_get());
	पूर्णांक cpu;

	अगर (blk_queue_nonrot(blkg->q))
		iolat->ssd = true;
	अन्यथा
		iolat->ssd = false;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा latency_stat *stat;
		stat = per_cpu_ptr(iolat->stats, cpu);
		latency_stat_init(iolat, stat);
	पूर्ण

	latency_stat_init(iolat, &iolat->cur_stat);
	rq_रुको_init(&iolat->rq_रुको);
	spin_lock_init(&iolat->child_lat.lock);
	iolat->rq_depth.queue_depth = blkg->q->nr_requests;
	iolat->rq_depth.max_depth = अच_पूर्णांक_उच्च;
	iolat->rq_depth.शेष_depth = iolat->rq_depth.queue_depth;
	iolat->blkiolat = blkiolat;
	iolat->cur_win_nsec = 100 * NSEC_PER_MSEC;
	atomic64_set(&iolat->winकरोw_start, now);

	/*
	 * We init things in list order, so the pd क्रम the parent may not be
	 * init'ed yet क्रम whatever reason.
	 */
	अगर (blkg->parent && blkg_to_pd(blkg->parent, &blkcg_policy_iolatency)) अणु
		काष्ठा iolatency_grp *parent = blkg_to_lat(blkg->parent);
		atomic_set(&iolat->scale_cookie,
			   atomic_पढ़ो(&parent->child_lat.scale_cookie));
	पूर्ण अन्यथा अणु
		atomic_set(&iolat->scale_cookie, DEFAULT_SCALE_COOKIE);
	पूर्ण

	atomic_set(&iolat->child_lat.scale_cookie, DEFAULT_SCALE_COOKIE);
पूर्ण

अटल व्योम iolatency_pd_offline(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा iolatency_grp *iolat = pd_to_lat(pd);
	काष्ठा blkcg_gq *blkg = lat_to_blkg(iolat);
	काष्ठा blk_iolatency *blkiolat = iolat->blkiolat;
	पूर्णांक ret;

	ret = iolatency_set_min_lat_nsec(blkg, 0);
	अगर (ret == 1)
		atomic_inc(&blkiolat->enabled);
	अगर (ret == -1)
		atomic_dec(&blkiolat->enabled);
	iolatency_clear_scaling(blkg);
पूर्ण

अटल व्योम iolatency_pd_मुक्त(काष्ठा blkg_policy_data *pd)
अणु
	काष्ठा iolatency_grp *iolat = pd_to_lat(pd);
	मुक्त_percpu(iolat->stats);
	kमुक्त(iolat);
पूर्ण

अटल काष्ठा cftype iolatency_files[] = अणु
	अणु
		.name = "latency",
		.flags = CFTYPE_NOT_ON_ROOT,
		.seq_show = iolatency_prपूर्णांक_limit,
		.ग_लिखो = iolatency_set_limit,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा blkcg_policy blkcg_policy_iolatency = अणु
	.dfl_cftypes	= iolatency_files,
	.pd_alloc_fn	= iolatency_pd_alloc,
	.pd_init_fn	= iolatency_pd_init,
	.pd_offline_fn	= iolatency_pd_offline,
	.pd_मुक्त_fn	= iolatency_pd_मुक्त,
	.pd_stat_fn	= iolatency_pd_stat,
पूर्ण;

अटल पूर्णांक __init iolatency_init(व्योम)
अणु
	वापस blkcg_policy_रेजिस्टर(&blkcg_policy_iolatency);
पूर्ण

अटल व्योम __निकास iolatency_निकास(व्योम)
अणु
	blkcg_policy_unरेजिस्टर(&blkcg_policy_iolatency);
पूर्ण

module_init(iolatency_init);
module_निकास(iolatency_निकास);
