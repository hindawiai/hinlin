<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_TLB_H
#घोषणा _ASM_RISCV_TLB_H

काष्ठा mmu_gather;

अटल व्योम tlb_flush(काष्ठा mmu_gather *tlb);

#घोषणा tlb_flush tlb_flush
#समावेश <यंत्र-generic/tlb.h>

अटल अंतरभूत व्योम tlb_flush(काष्ठा mmu_gather *tlb)
अणु
	flush_tlb_mm(tlb->mm);
पूर्ण

#पूर्ण_अगर /* _ASM_RISCV_TLB_H */
