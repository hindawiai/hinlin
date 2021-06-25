<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <drm/drm_of.h>

#समावेश "dcss-dev.h"
#समावेश "dcss-kms.h"

काष्ठा dcss_drv अणु
	काष्ठा dcss_dev *dcss;
	काष्ठा dcss_kms_dev *kms;
पूर्ण;

काष्ठा dcss_dev *dcss_drv_dev_to_dcss(काष्ठा device *dev)
अणु
	काष्ठा dcss_drv *mdrv = dev_get_drvdata(dev);

	वापस mdrv ? mdrv->dcss : शून्य;
पूर्ण

काष्ठा drm_device *dcss_drv_dev_to_drm(काष्ठा device *dev)
अणु
	काष्ठा dcss_drv *mdrv = dev_get_drvdata(dev);

	वापस mdrv ? &mdrv->kms->base : शून्य;
पूर्ण

अटल पूर्णांक dcss_drv_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *remote;
	काष्ठा dcss_drv *mdrv;
	पूर्णांक err = 0;
	bool hdmi_output = true;

	अगर (!dev->of_node)
		वापस -ENODEV;

	remote = of_graph_get_remote_node(dev->of_node, 0, 0);
	अगर (!remote)
		वापस -ENODEV;

	hdmi_output = !of_device_is_compatible(remote, "fsl,imx8mq-nwl-dsi");

	of_node_put(remote);

	mdrv = kzalloc(माप(*mdrv), GFP_KERNEL);
	अगर (!mdrv)
		वापस -ENOMEM;

	mdrv->dcss = dcss_dev_create(dev, hdmi_output);
	अगर (IS_ERR(mdrv->dcss)) अणु
		err = PTR_ERR(mdrv->dcss);
		जाओ err;
	पूर्ण

	dev_set_drvdata(dev, mdrv);

	mdrv->kms = dcss_kms_attach(mdrv->dcss);
	अगर (IS_ERR(mdrv->kms)) अणु
		err = PTR_ERR(mdrv->kms);
		जाओ dcss_shutoff;
	पूर्ण

	वापस 0;

dcss_shutoff:
	dcss_dev_destroy(mdrv->dcss);

	dev_set_drvdata(dev, शून्य);

err:
	kमुक्त(mdrv);
	वापस err;
पूर्ण

अटल पूर्णांक dcss_drv_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dcss_drv *mdrv = dev_get_drvdata(&pdev->dev);

	अगर (!mdrv)
		वापस 0;

	dcss_kms_detach(mdrv->kms);
	dcss_dev_destroy(mdrv->dcss);

	dev_set_drvdata(&pdev->dev, शून्य);

	kमुक्त(mdrv);

	वापस 0;
पूर्ण

अटल काष्ठा dcss_type_data dcss_types[] = अणु
	[DCSS_IMX8MQ] = अणु
		.name = "DCSS_IMX8MQ",
		.blkctl_ofs = 0x2F000,
		.ctxld_ofs = 0x23000,
		.dtg_ofs = 0x20000,
		.scaler_ofs = 0x1C000,
		.ss_ofs = 0x1B000,
		.dpr_ofs = 0x18000,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dcss_of_match[] = अणु
	अणु .compatible = "nxp,imx8mq-dcss", .data = &dcss_types[DCSS_IMX8MQ], पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, dcss_of_match);

अटल स्थिर काष्ठा dev_pm_ops dcss_dev_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(dcss_dev_suspend, dcss_dev_resume)
	SET_RUNTIME_PM_OPS(dcss_dev_runसमय_suspend,
			   dcss_dev_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver dcss_platक्रमm_driver = अणु
	.probe	= dcss_drv_platक्रमm_probe,
	.हटाओ	= dcss_drv_platक्रमm_हटाओ,
	.driver	= अणु
		.name = "imx-dcss",
		.of_match_table	= dcss_of_match,
		.pm = &dcss_dev_pm,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(dcss_platक्रमm_driver);

MODULE_AUTHOR("Laurentiu Palcu <laurentiu.palcu@nxp.com>");
MODULE_DESCRIPTION("DCSS driver for i.MX8MQ");
MODULE_LICENSE("GPL v2");
