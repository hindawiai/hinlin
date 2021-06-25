<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AMD IOMMU driver
 *
 * Copyright (C) 2018 Advanced Micro Devices, Inc.
 *
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/pci.h>

#समावेश "amd_iommu.h"

अटल काष्ठा dentry *amd_iommu_debugfs;
अटल DEFINE_MUTEX(amd_iommu_debugfs_lock);

#घोषणा	MAX_NAME_LEN	20

व्योम amd_iommu_debugfs_setup(काष्ठा amd_iommu *iommu)
अणु
	अक्षर name[MAX_NAME_LEN + 1];

	mutex_lock(&amd_iommu_debugfs_lock);
	अगर (!amd_iommu_debugfs)
		amd_iommu_debugfs = debugfs_create_dir("amd",
						       iommu_debugfs_dir);
	mutex_unlock(&amd_iommu_debugfs_lock);

	snम_लिखो(name, MAX_NAME_LEN, "iommu%02d", iommu->index);
	iommu->debugfs = debugfs_create_dir(name, amd_iommu_debugfs);
पूर्ण
