<शैली गुरु>
/* sis.c -- sis driver -*- linux-c -*-
 *
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_pciids.h>
#समावेश <drm/sis_drm.h>

#समावेश "sis_drv.h"

अटल काष्ठा pci_device_id pciidlist[] = अणु
	sisdrv_PCI_IDS
पूर्ण;

अटल पूर्णांक sis_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ chipset)
अणु
	drm_sis_निजी_t *dev_priv;

	pci_set_master(dev->pdev);

	dev_priv = kzalloc(माप(drm_sis_निजी_t), GFP_KERNEL);
	अगर (dev_priv == शून्य)
		वापस -ENOMEM;

	idr_init(&dev_priv->object_idr);
	dev->dev_निजी = (व्योम *)dev_priv;
	dev_priv->chipset = chipset;

	वापस 0;
पूर्ण

अटल व्योम sis_driver_unload(काष्ठा drm_device *dev)
अणु
	drm_sis_निजी_t *dev_priv = dev->dev_निजी;

	idr_destroy(&dev_priv->object_idr);

	kमुक्त(dev_priv);
पूर्ण

अटल स्थिर काष्ठा file_operations sis_driver_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = drm_ioctl,
	.mmap = drm_legacy_mmap,
	.poll = drm_poll,
	.compat_ioctl = drm_compat_ioctl,
	.llseek = noop_llseek,
पूर्ण;

अटल पूर्णांक sis_driver_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा sis_file_निजी *file_priv;

	DRM_DEBUG_DRIVER("\n");
	file_priv = kदो_स्मृति(माप(*file_priv), GFP_KERNEL);
	अगर (!file_priv)
		वापस -ENOMEM;

	file->driver_priv = file_priv;

	INIT_LIST_HEAD(&file_priv->obj_list);

	वापस 0;
पूर्ण

अटल व्योम sis_driver_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा sis_file_निजी *file_priv = file->driver_priv;

	kमुक्त(file_priv);
पूर्ण

अटल काष्ठा drm_driver driver = अणु
	.driver_features = DRIVER_USE_AGP | DRIVER_LEGACY,
	.load = sis_driver_load,
	.unload = sis_driver_unload,
	.खोलो = sis_driver_खोलो,
	.preबंद = sis_reclaim_buffers_locked,
	.postबंद = sis_driver_postबंद,
	.dma_quiescent = sis_idle,
	.lastबंद = sis_lastबंद,
	.ioctls = sis_ioctls,
	.fops = &sis_driver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

अटल काष्ठा pci_driver sis_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
पूर्ण;

अटल पूर्णांक __init sis_init(व्योम)
अणु
	driver.num_ioctls = sis_max_ioctl;
	वापस drm_legacy_pci_init(&driver, &sis_pci_driver);
पूर्ण

अटल व्योम __निकास sis_निकास(व्योम)
अणु
	drm_legacy_pci_निकास(&driver, &sis_pci_driver);
पूर्ण

module_init(sis_init);
module_निकास(sis_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
