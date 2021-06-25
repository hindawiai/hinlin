<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Read-Copy Update mechanism क्रम mutual exclusion, the Bloatwatch edition.
 *
 * Copyright IBM Corporation, 2008
 *
 * Author: Paul E. McKenney <paulmck@linux.ibm.com>
 *
 * For detailed explanation of Read-Copy Update mechanism see -
 *		Documentation/RCU
 */
#अगर_अघोषित __LINUX_TINY_H
#घोषणा __LINUX_TINY_H

#समावेश <यंत्र/param.h> /* क्रम HZ */

/* Never flag non-existent other CPUs! */
अटल अंतरभूत bool rcu_eqs_special_set(पूर्णांक cpu) अणु वापस false; पूर्ण

अचिन्हित दीर्घ get_state_synchronize_rcu(व्योम);
अचिन्हित दीर्घ start_poll_synchronize_rcu(व्योम);
bool poll_state_synchronize_rcu(अचिन्हित दीर्घ oldstate);

अटल अंतरभूत व्योम cond_synchronize_rcu(अचिन्हित दीर्घ oldstate)
अणु
	might_sleep();
पूर्ण

बाह्य व्योम rcu_barrier(व्योम);

अटल अंतरभूत व्योम synchronize_rcu_expedited(व्योम)
अणु
	synchronize_rcu();
पूर्ण

/*
 * Add one more declaration of kvमुक्त() here. It is
 * not so straight क्रमward to just include <linux/mm.h>
 * where it is defined due to getting many compile
 * errors caused by that include.
 */
बाह्य व्योम kvमुक्त(स्थिर व्योम *addr);

अटल अंतरभूत व्योम kvमुक्त_call_rcu(काष्ठा rcu_head *head, rcu_callback_t func)
अणु
	अगर (head) अणु
		call_rcu(head, func);
		वापस;
	पूर्ण

	// kvमुक्त_rcu(one_arg) call.
	might_sleep();
	synchronize_rcu();
	kvमुक्त((व्योम *) func);
पूर्ण

व्योम rcu_qs(व्योम);

अटल अंतरभूत व्योम rcu_softirq_qs(व्योम)
अणु
	rcu_qs();
पूर्ण

#घोषणा rcu_note_context_चयन(preempt) \
	करो अणु \
		rcu_qs(); \
		rcu_tasks_qs(current, (preempt)); \
	पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक rcu_needs_cpu(u64 basemono, u64 *nextevt)
अणु
	*nextevt = KTIME_MAX;
	वापस 0;
पूर्ण

/*
 * Take advantage of the fact that there is only one CPU, which
 * allows us to ignore भवization-based context चयनes.
 */
अटल अंतरभूत व्योम rcu_virt_note_context_चयन(पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम rcu_cpu_stall_reset(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक rcu_jअगरfies_till_stall_check(व्योम) अणु वापस 21 * HZ; पूर्ण
अटल अंतरभूत व्योम rcu_idle_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_idle_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_irq_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_irq_निकास_irqson(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_irq_enter_irqson(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_irq_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_irq_निकास_preempt(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_irq_निकास_check_preempt(व्योम) अणु पूर्ण
#घोषणा rcu_is_idle_cpu(cpu) \
	(is_idle_task(current) && !in_nmi() && !in_irq() && !in_serving_softirq())
अटल अंतरभूत व्योम निकास_rcu(व्योम) अणु पूर्ण
अटल अंतरभूत bool rcu_preempt_need_deferred_qs(काष्ठा task_काष्ठा *t)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम rcu_preempt_deferred_qs(काष्ठा task_काष्ठा *t) अणु पूर्ण
#अगर_घोषित CONFIG_SRCU
व्योम rcu_scheduler_starting(व्योम);
#अन्यथा /* #अगर_अघोषित CONFIG_SRCU */
अटल अंतरभूत व्योम rcu_scheduler_starting(व्योम) अणु पूर्ण
#पूर्ण_अगर /* #अन्यथा #अगर_अघोषित CONFIG_SRCU */
अटल अंतरभूत व्योम rcu_end_inkernel_boot(व्योम) अणु पूर्ण
अटल अंतरभूत bool rcu_inkernel_boot_has_ended(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत bool rcu_is_watching(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत व्योम rcu_momentary_dyntick_idle(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kमुक्त_rcu_scheduler_running(व्योम) अणु पूर्ण
अटल अंतरभूत bool rcu_gp_might_be_stalled(व्योम) अणु वापस false; पूर्ण

/* Aव्योम RCU पढ़ो-side critical sections leaking across. */
अटल अंतरभूत व्योम rcu_all_qs(व्योम) अणु barrier(); पूर्ण

/* RCUtree hotplug events */
#घोषणा rcutree_prepare_cpu      शून्य
#घोषणा rcutree_online_cpu       शून्य
#घोषणा rcutree_offline_cpu      शून्य
#घोषणा rcutree_dead_cpu         शून्य
#घोषणा rcutree_dying_cpu        शून्य
अटल अंतरभूत व्योम rcu_cpu_starting(अचिन्हित पूर्णांक cpu) अणु पूर्ण

#पूर्ण_अगर /* __LINUX_RCUTINY_H */
