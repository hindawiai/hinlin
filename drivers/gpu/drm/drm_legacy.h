<शैली गुरु>
#अगर_अघोषित __DRM_LEGACY_H__
#घोषणा __DRM_LEGACY_H__

/*
 * Copyright (c) 2014 David Herrmann <dh.herrmann@gmail.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * This file contains legacy पूर्णांकerfaces that modern drm drivers
 * should no दीर्घer be using. They cannot be हटाओd as legacy
 * drivers use them, and removing them are API अवरोधs.
 */
#समावेश <linux/list.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_legacy.h>

काष्ठा agp_memory;
काष्ठा drm_device;
काष्ठा drm_file;
काष्ठा drm_buf_desc;

/*
 * Generic DRM Contexts
 */

#घोषणा DRM_KERNEL_CONTEXT		0
#घोषणा DRM_RESERVED_CONTEXTS		1

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
व्योम drm_legacy_ctxbiपंचांगap_init(काष्ठा drm_device *dev);
व्योम drm_legacy_ctxbiपंचांगap_cleanup(काष्ठा drm_device *dev);
व्योम drm_legacy_ctxbiपंचांगap_flush(काष्ठा drm_device *dev, काष्ठा drm_file *file);
#अन्यथा
अटल अंतरभूत व्योम drm_legacy_ctxbiपंचांगap_init(काष्ठा drm_device *dev) अणुपूर्ण
अटल अंतरभूत व्योम drm_legacy_ctxbiपंचांगap_cleanup(काष्ठा drm_device *dev) अणुपूर्ण
अटल अंतरभूत व्योम drm_legacy_ctxbiपंचांगap_flush(काष्ठा drm_device *dev, काष्ठा drm_file *file) अणुपूर्ण
#पूर्ण_अगर

व्योम drm_legacy_ctxbiपंचांगap_मुक्त(काष्ठा drm_device *dev, पूर्णांक ctx_handle);

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
पूर्णांक drm_legacy_resctx(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_addctx(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_अ_लोtx(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_चयनctx(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_newctx(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_rmctx(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);

पूर्णांक drm_legacy_setsareactx(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_माला_लोareactx(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
#पूर्ण_अगर

/*
 * Generic Buffer Management
 */

#घोषणा DRM_MAP_HASH_OFFSET 0x10000000

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
अटल अंतरभूत पूर्णांक drm_legacy_create_map_hash(काष्ठा drm_device *dev)
अणु
	वापस drm_ht_create(&dev->map_hash, 12);
पूर्ण

अटल अंतरभूत व्योम drm_legacy_हटाओ_map_hash(काष्ठा drm_device *dev)
अणु
	drm_ht_हटाओ(&dev->map_hash);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक drm_legacy_create_map_hash(काष्ठा drm_device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम drm_legacy_हटाओ_map_hash(काष्ठा drm_device *dev) अणुपूर्ण
#पूर्ण_अगर


#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
पूर्णांक drm_legacy_geपंचांगap_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv);
पूर्णांक drm_legacy_addmap_ioctl(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_rmmap_ioctl(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);

पूर्णांक drm_legacy_addbufs(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_infobufs(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_markbufs(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_मुक्तbufs(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_mapbufs(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_dma_ioctl(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
#पूर्ण_अगर

पूर्णांक __drm_legacy_infobufs(काष्ठा drm_device *, व्योम *, पूर्णांक *,
			  पूर्णांक (*)(व्योम *, पूर्णांक, काष्ठा drm_buf_entry *));
पूर्णांक __drm_legacy_mapbufs(काष्ठा drm_device *, व्योम *, पूर्णांक *,
			  व्योम __user **,
			  पूर्णांक (*)(व्योम *, पूर्णांक, अचिन्हित दीर्घ, काष्ठा drm_buf *),
			  काष्ठा drm_file *);

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
व्योम drm_legacy_master_rmmaps(काष्ठा drm_device *dev,
			      काष्ठा drm_master *master);
व्योम drm_legacy_rmmaps(काष्ठा drm_device *dev);
#अन्यथा
अटल अंतरभूत व्योम drm_legacy_master_rmmaps(काष्ठा drm_device *dev,
					    काष्ठा drm_master *master) अणुपूर्ण
अटल अंतरभूत व्योम drm_legacy_rmmaps(काष्ठा drm_device *dev) अणुपूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
व्योम drm_legacy_vma_flush(काष्ठा drm_device *d);
#अन्यथा
अटल अंतरभूत व्योम drm_legacy_vma_flush(काष्ठा drm_device *d)
अणु
	/* करो nothing */
पूर्ण
#पूर्ण_अगर

/*
 * AGP Support
 */

काष्ठा drm_agp_mem अणु
	अचिन्हित दीर्घ handle;
	काष्ठा agp_memory *memory;
	अचिन्हित दीर्घ bound;
	पूर्णांक pages;
	काष्ठा list_head head;
पूर्ण;

/* drm_lock.c */
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
पूर्णांक drm_legacy_lock(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
पूर्णांक drm_legacy_unlock(काष्ठा drm_device *d, व्योम *v, काष्ठा drm_file *f);
व्योम drm_legacy_lock_release(काष्ठा drm_device *dev, काष्ठा file *filp);
#अन्यथा
अटल अंतरभूत व्योम drm_legacy_lock_release(काष्ठा drm_device *dev, काष्ठा file *filp) अणुपूर्ण
#पूर्ण_अगर

/* DMA support */
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
पूर्णांक drm_legacy_dma_setup(काष्ठा drm_device *dev);
व्योम drm_legacy_dma_takeकरोwn(काष्ठा drm_device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक drm_legacy_dma_setup(काष्ठा drm_device *dev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम drm_legacy_मुक्त_buffer(काष्ठा drm_device *dev,
			    काष्ठा drm_buf * buf);
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
व्योम drm_legacy_reclaim_buffers(काष्ठा drm_device *dev,
				काष्ठा drm_file *filp);
#अन्यथा
अटल अंतरभूत व्योम drm_legacy_reclaim_buffers(काष्ठा drm_device *dev,
					      काष्ठा drm_file *filp) अणुपूर्ण
#पूर्ण_अगर

/* Scatter Gather Support */
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
व्योम drm_legacy_sg_cleanup(काष्ठा drm_device *dev);
पूर्णांक drm_legacy_sg_alloc(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv);
पूर्णांक drm_legacy_sg_मुक्त(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
व्योम drm_legacy_init_members(काष्ठा drm_device *dev);
व्योम drm_legacy_destroy_members(काष्ठा drm_device *dev);
व्योम drm_legacy_dev_reinit(काष्ठा drm_device *dev);
पूर्णांक drm_legacy_setup(काष्ठा drm_device * dev);
#अन्यथा
अटल अंतरभूत व्योम drm_legacy_init_members(काष्ठा drm_device *dev) अणुपूर्ण
अटल अंतरभूत व्योम drm_legacy_destroy_members(काष्ठा drm_device *dev) अणुपूर्ण
अटल अंतरभूत व्योम drm_legacy_dev_reinit(काष्ठा drm_device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक drm_legacy_setup(काष्ठा drm_device * dev) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
व्योम drm_legacy_lock_master_cleanup(काष्ठा drm_device *dev, काष्ठा drm_master *master);
#अन्यथा
अटल अंतरभूत व्योम drm_legacy_lock_master_cleanup(काष्ठा drm_device *dev, काष्ठा drm_master *master) अणुपूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
व्योम drm_master_legacy_init(काष्ठा drm_master *master);
#अन्यथा
अटल अंतरभूत व्योम drm_master_legacy_init(काष्ठा drm_master *master) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __DRM_LEGACY_H__ */
