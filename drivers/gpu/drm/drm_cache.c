<शैली गुरु>
/**************************************************************************
 *
 * Copyright (c) 2006-2007 Tungsten Graphics, Inc., Cedar Park, TX., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
/*
 * Authors: Thomas Hellstrथघm <thomas-at-tungstengraphics-करोt-com>
 */

#समावेश <linux/export.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mem_encrypt.h>
#समावेश <xen/xen.h>

#समावेश <drm/drm_cache.h>

#अगर defined(CONFIG_X86)
#समावेश <यंत्र/smp.h>

/*
 * clflushopt is an unordered inकाष्ठाion which needs fencing with mfence or
 * sfence to aव्योम ordering issues.  For drm_clflush_page this fencing happens
 * in the caller.
 */
अटल व्योम
drm_clflush_page(काष्ठा page *page)
अणु
	uपूर्णांक8_t *page_भव;
	अचिन्हित पूर्णांक i;
	स्थिर पूर्णांक size = boot_cpu_data.x86_clflush_size;

	अगर (unlikely(page == शून्य))
		वापस;

	page_भव = kmap_atomic(page);
	क्रम (i = 0; i < PAGE_SIZE; i += size)
		clflushopt(page_भव + i);
	kunmap_atomic(page_भव);
पूर्ण

अटल व्योम drm_cache_flush_clflush(काष्ठा page *pages[],
				    अचिन्हित दीर्घ num_pages)
अणु
	अचिन्हित दीर्घ i;

	mb(); /*Full memory barrier used beक्रमe so that CLFLUSH is ordered*/
	क्रम (i = 0; i < num_pages; i++)
		drm_clflush_page(*pages++);
	mb(); /*Also used after CLFLUSH so that all cache is flushed*/
पूर्ण
#पूर्ण_अगर

/**
 * drm_clflush_pages - Flush dcache lines of a set of pages.
 * @pages: List of pages to be flushed.
 * @num_pages: Number of pages in the array.
 *
 * Flush every data cache line entry that poपूर्णांकs to an address beदीर्घing
 * to a page in the array.
 */
व्योम
drm_clflush_pages(काष्ठा page *pages[], अचिन्हित दीर्घ num_pages)
अणु

#अगर defined(CONFIG_X86)
	अगर (अटल_cpu_has(X86_FEATURE_CLFLUSH)) अणु
		drm_cache_flush_clflush(pages, num_pages);
		वापस;
	पूर्ण

	अगर (wbinvd_on_all_cpus())
		pr_err("Timed out waiting for cache flush\n");

#या_अगर defined(__घातerpc__)
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < num_pages; i++) अणु
		काष्ठा page *page = pages[i];
		व्योम *page_भव;

		अगर (unlikely(page == शून्य))
			जारी;

		page_भव = kmap_atomic(page);
		flush_dcache_range((अचिन्हित दीर्घ)page_भव,
				   (अचिन्हित दीर्घ)page_भव + PAGE_SIZE);
		kunmap_atomic(page_भव);
	पूर्ण
#अन्यथा
	pr_err("Architecture has no drm_cache.c support\n");
	WARN_ON_ONCE(1);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(drm_clflush_pages);

/**
 * drm_clflush_sg - Flush dcache lines poपूर्णांकing to a scather-gather.
 * @st: काष्ठा sg_table.
 *
 * Flush every data cache line entry that poपूर्णांकs to an address in the
 * sg.
 */
व्योम
drm_clflush_sg(काष्ठा sg_table *st)
अणु
#अगर defined(CONFIG_X86)
	अगर (अटल_cpu_has(X86_FEATURE_CLFLUSH)) अणु
		काष्ठा sg_page_iter sg_iter;

		mb(); /*CLFLUSH is ordered only by using memory barriers*/
		क्रम_each_sgtable_page(st, &sg_iter, 0)
			drm_clflush_page(sg_page_iter_page(&sg_iter));
		mb(); /*Make sure that all cache line entry is flushed*/

		वापस;
	पूर्ण

	अगर (wbinvd_on_all_cpus())
		pr_err("Timed out waiting for cache flush\n");
#अन्यथा
	pr_err("Architecture has no drm_cache.c support\n");
	WARN_ON_ONCE(1);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(drm_clflush_sg);

/**
 * drm_clflush_virt_range - Flush dcache lines of a region
 * @addr: Initial kernel memory address.
 * @length: Region size.
 *
 * Flush every data cache line entry that poपूर्णांकs to an address in the
 * region requested.
 */
व्योम
drm_clflush_virt_range(व्योम *addr, अचिन्हित दीर्घ length)
अणु
#अगर defined(CONFIG_X86)
	अगर (अटल_cpu_has(X86_FEATURE_CLFLUSH)) अणु
		स्थिर पूर्णांक size = boot_cpu_data.x86_clflush_size;
		व्योम *end = addr + length;

		addr = (व्योम *)(((अचिन्हित दीर्घ)addr) & -size);
		mb(); /*CLFLUSH is only ordered with a full memory barrier*/
		क्रम (; addr < end; addr += size)
			clflushopt(addr);
		clflushopt(end - 1); /* क्रमce serialisation */
		mb(); /*Ensure that evry data cache line entry is flushed*/
		वापस;
	पूर्ण

	अगर (wbinvd_on_all_cpus())
		pr_err("Timed out waiting for cache flush\n");
#अन्यथा
	pr_err("Architecture has no drm_cache.c support\n");
	WARN_ON_ONCE(1);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(drm_clflush_virt_range);

bool drm_need_swiotlb(पूर्णांक dma_bits)
अणु
	काष्ठा resource *पंचांगp;
	resource_माप_प्रकार max_iomem = 0;

	/*
	 * Xen paraभव hosts require swiotlb regardless of requested dma
	 * transfer size.
	 *
	 * NOTE: Really, what it requires is use of the dma_alloc_coherent
	 *       allocator used in tपंचांग_dma_populate() instead of
	 *       tपंचांग_populate_and_map_pages(), which bounce buffers so much in
	 *       Xen it leads to swiotlb buffer exhaustion.
	 */
	अगर (xen_pv_करोमुख्य())
		वापस true;

	/*
	 * Enक्रमce dma_alloc_coherent when memory encryption is active as well
	 * क्रम the same reasons as क्रम Xen paraभव hosts.
	 */
	अगर (mem_encrypt_active())
		वापस true;

	क्रम (पंचांगp = iomem_resource.child; पंचांगp; पंचांगp = पंचांगp->sibling)
		max_iomem = max(max_iomem,  पंचांगp->end);

	वापस max_iomem > ((u64)1 << dma_bits);
पूर्ण
EXPORT_SYMBOL(drm_need_swiotlb);
