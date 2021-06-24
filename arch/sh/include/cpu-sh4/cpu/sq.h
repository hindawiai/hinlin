<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * include/यंत्र-sh/cpu-sh4/sq.h
 *
 * Copyright (C) 2001, 2002, 2003  Paul Mundt
 * Copyright (C) 2001, 2002  M. R. Brown
 */
#अगर_अघोषित __ASM_CPU_SH4_SQ_H
#घोषणा __ASM_CPU_SH4_SQ_H

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/page.h>

/*
 * Store queues range from e0000000-e3fffffc, allowing approx. 64MB to be
 * mapped to any physical address space. Since data is written (and aligned)
 * to 32-byte boundaries, we need to be sure that all allocations are aligned.
 */
#घोषणा SQ_SIZE                 32
#घोषणा SQ_ALIGN_MASK           (~(SQ_SIZE - 1))
#घोषणा SQ_ALIGN(addr)          (((addr)+SQ_SIZE-1) & SQ_ALIGN_MASK)

#घोषणा SQ_QACR0		(P4SEG_REG_BASE  + 0x38)
#घोषणा SQ_QACR1		(P4SEG_REG_BASE  + 0x3c)
#घोषणा SQ_ADDRMAX              (P4SEG_STORE_QUE + 0x04000000)

/* arch/sh/kernel/cpu/sh4/sq.c */
अचिन्हित दीर्घ sq_remap(अचिन्हित दीर्घ phys, अचिन्हित पूर्णांक size,
		       स्थिर अक्षर *name, pgprot_t prot);
व्योम sq_unmap(अचिन्हित दीर्घ vaddr);
व्योम sq_flush_range(अचिन्हित दीर्घ start, अचिन्हित पूर्णांक len);

#पूर्ण_अगर /* __ASM_CPU_SH4_SQ_H */
