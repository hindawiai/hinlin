<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Qualcomm Technologies HIDMA DMA engine Management पूर्णांकerface
 *
 * Copyright (c) 2015-2017, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/dmaengine.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of.h>
#समावेश <linux/property.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>

#समावेश "hidma_mgmt.h"

#घोषणा HIDMA_QOS_N_OFFSET		0x700
#घोषणा HIDMA_CFG_OFFSET		0x400
#घोषणा HIDMA_MAX_BUS_REQ_LEN_OFFSET	0x41C
#घोषणा HIDMA_MAX_XACTIONS_OFFSET	0x420
#घोषणा HIDMA_HW_VERSION_OFFSET	0x424
#घोषणा HIDMA_CHRESET_TIMEOUT_OFFSET	0x418

#घोषणा HIDMA_MAX_WR_XACTIONS_MASK	GENMASK(4, 0)
#घोषणा HIDMA_MAX_RD_XACTIONS_MASK	GENMASK(4, 0)
#घोषणा HIDMA_WEIGHT_MASK		GENMASK(6, 0)
#घोषणा HIDMA_MAX_BUS_REQ_LEN_MASK	GENMASK(15, 0)
#घोषणा HIDMA_CHRESET_TIMEOUT_MASK	GENMASK(19, 0)

#घोषणा HIDMA_MAX_WR_XACTIONS_BIT_POS	16
#घोषणा HIDMA_MAX_BUS_WR_REQ_BIT_POS	16
#घोषणा HIDMA_WRR_BIT_POS		8
#घोषणा HIDMA_PRIORITY_BIT_POS		15

#घोषणा HIDMA_AUTOSUSPEND_TIMEOUT	2000
#घोषणा HIDMA_MAX_CHANNEL_WEIGHT	15

अटल अचिन्हित पूर्णांक max_ग_लिखो_request;
module_param(max_ग_लिखो_request, uपूर्णांक, 0644);
MODULE_PARM_DESC(max_ग_लिखो_request,
		"maximum write burst (default: ACPI/DT value)");

अटल अचिन्हित पूर्णांक max_पढ़ो_request;
module_param(max_पढ़ो_request, uपूर्णांक, 0644);
MODULE_PARM_DESC(max_पढ़ो_request,
		"maximum read burst (default: ACPI/DT value)");

अटल अचिन्हित पूर्णांक max_wr_xactions;
module_param(max_wr_xactions, uपूर्णांक, 0644);
MODULE_PARM_DESC(max_wr_xactions,
	"maximum number of write transactions (default: ACPI/DT value)");

अटल अचिन्हित पूर्णांक max_rd_xactions;
module_param(max_rd_xactions, uपूर्णांक, 0644);
MODULE_PARM_DESC(max_rd_xactions,
	"maximum number of read transactions (default: ACPI/DT value)");

पूर्णांक hidma_mgmt_setup(काष्ठा hidma_mgmt_dev *mgmtdev)
अणु
	अचिन्हित पूर्णांक i;
	u32 val;

	अगर (!is_घातer_of_2(mgmtdev->max_ग_लिखो_request) ||
	    (mgmtdev->max_ग_लिखो_request < 128) ||
	    (mgmtdev->max_ग_लिखो_request > 1024)) अणु
		dev_err(&mgmtdev->pdev->dev, "invalid write request %d\n",
			mgmtdev->max_ग_लिखो_request);
		वापस -EINVAL;
	पूर्ण

	अगर (!is_घातer_of_2(mgmtdev->max_पढ़ो_request) ||
	    (mgmtdev->max_पढ़ो_request < 128) ||
	    (mgmtdev->max_पढ़ो_request > 1024)) अणु
		dev_err(&mgmtdev->pdev->dev, "invalid read request %d\n",
			mgmtdev->max_पढ़ो_request);
		वापस -EINVAL;
	पूर्ण

	अगर (mgmtdev->max_wr_xactions > HIDMA_MAX_WR_XACTIONS_MASK) अणु
		dev_err(&mgmtdev->pdev->dev,
			"max_wr_xactions cannot be bigger than %ld\n",
			HIDMA_MAX_WR_XACTIONS_MASK);
		वापस -EINVAL;
	पूर्ण

	अगर (mgmtdev->max_rd_xactions > HIDMA_MAX_RD_XACTIONS_MASK) अणु
		dev_err(&mgmtdev->pdev->dev,
			"max_rd_xactions cannot be bigger than %ld\n",
			HIDMA_MAX_RD_XACTIONS_MASK);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < mgmtdev->dma_channels; i++) अणु
		अगर (mgmtdev->priority[i] > 1) अणु
			dev_err(&mgmtdev->pdev->dev,
				"priority can be 0 or 1\n");
			वापस -EINVAL;
		पूर्ण

		अगर (mgmtdev->weight[i] > HIDMA_MAX_CHANNEL_WEIGHT) अणु
			dev_err(&mgmtdev->pdev->dev,
				"max value of weight can be %d.\n",
				HIDMA_MAX_CHANNEL_WEIGHT);
			वापस -EINVAL;
		पूर्ण

		/* weight needs to be at least one */
		अगर (mgmtdev->weight[i] == 0)
			mgmtdev->weight[i] = 1;
	पूर्ण

	pm_runसमय_get_sync(&mgmtdev->pdev->dev);
	val = पढ़ोl(mgmtdev->virtaddr + HIDMA_MAX_BUS_REQ_LEN_OFFSET);
	val &= ~(HIDMA_MAX_BUS_REQ_LEN_MASK << HIDMA_MAX_BUS_WR_REQ_BIT_POS);
	val |= mgmtdev->max_ग_लिखो_request << HIDMA_MAX_BUS_WR_REQ_BIT_POS;
	val &= ~HIDMA_MAX_BUS_REQ_LEN_MASK;
	val |= mgmtdev->max_पढ़ो_request;
	ग_लिखोl(val, mgmtdev->virtaddr + HIDMA_MAX_BUS_REQ_LEN_OFFSET);

	val = पढ़ोl(mgmtdev->virtaddr + HIDMA_MAX_XACTIONS_OFFSET);
	val &= ~(HIDMA_MAX_WR_XACTIONS_MASK << HIDMA_MAX_WR_XACTIONS_BIT_POS);
	val |= mgmtdev->max_wr_xactions << HIDMA_MAX_WR_XACTIONS_BIT_POS;
	val &= ~HIDMA_MAX_RD_XACTIONS_MASK;
	val |= mgmtdev->max_rd_xactions;
	ग_लिखोl(val, mgmtdev->virtaddr + HIDMA_MAX_XACTIONS_OFFSET);

	mgmtdev->hw_version =
	    पढ़ोl(mgmtdev->virtaddr + HIDMA_HW_VERSION_OFFSET);
	mgmtdev->hw_version_major = (mgmtdev->hw_version >> 28) & 0xF;
	mgmtdev->hw_version_minor = (mgmtdev->hw_version >> 16) & 0xF;

	क्रम (i = 0; i < mgmtdev->dma_channels; i++) अणु
		u32 weight = mgmtdev->weight[i];
		u32 priority = mgmtdev->priority[i];

		val = पढ़ोl(mgmtdev->virtaddr + HIDMA_QOS_N_OFFSET + (4 * i));
		val &= ~(1 << HIDMA_PRIORITY_BIT_POS);
		val |= (priority & 0x1) << HIDMA_PRIORITY_BIT_POS;
		val &= ~(HIDMA_WEIGHT_MASK << HIDMA_WRR_BIT_POS);
		val |= (weight & HIDMA_WEIGHT_MASK) << HIDMA_WRR_BIT_POS;
		ग_लिखोl(val, mgmtdev->virtaddr + HIDMA_QOS_N_OFFSET + (4 * i));
	पूर्ण

	val = पढ़ोl(mgmtdev->virtaddr + HIDMA_CHRESET_TIMEOUT_OFFSET);
	val &= ~HIDMA_CHRESET_TIMEOUT_MASK;
	val |= mgmtdev->chreset_समयout_cycles & HIDMA_CHRESET_TIMEOUT_MASK;
	ग_लिखोl(val, mgmtdev->virtaddr + HIDMA_CHRESET_TIMEOUT_OFFSET);

	pm_runसमय_mark_last_busy(&mgmtdev->pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&mgmtdev->pdev->dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hidma_mgmt_setup);

अटल पूर्णांक hidma_mgmt_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hidma_mgmt_dev *mgmtdev;
	काष्ठा resource *res;
	व्योम __iomem *virtaddr;
	पूर्णांक irq;
	पूर्णांक rc;
	u32 val;

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, HIDMA_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	virtaddr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(virtaddr)) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		rc = irq;
		जाओ out;
	पूर्ण

	mgmtdev = devm_kzalloc(&pdev->dev, माप(*mgmtdev), GFP_KERNEL);
	अगर (!mgmtdev) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	mgmtdev->pdev = pdev;
	mgmtdev->addrsize = resource_size(res);
	mgmtdev->virtaddr = virtaddr;

	rc = device_property_पढ़ो_u32(&pdev->dev, "dma-channels",
				      &mgmtdev->dma_channels);
	अगर (rc) अणु
		dev_err(&pdev->dev, "number of channels missing\n");
		जाओ out;
	पूर्ण

	rc = device_property_पढ़ो_u32(&pdev->dev,
				      "channel-reset-timeout-cycles",
				      &mgmtdev->chreset_समयout_cycles);
	अगर (rc) अणु
		dev_err(&pdev->dev, "channel reset timeout missing\n");
		जाओ out;
	पूर्ण

	rc = device_property_पढ़ो_u32(&pdev->dev, "max-write-burst-bytes",
				      &mgmtdev->max_ग_लिखो_request);
	अगर (rc) अणु
		dev_err(&pdev->dev, "max-write-burst-bytes missing\n");
		जाओ out;
	पूर्ण

	अगर (max_ग_लिखो_request &&
			(max_ग_लिखो_request != mgmtdev->max_ग_लिखो_request)) अणु
		dev_info(&pdev->dev, "overriding max-write-burst-bytes: %d\n",
			max_ग_लिखो_request);
		mgmtdev->max_ग_लिखो_request = max_ग_लिखो_request;
	पूर्ण अन्यथा
		max_ग_लिखो_request = mgmtdev->max_ग_लिखो_request;

	rc = device_property_पढ़ो_u32(&pdev->dev, "max-read-burst-bytes",
				      &mgmtdev->max_पढ़ो_request);
	अगर (rc) अणु
		dev_err(&pdev->dev, "max-read-burst-bytes missing\n");
		जाओ out;
	पूर्ण
	अगर (max_पढ़ो_request &&
			(max_पढ़ो_request != mgmtdev->max_पढ़ो_request)) अणु
		dev_info(&pdev->dev, "overriding max-read-burst-bytes: %d\n",
			max_पढ़ो_request);
		mgmtdev->max_पढ़ो_request = max_पढ़ो_request;
	पूर्ण अन्यथा
		max_पढ़ो_request = mgmtdev->max_पढ़ो_request;

	rc = device_property_पढ़ो_u32(&pdev->dev, "max-write-transactions",
				      &mgmtdev->max_wr_xactions);
	अगर (rc) अणु
		dev_err(&pdev->dev, "max-write-transactions missing\n");
		जाओ out;
	पूर्ण
	अगर (max_wr_xactions &&
			(max_wr_xactions != mgmtdev->max_wr_xactions)) अणु
		dev_info(&pdev->dev, "overriding max-write-transactions: %d\n",
			max_wr_xactions);
		mgmtdev->max_wr_xactions = max_wr_xactions;
	पूर्ण अन्यथा
		max_wr_xactions = mgmtdev->max_wr_xactions;

	rc = device_property_पढ़ो_u32(&pdev->dev, "max-read-transactions",
				      &mgmtdev->max_rd_xactions);
	अगर (rc) अणु
		dev_err(&pdev->dev, "max-read-transactions missing\n");
		जाओ out;
	पूर्ण
	अगर (max_rd_xactions &&
			(max_rd_xactions != mgmtdev->max_rd_xactions)) अणु
		dev_info(&pdev->dev, "overriding max-read-transactions: %d\n",
			max_rd_xactions);
		mgmtdev->max_rd_xactions = max_rd_xactions;
	पूर्ण अन्यथा
		max_rd_xactions = mgmtdev->max_rd_xactions;

	mgmtdev->priority = devm_kसुस्मृति(&pdev->dev,
					 mgmtdev->dma_channels,
					 माप(*mgmtdev->priority),
					 GFP_KERNEL);
	अगर (!mgmtdev->priority) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	mgmtdev->weight = devm_kसुस्मृति(&pdev->dev,
				       mgmtdev->dma_channels,
				       माप(*mgmtdev->weight), GFP_KERNEL);
	अगर (!mgmtdev->weight) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	rc = hidma_mgmt_setup(mgmtdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "setup failed\n");
		जाओ out;
	पूर्ण

	/* start the HW */
	val = पढ़ोl(mgmtdev->virtaddr + HIDMA_CFG_OFFSET);
	val |= 1;
	ग_लिखोl(val, mgmtdev->virtaddr + HIDMA_CFG_OFFSET);

	rc = hidma_mgmt_init_sys(mgmtdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "sysfs setup failed\n");
		जाओ out;
	पूर्ण

	dev_info(&pdev->dev,
		 "HW rev: %d.%d @ %pa with %d physical channels\n",
		 mgmtdev->hw_version_major, mgmtdev->hw_version_minor,
		 &res->start, mgmtdev->dma_channels);

	platक्रमm_set_drvdata(pdev, mgmtdev);
	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);
	वापस 0;
out:
	pm_runसमय_put_sync_suspend(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस rc;
पूर्ण

#अगर IS_ENABLED(CONFIG_ACPI)
अटल स्थिर काष्ठा acpi_device_id hidma_mgmt_acpi_ids[] = अणु
	अणु"QCOM8060"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, hidma_mgmt_acpi_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id hidma_mgmt_match[] = अणु
	अणु.compatible = "qcom,hidma-mgmt-1.0",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hidma_mgmt_match);

अटल काष्ठा platक्रमm_driver hidma_mgmt_driver = अणु
	.probe = hidma_mgmt_probe,
	.driver = अणु
		   .name = "hidma-mgmt",
		   .of_match_table = hidma_mgmt_match,
		   .acpi_match_table = ACPI_PTR(hidma_mgmt_acpi_ids),
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_OF) && defined(CONFIG_OF_IRQ)
अटल पूर्णांक object_counter;

अटल पूर्णांक __init hidma_mgmt_of_populate_channels(काष्ठा device_node *np)
अणु
	काष्ठा platक्रमm_device *pdev_parent = of_find_device_by_node(np);
	काष्ठा platक्रमm_device_info pdevinfo;
	काष्ठा device_node *child;
	काष्ठा resource *res;
	पूर्णांक ret = 0;

	/* allocate a resource array */
	res = kसुस्मृति(3, माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा platक्रमm_device *new_pdev;

		ret = of_address_to_resource(child, 0, &res[0]);
		अगर (!ret)
			जाओ out;

		ret = of_address_to_resource(child, 1, &res[1]);
		अगर (!ret)
			जाओ out;

		ret = of_irq_to_resource(child, 0, &res[2]);
		अगर (ret <= 0)
			जाओ out;

		स_रखो(&pdevinfo, 0, माप(pdevinfo));
		pdevinfo.fwnode = &child->fwnode;
		pdevinfo.parent = pdev_parent ? &pdev_parent->dev : शून्य;
		pdevinfo.name = child->name;
		pdevinfo.id = object_counter++;
		pdevinfo.res = res;
		pdevinfo.num_res = 3;
		pdevinfo.data = शून्य;
		pdevinfo.size_data = 0;
		pdevinfo.dma_mask = DMA_BIT_MASK(64);
		new_pdev = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
		अगर (IS_ERR(new_pdev)) अणु
			ret = PTR_ERR(new_pdev);
			जाओ out;
		पूर्ण
		new_pdev->dev.of_node = child;
		of_dma_configure(&new_pdev->dev, child, true);
		/*
		 * It is assumed that calling of_msi_configure is safe on
		 * platक्रमms with or without MSI support.
		 */
		of_msi_configure(&new_pdev->dev, child);
	पूर्ण

	kमुक्त(res);

	वापस ret;

out:
	of_node_put(child);
	kमुक्त(res);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init hidma_mgmt_init(व्योम)
अणु
#अगर defined(CONFIG_OF) && defined(CONFIG_OF_IRQ)
	काष्ठा device_node *child;

	क्रम_each_matching_node(child, hidma_mgmt_match) अणु
		/* device tree based firmware here */
		hidma_mgmt_of_populate_channels(child);
	पूर्ण
#पूर्ण_अगर
	/*
	 * We करो not check क्रम वापस value here, as it is assumed that
	 * platक्रमm_driver_रेजिस्टर must not fail. The reason क्रम this is that
	 * the (potential) hidma_mgmt_of_populate_channels calls above are not
	 * cleaned up अगर it करोes fail, and to करो this work is quite
	 * complicated. In particular, various calls of of_address_to_resource,
	 * of_irq_to_resource, platक्रमm_device_रेजिस्टर_full, of_dma_configure,
	 * and of_msi_configure which then call other functions and so on, must
	 * be cleaned up - this is not a trivial exercise.
	 *
	 * Currently, this module is not पूर्णांकended to be unloaded, and there is
	 * no module_निकास function defined which करोes the needed cleanup. For
	 * this reason, we have to assume success here.
	 */
	platक्रमm_driver_रेजिस्टर(&hidma_mgmt_driver);

	वापस 0;
पूर्ण
module_init(hidma_mgmt_init);
MODULE_LICENSE("GPL v2");
