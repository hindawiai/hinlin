<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_AUDIO_H_
#घोषणा _DP_AUDIO_H_

#समावेश <linux/platक्रमm_device.h>

#समावेश "dp_panel.h"
#समावेश "dp_catalog.h"
#समावेश <sound/hdmi-codec.h>

/**
 * काष्ठा dp_audio
 * @lane_count: number of lanes configured in current session
 * @bw_code: link rate's bandwidth code क्रम current session
 */
काष्ठा dp_audio अणु
	u32 lane_count;
	u32 bw_code;
पूर्ण;

/**
 * dp_audio_get()
 *
 * Creates and instance of dp audio.
 *
 * @pdev: caller's platक्रमm device instance.
 * @panel: an instance of dp_panel module.
 * @catalog: an instance of dp_catalog module.
 *
 * Returns the error code in हाल of failure, otherwize
 * an instance of newly created dp_module.
 */
काष्ठा dp_audio *dp_audio_get(काष्ठा platक्रमm_device *pdev,
			काष्ठा dp_panel *panel,
			काष्ठा dp_catalog *catalog);

/**
 * dp_रेजिस्टर_audio_driver()
 *
 * Registers DP device with hdmi_codec पूर्णांकerface.
 *
 * @dev: DP device instance.
 * @dp_audio: an instance of dp_audio module.
 *
 *
 * Returns the error code in हाल of failure, otherwise
 * zero on success.
 */
पूर्णांक dp_रेजिस्टर_audio_driver(काष्ठा device *dev,
		काष्ठा dp_audio *dp_audio);

/**
 * dp_audio_put()
 *
 * Cleans the dp_audio instance.
 *
 * @dp_audio: an instance of dp_audio.
 */
व्योम dp_audio_put(काष्ठा dp_audio *dp_audio);

पूर्णांक dp_audio_hw_params(काष्ठा device *dev,
	व्योम *data,
	काष्ठा hdmi_codec_daअगरmt *daअगरmt,
	काष्ठा hdmi_codec_params *params);

#पूर्ण_अगर /* _DP_AUDIO_H_ */


