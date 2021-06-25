<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_32_PTE_40x_H
#घोषणा _ASM_POWERPC_NOHASH_32_PTE_40x_H
#अगर_घोषित __KERNEL__

/*
 * At present, all PowerPC 400-class processors share a similar TLB
 * architecture. The inकाष्ठाion and data sides share a unअगरied,
 * 64-entry, fully-associative TLB which is मुख्यtained totally under
 * software control. In addition, the inकाष्ठाion side has a
 * hardware-managed, 4-entry, fully-associative TLB which serves as a
 * first level to the shared TLB. These two TLBs are known as the UTLB
 * and ITLB, respectively (see "mmu.h" क्रम definitions).
 *
 * There are several potential gotchas here.  The 40x hardware TLBLO
 * field looks like this:
 *
 * 0  1  2  3  4  ... 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 * RPN.....................  0  0 EX WR ZSEL.......  W  I  M  G
 *
 * Where possible we make the Linux PTE bits match up with this
 *
 * - bits 20 and 21 must be cleared, because we use 4k pages (40x can
 *   support करोwn to 1k pages), this is करोne in the TLBMiss exception
 *   handler.
 * - We use only zones 0 (क्रम kernel pages) and 1 (क्रम user pages)
 *   of the 16 available.  Bit 24-26 of the TLB are cleared in the TLB
 *   miss handler.  Bit 27 is PAGE_USER, thus selecting the correct
 *   zone.
 * - PRESENT *must* be in the bottom two bits because swap cache
 *   entries use the top 30 bits.  Because 40x करोesn't support SMP
 *   anyway, M is irrelevant so we borrow it क्रम PAGE_PRESENT.  Bit 30
 *   is cleared in the TLB miss handler beक्रमe the TLB entry is loaded.
 * - All other bits of the PTE are loaded पूर्णांकo TLBLO without
 *   modअगरication, leaving us only the bits 20, 21, 24, 25, 26, 30 क्रम
 *   software PTE bits.  We actually use bits 21, 24, 25, and
 *   30 respectively क्रम the software bits: ACCESSED, सूचीTY, RW, and
 *   PRESENT.
 */

#घोषणा	_PAGE_GUARDED	0x001	/* G: page is guarded from prefetch */
#घोषणा _PAGE_PRESENT	0x002	/* software: PTE contains a translation */
#घोषणा	_PAGE_NO_CACHE	0x004	/* I: caching is inhibited */
#घोषणा	_PAGE_WRITETHRU	0x008	/* W: caching is ग_लिखो-through */
#घोषणा	_PAGE_USER	0x010	/* matches one of the zone permission bits */
#घोषणा	_PAGE_SPECIAL	0x020	/* software: Special page */
#घोषणा	_PAGE_सूचीTY	0x080	/* software: dirty page */
#घोषणा _PAGE_RW	0x100	/* hardware: WR, anded with dirty in exception */
#घोषणा _PAGE_EXEC	0x200	/* hardware: EX permission */
#घोषणा _PAGE_ACCESSED	0x400	/* software: R: page referenced */

/* No page size encoding in the linux PTE */
#घोषणा _PAGE_PSIZE		0

/* cache related flags non existing on 40x */
#घोषणा _PAGE_COHERENT	0

#घोषणा _PAGE_KERNEL_RO		0
#घोषणा _PAGE_KERNEL_ROX	_PAGE_EXEC
#घोषणा _PAGE_KERNEL_RW		(_PAGE_सूचीTY | _PAGE_RW)
#घोषणा _PAGE_KERNEL_RWX	(_PAGE_सूचीTY | _PAGE_RW | _PAGE_EXEC)

#घोषणा _PMD_PRESENT	0x400	/* PMD poपूर्णांकs to page of PTEs */
#घोषणा _PMD_PRESENT_MASK	_PMD_PRESENT
#घोषणा _PMD_BAD	0x802
#घोषणा _PMD_SIZE_4M	0x0c0
#घोषणा _PMD_SIZE_16M	0x0e0
#घोषणा _PMD_USER	0

#घोषणा _PTE_NONE_MASK	0

/* Until my rework is finished, 40x still needs atomic PTE updates */
#घोषणा PTE_ATOMIC_UPDATES	1

#घोषणा _PAGE_BASE_NC	(_PAGE_PRESENT | _PAGE_ACCESSED)
#घोषणा _PAGE_BASE	(_PAGE_BASE_NC)

/* Permission masks used to generate the __P and __S table */
#घोषणा PAGE_NONE	__pgprot(_PAGE_BASE)
#घोषणा PAGE_SHARED	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW)
#घोषणा PAGE_SHARED_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_RW | _PAGE_EXEC)
#घोषणा PAGE_COPY	__pgprot(_PAGE_BASE | _PAGE_USER)
#घोषणा PAGE_COPY_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)
#घोषणा PAGE_READONLY	__pgprot(_PAGE_BASE | _PAGE_USER)
#घोषणा PAGE_READONLY_X	__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /*  _ASM_POWERPC_NOHASH_32_PTE_40x_H */
