<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_CPUTIME_H
#घोषणा _LINUX_SCHED_CPUTIME_H

#समावेश <linux/sched/संकेत.स>

/*
 * cpuसमय accounting APIs:
 */

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
#समावेश <यंत्र/cpuसमय.स>

#अगर_अघोषित cpuसमय_प्रकारo_nsecs
# define cpuसमय_प्रकारo_nsecs(__ct)	\
	(cpuसमय_प्रकारo_usecs(__ct) * NSEC_PER_USEC)
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_GEN
बाह्य व्योम task_cpuसमय(काष्ठा task_काष्ठा *t,
			 u64 *uसमय, u64 *sसमय);
बाह्य u64 task_gसमय(काष्ठा task_काष्ठा *t);
#अन्यथा
अटल अंतरभूत व्योम task_cpuसमय(काष्ठा task_काष्ठा *t,
				u64 *uसमय, u64 *sसमय)
अणु
	*uसमय = t->uसमय;
	*sसमय = t->sसमय;
पूर्ण

अटल अंतरभूत u64 task_gसमय(काष्ठा task_काष्ठा *t)
अणु
	वापस t->gसमय;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_HAS_SCALED_CPUTIME
अटल अंतरभूत व्योम task_cpuसमय_scaled(काष्ठा task_काष्ठा *t,
				       u64 *uबारcaled,
				       u64 *sबारcaled)
अणु
	*uबारcaled = t->uबारcaled;
	*sबारcaled = t->sबारcaled;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम task_cpuसमय_scaled(काष्ठा task_काष्ठा *t,
				       u64 *uबारcaled,
				       u64 *sबारcaled)
अणु
	task_cpuसमय(t, uबारcaled, sबारcaled);
पूर्ण
#पूर्ण_अगर

बाह्य व्योम task_cpuसमय_adjusted(काष्ठा task_काष्ठा *p, u64 *ut, u64 *st);
बाह्य व्योम thपढ़ो_group_cpuसमय_adjusted(काष्ठा task_काष्ठा *p, u64 *ut, u64 *st);
बाह्य व्योम cpuसमय_adjust(काष्ठा task_cpuसमय *curr, काष्ठा prev_cpuसमय *prev,
			   u64 *ut, u64 *st);

/*
 * Thपढ़ो group CPU समय accounting.
 */
व्योम thपढ़ो_group_cpuसमय(काष्ठा task_काष्ठा *tsk, काष्ठा task_cpuसमय *बार);
व्योम thपढ़ो_group_sample_cpuसमय(काष्ठा task_काष्ठा *tsk, u64 *samples);

/*
 * The following are functions that support scheduler-पूर्णांकernal समय accounting.
 * These functions are generally called at the समयr tick.  None of this depends
 * on CONFIG_SCHEDSTATS.
 */

/**
 * get_running_cpuसमयr - वापस &tsk->संकेत->cpuसमयr अगर cpuसमयrs are active
 *
 * @tsk:	Poपूर्णांकer to target task.
 */
#अगर_घोषित CONFIG_POSIX_TIMERS
अटल अंतरभूत
काष्ठा thपढ़ो_group_cpuसमयr *get_running_cpuसमयr(काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा thपढ़ो_group_cpuसमयr *cpuसमयr = &tsk->संकेत->cpuसमयr;

	/*
	 * Check whether posix CPU समयrs are active. If not the thपढ़ो
	 * group accounting is not active either. Lockless check.
	 */
	अगर (!READ_ONCE(tsk->संकेत->posix_cpuसमयrs.समयrs_active))
		वापस शून्य;

	/*
	 * After we flush the task's sum_exec_runसमय to sig->sum_sched_runसमय
	 * in __निकास_संकेत(), we won't account to the संकेत काष्ठा further
	 * cpuसमय consumed by that task, even though the task can still be
	 * ticking after __निकास_संकेत().
	 *
	 * In order to keep a consistent behaviour between thपढ़ो group cpuसमय
	 * and thपढ़ो group cpuसमयr accounting, lets also ignore the cpuसमय
	 * elapsing after __निकास_संकेत() in any thपढ़ो group समयr running.
	 *
	 * This makes sure that POSIX CPU घड़ीs and समयrs are synchronized, so
	 * that a POSIX CPU समयr won't expire जबतक the corresponding POSIX CPU
	 * घड़ी delta is behind the expiring समयr value.
	 */
	अगर (unlikely(!tsk->sighand))
		वापस शून्य;

	वापस cpuसमयr;
पूर्ण
#अन्यथा
अटल अंतरभूत
काष्ठा thपढ़ो_group_cpuसमयr *get_running_cpuसमयr(काष्ठा task_काष्ठा *tsk)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/**
 * account_group_user_समय - Maपूर्णांकain uसमय क्रम a thपढ़ो group.
 *
 * @tsk:	Poपूर्णांकer to task काष्ठाure.
 * @cpuसमय:	Time value by which to increment the uसमय field of the
 *		thपढ़ो_group_cpuसमय काष्ठाure.
 *
 * If thपढ़ो group समय is being मुख्यtained, get the काष्ठाure क्रम the
 * running CPU and update the uसमय field there.
 */
अटल अंतरभूत व्योम account_group_user_समय(काष्ठा task_काष्ठा *tsk,
					   u64 cpuसमय)
अणु
	काष्ठा thपढ़ो_group_cpuसमयr *cpuसमयr = get_running_cpuसमयr(tsk);

	अगर (!cpuसमयr)
		वापस;

	atomic64_add(cpuसमय, &cpuसमयr->cpuसमय_atomic.uसमय);
पूर्ण

/**
 * account_group_प्रणाली_समय - Maपूर्णांकain sसमय क्रम a thपढ़ो group.
 *
 * @tsk:	Poपूर्णांकer to task काष्ठाure.
 * @cpuसमय:	Time value by which to increment the sसमय field of the
 *		thपढ़ो_group_cpuसमय काष्ठाure.
 *
 * If thपढ़ो group समय is being मुख्यtained, get the काष्ठाure क्रम the
 * running CPU and update the sसमय field there.
 */
अटल अंतरभूत व्योम account_group_प्रणाली_समय(काष्ठा task_काष्ठा *tsk,
					     u64 cpuसमय)
अणु
	काष्ठा thपढ़ो_group_cpuसमयr *cpuसमयr = get_running_cpuसमयr(tsk);

	अगर (!cpuसमयr)
		वापस;

	atomic64_add(cpuसमय, &cpuसमयr->cpuसमय_atomic.sसमय);
पूर्ण

/**
 * account_group_exec_runसमय - Maपूर्णांकain exec runसमय क्रम a thपढ़ो group.
 *
 * @tsk:	Poपूर्णांकer to task काष्ठाure.
 * @ns:		Time value by which to increment the sum_exec_runसमय field
 *		of the thपढ़ो_group_cpuसमय काष्ठाure.
 *
 * If thपढ़ो group समय is being मुख्यtained, get the काष्ठाure क्रम the
 * running CPU and update the sum_exec_runसमय field there.
 */
अटल अंतरभूत व्योम account_group_exec_runसमय(काष्ठा task_काष्ठा *tsk,
					      अचिन्हित दीर्घ दीर्घ ns)
अणु
	काष्ठा thपढ़ो_group_cpuसमयr *cpuसमयr = get_running_cpuसमयr(tsk);

	अगर (!cpuसमयr)
		वापस;

	atomic64_add(ns, &cpuसमयr->cpuसमय_atomic.sum_exec_runसमय);
पूर्ण

अटल अंतरभूत व्योम prev_cpuसमय_init(काष्ठा prev_cpuसमय *prev)
अणु
#अगर_अघोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
	prev->uसमय = prev->sसमय = 0;
	raw_spin_lock_init(&prev->lock);
#पूर्ण_अगर
पूर्ण

बाह्य अचिन्हित दीर्घ दीर्घ
task_sched_runसमय(काष्ठा task_काष्ठा *task);

#पूर्ण_अगर /* _LINUX_SCHED_CPUTIME_H */
