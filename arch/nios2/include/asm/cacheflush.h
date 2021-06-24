<शैली गुरु>
/*
 * Copyright (C) 2003 Microtronix Datacom Ltd.
 * Copyright (C) 2000-2002 Greg Ungerer <gerg@snapgear.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#अगर_अघोषित _ASM_NIOS2_CACHEFLUSH_H
#घोषणा _ASM_NIOS2_CACHEFLUSH_H

#समावेश <linux/mm_types.h>

/*
 * This flag is used to indicate that the page poपूर्णांकed to by a pte is clean
 * and करोes not require cleaning beक्रमe वापसing it to the user.
 */
#घोषणा PG_dcache_clean PG_arch_1

काष्ठा mm_काष्ठा;

बाह्य व्योम flush_cache_all(व्योम);
बाह्य व्योम flush_cache_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_cache_dup_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
	अचिन्हित दीर्घ end);
बाह्य व्योम flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr,
	अचिन्हित दीर्घ pfn);
#घोषणा ARCH_IMPLEMENTS_FLUSH_DCACHE_PAGE 1
बाह्य व्योम flush_dcache_page(काष्ठा page *page);

बाह्य व्योम flush_icache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम flush_icache_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page);

#घोषणा flush_cache_vmap(start, end)		flush_dcache_range(start, end)
#घोषणा flush_cache_vunmap(start, end)		flush_dcache_range(start, end)

बाह्य व्योम copy_to_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
				अचिन्हित दीर्घ user_vaddr,
				व्योम *dst, व्योम *src, पूर्णांक len);
बाह्य व्योम copy_from_user_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page,
				अचिन्हित दीर्घ user_vaddr,
				व्योम *dst, व्योम *src, पूर्णांक len);

बाह्य व्योम flush_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम invalidate_dcache_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#घोषणा flush_dcache_mmap_lock(mapping)		xa_lock_irq(&mapping->i_pages)
#घोषणा flush_dcache_mmap_unlock(mapping)	xa_unlock_irq(&mapping->i_pages)

#पूर्ण_अगर /* _ASM_NIOS2_CACHEFLUSH_H */
