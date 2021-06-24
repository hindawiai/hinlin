<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012,2013 - ARM Ltd
 * Author: Marc Zyngier <marc.zyngier@arm.com>
 */

#अगर_अघोषित __ARM64_KVM_MMU_H__
#घोषणा __ARM64_KVM_MMU_H__

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/cpufeature.h>

/*
 * As ARMv8.0 only has the TTBR0_EL2 रेजिस्टर, we cannot express
 * "negative" addresses. This makes it impossible to directly share
 * mappings with the kernel.
 *
 * Instead, give the HYP mode its own VA region at a fixed offset from
 * the kernel by just masking the top bits (which are all ones क्रम a
 * kernel address). We need to find out how many bits to mask.
 *
 * We want to build a set of page tables that cover both parts of the
 * idmap (the trampoline page used to initialize EL2), and our normal
 * runसमय VA space, at the same समय.
 *
 * Given that the kernel uses VA_BITS क्रम its entire address space,
 * and that half of that space (VA_BITS - 1) is used क्रम the linear
 * mapping, we can also limit the EL2 space to (VA_BITS - 1).
 *
 * The मुख्य question is "Within the VA_BITS space, करोes EL2 use the
 * top or the bottom half of that space to shaकरोw the kernel's linear
 * mapping?". As we need to idmap the trampoline page, this is
 * determined by the range in which this page lives.
 *
 * If the page is in the bottom half, we have to use the top half. If
 * the page is in the top half, we have to use the bottom half:
 *
 * T = __pa_symbol(__hyp_idmap_text_start)
 * अगर (T & BIT(VA_BITS - 1))
 *	HYP_VA_MIN = 0  //idmap in upper half
 * अन्यथा
 *	HYP_VA_MIN = 1 << (VA_BITS - 1)
 * HYP_VA_MAX = HYP_VA_MIN + (1 << (VA_BITS - 1)) - 1
 *
 * When using VHE, there are no separate hyp mappings and all KVM
 * functionality is alपढ़ोy mapped as part of the मुख्य kernel
 * mappings, and none of this applies in that हाल.
 */

#अगर_घोषित __ASSEMBLY__

#समावेश <यंत्र/alternative.h>

/*
 * Convert a kernel VA पूर्णांकo a HYP VA.
 * reg: VA to be converted.
 *
 * The actual code generation takes place in kvm_update_va_mask, and
 * the inकाष्ठाions below are only there to reserve the space and
 * perक्रमm the रेजिस्टर allocation (kvm_update_va_mask uses the
 * specअगरic रेजिस्टरs encoded in the inकाष्ठाions).
 */
.macro kern_hyp_va	reg
alternative_cb kvm_update_va_mask
	and     \लeg, \लeg, #1		/* mask with va_mask */
	ror	\लeg, \लeg, #1		/* rotate to the first tag bit */
	add	\लeg, \लeg, #0		/* insert the low 12 bits of the tag */
	add	\लeg, \लeg, #0, lsl 12	/* insert the top 12 bits of the tag */
	ror	\लeg, \लeg, #63		/* rotate back */
alternative_cb_end
.endm

/*
 * Convert a hypervisor VA to a PA
 * reg: hypervisor address to be converted in place
 * पंचांगp: temporary रेजिस्टर
 */
.macro hyp_pa reg, पंचांगp
	ldr_l	\टmp, hyp_physvirt_offset
	add	\लeg, \लeg, \टmp
.endm

/*
 * Convert a hypervisor VA to a kernel image address
 * reg: hypervisor address to be converted in place
 * पंचांगp: temporary रेजिस्टर
 *
 * The actual code generation takes place in kvm_get_kimage_voffset, and
 * the inकाष्ठाions below are only there to reserve the space and
 * perक्रमm the रेजिस्टर allocation (kvm_get_kimage_voffset uses the
 * specअगरic रेजिस्टरs encoded in the inकाष्ठाions).
 */
.macro hyp_kimg_va reg, पंचांगp
	/* Convert hyp VA -> PA. */
	hyp_pa	\लeg, \टmp

	/* Load kimage_voffset. */
alternative_cb kvm_get_kimage_voffset
	movz	\टmp, #0
	movk	\टmp, #0, lsl #16
	movk	\टmp, #0, lsl #32
	movk	\टmp, #0, lsl #48
alternative_cb_end

	/* Convert PA -> kimg VA. */
	add	\लeg, \लeg, \टmp
.endm

#अन्यथा

#समावेश <linux/pgtable.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mmu_context.h>

व्योम kvm_update_va_mask(काष्ठा alt_instr *alt,
			__le32 *origptr, __le32 *updptr, पूर्णांक nr_inst);
व्योम kvm_compute_layout(व्योम);
व्योम kvm_apply_hyp_relocations(व्योम);

#घोषणा __hyp_pa(x) (((phys_addr_t)(x)) + hyp_physvirt_offset)

अटल __always_अंतरभूत अचिन्हित दीर्घ __kern_hyp_va(अचिन्हित दीर्घ v)
अणु
	यंत्र अस्थिर(ALTERNATIVE_CB("and %0, %0, #1\n"
				    "ror %0, %0, #1\n"
				    "add %0, %0, #0\n"
				    "add %0, %0, #0, lsl 12\n"
				    "ror %0, %0, #63\n",
				    kvm_update_va_mask)
		     : "+r" (v));
	वापस v;
पूर्ण

#घोषणा kern_hyp_va(v) 	((typeof(v))(__kern_hyp_va((अचिन्हित दीर्घ)(v))))

/*
 * We currently support using a VM-specअगरied IPA size. For backward
 * compatibility, the शेष IPA size is fixed to 40bits.
 */
#घोषणा KVM_PHYS_SHIFT	(40)

#घोषणा kvm_phys_shअगरt(kvm)		VTCR_EL2_IPA(kvm->arch.vtcr)
#घोषणा kvm_phys_size(kvm)		(_AC(1, ULL) << kvm_phys_shअगरt(kvm))
#घोषणा kvm_phys_mask(kvm)		(kvm_phys_size(kvm) - _AC(1, ULL))

#समावेश <यंत्र/kvm_pgtable.h>
#समावेश <यंत्र/stage2_pgtable.h>

पूर्णांक create_hyp_mappings(व्योम *from, व्योम *to, क्रमागत kvm_pgtable_prot prot);
पूर्णांक create_hyp_io_mappings(phys_addr_t phys_addr, माप_प्रकार size,
			   व्योम __iomem **kaddr,
			   व्योम __iomem **haddr);
पूर्णांक create_hyp_exec_mappings(phys_addr_t phys_addr, माप_प्रकार size,
			     व्योम **haddr);
व्योम मुक्त_hyp_pgds(व्योम);

व्योम stage2_unmap_vm(काष्ठा kvm *kvm);
पूर्णांक kvm_init_stage2_mmu(काष्ठा kvm *kvm, काष्ठा kvm_s2_mmu *mmu);
व्योम kvm_मुक्त_stage2_pgd(काष्ठा kvm_s2_mmu *mmu);
पूर्णांक kvm_phys_addr_ioremap(काष्ठा kvm *kvm, phys_addr_t guest_ipa,
			  phys_addr_t pa, अचिन्हित दीर्घ size, bool writable);

पूर्णांक kvm_handle_guest_पात(काष्ठा kvm_vcpu *vcpu);

phys_addr_t kvm_mmu_get_httbr(व्योम);
phys_addr_t kvm_get_idmap_vector(व्योम);
पूर्णांक kvm_mmu_init(u32 *hyp_va_bits);

अटल अंतरभूत व्योम *__kvm_vector_slot2addr(व्योम *base,
					   क्रमागत arm64_hyp_spectre_vector slot)
अणु
	पूर्णांक idx = slot - (slot != HYP_VECTOR_सूचीECT);

	वापस base + (idx * SZ_2K);
पूर्ण

काष्ठा kvm;

#घोषणा kvm_flush_dcache_to_poc(a,l)	__flush_dcache_area((a), (l))

अटल अंतरभूत bool vcpu_has_cache_enabled(काष्ठा kvm_vcpu *vcpu)
अणु
	वापस (vcpu_पढ़ो_sys_reg(vcpu, SCTLR_EL1) & 0b101) == 0b101;
पूर्ण

अटल अंतरभूत व्योम __clean_dcache_guest_page(kvm_pfn_t pfn, अचिन्हित दीर्घ size)
अणु
	व्योम *va = page_address(pfn_to_page(pfn));

	/*
	 * With FWB, we ensure that the guest always accesses memory using
	 * cacheable attributes, and we करोn't have to clean to PoC when
	 * faulting in pages. Furthermore, FWB implies IDC, so cleaning to
	 * PoU is not required either in this हाल.
	 */
	अगर (cpus_have_स्थिर_cap(ARM64_HAS_STAGE2_FWB))
		वापस;

	kvm_flush_dcache_to_poc(va, size);
पूर्ण

अटल अंतरभूत व्योम __invalidate_icache_guest_page(kvm_pfn_t pfn,
						  अचिन्हित दीर्घ size)
अणु
	अगर (icache_is_aliasing()) अणु
		/* any kind of VIPT cache */
		__flush_icache_all();
	पूर्ण अन्यथा अगर (is_kernel_in_hyp_mode() || !icache_is_vpipt()) अणु
		/* PIPT or VPIPT at EL2 (see comment in __kvm_tlb_flush_vmid_ipa) */
		व्योम *va = page_address(pfn_to_page(pfn));

		invalidate_icache_range((अचिन्हित दीर्घ)va,
					(अचिन्हित दीर्घ)va + size);
	पूर्ण
पूर्ण

व्योम kvm_set_way_flush(काष्ठा kvm_vcpu *vcpu);
व्योम kvm_toggle_cache(काष्ठा kvm_vcpu *vcpu, bool was_enabled);

अटल अंतरभूत अचिन्हित पूर्णांक kvm_get_vmid_bits(व्योम)
अणु
	पूर्णांक reg = पढ़ो_sanitised_ftr_reg(SYS_ID_AA64MMFR1_EL1);

	वापस get_vmid_bits(reg);
पूर्ण

/*
 * We are not in the kvm->srcu critical section most of the समय, so we take
 * the SRCU पढ़ो lock here. Since we copy the data from the user page, we
 * can immediately drop the lock again.
 */
अटल अंतरभूत पूर्णांक kvm_पढ़ो_guest_lock(काष्ठा kvm *kvm,
				      gpa_t gpa, व्योम *data, अचिन्हित दीर्घ len)
अणु
	पूर्णांक srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	पूर्णांक ret = kvm_पढ़ो_guest(kvm, gpa, data, len);

	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक kvm_ग_लिखो_guest_lock(काष्ठा kvm *kvm, gpa_t gpa,
				       स्थिर व्योम *data, अचिन्हित दीर्घ len)
अणु
	पूर्णांक srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	पूर्णांक ret = kvm_ग_लिखो_guest(kvm, gpa, data, len);

	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);

	वापस ret;
पूर्ण

#घोषणा kvm_phys_to_vttbr(addr)		phys_to_ttbr(addr)

अटल __always_अंतरभूत u64 kvm_get_vttbr(काष्ठा kvm_s2_mmu *mmu)
अणु
	काष्ठा kvm_vmid *vmid = &mmu->vmid;
	u64 vmid_field, baddr;
	u64 cnp = प्रणाली_supports_cnp() ? VTTBR_CNP_BIT : 0;

	baddr = mmu->pgd_phys;
	vmid_field = (u64)vmid->vmid << VTTBR_VMID_SHIFT;
	वापस kvm_phys_to_vttbr(baddr) | vmid_field | cnp;
पूर्ण

/*
 * Must be called from hyp code running at EL2 with an updated VTTBR
 * and पूर्णांकerrupts disabled.
 */
अटल __always_अंतरभूत व्योम __load_stage2(काष्ठा kvm_s2_mmu *mmu, अचिन्हित दीर्घ vtcr)
अणु
	ग_लिखो_sysreg(vtcr, vtcr_el2);
	ग_लिखो_sysreg(kvm_get_vttbr(mmu), vttbr_el2);

	/*
	 * ARM errata 1165522 and 1530923 require the actual execution of the
	 * above beक्रमe we can चयन to the EL1/EL0 translation regime used by
	 * the guest.
	 */
	यंत्र(ALTERNATIVE("nop", "isb", ARM64_WORKAROUND_SPECULATIVE_AT));
पूर्ण

अटल __always_अंतरभूत व्योम __load_guest_stage2(काष्ठा kvm_s2_mmu *mmu)
अणु
	__load_stage2(mmu, kern_hyp_va(mmu->arch)->vtcr);
पूर्ण

अटल अंतरभूत काष्ठा kvm *kvm_s2_mmu_to_kvm(काष्ठा kvm_s2_mmu *mmu)
अणु
	वापस container_of(mmu->arch, काष्ठा kvm, arch);
पूर्ण
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* __ARM64_KVM_MMU_H__ */
