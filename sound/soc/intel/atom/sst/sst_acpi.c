<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sst_acpi.c - SST (LPE) driver init file क्रम ACPI क्रमागतeration.
 *
 * Copyright (c) 2013, Intel Corporation.
 *
 *  Authors:	Ramesh Babu K V <Ramesh.Babu@पूर्णांकel.com>
 *  Authors:	Omair Mohammed Abdullah <omair.m.abdullah@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <यंत्र/platक्रमm_sst_audपन.स>
#समावेश <sound/core.h>
#समावेश <sound/पूर्णांकel-dsp-config.h>
#समावेश <sound/soc.h>
#समावेश <sound/compress_driver.h>
#समावेश <acpi/acbuffer.h>
#समावेश <acpi/platक्रमm/acenv.h>
#समावेश <acpi/platक्रमm/aclinux.h>
#समावेश <acpi/actypes.h>
#समावेश <acpi/acpi_bus.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/soc-acpi-पूर्णांकel-match.h>
#समावेश "../sst-mfld-platform.h"
#समावेश "../../common/soc-intel-quirks.h"
#समावेश "sst.h"

/* LPE viewpoपूर्णांक addresses */
#घोषणा SST_BYT_IRAM_PHY_START	0xff2c0000
#घोषणा SST_BYT_IRAM_PHY_END	0xff2d4000
#घोषणा SST_BYT_DRAM_PHY_START	0xff300000
#घोषणा SST_BYT_DRAM_PHY_END	0xff320000
#घोषणा SST_BYT_IMR_VIRT_START	0xc0000000 /* भव addr in LPE */
#घोषणा SST_BYT_IMR_VIRT_END	0xc01fffff
#घोषणा SST_BYT_SHIM_PHY_ADDR	0xff340000
#घोषणा SST_BYT_MBOX_PHY_ADDR	0xff344000
#घोषणा SST_BYT_DMA0_PHY_ADDR	0xff298000
#घोषणा SST_BYT_DMA1_PHY_ADDR	0xff29c000
#घोषणा SST_BYT_SSP0_PHY_ADDR	0xff2a0000
#घोषणा SST_BYT_SSP2_PHY_ADDR	0xff2a2000

#घोषणा BYT_FW_MOD_TABLE_OFFSET	0x80000
#घोषणा BYT_FW_MOD_TABLE_SIZE	0x100
#घोषणा BYT_FW_MOD_OFFSET	(BYT_FW_MOD_TABLE_OFFSET + BYT_FW_MOD_TABLE_SIZE)

अटल स्थिर काष्ठा sst_info byt_fwparse_info = अणु
	.use_elf	= false,
	.max_streams	= 25,
	.iram_start	= SST_BYT_IRAM_PHY_START,
	.iram_end	= SST_BYT_IRAM_PHY_END,
	.iram_use	= true,
	.dram_start	= SST_BYT_DRAM_PHY_START,
	.dram_end	= SST_BYT_DRAM_PHY_END,
	.dram_use	= true,
	.imr_start	= SST_BYT_IMR_VIRT_START,
	.imr_end	= SST_BYT_IMR_VIRT_END,
	.imr_use	= true,
	.mailbox_start	= SST_BYT_MBOX_PHY_ADDR,
	.num_probes	= 0,
	.lpe_viewpt_rqd  = true,
पूर्ण;

अटल स्थिर काष्ठा sst_ipc_info byt_ipc_info = अणु
	.ipc_offset = 0,
	.mbox_recv_off = 0x400,
पूर्ण;

अटल स्थिर काष्ठा sst_lib_dnld_info  byt_lib_dnld_info = अणु
	.mod_base           = SST_BYT_IMR_VIRT_START,
	.mod_end            = SST_BYT_IMR_VIRT_END,
	.mod_table_offset   = BYT_FW_MOD_TABLE_OFFSET,
	.mod_table_size     = BYT_FW_MOD_TABLE_SIZE,
	.mod_ddr_dnld       = false,
पूर्ण;

अटल स्थिर काष्ठा sst_res_info byt_rvp_res_info = अणु
	.shim_offset = 0x140000,
	.shim_size = 0x000100,
	.shim_phy_addr = SST_BYT_SHIM_PHY_ADDR,
	.ssp0_offset = 0xa0000,
	.ssp0_size = 0x1000,
	.dma0_offset = 0x98000,
	.dma0_size = 0x4000,
	.dma1_offset = 0x9c000,
	.dma1_size = 0x4000,
	.iram_offset = 0x0c0000,
	.iram_size = 0x14000,
	.dram_offset = 0x100000,
	.dram_size = 0x28000,
	.mbox_offset = 0x144000,
	.mbox_size = 0x1000,
	.acpi_lpe_res_index = 0,
	.acpi_ddr_index = 2,
	.acpi_ipc_irq_index = 5,
पूर्ण;

/* BYTCR has dअगरferent BIOS from BYT */
अटल स्थिर काष्ठा sst_res_info bytcr_res_info = अणु
	.shim_offset = 0x140000,
	.shim_size = 0x000100,
	.shim_phy_addr = SST_BYT_SHIM_PHY_ADDR,
	.ssp0_offset = 0xa0000,
	.ssp0_size = 0x1000,
	.dma0_offset = 0x98000,
	.dma0_size = 0x4000,
	.dma1_offset = 0x9c000,
	.dma1_size = 0x4000,
	.iram_offset = 0x0c0000,
	.iram_size = 0x14000,
	.dram_offset = 0x100000,
	.dram_size = 0x28000,
	.mbox_offset = 0x144000,
	.mbox_size = 0x1000,
	.acpi_lpe_res_index = 0,
	.acpi_ddr_index = 2,
	.acpi_ipc_irq_index = 0
पूर्ण;

अटल काष्ठा sst_platक्रमm_info byt_rvp_platक्रमm_data = अणु
	.probe_data = &byt_fwparse_info,
	.ipc_info = &byt_ipc_info,
	.lib_info = &byt_lib_dnld_info,
	.res_info = &byt_rvp_res_info,
	.platक्रमm = "sst-mfld-platform",
	.streams_lost_on_suspend = true,
पूर्ण;

/* Cherryview (Cherrytrail and Braswell) uses same mrfld dpcm fw as Baytrail,
 * so pdata is same as Baytrail, minus the streams_lost_on_suspend quirk.
 */
अटल काष्ठा sst_platक्रमm_info chv_platक्रमm_data = अणु
	.probe_data = &byt_fwparse_info,
	.ipc_info = &byt_ipc_info,
	.lib_info = &byt_lib_dnld_info,
	.res_info = &byt_rvp_res_info,
	.platक्रमm = "sst-mfld-platform",
पूर्ण;

अटल पूर्णांक sst_platक्रमm_get_resources(काष्ठा पूर्णांकel_sst_drv *ctx)
अणु
	काष्ठा resource *rsrc;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(ctx->dev);

	/* All ACPI resource request here */
	/* Get Shim addr */
	rsrc = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
					ctx->pdata->res_info->acpi_lpe_res_index);
	अगर (!rsrc) अणु
		dev_err(ctx->dev, "Invalid SHIM base from IFWI\n");
		वापस -EIO;
	पूर्ण
	dev_info(ctx->dev, "LPE base: %#x size:%#x", (अचिन्हित पूर्णांक) rsrc->start,
					(अचिन्हित पूर्णांक)resource_size(rsrc));

	ctx->iram_base = rsrc->start + ctx->pdata->res_info->iram_offset;
	ctx->iram_end =  ctx->iram_base + ctx->pdata->res_info->iram_size - 1;
	dev_info(ctx->dev, "IRAM base: %#x", ctx->iram_base);
	ctx->iram = devm_ioremap(ctx->dev, ctx->iram_base,
					 ctx->pdata->res_info->iram_size);
	अगर (!ctx->iram) अणु
		dev_err(ctx->dev, "unable to map IRAM\n");
		वापस -EIO;
	पूर्ण

	ctx->dram_base = rsrc->start + ctx->pdata->res_info->dram_offset;
	ctx->dram_end = ctx->dram_base + ctx->pdata->res_info->dram_size - 1;
	dev_info(ctx->dev, "DRAM base: %#x", ctx->dram_base);
	ctx->dram = devm_ioremap(ctx->dev, ctx->dram_base,
					 ctx->pdata->res_info->dram_size);
	अगर (!ctx->dram) अणु
		dev_err(ctx->dev, "unable to map DRAM\n");
		वापस -EIO;
	पूर्ण

	ctx->shim_phy_add = rsrc->start + ctx->pdata->res_info->shim_offset;
	dev_info(ctx->dev, "SHIM base: %#x", ctx->shim_phy_add);
	ctx->shim = devm_ioremap(ctx->dev, ctx->shim_phy_add,
					ctx->pdata->res_info->shim_size);
	अगर (!ctx->shim) अणु
		dev_err(ctx->dev, "unable to map SHIM\n");
		वापस -EIO;
	पूर्ण

	/* reassign physical address to LPE viewpoपूर्णांक address */
	ctx->shim_phy_add = ctx->pdata->res_info->shim_phy_addr;

	/* Get mailbox addr */
	ctx->mailbox_add = rsrc->start + ctx->pdata->res_info->mbox_offset;
	dev_info(ctx->dev, "Mailbox base: %#x", ctx->mailbox_add);
	ctx->mailbox = devm_ioremap(ctx->dev, ctx->mailbox_add,
					    ctx->pdata->res_info->mbox_size);
	अगर (!ctx->mailbox) अणु
		dev_err(ctx->dev, "unable to map mailbox\n");
		वापस -EIO;
	पूर्ण

	/* reassign physical address to LPE viewpoपूर्णांक address */
	ctx->mailbox_add = ctx->info.mailbox_start;

	rsrc = platक्रमm_get_resource(pdev, IORESOURCE_MEM,
					ctx->pdata->res_info->acpi_ddr_index);
	अगर (!rsrc) अणु
		dev_err(ctx->dev, "Invalid DDR base from IFWI\n");
		वापस -EIO;
	पूर्ण
	ctx->ddr_base = rsrc->start;
	ctx->ddr_end = rsrc->end;
	dev_info(ctx->dev, "DDR base: %#x", ctx->ddr_base);
	ctx->ddr = devm_ioremap(ctx->dev, ctx->ddr_base,
					resource_size(rsrc));
	अगर (!ctx->ddr) अणु
		dev_err(ctx->dev, "unable to map DDR\n");
		वापस -EIO;
	पूर्ण

	/* Find the IRQ */
	ctx->irq_num = platक्रमm_get_irq(pdev,
				ctx->pdata->res_info->acpi_ipc_irq_index);
	अगर (ctx->irq_num <= 0)
		वापस ctx->irq_num < 0 ? ctx->irq_num : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक sst_acpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret = 0;
	काष्ठा पूर्णांकel_sst_drv *ctx;
	स्थिर काष्ठा acpi_device_id *id;
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा platक्रमm_device *mdev;
	काष्ठा platक्रमm_device *plat_dev;
	काष्ठा sst_platक्रमm_info *pdata;
	अचिन्हित पूर्णांक dev_id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस -ENODEV;

	ret = snd_पूर्णांकel_acpi_dsp_driver_probe(dev, id->id);
	अगर (ret != SND_INTEL_DSP_DRIVER_ANY && ret != SND_INTEL_DSP_DRIVER_SST) अणु
		dev_dbg(dev, "SST ACPI driver not selected, aborting probe\n");
		वापस -ENODEV;
	पूर्ण

	dev_dbg(dev, "for %s\n", id->id);

	mach = (काष्ठा snd_soc_acpi_mach *)id->driver_data;
	mach = snd_soc_acpi_find_machine(mach);
	अगर (mach == शून्य) अणु
		dev_err(dev, "No matching machine driver found\n");
		वापस -ENODEV;
	पूर्ण

	अगर (soc_पूर्णांकel_is_byt())
		mach->pdata = &byt_rvp_platक्रमm_data;
	अन्यथा
		mach->pdata = &chv_platक्रमm_data;
	pdata = mach->pdata;

	ret = kstrtouपूर्णांक(id->id, 16, &dev_id);
	अगर (ret < 0) अणु
		dev_err(dev, "Unique device id conversion error: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "ACPI device id: %x\n", dev_id);

	ret = sst_alloc_drv_context(&ctx, dev, dev_id);
	अगर (ret < 0)
		वापस ret;

	अगर (soc_पूर्णांकel_is_byt_cr(pdev)) अणु
		/* override resource info */
		byt_rvp_platक्रमm_data.res_info = &bytcr_res_info;
	पूर्ण

	/* update machine parameters */
	mach->mach_params.acpi_ipc_irq_index =
		pdata->res_info->acpi_ipc_irq_index;

	plat_dev = platक्रमm_device_रेजिस्टर_data(dev, pdata->platक्रमm, -1,
						शून्य, 0);
	अगर (IS_ERR(plat_dev)) अणु
		dev_err(dev, "Failed to create machine device: %s\n",
			pdata->platक्रमm);
		वापस PTR_ERR(plat_dev);
	पूर्ण

	/*
	 * Create platक्रमm device क्रम sst machine driver,
	 * pass machine info as pdata
	 */
	mdev = platक्रमm_device_रेजिस्टर_data(dev, mach->drv_name, -1,
					(स्थिर व्योम *)mach, माप(*mach));
	अगर (IS_ERR(mdev)) अणु
		dev_err(dev, "Failed to create machine device: %s\n",
			mach->drv_name);
		वापस PTR_ERR(mdev);
	पूर्ण

	/* Fill sst platक्रमm data */
	ctx->pdata = pdata;
	म_नकल(ctx->firmware_name, mach->fw_filename);

	ret = sst_platक्रमm_get_resources(ctx);
	अगर (ret)
		वापस ret;

	ret = sst_context_init(ctx);
	अगर (ret < 0)
		वापस ret;

	sst_configure_runसमय_pm(ctx);
	platक्रमm_set_drvdata(pdev, ctx);
	वापस ret;
पूर्ण

/**
* sst_acpi_हटाओ - हटाओ function
*
* @pdev:	platक्रमm device काष्ठाure
*
* This function is called by OS when a device is unloaded
* This मुक्तs the पूर्णांकerrupt etc
*/
अटल पूर्णांक sst_acpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx;

	ctx = platक्रमm_get_drvdata(pdev);
	sst_context_cleanup(ctx);
	platक्रमm_set_drvdata(pdev, शून्य);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id sst_acpi_ids[] = अणु
	अणु "80860F28", (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_baytrail_machinesपूर्ण,
	अणु "808622A8", (अचिन्हित दीर्घ)&snd_soc_acpi_पूर्णांकel_cherrytrail_machinesपूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, sst_acpi_ids);

अटल काष्ठा platक्रमm_driver sst_acpi_driver = अणु
	.driver = अणु
		.name			= "intel_sst_acpi",
		.acpi_match_table	= ACPI_PTR(sst_acpi_ids),
		.pm			= &पूर्णांकel_sst_pm,
	पूर्ण,
	.probe	= sst_acpi_probe,
	.हटाओ	= sst_acpi_हटाओ,
पूर्ण;

module_platक्रमm_driver(sst_acpi_driver);

MODULE_DESCRIPTION("Intel (R) SST(R) Audio Engine ACPI Driver");
MODULE_AUTHOR("Ramesh Babu K V");
MODULE_AUTHOR("Omair Mohammed Abdullah");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("sst");
