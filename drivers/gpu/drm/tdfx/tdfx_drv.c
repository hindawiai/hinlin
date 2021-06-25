<शैली गुरु>
/* tdfx_drv.c -- tdfx driver -*- linux-c -*-
 * Created: Thu Oct  7 10:38:32 1999 by faith@precisioninsight.com
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
 * Authors:
 *    Rickard E. (Rik) Faith <faith@valinux.com>
 *    Daryll Strauss <daryll@valinux.com>
 *    Gareth Hughes <gareth@valinux.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_legacy.h>
#समावेश <drm/drm_pciids.h>

#समावेश "tdfx_drv.h"

अटल काष्ठा pci_device_id pciidlist[] = अणु
	tdfx_PCI_IDS
पूर्ण;

अटल स्थिर काष्ठा file_operations tdfx_driver_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = drm_ioctl,
	.mmap = drm_legacy_mmap,
	.poll = drm_poll,
	.compat_ioctl = drm_compat_ioctl,
	.llseek = noop_llseek,
पूर्ण;

अटल स्थिर काष्ठा drm_driver driver = अणु
	.driver_features = DRIVER_LEGACY,
	.fops = &tdfx_driver_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL,
पूर्ण;

अटल काष्ठा pci_driver tdfx_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
पूर्ण;

अटल पूर्णांक __init tdfx_init(व्योम)
अणु
	वापस drm_legacy_pci_init(&driver, &tdfx_pci_driver);
पूर्ण

अटल व्योम __निकास tdfx_निकास(व्योम)
अणु
	drm_legacy_pci_निकास(&driver, &tdfx_pci_driver);
पूर्ण

module_init(tdfx_init);
module_निकास(tdfx_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL and additional rights");
