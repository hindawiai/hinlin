<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_WAIT_H
#घोषणा _LINUX_WAIT_H
/*
 * Linux रुको queue related types and methods
 */
#समावेश <linux/list.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/spinlock.h>

#समावेश <यंत्र/current.h>
#समावेश <uapi/linux/रुको.h>

प्रकार काष्ठा रुको_queue_entry रुको_queue_entry_t;

प्रकार पूर्णांक (*रुको_queue_func_t)(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, पूर्णांक flags, व्योम *key);
पूर्णांक शेष_wake_function(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, पूर्णांक flags, व्योम *key);

/* रुको_queue_entry::flags */
#घोषणा WQ_FLAG_EXCLUSIVE	0x01
#घोषणा WQ_FLAG_WOKEN		0x02
#घोषणा WQ_FLAG_BOOKMARK	0x04
#घोषणा WQ_FLAG_CUSTOM		0x08
#घोषणा WQ_FLAG_DONE		0x10
#घोषणा WQ_FLAG_PRIORITY	0x20

/*
 * A single रुको-queue entry काष्ठाure:
 */
काष्ठा रुको_queue_entry अणु
	अचिन्हित पूर्णांक		flags;
	व्योम			*निजी;
	रुको_queue_func_t	func;
	काष्ठा list_head	entry;
पूर्ण;

काष्ठा रुको_queue_head अणु
	spinlock_t		lock;
	काष्ठा list_head	head;
पूर्ण;
प्रकार काष्ठा रुको_queue_head रुको_queue_head_t;

काष्ठा task_काष्ठा;

/*
 * Macros क्रम declaration and initialisaton of the datatypes
 */

#घोषणा __WAITQUEUE_INITIALIZER(name, tsk) अणु					\
	.निजी	= tsk,							\
	.func		= शेष_wake_function,				\
	.entry		= अणु शून्य, शून्य पूर्ण पूर्ण

#घोषणा DECLARE_WAITQUEUE(name, tsk)						\
	काष्ठा रुको_queue_entry name = __WAITQUEUE_INITIALIZER(name, tsk)

#घोषणा __WAIT_QUEUE_HEAD_INITIALIZER(name) अणु					\
	.lock		= __SPIN_LOCK_UNLOCKED(name.lock),			\
	.head		= अणु &(name).head, &(name).head पूर्ण पूर्ण

#घोषणा DECLARE_WAIT_QUEUE_HEAD(name) \
	काष्ठा रुको_queue_head name = __WAIT_QUEUE_HEAD_INITIALIZER(name)

बाह्य व्योम __init_रुकोqueue_head(काष्ठा रुको_queue_head *wq_head, स्थिर अक्षर *name, काष्ठा lock_class_key *);

#घोषणा init_रुकोqueue_head(wq_head)						\
	करो अणु									\
		अटल काष्ठा lock_class_key __key;				\
										\
		__init_रुकोqueue_head((wq_head), #wq_head, &__key);		\
	पूर्ण जबतक (0)

#अगर_घोषित CONFIG_LOCKDEP
# define __WAIT_QUEUE_HEAD_INIT_ONSTACK(name) \
	(अणु init_रुकोqueue_head(&name); name; पूर्ण)
# define DECLARE_WAIT_QUEUE_HEAD_ONSTACK(name) \
	काष्ठा रुको_queue_head name = __WAIT_QUEUE_HEAD_INIT_ONSTACK(name)
#अन्यथा
# define DECLARE_WAIT_QUEUE_HEAD_ONSTACK(name) DECLARE_WAIT_QUEUE_HEAD(name)
#पूर्ण_अगर

अटल अंतरभूत व्योम init_रुकोqueue_entry(काष्ठा रुको_queue_entry *wq_entry, काष्ठा task_काष्ठा *p)
अणु
	wq_entry->flags		= 0;
	wq_entry->निजी	= p;
	wq_entry->func		= शेष_wake_function;
पूर्ण

अटल अंतरभूत व्योम
init_रुकोqueue_func_entry(काष्ठा रुको_queue_entry *wq_entry, रुको_queue_func_t func)
अणु
	wq_entry->flags		= 0;
	wq_entry->निजी	= शून्य;
	wq_entry->func		= func;
पूर्ण

/**
 * रुकोqueue_active -- locklessly test क्रम रुकोers on the queue
 * @wq_head: the रुकोqueue to test क्रम रुकोers
 *
 * वापसs true अगर the रुको list is not empty
 *
 * NOTE: this function is lockless and requires care, incorrect usage _will_
 * lead to sporadic and non-obvious failure.
 *
 * Use either जबतक holding रुको_queue_head::lock or when used क्रम wakeups
 * with an extra smp_mb() like::
 *
 *      CPU0 - waker                    CPU1 - रुकोer
 *
 *                                      क्रम (;;) अणु
 *      @cond = true;                     prepare_to_रुको(&wq_head, &रुको, state);
 *      smp_mb();                         // smp_mb() from set_current_state()
 *      अगर (रुकोqueue_active(wq_head))         अगर (@cond)
 *        wake_up(wq_head);                      अवरोध;
 *                                        schedule();
 *                                      पूर्ण
 *                                      finish_रुको(&wq_head, &रुको);
 *
 * Because without the explicit smp_mb() it's possible क्रम the
 * रुकोqueue_active() load to get hoisted over the @cond store such that we'll
 * observe an empty रुको list जबतक the रुकोer might not observe @cond.
 *
 * Also note that this 'optimization' trades a spin_lock() क्रम an smp_mb(),
 * which (when the lock is uncontended) are of roughly equal cost.
 */
अटल अंतरभूत पूर्णांक रुकोqueue_active(काष्ठा रुको_queue_head *wq_head)
अणु
	वापस !list_empty(&wq_head->head);
पूर्ण

/**
 * wq_has_single_sleeper - check अगर there is only one sleeper
 * @wq_head: रुको queue head
 *
 * Returns true of wq_head has only one sleeper on the list.
 *
 * Please refer to the comment क्रम रुकोqueue_active.
 */
अटल अंतरभूत bool wq_has_single_sleeper(काष्ठा रुको_queue_head *wq_head)
अणु
	वापस list_is_singular(&wq_head->head);
पूर्ण

/**
 * wq_has_sleeper - check अगर there are any रुकोing processes
 * @wq_head: रुको queue head
 *
 * Returns true अगर wq_head has रुकोing processes
 *
 * Please refer to the comment क्रम रुकोqueue_active.
 */
अटल अंतरभूत bool wq_has_sleeper(काष्ठा रुको_queue_head *wq_head)
अणु
	/*
	 * We need to be sure we are in sync with the
	 * add_रुको_queue modअगरications to the रुको queue.
	 *
	 * This memory barrier should be paired with one on the
	 * रुकोing side.
	 */
	smp_mb();
	वापस रुकोqueue_active(wq_head);
पूर्ण

बाह्य व्योम add_रुको_queue(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry);
बाह्य व्योम add_रुको_queue_exclusive(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry);
बाह्य व्योम add_रुको_queue_priority(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry);
बाह्य व्योम हटाओ_रुको_queue(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry);

अटल अंतरभूत व्योम __add_रुको_queue(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	काष्ठा list_head *head = &wq_head->head;
	काष्ठा रुको_queue_entry *wq;

	list_क्रम_each_entry(wq, &wq_head->head, entry) अणु
		अगर (!(wq->flags & WQ_FLAG_PRIORITY))
			अवरोध;
		head = &wq->entry;
	पूर्ण
	list_add(&wq_entry->entry, head);
पूर्ण

/*
 * Used क्रम wake-one thपढ़ोs:
 */
अटल अंतरभूत व्योम
__add_रुको_queue_exclusive(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	wq_entry->flags |= WQ_FLAG_EXCLUSIVE;
	__add_रुको_queue(wq_head, wq_entry);
पूर्ण

अटल अंतरभूत व्योम __add_रुको_queue_entry_tail(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	list_add_tail(&wq_entry->entry, &wq_head->head);
पूर्ण

अटल अंतरभूत व्योम
__add_रुको_queue_entry_tail_exclusive(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	wq_entry->flags |= WQ_FLAG_EXCLUSIVE;
	__add_रुको_queue_entry_tail(wq_head, wq_entry);
पूर्ण

अटल अंतरभूत व्योम
__हटाओ_रुको_queue(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry)
अणु
	list_del(&wq_entry->entry);
पूर्ण

व्योम __wake_up(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode, पूर्णांक nr, व्योम *key);
व्योम __wake_up_locked_key(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode, व्योम *key);
व्योम __wake_up_locked_key_bookmark(काष्ठा रुको_queue_head *wq_head,
		अचिन्हित पूर्णांक mode, व्योम *key, रुको_queue_entry_t *bookmark);
व्योम __wake_up_sync_key(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode, व्योम *key);
व्योम __wake_up_locked_sync_key(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode, व्योम *key);
व्योम __wake_up_locked(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode, पूर्णांक nr);
व्योम __wake_up_sync(काष्ठा रुको_queue_head *wq_head, अचिन्हित पूर्णांक mode);

#घोषणा wake_up(x)			__wake_up(x, TASK_NORMAL, 1, शून्य)
#घोषणा wake_up_nr(x, nr)		__wake_up(x, TASK_NORMAL, nr, शून्य)
#घोषणा wake_up_all(x)			__wake_up(x, TASK_NORMAL, 0, शून्य)
#घोषणा wake_up_locked(x)		__wake_up_locked((x), TASK_NORMAL, 1)
#घोषणा wake_up_all_locked(x)		__wake_up_locked((x), TASK_NORMAL, 0)

#घोषणा wake_up_पूर्णांकerruptible(x)	__wake_up(x, TASK_INTERRUPTIBLE, 1, शून्य)
#घोषणा wake_up_पूर्णांकerruptible_nr(x, nr)	__wake_up(x, TASK_INTERRUPTIBLE, nr, शून्य)
#घोषणा wake_up_पूर्णांकerruptible_all(x)	__wake_up(x, TASK_INTERRUPTIBLE, 0, शून्य)
#घोषणा wake_up_पूर्णांकerruptible_sync(x)	__wake_up_sync((x), TASK_INTERRUPTIBLE)

/*
 * Wakeup macros to be used to report events to the tarमाला_लो.
 */
#घोषणा poll_to_key(m) ((व्योम *)(__क्रमce uपूर्णांकptr_t)(__poll_t)(m))
#घोषणा key_to_poll(m) ((__क्रमce __poll_t)(uपूर्णांकptr_t)(व्योम *)(m))
#घोषणा wake_up_poll(x, m)							\
	__wake_up(x, TASK_NORMAL, 1, poll_to_key(m))
#घोषणा wake_up_locked_poll(x, m)						\
	__wake_up_locked_key((x), TASK_NORMAL, poll_to_key(m))
#घोषणा wake_up_पूर्णांकerruptible_poll(x, m)					\
	__wake_up(x, TASK_INTERRUPTIBLE, 1, poll_to_key(m))
#घोषणा wake_up_पूर्णांकerruptible_sync_poll(x, m)					\
	__wake_up_sync_key((x), TASK_INTERRUPTIBLE, poll_to_key(m))
#घोषणा wake_up_पूर्णांकerruptible_sync_poll_locked(x, m)				\
	__wake_up_locked_sync_key((x), TASK_INTERRUPTIBLE, poll_to_key(m))

#घोषणा ___रुको_cond_समयout(condition)						\
(अणु										\
	bool __cond = (condition);						\
	अगर (__cond && !__ret)							\
		__ret = 1;							\
	__cond || !__ret;							\
पूर्ण)

#घोषणा ___रुको_is_पूर्णांकerruptible(state)						\
	(!__builtin_स्थिरant_p(state) ||					\
		state == TASK_INTERRUPTIBLE || state == TASK_KILLABLE)		\

बाह्य व्योम init_रुको_entry(काष्ठा रुको_queue_entry *wq_entry, पूर्णांक flags);

/*
 * The below macro ___रुको_event() has an explicit shaकरोw of the __ret
 * variable when used from the रुको_event_*() macros.
 *
 * This is so that both can use the ___रुको_cond_समयout() स्थिरruct
 * to wrap the condition.
 *
 * The type inconsistency of the रुको_event_*() __ret variable is also
 * on purpose; we use दीर्घ where we can वापस समयout values and पूर्णांक
 * otherwise.
 */

#घोषणा ___रुको_event(wq_head, condition, state, exclusive, ret, cmd)		\
(अणु										\
	__label__ __out;							\
	काष्ठा रुको_queue_entry __wq_entry;					\
	दीर्घ __ret = ret;	/* explicit shaकरोw */				\
										\
	init_रुको_entry(&__wq_entry, exclusive ? WQ_FLAG_EXCLUSIVE : 0);	\
	क्रम (;;) अणु								\
		दीर्घ __पूर्णांक = prepare_to_रुको_event(&wq_head, &__wq_entry, state);\
										\
		अगर (condition)							\
			अवरोध;							\
										\
		अगर (___रुको_is_पूर्णांकerruptible(state) && __पूर्णांक) अणु			\
			__ret = __पूर्णांक;						\
			जाओ __out;						\
		पूर्ण								\
										\
		cmd;								\
	पूर्ण									\
	finish_रुको(&wq_head, &__wq_entry);					\
__out:	__ret;									\
पूर्ण)

#घोषणा __रुको_event(wq_head, condition)					\
	(व्योम)___रुको_event(wq_head, condition, TASK_UNINTERRUPTIBLE, 0, 0,	\
			    schedule())

/**
 * रुको_event - sleep until a condition माला_लो true
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_UNINTERRUPTIBLE) until the
 * @condition evaluates to true. The @condition is checked each समय
 * the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 */
#घोषणा रुको_event(wq_head, condition)						\
करो अणु										\
	might_sleep();								\
	अगर (condition)								\
		अवरोध;								\
	__रुको_event(wq_head, condition);					\
पूर्ण जबतक (0)

#घोषणा __io_रुको_event(wq_head, condition)					\
	(व्योम)___रुको_event(wq_head, condition, TASK_UNINTERRUPTIBLE, 0, 0,	\
			    io_schedule())

/*
 * io_रुको_event() -- like रुको_event() but with io_schedule()
 */
#घोषणा io_रुको_event(wq_head, condition)					\
करो अणु										\
	might_sleep();								\
	अगर (condition)								\
		अवरोध;								\
	__io_रुको_event(wq_head, condition);					\
पूर्ण जबतक (0)

#घोषणा __रुको_event_मुक्तzable(wq_head, condition)				\
	___रुको_event(wq_head, condition, TASK_INTERRUPTIBLE, 0, 0,		\
			    मुक्तzable_schedule())

/**
 * रुको_event_मुक्तzable - sleep (or मुक्तze) until a condition माला_लो true
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE -- so as not to contribute
 * to प्रणाली load) until the @condition evaluates to true. The
 * @condition is checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 */
#घोषणा रुको_event_मुक्तzable(wq_head, condition)				\
(अणु										\
	पूर्णांक __ret = 0;								\
	might_sleep();								\
	अगर (!(condition))							\
		__ret = __रुको_event_मुक्तzable(wq_head, condition);		\
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_समयout(wq_head, condition, समयout)			\
	___रुको_event(wq_head, ___रुको_cond_समयout(condition),			\
		      TASK_UNINTERRUPTIBLE, 0, समयout,				\
		      __ret = schedule_समयout(__ret))

/**
 * रुको_event_समयout - sleep until a condition माला_लो true or a समयout elapses
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @समयout: समयout, in jअगरfies
 *
 * The process is put to sleep (TASK_UNINTERRUPTIBLE) until the
 * @condition evaluates to true. The @condition is checked each समय
 * the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * Returns:
 * 0 अगर the @condition evaluated to %false after the @समयout elapsed,
 * 1 अगर the @condition evaluated to %true after the @समयout elapsed,
 * or the reमुख्यing jअगरfies (at least 1) अगर the @condition evaluated
 * to %true beक्रमe the @समयout elapsed.
 */
#घोषणा रुको_event_समयout(wq_head, condition, समयout)				\
(अणु										\
	दीर्घ __ret = समयout;							\
	might_sleep();								\
	अगर (!___रुको_cond_समयout(condition))					\
		__ret = __रुको_event_समयout(wq_head, condition, समयout);	\
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_मुक्तzable_समयout(wq_head, condition, समयout)		\
	___रुको_event(wq_head, ___रुको_cond_समयout(condition),			\
		      TASK_INTERRUPTIBLE, 0, समयout,				\
		      __ret = मुक्तzable_schedule_समयout(__ret))

/*
 * like रुको_event_समयout() -- except it uses TASK_INTERRUPTIBLE to aव्योम
 * increasing load and is मुक्तzable.
 */
#घोषणा रुको_event_मुक्तzable_समयout(wq_head, condition, समयout)		\
(अणु										\
	दीर्घ __ret = समयout;							\
	might_sleep();								\
	अगर (!___रुको_cond_समयout(condition))					\
		__ret = __रुको_event_मुक्तzable_समयout(wq_head, condition, समयout); \
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_exclusive_cmd(wq_head, condition, cmd1, cmd2)		\
	(व्योम)___रुको_event(wq_head, condition, TASK_UNINTERRUPTIBLE, 1, 0,	\
			    cmd1; schedule(); cmd2)
/*
 * Just like रुको_event_cmd(), except it sets exclusive flag
 */
#घोषणा रुको_event_exclusive_cmd(wq_head, condition, cmd1, cmd2)		\
करो अणु										\
	अगर (condition)								\
		अवरोध;								\
	__रुको_event_exclusive_cmd(wq_head, condition, cmd1, cmd2);		\
पूर्ण जबतक (0)

#घोषणा __रुको_event_cmd(wq_head, condition, cmd1, cmd2)			\
	(व्योम)___रुको_event(wq_head, condition, TASK_UNINTERRUPTIBLE, 0, 0,	\
			    cmd1; schedule(); cmd2)

/**
 * रुको_event_cmd - sleep until a condition माला_लो true
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @cmd1: the command will be executed beक्रमe sleep
 * @cmd2: the command will be executed after sleep
 *
 * The process is put to sleep (TASK_UNINTERRUPTIBLE) until the
 * @condition evaluates to true. The @condition is checked each समय
 * the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 */
#घोषणा रुको_event_cmd(wq_head, condition, cmd1, cmd2)				\
करो अणु										\
	अगर (condition)								\
		अवरोध;								\
	__रुको_event_cmd(wq_head, condition, cmd1, cmd2);			\
पूर्ण जबतक (0)

#घोषणा __रुको_event_पूर्णांकerruptible(wq_head, condition)				\
	___रुको_event(wq_head, condition, TASK_INTERRUPTIBLE, 0, 0,		\
		      schedule())

/**
 * रुको_event_पूर्णांकerruptible - sleep until a condition माला_लो true
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * The function will वापस -ERESTARTSYS अगर it was पूर्णांकerrupted by a
 * संकेत and 0 अगर @condition evaluated to true.
 */
#घोषणा रुको_event_पूर्णांकerruptible(wq_head, condition)				\
(अणु										\
	पूर्णांक __ret = 0;								\
	might_sleep();								\
	अगर (!(condition))							\
		__ret = __रुको_event_पूर्णांकerruptible(wq_head, condition);		\
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_पूर्णांकerruptible_समयout(wq_head, condition, समयout)		\
	___रुको_event(wq_head, ___रुको_cond_समयout(condition),			\
		      TASK_INTERRUPTIBLE, 0, समयout,				\
		      __ret = schedule_समयout(__ret))

/**
 * रुको_event_पूर्णांकerruptible_समयout - sleep until a condition माला_लो true or a समयout elapses
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @समयout: समयout, in jअगरfies
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * Returns:
 * 0 अगर the @condition evaluated to %false after the @समयout elapsed,
 * 1 अगर the @condition evaluated to %true after the @समयout elapsed,
 * the reमुख्यing jअगरfies (at least 1) अगर the @condition evaluated
 * to %true beक्रमe the @समयout elapsed, or -%ERESTARTSYS अगर it was
 * पूर्णांकerrupted by a संकेत.
 */
#घोषणा रुको_event_पूर्णांकerruptible_समयout(wq_head, condition, समयout)		\
(अणु										\
	दीर्घ __ret = समयout;							\
	might_sleep();								\
	अगर (!___रुको_cond_समयout(condition))					\
		__ret = __रुको_event_पूर्णांकerruptible_समयout(wq_head,		\
						condition, समयout);		\
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_hrसमयout(wq_head, condition, समयout, state)		\
(अणु										\
	पूर्णांक __ret = 0;								\
	काष्ठा hrसमयr_sleeper __t;						\
										\
	hrसमयr_init_sleeper_on_stack(&__t, CLOCK_MONOTONIC,			\
				      HRTIMER_MODE_REL);			\
	अगर ((समयout) != KTIME_MAX)						\
		hrसमयr_start_range_ns(&__t.समयr, समयout,			\
				       current->समयr_slack_ns,			\
				       HRTIMER_MODE_REL);			\
										\
	__ret = ___रुको_event(wq_head, condition, state, 0, 0,			\
		अगर (!__t.task) अणु						\
			__ret = -ETIME;						\
			अवरोध;							\
		पूर्ण								\
		schedule());							\
										\
	hrसमयr_cancel(&__t.समयr);						\
	destroy_hrसमयr_on_stack(&__t.समयr);					\
	__ret;									\
पूर्ण)

/**
 * रुको_event_hrसमयout - sleep until a condition माला_लो true or a समयout elapses
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @समयout: समयout, as a kसमय_प्रकार
 *
 * The process is put to sleep (TASK_UNINTERRUPTIBLE) until the
 * @condition evaluates to true or a संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * The function वापसs 0 अगर @condition became true, or -ETIME अगर the समयout
 * elapsed.
 */
#घोषणा रुको_event_hrसमयout(wq_head, condition, समयout)			\
(अणु										\
	पूर्णांक __ret = 0;								\
	might_sleep();								\
	अगर (!(condition))							\
		__ret = __रुको_event_hrसमयout(wq_head, condition, समयout,	\
					       TASK_UNINTERRUPTIBLE);		\
	__ret;									\
पूर्ण)

/**
 * रुको_event_पूर्णांकerruptible_hrसमयout - sleep until a condition माला_लो true or a समयout elapses
 * @wq: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @समयout: समयout, as a kसमय_प्रकार
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * The function वापसs 0 अगर @condition became true, -ERESTARTSYS अगर it was
 * पूर्णांकerrupted by a संकेत, or -ETIME अगर the समयout elapsed.
 */
#घोषणा रुको_event_पूर्णांकerruptible_hrसमयout(wq, condition, समयout)		\
(अणु										\
	दीर्घ __ret = 0;								\
	might_sleep();								\
	अगर (!(condition))							\
		__ret = __रुको_event_hrसमयout(wq, condition, समयout,		\
					       TASK_INTERRUPTIBLE);		\
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_पूर्णांकerruptible_exclusive(wq, condition)			\
	___रुको_event(wq, condition, TASK_INTERRUPTIBLE, 1, 0,			\
		      schedule())

#घोषणा रुको_event_पूर्णांकerruptible_exclusive(wq, condition)			\
(अणु										\
	पूर्णांक __ret = 0;								\
	might_sleep();								\
	अगर (!(condition))							\
		__ret = __रुको_event_पूर्णांकerruptible_exclusive(wq, condition);	\
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_समाप्तable_exclusive(wq, condition)				\
	___रुको_event(wq, condition, TASK_KILLABLE, 1, 0,			\
		      schedule())

#घोषणा रुको_event_समाप्तable_exclusive(wq, condition)				\
(अणु										\
	पूर्णांक __ret = 0;								\
	might_sleep();								\
	अगर (!(condition))							\
		__ret = __रुको_event_समाप्तable_exclusive(wq, condition);		\
	__ret;									\
पूर्ण)


#घोषणा __रुको_event_मुक्तzable_exclusive(wq, condition)				\
	___रुको_event(wq, condition, TASK_INTERRUPTIBLE, 1, 0,			\
			मुक्तzable_schedule())

#घोषणा रुको_event_मुक्तzable_exclusive(wq, condition)				\
(अणु										\
	पूर्णांक __ret = 0;								\
	might_sleep();								\
	अगर (!(condition))							\
		__ret = __रुको_event_मुक्तzable_exclusive(wq, condition);	\
	__ret;									\
पूर्ण)

/**
 * रुको_event_idle - रुको क्रम a condition without contributing to प्रणाली load
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_IDLE) until the
 * @condition evaluates to true.
 * The @condition is checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 */
#घोषणा रुको_event_idle(wq_head, condition)					\
करो अणु										\
	might_sleep();								\
	अगर (!(condition))							\
		___रुको_event(wq_head, condition, TASK_IDLE, 0, 0, schedule());	\
पूर्ण जबतक (0)

/**
 * रुको_event_idle_exclusive - रुको क्रम a condition with contributing to प्रणाली load
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_IDLE) until the
 * @condition evaluates to true.
 * The @condition is checked each समय the रुकोqueue @wq_head is woken up.
 *
 * The process is put on the रुको queue with an WQ_FLAG_EXCLUSIVE flag
 * set thus अगर other processes रुको on the same list, when this
 * process is woken further processes are not considered.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 */
#घोषणा रुको_event_idle_exclusive(wq_head, condition)				\
करो अणु										\
	might_sleep();								\
	अगर (!(condition))							\
		___रुको_event(wq_head, condition, TASK_IDLE, 1, 0, schedule());	\
पूर्ण जबतक (0)

#घोषणा __रुको_event_idle_समयout(wq_head, condition, समयout)			\
	___रुको_event(wq_head, ___रुको_cond_समयout(condition),			\
		      TASK_IDLE, 0, समयout,					\
		      __ret = schedule_समयout(__ret))

/**
 * रुको_event_idle_समयout - sleep without load until a condition becomes true or a समयout elapses
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @समयout: समयout, in jअगरfies
 *
 * The process is put to sleep (TASK_IDLE) until the
 * @condition evaluates to true. The @condition is checked each समय
 * the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * Returns:
 * 0 अगर the @condition evaluated to %false after the @समयout elapsed,
 * 1 अगर the @condition evaluated to %true after the @समयout elapsed,
 * or the reमुख्यing jअगरfies (at least 1) अगर the @condition evaluated
 * to %true beक्रमe the @समयout elapsed.
 */
#घोषणा रुको_event_idle_समयout(wq_head, condition, समयout)			\
(अणु										\
	दीर्घ __ret = समयout;							\
	might_sleep();								\
	अगर (!___रुको_cond_समयout(condition))					\
		__ret = __रुको_event_idle_समयout(wq_head, condition, समयout);	\
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_idle_exclusive_समयout(wq_head, condition, समयout)	\
	___रुको_event(wq_head, ___रुको_cond_समयout(condition),			\
		      TASK_IDLE, 1, समयout,					\
		      __ret = schedule_समयout(__ret))

/**
 * रुको_event_idle_exclusive_समयout - sleep without load until a condition becomes true or a समयout elapses
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @समयout: समयout, in jअगरfies
 *
 * The process is put to sleep (TASK_IDLE) until the
 * @condition evaluates to true. The @condition is checked each समय
 * the रुकोqueue @wq_head is woken up.
 *
 * The process is put on the रुको queue with an WQ_FLAG_EXCLUSIVE flag
 * set thus अगर other processes रुको on the same list, when this
 * process is woken further processes are not considered.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * Returns:
 * 0 अगर the @condition evaluated to %false after the @समयout elapsed,
 * 1 अगर the @condition evaluated to %true after the @समयout elapsed,
 * or the reमुख्यing jअगरfies (at least 1) अगर the @condition evaluated
 * to %true beक्रमe the @समयout elapsed.
 */
#घोषणा रुको_event_idle_exclusive_समयout(wq_head, condition, समयout)		\
(अणु										\
	दीर्घ __ret = समयout;							\
	might_sleep();								\
	अगर (!___रुको_cond_समयout(condition))					\
		__ret = __रुको_event_idle_exclusive_समयout(wq_head, condition, समयout);\
	__ret;									\
पूर्ण)

बाह्य पूर्णांक करो_रुको_पूर्णांकr(रुको_queue_head_t *, रुको_queue_entry_t *);
बाह्य पूर्णांक करो_रुको_पूर्णांकr_irq(रुको_queue_head_t *, रुको_queue_entry_t *);

#घोषणा __रुको_event_पूर्णांकerruptible_locked(wq, condition, exclusive, fn)		\
(अणु										\
	पूर्णांक __ret;								\
	DEFINE_WAIT(__रुको);							\
	अगर (exclusive)								\
		__रुको.flags |= WQ_FLAG_EXCLUSIVE;				\
	करो अणु									\
		__ret = fn(&(wq), &__रुको);					\
		अगर (__ret)							\
			अवरोध;							\
	पूर्ण जबतक (!(condition));							\
	__हटाओ_रुको_queue(&(wq), &__रुको);					\
	__set_current_state(TASK_RUNNING);					\
	__ret;									\
पूर्ण)


/**
 * रुको_event_पूर्णांकerruptible_locked - sleep until a condition माला_लो true
 * @wq: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq is woken up.
 *
 * It must be called with wq.lock being held.  This spinlock is
 * unlocked जबतक sleeping but @condition testing is करोne जबतक lock
 * is held and when this macro निकासs the lock is held.
 *
 * The lock is locked/unlocked using spin_lock()/spin_unlock()
 * functions which must match the way they are locked/unlocked outside
 * of this macro.
 *
 * wake_up_locked() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * The function will वापस -ERESTARTSYS अगर it was पूर्णांकerrupted by a
 * संकेत and 0 अगर @condition evaluated to true.
 */
#घोषणा रुको_event_पूर्णांकerruptible_locked(wq, condition)				\
	((condition)								\
	 ? 0 : __रुको_event_पूर्णांकerruptible_locked(wq, condition, 0, करो_रुको_पूर्णांकr))

/**
 * रुको_event_पूर्णांकerruptible_locked_irq - sleep until a condition माला_लो true
 * @wq: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq is woken up.
 *
 * It must be called with wq.lock being held.  This spinlock is
 * unlocked जबतक sleeping but @condition testing is करोne जबतक lock
 * is held and when this macro निकासs the lock is held.
 *
 * The lock is locked/unlocked using spin_lock_irq()/spin_unlock_irq()
 * functions which must match the way they are locked/unlocked outside
 * of this macro.
 *
 * wake_up_locked() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * The function will वापस -ERESTARTSYS अगर it was पूर्णांकerrupted by a
 * संकेत and 0 अगर @condition evaluated to true.
 */
#घोषणा रुको_event_पूर्णांकerruptible_locked_irq(wq, condition)			\
	((condition)								\
	 ? 0 : __रुको_event_पूर्णांकerruptible_locked(wq, condition, 0, करो_रुको_पूर्णांकr_irq))

/**
 * रुको_event_पूर्णांकerruptible_exclusive_locked - sleep exclusively until a condition माला_लो true
 * @wq: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq is woken up.
 *
 * It must be called with wq.lock being held.  This spinlock is
 * unlocked जबतक sleeping but @condition testing is करोne जबतक lock
 * is held and when this macro निकासs the lock is held.
 *
 * The lock is locked/unlocked using spin_lock()/spin_unlock()
 * functions which must match the way they are locked/unlocked outside
 * of this macro.
 *
 * The process is put on the रुको queue with an WQ_FLAG_EXCLUSIVE flag
 * set thus when other process रुकोs process on the list अगर this
 * process is awaken further processes are not considered.
 *
 * wake_up_locked() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * The function will वापस -ERESTARTSYS अगर it was पूर्णांकerrupted by a
 * संकेत and 0 अगर @condition evaluated to true.
 */
#घोषणा रुको_event_पूर्णांकerruptible_exclusive_locked(wq, condition)		\
	((condition)								\
	 ? 0 : __रुको_event_पूर्णांकerruptible_locked(wq, condition, 1, करो_रुको_पूर्णांकr))

/**
 * रुको_event_पूर्णांकerruptible_exclusive_locked_irq - sleep until a condition माला_लो true
 * @wq: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq is woken up.
 *
 * It must be called with wq.lock being held.  This spinlock is
 * unlocked जबतक sleeping but @condition testing is करोne जबतक lock
 * is held and when this macro निकासs the lock is held.
 *
 * The lock is locked/unlocked using spin_lock_irq()/spin_unlock_irq()
 * functions which must match the way they are locked/unlocked outside
 * of this macro.
 *
 * The process is put on the रुको queue with an WQ_FLAG_EXCLUSIVE flag
 * set thus when other process रुकोs process on the list अगर this
 * process is awaken further processes are not considered.
 *
 * wake_up_locked() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * The function will वापस -ERESTARTSYS अगर it was पूर्णांकerrupted by a
 * संकेत and 0 अगर @condition evaluated to true.
 */
#घोषणा रुको_event_पूर्णांकerruptible_exclusive_locked_irq(wq, condition)		\
	((condition)								\
	 ? 0 : __रुको_event_पूर्णांकerruptible_locked(wq, condition, 1, करो_रुको_पूर्णांकr_irq))


#घोषणा __रुको_event_समाप्तable(wq, condition)					\
	___रुको_event(wq, condition, TASK_KILLABLE, 0, 0, schedule())

/**
 * रुको_event_समाप्तable - sleep until a condition माला_लो true
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 *
 * The process is put to sleep (TASK_KILLABLE) until the
 * @condition evaluates to true or a संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * The function will वापस -ERESTARTSYS अगर it was पूर्णांकerrupted by a
 * संकेत and 0 अगर @condition evaluated to true.
 */
#घोषणा रुको_event_समाप्तable(wq_head, condition)					\
(अणु										\
	पूर्णांक __ret = 0;								\
	might_sleep();								\
	अगर (!(condition))							\
		__ret = __रुको_event_समाप्तable(wq_head, condition);		\
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_समाप्तable_समयout(wq_head, condition, समयout)		\
	___रुको_event(wq_head, ___रुको_cond_समयout(condition),			\
		      TASK_KILLABLE, 0, समयout,				\
		      __ret = schedule_समयout(__ret))

/**
 * रुको_event_समाप्तable_समयout - sleep until a condition माला_लो true or a समयout elapses
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @समयout: समयout, in jअगरfies
 *
 * The process is put to sleep (TASK_KILLABLE) until the
 * @condition evaluates to true or a समाप्त संकेत is received.
 * The @condition is checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * Returns:
 * 0 अगर the @condition evaluated to %false after the @समयout elapsed,
 * 1 अगर the @condition evaluated to %true after the @समयout elapsed,
 * the reमुख्यing jअगरfies (at least 1) अगर the @condition evaluated
 * to %true beक्रमe the @समयout elapsed, or -%ERESTARTSYS अगर it was
 * पूर्णांकerrupted by a समाप्त संकेत.
 *
 * Only समाप्त संकेतs पूर्णांकerrupt this process.
 */
#घोषणा रुको_event_समाप्तable_समयout(wq_head, condition, समयout)		\
(अणु										\
	दीर्घ __ret = समयout;							\
	might_sleep();								\
	अगर (!___रुको_cond_समयout(condition))					\
		__ret = __रुको_event_समाप्तable_समयout(wq_head,			\
						condition, समयout);		\
	__ret;									\
पूर्ण)


#घोषणा __रुको_event_lock_irq(wq_head, condition, lock, cmd)			\
	(व्योम)___रुको_event(wq_head, condition, TASK_UNINTERRUPTIBLE, 0, 0,	\
			    spin_unlock_irq(&lock);				\
			    cmd;						\
			    schedule();						\
			    spin_lock_irq(&lock))

/**
 * रुको_event_lock_irq_cmd - sleep until a condition माला_लो true. The
 *			     condition is checked under the lock. This
 *			     is expected to be called with the lock
 *			     taken.
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @lock: a locked spinlock_t, which will be released beक्रमe cmd
 *	  and schedule() and reacquired afterwards.
 * @cmd: a command which is invoked outside the critical section beक्रमe
 *	 sleep
 *
 * The process is put to sleep (TASK_UNINTERRUPTIBLE) until the
 * @condition evaluates to true. The @condition is checked each समय
 * the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * This is supposed to be called जबतक holding the lock. The lock is
 * dropped beक्रमe invoking the cmd and going to sleep and is reacquired
 * afterwards.
 */
#घोषणा रुको_event_lock_irq_cmd(wq_head, condition, lock, cmd)			\
करो अणु										\
	अगर (condition)								\
		अवरोध;								\
	__रुको_event_lock_irq(wq_head, condition, lock, cmd);			\
पूर्ण जबतक (0)

/**
 * रुको_event_lock_irq - sleep until a condition माला_लो true. The
 *			 condition is checked under the lock. This
 *			 is expected to be called with the lock
 *			 taken.
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @lock: a locked spinlock_t, which will be released beक्रमe schedule()
 *	  and reacquired afterwards.
 *
 * The process is put to sleep (TASK_UNINTERRUPTIBLE) until the
 * @condition evaluates to true. The @condition is checked each समय
 * the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * This is supposed to be called जबतक holding the lock. The lock is
 * dropped beक्रमe going to sleep and is reacquired afterwards.
 */
#घोषणा रुको_event_lock_irq(wq_head, condition, lock)				\
करो अणु										\
	अगर (condition)								\
		अवरोध;								\
	__रुको_event_lock_irq(wq_head, condition, lock, );			\
पूर्ण जबतक (0)


#घोषणा __रुको_event_पूर्णांकerruptible_lock_irq(wq_head, condition, lock, cmd)	\
	___रुको_event(wq_head, condition, TASK_INTERRUPTIBLE, 0, 0,		\
		      spin_unlock_irq(&lock);					\
		      cmd;							\
		      schedule();						\
		      spin_lock_irq(&lock))

/**
 * रुको_event_पूर्णांकerruptible_lock_irq_cmd - sleep until a condition माला_लो true.
 *		The condition is checked under the lock. This is expected to
 *		be called with the lock taken.
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @lock: a locked spinlock_t, which will be released beक्रमe cmd and
 *	  schedule() and reacquired afterwards.
 * @cmd: a command which is invoked outside the critical section beक्रमe
 *	 sleep
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or a संकेत is received. The @condition is
 * checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * This is supposed to be called जबतक holding the lock. The lock is
 * dropped beक्रमe invoking the cmd and going to sleep and is reacquired
 * afterwards.
 *
 * The macro will वापस -ERESTARTSYS अगर it was पूर्णांकerrupted by a संकेत
 * and 0 अगर @condition evaluated to true.
 */
#घोषणा रुको_event_पूर्णांकerruptible_lock_irq_cmd(wq_head, condition, lock, cmd)	\
(अणु										\
	पूर्णांक __ret = 0;								\
	अगर (!(condition))							\
		__ret = __रुको_event_पूर्णांकerruptible_lock_irq(wq_head,		\
						condition, lock, cmd);		\
	__ret;									\
पूर्ण)

/**
 * रुको_event_पूर्णांकerruptible_lock_irq - sleep until a condition माला_लो true.
 *		The condition is checked under the lock. This is expected
 *		to be called with the lock taken.
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @lock: a locked spinlock_t, which will be released beक्रमe schedule()
 *	  and reacquired afterwards.
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or संकेत is received. The @condition is
 * checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * This is supposed to be called जबतक holding the lock. The lock is
 * dropped beक्रमe going to sleep and is reacquired afterwards.
 *
 * The macro will वापस -ERESTARTSYS अगर it was पूर्णांकerrupted by a संकेत
 * and 0 अगर @condition evaluated to true.
 */
#घोषणा रुको_event_पूर्णांकerruptible_lock_irq(wq_head, condition, lock)		\
(अणु										\
	पूर्णांक __ret = 0;								\
	अगर (!(condition))							\
		__ret = __रुको_event_पूर्णांकerruptible_lock_irq(wq_head,		\
						condition, lock,);		\
	__ret;									\
पूर्ण)

#घोषणा __रुको_event_lock_irq_समयout(wq_head, condition, lock, समयout, state)	\
	___रुको_event(wq_head, ___रुको_cond_समयout(condition),			\
		      state, 0, समयout,					\
		      spin_unlock_irq(&lock);					\
		      __ret = schedule_समयout(__ret);				\
		      spin_lock_irq(&lock));

/**
 * रुको_event_पूर्णांकerruptible_lock_irq_समयout - sleep until a condition माला_लो
 *		true or a समयout elapses. The condition is checked under
 *		the lock. This is expected to be called with the lock taken.
 * @wq_head: the रुकोqueue to रुको on
 * @condition: a C expression क्रम the event to रुको क्रम
 * @lock: a locked spinlock_t, which will be released beक्रमe schedule()
 *	  and reacquired afterwards.
 * @समयout: समयout, in jअगरfies
 *
 * The process is put to sleep (TASK_INTERRUPTIBLE) until the
 * @condition evaluates to true or संकेत is received. The @condition is
 * checked each समय the रुकोqueue @wq_head is woken up.
 *
 * wake_up() has to be called after changing any variable that could
 * change the result of the रुको condition.
 *
 * This is supposed to be called जबतक holding the lock. The lock is
 * dropped beक्रमe going to sleep and is reacquired afterwards.
 *
 * The function वापसs 0 अगर the @समयout elapsed, -ERESTARTSYS अगर it
 * was पूर्णांकerrupted by a संकेत, and the reमुख्यing jअगरfies otherwise
 * अगर the condition evaluated to true beक्रमe the समयout elapsed.
 */
#घोषणा रुको_event_पूर्णांकerruptible_lock_irq_समयout(wq_head, condition, lock,	\
						  समयout)			\
(अणु										\
	दीर्घ __ret = समयout;							\
	अगर (!___रुको_cond_समयout(condition))					\
		__ret = __रुको_event_lock_irq_समयout(				\
					wq_head, condition, lock, समयout,	\
					TASK_INTERRUPTIBLE);			\
	__ret;									\
पूर्ण)

#घोषणा रुको_event_lock_irq_समयout(wq_head, condition, lock, समयout)		\
(अणु										\
	दीर्घ __ret = समयout;							\
	अगर (!___रुको_cond_समयout(condition))					\
		__ret = __रुको_event_lock_irq_समयout(				\
					wq_head, condition, lock, समयout,	\
					TASK_UNINTERRUPTIBLE);			\
	__ret;									\
पूर्ण)

/*
 * Waitqueues which are हटाओd from the रुकोqueue_head at wakeup समय
 */
व्योम prepare_to_रुको(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry, पूर्णांक state);
व्योम prepare_to_रुको_exclusive(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry, पूर्णांक state);
दीर्घ prepare_to_रुको_event(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry, पूर्णांक state);
व्योम finish_रुको(काष्ठा रुको_queue_head *wq_head, काष्ठा रुको_queue_entry *wq_entry);
दीर्घ रुको_woken(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, दीर्घ समयout);
पूर्णांक woken_wake_function(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, पूर्णांक sync, व्योम *key);
पूर्णांक स्वतःहटाओ_wake_function(काष्ठा रुको_queue_entry *wq_entry, अचिन्हित mode, पूर्णांक sync, व्योम *key);

#घोषणा DEFINE_WAIT_FUNC(name, function)					\
	काष्ठा रुको_queue_entry name = अणु					\
		.निजी	= current,					\
		.func		= function,					\
		.entry		= LIST_HEAD_INIT((name).entry),			\
	पूर्ण

#घोषणा DEFINE_WAIT(name) DEFINE_WAIT_FUNC(name, स्वतःहटाओ_wake_function)

#घोषणा init_रुको(रुको)								\
	करो अणु									\
		(रुको)->निजी = current;					\
		(रुको)->func = स्वतःहटाओ_wake_function;			\
		INIT_LIST_HEAD(&(रुको)->entry);					\
		(रुको)->flags = 0;						\
	पूर्ण जबतक (0)

bool try_invoke_on_locked_करोwn_task(काष्ठा task_काष्ठा *p, bool (*func)(काष्ठा task_काष्ठा *t, व्योम *arg), व्योम *arg);

#पूर्ण_अगर /* _LINUX_WAIT_H */
