<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HyperV  Detection code.
 *
 * Copyright (C) 2010, Novell, Inc.
 * Author : K. Y. Srinivasan <ksrinivasan@novell.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/समय.स>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/efi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kexec.h>
#समावेश <linux/i8253.h>
#समावेश <linux/अक्रमom.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/hyperv-tlfs.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/समयr.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/nmi.h>
#समावेश <घड़ीsource/hyperv_समयr.h>
#समावेश <यंत्र/numa.h>

/* Is Linux running as the root partition? */
bool hv_root_partition;
EXPORT_SYMBOL_GPL(hv_root_partition);

काष्ठा ms_hyperv_info ms_hyperv;
EXPORT_SYMBOL_GPL(ms_hyperv);

#अगर IS_ENABLED(CONFIG_HYPERV)
अटल व्योम (*vmbus_handler)(व्योम);
अटल व्योम (*hv_sसमयr0_handler)(व्योम);
अटल व्योम (*hv_kexec_handler)(व्योम);
अटल व्योम (*hv_crash_handler)(काष्ठा pt_regs *regs);

DEFINE_IDTENTRY_SYSVEC(sysvec_hyperv_callback)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	inc_irq_stat(irq_hv_callback_count);
	अगर (vmbus_handler)
		vmbus_handler();

	अगर (ms_hyperv.hपूर्णांकs & HV_DEPRECATING_AEOI_RECOMMENDED)
		ack_APIC_irq();

	set_irq_regs(old_regs);
पूर्ण

व्योम hv_setup_vmbus_handler(व्योम (*handler)(व्योम))
अणु
	vmbus_handler = handler;
पूर्ण
EXPORT_SYMBOL_GPL(hv_setup_vmbus_handler);

व्योम hv_हटाओ_vmbus_handler(व्योम)
अणु
	/* We have no way to deallocate the पूर्णांकerrupt gate */
	vmbus_handler = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(hv_हटाओ_vmbus_handler);

/*
 * Routines to करो per-architecture handling of sसमयr0
 * पूर्णांकerrupts when in Direct Mode
 */
DEFINE_IDTENTRY_SYSVEC(sysvec_hyperv_sसमयr0)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	inc_irq_stat(hyperv_sसमयr0_count);
	अगर (hv_sसमयr0_handler)
		hv_sसमयr0_handler();
	add_पूर्णांकerrupt_अक्रमomness(HYPERV_STIMER0_VECTOR, 0);
	ack_APIC_irq();

	set_irq_regs(old_regs);
पूर्ण

/* For x86/x64, override weak placeholders in hyperv_समयr.c */
व्योम hv_setup_sसमयr0_handler(व्योम (*handler)(व्योम))
अणु
	hv_sसमयr0_handler = handler;
पूर्ण

व्योम hv_हटाओ_sसमयr0_handler(व्योम)
अणु
	/* We have no way to deallocate the पूर्णांकerrupt gate */
	hv_sसमयr0_handler = शून्य;
पूर्ण

व्योम hv_setup_kexec_handler(व्योम (*handler)(व्योम))
अणु
	hv_kexec_handler = handler;
पूर्ण
EXPORT_SYMBOL_GPL(hv_setup_kexec_handler);

व्योम hv_हटाओ_kexec_handler(व्योम)
अणु
	hv_kexec_handler = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(hv_हटाओ_kexec_handler);

व्योम hv_setup_crash_handler(व्योम (*handler)(काष्ठा pt_regs *regs))
अणु
	hv_crash_handler = handler;
पूर्ण
EXPORT_SYMBOL_GPL(hv_setup_crash_handler);

व्योम hv_हटाओ_crash_handler(व्योम)
अणु
	hv_crash_handler = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(hv_हटाओ_crash_handler);

#अगर_घोषित CONFIG_KEXEC_CORE
अटल व्योम hv_machine_shutकरोwn(व्योम)
अणु
	अगर (kexec_in_progress && hv_kexec_handler)
		hv_kexec_handler();

	/*
	 * Call hv_cpu_die() on all the CPUs, otherwise later the hypervisor
	 * corrupts the old VP Assist Pages and can crash the kexec kernel.
	 */
	अगर (kexec_in_progress && hyperv_init_cpuhp > 0)
		cpuhp_हटाओ_state(hyperv_init_cpuhp);

	/* The function calls stop_other_cpus(). */
	native_machine_shutकरोwn();

	/* Disable the hypercall page when there is only 1 active CPU. */
	अगर (kexec_in_progress)
		hyperv_cleanup();
पूर्ण

अटल व्योम hv_machine_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	अगर (hv_crash_handler)
		hv_crash_handler(regs);

	/* The function calls crash_smp_send_stop(). */
	native_machine_crash_shutकरोwn(regs);

	/* Disable the hypercall page when there is only 1 active CPU. */
	hyperv_cleanup();
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */
#पूर्ण_अगर /* CONFIG_HYPERV */

अटल uपूर्णांक32_t  __init ms_hyperv_platक्रमm(व्योम)
अणु
	u32 eax;
	u32 hyp_signature[3];

	अगर (!boot_cpu_has(X86_FEATURE_HYPERVISOR))
		वापस 0;

	cpuid(HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS,
	      &eax, &hyp_signature[0], &hyp_signature[1], &hyp_signature[2]);

	अगर (eax >= HYPERV_CPUID_MIN &&
	    eax <= HYPERV_CPUID_MAX &&
	    !स_भेद("Microsoft Hv", hyp_signature, 12))
		वापस HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS;

	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर hv_get_nmi_reason(व्योम)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86_LOCAL_APIC
/*
 * Prior to WS2016 Debug-VM sends NMIs to all CPUs which makes
 * it dअगरficult to process CHANNELMSG_UNLOAD in हाल of crash. Handle
 * unknown NMI on the first CPU which माला_लो it.
 */
अटल पूर्णांक hv_nmi_unknown(अचिन्हित पूर्णांक val, काष्ठा pt_regs *regs)
अणु
	अटल atomic_t nmi_cpu = ATOMIC_INIT(-1);

	अगर (!unknown_nmi_panic)
		वापस NMI_DONE;

	अगर (atomic_cmpxchg(&nmi_cpu, -1, raw_smp_processor_id()) != -1)
		वापस NMI_HANDLED;

	वापस NMI_DONE;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित दीर्घ hv_get_tsc_khz(व्योम)
अणु
	अचिन्हित दीर्घ freq;

	rdmsrl(HV_X64_MSR_TSC_FREQUENCY, freq);

	वापस freq / 1000;
पूर्ण

#अगर defined(CONFIG_SMP) && IS_ENABLED(CONFIG_HYPERV)
अटल व्योम __init hv_smp_prepare_boot_cpu(व्योम)
अणु
	native_smp_prepare_boot_cpu();
#अगर defined(CONFIG_X86_64) && defined(CONFIG_PARAVIRT_SPINLOCKS)
	hv_init_spinlocks();
#पूर्ण_अगर
पूर्ण

अटल व्योम __init hv_smp_prepare_cpus(अचिन्हित पूर्णांक max_cpus)
अणु
#अगर_घोषित CONFIG_X86_64
	पूर्णांक i;
	पूर्णांक ret;
#पूर्ण_अगर

	native_smp_prepare_cpus(max_cpus);

#अगर_घोषित CONFIG_X86_64
	क्रम_each_present_cpu(i) अणु
		अगर (i == 0)
			जारी;
		ret = hv_call_add_logical_proc(numa_cpu_node(i), i, cpu_physical_id(i));
		BUG_ON(ret);
	पूर्ण

	क्रम_each_present_cpu(i) अणु
		अगर (i == 0)
			जारी;
		ret = hv_call_create_vp(numa_cpu_node(i), hv_current_partition_id, i, i);
		BUG_ON(ret);
	पूर्ण
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

अटल व्योम __init ms_hyperv_init_platक्रमm(व्योम)
अणु
	पूर्णांक hv_host_info_eax;
	पूर्णांक hv_host_info_ebx;
	पूर्णांक hv_host_info_ecx;
	पूर्णांक hv_host_info_edx;

#अगर_घोषित CONFIG_PARAVIRT
	pv_info.name = "Hyper-V";
#पूर्ण_अगर

	/*
	 * Extract the features and hपूर्णांकs
	 */
	ms_hyperv.features = cpuid_eax(HYPERV_CPUID_FEATURES);
	ms_hyperv.priv_high = cpuid_ebx(HYPERV_CPUID_FEATURES);
	ms_hyperv.misc_features = cpuid_edx(HYPERV_CPUID_FEATURES);
	ms_hyperv.hपूर्णांकs    = cpuid_eax(HYPERV_CPUID_ENLIGHTMENT_INFO);

	pr_info("Hyper-V: privilege flags low 0x%x, high 0x%x, hints 0x%x, misc 0x%x\n",
		ms_hyperv.features, ms_hyperv.priv_high, ms_hyperv.hपूर्णांकs,
		ms_hyperv.misc_features);

	ms_hyperv.max_vp_index = cpuid_eax(HYPERV_CPUID_IMPLEMENT_LIMITS);
	ms_hyperv.max_lp_index = cpuid_ebx(HYPERV_CPUID_IMPLEMENT_LIMITS);

	pr_debug("Hyper-V: max %u virtual processors, %u logical processors\n",
		 ms_hyperv.max_vp_index, ms_hyperv.max_lp_index);

	/*
	 * Check CPU management privilege.
	 *
	 * To mirror what Winकरोws करोes we should extract CPU management
	 * features and use the ReservedIdentityBit to detect अगर Linux is the
	 * root partition. But that requires negotiating CPU management
	 * पूर्णांकerface (a process to be finalized).
	 *
	 * For now, use the privilege flag as the indicator क्रम running as
	 * root.
	 */
	अगर (cpuid_ebx(HYPERV_CPUID_FEATURES) & HV_CPU_MANAGEMENT) अणु
		hv_root_partition = true;
		pr_info("Hyper-V: running as root partition\n");
	पूर्ण

	/*
	 * Extract host inक्रमmation.
	 */
	अगर (cpuid_eax(HYPERV_CPUID_VENDOR_AND_MAX_FUNCTIONS) >=
	    HYPERV_CPUID_VERSION) अणु
		hv_host_info_eax = cpuid_eax(HYPERV_CPUID_VERSION);
		hv_host_info_ebx = cpuid_ebx(HYPERV_CPUID_VERSION);
		hv_host_info_ecx = cpuid_ecx(HYPERV_CPUID_VERSION);
		hv_host_info_edx = cpuid_edx(HYPERV_CPUID_VERSION);

		pr_info("Hyper-V Host Build:%d-%d.%d-%d-%d.%d\n",
			hv_host_info_eax, hv_host_info_ebx >> 16,
			hv_host_info_ebx & 0xFFFF, hv_host_info_ecx,
			hv_host_info_edx >> 24, hv_host_info_edx & 0xFFFFFF);
	पूर्ण

	अगर (ms_hyperv.features & HV_ACCESS_FREQUENCY_MSRS &&
	    ms_hyperv.misc_features & HV_FEATURE_FREQUENCY_MSRS_AVAILABLE) अणु
		x86_platक्रमm.calibrate_tsc = hv_get_tsc_khz;
		x86_platक्रमm.calibrate_cpu = hv_get_tsc_khz;
	पूर्ण

	अगर (ms_hyperv.priv_high & HV_ISOLATION) अणु
		ms_hyperv.isolation_config_a = cpuid_eax(HYPERV_CPUID_ISOLATION_CONFIG);
		ms_hyperv.isolation_config_b = cpuid_ebx(HYPERV_CPUID_ISOLATION_CONFIG);

		pr_info("Hyper-V: Isolation Config: Group A 0x%x, Group B 0x%x\n",
			ms_hyperv.isolation_config_a, ms_hyperv.isolation_config_b);
	पूर्ण

	अगर (ms_hyperv.hपूर्णांकs & HV_X64_ENLIGHTENED_VMCS_RECOMMENDED) अणु
		ms_hyperv.nested_features =
			cpuid_eax(HYPERV_CPUID_NESTED_FEATURES);
	पूर्ण

	/*
	 * Hyper-V expects to get crash रेजिस्टर data or kmsg when
	 * crash enlighपंचांगent is available and प्रणाली crashes. Set
	 * crash_kexec_post_notअगरiers to be true to make sure that
	 * calling crash enlighपंचांगent पूर्णांकerface beक्रमe running kdump
	 * kernel.
	 */
	अगर (ms_hyperv.misc_features & HV_FEATURE_GUEST_CRASH_MSR_AVAILABLE)
		crash_kexec_post_notअगरiers = true;

#अगर_घोषित CONFIG_X86_LOCAL_APIC
	अगर (ms_hyperv.features & HV_ACCESS_FREQUENCY_MSRS &&
	    ms_hyperv.misc_features & HV_FEATURE_FREQUENCY_MSRS_AVAILABLE) अणु
		/*
		 * Get the APIC frequency.
		 */
		u64	hv_lapic_frequency;

		rdmsrl(HV_X64_MSR_APIC_FREQUENCY, hv_lapic_frequency);
		hv_lapic_frequency = भाग_u64(hv_lapic_frequency, HZ);
		lapic_समयr_period = hv_lapic_frequency;
		pr_info("Hyper-V: LAPIC Timer Frequency: %#x\n",
			lapic_समयr_period);
	पूर्ण

	रेजिस्टर_nmi_handler(NMI_UNKNOWN, hv_nmi_unknown, NMI_FLAG_FIRST,
			     "hv_nmi_unknown");
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86_IO_APIC
	no_समयr_check = 1;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_HYPERV) && defined(CONFIG_KEXEC_CORE)
	machine_ops.shutकरोwn = hv_machine_shutकरोwn;
	machine_ops.crash_shutकरोwn = hv_machine_crash_shutकरोwn;
#पूर्ण_अगर
	अगर (ms_hyperv.features & HV_ACCESS_TSC_INVARIANT) अणु
		wrmsrl(HV_X64_MSR_TSC_INVARIANT_CONTROL, 0x1);
		setup_क्रमce_cpu_cap(X86_FEATURE_TSC_RELIABLE);
	पूर्ण अन्यथा अणु
		mark_tsc_unstable("running on Hyper-V");
	पूर्ण

	/*
	 * Generation 2 instances करोn't support पढ़ोing the NMI status from
	 * 0x61 port.
	 */
	अगर (efi_enabled(EFI_BOOT))
		x86_platक्रमm.get_nmi_reason = hv_get_nmi_reason;

	/*
	 * Hyper-V VMs have a PIT emulation quirk such that zeroing the
	 * counter रेजिस्टर during PIT shutकरोwn restarts the PIT. So it
	 * जारीs to पूर्णांकerrupt @18.2 HZ. Setting i8253_clear_counter
	 * to false tells pit_shutकरोwn() not to zero the counter so that
	 * the PIT really is shutकरोwn. Generation 2 VMs करोn't have a PIT,
	 * and setting this value has no effect.
	 */
	i8253_clear_counter_on_shutकरोwn = false;

#अगर IS_ENABLED(CONFIG_HYPERV)
	/*
	 * Setup the hook to get control post apic initialization.
	 */
	x86_platक्रमm.apic_post_init = hyperv_init;
	hyperv_setup_mmu_ops();
	/* Setup the IDT क्रम hypervisor callback */
	alloc_पूर्णांकr_gate(HYPERVISOR_CALLBACK_VECTOR, यंत्र_sysvec_hyperv_callback);

	/* Setup the IDT क्रम reenlightenment notअगरications */
	अगर (ms_hyperv.features & HV_ACCESS_REENLIGHTENMENT) अणु
		alloc_पूर्णांकr_gate(HYPERV_REENLIGHTENMENT_VECTOR,
				यंत्र_sysvec_hyperv_reenlightenment);
	पूर्ण

	/* Setup the IDT क्रम sसमयr0 */
	अगर (ms_hyperv.misc_features & HV_STIMER_सूचीECT_MODE_AVAILABLE) अणु
		alloc_पूर्णांकr_gate(HYPERV_STIMER0_VECTOR,
				यंत्र_sysvec_hyperv_sसमयr0);
	पूर्ण

# अगरdef CONFIG_SMP
	smp_ops.smp_prepare_boot_cpu = hv_smp_prepare_boot_cpu;
	अगर (hv_root_partition)
		smp_ops.smp_prepare_cpus = hv_smp_prepare_cpus;
# endअगर

	/*
	 * Hyper-V करोesn't provide irq remapping क्रम IO-APIC. To enable x2apic,
	 * set x2apic destination mode to physical mode when x2apic is available
	 * and Hyper-V IOMMU driver makes sure cpus asचिन्हित with IO-APIC irqs
	 * have 8-bit APIC id.
	 */
# अगरdef CONFIG_X86_X2APIC
	अगर (x2apic_supported())
		x2apic_phys = 1;
# endअगर

	/* Register Hyper-V specअगरic घड़ीsource */
	hv_init_घड़ीsource();
#पूर्ण_अगर
पूर्ण

अटल bool __init ms_hyperv_x2apic_available(व्योम)
अणु
	वापस x2apic_supported();
पूर्ण

/*
 * If ms_hyperv_msi_ext_dest_id() वापसs true, hyperv_prepare_irq_remapping()
 * वापसs -ENODEV and the Hyper-V IOMMU driver is not used; instead, the
 * generic support of the 15-bit APIC ID is used: see __irq_msi_compose_msg().
 *
 * Note: क्रम a VM on Hyper-V, the I/O-APIC is the only device which
 * (logically) generates MSIs directly to the प्रणाली APIC irq करोमुख्य.
 * There is no HPET, and PCI MSI/MSI-X पूर्णांकerrupts are remapped by the
 * pci-hyperv host bridge.
 */
अटल bool __init ms_hyperv_msi_ext_dest_id(व्योम)
अणु
	u32 eax;

	eax = cpuid_eax(HYPERV_CPUID_VIRT_STACK_INTERFACE);
	अगर (eax != HYPERV_VS_INTERFACE_EAX_SIGNATURE)
		वापस false;

	eax = cpuid_eax(HYPERV_CPUID_VIRT_STACK_PROPERTIES);
	वापस eax & HYPERV_VS_PROPERTIES_EAX_EXTENDED_IOAPIC_RTE;
पूर्ण

स्थिर __initस्थिर काष्ठा hypervisor_x86 x86_hyper_ms_hyperv = अणु
	.name			= "Microsoft Hyper-V",
	.detect			= ms_hyperv_platक्रमm,
	.type			= X86_HYPER_MS_HYPERV,
	.init.x2apic_available	= ms_hyperv_x2apic_available,
	.init.msi_ext_dest_id	= ms_hyperv_msi_ext_dest_id,
	.init.init_platक्रमm	= ms_hyperv_init_platक्रमm,
पूर्ण;
