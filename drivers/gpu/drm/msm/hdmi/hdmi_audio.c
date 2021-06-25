<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/hdmi.h>
#समावेश "hdmi.h"

/* maps MSM_HDMI_AUDIO_CHANNEL_n स्थिरs used by audio driver to # of channels: */
अटल पूर्णांक nchannels[] = अणु 2, 4, 6, 8 पूर्ण;

/* Supported HDMI Audio sample rates */
#घोषणा MSM_HDMI_SAMPLE_RATE_32KHZ		0
#घोषणा MSM_HDMI_SAMPLE_RATE_44_1KHZ		1
#घोषणा MSM_HDMI_SAMPLE_RATE_48KHZ		2
#घोषणा MSM_HDMI_SAMPLE_RATE_88_2KHZ		3
#घोषणा MSM_HDMI_SAMPLE_RATE_96KHZ		4
#घोषणा MSM_HDMI_SAMPLE_RATE_176_4KHZ		5
#घोषणा MSM_HDMI_SAMPLE_RATE_192KHZ		6
#घोषणा MSM_HDMI_SAMPLE_RATE_MAX		7


काष्ठा hdmi_msm_audio_acr अणु
	uपूर्णांक32_t n;	/* N parameter क्रम घड़ी regeneration */
	uपूर्णांक32_t cts;	/* CTS parameter क्रम घड़ी regeneration */
पूर्ण;

काष्ठा hdmi_msm_audio_arcs अणु
	अचिन्हित दीर्घ पूर्णांक pixघड़ी;
	काष्ठा hdmi_msm_audio_acr lut[MSM_HDMI_SAMPLE_RATE_MAX];
पूर्ण;

#घोषणा HDMI_MSM_AUDIO_ARCS(pclk, ...) अणु (1000 * (pclk)), __VA_ARGS__ पूर्ण

/* Audio स्थिरants lookup table क्रम hdmi_msm_audio_acr_setup */
/* Valid Pixel-Clock rates: 25.2MHz, 27MHz, 27.03MHz, 74.25MHz, 148.5MHz */
अटल स्थिर काष्ठा hdmi_msm_audio_arcs acr_lut[] = अणु
	/*  25.200MHz  */
	HDMI_MSM_AUDIO_ARCS(25200, अणु
		अणु4096, 25200पूर्ण, अणु6272, 28000पूर्ण, अणु6144, 25200पूर्ण, अणु12544, 28000पूर्ण,
		अणु12288, 25200पूर्ण, अणु25088, 28000पूर्ण, अणु24576, 25200पूर्ण पूर्ण),
	/*  27.000MHz  */
	HDMI_MSM_AUDIO_ARCS(27000, अणु
		अणु4096, 27000पूर्ण, अणु6272, 30000पूर्ण, अणु6144, 27000पूर्ण, अणु12544, 30000पूर्ण,
		अणु12288, 27000पूर्ण, अणु25088, 30000पूर्ण, अणु24576, 27000पूर्ण पूर्ण),
	/*  27.027MHz */
	HDMI_MSM_AUDIO_ARCS(27030, अणु
		अणु4096, 27027पूर्ण, अणु6272, 30030पूर्ण, अणु6144, 27027पूर्ण, अणु12544, 30030पूर्ण,
		अणु12288, 27027पूर्ण, अणु25088, 30030पूर्ण, अणु24576, 27027पूर्ण पूर्ण),
	/*  74.250MHz */
	HDMI_MSM_AUDIO_ARCS(74250, अणु
		अणु4096, 74250पूर्ण, अणु6272, 82500पूर्ण, अणु6144, 74250पूर्ण, अणु12544, 82500पूर्ण,
		अणु12288, 74250पूर्ण, अणु25088, 82500पूर्ण, अणु24576, 74250पूर्ण पूर्ण),
	/* 148.500MHz */
	HDMI_MSM_AUDIO_ARCS(148500, अणु
		अणु4096, 148500पूर्ण, अणु6272, 165000पूर्ण, अणु6144, 148500पूर्ण, अणु12544, 165000पूर्ण,
		अणु12288, 148500पूर्ण, अणु25088, 165000पूर्ण, अणु24576, 148500पूर्ण पूर्ण),
पूर्ण;

अटल स्थिर काष्ठा hdmi_msm_audio_arcs *get_arcs(अचिन्हित दीर्घ पूर्णांक pixघड़ी)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(acr_lut); i++) अणु
		स्थिर काष्ठा hdmi_msm_audio_arcs *arcs = &acr_lut[i];
		अगर (arcs->pixघड़ी == pixघड़ी)
			वापस arcs;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक msm_hdmi_audio_update(काष्ठा hdmi *hdmi)
अणु
	काष्ठा hdmi_audio *audio = &hdmi->audio;
	काष्ठा hdmi_audio_infoframe *info = &audio->infoframe;
	स्थिर काष्ठा hdmi_msm_audio_arcs *arcs = शून्य;
	bool enabled = audio->enabled;
	uपूर्णांक32_t acr_pkt_ctrl, vbi_pkt_ctrl, aud_pkt_ctrl;
	uपूर्णांक32_t infofrm_ctrl, audio_config;

	DBG("audio: enabled=%d, channels=%d, channel_allocation=0x%x, "
		"level_shift_value=%d, downmix_inhibit=%d, rate=%d",
		audio->enabled, info->channels,  info->channel_allocation,
		info->level_shअगरt_value, info->करोwnmix_inhibit, audio->rate);
	DBG("video: power_on=%d, pixclock=%lu", hdmi->घातer_on, hdmi->pixघड़ी);

	अगर (enabled && !(hdmi->घातer_on && hdmi->pixघड़ी)) अणु
		DBG("disabling audio: no video");
		enabled = false;
	पूर्ण

	अगर (enabled) अणु
		arcs = get_arcs(hdmi->pixघड़ी);
		अगर (!arcs) अणु
			DBG("disabling audio: unsupported pixclock: %lu",
					hdmi->pixघड़ी);
			enabled = false;
		पूर्ण
	पूर्ण

	/* Read first beक्रमe writing */
	acr_pkt_ctrl = hdmi_पढ़ो(hdmi, REG_HDMI_ACR_PKT_CTRL);
	vbi_pkt_ctrl = hdmi_पढ़ो(hdmi, REG_HDMI_VBI_PKT_CTRL);
	aud_pkt_ctrl = hdmi_पढ़ो(hdmi, REG_HDMI_AUDIO_PKT_CTRL1);
	infofrm_ctrl = hdmi_पढ़ो(hdmi, REG_HDMI_INFOFRAME_CTRL0);
	audio_config = hdmi_पढ़ो(hdmi, REG_HDMI_AUDIO_CFG);

	/* Clear N/CTS selection bits */
	acr_pkt_ctrl &= ~HDMI_ACR_PKT_CTRL_SELECT__MASK;

	अगर (enabled) अणु
		uपूर्णांक32_t n, cts, multiplier;
		क्रमागत hdmi_acr_cts select;
		uपूर्णांक8_t buf[14];

		n   = arcs->lut[audio->rate].n;
		cts = arcs->lut[audio->rate].cts;

		अगर ((MSM_HDMI_SAMPLE_RATE_192KHZ == audio->rate) ||
				(MSM_HDMI_SAMPLE_RATE_176_4KHZ == audio->rate)) अणु
			multiplier = 4;
			n >>= 2; /* भागide N by 4 and use multiplier */
		पूर्ण अन्यथा अगर ((MSM_HDMI_SAMPLE_RATE_96KHZ == audio->rate) ||
				(MSM_HDMI_SAMPLE_RATE_88_2KHZ == audio->rate)) अणु
			multiplier = 2;
			n >>= 1; /* भागide N by 2 and use multiplier */
		पूर्ण अन्यथा अणु
			multiplier = 1;
		पूर्ण

		DBG("n=%u, cts=%u, multiplier=%u", n, cts, multiplier);

		acr_pkt_ctrl |= HDMI_ACR_PKT_CTRL_SOURCE;
		acr_pkt_ctrl |= HDMI_ACR_PKT_CTRL_AUDIO_PRIORITY;
		acr_pkt_ctrl |= HDMI_ACR_PKT_CTRL_N_MULTIPLIER(multiplier);

		अगर ((MSM_HDMI_SAMPLE_RATE_48KHZ == audio->rate) ||
				(MSM_HDMI_SAMPLE_RATE_96KHZ == audio->rate) ||
				(MSM_HDMI_SAMPLE_RATE_192KHZ == audio->rate))
			select = ACR_48;
		अन्यथा अगर ((MSM_HDMI_SAMPLE_RATE_44_1KHZ == audio->rate) ||
				(MSM_HDMI_SAMPLE_RATE_88_2KHZ == audio->rate) ||
				(MSM_HDMI_SAMPLE_RATE_176_4KHZ == audio->rate))
			select = ACR_44;
		अन्यथा /* शेष to 32k */
			select = ACR_32;

		acr_pkt_ctrl |= HDMI_ACR_PKT_CTRL_SELECT(select);

		hdmi_ग_लिखो(hdmi, REG_HDMI_ACR_0(select - 1),
				HDMI_ACR_0_CTS(cts));
		hdmi_ग_लिखो(hdmi, REG_HDMI_ACR_1(select - 1),
				HDMI_ACR_1_N(n));

		hdmi_ग_लिखो(hdmi, REG_HDMI_AUDIO_PKT_CTRL2,
				COND(info->channels != 2, HDMI_AUDIO_PKT_CTRL2_LAYOUT) |
				HDMI_AUDIO_PKT_CTRL2_OVERRIDE);

		acr_pkt_ctrl |= HDMI_ACR_PKT_CTRL_CONT;
		acr_pkt_ctrl |= HDMI_ACR_PKT_CTRL_SEND;

		/* configure infoframe: */
		hdmi_audio_infoframe_pack(info, buf, माप(buf));
		hdmi_ग_लिखो(hdmi, REG_HDMI_AUDIO_INFO0,
				(buf[3] <<  0) | (buf[4] <<  8) |
				(buf[5] << 16) | (buf[6] << 24));
		hdmi_ग_लिखो(hdmi, REG_HDMI_AUDIO_INFO1,
				(buf[7] <<  0) | (buf[8] << 8));

		hdmi_ग_लिखो(hdmi, REG_HDMI_GC, 0);

		vbi_pkt_ctrl |= HDMI_VBI_PKT_CTRL_GC_ENABLE;
		vbi_pkt_ctrl |= HDMI_VBI_PKT_CTRL_GC_EVERY_FRAME;

		aud_pkt_ctrl |= HDMI_AUDIO_PKT_CTRL1_AUDIO_SAMPLE_SEND;

		infofrm_ctrl |= HDMI_INFOFRAME_CTRL0_AUDIO_INFO_SEND;
		infofrm_ctrl |= HDMI_INFOFRAME_CTRL0_AUDIO_INFO_CONT;
		infofrm_ctrl |= HDMI_INFOFRAME_CTRL0_AUDIO_INFO_SOURCE;
		infofrm_ctrl |= HDMI_INFOFRAME_CTRL0_AUDIO_INFO_UPDATE;

		audio_config &= ~HDMI_AUDIO_CFG_FIFO_WATERMARK__MASK;
		audio_config |= HDMI_AUDIO_CFG_FIFO_WATERMARK(4);
		audio_config |= HDMI_AUDIO_CFG_ENGINE_ENABLE;
	पूर्ण अन्यथा अणु
		acr_pkt_ctrl &= ~HDMI_ACR_PKT_CTRL_CONT;
		acr_pkt_ctrl &= ~HDMI_ACR_PKT_CTRL_SEND;
		vbi_pkt_ctrl &= ~HDMI_VBI_PKT_CTRL_GC_ENABLE;
		vbi_pkt_ctrl &= ~HDMI_VBI_PKT_CTRL_GC_EVERY_FRAME;
		aud_pkt_ctrl &= ~HDMI_AUDIO_PKT_CTRL1_AUDIO_SAMPLE_SEND;
		infofrm_ctrl &= ~HDMI_INFOFRAME_CTRL0_AUDIO_INFO_SEND;
		infofrm_ctrl &= ~HDMI_INFOFRAME_CTRL0_AUDIO_INFO_CONT;
		infofrm_ctrl &= ~HDMI_INFOFRAME_CTRL0_AUDIO_INFO_SOURCE;
		infofrm_ctrl &= ~HDMI_INFOFRAME_CTRL0_AUDIO_INFO_UPDATE;
		audio_config &= ~HDMI_AUDIO_CFG_ENGINE_ENABLE;
	पूर्ण

	hdmi_ग_लिखो(hdmi, REG_HDMI_ACR_PKT_CTRL, acr_pkt_ctrl);
	hdmi_ग_लिखो(hdmi, REG_HDMI_VBI_PKT_CTRL, vbi_pkt_ctrl);
	hdmi_ग_लिखो(hdmi, REG_HDMI_AUDIO_PKT_CTRL1, aud_pkt_ctrl);
	hdmi_ग_लिखो(hdmi, REG_HDMI_INFOFRAME_CTRL0, infofrm_ctrl);

	hdmi_ग_लिखो(hdmi, REG_HDMI_AUD_INT,
			COND(enabled, HDMI_AUD_INT_AUD_FIFO_URUN_INT) |
			COND(enabled, HDMI_AUD_INT_AUD_SAM_DROP_INT));

	hdmi_ग_लिखो(hdmi, REG_HDMI_AUDIO_CFG, audio_config);


	DBG("audio %sabled", enabled ? "en" : "dis");

	वापस 0;
पूर्ण

पूर्णांक msm_hdmi_audio_info_setup(काष्ठा hdmi *hdmi, bool enabled,
	uपूर्णांक32_t num_of_channels, uपूर्णांक32_t channel_allocation,
	uपूर्णांक32_t level_shअगरt, bool करोwn_mix)
अणु
	काष्ठा hdmi_audio *audio;

	अगर (!hdmi)
		वापस -ENXIO;

	audio = &hdmi->audio;

	अगर (num_of_channels >= ARRAY_SIZE(nchannels))
		वापस -EINVAL;

	audio->enabled = enabled;
	audio->infoframe.channels = nchannels[num_of_channels];
	audio->infoframe.channel_allocation = channel_allocation;
	audio->infoframe.level_shअगरt_value = level_shअगरt;
	audio->infoframe.करोwnmix_inhibit = करोwn_mix;

	वापस msm_hdmi_audio_update(hdmi);
पूर्ण

व्योम msm_hdmi_audio_set_sample_rate(काष्ठा hdmi *hdmi, पूर्णांक rate)
अणु
	काष्ठा hdmi_audio *audio;

	अगर (!hdmi)
		वापस;

	audio = &hdmi->audio;

	अगर ((rate < 0) || (rate >= MSM_HDMI_SAMPLE_RATE_MAX))
		वापस;

	audio->rate = rate;
	msm_hdmi_audio_update(hdmi);
पूर्ण
