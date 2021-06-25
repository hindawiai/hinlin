<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/radeon_drm.h>
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/set_memory.h>
#पूर्ण_अगर
#समावेश "radeon.h"

/*
 * GART
 * The GART (Graphics Aperture Remapping Table) is an aperture
 * in the GPU's address space.  System pages can be mapped पूर्णांकo
 * the aperture and look like contiguous pages from the GPU's
 * perspective.  A page table maps the pages in the aperture
 * to the actual backing pages in प्रणाली memory.
 *
 * Radeon GPUs support both an पूर्णांकernal GART, as described above,
 * and AGP.  AGP works similarly, but the GART table is configured
 * and मुख्यtained by the northbridge rather than the driver.
 * Radeon hw has a separate AGP aperture that is programmed to
 * poपूर्णांक to the AGP aperture provided by the northbridge and the
 * requests are passed through to the northbridge aperture.
 * Both AGP and पूर्णांकernal GART can be used at the same समय, however
 * that is not currently supported by the driver.
 *
 * This file handles the common पूर्णांकernal GART management.
 */

/*
 * Common GART table functions.
 */
/**
 * radeon_gart_table_ram_alloc - allocate प्रणाली ram क्रम gart page table
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Allocate प्रणाली memory क्रम GART page table
 * (r1xx-r3xx, non-pcie r4xx, rs400).  These asics require the
 * gart table to be in प्रणाली memory.
 * Returns 0 क्रम success, -ENOMEM क्रम failure.
 */
पूर्णांक radeon_gart_table_ram_alloc(काष्ठा radeon_device *rdev)
अणु
	व्योम *ptr;

	ptr = dma_alloc_coherent(&rdev->pdev->dev, rdev->gart.table_size,
				 &rdev->gart.table_addr, GFP_KERNEL);
	अगर (ptr == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण
#अगर_घोषित CONFIG_X86
	अगर (rdev->family == CHIP_RS400 || rdev->family == CHIP_RS480 ||
	    rdev->family == CHIP_RS690 || rdev->family == CHIP_RS740) अणु
		set_memory_uc((अचिन्हित दीर्घ)ptr,
			      rdev->gart.table_size >> PAGE_SHIFT);
	पूर्ण
#पूर्ण_अगर
	rdev->gart.ptr = ptr;
	वापस 0;
पूर्ण

/**
 * radeon_gart_table_ram_मुक्त - मुक्त प्रणाली ram क्रम gart page table
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Free प्रणाली memory क्रम GART page table
 * (r1xx-r3xx, non-pcie r4xx, rs400).  These asics require the
 * gart table to be in प्रणाली memory.
 */
व्योम radeon_gart_table_ram_मुक्त(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->gart.ptr == शून्य) अणु
		वापस;
	पूर्ण
#अगर_घोषित CONFIG_X86
	अगर (rdev->family == CHIP_RS400 || rdev->family == CHIP_RS480 ||
	    rdev->family == CHIP_RS690 || rdev->family == CHIP_RS740) अणु
		set_memory_wb((अचिन्हित दीर्घ)rdev->gart.ptr,
			      rdev->gart.table_size >> PAGE_SHIFT);
	पूर्ण
#पूर्ण_अगर
	dma_मुक्त_coherent(&rdev->pdev->dev, rdev->gart.table_size,
			  (व्योम *)rdev->gart.ptr, rdev->gart.table_addr);
	rdev->gart.ptr = शून्य;
	rdev->gart.table_addr = 0;
पूर्ण

/**
 * radeon_gart_table_vram_alloc - allocate vram क्रम gart page table
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Allocate video memory क्रम GART page table
 * (pcie r4xx, r5xx+).  These asics require the
 * gart table to be in video memory.
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक radeon_gart_table_vram_alloc(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->gart.robj == शून्य) अणु
		r = radeon_bo_create(rdev, rdev->gart.table_size,
				     PAGE_SIZE, true, RADEON_GEM_DOMAIN_VRAM,
				     0, शून्य, शून्य, &rdev->gart.robj);
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * radeon_gart_table_vram_pin - pin gart page table in vram
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Pin the GART page table in vram so it will not be moved
 * by the memory manager (pcie r4xx, r5xx+).  These asics require the
 * gart table to be in video memory.
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक radeon_gart_table_vram_pin(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक64_t gpu_addr;
	पूर्णांक r;

	r = radeon_bo_reserve(rdev->gart.robj, false);
	अगर (unlikely(r != 0))
		वापस r;
	r = radeon_bo_pin(rdev->gart.robj,
				RADEON_GEM_DOMAIN_VRAM, &gpu_addr);
	अगर (r) अणु
		radeon_bo_unreserve(rdev->gart.robj);
		वापस r;
	पूर्ण
	r = radeon_bo_kmap(rdev->gart.robj, &rdev->gart.ptr);
	अगर (r)
		radeon_bo_unpin(rdev->gart.robj);
	radeon_bo_unreserve(rdev->gart.robj);
	rdev->gart.table_addr = gpu_addr;

	अगर (!r) अणु
		पूर्णांक i;

		/* We might have dropped some GART table updates जबतक it wasn't
		 * mapped, restore all entries
		 */
		क्रम (i = 0; i < rdev->gart.num_gpu_pages; i++)
			radeon_gart_set_page(rdev, i, rdev->gart.pages_entry[i]);
		mb();
		radeon_gart_tlb_flush(rdev);
	पूर्ण

	वापस r;
पूर्ण

/**
 * radeon_gart_table_vram_unpin - unpin gart page table in vram
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Unpin the GART page table in vram (pcie r4xx, r5xx+).
 * These asics require the gart table to be in video memory.
 */
व्योम radeon_gart_table_vram_unpin(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (rdev->gart.robj == शून्य) अणु
		वापस;
	पूर्ण
	r = radeon_bo_reserve(rdev->gart.robj, false);
	अगर (likely(r == 0)) अणु
		radeon_bo_kunmap(rdev->gart.robj);
		radeon_bo_unpin(rdev->gart.robj);
		radeon_bo_unreserve(rdev->gart.robj);
		rdev->gart.ptr = शून्य;
	पूर्ण
पूर्ण

/**
 * radeon_gart_table_vram_मुक्त - मुक्त gart page table vram
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Free the video memory used क्रम the GART page table
 * (pcie r4xx, r5xx+).  These asics require the gart table to
 * be in video memory.
 */
व्योम radeon_gart_table_vram_मुक्त(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->gart.robj == शून्य) अणु
		वापस;
	पूर्ण
	radeon_bo_unref(&rdev->gart.robj);
पूर्ण

/*
 * Common gart functions.
 */
/**
 * radeon_gart_unbind - unbind pages from the gart page table
 *
 * @rdev: radeon_device poपूर्णांकer
 * @offset: offset पूर्णांकo the GPU's gart aperture
 * @pages: number of pages to unbind
 *
 * Unbinds the requested pages from the gart page table and
 * replaces them with the dummy page (all asics).
 */
व्योम radeon_gart_unbind(काष्ठा radeon_device *rdev, अचिन्हित offset,
			पूर्णांक pages)
अणु
	अचिन्हित t;
	अचिन्हित p;
	पूर्णांक i, j;

	अगर (!rdev->gart.पढ़ोy) अणु
		WARN(1, "trying to unbind memory from uninitialized GART !\n");
		वापस;
	पूर्ण
	t = offset / RADEON_GPU_PAGE_SIZE;
	p = t / (PAGE_SIZE / RADEON_GPU_PAGE_SIZE);
	क्रम (i = 0; i < pages; i++, p++) अणु
		अगर (rdev->gart.pages[p]) अणु
			rdev->gart.pages[p] = शून्य;
			क्रम (j = 0; j < (PAGE_SIZE / RADEON_GPU_PAGE_SIZE); j++, t++) अणु
				rdev->gart.pages_entry[t] = rdev->dummy_page.entry;
				अगर (rdev->gart.ptr) अणु
					radeon_gart_set_page(rdev, t,
							     rdev->dummy_page.entry);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (rdev->gart.ptr) अणु
		mb();
		radeon_gart_tlb_flush(rdev);
	पूर्ण
पूर्ण

/**
 * radeon_gart_bind - bind pages पूर्णांकo the gart page table
 *
 * @rdev: radeon_device poपूर्णांकer
 * @offset: offset पूर्णांकo the GPU's gart aperture
 * @pages: number of pages to bind
 * @pagelist: pages to bind
 * @dma_addr: DMA addresses of pages
 * @flags: RADEON_GART_PAGE_* flags
 *
 * Binds the requested pages to the gart page table
 * (all asics).
 * Returns 0 क्रम success, -EINVAL क्रम failure.
 */
पूर्णांक radeon_gart_bind(काष्ठा radeon_device *rdev, अचिन्हित offset,
		     पूर्णांक pages, काष्ठा page **pagelist, dma_addr_t *dma_addr,
		     uपूर्णांक32_t flags)
अणु
	अचिन्हित t;
	अचिन्हित p;
	uपूर्णांक64_t page_base, page_entry;
	पूर्णांक i, j;

	अगर (!rdev->gart.पढ़ोy) अणु
		WARN(1, "trying to bind memory to uninitialized GART !\n");
		वापस -EINVAL;
	पूर्ण
	t = offset / RADEON_GPU_PAGE_SIZE;
	p = t / (PAGE_SIZE / RADEON_GPU_PAGE_SIZE);

	क्रम (i = 0; i < pages; i++, p++) अणु
		rdev->gart.pages[p] = pagelist ? pagelist[i] :
			rdev->dummy_page.page;
		page_base = dma_addr[i];
		क्रम (j = 0; j < (PAGE_SIZE / RADEON_GPU_PAGE_SIZE); j++, t++) अणु
			page_entry = radeon_gart_get_page_entry(page_base, flags);
			rdev->gart.pages_entry[t] = page_entry;
			अगर (rdev->gart.ptr) अणु
				radeon_gart_set_page(rdev, t, page_entry);
			पूर्ण
			page_base += RADEON_GPU_PAGE_SIZE;
		पूर्ण
	पूर्ण
	अगर (rdev->gart.ptr) अणु
		mb();
		radeon_gart_tlb_flush(rdev);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * radeon_gart_init - init the driver info क्रम managing the gart
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Allocate the dummy page and init the gart driver info (all asics).
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक radeon_gart_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r, i;

	अगर (rdev->gart.pages) अणु
		वापस 0;
	पूर्ण
	/* We need PAGE_SIZE >= RADEON_GPU_PAGE_SIZE */
	अगर (PAGE_SIZE < RADEON_GPU_PAGE_SIZE) अणु
		DRM_ERROR("Page size is smaller than GPU page size!\n");
		वापस -EINVAL;
	पूर्ण
	r = radeon_dummy_page_init(rdev);
	अगर (r)
		वापस r;
	/* Compute table size */
	rdev->gart.num_cpu_pages = rdev->mc.gtt_size / PAGE_SIZE;
	rdev->gart.num_gpu_pages = rdev->mc.gtt_size / RADEON_GPU_PAGE_SIZE;
	DRM_INFO("GART: num cpu pages %u, num gpu pages %u\n",
		 rdev->gart.num_cpu_pages, rdev->gart.num_gpu_pages);
	/* Allocate pages table */
	rdev->gart.pages = vzalloc(array_size(माप(व्योम *),
				   rdev->gart.num_cpu_pages));
	अगर (rdev->gart.pages == शून्य) अणु
		radeon_gart_fini(rdev);
		वापस -ENOMEM;
	पूर्ण
	rdev->gart.pages_entry = vदो_स्मृति(array_size(माप(uपूर्णांक64_t),
						    rdev->gart.num_gpu_pages));
	अगर (rdev->gart.pages_entry == शून्य) अणु
		radeon_gart_fini(rdev);
		वापस -ENOMEM;
	पूर्ण
	/* set GART entry to poपूर्णांक to the dummy page by शेष */
	क्रम (i = 0; i < rdev->gart.num_gpu_pages; i++)
		rdev->gart.pages_entry[i] = rdev->dummy_page.entry;
	वापस 0;
पूर्ण

/**
 * radeon_gart_fini - tear करोwn the driver info क्रम managing the gart
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Tear करोwn the gart driver info and मुक्त the dummy page (all asics).
 */
व्योम radeon_gart_fini(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->gart.पढ़ोy) अणु
		/* unbind pages */
		radeon_gart_unbind(rdev, 0, rdev->gart.num_cpu_pages);
	पूर्ण
	rdev->gart.पढ़ोy = false;
	vमुक्त(rdev->gart.pages);
	vमुक्त(rdev->gart.pages_entry);
	rdev->gart.pages = शून्य;
	rdev->gart.pages_entry = शून्य;

	radeon_dummy_page_fini(rdev);
पूर्ण
