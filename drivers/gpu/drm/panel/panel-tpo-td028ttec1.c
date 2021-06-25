<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Toppoly TD028TTEC1 Panel Driver
 *
 * Copyright (C) 2019 Texas Instruments Incorporated
 *
 * Based on the omapdrm-specअगरic panel-tpo-td028ttec1 driver
 *
 * Copyright (C) 2008 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 *
 * Neo 1973 code (jbt6k74.c):
 * Copyright (C) 2006-2007 OpenMoko, Inc.
 * Author: Harald Welte <laक्रमge@खोलोmoko.org>
 *
 * Ported and adapted from Neo 1973 U-Boot by:
 * H. Nikolaus Schaller <hns@goldelico.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_modes.h>
#समावेश <drm/drm_panel.h>

#घोषणा JBT_COMMAND			0x000
#घोषणा JBT_DATA			0x100

#घोषणा JBT_REG_SLEEP_IN		0x10
#घोषणा JBT_REG_SLEEP_OUT		0x11

#घोषणा JBT_REG_DISPLAY_OFF		0x28
#घोषणा JBT_REG_DISPLAY_ON		0x29

#घोषणा JBT_REG_RGB_FORMAT		0x3a
#घोषणा JBT_REG_QUAD_RATE		0x3b

#घोषणा JBT_REG_POWER_ON_OFF		0xb0
#घोषणा JBT_REG_BOOSTER_OP		0xb1
#घोषणा JBT_REG_BOOSTER_MODE		0xb2
#घोषणा JBT_REG_BOOSTER_FREQ		0xb3
#घोषणा JBT_REG_OPAMP_SYSCLK		0xb4
#घोषणा JBT_REG_VSC_VOLTAGE		0xb5
#घोषणा JBT_REG_VCOM_VOLTAGE		0xb6
#घोषणा JBT_REG_EXT_DISPL		0xb7
#घोषणा JBT_REG_OUTPUT_CONTROL		0xb8
#घोषणा JBT_REG_DCCLK_DCEV		0xb9
#घोषणा JBT_REG_DISPLAY_MODE1		0xba
#घोषणा JBT_REG_DISPLAY_MODE2		0xbb
#घोषणा JBT_REG_DISPLAY_MODE		0xbc
#घोषणा JBT_REG_ASW_SLEW		0xbd
#घोषणा JBT_REG_DUMMY_DISPLAY		0xbe
#घोषणा JBT_REG_DRIVE_SYSTEM		0xbf

#घोषणा JBT_REG_SLEEP_OUT_FR_A		0xc0
#घोषणा JBT_REG_SLEEP_OUT_FR_B		0xc1
#घोषणा JBT_REG_SLEEP_OUT_FR_C		0xc2
#घोषणा JBT_REG_SLEEP_IN_LCCNT_D	0xc3
#घोषणा JBT_REG_SLEEP_IN_LCCNT_E	0xc4
#घोषणा JBT_REG_SLEEP_IN_LCCNT_F	0xc5
#घोषणा JBT_REG_SLEEP_IN_LCCNT_G	0xc6

#घोषणा JBT_REG_GAMMA1_FINE_1		0xc7
#घोषणा JBT_REG_GAMMA1_FINE_2		0xc8
#घोषणा JBT_REG_GAMMA1_INCLINATION	0xc9
#घोषणा JBT_REG_GAMMA1_BLUE_OFFSET	0xca

#घोषणा JBT_REG_BLANK_CONTROL		0xcf
#घोषणा JBT_REG_BLANK_TH_TV		0xd0
#घोषणा JBT_REG_CKV_ON_OFF		0xd1
#घोषणा JBT_REG_CKV_1_2			0xd2
#घोषणा JBT_REG_OEV_TIMING		0xd3
#घोषणा JBT_REG_ASW_TIMING_1		0xd4
#घोषणा JBT_REG_ASW_TIMING_2		0xd5

#घोषणा JBT_REG_HCLOCK_VGA		0xec
#घोषणा JBT_REG_HCLOCK_QVGA		0xed

काष्ठा td028ttec1_panel अणु
	काष्ठा drm_panel panel;

	काष्ठा spi_device *spi;
पूर्ण;

#घोषणा to_td028ttec1_device(p) container_of(p, काष्ठा td028ttec1_panel, panel)

/*
 * noअंतरभूत_क्रम_stack so we करोn't get multiple copies of tx_buf
 * on the stack in हाल of gcc-plugin-काष्ठाleak
 */
अटल पूर्णांक noअंतरभूत_क्रम_stack
jbt_ret_ग_लिखो_0(काष्ठा td028ttec1_panel *lcd, u8 reg, पूर्णांक *err)
अणु
	काष्ठा spi_device *spi = lcd->spi;
	u16 tx_buf = JBT_COMMAND | reg;
	पूर्णांक ret;

	अगर (err && *err)
		वापस *err;

	ret = spi_ग_लिखो(spi, (u8 *)&tx_buf, माप(tx_buf));
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "%s: SPI write failed: %d\n", __func__, ret);
		अगर (err)
			*err = ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक noअंतरभूत_क्रम_stack
jbt_reg_ग_लिखो_1(काष्ठा td028ttec1_panel *lcd,
		u8 reg, u8 data, पूर्णांक *err)
अणु
	काष्ठा spi_device *spi = lcd->spi;
	u16 tx_buf[2];
	पूर्णांक ret;

	अगर (err && *err)
		वापस *err;

	tx_buf[0] = JBT_COMMAND | reg;
	tx_buf[1] = JBT_DATA | data;

	ret = spi_ग_लिखो(spi, (u8 *)tx_buf, माप(tx_buf));
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "%s: SPI write failed: %d\n", __func__, ret);
		अगर (err)
			*err = ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक noअंतरभूत_क्रम_stack
jbt_reg_ग_लिखो_2(काष्ठा td028ttec1_panel *lcd,
		u8 reg, u16 data, पूर्णांक *err)
अणु
	काष्ठा spi_device *spi = lcd->spi;
	u16 tx_buf[3];
	पूर्णांक ret;

	अगर (err && *err)
		वापस *err;

	tx_buf[0] = JBT_COMMAND | reg;
	tx_buf[1] = JBT_DATA | (data >> 8);
	tx_buf[2] = JBT_DATA | (data & 0xff);

	ret = spi_ग_लिखो(spi, (u8 *)tx_buf, माप(tx_buf));
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "%s: SPI write failed: %d\n", __func__, ret);
		अगर (err)
			*err = ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक td028ttec1_prepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा td028ttec1_panel *lcd = to_td028ttec1_device(panel);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret = 0;

	/* Three बार command zero */
	क्रम (i = 0; i < 3; ++i) अणु
		jbt_ret_ग_लिखो_0(lcd, 0x00, &ret);
		usleep_range(1000, 2000);
	पूर्ण

	/* deep standby out */
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_POWER_ON_OFF, 0x17, &ret);

	/* RGB I/F on, RAM ग_लिखो off, QVGA through, SIGCON enable */
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_DISPLAY_MODE, 0x80, &ret);

	/* Quad mode off */
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_QUAD_RATE, 0x00, &ret);

	/* AVDD on, XVDD on */
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_POWER_ON_OFF, 0x16, &ret);

	/* Output control */
	jbt_reg_ग_लिखो_2(lcd, JBT_REG_OUTPUT_CONTROL, 0xfff9, &ret);

	/* Sleep mode off */
	jbt_ret_ग_लिखो_0(lcd, JBT_REG_SLEEP_OUT, &ret);

	/* at this poपूर्णांक we have like 50% grey */

	/* initialize रेजिस्टर set */
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_DISPLAY_MODE1, 0x01, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_DISPLAY_MODE2, 0x00, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_RGB_FORMAT, 0x60, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_DRIVE_SYSTEM, 0x10, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_BOOSTER_OP, 0x56, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_BOOSTER_MODE, 0x33, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_BOOSTER_FREQ, 0x11, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_BOOSTER_FREQ, 0x11, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_OPAMP_SYSCLK, 0x02, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_VSC_VOLTAGE, 0x2b, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_VCOM_VOLTAGE, 0x40, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_EXT_DISPL, 0x03, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_DCCLK_DCEV, 0x04, &ret);
	/*
	 * शेष of 0x02 in JBT_REG_ASW_SLEW responsible क्रम 72Hz requirement
	 * to aव्योम red / blue flicker
	 */
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_ASW_SLEW, 0x04, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_DUMMY_DISPLAY, 0x00, &ret);

	jbt_reg_ग_लिखो_1(lcd, JBT_REG_SLEEP_OUT_FR_A, 0x11, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_SLEEP_OUT_FR_B, 0x11, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_SLEEP_OUT_FR_C, 0x11, &ret);
	jbt_reg_ग_लिखो_2(lcd, JBT_REG_SLEEP_IN_LCCNT_D, 0x2040, &ret);
	jbt_reg_ग_लिखो_2(lcd, JBT_REG_SLEEP_IN_LCCNT_E, 0x60c0, &ret);
	jbt_reg_ग_लिखो_2(lcd, JBT_REG_SLEEP_IN_LCCNT_F, 0x1020, &ret);
	jbt_reg_ग_लिखो_2(lcd, JBT_REG_SLEEP_IN_LCCNT_G, 0x60c0, &ret);

	jbt_reg_ग_लिखो_2(lcd, JBT_REG_GAMMA1_FINE_1, 0x5533, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_GAMMA1_FINE_2, 0x00, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_GAMMA1_INCLINATION, 0x00, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_GAMMA1_BLUE_OFFSET, 0x00, &ret);

	jbt_reg_ग_लिखो_2(lcd, JBT_REG_HCLOCK_VGA, 0x1f0, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_BLANK_CONTROL, 0x02, &ret);
	jbt_reg_ग_लिखो_2(lcd, JBT_REG_BLANK_TH_TV, 0x0804, &ret);

	jbt_reg_ग_लिखो_1(lcd, JBT_REG_CKV_ON_OFF, 0x01, &ret);
	jbt_reg_ग_लिखो_2(lcd, JBT_REG_CKV_1_2, 0x0000, &ret);

	jbt_reg_ग_लिखो_2(lcd, JBT_REG_OEV_TIMING, 0x0d0e, &ret);
	jbt_reg_ग_लिखो_2(lcd, JBT_REG_ASW_TIMING_1, 0x11a4, &ret);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_ASW_TIMING_2, 0x0e, &ret);

	वापस ret;
पूर्ण

अटल पूर्णांक td028ttec1_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा td028ttec1_panel *lcd = to_td028ttec1_device(panel);

	वापस jbt_ret_ग_लिखो_0(lcd, JBT_REG_DISPLAY_ON, शून्य);
पूर्ण

अटल पूर्णांक td028ttec1_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा td028ttec1_panel *lcd = to_td028ttec1_device(panel);

	jbt_ret_ग_लिखो_0(lcd, JBT_REG_DISPLAY_OFF, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक td028ttec1_unprepare(काष्ठा drm_panel *panel)
अणु
	काष्ठा td028ttec1_panel *lcd = to_td028ttec1_device(panel);

	jbt_reg_ग_लिखो_2(lcd, JBT_REG_OUTPUT_CONTROL, 0x8002, शून्य);
	jbt_ret_ग_लिखो_0(lcd, JBT_REG_SLEEP_IN, शून्य);
	jbt_reg_ग_लिखो_1(lcd, JBT_REG_POWER_ON_OFF, 0x00, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_display_mode td028ttec1_mode = अणु
	.घड़ी = 22153,
	.hdisplay = 480,
	.hsync_start = 480 + 24,
	.hsync_end = 480 + 24 + 8,
	.htotal = 480 + 24 + 8 + 8,
	.vdisplay = 640,
	.vsync_start = 640 + 4,
	.vsync_end = 640 + 4 + 2,
	.vtotal = 640 + 4 + 2 + 2,
	.type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED,
	.flags = DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC,
	.width_mm = 43,
	.height_mm = 58,
पूर्ण;

अटल पूर्णांक td028ttec1_get_modes(काष्ठा drm_panel *panel,
				काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &td028ttec1_mode);
	अगर (!mode)
		वापस -ENOMEM;

	drm_mode_set_name(mode);
	drm_mode_probed_add(connector, mode);

	connector->display_info.width_mm = td028ttec1_mode.width_mm;
	connector->display_info.height_mm = td028ttec1_mode.height_mm;
	/*
	 * FIXME: According to the datasheet sync संकेतs are sampled on the
	 * rising edge of the घड़ी, but the code running on the OpenMoko Neo
	 * FreeRunner and Neo 1973 indicates sampling on the falling edge. This
	 * should be tested on a real device.
	 */
	connector->display_info.bus_flags = DRM_BUS_FLAG_DE_HIGH
					  | DRM_BUS_FLAG_SYNC_SAMPLE_NEGEDGE
					  | DRM_BUS_FLAG_PIXDATA_SAMPLE_POSEDGE;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs td028ttec1_funcs = अणु
	.prepare = td028ttec1_prepare,
	.enable = td028ttec1_enable,
	.disable = td028ttec1_disable,
	.unprepare = td028ttec1_unprepare,
	.get_modes = td028ttec1_get_modes,
पूर्ण;

अटल पूर्णांक td028ttec1_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा td028ttec1_panel *lcd;
	पूर्णांक ret;

	lcd = devm_kzalloc(&spi->dev, माप(*lcd), GFP_KERNEL);
	अगर (!lcd)
		वापस -ENOMEM;

	spi_set_drvdata(spi, lcd);
	lcd->spi = spi;

	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 9;

	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "failed to setup SPI: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_panel_init(&lcd->panel, &lcd->spi->dev, &td028ttec1_funcs,
		       DRM_MODE_CONNECTOR_DPI);

	ret = drm_panel_of_backlight(&lcd->panel);
	अगर (ret)
		वापस ret;

	drm_panel_add(&lcd->panel);

	वापस 0;
पूर्ण

अटल पूर्णांक td028ttec1_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा td028ttec1_panel *lcd = spi_get_drvdata(spi);

	drm_panel_हटाओ(&lcd->panel);
	drm_panel_disable(&lcd->panel);
	drm_panel_unprepare(&lcd->panel);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id td028ttec1_of_match[] = अणु
	अणु .compatible = "tpo,td028ttec1", पूर्ण,
	/* DT backward compatibility. */
	अणु .compatible = "toppoly,td028ttec1", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, td028ttec1_of_match);

अटल स्थिर काष्ठा spi_device_id td028ttec1_ids[] = अणु
	अणु "td028ttec1", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, td028ttec1_ids);

अटल काष्ठा spi_driver td028ttec1_driver = अणु
	.probe		= td028ttec1_probe,
	.हटाओ		= td028ttec1_हटाओ,
	.id_table	= td028ttec1_ids,
	.driver		= अणु
		.name   = "panel-tpo-td028ttec1",
		.of_match_table = td028ttec1_of_match,
	पूर्ण,
पूर्ण;

module_spi_driver(td028ttec1_driver);

MODULE_AUTHOR("H. Nikolaus Schaller <hns@goldelico.com>");
MODULE_DESCRIPTION("Toppoly TD028TTEC1 panel driver");
MODULE_LICENSE("GPL");
