<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_HASH_PKEY_H
#घोषणा _ASM_POWERPC_BOOK3S_64_HASH_PKEY_H

/*  We use key 3 क्रम KERNEL */
#घोषणा HASH_DEFAULT_KERNEL_KEY (HPTE_R_KEY_BIT0 | HPTE_R_KEY_BIT1)

अटल अंतरभूत u64 hash__vmflag_to_pte_pkey_bits(u64 vm_flags)
अणु
	वापस (((vm_flags & VM_PKEY_BIT0) ? H_PTE_PKEY_BIT0 : 0x0UL) |
		((vm_flags & VM_PKEY_BIT1) ? H_PTE_PKEY_BIT1 : 0x0UL) |
		((vm_flags & VM_PKEY_BIT2) ? H_PTE_PKEY_BIT2 : 0x0UL) |
		((vm_flags & VM_PKEY_BIT3) ? H_PTE_PKEY_BIT3 : 0x0UL) |
		((vm_flags & VM_PKEY_BIT4) ? H_PTE_PKEY_BIT4 : 0x0UL));
पूर्ण

अटल अंतरभूत u64 pte_to_hpte_pkey_bits(u64 pteflags, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ pte_pkey;

	pte_pkey = (((pteflags & H_PTE_PKEY_BIT4) ? HPTE_R_KEY_BIT4 : 0x0UL) |
		    ((pteflags & H_PTE_PKEY_BIT3) ? HPTE_R_KEY_BIT3 : 0x0UL) |
		    ((pteflags & H_PTE_PKEY_BIT2) ? HPTE_R_KEY_BIT2 : 0x0UL) |
		    ((pteflags & H_PTE_PKEY_BIT1) ? HPTE_R_KEY_BIT1 : 0x0UL) |
		    ((pteflags & H_PTE_PKEY_BIT0) ? HPTE_R_KEY_BIT0 : 0x0UL));

	अगर (mmu_has_feature(MMU_FTR_BOOK3S_KUAP) ||
	    mmu_has_feature(MMU_FTR_BOOK3S_KUEP)) अणु
		अगर ((pte_pkey == 0) && (flags & HPTE_USE_KERNEL_KEY))
			वापस HASH_DEFAULT_KERNEL_KEY;
	पूर्ण

	वापस pte_pkey;
पूर्ण

अटल अंतरभूत u16 hash__pte_to_pkey_bits(u64 pteflags)
अणु
	वापस (((pteflags & H_PTE_PKEY_BIT4) ? 0x10 : 0x0UL) |
		((pteflags & H_PTE_PKEY_BIT3) ? 0x8 : 0x0UL) |
		((pteflags & H_PTE_PKEY_BIT2) ? 0x4 : 0x0UL) |
		((pteflags & H_PTE_PKEY_BIT1) ? 0x2 : 0x0UL) |
		((pteflags & H_PTE_PKEY_BIT0) ? 0x1 : 0x0UL));
पूर्ण

#पूर्ण_अगर
