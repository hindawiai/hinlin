<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * MIPI-DSI Sony ACX424AKP panel driver. This is a 480x864
 * AMOLED panel with a command-only DSI पूर्णांकerface.
 *
 * Copyright (C) Linaro Ltd. 2019
 * Author: Linus Walleij
 * Based on code and know-how from Marcus Lorentzon
 * Copyright (C) ST-Ericsson SA 2010
 */
#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <video/mipi_display.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा ACX424_DCS_READ_ID1		0xDA
#घोषणा ACX424_DCS_READ_ID2		0xDB
#घोषणा ACX424_DCS_READ_ID3		0xDC
#घोषणा ACX424_DCS_SET_MDDI		0xAE

/*
 * Sony seems to use venकरोr ID 0x81
 */
#घोषणा DISPLAY_SONY_ACX424AKP_ID1	0x811b
#घोषणा DISPLAY_SONY_ACX424AKP_ID2	0x811a
/*
 * The third ID looks like a bug, venकरोr IDs begin at 0x80
 * and panel 00 ... seems like शेष values.
 */
#घोषणा DISPLAY_SONY_ACX424AKP_ID3	0x8000

काष्ठा acx424akp अणु
	काष्ठा drm_panel panel;
	काष्ठा device *dev;
	काष्ठा backlight_device *bl;
	काष्ठा regulator *supply;
	काष्ठा gpio_desc *reset_gpio;
	bool video_mode;
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode sony_acx424akp_vid_mode = अणु
	.घड़ी = 27234,
	.hdisplay = 480,
	.hsync_start = 480 + 15,
	.hsync_end = 480 + 15 + 0,
	.htotal = 480 + 15 + 0 + 15,
	.vdisplay = 864,
	.vsync_start = 864 + 14,
	.vsync_end = 864 + 14 + 1,
	.vtotal = 864 + 14 + 1 + 11,
	.width_mm = 48,
	.height_mm = 84,
	.flags = DRM_MODE_FLAG_PVSYNC,
पूर्ण;

/*
 * The timings are not very helpful as the display is used in
 * command mode using the maximum HS frequency.
 */
अटल स्थिर काष्ठा drm_display_mode sony_acx424akp_cmd_mode = अणु
	.घड़ी = 35478,
	.hdisplay = 480,
	.hsync_start = 480 + 154,
	.hsync_end = 480 + 154 + 16,
	.htotal = 480 + 154 + 16 + 32,
	.vdisplay = 864,
	.vsync_start = 864 + 1,
	.vsync_end = 864 + 1 + 1,
	.vtotal = 864 + 1 + 1 + 1,
	/*
	 * Some desired refresh rate, experiments at the maximum "pixel"
	 * घड़ी speed (HS घड़ी 420 MHz) yields around 117Hz.
	 */
	.width_mm = 48,
	.height_mm = 84,
पूर्ण;

अटल अंतरभूत काष्ठा acx424akp *panel_to_acx424akp(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा acx424akp, panel);
पूर्ण

#घोषणा FOSC			20 /* 20Mhz */
#घोषणा SCALE_FACTOR_NS_DIV_MHZ	1000

अटल पूर्णांक acx424akp_set_brightness(काष्ठा backlight_device *bl)
अणु
	काष्ठा acx424akp *acx = bl_get_data(bl);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(acx->dev);
	पूर्णांक period_ns = 1023;
	पूर्णांक duty_ns = bl->props.brightness;
	u8 pwm_ratio;
	u8 pwm_भाग;
	u8 par;
	पूर्णांक ret;

	/* Calculate the PWM duty cycle in n/256's */
	pwm_ratio = max(((duty_ns * 256) / period_ns) - 1, 1);
	pwm_भाग = max(1,
		      ((FOSC * period_ns) / 256) /
		      SCALE_FACTOR_NS_DIV_MHZ);

	/* Set up PWM dutycycle ONE byte (dअगरfers from the standard) */
	dev_dbg(acx->dev, "calculated duty cycle %02x\n", pwm_ratio);
	ret = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_SET_DISPLAY_BRIGHTNESS,
				 &pwm_ratio, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "failed to set display PWM ratio (%d)\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Sequence to ग_लिखो PWMDIV:
	 *	address		data
	 *	0xF3		0xAA   CMD2 Unlock
	 *	0x00		0x01   Enter CMD2 page 0
	 *	0X7D		0x01   No reload MTP of CMD2 P1
	 *	0x22		PWMDIV
	 *	0x7F		0xAA   CMD2 page 1 lock
	 */
	par = 0xaa;
	ret = mipi_dsi_dcs_ग_लिखो(dsi, 0xf3, &par, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "failed to unlock CMD 2 (%d)\n", ret);
		वापस ret;
	पूर्ण
	par = 0x01;
	ret = mipi_dsi_dcs_ग_लिखो(dsi, 0x00, &par, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "failed to enter page 1 (%d)\n", ret);
		वापस ret;
	पूर्ण
	par = 0x01;
	ret = mipi_dsi_dcs_ग_लिखो(dsi, 0x7d, &par, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "failed to disable MTP reload (%d)\n", ret);
		वापस ret;
	पूर्ण
	ret = mipi_dsi_dcs_ग_लिखो(dsi, 0x22, &pwm_भाग, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "failed to set PWM divisor (%d)\n", ret);
		वापस ret;
	पूर्ण
	par = 0xaa;
	ret = mipi_dsi_dcs_ग_लिखो(dsi, 0x7f, &par, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "failed to lock CMD 2 (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Enable backlight */
	par = 0x24;
	ret = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				 &par, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "failed to enable display backlight (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops acx424akp_bl_ops = अणु
	.update_status = acx424akp_set_brightness,
पूर्ण;

अटल पूर्णांक acx424akp_पढ़ो_id(काष्ठा acx424akp *acx)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(acx->dev);
	u8 venकरोr, version, panel;
	u16 val;
	पूर्णांक ret;

	ret = mipi_dsi_dcs_पढ़ो(dsi, ACX424_DCS_READ_ID1, &venकरोr, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "could not vendor ID byte\n");
		वापस ret;
	पूर्ण
	ret = mipi_dsi_dcs_पढ़ो(dsi, ACX424_DCS_READ_ID2, &version, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "could not read device version byte\n");
		वापस ret;
	पूर्ण
	ret = mipi_dsi_dcs_पढ़ो(dsi, ACX424_DCS_READ_ID3, &panel, 1);
	अगर (ret < 0) अणु
		dev_err(acx->dev, "could not read panel ID byte\n");
		वापस ret;
	पूर्ण

	अगर (venकरोr == 0x00) अणु
		dev_err(acx->dev, "device vendor ID is zero\n");
		वापस -ENODEV;
	पूर्ण

	val = (venकरोr << 8) | panel;
	चयन (val) अणु
	हाल DISPLAY_SONY_ACX424AKP_ID1:
	हाल DISPLAY_SONY_ACX424AKP_ID2:
	हाल DISPLAY_SONY_ACX424AKP_ID3:
		dev_info(acx->dev, "MTP vendor: %02x, version: %02x, panel: %02x\n",
			 venकरोr, version, panel);
		अवरोध;
	शेष:
		dev_info(acx->dev, "unknown vendor: %02x, version: %02x, panel: %02x\n",
			 venकरोr, version, panel);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acx424akp_घातer_on(काष्ठा acx424akp *acx)
अणु
	पूर्णांक ret;

	ret = regulator_enable(acx->supply);
	अगर (ret) अणु
		dev_err(acx->dev, "failed to enable supply (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Assert RESET */
	gpiod_set_value_cansleep(acx->reset_gpio, 1);
	udelay(20);
	/* De-निश्चित RESET */
	gpiod_set_value_cansleep(acx->reset_gpio, 0);
	usleep_range(11000, 20000);

	वापस 0;
पूर्ण

अटल व्योम acx424akp_घातer_off(काष्ठा acx424akp *acx)
अणु
	/* Assert RESET */
	gpiod_set_value_cansleep(acx->reset_gpio, 1);
	usleep_range(11000, 20000);

	regulator_disable(acx->supply);
पूर्ण

अटल पूर्णांक acx424akp_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा acx424akp *acx = panel_to_acx424akp(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(acx->dev);
	स्थिर u8 mddi = 3;
	पूर्णांक ret;

	ret = acx424akp_घातer_on(acx);
	अगर (ret)
		वापस ret;

	ret = acx424akp_पढ़ो_id(acx);
	अगर (ret) अणु
		dev_err(acx->dev, "failed to read panel ID (%d)\n", ret);
		जाओ err_घातer_off;
	पूर्ण

	/* Enabe tearing mode: send TE (tearing effect) at VBLANK */
	ret = mipi_dsi_dcs_set_tear_on(dsi,
				       MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	अगर (ret) अणु
		dev_err(acx->dev, "failed to enable vblank TE (%d)\n", ret);
		जाओ err_घातer_off;
	पूर्ण

	/*
	 * Set MDDI
	 *
	 * This presumably deactivates the Qualcomm MDDI पूर्णांकerface and
	 * selects DSI, similar code is found in other drivers such as the
	 * Sharp LS043T1LE01 which makes us suspect that this panel may be
	 * using a Novatek NT35565 or similar display driver chip that shares
	 * this command. Due to the lack of करोcumentation we cannot know क्रम
	 * sure.
	 */
	ret = mipi_dsi_dcs_ग_लिखो(dsi, ACX424_DCS_SET_MDDI,
				 &mddi, माप(mddi));
	अगर (ret < 0) अणु
		dev_err(acx->dev, "failed to set MDDI (%d)\n", ret);
		जाओ err_घातer_off;
	पूर्ण

	/* Exit sleep mode */
	ret = mipi_dsi_dcs_निकास_sleep_mode(dsi);
	अगर (ret) अणु
		dev_err(acx->dev, "failed to exit sleep mode (%d)\n", ret);
		जाओ err_घातer_off;
	पूर्ण
	msleep(140);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	अगर (ret) अणु
		dev_err(acx->dev, "failed to turn display on (%d)\n", ret);
		जाओ err_घातer_off;
	पूर्ण
	अगर (acx->video_mode) अणु
		/* In video mode turn peripheral on */
		ret = mipi_dsi_turn_on_peripheral(dsi);
		अगर (ret) अणु
			dev_err(acx->dev, "failed to turn on peripheral\n");
			जाओ err_घातer_off;
		पूर्ण
	पूर्ण

	acx->bl->props.घातer = FB_BLANK_NORMAL;

	वापस 0;

err_घातer_off:
	acx424akp_घातer_off(acx);
	वापस ret;
पूर्ण

अटल पूर्णांक acx424akp_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा acx424akp *acx = panel_to_acx424akp(panel);
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(acx->dev);
	u8 par;
	पूर्णांक ret;

	/* Disable backlight */
	par = 0x00;
	ret = mipi_dsi_dcs_ग_लिखो(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				 &par, 1);
	अगर (ret) अणु
		dev_err(acx->dev, "failed to disable display backlight (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = mipi_dsi_dcs_set_display_off(dsi);
	अगर (ret) अणु
		dev_err(acx->dev, "failed to turn display off (%d)\n", ret);
		वापस ret;
	पूर्ण

	/* Enter sleep mode */
	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	अगर (ret) अणु
		dev_err(acx->dev, "failed to enter sleep mode (%d)\n", ret);
		वापस ret;
	पूर्ण
	msleep(85);

	acx424akp_घातer_off(acx);
	acx->bl->props.घातer = FB_BLANK_POWERDOWN;

	वापस 0;
पूर्ण

अटल पूर्णांक acx424akp_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा acx424akp *acx = panel_to_acx424akp(panel);

	/*
	 * The backlight is on as दीर्घ as the display is on
	 * so no use to call backlight_enable() here.
	 */
	acx->bl->props.घातer = FB_BLANK_UNBLANK;

	वापस 0;
पूर्ण

अटल पूर्णांक acx424akp_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा acx424akp *acx = panel_to_acx424akp(panel);

	/*
	 * The backlight is on as दीर्घ as the display is on
	 * so no use to call backlight_disable() here.
	 */
	acx->bl->props.घातer = FB_BLANK_NORMAL;

	वापस 0;
पूर्ण

अटल पूर्णांक acx424akp_get_modes(काष्ठा drm_panel *panel,
			       काष्ठा drm_connector *connector)
अणु
	काष्ठा acx424akp *acx = panel_to_acx424akp(panel);
	काष्ठा drm_display_mode *mode;

	अगर (acx->video_mode)
		mode = drm_mode_duplicate(connector->dev,
					  &sony_acx424akp_vid_mode);
	अन्यथा
		mode = drm_mode_duplicate(connector->dev,
					  &sony_acx424akp_cmd_mode);
	अगर (!mode) अणु
		dev_err(panel->dev, "bad mode or failed to add mode\n");
		वापस -EINVAL;
	पूर्ण
	drm_mode_set_name(mode);
	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;

	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;

	drm_mode_probed_add(connector, mode);

	वापस 1; /* Number of modes */
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs acx424akp_drm_funcs = अणु
	.disable = acx424akp_disable,
	.unprepare = acx424akp_unprepare,
	.prepare = acx424akp_prepare,
	.enable = acx424akp_enable,
	.get_modes = acx424akp_get_modes,
पूर्ण;

अटल पूर्णांक acx424akp_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	काष्ठा acx424akp *acx;
	पूर्णांक ret;

	acx = devm_kzalloc(dev, माप(काष्ठा acx424akp), GFP_KERNEL);
	अगर (!acx)
		वापस -ENOMEM;
	acx->video_mode = of_property_पढ़ो_bool(dev->of_node,
						"enforce-video-mode");

	mipi_dsi_set_drvdata(dsi, acx);
	acx->dev = dev;

	dsi->lanes = 2;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	/*
	 * FIXME: these come from the ST-Ericsson venकरोr driver क्रम the
	 * HREF520 and seems to reflect limitations in the PLLs on that
	 * platक्रमm, अगर you have the datasheet, please cross-check the
	 * actual max rates.
	 */
	dsi->lp_rate = 19200000;
	dsi->hs_rate = 420160000;

	अगर (acx->video_mode)
		/* Burst mode using event क्रम sync */
		dsi->mode_flags =
			MIPI_DSI_MODE_VIDEO |
			MIPI_DSI_MODE_VIDEO_BURST;
	अन्यथा
		dsi->mode_flags =
			MIPI_DSI_CLOCK_NON_CONTINUOUS;

	acx->supply = devm_regulator_get(dev, "vddi");
	अगर (IS_ERR(acx->supply))
		वापस PTR_ERR(acx->supply);

	/* This निश्चितs RESET by शेष */
	acx->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						  GPIOD_OUT_HIGH);
	अगर (IS_ERR(acx->reset_gpio)) अणु
		ret = PTR_ERR(acx->reset_gpio);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to request GPIO (%d)\n", ret);
		वापस ret;
	पूर्ण

	drm_panel_init(&acx->panel, dev, &acx424akp_drm_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	acx->bl = devm_backlight_device_रेजिस्टर(dev, "acx424akp", dev, acx,
						 &acx424akp_bl_ops, शून्य);
	अगर (IS_ERR(acx->bl)) अणु
		dev_err(dev, "failed to register backlight device\n");
		वापस PTR_ERR(acx->bl);
	पूर्ण
	acx->bl->props.max_brightness = 1023;
	acx->bl->props.brightness = 512;
	acx->bl->props.घातer = FB_BLANK_POWERDOWN;

	drm_panel_add(&acx->panel);

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		drm_panel_हटाओ(&acx->panel);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acx424akp_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा acx424akp *acx = mipi_dsi_get_drvdata(dsi);

	mipi_dsi_detach(dsi);
	drm_panel_हटाओ(&acx->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id acx424akp_of_match[] = अणु
	अणु .compatible = "sony,acx424akp" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, acx424akp_of_match);

अटल काष्ठा mipi_dsi_driver acx424akp_driver = अणु
	.probe = acx424akp_probe,
	.हटाओ = acx424akp_हटाओ,
	.driver = अणु
		.name = "panel-sony-acx424akp",
		.of_match_table = acx424akp_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(acx424akp_driver);

MODULE_AUTHOR("Linus Wallei <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("MIPI-DSI Sony acx424akp Panel Driver");
MODULE_LICENSE("GPL v2");
