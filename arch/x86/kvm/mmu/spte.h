<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#अगर_अघोषित KVM_X86_MMU_SPTE_H
#घोषणा KVM_X86_MMU_SPTE_H

#समावेश "mmu_internal.h"

/*
 * A MMU present SPTE is backed by actual memory and may or may not be present
 * in hardware.  E.g. MMIO SPTEs are not considered present.  Use bit 11, as it
 * is ignored by all flavors of SPTEs and checking a low bit often generates
 * better code than क्रम a high bit, e.g. 56+.  MMU present checks are pervasive
 * enough that the improved code generation is noticeable in KVM's footprपूर्णांक.
 */
#घोषणा SPTE_MMU_PRESENT_MASK		BIT_ULL(11)

/*
 * TDP SPTES (more specअगरically, EPT SPTEs) may not have A/D bits, and may also
 * be restricted to using ग_लिखो-protection (क्रम L2 when CPU dirty logging, i.e.
 * PML, is enabled).  Use bits 52 and 53 to hold the type of A/D tracking that
 * is must be employed क्रम a given TDP SPTE.
 *
 * Note, the "enabled" mask must be '0', as bits 62:52 are _reserved_ क्रम PAE
 * paging, including NPT PAE.  This scheme works because legacy shaकरोw paging
 * is guaranteed to have A/D bits and ग_लिखो-protection is क्रमced only क्रम
 * TDP with CPU dirty logging (PML).  If NPT ever gains PML-like support, it
 * must be restricted to 64-bit KVM.
 */
#घोषणा SPTE_TDP_AD_SHIFT		52
#घोषणा SPTE_TDP_AD_MASK		(3ULL << SPTE_TDP_AD_SHIFT)
#घोषणा SPTE_TDP_AD_ENABLED_MASK	(0ULL << SPTE_TDP_AD_SHIFT)
#घोषणा SPTE_TDP_AD_DISABLED_MASK	(1ULL << SPTE_TDP_AD_SHIFT)
#घोषणा SPTE_TDP_AD_WRPROT_ONLY_MASK	(2ULL << SPTE_TDP_AD_SHIFT)
अटल_निश्चित(SPTE_TDP_AD_ENABLED_MASK == 0);

#अगर_घोषित CONFIG_DYNAMIC_PHYSICAL_MASK
#घोषणा PT64_BASE_ADDR_MASK (physical_mask & ~(u64)(PAGE_SIZE-1))
#अन्यथा
#घोषणा PT64_BASE_ADDR_MASK (((1ULL << 52) - 1) & ~(u64)(PAGE_SIZE-1))
#पूर्ण_अगर
#घोषणा PT64_LVL_ADDR_MASK(level) \
	(PT64_BASE_ADDR_MASK & ~((1ULL << (PAGE_SHIFT + (((level) - 1) \
						* PT64_LEVEL_BITS))) - 1))
#घोषणा PT64_LVL_OFFSET_MASK(level) \
	(PT64_BASE_ADDR_MASK & ((1ULL << (PAGE_SHIFT + (((level) - 1) \
						* PT64_LEVEL_BITS))) - 1))

#घोषणा PT64_PERM_MASK (PT_PRESENT_MASK | PT_WRITABLE_MASK | shaकरोw_user_mask \
			| shaकरोw_x_mask | shaकरोw_nx_mask | shaकरोw_me_mask)

#घोषणा ACC_EXEC_MASK    1
#घोषणा ACC_WRITE_MASK   PT_WRITABLE_MASK
#घोषणा ACC_USER_MASK    PT_USER_MASK
#घोषणा ACC_ALL          (ACC_EXEC_MASK | ACC_WRITE_MASK | ACC_USER_MASK)

/* The mask क्रम the R/X bits in EPT PTEs */
#घोषणा PT64_EPT_READABLE_MASK			0x1ull
#घोषणा PT64_EPT_EXECUTABLE_MASK		0x4ull

#घोषणा PT64_LEVEL_BITS 9

#घोषणा PT64_LEVEL_SHIFT(level) \
		(PAGE_SHIFT + (level - 1) * PT64_LEVEL_BITS)

#घोषणा PT64_INDEX(address, level)\
	(((address) >> PT64_LEVEL_SHIFT(level)) & ((1 << PT64_LEVEL_BITS) - 1))
#घोषणा SHADOW_PT_INDEX(addr, level) PT64_INDEX(addr, level)

/* Bits 9 and 10 are ignored by all non-EPT PTEs. */
#घोषणा DEFAULT_SPTE_HOST_WRITEABLE	BIT_ULL(9)
#घोषणा DEFAULT_SPTE_MMU_WRITEABLE	BIT_ULL(10)

/*
 * The mask/shअगरt to use क्रम saving the original R/X bits when marking the PTE
 * as not-present क्रम access tracking purposes. We करो not save the W bit as the
 * PTEs being access tracked also need to be dirty tracked, so the W bit will be
 * restored only when a ग_लिखो is attempted to the page.  This mask obviously
 * must not overlap the A/D type mask.
 */
#घोषणा SHADOW_ACC_TRACK_SAVED_BITS_MASK (PT64_EPT_READABLE_MASK | \
					  PT64_EPT_EXECUTABLE_MASK)
#घोषणा SHADOW_ACC_TRACK_SAVED_BITS_SHIFT 54
#घोषणा SHADOW_ACC_TRACK_SAVED_MASK	(SHADOW_ACC_TRACK_SAVED_BITS_MASK << \
					 SHADOW_ACC_TRACK_SAVED_BITS_SHIFT)
अटल_निश्चित(!(SPTE_TDP_AD_MASK & SHADOW_ACC_TRACK_SAVED_MASK));

/*
 * Low ignored bits are at a premium क्रम EPT, use high ignored bits, taking care
 * to not overlap the A/D type mask or the saved access bits of access-tracked
 * SPTEs when A/D bits are disabled.
 */
#घोषणा EPT_SPTE_HOST_WRITABLE		BIT_ULL(57)
#घोषणा EPT_SPTE_MMU_WRITABLE		BIT_ULL(58)

अटल_निश्चित(!(EPT_SPTE_HOST_WRITABLE & SPTE_TDP_AD_MASK));
अटल_निश्चित(!(EPT_SPTE_MMU_WRITABLE & SPTE_TDP_AD_MASK));
अटल_निश्चित(!(EPT_SPTE_HOST_WRITABLE & SHADOW_ACC_TRACK_SAVED_MASK));
अटल_निश्चित(!(EPT_SPTE_MMU_WRITABLE & SHADOW_ACC_TRACK_SAVED_MASK));

/* Defined only to keep the above अटल निश्चितs पढ़ोable. */
#अघोषित SHADOW_ACC_TRACK_SAVED_MASK

/*
 * Due to limited space in PTEs, the MMIO generation is a 19 bit subset of
 * the memslots generation and is derived as follows:
 *
 * Bits 0-7 of the MMIO generation are propagated to spte bits 3-10
 * Bits 8-18 of the MMIO generation are propagated to spte bits 52-62
 *
 * The KVM_MEMSLOT_GEN_UPDATE_IN_PROGRESS flag is पूर्णांकentionally not included in
 * the MMIO generation number, as करोing so would require stealing a bit from
 * the "real" generation number and thus effectively halve the maximum number
 * of MMIO generations that can be handled beक्रमe encountering a wrap (which
 * requires a full MMU zap).  The flag is instead explicitly queried when
 * checking क्रम MMIO spte cache hits.
 */

#घोषणा MMIO_SPTE_GEN_LOW_START		3
#घोषणा MMIO_SPTE_GEN_LOW_END		10

#घोषणा MMIO_SPTE_GEN_HIGH_START	52
#घोषणा MMIO_SPTE_GEN_HIGH_END		62

#घोषणा MMIO_SPTE_GEN_LOW_MASK		GENMASK_ULL(MMIO_SPTE_GEN_LOW_END, \
						    MMIO_SPTE_GEN_LOW_START)
#घोषणा MMIO_SPTE_GEN_HIGH_MASK		GENMASK_ULL(MMIO_SPTE_GEN_HIGH_END, \
						    MMIO_SPTE_GEN_HIGH_START)
अटल_निश्चित(!(SPTE_MMU_PRESENT_MASK &
		(MMIO_SPTE_GEN_LOW_MASK | MMIO_SPTE_GEN_HIGH_MASK)));

#घोषणा MMIO_SPTE_GEN_LOW_BITS		(MMIO_SPTE_GEN_LOW_END - MMIO_SPTE_GEN_LOW_START + 1)
#घोषणा MMIO_SPTE_GEN_HIGH_BITS		(MMIO_SPTE_GEN_HIGH_END - MMIO_SPTE_GEN_HIGH_START + 1)

/* remember to adjust the comment above as well अगर you change these */
अटल_निश्चित(MMIO_SPTE_GEN_LOW_BITS == 8 && MMIO_SPTE_GEN_HIGH_BITS == 11);

#घोषणा MMIO_SPTE_GEN_LOW_SHIFT		(MMIO_SPTE_GEN_LOW_START - 0)
#घोषणा MMIO_SPTE_GEN_HIGH_SHIFT	(MMIO_SPTE_GEN_HIGH_START - MMIO_SPTE_GEN_LOW_BITS)

#घोषणा MMIO_SPTE_GEN_MASK		GENMASK_ULL(MMIO_SPTE_GEN_LOW_BITS + MMIO_SPTE_GEN_HIGH_BITS - 1, 0)

बाह्य u64 __पढ़ो_mostly shaकरोw_host_writable_mask;
बाह्य u64 __पढ़ो_mostly shaकरोw_mmu_writable_mask;
बाह्य u64 __पढ़ो_mostly shaकरोw_nx_mask;
बाह्य u64 __पढ़ो_mostly shaकरोw_x_mask; /* mutual exclusive with nx_mask */
बाह्य u64 __पढ़ो_mostly shaकरोw_user_mask;
बाह्य u64 __पढ़ो_mostly shaकरोw_accessed_mask;
बाह्य u64 __पढ़ो_mostly shaकरोw_dirty_mask;
बाह्य u64 __पढ़ो_mostly shaकरोw_mmio_value;
बाह्य u64 __पढ़ो_mostly shaकरोw_mmio_mask;
बाह्य u64 __पढ़ो_mostly shaकरोw_mmio_access_mask;
बाह्य u64 __पढ़ो_mostly shaकरोw_present_mask;
बाह्य u64 __पढ़ो_mostly shaकरोw_me_mask;

/*
 * SPTEs in MMUs without A/D bits are marked with SPTE_TDP_AD_DISABLED_MASK;
 * shaकरोw_acc_track_mask is the set of bits to be cleared in non-accessed
 * pages.
 */
बाह्य u64 __पढ़ो_mostly shaकरोw_acc_track_mask;

/*
 * This mask must be set on all non-zero Non-Present or Reserved SPTEs in order
 * to guard against L1TF attacks.
 */
बाह्य u64 __पढ़ो_mostly shaकरोw_nonpresent_or_rsvd_mask;

/*
 * The number of high-order 1 bits to use in the mask above.
 */
#घोषणा SHADOW_NONPRESENT_OR_RSVD_MASK_LEN 5

/*
 * If a thपढ़ो running without exclusive control of the MMU lock must perक्रमm a
 * multi-part operation on an SPTE, it can set the SPTE to REMOVED_SPTE as a
 * non-present पूर्णांकermediate value. Other thपढ़ोs which encounter this value
 * should not modअगरy the SPTE.
 *
 * Use a semi-arbitrary value that करोesn't set RWX bits, i.e. is not-present on
 * bot AMD and Intel CPUs, and करोesn't set PFN bits, i.e. doesn't create a L1TF
 * vulnerability.  Use only low bits to aव्योम 64-bit immediates.
 *
 * Only used by the TDP MMU.
 */
#घोषणा REMOVED_SPTE	0x5a0ULL

/* Removed SPTEs must not be misस्थिरrued as shaकरोw present PTEs. */
अटल_निश्चित(!(REMOVED_SPTE & SPTE_MMU_PRESENT_MASK));

अटल अंतरभूत bool is_हटाओd_spte(u64 spte)
अणु
	वापस spte == REMOVED_SPTE;
पूर्ण

/*
 * In some हालs, we need to preserve the GFN of a non-present or reserved
 * SPTE when we usurp the upper five bits of the physical address space to
 * defend against L1TF, e.g. क्रम MMIO SPTEs.  To preserve the GFN, we'll
 * shअगरt bits of the GFN that overlap with shaकरोw_nonpresent_or_rsvd_mask
 * left पूर्णांकo the reserved bits, i.e. the GFN in the SPTE will be split पूर्णांकo
 * high and low parts.  This mask covers the lower bits of the GFN.
 */
बाह्य u64 __पढ़ो_mostly shaकरोw_nonpresent_or_rsvd_lower_gfn_mask;

/*
 * The number of non-reserved physical address bits irrespective of features
 * that repurpose legal bits, e.g. MKTME.
 */
बाह्य u8 __पढ़ो_mostly shaकरोw_phys_bits;

अटल अंतरभूत bool is_mmio_spte(u64 spte)
अणु
	वापस (spte & shaकरोw_mmio_mask) == shaकरोw_mmio_value &&
	       likely(shaकरोw_mmio_value);
पूर्ण

अटल अंतरभूत bool is_shaकरोw_present_pte(u64 pte)
अणु
	वापस !!(pte & SPTE_MMU_PRESENT_MASK);
पूर्ण

अटल अंतरभूत bool sp_ad_disabled(काष्ठा kvm_mmu_page *sp)
अणु
	वापस sp->role.ad_disabled;
पूर्ण

अटल अंतरभूत bool spte_ad_enabled(u64 spte)
अणु
	MMU_WARN_ON(!is_shaकरोw_present_pte(spte));
	वापस (spte & SPTE_TDP_AD_MASK) != SPTE_TDP_AD_DISABLED_MASK;
पूर्ण

अटल अंतरभूत bool spte_ad_need_ग_लिखो_protect(u64 spte)
अणु
	MMU_WARN_ON(!is_shaकरोw_present_pte(spte));
	/*
	 * This is benign क्रम non-TDP SPTEs as SPTE_TDP_AD_ENABLED_MASK is '0',
	 * and non-TDP SPTEs will never set these bits.  Optimize क्रम 64-bit
	 * TDP and करो the A/D type check unconditionally.
	 */
	वापस (spte & SPTE_TDP_AD_MASK) != SPTE_TDP_AD_ENABLED_MASK;
पूर्ण

अटल अंतरभूत u64 spte_shaकरोw_accessed_mask(u64 spte)
अणु
	MMU_WARN_ON(!is_shaकरोw_present_pte(spte));
	वापस spte_ad_enabled(spte) ? shaकरोw_accessed_mask : 0;
पूर्ण

अटल अंतरभूत u64 spte_shaकरोw_dirty_mask(u64 spte)
अणु
	MMU_WARN_ON(!is_shaकरोw_present_pte(spte));
	वापस spte_ad_enabled(spte) ? shaकरोw_dirty_mask : 0;
पूर्ण

अटल अंतरभूत bool is_access_track_spte(u64 spte)
अणु
	वापस !spte_ad_enabled(spte) && (spte & shaकरोw_acc_track_mask) == 0;
पूर्ण

अटल अंतरभूत bool is_large_pte(u64 pte)
अणु
	वापस pte & PT_PAGE_SIZE_MASK;
पूर्ण

अटल अंतरभूत bool is_last_spte(u64 pte, पूर्णांक level)
अणु
	वापस (level == PG_LEVEL_4K) || is_large_pte(pte);
पूर्ण

अटल अंतरभूत bool is_executable_pte(u64 spte)
अणु
	वापस (spte & (shaकरोw_x_mask | shaकरोw_nx_mask)) == shaकरोw_x_mask;
पूर्ण

अटल अंतरभूत kvm_pfn_t spte_to_pfn(u64 pte)
अणु
	वापस (pte & PT64_BASE_ADDR_MASK) >> PAGE_SHIFT;
पूर्ण

अटल अंतरभूत bool is_accessed_spte(u64 spte)
अणु
	u64 accessed_mask = spte_shaकरोw_accessed_mask(spte);

	वापस accessed_mask ? spte & accessed_mask
			     : !is_access_track_spte(spte);
पूर्ण

अटल अंतरभूत bool is_dirty_spte(u64 spte)
अणु
	u64 dirty_mask = spte_shaकरोw_dirty_mask(spte);

	वापस dirty_mask ? spte & dirty_mask : spte & PT_WRITABLE_MASK;
पूर्ण

अटल अंतरभूत bool spte_can_locklessly_be_made_writable(u64 spte)
अणु
	वापस (spte & shaकरोw_host_writable_mask) &&
	       (spte & shaकरोw_mmu_writable_mask);
पूर्ण

अटल अंतरभूत u64 get_mmio_spte_generation(u64 spte)
अणु
	u64 gen;

	gen = (spte & MMIO_SPTE_GEN_LOW_MASK) >> MMIO_SPTE_GEN_LOW_SHIFT;
	gen |= (spte & MMIO_SPTE_GEN_HIGH_MASK) >> MMIO_SPTE_GEN_HIGH_SHIFT;
	वापस gen;
पूर्ण

/* Bits which may be वापसed by set_spte() */
#घोषणा SET_SPTE_WRITE_PROTECTED_PT    BIT(0)
#घोषणा SET_SPTE_NEED_REMOTE_TLB_FLUSH BIT(1)
#घोषणा SET_SPTE_SPURIOUS              BIT(2)

पूर्णांक make_spte(काष्ठा kvm_vcpu *vcpu, अचिन्हित पूर्णांक pte_access, पूर्णांक level,
		     gfn_t gfn, kvm_pfn_t pfn, u64 old_spte, bool speculative,
		     bool can_unsync, bool host_writable, bool ad_disabled,
		     u64 *new_spte);
u64 make_nonleaf_spte(u64 *child_pt, bool ad_disabled);
u64 make_mmio_spte(काष्ठा kvm_vcpu *vcpu, u64 gfn, अचिन्हित पूर्णांक access);
u64 mark_spte_क्रम_access_track(u64 spte);
u64 kvm_mmu_changed_pte_notअगरier_make_spte(u64 old_spte, kvm_pfn_t new_pfn);

व्योम kvm_mmu_reset_all_pte_masks(व्योम);

#पूर्ण_अगर
