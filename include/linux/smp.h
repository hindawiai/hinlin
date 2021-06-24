<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_SMP_H
#घोषणा __LINUX_SMP_H

/*
 *	Generic SMP support
 *		Alan Cox. <alan@redhat.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/init.h>
#समावेश <linux/smp_types.h>

प्रकार व्योम (*smp_call_func_t)(व्योम *info);
प्रकार bool (*smp_cond_func_t)(पूर्णांक cpu, व्योम *info);

/*
 * काष्ठाure shares (partial) layout with काष्ठा irq_work
 */
काष्ठा __call_single_data अणु
	काष्ठा __call_single_node node;
	smp_call_func_t func;
	व्योम *info;
पूर्ण;

#घोषणा CSD_INIT(_func, _info) \
	(काष्ठा __call_single_data)अणु .func = (_func), .info = (_info), पूर्ण

/* Use __aligned() to aव्योम to use 2 cache lines क्रम 1 csd */
प्रकार काष्ठा __call_single_data call_single_data_t
	__aligned(माप(काष्ठा __call_single_data));

#घोषणा INIT_CSD(_csd, _func, _info)		\
करो अणु						\
	*(_csd) = CSD_INIT((_func), (_info));	\
पूर्ण जबतक (0)

/*
 * Enqueue a llist_node on the call_single_queue; be very careful, पढ़ो
 * flush_smp_call_function_queue() in detail.
 */
बाह्य व्योम __smp_call_single_queue(पूर्णांक cpu, काष्ठा llist_node *node);

/* total number of cpus in this प्रणाली (may exceed NR_CPUS) */
बाह्य अचिन्हित पूर्णांक total_cpus;

पूर्णांक smp_call_function_single(पूर्णांक cpuid, smp_call_func_t func, व्योम *info,
			     पूर्णांक रुको);

व्योम on_each_cpu_cond_mask(smp_cond_func_t cond_func, smp_call_func_t func,
			   व्योम *info, bool रुको, स्थिर काष्ठा cpumask *mask);

पूर्णांक smp_call_function_single_async(पूर्णांक cpu, काष्ठा __call_single_data *csd);

/*
 * Cpus stopping functions in panic. All have शेष weak definitions.
 * Architecture-dependent code may override them.
 */
व्योम panic_smp_self_stop(व्योम);
व्योम nmi_panic_self_stop(काष्ठा pt_regs *regs);
व्योम crash_smp_send_stop(व्योम);

/*
 * Call a function on all processors
 */
अटल अंतरभूत व्योम on_each_cpu(smp_call_func_t func, व्योम *info, पूर्णांक रुको)
अणु
	on_each_cpu_cond_mask(शून्य, func, info, रुको, cpu_online_mask);
पूर्ण

/**
 * on_each_cpu_mask(): Run a function on processors specअगरied by
 * cpumask, which may include the local processor.
 * @mask: The set of cpus to run on (only runs on online subset).
 * @func: The function to run. This must be fast and non-blocking.
 * @info: An arbitrary poपूर्णांकer to pass to the function.
 * @रुको: If true, रुको (atomically) until function has completed
 *        on other CPUs.
 *
 * If @रुको is true, then वापसs once @func has वापसed.
 *
 * You must not call this function with disabled पूर्णांकerrupts or from a
 * hardware पूर्णांकerrupt handler or from a bottom half handler.  The
 * exception is that it may be used during early boot जबतक
 * early_boot_irqs_disabled is set.
 */
अटल अंतरभूत व्योम on_each_cpu_mask(स्थिर काष्ठा cpumask *mask,
				    smp_call_func_t func, व्योम *info, bool रुको)
अणु
	on_each_cpu_cond_mask(शून्य, func, info, रुको, mask);
पूर्ण

/*
 * Call a function on each processor क्रम which the supplied function
 * cond_func वापसs a positive value. This may include the local
 * processor.  May be used during early boot जबतक early_boot_irqs_disabled is
 * set. Use local_irq_save/restore() instead of local_irq_disable/enable().
 */
अटल अंतरभूत व्योम on_each_cpu_cond(smp_cond_func_t cond_func,
				    smp_call_func_t func, व्योम *info, bool रुको)
अणु
	on_each_cpu_cond_mask(cond_func, func, info, रुको, cpu_online_mask);
पूर्ण

#अगर_घोषित CONFIG_SMP

#समावेश <linux/preempt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/compiler.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/smp.h>

/*
 * मुख्य cross-CPU पूर्णांकerfaces, handles INIT, TLB flush, STOP, etc.
 * (defined in यंत्र header):
 */

/*
 * stops all CPUs but the current one:
 */
बाह्य व्योम smp_send_stop(व्योम);

/*
 * sends a 'reschedule' event to another CPU:
 */
बाह्य व्योम smp_send_reschedule(पूर्णांक cpu);


/*
 * Prepare machine क्रम booting other CPUs.
 */
बाह्य व्योम smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus);

/*
 * Bring a CPU up
 */
बाह्य पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpunum, काष्ठा task_काष्ठा *tidle);

/*
 * Final polishing of CPUs
 */
बाह्य व्योम smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus);

/*
 * Call a function on all other processors
 */
व्योम smp_call_function(smp_call_func_t func, व्योम *info, पूर्णांक रुको);
व्योम smp_call_function_many(स्थिर काष्ठा cpumask *mask,
			    smp_call_func_t func, व्योम *info, bool रुको);

पूर्णांक smp_call_function_any(स्थिर काष्ठा cpumask *mask,
			  smp_call_func_t func, व्योम *info, पूर्णांक रुको);

व्योम kick_all_cpus_sync(व्योम);
व्योम wake_up_all_idle_cpus(व्योम);

/*
 * Generic and arch helpers
 */
व्योम __init call_function_init(व्योम);
व्योम generic_smp_call_function_single_पूर्णांकerrupt(व्योम);
#घोषणा generic_smp_call_function_पूर्णांकerrupt \
	generic_smp_call_function_single_पूर्णांकerrupt

/*
 * Mark the boot cpu "online" so that it can call console drivers in
 * prपूर्णांकk() and can access its per-cpu storage.
 */
व्योम smp_prepare_boot_cpu(व्योम);

बाह्य अचिन्हित पूर्णांक setup_max_cpus;
बाह्य व्योम __init setup_nr_cpu_ids(व्योम);
बाह्य व्योम __init smp_init(व्योम);

बाह्य पूर्णांक __boot_cpu_id;

अटल अंतरभूत पूर्णांक get_boot_cpu_id(व्योम)
अणु
	वापस __boot_cpu_id;
पूर्ण

#अन्यथा /* !SMP */

अटल अंतरभूत व्योम smp_send_stop(व्योम) अणु पूर्ण

/*
 *	These macros fold the SMP functionality पूर्णांकo a single CPU प्रणाली
 */
#घोषणा raw_smp_processor_id()			0
अटल अंतरभूत व्योम up_smp_call_function(smp_call_func_t func, व्योम *info)
अणु
पूर्ण
#घोषणा smp_call_function(func, info, रुको) \
			(up_smp_call_function(func, info))

अटल अंतरभूत व्योम smp_send_reschedule(पूर्णांक cpu) अणु पूर्ण
#घोषणा smp_prepare_boot_cpu()			करो अणुपूर्ण जबतक (0)
#घोषणा smp_call_function_many(mask, func, info, रुको) \
			(up_smp_call_function(func, info))
अटल अंतरभूत व्योम call_function_init(व्योम) अणु पूर्ण

अटल अंतरभूत पूर्णांक
smp_call_function_any(स्थिर काष्ठा cpumask *mask, smp_call_func_t func,
		      व्योम *info, पूर्णांक रुको)
अणु
	वापस smp_call_function_single(0, func, info, रुको);
पूर्ण

अटल अंतरभूत व्योम kick_all_cpus_sync(व्योम) अणु  पूर्ण
अटल अंतरभूत व्योम wake_up_all_idle_cpus(व्योम) अणु  पूर्ण

#अगर_घोषित CONFIG_UP_LATE_INIT
बाह्य व्योम __init up_late_init(व्योम);
अटल अंतरभूत व्योम smp_init(व्योम) अणु up_late_init(); पूर्ण
#अन्यथा
अटल अंतरभूत व्योम smp_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक get_boot_cpu_id(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !SMP */

/**
 * raw_processor_id() - get the current (unstable) CPU id
 *
 * For then you know what you are करोing and need an unstable
 * CPU id.
 */

/**
 * smp_processor_id() - get the current (stable) CPU id
 *
 * This is the normal accessor to the CPU id and should be used
 * whenever possible.
 *
 * The CPU id is stable when:
 *
 *  - IRQs are disabled;
 *  - preemption is disabled;
 *  - the task is CPU affine.
 *
 * When CONFIG_DEBUG_PREEMPT; we verअगरy these assumption and WARN
 * when smp_processor_id() is used when the CPU id is not stable.
 */

/*
 * Allow the architecture to dअगरferentiate between a stable and unstable पढ़ो.
 * For example, x86 uses an IRQ-safe यंत्र-अस्थिर पढ़ो क्रम the unstable but a
 * regular यंत्र पढ़ो क्रम the stable.
 */
#अगर_अघोषित __smp_processor_id
#घोषणा __smp_processor_id(x) raw_smp_processor_id(x)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_PREEMPT
  बाह्य अचिन्हित पूर्णांक debug_smp_processor_id(व्योम);
# define smp_processor_id() debug_smp_processor_id()
#अन्यथा
# define smp_processor_id() __smp_processor_id()
#पूर्ण_अगर

#घोषणा get_cpu()		(अणु preempt_disable(); __smp_processor_id(); पूर्ण)
#घोषणा put_cpu()		preempt_enable()

/*
 * Callback to arch code अगर there's nosmp or maxcpus=0 on the
 * boot command line:
 */
बाह्य व्योम arch_disable_smp_support(व्योम);

बाह्य व्योम arch_thaw_secondary_cpus_begin(व्योम);
बाह्य व्योम arch_thaw_secondary_cpus_end(व्योम);

व्योम smp_setup_processor_id(व्योम);

पूर्णांक smp_call_on_cpu(अचिन्हित पूर्णांक cpu, पूर्णांक (*func)(व्योम *), व्योम *par,
		    bool phys);

/* SMP core functions */
पूर्णांक smpcfd_prepare_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक smpcfd_dead_cpu(अचिन्हित पूर्णांक cpu);
पूर्णांक smpcfd_dying_cpu(अचिन्हित पूर्णांक cpu);

#पूर्ण_अगर /* __LINUX_SMP_H */
