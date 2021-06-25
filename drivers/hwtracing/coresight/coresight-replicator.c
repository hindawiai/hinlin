<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2015, The Linux Foundation. All rights reserved.
 *
 * Description: CoreSight Replicator driver
 */

#समावेश <linux/acpi.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/coresight.h>

#समावेश "coresight-priv.h"

#घोषणा REPLICATOR_IDFILTER0		0x000
#घोषणा REPLICATOR_IDFILTER1		0x004

DEFINE_CORESIGHT_DEVLIST(replicator_devs, "replicator");

/**
 * काष्ठा replicator_drvdata - specअगरics associated to a replicator component
 * @base:	memory mapped base address क्रम this component. Also indicates
 *		whether this one is programmable or not.
 * @atclk:	optional घड़ी क्रम the core parts of the replicator.
 * @csdev:	component vitals needed by the framework
 * @spinlock:	serialize enable/disable operations.
 * @check_idfilter_val: check अगर the context is lost upon घड़ी removal.
 */
काष्ठा replicator_drvdata अणु
	व्योम __iomem		*base;
	काष्ठा clk		*atclk;
	काष्ठा coresight_device	*csdev;
	spinlock_t		spinlock;
	bool			check_idfilter_val;
पूर्ण;

अटल व्योम dynamic_replicator_reset(काष्ठा replicator_drvdata *drvdata)
अणु
	काष्ठा coresight_device *csdev = drvdata->csdev;

	CS_UNLOCK(drvdata->base);

	अगर (!coresight_claim_device_unlocked(csdev)) अणु
		ग_लिखोl_relaxed(0xff, drvdata->base + REPLICATOR_IDFILTER0);
		ग_लिखोl_relaxed(0xff, drvdata->base + REPLICATOR_IDFILTER1);
		coresight_disclaim_device_unlocked(csdev);
	पूर्ण

	CS_LOCK(drvdata->base);
पूर्ण

/*
 * replicator_reset : Reset the replicator configuration to sane values.
 */
अटल अंतरभूत व्योम replicator_reset(काष्ठा replicator_drvdata *drvdata)
अणु
	अगर (drvdata->base)
		dynamic_replicator_reset(drvdata);
पूर्ण

अटल पूर्णांक dynamic_replicator_enable(काष्ठा replicator_drvdata *drvdata,
				     पूर्णांक inport, पूर्णांक outport)
अणु
	पूर्णांक rc = 0;
	u32 id0val, id1val;
	काष्ठा coresight_device *csdev = drvdata->csdev;

	CS_UNLOCK(drvdata->base);

	id0val = पढ़ोl_relaxed(drvdata->base + REPLICATOR_IDFILTER0);
	id1val = पढ़ोl_relaxed(drvdata->base + REPLICATOR_IDFILTER1);

	/*
	 * Some replicator designs lose context when AMBA घड़ीs are हटाओd,
	 * so have a check क्रम this.
	 */
	अगर (drvdata->check_idfilter_val && id0val == 0x0 && id1val == 0x0)
		id0val = id1val = 0xff;

	अगर (id0val == 0xff && id1val == 0xff)
		rc = coresight_claim_device_unlocked(csdev);

	अगर (!rc) अणु
		चयन (outport) अणु
		हाल 0:
			id0val = 0x0;
			अवरोध;
		हाल 1:
			id1val = 0x0;
			अवरोध;
		शेष:
			WARN_ON(1);
			rc = -EINVAL;
		पूर्ण
	पूर्ण

	/* Ensure that the outport is enabled. */
	अगर (!rc) अणु
		ग_लिखोl_relaxed(id0val, drvdata->base + REPLICATOR_IDFILTER0);
		ग_लिखोl_relaxed(id1val, drvdata->base + REPLICATOR_IDFILTER1);
	पूर्ण

	CS_LOCK(drvdata->base);

	वापस rc;
पूर्ण

अटल पूर्णांक replicator_enable(काष्ठा coresight_device *csdev, पूर्णांक inport,
			     पूर्णांक outport)
अणु
	पूर्णांक rc = 0;
	काष्ठा replicator_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	अचिन्हित दीर्घ flags;
	bool first_enable = false;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	अगर (atomic_पढ़ो(&csdev->refcnt[outport]) == 0) अणु
		अगर (drvdata->base)
			rc = dynamic_replicator_enable(drvdata, inport,
						       outport);
		अगर (!rc)
			first_enable = true;
	पूर्ण
	अगर (!rc)
		atomic_inc(&csdev->refcnt[outport]);
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	अगर (first_enable)
		dev_dbg(&csdev->dev, "REPLICATOR enabled\n");
	वापस rc;
पूर्ण

अटल व्योम dynamic_replicator_disable(काष्ठा replicator_drvdata *drvdata,
				       पूर्णांक inport, पूर्णांक outport)
अणु
	u32 reg;
	काष्ठा coresight_device *csdev = drvdata->csdev;

	चयन (outport) अणु
	हाल 0:
		reg = REPLICATOR_IDFILTER0;
		अवरोध;
	हाल 1:
		reg = REPLICATOR_IDFILTER1;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	CS_UNLOCK(drvdata->base);

	/* disable the flow of ATB data through port */
	ग_लिखोl_relaxed(0xff, drvdata->base + reg);

	अगर ((पढ़ोl_relaxed(drvdata->base + REPLICATOR_IDFILTER0) == 0xff) &&
	    (पढ़ोl_relaxed(drvdata->base + REPLICATOR_IDFILTER1) == 0xff))
		coresight_disclaim_device_unlocked(csdev);
	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम replicator_disable(काष्ठा coresight_device *csdev, पूर्णांक inport,
			       पूर्णांक outport)
अणु
	काष्ठा replicator_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	अचिन्हित दीर्घ flags;
	bool last_disable = false;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	अगर (atomic_dec_वापस(&csdev->refcnt[outport]) == 0) अणु
		अगर (drvdata->base)
			dynamic_replicator_disable(drvdata, inport, outport);
		last_disable = true;
	पूर्ण
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	अगर (last_disable)
		dev_dbg(&csdev->dev, "REPLICATOR disabled\n");
पूर्ण

अटल स्थिर काष्ठा coresight_ops_link replicator_link_ops = अणु
	.enable		= replicator_enable,
	.disable	= replicator_disable,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops replicator_cs_ops = अणु
	.link_ops	= &replicator_link_ops,
पूर्ण;

#घोषणा coresight_replicator_reg(name, offset) \
	coresight_simple_reg32(काष्ठा replicator_drvdata, name, offset)

coresight_replicator_reg(idfilter0, REPLICATOR_IDFILTER0);
coresight_replicator_reg(idfilter1, REPLICATOR_IDFILTER1);

अटल काष्ठा attribute *replicator_mgmt_attrs[] = अणु
	&dev_attr_idfilter0.attr,
	&dev_attr_idfilter1.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group replicator_mgmt_group = अणु
	.attrs = replicator_mgmt_attrs,
	.name = "mgmt",
पूर्ण;

अटल स्थिर काष्ठा attribute_group *replicator_groups[] = अणु
	&replicator_mgmt_group,
	शून्य,
पूर्ण;

अटल पूर्णांक replicator_probe(काष्ठा device *dev, काष्ठा resource *res)
अणु
	पूर्णांक ret = 0;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा replicator_drvdata *drvdata;
	काष्ठा coresight_desc desc = अणु 0 पूर्ण;
	व्योम __iomem *base;

	अगर (is_of_node(dev_fwnode(dev)) &&
	    of_device_is_compatible(dev->of_node, "arm,coresight-replicator"))
		dev_warn_once(dev,
			      "Uses OBSOLETE CoreSight replicator binding\n");

	desc.name = coresight_alloc_device_name(&replicator_devs, dev);
	अगर (!desc.name)
		वापस -ENOMEM;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->atclk = devm_clk_get(dev, "atclk"); /* optional */
	अगर (!IS_ERR(drvdata->atclk)) अणु
		ret = clk_prepare_enable(drvdata->atclk);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Map the device base क्रम dynamic-replicator, which has been
	 * validated by AMBA core
	 */
	अगर (res) अणु
		base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(base)) अणु
			ret = PTR_ERR(base);
			जाओ out_disable_clk;
		पूर्ण
		drvdata->base = base;
		desc.groups = replicator_groups;
		desc.access = CSDEV_ACCESS_IOMEM(base);
	पूर्ण

	अगर (fwnode_property_present(dev_fwnode(dev),
				    "qcom,replicator-loses-context"))
		drvdata->check_idfilter_val = true;

	dev_set_drvdata(dev, drvdata);

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata)) अणु
		ret = PTR_ERR(pdata);
		जाओ out_disable_clk;
	पूर्ण
	dev->platक्रमm_data = pdata;

	spin_lock_init(&drvdata->spinlock);
	desc.type = CORESIGHT_DEV_TYPE_LINK;
	desc.subtype.link_subtype = CORESIGHT_DEV_SUBTYPE_LINK_SPLIT;
	desc.ops = &replicator_cs_ops;
	desc.pdata = dev->platक्रमm_data;
	desc.dev = dev;

	drvdata->csdev = coresight_रेजिस्टर(&desc);
	अगर (IS_ERR(drvdata->csdev)) अणु
		ret = PTR_ERR(drvdata->csdev);
		जाओ out_disable_clk;
	पूर्ण

	replicator_reset(drvdata);
	pm_runसमय_put(dev);

out_disable_clk:
	अगर (ret && !IS_ERR_OR_शून्य(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);
	वापस ret;
पूर्ण

अटल पूर्णांक replicator_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा replicator_drvdata *drvdata = dev_get_drvdata(dev);

	coresight_unरेजिस्टर(drvdata->csdev);
	वापस 0;
पूर्ण

अटल पूर्णांक अटल_replicator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	/* Static replicators करो not have programming base */
	ret = replicator_probe(&pdev->dev, शून्य);

	अगर (ret) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		pm_runसमय_disable(&pdev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक अटल_replicator_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	replicator_हटाओ(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक replicator_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा replicator_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);

	वापस 0;
पूर्ण

अटल पूर्णांक replicator_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा replicator_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_prepare_enable(drvdata->atclk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops replicator_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(replicator_runसमय_suspend,
			   replicator_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id अटल_replicator_match[] = अणु
	अणु.compatible = "arm,coresight-replicator"पूर्ण,
	अणु.compatible = "arm,coresight-static-replicator"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, अटल_replicator_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id अटल_replicator_acpi_ids[] = अणु
	अणु"ARMHC985", 0पूर्ण, /* ARM CoreSight Static Replicator */
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, अटल_replicator_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver अटल_replicator_driver = अणु
	.probe          = अटल_replicator_probe,
	.हटाओ         = अटल_replicator_हटाओ,
	.driver         = अणु
		.name   = "coresight-static-replicator",
		/* THIS_MODULE is taken care of by platक्रमm_driver_रेजिस्टर() */
		.of_match_table = of_match_ptr(अटल_replicator_match),
		.acpi_match_table = ACPI_PTR(अटल_replicator_acpi_ids),
		.pm	= &replicator_dev_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dynamic_replicator_probe(काष्ठा amba_device *adev,
				    स्थिर काष्ठा amba_id *id)
अणु
	वापस replicator_probe(&adev->dev, &adev->res);
पूर्ण

अटल व्योम dynamic_replicator_हटाओ(काष्ठा amba_device *adev)
अणु
	replicator_हटाओ(&adev->dev);
पूर्ण

अटल स्थिर काष्ठा amba_id dynamic_replicator_ids[] = अणु
	CS_AMBA_ID(0x000bb909),
	CS_AMBA_ID(0x000bb9ec),		/* Coresight SoC-600 */
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, dynamic_replicator_ids);

अटल काष्ठा amba_driver dynamic_replicator_driver = अणु
	.drv = अणु
		.name	= "coresight-dynamic-replicator",
		.pm	= &replicator_dev_pm_ops,
		.owner	= THIS_MODULE,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= dynamic_replicator_probe,
	.हटाओ         = dynamic_replicator_हटाओ,
	.id_table	= dynamic_replicator_ids,
पूर्ण;

अटल पूर्णांक __init replicator_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&अटल_replicator_driver);
	अगर (ret) अणु
		pr_info("Error registering platform driver\n");
		वापस ret;
	पूर्ण

	ret = amba_driver_रेजिस्टर(&dynamic_replicator_driver);
	अगर (ret) अणु
		pr_info("Error registering amba driver\n");
		platक्रमm_driver_unरेजिस्टर(&अटल_replicator_driver);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास replicator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&अटल_replicator_driver);
	amba_driver_unरेजिस्टर(&dynamic_replicator_driver);
पूर्ण

module_init(replicator_init);
module_निकास(replicator_निकास);

MODULE_AUTHOR("Pratik Patel <pratikp@codeaurora.org>");
MODULE_AUTHOR("Mathieu Poirier <mathieu.poirier@linaro.org>");
MODULE_DESCRIPTION("Arm CoreSight Replicator Driver");
MODULE_LICENSE("GPL v2");
