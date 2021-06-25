<शैली गुरु>
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009 Wind River Systems Inc
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_PGTABLE_BITS_H
#घोषणा _ASM_NIOS2_PGTABLE_BITS_H

/*
 * These are actual hardware defined protection bits in the tlbacc रेजिस्टर
 * which looks like this:
 *
 * 31 30 ... 26 25 24 23 22 21 20 19 18 ...  1  0
 * ignored........  C  R  W  X  G PFN............
 */
#घोषणा _PAGE_GLOBAL	(1<<20)
#घोषणा _PAGE_EXEC	(1<<21)
#घोषणा _PAGE_WRITE	(1<<22)
#घोषणा _PAGE_READ	(1<<23)
#घोषणा _PAGE_CACHED	(1<<24)	/* C: data access cacheable */

/*
 * Software defined bits. They are ignored by the hardware and always पढ़ो back
 * as zero, but can be written as non-zero.
 */
#घोषणा _PAGE_PRESENT	(1<<25)	/* PTE contains a translation */
#घोषणा _PAGE_ACCESSED	(1<<26)	/* page referenced */
#घोषणा _PAGE_सूचीTY	(1<<27)	/* dirty page */

#पूर्ण_अगर /* _ASM_NIOS2_PGTABLE_BITS_H */
