<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sst_pci.c - SST (LPE) driver init file क्रम pci क्रमागतeration.
 *
 *  Copyright (C) 2008-14	Intel Corp
 *  Authors:	Vinod Koul <vinod.koul@पूर्णांकel.com>
 *		Harsha Priya <priya.harsha@पूर्णांकel.com>
 *		Dharageswari R <dharageswari.r@पूर्णांकel.com>
 *		KP Jeeja <jeeja.kp@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/fs.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/platक्रमm_sst_audपन.स>
#समावेश "../sst-mfld-platform.h"
#समावेश "sst.h"

अटल पूर्णांक sst_platक्रमm_get_resources(काष्ठा पूर्णांकel_sst_drv *ctx)
अणु
	पूर्णांक ddr_base, ret = 0;
	काष्ठा pci_dev *pci = ctx->pci;

	ret = pci_request_regions(pci, SST_DRV_NAME);
	अगर (ret)
		वापस ret;

	/* map रेजिस्टरs */
	/* DDR base */
	अगर (ctx->dev_id == SST_MRFLD_PCI_ID) अणु
		ctx->ddr_base = pci_resource_start(pci, 0);
		/* check that the relocated IMR base matches with FW Binary */
		ddr_base = relocate_imr_addr_mrfld(ctx->ddr_base);
		अगर (!ctx->pdata->lib_info) अणु
			dev_err(ctx->dev, "lib_info pointer NULL\n");
			ret = -EINVAL;
			जाओ करो_release_regions;
		पूर्ण
		अगर (ddr_base != ctx->pdata->lib_info->mod_base) अणु
			dev_err(ctx->dev,
					"FW LSP DDR BASE does not match with IFWI\n");
			ret = -EINVAL;
			जाओ करो_release_regions;
		पूर्ण
		ctx->ddr_end = pci_resource_end(pci, 0);

		ctx->ddr = pcim_iomap(pci, 0,
					pci_resource_len(pci, 0));
		अगर (!ctx->ddr) अणु
			ret = -EINVAL;
			जाओ करो_release_regions;
		पूर्ण
		dev_dbg(ctx->dev, "sst: DDR Ptr %p\n", ctx->ddr);
	पूर्ण अन्यथा अणु
		ctx->ddr = शून्य;
	पूर्ण
	/* SHIM */
	ctx->shim_phy_add = pci_resource_start(pci, 1);
	ctx->shim = pcim_iomap(pci, 1, pci_resource_len(pci, 1));
	अगर (!ctx->shim) अणु
		ret = -EINVAL;
		जाओ करो_release_regions;
	पूर्ण
	dev_dbg(ctx->dev, "SST Shim Ptr %p\n", ctx->shim);

	/* Shared SRAM */
	ctx->mailbox_add = pci_resource_start(pci, 2);
	ctx->mailbox = pcim_iomap(pci, 2, pci_resource_len(pci, 2));
	अगर (!ctx->mailbox) अणु
		ret = -EINVAL;
		जाओ करो_release_regions;
	पूर्ण
	dev_dbg(ctx->dev, "SRAM Ptr %p\n", ctx->mailbox);

	/* IRAM */
	ctx->iram_end = pci_resource_end(pci, 3);
	ctx->iram_base = pci_resource_start(pci, 3);
	ctx->iram = pcim_iomap(pci, 3, pci_resource_len(pci, 3));
	अगर (!ctx->iram) अणु
		ret = -EINVAL;
		जाओ करो_release_regions;
	पूर्ण
	dev_dbg(ctx->dev, "IRAM Ptr %p\n", ctx->iram);

	/* DRAM */
	ctx->dram_end = pci_resource_end(pci, 4);
	ctx->dram_base = pci_resource_start(pci, 4);
	ctx->dram = pcim_iomap(pci, 4, pci_resource_len(pci, 4));
	अगर (!ctx->dram) अणु
		ret = -EINVAL;
		जाओ करो_release_regions;
	पूर्ण
	dev_dbg(ctx->dev, "DRAM Ptr %p\n", ctx->dram);
करो_release_regions:
	pci_release_regions(pci);
	वापस ret;
पूर्ण

/*
 * पूर्णांकel_sst_probe - PCI probe function
 *
 * @pci:	PCI device काष्ठाure
 * @pci_id: PCI device ID काष्ठाure
 *
 */
अटल पूर्णांक पूर्णांकel_sst_probe(काष्ठा pci_dev *pci,
			स्थिर काष्ठा pci_device_id *pci_id)
अणु
	पूर्णांक ret = 0;
	काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx;
	काष्ठा sst_platक्रमm_info *sst_pdata = pci->dev.platक्रमm_data;

	dev_dbg(&pci->dev, "Probe for DID %x\n", pci->device);
	ret = sst_alloc_drv_context(&sst_drv_ctx, &pci->dev, pci->device);
	अगर (ret < 0)
		वापस ret;

	sst_drv_ctx->pdata = sst_pdata;
	sst_drv_ctx->irq_num = pci->irq;
	snम_लिखो(sst_drv_ctx->firmware_name, माप(sst_drv_ctx->firmware_name),
			"%s%04x%s", "fw_sst_",
			sst_drv_ctx->dev_id, ".bin");

	ret = sst_context_init(sst_drv_ctx);
	अगर (ret < 0)
		वापस ret;

	/* Init the device */
	ret = pcim_enable_device(pci);
	अगर (ret) अणु
		dev_err(sst_drv_ctx->dev,
			"device can't be enabled. Returned err: %d\n", ret);
		जाओ करो_मुक्त_drv_ctx;
	पूर्ण
	sst_drv_ctx->pci = pci_dev_get(pci);
	ret = sst_platक्रमm_get_resources(sst_drv_ctx);
	अगर (ret < 0)
		जाओ करो_मुक्त_drv_ctx;

	pci_set_drvdata(pci, sst_drv_ctx);
	sst_configure_runसमय_pm(sst_drv_ctx);

	वापस ret;

करो_मुक्त_drv_ctx:
	sst_context_cleanup(sst_drv_ctx);
	dev_err(sst_drv_ctx->dev, "Probe failed with %d\n", ret);
	वापस ret;
पूर्ण

/**
 * पूर्णांकel_sst_हटाओ - PCI हटाओ function
 *
 * @pci:	PCI device काष्ठाure
 *
 * This function is called by OS when a device is unloaded
 * This मुक्तs the पूर्णांकerrupt etc
 */
अटल व्योम पूर्णांकel_sst_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा पूर्णांकel_sst_drv *sst_drv_ctx = pci_get_drvdata(pci);

	sst_context_cleanup(sst_drv_ctx);
	pci_dev_put(sst_drv_ctx->pci);
	pci_release_regions(pci);
	pci_set_drvdata(pci, शून्य);
पूर्ण

/* PCI Routines */
अटल स्थिर काष्ठा pci_device_id पूर्णांकel_sst_ids[] = अणु
	अणु PCI_VDEVICE(INTEL, SST_MRFLD_PCI_ID), 0पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा pci_driver sst_driver = अणु
	.name = SST_DRV_NAME,
	.id_table = पूर्णांकel_sst_ids,
	.probe = पूर्णांकel_sst_probe,
	.हटाओ = पूर्णांकel_sst_हटाओ,
#अगर_घोषित CONFIG_PM
	.driver = अणु
		.pm = &पूर्णांकel_sst_pm,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

module_pci_driver(sst_driver);

MODULE_DESCRIPTION("Intel (R) SST(R) Audio Engine PCI Driver");
MODULE_AUTHOR("Vinod Koul <vinod.koul@intel.com>");
MODULE_AUTHOR("Harsha Priya <priya.harsha@intel.com>");
MODULE_AUTHOR("Dharageswari R <dharageswari.r@intel.com>");
MODULE_AUTHOR("KP Jeeja <jeeja.kp@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("sst");
