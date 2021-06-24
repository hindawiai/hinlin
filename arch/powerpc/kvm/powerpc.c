<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright IBM Corp. 2007
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 *          Christian Ehrhardt <ehrhardt@linux.vnet.ibm.com>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <linux/irqbypass.h>
#समावेश <linux/kvm_irqfd.h>
#समावेश <यंत्र/cputable.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/irqflags.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/xive.h>
#अगर_घोषित CONFIG_PPC_PSERIES
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/plpar_wrappers.h>
#पूर्ण_अगर
#समावेश <यंत्र/ultravisor.h>

#समावेश "timing.h"
#समावेश "irq.h"
#समावेश "../mm/mmu_decl.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"

काष्ठा kvmppc_ops *kvmppc_hv_ops;
EXPORT_SYMBOL_GPL(kvmppc_hv_ops);
काष्ठा kvmppc_ops *kvmppc_pr_ops;
EXPORT_SYMBOL_GPL(kvmppc_pr_ops);


पूर्णांक kvm_arch_vcpu_runnable(काष्ठा kvm_vcpu *v)
अणु
	वापस !!(v->arch.pending_exceptions) || kvm_request_pending(v);
पूर्ण

bool kvm_arch_dy_runnable(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvm_arch_vcpu_runnable(vcpu);
पूर्ण

bool kvm_arch_vcpu_in_kernel(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस false;
पूर्ण

पूर्णांक kvm_arch_vcpu_should_kick(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस 1;
पूर्ण

/*
 * Common checks beक्रमe entering the guest world.  Call with पूर्णांकerrupts
 * disabled.
 *
 * वापसs:
 *
 * == 1 अगर we're पढ़ोy to go पूर्णांकo guest state
 * <= 0 अगर we need to go back to the host with वापस value
 */
पूर्णांक kvmppc_prepare_to_enter(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r;

	WARN_ON(irqs_disabled());
	hard_irq_disable();

	जबतक (true) अणु
		अगर (need_resched()) अणु
			local_irq_enable();
			cond_resched();
			hard_irq_disable();
			जारी;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			kvmppc_account_निकास(vcpu, SIGNAL_EXITS);
			vcpu->run->निकास_reason = KVM_EXIT_INTR;
			r = -EINTR;
			अवरोध;
		पूर्ण

		vcpu->mode = IN_GUEST_MODE;

		/*
		 * Reading vcpu->requests must happen after setting vcpu->mode,
		 * so we करोn't miss a request because the requester sees
		 * OUTSIDE_GUEST_MODE and assumes we'll be checking requests
		 * beक्रमe next entering the guest (and thus करोesn't IPI).
		 * This also orders the ग_लिखो to mode from any पढ़ोs
		 * to the page tables करोne जबतक the VCPU is running.
		 * Please see the comment in kvm_flush_remote_tlbs.
		 */
		smp_mb();

		अगर (kvm_request_pending(vcpu)) अणु
			/* Make sure we process requests preemptable */
			local_irq_enable();
			trace_kvm_check_requests(vcpu);
			r = kvmppc_core_check_requests(vcpu);
			hard_irq_disable();
			अगर (r > 0)
				जारी;
			अवरोध;
		पूर्ण

		अगर (kvmppc_core_prepare_to_enter(vcpu)) अणु
			/* पूर्णांकerrupts got enabled in between, so we
			   are back at square 1 */
			जारी;
		पूर्ण

		guest_enter_irqoff();
		वापस 1;
	पूर्ण

	/* वापस to host */
	local_irq_enable();
	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_prepare_to_enter);

#अगर defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_KVM_BOOK3S_PR_POSSIBLE)
अटल व्योम kvmppc_swab_shared(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_vcpu_arch_shared *shared = vcpu->arch.shared;
	पूर्णांक i;

	shared->sprg0 = swab64(shared->sprg0);
	shared->sprg1 = swab64(shared->sprg1);
	shared->sprg2 = swab64(shared->sprg2);
	shared->sprg3 = swab64(shared->sprg3);
	shared->srr0 = swab64(shared->srr0);
	shared->srr1 = swab64(shared->srr1);
	shared->dar = swab64(shared->dar);
	shared->msr = swab64(shared->msr);
	shared->dsisr = swab32(shared->dsisr);
	shared->पूर्णांक_pending = swab32(shared->पूर्णांक_pending);
	क्रम (i = 0; i < ARRAY_SIZE(shared->sr); i++)
		shared->sr[i] = swab32(shared->sr[i]);
पूर्ण
#पूर्ण_अगर

पूर्णांक kvmppc_kvm_pv(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक nr = kvmppc_get_gpr(vcpu, 11);
	पूर्णांक r;
	अचिन्हित दीर्घ __maybe_unused param1 = kvmppc_get_gpr(vcpu, 3);
	अचिन्हित दीर्घ __maybe_unused param2 = kvmppc_get_gpr(vcpu, 4);
	अचिन्हित दीर्घ __maybe_unused param3 = kvmppc_get_gpr(vcpu, 5);
	अचिन्हित दीर्घ __maybe_unused param4 = kvmppc_get_gpr(vcpu, 6);
	अचिन्हित दीर्घ r2 = 0;

	अगर (!(kvmppc_get_msr(vcpu) & MSR_SF)) अणु
		/* 32 bit mode */
		param1 &= 0xffffffff;
		param2 &= 0xffffffff;
		param3 &= 0xffffffff;
		param4 &= 0xffffffff;
	पूर्ण

	चयन (nr) अणु
	हाल KVM_HCALL_TOKEN(KVM_HC_PPC_MAP_MAGIC_PAGE):
	अणु
#अगर defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_KVM_BOOK3S_PR_POSSIBLE)
		/* Book3S can be little endian, find it out here */
		पूर्णांक shared_big_endian = true;
		अगर (vcpu->arch.पूर्णांकr_msr & MSR_LE)
			shared_big_endian = false;
		अगर (shared_big_endian != vcpu->arch.shared_big_endian)
			kvmppc_swab_shared(vcpu);
		vcpu->arch.shared_big_endian = shared_big_endian;
#पूर्ण_अगर

		अगर (!(param2 & MAGIC_PAGE_FLAG_NOT_MAPPED_NX)) अणु
			/*
			 * Older versions of the Linux magic page code had
			 * a bug where they would map their trampoline code
			 * NX. If that's the हाल, हटाओ !PR NX capability.
			 */
			vcpu->arch.disable_kernel_nx = true;
			kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
		पूर्ण

		vcpu->arch.magic_page_pa = param1 & ~0xfffULL;
		vcpu->arch.magic_page_ea = param2 & ~0xfffULL;

#अगर_घोषित CONFIG_PPC_64K_PAGES
		/*
		 * Make sure our 4k magic page is in the same winकरोw of a 64k
		 * page within the guest and within the host's page.
		 */
		अगर ((vcpu->arch.magic_page_pa & 0xf000) !=
		    ((uदीर्घ)vcpu->arch.shared & 0xf000)) अणु
			व्योम *old_shared = vcpu->arch.shared;
			uदीर्घ shared = (uदीर्घ)vcpu->arch.shared;
			व्योम *new_shared;

			shared &= PAGE_MASK;
			shared |= vcpu->arch.magic_page_pa & 0xf000;
			new_shared = (व्योम*)shared;
			स_नकल(new_shared, old_shared, 0x1000);
			vcpu->arch.shared = new_shared;
		पूर्ण
#पूर्ण_अगर

		r2 = KVM_MAGIC_FEAT_SR | KVM_MAGIC_FEAT_MAS0_TO_SPRG7;

		r = EV_SUCCESS;
		अवरोध;
	पूर्ण
	हाल KVM_HCALL_TOKEN(KVM_HC_FEATURES):
		r = EV_SUCCESS;
#अगर defined(CONFIG_PPC_BOOK3S) || defined(CONFIG_KVM_E500V2)
		r2 |= (1 << KVM_FEATURE_MAGIC_PAGE);
#पूर्ण_अगर

		/* Second वापस value is in r4 */
		अवरोध;
	हाल EV_HCALL_TOKEN(EV_IDLE):
		r = EV_SUCCESS;
		kvm_vcpu_block(vcpu);
		kvm_clear_request(KVM_REQ_UNHALT, vcpu);
		अवरोध;
	शेष:
		r = EV_UNIMPLEMENTED;
		अवरोध;
	पूर्ण

	kvmppc_set_gpr(vcpu, 4, r2);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_kvm_pv);

पूर्णांक kvmppc_sanity_check(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक r = false;

	/* We have to know what CPU to भवize */
	अगर (!vcpu->arch.pvr)
		जाओ out;

	/* PAPR only works with book3s_64 */
	अगर ((vcpu->arch.cpu_type != KVM_CPU_3S_64) && vcpu->arch.papr_enabled)
		जाओ out;

	/* HV KVM can only करो PAPR mode क्रम now */
	अगर (!vcpu->arch.papr_enabled && is_kvmppc_hv_enabled(vcpu->kvm))
		जाओ out;

#अगर_घोषित CONFIG_KVM_BOOKE_HV
	अगर (!cpu_has_feature(CPU_FTR_EMB_HV))
		जाओ out;
#पूर्ण_अगर

	r = true;

out:
	vcpu->arch.sane = r;
	वापस r ? 0 : -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_sanity_check);

पूर्णांक kvmppc_emulate_mmio(काष्ठा kvm_vcpu *vcpu)
अणु
	क्रमागत emulation_result er;
	पूर्णांक r;

	er = kvmppc_emulate_loadstore(vcpu);
	चयन (er) अणु
	हाल EMULATE_DONE:
		/* Future optimization: only reload non-अस्थिरs अगर they were
		 * actually modअगरied. */
		r = RESUME_GUEST_NV;
		अवरोध;
	हाल EMULATE_AGAIN:
		r = RESUME_GUEST;
		अवरोध;
	हाल EMULATE_DO_MMIO:
		vcpu->run->निकास_reason = KVM_EXIT_MMIO;
		/* We must reload nonअस्थिरs because "update" load/store
		 * inकाष्ठाions modअगरy रेजिस्टर state. */
		/* Future optimization: only reload non-अस्थिरs अगर they were
		 * actually modअगरied. */
		r = RESUME_HOST_NV;
		अवरोध;
	हाल EMULATE_FAIL:
	अणु
		u32 last_inst;

		kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst);
		/* XXX Deliver Program पूर्णांकerrupt to guest. */
		pr_emerg("%s: emulation failed (%08x)\n", __func__, last_inst);
		r = RESUME_HOST;
		अवरोध;
	पूर्ण
	शेष:
		WARN_ON(1);
		r = RESUME_GUEST;
	पूर्ण

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_emulate_mmio);

पूर्णांक kvmppc_st(काष्ठा kvm_vcpu *vcpu, uदीर्घ *eaddr, पूर्णांक size, व्योम *ptr,
	      bool data)
अणु
	uदीर्घ mp_pa = vcpu->arch.magic_page_pa & KVM_PAM & PAGE_MASK;
	काष्ठा kvmppc_pte pte;
	पूर्णांक r = -EINVAL;

	vcpu->stat.st++;

	अगर (vcpu->kvm->arch.kvm_ops && vcpu->kvm->arch.kvm_ops->store_to_eaddr)
		r = vcpu->kvm->arch.kvm_ops->store_to_eaddr(vcpu, eaddr, ptr,
							    size);

	अगर ((!r) || (r == -EAGAIN))
		वापस r;

	r = kvmppc_xlate(vcpu, *eaddr, data ? XLATE_DATA : XLATE_INST,
			 XLATE_WRITE, &pte);
	अगर (r < 0)
		वापस r;

	*eaddr = pte.raddr;

	अगर (!pte.may_ग_लिखो)
		वापस -EPERM;

	/* Magic page override */
	अगर (kvmppc_supports_magic_page(vcpu) && mp_pa &&
	    ((pte.raddr & KVM_PAM & PAGE_MASK) == mp_pa) &&
	    !(kvmppc_get_msr(vcpu) & MSR_PR)) अणु
		व्योम *magic = vcpu->arch.shared;
		magic += pte.eaddr & 0xfff;
		स_नकल(magic, ptr, size);
		वापस EMULATE_DONE;
	पूर्ण

	अगर (kvm_ग_लिखो_guest(vcpu->kvm, pte.raddr, ptr, size))
		वापस EMULATE_DO_MMIO;

	वापस EMULATE_DONE;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_st);

पूर्णांक kvmppc_ld(काष्ठा kvm_vcpu *vcpu, uदीर्घ *eaddr, पूर्णांक size, व्योम *ptr,
		      bool data)
अणु
	uदीर्घ mp_pa = vcpu->arch.magic_page_pa & KVM_PAM & PAGE_MASK;
	काष्ठा kvmppc_pte pte;
	पूर्णांक rc = -EINVAL;

	vcpu->stat.ld++;

	अगर (vcpu->kvm->arch.kvm_ops && vcpu->kvm->arch.kvm_ops->load_from_eaddr)
		rc = vcpu->kvm->arch.kvm_ops->load_from_eaddr(vcpu, eaddr, ptr,
							      size);

	अगर ((!rc) || (rc == -EAGAIN))
		वापस rc;

	rc = kvmppc_xlate(vcpu, *eaddr, data ? XLATE_DATA : XLATE_INST,
			  XLATE_READ, &pte);
	अगर (rc)
		वापस rc;

	*eaddr = pte.raddr;

	अगर (!pte.may_पढ़ो)
		वापस -EPERM;

	अगर (!data && !pte.may_execute)
		वापस -ENOEXEC;

	/* Magic page override */
	अगर (kvmppc_supports_magic_page(vcpu) && mp_pa &&
	    ((pte.raddr & KVM_PAM & PAGE_MASK) == mp_pa) &&
	    !(kvmppc_get_msr(vcpu) & MSR_PR)) अणु
		व्योम *magic = vcpu->arch.shared;
		magic += pte.eaddr & 0xfff;
		स_नकल(ptr, magic, size);
		वापस EMULATE_DONE;
	पूर्ण

	vcpu->srcu_idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
	rc = kvm_पढ़ो_guest(vcpu->kvm, pte.raddr, ptr, size);
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, vcpu->srcu_idx);
	अगर (rc)
		वापस EMULATE_DO_MMIO;

	वापस EMULATE_DONE;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_ld);

पूर्णांक kvm_arch_hardware_enable(व्योम)
अणु
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_hardware_setup(व्योम *opaque)
अणु
	वापस 0;
पूर्ण

पूर्णांक kvm_arch_check_processor_compat(व्योम *opaque)
अणु
	वापस kvmppc_core_check_processor_compat();
पूर्ण

पूर्णांक kvm_arch_init_vm(काष्ठा kvm *kvm, अचिन्हित दीर्घ type)
अणु
	काष्ठा kvmppc_ops *kvm_ops = शून्य;
	/*
	 * अगर we have both HV and PR enabled, शेष is HV
	 */
	अगर (type == 0) अणु
		अगर (kvmppc_hv_ops)
			kvm_ops = kvmppc_hv_ops;
		अन्यथा
			kvm_ops = kvmppc_pr_ops;
		अगर (!kvm_ops)
			जाओ err_out;
	पूर्ण अन्यथा	अगर (type == KVM_VM_PPC_HV) अणु
		अगर (!kvmppc_hv_ops)
			जाओ err_out;
		kvm_ops = kvmppc_hv_ops;
	पूर्ण अन्यथा अगर (type == KVM_VM_PPC_PR) अणु
		अगर (!kvmppc_pr_ops)
			जाओ err_out;
		kvm_ops = kvmppc_pr_ops;
	पूर्ण अन्यथा
		जाओ err_out;

	अगर (kvm_ops->owner && !try_module_get(kvm_ops->owner))
		वापस -ENOENT;

	kvm->arch.kvm_ops = kvm_ops;
	वापस kvmppc_core_init_vm(kvm);
err_out:
	वापस -EINVAL;
पूर्ण

व्योम kvm_arch_destroy_vm(काष्ठा kvm *kvm)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा kvm_vcpu *vcpu;

#अगर_घोषित CONFIG_KVM_XICS
	/*
	 * We call kick_all_cpus_sync() to ensure that all
	 * CPUs have executed any pending IPIs beक्रमe we
	 * जारी and मुक्त VCPUs काष्ठाures below.
	 */
	अगर (is_kvmppc_hv_enabled(kvm))
		kick_all_cpus_sync();
#पूर्ण_अगर

	kvm_क्रम_each_vcpu(i, vcpu, kvm)
		kvm_vcpu_destroy(vcpu);

	mutex_lock(&kvm->lock);
	क्रम (i = 0; i < atomic_पढ़ो(&kvm->online_vcpus); i++)
		kvm->vcpus[i] = शून्य;

	atomic_set(&kvm->online_vcpus, 0);

	kvmppc_core_destroy_vm(kvm);

	mutex_unlock(&kvm->lock);

	/* drop the module reference */
	module_put(kvm->arch.kvm_ops->owner);
पूर्ण

पूर्णांक kvm_vm_ioctl_check_extension(काष्ठा kvm *kvm, दीर्घ ext)
अणु
	पूर्णांक r;
	/* Assume we're using HV mode when the HV module is loaded */
	पूर्णांक hv_enabled = kvmppc_hv_ops ? 1 : 0;

	अगर (kvm) अणु
		/*
		 * Hooray - we know which VM type we're running on. Depend on
		 * that rather than the guess above.
		 */
		hv_enabled = is_kvmppc_hv_enabled(kvm);
	पूर्ण

	चयन (ext) अणु
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_CAP_PPC_BOOKE_SREGS:
	हाल KVM_CAP_PPC_BOOKE_WATCHDOG:
	हाल KVM_CAP_PPC_EPR:
#अन्यथा
	हाल KVM_CAP_PPC_SEGSTATE:
	हाल KVM_CAP_PPC_HIOR:
	हाल KVM_CAP_PPC_PAPR:
#पूर्ण_अगर
	हाल KVM_CAP_PPC_UNSET_IRQ:
	हाल KVM_CAP_PPC_IRQ_LEVEL:
	हाल KVM_CAP_ENABLE_CAP:
	हाल KVM_CAP_ONE_REG:
	हाल KVM_CAP_IOEVENTFD:
	हाल KVM_CAP_DEVICE_CTRL:
	हाल KVM_CAP_IMMEDIATE_EXIT:
	हाल KVM_CAP_SET_GUEST_DEBUG:
		r = 1;
		अवरोध;
	हाल KVM_CAP_PPC_GUEST_DEBUG_SSTEP:
	हाल KVM_CAP_PPC_PAIRED_SINGLES:
	हाल KVM_CAP_PPC_OSI:
	हाल KVM_CAP_PPC_GET_PVINFO:
#अगर defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	हाल KVM_CAP_SW_TLB:
#पूर्ण_अगर
		/* We support this only क्रम PR */
		r = !hv_enabled;
		अवरोध;
#अगर_घोषित CONFIG_KVM_MPIC
	हाल KVM_CAP_IRQ_MPIC:
		r = 1;
		अवरोध;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल KVM_CAP_SPAPR_TCE:
	हाल KVM_CAP_SPAPR_TCE_64:
		r = 1;
		अवरोध;
	हाल KVM_CAP_SPAPR_TCE_VFIO:
		r = !!cpu_has_feature(CPU_FTR_HVMODE);
		अवरोध;
	हाल KVM_CAP_PPC_RTAS:
	हाल KVM_CAP_PPC_FIXUP_HCALL:
	हाल KVM_CAP_PPC_ENABLE_HCALL:
#अगर_घोषित CONFIG_KVM_XICS
	हाल KVM_CAP_IRQ_XICS:
#पूर्ण_अगर
	हाल KVM_CAP_PPC_GET_CPU_CHAR:
		r = 1;
		अवरोध;
#अगर_घोषित CONFIG_KVM_XIVE
	हाल KVM_CAP_PPC_IRQ_XIVE:
		/*
		 * We need XIVE to be enabled on the platक्रमm (implies
		 * a POWER9 processor) and the PowerNV platक्रमm, as
		 * nested is not yet supported.
		 */
		r = xive_enabled() && !!cpu_has_feature(CPU_FTR_HVMODE) &&
			kvmppc_xive_native_supported();
		अवरोध;
#पूर्ण_अगर

	हाल KVM_CAP_PPC_ALLOC_HTAB:
		r = hv_enabled;
		अवरोध;
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	हाल KVM_CAP_PPC_SMT:
		r = 0;
		अगर (kvm) अणु
			अगर (kvm->arch.emul_smt_mode > 1)
				r = kvm->arch.emul_smt_mode;
			अन्यथा
				r = kvm->arch.smt_mode;
		पूर्ण अन्यथा अगर (hv_enabled) अणु
			अगर (cpu_has_feature(CPU_FTR_ARCH_300))
				r = 1;
			अन्यथा
				r = thपढ़ोs_per_subcore;
		पूर्ण
		अवरोध;
	हाल KVM_CAP_PPC_SMT_POSSIBLE:
		r = 1;
		अगर (hv_enabled) अणु
			अगर (!cpu_has_feature(CPU_FTR_ARCH_300))
				r = ((thपढ़ोs_per_subcore << 1) - 1);
			अन्यथा
				/* P9 can emulate dbells, so allow any mode */
				r = 8 | 4 | 2 | 1;
		पूर्ण
		अवरोध;
	हाल KVM_CAP_PPC_RMA:
		r = 0;
		अवरोध;
	हाल KVM_CAP_PPC_HWRNG:
		r = kvmppc_hwrng_present();
		अवरोध;
	हाल KVM_CAP_PPC_MMU_RADIX:
		r = !!(hv_enabled && radix_enabled());
		अवरोध;
	हाल KVM_CAP_PPC_MMU_HASH_V3:
		r = !!(hv_enabled && kvmppc_hv_ops->hash_v3_possible &&
		       kvmppc_hv_ops->hash_v3_possible());
		अवरोध;
	हाल KVM_CAP_PPC_NESTED_HV:
		r = !!(hv_enabled && kvmppc_hv_ops->enable_nested &&
		       !kvmppc_hv_ops->enable_nested(शून्य));
		अवरोध;
#पूर्ण_अगर
	हाल KVM_CAP_SYNC_MMU:
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
		r = hv_enabled;
#या_अगर defined(KVM_ARCH_WANT_MMU_NOTIFIER)
		r = 1;
#अन्यथा
		r = 0;
#पूर्ण_अगर
		अवरोध;
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	हाल KVM_CAP_PPC_HTAB_FD:
		r = hv_enabled;
		अवरोध;
#पूर्ण_अगर
	हाल KVM_CAP_NR_VCPUS:
		/*
		 * Recommending a number of CPUs is somewhat arbitrary; we
		 * वापस the number of present CPUs क्रम -HV (since a host
		 * will have secondary thपढ़ोs "offline"), and क्रम other KVM
		 * implementations just count online CPUs.
		 */
		अगर (hv_enabled)
			r = num_present_cpus();
		अन्यथा
			r = num_online_cpus();
		अवरोध;
	हाल KVM_CAP_MAX_VCPUS:
		r = KVM_MAX_VCPUS;
		अवरोध;
	हाल KVM_CAP_MAX_VCPU_ID:
		r = KVM_MAX_VCPU_ID;
		अवरोध;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल KVM_CAP_PPC_GET_SMMU_INFO:
		r = 1;
		अवरोध;
	हाल KVM_CAP_SPAPR_MULTITCE:
		r = 1;
		अवरोध;
	हाल KVM_CAP_SPAPR_RESIZE_HPT:
		r = !!hv_enabled;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	हाल KVM_CAP_PPC_FWNMI:
		r = hv_enabled;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	हाल KVM_CAP_PPC_HTM:
		r = !!(cur_cpu_spec->cpu_user_features2 & PPC_FEATURE2_HTM) ||
		     (hv_enabled && cpu_has_feature(CPU_FTR_P9_TM_HV_ASSIST));
		अवरोध;
#पूर्ण_अगर
#अगर defined(CONFIG_KVM_BOOK3S_HV_POSSIBLE)
	हाल KVM_CAP_PPC_SECURE_GUEST:
		r = hv_enabled && kvmppc_hv_ops->enable_svm &&
			!kvmppc_hv_ops->enable_svm(शून्य);
		अवरोध;
	हाल KVM_CAP_PPC_DAWR1:
		r = !!(hv_enabled && kvmppc_hv_ops->enable_dawr1 &&
		       !kvmppc_hv_ops->enable_dawr1(शून्य));
		अवरोध;
#पूर्ण_अगर
	शेष:
		r = 0;
		अवरोध;
	पूर्ण
	वापस r;

पूर्ण

दीर्घ kvm_arch_dev_ioctl(काष्ठा file *filp,
                        अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	वापस -EINVAL;
पूर्ण

व्योम kvm_arch_मुक्त_memslot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot)
अणु
	kvmppc_core_मुक्त_memslot(kvm, slot);
पूर्ण

पूर्णांक kvm_arch_prepare_memory_region(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *memslot,
				   स्थिर काष्ठा kvm_userspace_memory_region *mem,
				   क्रमागत kvm_mr_change change)
अणु
	वापस kvmppc_core_prepare_memory_region(kvm, memslot, mem, change);
पूर्ण

व्योम kvm_arch_commit_memory_region(काष्ठा kvm *kvm,
				   स्थिर काष्ठा kvm_userspace_memory_region *mem,
				   काष्ठा kvm_memory_slot *old,
				   स्थिर काष्ठा kvm_memory_slot *new,
				   क्रमागत kvm_mr_change change)
अणु
	kvmppc_core_commit_memory_region(kvm, mem, old, new, change);
पूर्ण

व्योम kvm_arch_flush_shaकरोw_memslot(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *slot)
अणु
	kvmppc_core_flush_memslot(kvm, slot);
पूर्ण

पूर्णांक kvm_arch_vcpu_precreate(काष्ठा kvm *kvm, अचिन्हित पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल क्रमागत hrसमयr_restart kvmppc_decrementer_wakeup(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा kvm_vcpu *vcpu;

	vcpu = container_of(समयr, काष्ठा kvm_vcpu, arch.dec_समयr);
	kvmppc_decrementer_func(vcpu);

	वापस HRTIMER_NORESTART;
पूर्ण

पूर्णांक kvm_arch_vcpu_create(काष्ठा kvm_vcpu *vcpu)
अणु
	पूर्णांक err;

	hrसमयr_init(&vcpu->arch.dec_समयr, CLOCK_REALTIME, HRTIMER_MODE_ABS);
	vcpu->arch.dec_समयr.function = kvmppc_decrementer_wakeup;
	vcpu->arch.dec_expires = get_tb();

#अगर_घोषित CONFIG_KVM_EXIT_TIMING
	mutex_init(&vcpu->arch.निकास_timing_lock);
#पूर्ण_अगर
	err = kvmppc_subarch_vcpu_init(vcpu);
	अगर (err)
		वापस err;

	err = kvmppc_core_vcpu_create(vcpu);
	अगर (err)
		जाओ out_vcpu_uninit;

	vcpu->arch.रुकोp = &vcpu->रुको;
	kvmppc_create_vcpu_debugfs(vcpu, vcpu->vcpu_id);
	वापस 0;

out_vcpu_uninit:
	kvmppc_subarch_vcpu_uninit(vcpu);
	वापस err;
पूर्ण

व्योम kvm_arch_vcpu_postcreate(काष्ठा kvm_vcpu *vcpu)
अणु
पूर्ण

व्योम kvm_arch_vcpu_destroy(काष्ठा kvm_vcpu *vcpu)
अणु
	/* Make sure we're not using the vcpu anymore */
	hrसमयr_cancel(&vcpu->arch.dec_समयr);

	kvmppc_हटाओ_vcpu_debugfs(vcpu);

	चयन (vcpu->arch.irq_type) अणु
	हाल KVMPPC_IRQ_MPIC:
		kvmppc_mpic_disconnect_vcpu(vcpu->arch.mpic, vcpu);
		अवरोध;
	हाल KVMPPC_IRQ_XICS:
		अगर (xics_on_xive())
			kvmppc_xive_cleanup_vcpu(vcpu);
		अन्यथा
			kvmppc_xics_मुक्त_icp(vcpu);
		अवरोध;
	हाल KVMPPC_IRQ_XIVE:
		kvmppc_xive_native_cleanup_vcpu(vcpu);
		अवरोध;
	पूर्ण

	kvmppc_core_vcpu_मुक्त(vcpu);

	kvmppc_subarch_vcpu_uninit(vcpu);
पूर्ण

पूर्णांक kvm_cpu_has_pending_समयr(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस kvmppc_core_pending_dec(vcpu);
पूर्ण

व्योम kvm_arch_vcpu_load(काष्ठा kvm_vcpu *vcpu, पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_BOOKE
	/*
	 * vrsave (क्रमmerly usprg0) isn't used by Linux, but may
	 * be used by the guest.
	 *
	 * On non-booke this is associated with Altivec and
	 * is handled by code in book3s.c.
	 */
	mtspr(SPRN_VRSAVE, vcpu->arch.vrsave);
#पूर्ण_अगर
	kvmppc_core_vcpu_load(vcpu, cpu);
पूर्ण

व्योम kvm_arch_vcpu_put(काष्ठा kvm_vcpu *vcpu)
अणु
	kvmppc_core_vcpu_put(vcpu);
#अगर_घोषित CONFIG_BOOKE
	vcpu->arch.vrsave = mfspr(SPRN_VRSAVE);
#पूर्ण_अगर
पूर्ण

/*
 * irq_bypass_add_producer and irq_bypass_del_producer are only
 * useful अगर the architecture supports PCI passthrough.
 * irq_bypass_stop and irq_bypass_start are not needed and so
 * kvm_ops are not defined क्रम them.
 */
bool kvm_arch_has_irq_bypass(व्योम)
अणु
	वापस ((kvmppc_hv_ops && kvmppc_hv_ops->irq_bypass_add_producer) ||
		(kvmppc_pr_ops && kvmppc_pr_ops->irq_bypass_add_producer));
पूर्ण

पूर्णांक kvm_arch_irq_bypass_add_producer(काष्ठा irq_bypass_consumer *cons,
				     काष्ठा irq_bypass_producer *prod)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);
	काष्ठा kvm *kvm = irqfd->kvm;

	अगर (kvm->arch.kvm_ops->irq_bypass_add_producer)
		वापस kvm->arch.kvm_ops->irq_bypass_add_producer(cons, prod);

	वापस 0;
पूर्ण

व्योम kvm_arch_irq_bypass_del_producer(काष्ठा irq_bypass_consumer *cons,
				      काष्ठा irq_bypass_producer *prod)
अणु
	काष्ठा kvm_kernel_irqfd *irqfd =
		container_of(cons, काष्ठा kvm_kernel_irqfd, consumer);
	काष्ठा kvm *kvm = irqfd->kvm;

	अगर (kvm->arch.kvm_ops->irq_bypass_del_producer)
		kvm->arch.kvm_ops->irq_bypass_del_producer(cons, prod);
पूर्ण

#अगर_घोषित CONFIG_VSX
अटल अंतरभूत पूर्णांक kvmppc_get_vsr_dword_offset(पूर्णांक index)
अणु
	पूर्णांक offset;

	अगर ((index != 0) && (index != 1))
		वापस -1;

#अगर_घोषित __BIG_ENDIAN
	offset =  index;
#अन्यथा
	offset = 1 - index;
#पूर्ण_अगर

	वापस offset;
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_get_vsr_word_offset(पूर्णांक index)
अणु
	पूर्णांक offset;

	अगर ((index > 3) || (index < 0))
		वापस -1;

#अगर_घोषित __BIG_ENDIAN
	offset = index;
#अन्यथा
	offset = 3 - index;
#पूर्ण_अगर
	वापस offset;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_vsr_dword(काष्ठा kvm_vcpu *vcpu,
	u64 gpr)
अणु
	जोड़ kvmppc_one_reg val;
	पूर्णांक offset = kvmppc_get_vsr_dword_offset(vcpu->arch.mmio_vsx_offset);
	पूर्णांक index = vcpu->arch.io_gpr & KVM_MMIO_REG_MASK;

	अगर (offset == -1)
		वापस;

	अगर (index >= 32) अणु
		val.vval = VCPU_VSX_VR(vcpu, index - 32);
		val.vsxval[offset] = gpr;
		VCPU_VSX_VR(vcpu, index - 32) = val.vval;
	पूर्ण अन्यथा अणु
		VCPU_VSX_FPR(vcpu, index, offset) = gpr;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_vsr_dword_dump(काष्ठा kvm_vcpu *vcpu,
	u64 gpr)
अणु
	जोड़ kvmppc_one_reg val;
	पूर्णांक index = vcpu->arch.io_gpr & KVM_MMIO_REG_MASK;

	अगर (index >= 32) अणु
		val.vval = VCPU_VSX_VR(vcpu, index - 32);
		val.vsxval[0] = gpr;
		val.vsxval[1] = gpr;
		VCPU_VSX_VR(vcpu, index - 32) = val.vval;
	पूर्ण अन्यथा अणु
		VCPU_VSX_FPR(vcpu, index, 0) = gpr;
		VCPU_VSX_FPR(vcpu, index, 1) = gpr;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_vsr_word_dump(काष्ठा kvm_vcpu *vcpu,
	u32 gpr)
अणु
	जोड़ kvmppc_one_reg val;
	पूर्णांक index = vcpu->arch.io_gpr & KVM_MMIO_REG_MASK;

	अगर (index >= 32) अणु
		val.vsx32val[0] = gpr;
		val.vsx32val[1] = gpr;
		val.vsx32val[2] = gpr;
		val.vsx32val[3] = gpr;
		VCPU_VSX_VR(vcpu, index - 32) = val.vval;
	पूर्ण अन्यथा अणु
		val.vsx32val[0] = gpr;
		val.vsx32val[1] = gpr;
		VCPU_VSX_FPR(vcpu, index, 0) = val.vsxval[0];
		VCPU_VSX_FPR(vcpu, index, 1) = val.vsxval[0];
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_vsr_word(काष्ठा kvm_vcpu *vcpu,
	u32 gpr32)
अणु
	जोड़ kvmppc_one_reg val;
	पूर्णांक offset = kvmppc_get_vsr_word_offset(vcpu->arch.mmio_vsx_offset);
	पूर्णांक index = vcpu->arch.io_gpr & KVM_MMIO_REG_MASK;
	पूर्णांक dword_offset, word_offset;

	अगर (offset == -1)
		वापस;

	अगर (index >= 32) अणु
		val.vval = VCPU_VSX_VR(vcpu, index - 32);
		val.vsx32val[offset] = gpr32;
		VCPU_VSX_VR(vcpu, index - 32) = val.vval;
	पूर्ण अन्यथा अणु
		dword_offset = offset / 2;
		word_offset = offset % 2;
		val.vsxval[0] = VCPU_VSX_FPR(vcpu, index, dword_offset);
		val.vsx32val[word_offset] = gpr32;
		VCPU_VSX_FPR(vcpu, index, dword_offset) = val.vsxval[0];
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित CONFIG_ALTIVEC
अटल अंतरभूत पूर्णांक kvmppc_get_vmx_offset_generic(काष्ठा kvm_vcpu *vcpu,
		पूर्णांक index, पूर्णांक element_size)
अणु
	पूर्णांक offset;
	पूर्णांक elts = माप(vector128)/element_size;

	अगर ((index < 0) || (index >= elts))
		वापस -1;

	अगर (kvmppc_need_byteswap(vcpu))
		offset = elts - index - 1;
	अन्यथा
		offset = index;

	वापस offset;
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_get_vmx_dword_offset(काष्ठा kvm_vcpu *vcpu,
		पूर्णांक index)
अणु
	वापस kvmppc_get_vmx_offset_generic(vcpu, index, 8);
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_get_vmx_word_offset(काष्ठा kvm_vcpu *vcpu,
		पूर्णांक index)
अणु
	वापस kvmppc_get_vmx_offset_generic(vcpu, index, 4);
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_get_vmx_hword_offset(काष्ठा kvm_vcpu *vcpu,
		पूर्णांक index)
अणु
	वापस kvmppc_get_vmx_offset_generic(vcpu, index, 2);
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_get_vmx_byte_offset(काष्ठा kvm_vcpu *vcpu,
		पूर्णांक index)
अणु
	वापस kvmppc_get_vmx_offset_generic(vcpu, index, 1);
पूर्ण


अटल अंतरभूत व्योम kvmppc_set_vmx_dword(काष्ठा kvm_vcpu *vcpu,
	u64 gpr)
अणु
	जोड़ kvmppc_one_reg val;
	पूर्णांक offset = kvmppc_get_vmx_dword_offset(vcpu,
			vcpu->arch.mmio_vmx_offset);
	पूर्णांक index = vcpu->arch.io_gpr & KVM_MMIO_REG_MASK;

	अगर (offset == -1)
		वापस;

	val.vval = VCPU_VSX_VR(vcpu, index);
	val.vsxval[offset] = gpr;
	VCPU_VSX_VR(vcpu, index) = val.vval;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_vmx_word(काष्ठा kvm_vcpu *vcpu,
	u32 gpr32)
अणु
	जोड़ kvmppc_one_reg val;
	पूर्णांक offset = kvmppc_get_vmx_word_offset(vcpu,
			vcpu->arch.mmio_vmx_offset);
	पूर्णांक index = vcpu->arch.io_gpr & KVM_MMIO_REG_MASK;

	अगर (offset == -1)
		वापस;

	val.vval = VCPU_VSX_VR(vcpu, index);
	val.vsx32val[offset] = gpr32;
	VCPU_VSX_VR(vcpu, index) = val.vval;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_vmx_hword(काष्ठा kvm_vcpu *vcpu,
	u16 gpr16)
अणु
	जोड़ kvmppc_one_reg val;
	पूर्णांक offset = kvmppc_get_vmx_hword_offset(vcpu,
			vcpu->arch.mmio_vmx_offset);
	पूर्णांक index = vcpu->arch.io_gpr & KVM_MMIO_REG_MASK;

	अगर (offset == -1)
		वापस;

	val.vval = VCPU_VSX_VR(vcpu, index);
	val.vsx16val[offset] = gpr16;
	VCPU_VSX_VR(vcpu, index) = val.vval;
पूर्ण

अटल अंतरभूत व्योम kvmppc_set_vmx_byte(काष्ठा kvm_vcpu *vcpu,
	u8 gpr8)
अणु
	जोड़ kvmppc_one_reg val;
	पूर्णांक offset = kvmppc_get_vmx_byte_offset(vcpu,
			vcpu->arch.mmio_vmx_offset);
	पूर्णांक index = vcpu->arch.io_gpr & KVM_MMIO_REG_MASK;

	अगर (offset == -1)
		वापस;

	val.vval = VCPU_VSX_VR(vcpu, index);
	val.vsx8val[offset] = gpr8;
	VCPU_VSX_VR(vcpu, index) = val.vval;
पूर्ण
#पूर्ण_अगर /* CONFIG_ALTIVEC */

#अगर_घोषित CONFIG_PPC_FPU
अटल अंतरभूत u64 sp_to_dp(u32 fprs)
अणु
	u64 fprd;

	preempt_disable();
	enable_kernel_fp();
	यंत्र ("lfs%U1%X1 0,%1; stfd%U0%X0 0,%0" : "=m"UPD_CONSTR (fprd) : "m"UPD_CONSTR (fprs)
	     : "fr0");
	preempt_enable();
	वापस fprd;
पूर्ण

अटल अंतरभूत u32 dp_to_sp(u64 fprd)
अणु
	u32 fprs;

	preempt_disable();
	enable_kernel_fp();
	यंत्र ("lfd%U1%X1 0,%1; stfs%U0%X0 0,%0" : "=m"UPD_CONSTR (fprs) : "m"UPD_CONSTR (fprd)
	     : "fr0");
	preempt_enable();
	वापस fprs;
पूर्ण

#अन्यथा
#घोषणा sp_to_dp(x)	(x)
#घोषणा dp_to_sp(x)	(x)
#पूर्ण_अगर /* CONFIG_PPC_FPU */

अटल व्योम kvmppc_complete_mmio_load(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	u64 gpr;

	अगर (run->mmio.len > माप(gpr)) अणु
		prपूर्णांकk(KERN_ERR "bad MMIO length: %d\n", run->mmio.len);
		वापस;
	पूर्ण

	अगर (!vcpu->arch.mmio_host_swabbed) अणु
		चयन (run->mmio.len) अणु
		हाल 8: gpr = *(u64 *)run->mmio.data; अवरोध;
		हाल 4: gpr = *(u32 *)run->mmio.data; अवरोध;
		हाल 2: gpr = *(u16 *)run->mmio.data; अवरोध;
		हाल 1: gpr = *(u8 *)run->mmio.data; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (run->mmio.len) अणु
		हाल 8: gpr = swab64(*(u64 *)run->mmio.data); अवरोध;
		हाल 4: gpr = swab32(*(u32 *)run->mmio.data); अवरोध;
		हाल 2: gpr = swab16(*(u16 *)run->mmio.data); अवरोध;
		हाल 1: gpr = *(u8 *)run->mmio.data; अवरोध;
		पूर्ण
	पूर्ण

	/* conversion between single and द्विगुन precision */
	अगर ((vcpu->arch.mmio_sp64_extend) && (run->mmio.len == 4))
		gpr = sp_to_dp(gpr);

	अगर (vcpu->arch.mmio_sign_extend) अणु
		चयन (run->mmio.len) अणु
#अगर_घोषित CONFIG_PPC64
		हाल 4:
			gpr = (s64)(s32)gpr;
			अवरोध;
#पूर्ण_अगर
		हाल 2:
			gpr = (s64)(s16)gpr;
			अवरोध;
		हाल 1:
			gpr = (s64)(s8)gpr;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (vcpu->arch.io_gpr & KVM_MMIO_REG_EXT_MASK) अणु
	हाल KVM_MMIO_REG_GPR:
		kvmppc_set_gpr(vcpu, vcpu->arch.io_gpr, gpr);
		अवरोध;
	हाल KVM_MMIO_REG_FPR:
		अगर (vcpu->kvm->arch.kvm_ops->giveup_ext)
			vcpu->kvm->arch.kvm_ops->giveup_ext(vcpu, MSR_FP);

		VCPU_FPR(vcpu, vcpu->arch.io_gpr & KVM_MMIO_REG_MASK) = gpr;
		अवरोध;
#अगर_घोषित CONFIG_PPC_BOOK3S
	हाल KVM_MMIO_REG_QPR:
		vcpu->arch.qpr[vcpu->arch.io_gpr & KVM_MMIO_REG_MASK] = gpr;
		अवरोध;
	हाल KVM_MMIO_REG_FQPR:
		VCPU_FPR(vcpu, vcpu->arch.io_gpr & KVM_MMIO_REG_MASK) = gpr;
		vcpu->arch.qpr[vcpu->arch.io_gpr & KVM_MMIO_REG_MASK] = gpr;
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	हाल KVM_MMIO_REG_VSX:
		अगर (vcpu->kvm->arch.kvm_ops->giveup_ext)
			vcpu->kvm->arch.kvm_ops->giveup_ext(vcpu, MSR_VSX);

		अगर (vcpu->arch.mmio_copy_type == KVMPPC_VSX_COPY_DWORD)
			kvmppc_set_vsr_dword(vcpu, gpr);
		अन्यथा अगर (vcpu->arch.mmio_copy_type == KVMPPC_VSX_COPY_WORD)
			kvmppc_set_vsr_word(vcpu, gpr);
		अन्यथा अगर (vcpu->arch.mmio_copy_type ==
				KVMPPC_VSX_COPY_DWORD_LOAD_DUMP)
			kvmppc_set_vsr_dword_dump(vcpu, gpr);
		अन्यथा अगर (vcpu->arch.mmio_copy_type ==
				KVMPPC_VSX_COPY_WORD_LOAD_DUMP)
			kvmppc_set_vsr_word_dump(vcpu, gpr);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	हाल KVM_MMIO_REG_VMX:
		अगर (vcpu->kvm->arch.kvm_ops->giveup_ext)
			vcpu->kvm->arch.kvm_ops->giveup_ext(vcpu, MSR_VEC);

		अगर (vcpu->arch.mmio_copy_type == KVMPPC_VMX_COPY_DWORD)
			kvmppc_set_vmx_dword(vcpu, gpr);
		अन्यथा अगर (vcpu->arch.mmio_copy_type == KVMPPC_VMX_COPY_WORD)
			kvmppc_set_vmx_word(vcpu, gpr);
		अन्यथा अगर (vcpu->arch.mmio_copy_type ==
				KVMPPC_VMX_COPY_HWORD)
			kvmppc_set_vmx_hword(vcpu, gpr);
		अन्यथा अगर (vcpu->arch.mmio_copy_type ==
				KVMPPC_VMX_COPY_BYTE)
			kvmppc_set_vmx_byte(vcpu, gpr);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	हाल KVM_MMIO_REG_NESTED_GPR:
		अगर (kvmppc_need_byteswap(vcpu))
			gpr = swab64(gpr);
		kvm_vcpu_ग_लिखो_guest(vcpu, vcpu->arch.nested_io_gpr, &gpr,
				     माप(gpr));
		अवरोध;
#पूर्ण_अगर
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल पूर्णांक __kvmppc_handle_load(काष्ठा kvm_vcpu *vcpu,
				अचिन्हित पूर्णांक rt, अचिन्हित पूर्णांक bytes,
				पूर्णांक is_शेष_endian, पूर्णांक sign_extend)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक idx, ret;
	bool host_swabbed;

	/* Pity C करोesn't have a logical XOR चालक */
	अगर (kvmppc_need_byteswap(vcpu)) अणु
		host_swabbed = is_शेष_endian;
	पूर्ण अन्यथा अणु
		host_swabbed = !is_शेष_endian;
	पूर्ण

	अगर (bytes > माप(run->mmio.data)) अणु
		prपूर्णांकk(KERN_ERR "%s: bad MMIO length: %d\n", __func__,
		       run->mmio.len);
	पूर्ण

	run->mmio.phys_addr = vcpu->arch.paddr_accessed;
	run->mmio.len = bytes;
	run->mmio.is_ग_लिखो = 0;

	vcpu->arch.io_gpr = rt;
	vcpu->arch.mmio_host_swabbed = host_swabbed;
	vcpu->mmio_needed = 1;
	vcpu->mmio_is_ग_लिखो = 0;
	vcpu->arch.mmio_sign_extend = sign_extend;

	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	ret = kvm_io_bus_पढ़ो(vcpu, KVM_MMIO_BUS, run->mmio.phys_addr,
			      bytes, &run->mmio.data);

	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);

	अगर (!ret) अणु
		kvmppc_complete_mmio_load(vcpu);
		vcpu->mmio_needed = 0;
		वापस EMULATE_DONE;
	पूर्ण

	वापस EMULATE_DO_MMIO;
पूर्ण

पूर्णांक kvmppc_handle_load(काष्ठा kvm_vcpu *vcpu,
		       अचिन्हित पूर्णांक rt, अचिन्हित पूर्णांक bytes,
		       पूर्णांक is_शेष_endian)
अणु
	वापस __kvmppc_handle_load(vcpu, rt, bytes, is_शेष_endian, 0);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_handle_load);

/* Same as above, but sign extends */
पूर्णांक kvmppc_handle_loads(काष्ठा kvm_vcpu *vcpu,
			अचिन्हित पूर्णांक rt, अचिन्हित पूर्णांक bytes,
			पूर्णांक is_शेष_endian)
अणु
	वापस __kvmppc_handle_load(vcpu, rt, bytes, is_शेष_endian, 1);
पूर्ण

#अगर_घोषित CONFIG_VSX
पूर्णांक kvmppc_handle_vsx_load(काष्ठा kvm_vcpu *vcpu,
			अचिन्हित पूर्णांक rt, अचिन्हित पूर्णांक bytes,
			पूर्णांक is_शेष_endian, पूर्णांक mmio_sign_extend)
अणु
	क्रमागत emulation_result emulated = EMULATE_DONE;

	/* Currently, mmio_vsx_copy_nums only allowed to be 4 or less */
	अगर (vcpu->arch.mmio_vsx_copy_nums > 4)
		वापस EMULATE_FAIL;

	जबतक (vcpu->arch.mmio_vsx_copy_nums) अणु
		emulated = __kvmppc_handle_load(vcpu, rt, bytes,
			is_शेष_endian, mmio_sign_extend);

		अगर (emulated != EMULATE_DONE)
			अवरोध;

		vcpu->arch.paddr_accessed += vcpu->run->mmio.len;

		vcpu->arch.mmio_vsx_copy_nums--;
		vcpu->arch.mmio_vsx_offset++;
	पूर्ण
	वापस emulated;
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

पूर्णांक kvmppc_handle_store(काष्ठा kvm_vcpu *vcpu,
			u64 val, अचिन्हित पूर्णांक bytes, पूर्णांक is_शेष_endian)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	व्योम *data = run->mmio.data;
	पूर्णांक idx, ret;
	bool host_swabbed;

	/* Pity C करोesn't have a logical XOR चालक */
	अगर (kvmppc_need_byteswap(vcpu)) अणु
		host_swabbed = is_शेष_endian;
	पूर्ण अन्यथा अणु
		host_swabbed = !is_शेष_endian;
	पूर्ण

	अगर (bytes > माप(run->mmio.data)) अणु
		prपूर्णांकk(KERN_ERR "%s: bad MMIO length: %d\n", __func__,
		       run->mmio.len);
	पूर्ण

	run->mmio.phys_addr = vcpu->arch.paddr_accessed;
	run->mmio.len = bytes;
	run->mmio.is_ग_लिखो = 1;
	vcpu->mmio_needed = 1;
	vcpu->mmio_is_ग_लिखो = 1;

	अगर ((vcpu->arch.mmio_sp64_extend) && (bytes == 4))
		val = dp_to_sp(val);

	/* Store the value at the lowest bytes in 'data'. */
	अगर (!host_swabbed) अणु
		चयन (bytes) अणु
		हाल 8: *(u64 *)data = val; अवरोध;
		हाल 4: *(u32 *)data = val; अवरोध;
		हाल 2: *(u16 *)data = val; अवरोध;
		हाल 1: *(u8  *)data = val; अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (bytes) अणु
		हाल 8: *(u64 *)data = swab64(val); अवरोध;
		हाल 4: *(u32 *)data = swab32(val); अवरोध;
		हाल 2: *(u16 *)data = swab16(val); अवरोध;
		हाल 1: *(u8  *)data = val; अवरोध;
		पूर्ण
	पूर्ण

	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	ret = kvm_io_bus_ग_लिखो(vcpu, KVM_MMIO_BUS, run->mmio.phys_addr,
			       bytes, &run->mmio.data);

	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);

	अगर (!ret) अणु
		vcpu->mmio_needed = 0;
		वापस EMULATE_DONE;
	पूर्ण

	वापस EMULATE_DO_MMIO;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_handle_store);

#अगर_घोषित CONFIG_VSX
अटल अंतरभूत पूर्णांक kvmppc_get_vsr_data(काष्ठा kvm_vcpu *vcpu, पूर्णांक rs, u64 *val)
अणु
	u32 dword_offset, word_offset;
	जोड़ kvmppc_one_reg reg;
	पूर्णांक vsx_offset = 0;
	पूर्णांक copy_type = vcpu->arch.mmio_copy_type;
	पूर्णांक result = 0;

	चयन (copy_type) अणु
	हाल KVMPPC_VSX_COPY_DWORD:
		vsx_offset =
			kvmppc_get_vsr_dword_offset(vcpu->arch.mmio_vsx_offset);

		अगर (vsx_offset == -1) अणु
			result = -1;
			अवरोध;
		पूर्ण

		अगर (rs < 32) अणु
			*val = VCPU_VSX_FPR(vcpu, rs, vsx_offset);
		पूर्ण अन्यथा अणु
			reg.vval = VCPU_VSX_VR(vcpu, rs - 32);
			*val = reg.vsxval[vsx_offset];
		पूर्ण
		अवरोध;

	हाल KVMPPC_VSX_COPY_WORD:
		vsx_offset =
			kvmppc_get_vsr_word_offset(vcpu->arch.mmio_vsx_offset);

		अगर (vsx_offset == -1) अणु
			result = -1;
			अवरोध;
		पूर्ण

		अगर (rs < 32) अणु
			dword_offset = vsx_offset / 2;
			word_offset = vsx_offset % 2;
			reg.vsxval[0] = VCPU_VSX_FPR(vcpu, rs, dword_offset);
			*val = reg.vsx32val[word_offset];
		पूर्ण अन्यथा अणु
			reg.vval = VCPU_VSX_VR(vcpu, rs - 32);
			*val = reg.vsx32val[vsx_offset];
		पूर्ण
		अवरोध;

	शेष:
		result = -1;
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

पूर्णांक kvmppc_handle_vsx_store(काष्ठा kvm_vcpu *vcpu,
			पूर्णांक rs, अचिन्हित पूर्णांक bytes, पूर्णांक is_शेष_endian)
अणु
	u64 val;
	क्रमागत emulation_result emulated = EMULATE_DONE;

	vcpu->arch.io_gpr = rs;

	/* Currently, mmio_vsx_copy_nums only allowed to be 4 or less */
	अगर (vcpu->arch.mmio_vsx_copy_nums > 4)
		वापस EMULATE_FAIL;

	जबतक (vcpu->arch.mmio_vsx_copy_nums) अणु
		अगर (kvmppc_get_vsr_data(vcpu, rs, &val) == -1)
			वापस EMULATE_FAIL;

		emulated = kvmppc_handle_store(vcpu,
			 val, bytes, is_शेष_endian);

		अगर (emulated != EMULATE_DONE)
			अवरोध;

		vcpu->arch.paddr_accessed += vcpu->run->mmio.len;

		vcpu->arch.mmio_vsx_copy_nums--;
		vcpu->arch.mmio_vsx_offset++;
	पूर्ण

	वापस emulated;
पूर्ण

अटल पूर्णांक kvmppc_emulate_mmio_vsx_loadstore(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	क्रमागत emulation_result emulated = EMULATE_FAIL;
	पूर्णांक r;

	vcpu->arch.paddr_accessed += run->mmio.len;

	अगर (!vcpu->mmio_is_ग_लिखो) अणु
		emulated = kvmppc_handle_vsx_load(vcpu, vcpu->arch.io_gpr,
			 run->mmio.len, 1, vcpu->arch.mmio_sign_extend);
	पूर्ण अन्यथा अणु
		emulated = kvmppc_handle_vsx_store(vcpu,
			 vcpu->arch.io_gpr, run->mmio.len, 1);
	पूर्ण

	चयन (emulated) अणु
	हाल EMULATE_DO_MMIO:
		run->निकास_reason = KVM_EXIT_MMIO;
		r = RESUME_HOST;
		अवरोध;
	हाल EMULATE_FAIL:
		pr_info("KVM: MMIO emulation failed (VSX repeat)\n");
		run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		r = RESUME_HOST;
		अवरोध;
	शेष:
		r = RESUME_GUEST;
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित CONFIG_ALTIVEC
पूर्णांक kvmppc_handle_vmx_load(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित पूर्णांक rt, अचिन्हित पूर्णांक bytes, पूर्णांक is_शेष_endian)
अणु
	क्रमागत emulation_result emulated = EMULATE_DONE;

	अगर (vcpu->arch.mmio_vsx_copy_nums > 2)
		वापस EMULATE_FAIL;

	जबतक (vcpu->arch.mmio_vmx_copy_nums) अणु
		emulated = __kvmppc_handle_load(vcpu, rt, bytes,
				is_शेष_endian, 0);

		अगर (emulated != EMULATE_DONE)
			अवरोध;

		vcpu->arch.paddr_accessed += vcpu->run->mmio.len;
		vcpu->arch.mmio_vmx_copy_nums--;
		vcpu->arch.mmio_vmx_offset++;
	पूर्ण

	वापस emulated;
पूर्ण

अटल पूर्णांक kvmppc_get_vmx_dword(काष्ठा kvm_vcpu *vcpu, पूर्णांक index, u64 *val)
अणु
	जोड़ kvmppc_one_reg reg;
	पूर्णांक vmx_offset = 0;
	पूर्णांक result = 0;

	vmx_offset =
		kvmppc_get_vmx_dword_offset(vcpu, vcpu->arch.mmio_vmx_offset);

	अगर (vmx_offset == -1)
		वापस -1;

	reg.vval = VCPU_VSX_VR(vcpu, index);
	*val = reg.vsxval[vmx_offset];

	वापस result;
पूर्ण

अटल पूर्णांक kvmppc_get_vmx_word(काष्ठा kvm_vcpu *vcpu, पूर्णांक index, u64 *val)
अणु
	जोड़ kvmppc_one_reg reg;
	पूर्णांक vmx_offset = 0;
	पूर्णांक result = 0;

	vmx_offset =
		kvmppc_get_vmx_word_offset(vcpu, vcpu->arch.mmio_vmx_offset);

	अगर (vmx_offset == -1)
		वापस -1;

	reg.vval = VCPU_VSX_VR(vcpu, index);
	*val = reg.vsx32val[vmx_offset];

	वापस result;
पूर्ण

अटल पूर्णांक kvmppc_get_vmx_hword(काष्ठा kvm_vcpu *vcpu, पूर्णांक index, u64 *val)
अणु
	जोड़ kvmppc_one_reg reg;
	पूर्णांक vmx_offset = 0;
	पूर्णांक result = 0;

	vmx_offset =
		kvmppc_get_vmx_hword_offset(vcpu, vcpu->arch.mmio_vmx_offset);

	अगर (vmx_offset == -1)
		वापस -1;

	reg.vval = VCPU_VSX_VR(vcpu, index);
	*val = reg.vsx16val[vmx_offset];

	वापस result;
पूर्ण

अटल पूर्णांक kvmppc_get_vmx_byte(काष्ठा kvm_vcpu *vcpu, पूर्णांक index, u64 *val)
अणु
	जोड़ kvmppc_one_reg reg;
	पूर्णांक vmx_offset = 0;
	पूर्णांक result = 0;

	vmx_offset =
		kvmppc_get_vmx_byte_offset(vcpu, vcpu->arch.mmio_vmx_offset);

	अगर (vmx_offset == -1)
		वापस -1;

	reg.vval = VCPU_VSX_VR(vcpu, index);
	*val = reg.vsx8val[vmx_offset];

	वापस result;
पूर्ण

पूर्णांक kvmppc_handle_vmx_store(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित पूर्णांक rs, अचिन्हित पूर्णांक bytes, पूर्णांक is_शेष_endian)
अणु
	u64 val = 0;
	अचिन्हित पूर्णांक index = rs & KVM_MMIO_REG_MASK;
	क्रमागत emulation_result emulated = EMULATE_DONE;

	अगर (vcpu->arch.mmio_vsx_copy_nums > 2)
		वापस EMULATE_FAIL;

	vcpu->arch.io_gpr = rs;

	जबतक (vcpu->arch.mmio_vmx_copy_nums) अणु
		चयन (vcpu->arch.mmio_copy_type) अणु
		हाल KVMPPC_VMX_COPY_DWORD:
			अगर (kvmppc_get_vmx_dword(vcpu, index, &val) == -1)
				वापस EMULATE_FAIL;

			अवरोध;
		हाल KVMPPC_VMX_COPY_WORD:
			अगर (kvmppc_get_vmx_word(vcpu, index, &val) == -1)
				वापस EMULATE_FAIL;
			अवरोध;
		हाल KVMPPC_VMX_COPY_HWORD:
			अगर (kvmppc_get_vmx_hword(vcpu, index, &val) == -1)
				वापस EMULATE_FAIL;
			अवरोध;
		हाल KVMPPC_VMX_COPY_BYTE:
			अगर (kvmppc_get_vmx_byte(vcpu, index, &val) == -1)
				वापस EMULATE_FAIL;
			अवरोध;
		शेष:
			वापस EMULATE_FAIL;
		पूर्ण

		emulated = kvmppc_handle_store(vcpu, val, bytes,
				is_शेष_endian);
		अगर (emulated != EMULATE_DONE)
			अवरोध;

		vcpu->arch.paddr_accessed += vcpu->run->mmio.len;
		vcpu->arch.mmio_vmx_copy_nums--;
		vcpu->arch.mmio_vmx_offset++;
	पूर्ण

	वापस emulated;
पूर्ण

अटल पूर्णांक kvmppc_emulate_mmio_vmx_loadstore(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	क्रमागत emulation_result emulated = EMULATE_FAIL;
	पूर्णांक r;

	vcpu->arch.paddr_accessed += run->mmio.len;

	अगर (!vcpu->mmio_is_ग_लिखो) अणु
		emulated = kvmppc_handle_vmx_load(vcpu,
				vcpu->arch.io_gpr, run->mmio.len, 1);
	पूर्ण अन्यथा अणु
		emulated = kvmppc_handle_vmx_store(vcpu,
				vcpu->arch.io_gpr, run->mmio.len, 1);
	पूर्ण

	चयन (emulated) अणु
	हाल EMULATE_DO_MMIO:
		run->निकास_reason = KVM_EXIT_MMIO;
		r = RESUME_HOST;
		अवरोध;
	हाल EMULATE_FAIL:
		pr_info("KVM: MMIO emulation failed (VMX repeat)\n");
		run->निकास_reason = KVM_EXIT_INTERNAL_ERROR;
		run->पूर्णांकernal.suberror = KVM_INTERNAL_ERROR_EMULATION;
		r = RESUME_HOST;
		अवरोध;
	शेष:
		r = RESUME_GUEST;
		अवरोध;
	पूर्ण
	वापस r;
पूर्ण
#पूर्ण_अगर /* CONFIG_ALTIVEC */

पूर्णांक kvm_vcpu_ioctl_get_one_reg(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_one_reg *reg)
अणु
	पूर्णांक r = 0;
	जोड़ kvmppc_one_reg val;
	पूर्णांक size;

	size = one_reg_size(reg->id);
	अगर (size > माप(val))
		वापस -EINVAL;

	r = kvmppc_get_one_reg(vcpu, reg->id, &val);
	अगर (r == -EINVAL) अणु
		r = 0;
		चयन (reg->id) अणु
#अगर_घोषित CONFIG_ALTIVEC
		हाल KVM_REG_PPC_VR0 ... KVM_REG_PPC_VR31:
			अगर (!cpu_has_feature(CPU_FTR_ALTIVEC)) अणु
				r = -ENXIO;
				अवरोध;
			पूर्ण
			val.vval = vcpu->arch.vr.vr[reg->id - KVM_REG_PPC_VR0];
			अवरोध;
		हाल KVM_REG_PPC_VSCR:
			अगर (!cpu_has_feature(CPU_FTR_ALTIVEC)) अणु
				r = -ENXIO;
				अवरोध;
			पूर्ण
			val = get_reg_val(reg->id, vcpu->arch.vr.vscr.u[3]);
			अवरोध;
		हाल KVM_REG_PPC_VRSAVE:
			val = get_reg_val(reg->id, vcpu->arch.vrsave);
			अवरोध;
#पूर्ण_अगर /* CONFIG_ALTIVEC */
		शेष:
			r = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (r)
		वापस r;

	अगर (copy_to_user((अक्षर __user *)(अचिन्हित दीर्घ)reg->addr, &val, size))
		r = -EFAULT;

	वापस r;
पूर्ण

पूर्णांक kvm_vcpu_ioctl_set_one_reg(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_one_reg *reg)
अणु
	पूर्णांक r;
	जोड़ kvmppc_one_reg val;
	पूर्णांक size;

	size = one_reg_size(reg->id);
	अगर (size > माप(val))
		वापस -EINVAL;

	अगर (copy_from_user(&val, (अक्षर __user *)(अचिन्हित दीर्घ)reg->addr, size))
		वापस -EFAULT;

	r = kvmppc_set_one_reg(vcpu, reg->id, &val);
	अगर (r == -EINVAL) अणु
		r = 0;
		चयन (reg->id) अणु
#अगर_घोषित CONFIG_ALTIVEC
		हाल KVM_REG_PPC_VR0 ... KVM_REG_PPC_VR31:
			अगर (!cpu_has_feature(CPU_FTR_ALTIVEC)) अणु
				r = -ENXIO;
				अवरोध;
			पूर्ण
			vcpu->arch.vr.vr[reg->id - KVM_REG_PPC_VR0] = val.vval;
			अवरोध;
		हाल KVM_REG_PPC_VSCR:
			अगर (!cpu_has_feature(CPU_FTR_ALTIVEC)) अणु
				r = -ENXIO;
				अवरोध;
			पूर्ण
			vcpu->arch.vr.vscr.u[3] = set_reg_val(reg->id, val);
			अवरोध;
		हाल KVM_REG_PPC_VRSAVE:
			अगर (!cpu_has_feature(CPU_FTR_ALTIVEC)) अणु
				r = -ENXIO;
				अवरोध;
			पूर्ण
			vcpu->arch.vrsave = set_reg_val(reg->id, val);
			अवरोध;
#पूर्ण_अगर /* CONFIG_ALTIVEC */
		शेष:
			r = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_run(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm_run *run = vcpu->run;
	पूर्णांक r;

	vcpu_load(vcpu);

	अगर (vcpu->mmio_needed) अणु
		vcpu->mmio_needed = 0;
		अगर (!vcpu->mmio_is_ग_लिखो)
			kvmppc_complete_mmio_load(vcpu);
#अगर_घोषित CONFIG_VSX
		अगर (vcpu->arch.mmio_vsx_copy_nums > 0) अणु
			vcpu->arch.mmio_vsx_copy_nums--;
			vcpu->arch.mmio_vsx_offset++;
		पूर्ण

		अगर (vcpu->arch.mmio_vsx_copy_nums > 0) अणु
			r = kvmppc_emulate_mmio_vsx_loadstore(vcpu);
			अगर (r == RESUME_HOST) अणु
				vcpu->mmio_needed = 1;
				जाओ out;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
		अगर (vcpu->arch.mmio_vmx_copy_nums > 0) अणु
			vcpu->arch.mmio_vmx_copy_nums--;
			vcpu->arch.mmio_vmx_offset++;
		पूर्ण

		अगर (vcpu->arch.mmio_vmx_copy_nums > 0) अणु
			r = kvmppc_emulate_mmio_vmx_loadstore(vcpu);
			अगर (r == RESUME_HOST) अणु
				vcpu->mmio_needed = 1;
				जाओ out;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (vcpu->arch.osi_needed) अणु
		u64 *gprs = run->osi.gprs;
		पूर्णांक i;

		क्रम (i = 0; i < 32; i++)
			kvmppc_set_gpr(vcpu, i, gprs[i]);
		vcpu->arch.osi_needed = 0;
	पूर्ण अन्यथा अगर (vcpu->arch.hcall_needed) अणु
		पूर्णांक i;

		kvmppc_set_gpr(vcpu, 3, run->papr_hcall.ret);
		क्रम (i = 0; i < 9; ++i)
			kvmppc_set_gpr(vcpu, 4 + i, run->papr_hcall.args[i]);
		vcpu->arch.hcall_needed = 0;
#अगर_घोषित CONFIG_BOOKE
	पूर्ण अन्यथा अगर (vcpu->arch.epr_needed) अणु
		kvmppc_set_epr(vcpu, run->epr.epr);
		vcpu->arch.epr_needed = 0;
#पूर्ण_अगर
	पूर्ण

	kvm_sigset_activate(vcpu);

	अगर (run->immediate_निकास)
		r = -EINTR;
	अन्यथा
		r = kvmppc_vcpu_run(vcpu);

	kvm_sigset_deactivate(vcpu);

#अगर_घोषित CONFIG_ALTIVEC
out:
#पूर्ण_अगर
	vcpu_put(vcpu);
	वापस r;
पूर्ण

पूर्णांक kvm_vcpu_ioctl_पूर्णांकerrupt(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_पूर्णांकerrupt *irq)
अणु
	अगर (irq->irq == KVM_INTERRUPT_UNSET) अणु
		kvmppc_core_dequeue_बाह्यal(vcpu);
		वापस 0;
	पूर्ण

	kvmppc_core_queue_बाह्यal(vcpu, irq);

	kvm_vcpu_kick(vcpu);

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_vcpu_ioctl_enable_cap(काष्ठा kvm_vcpu *vcpu,
				     काष्ठा kvm_enable_cap *cap)
अणु
	पूर्णांक r;

	अगर (cap->flags)
		वापस -EINVAL;

	चयन (cap->cap) अणु
	हाल KVM_CAP_PPC_OSI:
		r = 0;
		vcpu->arch.osi_enabled = true;
		अवरोध;
	हाल KVM_CAP_PPC_PAPR:
		r = 0;
		vcpu->arch.papr_enabled = true;
		अवरोध;
	हाल KVM_CAP_PPC_EPR:
		r = 0;
		अगर (cap->args[0])
			vcpu->arch.epr_flags |= KVMPPC_EPR_USER;
		अन्यथा
			vcpu->arch.epr_flags &= ~KVMPPC_EPR_USER;
		अवरोध;
#अगर_घोषित CONFIG_BOOKE
	हाल KVM_CAP_PPC_BOOKE_WATCHDOG:
		r = 0;
		vcpu->arch.watchकरोg_enabled = true;
		अवरोध;
#पूर्ण_अगर
#अगर defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	हाल KVM_CAP_SW_TLB: अणु
		काष्ठा kvm_config_tlb cfg;
		व्योम __user *user_ptr = (व्योम __user *)(uपूर्णांकptr_t)cap->args[0];

		r = -EFAULT;
		अगर (copy_from_user(&cfg, user_ptr, माप(cfg)))
			अवरोध;

		r = kvm_vcpu_ioctl_config_tlb(vcpu, &cfg);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_MPIC
	हाल KVM_CAP_IRQ_MPIC: अणु
		काष्ठा fd f;
		काष्ठा kvm_device *dev;

		r = -EBADF;
		f = fdget(cap->args[0]);
		अगर (!f.file)
			अवरोध;

		r = -EPERM;
		dev = kvm_device_from_filp(f.file);
		अगर (dev)
			r = kvmppc_mpic_connect_vcpu(dev, vcpu, cap->args[1]);

		fdput(f);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_XICS
	हाल KVM_CAP_IRQ_XICS: अणु
		काष्ठा fd f;
		काष्ठा kvm_device *dev;

		r = -EBADF;
		f = fdget(cap->args[0]);
		अगर (!f.file)
			अवरोध;

		r = -EPERM;
		dev = kvm_device_from_filp(f.file);
		अगर (dev) अणु
			अगर (xics_on_xive())
				r = kvmppc_xive_connect_vcpu(dev, vcpu, cap->args[1]);
			अन्यथा
				r = kvmppc_xics_connect_vcpu(dev, vcpu, cap->args[1]);
		पूर्ण

		fdput(f);
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_XICS */
#अगर_घोषित CONFIG_KVM_XIVE
	हाल KVM_CAP_PPC_IRQ_XIVE: अणु
		काष्ठा fd f;
		काष्ठा kvm_device *dev;

		r = -EBADF;
		f = fdget(cap->args[0]);
		अगर (!f.file)
			अवरोध;

		r = -ENXIO;
		अगर (!xive_enabled())
			अवरोध;

		r = -EPERM;
		dev = kvm_device_from_filp(f.file);
		अगर (dev)
			r = kvmppc_xive_native_connect_vcpu(dev, vcpu,
							    cap->args[1]);

		fdput(f);
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* CONFIG_KVM_XIVE */
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	हाल KVM_CAP_PPC_FWNMI:
		r = -EINVAL;
		अगर (!is_kvmppc_hv_enabled(vcpu->kvm))
			अवरोध;
		r = 0;
		vcpu->kvm->arch.fwnmi_enabled = true;
		अवरोध;
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_HV_POSSIBLE */
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (!r)
		r = kvmppc_sanity_check(vcpu);

	वापस r;
पूर्ण

bool kvm_arch_पूर्णांकc_initialized(काष्ठा kvm *kvm)
अणु
#अगर_घोषित CONFIG_KVM_MPIC
	अगर (kvm->arch.mpic)
		वापस true;
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_XICS
	अगर (kvm->arch.xics || kvm->arch.xive)
		वापस true;
#पूर्ण_अगर
	वापस false;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_get_mpstate(काष्ठा kvm_vcpu *vcpu,
                                    काष्ठा kvm_mp_state *mp_state)
अणु
	वापस -EINVAL;
पूर्ण

पूर्णांक kvm_arch_vcpu_ioctl_set_mpstate(काष्ठा kvm_vcpu *vcpu,
                                    काष्ठा kvm_mp_state *mp_state)
अणु
	वापस -EINVAL;
पूर्ण

दीर्घ kvm_arch_vcpu_async_ioctl(काष्ठा file *filp,
			       अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (ioctl == KVM_INTERRUPT) अणु
		काष्ठा kvm_पूर्णांकerrupt irq;
		अगर (copy_from_user(&irq, argp, माप(irq)))
			वापस -EFAULT;
		वापस kvm_vcpu_ioctl_पूर्णांकerrupt(vcpu, &irq);
	पूर्ण
	वापस -ENOIOCTLCMD;
पूर्ण

दीर्घ kvm_arch_vcpu_ioctl(काष्ठा file *filp,
                         अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm_vcpu *vcpu = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	दीर्घ r;

	चयन (ioctl) अणु
	हाल KVM_ENABLE_CAP:
	अणु
		काष्ठा kvm_enable_cap cap;
		r = -EFAULT;
		vcpu_load(vcpu);
		अगर (copy_from_user(&cap, argp, माप(cap)))
			जाओ out;
		r = kvm_vcpu_ioctl_enable_cap(vcpu, &cap);
		vcpu_put(vcpu);
		अवरोध;
	पूर्ण

	हाल KVM_SET_ONE_REG:
	हाल KVM_GET_ONE_REG:
	अणु
		काष्ठा kvm_one_reg reg;
		r = -EFAULT;
		अगर (copy_from_user(&reg, argp, माप(reg)))
			जाओ out;
		अगर (ioctl == KVM_SET_ONE_REG)
			r = kvm_vcpu_ioctl_set_one_reg(vcpu, &reg);
		अन्यथा
			r = kvm_vcpu_ioctl_get_one_reg(vcpu, &reg);
		अवरोध;
	पूर्ण

#अगर defined(CONFIG_KVM_E500V2) || defined(CONFIG_KVM_E500MC)
	हाल KVM_सूचीTY_TLB: अणु
		काष्ठा kvm_dirty_tlb dirty;
		r = -EFAULT;
		vcpu_load(vcpu);
		अगर (copy_from_user(&dirty, argp, माप(dirty)))
			जाओ out;
		r = kvm_vcpu_ioctl_dirty_tlb(vcpu, &dirty);
		vcpu_put(vcpu);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		r = -EINVAL;
	पूर्ण

out:
	वापस r;
पूर्ण

vm_fault_t kvm_arch_vcpu_fault(काष्ठा kvm_vcpu *vcpu, काष्ठा vm_fault *vmf)
अणु
	वापस VM_FAULT_SIGBUS;
पूर्ण

अटल पूर्णांक kvm_vm_ioctl_get_pvinfo(काष्ठा kvm_ppc_pvinfo *pvinfo)
अणु
	u32 inst_nop = 0x60000000;
#अगर_घोषित CONFIG_KVM_BOOKE_HV
	u32 inst_sc1 = 0x44000022;
	pvinfo->hcall[0] = cpu_to_be32(inst_sc1);
	pvinfo->hcall[1] = cpu_to_be32(inst_nop);
	pvinfo->hcall[2] = cpu_to_be32(inst_nop);
	pvinfo->hcall[3] = cpu_to_be32(inst_nop);
#अन्यथा
	u32 inst_lis = 0x3c000000;
	u32 inst_ori = 0x60000000;
	u32 inst_sc = 0x44000002;
	u32 inst_imm_mask = 0xffff;

	/*
	 * The hypercall to get पूर्णांकo KVM from within guest context is as
	 * follows:
	 *
	 *    lis r0, r0, KVM_SC_MAGIC_R0@h
	 *    ori r0, KVM_SC_MAGIC_R0@l
	 *    sc
	 *    nop
	 */
	pvinfo->hcall[0] = cpu_to_be32(inst_lis | ((KVM_SC_MAGIC_R0 >> 16) & inst_imm_mask));
	pvinfo->hcall[1] = cpu_to_be32(inst_ori | (KVM_SC_MAGIC_R0 & inst_imm_mask));
	pvinfo->hcall[2] = cpu_to_be32(inst_sc);
	pvinfo->hcall[3] = cpu_to_be32(inst_nop);
#पूर्ण_अगर

	pvinfo->flags = KVM_PPC_PVINFO_FLAGS_EV_IDLE;

	वापस 0;
पूर्ण

पूर्णांक kvm_vm_ioctl_irq_line(काष्ठा kvm *kvm, काष्ठा kvm_irq_level *irq_event,
			  bool line_status)
अणु
	अगर (!irqchip_in_kernel(kvm))
		वापस -ENXIO;

	irq_event->status = kvm_set_irq(kvm, KVM_USERSPACE_IRQ_SOURCE_ID,
					irq_event->irq, irq_event->level,
					line_status);
	वापस 0;
पूर्ण


पूर्णांक kvm_vm_ioctl_enable_cap(काष्ठा kvm *kvm,
			    काष्ठा kvm_enable_cap *cap)
अणु
	पूर्णांक r;

	अगर (cap->flags)
		वापस -EINVAL;

	चयन (cap->cap) अणु
#अगर_घोषित CONFIG_KVM_BOOK3S_64_HANDLER
	हाल KVM_CAP_PPC_ENABLE_HCALL: अणु
		अचिन्हित दीर्घ hcall = cap->args[0];

		r = -EINVAL;
		अगर (hcall > MAX_HCALL_OPCODE || (hcall & 3) ||
		    cap->args[1] > 1)
			अवरोध;
		अगर (!kvmppc_book3s_hcall_implemented(kvm, hcall))
			अवरोध;
		अगर (cap->args[1])
			set_bit(hcall / 4, kvm->arch.enabled_hcalls);
		अन्यथा
			clear_bit(hcall / 4, kvm->arch.enabled_hcalls);
		r = 0;
		अवरोध;
	पूर्ण
	हाल KVM_CAP_PPC_SMT: अणु
		अचिन्हित दीर्घ mode = cap->args[0];
		अचिन्हित दीर्घ flags = cap->args[1];

		r = -EINVAL;
		अगर (kvm->arch.kvm_ops->set_smt_mode)
			r = kvm->arch.kvm_ops->set_smt_mode(kvm, mode, flags);
		अवरोध;
	पूर्ण

	हाल KVM_CAP_PPC_NESTED_HV:
		r = -EINVAL;
		अगर (!is_kvmppc_hv_enabled(kvm) ||
		    !kvm->arch.kvm_ops->enable_nested)
			अवरोध;
		r = kvm->arch.kvm_ops->enable_nested(kvm);
		अवरोध;
#पूर्ण_अगर
#अगर defined(CONFIG_KVM_BOOK3S_HV_POSSIBLE)
	हाल KVM_CAP_PPC_SECURE_GUEST:
		r = -EINVAL;
		अगर (!is_kvmppc_hv_enabled(kvm) || !kvm->arch.kvm_ops->enable_svm)
			अवरोध;
		r = kvm->arch.kvm_ops->enable_svm(kvm);
		अवरोध;
	हाल KVM_CAP_PPC_DAWR1:
		r = -EINVAL;
		अगर (!is_kvmppc_hv_enabled(kvm) || !kvm->arch.kvm_ops->enable_dawr1)
			अवरोध;
		r = kvm->arch.kvm_ops->enable_dawr1(kvm);
		अवरोध;
#पूर्ण_अगर
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
/*
 * These functions check whether the underlying hardware is safe
 * against attacks based on observing the effects of speculatively
 * executed inकाष्ठाions, and whether it supplies inकाष्ठाions क्रम
 * use in workarounds.  The inक्रमmation comes from firmware, either
 * via the device tree on घातernv platक्रमms or from an hcall on
 * pseries platक्रमms.
 */
#अगर_घोषित CONFIG_PPC_PSERIES
अटल पूर्णांक pseries_get_cpu_अक्षर(काष्ठा kvm_ppc_cpu_अक्षर *cp)
अणु
	काष्ठा h_cpu_अक्षर_result c;
	अचिन्हित दीर्घ rc;

	अगर (!machine_is(pseries))
		वापस -ENOTTY;

	rc = plpar_get_cpu_अक्षरacteristics(&c);
	अगर (rc == H_SUCCESS) अणु
		cp->अक्षरacter = c.अक्षरacter;
		cp->behaviour = c.behaviour;
		cp->अक्षरacter_mask = KVM_PPC_CPU_CHAR_SPEC_BAR_ORI31 |
			KVM_PPC_CPU_CHAR_BCCTRL_SERIALISED |
			KVM_PPC_CPU_CHAR_L1D_FLUSH_ORI30 |
			KVM_PPC_CPU_CHAR_L1D_FLUSH_TRIG2 |
			KVM_PPC_CPU_CHAR_L1D_THREAD_PRIV |
			KVM_PPC_CPU_CHAR_BR_HINT_HONOURED |
			KVM_PPC_CPU_CHAR_MTTRIG_THR_RECONF |
			KVM_PPC_CPU_CHAR_COUNT_CACHE_DIS |
			KVM_PPC_CPU_CHAR_BCCTR_FLUSH_ASSIST;
		cp->behaviour_mask = KVM_PPC_CPU_BEHAV_FAVOUR_SECURITY |
			KVM_PPC_CPU_BEHAV_L1D_FLUSH_PR |
			KVM_PPC_CPU_BEHAV_BNDS_CHK_SPEC_BAR |
			KVM_PPC_CPU_BEHAV_FLUSH_COUNT_CACHE;
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक pseries_get_cpu_अक्षर(काष्ठा kvm_ppc_cpu_अक्षर *cp)
अणु
	वापस -ENOTTY;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool have_fw_feat(काष्ठा device_node *fw_features,
				स्थिर अक्षर *state, स्थिर अक्षर *name)
अणु
	काष्ठा device_node *np;
	bool r = false;

	np = of_get_child_by_name(fw_features, name);
	अगर (np) अणु
		r = of_property_पढ़ो_bool(np, state);
		of_node_put(np);
	पूर्ण
	वापस r;
पूर्ण

अटल पूर्णांक kvmppc_get_cpu_अक्षर(काष्ठा kvm_ppc_cpu_अक्षर *cp)
अणु
	काष्ठा device_node *np, *fw_features;
	पूर्णांक r;

	स_रखो(cp, 0, माप(*cp));
	r = pseries_get_cpu_अक्षर(cp);
	अगर (r != -ENOTTY)
		वापस r;

	np = of_find_node_by_name(शून्य, "ibm,opal");
	अगर (np) अणु
		fw_features = of_get_child_by_name(np, "fw-features");
		of_node_put(np);
		अगर (!fw_features)
			वापस 0;
		अगर (have_fw_feat(fw_features, "enabled",
				 "inst-spec-barrier-ori31,31,0"))
			cp->अक्षरacter |= KVM_PPC_CPU_CHAR_SPEC_BAR_ORI31;
		अगर (have_fw_feat(fw_features, "enabled",
				 "fw-bcctrl-serialized"))
			cp->अक्षरacter |= KVM_PPC_CPU_CHAR_BCCTRL_SERIALISED;
		अगर (have_fw_feat(fw_features, "enabled",
				 "inst-l1d-flush-ori30,30,0"))
			cp->अक्षरacter |= KVM_PPC_CPU_CHAR_L1D_FLUSH_ORI30;
		अगर (have_fw_feat(fw_features, "enabled",
				 "inst-l1d-flush-trig2"))
			cp->अक्षरacter |= KVM_PPC_CPU_CHAR_L1D_FLUSH_TRIG2;
		अगर (have_fw_feat(fw_features, "enabled",
				 "fw-l1d-thread-split"))
			cp->अक्षरacter |= KVM_PPC_CPU_CHAR_L1D_THREAD_PRIV;
		अगर (have_fw_feat(fw_features, "enabled",
				 "fw-count-cache-disabled"))
			cp->अक्षरacter |= KVM_PPC_CPU_CHAR_COUNT_CACHE_DIS;
		अगर (have_fw_feat(fw_features, "enabled",
				 "fw-count-cache-flush-bcctr2,0,0"))
			cp->अक्षरacter |= KVM_PPC_CPU_CHAR_BCCTR_FLUSH_ASSIST;
		cp->अक्षरacter_mask = KVM_PPC_CPU_CHAR_SPEC_BAR_ORI31 |
			KVM_PPC_CPU_CHAR_BCCTRL_SERIALISED |
			KVM_PPC_CPU_CHAR_L1D_FLUSH_ORI30 |
			KVM_PPC_CPU_CHAR_L1D_FLUSH_TRIG2 |
			KVM_PPC_CPU_CHAR_L1D_THREAD_PRIV |
			KVM_PPC_CPU_CHAR_COUNT_CACHE_DIS |
			KVM_PPC_CPU_CHAR_BCCTR_FLUSH_ASSIST;

		अगर (have_fw_feat(fw_features, "enabled",
				 "speculation-policy-favor-security"))
			cp->behaviour |= KVM_PPC_CPU_BEHAV_FAVOUR_SECURITY;
		अगर (!have_fw_feat(fw_features, "disabled",
				  "needs-l1d-flush-msr-pr-0-to-1"))
			cp->behaviour |= KVM_PPC_CPU_BEHAV_L1D_FLUSH_PR;
		अगर (!have_fw_feat(fw_features, "disabled",
				  "needs-spec-barrier-for-bound-checks"))
			cp->behaviour |= KVM_PPC_CPU_BEHAV_BNDS_CHK_SPEC_BAR;
		अगर (have_fw_feat(fw_features, "enabled",
				 "needs-count-cache-flush-on-context-switch"))
			cp->behaviour |= KVM_PPC_CPU_BEHAV_FLUSH_COUNT_CACHE;
		cp->behaviour_mask = KVM_PPC_CPU_BEHAV_FAVOUR_SECURITY |
			KVM_PPC_CPU_BEHAV_L1D_FLUSH_PR |
			KVM_PPC_CPU_BEHAV_BNDS_CHK_SPEC_BAR |
			KVM_PPC_CPU_BEHAV_FLUSH_COUNT_CACHE;

		of_node_put(fw_features);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

दीर्घ kvm_arch_vm_ioctl(काष्ठा file *filp,
                       अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा kvm *kvm __maybe_unused = filp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	दीर्घ r;

	चयन (ioctl) अणु
	हाल KVM_PPC_GET_PVINFO: अणु
		काष्ठा kvm_ppc_pvinfo pvinfo;
		स_रखो(&pvinfo, 0, माप(pvinfo));
		r = kvm_vm_ioctl_get_pvinfo(&pvinfo);
		अगर (copy_to_user(argp, &pvinfo, माप(pvinfo))) अणु
			r = -EFAULT;
			जाओ out;
		पूर्ण

		अवरोध;
	पूर्ण
#अगर_घोषित CONFIG_SPAPR_TCE_IOMMU
	हाल KVM_CREATE_SPAPR_TCE_64: अणु
		काष्ठा kvm_create_spapr_tce_64 create_tce_64;

		r = -EFAULT;
		अगर (copy_from_user(&create_tce_64, argp, माप(create_tce_64)))
			जाओ out;
		अगर (create_tce_64.flags) अणु
			r = -EINVAL;
			जाओ out;
		पूर्ण
		r = kvm_vm_ioctl_create_spapr_tce(kvm, &create_tce_64);
		जाओ out;
	पूर्ण
	हाल KVM_CREATE_SPAPR_TCE: अणु
		काष्ठा kvm_create_spapr_tce create_tce;
		काष्ठा kvm_create_spapr_tce_64 create_tce_64;

		r = -EFAULT;
		अगर (copy_from_user(&create_tce, argp, माप(create_tce)))
			जाओ out;

		create_tce_64.liobn = create_tce.liobn;
		create_tce_64.page_shअगरt = IOMMU_PAGE_SHIFT_4K;
		create_tce_64.offset = 0;
		create_tce_64.size = create_tce.winकरोw_size >>
				IOMMU_PAGE_SHIFT_4K;
		create_tce_64.flags = 0;
		r = kvm_vm_ioctl_create_spapr_tce(kvm, &create_tce_64);
		जाओ out;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	हाल KVM_PPC_GET_SMMU_INFO: अणु
		काष्ठा kvm_ppc_smmu_info info;
		काष्ठा kvm *kvm = filp->निजी_data;

		स_रखो(&info, 0, माप(info));
		r = kvm->arch.kvm_ops->get_smmu_info(kvm, &info);
		अगर (r >= 0 && copy_to_user(argp, &info, माप(info)))
			r = -EFAULT;
		अवरोध;
	पूर्ण
	हाल KVM_PPC_RTAS_DEFINE_TOKEN: अणु
		काष्ठा kvm *kvm = filp->निजी_data;

		r = kvm_vm_ioctl_rtas_define_token(kvm, argp);
		अवरोध;
	पूर्ण
	हाल KVM_PPC_CONFIGURE_V3_MMU: अणु
		काष्ठा kvm *kvm = filp->निजी_data;
		काष्ठा kvm_ppc_mmuv3_cfg cfg;

		r = -EINVAL;
		अगर (!kvm->arch.kvm_ops->configure_mmu)
			जाओ out;
		r = -EFAULT;
		अगर (copy_from_user(&cfg, argp, माप(cfg)))
			जाओ out;
		r = kvm->arch.kvm_ops->configure_mmu(kvm, &cfg);
		अवरोध;
	पूर्ण
	हाल KVM_PPC_GET_RMMU_INFO: अणु
		काष्ठा kvm *kvm = filp->निजी_data;
		काष्ठा kvm_ppc_rmmu_info info;

		r = -EINVAL;
		अगर (!kvm->arch.kvm_ops->get_rmmu_info)
			जाओ out;
		r = kvm->arch.kvm_ops->get_rmmu_info(kvm, &info);
		अगर (r >= 0 && copy_to_user(argp, &info, माप(info)))
			r = -EFAULT;
		अवरोध;
	पूर्ण
	हाल KVM_PPC_GET_CPU_CHAR: अणु
		काष्ठा kvm_ppc_cpu_अक्षर cpuअक्षर;

		r = kvmppc_get_cpu_अक्षर(&cpuअक्षर);
		अगर (r >= 0 && copy_to_user(argp, &cpuअक्षर, माप(cpuअक्षर)))
			r = -EFAULT;
		अवरोध;
	पूर्ण
	हाल KVM_PPC_SVM_OFF: अणु
		काष्ठा kvm *kvm = filp->निजी_data;

		r = 0;
		अगर (!kvm->arch.kvm_ops->svm_off)
			जाओ out;

		r = kvm->arch.kvm_ops->svm_off(kvm);
		अवरोध;
	पूर्ण
	शेष: अणु
		काष्ठा kvm *kvm = filp->निजी_data;
		r = kvm->arch.kvm_ops->arch_vm_ioctl(filp, ioctl, arg);
	पूर्ण
#अन्यथा /* CONFIG_PPC_BOOK3S_64 */
	शेष:
		r = -ENOTTY;
#पूर्ण_अगर
	पूर्ण
out:
	वापस r;
पूर्ण

अटल अचिन्हित दीर्घ lpid_inuse[BITS_TO_LONGS(KVMPPC_NR_LPIDS)];
अटल अचिन्हित दीर्घ nr_lpids;

दीर्घ kvmppc_alloc_lpid(व्योम)
अणु
	दीर्घ lpid;

	करो अणु
		lpid = find_first_zero_bit(lpid_inuse, KVMPPC_NR_LPIDS);
		अगर (lpid >= nr_lpids) अणु
			pr_err("%s: No LPIDs free\n", __func__);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण जबतक (test_and_set_bit(lpid, lpid_inuse));

	वापस lpid;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_alloc_lpid);

व्योम kvmppc_claim_lpid(दीर्घ lpid)
अणु
	set_bit(lpid, lpid_inuse);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_claim_lpid);

व्योम kvmppc_मुक्त_lpid(दीर्घ lpid)
अणु
	clear_bit(lpid, lpid_inuse);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_मुक्त_lpid);

व्योम kvmppc_init_lpid(अचिन्हित दीर्घ nr_lpids_param)
अणु
	nr_lpids = min_t(अचिन्हित दीर्घ, KVMPPC_NR_LPIDS, nr_lpids_param);
	स_रखो(lpid_inuse, 0, माप(lpid_inuse));
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_init_lpid);

पूर्णांक kvm_arch_init(व्योम *opaque)
अणु
	वापस 0;
पूर्ण

EXPORT_TRACEPOINT_SYMBOL_GPL(kvm_ppc_instr);
