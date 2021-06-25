<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#समावेश "dsi.h"

काष्ठा drm_encoder *msm_dsi_get_encoder(काष्ठा msm_dsi *msm_dsi)
अणु
	अगर (!msm_dsi || !msm_dsi_device_connected(msm_dsi))
		वापस शून्य;

	वापस msm_dsi->encoder;
पूर्ण

अटल पूर्णांक dsi_get_phy(काष्ठा msm_dsi *msm_dsi)
अणु
	काष्ठा platक्रमm_device *pdev = msm_dsi->pdev;
	काष्ठा platक्रमm_device *phy_pdev;
	काष्ठा device_node *phy_node;

	phy_node = of_parse_phandle(pdev->dev.of_node, "phys", 0);
	अगर (!phy_node) अणु
		DRM_DEV_ERROR(&pdev->dev, "cannot find phy device\n");
		वापस -ENXIO;
	पूर्ण

	phy_pdev = of_find_device_by_node(phy_node);
	अगर (phy_pdev)
		msm_dsi->phy = platक्रमm_get_drvdata(phy_pdev);

	of_node_put(phy_node);

	अगर (!phy_pdev || !msm_dsi->phy) अणु
		DRM_DEV_ERROR(&pdev->dev, "%s: phy driver is not ready\n", __func__);
		वापस -EPROBE_DEFER;
	पूर्ण

	msm_dsi->phy_dev = get_device(&phy_pdev->dev);

	वापस 0;
पूर्ण

अटल व्योम dsi_destroy(काष्ठा msm_dsi *msm_dsi)
अणु
	अगर (!msm_dsi)
		वापस;

	msm_dsi_manager_unरेजिस्टर(msm_dsi);

	अगर (msm_dsi->phy_dev) अणु
		put_device(msm_dsi->phy_dev);
		msm_dsi->phy = शून्य;
		msm_dsi->phy_dev = शून्य;
	पूर्ण

	अगर (msm_dsi->host) अणु
		msm_dsi_host_destroy(msm_dsi->host);
		msm_dsi->host = शून्य;
	पूर्ण

	platक्रमm_set_drvdata(msm_dsi->pdev, शून्य);
पूर्ण

अटल काष्ठा msm_dsi *dsi_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msm_dsi *msm_dsi;
	पूर्णांक ret;

	अगर (!pdev)
		वापस ERR_PTR(-ENXIO);

	msm_dsi = devm_kzalloc(&pdev->dev, माप(*msm_dsi), GFP_KERNEL);
	अगर (!msm_dsi)
		वापस ERR_PTR(-ENOMEM);
	DBG("dsi probed=%p", msm_dsi);

	msm_dsi->id = -1;
	msm_dsi->pdev = pdev;
	platक्रमm_set_drvdata(pdev, msm_dsi);

	/* Init dsi host */
	ret = msm_dsi_host_init(msm_dsi);
	अगर (ret)
		जाओ destroy_dsi;

	/* GET dsi PHY */
	ret = dsi_get_phy(msm_dsi);
	अगर (ret)
		जाओ destroy_dsi;

	/* Register to dsi manager */
	ret = msm_dsi_manager_रेजिस्टर(msm_dsi);
	अगर (ret)
		जाओ destroy_dsi;

	वापस msm_dsi;

destroy_dsi:
	dsi_destroy(msm_dsi);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक dsi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा msm_dsi *msm_dsi;

	DBG("");
	msm_dsi = dsi_init(pdev);
	अगर (IS_ERR(msm_dsi)) अणु
		/* Don't fail the bind अगर the dsi port is not connected */
		अगर (PTR_ERR(msm_dsi) == -ENODEV)
			वापस 0;
		अन्यथा
			वापस PTR_ERR(msm_dsi);
	पूर्ण

	priv->dsi[msm_dsi->id] = msm_dsi;

	वापस 0;
पूर्ण

अटल व्योम dsi_unbind(काष्ठा device *dev, काष्ठा device *master,
		व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;
	काष्ठा msm_dsi *msm_dsi = dev_get_drvdata(dev);
	पूर्णांक id = msm_dsi->id;

	अगर (priv->dsi[id]) अणु
		dsi_destroy(msm_dsi);
		priv->dsi[id] = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा component_ops dsi_ops = अणु
	.bind   = dsi_bind,
	.unbind = dsi_unbind,
पूर्ण;

अटल पूर्णांक dsi_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &dsi_ops);
पूर्ण

अटल पूर्णांक dsi_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	DBG("");
	component_del(&pdev->dev, &dsi_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id dt_match[] = अणु
	अणु .compatible = "qcom,mdss-dsi-ctrl" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops dsi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(msm_dsi_runसमय_suspend, msm_dsi_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver dsi_driver = अणु
	.probe = dsi_dev_probe,
	.हटाओ = dsi_dev_हटाओ,
	.driver = अणु
		.name = "msm_dsi",
		.of_match_table = dt_match,
		.pm = &dsi_pm_ops,
	पूर्ण,
पूर्ण;

व्योम __init msm_dsi_रेजिस्टर(व्योम)
अणु
	DBG("");
	msm_dsi_phy_driver_रेजिस्टर();
	platक्रमm_driver_रेजिस्टर(&dsi_driver);
पूर्ण

व्योम __निकास msm_dsi_unरेजिस्टर(व्योम)
अणु
	DBG("");
	msm_dsi_phy_driver_unरेजिस्टर();
	platक्रमm_driver_unरेजिस्टर(&dsi_driver);
पूर्ण

पूर्णांक msm_dsi_modeset_init(काष्ठा msm_dsi *msm_dsi, काष्ठा drm_device *dev,
			 काष्ठा drm_encoder *encoder)
अणु
	काष्ठा msm_drm_निजी *priv;
	काष्ठा drm_bridge *ext_bridge;
	पूर्णांक ret;

	अगर (WARN_ON(!encoder) || WARN_ON(!msm_dsi) || WARN_ON(!dev))
		वापस -EINVAL;

	priv = dev->dev_निजी;
	msm_dsi->dev = dev;

	ret = msm_dsi_host_modeset_init(msm_dsi->host, dev);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev->dev, "failed to modeset init host: %d\n", ret);
		जाओ fail;
	पूर्ण

	अगर (!msm_dsi_manager_validate_current_config(msm_dsi->id))
		जाओ fail;

	msm_dsi->encoder = encoder;

	msm_dsi->bridge = msm_dsi_manager_bridge_init(msm_dsi->id);
	अगर (IS_ERR(msm_dsi->bridge)) अणु
		ret = PTR_ERR(msm_dsi->bridge);
		DRM_DEV_ERROR(dev->dev, "failed to create dsi bridge: %d\n", ret);
		msm_dsi->bridge = शून्य;
		जाओ fail;
	पूर्ण

	/*
	 * check अगर the dsi encoder output is connected to a panel or an
	 * बाह्यal bridge. We create a connector only अगर we're connected to a
	 * drm_panel device. When we're connected to an बाह्यal bridge, we
	 * assume that the drm_bridge driver will create the connector itself.
	 */
	ext_bridge = msm_dsi_host_get_bridge(msm_dsi->host);

	अगर (ext_bridge)
		msm_dsi->connector =
			msm_dsi_manager_ext_bridge_init(msm_dsi->id);
	अन्यथा
		msm_dsi->connector =
			msm_dsi_manager_connector_init(msm_dsi->id);

	अगर (IS_ERR(msm_dsi->connector)) अणु
		ret = PTR_ERR(msm_dsi->connector);
		DRM_DEV_ERROR(dev->dev,
			"failed to create dsi connector: %d\n", ret);
		msm_dsi->connector = शून्य;
		जाओ fail;
	पूर्ण

	msm_dsi_manager_setup_encoder(msm_dsi->id);

	priv->bridges[priv->num_bridges++]       = msm_dsi->bridge;
	priv->connectors[priv->num_connectors++] = msm_dsi->connector;

	वापस 0;
fail:
	/* bridge/connector are normally destroyed by drm: */
	अगर (msm_dsi->bridge) अणु
		msm_dsi_manager_bridge_destroy(msm_dsi->bridge);
		msm_dsi->bridge = शून्य;
	पूर्ण

	/* करोn't destroy connector if we didn't make it */
	अगर (msm_dsi->connector && !msm_dsi->बाह्यal_bridge)
		msm_dsi->connector->funcs->destroy(msm_dsi->connector);

	msm_dsi->connector = शून्य;

	वापस ret;
पूर्ण

