<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018, The Linux Foundation. All rights reserved.
 * Copyright (c) 2019-2020. Linaro Limited.
 */

#समावेश <linux/firmware.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

#समावेश <sound/hdmi-codec.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>

#घोषणा EDID_BLOCK_SIZE	128
#घोषणा EDID_NUM_BLOCKS	2

काष्ठा lt9611uxc अणु
	काष्ठा device *dev;
	काष्ठा drm_bridge bridge;
	काष्ठा drm_connector connector;

	काष्ठा regmap *regmap;
	/* Protects all accesses to रेजिस्टरs by stopping the on-chip MCU */
	काष्ठा mutex ocm_lock;

	काष्ठा रुको_queue_head wq;
	काष्ठा work_काष्ठा work;

	काष्ठा device_node *dsi0_node;
	काष्ठा device_node *dsi1_node;
	काष्ठा mipi_dsi_device *dsi0;
	काष्ठा mipi_dsi_device *dsi1;
	काष्ठा platक्रमm_device *audio_pdev;

	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *enable_gpio;

	काष्ठा regulator_bulk_data supplies[2];

	काष्ठा i2c_client *client;

	bool hpd_supported;
	bool edid_पढ़ो;
	/* can be accessed from dअगरferent thपढ़ोs, so protect this with ocm_lock */
	bool hdmi_connected;
	uपूर्णांक8_t fw_version;
पूर्ण;

#घोषणा LT9611_PAGE_CONTROL	0xff

अटल स्थिर काष्ठा regmap_range_cfg lt9611uxc_ranges[] = अणु
	अणु
		.name = "register_range",
		.range_min =  0,
		.range_max = 0xd0ff,
		.selector_reg = LT9611_PAGE_CONTROL,
		.selector_mask = 0xff,
		.selector_shअगरt = 0,
		.winकरोw_start = 0,
		.winकरोw_len = 0x100,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config lt9611uxc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xffff,
	.ranges = lt9611uxc_ranges,
	.num_ranges = ARRAY_SIZE(lt9611uxc_ranges),
पूर्ण;

काष्ठा lt9611uxc_mode अणु
	u16 hdisplay;
	u16 vdisplay;
	u8 vrefresh;
पूर्ण;

/*
 * This chip supports only a fixed set of modes.
 * Enumerate them here to check whether the mode is supported.
 */
अटल काष्ठा lt9611uxc_mode lt9611uxc_modes[] = अणु
	अणु 1920, 1080, 60 पूर्ण,
	अणु 1920, 1080, 30 पूर्ण,
	अणु 1920, 1080, 25 पूर्ण,
	अणु 1366, 768, 60 पूर्ण,
	अणु 1360, 768, 60 पूर्ण,
	अणु 1280, 1024, 60 पूर्ण,
	अणु 1280, 800, 60 पूर्ण,
	अणु 1280, 720, 60 पूर्ण,
	अणु 1280, 720, 50 पूर्ण,
	अणु 1280, 720, 30 पूर्ण,
	अणु 1152, 864, 60 पूर्ण,
	अणु 1024, 768, 60 पूर्ण,
	अणु 800, 600, 60 पूर्ण,
	अणु 720, 576, 50 पूर्ण,
	अणु 720, 480, 60 पूर्ण,
	अणु 640, 480, 60 पूर्ण,
पूर्ण;

अटल काष्ठा lt9611uxc *bridge_to_lt9611uxc(काष्ठा drm_bridge *bridge)
अणु
	वापस container_of(bridge, काष्ठा lt9611uxc, bridge);
पूर्ण

अटल काष्ठा lt9611uxc *connector_to_lt9611uxc(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा lt9611uxc, connector);
पूर्ण

अटल व्योम lt9611uxc_lock(काष्ठा lt9611uxc *lt9611uxc)
अणु
	mutex_lock(&lt9611uxc->ocm_lock);
	regmap_ग_लिखो(lt9611uxc->regmap, 0x80ee, 0x01);
पूर्ण

अटल व्योम lt9611uxc_unlock(काष्ठा lt9611uxc *lt9611uxc)
अणु
	regmap_ग_लिखो(lt9611uxc->regmap, 0x80ee, 0x00);
	msleep(50);
	mutex_unlock(&lt9611uxc->ocm_lock);
पूर्ण

अटल irqवापस_t lt9611uxc_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lt9611uxc *lt9611uxc = dev_id;
	अचिन्हित पूर्णांक irq_status = 0;
	अचिन्हित पूर्णांक hpd_status = 0;

	lt9611uxc_lock(lt9611uxc);

	regmap_पढ़ो(lt9611uxc->regmap, 0xb022, &irq_status);
	regmap_पढ़ो(lt9611uxc->regmap, 0xb023, &hpd_status);
	अगर (irq_status)
		regmap_ग_लिखो(lt9611uxc->regmap, 0xb022, 0);

	अगर (irq_status & BIT(0)) अणु
		lt9611uxc->edid_पढ़ो = !!(hpd_status & BIT(0));
		wake_up_all(&lt9611uxc->wq);
	पूर्ण

	अगर (irq_status & BIT(1)) अणु
		lt9611uxc->hdmi_connected = hpd_status & BIT(1);
		schedule_work(&lt9611uxc->work);
	पूर्ण

	lt9611uxc_unlock(lt9611uxc);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम lt9611uxc_hpd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lt9611uxc *lt9611uxc = container_of(work, काष्ठा lt9611uxc, work);
	bool connected;

	अगर (lt9611uxc->connector.dev)
		drm_kms_helper_hotplug_event(lt9611uxc->connector.dev);
	अन्यथा अणु

		mutex_lock(&lt9611uxc->ocm_lock);
		connected = lt9611uxc->hdmi_connected;
		mutex_unlock(&lt9611uxc->ocm_lock);

		drm_bridge_hpd_notअगरy(&lt9611uxc->bridge,
				      connected ?
				      connector_status_connected :
				      connector_status_disconnected);
	पूर्ण
पूर्ण

अटल व्योम lt9611uxc_reset(काष्ठा lt9611uxc *lt9611uxc)
अणु
	gpiod_set_value_cansleep(lt9611uxc->reset_gpio, 1);
	msleep(20);

	gpiod_set_value_cansleep(lt9611uxc->reset_gpio, 0);
	msleep(20);

	gpiod_set_value_cansleep(lt9611uxc->reset_gpio, 1);
	msleep(300);
पूर्ण

अटल व्योम lt9611uxc_निश्चित_5v(काष्ठा lt9611uxc *lt9611uxc)
अणु
	अगर (!lt9611uxc->enable_gpio)
		वापस;

	gpiod_set_value_cansleep(lt9611uxc->enable_gpio, 1);
	msleep(20);
पूर्ण

अटल पूर्णांक lt9611uxc_regulator_init(काष्ठा lt9611uxc *lt9611uxc)
अणु
	पूर्णांक ret;

	lt9611uxc->supplies[0].supply = "vdd";
	lt9611uxc->supplies[1].supply = "vcc";

	ret = devm_regulator_bulk_get(lt9611uxc->dev, 2, lt9611uxc->supplies);
	अगर (ret < 0)
		वापस ret;

	वापस regulator_set_load(lt9611uxc->supplies[0].consumer, 200000);
पूर्ण

अटल पूर्णांक lt9611uxc_regulator_enable(काष्ठा lt9611uxc *lt9611uxc)
अणु
	पूर्णांक ret;

	ret = regulator_enable(lt9611uxc->supplies[0].consumer);
	अगर (ret < 0)
		वापस ret;

	usleep_range(1000, 10000); /* 50000 according to dtsi */

	ret = regulator_enable(lt9611uxc->supplies[1].consumer);
	अगर (ret < 0) अणु
		regulator_disable(lt9611uxc->supplies[0].consumer);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा lt9611uxc_mode *lt9611uxc_find_mode(स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lt9611uxc_modes); i++) अणु
		अगर (lt9611uxc_modes[i].hdisplay == mode->hdisplay &&
		    lt9611uxc_modes[i].vdisplay == mode->vdisplay &&
		    lt9611uxc_modes[i].vrefresh == drm_mode_vrefresh(mode)) अणु
			वापस &lt9611uxc_modes[i];
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mipi_dsi_device *lt9611uxc_attach_dsi(काष्ठा lt9611uxc *lt9611uxc,
						    काष्ठा device_node *dsi_node)
अणु
	स्थिर काष्ठा mipi_dsi_device_info info = अणु "lt9611uxc", 0, शून्य पूर्ण;
	काष्ठा mipi_dsi_device *dsi;
	काष्ठा mipi_dsi_host *host;
	पूर्णांक ret;

	host = of_find_mipi_dsi_host_by_node(dsi_node);
	अगर (!host) अणु
		dev_err(lt9611uxc->dev, "failed to find dsi host\n");
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	dsi = mipi_dsi_device_रेजिस्टर_full(host, &info);
	अगर (IS_ERR(dsi)) अणु
		dev_err(lt9611uxc->dev, "failed to create dsi device\n");
		वापस dsi;
	पूर्ण

	dsi->lanes = 4;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_SYNC_PULSE |
			  MIPI_DSI_MODE_VIDEO_HSE;

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0) अणु
		dev_err(lt9611uxc->dev, "failed to attach dsi to host\n");
		mipi_dsi_device_unरेजिस्टर(dsi);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस dsi;
पूर्ण

अटल पूर्णांक lt9611uxc_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा lt9611uxc *lt9611uxc = connector_to_lt9611uxc(connector);
	अचिन्हित पूर्णांक count;
	काष्ठा edid *edid;

	edid = lt9611uxc->bridge.funcs->get_edid(&lt9611uxc->bridge, connector);
	drm_connector_update_edid_property(connector, edid);
	count = drm_add_edid_modes(connector, edid);
	kमुक्त(edid);

	वापस count;
पूर्ण

अटल क्रमागत drm_connector_status lt9611uxc_connector_detect(काष्ठा drm_connector *connector,
							    bool क्रमce)
अणु
	काष्ठा lt9611uxc *lt9611uxc = connector_to_lt9611uxc(connector);

	वापस lt9611uxc->bridge.funcs->detect(&lt9611uxc->bridge);
पूर्ण

अटल क्रमागत drm_mode_status lt9611uxc_connector_mode_valid(काष्ठा drm_connector *connector,
							   काष्ठा drm_display_mode *mode)
अणु
	काष्ठा lt9611uxc_mode *lt9611uxc_mode = lt9611uxc_find_mode(mode);

	वापस lt9611uxc_mode ? MODE_OK : MODE_BAD;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs lt9611uxc_bridge_connector_helper_funcs = अणु
	.get_modes = lt9611uxc_connector_get_modes,
	.mode_valid = lt9611uxc_connector_mode_valid,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs lt9611uxc_bridge_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.detect = lt9611uxc_connector_detect,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक lt9611uxc_connector_init(काष्ठा drm_bridge *bridge, काष्ठा lt9611uxc *lt9611uxc)
अणु
	पूर्णांक ret;

	अगर (!bridge->encoder) अणु
		DRM_ERROR("Parent encoder object not found");
		वापस -ENODEV;
	पूर्ण

	drm_connector_helper_add(&lt9611uxc->connector,
				 &lt9611uxc_bridge_connector_helper_funcs);
	ret = drm_connector_init(bridge->dev, &lt9611uxc->connector,
				 &lt9611uxc_bridge_connector_funcs,
				 DRM_MODE_CONNECTOR_HDMIA);
	अगर (ret) अणु
		DRM_ERROR("Failed to initialize connector with drm\n");
		वापस ret;
	पूर्ण

	वापस drm_connector_attach_encoder(&lt9611uxc->connector, bridge->encoder);
पूर्ण

अटल व्योम lt9611uxc_bridge_detach(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt9611uxc *lt9611uxc = bridge_to_lt9611uxc(bridge);

	अगर (lt9611uxc->dsi1) अणु
		mipi_dsi_detach(lt9611uxc->dsi1);
		mipi_dsi_device_unरेजिस्टर(lt9611uxc->dsi1);
	पूर्ण

	mipi_dsi_detach(lt9611uxc->dsi0);
	mipi_dsi_device_unरेजिस्टर(lt9611uxc->dsi0);
पूर्ण

अटल पूर्णांक lt9611uxc_bridge_attach(काष्ठा drm_bridge *bridge,
				   क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा lt9611uxc *lt9611uxc = bridge_to_lt9611uxc(bridge);
	पूर्णांक ret;

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR)) अणु
		ret = lt9611uxc_connector_init(bridge, lt9611uxc);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Attach primary DSI */
	lt9611uxc->dsi0 = lt9611uxc_attach_dsi(lt9611uxc, lt9611uxc->dsi0_node);
	अगर (IS_ERR(lt9611uxc->dsi0))
		वापस PTR_ERR(lt9611uxc->dsi0);

	/* Attach secondary DSI, अगर specअगरied */
	अगर (lt9611uxc->dsi1_node) अणु
		lt9611uxc->dsi1 = lt9611uxc_attach_dsi(lt9611uxc, lt9611uxc->dsi1_node);
		अगर (IS_ERR(lt9611uxc->dsi1)) अणु
			ret = PTR_ERR(lt9611uxc->dsi1);
			जाओ err_unरेजिस्टर_dsi0;
		पूर्ण
	पूर्ण

	वापस 0;

err_unरेजिस्टर_dsi0:
	mipi_dsi_detach(lt9611uxc->dsi0);
	mipi_dsi_device_unरेजिस्टर(lt9611uxc->dsi0);

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status
lt9611uxc_bridge_mode_valid(काष्ठा drm_bridge *bridge,
			    स्थिर काष्ठा drm_display_info *info,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा lt9611uxc_mode *lt9611uxc_mode;

	lt9611uxc_mode = lt9611uxc_find_mode(mode);

	वापस lt9611uxc_mode ? MODE_OK : MODE_BAD;
पूर्ण

अटल व्योम lt9611uxc_video_setup(काष्ठा lt9611uxc *lt9611uxc,
				  स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 h_total, hactive, hsync_len, hfront_porch;
	u32 v_total, vactive, vsync_len, vfront_porch;

	h_total = mode->htotal;
	v_total = mode->vtotal;

	hactive = mode->hdisplay;
	hsync_len = mode->hsync_end - mode->hsync_start;
	hfront_porch = mode->hsync_start - mode->hdisplay;

	vactive = mode->vdisplay;
	vsync_len = mode->vsync_end - mode->vsync_start;
	vfront_porch = mode->vsync_start - mode->vdisplay;

	regmap_ग_लिखो(lt9611uxc->regmap, 0xd00d, (u8)(v_total / 256));
	regmap_ग_लिखो(lt9611uxc->regmap, 0xd00e, (u8)(v_total % 256));

	regmap_ग_लिखो(lt9611uxc->regmap, 0xd00f, (u8)(vactive / 256));
	regmap_ग_लिखो(lt9611uxc->regmap, 0xd010, (u8)(vactive % 256));

	regmap_ग_लिखो(lt9611uxc->regmap, 0xd011, (u8)(h_total / 256));
	regmap_ग_लिखो(lt9611uxc->regmap, 0xd012, (u8)(h_total % 256));

	regmap_ग_लिखो(lt9611uxc->regmap, 0xd013, (u8)(hactive / 256));
	regmap_ग_लिखो(lt9611uxc->regmap, 0xd014, (u8)(hactive % 256));

	regmap_ग_लिखो(lt9611uxc->regmap, 0xd015, (u8)(vsync_len % 256));

	regmap_update_bits(lt9611uxc->regmap, 0xd016, 0xf, (u8)(hsync_len / 256));
	regmap_ग_लिखो(lt9611uxc->regmap, 0xd017, (u8)(hsync_len % 256));

	regmap_update_bits(lt9611uxc->regmap, 0xd018, 0xf, (u8)(vfront_porch / 256));
	regmap_ग_लिखो(lt9611uxc->regmap, 0xd019, (u8)(vfront_porch % 256));

	regmap_update_bits(lt9611uxc->regmap, 0xd01a, 0xf, (u8)(hfront_porch / 256));
	regmap_ग_लिखो(lt9611uxc->regmap, 0xd01b, (u8)(hfront_porch % 256));
पूर्ण

अटल व्योम lt9611uxc_bridge_mode_set(काष्ठा drm_bridge *bridge,
				      स्थिर काष्ठा drm_display_mode *mode,
				      स्थिर काष्ठा drm_display_mode *adj_mode)
अणु
	काष्ठा lt9611uxc *lt9611uxc = bridge_to_lt9611uxc(bridge);

	lt9611uxc_lock(lt9611uxc);
	lt9611uxc_video_setup(lt9611uxc, mode);
	lt9611uxc_unlock(lt9611uxc);
पूर्ण

अटल क्रमागत drm_connector_status lt9611uxc_bridge_detect(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा lt9611uxc *lt9611uxc = bridge_to_lt9611uxc(bridge);
	अचिन्हित पूर्णांक reg_val = 0;
	पूर्णांक ret;
	bool connected = true;

	lt9611uxc_lock(lt9611uxc);

	अगर (lt9611uxc->hpd_supported) अणु
		ret = regmap_पढ़ो(lt9611uxc->regmap, 0xb023, &reg_val);

		अगर (ret)
			dev_err(lt9611uxc->dev, "failed to read hpd status: %d\n", ret);
		अन्यथा
			connected  = reg_val & BIT(1);
	पूर्ण
	lt9611uxc->hdmi_connected = connected;

	lt9611uxc_unlock(lt9611uxc);

	वापस connected ?  connector_status_connected :
				connector_status_disconnected;
पूर्ण

अटल पूर्णांक lt9611uxc_रुको_क्रम_edid(काष्ठा lt9611uxc *lt9611uxc)
अणु
	वापस रुको_event_पूर्णांकerruptible_समयout(lt9611uxc->wq, lt9611uxc->edid_पढ़ो,
			msecs_to_jअगरfies(500));
पूर्ण

अटल पूर्णांक lt9611uxc_get_edid_block(व्योम *data, u8 *buf, अचिन्हित पूर्णांक block, माप_प्रकार len)
अणु
	काष्ठा lt9611uxc *lt9611uxc = data;
	पूर्णांक ret;

	अगर (len > EDID_BLOCK_SIZE)
		वापस -EINVAL;

	अगर (block >= EDID_NUM_BLOCKS)
		वापस -EINVAL;

	lt9611uxc_lock(lt9611uxc);

	regmap_ग_लिखो(lt9611uxc->regmap, 0xb00b, 0x10);

	regmap_ग_लिखो(lt9611uxc->regmap, 0xb00a, block * EDID_BLOCK_SIZE);

	ret = regmap_noinc_पढ़ो(lt9611uxc->regmap, 0xb0b0, buf, len);
	अगर (ret)
		dev_err(lt9611uxc->dev, "edid read failed: %d\n", ret);

	lt9611uxc_unlock(lt9611uxc);

	वापस 0;
पूर्ण;

अटल काष्ठा edid *lt9611uxc_bridge_get_edid(काष्ठा drm_bridge *bridge,
					      काष्ठा drm_connector *connector)
अणु
	काष्ठा lt9611uxc *lt9611uxc = bridge_to_lt9611uxc(bridge);
	पूर्णांक ret;

	ret = lt9611uxc_रुको_क्रम_edid(lt9611uxc);
	अगर (ret < 0) अणु
		dev_err(lt9611uxc->dev, "wait for EDID failed: %d\n", ret);
		वापस शून्य;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		dev_err(lt9611uxc->dev, "wait for EDID timeout\n");
		वापस शून्य;
	पूर्ण

	वापस drm_करो_get_edid(connector, lt9611uxc_get_edid_block, lt9611uxc);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs lt9611uxc_bridge_funcs = अणु
	.attach = lt9611uxc_bridge_attach,
	.detach = lt9611uxc_bridge_detach,
	.mode_valid = lt9611uxc_bridge_mode_valid,
	.mode_set = lt9611uxc_bridge_mode_set,
	.detect = lt9611uxc_bridge_detect,
	.get_edid = lt9611uxc_bridge_get_edid,
पूर्ण;

अटल पूर्णांक lt9611uxc_parse_dt(काष्ठा device *dev,
			      काष्ठा lt9611uxc *lt9611uxc)
अणु
	lt9611uxc->dsi0_node = of_graph_get_remote_node(dev->of_node, 0, -1);
	अगर (!lt9611uxc->dsi0_node) अणु
		dev_err(lt9611uxc->dev, "failed to get remote node for primary dsi\n");
		वापस -ENODEV;
	पूर्ण

	lt9611uxc->dsi1_node = of_graph_get_remote_node(dev->of_node, 1, -1);

	वापस 0;
पूर्ण

अटल पूर्णांक lt9611uxc_gpio_init(काष्ठा lt9611uxc *lt9611uxc)
अणु
	काष्ठा device *dev = lt9611uxc->dev;

	lt9611uxc->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(lt9611uxc->reset_gpio)) अणु
		dev_err(dev, "failed to acquire reset gpio\n");
		वापस PTR_ERR(lt9611uxc->reset_gpio);
	पूर्ण

	lt9611uxc->enable_gpio = devm_gpiod_get_optional(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(lt9611uxc->enable_gpio)) अणु
		dev_err(dev, "failed to acquire enable gpio\n");
		वापस PTR_ERR(lt9611uxc->enable_gpio);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lt9611uxc_पढ़ो_device_rev(काष्ठा lt9611uxc *lt9611uxc)
अणु
	अचिन्हित पूर्णांक rev0, rev1, rev2;
	पूर्णांक ret;

	lt9611uxc_lock(lt9611uxc);

	ret = regmap_पढ़ो(lt9611uxc->regmap, 0x8100, &rev0);
	ret |= regmap_पढ़ो(lt9611uxc->regmap, 0x8101, &rev1);
	ret |= regmap_पढ़ो(lt9611uxc->regmap, 0x8102, &rev2);
	अगर (ret)
		dev_err(lt9611uxc->dev, "failed to read revision: %d\n", ret);
	अन्यथा
		dev_info(lt9611uxc->dev, "LT9611 revision: 0x%02x.%02x.%02x\n", rev0, rev1, rev2);

	lt9611uxc_unlock(lt9611uxc);

	वापस ret;
पूर्ण

अटल पूर्णांक lt9611uxc_पढ़ो_version(काष्ठा lt9611uxc *lt9611uxc)
अणु
	अचिन्हित पूर्णांक rev;
	पूर्णांक ret;

	lt9611uxc_lock(lt9611uxc);

	ret = regmap_पढ़ो(lt9611uxc->regmap, 0xb021, &rev);
	अगर (ret)
		dev_err(lt9611uxc->dev, "failed to read revision: %d\n", ret);
	अन्यथा
		dev_info(lt9611uxc->dev, "LT9611 version: 0x%02x\n", rev);

	lt9611uxc_unlock(lt9611uxc);

	वापस ret < 0 ? ret : rev;
पूर्ण

अटल पूर्णांक lt9611uxc_hdmi_hw_params(काष्ठा device *dev, व्योम *data,
				    काष्ठा hdmi_codec_daअगरmt *fmt,
				    काष्ठा hdmi_codec_params *hparms)
अणु
	/*
	 * LT9611UXC will स्वतःmatically detect rate and sample size, so no need
	 * to setup anything here.
	 */
	वापस 0;
पूर्ण

अटल व्योम lt9611uxc_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
पूर्ण

अटल पूर्णांक lt9611uxc_hdmi_i2s_get_dai_id(काष्ठा snd_soc_component *component,
					 काष्ठा device_node *endpoपूर्णांक)
अणु
	काष्ठा of_endpoपूर्णांक of_ep;
	पूर्णांक ret;

	ret = of_graph_parse_endpoपूर्णांक(endpoपूर्णांक, &of_ep);
	अगर (ret < 0)
		वापस ret;

	/*
	 * HDMI sound should be located as reg = <2>
	 * Then, it is sound port 0
	 */
	अगर (of_ep.port == 2)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops lt9611uxc_codec_ops = अणु
	.hw_params	= lt9611uxc_hdmi_hw_params,
	.audio_shutकरोwn = lt9611uxc_audio_shutकरोwn,
	.get_dai_id	= lt9611uxc_hdmi_i2s_get_dai_id,
पूर्ण;

अटल पूर्णांक lt9611uxc_audio_init(काष्ठा device *dev, काष्ठा lt9611uxc *lt9611uxc)
अणु
	काष्ठा hdmi_codec_pdata codec_data = अणु
		.ops = &lt9611uxc_codec_ops,
		.max_i2s_channels = 2,
		.i2s = 1,
		.data = lt9611uxc,
	पूर्ण;

	lt9611uxc->audio_pdev =
		platक्रमm_device_रेजिस्टर_data(dev, HDMI_CODEC_DRV_NAME,
					      PLATFORM_DEVID_AUTO,
					      &codec_data, माप(codec_data));

	वापस PTR_ERR_OR_ZERO(lt9611uxc->audio_pdev);
पूर्ण

अटल व्योम lt9611uxc_audio_निकास(काष्ठा lt9611uxc *lt9611uxc)
अणु
	अगर (lt9611uxc->audio_pdev) अणु
		platक्रमm_device_unरेजिस्टर(lt9611uxc->audio_pdev);
		lt9611uxc->audio_pdev = शून्य;
	पूर्ण
पूर्ण

#घोषणा LT9611UXC_FW_PAGE_SIZE 32
अटल व्योम lt9611uxc_firmware_ग_लिखो_page(काष्ठा lt9611uxc *lt9611uxc, u16 addr, स्थिर u8 *buf)
अणु
	काष्ठा reg_sequence seq_ग_लिखो_prepare[] = अणु
		REG_SEQ0(0x805a, 0x04),
		REG_SEQ0(0x805a, 0x00),

		REG_SEQ0(0x805e, 0xdf),
		REG_SEQ0(0x805a, 0x20),
		REG_SEQ0(0x805a, 0x00),
		REG_SEQ0(0x8058, 0x21),
	पूर्ण;

	काष्ठा reg_sequence seq_ग_लिखो_addr[] = अणु
		REG_SEQ0(0x805b, (addr >> 16) & 0xff),
		REG_SEQ0(0x805c, (addr >> 8) & 0xff),
		REG_SEQ0(0x805d, addr & 0xff),
		REG_SEQ0(0x805a, 0x10),
		REG_SEQ0(0x805a, 0x00),
	पूर्ण;

	regmap_ग_लिखो(lt9611uxc->regmap, 0x8108, 0xbf);
	msleep(20);
	regmap_ग_लिखो(lt9611uxc->regmap, 0x8108, 0xff);
	msleep(20);
	regmap_multi_reg_ग_लिखो(lt9611uxc->regmap, seq_ग_लिखो_prepare, ARRAY_SIZE(seq_ग_लिखो_prepare));
	regmap_noinc_ग_लिखो(lt9611uxc->regmap, 0x8059, buf, LT9611UXC_FW_PAGE_SIZE);
	regmap_multi_reg_ग_लिखो(lt9611uxc->regmap, seq_ग_लिखो_addr, ARRAY_SIZE(seq_ग_लिखो_addr));
	msleep(20);
पूर्ण

अटल व्योम lt9611uxc_firmware_पढ़ो_page(काष्ठा lt9611uxc *lt9611uxc, u16 addr, अक्षर *buf)
अणु
	काष्ठा reg_sequence seq_पढ़ो_page[] = अणु
		REG_SEQ0(0x805a, 0xa0),
		REG_SEQ0(0x805a, 0x80),
		REG_SEQ0(0x805b, (addr >> 16) & 0xff),
		REG_SEQ0(0x805c, (addr >> 8) & 0xff),
		REG_SEQ0(0x805d, addr & 0xff),
		REG_SEQ0(0x805a, 0x90),
		REG_SEQ0(0x805a, 0x80),
		REG_SEQ0(0x8058, 0x21),
	पूर्ण;

	regmap_multi_reg_ग_लिखो(lt9611uxc->regmap, seq_पढ़ो_page, ARRAY_SIZE(seq_पढ़ो_page));
	regmap_noinc_पढ़ो(lt9611uxc->regmap, 0x805f, buf, LT9611UXC_FW_PAGE_SIZE);
पूर्ण

अटल अक्षर *lt9611uxc_firmware_पढ़ो(काष्ठा lt9611uxc *lt9611uxc, माप_प्रकार size)
अणु
	काष्ठा reg_sequence seq_पढ़ो_setup[] = अणु
		REG_SEQ0(0x805a, 0x84),
		REG_SEQ0(0x805a, 0x80),
	पूर्ण;

	अक्षर *पढ़ोbuf;
	u16 offset;

	पढ़ोbuf = kzalloc(ALIGN(size, 32), GFP_KERNEL);
	अगर (!पढ़ोbuf)
		वापस शून्य;

	regmap_multi_reg_ग_लिखो(lt9611uxc->regmap, seq_पढ़ो_setup, ARRAY_SIZE(seq_पढ़ो_setup));

	क्रम (offset = 0;
	     offset < size;
	     offset += LT9611UXC_FW_PAGE_SIZE)
		lt9611uxc_firmware_पढ़ो_page(lt9611uxc, offset, &पढ़ोbuf[offset]);

	वापस पढ़ोbuf;
पूर्ण

अटल पूर्णांक lt9611uxc_firmware_update(काष्ठा lt9611uxc *lt9611uxc)
अणु
	पूर्णांक ret;
	u16 offset;
	माप_प्रकार reमुख्य;
	अक्षर *पढ़ोbuf;
	स्थिर काष्ठा firmware *fw;

	काष्ठा reg_sequence seq_setup[] = अणु
		REG_SEQ0(0x805e, 0xdf),
		REG_SEQ0(0x8058, 0x00),
		REG_SEQ0(0x8059, 0x50),
		REG_SEQ0(0x805a, 0x10),
		REG_SEQ0(0x805a, 0x00),
	पूर्ण;


	काष्ठा reg_sequence seq_block_erase[] = अणु
		REG_SEQ0(0x805a, 0x04),
		REG_SEQ0(0x805a, 0x00),
		REG_SEQ0(0x805b, 0x00),
		REG_SEQ0(0x805c, 0x00),
		REG_SEQ0(0x805d, 0x00),
		REG_SEQ0(0x805a, 0x01),
		REG_SEQ0(0x805a, 0x00),
	पूर्ण;

	ret = request_firmware(&fw, "lt9611uxc_fw.bin", lt9611uxc->dev);
	अगर (ret < 0)
		वापस ret;

	dev_info(lt9611uxc->dev, "Updating firmware\n");
	lt9611uxc_lock(lt9611uxc);

	regmap_multi_reg_ग_लिखो(lt9611uxc->regmap, seq_setup, ARRAY_SIZE(seq_setup));

	/*
	 * Need erase block 2 बारs here. Someबार, block erase can fail.
	 * This is a workaroud.
	 */
	regmap_multi_reg_ग_लिखो(lt9611uxc->regmap, seq_block_erase, ARRAY_SIZE(seq_block_erase));
	msleep(3000);
	regmap_multi_reg_ग_लिखो(lt9611uxc->regmap, seq_block_erase, ARRAY_SIZE(seq_block_erase));
	msleep(3000);

	क्रम (offset = 0, reमुख्य = fw->size;
	     reमुख्य >= LT9611UXC_FW_PAGE_SIZE;
	     offset += LT9611UXC_FW_PAGE_SIZE, reमुख्य -= LT9611UXC_FW_PAGE_SIZE)
		lt9611uxc_firmware_ग_लिखो_page(lt9611uxc, offset, fw->data + offset);

	अगर (reमुख्य > 0) अणु
		अक्षर buf[LT9611UXC_FW_PAGE_SIZE];

		स_रखो(buf, 0xff, LT9611UXC_FW_PAGE_SIZE);
		स_नकल(buf, fw->data + offset, reमुख्य);
		lt9611uxc_firmware_ग_लिखो_page(lt9611uxc, offset, buf);
	पूर्ण
	msleep(20);

	पढ़ोbuf = lt9611uxc_firmware_पढ़ो(lt9611uxc, fw->size);
	अगर (!पढ़ोbuf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (!स_भेद(पढ़ोbuf, fw->data, fw->size)) अणु
		dev_err(lt9611uxc->dev, "Firmware update failed\n");
		prपूर्णांक_hex_dump(KERN_ERR, "fw: ", DUMP_PREFIX_OFFSET, 16, 1, पढ़ोbuf, fw->size, false);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		dev_info(lt9611uxc->dev, "Firmware updates successfully\n");
		ret = 0;
	पूर्ण
	kमुक्त(पढ़ोbuf);

out:
	lt9611uxc_unlock(lt9611uxc);
	lt9611uxc_reset(lt9611uxc);
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार lt9611uxc_firmware_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lt9611uxc *lt9611uxc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = lt9611uxc_firmware_update(lt9611uxc);
	अगर (ret < 0)
		वापस ret;
	वापस len;
पूर्ण

अटल sमाप_प्रकार lt9611uxc_firmware_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lt9611uxc *lt9611uxc = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%02x\n", lt9611uxc->fw_version);
पूर्ण

अटल DEVICE_ATTR_RW(lt9611uxc_firmware);

अटल काष्ठा attribute *lt9611uxc_attrs[] = अणु
	&dev_attr_lt9611uxc_firmware.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lt9611uxc_attr_group = अणु
	.attrs = lt9611uxc_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *lt9611uxc_attr_groups[] = अणु
	&lt9611uxc_attr_group,
	शून्य,
पूर्ण;

अटल पूर्णांक lt9611uxc_probe(काष्ठा i2c_client *client,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lt9611uxc *lt9611uxc;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;
	bool fw_updated = false;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(dev, "device doesn't support I2C\n");
		वापस -ENODEV;
	पूर्ण

	lt9611uxc = devm_kzalloc(dev, माप(*lt9611uxc), GFP_KERNEL);
	अगर (!lt9611uxc)
		वापस -ENOMEM;

	lt9611uxc->dev = &client->dev;
	lt9611uxc->client = client;
	mutex_init(&lt9611uxc->ocm_lock);

	lt9611uxc->regmap = devm_regmap_init_i2c(client, &lt9611uxc_regmap_config);
	अगर (IS_ERR(lt9611uxc->regmap)) अणु
		dev_err(lt9611uxc->dev, "regmap i2c init failed\n");
		वापस PTR_ERR(lt9611uxc->regmap);
	पूर्ण

	ret = lt9611uxc_parse_dt(&client->dev, lt9611uxc);
	अगर (ret) अणु
		dev_err(dev, "failed to parse device tree\n");
		वापस ret;
	पूर्ण

	ret = lt9611uxc_gpio_init(lt9611uxc);
	अगर (ret < 0)
		जाओ err_of_put;

	ret = lt9611uxc_regulator_init(lt9611uxc);
	अगर (ret < 0)
		जाओ err_of_put;

	lt9611uxc_निश्चित_5v(lt9611uxc);

	ret = lt9611uxc_regulator_enable(lt9611uxc);
	अगर (ret)
		जाओ err_of_put;

	lt9611uxc_reset(lt9611uxc);

	ret = lt9611uxc_पढ़ो_device_rev(lt9611uxc);
	अगर (ret) अणु
		dev_err(dev, "failed to read chip rev\n");
		जाओ err_disable_regulators;
	पूर्ण

retry:
	ret = lt9611uxc_पढ़ो_version(lt9611uxc);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to read FW version\n");
		जाओ err_disable_regulators;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		अगर (!fw_updated) अणु
			fw_updated = true;
			dev_err(dev, "FW version 0, enforcing firmware update\n");
			ret = lt9611uxc_firmware_update(lt9611uxc);
			अगर (ret < 0)
				जाओ err_disable_regulators;
			अन्यथा
				जाओ retry;
		पूर्ण अन्यथा अणु
			dev_err(dev, "FW version 0, update failed\n");
			ret = -EOPNOTSUPP;
			जाओ err_disable_regulators;
		पूर्ण
	पूर्ण अन्यथा अगर (ret < 0x40) अणु
		dev_info(dev, "FW version 0x%x, HPD not supported\n", ret);
	पूर्ण अन्यथा अणु
		lt9611uxc->hpd_supported = true;
	पूर्ण
	lt9611uxc->fw_version = ret;

	init_रुकोqueue_head(&lt9611uxc->wq);
	INIT_WORK(&lt9611uxc->work, lt9611uxc_hpd_work);

	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
					lt9611uxc_irq_thपढ़ो_handler,
					IRQF_ONESHOT, "lt9611uxc", lt9611uxc);
	अगर (ret) अणु
		dev_err(dev, "failed to request irq\n");
		जाओ err_disable_regulators;
	पूर्ण

	i2c_set_clientdata(client, lt9611uxc);

	lt9611uxc->bridge.funcs = &lt9611uxc_bridge_funcs;
	lt9611uxc->bridge.of_node = client->dev.of_node;
	lt9611uxc->bridge.ops = DRM_BRIDGE_OP_DETECT | DRM_BRIDGE_OP_EDID;
	अगर (lt9611uxc->hpd_supported)
		lt9611uxc->bridge.ops |= DRM_BRIDGE_OP_HPD;
	lt9611uxc->bridge.type = DRM_MODE_CONNECTOR_HDMIA;

	drm_bridge_add(&lt9611uxc->bridge);

	वापस lt9611uxc_audio_init(dev, lt9611uxc);

err_disable_regulators:
	regulator_bulk_disable(ARRAY_SIZE(lt9611uxc->supplies), lt9611uxc->supplies);

err_of_put:
	of_node_put(lt9611uxc->dsi1_node);
	of_node_put(lt9611uxc->dsi0_node);

	वापस ret;
पूर्ण

अटल पूर्णांक lt9611uxc_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lt9611uxc *lt9611uxc = i2c_get_clientdata(client);

	disable_irq(client->irq);
	flush_scheduled_work();
	lt9611uxc_audio_निकास(lt9611uxc);
	drm_bridge_हटाओ(&lt9611uxc->bridge);

	mutex_destroy(&lt9611uxc->ocm_lock);

	regulator_bulk_disable(ARRAY_SIZE(lt9611uxc->supplies), lt9611uxc->supplies);

	of_node_put(lt9611uxc->dsi1_node);
	of_node_put(lt9611uxc->dsi0_node);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_device_id lt9611uxc_id[] = अणु
	अणु "lontium,lt9611uxc", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id lt9611uxc_match_table[] = अणु
	अणु .compatible = "lontium,lt9611uxc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lt9611uxc_match_table);

अटल काष्ठा i2c_driver lt9611uxc_driver = अणु
	.driver = अणु
		.name = "lt9611uxc",
		.of_match_table = lt9611uxc_match_table,
		.dev_groups = lt9611uxc_attr_groups,
	पूर्ण,
	.probe = lt9611uxc_probe,
	.हटाओ = lt9611uxc_हटाओ,
	.id_table = lt9611uxc_id,
पूर्ण;
module_i2c_driver(lt9611uxc_driver);

MODULE_AUTHOR("Dmitry Baryshkov <dmitry.baryshkov@linaro.org>");
MODULE_LICENSE("GPL v2");
