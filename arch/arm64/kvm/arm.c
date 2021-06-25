<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/bug.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched.h>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_irqfd.h>
#समावेश <linux/irqbypass.h>
#समावेश <linux/sched/स्थिति.स>
#समावेश <linux/psci.h>
#समावेश <trace/events/kvm.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace_arm.h"

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/virt.h>
#समावेश <यंत्र/kvm_arm.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/sections.h>

#समावेश <kvm/arm_hypercalls.h>
#समावेश <kvm/arm_pmu.h>
#समावेश <kvm/arm_psci.h>

#अगर_घोषित REQUIRES_VIRT
__यंत्र__(".arch_extension	virt");
#पूर्ण_अगर

अटल क्रमागत kvm_mode kvm_mode = KVM_MODE_DEFAULT;
DEFINE_STATIC_KEY_FALSE(kvm_रक्षित_mode_initialized);

DECLARE_KVM_HYP_PER_CPU(अचिन्हित दीर्घ, kvm_hyp_vector);

अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, kvm_arm_hyp_stack_page);
अचिन्हित दीर्घ kvm_arm_hyp_percpu_base[NR_CPUS];
DECLARE_KVM_NVHE_PER_CPU(काष्ठा kvm_nvhe_init_params, kvm_init_params);

/* The VMID used in the VTTBR */
अटल atomic64_t kvm_vmid_gen = ATOMIC64_INIT(1);
अटल u32 kvm_next_vmid;
अटल DEFINE_SPINLOCK(kvm_vmid_lock);

अटल bool vgic_present;

अटल DEFINE_PER_CPU(अचिन्हित अक्षर, kvm_arm_hardware_enabled);
DEFINE_STATIC_KEY_FALSE(userspace_irqchip_in_use);

पूर्णांक kvm_arch_vcpu_should_kick(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_vcpu_निकासing_guest_mode(vcpu) == IN_GUEST_MODE;
पूर्ण

पूर्णांक kvm_arch_hardware_setup(व्योम *opaque)
अणु
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_check_processor_compat(व्योम *opaque)
अणु
	वापस 0;
पूर्ण

पूर्णांक kvm_vm_ioctl_enable_cap(काष्ठा kvm *kvm,
			    काष्ठा kvm_enable_cap *cap)
अणु
	पूर्णांक r;

	अगर (cap->flags)
		वापस -EINVAL;

	चयन (cap->cap) अणु
	हाल KVM_CAP_ARM_NISV_TO_USER:
		r = 0;
		kvm->arch.वापस_nisv_io_पात_to_user = true;
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक kvm_arm_शेष_max_vcpus(व्योम)
अणु
	वापस vgic_present ? kvm_vgic_get_max_vcpus() : KVM_MAX_VCPUS;
पूर्ण

अटल व्योम set_शेष_spectre(काष्ठा kvm *kvm)
अणु
	/*
	 * The शेष is to expose CSV2 == 1 अगर the HW isn't affected.
	 * Although this is a per-CPU feature, we make it global because
	 * asymmetric प्रणालीs are just a nuisance.
	 *
	 * Userspace can override this as दीर्घ as it करोesn't promise
	 * the impossible.
	 */
	अगर (arm64_get_spectre_v2_state() == SPECTRE_UNAFFECTED)
		kvm->arch.pfr0_csv2 = 1;
	अगर (arm64_get_meltकरोwn_state() == SPECTRE_UNAFFECTED)
		kvm->arch.pfr0_csv3 = 1;
पूर्ण

/**
 * kvm_arch_init_vm - initializes a VM data काष्ठाure
 * @kvm:	poपूर्णांकer to the KVM काष्ठा
 */
पूर्णांक kvm_arch_init_vm(काष्ठा kvm *kvm, अचिन्हित दीर्घ type)
अणु
	पूर्णांक ret;

	ret = kvm_arm_setup_stage2(kvm, type);
	अगर (ret)
		वापस ret;

	ret = kvm_init_stage2_mmu(kvm, &kvm->arch.mmu);
	अगर (ret)
		वापस ret;

	ret = create_hyp_mappings(kvm, kvm + 1, PAGE_HYP);
	अगर (ret)
		जाओ out_मुक्त_stage2_pgd;

	kvm_vgic_early_init(kvm);

	/* The maximum number of VCPUs is limited by the host's GIC model */
	kvm->arch.max_vcpus = kvm_arm_शेष_max_vcpus();

	set_शेष_spectre(kvm);

	वापस ret;
out_मुक्त_stage2_pgd:
	kvm_मुक्त_stage2_pgd(&kvm->arch.mmu);
	वापस ret;
पूर्ण

vm_fault_t kvm_arch_vcpu_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा vm_fault *vmf)
अणु
	वापस VM_FAULT_SIGBUS;
पूर्ण


/**
 * kvm_arch_destroy_vm - destroy the VM data काष्ठाure
 * @kvm:	poपूर्णांकer to the KVM काष्ठा
 */
व्योम kvm_arch_destroy_vm(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;

	biपंचांगap_मुक्त(kvm->arch.pmu_filter);

	kvm_vgic_destroy(kvm);

	क्रम (i = 0; i < KVM_MAX_VCPUS; ++i) अणु
		अगर (kvm->vcpus[i]) अणु
			kvm_vcpu_destroy(kvm->vcpus[i]);
			kvm->vcpus[i] = शून्य;
		पूर्ण
	पूर्ण
	atomic_set(&kvm->online_vcpus, 0);
पूर्ण

पूर्णांक kvm_vm_ioctl_check_extension(काष्ठा kvm *kvm, दीर्घ ext)
अणु
	पूर्णांक r;
	चयन (ext) अणु
	हाल KVM_CAP_IRQCHIP:
		r = vgic_present;
		अवरोध;
	हाल KVM_CAP_IOEVENTFD:
	हाल KVM_CAP_DEVICE_CTRL:
	हाल KVM_CAP_USER_MEMORY:
	हाल KVM_CAP_SYNC_MMU:
	हाल KVM_CAP_DESTROY_MEMORY_REGION_WORKS:
	हाल KVM_CAP_ONE_REG:
	हाल KVM_CAP_ARM_PSCI:
	हाल KVM_CAP_ARM_PSCI_0_2:
	हाल KVM_CAP_READONLY_MEM:
	हाल KVM_CAP_MP_STATE:
	हाल KVM_CAP_IMMEDIATE_EXIT:
	हाल KVM_CAP_VCPU_EVENTS:
	हाल KVM_CAP_ARM_IRQ_LINE_LAYOUT_2:
	हाल KVM_CAP_ARM_NISV_TO_USER:
	हाल KVM_CAP_ARM_INJECT_EXT_DABT:
	हाल KVM_CAP_SET_GUEST_DEBUG:
	हाल KVM_CAP_VCPU_ATTRIBUTES:
	हाल KVM_CAP_PTP_KVM:
		r = 1;
		अवरोध;
	हाल KVM_CAP_SET_GUEST_DEBUG2:
		वापस KVM_GUESTDBG_VALID_MASK;
	हाल KVM_CAP_ARM_SET_DEVICE_ADDR:
		r = 1;
		अवरोध;
	हाल KVM_CAP_NR_VCPUS:
		r = num_online_cpus();
		अवरोध;
	हाल KVM_CAP_MAX_VCPUS:
	हाल KVM_CAP_MAX_VCPU_ID:
		अगर (kvm)
			r = kvm->arch.max_vcpus;
		अन्यथा
			r = kvm_arm_शेष_max_vcpus();
		अवरोध;
	हाल KVM_CAP_MSI_DEVID:
		अगर (!kvm)
			r = -EINVAL;
		अन्यथा
			r = kvm->arch.vgic.msis_require_devid;
		अवरोध;
	हाल KVM_CAP_ARM_USER_IRQ:
		/*
		 * 1: EL1_VTIMER, EL1_PTIMER, and PMU.
		 * (bump this number अगर adding more devices)
		 */
		r = 1;
		अवरोध;
	हाल KVM_CAP_STEAL_TIME:
		r = kvm_arm_pvसमय_supported();
		अवरोध;
	हाल KVM_CAP_ARM_EL1_32BIT:
		r = cpus_have_स्थिर_cap(ARM64_HAS_32BIT_EL1);
		अवरोध;
	हाल KVM_CAP_GUEST_DEBUG_HW_BPS:
		r = get_num_brps();
		अवरोध;
	हाल KVM_CAP_GUEST_DEBUG_HW_WPS:
		r = get_num_wrps();
		अवरोध;
	हाल KVM_CAP_ARM_PMU_V3:
		r = kvm_arm_support_pmu_v3();
		अवरोध;
	हाल KVM_CAP_ARM_INJECT_SERROR_ESR:
		r = cpus_have_स्थिर_cap(ARM64_HAS_RAS_EXTN);
		अवरोध;
	हाल KVM_CAP_ARM_VM_IPA_SIZE:
		r = get_kvm_ipa_limit();
		अवरोध;
	हाल KVM_CAP_ARM_SVE:
		r = प्रणाली_supports_sve();
		अवरोध;
	हाल KVM_CAP_ARM_PTRAUTH_ADDRESS:
	हाल KVM_CAP_ARM_PTRAUTH_GENERIC:
		r = प्रणाली_has_full_ptr_auth();
		अवरोध;
	शेष:
		r = 0;
	पूर्ण

	वापस r;
पूर्ण

दीर्घ kvm_arch_dev_ioctl(काष्ठा file *filp,
			अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	वापस -EINVAL;
पूर्ण

काष्ठा kvm *kvm_arch_alloc_vm(व्योम)
अणु
	अगर (!has_vhe())
		वापस kzalloc(माप(काष्ठा kvm), GFP_KERNEL);

	वापस vzalloc(माप(काष्ठा kvm));
पूर्ण

व्योम kvm_arch_मुक्त_vm(काष्ठा kvm *kvm)
अणु
	अगर (!has_vhe())
		kमुक्त(kvm);
	अन्यथा
		vमुक्त(kvm);
पूर्ण

पूर्णांक kvm_arch_vcpu_precreate(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id)
अणु
	अगर (irqchip_in_kernel(kvm) && vgic_initialized(kvm))
		वापस -EBUSY;

	अगर (id >= kvm->arch.max_vcpus)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_create(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक err;

	/* Force users to call KVM_ARM_VCPU_INIT */
	vcpu->arch.target = -1;
	biपंचांगap_zero(vcpu->arch.features, KVM_VCPU_MAX_FEATURES);

	vcpu->arch.mmu_page_cache.gfp_zero = __GFP_ZERO;

	/* Set up the समयr */
	kvm_समयr_vcpu_init(vcpu);

	kvm_pmu_vcpu_init(vcpu);

	kvm_arm_reset_debug_ptr(vcpu);

	kvm_arm_pvसमय_vcpu_init(&vcpu->arch);

	vcpu->arch.hw_mmu = &vcpu->kvm->arch.mmu;

	err = kvm_vgic_vcpu_init(vcpu);
	अगर (err)
		वापस err;

	वापस create_hyp_mappings(vcpu, vcpu + 1, PAGE_HYP);
पूर्ण

व्योम kvm_arch_vcpu_postcreate(काष्ठा kvm_vcpu *vcpu)
अणु
पूर्ण

व्योम kvm_arch_vcpu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (vcpu->arch.has_run_once && unlikely(!irqchip_in_kernel(vcpu->kvm)))
		अटल_branch_dec(&userspace_irqchip_in_use);

	kvm_mmu_मुक्त_memory_cache(&vcpu->arch.mmu_page_cache);
	kvm_समयr_vcpu_terminate(vcpu);
	kvm_pmu_vcpu_destroy(vcpu);

	kvm_arm_vcpu_destroy(vcpu);
पूर्ण

पूर्णांक kvm_cpu_has_pending_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_समयr_is_pending(vcpu);
पूर्ण

व्योम kvm_arch_vcpu_blocking(काष्ठा kvm_vcpu *vcpu)
अणु
	/*
	 * If we're about to block (most likely because we've just hit a
	 * WFI), we need to sync back the state of the GIC CPU पूर्णांकerface
	 * so that we have the latest PMR and group enables. This ensures
	 * that kvm_arch_vcpu_runnable has up-to-date data to decide
	 * whether we have pending पूर्णांकerrupts.
	 *
	 * For the same reason, we want to tell GICv4 that we need
	 * करोorbells to be संकेतled, should an पूर्णांकerrupt become pending.
	 */
	preempt_disable();
	kvm_vgic_vmcr_sync(vcpu);
	vgic_v4_put(vcpu, true);
	preempt_enable();
पूर्ण

व्योम kvm_arch_vcpu_unblocking(काष्ठा kvm_vcpu *vcpu)
अणु
	preempt_disable();
	vgic_v4_load(vcpu);
	preempt_enable();
पूर्ण

व्योम kvm_arch_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
	काष्ठा kvm_s2_mmu *mmu;
	पूर्णांक *last_ran;

	mmu = vcpu->arch.hw_mmu;
	last_ran = this_cpu_ptr(mmu->last_vcpu_ran);

	/*
	 * We guarantee that both TLBs and I-cache are निजी to each
	 * vcpu. If detecting that a vcpu from the same VM has
	 * previously run on the same physical CPU, call पूर्णांकo the
	 * hypervisor code to nuke the relevant contexts.
	 *
	 * We might get preempted beक्रमe the vCPU actually runs, but
	 * over-invalidation करोesn't affect correctness.
	 */
	अगर (*last_ran != vcpu->vcpu_id) अणु
		kvm_call_hyp(__kvm_flush_cpu_context, mmu);
		*last_ran = vcpu->vcpu_id;
	पूर्ण

	vcpu->cpu = cpu;

	kvm_vgic_load(vcpu);
	kvm_समयr_vcpu_load(vcpu);
	अगर (has_vhe())
		kvm_vcpu_load_sysregs_vhe(vcpu);
	kvm_arch_vcpu_load_fp(vcpu);
	kvm_vcpu_pmu_restore_guest(vcpu);
	अगर (kvm_arm_is_pvसमय_enabled(&vcpu->arch))
		kvm_make_request(KVM_REQ_RECORD_STEAL, vcpu);

	अगर (single_task_running())
		vcpu_clear_wfx_traps(vcpu);
	अन्यथा
		vcpu_set_wfx_traps(vcpu);

	अगर (vcpu_has_ptrauth(vcpu))
		vcpu_ptrauth_disable(vcpu);
	kvm_arch_vcpu_load_debug_state_flags(vcpu);
पूर्ण

व्योम kvm_arch_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	kvm_arch_vcpu_put_debug_state_flags(vcpu);
	kvm_arch_vcpu_put_fp(vcpu);
	अगर (has_vhe())
		kvm_vcpu_put_sysregs_vhe(vcpu);
	kvm_समयr_vcpu_put(vcpu);
	kvm_vgic_put(vcpu);
	kvm_vcpu_pmu_restore_host(vcpu);

	vcpu->cpu = -1;
पूर्ण

अटल व्योम vcpu_घातer_off(काष्ठा kvm_vcpu *vcpu)
अणु
	vcpu->arch.घातer_off = true;
	kvm_make_request(KVM_REQ_SLEEP, vcpu);
	kvm_vcpu_kick(vcpu);
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state)
अणु
	अगर (vcpu->arch.घातer_off)
		mp_state->mp_state = KVM_MP_STATE_STOPPED;
	अन्यथा
		mp_state->mp_state = KVM_MP_STATE_RUNNABLE;

	वापस 0;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_mpstate(काष्ठा kvm_vcpu *vcpu,
				    काष्ठा kvm_mp_state *mp_state)
अणु
	पूर्णांक ret = 0;

	चयन (mp_state->mp_state) अणु
	हाल KVM_MP_STATE_RUNNABLE:
		vcpu->arch.घातer_off = false;
		अवरोध;
	हाल KVM_MP_STATE_STOPPED:
		vcpu_घातer_off(vcpu);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * kvm_arch_vcpu_runnable - determine अगर the vcpu can be scheduled
 * @v:		The VCPU poपूर्णांकer
 *
 * If the guest CPU is not रुकोing क्रम पूर्णांकerrupts or an पूर्णांकerrupt line is
 * निश्चितed, the CPU is by definition runnable.
 */
पूर्णांक kvm_arch_vcpu_runnable(काष्ठा kvm_vcpu *v)
अणु
	bool irq_lines = *vcpu_hcr(v) & (HCR_VI | HCR_VF);
	वापस ((irq_lines || kvm_vgic_vcpu_pending_irq(v))
		&& !v->arch.घातer_off && !v->arch.छोड़ो);
पूर्ण

bool kvm_arch_vcpu_in_kernel(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu_mode_priv(vcpu);
पूर्ण

/* Just ensure a guest निकास from a particular CPU */
अटल व्योम निकास_vm_noop(व्योम *info)
अणु
पूर्ण

व्योम क्रमce_vm_निकास(स्थिर cpumask_t *mask)
अणु
	preempt_disable();
	smp_call_function_many(mask, निकास_vm_noop, शून्य, true);
	preempt_enable();
पूर्ण

/**
 * need_new_vmid_gen - check that the VMID is still valid
 * @vmid: The VMID to check
 *
 * वापस true अगर there is a new generation of VMIDs being used
 *
 * The hardware supports a limited set of values with the value zero reserved
 * क्रम the host, so we check अगर an asचिन्हित value beदीर्घs to a previous
 * generation, which requires us to assign a new value. If we're the first to
 * use a VMID क्रम the new generation, we must flush necessary caches and TLBs
 * on all CPUs.
 */
अटल bool need_new_vmid_gen(काष्ठा kvm_vmid *vmid)
अणु
	u64 current_vmid_gen = atomic64_पढ़ो(&kvm_vmid_gen);
	smp_rmb(); /* Orders पढ़ो of kvm_vmid_gen and kvm->arch.vmid */
	वापस unlikely(READ_ONCE(vmid->vmid_gen) != current_vmid_gen);
पूर्ण

/**
 * update_vmid - Update the vmid with a valid VMID क्रम the current generation
 * @vmid: The stage-2 VMID inक्रमmation काष्ठा
 */
अटल व्योम update_vmid(काष्ठा kvm_vmid *vmid)
अणु
	अगर (!need_new_vmid_gen(vmid))
		वापस;

	spin_lock(&kvm_vmid_lock);

	/*
	 * We need to re-check the vmid_gen here to ensure that अगर another vcpu
	 * alपढ़ोy allocated a valid vmid क्रम this vm, then this vcpu should
	 * use the same vmid.
	 */
	अगर (!need_new_vmid_gen(vmid)) अणु
		spin_unlock(&kvm_vmid_lock);
		वापस;
	पूर्ण

	/* First user of a new VMID generation? */
	अगर (unlikely(kvm_next_vmid == 0)) अणु
		atomic64_inc(&kvm_vmid_gen);
		kvm_next_vmid = 1;

		/*
		 * On SMP we know no other CPUs can use this CPU's or each
		 * other's VMID after क्रमce_vm_निकास वापसs since the
		 * kvm_vmid_lock blocks them from reentry to the guest.
		 */
		क्रमce_vm_निकास(cpu_all_mask);
		/*
		 * Now broadcast TLB + ICACHE invalidation over the inner
		 * shareable करोमुख्य to make sure all data काष्ठाures are
		 * clean.
		 */
		kvm_call_hyp(__kvm_flush_vm_context);
	पूर्ण

	vmid->vmid = kvm_next_vmid;
	kvm_next_vmid++;
	kvm_next_vmid &= (1 << kvm_get_vmid_bits()) - 1;

	smp_wmb();
	WRITE_ONCE(vmid->vmid_gen, atomic64_पढ़ो(&kvm_vmid_gen));

	spin_unlock(&kvm_vmid_lock);
पूर्ण

अटल पूर्णांक kvm_vcpu_first_run_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	पूर्णांक ret = 0;

	अगर (likely(vcpu->arch.has_run_once))
		वापस 0;

	अगर (!kvm_arm_vcpu_is_finalized(vcpu))
		वापस -EPERM;

	vcpu->arch.has_run_once = true;

	kvm_arm_vcpu_init_debug(vcpu);

	अगर (likely(irqchip_in_kernel(kvm))) अणु
		/*
		 * Map the VGIC hardware resources beक्रमe running a vcpu the
		 * first समय on this VM.
		 */
		ret = kvm_vgic_map_resources(kvm);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/*
		 * Tell the rest of the code that there are userspace irqchip
		 * VMs in the wild.
		 */
		अटल_branch_inc(&userspace_irqchip_in_use);
	पूर्ण

	ret = kvm_समयr_enable(vcpu);
	अगर (ret)
		वापस ret;

	ret = kvm_arm_pmu_v3_enable(vcpu);

	वापस ret;
पूर्ण

bool kvm_arch_पूर्णांकc_initialized(काष्ठा kvm *kvm)
अणु
	वापस vgic_initialized(kvm);
पूर्ण

व्योम kvm_arm_halt_guest(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		vcpu->arch.छोड़ो = true;
	kvm_make_all_cpus_request(kvm, KVM_REQ_SLEEP);
पूर्ण

व्योम kvm_arm_resume_guest(काष्ठा kvm *kvm)
अणु
	पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		vcpu->arch.छोड़ो = false;
		rcuरुको_wake_up(kvm_arch_vcpu_get_रुको(vcpu));
	पूर्ण
पूर्ण

अटल व्योम vcpu_req_sleep(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा rcuरुको *रुको = kvm_arch_vcpu_get_रुको(vcpu);

	rcuरुको_रुको_event(रुको,
			   (!vcpu->arch.घातer_off) &&(!vcpu->arch.छोड़ो),
			   TASK_INTERRUPTIBLE);

	अगर (vcpu->arch.घातer_off || vcpu->arch.छोड़ो) अणु
		/* Awaken to handle a संकेत, request we sleep again later. */
		kvm_make_request(KVM_REQ_SLEEP, vcpu);
	पूर्ण

	/*
	 * Make sure we will observe a potential reset request अगर we've
	 * observed a change to the घातer state. Pairs with the smp_wmb() in
	 * kvm_psci_vcpu_on().
	 */
	smp_rmb();
पूर्ण

अटल पूर्णांक kvm_vcpu_initialized(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस vcpu->arch.target >= 0;
पूर्ण

अटल व्योम check_vcpu_requests(काष्ठा kvm_vcpu *vcpu)
अणु
	अगर (kvm_request_pending(vcpu)) अणु
		अगर (kvm_check_request(KVM_REQ_SLEEP, vcpu))
			vcpu_req_sleep(vcpu);

		अगर (kvm_check_request(KVM_REQ_VCPU_RESET, vcpu))
			kvm_reset_vcpu(vcpu);

		/*
		 * Clear IRQ_PENDING requests that were made to guarantee
		 * that a VCPU sees new भव पूर्णांकerrupts.
		 */
		kvm_check_request(KVM_REQ_IRQ_PENDING, vcpu);

		अगर (kvm_check_request(KVM_REQ_RECORD_STEAL, vcpu))
			kvm_update_stolen_समय(vcpu);

		अगर (kvm_check_request(KVM_REQ_RELOAD_GICv4, vcpu)) अणु
			/* The distributor enable bits were changed */
			preempt_disable();
			vgic_v4_put(vcpu, false);
			vgic_v4_load(vcpu);
			preempt_enable();
		पूर्ण
	पूर्ण
पूर्ण

/**
 * kvm_arch_vcpu_ioctl_run - the मुख्य VCPU run function to execute guest code
 * @vcpu:	The VCPU poपूर्णांकer
 *
 * This function is called through the VCPU_RUN ioctl called from user space. It
 * will execute VM code in a loop until the समय slice क्रम the process is used
 * or some emulation is needed from user space in which हाल the function will
 * वापस with वापस value 0 and with the kvm_run काष्ठाure filled in with the
 * required data क्रम the requested emulation.
 */
पूर्णांक kvm_arch_vcpu_ioctl_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक ret;

	अगर (unlikely(!kvm_vcpu_initialized(vcpu)))
		वापस -ENOEXEC;

	ret = kvm_vcpu_first_run_init(vcpu);
	अगर (ret)
		वापस ret;

	अगर (run->निकास_reason == KVM_EXIT_MMIO) अणु
		ret = kvm_handle_mmio_वापस(vcpu);
		अगर (ret)
			वापस ret;
	पूर्ण

	vcpu_load(vcpu);

	अगर (run->immediate_निकास) अणु
		ret = -EINTR;
		जाओ out;
	पूर्ण

	kvm_sigset_activate(vcpu);

	ret = 1;
	run->निकास_reason = KVM_EXIT_UNKNOWN;
	जबतक (ret > 0) अणु
		/*
		 * Check conditions beक्रमe entering the guest
		 */
		cond_resched();

		update_vmid(&vcpu->arch.hw_mmu->vmid);

		check_vcpu_requests(vcpu);

		/*
		 * Preparing the पूर्णांकerrupts to be injected also
		 * involves poking the GIC, which must be करोne in a
		 * non-preemptible context.
		 */
		preempt_disable();

		kvm_pmu_flush_hwstate(vcpu);

		local_irq_disable();

		kvm_vgic_flush_hwstate(vcpu);

		/*
		 * Exit अगर we have a संकेत pending so that we can deliver the
		 * संकेत to user space.
		 */
		अगर (संकेत_pending(current)) अणु
			ret = -EINTR;
			run->निकास_reason = KVM_EXIT_INTR;
		पूर्ण

		/*
		 * If we're using a userspace irqchip, then check अगर we need
		 * to tell a userspace irqchip about समयr or PMU level
		 * changes and अगर so, निकास to userspace (the actual level
		 * state माला_लो updated in kvm_समयr_update_run and
		 * kvm_pmu_update_run below).
		 */
		अगर (अटल_branch_unlikely(&userspace_irqchip_in_use)) अणु
			अगर (kvm_समयr_should_notअगरy_user(vcpu) ||
			    kvm_pmu_should_notअगरy_user(vcpu)) अणु
				ret = -EINTR;
				run->निकास_reason = KVM_EXIT_INTR;
			पूर्ण
		पूर्ण

		/*
		 * Ensure we set mode to IN_GUEST_MODE after we disable
		 * पूर्णांकerrupts and beक्रमe the final VCPU requests check.
		 * See the comment in kvm_vcpu_निकासing_guest_mode() and
		 * Documentation/virt/kvm/vcpu-requests.rst
		 */
		smp_store_mb(vcpu->mode, IN_GUEST_MODE);

		अगर (ret <= 0 || need_new_vmid_gen(&vcpu->arch.hw_mmu->vmid) ||
		    kvm_request_pending(vcpu)) अणु
			vcpu->mode = OUTSIDE_GUEST_MODE;
			isb(); /* Ensure work in x_flush_hwstate is committed */
			kvm_pmu_sync_hwstate(vcpu);
			अगर (अटल_branch_unlikely(&userspace_irqchip_in_use))
				kvm_समयr_sync_user(vcpu);
			kvm_vgic_sync_hwstate(vcpu);
			local_irq_enable();
			preempt_enable();
			जारी;
		पूर्ण

		kvm_arm_setup_debug(vcpu);

		/**************************************************************
		 * Enter the guest
		 */
		trace_kvm_entry(*vcpu_pc(vcpu));
		guest_enter_irqoff();

		ret = kvm_call_hyp_ret(__kvm_vcpu_run, vcpu);

		vcpu->mode = OUTSIDE_GUEST_MODE;
		vcpu->stat.निकासs++;
		/*
		 * Back from guest
		 *************************************************************/

		kvm_arm_clear_debug(vcpu);

		/*
		 * We must sync the PMU state beक्रमe the vgic state so
		 * that the vgic can properly sample the updated state of the
		 * पूर्णांकerrupt line.
		 */
		kvm_pmu_sync_hwstate(vcpu);

		/*
		 * Sync the vgic state beक्रमe syncing the समयr state because
		 * the समयr code needs to know अगर the भव समयr
		 * पूर्णांकerrupts are active.
		 */
		kvm_vgic_sync_hwstate(vcpu);

		/*
		 * Sync the समयr hardware state beक्रमe enabling पूर्णांकerrupts as
		 * we करोn't want vसमयr पूर्णांकerrupts to race with syncing the
		 * समयr भव पूर्णांकerrupt state.
		 */
		अगर (अटल_branch_unlikely(&userspace_irqchip_in_use))
			kvm_समयr_sync_user(vcpu);

		kvm_arch_vcpu_ctxsync_fp(vcpu);

		/*
		 * We may have taken a host पूर्णांकerrupt in HYP mode (ie
		 * जबतक executing the guest). This पूर्णांकerrupt is still
		 * pending, as we haven't serviced it yet!
		 *
		 * We're now back in SVC mode, with पूर्णांकerrupts
		 * disabled.  Enabling the पूर्णांकerrupts now will have
		 * the effect of taking the पूर्णांकerrupt again, in SVC
		 * mode this समय.
		 */
		local_irq_enable();

		/*
		 * We करो local_irq_enable() beक्रमe calling guest_निकास() so
		 * that अगर a समयr पूर्णांकerrupt hits जबतक running the guest we
		 * account that tick as being spent in the guest.  We enable
		 * preemption after calling guest_निकास() so that अगर we get
		 * preempted we make sure ticks after that is not counted as
		 * guest समय.
		 */
		guest_निकास();
		trace_kvm_निकास(ret, kvm_vcpu_trap_get_class(vcpu), *vcpu_pc(vcpu));

		/* Exit types that need handling beक्रमe we can be preempted */
		handle_निकास_early(vcpu, ret);

		preempt_enable();

		/*
		 * The ARMv8 architecture करोesn't give the hypervisor
		 * a mechanism to prevent a guest from dropping to AArch32 EL0
		 * अगर implemented by the CPU. If we spot the guest in such
		 * state and that we decided it wasn't supposed to करो so (like
		 * with the asymmetric AArch32 हाल), वापस to userspace with
		 * a fatal error.
		 */
		अगर (!प्रणाली_supports_32bit_el0() && vcpu_mode_is_32bit(vcpu)) अणु
			/*
			 * As we have caught the guest red-handed, decide that
			 * it isn't fit क्रम purpose anymore by making the vcpu
			 * invalid. The VMM can try and fix it by issuing  a
			 * KVM_ARM_VCPU_INIT अगर it really wants to.
			 */
			vcpu->arch.target = -1;
			ret = ARM_EXCEPTION_IL;
		पूर्ण

		ret = handle_निकास(vcpu, ret);
	पूर्ण

	/* Tell userspace about in-kernel device output levels */
	अगर (unlikely(!irqchip_in_kernel(vcpu->kvm))) अणु
		kvm_समयr_update_run(vcpu);
		kvm_pmu_update_run(vcpu);
	पूर्ण

	kvm_sigset_deactivate(vcpu);

out:
	/*
	 * In the unlikely event that we are वापसing to userspace
	 * with pending exceptions or PC adjusपंचांगent, commit these
	 * adjusपंचांगents in order to give userspace a consistent view of
	 * the vcpu state. Note that this relies on __kvm_adjust_pc()
	 * being preempt-safe on VHE.
	 */
	अगर (unlikely(vcpu->arch.flags & (KVM_ARM64_PENDING_EXCEPTION |
					 KVM_ARM64_INCREMENT_PC)))
		kvm_call_hyp(__kvm_adjust_pc, vcpu);

	vcpu_put(vcpu);
	वापस ret;
पूर्ण

अटल पूर्णांक vcpu_पूर्णांकerrupt_line(काष्ठा kvm_vcpu *vcpu, पूर्णांक number, bool level)
अणु
	पूर्णांक bit_index;
	bool set;
	अचिन्हित दीर्घ *hcr;

	अगर (number == KVM_ARM_IRQ_CPU_IRQ)
		bit_index = __ffs(HCR_VI);
	अन्यथा /* KVM_ARM_IRQ_CPU_FIQ */
		bit_index = __ffs(HCR_VF);

	hcr = vcpu_hcr(vcpu);
	अगर (level)
		set = test_and_set_bit(bit_index, hcr);
	अन्यथा
		set = test_and_clear_bit(bit_index, hcr);

	/*
	 * If we didn't change anything, no need to wake up or kick other CPUs
	 */
	अगर (set == level)
		वापस 0;

	/*
	 * The vcpu irq_lines field was updated, wake up sleeping VCPUs and
	 * trigger a world-चयन round on the running physical CPU to set the
	 * भव IRQ/FIQ fields in the HCR appropriately.
	 */
	kvm_make_request(KVM_REQ_IRQ_PENDING, vcpu);
	kvm_vcpu_kick(vcpu);

	वापस 0;
पूर्ण

पूर्णांक kvm_vm_ioctl_irq_line(काष्ठा kvm *kvm, काष्ठा kvm_irq_level *irq_level,
			  bool line_status)
अणु
	u32 irq = irq_level->irq;
	अचिन्हित पूर्णांक irq_type, vcpu_idx, irq_num;
	पूर्णांक nrcpus = atomic_पढ़ो(&kvm->online_vcpus);
	काष्ठा kvm_vcpu *vcpu = शून्य;
	bool level = irq_level->level;

	irq_type = (irq >> KVM_ARM_IRQ_TYPE_SHIFT) & KVM_ARM_IRQ_TYPE_MASK;
	vcpu_idx = (irq >> KVM_ARM_IRQ_VCPU_SHIFT) & KVM_ARM_IRQ_VCPU_MASK;
	vcpu_idx += ((irq >> KVM_ARM_IRQ_VCPU2_SHIFT) & KVM_ARM_IRQ_VCPU2_MASK) * (KVM_ARM_IRQ_VCPU_MASK + 1);
	irq_num = (irq >> KVM_ARM_IRQ_NUM_SHIFT) & KVM_ARM_IRQ_NUM_MASK;

	trace_kvm_irq_line(irq_type, vcpu_idx, irq_num, irq_level->level);

	चयन (irq_type) अणु
	हाल KVM_ARM_IRQ_TYPE_CPU:
		अगर (irqchip_in_kernel(kvm))
			वापस -ENXIO;

		अगर (vcpu_idx >= nrcpus)
			वापस -EINVAL;

		vcpu = kvm_get_vcpu(kvm, vcpu_idx);
		अगर (!vcpu)
			वापस -EINVAL;

		अगर (irq_num > KVM_ARM_IRQ_CPU_FIQ)
			वापस -EINVAL;

		वापस vcpu_पूर्णांकerrupt_line(vcpu, irq_num, level);
	हाल KVM_ARM_IRQ_TYPE_PPI:
		अगर (!irqchip_in_kernel(kvm))
			वापस -ENXIO;

		अगर (vcpu_idx >= nrcpus)
			वापस -EINVAL;

		vcpu = kvm_get_vcpu(kvm, vcpu_idx);
		अगर (!vcpu)
			वापस -EINVAL;

		अगर (irq_num < VGIC_NR_SGIS || irq_num >= VGIC_NR_PRIVATE_IRQS)
			वापस -EINVAL;

		वापस kvm_vgic_inject_irq(kvm, vcpu->vcpu_id, irq_num, level, शून्य);
	हाल KVM_ARM_IRQ_TYPE_SPI:
		अगर (!irqchip_in_kernel(kvm))
			वापस -ENXIO;

		अगर (irq_num < VGIC_NR_PRIVATE_IRQS)
			वापस -EINVAL;

		वापस kvm_vgic_inject_irq(kvm, 0, irq_num, level, शून्य);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kvm_vcpu_set_target(काष्ठा kvm_vcpu *vcpu,
			       स्थिर काष्ठा kvm_vcpu_init *init)
अणु
	अचिन्हित पूर्णांक i, ret;
	पूर्णांक phys_target = kvm_target_cpu();

	अगर (init->target != phys_target)
		वापस -EINVAL;

	/*
	 * Secondary and subsequent calls to KVM_ARM_VCPU_INIT must
	 * use the same target.
	 */
	अगर (vcpu->arch.target != -1 && vcpu->arch.target != init->target)
		वापस -EINVAL;

	/* -ENOENT क्रम unknown features, -EINVAL क्रम invalid combinations. */
	क्रम (i = 0; i < माप(init->features) * 8; i++) अणु
		bool set = (init->features[i / 32] & (1 << (i % 32)));

		अगर (set && i >= KVM_VCPU_MAX_FEATURES)
			वापस -ENOENT;

		/*
		 * Secondary and subsequent calls to KVM_ARM_VCPU_INIT must
		 * use the same feature set.
		 */
		अगर (vcpu->arch.target != -1 && i < KVM_VCPU_MAX_FEATURES &&
		    test_bit(i, vcpu->arch.features) != set)
			वापस -EINVAL;

		अगर (set)
			set_bit(i, vcpu->arch.features);
	पूर्ण

	vcpu->arch.target = phys_target;

	/* Now we know what it is, we can reset it. */
	ret = kvm_reset_vcpu(vcpu);
	अगर (ret) अणु
		vcpu->arch.target = -1;
		biपंचांगap_zero(vcpu->arch.features, KVM_VCPU_MAX_FEATURES);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_arch_vcpu_ioctl_vcpu_init(काष्ठा kvm_vcpu *vcpu,
					 काष्ठा kvm_vcpu_init *init)
अणु
	पूर्णांक ret;

	ret = kvm_vcpu_set_target(vcpu, init);
	अगर (ret)
		वापस ret;

	/*
	 * Ensure a rebooted VM will fault in RAM pages and detect अगर the
	 * guest MMU is turned off and flush the caches as needed.
	 *
	 * S2FWB enक्रमces all memory accesses to RAM being cacheable,
	 * ensuring that the data side is always coherent. We still
	 * need to invalidate the I-cache though, as FWB करोes *not*
	 * imply CTR_EL0.DIC.
	 */
	अगर (vcpu->arch.has_run_once) अणु
		अगर (!cpus_have_final_cap(ARM64_HAS_STAGE2_FWB))
			stage2_unmap_vm(vcpu->kvm);
		अन्यथा
			__flush_icache_all();
	पूर्ण

	vcpu_reset_hcr(vcpu);

	/*
	 * Handle the "start in power-off" हाल.
	 */
	अगर (test_bit(KVM_ARM_VCPU_POWER_OFF, vcpu->arch.features))
		vcpu_घातer_off(vcpu);
	अन्यथा
		vcpu->arch.घातer_off = false;

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_arm_vcpu_set_attr(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret = -ENXIO;

	चयन (attr->group) अणु
	शेष:
		ret = kvm_arm_vcpu_arch_set_attr(vcpu, attr);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_arm_vcpu_get_attr(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret = -ENXIO;

	चयन (attr->group) अणु
	शेष:
		ret = kvm_arm_vcpu_arch_get_attr(vcpu, attr);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_arm_vcpu_has_attr(काष्ठा kvm_vcpu *vcpu,
				 काष्ठा kvm_device_attr *attr)
अणु
	पूर्णांक ret = -ENXIO;

	चयन (attr->group) अणु
	शेष:
		ret = kvm_arm_vcpu_arch_has_attr(vcpu, attr);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_arm_vcpu_get_events(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा kvm_vcpu_events *events)
अणु
	स_रखो(events, 0, माप(*events));

	वापस __kvm_arm_vcpu_get_events(vcpu, events);
पूर्ण

अटल पूर्णांक kvm_arm_vcpu_set_events(काष्ठा kvm_vcpu *vcpu,
				   काष्ठा kvm_vcpu_events *events)
अणु
	पूर्णांक i;

	/* check whether the reserved field is zero */
	क्रम (i = 0; i < ARRAY_SIZE(events->reserved); i++)
		अगर (events->reserved[i])
			वापस -EINVAL;

	/* check whether the pad field is zero */
	क्रम (i = 0; i < ARRAY_SIZE(events->exception.pad); i++)
		अगर (events->exception.pad[i])
			वापस -EINVAL;

	वापस __kvm_arm_vcpu_set_events(vcpu, events);
पूर्ण

दीर्घ kvm_arch_vcpu_ioctl(काष्ठा file *filp,
			 अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा kvm_device_attr attr;
	दीर्घ r;

	चयन (ioctl) अणु
	हाल KVM_ARM_VCPU_INIT: अणु
		काष्ठा kvm_vcpu_init init;

		r = -EFAULT;
		अगर (copy_from_user(&init, argp, माप(init)))
			अवरोध;

		r = kvm_arch_vcpu_ioctl_vcpu_init(vcpu, &init);
		अवरोध;
	पूर्ण
	हाल KVM_SET_ONE_REG:
	हाल KVM_GET_ONE_REG: अणु
		काष्ठा kvm_one_reg reg;

		r = -ENOEXEC;
		अगर (unlikely(!kvm_vcpu_initialized(vcpu)))
			अवरोध;

		r = -EFAULT;
		अगर (copy_from_user(&reg, argp, माप(reg)))
			अवरोध;

		अगर (ioctl == KVM_SET_ONE_REG)
			r = kvm_arm_set_reg(vcpu, &reg);
		अन्यथा
			r = kvm_arm_get_reg(vcpu, &reg);
		अवरोध;
	पूर्ण
	हाल KVM_GET_REG_LIST: अणु
		काष्ठा kvm_reg_list __user *user_list = argp;
		काष्ठा kvm_reg_list reg_list;
		अचिन्हित n;

		r = -ENOEXEC;
		अगर (unlikely(!kvm_vcpu_initialized(vcpu)))
			अवरोध;

		r = -EPERM;
		अगर (!kvm_arm_vcpu_is_finalized(vcpu))
			अवरोध;

		r = -EFAULT;
		अगर (copy_from_user(&reg_list, user_list, माप(reg_list)))
			अवरोध;
		n = reg_list.n;
		reg_list.n = kvm_arm_num_regs(vcpu);
		अगर (copy_to_user(user_list, &reg_list, माप(reg_list)))
			अवरोध;
		r = -E2BIG;
		अगर (n < reg_list.n)
			अवरोध;
		r = kvm_arm_copy_reg_indices(vcpu, user_list->reg);
		अवरोध;
	पूर्ण
	हाल KVM_SET_DEVICE_ATTR: अणु
		r = -EFAULT;
		अगर (copy_from_user(&attr, argp, माप(attr)))
			अवरोध;
		r = kvm_arm_vcpu_set_attr(vcpu, &attr);
		अवरोध;
	पूर्ण
	हाल KVM_GET_DEVICE_ATTR: अणु
		r = -EFAULT;
		अगर (copy_from_user(&attr, argp, माप(attr)))
			अवरोध;
		r = kvm_arm_vcpu_get_attr(vcpu, &attr);
		अवरोध;
	पूर्ण
	हाल KVM_HAS_DEVICE_ATTR: अणु
		r = -EFAULT;
		अगर (copy_from_user(&attr, argp, माप(attr)))
			अवरोध;
		r = kvm_arm_vcpu_has_attr(vcpu, &attr);
		अवरोध;
	पूर्ण
	हाल KVM_GET_VCPU_EVENTS: अणु
		काष्ठा kvm_vcpu_events events;

		अगर (kvm_arm_vcpu_get_events(vcpu, &events))
			वापस -EINVAL;

		अगर (copy_to_user(argp, &events, माप(events)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	हाल KVM_SET_VCPU_EVENTS: अणु
		काष्ठा kvm_vcpu_events events;

		अगर (copy_from_user(&events, argp, माप(events)))
			वापस -EFAULT;

		वापस kvm_arm_vcpu_set_events(vcpu, &events);
	पूर्ण
	हाल KVM_ARM_VCPU_FINALIZE: अणु
		पूर्णांक what;

		अगर (!kvm_vcpu_initialized(vcpu))
			वापस -ENOEXEC;

		अगर (get_user(what, (स्थिर पूर्णांक __user *)argp))
			वापस -EFAULT;

		वापस kvm_arm_vcpu_finalize(vcpu, what);
	पूर्ण
	शेष:
		r = -EINVAL;
	पूर्ण

	वापस r;
पूर्ण

व्योम kvm_arch_sync_dirty_log(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot)
अणु

पूर्ण

व्योम kvm_arch_flush_remote_tlbs_memslot(काष्ठा kvm *kvm,
					स्थिर काष्ठा kvm_memory_slot *memslot)
अणु
	kvm_flush_remote_tlbs(kvm);
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_set_device_addr(काष्ठा kvm *kvm,
					काष्ठा kvm_arm_device_addr *dev_addr)
अणु
	अचिन्हित दीर्घ dev_id, type;

	dev_id = (dev_addr->id & KVM_ARM_DEVICE_ID_MASK) >>
		KVM_ARM_DEVICE_ID_SHIFT;
	type = (dev_addr->id & KVM_ARM_DEVICE_TYPE_MASK) >>
		KVM_ARM_DEVICE_TYPE_SHIFT;

	चयन (dev_id) अणु
	हाल KVM_ARM_DEVICE_VGIC_V2:
		अगर (!vgic_present)
			वापस -ENXIO;
		वापस kvm_vgic_addr(kvm, type, &dev_addr->addr, true);
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

दीर्घ kvm_arch_vm_ioctl(काष्ठा file *filp,
		       अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm *kvm = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;

	चयन (ioctl) अणु
	हाल KVM_CREATE_IRQCHIP: अणु
		पूर्णांक ret;
		अगर (!vgic_present)
			वापस -ENXIO;
		mutex_lock(&kvm->lock);
		ret = kvm_vgic_create(kvm, KVM_DEV_TYPE_ARM_VGIC_V2);
		mutex_unlock(&kvm->lock);
		वापस ret;
	पूर्ण
	हाल KVM_ARM_SET_DEVICE_ADDR: अणु
		काष्ठा kvm_arm_device_addr dev_addr;

		अगर (copy_from_user(&dev_addr, argp, माप(dev_addr)))
			वापस -EFAULT;
		वापस kvm_vm_ioctl_set_device_addr(kvm, &dev_addr);
	पूर्ण
	हाल KVM_ARM_PREFERRED_TARGET: अणु
		पूर्णांक err;
		काष्ठा kvm_vcpu_init init;

		err = kvm_vcpu_preferred_target(&init);
		अगर (err)
			वापस err;

		अगर (copy_to_user(argp, &init, माप(init)))
			वापस -EFAULT;

		वापस 0;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ nvhe_percpu_size(व्योम)
अणु
	वापस (अचिन्हित दीर्घ)CHOOSE_NVHE_SYM(__per_cpu_end) -
		(अचिन्हित दीर्घ)CHOOSE_NVHE_SYM(__per_cpu_start);
पूर्ण

अटल अचिन्हित दीर्घ nvhe_percpu_order(व्योम)
अणु
	अचिन्हित दीर्घ size = nvhe_percpu_size();

	वापस size ? get_order(size) : 0;
पूर्ण

/* A lookup table holding the hypervisor VA क्रम each vector slot */
अटल व्योम *hyp_spectre_vector_selector[BP_HARDEN_EL2_SLOTS];

अटल व्योम kvm_init_vector_slot(व्योम *base, क्रमागत arm64_hyp_spectre_vector slot)
अणु
	hyp_spectre_vector_selector[slot] = __kvm_vector_slot2addr(base, slot);
पूर्ण

अटल पूर्णांक kvm_init_vector_slots(व्योम)
अणु
	पूर्णांक err;
	व्योम *base;

	base = kern_hyp_va(kvm_ksym_ref(__kvm_hyp_vector));
	kvm_init_vector_slot(base, HYP_VECTOR_सूचीECT);

	base = kern_hyp_va(kvm_ksym_ref(__bp_harden_hyp_vecs));
	kvm_init_vector_slot(base, HYP_VECTOR_SPECTRE_सूचीECT);

	अगर (!cpus_have_स्थिर_cap(ARM64_SPECTRE_V3A))
		वापस 0;

	अगर (!has_vhe()) अणु
		err = create_hyp_exec_mappings(__pa_symbol(__bp_harden_hyp_vecs),
					       __BP_HARDEN_HYP_VECS_SZ, &base);
		अगर (err)
			वापस err;
	पूर्ण

	kvm_init_vector_slot(base, HYP_VECTOR_INसूचीECT);
	kvm_init_vector_slot(base, HYP_VECTOR_SPECTRE_INसूचीECT);
	वापस 0;
पूर्ण

अटल व्योम cpu_prepare_hyp_mode(पूर्णांक cpu)
अणु
	काष्ठा kvm_nvhe_init_params *params = per_cpu_ptr_nvhe_sym(kvm_init_params, cpu);
	अचिन्हित दीर्घ tcr;

	/*
	 * Calculate the raw per-cpu offset without a translation from the
	 * kernel's mapping to the linear mapping, and store it in tpidr_el2
	 * so that we can use adr_l to access per-cpu variables in EL2.
	 * Also drop the KASAN tag which माला_लो in the way...
	 */
	params->tpidr_el2 = (अचिन्हित दीर्घ)kasan_reset_tag(per_cpu_ptr_nvhe_sym(__per_cpu_start, cpu)) -
			    (अचिन्हित दीर्घ)kvm_ksym_ref(CHOOSE_NVHE_SYM(__per_cpu_start));

	params->mair_el2 = पढ़ो_sysreg(mair_el1);

	/*
	 * The ID map may be configured to use an extended भव address
	 * range. This is only the हाल अगर प्रणाली RAM is out of range क्रम the
	 * currently configured page size and VA_BITS, in which हाल we will
	 * also need the extended भव range क्रम the HYP ID map, or we won't
	 * be able to enable the EL2 MMU.
	 *
	 * However, at EL2, there is only one TTBR रेजिस्टर, and we can't चयन
	 * between translation tables *and* update TCR_EL2.T0SZ at the same
	 * समय. Bottom line: we need to use the extended range with *both* our
	 * translation tables.
	 *
	 * So use the same T0SZ value we use क्रम the ID map.
	 */
	tcr = (पढ़ो_sysreg(tcr_el1) & TCR_EL2_MASK) | TCR_EL2_RES1;
	tcr &= ~TCR_T0SZ_MASK;
	tcr |= (idmap_t0sz & GENMASK(TCR_TxSZ_WIDTH - 1, 0)) << TCR_T0SZ_OFFSET;
	params->tcr_el2 = tcr;

	params->stack_hyp_va = kern_hyp_va(per_cpu(kvm_arm_hyp_stack_page, cpu) + PAGE_SIZE);
	params->pgd_pa = kvm_mmu_get_httbr();
	अगर (is_रक्षित_kvm_enabled())
		params->hcr_el2 = HCR_HOST_NVHE_PROTECTED_FLAGS;
	अन्यथा
		params->hcr_el2 = HCR_HOST_NVHE_FLAGS;
	params->vttbr = params->vtcr = 0;

	/*
	 * Flush the init params from the data cache because the काष्ठा will
	 * be पढ़ो जबतक the MMU is off.
	 */
	kvm_flush_dcache_to_poc(params, माप(*params));
पूर्ण

अटल व्योम hyp_install_host_vector(व्योम)
अणु
	काष्ठा kvm_nvhe_init_params *params;
	काष्ठा arm_smccc_res res;

	/* Switch from the HYP stub to our own HYP init vector */
	__hyp_set_vectors(kvm_get_idmap_vector());

	/*
	 * Call initialization code, and चयन to the full blown HYP code.
	 * If the cpucaps haven't been finalized yet, something has gone very
	 * wrong, and hyp will crash and burn when it uses any
	 * cpus_have_स्थिर_cap() wrapper.
	 */
	BUG_ON(!प्रणाली_capabilities_finalized());
	params = this_cpu_ptr_nvhe_sym(kvm_init_params);
	arm_smccc_1_1_hvc(KVM_HOST_SMCCC_FUNC(__kvm_hyp_init), virt_to_phys(params), &res);
	WARN_ON(res.a0 != SMCCC_RET_SUCCESS);
पूर्ण

अटल व्योम cpu_init_hyp_mode(व्योम)
अणु
	hyp_install_host_vector();

	/*
	 * Disabling SSBD on a non-VHE प्रणाली requires us to enable SSBS
	 * at EL2.
	 */
	अगर (this_cpu_has_cap(ARM64_SSBS) &&
	    arm64_get_spectre_v4_state() == SPECTRE_VULNERABLE) अणु
		kvm_call_hyp_nvhe(__kvm_enable_ssbs);
	पूर्ण
पूर्ण

अटल व्योम cpu_hyp_reset(व्योम)
अणु
	अगर (!is_kernel_in_hyp_mode())
		__hyp_reset_vectors();
पूर्ण

/*
 * EL2 vectors can be mapped and rerouted in a number of ways,
 * depending on the kernel configuration and CPU present:
 *
 * - If the CPU is affected by Spectre-v2, the hardening sequence is
 *   placed in one of the vector slots, which is executed beक्रमe jumping
 *   to the real vectors.
 *
 * - If the CPU also has the ARM64_SPECTRE_V3A cap, the slot
 *   containing the hardening sequence is mapped next to the idmap page,
 *   and executed beक्रमe jumping to the real vectors.
 *
 * - If the CPU only has the ARM64_SPECTRE_V3A cap, then an
 *   empty slot is selected, mapped next to the idmap page, and
 *   executed beक्रमe jumping to the real vectors.
 *
 * Note that ARM64_SPECTRE_V3A is somewhat incompatible with
 * VHE, as we करोn't have hypervisor-specअगरic mappings. If the प्रणाली
 * is VHE and yet selects this capability, it will be ignored.
 */
अटल व्योम cpu_set_hyp_vector(व्योम)
अणु
	काष्ठा bp_hardening_data *data = this_cpu_ptr(&bp_hardening_data);
	व्योम *vector = hyp_spectre_vector_selector[data->slot];

	अगर (!is_रक्षित_kvm_enabled())
		*this_cpu_ptr_hyp_sym(kvm_hyp_vector) = (अचिन्हित दीर्घ)vector;
	अन्यथा
		kvm_call_hyp_nvhe(__pkvm_cpu_set_vector, data->slot);
पूर्ण

अटल व्योम cpu_hyp_reinit(व्योम)
अणु
	kvm_init_host_cpu_context(&this_cpu_ptr_hyp_sym(kvm_host_data)->host_ctxt);

	cpu_hyp_reset();

	अगर (is_kernel_in_hyp_mode())
		kvm_समयr_init_vhe();
	अन्यथा
		cpu_init_hyp_mode();

	cpu_set_hyp_vector();

	kvm_arm_init_debug();

	अगर (vgic_present)
		kvm_vgic_init_cpu_hardware();
पूर्ण

अटल व्योम _kvm_arch_hardware_enable(व्योम *discard)
अणु
	अगर (!__this_cpu_पढ़ो(kvm_arm_hardware_enabled)) अणु
		cpu_hyp_reinit();
		__this_cpu_ग_लिखो(kvm_arm_hardware_enabled, 1);
	पूर्ण
पूर्ण

पूर्णांक kvm_arch_hardware_enable(व्योम)
अणु
	_kvm_arch_hardware_enable(शून्य);
	वापस 0;
पूर्ण

अटल व्योम _kvm_arch_hardware_disable(व्योम *discard)
अणु
	अगर (__this_cpu_पढ़ो(kvm_arm_hardware_enabled)) अणु
		cpu_hyp_reset();
		__this_cpu_ग_लिखो(kvm_arm_hardware_enabled, 0);
	पूर्ण
पूर्ण

व्योम kvm_arch_hardware_disable(व्योम)
अणु
	अगर (!is_रक्षित_kvm_enabled())
		_kvm_arch_hardware_disable(शून्य);
पूर्ण

#अगर_घोषित CONFIG_CPU_PM
अटल पूर्णांक hyp_init_cpu_pm_notअगरier(काष्ठा notअगरier_block *self,
				    अचिन्हित दीर्घ cmd,
				    व्योम *v)
अणु
	/*
	 * kvm_arm_hardware_enabled is left with its old value over
	 * PM_ENTER->PM_EXIT. It is used to indicate PM_EXIT should
	 * re-enable hyp.
	 */
	चयन (cmd) अणु
	हाल CPU_PM_ENTER:
		अगर (__this_cpu_पढ़ो(kvm_arm_hardware_enabled))
			/*
			 * करोn't update kvm_arm_hardware_enabled here
			 * so that the hardware will be re-enabled
			 * when we resume. See below.
			 */
			cpu_hyp_reset();

		वापस NOTIFY_OK;
	हाल CPU_PM_ENTER_FAILED:
	हाल CPU_PM_EXIT:
		अगर (__this_cpu_पढ़ो(kvm_arm_hardware_enabled))
			/* The hardware was enabled beक्रमe suspend. */
			cpu_hyp_reinit();

		वापस NOTIFY_OK;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block hyp_init_cpu_pm_nb = अणु
	.notअगरier_call = hyp_init_cpu_pm_notअगरier,
पूर्ण;

अटल व्योम hyp_cpu_pm_init(व्योम)
अणु
	अगर (!is_रक्षित_kvm_enabled())
		cpu_pm_रेजिस्टर_notअगरier(&hyp_init_cpu_pm_nb);
पूर्ण
अटल व्योम hyp_cpu_pm_निकास(व्योम)
अणु
	अगर (!is_रक्षित_kvm_enabled())
		cpu_pm_unरेजिस्टर_notअगरier(&hyp_init_cpu_pm_nb);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम hyp_cpu_pm_init(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम hyp_cpu_pm_निकास(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम init_cpu_logical_map(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	/*
	 * Copy the MPIDR <-> logical CPU ID mapping to hyp.
	 * Only copy the set of online CPUs whose features have been chacked
	 * against the finalized प्रणाली capabilities. The hypervisor will not
	 * allow any other CPUs from the `possible` set to boot.
	 */
	क्रम_each_online_cpu(cpu)
		hyp_cpu_logical_map[cpu] = cpu_logical_map(cpu);
पूर्ण

#घोषणा init_psci_0_1_impl_state(config, what)	\
	config.psci_0_1_ ## what ## _implemented = psci_ops.what

अटल bool init_psci_relay(व्योम)
अणु
	/*
	 * If PSCI has not been initialized, रक्षित KVM cannot install
	 * itself on newly booted CPUs.
	 */
	अगर (!psci_ops.get_version) अणु
		kvm_err("Cannot initialize protected mode without PSCI\n");
		वापस false;
	पूर्ण

	kvm_host_psci_config.version = psci_ops.get_version();

	अगर (kvm_host_psci_config.version == PSCI_VERSION(0, 1)) अणु
		kvm_host_psci_config.function_ids_0_1 = get_psci_0_1_function_ids();
		init_psci_0_1_impl_state(kvm_host_psci_config, cpu_suspend);
		init_psci_0_1_impl_state(kvm_host_psci_config, cpu_on);
		init_psci_0_1_impl_state(kvm_host_psci_config, cpu_off);
		init_psci_0_1_impl_state(kvm_host_psci_config, migrate);
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक init_common_resources(व्योम)
अणु
	वापस kvm_set_ipa_limit();
पूर्ण

अटल पूर्णांक init_subप्रणालीs(व्योम)
अणु
	पूर्णांक err = 0;

	/*
	 * Enable hardware so that subप्रणाली initialisation can access EL2.
	 */
	on_each_cpu(_kvm_arch_hardware_enable, शून्य, 1);

	/*
	 * Register CPU lower-घातer notअगरier
	 */
	hyp_cpu_pm_init();

	/*
	 * Init HYP view of VGIC
	 */
	err = kvm_vgic_hyp_init();
	चयन (err) अणु
	हाल 0:
		vgic_present = true;
		अवरोध;
	हाल -ENODEV:
	हाल -ENXIO:
		vgic_present = false;
		err = 0;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	/*
	 * Init HYP architected समयr support
	 */
	err = kvm_समयr_hyp_init(vgic_present);
	अगर (err)
		जाओ out;

	kvm_perf_init();
	kvm_sys_reg_table_init();

out:
	अगर (err || !is_रक्षित_kvm_enabled())
		on_each_cpu(_kvm_arch_hardware_disable, शून्य, 1);

	वापस err;
पूर्ण

अटल व्योम tearकरोwn_hyp_mode(व्योम)
अणु
	पूर्णांक cpu;

	मुक्त_hyp_pgds();
	क्रम_each_possible_cpu(cpu) अणु
		मुक्त_page(per_cpu(kvm_arm_hyp_stack_page, cpu));
		मुक्त_pages(kvm_arm_hyp_percpu_base[cpu], nvhe_percpu_order());
	पूर्ण
पूर्ण

अटल पूर्णांक करो_pkvm_init(u32 hyp_va_bits)
अणु
	व्योम *per_cpu_base = kvm_ksym_ref(kvm_arm_hyp_percpu_base);
	पूर्णांक ret;

	preempt_disable();
	hyp_install_host_vector();
	ret = kvm_call_hyp_nvhe(__pkvm_init, hyp_mem_base, hyp_mem_size,
				num_possible_cpus(), kern_hyp_va(per_cpu_base),
				hyp_va_bits);
	preempt_enable();

	वापस ret;
पूर्ण

अटल पूर्णांक kvm_hyp_init_protection(u32 hyp_va_bits)
अणु
	व्योम *addr = phys_to_virt(hyp_mem_base);
	पूर्णांक ret;

	kvm_nvhe_sym(id_aa64mmfr0_el1_sys_val) = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1);
	kvm_nvhe_sym(id_aa64mmfr1_el1_sys_val) = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR1_EL1);

	ret = create_hyp_mappings(addr, addr + hyp_mem_size, PAGE_HYP);
	अगर (ret)
		वापस ret;

	ret = करो_pkvm_init(hyp_va_bits);
	अगर (ret)
		वापस ret;

	मुक्त_hyp_pgds();

	वापस 0;
पूर्ण

/**
 * Inits Hyp-mode on all online CPUs
 */
अटल पूर्णांक init_hyp_mode(व्योम)
अणु
	u32 hyp_va_bits;
	पूर्णांक cpu;
	पूर्णांक err = -ENOMEM;

	/*
	 * The रक्षित Hyp-mode cannot be initialized अगर the memory pool
	 * allocation has failed.
	 */
	अगर (is_रक्षित_kvm_enabled() && !hyp_mem_base)
		जाओ out_err;

	/*
	 * Allocate Hyp PGD and setup Hyp identity mapping
	 */
	err = kvm_mmu_init(&hyp_va_bits);
	अगर (err)
		जाओ out_err;

	/*
	 * Allocate stack pages क्रम Hypervisor-mode
	 */
	क्रम_each_possible_cpu(cpu) अणु
		अचिन्हित दीर्घ stack_page;

		stack_page = __get_मुक्त_page(GFP_KERNEL);
		अगर (!stack_page) अणु
			err = -ENOMEM;
			जाओ out_err;
		पूर्ण

		per_cpu(kvm_arm_hyp_stack_page, cpu) = stack_page;
	पूर्ण

	/*
	 * Allocate and initialize pages क्रम Hypervisor-mode percpu regions.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा page *page;
		व्योम *page_addr;

		page = alloc_pages(GFP_KERNEL, nvhe_percpu_order());
		अगर (!page) अणु
			err = -ENOMEM;
			जाओ out_err;
		पूर्ण

		page_addr = page_address(page);
		स_नकल(page_addr, CHOOSE_NVHE_SYM(__per_cpu_start), nvhe_percpu_size());
		kvm_arm_hyp_percpu_base[cpu] = (अचिन्हित दीर्घ)page_addr;
	पूर्ण

	/*
	 * Map the Hyp-code called directly from the host
	 */
	err = create_hyp_mappings(kvm_ksym_ref(__hyp_text_start),
				  kvm_ksym_ref(__hyp_text_end), PAGE_HYP_EXEC);
	अगर (err) अणु
		kvm_err("Cannot map world-switch code\n");
		जाओ out_err;
	पूर्ण

	err = create_hyp_mappings(kvm_ksym_ref(__hyp_rodata_start),
				  kvm_ksym_ref(__hyp_rodata_end), PAGE_HYP_RO);
	अगर (err) अणु
		kvm_err("Cannot map .hyp.rodata section\n");
		जाओ out_err;
	पूर्ण

	err = create_hyp_mappings(kvm_ksym_ref(__start_rodata),
				  kvm_ksym_ref(__end_rodata), PAGE_HYP_RO);
	अगर (err) अणु
		kvm_err("Cannot map rodata section\n");
		जाओ out_err;
	पूर्ण

	/*
	 * .hyp.bss is guaranteed to be placed at the beginning of the .bss
	 * section thanks to an निश्चितion in the linker script. Map it RW and
	 * the rest of .bss RO.
	 */
	err = create_hyp_mappings(kvm_ksym_ref(__hyp_bss_start),
				  kvm_ksym_ref(__hyp_bss_end), PAGE_HYP);
	अगर (err) अणु
		kvm_err("Cannot map hyp bss section: %d\n", err);
		जाओ out_err;
	पूर्ण

	err = create_hyp_mappings(kvm_ksym_ref(__hyp_bss_end),
				  kvm_ksym_ref(__bss_stop), PAGE_HYP_RO);
	अगर (err) अणु
		kvm_err("Cannot map bss section\n");
		जाओ out_err;
	पूर्ण

	/*
	 * Map the Hyp stack pages
	 */
	क्रम_each_possible_cpu(cpu) अणु
		अक्षर *stack_page = (अक्षर *)per_cpu(kvm_arm_hyp_stack_page, cpu);
		err = create_hyp_mappings(stack_page, stack_page + PAGE_SIZE,
					  PAGE_HYP);

		अगर (err) अणु
			kvm_err("Cannot map hyp stack\n");
			जाओ out_err;
		पूर्ण
	पूर्ण

	क्रम_each_possible_cpu(cpu) अणु
		अक्षर *percpu_begin = (अक्षर *)kvm_arm_hyp_percpu_base[cpu];
		अक्षर *percpu_end = percpu_begin + nvhe_percpu_size();

		/* Map Hyp percpu pages */
		err = create_hyp_mappings(percpu_begin, percpu_end, PAGE_HYP);
		अगर (err) अणु
			kvm_err("Cannot map hyp percpu region\n");
			जाओ out_err;
		पूर्ण

		/* Prepare the CPU initialization parameters */
		cpu_prepare_hyp_mode(cpu);
	पूर्ण

	अगर (is_रक्षित_kvm_enabled()) अणु
		init_cpu_logical_map();

		अगर (!init_psci_relay()) अणु
			err = -ENODEV;
			जाओ out_err;
		पूर्ण
	पूर्ण

	अगर (is_रक्षित_kvm_enabled()) अणु
		err = kvm_hyp_init_protection(hyp_va_bits);
		अगर (err) अणु
			kvm_err("Failed to init hyp memory protection\n");
			जाओ out_err;
		पूर्ण
	पूर्ण

	वापस 0;

out_err:
	tearकरोwn_hyp_mode();
	kvm_err("error initializing Hyp mode: %d\n", err);
	वापस err;
पूर्ण

अटल व्योम _kvm_host_prot_finalize(व्योम *discard)
अणु
	WARN_ON(kvm_call_hyp_nvhe(__pkvm_prot_finalize));
पूर्ण

अटल अंतरभूत पूर्णांक pkvm_mark_hyp(phys_addr_t start, phys_addr_t end)
अणु
	वापस kvm_call_hyp_nvhe(__pkvm_mark_hyp, start, end);
पूर्ण

#घोषणा pkvm_mark_hyp_section(__section)		\
	pkvm_mark_hyp(__pa_symbol(__section##_start),	\
			__pa_symbol(__section##_end))

अटल पूर्णांक finalize_hyp_mode(व्योम)
अणु
	पूर्णांक cpu, ret;

	अगर (!is_रक्षित_kvm_enabled())
		वापस 0;

	ret = pkvm_mark_hyp_section(__hyp_idmap_text);
	अगर (ret)
		वापस ret;

	ret = pkvm_mark_hyp_section(__hyp_text);
	अगर (ret)
		वापस ret;

	ret = pkvm_mark_hyp_section(__hyp_rodata);
	अगर (ret)
		वापस ret;

	ret = pkvm_mark_hyp_section(__hyp_bss);
	अगर (ret)
		वापस ret;

	ret = pkvm_mark_hyp(hyp_mem_base, hyp_mem_base + hyp_mem_size);
	अगर (ret)
		वापस ret;

	क्रम_each_possible_cpu(cpu) अणु
		phys_addr_t start = virt_to_phys((व्योम *)kvm_arm_hyp_percpu_base[cpu]);
		phys_addr_t end = start + (PAGE_SIZE << nvhe_percpu_order());

		ret = pkvm_mark_hyp(start, end);
		अगर (ret)
			वापस ret;

		start = virt_to_phys((व्योम *)per_cpu(kvm_arm_hyp_stack_page, cpu));
		end = start + PAGE_SIZE;
		ret = pkvm_mark_hyp(start, end);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Flip the अटल key upfront as that may no दीर्घer be possible
	 * once the host stage 2 is installed.
	 */
	अटल_branch_enable(&kvm_रक्षित_mode_initialized);
	on_each_cpu(_kvm_host_prot_finalize, शून्य, 1);

	वापस 0;
पूर्ण

अटल व्योम check_kvm_target_cpu(व्योम *ret)
अणु
	*(पूर्णांक *)ret = kvm_target_cpu();
पूर्ण

काष्ठा kvm_vcpu *kvm_mpidr_to_vcpu(काष्ठा kvm *kvm, अचिन्हित दीर्घ mpidr)
अणु
	काष्ठा kvm_vcpu *vcpu;
	पूर्णांक i;

	mpidr &= MPIDR_HWID_BITMASK;
	kvm_क्रम_each_vcpu(i, vcpu, kvm) अणु
		अगर (mpidr == kvm_vcpu_get_mpidr_aff(vcpu))
			वापस vcpu;
	पूर्ण
	वापस शून्य;
पूर्ण

bool kvm_arch_has_irq_bypass(व्योम)
अणु
	वापस true;
पूर्ण

पूर्णांक kvm_arch_irq_bypass_add_producer(काष्ठा irq_bypass_consumer *cons,
				      काष्ठा irq_bypass_producer *prod)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);

	वापस kvm_vgic_v4_set_क्रमwarding(irqfd->kvm, prod->irq,
					  &irqfd->irq_entry);
पूर्ण
व्योम kvm_arch_irq_bypass_del_producer(काष्ठा irq_bypass_consumer *cons,
				      काष्ठा irq_bypass_producer *prod)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);

	kvm_vgic_v4_unset_क्रमwarding(irqfd->kvm, prod->irq,
				     &irqfd->irq_entry);
पूर्ण

व्योम kvm_arch_irq_bypass_stop(काष्ठा irq_bypass_consumer *cons)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);

	kvm_arm_halt_guest(irqfd->kvm);
पूर्ण

व्योम kvm_arch_irq_bypass_start(काष्ठा irq_bypass_consumer *cons)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);

	kvm_arm_resume_guest(irqfd->kvm);
पूर्ण

/**
 * Initialize Hyp-mode and memory mappings on all CPUs.
 */
पूर्णांक kvm_arch_init(व्योम *opaque)
अणु
	पूर्णांक err;
	पूर्णांक ret, cpu;
	bool in_hyp_mode;

	अगर (!is_hyp_mode_available()) अणु
		kvm_info("HYP mode not available\n");
		वापस -ENODEV;
	पूर्ण

	in_hyp_mode = is_kernel_in_hyp_mode();

	अगर (cpus_have_final_cap(ARM64_WORKAROUND_DEVICE_LOAD_ACQUIRE) ||
	    cpus_have_final_cap(ARM64_WORKAROUND_1508412))
		kvm_info("Guests without required CPU erratum workarounds can deadlock system!\n" \
			 "Only trusted guests should be used on this system.\n");

	क्रम_each_online_cpu(cpu) अणु
		smp_call_function_single(cpu, check_kvm_target_cpu, &ret, 1);
		अगर (ret < 0) अणु
			kvm_err("Error, CPU %d not supported!\n", cpu);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	err = init_common_resources();
	अगर (err)
		वापस err;

	err = kvm_arm_init_sve();
	अगर (err)
		वापस err;

	अगर (!in_hyp_mode) अणु
		err = init_hyp_mode();
		अगर (err)
			जाओ out_err;
	पूर्ण

	err = kvm_init_vector_slots();
	अगर (err) अणु
		kvm_err("Cannot initialise vector slots\n");
		जाओ out_err;
	पूर्ण

	err = init_subप्रणालीs();
	अगर (err)
		जाओ out_hyp;

	अगर (!in_hyp_mode) अणु
		err = finalize_hyp_mode();
		अगर (err) अणु
			kvm_err("Failed to finalize Hyp protection\n");
			जाओ out_hyp;
		पूर्ण
	पूर्ण

	अगर (is_रक्षित_kvm_enabled()) अणु
		kvm_info("Protected nVHE mode initialized successfully\n");
	पूर्ण अन्यथा अगर (in_hyp_mode) अणु
		kvm_info("VHE mode initialized successfully\n");
	पूर्ण अन्यथा अणु
		kvm_info("Hyp mode initialized successfully\n");
	पूर्ण

	वापस 0;

out_hyp:
	hyp_cpu_pm_निकास();
	अगर (!in_hyp_mode)
		tearकरोwn_hyp_mode();
out_err:
	वापस err;
पूर्ण

/* NOP: Compiling as a module not supported */
व्योम kvm_arch_निकास(व्योम)
अणु
	kvm_perf_tearकरोwn();
पूर्ण

अटल पूर्णांक __init early_kvm_mode_cfg(अक्षर *arg)
अणु
	अगर (!arg)
		वापस -EINVAL;

	अगर (म_भेद(arg, "protected") == 0) अणु
		kvm_mode = KVM_MODE_PROTECTED;
		वापस 0;
	पूर्ण

	अगर (म_भेद(arg, "nvhe") == 0 && !WARN_ON(is_kernel_in_hyp_mode()))
		वापस 0;

	वापस -EINVAL;
पूर्ण
early_param("kvm-arm.mode", early_kvm_mode_cfg);

क्रमागत kvm_mode kvm_get_mode(व्योम)
अणु
	वापस kvm_mode;
पूर्ण

अटल पूर्णांक arm_init(व्योम)
अणु
	पूर्णांक rc = kvm_init(शून्य, माप(काष्ठा kvm_vcpu), 0, THIS_MODULE);
	वापस rc;
पूर्ण

module_init(arm_init);
