<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 */

#अगर_अघोषित _ROCKCHIP_DRM_GEM_H
#घोषणा _ROCKCHIP_DRM_GEM_H

#घोषणा to_rockchip_obj(x) container_of(x, काष्ठा rockchip_gem_object, base)

काष्ठा rockchip_gem_object अणु
	काष्ठा drm_gem_object base;
	अचिन्हित पूर्णांक flags;

	व्योम *kvaddr;
	dma_addr_t dma_addr;
	/* Used when IOMMU is disabled */
	अचिन्हित दीर्घ dma_attrs;

	/* Used when IOMMU is enabled */
	काष्ठा drm_mm_node mm;
	अचिन्हित दीर्घ num_pages;
	काष्ठा page **pages;
	काष्ठा sg_table *sgt;
	माप_प्रकार size;
पूर्ण;

काष्ठा sg_table *rockchip_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj);
काष्ठा drm_gem_object *
rockchip_gem_prime_import_sg_table(काष्ठा drm_device *dev,
				   काष्ठा dma_buf_attachment *attach,
				   काष्ठा sg_table *sg);
पूर्णांक rockchip_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);
व्योम rockchip_gem_prime_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);

/* drm driver mmap file operations */
पूर्णांक rockchip_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);

/* mmap a gem object to userspace. */
पूर्णांक rockchip_gem_mmap_buf(काष्ठा drm_gem_object *obj,
			  काष्ठा vm_area_काष्ठा *vma);

काष्ठा rockchip_gem_object *
	rockchip_gem_create_object(काष्ठा drm_device *drm, अचिन्हित पूर्णांक size,
				   bool alloc_kmap);

व्योम rockchip_gem_मुक्त_object(काष्ठा drm_gem_object *obj);

पूर्णांक rockchip_gem_dumb_create(काष्ठा drm_file *file_priv,
			     काष्ठा drm_device *dev,
			     काष्ठा drm_mode_create_dumb *args);
#पूर्ण_अगर /* _ROCKCHIP_DRM_GEM_H */
