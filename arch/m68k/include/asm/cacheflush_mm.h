<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_CACHEFLUSH_H
#घोषणा _M68K_CACHEFLUSH_H

#समावेश <linux/mm.h>
#अगर_घोषित CONFIG_COLDFIRE
#समावेश <यंत्र/mcfsim.h>
#पूर्ण_अगर

/* cache code */
#घोषणा FLUSH_I_AND_D	(0x00000808)
#घोषणा FLUSH_I		(0x00000008)

#अगर_अघोषित ICACHE_MAX_ADDR
#घोषणा ICACHE_MAX_ADDR	0
#घोषणा ICACHE_SET_MASK	0
#घोषणा DCACHE_MAX_ADDR	0
#घोषणा DCACHE_SETMASK	0
#पूर्ण_अगर
#अगर_अघोषित CACHE_MODE
#घोषणा	CACHE_MODE	0
#घोषणा	CACR_ICINVA	0
#घोषणा	CACR_DCINVA	0
#घोषणा	CACR_BCINVA	0
#पूर्ण_अगर

/*
 * ColdFire architecture has no way to clear inभागidual cache lines, so we
 * are stuck invalidating all the cache entries when we want a clear operation.
 */
अटल अंतरभूत व्योम clear_cf_icache(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	__यंत्र__ __अस्थिर__ (
		"movec	%0,%%cacr\n\t"
		"nop"
		:
		: "r" (CACHE_MODE | CACR_ICINVA | CACR_BCINVA));
पूर्ण

अटल अंतरभूत व्योम clear_cf_dcache(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	__यंत्र__ __अस्थिर__ (
		"movec	%0,%%cacr\n\t"
		"nop"
		:
		: "r" (CACHE_MODE | CACR_DCINVA));
पूर्ण

अटल अंतरभूत व्योम clear_cf_bcache(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	__यंत्र__ __अस्थिर__ (
		"movec	%0,%%cacr\n\t"
		"nop"
		:
		: "r" (CACHE_MODE | CACR_ICINVA | CACR_BCINVA | CACR_DCINVA));
पूर्ण

/*
 * Use the ColdFire cpushl inकाष्ठाion to push (and invalidate) cache lines.
 * The start and end addresses are cache line numbers not memory addresses.
 */
अटल अंतरभूत व्योम flush_cf_icache(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ set;

	क्रम (set = start; set <= end; set += (0x10 - 3)) अणु
		__यंत्र__ __अस्थिर__ (
			"cpushl %%ic,(%0)\n\t"
			"addq%.l #1,%0\n\t"
			"cpushl %%ic,(%0)\n\t"
			"addq%.l #1,%0\n\t"
			"cpushl %%ic,(%0)\n\t"
			"addq%.l #1,%0\n\t"
			"cpushl %%ic,(%0)"
			: "=a" (set)
			: "a" (set));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush_cf_dcache(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ set;

	क्रम (set = start; set <= end; set += (0x10 - 3)) अणु
		__यंत्र__ __अस्थिर__ (
			"cpushl %%dc,(%0)\n\t"
			"addq%.l #1,%0\n\t"
			"cpushl %%dc,(%0)\n\t"
			"addq%.l #1,%0\n\t"
			"cpushl %%dc,(%0)\n\t"
			"addq%.l #1,%0\n\t"
			"cpushl %%dc,(%0)"
			: "=a" (set)
			: "a" (set));
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम flush_cf_bcache(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ set;

	क्रम (set = start; set <= end; set += (0x10 - 3)) अणु
		__यंत्र__ __अस्थिर__ (
			"cpushl %%bc,(%0)\n\t"
			"addq%.l #1,%0\n\t"
			"cpushl %%bc,(%0)\n\t"
			"addq%.l #1,%0\n\t"
			"cpushl %%bc,(%0)\n\t"
			"addq%.l #1,%0\n\t"
			"cpushl %%bc,(%0)"
			: "=a" (set)
			: "a" (set));
	पूर्ण
पूर्ण

/*
 * Cache handling functions
 */

अटल अंतरभूत व्योम flush_icache(व्योम)
अणु
	अगर (CPU_IS_COLDFIRE) अणु
		flush_cf_icache(0, ICACHE_MAX_ADDR);
	पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु
		यंत्र अस्थिर (	"nop\n"
			"	.chip	68040\n"
			"	cpusha	%bc\n"
			"	.chip	68k");
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ पंचांगp;
		यंत्र अस्थिर (	"movec	%%cacr,%0\n"
			"	or.w	%1,%0\n"
			"	movec	%0,%%cacr"
			: "=&d" (पंचांगp)
			: "id" (FLUSH_I));
	पूर्ण
पूर्ण

/*
 * invalidate the cache क्रम the specअगरied memory range.
 * It starts at the physical address specअगरied क्रम
 * the given number of bytes.
 */
बाह्य व्योम cache_clear(अचिन्हित दीर्घ paddr, पूर्णांक len);
/*
 * push any dirty cache in the specअगरied memory range.
 * It starts at the physical address specअगरied क्रम
 * the given number of bytes.
 */
बाह्य व्योम cache_push(अचिन्हित दीर्घ paddr, पूर्णांक len);

/*
 * push and invalidate pages in the specअगरied user भव
 * memory range.
 */
बाह्य व्योम cache_push_v(अचिन्हित दीर्घ vaddr, पूर्णांक len);

/* This is needed whenever the भव mapping of the current
   process changes.  */
#घोषणा __flush_cache_all()					\
(अणु								\
	अगर (CPU_IS_COLDFIRE) अणु					\
		flush_cf_dcache(0, DCACHE_MAX_ADDR);		\
	पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु				\
		__यंत्र__ __अस्थिर__("nop\n\t"			\
				     ".chip 68040\n\t"		\
				     "cpusha %dc\n\t"		\
				     ".chip 68k");		\
	पूर्ण अन्यथा अणु						\
		अचिन्हित दीर्घ _पंचांगp;				\
		__यंत्र__ __अस्थिर__("movec %%cacr,%0\n\t"	\
				     "orw %1,%0\n\t"		\
				     "movec %0,%%cacr"		\
				     : "=&d" (_पंचांगp)		\
				     : "di" (FLUSH_I_AND_D));	\
	पूर्ण							\
पूर्ण)

#घोषणा __flush_cache_030()					\
(अणु								\
	अगर (CPU_IS_020_OR_030) अणु				\
		अचिन्हित दीर्घ _पंचांगp;				\
		__यंत्र__ __अस्थिर__("movec %%cacr,%0\n\t"	\
				     "orw %1,%0\n\t"		\
				     "movec %0,%%cacr"		\
				     : "=&d" (_पंचांगp)		\
				     : "di" (FLUSH_I_AND_D));	\
	पूर्ण							\
पूर्ण)

#घोषणा flush_cache_all() __flush_cache_all()

#घोषणा flush_cache_vmap(start, end)		flush_cache_all()
#घोषणा flush_cache_vunmap(start, end)		flush_cache_all()

अटल अंतरभूत व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm == current->mm)
		__flush_cache_030();
पूर्ण

#घोषणा flush_cache_dup_mm(mm)			flush_cache_mm(mm)

/* flush_cache_range/flush_cache_page must be macros to aव्योम
   a dependency on linux/mm.h, which includes this file... */
अटल अंतरभूत व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ start,
				     अचिन्हित दीर्घ end)
अणु
	अगर (vma->vm_mm == current->mm)
	        __flush_cache_030();
पूर्ण

अटल अंतरभूत व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr, अचिन्हित दीर्घ pfn)
अणु
	अगर (vma->vm_mm == current->mm)
	        __flush_cache_030();
पूर्ण


/* Push the page at kernel भव address and clear the icache */
/* RZ: use cpush %bc instead of cpush %dc, cinv %ic */
अटल अंतरभूत व्योम __flush_page_to_ram(व्योम *vaddr)
अणु
	अगर (CPU_IS_COLDFIRE) अणु
		अचिन्हित दीर्घ addr, start, end;
		addr = ((अचिन्हित दीर्घ) vaddr) & ~(PAGE_SIZE - 1);
		start = addr & ICACHE_SET_MASK;
		end = (addr + PAGE_SIZE - 1) & ICACHE_SET_MASK;
		अगर (start > end) अणु
			flush_cf_bcache(0, end);
			end = ICACHE_MAX_ADDR;
		पूर्ण
		flush_cf_bcache(start, end);
	पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु
		__यंत्र__ __अस्थिर__("nop\n\t"
				     ".chip 68040\n\t"
				     "cpushp %%bc,(%0)\n\t"
				     ".chip 68k"
				     : : "a" (__pa(vaddr)));
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ _पंचांगp;
		__यंत्र__ __अस्थिर__("movec %%cacr,%0\n\t"
				     "orw %1,%0\n\t"
				     "movec %0,%%cacr"
				     : "=&d" (_पंचांगp)
				     : "di" (FLUSH_I));
	पूर्ण
पूर्ण

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
#घोषणा flush_dcache_page(page)		__flush_page_to_ram(page_address(page))
#घोषणा flush_dcache_mmap_lock(mapping)		करो अणु पूर्ण जबतक (0)
#घोषणा flush_dcache_mmap_unlock(mapping)	करो अणु पूर्ण जबतक (0)
#घोषणा flush_icache_page(vma, page)	__flush_page_to_ram(page_address(page))

बाह्य व्योम flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
				    अचिन्हित दीर्घ addr, पूर्णांक len);
बाह्य व्योम flush_icache_range(अचिन्हित दीर्घ address, अचिन्हित दीर्घ endaddr);
बाह्य व्योम flush_icache_user_range(अचिन्हित दीर्घ address,
		अचिन्हित दीर्घ endaddr);

अटल अंतरभूत व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma,
				     काष्ठा page *page, अचिन्हित दीर्घ vaddr,
				     व्योम *dst, व्योम *src, पूर्णांक len)
अणु
	flush_cache_page(vma, vaddr, page_to_pfn(page));
	स_नकल(dst, src, len);
	flush_icache_user_page(vma, page, vaddr, len);
पूर्ण
अटल अंतरभूत व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma,
				       काष्ठा page *page, अचिन्हित दीर्घ vaddr,
				       व्योम *dst, व्योम *src, पूर्णांक len)
अणु
	flush_cache_page(vma, vaddr, page_to_pfn(page));
	स_नकल(dst, src, len);
पूर्ण

#पूर्ण_अगर /* _M68K_CACHEFLUSH_H */
