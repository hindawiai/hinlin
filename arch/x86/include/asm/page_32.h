<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_PAGE_32_H
#घोषणा _ASM_X86_PAGE_32_H

#समावेश <यंत्र/page_32_types.h>

#अगर_अघोषित __ASSEMBLY__

#घोषणा __phys_addr_nodebug(x)	((x) - PAGE_OFFSET)
#अगर_घोषित CONFIG_DEBUG_VIRTUAL
बाह्य अचिन्हित दीर्घ __phys_addr(अचिन्हित दीर्घ);
#अन्यथा
#घोषणा __phys_addr(x)		__phys_addr_nodebug(x)
#पूर्ण_अगर
#घोषणा __phys_addr_symbol(x)	__phys_addr(x)
#घोषणा __phys_reloc_hide(x)	RELOC_HIDE((x), 0)

#अगर_घोषित CONFIG_FLATMEM
#घोषणा pfn_valid(pfn)		((pfn) < max_mapnr)
#पूर्ण_अगर /* CONFIG_FLATMEM */

#अगर_घोषित CONFIG_X86_USE_3DNOW
#समावेश <यंत्र/mmx.h>

अटल अंतरभूत व्योम clear_page(व्योम *page)
अणु
	mmx_clear_page(page);
पूर्ण

अटल अंतरभूत व्योम copy_page(व्योम *to, व्योम *from)
अणु
	mmx_copy_page(to, from);
पूर्ण
#अन्यथा  /* !CONFIG_X86_USE_3DNOW */
#समावेश <linux/माला.स>

अटल अंतरभूत व्योम clear_page(व्योम *page)
अणु
	स_रखो(page, 0, PAGE_SIZE);
पूर्ण

अटल अंतरभूत व्योम copy_page(व्योम *to, व्योम *from)
अणु
	स_नकल(to, from, PAGE_SIZE);
पूर्ण
#पूर्ण_अगर	/* CONFIG_X86_3DNOW */
#पूर्ण_अगर	/* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_PAGE_32_H */
