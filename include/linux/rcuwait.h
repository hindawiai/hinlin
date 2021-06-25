<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RCUWAIT_H_
#घोषणा _LINUX_RCUWAIT_H_

#समावेश <linux/rcupdate.h>
#समावेश <linux/sched/संकेत.स>

/*
 * rcuरुको provides a way of blocking and waking up a single
 * task in an rcu-safe manner.
 *
 * The only समय @task is non-nil is when a user is blocked (or
 * checking अगर it needs to) on a condition, and reset as soon as we
 * know that the condition has succeeded and are awoken.
 */
काष्ठा rcuरुको अणु
	काष्ठा task_काष्ठा __rcu *task;
पूर्ण;

#घोषणा __RCUWAIT_INITIALIZER(name)		\
	अणु .task = शून्य, पूर्ण

अटल अंतरभूत व्योम rcuरुको_init(काष्ठा rcuरुको *w)
अणु
	w->task = शून्य;
पूर्ण

/*
 * Note: this provides no serialization and, just as with रुकोqueues,
 * requires care to estimate as to whether or not the रुको is active.
 */
अटल अंतरभूत पूर्णांक rcuरुको_active(काष्ठा rcuरुको *w)
अणु
	वापस !!rcu_access_poपूर्णांकer(w->task);
पूर्ण

बाह्य पूर्णांक rcuरुको_wake_up(काष्ठा rcuरुको *w);

/*
 * The caller is responsible क्रम locking around rcuरुको_रुको_event(),
 * and [prepare_to/finish]_rcuरुको() such that ग_लिखोs to @task are
 * properly serialized.
 */

अटल अंतरभूत व्योम prepare_to_rcuरुको(काष्ठा rcuरुको *w)
अणु
	rcu_assign_poपूर्णांकer(w->task, current);
पूर्ण

अटल अंतरभूत व्योम finish_rcuरुको(काष्ठा rcuरुको *w)
अणु
        rcu_assign_poपूर्णांकer(w->task, शून्य);
	__set_current_state(TASK_RUNNING);
पूर्ण

#घोषणा rcuरुको_रुको_event(w, condition, state)				\
(अणु									\
	पूर्णांक __ret = 0;							\
	prepare_to_rcuरुको(w);						\
	क्रम (;;) अणु							\
		/*							\
		 * Implicit barrier (A) pairs with (B) in		\
		 * rcuरुको_wake_up().					\
		 */							\
		set_current_state(state);				\
		अगर (condition)						\
			अवरोध;						\
									\
		अगर (संकेत_pending_state(state, current)) अणु		\
			__ret = -EINTR;					\
			अवरोध;						\
		पूर्ण							\
									\
		schedule();						\
	पूर्ण								\
	finish_rcuरुको(w);						\
	__ret;								\
पूर्ण)

#पूर्ण_अगर /* _LINUX_RCUWAIT_H_ */
