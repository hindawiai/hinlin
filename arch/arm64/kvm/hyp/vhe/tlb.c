<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <linux/irqflags.h>

#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/tlbflush.h>

काष्ठा tlb_inv_context अणु
	अचिन्हित दीर्घ	flags;
	u64		tcr;
	u64		sctlr;
पूर्ण;

अटल व्योम __tlb_चयन_to_guest(काष्ठा kvm_s2_mmu *mmu,
				  काष्ठा tlb_inv_context *cxt)
अणु
	u64 val;

	local_irq_save(cxt->flags);

	अगर (cpus_have_final_cap(ARM64_WORKAROUND_SPECULATIVE_AT)) अणु
		/*
		 * For CPUs that are affected by ARM errata 1165522 or 1530923,
		 * we cannot trust stage-1 to be in a correct state at that
		 * poपूर्णांक. Since we करो not want to क्रमce a full load of the
		 * vcpu state, we prevent the EL1 page-table walker to
		 * allocate new TLBs. This is करोne by setting the EPD bits
		 * in the TCR_EL1 रेजिस्टर. We also need to prevent it to
		 * allocate IPA->PA walks, so we enable the S1 MMU...
		 */
		val = cxt->tcr = पढ़ो_sysreg_el1(SYS_TCR);
		val |= TCR_EPD1_MASK | TCR_EPD0_MASK;
		ग_लिखो_sysreg_el1(val, SYS_TCR);
		val = cxt->sctlr = पढ़ो_sysreg_el1(SYS_SCTLR);
		val |= SCTLR_ELx_M;
		ग_लिखो_sysreg_el1(val, SYS_SCTLR);
	पूर्ण

	/*
	 * With VHE enabled, we have HCR_EL2.अणुE2H,TGEपूर्ण = अणु1,1पूर्ण, and
	 * most TLB operations target EL2/EL0. In order to affect the
	 * guest TLBs (EL1/EL0), we need to change one of these two
	 * bits. Changing E2H is impossible (goodbye TTBR1_EL2), so
	 * let's flip TGE beक्रमe executing the TLB operation.
	 *
	 * ARM erratum 1165522 requires some special handling (again),
	 * as we need to make sure both stages of translation are in
	 * place beक्रमe clearing TGE. __load_guest_stage2() alपढ़ोy
	 * has an ISB in order to deal with this.
	 */
	__load_guest_stage2(mmu);
	val = पढ़ो_sysreg(hcr_el2);
	val &= ~HCR_TGE;
	ग_लिखो_sysreg(val, hcr_el2);
	isb();
पूर्ण

अटल व्योम __tlb_चयन_to_host(काष्ठा tlb_inv_context *cxt)
अणु
	/*
	 * We're done with the TLB operation, let's restore the host's
	 * view of HCR_EL2.
	 */
	ग_लिखो_sysreg(0, vttbr_el2);
	ग_लिखो_sysreg(HCR_HOST_VHE_FLAGS, hcr_el2);
	isb();

	अगर (cpus_have_final_cap(ARM64_WORKAROUND_SPECULATIVE_AT)) अणु
		/* Restore the रेजिस्टरs to what they were */
		ग_लिखो_sysreg_el1(cxt->tcr, SYS_TCR);
		ग_लिखो_sysreg_el1(cxt->sctlr, SYS_SCTLR);
	पूर्ण

	local_irq_restore(cxt->flags);
पूर्ण

व्योम __kvm_tlb_flush_vmid_ipa(काष्ठा kvm_s2_mmu *mmu,
			      phys_addr_t ipa, पूर्णांक level)
अणु
	काष्ठा tlb_inv_context cxt;

	dsb(ishst);

	/* Switch to requested VMID */
	__tlb_चयन_to_guest(mmu, &cxt);

	/*
	 * We could करो so much better अगर we had the VA as well.
	 * Instead, we invalidate Stage-2 क्रम this IPA, and the
	 * whole of Stage-1. Weep...
	 */
	ipa >>= 12;
	__tlbi_level(ipas2e1is, ipa, level);

	/*
	 * We have to ensure completion of the invalidation at Stage-2,
	 * since a table walk on another CPU could refill a TLB with a
	 * complete (S1 + S2) walk based on the old Stage-2 mapping अगर
	 * the Stage-1 invalidation happened first.
	 */
	dsb(ish);
	__tlbi(vmalle1is);
	dsb(ish);
	isb();

	__tlb_चयन_to_host(&cxt);
पूर्ण

व्योम __kvm_tlb_flush_vmid(काष्ठा kvm_s2_mmu *mmu)
अणु
	काष्ठा tlb_inv_context cxt;

	dsb(ishst);

	/* Switch to requested VMID */
	__tlb_चयन_to_guest(mmu, &cxt);

	__tlbi(vmalls12e1is);
	dsb(ish);
	isb();

	__tlb_चयन_to_host(&cxt);
पूर्ण

व्योम __kvm_flush_cpu_context(काष्ठा kvm_s2_mmu *mmu)
अणु
	काष्ठा tlb_inv_context cxt;

	/* Switch to requested VMID */
	__tlb_चयन_to_guest(mmu, &cxt);

	__tlbi(vmalle1);
	यंत्र अस्थिर("ic iallu");
	dsb(nsh);
	isb();

	__tlb_चयन_to_host(&cxt);
पूर्ण

व्योम __kvm_flush_vm_context(व्योम)
अणु
	dsb(ishst);
	__tlbi(alle1is);

	/*
	 * VIPT and PIPT caches are not affected by VMID, so no मुख्यtenance
	 * is necessary across a VMID rollover.
	 *
	 * VPIPT caches स्थिरrain lookup and मुख्यtenance to the active VMID,
	 * so we need to invalidate lines with a stale VMID to aव्योम an ABA
	 * race after multiple rollovers.
	 *
	 */
	अगर (icache_is_vpipt())
		यंत्र अस्थिर("ic ialluis");

	dsb(ish);
पूर्ण
