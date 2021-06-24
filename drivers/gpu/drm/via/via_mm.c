<शैली गुरु>
/*
 * Copyright 2006 Tungsten Graphics Inc., Bismarck, ND., USA.
 * All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/*
 * Authors: Thomas Hellstrथघm <thomas-at-tungstengraphics-करोt-com>
 */

#समावेश <linux/slab.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/via_drm.h>

#समावेश "via_drv.h"

#घोषणा VIA_MM_ALIGN_SHIFT 4
#घोषणा VIA_MM_ALIGN_MASK ((1 << VIA_MM_ALIGN_SHIFT) - 1)

काष्ठा via_memblock अणु
	काष्ठा drm_mm_node mm_node;
	काष्ठा list_head owner_list;
पूर्ण;

पूर्णांक via_agp_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_agp_t *agp = data;
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;

	mutex_lock(&dev->काष्ठा_mutex);
	drm_mm_init(&dev_priv->agp_mm, 0, agp->size >> VIA_MM_ALIGN_SHIFT);

	dev_priv->agp_initialized = 1;
	dev_priv->agp_offset = agp->offset;
	mutex_unlock(&dev->काष्ठा_mutex);

	DRM_DEBUG("offset = %u, size = %u\n", agp->offset, agp->size);
	वापस 0;
पूर्ण

पूर्णांक via_fb_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_fb_t *fb = data;
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;

	mutex_lock(&dev->काष्ठा_mutex);
	drm_mm_init(&dev_priv->vram_mm, 0, fb->size >> VIA_MM_ALIGN_SHIFT);

	dev_priv->vram_initialized = 1;
	dev_priv->vram_offset = fb->offset;

	mutex_unlock(&dev->काष्ठा_mutex);
	DRM_DEBUG("offset = %u, size = %u\n", fb->offset, fb->size);

	वापस 0;

पूर्ण

पूर्णांक via_final_context(काष्ठा drm_device *dev, पूर्णांक context)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;

	via_release_futex(dev_priv, context);

	/* Linux specअगरic until context tracking code माला_लो ported to BSD */
	/* Last context, perक्रमm cleanup */
	अगर (list_is_singular(&dev->ctxlist)) अणु
		DRM_DEBUG("Last Context\n");
		drm_irq_uninstall(dev);
		via_cleanup_futex(dev_priv);
		via_करो_cleanup_map(dev);
	पूर्ण
	वापस 1;
पूर्ण

व्योम via_lastबंद(काष्ठा drm_device *dev)
अणु
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;

	अगर (!dev_priv)
		वापस;

	mutex_lock(&dev->काष्ठा_mutex);
	अगर (dev_priv->vram_initialized) अणु
		drm_mm_takeकरोwn(&dev_priv->vram_mm);
		dev_priv->vram_initialized = 0;
	पूर्ण
	अगर (dev_priv->agp_initialized) अणु
		drm_mm_takeकरोwn(&dev_priv->agp_mm);
		dev_priv->agp_initialized = 0;
	पूर्ण
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण

पूर्णांक via_mem_alloc(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file)
अणु
	drm_via_mem_t *mem = data;
	पूर्णांक retval = 0, user_key;
	काष्ठा via_memblock *item;
	drm_via_निजी_t *dev_priv = (drm_via_निजी_t *) dev->dev_निजी;
	काष्ठा via_file_निजी *file_priv = file->driver_priv;
	अचिन्हित दीर्घ पंचांगpSize;

	अगर (mem->type > VIA_MEM_AGP) अणु
		DRM_ERROR("Unknown memory type allocation\n");
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&dev->काष्ठा_mutex);
	अगर (0 == ((mem->type == VIA_MEM_VIDEO) ? dev_priv->vram_initialized :
		      dev_priv->agp_initialized)) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		DRM_ERROR
		    ("Attempt to allocate from uninitialized memory manager.\n");
		वापस -EINVAL;
	पूर्ण

	item = kzalloc(माप(*item), GFP_KERNEL);
	अगर (!item) अणु
		retval = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	पंचांगpSize = (mem->size + VIA_MM_ALIGN_MASK) >> VIA_MM_ALIGN_SHIFT;
	अगर (mem->type == VIA_MEM_AGP)
		retval = drm_mm_insert_node(&dev_priv->agp_mm,
					    &item->mm_node,
					    पंचांगpSize);
	अन्यथा
		retval = drm_mm_insert_node(&dev_priv->vram_mm,
					    &item->mm_node,
					    पंचांगpSize);
	अगर (retval)
		जाओ fail_alloc;

	retval = idr_alloc(&dev_priv->object_idr, item, 1, 0, GFP_KERNEL);
	अगर (retval < 0)
		जाओ fail_idr;
	user_key = retval;

	list_add(&item->owner_list, &file_priv->obj_list);
	mutex_unlock(&dev->काष्ठा_mutex);

	mem->offset = ((mem->type == VIA_MEM_VIDEO) ?
		      dev_priv->vram_offset : dev_priv->agp_offset) +
	    ((item->mm_node.start) << VIA_MM_ALIGN_SHIFT);
	mem->index = user_key;

	वापस 0;

fail_idr:
	drm_mm_हटाओ_node(&item->mm_node);
fail_alloc:
	kमुक्त(item);
	mutex_unlock(&dev->काष्ठा_mutex);

	mem->offset = 0;
	mem->size = 0;
	mem->index = 0;
	DRM_DEBUG("Video memory allocation failed\n");

	वापस retval;
पूर्ण

पूर्णांक via_mem_मुक्त(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_via_निजी_t *dev_priv = dev->dev_निजी;
	drm_via_mem_t *mem = data;
	काष्ठा via_memblock *obj;

	mutex_lock(&dev->काष्ठा_mutex);
	obj = idr_find(&dev_priv->object_idr, mem->index);
	अगर (obj == शून्य) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		वापस -EINVAL;
	पूर्ण

	idr_हटाओ(&dev_priv->object_idr, mem->index);
	list_del(&obj->owner_list);
	drm_mm_हटाओ_node(&obj->mm_node);
	kमुक्त(obj);
	mutex_unlock(&dev->काष्ठा_mutex);

	DRM_DEBUG("free = 0x%lx\n", mem->index);

	वापस 0;
पूर्ण


व्योम via_reclaim_buffers_locked(काष्ठा drm_device *dev,
				काष्ठा drm_file *file)
अणु
	काष्ठा via_file_निजी *file_priv = file->driver_priv;
	काष्ठा via_memblock *entry, *next;

	अगर (!(dev->master && file->master->lock.hw_lock))
		वापस;

	drm_legacy_idlelock_take(&file->master->lock);

	mutex_lock(&dev->काष्ठा_mutex);
	अगर (list_empty(&file_priv->obj_list)) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		drm_legacy_idlelock_release(&file->master->lock);

		वापस;
	पूर्ण

	via_driver_dma_quiescent(dev);

	list_क्रम_each_entry_safe(entry, next, &file_priv->obj_list,
				 owner_list) अणु
		list_del(&entry->owner_list);
		drm_mm_हटाओ_node(&entry->mm_node);
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&dev->काष्ठा_mutex);

	drm_legacy_idlelock_release(&file->master->lock);

	वापस;
पूर्ण
