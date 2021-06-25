<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_X86_ACPI_H
#घोषणा _ASM_X86_ACPI_H

/*
 *  Copyright (C) 2001 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2001 Patrick Mochel <mochel@osdl.org>
 */
#समावेश <acpi/pdc_पूर्णांकel.h>

#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/x86_init.h>

#अगर_घोषित CONFIG_ACPI_APEI
# include <यंत्र/pgtable_types.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
बाह्य पूर्णांक acpi_lapic;
बाह्य पूर्णांक acpi_ioapic;
बाह्य पूर्णांक acpi_noirq;
बाह्य पूर्णांक acpi_strict;
बाह्य पूर्णांक acpi_disabled;
बाह्य पूर्णांक acpi_pci_disabled;
बाह्य पूर्णांक acpi_skip_समयr_override;
बाह्य पूर्णांक acpi_use_समयr_override;
बाह्य पूर्णांक acpi_fix_pin2_polarity;
बाह्य पूर्णांक acpi_disable_cmcff;

बाह्य u8 acpi_sci_flags;
बाह्य u32 acpi_sci_override_gsi;
व्योम acpi_pic_sci_set_trigger(अचिन्हित पूर्णांक, u16);

काष्ठा device;

बाह्य पूर्णांक (*__acpi_रेजिस्टर_gsi)(काष्ठा device *dev, u32 gsi,
				  पूर्णांक trigger, पूर्णांक polarity);
बाह्य व्योम (*__acpi_unरेजिस्टर_gsi)(u32 gsi);

अटल अंतरभूत व्योम disable_acpi(व्योम)
अणु
	acpi_disabled = 1;
	acpi_pci_disabled = 1;
	acpi_noirq = 1;
पूर्ण

बाह्य पूर्णांक acpi_gsi_to_irq(u32 gsi, अचिन्हित पूर्णांक *irq);

अटल अंतरभूत व्योम acpi_noirq_set(व्योम) अणु acpi_noirq = 1; पूर्ण
अटल अंतरभूत व्योम acpi_disable_pci(व्योम)
अणु
	acpi_pci_disabled = 1;
	acpi_noirq_set();
पूर्ण

/* Low-level suspend routine. */
बाह्य पूर्णांक (*acpi_suspend_lowlevel)(व्योम);

/* Physical address to resume after wakeup */
अचिन्हित दीर्घ acpi_get_wakeup_address(व्योम);

/*
 * Check अगर the CPU can handle C2 and deeper
 */
अटल अंतरभूत अचिन्हित पूर्णांक acpi_processor_cstate_check(अचिन्हित पूर्णांक max_cstate)
अणु
	/*
	 * Early models (<=5) of AMD Opterons are not supposed to go पूर्णांकo
	 * C2 state.
	 *
	 * Steppings 0x0A and later are good
	 */
	अगर (boot_cpu_data.x86 == 0x0F &&
	    boot_cpu_data.x86_venकरोr == X86_VENDOR_AMD &&
	    boot_cpu_data.x86_model <= 0x05 &&
	    boot_cpu_data.x86_stepping < 0x0A)
		वापस 1;
	अन्यथा अगर (boot_cpu_has(X86_BUG_AMD_APIC_C1E))
		वापस 1;
	अन्यथा
		वापस max_cstate;
पूर्ण

अटल अंतरभूत bool arch_has_acpi_pdc(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);
	वापस (c->x86_venकरोr == X86_VENDOR_INTEL ||
		c->x86_venकरोr == X86_VENDOR_CENTAUR);
पूर्ण

अटल अंतरभूत व्योम arch_acpi_set_pdc_bits(u32 *buf)
अणु
	काष्ठा cpuinfo_x86 *c = &cpu_data(0);

	buf[2] |= ACPI_PDC_C_CAPABILITY_SMP;

	अगर (cpu_has(c, X86_FEATURE_EST))
		buf[2] |= ACPI_PDC_EST_CAPABILITY_SWSMP;

	अगर (cpu_has(c, X86_FEATURE_ACPI))
		buf[2] |= ACPI_PDC_T_FFH;

	/*
	 * If mरुको/monitor is unsupported, C2/C3_FFH will be disabled
	 */
	अगर (!cpu_has(c, X86_FEATURE_MWAIT))
		buf[2] &= ~(ACPI_PDC_C_C2C3_FFH);
पूर्ण

अटल अंतरभूत bool acpi_has_cpu_in_madt(व्योम)
अणु
	वापस !!acpi_lapic;
पूर्ण

#घोषणा ACPI_HAVE_ARCH_SET_ROOT_POINTER
अटल अंतरभूत व्योम acpi_arch_set_root_poपूर्णांकer(u64 addr)
अणु
	x86_init.acpi.set_root_poपूर्णांकer(addr);
पूर्ण

#घोषणा ACPI_HAVE_ARCH_GET_ROOT_POINTER
अटल अंतरभूत u64 acpi_arch_get_root_poपूर्णांकer(व्योम)
अणु
	वापस x86_init.acpi.get_root_poपूर्णांकer();
पूर्ण

व्योम acpi_generic_reduced_hw_init(व्योम);

व्योम x86_शेष_set_root_poपूर्णांकer(u64 addr);
u64 x86_शेष_get_root_poपूर्णांकer(व्योम);

#अन्यथा /* !CONFIG_ACPI */

#घोषणा acpi_lapic 0
#घोषणा acpi_ioapic 0
#घोषणा acpi_disable_cmcff 0
अटल अंतरभूत व्योम acpi_noirq_set(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम acpi_disable_pci(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम disable_acpi(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम acpi_generic_reduced_hw_init(व्योम) अणु पूर्ण

अटल अंतरभूत व्योम x86_शेष_set_root_poपूर्णांकer(u64 addr) अणु पूर्ण

अटल अंतरभूत u64 x86_शेष_get_root_poपूर्णांकer(व्योम)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_ACPI */

#घोषणा ARCH_HAS_POWER_INIT	1

#अगर_घोषित CONFIG_ACPI_NUMA
बाह्य पूर्णांक x86_acpi_numa_init(व्योम);
#पूर्ण_अगर /* CONFIG_ACPI_NUMA */

काष्ठा cper_ia_proc_ctx;

#अगर_घोषित CONFIG_ACPI_APEI
अटल अंतरभूत pgprot_t arch_apei_get_mem_attribute(phys_addr_t addr)
अणु
	/*
	 * We currently have no way to look up the EFI memory map
	 * attributes क्रम a region in a consistent way, because the
	 * memmap is discarded after efi_मुक्त_boot_services(). So अगर
	 * you call efi_mem_attributes() during boot and at runसमय,
	 * you could theoretically see dअगरferent attributes.
	 *
	 * We are yet to see any x86 platक्रमms that require anything
	 * other than PAGE_KERNEL (some ARM64 platक्रमms require the
	 * equivalent of PAGE_KERNEL_NOCACHE). Additionally, अगर SME
	 * is active, the ACPI inक्रमmation will not be encrypted,
	 * so वापस PAGE_KERNEL_NOENC until we know dअगरferently.
	 */
	वापस PAGE_KERNEL_NOENC;
पूर्ण

पूर्णांक arch_apei_report_x86_error(काष्ठा cper_ia_proc_ctx *ctx_info,
			       u64 lapic_id);
#अन्यथा
अटल अंतरभूत पूर्णांक arch_apei_report_x86_error(काष्ठा cper_ia_proc_ctx *ctx_info,
					     u64 lapic_id)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#घोषणा ACPI_TABLE_UPGRADE_MAX_PHYS (max_low_pfn_mapped << PAGE_SHIFT)

#पूर्ण_अगर /* _ASM_X86_ACPI_H */
