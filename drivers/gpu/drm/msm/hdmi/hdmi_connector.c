<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pinctrl/consumer.h>

#समावेश "msm_kms.h"
#समावेश "hdmi.h"

काष्ठा hdmi_connector अणु
	काष्ठा drm_connector base;
	काष्ठा hdmi *hdmi;
	काष्ठा work_काष्ठा hpd_work;
पूर्ण;
#घोषणा to_hdmi_connector(x) container_of(x, काष्ठा hdmi_connector, base)

अटल व्योम msm_hdmi_phy_reset(काष्ठा hdmi *hdmi)
अणु
	अचिन्हित पूर्णांक val;

	val = hdmi_पढ़ो(hdmi, REG_HDMI_PHY_CTRL);

	अगर (val & HDMI_PHY_CTRL_SW_RESET_LOW) अणु
		/* pull low */
		hdmi_ग_लिखो(hdmi, REG_HDMI_PHY_CTRL,
				val & ~HDMI_PHY_CTRL_SW_RESET);
	पूर्ण अन्यथा अणु
		/* pull high */
		hdmi_ग_लिखो(hdmi, REG_HDMI_PHY_CTRL,
				val | HDMI_PHY_CTRL_SW_RESET);
	पूर्ण

	अगर (val & HDMI_PHY_CTRL_SW_RESET_PLL_LOW) अणु
		/* pull low */
		hdmi_ग_लिखो(hdmi, REG_HDMI_PHY_CTRL,
				val & ~HDMI_PHY_CTRL_SW_RESET_PLL);
	पूर्ण अन्यथा अणु
		/* pull high */
		hdmi_ग_लिखो(hdmi, REG_HDMI_PHY_CTRL,
				val | HDMI_PHY_CTRL_SW_RESET_PLL);
	पूर्ण

	msleep(100);

	अगर (val & HDMI_PHY_CTRL_SW_RESET_LOW) अणु
		/* pull high */
		hdmi_ग_लिखो(hdmi, REG_HDMI_PHY_CTRL,
				val | HDMI_PHY_CTRL_SW_RESET);
	पूर्ण अन्यथा अणु
		/* pull low */
		hdmi_ग_लिखो(hdmi, REG_HDMI_PHY_CTRL,
				val & ~HDMI_PHY_CTRL_SW_RESET);
	पूर्ण

	अगर (val & HDMI_PHY_CTRL_SW_RESET_PLL_LOW) अणु
		/* pull high */
		hdmi_ग_लिखो(hdmi, REG_HDMI_PHY_CTRL,
				val | HDMI_PHY_CTRL_SW_RESET_PLL);
	पूर्ण अन्यथा अणु
		/* pull low */
		hdmi_ग_लिखो(hdmi, REG_HDMI_PHY_CTRL,
				val & ~HDMI_PHY_CTRL_SW_RESET_PLL);
	पूर्ण
पूर्ण

अटल पूर्णांक gpio_config(काष्ठा hdmi *hdmi, bool on)
अणु
	स्थिर काष्ठा hdmi_platक्रमm_config *config = hdmi->config;
	पूर्णांक i;

	अगर (on) अणु
		क्रम (i = 0; i < HDMI_MAX_NUM_GPIO; i++) अणु
			काष्ठा hdmi_gpio_data gpio = config->gpios[i];

			अगर (gpio.gpiod) अणु
				अगर (gpio.output) अणु
					gpiod_direction_output(gpio.gpiod,
							       gpio.value);
				पूर्ण अन्यथा अणु
					gpiod_direction_input(gpio.gpiod);
					gpiod_set_value_cansleep(gpio.gpiod,
								 gpio.value);
				पूर्ण
			पूर्ण
		पूर्ण

		DBG("gpio on");
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < HDMI_MAX_NUM_GPIO; i++) अणु
			काष्ठा hdmi_gpio_data gpio = config->gpios[i];

			अगर (!gpio.gpiod)
				जारी;

			अगर (gpio.output) अणु
				पूर्णांक value = gpio.value ? 0 : 1;

				gpiod_set_value_cansleep(gpio.gpiod, value);
			पूर्ण
		पूर्ण

		DBG("gpio off");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम enable_hpd_घड़ीs(काष्ठा hdmi *hdmi, bool enable)
अणु
	स्थिर काष्ठा hdmi_platक्रमm_config *config = hdmi->config;
	काष्ठा device *dev = &hdmi->pdev->dev;
	पूर्णांक i, ret;

	अगर (enable) अणु
		क्रम (i = 0; i < config->hpd_clk_cnt; i++) अणु
			अगर (config->hpd_freq && config->hpd_freq[i]) अणु
				ret = clk_set_rate(hdmi->hpd_clks[i],
						   config->hpd_freq[i]);
				अगर (ret)
					dev_warn(dev,
						 "failed to set clk %s (%d)\n",
						 config->hpd_clk_names[i], ret);
			पूर्ण

			ret = clk_prepare_enable(hdmi->hpd_clks[i]);
			अगर (ret) अणु
				DRM_DEV_ERROR(dev,
					"failed to enable hpd clk: %s (%d)\n",
					config->hpd_clk_names[i], ret);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = config->hpd_clk_cnt - 1; i >= 0; i--)
			clk_disable_unprepare(hdmi->hpd_clks[i]);
	पूर्ण
पूर्ण

पूर्णांक msm_hdmi_hpd_enable(काष्ठा drm_connector *connector)
अणु
	काष्ठा hdmi_connector *hdmi_connector = to_hdmi_connector(connector);
	काष्ठा hdmi *hdmi = hdmi_connector->hdmi;
	स्थिर काष्ठा hdmi_platक्रमm_config *config = hdmi->config;
	काष्ठा device *dev = &hdmi->pdev->dev;
	uपूर्णांक32_t hpd_ctrl;
	पूर्णांक i, ret;
	अचिन्हित दीर्घ flags;

	क्रम (i = 0; i < config->hpd_reg_cnt; i++) अणु
		ret = regulator_enable(hdmi->hpd_regs[i]);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev, "failed to enable hpd regulator: %s (%d)\n",
					config->hpd_reg_names[i], ret);
			जाओ fail;
		पूर्ण
	पूर्ण

	ret = pinctrl_pm_select_शेष_state(dev);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "pinctrl state chg failed: %d\n", ret);
		जाओ fail;
	पूर्ण

	ret = gpio_config(hdmi, true);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "failed to configure GPIOs: %d\n", ret);
		जाओ fail;
	पूर्ण

	pm_runसमय_get_sync(dev);
	enable_hpd_घड़ीs(hdmi, true);

	msm_hdmi_set_mode(hdmi, false);
	msm_hdmi_phy_reset(hdmi);
	msm_hdmi_set_mode(hdmi, true);

	hdmi_ग_लिखो(hdmi, REG_HDMI_USEC_REFTIMER, 0x0001001b);

	/* enable HPD events: */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_INT_CTRL,
			HDMI_HPD_INT_CTRL_INT_CONNECT |
			HDMI_HPD_INT_CTRL_INT_EN);

	/* set समयout to 4.1ms (max) क्रम hardware debounce */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	hpd_ctrl = hdmi_पढ़ो(hdmi, REG_HDMI_HPD_CTRL);
	hpd_ctrl |= HDMI_HPD_CTRL_TIMEOUT(0x1fff);

	/* Toggle HPD circuit to trigger HPD sense */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_CTRL,
			~HDMI_HPD_CTRL_ENABLE & hpd_ctrl);
	hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_CTRL,
			HDMI_HPD_CTRL_ENABLE | hpd_ctrl);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	वापस 0;

fail:
	वापस ret;
पूर्ण

अटल व्योम hdp_disable(काष्ठा hdmi_connector *hdmi_connector)
अणु
	काष्ठा hdmi *hdmi = hdmi_connector->hdmi;
	स्थिर काष्ठा hdmi_platक्रमm_config *config = hdmi->config;
	काष्ठा device *dev = &hdmi->pdev->dev;
	पूर्णांक i, ret = 0;

	/* Disable HPD पूर्णांकerrupt */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_INT_CTRL, 0);

	msm_hdmi_set_mode(hdmi, false);

	enable_hpd_घड़ीs(hdmi, false);
	pm_runसमय_put_स्वतःsuspend(dev);

	ret = gpio_config(hdmi, false);
	अगर (ret)
		dev_warn(dev, "failed to unconfigure GPIOs: %d\n", ret);

	ret = pinctrl_pm_select_sleep_state(dev);
	अगर (ret)
		dev_warn(dev, "pinctrl state chg failed: %d\n", ret);

	क्रम (i = 0; i < config->hpd_reg_cnt; i++) अणु
		ret = regulator_disable(hdmi->hpd_regs[i]);
		अगर (ret)
			dev_warn(dev, "failed to disable hpd regulator: %s (%d)\n",
					config->hpd_reg_names[i], ret);
	पूर्ण
पूर्ण

अटल व्योम
msm_hdmi_hotplug_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdmi_connector *hdmi_connector =
		container_of(work, काष्ठा hdmi_connector, hpd_work);
	काष्ठा drm_connector *connector = &hdmi_connector->base;
	drm_helper_hpd_irq_event(connector->dev);
पूर्ण

व्योम msm_hdmi_connector_irq(काष्ठा drm_connector *connector)
अणु
	काष्ठा hdmi_connector *hdmi_connector = to_hdmi_connector(connector);
	काष्ठा hdmi *hdmi = hdmi_connector->hdmi;
	uपूर्णांक32_t hpd_पूर्णांक_status, hpd_पूर्णांक_ctrl;

	/* Process HPD: */
	hpd_पूर्णांक_status = hdmi_पढ़ो(hdmi, REG_HDMI_HPD_INT_STATUS);
	hpd_पूर्णांक_ctrl   = hdmi_पढ़ो(hdmi, REG_HDMI_HPD_INT_CTRL);

	अगर ((hpd_पूर्णांक_ctrl & HDMI_HPD_INT_CTRL_INT_EN) &&
			(hpd_पूर्णांक_status & HDMI_HPD_INT_STATUS_INT)) अणु
		bool detected = !!(hpd_पूर्णांक_status & HDMI_HPD_INT_STATUS_CABLE_DETECTED);

		/* ack & disable (temporarily) HPD events: */
		hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_INT_CTRL,
			HDMI_HPD_INT_CTRL_INT_ACK);

		DBG("status=%04x, ctrl=%04x", hpd_पूर्णांक_status, hpd_पूर्णांक_ctrl);

		/* detect disconnect अगर we are connected or visa versa: */
		hpd_पूर्णांक_ctrl = HDMI_HPD_INT_CTRL_INT_EN;
		अगर (!detected)
			hpd_पूर्णांक_ctrl |= HDMI_HPD_INT_CTRL_INT_CONNECT;
		hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_INT_CTRL, hpd_पूर्णांक_ctrl);

		queue_work(hdmi->workq, &hdmi_connector->hpd_work);
	पूर्ण
पूर्ण

अटल क्रमागत drm_connector_status detect_reg(काष्ठा hdmi *hdmi)
अणु
	uपूर्णांक32_t hpd_पूर्णांक_status;

	pm_runसमय_get_sync(&hdmi->pdev->dev);
	enable_hpd_घड़ीs(hdmi, true);

	hpd_पूर्णांक_status = hdmi_पढ़ो(hdmi, REG_HDMI_HPD_INT_STATUS);

	enable_hpd_घड़ीs(hdmi, false);
	pm_runसमय_put_स्वतःsuspend(&hdmi->pdev->dev);

	वापस (hpd_पूर्णांक_status & HDMI_HPD_INT_STATUS_CABLE_DETECTED) ?
			connector_status_connected : connector_status_disconnected;
पूर्ण

#घोषणा HPD_GPIO_INDEX	2
अटल क्रमागत drm_connector_status detect_gpio(काष्ठा hdmi *hdmi)
अणु
	स्थिर काष्ठा hdmi_platक्रमm_config *config = hdmi->config;
	काष्ठा hdmi_gpio_data hpd_gpio = config->gpios[HPD_GPIO_INDEX];

	वापस gpiod_get_value(hpd_gpio.gpiod) ?
			connector_status_connected :
			connector_status_disconnected;
पूर्ण

अटल क्रमागत drm_connector_status hdmi_connector_detect(
		काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा hdmi_connector *hdmi_connector = to_hdmi_connector(connector);
	काष्ठा hdmi *hdmi = hdmi_connector->hdmi;
	स्थिर काष्ठा hdmi_platक्रमm_config *config = hdmi->config;
	काष्ठा hdmi_gpio_data hpd_gpio = config->gpios[HPD_GPIO_INDEX];
	क्रमागत drm_connector_status stat_gpio, stat_reg;
	पूर्णांक retry = 20;

	/*
	 * some platक्रमms may not have hpd gpio. Rely only on the status
	 * provided by REG_HDMI_HPD_INT_STATUS in this हाल.
	 */
	अगर (!hpd_gpio.gpiod)
		वापस detect_reg(hdmi);

	करो अणु
		stat_gpio = detect_gpio(hdmi);
		stat_reg  = detect_reg(hdmi);

		अगर (stat_gpio == stat_reg)
			अवरोध;

		mdelay(10);
	पूर्ण जबतक (--retry);

	/* the status we get from पढ़ोing gpio seems to be more reliable,
	 * so trust that one the most अगर we didn't manage to get hdmi and
	 * gpio status to agree:
	 */
	अगर (stat_gpio != stat_reg) अणु
		DBG("HDMI_HPD_INT_STATUS tells us: %d", stat_reg);
		DBG("hpd gpio tells us: %d", stat_gpio);
	पूर्ण

	वापस stat_gpio;
पूर्ण

अटल व्योम hdmi_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा hdmi_connector *hdmi_connector = to_hdmi_connector(connector);

	hdp_disable(hdmi_connector);

	drm_connector_cleanup(connector);

	kमुक्त(hdmi_connector);
पूर्ण

अटल पूर्णांक msm_hdmi_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा hdmi_connector *hdmi_connector = to_hdmi_connector(connector);
	काष्ठा hdmi *hdmi = hdmi_connector->hdmi;
	काष्ठा edid *edid;
	uपूर्णांक32_t hdmi_ctrl;
	पूर्णांक ret = 0;

	hdmi_ctrl = hdmi_पढ़ो(hdmi, REG_HDMI_CTRL);
	hdmi_ग_लिखो(hdmi, REG_HDMI_CTRL, hdmi_ctrl | HDMI_CTRL_ENABLE);

	edid = drm_get_edid(connector, hdmi->i2c);

	hdmi_ग_लिखो(hdmi, REG_HDMI_CTRL, hdmi_ctrl);

	hdmi->hdmi_mode = drm_detect_hdmi_monitor(edid);
	drm_connector_update_edid_property(connector, edid);

	अगर (edid) अणु
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक msm_hdmi_connector_mode_valid(काष्ठा drm_connector *connector,
				 काष्ठा drm_display_mode *mode)
अणु
	काष्ठा hdmi_connector *hdmi_connector = to_hdmi_connector(connector);
	काष्ठा hdmi *hdmi = hdmi_connector->hdmi;
	स्थिर काष्ठा hdmi_platक्रमm_config *config = hdmi->config;
	काष्ठा msm_drm_निजी *priv = connector->dev->dev_निजी;
	काष्ठा msm_kms *kms = priv->kms;
	दीर्घ actual, requested;

	requested = 1000 * mode->घड़ी;
	actual = kms->funcs->round_pixclk(kms,
			requested, hdmi_connector->hdmi->encoder);

	/* क्रम mdp5/apq8074, we manage our own pixel clk (as opposed to
	 * mdp4/dtv stuff where pixel clk is asचिन्हित to mdp/encoder
	 * instead):
	 */
	अगर (config->pwr_clk_cnt > 0)
		actual = clk_round_rate(hdmi->pwr_clks[0], actual);

	DBG("requested=%ld, actual=%ld", requested, actual);

	अगर (actual != requested)
		वापस MODE_CLOCK_RANGE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs hdmi_connector_funcs = अणु
	.detect = hdmi_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = hdmi_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs msm_hdmi_connector_helper_funcs = अणु
	.get_modes = msm_hdmi_connector_get_modes,
	.mode_valid = msm_hdmi_connector_mode_valid,
पूर्ण;

/* initialize connector */
काष्ठा drm_connector *msm_hdmi_connector_init(काष्ठा hdmi *hdmi)
अणु
	काष्ठा drm_connector *connector = शून्य;
	काष्ठा hdmi_connector *hdmi_connector;

	hdmi_connector = kzalloc(माप(*hdmi_connector), GFP_KERNEL);
	अगर (!hdmi_connector)
		वापस ERR_PTR(-ENOMEM);

	hdmi_connector->hdmi = hdmi;
	INIT_WORK(&hdmi_connector->hpd_work, msm_hdmi_hotplug_work);

	connector = &hdmi_connector->base;

	drm_connector_init_with_ddc(hdmi->dev, connector,
				    &hdmi_connector_funcs,
				    DRM_MODE_CONNECTOR_HDMIA,
				    hdmi->i2c);
	drm_connector_helper_add(connector, &msm_hdmi_connector_helper_funcs);

	connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			DRM_CONNECTOR_POLL_DISCONNECT;

	connector->पूर्णांकerlace_allowed = 0;
	connector->द्विगुनscan_allowed = 0;

	drm_connector_attach_encoder(connector, hdmi->encoder);

	वापस connector;
पूर्ण
