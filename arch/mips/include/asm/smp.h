<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of this
 * archive क्रम more details.
 *
 * Copyright (C) 2000 - 2001 by Kanoj Sarcar (kanoj@sgi.com)
 * Copyright (C) 2000 - 2001 by Silicon Graphics, Inc.
 * Copyright (C) 2000, 2001, 2002 Ralf Baechle
 * Copyright (C) 2000, 2001 Broadcom Corporation
 */
#अगर_अघोषित __ASM_SMP_H
#घोषणा __ASM_SMP_H

#समावेश <linux/bitops.h>
#समावेश <linux/linkage.h>
#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/cpumask.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/smp-ops.h>

बाह्य पूर्णांक smp_num_siblings;
बाह्य cpumask_t cpu_sibling_map[];
बाह्य cpumask_t cpu_core_map[];
बाह्य cpumask_t cpu_क्रमeign_map[];

अटल अंतरभूत पूर्णांक raw_smp_processor_id(व्योम)
अणु
#अगर defined(__VDSO__)
	बाह्य पूर्णांक vdso_smp_processor_id(व्योम)
		__compileसमय_error("VDSO should not call smp_processor_id()");
	वापस vdso_smp_processor_id();
#अन्यथा
	वापस current_thपढ़ो_info()->cpu;
#पूर्ण_अगर
पूर्ण
#घोषणा raw_smp_processor_id raw_smp_processor_id

/* Map from cpu id to sequential logical cpu number.  This will only
   not be idempotent when cpus failed to come on-line.	*/
बाह्य पूर्णांक __cpu_number_map[CONFIG_MIPS_NR_CPU_NR_MAP];
#घोषणा cpu_number_map(cpu)  __cpu_number_map[cpu]

/* The reverse map from sequential logical cpu number to cpu id.  */
बाह्य पूर्णांक __cpu_logical_map[NR_CPUS];
#घोषणा cpu_logical_map(cpu)  __cpu_logical_map[cpu]

#घोषणा NO_PROC_ID	(-1)

#घोषणा SMP_RESCHEDULE_YOURSELF 0x1	/* XXX braindead */
#घोषणा SMP_CALL_FUNCTION	0x2
/* Octeon - Tell another core to flush its icache */
#घोषणा SMP_ICACHE_FLUSH	0x4
#घोषणा SMP_ASK_C0COUNT		0x8

/* Mask of CPUs which are currently definitely operating coherently */
बाह्य cpumask_t cpu_coherent_mask;

बाह्य यंत्रlinkage व्योम smp_bootstrap(व्योम);

बाह्य व्योम calculate_cpu_क्रमeign_map(व्योम);

/*
 * this function sends a 'reschedule' IPI to another CPU.
 * it goes straight through and wastes no समय serializing
 * anything. Worst हाल is that we lose a reschedule ...
 */
अटल अंतरभूत व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	बाह्य स्थिर काष्ठा plat_smp_ops *mp_ops;	/* निजी */

	mp_ops->send_ipi_single(cpu, SMP_RESCHEDULE_YOURSELF);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल अंतरभूत पूर्णांक __cpu_disable(व्योम)
अणु
	बाह्य स्थिर काष्ठा plat_smp_ops *mp_ops;	/* निजी */

	वापस mp_ops->cpu_disable();
पूर्ण

अटल अंतरभूत व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	बाह्य स्थिर काष्ठा plat_smp_ops *mp_ops;	/* निजी */

	mp_ops->cpu_die(cpu);
पूर्ण

बाह्य व्योम play_dead(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC
अटल अंतरभूत व्योम kexec_nonboot_cpu(व्योम)
अणु
	बाह्य स्थिर काष्ठा plat_smp_ops *mp_ops;	/* निजी */

	वापस mp_ops->kexec_nonboot_cpu();
पूर्ण

अटल अंतरभूत व्योम *kexec_nonboot_cpu_func(व्योम)
अणु
	बाह्य स्थिर काष्ठा plat_smp_ops *mp_ops;	/* निजी */

	वापस mp_ops->kexec_nonboot_cpu;
पूर्ण
#पूर्ण_अगर

/*
 * This function will set up the necessary IPIs क्रम Linux to communicate
 * with the CPUs in mask.
 * Return 0 on success.
 */
पूर्णांक mips_smp_ipi_allocate(स्थिर काष्ठा cpumask *mask);

/*
 * This function will मुक्त up IPIs allocated with mips_smp_ipi_allocate to the
 * CPUs in mask, which must be a subset of the IPIs that have been configured.
 * Return 0 on success.
 */
पूर्णांक mips_smp_ipi_मुक्त(स्थिर काष्ठा cpumask *mask);

अटल अंतरभूत व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	बाह्य स्थिर काष्ठा plat_smp_ops *mp_ops;	/* निजी */

	mp_ops->send_ipi_single(cpu, SMP_CALL_FUNCTION);
पूर्ण

अटल अंतरभूत व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	बाह्य स्थिर काष्ठा plat_smp_ops *mp_ops;	/* निजी */

	mp_ops->send_ipi_mask(mask, SMP_CALL_FUNCTION);
पूर्ण

#पूर्ण_अगर /* __ASM_SMP_H */
