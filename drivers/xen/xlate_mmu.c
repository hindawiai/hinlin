<शैली गुरु>
/*
 * MMU operations common to all स्वतः-translated physmap guests.
 *
 * Copyright (C) 2015 Citrix Systems R&D Ltd.
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
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/xen.h>
#समावेश <xen/xen-ops.h>
#समावेश <xen/page.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/balloon.h>

प्रकार व्योम (*xen_gfn_fn_t)(अचिन्हित दीर्घ gfn, व्योम *data);

/* Break करोwn the pages in 4KB chunk and call fn क्रम each gfn */
अटल व्योम xen_क्रम_each_gfn(काष्ठा page **pages, अचिन्हित nr_gfn,
			     xen_gfn_fn_t fn, व्योम *data)
अणु
	अचिन्हित दीर्घ xen_pfn = 0;
	काष्ठा page *page;
	पूर्णांक i;

	क्रम (i = 0; i < nr_gfn; i++) अणु
		अगर ((i % XEN_PFN_PER_PAGE) == 0) अणु
			page = pages[i / XEN_PFN_PER_PAGE];
			xen_pfn = page_to_xen_pfn(page);
		पूर्ण
		fn(pfn_to_gfn(xen_pfn++), data);
	पूर्ण
पूर्ण

काष्ठा remap_data अणु
	xen_pfn_t *fgfn; /* क्रमeign करोमुख्य's gfn */
	पूर्णांक nr_fgfn; /* Number of क्रमeign gfn left to map */
	pgprot_t prot;
	करोmid_t  करोmid;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक index;
	काष्ठा page **pages;
	काष्ठा xen_remap_gfn_info *info;
	पूर्णांक *err_ptr;
	पूर्णांक mapped;

	/* Hypercall parameters */
	पूर्णांक h_errs[XEN_PFN_PER_PAGE];
	xen_uदीर्घ_t h_idxs[XEN_PFN_PER_PAGE];
	xen_pfn_t h_gpfns[XEN_PFN_PER_PAGE];

	पूर्णांक h_iter;	/* Iterator */
पूर्ण;

अटल व्योम setup_hparams(अचिन्हित दीर्घ gfn, व्योम *data)
अणु
	काष्ठा remap_data *info = data;

	info->h_idxs[info->h_iter] = *info->fgfn;
	info->h_gpfns[info->h_iter] = gfn;
	info->h_errs[info->h_iter] = 0;

	info->h_iter++;
	info->fgfn++;
पूर्ण

अटल पूर्णांक remap_pte_fn(pte_t *ptep, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा remap_data *info = data;
	काष्ठा page *page = info->pages[info->index++];
	pte_t pte = pte_mkspecial(pfn_pte(page_to_pfn(page), info->prot));
	पूर्णांक rc, nr_gfn;
	uपूर्णांक32_t i;
	काष्ठा xen_add_to_physmap_range xatp = अणु
		.करोmid = DOMID_SELF,
		.क्रमeign_करोmid = info->करोmid,
		.space = XENMAPSPACE_gmfn_क्रमeign,
	पूर्ण;

	nr_gfn = min_t(typeof(info->nr_fgfn), XEN_PFN_PER_PAGE, info->nr_fgfn);
	info->nr_fgfn -= nr_gfn;

	info->h_iter = 0;
	xen_क्रम_each_gfn(&page, nr_gfn, setup_hparams, info);
	BUG_ON(info->h_iter != nr_gfn);

	set_xen_guest_handle(xatp.idxs, info->h_idxs);
	set_xen_guest_handle(xatp.gpfns, info->h_gpfns);
	set_xen_guest_handle(xatp.errs, info->h_errs);
	xatp.size = nr_gfn;

	rc = HYPERVISOR_memory_op(XENMEM_add_to_physmap_range, &xatp);

	/* info->err_ptr expect to have one error status per Xen PFN */
	क्रम (i = 0; i < nr_gfn; i++) अणु
		पूर्णांक err = (rc < 0) ? rc : info->h_errs[i];

		*(info->err_ptr++) = err;
		अगर (!err)
			info->mapped++;
	पूर्ण

	/*
	 * Note: The hypercall will वापस 0 in most of the हाल अगर even अगर
	 * all the fgmfn are not mapped. We still have to update the pte
	 * as the userspace may decide to जारी.
	 */
	अगर (!rc)
		set_pte_at(info->vma->vm_mm, addr, ptep, pte);

	वापस 0;
पूर्ण

पूर्णांक xen_xlate_remap_gfn_array(काष्ठा vm_area_काष्ठा *vma,
			      अचिन्हित दीर्घ addr,
			      xen_pfn_t *gfn, पूर्णांक nr,
			      पूर्णांक *err_ptr, pgprot_t prot,
			      अचिन्हित करोmid,
			      काष्ठा page **pages)
अणु
	पूर्णांक err;
	काष्ठा remap_data data;
	अचिन्हित दीर्घ range = DIV_ROUND_UP(nr, XEN_PFN_PER_PAGE) << PAGE_SHIFT;

	/* Kept here क्रम the purpose of making sure code करोesn't अवरोध
	   x86 PVOPS */
	BUG_ON(!((vma->vm_flags & (VM_PFNMAP | VM_IO)) == (VM_PFNMAP | VM_IO)));

	data.fgfn = gfn;
	data.nr_fgfn = nr;
	data.prot  = prot;
	data.करोmid = करोmid;
	data.vma   = vma;
	data.pages = pages;
	data.index = 0;
	data.err_ptr = err_ptr;
	data.mapped = 0;

	err = apply_to_page_range(vma->vm_mm, addr, range,
				  remap_pte_fn, &data);
	वापस err < 0 ? err : data.mapped;
पूर्ण
EXPORT_SYMBOL_GPL(xen_xlate_remap_gfn_array);

अटल व्योम unmap_gfn(अचिन्हित दीर्घ gfn, व्योम *data)
अणु
	काष्ठा xen_हटाओ_from_physmap xrp;

	xrp.करोmid = DOMID_SELF;
	xrp.gpfn = gfn;
	(व्योम)HYPERVISOR_memory_op(XENMEM_हटाओ_from_physmap, &xrp);
पूर्ण

पूर्णांक xen_xlate_unmap_gfn_range(काष्ठा vm_area_काष्ठा *vma,
			      पूर्णांक nr, काष्ठा page **pages)
अणु
	xen_क्रम_each_gfn(pages, nr, unmap_gfn, शून्य);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xen_xlate_unmap_gfn_range);

काष्ठा map_balloon_pages अणु
	xen_pfn_t *pfns;
	अचिन्हित पूर्णांक idx;
पूर्ण;

अटल व्योम setup_balloon_gfn(अचिन्हित दीर्घ gfn, व्योम *data)
अणु
	काष्ठा map_balloon_pages *info = data;

	info->pfns[info->idx++] = gfn;
पूर्ण

/**
 * xen_xlate_map_ballooned_pages - map a new set of ballooned pages
 * @gfns: वापसs the array of corresponding GFNs
 * @virt: वापसs the भव address of the mapped region
 * @nr_grant_frames: number of GFNs
 * @वापस 0 on success, error otherwise
 *
 * This allocates a set of ballooned pages and maps them पूर्णांकo the
 * kernel's address space.
 */
पूर्णांक __init xen_xlate_map_ballooned_pages(xen_pfn_t **gfns, व्योम **virt,
					 अचिन्हित दीर्घ nr_grant_frames)
अणु
	काष्ठा page **pages;
	xen_pfn_t *pfns;
	व्योम *vaddr;
	काष्ठा map_balloon_pages data;
	पूर्णांक rc;
	अचिन्हित दीर्घ nr_pages;

	BUG_ON(nr_grant_frames == 0);
	nr_pages = DIV_ROUND_UP(nr_grant_frames, XEN_PFN_PER_PAGE);
	pages = kसुस्मृति(nr_pages, माप(pages[0]), GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;

	pfns = kसुस्मृति(nr_grant_frames, माप(pfns[0]), GFP_KERNEL);
	अगर (!pfns) अणु
		kमुक्त(pages);
		वापस -ENOMEM;
	पूर्ण
	rc = xen_alloc_unpopulated_pages(nr_pages, pages);
	अगर (rc) अणु
		pr_warn("%s Couldn't balloon alloc %ld pages rc:%d\n", __func__,
			nr_pages, rc);
		kमुक्त(pages);
		kमुक्त(pfns);
		वापस rc;
	पूर्ण

	data.pfns = pfns;
	data.idx = 0;
	xen_क्रम_each_gfn(pages, nr_grant_frames, setup_balloon_gfn, &data);

	vaddr = vmap(pages, nr_pages, 0, PAGE_KERNEL);
	अगर (!vaddr) अणु
		pr_warn("%s Couldn't map %ld pages rc:%d\n", __func__,
			nr_pages, rc);
		xen_मुक्त_unpopulated_pages(nr_pages, pages);
		kमुक्त(pages);
		kमुक्त(pfns);
		वापस -ENOMEM;
	पूर्ण
	kमुक्त(pages);

	*gfns = pfns;
	*virt = vaddr;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xen_xlate_map_ballooned_pages);

काष्ठा remap_pfn अणु
	काष्ठा mm_काष्ठा *mm;
	काष्ठा page **pages;
	pgprot_t prot;
	अचिन्हित दीर्घ i;
पूर्ण;

अटल पूर्णांक remap_pfn_fn(pte_t *ptep, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा remap_pfn *r = data;
	काष्ठा page *page = r->pages[r->i];
	pte_t pte = pte_mkspecial(pfn_pte(page_to_pfn(page), r->prot));

	set_pte_at(r->mm, addr, ptep, pte);
	r->i++;

	वापस 0;
पूर्ण

/* Used by the privcmd module, but has to be built-in on ARM */
पूर्णांक xen_remap_vma_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	काष्ठा remap_pfn r = अणु
		.mm = vma->vm_mm,
		.pages = vma->vm_निजी_data,
		.prot = vma->vm_page_prot,
	पूर्ण;

	वापस apply_to_page_range(vma->vm_mm, addr, len, remap_pfn_fn, &r);
पूर्ण
EXPORT_SYMBOL_GPL(xen_remap_vma_range);
