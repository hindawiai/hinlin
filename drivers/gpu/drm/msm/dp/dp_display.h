<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_DISPLAY_H_
#घोषणा _DP_DISPLAY_H_

#समावेश "dp_panel.h"
#समावेश <sound/hdmi-codec.h>

काष्ठा msm_dp अणु
	काष्ठा drm_device *drm_dev;
	काष्ठा device *codec_dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	bool is_connected;
	bool audio_enabled;
	bool घातer_on;

	hdmi_codec_plugged_cb plugged_cb;

	u32 max_pclk_khz;

	u32 max_dp_lanes;
	काष्ठा dp_audio *dp_audio;
पूर्ण;

पूर्णांक dp_display_set_plugged_cb(काष्ठा msm_dp *dp_display,
		hdmi_codec_plugged_cb fn, काष्ठा device *codec_dev);
पूर्णांक dp_display_validate_mode(काष्ठा msm_dp *dp_display, u32 mode_pclk_khz);
पूर्णांक dp_display_get_modes(काष्ठा msm_dp *dp_display,
		काष्ठा dp_display_mode *dp_mode);
पूर्णांक dp_display_request_irq(काष्ठा msm_dp *dp_display);
bool dp_display_check_video_test(काष्ठा msm_dp *dp_display);
पूर्णांक dp_display_get_test_bpp(काष्ठा msm_dp *dp_display);
व्योम dp_display_संकेत_audio_start(काष्ठा msm_dp *dp_display);
व्योम dp_display_संकेत_audio_complete(काष्ठा msm_dp *dp_display);

#पूर्ण_अगर /* _DP_DISPLAY_H_ */
