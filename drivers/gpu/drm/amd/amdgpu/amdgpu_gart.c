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

#समावेश <drm/amdgpu_drm.h>
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/set_memory.h>
#पूर्ण_अगर
#समावेश "amdgpu.h"

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
 * amdgpu_dummy_page_init - init dummy page used by the driver
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate the dummy page used by the driver (all asics).
 * This dummy page is used by the driver as a filler क्रम gart entries
 * when pages are taken out of the GART
 * Returns 0 on sucess, -ENOMEM on failure.
 */
अटल पूर्णांक amdgpu_gart_dummy_page_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा page *dummy_page = tपंचांग_glob.dummy_पढ़ो_page;

	अगर (adev->dummy_page_addr)
		वापस 0;
	adev->dummy_page_addr = dma_map_page(&adev->pdev->dev, dummy_page, 0,
					     PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(&adev->pdev->dev, adev->dummy_page_addr)) अणु
		dev_err(&adev->pdev->dev, "Failed to DMA MAP the dummy page\n");
		adev->dummy_page_addr = 0;
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_dummy_page_fini - मुक्त dummy page used by the driver
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Frees the dummy page used by the driver (all asics).
 */
अटल व्योम amdgpu_gart_dummy_page_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (!adev->dummy_page_addr)
		वापस;
	pci_unmap_page(adev->pdev, adev->dummy_page_addr,
		       PAGE_SIZE, PCI_DMA_BIसूचीECTIONAL);
	adev->dummy_page_addr = 0;
पूर्ण

/**
 * amdgpu_gart_table_vram_alloc - allocate vram क्रम gart page table
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate video memory क्रम GART page table
 * (pcie r4xx, r5xx+).  These asics require the
 * gart table to be in video memory.
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक amdgpu_gart_table_vram_alloc(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->gart.bo == शून्य) अणु
		काष्ठा amdgpu_bo_param bp;

		स_रखो(&bp, 0, माप(bp));
		bp.size = adev->gart.table_size;
		bp.byte_align = PAGE_SIZE;
		bp.करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;
		bp.flags = AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED |
			AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
		bp.type = tपंचांग_bo_type_kernel;
		bp.resv = शून्य;
		bp.bo_ptr_size = माप(काष्ठा amdgpu_bo);

		r = amdgpu_bo_create(adev, &bp, &adev->gart.bo);
		अगर (r) अणु
			वापस r;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_gart_table_vram_pin - pin gart page table in vram
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Pin the GART page table in vram so it will not be moved
 * by the memory manager (pcie r4xx, r5xx+).  These asics require the
 * gart table to be in video memory.
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक amdgpu_gart_table_vram_pin(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	r = amdgpu_bo_reserve(adev->gart.bo, false);
	अगर (unlikely(r != 0))
		वापस r;
	r = amdgpu_bo_pin(adev->gart.bo, AMDGPU_GEM_DOMAIN_VRAM);
	अगर (r) अणु
		amdgpu_bo_unreserve(adev->gart.bo);
		वापस r;
	पूर्ण
	r = amdgpu_bo_kmap(adev->gart.bo, &adev->gart.ptr);
	अगर (r)
		amdgpu_bo_unpin(adev->gart.bo);
	amdgpu_bo_unreserve(adev->gart.bo);
	वापस r;
पूर्ण

/**
 * amdgpu_gart_table_vram_unpin - unpin gart page table in vram
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Unpin the GART page table in vram (pcie r4xx, r5xx+).
 * These asics require the gart table to be in video memory.
 */
व्योम amdgpu_gart_table_vram_unpin(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->gart.bo == शून्य) अणु
		वापस;
	पूर्ण
	r = amdgpu_bo_reserve(adev->gart.bo, true);
	अगर (likely(r == 0)) अणु
		amdgpu_bo_kunmap(adev->gart.bo);
		amdgpu_bo_unpin(adev->gart.bo);
		amdgpu_bo_unreserve(adev->gart.bo);
		adev->gart.ptr = शून्य;
	पूर्ण
पूर्ण

/**
 * amdgpu_gart_table_vram_मुक्त - मुक्त gart page table vram
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Free the video memory used क्रम the GART page table
 * (pcie r4xx, r5xx+).  These asics require the gart table to
 * be in video memory.
 */
व्योम amdgpu_gart_table_vram_मुक्त(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->gart.bo == शून्य) अणु
		वापस;
	पूर्ण
	amdgpu_bo_unref(&adev->gart.bo);
	adev->gart.ptr = शून्य;
पूर्ण

/*
 * Common gart functions.
 */
/**
 * amdgpu_gart_unbind - unbind pages from the gart page table
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @offset: offset पूर्णांकo the GPU's gart aperture
 * @pages: number of pages to unbind
 *
 * Unbinds the requested pages from the gart page table and
 * replaces them with the dummy page (all asics).
 * Returns 0 क्रम success, -EINVAL क्रम failure.
 */
पूर्णांक amdgpu_gart_unbind(काष्ठा amdgpu_device *adev, uपूर्णांक64_t offset,
			पूर्णांक pages)
अणु
	अचिन्हित t;
	अचिन्हित p;
	पूर्णांक i, j;
	u64 page_base;
	/* Starting from VEGA10, प्रणाली bit must be 0 to mean invalid. */
	uपूर्णांक64_t flags = 0;

	अगर (!adev->gart.पढ़ोy) अणु
		WARN(1, "trying to unbind memory from uninitialized GART !\n");
		वापस -EINVAL;
	पूर्ण

	t = offset / AMDGPU_GPU_PAGE_SIZE;
	p = t / AMDGPU_GPU_PAGES_IN_CPU_PAGE;
	क्रम (i = 0; i < pages; i++, p++) अणु
		page_base = adev->dummy_page_addr;
		अगर (!adev->gart.ptr)
			जारी;

		क्रम (j = 0; j < AMDGPU_GPU_PAGES_IN_CPU_PAGE; j++, t++) अणु
			amdgpu_gmc_set_pte_pde(adev, adev->gart.ptr,
					       t, page_base, flags);
			page_base += AMDGPU_GPU_PAGE_SIZE;
		पूर्ण
	पूर्ण
	mb();
	amdgpu_asic_flush_hdp(adev, शून्य);
	क्रम (i = 0; i < adev->num_vmhubs; i++)
		amdgpu_gmc_flush_gpu_tlb(adev, 0, i, 0);

	वापस 0;
पूर्ण

/**
 * amdgpu_gart_map - map dma_addresses पूर्णांकo GART entries
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @offset: offset पूर्णांकo the GPU's gart aperture
 * @pages: number of pages to bind
 * @dma_addr: DMA addresses of pages
 * @flags: page table entry flags
 * @dst: CPU address of the gart table
 *
 * Map the dma_addresses पूर्णांकo GART entries (all asics).
 * Returns 0 क्रम success, -EINVAL क्रम failure.
 */
पूर्णांक amdgpu_gart_map(काष्ठा amdgpu_device *adev, uपूर्णांक64_t offset,
		    पूर्णांक pages, dma_addr_t *dma_addr, uपूर्णांक64_t flags,
		    व्योम *dst)
अणु
	uपूर्णांक64_t page_base;
	अचिन्हित i, j, t;

	अगर (!adev->gart.पढ़ोy) अणु
		WARN(1, "trying to bind memory to uninitialized GART !\n");
		वापस -EINVAL;
	पूर्ण

	t = offset / AMDGPU_GPU_PAGE_SIZE;

	क्रम (i = 0; i < pages; i++) अणु
		page_base = dma_addr[i];
		क्रम (j = 0; j < AMDGPU_GPU_PAGES_IN_CPU_PAGE; j++, t++) अणु
			amdgpu_gmc_set_pte_pde(adev, dst, t, page_base, flags);
			page_base += AMDGPU_GPU_PAGE_SIZE;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_gart_bind - bind pages पूर्णांकo the gart page table
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @offset: offset पूर्णांकo the GPU's gart aperture
 * @pages: number of pages to bind
 * @pagelist: pages to bind
 * @dma_addr: DMA addresses of pages
 * @flags: page table entry flags
 *
 * Binds the requested pages to the gart page table
 * (all asics).
 * Returns 0 क्रम success, -EINVAL क्रम failure.
 */
पूर्णांक amdgpu_gart_bind(काष्ठा amdgpu_device *adev, uपूर्णांक64_t offset,
		     पूर्णांक pages, काष्ठा page **pagelist, dma_addr_t *dma_addr,
		     uपूर्णांक64_t flags)
अणु
	पूर्णांक r, i;

	अगर (!adev->gart.पढ़ोy) अणु
		WARN(1, "trying to bind memory to uninitialized GART !\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!adev->gart.ptr)
		वापस 0;

	r = amdgpu_gart_map(adev, offset, pages, dma_addr, flags,
		    adev->gart.ptr);
	अगर (r)
		वापस r;

	mb();
	amdgpu_asic_flush_hdp(adev, शून्य);
	क्रम (i = 0; i < adev->num_vmhubs; i++)
		amdgpu_gmc_flush_gpu_tlb(adev, 0, i, 0);
	वापस 0;
पूर्ण

/**
 * amdgpu_gart_init - init the driver info क्रम managing the gart
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate the dummy page and init the gart driver info (all asics).
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक amdgpu_gart_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r;

	अगर (adev->dummy_page_addr)
		वापस 0;

	/* We need PAGE_SIZE >= AMDGPU_GPU_PAGE_SIZE */
	अगर (PAGE_SIZE < AMDGPU_GPU_PAGE_SIZE) अणु
		DRM_ERROR("Page size is smaller than GPU page size!\n");
		वापस -EINVAL;
	पूर्ण
	r = amdgpu_gart_dummy_page_init(adev);
	अगर (r)
		वापस r;
	/* Compute table size */
	adev->gart.num_cpu_pages = adev->gmc.gart_size / PAGE_SIZE;
	adev->gart.num_gpu_pages = adev->gmc.gart_size / AMDGPU_GPU_PAGE_SIZE;
	DRM_INFO("GART: num cpu pages %u, num gpu pages %u\n",
		 adev->gart.num_cpu_pages, adev->gart.num_gpu_pages);

	वापस 0;
पूर्ण

/**
 * amdgpu_gart_fini - tear करोwn the driver info क्रम managing the gart
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Tear करोwn the gart driver info and मुक्त the dummy page (all asics).
 */
व्योम amdgpu_gart_fini(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_gart_dummy_page_fini(adev);
पूर्ण
