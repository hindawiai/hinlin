<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_CACHEFLUSH_H
#घोषणा _ASM_GENERIC_CACHEFLUSH_H

काष्ठा mm_काष्ठा;
काष्ठा vm_area_काष्ठा;
काष्ठा page;
काष्ठा address_space;

/*
 * The cache करोesn't need to be flushed when TLB entries change when
 * the cache is mapped to physical memory, not भव memory
 */
#अगर_अघोषित flush_cache_all
अटल अंतरभूत व्योम flush_cache_all(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_cache_mm
अटल अंतरभूत व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_cache_dup_mm
अटल अंतरभूत व्योम flush_cache_dup_mm(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_cache_range
अटल अंतरभूत व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
				     अचिन्हित दीर्घ start,
				     अचिन्हित दीर्घ end)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_cache_page
अटल अंतरभूत व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ vmaddr,
				    अचिन्हित दीर्घ pfn)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE
अटल अंतरभूत व्योम flush_dcache_page(काष्ठा page *page)
अणु
पूर्ण
#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 0
#पूर्ण_अगर


#अगर_अघोषित flush_dcache_mmap_lock
अटल अंतरभूत व्योम flush_dcache_mmap_lock(काष्ठा address_space *mapping)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_dcache_mmap_unlock
अटल अंतरभूत व्योम flush_dcache_mmap_unlock(काष्ठा address_space *mapping)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_icache_range
अटल अंतरभूत व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_icache_user_range
#घोषणा flush_icache_user_range flush_icache_range
#पूर्ण_अगर

#अगर_अघोषित flush_icache_page
अटल अंतरभूत व्योम flush_icache_page(काष्ठा vm_area_काष्ठा *vma,
				     काष्ठा page *page)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_icache_user_page
अटल अंतरभूत व्योम flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma,
					   काष्ठा page *page,
					   अचिन्हित दीर्घ addr, पूर्णांक len)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_cache_vmap
अटल अंतरभूत व्योम flush_cache_vmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित flush_cache_vunmap
अटल अंतरभूत व्योम flush_cache_vunmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित copy_to_user_page
#घोषणा copy_to_user_page(vma, page, vaddr, dst, src, len)	\
	करो अणु \
		स_नकल(dst, src, len); \
		flush_icache_user_page(vma, page, vaddr, len); \
	पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_अघोषित copy_from_user_page
#घोषणा copy_from_user_page(vma, page, vaddr, dst, src, len) \
	स_नकल(dst, src, len)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_GENERIC_CACHEFLUSH_H */
