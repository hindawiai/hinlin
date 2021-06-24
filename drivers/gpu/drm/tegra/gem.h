<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Tegra host1x GEM implementation
 *
 * Copyright (c) 2012-2013, NVIDIA Corporation.
 */

#अगर_अघोषित __HOST1X_GEM_H
#घोषणा __HOST1X_GEM_H

#समावेश <linux/host1x.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_gem.h>

#घोषणा TEGRA_BO_BOTTOM_UP (1 << 0)

क्रमागत tegra_bo_tiling_mode अणु
	TEGRA_BO_TILING_MODE_PITCH,
	TEGRA_BO_TILING_MODE_TILED,
	TEGRA_BO_TILING_MODE_BLOCK,
पूर्ण;

क्रमागत tegra_bo_sector_layout अणु
	TEGRA_BO_SECTOR_LAYOUT_TEGRA,
	TEGRA_BO_SECTOR_LAYOUT_GPU,
पूर्ण;

काष्ठा tegra_bo_tiling अणु
	क्रमागत tegra_bo_tiling_mode mode;
	अचिन्हित दीर्घ value;
	क्रमागत tegra_bo_sector_layout sector_layout;
पूर्ण;

काष्ठा tegra_bo अणु
	काष्ठा drm_gem_object gem;
	काष्ठा host1x_bo base;
	अचिन्हित दीर्घ flags;
	काष्ठा sg_table *sgt;
	dma_addr_t iova;
	व्योम *vaddr;

	काष्ठा drm_mm_node *mm;
	अचिन्हित दीर्घ num_pages;
	काष्ठा page **pages;
	/* size of IOMMU mapping */
	माप_प्रकार size;

	काष्ठा tegra_bo_tiling tiling;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_bo *to_tegra_bo(काष्ठा drm_gem_object *gem)
अणु
	वापस container_of(gem, काष्ठा tegra_bo, gem);
पूर्ण

अटल अंतरभूत काष्ठा tegra_bo *host1x_to_tegra_bo(काष्ठा host1x_bo *bo)
अणु
	वापस container_of(bo, काष्ठा tegra_bo, base);
पूर्ण

काष्ठा tegra_bo *tegra_bo_create(काष्ठा drm_device *drm, माप_प्रकार size,
				 अचिन्हित दीर्घ flags);
काष्ठा tegra_bo *tegra_bo_create_with_handle(काष्ठा drm_file *file,
					     काष्ठा drm_device *drm,
					     माप_प्रकार size,
					     अचिन्हित दीर्घ flags,
					     u32 *handle);
व्योम tegra_bo_मुक्त_object(काष्ठा drm_gem_object *gem);
पूर्णांक tegra_bo_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *drm,
			 काष्ठा drm_mode_create_dumb *args);

बाह्य स्थिर काष्ठा vm_operations_काष्ठा tegra_bo_vm_ops;

पूर्णांक __tegra_gem_mmap(काष्ठा drm_gem_object *gem, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक tegra_drm_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);

काष्ठा dma_buf *tegra_gem_prime_export(काष्ठा drm_gem_object *gem,
				       पूर्णांक flags);
काष्ठा drm_gem_object *tegra_gem_prime_import(काष्ठा drm_device *drm,
					      काष्ठा dma_buf *buf);

#पूर्ण_अगर
