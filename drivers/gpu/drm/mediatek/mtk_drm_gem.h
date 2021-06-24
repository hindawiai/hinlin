<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#अगर_अघोषित _MTK_DRM_GEM_H_
#घोषणा _MTK_DRM_GEM_H_

#समावेश <drm/drm_gem.h>

/*
 * mtk drm buffer काष्ठाure.
 *
 * @base: a gem object.
 *	- a new handle to this gem object would be created
 *	by drm_gem_handle_create().
 * @cookie: the वापस value of dma_alloc_attrs(), keep it क्रम dma_मुक्त_attrs()
 * @kvaddr: kernel भव address of gem buffer.
 * @dma_addr: dma address of gem buffer.
 * @dma_attrs: dma attributes of gem buffer.
 *
 * P.S. this object would be transferred to user as kms_bo.handle so
 *	user can access the buffer through kms_bo.handle.
 */
काष्ठा mtk_drm_gem_obj अणु
	काष्ठा drm_gem_object	base;
	व्योम			*cookie;
	व्योम			*kvaddr;
	dma_addr_t		dma_addr;
	अचिन्हित दीर्घ		dma_attrs;
	काष्ठा sg_table		*sg;
	काष्ठा page		**pages;
पूर्ण;

#घोषणा to_mtk_gem_obj(x)	container_of(x, काष्ठा mtk_drm_gem_obj, base)

व्योम mtk_drm_gem_मुक्त_object(काष्ठा drm_gem_object *gem);
काष्ठा mtk_drm_gem_obj *mtk_drm_gem_create(काष्ठा drm_device *dev, माप_प्रकार size,
					   bool alloc_kmap);
पूर्णांक mtk_drm_gem_dumb_create(काष्ठा drm_file *file_priv, काष्ठा drm_device *dev,
			    काष्ठा drm_mode_create_dumb *args);
पूर्णांक mtk_drm_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक mtk_drm_gem_mmap_buf(काष्ठा drm_gem_object *obj,
			 काष्ठा vm_area_काष्ठा *vma);
काष्ठा sg_table *mtk_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj);
काष्ठा drm_gem_object *mtk_gem_prime_import_sg_table(काष्ठा drm_device *dev,
			काष्ठा dma_buf_attachment *attach, काष्ठा sg_table *sg);
पूर्णांक mtk_drm_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);
व्योम mtk_drm_gem_prime_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);

#पूर्ण_अगर
