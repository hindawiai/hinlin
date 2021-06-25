<शैली गुरु>
/******************************************************************************
 * grant_table.h
 *
 * Two sets of functionality:
 * 1. Granting क्रमeign access to our memory reservation.
 * 2. Accessing others' memory reservations via grant references.
 * (i.e., mechanisms क्रम both sender and recipient of grant references)
 *
 * Copyright (c) 2004-2005, K A Fraser
 * Copyright (c) 2005, Christopher Clark
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित __ASM_GNTTAB_H__
#घोषणा __ASM_GNTTAB_H__

#समावेश <यंत्र/page.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/grant_table.h>

#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/features.h>
#समावेश <xen/page.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/page-flags.h>
#समावेश <linux/kernel.h>

/*
 * Technically there's no reliably invalid grant reference or grant handle,
 * so pick the value that is the most unlikely one to be observed valid.
 */
#घोषणा INVALID_GRANT_REF          ((grant_ref_t)-1)
#घोषणा INVALID_GRANT_HANDLE       ((grant_handle_t)-1)

#घोषणा GNTTAB_RESERVED_XENSTORE 1

/* NR_GRANT_FRAMES must be less than or equal to that configured in Xen */
#घोषणा NR_GRANT_FRAMES 4

काष्ठा gnttab_मुक्त_callback अणु
	काष्ठा gnttab_मुक्त_callback *next;
	व्योम (*fn)(व्योम *);
	व्योम *arg;
	u16 count;
पूर्ण;

काष्ठा gntab_unmap_queue_data;

प्रकार व्योम (*gnttab_unmap_refs_करोne)(पूर्णांक result, काष्ठा gntab_unmap_queue_data *data);

काष्ठा gntab_unmap_queue_data
अणु
	काष्ठा delayed_work	gnttab_work;
	व्योम *data;
	gnttab_unmap_refs_करोne	करोne;
	काष्ठा gnttab_unmap_grant_ref *unmap_ops;
	काष्ठा gnttab_unmap_grant_ref *kunmap_ops;
	काष्ठा page **pages;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक age;
पूर्ण;

पूर्णांक gnttab_init(व्योम);
पूर्णांक gnttab_suspend(व्योम);
पूर्णांक gnttab_resume(व्योम);

पूर्णांक gnttab_grant_क्रमeign_access(करोmid_t करोmid, अचिन्हित दीर्घ frame,
				पूर्णांक पढ़ोonly);

/*
 * End access through the given grant reference, अगरf the grant entry is no
 * दीर्घer in use.  Return 1 अगर the grant entry was मुक्तd, 0 अगर it is still in
 * use.
 */
पूर्णांक gnttab_end_क्रमeign_access_ref(grant_ref_t ref, पूर्णांक पढ़ोonly);

/*
 * Eventually end access through the given grant reference, and once that
 * access has been ended, मुक्त the given page too.  Access will be ended
 * immediately अगरf the grant entry is not in use, otherwise it will happen
 * some समय later.  page may be 0, in which हाल no मुक्तing will occur.
 */
व्योम gnttab_end_क्रमeign_access(grant_ref_t ref, पूर्णांक पढ़ोonly,
			       अचिन्हित दीर्घ page);

पूर्णांक gnttab_grant_क्रमeign_transfer(करोmid_t करोmid, अचिन्हित दीर्घ pfn);

अचिन्हित दीर्घ gnttab_end_क्रमeign_transfer_ref(grant_ref_t ref);
अचिन्हित दीर्घ gnttab_end_क्रमeign_transfer(grant_ref_t ref);

पूर्णांक gnttab_query_क्रमeign_access(grant_ref_t ref);

/*
 * operations on reserved batches of grant references
 */
पूर्णांक gnttab_alloc_grant_references(u16 count, grant_ref_t *pनिजी_head);

व्योम gnttab_मुक्त_grant_reference(grant_ref_t ref);

व्योम gnttab_मुक्त_grant_references(grant_ref_t head);

पूर्णांक gnttab_empty_grant_references(स्थिर grant_ref_t *pनिजी_head);

पूर्णांक gnttab_claim_grant_reference(grant_ref_t *pनिजी_head);

व्योम gnttab_release_grant_reference(grant_ref_t *निजी_head,
				    grant_ref_t release);

व्योम gnttab_request_मुक्त_callback(काष्ठा gnttab_मुक्त_callback *callback,
				  व्योम (*fn)(व्योम *), व्योम *arg, u16 count);
व्योम gnttab_cancel_मुक्त_callback(काष्ठा gnttab_मुक्त_callback *callback);

व्योम gnttab_grant_क्रमeign_access_ref(grant_ref_t ref, करोmid_t करोmid,
				     अचिन्हित दीर्घ frame, पूर्णांक पढ़ोonly);

/* Give access to the first 4K of the page */
अटल अंतरभूत व्योम gnttab_page_grant_क्रमeign_access_ref_one(
	grant_ref_t ref, करोmid_t करोmid,
	काष्ठा page *page, पूर्णांक पढ़ोonly)
अणु
	gnttab_grant_क्रमeign_access_ref(ref, करोmid, xen_page_to_gfn(page),
					पढ़ोonly);
पूर्ण

व्योम gnttab_grant_क्रमeign_transfer_ref(grant_ref_t, करोmid_t करोmid,
				       अचिन्हित दीर्घ pfn);

अटल अंतरभूत व्योम
gnttab_set_map_op(काष्ठा gnttab_map_grant_ref *map, phys_addr_t addr,
		  uपूर्णांक32_t flags, grant_ref_t ref, करोmid_t करोmid)
अणु
	अगर (flags & GNTMAP_contains_pte)
		map->host_addr = addr;
	अन्यथा अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		map->host_addr = __pa(addr);
	अन्यथा
		map->host_addr = addr;

	map->flags = flags;
	map->ref = ref;
	map->करोm = करोmid;
	map->status = 1; /* arbitrary positive value */
पूर्ण

अटल अंतरभूत व्योम
gnttab_set_unmap_op(काष्ठा gnttab_unmap_grant_ref *unmap, phys_addr_t addr,
		    uपूर्णांक32_t flags, grant_handle_t handle)
अणु
	अगर (flags & GNTMAP_contains_pte)
		unmap->host_addr = addr;
	अन्यथा अगर (xen_feature(XENFEAT_स्वतः_translated_physmap))
		unmap->host_addr = __pa(addr);
	अन्यथा
		unmap->host_addr = addr;

	unmap->handle = handle;
	unmap->dev_bus_addr = 0;
पूर्ण

पूर्णांक arch_gnttab_init(अचिन्हित दीर्घ nr_shared, अचिन्हित दीर्घ nr_status);
पूर्णांक arch_gnttab_map_shared(xen_pfn_t *frames, अचिन्हित दीर्घ nr_gframes,
			   अचिन्हित दीर्घ max_nr_gframes,
			   व्योम **__shared);
पूर्णांक arch_gnttab_map_status(uपूर्णांक64_t *frames, अचिन्हित दीर्घ nr_gframes,
			   अचिन्हित दीर्घ max_nr_gframes,
			   grant_status_t **__shared);
व्योम arch_gnttab_unmap(व्योम *shared, अचिन्हित दीर्घ nr_gframes);

काष्ठा grant_frames अणु
	xen_pfn_t *pfn;
	अचिन्हित पूर्णांक count;
	व्योम *vaddr;
पूर्ण;
बाह्य काष्ठा grant_frames xen_स्वतः_xlat_grant_frames;
अचिन्हित पूर्णांक gnttab_max_grant_frames(व्योम);
पूर्णांक gnttab_setup_स्वतः_xlat_frames(phys_addr_t addr);
व्योम gnttab_मुक्त_स्वतः_xlat_frames(व्योम);

#घोषणा gnttab_map_vaddr(map) ((व्योम *)(map.host_virt_addr))

पूर्णांक gnttab_alloc_pages(पूर्णांक nr_pages, काष्ठा page **pages);
व्योम gnttab_मुक्त_pages(पूर्णांक nr_pages, काष्ठा page **pages);

काष्ठा gnttab_page_cache अणु
	spinlock_t		lock;
#अगर_घोषित CONFIG_XEN_UNPOPULATED_ALLOC
	काष्ठा page		*pages;
#अन्यथा
	काष्ठा list_head	pages;
#पूर्ण_अगर
	अचिन्हित पूर्णांक		num_pages;
पूर्ण;

व्योम gnttab_page_cache_init(काष्ठा gnttab_page_cache *cache);
पूर्णांक gnttab_page_cache_get(काष्ठा gnttab_page_cache *cache, काष्ठा page **page);
व्योम gnttab_page_cache_put(काष्ठा gnttab_page_cache *cache, काष्ठा page **page,
			   अचिन्हित पूर्णांक num);
व्योम gnttab_page_cache_shrink(काष्ठा gnttab_page_cache *cache,
			      अचिन्हित पूर्णांक num);

#अगर_घोषित CONFIG_XEN_GRANT_DMA_ALLOC
काष्ठा gnttab_dma_alloc_args अणु
	/* Device क्रम which DMA memory will be/was allocated. */
	काष्ठा device *dev;
	/* If set then DMA buffer is coherent and ग_लिखो-combine otherwise. */
	bool coherent;

	पूर्णांक nr_pages;
	काष्ठा page **pages;
	xen_pfn_t *frames;
	व्योम *vaddr;
	dma_addr_t dev_bus_addr;
पूर्ण;

पूर्णांक gnttab_dma_alloc_pages(काष्ठा gnttab_dma_alloc_args *args);
पूर्णांक gnttab_dma_मुक्त_pages(काष्ठा gnttab_dma_alloc_args *args);
#पूर्ण_अगर

पूर्णांक gnttab_pages_set_निजी(पूर्णांक nr_pages, काष्ठा page **pages);
व्योम gnttab_pages_clear_निजी(पूर्णांक nr_pages, काष्ठा page **pages);

पूर्णांक gnttab_map_refs(काष्ठा gnttab_map_grant_ref *map_ops,
		    काष्ठा gnttab_map_grant_ref *kmap_ops,
		    काष्ठा page **pages, अचिन्हित पूर्णांक count);
पूर्णांक gnttab_unmap_refs(काष्ठा gnttab_unmap_grant_ref *unmap_ops,
		      काष्ठा gnttab_unmap_grant_ref *kunmap_ops,
		      काष्ठा page **pages, अचिन्हित पूर्णांक count);
व्योम gnttab_unmap_refs_async(काष्ठा gntab_unmap_queue_data* item);
पूर्णांक gnttab_unmap_refs_sync(काष्ठा gntab_unmap_queue_data *item);


/* Perक्रमm a batch of grant map/copy operations. Retry every batch slot
 * क्रम which the hypervisor वापसs GNTST_eagain. This is typically due
 * to paged out target frames.
 *
 * Will retry क्रम 1, 2, ... 255 ms, i.e. 256 बार during 32 seconds.
 *
 * Return value in each iand every status field of the batch guaranteed
 * to not be GNTST_eagain.
 */
व्योम gnttab_batch_map(काष्ठा gnttab_map_grant_ref *batch, अचिन्हित count);
व्योम gnttab_batch_copy(काष्ठा gnttab_copy *batch, अचिन्हित count);


काष्ठा xen_page_क्रमeign अणु
	करोmid_t करोmid;
	grant_ref_t gref;
पूर्ण;

अटल अंतरभूत काष्ठा xen_page_क्रमeign *xen_page_क्रमeign(काष्ठा page *page)
अणु
	अगर (!PageForeign(page))
		वापस शून्य;
#अगर BITS_PER_LONG < 64
	वापस (काष्ठा xen_page_क्रमeign *)page->निजी;
#अन्यथा
	BUILD_BUG_ON(माप(काष्ठा xen_page_क्रमeign) > BITS_PER_LONG);
	वापस (काष्ठा xen_page_क्रमeign *)&page->निजी;
#पूर्ण_अगर
पूर्ण

/* Split Linux page in chunk of the size of the grant and call fn
 *
 * Parameters of fn:
 *	gfn: guest frame number
 *	offset: offset in the grant
 *	len: length of the data in the grant.
 *	data: पूर्णांकernal inक्रमmation
 */
प्रकार व्योम (*xen_grant_fn_t)(अचिन्हित दीर्घ gfn, अचिन्हित पूर्णांक offset,
			       अचिन्हित पूर्णांक len, व्योम *data);

व्योम gnttab_क्रमeach_grant_in_range(काष्ठा page *page,
				   अचिन्हित पूर्णांक offset,
				   अचिन्हित पूर्णांक len,
				   xen_grant_fn_t fn,
				   व्योम *data);

/* Helper to get to call fn only on the first "grant chunk" */
अटल अंतरभूत व्योम gnttab_क्रम_one_grant(काष्ठा page *page, अचिन्हित पूर्णांक offset,
					अचिन्हित len, xen_grant_fn_t fn,
					व्योम *data)
अणु
	/* The first request is limited to the size of one grant */
	len = min_t(अचिन्हित पूर्णांक, XEN_PAGE_SIZE - (offset & ~XEN_PAGE_MASK),
		    len);

	gnttab_क्रमeach_grant_in_range(page, offset, len, fn, data);
पूर्ण

/* Get @nr_grefs grants from an array of page and call fn क्रम each grant */
व्योम gnttab_क्रमeach_grant(काष्ठा page **pages,
			  अचिन्हित पूर्णांक nr_grefs,
			  xen_grant_fn_t fn,
			  व्योम *data);

/* Get the number of grant in a specअगरied region
 *
 * start: Offset from the beginning of the first page
 * len: total length of data (can cross multiple page)
 */
अटल अंतरभूत अचिन्हित पूर्णांक gnttab_count_grant(अचिन्हित पूर्णांक start,
					      अचिन्हित पूर्णांक len)
अणु
	वापस XEN_PFN_UP(xen_offset_in_page(start) + len);
पूर्ण

#पूर्ण_अगर /* __ASM_GNTTAB_H__ */
