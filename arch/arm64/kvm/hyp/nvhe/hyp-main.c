<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 - Google Inc
 * Author: Andrew Scull <ascull@google.com>
 */

#समावेश <hyp/चयन.h>

#समावेश <यंत्र/pgtable-types.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_host.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>

#समावेश <nvhe/mem_protect.h>
#समावेश <nvhe/mm.h>
#समावेश <nvhe/trap_handler.h>

DEFINE_PER_CPU(काष्ठा kvm_nvhe_init_params, kvm_init_params);

व्योम __kvm_hyp_host_क्रमward_smc(काष्ठा kvm_cpu_context *host_ctxt);

अटल व्योम handle___kvm_vcpu_run(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(काष्ठा kvm_vcpu *, vcpu, host_ctxt, 1);

	cpu_reg(host_ctxt, 1) =  __kvm_vcpu_run(kern_hyp_va(vcpu));
पूर्ण

अटल व्योम handle___kvm_adjust_pc(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(काष्ठा kvm_vcpu *, vcpu, host_ctxt, 1);

	__kvm_adjust_pc(kern_hyp_va(vcpu));
पूर्ण

अटल व्योम handle___kvm_flush_vm_context(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	__kvm_flush_vm_context();
पूर्ण

अटल व्योम handle___kvm_tlb_flush_vmid_ipa(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(काष्ठा kvm_s2_mmu *, mmu, host_ctxt, 1);
	DECLARE_REG(phys_addr_t, ipa, host_ctxt, 2);
	DECLARE_REG(पूर्णांक, level, host_ctxt, 3);

	__kvm_tlb_flush_vmid_ipa(kern_hyp_va(mmu), ipa, level);
पूर्ण

अटल व्योम handle___kvm_tlb_flush_vmid(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(काष्ठा kvm_s2_mmu *, mmu, host_ctxt, 1);

	__kvm_tlb_flush_vmid(kern_hyp_va(mmu));
पूर्ण

अटल व्योम handle___kvm_flush_cpu_context(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(काष्ठा kvm_s2_mmu *, mmu, host_ctxt, 1);

	__kvm_flush_cpu_context(kern_hyp_va(mmu));
पूर्ण

अटल व्योम handle___kvm_समयr_set_cntvoff(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	__kvm_समयr_set_cntvoff(cpu_reg(host_ctxt, 1));
पूर्ण

अटल व्योम handle___kvm_enable_ssbs(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	u64 पंचांगp;

	पंचांगp = पढ़ो_sysreg_el2(SYS_SCTLR);
	पंचांगp |= SCTLR_ELx_DSSBS;
	ग_लिखो_sysreg_el2(पंचांगp, SYS_SCTLR);
पूर्ण

अटल व्योम handle___vgic_v3_get_gic_config(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	cpu_reg(host_ctxt, 1) = __vgic_v3_get_gic_config();
पूर्ण

अटल व्योम handle___vgic_v3_पढ़ो_vmcr(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	cpu_reg(host_ctxt, 1) = __vgic_v3_पढ़ो_vmcr();
पूर्ण

अटल व्योम handle___vgic_v3_ग_लिखो_vmcr(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	__vgic_v3_ग_लिखो_vmcr(cpu_reg(host_ctxt, 1));
पूर्ण

अटल व्योम handle___vgic_v3_init_lrs(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	__vgic_v3_init_lrs();
पूर्ण

अटल व्योम handle___kvm_get_mdcr_el2(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	cpu_reg(host_ctxt, 1) = __kvm_get_mdcr_el2();
पूर्ण

अटल व्योम handle___vgic_v3_save_aprs(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(काष्ठा vgic_v3_cpu_अगर *, cpu_अगर, host_ctxt, 1);

	__vgic_v3_save_aprs(kern_hyp_va(cpu_अगर));
पूर्ण

अटल व्योम handle___vgic_v3_restore_aprs(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(काष्ठा vgic_v3_cpu_अगर *, cpu_अगर, host_ctxt, 1);

	__vgic_v3_restore_aprs(kern_hyp_va(cpu_अगर));
पूर्ण

अटल व्योम handle___pkvm_init(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(phys_addr_t, phys, host_ctxt, 1);
	DECLARE_REG(अचिन्हित दीर्घ, size, host_ctxt, 2);
	DECLARE_REG(अचिन्हित दीर्घ, nr_cpus, host_ctxt, 3);
	DECLARE_REG(अचिन्हित दीर्घ *, per_cpu_base, host_ctxt, 4);
	DECLARE_REG(u32, hyp_va_bits, host_ctxt, 5);

	/*
	 * __pkvm_init() will वापस only अगर an error occurred, otherwise it
	 * will tail-call in __pkvm_init_finalise() which will have to deal
	 * with the host context directly.
	 */
	cpu_reg(host_ctxt, 1) = __pkvm_init(phys, size, nr_cpus, per_cpu_base,
					    hyp_va_bits);
पूर्ण

अटल व्योम handle___pkvm_cpu_set_vector(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(क्रमागत arm64_hyp_spectre_vector, slot, host_ctxt, 1);

	cpu_reg(host_ctxt, 1) = pkvm_cpu_set_vector(slot);
पूर्ण

अटल व्योम handle___pkvm_create_mappings(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(अचिन्हित दीर्घ, start, host_ctxt, 1);
	DECLARE_REG(अचिन्हित दीर्घ, size, host_ctxt, 2);
	DECLARE_REG(अचिन्हित दीर्घ, phys, host_ctxt, 3);
	DECLARE_REG(क्रमागत kvm_pgtable_prot, prot, host_ctxt, 4);

	cpu_reg(host_ctxt, 1) = __pkvm_create_mappings(start, size, phys, prot);
पूर्ण

अटल व्योम handle___pkvm_create_निजी_mapping(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(phys_addr_t, phys, host_ctxt, 1);
	DECLARE_REG(माप_प्रकार, size, host_ctxt, 2);
	DECLARE_REG(क्रमागत kvm_pgtable_prot, prot, host_ctxt, 3);

	cpu_reg(host_ctxt, 1) = __pkvm_create_निजी_mapping(phys, size, prot);
पूर्ण

अटल व्योम handle___pkvm_prot_finalize(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	cpu_reg(host_ctxt, 1) = __pkvm_prot_finalize();
पूर्ण

अटल व्योम handle___pkvm_mark_hyp(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(phys_addr_t, start, host_ctxt, 1);
	DECLARE_REG(phys_addr_t, end, host_ctxt, 2);

	cpu_reg(host_ctxt, 1) = __pkvm_mark_hyp(start, end);
पूर्ण
प्रकार व्योम (*hcall_t)(काष्ठा kvm_cpu_context *);

#घोषणा HANDLE_FUNC(x)	[__KVM_HOST_SMCCC_FUNC_##x] = (hcall_t)handle_##x

अटल स्थिर hcall_t host_hcall[] = अणु
	HANDLE_FUNC(__kvm_vcpu_run),
	HANDLE_FUNC(__kvm_adjust_pc),
	HANDLE_FUNC(__kvm_flush_vm_context),
	HANDLE_FUNC(__kvm_tlb_flush_vmid_ipa),
	HANDLE_FUNC(__kvm_tlb_flush_vmid),
	HANDLE_FUNC(__kvm_flush_cpu_context),
	HANDLE_FUNC(__kvm_समयr_set_cntvoff),
	HANDLE_FUNC(__kvm_enable_ssbs),
	HANDLE_FUNC(__vgic_v3_get_gic_config),
	HANDLE_FUNC(__vgic_v3_पढ़ो_vmcr),
	HANDLE_FUNC(__vgic_v3_ग_लिखो_vmcr),
	HANDLE_FUNC(__vgic_v3_init_lrs),
	HANDLE_FUNC(__kvm_get_mdcr_el2),
	HANDLE_FUNC(__vgic_v3_save_aprs),
	HANDLE_FUNC(__vgic_v3_restore_aprs),
	HANDLE_FUNC(__pkvm_init),
	HANDLE_FUNC(__pkvm_cpu_set_vector),
	HANDLE_FUNC(__pkvm_create_mappings),
	HANDLE_FUNC(__pkvm_create_निजी_mapping),
	HANDLE_FUNC(__pkvm_prot_finalize),
	HANDLE_FUNC(__pkvm_mark_hyp),
पूर्ण;

अटल व्योम handle_host_hcall(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	DECLARE_REG(अचिन्हित दीर्घ, id, host_ctxt, 0);
	hcall_t hfn;

	id -= KVM_HOST_SMCCC_ID(0);

	अगर (unlikely(id >= ARRAY_SIZE(host_hcall)))
		जाओ inval;

	hfn = host_hcall[id];
	अगर (unlikely(!hfn))
		जाओ inval;

	cpu_reg(host_ctxt, 0) = SMCCC_RET_SUCCESS;
	hfn(host_ctxt);

	वापस;
inval:
	cpu_reg(host_ctxt, 0) = SMCCC_RET_NOT_SUPPORTED;
पूर्ण

अटल व्योम शेष_host_smc_handler(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	__kvm_hyp_host_क्रमward_smc(host_ctxt);
पूर्ण

अटल व्योम handle_host_smc(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	bool handled;

	handled = kvm_host_psci_handler(host_ctxt);
	अगर (!handled)
		शेष_host_smc_handler(host_ctxt);

	/* SMC was trapped, move ELR past the current PC. */
	kvm_skip_host_instr();
पूर्ण

व्योम handle_trap(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	u64 esr = पढ़ो_sysreg_el2(SYS_ESR);

	चयन (ESR_ELx_EC(esr)) अणु
	हाल ESR_ELx_EC_HVC64:
		handle_host_hcall(host_ctxt);
		अवरोध;
	हाल ESR_ELx_EC_SMC64:
		handle_host_smc(host_ctxt);
		अवरोध;
	हाल ESR_ELx_EC_SVE:
		sysreg_clear_set(cptr_el2, CPTR_EL2_TZ, 0);
		isb();
		sve_cond_update_zcr_vq(ZCR_ELx_LEN_MASK, SYS_ZCR_EL2);
		अवरोध;
	हाल ESR_ELx_EC_IABT_LOW:
	हाल ESR_ELx_EC_DABT_LOW:
		handle_host_mem_पात(host_ctxt);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
