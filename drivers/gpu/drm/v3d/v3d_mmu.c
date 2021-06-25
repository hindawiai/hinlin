<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2017-2018 Broadcom */

/**
 * DOC: Broadcom V3D MMU
 *
 * The V3D 3.x hardware (compared to VC4) now includes an MMU.  It has
 * a single level of page tables क्रम the V3D's 4GB address space to
 * map to AXI bus addresses, thus it could need up to 4MB of
 * physically contiguous memory to store the PTEs.
 *
 * Because the 4MB of contiguous memory क्रम page tables is precious,
 * and चयनing between them is expensive, we load all BOs पूर्णांकo the
 * same 4GB address space.
 *
 * To protect clients from each other, we should use the GMP to
 * quickly mask out (at 128kb granularity) what pages are available to
 * each client.  This is not yet implemented.
 */

#समावेश "v3d_drv.h"
#समावेश "v3d_regs.h"

#घोषणा V3D_MMU_PAGE_SHIFT 12

/* Note: All PTEs क्रम the 1MB superpage must be filled with the
 * superpage bit set.
 */
#घोषणा V3D_PTE_SUPERPAGE BIT(31)
#घोषणा V3D_PTE_WRITEABLE BIT(29)
#घोषणा V3D_PTE_VALID BIT(28)

अटल पूर्णांक v3d_mmu_flush_all(काष्ठा v3d_dev *v3d)
अणु
	पूर्णांक ret;

	/* Make sure that another flush isn't alपढ़ोy running when we
	 * start this one.
	 */
	ret = रुको_क्रम(!(V3D_READ(V3D_MMU_CTL) &
			 V3D_MMU_CTL_TLB_CLEARING), 100);
	अगर (ret)
		dev_err(v3d->drm.dev, "TLB clear wait idle pre-wait failed\n");

	V3D_WRITE(V3D_MMU_CTL, V3D_READ(V3D_MMU_CTL) |
		  V3D_MMU_CTL_TLB_CLEAR);

	V3D_WRITE(V3D_MMUC_CONTROL,
		  V3D_MMUC_CONTROL_FLUSH |
		  V3D_MMUC_CONTROL_ENABLE);

	ret = रुको_क्रम(!(V3D_READ(V3D_MMU_CTL) &
			 V3D_MMU_CTL_TLB_CLEARING), 100);
	अगर (ret) अणु
		dev_err(v3d->drm.dev, "TLB clear wait idle failed\n");
		वापस ret;
	पूर्ण

	ret = रुको_क्रम(!(V3D_READ(V3D_MMUC_CONTROL) &
			 V3D_MMUC_CONTROL_FLUSHING), 100);
	अगर (ret)
		dev_err(v3d->drm.dev, "MMUC flush wait idle failed\n");

	वापस ret;
पूर्ण

पूर्णांक v3d_mmu_set_page_table(काष्ठा v3d_dev *v3d)
अणु
	V3D_WRITE(V3D_MMU_PT_PA_BASE, v3d->pt_paddr >> V3D_MMU_PAGE_SHIFT);
	V3D_WRITE(V3D_MMU_CTL,
		  V3D_MMU_CTL_ENABLE |
		  V3D_MMU_CTL_PT_INVALID_ENABLE |
		  V3D_MMU_CTL_PT_INVALID_ABORT |
		  V3D_MMU_CTL_PT_INVALID_INT |
		  V3D_MMU_CTL_WRITE_VIOLATION_ABORT |
		  V3D_MMU_CTL_WRITE_VIOLATION_INT |
		  V3D_MMU_CTL_CAP_EXCEEDED_ABORT |
		  V3D_MMU_CTL_CAP_EXCEEDED_INT);
	V3D_WRITE(V3D_MMU_ILLEGAL_ADDR,
		  (v3d->mmu_scratch_paddr >> V3D_MMU_PAGE_SHIFT) |
		  V3D_MMU_ILLEGAL_ADDR_ENABLE);
	V3D_WRITE(V3D_MMUC_CONTROL, V3D_MMUC_CONTROL_ENABLE);

	वापस v3d_mmu_flush_all(v3d);
पूर्ण

व्योम v3d_mmu_insert_ptes(काष्ठा v3d_bo *bo)
अणु
	काष्ठा drm_gem_shmem_object *shmem_obj = &bo->base;
	काष्ठा v3d_dev *v3d = to_v3d_dev(shmem_obj->base.dev);
	u32 page = bo->node.start;
	u32 page_prot = V3D_PTE_WRITEABLE | V3D_PTE_VALID;
	काष्ठा sg_dma_page_iter dma_iter;

	क्रम_each_sgtable_dma_page(shmem_obj->sgt, &dma_iter, 0) अणु
		dma_addr_t dma_addr = sg_page_iter_dma_address(&dma_iter);
		u32 page_address = dma_addr >> V3D_MMU_PAGE_SHIFT;
		u32 pte = page_prot | page_address;
		u32 i;

		BUG_ON(page_address + (PAGE_SIZE >> V3D_MMU_PAGE_SHIFT) >=
		       BIT(24));
		क्रम (i = 0; i < PAGE_SIZE >> V3D_MMU_PAGE_SHIFT; i++)
			v3d->pt[page++] = pte + i;
	पूर्ण

	WARN_ON_ONCE(page - bo->node.start !=
		     shmem_obj->base.size >> V3D_MMU_PAGE_SHIFT);

	अगर (v3d_mmu_flush_all(v3d))
		dev_err(v3d->drm.dev, "MMU flush timeout\n");
पूर्ण

व्योम v3d_mmu_हटाओ_ptes(काष्ठा v3d_bo *bo)
अणु
	काष्ठा v3d_dev *v3d = to_v3d_dev(bo->base.base.dev);
	u32 npages = bo->base.base.size >> V3D_MMU_PAGE_SHIFT;
	u32 page;

	क्रम (page = bo->node.start; page < bo->node.start + npages; page++)
		v3d->pt[page] = 0;

	अगर (v3d_mmu_flush_all(v3d))
		dev_err(v3d->drm.dev, "MMU flush timeout\n");
पूर्ण
