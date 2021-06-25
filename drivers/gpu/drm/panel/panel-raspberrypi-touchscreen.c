<शैली गुरु>
/*
 * Copyright तऊ 2016-2017 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Portions of this file (derived from panel-simple.c) are:
 *
 * Copyright (C) 2013, NVIDIA Corporation.  All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/**
 * Raspberry Pi 7" touchscreen panel driver.
 *
 * The 7" touchscreen consists of a DPI LCD panel, a Toshiba
 * TC358762XBG DSI-DPI bridge, and an I2C-connected Aपंचांगel ATTINY88-MUR
 * controlling घातer management, the LCD PWM, and initial रेजिस्टर
 * setup of the Tohsiba.
 *
 * This driver controls the TC358762 and ATTINY88, presenting a DSI
 * device with a drm_panel.
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>

#घोषणा RPI_DSI_DRIVER_NAME "rpi-ts-dsi"

/* I2C रेजिस्टरs of the Aपंचांगel microcontroller. */
क्रमागत REG_ADDR अणु
	REG_ID = 0x80,
	REG_PORTA, /* BIT(2) क्रम horizontal flip, BIT(3) क्रम vertical flip */
	REG_PORTB,
	REG_PORTC,
	REG_PORTD,
	REG_POWERON,
	REG_PWM,
	REG_DDRA,
	REG_DDRB,
	REG_DDRC,
	REG_DDRD,
	REG_TEST,
	REG_WR_ADDRL,
	REG_WR_ADDRH,
	REG_READH,
	REG_READL,
	REG_WRITEH,
	REG_WRITEL,
	REG_ID2,
पूर्ण;

/* DSI D-PHY Layer Registers */
#घोषणा D0W_DPHYCONTTX		0x0004
#घोषणा CLW_DPHYCONTRX		0x0020
#घोषणा D0W_DPHYCONTRX		0x0024
#घोषणा D1W_DPHYCONTRX		0x0028
#घोषणा COM_DPHYCONTRX		0x0038
#घोषणा CLW_CNTRL		0x0040
#घोषणा D0W_CNTRL		0x0044
#घोषणा D1W_CNTRL		0x0048
#घोषणा DFTMODE_CNTRL		0x0054

/* DSI PPI Layer Registers */
#घोषणा PPI_STARTPPI		0x0104
#घोषणा PPI_BUSYPPI		0x0108
#घोषणा PPI_LINEINITCNT		0x0110
#घोषणा PPI_LPTXTIMECNT		0x0114
#घोषणा PPI_CLS_ATMR		0x0140
#घोषणा PPI_D0S_ATMR		0x0144
#घोषणा PPI_D1S_ATMR		0x0148
#घोषणा PPI_D0S_CLRSIPOCOUNT	0x0164
#घोषणा PPI_D1S_CLRSIPOCOUNT	0x0168
#घोषणा CLS_PRE			0x0180
#घोषणा D0S_PRE			0x0184
#घोषणा D1S_PRE			0x0188
#घोषणा CLS_PREP		0x01A0
#घोषणा D0S_PREP		0x01A4
#घोषणा D1S_PREP		0x01A8
#घोषणा CLS_ZERO		0x01C0
#घोषणा D0S_ZERO		0x01C4
#घोषणा D1S_ZERO		0x01C8
#घोषणा PPI_CLRFLG		0x01E0
#घोषणा PPI_CLRSIPO		0x01E4
#घोषणा HSTIMEOUT		0x01F0
#घोषणा HSTIMEOUTENABLE		0x01F4

/* DSI Protocol Layer Registers */
#घोषणा DSI_STARTDSI		0x0204
#घोषणा DSI_BUSYDSI		0x0208
#घोषणा DSI_LANEENABLE		0x0210
# define DSI_LANEENABLE_CLOCK		BIT(0)
# define DSI_LANEENABLE_D0		BIT(1)
# define DSI_LANEENABLE_D1		BIT(2)

#घोषणा DSI_LANESTATUS0		0x0214
#घोषणा DSI_LANESTATUS1		0x0218
#घोषणा DSI_INTSTATUS		0x0220
#घोषणा DSI_INTMASK		0x0224
#घोषणा DSI_INTCLR		0x0228
#घोषणा DSI_LPTXTO		0x0230
#घोषणा DSI_MODE		0x0260
#घोषणा DSI_PAYLOAD0		0x0268
#घोषणा DSI_PAYLOAD1		0x026C
#घोषणा DSI_SHORTPKTDAT		0x0270
#घोषणा DSI_SHORTPKTREQ		0x0274
#घोषणा DSI_BTASTA		0x0278
#घोषणा DSI_BTACLR		0x027C

/* DSI General Registers */
#घोषणा DSIERRCNT		0x0300
#घोषणा DSISIGMOD		0x0304

/* DSI Application Layer Registers */
#घोषणा APLCTRL			0x0400
#घोषणा APLSTAT			0x0404
#घोषणा APLERR			0x0408
#घोषणा PWRMOD			0x040C
#घोषणा RDPKTLN			0x0410
#घोषणा PXLFMT			0x0414
#घोषणा MEMWRCMD		0x0418

/* LCDC/DPI Host Registers */
#घोषणा LCDCTRL			0x0420
#घोषणा HSR			0x0424
#घोषणा HDISPR			0x0428
#घोषणा VSR			0x042C
#घोषणा VDISPR			0x0430
#घोषणा VFUEN			0x0434

/* DBI-B Host Registers */
#घोषणा DBIBCTRL		0x0440

/* SPI Master Registers */
#घोषणा SPICMR			0x0450
#घोषणा SPITCR			0x0454

/* System Controller Registers */
#घोषणा SYSSTAT			0x0460
#घोषणा SYSCTRL			0x0464
#घोषणा SYSPLL1			0x0468
#घोषणा SYSPLL2			0x046C
#घोषणा SYSPLL3			0x0470
#घोषणा SYSPMCTRL		0x047C

/* GPIO Registers */
#घोषणा GPIOC			0x0480
#घोषणा GPIOO			0x0484
#घोषणा GPIOI			0x0488

/* I2C Registers */
#घोषणा I2CCLKCTRL		0x0490

/* Chip/Rev Registers */
#घोषणा IDREG			0x04A0

/* Debug Registers */
#घोषणा WCMDQUEUE		0x0500
#घोषणा RCMDQUEUE		0x0504

काष्ठा rpi_touchscreen अणु
	काष्ठा drm_panel base;
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा i2c_client *i2c;
पूर्ण;

अटल स्थिर काष्ठा drm_display_mode rpi_touchscreen_modes[] = अणु
	अणु
		/* Modeline comes from the Raspberry Pi firmware, with HFP=1
		 * plugged in and घड़ी re-computed from that.
		 */
		.घड़ी = 25979400 / 1000,
		.hdisplay = 800,
		.hsync_start = 800 + 1,
		.hsync_end = 800 + 1 + 2,
		.htotal = 800 + 1 + 2 + 46,
		.vdisplay = 480,
		.vsync_start = 480 + 7,
		.vsync_end = 480 + 7 + 2,
		.vtotal = 480 + 7 + 2 + 21,
	पूर्ण,
पूर्ण;

अटल काष्ठा rpi_touchscreen *panel_to_ts(काष्ठा drm_panel *panel)
अणु
	वापस container_of(panel, काष्ठा rpi_touchscreen, base);
पूर्ण

अटल पूर्णांक rpi_touchscreen_i2c_पढ़ो(काष्ठा rpi_touchscreen *ts, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(ts->i2c, reg);
पूर्ण

अटल व्योम rpi_touchscreen_i2c_ग_लिखो(काष्ठा rpi_touchscreen *ts,
				      u8 reg, u8 val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(ts->i2c, reg, val);
	अगर (ret)
		dev_err(&ts->dsi->dev, "I2C write failed: %d\n", ret);
पूर्ण

अटल पूर्णांक rpi_touchscreen_ग_लिखो(काष्ठा rpi_touchscreen *ts, u16 reg, u32 val)
अणु
	u8 msg[] = अणु
		reg,
		reg >> 8,
		val,
		val >> 8,
		val >> 16,
		val >> 24,
	पूर्ण;

	mipi_dsi_generic_ग_लिखो(ts->dsi, msg, माप(msg));

	वापस 0;
पूर्ण

अटल पूर्णांक rpi_touchscreen_disable(काष्ठा drm_panel *panel)
अणु
	काष्ठा rpi_touchscreen *ts = panel_to_ts(panel);

	rpi_touchscreen_i2c_ग_लिखो(ts, REG_PWM, 0);

	rpi_touchscreen_i2c_ग_लिखो(ts, REG_POWERON, 0);
	udelay(1);

	वापस 0;
पूर्ण

अटल पूर्णांक rpi_touchscreen_noop(काष्ठा drm_panel *panel)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक rpi_touchscreen_enable(काष्ठा drm_panel *panel)
अणु
	काष्ठा rpi_touchscreen *ts = panel_to_ts(panel);
	पूर्णांक i;

	rpi_touchscreen_i2c_ग_लिखो(ts, REG_POWERON, 1);
	/* Wait क्रम nPWRDWN to go low to indicate घातeron is करोne. */
	क्रम (i = 0; i < 100; i++) अणु
		अगर (rpi_touchscreen_i2c_पढ़ो(ts, REG_PORTB) & 1)
			अवरोध;
	पूर्ण

	rpi_touchscreen_ग_लिखो(ts, DSI_LANEENABLE,
			      DSI_LANEENABLE_CLOCK |
			      DSI_LANEENABLE_D0);
	rpi_touchscreen_ग_लिखो(ts, PPI_D0S_CLRSIPOCOUNT, 0x05);
	rpi_touchscreen_ग_लिखो(ts, PPI_D1S_CLRSIPOCOUNT, 0x05);
	rpi_touchscreen_ग_लिखो(ts, PPI_D0S_ATMR, 0x00);
	rpi_touchscreen_ग_लिखो(ts, PPI_D1S_ATMR, 0x00);
	rpi_touchscreen_ग_लिखो(ts, PPI_LPTXTIMECNT, 0x03);

	rpi_touchscreen_ग_लिखो(ts, SPICMR, 0x00);
	rpi_touchscreen_ग_लिखो(ts, LCDCTRL, 0x00100150);
	rpi_touchscreen_ग_लिखो(ts, SYSCTRL, 0x040f);
	msleep(100);

	rpi_touchscreen_ग_लिखो(ts, PPI_STARTPPI, 0x01);
	rpi_touchscreen_ग_लिखो(ts, DSI_STARTDSI, 0x01);
	msleep(100);

	/* Turn on the backlight. */
	rpi_touchscreen_i2c_ग_लिखो(ts, REG_PWM, 255);

	/* Default to the same orientation as the बंदd source
	 * firmware used क्रम the panel.  Runसमय rotation
	 * configuration will be supported using VC4's plane
	 * orientation bits.
	 */
	rpi_touchscreen_i2c_ग_लिखो(ts, REG_PORTA, BIT(2));

	वापस 0;
पूर्ण

अटल पूर्णांक rpi_touchscreen_get_modes(काष्ठा drm_panel *panel,
				     काष्ठा drm_connector *connector)
अणु
	अचिन्हित पूर्णांक i, num = 0;
	अटल स्थिर u32 bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;

	क्रम (i = 0; i < ARRAY_SIZE(rpi_touchscreen_modes); i++) अणु
		स्थिर काष्ठा drm_display_mode *m = &rpi_touchscreen_modes[i];
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_duplicate(connector->dev, m);
		अगर (!mode) अणु
			dev_err(panel->dev, "failed to add mode %ux%u@%u\n",
				m->hdisplay, m->vdisplay,
				drm_mode_vrefresh(m));
			जारी;
		पूर्ण

		mode->type |= DRM_MODE_TYPE_DRIVER;

		अगर (i == 0)
			mode->type |= DRM_MODE_TYPE_PREFERRED;

		drm_mode_set_name(mode);

		drm_mode_probed_add(connector, mode);
		num++;
	पूर्ण

	connector->display_info.bpc = 8;
	connector->display_info.width_mm = 154;
	connector->display_info.height_mm = 86;
	drm_display_info_set_bus_क्रमmats(&connector->display_info,
					 &bus_क्रमmat, 1);

	वापस num;
पूर्ण

अटल स्थिर काष्ठा drm_panel_funcs rpi_touchscreen_funcs = अणु
	.disable = rpi_touchscreen_disable,
	.unprepare = rpi_touchscreen_noop,
	.prepare = rpi_touchscreen_noop,
	.enable = rpi_touchscreen_enable,
	.get_modes = rpi_touchscreen_get_modes,
पूर्ण;

अटल पूर्णांक rpi_touchscreen_probe(काष्ठा i2c_client *i2c,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा rpi_touchscreen *ts;
	काष्ठा device_node *endpoपूर्णांक, *dsi_host_node;
	काष्ठा mipi_dsi_host *host;
	पूर्णांक ver;
	काष्ठा mipi_dsi_device_info info = अणु
		.type = RPI_DSI_DRIVER_NAME,
		.channel = 0,
		.node = शून्य,
	पूर्ण;

	ts = devm_kzalloc(dev, माप(*ts), GFP_KERNEL);
	अगर (!ts)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, ts);

	ts->i2c = i2c;

	ver = rpi_touchscreen_i2c_पढ़ो(ts, REG_ID);
	अगर (ver < 0) अणु
		dev_err(dev, "Atmel I2C read failed: %d\n", ver);
		वापस -ENODEV;
	पूर्ण

	चयन (ver) अणु
	हाल 0xde: /* ver 1 */
	हाल 0xc3: /* ver 2 */
		अवरोध;
	शेष:
		dev_err(dev, "Unknown Atmel firmware revision: 0x%02x\n", ver);
		वापस -ENODEV;
	पूर्ण

	/* Turn off at boot, so we can cleanly sequence घातering on. */
	rpi_touchscreen_i2c_ग_लिखो(ts, REG_POWERON, 0);

	/* Look up the DSI host.  It needs to probe beक्रमe we करो. */
	endpoपूर्णांक = of_graph_get_next_endpoपूर्णांक(dev->of_node, शून्य);
	अगर (!endpoपूर्णांक)
		वापस -ENODEV;

	dsi_host_node = of_graph_get_remote_port_parent(endpoपूर्णांक);
	अगर (!dsi_host_node)
		जाओ error;

	host = of_find_mipi_dsi_host_by_node(dsi_host_node);
	of_node_put(dsi_host_node);
	अगर (!host) अणु
		of_node_put(endpoपूर्णांक);
		वापस -EPROBE_DEFER;
	पूर्ण

	info.node = of_graph_get_remote_port(endpoपूर्णांक);
	अगर (!info.node)
		जाओ error;

	of_node_put(endpoपूर्णांक);

	ts->dsi = mipi_dsi_device_रेजिस्टर_full(host, &info);
	अगर (IS_ERR(ts->dsi)) अणु
		dev_err(dev, "DSI device registration failed: %ld\n",
			PTR_ERR(ts->dsi));
		वापस PTR_ERR(ts->dsi);
	पूर्ण

	drm_panel_init(&ts->base, dev, &rpi_touchscreen_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	/* This appears last, as it's what will unblock the DSI host
	 * driver's component bind function.
	 */
	drm_panel_add(&ts->base);

	वापस 0;

error:
	of_node_put(endpoपूर्णांक);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक rpi_touchscreen_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rpi_touchscreen *ts = i2c_get_clientdata(i2c);

	mipi_dsi_detach(ts->dsi);

	drm_panel_हटाओ(&ts->base);

	mipi_dsi_device_unरेजिस्टर(ts->dsi);
	kमुक्त(ts->dsi);

	वापस 0;
पूर्ण

अटल पूर्णांक rpi_touchscreen_dsi_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	पूर्णांक ret;

	dsi->mode_flags = (MIPI_DSI_MODE_VIDEO |
			   MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
			   MIPI_DSI_MODE_LPM);
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->lanes = 1;

	ret = mipi_dsi_attach(dsi);

	अगर (ret)
		dev_err(&dsi->dev, "failed to attach dsi to host: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा mipi_dsi_driver rpi_touchscreen_dsi_driver = अणु
	.driver.name = RPI_DSI_DRIVER_NAME,
	.probe = rpi_touchscreen_dsi_probe,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rpi_touchscreen_of_ids[] = अणु
	अणु .compatible = "raspberrypi,7inch-touchscreen-panel" पूर्ण,
	अणु पूर्ण /* sentinel */
पूर्ण;
MODULE_DEVICE_TABLE(of, rpi_touchscreen_of_ids);

अटल काष्ठा i2c_driver rpi_touchscreen_driver = अणु
	.driver = अणु
		.name = "rpi_touchscreen",
		.of_match_table = rpi_touchscreen_of_ids,
	पूर्ण,
	.probe = rpi_touchscreen_probe,
	.हटाओ = rpi_touchscreen_हटाओ,
पूर्ण;

अटल पूर्णांक __init rpi_touchscreen_init(व्योम)
अणु
	mipi_dsi_driver_रेजिस्टर(&rpi_touchscreen_dsi_driver);
	वापस i2c_add_driver(&rpi_touchscreen_driver);
पूर्ण
module_init(rpi_touchscreen_init);

अटल व्योम __निकास rpi_touchscreen_निकास(व्योम)
अणु
	i2c_del_driver(&rpi_touchscreen_driver);
	mipi_dsi_driver_unरेजिस्टर(&rpi_touchscreen_dsi_driver);
पूर्ण
module_निकास(rpi_touchscreen_निकास);

MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_DESCRIPTION("Raspberry Pi 7-inch touchscreen driver");
MODULE_LICENSE("GPL v2");
