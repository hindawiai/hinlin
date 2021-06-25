<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
 *
 * Description: CoreSight Funnel driver
 */

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/coresight.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/clk.h>

#समावेश "coresight-priv.h"

#घोषणा FUNNEL_FUNCTL		0x000
#घोषणा FUNNEL_PRICTL		0x004

#घोषणा FUNNEL_HOLDTIME_MASK	0xf00
#घोषणा FUNNEL_HOLDTIME_SHFT	0x8
#घोषणा FUNNEL_HOLDTIME		(0x7 << FUNNEL_HOLDTIME_SHFT)
#घोषणा FUNNEL_ENSx_MASK	0xff

DEFINE_CORESIGHT_DEVLIST(funnel_devs, "funnel");

/**
 * काष्ठा funnel_drvdata - specअगरics associated to a funnel component
 * @base:	memory mapped base address क्रम this component.
 * @atclk:	optional घड़ी क्रम the core parts of the funnel.
 * @csdev:	component vitals needed by the framework.
 * @priority:	port selection order.
 * @spinlock:	serialize enable/disable operations.
 */
काष्ठा funnel_drvdata अणु
	व्योम __iomem		*base;
	काष्ठा clk		*atclk;
	काष्ठा coresight_device	*csdev;
	अचिन्हित दीर्घ		priority;
	spinlock_t		spinlock;
पूर्ण;

अटल पूर्णांक dynamic_funnel_enable_hw(काष्ठा funnel_drvdata *drvdata, पूर्णांक port)
अणु
	u32 functl;
	पूर्णांक rc = 0;
	काष्ठा coresight_device *csdev = drvdata->csdev;

	CS_UNLOCK(drvdata->base);

	functl = पढ़ोl_relaxed(drvdata->base + FUNNEL_FUNCTL);
	/* Claim the device only when we enable the first slave */
	अगर (!(functl & FUNNEL_ENSx_MASK)) अणु
		rc = coresight_claim_device_unlocked(csdev);
		अगर (rc)
			जाओ करोne;
	पूर्ण

	functl &= ~FUNNEL_HOLDTIME_MASK;
	functl |= FUNNEL_HOLDTIME;
	functl |= (1 << port);
	ग_लिखोl_relaxed(functl, drvdata->base + FUNNEL_FUNCTL);
	ग_लिखोl_relaxed(drvdata->priority, drvdata->base + FUNNEL_PRICTL);
करोne:
	CS_LOCK(drvdata->base);
	वापस rc;
पूर्ण

अटल पूर्णांक funnel_enable(काष्ठा coresight_device *csdev, पूर्णांक inport,
			 पूर्णांक outport)
अणु
	पूर्णांक rc = 0;
	काष्ठा funnel_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	अचिन्हित दीर्घ flags;
	bool first_enable = false;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	अगर (atomic_पढ़ो(&csdev->refcnt[inport]) == 0) अणु
		अगर (drvdata->base)
			rc = dynamic_funnel_enable_hw(drvdata, inport);
		अगर (!rc)
			first_enable = true;
	पूर्ण
	अगर (!rc)
		atomic_inc(&csdev->refcnt[inport]);
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	अगर (first_enable)
		dev_dbg(&csdev->dev, "FUNNEL inport %d enabled\n", inport);
	वापस rc;
पूर्ण

अटल व्योम dynamic_funnel_disable_hw(काष्ठा funnel_drvdata *drvdata,
				      पूर्णांक inport)
अणु
	u32 functl;
	काष्ठा coresight_device *csdev = drvdata->csdev;

	CS_UNLOCK(drvdata->base);

	functl = पढ़ोl_relaxed(drvdata->base + FUNNEL_FUNCTL);
	functl &= ~(1 << inport);
	ग_लिखोl_relaxed(functl, drvdata->base + FUNNEL_FUNCTL);

	/* Disclaim the device अगर none of the slaves are now active */
	अगर (!(functl & FUNNEL_ENSx_MASK))
		coresight_disclaim_device_unlocked(csdev);

	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम funnel_disable(काष्ठा coresight_device *csdev, पूर्णांक inport,
			   पूर्णांक outport)
अणु
	काष्ठा funnel_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	अचिन्हित दीर्घ flags;
	bool last_disable = false;

	spin_lock_irqsave(&drvdata->spinlock, flags);
	अगर (atomic_dec_वापस(&csdev->refcnt[inport]) == 0) अणु
		अगर (drvdata->base)
			dynamic_funnel_disable_hw(drvdata, inport);
		last_disable = true;
	पूर्ण
	spin_unlock_irqrestore(&drvdata->spinlock, flags);

	अगर (last_disable)
		dev_dbg(&csdev->dev, "FUNNEL inport %d disabled\n", inport);
पूर्ण

अटल स्थिर काष्ठा coresight_ops_link funnel_link_ops = अणु
	.enable		= funnel_enable,
	.disable	= funnel_disable,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops funnel_cs_ops = अणु
	.link_ops	= &funnel_link_ops,
पूर्ण;

अटल sमाप_प्रकार priority_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा funnel_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val = drvdata->priority;

	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार priority_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा funnel_drvdata *drvdata = dev_get_drvdata(dev->parent);

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	drvdata->priority = val;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(priority);

अटल u32 get_funnel_ctrl_hw(काष्ठा funnel_drvdata *drvdata)
अणु
	u32 functl;

	CS_UNLOCK(drvdata->base);
	functl = पढ़ोl_relaxed(drvdata->base + FUNNEL_FUNCTL);
	CS_LOCK(drvdata->base);

	वापस functl;
पूर्ण

अटल sमाप_प्रकार funnel_ctrl_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	u32 val;
	काष्ठा funnel_drvdata *drvdata = dev_get_drvdata(dev->parent);

	pm_runसमय_get_sync(dev->parent);

	val = get_funnel_ctrl_hw(drvdata);

	pm_runसमय_put(dev->parent);

	वापस प्र_लिखो(buf, "%#x\n", val);
पूर्ण
अटल DEVICE_ATTR_RO(funnel_ctrl);

अटल काष्ठा attribute *coresight_funnel_attrs[] = अणु
	&dev_attr_funnel_ctrl.attr,
	&dev_attr_priority.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(coresight_funnel);

अटल पूर्णांक funnel_probe(काष्ठा device *dev, काष्ठा resource *res)
अणु
	पूर्णांक ret;
	व्योम __iomem *base;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा funnel_drvdata *drvdata;
	काष्ठा coresight_desc desc = अणु 0 पूर्ण;

	अगर (is_of_node(dev_fwnode(dev)) &&
	    of_device_is_compatible(dev->of_node, "arm,coresight-funnel"))
		dev_warn_once(dev, "Uses OBSOLETE CoreSight funnel binding\n");

	desc.name = coresight_alloc_device_name(&funnel_devs, dev);
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
	 * Map the device base क्रम dynamic-funnel, which has been
	 * validated by AMBA core.
	 */
	अगर (res) अणु
		base = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(base)) अणु
			ret = PTR_ERR(base);
			जाओ out_disable_clk;
		पूर्ण
		drvdata->base = base;
		desc.groups = coresight_funnel_groups;
		desc.access = CSDEV_ACCESS_IOMEM(base);
	पूर्ण

	dev_set_drvdata(dev, drvdata);

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata)) अणु
		ret = PTR_ERR(pdata);
		जाओ out_disable_clk;
	पूर्ण
	dev->platक्रमm_data = pdata;

	spin_lock_init(&drvdata->spinlock);
	desc.type = CORESIGHT_DEV_TYPE_LINK;
	desc.subtype.link_subtype = CORESIGHT_DEV_SUBTYPE_LINK_MERG;
	desc.ops = &funnel_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	drvdata->csdev = coresight_रेजिस्टर(&desc);
	अगर (IS_ERR(drvdata->csdev)) अणु
		ret = PTR_ERR(drvdata->csdev);
		जाओ out_disable_clk;
	पूर्ण

	pm_runसमय_put(dev);
	ret = 0;

out_disable_clk:
	अगर (ret && !IS_ERR_OR_शून्य(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);
	वापस ret;
पूर्ण

अटल पूर्णांक funnel_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा funnel_drvdata *drvdata = dev_get_drvdata(dev);

	coresight_unरेजिस्टर(drvdata->csdev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक funnel_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा funnel_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);

	वापस 0;
पूर्ण

अटल पूर्णांक funnel_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा funnel_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_prepare_enable(drvdata->atclk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops funnel_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(funnel_runसमय_suspend, funnel_runसमय_resume, शून्य)
पूर्ण;

अटल पूर्णांक अटल_funnel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	/* Static funnel करो not have programming base */
	ret = funnel_probe(&pdev->dev, शून्य);

	अगर (ret) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		pm_runसमय_disable(&pdev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक अटल_funnel_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	funnel_हटाओ(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id अटल_funnel_match[] = अणु
	अणु.compatible = "arm,coresight-static-funnel"पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, अटल_funnel_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id अटल_funnel_ids[] = अणु
	अणु"ARMHC9FE", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, अटल_funnel_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver अटल_funnel_driver = अणु
	.probe          = अटल_funnel_probe,
	.हटाओ          = अटल_funnel_हटाओ,
	.driver         = अणु
		.name   = "coresight-static-funnel",
		/* THIS_MODULE is taken care of by platक्रमm_driver_रेजिस्टर() */
		.of_match_table = अटल_funnel_match,
		.acpi_match_table = ACPI_PTR(अटल_funnel_ids),
		.pm	= &funnel_dev_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dynamic_funnel_probe(काष्ठा amba_device *adev,
				स्थिर काष्ठा amba_id *id)
अणु
	वापस funnel_probe(&adev->dev, &adev->res);
पूर्ण

अटल व्योम dynamic_funnel_हटाओ(काष्ठा amba_device *adev)
अणु
	funnel_हटाओ(&adev->dev);
पूर्ण

अटल स्थिर काष्ठा amba_id dynamic_funnel_ids[] = अणु
	अणु
		.id     = 0x000bb908,
		.mask   = 0x000fffff,
	पूर्ण,
	अणु
		/* Coresight SoC-600 */
		.id     = 0x000bb9eb,
		.mask   = 0x000fffff,
	पूर्ण,
	अणु 0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, dynamic_funnel_ids);

अटल काष्ठा amba_driver dynamic_funnel_driver = अणु
	.drv = अणु
		.name	= "coresight-dynamic-funnel",
		.owner	= THIS_MODULE,
		.pm	= &funnel_dev_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= dynamic_funnel_probe,
	.हटाओ		= dynamic_funnel_हटाओ,
	.id_table	= dynamic_funnel_ids,
पूर्ण;

अटल पूर्णांक __init funnel_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&अटल_funnel_driver);
	अगर (ret) अणु
		pr_info("Error registering platform driver\n");
		वापस ret;
	पूर्ण

	ret = amba_driver_रेजिस्टर(&dynamic_funnel_driver);
	अगर (ret) अणु
		pr_info("Error registering amba driver\n");
		platक्रमm_driver_unरेजिस्टर(&अटल_funnel_driver);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास funnel_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&अटल_funnel_driver);
	amba_driver_unरेजिस्टर(&dynamic_funnel_driver);
पूर्ण

module_init(funnel_init);
module_निकास(funnel_निकास);

MODULE_AUTHOR("Pratik Patel <pratikp@codeaurora.org>");
MODULE_AUTHOR("Mathieu Poirier <mathieu.poirier@linaro.org>");
MODULE_DESCRIPTION("Arm CoreSight Funnel Driver");
MODULE_LICENSE("GPL v2");
