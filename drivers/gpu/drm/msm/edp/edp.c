<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/of_irq.h>
#समावेश "edp.h"

अटल irqवापस_t edp_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा msm_edp *edp = dev_id;

	/* Process eDP irq */
	वापस msm_edp_ctrl_irq(edp->ctrl);
पूर्ण

अटल व्योम edp_destroy(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_edp *edp = platक्रमm_get_drvdata(pdev);

	अगर (!edp)
		वापस;

	अगर (edp->ctrl) अणु
		msm_edp_ctrl_destroy(edp->ctrl);
		edp->ctrl = शून्य;
	पूर्ण

	platक्रमm_set_drvdata(pdev, शून्य);
पूर्ण

/* स्थिरruct eDP at bind/probe समय, grab all the resources. */
अटल काष्ठा msm_edp *edp_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_edp *edp = शून्य;
	पूर्णांक ret;

	अगर (!pdev) अणु
		pr_err("no eDP device\n");
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	edp = devm_kzalloc(&pdev->dev, माप(*edp), GFP_KERNEL);
	अगर (!edp) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	DBG("eDP probed=%p", edp);

	edp->pdev = pdev;
	platक्रमm_set_drvdata(pdev, edp);

	ret = msm_edp_ctrl_init(edp);
	अगर (ret)
		जाओ fail;

	वापस edp;

fail:
	अगर (edp)
		edp_destroy(pdev);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक edp_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;
	काष्ठा msm_edp *edp;

	DBG("");
	edp = edp_init(to_platक्रमm_device(dev));
	अगर (IS_ERR(edp))
		वापस PTR_ERR(edp);
	priv->edp = edp;

	वापस 0;
पूर्ण

अटल व्योम edp_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;

	DBG("");
	अगर (priv->edp) अणु
		edp_destroy(to_platक्रमm_device(dev));
		priv->edp = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा component_ops edp_ops = अणु
		.bind   = edp_bind,
		.unbind = edp_unbind,
पूर्ण;

अटल पूर्णांक edp_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	DBG("");
	वापस component_add(&pdev->dev, &edp_ops);
पूर्ण

अटल पूर्णांक edp_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	DBG("");
	component_del(&pdev->dev, &edp_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dt_match[] = अणु
	अणु .compatible = "qcom,mdss-edp" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver edp_driver = अणु
	.probe = edp_dev_probe,
	.हटाओ = edp_dev_हटाओ,
	.driver = अणु
		.name = "msm_edp",
		.of_match_table = dt_match,
	पूर्ण,
पूर्ण;

व्योम __init msm_edp_रेजिस्टर(व्योम)
अणु
	DBG("");
	platक्रमm_driver_रेजिस्टर(&edp_driver);
पूर्ण

व्योम __निकास msm_edp_unरेजिस्टर(व्योम)
अणु
	DBG("");
	platक्रमm_driver_unरेजिस्टर(&edp_driver);
पूर्ण

/* Second part of initialization, the drm/kms level modeset_init */
पूर्णांक msm_edp_modeset_init(काष्ठा msm_edp *edp, काष्ठा drm_device *dev,
				काष्ठा drm_encoder *encoder)
अणु
	काष्ठा platक्रमm_device *pdev = edp->pdev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	पूर्णांक ret;

	edp->encoder = encoder;
	edp->dev = dev;

	edp->bridge = msm_edp_bridge_init(edp);
	अगर (IS_ERR(edp->bridge)) अणु
		ret = PTR_ERR(edp->bridge);
		DRM_DEV_ERROR(dev->dev, "failed to create eDP bridge: %d\n", ret);
		edp->bridge = शून्य;
		जाओ fail;
	पूर्ण

	edp->connector = msm_edp_connector_init(edp);
	अगर (IS_ERR(edp->connector)) अणु
		ret = PTR_ERR(edp->connector);
		DRM_DEV_ERROR(dev->dev, "failed to create eDP connector: %d\n", ret);
		edp->connector = शून्य;
		जाओ fail;
	पूर्ण

	edp->irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	अगर (edp->irq < 0) अणु
		ret = edp->irq;
		DRM_DEV_ERROR(dev->dev, "failed to get IRQ: %d\n", ret);
		जाओ fail;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, edp->irq,
			edp_irq, IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
			"edp_isr", edp);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev->dev, "failed to request IRQ%u: %d\n",
				edp->irq, ret);
		जाओ fail;
	पूर्ण

	priv->bridges[priv->num_bridges++]       = edp->bridge;
	priv->connectors[priv->num_connectors++] = edp->connector;

	वापस 0;

fail:
	/* bridge/connector are normally destroyed by drm */
	अगर (edp->bridge) अणु
		edp_bridge_destroy(edp->bridge);
		edp->bridge = शून्य;
	पूर्ण
	अगर (edp->connector) अणु
		edp->connector->funcs->destroy(edp->connector);
		edp->connector = शून्य;
	पूर्ण

	वापस ret;
पूर्ण
