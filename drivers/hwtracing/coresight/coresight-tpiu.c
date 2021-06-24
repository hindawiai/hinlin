<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
 *
 * Description: CoreSight Trace Port Interface Unit driver
 */

#समावेश <linux/atomic.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/coresight.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/clk.h>

#समावेश "coresight-priv.h"

#घोषणा TPIU_SUPP_PORTSZ	0x000
#घोषणा TPIU_CURR_PORTSZ	0x004
#घोषणा TPIU_SUPP_TRIGMODES	0x100
#घोषणा TPIU_TRIG_CNTRVAL	0x104
#घोषणा TPIU_TRIG_MULT		0x108
#घोषणा TPIU_SUPP_TESTPATM	0x200
#घोषणा TPIU_CURR_TESTPATM	0x204
#घोषणा TPIU_TEST_PATREPCNTR	0x208
#घोषणा TPIU_FFSR		0x300
#घोषणा TPIU_FFCR		0x304
#घोषणा TPIU_FSYNC_CNTR		0x308
#घोषणा TPIU_EXTCTL_INPORT	0x400
#घोषणा TPIU_EXTCTL_OUTPORT	0x404
#घोषणा TPIU_ITTRFLINACK	0xee4
#घोषणा TPIU_ITTRFLIN		0xee8
#घोषणा TPIU_ITATBDATA0		0xeec
#घोषणा TPIU_ITATBCTR2		0xef0
#घोषणा TPIU_ITATBCTR1		0xef4
#घोषणा TPIU_ITATBCTR0		0xef8

/** रेजिस्टर definition **/
/* FFSR - 0x300 */
#घोषणा FFSR_FT_STOPPED_BIT	1
/* FFCR - 0x304 */
#घोषणा FFCR_FON_MAN_BIT	6
#घोषणा FFCR_FON_MAN		BIT(6)
#घोषणा FFCR_STOP_FI		BIT(12)

DEFINE_CORESIGHT_DEVLIST(tpiu_devs, "tpiu");

/*
 * @base:	memory mapped base address क्रम this component.
 * @atclk:	optional घड़ी क्रम the core parts of the TPIU.
 * @csdev:	component vitals needed by the framework.
 */
काष्ठा tpiu_drvdata अणु
	व्योम __iomem		*base;
	काष्ठा clk		*atclk;
	काष्ठा coresight_device	*csdev;
पूर्ण;

अटल व्योम tpiu_enable_hw(काष्ठा csdev_access *csa)
अणु
	CS_UNLOCK(csa->base);

	/* TODO: fill this up */

	CS_LOCK(csa->base);
पूर्ण

अटल पूर्णांक tpiu_enable(काष्ठा coresight_device *csdev, u32 mode, व्योम *__unused)
अणु
	tpiu_enable_hw(&csdev->access);
	atomic_inc(csdev->refcnt);
	dev_dbg(&csdev->dev, "TPIU enabled\n");
	वापस 0;
पूर्ण

अटल व्योम tpiu_disable_hw(काष्ठा csdev_access *csa)
अणु
	CS_UNLOCK(csa->base);

	/* Clear क्रमmatter and stop on flush */
	csdev_access_relaxed_ग_लिखो32(csa, FFCR_STOP_FI, TPIU_FFCR);
	/* Generate manual flush */
	csdev_access_relaxed_ग_लिखो32(csa, FFCR_STOP_FI | FFCR_FON_MAN, TPIU_FFCR);
	/* Wait क्रम flush to complete */
	coresight_समयout(csa, TPIU_FFCR, FFCR_FON_MAN_BIT, 0);
	/* Wait क्रम क्रमmatter to stop */
	coresight_समयout(csa, TPIU_FFSR, FFSR_FT_STOPPED_BIT, 1);

	CS_LOCK(csa->base);
पूर्ण

अटल पूर्णांक tpiu_disable(काष्ठा coresight_device *csdev)
अणु
	अगर (atomic_dec_वापस(csdev->refcnt))
		वापस -EBUSY;

	tpiu_disable_hw(&csdev->access);

	dev_dbg(&csdev->dev, "TPIU disabled\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा coresight_ops_sink tpiu_sink_ops = अणु
	.enable		= tpiu_enable,
	.disable	= tpiu_disable,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops tpiu_cs_ops = अणु
	.sink_ops	= &tpiu_sink_ops,
पूर्ण;

अटल पूर्णांक tpiu_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret;
	व्योम __iomem *base;
	काष्ठा device *dev = &adev->dev;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा tpiu_drvdata *drvdata;
	काष्ठा resource *res = &adev->res;
	काष्ठा coresight_desc desc = अणु 0 पूर्ण;

	desc.name = coresight_alloc_device_name(&tpiu_devs, dev);
	अगर (!desc.name)
		वापस -ENOMEM;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->atclk = devm_clk_get(&adev->dev, "atclk"); /* optional */
	अगर (!IS_ERR(drvdata->atclk)) अणु
		ret = clk_prepare_enable(drvdata->atclk);
		अगर (ret)
			वापस ret;
	पूर्ण
	dev_set_drvdata(dev, drvdata);

	/* Validity क्रम the resource is alपढ़ोy checked by the AMBA core */
	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	drvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	/* Disable tpiu to support older devices */
	tpiu_disable_hw(&desc.access);

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);
	dev->platक्रमm_data = pdata;

	desc.type = CORESIGHT_DEV_TYPE_SINK;
	desc.subtype.sink_subtype = CORESIGHT_DEV_SUBTYPE_SINK_PORT;
	desc.ops = &tpiu_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	drvdata->csdev = coresight_रेजिस्टर(&desc);

	अगर (!IS_ERR(drvdata->csdev)) अणु
		pm_runसमय_put(&adev->dev);
		वापस 0;
	पूर्ण

	वापस PTR_ERR(drvdata->csdev);
पूर्ण

अटल व्योम tpiu_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा tpiu_drvdata *drvdata = dev_get_drvdata(&adev->dev);

	coresight_unरेजिस्टर(drvdata->csdev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tpiu_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा tpiu_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);

	वापस 0;
पूर्ण

अटल पूर्णांक tpiu_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा tpiu_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_prepare_enable(drvdata->atclk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops tpiu_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tpiu_runसमय_suspend, tpiu_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा amba_id tpiu_ids[] = अणु
	अणु
		.id	= 0x000bb912,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु
		.id	= 0x0004b912,
		.mask	= 0x0007ffff,
	पूर्ण,
	अणु
		/* Coresight SoC-600 */
		.id	= 0x000bb9e7,
		.mask	= 0x000fffff,
	पूर्ण,
	अणु 0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, tpiu_ids);

अटल काष्ठा amba_driver tpiu_driver = अणु
	.drv = अणु
		.name	= "coresight-tpiu",
		.owner	= THIS_MODULE,
		.pm	= &tpiu_dev_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe		= tpiu_probe,
	.हटाओ         = tpiu_हटाओ,
	.id_table	= tpiu_ids,
पूर्ण;

module_amba_driver(tpiu_driver);

MODULE_AUTHOR("Pratik Patel <pratikp@codeaurora.org>");
MODULE_AUTHOR("Mathieu Poirier <mathieu.poirier@linaro.org>");
MODULE_DESCRIPTION("Arm CoreSight TPIU (Trace Port Interface Unit) driver");
MODULE_LICENSE("GPL v2");
