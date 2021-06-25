<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Universal Flash Storage Host controller Platक्रमm bus based glue driver
 * Copyright (C) 2011-2013 Samsung India Software Operations
 *
 * Authors:
 *	Santosh Yaraganavi <santosh.sy@samsung.com>
 *	Vinayak Holikatti <h.vinayak@samsung.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>

#समावेश "ufshcd.h"
#समावेश "ufshcd-pltfrm.h"
#समावेश "unipro.h"

#घोषणा UFSHCD_DEFAULT_LANES_PER_सूचीECTION		2

अटल पूर्णांक ufshcd_parse_घड़ी_info(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret = 0;
	पूर्णांक cnt;
	पूर्णांक i;
	काष्ठा device *dev = hba->dev;
	काष्ठा device_node *np = dev->of_node;
	अक्षर *name;
	u32 *clkfreq = शून्य;
	काष्ठा ufs_clk_info *clki;
	पूर्णांक len = 0;
	माप_प्रकार sz = 0;

	अगर (!np)
		जाओ out;

	cnt = of_property_count_strings(np, "clock-names");
	अगर (!cnt || (cnt == -EINVAL)) अणु
		dev_info(dev, "%s: Unable to find clocks, assuming enabled\n",
				__func__);
	पूर्ण अन्यथा अगर (cnt < 0) अणु
		dev_err(dev, "%s: count clock strings failed, err %d\n",
				__func__, cnt);
		ret = cnt;
	पूर्ण

	अगर (cnt <= 0)
		जाओ out;

	अगर (!of_get_property(np, "freq-table-hz", &len)) अणु
		dev_info(dev, "freq-table-hz property not specified\n");
		जाओ out;
	पूर्ण

	अगर (len <= 0)
		जाओ out;

	sz = len / माप(*clkfreq);
	अगर (sz != 2 * cnt) अणु
		dev_err(dev, "%s len mismatch\n", "freq-table-hz");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	clkfreq = devm_kसुस्मृति(dev, sz, माप(*clkfreq),
			       GFP_KERNEL);
	अगर (!clkfreq) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = of_property_पढ़ो_u32_array(np, "freq-table-hz",
			clkfreq, sz);
	अगर (ret && (ret != -EINVAL)) अणु
		dev_err(dev, "%s: error reading array %d\n",
				"freq-table-hz", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < sz; i += 2) अणु
		ret = of_property_पढ़ो_string_index(np,
				"clock-names", i/2, (स्थिर अक्षर **)&name);
		अगर (ret)
			जाओ out;

		clki = devm_kzalloc(dev, माप(*clki), GFP_KERNEL);
		अगर (!clki) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		clki->min_freq = clkfreq[i];
		clki->max_freq = clkfreq[i+1];
		clki->name = kstrdup(name, GFP_KERNEL);
		अगर (!म_भेद(name, "ref_clk"))
			clki->keep_link_active = true;
		dev_dbg(dev, "%s: min %u max %u name %s\n", "freq-table-hz",
				clki->min_freq, clki->max_freq, clki->name);
		list_add_tail(&clki->list, &hba->clk_list_head);
	पूर्ण
out:
	वापस ret;
पूर्ण

#घोषणा MAX_PROP_SIZE 32
अटल पूर्णांक ufshcd_populate_vreg(काष्ठा device *dev, स्थिर अक्षर *name,
		काष्ठा ufs_vreg **out_vreg)
अणु
	अक्षर prop_name[MAX_PROP_SIZE];
	काष्ठा ufs_vreg *vreg = शून्य;
	काष्ठा device_node *np = dev->of_node;

	अगर (!np) अणु
		dev_err(dev, "%s: non DT initialization\n", __func__);
		जाओ out;
	पूर्ण

	snम_लिखो(prop_name, MAX_PROP_SIZE, "%s-supply", name);
	अगर (!of_parse_phandle(np, prop_name, 0)) अणु
		dev_info(dev, "%s: Unable to find %s regulator, assuming enabled\n",
				__func__, prop_name);
		जाओ out;
	पूर्ण

	vreg = devm_kzalloc(dev, माप(*vreg), GFP_KERNEL);
	अगर (!vreg)
		वापस -ENOMEM;

	vreg->name = kstrdup(name, GFP_KERNEL);

	snम_लिखो(prop_name, MAX_PROP_SIZE, "%s-max-microamp", name);
	अगर (of_property_पढ़ो_u32(np, prop_name, &vreg->max_uA)) अणु
		dev_info(dev, "%s: unable to find %s\n", __func__, prop_name);
		vreg->max_uA = 0;
	पूर्ण
out:
	*out_vreg = vreg;
	वापस 0;
पूर्ण

/**
 * ufshcd_parse_regulator_info - get regulator info from device tree
 * @hba: per adapter instance
 *
 * Get regulator info from device tree क्रम vcc, vccq, vccq2 घातer supplies.
 * If any of the supplies are not defined it is assumed that they are always-on
 * and hence वापस zero. If the property is defined but parsing is failed
 * then वापस corresponding error.
 */
अटल पूर्णांक ufshcd_parse_regulator_info(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;
	काष्ठा device *dev = hba->dev;
	काष्ठा ufs_vreg_info *info = &hba->vreg_info;

	err = ufshcd_populate_vreg(dev, "vdd-hba", &info->vdd_hba);
	अगर (err)
		जाओ out;

	err = ufshcd_populate_vreg(dev, "vcc", &info->vcc);
	अगर (err)
		जाओ out;

	err = ufshcd_populate_vreg(dev, "vccq", &info->vccq);
	अगर (err)
		जाओ out;

	err = ufshcd_populate_vreg(dev, "vccq2", &info->vccq2);
out:
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PM
/**
 * ufshcd_pltfrm_suspend - suspend घातer management function
 * @dev: poपूर्णांकer to device handle
 *
 * Returns 0 अगर successful
 * Returns non-zero otherwise
 */
पूर्णांक ufshcd_pltfrm_suspend(काष्ठा device *dev)
अणु
	वापस ufshcd_प्रणाली_suspend(dev_get_drvdata(dev));
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_pltfrm_suspend);

/**
 * ufshcd_pltfrm_resume - resume घातer management function
 * @dev: poपूर्णांकer to device handle
 *
 * Returns 0 अगर successful
 * Returns non-zero otherwise
 */
पूर्णांक ufshcd_pltfrm_resume(काष्ठा device *dev)
अणु
	वापस ufshcd_प्रणाली_resume(dev_get_drvdata(dev));
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_pltfrm_resume);

पूर्णांक ufshcd_pltfrm_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस ufshcd_runसमय_suspend(dev_get_drvdata(dev));
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_pltfrm_runसमय_suspend);

पूर्णांक ufshcd_pltfrm_runसमय_resume(काष्ठा device *dev)
अणु
	वापस ufshcd_runसमय_resume(dev_get_drvdata(dev));
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_pltfrm_runसमय_resume);

पूर्णांक ufshcd_pltfrm_runसमय_idle(काष्ठा device *dev)
अणु
	वापस ufshcd_runसमय_idle(dev_get_drvdata(dev));
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_pltfrm_runसमय_idle);

#पूर्ण_अगर /* CONFIG_PM */

व्योम ufshcd_pltfrm_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	ufshcd_shutकरोwn((काष्ठा ufs_hba *)platक्रमm_get_drvdata(pdev));
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_pltfrm_shutकरोwn);

अटल व्योम ufshcd_init_lanes_per_dir(काष्ठा ufs_hba *hba)
अणु
	काष्ठा device *dev = hba->dev;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(dev->of_node, "lanes-per-direction",
		&hba->lanes_per_direction);
	अगर (ret) अणु
		dev_dbg(hba->dev,
			"%s: failed to read lanes-per-direction, ret=%d\n",
			__func__, ret);
		hba->lanes_per_direction = UFSHCD_DEFAULT_LANES_PER_सूचीECTION;
	पूर्ण
पूर्ण

/**
 * ufshcd_get_pwr_dev_param - get finally agreed attributes क्रम
 *                            घातer mode change
 * @pltfrm_param: poपूर्णांकer to platक्रमm parameters
 * @dev_max: poपूर्णांकer to device attributes
 * @agreed_pwr: वापसed agreed attributes
 *
 * Returns 0 on success, non-zero value on failure
 */
पूर्णांक ufshcd_get_pwr_dev_param(काष्ठा ufs_dev_params *pltfrm_param,
			     काष्ठा ufs_pa_layer_attr *dev_max,
			     काष्ठा ufs_pa_layer_attr *agreed_pwr)
अणु
	पूर्णांक min_pltfrm_gear;
	पूर्णांक min_dev_gear;
	bool is_dev_sup_hs = false;
	bool is_pltfrm_max_hs = false;

	अगर (dev_max->pwr_rx == FAST_MODE)
		is_dev_sup_hs = true;

	अगर (pltfrm_param->desired_working_mode == UFS_HS_MODE) अणु
		is_pltfrm_max_hs = true;
		min_pltfrm_gear = min_t(u32, pltfrm_param->hs_rx_gear,
					pltfrm_param->hs_tx_gear);
	पूर्ण अन्यथा अणु
		min_pltfrm_gear = min_t(u32, pltfrm_param->pwm_rx_gear,
					pltfrm_param->pwm_tx_gear);
	पूर्ण

	/*
	 * device करोesn't support HS but
	 * pltfrm_param->desired_working_mode is HS,
	 * thus device and pltfrm_param करोn't agree
	 */
	अगर (!is_dev_sup_hs && is_pltfrm_max_hs) अणु
		pr_info("%s: device doesn't support HS\n",
			__func__);
		वापस -ENOTSUPP;
	पूर्ण अन्यथा अगर (is_dev_sup_hs && is_pltfrm_max_hs) अणु
		/*
		 * since device supports HS, it supports FAST_MODE.
		 * since pltfrm_param->desired_working_mode is also HS
		 * then final decision (FAST/FASTAUTO) is करोne according
		 * to pltfrm_params as it is the restricting factor
		 */
		agreed_pwr->pwr_rx = pltfrm_param->rx_pwr_hs;
		agreed_pwr->pwr_tx = agreed_pwr->pwr_rx;
	पूर्ण अन्यथा अणु
		/*
		 * here pltfrm_param->desired_working_mode is PWM.
		 * it करोesn't matter whether device supports HS or PWM,
		 * in both हालs pltfrm_param->desired_working_mode will
		 * determine the mode
		 */
		agreed_pwr->pwr_rx = pltfrm_param->rx_pwr_pwm;
		agreed_pwr->pwr_tx = agreed_pwr->pwr_rx;
	पूर्ण

	/*
	 * we would like tx to work in the minimum number of lanes
	 * between device capability and venकरोr preferences.
	 * the same decision will be made क्रम rx
	 */
	agreed_pwr->lane_tx = min_t(u32, dev_max->lane_tx,
				    pltfrm_param->tx_lanes);
	agreed_pwr->lane_rx = min_t(u32, dev_max->lane_rx,
				    pltfrm_param->rx_lanes);

	/* device maximum gear is the minimum between device rx and tx gears */
	min_dev_gear = min_t(u32, dev_max->gear_rx, dev_max->gear_tx);

	/*
	 * अगर both device capabilities and venकरोr pre-defined preferences are
	 * both HS or both PWM then set the minimum gear to be the chosen
	 * working gear.
	 * अगर one is PWM and one is HS then the one that is PWM get to decide
	 * what is the gear, as it is the one that also decided previously what
	 * pwr the device will be configured to.
	 */
	अगर ((is_dev_sup_hs && is_pltfrm_max_hs) ||
	    (!is_dev_sup_hs && !is_pltfrm_max_hs)) अणु
		agreed_pwr->gear_rx =
			min_t(u32, min_dev_gear, min_pltfrm_gear);
	पूर्ण अन्यथा अगर (!is_dev_sup_hs) अणु
		agreed_pwr->gear_rx = min_dev_gear;
	पूर्ण अन्यथा अणु
		agreed_pwr->gear_rx = min_pltfrm_gear;
	पूर्ण
	agreed_pwr->gear_tx = agreed_pwr->gear_rx;

	agreed_pwr->hs_rate = pltfrm_param->hs_rate;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_get_pwr_dev_param);

व्योम ufshcd_init_pwr_dev_param(काष्ठा ufs_dev_params *dev_param)
अणु
	dev_param->tx_lanes = 2;
	dev_param->rx_lanes = 2;
	dev_param->hs_rx_gear = UFS_HS_G3;
	dev_param->hs_tx_gear = UFS_HS_G3;
	dev_param->pwm_rx_gear = UFS_PWM_G4;
	dev_param->pwm_tx_gear = UFS_PWM_G4;
	dev_param->rx_pwr_pwm = SLOW_MODE;
	dev_param->tx_pwr_pwm = SLOW_MODE;
	dev_param->rx_pwr_hs = FAST_MODE;
	dev_param->tx_pwr_hs = FAST_MODE;
	dev_param->hs_rate = PA_HS_MODE_B;
	dev_param->desired_working_mode = UFS_HS_MODE;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_init_pwr_dev_param);

/**
 * ufshcd_pltfrm_init - probe routine of the driver
 * @pdev: poपूर्णांकer to Platक्रमm device handle
 * @vops: poपूर्णांकer to variant ops
 *
 * Returns 0 on success, non-zero value on failure
 */
पूर्णांक ufshcd_pltfrm_init(काष्ठा platक्रमm_device *pdev,
		       स्थिर काष्ठा ufs_hba_variant_ops *vops)
अणु
	काष्ठा ufs_hba *hba;
	व्योम __iomem *mmio_base;
	पूर्णांक irq, err;
	काष्ठा device *dev = &pdev->dev;

	mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mmio_base)) अणु
		err = PTR_ERR(mmio_base);
		जाओ out;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		err = irq;
		जाओ out;
	पूर्ण

	err = ufshcd_alloc_host(dev, &hba);
	अगर (err) अणु
		dev_err(&pdev->dev, "Allocation failed\n");
		जाओ out;
	पूर्ण

	hba->vops = vops;

	err = ufshcd_parse_घड़ी_info(hba);
	अगर (err) अणु
		dev_err(&pdev->dev, "%s: clock parse failed %d\n",
				__func__, err);
		जाओ dealloc_host;
	पूर्ण
	err = ufshcd_parse_regulator_info(hba);
	अगर (err) अणु
		dev_err(&pdev->dev, "%s: regulator init failed %d\n",
				__func__, err);
		जाओ dealloc_host;
	पूर्ण

	ufshcd_init_lanes_per_dir(hba);

	err = ufshcd_init(hba, mmio_base, irq);
	अगर (err) अणु
		dev_err(dev, "Initialization failed\n");
		जाओ dealloc_host;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hba);

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	वापस 0;

dealloc_host:
	ufshcd_dealloc_host(hba);
out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ufshcd_pltfrm_init);

MODULE_AUTHOR("Santosh Yaragnavi <santosh.sy@samsung.com>");
MODULE_AUTHOR("Vinayak Holikatti <h.vinayak@samsung.com>");
MODULE_DESCRIPTION("UFS host controller Platform bus based glue driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(UFSHCD_DRIVER_VERSION);
