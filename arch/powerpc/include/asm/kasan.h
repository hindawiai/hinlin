<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_KASAN_H
#घोषणा __ASM_KASAN_H

#अगर_घोषित CONFIG_KASAN
#घोषणा _GLOBAL_KASAN(fn)	_GLOBAL(__##fn)
#घोषणा _GLOBAL_TOC_KASAN(fn)	_GLOBAL_TOC(__##fn)
#घोषणा EXPORT_SYMBOL_KASAN(fn)	EXPORT_SYMBOL(__##fn)
#अन्यथा
#घोषणा _GLOBAL_KASAN(fn)	_GLOBAL(fn)
#घोषणा _GLOBAL_TOC_KASAN(fn)	_GLOBAL_TOC(fn)
#घोषणा EXPORT_SYMBOL_KASAN(fn)
#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

#समावेश <यंत्र/page.h>
#समावेश <linux/sizes.h>

#घोषणा KASAN_SHADOW_SCALE_SHIFT	3

#अगर_घोषित CONFIG_MODULES
#घोषणा KASAN_KERN_START	ALIGN_DOWN(PAGE_OFFSET - SZ_256M, SZ_256M)
#अन्यथा
#घोषणा KASAN_KERN_START	PAGE_OFFSET
#पूर्ण_अगर

#घोषणा KASAN_SHADOW_START	(KASAN_SHADOW_OFFSET + \
				 (KASAN_KERN_START >> KASAN_SHADOW_SCALE_SHIFT))

#घोषणा KASAN_SHADOW_OFFSET	ASM_CONST(CONFIG_KASAN_SHADOW_OFFSET)

#घोषणा KASAN_SHADOW_END	(-(-KASAN_SHADOW_START >> KASAN_SHADOW_SCALE_SHIFT))

#अगर_घोषित CONFIG_KASAN
व्योम kasan_early_init(व्योम);
व्योम kasan_mmu_init(व्योम);
व्योम kasan_init(व्योम);
व्योम kasan_late_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kasan_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kasan_mmu_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kasan_late_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम kasan_update_early_region(अचिन्हित दीर्घ k_start, अचिन्हित दीर्घ k_end, pte_t pte);
पूर्णांक kasan_init_shaकरोw_page_tables(अचिन्हित दीर्घ k_start, अचिन्हित दीर्घ k_end);
पूर्णांक kasan_init_region(व्योम *start, माप_प्रकार size);

#पूर्ण_अगर /* __ASSEMBLY */
#पूर्ण_अगर
