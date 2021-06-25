<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Read-Copy Update mechanism क्रम mutual exclusion (tree-based version)
 *
 * Copyright IBM Corporation, 2008
 *
 * Author: Dipankar Sarma <dipankar@in.ibm.com>
 *	   Paul E. McKenney <paulmck@linux.ibm.com> Hierarchical algorithm
 *
 * Based on the original work by Paul McKenney <paulmck@linux.ibm.com>
 * and inमाला_दो from Rusty Russell, Andrea Arcangeli and Andi Kleen.
 *
 * For detailed explanation of Read-Copy Update mechanism see -
 *	Documentation/RCU
 */

#अगर_अघोषित __LINUX_RCUTREE_H
#घोषणा __LINUX_RCUTREE_H

व्योम rcu_softirq_qs(व्योम);
व्योम rcu_note_context_चयन(bool preempt);
पूर्णांक rcu_needs_cpu(u64 basem, u64 *nextevt);
व्योम rcu_cpu_stall_reset(व्योम);

/*
 * Note a भवization-based context चयन.  This is simply a
 * wrapper around rcu_note_context_चयन(), which allows TINY_RCU
 * to save a few bytes. The caller must have disabled पूर्णांकerrupts.
 */
अटल अंतरभूत व्योम rcu_virt_note_context_चयन(पूर्णांक cpu)
अणु
	rcu_note_context_चयन(false);
पूर्ण

व्योम synchronize_rcu_expedited(व्योम);
व्योम kvमुक्त_call_rcu(काष्ठा rcu_head *head, rcu_callback_t func);

व्योम rcu_barrier(व्योम);
bool rcu_eqs_special_set(पूर्णांक cpu);
व्योम rcu_momentary_dyntick_idle(व्योम);
व्योम kमुक्त_rcu_scheduler_running(व्योम);
bool rcu_gp_might_be_stalled(व्योम);
अचिन्हित दीर्घ get_state_synchronize_rcu(व्योम);
अचिन्हित दीर्घ start_poll_synchronize_rcu(व्योम);
bool poll_state_synchronize_rcu(अचिन्हित दीर्घ oldstate);
व्योम cond_synchronize_rcu(अचिन्हित दीर्घ oldstate);

व्योम rcu_idle_enter(व्योम);
व्योम rcu_idle_निकास(व्योम);
व्योम rcu_irq_enter(व्योम);
व्योम rcu_irq_निकास(व्योम);
व्योम rcu_irq_निकास_preempt(व्योम);
व्योम rcu_irq_enter_irqson(व्योम);
व्योम rcu_irq_निकास_irqson(व्योम);
bool rcu_is_idle_cpu(पूर्णांक cpu);

#अगर_घोषित CONFIG_PROVE_RCU
व्योम rcu_irq_निकास_check_preempt(व्योम);
#अन्यथा
अटल अंतरभूत व्योम rcu_irq_निकास_check_preempt(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम निकास_rcu(व्योम);

व्योम rcu_scheduler_starting(व्योम);
बाह्य पूर्णांक rcu_scheduler_active __पढ़ो_mostly;
व्योम rcu_end_inkernel_boot(व्योम);
bool rcu_inkernel_boot_has_ended(व्योम);
bool rcu_is_watching(व्योम);
#अगर_अघोषित CONFIG_PREEMPTION
व्योम rcu_all_qs(व्योम);
#पूर्ण_अगर

/* RCUtree hotplug events */
पूर्णांक rcutree_prepare_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक rcutree_online_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक rcutree_offline_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक rcutree_dead_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक rcutree_dying_cpu(अचिन्हित पूर्णांक cpu);
व्योम rcu_cpu_starting(अचिन्हित पूर्णांक cpu);

#पूर्ण_अगर /* __LINUX_RCUTREE_H */
