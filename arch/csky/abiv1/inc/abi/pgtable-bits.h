<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_PGTABLE_BITS_H
#घोषणा __ASM_CSKY_PGTABLE_BITS_H

/* implemented in software */
#घोषणा _PAGE_PRESENT		(1<<0)
#घोषणा _PAGE_READ		(1<<1)
#घोषणा _PAGE_WRITE		(1<<2)
#घोषणा _PAGE_ACCESSED		(1<<3)
#घोषणा _PAGE_MODIFIED		(1<<4)

/* implemented in hardware */
#घोषणा _PAGE_GLOBAL		(1<<6)
#घोषणा _PAGE_VALID		(1<<7)
#घोषणा _PAGE_सूचीTY		(1<<8)

#घोषणा _PAGE_CACHE		(3<<9)
#घोषणा _PAGE_UNCACHE		(2<<9)
#घोषणा _PAGE_SO		_PAGE_UNCACHE
#घोषणा _CACHE_MASK		(7<<9)

#घोषणा _CACHE_CACHED		_PAGE_CACHE
#घोषणा _CACHE_UNCACHED		_PAGE_UNCACHE

#घोषणा _PAGE_PROT_NONE		_PAGE_READ

/*
 * Encode and decode a swap entry
 *
 * Format of swap PTE:
 *     bit          0:    _PAGE_PRESENT (zero)
 *     bit          1:    _PAGE_READ (zero)
 *     bit      2 - 5:    swap type[0 - 3]
 *     bit          6:    _PAGE_GLOBAL (zero)
 *     bit          7:    _PAGE_VALID (zero)
 *     bit          8:    swap type[4]
 *     bit     9 - 31:    swap offset
 */
#घोषणा __swp_type(x)			((((x).val >> 2) & 0xf) | \
					(((x).val >> 4) & 0x10))
#घोषणा __swp_offset(x)			((x).val >> 9)
#घोषणा __swp_entry(type, offset)	((swp_entry_t) अणु \
					((type & 0xf) << 2) | \
					((type & 0x10) << 4) | \
					((offset) << 9)पूर्ण)

#घोषणा HAVE_ARCH_UNMAPPED_AREA

#पूर्ण_अगर /* __ASM_CSKY_PGTABLE_BITS_H */
