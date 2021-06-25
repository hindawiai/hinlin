<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_ARC_TLBFLUSH__
#घोषणा __ASM_ARC_TLBFLUSH__

#समावेश <linux/mm.h>

व्योम local_flush_tlb_all(व्योम);
व्योम local_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
व्योम local_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);
व्योम local_flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम local_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
व्योम local_flush_pmd_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
			       अचिन्हित दीर्घ end);
#पूर्ण_अगर

#अगर_अघोषित CONFIG_SMP
#घोषणा flush_tlb_range(vma, s, e)	local_flush_tlb_range(vma, s, e)
#घोषणा flush_tlb_page(vma, page)	local_flush_tlb_page(vma, page)
#घोषणा flush_tlb_kernel_range(s, e)	local_flush_tlb_kernel_range(s, e)
#घोषणा flush_tlb_all()			local_flush_tlb_all()
#घोषणा flush_tlb_mm(mm)		local_flush_tlb_mm(mm)
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
#घोषणा flush_pmd_tlb_range(vma, s, e)	local_flush_pmd_tlb_range(vma, s, e)
#पूर्ण_अगर
#अन्यथा
बाह्य व्योम flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
							 अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);
बाह्य व्योम flush_tlb_kernel_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_tlb_all(व्योम);
बाह्य व्योम flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
बाह्य व्योम flush_pmd_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर
