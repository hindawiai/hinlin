<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016, Fuzhou Rockchip Electronics Co., Ltd.
 * Author: Lin Huang <hl@rock-chips.com>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/devfreq-event.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/suspend.h>

#समावेश <soc/rockchip/rk3399_grf.h>
#समावेश <soc/rockchip/rockchip_sip.h>

काष्ठा dram_timing अणु
	अचिन्हित पूर्णांक ddr3_speed_bin;
	अचिन्हित पूर्णांक pd_idle;
	अचिन्हित पूर्णांक sr_idle;
	अचिन्हित पूर्णांक sr_mc_gate_idle;
	अचिन्हित पूर्णांक srpd_lite_idle;
	अचिन्हित पूर्णांक standby_idle;
	अचिन्हित पूर्णांक स्वतः_pd_dis_freq;
	अचिन्हित पूर्णांक dram_dll_dis_freq;
	अचिन्हित पूर्णांक phy_dll_dis_freq;
	अचिन्हित पूर्णांक ddr3_odt_dis_freq;
	अचिन्हित पूर्णांक ddr3_drv;
	अचिन्हित पूर्णांक ddr3_odt;
	अचिन्हित पूर्णांक phy_ddr3_ca_drv;
	अचिन्हित पूर्णांक phy_ddr3_dq_drv;
	अचिन्हित पूर्णांक phy_ddr3_odt;
	अचिन्हित पूर्णांक lpddr3_odt_dis_freq;
	अचिन्हित पूर्णांक lpddr3_drv;
	अचिन्हित पूर्णांक lpddr3_odt;
	अचिन्हित पूर्णांक phy_lpddr3_ca_drv;
	अचिन्हित पूर्णांक phy_lpddr3_dq_drv;
	अचिन्हित पूर्णांक phy_lpddr3_odt;
	अचिन्हित पूर्णांक lpddr4_odt_dis_freq;
	अचिन्हित पूर्णांक lpddr4_drv;
	अचिन्हित पूर्णांक lpddr4_dq_odt;
	अचिन्हित पूर्णांक lpddr4_ca_odt;
	अचिन्हित पूर्णांक phy_lpddr4_ca_drv;
	अचिन्हित पूर्णांक phy_lpddr4_ck_cs_drv;
	अचिन्हित पूर्णांक phy_lpddr4_dq_drv;
	अचिन्हित पूर्णांक phy_lpddr4_odt;
पूर्ण;

काष्ठा rk3399_dmcfreq अणु
	काष्ठा device *dev;
	काष्ठा devfreq *devfreq;
	काष्ठा devfreq_simple_ondemand_data ondemand_data;
	काष्ठा clk *dmc_clk;
	काष्ठा devfreq_event_dev *edev;
	काष्ठा mutex lock;
	काष्ठा dram_timing timing;
	काष्ठा regulator *vdd_center;
	काष्ठा regmap *regmap_pmu;
	अचिन्हित दीर्घ rate, target_rate;
	अचिन्हित दीर्घ volt, target_volt;
	अचिन्हित पूर्णांक odt_dis_freq;
	पूर्णांक odt_pd_arg0, odt_pd_arg1;
पूर्ण;

अटल पूर्णांक rk3399_dmcfreq_target(काष्ठा device *dev, अचिन्हित दीर्घ *freq,
				 u32 flags)
अणु
	काष्ठा rk3399_dmcfreq *dmcfreq = dev_get_drvdata(dev);
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ old_clk_rate = dmcfreq->rate;
	अचिन्हित दीर्घ target_volt, target_rate;
	काष्ठा arm_smccc_res res;
	bool odt_enable = false;
	पूर्णांक err;

	opp = devfreq_recommended_opp(dev, freq, flags);
	अगर (IS_ERR(opp))
		वापस PTR_ERR(opp);

	target_rate = dev_pm_opp_get_freq(opp);
	target_volt = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	अगर (dmcfreq->rate == target_rate)
		वापस 0;

	mutex_lock(&dmcfreq->lock);

	अगर (dmcfreq->regmap_pmu) अणु
		अगर (target_rate >= dmcfreq->odt_dis_freq)
			odt_enable = true;

		/*
		 * This makes a SMC call to the TF-A to set the DDR PD
		 * (घातer-करोwn) timings and to enable or disable the
		 * ODT (on-die termination) resistors.
		 */
		arm_smccc_smc(ROCKCHIP_SIP_DRAM_FREQ, dmcfreq->odt_pd_arg0,
			      dmcfreq->odt_pd_arg1,
			      ROCKCHIP_SIP_CONFIG_DRAM_SET_ODT_PD,
			      odt_enable, 0, 0, 0, &res);
	पूर्ण

	/*
	 * If frequency scaling from low to high, adjust voltage first.
	 * If frequency scaling from high to low, adjust frequency first.
	 */
	अगर (old_clk_rate < target_rate) अणु
		err = regulator_set_voltage(dmcfreq->vdd_center, target_volt,
					    target_volt);
		अगर (err) अणु
			dev_err(dev, "Cannot set voltage %lu uV\n",
				target_volt);
			जाओ out;
		पूर्ण
	पूर्ण

	err = clk_set_rate(dmcfreq->dmc_clk, target_rate);
	अगर (err) अणु
		dev_err(dev, "Cannot set frequency %lu (%d)\n", target_rate,
			err);
		regulator_set_voltage(dmcfreq->vdd_center, dmcfreq->volt,
				      dmcfreq->volt);
		जाओ out;
	पूर्ण

	/*
	 * Check the dpll rate,
	 * There only two result we will get,
	 * 1. Ddr frequency scaling fail, we still get the old rate.
	 * 2. Ddr frequency scaling sucessful, we get the rate we set.
	 */
	dmcfreq->rate = clk_get_rate(dmcfreq->dmc_clk);

	/* If get the incorrect rate, set voltage to old value. */
	अगर (dmcfreq->rate != target_rate) अणु
		dev_err(dev, "Got wrong frequency, Request %lu, Current %lu\n",
			target_rate, dmcfreq->rate);
		regulator_set_voltage(dmcfreq->vdd_center, dmcfreq->volt,
				      dmcfreq->volt);
		जाओ out;
	पूर्ण अन्यथा अगर (old_clk_rate > target_rate)
		err = regulator_set_voltage(dmcfreq->vdd_center, target_volt,
					    target_volt);
	अगर (err)
		dev_err(dev, "Cannot set voltage %lu uV\n", target_volt);

	dmcfreq->rate = target_rate;
	dmcfreq->volt = target_volt;

out:
	mutex_unlock(&dmcfreq->lock);
	वापस err;
पूर्ण

अटल पूर्णांक rk3399_dmcfreq_get_dev_status(काष्ठा device *dev,
					 काष्ठा devfreq_dev_status *stat)
अणु
	काष्ठा rk3399_dmcfreq *dmcfreq = dev_get_drvdata(dev);
	काष्ठा devfreq_event_data edata;
	पूर्णांक ret = 0;

	ret = devfreq_event_get_event(dmcfreq->edev, &edata);
	अगर (ret < 0)
		वापस ret;

	stat->current_frequency = dmcfreq->rate;
	stat->busy_समय = edata.load_count;
	stat->total_समय = edata.total_count;

	वापस ret;
पूर्ण

अटल पूर्णांक rk3399_dmcfreq_get_cur_freq(काष्ठा device *dev, अचिन्हित दीर्घ *freq)
अणु
	काष्ठा rk3399_dmcfreq *dmcfreq = dev_get_drvdata(dev);

	*freq = dmcfreq->rate;

	वापस 0;
पूर्ण

अटल काष्ठा devfreq_dev_profile rk3399_devfreq_dmc_profile = अणु
	.polling_ms	= 200,
	.target		= rk3399_dmcfreq_target,
	.get_dev_status	= rk3399_dmcfreq_get_dev_status,
	.get_cur_freq	= rk3399_dmcfreq_get_cur_freq,
पूर्ण;

अटल __maybe_unused पूर्णांक rk3399_dmcfreq_suspend(काष्ठा device *dev)
अणु
	काष्ठा rk3399_dmcfreq *dmcfreq = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	ret = devfreq_event_disable_edev(dmcfreq->edev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to disable the devfreq-event devices\n");
		वापस ret;
	पूर्ण

	ret = devfreq_suspend_device(dmcfreq->devfreq);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to suspend the devfreq devices\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक rk3399_dmcfreq_resume(काष्ठा device *dev)
अणु
	काष्ठा rk3399_dmcfreq *dmcfreq = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	ret = devfreq_event_enable_edev(dmcfreq->edev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable the devfreq-event devices\n");
		वापस ret;
	पूर्ण

	ret = devfreq_resume_device(dmcfreq->devfreq);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to resume the devfreq devices\n");
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rk3399_dmcfreq_pm, rk3399_dmcfreq_suspend,
			 rk3399_dmcfreq_resume);

अटल पूर्णांक of_get_ddr_timings(काष्ठा dram_timing *timing,
			      काष्ठा device_node *np)
अणु
	पूर्णांक ret = 0;

	ret = of_property_पढ़ो_u32(np, "rockchip,ddr3_speed_bin",
				   &timing->ddr3_speed_bin);
	ret |= of_property_पढ़ो_u32(np, "rockchip,pd_idle",
				    &timing->pd_idle);
	ret |= of_property_पढ़ो_u32(np, "rockchip,sr_idle",
				    &timing->sr_idle);
	ret |= of_property_पढ़ो_u32(np, "rockchip,sr_mc_gate_idle",
				    &timing->sr_mc_gate_idle);
	ret |= of_property_पढ़ो_u32(np, "rockchip,srpd_lite_idle",
				    &timing->srpd_lite_idle);
	ret |= of_property_पढ़ो_u32(np, "rockchip,standby_idle",
				    &timing->standby_idle);
	ret |= of_property_पढ़ो_u32(np, "rockchip,auto_pd_dis_freq",
				    &timing->स्वतः_pd_dis_freq);
	ret |= of_property_पढ़ो_u32(np, "rockchip,dram_dll_dis_freq",
				    &timing->dram_dll_dis_freq);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_dll_dis_freq",
				    &timing->phy_dll_dis_freq);
	ret |= of_property_पढ़ो_u32(np, "rockchip,ddr3_odt_dis_freq",
				    &timing->ddr3_odt_dis_freq);
	ret |= of_property_पढ़ो_u32(np, "rockchip,ddr3_drv",
				    &timing->ddr3_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,ddr3_odt",
				    &timing->ddr3_odt);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_ddr3_ca_drv",
				    &timing->phy_ddr3_ca_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_ddr3_dq_drv",
				    &timing->phy_ddr3_dq_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_ddr3_odt",
				    &timing->phy_ddr3_odt);
	ret |= of_property_पढ़ो_u32(np, "rockchip,lpddr3_odt_dis_freq",
				    &timing->lpddr3_odt_dis_freq);
	ret |= of_property_पढ़ो_u32(np, "rockchip,lpddr3_drv",
				    &timing->lpddr3_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,lpddr3_odt",
				    &timing->lpddr3_odt);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_lpddr3_ca_drv",
				    &timing->phy_lpddr3_ca_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_lpddr3_dq_drv",
				    &timing->phy_lpddr3_dq_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_lpddr3_odt",
				    &timing->phy_lpddr3_odt);
	ret |= of_property_पढ़ो_u32(np, "rockchip,lpddr4_odt_dis_freq",
				    &timing->lpddr4_odt_dis_freq);
	ret |= of_property_पढ़ो_u32(np, "rockchip,lpddr4_drv",
				    &timing->lpddr4_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,lpddr4_dq_odt",
				    &timing->lpddr4_dq_odt);
	ret |= of_property_पढ़ो_u32(np, "rockchip,lpddr4_ca_odt",
				    &timing->lpddr4_ca_odt);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_lpddr4_ca_drv",
				    &timing->phy_lpddr4_ca_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_lpddr4_ck_cs_drv",
				    &timing->phy_lpddr4_ck_cs_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_lpddr4_dq_drv",
				    &timing->phy_lpddr4_dq_drv);
	ret |= of_property_पढ़ो_u32(np, "rockchip,phy_lpddr4_odt",
				    &timing->phy_lpddr4_odt);

	वापस ret;
पूर्ण

अटल पूर्णांक rk3399_dmcfreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arm_smccc_res res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = pdev->dev.of_node, *node;
	काष्ठा rk3399_dmcfreq *data;
	पूर्णांक ret, index, size;
	uपूर्णांक32_t *timing;
	काष्ठा dev_pm_opp *opp;
	u32 ddr_type;
	u32 val;

	data = devm_kzalloc(dev, माप(काष्ठा rk3399_dmcfreq), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->lock);

	data->vdd_center = devm_regulator_get(dev, "center");
	अगर (IS_ERR(data->vdd_center))
		वापस dev_err_probe(dev, PTR_ERR(data->vdd_center),
				     "Cannot get the regulator \"center\"\n");

	data->dmc_clk = devm_clk_get(dev, "dmc_clk");
	अगर (IS_ERR(data->dmc_clk))
		वापस dev_err_probe(dev, PTR_ERR(data->dmc_clk),
				     "Cannot get the clk dmc_clk\n");

	data->edev = devfreq_event_get_edev_by_phandle(dev, "devfreq-events", 0);
	अगर (IS_ERR(data->edev))
		वापस -EPROBE_DEFER;

	ret = devfreq_event_enable_edev(data->edev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable devfreq-event devices\n");
		वापस ret;
	पूर्ण

	/*
	 * Get dram timing and pass it to arm trust firmware,
	 * the dram driver in arm trust firmware will get these
	 * timing and to करो dram initial.
	 */
	अगर (!of_get_ddr_timings(&data->timing, np)) अणु
		timing = &data->timing.ddr3_speed_bin;
		size = माप(काष्ठा dram_timing) / 4;
		क्रम (index = 0; index < size; index++) अणु
			arm_smccc_smc(ROCKCHIP_SIP_DRAM_FREQ, *timing++, index,
				      ROCKCHIP_SIP_CONFIG_DRAM_SET_PARAM,
				      0, 0, 0, 0, &res);
			अगर (res.a0) अणु
				dev_err(dev, "Failed to set dram param: %ld\n",
					res.a0);
				ret = -EINVAL;
				जाओ err_edev;
			पूर्ण
		पूर्ण
	पूर्ण

	node = of_parse_phandle(np, "rockchip,pmu", 0);
	अगर (!node)
		जाओ no_pmu;

	data->regmap_pmu = syscon_node_to_regmap(node);
	of_node_put(node);
	अगर (IS_ERR(data->regmap_pmu)) अणु
		ret = PTR_ERR(data->regmap_pmu);
		जाओ err_edev;
	पूर्ण

	regmap_पढ़ो(data->regmap_pmu, RK3399_PMUGRF_OS_REG2, &val);
	ddr_type = (val >> RK3399_PMUGRF_DDRTYPE_SHIFT) &
		    RK3399_PMUGRF_DDRTYPE_MASK;

	चयन (ddr_type) अणु
	हाल RK3399_PMUGRF_DDRTYPE_DDR3:
		data->odt_dis_freq = data->timing.ddr3_odt_dis_freq;
		अवरोध;
	हाल RK3399_PMUGRF_DDRTYPE_LPDDR3:
		data->odt_dis_freq = data->timing.lpddr3_odt_dis_freq;
		अवरोध;
	हाल RK3399_PMUGRF_DDRTYPE_LPDDR4:
		data->odt_dis_freq = data->timing.lpddr4_odt_dis_freq;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err_edev;
	पूर्ण

no_pmu:
	arm_smccc_smc(ROCKCHIP_SIP_DRAM_FREQ, 0, 0,
		      ROCKCHIP_SIP_CONFIG_DRAM_INIT,
		      0, 0, 0, 0, &res);

	/*
	 * In TF-A there is a platक्रमm SIP call to set the PD (घातer-करोwn)
	 * timings and to enable or disable the ODT (on-die termination).
	 * This call needs three arguments as follows:
	 *
	 * arg0:
	 *     bit[0-7]   : sr_idle
	 *     bit[8-15]  : sr_mc_gate_idle
	 *     bit[16-31] : standby idle
	 * arg1:
	 *     bit[0-11]  : pd_idle
	 *     bit[16-27] : srpd_lite_idle
	 * arg2:
	 *     bit[0]     : odt enable
	 */
	data->odt_pd_arg0 = (data->timing.sr_idle & 0xff) |
			    ((data->timing.sr_mc_gate_idle & 0xff) << 8) |
			    ((data->timing.standby_idle & 0xffff) << 16);
	data->odt_pd_arg1 = (data->timing.pd_idle & 0xfff) |
			    ((data->timing.srpd_lite_idle & 0xfff) << 16);

	/*
	 * We add a devfreq driver to our parent since it has a device tree node
	 * with operating poपूर्णांकs.
	 */
	अगर (dev_pm_opp_of_add_table(dev)) अणु
		dev_err(dev, "Invalid operating-points in device tree.\n");
		ret = -EINVAL;
		जाओ err_edev;
	पूर्ण

	of_property_पढ़ो_u32(np, "upthreshold",
			     &data->ondemand_data.upthreshold);
	of_property_पढ़ो_u32(np, "downdifferential",
			     &data->ondemand_data.करोwndअगरferential);

	data->rate = clk_get_rate(data->dmc_clk);

	opp = devfreq_recommended_opp(dev, &data->rate, 0);
	अगर (IS_ERR(opp)) अणु
		ret = PTR_ERR(opp);
		जाओ err_मुक्त_opp;
	पूर्ण

	data->rate = dev_pm_opp_get_freq(opp);
	data->volt = dev_pm_opp_get_voltage(opp);
	dev_pm_opp_put(opp);

	rk3399_devfreq_dmc_profile.initial_freq = data->rate;

	data->devfreq = devm_devfreq_add_device(dev,
					   &rk3399_devfreq_dmc_profile,
					   DEVFREQ_GOV_SIMPLE_ONDEMAND,
					   &data->ondemand_data);
	अगर (IS_ERR(data->devfreq)) अणु
		ret = PTR_ERR(data->devfreq);
		जाओ err_मुक्त_opp;
	पूर्ण

	devm_devfreq_रेजिस्टर_opp_notअगरier(dev, data->devfreq);

	data->dev = dev;
	platक्रमm_set_drvdata(pdev, data);

	वापस 0;

err_मुक्त_opp:
	dev_pm_opp_of_हटाओ_table(&pdev->dev);
err_edev:
	devfreq_event_disable_edev(data->edev);

	वापस ret;
पूर्ण

अटल पूर्णांक rk3399_dmcfreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk3399_dmcfreq *dmcfreq = dev_get_drvdata(&pdev->dev);

	/*
	 * Beक्रमe हटाओ the opp table we need to unरेजिस्टर the opp notअगरier.
	 */
	devm_devfreq_unरेजिस्टर_opp_notअगरier(dmcfreq->dev, dmcfreq->devfreq);
	dev_pm_opp_of_हटाओ_table(dmcfreq->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rk3399dmc_devfreq_of_match[] = अणु
	अणु .compatible = "rockchip,rk3399-dmc" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rk3399dmc_devfreq_of_match);

अटल काष्ठा platक्रमm_driver rk3399_dmcfreq_driver = अणु
	.probe	= rk3399_dmcfreq_probe,
	.हटाओ = rk3399_dmcfreq_हटाओ,
	.driver = अणु
		.name	= "rk3399-dmc-freq",
		.pm	= &rk3399_dmcfreq_pm,
		.of_match_table = rk3399dmc_devfreq_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rk3399_dmcfreq_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Lin Huang <hl@rock-chips.com>");
MODULE_DESCRIPTION("RK3399 dmcfreq driver with devfreq framework");
