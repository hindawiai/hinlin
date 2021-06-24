<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2013-2017 Oracle Corporation
 * This file is based on ast_tपंचांग.c
 * Copyright 2012 Red Hat Inc.
 * Authors: Dave Airlie <airlied@redhat.com>
 *          Michael Thayer <michael.thayer@oracle.com>
 */
#समावेश <linux/pci.h>
#समावेश <drm/drm_file.h>
#समावेश "vbox_drv.h"

पूर्णांक vbox_mm_init(काष्ठा vbox_निजी *vbox)
अणु
	पूर्णांक ret;
	काष्ठा drm_device *dev = &vbox->ddev;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	ret = drmm_vram_helper_init(dev, pci_resource_start(pdev, 0),
				       vbox->available_vram_size);
	अगर (ret) अणु
		DRM_ERROR("Error initializing VRAM MM; %d\n", ret);
		वापस ret;
	पूर्ण

	vbox->fb_mtrr = arch_phys_wc_add(pci_resource_start(pdev, 0),
					 pci_resource_len(pdev, 0));
	वापस 0;
पूर्ण

व्योम vbox_mm_fini(काष्ठा vbox_निजी *vbox)
अणु
	arch_phys_wc_del(vbox->fb_mtrr);
पूर्ण
