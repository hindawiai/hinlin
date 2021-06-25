<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SWAIT_H
#घोषणा _LINUX_SWAIT_H

#समावेश <linux/list.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/current.h>

/*
 * Simple रुकोqueues are semantically very dअगरferent to regular रुको queues
 * (रुको.h). The most important dअगरference is that the simple रुकोqueue allows
 * क्रम deterministic behaviour -- IOW it has strictly bounded IRQ and lock hold
 * बार.
 *
 * Mainly, this is accomplished by two things. Firstly not allowing swake_up_all
 * from IRQ disabled, and dropping the lock upon every wakeup, giving a higher
 * priority task a chance to run.
 *
 * Secondly, we had to drop a fair number of features of the other रुकोqueue
 * code; notably:
 *
 *  - mixing INTERRUPTIBLE and UNINTERRUPTIBLE sleeps on the same रुकोqueue;
 *    all wakeups are TASK_NORMAL in order to aव्योम O(n) lookups क्रम the right
 *    sleeper state.
 *
 *  - the !exclusive mode; because that leads to O(n) wakeups, everything is
 *    exclusive. As such swake_up_one will only ever awake _one_ रुकोer.
 *
 *  - custom wake callback functions; because you cannot give any guarantees
 *    about अक्रमom code. This also allows sरुको to be used in RT, such that
 *    raw spinlock can be used क्रम the sरुको queue head.
 *
 * As a side effect of these; the data काष्ठाures are slimmer albeit more ad-hoc.
 * For all the above, note that simple रुको queues should _only_ be used under
 * very specअगरic realसमय स्थिरraपूर्णांकs -- it is best to stick with the regular
 * रुको queues in most हालs.
 */

काष्ठा task_काष्ठा;

काष्ठा sरुको_queue_head अणु
	raw_spinlock_t		lock;
	काष्ठा list_head	task_list;
पूर्ण;

काष्ठा sरुको_queue अणु
	काष्ठा task_काष्ठा	*task;
	काष्ठा list_head	task_list;
पूर्ण;

#घोषणा __SWAITQUEUE_INITIALIZER(name) अणु				\
	.task		= current,					\
	.task_list	= LIST_HEAD_INIT((name).task_list),		\
पूर्ण

#घोषणा DECLARE_SWAITQUEUE(name)					\
	काष्ठा sरुको_queue name = __SWAITQUEUE_INITIALIZER(name)

#घोषणा __SWAIT_QUEUE_HEAD_INITIALIZER(name) अणु				\
	.lock		= __RAW_SPIN_LOCK_UNLOCKED(name.lock),		\
	.task_list	= LIST_HEAD_INIT((name).task_list),		\
पूर्ण

#घोषणा DECLARE_SWAIT_QUEUE_HEAD(name)					\
	काष्ठा sरुको_queue_head name = __SWAIT_QUEUE_HEAD_INITIALIZER(name)

बाह्य व्योम __init_sरुको_queue_head(काष्ठा sरुको_queue_head *q, स्थिर अक्षर *name,
				    काष्ठा lock_class_key *key);

#घोषणा init_sरुको_queue_head(q)				\
	करो अणु							\
		अटल काष्ठा lock_class_key __key;		\
		__init_sरुको_queue_head((q), #q, &__key);	\
	पूर्ण जबतक (0)

#अगर_घोषित CONFIG_LOCKDEP
# define __SWAIT_QUEUE_HEAD_INIT_ONSTACK(name)			\
	(अणु init_sरुको_queue_head(&name); name; पूर्ण)
# define DECLARE_SWAIT_QUEUE_HEAD_ONSTACK(name)			\
	काष्ठा sरुको_queue_head name = __SWAIT_QUEUE_HEAD_INIT_ONSTACK(name)
#अन्यथा
# define DECLARE_SWAIT_QUEUE_HEAD_ONSTACK(name)			\
	DECLARE_SWAIT_QUEUE_HEAD(name)
#पूर्ण_अगर

/**
 * sरुको_active -- locklessly test क्रम रुकोers on the queue
 * @wq: the रुकोqueue to test क्रम रुकोers
 *
 * वापसs true अगर the रुको list is not empty
 *
 * NOTE: this function is lockless and requires care, incorrect usage _will_
 * lead to sporadic and non-obvious failure.
 *
 * NOTE2: this function has the same above implications as regular रुकोqueues.
 *
 * Use either जबतक holding sरुको_queue_head::lock or when used क्रम wakeups
 * with an extra smp_mb() like:
 *
 *      CPU0 - waker                    CPU1 - रुकोer
 *
 *                                      क्रम (;;) अणु
 *      @cond = true;                     prepare_to_sरुको_exclusive(&wq_head, &रुको, state);
 *      smp_mb();                         // smp_mb() from set_current_state()
 *      अगर (sरुको_active(wq_head))        अगर (@cond)
 *        wake_up(wq_head);                      अवरोध;
 *                                        schedule();
 *                                      पूर्ण
 *                                      finish_sरुको(&wq_head, &रुको);
 *
 * Because without the explicit smp_mb() it's possible क्रम the
 * sरुको_active() load to get hoisted over the @cond store such that we'll
 * observe an empty रुको list जबतक the रुकोer might not observe @cond.
 * This, in turn, can trigger missing wakeups.
 *
 * Also note that this 'optimization' trades a spin_lock() क्रम an smp_mb(),
 * which (when the lock is uncontended) are of roughly equal cost.
 */
अटल अंतरभूत पूर्णांक sरुको_active(काष्ठा sरुको_queue_head *wq)
अणु
	वापस !list_empty(&wq->task_list);
पूर्ण

/**
 * swq_has_sleeper - check अगर there are any रुकोing processes
 * @wq: the रुकोqueue to test क्रम रुकोers
 *
 * Returns true अगर @wq has रुकोing processes
 *
 * Please refer to the comment क्रम sरुको_active.
 */
अटल अंतरभूत bool swq_has_sleeper(काष्ठा sरुको_queue_head *wq)
अणु
	/*
	 * We need to be sure we are in sync with the list_add()
	 * modअगरications to the रुको queue (task_list).
	 *
	 * This memory barrier should be paired with one on the
	 * रुकोing side.
	 */
	smp_mb();
	वापस sरुको_active(wq);
पूर्ण

बाह्य व्योम swake_up_one(काष्ठा sरुको_queue_head *q);
बाह्य व्योम swake_up_all(काष्ठा sरुको_queue_head *q);
बाह्य व्योम swake_up_locked(काष्ठा sरुको_queue_head *q);

बाह्य व्योम prepare_to_sरुको_exclusive(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको, पूर्णांक state);
बाह्य दीर्घ prepare_to_sरुको_event(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको, पूर्णांक state);

बाह्य व्योम __finish_sरुको(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको);
बाह्य व्योम finish_sरुको(काष्ठा sरुको_queue_head *q, काष्ठा sरुको_queue *रुको);

/* as per ___रुको_event() but क्रम sरुको, thereक्रमe "exclusive == 1" */
#घोषणा ___sरुको_event(wq, condition, state, ret, cmd)			\
(अणु									\
	__label__ __out;						\
	काष्ठा sरुको_queue __रुको;					\
	दीर्घ __ret = ret;						\
									\
	INIT_LIST_HEAD(&__रुको.task_list);				\
	क्रम (;;) अणु							\
		दीर्घ __पूर्णांक = prepare_to_sरुको_event(&wq, &__रुको, state);\
									\
		अगर (condition)						\
			अवरोध;						\
									\
		अगर (___रुको_is_पूर्णांकerruptible(state) && __पूर्णांक) अणु		\
			__ret = __पूर्णांक;					\
			जाओ __out;					\
		पूर्ण							\
									\
		cmd;							\
	पूर्ण								\
	finish_sरुको(&wq, &__रुको);					\
__out:	__ret;								\
पूर्ण)

#घोषणा __sरुको_event(wq, condition)					\
	(व्योम)___sरुको_event(wq, condition, TASK_UNINTERRUPTIBLE, 0,	\
			    schedule())

#घोषणा sरुको_event_exclusive(wq, condition)				\
करो अणु									\
	अगर (condition)							\
		अवरोध;							\
	__sरुको_event(wq, condition);					\
पूर्ण जबतक (0)

#घोषणा __sरुको_event_समयout(wq, condition, समयout)			\
	___sरुको_event(wq, ___रुको_cond_समयout(condition),		\
		      TASK_UNINTERRUPTIBLE, समयout,			\
		      __ret = schedule_समयout(__ret))

#घोषणा sरुको_event_समयout_exclusive(wq, condition, समयout)		\
(अणु									\
	दीर्घ __ret = समयout;						\
	अगर (!___रुको_cond_समयout(condition))				\
		__ret = __sरुको_event_समयout(wq, condition, समयout);	\
	__ret;								\
पूर्ण)

#घोषणा __sरुको_event_पूर्णांकerruptible(wq, condition)			\
	___sरुको_event(wq, condition, TASK_INTERRUPTIBLE, 0,		\
		      schedule())

#घोषणा sरुको_event_पूर्णांकerruptible_exclusive(wq, condition)		\
(अणु									\
	पूर्णांक __ret = 0;							\
	अगर (!(condition))						\
		__ret = __sरुको_event_पूर्णांकerruptible(wq, condition);	\
	__ret;								\
पूर्ण)

#घोषणा __sरुको_event_पूर्णांकerruptible_समयout(wq, condition, समयout)	\
	___sरुको_event(wq, ___रुको_cond_समयout(condition),		\
		      TASK_INTERRUPTIBLE, समयout,			\
		      __ret = schedule_समयout(__ret))

#घोषणा sरुको_event_पूर्णांकerruptible_समयout_exclusive(wq, condition, समयout)\
(अणु									\
	दीर्घ __ret = समयout;						\
	अगर (!___रुको_cond_समयout(condition))				\
		__ret = __sरुको_event_पूर्णांकerruptible_समयout(wq,		\
						condition, समयout);	\
	__ret;								\
पूर्ण)

#घोषणा __sरुको_event_idle(wq, condition)				\
	(व्योम)___sरुको_event(wq, condition, TASK_IDLE, 0, schedule())

/**
 * sरुको_event_idle_exclusive - रुको without प्रणाली load contribution
 * @wq: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_IDLE) until the @condition evaluates to
 * true. The @condition is checked each समय the रुकोqueue @wq is woken up.
 *
 * This function is mostly used when a kthपढ़ो or workqueue रुकोs क्रम some
 * condition and करोesn't want to contribute to प्रणाली load. Signals are
 * ignored.
 */
#घोषणा sरुको_event_idle_exclusive(wq, condition)			\
करो अणु									\
	अगर (condition)							\
		अवरोध;							\
	__sरुको_event_idle(wq, condition);				\
पूर्ण जबतक (0)

#घोषणा __sरुको_event_idle_समयout(wq, condition, समयout)		\
	___sरुको_event(wq, ___रुको_cond_समयout(condition),		\
		       TASK_IDLE, समयout,				\
		       __ret = schedule_समयout(__ret))

/**
 * sरुको_event_idle_समयout_exclusive - रुको up to समयout without load contribution
 * @wq: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @समयout: समयout at which we'll give up in jअगरfies
 *
 * The process is put to sleep (TASK_IDLE) until the @condition evaluates to
 * true. The @condition is checked each समय the रुकोqueue @wq is woken up.
 *
 * This function is mostly used when a kthपढ़ो or workqueue रुकोs क्रम some
 * condition and करोesn't want to contribute to प्रणाली load. Signals are
 * ignored.
 *
 * Returns:
 * 0 अगर the @condition evaluated to %false after the @समयout elapsed,
 * 1 अगर the @condition evaluated to %true after the @समयout elapsed,
 * or the reमुख्यing jअगरfies (at least 1) अगर the @condition evaluated
 * to %true beक्रमe the @समयout elapsed.
 */
#घोषणा sरुको_event_idle_समयout_exclusive(wq, condition, समयout)	\
(अणु									\
	दीर्घ __ret = समयout;						\
	अगर (!___रुको_cond_समयout(condition))				\
		__ret = __sरुको_event_idle_समयout(wq,			\
						   condition, समयout);	\
	__ret;								\
पूर्ण)

#पूर्ण_अगर /* _LINUX_SWAIT_H */
