<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_TLB_H
#घोषणा __ASM_CSKY_TLB_H

#समावेश <यंत्र/cacheflush.h>

#घोषणा tlb_start_vma(tlb, vma) \
	करो अणु \
		अगर (!(tlb)->fullmm) \
			flush_cache_range(vma, (vma)->vm_start, (vma)->vm_end); \
	पूर्ण  जबतक (0)

#घोषणा tlb_end_vma(tlb, vma) \
	करो अणु \
		अगर (!(tlb)->fullmm) \
			flush_tlb_range(vma, (vma)->vm_start, (vma)->vm_end); \
	पूर्ण  जबतक (0)

#घोषणा tlb_flush(tlb) flush_tlb_mm((tlb)->mm)

#समावेश <यंत्र-generic/tlb.h>

#पूर्ण_अगर /* __ASM_CSKY_TLB_H */
