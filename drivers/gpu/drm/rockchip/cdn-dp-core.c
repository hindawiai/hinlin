<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Chris Zhong <zyw@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/extcon.h>
#समावेश <linux/firmware.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <sound/hdmi-codec.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "cdn-dp-core.h"
#समावेश "cdn-dp-reg.h"
#समावेश "rockchip_drm_vop.h"

#घोषणा connector_to_dp(c) \
		container_of(c, काष्ठा cdn_dp_device, connector)

#घोषणा encoder_to_dp(c) \
		container_of(c, काष्ठा cdn_dp_device, encoder)

#घोषणा GRF_SOC_CON9		0x6224
#घोषणा DP_SEL_VOP_LIT		BIT(12)
#घोषणा GRF_SOC_CON26		0x6268
#घोषणा DPTX_HPD_SEL		(3 << 12)
#घोषणा DPTX_HPD_DEL		(2 << 12)
#घोषणा DPTX_HPD_SEL_MASK	(3 << 28)

#घोषणा CDN_FW_TIMEOUT_MS	(64 * 1000)
#घोषणा CDN_DPCD_TIMEOUT_MS	5000
#घोषणा CDN_DP_FIRMWARE		"rockchip/dptx.bin"

काष्ठा cdn_dp_data अणु
	u8 max_phy;
पूर्ण;

काष्ठा cdn_dp_data rk3399_cdn_dp = अणु
	.max_phy = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cdn_dp_dt_ids[] = अणु
	अणु .compatible = "rockchip,rk3399-cdn-dp",
		.data = (व्योम *)&rk3399_cdn_dp पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, cdn_dp_dt_ids);

अटल पूर्णांक cdn_dp_grf_ग_लिखो(काष्ठा cdn_dp_device *dp,
			    अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(dp->grf_clk);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to prepare_enable grf clock\n");
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(dp->grf, reg, val);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Could not write to GRF: %d\n", ret);
		वापस ret;
	पूर्ण

	clk_disable_unprepare(dp->grf_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_clk_enable(काष्ठा cdn_dp_device *dp)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ rate;

	ret = clk_prepare_enable(dp->pclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dp->dev, "cannot enable dp pclk %d\n", ret);
		जाओ err_pclk;
	पूर्ण

	ret = clk_prepare_enable(dp->core_clk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dp->dev, "cannot enable core_clk %d\n", ret);
		जाओ err_core_clk;
	पूर्ण

	ret = pm_runसमय_get_sync(dp->dev);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dp->dev, "cannot get pm runtime %d\n", ret);
		जाओ err_pm_runसमय_get;
	पूर्ण

	reset_control_निश्चित(dp->core_rst);
	reset_control_निश्चित(dp->dptx_rst);
	reset_control_निश्चित(dp->apb_rst);
	reset_control_deनिश्चित(dp->core_rst);
	reset_control_deनिश्चित(dp->dptx_rst);
	reset_control_deनिश्चित(dp->apb_rst);

	rate = clk_get_rate(dp->core_clk);
	अगर (!rate) अणु
		DRM_DEV_ERROR(dp->dev, "get clk rate failed\n");
		ret = -EINVAL;
		जाओ err_set_rate;
	पूर्ण

	cdn_dp_set_fw_clk(dp, rate);
	cdn_dp_घड़ी_reset(dp);

	वापस 0;

err_set_rate:
	pm_runसमय_put(dp->dev);
err_pm_runसमय_get:
	clk_disable_unprepare(dp->core_clk);
err_core_clk:
	clk_disable_unprepare(dp->pclk);
err_pclk:
	वापस ret;
पूर्ण

अटल व्योम cdn_dp_clk_disable(काष्ठा cdn_dp_device *dp)
अणु
	pm_runसमय_put_sync(dp->dev);
	clk_disable_unprepare(dp->pclk);
	clk_disable_unprepare(dp->core_clk);
पूर्ण

अटल पूर्णांक cdn_dp_get_port_lanes(काष्ठा cdn_dp_port *port)
अणु
	काष्ठा extcon_dev *edev = port->extcon;
	जोड़ extcon_property_value property;
	पूर्णांक dptx;
	u8 lanes;

	dptx = extcon_get_state(edev, EXTCON_DISP_DP);
	अगर (dptx > 0) अणु
		extcon_get_property(edev, EXTCON_DISP_DP,
				    EXTCON_PROP_USB_SS, &property);
		अगर (property.पूर्णांकval)
			lanes = 2;
		अन्यथा
			lanes = 4;
	पूर्ण अन्यथा अणु
		lanes = 0;
	पूर्ण

	वापस lanes;
पूर्ण

अटल पूर्णांक cdn_dp_get_sink_count(काष्ठा cdn_dp_device *dp, u8 *sink_count)
अणु
	पूर्णांक ret;
	u8 value;

	*sink_count = 0;
	ret = cdn_dp_dpcd_पढ़ो(dp, DP_SINK_COUNT, &value, 1);
	अगर (ret)
		वापस ret;

	*sink_count = DP_GET_SINK_COUNT(value);
	वापस 0;
पूर्ण

अटल काष्ठा cdn_dp_port *cdn_dp_connected_port(काष्ठा cdn_dp_device *dp)
अणु
	काष्ठा cdn_dp_port *port;
	पूर्णांक i, lanes;

	क्रम (i = 0; i < dp->ports; i++) अणु
		port = dp->port[i];
		lanes = cdn_dp_get_port_lanes(port);
		अगर (lanes)
			वापस port;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल bool cdn_dp_check_sink_connection(काष्ठा cdn_dp_device *dp)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(CDN_DPCD_TIMEOUT_MS);
	काष्ठा cdn_dp_port *port;
	u8 sink_count = 0;

	अगर (dp->active_port < 0 || dp->active_port >= dp->ports) अणु
		DRM_DEV_ERROR(dp->dev, "active_port is wrong!\n");
		वापस false;
	पूर्ण

	port = dp->port[dp->active_port];

	/*
	 * Attempt to पढ़ो sink count, retry in हाल the sink may not be पढ़ोy.
	 *
	 * Sinks are *supposed* to come up within 1ms from an off state, but
	 * some करोcks need more समय to घातer up.
	 */
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (!extcon_get_state(port->extcon, EXTCON_DISP_DP))
			वापस false;

		अगर (!cdn_dp_get_sink_count(dp, &sink_count))
			वापस sink_count ? true : false;

		usleep_range(5000, 10000);
	पूर्ण

	DRM_DEV_ERROR(dp->dev, "Get sink capability timed out\n");
	वापस false;
पूर्ण

अटल क्रमागत drm_connector_status
cdn_dp_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा cdn_dp_device *dp = connector_to_dp(connector);
	क्रमागत drm_connector_status status = connector_status_disconnected;

	mutex_lock(&dp->lock);
	अगर (dp->connected)
		status = connector_status_connected;
	mutex_unlock(&dp->lock);

	वापस status;
पूर्ण

अटल व्योम cdn_dp_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs cdn_dp_atomic_connector_funcs = अणु
	.detect = cdn_dp_connector_detect,
	.destroy = cdn_dp_connector_destroy,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक cdn_dp_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा cdn_dp_device *dp = connector_to_dp(connector);
	काष्ठा edid *edid;
	पूर्णांक ret = 0;

	mutex_lock(&dp->lock);
	edid = dp->edid;
	अगर (edid) अणु
		DRM_DEV_DEBUG_KMS(dp->dev, "got edid: width[%d] x height[%d]\n",
				  edid->width_cm, edid->height_cm);

		dp->sink_has_audio = drm_detect_monitor_audio(edid);
		ret = drm_add_edid_modes(connector, edid);
		अगर (ret)
			drm_connector_update_edid_property(connector,
								edid);
	पूर्ण
	mutex_unlock(&dp->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cdn_dp_connector_mode_valid(काष्ठा drm_connector *connector,
				       काष्ठा drm_display_mode *mode)
अणु
	काष्ठा cdn_dp_device *dp = connector_to_dp(connector);
	काष्ठा drm_display_info *display_info = &dp->connector.display_info;
	u32 requested, actual, rate, sink_max, source_max = 0;
	u8 lanes, bpc;

	/* If DP is disconnected, every mode is invalid */
	अगर (!dp->connected)
		वापस MODE_BAD;

	चयन (display_info->bpc) अणु
	हाल 10:
		bpc = 10;
		अवरोध;
	हाल 6:
		bpc = 6;
		अवरोध;
	शेष:
		bpc = 8;
		अवरोध;
	पूर्ण

	requested = mode->घड़ी * bpc * 3 / 1000;

	source_max = dp->lanes;
	sink_max = drm_dp_max_lane_count(dp->dpcd);
	lanes = min(source_max, sink_max);

	source_max = drm_dp_bw_code_to_link_rate(CDN_DP_MAX_LINK_RATE);
	sink_max = drm_dp_max_link_rate(dp->dpcd);
	rate = min(source_max, sink_max);

	actual = rate * lanes / 100;

	/* efficiency is about 0.8 */
	actual = actual * 8 / 10;

	अगर (requested > actual) अणु
		DRM_DEV_DEBUG_KMS(dp->dev,
				  "requested=%d, actual=%d, clock=%d\n",
				  requested, actual, mode->घड़ी);
		वापस MODE_CLOCK_HIGH;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल काष्ठा drm_connector_helper_funcs cdn_dp_connector_helper_funcs = अणु
	.get_modes = cdn_dp_connector_get_modes,
	.mode_valid = cdn_dp_connector_mode_valid,
पूर्ण;

अटल पूर्णांक cdn_dp_firmware_init(काष्ठा cdn_dp_device *dp)
अणु
	पूर्णांक ret;
	स्थिर u32 *iram_data, *dram_data;
	स्थिर काष्ठा firmware *fw = dp->fw;
	स्थिर काष्ठा cdn_firmware_header *hdr;

	hdr = (काष्ठा cdn_firmware_header *)fw->data;
	अगर (fw->size != le32_to_cpu(hdr->size_bytes)) अणु
		DRM_DEV_ERROR(dp->dev, "firmware is invalid\n");
		वापस -EINVAL;
	पूर्ण

	iram_data = (स्थिर u32 *)(fw->data + hdr->header_size);
	dram_data = (स्थिर u32 *)(fw->data + hdr->header_size + hdr->iram_size);

	ret = cdn_dp_load_firmware(dp, iram_data, hdr->iram_size,
				   dram_data, hdr->dram_size);
	अगर (ret)
		वापस ret;

	ret = cdn_dp_set_firmware_active(dp, true);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "active ucpu failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस cdn_dp_event_config(dp);
पूर्ण

अटल पूर्णांक cdn_dp_get_sink_capability(काष्ठा cdn_dp_device *dp)
अणु
	पूर्णांक ret;

	अगर (!cdn_dp_check_sink_connection(dp))
		वापस -ENODEV;

	ret = cdn_dp_dpcd_पढ़ो(dp, DP_DPCD_REV, dp->dpcd,
			       DP_RECEIVER_CAP_SIZE);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to get caps %d\n", ret);
		वापस ret;
	पूर्ण

	kमुक्त(dp->edid);
	dp->edid = drm_करो_get_edid(&dp->connector,
				   cdn_dp_get_edid_block, dp);
	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_enable_phy(काष्ठा cdn_dp_device *dp, काष्ठा cdn_dp_port *port)
अणु
	जोड़ extcon_property_value property;
	पूर्णांक ret;

	अगर (!port->phy_enabled) अणु
		ret = phy_घातer_on(port->phy);
		अगर (ret) अणु
			DRM_DEV_ERROR(dp->dev, "phy power on failed: %d\n",
				      ret);
			जाओ err_phy;
		पूर्ण
		port->phy_enabled = true;
	पूर्ण

	ret = cdn_dp_grf_ग_लिखो(dp, GRF_SOC_CON26,
			       DPTX_HPD_SEL_MASK | DPTX_HPD_SEL);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to write HPD_SEL %d\n", ret);
		जाओ err_घातer_on;
	पूर्ण

	ret = cdn_dp_get_hpd_status(dp);
	अगर (ret <= 0) अणु
		अगर (!ret)
			DRM_DEV_ERROR(dp->dev, "hpd does not exist\n");
		जाओ err_घातer_on;
	पूर्ण

	ret = extcon_get_property(port->extcon, EXTCON_DISP_DP,
				  EXTCON_PROP_USB_TYPEC_POLARITY, &property);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "get property failed\n");
		जाओ err_घातer_on;
	पूर्ण

	port->lanes = cdn_dp_get_port_lanes(port);
	ret = cdn_dp_set_host_cap(dp, port->lanes, property.पूर्णांकval);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "set host capabilities failed: %d\n",
			      ret);
		जाओ err_घातer_on;
	पूर्ण

	dp->active_port = port->id;
	वापस 0;

err_घातer_on:
	अगर (phy_घातer_off(port->phy))
		DRM_DEV_ERROR(dp->dev, "phy power off failed: %d", ret);
	अन्यथा
		port->phy_enabled = false;

err_phy:
	cdn_dp_grf_ग_लिखो(dp, GRF_SOC_CON26,
			 DPTX_HPD_SEL_MASK | DPTX_HPD_DEL);
	वापस ret;
पूर्ण

अटल पूर्णांक cdn_dp_disable_phy(काष्ठा cdn_dp_device *dp,
			      काष्ठा cdn_dp_port *port)
अणु
	पूर्णांक ret;

	अगर (port->phy_enabled) अणु
		ret = phy_घातer_off(port->phy);
		अगर (ret) अणु
			DRM_DEV_ERROR(dp->dev, "phy power off failed: %d", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	port->phy_enabled = false;
	port->lanes = 0;
	dp->active_port = -1;
	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_disable(काष्ठा cdn_dp_device *dp)
अणु
	पूर्णांक ret, i;

	अगर (!dp->active)
		वापस 0;

	क्रम (i = 0; i < dp->ports; i++)
		cdn_dp_disable_phy(dp, dp->port[i]);

	ret = cdn_dp_grf_ग_लिखो(dp, GRF_SOC_CON26,
			       DPTX_HPD_SEL_MASK | DPTX_HPD_DEL);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to clear hpd sel %d\n",
			      ret);
		वापस ret;
	पूर्ण

	cdn_dp_set_firmware_active(dp, false);
	cdn_dp_clk_disable(dp);
	dp->active = false;
	dp->max_lanes = 0;
	dp->max_rate = 0;
	अगर (!dp->connected) अणु
		kमुक्त(dp->edid);
		dp->edid = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_enable(काष्ठा cdn_dp_device *dp)
अणु
	पूर्णांक ret, i, lanes;
	काष्ठा cdn_dp_port *port;

	port = cdn_dp_connected_port(dp);
	अगर (!port) अणु
		DRM_DEV_ERROR(dp->dev,
			      "Can't enable without connection\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dp->active)
		वापस 0;

	ret = cdn_dp_clk_enable(dp);
	अगर (ret)
		वापस ret;

	ret = cdn_dp_firmware_init(dp);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "firmware init failed: %d", ret);
		जाओ err_clk_disable;
	पूर्ण

	/* only enable the port that connected with करोwnstream device */
	क्रम (i = port->id; i < dp->ports; i++) अणु
		port = dp->port[i];
		lanes = cdn_dp_get_port_lanes(port);
		अगर (lanes) अणु
			ret = cdn_dp_enable_phy(dp, port);
			अगर (ret)
				जारी;

			ret = cdn_dp_get_sink_capability(dp);
			अगर (ret) अणु
				cdn_dp_disable_phy(dp, port);
			पूर्ण अन्यथा अणु
				dp->active = true;
				dp->lanes = port->lanes;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

err_clk_disable:
	cdn_dp_clk_disable(dp);
	वापस ret;
पूर्ण

अटल व्योम cdn_dp_encoder_mode_set(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_display_mode *mode,
				    काष्ठा drm_display_mode *adjusted)
अणु
	काष्ठा cdn_dp_device *dp = encoder_to_dp(encoder);
	काष्ठा drm_display_info *display_info = &dp->connector.display_info;
	काष्ठा video_info *video = &dp->video_info;

	चयन (display_info->bpc) अणु
	हाल 10:
		video->color_depth = 10;
		अवरोध;
	हाल 6:
		video->color_depth = 6;
		अवरोध;
	शेष:
		video->color_depth = 8;
		अवरोध;
	पूर्ण

	video->color_fmt = PXL_RGB;
	video->v_sync_polarity = !!(mode->flags & DRM_MODE_FLAG_NVSYNC);
	video->h_sync_polarity = !!(mode->flags & DRM_MODE_FLAG_NHSYNC);

	स_नकल(&dp->mode, adjusted, माप(*mode));
पूर्ण

अटल bool cdn_dp_check_link_status(काष्ठा cdn_dp_device *dp)
अणु
	u8 link_status[DP_LINK_STATUS_SIZE];
	काष्ठा cdn_dp_port *port = cdn_dp_connected_port(dp);
	u8 sink_lanes = drm_dp_max_lane_count(dp->dpcd);

	अगर (!port || !dp->max_rate || !dp->max_lanes)
		वापस false;

	अगर (cdn_dp_dpcd_पढ़ो(dp, DP_LANE0_1_STATUS, link_status,
			     DP_LINK_STATUS_SIZE)) अणु
		DRM_ERROR("Failed to get link status\n");
		वापस false;
	पूर्ण

	/* अगर link training is requested we should perक्रमm it always */
	वापस drm_dp_channel_eq_ok(link_status, min(port->lanes, sink_lanes));
पूर्ण

अटल व्योम cdn_dp_encoder_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा cdn_dp_device *dp = encoder_to_dp(encoder);
	पूर्णांक ret, val;

	ret = drm_of_encoder_active_endpoपूर्णांक_id(dp->dev->of_node, encoder);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dp->dev, "Could not get vop id, %d", ret);
		वापस;
	पूर्ण

	DRM_DEV_DEBUG_KMS(dp->dev, "vop %s output to cdn-dp\n",
			  (ret) ? "LIT" : "BIG");
	अगर (ret)
		val = DP_SEL_VOP_LIT | (DP_SEL_VOP_LIT << 16);
	अन्यथा
		val = DP_SEL_VOP_LIT << 16;

	ret = cdn_dp_grf_ग_लिखो(dp, GRF_SOC_CON9, val);
	अगर (ret)
		वापस;

	mutex_lock(&dp->lock);

	ret = cdn_dp_enable(dp);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to enable encoder %d\n",
			      ret);
		जाओ out;
	पूर्ण
	अगर (!cdn_dp_check_link_status(dp)) अणु
		ret = cdn_dp_train_link(dp);
		अगर (ret) अणु
			DRM_DEV_ERROR(dp->dev, "Failed link train %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = cdn_dp_set_video_status(dp, CONTROL_VIDEO_IDLE);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to idle video %d\n", ret);
		जाओ out;
	पूर्ण

	ret = cdn_dp_config_video(dp);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to config video %d\n", ret);
		जाओ out;
	पूर्ण

	ret = cdn_dp_set_video_status(dp, CONTROL_VIDEO_VALID);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to valid video %d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&dp->lock);
पूर्ण

अटल व्योम cdn_dp_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा cdn_dp_device *dp = encoder_to_dp(encoder);
	पूर्णांक ret;

	mutex_lock(&dp->lock);
	अगर (dp->active) अणु
		ret = cdn_dp_disable(dp);
		अगर (ret) अणु
			DRM_DEV_ERROR(dp->dev, "Failed to disable encoder %d\n",
				      ret);
		पूर्ण
	पूर्ण
	mutex_unlock(&dp->lock);

	/*
	 * In the following 2 हालs, we need to run the event_work to re-enable
	 * the DP:
	 * 1. If there is not just one port device is connected, and हटाओ one
	 *    device from a port, the DP will be disabled here, at this हाल,
	 *    run the event_work to re-खोलो DP क्रम the other port.
	 * 2. If re-training or re-config failed, the DP will be disabled here.
	 *    run the event_work to re-connect it.
	 */
	अगर (!dp->connected && cdn_dp_connected_port(dp))
		schedule_work(&dp->event_work);
पूर्ण

अटल पूर्णांक cdn_dp_encoder_atomic_check(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_crtc_state *crtc_state,
				       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा rockchip_crtc_state *s = to_rockchip_crtc_state(crtc_state);

	s->output_mode = ROCKCHIP_OUT_MODE_AAAA;
	s->output_type = DRM_MODE_CONNECTOR_DisplayPort;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs cdn_dp_encoder_helper_funcs = अणु
	.mode_set = cdn_dp_encoder_mode_set,
	.enable = cdn_dp_encoder_enable,
	.disable = cdn_dp_encoder_disable,
	.atomic_check = cdn_dp_encoder_atomic_check,
पूर्ण;

अटल पूर्णांक cdn_dp_parse_dt(काष्ठा cdn_dp_device *dp)
अणु
	काष्ठा device *dev = dp->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा resource *res;

	dp->grf = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	अगर (IS_ERR(dp->grf)) अणु
		DRM_DEV_ERROR(dev, "cdn-dp needs rockchip,grf property\n");
		वापस PTR_ERR(dp->grf);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dp->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(dp->regs)) अणु
		DRM_DEV_ERROR(dev, "ioremap reg failed\n");
		वापस PTR_ERR(dp->regs);
	पूर्ण

	dp->core_clk = devm_clk_get(dev, "core-clk");
	अगर (IS_ERR(dp->core_clk)) अणु
		DRM_DEV_ERROR(dev, "cannot get core_clk_dp\n");
		वापस PTR_ERR(dp->core_clk);
	पूर्ण

	dp->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(dp->pclk)) अणु
		DRM_DEV_ERROR(dev, "cannot get pclk\n");
		वापस PTR_ERR(dp->pclk);
	पूर्ण

	dp->spdअगर_clk = devm_clk_get(dev, "spdif");
	अगर (IS_ERR(dp->spdअगर_clk)) अणु
		DRM_DEV_ERROR(dev, "cannot get spdif_clk\n");
		वापस PTR_ERR(dp->spdअगर_clk);
	पूर्ण

	dp->grf_clk = devm_clk_get(dev, "grf");
	अगर (IS_ERR(dp->grf_clk)) अणु
		DRM_DEV_ERROR(dev, "cannot get grf clk\n");
		वापस PTR_ERR(dp->grf_clk);
	पूर्ण

	dp->spdअगर_rst = devm_reset_control_get(dev, "spdif");
	अगर (IS_ERR(dp->spdअगर_rst)) अणु
		DRM_DEV_ERROR(dev, "no spdif reset control found\n");
		वापस PTR_ERR(dp->spdअगर_rst);
	पूर्ण

	dp->dptx_rst = devm_reset_control_get(dev, "dptx");
	अगर (IS_ERR(dp->dptx_rst)) अणु
		DRM_DEV_ERROR(dev, "no uphy reset control found\n");
		वापस PTR_ERR(dp->dptx_rst);
	पूर्ण

	dp->core_rst = devm_reset_control_get(dev, "core");
	अगर (IS_ERR(dp->core_rst)) अणु
		DRM_DEV_ERROR(dev, "no core reset control found\n");
		वापस PTR_ERR(dp->core_rst);
	पूर्ण

	dp->apb_rst = devm_reset_control_get(dev, "apb");
	अगर (IS_ERR(dp->apb_rst)) अणु
		DRM_DEV_ERROR(dev, "no apb reset control found\n");
		वापस PTR_ERR(dp->apb_rst);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_audio_hw_params(काष्ठा device *dev,  व्योम *data,
				  काष्ठा hdmi_codec_daअगरmt *daअगरmt,
				  काष्ठा hdmi_codec_params *params)
अणु
	काष्ठा cdn_dp_device *dp = dev_get_drvdata(dev);
	काष्ठा audio_info audio = अणु
		.sample_width = params->sample_width,
		.sample_rate = params->sample_rate,
		.channels = params->channels,
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&dp->lock);
	अगर (!dp->active) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	चयन (daअगरmt->fmt) अणु
	हाल HDMI_I2S:
		audio.क्रमmat = AFMT_I2S;
		अवरोध;
	हाल HDMI_SPDIF:
		audio.क्रमmat = AFMT_SPDIF;
		अवरोध;
	शेष:
		DRM_DEV_ERROR(dev, "Invalid format %d\n", daअगरmt->fmt);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = cdn_dp_audio_config(dp, &audio);
	अगर (!ret)
		dp->audio_info = audio;

out:
	mutex_unlock(&dp->lock);
	वापस ret;
पूर्ण

अटल व्योम cdn_dp_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा cdn_dp_device *dp = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&dp->lock);
	अगर (!dp->active)
		जाओ out;

	ret = cdn_dp_audio_stop(dp, &dp->audio_info);
	अगर (!ret)
		dp->audio_info.क्रमmat = AFMT_UNUSED;
out:
	mutex_unlock(&dp->lock);
पूर्ण

अटल पूर्णांक cdn_dp_audio_mute_stream(काष्ठा device *dev, व्योम *data,
				    bool enable, पूर्णांक direction)
अणु
	काष्ठा cdn_dp_device *dp = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&dp->lock);
	अगर (!dp->active) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = cdn_dp_audio_mute(dp, enable);

out:
	mutex_unlock(&dp->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक cdn_dp_audio_get_eld(काष्ठा device *dev, व्योम *data,
				u8 *buf, माप_प्रकार len)
अणु
	काष्ठा cdn_dp_device *dp = dev_get_drvdata(dev);

	स_नकल(buf, dp->connector.eld, min(माप(dp->connector.eld), len));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops audio_codec_ops = अणु
	.hw_params = cdn_dp_audio_hw_params,
	.audio_shutकरोwn = cdn_dp_audio_shutकरोwn,
	.mute_stream = cdn_dp_audio_mute_stream,
	.get_eld = cdn_dp_audio_get_eld,
	.no_capture_mute = 1,
पूर्ण;

अटल पूर्णांक cdn_dp_audio_codec_init(काष्ठा cdn_dp_device *dp,
				   काष्ठा device *dev)
अणु
	काष्ठा hdmi_codec_pdata codec_data = अणु
		.i2s = 1,
		.spdअगर = 1,
		.ops = &audio_codec_ops,
		.max_i2s_channels = 8,
	पूर्ण;

	dp->audio_pdev = platक्रमm_device_रेजिस्टर_data(
			 dev, HDMI_CODEC_DRV_NAME, PLATFORM_DEVID_AUTO,
			 &codec_data, माप(codec_data));

	वापस PTR_ERR_OR_ZERO(dp->audio_pdev);
पूर्ण

अटल पूर्णांक cdn_dp_request_firmware(काष्ठा cdn_dp_device *dp)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(CDN_FW_TIMEOUT_MS);
	अचिन्हित दीर्घ sleep = 1000;

	WARN_ON(!mutex_is_locked(&dp->lock));

	अगर (dp->fw_loaded)
		वापस 0;

	/* Drop the lock beक्रमe getting the firmware to aव्योम blocking boot */
	mutex_unlock(&dp->lock);

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		ret = request_firmware(&dp->fw, CDN_DP_FIRMWARE, dp->dev);
		अगर (ret == -ENOENT) अणु
			msleep(sleep);
			sleep *= 2;
			जारी;
		पूर्ण अन्यथा अगर (ret) अणु
			DRM_DEV_ERROR(dp->dev,
				      "failed to request firmware: %d\n", ret);
			जाओ out;
		पूर्ण

		dp->fw_loaded = true;
		ret = 0;
		जाओ out;
	पूर्ण

	DRM_DEV_ERROR(dp->dev, "Timed out trying to load firmware\n");
	ret = -ETIMEDOUT;
out:
	mutex_lock(&dp->lock);
	वापस ret;
पूर्ण

अटल व्योम cdn_dp_pd_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cdn_dp_device *dp = container_of(work, काष्ठा cdn_dp_device,
						event_work);
	काष्ठा drm_connector *connector = &dp->connector;
	क्रमागत drm_connector_status old_status;

	पूर्णांक ret;

	mutex_lock(&dp->lock);

	अगर (dp->suspended)
		जाओ out;

	ret = cdn_dp_request_firmware(dp);
	अगर (ret)
		जाओ out;

	dp->connected = true;

	/* Not connected, notअगरy userspace to disable the block */
	अगर (!cdn_dp_connected_port(dp)) अणु
		DRM_DEV_INFO(dp->dev, "Not connected. Disabling cdn\n");
		dp->connected = false;

	/* Connected but not enabled, enable the block */
	पूर्ण अन्यथा अगर (!dp->active) अणु
		DRM_DEV_INFO(dp->dev, "Connected, not enabled. Enabling cdn\n");
		ret = cdn_dp_enable(dp);
		अगर (ret) अणु
			DRM_DEV_ERROR(dp->dev, "Enable dp failed %d\n", ret);
			dp->connected = false;
		पूर्ण

	/* Enabled and connected to a करोngle without a sink, notअगरy userspace */
	पूर्ण अन्यथा अगर (!cdn_dp_check_sink_connection(dp)) अणु
		DRM_DEV_INFO(dp->dev, "Connected without sink. Assert hpd\n");
		dp->connected = false;

	/* Enabled and connected with a sink, re-train अगर requested */
	पूर्ण अन्यथा अगर (!cdn_dp_check_link_status(dp)) अणु
		अचिन्हित पूर्णांक rate = dp->max_rate;
		अचिन्हित पूर्णांक lanes = dp->max_lanes;
		काष्ठा drm_display_mode *mode = &dp->mode;

		DRM_DEV_INFO(dp->dev, "Connected with sink. Re-train link\n");
		ret = cdn_dp_train_link(dp);
		अगर (ret) अणु
			dp->connected = false;
			DRM_DEV_ERROR(dp->dev, "Train link failed %d\n", ret);
			जाओ out;
		पूर्ण

		/* If training result is changed, update the video config */
		अगर (mode->घड़ी &&
		    (rate != dp->max_rate || lanes != dp->max_lanes)) अणु
			ret = cdn_dp_config_video(dp);
			अगर (ret) अणु
				dp->connected = false;
				DRM_DEV_ERROR(dp->dev,
					      "Failed to config video %d\n",
					      ret);
			पूर्ण
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&dp->lock);

	old_status = connector->status;
	connector->status = connector->funcs->detect(connector, false);
	अगर (old_status != connector->status)
		drm_kms_helper_hotplug_event(dp->drm_dev);
पूर्ण

अटल पूर्णांक cdn_dp_pd_event(काष्ठा notअगरier_block *nb,
			   अचिन्हित दीर्घ event, व्योम *priv)
अणु
	काष्ठा cdn_dp_port *port = container_of(nb, काष्ठा cdn_dp_port,
						event_nb);
	काष्ठा cdn_dp_device *dp = port->dp;

	/*
	 * It would be nice to be able to just करो the work अंतरभूत right here.
	 * However, we need to make a bunch of calls that might sleep in order
	 * to turn on the block/phy, so use a worker instead.
	 */
	schedule_work(&dp->event_work);

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक cdn_dp_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा cdn_dp_device *dp = dev_get_drvdata(dev);
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	काष्ठा cdn_dp_port *port;
	काष्ठा drm_device *drm_dev = data;
	पूर्णांक ret, i;

	ret = cdn_dp_parse_dt(dp);
	अगर (ret < 0)
		वापस ret;

	dp->drm_dev = drm_dev;
	dp->connected = false;
	dp->active = false;
	dp->active_port = -1;
	dp->fw_loaded = false;

	INIT_WORK(&dp->event_work, cdn_dp_pd_event_work);

	encoder = &dp->encoder;

	encoder->possible_crtcs = drm_of_find_possible_crtcs(drm_dev,
							     dev->of_node);
	DRM_DEBUG_KMS("possible_crtcs = 0x%x\n", encoder->possible_crtcs);

	ret = drm_simple_encoder_init(drm_dev, encoder,
				      DRM_MODE_ENCODER_TMDS);
	अगर (ret) अणु
		DRM_ERROR("failed to initialize encoder with drm\n");
		वापस ret;
	पूर्ण

	drm_encoder_helper_add(encoder, &cdn_dp_encoder_helper_funcs);

	connector = &dp->connector;
	connector->polled = DRM_CONNECTOR_POLL_HPD;
	connector->dpms = DRM_MODE_DPMS_OFF;

	ret = drm_connector_init(drm_dev, connector,
				 &cdn_dp_atomic_connector_funcs,
				 DRM_MODE_CONNECTOR_DisplayPort);
	अगर (ret) अणु
		DRM_ERROR("failed to initialize connector with drm\n");
		जाओ err_मुक्त_encoder;
	पूर्ण

	drm_connector_helper_add(connector, &cdn_dp_connector_helper_funcs);

	ret = drm_connector_attach_encoder(connector, encoder);
	अगर (ret) अणु
		DRM_ERROR("failed to attach connector and encoder\n");
		जाओ err_मुक्त_connector;
	पूर्ण

	क्रम (i = 0; i < dp->ports; i++) अणु
		port = dp->port[i];

		port->event_nb.notअगरier_call = cdn_dp_pd_event;
		ret = devm_extcon_रेजिस्टर_notअगरier(dp->dev, port->extcon,
						    EXTCON_DISP_DP,
						    &port->event_nb);
		अगर (ret) अणु
			DRM_DEV_ERROR(dev,
				      "register EXTCON_DISP_DP notifier err\n");
			जाओ err_मुक्त_connector;
		पूर्ण
	पूर्ण

	pm_runसमय_enable(dev);

	schedule_work(&dp->event_work);

	वापस 0;

err_मुक्त_connector:
	drm_connector_cleanup(connector);
err_मुक्त_encoder:
	drm_encoder_cleanup(encoder);
	वापस ret;
पूर्ण

अटल व्योम cdn_dp_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा cdn_dp_device *dp = dev_get_drvdata(dev);
	काष्ठा drm_encoder *encoder = &dp->encoder;
	काष्ठा drm_connector *connector = &dp->connector;

	cancel_work_sync(&dp->event_work);
	cdn_dp_encoder_disable(encoder);
	encoder->funcs->destroy(encoder);
	connector->funcs->destroy(connector);

	pm_runसमय_disable(dev);
	अगर (dp->fw_loaded)
		release_firmware(dp->fw);
	kमुक्त(dp->edid);
	dp->edid = शून्य;
पूर्ण

अटल स्थिर काष्ठा component_ops cdn_dp_component_ops = अणु
	.bind = cdn_dp_bind,
	.unbind = cdn_dp_unbind,
पूर्ण;

अटल पूर्णांक cdn_dp_suspend(काष्ठा device *dev)
अणु
	काष्ठा cdn_dp_device *dp = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&dp->lock);
	अगर (dp->active)
		ret = cdn_dp_disable(dp);
	dp->suspended = true;
	mutex_unlock(&dp->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक cdn_dp_resume(काष्ठा device *dev)
अणु
	काष्ठा cdn_dp_device *dp = dev_get_drvdata(dev);

	mutex_lock(&dp->lock);
	dp->suspended = false;
	अगर (dp->fw_loaded)
		schedule_work(&dp->event_work);
	mutex_unlock(&dp->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा cdn_dp_data *dp_data;
	काष्ठा cdn_dp_port *port;
	काष्ठा cdn_dp_device *dp;
	काष्ठा extcon_dev *extcon;
	काष्ठा phy *phy;
	पूर्णांक i;

	dp = devm_kzalloc(dev, माप(*dp), GFP_KERNEL);
	अगर (!dp)
		वापस -ENOMEM;
	dp->dev = dev;

	match = of_match_node(cdn_dp_dt_ids, pdev->dev.of_node);
	dp_data = (काष्ठा cdn_dp_data *)match->data;

	क्रम (i = 0; i < dp_data->max_phy; i++) अणु
		extcon = extcon_get_edev_by_phandle(dev, i);
		phy = devm_of_phy_get_by_index(dev, dev->of_node, i);

		अगर (PTR_ERR(extcon) == -EPROBE_DEFER ||
		    PTR_ERR(phy) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		अगर (IS_ERR(extcon) || IS_ERR(phy))
			जारी;

		port = devm_kzalloc(dev, माप(*port), GFP_KERNEL);
		अगर (!port)
			वापस -ENOMEM;

		port->extcon = extcon;
		port->phy = phy;
		port->dp = dp;
		port->id = i;
		dp->port[dp->ports++] = port;
	पूर्ण

	अगर (!dp->ports) अणु
		DRM_DEV_ERROR(dev, "missing extcon or phy\n");
		वापस -EINVAL;
	पूर्ण

	mutex_init(&dp->lock);
	dev_set_drvdata(dev, dp);

	cdn_dp_audio_codec_init(dp, dev);

	वापस component_add(dev, &cdn_dp_component_ops);
पूर्ण

अटल पूर्णांक cdn_dp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdn_dp_device *dp = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर(dp->audio_pdev);
	cdn_dp_suspend(dp->dev);
	component_del(&pdev->dev, &cdn_dp_component_ops);

	वापस 0;
पूर्ण

अटल व्योम cdn_dp_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdn_dp_device *dp = platक्रमm_get_drvdata(pdev);

	cdn_dp_suspend(dp->dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cdn_dp_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cdn_dp_suspend,
				cdn_dp_resume)
पूर्ण;

काष्ठा platक्रमm_driver cdn_dp_driver = अणु
	.probe = cdn_dp_probe,
	.हटाओ = cdn_dp_हटाओ,
	.shutकरोwn = cdn_dp_shutकरोwn,
	.driver = अणु
		   .name = "cdn-dp",
		   .owner = THIS_MODULE,
		   .of_match_table = of_match_ptr(cdn_dp_dt_ids),
		   .pm = &cdn_dp_pm_ops,
	पूर्ण,
पूर्ण;
