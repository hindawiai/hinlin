<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * buffered ग_लिखोback throttling. loosely based on CoDel. We can't drop
 * packets क्रम IO scheduling, so the logic is something like this:
 *
 * - Monitor latencies in a defined winकरोw of समय.
 * - If the minimum latency in the above winकरोw exceeds some target, increment
 *   scaling step and scale करोwn queue depth by a factor of 2x. The monitoring
 *   winकरोw is then shrunk to 100 / वर्ग_मूल(scaling step + 1).
 * - For any winकरोw where we करोn't have solid data on what the latencies
 *   look like, retain status quo.
 * - If latencies look good, decrement scaling step.
 * - If we're only करोing ग_लिखोs, allow the scaling step to go negative. This
 *   will temporarily boost ग_लिखो perक्रमmance, snapping back to a stable
 *   scaling step of 0 अगर पढ़ोs show up or the heavy ग_लिखोrs finish. Unlike
 *   positive scaling steps where we shrink the monitoring winकरोw, a negative
 *   scaling step retains the शेष step==0 winकरोw size.
 *
 * Copyright (C) 2016 Jens Axboe
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/blk_types.h>
#समावेश <linux/slab.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/swap.h>

#समावेश "blk-wbt.h"
#समावेश "blk-rq-qos.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/wbt.h>

अटल अंतरभूत व्योम wbt_clear_state(काष्ठा request *rq)
अणु
	rq->wbt_flags = 0;
पूर्ण

अटल अंतरभूत क्रमागत wbt_flags wbt_flags(काष्ठा request *rq)
अणु
	वापस rq->wbt_flags;
पूर्ण

अटल अंतरभूत bool wbt_is_tracked(काष्ठा request *rq)
अणु
	वापस rq->wbt_flags & WBT_TRACKED;
पूर्ण

अटल अंतरभूत bool wbt_is_पढ़ो(काष्ठा request *rq)
अणु
	वापस rq->wbt_flags & WBT_READ;
पूर्ण

क्रमागत अणु
	/*
	 * Default setting, we'll scale up (to 75% of QD max) or करोwn (min 1)
	 * from here depending on device stats
	 */
	RWB_DEF_DEPTH	= 16,

	/*
	 * 100msec winकरोw
	 */
	RWB_WINDOW_NSEC		= 100 * 1000 * 1000ULL,

	/*
	 * Disregard stats, अगर we करोn't meet this minimum
	 */
	RWB_MIN_WRITE_SAMPLES	= 3,

	/*
	 * If we have this number of consecutive winकरोws with not enough
	 * inक्रमmation to scale up or करोwn, scale up.
	 */
	RWB_UNKNOWN_BUMP	= 5,
पूर्ण;

अटल अंतरभूत bool rwb_enabled(काष्ठा rq_wb *rwb)
अणु
	वापस rwb && rwb->wb_normal != 0;
पूर्ण

अटल व्योम wb_बारtamp(काष्ठा rq_wb *rwb, अचिन्हित दीर्घ *var)
अणु
	अगर (rwb_enabled(rwb)) अणु
		स्थिर अचिन्हित दीर्घ cur = jअगरfies;

		अगर (cur != *var)
			*var = cur;
	पूर्ण
पूर्ण

/*
 * If a task was rate throttled in balance_dirty_pages() within the last
 * second or so, use that to indicate a higher cleaning rate.
 */
अटल bool wb_recent_रुको(काष्ठा rq_wb *rwb)
अणु
	काष्ठा bdi_ग_लिखोback *wb = &rwb->rqos.q->backing_dev_info->wb;

	वापस समय_beक्रमe(jअगरfies, wb->dirty_sleep + HZ);
पूर्ण

अटल अंतरभूत काष्ठा rq_रुको *get_rq_रुको(काष्ठा rq_wb *rwb,
					  क्रमागत wbt_flags wb_acct)
अणु
	अगर (wb_acct & WBT_KSWAPD)
		वापस &rwb->rq_रुको[WBT_RWQ_KSWAPD];
	अन्यथा अगर (wb_acct & WBT_DISCARD)
		वापस &rwb->rq_रुको[WBT_RWQ_DISCARD];

	वापस &rwb->rq_रुको[WBT_RWQ_BG];
पूर्ण

अटल व्योम rwb_wake_all(काष्ठा rq_wb *rwb)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < WBT_NUM_RWQ; i++) अणु
		काष्ठा rq_रुको *rqw = &rwb->rq_रुको[i];

		अगर (wq_has_sleeper(&rqw->रुको))
			wake_up_all(&rqw->रुको);
	पूर्ण
पूर्ण

अटल व्योम wbt_rqw_करोne(काष्ठा rq_wb *rwb, काष्ठा rq_रुको *rqw,
			 क्रमागत wbt_flags wb_acct)
अणु
	पूर्णांक inflight, limit;

	inflight = atomic_dec_वापस(&rqw->inflight);

	/*
	 * wbt got disabled with IO in flight. Wake up any potential
	 * रुकोers, we करोn't have to करो more than that.
	 */
	अगर (unlikely(!rwb_enabled(rwb))) अणु
		rwb_wake_all(rwb);
		वापस;
	पूर्ण

	/*
	 * For discards, our limit is always the background. For ग_लिखोs, अगर
	 * the device करोes ग_लिखो back caching, drop further करोwn beक्रमe we
	 * wake people up.
	 */
	अगर (wb_acct & WBT_DISCARD)
		limit = rwb->wb_background;
	अन्यथा अगर (rwb->wc && !wb_recent_रुको(rwb))
		limit = 0;
	अन्यथा
		limit = rwb->wb_normal;

	/*
	 * Don't wake anyone up अगर we are above the normal limit.
	 */
	अगर (inflight && inflight >= limit)
		वापस;

	अगर (wq_has_sleeper(&rqw->रुको)) अणु
		पूर्णांक dअगरf = limit - inflight;

		अगर (!inflight || dअगरf >= rwb->wb_background / 2)
			wake_up_all(&rqw->रुको);
	पूर्ण
पूर्ण

अटल व्योम __wbt_करोne(काष्ठा rq_qos *rqos, क्रमागत wbt_flags wb_acct)
अणु
	काष्ठा rq_wb *rwb = RQWB(rqos);
	काष्ठा rq_रुको *rqw;

	अगर (!(wb_acct & WBT_TRACKED))
		वापस;

	rqw = get_rq_रुको(rwb, wb_acct);
	wbt_rqw_करोne(rwb, rqw, wb_acct);
पूर्ण

/*
 * Called on completion of a request. Note that it's also called when
 * a request is merged, when the request माला_लो मुक्तd.
 */
अटल व्योम wbt_करोne(काष्ठा rq_qos *rqos, काष्ठा request *rq)
अणु
	काष्ठा rq_wb *rwb = RQWB(rqos);

	अगर (!wbt_is_tracked(rq)) अणु
		अगर (rwb->sync_cookie == rq) अणु
			rwb->sync_issue = 0;
			rwb->sync_cookie = शून्य;
		पूर्ण

		अगर (wbt_is_पढ़ो(rq))
			wb_बारtamp(rwb, &rwb->last_comp);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(rq == rwb->sync_cookie);
		__wbt_करोne(rqos, wbt_flags(rq));
	पूर्ण
	wbt_clear_state(rq);
पूर्ण

अटल अंतरभूत bool stat_sample_valid(काष्ठा blk_rq_stat *stat)
अणु
	/*
	 * We need at least one पढ़ो sample, and a minimum of
	 * RWB_MIN_WRITE_SAMPLES. We require some ग_लिखो samples to know
	 * that it's ग_लिखोs impacting us, and not just some sole पढ़ो on
	 * a device that is in a lower घातer state.
	 */
	वापस (stat[READ].nr_samples >= 1 &&
		stat[WRITE].nr_samples >= RWB_MIN_WRITE_SAMPLES);
पूर्ण

अटल u64 rwb_sync_issue_lat(काष्ठा rq_wb *rwb)
अणु
	u64 now, issue = READ_ONCE(rwb->sync_issue);

	अगर (!issue || !rwb->sync_cookie)
		वापस 0;

	now = kसमय_प्रकारo_ns(kसमय_get());
	वापस now - issue;
पूर्ण

क्रमागत अणु
	LAT_OK = 1,
	LAT_UNKNOWN,
	LAT_UNKNOWN_WRITES,
	LAT_EXCEEDED,
पूर्ण;

अटल पूर्णांक latency_exceeded(काष्ठा rq_wb *rwb, काष्ठा blk_rq_stat *stat)
अणु
	काष्ठा backing_dev_info *bdi = rwb->rqos.q->backing_dev_info;
	काष्ठा rq_depth *rqd = &rwb->rq_depth;
	u64 thislat;

	/*
	 * If our stored sync issue exceeds the winकरोw size, or it
	 * exceeds our min target AND we haven't logged any entries,
	 * flag the latency as exceeded. wbt works off completion latencies,
	 * but क्रम a flooded device, a single sync IO can take a दीर्घ समय
	 * to complete after being issued. If this समय exceeds our
	 * monitoring winकरोw AND we didn't see any other completions in that
	 * winकरोw, then count that sync IO as a violation of the latency.
	 */
	thislat = rwb_sync_issue_lat(rwb);
	अगर (thislat > rwb->cur_win_nsec ||
	    (thislat > rwb->min_lat_nsec && !stat[READ].nr_samples)) अणु
		trace_wbt_lat(bdi, thislat);
		वापस LAT_EXCEEDED;
	पूर्ण

	/*
	 * No पढ़ो/ग_लिखो mix, अगर stat isn't valid
	 */
	अगर (!stat_sample_valid(stat)) अणु
		/*
		 * If we had ग_लिखोs in this stat winकरोw and the winकरोw is
		 * current, we're only करोing ग_लिखोs. If a task recently
		 * रुकोed or still has ग_लिखोs in flights, consider us करोing
		 * just ग_लिखोs as well.
		 */
		अगर (stat[WRITE].nr_samples || wb_recent_रुको(rwb) ||
		    wbt_inflight(rwb))
			वापस LAT_UNKNOWN_WRITES;
		वापस LAT_UNKNOWN;
	पूर्ण

	/*
	 * If the 'min' latency exceeds our target, step करोwn.
	 */
	अगर (stat[READ].min > rwb->min_lat_nsec) अणु
		trace_wbt_lat(bdi, stat[READ].min);
		trace_wbt_stat(bdi, stat);
		वापस LAT_EXCEEDED;
	पूर्ण

	अगर (rqd->scale_step)
		trace_wbt_stat(bdi, stat);

	वापस LAT_OK;
पूर्ण

अटल व्योम rwb_trace_step(काष्ठा rq_wb *rwb, स्थिर अक्षर *msg)
अणु
	काष्ठा backing_dev_info *bdi = rwb->rqos.q->backing_dev_info;
	काष्ठा rq_depth *rqd = &rwb->rq_depth;

	trace_wbt_step(bdi, msg, rqd->scale_step, rwb->cur_win_nsec,
			rwb->wb_background, rwb->wb_normal, rqd->max_depth);
पूर्ण

अटल व्योम calc_wb_limits(काष्ठा rq_wb *rwb)
अणु
	अगर (rwb->min_lat_nsec == 0) अणु
		rwb->wb_normal = rwb->wb_background = 0;
	पूर्ण अन्यथा अगर (rwb->rq_depth.max_depth <= 2) अणु
		rwb->wb_normal = rwb->rq_depth.max_depth;
		rwb->wb_background = 1;
	पूर्ण अन्यथा अणु
		rwb->wb_normal = (rwb->rq_depth.max_depth + 1) / 2;
		rwb->wb_background = (rwb->rq_depth.max_depth + 3) / 4;
	पूर्ण
पूर्ण

अटल व्योम scale_up(काष्ठा rq_wb *rwb)
अणु
	अगर (!rq_depth_scale_up(&rwb->rq_depth))
		वापस;
	calc_wb_limits(rwb);
	rwb->unknown_cnt = 0;
	rwb_wake_all(rwb);
	rwb_trace_step(rwb, tracepoपूर्णांक_string("scale up"));
पूर्ण

अटल व्योम scale_करोwn(काष्ठा rq_wb *rwb, bool hard_throttle)
अणु
	अगर (!rq_depth_scale_करोwn(&rwb->rq_depth, hard_throttle))
		वापस;
	calc_wb_limits(rwb);
	rwb->unknown_cnt = 0;
	rwb_trace_step(rwb, tracepoपूर्णांक_string("scale down"));
पूर्ण

अटल व्योम rwb_arm_समयr(काष्ठा rq_wb *rwb)
अणु
	काष्ठा rq_depth *rqd = &rwb->rq_depth;

	अगर (rqd->scale_step > 0) अणु
		/*
		 * We should speed this up, using some variant of a fast
		 * पूर्णांकeger inverse square root calculation. Since we only करो
		 * this क्रम every winकरोw expiration, it's not a huge deal,
		 * though.
		 */
		rwb->cur_win_nsec = भाग_u64(rwb->win_nsec << 4,
					पूर्णांक_वर्ग_मूल((rqd->scale_step + 1) << 8));
	पूर्ण अन्यथा अणु
		/*
		 * For step < 0, we करोn't want to increase/decrease the
		 * winकरोw size.
		 */
		rwb->cur_win_nsec = rwb->win_nsec;
	पूर्ण

	blk_stat_activate_nsecs(rwb->cb, rwb->cur_win_nsec);
पूर्ण

अटल व्योम wb_समयr_fn(काष्ठा blk_stat_callback *cb)
अणु
	काष्ठा rq_wb *rwb = cb->data;
	काष्ठा rq_depth *rqd = &rwb->rq_depth;
	अचिन्हित पूर्णांक inflight = wbt_inflight(rwb);
	पूर्णांक status;

	status = latency_exceeded(rwb, cb->stat);

	trace_wbt_समयr(rwb->rqos.q->backing_dev_info, status, rqd->scale_step,
			inflight);

	/*
	 * If we exceeded the latency target, step करोwn. If we did not,
	 * step one level up. If we करोn't know enough to say either exceeded
	 * or ok, then करोn't करो anything.
	 */
	चयन (status) अणु
	हाल LAT_EXCEEDED:
		scale_करोwn(rwb, true);
		अवरोध;
	हाल LAT_OK:
		scale_up(rwb);
		अवरोध;
	हाल LAT_UNKNOWN_WRITES:
		/*
		 * We started a the center step, but करोn't have a valid
		 * पढ़ो/ग_लिखो sample, but we करो have ग_लिखोs going on.
		 * Allow step to go negative, to increase ग_लिखो perf.
		 */
		scale_up(rwb);
		अवरोध;
	हाल LAT_UNKNOWN:
		अगर (++rwb->unknown_cnt < RWB_UNKNOWN_BUMP)
			अवरोध;
		/*
		 * We get here when previously scaled reduced depth, and we
		 * currently करोn't have a valid पढ़ो/ग_लिखो sample. For that
		 * हाल, slowly वापस to center state (step == 0).
		 */
		अगर (rqd->scale_step > 0)
			scale_up(rwb);
		अन्यथा अगर (rqd->scale_step < 0)
			scale_करोwn(rwb, false);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Re-arm समयr, अगर we have IO in flight
	 */
	अगर (rqd->scale_step || inflight)
		rwb_arm_समयr(rwb);
पूर्ण

अटल व्योम wbt_update_limits(काष्ठा rq_wb *rwb)
अणु
	काष्ठा rq_depth *rqd = &rwb->rq_depth;

	rqd->scale_step = 0;
	rqd->scaled_max = false;

	rq_depth_calc_max_depth(rqd);
	calc_wb_limits(rwb);

	rwb_wake_all(rwb);
पूर्ण

u64 wbt_get_min_lat(काष्ठा request_queue *q)
अणु
	काष्ठा rq_qos *rqos = wbt_rq_qos(q);
	अगर (!rqos)
		वापस 0;
	वापस RQWB(rqos)->min_lat_nsec;
पूर्ण

व्योम wbt_set_min_lat(काष्ठा request_queue *q, u64 val)
अणु
	काष्ठा rq_qos *rqos = wbt_rq_qos(q);
	अगर (!rqos)
		वापस;
	RQWB(rqos)->min_lat_nsec = val;
	RQWB(rqos)->enable_state = WBT_STATE_ON_MANUAL;
	wbt_update_limits(RQWB(rqos));
पूर्ण


अटल bool बंद_io(काष्ठा rq_wb *rwb)
अणु
	स्थिर अचिन्हित दीर्घ now = jअगरfies;

	वापस समय_beक्रमe(now, rwb->last_issue + HZ / 10) ||
		समय_beक्रमe(now, rwb->last_comp + HZ / 10);
पूर्ण

#घोषणा REQ_HIPRIO	(REQ_SYNC | REQ_META | REQ_PRIO)

अटल अंतरभूत अचिन्हित पूर्णांक get_limit(काष्ठा rq_wb *rwb, अचिन्हित दीर्घ rw)
अणु
	अचिन्हित पूर्णांक limit;

	/*
	 * If we got disabled, just वापस अच_पूर्णांक_उच्च. This ensures that
	 * we'll properly inc a new IO, and dec+wakeup at the end.
	 */
	अगर (!rwb_enabled(rwb))
		वापस अच_पूर्णांक_उच्च;

	अगर ((rw & REQ_OP_MASK) == REQ_OP_DISCARD)
		वापस rwb->wb_background;

	/*
	 * At this poपूर्णांक we know it's a buffered ग_लिखो. If this is
	 * kswapd trying to मुक्त memory, or REQ_SYNC is set, then
	 * it's WB_SYNC_ALL writeback, and we'll use the max limit क्रम
	 * that. If the ग_लिखो is marked as a background ग_लिखो, then use
	 * the idle limit, or go to normal अगर we haven't had competing
	 * IO क्रम a bit.
	 */
	अगर ((rw & REQ_HIPRIO) || wb_recent_रुको(rwb) || current_is_kswapd())
		limit = rwb->rq_depth.max_depth;
	अन्यथा अगर ((rw & REQ_BACKGROUND) || बंद_io(rwb)) अणु
		/*
		 * If less than 100ms since we completed unrelated IO,
		 * limit us to half the depth क्रम background ग_लिखोback.
		 */
		limit = rwb->wb_background;
	पूर्ण अन्यथा
		limit = rwb->wb_normal;

	वापस limit;
पूर्ण

काष्ठा wbt_रुको_data अणु
	काष्ठा rq_wb *rwb;
	क्रमागत wbt_flags wb_acct;
	अचिन्हित दीर्घ rw;
पूर्ण;

अटल bool wbt_inflight_cb(काष्ठा rq_रुको *rqw, व्योम *निजी_data)
अणु
	काष्ठा wbt_रुको_data *data = निजी_data;
	वापस rq_रुको_inc_below(rqw, get_limit(data->rwb, data->rw));
पूर्ण

अटल व्योम wbt_cleanup_cb(काष्ठा rq_रुको *rqw, व्योम *निजी_data)
अणु
	काष्ठा wbt_रुको_data *data = निजी_data;
	wbt_rqw_करोne(data->rwb, rqw, data->wb_acct);
पूर्ण

/*
 * Block अगर we will exceed our limit, or अगर we are currently रुकोing क्रम
 * the समयr to kick off queuing again.
 */
अटल व्योम __wbt_रुको(काष्ठा rq_wb *rwb, क्रमागत wbt_flags wb_acct,
		       अचिन्हित दीर्घ rw)
अणु
	काष्ठा rq_रुको *rqw = get_rq_रुको(rwb, wb_acct);
	काष्ठा wbt_रुको_data data = अणु
		.rwb = rwb,
		.wb_acct = wb_acct,
		.rw = rw,
	पूर्ण;

	rq_qos_रुको(rqw, &data, wbt_inflight_cb, wbt_cleanup_cb);
पूर्ण

अटल अंतरभूत bool wbt_should_throttle(काष्ठा bio *bio)
अणु
	चयन (bio_op(bio)) अणु
	हाल REQ_OP_WRITE:
		/*
		 * Don't throttle WRITE_OसूचीECT
		 */
		अगर ((bio->bi_opf & (REQ_SYNC | REQ_IDLE)) ==
		    (REQ_SYNC | REQ_IDLE))
			वापस false;
		fallthrough;
	हाल REQ_OP_DISCARD:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल क्रमागत wbt_flags bio_to_wbt_flags(काष्ठा rq_wb *rwb, काष्ठा bio *bio)
अणु
	क्रमागत wbt_flags flags = 0;

	अगर (!rwb_enabled(rwb))
		वापस 0;

	अगर (bio_op(bio) == REQ_OP_READ) अणु
		flags = WBT_READ;
	पूर्ण अन्यथा अगर (wbt_should_throttle(bio)) अणु
		अगर (current_is_kswapd())
			flags |= WBT_KSWAPD;
		अगर (bio_op(bio) == REQ_OP_DISCARD)
			flags |= WBT_DISCARD;
		flags |= WBT_TRACKED;
	पूर्ण
	वापस flags;
पूर्ण

अटल व्योम wbt_cleanup(काष्ठा rq_qos *rqos, काष्ठा bio *bio)
अणु
	काष्ठा rq_wb *rwb = RQWB(rqos);
	क्रमागत wbt_flags flags = bio_to_wbt_flags(rwb, bio);
	__wbt_करोne(rqos, flags);
पूर्ण

/*
 * Returns true अगर the IO request should be accounted, false अगर not.
 * May sleep, अगर we have exceeded the ग_लिखोback limits. Caller can pass
 * in an irq held spinlock, अगर it holds one when calling this function.
 * If we करो sleep, we'll release and re-grab it.
 */
अटल व्योम wbt_रुको(काष्ठा rq_qos *rqos, काष्ठा bio *bio)
अणु
	काष्ठा rq_wb *rwb = RQWB(rqos);
	क्रमागत wbt_flags flags;

	flags = bio_to_wbt_flags(rwb, bio);
	अगर (!(flags & WBT_TRACKED)) अणु
		अगर (flags & WBT_READ)
			wb_बारtamp(rwb, &rwb->last_issue);
		वापस;
	पूर्ण

	__wbt_रुको(rwb, flags, bio->bi_opf);

	अगर (!blk_stat_is_active(rwb->cb))
		rwb_arm_समयr(rwb);
पूर्ण

अटल व्योम wbt_track(काष्ठा rq_qos *rqos, काष्ठा request *rq, काष्ठा bio *bio)
अणु
	काष्ठा rq_wb *rwb = RQWB(rqos);
	rq->wbt_flags |= bio_to_wbt_flags(rwb, bio);
पूर्ण

अटल व्योम wbt_issue(काष्ठा rq_qos *rqos, काष्ठा request *rq)
अणु
	काष्ठा rq_wb *rwb = RQWB(rqos);

	अगर (!rwb_enabled(rwb))
		वापस;

	/*
	 * Track sync issue, in हाल it takes a दीर्घ समय to complete. Allows us
	 * to react quicker, अगर a sync IO takes a दीर्घ समय to complete. Note
	 * that this is just a hपूर्णांक. The request can go away when it completes,
	 * so it's important we never dereference it. We only use the address to
	 * compare with, which is why we store the sync_issue समय locally.
	 */
	अगर (wbt_is_पढ़ो(rq) && !rwb->sync_issue) अणु
		rwb->sync_cookie = rq;
		rwb->sync_issue = rq->io_start_समय_ns;
	पूर्ण
पूर्ण

अटल व्योम wbt_requeue(काष्ठा rq_qos *rqos, काष्ठा request *rq)
अणु
	काष्ठा rq_wb *rwb = RQWB(rqos);
	अगर (!rwb_enabled(rwb))
		वापस;
	अगर (rq == rwb->sync_cookie) अणु
		rwb->sync_issue = 0;
		rwb->sync_cookie = शून्य;
	पूर्ण
पूर्ण

व्योम wbt_set_ग_लिखो_cache(काष्ठा request_queue *q, bool ग_लिखो_cache_on)
अणु
	काष्ठा rq_qos *rqos = wbt_rq_qos(q);
	अगर (rqos)
		RQWB(rqos)->wc = ग_लिखो_cache_on;
पूर्ण

/*
 * Enable wbt अगर शेषs are configured that way
 */
व्योम wbt_enable_शेष(काष्ठा request_queue *q)
अणु
	काष्ठा rq_qos *rqos = wbt_rq_qos(q);
	/* Throttling alपढ़ोy enabled? */
	अगर (rqos)
		वापस;

	/* Queue not रेजिस्टरed? Maybe shutting करोwn... */
	अगर (!blk_queue_रेजिस्टरed(q))
		वापस;

	अगर (queue_is_mq(q) && IS_ENABLED(CONFIG_BLK_WBT_MQ))
		wbt_init(q);
पूर्ण
EXPORT_SYMBOL_GPL(wbt_enable_शेष);

u64 wbt_शेष_latency_nsec(काष्ठा request_queue *q)
अणु
	/*
	 * We शेष to 2msec क्रम non-rotational storage, and 75msec
	 * क्रम rotational storage.
	 */
	अगर (blk_queue_nonrot(q))
		वापस 2000000ULL;
	अन्यथा
		वापस 75000000ULL;
पूर्ण

अटल पूर्णांक wbt_data_dir(स्थिर काष्ठा request *rq)
अणु
	स्थिर पूर्णांक op = req_op(rq);

	अगर (op == REQ_OP_READ)
		वापस READ;
	अन्यथा अगर (op_is_ग_लिखो(op))
		वापस WRITE;

	/* करोn't account */
	वापस -1;
पूर्ण

अटल व्योम wbt_queue_depth_changed(काष्ठा rq_qos *rqos)
अणु
	RQWB(rqos)->rq_depth.queue_depth = blk_queue_depth(rqos->q);
	wbt_update_limits(RQWB(rqos));
पूर्ण

अटल व्योम wbt_निकास(काष्ठा rq_qos *rqos)
अणु
	काष्ठा rq_wb *rwb = RQWB(rqos);
	काष्ठा request_queue *q = rqos->q;

	blk_stat_हटाओ_callback(q, rwb->cb);
	blk_stat_मुक्त_callback(rwb->cb);
	kमुक्त(rwb);
पूर्ण

/*
 * Disable wbt, अगर enabled by शेष.
 */
व्योम wbt_disable_शेष(काष्ठा request_queue *q)
अणु
	काष्ठा rq_qos *rqos = wbt_rq_qos(q);
	काष्ठा rq_wb *rwb;
	अगर (!rqos)
		वापस;
	rwb = RQWB(rqos);
	अगर (rwb->enable_state == WBT_STATE_ON_DEFAULT) अणु
		blk_stat_deactivate(rwb->cb);
		rwb->wb_normal = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(wbt_disable_शेष);

#अगर_घोषित CONFIG_BLK_DEBUG_FS
अटल पूर्णांक wbt_curr_win_nsec_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा rq_qos *rqos = data;
	काष्ठा rq_wb *rwb = RQWB(rqos);

	seq_म_लिखो(m, "%llu\n", rwb->cur_win_nsec);
	वापस 0;
पूर्ण

अटल पूर्णांक wbt_enabled_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा rq_qos *rqos = data;
	काष्ठा rq_wb *rwb = RQWB(rqos);

	seq_म_लिखो(m, "%d\n", rwb->enable_state);
	वापस 0;
पूर्ण

अटल पूर्णांक wbt_id_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा rq_qos *rqos = data;

	seq_म_लिखो(m, "%u\n", rqos->id);
	वापस 0;
पूर्ण

अटल पूर्णांक wbt_inflight_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा rq_qos *rqos = data;
	काष्ठा rq_wb *rwb = RQWB(rqos);
	पूर्णांक i;

	क्रम (i = 0; i < WBT_NUM_RWQ; i++)
		seq_म_लिखो(m, "%d: inflight %d\n", i,
			   atomic_पढ़ो(&rwb->rq_रुको[i].inflight));
	वापस 0;
पूर्ण

अटल पूर्णांक wbt_min_lat_nsec_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा rq_qos *rqos = data;
	काष्ठा rq_wb *rwb = RQWB(rqos);

	seq_म_लिखो(m, "%lu\n", rwb->min_lat_nsec);
	वापस 0;
पूर्ण

अटल पूर्णांक wbt_unknown_cnt_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा rq_qos *rqos = data;
	काष्ठा rq_wb *rwb = RQWB(rqos);

	seq_म_लिखो(m, "%u\n", rwb->unknown_cnt);
	वापस 0;
पूर्ण

अटल पूर्णांक wbt_normal_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा rq_qos *rqos = data;
	काष्ठा rq_wb *rwb = RQWB(rqos);

	seq_म_लिखो(m, "%u\n", rwb->wb_normal);
	वापस 0;
पूर्ण

अटल पूर्णांक wbt_background_show(व्योम *data, काष्ठा seq_file *m)
अणु
	काष्ठा rq_qos *rqos = data;
	काष्ठा rq_wb *rwb = RQWB(rqos);

	seq_म_लिखो(m, "%u\n", rwb->wb_background);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा blk_mq_debugfs_attr wbt_debugfs_attrs[] = अणु
	अणु"curr_win_nsec", 0400, wbt_curr_win_nsec_showपूर्ण,
	अणु"enabled", 0400, wbt_enabled_showपूर्ण,
	अणु"id", 0400, wbt_id_showपूर्ण,
	अणु"inflight", 0400, wbt_inflight_showपूर्ण,
	अणु"min_lat_nsec", 0400, wbt_min_lat_nsec_showपूर्ण,
	अणु"unknown_cnt", 0400, wbt_unknown_cnt_showपूर्ण,
	अणु"wb_normal", 0400, wbt_normal_showपूर्ण,
	अणु"wb_background", 0400, wbt_background_showपूर्ण,
	अणुपूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा rq_qos_ops wbt_rqos_ops = अणु
	.throttle = wbt_रुको,
	.issue = wbt_issue,
	.track = wbt_track,
	.requeue = wbt_requeue,
	.करोne = wbt_करोne,
	.cleanup = wbt_cleanup,
	.queue_depth_changed = wbt_queue_depth_changed,
	.निकास = wbt_निकास,
#अगर_घोषित CONFIG_BLK_DEBUG_FS
	.debugfs_attrs = wbt_debugfs_attrs,
#पूर्ण_अगर
पूर्ण;

पूर्णांक wbt_init(काष्ठा request_queue *q)
अणु
	काष्ठा rq_wb *rwb;
	पूर्णांक i;

	rwb = kzalloc(माप(*rwb), GFP_KERNEL);
	अगर (!rwb)
		वापस -ENOMEM;

	rwb->cb = blk_stat_alloc_callback(wb_समयr_fn, wbt_data_dir, 2, rwb);
	अगर (!rwb->cb) अणु
		kमुक्त(rwb);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < WBT_NUM_RWQ; i++)
		rq_रुको_init(&rwb->rq_रुको[i]);

	rwb->rqos.id = RQ_QOS_WBT;
	rwb->rqos.ops = &wbt_rqos_ops;
	rwb->rqos.q = q;
	rwb->last_comp = rwb->last_issue = jअगरfies;
	rwb->win_nsec = RWB_WINDOW_NSEC;
	rwb->enable_state = WBT_STATE_ON_DEFAULT;
	rwb->wc = 1;
	rwb->rq_depth.शेष_depth = RWB_DEF_DEPTH;

	/*
	 * Assign rwb and add the stats callback.
	 */
	rq_qos_add(q, &rwb->rqos);
	blk_stat_add_callback(q, rwb->cb);

	rwb->min_lat_nsec = wbt_शेष_latency_nsec(q);

	wbt_queue_depth_changed(&rwb->rqos);
	wbt_set_ग_लिखो_cache(q, test_bit(QUEUE_FLAG_WC, &q->queue_flags));

	वापस 0;
पूर्ण
