<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 */

#समावेश <linux/mm.h>
#समावेश <linux/io-mapping.h>


#समावेश "i915_drv.h"

काष्ठा remap_pfn अणु
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ pfn;
	pgprot_t prot;

	काष्ठा sgt_iter sgt;
	resource_माप_प्रकार iobase;
पूर्ण;

अटल पूर्णांक remap_pfn(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा remap_pfn *r = data;

	/* Special PTE are not associated with any काष्ठा page */
	set_pte_at(r->mm, addr, pte, pte_mkspecial(pfn_pte(r->pfn, r->prot)));
	r->pfn++;

	वापस 0;
पूर्ण

#घोषणा use_dma(io) ((io) != -1)

अटल अंतरभूत अचिन्हित दीर्घ sgt_pfn(स्थिर काष्ठा remap_pfn *r)
अणु
	अगर (use_dma(r->iobase))
		वापस (r->sgt.dma + r->sgt.curr + r->iobase) >> PAGE_SHIFT;
	अन्यथा
		वापस r->sgt.pfn + (r->sgt.curr >> PAGE_SHIFT);
पूर्ण

अटल पूर्णांक remap_sg(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा remap_pfn *r = data;

	अगर (GEM_WARN_ON(!r->sgt.sgp))
		वापस -EINVAL;

	/* Special PTE are not associated with any काष्ठा page */
	set_pte_at(r->mm, addr, pte,
		   pte_mkspecial(pfn_pte(sgt_pfn(r), r->prot)));
	r->pfn++; /* track insertions in हाल we need to unwind later */

	r->sgt.curr += PAGE_SIZE;
	अगर (r->sgt.curr >= r->sgt.max)
		r->sgt = __sgt_iter(__sg_next(r->sgt.sgp), use_dma(r->iobase));

	वापस 0;
पूर्ण

/**
 * remap_io_mapping - remap an IO mapping to userspace
 * @vma: user vma to map to
 * @addr: target user address to start at
 * @pfn: physical address of kernel memory
 * @size: size of map area
 * @iomap: the source io_mapping
 *
 *  Note: this is only safe अगर the mm semaphore is held when called.
 */
पूर्णांक remap_io_mapping(काष्ठा vm_area_काष्ठा *vma,
		     अचिन्हित दीर्घ addr, अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ size,
		     काष्ठा io_mapping *iomap)
अणु
	काष्ठा remap_pfn r;
	पूर्णांक err;

#घोषणा EXPECTED_FLAGS (VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP)
	GEM_BUG_ON((vma->vm_flags & EXPECTED_FLAGS) != EXPECTED_FLAGS);

	/* We rely on prevalidation of the io-mapping to skip track_pfn(). */
	r.mm = vma->vm_mm;
	r.pfn = pfn;
	r.prot = __pgprot((pgprot_val(iomap->prot) & _PAGE_CACHE_MASK) |
			  (pgprot_val(vma->vm_page_prot) & ~_PAGE_CACHE_MASK));

	err = apply_to_page_range(r.mm, addr, size, remap_pfn, &r);
	अगर (unlikely(err)) अणु
		zap_vma_ptes(vma, addr, (r.pfn - pfn) << PAGE_SHIFT);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * remap_io_sg - remap an IO mapping to userspace
 * @vma: user vma to map to
 * @addr: target user address to start at
 * @size: size of map area
 * @sgl: Start sg entry
 * @iobase: Use stored dma address offset by this address or pfn अगर -1
 *
 *  Note: this is only safe अगर the mm semaphore is held when called.
 */
पूर्णांक remap_io_sg(काष्ठा vm_area_काष्ठा *vma,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size,
		काष्ठा scatterlist *sgl, resource_माप_प्रकार iobase)
अणु
	काष्ठा remap_pfn r = अणु
		.mm = vma->vm_mm,
		.prot = vma->vm_page_prot,
		.sgt = __sgt_iter(sgl, use_dma(iobase)),
		.iobase = iobase,
	पूर्ण;
	पूर्णांक err;

	/* We rely on prevalidation of the io-mapping to skip track_pfn(). */
	GEM_BUG_ON((vma->vm_flags & EXPECTED_FLAGS) != EXPECTED_FLAGS);

	अगर (!use_dma(iobase))
		flush_cache_range(vma, addr, size);

	err = apply_to_page_range(r.mm, addr, size, remap_sg, &r);
	अगर (unlikely(err)) अणु
		zap_vma_ptes(vma, addr, r.pfn << PAGE_SHIFT);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण
