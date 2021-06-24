<शैली गुरु>
/*
 * Copyright 1998-2003 VIA Technologies, Inc. All Rights Reserved.
 * Copyright 2001-2003 S3 Graphics, Inc. All Rights Reserved.
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
 * VIA, S3 GRAPHICS, AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_pciids.h>
#समावेश <drm/via_drm.h>

#समावेश "via_drv.h"


अटल पूर्णांक via_driver_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा via_file_निजी *file_priv;

	DRM_DEBUG_DRIVER("\n");
	file_priv = kदो_स्मृति(माप(*file_priv), GFP_KERNEL);
	अगर (!file_priv)
		वापस -ENOMEM;

	file->driver_priv = file_priv;

	INIT_LIST_HEAD(&file_priv->obj_list);

	वापस 0;
पूर्ण

अटल व्योम via_driver_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file)
अणु
	काष्ठा via_file_निजी *file_priv = file->driver_priv;

	kमुक्त(file_priv);
पूर्ण

अटल काष्ठा pci_device_id pciidlist[] = अणु
	viadrv_PCI_IDS
पूर्ण;

अटल स्थिर काष्ठा file_operations via_driver_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = drm_ioctl,
	.mmap = drm_legacy_mmap,
	.poll = drm_poll,
	.compat_ioctl = drm_compat_ioctl,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा drm_driver driver = अणु
	.driver_features =
	    DRIVER_USE_AGP | DRIVER_HAVE_IRQ | DRIVER_LEGACY,
	.load = via_driver_load,
	.unload = via_driver_unload,
	.खोलो = via_driver_खोलो,
	.preबंद = via_reclaim_buffers_locked,
	.postबंद = via_driver_postबंद,
	.context_dtor = via_final_context,
	.get_vblank_counter = via_get_vblank_counter,
	.enable_vblank = via_enable_vblank,
	.disable_vblank = via_disable_vblank,
	.irq_preinstall = via_driver_irq_preinstall,
	.irq_postinstall = via_driver_irq_postinstall,
	.irq_uninstall = via_driver_irq_uninstall,
	.irq_handler = via_driver_irq_handler,
	.dma_quiescent = via_driver_dma_quiescent,
	.lastबंद = via_lastबंद,
	.ioctls = via_ioctls,
	.fops = &via_driver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

अटल काष्ठा pci_driver via_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
पूर्ण;

अटल पूर्णांक __init via_init(व्योम)
अणु
	driver.num_ioctls = via_max_ioctl;
	via_init_command_verअगरier();
	वापस drm_legacy_pci_init(&driver, &via_pci_driver);
पूर्ण

अटल व्योम __निकास via_निकास(व्योम)
अणु
	drm_legacy_pci_निकास(&driver, &via_pci_driver);
पूर्ण

module_init(via_init);
module_निकास(via_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
