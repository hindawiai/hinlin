<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *   पूर्णांकel_hdmi_audio.c - Intel HDMI audio driver
 *
 *  Copyright (C) 2016 Intel Corp
 *  Authors:	Sailaja Bandarupalli <sailaja.bandarupalli@पूर्णांकel.com>
 *		Ramesh Babu K V	<ramesh.babu@पूर्णांकel.com>
 *		Vaibhav Agarwal <vaibhav.agarwal@पूर्णांकel.com>
 *		Jerome Anand <jerome.anand@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ALSA driver क्रम Intel HDMI audio
 */

#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/control.h>
#समावेश <sound/jack.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/पूर्णांकel_lpe_audपन.स>
#समावेश "intel_hdmi_audio.h"

#घोषणा क्रम_each_pipe(card_ctx, pipe) \
	क्रम ((pipe) = 0; (pipe) < (card_ctx)->num_pipes; (pipe)++)
#घोषणा क्रम_each_port(card_ctx, port) \
	क्रम ((port) = 0; (port) < (card_ctx)->num_ports; (port)++)

/*standard module options क्रम ALSA. This module supports only one card*/
अटल पूर्णांक hdmi_card_index = SNDRV_DEFAULT_IDX1;
अटल अक्षर *hdmi_card_id = SNDRV_DEFAULT_STR1;
अटल bool single_port;

module_param_named(index, hdmi_card_index, पूर्णांक, 0444);
MODULE_PARM_DESC(index,
		"Index value for INTEL Intel HDMI Audio controller.");
module_param_named(id, hdmi_card_id, अक्षरp, 0444);
MODULE_PARM_DESC(id,
		"ID string for INTEL Intel HDMI Audio controller.");
module_param(single_port, bool, 0444);
MODULE_PARM_DESC(single_port,
		"Single-port mode (for compatibility)");

/*
 * ELD SA bits in the CEA Speaker Allocation data block
 */
अटल स्थिर पूर्णांक eld_speaker_allocation_bits[] = अणु
	[0] = FL | FR,
	[1] = LFE,
	[2] = FC,
	[3] = RL | RR,
	[4] = RC,
	[5] = FLC | FRC,
	[6] = RLC | RRC,
	/* the following are not defined in ELD yet */
	[7] = 0,
पूर्ण;

/*
 * This is an ordered list!
 *
 * The preceding ones have better chances to be selected by
 * hdmi_channel_allocation().
 */
अटल काष्ठा cea_channel_speaker_allocation channel_allocations[] = अणु
/*                        channel:   7     6    5    4    3     2    1    0  */
अणु .ca_index = 0x00,  .speakers = अणु   0,    0,   0,   0,   0,    0,  FR,  FL पूर्ण पूर्ण,
				/* 2.1 */
अणु .ca_index = 0x01,  .speakers = अणु   0,    0,   0,   0,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
				/* Dolby Surround */
अणु .ca_index = 0x02,  .speakers = अणु   0,    0,   0,   0,  FC,    0,  FR,  FL पूर्ण पूर्ण,
				/* surround40 */
अणु .ca_index = 0x08,  .speakers = अणु   0,    0,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
				/* surround41 */
अणु .ca_index = 0x09,  .speakers = अणु   0,    0,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
				/* surround50 */
अणु .ca_index = 0x0a,  .speakers = अणु   0,    0,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
				/* surround51 */
अणु .ca_index = 0x0b,  .speakers = अणु   0,    0,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
				/* 6.1 */
अणु .ca_index = 0x0f,  .speakers = अणु   0,   RC,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
				/* surround71 */
अणु .ca_index = 0x13,  .speakers = अणु RRC,  RLC,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,

अणु .ca_index = 0x03,  .speakers = अणु   0,    0,   0,   0,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x04,  .speakers = अणु   0,    0,   0,  RC,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x05,  .speakers = अणु   0,    0,   0,  RC,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x06,  .speakers = अणु   0,    0,   0,  RC,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x07,  .speakers = अणु   0,    0,   0,  RC,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x0c,  .speakers = अणु   0,   RC,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x0d,  .speakers = अणु   0,   RC,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x0e,  .speakers = अणु   0,   RC,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x10,  .speakers = अणु RRC,  RLC,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x11,  .speakers = अणु RRC,  RLC,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x12,  .speakers = अणु RRC,  RLC,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x14,  .speakers = अणु FRC,  FLC,   0,   0,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x15,  .speakers = अणु FRC,  FLC,   0,   0,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x16,  .speakers = अणु FRC,  FLC,   0,   0,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x17,  .speakers = अणु FRC,  FLC,   0,   0,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x18,  .speakers = अणु FRC,  FLC,   0,  RC,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x19,  .speakers = अणु FRC,  FLC,   0,  RC,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1a,  .speakers = अणु FRC,  FLC,   0,  RC,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1b,  .speakers = अणु FRC,  FLC,   0,  RC,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1c,  .speakers = अणु FRC,  FLC,  RR,  RL,   0,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1d,  .speakers = अणु FRC,  FLC,  RR,  RL,   0,  LFE,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1e,  .speakers = अणु FRC,  FLC,  RR,  RL,  FC,    0,  FR,  FL पूर्ण पूर्ण,
अणु .ca_index = 0x1f,  .speakers = अणु FRC,  FLC,  RR,  RL,  FC,  LFE,  FR,  FL पूर्ण पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा channel_map_table map_tables[] = अणु
	अणु SNDRV_CHMAP_FL,       0x00,   FL पूर्ण,
	अणु SNDRV_CHMAP_FR,       0x01,   FR पूर्ण,
	अणु SNDRV_CHMAP_RL,       0x04,   RL पूर्ण,
	अणु SNDRV_CHMAP_RR,       0x05,   RR पूर्ण,
	अणु SNDRV_CHMAP_LFE,      0x02,   LFE पूर्ण,
	अणु SNDRV_CHMAP_FC,       0x03,   FC पूर्ण,
	अणु SNDRV_CHMAP_RLC,      0x06,   RLC पूर्ण,
	अणु SNDRV_CHMAP_RRC,      0x07,   RRC पूर्ण,
	अणुपूर्ण /* terminator */
पूर्ण;

/* hardware capability काष्ठाure */
अटल स्थिर काष्ठा snd_pcm_hardware had_pcm_hardware = अणु
	.info =	(SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_NO_PERIOD_WAKEUP),
	.क्रमmats = (SNDRV_PCM_FMTBIT_S16_LE |
		    SNDRV_PCM_FMTBIT_S24_LE |
		    SNDRV_PCM_FMTBIT_S32_LE),
	.rates = SNDRV_PCM_RATE_32000 |
		SNDRV_PCM_RATE_44100 |
		SNDRV_PCM_RATE_48000 |
		SNDRV_PCM_RATE_88200 |
		SNDRV_PCM_RATE_96000 |
		SNDRV_PCM_RATE_176400 |
		SNDRV_PCM_RATE_192000,
	.rate_min = HAD_MIN_RATE,
	.rate_max = HAD_MAX_RATE,
	.channels_min = HAD_MIN_CHANNEL,
	.channels_max = HAD_MAX_CHANNEL,
	.buffer_bytes_max = HAD_MAX_BUFFER,
	.period_bytes_min = HAD_MIN_PERIOD_BYTES,
	.period_bytes_max = HAD_MAX_PERIOD_BYTES,
	.periods_min = HAD_MIN_PERIODS,
	.periods_max = HAD_MAX_PERIODS,
	.fअगरo_size = HAD_FIFO_SIZE,
पूर्ण;

/* Get the active PCM substream;
 * Call had_substream_put() क्रम unreferecing.
 * Don't call this inside had_spinlock, as it takes by itself
 */
अटल काष्ठा snd_pcm_substream *
had_substream_get(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पूर्णांकelhaddata->had_spinlock, flags);
	substream = पूर्णांकelhaddata->stream_info.substream;
	अगर (substream)
		पूर्णांकelhaddata->stream_info.substream_refcount++;
	spin_unlock_irqrestore(&पूर्णांकelhaddata->had_spinlock, flags);
	वापस substream;
पूर्ण

/* Unref the active PCM substream;
 * Don't call this inside had_spinlock, as it takes by itself
 */
अटल व्योम had_substream_put(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&पूर्णांकelhaddata->had_spinlock, flags);
	पूर्णांकelhaddata->stream_info.substream_refcount--;
	spin_unlock_irqrestore(&पूर्णांकelhaddata->had_spinlock, flags);
पूर्ण

अटल u32 had_config_offset(पूर्णांक pipe)
अणु
	चयन (pipe) अणु
	शेष:
	हाल 0:
		वापस AUDIO_HDMI_CONFIG_A;
	हाल 1:
		वापस AUDIO_HDMI_CONFIG_B;
	हाल 2:
		वापस AUDIO_HDMI_CONFIG_C;
	पूर्ण
पूर्ण

/* Register access functions */
अटल u32 had_पढ़ो_रेजिस्टर_raw(काष्ठा snd_पूर्णांकelhad_card *card_ctx,
				 पूर्णांक pipe, u32 reg)
अणु
	वापस ioपढ़ो32(card_ctx->mmio_start + had_config_offset(pipe) + reg);
पूर्ण

अटल व्योम had_ग_लिखो_रेजिस्टर_raw(काष्ठा snd_पूर्णांकelhad_card *card_ctx,
				   पूर्णांक pipe, u32 reg, u32 val)
अणु
	ioग_लिखो32(val, card_ctx->mmio_start + had_config_offset(pipe) + reg);
पूर्ण

अटल व्योम had_पढ़ो_रेजिस्टर(काष्ठा snd_पूर्णांकelhad *ctx, u32 reg, u32 *val)
अणु
	अगर (!ctx->connected)
		*val = 0;
	अन्यथा
		*val = had_पढ़ो_रेजिस्टर_raw(ctx->card_ctx, ctx->pipe, reg);
पूर्ण

अटल व्योम had_ग_लिखो_रेजिस्टर(काष्ठा snd_पूर्णांकelhad *ctx, u32 reg, u32 val)
अणु
	अगर (ctx->connected)
		had_ग_लिखो_रेजिस्टर_raw(ctx->card_ctx, ctx->pipe, reg, val);
पूर्ण

/*
 * enable / disable audio configuration
 *
 * The normal पढ़ो/modअगरy should not directly be used on VLV2 क्रम
 * updating AUD_CONFIG रेजिस्टर.
 * This is because:
 * Bit6 of AUD_CONFIG रेजिस्टर is ग_लिखोonly due to a silicon bug on VLV2
 * HDMI IP. As a result a पढ़ो-modअगरy of AUD_CONFIG regiter will always
 * clear bit6. AUD_CONFIG[6:4] represents the "channels" field of the
 * रेजिस्टर. This field should be 1xy binary क्रम configuration with 6 or
 * more channels. Read-modअगरy of AUD_CONFIG (Eg. क्रम enabling audio)
 * causes the "channels" field to be updated as 0xy binary resulting in
 * bad audio. The fix is to always ग_लिखो the AUD_CONFIG[6:4] with
 * appropriate value when करोing पढ़ो-modअगरy of AUD_CONFIG रेजिस्टर.
 */
अटल व्योम had_enable_audio(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata,
			     bool enable)
अणु
	/* update the cached value */
	पूर्णांकelhaddata->aud_config.regx.aud_en = enable;
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_CONFIG,
			   पूर्णांकelhaddata->aud_config.regval);
पूर्ण

/* क्रमcibly ACKs to both BUFFER_DONE and BUFFER_UNDERRUN पूर्णांकerrupts */
अटल व्योम had_ack_irqs(काष्ठा snd_पूर्णांकelhad *ctx)
अणु
	u32 status_reg;

	अगर (!ctx->connected)
		वापस;
	had_पढ़ो_रेजिस्टर(ctx, AUD_HDMI_STATUS, &status_reg);
	status_reg |= HDMI_AUDIO_BUFFER_DONE | HDMI_AUDIO_UNDERRUN;
	had_ग_लिखो_रेजिस्टर(ctx, AUD_HDMI_STATUS, status_reg);
	had_पढ़ो_रेजिस्टर(ctx, AUD_HDMI_STATUS, &status_reg);
पूर्ण

/* Reset buffer poपूर्णांकers */
अटल व्योम had_reset_audio(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_HDMI_STATUS,
			   AUD_HDMI_STATUSG_MASK_FUNCRST);
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_HDMI_STATUS, 0);
पूर्ण

/*
 * initialize audio channel status रेजिस्टरs
 * This function is called in the prepare callback
 */
अटल पूर्णांक had_prog_status_reg(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	जोड़ aud_ch_status_0 ch_stat0 = अणु.regval = 0पूर्ण;
	जोड़ aud_ch_status_1 ch_stat1 = अणु.regval = 0पूर्ण;

	ch_stat0.regx.lpcm_id = (पूर्णांकelhaddata->aes_bits &
					  IEC958_AES0_NONAUDIO) >> 1;
	ch_stat0.regx.clk_acc = (पूर्णांकelhaddata->aes_bits &
					  IEC958_AES3_CON_CLOCK) >> 4;

	चयन (substream->runसमय->rate) अणु
	हाल AUD_SAMPLE_RATE_32:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_32KHZ;
		अवरोध;

	हाल AUD_SAMPLE_RATE_44_1:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_44KHZ;
		अवरोध;
	हाल AUD_SAMPLE_RATE_48:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_48KHZ;
		अवरोध;
	हाल AUD_SAMPLE_RATE_88_2:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_88KHZ;
		अवरोध;
	हाल AUD_SAMPLE_RATE_96:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_96KHZ;
		अवरोध;
	हाल AUD_SAMPLE_RATE_176_4:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_176KHZ;
		अवरोध;
	हाल AUD_SAMPLE_RATE_192:
		ch_stat0.regx.samp_freq = CH_STATUS_MAP_192KHZ;
		अवरोध;

	शेष:
		/* control should never come here */
		वापस -EINVAL;
	पूर्ण

	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata,
			   AUD_CH_STATUS_0, ch_stat0.regval);

	चयन (substream->runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		ch_stat1.regx.max_wrd_len = MAX_SMPL_WIDTH_20;
		ch_stat1.regx.wrd_len = SMPL_WIDTH_16BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
	हाल SNDRV_PCM_FORMAT_S32_LE:
		ch_stat1.regx.max_wrd_len = MAX_SMPL_WIDTH_24;
		ch_stat1.regx.wrd_len = SMPL_WIDTH_24BITS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata,
			   AUD_CH_STATUS_1, ch_stat1.regval);
	वापस 0;
पूर्ण

/*
 * function to initialize audio
 * रेजिस्टरs and buffer confgiuration रेजिस्टरs
 * This function is called in the prepare callback
 */
अटल पूर्णांक had_init_audio_ctrl(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	जोड़ aud_cfg cfg_val = अणु.regval = 0पूर्ण;
	जोड़ aud_buf_config buf_cfg = अणु.regval = 0पूर्ण;
	u8 channels;

	had_prog_status_reg(substream, पूर्णांकelhaddata);

	buf_cfg.regx.audio_fअगरo_watermark = FIFO_THRESHOLD;
	buf_cfg.regx.dma_fअगरo_watermark = DMA_FIFO_THRESHOLD;
	buf_cfg.regx.aud_delay = 0;
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_BUF_CONFIG, buf_cfg.regval);

	channels = substream->runसमय->channels;
	cfg_val.regx.num_ch = channels - 2;
	अगर (channels <= 2)
		cfg_val.regx.layout = LAYOUT0;
	अन्यथा
		cfg_val.regx.layout = LAYOUT1;

	अगर (substream->runसमय->क्रमmat == SNDRV_PCM_FORMAT_S16_LE)
		cfg_val.regx.packet_mode = 1;

	अगर (substream->runसमय->क्रमmat == SNDRV_PCM_FORMAT_S32_LE)
		cfg_val.regx.left_align = 1;

	cfg_val.regx.val_bit = 1;

	/* fix up the DP bits */
	अगर (पूर्णांकelhaddata->dp_output) अणु
		cfg_val.regx.dp_modei = 1;
		cfg_val.regx.set = 1;
	पूर्ण

	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_CONFIG, cfg_val.regval);
	पूर्णांकelhaddata->aud_config = cfg_val;
	वापस 0;
पूर्ण

/*
 * Compute derived values in channel_allocations[].
 */
अटल व्योम init_channel_allocations(व्योम)
अणु
	पूर्णांक i, j;
	काष्ठा cea_channel_speaker_allocation *p;

	क्रम (i = 0; i < ARRAY_SIZE(channel_allocations); i++) अणु
		p = channel_allocations + i;
		p->channels = 0;
		p->spk_mask = 0;
		क्रम (j = 0; j < ARRAY_SIZE(p->speakers); j++)
			अगर (p->speakers[j]) अणु
				p->channels++;
				p->spk_mask |= p->speakers[j];
			पूर्ण
	पूर्ण
पूर्ण

/*
 * The transक्रमmation takes two steps:
 *
 *      eld->spk_alloc => (eld_speaker_allocation_bits[]) => spk_mask
 *            spk_mask => (channel_allocations[])         => ai->CA
 *
 * TODO: it could select the wrong CA from multiple candidates.
 */
अटल पूर्णांक had_channel_allocation(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata,
				  पूर्णांक channels)
अणु
	पूर्णांक i;
	पूर्णांक ca = 0;
	पूर्णांक spk_mask = 0;

	/*
	 * CA शेषs to 0 क्रम basic stereo audio
	 */
	अगर (channels <= 2)
		वापस 0;

	/*
	 * expand ELD's speaker allocation mask
	 *
	 * ELD tells the speaker mask in a compact(paired) क्रमm,
	 * expand ELD's notions to match the ones used by Audio InfoFrame.
	 */

	क्रम (i = 0; i < ARRAY_SIZE(eld_speaker_allocation_bits); i++) अणु
		अगर (पूर्णांकelhaddata->eld[DRM_ELD_SPEAKER] & (1 << i))
			spk_mask |= eld_speaker_allocation_bits[i];
	पूर्ण

	/* search क्रम the first working match in the CA table */
	क्रम (i = 0; i < ARRAY_SIZE(channel_allocations); i++) अणु
		अगर (channels == channel_allocations[i].channels &&
		(spk_mask & channel_allocations[i].spk_mask) ==
				channel_allocations[i].spk_mask) अणु
			ca = channel_allocations[i].ca_index;
			अवरोध;
		पूर्ण
	पूर्ण

	dev_dbg(पूर्णांकelhaddata->dev, "select CA 0x%x for %d\n", ca, channels);

	वापस ca;
पूर्ण

/* from speaker bit mask to ALSA API channel position */
अटल पूर्णांक spk_to_chmap(पूर्णांक spk)
अणु
	स्थिर काष्ठा channel_map_table *t = map_tables;

	क्रम (; t->map; t++) अणु
		अगर (t->spk_mask == spk)
			वापस t->map;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम had_build_channel_allocation_map(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	पूर्णांक i, c;
	पूर्णांक spk_mask = 0;
	काष्ठा snd_pcm_chmap_elem *chmap;
	u8 eld_high, eld_high_mask = 0xF0;
	u8 high_msb;

	kमुक्त(पूर्णांकelhaddata->chmap->chmap);
	पूर्णांकelhaddata->chmap->chmap = शून्य;

	chmap = kzalloc(माप(*chmap), GFP_KERNEL);
	अगर (!chmap)
		वापस;

	dev_dbg(पूर्णांकelhaddata->dev, "eld speaker = %x\n",
		पूर्णांकelhaddata->eld[DRM_ELD_SPEAKER]);

	/* WA: Fix the max channel supported to 8 */

	/*
	 * Sink may support more than 8 channels, अगर eld_high has more than
	 * one bit set. SOC supports max 8 channels.
	 * Refer eld_speaker_allocation_bits, क्रम sink speaker allocation
	 */

	/* अगर 0x2F < eld < 0x4F fall back to 0x2f, अन्यथा fall back to 0x4F */
	eld_high = पूर्णांकelhaddata->eld[DRM_ELD_SPEAKER] & eld_high_mask;
	अगर ((eld_high & (eld_high-1)) && (eld_high > 0x1F)) अणु
		/* eld_high & (eld_high-1): अगर more than 1 bit set */
		/* 0x1F: 7 channels */
		क्रम (i = 1; i < 4; i++) अणु
			high_msb = eld_high & (0x80 >> i);
			अगर (high_msb) अणु
				पूर्णांकelhaddata->eld[DRM_ELD_SPEAKER] &=
					high_msb | 0xF;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(eld_speaker_allocation_bits); i++) अणु
		अगर (पूर्णांकelhaddata->eld[DRM_ELD_SPEAKER] & (1 << i))
			spk_mask |= eld_speaker_allocation_bits[i];
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(channel_allocations); i++) अणु
		अगर (spk_mask == channel_allocations[i].spk_mask) अणु
			क्रम (c = 0; c < channel_allocations[i].channels; c++) अणु
				chmap->map[c] = spk_to_chmap(
					channel_allocations[i].speakers[
						(MAX_SPEAKERS - 1) - c]);
			पूर्ण
			chmap->channels = channel_allocations[i].channels;
			पूर्णांकelhaddata->chmap->chmap = chmap;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i >= ARRAY_SIZE(channel_allocations))
		kमुक्त(chmap);
पूर्ण

/*
 * ALSA API channel-map control callbacks
 */
अटल पूर्णांक had_chmap_ctl_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = HAD_MAX_CHANNEL;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = SNDRV_CHMAP_LAST;
	वापस 0;
पूर्ण

अटल पूर्णांक had_chmap_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcm_chmap *info = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata = info->निजी_data;
	पूर्णांक i;
	स्थिर काष्ठा snd_pcm_chmap_elem *chmap;

	स_रखो(ucontrol->value.पूर्णांकeger.value, 0,
	       माप(दीर्घ) * HAD_MAX_CHANNEL);
	mutex_lock(&पूर्णांकelhaddata->mutex);
	अगर (!पूर्णांकelhaddata->chmap->chmap) अणु
		mutex_unlock(&पूर्णांकelhaddata->mutex);
		वापस 0;
	पूर्ण

	chmap = पूर्णांकelhaddata->chmap->chmap;
	क्रम (i = 0; i < chmap->channels; i++)
		ucontrol->value.पूर्णांकeger.value[i] = chmap->map[i];
	mutex_unlock(&पूर्णांकelhaddata->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक had_रेजिस्टर_chmap_ctls(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata,
						काष्ठा snd_pcm *pcm)
अणु
	पूर्णांक err;

	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			शून्य, 0, (अचिन्हित दीर्घ)पूर्णांकelhaddata,
			&पूर्णांकelhaddata->chmap);
	अगर (err < 0)
		वापस err;

	पूर्णांकelhaddata->chmap->निजी_data = पूर्णांकelhaddata;
	पूर्णांकelhaddata->chmap->kctl->info = had_chmap_ctl_info;
	पूर्णांकelhaddata->chmap->kctl->get = had_chmap_ctl_get;
	पूर्णांकelhaddata->chmap->chmap = शून्य;
	वापस 0;
पूर्ण

/*
 * Initialize Data Island Packets रेजिस्टरs
 * This function is called in the prepare callback
 */
अटल व्योम had_prog_dip(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	पूर्णांक i;
	जोड़ aud_ctrl_st ctrl_state = अणु.regval = 0पूर्ण;
	जोड़ aud_info_frame2 frame2 = अणु.regval = 0पूर्ण;
	जोड़ aud_info_frame3 frame3 = अणु.regval = 0पूर्ण;
	u8 checksum = 0;
	u32 info_frame;
	पूर्णांक channels;
	पूर्णांक ca;

	channels = substream->runसमय->channels;

	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_CNTL_ST, ctrl_state.regval);

	ca = had_channel_allocation(पूर्णांकelhaddata, channels);
	अगर (पूर्णांकelhaddata->dp_output) अणु
		info_frame = DP_INFO_FRAME_WORD1;
		frame2.regval = (substream->runसमय->channels - 1) | (ca << 24);
	पूर्ण अन्यथा अणु
		info_frame = HDMI_INFO_FRAME_WORD1;
		frame2.regx.chnl_cnt = substream->runसमय->channels - 1;
		frame3.regx.chnl_alloc = ca;

		/* Calculte the byte wide checksum क्रम all valid DIP words */
		क्रम (i = 0; i < BYTES_PER_WORD; i++)
			checksum += (info_frame >> (i * 8)) & 0xff;
		क्रम (i = 0; i < BYTES_PER_WORD; i++)
			checksum += (frame2.regval >> (i * 8)) & 0xff;
		क्रम (i = 0; i < BYTES_PER_WORD; i++)
			checksum += (frame3.regval >> (i * 8)) & 0xff;

		frame2.regx.chksum = -(checksum);
	पूर्ण

	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_HDMIW_INFOFR, info_frame);
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_HDMIW_INFOFR, frame2.regval);
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_HDMIW_INFOFR, frame3.regval);

	/* program reमुख्यing DIP words with zero */
	क्रम (i = 0; i < HAD_MAX_DIP_WORDS-VALID_DIP_WORDS; i++)
		had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_HDMIW_INFOFR, 0x0);

	ctrl_state.regx.dip_freq = 1;
	ctrl_state.regx.dip_en_sta = 1;
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_CNTL_ST, ctrl_state.regval);
पूर्ण

अटल पूर्णांक had_calculate_maud_value(u32 aud_samp_freq, u32 link_rate)
अणु
	u32 maud_val;

	/* Select maud according to DP 1.2 spec */
	अगर (link_rate == DP_2_7_GHZ) अणु
		चयन (aud_samp_freq) अणु
		हाल AUD_SAMPLE_RATE_32:
			maud_val = AUD_SAMPLE_RATE_32_DP_2_7_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_44_1:
			maud_val = AUD_SAMPLE_RATE_44_1_DP_2_7_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_48:
			maud_val = AUD_SAMPLE_RATE_48_DP_2_7_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_88_2:
			maud_val = AUD_SAMPLE_RATE_88_2_DP_2_7_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_96:
			maud_val = AUD_SAMPLE_RATE_96_DP_2_7_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_176_4:
			maud_val = AUD_SAMPLE_RATE_176_4_DP_2_7_MAUD_VAL;
			अवरोध;

		हाल HAD_MAX_RATE:
			maud_val = HAD_MAX_RATE_DP_2_7_MAUD_VAL;
			अवरोध;

		शेष:
			maud_val = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (link_rate == DP_1_62_GHZ) अणु
		चयन (aud_samp_freq) अणु
		हाल AUD_SAMPLE_RATE_32:
			maud_val = AUD_SAMPLE_RATE_32_DP_1_62_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_44_1:
			maud_val = AUD_SAMPLE_RATE_44_1_DP_1_62_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_48:
			maud_val = AUD_SAMPLE_RATE_48_DP_1_62_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_88_2:
			maud_val = AUD_SAMPLE_RATE_88_2_DP_1_62_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_96:
			maud_val = AUD_SAMPLE_RATE_96_DP_1_62_MAUD_VAL;
			अवरोध;

		हाल AUD_SAMPLE_RATE_176_4:
			maud_val = AUD_SAMPLE_RATE_176_4_DP_1_62_MAUD_VAL;
			अवरोध;

		हाल HAD_MAX_RATE:
			maud_val = HAD_MAX_RATE_DP_1_62_MAUD_VAL;
			अवरोध;

		शेष:
			maud_val = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		maud_val = -EINVAL;

	वापस maud_val;
पूर्ण

/*
 * Program HDMI audio CTS value
 *
 * @aud_samp_freq: sampling frequency of audio data
 * @पंचांगds: sampling frequency of the display data
 * @link_rate: DP link rate
 * @n_param: N value, depends on aud_samp_freq
 * @पूर्णांकelhaddata: substream निजी data
 *
 * Program CTS रेजिस्टर based on the audio and display sampling frequency
 */
अटल व्योम had_prog_cts(u32 aud_samp_freq, u32 पंचांगds, u32 link_rate,
			 u32 n_param, काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	u32 cts_val;
	u64 भागidend, भागisor;

	अगर (पूर्णांकelhaddata->dp_output) अणु
		/* Substitute cts_val with Maud according to DP 1.2 spec*/
		cts_val = had_calculate_maud_value(aud_samp_freq, link_rate);
	पूर्ण अन्यथा अणु
		/* Calculate CTS according to HDMI 1.3a spec*/
		भागidend = (u64)पंचांगds * n_param*1000;
		भागisor = 128 * aud_samp_freq;
		cts_val = भाग64_u64(भागidend, भागisor);
	पूर्ण
	dev_dbg(पूर्णांकelhaddata->dev, "TMDS value=%d, N value=%d, CTS Value=%d\n",
		 पंचांगds, n_param, cts_val);
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_HDMI_CTS, (BIT(24) | cts_val));
पूर्ण

अटल पूर्णांक had_calculate_n_value(u32 aud_samp_freq)
अणु
	पूर्णांक n_val;

	/* Select N according to HDMI 1.3a spec*/
	चयन (aud_samp_freq) अणु
	हाल AUD_SAMPLE_RATE_32:
		n_val = 4096;
		अवरोध;

	हाल AUD_SAMPLE_RATE_44_1:
		n_val = 6272;
		अवरोध;

	हाल AUD_SAMPLE_RATE_48:
		n_val = 6144;
		अवरोध;

	हाल AUD_SAMPLE_RATE_88_2:
		n_val = 12544;
		अवरोध;

	हाल AUD_SAMPLE_RATE_96:
		n_val = 12288;
		अवरोध;

	हाल AUD_SAMPLE_RATE_176_4:
		n_val = 25088;
		अवरोध;

	हाल HAD_MAX_RATE:
		n_val = 24576;
		अवरोध;

	शेष:
		n_val = -EINVAL;
		अवरोध;
	पूर्ण
	वापस n_val;
पूर्ण

/*
 * Program HDMI audio N value
 *
 * @aud_samp_freq: sampling frequency of audio data
 * @n_param: N value, depends on aud_samp_freq
 * @पूर्णांकelhaddata: substream निजी data
 *
 * This function is called in the prepare callback.
 * It programs based on the audio and display sampling frequency
 */
अटल पूर्णांक had_prog_n(u32 aud_samp_freq, u32 *n_param,
		      काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	पूर्णांक n_val;

	अगर (पूर्णांकelhaddata->dp_output) अणु
		/*
		 * According to DP specs, Maud and Naud values hold
		 * a relationship, which is stated as:
		 * Maud/Naud = 512 * fs / f_LS_Clk
		 * where, fs is the sampling frequency of the audio stream
		 * and Naud is 32768 क्रम Async घड़ी.
		 */

		n_val = DP_NAUD_VAL;
	पूर्ण अन्यथा
		n_val =	had_calculate_n_value(aud_samp_freq);

	अगर (n_val < 0)
		वापस n_val;

	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_N_ENABLE, (BIT(24) | n_val));
	*n_param = n_val;
	वापस 0;
पूर्ण

/*
 * PCM ring buffer handling
 *
 * The hardware provides a ring buffer with the fixed 4 buffer descriptors
 * (BDs).  The driver maps these 4 BDs onto the PCM ring buffer.  The mapping
 * moves at each period elapsed.  The below illustrates how it works:
 *
 * At समय=0
 *  PCM | 0 | 1 | 2 | 3 | 4 | 5 | .... |n-1|
 *  BD  | 0 | 1 | 2 | 3 |
 *
 * At समय=1 (period elapsed)
 *  PCM | 0 | 1 | 2 | 3 | 4 | 5 | .... |n-1|
 *  BD      | 1 | 2 | 3 | 0 |
 *
 * At समय=2 (second period elapsed)
 *  PCM | 0 | 1 | 2 | 3 | 4 | 5 | .... |n-1|
 *  BD          | 2 | 3 | 0 | 1 |
 *
 * The bd_head field poपूर्णांकs to the index of the BD to be पढ़ो.  It's also the
 * position to be filled at next.  The pcm_head and the pcm_filled fields
 * poपूर्णांक to the indices of the current position and of the next position to
 * be filled, respectively.  For PCM buffer there are both _head and _filled
 * because they may be dअगरference when nperiods > 4.  For example, in the
 * example above at t=1, bd_head=1 and pcm_head=1 जबतक pcm_filled=5:
 *
 * pcm_head (=1) --v               v-- pcm_filled (=5)
 *       PCM | 0 | 1 | 2 | 3 | 4 | 5 | .... |n-1|
 *       BD      | 1 | 2 | 3 | 0 |
 *  bd_head (=1) --^               ^-- next to fill (= bd_head)
 *
 * For nperiods < 4, the reमुख्यing BDs out of 4 are marked as invalid, so that
 * the hardware skips those BDs in the loop.
 *
 * An exceptional setup is the हाल with nperiods=1.  Since we have to update
 * BDs after finishing one BD processing, we'd need at least two BDs, where
 * both BDs poपूर्णांक to the same content, the same address, the same size of the
 * whole PCM buffer.
 */

#घोषणा AUD_BUF_ADDR(x)		(AUD_BUF_A_ADDR + (x) * HAD_REG_WIDTH)
#घोषणा AUD_BUF_LEN(x)		(AUD_BUF_A_LENGTH + (x) * HAD_REG_WIDTH)

/* Set up a buffer descriptor at the "filled" position */
अटल व्योम had_prog_bd(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	पूर्णांक idx = पूर्णांकelhaddata->bd_head;
	पूर्णांक ofs = पूर्णांकelhaddata->pcmbuf_filled * पूर्णांकelhaddata->period_bytes;
	u32 addr = substream->runसमय->dma_addr + ofs;

	addr |= AUD_BUF_VALID;
	अगर (!substream->runसमय->no_period_wakeup)
		addr |= AUD_BUF_INTR_EN;
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_BUF_ADDR(idx), addr);
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_BUF_LEN(idx),
			   पूर्णांकelhaddata->period_bytes);

	/* advance the indices to the next */
	पूर्णांकelhaddata->bd_head++;
	पूर्णांकelhaddata->bd_head %= पूर्णांकelhaddata->num_bds;
	पूर्णांकelhaddata->pcmbuf_filled++;
	पूर्णांकelhaddata->pcmbuf_filled %= substream->runसमय->periods;
पूर्ण

/* invalidate a buffer descriptor with the given index */
अटल व्योम had_invalidate_bd(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata,
			      पूर्णांक idx)
अणु
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_BUF_ADDR(idx), 0);
	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_BUF_LEN(idx), 0);
पूर्ण

/* Initial programming of ring buffer */
अटल व्योम had_init_ringbuf(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक i, num_periods;

	num_periods = runसमय->periods;
	पूर्णांकelhaddata->num_bds = min(num_periods, HAD_NUM_OF_RING_BUFS);
	/* set the minimum 2 BDs क्रम num_periods=1 */
	पूर्णांकelhaddata->num_bds = max(पूर्णांकelhaddata->num_bds, 2U);
	पूर्णांकelhaddata->period_bytes =
		frames_to_bytes(runसमय, runसमय->period_size);
	WARN_ON(पूर्णांकelhaddata->period_bytes & 0x3f);

	पूर्णांकelhaddata->bd_head = 0;
	पूर्णांकelhaddata->pcmbuf_head = 0;
	पूर्णांकelhaddata->pcmbuf_filled = 0;

	क्रम (i = 0; i < HAD_NUM_OF_RING_BUFS; i++) अणु
		अगर (i < पूर्णांकelhaddata->num_bds)
			had_prog_bd(substream, पूर्णांकelhaddata);
		अन्यथा /* invalidate the rest */
			had_invalidate_bd(पूर्णांकelhaddata, i);
	पूर्ण

	पूर्णांकelhaddata->bd_head = 0; /* reset at head again beक्रमe starting */
पूर्ण

/* process a bd, advance to the next */
अटल व्योम had_advance_ringbuf(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	पूर्णांक num_periods = substream->runसमय->periods;

	/* reprogram the next buffer */
	had_prog_bd(substream, पूर्णांकelhaddata);

	/* proceed to next */
	पूर्णांकelhaddata->pcmbuf_head++;
	पूर्णांकelhaddata->pcmbuf_head %= num_periods;
पूर्ण

/* process the current BD(s);
 * वापसs the current PCM buffer byte position, or -EPIPE क्रम underrun.
 */
अटल पूर्णांक had_process_ringbuf(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	पूर्णांक len, processed;
	अचिन्हित दीर्घ flags;

	processed = 0;
	spin_lock_irqsave(&पूर्णांकelhaddata->had_spinlock, flags);
	क्रम (;;) अणु
		/* get the reमुख्यing bytes on the buffer */
		had_पढ़ो_रेजिस्टर(पूर्णांकelhaddata,
				  AUD_BUF_LEN(पूर्णांकelhaddata->bd_head),
				  &len);
		अगर (len < 0 || len > पूर्णांकelhaddata->period_bytes) अणु
			dev_dbg(पूर्णांकelhaddata->dev, "Invalid buf length %d\n",
				len);
			len = -EPIPE;
			जाओ out;
		पूर्ण

		अगर (len > 0) /* OK, this is the current buffer */
			अवरोध;

		/* len=0 => alपढ़ोy empty, check the next buffer */
		अगर (++processed >= पूर्णांकelhaddata->num_bds) अणु
			len = -EPIPE; /* all empty? - report underrun */
			जाओ out;
		पूर्ण
		had_advance_ringbuf(substream, पूर्णांकelhaddata);
	पूर्ण

	len = पूर्णांकelhaddata->period_bytes - len;
	len += पूर्णांकelhaddata->period_bytes * पूर्णांकelhaddata->pcmbuf_head;
 out:
	spin_unlock_irqrestore(&पूर्णांकelhaddata->had_spinlock, flags);
	वापस len;
पूर्ण

/* called from irq handler */
अटल व्योम had_process_buffer_करोne(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	काष्ठा snd_pcm_substream *substream;

	substream = had_substream_get(पूर्णांकelhaddata);
	अगर (!substream)
		वापस; /* no stream? - bail out */

	अगर (!पूर्णांकelhaddata->connected) अणु
		snd_pcm_stop_xrun(substream);
		जाओ out; /* disconnected? - bail out */
	पूर्ण

	/* process or stop the stream */
	अगर (had_process_ringbuf(substream, पूर्णांकelhaddata) < 0)
		snd_pcm_stop_xrun(substream);
	अन्यथा
		snd_pcm_period_elapsed(substream);

 out:
	had_substream_put(पूर्णांकelhaddata);
पूर्ण

/*
 * The पूर्णांकerrupt status 'sticky' bits might not be cleared by
 * setting '1' to that bit once...
 */
अटल व्योम रुको_clear_underrun_bit(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	पूर्णांक i;
	u32 val;

	क्रम (i = 0; i < 100; i++) अणु
		/* clear bit30, 31 AUD_HDMI_STATUS */
		had_पढ़ो_रेजिस्टर(पूर्णांकelhaddata, AUD_HDMI_STATUS, &val);
		अगर (!(val & AUD_HDMI_STATUS_MASK_UNDERRUN))
			वापस;
		udelay(100);
		cond_resched();
		had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_HDMI_STATUS, val);
	पूर्ण
	dev_err(पूर्णांकelhaddata->dev, "Unable to clear UNDERRUN bits\n");
पूर्ण

/* Perक्रमm some reset procedure but only when need_reset is set;
 * this is called from prepare or hw_मुक्त callbacks once after trigger STOP
 * or underrun has been processed in order to settle करोwn the h/w state.
 */
अटल व्योम had_करो_reset(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	अगर (!पूर्णांकelhaddata->need_reset || !पूर्णांकelhaddata->connected)
		वापस;

	/* Reset buffer poपूर्णांकers */
	had_reset_audio(पूर्णांकelhaddata);
	रुको_clear_underrun_bit(पूर्णांकelhaddata);
	पूर्णांकelhaddata->need_reset = false;
पूर्ण

/* called from irq handler */
अटल व्योम had_process_buffer_underrun(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	काष्ठा snd_pcm_substream *substream;

	/* Report UNDERRUN error to above layers */
	substream = had_substream_get(पूर्णांकelhaddata);
	अगर (substream) अणु
		snd_pcm_stop_xrun(substream);
		had_substream_put(पूर्णांकelhaddata);
	पूर्ण
	पूर्णांकelhaddata->need_reset = true;
पूर्ण

/*
 * ALSA PCM खोलो callback
 */
अटल पूर्णांक had_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata;
	काष्ठा snd_pcm_runसमय *runसमय;
	पूर्णांक retval;

	पूर्णांकelhaddata = snd_pcm_substream_chip(substream);
	runसमय = substream->runसमय;

	pm_runसमय_get_sync(पूर्णांकelhaddata->dev);

	/* set the runसमय hw parameter with local snd_pcm_hardware काष्ठा */
	runसमय->hw = had_pcm_hardware;

	retval = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
			 SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (retval < 0)
		जाओ error;

	/* Make sure, that the period size is always aligned
	 * 64byte boundary
	 */
	retval = snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 64);
	अगर (retval < 0)
		जाओ error;

	retval = snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	अगर (retval < 0)
		जाओ error;

	/* expose PCM substream */
	spin_lock_irq(&पूर्णांकelhaddata->had_spinlock);
	पूर्णांकelhaddata->stream_info.substream = substream;
	पूर्णांकelhaddata->stream_info.substream_refcount++;
	spin_unlock_irq(&पूर्णांकelhaddata->had_spinlock);

	वापस retval;
 error:
	pm_runसमय_mark_last_busy(पूर्णांकelhaddata->dev);
	pm_runसमय_put_स्वतःsuspend(पूर्णांकelhaddata->dev);
	वापस retval;
पूर्ण

/*
 * ALSA PCM बंद callback
 */
अटल पूर्णांक had_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata;

	पूर्णांकelhaddata = snd_pcm_substream_chip(substream);

	/* unreference and sync with the pending PCM accesses */
	spin_lock_irq(&पूर्णांकelhaddata->had_spinlock);
	पूर्णांकelhaddata->stream_info.substream = शून्य;
	पूर्णांकelhaddata->stream_info.substream_refcount--;
	जबतक (पूर्णांकelhaddata->stream_info.substream_refcount > 0) अणु
		spin_unlock_irq(&पूर्णांकelhaddata->had_spinlock);
		cpu_relax();
		spin_lock_irq(&पूर्णांकelhaddata->had_spinlock);
	पूर्ण
	spin_unlock_irq(&पूर्णांकelhaddata->had_spinlock);

	pm_runसमय_mark_last_busy(पूर्णांकelhaddata->dev);
	pm_runसमय_put_स्वतःsuspend(पूर्णांकelhaddata->dev);
	वापस 0;
पूर्ण

/*
 * ALSA PCM hw_params callback
 */
अटल पूर्णांक had_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata;
	पूर्णांक buf_size;

	पूर्णांकelhaddata = snd_pcm_substream_chip(substream);
	buf_size = params_buffer_bytes(hw_params);
	dev_dbg(पूर्णांकelhaddata->dev, "%s:allocated memory = %d\n",
		__func__, buf_size);
	वापस 0;
पूर्ण

/*
 * ALSA PCM hw_मुक्त callback
 */
अटल पूर्णांक had_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata;

	पूर्णांकelhaddata = snd_pcm_substream_chip(substream);
	had_करो_reset(पूर्णांकelhaddata);

	वापस 0;
पूर्ण

/*
 * ALSA PCM trigger callback
 */
अटल पूर्णांक had_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक retval = 0;
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata;

	पूर्णांकelhaddata = snd_pcm_substream_chip(substream);

	spin_lock(&पूर्णांकelhaddata->had_spinlock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		/* Enable Audio */
		had_ack_irqs(पूर्णांकelhaddata); /* FIXME: करो we need this? */
		had_enable_audio(पूर्णांकelhaddata, true);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		/* Disable Audio */
		had_enable_audio(पूर्णांकelhaddata, false);
		पूर्णांकelhaddata->need_reset = true;
		अवरोध;

	शेष:
		retval = -EINVAL;
	पूर्ण
	spin_unlock(&पूर्णांकelhaddata->had_spinlock);
	वापस retval;
पूर्ण

/*
 * ALSA PCM prepare callback
 */
अटल पूर्णांक had_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक retval;
	u32 disp_samp_freq, n_param;
	u32 link_rate = 0;
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata;
	काष्ठा snd_pcm_runसमय *runसमय;

	पूर्णांकelhaddata = snd_pcm_substream_chip(substream);
	runसमय = substream->runसमय;

	dev_dbg(पूर्णांकelhaddata->dev, "period_size=%d\n",
		(पूर्णांक)frames_to_bytes(runसमय, runसमय->period_size));
	dev_dbg(पूर्णांकelhaddata->dev, "periods=%d\n", runसमय->periods);
	dev_dbg(पूर्णांकelhaddata->dev, "buffer_size=%d\n",
		(पूर्णांक)snd_pcm_lib_buffer_bytes(substream));
	dev_dbg(पूर्णांकelhaddata->dev, "rate=%d\n", runसमय->rate);
	dev_dbg(पूर्णांकelhaddata->dev, "channels=%d\n", runसमय->channels);

	had_करो_reset(पूर्णांकelhaddata);

	/* Get N value in KHz */
	disp_samp_freq = पूर्णांकelhaddata->पंचांगds_घड़ी_speed;

	retval = had_prog_n(substream->runसमय->rate, &n_param, पूर्णांकelhaddata);
	अगर (retval) अणु
		dev_err(पूर्णांकelhaddata->dev,
			"programming N value failed %#x\n", retval);
		जाओ prep_end;
	पूर्ण

	अगर (पूर्णांकelhaddata->dp_output)
		link_rate = पूर्णांकelhaddata->link_rate;

	had_prog_cts(substream->runसमय->rate, disp_samp_freq, link_rate,
		     n_param, पूर्णांकelhaddata);

	had_prog_dip(substream, पूर्णांकelhaddata);

	retval = had_init_audio_ctrl(substream, पूर्णांकelhaddata);

	/* Prog buffer address */
	had_init_ringbuf(substream, पूर्णांकelhaddata);

	/*
	 * Program channel mapping in following order:
	 * FL, FR, C, LFE, RL, RR
	 */

	had_ग_लिखो_रेजिस्टर(पूर्णांकelhaddata, AUD_BUF_CH_SWAP, SWAP_LFE_CENTER);

prep_end:
	वापस retval;
पूर्ण

/*
 * ALSA PCM poपूर्णांकer callback
 */
अटल snd_pcm_uframes_t had_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata;
	पूर्णांक len;

	पूर्णांकelhaddata = snd_pcm_substream_chip(substream);

	अगर (!पूर्णांकelhaddata->connected)
		वापस SNDRV_PCM_POS_XRUN;

	len = had_process_ringbuf(substream, पूर्णांकelhaddata);
	अगर (len < 0)
		वापस SNDRV_PCM_POS_XRUN;
	len = bytes_to_frames(substream->runसमय, len);
	/* wrapping may happen when periods=1 */
	len %= substream->runसमय->buffer_size;
	वापस len;
पूर्ण

/*
 * ALSA PCM mmap callback
 */
अटल पूर्णांक had_pcm_mmap(काष्ठा snd_pcm_substream *substream,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	वापस remap_pfn_range(vma, vma->vm_start,
			substream->dma_buffer.addr >> PAGE_SHIFT,
			vma->vm_end - vma->vm_start, vma->vm_page_prot);
पूर्ण

/*
 * ALSA PCM ops
 */
अटल स्थिर काष्ठा snd_pcm_ops had_pcm_ops = अणु
	.खोलो =		had_pcm_खोलो,
	.बंद =	had_pcm_बंद,
	.hw_params =	had_pcm_hw_params,
	.hw_मुक्त =	had_pcm_hw_मुक्त,
	.prepare =	had_pcm_prepare,
	.trigger =	had_pcm_trigger,
	.poपूर्णांकer =	had_pcm_poपूर्णांकer,
	.mmap =		had_pcm_mmap,
पूर्ण;

/* process mode change of the running stream; called in mutex */
अटल पूर्णांक had_process_mode_change(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक retval = 0;
	u32 disp_samp_freq, n_param;
	u32 link_rate = 0;

	substream = had_substream_get(पूर्णांकelhaddata);
	अगर (!substream)
		वापस 0;

	/* Disable Audio */
	had_enable_audio(पूर्णांकelhaddata, false);

	/* Update CTS value */
	disp_samp_freq = पूर्णांकelhaddata->पंचांगds_घड़ी_speed;

	retval = had_prog_n(substream->runसमय->rate, &n_param, पूर्णांकelhaddata);
	अगर (retval) अणु
		dev_err(पूर्णांकelhaddata->dev,
			"programming N value failed %#x\n", retval);
		जाओ out;
	पूर्ण

	अगर (पूर्णांकelhaddata->dp_output)
		link_rate = पूर्णांकelhaddata->link_rate;

	had_prog_cts(substream->runसमय->rate, disp_samp_freq, link_rate,
		     n_param, पूर्णांकelhaddata);

	/* Enable Audio */
	had_enable_audio(पूर्णांकelhaddata, true);

out:
	had_substream_put(पूर्णांकelhaddata);
	वापस retval;
पूर्ण

/* process hot plug, called from wq with mutex locked */
अटल व्योम had_process_hot_plug(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	काष्ठा snd_pcm_substream *substream;

	spin_lock_irq(&पूर्णांकelhaddata->had_spinlock);
	अगर (पूर्णांकelhaddata->connected) अणु
		dev_dbg(पूर्णांकelhaddata->dev, "Device already connected\n");
		spin_unlock_irq(&पूर्णांकelhaddata->had_spinlock);
		वापस;
	पूर्ण

	/* Disable Audio */
	had_enable_audio(पूर्णांकelhaddata, false);

	पूर्णांकelhaddata->connected = true;
	dev_dbg(पूर्णांकelhaddata->dev,
		"%s @ %d:DEBUG PLUG/UNPLUG : HAD_DRV_CONNECTED\n",
			__func__, __LINE__);
	spin_unlock_irq(&पूर्णांकelhaddata->had_spinlock);

	had_build_channel_allocation_map(पूर्णांकelhaddata);

	/* Report to above ALSA layer */
	substream = had_substream_get(पूर्णांकelhaddata);
	अगर (substream) अणु
		snd_pcm_stop_xrun(substream);
		had_substream_put(पूर्णांकelhaddata);
	पूर्ण

	snd_jack_report(पूर्णांकelhaddata->jack, SND_JACK_AVOUT);
पूर्ण

/* process hot unplug, called from wq with mutex locked */
अटल व्योम had_process_hot_unplug(काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata)
अणु
	काष्ठा snd_pcm_substream *substream;

	spin_lock_irq(&पूर्णांकelhaddata->had_spinlock);
	अगर (!पूर्णांकelhaddata->connected) अणु
		dev_dbg(पूर्णांकelhaddata->dev, "Device already disconnected\n");
		spin_unlock_irq(&पूर्णांकelhaddata->had_spinlock);
		वापस;

	पूर्ण

	/* Disable Audio */
	had_enable_audio(पूर्णांकelhaddata, false);

	पूर्णांकelhaddata->connected = false;
	dev_dbg(पूर्णांकelhaddata->dev,
		"%s @ %d:DEBUG PLUG/UNPLUG : HAD_DRV_DISCONNECTED\n",
			__func__, __LINE__);
	spin_unlock_irq(&पूर्णांकelhaddata->had_spinlock);

	kमुक्त(पूर्णांकelhaddata->chmap->chmap);
	पूर्णांकelhaddata->chmap->chmap = शून्य;

	/* Report to above ALSA layer */
	substream = had_substream_get(पूर्णांकelhaddata);
	अगर (substream) अणु
		snd_pcm_stop_xrun(substream);
		had_substream_put(पूर्णांकelhaddata);
	पूर्ण

	snd_jack_report(पूर्णांकelhaddata->jack, 0);
पूर्ण

/*
 * ALSA iec958 and ELD controls
 */

अटल पूर्णांक had_iec958_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक had_iec958_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata = snd_kcontrol_chip(kcontrol);

	mutex_lock(&पूर्णांकelhaddata->mutex);
	ucontrol->value.iec958.status[0] = (पूर्णांकelhaddata->aes_bits >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (पूर्णांकelhaddata->aes_bits >> 8) & 0xff;
	ucontrol->value.iec958.status[2] =
					(पूर्णांकelhaddata->aes_bits >> 16) & 0xff;
	ucontrol->value.iec958.status[3] =
					(पूर्णांकelhaddata->aes_bits >> 24) & 0xff;
	mutex_unlock(&पूर्णांकelhaddata->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक had_iec958_mask_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक had_iec958_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;

	val = (ucontrol->value.iec958.status[0] << 0) |
		(ucontrol->value.iec958.status[1] << 8) |
		(ucontrol->value.iec958.status[2] << 16) |
		(ucontrol->value.iec958.status[3] << 24);
	mutex_lock(&पूर्णांकelhaddata->mutex);
	अगर (पूर्णांकelhaddata->aes_bits != val) अणु
		पूर्णांकelhaddata->aes_bits = val;
		changed = 1;
	पूर्ण
	mutex_unlock(&पूर्णांकelhaddata->mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक had_ctl_eld_info(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = HDMI_MAX_ELD_BYTES;
	वापस 0;
पूर्ण

अटल पूर्णांक had_ctl_eld_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_पूर्णांकelhad *पूर्णांकelhaddata = snd_kcontrol_chip(kcontrol);

	mutex_lock(&पूर्णांकelhaddata->mutex);
	स_नकल(ucontrol->value.bytes.data, पूर्णांकelhaddata->eld,
	       HDMI_MAX_ELD_BYTES);
	mutex_unlock(&पूर्णांकelhaddata->mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new had_controls[] = अणु
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, MASK),
		.info = had_iec958_info, /* shared */
		.get = had_iec958_mask_get,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.info = had_iec958_info,
		.get = had_iec958_get,
		.put = had_iec958_put,
	पूर्ण,
	अणु
		.access = (SNDRV_CTL_ELEM_ACCESS_READ |
			   SNDRV_CTL_ELEM_ACCESS_VOLATILE),
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = "ELD",
		.info = had_ctl_eld_info,
		.get = had_ctl_eld_get,
	पूर्ण,
पूर्ण;

/*
 * audio पूर्णांकerrupt handler
 */
अटल irqवापस_t display_pipe_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_पूर्णांकelhad_card *card_ctx = dev_id;
	u32 audio_stat[3] = अणुपूर्ण;
	पूर्णांक pipe, port;

	क्रम_each_pipe(card_ctx, pipe) अणु
		/* use raw रेजिस्टर access to ack IRQs even जबतक disconnected */
		audio_stat[pipe] = had_पढ़ो_रेजिस्टर_raw(card_ctx, pipe,
							 AUD_HDMI_STATUS) &
			(HDMI_AUDIO_UNDERRUN | HDMI_AUDIO_BUFFER_DONE);

		अगर (audio_stat[pipe])
			had_ग_लिखो_रेजिस्टर_raw(card_ctx, pipe,
					       AUD_HDMI_STATUS, audio_stat[pipe]);
	पूर्ण

	क्रम_each_port(card_ctx, port) अणु
		काष्ठा snd_पूर्णांकelhad *ctx = &card_ctx->pcm_ctx[port];
		पूर्णांक pipe = ctx->pipe;

		अगर (pipe < 0)
			जारी;

		अगर (audio_stat[pipe] & HDMI_AUDIO_BUFFER_DONE)
			had_process_buffer_करोne(ctx);
		अगर (audio_stat[pipe] & HDMI_AUDIO_UNDERRUN)
			had_process_buffer_underrun(ctx);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * monitor plug/unplug notअगरication from i915; just kick off the work
 */
अटल व्योम notअगरy_audio_lpe(काष्ठा platक्रमm_device *pdev, पूर्णांक port)
अणु
	काष्ठा snd_पूर्णांकelhad_card *card_ctx = platक्रमm_get_drvdata(pdev);
	काष्ठा snd_पूर्णांकelhad *ctx;

	ctx = &card_ctx->pcm_ctx[single_port ? 0 : port];
	अगर (single_port)
		ctx->port = port;

	schedule_work(&ctx->hdmi_audio_wq);
पूर्ण

/* the work to handle monitor hot plug/unplug */
अटल व्योम had_audio_wq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा snd_पूर्णांकelhad *ctx =
		container_of(work, काष्ठा snd_पूर्णांकelhad, hdmi_audio_wq);
	काष्ठा पूर्णांकel_hdmi_lpe_audio_pdata *pdata = ctx->dev->platक्रमm_data;
	काष्ठा पूर्णांकel_hdmi_lpe_audio_port_pdata *ppdata = &pdata->port[ctx->port];

	pm_runसमय_get_sync(ctx->dev);
	mutex_lock(&ctx->mutex);
	अगर (ppdata->pipe < 0) अणु
		dev_dbg(ctx->dev, "%s: Event: HAD_NOTIFY_HOT_UNPLUG : port = %d\n",
			__func__, ctx->port);

		स_रखो(ctx->eld, 0, माप(ctx->eld)); /* clear the old ELD */

		ctx->dp_output = false;
		ctx->पंचांगds_घड़ी_speed = 0;
		ctx->link_rate = 0;

		/* Shut करोwn the stream */
		had_process_hot_unplug(ctx);

		ctx->pipe = -1;
	पूर्ण अन्यथा अणु
		dev_dbg(ctx->dev, "%s: HAD_NOTIFY_ELD : port = %d, tmds = %d\n",
			__func__, ctx->port, ppdata->ls_घड़ी);

		स_नकल(ctx->eld, ppdata->eld, माप(ctx->eld));

		ctx->dp_output = ppdata->dp_output;
		अगर (ctx->dp_output) अणु
			ctx->पंचांगds_घड़ी_speed = 0;
			ctx->link_rate = ppdata->ls_घड़ी;
		पूर्ण अन्यथा अणु
			ctx->पंचांगds_घड़ी_speed = ppdata->ls_घड़ी;
			ctx->link_rate = 0;
		पूर्ण

		/*
		 * Shut करोwn the stream beक्रमe we change
		 * the pipe assignment क्रम this pcm device
		 */
		had_process_hot_plug(ctx);

		ctx->pipe = ppdata->pipe;

		/* Restart the stream अगर necessary */
		had_process_mode_change(ctx);
	पूर्ण

	mutex_unlock(&ctx->mutex);
	pm_runसमय_mark_last_busy(ctx->dev);
	pm_runसमय_put_स्वतःsuspend(ctx->dev);
पूर्ण

/*
 * Jack पूर्णांकerface
 */
अटल पूर्णांक had_create_jack(काष्ठा snd_पूर्णांकelhad *ctx,
			   काष्ठा snd_pcm *pcm)
अणु
	अक्षर hdmi_str[32];
	पूर्णांक err;

	snम_लिखो(hdmi_str, माप(hdmi_str),
		 "HDMI/DP,pcm=%d", pcm->device);

	err = snd_jack_new(ctx->card_ctx->card, hdmi_str,
			   SND_JACK_AVOUT, &ctx->jack,
			   true, false);
	अगर (err < 0)
		वापस err;
	ctx->jack->निजी_data = ctx;
	वापस 0;
पूर्ण

/*
 * PM callbacks
 */

अटल पूर्णांक __maybe_unused hdmi_lpe_audio_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_पूर्णांकelhad_card *card_ctx = dev_get_drvdata(dev);

	snd_घातer_change_state(card_ctx->card, SNDRV_CTL_POWER_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused hdmi_lpe_audio_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_पूर्णांकelhad_card *card_ctx = dev_get_drvdata(dev);

	pm_runसमय_mark_last_busy(dev);

	snd_घातer_change_state(card_ctx->card, SNDRV_CTL_POWER_D0);

	वापस 0;
पूर्ण

/* release resources */
अटल व्योम hdmi_lpe_audio_मुक्त(काष्ठा snd_card *card)
अणु
	काष्ठा snd_पूर्णांकelhad_card *card_ctx = card->निजी_data;
	काष्ठा पूर्णांकel_hdmi_lpe_audio_pdata *pdata = card_ctx->dev->platक्रमm_data;
	पूर्णांक port;

	spin_lock_irq(&pdata->lpe_audio_slock);
	pdata->notअगरy_audio_lpe = शून्य;
	spin_unlock_irq(&pdata->lpe_audio_slock);

	क्रम_each_port(card_ctx, port) अणु
		काष्ठा snd_पूर्णांकelhad *ctx = &card_ctx->pcm_ctx[port];

		cancel_work_sync(&ctx->hdmi_audio_wq);
	पूर्ण

	अगर (card_ctx->mmio_start)
		iounmap(card_ctx->mmio_start);
	अगर (card_ctx->irq >= 0)
		मुक्त_irq(card_ctx->irq, card_ctx);
पूर्ण

/*
 * hdmi_lpe_audio_probe - start bridge with i915
 *
 * This function is called when the i915 driver creates the
 * hdmi-lpe-audio platक्रमm device.
 */
अटल पूर्णांक hdmi_lpe_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_पूर्णांकelhad_card *card_ctx;
	काष्ठा snd_पूर्णांकelhad *ctx;
	काष्ठा snd_pcm *pcm;
	काष्ठा पूर्णांकel_hdmi_lpe_audio_pdata *pdata;
	पूर्णांक irq;
	काष्ठा resource *res_mmio;
	पूर्णांक port, ret;

	pdata = pdev->dev.platक्रमm_data;
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "%s: quit: pdata not allocated by i915!!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* get resources */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	res_mmio = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res_mmio) अणु
		dev_err(&pdev->dev, "Could not get IO_MEM resources\n");
		वापस -ENXIO;
	पूर्ण

	/* create a card instance with ALSA framework */
	ret = snd_card_new(&pdev->dev, hdmi_card_index, hdmi_card_id,
			   THIS_MODULE, माप(*card_ctx), &card);
	अगर (ret)
		वापस ret;

	card_ctx = card->निजी_data;
	card_ctx->dev = &pdev->dev;
	card_ctx->card = card;
	म_नकल(card->driver, INTEL_HAD);
	म_नकल(card->लघुname, "Intel HDMI/DP LPE Audio");
	म_नकल(card->दीर्घname, "Intel HDMI/DP LPE Audio");

	card_ctx->irq = -1;

	card->निजी_मुक्त = hdmi_lpe_audio_मुक्त;

	platक्रमm_set_drvdata(pdev, card_ctx);

	card_ctx->num_pipes = pdata->num_pipes;
	card_ctx->num_ports = single_port ? 1 : pdata->num_ports;

	क्रम_each_port(card_ctx, port) अणु
		ctx = &card_ctx->pcm_ctx[port];
		ctx->card_ctx = card_ctx;
		ctx->dev = card_ctx->dev;
		ctx->port = single_port ? -1 : port;
		ctx->pipe = -1;

		spin_lock_init(&ctx->had_spinlock);
		mutex_init(&ctx->mutex);
		INIT_WORK(&ctx->hdmi_audio_wq, had_audio_wq);
	पूर्ण

	dev_dbg(&pdev->dev, "%s: mmio_start = 0x%x, mmio_end = 0x%x\n",
		__func__, (अचिन्हित पूर्णांक)res_mmio->start,
		(अचिन्हित पूर्णांक)res_mmio->end);

	card_ctx->mmio_start = ioremap(res_mmio->start,
					       (माप_प्रकार)(resource_size(res_mmio)));
	अगर (!card_ctx->mmio_start) अणु
		dev_err(&pdev->dev, "Could not get ioremap\n");
		ret = -EACCES;
		जाओ err;
	पूर्ण

	/* setup पूर्णांकerrupt handler */
	ret = request_irq(irq, display_pipe_पूर्णांकerrupt_handler, 0,
			  pdev->name, card_ctx);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "request_irq failed\n");
		जाओ err;
	पूर्ण

	card_ctx->irq = irq;

	/* only 32bit addressable */
	dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));

	init_channel_allocations();

	card_ctx->num_pipes = pdata->num_pipes;
	card_ctx->num_ports = single_port ? 1 : pdata->num_ports;

	क्रम_each_port(card_ctx, port) अणु
		पूर्णांक i;

		ctx = &card_ctx->pcm_ctx[port];
		ret = snd_pcm_new(card, INTEL_HAD, port, MAX_PB_STREAMS,
				  MAX_CAP_STREAMS, &pcm);
		अगर (ret)
			जाओ err;

		/* setup निजी data which can be retrieved when required */
		pcm->निजी_data = ctx;
		pcm->info_flags = 0;
		strscpy(pcm->name, card->लघुname, म_माप(card->लघुname));
		/* setup the ops क्रम playabck */
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &had_pcm_ops);

		/* allocate dma pages;
		 * try to allocate 600k buffer as शेष which is large enough
		 */
		snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_UC,
					       card->dev, HAD_DEFAULT_BUFFER,
					       HAD_MAX_BUFFER);

		/* create controls */
		क्रम (i = 0; i < ARRAY_SIZE(had_controls); i++) अणु
			काष्ठा snd_kcontrol *kctl;

			kctl = snd_ctl_new1(&had_controls[i], ctx);
			अगर (!kctl) अणु
				ret = -ENOMEM;
				जाओ err;
			पूर्ण

			kctl->id.device = pcm->device;

			ret = snd_ctl_add(card, kctl);
			अगर (ret < 0)
				जाओ err;
		पूर्ण

		/* Register channel map controls */
		ret = had_रेजिस्टर_chmap_ctls(ctx, pcm);
		अगर (ret < 0)
			जाओ err;

		ret = had_create_jack(ctx, pcm);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	ret = snd_card_रेजिस्टर(card);
	अगर (ret)
		जाओ err;

	spin_lock_irq(&pdata->lpe_audio_slock);
	pdata->notअगरy_audio_lpe = notअगरy_audio_lpe;
	spin_unlock_irq(&pdata->lpe_audio_slock);

	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_mark_last_busy(&pdev->dev);

	dev_dbg(&pdev->dev, "%s: handle pending notification\n", __func__);
	क्रम_each_port(card_ctx, port) अणु
		काष्ठा snd_पूर्णांकelhad *ctx = &card_ctx->pcm_ctx[port];

		schedule_work(&ctx->hdmi_audio_wq);
	पूर्ण

	वापस 0;

err:
	snd_card_मुक्त(card);
	वापस ret;
पूर्ण

/*
 * hdmi_lpe_audio_हटाओ - stop bridge with i915
 *
 * This function is called when the platक्रमm device is destroyed.
 */
अटल पूर्णांक hdmi_lpe_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_पूर्णांकelhad_card *card_ctx = platक्रमm_get_drvdata(pdev);

	snd_card_मुक्त(card_ctx->card);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops hdmi_lpe_audio_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(hdmi_lpe_audio_suspend, hdmi_lpe_audio_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver hdmi_lpe_audio_driver = अणु
	.driver		= अणु
		.name  = "hdmi-lpe-audio",
		.pm = &hdmi_lpe_audio_pm,
	पूर्ण,
	.probe          = hdmi_lpe_audio_probe,
	.हटाओ		= hdmi_lpe_audio_हटाओ,
पूर्ण;

module_platक्रमm_driver(hdmi_lpe_audio_driver);
MODULE_ALIAS("platform:hdmi_lpe_audio");

MODULE_AUTHOR("Sailaja Bandarupalli <sailaja.bandarupalli@intel.com>");
MODULE_AUTHOR("Ramesh Babu K V <ramesh.babu@intel.com>");
MODULE_AUTHOR("Vaibhav Agarwal <vaibhav.agarwal@intel.com>");
MODULE_AUTHOR("Jerome Anand <jerome.anand@intel.com>");
MODULE_DESCRIPTION("Intel HDMI Audio driver");
MODULE_LICENSE("GPL v2");
