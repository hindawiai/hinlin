<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 - 2002 by Ralf Baechle
 * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.
 * Copyright (C) 2002  Maciej W. Rozycki
 */
#अगर_अघोषित _ASM_PGTABLE_BITS_H
#घोषणा _ASM_PGTABLE_BITS_H


/*
 * Note that we shअगरt the lower 32bits of each EntryLo[01] entry
 * 6 bits to the left. That way we can convert the PFN पूर्णांकo the
 * physical address by a single 'and' operation and gain 6 additional
 * bits क्रम storing inक्रमmation which isn't present in a normal
 * MIPS page table.
 *
 * Similar to the Alpha port, we need to keep track of the ref
 * and mod bits in software.  We have a software "yeah you can पढ़ो
 * from this page" bit, and a hardware one which actually lets the
 * process पढ़ो from the page.	On the same token we have a software
 * writable bit and the real hardware one which actually lets the
 * process ग_लिखो to the page, this keeps a mod bit via the hardware
 * dirty bit.
 *
 * Certain revisions of the R4000 and R5000 have a bug where अगर a
 * certain sequence occurs in the last 3 inकाष्ठाions of an executable
 * page, and the following page is not mapped, the cpu can करो
 * unpredictable things.  The code (when it is written) to deal with
 * this problem will be in the update_mmu_cache() code क्रम the r4k.
 */
#अगर defined(CONFIG_XPA)

/*
 * Page table bit offsets used क्रम 64 bit physical addressing on
 * MIPS32r5 with XPA.
 */
क्रमागत pgtable_bits अणु
	/* Used by TLB hardware (placed in EntryLo*) */
	_PAGE_NO_EXEC_SHIFT,
	_PAGE_NO_READ_SHIFT,
	_PAGE_GLOBAL_SHIFT,
	_PAGE_VALID_SHIFT,
	_PAGE_सूचीTY_SHIFT,
	_CACHE_SHIFT,

	/* Used only by software (masked out beक्रमe writing EntryLo*) */
	_PAGE_PRESENT_SHIFT = 24,
	_PAGE_WRITE_SHIFT,
	_PAGE_ACCESSED_SHIFT,
	_PAGE_MODIFIED_SHIFT,
#अगर defined(CONFIG_ARCH_HAS_PTE_SPECIAL)
	_PAGE_SPECIAL_SHIFT,
#पूर्ण_अगर
#अगर defined(CONFIG_HAVE_ARCH_SOFT_सूचीTY)
	_PAGE_SOFT_सूचीTY_SHIFT,
#पूर्ण_अगर
पूर्ण;

/*
 * Bits क्रम extended EntryLo0/EntryLo1 रेजिस्टरs
 */
#घोषणा _PFNX_MASK		0xffffff

#या_अगर defined(CONFIG_PHYS_ADDR_T_64BIT) && defined(CONFIG_CPU_MIPS32)

/*
 * Page table bit offsets used क्रम 36 bit physical addressing on MIPS32,
 * क्रम example with Alchemy or Netlogic XLP/XLR.
 */
क्रमागत pgtable_bits अणु
	/* Used by TLB hardware (placed in EntryLo*) */
	_PAGE_GLOBAL_SHIFT,
	_PAGE_VALID_SHIFT,
	_PAGE_सूचीTY_SHIFT,
	_CACHE_SHIFT,

	/* Used only by software (masked out beक्रमe writing EntryLo*) */
	_PAGE_PRESENT_SHIFT = _CACHE_SHIFT + 3,
	_PAGE_NO_READ_SHIFT,
	_PAGE_WRITE_SHIFT,
	_PAGE_ACCESSED_SHIFT,
	_PAGE_MODIFIED_SHIFT,
#अगर defined(CONFIG_ARCH_HAS_PTE_SPECIAL)
	_PAGE_SPECIAL_SHIFT,
#पूर्ण_अगर
#अगर defined(CONFIG_HAVE_ARCH_SOFT_सूचीTY)
	_PAGE_SOFT_सूचीTY_SHIFT,
#पूर्ण_अगर
पूर्ण;

#या_अगर defined(CONFIG_CPU_R3K_TLB)

/* Page table bits used क्रम r3k प्रणालीs */
क्रमागत pgtable_bits अणु
	/* Used only by software (ग_लिखोs to EntryLo ignored) */
	_PAGE_PRESENT_SHIFT,
	_PAGE_NO_READ_SHIFT,
	_PAGE_WRITE_SHIFT,
	_PAGE_ACCESSED_SHIFT,
	_PAGE_MODIFIED_SHIFT,
#अगर defined(CONFIG_ARCH_HAS_PTE_SPECIAL)
	_PAGE_SPECIAL_SHIFT,
#पूर्ण_अगर
#अगर defined(CONFIG_HAVE_ARCH_SOFT_सूचीTY)
	_PAGE_SOFT_सूचीTY_SHIFT,
#पूर्ण_अगर

	/* Used by TLB hardware (placed in EntryLo) */
	_PAGE_GLOBAL_SHIFT = 8,
	_PAGE_VALID_SHIFT,
	_PAGE_सूचीTY_SHIFT,
	_CACHE_UNCACHED_SHIFT,
पूर्ण;

#अन्यथा

/* Page table bits used क्रम r4k प्रणालीs */
क्रमागत pgtable_bits अणु
	/* Used only by software (masked out beक्रमe writing EntryLo*) */
	_PAGE_PRESENT_SHIFT,
#अगर !defined(CONFIG_CPU_HAS_RIXI)
	_PAGE_NO_READ_SHIFT,
#पूर्ण_अगर
	_PAGE_WRITE_SHIFT,
	_PAGE_ACCESSED_SHIFT,
	_PAGE_MODIFIED_SHIFT,
#अगर defined(CONFIG_MIPS_HUGE_TLB_SUPPORT)
	_PAGE_HUGE_SHIFT,
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_HAS_PTE_SPECIAL)
	_PAGE_SPECIAL_SHIFT,
#पूर्ण_अगर
#अगर defined(CONFIG_HAVE_ARCH_SOFT_सूचीTY)
	_PAGE_SOFT_सूचीTY_SHIFT,
#पूर्ण_अगर
	/* Used by TLB hardware (placed in EntryLo*) */
#अगर defined(CONFIG_CPU_HAS_RIXI)
	_PAGE_NO_EXEC_SHIFT,
	_PAGE_NO_READ_SHIFT,
#पूर्ण_अगर
	_PAGE_GLOBAL_SHIFT,
	_PAGE_VALID_SHIFT,
	_PAGE_सूचीTY_SHIFT,
	_CACHE_SHIFT,
पूर्ण;

#पूर्ण_अगर /* defined(CONFIG_PHYS_ADDR_T_64BIT && defined(CONFIG_CPU_MIPS32) */

/* Used only by software */
#घोषणा _PAGE_PRESENT		(1 << _PAGE_PRESENT_SHIFT)
#घोषणा _PAGE_WRITE		(1 << _PAGE_WRITE_SHIFT)
#घोषणा _PAGE_ACCESSED		(1 << _PAGE_ACCESSED_SHIFT)
#घोषणा _PAGE_MODIFIED		(1 << _PAGE_MODIFIED_SHIFT)
#अगर defined(CONFIG_MIPS_HUGE_TLB_SUPPORT)
# define _PAGE_HUGE		(1 << _PAGE_HUGE_SHIFT)
#पूर्ण_अगर
#अगर defined(CONFIG_ARCH_HAS_PTE_SPECIAL)
# define _PAGE_SPECIAL		(1 << _PAGE_SPECIAL_SHIFT)
#अन्यथा
# define _PAGE_SPECIAL		0
#पूर्ण_अगर
#अगर defined(CONFIG_HAVE_ARCH_SOFT_सूचीTY)
# define _PAGE_SOFT_सूचीTY	(1 << _PAGE_SOFT_सूचीTY_SHIFT)
#अन्यथा
# define _PAGE_SOFT_सूचीTY	0
#पूर्ण_अगर

/* Used by TLB hardware (placed in EntryLo*) */
#अगर defined(CONFIG_XPA)
# define _PAGE_NO_EXEC		(1 << _PAGE_NO_EXEC_SHIFT)
#या_अगर defined(CONFIG_CPU_HAS_RIXI)
# define _PAGE_NO_EXEC		(cpu_has_rixi ? (1 << _PAGE_NO_EXEC_SHIFT) : 0)
#पूर्ण_अगर
#घोषणा _PAGE_NO_READ		(1 << _PAGE_NO_READ_SHIFT)
#घोषणा _PAGE_GLOBAL		(1 << _PAGE_GLOBAL_SHIFT)
#घोषणा _PAGE_VALID		(1 << _PAGE_VALID_SHIFT)
#घोषणा _PAGE_सूचीTY		(1 << _PAGE_सूचीTY_SHIFT)
#अगर defined(CONFIG_CPU_R3K_TLB)
# define _CACHE_UNCACHED	(1 << _CACHE_UNCACHED_SHIFT)
# define _CACHE_MASK		_CACHE_UNCACHED
# define _PFN_SHIFT		PAGE_SHIFT
#अन्यथा
# define _CACHE_MASK		(7 << _CACHE_SHIFT)
# define _PFN_SHIFT		(PAGE_SHIFT - 12 + _CACHE_SHIFT + 3)
#पूर्ण_अगर

#अगर_अघोषित _PAGE_NO_EXEC
#घोषणा _PAGE_NO_EXEC		0
#पूर्ण_अगर

#घोषणा _PAGE_SILENT_READ	_PAGE_VALID
#घोषणा _PAGE_SILENT_WRITE	_PAGE_सूचीTY

#घोषणा _PFN_MASK		(~((1 << (_PFN_SHIFT)) - 1))

/*
 * The final layouts of the PTE bits are:
 *
 *   64-bit, R1 or earlier:     CCC D V G [S H] M A W R P
 *   32-bit, R1 or earler:      CCC D V G M A W R P
 *   64-bit, R2 or later:       CCC D V G RI/R XI [S H] M A W P
 *   32-bit, R2 or later:       CCC D V G RI/R XI M A W P
 */


/*
 * pte_to_entrylo converts a page table entry (PTE) पूर्णांकo a Mips
 * entrylo0/1 value.
 */
अटल अंतरभूत uपूर्णांक64_t pte_to_entrylo(अचिन्हित दीर्घ pte_val)
अणु
#अगर_घोषित CONFIG_CPU_HAS_RIXI
	अगर (cpu_has_rixi) अणु
		पूर्णांक sa;
#अगर_घोषित CONFIG_32BIT
		sa = 31 - _PAGE_NO_READ_SHIFT;
#अन्यथा
		sa = 63 - _PAGE_NO_READ_SHIFT;
#पूर्ण_अगर
		/*
		 * C has no way to express that this is a DSRL
		 * _PAGE_NO_EXEC_SHIFT followed by a ROTR 2.  Luckily
		 * in the fast path this is करोne in assembly
		 */
		वापस (pte_val >> _PAGE_GLOBAL_SHIFT) |
			((pte_val & (_PAGE_NO_EXEC | _PAGE_NO_READ)) << sa);
	पूर्ण
#पूर्ण_अगर

	वापस pte_val >> _PAGE_GLOBAL_SHIFT;
पूर्ण

/*
 * Cache attributes
 */
#अगर defined(CONFIG_CPU_R3K_TLB)

#घोषणा _CACHE_CACHABLE_NONCOHERENT 0
#घोषणा _CACHE_UNCACHED_ACCELERATED _CACHE_UNCACHED

#या_अगर defined(CONFIG_CPU_SB1)

/* No penalty क्रम being coherent on the SB1, so just
   use it क्रम "noncoherent" spaces, too.  Shouldn't hurt. */

#घोषणा _CACHE_CACHABLE_NONCOHERENT (5<<_CACHE_SHIFT)

#पूर्ण_अगर

#अगर_अघोषित _CACHE_CACHABLE_NO_WA
#घोषणा _CACHE_CACHABLE_NO_WA		(0<<_CACHE_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित _CACHE_CACHABLE_WA
#घोषणा _CACHE_CACHABLE_WA		(1<<_CACHE_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित _CACHE_UNCACHED
#घोषणा _CACHE_UNCACHED			(2<<_CACHE_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित _CACHE_CACHABLE_NONCOHERENT
#घोषणा _CACHE_CACHABLE_NONCOHERENT	(3<<_CACHE_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित _CACHE_CACHABLE_CE
#घोषणा _CACHE_CACHABLE_CE		(4<<_CACHE_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित _CACHE_CACHABLE_COW
#घोषणा _CACHE_CACHABLE_COW		(5<<_CACHE_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित _CACHE_CACHABLE_CUW
#घोषणा _CACHE_CACHABLE_CUW		(6<<_CACHE_SHIFT)
#पूर्ण_अगर
#अगर_अघोषित _CACHE_UNCACHED_ACCELERATED
#घोषणा _CACHE_UNCACHED_ACCELERATED	(7<<_CACHE_SHIFT)
#पूर्ण_अगर

#घोषणा __READABLE	(_PAGE_SILENT_READ | _PAGE_ACCESSED)
#घोषणा __WRITEABLE	(_PAGE_SILENT_WRITE | _PAGE_WRITE | _PAGE_MODIFIED)

#घोषणा _PAGE_CHG_MASK	(_PAGE_ACCESSED | _PAGE_MODIFIED |	\
			 _PAGE_SOFT_सूचीTY | _PFN_MASK | _CACHE_MASK)

#पूर्ण_अगर /* _ASM_PGTABLE_BITS_H */
