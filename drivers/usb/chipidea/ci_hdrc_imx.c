<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 * Copyright (C) 2012 Marek Vasut <marex@denx.de>
 * on behalf of DENX Software Engineering GmbH
 */

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/usb/chipidea.h>
#समावेश <linux/usb/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_qos.h>

#समावेश "ci.h"
#समावेश "ci_hdrc_imx.h"

काष्ठा ci_hdrc_imx_platक्रमm_flag अणु
	अचिन्हित पूर्णांक flags;
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag imx23_usb_data = अणु
	.flags = CI_HDRC_TURN_VBUS_EARLY_ON |
		CI_HDRC_DISABLE_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag imx27_usb_data = अणु
	.flags = CI_HDRC_DISABLE_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag imx28_usb_data = अणु
	.flags = CI_HDRC_IMX28_WRITE_FIX |
		CI_HDRC_TURN_VBUS_EARLY_ON |
		CI_HDRC_DISABLE_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag imx6q_usb_data = अणु
	.flags = CI_HDRC_SUPPORTS_RUNTIME_PM |
		CI_HDRC_TURN_VBUS_EARLY_ON |
		CI_HDRC_DISABLE_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag imx6sl_usb_data = अणु
	.flags = CI_HDRC_SUPPORTS_RUNTIME_PM |
		CI_HDRC_TURN_VBUS_EARLY_ON |
		CI_HDRC_DISABLE_HOST_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag imx6sx_usb_data = अणु
	.flags = CI_HDRC_SUPPORTS_RUNTIME_PM |
		CI_HDRC_TURN_VBUS_EARLY_ON |
		CI_HDRC_DISABLE_HOST_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag imx6ul_usb_data = अणु
	.flags = CI_HDRC_SUPPORTS_RUNTIME_PM |
		CI_HDRC_TURN_VBUS_EARLY_ON |
		CI_HDRC_DISABLE_DEVICE_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag imx7d_usb_data = अणु
	.flags = CI_HDRC_SUPPORTS_RUNTIME_PM,
पूर्ण;

अटल स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag imx7ulp_usb_data = अणु
	.flags = CI_HDRC_SUPPORTS_RUNTIME_PM |
		CI_HDRC_PMQOS,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ci_hdrc_imx_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-usb", .data = &imx23_usb_dataपूर्ण,
	अणु .compatible = "fsl,imx28-usb", .data = &imx28_usb_dataपूर्ण,
	अणु .compatible = "fsl,imx27-usb", .data = &imx27_usb_dataपूर्ण,
	अणु .compatible = "fsl,imx6q-usb", .data = &imx6q_usb_dataपूर्ण,
	अणु .compatible = "fsl,imx6sl-usb", .data = &imx6sl_usb_dataपूर्ण,
	अणु .compatible = "fsl,imx6sx-usb", .data = &imx6sx_usb_dataपूर्ण,
	अणु .compatible = "fsl,imx6ul-usb", .data = &imx6ul_usb_dataपूर्ण,
	अणु .compatible = "fsl,imx7d-usb", .data = &imx7d_usb_dataपूर्ण,
	अणु .compatible = "fsl,imx7ulp-usb", .data = &imx7ulp_usb_dataपूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ci_hdrc_imx_dt_ids);

काष्ठा ci_hdrc_imx_data अणु
	काष्ठा usb_phy *phy;
	काष्ठा platक्रमm_device *ci_pdev;
	काष्ठा clk *clk;
	काष्ठा imx_usbmisc_data *usbmisc_data;
	bool supports_runसमय_pm;
	bool override_phy_control;
	bool in_lpm;
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pinctrl_hsic_active;
	काष्ठा regulator *hsic_pad_regulator;
	/* SoC beक्रमe i.mx6 (except imx23/imx28) needs three clks */
	bool need_three_clks;
	काष्ठा clk *clk_ipg;
	काष्ठा clk *clk_ahb;
	काष्ठा clk *clk_per;
	/* --------------------------------- */
	काष्ठा pm_qos_request pm_qos_req;
	स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag *plat_data;
पूर्ण;

/* Common functions shared by usbmisc drivers */

अटल काष्ठा imx_usbmisc_data *usbmisc_get_init_data(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *misc_pdev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा of_phandle_args args;
	काष्ठा imx_usbmisc_data *data;
	पूर्णांक ret;

	/*
	 * In हाल the fsl,usbmisc property is not present this device करोesn't
	 * need usbmisc. Return शून्य (which is no error here)
	 */
	अगर (!of_get_property(np, "fsl,usbmisc", शून्य))
		वापस शून्य;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	ret = of_parse_phandle_with_args(np, "fsl,usbmisc", "#index-cells",
					0, &args);
	अगर (ret) अणु
		dev_err(dev, "Failed to parse property fsl,usbmisc, errno %d\n",
			ret);
		वापस ERR_PTR(ret);
	पूर्ण

	data->index = args.args[0];

	misc_pdev = of_find_device_by_node(args.np);
	of_node_put(args.np);

	अगर (!misc_pdev)
		वापस ERR_PTR(-EPROBE_DEFER);

	अगर (!platक्रमm_get_drvdata(misc_pdev)) अणु
		put_device(&misc_pdev->dev);
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण
	data->dev = &misc_pdev->dev;

	/*
	 * Check the various over current related properties. If over current
	 * detection is disabled we're not पूर्णांकerested in the polarity.
	 */
	अगर (of_find_property(np, "disable-over-current", शून्य)) अणु
		data->disable_oc = 1;
	पूर्ण अन्यथा अगर (of_find_property(np, "over-current-active-high", शून्य)) अणु
		data->oc_pol_active_low = 0;
		data->oc_pol_configured = 1;
	पूर्ण अन्यथा अगर (of_find_property(np, "over-current-active-low", शून्य)) अणु
		data->oc_pol_active_low = 1;
		data->oc_pol_configured = 1;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "No over current polarity defined\n");
	पूर्ण

	data->pwr_pol = of_property_पढ़ो_bool(np, "power-active-high");
	data->evकरो = of_property_पढ़ो_bool(np, "external-vbus-divider");

	अगर (of_usb_get_phy_mode(np) == USBPHY_INTERFACE_MODE_ULPI)
		data->ulpi = 1;

	of_property_पढ़ो_u32(np, "samsung,picophy-pre-emp-curr-control",
			&data->emp_curr_control);
	of_property_पढ़ो_u32(np, "samsung,picophy-dc-vol-level-adjust",
			&data->dc_vol_level_adjust);

	वापस data;
पूर्ण

/* End of common functions shared by usbmisc drivers*/
अटल पूर्णांक imx_get_clks(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	data->clk_ipg = devm_clk_get(dev, "ipg");
	अगर (IS_ERR(data->clk_ipg)) अणु
		/* If the platक्रमm only needs one घड़ीs */
		data->clk = devm_clk_get(dev, शून्य);
		अगर (IS_ERR(data->clk)) अणु
			ret = PTR_ERR(data->clk);
			dev_err(dev,
				"Failed to get clks, err=%ld,%ld\n",
				PTR_ERR(data->clk), PTR_ERR(data->clk_ipg));
			वापस ret;
		पूर्ण
		वापस ret;
	पूर्ण

	data->clk_ahb = devm_clk_get(dev, "ahb");
	अगर (IS_ERR(data->clk_ahb)) अणु
		ret = PTR_ERR(data->clk_ahb);
		dev_err(dev,
			"Failed to get ahb clock, err=%d\n", ret);
		वापस ret;
	पूर्ण

	data->clk_per = devm_clk_get(dev, "per");
	अगर (IS_ERR(data->clk_per)) अणु
		ret = PTR_ERR(data->clk_per);
		dev_err(dev,
			"Failed to get per clock, err=%d\n", ret);
		वापस ret;
	पूर्ण

	data->need_three_clks = true;
	वापस ret;
पूर्ण

अटल पूर्णांक imx_prepare_enable_clks(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (data->need_three_clks) अणु
		ret = clk_prepare_enable(data->clk_ipg);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to prepare/enable ipg clk, err=%d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = clk_prepare_enable(data->clk_ahb);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to prepare/enable ahb clk, err=%d\n",
				ret);
			clk_disable_unprepare(data->clk_ipg);
			वापस ret;
		पूर्ण

		ret = clk_prepare_enable(data->clk_per);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to prepare/enable per clk, err=%d\n",
				ret);
			clk_disable_unprepare(data->clk_ahb);
			clk_disable_unprepare(data->clk_ipg);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(data->clk);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to prepare/enable clk, err=%d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम imx_disable_unprepare_clks(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc_imx_data *data = dev_get_drvdata(dev);

	अगर (data->need_three_clks) अणु
		clk_disable_unprepare(data->clk_per);
		clk_disable_unprepare(data->clk_ahb);
		clk_disable_unprepare(data->clk_ipg);
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(data->clk);
	पूर्ण
पूर्ण

अटल पूर्णांक ci_hdrc_imx_notअगरy_event(काष्ठा ci_hdrc *ci, अचिन्हित पूर्णांक event)
अणु
	काष्ठा device *dev = ci->dev->parent;
	काष्ठा ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	काष्ठा imx_usbmisc_data *mdata = data->usbmisc_data;

	चयन (event) अणु
	हाल CI_HDRC_IMX_HSIC_ACTIVE_EVENT:
		अगर (data->pinctrl) अणु
			ret = pinctrl_select_state(data->pinctrl,
					data->pinctrl_hsic_active);
			अगर (ret)
				dev_err(dev,
					"hsic_active select failed, err=%d\n",
					ret);
		पूर्ण
		अवरोध;
	हाल CI_HDRC_IMX_HSIC_SUSPEND_EVENT:
		ret = imx_usbmisc_hsic_set_connect(mdata);
		अगर (ret)
			dev_err(dev,
				"hsic_set_connect failed, err=%d\n", ret);
		अवरोध;
	हाल CI_HDRC_CONTROLLER_VBUS_EVENT:
		अगर (ci->vbus_active)
			ret = imx_usbmisc_अक्षरger_detection(mdata, true);
		अन्यथा
			ret = imx_usbmisc_अक्षरger_detection(mdata, false);
		अगर (ci->usb_phy)
			schedule_work(&ci->usb_phy->chg_work);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ci_hdrc_imx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ci_hdrc_imx_data *data;
	काष्ठा ci_hdrc_platक्रमm_data pdata = अणु
		.name		= dev_name(&pdev->dev),
		.capoffset	= DEF_CAPOFFSET,
		.notअगरy_event	= ci_hdrc_imx_notअगरy_event,
	पूर्ण;
	पूर्णांक ret;
	स्थिर काष्ठा ci_hdrc_imx_platक्रमm_flag *imx_platक्रमm_flag;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;

	imx_platक्रमm_flag = of_device_get_match_data(&pdev->dev);

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->plat_data = imx_platक्रमm_flag;
	pdata.flags |= imx_platक्रमm_flag->flags;
	platक्रमm_set_drvdata(pdev, data);
	data->usbmisc_data = usbmisc_get_init_data(dev);
	अगर (IS_ERR(data->usbmisc_data))
		वापस PTR_ERR(data->usbmisc_data);

	अगर ((of_usb_get_phy_mode(dev->of_node) == USBPHY_INTERFACE_MODE_HSIC)
		&& data->usbmisc_data) अणु
		pdata.flags |= CI_HDRC_IMX_IS_HSIC;
		data->usbmisc_data->hsic = 1;
		data->pinctrl = devm_pinctrl_get(dev);
		अगर (PTR_ERR(data->pinctrl) == -ENODEV)
			data->pinctrl = शून्य;
		अन्यथा अगर (IS_ERR(data->pinctrl)) अणु
			अगर (PTR_ERR(data->pinctrl) != -EPROBE_DEFER)
				dev_err(dev, "pinctrl get failed, err=%ld\n",
					PTR_ERR(data->pinctrl));
			वापस PTR_ERR(data->pinctrl);
		पूर्ण

		data->hsic_pad_regulator =
				devm_regulator_get_optional(dev, "hsic");
		अगर (PTR_ERR(data->hsic_pad_regulator) == -ENODEV) अणु
			/* no pad regualator is needed */
			data->hsic_pad_regulator = शून्य;
		पूर्ण अन्यथा अगर (IS_ERR(data->hsic_pad_regulator)) अणु
			अगर (PTR_ERR(data->hsic_pad_regulator) != -EPROBE_DEFER)
				dev_err(dev,
					"Get HSIC pad regulator error: %ld\n",
					PTR_ERR(data->hsic_pad_regulator));
			वापस PTR_ERR(data->hsic_pad_regulator);
		पूर्ण

		अगर (data->hsic_pad_regulator) अणु
			ret = regulator_enable(data->hsic_pad_regulator);
			अगर (ret) अणु
				dev_err(dev,
					"Failed to enable HSIC pad regulator\n");
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	/* HSIC pinctrl handling */
	अगर (data->pinctrl) अणु
		काष्ठा pinctrl_state *pinctrl_hsic_idle;

		pinctrl_hsic_idle = pinctrl_lookup_state(data->pinctrl, "idle");
		अगर (IS_ERR(pinctrl_hsic_idle)) अणु
			dev_err(dev,
				"pinctrl_hsic_idle lookup failed, err=%ld\n",
					PTR_ERR(pinctrl_hsic_idle));
			वापस PTR_ERR(pinctrl_hsic_idle);
		पूर्ण

		ret = pinctrl_select_state(data->pinctrl, pinctrl_hsic_idle);
		अगर (ret) अणु
			dev_err(dev, "hsic_idle select failed, err=%d\n", ret);
			वापस ret;
		पूर्ण

		data->pinctrl_hsic_active = pinctrl_lookup_state(data->pinctrl,
								"active");
		अगर (IS_ERR(data->pinctrl_hsic_active)) अणु
			dev_err(dev,
				"pinctrl_hsic_active lookup failed, err=%ld\n",
					PTR_ERR(data->pinctrl_hsic_active));
			वापस PTR_ERR(data->pinctrl_hsic_active);
		पूर्ण
	पूर्ण

	अगर (pdata.flags & CI_HDRC_PMQOS)
		cpu_latency_qos_add_request(&data->pm_qos_req, 0);

	ret = imx_get_clks(dev);
	अगर (ret)
		जाओ disable_hsic_regulator;

	ret = imx_prepare_enable_clks(dev);
	अगर (ret)
		जाओ disable_hsic_regulator;

	data->phy = devm_usb_get_phy_by_phandle(dev, "fsl,usbphy", 0);
	अगर (IS_ERR(data->phy)) अणु
		ret = PTR_ERR(data->phy);
		/* Return -EINVAL अगर no usbphy is available */
		अगर (ret == -ENODEV)
			data->phy = शून्य;
		अन्यथा
			जाओ err_clk;
	पूर्ण

	pdata.usb_phy = data->phy;
	अगर (data->usbmisc_data)
		data->usbmisc_data->usb_phy = data->phy;

	अगर ((of_device_is_compatible(np, "fsl,imx53-usb") ||
	     of_device_is_compatible(np, "fsl,imx51-usb")) && pdata.usb_phy &&
	    of_usb_get_phy_mode(np) == USBPHY_INTERFACE_MODE_ULPI) अणु
		pdata.flags |= CI_HDRC_OVERRIDE_PHY_CONTROL;
		data->override_phy_control = true;
		usb_phy_init(pdata.usb_phy);
	पूर्ण

	अगर (pdata.flags & CI_HDRC_SUPPORTS_RUNTIME_PM)
		data->supports_runसमय_pm = true;

	ret = imx_usbmisc_init(data->usbmisc_data);
	अगर (ret) अणु
		dev_err(dev, "usbmisc init failed, ret=%d\n", ret);
		जाओ err_clk;
	पूर्ण

	data->ci_pdev = ci_hdrc_add_device(dev,
				pdev->resource, pdev->num_resources,
				&pdata);
	अगर (IS_ERR(data->ci_pdev)) अणु
		ret = PTR_ERR(data->ci_pdev);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "ci_hdrc_add_device failed, err=%d\n",
					ret);
		जाओ err_clk;
	पूर्ण

	अगर (data->usbmisc_data) अणु
		अगर (!IS_ERR(pdata.id_extcon.edev) ||
		    of_property_पढ़ो_bool(np, "usb-role-switch"))
			data->usbmisc_data->ext_id = 1;

		अगर (!IS_ERR(pdata.vbus_extcon.edev) ||
		    of_property_पढ़ो_bool(np, "usb-role-switch"))
			data->usbmisc_data->ext_vbus = 1;

		/* usbmisc needs to know dr mode to choose wakeup setting */
		data->usbmisc_data->available_role =
			ci_hdrc_query_available_role(data->ci_pdev);
	पूर्ण

	ret = imx_usbmisc_init_post(data->usbmisc_data);
	अगर (ret) अणु
		dev_err(dev, "usbmisc post failed, ret=%d\n", ret);
		जाओ disable_device;
	पूर्ण

	अगर (data->supports_runसमय_pm) अणु
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	device_set_wakeup_capable(dev, true);

	वापस 0;

disable_device:
	ci_hdrc_हटाओ_device(data->ci_pdev);
err_clk:
	imx_disable_unprepare_clks(dev);
disable_hsic_regulator:
	अगर (data->hsic_pad_regulator)
		/* करोn't overग_लिखो original ret (cf. EPROBE_DEFER) */
		regulator_disable(data->hsic_pad_regulator);
	अगर (pdata.flags & CI_HDRC_PMQOS)
		cpu_latency_qos_हटाओ_request(&data->pm_qos_req);
	data->ci_pdev = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक ci_hdrc_imx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ci_hdrc_imx_data *data = platक्रमm_get_drvdata(pdev);

	अगर (data->supports_runसमय_pm) अणु
		pm_runसमय_get_sync(&pdev->dev);
		pm_runसमय_disable(&pdev->dev);
		pm_runसमय_put_noidle(&pdev->dev);
	पूर्ण
	अगर (data->ci_pdev)
		ci_hdrc_हटाओ_device(data->ci_pdev);
	अगर (data->override_phy_control)
		usb_phy_shutकरोwn(data->phy);
	अगर (data->ci_pdev) अणु
		imx_disable_unprepare_clks(&pdev->dev);
		अगर (data->plat_data->flags & CI_HDRC_PMQOS)
			cpu_latency_qos_हटाओ_request(&data->pm_qos_req);
		अगर (data->hsic_pad_regulator)
			regulator_disable(data->hsic_pad_regulator);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ci_hdrc_imx_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	ci_hdrc_imx_हटाओ(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused imx_controller_suspend(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	dev_dbg(dev, "at %s\n", __func__);

	ret = imx_usbmisc_hsic_set_clk(data->usbmisc_data, false);
	अगर (ret) अणु
		dev_err(dev, "usbmisc hsic_set_clk failed, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	imx_disable_unprepare_clks(dev);
	अगर (data->plat_data->flags & CI_HDRC_PMQOS)
		cpu_latency_qos_हटाओ_request(&data->pm_qos_req);

	data->in_lpm = true;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused imx_controller_resume(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	dev_dbg(dev, "at %s\n", __func__);

	अगर (!data->in_lpm) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण

	अगर (data->plat_data->flags & CI_HDRC_PMQOS)
		cpu_latency_qos_add_request(&data->pm_qos_req, 0);

	ret = imx_prepare_enable_clks(dev);
	अगर (ret)
		वापस ret;

	data->in_lpm = false;

	ret = imx_usbmisc_set_wakeup(data->usbmisc_data, false);
	अगर (ret) अणु
		dev_err(dev, "usbmisc set_wakeup failed, ret=%d\n", ret);
		जाओ clk_disable;
	पूर्ण

	ret = imx_usbmisc_hsic_set_clk(data->usbmisc_data, true);
	अगर (ret) अणु
		dev_err(dev, "usbmisc hsic_set_clk failed, ret=%d\n", ret);
		जाओ hsic_set_clk_fail;
	पूर्ण

	वापस 0;

hsic_set_clk_fail:
	imx_usbmisc_set_wakeup(data->usbmisc_data, true);
clk_disable:
	imx_disable_unprepare_clks(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ci_hdrc_imx_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	काष्ठा ci_hdrc_imx_data *data = dev_get_drvdata(dev);

	अगर (data->in_lpm)
		/* The core's suspend doesn't run */
		वापस 0;

	अगर (device_may_wakeup(dev)) अणु
		ret = imx_usbmisc_set_wakeup(data->usbmisc_data, true);
		अगर (ret) अणु
			dev_err(dev, "usbmisc set_wakeup failed, ret=%d\n",
					ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = imx_controller_suspend(dev);
	अगर (ret)
		वापस ret;

	pinctrl_pm_select_sleep_state(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ci_hdrc_imx_resume(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	pinctrl_pm_select_शेष_state(dev);
	ret = imx_controller_resume(dev);
	अगर (!ret && data->supports_runसमय_pm) अणु
		pm_runसमय_disable(dev);
		pm_runसमय_set_active(dev);
		pm_runसमय_enable(dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ci_hdrc_imx_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा ci_hdrc_imx_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (data->in_lpm) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण

	ret = imx_usbmisc_set_wakeup(data->usbmisc_data, true);
	अगर (ret) अणु
		dev_err(dev, "usbmisc set_wakeup failed, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस imx_controller_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused ci_hdrc_imx_runसमय_resume(काष्ठा device *dev)
अणु
	वापस imx_controller_resume(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ci_hdrc_imx_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ci_hdrc_imx_suspend, ci_hdrc_imx_resume)
	SET_RUNTIME_PM_OPS(ci_hdrc_imx_runसमय_suspend,
			ci_hdrc_imx_runसमय_resume, शून्य)
पूर्ण;
अटल काष्ठा platक्रमm_driver ci_hdrc_imx_driver = अणु
	.probe = ci_hdrc_imx_probe,
	.हटाओ = ci_hdrc_imx_हटाओ,
	.shutकरोwn = ci_hdrc_imx_shutकरोwn,
	.driver = अणु
		.name = "imx_usb",
		.of_match_table = ci_hdrc_imx_dt_ids,
		.pm = &ci_hdrc_imx_pm_ops,
	 पूर्ण,
पूर्ण;

module_platक्रमm_driver(ci_hdrc_imx_driver);

MODULE_ALIAS("platform:imx-usb");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("CI HDRC i.MX USB binding");
MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_AUTHOR("Richard Zhao <richard.zhao@freescale.com>");
