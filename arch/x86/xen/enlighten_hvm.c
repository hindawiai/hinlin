<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/acpi.h>
#समावेश <linux/cpu.h>
#समावेश <linux/kexec.h>
#समावेश <linux/memblock.h>

#समावेश <xen/features.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/memory.h>

#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/early_ioremap.h>

#समावेश <यंत्र/xen/cpuid.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/page.h>

#समावेश "xen-ops.h"
#समावेश "mmu.h"
#समावेश "smp.h"

अटल अचिन्हित दीर्घ shared_info_pfn;

व्योम xen_hvm_init_shared_info(व्योम)
अणु
	काष्ठा xen_add_to_physmap xatp;

	xatp.करोmid = DOMID_SELF;
	xatp.idx = 0;
	xatp.space = XENMAPSPACE_shared_info;
	xatp.gpfn = shared_info_pfn;
	अगर (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp))
		BUG();
पूर्ण

अटल व्योम __init reserve_shared_info(व्योम)
अणु
	u64 pa;

	/*
	 * Search क्रम a मुक्त page starting at 4kB physical address.
	 * Low memory is preferred to aव्योम an EPT large page split up
	 * by the mapping.
	 * Starting below X86_RESERVE_LOW (usually 64kB) is fine as
	 * the BIOS used क्रम HVM guests is well behaved and won't
	 * clobber memory other than the first 4kB.
	 */
	क्रम (pa = PAGE_SIZE;
	     !e820__mapped_all(pa, pa + PAGE_SIZE, E820_TYPE_RAM) ||
	     memblock_is_reserved(pa);
	     pa += PAGE_SIZE)
		;

	shared_info_pfn = PHYS_PFN(pa);

	memblock_reserve(pa, PAGE_SIZE);
	HYPERVISOR_shared_info = early_memremap(pa, PAGE_SIZE);
पूर्ण

अटल व्योम __init xen_hvm_init_mem_mapping(व्योम)
अणु
	early_memunmap(HYPERVISOR_shared_info, PAGE_SIZE);
	HYPERVISOR_shared_info = __va(PFN_PHYS(shared_info_pfn));

	/*
	 * The भव address of the shared_info page has changed, so
	 * the vcpu_info poपूर्णांकer क्रम VCPU 0 is now stale.
	 *
	 * The prepare_boot_cpu callback will re-initialize it via
	 * xen_vcpu_setup, but we can't rely on that to be called क्रम
	 * old Xen versions (xen_have_vector_callback == 0).
	 *
	 * It is, in any हाल, bad to have a stale vcpu_info poपूर्णांकer
	 * so reset it now.
	 */
	xen_vcpu_info_reset(0);
पूर्ण

अटल व्योम __init init_hvm_pv_info(व्योम)
अणु
	पूर्णांक major, minor;
	uपूर्णांक32_t eax, ebx, ecx, edx, base;

	base = xen_cpuid_base();
	eax = cpuid_eax(base + 1);

	major = eax >> 16;
	minor = eax & 0xffff;
	prपूर्णांकk(KERN_INFO "Xen version %d.%d.\n", major, minor);

	xen_करोमुख्य_type = XEN_HVM_DOMAIN;

	/* PVH set up hypercall page in xen_prepare_pvh(). */
	अगर (xen_pvh_करोमुख्य())
		pv_info.name = "Xen PVH";
	अन्यथा अणु
		u64 pfn;
		uपूर्णांक32_t msr;

		pv_info.name = "Xen HVM";
		msr = cpuid_ebx(base + 2);
		pfn = __pa(hypercall_page);
		wrmsr_safe(msr, (u32)pfn, (u32)(pfn >> 32));
	पूर्ण

	xen_setup_features();

	cpuid(base + 4, &eax, &ebx, &ecx, &edx);
	अगर (eax & XEN_HVM_CPUID_VCPU_ID_PRESENT)
		this_cpu_ग_लिखो(xen_vcpu_id, ebx);
	अन्यथा
		this_cpu_ग_लिखो(xen_vcpu_id, smp_processor_id());
पूर्ण

DEFINE_IDTENTRY_SYSVEC(sysvec_xen_hvm_callback)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);

	inc_irq_stat(irq_hv_callback_count);

	xen_hvm_evtchn_करो_upcall();

	set_irq_regs(old_regs);
पूर्ण

#अगर_घोषित CONFIG_KEXEC_CORE
अटल व्योम xen_hvm_shutकरोwn(व्योम)
अणु
	native_machine_shutकरोwn();
	अगर (kexec_in_progress)
		xen_reboot(SHUTDOWN_soft_reset);
पूर्ण

अटल व्योम xen_hvm_crash_shutकरोwn(काष्ठा pt_regs *regs)
अणु
	native_machine_crash_shutकरोwn(regs);
	xen_reboot(SHUTDOWN_soft_reset);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक xen_cpu_up_prepare_hvm(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक rc = 0;

	/*
	 * This can happen अगर CPU was offlined earlier and
	 * offlining समयd out in common_cpu_die().
	 */
	अगर (cpu_report_state(cpu) == CPU_DEAD_FROZEN) अणु
		xen_smp_पूर्णांकr_मुक्त(cpu);
		xen_uninit_lock_cpu(cpu);
	पूर्ण

	अगर (cpu_acpi_id(cpu) != U32_MAX)
		per_cpu(xen_vcpu_id, cpu) = cpu_acpi_id(cpu);
	अन्यथा
		per_cpu(xen_vcpu_id, cpu) = cpu;
	rc = xen_vcpu_setup(cpu);
	अगर (rc || !xen_have_vector_callback)
		वापस rc;

	अगर (xen_feature(XENFEAT_hvm_safe_pvघड़ी))
		xen_setup_समयr(cpu);

	rc = xen_smp_पूर्णांकr_init(cpu);
	अगर (rc) अणु
		WARN(1, "xen_smp_intr_init() for CPU %d failed: %d\n",
		     cpu, rc);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक xen_cpu_dead_hvm(अचिन्हित पूर्णांक cpu)
अणु
	xen_smp_पूर्णांकr_मुक्त(cpu);

	अगर (xen_have_vector_callback && xen_feature(XENFEAT_hvm_safe_pvघड़ी))
		xen_tearकरोwn_समयr(cpu);

       वापस 0;
पूर्ण

अटल bool no_vector_callback __initdata;

अटल व्योम __init xen_hvm_guest_init(व्योम)
अणु
	अगर (xen_pv_करोमुख्य())
		वापस;

	init_hvm_pv_info();

	reserve_shared_info();
	xen_hvm_init_shared_info();

	/*
	 * xen_vcpu is a poपूर्णांकer to the vcpu_info काष्ठा in the shared_info
	 * page, we use it in the event channel upcall and in some pvघड़ी
	 * related functions.
	 */
	xen_vcpu_info_reset(0);

	xen_panic_handler_init();

	अगर (!no_vector_callback && xen_feature(XENFEAT_hvm_callback_vector))
		xen_have_vector_callback = 1;

	xen_hvm_smp_init();
	WARN_ON(xen_cpuhp_setup(xen_cpu_up_prepare_hvm, xen_cpu_dead_hvm));
	xen_unplug_emulated_devices();
	x86_init.irqs.पूर्णांकr_init = xen_init_IRQ;
	xen_hvm_init_समय_ops();
	xen_hvm_init_mmu_ops();

#अगर_घोषित CONFIG_KEXEC_CORE
	machine_ops.shutकरोwn = xen_hvm_shutकरोwn;
	machine_ops.crash_shutकरोwn = xen_hvm_crash_shutकरोwn;
#पूर्ण_अगर
पूर्ण

अटल __init पूर्णांक xen_parse_nopv(अक्षर *arg)
अणु
	pr_notice("\"xen_nopv\" is deprecated, please use \"nopv\" instead\n");

	अगर (xen_cpuid_base())
		nopv = true;
	वापस 0;
पूर्ण
early_param("xen_nopv", xen_parse_nopv);

अटल __init पूर्णांक xen_parse_no_vector_callback(अक्षर *arg)
अणु
	no_vector_callback = true;
	वापस 0;
पूर्ण
early_param("xen_no_vector_callback", xen_parse_no_vector_callback);

bool __init xen_hvm_need_lapic(व्योम)
अणु
	अगर (xen_pv_करोमुख्य())
		वापस false;
	अगर (!xen_hvm_करोमुख्य())
		वापस false;
	अगर (xen_feature(XENFEAT_hvm_pirqs) && xen_have_vector_callback)
		वापस false;
	वापस true;
पूर्ण

अटल __init व्योम xen_hvm_guest_late_init(व्योम)
अणु
#अगर_घोषित CONFIG_XEN_PVH
	/* Test क्रम PVH करोमुख्य (PVH boot path taken overrides ACPI flags). */
	अगर (!xen_pvh &&
	    (x86_platक्रमm.legacy.rtc || !x86_platक्रमm.legacy.no_vga))
		वापस;

	/* PVH detected. */
	xen_pvh = true;

	अगर (nopv)
		panic("\"nopv\" and \"xen_nopv\" parameters are unsupported in PVH guest.");

	/* Make sure we करोn't fall back to (शेष) ACPI_IRQ_MODEL_PIC. */
	अगर (!nr_ioapics && acpi_irq_model == ACPI_IRQ_MODEL_PIC)
		acpi_irq_model = ACPI_IRQ_MODEL_PLATFORM;

	machine_ops.emergency_restart = xen_emergency_restart;
	pv_info.name = "Xen PVH";
#पूर्ण_अगर
पूर्ण

अटल uपूर्णांक32_t __init xen_platक्रमm_hvm(व्योम)
अणु
	uपूर्णांक32_t xen_करोमुख्य = xen_cpuid_base();
	काष्ठा x86_hyper_init *h = &x86_hyper_xen_hvm.init;

	अगर (xen_pv_करोमुख्य())
		वापस 0;

	अगर (xen_pvh_करोमुख्य() && nopv) अणु
		/* Guest booting via the Xen-PVH boot entry goes here */
		pr_info("\"nopv\" parameter is ignored in PVH guest\n");
		nopv = false;
	पूर्ण अन्यथा अगर (nopv && xen_करोमुख्य) अणु
		/*
		 * Guest booting via normal boot entry (like via grub2) goes
		 * here.
		 *
		 * Use पूर्णांकerface functions क्रम bare hardware अगर nopv,
		 * xen_hvm_guest_late_init is an exception as we need to
		 * detect PVH and panic there.
		 */
		h->init_platक्रमm = x86_init_noop;
		h->x2apic_available = bool_x86_init_noop;
		h->init_mem_mapping = x86_init_noop;
		h->init_after_booपंचांगem = x86_init_noop;
		h->guest_late_init = xen_hvm_guest_late_init;
		x86_hyper_xen_hvm.runसमय.pin_vcpu = x86_op_पूर्णांक_noop;
	पूर्ण
	वापस xen_करोमुख्य;
पूर्ण

काष्ठा hypervisor_x86 x86_hyper_xen_hvm __initdata = अणु
	.name                   = "Xen HVM",
	.detect                 = xen_platक्रमm_hvm,
	.type			= X86_HYPER_XEN_HVM,
	.init.init_platक्रमm     = xen_hvm_guest_init,
	.init.x2apic_available  = xen_x2apic_para_available,
	.init.init_mem_mapping	= xen_hvm_init_mem_mapping,
	.init.guest_late_init	= xen_hvm_guest_late_init,
	.runसमय.pin_vcpu       = xen_pin_vcpu,
	.ignore_nopv            = true,
पूर्ण;
