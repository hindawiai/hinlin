<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tegra host1x Interrupt Management
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#अगर_अघोषित __HOST1X_INTR_H
#घोषणा __HOST1X_INTR_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>

काष्ठा host1x_syncpt;
काष्ठा host1x;

क्रमागत host1x_पूर्णांकr_action अणु
	/*
	 * Perक्रमm cleanup after a submit has completed.
	 * 'data' poपूर्णांकs to a channel
	 */
	HOST1X_INTR_ACTION_SUBMIT_COMPLETE = 0,

	/*
	 * Wake up a  task.
	 * 'data' poपूर्णांकs to a रुको_queue_head_t
	 */
	HOST1X_INTR_ACTION_WAKEUP,

	/*
	 * Wake up a पूर्णांकerruptible task.
	 * 'data' poपूर्णांकs to a रुको_queue_head_t
	 */
	HOST1X_INTR_ACTION_WAKEUP_INTERRUPTIBLE,

	HOST1X_INTR_ACTION_COUNT
पूर्ण;

काष्ठा host1x_syncpt_पूर्णांकr अणु
	spinlock_t lock;
	काष्ठा list_head रुको_head;
	अक्षर thresh_irq_name[12];
	काष्ठा work_काष्ठा work;
पूर्ण;

काष्ठा host1x_रुकोlist अणु
	काष्ठा list_head list;
	काष्ठा kref refcount;
	u32 thresh;
	क्रमागत host1x_पूर्णांकr_action action;
	atomic_t state;
	व्योम *data;
	पूर्णांक count;
पूर्ण;

/*
 * Schedule an action to be taken when a sync poपूर्णांक reaches the given threshold.
 *
 * @id the sync poपूर्णांक
 * @thresh the threshold
 * @action the action to take
 * @data a poपूर्णांकer to extra data depending on action, see above
 * @रुकोer रुकोer काष्ठाure - assumes ownership
 * @ref must be passed अगर cancellation is possible, अन्यथा शून्य
 *
 * This is a non-blocking api.
 */
पूर्णांक host1x_पूर्णांकr_add_action(काष्ठा host1x *host, काष्ठा host1x_syncpt *syncpt,
			   u32 thresh, क्रमागत host1x_पूर्णांकr_action action,
			   व्योम *data, काष्ठा host1x_रुकोlist *रुकोer,
			   व्योम **ref);

/*
 * Unreference an action submitted to host1x_पूर्णांकr_add_action().
 * You must call this अगर you passed non-शून्य as ref.
 * @ref the ref वापसed from host1x_पूर्णांकr_add_action()
 * @flush रुको until any pending handlers have completed beक्रमe वापसing.
 */
व्योम host1x_पूर्णांकr_put_ref(काष्ठा host1x *host, अचिन्हित पूर्णांक id, व्योम *ref,
			 bool flush);

/* Initialize host1x sync poपूर्णांक पूर्णांकerrupt */
पूर्णांक host1x_पूर्णांकr_init(काष्ठा host1x *host, अचिन्हित पूर्णांक irq_sync);

/* Deinitialize host1x sync poपूर्णांक पूर्णांकerrupt */
व्योम host1x_पूर्णांकr_deinit(काष्ठा host1x *host);

/* Enable host1x sync poपूर्णांक पूर्णांकerrupt */
व्योम host1x_पूर्णांकr_start(काष्ठा host1x *host);

/* Disable host1x sync poपूर्णांक पूर्णांकerrupt */
व्योम host1x_पूर्णांकr_stop(काष्ठा host1x *host);

irqवापस_t host1x_syncpt_thresh_fn(व्योम *dev_id);
#पूर्ण_अगर
