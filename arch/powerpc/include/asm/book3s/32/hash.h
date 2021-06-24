<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_BOOK3S_32_HASH_H
#घोषणा _ASM_POWERPC_BOOK3S_32_HASH_H
#अगर_घोषित __KERNEL__

/*
 * The "classic" 32-bit implementation of the PowerPC MMU uses a hash
 * table containing PTEs, together with a set of 16 segment रेजिस्टरs,
 * to define the भव to physical address mapping.
 *
 * We use the hash table as an extended TLB, i.e. a cache of currently
 * active mappings.  We मुख्यtain a two-level page table tree, much
 * like that used by the i386, क्रम the sake of the Linux memory
 * management code.  Low-level assembler code in hash_low_32.S
 * (procedure hash_page) is responsible क्रम extracting ptes from the
 * tree and putting them पूर्णांकo the hash table when necessary, and
 * updating the accessed and modअगरied bits in the page table tree.
 */

#घोषणा _PAGE_PRESENT	0x001	/* software: pte contains a translation */
#घोषणा _PAGE_HASHPTE	0x002	/* hash_page has made an HPTE क्रम this pte */
#घोषणा _PAGE_USER	0x004	/* usermode access allowed */
#घोषणा _PAGE_GUARDED	0x008	/* G: prohibit speculative access */
#घोषणा _PAGE_COHERENT	0x010	/* M: enक्रमce memory coherence (SMP प्रणालीs) */
#घोषणा _PAGE_NO_CACHE	0x020	/* I: cache inhibit */
#घोषणा _PAGE_WRITETHRU	0x040	/* W: cache ग_लिखो-through */
#घोषणा _PAGE_सूचीTY	0x080	/* C: page changed */
#घोषणा _PAGE_ACCESSED	0x100	/* R: page referenced */
#घोषणा _PAGE_EXEC	0x200	/* software: exec allowed */
#घोषणा _PAGE_RW	0x400	/* software: user ग_लिखो access allowed */
#घोषणा _PAGE_SPECIAL	0x800	/* software: Special page */

#अगर_घोषित CONFIG_PTE_64BIT
/* We never clear the high word of the pte */
#घोषणा _PTE_NONE_MASK	(0xffffffff00000000ULL | _PAGE_HASHPTE)
#अन्यथा
#घोषणा _PTE_NONE_MASK	_PAGE_HASHPTE
#पूर्ण_अगर

#घोषणा _PMD_PRESENT	0
#घोषणा _PMD_PRESENT_MASK (PAGE_MASK)
#घोषणा _PMD_BAD	(~PAGE_MASK)

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_BOOK3S_32_HASH_H */
