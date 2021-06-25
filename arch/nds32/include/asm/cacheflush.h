<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __NDS32_CACHEFLUSH_H__
#घोषणा __NDS32_CACHEFLUSH_H__

#समावेश <linux/mm.h>

#घोषणा PG_dcache_dirty PG_arch_1

व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
#घोषणा flush_icache_range flush_icache_range

व्योम flush_icache_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page);
#घोषणा flush_icache_page flush_icache_page

#अगर_घोषित CONFIG_CPU_CACHE_ALIASING
व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm);
व्योम flush_cache_dup_mm(काष्ठा mm_काष्ठा *mm);
व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
		       अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma,
		      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn);
व्योम flush_cache_kmaps(व्योम);
व्योम flush_cache_vmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
व्योम flush_cache_vunmap(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
व्योम flush_dcache_page(काष्ठा page *page);
व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
		       अचिन्हित दीर्घ vaddr, व्योम *dst, व्योम *src, पूर्णांक len);
व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
			 अचिन्हित दीर्घ vaddr, व्योम *dst, व्योम *src, पूर्णांक len);

#घोषणा ARCH_HAS_FLUSH_ANON_PAGE
व्योम flush_anon_page(काष्ठा vm_area_काष्ठा *vma,
		     काष्ठा page *page, अचिन्हित दीर्घ vaddr);

#घोषणा ARCH_HAS_FLUSH_KERNEL_DCACHE_PAGE
व्योम flush_kernel_dcache_page(काष्ठा page *page);
व्योम flush_kernel_vmap_range(व्योम *addr, पूर्णांक size);
व्योम invalidate_kernel_vmap_range(व्योम *addr, पूर्णांक size);
#घोषणा flush_dcache_mmap_lock(mapping)   xa_lock_irq(&(mapping)->i_pages)
#घोषणा flush_dcache_mmap_unlock(mapping) xa_unlock_irq(&(mapping)->i_pages)

#अन्यथा
व्योम flush_icache_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
	                     अचिन्हित दीर्घ addr, पूर्णांक len);
#घोषणा flush_icache_user_page flush_icache_user_page

#समावेश <यंत्र-generic/cacheflush.h>
#पूर्ण_अगर

#पूर्ण_अगर /* __NDS32_CACHEFLUSH_H__ */
