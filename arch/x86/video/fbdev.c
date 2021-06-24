<शैली गुरु>
/*
 * Copyright (C) 2007 Antonino Daplas <adaplas@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 */
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/vgaarb.h>

पूर्णांक fb_is_primary_device(काष्ठा fb_info *info)
अणु
	काष्ठा device *device = info->device;
	काष्ठा pci_dev *शेष_device = vga_शेष_device();
	काष्ठा pci_dev *pci_dev;
	काष्ठा resource *res;

	अगर (!device || !dev_is_pci(device))
		वापस 0;

	pci_dev = to_pci_dev(device);

	अगर (शेष_device) अणु
		अगर (pci_dev == शेष_device)
			वापस 1;
		वापस 0;
	पूर्ण

	res = pci_dev->resource + PCI_ROM_RESOURCE;

	अगर (res->flags & IORESOURCE_ROM_SHADOW)
		वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fb_is_primary_device);
MODULE_LICENSE("GPL");
