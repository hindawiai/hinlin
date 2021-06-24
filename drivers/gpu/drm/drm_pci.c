<शैली गुरु>
/*
 * Copyright 2003 Josथऊ Fonseca.
 * Copyright 2003 Leअगर Delgass.
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_internal.h"
#समावेश "drm_legacy.h"

#अगर_घोषित CONFIG_DRM_LEGACY
/* List of devices hanging off drivers with stealth attach. */
अटल LIST_HEAD(legacy_dev_list);
अटल DEFINE_MUTEX(legacy_dev_list_lock);

/**
 * drm_pci_alloc - Allocate a PCI consistent memory block, क्रम DMA.
 * @dev: DRM device
 * @size: size of block to allocate
 * @align: alignment of block
 *
 * FIXME: This is a needless असलtraction of the Linux dma-api and should be
 * हटाओd.
 *
 * Return: A handle to the allocated memory block on success or शून्य on
 * failure.
 */
drm_dma_handle_t *drm_pci_alloc(काष्ठा drm_device * dev, माप_प्रकार size, माप_प्रकार align)
अणु
	drm_dma_handle_t *dmah;

	/* pci_alloc_consistent only guarantees alignment to the smallest
	 * PAGE_SIZE order which is greater than or equal to the requested size.
	 * Return शून्य here क्रम now to make sure nobody tries क्रम larger alignment
	 */
	अगर (align > size)
		वापस शून्य;

	dmah = kदो_स्मृति(माप(drm_dma_handle_t), GFP_KERNEL);
	अगर (!dmah)
		वापस शून्य;

	dmah->size = size;
	dmah->vaddr = dma_alloc_coherent(dev->dev, size,
					 &dmah->busaddr,
					 GFP_KERNEL);

	अगर (dmah->vaddr == शून्य) अणु
		kमुक्त(dmah);
		वापस शून्य;
	पूर्ण

	वापस dmah;
पूर्ण
EXPORT_SYMBOL(drm_pci_alloc);

/**
 * drm_pci_मुक्त - Free a PCI consistent memory block
 * @dev: DRM device
 * @dmah: handle to memory block
 *
 * FIXME: This is a needless असलtraction of the Linux dma-api and should be
 * हटाओd.
 */
व्योम drm_pci_मुक्त(काष्ठा drm_device * dev, drm_dma_handle_t * dmah)
अणु
	dma_मुक्त_coherent(dev->dev, dmah->size, dmah->vaddr,
			  dmah->busaddr);
	kमुक्त(dmah);
पूर्ण

EXPORT_SYMBOL(drm_pci_मुक्त);
#पूर्ण_अगर

अटल पूर्णांक drm_get_pci_करोमुख्य(काष्ठा drm_device *dev)
अणु
#अगर_अघोषित __alpha__
	/* For historical reasons, drm_get_pci_करोमुख्य() is busticated
	 * on most archs and has to reमुख्य so क्रम userspace पूर्णांकerface
	 * < 1.4, except on alpha which was right from the beginning
	 */
	अगर (dev->अगर_version < 0x10004)
		वापस 0;
#पूर्ण_अगर /* __alpha__ */

	वापस pci_करोमुख्य_nr(to_pci_dev(dev->dev)->bus);
पूर्ण

पूर्णांक drm_pci_set_busid(काष्ठा drm_device *dev, काष्ठा drm_master *master)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	master->unique = kaप्र_लिखो(GFP_KERNEL, "pci:%04x:%02x:%02x.%d",
					drm_get_pci_करोमुख्य(dev),
					pdev->bus->number,
					PCI_SLOT(pdev->devfn),
					PCI_FUNC(pdev->devfn));
	अगर (!master->unique)
		वापस -ENOMEM;

	master->unique_len = म_माप(master->unique);
	वापस 0;
पूर्ण

अटल पूर्णांक drm_pci_irq_by_busid(काष्ठा drm_device *dev, काष्ठा drm_irq_busid *p)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	अगर ((p->busnum >> 8) != drm_get_pci_करोमुख्य(dev) ||
	    (p->busnum & 0xff) != pdev->bus->number ||
	    p->devnum != PCI_SLOT(pdev->devfn) || p->funcnum != PCI_FUNC(pdev->devfn))
		वापस -EINVAL;

	p->irq = pdev->irq;

	DRM_DEBUG("%d:%d:%d => IRQ %d\n", p->busnum, p->devnum, p->funcnum,
		  p->irq);
	वापस 0;
पूर्ण

/**
 * drm_legacy_irq_by_busid - Get पूर्णांकerrupt from bus ID
 * @dev: DRM device
 * @data: IOCTL parameter poपूर्णांकing to a drm_irq_busid काष्ठाure
 * @file_priv: DRM file निजी.
 *
 * Finds the PCI device with the specअगरied bus id and माला_लो its IRQ number.
 * This IOCTL is deprecated, and will now वापस EINVAL क्रम any busid not equal
 * to that of the device that this DRM instance attached to.
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_legacy_irq_by_busid(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_irq_busid *p = data;

	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस -EOPNOTSUPP;

	/* UMS was only ever support on PCI devices. */
	अगर (WARN_ON(!dev_is_pci(dev->dev)))
		वापस -EINVAL;

	अगर (!drm_core_check_feature(dev, DRIVER_HAVE_IRQ))
		वापस -EOPNOTSUPP;

	वापस drm_pci_irq_by_busid(dev, p);
पूर्ण

व्योम drm_pci_agp_destroy(काष्ठा drm_device *dev)
अणु
	अगर (dev->agp) अणु
		arch_phys_wc_del(dev->agp->agp_mtrr);
		drm_legacy_agp_clear(dev);
		kमुक्त(dev->agp);
		dev->agp = शून्य;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_DRM_LEGACY

अटल व्योम drm_pci_agp_init(काष्ठा drm_device *dev)
अणु
	अगर (drm_core_check_feature(dev, DRIVER_USE_AGP)) अणु
		अगर (pci_find_capability(to_pci_dev(dev->dev), PCI_CAP_ID_AGP))
			dev->agp = drm_agp_init(dev);
		अगर (dev->agp) अणु
			dev->agp->agp_mtrr = arch_phys_wc_add(
				dev->agp->agp_info.aper_base,
				dev->agp->agp_info.aper_size *
				1024 * 1024);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक drm_get_pci_dev(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent,
			   स्थिर काष्ठा drm_driver *driver)
अणु
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	DRM_DEBUG("\n");

	dev = drm_dev_alloc(driver, &pdev->dev);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	ret = pci_enable_device(pdev);
	अगर (ret)
		जाओ err_मुक्त;

	dev->pdev = pdev;
#अगर_घोषित __alpha__
	dev->hose = pdev->sysdata;
#पूर्ण_अगर

	अगर (drm_core_check_feature(dev, DRIVER_MODESET))
		pci_set_drvdata(pdev, dev);

	drm_pci_agp_init(dev);

	ret = drm_dev_रेजिस्टर(dev, ent->driver_data);
	अगर (ret)
		जाओ err_agp;

	अगर (drm_core_check_feature(dev, DRIVER_LEGACY)) अणु
		mutex_lock(&legacy_dev_list_lock);
		list_add_tail(&dev->legacy_dev_list, &legacy_dev_list);
		mutex_unlock(&legacy_dev_list_lock);
	पूर्ण

	वापस 0;

err_agp:
	drm_pci_agp_destroy(dev);
	pci_disable_device(pdev);
err_मुक्त:
	drm_dev_put(dev);
	वापस ret;
पूर्ण

/**
 * drm_legacy_pci_init - shaकरोw-attach a legacy DRM PCI driver
 * @driver: DRM device driver
 * @pdriver: PCI device driver
 *
 * This is only used by legacy dri1 drivers and deprecated.
 *
 * Return: 0 on success or a negative error code on failure.
 */
पूर्णांक drm_legacy_pci_init(स्थिर काष्ठा drm_driver *driver,
			काष्ठा pci_driver *pdriver)
अणु
	काष्ठा pci_dev *pdev = शून्य;
	स्थिर काष्ठा pci_device_id *pid;
	पूर्णांक i;

	DRM_DEBUG("\n");

	अगर (WARN_ON(!(driver->driver_features & DRIVER_LEGACY)))
		वापस -EINVAL;

	/* If not using KMS, fall back to stealth mode manual scanning. */
	क्रम (i = 0; pdriver->id_table[i].venकरोr != 0; i++) अणु
		pid = &pdriver->id_table[i];

		/* Loop around setting up a DRM device क्रम each PCI device
		 * matching our ID and device class.  If we had the पूर्णांकernal
		 * function that pci_get_subsys and pci_get_class used, we'd
		 * be able to just pass pid in instead of करोing a two-stage
		 * thing.
		 */
		pdev = शून्य;
		जबतक ((pdev =
			pci_get_subsys(pid->venकरोr, pid->device, pid->subvenकरोr,
				       pid->subdevice, pdev)) != शून्य) अणु
			अगर ((pdev->class & pid->class_mask) != pid->class)
				जारी;

			/* stealth mode requires a manual probe */
			pci_dev_get(pdev);
			drm_get_pci_dev(pdev, pid, driver);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_legacy_pci_init);

/**
 * drm_legacy_pci_निकास - unरेजिस्टर shaकरोw-attach legacy DRM driver
 * @driver: DRM device driver
 * @pdriver: PCI device driver
 *
 * Unरेजिस्टर a DRM driver shaकरोw-attached through drm_legacy_pci_init(). This
 * is deprecated and only used by dri1 drivers.
 */
व्योम drm_legacy_pci_निकास(स्थिर काष्ठा drm_driver *driver,
			 काष्ठा pci_driver *pdriver)
अणु
	काष्ठा drm_device *dev, *पंचांगp;

	DRM_DEBUG("\n");

	अगर (!(driver->driver_features & DRIVER_LEGACY)) अणु
		WARN_ON(1);
	पूर्ण अन्यथा अणु
		mutex_lock(&legacy_dev_list_lock);
		list_क्रम_each_entry_safe(dev, पंचांगp, &legacy_dev_list,
					 legacy_dev_list) अणु
			अगर (dev->driver == driver) अणु
				list_del(&dev->legacy_dev_list);
				drm_put_dev(dev);
			पूर्ण
		पूर्ण
		mutex_unlock(&legacy_dev_list_lock);
	पूर्ण
	DRM_INFO("Module unloaded\n");
पूर्ण
EXPORT_SYMBOL(drm_legacy_pci_निकास);

#पूर्ण_अगर
