<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * omap_gem.h -- OMAP DRM GEM Object Management
 *
 * Copyright (C) 2011 Texas Instruments
 * Author: Rob Clark <rob@ti.com>
 */

#अगर_अघोषित __OMAPDRM_GEM_H__
#घोषणा __OMAPDRM_GEM_H__

#समावेश <linux/types.h>
#समावेश <linux/mm_types.h>

क्रमागत dma_data_direction;

काष्ठा dma_buf;
काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_gem_object;
काष्ठा drm_mode_create_dumb;
काष्ठा file;
काष्ठा list_head;
काष्ठा page;
काष्ठा seq_file;
काष्ठा vm_area_काष्ठा;
काष्ठा vm_fault;

जोड़ omap_gem_size;

/* Initialization and Cleanup */
व्योम omap_gem_init(काष्ठा drm_device *dev);
व्योम omap_gem_deinit(काष्ठा drm_device *dev);

#अगर_घोषित CONFIG_PM
पूर्णांक omap_gem_resume(काष्ठा drm_device *dev);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_FS
व्योम omap_gem_describe(काष्ठा drm_gem_object *obj, काष्ठा seq_file *m);
व्योम omap_gem_describe_objects(काष्ठा list_head *list, काष्ठा seq_file *m);
#पूर्ण_अगर

/* GEM Object Creation and Deletion */
काष्ठा drm_gem_object *omap_gem_new(काष्ठा drm_device *dev,
		जोड़ omap_gem_size gsize, u32 flags);
काष्ठा drm_gem_object *omap_gem_new_dmabuf(काष्ठा drm_device *dev, माप_प्रकार size,
		काष्ठा sg_table *sgt);
पूर्णांक omap_gem_new_handle(काष्ठा drm_device *dev, काष्ठा drm_file *file,
		जोड़ omap_gem_size gsize, u32 flags, u32 *handle);
व्योम *omap_gem_vaddr(काष्ठा drm_gem_object *obj);

/* Dumb Buffers Interface */
पूर्णांक omap_gem_dumb_map_offset(काष्ठा drm_file *file, काष्ठा drm_device *dev,
		u32 handle, u64 *offset);
पूर्णांक omap_gem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
		काष्ठा drm_mode_create_dumb *args);

/* mmap() Interface */
पूर्णांक omap_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक omap_gem_mmap_obj(काष्ठा drm_gem_object *obj,
		काष्ठा vm_area_काष्ठा *vma);
u64 omap_gem_mmap_offset(काष्ठा drm_gem_object *obj);
माप_प्रकार omap_gem_mmap_size(काष्ठा drm_gem_object *obj);

/* PRIME Interface */
काष्ठा dma_buf *omap_gem_prime_export(काष्ठा drm_gem_object *obj, पूर्णांक flags);
काष्ठा drm_gem_object *omap_gem_prime_import(काष्ठा drm_device *dev,
		काष्ठा dma_buf *buffer);

पूर्णांक omap_gem_roll(काष्ठा drm_gem_object *obj, u32 roll);
व्योम omap_gem_cpu_sync_page(काष्ठा drm_gem_object *obj, पूर्णांक pgoff);
व्योम omap_gem_dma_sync_buffer(काष्ठा drm_gem_object *obj,
		क्रमागत dma_data_direction dir);
पूर्णांक omap_gem_pin(काष्ठा drm_gem_object *obj, dma_addr_t *dma_addr);
व्योम omap_gem_unpin(काष्ठा drm_gem_object *obj);
पूर्णांक omap_gem_get_pages(काष्ठा drm_gem_object *obj, काष्ठा page ***pages,
		bool remap);
पूर्णांक omap_gem_put_pages(काष्ठा drm_gem_object *obj);

u32 omap_gem_flags(काष्ठा drm_gem_object *obj);
पूर्णांक omap_gem_rotated_dma_addr(काष्ठा drm_gem_object *obj, u32 orient,
		पूर्णांक x, पूर्णांक y, dma_addr_t *dma_addr);
पूर्णांक omap_gem_tiled_stride(काष्ठा drm_gem_object *obj, u32 orient);

#पूर्ण_अगर /* __OMAPDRM_GEM_H__ */
