<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_BREADCRUMBS_TYPES__
#घोषणा __INTEL_BREADCRUMBS_TYPES__

#समावेश <linux/irq_work.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

/*
 * Rather than have every client रुको upon all user पूर्णांकerrupts,
 * with the herd waking after every पूर्णांकerrupt and each करोing the
 * heavyweight seqno dance, we delegate the task (of being the
 * bottom-half of the user पूर्णांकerrupt) to the first client. After
 * every पूर्णांकerrupt, we wake up one client, who करोes the heavyweight
 * coherent seqno पढ़ो and either goes back to sleep (अगर incomplete),
 * or wakes up all the completed clients in parallel, beक्रमe then
 * transferring the bottom-half status to the next client in the queue.
 *
 * Compared to walking the entire list of रुकोers in a single dedicated
 * bottom-half, we reduce the latency of the first रुकोer by aव्योमing
 * a context चयन, but incur additional coherent seqno पढ़ोs when
 * following the chain of request bपढ़ोcrumbs. Since it is most likely
 * that we have a single client रुकोing on each seqno, then reducing
 * the overhead of waking that client is much preferred.
 */
काष्ठा पूर्णांकel_bपढ़ोcrumbs अणु
	atomic_t active;

	spinlock_t संकेतers_lock; /* protects the list of संकेतers */
	काष्ठा list_head संकेतers;
	काष्ठा llist_head संकेतed_requests;
	atomic_t संकेतer_active;

	spinlock_t irq_lock; /* protects the पूर्णांकerrupt from hardirq context */
	काष्ठा irq_work irq_work; /* क्रम use from inside irq_lock */
	अचिन्हित पूर्णांक irq_enabled;
	bool irq_armed;

	/* Not all bपढ़ोcrumbs are attached to physical HW */
	काष्ठा पूर्णांकel_engine_cs *irq_engine;
पूर्ण;

#पूर्ण_अगर /* __INTEL_BREADCRUMBS_TYPES__ */
