<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016 - ARM Ltd
 *
 * stage2 page table helpers
 */

#अगर_अघोषित __ARM64_S2_PGTABLE_H_
#घोषणा __ARM64_S2_PGTABLE_H_

#समावेश <linux/pgtable.h>

/*
 * PGसूची_SHIFT determines the size a top-level page table entry can map
 * and depends on the number of levels in the page table. Compute the
 * PGसूची_SHIFT क्रम a given number of levels.
 */
#घोषणा pt_levels_pgdir_shअगरt(lvls)	ARM64_HW_PGTABLE_LEVEL_SHIFT(4 - (lvls))

/*
 * The hardware supports concatenation of up to 16 tables at stage2 entry
 * level and we use the feature whenever possible, which means we resolve 4
 * additional bits of address at the entry level.
 *
 * This implies, the total number of page table levels required क्रम
 * IPA_SHIFT at stage2 expected by the hardware can be calculated using
 * the same logic used क्रम the (non-collapsable) stage1 page tables but क्रम
 * (IPA_SHIFT - 4).
 */
#घोषणा stage2_pgtable_levels(ipa)	ARM64_HW_PGTABLE_LEVELS((ipa) - 4)
#घोषणा kvm_stage2_levels(kvm)		VTCR_EL2_LVLS(kvm->arch.vtcr)

/* stage2_pgdir_shअगरt() is the size mapped by top-level stage2 entry क्रम the VM */
#घोषणा stage2_pgdir_shअगरt(kvm)		pt_levels_pgdir_shअगरt(kvm_stage2_levels(kvm))
#घोषणा stage2_pgdir_size(kvm)		(1ULL << stage2_pgdir_shअगरt(kvm))
#घोषणा stage2_pgdir_mask(kvm)		~(stage2_pgdir_size(kvm) - 1)

/*
 * kvm_mmmu_cache_min_pages() is the number of pages required to install
 * a stage-2 translation. We pre-allocate the entry level page table at
 * the VM creation.
 */
#घोषणा kvm_mmu_cache_min_pages(kvm)	(kvm_stage2_levels(kvm) - 1)

अटल अंतरभूत phys_addr_t
stage2_pgd_addr_end(काष्ठा kvm *kvm, phys_addr_t addr, phys_addr_t end)
अणु
	phys_addr_t boundary = (addr + stage2_pgdir_size(kvm)) & stage2_pgdir_mask(kvm);

	वापस (boundary - 1 < end - 1) ? boundary : end;
पूर्ण

#पूर्ण_अगर	/* __ARM64_S2_PGTABLE_H_ */
