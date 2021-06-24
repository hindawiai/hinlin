<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* exynos_drm_gem.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authoer: Inki Dae <inki.dae@samsung.com>
 */

#अगर_अघोषित _EXYNOS_DRM_GEM_H_
#घोषणा _EXYNOS_DRM_GEM_H_

#समावेश <drm/drm_gem.h>
#समावेश <linux/mm_types.h>

#घोषणा to_exynos_gem(x)	container_of(x, काष्ठा exynos_drm_gem, base)

#घोषणा IS_NONCONTIG_BUFFER(f)		(f & EXYNOS_BO_NONCONTIG)

/*
 * exynos drm buffer काष्ठाure.
 *
 * @base: a gem object.
 *	- a new handle to this gem object would be created
 *	by drm_gem_handle_create().
 * @flags: indicate memory type to allocated buffer and cache attruibute.
 * @size: size requested from user, in bytes and this size is aligned
 *	in page unit.
 * @cookie: cookie वापसed by dma_alloc_attrs
 * @kvaddr: kernel भव address to allocated memory region (क्रम fbdev)
 * @dma_addr: bus address(accessed by dma) to allocated memory region.
 *	- this address could be physical address without IOMMU and
 *	device address with IOMMU.
 * @dma_attrs: attrs passed dma mapping framework
 * @sgt: Imported sg_table.
 *
 * P.S. this object would be transferred to user as kms_bo.handle so
 *	user can access the buffer through kms_bo.handle.
 */
काष्ठा exynos_drm_gem अणु
	काष्ठा drm_gem_object	base;
	अचिन्हित पूर्णांक		flags;
	अचिन्हित दीर्घ		size;
	व्योम			*cookie;
	व्योम			*kvaddr;
	dma_addr_t		dma_addr;
	अचिन्हित दीर्घ		dma_attrs;
	काष्ठा sg_table		*sgt;
पूर्ण;

/* destroy a buffer with gem object */
व्योम exynos_drm_gem_destroy(काष्ठा exynos_drm_gem *exynos_gem);

/* create a new buffer with gem object */
काष्ठा exynos_drm_gem *exynos_drm_gem_create(काष्ठा drm_device *dev,
					     अचिन्हित पूर्णांक flags,
					     अचिन्हित दीर्घ size,
					     bool kvmap);

/*
 * request gem object creation and buffer allocation as the size
 * that it is calculated with framebuffer inक्रमmation such as width,
 * height and bpp.
 */
पूर्णांक exynos_drm_gem_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv);

/* get fake-offset of gem object that can be used with mmap. */
पूर्णांक exynos_drm_gem_map_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv);

/*
 * get exynos drm object from gem handle, this function could be used क्रम
 * other drivers such as 2d/3d acceleration drivers.
 * with this function call, gem object reference count would be increased.
 */
काष्ठा exynos_drm_gem *exynos_drm_gem_get(काष्ठा drm_file *filp,
					  अचिन्हित पूर्णांक gem_handle);

/*
 * put exynos drm object acquired from exynos_drm_gem_get(),
 * gem object reference count would be decreased.
 */
अटल अंतरभूत व्योम exynos_drm_gem_put(काष्ठा exynos_drm_gem *exynos_gem)
अणु
	drm_gem_object_put(&exynos_gem->base);
पूर्ण

/* get buffer inक्रमmation to memory region allocated by gem. */
पूर्णांक exynos_drm_gem_get_ioctl(काष्ठा drm_device *dev, व्योम *data,
				      काष्ठा drm_file *file_priv);

/* मुक्त gem object. */
व्योम exynos_drm_gem_मुक्त_object(काष्ठा drm_gem_object *obj);

/* create memory region क्रम drm framebuffer. */
पूर्णांक exynos_drm_gem_dumb_create(काष्ठा drm_file *file_priv,
			       काष्ठा drm_device *dev,
			       काष्ठा drm_mode_create_dumb *args);

/* set vm_flags and we can change the vm attribute to other one at here. */
पूर्णांक exynos_drm_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);

/* low-level पूर्णांकerface prime helpers */
काष्ठा drm_gem_object *exynos_drm_gem_prime_import(काष्ठा drm_device *dev,
					    काष्ठा dma_buf *dma_buf);
काष्ठा sg_table *exynos_drm_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj);
काष्ठा drm_gem_object *
exynos_drm_gem_prime_import_sg_table(काष्ठा drm_device *dev,
				     काष्ठा dma_buf_attachment *attach,
				     काष्ठा sg_table *sgt);
पूर्णांक exynos_drm_gem_prime_mmap(काष्ठा drm_gem_object *obj,
			      काष्ठा vm_area_काष्ठा *vma);

#पूर्ण_अगर
