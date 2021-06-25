<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#अगर_घोषित CONFIG_XEN_BALLOON_MEMORY_HOTPLUG
#समावेश <linux/memblock.h>
#पूर्ण_अगर
#समावेश <linux/cpu.h>
#समावेश <linux/kexec.h>
#समावेश <linux/slab.h>

#समावेश <xen/xen.h>
#समावेश <xen/features.h>
#समावेश <xen/page.h>

#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/e820/api.h> 

#समावेश "xen-ops.h"
#समावेश "smp.h"
#समावेश "pmu.h"

EXPORT_SYMBOL_GPL(hypercall_page);

/*
 * Poपूर्णांकer to the xen_vcpu_info काष्ठाure or
 * &HYPERVISOR_shared_info->vcpu_info[cpu]. See xen_hvm_init_shared_info
 * and xen_vcpu_setup क्रम details. By शेष it poपूर्णांकs to share_info->vcpu_info
 * but अगर the hypervisor supports VCPUOP_रेजिस्टर_vcpu_info then it can poपूर्णांक
 * to xen_vcpu_info. The poपूर्णांकer is used in __xen_evtchn_करो_upcall to
 * acknowledge pending events.
 * Also more subtly it is used by the patched version of irq enable/disable
 * e.g. xen_irq_enable_direct and xen_iret in PV mode.
 *
 * The desire to be able to करो those mask/unmask operations as a single
 * inकाष्ठाion by using the per-cpu offset held in %gs is the real reason
 * vcpu info is in a per-cpu poपूर्णांकer and the original reason क्रम this
 * hypercall.
 *
 */
DEFINE_PER_CPU(काष्ठा vcpu_info *, xen_vcpu);

/*
 * Per CPU pages used अगर hypervisor supports VCPUOP_रेजिस्टर_vcpu_info
 * hypercall. This can be used both in PV and PVHVM mode. The काष्ठाure
 * overrides the शेष per_cpu(xen_vcpu, cpu) value.
 */
DEFINE_PER_CPU(काष्ठा vcpu_info, xen_vcpu_info);

/* Linux <-> Xen vCPU id mapping */
DEFINE_PER_CPU(uपूर्णांक32_t, xen_vcpu_id);
EXPORT_PER_CPU_SYMBOL(xen_vcpu_id);

क्रमागत xen_करोमुख्य_type xen_करोमुख्य_type = XEN_NATIVE;
EXPORT_SYMBOL_GPL(xen_करोमुख्य_type);

अचिन्हित दीर्घ *machine_to_phys_mapping = (व्योम *)MACH2PHYS_VIRT_START;
EXPORT_SYMBOL(machine_to_phys_mapping);
अचिन्हित दीर्घ  machine_to_phys_nr;
EXPORT_SYMBOL(machine_to_phys_nr);

काष्ठा start_info *xen_start_info;
EXPORT_SYMBOL_GPL(xen_start_info);

काष्ठा shared_info xen_dummy_shared_info;

__पढ़ो_mostly पूर्णांक xen_have_vector_callback;
EXPORT_SYMBOL_GPL(xen_have_vector_callback);

/*
 * NB: needs to live in .data because it's used by xen_prepare_pvh which runs
 * beक्रमe clearing the bss.
 */
uपूर्णांक32_t xen_start_flags __section(".data") = 0;
EXPORT_SYMBOL(xen_start_flags);

/*
 * Poपूर्णांक at some empty memory to start with. We map the real shared_info
 * page as soon as fixmap is up and running.
 */
काष्ठा shared_info *HYPERVISOR_shared_info = &xen_dummy_shared_info;

/*
 * Flag to determine whether vcpu info placement is available on all
 * VCPUs.  We assume it is to start with, and then set it to zero on
 * the first failure.  This is because it can succeed on some VCPUs
 * and not others, since it can involve hypervisor memory allocation,
 * or because the guest failed to guarantee all the appropriate
 * स्थिरraपूर्णांकs on all VCPUs (ie buffer can't cross a page boundary).
 *
 * Note that any particular CPU may be using a placed vcpu काष्ठाure,
 * but we can only optimise अगर the all are.
 *
 * 0: not available, 1: available
 */
पूर्णांक xen_have_vcpu_info_placement = 1;

अटल पूर्णांक xen_cpu_up_online(अचिन्हित पूर्णांक cpu)
अणु
	xen_init_lock_cpu(cpu);
	वापस 0;
पूर्ण

पूर्णांक xen_cpuhp_setup(पूर्णांक (*cpu_up_prepare_cb)(अचिन्हित पूर्णांक),
		    पूर्णांक (*cpu_dead_cb)(अचिन्हित पूर्णांक))
अणु
	पूर्णांक rc;

	rc = cpuhp_setup_state_nocalls(CPUHP_XEN_PREPARE,
				       "x86/xen/guest:prepare",
				       cpu_up_prepare_cb, cpu_dead_cb);
	अगर (rc >= 0) अणु
		rc = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					       "x86/xen/guest:online",
					       xen_cpu_up_online, शून्य);
		अगर (rc < 0)
			cpuhp_हटाओ_state_nocalls(CPUHP_XEN_PREPARE);
	पूर्ण

	वापस rc >= 0 ? 0 : rc;
पूर्ण

अटल पूर्णांक xen_vcpu_setup_restore(पूर्णांक cpu)
अणु
	पूर्णांक rc = 0;

	/* Any per_cpu(xen_vcpu) is stale, so reset it */
	xen_vcpu_info_reset(cpu);

	/*
	 * For PVH and PVHVM, setup online VCPUs only. The rest will
	 * be handled by hotplug.
	 */
	अगर (xen_pv_करोमुख्य() ||
	    (xen_hvm_करोमुख्य() && cpu_online(cpu))) अणु
		rc = xen_vcpu_setup(cpu);
	पूर्ण

	वापस rc;
पूर्ण

/*
 * On restore, set the vcpu placement up again.
 * If it fails, then we're in a bad state, since
 * we can't back out from using it...
 */
व्योम xen_vcpu_restore(व्योम)
अणु
	पूर्णांक cpu, rc;

	क्रम_each_possible_cpu(cpu) अणु
		bool other_cpu = (cpu != smp_processor_id());
		bool is_up;

		अगर (xen_vcpu_nr(cpu) == XEN_VCPU_ID_INVALID)
			जारी;

		/* Only Xen 4.5 and higher support this. */
		is_up = HYPERVISOR_vcpu_op(VCPUOP_is_up,
					   xen_vcpu_nr(cpu), शून्य) > 0;

		अगर (other_cpu && is_up &&
		    HYPERVISOR_vcpu_op(VCPUOP_करोwn, xen_vcpu_nr(cpu), शून्य))
			BUG();

		अगर (xen_pv_करोमुख्य() || xen_feature(XENFEAT_hvm_safe_pvघड़ी))
			xen_setup_runstate_info(cpu);

		rc = xen_vcpu_setup_restore(cpu);
		अगर (rc)
			pr_emerg_once("vcpu restore failed for cpu=%d err=%d. "
					"System will hang.\n", cpu, rc);
		/*
		 * In हाल xen_vcpu_setup_restore() fails, करो not bring up the
		 * VCPU. This helps us aव्योम the resulting OOPS when the VCPU
		 * accesses pvघड़ी_vcpu_समय via xen_vcpu (which is शून्य.)
		 * Note that this करोes not improve the situation much -- now the
		 * VM hangs instead of OOPSing -- with the VCPUs that did not
		 * fail, spinning in stop_machine(), रुकोing क्रम the failed
		 * VCPUs to come up.
		 */
		अगर (other_cpu && is_up && (rc == 0) &&
		    HYPERVISOR_vcpu_op(VCPUOP_up, xen_vcpu_nr(cpu), शून्य))
			BUG();
	पूर्ण
पूर्ण

व्योम xen_vcpu_info_reset(पूर्णांक cpu)
अणु
	अगर (xen_vcpu_nr(cpu) < MAX_VIRT_CPUS) अणु
		per_cpu(xen_vcpu, cpu) =
			&HYPERVISOR_shared_info->vcpu_info[xen_vcpu_nr(cpu)];
	पूर्ण अन्यथा अणु
		/* Set to शून्य so that अगर somebody accesses it we get an OOPS */
		per_cpu(xen_vcpu, cpu) = शून्य;
	पूर्ण
पूर्ण

पूर्णांक xen_vcpu_setup(पूर्णांक cpu)
अणु
	काष्ठा vcpu_रेजिस्टर_vcpu_info info;
	पूर्णांक err;
	काष्ठा vcpu_info *vcpup;

	BUG_ON(HYPERVISOR_shared_info == &xen_dummy_shared_info);

	/*
	 * This path is called on PVHVM at bootup (xen_hvm_smp_prepare_boot_cpu)
	 * and at restore (xen_vcpu_restore). Also called क्रम hotplugged
	 * VCPUs (cpu_init -> xen_hvm_cpu_prepare_hvm).
	 * However, the hypercall can only be करोne once (see below) so अगर a VCPU
	 * is offlined and comes back online then let's not reकरो the hypercall.
	 *
	 * For PV it is called during restore (xen_vcpu_restore) and bootup
	 * (xen_setup_vcpu_info_placement). The hotplug mechanism करोes not
	 * use this function.
	 */
	अगर (xen_hvm_करोमुख्य()) अणु
		अगर (per_cpu(xen_vcpu, cpu) == &per_cpu(xen_vcpu_info, cpu))
			वापस 0;
	पूर्ण

	अगर (xen_have_vcpu_info_placement) अणु
		vcpup = &per_cpu(xen_vcpu_info, cpu);
		info.mfn = arbitrary_virt_to_mfn(vcpup);
		info.offset = offset_in_page(vcpup);

		/*
		 * Check to see अगर the hypervisor will put the vcpu_info
		 * काष्ठाure where we want it, which allows direct access via
		 * a percpu-variable.
		 * N.B. This hypercall can _only_ be called once per CPU.
		 * Subsequent calls will error out with -EINVAL. This is due to
		 * the fact that hypervisor has no unरेजिस्टर variant and this
		 * hypercall करोes not allow to over-ग_लिखो info.mfn and
		 * info.offset.
		 */
		err = HYPERVISOR_vcpu_op(VCPUOP_रेजिस्टर_vcpu_info,
					 xen_vcpu_nr(cpu), &info);

		अगर (err) अणु
			pr_warn_once("register_vcpu_info failed: cpu=%d err=%d\n",
				     cpu, err);
			xen_have_vcpu_info_placement = 0;
		पूर्ण अन्यथा अणु
			/*
			 * This cpu is using the रेजिस्टरed vcpu info, even अगर
			 * later ones fail to.
			 */
			per_cpu(xen_vcpu, cpu) = vcpup;
		पूर्ण
	पूर्ण

	अगर (!xen_have_vcpu_info_placement)
		xen_vcpu_info_reset(cpu);

	वापस ((per_cpu(xen_vcpu, cpu) == शून्य) ? -ENODEV : 0);
पूर्ण

व्योम xen_reboot(पूर्णांक reason)
अणु
	काष्ठा sched_shutकरोwn r = अणु .reason = reason पूर्ण;
	पूर्णांक cpu;

	क्रम_each_online_cpu(cpu)
		xen_pmu_finish(cpu);

	अगर (HYPERVISOR_sched_op(SCHEDOP_shutकरोwn, &r))
		BUG();
पूर्ण

अटल पूर्णांक reboot_reason = SHUTDOWN_reboot;
अटल bool xen_legacy_crash;
व्योम xen_emergency_restart(व्योम)
अणु
	xen_reboot(reboot_reason);
पूर्ण

अटल पूर्णांक
xen_panic_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	अगर (!kexec_crash_loaded()) अणु
		अगर (xen_legacy_crash)
			xen_reboot(SHUTDOWN_crash);

		reboot_reason = SHUTDOWN_crash;

		/*
		 * If panic_समयout==0 then we are supposed to रुको क्रमever.
		 * However, to preserve original करोm0 behavior we have to drop
		 * पूर्णांकo hypervisor. (करोmU behavior is controlled by its
		 * config file)
		 */
		अगर (panic_समयout == 0)
			panic_समयout = -1;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक __init parse_xen_legacy_crash(अक्षर *arg)
अणु
	xen_legacy_crash = true;
	वापस 0;
पूर्ण
early_param("xen_legacy_crash", parse_xen_legacy_crash);

अटल काष्ठा notअगरier_block xen_panic_block = अणु
	.notअगरier_call = xen_panic_event,
	.priority = पूर्णांक_न्यून
पूर्ण;

पूर्णांक xen_panic_handler_init(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list, &xen_panic_block);
	वापस 0;
पूर्ण

व्योम xen_pin_vcpu(पूर्णांक cpu)
अणु
	अटल bool disable_pinning;
	काष्ठा sched_pin_override pin_override;
	पूर्णांक ret;

	अगर (disable_pinning)
		वापस;

	pin_override.pcpu = cpu;
	ret = HYPERVISOR_sched_op(SCHEDOP_pin_override, &pin_override);

	/* Ignore errors when removing override. */
	अगर (cpu < 0)
		वापस;

	चयन (ret) अणु
	हाल -ENOSYS:
		pr_warn("Unable to pin on physical cpu %d. In case of problems consider vcpu pinning.\n",
			cpu);
		disable_pinning = true;
		अवरोध;
	हाल -EPERM:
		WARN(1, "Trying to pin vcpu without having privilege to do so\n");
		disable_pinning = true;
		अवरोध;
	हाल -EINVAL:
	हाल -EBUSY:
		pr_warn("Physical cpu %d not available for pinning. Check Xen cpu configuration.\n",
			cpu);
		अवरोध;
	हाल 0:
		अवरोध;
	शेष:
		WARN(1, "rc %d while trying to pin vcpu\n", ret);
		disable_pinning = true;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
व्योम xen_arch_रेजिस्टर_cpu(पूर्णांक num)
अणु
	arch_रेजिस्टर_cpu(num);
पूर्ण
EXPORT_SYMBOL(xen_arch_रेजिस्टर_cpu);

व्योम xen_arch_unरेजिस्टर_cpu(पूर्णांक num)
अणु
	arch_unरेजिस्टर_cpu(num);
पूर्ण
EXPORT_SYMBOL(xen_arch_unरेजिस्टर_cpu);
#पूर्ण_अगर
