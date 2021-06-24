<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_CPU_H
#घोषणा _ASM_X86_CPU_H

#समावेश <linux/device.h>
#समावेश <linux/cpu.h>
#समावेश <linux/topology.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/percpu.h>

#अगर_घोषित CONFIG_SMP

बाह्य व्योम prefill_possible_map(व्योम);

#अन्यथा /* CONFIG_SMP */

अटल अंतरभूत व्योम prefill_possible_map(व्योम) अणुपूर्ण

#घोषणा cpu_physical_id(cpu)			boot_cpu_physical_apicid
#घोषणा cpu_acpi_id(cpu)			0
#घोषणा safe_smp_processor_id()			0

#पूर्ण_अगर /* CONFIG_SMP */

काष्ठा x86_cpu अणु
	काष्ठा cpu cpu;
पूर्ण;

#अगर_घोषित CONFIG_HOTPLUG_CPU
बाह्य पूर्णांक arch_रेजिस्टर_cpu(पूर्णांक num);
बाह्य व्योम arch_unरेजिस्टर_cpu(पूर्णांक);
बाह्य व्योम start_cpu0(व्योम);
#अगर_घोषित CONFIG_DEBUG_HOTPLUG_CPU0
बाह्य पूर्णांक _debug_hotplug_cpu(पूर्णांक cpu, पूर्णांक action);
#पूर्ण_अगर
#पूर्ण_अगर

पूर्णांक mरुको_usable(स्थिर काष्ठा cpuinfo_x86 *);

अचिन्हित पूर्णांक x86_family(अचिन्हित पूर्णांक sig);
अचिन्हित पूर्णांक x86_model(अचिन्हित पूर्णांक sig);
अचिन्हित पूर्णांक x86_stepping(अचिन्हित पूर्णांक sig);
#अगर_घोषित CONFIG_CPU_SUP_INTEL
बाह्य व्योम __init sld_setup(काष्ठा cpuinfo_x86 *c);
बाह्य व्योम चयन_to_sld(अचिन्हित दीर्घ tअगरn);
बाह्य bool handle_user_split_lock(काष्ठा pt_regs *regs, दीर्घ error_code);
बाह्य bool handle_guest_split_lock(अचिन्हित दीर्घ ip);
बाह्य व्योम handle_bus_lock(काष्ठा pt_regs *regs);
u8 get_this_hybrid_cpu_type(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __init sld_setup(काष्ठा cpuinfo_x86 *c) अणुपूर्ण
अटल अंतरभूत व्योम चयन_to_sld(अचिन्हित दीर्घ tअगरn) अणुपूर्ण
अटल अंतरभूत bool handle_user_split_lock(काष्ठा pt_regs *regs, दीर्घ error_code)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool handle_guest_split_lock(अचिन्हित दीर्घ ip)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम handle_bus_lock(काष्ठा pt_regs *regs) अणुपूर्ण

अटल अंतरभूत u8 get_this_hybrid_cpu_type(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_IA32_FEAT_CTL
व्योम init_ia32_feat_ctl(काष्ठा cpuinfo_x86 *c);
#अन्यथा
अटल अंतरभूत व्योम init_ia32_feat_ctl(काष्ठा cpuinfo_x86 *c) अणुपूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _ASM_X86_CPU_H */
