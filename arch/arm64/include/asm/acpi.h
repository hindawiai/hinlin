<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2013-2014, Linaro Ltd.
 *	Author: Al Stone <al.stone@linaro.org>
 *	Author: Graeme Gregory <graeme.gregory@linaro.org>
 *	Author: Hanjun Guo <hanjun.guo@linaro.org>
 */

#अगर_अघोषित _ASM_ACPI_H
#घोषणा _ASM_ACPI_H

#समावेश <linux/efi.h>
#समावेश <linux/memblock.h>
#समावेश <linux/psci.h>
#समावेश <linux/मानकघोष.स>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/tlbflush.h>

/* Macros क्रम consistency checks of the GICC subtable of MADT */

/*
 * MADT GICC minimum length refers to the MADT GICC काष्ठाure table length as
 * defined in the earliest ACPI version supported on arm64, ie ACPI 5.1.
 *
 * The efficiency_class member was added to the
 * काष्ठा acpi_madt_generic_पूर्णांकerrupt to represent the MADT GICC काष्ठाure
 * "Processor Power Efficiency Class" field, added in ACPI 6.0 whose offset
 * is thereक्रमe used to delimit the MADT GICC काष्ठाure minimum length
 * appropriately.
 */
#घोषणा ACPI_MADT_GICC_MIN_LENGTH   दुरत्व(  \
	काष्ठा acpi_madt_generic_पूर्णांकerrupt, efficiency_class)

#घोषणा BAD_MADT_GICC_ENTRY(entry, end)					\
	(!(entry) || (entry)->header.length < ACPI_MADT_GICC_MIN_LENGTH || \
	(अचिन्हित दीर्घ)(entry) + (entry)->header.length > (end))

#घोषणा ACPI_MADT_GICC_SPE  (दुरत्व(काष्ठा acpi_madt_generic_पूर्णांकerrupt, \
	spe_पूर्णांकerrupt) + माप(u16))

/* Basic configuration क्रम ACPI */
#अगर_घोषित	CONFIG_ACPI
pgprot_t __acpi_get_mem_attribute(phys_addr_t addr);

/* ACPI table mapping after acpi_permanent_mmap is set */
व्योम __iomem *acpi_os_ioremap(acpi_physical_address phys, acpi_size size);
#घोषणा acpi_os_ioremap acpi_os_ioremap

प्रकार u64 phys_cpuid_t;
#घोषणा PHYS_CPUID_INVALID INVALID_HWID

#घोषणा acpi_strict 1	/* No out-of-spec workarounds on ARM64 */
बाह्य पूर्णांक acpi_disabled;
बाह्य पूर्णांक acpi_noirq;
बाह्य पूर्णांक acpi_pci_disabled;

अटल अंतरभूत व्योम disable_acpi(व्योम)
अणु
	acpi_disabled = 1;
	acpi_pci_disabled = 1;
	acpi_noirq = 1;
पूर्ण

अटल अंतरभूत व्योम enable_acpi(व्योम)
अणु
	acpi_disabled = 0;
	acpi_pci_disabled = 0;
	acpi_noirq = 0;
पूर्ण

/*
 * The ACPI processor driver क्रम ACPI core code needs this macro
 * to find out this cpu was alपढ़ोy mapped (mapping from CPU hardware
 * ID to CPU logical ID) or not.
 */
#घोषणा cpu_physical_id(cpu) cpu_logical_map(cpu)

/*
 * It's used from ACPI core in kdump to boot UP प्रणाली with SMP kernel,
 * with this check the ACPI core will not override the CPU index
 * obtained from GICC with 0 and not prपूर्णांक some error message as well.
 * Since MADT must provide at least one GICC काष्ठाure क्रम GIC
 * initialization, CPU will be always available in MADT on ARM64.
 */
अटल अंतरभूत bool acpi_has_cpu_in_madt(व्योम)
अणु
	वापस true;
पूर्ण

काष्ठा acpi_madt_generic_पूर्णांकerrupt *acpi_cpu_get_madt_gicc(पूर्णांक cpu);
अटल अंतरभूत u32 get_acpi_id_क्रम_cpu(अचिन्हित पूर्णांक cpu)
अणु
	वापस	acpi_cpu_get_madt_gicc(cpu)->uid;
पूर्ण

अटल अंतरभूत व्योम arch_fix_phys_package_id(पूर्णांक num, u32 slot) अणु पूर्ण
व्योम __init acpi_init_cpus(व्योम);
पूर्णांक apei_claim_sea(काष्ठा pt_regs *regs);
#अन्यथा
अटल अंतरभूत व्योम acpi_init_cpus(व्योम) अणु पूर्ण
अटल अंतरभूत पूर्णांक apei_claim_sea(काष्ठा pt_regs *regs) अणु वापस -ENOENT; पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

#अगर_घोषित CONFIG_ARM64_ACPI_PARKING_PROTOCOL
bool acpi_parking_protocol_valid(पूर्णांक cpu);
व्योम __init
acpi_set_mailbox_entry(पूर्णांक cpu, काष्ठा acpi_madt_generic_पूर्णांकerrupt *processor);
#अन्यथा
अटल अंतरभूत bool acpi_parking_protocol_valid(पूर्णांक cpu) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम
acpi_set_mailbox_entry(पूर्णांक cpu, काष्ठा acpi_madt_generic_पूर्णांकerrupt *processor)
अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत स्थिर अक्षर *acpi_get_enable_method(पूर्णांक cpu)
अणु
	अगर (acpi_psci_present())
		वापस "psci";

	अगर (acpi_parking_protocol_valid(cpu))
		वापस "parking-protocol";

	वापस शून्य;
पूर्ण

#अगर_घोषित	CONFIG_ACPI_APEI
/*
 * acpi_disable_cmcff is used in drivers/acpi/apei/hest.c क्रम disabling
 * IA-32 Architecture Corrected Machine Check (CMC) Firmware-First mode
 * with a kernel command line parameter "acpi=nocmcoff". But we करोn't
 * have this IA-32 specअगरic feature on ARM64, this definition is only
 * क्रम compatibility.
 */
#घोषणा acpi_disable_cmcff 1
अटल अंतरभूत pgprot_t arch_apei_get_mem_attribute(phys_addr_t addr)
अणु
	वापस __acpi_get_mem_attribute(addr);
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_APEI */

#अगर_घोषित CONFIG_ACPI_NUMA
पूर्णांक arm64_acpi_numa_init(व्योम);
पूर्णांक acpi_numa_get_nid(अचिन्हित पूर्णांक cpu);
व्योम acpi_map_cpus_to_nodes(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक arm64_acpi_numa_init(व्योम) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत पूर्णांक acpi_numa_get_nid(अचिन्हित पूर्णांक cpu) अणु वापस NUMA_NO_NODE; पूर्ण
अटल अंतरभूत व्योम acpi_map_cpus_to_nodes(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_NUMA */

#घोषणा ACPI_TABLE_UPGRADE_MAX_PHYS MEMBLOCK_ALLOC_ACCESSIBLE

#पूर्ण_अगर /*_ASM_ACPI_H*/
