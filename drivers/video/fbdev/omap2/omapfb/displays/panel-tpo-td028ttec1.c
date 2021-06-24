<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Toppoly TD028TTEC1 panel support
 *
 * Copyright (C) 2008 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Neo 1973 code (jbt6k74.c):
 * Copyright (C) 2006-2007 by OpenMoko, Inc.
 * Author: Harald Welte <laक्रमge@खोलोmoko.org>
 *
 * Ported and adapted from Neo 1973 U-Boot by:
 * H. Nikolaus Schaller <hns@goldelico.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/gpपन.स>
#समावेश <video/omapfb_dss.h>

काष्ठा panel_drv_data अणु
	काष्ठा omap_dss_device dssdev;
	काष्ठा omap_dss_device *in;

	पूर्णांक data_lines;

	काष्ठा omap_video_timings videomode;

	काष्ठा spi_device *spi_dev;
पूर्ण;

अटल स्थिर काष्ठा omap_video_timings td028ttec1_panel_timings = अणु
	.x_res		= 480,
	.y_res		= 640,
	.pixelघड़ी	= 22153000,
	.hfp		= 24,
	.hsw		= 8,
	.hbp		= 8,
	.vfp		= 4,
	.vsw		= 2,
	.vbp		= 2,

	.vsync_level	= OMAPDSS_SIG_ACTIVE_LOW,
	.hsync_level	= OMAPDSS_SIG_ACTIVE_LOW,

	.data_pclk_edge	= OMAPDSS_DRIVE_SIG_FALLING_EDGE,
	.de_level	= OMAPDSS_SIG_ACTIVE_HIGH,
	.sync_pclk_edge	= OMAPDSS_DRIVE_SIG_RISING_EDGE,
पूर्ण;

#घोषणा JBT_COMMAND	0x000
#घोषणा JBT_DATA	0x100

अटल पूर्णांक jbt_ret_ग_लिखो_0(काष्ठा panel_drv_data *ddata, u8 reg)
अणु
	पूर्णांक rc;
	u16 tx_buf = JBT_COMMAND | reg;

	rc = spi_ग_लिखो(ddata->spi_dev, (u8 *)&tx_buf,
			1*माप(u16));
	अगर (rc != 0)
		dev_err(&ddata->spi_dev->dev,
			"jbt_ret_write_0 spi_write ret %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक jbt_reg_ग_लिखो_1(काष्ठा panel_drv_data *ddata, u8 reg, u8 data)
अणु
	पूर्णांक rc;
	u16 tx_buf[2];

	tx_buf[0] = JBT_COMMAND | reg;
	tx_buf[1] = JBT_DATA | data;
	rc = spi_ग_लिखो(ddata->spi_dev, (u8 *)tx_buf,
			2*माप(u16));
	अगर (rc != 0)
		dev_err(&ddata->spi_dev->dev,
			"jbt_reg_write_1 spi_write ret %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक jbt_reg_ग_लिखो_2(काष्ठा panel_drv_data *ddata, u8 reg, u16 data)
अणु
	पूर्णांक rc;
	u16 tx_buf[3];

	tx_buf[0] = JBT_COMMAND | reg;
	tx_buf[1] = JBT_DATA | (data >> 8);
	tx_buf[2] = JBT_DATA | (data & 0xff);

	rc = spi_ग_लिखो(ddata->spi_dev, (u8 *)tx_buf,
			3*माप(u16));

	अगर (rc != 0)
		dev_err(&ddata->spi_dev->dev,
			"jbt_reg_write_2 spi_write ret %d\n", rc);

	वापस rc;
पूर्ण

क्रमागत jbt_रेजिस्टर अणु
	JBT_REG_SLEEP_IN		= 0x10,
	JBT_REG_SLEEP_OUT		= 0x11,

	JBT_REG_DISPLAY_OFF		= 0x28,
	JBT_REG_DISPLAY_ON		= 0x29,

	JBT_REG_RGB_FORMAT		= 0x3a,
	JBT_REG_QUAD_RATE		= 0x3b,

	JBT_REG_POWER_ON_OFF		= 0xb0,
	JBT_REG_BOOSTER_OP		= 0xb1,
	JBT_REG_BOOSTER_MODE		= 0xb2,
	JBT_REG_BOOSTER_FREQ		= 0xb3,
	JBT_REG_OPAMP_SYSCLK		= 0xb4,
	JBT_REG_VSC_VOLTAGE		= 0xb5,
	JBT_REG_VCOM_VOLTAGE		= 0xb6,
	JBT_REG_EXT_DISPL		= 0xb7,
	JBT_REG_OUTPUT_CONTROL		= 0xb8,
	JBT_REG_DCCLK_DCEV		= 0xb9,
	JBT_REG_DISPLAY_MODE1		= 0xba,
	JBT_REG_DISPLAY_MODE2		= 0xbb,
	JBT_REG_DISPLAY_MODE		= 0xbc,
	JBT_REG_ASW_SLEW		= 0xbd,
	JBT_REG_DUMMY_DISPLAY		= 0xbe,
	JBT_REG_DRIVE_SYSTEM		= 0xbf,

	JBT_REG_SLEEP_OUT_FR_A		= 0xc0,
	JBT_REG_SLEEP_OUT_FR_B		= 0xc1,
	JBT_REG_SLEEP_OUT_FR_C		= 0xc2,
	JBT_REG_SLEEP_IN_LCCNT_D	= 0xc3,
	JBT_REG_SLEEP_IN_LCCNT_E	= 0xc4,
	JBT_REG_SLEEP_IN_LCCNT_F	= 0xc5,
	JBT_REG_SLEEP_IN_LCCNT_G	= 0xc6,

	JBT_REG_GAMMA1_FINE_1		= 0xc7,
	JBT_REG_GAMMA1_FINE_2		= 0xc8,
	JBT_REG_GAMMA1_INCLINATION	= 0xc9,
	JBT_REG_GAMMA1_BLUE_OFFSET	= 0xca,

	JBT_REG_BLANK_CONTROL		= 0xcf,
	JBT_REG_BLANK_TH_TV		= 0xd0,
	JBT_REG_CKV_ON_OFF		= 0xd1,
	JBT_REG_CKV_1_2			= 0xd2,
	JBT_REG_OEV_TIMING		= 0xd3,
	JBT_REG_ASW_TIMING_1		= 0xd4,
	JBT_REG_ASW_TIMING_2		= 0xd5,

	JBT_REG_HCLOCK_VGA		= 0xec,
	JBT_REG_HCLOCK_QVGA		= 0xed,
पूर्ण;

#घोषणा to_panel_data(p) container_of(p, काष्ठा panel_drv_data, dssdev)

अटल पूर्णांक td028ttec1_panel_connect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (omapdss_device_is_connected(dssdev))
		वापस 0;

	r = in->ops.dpi->connect(in, dssdev);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल व्योम td028ttec1_panel_disconnect(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस;

	in->ops.dpi->disconnect(in, dssdev);
पूर्ण

अटल पूर्णांक td028ttec1_panel_enable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;
	पूर्णांक r;

	अगर (!omapdss_device_is_connected(dssdev))
		वापस -ENODEV;

	अगर (omapdss_device_is_enabled(dssdev))
		वापस 0;

	अगर (ddata->data_lines)
		in->ops.dpi->set_data_lines(in, ddata->data_lines);
	in->ops.dpi->set_timings(in, &ddata->videomode);

	r = in->ops.dpi->enable(in);
	अगर (r)
		वापस r;

	dev_dbg(dssdev->dev, "td028ttec1_panel_enable() - state %d\n",
		dssdev->state);

	/* three बार command zero */
	r |= jbt_ret_ग_लिखो_0(ddata, 0x00);
	usleep_range(1000, 2000);
	r |= jbt_ret_ग_लिखो_0(ddata, 0x00);
	usleep_range(1000, 2000);
	r |= jbt_ret_ग_लिखो_0(ddata, 0x00);
	usleep_range(1000, 2000);

	अगर (r) अणु
		dev_warn(dssdev->dev, "transfer error\n");
		जाओ transfer_err;
	पूर्ण

	/* deep standby out */
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_POWER_ON_OFF, 0x17);

	/* RGB I/F on, RAM ग_लिखो off, QVGA through, SIGCON enable */
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_DISPLAY_MODE, 0x80);

	/* Quad mode off */
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_QUAD_RATE, 0x00);

	/* AVDD on, XVDD on */
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_POWER_ON_OFF, 0x16);

	/* Output control */
	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_OUTPUT_CONTROL, 0xfff9);

	/* Sleep mode off */
	r |= jbt_ret_ग_लिखो_0(ddata, JBT_REG_SLEEP_OUT);

	/* at this poपूर्णांक we have like 50% grey */

	/* initialize रेजिस्टर set */
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_DISPLAY_MODE1, 0x01);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_DISPLAY_MODE2, 0x00);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_RGB_FORMAT, 0x60);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_DRIVE_SYSTEM, 0x10);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_BOOSTER_OP, 0x56);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_BOOSTER_MODE, 0x33);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_BOOSTER_FREQ, 0x11);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_BOOSTER_FREQ, 0x11);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_OPAMP_SYSCLK, 0x02);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_VSC_VOLTAGE, 0x2b);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_VCOM_VOLTAGE, 0x40);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_EXT_DISPL, 0x03);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_DCCLK_DCEV, 0x04);
	/*
	 * शेष of 0x02 in JBT_REG_ASW_SLEW responsible क्रम 72Hz requirement
	 * to aव्योम red / blue flicker
	 */
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_ASW_SLEW, 0x04);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_DUMMY_DISPLAY, 0x00);

	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_SLEEP_OUT_FR_A, 0x11);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_SLEEP_OUT_FR_B, 0x11);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_SLEEP_OUT_FR_C, 0x11);
	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_SLEEP_IN_LCCNT_D, 0x2040);
	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_SLEEP_IN_LCCNT_E, 0x60c0);
	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_SLEEP_IN_LCCNT_F, 0x1020);
	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_SLEEP_IN_LCCNT_G, 0x60c0);

	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_GAMMA1_FINE_1, 0x5533);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_GAMMA1_FINE_2, 0x00);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_GAMMA1_INCLINATION, 0x00);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_GAMMA1_BLUE_OFFSET, 0x00);

	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_HCLOCK_VGA, 0x1f0);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_BLANK_CONTROL, 0x02);
	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_BLANK_TH_TV, 0x0804);

	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_CKV_ON_OFF, 0x01);
	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_CKV_1_2, 0x0000);

	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_OEV_TIMING, 0x0d0e);
	r |= jbt_reg_ग_लिखो_2(ddata, JBT_REG_ASW_TIMING_1, 0x11a4);
	r |= jbt_reg_ग_लिखो_1(ddata, JBT_REG_ASW_TIMING_2, 0x0e);

	r |= jbt_ret_ग_लिखो_0(ddata, JBT_REG_DISPLAY_ON);

	dssdev->state = OMAP_DSS_DISPLAY_ACTIVE;

transfer_err:

	वापस r ? -EIO : 0;
पूर्ण

अटल व्योम td028ttec1_panel_disable(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	अगर (!omapdss_device_is_enabled(dssdev))
		वापस;

	dev_dbg(dssdev->dev, "td028ttec1_panel_disable()\n");

	jbt_ret_ग_लिखो_0(ddata, JBT_REG_DISPLAY_OFF);
	jbt_reg_ग_लिखो_2(ddata, JBT_REG_OUTPUT_CONTROL, 0x8002);
	jbt_ret_ग_लिखो_0(ddata, JBT_REG_SLEEP_IN);
	jbt_reg_ग_लिखो_1(ddata, JBT_REG_POWER_ON_OFF, 0x00);

	in->ops.dpi->disable(in);

	dssdev->state = OMAP_DSS_DISPLAY_DISABLED;
पूर्ण

अटल व्योम td028ttec1_panel_set_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	ddata->videomode = *timings;
	dssdev->panel.timings = *timings;

	in->ops.dpi->set_timings(in, timings);
पूर्ण

अटल व्योम td028ttec1_panel_get_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);

	*timings = ddata->videomode;
पूर्ण

अटल पूर्णांक td028ttec1_panel_check_timings(काष्ठा omap_dss_device *dssdev,
		काष्ठा omap_video_timings *timings)
अणु
	काष्ठा panel_drv_data *ddata = to_panel_data(dssdev);
	काष्ठा omap_dss_device *in = ddata->in;

	वापस in->ops.dpi->check_timings(in, timings);
पूर्ण

अटल काष्ठा omap_dss_driver td028ttec1_ops = अणु
	.connect	= td028ttec1_panel_connect,
	.disconnect	= td028ttec1_panel_disconnect,

	.enable		= td028ttec1_panel_enable,
	.disable	= td028ttec1_panel_disable,

	.set_timings	= td028ttec1_panel_set_timings,
	.get_timings	= td028ttec1_panel_get_timings,
	.check_timings	= td028ttec1_panel_check_timings,
पूर्ण;

अटल पूर्णांक td028ttec1_probe_of(काष्ठा spi_device *spi)
अणु
	काष्ठा device_node *node = spi->dev.of_node;
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	काष्ठा omap_dss_device *in;

	in = omapdss_of_find_source_क्रम_first_ep(node);
	अगर (IS_ERR(in)) अणु
		dev_err(&spi->dev, "failed to find video source\n");
		वापस PTR_ERR(in);
	पूर्ण

	ddata->in = in;

	वापस 0;
पूर्ण

अटल पूर्णांक td028ttec1_panel_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata;
	काष्ठा omap_dss_device *dssdev;
	पूर्णांक r;

	dev_dbg(&spi->dev, "%s\n", __func__);

	अगर (!spi->dev.of_node)
		वापस -ENODEV;

	spi->bits_per_word = 9;
	spi->mode = SPI_MODE_3;

	r = spi_setup(spi);
	अगर (r < 0) अणु
		dev_err(&spi->dev, "spi_setup failed: %d\n", r);
		वापस r;
	पूर्ण

	ddata = devm_kzalloc(&spi->dev, माप(*ddata), GFP_KERNEL);
	अगर (ddata == शून्य)
		वापस -ENOMEM;

	dev_set_drvdata(&spi->dev, ddata);

	ddata->spi_dev = spi;

	r = td028ttec1_probe_of(spi);
	अगर (r)
		वापस r;

	ddata->videomode = td028ttec1_panel_timings;

	dssdev = &ddata->dssdev;
	dssdev->dev = &spi->dev;
	dssdev->driver = &td028ttec1_ops;
	dssdev->type = OMAP_DISPLAY_TYPE_DPI;
	dssdev->owner = THIS_MODULE;
	dssdev->panel.timings = ddata->videomode;
	dssdev->phy.dpi.data_lines = ddata->data_lines;

	r = omapdss_रेजिस्टर_display(dssdev);
	अगर (r) अणु
		dev_err(&spi->dev, "Failed to register panel\n");
		जाओ err_reg;
	पूर्ण

	वापस 0;

err_reg:
	omap_dss_put_device(ddata->in);
	वापस r;
पूर्ण

अटल पूर्णांक td028ttec1_panel_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा panel_drv_data *ddata = dev_get_drvdata(&spi->dev);
	काष्ठा omap_dss_device *dssdev = &ddata->dssdev;
	काष्ठा omap_dss_device *in = ddata->in;

	dev_dbg(&ddata->spi_dev->dev, "%s\n", __func__);

	omapdss_unरेजिस्टर_display(dssdev);

	td028ttec1_panel_disable(dssdev);
	td028ttec1_panel_disconnect(dssdev);

	omap_dss_put_device(in);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id td028ttec1_of_match[] = अणु
	अणु .compatible = "omapdss,tpo,td028ttec1", पूर्ण,
	/* keep to not अवरोध older DTB */
	अणु .compatible = "omapdss,toppoly,td028ttec1", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, td028ttec1_of_match);

अटल स्थिर काष्ठा spi_device_id td028ttec1_ids[] = अणु
	अणु "toppoly,td028ttec1", 0 पूर्ण,
	अणु "tpo,td028ttec1", 0पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, td028ttec1_ids);

अटल काष्ठा spi_driver td028ttec1_spi_driver = अणु
	.probe		= td028ttec1_panel_probe,
	.हटाओ		= td028ttec1_panel_हटाओ,
	.id_table	= td028ttec1_ids,

	.driver         = अणु
		.name   = "panel-tpo-td028ttec1",
		.of_match_table = td028ttec1_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;

module_spi_driver(td028ttec1_spi_driver);

MODULE_AUTHOR("H. Nikolaus Schaller <hns@goldelico.com>");
MODULE_DESCRIPTION("Toppoly TD028TTEC1 panel driver");
MODULE_LICENSE("GPL");
