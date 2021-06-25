<शैली गुरु>
/*
 * Copyright तऊ 2012 Red Hat
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * Copyright (c) 2009-2010, Code Aurora Forum.
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
 * Authors:
 *      Dave Airlie <airlied@redhat.com>
 *      Rob Clark <rob.clark@linaro.org>
 *
 */

#अगर_अघोषित __DRM_PRIME_H__
#घोषणा __DRM_PRIME_H__

#समावेश <linux/mutex.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/scatterlist.h>

/**
 * काष्ठा drm_prime_file_निजी - per-file tracking क्रम PRIME
 *
 * This just contains the पूर्णांकernal &काष्ठा dma_buf and handle caches क्रम each
 * &काष्ठा drm_file used by the PRIME core code.
 */
काष्ठा drm_prime_file_निजी अणु
/* निजी: */
	काष्ठा mutex lock;
	काष्ठा rb_root dmabufs;
	काष्ठा rb_root handles;
पूर्ण;

काष्ठा device;

काष्ठा dma_buf_export_info;
काष्ठा dma_buf;
काष्ठा dma_buf_attachment;
काष्ठा dma_buf_map;

क्रमागत dma_data_direction;

काष्ठा drm_device;
काष्ठा drm_gem_object;
काष्ठा drm_file;

/* core prime functions */
काष्ठा dma_buf *drm_gem_dmabuf_export(काष्ठा drm_device *dev,
				      काष्ठा dma_buf_export_info *exp_info);
व्योम drm_gem_dmabuf_release(काष्ठा dma_buf *dma_buf);

पूर्णांक drm_gem_prime_fd_to_handle(काष्ठा drm_device *dev,
			       काष्ठा drm_file *file_priv, पूर्णांक prime_fd, uपूर्णांक32_t *handle);
पूर्णांक drm_gem_prime_handle_to_fd(काष्ठा drm_device *dev,
			       काष्ठा drm_file *file_priv, uपूर्णांक32_t handle, uपूर्णांक32_t flags,
			       पूर्णांक *prime_fd);

/* helper functions क्रम exporting */
पूर्णांक drm_gem_map_attach(काष्ठा dma_buf *dma_buf,
		       काष्ठा dma_buf_attachment *attach);
व्योम drm_gem_map_detach(काष्ठा dma_buf *dma_buf,
			काष्ठा dma_buf_attachment *attach);
काष्ठा sg_table *drm_gem_map_dma_buf(काष्ठा dma_buf_attachment *attach,
				     क्रमागत dma_data_direction dir);
व्योम drm_gem_unmap_dma_buf(काष्ठा dma_buf_attachment *attach,
			   काष्ठा sg_table *sgt,
			   क्रमागत dma_data_direction dir);
पूर्णांक drm_gem_dmabuf_vmap(काष्ठा dma_buf *dma_buf, काष्ठा dma_buf_map *map);
व्योम drm_gem_dmabuf_vunmap(काष्ठा dma_buf *dma_buf, काष्ठा dma_buf_map *map);

पूर्णांक drm_gem_prime_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma);
पूर्णांक drm_gem_dmabuf_mmap(काष्ठा dma_buf *dma_buf, काष्ठा vm_area_काष्ठा *vma);

काष्ठा sg_table *drm_prime_pages_to_sg(काष्ठा drm_device *dev,
				       काष्ठा page **pages, अचिन्हित पूर्णांक nr_pages);
काष्ठा dma_buf *drm_gem_prime_export(काष्ठा drm_gem_object *obj,
				     पूर्णांक flags);

अचिन्हित दीर्घ drm_prime_get_contiguous_size(काष्ठा sg_table *sgt);

/* helper functions क्रम importing */
काष्ठा drm_gem_object *drm_gem_prime_import_dev(काष्ठा drm_device *dev,
						काष्ठा dma_buf *dma_buf,
						काष्ठा device *attach_dev);
काष्ठा drm_gem_object *drm_gem_prime_import(काष्ठा drm_device *dev,
					    काष्ठा dma_buf *dma_buf);

व्योम drm_prime_gem_destroy(काष्ठा drm_gem_object *obj, काष्ठा sg_table *sg);

पूर्णांक drm_prime_sg_to_page_array(काष्ठा sg_table *sgt, काष्ठा page **pages,
			       पूर्णांक max_pages);
पूर्णांक drm_prime_sg_to_dma_addr_array(काष्ठा sg_table *sgt, dma_addr_t *addrs,
				   पूर्णांक max_pages);

#पूर्ण_अगर /* __DRM_PRIME_H__ */
