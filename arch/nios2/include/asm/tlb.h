<शैली गुरु>
/*
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009 Wind River Systems Inc
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_TLB_H
#घोषणा _ASM_NIOS2_TLB_H

बाह्य व्योम set_mmu_pid(अचिन्हित दीर्घ pid);

/*
 * NIOS32 करोes have flush_tlb_range(), but it lacks a limit and fallback to
 * full mm invalidation. So use flush_tlb_mm() क्रम everything.
 */

#समावेश <linux/pagemap.h>
#समावेश <यंत्र-generic/tlb.h>

#पूर्ण_अगर /* _ASM_NIOS2_TLB_H */
