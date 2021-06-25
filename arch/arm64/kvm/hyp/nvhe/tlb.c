<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <nvhe/mem_protect.h>

काष्ठा tlb_inv_context अणु
	u64		tcr;
पूर्ण;

अटल व्योम __tlb_चयन_to_guest(काष्ठा kvm_s2_mmu *mmu,
				  काष्ठा tlb_inv_context *cxt)
अणु
	अगर (cpus_have_final_cap(ARM64_WORKAROUND_SPECULATIVE_AT)) अणु
		u64 val;

		/*
		 * For CPUs that are affected by ARM 1319367, we need to
		 * aव्योम a host Stage-1 walk जबतक we have the guest's
		 * VMID set in the VTTBR in order to invalidate TLBs.
		 * We're guaranteed that the S1 MMU is enabled, so we can
		 * simply set the EPD bits to aव्योम any further TLB fill.
		 */
		val = cxt->tcr = पढ़ो_sysreg_el1(SYS_TCR);
		val |= TCR_EPD1_MASK | TCR_EPD0_MASK;
		ग_लिखो_sysreg_el1(val, SYS_TCR);
		isb();
	पूर्ण

	/*
	 * __load_guest_stage2() includes an ISB only when the AT
	 * workaround is applied. Take care of the opposite condition,
	 * ensuring that we always have an ISB, but not two ISBs back
	 * to back.
	 */
	__load_guest_stage2(mmu);
	यंत्र(ALTERNATIVE("isb", "nop", ARM64_WORKAROUND_SPECULATIVE_AT));
पूर्ण

अटल व्योम __tlb_चयन_to_host(काष्ठा tlb_inv_context *cxt)
अणु
	__load_host_stage2();

	अगर (cpus_have_final_cap(ARM64_WORKAROUND_SPECULATIVE_AT)) अणु
		/* Ensure ग_लिखो of the host VMID */
		isb();
		/* Restore the host's TCR_EL1 */
		ग_लिखो_sysreg_el1(cxt->tcr, SYS_TCR);
	पूर्ण
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

	/*
	 * If the host is running at EL1 and we have a VPIPT I-cache,
	 * then we must perक्रमm I-cache मुख्यtenance at EL2 in order क्रम
	 * it to have an effect on the guest. Since the guest cannot hit
	 * I-cache lines allocated with a dअगरferent VMID, we करोn't need
	 * to worry about junk out of guest reset (we nuke the I-cache on
	 * VMID rollover), but we करो need to be careful when remapping
	 * executable pages क्रम the same guest. This can happen when KSM
	 * takes a CoW fault on an executable page, copies the page पूर्णांकo
	 * a page that was previously mapped in the guest and then needs
	 * to invalidate the guest view of the I-cache क्रम that page
	 * from EL1. To solve this, we invalidate the entire I-cache when
	 * unmapping a page from a guest अगर we have a VPIPT I-cache but
	 * the host is running at EL1. As above, we could करो better अगर
	 * we had the VA.
	 *
	 * The moral of this story is: अगर you have a VPIPT I-cache, then
	 * you should be running with VHE enabled.
	 */
	अगर (icache_is_vpipt())
		__flush_icache_all();

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
