<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SMP_H
#घोषणा _ASM_X86_SMP_H
#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/cpumask.h>
#समावेश <यंत्र/percpu.h>

#समावेश <यंत्र/thपढ़ो_info.h>
#समावेश <यंत्र/cpumask.h>

बाह्य पूर्णांक smp_num_siblings;
बाह्य अचिन्हित पूर्णांक num_processors;

DECLARE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_sibling_map);
DECLARE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_core_map);
DECLARE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_die_map);
/* cpus sharing the last level cache: */
DECLARE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_llc_shared_map);
DECLARE_PER_CPU_READ_MOSTLY(u16, cpu_llc_id);
DECLARE_PER_CPU_READ_MOSTLY(पूर्णांक, cpu_number);

अटल अंतरभूत काष्ठा cpumask *cpu_llc_shared_mask(पूर्णांक cpu)
अणु
	वापस per_cpu(cpu_llc_shared_map, cpu);
पूर्ण

DECLARE_EARLY_PER_CPU_READ_MOSTLY(u16, x86_cpu_to_apicid);
DECLARE_EARLY_PER_CPU_READ_MOSTLY(u32, x86_cpu_to_acpiid);
DECLARE_EARLY_PER_CPU_READ_MOSTLY(u16, x86_bios_cpu_apicid);
#अगर defined(CONFIG_X86_LOCAL_APIC) && defined(CONFIG_X86_32)
DECLARE_EARLY_PER_CPU_READ_MOSTLY(पूर्णांक, x86_cpu_to_logical_apicid);
#पूर्ण_अगर

काष्ठा task_काष्ठा;

काष्ठा smp_ops अणु
	व्योम (*smp_prepare_boot_cpu)(व्योम);
	व्योम (*smp_prepare_cpus)(अचिन्हित max_cpus);
	व्योम (*smp_cpus_करोne)(अचिन्हित max_cpus);

	व्योम (*stop_other_cpus)(पूर्णांक रुको);
	व्योम (*crash_stop_other_cpus)(व्योम);
	व्योम (*smp_send_reschedule)(पूर्णांक cpu);

	पूर्णांक (*cpu_up)(अचिन्हित cpu, काष्ठा task_काष्ठा *tidle);
	पूर्णांक (*cpu_disable)(व्योम);
	व्योम (*cpu_die)(अचिन्हित पूर्णांक cpu);
	व्योम (*play_dead)(व्योम);

	व्योम (*send_call_func_ipi)(स्थिर काष्ठा cpumask *mask);
	व्योम (*send_call_func_single_ipi)(पूर्णांक cpu);
पूर्ण;

/* Globals due to paravirt */
बाह्य व्योम set_cpu_sibling_map(पूर्णांक cpu);

#अगर_घोषित CONFIG_SMP
बाह्य काष्ठा smp_ops smp_ops;

अटल अंतरभूत व्योम smp_send_stop(व्योम)
अणु
	smp_ops.stop_other_cpus(0);
पूर्ण

अटल अंतरभूत व्योम stop_other_cpus(व्योम)
अणु
	smp_ops.stop_other_cpus(1);
पूर्ण

अटल अंतरभूत व्योम smp_prepare_boot_cpu(व्योम)
अणु
	smp_ops.smp_prepare_boot_cpu();
पूर्ण

अटल अंतरभूत व्योम smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
	smp_ops.smp_prepare_cpus(max_cpus);
पूर्ण

अटल अंतरभूत व्योम smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus)
अणु
	smp_ops.smp_cpus_करोne(max_cpus);
पूर्ण

अटल अंतरभूत पूर्णांक __cpu_up(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *tidle)
अणु
	वापस smp_ops.cpu_up(cpu, tidle);
पूर्ण

अटल अंतरभूत पूर्णांक __cpu_disable(व्योम)
अणु
	वापस smp_ops.cpu_disable();
पूर्ण

अटल अंतरभूत व्योम __cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	smp_ops.cpu_die(cpu);
पूर्ण

अटल अंतरभूत व्योम play_dead(व्योम)
अणु
	smp_ops.play_dead();
पूर्ण

अटल अंतरभूत व्योम smp_send_reschedule(पूर्णांक cpu)
अणु
	smp_ops.smp_send_reschedule(cpu);
पूर्ण

अटल अंतरभूत व्योम arch_send_call_function_single_ipi(पूर्णांक cpu)
अणु
	smp_ops.send_call_func_single_ipi(cpu);
पूर्ण

अटल अंतरभूत व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask)
अणु
	smp_ops.send_call_func_ipi(mask);
पूर्ण

व्योम cpu_disable_common(व्योम);
व्योम native_smp_prepare_boot_cpu(व्योम);
व्योम native_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus);
व्योम calculate_max_logical_packages(व्योम);
व्योम native_smp_cpus_करोne(अचिन्हित पूर्णांक max_cpus);
पूर्णांक common_cpu_up(अचिन्हित पूर्णांक cpunum, काष्ठा task_काष्ठा *tidle);
पूर्णांक native_cpu_up(अचिन्हित पूर्णांक cpunum, काष्ठा task_काष्ठा *tidle);
पूर्णांक native_cpu_disable(व्योम);
पूर्णांक common_cpu_die(अचिन्हित पूर्णांक cpu);
व्योम native_cpu_die(अचिन्हित पूर्णांक cpu);
व्योम hlt_play_dead(व्योम);
व्योम native_play_dead(व्योम);
व्योम play_dead_common(व्योम);
व्योम wbinvd_on_cpu(पूर्णांक cpu);
पूर्णांक wbinvd_on_all_cpus(व्योम);
व्योम cond_wakeup_cpu0(व्योम);

व्योम native_smp_send_reschedule(पूर्णांक cpu);
व्योम native_send_call_func_ipi(स्थिर काष्ठा cpumask *mask);
व्योम native_send_call_func_single_ipi(पूर्णांक cpu);
व्योम x86_idle_thपढ़ो_init(अचिन्हित पूर्णांक cpu, काष्ठा task_काष्ठा *idle);

व्योम smp_store_boot_cpu_info(व्योम);
व्योम smp_store_cpu_info(पूर्णांक id);

यंत्रlinkage __visible व्योम smp_reboot_पूर्णांकerrupt(व्योम);
__visible व्योम smp_reschedule_पूर्णांकerrupt(काष्ठा pt_regs *regs);
__visible व्योम smp_call_function_पूर्णांकerrupt(काष्ठा pt_regs *regs);
__visible व्योम smp_call_function_single_पूर्णांकerrupt(काष्ठा pt_regs *r);

#घोषणा cpu_physical_id(cpu)	per_cpu(x86_cpu_to_apicid, cpu)
#घोषणा cpu_acpi_id(cpu)	per_cpu(x86_cpu_to_acpiid, cpu)

/*
 * This function is needed by all SMP प्रणालीs. It must _always_ be valid
 * from the initial startup. We map APIC_BASE very early in page_setup(),
 * so this is correct in the x86 हाल.
 */
#घोषणा raw_smp_processor_id()  this_cpu_पढ़ो(cpu_number)
#घोषणा __smp_processor_id() __this_cpu_पढ़ो(cpu_number)

#अगर_घोषित CONFIG_X86_32
बाह्य पूर्णांक safe_smp_processor_id(व्योम);
#अन्यथा
# define safe_smp_processor_id()	smp_processor_id()
#पूर्ण_अगर

#अन्यथा /* !CONFIG_SMP */
#घोषणा wbinvd_on_cpu(cpu)     wbinvd()
अटल अंतरभूत पूर्णांक wbinvd_on_all_cpus(व्योम)
अणु
	wbinvd();
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */

बाह्य अचिन्हित disabled_cpus;

#अगर_घोषित CONFIG_X86_LOCAL_APIC
बाह्य पूर्णांक hard_smp_processor_id(व्योम);

#अन्यथा /* CONFIG_X86_LOCAL_APIC */
#घोषणा hard_smp_processor_id()	0
#पूर्ण_अगर /* CONFIG_X86_LOCAL_APIC */

#अगर_घोषित CONFIG_DEBUG_NMI_SELFTEST
बाह्य व्योम nmi_selftest(व्योम);
#अन्यथा
#घोषणा nmi_selftest() करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_X86_SMP_H */
