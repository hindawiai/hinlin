<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Freezer declarations */

#अगर_अघोषित FREEZER_H_INCLUDED
#घोषणा FREEZER_H_INCLUDED

#समावेश <linux/debug_locks.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>
#समावेश <linux/atomic.h>

#अगर_घोषित CONFIG_FREEZER
बाह्य atomic_t प्रणाली_मुक्तzing_cnt;	/* nr of मुक्तzing conds in effect */
बाह्य bool pm_मुक्तzing;		/* PM मुक्तzing in effect */
बाह्य bool pm_nosig_मुक्तzing;		/* PM nosig मुक्तzing in effect */

/*
 * Timeout क्रम stopping processes
 */
बाह्य अचिन्हित पूर्णांक मुक्तze_समयout_msecs;

/*
 * Check अगर a process has been frozen
 */
अटल अंतरभूत bool frozen(काष्ठा task_काष्ठा *p)
अणु
	वापस p->flags & PF_FROZEN;
पूर्ण

बाह्य bool मुक्तzing_slow_path(काष्ठा task_काष्ठा *p);

/*
 * Check अगर there is a request to मुक्तze a process
 */
अटल अंतरभूत bool मुक्तzing(काष्ठा task_काष्ठा *p)
अणु
	अगर (likely(!atomic_पढ़ो(&प्रणाली_मुक्तzing_cnt)))
		वापस false;
	वापस मुक्तzing_slow_path(p);
पूर्ण

/* Takes and releases task alloc lock using task_lock() */
बाह्य व्योम __thaw_task(काष्ठा task_काष्ठा *t);

बाह्य bool __refrigerator(bool check_kthr_stop);
बाह्य पूर्णांक मुक्तze_processes(व्योम);
बाह्य पूर्णांक मुक्तze_kernel_thपढ़ोs(व्योम);
बाह्य व्योम thaw_processes(व्योम);
बाह्य व्योम thaw_kernel_thपढ़ोs(व्योम);

/*
 * DO NOT ADD ANY NEW CALLERS OF THIS FUNCTION
 * If try_to_मुक्तze causes a lockdep warning it means the caller may deadlock
 */
अटल अंतरभूत bool try_to_मुक्तze_unsafe(व्योम)
अणु
	might_sleep();
	अगर (likely(!मुक्तzing(current)))
		वापस false;
	वापस __refrigerator(false);
पूर्ण

अटल अंतरभूत bool try_to_मुक्तze(व्योम)
अणु
	अगर (!(current->flags & PF_NOFREEZE))
		debug_check_no_locks_held();
	वापस try_to_मुक्तze_unsafe();
पूर्ण

बाह्य bool मुक्तze_task(काष्ठा task_काष्ठा *p);
बाह्य bool set_मुक्तzable(व्योम);

#अगर_घोषित CONFIG_CGROUP_FREEZER
बाह्य bool cgroup_मुक्तzing(काष्ठा task_काष्ठा *task);
#अन्यथा /* !CONFIG_CGROUP_FREEZER */
अटल अंतरभूत bool cgroup_मुक्तzing(काष्ठा task_काष्ठा *task)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* !CONFIG_CGROUP_FREEZER */

/*
 * The PF_FREEZER_SKIP flag should be set by a vविभाजन parent right beक्रमe it
 * calls रुको_क्रम_completion(&vविभाजन) and reset right after it वापसs from this
 * function.  Next, the parent should call try_to_मुक्तze() to मुक्तze itself
 * appropriately in हाल the child has निकासed beक्रमe the मुक्तzing of tasks is
 * complete.  However, we करोn't want kernel thपढ़ोs to be frozen in unexpected
 * places, so we allow them to block मुक्तze_processes() instead or to set
 * PF_NOFREEZE अगर needed. Fortunately, in the ____call_usermodehelper() हाल the
 * parent won't really block मुक्तze_processes(), since ____call_usermodehelper()
 * (the child) करोes a little beक्रमe exec/निकास and it can't be frozen beक्रमe
 * waking up the parent.
 */


/**
 * मुक्तzer_करो_not_count - tell मुक्तzer to ignore %current
 *
 * Tell मुक्तzers to ignore the current task when determining whether the
 * target frozen state is reached.  IOW, the current task will be
 * considered frozen enough by मुक्तzers.
 *
 * The caller shouldn't do anything which isn't allowed क्रम a frozen task
 * until मुक्तzer_cont() is called.  Usually, मुक्तzer[_करो_not]_count() pair
 * wrap a scheduling operation and nothing much अन्यथा.
 */
अटल अंतरभूत व्योम मुक्तzer_करो_not_count(व्योम)
अणु
	current->flags |= PF_FREEZER_SKIP;
पूर्ण

/**
 * मुक्तzer_count - tell मुक्तzer to stop ignoring %current
 *
 * Unकरो मुक्तzer_करो_not_count().  It tells मुक्तzers that %current should be
 * considered again and tries to मुक्तze अगर मुक्तzing condition is alपढ़ोy in
 * effect.
 */
अटल अंतरभूत व्योम मुक्तzer_count(व्योम)
अणु
	current->flags &= ~PF_FREEZER_SKIP;
	/*
	 * If मुक्तzing is in progress, the following paired with smp_mb()
	 * in मुक्तzer_should_skip() ensures that either we see %true
	 * मुक्तzing() or मुक्तzer_should_skip() sees !PF_FREEZER_SKIP.
	 */
	smp_mb();
	try_to_मुक्तze();
पूर्ण

/* DO NOT ADD ANY NEW CALLERS OF THIS FUNCTION */
अटल अंतरभूत व्योम मुक्तzer_count_unsafe(व्योम)
अणु
	current->flags &= ~PF_FREEZER_SKIP;
	smp_mb();
	try_to_मुक्तze_unsafe();
पूर्ण

/**
 * मुक्तzer_should_skip - whether to skip a task when determining frozen
 *			 state is reached
 * @p: task in quesion
 *
 * This function is used by मुक्तzers after establishing %true मुक्तzing() to
 * test whether a task should be skipped when determining the target frozen
 * state is reached.  IOW, अगर this function वापसs %true, @p is considered
 * frozen enough.
 */
अटल अंतरभूत bool मुक्तzer_should_skip(काष्ठा task_काष्ठा *p)
अणु
	/*
	 * The following smp_mb() paired with the one in मुक्तzer_count()
	 * ensures that either मुक्तzer_count() sees %true मुक्तzing() or we
	 * see cleared %PF_FREEZER_SKIP and वापस %false.  This makes it
	 * impossible क्रम a task to slip frozen state testing after
	 * clearing %PF_FREEZER_SKIP.
	 */
	smp_mb();
	वापस p->flags & PF_FREEZER_SKIP;
पूर्ण

/*
 * These functions are पूर्णांकended to be used whenever you want allow a sleeping
 * task to be frozen. Note that neither वापस any clear indication of
 * whether a मुक्तze event happened जबतक in this function.
 */

/* Like schedule(), but should not block the मुक्तzer. */
अटल अंतरभूत व्योम मुक्तzable_schedule(व्योम)
अणु
	मुक्तzer_करो_not_count();
	schedule();
	मुक्तzer_count();
पूर्ण

/* DO NOT ADD ANY NEW CALLERS OF THIS FUNCTION */
अटल अंतरभूत व्योम मुक्तzable_schedule_unsafe(व्योम)
अणु
	मुक्तzer_करो_not_count();
	schedule();
	मुक्तzer_count_unsafe();
पूर्ण

/*
 * Like schedule_समयout(), but should not block the मुक्तzer.  Do not
 * call this with locks held.
 */
अटल अंतरभूत दीर्घ मुक्तzable_schedule_समयout(दीर्घ समयout)
अणु
	दीर्घ __retval;
	मुक्तzer_करो_not_count();
	__retval = schedule_समयout(समयout);
	मुक्तzer_count();
	वापस __retval;
पूर्ण

/*
 * Like schedule_समयout_पूर्णांकerruptible(), but should not block the मुक्तzer.  Do not
 * call this with locks held.
 */
अटल अंतरभूत दीर्घ मुक्तzable_schedule_समयout_पूर्णांकerruptible(दीर्घ समयout)
अणु
	दीर्घ __retval;
	मुक्तzer_करो_not_count();
	__retval = schedule_समयout_पूर्णांकerruptible(समयout);
	मुक्तzer_count();
	वापस __retval;
पूर्ण

/* DO NOT ADD ANY NEW CALLERS OF THIS FUNCTION */
अटल अंतरभूत दीर्घ मुक्तzable_schedule_समयout_पूर्णांकerruptible_unsafe(दीर्घ समयout)
अणु
	दीर्घ __retval;

	मुक्तzer_करो_not_count();
	__retval = schedule_समयout_पूर्णांकerruptible(समयout);
	मुक्तzer_count_unsafe();
	वापस __retval;
पूर्ण

/* Like schedule_समयout_समाप्तable(), but should not block the मुक्तzer. */
अटल अंतरभूत दीर्घ मुक्तzable_schedule_समयout_समाप्तable(दीर्घ समयout)
अणु
	दीर्घ __retval;
	मुक्तzer_करो_not_count();
	__retval = schedule_समयout_समाप्तable(समयout);
	मुक्तzer_count();
	वापस __retval;
पूर्ण

/* DO NOT ADD ANY NEW CALLERS OF THIS FUNCTION */
अटल अंतरभूत दीर्घ मुक्तzable_schedule_समयout_समाप्तable_unsafe(दीर्घ समयout)
अणु
	दीर्घ __retval;
	मुक्तzer_करो_not_count();
	__retval = schedule_समयout_समाप्तable(समयout);
	मुक्तzer_count_unsafe();
	वापस __retval;
पूर्ण

/*
 * Like schedule_hrसमयout_range(), but should not block the मुक्तzer.  Do not
 * call this with locks held.
 */
अटल अंतरभूत पूर्णांक मुक्तzable_schedule_hrसमयout_range(kसमय_प्रकार *expires,
		u64 delta, स्थिर क्रमागत hrसमयr_mode mode)
अणु
	पूर्णांक __retval;
	मुक्तzer_करो_not_count();
	__retval = schedule_hrसमयout_range(expires, delta, mode);
	मुक्तzer_count();
	वापस __retval;
पूर्ण

/*
 * Freezer-मित्रly wrappers around रुको_event_पूर्णांकerruptible(),
 * रुको_event_समाप्तable() and रुको_event_पूर्णांकerruptible_समयout(), originally
 * defined in <linux/रुको.h>
 */

/* DO NOT ADD ANY NEW CALLERS OF THIS FUNCTION */
#घोषणा रुको_event_मुक्तzeसमाप्तable_unsafe(wq, condition)			\
(अणु									\
	पूर्णांक __retval;							\
	मुक्तzer_करो_not_count();						\
	__retval = रुको_event_समाप्तable(wq, (condition));		\
	मुक्तzer_count_unsafe();						\
	__retval;							\
पूर्ण)

#अन्यथा /* !CONFIG_FREEZER */
अटल अंतरभूत bool frozen(काष्ठा task_काष्ठा *p) अणु वापस false; पूर्ण
अटल अंतरभूत bool मुक्तzing(काष्ठा task_काष्ठा *p) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम __thaw_task(काष्ठा task_काष्ठा *t) अणुपूर्ण

अटल अंतरभूत bool __refrigerator(bool check_kthr_stop) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक मुक्तze_processes(व्योम) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक मुक्तze_kernel_thपढ़ोs(व्योम) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम thaw_processes(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम thaw_kernel_thपढ़ोs(व्योम) अणुपूर्ण

अटल अंतरभूत bool try_to_मुक्तze(व्योम) अणु वापस false; पूर्ण

अटल अंतरभूत व्योम मुक्तzer_करो_not_count(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम मुक्तzer_count(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक मुक्तzer_should_skip(काष्ठा task_काष्ठा *p) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम set_मुक्तzable(व्योम) अणुपूर्ण

#घोषणा मुक्तzable_schedule()  schedule()

#घोषणा मुक्तzable_schedule_unsafe()  schedule()

#घोषणा मुक्तzable_schedule_समयout(समयout)  schedule_समयout(समयout)

#घोषणा मुक्तzable_schedule_समयout_पूर्णांकerruptible(समयout)		\
	schedule_समयout_पूर्णांकerruptible(समयout)

#घोषणा मुक्तzable_schedule_समयout_पूर्णांकerruptible_unsafe(समयout)	\
	schedule_समयout_पूर्णांकerruptible(समयout)

#घोषणा मुक्तzable_schedule_समयout_समाप्तable(समयout)			\
	schedule_समयout_समाप्तable(समयout)

#घोषणा मुक्तzable_schedule_समयout_समाप्तable_unsafe(समयout)		\
	schedule_समयout_समाप्तable(समयout)

#घोषणा मुक्तzable_schedule_hrसमयout_range(expires, delta, mode)	\
	schedule_hrसमयout_range(expires, delta, mode)

#घोषणा रुको_event_मुक्तzeसमाप्तable_unsafe(wq, condition)			\
		रुको_event_समाप्तable(wq, condition)

#पूर्ण_अगर /* !CONFIG_FREEZER */

#पूर्ण_अगर	/* FREEZER_H_INCLUDED */
