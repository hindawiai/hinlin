<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KERNEL_STAT_H
#घोषणा _LINUX_KERNEL_STAT_H

#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/vसमय.स>
#समावेश <यंत्र/irq.h>

/*
 * 'kernel_stat.h' contains the definitions needed क्रम करोing
 * some kernel statistics (CPU usage, context चयनes ...),
 * used by rstatd/perfmeter
 */

क्रमागत cpu_usage_stat अणु
	CPUTIME_USER,
	CPUTIME_NICE,
	CPUTIME_SYSTEM,
	CPUTIME_SOFTIRQ,
	CPUTIME_IRQ,
	CPUTIME_IDLE,
	CPUTIME_IOWAIT,
	CPUTIME_STEAL,
	CPUTIME_GUEST,
	CPUTIME_GUEST_NICE,
	NR_STATS,
पूर्ण;

काष्ठा kernel_cpustat अणु
	u64 cpustat[NR_STATS];
पूर्ण;

काष्ठा kernel_stat अणु
	अचिन्हित दीर्घ irqs_sum;
	अचिन्हित पूर्णांक softirqs[NR_SOFTIRQS];
पूर्ण;

DECLARE_PER_CPU(काष्ठा kernel_stat, kstat);
DECLARE_PER_CPU(काष्ठा kernel_cpustat, kernel_cpustat);

/* Must have preemption disabled क्रम this to be meaningful. */
#घोषणा kstat_this_cpu this_cpu_ptr(&kstat)
#घोषणा kcpustat_this_cpu this_cpu_ptr(&kernel_cpustat)
#घोषणा kstat_cpu(cpu) per_cpu(kstat, cpu)
#घोषणा kcpustat_cpu(cpu) per_cpu(kernel_cpustat, cpu)

बाह्य अचिन्हित दीर्घ दीर्घ nr_context_चयनes(व्योम);

बाह्य अचिन्हित पूर्णांक kstat_irqs_cpu(अचिन्हित पूर्णांक irq, पूर्णांक cpu);
बाह्य व्योम kstat_incr_irq_this_cpu(अचिन्हित पूर्णांक irq);

अटल अंतरभूत व्योम kstat_incr_softirqs_this_cpu(अचिन्हित पूर्णांक irq)
अणु
	__this_cpu_inc(kstat.softirqs[irq]);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक kstat_softirqs_cpu(अचिन्हित पूर्णांक irq, पूर्णांक cpu)
अणु
       वापस kstat_cpu(cpu).softirqs[irq];
पूर्ण

/*
 * Number of पूर्णांकerrupts per specअगरic IRQ source, since bootup
 */
बाह्य अचिन्हित पूर्णांक kstat_irqs_usr(अचिन्हित पूर्णांक irq);

/*
 * Number of पूर्णांकerrupts per cpu, since bootup
 */
अटल अंतरभूत अचिन्हित पूर्णांक kstat_cpu_irqs_sum(अचिन्हित पूर्णांक cpu)
अणु
	वापस kstat_cpu(cpu).irqs_sum;
पूर्ण

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_GEN
बाह्य u64 kcpustat_field(काष्ठा kernel_cpustat *kcpustat,
			  क्रमागत cpu_usage_stat usage, पूर्णांक cpu);
बाह्य व्योम kcpustat_cpu_fetch(काष्ठा kernel_cpustat *dst, पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत u64 kcpustat_field(काष्ठा kernel_cpustat *kcpustat,
				 क्रमागत cpu_usage_stat usage, पूर्णांक cpu)
अणु
	वापस kcpustat->cpustat[usage];
पूर्ण

अटल अंतरभूत व्योम kcpustat_cpu_fetch(काष्ठा kernel_cpustat *dst, पूर्णांक cpu)
अणु
	*dst = kcpustat_cpu(cpu);
पूर्ण

#पूर्ण_अगर

बाह्य व्योम account_user_समय(काष्ठा task_काष्ठा *, u64);
बाह्य व्योम account_guest_समय(काष्ठा task_काष्ठा *, u64);
बाह्य व्योम account_प्रणाली_समय(काष्ठा task_काष्ठा *, पूर्णांक, u64);
बाह्य व्योम account_प्रणाली_index_समय(काष्ठा task_काष्ठा *, u64,
				      क्रमागत cpu_usage_stat);
बाह्य व्योम account_steal_समय(u64);
बाह्य व्योम account_idle_समय(u64);

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
अटल अंतरभूत व्योम account_process_tick(काष्ठा task_काष्ठा *tsk, पूर्णांक user)
अणु
	vसमय_flush(tsk);
पूर्ण
#अन्यथा
बाह्य व्योम account_process_tick(काष्ठा task_काष्ठा *, पूर्णांक user);
#पूर्ण_अगर

बाह्य व्योम account_idle_ticks(अचिन्हित दीर्घ ticks);

#पूर्ण_अगर /* _LINUX_KERNEL_STAT_H */
