<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_HARसूचीQ_H
#घोषणा LINUX_HARसूचीQ_H

#समावेश <linux/context_tracking_state.h>
#समावेश <linux/preempt.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/ftrace_irq.h>
#समावेश <linux/sched.h>
#समावेश <linux/vसमय.स>
#समावेश <यंत्र/hardirq.h>

बाह्य व्योम synchronize_irq(अचिन्हित पूर्णांक irq);
बाह्य bool synchronize_hardirq(अचिन्हित पूर्णांक irq);

#अगर_घोषित CONFIG_NO_HZ_FULL
व्योम __rcu_irq_enter_check_tick(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __rcu_irq_enter_check_tick(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल __always_अंतरभूत व्योम rcu_irq_enter_check_tick(व्योम)
अणु
	अगर (context_tracking_enabled())
		__rcu_irq_enter_check_tick();
पूर्ण

/*
 * It is safe to करो non-atomic ops on ->hardirq_context,
 * because NMI handlers may not preempt and the ops are
 * always balanced, so the पूर्णांकerrupted value of ->hardirq_context
 * will always be restored.
 */
#घोषणा __irq_enter()					\
	करो अणु						\
		preempt_count_add(HARसूचीQ_OFFSET);	\
		lockdep_hardirq_enter();		\
		account_hardirq_enter(current);		\
	पूर्ण जबतक (0)

/*
 * Like __irq_enter() without समय accounting क्रम fast
 * पूर्णांकerrupts, e.g. reschedule IPI where समय accounting
 * is more expensive than the actual पूर्णांकerrupt.
 */
#घोषणा __irq_enter_raw()				\
	करो अणु						\
		preempt_count_add(HARसूचीQ_OFFSET);	\
		lockdep_hardirq_enter();		\
	पूर्ण जबतक (0)

/*
 * Enter irq context (on NO_HZ, update jअगरfies):
 */
व्योम irq_enter(व्योम);
/*
 * Like irq_enter(), but RCU is alपढ़ोy watching.
 */
व्योम irq_enter_rcu(व्योम);

/*
 * Exit irq context without processing softirqs:
 */
#घोषणा __irq_निकास()					\
	करो अणु						\
		account_hardirq_निकास(current);		\
		lockdep_hardirq_निकास();			\
		preempt_count_sub(HARसूचीQ_OFFSET);	\
	पूर्ण जबतक (0)

/*
 * Like __irq_निकास() without समय accounting
 */
#घोषणा __irq_निकास_raw()				\
	करो अणु						\
		lockdep_hardirq_निकास();			\
		preempt_count_sub(HARसूचीQ_OFFSET);	\
	पूर्ण जबतक (0)

/*
 * Exit irq context and process softirqs अगर needed:
 */
व्योम irq_निकास(व्योम);

/*
 * Like irq_निकास(), but वापस with RCU watching.
 */
व्योम irq_निकास_rcu(व्योम);

#अगर_अघोषित arch_nmi_enter
#घोषणा arch_nmi_enter()	करो अणु पूर्ण जबतक (0)
#घोषणा arch_nmi_निकास()		करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_TINY_RCU
अटल अंतरभूत व्योम rcu_nmi_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम rcu_nmi_निकास(व्योम) अणु पूर्ण
#अन्यथा
बाह्य व्योम rcu_nmi_enter(व्योम);
बाह्य व्योम rcu_nmi_निकास(व्योम);
#पूर्ण_अगर

/*
 * NMI vs Tracing
 * --------------
 *
 * We must not land in a tracer until (or after) we've changed preempt_count
 * such that in_nmi() becomes true. To that effect all NMI C entry poपूर्णांकs must
 * be marked 'notrace' and call nmi_enter() as soon as possible.
 */

/*
 * nmi_enter() can nest up to 15 बार; see NMI_BITS.
 */
#घोषणा __nmi_enter()						\
	करो अणु							\
		lockdep_off();					\
		arch_nmi_enter();				\
		prपूर्णांकk_nmi_enter();				\
		BUG_ON(in_nmi() == NMI_MASK);			\
		__preempt_count_add(NMI_OFFSET + HARसूचीQ_OFFSET);	\
	पूर्ण जबतक (0)

#घोषणा nmi_enter()						\
	करो अणु							\
		__nmi_enter();					\
		lockdep_hardirq_enter();			\
		rcu_nmi_enter();				\
		instrumentation_begin();			\
		ftrace_nmi_enter();				\
		instrumentation_end();				\
	पूर्ण जबतक (0)

#घोषणा __nmi_निकास()						\
	करो अणु							\
		BUG_ON(!in_nmi());				\
		__preempt_count_sub(NMI_OFFSET + HARसूचीQ_OFFSET);	\
		prपूर्णांकk_nmi_निकास();				\
		arch_nmi_निकास();				\
		lockdep_on();					\
	पूर्ण जबतक (0)

#घोषणा nmi_निकास()						\
	करो अणु							\
		instrumentation_begin();			\
		ftrace_nmi_निकास();				\
		instrumentation_end();				\
		rcu_nmi_निकास();					\
		lockdep_hardirq_निकास();				\
		__nmi_निकास();					\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* LINUX_HARसूचीQ_H */
