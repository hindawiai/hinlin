<शैली गुरु>
/*
 * \पile drm_agpsupport.c
 * DRM support क्रम AGP/GART backend
 *
 * \चuthor Rickard E. (Rik) Faith <faith@valinux.com>
 * \चuthor Gareth Hughes <gareth@valinux.com>
 */

/*
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All Rights Reserved.
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

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/agp.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_legacy.h"

/*
 * Get AGP inक्रमmation.
 *
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies the AGP device has been initialized and acquired and fills in the
 * drm_agp_info काष्ठाure with the inक्रमmation in drm_agp_head::agp_info.
 */
पूर्णांक drm_agp_info(काष्ठा drm_device *dev, काष्ठा drm_agp_info *info)
अणु
	काष्ठा agp_kern_info *kern;

	अगर (!dev->agp || !dev->agp->acquired)
		वापस -EINVAL;

	kern = &dev->agp->agp_info;
	info->agp_version_major = kern->version.major;
	info->agp_version_minor = kern->version.minor;
	info->mode = kern->mode;
	info->aperture_base = kern->aper_base;
	info->aperture_size = kern->aper_size * 1024 * 1024;
	info->memory_allowed = kern->max_memory << PAGE_SHIFT;
	info->memory_used = kern->current_memory << PAGE_SHIFT;
	info->id_venकरोr = kern->device->venकरोr;
	info->id_device = kern->device->device;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_agp_info);

पूर्णांक drm_agp_info_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_agp_info *info = data;
	पूर्णांक err;

	err = drm_agp_info(dev, info);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/*
 * Acquire the AGP device.
 *
 * \param dev DRM device that is to acquire AGP.
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies the AGP device hasn't been acquired beक्रमe and calls
 * \c agp_backend_acquire.
 */
पूर्णांक drm_agp_acquire(काष्ठा drm_device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	अगर (!dev->agp)
		वापस -ENODEV;
	अगर (dev->agp->acquired)
		वापस -EBUSY;
	dev->agp->bridge = agp_backend_acquire(pdev);
	अगर (!dev->agp->bridge)
		वापस -ENODEV;
	dev->agp->acquired = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_agp_acquire);

/*
 * Acquire the AGP device (ioctl).
 *
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies the AGP device hasn't been acquired beक्रमe and calls
 * \c agp_backend_acquire.
 */
पूर्णांक drm_agp_acquire_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	वापस drm_agp_acquire((काष्ठा drm_device *) file_priv->minor->dev);
पूर्ण

/*
 * Release the AGP device.
 *
 * \param dev DRM device that is to release AGP.
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies the AGP device has been acquired and calls \c agp_backend_release.
 */
पूर्णांक drm_agp_release(काष्ठा drm_device *dev)
अणु
	अगर (!dev->agp || !dev->agp->acquired)
		वापस -EINVAL;
	agp_backend_release(dev->agp->bridge);
	dev->agp->acquired = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_agp_release);

पूर्णांक drm_agp_release_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	वापस drm_agp_release(dev);
पूर्ण

/*
 * Enable the AGP bus.
 *
 * \param dev DRM device that has previously acquired AGP.
 * \param mode Requested AGP mode.
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies the AGP device has been acquired but not enabled, and calls
 * \c agp_enable.
 */
पूर्णांक drm_agp_enable(काष्ठा drm_device *dev, काष्ठा drm_agp_mode mode)
अणु
	अगर (!dev->agp || !dev->agp->acquired)
		वापस -EINVAL;

	dev->agp->mode = mode.mode;
	agp_enable(dev->agp->bridge, mode.mode);
	dev->agp->enabled = 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_agp_enable);

पूर्णांक drm_agp_enable_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_agp_mode *mode = data;

	वापस drm_agp_enable(dev, *mode);
पूर्ण

/*
 * Allocate AGP memory.
 *
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies the AGP device is present and has been acquired, allocates the
 * memory via agp_allocate_memory() and creates a drm_agp_mem entry क्रम it.
 */
पूर्णांक drm_agp_alloc(काष्ठा drm_device *dev, काष्ठा drm_agp_buffer *request)
अणु
	काष्ठा drm_agp_mem *entry;
	काष्ठा agp_memory *memory;
	अचिन्हित दीर्घ pages;
	u32 type;

	अगर (!dev->agp || !dev->agp->acquired)
		वापस -EINVAL;
	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	pages = DIV_ROUND_UP(request->size, PAGE_SIZE);
	type = (u32) request->type;
	memory = agp_allocate_memory(dev->agp->bridge, pages, type);
	अगर (!memory) अणु
		kमुक्त(entry);
		वापस -ENOMEM;
	पूर्ण

	entry->handle = (अचिन्हित दीर्घ)memory->key + 1;
	entry->memory = memory;
	entry->bound = 0;
	entry->pages = pages;
	list_add(&entry->head, &dev->agp->memory);

	request->handle = entry->handle;
	request->physical = memory->physical;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_agp_alloc);


पूर्णांक drm_agp_alloc_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_agp_buffer *request = data;

	वापस drm_agp_alloc(dev, request);
पूर्ण

/*
 * Search क्रम the AGP memory entry associated with a handle.
 *
 * \param dev DRM device काष्ठाure.
 * \param handle AGP memory handle.
 * \लeturn poपूर्णांकer to the drm_agp_mem काष्ठाure associated with \p handle.
 *
 * Walks through drm_agp_head::memory until finding a matching handle.
 */
अटल काष्ठा drm_agp_mem *drm_agp_lookup_entry(काष्ठा drm_device *dev,
						अचिन्हित दीर्घ handle)
अणु
	काष्ठा drm_agp_mem *entry;

	list_क्रम_each_entry(entry, &dev->agp->memory, head) अणु
		अगर (entry->handle == handle)
			वापस entry;
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Unbind AGP memory from the GATT (ioctl).
 *
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies the AGP device is present and acquired, looks-up the AGP memory
 * entry and passes it to the unbind_agp() function.
 */
पूर्णांक drm_agp_unbind(काष्ठा drm_device *dev, काष्ठा drm_agp_binding *request)
अणु
	काष्ठा drm_agp_mem *entry;
	पूर्णांक ret;

	अगर (!dev->agp || !dev->agp->acquired)
		वापस -EINVAL;
	entry = drm_agp_lookup_entry(dev, request->handle);
	अगर (!entry || !entry->bound)
		वापस -EINVAL;
	ret = agp_unbind_memory(entry->memory);
	अगर (ret == 0)
		entry->bound = 0;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_agp_unbind);


पूर्णांक drm_agp_unbind_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_agp_binding *request = data;

	वापस drm_agp_unbind(dev, request);
पूर्ण

/*
 * Bind AGP memory पूर्णांकo the GATT (ioctl)
 *
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies the AGP device is present and has been acquired and that no memory
 * is currently bound पूर्णांकo the GATT. Looks-up the AGP memory entry and passes
 * it to bind_agp() function.
 */
पूर्णांक drm_agp_bind(काष्ठा drm_device *dev, काष्ठा drm_agp_binding *request)
अणु
	काष्ठा drm_agp_mem *entry;
	पूर्णांक retcode;
	पूर्णांक page;

	अगर (!dev->agp || !dev->agp->acquired)
		वापस -EINVAL;
	entry = drm_agp_lookup_entry(dev, request->handle);
	अगर (!entry || entry->bound)
		वापस -EINVAL;
	page = DIV_ROUND_UP(request->offset, PAGE_SIZE);
	retcode = agp_bind_memory(entry->memory, page);
	अगर (retcode)
		वापस retcode;
	entry->bound = dev->agp->base + (page << PAGE_SHIFT);
	DRM_DEBUG("base = 0x%lx entry->bound = 0x%lx\n",
		  dev->agp->base, entry->bound);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_agp_bind);


पूर्णांक drm_agp_bind_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_agp_binding *request = data;

	वापस drm_agp_bind(dev, request);
पूर्ण

/*
 * Free AGP memory (ioctl).
 *
 * \लeturn zero on success or a negative number on failure.
 *
 * Verअगरies the AGP device is present and has been acquired and looks up the
 * AGP memory entry. If the memory is currently bound, unbind it via
 * unbind_agp(). Frees it via मुक्त_agp() as well as the entry itself
 * and unlinks from the करोubly linked list it's inserted in.
 */
पूर्णांक drm_agp_मुक्त(काष्ठा drm_device *dev, काष्ठा drm_agp_buffer *request)
अणु
	काष्ठा drm_agp_mem *entry;

	अगर (!dev->agp || !dev->agp->acquired)
		वापस -EINVAL;
	entry = drm_agp_lookup_entry(dev, request->handle);
	अगर (!entry)
		वापस -EINVAL;
	अगर (entry->bound)
		agp_unbind_memory(entry->memory);

	list_del(&entry->head);

	agp_मुक्त_memory(entry->memory);
	kमुक्त(entry);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_agp_मुक्त);


पूर्णांक drm_agp_मुक्त_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_agp_buffer *request = data;

	वापस drm_agp_मुक्त(dev, request);
पूर्ण

/*
 * Initialize the AGP resources.
 *
 * \लeturn poपूर्णांकer to a drm_agp_head काष्ठाure.
 *
 * Gets the drm_agp_t काष्ठाure which is made available by the agpgart module
 * via the पूर्णांकer_module_* functions. Creates and initializes a drm_agp_head
 * काष्ठाure.
 *
 * Note that final cleanup of the kदो_स्मृतिed काष्ठाure is directly करोne in
 * drm_pci_agp_destroy.
 */
काष्ठा drm_agp_head *drm_agp_init(काष्ठा drm_device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा drm_agp_head *head = शून्य;

	head = kzalloc(माप(*head), GFP_KERNEL);
	अगर (!head)
		वापस शून्य;
	head->bridge = agp_find_bridge(pdev);
	अगर (!head->bridge) अणु
		head->bridge = agp_backend_acquire(pdev);
		अगर (!head->bridge) अणु
			kमुक्त(head);
			वापस शून्य;
		पूर्ण
		agp_copy_info(head->bridge, &head->agp_info);
		agp_backend_release(head->bridge);
	पूर्ण अन्यथा अणु
		agp_copy_info(head->bridge, &head->agp_info);
	पूर्ण
	अगर (head->agp_info.chipset == NOT_SUPPORTED) अणु
		kमुक्त(head);
		वापस शून्य;
	पूर्ण
	INIT_LIST_HEAD(&head->memory);
	head->cant_use_aperture = head->agp_info.cant_use_aperture;
	head->page_mask = head->agp_info.page_mask;
	head->base = head->agp_info.aper_base;
	वापस head;
पूर्ण
/* Only exported क्रम i810.ko */
EXPORT_SYMBOL(drm_agp_init);

/**
 * drm_legacy_agp_clear - Clear AGP resource list
 * @dev: DRM device
 *
 * Iterate over all AGP resources and हटाओ them. But keep the AGP head
 * पूर्णांकact so it can still be used. It is safe to call this अगर AGP is disabled or
 * was alपढ़ोy हटाओd.
 *
 * Cleanup is only करोne क्रम drivers who have DRIVER_LEGACY set.
 */
व्योम drm_legacy_agp_clear(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_agp_mem *entry, *tempe;

	अगर (!dev->agp)
		वापस;
	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस;

	list_क्रम_each_entry_safe(entry, tempe, &dev->agp->memory, head) अणु
		अगर (entry->bound)
			agp_unbind_memory(entry->memory);
		agp_मुक्त_memory(entry->memory);
		kमुक्त(entry);
	पूर्ण
	INIT_LIST_HEAD(&dev->agp->memory);

	अगर (dev->agp->acquired)
		drm_agp_release(dev);

	dev->agp->acquired = 0;
	dev->agp->enabled = 0;
पूर्ण
