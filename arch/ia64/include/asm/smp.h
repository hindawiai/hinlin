<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * SMP Support
 *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * (c) Copyright 2001-2003, 2005 Hewlett-Packard Development Company, L.P.
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */
#अगर_अघोषित _ASM_IA64_SMP_H
#घोषणा _ASM_IA64_SMP_H

#समावेश <linux/init.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irqवापस.h>

#समावेश <यंत्र/param.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/ptrace.h>

अटल अंतरभूत अचिन्हित पूर्णांक
ia64_get_lid (व्योम)
अणु
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ reserved : 16;
			अचिन्हित दीर्घ eid : 8;
			अचिन्हित दीर्घ id : 8;
			अचिन्हित दीर्घ ignored : 32;
		पूर्ण f;
		अचिन्हित दीर्घ bits;
	पूर्ण lid;

	lid.bits = ia64_getreg(_IA64_REG_CR_LID);
	वापस lid.f.id << 8 | lid.f.eid;
पूर्ण

#घोषणा hard_smp_processor_id()		ia64_get_lid()

#अगर_घोषित CONFIG_SMP

#घोषणा raw_smp_processor_id() (current_thपढ़ो_info()->cpu)

बाह्य काष्ठा smp_boot_data अणु
	पूर्णांक cpu_count;
	पूर्णांक cpu_phys_id[NR_CPUS];
पूर्ण smp_boot_data __initdata;

बाह्य अक्षर no_पूर्णांक_routing;

बाह्य cpumask_t cpu_core_map[NR_CPUS];
DECLARE_PER_CPU_SHARED_ALIGNED(cpumask_t, cpu_sibling_map);
बाह्य पूर्णांक smp_num_siblings;
बाह्य व्योम __iomem *ipi_base_addr;

बाह्य अस्थिर पूर्णांक ia64_cpu_to_sapicid[];
#घोषणा cpu_physical_id(i)	ia64_cpu_to_sapicid[i]

बाह्य अचिन्हित दीर्घ ap_wakeup_vector;

/*
 * Function to map hard smp processor id to logical id.  Slow, so करोn't use this in
 * perक्रमmance-critical code.
 */
अटल अंतरभूत पूर्णांक
cpu_logical_id (पूर्णांक cpuid)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_CPUS; ++i)
		अगर (cpu_physical_id(i) == cpuid)
			अवरोध;
	वापस i;
पूर्ण

/* Upping and करोwning of CPUs */
बाह्य पूर्णांक __cpu_disable (व्योम);
बाह्य व्योम __cpu_die (अचिन्हित पूर्णांक cpu);
बाह्य व्योम cpu_die (व्योम) __attribute__ ((noवापस));
बाह्य व्योम __init smp_build_cpu_map(व्योम);

बाह्य व्योम __init init_smp_config (व्योम);
बाह्य व्योम smp_करो_समयr (काष्ठा pt_regs *regs);

बाह्य irqवापस_t handle_IPI(पूर्णांक irq, व्योम *dev_id);
बाह्य व्योम smp_send_reschedule (पूर्णांक cpu);
बाह्य व्योम identअगरy_siblings (काष्ठा cpuinfo_ia64 *);
बाह्य पूर्णांक is_multithपढ़ोing_enabled(व्योम);

बाह्य व्योम arch_send_call_function_single_ipi(पूर्णांक cpu);
बाह्य व्योम arch_send_call_function_ipi_mask(स्थिर काष्ठा cpumask *mask);

#अन्यथा /* CONFIG_SMP */

#घोषणा cpu_logical_id(i)		0
#घोषणा cpu_physical_id(i)		ia64_get_lid()

#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर /* _ASM_IA64_SMP_H */
