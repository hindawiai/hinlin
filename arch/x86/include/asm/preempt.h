<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_PREEMPT_H
#घोषणा __ASM_PREEMPT_H

#समावेश <यंत्र/rmwcc.h>
#समावेश <यंत्र/percpu.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/अटल_call_types.h>

DECLARE_PER_CPU(पूर्णांक, __preempt_count);

/* We use the MSB mostly because its available */
#घोषणा PREEMPT_NEED_RESCHED	0x80000000

/*
 * We use the PREEMPT_NEED_RESCHED bit as an inverted NEED_RESCHED such
 * that a decrement hitting 0 means we can and should reschedule.
 */
#घोषणा PREEMPT_ENABLED	(0 + PREEMPT_NEED_RESCHED)

/*
 * We mask the PREEMPT_NEED_RESCHED bit so as not to confuse all current users
 * that think a non-zero value indicates we cannot preempt.
 */
अटल __always_अंतरभूत पूर्णांक preempt_count(व्योम)
अणु
	वापस raw_cpu_पढ़ो_4(__preempt_count) & ~PREEMPT_NEED_RESCHED;
पूर्ण

अटल __always_अंतरभूत व्योम preempt_count_set(पूर्णांक pc)
अणु
	पूर्णांक old, new;

	करो अणु
		old = raw_cpu_पढ़ो_4(__preempt_count);
		new = (old & PREEMPT_NEED_RESCHED) |
			(pc & ~PREEMPT_NEED_RESCHED);
	पूर्ण जबतक (raw_cpu_cmpxchg_4(__preempt_count, old, new) != old);
पूर्ण

/*
 * must be macros to aव्योम header recursion hell
 */
#घोषणा init_task_preempt_count(p) करो अणु पूर्ण जबतक (0)

#घोषणा init_idle_preempt_count(p, cpu) करो अणु \
	per_cpu(__preempt_count, (cpu)) = PREEMPT_ENABLED; \
पूर्ण जबतक (0)

/*
 * We fold the NEED_RESCHED bit पूर्णांकo the preempt count such that
 * preempt_enable() can decrement and test क्रम needing to reschedule with a
 * single inकाष्ठाion.
 *
 * We invert the actual bit, so that when the decrement hits 0 we know we both
 * need to resched (the bit is cleared) and can resched (no preempt count).
 */

अटल __always_अंतरभूत व्योम set_preempt_need_resched(व्योम)
अणु
	raw_cpu_and_4(__preempt_count, ~PREEMPT_NEED_RESCHED);
पूर्ण

अटल __always_अंतरभूत व्योम clear_preempt_need_resched(व्योम)
अणु
	raw_cpu_or_4(__preempt_count, PREEMPT_NEED_RESCHED);
पूर्ण

अटल __always_अंतरभूत bool test_preempt_need_resched(व्योम)
अणु
	वापस !(raw_cpu_पढ़ो_4(__preempt_count) & PREEMPT_NEED_RESCHED);
पूर्ण

/*
 * The various preempt_count add/sub methods
 */

अटल __always_अंतरभूत व्योम __preempt_count_add(पूर्णांक val)
अणु
	raw_cpu_add_4(__preempt_count, val);
पूर्ण

अटल __always_अंतरभूत व्योम __preempt_count_sub(पूर्णांक val)
अणु
	raw_cpu_add_4(__preempt_count, -val);
पूर्ण

/*
 * Because we keep PREEMPT_NEED_RESCHED set when we करो _not_ need to reschedule
 * a decrement which hits zero means we have no preempt_count and should
 * reschedule.
 */
अटल __always_अंतरभूत bool __preempt_count_dec_and_test(व्योम)
अणु
	वापस GEN_UNARY_RMWcc("decl", __preempt_count, e, __percpu_arg([var]));
पूर्ण

/*
 * Returns true when we need to resched and can (barring IRQ state).
 */
अटल __always_अंतरभूत bool should_resched(पूर्णांक preempt_offset)
अणु
	वापस unlikely(raw_cpu_पढ़ो_4(__preempt_count) == preempt_offset);
पूर्ण

#अगर_घोषित CONFIG_PREEMPTION

बाह्य यंत्रlinkage व्योम preempt_schedule(व्योम);
बाह्य यंत्रlinkage व्योम preempt_schedule_thunk(व्योम);

#घोषणा __preempt_schedule_func preempt_schedule_thunk

बाह्य यंत्रlinkage व्योम preempt_schedule_notrace(व्योम);
बाह्य यंत्रlinkage व्योम preempt_schedule_notrace_thunk(व्योम);

#घोषणा __preempt_schedule_notrace_func preempt_schedule_notrace_thunk

#अगर_घोषित CONFIG_PREEMPT_DYNAMIC

DECLARE_STATIC_CALL(preempt_schedule, __preempt_schedule_func);

#घोषणा __preempt_schedule() \
करो अणु \
	__STATIC_CALL_MOD_ADDRESSABLE(preempt_schedule); \
	यंत्र अस्थिर ("call " STATIC_CALL_TRAMP_STR(preempt_schedule) : ASM_CALL_CONSTRAINT); \
पूर्ण जबतक (0)

DECLARE_STATIC_CALL(preempt_schedule_notrace, __preempt_schedule_notrace_func);

#घोषणा __preempt_schedule_notrace() \
करो अणु \
	__STATIC_CALL_MOD_ADDRESSABLE(preempt_schedule_notrace); \
	यंत्र अस्थिर ("call " STATIC_CALL_TRAMP_STR(preempt_schedule_notrace) : ASM_CALL_CONSTRAINT); \
पूर्ण जबतक (0)

#अन्यथा /* PREEMPT_DYNAMIC */

#घोषणा __preempt_schedule() \
	यंत्र अस्थिर ("call preempt_schedule_thunk" : ASM_CALL_CONSTRAINT);

#घोषणा __preempt_schedule_notrace() \
	यंत्र अस्थिर ("call preempt_schedule_notrace_thunk" : ASM_CALL_CONSTRAINT);

#पूर्ण_अगर /* PREEMPT_DYNAMIC */

#पूर्ण_अगर /* PREEMPTION */

#पूर्ण_अगर /* __ASM_PREEMPT_H */
