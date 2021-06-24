<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 * datasheet: https://www.ti.com/lit/ds/symlink/sn65dsi86.pdf
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <यंत्र/unaligned.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#घोषणा SN_DEVICE_REV_REG			0x08
#घोषणा SN_DPPLL_SRC_REG			0x0A
#घोषणा  DPPLL_CLK_SRC_DSICLK			BIT(0)
#घोषणा  REFCLK_FREQ_MASK			GENMASK(3, 1)
#घोषणा  REFCLK_FREQ(x)				((x) << 1)
#घोषणा  DPPLL_SRC_DP_PLL_LOCK			BIT(7)
#घोषणा SN_PLL_ENABLE_REG			0x0D
#घोषणा SN_DSI_LANES_REG			0x10
#घोषणा  CHA_DSI_LANES_MASK			GENMASK(4, 3)
#घोषणा  CHA_DSI_LANES(x)			((x) << 3)
#घोषणा SN_DSIA_CLK_FREQ_REG			0x12
#घोषणा SN_CHA_ACTIVE_LINE_LENGTH_LOW_REG	0x20
#घोषणा SN_CHA_VERTICAL_DISPLAY_SIZE_LOW_REG	0x24
#घोषणा SN_CHA_HSYNC_PULSE_WIDTH_LOW_REG	0x2C
#घोषणा SN_CHA_HSYNC_PULSE_WIDTH_HIGH_REG	0x2D
#घोषणा  CHA_HSYNC_POLARITY			BIT(7)
#घोषणा SN_CHA_VSYNC_PULSE_WIDTH_LOW_REG	0x30
#घोषणा SN_CHA_VSYNC_PULSE_WIDTH_HIGH_REG	0x31
#घोषणा  CHA_VSYNC_POLARITY			BIT(7)
#घोषणा SN_CHA_HORIZONTAL_BACK_PORCH_REG	0x34
#घोषणा SN_CHA_VERTICAL_BACK_PORCH_REG		0x36
#घोषणा SN_CHA_HORIZONTAL_FRONT_PORCH_REG	0x38
#घोषणा SN_CHA_VERTICAL_FRONT_PORCH_REG		0x3A
#घोषणा SN_LN_ASSIGN_REG			0x59
#घोषणा  LN_ASSIGN_WIDTH			2
#घोषणा SN_ENH_FRAME_REG			0x5A
#घोषणा  VSTREAM_ENABLE				BIT(3)
#घोषणा  LN_POLRS_OFFSET			4
#घोषणा  LN_POLRS_MASK				0xf0
#घोषणा SN_DATA_FORMAT_REG			0x5B
#घोषणा  BPP_18_RGB				BIT(0)
#घोषणा SN_HPD_DISABLE_REG			0x5C
#घोषणा  HPD_DISABLE				BIT(0)
#घोषणा SN_GPIO_IO_REG				0x5E
#घोषणा  SN_GPIO_INPUT_SHIFT			4
#घोषणा  SN_GPIO_OUTPUT_SHIFT			0
#घोषणा SN_GPIO_CTRL_REG			0x5F
#घोषणा  SN_GPIO_MUX_INPUT			0
#घोषणा  SN_GPIO_MUX_OUTPUT			1
#घोषणा  SN_GPIO_MUX_SPECIAL			2
#घोषणा  SN_GPIO_MUX_MASK			0x3
#घोषणा SN_AUX_WDATA_REG(x)			(0x64 + (x))
#घोषणा SN_AUX_ADDR_19_16_REG			0x74
#घोषणा SN_AUX_ADDR_15_8_REG			0x75
#घोषणा SN_AUX_ADDR_7_0_REG			0x76
#घोषणा SN_AUX_ADDR_MASK			GENMASK(19, 0)
#घोषणा SN_AUX_LENGTH_REG			0x77
#घोषणा SN_AUX_CMD_REG				0x78
#घोषणा  AUX_CMD_SEND				BIT(0)
#घोषणा  AUX_CMD_REQ(x)				((x) << 4)
#घोषणा SN_AUX_RDATA_REG(x)			(0x79 + (x))
#घोषणा SN_SSC_CONFIG_REG			0x93
#घोषणा  DP_NUM_LANES_MASK			GENMASK(5, 4)
#घोषणा  DP_NUM_LANES(x)			((x) << 4)
#घोषणा SN_DATARATE_CONFIG_REG			0x94
#घोषणा  DP_DATARATE_MASK			GENMASK(7, 5)
#घोषणा  DP_DATARATE(x)				((x) << 5)
#घोषणा SN_ML_TX_MODE_REG			0x96
#घोषणा  ML_TX_MAIN_LINK_OFF			0
#घोषणा  ML_TX_NORMAL_MODE			BIT(0)
#घोषणा SN_AUX_CMD_STATUS_REG			0xF4
#घोषणा  AUX_IRQ_STATUS_AUX_RPLY_TOUT		BIT(3)
#घोषणा  AUX_IRQ_STATUS_AUX_SHORT		BIT(5)
#घोषणा  AUX_IRQ_STATUS_NAT_I2C_FAIL		BIT(6)

#घोषणा MIN_DSI_CLK_FREQ_MHZ	40

/* fudge factor required to account क्रम 8b/10b encoding */
#घोषणा DP_CLK_FUDGE_NUM	10
#घोषणा DP_CLK_FUDGE_DEN	8

/* Matches DP_AUX_MAX_PAYLOAD_BYTES (क्रम now) */
#घोषणा SN_AUX_MAX_PAYLOAD_BYTES	16

#घोषणा SN_REGULATOR_SUPPLY_NUM		4

#घोषणा SN_MAX_DP_LANES			4
#घोषणा SN_NUM_GPIOS			4
#घोषणा SN_GPIO_PHYSICAL_OFFSET		1

#घोषणा SN_LINK_TRAINING_TRIES		10

/**
 * काष्ठा ti_sn_bridge - Platक्रमm data क्रम ti-sn65dsi86 driver.
 * @dev:          Poपूर्णांकer to our device.
 * @regmap:       Regmap क्रम accessing i2c.
 * @aux:          Our aux channel.
 * @bridge:       Our bridge.
 * @connector:    Our connector.
 * @debugfs:      Used क्रम managing our debugfs.
 * @host_node:    Remote DSI node.
 * @dsi:          Our MIPI DSI source.
 * @edid:         Detected EDID of eDP panel.
 * @refclk:       Our reference घड़ी.
 * @panel:        Our panel.
 * @enable_gpio:  The GPIO we toggle to enable the bridge.
 * @supplies:     Data क्रम bulk enabling/disabling our regulators.
 * @dp_lanes:     Count of dp_lanes we're using.
 * @ln_assign:    Value to program to the LN_ASSIGN रेजिस्टर.
 * @ln_polrs:     Value क्रम the 4-bit LN_POLRS field of SN_ENH_FRAME_REG.
 *
 * @gchip:        If we expose our GPIOs, this is used.
 * @gchip_output: A cache of whether we've set GPIOs to output.  This
 *                serves द्विगुन-duty of keeping track of the direction and
 *                also keeping track of whether we've incremented the
 *                pm_runसमय reference count क्रम this pin, which we करो
 *                whenever a pin is configured as an output.  This is a
 *                biपंचांगap so we can करो atomic ops on it without an extra
 *                lock so concurrent users of our 4 GPIOs करोn't stomp on
 *                each other's पढ़ो-modअगरy-ग_लिखो.
 */
काष्ठा ti_sn_bridge अणु
	काष्ठा device			*dev;
	काष्ठा regmap			*regmap;
	काष्ठा drm_dp_aux		aux;
	काष्ठा drm_bridge		bridge;
	काष्ठा drm_connector		connector;
	काष्ठा dentry			*debugfs;
	काष्ठा edid			*edid;
	काष्ठा device_node		*host_node;
	काष्ठा mipi_dsi_device		*dsi;
	काष्ठा clk			*refclk;
	काष्ठा drm_panel		*panel;
	काष्ठा gpio_desc		*enable_gpio;
	काष्ठा regulator_bulk_data	supplies[SN_REGULATOR_SUPPLY_NUM];
	पूर्णांक				dp_lanes;
	u8				ln_assign;
	u8				ln_polrs;

#अगर defined(CONFIG_OF_GPIO)
	काष्ठा gpio_chip		gchip;
	DECLARE_BITMAP(gchip_output, SN_NUM_GPIOS);
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा regmap_range ti_sn_bridge_अस्थिर_ranges[] = अणु
	अणु .range_min = 0, .range_max = 0xFF पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table ti_sn_bridge_अस्थिर_table = अणु
	.yes_ranges = ti_sn_bridge_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(ti_sn_bridge_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config ti_sn_bridge_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_table = &ti_sn_bridge_अस्थिर_table,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल व्योम ti_sn_bridge_ग_लिखो_u16(काष्ठा ti_sn_bridge *pdata,
				   अचिन्हित पूर्णांक reg, u16 val)
अणु
	regmap_ग_लिखो(pdata->regmap, reg, val & 0xFF);
	regmap_ग_लिखो(pdata->regmap, reg + 1, val >> 8);
पूर्ण

अटल पूर्णांक __maybe_unused ti_sn_bridge_resume(काष्ठा device *dev)
अणु
	काष्ठा ti_sn_bridge *pdata = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(SN_REGULATOR_SUPPLY_NUM, pdata->supplies);
	अगर (ret) अणु
		DRM_ERROR("failed to enable supplies %d\n", ret);
		वापस ret;
	पूर्ण

	gpiod_set_value(pdata->enable_gpio, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ti_sn_bridge_suspend(काष्ठा device *dev)
अणु
	काष्ठा ti_sn_bridge *pdata = dev_get_drvdata(dev);
	पूर्णांक ret;

	gpiod_set_value(pdata->enable_gpio, 0);

	ret = regulator_bulk_disable(SN_REGULATOR_SUPPLY_NUM, pdata->supplies);
	अगर (ret)
		DRM_ERROR("failed to disable supplies %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ti_sn_bridge_pm_ops = अणु
	SET_RUNTIME_PM_OPS(ti_sn_bridge_suspend, ti_sn_bridge_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल पूर्णांक status_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा ti_sn_bridge *pdata = s->निजी;
	अचिन्हित पूर्णांक reg, val;

	seq_माला_दो(s, "STATUS REGISTERS:\n");

	pm_runसमय_get_sync(pdata->dev);

	/* IRQ Status Registers, see Table 31 in datasheet */
	क्रम (reg = 0xf0; reg <= 0xf8; reg++) अणु
		regmap_पढ़ो(pdata->regmap, reg, &val);
		seq_म_लिखो(s, "[0x%02x] = 0x%08x\n", reg, val);
	पूर्ण

	pm_runसमय_put(pdata->dev);

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(status);

अटल व्योम ti_sn_debugfs_init(काष्ठा ti_sn_bridge *pdata)
अणु
	pdata->debugfs = debugfs_create_dir(dev_name(pdata->dev), शून्य);

	debugfs_create_file("status", 0600, pdata->debugfs, pdata,
			&status_fops);
पूर्ण

अटल व्योम ti_sn_debugfs_हटाओ(काष्ठा ti_sn_bridge *pdata)
अणु
	debugfs_हटाओ_recursive(pdata->debugfs);
	pdata->debugfs = शून्य;
पूर्ण

/* Connector funcs */
अटल काष्ठा ti_sn_bridge *
connector_to_ti_sn_bridge(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा ti_sn_bridge, connector);
पूर्ण

अटल पूर्णांक ti_sn_bridge_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा ti_sn_bridge *pdata = connector_to_ti_sn_bridge(connector);
	काष्ठा edid *edid = pdata->edid;
	पूर्णांक num, ret;

	अगर (!edid) अणु
		pm_runसमय_get_sync(pdata->dev);
		edid = pdata->edid = drm_get_edid(connector, &pdata->aux.ddc);
		pm_runसमय_put(pdata->dev);
	पूर्ण

	अगर (edid && drm_edid_is_valid(edid)) अणु
		ret = drm_connector_update_edid_property(connector, edid);
		अगर (!ret) अणु
			num = drm_add_edid_modes(connector, edid);
			अगर (num)
				वापस num;
		पूर्ण
	पूर्ण

	वापस drm_panel_get_modes(pdata->panel, connector);
पूर्ण

अटल क्रमागत drm_mode_status
ti_sn_bridge_connector_mode_valid(काष्ठा drm_connector *connector,
				  काष्ठा drm_display_mode *mode)
अणु
	/* maximum supported resolution is 4K at 60 fps */
	अगर (mode->घड़ी > 594000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल काष्ठा drm_connector_helper_funcs ti_sn_bridge_connector_helper_funcs = अणु
	.get_modes = ti_sn_bridge_connector_get_modes,
	.mode_valid = ti_sn_bridge_connector_mode_valid,
पूर्ण;

अटल क्रमागत drm_connector_status
ti_sn_bridge_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	/**
	 * TODO: Currently अगर drm_panel is present, then always
	 * वापस the status as connected. Need to add support to detect
	 * device state क्रम hot pluggable scenarios.
	 */
	वापस connector_status_connected;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs ti_sn_bridge_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = ti_sn_bridge_connector_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल काष्ठा ti_sn_bridge *bridge_to_ti_sn_bridge(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा ti_sn_bridge, bridge);
पूर्ण

अटल पूर्णांक ti_sn_bridge_parse_regulators(काष्ठा ti_sn_bridge *pdata)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर अक्षर * स्थिर ti_sn_bridge_supply_names[] = अणु
		"vcca", "vcc", "vccio", "vpll",
	पूर्ण;

	क्रम (i = 0; i < SN_REGULATOR_SUPPLY_NUM; i++)
		pdata->supplies[i].supply = ti_sn_bridge_supply_names[i];

	वापस devm_regulator_bulk_get(pdata->dev, SN_REGULATOR_SUPPLY_NUM,
				       pdata->supplies);
पूर्ण

अटल पूर्णांक ti_sn_bridge_attach(काष्ठा drm_bridge *bridge,
			       क्रमागत drm_bridge_attach_flags flags)
अणु
	पूर्णांक ret, val;
	काष्ठा ti_sn_bridge *pdata = bridge_to_ti_sn_bridge(bridge);
	काष्ठा mipi_dsi_host *host;
	काष्ठा mipi_dsi_device *dsi;
	स्थिर काष्ठा mipi_dsi_device_info info = अणु .type = "ti_sn_bridge",
						   .channel = 0,
						   .node = शून्य,
						 पूर्ण;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR) अणु
		DRM_ERROR("Fix bridge driver to make connector optional!");
		वापस -EINVAL;
	पूर्ण

	ret = drm_dp_aux_रेजिस्टर(&pdata->aux);
	अगर (ret < 0) अणु
		drm_err(bridge->dev, "Failed to register DP AUX channel: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = drm_connector_init(bridge->dev, &pdata->connector,
				 &ti_sn_bridge_connector_funcs,
				 DRM_MODE_CONNECTOR_eDP);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector with drm\n");
		जाओ err_conn_init;
	पूर्ण

	drm_connector_helper_add(&pdata->connector,
				 &ti_sn_bridge_connector_helper_funcs);
	drm_connector_attach_encoder(&pdata->connector, bridge->encoder);

	/*
	 * TODO: ideally finding host resource and dsi dev registration needs
	 * to be करोne in bridge probe. But some existing DSI host drivers will
	 * रुको क्रम any of the drm_bridge/drm_panel to get added to the global
	 * bridge/panel list, beक्रमe completing their probe. So अगर we करो the
	 * dsi dev registration part in bridge probe, beक्रमe populating in
	 * the global bridge list, then it will cause deadlock as dsi host probe
	 * will never complete, neither our bridge probe. So keeping it here
	 * will satisfy most of the existing host drivers. Once the host driver
	 * is fixed we can move the below code to bridge probe safely.
	 */
	host = of_find_mipi_dsi_host_by_node(pdata->host_node);
	अगर (!host) अणु
		DRM_ERROR("failed to find dsi host\n");
		ret = -ENODEV;
		जाओ err_dsi_host;
	पूर्ण

	dsi = mipi_dsi_device_रेजिस्टर_full(host, &info);
	अगर (IS_ERR(dsi)) अणु
		DRM_ERROR("failed to create dsi device\n");
		ret = PTR_ERR(dsi);
		जाओ err_dsi_host;
	पूर्ण

	/* TODO: setting to 4 MIPI lanes always क्रम now */
	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO;

	/* check अगर continuous dsi घड़ी is required or not */
	pm_runसमय_get_sync(pdata->dev);
	regmap_पढ़ो(pdata->regmap, SN_DPPLL_SRC_REG, &val);
	pm_runसमय_put(pdata->dev);
	अगर (!(val & DPPLL_CLK_SRC_DSICLK))
		dsi->mode_flags |= MIPI_DSI_CLOCK_NON_CONTINUOUS;

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to attach dsi to host\n");
		जाओ err_dsi_attach;
	पूर्ण
	pdata->dsi = dsi;

	वापस 0;

err_dsi_attach:
	mipi_dsi_device_unरेजिस्टर(dsi);
err_dsi_host:
	drm_connector_cleanup(&pdata->connector);
err_conn_init:
	drm_dp_aux_unरेजिस्टर(&pdata->aux);
	वापस ret;
पूर्ण

अटल व्योम ti_sn_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	drm_dp_aux_unरेजिस्टर(&bridge_to_ti_sn_bridge(bridge)->aux);
पूर्ण

अटल व्योम ti_sn_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ti_sn_bridge *pdata = bridge_to_ti_sn_bridge(bridge);

	drm_panel_disable(pdata->panel);

	/* disable video stream */
	regmap_update_bits(pdata->regmap, SN_ENH_FRAME_REG, VSTREAM_ENABLE, 0);
	/* semi स्वतः link training mode OFF */
	regmap_ग_लिखो(pdata->regmap, SN_ML_TX_MODE_REG, 0);
	/* disable DP PLL */
	regmap_ग_लिखो(pdata->regmap, SN_PLL_ENABLE_REG, 0);

	drm_panel_unprepare(pdata->panel);
पूर्ण

अटल u32 ti_sn_bridge_get_dsi_freq(काष्ठा ti_sn_bridge *pdata)
अणु
	u32 bit_rate_khz, clk_freq_khz;
	काष्ठा drm_display_mode *mode =
		&pdata->bridge.encoder->crtc->state->adjusted_mode;

	bit_rate_khz = mode->घड़ी *
			mipi_dsi_pixel_क्रमmat_to_bpp(pdata->dsi->क्रमmat);
	clk_freq_khz = bit_rate_khz / (pdata->dsi->lanes * 2);

	वापस clk_freq_khz;
पूर्ण

/* clk frequencies supported by bridge in Hz in हाल derived from REFCLK pin */
अटल स्थिर u32 ti_sn_bridge_refclk_lut[] = अणु
	12000000,
	19200000,
	26000000,
	27000000,
	38400000,
पूर्ण;

/* clk frequencies supported by bridge in Hz in हाल derived from DACP/N pin */
अटल स्थिर u32 ti_sn_bridge_dsiclk_lut[] = अणु
	468000000,
	384000000,
	416000000,
	486000000,
	460800000,
पूर्ण;

अटल व्योम ti_sn_bridge_set_refclk_freq(काष्ठा ti_sn_bridge *pdata)
अणु
	पूर्णांक i;
	u32 refclk_rate;
	स्थिर u32 *refclk_lut;
	माप_प्रकार refclk_lut_size;

	अगर (pdata->refclk) अणु
		refclk_rate = clk_get_rate(pdata->refclk);
		refclk_lut = ti_sn_bridge_refclk_lut;
		refclk_lut_size = ARRAY_SIZE(ti_sn_bridge_refclk_lut);
		clk_prepare_enable(pdata->refclk);
	पूर्ण अन्यथा अणु
		refclk_rate = ti_sn_bridge_get_dsi_freq(pdata) * 1000;
		refclk_lut = ti_sn_bridge_dsiclk_lut;
		refclk_lut_size = ARRAY_SIZE(ti_sn_bridge_dsiclk_lut);
	पूर्ण

	/* क्रम i equals to refclk_lut_size means शेष frequency */
	क्रम (i = 0; i < refclk_lut_size; i++)
		अगर (refclk_lut[i] == refclk_rate)
			अवरोध;

	regmap_update_bits(pdata->regmap, SN_DPPLL_SRC_REG, REFCLK_FREQ_MASK,
			   REFCLK_FREQ(i));
पूर्ण

अटल व्योम ti_sn_bridge_set_dsi_rate(काष्ठा ti_sn_bridge *pdata)
अणु
	अचिन्हित पूर्णांक bit_rate_mhz, clk_freq_mhz;
	अचिन्हित पूर्णांक val;
	काष्ठा drm_display_mode *mode =
		&pdata->bridge.encoder->crtc->state->adjusted_mode;

	/* set DSIA clk frequency */
	bit_rate_mhz = (mode->घड़ी / 1000) *
			mipi_dsi_pixel_क्रमmat_to_bpp(pdata->dsi->क्रमmat);
	clk_freq_mhz = bit_rate_mhz / (pdata->dsi->lanes * 2);

	/* क्रम each increment in val, frequency increases by 5MHz */
	val = (MIN_DSI_CLK_FREQ_MHZ / 5) +
		(((clk_freq_mhz - MIN_DSI_CLK_FREQ_MHZ) / 5) & 0xFF);
	regmap_ग_लिखो(pdata->regmap, SN_DSIA_CLK_FREQ_REG, val);
पूर्ण

अटल अचिन्हित पूर्णांक ti_sn_bridge_get_bpp(काष्ठा ti_sn_bridge *pdata)
अणु
	अगर (pdata->connector.display_info.bpc <= 6)
		वापस 18;
	अन्यथा
		वापस 24;
पूर्ण

/*
 * LUT index corresponds to रेजिस्टर value and
 * LUT values corresponds to dp data rate supported
 * by the bridge in Mbps unit.
 */
अटल स्थिर अचिन्हित पूर्णांक ti_sn_bridge_dp_rate_lut[] = अणु
	0, 1620, 2160, 2430, 2700, 3240, 4320, 5400
पूर्ण;

अटल पूर्णांक ti_sn_bridge_calc_min_dp_rate_idx(काष्ठा ti_sn_bridge *pdata)
अणु
	अचिन्हित पूर्णांक bit_rate_khz, dp_rate_mhz;
	अचिन्हित पूर्णांक i;
	काष्ठा drm_display_mode *mode =
		&pdata->bridge.encoder->crtc->state->adjusted_mode;

	/* Calculate minimum bit rate based on our pixel घड़ी. */
	bit_rate_khz = mode->घड़ी * ti_sn_bridge_get_bpp(pdata);

	/* Calculate minimum DP data rate, taking 80% as per DP spec */
	dp_rate_mhz = DIV_ROUND_UP(bit_rate_khz * DP_CLK_FUDGE_NUM,
				   1000 * pdata->dp_lanes * DP_CLK_FUDGE_DEN);

	क्रम (i = 1; i < ARRAY_SIZE(ti_sn_bridge_dp_rate_lut) - 1; i++)
		अगर (ti_sn_bridge_dp_rate_lut[i] >= dp_rate_mhz)
			अवरोध;

	वापस i;
पूर्ण

अटल व्योम ti_sn_bridge_पढ़ो_valid_rates(काष्ठा ti_sn_bridge *pdata,
					  bool rate_valid[])
अणु
	अचिन्हित पूर्णांक rate_per_200khz;
	अचिन्हित पूर्णांक rate_mhz;
	u8 dpcd_val;
	पूर्णांक ret;
	पूर्णांक i, j;

	ret = drm_dp_dpcd_पढ़ोb(&pdata->aux, DP_EDP_DPCD_REV, &dpcd_val);
	अगर (ret != 1) अणु
		DRM_DEV_ERROR(pdata->dev,
			      "Can't read eDP rev (%d), assuming 1.1\n", ret);
		dpcd_val = DP_EDP_11;
	पूर्ण

	अगर (dpcd_val >= DP_EDP_14) अणु
		/* eDP 1.4 devices must provide a custom table */
		__le16 sink_rates[DP_MAX_SUPPORTED_RATES];

		ret = drm_dp_dpcd_पढ़ो(&pdata->aux, DP_SUPPORTED_LINK_RATES,
				       sink_rates, माप(sink_rates));

		अगर (ret != माप(sink_rates)) अणु
			DRM_DEV_ERROR(pdata->dev,
				"Can't read supported rate table (%d)\n", ret);

			/* By zeroing we'll fall back to DP_MAX_LINK_RATE. */
			स_रखो(sink_rates, 0, माप(sink_rates));
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(sink_rates); i++) अणु
			rate_per_200khz = le16_to_cpu(sink_rates[i]);

			अगर (!rate_per_200khz)
				अवरोध;

			rate_mhz = rate_per_200khz * 200 / 1000;
			क्रम (j = 0;
			     j < ARRAY_SIZE(ti_sn_bridge_dp_rate_lut);
			     j++) अणु
				अगर (ti_sn_bridge_dp_rate_lut[j] == rate_mhz)
					rate_valid[j] = true;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(ti_sn_bridge_dp_rate_lut); i++) अणु
			अगर (rate_valid[i])
				वापस;
		पूर्ण
		DRM_DEV_ERROR(pdata->dev,
			      "No matching eDP rates in table; falling back\n");
	पूर्ण

	/* On older versions best we can करो is use DP_MAX_LINK_RATE */
	ret = drm_dp_dpcd_पढ़ोb(&pdata->aux, DP_MAX_LINK_RATE, &dpcd_val);
	अगर (ret != 1) अणु
		DRM_DEV_ERROR(pdata->dev,
			      "Can't read max rate (%d); assuming 5.4 GHz\n",
			      ret);
		dpcd_val = DP_LINK_BW_5_4;
	पूर्ण

	चयन (dpcd_val) अणु
	शेष:
		DRM_DEV_ERROR(pdata->dev,
			      "Unexpected max rate (%#x); assuming 5.4 GHz\n",
			      (पूर्णांक)dpcd_val);
		fallthrough;
	हाल DP_LINK_BW_5_4:
		rate_valid[7] = 1;
		fallthrough;
	हाल DP_LINK_BW_2_7:
		rate_valid[4] = 1;
		fallthrough;
	हाल DP_LINK_BW_1_62:
		rate_valid[1] = 1;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ti_sn_bridge_set_video_timings(काष्ठा ti_sn_bridge *pdata)
अणु
	काष्ठा drm_display_mode *mode =
		&pdata->bridge.encoder->crtc->state->adjusted_mode;
	u8 hsync_polarity = 0, vsync_polarity = 0;

	अगर (mode->flags & DRM_MODE_FLAG_PHSYNC)
		hsync_polarity = CHA_HSYNC_POLARITY;
	अगर (mode->flags & DRM_MODE_FLAG_PVSYNC)
		vsync_polarity = CHA_VSYNC_POLARITY;

	ti_sn_bridge_ग_लिखो_u16(pdata, SN_CHA_ACTIVE_LINE_LENGTH_LOW_REG,
			       mode->hdisplay);
	ti_sn_bridge_ग_लिखो_u16(pdata, SN_CHA_VERTICAL_DISPLAY_SIZE_LOW_REG,
			       mode->vdisplay);
	regmap_ग_लिखो(pdata->regmap, SN_CHA_HSYNC_PULSE_WIDTH_LOW_REG,
		     (mode->hsync_end - mode->hsync_start) & 0xFF);
	regmap_ग_लिखो(pdata->regmap, SN_CHA_HSYNC_PULSE_WIDTH_HIGH_REG,
		     (((mode->hsync_end - mode->hsync_start) >> 8) & 0x7F) |
		     hsync_polarity);
	regmap_ग_लिखो(pdata->regmap, SN_CHA_VSYNC_PULSE_WIDTH_LOW_REG,
		     (mode->vsync_end - mode->vsync_start) & 0xFF);
	regmap_ग_लिखो(pdata->regmap, SN_CHA_VSYNC_PULSE_WIDTH_HIGH_REG,
		     (((mode->vsync_end - mode->vsync_start) >> 8) & 0x7F) |
		     vsync_polarity);

	regmap_ग_लिखो(pdata->regmap, SN_CHA_HORIZONTAL_BACK_PORCH_REG,
		     (mode->htotal - mode->hsync_end) & 0xFF);
	regmap_ग_लिखो(pdata->regmap, SN_CHA_VERTICAL_BACK_PORCH_REG,
		     (mode->vtotal - mode->vsync_end) & 0xFF);

	regmap_ग_लिखो(pdata->regmap, SN_CHA_HORIZONTAL_FRONT_PORCH_REG,
		     (mode->hsync_start - mode->hdisplay) & 0xFF);
	regmap_ग_लिखो(pdata->regmap, SN_CHA_VERTICAL_FRONT_PORCH_REG,
		     (mode->vsync_start - mode->vdisplay) & 0xFF);

	usleep_range(10000, 10500); /* 10ms delay recommended by spec */
पूर्ण

अटल अचिन्हित पूर्णांक ti_sn_get_max_lanes(काष्ठा ti_sn_bridge *pdata)
अणु
	u8 data;
	पूर्णांक ret;

	ret = drm_dp_dpcd_पढ़ोb(&pdata->aux, DP_MAX_LANE_COUNT, &data);
	अगर (ret != 1) अणु
		DRM_DEV_ERROR(pdata->dev,
			      "Can't read lane count (%d); assuming 4\n", ret);
		वापस 4;
	पूर्ण

	वापस data & DP_LANE_COUNT_MASK;
पूर्ण

अटल पूर्णांक ti_sn_link_training(काष्ठा ti_sn_bridge *pdata, पूर्णांक dp_rate_idx,
			       स्थिर अक्षर **last_err_str)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	पूर्णांक i;

	/* set dp clk frequency value */
	regmap_update_bits(pdata->regmap, SN_DATARATE_CONFIG_REG,
			   DP_DATARATE_MASK, DP_DATARATE(dp_rate_idx));

	/* enable DP PLL */
	regmap_ग_लिखो(pdata->regmap, SN_PLL_ENABLE_REG, 1);

	ret = regmap_पढ़ो_poll_समयout(pdata->regmap, SN_DPPLL_SRC_REG, val,
				       val & DPPLL_SRC_DP_PLL_LOCK, 1000,
				       50 * 1000);
	अगर (ret) अणु
		*last_err_str = "DP_PLL_LOCK polling failed";
		जाओ निकास;
	पूर्ण

	/*
	 * We'll try to link train several बार.  As part of link training
	 * the bridge chip will ग_लिखो DP_SET_POWER_D0 to DP_SET_POWER.  If
	 * the panel isn't पढ़ोy quite it might respond NAK here which means
	 * we need to try again.
	 */
	क्रम (i = 0; i < SN_LINK_TRAINING_TRIES; i++) अणु
		/* Semi स्वतः link training mode */
		regmap_ग_लिखो(pdata->regmap, SN_ML_TX_MODE_REG, 0x0A);
		ret = regmap_पढ़ो_poll_समयout(pdata->regmap, SN_ML_TX_MODE_REG, val,
					       val == ML_TX_MAIN_LINK_OFF ||
					       val == ML_TX_NORMAL_MODE, 1000,
					       500 * 1000);
		अगर (ret) अणु
			*last_err_str = "Training complete polling failed";
		पूर्ण अन्यथा अगर (val == ML_TX_MAIN_LINK_OFF) अणु
			*last_err_str = "Link training failed, link is off";
			ret = -EIO;
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण

	/* If we saw quite a few retries, add a note about it */
	अगर (!ret && i > SN_LINK_TRAINING_TRIES / 2)
		DRM_DEV_INFO(pdata->dev, "Link training needed %d retries\n", i);

निकास:
	/* Disable the PLL अगर we failed */
	अगर (ret)
		regmap_ग_लिखो(pdata->regmap, SN_PLL_ENABLE_REG, 0);

	वापस ret;
पूर्ण

अटल व्योम ti_sn_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ti_sn_bridge *pdata = bridge_to_ti_sn_bridge(bridge);
	bool rate_valid[ARRAY_SIZE(ti_sn_bridge_dp_rate_lut)] = अणु पूर्ण;
	स्थिर अक्षर *last_err_str = "No supported DP rate";
	पूर्णांक dp_rate_idx;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = -EINVAL;
	पूर्णांक max_dp_lanes;

	max_dp_lanes = ti_sn_get_max_lanes(pdata);
	pdata->dp_lanes = min(pdata->dp_lanes, max_dp_lanes);

	/* DSI_A lane config */
	val = CHA_DSI_LANES(SN_MAX_DP_LANES - pdata->dsi->lanes);
	regmap_update_bits(pdata->regmap, SN_DSI_LANES_REG,
			   CHA_DSI_LANES_MASK, val);

	regmap_ग_लिखो(pdata->regmap, SN_LN_ASSIGN_REG, pdata->ln_assign);
	regmap_update_bits(pdata->regmap, SN_ENH_FRAME_REG, LN_POLRS_MASK,
			   pdata->ln_polrs << LN_POLRS_OFFSET);

	/* set dsi clk frequency value */
	ti_sn_bridge_set_dsi_rate(pdata);

	/**
	 * The SN65DSI86 only supports ASSR Display Authentication method and
	 * this method is enabled by शेष. An eDP panel must support this
	 * authentication method. We need to enable this method in the eDP panel
	 * at DisplayPort address 0x0010A prior to link training.
	 */
	drm_dp_dpcd_ग_लिखोb(&pdata->aux, DP_EDP_CONFIGURATION_SET,
			   DP_ALTERNATE_SCRAMBLER_RESET_ENABLE);

	/* Set the DP output क्रमmat (18 bpp or 24 bpp) */
	val = (ti_sn_bridge_get_bpp(pdata) == 18) ? BPP_18_RGB : 0;
	regmap_update_bits(pdata->regmap, SN_DATA_FORMAT_REG, BPP_18_RGB, val);

	/* DP lane config */
	val = DP_NUM_LANES(min(pdata->dp_lanes, 3));
	regmap_update_bits(pdata->regmap, SN_SSC_CONFIG_REG, DP_NUM_LANES_MASK,
			   val);

	ti_sn_bridge_पढ़ो_valid_rates(pdata, rate_valid);

	/* Train until we run out of rates */
	क्रम (dp_rate_idx = ti_sn_bridge_calc_min_dp_rate_idx(pdata);
	     dp_rate_idx < ARRAY_SIZE(ti_sn_bridge_dp_rate_lut);
	     dp_rate_idx++) अणु
		अगर (!rate_valid[dp_rate_idx])
			जारी;

		ret = ti_sn_link_training(pdata, dp_rate_idx, &last_err_str);
		अगर (!ret)
			अवरोध;
	पूर्ण
	अगर (ret) अणु
		DRM_DEV_ERROR(pdata->dev, "%s (%d)\n", last_err_str, ret);
		वापस;
	पूर्ण

	/* config video parameters */
	ti_sn_bridge_set_video_timings(pdata);

	/* enable video stream */
	regmap_update_bits(pdata->regmap, SN_ENH_FRAME_REG, VSTREAM_ENABLE,
			   VSTREAM_ENABLE);

	drm_panel_enable(pdata->panel);
पूर्ण

अटल व्योम ti_sn_bridge_pre_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ti_sn_bridge *pdata = bridge_to_ti_sn_bridge(bridge);

	pm_runसमय_get_sync(pdata->dev);

	/* configure bridge ref_clk */
	ti_sn_bridge_set_refclk_freq(pdata);

	/*
	 * HPD on this bridge chip is a bit useless.  This is an eDP bridge
	 * so the HPD is an पूर्णांकernal संकेत that's only there to संकेत that
	 * the panel is करोne घातering up.  ...but the bridge chip debounces
	 * this संकेत by between 100 ms and 400 ms (depending on process,
	 * voltage, and temperate--I measured it at about 200 ms).  One
	 * particular panel निश्चितed HPD 84 ms after it was घातered on meaning
	 * that we saw HPD 284 ms after घातer on.  ...but the same panel said
	 * that instead of looking at HPD you could just hardcode a delay of
	 * 200 ms.  We'll assume that the panel driver will have the hardcoded
	 * delay in its prepare and always disable HPD.
	 *
	 * If HPD somehow makes sense on some future panel we'll have to
	 * change this to be conditional on someone specअगरying that HPD should
	 * be used.
	 */
	regmap_update_bits(pdata->regmap, SN_HPD_DISABLE_REG, HPD_DISABLE,
			   HPD_DISABLE);

	drm_panel_prepare(pdata->panel);
पूर्ण

अटल व्योम ti_sn_bridge_post_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा ti_sn_bridge *pdata = bridge_to_ti_sn_bridge(bridge);

	clk_disable_unprepare(pdata->refclk);

	pm_runसमय_put_sync(pdata->dev);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs ti_sn_bridge_funcs = अणु
	.attach = ti_sn_bridge_attach,
	.detach = ti_sn_bridge_detach,
	.pre_enable = ti_sn_bridge_pre_enable,
	.enable = ti_sn_bridge_enable,
	.disable = ti_sn_bridge_disable,
	.post_disable = ti_sn_bridge_post_disable,
पूर्ण;

अटल काष्ठा ti_sn_bridge *aux_to_ti_sn_bridge(काष्ठा drm_dp_aux *aux)
अणु
	वापस container_of(aux, काष्ठा ti_sn_bridge, aux);
पूर्ण

अटल sमाप_प्रकार ti_sn_aux_transfer(काष्ठा drm_dp_aux *aux,
				  काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा ti_sn_bridge *pdata = aux_to_ti_sn_bridge(aux);
	u32 request = msg->request & ~(DP_AUX_I2C_MOT | DP_AUX_I2C_WRITE_STATUS_UPDATE);
	u32 request_val = AUX_CMD_REQ(msg->request);
	u8 *buf = msg->buffer;
	अचिन्हित पूर्णांक len = msg->size;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	u8 addr_len[SN_AUX_LENGTH_REG + 1 - SN_AUX_ADDR_19_16_REG];

	अगर (len > SN_AUX_MAX_PAYLOAD_BYTES)
		वापस -EINVAL;

	चयन (request) अणु
	हाल DP_AUX_NATIVE_WRITE:
	हाल DP_AUX_I2C_WRITE:
	हाल DP_AUX_NATIVE_READ:
	हाल DP_AUX_I2C_READ:
		regmap_ग_लिखो(pdata->regmap, SN_AUX_CMD_REG, request_val);
		/* Assume it's good */
		msg->reply = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(माप(addr_len) != माप(__be32));
	put_unaligned_be32((msg->address & SN_AUX_ADDR_MASK) << 8 | len,
			   addr_len);
	regmap_bulk_ग_लिखो(pdata->regmap, SN_AUX_ADDR_19_16_REG, addr_len,
			  ARRAY_SIZE(addr_len));

	अगर (request == DP_AUX_NATIVE_WRITE || request == DP_AUX_I2C_WRITE)
		regmap_bulk_ग_लिखो(pdata->regmap, SN_AUX_WDATA_REG(0), buf, len);

	/* Clear old status bits beक्रमe start so we करोn't get confused */
	regmap_ग_लिखो(pdata->regmap, SN_AUX_CMD_STATUS_REG,
		     AUX_IRQ_STATUS_NAT_I2C_FAIL |
		     AUX_IRQ_STATUS_AUX_RPLY_TOUT |
		     AUX_IRQ_STATUS_AUX_SHORT);

	regmap_ग_लिखो(pdata->regmap, SN_AUX_CMD_REG, request_val | AUX_CMD_SEND);

	/* Zero delay loop because i2c transactions are slow alपढ़ोy */
	ret = regmap_पढ़ो_poll_समयout(pdata->regmap, SN_AUX_CMD_REG, val,
				       !(val & AUX_CMD_SEND), 0, 50 * 1000);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(pdata->regmap, SN_AUX_CMD_STATUS_REG, &val);
	अगर (ret)
		वापस ret;

	अगर (val & AUX_IRQ_STATUS_AUX_RPLY_TOUT) अणु
		/*
		 * The hardware tried the message seven बार per the DP spec
		 * but it hit a समयout. We ignore defers here because they're
		 * handled in hardware.
		 */
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (val & AUX_IRQ_STATUS_AUX_SHORT) अणु
		ret = regmap_पढ़ो(pdata->regmap, SN_AUX_LENGTH_REG, &len);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (val & AUX_IRQ_STATUS_NAT_I2C_FAIL) अणु
		चयन (request) अणु
		हाल DP_AUX_I2C_WRITE:
		हाल DP_AUX_I2C_READ:
			msg->reply |= DP_AUX_I2C_REPLY_NACK;
			अवरोध;
		हाल DP_AUX_NATIVE_READ:
		हाल DP_AUX_NATIVE_WRITE:
			msg->reply |= DP_AUX_NATIVE_REPLY_NACK;
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (request == DP_AUX_NATIVE_WRITE || request == DP_AUX_I2C_WRITE ||
	    len == 0)
		वापस len;

	ret = regmap_bulk_पढ़ो(pdata->regmap, SN_AUX_RDATA_REG(0), buf, len);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल पूर्णांक ti_sn_bridge_parse_dsi_host(काष्ठा ti_sn_bridge *pdata)
अणु
	काष्ठा device_node *np = pdata->dev->of_node;

	pdata->host_node = of_graph_get_remote_node(np, 0, 0);

	अगर (!pdata->host_node) अणु
		DRM_ERROR("remote dsi host node not found\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

#अगर defined(CONFIG_OF_GPIO)

अटल पूर्णांक tn_sn_bridge_of_xlate(काष्ठा gpio_chip *chip,
				 स्थिर काष्ठा of_phandle_args *gpiospec,
				 u32 *flags)
अणु
	अगर (WARN_ON(gpiospec->args_count < chip->of_gpio_n_cells))
		वापस -EINVAL;

	अगर (gpiospec->args[0] > chip->ngpio || gpiospec->args[0] < 1)
		वापस -EINVAL;

	अगर (flags)
		*flags = gpiospec->args[1];

	वापस gpiospec->args[0] - SN_GPIO_PHYSICAL_OFFSET;
पूर्ण

अटल पूर्णांक ti_sn_bridge_gpio_get_direction(काष्ठा gpio_chip *chip,
					   अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ti_sn_bridge *pdata = gpiochip_get_data(chip);

	/*
	 * We alपढ़ोy have to keep track of the direction because we use
	 * that to figure out whether we've घातered the device.  We can
	 * just वापस that rather than (maybe) घातering up the device
	 * to ask its direction.
	 */
	वापस test_bit(offset, pdata->gchip_output) ?
		GPIO_LINE_सूचीECTION_OUT : GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक ti_sn_bridge_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ti_sn_bridge *pdata = gpiochip_get_data(chip);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/*
	 * When the pin is an input we करोn't क्रमcibly keep the bridge
	 * घातered--we just घातer it on to पढ़ो the pin.  NOTE: part of
	 * the reason this works is that the bridge शेषs (when
	 * घातered back on) to all 4 GPIOs being configured as GPIO input.
	 * Also note that अगर something अन्यथा is keeping the chip घातered the
	 * pm_runसमय functions are lightweight increments of a refcount.
	 */
	pm_runसमय_get_sync(pdata->dev);
	ret = regmap_पढ़ो(pdata->regmap, SN_GPIO_IO_REG, &val);
	pm_runसमय_put(pdata->dev);

	अगर (ret)
		वापस ret;

	वापस !!(val & BIT(SN_GPIO_INPUT_SHIFT + offset));
पूर्ण

अटल व्योम ti_sn_bridge_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				  पूर्णांक val)
अणु
	काष्ठा ti_sn_bridge *pdata = gpiochip_get_data(chip);
	पूर्णांक ret;

	अगर (!test_bit(offset, pdata->gchip_output)) अणु
		dev_err(pdata->dev, "Ignoring GPIO set while input\n");
		वापस;
	पूर्ण

	val &= 1;
	ret = regmap_update_bits(pdata->regmap, SN_GPIO_IO_REG,
				 BIT(SN_GPIO_OUTPUT_SHIFT + offset),
				 val << (SN_GPIO_OUTPUT_SHIFT + offset));
	अगर (ret)
		dev_warn(pdata->dev,
			 "Failed to set bridge GPIO %u: %d\n", offset, ret);
पूर्ण

अटल पूर्णांक ti_sn_bridge_gpio_direction_input(काष्ठा gpio_chip *chip,
					     अचिन्हित पूर्णांक offset)
अणु
	काष्ठा ti_sn_bridge *pdata = gpiochip_get_data(chip);
	पूर्णांक shअगरt = offset * 2;
	पूर्णांक ret;

	अगर (!test_and_clear_bit(offset, pdata->gchip_output))
		वापस 0;

	ret = regmap_update_bits(pdata->regmap, SN_GPIO_CTRL_REG,
				 SN_GPIO_MUX_MASK << shअगरt,
				 SN_GPIO_MUX_INPUT << shअगरt);
	अगर (ret) अणु
		set_bit(offset, pdata->gchip_output);
		वापस ret;
	पूर्ण

	/*
	 * NOTE: अगर nobody अन्यथा is घातering the device this may fully घातer
	 * it off and when it comes back it will have lost all state, but
	 * that's OK because the default is input and we're now an input.
	 */
	pm_runसमय_put(pdata->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ti_sn_bridge_gpio_direction_output(काष्ठा gpio_chip *chip,
					      अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा ti_sn_bridge *pdata = gpiochip_get_data(chip);
	पूर्णांक shअगरt = offset * 2;
	पूर्णांक ret;

	अगर (test_and_set_bit(offset, pdata->gchip_output))
		वापस 0;

	pm_runसमय_get_sync(pdata->dev);

	/* Set value first to aव्योम glitching */
	ti_sn_bridge_gpio_set(chip, offset, val);

	/* Set direction */
	ret = regmap_update_bits(pdata->regmap, SN_GPIO_CTRL_REG,
				 SN_GPIO_MUX_MASK << shअगरt,
				 SN_GPIO_MUX_OUTPUT << shअगरt);
	अगर (ret) अणु
		clear_bit(offset, pdata->gchip_output);
		pm_runसमय_put(pdata->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ti_sn_bridge_gpio_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	/* We won't keep pm_runtime if we're input, so चयन there on मुक्त */
	ti_sn_bridge_gpio_direction_input(chip, offset);
पूर्ण

अटल स्थिर अक्षर * स्थिर ti_sn_bridge_gpio_names[SN_NUM_GPIOS] = अणु
	"GPIO1", "GPIO2", "GPIO3", "GPIO4"
पूर्ण;

अटल पूर्णांक ti_sn_setup_gpio_controller(काष्ठा ti_sn_bridge *pdata)
अणु
	पूर्णांक ret;

	/* Only init अगर someone is going to use us as a GPIO controller */
	अगर (!of_property_पढ़ो_bool(pdata->dev->of_node, "gpio-controller"))
		वापस 0;

	pdata->gchip.label = dev_name(pdata->dev);
	pdata->gchip.parent = pdata->dev;
	pdata->gchip.owner = THIS_MODULE;
	pdata->gchip.of_xlate = tn_sn_bridge_of_xlate;
	pdata->gchip.of_gpio_n_cells = 2;
	pdata->gchip.मुक्त = ti_sn_bridge_gpio_मुक्त;
	pdata->gchip.get_direction = ti_sn_bridge_gpio_get_direction;
	pdata->gchip.direction_input = ti_sn_bridge_gpio_direction_input;
	pdata->gchip.direction_output = ti_sn_bridge_gpio_direction_output;
	pdata->gchip.get = ti_sn_bridge_gpio_get;
	pdata->gchip.set = ti_sn_bridge_gpio_set;
	pdata->gchip.can_sleep = true;
	pdata->gchip.names = ti_sn_bridge_gpio_names;
	pdata->gchip.ngpio = SN_NUM_GPIOS;
	pdata->gchip.base = -1;
	ret = devm_gpiochip_add_data(pdata->dev, &pdata->gchip, pdata);
	अगर (ret)
		dev_err(pdata->dev, "can't add gpio chip\n");

	वापस ret;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक ti_sn_setup_gpio_controller(काष्ठा ti_sn_bridge *pdata)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल व्योम ti_sn_bridge_parse_lanes(काष्ठा ti_sn_bridge *pdata,
				     काष्ठा device_node *np)
अणु
	u32 lane_assignments[SN_MAX_DP_LANES] = अणु 0, 1, 2, 3 पूर्ण;
	u32 lane_polarities[SN_MAX_DP_LANES] = अणु पूर्ण;
	काष्ठा device_node *endpoपूर्णांक;
	u8 ln_assign = 0;
	u8 ln_polrs = 0;
	पूर्णांक dp_lanes;
	पूर्णांक i;

	/*
	 * Read config from the device tree about lane remapping and lane
	 * polarities.  These are optional and we assume identity map and
	 * normal polarity अगर nothing is specअगरied.  It's OK to specअगरy just
	 * data-lanes but not lane-polarities but not vice versa.
	 *
	 * Error checking is light (we just make sure we करोn't crash or
	 * buffer overrun) and we assume dts is well क्रमmed and specअगरying
	 * mappings that the hardware supports.
	 */
	endpoपूर्णांक = of_graph_get_endpoपूर्णांक_by_regs(np, 1, -1);
	dp_lanes = of_property_count_u32_elems(endpoपूर्णांक, "data-lanes");
	अगर (dp_lanes > 0 && dp_lanes <= SN_MAX_DP_LANES) अणु
		of_property_पढ़ो_u32_array(endpoपूर्णांक, "data-lanes",
					   lane_assignments, dp_lanes);
		of_property_पढ़ो_u32_array(endpoपूर्णांक, "lane-polarities",
					   lane_polarities, dp_lanes);
	पूर्ण अन्यथा अणु
		dp_lanes = SN_MAX_DP_LANES;
	पूर्ण
	of_node_put(endpoपूर्णांक);

	/*
	 * Convert पूर्णांकo रेजिस्टर क्रमmat.  Loop over all lanes even अगर
	 * data-lanes had fewer elements so that we nicely initialize
	 * the LN_ASSIGN रेजिस्टर.
	 */
	क्रम (i = SN_MAX_DP_LANES - 1; i >= 0; i--) अणु
		ln_assign = ln_assign << LN_ASSIGN_WIDTH | lane_assignments[i];
		ln_polrs = ln_polrs << 1 | lane_polarities[i];
	पूर्ण

	/* Stash in our काष्ठा क्रम when we घातer on */
	pdata->dp_lanes = dp_lanes;
	pdata->ln_assign = ln_assign;
	pdata->ln_polrs = ln_polrs;
पूर्ण

अटल पूर्णांक ti_sn_bridge_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ti_sn_bridge *pdata;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		DRM_ERROR("device doesn't support I2C\n");
		वापस -ENODEV;
	पूर्ण

	pdata = devm_kzalloc(&client->dev, माप(काष्ठा ti_sn_bridge),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdata->regmap = devm_regmap_init_i2c(client,
					     &ti_sn_bridge_regmap_config);
	अगर (IS_ERR(pdata->regmap)) अणु
		DRM_ERROR("regmap i2c init failed\n");
		वापस PTR_ERR(pdata->regmap);
	पूर्ण

	pdata->dev = &client->dev;

	ret = drm_of_find_panel_or_bridge(pdata->dev->of_node, 1, 0,
					  &pdata->panel, शून्य);
	अगर (ret) अणु
		DRM_ERROR("could not find any panel node\n");
		वापस ret;
	पूर्ण

	dev_set_drvdata(&client->dev, pdata);

	pdata->enable_gpio = devm_gpiod_get(pdata->dev, "enable",
					    GPIOD_OUT_LOW);
	अगर (IS_ERR(pdata->enable_gpio)) अणु
		DRM_ERROR("failed to get enable gpio from DT\n");
		ret = PTR_ERR(pdata->enable_gpio);
		वापस ret;
	पूर्ण

	ti_sn_bridge_parse_lanes(pdata, client->dev.of_node);

	ret = ti_sn_bridge_parse_regulators(pdata);
	अगर (ret) अणु
		DRM_ERROR("failed to parse regulators\n");
		वापस ret;
	पूर्ण

	pdata->refclk = devm_clk_get(pdata->dev, "refclk");
	अगर (IS_ERR(pdata->refclk)) अणु
		ret = PTR_ERR(pdata->refclk);
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
		DRM_DEBUG_KMS("refclk not found\n");
		pdata->refclk = शून्य;
	पूर्ण

	ret = ti_sn_bridge_parse_dsi_host(pdata);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(pdata->dev);

	ret = ti_sn_setup_gpio_controller(pdata);
	अगर (ret) अणु
		pm_runसमय_disable(pdata->dev);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, pdata);

	pdata->aux.name = "ti-sn65dsi86-aux";
	pdata->aux.dev = pdata->dev;
	pdata->aux.transfer = ti_sn_aux_transfer;
	drm_dp_aux_init(&pdata->aux);

	pdata->bridge.funcs = &ti_sn_bridge_funcs;
	pdata->bridge.of_node = client->dev.of_node;

	drm_bridge_add(&pdata->bridge);

	ti_sn_debugfs_init(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक ti_sn_bridge_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ti_sn_bridge *pdata = i2c_get_clientdata(client);

	अगर (!pdata)
		वापस -EINVAL;

	kमुक्त(pdata->edid);
	ti_sn_debugfs_हटाओ(pdata);

	of_node_put(pdata->host_node);

	pm_runसमय_disable(pdata->dev);

	अगर (pdata->dsi) अणु
		mipi_dsi_detach(pdata->dsi);
		mipi_dsi_device_unरेजिस्टर(pdata->dsi);
	पूर्ण

	drm_bridge_हटाओ(&pdata->bridge);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_device_id ti_sn_bridge_id[] = अणु
	अणु "ti,sn65dsi86", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ti_sn_bridge_id);

अटल स्थिर काष्ठा of_device_id ti_sn_bridge_match_table[] = अणु
	अणु.compatible = "ti,sn65dsi86"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_sn_bridge_match_table);

अटल काष्ठा i2c_driver ti_sn_bridge_driver = अणु
	.driver = अणु
		.name = "ti_sn65dsi86",
		.of_match_table = ti_sn_bridge_match_table,
		.pm = &ti_sn_bridge_pm_ops,
	पूर्ण,
	.probe = ti_sn_bridge_probe,
	.हटाओ = ti_sn_bridge_हटाओ,
	.id_table = ti_sn_bridge_id,
पूर्ण;
module_i2c_driver(ti_sn_bridge_driver);

MODULE_AUTHOR("Sandeep Panda <spanda@codeaurora.org>");
MODULE_DESCRIPTION("sn65dsi86 DSI to eDP bridge driver");
MODULE_LICENSE("GPL v2");
