<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_HIGHMEM_H
#घोषणा _LINUX_HIGHMEM_H

#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hardirq.h>

#समावेश <यंत्र/cacheflush.h>

#समावेश "highmem-internal.h"

/**
 * kmap - Map a page क्रम दीर्घ term usage
 * @page:	Poपूर्णांकer to the page to be mapped
 *
 * Returns: The भव address of the mapping
 *
 * Can only be invoked from preemptible task context because on 32bit
 * प्रणालीs with CONFIG_HIGHMEM enabled this function might sleep.
 *
 * For प्रणालीs with CONFIG_HIGHMEM=n and क्रम pages in the low memory area
 * this वापसs the भव address of the direct kernel mapping.
 *
 * The वापसed भव address is globally visible and valid up to the
 * poपूर्णांक where it is unmapped via kunmap(). The poपूर्णांकer can be handed to
 * other contexts.
 *
 * For highmem pages on 32bit प्रणालीs this can be slow as the mapping space
 * is limited and रक्षित by a global lock. In हाल that there is no
 * mapping slot available the function blocks until a slot is released via
 * kunmap().
 */
अटल अंतरभूत व्योम *kmap(काष्ठा page *page);

/**
 * kunmap - Unmap the भव address mapped by kmap()
 * @addr:	Virtual address to be unmapped
 *
 * Counterpart to kmap(). A NOOP क्रम CONFIG_HIGHMEM=n and क्रम mappings of
 * pages in the low memory area.
 */
अटल अंतरभूत व्योम kunmap(काष्ठा page *page);

/**
 * kmap_to_page - Get the page क्रम a kmap'ed address
 * @addr:	The address to look up
 *
 * Returns: The page which is mapped to @addr.
 */
अटल अंतरभूत काष्ठा page *kmap_to_page(व्योम *addr);

/**
 * kmap_flush_unused - Flush all unused kmap mappings in order to
 *		       हटाओ stray mappings
 */
अटल अंतरभूत व्योम kmap_flush_unused(व्योम);

/**
 * kmap_local_page - Map a page क्रम temporary usage
 * @page:	Poपूर्णांकer to the page to be mapped
 *
 * Returns: The भव address of the mapping
 *
 * Can be invoked from any context.
 *
 * Requires careful handling when nesting multiple mappings because the map
 * management is stack based. The unmap has to be in the reverse order of
 * the map operation:
 *
 * addr1 = kmap_local_page(page1);
 * addr2 = kmap_local_page(page2);
 * ...
 * kunmap_local(addr2);
 * kunmap_local(addr1);
 *
 * Unmapping addr1 beक्रमe addr2 is invalid and causes malfunction.
 *
 * Contrary to kmap() mappings the mapping is only valid in the context of
 * the caller and cannot be handed to other contexts.
 *
 * On CONFIG_HIGHMEM=n kernels and क्रम low memory pages this वापसs the
 * भव address of the direct mapping. Only real highmem pages are
 * temporarily mapped.
 *
 * While it is signअगरicantly faster than kmap() क्रम the higmem हाल it
 * comes with restrictions about the poपूर्णांकer validity. Only use when really
 * necessary.
 *
 * On HIGHMEM enabled प्रणालीs mapping a highmem page has the side effect of
 * disabling migration in order to keep the भव address stable across
 * preemption. No caller of kmap_local_page() can rely on this side effect.
 */
अटल अंतरभूत व्योम *kmap_local_page(काष्ठा page *page);

/**
 * kmap_atomic - Atomically map a page क्रम temporary usage - Deprecated!
 * @page:	Poपूर्णांकer to the page to be mapped
 *
 * Returns: The भव address of the mapping
 *
 * Effectively a wrapper around kmap_local_page() which disables pagefaults
 * and preemption.
 *
 * Do not use in new code. Use kmap_local_page() instead.
 */
अटल अंतरभूत व्योम *kmap_atomic(काष्ठा page *page);

/**
 * kunmap_atomic - Unmap the भव address mapped by kmap_atomic()
 * @addr:	Virtual address to be unmapped
 *
 * Counterpart to kmap_atomic().
 *
 * Effectively a wrapper around kunmap_local() which additionally unकरोes
 * the side effects of kmap_atomic(), i.e. reenabling pagefaults and
 * preemption.
 */

/* Highmem related पूर्णांकerfaces क्रम management code */
अटल अंतरभूत अचिन्हित पूर्णांक nr_मुक्त_highpages(व्योम);
अटल अंतरभूत अचिन्हित दीर्घ totalhigh_pages(व्योम);

#अगर_अघोषित ARCH_HAS_FLUSH_ANON_PAGE
अटल अंतरभूत व्योम flush_anon_page(काष्ठा vm_area_काष्ठा *vma, काष्ठा page *page, अचिन्हित दीर्घ vmaddr)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ARCH_HAS_FLUSH_KERNEL_DCACHE_PAGE
अटल अंतरभूत व्योम flush_kernel_dcache_page(काष्ठा page *page)
अणु
पूर्ण
अटल अंतरभूत व्योम flush_kernel_vmap_range(व्योम *vaddr, पूर्णांक size)
अणु
पूर्ण
अटल अंतरभूत व्योम invalidate_kernel_vmap_range(व्योम *vaddr, पूर्णांक size)
अणु
पूर्ण
#पूर्ण_अगर

/* when CONFIG_HIGHMEM is not set these will be plain clear/copy_page */
#अगर_अघोषित clear_user_highpage
अटल अंतरभूत व्योम clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	व्योम *addr = kmap_atomic(page);
	clear_user_page(addr, vaddr, page);
	kunmap_atomic(addr);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE
/**
 * __alloc_zeroed_user_highpage - Allocate a zeroed HIGHMEM page क्रम a VMA with caller-specअगरied movable GFP flags
 * @movableflags: The GFP flags related to the pages future ability to move like __GFP_MOVABLE
 * @vma: The VMA the page is to be allocated क्रम
 * @vaddr: The भव address the page will be inserted पूर्णांकo
 *
 * This function will allocate a page क्रम a VMA but the caller is expected
 * to specअगरy via movableflags whether the page will be movable in the
 * future or not
 *
 * An architecture may override this function by defining
 * __HAVE_ARCH_ALLOC_ZEROED_USER_HIGHPAGE and providing their own
 * implementation.
 */
अटल अंतरभूत काष्ठा page *
__alloc_zeroed_user_highpage(gfp_t movableflags,
			काष्ठा vm_area_काष्ठा *vma,
			अचिन्हित दीर्घ vaddr)
अणु
	काष्ठा page *page = alloc_page_vma(GFP_HIGHUSER | movableflags,
			vma, vaddr);

	अगर (page)
		clear_user_highpage(page, vaddr);

	वापस page;
पूर्ण
#पूर्ण_अगर

/**
 * alloc_zeroed_user_highpage_movable - Allocate a zeroed HIGHMEM page क्रम a VMA that the caller knows can move
 * @vma: The VMA the page is to be allocated क्रम
 * @vaddr: The भव address the page will be inserted पूर्णांकo
 *
 * This function will allocate a page क्रम a VMA that the caller knows will
 * be able to migrate in the future using move_pages() or reclaimed
 */
अटल अंतरभूत काष्ठा page *
alloc_zeroed_user_highpage_movable(काष्ठा vm_area_काष्ठा *vma,
					अचिन्हित दीर्घ vaddr)
अणु
	वापस __alloc_zeroed_user_highpage(__GFP_MOVABLE, vma, vaddr);
पूर्ण

अटल अंतरभूत व्योम clear_highpage(काष्ठा page *page)
अणु
	व्योम *kaddr = kmap_atomic(page);
	clear_page(kaddr);
	kunmap_atomic(kaddr);
पूर्ण

/*
 * If we pass in a base or tail page, we can zero up to PAGE_SIZE.
 * If we pass in a head page, we can zero up to the size of the compound page.
 */
#अगर defined(CONFIG_HIGHMEM) && defined(CONFIG_TRANSPARENT_HUGEPAGE)
व्योम zero_user_segments(काष्ठा page *page, अचिन्हित start1, अचिन्हित end1,
		अचिन्हित start2, अचिन्हित end2);
#अन्यथा /* !HIGHMEM || !TRANSPARENT_HUGEPAGE */
अटल अंतरभूत व्योम zero_user_segments(काष्ठा page *page,
		अचिन्हित start1, अचिन्हित end1,
		अचिन्हित start2, अचिन्हित end2)
अणु
	व्योम *kaddr = kmap_atomic(page);
	अचिन्हित पूर्णांक i;

	BUG_ON(end1 > page_size(page) || end2 > page_size(page));

	अगर (end1 > start1)
		स_रखो(kaddr + start1, 0, end1 - start1);

	अगर (end2 > start2)
		स_रखो(kaddr + start2, 0, end2 - start2);

	kunmap_atomic(kaddr);
	क्रम (i = 0; i < compound_nr(page); i++)
		flush_dcache_page(page + i);
पूर्ण
#पूर्ण_अगर /* !HIGHMEM || !TRANSPARENT_HUGEPAGE */

अटल अंतरभूत व्योम zero_user_segment(काष्ठा page *page,
	अचिन्हित start, अचिन्हित end)
अणु
	zero_user_segments(page, start, end, 0, 0);
पूर्ण

अटल अंतरभूत व्योम zero_user(काष्ठा page *page,
	अचिन्हित start, अचिन्हित size)
अणु
	zero_user_segments(page, start, start + size, 0, 0);
पूर्ण

#अगर_अघोषित __HAVE_ARCH_COPY_USER_HIGHPAGE

अटल अंतरभूत व्योम copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	अक्षर *vfrom, *vto;

	vfrom = kmap_atomic(from);
	vto = kmap_atomic(to);
	copy_user_page(vto, vfrom, vaddr, to);
	kunmap_atomic(vto);
	kunmap_atomic(vfrom);
पूर्ण

#पूर्ण_अगर

#अगर_अघोषित __HAVE_ARCH_COPY_HIGHPAGE

अटल अंतरभूत व्योम copy_highpage(काष्ठा page *to, काष्ठा page *from)
अणु
	अक्षर *vfrom, *vto;

	vfrom = kmap_atomic(from);
	vto = kmap_atomic(to);
	copy_page(vto, vfrom);
	kunmap_atomic(vto);
	kunmap_atomic(vfrom);
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत व्योम स_नकल_page(काष्ठा page *dst_page, माप_प्रकार dst_off,
			       काष्ठा page *src_page, माप_प्रकार src_off,
			       माप_प्रकार len)
अणु
	अक्षर *dst = kmap_local_page(dst_page);
	अक्षर *src = kmap_local_page(src_page);

	VM_BUG_ON(dst_off + len > PAGE_SIZE || src_off + len > PAGE_SIZE);
	स_नकल(dst + dst_off, src + src_off, len);
	kunmap_local(src);
	kunmap_local(dst);
पूर्ण

अटल अंतरभूत व्योम स_हटाओ_page(काष्ठा page *dst_page, माप_प्रकार dst_off,
			       काष्ठा page *src_page, माप_प्रकार src_off,
			       माप_प्रकार len)
अणु
	अक्षर *dst = kmap_local_page(dst_page);
	अक्षर *src = kmap_local_page(src_page);

	VM_BUG_ON(dst_off + len > PAGE_SIZE || src_off + len > PAGE_SIZE);
	स_हटाओ(dst + dst_off, src + src_off, len);
	kunmap_local(src);
	kunmap_local(dst);
पूर्ण

अटल अंतरभूत व्योम स_रखो_page(काष्ठा page *page, माप_प्रकार offset, पूर्णांक val,
			       माप_प्रकार len)
अणु
	अक्षर *addr = kmap_local_page(page);

	VM_BUG_ON(offset + len > PAGE_SIZE);
	स_रखो(addr + offset, val, len);
	kunmap_local(addr);
पूर्ण

अटल अंतरभूत व्योम स_नकल_from_page(अक्षर *to, काष्ठा page *page,
				    माप_प्रकार offset, माप_प्रकार len)
अणु
	अक्षर *from = kmap_local_page(page);

	VM_BUG_ON(offset + len > PAGE_SIZE);
	स_नकल(to, from + offset, len);
	kunmap_local(from);
पूर्ण

अटल अंतरभूत व्योम स_नकल_to_page(काष्ठा page *page, माप_प्रकार offset,
				  स्थिर अक्षर *from, माप_प्रकार len)
अणु
	अक्षर *to = kmap_local_page(page);

	VM_BUG_ON(offset + len > PAGE_SIZE);
	स_नकल(to + offset, from, len);
	kunmap_local(to);
पूर्ण

अटल अंतरभूत व्योम memzero_page(काष्ठा page *page, माप_प्रकार offset, माप_प्रकार len)
अणु
	अक्षर *addr = kmap_atomic(page);
	स_रखो(addr + offset, 0, len);
	kunmap_atomic(addr);
पूर्ण

#पूर्ण_अगर /* _LINUX_HIGHMEM_H */
