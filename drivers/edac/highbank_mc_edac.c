<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2011-2012 Calxeda, Inc.
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/edac.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/uaccess.h>

#समावेश "edac_module.h"

/* DDR Ctrlr Error Registers */

#घोषणा HB_DDR_ECC_ERR_BASE		0x128
#घोषणा MW_DDR_ECC_ERR_BASE		0x1b4

#घोषणा HB_DDR_ECC_OPT			0x00
#घोषणा HB_DDR_ECC_U_ERR_ADDR		0x08
#घोषणा HB_DDR_ECC_U_ERR_STAT		0x0c
#घोषणा HB_DDR_ECC_U_ERR_DATAL		0x10
#घोषणा HB_DDR_ECC_U_ERR_DATAH		0x14
#घोषणा HB_DDR_ECC_C_ERR_ADDR		0x18
#घोषणा HB_DDR_ECC_C_ERR_STAT		0x1c
#घोषणा HB_DDR_ECC_C_ERR_DATAL		0x20
#घोषणा HB_DDR_ECC_C_ERR_DATAH		0x24

#घोषणा HB_DDR_ECC_OPT_MODE_MASK	0x3
#घोषणा HB_DDR_ECC_OPT_FWC		0x100
#घोषणा HB_DDR_ECC_OPT_XOR_SHIFT	16

/* DDR Ctrlr Interrupt Registers */

#घोषणा HB_DDR_ECC_INT_BASE		0x180
#घोषणा MW_DDR_ECC_INT_BASE		0x218

#घोषणा HB_DDR_ECC_INT_STATUS		0x00
#घोषणा HB_DDR_ECC_INT_ACK		0x04

#घोषणा HB_DDR_ECC_INT_STAT_CE		0x8
#घोषणा HB_DDR_ECC_INT_STAT_DOUBLE_CE	0x10
#घोषणा HB_DDR_ECC_INT_STAT_UE		0x20
#घोषणा HB_DDR_ECC_INT_STAT_DOUBLE_UE	0x40

काष्ठा hb_mc_drvdata अणु
	व्योम __iomem *mc_err_base;
	व्योम __iomem *mc_पूर्णांक_base;
पूर्ण;

अटल irqवापस_t highbank_mc_err_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mem_ctl_info *mci = dev_id;
	काष्ठा hb_mc_drvdata *drvdata = mci->pvt_info;
	u32 status, err_addr;

	/* Read the पूर्णांकerrupt status रेजिस्टर */
	status = पढ़ोl(drvdata->mc_पूर्णांक_base + HB_DDR_ECC_INT_STATUS);

	अगर (status & HB_DDR_ECC_INT_STAT_UE) अणु
		err_addr = पढ़ोl(drvdata->mc_err_base + HB_DDR_ECC_U_ERR_ADDR);
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     err_addr >> PAGE_SHIFT,
				     err_addr & ~PAGE_MASK, 0,
				     0, 0, -1,
				     mci->ctl_name, "");
	पूर्ण
	अगर (status & HB_DDR_ECC_INT_STAT_CE) अणु
		u32 syndrome = पढ़ोl(drvdata->mc_err_base + HB_DDR_ECC_C_ERR_STAT);
		syndrome = (syndrome >> 8) & 0xff;
		err_addr = पढ़ोl(drvdata->mc_err_base + HB_DDR_ECC_C_ERR_ADDR);
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
				     err_addr >> PAGE_SHIFT,
				     err_addr & ~PAGE_MASK, syndrome,
				     0, 0, -1,
				     mci->ctl_name, "");
	पूर्ण

	/* clear the error, clears the पूर्णांकerrupt */
	ग_लिखोl(status, drvdata->mc_पूर्णांक_base + HB_DDR_ECC_INT_ACK);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम highbank_mc_err_inject(काष्ठा mem_ctl_info *mci, u8 synd)
अणु
	काष्ठा hb_mc_drvdata *pdata = mci->pvt_info;
	u32 reg;

	reg = पढ़ोl(pdata->mc_err_base + HB_DDR_ECC_OPT);
	reg &= HB_DDR_ECC_OPT_MODE_MASK;
	reg |= (synd << HB_DDR_ECC_OPT_XOR_SHIFT) | HB_DDR_ECC_OPT_FWC;
	ग_लिखोl(reg, pdata->mc_err_base + HB_DDR_ECC_OPT);
पूर्ण

#घोषणा to_mci(k) container_of(k, काष्ठा mem_ctl_info, dev)

अटल sमाप_प्रकार highbank_mc_inject_ctrl(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा mem_ctl_info *mci = to_mci(dev);
	u8 synd;

	अगर (kstrtou8(buf, 16, &synd))
		वापस -EINVAL;

	highbank_mc_err_inject(mci, synd);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(inject_ctrl, S_IWUSR, शून्य, highbank_mc_inject_ctrl);

अटल काष्ठा attribute *highbank_dev_attrs[] = अणु
	&dev_attr_inject_ctrl.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(highbank_dev);

काष्ठा hb_mc_settings अणु
	पूर्णांक	err_offset;
	पूर्णांक	पूर्णांक_offset;
पूर्ण;

अटल काष्ठा hb_mc_settings hb_settings = अणु
	.err_offset = HB_DDR_ECC_ERR_BASE,
	.पूर्णांक_offset = HB_DDR_ECC_INT_BASE,
पूर्ण;

अटल काष्ठा hb_mc_settings mw_settings = अणु
	.err_offset = MW_DDR_ECC_ERR_BASE,
	.पूर्णांक_offset = MW_DDR_ECC_INT_BASE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hb_ddr_ctrl_of_match[] = अणु
	अणु .compatible = "calxeda,hb-ddr-ctrl",		.data = &hb_settings पूर्ण,
	अणु .compatible = "calxeda,ecx-2000-ddr-ctrl",	.data = &mw_settings पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hb_ddr_ctrl_of_match);

अटल पूर्णांक highbank_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id;
	स्थिर काष्ठा hb_mc_settings *settings;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा mem_ctl_info *mci;
	काष्ठा hb_mc_drvdata *drvdata;
	काष्ठा dimm_info *dimm;
	काष्ठा resource *r;
	व्योम __iomem *base;
	u32 control;
	पूर्णांक irq;
	पूर्णांक res = 0;

	id = of_match_device(hb_ddr_ctrl_of_match, &pdev->dev);
	अगर (!id)
		वापस -ENODEV;

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = 1;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = 1;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers,
			    माप(काष्ठा hb_mc_drvdata));
	अगर (!mci)
		वापस -ENOMEM;

	mci->pdev = &pdev->dev;
	drvdata = mci->pvt_info;
	platक्रमm_set_drvdata(pdev, mci);

	अगर (!devres_खोलो_group(&pdev->dev, शून्य, GFP_KERNEL))
		वापस -ENOMEM;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "Unable to get mem resource\n");
		res = -ENODEV;
		जाओ err;
	पूर्ण

	अगर (!devm_request_mem_region(&pdev->dev, r->start,
				     resource_size(r), dev_name(&pdev->dev))) अणु
		dev_err(&pdev->dev, "Error while requesting mem region\n");
		res = -EBUSY;
		जाओ err;
	पूर्ण

	base = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!base) अणु
		dev_err(&pdev->dev, "Unable to map regs\n");
		res = -ENOMEM;
		जाओ err;
	पूर्ण

	settings = id->data;
	drvdata->mc_err_base = base + settings->err_offset;
	drvdata->mc_पूर्णांक_base = base + settings->पूर्णांक_offset;

	control = पढ़ोl(drvdata->mc_err_base + HB_DDR_ECC_OPT) & 0x3;
	अगर (!control || (control == 0x2)) अणु
		dev_err(&pdev->dev, "No ECC present, or ECC disabled\n");
		res = -ENODEV;
		जाओ err;
	पूर्ण

	mci->mtype_cap = MEM_FLAG_DDR3;
	mci->edac_ctl_cap = EDAC_FLAG_NONE | EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = pdev->dev.driver->name;
	mci->ctl_name = id->compatible;
	mci->dev_name = dev_name(&pdev->dev);
	mci->scrub_mode = SCRUB_SW_SRC;

	/* Only a single 4GB DIMM is supported */
	dimm = *mci->dimms;
	dimm->nr_pages = (~0UL >> PAGE_SHIFT) + 1;
	dimm->grain = 8;
	dimm->dtype = DEV_X8;
	dimm->mtype = MEM_DDR3;
	dimm->edac_mode = EDAC_SECDED;

	res = edac_mc_add_mc_with_groups(mci, highbank_dev_groups);
	अगर (res < 0)
		जाओ err;

	irq = platक्रमm_get_irq(pdev, 0);
	res = devm_request_irq(&pdev->dev, irq, highbank_mc_err_handler,
			       0, dev_name(&pdev->dev), mci);
	अगर (res < 0) अणु
		dev_err(&pdev->dev, "Unable to request irq %d\n", irq);
		जाओ err2;
	पूर्ण

	devres_बंद_group(&pdev->dev, शून्य);
	वापस 0;
err2:
	edac_mc_del_mc(&pdev->dev);
err:
	devres_release_group(&pdev->dev, शून्य);
	edac_mc_मुक्त(mci);
	वापस res;
पूर्ण

अटल पूर्णांक highbank_mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mem_ctl_info *mci = platक्रमm_get_drvdata(pdev);

	edac_mc_del_mc(&pdev->dev);
	edac_mc_मुक्त(mci);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver highbank_mc_edac_driver = अणु
	.probe = highbank_mc_probe,
	.हटाओ = highbank_mc_हटाओ,
	.driver = अणु
		.name = "hb_mc_edac",
		.of_match_table = hb_ddr_ctrl_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(highbank_mc_edac_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Calxeda, Inc.");
MODULE_DESCRIPTION("EDAC Driver for Calxeda Highbank");
