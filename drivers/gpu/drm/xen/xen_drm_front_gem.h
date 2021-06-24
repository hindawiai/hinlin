<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#अगर_अघोषित __XEN_DRM_FRONT_GEM_H
#घोषणा __XEN_DRM_FRONT_GEM_H

काष्ठा dma_buf_attachment;
काष्ठा dma_buf_map;
काष्ठा drm_device;
काष्ठा drm_gem_object;
काष्ठा file;
काष्ठा sg_table;
काष्ठा vm_area_काष्ठा;

काष्ठा drm_gem_object *xen_drm_front_gem_create(काष्ठा drm_device *dev,
						माप_प्रकार size);

काष्ठा drm_gem_object *
xen_drm_front_gem_import_sg_table(काष्ठा drm_device *dev,
				  काष्ठा dma_buf_attachment *attach,
				  काष्ठा sg_table *sgt);

काष्ठा sg_table *xen_drm_front_gem_get_sg_table(काष्ठा drm_gem_object *gem_obj);

काष्ठा page **xen_drm_front_gem_get_pages(काष्ठा drm_gem_object *obj);

व्योम xen_drm_front_gem_मुक्त_object_unlocked(काष्ठा drm_gem_object *gem_obj);

पूर्णांक xen_drm_front_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);

पूर्णांक xen_drm_front_gem_prime_vmap(काष्ठा drm_gem_object *gem_obj,
				 काष्ठा dma_buf_map *map);

व्योम xen_drm_front_gem_prime_vunmap(काष्ठा drm_gem_object *gem_obj,
				    काष्ठा dma_buf_map *map);

पूर्णांक xen_drm_front_gem_prime_mmap(काष्ठा drm_gem_object *gem_obj,
				 काष्ठा vm_area_काष्ठा *vma);

#पूर्ण_अगर /* __XEN_DRM_FRONT_GEM_H */
