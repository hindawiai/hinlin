<शैली गुरु>
#अगर_अघोषित __DRM_DRM_LEGACY_H__
#घोषणा __DRM_DRM_LEGACY_H__
/*
 * Legacy driver पूर्णांकerfaces क्रम the Direct Rendering Manager
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * Copyright (c) 2009-2010, Code Aurora Forum.
 * All rights reserved.
 * Copyright तऊ 2014 Intel Corporation
 *   Daniel Vetter <daniel.vetter@ffwll.ch>
 *
 * Author: Rickard E. (Rik) Faith <faith@valinux.com>
 * Author: Gareth Hughes <gareth@valinux.com>
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <drm/drm.h>
#समावेश <drm/drm_auth.h>
#समावेश <drm/drm_hashtab.h>

काष्ठा drm_device;
काष्ठा drm_driver;
काष्ठा file;
काष्ठा pci_driver;

/*
 * Legacy Support क्रम palateontologic DRM drivers
 *
 * If you add a new driver and it uses any of these functions or काष्ठाures,
 * you're करोing it terribly wrong.
 */

/**
 * DMA buffer.
 */
काष्ठा drm_buf अणु
	पूर्णांक idx;		       /**< Index पूर्णांकo master buflist */
	पूर्णांक total;		       /**< Buffer size */
	पूर्णांक order;		       /**< log-base-2(total) */
	पूर्णांक used;		       /**< Amount of buffer in use (क्रम DMA) */
	अचिन्हित दीर्घ offset;	       /**< Byte offset (used पूर्णांकernally) */
	व्योम *address;		       /**< Address of buffer */
	अचिन्हित दीर्घ bus_address;     /**< Bus address of buffer */
	काष्ठा drm_buf *next;	       /**< Kernel-only: used क्रम मुक्त list */
	__अस्थिर__ पूर्णांक रुकोing;      /**< On kernel DMA queue */
	__अस्थिर__ पूर्णांक pending;      /**< On hardware DMA queue */
	काष्ठा drm_file *file_priv;    /**< Private of holding file descr */
	पूर्णांक context;		       /**< Kernel queue क्रम this buffer */
	पूर्णांक जबतक_locked;	       /**< Dispatch this buffer जबतक locked */
	क्रमागत अणु
		DRM_LIST_NONE = 0,
		DRM_LIST_FREE = 1,
		DRM_LIST_WAIT = 2,
		DRM_LIST_PEND = 3,
		DRM_LIST_PRIO = 4,
		DRM_LIST_RECLAIM = 5
	पूर्ण list;			       /**< Which list we're on */

	पूर्णांक dev_priv_size;		 /**< Size of buffer निजी storage */
	व्योम *dev_निजी;		 /**< Per-buffer निजी storage */
पूर्ण;

प्रकार काष्ठा drm_dma_handle अणु
	dma_addr_t busaddr;
	व्योम *vaddr;
	माप_प्रकार size;
पूर्ण drm_dma_handle_t;

/**
 * Buffer entry.  There is one of this क्रम each buffer size order.
 */
काष्ठा drm_buf_entry अणु
	पूर्णांक buf_size;			/**< size */
	पूर्णांक buf_count;			/**< number of buffers */
	काष्ठा drm_buf *buflist;		/**< buffer list */
	पूर्णांक seg_count;
	पूर्णांक page_order;
	काष्ठा drm_dma_handle **seglist;

	पूर्णांक low_mark;			/**< Low water mark */
	पूर्णांक high_mark;			/**< High water mark */
पूर्ण;

/**
 * DMA data.
 */
काष्ठा drm_device_dma अणु

	काष्ठा drm_buf_entry bufs[DRM_MAX_ORDER + 1];	/**< buffers, grouped by their size order */
	पूर्णांक buf_count;			/**< total number of buffers */
	काष्ठा drm_buf **buflist;		/**< Vector of poपूर्णांकers पूर्णांकo drm_device_dma::bufs */
	पूर्णांक seg_count;
	पूर्णांक page_count;			/**< number of pages */
	अचिन्हित दीर्घ *pagelist;	/**< page list */
	अचिन्हित दीर्घ byte_count;
	क्रमागत अणु
		_DRM_DMA_USE_AGP = 0x01,
		_DRM_DMA_USE_SG = 0x02,
		_DRM_DMA_USE_FB = 0x04,
		_DRM_DMA_USE_PCI_RO = 0x08
	पूर्ण flags;

पूर्ण;

/**
 * Scatter-gather memory.
 */
काष्ठा drm_sg_mem अणु
	अचिन्हित दीर्घ handle;
	व्योम *भव;
	पूर्णांक pages;
	काष्ठा page **pagelist;
	dma_addr_t *busaddr;
पूर्ण;

/**
 * Kernel side of a mapping
 */
काष्ठा drm_local_map अणु
	dma_addr_t offset;	 /**< Requested physical address (0 क्रम SAREA)*/
	अचिन्हित दीर्घ size;	 /**< Requested physical size (bytes) */
	क्रमागत drm_map_type type;	 /**< Type of memory to map */
	क्रमागत drm_map_flags flags;	 /**< Flags */
	व्योम *handle;		 /**< User-space: "Handle" to pass to mmap() */
				 /**< Kernel-space: kernel-भव address */
	पूर्णांक mtrr;		 /**< MTRR slot used */
पूर्ण;

प्रकार काष्ठा drm_local_map drm_local_map_t;

/**
 * Mappings list
 */
काष्ठा drm_map_list अणु
	काष्ठा list_head head;		/**< list head */
	काष्ठा drm_hash_item hash;
	काष्ठा drm_local_map *map;	/**< mapping */
	uपूर्णांक64_t user_token;
	काष्ठा drm_master *master;
पूर्ण;

पूर्णांक drm_legacy_addmap(काष्ठा drm_device *d, resource_माप_प्रकार offset,
		      अचिन्हित पूर्णांक size, क्रमागत drm_map_type type,
		      क्रमागत drm_map_flags flags, काष्ठा drm_local_map **map_p);
काष्ठा drm_local_map *drm_legacy_findmap(काष्ठा drm_device *dev, अचिन्हित पूर्णांक token);
व्योम drm_legacy_rmmap(काष्ठा drm_device *d, काष्ठा drm_local_map *map);
पूर्णांक drm_legacy_rmmap_locked(काष्ठा drm_device *d, काष्ठा drm_local_map *map);
काष्ठा drm_local_map *drm_legacy_माला_लोarea(काष्ठा drm_device *dev);
पूर्णांक drm_legacy_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);

पूर्णांक drm_legacy_addbufs_agp(काष्ठा drm_device *d, काष्ठा drm_buf_desc *req);
पूर्णांक drm_legacy_addbufs_pci(काष्ठा drm_device *d, काष्ठा drm_buf_desc *req);

/**
 * Test that the hardware lock is held by the caller, वापसing otherwise.
 *
 * \param dev DRM device.
 * \param filp file poपूर्णांकer of the caller.
 */
#घोषणा LOCK_TEST_WITH_RETURN( dev, _file_priv )				\
करो अणु										\
	अगर (!_DRM_LOCK_IS_HELD(_file_priv->master->lock.hw_lock->lock) ||	\
	    _file_priv->master->lock.file_priv != _file_priv)	अणु		\
		DRM_ERROR( "%s called without lock held, held  %d owner %p %p\n",\
			   __func__, _DRM_LOCK_IS_HELD(_file_priv->master->lock.hw_lock->lock),\
			   _file_priv->master->lock.file_priv, _file_priv);	\
		वापस -EINVAL;							\
	पूर्ण									\
पूर्ण जबतक (0)

व्योम drm_legacy_idlelock_take(काष्ठा drm_lock_data *lock);
व्योम drm_legacy_idlelock_release(काष्ठा drm_lock_data *lock);

/* drm_pci.c */

#अगर_घोषित CONFIG_PCI

काष्ठा drm_dma_handle *drm_pci_alloc(काष्ठा drm_device *dev, माप_प्रकार size,
				     माप_प्रकार align);
व्योम drm_pci_मुक्त(काष्ठा drm_device *dev, काष्ठा drm_dma_handle *dmah);

पूर्णांक drm_legacy_pci_init(स्थिर काष्ठा drm_driver *driver,
			काष्ठा pci_driver *pdriver);
व्योम drm_legacy_pci_निकास(स्थिर काष्ठा drm_driver *driver,
			 काष्ठा pci_driver *pdriver);

#अन्यथा

अटल अंतरभूत काष्ठा drm_dma_handle *drm_pci_alloc(काष्ठा drm_device *dev,
						   माप_प्रकार size, माप_प्रकार align)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम drm_pci_मुक्त(काष्ठा drm_device *dev,
				काष्ठा drm_dma_handle *dmah)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक drm_legacy_pci_init(स्थिर काष्ठा drm_driver *driver,
				      काष्ठा pci_driver *pdriver)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम drm_legacy_pci_निकास(स्थिर काष्ठा drm_driver *driver,
				       काष्ठा pci_driver *pdriver)
अणु
पूर्ण

#पूर्ण_अगर

/* drm_memory.c */
व्योम drm_legacy_ioremap(काष्ठा drm_local_map *map, काष्ठा drm_device *dev);
व्योम drm_legacy_ioremap_wc(काष्ठा drm_local_map *map, काष्ठा drm_device *dev);
व्योम drm_legacy_ioremapमुक्त(काष्ठा drm_local_map *map, काष्ठा drm_device *dev);

#पूर्ण_अगर /* __DRM_DRM_LEGACY_H__ */
