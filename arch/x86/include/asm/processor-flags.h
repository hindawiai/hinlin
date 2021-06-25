<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PROCESSOR_FLAGS_H
#घोषणा _ASM_X86_PROCESSOR_FLAGS_H

#समावेश <uapi/यंत्र/processor-flags.h>
#समावेश <linux/mem_encrypt.h>

#अगर_घोषित CONFIG_VM86
#घोषणा X86_VM_MASK	X86_EFLAGS_VM
#अन्यथा
#घोषणा X86_VM_MASK	0 /* No VM86 support */
#पूर्ण_अगर

/*
 * CR3's layout varies depending on several things.
 *
 * If CR4.PCIDE is set (64-bit only), then CR3[11:0] is the address space ID.
 * If PAE is enabled, then CR3[11:5] is part of the PDPT address
 * (i.e. it's 32-byte aligned, not page-aligned) and CR3[4:0] is ignored.
 * Otherwise (non-PAE, non-PCID), CR3[3] is PWT, CR3[4] is PCD, and
 * CR3[2:0] and CR3[11:5] are ignored.
 *
 * In all हालs, Linux माला_दो zeros in the low ignored bits and in PWT and PCD.
 *
 * CR3[63] is always पढ़ो as zero.  If CR4.PCIDE is set, then CR3[63] may be
 * written as 1 to prevent the ग_लिखो to CR3 from flushing the TLB.
 *
 * On प्रणालीs with SME, one bit (in a variable position!) is stolen to indicate
 * that the top-level paging काष्ठाure is encrypted.
 *
 * All of the reमुख्यing bits indicate the physical address of the top-level
 * paging काष्ठाure.
 *
 * CR3_ADDR_MASK is the mask used by पढ़ो_cr3_pa().
 */
#अगर_घोषित CONFIG_X86_64
/* Mask off the address space ID and SME encryption bits. */
#घोषणा CR3_ADDR_MASK	__sme_clr(0x7FFFFFFFFFFFF000ull)
#घोषणा CR3_PCID_MASK	0xFFFull
#घोषणा CR3_NOFLUSH	BIT_ULL(63)

#अन्यथा
/*
 * CR3_ADDR_MASK needs at least bits 31:5 set on PAE प्रणालीs, and we save
 * a tiny bit of code size by setting all the bits.
 */
#घोषणा CR3_ADDR_MASK	0xFFFFFFFFull
#घोषणा CR3_PCID_MASK	0ull
#घोषणा CR3_NOFLUSH	0
#पूर्ण_अगर

#अगर_घोषित CONFIG_PAGE_TABLE_ISOLATION
# define X86_CR3_PTI_PCID_USER_BIT	11
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_X86_PROCESSOR_FLAGS_H */
