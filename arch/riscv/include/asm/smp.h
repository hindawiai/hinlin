<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_SMP_H
#घोषणा _ASM_RISCV_SMP_H

#समावेश <linux/cpumask.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/thपढ़ो_info.h>

#घोषणा INVALID_HARTID अच_दीर्घ_उच्च

काष्ठा seq_file;
बाह्य अचिन्हित दीर्घ boot_cpu_hartid;

काष्ठा riscv_ipi_ops अणु
	व्योम (*ipi_inject)(स्थिर काष्ठा cpumask *target);
	व्योम (*ipi_clear)(व्योम);
पूर्ण;

#अगर_घोषित CONFIG_SMP
/*
 * Mapping between linux logical cpu index and hartid.
 */
बाह्य अचिन्हित दीर्घ __cpuid_to_hartid_map[NR_CPUS];
#घोषणा cpuid_to_hartid_map(cpu)    __cpuid_to_hartid_map[cpu]

/* prपूर्णांक IPI stats */
व्योम show_ipi_stats(काष्ठा seq_file *p, पूर्णांक prec);

/* SMP initialization hook क्रम setup_arch */
व्योम __init setup_smp(व्योम);

/* Called from C code, this handles an IPI. */
व्योम handle_IPI(काष्ठा pt_regs *regs);

/* Hook क्रम the generic smp_call_function_many() routine. */
व्योम arch_send_call_function_ipi_mask(काष्ठा cpumask *mask);

/* Hook क्रम the generic smp_call_function_single() routine. */
व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);

पूर्णांक riscv_hartid_to_cpuid(पूर्णांक hartid);
व्योम riscv_cpuid_to_hartid_mask(स्थिर काष्ठा cpumask *in, काष्ठा cpumask *out);

/* Set custom IPI operations */
व्योम riscv_set_ipi_ops(स्थिर काष्ठा riscv_ipi_ops *ops);

/* Clear IPI क्रम current CPU */
व्योम riscv_clear_ipi(व्योम);

/* Secondary hart entry */
यंत्रlinkage व्योम smp_callin(व्योम);

/*
 * Obtains the hart ID of the currently executing task.  This relies on
 * THREAD_INFO_IN_TASK, but we define that unconditionally.
 */
#घोषणा raw_smp_processor_id() (current_thपढ़ो_info()->cpu)

#अगर defined CONFIG_HOTPLUG_CPU
पूर्णांक __cpu_disable(व्योम);
व्योम __cpu_die(अचिन्हित पूर्णांक cpu);
व्योम cpu_stop(व्योम);
#अन्यथा
#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

#अन्यथा

अटल अंतरभूत व्योम show_ipi_stats(काष्ठा seq_file *p, पूर्णांक prec)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक riscv_hartid_to_cpuid(पूर्णांक hartid)
अणु
	अगर (hartid == boot_cpu_hartid)
		वापस 0;

	वापस -1;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ cpuid_to_hartid_map(पूर्णांक cpu)
अणु
	वापस boot_cpu_hartid;
पूर्ण

अटल अंतरभूत व्योम riscv_cpuid_to_hartid_mask(स्थिर काष्ठा cpumask *in,
					      काष्ठा cpumask *out)
अणु
	cpumask_clear(out);
	cpumask_set_cpu(boot_cpu_hartid, out);
पूर्ण

अटल अंतरभूत व्योम riscv_set_ipi_ops(स्थिर काष्ठा riscv_ipi_ops *ops)
अणु
पूर्ण

अटल अंतरभूत व्योम riscv_clear_ipi(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

#अगर defined(CONFIG_HOTPLUG_CPU) && (CONFIG_SMP)
bool cpu_has_hotplug(अचिन्हित पूर्णांक cpu);
#अन्यथा
अटल अंतरभूत bool cpu_has_hotplug(अचिन्हित पूर्णांक cpu)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_RISCV_SMP_H */
