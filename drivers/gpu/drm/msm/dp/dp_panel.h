<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_PANEL_H_
#घोषणा _DP_PANEL_H_

#समावेश <drm/msm_drm.h>

#समावेश "dp_aux.h"
#समावेश "dp_link.h"
#समावेश "dp_hpd.h"

काष्ठा edid;

#घोषणा DPRX_EXTENDED_DPCD_FIELD	0x2200

#घोषणा DP_DOWNSTREAM_PORTS		4
#घोषणा DP_DOWNSTREAM_CAP_SIZE		4

काष्ठा dp_display_mode अणु
	काष्ठा drm_display_mode drm_mode;
	u32 capabilities;
	u32 bpp;
	u32 h_active_low;
	u32 v_active_low;
पूर्ण;

काष्ठा dp_panel_in अणु
	काष्ठा device *dev;
	काष्ठा drm_dp_aux *aux;
	काष्ठा dp_link *link;
	काष्ठा dp_catalog *catalog;
पूर्ण;

काष्ठा dp_panel अणु
	/* dpcd raw data */
	u8 dpcd[DP_RECEIVER_CAP_SIZE + 1];
	u8 ds_cap_info[DP_DOWNSTREAM_PORTS * DP_DOWNSTREAM_CAP_SIZE];
	u32 ds_port_cnt;
	u32 dfp_present;

	काष्ठा dp_link_info link_info;
	काष्ठा drm_dp_desc desc;
	काष्ठा edid *edid;
	काष्ठा drm_connector *connector;
	काष्ठा dp_display_mode dp_mode;
	bool video_test;

	u32 vic;
	u32 max_pclk_khz;
	u32 max_dp_lanes;

	u32 max_bw_code;
पूर्ण;

पूर्णांक dp_panel_init_panel_info(काष्ठा dp_panel *dp_panel);
पूर्णांक dp_panel_deinit(काष्ठा dp_panel *dp_panel);
पूर्णांक dp_panel_timing_cfg(काष्ठा dp_panel *dp_panel);
व्योम dp_panel_dump_regs(काष्ठा dp_panel *dp_panel);
पूर्णांक dp_panel_पढ़ो_sink_caps(काष्ठा dp_panel *dp_panel,
		काष्ठा drm_connector *connector);
u32 dp_panel_get_mode_bpp(काष्ठा dp_panel *dp_panel, u32 mode_max_bpp,
			u32 mode_pclk_khz);
पूर्णांक dp_panel_get_modes(काष्ठा dp_panel *dp_panel,
		काष्ठा drm_connector *connector, काष्ठा dp_display_mode *mode);
व्योम dp_panel_handle_sink_request(काष्ठा dp_panel *dp_panel);
व्योम dp_panel_tpg_config(काष्ठा dp_panel *dp_panel, bool enable);

/**
 * is_link_rate_valid() - validates the link rate
 * @lane_rate: link rate requested by the sink
 *
 * Returns true अगर the requested link rate is supported.
 */
अटल अंतरभूत bool is_link_rate_valid(u32 bw_code)
अणु
	वापस (bw_code == DP_LINK_BW_1_62 ||
		bw_code == DP_LINK_BW_2_7 ||
		bw_code == DP_LINK_BW_5_4 ||
		bw_code == DP_LINK_BW_8_1);
पूर्ण

/**
 * dp_link_is_lane_count_valid() - validates the lane count
 * @lane_count: lane count requested by the sink
 *
 * Returns true अगर the requested lane count is supported.
 */
अटल अंतरभूत bool is_lane_count_valid(u32 lane_count)
अणु
	वापस (lane_count == 1 ||
		lane_count == 2 ||
		lane_count == 4);
पूर्ण

काष्ठा dp_panel *dp_panel_get(काष्ठा dp_panel_in *in);
व्योम dp_panel_put(काष्ठा dp_panel *dp_panel);
#पूर्ण_अगर /* _DP_PANEL_H_ */
