<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * hdmi-codec.h - HDMI Codec driver API
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com
 *
 * Author: Jyri Sarha <jsarha@ti.com>
 */

#अगर_अघोषित __HDMI_CODEC_H__
#घोषणा __HDMI_CODEC_H__

#समावेश <linux/of_graph.h>
#समावेश <linux/hdmi.h>
#समावेश <drm/drm_edid.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/soc.h>
#समावेश <uapi/sound/asound.h>

/*
 * Protocol between ASoC cpu-dai and HDMI-encoder
 */
काष्ठा hdmi_codec_daअगरmt अणु
	क्रमागत अणु
		HDMI_I2S,
		HDMI_RIGHT_J,
		HDMI_LEFT_J,
		HDMI_DSP_A,
		HDMI_DSP_B,
		HDMI_AC97,
		HDMI_SPDIF,
	पूर्ण fmt;
	अचिन्हित पूर्णांक bit_clk_inv:1;
	अचिन्हित पूर्णांक frame_clk_inv:1;
	अचिन्हित पूर्णांक bit_clk_master:1;
	अचिन्हित पूर्णांक frame_clk_master:1;
	/* bit_fmt could be standard PCM क्रमmat or
	 * IEC958 encoded क्रमmat. ALSA IEC958 plugin will pass
	 * IEC958_SUBFRAME क्रमmat to the underneath driver.
	 */
	snd_pcm_क्रमmat_t bit_fmt;
पूर्ण;

/*
 * HDMI audio parameters
 */
काष्ठा hdmi_codec_params अणु
	काष्ठा hdmi_audio_infoframe cea;
	काष्ठा snd_aes_iec958 iec;
	पूर्णांक sample_rate;
	पूर्णांक sample_width;
	पूर्णांक channels;
पूर्ण;

प्रकार व्योम (*hdmi_codec_plugged_cb)(काष्ठा device *dev,
				      bool plugged);

काष्ठा hdmi_codec_pdata;
काष्ठा hdmi_codec_ops अणु
	/*
	 * Called when ASoC starts an audio stream setup.
	 * Optional
	 */
	पूर्णांक (*audio_startup)(काष्ठा device *dev, व्योम *data);

	/*
	 * Configures HDMI-encoder क्रम audio stream.
	 * Mandatory
	 */
	पूर्णांक (*hw_params)(काष्ठा device *dev, व्योम *data,
			 काष्ठा hdmi_codec_daअगरmt *fmt,
			 काष्ठा hdmi_codec_params *hparms);

	/*
	 * Shuts करोwn the audio stream.
	 * Mandatory
	 */
	व्योम (*audio_shutकरोwn)(काष्ठा device *dev, व्योम *data);

	/*
	 * Mute/unmute HDMI audio stream.
	 * Optional
	 */
	पूर्णांक (*mute_stream)(काष्ठा device *dev, व्योम *data,
			   bool enable, पूर्णांक direction);

	/*
	 * Provides EDID-Like-Data from connected HDMI device.
	 * Optional
	 */
	पूर्णांक (*get_eld)(काष्ठा device *dev, व्योम *data,
		       uपूर्णांक8_t *buf, माप_प्रकार len);

	/*
	 * Getting DAI ID
	 * Optional
	 */
	पूर्णांक (*get_dai_id)(काष्ठा snd_soc_component *comment,
			  काष्ठा device_node *endpoपूर्णांक);

	/*
	 * Hook callback function to handle connector plug event.
	 * Optional
	 */
	पूर्णांक (*hook_plugged_cb)(काष्ठा device *dev, व्योम *data,
			       hdmi_codec_plugged_cb fn,
			       काष्ठा device *codec_dev);

	/* bit field */
	अचिन्हित पूर्णांक no_capture_mute:1;
पूर्ण;

/* HDMI codec initalization data */
काष्ठा hdmi_codec_pdata अणु
	स्थिर काष्ठा hdmi_codec_ops *ops;
	uपूर्णांक i2s:1;
	uपूर्णांक spdअगर:1;
	पूर्णांक max_i2s_channels;
	व्योम *data;
पूर्ण;

काष्ठा snd_soc_component;
काष्ठा snd_soc_jack;

#घोषणा HDMI_CODEC_DRV_NAME "hdmi-audio-codec"

#पूर्ण_अगर /* __HDMI_CODEC_H__ */
