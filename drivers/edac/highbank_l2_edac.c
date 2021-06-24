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

#समावेश "edac_module.h"

#घोषणा SR_CLR_SB_ECC_INTR	0x0
#घोषणा SR_CLR_DB_ECC_INTR	0x4

काष्ठा hb_l2_drvdata अणु
	व्योम __iomem *base;
	पूर्णांक sb_irq;
	पूर्णांक db_irq;
पूर्ण;

अटल irqवापस_t highbank_l2_err_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा edac_device_ctl_info *dci = dev_id;
	काष्ठा hb_l2_drvdata *drvdata = dci->pvt_info;

	अगर (irq == drvdata->sb_irq) अणु
		ग_लिखोl(1, drvdata->base + SR_CLR_SB_ECC_INTR);
		edac_device_handle_ce(dci, 0, 0, dci->ctl_name);
	पूर्ण
	अगर (irq == drvdata->db_irq) अणु
		ग_लिखोl(1, drvdata->base + SR_CLR_DB_ECC_INTR);
		edac_device_handle_ue(dci, 0, 0, dci->ctl_name);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id hb_l2_err_of_match[] = अणु
	अणु .compatible = "calxeda,hb-sregs-l2-ecc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hb_l2_err_of_match);

अटल पूर्णांक highbank_l2_err_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id;
	काष्ठा edac_device_ctl_info *dci;
	काष्ठा hb_l2_drvdata *drvdata;
	काष्ठा resource *r;
	पूर्णांक res = 0;

	dci = edac_device_alloc_ctl_info(माप(*drvdata), "cpu",
		1, "L", 1, 2, शून्य, 0, 0);
	अगर (!dci)
		वापस -ENOMEM;

	drvdata = dci->pvt_info;
	dci->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dci);

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

	drvdata->base = devm_ioremap(&pdev->dev, r->start, resource_size(r));
	अगर (!drvdata->base) अणु
		dev_err(&pdev->dev, "Unable to map regs\n");
		res = -ENOMEM;
		जाओ err;
	पूर्ण

	id = of_match_device(hb_l2_err_of_match, &pdev->dev);
	dci->mod_name = pdev->dev.driver->name;
	dci->ctl_name = id ? id->compatible : "unknown";
	dci->dev_name = dev_name(&pdev->dev);

	अगर (edac_device_add_device(dci))
		जाओ err;

	drvdata->db_irq = platक्रमm_get_irq(pdev, 0);
	res = devm_request_irq(&pdev->dev, drvdata->db_irq,
			       highbank_l2_err_handler,
			       0, dev_name(&pdev->dev), dci);
	अगर (res < 0)
		जाओ err2;

	drvdata->sb_irq = platक्रमm_get_irq(pdev, 1);
	res = devm_request_irq(&pdev->dev, drvdata->sb_irq,
			       highbank_l2_err_handler,
			       0, dev_name(&pdev->dev), dci);
	अगर (res < 0)
		जाओ err2;

	devres_बंद_group(&pdev->dev, शून्य);
	वापस 0;
err2:
	edac_device_del_device(&pdev->dev);
err:
	devres_release_group(&pdev->dev, शून्य);
	edac_device_मुक्त_ctl_info(dci);
	वापस res;
पूर्ण

अटल पूर्णांक highbank_l2_err_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा edac_device_ctl_info *dci = platक्रमm_get_drvdata(pdev);

	edac_device_del_device(&pdev->dev);
	edac_device_मुक्त_ctl_info(dci);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver highbank_l2_edac_driver = अणु
	.probe = highbank_l2_err_probe,
	.हटाओ = highbank_l2_err_हटाओ,
	.driver = अणु
		.name = "hb_l2_edac",
		.of_match_table = hb_l2_err_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(highbank_l2_edac_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Calxeda, Inc.");
MODULE_DESCRIPTION("EDAC Driver for Calxeda Highbank L2 Cache");
