<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* 
 * smp.h: PowerPC-specअगरic SMP code.
 *
 * Original was a copy of sparc smp.h.  Now heavily modअगरied
 * क्रम PPC.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 * Copyright (C) 1996-2001 Cort Dougan <cort@fsmद_असल.com>
 */

#अगर_अघोषित _ASM_POWERPC_SMP_H
#घोषणा _ASM_POWERPC_SMP_H
#अगर_घोषित __KERNEL__

#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/kernel.h>
#समावेश <linux/irqवापस.h>

#अगर_अघोषित __ASSEMBLY__

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/paca.h>
#पूर्ण_अगर
#समावेश <यंत्र/percpu.h>

बाह्य पूर्णांक boot_cpuid;
बाह्य पूर्णांक spinning_secondaries;
बाह्य u32 *cpu_to_phys_id;
बाह्य bool coregroup_enabled;

बाह्य पूर्णांक cpu_to_chip_id(पूर्णांक cpu);
बाह्य पूर्णांक *chip_id_lookup_table;

#अगर_घोषित CONFIG_SMP

काष्ठा smp_ops_t अणु
	व्योम  (*message_pass)(पूर्णांक cpu, पूर्णांक msg);
#अगर_घोषित CONFIG_PPC_SMP_MUXED_IPI
	व्योम  (*cause_ipi)(पूर्णांक cpu);
#पूर्ण_अगर
	पूर्णांक   (*cause_nmi_ipi)(पूर्णांक cpu);
	व्योम  (*probe)(व्योम);
	पूर्णांक   (*kick_cpu)(पूर्णांक nr);
	पूर्णांक   (*prepare_cpu)(पूर्णांक nr);
	व्योम  (*setup_cpu)(पूर्णांक nr);
	व्योम  (*bringup_करोne)(व्योम);
	व्योम  (*take_समयbase)(व्योम);
	व्योम  (*give_समयbase)(व्योम);
	पूर्णांक   (*cpu_disable)(व्योम);
	व्योम  (*cpu_die)(अचिन्हित पूर्णांक nr);
	पूर्णांक   (*cpu_bootable)(अचिन्हित पूर्णांक nr);
#अगर_घोषित CONFIG_HOTPLUG_CPU
	व्योम  (*cpu_offline_self)(व्योम);
#पूर्ण_अगर
पूर्ण;

बाह्य पूर्णांक smp_send_nmi_ipi(पूर्णांक cpu, व्योम (*fn)(काष्ठा pt_regs *), u64 delay_us);
बाह्य पूर्णांक smp_send_safe_nmi_ipi(पूर्णांक cpu, व्योम (*fn)(काष्ठा pt_regs *), u64 delay_us);
बाह्य व्योम smp_send_debugger_अवरोध(व्योम);
बाह्य व्योम start_secondary_resume(व्योम);
बाह्य व्योम smp_generic_give_समयbase(व्योम);
बाह्य व्योम smp_generic_take_समयbase(व्योम);

DECLARE_PER_CPU(अचिन्हित पूर्णांक, cpu_pvr);

#अगर_घोषित CONFIG_HOTPLUG_CPU
पूर्णांक generic_cpu_disable(व्योम);
व्योम generic_cpu_die(अचिन्हित पूर्णांक cpu);
व्योम generic_set_cpu_dead(अचिन्हित पूर्णांक cpu);
व्योम generic_set_cpu_up(अचिन्हित पूर्णांक cpu);
पूर्णांक generic_check_cpu_restart(अचिन्हित पूर्णांक cpu);
पूर्णांक is_cpu_dead(अचिन्हित पूर्णांक cpu);
#अन्यथा
#घोषणा generic_set_cpu_up(i)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
#घोषणा raw_smp_processor_id()	(local_paca->paca_index)
#घोषणा hard_smp_processor_id() (get_paca()->hw_cpu_id)
#अन्यथा
/* 32-bit */
बाह्य पूर्णांक smp_hw_index[];

/*
 * This is particularly ugly: it appears we can't actually get the definition
 * of task_काष्ठा here, but we need access to the CPU this task is running on.
 * Instead of using task_काष्ठा we're using _TASK_CPU which is extracted from
 * यंत्र-offsets.h by kbuild to get the current processor ID.
 *
 * This also needs to be safeguarded when building यंत्र-offsets.s because at
 * that समय _TASK_CPU is not defined yet. It could have been guarded by
 * _TASK_CPU itself, but we want the build to fail अगर _TASK_CPU is missing
 * when building something अन्यथा than यंत्र-offsets.s
 */
#अगर_घोषित GENERATING_ASM_OFFSETS
#घोषणा raw_smp_processor_id()		(0)
#अन्यथा
#घोषणा raw_smp_processor_id()		(*(अचिन्हित पूर्णांक *)((व्योम *)current + _TASK_CPU))
#पूर्ण_अगर
#घोषणा hard_smp_processor_id() 	(smp_hw_index[smp_processor_id()])

अटल अंतरभूत पूर्णांक get_hard_smp_processor_id(पूर्णांक cpu)
अणु
	वापस smp_hw_index[cpu];
पूर्ण

अटल अंतरभूत व्योम set_hard_smp_processor_id(पूर्णांक cpu, पूर्णांक phys)
अणु
	smp_hw_index[cpu] = phys;
पूर्ण
#पूर्ण_अगर

DECLARE_PER_CPU(cpumask_var_t, cpu_sibling_map);
DECLARE_PER_CPU(cpumask_var_t, cpu_l2_cache_map);
DECLARE_PER_CPU(cpumask_var_t, cpu_core_map);
DECLARE_PER_CPU(cpumask_var_t, cpu_smallcore_map);

अटल अंतरभूत काष्ठा cpumask *cpu_sibling_mask(पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_sibling_map, cpu);
पूर्ण

अटल अंतरभूत काष्ठा cpumask *cpu_core_mask(पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_core_map, cpu);
पूर्ण

अटल अंतरभूत काष्ठा cpumask *cpu_l2_cache_mask(पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_l2_cache_map, cpu);
पूर्ण

अटल अंतरभूत काष्ठा cpumask *cpu_smallcore_mask(पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_smallcore_map, cpu);
पूर्ण

बाह्य पूर्णांक cpu_to_core_id(पूर्णांक cpu);

बाह्य bool has_big_cores;
बाह्य bool thपढ़ो_group_shares_l2;

#घोषणा cpu_smt_mask cpu_smt_mask
#अगर_घोषित CONFIG_SCHED_SMT
अटल अंतरभूत स्थिर काष्ठा cpumask *cpu_smt_mask(पूर्णांक cpu)
अणु
	अगर (has_big_cores)
		वापस per_cpu(cpu_smallcore_map, cpu);

	वापस per_cpu(cpu_sibling_map, cpu);
पूर्ण
#पूर्ण_अगर /* CONFIG_SCHED_SMT */

/* Since OpenPIC has only 4 IPIs, we use slightly dअगरferent message numbers.
 *
 * Make sure this matches खोलोpic_request_IPIs in खोलो_pic.c, or what shows up
 * in /proc/पूर्णांकerrupts will be wrong!!! --Troy */
#घोषणा PPC_MSG_CALL_FUNCTION	0
#घोषणा PPC_MSG_RESCHEDULE	1
#घोषणा PPC_MSG_TICK_BROADCAST	2
#घोषणा PPC_MSG_NMI_IPI		3

/* This is only used by the घातernv kernel */
#घोषणा PPC_MSG_RM_HOST_ACTION	4

#घोषणा NMI_IPI_ALL_OTHERS		-2

#अगर_घोषित CONFIG_NMI_IPI
बाह्य पूर्णांक smp_handle_nmi_ipi(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत पूर्णांक smp_handle_nmi_ipi(काष्ठा pt_regs *regs) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* क्रम irq controllers that have dedicated ipis per message (4) */
बाह्य पूर्णांक smp_request_message_ipi(पूर्णांक virq, पूर्णांक message);
बाह्य स्थिर अक्षर *smp_ipi_name[];

/* क्रम irq controllers with only a single ipi */
बाह्य व्योम smp_muxed_ipi_message_pass(पूर्णांक cpu, पूर्णांक msg);
बाह्य व्योम smp_muxed_ipi_set_message(पूर्णांक cpu, पूर्णांक msg);
बाह्य irqवापस_t smp_ipi_demux(व्योम);
बाह्य irqवापस_t smp_ipi_demux_relaxed(व्योम);

व्योम smp_init_pSeries(व्योम);
व्योम smp_init_cell(व्योम);
व्योम smp_setup_cpu_maps(व्योम);

बाह्य पूर्णांक __cpu_disable(व्योम);
बाह्य व्योम __cpu_die(अचिन्हित पूर्णांक cpu);

#अन्यथा
/* क्रम UP */
#घोषणा hard_smp_processor_id()		get_hard_smp_processor_id(0)
#घोषणा smp_setup_cpu_maps()
#घोषणा thपढ़ो_group_shares_l2  0
अटल अंतरभूत व्योम inhibit_secondary_onlining(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम uninhibit_secondary_onlining(व्योम) अणुपूर्ण
अटल अंतरभूत स्थिर काष्ठा cpumask *cpu_sibling_mask(पूर्णांक cpu)
अणु
	वापस cpumask_of(cpu);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cpumask *cpu_smallcore_mask(पूर्णांक cpu)
अणु
	वापस cpumask_of(cpu);
पूर्ण

अटल अंतरभूत स्थिर काष्ठा cpumask *cpu_l2_cache_mask(पूर्णांक cpu)
अणु
	वापस cpumask_of(cpu);
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

#अगर_घोषित CONFIG_PPC64
अटल अंतरभूत पूर्णांक get_hard_smp_processor_id(पूर्णांक cpu)
अणु
	वापस paca_ptrs[cpu]->hw_cpu_id;
पूर्ण

अटल अंतरभूत व्योम set_hard_smp_processor_id(पूर्णांक cpu, पूर्णांक phys)
अणु
	paca_ptrs[cpu]->hw_cpu_id = phys;
पूर्ण
#अन्यथा
/* 32-bit */
#अगर_अघोषित CONFIG_SMP
बाह्य पूर्णांक boot_cpuid_phys;
अटल अंतरभूत पूर्णांक get_hard_smp_processor_id(पूर्णांक cpu)
अणु
	वापस boot_cpuid_phys;
पूर्ण

अटल अंतरभूत व्योम set_hard_smp_processor_id(पूर्णांक cpu, पूर्णांक phys)
अणु
	boot_cpuid_phys = phys;
पूर्ण
#पूर्ण_अगर /* !CONFIG_SMP */
#पूर्ण_अगर /* !CONFIG_PPC64 */

#अगर defined(CONFIG_PPC64) && (defined(CONFIG_SMP) || defined(CONFIG_KEXEC_CORE))
बाह्य व्योम smp_release_cpus(व्योम);
#अन्यथा
अटल अंतरभूत व्योम smp_release_cpus(व्योम) अणु पूर्ण
#पूर्ण_अगर

बाह्य पूर्णांक smt_enabled_at_boot;

बाह्य व्योम smp_mpic_probe(व्योम);
बाह्य व्योम smp_mpic_setup_cpu(पूर्णांक cpu);
बाह्य पूर्णांक smp_generic_kick_cpu(पूर्णांक nr);
बाह्य पूर्णांक smp_generic_cpu_bootable(अचिन्हित पूर्णांक nr);


बाह्य व्योम smp_generic_give_समयbase(व्योम);
बाह्य व्योम smp_generic_take_समयbase(व्योम);

बाह्य काष्ठा smp_ops_t *smp_ops;

बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

/* Definitions relative to the secondary CPU spin loop
 * and entry poपूर्णांक. Not all of them exist on both 32 and
 * 64-bit but defining them all here करोesn't harm
 */
बाह्य व्योम generic_secondary_smp_init(व्योम);
बाह्य अचिन्हित दीर्घ __secondary_hold_spinloop;
बाह्य अचिन्हित दीर्घ __secondary_hold_acknowledge;
बाह्य अक्षर __secondary_hold;
बाह्य अचिन्हित पूर्णांक booting_thपढ़ो_hwid;

बाह्य व्योम __early_start(व्योम);
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_SMP_H) */
