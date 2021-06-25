<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * VFIO ZPCI devices support
 *
 * Copyright (C) IBM Corp. 2020.  All rights reserved.
 *	Author(s): Pierre Morel <pmorel@linux.ibm.com>
 *                 Matthew Rosato <mjrosato@linux.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/vfio_zdev.h>
#समावेश <यंत्र/pci_clp.h>
#समावेश <यंत्र/pci_पन.स>

#समावेश "vfio_pci_private.h"

/*
 * Add the Base PCI Function inक्रमmation to the device info region.
 */
अटल पूर्णांक zpci_base_cap(काष्ठा zpci_dev *zdev, काष्ठा vfio_info_cap *caps)
अणु
	काष्ठा vfio_device_info_cap_zpci_base cap = अणु
		.header.id = VFIO_DEVICE_INFO_CAP_ZPCI_BASE,
		.header.version = 1,
		.start_dma = zdev->start_dma,
		.end_dma = zdev->end_dma,
		.pchid = zdev->pchid,
		.vfn = zdev->vfn,
		.fmb_length = zdev->fmb_length,
		.pft = zdev->pft,
		.gid = zdev->pfgid
	पूर्ण;

	वापस vfio_info_add_capability(caps, &cap.header, माप(cap));
पूर्ण

/*
 * Add the Base PCI Function Group inक्रमmation to the device info region.
 */
अटल पूर्णांक zpci_group_cap(काष्ठा zpci_dev *zdev, काष्ठा vfio_info_cap *caps)
अणु
	काष्ठा vfio_device_info_cap_zpci_group cap = अणु
		.header.id = VFIO_DEVICE_INFO_CAP_ZPCI_GROUP,
		.header.version = 1,
		.dयंत्र = zdev->dma_mask,
		.msi_addr = zdev->msi_addr,
		.flags = VFIO_DEVICE_INFO_ZPCI_FLAG_REFRESH,
		.mui = zdev->fmb_update,
		.noi = zdev->max_msi,
		.maxstbl = ZPCI_MAX_WRITE_SIZE,
		.version = zdev->version
	पूर्ण;

	वापस vfio_info_add_capability(caps, &cap.header, माप(cap));
पूर्ण

/*
 * Add the device utility string to the device info region.
 */
अटल पूर्णांक zpci_util_cap(काष्ठा zpci_dev *zdev, काष्ठा vfio_info_cap *caps)
अणु
	काष्ठा vfio_device_info_cap_zpci_util *cap;
	पूर्णांक cap_size = माप(*cap) + CLP_UTIL_STR_LEN;
	पूर्णांक ret;

	cap = kदो_स्मृति(cap_size, GFP_KERNEL);
	अगर (!cap)
		वापस -ENOMEM;

	cap->header.id = VFIO_DEVICE_INFO_CAP_ZPCI_UTIL;
	cap->header.version = 1;
	cap->size = CLP_UTIL_STR_LEN;
	स_नकल(cap->util_str, zdev->util_str, cap->size);

	ret = vfio_info_add_capability(caps, &cap->header, cap_size);

	kमुक्त(cap);

	वापस ret;
पूर्ण

/*
 * Add the function path string to the device info region.
 */
अटल पूर्णांक zpci_pfip_cap(काष्ठा zpci_dev *zdev, काष्ठा vfio_info_cap *caps)
अणु
	काष्ठा vfio_device_info_cap_zpci_pfip *cap;
	पूर्णांक cap_size = माप(*cap) + CLP_PFIP_NR_SEGMENTS;
	पूर्णांक ret;

	cap = kदो_स्मृति(cap_size, GFP_KERNEL);
	अगर (!cap)
		वापस -ENOMEM;

	cap->header.id = VFIO_DEVICE_INFO_CAP_ZPCI_PFIP;
	cap->header.version = 1;
	cap->size = CLP_PFIP_NR_SEGMENTS;
	स_नकल(cap->pfip, zdev->pfip, cap->size);

	ret = vfio_info_add_capability(caps, &cap->header, cap_size);

	kमुक्त(cap);

	वापस ret;
पूर्ण

/*
 * Add all supported capabilities to the VFIO_DEVICE_GET_INFO capability chain.
 */
पूर्णांक vfio_pci_info_zdev_add_caps(काष्ठा vfio_pci_device *vdev,
				काष्ठा vfio_info_cap *caps)
अणु
	काष्ठा zpci_dev *zdev = to_zpci(vdev->pdev);
	पूर्णांक ret;

	अगर (!zdev)
		वापस -ENODEV;

	ret = zpci_base_cap(zdev, caps);
	अगर (ret)
		वापस ret;

	ret = zpci_group_cap(zdev, caps);
	अगर (ret)
		वापस ret;

	अगर (zdev->util_str_avail) अणु
		ret = zpci_util_cap(zdev, caps);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = zpci_pfip_cap(zdev, caps);

	वापस ret;
पूर्ण
