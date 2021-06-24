<शैली गुरु>
/* savage_drv.c -- Savage driver क्रम Linux
 *
 * Copyright 2004  Felix Kuehling
 * All Rights Reserved.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT. IN NO EVENT SHALL FELIX KUEHLING BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_pciids.h>

#समावेश "savage_drv.h"

अटल काष्ठा pci_device_id pciidlist[] = अणु
	savage_PCI_IDS
पूर्ण;

अटल स्थिर काष्ठा file_operations savage_driver_fops = अणु
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
	    DRIVER_USE_AGP | DRIVER_HAVE_DMA | DRIVER_PCI_DMA | DRIVER_LEGACY,
	.dev_priv_size = माप(drm_savage_buf_priv_t),
	.load = savage_driver_load,
	.firstखोलो = savage_driver_firstखोलो,
	.preबंद = savage_reclaim_buffers,
	.lastबंद = savage_driver_lastबंद,
	.unload = savage_driver_unload,
	.ioctls = savage_ioctls,
	.dma_ioctl = savage_bci_buffers,
	.fops = &savage_driver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

अटल काष्ठा pci_driver savage_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
पूर्ण;

अटल पूर्णांक __init savage_init(व्योम)
अणु
	driver.num_ioctls = savage_max_ioctl;
	वापस drm_legacy_pci_init(&driver, &savage_pci_driver);
पूर्ण

अटल व्योम __निकास savage_निकास(व्योम)
अणु
	drm_legacy_pci_निकास(&driver, &savage_pci_driver);
पूर्ण

module_init(savage_init);
module_निकास(savage_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
