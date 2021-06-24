<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

#अगर_अघोषित _ASM_POWERPC_BOOK3S_64_PKEYS_H
#घोषणा _ASM_POWERPC_BOOK3S_64_PKEYS_H

#समावेश <यंत्र/book3s/64/hash-pkey.h>

अटल अंतरभूत u64 vmflag_to_pte_pkey_bits(u64 vm_flags)
अणु
	अगर (!mmu_has_feature(MMU_FTR_PKEY))
		वापस 0x0UL;

	अगर (radix_enabled())
		BUG();
	वापस hash__vmflag_to_pte_pkey_bits(vm_flags);
पूर्ण

अटल अंतरभूत u16 pte_to_pkey_bits(u64 pteflags)
अणु
	अगर (radix_enabled())
		BUG();
	वापस hash__pte_to_pkey_bits(pteflags);
पूर्ण

#पूर्ण_अगर /*_ASM_POWERPC_KEYS_H */
