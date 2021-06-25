<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/map.h
 *
 *  Copyright (C) 1999-2000 Russell King
 *
 *  Page table mapping स्थिरructs and function prototypes
 */
#अगर_अघोषित __ASM_MACH_MAP_H
#घोषणा __ASM_MACH_MAP_H

#समावेश <यंत्र/पन.स>

काष्ठा map_desc अणु
	अचिन्हित दीर्घ भव;
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ length;
	अचिन्हित पूर्णांक type;
पूर्ण;

/* types 0-3 are defined in यंत्र/पन.स */
क्रमागत अणु
	MT_UNCACHED = 4,
	MT_CACHECLEAN,
	MT_MINICLEAN,
	MT_LOW_VECTORS,
	MT_HIGH_VECTORS,
	MT_MEMORY_RWX,
	MT_MEMORY_RW,
	MT_ROM,
	MT_MEMORY_RWX_NONCACHED,
	MT_MEMORY_RW_DTCM,
	MT_MEMORY_RWX_ITCM,
	MT_MEMORY_RW_SO,
	MT_MEMORY_DMA_READY,
पूर्ण;

#अगर_घोषित CONFIG_MMU
बाह्य व्योम iotable_init(काष्ठा map_desc *, पूर्णांक);
बाह्य व्योम vm_reserve_area_early(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size,
				  व्योम *caller);
बाह्य व्योम create_mapping_late(काष्ठा mm_काष्ठा *mm, काष्ठा map_desc *md,
				bool ng);

#अगर_घोषित CONFIG_DEBUG_LL
बाह्य व्योम debug_ll_addr(अचिन्हित दीर्घ *paddr, अचिन्हित दीर्घ *vaddr);
बाह्य व्योम debug_ll_io_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम debug_ll_io_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

काष्ठा mem_type;
बाह्य स्थिर काष्ठा mem_type *get_mem_type(अचिन्हित पूर्णांक type);
/*
 * बाह्यal पूर्णांकerface to remap single page with appropriate type
 */
बाह्य पूर्णांक ioremap_page(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ phys,
			स्थिर काष्ठा mem_type *mtype);
#अन्यथा
#घोषणा iotable_init(map,num)	करो अणु पूर्ण जबतक (0)
#घोषणा vm_reserve_area_early(a,s,c)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
