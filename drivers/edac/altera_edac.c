<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2017-2018, Intel Corporation. All rights reserved
 *  Copyright Altera Corporation (C) 2014-2016. All rights reserved.
 *  Copyright 2011-2012 Calxeda, Inc.
 */

#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/edac.h>
#समावेश <linux/firmware/पूर्णांकel/stratix10-smc.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/altera-sysmgr.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#समावेश "altera_edac.h"
#समावेश "edac_module.h"

#घोषणा EDAC_MOD_STR		"altera_edac"
#घोषणा EDAC_DEVICE		"Altera"

#अगर_घोषित CONFIG_EDAC_ALTERA_SDRAM
अटल स्थिर काष्ठा altr_sdram_prv_data c5_data = अणु
	.ecc_ctrl_offset    = CV_CTLCFG_OFST,
	.ecc_ctl_en_mask    = CV_CTLCFG_ECC_AUTO_EN,
	.ecc_stat_offset    = CV_DRAMSTS_OFST,
	.ecc_stat_ce_mask   = CV_DRAMSTS_SBEERR,
	.ecc_stat_ue_mask   = CV_DRAMSTS_DBEERR,
	.ecc_saddr_offset   = CV_ERRADDR_OFST,
	.ecc_daddr_offset   = CV_ERRADDR_OFST,
	.ecc_cecnt_offset   = CV_SBECOUNT_OFST,
	.ecc_uecnt_offset   = CV_DBECOUNT_OFST,
	.ecc_irq_en_offset  = CV_DRAMINTR_OFST,
	.ecc_irq_en_mask    = CV_DRAMINTR_INTREN,
	.ecc_irq_clr_offset = CV_DRAMINTR_OFST,
	.ecc_irq_clr_mask   = (CV_DRAMINTR_INTRCLR | CV_DRAMINTR_INTREN),
	.ecc_cnt_rst_offset = CV_DRAMINTR_OFST,
	.ecc_cnt_rst_mask   = CV_DRAMINTR_INTRCLR,
	.ce_ue_trgr_offset  = CV_CTLCFG_OFST,
	.ce_set_mask        = CV_CTLCFG_GEN_SB_ERR,
	.ue_set_mask        = CV_CTLCFG_GEN_DB_ERR,
पूर्ण;

अटल स्थिर काष्ठा altr_sdram_prv_data a10_data = अणु
	.ecc_ctrl_offset    = A10_ECCCTRL1_OFST,
	.ecc_ctl_en_mask    = A10_ECCCTRL1_ECC_EN,
	.ecc_stat_offset    = A10_INTSTAT_OFST,
	.ecc_stat_ce_mask   = A10_INTSTAT_SBEERR,
	.ecc_stat_ue_mask   = A10_INTSTAT_DBEERR,
	.ecc_saddr_offset   = A10_SERRADDR_OFST,
	.ecc_daddr_offset   = A10_DERRADDR_OFST,
	.ecc_irq_en_offset  = A10_ERRINTEN_OFST,
	.ecc_irq_en_mask    = A10_ECC_IRQ_EN_MASK,
	.ecc_irq_clr_offset = A10_INTSTAT_OFST,
	.ecc_irq_clr_mask   = (A10_INTSTAT_SBEERR | A10_INTSTAT_DBEERR),
	.ecc_cnt_rst_offset = A10_ECCCTRL1_OFST,
	.ecc_cnt_rst_mask   = A10_ECC_CNT_RESET_MASK,
	.ce_ue_trgr_offset  = A10_DIAGINTTEST_OFST,
	.ce_set_mask        = A10_DIAGINT_TSERRA_MASK,
	.ue_set_mask        = A10_DIAGINT_TDERRA_MASK,
पूर्ण;

/*********************** EDAC Memory Controller Functions ****************/

/* The SDRAM controller uses the EDAC Memory Controller framework.       */

अटल irqवापस_t altr_sdram_mc_err_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mem_ctl_info *mci = dev_id;
	काष्ठा altr_sdram_mc_data *drvdata = mci->pvt_info;
	स्थिर काष्ठा altr_sdram_prv_data *priv = drvdata->data;
	u32 status, err_count = 1, err_addr;

	regmap_पढ़ो(drvdata->mc_vbase, priv->ecc_stat_offset, &status);

	अगर (status & priv->ecc_stat_ue_mask) अणु
		regmap_पढ़ो(drvdata->mc_vbase, priv->ecc_daddr_offset,
			    &err_addr);
		अगर (priv->ecc_uecnt_offset)
			regmap_पढ़ो(drvdata->mc_vbase, priv->ecc_uecnt_offset,
				    &err_count);
		panic("\nEDAC: [%d Uncorrectable errors @ 0x%08X]\n",
		      err_count, err_addr);
	पूर्ण
	अगर (status & priv->ecc_stat_ce_mask) अणु
		regmap_पढ़ो(drvdata->mc_vbase, priv->ecc_saddr_offset,
			    &err_addr);
		अगर (priv->ecc_uecnt_offset)
			regmap_पढ़ो(drvdata->mc_vbase,  priv->ecc_cecnt_offset,
				    &err_count);
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, err_count,
				     err_addr >> PAGE_SHIFT,
				     err_addr & ~PAGE_MASK, 0,
				     0, 0, -1, mci->ctl_name, "");
		/* Clear IRQ to resume */
		regmap_ग_लिखो(drvdata->mc_vbase,	priv->ecc_irq_clr_offset,
			     priv->ecc_irq_clr_mask);

		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल sमाप_प्रकार altr_sdr_mc_err_inject_ग_लिखो(काष्ठा file *file,
					    स्थिर अक्षर __user *data,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mem_ctl_info *mci = file->निजी_data;
	काष्ठा altr_sdram_mc_data *drvdata = mci->pvt_info;
	स्थिर काष्ठा altr_sdram_prv_data *priv = drvdata->data;
	u32 *ptemp;
	dma_addr_t dma_handle;
	u32 reg, पढ़ो_reg;

	ptemp = dma_alloc_coherent(mci->pdev, 16, &dma_handle, GFP_KERNEL);
	अगर (!ptemp) अणु
		dma_मुक्त_coherent(mci->pdev, 16, ptemp, dma_handle);
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Inject: Buffer Allocation error\n");
		वापस -ENOMEM;
	पूर्ण

	regmap_पढ़ो(drvdata->mc_vbase, priv->ce_ue_trgr_offset,
		    &पढ़ो_reg);
	पढ़ो_reg &= ~(priv->ce_set_mask | priv->ue_set_mask);

	/* Error are injected by writing a word जबतक the SBE or DBE
	 * bit in the CTLCFG रेजिस्टर is set. Reading the word will
	 * trigger the SBE or DBE error and the corresponding IRQ.
	 */
	अगर (count == 3) अणु
		edac_prपूर्णांकk(KERN_ALERT, EDAC_MC,
			    "Inject Double bit error\n");
		local_irq_disable();
		regmap_ग_लिखो(drvdata->mc_vbase, priv->ce_ue_trgr_offset,
			     (पढ़ो_reg | priv->ue_set_mask));
		local_irq_enable();
	पूर्ण अन्यथा अणु
		edac_prपूर्णांकk(KERN_ALERT, EDAC_MC,
			    "Inject Single bit error\n");
		local_irq_disable();
		regmap_ग_लिखो(drvdata->mc_vbase,	priv->ce_ue_trgr_offset,
			     (पढ़ो_reg | priv->ce_set_mask));
		local_irq_enable();
	पूर्ण

	ptemp[0] = 0x5A5A5A5A;
	ptemp[1] = 0xA5A5A5A5;

	/* Clear the error injection bits */
	regmap_ग_लिखो(drvdata->mc_vbase,	priv->ce_ue_trgr_offset, पढ़ो_reg);
	/* Ensure it has been written out */
	wmb();

	/*
	 * To trigger the error, we need to पढ़ो the data back
	 * (the data was written with errors above).
	 * The READ_ONCE macros and prपूर्णांकk are used to prevent the
	 * the compiler optimizing these पढ़ोs out.
	 */
	reg = READ_ONCE(ptemp[0]);
	पढ़ो_reg = READ_ONCE(ptemp[1]);
	/* Force Read */
	rmb();

	edac_prपूर्णांकk(KERN_ALERT, EDAC_MC, "Read Data [0x%X, 0x%X]\n",
		    reg, पढ़ो_reg);

	dma_मुक्त_coherent(mci->pdev, 16, ptemp, dma_handle);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations altr_sdr_mc_debug_inject_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = altr_sdr_mc_err_inject_ग_लिखो,
	.llseek = generic_file_llseek,
पूर्ण;

अटल व्योम altr_sdr_mc_create_debugfs_nodes(काष्ठा mem_ctl_info *mci)
अणु
	अगर (!IS_ENABLED(CONFIG_EDAC_DEBUG))
		वापस;

	अगर (!mci->debugfs)
		वापस;

	edac_debugfs_create_file("altr_trigger", S_IWUSR, mci->debugfs, mci,
				 &altr_sdr_mc_debug_inject_fops);
पूर्ण

/* Get total memory size from Open Firmware DTB */
अटल अचिन्हित दीर्घ get_total_mem(व्योम)
अणु
	काष्ठा device_node *np = शून्य;
	काष्ठा resource res;
	पूर्णांक ret;
	अचिन्हित दीर्घ total_mem = 0;

	क्रम_each_node_by_type(np, "memory") अणु
		ret = of_address_to_resource(np, 0, &res);
		अगर (ret)
			जारी;

		total_mem += resource_size(&res);
	पूर्ण
	edac_dbg(0, "total_mem 0x%lx\n", total_mem);
	वापस total_mem;
पूर्ण

अटल स्थिर काष्ठा of_device_id altr_sdram_ctrl_of_match[] = अणु
	अणु .compatible = "altr,sdram-edac", .data = &c5_dataपूर्ण,
	अणु .compatible = "altr,sdram-edac-a10", .data = &a10_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altr_sdram_ctrl_of_match);

अटल पूर्णांक a10_init(काष्ठा regmap *mc_vbase)
अणु
	अगर (regmap_update_bits(mc_vbase, A10_INTMODE_OFST,
			       A10_INTMODE_SB_INT, A10_INTMODE_SB_INT)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Error setting SB IRQ mode\n");
		वापस -ENODEV;
	पूर्ण

	अगर (regmap_ग_लिखो(mc_vbase, A10_SERRCNTREG_OFST, 1)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Error setting trigger count\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक a10_unmask_irq(काष्ठा platक्रमm_device *pdev, u32 mask)
अणु
	व्योम __iomem  *sm_base;
	पूर्णांक  ret = 0;

	अगर (!request_mem_region(A10_SYMAN_INTMASK_CLR, माप(u32),
				dev_name(&pdev->dev))) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Unable to request mem region\n");
		वापस -EBUSY;
	पूर्ण

	sm_base = ioremap(A10_SYMAN_INTMASK_CLR, माप(u32));
	अगर (!sm_base) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Unable to ioremap device\n");

		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	ioग_लिखो32(mask, sm_base);

	iounmap(sm_base);

release:
	release_mem_region(A10_SYMAN_INTMASK_CLR, माप(u32));

	वापस ret;
पूर्ण

अटल पूर्णांक altr_sdram_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा mem_ctl_info *mci;
	काष्ठा altr_sdram_mc_data *drvdata;
	स्थिर काष्ठा altr_sdram_prv_data *priv;
	काष्ठा regmap *mc_vbase;
	काष्ठा dimm_info *dimm;
	u32 पढ़ो_reg;
	पूर्णांक irq, irq2, res = 0;
	अचिन्हित दीर्घ mem_size, irqflags = 0;

	id = of_match_device(altr_sdram_ctrl_of_match, &pdev->dev);
	अगर (!id)
		वापस -ENODEV;

	/* Grab the रेजिस्टर range from the sdr controller in device tree */
	mc_vbase = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
						   "altr,sdr-syscon");
	अगर (IS_ERR(mc_vbase)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "regmap for altr,sdr-syscon lookup failed.\n");
		वापस -ENODEV;
	पूर्ण

	/* Check specअगरic dependencies क्रम the module */
	priv = of_match_node(altr_sdram_ctrl_of_match,
			     pdev->dev.of_node)->data;

	/* Validate the SDRAM controller has ECC enabled */
	अगर (regmap_पढ़ो(mc_vbase, priv->ecc_ctrl_offset, &पढ़ो_reg) ||
	    ((पढ़ो_reg & priv->ecc_ctl_en_mask) != priv->ecc_ctl_en_mask)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "No ECC/ECC disabled [0x%08X]\n", पढ़ो_reg);
		वापस -ENODEV;
	पूर्ण

	/* Grab memory size from device tree. */
	mem_size = get_total_mem();
	अगर (!mem_size) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC, "Unable to calculate memory size\n");
		वापस -ENODEV;
	पूर्ण

	/* Ensure the SDRAM Interrupt is disabled */
	अगर (regmap_update_bits(mc_vbase, priv->ecc_irq_en_offset,
			       priv->ecc_irq_en_mask, 0)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Error disabling SDRAM ECC IRQ\n");
		वापस -ENODEV;
	पूर्ण

	/* Toggle to clear the SDRAM Error count */
	अगर (regmap_update_bits(mc_vbase, priv->ecc_cnt_rst_offset,
			       priv->ecc_cnt_rst_mask,
			       priv->ecc_cnt_rst_mask)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Error clearing SDRAM ECC count\n");
		वापस -ENODEV;
	पूर्ण

	अगर (regmap_update_bits(mc_vbase, priv->ecc_cnt_rst_offset,
			       priv->ecc_cnt_rst_mask, 0)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Error clearing SDRAM ECC count\n");
		वापस -ENODEV;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "No irq %d in DT\n", irq);
		वापस -ENODEV;
	पूर्ण

	/* Arria10 has a 2nd IRQ */
	irq2 = platक्रमm_get_irq(pdev, 1);

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = 1;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = 1;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers,
			    माप(काष्ठा altr_sdram_mc_data));
	अगर (!mci)
		वापस -ENOMEM;

	mci->pdev = &pdev->dev;
	drvdata = mci->pvt_info;
	drvdata->mc_vbase = mc_vbase;
	drvdata->data = priv;
	platक्रमm_set_drvdata(pdev, mci);

	अगर (!devres_खोलो_group(&pdev->dev, शून्य, GFP_KERNEL)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
			    "Unable to get managed device resource\n");
		res = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	mci->mtype_cap = MEM_FLAG_DDR3;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_name = dev_name(&pdev->dev);
	mci->scrub_mode = SCRUB_SW_SRC;
	mci->dev_name = dev_name(&pdev->dev);

	dimm = *mci->dimms;
	dimm->nr_pages = ((mem_size - 1) >> PAGE_SHIFT) + 1;
	dimm->grain = 8;
	dimm->dtype = DEV_X8;
	dimm->mtype = MEM_DDR3;
	dimm->edac_mode = EDAC_SECDED;

	res = edac_mc_add_mc(mci);
	अगर (res < 0)
		जाओ err;

	/* Only the Arria10 has separate IRQs */
	अगर (of_machine_is_compatible("altr,socfpga-arria10")) अणु
		/* Arria10 specअगरic initialization */
		res = a10_init(mc_vbase);
		अगर (res < 0)
			जाओ err2;

		res = devm_request_irq(&pdev->dev, irq2,
				       altr_sdram_mc_err_handler,
				       IRQF_SHARED, dev_name(&pdev->dev), mci);
		अगर (res < 0) अणु
			edac_mc_prपूर्णांकk(mci, KERN_ERR,
				       "Unable to request irq %d\n", irq2);
			res = -ENODEV;
			जाओ err2;
		पूर्ण

		res = a10_unmask_irq(pdev, A10_DDR0_IRQ_MASK);
		अगर (res < 0)
			जाओ err2;

		irqflags = IRQF_SHARED;
	पूर्ण

	res = devm_request_irq(&pdev->dev, irq, altr_sdram_mc_err_handler,
			       irqflags, dev_name(&pdev->dev), mci);
	अगर (res < 0) अणु
		edac_mc_prपूर्णांकk(mci, KERN_ERR,
			       "Unable to request irq %d\n", irq);
		res = -ENODEV;
		जाओ err2;
	पूर्ण

	/* Infraकाष्ठाure पढ़ोy - enable the IRQ */
	अगर (regmap_update_bits(drvdata->mc_vbase, priv->ecc_irq_en_offset,
			       priv->ecc_irq_en_mask, priv->ecc_irq_en_mask)) अणु
		edac_mc_prपूर्णांकk(mci, KERN_ERR,
			       "Error enabling SDRAM ECC IRQ\n");
		res = -ENODEV;
		जाओ err2;
	पूर्ण

	altr_sdr_mc_create_debugfs_nodes(mci);

	devres_बंद_group(&pdev->dev, शून्य);

	वापस 0;

err2:
	edac_mc_del_mc(&pdev->dev);
err:
	devres_release_group(&pdev->dev, शून्य);
मुक्त:
	edac_mc_मुक्त(mci);
	edac_prपूर्णांकk(KERN_ERR, EDAC_MC,
		    "EDAC Probe Failed; Error %d\n", res);

	वापस res;
पूर्ण

अटल पूर्णांक altr_sdram_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

/*
 * If you want to suspend, need to disable EDAC by removing it
 * from the device tree or defconfig.
 */
#अगर_घोषित CONFIG_PM
अटल पूर्णांक altr_sdram_prepare(काष्ठा device *dev)
अणु
	pr_err("Suspend not allowed when EDAC is enabled.\n");

	वापस -EPERM;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops altr_sdram_pm_ops = अणु
	.prepare = altr_sdram_prepare,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver altr_sdram_edac_driver = अणु
	.probe = altr_sdram_probe,
	.हटाओ = altr_sdram_हटाओ,
	.driver = अणु
		.name = "altr_sdram_edac",
#अगर_घोषित CONFIG_PM
		.pm = &altr_sdram_pm_ops,
#पूर्ण_अगर
		.of_match_table = altr_sdram_ctrl_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(altr_sdram_edac_driver);

#पूर्ण_अगर	/* CONFIG_EDAC_ALTERA_SDRAM */

/************************* EDAC Parent Probe *************************/

अटल स्थिर काष्ठा of_device_id altr_edac_device_of_match[];

अटल स्थिर काष्ठा of_device_id altr_edac_of_match[] = अणु
	अणु .compatible = "altr,socfpga-ecc-manager" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altr_edac_of_match);

अटल पूर्णांक altr_edac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	of_platक्रमm_populate(pdev->dev.of_node, altr_edac_device_of_match,
			     शून्य, &pdev->dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver altr_edac_driver = अणु
	.probe =  altr_edac_probe,
	.driver = अणु
		.name = "socfpga_ecc_manager",
		.of_match_table = altr_edac_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(altr_edac_driver);

/************************* EDAC Device Functions *************************/

/*
 * EDAC Device Functions (shared between various IPs).
 * The discrete memories use the EDAC Device framework. The probe
 * and error handling functions are very similar between memories
 * so they are shared. The memory allocation and मुक्तing क्रम EDAC
 * trigger testing are dअगरferent क्रम each memory.
 */

अटल स्थिर काष्ठा edac_device_prv_data ocramecc_data;
अटल स्थिर काष्ठा edac_device_prv_data l2ecc_data;
अटल स्थिर काष्ठा edac_device_prv_data a10_ocramecc_data;
अटल स्थिर काष्ठा edac_device_prv_data a10_l2ecc_data;

अटल irqवापस_t altr_edac_device_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	irqवापस_t ret_value = IRQ_NONE;
	काष्ठा edac_device_ctl_info *dci = dev_id;
	काष्ठा altr_edac_device_dev *drvdata = dci->pvt_info;
	स्थिर काष्ठा edac_device_prv_data *priv = drvdata->data;

	अगर (irq == drvdata->sb_irq) अणु
		अगर (priv->ce_clear_mask)
			ग_लिखोl(priv->ce_clear_mask, drvdata->base);
		edac_device_handle_ce(dci, 0, 0, drvdata->edac_dev_name);
		ret_value = IRQ_HANDLED;
	पूर्ण अन्यथा अगर (irq == drvdata->db_irq) अणु
		अगर (priv->ue_clear_mask)
			ग_लिखोl(priv->ue_clear_mask, drvdata->base);
		edac_device_handle_ue(dci, 0, 0, drvdata->edac_dev_name);
		panic("\nEDAC:ECC_DEVICE[Uncorrectable errors]\n");
		ret_value = IRQ_HANDLED;
	पूर्ण अन्यथा अणु
		WARN_ON(1);
	पूर्ण

	वापस ret_value;
पूर्ण

अटल sमाप_प्रकार altr_edac_device_trig(काष्ठा file *file,
				     स्थिर अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)

अणु
	u32 *ptemp, i, error_mask;
	पूर्णांक result = 0;
	u8 trig_type;
	अचिन्हित दीर्घ flags;
	काष्ठा edac_device_ctl_info *edac_dci = file->निजी_data;
	काष्ठा altr_edac_device_dev *drvdata = edac_dci->pvt_info;
	स्थिर काष्ठा edac_device_prv_data *priv = drvdata->data;
	व्योम *generic_ptr = edac_dci->dev;

	अगर (!user_buf || get_user(trig_type, user_buf))
		वापस -EFAULT;

	अगर (!priv->alloc_mem)
		वापस -ENOMEM;

	/*
	 * Note that generic_ptr is initialized to the device * but in
	 * some alloc_functions, this is overridden and वापसs data.
	 */
	ptemp = priv->alloc_mem(priv->trig_alloc_sz, &generic_ptr);
	अगर (!ptemp) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "Inject: Buffer Allocation error\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (trig_type == ALTR_UE_TRIGGER_CHAR)
		error_mask = priv->ue_set_mask;
	अन्यथा
		error_mask = priv->ce_set_mask;

	edac_prपूर्णांकk(KERN_ALERT, EDAC_DEVICE,
		    "Trigger Error Mask (0x%X)\n", error_mask);

	local_irq_save(flags);
	/* ग_लिखो ECC corrupted data out. */
	क्रम (i = 0; i < (priv->trig_alloc_sz / माप(*ptemp)); i++) अणु
		/* Read data so we're in the correct state */
		rmb();
		अगर (READ_ONCE(ptemp[i]))
			result = -1;
		/* Toggle Error bit (it is latched), leave ECC enabled */
		ग_लिखोl(error_mask, (drvdata->base + priv->set_err_ofst));
		ग_लिखोl(priv->ecc_enable_mask, (drvdata->base +
					       priv->set_err_ofst));
		ptemp[i] = i;
	पूर्ण
	/* Ensure it has been written out */
	wmb();
	local_irq_restore(flags);

	अगर (result)
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "Mem Not Cleared\n");

	/* Read out written data. ECC error caused here */
	क्रम (i = 0; i < ALTR_TRIGGER_READ_WRD_CNT; i++)
		अगर (READ_ONCE(ptemp[i]) != i)
			edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
				    "Read doesn't match written data\n");

	अगर (priv->मुक्त_mem)
		priv->मुक्त_mem(ptemp, priv->trig_alloc_sz, generic_ptr);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations altr_edac_device_inject_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = altr_edac_device_trig,
	.llseek = generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार altr_edac_a10_device_trig(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos);

अटल स्थिर काष्ठा file_operations altr_edac_a10_device_inject_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = altr_edac_a10_device_trig,
	.llseek = generic_file_llseek,
पूर्ण;

अटल sमाप_प्रकार altr_edac_a10_device_trig2(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos);

अटल स्थिर काष्ठा file_operations altr_edac_a10_device_inject2_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = altr_edac_a10_device_trig2,
	.llseek = generic_file_llseek,
पूर्ण;

अटल व्योम altr_create_edacdev_dbgfs(काष्ठा edac_device_ctl_info *edac_dci,
				      स्थिर काष्ठा edac_device_prv_data *priv)
अणु
	काष्ठा altr_edac_device_dev *drvdata = edac_dci->pvt_info;

	अगर (!IS_ENABLED(CONFIG_EDAC_DEBUG))
		वापस;

	drvdata->debugfs_dir = edac_debugfs_create_dir(drvdata->edac_dev_name);
	अगर (!drvdata->debugfs_dir)
		वापस;

	अगर (!edac_debugfs_create_file("altr_trigger", S_IWUSR,
				      drvdata->debugfs_dir, edac_dci,
				      priv->inject_fops))
		debugfs_हटाओ_recursive(drvdata->debugfs_dir);
पूर्ण

अटल स्थिर काष्ठा of_device_id altr_edac_device_of_match[] = अणु
#अगर_घोषित CONFIG_EDAC_ALTERA_L2C
	अणु .compatible = "altr,socfpga-l2-ecc", .data = &l2ecc_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_ALTERA_OCRAM
	अणु .compatible = "altr,socfpga-ocram-ecc", .data = &ocramecc_data पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altr_edac_device_of_match);

/*
 * altr_edac_device_probe()
 *	This is a generic EDAC device driver that will support
 *	various Altera memory devices such as the L2 cache ECC and
 *	OCRAM ECC as well as the memories क्रम other peripherals.
 *	Module specअगरic initialization is करोne by passing the
 *	function index in the device tree.
 */
अटल पूर्णांक altr_edac_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_device_ctl_info *dci;
	काष्ठा altr_edac_device_dev *drvdata;
	काष्ठा resource *r;
	पूर्णांक res = 0;
	काष्ठा device_node *np = pdev->dev.of_node;
	अक्षर *ecc_name = (अक्षर *)np->name;
	अटल पूर्णांक dev_instance;

	अगर (!devres_खोलो_group(&pdev->dev, शून्य, GFP_KERNEL)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "Unable to open devm\n");
		वापस -ENOMEM;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "Unable to get mem resource\n");
		res = -ENODEV;
		जाओ fail;
	पूर्ण

	अगर (!devm_request_mem_region(&pdev->dev, r->start, resource_size(r),
				     dev_name(&pdev->dev))) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "%s:Error requesting mem region\n", ecc_name);
		res = -EBUSY;
		जाओ fail;
	पूर्ण

	dci = edac_device_alloc_ctl_info(माप(*drvdata), ecc_name,
					 1, ecc_name, 1, 0, शून्य, 0,
					 dev_instance++);

	अगर (!dci) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "%s: Unable to allocate EDAC device\n", ecc_name);
		res = -ENOMEM;
		जाओ fail;
	पूर्ण

	drvdata = dci->pvt_info;
	dci->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dci);
	drvdata->edac_dev_name = ecc_name;

	drvdata->base = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!drvdata->base) अणु
		res = -ENOMEM;
		जाओ fail1;
	पूर्ण

	/* Get driver specअगरic data क्रम this EDAC device */
	drvdata->data = of_match_node(altr_edac_device_of_match, np)->data;

	/* Check specअगरic dependencies क्रम the module */
	अगर (drvdata->data->setup) अणु
		res = drvdata->data->setup(drvdata);
		अगर (res)
			जाओ fail1;
	पूर्ण

	drvdata->sb_irq = platक्रमm_get_irq(pdev, 0);
	res = devm_request_irq(&pdev->dev, drvdata->sb_irq,
			       altr_edac_device_handler,
			       0, dev_name(&pdev->dev), dci);
	अगर (res)
		जाओ fail1;

	drvdata->db_irq = platक्रमm_get_irq(pdev, 1);
	res = devm_request_irq(&pdev->dev, drvdata->db_irq,
			       altr_edac_device_handler,
			       0, dev_name(&pdev->dev), dci);
	अगर (res)
		जाओ fail1;

	dci->mod_name = "Altera ECC Manager";
	dci->dev_name = drvdata->edac_dev_name;

	res = edac_device_add_device(dci);
	अगर (res)
		जाओ fail1;

	altr_create_edacdev_dbgfs(dci, drvdata->data);

	devres_बंद_group(&pdev->dev, शून्य);

	वापस 0;

fail1:
	edac_device_मुक्त_ctl_info(dci);
fail:
	devres_release_group(&pdev->dev, शून्य);
	edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
		    "%s:Error setting up EDAC device: %d\n", ecc_name, res);

	वापस res;
पूर्ण

अटल पूर्णांक altr_edac_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_device_ctl_info *dci = platक्रमm_get_drvdata(pdev);
	काष्ठा altr_edac_device_dev *drvdata = dci->pvt_info;

	debugfs_हटाओ_recursive(drvdata->debugfs_dir);
	edac_device_del_device(&pdev->dev);
	edac_device_मुक्त_ctl_info(dci);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver altr_edac_device_driver = अणु
	.probe =  altr_edac_device_probe,
	.हटाओ = altr_edac_device_हटाओ,
	.driver = अणु
		.name = "altr_edac_device",
		.of_match_table = altr_edac_device_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(altr_edac_device_driver);

/******************* Arria10 Device ECC Shared Functions *****************/

/*
 *  Test क्रम memory's ECC dependencies upon entry because platक्रमm specअगरic
 *  startup should have initialized the memory and enabled the ECC.
 *  Can't turn on ECC here because accessing un-initialized memory will
 *  cause CE/UE errors possibly causing an ABORT.
 */
अटल पूर्णांक __maybe_unused
altr_check_ecc_deps(काष्ठा altr_edac_device_dev *device)
अणु
	व्योम __iomem  *base = device->base;
	स्थिर काष्ठा edac_device_prv_data *prv = device->data;

	अगर (पढ़ोl(base + prv->ecc_en_ofst) & prv->ecc_enable_mask)
		वापस 0;

	edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
		    "%s: No ECC present or ECC disabled.\n",
		    device->edac_dev_name);
	वापस -ENODEV;
पूर्ण

अटल irqवापस_t __maybe_unused altr_edac_a10_ecc_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा altr_edac_device_dev *dci = dev_id;
	व्योम __iomem  *base = dci->base;

	अगर (irq == dci->sb_irq) अणु
		ग_लिखोl(ALTR_A10_ECC_SERRPENA,
		       base + ALTR_A10_ECC_INTSTAT_OFST);
		edac_device_handle_ce(dci->edac_dev, 0, 0, dci->edac_dev_name);

		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर (irq == dci->db_irq) अणु
		ग_लिखोl(ALTR_A10_ECC_DERRPENA,
		       base + ALTR_A10_ECC_INTSTAT_OFST);
		edac_device_handle_ue(dci->edac_dev, 0, 0, dci->edac_dev_name);
		अगर (dci->data->panic)
			panic("\nEDAC:ECC_DEVICE[Uncorrectable errors]\n");

		वापस IRQ_HANDLED;
	पूर्ण

	WARN_ON(1);

	वापस IRQ_NONE;
पूर्ण

/******************* Arria10 Memory Buffer Functions *********************/

अटल अंतरभूत पूर्णांक a10_get_irq_mask(काष्ठा device_node *np)
अणु
	पूर्णांक irq;
	स्थिर u32 *handle = of_get_property(np, "interrupts", शून्य);

	अगर (!handle)
		वापस -ENODEV;
	irq = be32_to_cpup(handle);
	वापस irq;
पूर्ण

अटल अंतरभूत व्योम ecc_set_bits(u32 bit_mask, व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr);

	value |= bit_mask;
	ग_लिखोl(value, ioaddr);
पूर्ण

अटल अंतरभूत व्योम ecc_clear_bits(u32 bit_mask, व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr);

	value &= ~bit_mask;
	ग_लिखोl(value, ioaddr);
पूर्ण

अटल अंतरभूत पूर्णांक ecc_test_bits(u32 bit_mask, व्योम __iomem *ioaddr)
अणु
	u32 value = पढ़ोl(ioaddr);

	वापस (value & bit_mask) ? 1 : 0;
पूर्ण

/*
 * This function uses the memory initialization block in the Arria10 ECC
 * controller to initialize/clear the entire memory data and ECC data.
 */
अटल पूर्णांक __maybe_unused altr_init_memory_port(व्योम __iomem *ioaddr, पूर्णांक port)
अणु
	पूर्णांक limit = ALTR_A10_ECC_INIT_WATCHDOG_10US;
	u32 init_mask, stat_mask, clear_mask;
	पूर्णांक ret = 0;

	अगर (port) अणु
		init_mask = ALTR_A10_ECC_INITB;
		stat_mask = ALTR_A10_ECC_INITCOMPLETEB;
		clear_mask = ALTR_A10_ECC_ERRPENB_MASK;
	पूर्ण अन्यथा अणु
		init_mask = ALTR_A10_ECC_INITA;
		stat_mask = ALTR_A10_ECC_INITCOMPLETEA;
		clear_mask = ALTR_A10_ECC_ERRPENA_MASK;
	पूर्ण

	ecc_set_bits(init_mask, (ioaddr + ALTR_A10_ECC_CTRL_OFST));
	जबतक (limit--) अणु
		अगर (ecc_test_bits(stat_mask,
				  (ioaddr + ALTR_A10_ECC_INITSTAT_OFST)))
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (limit < 0)
		ret = -EBUSY;

	/* Clear any pending ECC पूर्णांकerrupts */
	ग_लिखोl(clear_mask, (ioaddr + ALTR_A10_ECC_INTSTAT_OFST));

	वापस ret;
पूर्ण

अटल __init पूर्णांक __maybe_unused
altr_init_a10_ecc_block(काष्ठा device_node *np, u32 irq_mask,
			u32 ecc_ctrl_en_mask, bool dual_port)
अणु
	पूर्णांक ret = 0;
	व्योम __iomem *ecc_block_base;
	काष्ठा regmap *ecc_mgr_map;
	अक्षर *ecc_name;
	काष्ठा device_node *np_eccmgr;

	ecc_name = (अक्षर *)np->name;

	/* Get the ECC Manager - parent of the device EDACs */
	np_eccmgr = of_get_parent(np);

	ecc_mgr_map =
		altr_sysmgr_regmap_lookup_by_phandle(np_eccmgr,
						     "altr,sysmgr-syscon");

	of_node_put(np_eccmgr);
	अगर (IS_ERR(ecc_mgr_map)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "Unable to get syscon altr,sysmgr-syscon\n");
		वापस -ENODEV;
	पूर्ण

	/* Map the ECC Block */
	ecc_block_base = of_iomap(np, 0);
	अगर (!ecc_block_base) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "Unable to map %s ECC block\n", ecc_name);
		वापस -ENODEV;
	पूर्ण

	/* Disable ECC */
	regmap_ग_लिखो(ecc_mgr_map, A10_SYSMGR_ECC_INTMASK_SET_OFST, irq_mask);
	ग_लिखोl(ALTR_A10_ECC_SERRINTEN,
	       (ecc_block_base + ALTR_A10_ECC_ERRINTENR_OFST));
	ecc_clear_bits(ecc_ctrl_en_mask,
		       (ecc_block_base + ALTR_A10_ECC_CTRL_OFST));
	/* Ensure all ग_लिखोs complete */
	wmb();
	/* Use HW initialization block to initialize memory क्रम ECC */
	ret = altr_init_memory_port(ecc_block_base, 0);
	अगर (ret) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "ECC: cannot init %s PORTA memory\n", ecc_name);
		जाओ out;
	पूर्ण

	अगर (dual_port) अणु
		ret = altr_init_memory_port(ecc_block_base, 1);
		अगर (ret) अणु
			edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
				    "ECC: cannot init %s PORTB memory\n",
				    ecc_name);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Interrupt mode set to every SBERR */
	regmap_ग_लिखो(ecc_mgr_map, ALTR_A10_ECC_INTMODE_OFST,
		     ALTR_A10_ECC_INTMODE);
	/* Enable ECC */
	ecc_set_bits(ecc_ctrl_en_mask, (ecc_block_base +
					ALTR_A10_ECC_CTRL_OFST));
	ग_लिखोl(ALTR_A10_ECC_SERRINTEN,
	       (ecc_block_base + ALTR_A10_ECC_ERRINTENS_OFST));
	regmap_ग_लिखो(ecc_mgr_map, A10_SYSMGR_ECC_INTMASK_CLR_OFST, irq_mask);
	/* Ensure all ग_लिखोs complete */
	wmb();
out:
	iounmap(ecc_block_base);
	वापस ret;
पूर्ण

अटल पूर्णांक validate_parent_available(काष्ठा device_node *np);
अटल स्थिर काष्ठा of_device_id altr_edac_a10_device_of_match[];
अटल पूर्णांक __init __maybe_unused altr_init_a10_ecc_device_type(अक्षर *compat)
अणु
	पूर्णांक irq;
	काष्ठा device_node *child, *np;

	np = of_find_compatible_node(शून्य, शून्य,
				     "altr,socfpga-a10-ecc-manager");
	अगर (!np) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "ECC Manager not found\n");
		वापस -ENODEV;
	पूर्ण

	क्रम_each_child_of_node(np, child) अणु
		स्थिर काष्ठा of_device_id *pdev_id;
		स्थिर काष्ठा edac_device_prv_data *prv;

		अगर (!of_device_is_available(child))
			जारी;
		अगर (!of_device_is_compatible(child, compat))
			जारी;

		अगर (validate_parent_available(child))
			जारी;

		irq = a10_get_irq_mask(child);
		अगर (irq < 0)
			जारी;

		/* Get matching node and check क्रम valid result */
		pdev_id = of_match_node(altr_edac_a10_device_of_match, child);
		अगर (IS_ERR_OR_शून्य(pdev_id))
			जारी;

		/* Validate निजी data poपूर्णांकer beक्रमe dereferencing */
		prv = pdev_id->data;
		अगर (!prv)
			जारी;

		altr_init_a10_ecc_block(child, BIT(irq),
					prv->ecc_enable_mask, 0);
	पूर्ण

	of_node_put(np);
	वापस 0;
पूर्ण

/*********************** SDRAM EDAC Device Functions *********************/

#अगर_घोषित CONFIG_EDAC_ALTERA_SDRAM

अटल स्थिर काष्ठा edac_device_prv_data s10_sdramecc_data = अणु
	.setup = altr_check_ecc_deps,
	.ce_clear_mask = ALTR_S10_ECC_SERRPENA,
	.ue_clear_mask = ALTR_S10_ECC_DERRPENA,
	.ecc_enable_mask = ALTR_S10_ECC_EN,
	.ecc_en_ofst = ALTR_S10_ECC_CTRL_SDRAM_OFST,
	.ce_set_mask = ALTR_S10_ECC_TSERRA,
	.ue_set_mask = ALTR_S10_ECC_TDERRA,
	.set_err_ofst = ALTR_S10_ECC_INTTEST_OFST,
	.ecc_irq_handler = altr_edac_a10_ecc_irq,
	.inject_fops = &altr_edac_a10_device_inject_fops,
पूर्ण;
#पूर्ण_अगर /* CONFIG_EDAC_ALTERA_SDRAM */

/*********************** OCRAM EDAC Device Functions *********************/

#अगर_घोषित CONFIG_EDAC_ALTERA_OCRAM

अटल व्योम *ocram_alloc_mem(माप_प्रकार size, व्योम **other)
अणु
	काष्ठा device_node *np;
	काष्ठा gen_pool *gp;
	व्योम *sram_addr;

	np = of_find_compatible_node(शून्य, शून्य, "altr,socfpga-ocram-ecc");
	अगर (!np)
		वापस शून्य;

	gp = of_gen_pool_get(np, "iram", 0);
	of_node_put(np);
	अगर (!gp)
		वापस शून्य;

	sram_addr = (व्योम *)gen_pool_alloc(gp, size);
	अगर (!sram_addr)
		वापस शून्य;

	स_रखो(sram_addr, 0, size);
	/* Ensure data is written out */
	wmb();

	/* Remember this handle क्रम मुक्तing  later */
	*other = gp;

	वापस sram_addr;
पूर्ण

अटल व्योम ocram_मुक्त_mem(व्योम *p, माप_प्रकार size, व्योम *other)
अणु
	gen_pool_मुक्त((काष्ठा gen_pool *)other, (अचिन्हित दीर्घ)p, size);
पूर्ण

अटल स्थिर काष्ठा edac_device_prv_data ocramecc_data = अणु
	.setup = altr_check_ecc_deps,
	.ce_clear_mask = (ALTR_OCR_ECC_EN | ALTR_OCR_ECC_SERR),
	.ue_clear_mask = (ALTR_OCR_ECC_EN | ALTR_OCR_ECC_DERR),
	.alloc_mem = ocram_alloc_mem,
	.मुक्त_mem = ocram_मुक्त_mem,
	.ecc_enable_mask = ALTR_OCR_ECC_EN,
	.ecc_en_ofst = ALTR_OCR_ECC_REG_OFFSET,
	.ce_set_mask = (ALTR_OCR_ECC_EN | ALTR_OCR_ECC_INJS),
	.ue_set_mask = (ALTR_OCR_ECC_EN | ALTR_OCR_ECC_INJD),
	.set_err_ofst = ALTR_OCR_ECC_REG_OFFSET,
	.trig_alloc_sz = ALTR_TRIG_OCRAM_BYTE_SIZE,
	.inject_fops = &altr_edac_device_inject_fops,
पूर्ण;

अटल पूर्णांक __maybe_unused
altr_check_ocram_deps_init(काष्ठा altr_edac_device_dev *device)
अणु
	व्योम __iomem  *base = device->base;
	पूर्णांक ret;

	ret = altr_check_ecc_deps(device);
	अगर (ret)
		वापस ret;

	/* Verअगरy OCRAM has been initialized */
	अगर (!ecc_test_bits(ALTR_A10_ECC_INITCOMPLETEA,
			   (base + ALTR_A10_ECC_INITSTAT_OFST)))
		वापस -ENODEV;

	/* Enable IRQ on Single Bit Error */
	ग_लिखोl(ALTR_A10_ECC_SERRINTEN, (base + ALTR_A10_ECC_ERRINTENS_OFST));
	/* Ensure all ग_लिखोs complete */
	wmb();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा edac_device_prv_data a10_ocramecc_data = अणु
	.setup = altr_check_ocram_deps_init,
	.ce_clear_mask = ALTR_A10_ECC_SERRPENA,
	.ue_clear_mask = ALTR_A10_ECC_DERRPENA,
	.irq_status_mask = A10_SYSMGR_ECC_INTSTAT_OCRAM,
	.ecc_enable_mask = ALTR_A10_OCRAM_ECC_EN_CTL,
	.ecc_en_ofst = ALTR_A10_ECC_CTRL_OFST,
	.ce_set_mask = ALTR_A10_ECC_TSERRA,
	.ue_set_mask = ALTR_A10_ECC_TDERRA,
	.set_err_ofst = ALTR_A10_ECC_INTTEST_OFST,
	.ecc_irq_handler = altr_edac_a10_ecc_irq,
	.inject_fops = &altr_edac_a10_device_inject2_fops,
	/*
	 * OCRAM panic on uncorrectable error because sleep/resume
	 * functions and FPGA contents are stored in OCRAM. Prefer
	 * a kernel panic over executing/loading corrupted data.
	 */
	.panic = true,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_EDAC_ALTERA_OCRAM */

/********************* L2 Cache EDAC Device Functions ********************/

#अगर_घोषित CONFIG_EDAC_ALTERA_L2C

अटल व्योम *l2_alloc_mem(माप_प्रकार size, व्योम **other)
अणु
	काष्ठा device *dev = *other;
	व्योम *ptemp = devm_kzalloc(dev, size, GFP_KERNEL);

	अगर (!ptemp)
		वापस शून्य;

	/* Make sure everything is written out */
	wmb();

	/*
	 * Clean all cache levels up to LoC (includes L2)
	 * This ensures the corrupted data is written पूर्णांकo
	 * L2 cache क्रम पढ़ोback test (which causes ECC error).
	 */
	flush_cache_all();

	वापस ptemp;
पूर्ण

अटल व्योम l2_मुक्त_mem(व्योम *p, माप_प्रकार size, व्योम *other)
अणु
	काष्ठा device *dev = other;

	अगर (dev && p)
		devm_kमुक्त(dev, p);
पूर्ण

/*
 * altr_l2_check_deps()
 *	Test क्रम L2 cache ECC dependencies upon entry because
 *	platक्रमm specअगरic startup should have initialized the L2
 *	memory and enabled the ECC.
 *	Bail अगर ECC is not enabled.
 *	Note that L2 Cache Enable is क्रमced at build समय.
 */
अटल पूर्णांक altr_l2_check_deps(काष्ठा altr_edac_device_dev *device)
अणु
	व्योम __iomem *base = device->base;
	स्थिर काष्ठा edac_device_prv_data *prv = device->data;

	अगर ((पढ़ोl(base) & prv->ecc_enable_mask) ==
	     prv->ecc_enable_mask)
		वापस 0;

	edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
		    "L2: No ECC present, or ECC disabled\n");
	वापस -ENODEV;
पूर्ण

अटल irqवापस_t altr_edac_a10_l2_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा altr_edac_device_dev *dci = dev_id;

	अगर (irq == dci->sb_irq) अणु
		regmap_ग_लिखो(dci->edac->ecc_mgr_map,
			     A10_SYSGMR_MPU_CLEAR_L2_ECC_OFST,
			     A10_SYSGMR_MPU_CLEAR_L2_ECC_SB);
		edac_device_handle_ce(dci->edac_dev, 0, 0, dci->edac_dev_name);

		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर (irq == dci->db_irq) अणु
		regmap_ग_लिखो(dci->edac->ecc_mgr_map,
			     A10_SYSGMR_MPU_CLEAR_L2_ECC_OFST,
			     A10_SYSGMR_MPU_CLEAR_L2_ECC_MB);
		edac_device_handle_ue(dci->edac_dev, 0, 0, dci->edac_dev_name);
		panic("\nEDAC:ECC_DEVICE[Uncorrectable errors]\n");

		वापस IRQ_HANDLED;
	पूर्ण

	WARN_ON(1);

	वापस IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा edac_device_prv_data l2ecc_data = अणु
	.setup = altr_l2_check_deps,
	.ce_clear_mask = 0,
	.ue_clear_mask = 0,
	.alloc_mem = l2_alloc_mem,
	.मुक्त_mem = l2_मुक्त_mem,
	.ecc_enable_mask = ALTR_L2_ECC_EN,
	.ce_set_mask = (ALTR_L2_ECC_EN | ALTR_L2_ECC_INJS),
	.ue_set_mask = (ALTR_L2_ECC_EN | ALTR_L2_ECC_INJD),
	.set_err_ofst = ALTR_L2_ECC_REG_OFFSET,
	.trig_alloc_sz = ALTR_TRIG_L2C_BYTE_SIZE,
	.inject_fops = &altr_edac_device_inject_fops,
पूर्ण;

अटल स्थिर काष्ठा edac_device_prv_data a10_l2ecc_data = अणु
	.setup = altr_l2_check_deps,
	.ce_clear_mask = ALTR_A10_L2_ECC_SERR_CLR,
	.ue_clear_mask = ALTR_A10_L2_ECC_MERR_CLR,
	.irq_status_mask = A10_SYSMGR_ECC_INTSTAT_L2,
	.alloc_mem = l2_alloc_mem,
	.मुक्त_mem = l2_मुक्त_mem,
	.ecc_enable_mask = ALTR_A10_L2_ECC_EN_CTL,
	.ce_set_mask = ALTR_A10_L2_ECC_CE_INJ_MASK,
	.ue_set_mask = ALTR_A10_L2_ECC_UE_INJ_MASK,
	.set_err_ofst = ALTR_A10_L2_ECC_INJ_OFST,
	.ecc_irq_handler = altr_edac_a10_l2_irq,
	.trig_alloc_sz = ALTR_TRIG_L2C_BYTE_SIZE,
	.inject_fops = &altr_edac_device_inject_fops,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_EDAC_ALTERA_L2C */

/********************* Ethernet Device Functions ********************/

#अगर_घोषित CONFIG_EDAC_ALTERA_ETHERNET

अटल पूर्णांक __init socfpga_init_ethernet_ecc(काष्ठा altr_edac_device_dev *dev)
अणु
	पूर्णांक ret;

	ret = altr_init_a10_ecc_device_type("altr,socfpga-eth-mac-ecc");
	अगर (ret)
		वापस ret;

	वापस altr_check_ecc_deps(dev);
पूर्ण

अटल स्थिर काष्ठा edac_device_prv_data a10_enetecc_data = अणु
	.setup = socfpga_init_ethernet_ecc,
	.ce_clear_mask = ALTR_A10_ECC_SERRPENA,
	.ue_clear_mask = ALTR_A10_ECC_DERRPENA,
	.ecc_enable_mask = ALTR_A10_COMMON_ECC_EN_CTL,
	.ecc_en_ofst = ALTR_A10_ECC_CTRL_OFST,
	.ce_set_mask = ALTR_A10_ECC_TSERRA,
	.ue_set_mask = ALTR_A10_ECC_TDERRA,
	.set_err_ofst = ALTR_A10_ECC_INTTEST_OFST,
	.ecc_irq_handler = altr_edac_a10_ecc_irq,
	.inject_fops = &altr_edac_a10_device_inject2_fops,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_EDAC_ALTERA_ETHERNET */

/********************** न_अंकD Device Functions **********************/

#अगर_घोषित CONFIG_EDAC_ALTERA_न_अंकD

अटल पूर्णांक __init socfpga_init_nand_ecc(काष्ठा altr_edac_device_dev *device)
अणु
	पूर्णांक ret;

	ret = altr_init_a10_ecc_device_type("altr,socfpga-nand-ecc");
	अगर (ret)
		वापस ret;

	वापस altr_check_ecc_deps(device);
पूर्ण

अटल स्थिर काष्ठा edac_device_prv_data a10_nandecc_data = अणु
	.setup = socfpga_init_nand_ecc,
	.ce_clear_mask = ALTR_A10_ECC_SERRPENA,
	.ue_clear_mask = ALTR_A10_ECC_DERRPENA,
	.ecc_enable_mask = ALTR_A10_COMMON_ECC_EN_CTL,
	.ecc_en_ofst = ALTR_A10_ECC_CTRL_OFST,
	.ce_set_mask = ALTR_A10_ECC_TSERRA,
	.ue_set_mask = ALTR_A10_ECC_TDERRA,
	.set_err_ofst = ALTR_A10_ECC_INTTEST_OFST,
	.ecc_irq_handler = altr_edac_a10_ecc_irq,
	.inject_fops = &altr_edac_a10_device_inject_fops,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_EDAC_ALTERA_न_अंकD */

/********************** DMA Device Functions **********************/

#अगर_घोषित CONFIG_EDAC_ALTERA_DMA

अटल पूर्णांक __init socfpga_init_dma_ecc(काष्ठा altr_edac_device_dev *device)
अणु
	पूर्णांक ret;

	ret = altr_init_a10_ecc_device_type("altr,socfpga-dma-ecc");
	अगर (ret)
		वापस ret;

	वापस altr_check_ecc_deps(device);
पूर्ण

अटल स्थिर काष्ठा edac_device_prv_data a10_dmaecc_data = अणु
	.setup = socfpga_init_dma_ecc,
	.ce_clear_mask = ALTR_A10_ECC_SERRPENA,
	.ue_clear_mask = ALTR_A10_ECC_DERRPENA,
	.ecc_enable_mask = ALTR_A10_COMMON_ECC_EN_CTL,
	.ecc_en_ofst = ALTR_A10_ECC_CTRL_OFST,
	.ce_set_mask = ALTR_A10_ECC_TSERRA,
	.ue_set_mask = ALTR_A10_ECC_TDERRA,
	.set_err_ofst = ALTR_A10_ECC_INTTEST_OFST,
	.ecc_irq_handler = altr_edac_a10_ecc_irq,
	.inject_fops = &altr_edac_a10_device_inject_fops,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_EDAC_ALTERA_DMA */

/********************** USB Device Functions **********************/

#अगर_घोषित CONFIG_EDAC_ALTERA_USB

अटल पूर्णांक __init socfpga_init_usb_ecc(काष्ठा altr_edac_device_dev *device)
अणु
	पूर्णांक ret;

	ret = altr_init_a10_ecc_device_type("altr,socfpga-usb-ecc");
	अगर (ret)
		वापस ret;

	वापस altr_check_ecc_deps(device);
पूर्ण

अटल स्थिर काष्ठा edac_device_prv_data a10_usbecc_data = अणु
	.setup = socfpga_init_usb_ecc,
	.ce_clear_mask = ALTR_A10_ECC_SERRPENA,
	.ue_clear_mask = ALTR_A10_ECC_DERRPENA,
	.ecc_enable_mask = ALTR_A10_COMMON_ECC_EN_CTL,
	.ecc_en_ofst = ALTR_A10_ECC_CTRL_OFST,
	.ce_set_mask = ALTR_A10_ECC_TSERRA,
	.ue_set_mask = ALTR_A10_ECC_TDERRA,
	.set_err_ofst = ALTR_A10_ECC_INTTEST_OFST,
	.ecc_irq_handler = altr_edac_a10_ecc_irq,
	.inject_fops = &altr_edac_a10_device_inject2_fops,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_EDAC_ALTERA_USB */

/********************** QSPI Device Functions **********************/

#अगर_घोषित CONFIG_EDAC_ALTERA_QSPI

अटल पूर्णांक __init socfpga_init_qspi_ecc(काष्ठा altr_edac_device_dev *device)
अणु
	पूर्णांक ret;

	ret = altr_init_a10_ecc_device_type("altr,socfpga-qspi-ecc");
	अगर (ret)
		वापस ret;

	वापस altr_check_ecc_deps(device);
पूर्ण

अटल स्थिर काष्ठा edac_device_prv_data a10_qspiecc_data = अणु
	.setup = socfpga_init_qspi_ecc,
	.ce_clear_mask = ALTR_A10_ECC_SERRPENA,
	.ue_clear_mask = ALTR_A10_ECC_DERRPENA,
	.ecc_enable_mask = ALTR_A10_COMMON_ECC_EN_CTL,
	.ecc_en_ofst = ALTR_A10_ECC_CTRL_OFST,
	.ce_set_mask = ALTR_A10_ECC_TSERRA,
	.ue_set_mask = ALTR_A10_ECC_TDERRA,
	.set_err_ofst = ALTR_A10_ECC_INTTEST_OFST,
	.ecc_irq_handler = altr_edac_a10_ecc_irq,
	.inject_fops = &altr_edac_a10_device_inject_fops,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_EDAC_ALTERA_QSPI */

/********************* SDMMC Device Functions **********************/

#अगर_घोषित CONFIG_EDAC_ALTERA_SDMMC

अटल स्थिर काष्ठा edac_device_prv_data a10_sdmmceccb_data;
अटल पूर्णांक altr_portb_setup(काष्ठा altr_edac_device_dev *device)
अणु
	काष्ठा edac_device_ctl_info *dci;
	काष्ठा altr_edac_device_dev *altdev;
	अक्षर *ecc_name = "sdmmcb-ecc";
	पूर्णांक edac_idx, rc;
	काष्ठा device_node *np;
	स्थिर काष्ठा edac_device_prv_data *prv = &a10_sdmmceccb_data;

	rc = altr_check_ecc_deps(device);
	अगर (rc)
		वापस rc;

	np = of_find_compatible_node(शून्य, शून्य, "altr,socfpga-sdmmc-ecc");
	अगर (!np) अणु
		edac_prपूर्णांकk(KERN_WARNING, EDAC_DEVICE, "SDMMC node not found\n");
		वापस -ENODEV;
	पूर्ण

	/* Create the PortB EDAC device */
	edac_idx = edac_device_alloc_index();
	dci = edac_device_alloc_ctl_info(माप(*altdev), ecc_name, 1,
					 ecc_name, 1, 0, शून्य, 0, edac_idx);
	अगर (!dci) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "%s: Unable to allocate PortB EDAC device\n",
			    ecc_name);
		वापस -ENOMEM;
	पूर्ण

	/* Initialize the PortB EDAC device काष्ठाure from PortA काष्ठाure */
	altdev = dci->pvt_info;
	*altdev = *device;

	अगर (!devres_खोलो_group(&altdev->ddev, altr_portb_setup, GFP_KERNEL))
		वापस -ENOMEM;

	/* Update PortB specअगरic values */
	altdev->edac_dev_name = ecc_name;
	altdev->edac_idx = edac_idx;
	altdev->edac_dev = dci;
	altdev->data = prv;
	dci->dev = &altdev->ddev;
	dci->ctl_name = "Altera ECC Manager";
	dci->mod_name = ecc_name;
	dci->dev_name = ecc_name;

	/*
	 * Update the PortB IRQs - A10 has 4, S10 has 2, Index accordingly
	 *
	 * FIXME: Instead of अगरdefs with dअगरferent architectures the driver
	 *        should properly use compatibles.
	 */
#अगर_घोषित CONFIG_64BIT
	altdev->sb_irq = irq_of_parse_and_map(np, 1);
#अन्यथा
	altdev->sb_irq = irq_of_parse_and_map(np, 2);
#पूर्ण_अगर
	अगर (!altdev->sb_irq) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "Error PortB SBIRQ alloc\n");
		rc = -ENODEV;
		जाओ err_release_group_1;
	पूर्ण
	rc = devm_request_irq(&altdev->ddev, altdev->sb_irq,
			      prv->ecc_irq_handler,
			      IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
			      ecc_name, altdev);
	अगर (rc) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "PortB SBERR IRQ error\n");
		जाओ err_release_group_1;
	पूर्ण

#अगर_घोषित CONFIG_64BIT
	/* Use IRQ to determine SError origin instead of assigning IRQ */
	rc = of_property_पढ़ो_u32_index(np, "interrupts", 1, &altdev->db_irq);
	अगर (rc) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "Error PortB DBIRQ alloc\n");
		जाओ err_release_group_1;
	पूर्ण
#अन्यथा
	altdev->db_irq = irq_of_parse_and_map(np, 3);
	अगर (!altdev->db_irq) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "Error PortB DBIRQ alloc\n");
		rc = -ENODEV;
		जाओ err_release_group_1;
	पूर्ण
	rc = devm_request_irq(&altdev->ddev, altdev->db_irq,
			      prv->ecc_irq_handler,
			      IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
			      ecc_name, altdev);
	अगर (rc) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "PortB DBERR IRQ error\n");
		जाओ err_release_group_1;
	पूर्ण
#पूर्ण_अगर

	rc = edac_device_add_device(dci);
	अगर (rc) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "edac_device_add_device portB failed\n");
		rc = -ENOMEM;
		जाओ err_release_group_1;
	पूर्ण
	altr_create_edacdev_dbgfs(dci, prv);

	list_add(&altdev->next, &altdev->edac->a10_ecc_devices);

	devres_हटाओ_group(&altdev->ddev, altr_portb_setup);

	वापस 0;

err_release_group_1:
	edac_device_मुक्त_ctl_info(dci);
	devres_release_group(&altdev->ddev, altr_portb_setup);
	edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
		    "%s:Error setting up EDAC device: %d\n", ecc_name, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक __init socfpga_init_sdmmc_ecc(काष्ठा altr_edac_device_dev *device)
अणु
	पूर्णांक rc = -ENODEV;
	काष्ठा device_node *child;

	child = of_find_compatible_node(शून्य, शून्य, "altr,socfpga-sdmmc-ecc");
	अगर (!child)
		वापस -ENODEV;

	अगर (!of_device_is_available(child))
		जाओ निकास;

	अगर (validate_parent_available(child))
		जाओ निकास;

	/* Init portB */
	rc = altr_init_a10_ecc_block(child, ALTR_A10_SDMMC_IRQ_MASK,
				     a10_sdmmceccb_data.ecc_enable_mask, 1);
	अगर (rc)
		जाओ निकास;

	/* Setup portB */
	वापस altr_portb_setup(device);

निकास:
	of_node_put(child);
	वापस rc;
पूर्ण

अटल irqवापस_t altr_edac_a10_ecc_irq_portb(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा altr_edac_device_dev *ad = dev_id;
	व्योम __iomem  *base = ad->base;
	स्थिर काष्ठा edac_device_prv_data *priv = ad->data;

	अगर (irq == ad->sb_irq) अणु
		ग_लिखोl(priv->ce_clear_mask,
		       base + ALTR_A10_ECC_INTSTAT_OFST);
		edac_device_handle_ce(ad->edac_dev, 0, 0, ad->edac_dev_name);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा अगर (irq == ad->db_irq) अणु
		ग_लिखोl(priv->ue_clear_mask,
		       base + ALTR_A10_ECC_INTSTAT_OFST);
		edac_device_handle_ue(ad->edac_dev, 0, 0, ad->edac_dev_name);
		वापस IRQ_HANDLED;
	पूर्ण

	WARN_ONCE(1, "Unhandled IRQ%d on Port B.", irq);

	वापस IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा edac_device_prv_data a10_sdmmcecca_data = अणु
	.setup = socfpga_init_sdmmc_ecc,
	.ce_clear_mask = ALTR_A10_ECC_SERRPENA,
	.ue_clear_mask = ALTR_A10_ECC_DERRPENA,
	.ecc_enable_mask = ALTR_A10_COMMON_ECC_EN_CTL,
	.ecc_en_ofst = ALTR_A10_ECC_CTRL_OFST,
	.ce_set_mask = ALTR_A10_ECC_SERRPENA,
	.ue_set_mask = ALTR_A10_ECC_DERRPENA,
	.set_err_ofst = ALTR_A10_ECC_INTTEST_OFST,
	.ecc_irq_handler = altr_edac_a10_ecc_irq,
	.inject_fops = &altr_edac_a10_device_inject_fops,
पूर्ण;

अटल स्थिर काष्ठा edac_device_prv_data a10_sdmmceccb_data = अणु
	.setup = socfpga_init_sdmmc_ecc,
	.ce_clear_mask = ALTR_A10_ECC_SERRPENB,
	.ue_clear_mask = ALTR_A10_ECC_DERRPENB,
	.ecc_enable_mask = ALTR_A10_COMMON_ECC_EN_CTL,
	.ecc_en_ofst = ALTR_A10_ECC_CTRL_OFST,
	.ce_set_mask = ALTR_A10_ECC_TSERRB,
	.ue_set_mask = ALTR_A10_ECC_TDERRB,
	.set_err_ofst = ALTR_A10_ECC_INTTEST_OFST,
	.ecc_irq_handler = altr_edac_a10_ecc_irq_portb,
	.inject_fops = &altr_edac_a10_device_inject_fops,
पूर्ण;

#पूर्ण_अगर	/* CONFIG_EDAC_ALTERA_SDMMC */

/********************* Arria10 EDAC Device Functions *************************/
अटल स्थिर काष्ठा of_device_id altr_edac_a10_device_of_match[] = अणु
#अगर_घोषित CONFIG_EDAC_ALTERA_L2C
	अणु .compatible = "altr,socfpga-a10-l2-ecc", .data = &a10_l2ecc_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_ALTERA_OCRAM
	अणु .compatible = "altr,socfpga-a10-ocram-ecc",
	  .data = &a10_ocramecc_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_ALTERA_ETHERNET
	अणु .compatible = "altr,socfpga-eth-mac-ecc",
	  .data = &a10_enetecc_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_ALTERA_न_अंकD
	अणु .compatible = "altr,socfpga-nand-ecc", .data = &a10_nandecc_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_ALTERA_DMA
	अणु .compatible = "altr,socfpga-dma-ecc", .data = &a10_dmaecc_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_ALTERA_USB
	अणु .compatible = "altr,socfpga-usb-ecc", .data = &a10_usbecc_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_ALTERA_QSPI
	अणु .compatible = "altr,socfpga-qspi-ecc", .data = &a10_qspiecc_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_ALTERA_SDMMC
	अणु .compatible = "altr,socfpga-sdmmc-ecc", .data = &a10_sdmmcecca_data पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EDAC_ALTERA_SDRAM
	अणु .compatible = "altr,sdram-edac-s10", .data = &s10_sdramecc_data पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altr_edac_a10_device_of_match);

/*
 * The Arria10 EDAC Device Functions dअगरfer from the Cyclone5/Arria5
 * because 2 IRQs are shared among the all ECC peripherals. The ECC
 * manager manages the IRQs and the children.
 * Based on xgene_edac.c peripheral code.
 */

अटल sमाप_प्रकार altr_edac_a10_device_trig(काष्ठा file *file,
					 स्थिर अक्षर __user *user_buf,
					 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा edac_device_ctl_info *edac_dci = file->निजी_data;
	काष्ठा altr_edac_device_dev *drvdata = edac_dci->pvt_info;
	स्थिर काष्ठा edac_device_prv_data *priv = drvdata->data;
	व्योम __iomem *set_addr = (drvdata->base + priv->set_err_ofst);
	अचिन्हित दीर्घ flags;
	u8 trig_type;

	अगर (!user_buf || get_user(trig_type, user_buf))
		वापस -EFAULT;

	local_irq_save(flags);
	अगर (trig_type == ALTR_UE_TRIGGER_CHAR)
		ग_लिखोl(priv->ue_set_mask, set_addr);
	अन्यथा
		ग_लिखोl(priv->ce_set_mask, set_addr);

	/* Ensure the पूर्णांकerrupt test bits are set */
	wmb();
	local_irq_restore(flags);

	वापस count;
पूर्ण

/*
 * The Stratix10 EDAC Error Injection Functions dअगरfer from Arria10
 * slightly. A few Arria10 peripherals can use this injection function.
 * Inject the error पूर्णांकo the memory and then पढ़ोback to trigger the IRQ.
 */
अटल sमाप_प्रकार altr_edac_a10_device_trig2(काष्ठा file *file,
					  स्थिर अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा edac_device_ctl_info *edac_dci = file->निजी_data;
	काष्ठा altr_edac_device_dev *drvdata = edac_dci->pvt_info;
	स्थिर काष्ठा edac_device_prv_data *priv = drvdata->data;
	व्योम __iomem *set_addr = (drvdata->base + priv->set_err_ofst);
	अचिन्हित दीर्घ flags;
	u8 trig_type;

	अगर (!user_buf || get_user(trig_type, user_buf))
		वापस -EFAULT;

	local_irq_save(flags);
	अगर (trig_type == ALTR_UE_TRIGGER_CHAR) अणु
		ग_लिखोl(priv->ue_set_mask, set_addr);
	पूर्ण अन्यथा अणु
		/* Setup पढ़ो/ग_लिखो of 4 bytes */
		ग_लिखोl(ECC_WORD_WRITE, drvdata->base + ECC_BLK_DBYTECTRL_OFST);
		/* Setup Address to 0 */
		ग_लिखोl(0, drvdata->base + ECC_BLK_ADDRESS_OFST);
		/* Setup accctrl to पढ़ो & ecc & data override */
		ग_लिखोl(ECC_READ_EDOVR, drvdata->base + ECC_BLK_ACCCTRL_OFST);
		/* Kick it. */
		ग_लिखोl(ECC_XACT_KICK, drvdata->base + ECC_BLK_STARTACC_OFST);
		/* Setup ग_लिखो क्रम single bit change */
		ग_लिखोl(पढ़ोl(drvdata->base + ECC_BLK_RDATA0_OFST) ^ 0x1,
		       drvdata->base + ECC_BLK_WDATA0_OFST);
		ग_लिखोl(पढ़ोl(drvdata->base + ECC_BLK_RDATA1_OFST),
		       drvdata->base + ECC_BLK_WDATA1_OFST);
		ग_लिखोl(पढ़ोl(drvdata->base + ECC_BLK_RDATA2_OFST),
		       drvdata->base + ECC_BLK_WDATA2_OFST);
		ग_लिखोl(पढ़ोl(drvdata->base + ECC_BLK_RDATA3_OFST),
		       drvdata->base + ECC_BLK_WDATA3_OFST);

		/* Copy Read ECC to Write ECC */
		ग_लिखोl(पढ़ोl(drvdata->base + ECC_BLK_RECC0_OFST),
		       drvdata->base + ECC_BLK_WECC0_OFST);
		ग_लिखोl(पढ़ोl(drvdata->base + ECC_BLK_RECC1_OFST),
		       drvdata->base + ECC_BLK_WECC1_OFST);
		/* Setup accctrl to ग_लिखो & ecc override & data override */
		ग_लिखोl(ECC_WRITE_EDOVR, drvdata->base + ECC_BLK_ACCCTRL_OFST);
		/* Kick it. */
		ग_लिखोl(ECC_XACT_KICK, drvdata->base + ECC_BLK_STARTACC_OFST);
		/* Setup accctrl to पढ़ो & ecc overग_लिखो & data overग_लिखो */
		ग_लिखोl(ECC_READ_EDOVR, drvdata->base + ECC_BLK_ACCCTRL_OFST);
		/* Kick it. */
		ग_लिखोl(ECC_XACT_KICK, drvdata->base + ECC_BLK_STARTACC_OFST);
	पूर्ण

	/* Ensure the पूर्णांकerrupt test bits are set */
	wmb();
	local_irq_restore(flags);

	वापस count;
पूर्ण

अटल व्योम altr_edac_a10_irq_handler(काष्ठा irq_desc *desc)
अणु
	पूर्णांक dberr, bit, sm_offset, irq_status;
	काष्ठा altr_arria10_edac *edac = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक irq = irq_desc_get_irq(desc);
	अचिन्हित दीर्घ bits;

	dberr = (irq == edac->db_irq) ? 1 : 0;
	sm_offset = dberr ? A10_SYSMGR_ECC_INTSTAT_DERR_OFST :
			    A10_SYSMGR_ECC_INTSTAT_SERR_OFST;

	chained_irq_enter(chip, desc);

	regmap_पढ़ो(edac->ecc_mgr_map, sm_offset, &irq_status);

	bits = irq_status;
	क्रम_each_set_bit(bit, &bits, 32) अणु
		irq = irq_linear_revmap(edac->करोमुख्य, dberr * 32 + bit);
		अगर (irq)
			generic_handle_irq(irq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल पूर्णांक validate_parent_available(काष्ठा device_node *np)
अणु
	काष्ठा device_node *parent;
	पूर्णांक ret = 0;

	/* SDRAM must be present क्रम Linux (implied parent) */
	अगर (of_device_is_compatible(np, "altr,sdram-edac-s10"))
		वापस 0;

	/* Ensure parent device is enabled अगर parent node exists */
	parent = of_parse_phandle(np, "altr,ecc-parent", 0);
	अगर (parent && !of_device_is_available(parent))
		ret = -ENODEV;

	of_node_put(parent);
	वापस ret;
पूर्ण

अटल पूर्णांक get_s10_sdram_edac_resource(काष्ठा device_node *np,
				       काष्ठा resource *res)
अणु
	काष्ठा device_node *parent;
	पूर्णांक ret;

	parent = of_parse_phandle(np, "altr,sdr-syscon", 0);
	अगर (!parent)
		वापस -ENODEV;

	ret = of_address_to_resource(parent, 0, res);
	of_node_put(parent);

	वापस ret;
पूर्ण

अटल पूर्णांक altr_edac_a10_device_add(काष्ठा altr_arria10_edac *edac,
				    काष्ठा device_node *np)
अणु
	काष्ठा edac_device_ctl_info *dci;
	काष्ठा altr_edac_device_dev *altdev;
	अक्षर *ecc_name = (अक्षर *)np->name;
	काष्ठा resource res;
	पूर्णांक edac_idx;
	पूर्णांक rc = 0;
	स्थिर काष्ठा edac_device_prv_data *prv;
	/* Get matching node and check क्रम valid result */
	स्थिर काष्ठा of_device_id *pdev_id =
		of_match_node(altr_edac_a10_device_of_match, np);
	अगर (IS_ERR_OR_शून्य(pdev_id))
		वापस -ENODEV;

	/* Get driver specअगरic data क्रम this EDAC device */
	prv = pdev_id->data;
	अगर (IS_ERR_OR_शून्य(prv))
		वापस -ENODEV;

	अगर (validate_parent_available(np))
		वापस -ENODEV;

	अगर (!devres_खोलो_group(edac->dev, altr_edac_a10_device_add, GFP_KERNEL))
		वापस -ENOMEM;

	अगर (of_device_is_compatible(np, "altr,sdram-edac-s10"))
		rc = get_s10_sdram_edac_resource(np, &res);
	अन्यथा
		rc = of_address_to_resource(np, 0, &res);

	अगर (rc < 0) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "%s: no resource address\n", ecc_name);
		जाओ err_release_group;
	पूर्ण

	edac_idx = edac_device_alloc_index();
	dci = edac_device_alloc_ctl_info(माप(*altdev), ecc_name,
					 1, ecc_name, 1, 0, शून्य, 0,
					 edac_idx);

	अगर (!dci) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "%s: Unable to allocate EDAC device\n", ecc_name);
		rc = -ENOMEM;
		जाओ err_release_group;
	पूर्ण

	altdev = dci->pvt_info;
	dci->dev = edac->dev;
	altdev->edac_dev_name = ecc_name;
	altdev->edac_idx = edac_idx;
	altdev->edac = edac;
	altdev->edac_dev = dci;
	altdev->data = prv;
	altdev->ddev = *edac->dev;
	dci->dev = &altdev->ddev;
	dci->ctl_name = "Altera ECC Manager";
	dci->mod_name = ecc_name;
	dci->dev_name = ecc_name;

	altdev->base = devm_ioremap_resource(edac->dev, &res);
	अगर (IS_ERR(altdev->base)) अणु
		rc = PTR_ERR(altdev->base);
		जाओ err_release_group1;
	पूर्ण

	/* Check specअगरic dependencies क्रम the module */
	अगर (altdev->data->setup) अणु
		rc = altdev->data->setup(altdev);
		अगर (rc)
			जाओ err_release_group1;
	पूर्ण

	altdev->sb_irq = irq_of_parse_and_map(np, 0);
	अगर (!altdev->sb_irq) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "Error allocating SBIRQ\n");
		rc = -ENODEV;
		जाओ err_release_group1;
	पूर्ण
	rc = devm_request_irq(edac->dev, altdev->sb_irq, prv->ecc_irq_handler,
			      IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
			      ecc_name, altdev);
	अगर (rc) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "No SBERR IRQ resource\n");
		जाओ err_release_group1;
	पूर्ण

#अगर_घोषित CONFIG_64BIT
	/* Use IRQ to determine SError origin instead of assigning IRQ */
	rc = of_property_पढ़ो_u32_index(np, "interrupts", 0, &altdev->db_irq);
	अगर (rc) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "Unable to parse DB IRQ index\n");
		जाओ err_release_group1;
	पूर्ण
#अन्यथा
	altdev->db_irq = irq_of_parse_and_map(np, 1);
	अगर (!altdev->db_irq) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "Error allocating DBIRQ\n");
		rc = -ENODEV;
		जाओ err_release_group1;
	पूर्ण
	rc = devm_request_irq(edac->dev, altdev->db_irq, prv->ecc_irq_handler,
			      IRQF_ONESHOT | IRQF_TRIGGER_HIGH,
			      ecc_name, altdev);
	अगर (rc) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE, "No DBERR IRQ resource\n");
		जाओ err_release_group1;
	पूर्ण
#पूर्ण_अगर

	rc = edac_device_add_device(dci);
	अगर (rc) अणु
		dev_err(edac->dev, "edac_device_add_device failed\n");
		rc = -ENOMEM;
		जाओ err_release_group1;
	पूर्ण

	altr_create_edacdev_dbgfs(dci, prv);

	list_add(&altdev->next, &edac->a10_ecc_devices);

	devres_हटाओ_group(edac->dev, altr_edac_a10_device_add);

	वापस 0;

err_release_group1:
	edac_device_मुक्त_ctl_info(dci);
err_release_group:
	devres_release_group(edac->dev, शून्य);
	edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
		    "%s:Error setting up EDAC device: %d\n", ecc_name, rc);

	वापस rc;
पूर्ण

अटल व्योम a10_eccmgr_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा altr_arria10_edac *edac = irq_data_get_irq_chip_data(d);

	regmap_ग_लिखो(edac->ecc_mgr_map,	A10_SYSMGR_ECC_INTMASK_SET_OFST,
		     BIT(d->hwirq));
पूर्ण

अटल व्योम a10_eccmgr_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा altr_arria10_edac *edac = irq_data_get_irq_chip_data(d);

	regmap_ग_लिखो(edac->ecc_mgr_map,	A10_SYSMGR_ECC_INTMASK_CLR_OFST,
		     BIT(d->hwirq));
पूर्ण

अटल पूर्णांक a10_eccmgr_irqकरोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				    irq_hw_number_t hwirq)
अणु
	काष्ठा altr_arria10_edac *edac = d->host_data;

	irq_set_chip_and_handler(irq, &edac->irq_chip, handle_simple_irq);
	irq_set_chip_data(irq, edac);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops a10_eccmgr_ic_ops = अणु
	.map = a10_eccmgr_irqकरोमुख्य_map,
	.xlate = irq_करोमुख्य_xlate_twocell,
पूर्ण;

/************** Stratix 10 EDAC Double Bit Error Handler ************/
#घोषणा to_a10edac(p, m) container_of(p, काष्ठा altr_arria10_edac, m)

#अगर_घोषित CONFIG_64BIT
/* panic routine issues reboot on non-zero panic_समयout */
बाह्य पूर्णांक panic_समयout;

/*
 * The द्विगुन bit error is handled through SError which is fatal. This is
 * called as a panic notअगरier to prपूर्णांकout ECC error info as part of the panic.
 */
अटल पूर्णांक s10_edac_dberr_handler(काष्ठा notअगरier_block *this,
				  अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा altr_arria10_edac *edac = to_a10edac(this, panic_notअगरier);
	पूर्णांक err_addr, dberror;

	regmap_पढ़ो(edac->ecc_mgr_map, S10_SYSMGR_ECC_INTSTAT_DERR_OFST,
		    &dberror);
	regmap_ग_लिखो(edac->ecc_mgr_map, S10_SYSMGR_UE_VAL_OFST, dberror);
	अगर (dberror & S10_DBE_IRQ_MASK) अणु
		काष्ठा list_head *position;
		काष्ठा altr_edac_device_dev *ed;
		काष्ठा arm_smccc_res result;

		/* Find the matching DBE in the list of devices */
		list_क्रम_each(position, &edac->a10_ecc_devices) अणु
			ed = list_entry(position, काष्ठा altr_edac_device_dev,
					next);
			अगर (!(BIT(ed->db_irq) & dberror))
				जारी;

			ग_लिखोl(ALTR_A10_ECC_DERRPENA,
			       ed->base + ALTR_A10_ECC_INTSTAT_OFST);
			err_addr = पढ़ोl(ed->base + ALTR_S10_DERR_ADDRA_OFST);
			regmap_ग_लिखो(edac->ecc_mgr_map,
				     S10_SYSMGR_UE_ADDR_OFST, err_addr);
			edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
				    "EDAC: [Fatal DBE on %s @ 0x%08X]\n",
				    ed->edac_dev_name, err_addr);
			अवरोध;
		पूर्ण
		/* Notअगरy the System through SMC. Reboot delay = 1 second */
		panic_समयout = 1;
		arm_smccc_smc(INTEL_SIP_SMC_ECC_DBE, dberror, 0, 0, 0, 0,
			      0, 0, &result);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण
#पूर्ण_अगर

/****************** Arria 10 EDAC Probe Function *********************/
अटल पूर्णांक altr_edac_a10_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा altr_arria10_edac *edac;
	काष्ठा device_node *child;

	edac = devm_kzalloc(&pdev->dev, माप(*edac), GFP_KERNEL);
	अगर (!edac)
		वापस -ENOMEM;

	edac->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, edac);
	INIT_LIST_HEAD(&edac->a10_ecc_devices);

	edac->ecc_mgr_map =
		altr_sysmgr_regmap_lookup_by_phandle(pdev->dev.of_node,
						     "altr,sysmgr-syscon");

	अगर (IS_ERR(edac->ecc_mgr_map)) अणु
		edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
			    "Unable to get syscon altr,sysmgr-syscon\n");
		वापस PTR_ERR(edac->ecc_mgr_map);
	पूर्ण

	edac->irq_chip.name = pdev->dev.of_node->name;
	edac->irq_chip.irq_mask = a10_eccmgr_irq_mask;
	edac->irq_chip.irq_unmask = a10_eccmgr_irq_unmask;
	edac->करोमुख्य = irq_करोमुख्य_add_linear(pdev->dev.of_node, 64,
					     &a10_eccmgr_ic_ops, edac);
	अगर (!edac->करोमुख्य) अणु
		dev_err(&pdev->dev, "Error adding IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	edac->sb_irq = platक्रमm_get_irq(pdev, 0);
	अगर (edac->sb_irq < 0) अणु
		dev_err(&pdev->dev, "No SBERR IRQ resource\n");
		वापस edac->sb_irq;
	पूर्ण

	irq_set_chained_handler_and_data(edac->sb_irq,
					 altr_edac_a10_irq_handler,
					 edac);

#अगर_घोषित CONFIG_64BIT
	अणु
		पूर्णांक dberror, err_addr;

		edac->panic_notअगरier.notअगरier_call = s10_edac_dberr_handler;
		atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
					       &edac->panic_notअगरier);

		/* Prपूर्णांकout a message अगर uncorrectable error previously. */
		regmap_पढ़ो(edac->ecc_mgr_map, S10_SYSMGR_UE_VAL_OFST,
			    &dberror);
		अगर (dberror) अणु
			regmap_पढ़ो(edac->ecc_mgr_map, S10_SYSMGR_UE_ADDR_OFST,
				    &err_addr);
			edac_prपूर्णांकk(KERN_ERR, EDAC_DEVICE,
				    "Previous Boot UE detected[0x%X] @ 0x%X\n",
				    dberror, err_addr);
			/* Reset the sticky रेजिस्टरs */
			regmap_ग_लिखो(edac->ecc_mgr_map,
				     S10_SYSMGR_UE_VAL_OFST, 0);
			regmap_ग_लिखो(edac->ecc_mgr_map,
				     S10_SYSMGR_UE_ADDR_OFST, 0);
		पूर्ण
	पूर्ण
#अन्यथा
	edac->db_irq = platक्रमm_get_irq(pdev, 1);
	अगर (edac->db_irq < 0) अणु
		dev_err(&pdev->dev, "No DBERR IRQ resource\n");
		वापस edac->db_irq;
	पूर्ण
	irq_set_chained_handler_and_data(edac->db_irq,
					 altr_edac_a10_irq_handler, edac);
#पूर्ण_अगर

	क्रम_each_child_of_node(pdev->dev.of_node, child) अणु
		अगर (!of_device_is_available(child))
			जारी;

		अगर (of_match_node(altr_edac_a10_device_of_match, child))
			altr_edac_a10_device_add(edac, child);

#अगर_घोषित CONFIG_EDAC_ALTERA_SDRAM
		अन्यथा अगर (of_device_is_compatible(child, "altr,sdram-edac-a10"))
			of_platक्रमm_populate(pdev->dev.of_node,
					     altr_sdram_ctrl_of_match,
					     शून्य, &pdev->dev);
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id altr_edac_a10_of_match[] = अणु
	अणु .compatible = "altr,socfpga-a10-ecc-manager" पूर्ण,
	अणु .compatible = "altr,socfpga-s10-ecc-manager" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, altr_edac_a10_of_match);

अटल काष्ठा platक्रमm_driver altr_edac_a10_driver = अणु
	.probe =  altr_edac_a10_probe,
	.driver = अणु
		.name = "socfpga_a10_ecc_manager",
		.of_match_table = altr_edac_a10_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(altr_edac_a10_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Thor Thayer");
MODULE_DESCRIPTION("EDAC Driver for Altera Memories");
