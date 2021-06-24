<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_PREEMPT_H
#घोषणा __ASM_PREEMPT_H

#समावेश <linux/thपढ़ो_info.h>

#घोषणा PREEMPT_ENABLED	(0)

अटल __always_अंतरभूत पूर्णांक preempt_count(व्योम)
अणु
	वापस READ_ONCE(current_thपढ़ो_info()->preempt_count);
पूर्ण

अटल __always_अंतरभूत अस्थिर पूर्णांक *preempt_count_ptr(व्योम)
अणु
	वापस &current_thपढ़ो_info()->preempt_count;
पूर्ण

अटल __always_अंतरभूत व्योम preempt_count_set(पूर्णांक pc)
अणु
	*preempt_count_ptr() = pc;
पूर्ण

/*
 * must be macros to aव्योम header recursion hell
 */
#घोषणा init_task_preempt_count(p) करो अणु \
	task_thपढ़ो_info(p)->preempt_count = FORK_PREEMPT_COUNT; \
पूर्ण जबतक (0)

#घोषणा init_idle_preempt_count(p, cpu) करो अणु \
	task_thपढ़ो_info(p)->preempt_count = PREEMPT_ENABLED; \
पूर्ण जबतक (0)

अटल __always_अंतरभूत व्योम set_preempt_need_resched(व्योम)
अणु
पूर्ण

अटल __always_अंतरभूत व्योम clear_preempt_need_resched(व्योम)
अणु
पूर्ण

अटल __always_अंतरभूत bool test_preempt_need_resched(व्योम)
अणु
	वापस false;
पूर्ण

/*
 * The various preempt_count add/sub methods
 */

अटल __always_अंतरभूत व्योम __preempt_count_add(पूर्णांक val)
अणु
	*preempt_count_ptr() += val;
पूर्ण

अटल __always_अंतरभूत व्योम __preempt_count_sub(पूर्णांक val)
अणु
	*preempt_count_ptr() -= val;
पूर्ण

अटल __always_अंतरभूत bool __preempt_count_dec_and_test(व्योम)
अणु
	/*
	 * Because of load-store architectures cannot करो per-cpu atomic
	 * operations; we cannot use PREEMPT_NEED_RESCHED because it might get
	 * lost.
	 */
	वापस !--*preempt_count_ptr() && tअगर_need_resched();
पूर्ण

/*
 * Returns true when we need to resched and can (barring IRQ state).
 */
अटल __always_अंतरभूत bool should_resched(पूर्णांक preempt_offset)
अणु
	वापस unlikely(preempt_count() == preempt_offset &&
			tअगर_need_resched());
पूर्ण

#अगर_घोषित CONFIG_PREEMPTION
बाह्य यंत्रlinkage व्योम preempt_schedule(व्योम);
#घोषणा __preempt_schedule() preempt_schedule()
बाह्य यंत्रlinkage व्योम preempt_schedule_notrace(व्योम);
#घोषणा __preempt_schedule_notrace() preempt_schedule_notrace()
#पूर्ण_अगर /* CONFIG_PREEMPTION */

#पूर्ण_अगर /* __ASM_PREEMPT_H */
