<शैली गुरु>
/**************************************************************************
 *
 * Copyright 2006 Tungsten Graphics, Inc., Bismarck, ND., USA.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 **************************************************************************/

/*
 * Authors:
 *    Thomas Hellstrथघm <thomas-at-tungstengraphics-करोt-com>
 */

#समावेश <video/sisfb.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/sis_drm.h>

#समावेश "sis_drv.h"


#घोषणा VIDEO_TYPE 0
#घोषणा AGP_TYPE 1


काष्ठा sis_memblock अणु
	काष्ठा drm_mm_node mm_node;
	काष्ठा sis_memreq req;
	काष्ठा list_head owner_list;
पूर्ण;

#अगर defined(CONFIG_FB_SIS) || defined(CONFIG_FB_SIS_MODULE)
/* fb management via fb device */

#घोषणा SIS_MM_ALIGN_SHIFT 0
#घोषणा SIS_MM_ALIGN_MASK 0

#अन्यथा /* CONFIG_FB_SIS[_MODULE] */

#घोषणा SIS_MM_ALIGN_SHIFT 4
#घोषणा SIS_MM_ALIGN_MASK ((1 << SIS_MM_ALIGN_SHIFT) - 1)

#पूर्ण_अगर /* CONFIG_FB_SIS[_MODULE] */

अटल पूर्णांक sis_fb_init(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_sis_निजी_t *dev_priv = dev->dev_निजी;
	drm_sis_fb_t *fb = data;

	mutex_lock(&dev->काष्ठा_mutex);
	/* Unconditionally init the drm_mm, even though we करोn't use it when the
	 * fb sis driver is available - make cleanup easier. */
	drm_mm_init(&dev_priv->vram_mm, 0, fb->size >> SIS_MM_ALIGN_SHIFT);

	dev_priv->vram_initialized = 1;
	dev_priv->vram_offset = fb->offset;

	mutex_unlock(&dev->काष्ठा_mutex);
	DRM_DEBUG("offset = %lu, size = %lu\n", fb->offset, fb->size);

	वापस 0;
पूर्ण

अटल पूर्णांक sis_drm_alloc(काष्ठा drm_device *dev, काष्ठा drm_file *file,
			 व्योम *data, पूर्णांक pool)
अणु
	drm_sis_निजी_t *dev_priv = dev->dev_निजी;
	drm_sis_mem_t *mem = data;
	पूर्णांक retval = 0, user_key;
	काष्ठा sis_memblock *item;
	काष्ठा sis_file_निजी *file_priv = file->driver_priv;
	अचिन्हित दीर्घ offset;

	mutex_lock(&dev->काष्ठा_mutex);

	अगर (0 == ((pool == 0) ? dev_priv->vram_initialized :
		      dev_priv->agp_initialized)) अणु
		DRM_ERROR
		    ("Attempt to allocate from uninitialized memory manager.\n");
		mutex_unlock(&dev->काष्ठा_mutex);
		वापस -EINVAL;
	पूर्ण

	item = kzalloc(माप(*item), GFP_KERNEL);
	अगर (!item) अणु
		retval = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	mem->size = (mem->size + SIS_MM_ALIGN_MASK) >> SIS_MM_ALIGN_SHIFT;
	अगर (pool == AGP_TYPE) अणु
		retval = drm_mm_insert_node(&dev_priv->agp_mm,
					    &item->mm_node,
					    mem->size);
		offset = item->mm_node.start;
	पूर्ण अन्यथा अणु
#अगर defined(CONFIG_FB_SIS) || defined(CONFIG_FB_SIS_MODULE)
		item->req.size = mem->size;
		sis_दो_स्मृति(&item->req);
		अगर (item->req.size == 0)
			retval = -ENOMEM;
		offset = item->req.offset;
#अन्यथा
		retval = drm_mm_insert_node(&dev_priv->vram_mm,
					    &item->mm_node,
					    mem->size);
		offset = item->mm_node.start;
#पूर्ण_अगर
	पूर्ण
	अगर (retval)
		जाओ fail_alloc;

	retval = idr_alloc(&dev_priv->object_idr, item, 1, 0, GFP_KERNEL);
	अगर (retval < 0)
		जाओ fail_idr;
	user_key = retval;

	list_add(&item->owner_list, &file_priv->obj_list);
	mutex_unlock(&dev->काष्ठा_mutex);

	mem->offset = ((pool == 0) ?
		      dev_priv->vram_offset : dev_priv->agp_offset) +
	    (offset << SIS_MM_ALIGN_SHIFT);
	mem->मुक्त = user_key;
	mem->size = mem->size << SIS_MM_ALIGN_SHIFT;

	वापस 0;

fail_idr:
	drm_mm_हटाओ_node(&item->mm_node);
fail_alloc:
	kमुक्त(item);
	mutex_unlock(&dev->काष्ठा_mutex);

	mem->offset = 0;
	mem->size = 0;
	mem->मुक्त = 0;

	DRM_DEBUG("alloc %d, size = %ld, offset = %ld\n", pool, mem->size,
		  mem->offset);

	वापस retval;
पूर्ण

अटल पूर्णांक sis_drm_मुक्त(काष्ठा drm_device *dev, व्योम *data, काष्ठा drm_file *file_priv)
अणु
	drm_sis_निजी_t *dev_priv = dev->dev_निजी;
	drm_sis_mem_t *mem = data;
	काष्ठा sis_memblock *obj;

	mutex_lock(&dev->काष्ठा_mutex);
	obj = idr_find(&dev_priv->object_idr, mem->मुक्त);
	अगर (obj == शून्य) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		वापस -EINVAL;
	पूर्ण

	idr_हटाओ(&dev_priv->object_idr, mem->मुक्त);
	list_del(&obj->owner_list);
	अगर (drm_mm_node_allocated(&obj->mm_node))
		drm_mm_हटाओ_node(&obj->mm_node);
#अगर defined(CONFIG_FB_SIS) || defined(CONFIG_FB_SIS_MODULE)
	अन्यथा
		sis_मुक्त(obj->req.offset);
#पूर्ण_अगर
	kमुक्त(obj);
	mutex_unlock(&dev->काष्ठा_mutex);
	DRM_DEBUG("free = 0x%lx\n", mem->मुक्त);

	वापस 0;
पूर्ण

अटल पूर्णांक sis_fb_alloc(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	वापस sis_drm_alloc(dev, file_priv, data, VIDEO_TYPE);
पूर्ण

अटल पूर्णांक sis_ioctl_agp_init(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv)
अणु
	drm_sis_निजी_t *dev_priv = dev->dev_निजी;
	drm_sis_agp_t *agp = data;
	dev_priv = dev->dev_निजी;

	mutex_lock(&dev->काष्ठा_mutex);
	drm_mm_init(&dev_priv->agp_mm, 0, agp->size >> SIS_MM_ALIGN_SHIFT);

	dev_priv->agp_initialized = 1;
	dev_priv->agp_offset = agp->offset;
	mutex_unlock(&dev->काष्ठा_mutex);

	DRM_DEBUG("offset = %lu, size = %lu\n", agp->offset, agp->size);
	वापस 0;
पूर्ण

अटल पूर्णांक sis_ioctl_agp_alloc(काष्ठा drm_device *dev, व्योम *data,
			       काष्ठा drm_file *file_priv)
अणु

	वापस sis_drm_alloc(dev, file_priv, data, AGP_TYPE);
पूर्ण

अटल drm_local_map_t *sis_reg_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_map_list *entry;
	drm_local_map_t *map;

	list_क्रम_each_entry(entry, &dev->maplist, head) अणु
		map = entry->map;
		अगर (!map)
			जारी;
		अगर (map->type == _DRM_REGISTERS)
			वापस map;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक sis_idle(काष्ठा drm_device *dev)
अणु
	drm_sis_निजी_t *dev_priv = dev->dev_निजी;
	uपूर्णांक32_t idle_reg;
	अचिन्हित दीर्घ end;
	पूर्णांक i;

	अगर (dev_priv->idle_fault)
		वापस 0;

	अगर (dev_priv->mmio == शून्य) अणु
		dev_priv->mmio = sis_reg_init(dev);
		अगर (dev_priv->mmio == शून्य) अणु
			DRM_ERROR("Could not find register map.\n");
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Implement a device चयन here अगर needed
	 */

	अगर (dev_priv->chipset != SIS_CHIP_315)
		वापस 0;

	/*
	 * Timeout after 3 seconds. We cannot use DRM_WAIT_ON here
	 * because its polling frequency is too low.
	 */

	end = jअगरfies + (HZ * 3);

	क्रम (i = 0; i < 4; ++i) अणु
		करो अणु
			idle_reg = SIS_READ(0x85cc);
		पूर्ण जबतक (!समय_after_eq(jअगरfies, end) &&
			  ((idle_reg & 0x80000000) != 0x80000000));
	पूर्ण

	अगर (समय_after_eq(jअगरfies, end)) अणु
		DRM_ERROR("Graphics engine idle timeout. "
			  "Disabling idle check\n");
		dev_priv->idle_fault = 1;
	पूर्ण

	/*
	 * The caller never sees an error code. It माला_लो trapped
	 * in libdrm.
	 */

	वापस 0;
पूर्ण


व्योम sis_lastबंद(काष्ठा drm_device *dev)
अणु
	drm_sis_निजी_t *dev_priv = dev->dev_निजी;

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
	dev_priv->mmio = शून्य;
	mutex_unlock(&dev->काष्ठा_mutex);
पूर्ण

व्योम sis_reclaim_buffers_locked(काष्ठा drm_device *dev,
				काष्ठा drm_file *file)
अणु
	काष्ठा sis_file_निजी *file_priv = file->driver_priv;
	काष्ठा sis_memblock *entry, *next;

	अगर (!(dev->master && file->master->lock.hw_lock))
		वापस;

	drm_legacy_idlelock_take(&file->master->lock);

	mutex_lock(&dev->काष्ठा_mutex);
	अगर (list_empty(&file_priv->obj_list)) अणु
		mutex_unlock(&dev->काष्ठा_mutex);
		drm_legacy_idlelock_release(&file->master->lock);

		वापस;
	पूर्ण

	sis_idle(dev);


	list_क्रम_each_entry_safe(entry, next, &file_priv->obj_list,
				 owner_list) अणु
		list_del(&entry->owner_list);
		अगर (drm_mm_node_allocated(&entry->mm_node))
			drm_mm_हटाओ_node(&entry->mm_node);
#अगर defined(CONFIG_FB_SIS) || defined(CONFIG_FB_SIS_MODULE)
		अन्यथा
			sis_मुक्त(entry->req.offset);
#पूर्ण_अगर
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&dev->काष्ठा_mutex);

	drm_legacy_idlelock_release(&file->master->lock);

	वापस;
पूर्ण

स्थिर काष्ठा drm_ioctl_desc sis_ioctls[] = अणु
	DRM_IOCTL_DEF_DRV(SIS_FB_ALLOC, sis_fb_alloc, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(SIS_FB_FREE, sis_drm_मुक्त, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(SIS_AGP_INIT, sis_ioctl_agp_init, DRM_AUTH | DRM_MASTER | DRM_ROOT_ONLY),
	DRM_IOCTL_DEF_DRV(SIS_AGP_ALLOC, sis_ioctl_agp_alloc, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(SIS_AGP_FREE, sis_drm_मुक्त, DRM_AUTH),
	DRM_IOCTL_DEF_DRV(SIS_FB_INIT, sis_fb_init, DRM_AUTH | DRM_MASTER | DRM_ROOT_ONLY),
पूर्ण;

पूर्णांक sis_max_ioctl = ARRAY_SIZE(sis_ioctls);
