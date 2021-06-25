<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_RT_H
#घोषणा _LINUX_SCHED_RT_H

#समावेश <linux/sched.h>

काष्ठा task_काष्ठा;

अटल अंतरभूत पूर्णांक rt_prio(पूर्णांक prio)
अणु
	अगर (unlikely(prio < MAX_RT_PRIO))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक rt_task(काष्ठा task_काष्ठा *p)
अणु
	वापस rt_prio(p->prio);
पूर्ण

अटल अंतरभूत bool task_is_realसमय(काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक policy = tsk->policy;

	अगर (policy == SCHED_FIFO || policy == SCHED_RR)
		वापस true;
	अगर (policy == SCHED_DEADLINE)
		वापस true;
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_RT_MUTEXES
/*
 * Must hold either p->pi_lock or task_rq(p)->lock.
 */
अटल अंतरभूत काष्ठा task_काष्ठा *rt_mutex_get_top_task(काष्ठा task_काष्ठा *p)
अणु
	वापस p->pi_top_task;
पूर्ण
बाह्य व्योम rt_mutex_setprio(काष्ठा task_काष्ठा *p, काष्ठा task_काष्ठा *pi_task);
बाह्य व्योम rt_mutex_adjust_pi(काष्ठा task_काष्ठा *p);
अटल अंतरभूत bool tsk_is_pi_blocked(काष्ठा task_काष्ठा *tsk)
अणु
	वापस tsk->pi_blocked_on != शून्य;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा task_काष्ठा *rt_mutex_get_top_task(काष्ठा task_काष्ठा *task)
अणु
	वापस शून्य;
पूर्ण
# define rt_mutex_adjust_pi(p)		करो अणु पूर्ण जबतक (0)
अटल अंतरभूत bool tsk_is_pi_blocked(काष्ठा task_काष्ठा *tsk)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

बाह्य व्योम normalize_rt_tasks(व्योम);


/*
 * शेष बारlice is 100 msecs (used only क्रम SCHED_RR tasks).
 * Timeslices get refilled after they expire.
 */
#घोषणा RR_TIMESLICE		(100 * HZ / 1000)

#पूर्ण_अगर /* _LINUX_SCHED_RT_H */
