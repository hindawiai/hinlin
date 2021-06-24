<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "blk-rq-qos.h"

/*
 * Increment 'v', if 'v' is below 'below'. Returns true अगर we succeeded,
 * false अगर 'v' + 1 would be bigger than 'below'.
 */
अटल bool atomic_inc_below(atomic_t *v, अचिन्हित पूर्णांक below)
अणु
	अचिन्हित पूर्णांक cur = atomic_पढ़ो(v);

	क्रम (;;) अणु
		अचिन्हित पूर्णांक old;

		अगर (cur >= below)
			वापस false;
		old = atomic_cmpxchg(v, cur, cur + 1);
		अगर (old == cur)
			अवरोध;
		cur = old;
	पूर्ण

	वापस true;
पूर्ण

bool rq_रुको_inc_below(काष्ठा rq_रुको *rq_रुको, अचिन्हित पूर्णांक limit)
अणु
	वापस atomic_inc_below(&rq_रुको->inflight, limit);
पूर्ण

व्योम __rq_qos_cleanup(काष्ठा rq_qos *rqos, काष्ठा bio *bio)
अणु
	करो अणु
		अगर (rqos->ops->cleanup)
			rqos->ops->cleanup(rqos, bio);
		rqos = rqos->next;
	पूर्ण जबतक (rqos);
पूर्ण

व्योम __rq_qos_करोne(काष्ठा rq_qos *rqos, काष्ठा request *rq)
अणु
	करो अणु
		अगर (rqos->ops->करोne)
			rqos->ops->करोne(rqos, rq);
		rqos = rqos->next;
	पूर्ण जबतक (rqos);
पूर्ण

व्योम __rq_qos_issue(काष्ठा rq_qos *rqos, काष्ठा request *rq)
अणु
	करो अणु
		अगर (rqos->ops->issue)
			rqos->ops->issue(rqos, rq);
		rqos = rqos->next;
	पूर्ण जबतक (rqos);
पूर्ण

व्योम __rq_qos_requeue(काष्ठा rq_qos *rqos, काष्ठा request *rq)
अणु
	करो अणु
		अगर (rqos->ops->requeue)
			rqos->ops->requeue(rqos, rq);
		rqos = rqos->next;
	पूर्ण जबतक (rqos);
पूर्ण

व्योम __rq_qos_throttle(काष्ठा rq_qos *rqos, काष्ठा bio *bio)
अणु
	करो अणु
		अगर (rqos->ops->throttle)
			rqos->ops->throttle(rqos, bio);
		rqos = rqos->next;
	पूर्ण जबतक (rqos);
पूर्ण

व्योम __rq_qos_track(काष्ठा rq_qos *rqos, काष्ठा request *rq, काष्ठा bio *bio)
अणु
	करो अणु
		अगर (rqos->ops->track)
			rqos->ops->track(rqos, rq, bio);
		rqos = rqos->next;
	पूर्ण जबतक (rqos);
पूर्ण

व्योम __rq_qos_merge(काष्ठा rq_qos *rqos, काष्ठा request *rq, काष्ठा bio *bio)
अणु
	करो अणु
		अगर (rqos->ops->merge)
			rqos->ops->merge(rqos, rq, bio);
		rqos = rqos->next;
	पूर्ण जबतक (rqos);
पूर्ण

व्योम __rq_qos_करोne_bio(काष्ठा rq_qos *rqos, काष्ठा bio *bio)
अणु
	करो अणु
		अगर (rqos->ops->करोne_bio)
			rqos->ops->करोne_bio(rqos, bio);
		rqos = rqos->next;
	पूर्ण जबतक (rqos);
पूर्ण

व्योम __rq_qos_queue_depth_changed(काष्ठा rq_qos *rqos)
अणु
	करो अणु
		अगर (rqos->ops->queue_depth_changed)
			rqos->ops->queue_depth_changed(rqos);
		rqos = rqos->next;
	पूर्ण जबतक (rqos);
पूर्ण

/*
 * Return true, अगर we can't increase the depth further by scaling
 */
bool rq_depth_calc_max_depth(काष्ठा rq_depth *rqd)
अणु
	अचिन्हित पूर्णांक depth;
	bool ret = false;

	/*
	 * For QD=1 devices, this is a special हाल. It's important क्रम those
	 * to have one request पढ़ोy when one completes, so क्रमce a depth of
	 * 2 क्रम those devices. On the backend, it'll be a depth of 1 anyway,
	 * since the device can't have more than that in flight. If we're
	 * scaling करोwn, then keep a setting of 1/1/1.
	 */
	अगर (rqd->queue_depth == 1) अणु
		अगर (rqd->scale_step > 0)
			rqd->max_depth = 1;
		अन्यथा अणु
			rqd->max_depth = 2;
			ret = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * scale_step == 0 is our शेष state. If we have suffered
		 * latency spikes, step will be > 0, and we shrink the
		 * allowed ग_लिखो depths. If step is < 0, we're only करोing
		 * ग_लिखोs, and we allow a temporarily higher depth to
		 * increase perक्रमmance.
		 */
		depth = min_t(अचिन्हित पूर्णांक, rqd->शेष_depth,
			      rqd->queue_depth);
		अगर (rqd->scale_step > 0)
			depth = 1 + ((depth - 1) >> min(31, rqd->scale_step));
		अन्यथा अगर (rqd->scale_step < 0) अणु
			अचिन्हित पूर्णांक maxd = 3 * rqd->queue_depth / 4;

			depth = 1 + ((depth - 1) << -rqd->scale_step);
			अगर (depth > maxd) अणु
				depth = maxd;
				ret = true;
			पूर्ण
		पूर्ण

		rqd->max_depth = depth;
	पूर्ण

	वापस ret;
पूर्ण

/* Returns true on success and false अगर scaling up wasn't possible */
bool rq_depth_scale_up(काष्ठा rq_depth *rqd)
अणु
	/*
	 * Hit max in previous round, stop here
	 */
	अगर (rqd->scaled_max)
		वापस false;

	rqd->scale_step--;

	rqd->scaled_max = rq_depth_calc_max_depth(rqd);
	वापस true;
पूर्ण

/*
 * Scale rwb करोwn. If 'hard_throttle' is set, करो it quicker, since we
 * had a latency violation. Returns true on success and वापसs false अगर
 * scaling करोwn wasn't possible.
 */
bool rq_depth_scale_करोwn(काष्ठा rq_depth *rqd, bool hard_throttle)
अणु
	/*
	 * Stop scaling करोwn when we've hit the limit. This also prevents
	 * ->scale_step from going to crazy values, अगर the device can't
	 * keep up.
	 */
	अगर (rqd->max_depth == 1)
		वापस false;

	अगर (rqd->scale_step < 0 && hard_throttle)
		rqd->scale_step = 0;
	अन्यथा
		rqd->scale_step++;

	rqd->scaled_max = false;
	rq_depth_calc_max_depth(rqd);
	वापस true;
पूर्ण

काष्ठा rq_qos_रुको_data अणु
	काष्ठा रुको_queue_entry wq;
	काष्ठा task_काष्ठा *task;
	काष्ठा rq_रुको *rqw;
	acquire_inflight_cb_t *cb;
	व्योम *निजी_data;
	bool got_token;
पूर्ण;

अटल पूर्णांक rq_qos_wake_function(काष्ठा रुको_queue_entry *curr,
				अचिन्हित पूर्णांक mode, पूर्णांक wake_flags, व्योम *key)
अणु
	काष्ठा rq_qos_रुको_data *data = container_of(curr,
						     काष्ठा rq_qos_रुको_data,
						     wq);

	/*
	 * If we fail to get a budget, वापस -1 to पूर्णांकerrupt the wake up loop
	 * in __wake_up_common.
	 */
	अगर (!data->cb(data->rqw, data->निजी_data))
		वापस -1;

	data->got_token = true;
	smp_wmb();
	list_del_init(&curr->entry);
	wake_up_process(data->task);
	वापस 1;
पूर्ण

/**
 * rq_qos_रुको - throttle on a rqw अगर we need to
 * @rqw: rqw to throttle on
 * @निजी_data: caller provided specअगरic data
 * @acquire_inflight_cb: inc the rqw->inflight counter अगर we can
 * @cleanup_cb: the callback to cleanup in हाल we race with a waker
 *
 * This provides a unअगरorm place क्रम the rq_qos users to करो their throttling.
 * Since you can end up with a lot of things sleeping at once, this manages the
 * waking up based on the resources available.  The acquire_inflight_cb should
 * inc the rqw->inflight अगर we have the ability to करो so, or वापस false अगर not
 * and then we will sleep until the room becomes available.
 *
 * cleanup_cb is in हाल that we race with a waker and need to cleanup the
 * inflight count accordingly.
 */
व्योम rq_qos_रुको(काष्ठा rq_रुको *rqw, व्योम *निजी_data,
		 acquire_inflight_cb_t *acquire_inflight_cb,
		 cleanup_cb_t *cleanup_cb)
अणु
	काष्ठा rq_qos_रुको_data data = अणु
		.wq = अणु
			.func	= rq_qos_wake_function,
			.entry	= LIST_HEAD_INIT(data.wq.entry),
		पूर्ण,
		.task = current,
		.rqw = rqw,
		.cb = acquire_inflight_cb,
		.निजी_data = निजी_data,
	पूर्ण;
	bool has_sleeper;

	has_sleeper = wq_has_sleeper(&rqw->रुको);
	अगर (!has_sleeper && acquire_inflight_cb(rqw, निजी_data))
		वापस;

	prepare_to_रुको_exclusive(&rqw->रुको, &data.wq, TASK_UNINTERRUPTIBLE);
	has_sleeper = !wq_has_single_sleeper(&rqw->रुको);
	करो अणु
		/* The memory barrier in set_task_state saves us here. */
		अगर (data.got_token)
			अवरोध;
		अगर (!has_sleeper && acquire_inflight_cb(rqw, निजी_data)) अणु
			finish_रुको(&rqw->रुको, &data.wq);

			/*
			 * We raced with wbt_wake_function() getting a token,
			 * which means we now have two. Put our local token
			 * and wake anyone अन्यथा potentially रुकोing क्रम one.
			 */
			smp_rmb();
			अगर (data.got_token)
				cleanup_cb(rqw, निजी_data);
			अवरोध;
		पूर्ण
		io_schedule();
		has_sleeper = true;
		set_current_state(TASK_UNINTERRUPTIBLE);
	पूर्ण जबतक (1);
	finish_रुको(&rqw->रुको, &data.wq);
पूर्ण

व्योम rq_qos_निकास(काष्ठा request_queue *q)
अणु
	blk_mq_debugfs_unरेजिस्टर_queue_rqos(q);

	जबतक (q->rq_qos) अणु
		काष्ठा rq_qos *rqos = q->rq_qos;
		q->rq_qos = rqos->next;
		rqos->ops->निकास(rqos);
	पूर्ण
पूर्ण
