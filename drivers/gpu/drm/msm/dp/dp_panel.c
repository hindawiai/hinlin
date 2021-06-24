<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#समावेश "dp_panel.h"

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_prपूर्णांक.h>

काष्ठा dp_panel_निजी अणु
	काष्ठा device *dev;
	काष्ठा dp_panel dp_panel;
	काष्ठा drm_dp_aux *aux;
	काष्ठा dp_link *link;
	काष्ठा dp_catalog *catalog;
	bool panel_on;
	bool aux_cfg_update_करोne;
पूर्ण;

अटल पूर्णांक dp_panel_पढ़ो_dpcd(काष्ठा dp_panel *dp_panel)
अणु
	पूर्णांक rc = 0;
	माप_प्रकार len;
	sमाप_प्रकार rlen;
	काष्ठा dp_panel_निजी *panel;
	काष्ठा dp_link_info *link_info;
	u8 *dpcd, major = 0, minor = 0, temp;
	u32 offset = DP_DPCD_REV;

	dpcd = dp_panel->dpcd;

	panel = container_of(dp_panel, काष्ठा dp_panel_निजी, dp_panel);
	link_info = &dp_panel->link_info;

	rlen = drm_dp_dpcd_पढ़ो(panel->aux, offset,
			dpcd, (DP_RECEIVER_CAP_SIZE + 1));
	अगर (rlen < (DP_RECEIVER_CAP_SIZE + 1)) अणु
		DRM_ERROR("dpcd read failed, rlen=%zd\n", rlen);
		अगर (rlen == -ETIMEDOUT)
			rc = rlen;
		अन्यथा
			rc = -EINVAL;

		जाओ end;
	पूर्ण

	temp = dpcd[DP_TRAINING_AUX_RD_INTERVAL];

	/* check क्रम EXTENDED_RECEIVER_CAPABILITY_FIELD_PRESENT */
	अगर (temp & BIT(7)) अणु
		DRM_DEBUG_DP("using EXTENDED_RECEIVER_CAPABILITY_FIELD\n");
		offset = DPRX_EXTENDED_DPCD_FIELD;
	पूर्ण

	rlen = drm_dp_dpcd_पढ़ो(panel->aux, offset,
		dpcd, (DP_RECEIVER_CAP_SIZE + 1));
	अगर (rlen < (DP_RECEIVER_CAP_SIZE + 1)) अणु
		DRM_ERROR("dpcd read failed, rlen=%zd\n", rlen);
		अगर (rlen == -ETIMEDOUT)
			rc = rlen;
		अन्यथा
			rc = -EINVAL;

		जाओ end;
	पूर्ण

	link_info->revision = dpcd[DP_DPCD_REV];
	major = (link_info->revision >> 4) & 0x0f;
	minor = link_info->revision & 0x0f;

	link_info->rate = drm_dp_bw_code_to_link_rate(dpcd[DP_MAX_LINK_RATE]);
	link_info->num_lanes = dpcd[DP_MAX_LANE_COUNT] & DP_MAX_LANE_COUNT_MASK;

	अगर (link_info->num_lanes > dp_panel->max_dp_lanes)
		link_info->num_lanes = dp_panel->max_dp_lanes;

	/* Limit support upto HBR2 until HBR3 support is added */
	अगर (link_info->rate >= (drm_dp_bw_code_to_link_rate(DP_LINK_BW_5_4)))
		link_info->rate = drm_dp_bw_code_to_link_rate(DP_LINK_BW_5_4);

	DRM_DEBUG_DP("version: %d.%d\n", major, minor);
	DRM_DEBUG_DP("link_rate=%d\n", link_info->rate);
	DRM_DEBUG_DP("lane_count=%d\n", link_info->num_lanes);

	अगर (drm_dp_enhanced_frame_cap(dpcd))
		link_info->capabilities |= DP_LINK_CAP_ENHANCED_FRAMING;

	dp_panel->dfp_present = dpcd[DP_DOWNSTREAMPORT_PRESENT];
	dp_panel->dfp_present &= DP_DWN_STRM_PORT_PRESENT;

	अगर (dp_panel->dfp_present && (dpcd[DP_DPCD_REV] > 0x10)) अणु
		dp_panel->ds_port_cnt = dpcd[DP_DOWN_STREAM_PORT_COUNT];
		dp_panel->ds_port_cnt &= DP_PORT_COUNT_MASK;
		len = DP_DOWNSTREAM_PORTS * DP_DOWNSTREAM_CAP_SIZE;

		rlen = drm_dp_dpcd_पढ़ो(panel->aux,
			DP_DOWNSTREAM_PORT_0, dp_panel->ds_cap_info, len);
		अगर (rlen < len) अणु
			DRM_ERROR("ds port status failed, rlen=%zd\n", rlen);
			rc = -EINVAL;
			जाओ end;
		पूर्ण
	पूर्ण

end:
	वापस rc;
पूर्ण

अटल u32 dp_panel_get_supported_bpp(काष्ठा dp_panel *dp_panel,
		u32 mode_edid_bpp, u32 mode_pclk_khz)
अणु
	काष्ठा dp_link_info *link_info;
	स्थिर u32 max_supported_bpp = 30, min_supported_bpp = 18;
	u32 bpp = 0, data_rate_khz = 0;

	bpp = min_t(u32, mode_edid_bpp, max_supported_bpp);

	link_info = &dp_panel->link_info;
	data_rate_khz = link_info->num_lanes * link_info->rate * 8;

	जबतक (bpp > min_supported_bpp) अणु
		अगर (mode_pclk_khz * bpp <= data_rate_khz)
			अवरोध;
		bpp -= 6;
	पूर्ण

	वापस bpp;
पूर्ण

अटल पूर्णांक dp_panel_update_modes(काष्ठा drm_connector *connector,
	काष्ठा edid *edid)
अणु
	पूर्णांक rc = 0;

	अगर (edid) अणु
		rc = drm_connector_update_edid_property(connector, edid);
		अगर (rc) अणु
			DRM_ERROR("failed to update edid property %d\n", rc);
			वापस rc;
		पूर्ण
		rc = drm_add_edid_modes(connector, edid);
		DRM_DEBUG_DP("%s -", __func__);
		वापस rc;
	पूर्ण

	rc = drm_connector_update_edid_property(connector, शून्य);
	अगर (rc)
		DRM_ERROR("failed to update edid property %d\n", rc);

	वापस rc;
पूर्ण

पूर्णांक dp_panel_पढ़ो_sink_caps(काष्ठा dp_panel *dp_panel,
	काष्ठा drm_connector *connector)
अणु
	पूर्णांक rc = 0, bw_code;
	पूर्णांक rlen, count;
	काष्ठा dp_panel_निजी *panel;

	अगर (!dp_panel || !connector) अणु
		DRM_ERROR("invalid input\n");
		वापस -EINVAL;
	पूर्ण

	panel = container_of(dp_panel, काष्ठा dp_panel_निजी, dp_panel);

	rc = dp_panel_पढ़ो_dpcd(dp_panel);
	अगर (rc) अणु
		DRM_ERROR("read dpcd failed %d\n", rc);
		वापस rc;
	पूर्ण

	bw_code = drm_dp_link_rate_to_bw_code(dp_panel->link_info.rate);
	अगर (!is_link_rate_valid(bw_code) ||
			!is_lane_count_valid(dp_panel->link_info.num_lanes) ||
			(bw_code > dp_panel->max_bw_code)) अणु
		DRM_ERROR("Illegal link rate=%d lane=%d\n", dp_panel->link_info.rate,
				dp_panel->link_info.num_lanes);
		वापस -EINVAL;
	पूर्ण

	अगर (dp_panel->dfp_present) अणु
		rlen = drm_dp_dpcd_पढ़ो(panel->aux, DP_SINK_COUNT,
				&count, 1);
		अगर (rlen == 1) अणु
			count = DP_GET_SINK_COUNT(count);
			अगर (!count) अणु
				DRM_ERROR("no downstream ports connected\n");
				panel->link->sink_count = 0;
				rc = -ENOTCONN;
				जाओ end;
			पूर्ण
		पूर्ण
	पूर्ण

	kमुक्त(dp_panel->edid);
	dp_panel->edid = शून्य;

	dp_panel->edid = drm_get_edid(connector,
					      &panel->aux->ddc);
	अगर (!dp_panel->edid) अणु
		DRM_ERROR("panel edid read failed\n");
		/* check edid पढ़ो fail is due to unplug */
		अगर (!dp_catalog_link_is_connected(panel->catalog)) अणु
			rc = -ETIMEDOUT;
			जाओ end;
		पूर्ण

		/* fail safe edid */
		mutex_lock(&connector->dev->mode_config.mutex);
		अगर (drm_add_modes_noedid(connector, 640, 480))
			drm_set_preferred_mode(connector, 640, 480);
		mutex_unlock(&connector->dev->mode_config.mutex);
	पूर्ण

	अगर (panel->aux_cfg_update_करोne) अणु
		DRM_DEBUG_DP("read DPCD with updated AUX config\n");
		rc = dp_panel_पढ़ो_dpcd(dp_panel);
		bw_code = drm_dp_link_rate_to_bw_code(dp_panel->link_info.rate);
		अगर (rc || !is_link_rate_valid(bw_code) ||
			!is_lane_count_valid(dp_panel->link_info.num_lanes)
			|| (bw_code > dp_panel->max_bw_code)) अणु
			DRM_ERROR("read dpcd failed %d\n", rc);
			वापस rc;
		पूर्ण
		panel->aux_cfg_update_करोne = false;
	पूर्ण
end:
	वापस rc;
पूर्ण

u32 dp_panel_get_mode_bpp(काष्ठा dp_panel *dp_panel,
		u32 mode_edid_bpp, u32 mode_pclk_khz)
अणु
	काष्ठा dp_panel_निजी *panel;
	u32 bpp = mode_edid_bpp;

	अगर (!dp_panel || !mode_edid_bpp || !mode_pclk_khz) अणु
		DRM_ERROR("invalid input\n");
		वापस 0;
	पूर्ण

	panel = container_of(dp_panel, काष्ठा dp_panel_निजी, dp_panel);

	अगर (dp_panel->video_test)
		bpp = dp_link_bit_depth_to_bpp(
				panel->link->test_video.test_bit_depth);
	अन्यथा
		bpp = dp_panel_get_supported_bpp(dp_panel, mode_edid_bpp,
				mode_pclk_khz);

	वापस bpp;
पूर्ण

पूर्णांक dp_panel_get_modes(काष्ठा dp_panel *dp_panel,
	काष्ठा drm_connector *connector, काष्ठा dp_display_mode *mode)
अणु
	अगर (!dp_panel) अणु
		DRM_ERROR("invalid input\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dp_panel->edid)
		वापस dp_panel_update_modes(connector, dp_panel->edid);

	वापस 0;
पूर्ण

अटल u8 dp_panel_get_edid_checksum(काष्ठा edid *edid)
अणु
	काष्ठा edid *last_block;
	u8 *raw_edid;
	bool is_edid_corrupt;

	अगर (!edid) अणु
		DRM_ERROR("invalid edid input\n");
		वापस 0;
	पूर्ण

	raw_edid = (u8 *)edid;
	raw_edid += (edid->extensions * EDID_LENGTH);
	last_block = (काष्ठा edid *)raw_edid;

	/* block type extension */
	drm_edid_block_valid(raw_edid, 1, false, &is_edid_corrupt);
	अगर (!is_edid_corrupt)
		वापस last_block->checksum;

	DRM_ERROR("Invalid block, no checksum\n");
	वापस 0;
पूर्ण

व्योम dp_panel_handle_sink_request(काष्ठा dp_panel *dp_panel)
अणु
	काष्ठा dp_panel_निजी *panel;

	अगर (!dp_panel) अणु
		DRM_ERROR("invalid input\n");
		वापस;
	पूर्ण

	panel = container_of(dp_panel, काष्ठा dp_panel_निजी, dp_panel);

	अगर (panel->link->sink_request & DP_TEST_LINK_EDID_READ) अणु
		u8 checksum = dp_panel_get_edid_checksum(dp_panel->edid);

		dp_link_send_edid_checksum(panel->link, checksum);
		dp_link_send_test_response(panel->link);
	पूर्ण
पूर्ण

व्योम dp_panel_tpg_config(काष्ठा dp_panel *dp_panel, bool enable)
अणु
	काष्ठा dp_catalog *catalog;
	काष्ठा dp_panel_निजी *panel;

	अगर (!dp_panel) अणु
		DRM_ERROR("invalid input\n");
		वापस;
	पूर्ण

	panel = container_of(dp_panel, काष्ठा dp_panel_निजी, dp_panel);
	catalog = panel->catalog;

	अगर (!panel->panel_on) अणु
		DRM_DEBUG_DP("DP panel not enabled, handle TPG on next on\n");
		वापस;
	पूर्ण

	अगर (!enable) अणु
		dp_catalog_panel_tpg_disable(catalog);
		वापस;
	पूर्ण

	DRM_DEBUG_DP("%s: calling catalog tpg_enable\n", __func__);
	dp_catalog_panel_tpg_enable(catalog, &panel->dp_panel.dp_mode.drm_mode);
पूर्ण

व्योम dp_panel_dump_regs(काष्ठा dp_panel *dp_panel)
अणु
	काष्ठा dp_catalog *catalog;
	काष्ठा dp_panel_निजी *panel;

	panel = container_of(dp_panel, काष्ठा dp_panel_निजी, dp_panel);
	catalog = panel->catalog;

	dp_catalog_dump_regs(catalog);
पूर्ण

पूर्णांक dp_panel_timing_cfg(काष्ठा dp_panel *dp_panel)
अणु
	पूर्णांक rc = 0;
	u32 data, total_ver, total_hor;
	काष्ठा dp_catalog *catalog;
	काष्ठा dp_panel_निजी *panel;
	काष्ठा drm_display_mode *drm_mode;

	panel = container_of(dp_panel, काष्ठा dp_panel_निजी, dp_panel);
	catalog = panel->catalog;
	drm_mode = &panel->dp_panel.dp_mode.drm_mode;

	DRM_DEBUG_DP("width=%d hporch= %d %d %d\n",
		drm_mode->hdisplay, drm_mode->htotal - drm_mode->hsync_end,
		drm_mode->hsync_start - drm_mode->hdisplay,
		drm_mode->hsync_end - drm_mode->hsync_start);

	DRM_DEBUG_DP("height=%d vporch= %d %d %d\n",
		drm_mode->vdisplay, drm_mode->vtotal - drm_mode->vsync_end,
		drm_mode->vsync_start - drm_mode->vdisplay,
		drm_mode->vsync_end - drm_mode->vsync_start);

	total_hor = drm_mode->htotal;

	total_ver = drm_mode->vtotal;

	data = total_ver;
	data <<= 16;
	data |= total_hor;

	catalog->total = data;

	data = (drm_mode->vtotal - drm_mode->vsync_start);
	data <<= 16;
	data |= (drm_mode->htotal - drm_mode->hsync_start);

	catalog->sync_start = data;

	data = drm_mode->vsync_end - drm_mode->vsync_start;
	data <<= 16;
	data |= (panel->dp_panel.dp_mode.v_active_low << 31);
	data |= drm_mode->hsync_end - drm_mode->hsync_start;
	data |= (panel->dp_panel.dp_mode.h_active_low << 15);

	catalog->width_blanking = data;

	data = drm_mode->vdisplay;
	data <<= 16;
	data |= drm_mode->hdisplay;

	catalog->dp_active = data;

	dp_catalog_panel_timing_cfg(catalog);
	panel->panel_on = true;

	वापस rc;
पूर्ण

पूर्णांक dp_panel_init_panel_info(काष्ठा dp_panel *dp_panel)
अणु
	काष्ठा drm_display_mode *drm_mode;

	drm_mode = &dp_panel->dp_mode.drm_mode;

	/*
	 * prपूर्णांक resolution info as this is a result
	 * of user initiated action of cable connection
	 */
	DRM_DEBUG_DP("SET NEW RESOLUTION:\n");
	DRM_DEBUG_DP("%dx%d@%dfps\n", drm_mode->hdisplay,
		drm_mode->vdisplay, drm_mode_vrefresh(drm_mode));
	DRM_DEBUG_DP("h_porches(back|front|width) = (%d|%d|%d)\n",
			drm_mode->htotal - drm_mode->hsync_end,
			drm_mode->hsync_start - drm_mode->hdisplay,
			drm_mode->hsync_end - drm_mode->hsync_start);
	DRM_DEBUG_DP("v_porches(back|front|width) = (%d|%d|%d)\n",
			drm_mode->vtotal - drm_mode->vsync_end,
			drm_mode->vsync_start - drm_mode->vdisplay,
			drm_mode->vsync_end - drm_mode->vsync_start);
	DRM_DEBUG_DP("pixel clock (KHz)=(%d)\n", drm_mode->घड़ी);
	DRM_DEBUG_DP("bpp = %d\n", dp_panel->dp_mode.bpp);

	dp_panel->dp_mode.bpp = max_t(u32, 18,
					min_t(u32, dp_panel->dp_mode.bpp, 30));
	DRM_DEBUG_DP("updated bpp = %d\n", dp_panel->dp_mode.bpp);

	वापस 0;
पूर्ण

काष्ठा dp_panel *dp_panel_get(काष्ठा dp_panel_in *in)
अणु
	काष्ठा dp_panel_निजी *panel;
	काष्ठा dp_panel *dp_panel;

	अगर (!in->dev || !in->catalog || !in->aux || !in->link) अणु
		DRM_ERROR("invalid input\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	panel = devm_kzalloc(in->dev, माप(*panel), GFP_KERNEL);
	अगर (!panel)
		वापस ERR_PTR(-ENOMEM);

	panel->dev = in->dev;
	panel->aux = in->aux;
	panel->catalog = in->catalog;
	panel->link = in->link;

	dp_panel = &panel->dp_panel;
	dp_panel->max_bw_code = DP_LINK_BW_8_1;
	panel->aux_cfg_update_करोne = false;

	वापस dp_panel;
पूर्ण

व्योम dp_panel_put(काष्ठा dp_panel *dp_panel)
अणु
	अगर (!dp_panel)
		वापस;

	kमुक्त(dp_panel->edid);
पूर्ण
