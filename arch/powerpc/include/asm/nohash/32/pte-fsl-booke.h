<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_32_PTE_FSL_BOOKE_H
#घोषणा _ASM_POWERPC_NOHASH_32_PTE_FSL_BOOKE_H
#अगर_घोषित __KERNEL__

/* PTE bit definitions क्रम Freescale BookE SW loaded TLB MMU based
 * processors
 *
   MMU Assist Register 3:

   32 33 34 35 36  ... 50 51 52 53 54 55 56 57 58 59 60 61 62 63
   RPN......................  0  0 U0 U1 U2 U3 UX SX UW SW UR SR

   - PRESENT *must* be in the bottom three bits because swap cache
     entries use the top 29 bits.

*/

/* Definitions क्रम FSL Book-E Cores */
#घोषणा _PAGE_PRESENT	0x00001	/* S: PTE contains a translation */
#घोषणा _PAGE_USER	0x00002	/* S: User page (maps to UR) */
#घोषणा _PAGE_RW	0x00004	/* S: Write permission (SW) */
#घोषणा _PAGE_सूचीTY	0x00008	/* S: Page dirty */
#घोषणा _PAGE_EXEC	0x00010	/* H: SX permission */
#घोषणा _PAGE_ACCESSED	0x00020	/* S: Page referenced */

#घोषणा _PAGE_ENDIAN	0x00040	/* H: E bit */
#घोषणा _PAGE_GUARDED	0x00080	/* H: G bit */
#घोषणा _PAGE_COHERENT	0x00100	/* H: M bit */
#घोषणा _PAGE_NO_CACHE	0x00200	/* H: I bit */
#घोषणा _PAGE_WRITETHRU	0x00400	/* H: W bit */
#घोषणा _PAGE_SPECIAL	0x00800 /* S: Special page */

#घोषणा _PAGE_KERNEL_RO		0
#घोषणा _PAGE_KERNEL_ROX	_PAGE_EXEC
#घोषणा _PAGE_KERNEL_RW		(_PAGE_सूचीTY | _PAGE_RW)
#घोषणा _PAGE_KERNEL_RWX	(_PAGE_सूचीTY | _PAGE_RW | _PAGE_EXEC)

/* No page size encoding in the linux PTE */
#घोषणा _PAGE_PSIZE		0

#घोषणा _PMD_PRESENT	0
#घोषणा _PMD_PRESENT_MASK (PAGE_MASK)
#घोषणा _PMD_BAD	(~PAGE_MASK)
#घोषणा _PMD_USER	0

#घोषणा _PTE_NONE_MASK	0

#घोषणा PTE_WIMGE_SHIFT (6)

/*
 * We define 2 sets of base prot bits, one क्रम basic pages (ie,
 * cacheable kernel and user pages) and one क्रम non cacheable
 * pages. We always set _PAGE_COHERENT when SMP is enabled or
 * the processor might need it क्रम DMA coherency.
 */
#घोषणा _PAGE_BASE_NC	(_PAGE_PRESENT | _PAGE_ACCESSED)
#अगर defined(CONFIG_SMP) || defined(CONFIG_PPC_E500MC)
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

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /*  _ASM_POWERPC_NOHASH_32_PTE_FSL_BOOKE_H */
