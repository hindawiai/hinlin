<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 ARM Ltd.
 */
#अगर_अघोषित __ASM_SMP_H
#घोषणा __ASM_SMP_H

#समावेश <linux/स्थिर.h>

/* Values क्रम secondary_data.status */
#घोषणा CPU_STUCK_REASON_SHIFT		(8)
#घोषणा CPU_BOOT_STATUS_MASK		((UL(1) << CPU_STUCK_REASON_SHIFT) - 1)

#घोषणा CPU_MMU_OFF			(-1)
#घोषणा CPU_BOOT_SUCCESS		(0)
/* The cpu invoked ops->cpu_die, synchronise it with cpu_समाप्त */
#घोषणा CPU_KILL_ME			(1)
/* The cpu couldn't die gracefully and is looping in the kernel */
#घोषणा CPU_STUCK_IN_KERNEL		(2)
/* Fatal प्रणाली error detected by secondary CPU, crash the प्रणाली */
#घोषणा CPU_PANIC_KERNEL		(3)

#घोषणा CPU_STUCK_REASON_52_BIT_VA	(UL(1) << CPU_STUCK_REASON_SHIFT)
#घोषणा CPU_STUCK_REASON_NO_GRAN	(UL(2) << CPU_STUCK_REASON_SHIFT)

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/percpu.h>

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/thपढ़ो_info.h>

DECLARE_PER_CPU_READ_MOSTLY(पूर्णांक, cpu_number);

/*
 * We करोn't use this_cpu_पढ़ो(cpu_number) as that has implicit ग_लिखोs to
 * preempt_count, and associated (compiler) barriers, that we'd like to aव्योम
 * the expense of. If we're preemptible, the value can be stale at use anyway.
 * And we can't use this_cpu_ptr() either, as that winds up recursing back
 * here under CONFIG_DEBUG_PREEMPT=y.
 */
#घोषणा raw_smp_processor_id() (*raw_cpu_ptr(&cpu_number))

/*
 * Logical CPU mapping.
 */
बाह्य u64 __cpu_logical_map[NR_CPUS];
बाह्य u64 cpu_logical_map(अचिन्हित पूर्णांक cpu);

अटल अंतरभूत व्योम set_cpu_logical_map(अचिन्हित पूर्णांक cpu, u64 hwid)
अणु
	__cpu_logical_map[cpu] = hwid;
पूर्ण

काष्ठा seq_file;

/*
 * Discover the set of possible CPUs and determine their
 * SMP operations.
 */
बाह्य व्योम smp_init_cpus(व्योम);

/*
 * Register IPI पूर्णांकerrupts with the arch SMP code
 */
बाह्य व्योम set_smp_ipi_range(पूर्णांक ipi_base, पूर्णांक nr_ipi);

/*
 * Called from the secondary holding pen, this is the secondary CPU entry poपूर्णांक.
 */
यंत्रlinkage व्योम secondary_start_kernel(व्योम);

/*
 * Initial data क्रम bringing up a secondary CPU.
 * @stack  - sp क्रम the secondary CPU
 * @status - Result passed back from the secondary CPU to
 *           indicate failure.
 */
काष्ठा secondary_data अणु
	व्योम *stack;
	काष्ठा task_काष्ठा *task;
	दीर्घ status;
पूर्ण;

बाह्य काष्ठा secondary_data secondary_data;
बाह्य दीर्घ __early_cpu_boot_status;
बाह्य व्योम secondary_entry(व्योम);

बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

#अगर_घोषित CONFIG_ARM64_ACPI_PARKING_PROTOCOL
बाह्य व्योम arch_send_wakeup_ipi_mask(स्थिर काष्ठा cpumask *mask);
#अन्यथा
अटल अंतरभूत व्योम arch_send_wakeup_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	BUILD_BUG();
पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक __cpu_disable(व्योम);

बाह्य व्योम __cpu_die(अचिन्हित पूर्णांक cpu);
बाह्य व्योम cpu_die(व्योम);
बाह्य व्योम cpu_die_early(व्योम);

अटल अंतरभूत व्योम cpu_park_loop(व्योम)
अणु
	क्रम (;;) अणु
		wfe();
		wfi();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम update_cpu_boot_status(पूर्णांक val)
अणु
	WRITE_ONCE(secondary_data.status, val);
	/* Ensure the visibility of the status update */
	dsb(ishst);
पूर्ण

/*
 * The calling secondary CPU has detected serious configuration mismatch,
 * which calls क्रम a kernel panic. Update the boot status and park the calling
 * CPU.
 */
अटल अंतरभूत व्योम cpu_panic_kernel(व्योम)
अणु
	update_cpu_boot_status(CPU_PANIC_KERNEL);
	cpu_park_loop();
पूर्ण

/*
 * If a secondary CPU enters the kernel but fails to come online,
 * (e.g. due to mismatched features), and cannot निकास the kernel,
 * we increment cpus_stuck_in_kernel and leave the CPU in a
 * quiesecent loop within the kernel text. The memory containing
 * this loop must not be re-used क्रम anything अन्यथा as the 'stuck'
 * core is executing it.
 *
 * This function is used to inhibit features like kexec and hibernate.
 */
bool cpus_are_stuck_in_kernel(व्योम);

बाह्य व्योम crash_smp_send_stop(व्योम);
बाह्य bool smp_crash_stop_failed(व्योम);
बाह्य व्योम panic_smp_self_stop(व्योम);

#पूर्ण_अगर /* अगरndef __ASSEMBLY__ */

#पूर्ण_अगर /* अगरndef __ASM_SMP_H */
