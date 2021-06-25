<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_WAKE_Q_H
#घोषणा _LINUX_SCHED_WAKE_Q_H

/*
 * Wake-queues are lists of tasks with a pending wakeup, whose
 * callers have alपढ़ोy marked the task as woken पूर्णांकernally,
 * and can thus carry on. A common use हाल is being able to
 * करो the wakeups once the corresponding user lock as been
 * released.
 *
 * We hold reference to each task in the list across the wakeup,
 * thus guaranteeing that the memory is still valid by the समय
 * the actual wakeups are perक्रमmed in wake_up_q().
 *
 * One per task suffices, because there's never a need क्रम a task to be
 * in two wake queues simultaneously; it is क्रमbidden to abanकरोn a task
 * in a wake queue (a call to wake_up_q() _must_ follow), so अगर a task is
 * alपढ़ोy in a wake queue, the wakeup will happen soon and the second
 * waker can just skip it.
 *
 * The DEFINE_WAKE_Q macro declares and initializes the list head.
 * wake_up_q() करोes NOT reinitialize the list; it's expected to be
 * called near the end of a function. Otherwise, the list can be
 * re-initialized क्रम later re-use by wake_q_init().
 *
 * NOTE that this can cause spurious wakeups. schedule() callers
 * must ensure the call is करोne inside a loop, confirming that the
 * wakeup condition has in fact occurred.
 *
 * NOTE that there is no guarantee the wakeup will happen any later than the
 * wake_q_add() location. Thereक्रमe task must be पढ़ोy to be woken at the
 * location of the wake_q_add().
 */

#समावेश <linux/sched.h>

काष्ठा wake_q_head अणु
	काष्ठा wake_q_node *first;
	काष्ठा wake_q_node **lastp;
पूर्ण;

#घोषणा WAKE_Q_TAIL ((काष्ठा wake_q_node *) 0x01)

#घोषणा DEFINE_WAKE_Q(name)				\
	काष्ठा wake_q_head name = अणु WAKE_Q_TAIL, &name.first पूर्ण

अटल अंतरभूत व्योम wake_q_init(काष्ठा wake_q_head *head)
अणु
	head->first = WAKE_Q_TAIL;
	head->lastp = &head->first;
पूर्ण

अटल अंतरभूत bool wake_q_empty(काष्ठा wake_q_head *head)
अणु
	वापस head->first == WAKE_Q_TAIL;
पूर्ण

बाह्य व्योम wake_q_add(काष्ठा wake_q_head *head, काष्ठा task_काष्ठा *task);
बाह्य व्योम wake_q_add_safe(काष्ठा wake_q_head *head, काष्ठा task_काष्ठा *task);
बाह्य व्योम wake_up_q(काष्ठा wake_q_head *head);

#पूर्ण_अगर /* _LINUX_SCHED_WAKE_Q_H */
