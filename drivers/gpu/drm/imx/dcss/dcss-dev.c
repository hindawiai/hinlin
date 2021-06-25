<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/clk.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <drm/drm_bridge_connector.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_modeset_helper.h>

#समावेश "dcss-dev.h"
#समावेश "dcss-kms.h"

अटल व्योम dcss_घड़ीs_enable(काष्ठा dcss_dev *dcss)
अणु
	clk_prepare_enable(dcss->axi_clk);
	clk_prepare_enable(dcss->apb_clk);
	clk_prepare_enable(dcss->rtrm_clk);
	clk_prepare_enable(dcss->dtrc_clk);
	clk_prepare_enable(dcss->pix_clk);
पूर्ण

अटल व्योम dcss_घड़ीs_disable(काष्ठा dcss_dev *dcss)
अणु
	clk_disable_unprepare(dcss->pix_clk);
	clk_disable_unprepare(dcss->dtrc_clk);
	clk_disable_unprepare(dcss->rtrm_clk);
	clk_disable_unprepare(dcss->apb_clk);
	clk_disable_unprepare(dcss->axi_clk);
पूर्ण

अटल व्योम dcss_disable_dtg_and_ss_cb(व्योम *data)
अणु
	काष्ठा dcss_dev *dcss = data;

	dcss->disable_callback = शून्य;

	dcss_ss_shutoff(dcss->ss);
	dcss_dtg_shutoff(dcss->dtg);

	complete(&dcss->disable_completion);
पूर्ण

व्योम dcss_disable_dtg_and_ss(काष्ठा dcss_dev *dcss)
अणु
	dcss->disable_callback = dcss_disable_dtg_and_ss_cb;
पूर्ण

व्योम dcss_enable_dtg_and_ss(काष्ठा dcss_dev *dcss)
अणु
	अगर (dcss->disable_callback)
		dcss->disable_callback = शून्य;

	dcss_dtg_enable(dcss->dtg);
	dcss_ss_enable(dcss->ss);
पूर्ण

अटल पूर्णांक dcss_submodules_init(काष्ठा dcss_dev *dcss)
अणु
	पूर्णांक ret = 0;
	u32 base_addr = dcss->start_addr;
	स्थिर काष्ठा dcss_type_data *devtype = dcss->devtype;

	dcss_घड़ीs_enable(dcss);

	ret = dcss_blkctl_init(dcss, base_addr + devtype->blkctl_ofs);
	अगर (ret)
		वापस ret;

	ret = dcss_ctxld_init(dcss, base_addr + devtype->ctxld_ofs);
	अगर (ret)
		जाओ ctxld_err;

	ret = dcss_dtg_init(dcss, base_addr + devtype->dtg_ofs);
	अगर (ret)
		जाओ dtg_err;

	ret = dcss_ss_init(dcss, base_addr + devtype->ss_ofs);
	अगर (ret)
		जाओ ss_err;

	ret = dcss_dpr_init(dcss, base_addr + devtype->dpr_ofs);
	अगर (ret)
		जाओ dpr_err;

	ret = dcss_scaler_init(dcss, base_addr + devtype->scaler_ofs);
	अगर (ret)
		जाओ scaler_err;

	dcss_घड़ीs_disable(dcss);

	वापस 0;

scaler_err:
	dcss_dpr_निकास(dcss->dpr);

dpr_err:
	dcss_ss_निकास(dcss->ss);

ss_err:
	dcss_dtg_निकास(dcss->dtg);

dtg_err:
	dcss_ctxld_निकास(dcss->ctxld);

ctxld_err:
	dcss_blkctl_निकास(dcss->blkctl);

	dcss_घड़ीs_disable(dcss);

	वापस ret;
पूर्ण

अटल व्योम dcss_submodules_stop(काष्ठा dcss_dev *dcss)
अणु
	dcss_घड़ीs_enable(dcss);
	dcss_scaler_निकास(dcss->scaler);
	dcss_dpr_निकास(dcss->dpr);
	dcss_ss_निकास(dcss->ss);
	dcss_dtg_निकास(dcss->dtg);
	dcss_ctxld_निकास(dcss->ctxld);
	dcss_blkctl_निकास(dcss->blkctl);
	dcss_घड़ीs_disable(dcss);
पूर्ण

अटल पूर्णांक dcss_clks_init(काष्ठा dcss_dev *dcss)
अणु
	पूर्णांक i;
	काष्ठा अणु
		स्थिर अक्षर *id;
		काष्ठा clk **clk;
	पूर्ण clks[] = अणु
		अणु"apb",   &dcss->apb_clkपूर्ण,
		अणु"axi",   &dcss->axi_clkपूर्ण,
		अणु"pix",   &dcss->pix_clkपूर्ण,
		अणु"rtrm",  &dcss->rtrm_clkपूर्ण,
		अणु"dtrc",  &dcss->dtrc_clkपूर्ण,
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(clks); i++) अणु
		*clks[i].clk = devm_clk_get(dcss->dev, clks[i].id);
		अगर (IS_ERR(*clks[i].clk)) अणु
			dev_err(dcss->dev, "failed to get %s clock\n",
				clks[i].id);
			वापस PTR_ERR(*clks[i].clk);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dcss_clks_release(काष्ठा dcss_dev *dcss)
अणु
	devm_clk_put(dcss->dev, dcss->dtrc_clk);
	devm_clk_put(dcss->dev, dcss->rtrm_clk);
	devm_clk_put(dcss->dev, dcss->pix_clk);
	devm_clk_put(dcss->dev, dcss->axi_clk);
	devm_clk_put(dcss->dev, dcss->apb_clk);
पूर्ण

काष्ठा dcss_dev *dcss_dev_create(काष्ठा device *dev, bool hdmi_output)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक ret;
	काष्ठा resource *res;
	काष्ठा dcss_dev *dcss;
	स्थिर काष्ठा dcss_type_data *devtype;

	devtype = of_device_get_match_data(dev);
	अगर (!devtype) अणु
		dev_err(dev, "no device match found\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(dev, "cannot get memory resource\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	dcss = kzalloc(माप(*dcss), GFP_KERNEL);
	अगर (!dcss)
		वापस ERR_PTR(-ENOMEM);

	dcss->dev = dev;
	dcss->devtype = devtype;
	dcss->hdmi_output = hdmi_output;

	ret = dcss_clks_init(dcss);
	अगर (ret) अणु
		dev_err(dev, "clocks initialization failed\n");
		जाओ err;
	पूर्ण

	dcss->of_port = of_graph_get_port_by_id(dev->of_node, 0);
	अगर (!dcss->of_port) अणु
		dev_err(dev, "no port@0 node in %s\n", dev->of_node->full_name);
		ret = -ENODEV;
		जाओ clks_err;
	पूर्ण

	dcss->start_addr = res->start;

	ret = dcss_submodules_init(dcss);
	अगर (ret) अणु
		dev_err(dev, "submodules initialization failed\n");
		जाओ clks_err;
	पूर्ण

	init_completion(&dcss->disable_completion);

	pm_runसमय_set_स्वतःsuspend_delay(dev, 100);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_allow(dev);
	pm_runसमय_enable(dev);

	वापस dcss;

clks_err:
	dcss_clks_release(dcss);

err:
	kमुक्त(dcss);

	वापस ERR_PTR(ret);
पूर्ण

व्योम dcss_dev_destroy(काष्ठा dcss_dev *dcss)
अणु
	अगर (!pm_runसमय_suspended(dcss->dev)) अणु
		dcss_ctxld_suspend(dcss->ctxld);
		dcss_घड़ीs_disable(dcss);
	पूर्ण

	pm_runसमय_disable(dcss->dev);

	dcss_submodules_stop(dcss);

	dcss_clks_release(dcss);

	kमुक्त(dcss);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक dcss_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा dcss_dev *dcss = dcss_drv_dev_to_dcss(dev);
	काष्ठा drm_device *ddev = dcss_drv_dev_to_drm(dev);
	काष्ठा dcss_kms_dev *kms = container_of(ddev, काष्ठा dcss_kms_dev, base);
	पूर्णांक ret;

	drm_bridge_connector_disable_hpd(kms->connector);

	drm_mode_config_helper_suspend(ddev);

	अगर (pm_runसमय_suspended(dev))
		वापस 0;

	ret = dcss_ctxld_suspend(dcss->ctxld);
	अगर (ret)
		वापस ret;

	dcss_घड़ीs_disable(dcss);

	वापस 0;
पूर्ण

पूर्णांक dcss_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा dcss_dev *dcss = dcss_drv_dev_to_dcss(dev);
	काष्ठा drm_device *ddev = dcss_drv_dev_to_drm(dev);
	काष्ठा dcss_kms_dev *kms = container_of(ddev, काष्ठा dcss_kms_dev, base);

	अगर (pm_runसमय_suspended(dev)) अणु
		drm_mode_config_helper_resume(ddev);
		वापस 0;
	पूर्ण

	dcss_घड़ीs_enable(dcss);

	dcss_blkctl_cfg(dcss->blkctl);

	dcss_ctxld_resume(dcss->ctxld);

	drm_mode_config_helper_resume(ddev);

	drm_bridge_connector_enable_hpd(kms->connector);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_PM
पूर्णांक dcss_dev_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dcss_dev *dcss = dcss_drv_dev_to_dcss(dev);
	पूर्णांक ret;

	ret = dcss_ctxld_suspend(dcss->ctxld);
	अगर (ret)
		वापस ret;

	dcss_घड़ीs_disable(dcss);

	वापस 0;
पूर्ण

पूर्णांक dcss_dev_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dcss_dev *dcss = dcss_drv_dev_to_dcss(dev);

	dcss_घड़ीs_enable(dcss);

	dcss_blkctl_cfg(dcss->blkctl);

	dcss_ctxld_resume(dcss->ctxld);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */
