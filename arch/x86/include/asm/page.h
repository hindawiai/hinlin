<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PAGE_H
#घोषणा _ASM_X86_PAGE_H

#समावेश <linux/types.h>

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/page_types.h>

#अगर_घोषित CONFIG_X86_64
#समावेश <यंत्र/page_64.h>
#अन्यथा
#समावेश <यंत्र/page_32.h>
#पूर्ण_अगर	/* CONFIG_X86_64 */

#अगर_अघोषित __ASSEMBLY__

काष्ठा page;

#समावेश <linux/range.h>
बाह्य काष्ठा range pfn_mapped[];
बाह्य पूर्णांक nr_pfn_mapped;

अटल अंतरभूत व्योम clear_user_page(व्योम *page, अचिन्हित दीर्घ vaddr,
				   काष्ठा page *pg)
अणु
	clear_page(page);
पूर्ण

अटल अंतरभूत व्योम copy_user_page(व्योम *to, व्योम *from, अचिन्हित दीर्घ vaddr,
				  काष्ठा page *topage)
अणु
	copy_page(to, from);
पूर्ण

#घोषणा __alloc_zeroed_user_highpage(movableflags, vma, vaddr) \
	alloc_page_vma(GFP_HIGHUSER | __GFP_ZERO | movableflags, vma, vaddr)
#घोषणा __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE

#अगर_अघोषित __pa
#घोषणा __pa(x)		__phys_addr((अचिन्हित दीर्घ)(x))
#पूर्ण_अगर

#घोषणा __pa_nodebug(x)	__phys_addr_nodebug((अचिन्हित दीर्घ)(x))
/* __pa_symbol should be used क्रम C visible symbols.
   This seems to be the official gcc blessed way to करो such arithmetic. */
/*
 * We need __phys_reloc_hide() here because gcc may assume that there is no
 * overflow during __pa() calculation and can optimize it unexpectedly.
 * Newer versions of gcc provide -fno-strict-overflow चयन to handle this
 * हाल properly. Once all supported versions of gcc understand it, we can
 * हटाओ this Vooकरोo magic stuff. (i.e. once gcc3.x is deprecated)
 */
#घोषणा __pa_symbol(x) \
	__phys_addr_symbol(__phys_reloc_hide((अचिन्हित दीर्घ)(x)))

#अगर_अघोषित __va
#घोषणा __va(x)			((व्योम *)((अचिन्हित दीर्घ)(x)+PAGE_OFFSET))
#पूर्ण_अगर

#घोषणा __boot_va(x)		__va(x)
#घोषणा __boot_pa(x)		__pa(x)

/*
 * virt_to_page(kaddr) वापसs a valid poपूर्णांकer अगर and only अगर
 * virt_addr_valid(kaddr) वापसs true.
 */
#घोषणा virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)
#घोषणा pfn_to_kaddr(pfn)      __va((pfn) << PAGE_SHIFT)
बाह्य bool __virt_addr_valid(अचिन्हित दीर्घ kaddr);
#घोषणा virt_addr_valid(kaddr)	__virt_addr_valid((अचिन्हित दीर्घ) (kaddr))

#पूर्ण_अगर	/* __ASSEMBLY__ */

#समावेश <यंत्र-generic/memory_model.h>
#समावेश <यंत्र-generic/getorder.h>

#घोषणा HAVE_ARCH_HUGETLB_UNMAPPED_AREA

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर /* _ASM_X86_PAGE_H */
