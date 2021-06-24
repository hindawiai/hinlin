<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2016, Analogix Semiconductor.
 * Copyright(c) 2017, Icenowy Zheng <icenowy@aosc.io>
 *
 * Based on anx7808 driver obtained from chromeos with copyright:
 * Copyright(c) 2013, Google Inc.
 */
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/types.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "analogix-i2c-dptx.h"
#समावेश "analogix-i2c-txcommon.h"

#घोषणा POLL_DELAY		50000 /* us */
#घोषणा POLL_TIMEOUT		5000000 /* us */

#घोषणा I2C_IDX_DPTX		0
#घोषणा I2C_IDX_TXCOM		1

अटल स्थिर u8 anx6345_i2c_addresses[] = अणु
	[I2C_IDX_DPTX]	= 0x70,
	[I2C_IDX_TXCOM]	= 0x72,
पूर्ण;
#घोषणा I2C_NUM_ADDRESSES	ARRAY_SIZE(anx6345_i2c_addresses)

काष्ठा anx6345 अणु
	काष्ठा drm_dp_aux aux;
	काष्ठा drm_bridge bridge;
	काष्ठा i2c_client *client;
	काष्ठा edid *edid;
	काष्ठा drm_connector connector;
	काष्ठा drm_panel *panel;
	काष्ठा regulator *dvdd12;
	काष्ठा regulator *dvdd25;
	काष्ठा gpio_desc *gpiod_reset;
	काष्ठा mutex lock;	/* protect EDID access */

	/* I2C Slave addresses of ANX6345 are mapped as DPTX and SYS */
	काष्ठा i2c_client *i2c_clients[I2C_NUM_ADDRESSES];
	काष्ठा regmap *map[I2C_NUM_ADDRESSES];

	u16 chipid;
	u8 dpcd[DP_RECEIVER_CAP_SIZE];

	bool घातered;
पूर्ण;

अटल अंतरभूत काष्ठा anx6345 *connector_to_anx6345(काष्ठा drm_connector *c)
अणु
	वापस container_of(c, काष्ठा anx6345, connector);
पूर्ण

अटल अंतरभूत काष्ठा anx6345 *bridge_to_anx6345(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा anx6345, bridge);
पूर्ण

अटल पूर्णांक anx6345_set_bits(काष्ठा regmap *map, u8 reg, u8 mask)
अणु
	वापस regmap_update_bits(map, reg, mask, mask);
पूर्ण

अटल पूर्णांक anx6345_clear_bits(काष्ठा regmap *map, u8 reg, u8 mask)
अणु
	वापस regmap_update_bits(map, reg, mask, 0);
पूर्ण

अटल sमाप_प्रकार anx6345_aux_transfer(काष्ठा drm_dp_aux *aux,
				    काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा anx6345 *anx6345 = container_of(aux, काष्ठा anx6345, aux);

	वापस anx_dp_aux_transfer(anx6345->map[I2C_IDX_DPTX], msg);
पूर्ण

अटल पूर्णांक anx6345_dp_link_training(काष्ठा anx6345 *anx6345)
अणु
	अचिन्हित पूर्णांक value;
	u8 dp_bw, dpcd[2];
	पूर्णांक err;

	err = anx6345_clear_bits(anx6345->map[I2C_IDX_TXCOM],
				 SP_POWERDOWN_CTRL_REG,
				 SP_TOTAL_PD);
	अगर (err)
		वापस err;

	err = drm_dp_dpcd_पढ़ोb(&anx6345->aux, DP_MAX_LINK_RATE, &dp_bw);
	अगर (err < 0)
		वापस err;

	चयन (dp_bw) अणु
	हाल DP_LINK_BW_1_62:
	हाल DP_LINK_BW_2_7:
		अवरोध;

	शेष:
		DRM_DEBUG_KMS("DP bandwidth (%#02x) not supported\n", dp_bw);
		वापस -EINVAL;
	पूर्ण

	err = anx6345_set_bits(anx6345->map[I2C_IDX_TXCOM], SP_VID_CTRL1_REG,
			       SP_VIDEO_MUTE);
	अगर (err)
		वापस err;

	err = anx6345_clear_bits(anx6345->map[I2C_IDX_TXCOM],
				 SP_VID_CTRL1_REG, SP_VIDEO_EN);
	अगर (err)
		वापस err;

	/* Get DPCD info */
	err = drm_dp_dpcd_पढ़ो(&anx6345->aux, DP_DPCD_REV,
			       &anx6345->dpcd, DP_RECEIVER_CAP_SIZE);
	अगर (err < 0) अणु
		DRM_ERROR("Failed to read DPCD: %d\n", err);
		वापस err;
	पूर्ण

	/* Clear channel x SERDES घातer करोwn */
	err = anx6345_clear_bits(anx6345->map[I2C_IDX_DPTX],
				 SP_DP_ANALOG_POWER_DOWN_REG, SP_CH0_PD);
	अगर (err)
		वापस err;

	/*
	 * Power up the sink (DP_SET_POWER रेजिस्टर is only available on DPCD
	 * v1.1 and later).
	 */
	अगर (anx6345->dpcd[DP_DPCD_REV] >= 0x11) अणु
		err = drm_dp_dpcd_पढ़ोb(&anx6345->aux, DP_SET_POWER, &dpcd[0]);
		अगर (err < 0) अणु
			DRM_ERROR("Failed to read DP_SET_POWER register: %d\n",
				  err);
			वापस err;
		पूर्ण

		dpcd[0] &= ~DP_SET_POWER_MASK;
		dpcd[0] |= DP_SET_POWER_D0;

		err = drm_dp_dpcd_ग_लिखोb(&anx6345->aux, DP_SET_POWER, dpcd[0]);
		अगर (err < 0) अणु
			DRM_ERROR("Failed to power up DisplayPort link: %d\n",
				  err);
			वापस err;
		पूर्ण

		/*
		 * According to the DP 1.1 specअगरication, a "Sink Device must
		 * निकास the घातer saving state within 1 ms" (Section 2.5.3.1,
		 * Table 5-52, "Sink Control Field" (रेजिस्टर 0x600).
		 */
		usleep_range(1000, 2000);
	पूर्ण

	/* Possibly enable करोwnspपढ़ो on the sink */
	err = regmap_ग_लिखो(anx6345->map[I2C_IDX_DPTX],
			   SP_DP_DOWNSPREAD_CTRL1_REG, 0);
	अगर (err)
		वापस err;

	अगर (anx6345->dpcd[DP_MAX_DOWNSPREAD] & DP_MAX_DOWNSPREAD_0_5) अणु
		DRM_DEBUG("Enable downspread on the sink\n");
		/* 4000PPM */
		err = regmap_ग_लिखो(anx6345->map[I2C_IDX_DPTX],
				   SP_DP_DOWNSPREAD_CTRL1_REG, 8);
		अगर (err)
			वापस err;

		err = drm_dp_dpcd_ग_लिखोb(&anx6345->aux, DP_DOWNSPREAD_CTRL,
					 DP_SPREAD_AMP_0_5);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		err = drm_dp_dpcd_ग_लिखोb(&anx6345->aux, DP_DOWNSPREAD_CTRL, 0);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* Set the lane count and the link rate on the sink */
	अगर (drm_dp_enhanced_frame_cap(anx6345->dpcd))
		err = anx6345_set_bits(anx6345->map[I2C_IDX_DPTX],
				       SP_DP_SYSTEM_CTRL_BASE + 4,
				       SP_ENHANCED_MODE);
	अन्यथा
		err = anx6345_clear_bits(anx6345->map[I2C_IDX_DPTX],
					 SP_DP_SYSTEM_CTRL_BASE + 4,
					 SP_ENHANCED_MODE);
	अगर (err)
		वापस err;

	dpcd[0] = dp_bw;
	err = regmap_ग_लिखो(anx6345->map[I2C_IDX_DPTX],
			   SP_DP_MAIN_LINK_BW_SET_REG, dpcd[0]);
	अगर (err)
		वापस err;

	dpcd[1] = drm_dp_max_lane_count(anx6345->dpcd);

	err = regmap_ग_लिखो(anx6345->map[I2C_IDX_DPTX],
			   SP_DP_LANE_COUNT_SET_REG, dpcd[1]);
	अगर (err)
		वापस err;

	अगर (drm_dp_enhanced_frame_cap(anx6345->dpcd))
		dpcd[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;

	err = drm_dp_dpcd_ग_लिखो(&anx6345->aux, DP_LINK_BW_SET, dpcd,
				माप(dpcd));

	अगर (err < 0) अणु
		DRM_ERROR("Failed to configure link: %d\n", err);
		वापस err;
	पूर्ण

	/* Start training on the source */
	err = regmap_ग_लिखो(anx6345->map[I2C_IDX_DPTX], SP_DP_LT_CTRL_REG,
			   SP_LT_EN);
	अगर (err)
		वापस err;

	वापस regmap_पढ़ो_poll_समयout(anx6345->map[I2C_IDX_DPTX],
				       SP_DP_LT_CTRL_REG,
				       value, !(value & SP_DP_LT_INPROGRESS),
				       POLL_DELAY, POLL_TIMEOUT);
पूर्ण

अटल पूर्णांक anx6345_tx_initialization(काष्ठा anx6345 *anx6345)
अणु
	पूर्णांक err, i;

	/* FIXME: colordepth is hardcoded क्रम now */
	err = regmap_ग_लिखो(anx6345->map[I2C_IDX_TXCOM], SP_VID_CTRL2_REG,
			   SP_IN_BPC_6BIT << SP_IN_BPC_SHIFT);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx6345->map[I2C_IDX_DPTX], SP_DP_PLL_CTRL_REG, 0);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx6345->map[I2C_IDX_TXCOM],
			   SP_ANALOG_DEBUG1_REG, 0);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx6345->map[I2C_IDX_DPTX],
			   SP_DP_LINK_DEBUG_CTRL_REG,
			   SP_NEW_PRBS7 | SP_M_VID_DEBUG);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(anx6345->map[I2C_IDX_DPTX],
			   SP_DP_ANALOG_POWER_DOWN_REG, 0);
	अगर (err)
		वापस err;

	/* Force HPD */
	err = anx6345_set_bits(anx6345->map[I2C_IDX_DPTX],
			       SP_DP_SYSTEM_CTRL_BASE + 3,
			       SP_HPD_FORCE | SP_HPD_CTRL);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < 4; i++) अणु
		/* 4 lanes */
		err = regmap_ग_लिखो(anx6345->map[I2C_IDX_DPTX],
				   SP_DP_LANE0_LT_CTRL_REG + i, 0);
		अगर (err)
			वापस err;
	पूर्ण

	/* Reset AUX */
	err = anx6345_set_bits(anx6345->map[I2C_IDX_TXCOM],
			       SP_RESET_CTRL2_REG, SP_AUX_RST);
	अगर (err)
		वापस err;

	वापस anx6345_clear_bits(anx6345->map[I2C_IDX_TXCOM],
				 SP_RESET_CTRL2_REG, SP_AUX_RST);
पूर्ण

अटल व्योम anx6345_घातeron(काष्ठा anx6345 *anx6345)
अणु
	पूर्णांक err;

	/* Ensure reset is निश्चितed beक्रमe starting घातer on sequence */
	gpiod_set_value_cansleep(anx6345->gpiod_reset, 1);
	usleep_range(1000, 2000);

	err = regulator_enable(anx6345->dvdd12);
	अगर (err) अणु
		DRM_ERROR("Failed to enable dvdd12 regulator: %d\n",
			  err);
		वापस;
	पूर्ण

	/* T1 - delay between VDD12 and VDD25 should be 0-2ms */
	usleep_range(1000, 2000);

	err = regulator_enable(anx6345->dvdd25);
	अगर (err) अणु
		DRM_ERROR("Failed to enable dvdd25 regulator: %d\n",
			  err);
		वापस;
	पूर्ण

	/* T2 - delay between RESETN and all घातer rail stable,
	 * should be 2-5ms
	 */
	usleep_range(2000, 5000);

	gpiod_set_value_cansleep(anx6345->gpiod_reset, 0);

	/* Power on रेजिस्टरs module */
	anx6345_set_bits(anx6345->map[I2C_IDX_TXCOM], SP_POWERDOWN_CTRL_REG,
			 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD | SP_LINK_PD);
	anx6345_clear_bits(anx6345->map[I2C_IDX_TXCOM], SP_POWERDOWN_CTRL_REG,
			   SP_REGISTER_PD | SP_TOTAL_PD);

	अगर (anx6345->panel)
		drm_panel_prepare(anx6345->panel);

	anx6345->घातered = true;
पूर्ण

अटल व्योम anx6345_घातeroff(काष्ठा anx6345 *anx6345)
अणु
	पूर्णांक err;

	gpiod_set_value_cansleep(anx6345->gpiod_reset, 1);
	usleep_range(1000, 2000);

	अगर (anx6345->panel)
		drm_panel_unprepare(anx6345->panel);

	err = regulator_disable(anx6345->dvdd25);
	अगर (err) अणु
		DRM_ERROR("Failed to disable dvdd25 regulator: %d\n",
			  err);
		वापस;
	पूर्ण

	usleep_range(5000, 10000);

	err = regulator_disable(anx6345->dvdd12);
	अगर (err) अणु
		DRM_ERROR("Failed to disable dvdd12 regulator: %d\n",
			  err);
		वापस;
	पूर्ण

	usleep_range(1000, 2000);

	anx6345->घातered = false;
पूर्ण

अटल पूर्णांक anx6345_start(काष्ठा anx6345 *anx6345)
अणु
	पूर्णांक err;

	अगर (!anx6345->घातered)
		anx6345_घातeron(anx6345);

	/* Power on needed modules */
	err = anx6345_clear_bits(anx6345->map[I2C_IDX_TXCOM],
				SP_POWERDOWN_CTRL_REG,
				SP_VIDEO_PD | SP_LINK_PD);

	err = anx6345_tx_initialization(anx6345);
	अगर (err) अणु
		DRM_ERROR("Failed eDP transmitter initialization: %d\n", err);
		anx6345_घातeroff(anx6345);
		वापस err;
	पूर्ण

	err = anx6345_dp_link_training(anx6345);
	अगर (err) अणु
		DRM_ERROR("Failed link training: %d\n", err);
		anx6345_घातeroff(anx6345);
		वापस err;
	पूर्ण

	/*
	 * This delay seems to help keep the hardware in a good state. Without
	 * it, there are बार where it fails silently.
	 */
	usleep_range(10000, 15000);

	वापस 0;
पूर्ण

अटल पूर्णांक anx6345_config_dp_output(काष्ठा anx6345 *anx6345)
अणु
	पूर्णांक err;

	err = anx6345_clear_bits(anx6345->map[I2C_IDX_TXCOM], SP_VID_CTRL1_REG,
				 SP_VIDEO_MUTE);
	अगर (err)
		वापस err;

	/* Enable DP output */
	err = anx6345_set_bits(anx6345->map[I2C_IDX_TXCOM], SP_VID_CTRL1_REG,
			       SP_VIDEO_EN);
	अगर (err)
		वापस err;

	/* Force stream valid */
	वापस anx6345_set_bits(anx6345->map[I2C_IDX_DPTX],
			       SP_DP_SYSTEM_CTRL_BASE + 3,
			       SP_STRM_FORCE | SP_STRM_CTRL);
पूर्ण

अटल पूर्णांक anx6345_get_करोwnstream_info(काष्ठा anx6345 *anx6345)
अणु
	u8 value;
	पूर्णांक err;

	err = drm_dp_dpcd_पढ़ोb(&anx6345->aux, DP_SINK_COUNT, &value);
	अगर (err < 0) अणु
		DRM_ERROR("Get sink count failed %d\n", err);
		वापस err;
	पूर्ण

	अगर (!DP_GET_SINK_COUNT(value)) अणु
		DRM_ERROR("Downstream disconnected\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक anx6345_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा anx6345 *anx6345 = connector_to_anx6345(connector);
	पूर्णांक err, num_modes = 0;
	bool घातer_off = false;

	mutex_lock(&anx6345->lock);

	अगर (!anx6345->edid) अणु
		अगर (!anx6345->घातered) अणु
			anx6345_घातeron(anx6345);
			घातer_off = true;
		पूर्ण

		err = anx6345_get_करोwnstream_info(anx6345);
		अगर (err) अणु
			DRM_ERROR("Failed to get downstream info: %d\n", err);
			जाओ unlock;
		पूर्ण

		anx6345->edid = drm_get_edid(connector, &anx6345->aux.ddc);
		अगर (!anx6345->edid)
			DRM_ERROR("Failed to read EDID from panel\n");

		err = drm_connector_update_edid_property(connector,
							 anx6345->edid);
		अगर (err) अणु
			DRM_ERROR("Failed to update EDID property: %d\n", err);
			जाओ unlock;
		पूर्ण
	पूर्ण

	num_modes += drm_add_edid_modes(connector, anx6345->edid);

	/* Driver currently supports only 6bpc */
	connector->display_info.bpc = 6;

unlock:
	अगर (घातer_off)
		anx6345_घातeroff(anx6345);

	mutex_unlock(&anx6345->lock);

	अगर (!num_modes && anx6345->panel)
		num_modes += drm_panel_get_modes(anx6345->panel, connector);

	वापस num_modes;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs anx6345_connector_helper_funcs = अणु
	.get_modes = anx6345_get_modes,
पूर्ण;

अटल व्योम
anx6345_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs anx6345_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = anx6345_connector_destroy,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक anx6345_bridge_attach(काष्ठा drm_bridge *bridge,
				 क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा anx6345 *anx6345 = bridge_to_anx6345(bridge);
	पूर्णांक err;

	अगर (flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR) अणु
		DRM_ERROR("Fix bridge driver to make connector optional!");
		वापस -EINVAL;
	पूर्ण

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	/* Register aux channel */
	anx6345->aux.name = "DP-AUX";
	anx6345->aux.dev = &anx6345->client->dev;
	anx6345->aux.transfer = anx6345_aux_transfer;

	err = drm_dp_aux_रेजिस्टर(&anx6345->aux);
	अगर (err < 0) अणु
		DRM_ERROR("Failed to register aux channel: %d\n", err);
		वापस err;
	पूर्ण

	err = drm_connector_init(bridge->dev, &anx6345->connector,
				 &anx6345_connector_funcs,
				 DRM_MODE_CONNECTOR_eDP);
	अगर (err) अणु
		DRM_ERROR("Failed to initialize connector: %d\n", err);
		जाओ aux_unरेजिस्टर;
	पूर्ण

	drm_connector_helper_add(&anx6345->connector,
				 &anx6345_connector_helper_funcs);

	anx6345->connector.polled = DRM_CONNECTOR_POLL_HPD;

	err = drm_connector_attach_encoder(&anx6345->connector,
					   bridge->encoder);
	अगर (err) अणु
		DRM_ERROR("Failed to link up connector to encoder: %d\n", err);
		जाओ connector_cleanup;
	पूर्ण

	err = drm_connector_रेजिस्टर(&anx6345->connector);
	अगर (err) अणु
		DRM_ERROR("Failed to register connector: %d\n", err);
		जाओ connector_cleanup;
	पूर्ण

	वापस 0;
connector_cleanup:
	drm_connector_cleanup(&anx6345->connector);
aux_unरेजिस्टर:
	drm_dp_aux_unरेजिस्टर(&anx6345->aux);
	वापस err;
पूर्ण

अटल व्योम anx6345_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	drm_dp_aux_unरेजिस्टर(&bridge_to_anx6345(bridge)->aux);
पूर्ण

अटल क्रमागत drm_mode_status
anx6345_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			  स्थिर काष्ठा drm_display_info *info,
			  स्थिर काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		वापस MODE_NO_INTERLACE;

	/* Max 1200p at 5.4 Ghz, one lane */
	अगर (mode->घड़ी > 154000)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल व्योम anx6345_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा anx6345 *anx6345 = bridge_to_anx6345(bridge);

	/* Power off all modules except configuration रेजिस्टरs access */
	anx6345_set_bits(anx6345->map[I2C_IDX_TXCOM], SP_POWERDOWN_CTRL_REG,
			 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD | SP_LINK_PD);
	अगर (anx6345->panel)
		drm_panel_disable(anx6345->panel);

	अगर (anx6345->घातered)
		anx6345_घातeroff(anx6345);
पूर्ण

अटल व्योम anx6345_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा anx6345 *anx6345 = bridge_to_anx6345(bridge);
	पूर्णांक err;

	अगर (anx6345->panel)
		drm_panel_enable(anx6345->panel);

	err = anx6345_start(anx6345);
	अगर (err) अणु
		DRM_ERROR("Failed to initialize: %d\n", err);
		वापस;
	पूर्ण

	err = anx6345_config_dp_output(anx6345);
	अगर (err)
		DRM_ERROR("Failed to enable DP output: %d\n", err);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs anx6345_bridge_funcs = अणु
	.attach = anx6345_bridge_attach,
	.detach = anx6345_bridge_detach,
	.mode_valid = anx6345_bridge_mode_valid,
	.disable = anx6345_bridge_disable,
	.enable = anx6345_bridge_enable,
पूर्ण;

अटल व्योम unरेजिस्टर_i2c_dummy_clients(काष्ठा anx6345 *anx6345)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < ARRAY_SIZE(anx6345->i2c_clients); i++)
		अगर (anx6345->i2c_clients[i] &&
		    anx6345->i2c_clients[i]->addr != anx6345->client->addr)
			i2c_unरेजिस्टर_device(anx6345->i2c_clients[i]);
पूर्ण

अटल स्थिर काष्ठा regmap_config anx6345_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xff,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर u16 anx6345_chipid_list[] = अणु
	0x6345,
पूर्ण;

अटल bool anx6345_get_chip_id(काष्ठा anx6345 *anx6345)
अणु
	अचिन्हित पूर्णांक i, idl, idh, version;

	अगर (regmap_पढ़ो(anx6345->map[I2C_IDX_TXCOM], SP_DEVICE_IDL_REG, &idl))
		वापस false;

	अगर (regmap_पढ़ो(anx6345->map[I2C_IDX_TXCOM], SP_DEVICE_IDH_REG, &idh))
		वापस false;

	anx6345->chipid = (u8)idl | ((u8)idh << 8);

	अगर (regmap_पढ़ो(anx6345->map[I2C_IDX_TXCOM], SP_DEVICE_VERSION_REG,
			&version))
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(anx6345_chipid_list); i++) अणु
		अगर (anx6345->chipid == anx6345_chipid_list[i]) अणु
			DRM_INFO("Found ANX%x (ver. %d) eDP Transmitter\n",
				 anx6345->chipid, version);
			वापस true;
		पूर्ण
	पूर्ण

	DRM_ERROR("ANX%x (ver. %d) not supported by this driver\n",
		  anx6345->chipid, version);

	वापस false;
पूर्ण

अटल पूर्णांक anx6345_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा anx6345 *anx6345;
	काष्ठा device *dev;
	पूर्णांक i, err;

	anx6345 = devm_kzalloc(&client->dev, माप(*anx6345), GFP_KERNEL);
	अगर (!anx6345)
		वापस -ENOMEM;

	mutex_init(&anx6345->lock);

	anx6345->bridge.of_node = client->dev.of_node;

	anx6345->client = client;
	i2c_set_clientdata(client, anx6345);

	dev = &anx6345->client->dev;

	err = drm_of_find_panel_or_bridge(client->dev.of_node, 1, 0,
					  &anx6345->panel, शून्य);
	अगर (err == -EPROBE_DEFER)
		वापस err;

	अगर (err)
		DRM_DEBUG("No panel found\n");

	/* 1.2V digital core घातer regulator  */
	anx6345->dvdd12 = devm_regulator_get(dev, "dvdd12");
	अगर (IS_ERR(anx6345->dvdd12)) अणु
		अगर (PTR_ERR(anx6345->dvdd12) != -EPROBE_DEFER)
			DRM_ERROR("Failed to get dvdd12 supply (%ld)\n",
				  PTR_ERR(anx6345->dvdd12));
		वापस PTR_ERR(anx6345->dvdd12);
	पूर्ण

	/* 2.5V digital core घातer regulator  */
	anx6345->dvdd25 = devm_regulator_get(dev, "dvdd25");
	अगर (IS_ERR(anx6345->dvdd25)) अणु
		अगर (PTR_ERR(anx6345->dvdd25) != -EPROBE_DEFER)
			DRM_ERROR("Failed to get dvdd25 supply (%ld)\n",
				  PTR_ERR(anx6345->dvdd25));
		वापस PTR_ERR(anx6345->dvdd25);
	पूर्ण

	/* GPIO क्रम chip reset */
	anx6345->gpiod_reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(anx6345->gpiod_reset)) अणु
		DRM_ERROR("Reset gpio not found\n");
		वापस PTR_ERR(anx6345->gpiod_reset);
	पूर्ण

	/* Map slave addresses of ANX6345 */
	क्रम (i = 0; i < I2C_NUM_ADDRESSES; i++) अणु
		अगर (anx6345_i2c_addresses[i] >> 1 != client->addr)
			anx6345->i2c_clients[i] = i2c_new_dummy_device(client->adapter,
						anx6345_i2c_addresses[i] >> 1);
		अन्यथा
			anx6345->i2c_clients[i] = client;

		अगर (IS_ERR(anx6345->i2c_clients[i])) अणु
			err = PTR_ERR(anx6345->i2c_clients[i]);
			DRM_ERROR("Failed to reserve I2C bus %02x\n",
				  anx6345_i2c_addresses[i]);
			जाओ err_unरेजिस्टर_i2c;
		पूर्ण

		anx6345->map[i] = devm_regmap_init_i2c(anx6345->i2c_clients[i],
						       &anx6345_regmap_config);
		अगर (IS_ERR(anx6345->map[i])) अणु
			err = PTR_ERR(anx6345->map[i]);
			DRM_ERROR("Failed regmap initialization %02x\n",
				  anx6345_i2c_addresses[i]);
			जाओ err_unरेजिस्टर_i2c;
		पूर्ण
	पूर्ण

	/* Look क्रम supported chip ID */
	anx6345_घातeron(anx6345);
	अगर (anx6345_get_chip_id(anx6345)) अणु
		anx6345->bridge.funcs = &anx6345_bridge_funcs;
		drm_bridge_add(&anx6345->bridge);

		वापस 0;
	पूर्ण अन्यथा अणु
		anx6345_घातeroff(anx6345);
		err = -ENODEV;
	पूर्ण

err_unरेजिस्टर_i2c:
	unरेजिस्टर_i2c_dummy_clients(anx6345);
	वापस err;
पूर्ण

अटल पूर्णांक anx6345_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा anx6345 *anx6345 = i2c_get_clientdata(client);

	drm_bridge_हटाओ(&anx6345->bridge);

	unरेजिस्टर_i2c_dummy_clients(anx6345);

	kमुक्त(anx6345->edid);

	mutex_destroy(&anx6345->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id anx6345_id[] = अणु
	अणु "anx6345", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, anx6345_id);

अटल स्थिर काष्ठा of_device_id anx6345_match_table[] = अणु
	अणु .compatible = "analogix,anx6345", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, anx6345_match_table);

अटल काष्ठा i2c_driver anx6345_driver = अणु
	.driver = अणु
		   .name = "anx6345",
		   .of_match_table = of_match_ptr(anx6345_match_table),
		  पूर्ण,
	.probe = anx6345_i2c_probe,
	.हटाओ = anx6345_i2c_हटाओ,
	.id_table = anx6345_id,
पूर्ण;
module_i2c_driver(anx6345_driver);

MODULE_DESCRIPTION("ANX6345 eDP Transmitter driver");
MODULE_AUTHOR("Icenowy Zheng <icenowy@aosc.io>");
MODULE_LICENSE("GPL v2");
