<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x Interrupt Management
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/irq.h>

#समावेश <trace/events/host1x.h>
#समावेश "channel.h"
#समावेश "dev.h"
#समावेश "intr.h"

/* Wait list management */

क्रमागत रुकोlist_state अणु
	WLS_PENDING,
	WLS_REMOVED,
	WLS_CANCELLED,
	WLS_HANDLED
पूर्ण;

अटल व्योम रुकोer_release(काष्ठा kref *kref)
अणु
	kमुक्त(container_of(kref, काष्ठा host1x_रुकोlist, refcount));
पूर्ण

/*
 * add a रुकोer to a रुकोer queue, sorted by threshold
 * वापसs true अगर it was added at the head of the queue
 */
अटल bool add_रुकोer_to_queue(काष्ठा host1x_रुकोlist *रुकोer,
				काष्ठा list_head *queue)
अणु
	काष्ठा host1x_रुकोlist *pos;
	u32 thresh = रुकोer->thresh;

	list_क्रम_each_entry_reverse(pos, queue, list)
		अगर ((s32)(pos->thresh - thresh) <= 0) अणु
			list_add(&रुकोer->list, &pos->list);
			वापस false;
		पूर्ण

	list_add(&रुकोer->list, queue);
	वापस true;
पूर्ण

/*
 * run through a रुकोer queue क्रम a single sync poपूर्णांक ID
 * and gather all completed रुकोers पूर्णांकo lists by actions
 */
अटल व्योम हटाओ_completed_रुकोers(काष्ठा list_head *head, u32 sync,
			काष्ठा list_head completed[HOST1X_INTR_ACTION_COUNT])
अणु
	काष्ठा list_head *dest;
	काष्ठा host1x_रुकोlist *रुकोer, *next, *prev;

	list_क्रम_each_entry_safe(रुकोer, next, head, list) अणु
		अगर ((s32)(रुकोer->thresh - sync) > 0)
			अवरोध;

		dest = completed + रुकोer->action;

		/* consolidate submit cleanups */
		अगर (रुकोer->action == HOST1X_INTR_ACTION_SUBMIT_COMPLETE &&
		    !list_empty(dest)) अणु
			prev = list_entry(dest->prev,
					  काष्ठा host1x_रुकोlist, list);
			अगर (prev->data == रुकोer->data) अणु
				prev->count++;
				dest = शून्य;
			पूर्ण
		पूर्ण

		/* PENDING->REMOVED or CANCELLED->HANDLED */
		अगर (atomic_inc_वापस(&रुकोer->state) == WLS_HANDLED || !dest) अणु
			list_del(&रुकोer->list);
			kref_put(&रुकोer->refcount, रुकोer_release);
		पूर्ण अन्यथा
			list_move_tail(&रुकोer->list, dest);
	पूर्ण
पूर्ण

अटल व्योम reset_threshold_पूर्णांकerrupt(काष्ठा host1x *host,
				      काष्ठा list_head *head,
				      अचिन्हित पूर्णांक id)
अणु
	u32 thresh =
		list_first_entry(head, काष्ठा host1x_रुकोlist, list)->thresh;

	host1x_hw_पूर्णांकr_set_syncpt_threshold(host, id, thresh);
	host1x_hw_पूर्णांकr_enable_syncpt_पूर्णांकr(host, id);
पूर्ण

अटल व्योम action_submit_complete(काष्ठा host1x_रुकोlist *रुकोer)
अणु
	काष्ठा host1x_channel *channel = रुकोer->data;

	host1x_cdma_update(&channel->cdma);

	/*  Add nr_completed to trace */
	trace_host1x_channel_submit_complete(dev_name(channel->dev),
					     रुकोer->count, रुकोer->thresh);
पूर्ण

अटल व्योम action_wakeup(काष्ठा host1x_रुकोlist *रुकोer)
अणु
	रुको_queue_head_t *wq = रुकोer->data;

	wake_up(wq);
पूर्ण

अटल व्योम action_wakeup_पूर्णांकerruptible(काष्ठा host1x_रुकोlist *रुकोer)
अणु
	रुको_queue_head_t *wq = रुकोer->data;

	wake_up_पूर्णांकerruptible(wq);
पूर्ण

प्रकार व्योम (*action_handler)(काष्ठा host1x_रुकोlist *रुकोer);

अटल स्थिर action_handler action_handlers[HOST1X_INTR_ACTION_COUNT] = अणु
	action_submit_complete,
	action_wakeup,
	action_wakeup_पूर्णांकerruptible,
पूर्ण;

अटल व्योम run_handlers(काष्ठा list_head completed[HOST1X_INTR_ACTION_COUNT])
अणु
	काष्ठा list_head *head = completed;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < HOST1X_INTR_ACTION_COUNT; ++i, ++head) अणु
		action_handler handler = action_handlers[i];
		काष्ठा host1x_रुकोlist *रुकोer, *next;

		list_क्रम_each_entry_safe(रुकोer, next, head, list) अणु
			list_del(&रुकोer->list);
			handler(रुकोer);
			WARN_ON(atomic_xchg(&रुकोer->state, WLS_HANDLED) !=
				WLS_REMOVED);
			kref_put(&रुकोer->refcount, रुकोer_release);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Remove & handle all रुकोers that have completed क्रम the given syncpt
 */
अटल पूर्णांक process_रुको_list(काष्ठा host1x *host,
			     काष्ठा host1x_syncpt *syncpt,
			     u32 threshold)
अणु
	काष्ठा list_head completed[HOST1X_INTR_ACTION_COUNT];
	अचिन्हित पूर्णांक i;
	पूर्णांक empty;

	क्रम (i = 0; i < HOST1X_INTR_ACTION_COUNT; ++i)
		INIT_LIST_HEAD(completed + i);

	spin_lock(&syncpt->पूर्णांकr.lock);

	हटाओ_completed_रुकोers(&syncpt->पूर्णांकr.रुको_head, threshold,
				 completed);

	empty = list_empty(&syncpt->पूर्णांकr.रुको_head);
	अगर (empty)
		host1x_hw_पूर्णांकr_disable_syncpt_पूर्णांकr(host, syncpt->id);
	अन्यथा
		reset_threshold_पूर्णांकerrupt(host, &syncpt->पूर्णांकr.रुको_head,
					  syncpt->id);

	spin_unlock(&syncpt->पूर्णांकr.lock);

	run_handlers(completed);

	वापस empty;
पूर्ण

/*
 * Sync poपूर्णांक threshold पूर्णांकerrupt service thपढ़ो function
 * Handles sync poपूर्णांक threshold triggers, in thपढ़ो context
 */

अटल व्योम syncpt_thresh_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा host1x_syncpt_पूर्णांकr *syncpt_पूर्णांकr =
		container_of(work, काष्ठा host1x_syncpt_पूर्णांकr, work);
	काष्ठा host1x_syncpt *syncpt =
		container_of(syncpt_पूर्णांकr, काष्ठा host1x_syncpt, पूर्णांकr);
	अचिन्हित पूर्णांक id = syncpt->id;
	काष्ठा host1x *host = syncpt->host;

	(व्योम)process_रुको_list(host, syncpt,
				host1x_syncpt_load(host->syncpt + id));
पूर्ण

पूर्णांक host1x_पूर्णांकr_add_action(काष्ठा host1x *host, काष्ठा host1x_syncpt *syncpt,
			   u32 thresh, क्रमागत host1x_पूर्णांकr_action action,
			   व्योम *data, काष्ठा host1x_रुकोlist *रुकोer,
			   व्योम **ref)
अणु
	पूर्णांक queue_was_empty;

	अगर (रुकोer == शून्य) अणु
		pr_warn("%s: NULL waiter\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* initialize a new रुकोer */
	INIT_LIST_HEAD(&रुकोer->list);
	kref_init(&रुकोer->refcount);
	अगर (ref)
		kref_get(&रुकोer->refcount);
	रुकोer->thresh = thresh;
	रुकोer->action = action;
	atomic_set(&रुकोer->state, WLS_PENDING);
	रुकोer->data = data;
	रुकोer->count = 1;

	spin_lock(&syncpt->पूर्णांकr.lock);

	queue_was_empty = list_empty(&syncpt->पूर्णांकr.रुको_head);

	अगर (add_रुकोer_to_queue(रुकोer, &syncpt->पूर्णांकr.रुको_head)) अणु
		/* added at head of list - new threshold value */
		host1x_hw_पूर्णांकr_set_syncpt_threshold(host, syncpt->id, thresh);

		/* added as first रुकोer - enable पूर्णांकerrupt */
		अगर (queue_was_empty)
			host1x_hw_पूर्णांकr_enable_syncpt_पूर्णांकr(host, syncpt->id);
	पूर्ण

	अगर (ref)
		*ref = रुकोer;

	spin_unlock(&syncpt->पूर्णांकr.lock);

	वापस 0;
पूर्ण

व्योम host1x_पूर्णांकr_put_ref(काष्ठा host1x *host, अचिन्हित पूर्णांक id, व्योम *ref,
			 bool flush)
अणु
	काष्ठा host1x_रुकोlist *रुकोer = ref;
	काष्ठा host1x_syncpt *syncpt;

	atomic_cmpxchg(&रुकोer->state, WLS_PENDING, WLS_CANCELLED);

	syncpt = host->syncpt + id;

	spin_lock(&syncpt->पूर्णांकr.lock);
	अगर (atomic_cmpxchg(&रुकोer->state, WLS_CANCELLED, WLS_HANDLED) ==
	    WLS_CANCELLED) अणु
		list_del(&रुकोer->list);
		kref_put(&रुकोer->refcount, रुकोer_release);
	पूर्ण
	spin_unlock(&syncpt->पूर्णांकr.lock);

	अगर (flush) अणु
		/* Wait until any concurrently executing handler has finished. */
		जबतक (atomic_पढ़ो(&रुकोer->state) != WLS_HANDLED)
			schedule();
	पूर्ण

	kref_put(&रुकोer->refcount, रुकोer_release);
पूर्ण

पूर्णांक host1x_पूर्णांकr_init(काष्ठा host1x *host, अचिन्हित पूर्णांक irq_sync)
अणु
	अचिन्हित पूर्णांक id;
	u32 nb_pts = host1x_syncpt_nb_pts(host);

	mutex_init(&host->पूर्णांकr_mutex);
	host->पूर्णांकr_syncpt_irq = irq_sync;

	क्रम (id = 0; id < nb_pts; ++id) अणु
		काष्ठा host1x_syncpt *syncpt = host->syncpt + id;

		spin_lock_init(&syncpt->पूर्णांकr.lock);
		INIT_LIST_HEAD(&syncpt->पूर्णांकr.रुको_head);
		snम_लिखो(syncpt->पूर्णांकr.thresh_irq_name,
			 माप(syncpt->पूर्णांकr.thresh_irq_name),
			 "host1x_sp_%02u", id);
	पूर्ण

	host1x_पूर्णांकr_start(host);

	वापस 0;
पूर्ण

व्योम host1x_पूर्णांकr_deinit(काष्ठा host1x *host)
अणु
	host1x_पूर्णांकr_stop(host);
पूर्ण

व्योम host1x_पूर्णांकr_start(काष्ठा host1x *host)
अणु
	u32 hz = clk_get_rate(host->clk);
	पूर्णांक err;

	mutex_lock(&host->पूर्णांकr_mutex);
	err = host1x_hw_पूर्णांकr_init_host_sync(host, DIV_ROUND_UP(hz, 1000000),
					    syncpt_thresh_work);
	अगर (err) अणु
		mutex_unlock(&host->पूर्णांकr_mutex);
		वापस;
	पूर्ण
	mutex_unlock(&host->पूर्णांकr_mutex);
पूर्ण

व्योम host1x_पूर्णांकr_stop(काष्ठा host1x *host)
अणु
	अचिन्हित पूर्णांक id;
	काष्ठा host1x_syncpt *syncpt = host->syncpt;
	u32 nb_pts = host1x_syncpt_nb_pts(host);

	mutex_lock(&host->पूर्णांकr_mutex);

	host1x_hw_पूर्णांकr_disable_all_syncpt_पूर्णांकrs(host);

	क्रम (id = 0; id < nb_pts; ++id) अणु
		काष्ठा host1x_रुकोlist *रुकोer, *next;

		list_क्रम_each_entry_safe(रुकोer, next,
			&syncpt[id].पूर्णांकr.रुको_head, list) अणु
			अगर (atomic_cmpxchg(&रुकोer->state,
			    WLS_CANCELLED, WLS_HANDLED) == WLS_CANCELLED) अणु
				list_del(&रुकोer->list);
				kref_put(&रुकोer->refcount, रुकोer_release);
			पूर्ण
		पूर्ण

		अगर (!list_empty(&syncpt[id].पूर्णांकr.रुको_head)) अणु
			/* output diagnostics */
			mutex_unlock(&host->पूर्णांकr_mutex);
			pr_warn("%s cannot stop syncpt intr id=%u\n",
				__func__, id);
			वापस;
		पूर्ण
	पूर्ण

	host1x_hw_पूर्णांकr_मुक्त_syncpt_irq(host);

	mutex_unlock(&host->पूर्णांकr_mutex);
पूर्ण
