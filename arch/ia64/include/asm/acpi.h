<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (C) 1999 VA Linux Systems
 *  Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 *  Copyright (C) 2000,2001 J.I. Lee <jung-ik.lee@पूर्णांकel.com>
 *  Copyright (C) 2001,2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#अगर_अघोषित _ASM_ACPI_H
#घोषणा _ASM_ACPI_H

#अगर_घोषित __KERNEL__

#समावेश <acpi/pdc_पूर्णांकel.h>

#समावेश <linux/init.h>
#समावेश <linux/numa.h>
#समावेश <यंत्र/numa.h>


बाह्य पूर्णांक acpi_lapic;
#घोषणा acpi_disabled 0	/* ACPI always enabled on IA64 */
#घोषणा acpi_noirq 0	/* ACPI always enabled on IA64 */
#घोषणा acpi_pci_disabled 0 /* ACPI PCI always enabled on IA64 */
#घोषणा acpi_strict 1	/* no ACPI spec workarounds on IA64 */

अटल अंतरभूत bool acpi_has_cpu_in_madt(व्योम)
अणु
	वापस !!acpi_lapic;
पूर्ण

#घोषणा acpi_processor_cstate_check(x) (x) /* no idle limits on IA64 :) */
अटल अंतरभूत व्योम disable_acpi(व्योम) अणु पूर्ण

पूर्णांक acpi_request_vector (u32 पूर्णांक_type);
पूर्णांक acpi_gsi_to_irq (u32 gsi, अचिन्हित पूर्णांक *irq);

/* Low-level suspend routine. */
बाह्य पूर्णांक acpi_suspend_lowlevel(व्योम);

अटल अंतरभूत अचिन्हित दीर्घ acpi_get_wakeup_address(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * Record the cpei override flag and current logical cpu. This is
 * useful क्रम CPU removal.
 */
बाह्य अचिन्हित पूर्णांक can_cpei_retarget(व्योम);
बाह्य अचिन्हित पूर्णांक is_cpu_cpei_target(अचिन्हित पूर्णांक cpu);
बाह्य व्योम set_cpei_target_cpu(अचिन्हित पूर्णांक cpu);
बाह्य अचिन्हित पूर्णांक get_cpei_target_cpu(व्योम);
बाह्य व्योम prefill_possible_map(व्योम);
#अगर_घोषित CONFIG_ACPI_HOTPLUG_CPU
बाह्य पूर्णांक additional_cpus;
#अन्यथा
#घोषणा additional_cpus 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_NUMA
#अगर MAX_NUMNODES > 256
#घोषणा MAX_PXM_DOMAINS MAX_NUMNODES
#अन्यथा
#घोषणा MAX_PXM_DOMAINS (256)
#पूर्ण_अगर
बाह्य पूर्णांक pxm_to_nid_map[MAX_PXM_DOMAINS];
बाह्य पूर्णांक __initdata nid_to_pxm_map[MAX_NUMNODES];
#पूर्ण_अगर

अटल अंतरभूत bool arch_has_acpi_pdc(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत व्योम arch_acpi_set_pdc_bits(u32 *buf)
अणु
	buf[2] |= ACPI_PDC_EST_CAPABILITY_SMP;
पूर्ण

#अगर_घोषित CONFIG_ACPI_NUMA
बाह्य cpumask_t early_cpu_possible_map;
#घोषणा क्रम_each_possible_early_cpu(cpu)  \
	क्रम_each_cpu((cpu), &early_cpu_possible_map)

अटल अंतरभूत व्योम per_cpu_scan_finalize(पूर्णांक min_cpus, पूर्णांक reserve_cpus)
अणु
	पूर्णांक low_cpu, high_cpu;
	पूर्णांक cpu;
	पूर्णांक next_nid = 0;

	low_cpu = cpumask_weight(&early_cpu_possible_map);

	high_cpu = max(low_cpu, min_cpus);
	high_cpu = min(high_cpu + reserve_cpus, NR_CPUS);

	क्रम (cpu = low_cpu; cpu < high_cpu; cpu++) अणु
		cpumask_set_cpu(cpu, &early_cpu_possible_map);
		अगर (node_cpuid[cpu].nid == NUMA_NO_NODE) अणु
			node_cpuid[cpu].nid = next_nid;
			next_nid++;
			अगर (next_nid >= num_online_nodes())
				next_nid = 0;
		पूर्ण
	पूर्ण
पूर्ण

बाह्य व्योम acpi_numa_fixup(व्योम);

#पूर्ण_अगर /* CONFIG_ACPI_NUMA */

#पूर्ण_अगर /*__KERNEL__*/

#पूर्ण_अगर /*_ASM_ACPI_H*/
