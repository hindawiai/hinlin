<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_NOHASH_32_PTE_44x_H
#घोषणा _ASM_POWERPC_NOHASH_32_PTE_44x_H
#अगर_घोषित __KERNEL__

/*
 * Definitions क्रम PPC440
 *
 * Because of the 3 word TLB entries to support 36-bit addressing,
 * the attribute are dअगरficult to map in such a fashion that they
 * are easily loaded during exception processing.  I decided to
 * organize the entry so the ERPN is the only portion in the
 * upper word of the PTE and the attribute bits below are packed
 * in as sensibly as they can be in the area below a 4KB page size
 * oriented RPN.  This at least makes it easy to load the RPN and
 * ERPN fields in the TLB. -Matt
 *
 * This isn't entirely true anymore, at least some bits are now
 * easier to move पूर्णांकo the TLB from the PTE. -BenH.
 *
 * Note that these bits preclude future use of a page size
 * less than 4KB.
 *
 *
 * PPC 440 core has following TLB attribute fields;
 *
 *   TLB1:
 *   0  1  2  3  4  ... 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 *   RPN.................................  -  -  -  -  -  - ERPN.......
 *
 *   TLB2:
 *   0  1  2  3  4  ... 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 *   -  -  -  -  -    - U0 U1 U2 U3 W  I  M  G  E   - UX UW UR SX SW SR
 *
 * Newer 440 cores (440x6 as used on AMCC 460EX/460GT) have additional
 * TLB2 storage attribute fields. Those are:
 *
 *   TLB2:
 *   0...10    11   12   13   14   15   16...31
 *   no change WL1  IL1I IL1D IL2I IL2D no change
 *
 * There are some स्थिरrains and options, to decide mapping software bits
 * पूर्णांकo TLB entry.
 *
 *   - PRESENT *must* be in the bottom three bits because swap cache
 *     entries use the top 29 bits क्रम TLB2.
 *
 *   - CACHE COHERENT bit (M) has no effect on original PPC440 cores,
 *     because it करोesn't support SMP. However, some later 460 variants
 *     have -some- क्रमm of SMP support and so I keep the bit there क्रम
 *     future use
 *
 * With the PPC 44x Linux implementation, the 0-11th LSBs of the PTE are used
 * क्रम memory protection related functions (see PTE काष्ठाure in
 * include/यंत्र-ppc/mmu.h).  The _PAGE_XXX definitions in this file map to the
 * above bits.  Note that the bit values are CPU specअगरic, not architecture
 * specअगरic.
 *
 * The kernel PTE entry holds an arch-dependent swp_entry काष्ठाure under
 * certain situations. In other words, in such situations some portion of
 * the PTE bits are used as a swp_entry. In the PPC implementation, the
 * 3-24th LSB are shared with swp_entry, however the 0-2nd three LSB still
 * hold protection values. That means the three protection bits are
 * reserved क्रम both PTE and SWAP entry at the most signअगरicant three
 * LSBs.
 *
 * There are three protection bits available क्रम SWAP entry:
 *	_PAGE_PRESENT
 *	_PAGE_HASHPTE (अगर HW has)
 *
 * So those three bits have to be inside of 0-2nd LSB of PTE.
 *
 */

#घोषणा _PAGE_PRESENT	0x00000001		/* S: PTE valid */
#घोषणा _PAGE_RW	0x00000002		/* S: Write permission */
#घोषणा _PAGE_EXEC	0x00000004		/* H: Execute permission */
#घोषणा _PAGE_ACCESSED	0x00000008		/* S: Page referenced */
#घोषणा _PAGE_सूचीTY	0x00000010		/* S: Page dirty */
#घोषणा _PAGE_SPECIAL	0x00000020		/* S: Special page */
#घोषणा _PAGE_USER	0x00000040		/* S: User page */
#घोषणा _PAGE_ENDIAN	0x00000080		/* H: E bit */
#घोषणा _PAGE_GUARDED	0x00000100		/* H: G bit */
#घोषणा _PAGE_COHERENT	0x00000200		/* H: M bit */
#घोषणा _PAGE_NO_CACHE	0x00000400		/* H: I bit */
#घोषणा _PAGE_WRITETHRU	0x00000800		/* H: W bit */

/* No page size encoding in the linux PTE */
#घोषणा _PAGE_PSIZE		0

#घोषणा _PAGE_KERNEL_RO		0
#घोषणा _PAGE_KERNEL_ROX	_PAGE_EXEC
#घोषणा _PAGE_KERNEL_RW		(_PAGE_सूचीTY | _PAGE_RW)
#घोषणा _PAGE_KERNEL_RWX	(_PAGE_सूचीTY | _PAGE_RW | _PAGE_EXEC)

/* TODO: Add large page lowmem mapping support */
#घोषणा _PMD_PRESENT	0
#घोषणा _PMD_PRESENT_MASK (PAGE_MASK)
#घोषणा _PMD_BAD	(~PAGE_MASK)
#घोषणा _PMD_USER	0

/* ERPN in a PTE never माला_लो cleared, ignore it */
#घोषणा _PTE_NONE_MASK	0xffffffff00000000ULL

/*
 * We define 2 sets of base prot bits, one क्रम basic pages (ie,
 * cacheable kernel and user pages) and one क्रम non cacheable
 * pages. We always set _PAGE_COHERENT when SMP is enabled or
 * the processor might need it क्रम DMA coherency.
 */
#घोषणा _PAGE_BASE_NC	(_PAGE_PRESENT | _PAGE_ACCESSED)
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

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /*  _ASM_POWERPC_NOHASH_32_PTE_44x_H */
