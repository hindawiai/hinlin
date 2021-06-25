<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_PREEMPT_H
#घोषणा __ASM_PREEMPT_H

#समावेश <यंत्र/current.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/atomic_ops.h>

#अगर_घोषित CONFIG_HAVE_MARCH_Z196_FEATURES

/* We use the MSB mostly because its available */
#घोषणा PREEMPT_NEED_RESCHED	0x80000000
#घोषणा PREEMPT_ENABLED	(0 + PREEMPT_NEED_RESCHED)

अटल अंतरभूत पूर्णांक preempt_count(व्योम)
अणु
	वापस READ_ONCE(S390_lowcore.preempt_count) & ~PREEMPT_NEED_RESCHED;
पूर्ण

अटल अंतरभूत व्योम preempt_count_set(पूर्णांक pc)
अणु
	पूर्णांक old, new;

	करो अणु
		old = READ_ONCE(S390_lowcore.preempt_count);
		new = (old & PREEMPT_NEED_RESCHED) |
			(pc & ~PREEMPT_NEED_RESCHED);
	पूर्ण जबतक (__atomic_cmpxchg(&S390_lowcore.preempt_count,
				  old, new) != old);
पूर्ण

#घोषणा init_task_preempt_count(p)	करो अणु पूर्ण जबतक (0)

#घोषणा init_idle_preempt_count(p, cpu)	करो अणु \
	S390_lowcore.preempt_count = PREEMPT_ENABLED; \
पूर्ण जबतक (0)

अटल अंतरभूत व्योम set_preempt_need_resched(व्योम)
अणु
	__atomic_and(~PREEMPT_NEED_RESCHED, &S390_lowcore.preempt_count);
पूर्ण

अटल अंतरभूत व्योम clear_preempt_need_resched(व्योम)
अणु
	__atomic_or(PREEMPT_NEED_RESCHED, &S390_lowcore.preempt_count);
पूर्ण

अटल अंतरभूत bool test_preempt_need_resched(व्योम)
अणु
	वापस !(READ_ONCE(S390_lowcore.preempt_count) & PREEMPT_NEED_RESCHED);
पूर्ण

अटल अंतरभूत व्योम __preempt_count_add(पूर्णांक val)
अणु
	अगर (__builtin_स्थिरant_p(val) && (val >= -128) && (val <= 127))
		__atomic_add_स्थिर(val, &S390_lowcore.preempt_count);
	अन्यथा
		__atomic_add(val, &S390_lowcore.preempt_count);
पूर्ण

अटल अंतरभूत व्योम __preempt_count_sub(पूर्णांक val)
अणु
	__preempt_count_add(-val);
पूर्ण

अटल अंतरभूत bool __preempt_count_dec_and_test(व्योम)
अणु
	वापस __atomic_add(-1, &S390_lowcore.preempt_count) == 1;
पूर्ण

अटल अंतरभूत bool should_resched(पूर्णांक preempt_offset)
अणु
	वापस unlikely(READ_ONCE(S390_lowcore.preempt_count) ==
			preempt_offset);
पूर्ण

#अन्यथा /* CONFIG_HAVE_MARCH_Z196_FEATURES */

#घोषणा PREEMPT_ENABLED	(0)

अटल अंतरभूत पूर्णांक preempt_count(व्योम)
अणु
	वापस READ_ONCE(S390_lowcore.preempt_count);
पूर्ण

अटल अंतरभूत व्योम preempt_count_set(पूर्णांक pc)
अणु
	S390_lowcore.preempt_count = pc;
पूर्ण

#घोषणा init_task_preempt_count(p)	करो अणु पूर्ण जबतक (0)

#घोषणा init_idle_preempt_count(p, cpu)	करो अणु \
	S390_lowcore.preempt_count = PREEMPT_ENABLED; \
पूर्ण जबतक (0)

अटल अंतरभूत व्योम set_preempt_need_resched(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम clear_preempt_need_resched(व्योम)
अणु
पूर्ण

अटल अंतरभूत bool test_preempt_need_resched(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम __preempt_count_add(पूर्णांक val)
अणु
	S390_lowcore.preempt_count += val;
पूर्ण

अटल अंतरभूत व्योम __preempt_count_sub(पूर्णांक val)
अणु
	S390_lowcore.preempt_count -= val;
पूर्ण

अटल अंतरभूत bool __preempt_count_dec_and_test(व्योम)
अणु
	वापस !--S390_lowcore.preempt_count && tअगर_need_resched();
पूर्ण

अटल अंतरभूत bool should_resched(पूर्णांक preempt_offset)
अणु
	वापस unlikely(preempt_count() == preempt_offset &&
			tअगर_need_resched());
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_MARCH_Z196_FEATURES */

#अगर_घोषित CONFIG_PREEMPTION
बाह्य व्योम preempt_schedule(व्योम);
#घोषणा __preempt_schedule() preempt_schedule()
बाह्य व्योम preempt_schedule_notrace(व्योम);
#घोषणा __preempt_schedule_notrace() preempt_schedule_notrace()
#पूर्ण_अगर /* CONFIG_PREEMPTION */

#पूर्ण_अगर /* __ASM_PREEMPT_H */
