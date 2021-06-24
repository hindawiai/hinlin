<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm-dp] %s: " fmt, __func__

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_opp.h>
#समावेश "dp_power.h"
#समावेश "msm_drv.h"

काष्ठा dp_घातer_निजी अणु
	काष्ठा dp_parser *parser;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device *dev;
	काष्ठा clk *link_clk_src;
	काष्ठा clk *pixel_provider;
	काष्ठा clk *link_provider;
	काष्ठा regulator_bulk_data supplies[DP_DEV_REGULATOR_MAX];

	काष्ठा dp_घातer dp_घातer;
पूर्ण;

अटल व्योम dp_घातer_regulator_disable(काष्ठा dp_घातer_निजी *घातer)
अणु
	काष्ठा regulator_bulk_data *s = घातer->supplies;
	स्थिर काष्ठा dp_reg_entry *regs = घातer->parser->regulator_cfg->regs;
	पूर्णांक num = घातer->parser->regulator_cfg->num;
	पूर्णांक i;

	DBG("");
	क्रम (i = num - 1; i >= 0; i--)
		अगर (regs[i].disable_load >= 0)
			regulator_set_load(s[i].consumer,
					   regs[i].disable_load);

	regulator_bulk_disable(num, s);
पूर्ण

अटल पूर्णांक dp_घातer_regulator_enable(काष्ठा dp_घातer_निजी *घातer)
अणु
	काष्ठा regulator_bulk_data *s = घातer->supplies;
	स्थिर काष्ठा dp_reg_entry *regs = घातer->parser->regulator_cfg->regs;
	पूर्णांक num = घातer->parser->regulator_cfg->num;
	पूर्णांक ret, i;

	DBG("");
	क्रम (i = 0; i < num; i++) अणु
		अगर (regs[i].enable_load >= 0) अणु
			ret = regulator_set_load(s[i].consumer,
						 regs[i].enable_load);
			अगर (ret < 0) अणु
				pr_err("regulator %d set op mode failed, %d\n",
					i, ret);
				जाओ fail;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = regulator_bulk_enable(num, s);
	अगर (ret < 0) अणु
		pr_err("regulator enable failed, %d\n", ret);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	क्रम (i--; i >= 0; i--)
		regulator_set_load(s[i].consumer, regs[i].disable_load);
	वापस ret;
पूर्ण

अटल पूर्णांक dp_घातer_regulator_init(काष्ठा dp_घातer_निजी *घातer)
अणु
	काष्ठा regulator_bulk_data *s = घातer->supplies;
	स्थिर काष्ठा dp_reg_entry *regs = घातer->parser->regulator_cfg->regs;
	काष्ठा platक्रमm_device *pdev = घातer->pdev;
	पूर्णांक num = घातer->parser->regulator_cfg->num;
	पूर्णांक i, ret;

	क्रम (i = 0; i < num; i++)
		s[i].supply = regs[i].name;

	ret = devm_regulator_bulk_get(&pdev->dev, num, s);
	अगर (ret < 0) अणु
		pr_err("%s: failed to init regulator, ret=%d\n",
						__func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dp_घातer_clk_init(काष्ठा dp_घातer_निजी *घातer)
अणु
	पूर्णांक rc = 0;
	काष्ठा dss_module_घातer *core, *ctrl, *stream;
	काष्ठा device *dev = &घातer->pdev->dev;

	core = &घातer->parser->mp[DP_CORE_PM];
	ctrl = &घातer->parser->mp[DP_CTRL_PM];
	stream = &घातer->parser->mp[DP_STREAM_PM];

	rc = msm_dss_get_clk(dev, core->clk_config, core->num_clk);
	अगर (rc) अणु
		DRM_ERROR("failed to get %s clk. err=%d\n",
			dp_parser_pm_name(DP_CORE_PM), rc);
		वापस rc;
	पूर्ण

	rc = msm_dss_get_clk(dev, ctrl->clk_config, ctrl->num_clk);
	अगर (rc) अणु
		DRM_ERROR("failed to get %s clk. err=%d\n",
			dp_parser_pm_name(DP_CTRL_PM), rc);
		msm_dss_put_clk(core->clk_config, core->num_clk);
		वापस -ENODEV;
	पूर्ण

	rc = msm_dss_get_clk(dev, stream->clk_config, stream->num_clk);
	अगर (rc) अणु
		DRM_ERROR("failed to get %s clk. err=%d\n",
			dp_parser_pm_name(DP_CTRL_PM), rc);
		msm_dss_put_clk(core->clk_config, core->num_clk);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dp_घातer_clk_deinit(काष्ठा dp_घातer_निजी *घातer)
अणु
	काष्ठा dss_module_घातer *core, *ctrl, *stream;

	core = &घातer->parser->mp[DP_CORE_PM];
	ctrl = &घातer->parser->mp[DP_CTRL_PM];
	stream = &घातer->parser->mp[DP_STREAM_PM];

	अगर (!core || !ctrl || !stream) अणु
		DRM_ERROR("invalid power_data\n");
		वापस -EINVAL;
	पूर्ण

	msm_dss_put_clk(ctrl->clk_config, ctrl->num_clk);
	msm_dss_put_clk(core->clk_config, core->num_clk);
	msm_dss_put_clk(stream->clk_config, stream->num_clk);
	वापस 0;
पूर्ण

अटल पूर्णांक dp_घातer_clk_set_link_rate(काष्ठा dp_घातer_निजी *घातer,
			काष्ठा dss_clk *clk_arry, पूर्णांक num_clk, पूर्णांक enable)
अणु
	u32 rate;
	पूर्णांक i, rc = 0;

	क्रम (i = 0; i < num_clk; i++) अणु
		अगर (clk_arry[i].clk) अणु
			अगर (clk_arry[i].type == DSS_CLK_PCLK) अणु
				अगर (enable)
					rate = clk_arry[i].rate;
				अन्यथा
					rate = 0;

				rc = dev_pm_opp_set_rate(घातer->dev, rate);
				अगर (rc)
					अवरोध;
			पूर्ण

		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक dp_घातer_clk_set_rate(काष्ठा dp_घातer_निजी *घातer,
		क्रमागत dp_pm_type module, bool enable)
अणु
	पूर्णांक rc = 0;
	काष्ठा dss_module_घातer *mp = &घातer->parser->mp[module];

	अगर (module == DP_CTRL_PM) अणु
		rc = dp_घातer_clk_set_link_rate(घातer, mp->clk_config, mp->num_clk, enable);
		अगर (rc) अणु
			DRM_ERROR("failed to set link clks rate\n");
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु

		अगर (enable) अणु
			rc = msm_dss_clk_set_rate(mp->clk_config, mp->num_clk);
			अगर (rc) अणु
				DRM_ERROR("failed to set clks rate\n");
				वापस rc;
			पूर्ण
		पूर्ण
	पूर्ण

	rc = msm_dss_enable_clk(mp->clk_config, mp->num_clk, enable);
	अगर (rc) अणु
		DRM_ERROR("failed to %d clks, err: %d\n", enable, rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dp_घातer_clk_status(काष्ठा dp_घातer *dp_घातer, क्रमागत dp_pm_type pm_type)
अणु
	अगर (pm_type == DP_CORE_PM)
		वापस dp_घातer->core_clks_on;

	अगर (pm_type == DP_CTRL_PM)
		वापस dp_घातer->link_clks_on;

	अगर (pm_type == DP_STREAM_PM)
		वापस dp_घातer->stream_clks_on;

	वापस 0;
पूर्ण

पूर्णांक dp_घातer_clk_enable(काष्ठा dp_घातer *dp_घातer,
		क्रमागत dp_pm_type pm_type, bool enable)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_घातer_निजी *घातer;

	घातer = container_of(dp_घातer, काष्ठा dp_घातer_निजी, dp_घातer);

	अगर (pm_type != DP_CORE_PM && pm_type != DP_CTRL_PM &&
			pm_type != DP_STREAM_PM) अणु
		DRM_ERROR("unsupported power module: %s\n",
				dp_parser_pm_name(pm_type));
		वापस -EINVAL;
	पूर्ण

	अगर (enable) अणु
		अगर (pm_type == DP_CORE_PM && dp_घातer->core_clks_on) अणु
			DRM_DEBUG_DP("core clks already enabled\n");
			वापस 0;
		पूर्ण

		अगर (pm_type == DP_CTRL_PM && dp_घातer->link_clks_on) अणु
			DRM_DEBUG_DP("links clks already enabled\n");
			वापस 0;
		पूर्ण

		अगर (pm_type == DP_STREAM_PM && dp_घातer->stream_clks_on) अणु
			DRM_DEBUG_DP("pixel clks already enabled\n");
			वापस 0;
		पूर्ण

		अगर ((pm_type == DP_CTRL_PM) && (!dp_घातer->core_clks_on)) अणु
			DRM_DEBUG_DP("Enable core clks before link clks\n");

			rc = dp_घातer_clk_set_rate(घातer, DP_CORE_PM, enable);
			अगर (rc) अणु
				DRM_ERROR("fail to enable clks: %s. err=%d\n",
					dp_parser_pm_name(DP_CORE_PM), rc);
				वापस rc;
			पूर्ण
			dp_घातer->core_clks_on = true;
		पूर्ण
	पूर्ण

	rc = dp_घातer_clk_set_rate(घातer, pm_type, enable);
	अगर (rc) अणु
		DRM_ERROR("failed to '%s' clks for: %s. err=%d\n",
			enable ? "enable" : "disable",
			dp_parser_pm_name(pm_type), rc);
		वापस rc;
	पूर्ण

	अगर (pm_type == DP_CORE_PM)
		dp_घातer->core_clks_on = enable;
	अन्यथा अगर (pm_type == DP_STREAM_PM)
		dp_घातer->stream_clks_on = enable;
	अन्यथा
		dp_घातer->link_clks_on = enable;

	DRM_DEBUG_DP("%s clocks for %s\n",
			enable ? "enable" : "disable",
			dp_parser_pm_name(pm_type));
	DRM_DEBUG_DP("strem_clks:%s link_clks:%s core_clks:%s\n",
		dp_घातer->stream_clks_on ? "on" : "off",
		dp_घातer->link_clks_on ? "on" : "off",
		dp_घातer->core_clks_on ? "on" : "off");

	वापस 0;
पूर्ण

पूर्णांक dp_घातer_client_init(काष्ठा dp_घातer *dp_घातer)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_घातer_निजी *घातer;

	अगर (!dp_घातer) अणु
		DRM_ERROR("invalid power data\n");
		वापस -EINVAL;
	पूर्ण

	घातer = container_of(dp_घातer, काष्ठा dp_घातer_निजी, dp_घातer);

	pm_runसमय_enable(&घातer->pdev->dev);

	rc = dp_घातer_regulator_init(घातer);
	अगर (rc) अणु
		DRM_ERROR("failed to init regulators %d\n", rc);
		जाओ error;
	पूर्ण

	rc = dp_घातer_clk_init(घातer);
	अगर (rc) अणु
		DRM_ERROR("failed to init clocks %d\n", rc);
		जाओ error;
	पूर्ण
	वापस 0;

error:
	pm_runसमय_disable(&घातer->pdev->dev);
	वापस rc;
पूर्ण

व्योम dp_घातer_client_deinit(काष्ठा dp_घातer *dp_घातer)
अणु
	काष्ठा dp_घातer_निजी *घातer;

	अगर (!dp_घातer) अणु
		DRM_ERROR("invalid power data\n");
		वापस;
	पूर्ण

	घातer = container_of(dp_घातer, काष्ठा dp_घातer_निजी, dp_घातer);

	dp_घातer_clk_deinit(घातer);
	pm_runसमय_disable(&घातer->pdev->dev);

पूर्ण

पूर्णांक dp_घातer_init(काष्ठा dp_घातer *dp_घातer, bool flip)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_घातer_निजी *घातer = शून्य;

	अगर (!dp_घातer) अणु
		DRM_ERROR("invalid power data\n");
		वापस -EINVAL;
	पूर्ण

	घातer = container_of(dp_घातer, काष्ठा dp_घातer_निजी, dp_घातer);

	pm_runसमय_get_sync(&घातer->pdev->dev);
	rc = dp_घातer_regulator_enable(घातer);
	अगर (rc) अणु
		DRM_ERROR("failed to enable regulators, %d\n", rc);
		जाओ निकास;
	पूर्ण

	rc = dp_घातer_clk_enable(dp_घातer, DP_CORE_PM, true);
	अगर (rc) अणु
		DRM_ERROR("failed to enable DP core clocks, %d\n", rc);
		जाओ err_clk;
	पूर्ण

	वापस 0;

err_clk:
	dp_घातer_regulator_disable(घातer);
निकास:
	pm_runसमय_put_sync(&घातer->pdev->dev);
	वापस rc;
पूर्ण

पूर्णांक dp_घातer_deinit(काष्ठा dp_घातer *dp_घातer)
अणु
	काष्ठा dp_घातer_निजी *घातer;

	घातer = container_of(dp_घातer, काष्ठा dp_घातer_निजी, dp_घातer);

	dp_घातer_clk_enable(dp_घातer, DP_CORE_PM, false);
	dp_घातer_regulator_disable(घातer);
	pm_runसमय_put_sync(&घातer->pdev->dev);
	वापस 0;
पूर्ण

काष्ठा dp_घातer *dp_घातer_get(काष्ठा device *dev, काष्ठा dp_parser *parser)
अणु
	काष्ठा dp_घातer_निजी *घातer;
	काष्ठा dp_घातer *dp_घातer;

	अगर (!parser) अणु
		DRM_ERROR("invalid input\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	घातer = devm_kzalloc(&parser->pdev->dev, माप(*घातer), GFP_KERNEL);
	अगर (!घातer)
		वापस ERR_PTR(-ENOMEM);

	घातer->parser = parser;
	घातer->pdev = parser->pdev;
	घातer->dev = dev;

	dp_घातer = &घातer->dp_घातer;

	वापस dp_घातer;
पूर्ण
