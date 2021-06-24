<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2007-2011, Intel Corporation.
 * All Rights Reserved.
 * Copyright (c) 2008, Tungsten Graphics, Inc. Cedar Park, TX., USA.
 * All Rights Reserved.
 *
 **************************************************************************/

#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/set_memory.h>

#समावेश <acpi/video.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_pciids.h>
#समावेश <drm/drm_vblank.h>

#समावेश "framebuffer.h"
#समावेश "intel_bios.h"
#समावेश "mid_bios.h"
#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"
#समावेश "psb_reg.h"

अटल स्थिर काष्ठा drm_driver driver;
अटल पूर्णांक psb_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);

/*
 * The table below contains a mapping of the PCI venकरोr ID and the PCI Device ID
 * to the dअगरferent groups of PowerVR 5-series chip designs
 *
 * 0x8086 = Intel Corporation
 *
 * PowerVR SGX535    - Poulsbo    - Intel GMA 500, Intel Atom Z5xx
 * PowerVR SGX535    - Moorestown - Intel GMA 600
 * PowerVR SGX535    - Oaktrail   - Intel GMA 600, Intel Atom Z6xx, E6xx
 * PowerVR SGX545    - Cedartrail - Intel GMA 3600, Intel Atom D2500, N2600
 * PowerVR SGX545    - Cedartrail - Intel GMA 3650, Intel Atom D2550, D2700,
 *                                  N2800
 */
अटल स्थिर काष्ठा pci_device_id pciidlist[] = अणु
	/* Poulsbo */
	अणु 0x8086, 0x8108, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &psb_chip_ops पूर्ण,
	अणु 0x8086, 0x8109, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &psb_chip_ops पूर्ण,
	/* Oak Trail */
	अणु 0x8086, 0x4100, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &oaktrail_chip_ops पूर्ण,
	अणु 0x8086, 0x4101, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &oaktrail_chip_ops पूर्ण,
	अणु 0x8086, 0x4102, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &oaktrail_chip_ops पूर्ण,
	अणु 0x8086, 0x4103, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &oaktrail_chip_ops पूर्ण,
	अणु 0x8086, 0x4104, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &oaktrail_chip_ops पूर्ण,
	अणु 0x8086, 0x4105, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &oaktrail_chip_ops पूर्ण,
	अणु 0x8086, 0x4106, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &oaktrail_chip_ops पूर्ण,
	अणु 0x8086, 0x4107, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &oaktrail_chip_ops पूर्ण,
	अणु 0x8086, 0x4108, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &oaktrail_chip_ops पूर्ण,
	/* Cedar Trail */
	अणु 0x8086, 0x0be0, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0be1, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0be2, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0be3, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0be4, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0be5, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0be6, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0be7, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0be8, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0be9, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0bea, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0beb, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0bec, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0bed, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0bee, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0x8086, 0x0bef, PCI_ANY_ID, PCI_ANY_ID, 0, 0, (दीर्घ) &cdv_chip_ops पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pciidlist);

/*
 * Standard IOCTLs.
 */
अटल स्थिर काष्ठा drm_ioctl_desc psb_ioctls[] = अणु
पूर्ण;

/**
 *	psb_spank		-	reset the 2D engine
 *	@dev_priv: our PSB DRM device
 *
 *	Soft reset the graphics engine and then reload the necessary रेजिस्टरs.
 */
व्योम psb_spank(काष्ठा drm_psb_निजी *dev_priv)
अणु
	PSB_WSGX32(_PSB_CS_RESET_BIF_RESET | _PSB_CS_RESET_DPM_RESET |
		_PSB_CS_RESET_TA_RESET | _PSB_CS_RESET_USE_RESET |
		_PSB_CS_RESET_ISP_RESET | _PSB_CS_RESET_TSP_RESET |
		_PSB_CS_RESET_TWOD_RESET, PSB_CR_SOFT_RESET);
	PSB_RSGX32(PSB_CR_SOFT_RESET);

	msleep(1);

	PSB_WSGX32(0, PSB_CR_SOFT_RESET);
	wmb();
	PSB_WSGX32(PSB_RSGX32(PSB_CR_BIF_CTRL) | _PSB_CB_CTRL_CLEAR_FAULT,
		   PSB_CR_BIF_CTRL);
	wmb();
	(व्योम) PSB_RSGX32(PSB_CR_BIF_CTRL);

	msleep(1);
	PSB_WSGX32(PSB_RSGX32(PSB_CR_BIF_CTRL) & ~_PSB_CB_CTRL_CLEAR_FAULT,
		   PSB_CR_BIF_CTRL);
	(व्योम) PSB_RSGX32(PSB_CR_BIF_CTRL);
	PSB_WSGX32(dev_priv->gtt.gatt_start, PSB_CR_BIF_TWOD_REQ_BASE);
पूर्ण

अटल पूर्णांक psb_करो_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_gtt *pg = &dev_priv->gtt;

	uपूर्णांक32_t stolen_gtt;

	अगर (pg->mmu_gatt_start & 0x0FFFFFFF) अणु
		dev_err(dev->dev, "Gatt must be 256M aligned. This is a bug.\n");
		वापस -EINVAL;
	पूर्ण

	stolen_gtt = (pg->stolen_size >> PAGE_SHIFT) * 4;
	stolen_gtt = (stolen_gtt + PAGE_SIZE - 1) >> PAGE_SHIFT;
	stolen_gtt = (stolen_gtt < pg->gtt_pages) ? stolen_gtt : pg->gtt_pages;

	dev_priv->gatt_मुक्त_offset = pg->mmu_gatt_start +
	    (stolen_gtt << PAGE_SHIFT) * 1024;

	spin_lock_init(&dev_priv->irqmask_lock);

	PSB_WSGX32(0x00000000, PSB_CR_BIF_BANK0);
	PSB_WSGX32(0x00000000, PSB_CR_BIF_BANK1);
	PSB_RSGX32(PSB_CR_BIF_BANK1);

	/* Do not bypass any MMU access, let them pagefault instead */
	PSB_WSGX32((PSB_RSGX32(PSB_CR_BIF_CTRL) & ~_PSB_MMU_ER_MASK),
		   PSB_CR_BIF_CTRL);
	PSB_RSGX32(PSB_CR_BIF_CTRL);

	psb_spank(dev_priv);

	/* mmu_gatt ?? */
	PSB_WSGX32(pg->gatt_start, PSB_CR_BIF_TWOD_REQ_BASE);
	PSB_RSGX32(PSB_CR_BIF_TWOD_REQ_BASE); /* Post */

	वापस 0;
पूर्ण

अटल व्योम psb_driver_unload(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	/* TODO: Kill vblank etc here */

	अगर (dev_priv) अणु
		अगर (dev_priv->backlight_device)
			gma_backlight_निकास(dev);
		psb_modeset_cleanup(dev);

		अगर (dev_priv->ops->chip_tearकरोwn)
			dev_priv->ops->chip_tearकरोwn(dev);

		psb_पूर्णांकel_opregion_fini(dev);

		अगर (dev_priv->pf_pd) अणु
			psb_mmu_मुक्त_pagedir(dev_priv->pf_pd);
			dev_priv->pf_pd = शून्य;
		पूर्ण
		अगर (dev_priv->mmu) अणु
			काष्ठा psb_gtt *pg = &dev_priv->gtt;

			करोwn_पढ़ो(&pg->sem);
			psb_mmu_हटाओ_pfn_sequence(
				psb_mmu_get_शेष_pd
				(dev_priv->mmu),
				pg->mmu_gatt_start,
				dev_priv->vram_stolen_size >> PAGE_SHIFT);
			up_पढ़ो(&pg->sem);
			psb_mmu_driver_takeकरोwn(dev_priv->mmu);
			dev_priv->mmu = शून्य;
		पूर्ण
		psb_gtt_takeकरोwn(dev);
		अगर (dev_priv->scratch_page) अणु
			set_pages_wb(dev_priv->scratch_page, 1);
			__मुक्त_page(dev_priv->scratch_page);
			dev_priv->scratch_page = शून्य;
		पूर्ण
		अगर (dev_priv->vdc_reg) अणु
			iounmap(dev_priv->vdc_reg);
			dev_priv->vdc_reg = शून्य;
		पूर्ण
		अगर (dev_priv->sgx_reg) अणु
			iounmap(dev_priv->sgx_reg);
			dev_priv->sgx_reg = शून्य;
		पूर्ण
		अगर (dev_priv->aux_reg) अणु
			iounmap(dev_priv->aux_reg);
			dev_priv->aux_reg = शून्य;
		पूर्ण
		pci_dev_put(dev_priv->aux_pdev);
		pci_dev_put(dev_priv->lpc_pdev);

		/* Destroy VBT data */
		psb_पूर्णांकel_destroy_bios(dev);

		kमुक्त(dev_priv);
		dev->dev_निजी = शून्य;
	पूर्ण
	gma_घातer_uninit(dev);
पूर्ण

अटल पूर्णांक psb_driver_load(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	काष्ठा drm_psb_निजी *dev_priv;
	अचिन्हित दीर्घ resource_start, resource_len;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret = -ENOMEM;
	काष्ठा drm_connector *connector;
	काष्ठा gma_encoder *gma_encoder;
	काष्ठा psb_gtt *pg;

	/* allocating and initializing driver निजी data */
	dev_priv = kzalloc(माप(*dev_priv), GFP_KERNEL);
	अगर (dev_priv == शून्य)
		वापस -ENOMEM;

	dev_priv->ops = (काष्ठा psb_ops *)flags;
	dev_priv->dev = dev;
	dev->dev_निजी = (व्योम *) dev_priv;

	pg = &dev_priv->gtt;

	pci_set_master(pdev);

	dev_priv->num_pipe = dev_priv->ops->pipes;

	resource_start = pci_resource_start(pdev, PSB_MMIO_RESOURCE);

	dev_priv->vdc_reg =
	    ioremap(resource_start + PSB_VDC_OFFSET, PSB_VDC_SIZE);
	अगर (!dev_priv->vdc_reg)
		जाओ out_err;

	dev_priv->sgx_reg = ioremap(resource_start + dev_priv->ops->sgx_offset,
							PSB_SGX_SIZE);
	अगर (!dev_priv->sgx_reg)
		जाओ out_err;

	अगर (IS_MRST(dev)) अणु
		पूर्णांक करोमुख्य = pci_करोमुख्य_nr(pdev->bus);

		dev_priv->aux_pdev =
			pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0,
						    PCI_DEVFN(3, 0));

		अगर (dev_priv->aux_pdev) अणु
			resource_start = pci_resource_start(dev_priv->aux_pdev,
							    PSB_AUX_RESOURCE);
			resource_len = pci_resource_len(dev_priv->aux_pdev,
							PSB_AUX_RESOURCE);
			dev_priv->aux_reg = ioremap(resource_start,
							    resource_len);
			अगर (!dev_priv->aux_reg)
				जाओ out_err;

			DRM_DEBUG_KMS("Found aux vdc");
		पूर्ण अन्यथा अणु
			/* Couldn't find the aux vdc so map to primary vdc */
			dev_priv->aux_reg = dev_priv->vdc_reg;
			DRM_DEBUG_KMS("Couldn't find aux pci device");
		पूर्ण
		dev_priv->gmbus_reg = dev_priv->aux_reg;

		dev_priv->lpc_pdev =
			pci_get_करोमुख्य_bus_and_slot(करोमुख्य, 0,
						    PCI_DEVFN(31, 0));
		अगर (dev_priv->lpc_pdev) अणु
			pci_पढ़ो_config_word(dev_priv->lpc_pdev, PSB_LPC_GBA,
				&dev_priv->lpc_gpio_base);
			pci_ग_लिखो_config_dword(dev_priv->lpc_pdev, PSB_LPC_GBA,
				(u32)dev_priv->lpc_gpio_base | (1L<<31));
			pci_पढ़ो_config_word(dev_priv->lpc_pdev, PSB_LPC_GBA,
				&dev_priv->lpc_gpio_base);
			dev_priv->lpc_gpio_base &= 0xffc0;
			अगर (dev_priv->lpc_gpio_base)
				DRM_DEBUG_KMS("Found LPC GPIO at 0x%04x\n",
						dev_priv->lpc_gpio_base);
			अन्यथा अणु
				pci_dev_put(dev_priv->lpc_pdev);
				dev_priv->lpc_pdev = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_priv->gmbus_reg = dev_priv->vdc_reg;
	पूर्ण

	psb_पूर्णांकel_opregion_setup(dev);

	ret = dev_priv->ops->chip_setup(dev);
	अगर (ret)
		जाओ out_err;

	/* Init OSPM support */
	gma_घातer_init(dev);

	ret = -ENOMEM;

	dev_priv->scratch_page = alloc_page(GFP_DMA32 | __GFP_ZERO);
	अगर (!dev_priv->scratch_page)
		जाओ out_err;

	set_pages_uc(dev_priv->scratch_page, 1);

	ret = psb_gtt_init(dev, 0);
	अगर (ret)
		जाओ out_err;

	ret = -ENOMEM;

	dev_priv->mmu = psb_mmu_driver_init(dev, 1, 0, शून्य);
	अगर (!dev_priv->mmu)
		जाओ out_err;

	dev_priv->pf_pd = psb_mmu_alloc_pd(dev_priv->mmu, 1, 0);
	अगर (!dev_priv->pf_pd)
		जाओ out_err;

	ret = psb_करो_init(dev);
	अगर (ret)
		वापस ret;

	/* Add stolen memory to SGX MMU */
	करोwn_पढ़ो(&pg->sem);
	ret = psb_mmu_insert_pfn_sequence(psb_mmu_get_शेष_pd(dev_priv->mmu),
					  dev_priv->stolen_base >> PAGE_SHIFT,
					  pg->gatt_start,
					  pg->stolen_size >> PAGE_SHIFT, 0);
	up_पढ़ो(&pg->sem);

	psb_mmu_set_pd_context(psb_mmu_get_शेष_pd(dev_priv->mmu), 0);
	psb_mmu_set_pd_context(dev_priv->pf_pd, 1);

	PSB_WSGX32(0x20000000, PSB_CR_PDS_EXEC_BASE);
	PSB_WSGX32(0x30000000, PSB_CR_BIF_3D_REQ_BASE);

	acpi_video_रेजिस्टर();

	/* Setup vertical blanking handling */
	ret = drm_vblank_init(dev, dev_priv->num_pipe);
	अगर (ret)
		जाओ out_err;

	/*
	 * Install पूर्णांकerrupt handlers prior to घातering off SGX or अन्यथा we will
	 * crash.
	 */
	dev_priv->vdc_irq_mask = 0;
	dev_priv->pipestat[0] = 0;
	dev_priv->pipestat[1] = 0;
	dev_priv->pipestat[2] = 0;
	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);
	PSB_WVDC32(0xFFFFFFFF, PSB_HWSTAM);
	PSB_WVDC32(0x00000000, PSB_INT_ENABLE_R);
	PSB_WVDC32(0xFFFFFFFF, PSB_INT_MASK_R);
	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);

	drm_irq_install(dev, pdev->irq);

	dev->max_vblank_count = 0xffffff; /* only 24 bits of frame count */

	psb_modeset_init(dev);
	psb_fbdev_init(dev);
	drm_kms_helper_poll_init(dev);

	/* Only add backlight support अगर we have LVDS output */
	list_क्रम_each_entry(connector, &dev->mode_config.connector_list,
			    head) अणु
		gma_encoder = gma_attached_encoder(connector);

		चयन (gma_encoder->type) अणु
		हाल INTEL_OUTPUT_LVDS:
		हाल INTEL_OUTPUT_MIPI:
			ret = gma_backlight_init(dev);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस ret;
	psb_पूर्णांकel_opregion_enable_asle(dev);
#अगर 0
	/* Enable runसमय pm at last */
	pm_runसमय_enable(dev->dev);
	pm_runसमय_set_active(dev->dev);
#पूर्ण_अगर
	/* Intel drm driver load is करोne, जारी करोing pvr load */
	वापस 0;
out_err:
	psb_driver_unload(dev);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम get_brightness(काष्ठा backlight_device *bd)
अणु
#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	अगर (bd) अणु
		bd->props.brightness = bd->ops->get_brightness(bd);
		backlight_update_status(bd);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल दीर्घ psb_unlocked_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा drm_device *dev = file_priv->minor->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अटल अचिन्हित पूर्णांक runसमय_allowed;

	अगर (runसमय_allowed == 1 && dev_priv->is_lvds_on) अणु
		runसमय_allowed++;
		pm_runसमय_allow(dev->dev);
		dev_priv->rpm_enabled = 1;
	पूर्ण
	वापस drm_ioctl(filp, cmd, arg);
	/* FIXME: करो we need to wrap the other side of this */
पूर्ण

अटल पूर्णांक psb_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा drm_device *dev;
	पूर्णांक ret;

	ret = pci_enable_device(pdev);
	अगर (ret)
		वापस ret;

	dev = drm_dev_alloc(&driver, &pdev->dev);
	अगर (IS_ERR(dev)) अणु
		ret = PTR_ERR(dev);
		जाओ err_pci_disable_device;
	पूर्ण

	pci_set_drvdata(pdev, dev);

	ret = psb_driver_load(dev, ent->driver_data);
	अगर (ret)
		जाओ err_drm_dev_put;

	ret = drm_dev_रेजिस्टर(dev, ent->driver_data);
	अगर (ret)
		जाओ err_psb_driver_unload;

	वापस 0;

err_psb_driver_unload:
	psb_driver_unload(dev);
err_drm_dev_put:
	drm_dev_put(dev);
err_pci_disable_device:
	pci_disable_device(pdev);
	वापस ret;
पूर्ण

अटल व्योम psb_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा drm_device *dev = pci_get_drvdata(pdev);

	drm_dev_unरेजिस्टर(dev);
	psb_driver_unload(dev);
	drm_dev_put(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops psb_pm_ops = अणु
	.resume = gma_घातer_resume,
	.suspend = gma_घातer_suspend,
	.thaw = gma_घातer_thaw,
	.मुक्तze = gma_घातer_मुक्तze,
	.restore = gma_घातer_restore,
	.runसमय_suspend = psb_runसमय_suspend,
	.runसमय_resume = psb_runसमय_resume,
	.runसमय_idle = psb_runसमय_idle,
पूर्ण;

अटल स्थिर काष्ठा file_operations psb_gem_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = drm_खोलो,
	.release = drm_release,
	.unlocked_ioctl = psb_unlocked_ioctl,
	.compat_ioctl = drm_compat_ioctl,
	.mmap = drm_gem_mmap,
	.poll = drm_poll,
	.पढ़ो = drm_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा drm_driver driver = अणु
	.driver_features = DRIVER_MODESET | DRIVER_GEM,
	.lastबंद = drm_fb_helper_lastबंद,

	.num_ioctls = ARRAY_SIZE(psb_ioctls),
	.irq_preinstall = psb_irq_preinstall,
	.irq_postinstall = psb_irq_postinstall,
	.irq_uninstall = psb_irq_uninstall,
	.irq_handler = psb_irq_handler,

	.dumb_create = psb_gem_dumb_create,
	.ioctls = psb_ioctls,
	.fops = &psb_gem_fops,
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
	.patchlevel = DRIVER_PATCHLEVEL
पूर्ण;

अटल काष्ठा pci_driver psb_pci_driver = अणु
	.name = DRIVER_NAME,
	.id_table = pciidlist,
	.probe = psb_pci_probe,
	.हटाओ = psb_pci_हटाओ,
	.driver.pm = &psb_pm_ops,
पूर्ण;

अटल पूर्णांक __init psb_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&psb_pci_driver);
पूर्ण

अटल व्योम __निकास psb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&psb_pci_driver);
पूर्ण

late_initcall(psb_init);
module_निकास(psb_निकास);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
