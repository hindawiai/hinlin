<शैली गुरु>
/*
 * Copyright (C) 2009 Thomas Gleixner <tglx@linutronix.de>
 *
 *  For licencing details see kernel-base/COPYING
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/bios_ebda.h>
#समावेश <यंत्र/paravirt.h>
#समावेश <यंत्र/pci_x86.h>
#समावेश <यंत्र/mpspec.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/hpet.h>
#समावेश <यंत्र/memtype.h>
#समावेश <यंत्र/tsc.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/mach_traps.h>
#समावेश <यंत्र/irqकरोमुख्य.h>

व्योम x86_init_noop(व्योम) अणु पूर्ण
व्योम __init x86_init_uपूर्णांक_noop(अचिन्हित पूर्णांक unused) अणु पूर्ण
अटल पूर्णांक __init iommu_init_noop(व्योम) अणु वापस 0; पूर्ण
अटल व्योम iommu_shutकरोwn_noop(व्योम) अणु पूर्ण
bool __init bool_x86_init_noop(व्योम) अणु वापस false; पूर्ण
व्योम x86_op_पूर्णांक_noop(पूर्णांक cpu) अणु पूर्ण
अटल __init पूर्णांक set_rtc_noop(स्थिर काष्ठा बारpec64 *now) अणु वापस -EINVAL; पूर्ण
अटल __init व्योम get_rtc_noop(काष्ठा बारpec64 *now) अणु पूर्ण

अटल __initस्थिर स्थिर काष्ठा of_device_id of_cmos_match[] = अणु
	अणु .compatible = "motorola,mc146818" पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Allow devicetree configured प्रणालीs to disable the RTC by setting the
 * corresponding DT node's status property to disabled. Code is optimized
 * out क्रम CONFIG_OF=n builds.
 */
अटल __init व्योम x86_wallघड़ी_init(व्योम)
अणु
	काष्ठा device_node *node = of_find_matching_node(शून्य, of_cmos_match);

	अगर (node && !of_device_is_available(node)) अणु
		x86_platक्रमm.get_wallघड़ी = get_rtc_noop;
		x86_platक्रमm.set_wallघड़ी = set_rtc_noop;
	पूर्ण
पूर्ण

/*
 * The platक्रमm setup functions are preset with the शेष functions
 * क्रम standard PC hardware.
 */
काष्ठा x86_init_ops x86_init __initdata = अणु

	.resources = अणु
		.probe_roms		= probe_roms,
		.reserve_resources	= reserve_standard_io_resources,
		.memory_setup		= e820__memory_setup_शेष,
	पूर्ण,

	.mpparse = अणु
		.setup_ioapic_ids	= x86_init_noop,
		.find_smp_config	= शेष_find_smp_config,
		.get_smp_config		= शेष_get_smp_config,
	पूर्ण,

	.irqs = अणु
		.pre_vector_init	= init_ISA_irqs,
		.पूर्णांकr_init		= native_init_IRQ,
		.पूर्णांकr_mode_select	= apic_पूर्णांकr_mode_select,
		.पूर्णांकr_mode_init		= apic_पूर्णांकr_mode_init,
		.create_pci_msi_करोमुख्य	= native_create_pci_msi_करोमुख्य,
	पूर्ण,

	.oem = अणु
		.arch_setup		= x86_init_noop,
		.banner			= शेष_banner,
	पूर्ण,

	.paging = अणु
		.pagetable_init		= native_pagetable_init,
	पूर्ण,

	.समयrs = अणु
		.setup_percpu_घड़ीev	= setup_boot_APIC_घड़ी,
		.समयr_init		= hpet_समय_init,
		.wallघड़ी_init		= x86_wallघड़ी_init,
	पूर्ण,

	.iommu = अणु
		.iommu_init		= iommu_init_noop,
	पूर्ण,

	.pci = अणु
		.init			= x86_शेष_pci_init,
		.init_irq		= x86_शेष_pci_init_irq,
		.fixup_irqs		= x86_शेष_pci_fixup_irqs,
	पूर्ण,

	.hyper = अणु
		.init_platक्रमm		= x86_init_noop,
		.guest_late_init	= x86_init_noop,
		.x2apic_available	= bool_x86_init_noop,
		.msi_ext_dest_id	= bool_x86_init_noop,
		.init_mem_mapping	= x86_init_noop,
		.init_after_booपंचांगem	= x86_init_noop,
	पूर्ण,

	.acpi = अणु
		.set_root_poपूर्णांकer	= x86_शेष_set_root_poपूर्णांकer,
		.get_root_poपूर्णांकer	= x86_शेष_get_root_poपूर्णांकer,
		.reduced_hw_early_init	= acpi_generic_reduced_hw_init,
	पूर्ण,
पूर्ण;

काष्ठा x86_cpuinit_ops x86_cpuinit = अणु
	.early_percpu_घड़ी_init	= x86_init_noop,
	.setup_percpu_घड़ीev		= setup_secondary_APIC_घड़ी,
पूर्ण;

अटल व्योम शेष_nmi_init(व्योम) अणु पूर्ण;

काष्ठा x86_platक्रमm_ops x86_platक्रमm __ro_after_init = अणु
	.calibrate_cpu			= native_calibrate_cpu_early,
	.calibrate_tsc			= native_calibrate_tsc,
	.get_wallघड़ी			= mach_get_cmos_समय,
	.set_wallघड़ी			= mach_set_rtc_mmss,
	.iommu_shutकरोwn			= iommu_shutकरोwn_noop,
	.is_untracked_pat_range		= is_ISA_range,
	.nmi_init			= शेष_nmi_init,
	.get_nmi_reason			= शेष_get_nmi_reason,
	.save_sched_घड़ी_state 	= tsc_save_sched_घड़ी_state,
	.restore_sched_घड़ी_state 	= tsc_restore_sched_घड़ी_state,
	.hyper.pin_vcpu			= x86_op_पूर्णांक_noop,
पूर्ण;

EXPORT_SYMBOL_GPL(x86_platक्रमm);

#अगर defined(CONFIG_PCI_MSI)
काष्ठा x86_msi_ops x86_msi __ro_after_init = अणु
	.restore_msi_irqs	= शेष_restore_msi_irqs,
पूर्ण;

/* MSI arch specअगरic hooks */
व्योम arch_restore_msi_irqs(काष्ठा pci_dev *dev)
अणु
	x86_msi.restore_msi_irqs(dev);
पूर्ण
#पूर्ण_अगर

काष्ठा x86_apic_ops x86_apic_ops __ro_after_init = अणु
	.io_apic_पढ़ो	= native_io_apic_पढ़ो,
	.restore	= native_restore_boot_irq_mode,
पूर्ण;
