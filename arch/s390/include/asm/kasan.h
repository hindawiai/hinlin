<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_KASAN_H
#घोषणा __ASM_KASAN_H

#समावेश <यंत्र/pgtable.h>

#अगर_घोषित CONFIG_KASAN

#घोषणा KASAN_SHADOW_SCALE_SHIFT 3
#घोषणा KASAN_SHADOW_SIZE						       \
	(_AC(1, UL) << (_REGION1_SHIFT - KASAN_SHADOW_SCALE_SHIFT))
#घोषणा KASAN_SHADOW_OFFSET	_AC(CONFIG_KASAN_SHADOW_OFFSET, UL)
#घोषणा KASAN_SHADOW_START	KASAN_SHADOW_OFFSET
#घोषणा KASAN_SHADOW_END	(KASAN_SHADOW_START + KASAN_SHADOW_SIZE)

बाह्य व्योम kasan_early_init(व्योम);
बाह्य व्योम kasan_copy_shaकरोw_mapping(व्योम);
बाह्य व्योम kasan_मुक्त_early_identity(व्योम);
बाह्य अचिन्हित दीर्घ kasan_vmax;

/*
 * Estimate kasan memory requirements, which it will reserve
 * at the very end of available physical memory. To estimate
 * that, we take पूर्णांकo account that kasan would require
 * 1/8 of available physical memory (क्रम shaकरोw memory) +
 * creating page tables क्रम the whole memory + shaकरोw memory
 * region (1 + 1/8). To keep page tables estimates simple take
 * the द्विगुन of combined ptes size.
 *
 * physmem parameter has to be alपढ़ोy adjusted अगर not entire physical memory
 * would be used (e.g. due to effect of "mem=" option).
 */
अटल अंतरभूत अचिन्हित दीर्घ kasan_estimate_memory_needs(अचिन्हित दीर्घ physmem)
अणु
	अचिन्हित दीर्घ kasan_needs;
	अचिन्हित दीर्घ pages;
	/* क्रम shaकरोw memory */
	kasan_needs = round_up(physmem / 8, PAGE_SIZE);
	/* क्रम paging काष्ठाures */
	pages = DIV_ROUND_UP(physmem + kasan_needs, PAGE_SIZE);
	kasan_needs += DIV_ROUND_UP(pages, _PAGE_ENTRIES) * _PAGE_TABLE_SIZE * 2;

	वापस kasan_needs;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम kasan_early_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kasan_copy_shaकरोw_mapping(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम kasan_मुक्त_early_identity(व्योम) अणु पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ kasan_estimate_memory_needs(अचिन्हित दीर्घ physmem) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
