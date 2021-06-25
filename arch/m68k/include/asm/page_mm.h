<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_PAGE_MM_H
#घोषणा _M68K_PAGE_MM_H

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/compiler.h>
#समावेश <यंत्र/module.h>

/*
 * We करोn't need to check क्रम alignment etc.
 */
#अगर_घोषित CPU_M68040_OR_M68060_ONLY
अटल अंतरभूत व्योम copy_page(व्योम *to, व्योम *from)
अणु
  अचिन्हित दीर्घ पंचांगp;

  __यंत्र__ __अस्थिर__("1:\t"
		       ".chip 68040\n\t"
		       "move16 %1@+,%0@+\n\t"
		       "move16 %1@+,%0@+\n\t"
		       ".chip 68k\n\t"
		       "dbra  %2,1b\n\t"
		       : "=a" (to), "=a" (from), "=d" (पंचांगp)
		       : "0" (to), "1" (from) , "2" (PAGE_SIZE / 32 - 1)
		       );
पूर्ण

अटल अंतरभूत व्योम clear_page(व्योम *page)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अचिन्हित दीर्घ *sp = page;

	*sp++ = 0;
	*sp++ = 0;
	*sp++ = 0;
	*sp++ = 0;

	__यंत्र__ __अस्थिर__("1:\t"
			     ".chip 68040\n\t"
			     "move16 %2@+,%0@+\n\t"
			     ".chip 68k\n\t"
			     "subqw  #8,%2\n\t"
			     "subqw  #8,%2\n\t"
			     "dbra   %1,1b\n\t"
			     : "=a" (sp), "=d" (पंचांगp)
			     : "a" (page), "0" (sp),
			       "1" ((PAGE_SIZE - 16) / 16 - 1));
पूर्ण

#अन्यथा
#घोषणा clear_page(page)	स_रखो((page), 0, PAGE_SIZE)
#घोषणा copy_page(to,from)	स_नकल((to), (from), PAGE_SIZE)
#पूर्ण_अगर

#घोषणा clear_user_page(addr, vaddr, page)	\
	करो अणु	clear_page(addr);		\
		flush_dcache_page(page);	\
	पूर्ण जबतक (0)
#घोषणा copy_user_page(to, from, vaddr, page)	\
	करो अणु	copy_page(to, from);		\
		flush_dcache_page(page);	\
	पूर्ण जबतक (0)

बाह्य अचिन्हित दीर्घ m68k_memoffset;

#अगर_अघोषित CONFIG_SUN3

#घोषणा WANT_PAGE_VIRTUAL

अटल अंतरभूत अचिन्हित दीर्घ ___pa(व्योम *vaddr)
अणु
	अचिन्हित दीर्घ paddr;
	यंत्र (
		"1:	addl #0,%0\n"
		m68k_fixup(%c2, 1b+2)
		: "=r" (paddr)
		: "0" (vaddr), "i" (m68k_fixup_memoffset));
	वापस paddr;
पूर्ण
#घोषणा __pa(vaddr)	___pa((व्योम *)(दीर्घ)(vaddr))
अटल अंतरभूत व्योम *__va(अचिन्हित दीर्घ paddr)
अणु
	व्योम *vaddr;
	यंत्र (
		"1:	subl #0,%0\n"
		m68k_fixup(%c2, 1b+2)
		: "=r" (vaddr)
		: "0" (paddr), "i" (m68k_fixup_memoffset));
	वापस vaddr;
पूर्ण

#अन्यथा	/* !CONFIG_SUN3 */
/* This #घोषणा is a horrible hack to suppress lots of warnings. --m */
#घोषणा __pa(x) ___pa((अचिन्हित दीर्घ)(x))
अटल अंतरभूत अचिन्हित दीर्घ ___pa(अचिन्हित दीर्घ x)
अणु
     अगर(x == 0)
	  वापस 0;
     अगर(x >= PAGE_OFFSET)
        वापस (x-PAGE_OFFSET);
     अन्यथा
        वापस (x+0x2000000);
पूर्ण

अटल अंतरभूत व्योम *__va(अचिन्हित दीर्घ x)
अणु
     अगर(x == 0)
	  वापस (व्योम *)0;

     अगर(x < 0x2000000)
        वापस (व्योम *)(x+PAGE_OFFSET);
     अन्यथा
        वापस (व्योम *)(x-0x2000000);
पूर्ण
#पूर्ण_अगर	/* CONFIG_SUN3 */

/*
 * NOTE: भव isn't really correct, actually it should be the offset पूर्णांकo the
 * memory node, but we have no highmem, so that works क्रम now.
 * TODO: implement (fast) pfn<->pgdat_idx conversion functions, this makes lots
 * of the shअगरts unnecessary.
 */
#घोषणा virt_to_pfn(kaddr)	(__pa(kaddr) >> PAGE_SHIFT)
#घोषणा pfn_to_virt(pfn)	__va((pfn) << PAGE_SHIFT)

बाह्य पूर्णांक m68k_virt_to_node_shअगरt;

#अगर_अघोषित CONFIG_DISCONTIGMEM
#घोषणा __virt_to_node(addr)	(&pg_data_map[0])
#अन्यथा
बाह्य काष्ठा pglist_data *pg_data_table[];

अटल अंतरभूत __attribute_स्थिर__ पूर्णांक __virt_to_node_shअगरt(व्योम)
अणु
	पूर्णांक shअगरt;

	यंत्र (
		"1:	moveq	#0,%0\n"
		m68k_fixup(%c1, 1b)
		: "=d" (shअगरt)
		: "i" (m68k_fixup_vnode_shअगरt));
	वापस shअगरt;
पूर्ण

#घोषणा __virt_to_node(addr)	(pg_data_table[(अचिन्हित दीर्घ)(addr) >> __virt_to_node_shअगरt()])
#पूर्ण_अगर

#घोषणा virt_to_page(addr) (अणु						\
	pfn_to_page(virt_to_pfn(addr));					\
पूर्ण)
#घोषणा page_to_virt(page) (अणु						\
	pfn_to_virt(page_to_pfn(page));					\
पूर्ण)

#अगर_घोषित CONFIG_DISCONTIGMEM
#घोषणा pfn_to_page(pfn) (अणु						\
	अचिन्हित दीर्घ __pfn = (pfn);					\
	काष्ठा pglist_data *pgdat;					\
	pgdat = __virt_to_node((अचिन्हित दीर्घ)pfn_to_virt(__pfn));	\
	pgdat->node_mem_map + (__pfn - pgdat->node_start_pfn);		\
पूर्ण)
#घोषणा page_to_pfn(_page) (अणु						\
	स्थिर काष्ठा page *__p = (_page);				\
	काष्ठा pglist_data *pgdat;					\
	pgdat = &pg_data_map[page_to_nid(__p)];				\
	((__p) - pgdat->node_mem_map) + pgdat->node_start_pfn;		\
पूर्ण)
#अन्यथा
#घोषणा ARCH_PFN_OFFSET (m68k_memory[0].addr >> PAGE_SHIFT)
#समावेश <यंत्र-generic/memory_model.h>
#पूर्ण_अगर

#घोषणा virt_addr_valid(kaddr)	((अचिन्हित दीर्घ)(kaddr) >= PAGE_OFFSET && (अचिन्हित दीर्घ)(kaddr) < (अचिन्हित दीर्घ)high_memory)
#घोषणा pfn_valid(pfn)		virt_addr_valid(pfn_to_virt(pfn))

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _M68K_PAGE_MM_H */
