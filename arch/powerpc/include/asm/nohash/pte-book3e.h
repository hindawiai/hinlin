<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_PTE_BOOK3E_H
#घोषणा _ASM_POWERPC_NOHASH_PTE_BOOK3E_H
#अगर_घोषित __KERNEL__

/* PTE bit definitions क्रम processors compliant to the Book3E
 * architecture 2.06 or later. The position of the PTE bits
 * matches the HW definition of the optional Embedded Page Table
 * category.
 */

/* Architected bits */
#घोषणा _PAGE_PRESENT	0x000001 /* software: pte contains a translation */
#घोषणा _PAGE_SW1	0x000002
#घोषणा _PAGE_BIT_SWAP_TYPE	2
#घोषणा _PAGE_BAP_SR	0x000004
#घोषणा _PAGE_BAP_UR	0x000008
#घोषणा _PAGE_BAP_SW	0x000010
#घोषणा _PAGE_BAP_UW	0x000020
#घोषणा _PAGE_BAP_SX	0x000040
#घोषणा _PAGE_BAP_UX	0x000080
#घोषणा _PAGE_PSIZE_MSK	0x000f00
#घोषणा _PAGE_PSIZE_4K	0x000200
#घोषणा _PAGE_PSIZE_8K	0x000300
#घोषणा _PAGE_PSIZE_16K	0x000400
#घोषणा _PAGE_PSIZE_32K	0x000500
#घोषणा _PAGE_PSIZE_64K	0x000600
#घोषणा _PAGE_PSIZE_128K	0x000700
#घोषणा _PAGE_PSIZE_256K	0x000800
#घोषणा _PAGE_PSIZE_512K	0x000900
#घोषणा _PAGE_PSIZE_1M	0x000a00
#घोषणा _PAGE_PSIZE_2M	0x000b00
#घोषणा _PAGE_PSIZE_4M	0x000c00
#घोषणा _PAGE_PSIZE_8M	0x000d00
#घोषणा _PAGE_PSIZE_16M	0x000e00
#घोषणा _PAGE_PSIZE_32M	0x000f00
#घोषणा _PAGE_सूचीTY	0x001000 /* C: page changed */
#घोषणा _PAGE_SW0	0x002000
#घोषणा _PAGE_U3	0x004000
#घोषणा _PAGE_U2	0x008000
#घोषणा _PAGE_U1	0x010000
#घोषणा _PAGE_U0	0x020000
#घोषणा _PAGE_ACCESSED	0x040000
#घोषणा _PAGE_ENDIAN	0x080000
#घोषणा _PAGE_GUARDED	0x100000
#घोषणा _PAGE_COHERENT	0x200000 /* M: enक्रमce memory coherence */
#घोषणा _PAGE_NO_CACHE	0x400000 /* I: cache inhibit */
#घोषणा _PAGE_WRITETHRU	0x800000 /* W: cache ग_लिखो-through */

/* "Higher level" linux bit combinations */
#घोषणा _PAGE_EXEC		_PAGE_BAP_UX /* .. and was cache cleaned */
#घोषणा _PAGE_RW		(_PAGE_BAP_SW | _PAGE_BAP_UW) /* User ग_लिखो permission */
#घोषणा _PAGE_KERNEL_RW		(_PAGE_BAP_SW | _PAGE_BAP_SR | _PAGE_सूचीTY)
#घोषणा _PAGE_KERNEL_RO		(_PAGE_BAP_SR)
#घोषणा _PAGE_KERNEL_RWX	(_PAGE_BAP_SW | _PAGE_BAP_SR | _PAGE_सूचीTY | _PAGE_BAP_SX)
#घोषणा _PAGE_KERNEL_ROX	(_PAGE_BAP_SR | _PAGE_BAP_SX)
#घोषणा _PAGE_USER		(_PAGE_BAP_UR | _PAGE_BAP_SR) /* Can be पढ़ो */
#घोषणा _PAGE_PRIVILEGED	(_PAGE_BAP_SR)

#घोषणा _PAGE_SPECIAL	_PAGE_SW0

/* Base page size */
#घोषणा _PAGE_PSIZE	_PAGE_PSIZE_4K
#घोषणा	PTE_RPN_SHIFT	(24)

#घोषणा PTE_WIMGE_SHIFT (19)
#घोषणा PTE_BAP_SHIFT	(2)

/* On 32-bit, we never clear the top part of the PTE */
#अगर_घोषित CONFIG_PPC32
#घोषणा _PTE_NONE_MASK	0xffffffff00000000ULL
#घोषणा _PMD_PRESENT	0
#घोषणा _PMD_PRESENT_MASK (PAGE_MASK)
#घोषणा _PMD_BAD	(~PAGE_MASK)
#घोषणा _PMD_USER	0
#अन्यथा
#घोषणा _PTE_NONE_MASK	0
#पूर्ण_अगर

/*
 * We define 2 sets of base prot bits, one क्रम basic pages (ie,
 * cacheable kernel and user pages) and one क्रम non cacheable
 * pages. We always set _PAGE_COHERENT when SMP is enabled or
 * the processor might need it क्रम DMA coherency.
 */
#घोषणा _PAGE_BASE_NC	(_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_PSIZE)
#अगर defined(CONFIG_SMP)
#घोषणा _PAGE_BASE	(_PAGE_BASE_NC | _PAGE_COHERENT)
#अन्यथा
#घोषणा _PAGE_BASE	(_PAGE_BASE_NC)
#पूर्ण_अगर

/* Permission masks used to generate the __P and __S table */
#घोषणा PAGE_NONE	__pgprot(_PAGE_BASE)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW)
#घोषणा PAGE_SHARED_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW | _PAGE_EXEC)
#घोषणा PAGE_COPY	__pgprot(_PAGE_BASE | _PAGE_USER)
#घोषणा PAGE_COPY_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_BASE | _PAGE_USER)
#घोषणा PAGE_READONLY_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)

#अगर_अघोषित __ASSEMBLY__
अटल अंतरभूत pte_t pte_mkprivileged(pte_t pte)
अणु
	वापस __pte((pte_val(pte) & ~_PAGE_USER) | _PAGE_PRIVILEGED);
पूर्ण

#घोषणा pte_mkprivileged pte_mkprivileged

अटल अंतरभूत pte_t pte_mkuser(pte_t pte)
अणु
	वापस __pte((pte_val(pte) & ~_PAGE_PRIVILEGED) | _PAGE_USER);
पूर्ण

#घोषणा pte_mkuser pte_mkuser
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /*  _ASM_POWERPC_NOHASH_PTE_BOOK3E_H */
