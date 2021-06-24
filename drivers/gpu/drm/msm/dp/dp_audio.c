<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016-2020, The Linux Foundation. All rights reserved.
 */


#घोषणा pr_fmt(fmt)	"[drm-dp] %s: " fmt, __func__

#समावेश <linux/of_platक्रमm.h>

#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>

#समावेश "dp_catalog.h"
#समावेश "dp_audio.h"
#समावेश "dp_panel.h"
#समावेश "dp_display.h"

#घोषणा HEADER_BYTE_2_BIT	 0
#घोषणा PARITY_BYTE_2_BIT	 8
#घोषणा HEADER_BYTE_1_BIT	16
#घोषणा PARITY_BYTE_1_BIT	24
#घोषणा HEADER_BYTE_3_BIT	16
#घोषणा PARITY_BYTE_3_BIT	24

काष्ठा dp_audio_निजी अणु
	काष्ठा platक्रमm_device *audio_pdev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा dp_catalog *catalog;
	काष्ठा dp_panel *panel;

	bool engine_on;
	u32 channels;

	काष्ठा dp_audio dp_audio;
पूर्ण;

अटल u8 dp_audio_get_g0_value(u8 data)
अणु
	u8 c[4];
	u8 g[4];
	u8 ret_data = 0;
	u8 i;

	क्रम (i = 0; i < 4; i++)
		c[i] = (data >> i) & 0x01;

	g[0] = c[3];
	g[1] = c[0] ^ c[3];
	g[2] = c[1];
	g[3] = c[2];

	क्रम (i = 0; i < 4; i++)
		ret_data = ((g[i] & 0x01) << i) | ret_data;

	वापस ret_data;
पूर्ण

अटल u8 dp_audio_get_g1_value(u8 data)
अणु
	u8 c[4];
	u8 g[4];
	u8 ret_data = 0;
	u8 i;

	क्रम (i = 0; i < 4; i++)
		c[i] = (data >> i) & 0x01;

	g[0] = c[0] ^ c[3];
	g[1] = c[0] ^ c[1] ^ c[3];
	g[2] = c[1] ^ c[2];
	g[3] = c[2] ^ c[3];

	क्रम (i = 0; i < 4; i++)
		ret_data = ((g[i] & 0x01) << i) | ret_data;

	वापस ret_data;
पूर्ण

अटल u8 dp_audio_calculate_parity(u32 data)
अणु
	u8 x0 = 0;
	u8 x1 = 0;
	u8 ci = 0;
	u8 iData = 0;
	u8 i = 0;
	u8 parity_byte;
	u8 num_byte = (data & 0xFF00) > 0 ? 8 : 2;

	क्रम (i = 0; i < num_byte; i++) अणु
		iData = (data >> i*4) & 0xF;

		ci = iData ^ x1;
		x1 = x0 ^ dp_audio_get_g1_value(ci);
		x0 = dp_audio_get_g0_value(ci);
	पूर्ण

	parity_byte = x1 | (x0 << 4);

	वापस parity_byte;
पूर्ण

अटल u32 dp_audio_get_header(काष्ठा dp_catalog *catalog,
		क्रमागत dp_catalog_audio_sdp_type sdp,
		क्रमागत dp_catalog_audio_header_type header)
अणु
	catalog->sdp_type = sdp;
	catalog->sdp_header = header;
	dp_catalog_audio_get_header(catalog);

	वापस catalog->audio_data;
पूर्ण

अटल व्योम dp_audio_set_header(काष्ठा dp_catalog *catalog,
		u32 data,
		क्रमागत dp_catalog_audio_sdp_type sdp,
		क्रमागत dp_catalog_audio_header_type header)
अणु
	catalog->sdp_type = sdp;
	catalog->sdp_header = header;
	catalog->audio_data = data;
	dp_catalog_audio_set_header(catalog);
पूर्ण

अटल व्योम dp_audio_stream_sdp(काष्ठा dp_audio_निजी *audio)
अणु
	काष्ठा dp_catalog *catalog = audio->catalog;
	u32 value, new_value;
	u8 parity_byte;

	/* Config header and parity byte 1 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_STREAM, DP_AUDIO_SDP_HEADER_1);

	new_value = 0x02;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_1_BIT)
			| (parity_byte << PARITY_BYTE_1_BIT));
	DRM_DEBUG_DP("Header Byte 1: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_STREAM, DP_AUDIO_SDP_HEADER_1);

	/* Config header and parity byte 2 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_STREAM, DP_AUDIO_SDP_HEADER_2);
	new_value = value;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_2_BIT)
			| (parity_byte << PARITY_BYTE_2_BIT));
	DRM_DEBUG_DP("Header Byte 2: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);

	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_STREAM, DP_AUDIO_SDP_HEADER_2);

	/* Config header and parity byte 3 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_STREAM, DP_AUDIO_SDP_HEADER_3);

	new_value = audio->channels - 1;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_3_BIT)
			| (parity_byte << PARITY_BYTE_3_BIT));
	DRM_DEBUG_DP("Header Byte 3: value = 0x%x, parity_byte = 0x%x\n",
		value, parity_byte);

	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_STREAM, DP_AUDIO_SDP_HEADER_3);
पूर्ण

अटल व्योम dp_audio_बारtamp_sdp(काष्ठा dp_audio_निजी *audio)
अणु
	काष्ठा dp_catalog *catalog = audio->catalog;
	u32 value, new_value;
	u8 parity_byte;

	/* Config header and parity byte 1 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADER_1);

	new_value = 0x1;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_1_BIT)
			| (parity_byte << PARITY_BYTE_1_BIT));
	DRM_DEBUG_DP("Header Byte 1: value = 0x%x, parity_byte = 0x%x\n",
		value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADER_1);

	/* Config header and parity byte 2 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADER_2);

	new_value = 0x17;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_2_BIT)
			| (parity_byte << PARITY_BYTE_2_BIT));
	DRM_DEBUG_DP("Header Byte 2: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADER_2);

	/* Config header and parity byte 3 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADER_3);

	new_value = (0x0 | (0x11 << 2));
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_3_BIT)
			| (parity_byte << PARITY_BYTE_3_BIT));
	DRM_DEBUG_DP("Header Byte 3: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_TIMESTAMP, DP_AUDIO_SDP_HEADER_3);
पूर्ण

अटल व्योम dp_audio_infoframe_sdp(काष्ठा dp_audio_निजी *audio)
अणु
	काष्ठा dp_catalog *catalog = audio->catalog;
	u32 value, new_value;
	u8 parity_byte;

	/* Config header and parity byte 1 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_INFOFRAME, DP_AUDIO_SDP_HEADER_1);

	new_value = 0x84;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_1_BIT)
			| (parity_byte << PARITY_BYTE_1_BIT));
	DRM_DEBUG_DP("Header Byte 1: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_INFOFRAME, DP_AUDIO_SDP_HEADER_1);

	/* Config header and parity byte 2 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_INFOFRAME, DP_AUDIO_SDP_HEADER_2);

	new_value = 0x1b;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_2_BIT)
			| (parity_byte << PARITY_BYTE_2_BIT));
	DRM_DEBUG_DP("Header Byte 2: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_INFOFRAME, DP_AUDIO_SDP_HEADER_2);

	/* Config header and parity byte 3 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_INFOFRAME, DP_AUDIO_SDP_HEADER_3);

	new_value = (0x0 | (0x11 << 2));
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_3_BIT)
			| (parity_byte << PARITY_BYTE_3_BIT));
	DRM_DEBUG_DP("Header Byte 3: value = 0x%x, parity_byte = 0x%x\n",
			new_value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_INFOFRAME, DP_AUDIO_SDP_HEADER_3);
पूर्ण

अटल व्योम dp_audio_copy_management_sdp(काष्ठा dp_audio_निजी *audio)
अणु
	काष्ठा dp_catalog *catalog = audio->catalog;
	u32 value, new_value;
	u8 parity_byte;

	/* Config header and parity byte 1 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADER_1);

	new_value = 0x05;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_1_BIT)
			| (parity_byte << PARITY_BYTE_1_BIT));
	DRM_DEBUG_DP("Header Byte 1: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADER_1);

	/* Config header and parity byte 2 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADER_2);

	new_value = 0x0F;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_2_BIT)
			| (parity_byte << PARITY_BYTE_2_BIT));
	DRM_DEBUG_DP("Header Byte 2: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADER_2);

	/* Config header and parity byte 3 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADER_3);

	new_value = 0x0;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_3_BIT)
			| (parity_byte << PARITY_BYTE_3_BIT));
	DRM_DEBUG_DP("Header Byte 3: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_COPYMANAGEMENT, DP_AUDIO_SDP_HEADER_3);
पूर्ण

अटल व्योम dp_audio_isrc_sdp(काष्ठा dp_audio_निजी *audio)
अणु
	काष्ठा dp_catalog *catalog = audio->catalog;
	u32 value, new_value;
	u8 parity_byte;

	/* Config header and parity byte 1 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_ISRC, DP_AUDIO_SDP_HEADER_1);

	new_value = 0x06;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_1_BIT)
			| (parity_byte << PARITY_BYTE_1_BIT));
	DRM_DEBUG_DP("Header Byte 1: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_ISRC, DP_AUDIO_SDP_HEADER_1);

	/* Config header and parity byte 2 */
	value = dp_audio_get_header(catalog,
			DP_AUDIO_SDP_ISRC, DP_AUDIO_SDP_HEADER_2);

	new_value = 0x0F;
	parity_byte = dp_audio_calculate_parity(new_value);
	value |= ((new_value << HEADER_BYTE_2_BIT)
			| (parity_byte << PARITY_BYTE_2_BIT));
	DRM_DEBUG_DP("Header Byte 2: value = 0x%x, parity_byte = 0x%x\n",
			value, parity_byte);
	dp_audio_set_header(catalog, value,
		DP_AUDIO_SDP_ISRC, DP_AUDIO_SDP_HEADER_2);
पूर्ण

अटल व्योम dp_audio_setup_sdp(काष्ठा dp_audio_निजी *audio)
अणु
	dp_catalog_audio_config_sdp(audio->catalog);

	dp_audio_stream_sdp(audio);
	dp_audio_बारtamp_sdp(audio);
	dp_audio_infoframe_sdp(audio);
	dp_audio_copy_management_sdp(audio);
	dp_audio_isrc_sdp(audio);
पूर्ण

अटल व्योम dp_audio_setup_acr(काष्ठा dp_audio_निजी *audio)
अणु
	u32 select = 0;
	काष्ठा dp_catalog *catalog = audio->catalog;

	चयन (audio->dp_audio.bw_code) अणु
	हाल DP_LINK_BW_1_62:
		select = 0;
		अवरोध;
	हाल DP_LINK_BW_2_7:
		select = 1;
		अवरोध;
	हाल DP_LINK_BW_5_4:
		select = 2;
		अवरोध;
	हाल DP_LINK_BW_8_1:
		select = 3;
		अवरोध;
	शेष:
		DRM_DEBUG_DP("Unknown link rate\n");
		select = 0;
		अवरोध;
	पूर्ण

	catalog->audio_data = select;
	dp_catalog_audio_config_acr(catalog);
पूर्ण

अटल व्योम dp_audio_safe_to_निकास_level(काष्ठा dp_audio_निजी *audio)
अणु
	काष्ठा dp_catalog *catalog = audio->catalog;
	u32 safe_to_निकास_level = 0;

	चयन (audio->dp_audio.lane_count) अणु
	हाल 1:
		safe_to_निकास_level = 14;
		अवरोध;
	हाल 2:
		safe_to_निकास_level = 8;
		अवरोध;
	हाल 4:
		safe_to_निकास_level = 5;
		अवरोध;
	शेष:
		DRM_DEBUG_DP("setting the default safe_to_exit_level = %u\n",
				safe_to_निकास_level);
		safe_to_निकास_level = 14;
		अवरोध;
	पूर्ण

	catalog->audio_data = safe_to_निकास_level;
	dp_catalog_audio_sfe_level(catalog);
पूर्ण

अटल व्योम dp_audio_enable(काष्ठा dp_audio_निजी *audio, bool enable)
अणु
	काष्ठा dp_catalog *catalog = audio->catalog;

	catalog->audio_data = enable;
	dp_catalog_audio_enable(catalog);

	audio->engine_on = enable;
पूर्ण

अटल काष्ठा dp_audio_निजी *dp_audio_get_data(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dp_audio *dp_audio;
	काष्ठा msm_dp *dp_display;

	अगर (!pdev) अणु
		DRM_ERROR("invalid input\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	dp_display = platक्रमm_get_drvdata(pdev);
	अगर (!dp_display) अणु
		DRM_ERROR("invalid input\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	dp_audio = dp_display->dp_audio;

	अगर (!dp_audio) अणु
		DRM_ERROR("invalid dp_audio data\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस container_of(dp_audio, काष्ठा dp_audio_निजी, dp_audio);
पूर्ण

अटल पूर्णांक dp_audio_hook_plugged_cb(काष्ठा device *dev, व्योम *data,
		hdmi_codec_plugged_cb fn,
		काष्ठा device *codec_dev)
अणु

	काष्ठा platक्रमm_device *pdev;
	काष्ठा msm_dp *dp_display;

	pdev = to_platक्रमm_device(dev);
	अगर (!pdev) अणु
		pr_err("invalid input\n");
		वापस -ENODEV;
	पूर्ण

	dp_display = platक्रमm_get_drvdata(pdev);
	अगर (!dp_display) अणु
		pr_err("invalid input\n");
		वापस -ENODEV;
	पूर्ण

	वापस dp_display_set_plugged_cb(dp_display, fn, codec_dev);
पूर्ण

अटल पूर्णांक dp_audio_get_eld(काष्ठा device *dev,
	व्योम *data, uपूर्णांक8_t *buf, माप_प्रकार len)
अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा msm_dp *dp_display;

	pdev = to_platक्रमm_device(dev);

	अगर (!pdev) अणु
		DRM_ERROR("invalid input\n");
		वापस -ENODEV;
	पूर्ण

	dp_display = platक्रमm_get_drvdata(pdev);
	अगर (!dp_display) अणु
		DRM_ERROR("invalid input\n");
		वापस -ENODEV;
	पूर्ण

	स_नकल(buf, dp_display->connector->eld,
		min(माप(dp_display->connector->eld), len));

	वापस 0;
पूर्ण

पूर्णांक dp_audio_hw_params(काष्ठा device *dev,
	व्योम *data,
	काष्ठा hdmi_codec_daअगरmt *daअगरmt,
	काष्ठा hdmi_codec_params *params)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_audio_निजी *audio;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा msm_dp *dp_display;

	pdev = to_platक्रमm_device(dev);
	dp_display = platक्रमm_get_drvdata(pdev);

	/*
	 * there could be हालs where sound card can be खोलोed even
	 * beक्रमe OR even when DP is not connected . This can cause
	 * unघड़ीed access as the audio subप्रणाली relies on the DP
	 * driver to मुख्यtain the correct state of घड़ीs. To protect
	 * such हालs check क्रम connection status and bail out अगर not
	 * connected.
	 */
	अगर (!dp_display->घातer_on) अणु
		rc = -EINVAL;
		जाओ end;
	पूर्ण

	audio = dp_audio_get_data(pdev);
	अगर (IS_ERR(audio)) अणु
		rc = PTR_ERR(audio);
		जाओ end;
	पूर्ण

	audio->channels = params->channels;

	dp_audio_setup_sdp(audio);
	dp_audio_setup_acr(audio);
	dp_audio_safe_to_निकास_level(audio);
	dp_audio_enable(audio, true);
	dp_display_संकेत_audio_start(dp_display);
	dp_display->audio_enabled = true;

end:
	वापस rc;
पूर्ण

अटल व्योम dp_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा dp_audio_निजी *audio;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा msm_dp *dp_display;

	pdev = to_platक्रमm_device(dev);
	dp_display = platक्रमm_get_drvdata(pdev);
	audio = dp_audio_get_data(pdev);
	अगर (IS_ERR(audio)) अणु
		DRM_ERROR("failed to get audio data\n");
		वापस;
	पूर्ण

	/*
	 * अगर audio was not enabled there is no need
	 * to execute the shutकरोwn and we can bail out early.
	 * This also makes sure that we करोnt cause an unघड़ीed
	 * access when audio subप्रणाली calls this without DP being
	 * connected. is_connected cannot be used here as its set
	 * to false earlier than this call
	 */
	अगर (!dp_display->audio_enabled)
		वापस;

	dp_audio_enable(audio, false);
	/* संकेत the dp display to safely shutकरोwn घड़ीs */
	dp_display_संकेत_audio_complete(dp_display);
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops dp_audio_codec_ops = अणु
	.hw_params = dp_audio_hw_params,
	.audio_shutकरोwn = dp_audio_shutकरोwn,
	.get_eld = dp_audio_get_eld,
	.hook_plugged_cb = dp_audio_hook_plugged_cb,
पूर्ण;

अटल काष्ठा hdmi_codec_pdata codec_data = अणु
	.ops = &dp_audio_codec_ops,
	.max_i2s_channels = 8,
	.i2s = 1,
पूर्ण;

पूर्णांक dp_रेजिस्टर_audio_driver(काष्ठा device *dev,
		काष्ठा dp_audio *dp_audio)
अणु
	काष्ठा dp_audio_निजी *audio_priv;

	audio_priv = container_of(dp_audio,
			काष्ठा dp_audio_निजी, dp_audio);

	audio_priv->audio_pdev = platक्रमm_device_रेजिस्टर_data(dev,
						HDMI_CODEC_DRV_NAME,
						PLATFORM_DEVID_AUTO,
						&codec_data,
						माप(codec_data));
	वापस PTR_ERR_OR_ZERO(audio_priv->audio_pdev);
पूर्ण

काष्ठा dp_audio *dp_audio_get(काष्ठा platक्रमm_device *pdev,
			काष्ठा dp_panel *panel,
			काष्ठा dp_catalog *catalog)
अणु
	पूर्णांक rc = 0;
	काष्ठा dp_audio_निजी *audio;
	काष्ठा dp_audio *dp_audio;

	अगर (!pdev || !panel || !catalog) अणु
		DRM_ERROR("invalid input\n");
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	audio = devm_kzalloc(&pdev->dev, माप(*audio), GFP_KERNEL);
	अगर (!audio) अणु
		rc = -ENOMEM;
		जाओ error;
	पूर्ण

	audio->pdev = pdev;
	audio->panel = panel;
	audio->catalog = catalog;

	dp_audio = &audio->dp_audio;

	dp_catalog_audio_init(catalog);

	वापस dp_audio;
error:
	वापस ERR_PTR(rc);
पूर्ण

व्योम dp_audio_put(काष्ठा dp_audio *dp_audio)
अणु
	काष्ठा dp_audio_निजी *audio;

	अगर (!dp_audio)
		वापस;

	audio = container_of(dp_audio, काष्ठा dp_audio_निजी, dp_audio);

	devm_kमुक्त(&audio->pdev->dev, audio);
पूर्ण
