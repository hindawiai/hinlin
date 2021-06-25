<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_PGTABLE_BITS_H
#घोषणा __ASM_CSKY_PGTABLE_BITS_H

/* implemented in software */
#घोषणा _PAGE_ACCESSED		(1<<7)
#घोषणा _PAGE_READ		(1<<8)
#घोषणा _PAGE_WRITE		(1<<9)
#घोषणा _PAGE_PRESENT		(1<<10)
#घोषणा _PAGE_MODIFIED		(1<<11)

/* implemented in hardware */
#घोषणा _PAGE_GLOBAL		(1<<0)
#घोषणा _PAGE_VALID		(1<<1)
#घोषणा _PAGE_सूचीTY		(1<<2)

#घोषणा _PAGE_SO		(1<<5)
#घोषणा _PAGE_BUF		(1<<6)
#घोषणा _PAGE_CACHE		(1<<3)
#घोषणा _CACHE_MASK		_PAGE_CACHE

#घोषणा _CACHE_CACHED		(_PAGE_CACHE | _PAGE_BUF)
#घोषणा _CACHE_UNCACHED		(0)

#घोषणा _PAGE_PROT_NONE		_PAGE_WRITE

/*
 * Encode and decode a swap entry
 *
 * Format of swap PTE:
 *     bit          0:    _PAGE_GLOBAL (zero)
 *     bit          1:    _PAGE_VALID (zero)
 *     bit      2 - 6:    swap type
 *     bit      7 - 8:    swap offset[0 - 1]
 *     bit          9:    _PAGE_WRITE (zero)
 *     bit         10:    _PAGE_PRESENT (zero)
 *     bit    11 - 31:    swap offset[2 - 22]
 */
#घोषणा __swp_type(x)			(((x).val >> 2) & 0x1f)
#घोषणा __swp_offset(x)			((((x).val >> 7) & 0x3) | \
					(((x).val >> 9) & 0x7ffffc))
#घोषणा __swp_entry(type, offset)	((swp_entry_t) अणु \
					((type & 0x1f) << 2) | \
					((offset & 0x3) << 7) | \
					((offset & 0x7ffffc) << 9)पूर्ण)

#पूर्ण_अगर /* __ASM_CSKY_PGTABLE_BITS_H */
