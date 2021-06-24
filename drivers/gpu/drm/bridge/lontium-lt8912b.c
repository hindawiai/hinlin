<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_of.h>

#समावेश <video/videomode.h>

#घोषणा I2C_MAIN 0
#घोषणा I2C_ADDR_MAIN 0x48

#घोषणा I2C_CEC_DSI 1
#घोषणा I2C_ADDR_CEC_DSI 0x49

#घोषणा I2C_MAX_IDX 2

काष्ठा lt8912 अणु
	काष्ठा device *dev;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;

	काष्ठा i2c_client *i2c_client[I2C_MAX_IDX];
	काष्ठा regmap *regmap[I2C_MAX_IDX];

	काष्ठा device_node *host_node;
	काष्ठा drm_bridge *hdmi_port;

	काष्ठा mipi_dsi_device *dsi;

	काष्ठा gpio_desc *gp_reset;

	काष्ठा videomode mode;

	u8 data_lanes;
	bool is_घातer_on;
	bool is_attached;
पूर्ण;

अटल पूर्णांक lt8912_ग_लिखो_init_config(काष्ठा lt8912 *lt)
अणु
	स्थिर काष्ठा reg_sequence seq[] = अणु
		/* Digital घड़ी en*/
		अणु0x08, 0xffपूर्ण,
		अणु0x09, 0xffपूर्ण,
		अणु0x0a, 0xffपूर्ण,
		अणु0x0b, 0x7cपूर्ण,
		अणु0x0c, 0xffपूर्ण,
		अणु0x42, 0x04पूर्ण,

		/*Tx Analog*/
		अणु0x31, 0xb1पूर्ण,
		अणु0x32, 0xb1पूर्ण,
		अणु0x33, 0x0eपूर्ण,
		अणु0x37, 0x00पूर्ण,
		अणु0x38, 0x22पूर्ण,
		अणु0x60, 0x82पूर्ण,

		/*Cbus Analog*/
		अणु0x39, 0x45पूर्ण,
		अणु0x3a, 0x00पूर्ण,
		अणु0x3b, 0x00पूर्ण,

		/*HDMI Pll Analog*/
		अणु0x44, 0x31पूर्ण,
		अणु0x55, 0x44पूर्ण,
		अणु0x57, 0x01पूर्ण,
		अणु0x5a, 0x02पूर्ण,

		/*MIPI Analog*/
		अणु0x3e, 0xd6पूर्ण,
		अणु0x3f, 0xd4पूर्ण,
		अणु0x41, 0x3cपूर्ण,
		अणु0xB2, 0x00पूर्ण,
	पूर्ण;

	वापस regmap_multi_reg_ग_लिखो(lt->regmap[I2C_MAIN], seq, ARRAY_SIZE(seq));
पूर्ण

अटल पूर्णांक lt8912_ग_लिखो_mipi_basic_config(काष्ठा lt8912 *lt)
अणु
	स्थिर काष्ठा reg_sequence seq[] = अणु
		अणु0x12, 0x04पूर्ण,
		अणु0x14, 0x00पूर्ण,
		अणु0x15, 0x00पूर्ण,
		अणु0x1a, 0x03पूर्ण,
		अणु0x1b, 0x03पूर्ण,
	पूर्ण;

	वापस regmap_multi_reg_ग_लिखो(lt->regmap[I2C_CEC_DSI], seq, ARRAY_SIZE(seq));
पूर्ण;

अटल पूर्णांक lt8912_ग_लिखो_dds_config(काष्ठा lt8912 *lt)
अणु
	स्थिर काष्ठा reg_sequence seq[] = अणु
		अणु0x4e, 0xffपूर्ण,
		अणु0x4f, 0x56पूर्ण,
		अणु0x50, 0x69पूर्ण,
		अणु0x51, 0x80पूर्ण,
		अणु0x1f, 0x5eपूर्ण,
		अणु0x20, 0x01पूर्ण,
		अणु0x21, 0x2cपूर्ण,
		अणु0x22, 0x01पूर्ण,
		अणु0x23, 0xfaपूर्ण,
		अणु0x24, 0x00पूर्ण,
		अणु0x25, 0xc8पूर्ण,
		अणु0x26, 0x00पूर्ण,
		अणु0x27, 0x5eपूर्ण,
		अणु0x28, 0x01पूर्ण,
		अणु0x29, 0x2cपूर्ण,
		अणु0x2a, 0x01पूर्ण,
		अणु0x2b, 0xfaपूर्ण,
		अणु0x2c, 0x00पूर्ण,
		अणु0x2d, 0xc8पूर्ण,
		अणु0x2e, 0x00पूर्ण,
		अणु0x42, 0x64पूर्ण,
		अणु0x43, 0x00पूर्ण,
		अणु0x44, 0x04पूर्ण,
		अणु0x45, 0x00पूर्ण,
		अणु0x46, 0x59पूर्ण,
		अणु0x47, 0x00पूर्ण,
		अणु0x48, 0xf2पूर्ण,
		अणु0x49, 0x06पूर्ण,
		अणु0x4a, 0x00पूर्ण,
		अणु0x4b, 0x72पूर्ण,
		अणु0x4c, 0x45पूर्ण,
		अणु0x4d, 0x00पूर्ण,
		अणु0x52, 0x08पूर्ण,
		अणु0x53, 0x00पूर्ण,
		अणु0x54, 0xb2पूर्ण,
		अणु0x55, 0x00पूर्ण,
		अणु0x56, 0xe4पूर्ण,
		अणु0x57, 0x0dपूर्ण,
		अणु0x58, 0x00पूर्ण,
		अणु0x59, 0xe4पूर्ण,
		अणु0x5a, 0x8aपूर्ण,
		अणु0x5b, 0x00पूर्ण,
		अणु0x5c, 0x34पूर्ण,
		अणु0x1e, 0x4fपूर्ण,
		अणु0x51, 0x00पूर्ण,
	पूर्ण;

	वापस regmap_multi_reg_ग_लिखो(lt->regmap[I2C_CEC_DSI], seq, ARRAY_SIZE(seq));
पूर्ण

अटल पूर्णांक lt8912_ग_लिखो_rxlogicres_config(काष्ठा lt8912 *lt)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(lt->regmap[I2C_MAIN], 0x03, 0x7f);
	usleep_range(10000, 20000);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_MAIN], 0x03, 0xff);

	वापस ret;
पूर्ण;

अटल पूर्णांक lt8912_ग_लिखो_lvds_config(काष्ठा lt8912 *lt)
अणु
	स्थिर काष्ठा reg_sequence seq[] = अणु
		अणु0x44, 0x30पूर्ण,
		अणु0x51, 0x05पूर्ण,
		अणु0x50, 0x24पूर्ण,
		अणु0x51, 0x2dपूर्ण,
		अणु0x52, 0x04पूर्ण,
		अणु0x69, 0x0eपूर्ण,
		अणु0x69, 0x8eपूर्ण,
		अणु0x6a, 0x00पूर्ण,
		अणु0x6c, 0xb8पूर्ण,
		अणु0x6b, 0x51पूर्ण,
		अणु0x04, 0xfbपूर्ण,
		अणु0x04, 0xffपूर्ण,
		अणु0x7f, 0x00पूर्ण,
		अणु0xa8, 0x13पूर्ण,
		अणु0x02, 0xf7पूर्ण,
		अणु0x02, 0xffपूर्ण,
		अणु0x03, 0xcfपूर्ण,
		अणु0x03, 0xffपूर्ण,
	पूर्ण;

	वापस regmap_multi_reg_ग_लिखो(lt->regmap[I2C_CEC_DSI], seq, ARRAY_SIZE(seq));
पूर्ण;

अटल अंतरभूत काष्ठा lt8912 *bridge_to_lt8912(काष्ठा drm_bridge *b)
अणु
	वापस container_of(b, काष्ठा lt8912, bridge);
पूर्ण

अटल अंतरभूत काष्ठा lt8912 *connector_to_lt8912(काष्ठा drm_connector *c)
अणु
	वापस container_of(c, काष्ठा lt8912, connector);
पूर्ण

अटल स्थिर काष्ठा regmap_config lt8912_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xff,
पूर्ण;

अटल पूर्णांक lt8912_init_i2c(काष्ठा lt8912 *lt, काष्ठा i2c_client *client)
अणु
	अचिन्हित पूर्णांक i;
	/*
	 * At this समय we only initialize 2 chips, but the lt8912 provides
	 * a third पूर्णांकerface क्रम the audio over HDMI configuration.
	 */
	काष्ठा i2c_board_info info[] = अणु
		अणु I2C_BOARD_INFO("lt8912p0", I2C_ADDR_MAIN), पूर्ण,
		अणु I2C_BOARD_INFO("lt8912p1", I2C_ADDR_CEC_DSI), पूर्ण,
	पूर्ण;

	अगर (!lt)
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(info); i++) अणु
		अगर (i > 0) अणु
			lt->i2c_client[i] = i2c_new_dummy_device(client->adapter,
								 info[i].addr);
			अगर (IS_ERR(lt->i2c_client[i]))
				वापस PTR_ERR(lt->i2c_client[i]);
		पूर्ण

		lt->regmap[i] = devm_regmap_init_i2c(lt->i2c_client[i],
						     &lt8912_regmap_config);
		अगर (IS_ERR(lt->regmap[i]))
			वापस PTR_ERR(lt->regmap[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lt8912_मुक्त_i2c(काष्ठा lt8912 *lt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 1; i < I2C_MAX_IDX; i++)
		i2c_unरेजिस्टर_device(lt->i2c_client[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक lt8912_hard_घातer_on(काष्ठा lt8912 *lt)
अणु
	gpiod_set_value_cansleep(lt->gp_reset, 0);
	msleep(20);

	वापस 0;
पूर्ण

अटल व्योम lt8912_hard_घातer_off(काष्ठा lt8912 *lt)
अणु
	gpiod_set_value_cansleep(lt->gp_reset, 1);
	msleep(20);
	lt->is_घातer_on = false;
पूर्ण

अटल पूर्णांक lt8912_video_setup(काष्ठा lt8912 *lt)
अणु
	u32 hactive, h_total, hpw, hfp, hbp;
	u32 vactive, v_total, vpw, vfp, vbp;
	u8 settle = 0x08;
	पूर्णांक ret;

	अगर (!lt)
		वापस -EINVAL;

	hactive = lt->mode.hactive;
	hfp = lt->mode.hfront_porch;
	hpw = lt->mode.hsync_len;
	hbp = lt->mode.hback_porch;
	h_total = hactive + hfp + hpw + hbp;

	vactive = lt->mode.vactive;
	vfp = lt->mode.vfront_porch;
	vpw = lt->mode.vsync_len;
	vbp = lt->mode.vback_porch;
	v_total = vactive + vfp + vpw + vbp;

	अगर (vactive <= 600)
		settle = 0x04;
	अन्यथा अगर (vactive == 1080)
		settle = 0x0a;

	ret = regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x10, 0x01);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x11, settle);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x18, hpw);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x19, vpw);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x1c, hactive & 0xff);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x1d, hactive >> 8);

	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x2f, 0x0c);

	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x34, h_total & 0xff);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x35, h_total >> 8);

	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x36, v_total & 0xff);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x37, v_total >> 8);

	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x38, vbp & 0xff);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x39, vbp >> 8);

	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x3a, vfp & 0xff);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x3b, vfp >> 8);

	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x3c, hbp & 0xff);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x3d, hbp >> 8);

	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x3e, hfp & 0xff);
	ret |= regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x3f, hfp >> 8);

	वापस ret;
पूर्ण

अटल पूर्णांक lt8912_soft_घातer_on(काष्ठा lt8912 *lt)
अणु
	अगर (!lt->is_घातer_on) अणु
		u32 lanes = lt->data_lanes;

		lt8912_ग_लिखो_init_config(lt);
		regmap_ग_लिखो(lt->regmap[I2C_CEC_DSI], 0x13, lanes & 3);

		lt8912_ग_लिखो_mipi_basic_config(lt);

		lt->is_घातer_on = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lt8912_video_on(काष्ठा lt8912 *lt)
अणु
	पूर्णांक ret;

	ret = lt8912_video_setup(lt);
	अगर (ret < 0)
		जाओ end;

	ret = lt8912_ग_लिखो_dds_config(lt);
	अगर (ret < 0)
		जाओ end;

	ret = lt8912_ग_लिखो_rxlogicres_config(lt);
	अगर (ret < 0)
		जाओ end;

	ret = lt8912_ग_लिखो_lvds_config(lt);
	अगर (ret < 0)
		जाओ end;

end:
	वापस ret;
पूर्ण

अटल क्रमागत drm_connector_status lt8912_check_cable_status(काष्ठा lt8912 *lt)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;

	ret = regmap_पढ़ो(lt->regmap[I2C_MAIN], 0xC1, &reg_val);
	अगर (ret)
		वापस connector_status_unknown;

	अगर (reg_val & BIT(7))
		वापस connector_status_connected;

	वापस connector_status_disconnected;
पूर्ण

अटल क्रमागत drm_connector_status
lt8912_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा lt8912 *lt = connector_to_lt8912(connector);

	अगर (lt->hdmi_port->ops & DRM_BRIDGE_OP_DETECT)
		वापस drm_bridge_detect(lt->hdmi_port);

	वापस lt8912_check_cable_status(lt);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs lt8912_connector_funcs = अणु
	.detect = lt8912_connector_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल क्रमागत drm_mode_status
lt8912_connector_mode_valid(काष्ठा drm_connector *connector,
			    काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > 150000)
		वापस MODE_CLOCK_HIGH;

	अगर (mode->hdisplay > 1920)
		वापस MODE_BAD_HVALUE;

	अगर (mode->vdisplay > 1080)
		वापस MODE_BAD_VVALUE;

	वापस MODE_OK;
पूर्ण

अटल पूर्णांक lt8912_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा edid *edid;
	पूर्णांक ret = -1;
	पूर्णांक num = 0;
	काष्ठा lt8912 *lt = connector_to_lt8912(connector);
	u32 bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;

	edid = drm_bridge_get_edid(lt->hdmi_port, connector);
	अगर (edid) अणु
		drm_connector_update_edid_property(connector, edid);
		num = drm_add_edid_modes(connector, edid);
	पूर्ण अन्यथा अणु
		वापस ret;
	पूर्ण

	ret = drm_display_info_set_bus_क्रमmats(&connector->display_info,
					       &bus_क्रमmat, 1);
	अगर (ret)
		num = ret;

	kमुक्त(edid);
	वापस num;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs lt8912_connector_helper_funcs = अणु
	.get_modes = lt8912_connector_get_modes,
	.mode_valid = lt8912_connector_mode_valid,
पूर्ण;

अटल व्योम lt8912_bridge_mode_set(काष्ठा drm_bridge *bridge,
				   स्थिर काष्ठा drm_display_mode *mode,
				   स्थिर काष्ठा drm_display_mode *adj)
अणु
	काष्ठा lt8912 *lt = bridge_to_lt8912(bridge);

	drm_display_mode_to_videomode(adj, &lt->mode);
पूर्ण

अटल व्योम lt8912_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt8912 *lt = bridge_to_lt8912(bridge);

	lt8912_video_on(lt);
पूर्ण

अटल पूर्णांक lt8912_attach_dsi(काष्ठा lt8912 *lt)
अणु
	काष्ठा device *dev = lt->dev;
	काष्ठा mipi_dsi_host *host;
	काष्ठा mipi_dsi_device *dsi;
	पूर्णांक ret = -1;
	स्थिर काष्ठा mipi_dsi_device_info info = अणु .type = "lt8912",
						   .channel = 0,
						   .node = शून्य,
						 पूर्ण;

	host = of_find_mipi_dsi_host_by_node(lt->host_node);
	अगर (!host) अणु
		dev_err(dev, "failed to find dsi host\n");
		वापस -EPROBE_DEFER;
	पूर्ण

	dsi = mipi_dsi_device_रेजिस्टर_full(host, &info);
	अगर (IS_ERR(dsi)) अणु
		ret = PTR_ERR(dsi);
		dev_err(dev, "failed to create dsi device (%d)\n", ret);
		जाओ err_dsi_device;
	पूर्ण

	lt->dsi = dsi;

	dsi->lanes = lt->data_lanes;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;

	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
			  MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_LPM |
			  MIPI_DSI_MODE_EOT_PACKET;

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to attach dsi to host\n");
		जाओ err_dsi_attach;
	पूर्ण

	वापस 0;

err_dsi_attach:
	mipi_dsi_device_unरेजिस्टर(dsi);
err_dsi_device:
	वापस ret;
पूर्ण

अटल व्योम lt8912_detach_dsi(काष्ठा lt8912 *lt)
अणु
	mipi_dsi_detach(lt->dsi);
	mipi_dsi_device_unरेजिस्टर(lt->dsi);
पूर्ण

अटल पूर्णांक lt8912_bridge_connector_init(काष्ठा drm_bridge *bridge)
अणु
	पूर्णांक ret;
	काष्ठा lt8912 *lt = bridge_to_lt8912(bridge);
	काष्ठा drm_connector *connector = &lt->connector;

	connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			    DRM_CONNECTOR_POLL_DISCONNECT;

	ret = drm_connector_init(bridge->dev, connector,
				 &lt8912_connector_funcs,
				 lt->hdmi_port->type);
	अगर (ret)
		जाओ निकास;

	drm_connector_helper_add(connector, &lt8912_connector_helper_funcs);

	connector->dpms = DRM_MODE_DPMS_OFF;
	drm_connector_attach_encoder(connector, bridge->encoder);

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक lt8912_bridge_attach(काष्ठा drm_bridge *bridge,
				क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा lt8912 *lt = bridge_to_lt8912(bridge);
	पूर्णांक ret;

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)) अणु
		ret = lt8912_bridge_connector_init(bridge);
		अगर (ret) अणु
			dev_err(lt->dev, "Failed to init bridge ! (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = lt8912_hard_घातer_on(lt);
	अगर (ret)
		वापस ret;

	ret = lt8912_soft_घातer_on(lt);
	अगर (ret)
		जाओ error;

	ret = lt8912_attach_dsi(lt);
	अगर (ret)
		जाओ error;

	lt->is_attached = true;

	वापस 0;

error:
	lt8912_hard_घातer_off(lt);
	वापस ret;
पूर्ण

अटल व्योम lt8912_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt8912 *lt = bridge_to_lt8912(bridge);

	अगर (lt->is_attached) अणु
		lt8912_detach_dsi(lt);
		lt8912_hard_घातer_off(lt);
		drm_connector_unरेजिस्टर(&lt->connector);
		drm_connector_cleanup(&lt->connector);
	पूर्ण
पूर्ण

अटल क्रमागत drm_connector_status
lt8912_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt8912 *lt = bridge_to_lt8912(bridge);

	अगर (lt->hdmi_port->ops & DRM_BRIDGE_OP_DETECT)
		वापस drm_bridge_detect(lt->hdmi_port);

	वापस lt8912_check_cable_status(lt);
पूर्ण

अटल काष्ठा edid *lt8912_bridge_get_edid(काष्ठा drm_bridge *bridge,
					   काष्ठा drm_connector *connector)
अणु
	काष्ठा lt8912 *lt = bridge_to_lt8912(bridge);

	/*
	 * edid must be पढ़ो through the ddc bus but it must be
	 * given to the hdmi connector node.
	 */
	अगर (lt->hdmi_port->ops & DRM_BRIDGE_OP_EDID)
		वापस drm_bridge_get_edid(lt->hdmi_port, connector);

	dev_warn(lt->dev, "The connected bridge does not supports DRM_BRIDGE_OP_EDID\n");
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs lt8912_bridge_funcs = अणु
	.attach = lt8912_bridge_attach,
	.detach = lt8912_bridge_detach,
	.mode_set = lt8912_bridge_mode_set,
	.enable = lt8912_bridge_enable,
	.detect = lt8912_bridge_detect,
	.get_edid = lt8912_bridge_get_edid,
पूर्ण;

अटल पूर्णांक lt8912_parse_dt(काष्ठा lt8912 *lt)
अणु
	काष्ठा gpio_desc *gp_reset;
	काष्ठा device *dev = lt->dev;
	पूर्णांक ret;
	पूर्णांक data_lanes;
	काष्ठा device_node *port_node;
	काष्ठा device_node *endpoपूर्णांक;

	gp_reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(gp_reset)) अणु
		ret = PTR_ERR(gp_reset);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get reset gpio: %d\n", ret);
		वापस ret;
	पूर्ण
	lt->gp_reset = gp_reset;

	endpoपूर्णांक = of_graph_get_endpoपूर्णांक_by_regs(dev->of_node, 0, -1);
	अगर (!endpoपूर्णांक)
		वापस -ENODEV;

	data_lanes = of_property_count_u32_elems(endpoपूर्णांक, "data-lanes");
	of_node_put(endpoपूर्णांक);
	अगर (data_lanes < 0) अणु
		dev_err(lt->dev, "%s: Bad data-lanes property\n", __func__);
		वापस data_lanes;
	पूर्ण
	lt->data_lanes = data_lanes;

	lt->host_node = of_graph_get_remote_node(dev->of_node, 0, -1);
	अगर (!lt->host_node) अणु
		dev_err(lt->dev, "%s: Failed to get remote port\n", __func__);
		वापस -ENODEV;
	पूर्ण

	port_node = of_graph_get_remote_node(dev->of_node, 1, -1);
	अगर (!port_node) अणु
		dev_err(lt->dev, "%s: Failed to get connector port\n", __func__);
		ret = -ENODEV;
		जाओ err_मुक्त_host_node;
	पूर्ण

	lt->hdmi_port = of_drm_find_bridge(port_node);
	अगर (!lt->hdmi_port) अणु
		dev_err(lt->dev, "%s: Failed to get hdmi port\n", __func__);
		ret = -ENODEV;
		जाओ err_मुक्त_host_node;
	पूर्ण

	अगर (!of_device_is_compatible(port_node, "hdmi-connector")) अणु
		dev_err(lt->dev, "%s: Failed to get hdmi port\n", __func__);
		ret = -EINVAL;
		जाओ err_मुक्त_host_node;
	पूर्ण

	of_node_put(port_node);
	वापस 0;

err_मुक्त_host_node:
	of_node_put(port_node);
	of_node_put(lt->host_node);
	वापस ret;
पूर्ण

अटल पूर्णांक lt8912_put_dt(काष्ठा lt8912 *lt)
अणु
	of_node_put(lt->host_node);
	वापस 0;
पूर्ण

अटल पूर्णांक lt8912_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	अटल काष्ठा lt8912 *lt;
	पूर्णांक ret = 0;
	काष्ठा device *dev = &client->dev;

	lt = devm_kzalloc(dev, माप(काष्ठा lt8912), GFP_KERNEL);
	अगर (!lt)
		वापस -ENOMEM;

	lt->dev = dev;
	lt->i2c_client[0] = client;

	ret = lt8912_parse_dt(lt);
	अगर (ret)
		जाओ err_dt_parse;

	ret = lt8912_init_i2c(lt, client);
	अगर (ret)
		जाओ err_i2c;

	i2c_set_clientdata(client, lt);

	lt->bridge.funcs = &lt8912_bridge_funcs;
	lt->bridge.of_node = dev->of_node;
	lt->bridge.ops = (DRM_BRIDGE_OP_EDID |
			  DRM_BRIDGE_OP_DETECT);

	drm_bridge_add(&lt->bridge);

	वापस 0;

err_i2c:
	lt8912_put_dt(lt);
err_dt_parse:
	वापस ret;
पूर्ण

अटल पूर्णांक lt8912_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lt8912 *lt = i2c_get_clientdata(client);

	lt8912_bridge_detach(&lt->bridge);
	drm_bridge_हटाओ(&lt->bridge);
	lt8912_मुक्त_i2c(lt);
	lt8912_put_dt(lt);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lt8912_dt_match[] = अणु
	अणु.compatible = "lontium,lt8912b"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lt8912_dt_match);

अटल स्थिर काष्ठा i2c_device_id lt8912_id[] = अणु
	अणु"lt8912", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lt8912_id);

अटल काष्ठा i2c_driver lt8912_i2c_driver = अणु
	.driver = अणु
		.name = "lt8912",
		.of_match_table = lt8912_dt_match,
		.owner = THIS_MODULE,
	पूर्ण,
	.probe = lt8912_probe,
	.हटाओ = lt8912_हटाओ,
	.id_table = lt8912_id,
पूर्ण;
module_i2c_driver(lt8912_i2c_driver);

MODULE_AUTHOR("Adrien Grassein <adrien.grassein@gmail.com>");
MODULE_DESCRIPTION("lt8912 drm driver");
MODULE_LICENSE("GPL v2");
