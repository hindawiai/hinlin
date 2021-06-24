<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_CLOCK_H
#घोषणा _LINUX_SCHED_CLOCK_H

#समावेश <linux/smp.h>

/*
 * Do not use outside of architecture code which knows its limitations.
 *
 * sched_घड़ी() has no promise of monotonicity or bounded drअगरt between
 * CPUs, use (which you should not) requires disabling IRQs.
 *
 * Please use one of the three पूर्णांकerfaces below.
 */
बाह्य अचिन्हित दीर्घ दीर्घ notrace sched_घड़ी(व्योम);

/*
 * See the comment in kernel/sched/घड़ी.c
 */
बाह्य u64 running_घड़ी(व्योम);
बाह्य u64 sched_घड़ी_cpu(पूर्णांक cpu);


बाह्य व्योम sched_घड़ी_init(व्योम);

#अगर_अघोषित CONFIG_HAVE_UNSTABLE_SCHED_CLOCK
अटल अंतरभूत व्योम sched_घड़ी_प्रकारick(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम clear_sched_घड़ी_stable(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम sched_घड़ी_idle_sleep_event(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम sched_घड़ी_idle_wakeup_event(व्योम)
अणु
पूर्ण

अटल अंतरभूत u64 cpu_घड़ी(पूर्णांक cpu)
अणु
	वापस sched_घड़ी();
पूर्ण

अटल अंतरभूत u64 local_घड़ी(व्योम)
अणु
	वापस sched_घड़ी();
पूर्ण
#अन्यथा
बाह्य पूर्णांक sched_घड़ी_stable(व्योम);
बाह्य व्योम clear_sched_घड़ी_stable(व्योम);

/*
 * When sched_घड़ी_stable(), __sched_घड़ी_offset provides the offset
 * between local_घड़ी() and sched_घड़ी().
 */
बाह्य u64 __sched_घड़ी_offset;

बाह्य व्योम sched_घड़ी_प्रकारick(व्योम);
बाह्य व्योम sched_घड़ी_प्रकारick_stable(व्योम);
बाह्य व्योम sched_घड़ी_idle_sleep_event(व्योम);
बाह्य व्योम sched_घड़ी_idle_wakeup_event(व्योम);

/*
 * As outlined in घड़ी.c, provides a fast, high resolution, nanosecond
 * समय source that is monotonic per cpu argument and has bounded drअगरt
 * between cpus.
 *
 * ######################### BIG FAT WARNING ##########################
 * # when comparing cpu_घड़ी(i) to cpu_घड़ी(j) क्रम i != j, समय can #
 * # go backwards !!                                                  #
 * ####################################################################
 */
अटल अंतरभूत u64 cpu_घड़ी(पूर्णांक cpu)
अणु
	वापस sched_घड़ी_cpu(cpu);
पूर्ण

अटल अंतरभूत u64 local_घड़ी(व्योम)
अणु
	वापस sched_घड़ी_cpu(raw_smp_processor_id());
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IRQ_TIME_ACCOUNTING
/*
 * An i/f to runसमय opt-in क्रम irq समय accounting based off of sched_घड़ी.
 * The reason क्रम this explicit opt-in is not to have perf penalty with
 * slow sched_घड़ीs.
 */
बाह्य व्योम enable_sched_घड़ी_irqसमय(व्योम);
बाह्य व्योम disable_sched_घड़ी_irqसमय(व्योम);
#अन्यथा
अटल अंतरभूत व्योम enable_sched_घड़ी_irqसमय(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम disable_sched_घड़ी_irqसमय(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCHED_CLOCK_H */
