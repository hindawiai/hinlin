<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <xen/xen.h>
#समावेश <xen/events.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/hvm.h>
#समावेश <xen/पूर्णांकerface/vcpu.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/पूर्णांकerface/hvm/params.h>
#समावेश <xen/features.h>
#समावेश <xen/platक्रमm_pci.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/page.h>
#समावेश <xen/पूर्णांकerface/sched.h>
#समावेश <xen/xen-ops.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/efi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_address.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/cpu.h>
#समावेश <linux/console.h>
#समावेश <linux/pvघड़ी_gtod.h>
#समावेश <linux/समय64.h>
#समावेश <linux/समयkeeping.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <linux/acpi.h>

#समावेश <linux/mm.h>

अटल काष्ठा start_info _xen_start_info;
काष्ठा start_info *xen_start_info = &_xen_start_info;
EXPORT_SYMBOL(xen_start_info);

क्रमागत xen_करोमुख्य_type xen_करोमुख्य_type = XEN_NATIVE;
EXPORT_SYMBOL(xen_करोमुख्य_type);

काष्ठा shared_info xen_dummy_shared_info;
काष्ठा shared_info *HYPERVISOR_shared_info = (व्योम *)&xen_dummy_shared_info;

DEFINE_PER_CPU(काष्ठा vcpu_info *, xen_vcpu);
अटल काष्ठा vcpu_info __percpu *xen_vcpu_info;

/* Linux <-> Xen vCPU id mapping */
DEFINE_PER_CPU(uपूर्णांक32_t, xen_vcpu_id);
EXPORT_PER_CPU_SYMBOL(xen_vcpu_id);

/* These are unused until we support booting "pre-ballooned" */
अचिन्हित दीर्घ xen_released_pages;
काष्ठा xen_memory_region xen_extra_mem[XEN_EXTRA_MEM_MAX_REGIONS] __initdata;

अटल __पढ़ो_mostly अचिन्हित पूर्णांक xen_events_irq;

uपूर्णांक32_t xen_start_flags;
EXPORT_SYMBOL(xen_start_flags);

पूर्णांक xen_unmap_करोमुख्य_gfn_range(काष्ठा vm_area_काष्ठा *vma,
			       पूर्णांक nr, काष्ठा page **pages)
अणु
	वापस xen_xlate_unmap_gfn_range(vma, nr, pages);
पूर्ण
EXPORT_SYMBOL_GPL(xen_unmap_करोमुख्य_gfn_range);

अटल व्योम xen_पढ़ो_wallघड़ी(काष्ठा बारpec64 *ts)
अणु
	u32 version;
	काष्ठा बारpec64 now, ts_monotonic;
	काष्ठा shared_info *s = HYPERVISOR_shared_info;
	काष्ठा pvघड़ी_wall_घड़ी *wall_घड़ी = &(s->wc);

	/* get wallघड़ी at प्रणाली boot */
	करो अणु
		version = wall_घड़ी->version;
		rmb();		/* fetch version beक्रमe समय */
		now.tv_sec  = ((uपूर्णांक64_t)wall_घड़ी->sec_hi << 32) | wall_घड़ी->sec;
		now.tv_nsec = wall_घड़ी->nsec;
		rmb();		/* fetch समय beक्रमe checking version */
	पूर्ण जबतक ((wall_घड़ी->version & 1) || (version != wall_घड़ी->version));

	/* समय since प्रणाली boot */
	kसमय_get_ts64(&ts_monotonic);
	*ts = बारpec64_add(now, ts_monotonic);
पूर्ण

अटल पूर्णांक xen_pvघड़ी_gtod_notअगरy(काष्ठा notअगरier_block *nb,
				   अचिन्हित दीर्घ was_set, व्योम *priv)
अणु
	/* Protected by the calling core code serialization */
	अटल काष्ठा बारpec64 next_sync;

	काष्ठा xen_platक्रमm_op op;
	काष्ठा बारpec64 now, प्रणाली_समय;
	काष्ठा समयkeeper *tk = priv;

	now.tv_sec = tk->xसमय_sec;
	now.tv_nsec = (दीर्घ)(tk->tkr_mono.xसमय_nsec >> tk->tkr_mono.shअगरt);
	प्रणाली_समय = बारpec64_add(now, tk->wall_to_monotonic);

	/*
	 * We only take the expensive HV call when the घड़ी was set
	 * or when the 11 minutes RTC synchronization समय elapsed.
	 */
	अगर (!was_set && बारpec64_compare(&now, &next_sync) < 0)
		वापस NOTIFY_OK;

	op.cmd = XENPF_समय_रखो64;
	op.u.समय_रखो64.mbz = 0;
	op.u.समय_रखो64.secs = now.tv_sec;
	op.u.समय_रखो64.nsecs = now.tv_nsec;
	op.u.समय_रखो64.प्रणाली_समय = बारpec64_to_ns(&प्रणाली_समय);
	(व्योम)HYPERVISOR_platक्रमm_op(&op);

	/*
	 * Move the next drअगरt compensation समय 11 minutes
	 * ahead. That's emulating the sync_cmos_घड़ी() update क्रम
	 * the hardware RTC.
	 */
	next_sync = now;
	next_sync.tv_sec += 11 * 60;

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block xen_pvघड़ी_gtod_notअगरier = अणु
	.notअगरier_call = xen_pvघड़ी_gtod_notअगरy,
पूर्ण;

अटल पूर्णांक xen_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा vcpu_रेजिस्टर_vcpu_info info;
	काष्ठा vcpu_info *vcpup;
	पूर्णांक err;

	/* 
	 * VCPUOP_रेजिस्टर_vcpu_info cannot be called twice क्रम the same
	 * vcpu, so अगर vcpu_info is alपढ़ोy रेजिस्टरed, just get out. This
	 * can happen with cpu-hotplug.
	 */
	अगर (per_cpu(xen_vcpu, cpu) != शून्य)
		जाओ after_रेजिस्टर_vcpu_info;

	pr_info("Xen: initializing cpu%d\n", cpu);
	vcpup = per_cpu_ptr(xen_vcpu_info, cpu);

	info.mfn = percpu_to_gfn(vcpup);
	info.offset = xen_offset_in_page(vcpup);

	err = HYPERVISOR_vcpu_op(VCPUOP_रेजिस्टर_vcpu_info, xen_vcpu_nr(cpu),
				 &info);
	BUG_ON(err);
	per_cpu(xen_vcpu, cpu) = vcpup;

	अगर (!xen_kernel_unmapped_at_usr())
		xen_setup_runstate_info(cpu);

after_रेजिस्टर_vcpu_info:
	enable_percpu_irq(xen_events_irq, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक xen_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	disable_percpu_irq(xen_events_irq);
	वापस 0;
पूर्ण

व्योम xen_reboot(पूर्णांक reason)
अणु
	काष्ठा sched_shutकरोwn r = अणु .reason = reason पूर्ण;
	पूर्णांक rc;

	rc = HYPERVISOR_sched_op(SCHEDOP_shutकरोwn, &r);
	BUG_ON(rc);
पूर्ण

अटल व्योम xen_restart(क्रमागत reboot_mode reboot_mode, स्थिर अक्षर *cmd)
अणु
	xen_reboot(SHUTDOWN_reboot);
पूर्ण


अटल व्योम xen_घातer_off(व्योम)
अणु
	xen_reboot(SHUTDOWN_घातeroff);
पूर्ण

अटल irqवापस_t xen_arm_callback(पूर्णांक irq, व्योम *arg)
अणु
	xen_hvm_evtchn_करो_upcall();
	वापस IRQ_HANDLED;
पूर्ण

अटल __initdata काष्ठा अणु
	स्थिर अक्षर *compat;
	स्थिर अक्षर *prefix;
	स्थिर अक्षर *version;
	bool found;
पूर्ण hyper_node = अणु"xen,xen", "xen,xen-", शून्य, falseपूर्ण;

अटल पूर्णांक __init fdt_find_hyper_node(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				      पूर्णांक depth, व्योम *data)
अणु
	स्थिर व्योम *s = शून्य;
	पूर्णांक len;

	अगर (depth != 1 || म_भेद(uname, "hypervisor") != 0)
		वापस 0;

	अगर (of_flat_dt_is_compatible(node, hyper_node.compat))
		hyper_node.found = true;

	s = of_get_flat_dt_prop(node, "compatible", &len);
	अगर (म_माप(hyper_node.prefix) + 3  < len &&
	    !म_भेदन(hyper_node.prefix, s, म_माप(hyper_node.prefix)))
		hyper_node.version = s + म_माप(hyper_node.prefix);

	/*
	 * Check अगर Xen supports EFI by checking whether there is the
	 * "/hypervisor/uefi" node in DT. If so, runसमय services are available
	 * through proxy functions (e.g. in हाल of Xen करोm0 EFI implementation
	 * they call special hypercall which executes relevant EFI functions)
	 * and that is why they are always enabled.
	 */
	अगर (IS_ENABLED(CONFIG_XEN_EFI)) अणु
		अगर ((of_get_flat_dt_subnode_by_name(node, "uefi") > 0) &&
		    !efi_runसमय_disabled())
			set_bit(EFI_RUNTIME_SERVICES, &efi.flags);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * see Documentation/devicetree/bindings/arm/xen.txt क्रम the
 * करोcumentation of the Xen Device Tree क्रमmat.
 */
व्योम __init xen_early_init(व्योम)
अणु
	of_scan_flat_dt(fdt_find_hyper_node, शून्य);
	अगर (!hyper_node.found) अणु
		pr_debug("No Xen support\n");
		वापस;
	पूर्ण

	अगर (hyper_node.version == शून्य) अणु
		pr_debug("Xen version not found\n");
		वापस;
	पूर्ण

	pr_info("Xen %s support found\n", hyper_node.version);

	xen_करोमुख्य_type = XEN_HVM_DOMAIN;

	xen_setup_features();

	अगर (xen_feature(XENFEAT_करोm0))
		xen_start_flags |= SIF_INITDOMAIN|SIF_PRIVILEGED;

	अगर (!console_set_on_cmdline && !xen_initial_करोमुख्य())
		add_preferred_console("hvc", 0, शून्य);
पूर्ण

अटल व्योम __init xen_acpi_guest_init(व्योम)
अणु
#अगर_घोषित CONFIG_ACPI
	काष्ठा xen_hvm_param a;
	पूर्णांक पूर्णांकerrupt, trigger, polarity;

	a.करोmid = DOMID_SELF;
	a.index = HVM_PARAM_CALLBACK_IRQ;

	अगर (HYPERVISOR_hvm_op(HVMOP_get_param, &a)
	    || (a.value >> 56) != HVM_PARAM_CALLBACK_TYPE_PPI) अणु
		xen_events_irq = 0;
		वापस;
	पूर्ण

	पूर्णांकerrupt = a.value & 0xff;
	trigger = ((a.value >> 8) & 0x1) ? ACPI_EDGE_SENSITIVE
					 : ACPI_LEVEL_SENSITIVE;
	polarity = ((a.value >> 8) & 0x2) ? ACPI_ACTIVE_LOW
					  : ACPI_ACTIVE_HIGH;
	xen_events_irq = acpi_रेजिस्टर_gsi(शून्य, पूर्णांकerrupt, trigger, polarity);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init xen_dt_guest_init(व्योम)
अणु
	काष्ठा device_node *xen_node;

	xen_node = of_find_compatible_node(शून्य, शून्य, "xen,xen");
	अगर (!xen_node) अणु
		pr_err("Xen support was detected before, but it has disappeared\n");
		वापस;
	पूर्ण

	xen_events_irq = irq_of_parse_and_map(xen_node, 0);
पूर्ण

अटल पूर्णांक __init xen_guest_init(व्योम)
अणु
	काष्ठा xen_add_to_physmap xatp;
	काष्ठा shared_info *shared_info_page = शून्य;
	पूर्णांक cpu;

	अगर (!xen_करोमुख्य())
		वापस 0;

	अगर (!acpi_disabled)
		xen_acpi_guest_init();
	अन्यथा
		xen_dt_guest_init();

	अगर (!xen_events_irq) अणु
		pr_err("Xen event channel interrupt not found\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * The fdt parsing codes have set EFI_RUNTIME_SERVICES अगर Xen EFI
	 * parameters are found. Force enable runसमय services.
	 */
	अगर (efi_enabled(EFI_RUNTIME_SERVICES))
		xen_efi_runसमय_setup();

	shared_info_page = (काष्ठा shared_info *)get_zeroed_page(GFP_KERNEL);

	अगर (!shared_info_page) अणु
		pr_err("not enough memory\n");
		वापस -ENOMEM;
	पूर्ण
	xatp.करोmid = DOMID_SELF;
	xatp.idx = 0;
	xatp.space = XENMAPSPACE_shared_info;
	xatp.gpfn = virt_to_gfn(shared_info_page);
	अगर (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp))
		BUG();

	HYPERVISOR_shared_info = (काष्ठा shared_info *)shared_info_page;

	/* xen_vcpu is a poपूर्णांकer to the vcpu_info काष्ठा in the shared_info
	 * page, we use it in the event channel upcall and in some pvघड़ी
	 * related functions. 
	 * The shared info contains exactly 1 CPU (the boot CPU). The guest
	 * is required to use VCPUOP_रेजिस्टर_vcpu_info to place vcpu info
	 * क्रम secondary CPUs as they are brought up.
	 * For unअगरormity we use VCPUOP_रेजिस्टर_vcpu_info even on cpu0.
	 */
	xen_vcpu_info = alloc_percpu(काष्ठा vcpu_info);
	अगर (xen_vcpu_info == शून्य)
		वापस -ENOMEM;

	/* Direct vCPU id mapping क्रम ARM guests. */
	क्रम_each_possible_cpu(cpu)
		per_cpu(xen_vcpu_id, cpu) = cpu;

	xen_स्वतः_xlat_grant_frames.count = gnttab_max_grant_frames();
	अगर (xen_xlate_map_ballooned_pages(&xen_स्वतः_xlat_grant_frames.pfn,
					  &xen_स्वतः_xlat_grant_frames.vaddr,
					  xen_स्वतः_xlat_grant_frames.count)) अणु
		मुक्त_percpu(xen_vcpu_info);
		वापस -ENOMEM;
	पूर्ण
	gnttab_init();

	/*
	 * Making sure board specअगरic code will not set up ops क्रम
	 * cpu idle and cpu freq.
	 */
	disable_cpuidle();
	disable_cpufreq();

	xen_init_IRQ();

	अगर (request_percpu_irq(xen_events_irq, xen_arm_callback,
			       "events", &xen_vcpu)) अणु
		pr_err("Error request IRQ %d\n", xen_events_irq);
		वापस -EINVAL;
	पूर्ण

	अगर (!xen_kernel_unmapped_at_usr())
		xen_समय_setup_guest();

	अगर (xen_initial_करोमुख्य())
		pvघड़ी_gtod_रेजिस्टर_notअगरier(&xen_pvघड़ी_gtod_notअगरier);

	वापस cpuhp_setup_state(CPUHP_AP_ARM_XEN_STARTING,
				 "arm/xen:starting", xen_starting_cpu,
				 xen_dying_cpu);
पूर्ण
early_initcall(xen_guest_init);

अटल पूर्णांक __init xen_pm_init(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	pm_घातer_off = xen_घातer_off;
	arm_pm_restart = xen_restart;
	अगर (!xen_initial_करोमुख्य()) अणु
		काष्ठा बारpec64 ts;
		xen_पढ़ो_wallघड़ी(&ts);
		करो_समय_रखोofday64(&ts);
	पूर्ण

	वापस 0;
पूर्ण
late_initcall(xen_pm_init);


/* empty stubs */
व्योम xen_arch_pre_suspend(व्योम) अणु पूर्ण
व्योम xen_arch_post_suspend(पूर्णांक suspend_cancelled) अणु पूर्ण
व्योम xen_समयr_resume(व्योम) अणु पूर्ण
व्योम xen_arch_resume(व्योम) अणु पूर्ण
व्योम xen_arch_suspend(व्योम) अणु पूर्ण


/* In the hypercall.S file. */
EXPORT_SYMBOL_GPL(HYPERVISOR_event_channel_op);
EXPORT_SYMBOL_GPL(HYPERVISOR_grant_table_op);
EXPORT_SYMBOL_GPL(HYPERVISOR_xen_version);
EXPORT_SYMBOL_GPL(HYPERVISOR_console_io);
EXPORT_SYMBOL_GPL(HYPERVISOR_sched_op);
EXPORT_SYMBOL_GPL(HYPERVISOR_hvm_op);
EXPORT_SYMBOL_GPL(HYPERVISOR_memory_op);
EXPORT_SYMBOL_GPL(HYPERVISOR_physdev_op);
EXPORT_SYMBOL_GPL(HYPERVISOR_vcpu_op);
EXPORT_SYMBOL_GPL(HYPERVISOR_पंचांगem_op);
EXPORT_SYMBOL_GPL(HYPERVISOR_platक्रमm_op_raw);
EXPORT_SYMBOL_GPL(HYPERVISOR_multicall);
EXPORT_SYMBOL_GPL(HYPERVISOR_vm_assist);
EXPORT_SYMBOL_GPL(HYPERVISOR_dm_op);
EXPORT_SYMBOL_GPL(privcmd_call);
