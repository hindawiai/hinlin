<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>

#समावेश <sound/hdmi-codec.h>
#समावेश "hdmi.h"

व्योम msm_hdmi_set_mode(काष्ठा hdmi *hdmi, bool घातer_on)
अणु
	uपूर्णांक32_t ctrl = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hdmi->reg_lock, flags);
	अगर (घातer_on) अणु
		ctrl |= HDMI_CTRL_ENABLE;
		अगर (!hdmi->hdmi_mode) अणु
			ctrl |= HDMI_CTRL_HDMI;
			hdmi_ग_लिखो(hdmi, REG_HDMI_CTRL, ctrl);
			ctrl &= ~HDMI_CTRL_HDMI;
		पूर्ण अन्यथा अणु
			ctrl |= HDMI_CTRL_HDMI;
		पूर्ण
	पूर्ण अन्यथा अणु
		ctrl = HDMI_CTRL_HDMI;
	पूर्ण

	hdmi_ग_लिखो(hdmi, REG_HDMI_CTRL, ctrl);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);
	DBG("HDMI Core: %s, HDMI_CTRL=0x%08x",
			घातer_on ? "Enable" : "Disable", ctrl);
पूर्ण

अटल irqवापस_t msm_hdmi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hdmi *hdmi = dev_id;

	/* Process HPD: */
	msm_hdmi_connector_irq(hdmi->connector);

	/* Process DDC: */
	msm_hdmi_i2c_irq(hdmi->i2c);

	/* Process HDCP: */
	अगर (hdmi->hdcp_ctrl)
		msm_hdmi_hdcp_irq(hdmi->hdcp_ctrl);

	/* TODO audio.. */

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम msm_hdmi_destroy(काष्ठा hdmi *hdmi)
अणु
	/*
	 * at this poपूर्णांक, hpd has been disabled,
	 * after flush workq, it's safe to deinit hdcp
	 */
	अगर (hdmi->workq) अणु
		flush_workqueue(hdmi->workq);
		destroy_workqueue(hdmi->workq);
	पूर्ण
	msm_hdmi_hdcp_destroy(hdmi);

	अगर (hdmi->phy_dev) अणु
		put_device(hdmi->phy_dev);
		hdmi->phy = शून्य;
		hdmi->phy_dev = शून्य;
	पूर्ण

	अगर (hdmi->i2c)
		msm_hdmi_i2c_destroy(hdmi->i2c);

	platक्रमm_set_drvdata(hdmi->pdev, शून्य);
पूर्ण

अटल पूर्णांक msm_hdmi_get_phy(काष्ठा hdmi *hdmi)
अणु
	काष्ठा platक्रमm_device *pdev = hdmi->pdev;
	काष्ठा platक्रमm_device *phy_pdev;
	काष्ठा device_node *phy_node;

	phy_node = of_parse_phandle(pdev->dev.of_node, "phys", 0);
	अगर (!phy_node) अणु
		DRM_DEV_ERROR(&pdev->dev, "cannot find phy device\n");
		वापस -ENXIO;
	पूर्ण

	phy_pdev = of_find_device_by_node(phy_node);
	अगर (phy_pdev)
		hdmi->phy = platक्रमm_get_drvdata(phy_pdev);

	of_node_put(phy_node);

	अगर (!phy_pdev || !hdmi->phy) अणु
		DRM_DEV_ERROR(&pdev->dev, "phy driver is not ready\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	hdmi->phy_dev = get_device(&phy_pdev->dev);

	वापस 0;
पूर्ण

/* स्थिरruct hdmi at bind/probe समय, grab all the resources.  If
 * we are to EPROBE_DEFER we want to करो it here, rather than later
 * at modeset_init() समय
 */
अटल काष्ठा hdmi *msm_hdmi_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hdmi_platक्रमm_config *config = pdev->dev.platक्रमm_data;
	काष्ठा hdmi *hdmi = शून्य;
	काष्ठा resource *res;
	पूर्णांक i, ret;

	hdmi = devm_kzalloc(&pdev->dev, माप(*hdmi), GFP_KERNEL);
	अगर (!hdmi) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	hdmi->pdev = pdev;
	hdmi->config = config;
	spin_lock_init(&hdmi->reg_lock);

	hdmi->mmio = msm_ioremap(pdev, config->mmio_name, "HDMI");
	अगर (IS_ERR(hdmi->mmio)) अणु
		ret = PTR_ERR(hdmi->mmio);
		जाओ fail;
	पूर्ण

	/* HDCP needs physical address of hdmi रेजिस्टर */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
		config->mmio_name);
	hdmi->mmio_phy_addr = res->start;

	hdmi->qfprom_mmio = msm_ioremap(pdev,
		config->qfprom_mmio_name, "HDMI_QFPROM");
	अगर (IS_ERR(hdmi->qfprom_mmio)) अणु
		DRM_DEV_INFO(&pdev->dev, "can't find qfprom resource\n");
		hdmi->qfprom_mmio = शून्य;
	पूर्ण

	hdmi->hpd_regs = devm_kसुस्मृति(&pdev->dev,
				      config->hpd_reg_cnt,
				      माप(hdmi->hpd_regs[0]),
				      GFP_KERNEL);
	अगर (!hdmi->hpd_regs) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	क्रम (i = 0; i < config->hpd_reg_cnt; i++) अणु
		काष्ठा regulator *reg;

		reg = devm_regulator_get(&pdev->dev,
				config->hpd_reg_names[i]);
		अगर (IS_ERR(reg)) अणु
			ret = PTR_ERR(reg);
			DRM_DEV_ERROR(&pdev->dev, "failed to get hpd regulator: %s (%d)\n",
					config->hpd_reg_names[i], ret);
			जाओ fail;
		पूर्ण

		hdmi->hpd_regs[i] = reg;
	पूर्ण

	hdmi->pwr_regs = devm_kसुस्मृति(&pdev->dev,
				      config->pwr_reg_cnt,
				      माप(hdmi->pwr_regs[0]),
				      GFP_KERNEL);
	अगर (!hdmi->pwr_regs) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	क्रम (i = 0; i < config->pwr_reg_cnt; i++) अणु
		काष्ठा regulator *reg;

		reg = devm_regulator_get(&pdev->dev,
				config->pwr_reg_names[i]);
		अगर (IS_ERR(reg)) अणु
			ret = PTR_ERR(reg);
			DRM_DEV_ERROR(&pdev->dev, "failed to get pwr regulator: %s (%d)\n",
					config->pwr_reg_names[i], ret);
			जाओ fail;
		पूर्ण

		hdmi->pwr_regs[i] = reg;
	पूर्ण

	hdmi->hpd_clks = devm_kसुस्मृति(&pdev->dev,
				      config->hpd_clk_cnt,
				      माप(hdmi->hpd_clks[0]),
				      GFP_KERNEL);
	अगर (!hdmi->hpd_clks) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	क्रम (i = 0; i < config->hpd_clk_cnt; i++) अणु
		काष्ठा clk *clk;

		clk = msm_clk_get(pdev, config->hpd_clk_names[i]);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			DRM_DEV_ERROR(&pdev->dev, "failed to get hpd clk: %s (%d)\n",
					config->hpd_clk_names[i], ret);
			जाओ fail;
		पूर्ण

		hdmi->hpd_clks[i] = clk;
	पूर्ण

	hdmi->pwr_clks = devm_kसुस्मृति(&pdev->dev,
				      config->pwr_clk_cnt,
				      माप(hdmi->pwr_clks[0]),
				      GFP_KERNEL);
	अगर (!hdmi->pwr_clks) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	क्रम (i = 0; i < config->pwr_clk_cnt; i++) अणु
		काष्ठा clk *clk;

		clk = msm_clk_get(pdev, config->pwr_clk_names[i]);
		अगर (IS_ERR(clk)) अणु
			ret = PTR_ERR(clk);
			DRM_DEV_ERROR(&pdev->dev, "failed to get pwr clk: %s (%d)\n",
					config->pwr_clk_names[i], ret);
			जाओ fail;
		पूर्ण

		hdmi->pwr_clks[i] = clk;
	पूर्ण

	pm_runसमय_enable(&pdev->dev);

	hdmi->workq = alloc_ordered_workqueue("msm_hdmi", 0);

	hdmi->i2c = msm_hdmi_i2c_init(hdmi);
	अगर (IS_ERR(hdmi->i2c)) अणु
		ret = PTR_ERR(hdmi->i2c);
		DRM_DEV_ERROR(&pdev->dev, "failed to get i2c: %d\n", ret);
		hdmi->i2c = शून्य;
		जाओ fail;
	पूर्ण

	ret = msm_hdmi_get_phy(hdmi);
	अगर (ret) अणु
		DRM_DEV_ERROR(&pdev->dev, "failed to get phy\n");
		जाओ fail;
	पूर्ण

	hdmi->hdcp_ctrl = msm_hdmi_hdcp_init(hdmi);
	अगर (IS_ERR(hdmi->hdcp_ctrl)) अणु
		dev_warn(&pdev->dev, "failed to init hdcp: disabled\n");
		hdmi->hdcp_ctrl = शून्य;
	पूर्ण

	वापस hdmi;

fail:
	अगर (hdmi)
		msm_hdmi_destroy(hdmi);

	वापस ERR_PTR(ret);
पूर्ण

/* Second part of initialization, the drm/kms level modeset_init,
 * स्थिरructs/initializes mode objects, etc, is called from master
 * driver (not hdmi sub-device's probe/bind!)
 *
 * Any resource (regulator/clk/etc) which could be missing at boot
 * should be handled in msm_hdmi_init() so that failure happens from
 * hdmi sub-device's probe.
 */
पूर्णांक msm_hdmi_modeset_init(काष्ठा hdmi *hdmi,
		काष्ठा drm_device *dev, काष्ठा drm_encoder *encoder)
अणु
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	काष्ठा platक्रमm_device *pdev = hdmi->pdev;
	पूर्णांक ret;

	hdmi->dev = dev;
	hdmi->encoder = encoder;

	hdmi_audio_infoframe_init(&hdmi->audio.infoframe);

	hdmi->bridge = msm_hdmi_bridge_init(hdmi);
	अगर (IS_ERR(hdmi->bridge)) अणु
		ret = PTR_ERR(hdmi->bridge);
		DRM_DEV_ERROR(dev->dev, "failed to create HDMI bridge: %d\n", ret);
		hdmi->bridge = शून्य;
		जाओ fail;
	पूर्ण

	hdmi->connector = msm_hdmi_connector_init(hdmi);
	अगर (IS_ERR(hdmi->connector)) अणु
		ret = PTR_ERR(hdmi->connector);
		DRM_DEV_ERROR(dev->dev, "failed to create HDMI connector: %d\n", ret);
		hdmi->connector = शून्य;
		जाओ fail;
	पूर्ण

	hdmi->irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	अगर (hdmi->irq < 0) अणु
		ret = hdmi->irq;
		DRM_DEV_ERROR(dev->dev, "failed to get irq: %d\n", ret);
		जाओ fail;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, hdmi->irq,
			msm_hdmi_irq, IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
			"hdmi_isr", hdmi);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev->dev, "failed to request IRQ%u: %d\n",
				hdmi->irq, ret);
		जाओ fail;
	पूर्ण

	ret = msm_hdmi_hpd_enable(hdmi->connector);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(&hdmi->pdev->dev, "failed to enable HPD: %d\n", ret);
		जाओ fail;
	पूर्ण

	priv->bridges[priv->num_bridges++]       = hdmi->bridge;
	priv->connectors[priv->num_connectors++] = hdmi->connector;

	platक्रमm_set_drvdata(pdev, hdmi);

	वापस 0;

fail:
	/* bridge is normally destroyed by drm: */
	अगर (hdmi->bridge) अणु
		msm_hdmi_bridge_destroy(hdmi->bridge);
		hdmi->bridge = शून्य;
	पूर्ण
	अगर (hdmi->connector) अणु
		hdmi->connector->funcs->destroy(hdmi->connector);
		hdmi->connector = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * The hdmi device:
 */

#घोषणा HDMI_CFG(item, entry) \
	.item ## _names = item ##_names_ ## entry, \
	.item ## _cnt   = ARRAY_SIZE(item ## _names_ ## entry)

अटल स्थिर अक्षर *pwr_reg_names_none[] = अणुपूर्ण;
अटल स्थिर अक्षर *hpd_reg_names_none[] = अणुपूर्ण;

अटल काष्ठा hdmi_platक्रमm_config hdmi_tx_8660_config;

अटल स्थिर अक्षर *hpd_reg_names_8960[] = अणु"core-vdda", "hdmi-mux"पूर्ण;
अटल स्थिर अक्षर *hpd_clk_names_8960[] = अणु"core", "master_iface", "slave_iface"पूर्ण;

अटल काष्ठा hdmi_platक्रमm_config hdmi_tx_8960_config = अणु
		HDMI_CFG(hpd_reg, 8960),
		HDMI_CFG(hpd_clk, 8960),
पूर्ण;

अटल स्थिर अक्षर *pwr_reg_names_8x74[] = अणु"core-vdda", "core-vcc"पूर्ण;
अटल स्थिर अक्षर *hpd_reg_names_8x74[] = अणु"hpd-gdsc", "hpd-5v"पूर्ण;
अटल स्थिर अक्षर *pwr_clk_names_8x74[] = अणु"extp", "alt_iface"पूर्ण;
अटल स्थिर अक्षर *hpd_clk_names_8x74[] = अणु"iface", "core", "mdp_core"पूर्ण;
अटल अचिन्हित दीर्घ hpd_clk_freq_8x74[] = अणु0, 19200000, 0पूर्ण;

अटल काष्ठा hdmi_platक्रमm_config hdmi_tx_8974_config = अणु
		HDMI_CFG(pwr_reg, 8x74),
		HDMI_CFG(hpd_reg, 8x74),
		HDMI_CFG(pwr_clk, 8x74),
		HDMI_CFG(hpd_clk, 8x74),
		.hpd_freq      = hpd_clk_freq_8x74,
पूर्ण;

अटल स्थिर अक्षर *hpd_reg_names_8084[] = अणु"hpd-gdsc", "hpd-5v", "hpd-5v-en"पूर्ण;

अटल काष्ठा hdmi_platक्रमm_config hdmi_tx_8084_config = अणु
		HDMI_CFG(pwr_reg, 8x74),
		HDMI_CFG(hpd_reg, 8084),
		HDMI_CFG(pwr_clk, 8x74),
		HDMI_CFG(hpd_clk, 8x74),
		.hpd_freq      = hpd_clk_freq_8x74,
पूर्ण;

अटल काष्ठा hdmi_platक्रमm_config hdmi_tx_8994_config = अणु
		HDMI_CFG(pwr_reg, 8x74),
		HDMI_CFG(hpd_reg, none),
		HDMI_CFG(pwr_clk, 8x74),
		HDMI_CFG(hpd_clk, 8x74),
		.hpd_freq      = hpd_clk_freq_8x74,
पूर्ण;

अटल काष्ठा hdmi_platक्रमm_config hdmi_tx_8996_config = अणु
		HDMI_CFG(pwr_reg, none),
		HDMI_CFG(hpd_reg, none),
		HDMI_CFG(pwr_clk, 8x74),
		HDMI_CFG(hpd_clk, 8x74),
		.hpd_freq      = hpd_clk_freq_8x74,
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	स्थिर bool output;
	स्थिर पूर्णांक value;
	स्थिर अक्षर *label;
पूर्ण msm_hdmi_gpio_pdata[] = अणु
	अणु "qcom,hdmi-tx-ddc-clk", true, 1, "HDMI_DDC_CLK" पूर्ण,
	अणु "qcom,hdmi-tx-ddc-data", true, 1, "HDMI_DDC_DATA" पूर्ण,
	अणु "qcom,hdmi-tx-hpd", false, 1, "HDMI_HPD" पूर्ण,
	अणु "qcom,hdmi-tx-mux-en", true, 1, "HDMI_MUX_EN" पूर्ण,
	अणु "qcom,hdmi-tx-mux-sel", true, 0, "HDMI_MUX_SEL" पूर्ण,
	अणु "qcom,hdmi-tx-mux-lpm", true, 1, "HDMI_MUX_LPM" पूर्ण,
पूर्ण;

/*
 * HDMI audio codec callbacks
 */
अटल पूर्णांक msm_hdmi_audio_hw_params(काष्ठा device *dev, व्योम *data,
				    काष्ठा hdmi_codec_daअगरmt *daअगरmt,
				    काष्ठा hdmi_codec_params *params)
अणु
	काष्ठा hdmi *hdmi = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक channel_allocation = 0;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक level_shअगरt  = 0; /* 0dB */
	bool करोwn_mix = false;

	DRM_DEV_DEBUG(dev, "%u Hz, %d bit, %d channels\n", params->sample_rate,
		 params->sample_width, params->cea.channels);

	चयन (params->cea.channels) अणु
	हाल 2:
		/* FR and FL speakers */
		channel_allocation  = 0;
		chan = MSM_HDMI_AUDIO_CHANNEL_2;
		अवरोध;
	हाल 4:
		/* FC, LFE, FR and FL speakers */
		channel_allocation  = 0x3;
		chan = MSM_HDMI_AUDIO_CHANNEL_4;
		अवरोध;
	हाल 6:
		/* RR, RL, FC, LFE, FR and FL speakers */
		channel_allocation  = 0x0B;
		chan = MSM_HDMI_AUDIO_CHANNEL_6;
		अवरोध;
	हाल 8:
		/* FRC, FLC, RR, RL, FC, LFE, FR and FL speakers */
		channel_allocation  = 0x1F;
		chan = MSM_HDMI_AUDIO_CHANNEL_8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params->sample_rate) अणु
	हाल 32000:
		rate = HDMI_SAMPLE_RATE_32KHZ;
		अवरोध;
	हाल 44100:
		rate = HDMI_SAMPLE_RATE_44_1KHZ;
		अवरोध;
	हाल 48000:
		rate = HDMI_SAMPLE_RATE_48KHZ;
		अवरोध;
	हाल 88200:
		rate = HDMI_SAMPLE_RATE_88_2KHZ;
		अवरोध;
	हाल 96000:
		rate = HDMI_SAMPLE_RATE_96KHZ;
		अवरोध;
	हाल 176400:
		rate = HDMI_SAMPLE_RATE_176_4KHZ;
		अवरोध;
	हाल 192000:
		rate = HDMI_SAMPLE_RATE_192KHZ;
		अवरोध;
	शेष:
		DRM_DEV_ERROR(dev, "rate[%d] not supported!\n",
			params->sample_rate);
		वापस -EINVAL;
	पूर्ण

	msm_hdmi_audio_set_sample_rate(hdmi, rate);
	msm_hdmi_audio_info_setup(hdmi, 1, chan, channel_allocation,
			      level_shअगरt, करोwn_mix);

	वापस 0;
पूर्ण

अटल व्योम msm_hdmi_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा hdmi *hdmi = dev_get_drvdata(dev);

	msm_hdmi_audio_info_setup(hdmi, 0, 0, 0, 0, 0);
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops msm_hdmi_audio_codec_ops = अणु
	.hw_params = msm_hdmi_audio_hw_params,
	.audio_shutकरोwn = msm_hdmi_audio_shutकरोwn,
पूर्ण;

अटल काष्ठा hdmi_codec_pdata codec_data = अणु
	.ops = &msm_hdmi_audio_codec_ops,
	.max_i2s_channels = 8,
	.i2s = 1,
पूर्ण;

अटल पूर्णांक msm_hdmi_रेजिस्टर_audio_driver(काष्ठा hdmi *hdmi, काष्ठा device *dev)
अणु
	hdmi->audio_pdev = platक्रमm_device_रेजिस्टर_data(dev,
							 HDMI_CODEC_DRV_NAME,
							 PLATFORM_DEVID_AUTO,
							 &codec_data,
							 माप(codec_data));
	वापस PTR_ERR_OR_ZERO(hdmi->audio_pdev);
पूर्ण

अटल पूर्णांक msm_hdmi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;
	काष्ठा hdmi_platक्रमm_config *hdmi_cfg;
	काष्ठा hdmi *hdmi;
	काष्ठा device_node *of_node = dev->of_node;
	पूर्णांक i, err;

	hdmi_cfg = (काष्ठा hdmi_platक्रमm_config *)
			of_device_get_match_data(dev);
	अगर (!hdmi_cfg) अणु
		DRM_DEV_ERROR(dev, "unknown hdmi_cfg: %pOFn\n", of_node);
		वापस -ENXIO;
	पूर्ण

	hdmi_cfg->mmio_name     = "core_physical";
	hdmi_cfg->qfprom_mmio_name = "qfprom_physical";

	क्रम (i = 0; i < HDMI_MAX_NUM_GPIO; i++) अणु
		स्थिर अक्षर *name = msm_hdmi_gpio_pdata[i].name;
		काष्ठा gpio_desc *gpiod;

		/*
		 * We are fetching the GPIO lines "as is" since the connector
		 * code is enabling and disabling the lines. Until that poपूर्णांक
		 * the घातer-on शेष value will be kept.
		 */
		gpiod = devm_gpiod_get_optional(dev, name, GPIOD_ASIS);
		/* This will catch e.g. -PROBE_DEFER */
		अगर (IS_ERR(gpiod))
			वापस PTR_ERR(gpiod);
		अगर (!gpiod) अणु
			/* Try a second समय, stripping करोwn the name */
			अक्षर name3[32];

			/*
			 * Try again after stripping out the "qcom,hdmi-tx"
			 * prefix. This is मुख्यly to match "hpd-gpios" used
			 * in the upstream bindings.
			 */
			अगर (माला_पूछो(name, "qcom,hdmi-tx-%s", name3))
				gpiod = devm_gpiod_get_optional(dev, name3, GPIOD_ASIS);
			अगर (IS_ERR(gpiod))
				वापस PTR_ERR(gpiod);
			अगर (!gpiod)
				DBG("failed to get gpio: %s", name);
		पूर्ण
		hdmi_cfg->gpios[i].gpiod = gpiod;
		अगर (gpiod)
			gpiod_set_consumer_name(gpiod, msm_hdmi_gpio_pdata[i].label);
		hdmi_cfg->gpios[i].output = msm_hdmi_gpio_pdata[i].output;
		hdmi_cfg->gpios[i].value = msm_hdmi_gpio_pdata[i].value;
	पूर्ण

	dev->platक्रमm_data = hdmi_cfg;

	hdmi = msm_hdmi_init(to_platक्रमm_device(dev));
	अगर (IS_ERR(hdmi))
		वापस PTR_ERR(hdmi);
	priv->hdmi = hdmi;

	err = msm_hdmi_रेजिस्टर_audio_driver(hdmi, dev);
	अगर (err) अणु
		DRM_ERROR("Failed to attach an audio codec %d\n", err);
		hdmi->audio_pdev = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम msm_hdmi_unbind(काष्ठा device *dev, काष्ठा device *master,
		व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा msm_drm_निजी *priv = drm->dev_निजी;
	अगर (priv->hdmi) अणु
		अगर (priv->hdmi->audio_pdev)
			platक्रमm_device_unरेजिस्टर(priv->hdmi->audio_pdev);

		msm_hdmi_destroy(priv->hdmi);
		priv->hdmi = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा component_ops msm_hdmi_ops = अणु
		.bind   = msm_hdmi_bind,
		.unbind = msm_hdmi_unbind,
पूर्ण;

अटल पूर्णांक msm_hdmi_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &msm_hdmi_ops);
पूर्ण

अटल पूर्णांक msm_hdmi_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &msm_hdmi_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id msm_hdmi_dt_match[] = अणु
	अणु .compatible = "qcom,hdmi-tx-8996", .data = &hdmi_tx_8996_config पूर्ण,
	अणु .compatible = "qcom,hdmi-tx-8994", .data = &hdmi_tx_8994_config पूर्ण,
	अणु .compatible = "qcom,hdmi-tx-8084", .data = &hdmi_tx_8084_config पूर्ण,
	अणु .compatible = "qcom,hdmi-tx-8974", .data = &hdmi_tx_8974_config पूर्ण,
	अणु .compatible = "qcom,hdmi-tx-8960", .data = &hdmi_tx_8960_config पूर्ण,
	अणु .compatible = "qcom,hdmi-tx-8660", .data = &hdmi_tx_8660_config पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver msm_hdmi_driver = अणु
	.probe = msm_hdmi_dev_probe,
	.हटाओ = msm_hdmi_dev_हटाओ,
	.driver = अणु
		.name = "hdmi_msm",
		.of_match_table = msm_hdmi_dt_match,
	पूर्ण,
पूर्ण;

व्योम __init msm_hdmi_रेजिस्टर(व्योम)
अणु
	msm_hdmi_phy_driver_रेजिस्टर();
	platक्रमm_driver_रेजिस्टर(&msm_hdmi_driver);
पूर्ण

व्योम __निकास msm_hdmi_unरेजिस्टर(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&msm_hdmi_driver);
	msm_hdmi_phy_driver_unरेजिस्टर();
पूर्ण
