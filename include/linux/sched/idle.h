<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_IDLE_H
#घोषणा _LINUX_SCHED_IDLE_H

#समावेश <linux/sched.h>

क्रमागत cpu_idle_type अणु
	CPU_IDLE,
	CPU_NOT_IDLE,
	CPU_NEWLY_IDLE,
	CPU_MAX_IDLE_TYPES
पूर्ण;

बाह्य व्योम wake_up_अगर_idle(पूर्णांक cpu);

/*
 * Idle thपढ़ो specअगरic functions to determine the need_resched
 * polling state.
 */
#अगर_घोषित TIF_POLLING_NRFLAG

अटल अंतरभूत व्योम __current_set_polling(व्योम)
अणु
	set_thपढ़ो_flag(TIF_POLLING_NRFLAG);
पूर्ण

अटल अंतरभूत bool __must_check current_set_polling_and_test(व्योम)
अणु
	__current_set_polling();

	/*
	 * Polling state must be visible beक्रमe we test NEED_RESCHED,
	 * paired by resched_curr()
	 */
	smp_mb__after_atomic();

	वापस unlikely(tअगर_need_resched());
पूर्ण

अटल अंतरभूत व्योम __current_clr_polling(व्योम)
अणु
	clear_thपढ़ो_flag(TIF_POLLING_NRFLAG);
पूर्ण

अटल अंतरभूत bool __must_check current_clr_polling_and_test(व्योम)
अणु
	__current_clr_polling();

	/*
	 * Polling state must be visible beक्रमe we test NEED_RESCHED,
	 * paired by resched_curr()
	 */
	smp_mb__after_atomic();

	वापस unlikely(tअगर_need_resched());
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम __current_set_polling(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम __current_clr_polling(व्योम) अणु पूर्ण

अटल अंतरभूत bool __must_check current_set_polling_and_test(व्योम)
अणु
	वापस unlikely(tअगर_need_resched());
पूर्ण
अटल अंतरभूत bool __must_check current_clr_polling_and_test(व्योम)
अणु
	वापस unlikely(tअगर_need_resched());
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम current_clr_polling(व्योम)
अणु
	__current_clr_polling();

	/*
	 * Ensure we check TIF_NEED_RESCHED after we clear the polling bit.
	 * Once the bit is cleared, we'll get IPIs with every new
	 * TIF_NEED_RESCHED and the IPI handler, scheduler_ipi(), will also
	 * fold.
	 */
	smp_mb(); /* paired with resched_curr() */

	preempt_fold_need_resched();
पूर्ण

#पूर्ण_अगर /* _LINUX_SCHED_IDLE_H */
