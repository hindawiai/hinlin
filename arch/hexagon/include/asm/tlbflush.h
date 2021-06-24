<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TLB flush support क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_TLBFLUSH_H
#घोषणा _ASM_TLBFLUSH_H

#समावेश <linux/mm.h>
#समावेश <यंत्र/processor.h>

/*
 * TLB flushing -- in "SMP", these routines get defined to be the
 * ones from smp.c, अन्यथा they are some local flavors.
 */

/*
 * These functions are commonly macros, but in the पूर्णांकerests of
 * VM vs. native implementation and code size, we simply declare
 * the function prototypes here.
 */
बाह्य व्योम tlb_flush_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr);
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_one(अचिन्हित दीर्घ);

/*
 * "This is called in munmap when we have मुक्तd up some page-table pages.
 * We करोn't need to करो anything here..."
 *
 * The VM kernel करोesn't walk page tables, and they are passed to the VMM
 * by logical address. There करोesn't seem to be any possibility that they
 * could be referenced by the VM kernel based on a stale mapping, since
 * they would only be located by consulting the mm काष्ठाure, and they
 * will have been purged from that काष्ठाure by the munmap.  Seems like
 * a noop on HVM as well.
 */
#घोषणा flush_tlb_pgtables(mm, start, end)

#पूर्ण_अगर
