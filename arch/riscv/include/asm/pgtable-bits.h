<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_PGTABLE_BITS_H
#घोषणा _ASM_RISCV_PGTABLE_BITS_H

/*
 * PTE क्रमmat:
 * | XLEN-1  10 | 9             8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0
 *       PFN      reserved क्रम SW   D   A   G   U   X   W   R   V
 */

#घोषणा _PAGE_ACCESSED_OFFSET 6

#घोषणा _PAGE_PRESENT   (1 << 0)
#घोषणा _PAGE_READ      (1 << 1)    /* Readable */
#घोषणा _PAGE_WRITE     (1 << 2)    /* Writable */
#घोषणा _PAGE_EXEC      (1 << 3)    /* Executable */
#घोषणा _PAGE_USER      (1 << 4)    /* User */
#घोषणा _PAGE_GLOBAL    (1 << 5)    /* Global */
#घोषणा _PAGE_ACCESSED  (1 << 6)    /* Set by hardware on any access */
#घोषणा _PAGE_सूचीTY     (1 << 7)    /* Set by hardware on any ग_लिखो */
#घोषणा _PAGE_SOFT      (1 << 8)    /* Reserved क्रम software */

#घोषणा _PAGE_SPECIAL   _PAGE_SOFT
#घोषणा _PAGE_TABLE     _PAGE_PRESENT

/*
 * _PAGE_PROT_NONE is set on not-present pages (and ignored by the hardware) to
 * distinguish them from swapped out pages
 */
#घोषणा _PAGE_PROT_NONE _PAGE_READ

#घोषणा _PAGE_PFN_SHIFT 10

/* Set of bits to preserve across pte_modअगरy() */
#घोषणा _PAGE_CHG_MASK  (~(अचिन्हित दीर्घ)(_PAGE_PRESENT | _PAGE_READ |	\
					  _PAGE_WRITE | _PAGE_EXEC |	\
					  _PAGE_USER | _PAGE_GLOBAL))

#पूर्ण_अगर /* _ASM_RISCV_PGTABLE_BITS_H */
