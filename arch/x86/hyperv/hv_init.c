<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * X86 specअगरic Hyper-V initialization code.
 *
 * Copyright (C) 2016, Microsoft, Inc.
 *
 * Author : K. Y. Srinivasan <kys@microsoft.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/efi.h>
#समावेश <linux/types.h>
#समावेश <linux/bitfield.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/hyperv-tlfs.h>
#समावेश <यंत्र/mshyperv.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <linux/kexec.h>
#समावेश <linux/version.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/hyperv.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/syscore_ops.h>
#समावेश <घड़ीsource/hyperv_समयr.h>
#समावेश <linux/highस्मृति.स>

पूर्णांक hyperv_init_cpuhp;
u64 hv_current_partition_id = ~0ull;
EXPORT_SYMBOL_GPL(hv_current_partition_id);

व्योम *hv_hypercall_pg;
EXPORT_SYMBOL_GPL(hv_hypercall_pg);

/* Storage to save the hypercall page temporarily क्रम hibernation */
अटल व्योम *hv_hypercall_pg_saved;

u32 *hv_vp_index;
EXPORT_SYMBOL_GPL(hv_vp_index);

काष्ठा hv_vp_assist_page **hv_vp_assist_page;
EXPORT_SYMBOL_GPL(hv_vp_assist_page);

व्योम  __percpu **hyperv_pcpu_input_arg;
EXPORT_SYMBOL_GPL(hyperv_pcpu_input_arg);

व्योम  __percpu **hyperv_pcpu_output_arg;
EXPORT_SYMBOL_GPL(hyperv_pcpu_output_arg);

u32 hv_max_vp_index;
EXPORT_SYMBOL_GPL(hv_max_vp_index);

अटल पूर्णांक hv_cpu_init(अचिन्हित पूर्णांक cpu)
अणु
	u64 msr_vp_index;
	काष्ठा hv_vp_assist_page **hvp = &hv_vp_assist_page[smp_processor_id()];
	व्योम **input_arg;
	काष्ठा page *pg;

	/* hv_cpu_init() can be called with IRQs disabled from hv_resume() */
	pg = alloc_pages(irqs_disabled() ? GFP_ATOMIC : GFP_KERNEL, hv_root_partition ? 1 : 0);
	अगर (unlikely(!pg))
		वापस -ENOMEM;

	input_arg = (व्योम **)this_cpu_ptr(hyperv_pcpu_input_arg);
	*input_arg = page_address(pg);
	अगर (hv_root_partition) अणु
		व्योम **output_arg;

		output_arg = (व्योम **)this_cpu_ptr(hyperv_pcpu_output_arg);
		*output_arg = page_address(pg + 1);
	पूर्ण

	msr_vp_index = hv_get_रेजिस्टर(HV_REGISTER_VP_INDEX);

	hv_vp_index[smp_processor_id()] = msr_vp_index;

	अगर (msr_vp_index > hv_max_vp_index)
		hv_max_vp_index = msr_vp_index;

	अगर (!hv_vp_assist_page)
		वापस 0;

	/*
	 * The VP ASSIST PAGE is an "overlay" page (see Hyper-V TLFS's Section
	 * 5.2.1 "GPA Overlay Pages"). Here it must be zeroed out to make sure
	 * we always ग_लिखो the EOI MSR in hv_apic_eoi_ग_लिखो() *after* the
	 * EOI optimization is disabled in hv_cpu_die(), otherwise a CPU may
	 * not be stopped in the हाल of CPU offlining and the VM will hang.
	 */
	अगर (!*hvp) अणु
		*hvp = __vदो_स्मृति(PAGE_SIZE, GFP_KERNEL | __GFP_ZERO);
	पूर्ण

	अगर (*hvp) अणु
		u64 val;

		val = vदो_स्मृति_to_pfn(*hvp);
		val = (val << HV_X64_MSR_VP_ASSIST_PAGE_ADDRESS_SHIFT) |
			HV_X64_MSR_VP_ASSIST_PAGE_ENABLE;

		wrmsrl(HV_X64_MSR_VP_ASSIST_PAGE, val);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम (*hv_reenlightenment_cb)(व्योम);

अटल व्योम hv_reenlightenment_notअगरy(काष्ठा work_काष्ठा *dummy)
अणु
	काष्ठा hv_tsc_emulation_status emu_status;

	rdmsrl(HV_X64_MSR_TSC_EMULATION_STATUS, *(u64 *)&emu_status);

	/* Don't issue the callback अगर TSC accesses are not emulated */
	अगर (hv_reenlightenment_cb && emu_status.inprogress)
		hv_reenlightenment_cb();
पूर्ण
अटल DECLARE_DELAYED_WORK(hv_reenlightenment_work, hv_reenlightenment_notअगरy);

व्योम hyperv_stop_tsc_emulation(व्योम)
अणु
	u64 freq;
	काष्ठा hv_tsc_emulation_status emu_status;

	rdmsrl(HV_X64_MSR_TSC_EMULATION_STATUS, *(u64 *)&emu_status);
	emu_status.inprogress = 0;
	wrmsrl(HV_X64_MSR_TSC_EMULATION_STATUS, *(u64 *)&emu_status);

	rdmsrl(HV_X64_MSR_TSC_FREQUENCY, freq);
	tsc_khz = भाग64_u64(freq, 1000);
पूर्ण
EXPORT_SYMBOL_GPL(hyperv_stop_tsc_emulation);

अटल अंतरभूत bool hv_reenlightenment_available(व्योम)
अणु
	/*
	 * Check क्रम required features and privileges to make TSC frequency
	 * change notअगरications work.
	 */
	वापस ms_hyperv.features & HV_ACCESS_FREQUENCY_MSRS &&
		ms_hyperv.misc_features & HV_FEATURE_FREQUENCY_MSRS_AVAILABLE &&
		ms_hyperv.features & HV_ACCESS_REENLIGHTENMENT;
पूर्ण

DEFINE_IDTENTRY_SYSVEC(sysvec_hyperv_reenlightenment)
अणु
	ack_APIC_irq();
	inc_irq_stat(irq_hv_reenlightenment_count);
	schedule_delayed_work(&hv_reenlightenment_work, HZ/10);
पूर्ण

व्योम set_hv_tscchange_cb(व्योम (*cb)(व्योम))
अणु
	काष्ठा hv_reenlightenment_control re_ctrl = अणु
		.vector = HYPERV_REENLIGHTENMENT_VECTOR,
		.enabled = 1,
		.target_vp = hv_vp_index[smp_processor_id()]
	पूर्ण;
	काष्ठा hv_tsc_emulation_control emu_ctrl = अणु.enabled = 1पूर्ण;

	अगर (!hv_reenlightenment_available()) अणु
		pr_warn("Hyper-V: reenlightenment support is unavailable\n");
		वापस;
	पूर्ण

	hv_reenlightenment_cb = cb;

	/* Make sure callback is रेजिस्टरed beक्रमe we ग_लिखो to MSRs */
	wmb();

	wrmsrl(HV_X64_MSR_REENLIGHTENMENT_CONTROL, *((u64 *)&re_ctrl));
	wrmsrl(HV_X64_MSR_TSC_EMULATION_CONTROL, *((u64 *)&emu_ctrl));
पूर्ण
EXPORT_SYMBOL_GPL(set_hv_tscchange_cb);

व्योम clear_hv_tscchange_cb(व्योम)
अणु
	काष्ठा hv_reenlightenment_control re_ctrl;

	अगर (!hv_reenlightenment_available())
		वापस;

	rdmsrl(HV_X64_MSR_REENLIGHTENMENT_CONTROL, *(u64 *)&re_ctrl);
	re_ctrl.enabled = 0;
	wrmsrl(HV_X64_MSR_REENLIGHTENMENT_CONTROL, *(u64 *)&re_ctrl);

	hv_reenlightenment_cb = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(clear_hv_tscchange_cb);

अटल पूर्णांक hv_cpu_die(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा hv_reenlightenment_control re_ctrl;
	अचिन्हित पूर्णांक new_cpu;
	अचिन्हित दीर्घ flags;
	व्योम **input_arg;
	व्योम *pg;

	local_irq_save(flags);
	input_arg = (व्योम **)this_cpu_ptr(hyperv_pcpu_input_arg);
	pg = *input_arg;
	*input_arg = शून्य;

	अगर (hv_root_partition) अणु
		व्योम **output_arg;

		output_arg = (व्योम **)this_cpu_ptr(hyperv_pcpu_output_arg);
		*output_arg = शून्य;
	पूर्ण

	local_irq_restore(flags);

	मुक्त_pages((अचिन्हित दीर्घ)pg, hv_root_partition ? 1 : 0);

	अगर (hv_vp_assist_page && hv_vp_assist_page[cpu])
		wrmsrl(HV_X64_MSR_VP_ASSIST_PAGE, 0);

	अगर (hv_reenlightenment_cb == शून्य)
		वापस 0;

	rdmsrl(HV_X64_MSR_REENLIGHTENMENT_CONTROL, *((u64 *)&re_ctrl));
	अगर (re_ctrl.target_vp == hv_vp_index[cpu]) अणु
		/*
		 * Reassign reenlightenment notअगरications to some other online
		 * CPU or just disable the feature अगर there are no online CPUs
		 * left (happens on hibernation).
		 */
		new_cpu = cpumask_any_but(cpu_online_mask, cpu);

		अगर (new_cpu < nr_cpu_ids)
			re_ctrl.target_vp = hv_vp_index[new_cpu];
		अन्यथा
			re_ctrl.enabled = 0;

		wrmsrl(HV_X64_MSR_REENLIGHTENMENT_CONTROL, *((u64 *)&re_ctrl));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init hv_pci_init(व्योम)
अणु
	पूर्णांक gen2vm = efi_enabled(EFI_BOOT);

	/*
	 * For Generation-2 VM, we निकास from pci_arch_init() by वापसing 0.
	 * The purpose is to suppress the harmless warning:
	 * "PCI: Fatal: No config space access function found"
	 */
	अगर (gen2vm)
		वापस 0;

	/* For Generation-1 VM, we'll proceed in pci_arch_init().  */
	वापस 1;
पूर्ण

अटल पूर्णांक hv_suspend(व्योम)
अणु
	जोड़ hv_x64_msr_hypercall_contents hypercall_msr;
	पूर्णांक ret;

	अगर (hv_root_partition)
		वापस -EPERM;

	/*
	 * Reset the hypercall page as it is going to be invalidated
	 * across hibernation. Setting hv_hypercall_pg to शून्य ensures
	 * that any subsequent hypercall operation fails safely instead of
	 * crashing due to an access of an invalid page. The hypercall page
	 * poपूर्णांकer is restored on resume.
	 */
	hv_hypercall_pg_saved = hv_hypercall_pg;
	hv_hypercall_pg = शून्य;

	/* Disable the hypercall page in the hypervisor */
	rdmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uपूर्णांक64);
	hypercall_msr.enable = 0;
	wrmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uपूर्णांक64);

	ret = hv_cpu_die(0);
	वापस ret;
पूर्ण

अटल व्योम hv_resume(व्योम)
अणु
	जोड़ hv_x64_msr_hypercall_contents hypercall_msr;
	पूर्णांक ret;

	ret = hv_cpu_init(0);
	WARN_ON(ret);

	/* Re-enable the hypercall page */
	rdmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uपूर्णांक64);
	hypercall_msr.enable = 1;
	hypercall_msr.guest_physical_address =
		vदो_स्मृति_to_pfn(hv_hypercall_pg_saved);
	wrmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uपूर्णांक64);

	hv_hypercall_pg = hv_hypercall_pg_saved;
	hv_hypercall_pg_saved = शून्य;

	/*
	 * Reenlightenment notअगरications are disabled by hv_cpu_die(0),
	 * reenable them here अगर hv_reenlightenment_cb was previously set.
	 */
	अगर (hv_reenlightenment_cb)
		set_hv_tscchange_cb(hv_reenlightenment_cb);
पूर्ण

/* Note: when the ops are called, only CPU0 is online and IRQs are disabled. */
अटल काष्ठा syscore_ops hv_syscore_ops = अणु
	.suspend	= hv_suspend,
	.resume		= hv_resume,
पूर्ण;

अटल व्योम (* __initdata old_setup_percpu_घड़ीev)(व्योम);

अटल व्योम __init hv_sसमयr_setup_percpu_घड़ीev(व्योम)
अणु
	/*
	 * Ignore any errors in setting up sसमयr घड़ीevents
	 * as we can run with the LAPIC समयr as a fallback.
	 */
	(व्योम)hv_sसमयr_alloc(false);

	/*
	 * Still रेजिस्टर the LAPIC समयr, because the direct-mode STIMER is
	 * not supported by old versions of Hyper-V. This also allows users
	 * to चयन to LAPIC समयr via /sys, अगर they want to.
	 */
	अगर (old_setup_percpu_घड़ीev)
		old_setup_percpu_घड़ीev();
पूर्ण

अटल व्योम __init hv_get_partition_id(व्योम)
अणु
	काष्ठा hv_get_partition_id *output_page;
	u64 status;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	output_page = *this_cpu_ptr(hyperv_pcpu_output_arg);
	status = hv_करो_hypercall(HVCALL_GET_PARTITION_ID, शून्य, output_page);
	अगर (!hv_result_success(status)) अणु
		/* No poपूर्णांक in proceeding अगर this failed */
		pr_err("Failed to get partition ID: %lld\n", status);
		BUG();
	पूर्ण
	hv_current_partition_id = output_page->partition_id;
	local_irq_restore(flags);
पूर्ण

/*
 * This function is to be invoked early in the boot sequence after the
 * hypervisor has been detected.
 *
 * 1. Setup the hypercall page.
 * 2. Register Hyper-V specअगरic घड़ीsource.
 * 3. Setup Hyper-V specअगरic APIC entry poपूर्णांकs.
 */
व्योम __init hyperv_init(व्योम)
अणु
	u64 guest_id, required_msrs;
	जोड़ hv_x64_msr_hypercall_contents hypercall_msr;
	पूर्णांक cpuhp, i;

	अगर (x86_hyper_type != X86_HYPER_MS_HYPERV)
		वापस;

	/* Absolutely required MSRs */
	required_msrs = HV_MSR_HYPERCALL_AVAILABLE |
		HV_MSR_VP_INDEX_AVAILABLE;

	अगर ((ms_hyperv.features & required_msrs) != required_msrs)
		वापस;

	/*
	 * Allocate the per-CPU state क्रम the hypercall input arg.
	 * If this allocation fails, we will not be able to setup
	 * (per-CPU) hypercall input page and thus this failure is
	 * fatal on Hyper-V.
	 */
	hyperv_pcpu_input_arg = alloc_percpu(व्योम  *);

	BUG_ON(hyperv_pcpu_input_arg == शून्य);

	/* Allocate the per-CPU state क्रम output arg क्रम root */
	अगर (hv_root_partition) अणु
		hyperv_pcpu_output_arg = alloc_percpu(व्योम *);
		BUG_ON(hyperv_pcpu_output_arg == शून्य);
	पूर्ण

	/* Allocate percpu VP index */
	hv_vp_index = kदो_स्मृति_array(num_possible_cpus(), माप(*hv_vp_index),
				    GFP_KERNEL);
	अगर (!hv_vp_index)
		वापस;

	क्रम (i = 0; i < num_possible_cpus(); i++)
		hv_vp_index[i] = VP_INVAL;

	hv_vp_assist_page = kसुस्मृति(num_possible_cpus(),
				    माप(*hv_vp_assist_page), GFP_KERNEL);
	अगर (!hv_vp_assist_page) अणु
		ms_hyperv.hपूर्णांकs &= ~HV_X64_ENLIGHTENED_VMCS_RECOMMENDED;
		जाओ मुक्त_vp_index;
	पूर्ण

	cpuhp = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "x86/hyperv_init:online",
				  hv_cpu_init, hv_cpu_die);
	अगर (cpuhp < 0)
		जाओ मुक्त_vp_assist_page;

	/*
	 * Setup the hypercall page and enable hypercalls.
	 * 1. Register the guest ID
	 * 2. Enable the hypercall and रेजिस्टर the hypercall page
	 */
	guest_id = generate_guest_id(0, LINUX_VERSION_CODE, 0);
	wrmsrl(HV_X64_MSR_GUEST_OS_ID, guest_id);

	hv_hypercall_pg = __vदो_स्मृति_node_range(PAGE_SIZE, 1, VMALLOC_START,
			VMALLOC_END, GFP_KERNEL, PAGE_KERNEL_ROX,
			VM_FLUSH_RESET_PERMS, NUMA_NO_NODE,
			__builtin_वापस_address(0));
	अगर (hv_hypercall_pg == शून्य) अणु
		wrmsrl(HV_X64_MSR_GUEST_OS_ID, 0);
		जाओ हटाओ_cpuhp_state;
	पूर्ण

	rdmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uपूर्णांक64);
	hypercall_msr.enable = 1;

	अगर (hv_root_partition) अणु
		काष्ठा page *pg;
		व्योम *src, *dst;

		/*
		 * For the root partition, the hypervisor will set up its
		 * hypercall page. The hypervisor guarantees it will not show
		 * up in the root's address space. The root can't change the
		 * location of the hypercall page.
		 *
		 * Order is important here. We must enable the hypercall page
		 * so it is populated with code, then copy the code to an
		 * executable page.
		 */
		wrmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uपूर्णांक64);

		pg = vदो_स्मृति_to_page(hv_hypercall_pg);
		dst = kmap(pg);
		src = memremap(hypercall_msr.guest_physical_address << PAGE_SHIFT, PAGE_SIZE,
				MEMREMAP_WB);
		BUG_ON(!(src && dst));
		स_नकल(dst, src, HV_HYP_PAGE_SIZE);
		memunmap(src);
		kunmap(pg);
	पूर्ण अन्यथा अणु
		hypercall_msr.guest_physical_address = vदो_स्मृति_to_pfn(hv_hypercall_pg);
		wrmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uपूर्णांक64);
	पूर्ण

	/*
	 * hyperv_init() is called beक्रमe LAPIC is initialized: see
	 * apic_पूर्णांकr_mode_init() -> x86_platक्रमm.apic_post_init() and
	 * apic_bsp_setup() -> setup_local_APIC(). The direct-mode STIMER
	 * depends on LAPIC, so hv_sसमयr_alloc() should be called from
	 * x86_init.समयrs.setup_percpu_घड़ीev.
	 */
	old_setup_percpu_घड़ीev = x86_init.समयrs.setup_percpu_घड़ीev;
	x86_init.समयrs.setup_percpu_घड़ीev = hv_sसमयr_setup_percpu_घड़ीev;

	hv_apic_init();

	x86_init.pci.arch_init = hv_pci_init;

	रेजिस्टर_syscore_ops(&hv_syscore_ops);

	hyperv_init_cpuhp = cpuhp;

	अगर (cpuid_ebx(HYPERV_CPUID_FEATURES) & HV_ACCESS_PARTITION_ID)
		hv_get_partition_id();

	BUG_ON(hv_root_partition && hv_current_partition_id == ~0ull);

#अगर_घोषित CONFIG_PCI_MSI
	/*
	 * If we're running as root, we want to create our own PCI MSI करोमुख्य.
	 * We can't set this in hv_pci_init because that would be too late.
	 */
	अगर (hv_root_partition)
		x86_init.irqs.create_pci_msi_करोमुख्य = hv_create_pci_msi_करोमुख्य;
#पूर्ण_अगर

	/* Query the VMs extended capability once, so that it can be cached. */
	hv_query_ext_cap(0);
	वापस;

हटाओ_cpuhp_state:
	cpuhp_हटाओ_state(cpuhp);
मुक्त_vp_assist_page:
	kमुक्त(hv_vp_assist_page);
	hv_vp_assist_page = शून्य;
मुक्त_vp_index:
	kमुक्त(hv_vp_index);
	hv_vp_index = शून्य;
पूर्ण

/*
 * This routine is called beक्रमe kexec/kdump, it करोes the required cleanup.
 */
व्योम hyperv_cleanup(व्योम)
अणु
	जोड़ hv_x64_msr_hypercall_contents hypercall_msr;

	unरेजिस्टर_syscore_ops(&hv_syscore_ops);

	/* Reset our OS id */
	wrmsrl(HV_X64_MSR_GUEST_OS_ID, 0);

	/*
	 * Reset hypercall page reference beक्रमe reset the page,
	 * let hypercall operations fail safely rather than
	 * panic the kernel क्रम using invalid hypercall page
	 */
	hv_hypercall_pg = शून्य;

	/* Reset the hypercall page */
	hypercall_msr.as_uपूर्णांक64 = 0;
	wrmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uपूर्णांक64);

	/* Reset the TSC page */
	hypercall_msr.as_uपूर्णांक64 = 0;
	wrmsrl(HV_X64_MSR_REFERENCE_TSC, hypercall_msr.as_uपूर्णांक64);
पूर्ण
EXPORT_SYMBOL_GPL(hyperv_cleanup);

व्योम hyperv_report_panic(काष्ठा pt_regs *regs, दीर्घ err, bool in_die)
अणु
	अटल bool panic_reported;
	u64 guest_id;

	अगर (in_die && !panic_on_oops)
		वापस;

	/*
	 * We prefer to report panic on 'die' chain as we have proper
	 * रेजिस्टरs to report, but अगर we miss it (e.g. on BUG()) we need
	 * to report it on 'panic'.
	 */
	अगर (panic_reported)
		वापस;
	panic_reported = true;

	rdmsrl(HV_X64_MSR_GUEST_OS_ID, guest_id);

	wrmsrl(HV_X64_MSR_CRASH_P0, err);
	wrmsrl(HV_X64_MSR_CRASH_P1, guest_id);
	wrmsrl(HV_X64_MSR_CRASH_P2, regs->ip);
	wrmsrl(HV_X64_MSR_CRASH_P3, regs->ax);
	wrmsrl(HV_X64_MSR_CRASH_P4, regs->sp);

	/*
	 * Let Hyper-V know there is crash data available
	 */
	wrmsrl(HV_X64_MSR_CRASH_CTL, HV_CRASH_CTL_CRASH_NOTIFY);
पूर्ण
EXPORT_SYMBOL_GPL(hyperv_report_panic);

bool hv_is_hyperv_initialized(व्योम)
अणु
	जोड़ hv_x64_msr_hypercall_contents hypercall_msr;

	/*
	 * Ensure that we're really on Hyper-V, and not a KVM or Xen
	 * emulation of Hyper-V
	 */
	अगर (x86_hyper_type != X86_HYPER_MS_HYPERV)
		वापस false;

	/*
	 * Verअगरy that earlier initialization succeeded by checking
	 * that the hypercall page is setup
	 */
	hypercall_msr.as_uपूर्णांक64 = 0;
	rdmsrl(HV_X64_MSR_HYPERCALL, hypercall_msr.as_uपूर्णांक64);

	वापस hypercall_msr.enable;
पूर्ण
EXPORT_SYMBOL_GPL(hv_is_hyperv_initialized);

bool hv_is_hibernation_supported(व्योम)
अणु
	वापस !hv_root_partition && acpi_sleep_state_supported(ACPI_STATE_S4);
पूर्ण
EXPORT_SYMBOL_GPL(hv_is_hibernation_supported);

क्रमागत hv_isolation_type hv_get_isolation_type(व्योम)
अणु
	अगर (!(ms_hyperv.priv_high & HV_ISOLATION))
		वापस HV_ISOLATION_TYPE_NONE;
	वापस FIELD_GET(HV_ISOLATION_TYPE, ms_hyperv.isolation_config_b);
पूर्ण
EXPORT_SYMBOL_GPL(hv_get_isolation_type);

bool hv_is_isolation_supported(व्योम)
अणु
	वापस hv_get_isolation_type() != HV_ISOLATION_TYPE_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(hv_is_isolation_supported);

/* Bit mask of the extended capability to query: see HV_EXT_CAPABILITY_xxx */
bool hv_query_ext_cap(u64 cap_query)
अणु
	/*
	 * The address of the 'hv_extended_cap' variable will be used as an
	 * output parameter to the hypercall below and so it should be
	 * compatible with 'virt_to_phys'. Which means, it's address should be
	 * directly mapped. Use 'static' to keep it compatible; stack variables
	 * can be भवly mapped, making them imcompatible with
	 * 'virt_to_phys'.
	 * Hypercall input/output addresses should also be 8-byte aligned.
	 */
	अटल u64 hv_extended_cap __aligned(8);
	अटल bool hv_extended_cap_queried;
	u64 status;

	/*
	 * Querying extended capabilities is an extended hypercall. Check अगर the
	 * partition supports extended hypercall, first.
	 */
	अगर (!(ms_hyperv.priv_high & HV_ENABLE_EXTENDED_HYPERCALLS))
		वापस false;

	/* Extended capabilities करो not change at runसमय. */
	अगर (hv_extended_cap_queried)
		वापस hv_extended_cap & cap_query;

	status = hv_करो_hypercall(HV_EXT_CALL_QUERY_CAPABILITIES, शून्य,
				 &hv_extended_cap);

	/*
	 * The query extended capabilities hypercall should not fail under
	 * any normal circumstances. Aव्योम repeatedly making the hypercall, on
	 * error.
	 */
	hv_extended_cap_queried = true;
	status &= HV_HYPERCALL_RESULT_MASK;
	अगर (status != HV_STATUS_SUCCESS) अणु
		pr_err("Hyper-V: Extended query capabilities hypercall failed 0x%llx\n",
		       status);
		वापस false;
	पूर्ण

	वापस hv_extended_cap & cap_query;
पूर्ण
EXPORT_SYMBOL_GPL(hv_query_ext_cap);
